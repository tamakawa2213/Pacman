#include "AStar2D.h"
#include "Engine/CallDef.h"

AStar2D::AStar2D(short size) : MapSize_(size), Start_(), Goal_(), totalMove_(0), ppCost_()
{
	Unexplored_.clear();
	Explored_.clear();
	Routelist_.clear();
	MapData_.clear();
}

AStar2D::~AStar2D()
{
	Unexplored_.clear();
	Explored_.clear();
	Routelist_.clear();
	MapData_.clear();
}

void AStar2D::SetStart(std::pair<int, int> start)
{
	Start_ = start;
	ppCost_[Start_.first][Start_.second] = 0;
	Unexplored_.remove({ Start_.first, Start_.second });
}

void AStar2D::SetGoal(std::pair<int, int> goal)
{
	Goal_ = goal;
}

void AStar2D::SetData(std::vector<std::vector<char>> MapData)
{
	for (int i = 0; i < MapSize_; i++)
	{
		MapData_.push_back(MapData.at(i));
	}
	//各データに初期値を設定
	for (int x = 0; x < MapSize_; x++)
	{
		for (int z = 0; z < MapSize_; z++)
		{
			ppCost_[x][z] = CostMax_;
			if (MapData_[x][z] == 1)
			{
				ppCost_[x][z] = -1;
			}
			Unexplored_.push_back({ x,z });
		}
	}
}

float AStar2D::GetDistance(std::pair<int, int> pos1)
{
	float ans = (float)sqrt(pow(((double)pos1.first - (double)Goal_.first), 2) + pow(((double)pos1.second - (double)Goal_.second), 2));
	return ans;
}

bool AStar2D::Passable(int X, int Z)
{
	if (X >= 0 && Z >= 0)
	if (MapData_.at(X).at(Z) == 0)
	{
		return true;
	}
	return false;
}

void AStar2D::Initialize()
{
	for (int i = 0; i < MapSize_; i++)
	{
		ppCost_.push_back({ (float)CostMax_ });
		for (int j = 1; j < MapSize_; j++)
		{
			ppCost_[i].push_back({ (float)CostMax_ });
		}
	}
}

void AStar2D::Adjacent(Move next)
{
	std::list<std::pair<int, int>> ex;
	ex.clear();
	totalMove_++;
	bool IsSearched = false;
	for (Move Dir : Direction)	//現在位置に隣り合っている4地点にコストを割り振っていく
	{
		int nextW = next.moveLR + Dir.moveLR;
		int nextH = next.moveHL + Dir.moveHL;
		if (Passable(nextW, nextH))
		{
			if (ppCost_[nextW][nextH] == CostMax_)
			{
				std::pair<int, int> nextpos = std::pair<int, int>(nextW, nextH);

				int movesX = Start_.first - (int)nextpos.first;
				int movesZ = Start_.second - (int)nextpos.second;
				if (movesX < 0)
				{
					movesX = -movesX;
				}
				if (movesZ < 0)
				{
					movesZ = -movesZ;
				}
				int Moves = movesX + movesZ;
				ppCost_[nextW][nextH] = GetDistance(nextpos) + totalMove_;

				//ゴールならば探索終了
				if (GetDistance(nextpos) < 0.1f)
				{
					Explored_.push_back({ nextW, nextH });
					return;
				}
				IsSearched = true;
				ex.push_back(nextpos);

				Unexplored_.remove({ nextW, nextH });
				Explored_.push_back({ nextW, nextH });
			}
		}
	}

	std::pair<float, std::pair<int, int>> Min;
	Min.first = CostMax_;
	Min.second = std::pair<int, int>(0, 0);

	//4点の少なくとも1つ以上探索ができた場合、その中でコストが最も小さい位置に移動する
	if (IsSearched)
	{
		for (auto itr = ex.begin(); itr != ex.end(); itr++)
		{
			if (ppCost_[(*itr).first][(*itr).second] < Min.first && ppCost_[(*itr).first][(*itr).second] > 0)
			{
				Min.first = ppCost_[(*itr).first][(*itr).second];
				Min.second = std::pair<int, int>((*itr).first, (*itr).second);
			}
		}
	}
	//いずれもできなかった場合、現在位置のコストの次に小さいコストを持つ位置に移動する
	else
	{
		float Died = ppCost_[next.moveLR][next.moveHL];

		for (auto itr = Unexplored_.begin(); itr != Unexplored_.end(); itr++)
		{
			if (ppCost_[(*itr).first][(*itr).second] < Min.first && ppCost_[(*itr).first][(*itr).second] > Died)
			{
				Min.first = ppCost_[(*itr).first][(*itr).second];
				Min.second = std::pair<int, int>((*itr).first, (*itr).second);
			}
		}
	}

	ex.clear();

	if ((int)Min.second.first == 0 && (int)Min.second.second == 0)
	{
		return;
	}

	//if (Min.first != CostMax_)
	{
		Adjacent({ (int)Min.second.first, (int)Min.second.second });
	}
}

void AStar2D::Route(std::pair<int, int> pos)
{
	std::pair<int, int> next = pos;
	float necos = CostMax_;

	for (Move Dir : Direction)
	{
		int nextW = pos.first + Dir.moveLR;
		int nextH = pos.second + Dir.moveHL;

		auto itr = std::find(Explored_.begin(), Explored_.end(), std::pair<int, int>(nextW, nextH));
		if (itr != Explored_.end())
		{
			if (std::pair<int, int>(nextW, nextH) == Start_)
			{
				Routelist_.push_back(std::pair<int, int>(nextW, nextH));
				return;
			}

			//隣り合う要素で最もコストが低い要素を選択する
			if (nextW >= 0 && nextH >= 0)
				if (ppCost_[nextW][nextH] < necos && ppCost_[nextW][nextH] >= 0)
				{
					necos = ppCost_[nextW][nextH];
					next = std::pair<int, int>(nextW, nextH);
				}
			Explored_.erase(itr);
		}
	}

	//同一の要素が発見された場合、ルート検索を終了する
	auto itr = std::find(Routelist_.begin(), Routelist_.end(), next);
	if (itr != Routelist_.end())
		return;

	Routelist_.push_back(next);
	Route(next);
}

void AStar2D::GetRoute(std::list<std::pair<int, int>>& Routelist)
{
	memcpy_s(&Routelist, std::size(Routelist_), &Routelist_, std::size(Routelist_));
}

void AStar2D::Reset()
{
	Unexplored_.clear();
	for (int x = 0; x < MapSize_; x++)
	{
		for (int z = 0; z < MapSize_; z++)
		{
			ppCost_[x][z] = CostMax_;
			if (MapData_[x][z] == 1)
			{
				ppCost_[x][z] = -1;
			}
			Unexplored_.push_back({ x,z });
		}
	}
	Explored_.clear();
	Routelist_.clear();
	totalMove_ = 0;
}
