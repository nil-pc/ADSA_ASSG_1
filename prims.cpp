//prims algorithm

#include<iostream>
#include<bits/stdc++.h> 
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
using namespace std;

int n,prior_len;
typedef struct adj_node           
{                         
	int node_val;
	int wt;
	struct adj_node*ptr;
}adj_node;

typedef struct adj_list_elem
{
	adj_node *front,*rear;
}adj_list_elem;

adj_list_elem *adj_list, *soln_list;               

adj_node* CreateNewAdjNode(int num)
{
	adj_node *newptr = (adj_node*)malloc(sizeof(adj_node));
	if (newptr==NULL)             //sets the value of node_val and ptr
	{                             // the wt is set later on
		printf("error\n");
		exit(0);
	}
	newptr->node_val=num;
	newptr->ptr=NULL;
	return newptr;
}

void create_adj_list()          
{
	for (int i=0;i<n;++i)
		adj_list[i].front=adj_list[i].rear=NULL;
}


typedef struct prior_node
{             
	int key;        
	int node_val;   
	struct prior_node*p;
}prior_node;

typedef struct prior_q_elem
{
	prior_node*ptr;      //an array of pointers that points to priority node
}prior_q_ele;

prior_q_ele *prior_q;

prior_node* CreatePriorNode(int value)
{
	prior_node*newptr=(prior_node*)malloc(sizeof(prior_node));
	if (newptr==NULL)
	{
		printf("Error");
		exit(0);
	}
	if(value==0)
		newptr->key=0;
	else                   //initialises the node with node_val 0 as 0
		newptr->key=INT_MAX;    // and the rest to inf
	newptr->node_val=value;
	newptr->p=NULL;
}

void create_prior_q()
{
	for(int i=0;i<n;++i)           //makes the ith element of the prior
		prior_q[i].ptr=CreatePriorNode(i);  //q pont to node_val i
}

void min_heapify(int i)
{
	int min,l,r;
	l=2*i+1;
	r=2*i+2;
	if(l<prior_len && (prior_q[l].ptr)->key < (prior_q[i].ptr)->key)
		min=l;
	else
		min=i;
	if(r<prior_len && (prior_q[r].ptr)->key < (prior_q[min].ptr)->key)
		min =r;
	if(min!=i)
	{
		prior_node*temp=prior_q[i].ptr;
		prior_q[i].ptr=prior_q[min].ptr;
		prior_q[min].ptr=temp;
		min_heapify(min);
	}
}

void build_heap()
{
	for(int i=prior_len/2;i>=0;--i)
		min_heapify(i);
}

prior_node*extract_min()
{
	build_heap();  //the min node is now at index 0;
	prior_node*temp=prior_q[0].ptr;
	prior_q[0].ptr=prior_q[prior_len-1].ptr;
	prior_q[prior_len-1].ptr=temp;
	--prior_len;
	return prior_q[prior_len].ptr;
}

int pos_in_q(int val)
{
	for(int i=0;i<n;++i)
		if((prior_q[i].ptr)->node_val == val)
			return i;
}

void insert(adj_node **front, adj_node **rear, int val)
{            
	adj_node *newptr=CreateNewAdjNode(val);
	if(*front==NULL)
		*front=*rear=newptr;
	else
	{
		(*rear)->ptr=newptr;
		*rear=newptr;
	}
}

int prims()
{
	int sum=0;	
	prior_len=n;
	prior_q=(prior_q_ele*)calloc(n,sizeof(prior_q_ele));
	create_prior_q();

	int pos;
	prior_node*u;
	adj_node *v;
	for(int i=0;i<n;++i)   
	{
		u=extract_min();        

		v=adj_list[u->node_val].front;  
		while(v!=NULL)              
		{
			pos=pos_in_q(v->node_val);          
			if(pos<prior_len && v->wt < (prior_q[pos].ptr)->key)      
			{

				(prior_q[pos].ptr)->p=u;
				(prior_q[pos].ptr)->key=v->wt;
				insert(&soln_list[u->node_val].front, &soln_list[u->node_val].rear, v->node_val);

			}
			v=v->ptr;	
		}
	}
	for(int i=0;i<n;++i)
		sum+=prior_q[i].ptr->key;
	return sum;
}

int main()
{
	int num, m, sum, i;
	char ch;

	cout<<"\nEnter number of vertices : \n";
	cin>>n;

	adj_list=(adj_list_elem*)calloc(n,sizeof(adj_list_elem));
	soln_list=(adj_list_elem*)calloc(n,sizeof(adj_list_elem));
	create_adj_list();

	cout<<"\nEnter adjacency list for each vertex : \n";
	getchar();
	for (i=0;i<n;++i)
	{
		num=0,m=1;
		while((ch=getchar())!='\n')
		{
			m=0;
			if(ch==' ')
			{
				insert(&adj_list[i].front,&adj_list[i].rear,num);
				num =0;
			}
			else
				num=num*10+ch-'0';
		}
		if(!m)
		{
			insert(&adj_list[i].front,&adj_list[i].rear,num);
		}
	}

	adj_node*x;
	cout<<"\nEnter weights for each edge : \n";
	for(i=0;i<n;++i)
	{
		x=adj_list[i].front;
		while(x!=NULL)
		{
			scanf("%d",&num);
			x->wt=num;
			x=x->ptr;
		}
	}
	sum = prims();
    cout<<"\nSum of weights in MST : "<<sum;
	cout<<"\nMST - adjacency list : ";
	for(i=0; i<n; ++i)
	{
		adj_node *p;
		p = soln_list[i].front;
		cout<<"\n"<<i<<"->";
		while(p!= NULL)
		{
			cout<<p->node_val;
			p = p->ptr;
			if(p!=NULL)
				cout<<",";
		}
	}
	cout<<"\n";
	return 0;
}