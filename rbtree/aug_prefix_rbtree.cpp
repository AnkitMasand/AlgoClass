#include<iostream>
#include<queue>

using namespace std;

enum color { RED, BLACK};

typedef struct Node{
	enum color color;
	int label;
	int nodes_rooted;
	Node *left, *right, *parent;
	Node(int val){
		label=val;
		color=RED;
		left=right=parent=NULL;
		nodes_rooted=1;
	}
};

class RBTree{
	Node *root;
   public:
	RBTree(Node *r){
		root=r;
		root->color=BLACK;
		root->nodes_rooted=1;
	}
	RBTree(){
		root=NULL;
	}
	void search(int);
	Node* grandparent(Node *c);
	Node* sibling(Node *c);
	Node* uncle(Node *c);
	Node* doublered(Node *c);
	void levelorder();
	void insert_n(int);
	void del(int);
	void del(Node*);
	void doubleblack(Node*,Node*,Node*);
};

void RBTree::search(int val){
	Node *r=root;
	while(r!=NULL){
		if(r->label > val){
			r=r->left;
		}
		else if(r->label < val){
			r=r->right;
		}
		else{
			break;	
		}
	}
	if(r==NULL){
		cout<<"Element not found!"<<endl;
		return;
	}
	else
		cout<<"element present!"<<endl;
}

void RBTree::levelorder(){
	queue<Node*> nodes;
	Node *r=root;
	nodes.push(r);
	while(!nodes.empty()){
		r=nodes.front();
		cout<<r->label<<":"<<r->color<<":"<<r->nodes_rooted<<"->"<<r->nodes_rooted<<endl;
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
void RBTree::insert_n(int val){
	Node *r=root;
	Node *p=r;
	int no=1;
	while(r!=NULL){
		cout<<r->label<<":"<<r->color<<" ";
		r->nodes_rooted+=1;
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
			r=prev_gp->left;
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
			r->nodes_rooted-=1;
			r=r->left;
		}
		else if(r->label < val){
			r->nodes_rooted-=1;
			r=r->right;
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
				x->nodes_rooted-=1;
				x=x->right;
			}
			cout<<"elem changedd to :"<<x->label<<endl;
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
			if(c->parent->left==c)
				c->parent->left=NULL;
			else
				c->parent->right=NULL;			
			delete c;
			return;
		}	
		else{
			if(g==NULL){
				doubleblack(c->right,c->parent,s);
				delete c;
				return;
			}
			else{
				if(g->left==c->parent)
					doubleblack(c->right,c->parent,s);
				else
					doubleblack(c->right,c->parent,s);
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
				doubleblack(x,c->parent,s);
				delete c;
				return;
			}
			else{
				if(g->left==c->parent)
					doubleblack(x,c->parent,s);
				else
					doubleblack(x,c->parent,s);
				delete c;
				return;
			}
		}
	}
}
//As double black prob is coz c was black, so even u has to exist as if it 
//does not exist, black height will not be balanced.
void RBTree::doubleblack(Node *x, Node *p, Node *s){
	cout<<"sibling:"<<s->label<<endl;
	if(s->color==RED)	//case 1
	{
		//both children black of uncle have to exist
		if(p->right==s){
			p->left=x;
			p->right=s->left;
			s->left=p;
			p->right->parent=p;
			s->parent=p->parent;
			if(p->parent!=NULL && p->parent->left==p)
				p->parent->left=s;
			else if(p->parent!=NULL)
				p->parent->right=s;
			else{
				root=s;
				root->color=BLACK;
			}
			p->parent=s;
			p->nodes_rooted=p->right->nodes_rooted;
			if(x!=NULL)	
				p->nodes_rooted+=x->nodes_rooted;
			p->nodes_rooted+=1;
			s->nodes_rooted=s->right->nodes_rooted;	
			s->nodes_rooted+=p->nodes_rooted;
			s->nodes_rooted+=1;
			s->color=BLACK;
			p->color=RED;
			doubleblack(x,p,p->right);
		}
		else if(p->left==s){
			p->right=x;
			p->left=s->right;
			s->right=p;
			p->left->parent=p;
			s->parent=p->parent;
			if(p->parent!=NULL && p->parent->left==p)
				p->parent->left=s;
			else if(p->parent!=NULL)
				p->parent->right=s;
			else{
				root=s;
				root->color=BLACK;
			}
			p->parent=s;
			p->nodes_rooted=p->left->nodes_rooted;
			if(x!=NULL)	
				p->nodes_rooted+=x->nodes_rooted;
			p->nodes_rooted+=1;
			s->nodes_rooted=s->left->nodes_rooted;	
			s->nodes_rooted+=p->nodes_rooted;
			s->nodes_rooted+=1;
			s->color=BLACK;
			p->color=RED;
			doubleblack(x,p,p->left);
		}
	}	
	else if(s->color==BLACK){
		if(p->left==s)
			p->right=x;
		else
			p->left=x;
		if(s->right==s->left)	//no child to sibling
		{
			if(x!=NULL)
				x->color=BLACK;
			s->color=RED;
			if(p->parent==NULL){
				root=p;
				root->color=BLACK;
				if(x!=NULL)
					x->color=RED;
			}
			else if(p->color==BLACK){
				doubleblack(p,p->parent,sibling(p));
			}
			else
				p->color=BLACK;
		}
		else if((s->right!=NULL && s->right->color==RED) || (s->left!=NULL && s->left->color==RED))	//case 3
		{
			if(x!=NULL)
				x->color=BLACK;
			if(p->right==s){
				p->right=s->left;
				s->left=p;
				s->right->color=BLACK;
				s->color=p->color;
				p->color=BLACK;
				if(p->parent==NULL){
					root=s;
					root->color=BLACK;
					root->parent=NULL;
				}
				else if(p->parent->left==p){
					p->parent->left=s;
					s->parent=p->parent;
				}
				else{
					p->parent->right=s;
					s->parent=p->parent;
				}
				p->parent=s;
				if(p->right!=NULL)				
					p->nodes_rooted=p->right->nodes_rooted;
				else
					p->nodes_rooted=0;
				if(x!=NULL)	
					p->nodes_rooted+=x->nodes_rooted;
				p->nodes_rooted+=1;
				if(s->right!=NULL)
					s->nodes_rooted=s->right->nodes_rooted;	
				else
					s->nodes_rooted=0;
				s->nodes_rooted+=p->nodes_rooted;
				s->nodes_rooted+=1;
			}
			else{
				p->left=s->right;
				s->right=p;
				s->left->color=BLACK;
				s->color=p->color;
				p->color=BLACK;
				if(p->parent==NULL){
					root=s;
					root->color=BLACK;
					root->parent=NULL;
				}
				else if(p->parent->left==p){
					p->parent->left=s;
					s->parent=p->parent;
				}
				else{
					p->parent->right=s;
					s->parent=p->parent;
				}
				p->parent=s;	
				if(p->right!=NULL)				
					p->nodes_rooted=p->right->nodes_rooted;
				else
					p->nodes_rooted=0;
				if(x!=NULL)	
					p->nodes_rooted+=x->nodes_rooted;
				p->nodes_rooted+=1;
				if(s->right!=NULL)
					s->nodes_rooted=s->right->nodes_rooted;	
				else
					s->nodes_rooted=0;
				s->nodes_rooted+=p->nodes_rooted;
				s->nodes_rooted+=1;
			}	
		}
		else	//case 2
		{
			if(x!=NULL)
				x->color=BLACK;
			s->color=RED;
			if(p->color==BLACK && p->parent!=NULL)	
				doubleblack(p,p->parent,sibling(p));
			else if(p->parent==NULL)
				return;
			else
				p->color=BLACK;
		}
	}
	return;
}

Node* RBTree::doublered(Node *X){
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
			X->parent->nodes_rooted-=1;
			g->left=X->right;
			X->left=X->parent;
			X->right=g;
			X->parent->parent=X;
			X->parent=g->parent;
			g->parent=X;
			X->color=BLACK;
			X->right->color=RED;
			X->left->color=RED;
			if(g->left!=NULL)
				g->nodes_rooted=g->left->nodes_rooted;
			else
				g->nodes_rooted=0;
			if(g->right!=NULL)
				g->nodes_rooted+=g->right->nodes_rooted;
			g->nodes_rooted+=1;
			if(X->left!=NULL)
				X->nodes_rooted=X->left->nodes_rooted;
			else
				X->nodes_rooted=0;
			if(X->right!=NULL)
				X->nodes_rooted+=X->right->nodes_rooted;
			X->nodes_rooted+=1;
			cout<<X->label<<" "<<X->left->label<<" "<<X->right->label<<endl;
			return X;			
		}
		else if(X->parent->left==X && g->right==X->parent){
			//ZIG ZAG
			X->parent->left=X->right;
			X->parent->nodes_rooted-=1;
			g->right=X->left;
			X->right=X->parent;
			X->left=g;
			X->parent->parent=X;
			X->parent=g->parent;
			g->parent=X;
			X->color=BLACK;
			X->right->color=RED;
			X->left->color=RED;
			if(g->left!=NULL)
				g->nodes_rooted=g->left->nodes_rooted;
			else
				g->nodes_rooted=0;
			if(g->right!=NULL)
				g->nodes_rooted+=g->right->nodes_rooted;
			g->nodes_rooted+=1;
			if(X->left!=NULL)
				X->nodes_rooted=X->left->nodes_rooted;
			else
				X->nodes_rooted=0;
			if(X->right!=NULL)
				X->nodes_rooted+=X->right->nodes_rooted;
			X->nodes_rooted+=1;
			cout<<X->label<<" "<<X->left->label<<" "<<X->right->label<<endl;
			return X;			
		}
		else if(g->left==X->parent){
			//ZIG ZIG
			g->left=X->parent->right;
			if(X->parent->right!=NULL)
				X->parent->right->parent=g;
			X->parent->parent=g->parent;
			X->parent->right=g;
			g->parent=X->parent;
			X->parent->color=BLACK;
			g->color=RED;
			if(g->left!=NULL)
				g->nodes_rooted=g->left->nodes_rooted;
			else
				g->nodes_rooted=0;
			if(g->right!=NULL)
				g->nodes_rooted+=g->right->nodes_rooted;
			g->nodes_rooted+=1;
			if(X->parent->left!=NULL)
				X->parent->nodes_rooted=X->parent->left->nodes_rooted;
			else
				X->parent->nodes_rooted=0;
			if(X->parent->right!=NULL)
				X->parent->nodes_rooted+=X->parent->right->nodes_rooted;
			X->parent->nodes_rooted+=1;
			return X->parent;
		}
		else if(g->right==X->parent){
			//ZIG ZIG
			g->right=X->parent->left;
			if(X->parent->left!=NULL)
				X->parent->left->parent=g;
			X->parent->parent=g->parent;
			X->parent->left=g;
			g->parent=X->parent;
			X->parent->color=BLACK;
			g->color=RED;
			if(g->left!=NULL)
				g->nodes_rooted=g->left->nodes_rooted;
			else
				g->nodes_rooted=0;
			if(g->right!=NULL)
				g->nodes_rooted+=g->right->nodes_rooted;
			g->nodes_rooted+=1;
			if(X->parent->left!=NULL)
				X->parent->nodes_rooted=X->parent->left->nodes_rooted;
			else
				X->parent->nodes_rooted=0;
			if(X->parent->right!=NULL)
				X->parent->nodes_rooted+=X->parent->right->nodes_rooted;
			X->parent->nodes_rooted+=1;
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
		cout<<endl<<"node:";
		cin>>val;
		Rb.insert_n(val);
		cout<<"levelord:";
		Rb.levelorder();
	}
	cout<<"Over:";
	cin>>val;
	Rb.levelorder();
	cout<<endl<<"enter nodes to delete:"<<endl;
	for(int i=0;i<3;i++){
		cin>>val;
		Rb.del(val);
		Rb.levelorder();
	}
	cout<<"Search key:"<<endl;
	cin>>val;
	Rb.search(val);
	return 0;
}
