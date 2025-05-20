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
// tìm node có giá trị cho trước
NODE* Search(NODE* pRoot, int x)
{
    if (pRoot == NULL) return NULL;//cây rỗng
    if (pRoot->key == x) return pRoot;//pRoot là node cần tìm
    if (pRoot->key > x)//node cần tìm có thể nằm ở cây con bên trái
    {
        return Search(pRoot->p_left, x);
    }
    else
    {
        return Search(pRoot->p_right, x);//node cần tìm có thể nằm ở cây con bên phải
    }
    return NULL;//không tìm được
}
// tạo node từ giá trị cho trước
NODE *createNode(int data)
{
    NODE *p = new NODE();
    p->key = data;
    p->p_left = NULL;
    p->p_right = NULL;
    return p;
}
// chèn node
void Insert(NODE* &pRoot, int x)
{
    NODE* p = createNode(x);
    if (pRoot == NULL)//cây rỗng
    {
        pRoot = p;
        pRoot->p_left = pRoot->p_right = NULL;
    }
    if (x < pRoot->key)// cần chèn ở cây con trái
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);// cần chèn ở cây con phải
}
// tìm node có giá trị cho trước, trả về NULL nếu không tìm được
NODE* findNode(NODE* root, int value) {
    if (root == NULL) return NULL;
    if (root->key == value) return root;
    
    NODE* left = findNode(root->p_left, value);
    if (left != NULL) return left;

    return findNode(root->p_right, value);
}
// xóa node
void Remove(NODE* &pRoot, int x)
{
    if (pRoot == NULL) return;// cây rỗng

    if (x < pRoot->key)
    {
        Remove(pRoot->p_left, x);// phần tử cần xóa ở cây con trái
    }
    else if (x > pRoot->key)
    {
        Remove(pRoot->p_right, x);//phần tử cần xóa ở cây con phải
    }
    else // Tìm thấy node có key == x
    {
        // Trường hợp node không có con
        if (pRoot->p_left == NULL && pRoot->p_right == NULL)
        {
            delete pRoot;
            pRoot = NULL;
        }
        // Chỉ có con phải
        else if (pRoot->p_left == NULL)
        {
            NODE* temp = pRoot;
            pRoot = pRoot->p_right;
            delete temp;
        }
        // Chỉ có con trái
        else if (pRoot->p_right == NULL)
        {
            NODE* temp = pRoot;
            pRoot = pRoot->p_left;
            delete temp;
        }
        else // Có cả 2 con
        {
            NODE* temp = pRoot->p_left;
            while (temp->p_right != NULL)
                temp = temp->p_right;

            pRoot->key = temp->key; // Gán giá trị lớn nhất bên trái
            Remove(pRoot->p_left, temp->key); // Xóa node trùng đó
        }
    }
}
NODE* createTree(int a[], int n)
{
    NODE* pRoot = createNode(a[0]);//tạo nút gốc
    for (int i = 1; i < n; i++)
    {
        Insert(pRoot, a[i]);//chèn các nút khác vào
    }
    return pRoot;
}

void removeTree(NODE* &pRoot)
{
    if (pRoot == NULL) return;//cây rỗng không cần xóa

    removeTree(pRoot->p_left);//xóa cây con trái
    removeTree(pRoot->p_right);//xóa cây con phải

    delete pRoot;//xóa nút gốc
    pRoot = NULL;
}

int Height(NODE* pRoot)//tính chiều cao
{
    if (pRoot == NULL) return -1; // Cây rỗng có chiều cao -1 (đếm theo cạnh)
    if (!pRoot->p_left && !pRoot->p_right) return 0;
    int left = Height(pRoot->p_left);
    int right = Height(pRoot->p_right);

    return 1 + max(left, right);
}
int countLess(NODE* pRoot, int x)
{
    if (pRoot == NULL) return 0;
    if (pRoot->key >= x)//node nhỏ hơn x nằm ở cây có trái
    {
        return countLess(pRoot->p_left, x);
    }
    return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);//có thể ở cả hai cây con
}
int countGreater(NODE* pRoot, int x)
{
    if (pRoot == NULL) return 0;
    if (pRoot->key <= x)//node lớn hơn x ở cây con phải
    {
        return countGreater(pRoot->p_right, x);
    }
    return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);// có thể ở cả 2 cây con
}
// kiểm tra có thuộc khoảng giá trị không
bool isSubtreeLesser(NODE* root, int value) {
    if (root == NULL) return true;
    if (root->key >= value) return false;
    return isSubtreeLesser(root->p_left, value) && 
           isSubtreeLesser(root->p_right, value);
}
bool isSubtreeGreater(NODE* root, int value) {
    if (root == NULL) return true;
    if (root->key <= value) return false;
    return isSubtreeGreater(root->p_left, value) && 
           isSubtreeGreater(root->p_right, value);
}
//là cây BST khi cây con trái và phải đều là cây BST
bool isBST(NODE* pRoot) {
    if (pRoot == NULL) return true;
    // kiểm tra có đúng là left_sub_tree < pRoot < right_sub_tree
    if (!isSubtreeLesser(pRoot->p_left, pRoot->key) ||
        !isSubtreeGreater(pRoot->p_right, pRoot->key))
        return false;
    
    return isBST(pRoot->p_left) && isBST(pRoot->p_right);
}
// kiểm tra cây có full node không
bool isFullTree(NODE* root) {
    if (root == NULL) return true;
    
    // Nếu chỉ có 1 con -> không phải Full Tree
    if ((root->p_left == NULL && root->p_right != NULL) ||
        (root->p_left != NULL && root->p_right == NULL))
        return false;
    
    return isFullTree(root->p_left) && isFullTree(root->p_right);
}
bool isFullBST(NODE* pRoot) {
    return isBST(pRoot) && isFullTree(pRoot);
}