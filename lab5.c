#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct tree{
	int key;
	struct tree* left;
	struct tree* right;
};

struct tree* Add(struct tree* t, int x){
	if(t==NULL){
		t = (struct tree*)malloc(sizeof(struct tree));
		t->key = x;
		t->left = NULL;
		t->right = NULL;
	}
	else{
		if (x<t->key)
		    t->left = Add(t->left, x);
		else if (x> t->key)
		    t->right = Add(t->right,x);
		}
	return t;
}

struct tree* del1(struct tree* q, struct tree *p)
{
	struct tree *r;

	if (q->right!=NULL)
	  r=del1(q->right,p);
	else
	{
		p->key=q->key;
		r=q;
		q=q->left;
	}
	return r;
}

struct tree* del(struct tree *t, int x){
  struct tree *p;

  if (t!=NULL) {
	if (x<t->key)
	   t->left=del(t->left,x);
	else if (x>t->key)
		t->right=del(t->right,x);
	else{
		p=t;
		if (p->right==NULL)
		   t=p->left;
		else if (p->left==NULL)
			t=p->right;
		else
			p=del1(p->left,p);
		free(p);
		}
        
	}
  return t;
}


void buildCrossReferences(struct tree* t){
	if(t == NULL)
	    return;
	printf("%-10d|", t->key);
	if(t->left != NULL)
	    printf("%-10d|", t->left->key);
	else
	    printf("NULL      |");
	if(t->right != NULL)
	    printf("%-10d\n", t->right->key);
	else
	    printf("NULL\n");
	buildCrossReferences(t->left);
	buildCrossReferences(t->right);
}

int main(){
	struct tree* t = (struct tree*)malloc(sizeof(struct tree));
	t = NULL;
	t = Add(t,10);
	t = Add(t,1);
	t = Add(t,17);
	t = Add(t,21);
	t = Add(t,30);
	t = Add(t,50);
	t = Add(t,60);
	t = Add(t,7);
	t = Add(t,2002);
	t = del(t,17);
	printf("Root      | Left     | Right\n");
	buildCrossReferences(t);
	free(t);
	return 0;	
}





