//Name : Ahmed Talaat Ibrahem Elrayes
//1st year computer department cairo university
//Mini project #1
#include <iostream>
#include "HandDigit.h"
#include <fstream>
#ifndef NULL
#define NULL 0
#endif
using namespace std;
struct image
{ // old images
	int arr [IMG_SIZE];
	int num;
	image* next;
};
struct list 
{
	int comp;
	int num;
};
//#include "trans.h"
int n; //int S[1000]; int top=-1;
void read_file(image*&head,int & n);
void compare (int*arr,image*head);
int main ()
{
	int x; int num;//S[0]=0;
	image*head=NULL;
	int*p;
	int arr[IMG_SIZE];
	p=arr;
	cout<<"loading ..."<<endl;
	read_file(head,n);
	cout<<"Enter the number of entries:";
	cin>>x;
	for (int i=0;i<x;i++)
	{
		getDigit(p);
		compare(arr,head);
	}
	return 0;
}
void read_file(image*&head,int& n)
{
	//reads train_1_5.txt file and puts it in a linked list
	ifstream file("train_1_5.txt");
	file>>n;
	for (int i =0;i<n;i++)
	{
		image*temp=new image;
		for (int e=0;e<IMG_SIZE;e++)
			file>>temp->arr[e];
		file>>temp->num;
		temp->next=head;
		head=temp;
	}
	file.close();
}
void compare (int*arr,image*head)
{
	image*p=head; int c;
	list compare[1000]; int top2=-1;
	while (p!=NULL)
	{
		c=0;
		for (int i=0;i<IMG_SIZE;i++)
		{
			if (arr[i]==p->arr[i])
				c++;
		}
		if (top2==-1)
		{
			top2++;
			compare[top2].comp=c;
			compare[top2].num=p->num;
		}
		else if (c>compare[top2].comp)
		{
			top2++;
			compare[top2].comp=c;
			compare[top2].num=p->num;
		}
		p=p->next;
	}
	cout<<"The number you entered is : ";
	cout<<compare[top2].num<<endl;
}
