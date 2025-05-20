#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
struct NODE
{
    int key;
    NODE *p_left;
    NODE *p_right;
};
// Tạo Node mới
NODE *createNode(int data)
{
    NODE *p = new NODE();
    p->key = data;
    p->p_left = NULL;
    p->p_right = NULL;
    return p;
}
// Duyệt pre-order
vector<int> NLR(NODE *pRoot)
{
    vector<int> arr;
    // tree rỗng
    if (pRoot == NULL) return arr;
    // tạo stack
    stack<NODE*> s;
    // đưa pRoot vào stack
    s.push(pRoot);
    while (!s.empty())
    {
        NODE* cur = s.top(); s.pop();
        arr.push_back(cur->key);
        // đưa con phải vào trước vì stack LIFO;
        if (cur->p_right) s.push(cur->p_right);
        if (cur->p_left) s.push(cur->p_left);
    }
    return arr;
}
// Duyệt In-order
// đưa phần tử pRoot vào stack rồi các phần tử trái vào stack
// lấy ra từ stack thì sẽ duyệt trái trước rồi đến pRoot
// rồi duyệt cây bên phải
vector<int> LNR(NODE *pRoot)
{
    vector<int> arr;
    if (pRoot == NULL) return arr;
    stack<NODE*> s;
    NODE* cur = pRoot;
    while (cur != NULL || !s.empty())
    {
        while (cur != NULL)
        {
            s.push(cur);
            cur = cur->p_left;
        }
        cur = s.top(); s.pop();
        arr.push_back(cur->key);
        cur = cur ->p_right;
    }
    return arr;
}
// duyệt Post-order
// đưa pRoot vào stack1 rồi đưa phần tử trái vào stack1 rồi phần tử phải vào stack1 
// đưa top của stack1 qua stack2 trong vòng while khi đó stack2 sẽ lưu phần tử pRoot, pt phải, pt trái
// lấy ra từ stack2 sẽ được Left-Right-Node
vector<int> LRN(NODE* pRoot) {
    vector<int> arr;
    if (pRoot == NULL) return arr;

    stack<NODE*> s1, s2;
    s1.push(pRoot);

    while (!s1.empty()) {
        NODE* cur = s1.top(); s1.pop();
        s2.push(cur);

        if (cur->p_left) s1.push(cur->p_left);
        if (cur->p_right) s1.push(cur->p_right);
    }

    while (!s2.empty()) {
        arr.push_back(s2.top()->key);
        s2.pop();
    }

    return arr;
}
// Duyệt DFS
vector<vector<int>> LevelOrder(NODE* pRoot)
{
    vector<vector<int>> arr;
    if (pRoot == NULL) return arr;
    queue<NODE*> q;
    q.push(pRoot);
    // đưa từng hàng vào queue
    while (!q.empty())
    {
        int l_size = q.size();
        vector<int> l;
        for (int i = 0; i < l_size; i++)
        {
            NODE* cur = q.front(); q.pop();
            l.push_back(cur->key);
            if (cur->p_left) q.push(cur->p_left);
            if (cur->p_right) q.push(cur->p_right);
        }
        arr.push_back(l);
    }
    return arr;
}
// đếm node
int countNode(NODE* pRoot)
{
    vector<int> arr = NLR(pRoot);
    int count = arr.size();//dếm số phần tử vector
    return count;
}

int sumNode(NODE* pRoot)
{
    if (pRoot == NULL) return 0;
    //tổng cây con trái và cây con phải và nút gốc
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}
// tìm node có giá trị cho trước
NODE* findNode(NODE* root, int value) {
    if (root == NULL) return NULL;
    if (root->key == value) return root;
    
    NODE* left = findNode(root->p_left, value);
    if (left != NULL) return left;

    return findNode(root->p_right, value);
}
// tính độ cao node 
int height(NODE* root) {
    if (root == NULL) return -1;
    int left = height(root->p_left);
    int right = height(root->p_right);
    return 1 + max(left, right);
}
// tính độ cao của node có giá trị cho trước
heightNode(NODE* pRoot, int value)
{
    if (pRoot == NULL) return -1;
    NODE* res = findNode(pRoot, value);
    if (res == NULL) return -1;
    return height(res);
}
//tính bậc của node
int Level(NODE* pRoot, NODE* p)
{
    if (pRoot == NULL) return -1;
    if (p == pRoot) return 0;
    int level_left = Level(pRoot->p_left, p);
    if (level_left >= 0) return 1 + level_left;
    int level_right = Level(pRoot->p_right, p);
    if (level_right >= 0) return 1 + level_right;
    return -1;
}
// đếm số node lá
int countLeaf(NODE* pRoot)
{
    if (pRoot == NULL) return 0;
    if (!pRoot->p_left && !pRoot->p_right) return 1;//node lá
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}
