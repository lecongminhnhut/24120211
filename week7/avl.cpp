#include <iostream>
using namespace std;
struct NODE{
int key;
NODE* p_left;
NODE* p_right;
int height;
};
NODE* createNode(int data)
{
    NODE* p = new NODE();
    p->key = data;
    p->p_left = p->p_right = NULL;
    p->height = -1;
    return p;
}
//tính chiều cao
int height(NODE* node)
{
    if (node != NULL) {
        return node->height;
    } 
    else {
        return 0;
    }
}

// Tính hệ số cân bằng
int balanceFactor(NODE* node) {
    return height(node->p_left) - height(node->p_right);
}
// Cập nhật chiều cao node
void updateHeight(NODE* node) {
    int leftHeight = height(node->p_left);
    int rightHeight = height(node->p_right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}


// Quay trái
NODE* rotateLeft(NODE* x) {
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;

    y->p_left = x;
    x->p_right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Quay phải
NODE* rotateRight(NODE* y) {
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;

    x->p_right = y;
    y->p_left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

NODE* balanceTree(NODE* node) {
    if (!node) return NULL;

    updateHeight(node);
    int bf = balanceFactor(node);

    // Trái-trái (LL)
    if (bf > 1 && balanceFactor(node->p_left) >= 0)
        return rotateRight(node);

    // Phải-phải (RR)
    if (bf < -1 && balanceFactor(node->p_right) <= 0)
        return rotateLeft(node);

    // Trái-phải (LR)
    if (bf > 1 && balanceFactor(node->p_left) < 0) {
        node->p_left = rotateLeft(node->p_left);
        return rotateRight(node);
    }

    // Phải-trái (RL)
    if (bf < -1 && balanceFactor(node->p_right) > 0) {
        node->p_right = rotateRight(node->p_right);
        return rotateLeft(node);
    }

    return node;
}
void Insert(NODE* &pRoot, int x) {
    // Chèn node như BST thông thường
    if (!pRoot) {
        pRoot = createNode(x); // Tạo node mới nếu cây rỗng
        return;
    }

    if (x < pRoot->key)
        Insert(pRoot->p_left, x); // Chèn vào cây con trái
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x); // Chèn vào cây con phải
    else
        return; // Bỏ qua nếu key đã tồn tại

    // Cập nhật chiều cao node hiện tại
    updateHeight(pRoot);

    // Cân bằng cây sau khi chèn
    pRoot = balanceTree(pRoot);
}

void Remove(NODE* &pRoot, int x)
{
     if (pRoot == NULL) return;

    if (x < pRoot->key)// có thể ở cây con trái
    {
        Remove(pRoot->p_left, x);
    }
    else if (x > pRoot->key) // có thể ở cây con phải
    {
        Remove(pRoot->p_right, x);
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
    updateHeight(pRoot);//cập nhật lại chiều cao
    pRoot = balanceTree(pRoot);// cân bằng lại cây
}





//phần BST của bst.cpp
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
bool isBST(NODE* pRoot) {
    if (pRoot == NULL) return true;
    
    if (!isSubtreeLesser(pRoot->p_left, pRoot->key) ||
        !isSubtreeGreater(pRoot->p_right, pRoot->key))
        return false;
    
    return isBST(pRoot->p_left) && isBST(pRoot->p_right);
}
// kiểm tra có cân bằng không
bool IsBalanceTree(NODE* pRoot)
{
    if (pRoot == NULL) return true;//cây rỗng cân bằng

    bool isLeftBalanced = IsBalanceTree(pRoot->p_left);// kiểm tra cây con trái
    bool isRightBalanced = IsBalanceTree(pRoot->p_right);// kiểm tra cây con phải
    
    if (!isLeftBalanced || !isRightBalanced)
        return false;

    int bf = balanceFactor(pRoot);
    return bf >= -1 && bf <= 1; // chênh lệch độ cao giữa hai cây con
}
bool isAVL(NODE* pRoot)
{
    return IsBalanceTree(pRoot) && isBST(pRoot);
}
int main()
{
    return 0;
}