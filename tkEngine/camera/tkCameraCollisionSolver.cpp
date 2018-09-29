/*!
 *@brief	カメラのコリジョンソルバー。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/camera/tkCameraCollisionSolver.h"

namespace tkEngine{
	struct SConvexSweepCallback : public btCollisionWorld::ClosestConvexResultCallback
	{
	public:
		CVector3 hitNor;
		CVector3 hitPoi;
		CVector3 m_rayDir;
		btCollisionObject* me = nullptr;
		SConvexSweepCallback(CVector3 rayDir) :
			btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f) ),
			m_rayDir(rayDir){}
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			hitNor = *(CVector3*)&convexResult.m_hitNormalLocal;
			hitPoi = *(CVector3*)&convexResult.m_hitPointLocal;
			
			CVector3 normal;
			normal.Set(convexResult.m_hitNormalLocal);
		
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character) {
				return 1.0f;
			}
			return btCollisionWorld::ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
		}
	};
	CCameraCollisionSolver::CCameraCollisionSolver()
	{
	}
	CCameraCollisionSolver::~CCameraCollisionSolver()
	{
	}
	void CCameraCollisionSolver::Init(float radius)
	{
		m_radius = radius;
		m_collider.Create(radius);
		//m_CCC.Init(radius, radius, MainCamera().GetPosition());
	}
	bool CCameraCollisionSolver::Execute(CVector3& result, const CVector3& position, const CVector3& target )
	{
		result = position;
		CVector3 vWk;
		vWk.Subtract(target, position);
		if (vWk.LengthSq() < FLT_EPSILON) {
			//視点と注視点がほぼ同じ座標にある。
			return false;
		}
		vWk.Normalize();

		//レイを作成する。
		btTransform btStart, btEnd;
		btStart.setIdentity();
		btEnd.setIdentity();

		//btStart.setOrigin(btVector3(target.x, target.y, target.z));
		btStart.setOrigin(btVector3(target.x, target.y, target.z));
		btEnd.setOrigin(btVector3(position.x, position.y, position.z));
		SConvexSweepCallback callback(vWk);
		//	callback.m_collisionFilterGroup = 
		PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), btStart, btEnd, callback);
		if (callback.hasHit()) 
		{
			CVector3 vHitPos;
			vHitPos.Set(callback.m_hitPointWorld);

			CVector3 vOffset;
			vOffset.Set(callback.m_hitNormalWorld);
			vOffset.Scale(m_radius);
			result.Add(vHitPos, vOffset);
			return true;
		}
		return false;
	}
	CVector3 CCameraCollisionSolver::Execute(CVector3 position, CVector3 oldpos)
	{
		//CVector3 pos = position;
		CVector3 nex = position;

		for (int count = 0; count < 5; count++)
		{
			CVector3 vWk;
			vWk.Subtract(oldpos, position);
			if (vWk.LengthSq() < FLT_EPSILON) {
				//視点と注視点がほぼ同じ座標にある。
				return nex;
			}
			vWk.Normalize();

			//レイを作成する。
			btTransform btStart, btEnd;
			btStart.setIdentity();
			btEnd.setIdentity();

			btStart.setOrigin(btVector3(oldpos.x, oldpos.y, oldpos.z));
			btEnd.setOrigin(btVector3(position.x, position.y, position.z));
			SConvexSweepCallback callback(vWk);
			//	callback.m_collisionFilterGroup = 
			PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), btStart, btEnd, callback);
			if (callback.hasHit())
			{
				CVector3 vpos, vhit;
				vpos = nex;
				vhit = callback.hitPoi;
				CVector3 meri;
				meri = vpos - vhit;

				CVector3 vnor = callback.hitNor;
				float ang = vnor.Dot(meri);

				CVector3 ofs = callback.hitNor;
				ofs.Scale(-ang + m_radius);
				nex.Add(ofs);
			}
			else
			{
				break;
			}
		}
		return nex;
	}
}
