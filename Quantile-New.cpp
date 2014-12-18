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
			if(comparator(*(Begin + (MoveElement - Begin)*2 + 1), *MoveElement))
				std::swap(*(Begin + (MoveElement - Begin)*2 + 1), *MoveElement);
		}
		else
		{
			while(true)
			{
				Iterator MoveTo = MoveElement;
				if((End - Begin) >= (MoveElement - Begin)*2+1)
					if(comparator(*(Begin + (MoveElement - Begin)*2+1), *MoveElement))
						MoveTo = Begin + (MoveElement - Begin) * 2 + 1;
				if((End - Begin) >= (MoveElement - Begin)*2+2)
					if(comparator(*(Begin + (MoveElement - Begin) * 2 + 2), *MoveTo))
						MoveTo = Begin + (MoveElement - Begin) * 2 + 2;
				if(MoveElement == MoveTo)
					return;
				std::swap(*MoveTo, *MoveElement);
				MoveElement = MoveTo;
			}
		}
}

template <typename Container>
void Solution(Container &Input, Container &Heap1, Container &Heap2,
			  const size_t &N, size_t &Quantile, const double &alpha, Container &Result)
{
	Heap1.push_back(Input[0]);
	Heap2.push_back(Input[0]);
	std::cout << Input[0] << '\n';
	Result[0] = Input[0];
	Quantile = 0;
	double Tmp;
	for(int i = 1; i < N; ++i)
	{
		Tmp = Quantile;
		Quantile = std::floor(alpha * static_cast<double>(i));
		if(Quantile - Tmp == 0)
		{
			if(Input[i] < *(Heap1.begin()))
			{
				*(Heap1.begin()) = Input[i];
				SiftDown(Heap1.begin(), Heap1.end()-1, std::greater<int>());
				Heap2.push_back(*Heap1.begin());
				SiftUp(Heap2.begin(), Heap2.end()-1, std::less<int>());
			}
			else
			{
				Heap2.push_back(Input[i]);
				SiftUp(Heap2.begin(), Heap2.end()-1,std::less<int>());
			}
		}
		else
		{
			if(Input[i] < *(Heap1.begin()))
			{
				Heap1.push_back(Input[i]);
				SiftUp(Heap1.begin(), Heap1.end()-1,std::greater<int>());
			}
			else
			{
				*Heap2.begin() = Input[i];
				SiftDown(Heap2.begin(), Heap2.end()-1, std::less<int>());
				Heap1.push_back(*Heap2.begin());
				SiftUp(Heap1.begin(), Heap1.end()-1, std::greater<int>());
			}
		}
//		Result[i] = *Heap1.begin();
		std::cout << *Heap1.begin() << '\n';
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