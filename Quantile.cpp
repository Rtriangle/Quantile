#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include <iterator>
#pragma warning(disable : 4996)

template <typename Iterator, typename Comparator>
void SiftUp(Iterator Begin, Iterator End, const Comparator &comparator)
{
	Iterator MoveElement = End;
	while(comparator(*MoveElement, *(Begin + ((MoveElement - Begin - 1) / 2))))
			iter_swap(MoveElement, Begin + ((MoveElement - Begin - 1) / 2));
}

template <typename Iterator, typename Comparator>
void SiftDown(Iterator Begin, Iterator End, const Comparator &comparator)
{
	Iterator MoveElement = Begin;
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
	Quantile = 0;
	std::cout << Input[0] << '\n';
	for(int i = 1; i < N; ++i)
	{
		Tmp = Quantile;
		Quantile = std::floor(alpha * static_cast<double>(i));
		if(Heap1.size() == 0 || Input[i] <= *(Heap1.begin()))
			if((Quantile - Tmp) == 1)
			{
				Heap1.push_back(Input[i]);
				SiftUp(Heap1.begin(),Heap1.end()-1, std::greater<int>());
			}
			else
			{
				if(!Heap1.empty())
				{
					size_t Tmp = Heap1[0];
					Heap1[0] = Input[i];
					Heap2.push_back(Tmp);
					SiftDown(Heap1.begin(), Heap1.end()-1, std::greater<int>());
				}
				else
					Heap2.push_back(Input[i]);
				SiftUp(Heap2.begin(), Heap2.end()-1, std::less<int>());
			}
		else
			if((Quantile - Tmp) == 1)
			{
				if(!Heap1.empty())
				{
					size_t Tmp = Heap2[0];
					Heap1.push_back(*(Heap2.begin()));
					Heap2[0] = Input[i];
					SiftUp(Heap1.begin(), Heap1.end()-1, std::greater<int>());
				}
				else
					Heap2.push_back(Input[i]);
				SiftDown(Heap2.begin(), Heap2.end()-1, std::less<int>());
			}
			else
			{
				Heap2.push_back(Input[i]);
				SiftUp(Heap2.begin(), Heap2.end()-1, std::less<int>());
			}
		if(!Heap1.empty())
			std::cout << *Heap1.begin() << '\n';
		else
			std::cout << Input[0] << '\n';
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}