#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
using namespace std;
const int INF = 1e9;

vector<vector<int>> convertMatrixToList(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
            cerr << "Cannot open file\n";
            return {};
        }

    vector<vector<int>> list;
    string line;

    // Đọc số đỉnh
    getline(fin, line);
    int n = stoi(line);
    list.resize(n);

    // Đọc từng dòng của ma trận kề
    for (int i = 0; i < n; ++i) {
        getline(fin, line);
        stringstream ss(line);
        int value, j = 0;

        // Đếm số đỉnh kề và lưu lại vị trí
        vector<int> l;
        while (ss >> value) {
            if (value == 1) {
                l.push_back(j);
            }
            j++;
        }

        // Lưu: số lượng kề + danh sách đỉnh kề
        vector<int> r;
        r.push_back(l.size());
        for (int v : l) {
            r.push_back(v);
        }
       list[i] = r;
    }
    fin.close();
    return list;
}

vector<vector<int>> convertListToMatrix(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Cannot open file\n";
        return {};
    }

    string line;
    getline(fin, line);
    int n = stoi(line);
    vector<vector<int>> matrix(n, vector<int>(n, 0)); // khởi tạo ma trận n x n toàn 0

    int u = 0; // đỉnh hiện tại
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        int count;
        ss >> count; 
        int v;
        while (ss >> v) {
            matrix[u][v] = 1;
        }
        ++u;
    }
    fin.close();
    return matrix;
}

bool isDirected(const vector<vector<int>> &adjMatrix) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != adjMatrix[j][i]) {
                return true; // có hướng
            }
        }
    }
    return false; // vô hướng
}

int countVertices(const vector<vector<int>> &adjMatrix)
{
    return adjMatrix.size();    
}

int countEdges(const vector<vector<int>> &adjMatrix) {
     int n = adjMatrix.size();
    int count = 0;
    int selfLoops = 0;
    bool isDirected = false;

    // Đếm cạnh và kiểm tra tính có hướng
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] != 0) {
                if (i == j) {
                    selfLoops++; // Đếm riêng self-loop
                    count++;
                } else {
                    count++;
                    if (!isDirected && j > i && adjMatrix[i][j] != adjMatrix[j][i]) {
                        isDirected = true;
                    }
                }
            }
        }
    }

    // Điều chỉnh cho đồ thị vô hướng (không chia đôi self-loop)
    if (!isDirected) {
        count = (count - selfLoops) / 2 + selfLoops;
    }

    return count;
}


vector<int> getIsolatedVertices(const vector<vector<int>> &adjMatrix) {
    int n = adjMatrix.size();
    vector<int> v;

    for (int i = 0; i < n; ++i) {
        bool co = false;
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0) {
                co = true;
                break;
            }
        }
        if (!co) {
            v.push_back(i);
        }
    }

    return v;
}

bool isCompleteGraph(const vector<vector<int>> &adjMatrix) {
    int n = adjMatrix.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                if (adjMatrix[i][j] != 0) return false; // không được có cạnh khuyên
            } else {
                if (adjMatrix[i][j] != 1) return false; // phải có cạnh giữa mọi cặp đỉnh
            }
        }
    }

    return true; // nếu không vi phạm điều kiện nào
}

bool isBipartite(const std::vector<std::vector<int>> &adjMatrix) {
    int n = adjMatrix.size();
    std::vector<int> color(n, -1);  // -1: chưa tô màu

    for (int start = 0; start < n; ++start) {
        if (color[start] == -1) {
            std::queue<int> q;
            q.push(start);
            color[start] = 0;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v = 0; v < n; ++v) {
                    if (adjMatrix[u][v]) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            return false; // đỉnh kề có cùng màu
                        }
                    }
                }
            }
        }
    }

    return true; // không có mâu thuẫn màu
}


bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> color(n, -1); // -1: chưa tô màu, 0/1: hai tập

    // Kiểm tra tính hai phía bằng BFS
    queue<int> q;
    q.push(0);
    color[0] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false; // Không phải hai phía
                }
            }
        }
    }

    // Kiểm tra tính đầy đủ hai phía
    vector<int> X, Y;
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0) X.push_back(i);
        else Y.push_back(i);
    }

    for (int x : X) {
        for (int y : Y) {
            if (!adjMatrix[x][y]) return false; // Thiếu cạnh nối X-Y
        }
    }

    for (int x1 : X) {
        for (int x2 : X) {
            if (adjMatrix[x1][x2]) return false; // Có cạnh trong X
        }
    }

    for (int y1 : Y) {
        for (int y2 : Y) {
            if (adjMatrix[y1][y2]) return false; // Có cạnh trong Y
        }
    }

    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix)
{
    if (!isDirected(adjMatrix)) return adjMatrix;
    int n = adjMatrix.size();
    vector<vector<int>> tempMatrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (adjMatrix[i][j])
                {
                    tempMatrix[i][j] = 1;
                    tempMatrix[j][i] = 1;
                }
        }
    return tempMatrix;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    vector<vector<int>> tempMatrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
        if (!adjMatrix[i][j] && i != j) 
        {
            tempMatrix[i][j] = 1;
        }
    }
    return tempMatrix;
}




bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    if (u < 0 || u >= n || v < 0 || v >= n) return false;//lỗi chỉ số
    if (u == v) return true;//xem là kết nối nếu trùng 

    vector<bool> visited(n, false);
    queue<int> q;
    visited[u] = true;
    q.push(u);

    while(!q.empty())
    {
        int to_x = q.front();
        q.pop();

        if (to_x == v) return true;// nếu đến v
        for (int x = 0; x < n; x++)
        {
            if (adjMatrix[to_x][x] == 1 && !visited[x])
            {
                visited[x] = true;
                q.push(x);
            }
        }
    }
    return false;// không kết nối
}


bool isGraphConnected(const vector<vector<int>>& adjMatrix, bool isDirected) {
    int n = adjMatrix.size();
    if (n == 0) return true;

    // Tìm ít nhất 1 đỉnh không cô lập để bắt đầu duyệt
    int start = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] == 1) {
                start = i;
                break;
            }
        }
        if (start != -1) break;
    }

    // Nếu tất cả đỉnh đều cô lập (start == -1)
    if (start == -1) {
        return (n == 1); // Liên thông nếu chỉ có 1 đỉnh
    }

    // Kiểm tra liên thông từ đỉnh start (bỏ qua đỉnh cô lập)
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
            if (!isDirected && adjMatrix[v][u] == 1 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    // Chỉ kiểm tra các đỉnh không cô lập
    for (int i = 0; i < n; ++i) {
        bool isIsolated = true;
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1) {
                isIsolated = false;
                break;
            }
        }
        if (!isIsolated && !visited[i]) {
            return false; // Tồn tại đỉnh không cô lập nhưng không được thăm
        }
    }

    return true;
}

bool Has_Cycle_Euler(const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    if (n == 0) return false;
    bool kiem_tra = isDirected(adjMatrix);
    vector<int> inDegree(n, 0);
    vector<int> outDegree(n, 0);
    // tính bậc vào, bậc ra tất cả đỉnh
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            if (adjMatrix[i][j] == 1) 
            {
                outDegree[i]++;
                inDegree[j]++;
            }
        }
    }
    if (kiem_tra) //xử lý có hướng hoặc vô hướng
    { //có hướng
        for (int i = 0; i < n; i++)
        {
            if (inDegree[i] != outDegree[i])
                return false;
        }
    }
    else
    {//vô hướng
        for (int i = 0; i < n; i++)
        {
            if ((inDegree[i] + outDegree[i]) % 2 != 0) return false;
        }
    }

    // Kiểm tra xem đồ thị có rỗng không
    bool hasEdges = false;
    for (int i = 0; i < n; ++i) {
        if (outDegree[i] > 0) {
            hasEdges = true;
            break;
        }
    }
    if (!hasEdges) {
        return false; // Không có cạnh nào, không có chu trình Euler
    }
    return isGraphConnected(adjMatrix, kiem_tra);
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    if (!Has_Cycle_Euler(adjMatrix)) return {};//không có chu trình euler
    
    vector<vector<int>> tempMatrix = adjMatrix;
    stack<int> now_path;
    vector<int> Ec;

    bool kiem_tra = isDirected(adjMatrix);
    int start = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (tempMatrix[i][j])
            {
                start = i;//tìm điểm bắt đầu chu trình
                break;
            }
        }
        if (start != -1) break;
    }
    if (start == -1) return {};//nếu tất cả điểm cô lập hoặc đồ thị rỗng
    // Thuật toán Hierholzer tìm chu trình Euler
    now_path.push(start);
    while (!now_path.empty())
    {
        int u = now_path.top();

        int v = -1;
        //tìm cạnh liền kề
        for (int i = 0; i < n; i++)
        {
            if (tempMatrix[u][i]) 
            {
                v = i;
                break;
            }
        }
        if (v != -1)
        {
            now_path.push(v);
            tempMatrix[u][v] = 0;
            if (!kiem_tra)//đối với vô hướng
            {
                tempMatrix[v][u] = 0;
            }
        }
        else
        {
            Ec.push_back(u);
            now_path.pop();
        }
    }
    reverse(Ec.begin(), Ec.end()); //đảo ngươc để đúng thứ tự chu trình
    //kiểm tra cong cạnh chưa duyệt không
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (tempMatrix[i][j]) return {};
        }
    }
    return Ec;
}
//DFS
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)
{
    int n = adjMatrix.size();
    if (start < 0 || start >= n) return {};
    vector<vector<int>> SpanningTree_Matrix(n, vector<int>(n,0));
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(start);
    visited[start] = true;
    while (!s.empty())
    {
        int u = s.top();
        s.pop();
        for (int i = 0; i < n; i++)
        {
            if (adjMatrix[u][i] == 1 && !visited[i])
            {
                SpanningTree_Matrix[u][i] = 1;
                SpanningTree_Matrix[i][u] = 1;
                visited[i] = true;
                s.push(i);
            }
        }
    }
    return SpanningTree_Matrix;
}
//BFS
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)
{
    int n = adjMatrix.size();
    if (start < 0 || start >= n) return {};
    vector<vector<int>> SpanningTree_Matrix(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < n; i++)
        {
            if (adjMatrix[u][i] && !visited[i])
            {
                SpanningTree_Matrix[u][i] = 1;
                SpanningTree_Matrix[i][u] = 1;
                q.push(i);
                visited[i] = true;
            }
        }
    }
    return SpanningTree_Matrix;
}
//Thuật toán Dijkstra
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    if (start < 0 || start >= n || end < 0 || end >= 0)
    {
        return {};
    }
    vector<long long> d(n, INF);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    d[0] = 0;
    q.push({0, start});
    while (!q.empty())
    {
        pair<int, int> top = q.top();
        q.pop();
        int u = top.second;
        int kc = top.first;
        if (kc > d[u]) continue;
        for (int x = 0; x < n; x++)
        {
            if (adjMatrix[u][x] > 0 && d[u] != INF)
            {
                if (d[u] + adjMatrix[u][x] < d[x])
                {
                    d[x] = d[u] + adjMatrix[u][x];
                    parent[x] = u;
                    q.push({d[x], x});
                }
            }
        }
    }
    vector<int> path;
    if (d[end] == INF)
    {
        return {};
    }

    int cur = end;
    while (cur != -1)
    {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());
    return path;
}
//Thuật toán Bellman Ford
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    if (start < 0 || start >= n || end < 0 || end >= n)
    {
        return {};
    }
    vector<long long> d(n, INF);
    vector<int> parent(n, -1);
    d[start] = 0;
    for (int i = 0; i < n -1; i++)
    {
        for (int u = 0; u < n; u++)
        {
            for (int v = 0; v < n; v++)
            {
                if (adjMatrix[u][v] != 0 && d[u] != INF)
                {
                    if (d[u] + adjMatrix[u][v] < d[v]) 
                    {
                        d[v] = d[u] + adjMatrix[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
    }
    // Kiểm tra chu trình âm (lặp lần thứ V)
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] != 0 && d[u] != INF) {
                if (d[u] + adjMatrix[u][v] < d[v]) {
                    // Phát hiện chu trình âm
                    // Đường đi ngắn nhất không xác định
                    return {}; // Trả về vector rỗng
                }
            }
        }
    }

    // Xây dựng đường đi
    vector<int> path;
    if (d[end] == INF) { // Không có đường đi đến end
        return {};
    }

    int cur = end;
    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());

    return path;
}

