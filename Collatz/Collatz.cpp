#include "stdafx.h"
#include <iostream>
#include <limits.h>
#define MAX 1
#define MIN -1

//Przy pisaniu projektu posłużyłem się pseudokodem zawartym w slajdach wykładu dr. inż. Krzysztofa Manuszewskiego

struct node
{
	unsigned int value;
	int org, other;
};

int Parent(int i)
{
	return i / 2;
}

int Left(int i)
{
	return i * 2;
}

int Right(int i)
{
	return i * 2 + 1;
}

void HeapifyDown(int i, int size, int orien, node* min, node* max)
{
	int maxps;
	node temp;
	int L = Left(i);
	int R = Right(i);
	if (orien == MAX)
	{
		if (L <= size && max[L - 1].value > max[i - 1].value)
			maxps = L;
		else if (L <= size && max[L - 1].value == max[i - 1].value)
		{
			if (max[L - 1].org < max[i - 1].org)
				maxps = L;
			else
				maxps = i;
		}
		else
			maxps = i;

		if (R <= size && max[R - 1].value > max[maxps - 1].value)
			maxps = R;
		else if (R <= size && max[R - 1].value == max[maxps - 1].value)
		{
			if (max[R - 1].org < max[maxps - 1].org)
				maxps = R;
		}

		if (maxps != i)
		{
			temp = max[i - 1];
			max[i - 1] = max[maxps - 1];
			min[temp.other].other = maxps - 1;
			min[max[maxps - 1].other].other = i - 1;
			max[maxps - 1] = temp;
			HeapifyDown(maxps, size, orien, min, max);
		}
	}
	else if (orien == MIN)
	{
		if (L <= size && min[L - 1].value < min[i - 1].value)
			maxps = L;
		else if (L <= size && min[L - 1].value == min[i - 1].value)
		{
			if (min[L - 1].org < min[i - 1].org)
				maxps = L;
			else
				maxps = i;
		}
		else
			maxps = i;

		if (R <= size && min[R - 1].value < min[maxps - 1].value)
			maxps = R;
		else if (R <= size && max[R - 1].value == min[maxps - 1].value)
		{
			if (min[R - 1].org < min[maxps - 1].org)
				maxps = R;
		}

		if (maxps != i)
		{
			temp = min[i - 1];
			min[i - 1] = min[maxps - 1];
			max[temp.other].other = maxps - 1;
			max[min[maxps - 1].other].other = i - 1;
			min[maxps - 1] = temp;
			HeapifyDown(maxps, size, orien, min, max);
		}
	}
}

void HeapifyUp(int i, int orien, node* min, node* max)
{
	int maxps;
	node temp;
	int parent = Parent(i);
	if (orien == MAX)
	{
		if (parent >= 0 && max[parent].value < max[i].value)
			maxps = parent;
		else if (parent >= 0 && max[parent].value == max[i].value)
		{
			if (max[parent].org > max[i].org)
				maxps = parent;
			else
				maxps = i;
		}
		else
			maxps = i;

		if (maxps != i)
		{
			temp = max[i];
			max[i] = max[maxps];
			min[temp.other].other = maxps;
			min[max[maxps].other].other = i;
			max[maxps] = temp;
			HeapifyUp(maxps, orien, min, max);
		}
	}
	else if (orien == MIN)
	{
		if (parent >= 0 && min[parent].value > min[i].value)
			maxps = parent;
		else if (parent >= 0 && min[parent].value == min[i].value)
		{
			if (min[parent].org > min[i].org)
				maxps = parent;
			else
				maxps = i;
		}
		else
			maxps = i;

		if (maxps != i)
		{
			temp = min[i];
			min[i] = min[maxps];
			max[temp.other].other = maxps;
			max[min[maxps].other].other = i;
			min[maxps] = temp;
			HeapifyUp(maxps, orien, min, max);
		}
	}
}


void BuildHeap(int size, int orien, node* min, node* max)
{
	for (int i = Parent(size); i > 0; i--)
		HeapifyDown(i, size, orien, min, max);
}

unsigned int Collatz(long long n)
{
	if (n % 2 == 1)
	{
		if (3 * n + 1 > UINT_MAX)
			return 0;
		else
			return ((3 * n) + 1);
	}
	else
		return (n / 2);
}

void Remove(node* min, node* max, int index, int& size, int orien)
{
	if (orien == MIN)
	{
		max[min[size - 1].other].other = index;
		max[min[index].other].other = size - 1;
		if (index != size - 1)
			min[index] = min[size - 1];
	}
	else
	{
		min[max[size - 1].other].other = index;
		if (index != size - 1)
			max[index] = max[size - 1];
	}
	size--;

	if (orien == MIN)
	{
		if (Parent(index) >= 0 && min[index].value < min[Parent(index)].value)
		{
			HeapifyUp(index, MIN, min, max);
		}
		else if (index == 0 || min[index].value > min[Parent(index)].value)
		{
			HeapifyDown(index + 1, size, MIN, min, max);
		}
	}
	else
	{
		if (Parent(index) >= 0 && max[index].value > max[Parent(index)].value)
		{
			HeapifyUp(index, MAX, min, max);
		}
		else if (index == 0 || max[index].value < max[Parent(index)].value)
		{
			HeapifyDown(index + 1, size, MAX, min, max);
		}
	}

}

void Command(int k, char c, int& sizeMin, int& sizeMax, node* min, node* max, node* org)
{
	unsigned int result, p;
	int indexMin, indexMax, pos;
	int index = 0;

	for (int i = 0; i < k; i++)
	{
		while (sizeMin > 0 && (min[0].value == 1 || min[0].value == 0))
		{
			Remove(min, max, 0, sizeMin, MIN);
		}
		if (sizeMin > 0)
		{

			if (c == 's')
			{
				result = Collatz(min[index].value);
				p = min[index].value;
				min[index].value = result;
				max[min[index].other].value = result;
				org[min[index].org].value = result;
				indexMin = index;
				indexMax = min[index].other;
				if (result > p)
				{
					HeapifyDown(indexMin + 1, sizeMin, MIN, min, max);
					HeapifyUp(indexMax, MAX, min, max);
				}

			}
			else if (c == 'l' && max[0].value != 1 && max[0].value != 0)
			{
				result = Collatz(max[0].value);
				p = max[0].value;
				max[0].value = result;
				min[max[0].other].value = result;
				org[max[0].org].value = result;
				indexMax = 0;
				indexMin = max[0].other;
				if (result < p)
				{
					HeapifyDown(indexMax + 1, sizeMax, MAX, min, max);
					HeapifyUp(indexMin, MIN, min, max);
				}
			}
		}
	}
}

int main()
{
	int numberOfCommands, k;
	char c;
	int sizeOrig, sizeMin, sizeMax;

	scanf("%d", &sizeOrig);
	sizeMin = sizeOrig;
	sizeMax = sizeOrig;

	node* orig = (node*)malloc(sizeOrig * sizeof(node));
	node* max = (node*)malloc(sizeOrig * sizeof(node));
	node* min = (node*)malloc(sizeOrig * sizeof(node));

	for (int i = 0; i < sizeOrig; i++)
	{
		scanf("%u", &orig[i].value);
		orig[i].org = i;
		orig[i].other = i;
		max[i] = orig[i];
		min[i] = orig[i];
	}
	BuildHeap(sizeMin, MIN, min, max);
	BuildHeap(sizeMax, MAX, min, max);

	scanf("%d", &numberOfCommands);
	for (int i = 0; i < numberOfCommands; i++)
	{
		scanf("%d %c", &k, &c);
		if (sizeMin > 0)
		{
			Command(k, c, sizeMin, sizeMax, min, max, orig);
		}
	}

	for (int i = 0; i < sizeOrig; i++)
	{
		if (orig[i].value == 0)
			printf("m ");
		else
			printf("%u ", orig[i].value);
	}

	free(orig);
	free(min);
	free(max);

	return 0;
}

