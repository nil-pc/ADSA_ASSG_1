//kruskal's algorithm

#include<iostream>
#include<bits/stdc++.h> 
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int n,sum=0,edge;

typedef struct adj_node
{
	int key;
	int wt;
	struct adj_node *ptr;
}adj_node;


typedef struct adj_list_ele
{
	adj_node *start,*rear;
}adj_ele;

adj_ele *adj_list, *soln_list;


typedef struct disj_node
{
	int key;
	struct disj_node *p;
}disjnode;


typedef struct disj_list_elem
{
	disjnode *ptr;
}disjele;

disjele *disj_list;


void create_adj_list()
{
	for(int i=0;i<n;++i)
	{
		adj_list[i].start  = adj_list[i].rear  = NULL;
		soln_list[i].start = soln_list[i].rear = NULL;
	}
}


adj_node* NewAdjNode(int val)
{
	adj_node * newptr=(adj_node*)malloc(sizeof(adj_node));
	if (newptr==NULL)
	{
		printf("Error");
		exit(0);
	}
	newptr->key=val;
	newptr->ptr=NULL;
	return newptr;
}


void insert_linked_list(adj_node **start,adj_node **rear,int val)
{
	adj_node *newptr=NewAdjNode(val);
	if(*start==NULL)
		*start=*rear=newptr;
	else
	{
		(*rear)->ptr=newptr;
		*rear=newptr;
	}
}


void create_disj_list()
{
	for(int i=0;i<n;++i)
	{
		disj_list[i].ptr=NULL;
	}
}

disjnode* CreateDisjNode(int val)
{
	disjnode *newptr=(disjnode*)malloc(sizeof(disjnode));
	if(newptr==NULL)
	{
		printf("Error");
		exit(0);
	}
	newptr->key=val;
	newptr->p=newptr;
	return newptr;
}

struct edge
{
	int u,v;
	int wt;
}*edge_set;


void make_set(int val)
{
	if(disj_list[val].ptr==NULL)
	{
		disjnode *newptr=CreateDisjNode(val);
		disj_list[val].ptr=newptr;
	}
}

int find_set(int val)
{
	disjnode *x = disj_list[val].ptr;
	while(x->p!=x)
		x=x->p;
	return x->key;
}

void union_set(int x,int y)
{
	int x_rep=find_set(x);
	int y_rep=find_set(y);
	disj_list[y_rep].ptr->p=disj_list[x_rep].ptr;
}

void sort()
{
	int min;
	struct edge temp;
	for(int i=0;i<edge;++i)
	{
		min =i;
		for(int j=i+1;j<edge;++j)
			if(edge_set[j].wt<edge_set[min].wt)
				min=j;
		temp=edge_set[i];
		edge_set[i]=edge_set[min];
		edge_set[min]=temp;
	}
}
void mst_kruskal()
{
	int i, u, v;
	for(i=0;i<n;++i)
		make_set(i);
	sort();
	for(i=0;i<edge;++i)
	{
		u = edge_set[i].u;
		v = edge_set[i].v;

		if(find_set(u)!=find_set(v))
		{
			sum+=edge_set[i].wt;
			insert_linked_list(&soln_list[u].start, &soln_list[u].rear, v);		
			union_set(u, v);
		}
	}
}

int main()
{
	char ch;
	int nw,val,i;

	cout<<"\nEnter number of vertices : \n";
	cin>>n;

	adj_list=(adj_ele*)calloc(n,sizeof(adj_ele));
	soln_list=(adj_ele*)calloc(n,sizeof(adj_ele));
	create_adj_list();
	//for(i=0;i<1000;i++);
	disj_list=(disjele*)calloc(n,sizeof(disjele));
	create_disj_list();

	edge_set=(struct edge*)calloc(n*n,sizeof(struct edge));

	cout<<"\nEnter adjacency list for each vertex : \n";
    getchar();
	edge = 0;
	for(i=0;i<n;i++)
	{
		val=0,nw=1;
		while((ch=getchar())!='\n')
		{
			nw=0;
			if(ch==' ')
			{
				insert_linked_list(&adj_list[i].start,&adj_list[i].rear,val);
				edge_set[edge].u=i;
				edge_set[edge].v=val;
				++edge;
				val =0;
			}
			else
				val=val*10+ch-'0';
		}
		if(!nw)
		{
			insert_linked_list(&adj_list[i].start,&adj_list[i].rear,val);
			edge_set[edge].u=i;
			edge_set[edge].v=val;
			++edge;
		}
	}
	//for(i=0;i<1000;i++);
	adj_node *x;
	edge = 0;
	cout<<"\nEnter weights for each edge : \n";
	for(i=0; i<n; ++i)
	{
		x = adj_list[i].start;
		while(x!=NULL)
		{
			cin>>val;
			x->wt=val;
			edge_set[edge++].wt=val;
			x=x->ptr;
		}
	}
	mst_kruskal();
	cout<<"\nSum of MST : "<<sum;
	cout<<"\nMST - adjacency list : ";
	for(i=0; i<n; ++i)
	{
		adj_node *p;
		p = soln_list[i].start;
		cout<<"\n"<<i<<"->";
		while(p!= NULL)
		{
			cout<<p->key<<",";
			p = p->ptr;
		}
		cout<<"|";
	}
	cout<<"\n";
	return 0;
}
