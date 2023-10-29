#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<math.h>
struct Stack {
    int top;
    unsigned capacity;
    double* array;
};

//Function creates a new stack
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (double*)malloc(stack->capacity * sizeof(double));
    return stack;
}

//Function to check if the stack is empty
bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

//Function checks stack is full
bool isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

//Push an element
void push(struct Stack* stack, double item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}
// Pop an element
double pop(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char x)
{
	if (x == '+' || x == '-')
		return 1 ;
	if (x == '*' || x == '/' )
		return 2;
}
char* infixtoPostfix(char*exp){
	struct Stack* stack = createStack(strlen(exp));	
	char* new_exp = (char*)malloc((strlen(exp)+1)*sizeof(char));
	int i,j;
	j=0;
	for(i=0;i<strlen(exp);i++){		
		while(isdigit(exp[i])){
		    new_exp[j++]= exp[i];
		    i++;
		}
		if(isOperator(exp[i])){
			while(!isEmpty(stack) && precedence(exp[i])<=precedence(stack->array[stack->top])){
				new_exp[j++]= pop(stack);
			}
			push(stack,exp[i]);
			if(isdigit(new_exp[j-1])){
				new_exp[j++]=' ';
			}			
		}
	}	
	while(!isEmpty(stack)){
		new_exp[j++] = pop(stack);
	}
	new_exp[j]='\0';
	return new_exp;
} 

double evaluateExp(char* exp) {
	char* new_exp = infixtoPostfix(exp);
    struct Stack* stack = createStack(strlen(new_exp));
    int i ;
    for(i=0;i<strlen(new_exp);i++){   
        if (isdigit(new_exp[i])) {
            int num = 0;
            while (isdigit(new_exp[i])) {
                num = num * 10 + (new_exp[i] - '0');
                i++;
            }
            push(stack, num);
            i--; 
        } else if (isOperator(new_exp[i])) {
            double val1 = pop(stack);
            double val2 = pop(stack);
            switch (new_exp[i]) {
                case '+': push(stack, val2 + val1); break;
                case '-': push(stack, val2 - val1); break;
                case '*': push(stack, val2 * val1); break;
                case '/': push(stack, val2 / val1); break;
            }
        }
    }
    return pop(stack);
}

char* find_expression(char* A, int B, char* current_exp, double current_result, int current_index){
	
	if ((current_index +1)== strlen(A)){
		//printf("%c\n",A[current_index-2]);
		if(current_result == B)
		    return strdup(current_exp);
	    else
	        return NULL;}
	        
	double new_result;
	int i;
	char* result = NULL;
	char operators[] = {'+','-','*','/'};
	char new_exp[100];
	
	for(i=0;i<5;i++){
		
		if(i<4){
            sprintf(new_exp, "%s%c%c", current_exp, operators[i], A[current_index]);
		}else{
            sprintf(new_exp, "%s%c", current_exp, A[current_index]);
		}
	
		new_result = evaluateExp(new_exp);
		result = find_expression(A,B,new_exp,new_result,current_index+1);
        if (result){
        	return result;
		}        	
	}
	return NULL;
	
}
int main(){
	FILE* input_file = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w");
    if (input_file == NULL || output_file == NULL) {
        printf("Error opening file");
        return 1;
    }
    
    char A[100];
    char D[100];
	int B;
	fgets(A,100,input_file);
	fscanf(input_file, "%d", &B);
    fclose(input_file);  
	
	strcpy(D,A);
	D[1]='\0';
	char* result = find_expression(A, B, D, (int)(D - '0'), 1);
	
    char exp[100]= "1+2+3+45+6+78+9";
    printf("%s\n", result);
    if (result != NULL) {
        fputs(result, output_file);
    } else {
        fputs("0\n", output_file);
    }
    fclose(output_file);
	return 0;
}
