#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
void gotoxy(int x, int y){
	static HANDLE h = NULL;
	if(!h)
	    h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c ={x,y};
	SetConsoleCursorPosition(h,c);
	
}
struct tree{
	int h;
	char ch;
	struct tree *left;
	struct tree *right;
};
struct tree* ReadTree(FILE *f){
	char ch, ch_l, ch_r;
	struct tree *t;
	
	ch=fgetc(f);
	ch_l=fgetc(f);
	ch_r=fgetc(f);
	if (!feof(f)){
		t =(struct tree*)malloc(sizeof(struct tree));
		t->ch = ch;
		t->left = NULL;
		t->right = NULL;
		if(ch_l != '-')
		    t->left = ReadTree(f);
		if (ch_r != '-')
		    t->right = ReadTree(f);
	}
	return t;
}

int CountH(struct tree *t){
	int h_l,h_r,h;
	if(t==NULL) return 0;
	else{
		if(t->left == NULL && t->right == NULL) return 1;
		else {
			h_r = CountH(t->right);
		    h_l = CountH(t->left);
		    if(h_l > h_r)   h = h_l + 1;
		    else h = h_r + 1;
			return h;
		}		
	}
}

void countH_diff(struct tree* t){
	if(t==NULL)
		return;
	int h_l = CountH(t->left);
	int h_r = CountH(t->right);
	t->h = h_l - h_r;
	countH_diff(t->left);
	countH_diff(t->right);	
}

int x = 1;
void PrintTree(struct tree *t, int y){
	if (t!=NULL)
	{
		PrintTree(t->left, y+1);
		gotoxy(x,y);  
		printf("%d",t->h);
		x++;
		PrintTree(t->right, y+1);
	}
}


int main(){
	struct tree *t;
	
	FILE *f = fopen("Tree.txt","r");
	if (f == NULL) {
        printf("Error opening file");
        return 1;
    }
    
	t = ReadTree(f); 
	fclose(f);
	
	countH_diff(t);
	int x = 1; 
    PrintTree(t,0);
    printf("\n\n") ;
	free(t);	
	
	return 0;
}
