#pragma once
class SaveLoad
{
public:
	SaveLoad();
	void Load();
	void Save();

	std::vector<int>getBeginner()
	{
		return B;
	}
	std::vector<int>getIntermediate()
	{
		return I;
	}
	std::vector<int>getAdvanced()
	{
		return A;
	}

	void setBiginner(std::vector<int> b)
	{
		B = b;
	}
	void setIntermadiate(std::vector<int> i)
	{
		I = i;
	}
	void setAdvanced(std::vector<int> a)
	{
		A = a;
	}
private:
	std::vector<int> B;
	std::vector<int> I;
	std::vector<int> A;
};