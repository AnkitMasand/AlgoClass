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
	Node* sibling(Node *c);
	Node* uncle(Node *c);
	Node* doublered(Node *c);
	void levelorder();
	void insertt(int);
	void insert_n(int);
	void del(int);
	void del(Node*);
	Node* doubleblack(Node*,Node*,Node*);
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

Node* RBTree::sibling(Node *c){
	if(c->parent->left==c)
		return c->parent->right;
	else
		return c->parent->left;
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
			prev_gp=prev_gp->parent;
			prev_gp->right=doublered(r);
			cout<<prev_gp->label<<"great gp"<<endl;
			r=prev_gp->right;
		}
		else if(prev_gp->parent!=NULL)
		{
			prev_gp=prev_gp->parent;
			prev_gp->left=doublered(r);
			cout<<prev_gp->label<<"great gp"<<endl;
			r=prev_gp->parent->left;
		}
		else
		{
			root=doublered(r);
			root->color=BLACK;
			break;
		}
	}
}

void RBTree::del(int val){
	Node *r=root;
	Node *x;
	while(r!=NULL){
		if(r->label > val){
			r=r->right;
		}
		else if(r->label < val){
			r=r->left;
		}
		else{
			break;	
		}
	}
	if(r==NULL){
		cout<<"Element not found!"<<endl;
		return;
	}
	else{
		if(r->left==r->right)
		{
			del(r);	 //case 0
		}
		else if(r->left==NULL || r->right==NULL){
			del(r);	//case 1
		}	
		else{
			//Both child exist case 3
			//inord predeccsor:
			x=r->left;
			while(x->right!=NULL){
				x=x->left;
			}
			r->label=x->label;
			del(x);
		}
	}
}

void RBTree::del(Node *c){
	if(c==root){
		if(root->left!=NULL)
			root=root->left;
		else if(root->right!=NULL)
			root=root->right;
		else{
			root=NULL;
			return;
		}
		root->color=BLACK;
		return;
	}
	//here onwards, parent exists.
	Node *s=sibling(c);
	Node *g=grandparent(c);
	if(c->right==c->left){
		if(c->color==RED)
		{	
			delete c;
			return;
		}	
		else{
			if(g==NULL){
				root=doubleblack(c->right,c->parent,s);
				delete c;
				return;
			}
			else{
				if(g->left==c->parent)
					g->left=doubleblack(c->right,c->parent,s);
				else
					g->right=doubleblack(c->right,c->parent,s);
				delete c;
				return;
			}
		}
	}
	else{
		if(c->color==RED){
			//No double black needed
			if(c->left!=NULL){
				c->left->parent=c->parent;
				if(c->parent->left==c)
					c->parent->left=c->left;
				else
					c->parent->right=c->left;
				delete c;
				return;
			}
			if(c->right!=NULL){
				c->right->parent=c->parent;
				if(c->parent->left==c)
					c->parent->left=c->right;
				else
					c->parent->right=c->right;
				delete c;
				return;
			}
		}
		else if(c->left!=NULL && c->left->color==RED){
			c->left->parent=c->parent;
			if(c->parent->left==c)
				c->parent->left=c->left;
			else
				c->parent->right=c->left;
			c->left->color=BLACK;
			delete c;
			return;
		}
		else if(c->right!=NULL && c->right->color==RED){
			c->right->parent=c->parent;
			if(c->parent->left==c)
				c->parent->left=c->right;
			else
				c->parent->right=c->right;
			c->right->color=BLACK;
			delete c;
			return;
		}
		else{
			//Need to call double black
			Node *x;
			if(c->right!=NULL)	
				x=c->right;
			else
				x=c->left;
			if(g==NULL){
				root=doubleblack(x,c->parent,s);
				delete c;
				return;
			}
			else{
				if(g->left==c->parent)
					g->left=doubleblack(x,c->parent,s);
				else
					g->right=doubleblack(x,c->parent,s);
				delete c;
				return;
			}
		}
	}
}
//As double black prob is coz c was black, so even u has to exist as if it 
//does not exist, black height will not be balanced.
Node* RBTree::doubleblack(Node *x, Node *p, Node *s){
	if(s->color==RED)	//case 1
	{
		//both children black of uncle have to exist
		if(p->right==s){
			p->right=s->left;
			s->left=p;
			p->right->parent=p;
			p->parent=s;
			s->color=BLACK;
			s->left=doubleblack(x,p,p->right);
			return s;
		}
		else if(p->left==s){
			p->left=s->right;
			s->right=p;
			p->left->parent=p;
			p->parent=s;
			s->color=BLACK;
			s->right=doubleblack(x,p,p->left);
			return s;
		}
	}	
	else if(s->color==BLACK){
		if(s->right==s->left)	//no child to sibling
		{
			if(x!=NULL)
				x->color=BLACK;
			s->color=RED;
			if(p->color==BLACK){
				if(grandparent(p)==NULL)
					return doubleblack(p,p->parent,sibling(p));
				else
				
			}
		}
	}
	return p;
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
		if(X->parent->right==X && g->left==X->parent){
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
		else if(X->parent->left==X && g->right==X->parent){
			//ZIG ZAG
			X->parent->left=X->right;
			g->right=X->left;
			X->right=X->parent;
			X->left=g;
			X->parent->parent=X;
			X->parent=g->parent;
			g->parent=X;
			X->color=BLACK;
			X->right->color=RED;
			X->left->color=RED;
			cout<<X->label<<" "<<X->left->label<<" "<<X->right->label<<endl;
			return X;			
		}
		else if(g->left==X->parent){
			//ZIG ZIG
			g->left=X->parent->right;
			X->parent->parent=g->parent;
			X->parent->right=g;
			g->parent=X->parent;
			X->parent->color=BLACK;
			g->color=RED;
			return X->parent;
		}
		else if(g->right==X->parent){
			//ZIG ZIG
			g->right=X->parent->left;
			X->parent->parent=g->parent;
			X->parent->left=g;
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
