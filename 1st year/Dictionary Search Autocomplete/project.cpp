#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Node
{
	Node();
	string entered_word;
	Node* next [26];
	bool word  ; //if this bool is true that means that theres a word that ends here
	bool complete; //if this bool is true that means that there's an end after this letter
};
Node::Node()
{ //initializes the valuse of two booleans in all structs & makes the pointer point to NULL
	word =false; complete =false; 
	for (int i = 0 ;  i < 26 ; i ++)
		next[i] = NULL;
}
void read (Node*&head);
bool search (Node*head,string word);
void autocomplete (Node*head,string word);
void deeper (Node*head,int &words_count);
int main ()
{
	Node *head;
	head = new Node[26];
	cout << "Loading ... \n";
	read (head);										//this function fills the tree with the txt file
	cout << "Enter the Number of words you want to check for : ";
	int n;
	cin >> n;
	for (int i =0 ; i<n ; i++)
	{
		cout << "Enter the word you want to check for : ";
		string word;
		cin >>word;
		bool available= search(head,word);				 //this checks weather the entered word is available or not
		if (available)
			cout << "The word you entered\t "<<word<<"\t exists\n";
		else
		{
			cout << "The word you entered\t "<<word<<"\t doesn't exist\n";
			cout << "Suggestions:\n";					//if the word doesn't exist then the program checks for the nearest word to this word
			autocomplete (head,word);
		}
	}
	cout <<"--------------------------------------\n";
	cout<<"Enter the number of times you wish to use autocomplete : ";
	int num;
	cin >> num;
	for (int i=0;i<num;i++)
	{																	//loops on the number of times the user wants to use the autocomplete procedure
		cout << "Enter the word that you'd like to autocomplete : ";
		string word;
		cin >> word;
		autocomplete (head,word);
	}
	return 0;
}
void read (Node*&head)
{// this function inserts the text file into a tree just by sending an array of structs to it and that array would be the first level in the tree
	ifstream in ("word_list.txt");
	int n;
	in >> n;
	string word ;

	for (int i = 0 ; i<n ; i++)
	{
		Node*p =head;
		in >> word;
		int size = word.length();
		p+=(word[0]-'a');
		p->complete = true ;
		Node**x = p->next;
		if (p->next[word[1]-'a'] == NULL)
			p->next[word[1]-'a'] = new Node;
		for (int e = 1 ; e <size-1; e++)
		{

			int letter = word[e]-'a';
			int next_letter = word[e+1] -'a';
			x[letter]->complete = true ;
			if (e<size-1&& x[letter]->next[next_letter]==NULL)
			{
				x[letter]->next[next_letter] = new Node;
			}
			x=x[letter]->next;
		}
		p=x[word[size-1]-'a'];
		p->word =true;
		p->entered_word=word;
	}
}
bool search (Node*head,string word)
{
	int size =word.length();
	head+=(word[0]-'a');
	for (int i=1;i<size;i++)
	{
		if (head ==NULL ) return false;
		head = head->next[word[i]-'a'];
	}
	if (head == NULL) return false;
	return head->word;
}
void autocomplete (Node*head,string word)
{
	int size = word.length();
	head+=(word[0]-'a');
	// this loop works on the entered word and goes to the level where it's possible to continue 
	//either to the last letter in the inserted word or the last possible letter that we can continue after it in the word
	for (int i = 1 ; i<size;i++)
	{		
		if (head->next[word[i]-'a']!=NULL)
		head = head->next[word[i]-'a'];
		else
			i=size;
	}
	int words_count =0;
	deeper (head,words_count);
}

void deeper (Node*head,int &words_count)
{ // recursive function that goes into all the levels and brings 10 possible words to complete for autocomplete
	for (int x = 0 ; x <26 ; x++)
	{
		if (head->next[x]!=NULL )
		{
			//hit.push (head);
			Node*temp = head;
			head = head->next[x];
			if (head->word)
			{
				if (words_count <= 9)
				{
					cout<<"\t"<<head->entered_word<<"\n";
					words_count++;
				}
				else return;
			}
			if (head->complete)
			{
				deeper(head,words_count);
			}
			head=temp;
		}

	}
}