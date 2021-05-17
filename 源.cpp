#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<cmath>
#include <iomanip>
using namespace std;
const int MAX = 0xFFFFFFF;
const int MIN = -MAX;
struct point
{
	float x;
	float y;
};

float distance2(point p1, point p2)
{
	float X = p1.x - p2.x;
	float Y = p1.y - p2.y;
	return (pow(X, 2) + pow(Y, 2));
}
class comparex
{
public:
	bool operator()(point p1, point p2)
	{
		return p1.x < p2.x;
	}
};

class comparey
{
public:
	bool operator()(point p1, point p2)
	{
		return p1.y < p2.y;
	}
};


float closest_pair(std::vector<point> pset, std::vector<point> Py)
{
	if (pset.size() <= 2)//�ݹ龡ͷ
	{
		if (pset.size() == 2)
		{
			return distance2(pset[0], pset[1]);
		}
		else
			return MAX;
	}


	else
	{
		int mid = pset.size() / 2;//devide
		vector<point>::iterator itmid = pset.begin();
		itmid += mid;
		vector<point> pleft(pset.begin(), itmid);
		vector<point> pright(itmid, pset.end());
		float devide = pset[mid - 1].x;
		pset.clear();
		vector<point> ply, pry;
		for (int i = 0;i < Py.size();i++)
		{
			if (Py[i].x <= devide)
			{
				ply.push_back(Py[i]);
			}
			if (Py[i].x >= devide)
			{
				pry.push_back(Py[i]);
			}
		}

		float l1, l2, l3;//calculate
		l1 = closest_pair(pleft, ply);
		l2 = closest_pair(pright, pry);


		float lm = (l1 < l2) ? l1 : l2;//merge
		vector<point> pmid;
		for (int i = 0;i < Py.size();i++)
		{
			if (pow((Py[i].x - devide), 2) <= lm)
			{
				pmid.push_back(Py[i]);
			}
		}
		l3 = MAX;
		for (int i = 0;i < pmid.size() - 1;i++)
		{
			int farthest;
			if (i + 8 > pmid.size())
			{
				farthest = pmid.size();
			}
			else
			{
				farthest = i + 8;
			}
			for (int j = i + 1;j < farthest;j++)
			{
				float distance = distance2(pmid[i], pmid[j]);
				if (l3 > distance)
				{
					l3 = distance;
				}
			}
		}
		pmid.clear();
		Py.clear();
		float Lm = (lm < l3) ? lm : l3;
		return Lm;
	}
}

int main()
{
	int N;
	cin >> N;
	vector<point>Px, Py;
	for (int i = 0;i < N;i++)
	{
		float x, y;
		cin >> x;
		cin >> y;
		point p{ x,y };
		Px.push_back(p);
		Py.push_back(p);
	}
	sort(Px.begin(), Px.end(), comparex());
	sort(Py.begin(), Py.end(), comparey());
	cout << fixed << setprecision(2) << closest_pair(Px, Py);
}