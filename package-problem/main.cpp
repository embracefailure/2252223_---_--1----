#include<iostream>
#include<vector>
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
using namespace std;


//solution 1
int timmy_max(int n1, int n2)
{
	if (n1 > n2)
		return n1;
	else
		return n2;
}
void package_problem_recursion(int totalweight,int objnum,int *weight,int *value)
{

	int bagWeight = totalweight;

	//define 2-dimension array for dynamic planning
	vector<vector<int>>dynamicplanner(objnum + 1, vector<int>(bagWeight + 1, 0));

	//initiate the dynamicplanner array
	for (int k = weight[0]; k <= bagWeight; k++)
	{
		dynamicplanner[0][k] = value[0];
	}

	for (int i = 1; i <int( objnum); i++)
	{
		//walk through the objects in the vector
		for (int j = 0; j <= bagWeight; j++)
		{
			//check the package capacity
			if (j < weight[i])
			{
				dynamicplanner[i][j] = dynamicplanner[i - 1][j];//the package cannot store the object, thus no increase in total value
			}
			else
			{
				dynamicplanner[i][j] = timmy_max(dynamicplanner[i - 1][j], dynamicplanner[i - 1][j - weight[i]] + value[i]);//compare 2 possible options: put this object in the package or not.
			}
		}
	}
	cout << dynamicplanner[objnum- 1][bagWeight] << endl;
	//because you cannot memorize the seemed minor one but the correct one with the seemed greater one but the incorrect one, you cannot expect a result vector to collect the weights of the correct sets.
}

void user_input(int** w, int** v, int* objnum, int*c)
{
	cout << "Please input the maximun capacity of the bag as C:" << endl;
	cin >> *c;
	cout << "Please input the number of the objects:" << endl;
	cin >> *objnum;
	*w = (int*)malloc(sizeof(int) * (*objnum));
	*v = (int*)malloc(sizeof(int) * (*objnum));
	cout << "Please input the weight of the objects separately:" << endl;
	for (int i = 0; i < *objnum; i++)
	{
		cin >> *(*w+i);
	}
	cout << "Please input the value of the objects separately:" << endl;
	for (int i = 0; i < *objnum; i++)
	{
		cin >> *(*v + i);
	}
}


//solution2
typedef int SElemType;//int is the data type of the elements in the stack

typedef struct {
	SElemType* base;
	SElemType* top;
	int stacksize;
}Stack;

void InitStack(Stack* S)
{
	S->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
}

void push(Stack* S, SElemType E)
{
	if (S->top - S->base >= S->stacksize)
	{
		S->base = (SElemType*)realloc(S->base, (S->stacksize + STACK_INCREMENT) * sizeof(SElemType));
		if (!S->base)
		{
			exit(OVERFLOW);
		}
		S->top = S->base + S->stacksize;
		S->stacksize += STACK_INCREMENT;
	}
	*S->top++ = E;
}

int pop(Stack* S, SElemType* E)
{
	if (S->top == S->base)
	{
		return -1;
	}
	* E = *(--S->top);
	return *E;
}

int StackEmpty(Stack S)
{
	if (S.base == S.top)
	{
		return 1;
	}
	return -1;
}

int package_problem_stack(int* w, int* v, int objnum, int c)
{
	int bagweight = 0;
	int bagvalue = 0;
	int dpvalue = 0;
	Stack bag;
	InitStack(&bag);
	for (int i = 0; StackEmpty(bag) != 1 || i < objnum; i++)
	{
		if (bagweight == c || i >= objnum)
		{
			if(bagvalue>dpvalue)
			{
				dpvalue = bagvalue;
			}
			pop(&bag, &i);
			bagweight -= w[i];
			bagvalue -= v[i];
		}
		else if (c >= bagweight + w[i])
		{
			push(&bag, i);
			bagweight += w[i];
			bagvalue += v[i];
		}
	}
	return dpvalue;
}

int main()
{
	int* w, * v;
	int c,objnum;
	user_input(&w, &v, &objnum, &c);
	cout << "The maximum value is:" << endl;
	cout << "Recursion:";
	package_problem_recursion(c,objnum,w,v);
	cout << "Stack:";
	cout<<package_problem_stack(w, v, objnum, c);
}
