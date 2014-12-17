#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include <cmath>
#include <math.h>
#include <cstdio>
#include <iterator>
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
		if(End - Begin == 1)
		{
			if(comparator(*MoveElement, *(Begin + (Begin - MoveElement)*2 + 1)))
				std::iter_swap(Begin + (Begin - MoveElement)*2 + 1, MoveElement);
		}
		else
		{
			while(true)
			{
				Iterator MoveTo = MoveElement;
				if(comparator(*MoveElement, *(Begin + (Begin - MoveElement)*2+1)))
					MoveTo = Begin + (Begin - MoveElement) * 2 + 1;
				else
					if(comparator(*MoveTo, *(Begin + (Begin - MoveElement) * 2 + 2)))
						MoveTo = Begin + (Begin - MoveElement) * 2 + 2;
					else
						return;
				std::iter_swap(MoveTo, MoveElement);
			}
		}
}

//Все хорошо, только добавить для Heap1.empty() == true
template <typename Container>
void Solution(Container &Input, Container &Heap1, Container &Heap2,
			  const size_t &N, size_t &Quantile, const double &alpha)
{
	std::cout << Input[0] << '\n';
	size_t Tmp;
	for(int i = 1; i < N; ++i)
	{
		Tmp = Quantile;
		Quantile = std::floor(alpha * static_cast<double>(i));
		if((Quantile - Tmp) == 0)
		{
			if(!Heap1.empty())
			{
				if(Input[i] <= *Heap1.begin())
				{
					Heap2.push_back(*Heap1.begin());
					SiftUp(Heap2.begin(), Heap2.end()-1, std::less<int>());
					Heap1[0] = Input[i];
					SiftDown(Heap1.begin(), Heap1.end()-1, std::greater<int>());
				}
				else
				{
					Heap2.push_back(Input[i]);
					SiftUp(Heap2.begin(), Heap2.end()-1, std::less<int>());
				}
			}
			else
			{
				Heap2.push_back(Input[i]);
				SiftUp(Heap2.begin(), Heap2.end()-1, std::less<int>());
			}
		}
		else
		{
			if(!Heap1.empty())
			{
				if(Input[i] <= *Heap1.begin())
				{
					Heap1.push_back(Input[i]);
					SiftUp(Heap1.begin(), Heap1.end()-1, std::greater<int>());
				}
				else
				{
					Heap1.push_back(Heap2[0]);
					*Heap2.begin() = Input[i];
					auto En = Heap2.end(); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					En--;
					auto Beg = Heap2.begin();//!!!!!!!!!!!!!!!!!!!!!!!
					auto comp = std::less<int>();
//					SiftDown(Heap2.begin(), Heap2.end()-1, std::less<int>());
					SiftDown(Beg, En, comp);
					SiftUp(Heap1.begin(), Heap1.end()-1, std::greater<int>());
				}	
			}
			else
			{
				if(*Heap2.begin() < Input[i])
				{
					Heap1.push_back(Heap2[0]);
					*Heap2.begin() = Input[i];
					if(Heap2.size() != 0)
					{
						auto En = Heap2.end(); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						En--;
						auto Beg = Heap2.begin();//!!!!!!!!!!!!!!!!!!!!!!!
						auto comp = std::less<int>();
//						SiftDown(Heap2.begin(), Heap2.end()-1, std::less<int>());
						SiftDown(Beg, En, comp);
					}
				}
				else
					Heap1.push_back(Input[i]);
			}
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	std::vector <int> Heap1;//Min On Top
	std::vector <int> Heap2;//Max On Top
	std::vector <int> Input;
	double alpha;
	size_t N, Quantile = 0;
	std::cin >> N >> alpha;
	int Tmp;
	for(int i = 0; i < N; ++i)
	{
		std::cin >> Tmp;
		Input.push_back(Tmp);
	}
	Solution(Input, Heap1, Heap2, N, Quantile, alpha);
	return 0;
}