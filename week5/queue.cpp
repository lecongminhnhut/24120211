#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct NODE {
    int key ;
    NODE * p_next ;
};
struct Queue {
    NODE * head ;
    NODE * tail ;
};

Queue* initializeQueue();
void enqueue(Queue* &q, int key);
int dequeue(Queue* &q);
int size(Queue* q);
bool isEmpty(Queue* q);

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
Queue* initializeQueue()
{
    Queue* q = new Queue();
    q->head = q->tail = NULL;
    return q;
}
void enqueue(Queue* &q, int key)
{
    NODE* p = CreateNode(key);
    if (q == NULL) {
        q = new Queue; // cấp phát vùng nhớ cho queue nếu nó NULL
        q->head = q->tail = NULL;
    }
    if (q->head == NULL)
    {
        q->head = q->tail = p;
    }
    else
    {
        q->tail->p_next = p;
        q->tail = p;
    }
}
int dequeue(Queue* &q)
{
    if (isEmpty(q))
    {
        cout << "Queue is empty";
        return -1;
    }
    NODE* temp = q->head;
    int value = temp->key;
    q->head = q->head->p_next;
    delete temp;
    return value;
}
int size(Queue* q)
{
    int size = 0;
    NODE* cur = q->head;
    while (cur != NULL)
    {
        size++;
        cur = cur->p_next;
    }
    return 0;
}
bool isEmpty(Queue* q)
{
    if (q == NULL || q->head == NULL)
    {
        return true;
    }
    return false;
}

void printQueue(Queue* q, ofstream& fout)
{
    if (isEmpty(q))
    {
        fout << "EMPTY";
    }
    NODE* temp = q->head;
    while (temp != NULL)
    {
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
    Queue* q = NULL;
    string cmd;
    while (fin >> cmd)
    {
        if (cmd == "init")
        {
            q = initializeQueue();
        }
        else if (cmd == "enqueue")
        {
            int a;
            fin >> a;
            enqueue(q, a);
        }
        else if (cmd == "dequeue")
        {
            if(!isEmpty(q))
                dequeue(q);
        }
        printQueue(q, fout);
    }
    fin.close();
    fout.close();
    return 0;
}