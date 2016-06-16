//#include "..\\HandDigit.h"
#ifndef NULL
#define NULL 0
#endif
#define IMG_SIZE (28*28)
struct image 
{ // old images
	int arr [IMG_SIZE];
	int num;
	image* next;
};
struct mini_img
{ // new structure for the minimized images
	int number_ones;
	int* simple_arr;
	int num_presented;
	mini_img* next;
};
//void prepend (mini_img *& head)
//	{
//		mini_img temp = new mini_img;
//
//	}
mini_img* transform (image *head)
{
	mini_img* head2 = NULL;
	image* p = head;
	while (p!=NULL)
	{
		head2->number_ones = 0;
		for (int i = 0; i<IMG_SIZE; i++)
		{
			if(head->arr[i]==1)
				head2->number_ones++ ;
			i++;
		}
		head2->simple_arr = new int[head2->number_ones];
		int x = 0;
		for (int i=0;i<IMG_SIZE;i++)
		{
			if(head->arr[i]==1)
			{
				head2->simple_arr[x] = i;
				x++;
			}
		p=p->next;
	}
	head2->simple_arr = new int [ head2->number_ones];
	return head2;
}
