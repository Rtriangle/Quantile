#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#pragma warning(disable : 4996)

template <typename Iterator, typename Comparator>
void SiftUp(Iterator Begin, Iterator End, const Comparator &comparator)
{
	Iterator MoveElement = End;
	while(Begin < MoveElement && comparator(*MoveElement, *(Begin + ((MoveElement - Begin - 1) / 2))))
	{
			std::iter_swap(MoveElement, Begin + ((MoveElement - Begin - 1) / 2));
			MoveElement = Begin + ((MoveElement - Begin - 1) / 2);
	}
}

template <typename Iterator, typename Comparator>
void SiftDown(Iterator Begin, Iterator End, const Comparator &comparator)
{
	Iterator MoveElement = Begin;
	if((End - Begin) == 0)
		return;
	else
		if((End - Begin) == 1)
		{
			if(comparator(*(Begin + (Begin - MoveElement)*2 + 1), *MoveElement))
				std::iter_swap(Begin + (Begin - MoveElement)*2 + 1, MoveElement);
		}
		else
		{
			while(true)
			{
				Iterator MoveTo = MoveElement;
				if(comparator(*(Begin + (Begin - MoveElement)*2+1), *MoveElement))
					MoveTo = Begin + (Begin - MoveElement) * 2 + 1;
				else
					if(comparator(*(Begin + (Begin - MoveElement) * 2 + 2), *MoveTo))
						MoveTo = Begin + (Begin - MoveElement) * 2 + 2;
					else
						return;
				std::iter_swap(MoveTo, MoveElement);
			}
		}
}

template <typename Container>
void Solution(Container &Input, Container &Heap1, Container &Heap2,
			  const size_t &N, size_t &Quantile, const double &alpha, Container &Result)
{
	int MinimByZero = Input[0]; 
	size_t Tmp;
	for(int i = 0; i < N; ++i)
	{
		Tmp = Quantile;
		Quantile = std::floor(alpha * static_cast<double>(i));
		if((Quantile - Tmp) == 0)
		{
			if(Heap2.empty())
			{
				Heap2.push_back(Input[i]);
				SiftUp(Heap2.begin(), Heap2.end()-1, std::less<int>());
			}
			else
			{
				if(Input[i] >= *Heap2.begin())
				{
					if(Quantile != 0)
					{
						Heap2.push_back(Input[i]);
						auto A = Heap2.begin(), B = Heap2.end()-1;
						auto com = std::less<int>();
						SiftUp(A,B,com);
//						SiftUp(Heap2.begin(), Heap2.end()-1, std::less<int>());
					}
					else
					{
						Heap2.push_back(Input[i]);
						SiftUp(Heap2.begin(), Heap2.end()-1,std::less<int>());
					}
				}
				else
				{
					if(Quantile != 0)
					{
						Heap1.push_back(Input[i]);
						SiftDown(Heap1.begin(),Heap1.end()-1,std::greater<int>());
						Heap2.push_back(*Heap1.begin());
						SiftUp(Heap2.begin(),Heap2.end()-1,std::less<int>());
					}
					else
					{
						Heap2.push_back(Input[i]);
						SiftUp(Heap2.begin(), Heap2.end()-1,std::less<int>());
					}
				}
			}
		}
		else
		{
			if(Input[i] < *Heap2.begin())
			{
				Heap1.push_back(Input[i]);
				SiftUp(Heap1.begin(), Heap1.end()-1, std::greater<int>());
			}
			else
			{
				Heap1.push_back(*Heap2.begin());
				SiftUp(Heap1.begin(), Heap1.end()-1, std::greater<int>());
				*Heap2.begin() = *(Heap2.end()-1);
				SiftDown(Heap2.begin(), Heap2.end()-1, std::greater<int>());
				*(Heap2.end()-1) = Input[i];
				SiftUp(Heap2.begin(),Heap2.end()-1, std::less<int>());
				auto A = Heap2.begin(), B = Heap2.end()-1;
				auto com = std::less<int>();
				SiftDown(A,B,com);
//				SiftDown(Heap2.begin(), Heap2.end()-1, std::less<int>());
			}
		}
		if(Heap2.empty())
		{
			MinimByZero = std::min(MinimByZero, Input[i]);
			std::cout << MinimByZero << '\n';
//			Result[i] = MinimByZero;
		}
		else
			std::cout << *Heap2.begin() << '\n';
//			Result[i] = *Heap.begin();
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	std::vector <int> Heap1;//Min On Top
	std::vector <int> Heap2;//Max On Top
	std::vector <int> Input;
	double alpha;
	size_t N, Quantile = 0;
	std::cin >> N >> alpha;
	std::vector <int> Result(N);
	int Tmp;
	for(int i = 0; i < N; ++i)
	{
		std::cin >> Tmp;
		Input.push_back(Tmp);
	}
	Solution(Input, Heap1, Heap2, N, Quantile, alpha, Result);
//	for(auto it = Result.begin(); it != Result.end(); ++it)
//		std::cout << *it << '\n';
	return 0;
}