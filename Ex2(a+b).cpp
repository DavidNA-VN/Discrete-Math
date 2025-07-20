#include <bits/stdc++.h>
using namespace std;

// Danh sách các từ đọc từ file sgb-words.txt
vector<string> tu;

// Đồ thị biểu diễn các từ có thể chuyển đổi thành nhau bằng cách đổi đúng 1 ký tự
vector<vector<int>> dothi;

// Hàm kiểm tra 2 từ có khác nhau đúng 1 ký tự không
bool check(string s1, string s2) {
    int diff = 0;
    for (int i = 0; i < 5; i++) {
        if (s1[i] != s2[i]) diff++;
    }
    return diff == 1;
}

// Xây dựng đồ thị: nối cạnh giữa các từ khác nhau đúng 1 ký tự
void build_dothi() {
    dothi.resize(tu.size());
    for (int i = 0; i < tu.size(); i++) {
        for (int j = i + 1; j < tu.size(); j++) {
            if (check(tu[i], tu[j])) {
                dothi[i].push_back(j);
                dothi[j].push_back(i);
            }
        }
    }
}

// DFS tìm thành phần liên thông
void dfs(int u, vector<bool> &visited) {
    visited[u] = true;
    for (int v : dothi[u]) {
        if (!visited[v]) {
            dfs(v, visited);
        }
    }
}

// Đếm số thành phần liên thông trong đồ thị
int stplt() {
    int dem = 0;
    vector<bool> visited(tu.size(), false);
    for (int i = 0; i < tu.size(); i++) {
        if (!visited[i]) {
            dfs(i, visited);
            dem++;
        }
    }
    return dem;
}

// BFS tìm đường đi từ u đến v, lưu lại cha để truy vết đường đi
void bfs(int u, int v, vector<bool> &visited, vector<int> &cha) {
    queue<int> q;
    q.push(u);
    visited[u] = true;
    cha[u] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : dothi[u]) {
            if (!visited[v]) {
                visited[v] = true;
                cha[v] = u;
                q.push(v);
            }
        }
    }
}

// Tìm đường đi ngắn nhất từ u đến v bằng BFS và truy vết từ mảng cha
vector<int> shortest_path(int u, int v) {
    vector<bool> visited(tu.size(), false);
    vector<int> cha(tu.size(), -1);
    bfs(u, v, visited, cha);

    vector<int> path;
    int current = v;
    while (current != -1) {
        path.push_back(current);
        current = cha[current];
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    // Đọc danh sách từ từ file
    ifstream file("E:/TRR code/sgb-words.txt");
    string word;
    while (file >> word) {
        tu.push_back(word);
    }
    file.close();

    // Xây đồ thị
    build_dothi();

    // Đếm và in số thành phần liên thông
    int n_components = stplt();
    cout << "Do thi co " << n_components << " thanh phan lien thong" << endl;

    // Nhập 2 từ đầu và cuối
    cout << "Nhap u: ";
    cin >> word;
    int u = find(tu.begin(), tu.end(), word) - tu.begin();

    cout << "Nhap v: ";
    cin >> word;
    int v = find(tu.begin(), tu.end(), word) - tu.begin();

    // Tìm đường đi ngắn nhất và in kết quả
    vector<int> path = shortest_path(u, v);
    cout << "Duong di ngan nhat tu " << tu[u] << " den " << tu[v] << " la:" << endl;
    for (int i : path) {
        cout << tu[i] << " ";
    }
    cout << endl;
    return 0;
}
