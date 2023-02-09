#pragma once
#include <list>
#include <vector>

struct Move
{
	int moveLR;
	int moveHL;
};

const Move Direction[4]
{
	{1,0},		//右
	{-1,0},		//左
	{0,1},		//上
	{0,-1}		//下
};

class AStar2D
{
	const short CostMax_ = 999;

	const short MapSize_;

	std::pair<int, int> Start_;
	std::pair<int, int> Goal_;

	std::list<std::pair<int, int>> Unexplored_;	//未探索
	std::list<std::pair<int, int>> Explored_;	//探索済み
	std::list<std::pair<int, int>> Routelist_;	//最終的なルートを示す

	std::vector<std::vector<char>> MapData_;

	float** ppCost_;

	int totalMove_;	//総移動距離

	float GetDistance(std::pair<int, int> pos1);
	bool Passable(int X, int Z);
public:
	AStar2D(short size);
	~AStar2D();
	void SetStart(std::pair<int, int> start);
	void SetGoal(std::pair<int, int> goal);
	void SetData(std::vector<std::vector<char>> MapData);
	void Initialize();
	void Adjacent(Move next);
	void Route(std::pair<int, int> pos);
	void GetRoute(std::list<std::pair<int, int>>& Routelist);
	void Reset() { Unexplored_.clear(); Explored_.clear(); Routelist_.clear(); }
	std::list<std::pair<int, int>> GetRoute() { return Routelist_; }
};