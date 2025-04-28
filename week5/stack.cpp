#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct NODE {
    int key ;
    NODE * p_next ;
};
struct Stack {
    NODE * top ;
};

Stack* initializeStack();
void push(Stack* &s, int key);
int pop(Stack* &s);
int size(Stack* s);
bool isEmpty(Stack* s);

NODE* CreateNode(int key)
{
    NODE* p = new NODE();
    if (p == NULL)
    {
        cout << "NOT ENOUGH MEMORY";
        return NULL;
    }
    p->key = key;
    p->p_next = NULL;
    return p;
}

Stack* initializeStack()
{
    Stack* s = new Stack();
    s->top = NULL;
    return s;
}

void push(Stack* &s, int key)
{
    NODE* new_top = CreateNode(key);
    if (s->top == NULL)
    {
        s->top = new_top;
    }
    else
    {
        new_top->p_next = s->top;
        s->top = new_top;
    }
}

int pop(Stack* &s)
{
    if (isEmpty(s))
    {
        cout << "Stack is empty";
        return -1;
    }
    else
    {
        NODE* temp = s->top;
        int value = temp->key;
        s->top = s->top->p_next;
        delete temp;
        return value;
    }
}

int size(Stack* s)
{
    int size = 0;
    NODE* cur = s->top;
    while (cur != NULL)
    {
        size++;
        cur = cur->p_next;
    }
    return size;
}

bool isEmpty(Stack* s)
{
    if (s->top != NULL)
        return false;
    return true;
}

void printStack(Stack* s, ofstream& fout) {
    if (isEmpty(s)) {
        fout << "EMPTY" << endl;
        return;
    }
    Stack* a = initializeStack();
    NODE* cur = s->top;
    while (cur != NULL)
    {
        push(a, cur->key);
        cur = cur->p_next;
    }
    // Duyệt stack và in ra các phần tử
    NODE* temp = a->top;
    while (temp != NULL) {
        fout << temp->key;
        if (temp->p_next != NULL) fout << " ";
        temp = temp->p_next;
    }
    fout << endl;
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    Stack* s = NULL;
    string cmd;
    while (fin >> cmd)
    {
        if (cmd == "init")
        {
            s = initializeStack();
        }
        else if (cmd == "push")
        {
            int a;
            fin >> a;
            push(s, a);
        }
        else if (cmd == "pop")
        {
            if (!isEmpty(s))
            {
                pop(s);
            }
        }
        printStack(s, fout);
    }

    fin.close();
    fout.close();

    return 0;
}

