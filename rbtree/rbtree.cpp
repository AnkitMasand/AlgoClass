#include<iostream>
#include<queue>

using namespace std;

enum color { RED, BLACK};

typedef struct Node{
	enum color color;
	int label;
	Node *left, *right, *parent;
	Node(int val){
		label=val;
		color=RED;
		left=right=parent=NULL;
	}
};

class RBTree{
	Node *root;
   public:
	RBTree(Node *r){
		root=r;
		root->color=BLACK;
	}
	RBTree(){
		root=NULL;
	}
	Node* insert(Node*,int);
	Node* grandparent(Node *c);
	//Node* sibling(Node *c);
	Node* uncle(Node *c);
	Node* doublered(Node *c);
	void levelorder();
	void insertt(int);
	void insert_n(int);
	void del(int);
};

void RBTree::levelorder(){
	queue<Node*> nodes;
	Node *r=root;
	nodes.push(r);
	while(!nodes.empty()){
		r=nodes.front();
		cout<<r->label<<":"<<r->color<<endl;
		nodes.pop();
		if(r->left!=NULL)
			nodes.push(r->left);
		if(r->right!=NULL)
			nodes.push(r->right);
	}	
}

Node* RBTree::grandparent(Node *c){
	return c->parent->parent;
}

Node* RBTree::uncle(Node *c){
	Node *g=grandparent(c);
	if(g->left==c->parent)
		return g->right;
	else
		return g->left;
}
/*
void RBTree::insertt(int val){
	root=insert(root,val);
}
*/
void RBTree::insert_n(int val){
	Node *r=root;
	Node *p=r;
	while(r!=NULL){
		cout<<r->label<<":"<<r->color<<" ";
		if(r->label <val){
			p=r;
			r=r->right;
		}
		else{
			p=r;
			r=r->left;
		}
	}
	if(r==NULL){
		r=new Node(val);
		r->parent=p;
		if(p->label <val)
			p->right=r;
		else
			p->left=r;
	}
	while(r->color==r->parent->color && r->color==RED){
		cout<<"double red on:"<<r->label<<" "<<r->parent->label<<" "<<r->parent->parent->label<<endl;
		Node *prev_gp=grandparent(r);
		if(prev_gp->parent!=NULL && prev_gp->parent->right==prev_gp)
		{
			prev_gp->parent->right=doublered(r);
			r=prev_gp->parent->right;
		}
		else if(prev_gp->parent!=NULL)
		{
			prev_gp->parent->left=doublered(r);
			r=prev_gp->parent->left;
		}
		else
		{
			root=doublered(r);
			root->color=BLACK;
			break;
		}
		/*if(r->parent==NULL)
		{
			root=r;
			root->color=BLACK;
			cout<<"Root is:"<<root->label<<endl;
			break;
		}*/
	}
}
/*
Node* RBTree::insert(Node *r,int val){
	Node c(val);
	if(r==NULL){
		r=new Node(val);
		return r;
	}
	if(r->label < val){
		Node *n=insert(r->right,val);
		n->parent=r;
		r->right=n;
		cout<<n->color<<" "<<r->color<<endl;
		if(r->color==n->color && r->color==RED){
			r=doublered(n);
			//r=r->right;
		}
		return r;	
	}	
	if(r->label >= val){
		Node *n=insert(r->left,val);
		n->parent=r;
		r->left=n;
		cout<<n->color<<" "<<r->color<<endl;
		if(r->color==n->color && r->color==RED){
			r=doublered(n);
			//r=r->left;
		}
		return r;
	}
}
*/
Node* RBTree::doublered(Node *X){
	//cout<<"double red :"<<endl;
	//To return the grandparent to X after rotations
	Node *u=uncle(X);
	Node *g=grandparent(X);
	cout<<g->label<<" "<<X->label<<endl;
	/*if(g==NULL)
	{
		root=g;
		root->color=BLACK;
		return X->parent;
	}*/
	if(u==NULL || u->color==BLACK){
		if(X->parent->right==X){
			//ZIG ZAG
			X->parent->right=X->left;
			g->left=X->right;
			X->left=X->parent;
			X->right=g;
			X->parent->parent=X;
			X->parent=g->parent;
			g->parent=X;
			X->color=BLACK;
			X->right->color=RED;
			X->left->color=RED;
			cout<<X->label<<" "<<X->left->label<<" "<<X->right->label<<endl;
			return X;			
		}
		else{
			//ZIG ZIG
			g->left=X->parent->right;
			X->parent->parent=g->parent;
			X->parent->right=g;
			g->parent=X->parent;
			X->parent->color=BLACK;
			g->color=RED;
			return X->parent;
		}
	}
	if( u->color==RED){
		cout<<u->label<<endl;
		u->color=BLACK;
		X->parent->color=BLACK;
		g->color=RED;
		X->color=RED;
		return X->parent->parent;
	}
}

int main(){
	cout<<"Value of root:";
	int r;
	cin>>r;
	RBTree Rb(new Node(r));	
	cout<<"No of nodes:"<<endl;
	int n;
	cin>>n;
	int val;
	for(int i=0;i<n;i++)
	{
		cin>>val;
		Rb.insert_n(val);
	}
	cout<<"Over:";
	cin>>val;
	Rb.levelorder();
	return 0;
}
