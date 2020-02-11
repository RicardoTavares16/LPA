#include <stdlib.h>
#include <stdio.h>

void swap(int* a, int* b)
{
	int t = *a;

	*a = *b;
	*b = t;
}

int partition (int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);
	int j;

	for (j = low; j <= high- 1; j++)
	{

		if (arr[j] <= pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int check(int numberGuests, int *guestList)
{
	int i, j, k;
	for (i = 0; i < numberGuests - 1; ++i)
	{
		j = i + 1;
		k = numberGuests - 1;

		while (k != j)
		{
			if (guestList[i] + guestList[j] + guestList[k] == 0)
			{
				return 1;
			}
			else if (guestList[i] + guestList[j] + guestList[k] > 0)
			{
				--k;
			}
			else
			{
				++j;
			}
		}
	}
	return 0;
}

int main()
{
	int numberGuests, i;

	while(scanf("%d", &numberGuests) == 1)
	{
		int guestList[numberGuests];

		for(i = 0; i < numberGuests; i++) scanf("%d", &guestList[i]);
		quickSort(guestList, 0, numberGuests - 1);
		if (check(numberGuests, guestList) == 1){
			printf("Fair\n");
		}
		else printf("Rigged\n");
		scanf("%d", &numberGuests);
	}
	return 0;
}