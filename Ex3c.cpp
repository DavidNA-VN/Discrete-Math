#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#define MAX 1000000

using namespace std;

// Hàm tìm đỉnh có khoảng cách nhỏ nhất chưa được duyệt
int minDistance(vector<int>& dist, vector<bool>& sptSet) {
    int min = MAX, chiso_min;
    for (int i = 0; i < dist.size(); i++)
        if (!sptSet[i] && dist[i] <= min) {
            min = dist[i];
            chiso_min = i;
        }
    return chiso_min;
}

// Hàm in đường đi ngược từ đích về đầu dựa vào mảng truy vết con[]
void inDuongDi(vector<int>& con, int start, int end, vector<string>& tu) {
    if (end == start) {
        cout << tu[start] << " ";
    } else if (con[end] == -1) {
        cout << "Khong co duong di tu " << tu[start] << " den " << tu[end] << ".\n";
    } else {
        inDuongDi(con, start, con[end], tu);  // đệ quy in trước
        cout << tu[end] << " ";
    }
}

// Thuật toán Dijkstra tìm đường đi ngắn nhất từ bdau đến kthuc
void dijkstra(vector<vector<int>>& dothi, int bdau, int kthuc, vector<string>& tu) {
    int size = dothi.size();
    vector<int> dist(size, MAX);      // Khoảng cách từ bdau đến các đỉnh
    vector<int> con(size, -1);        // Mảng truy vết để in đường đi
    vector<bool> subset(size, false); // Đánh dấu đỉnh đã duyệt

    dist[bdau] = 0;  // Khoảng cách từ bdau đến chính nó là 0

    for (int dem = 0; dem < size - 1; dem++) {
        int u = minDistance(dist, subset);  // Lấy đỉnh chưa xét có dist nhỏ nhất
        subset[u] = true;  // Đánh dấu đã xét

        // Cập nhật khoảng cách tới các đỉnh kề u
        for (int v = 0; v < size; v++) {
            if (!subset[v] && dothi[u][v] && dist[u] != MAX && dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                con[v] = u;  // Lưu truy vết đường đi
            }
        }
    }

    // In kết quả
    if (dist[kthuc] == MAX) {
        cout << "Khong co duong di tu " << tu[bdau] << " den " << tu[kthuc] << "\n";
    } else {
        cout << "Duong di: ";
        inDuongDi(con, bdau, kthuc, tu);
        cout << endl;
    }
}

// Hàm kiểm tra xem s1 và s2 có thể liên kết không (khác nhau đúng 4 ký tự từ vị trí 1 trở đi)
bool check(const string& s1, const string& s2) {
    vector<int> check_s1(5, 1);
    vector<int> check_s2(5, 0);
    for (int i = 1; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (check_s1[i] == 1 && check_s2[j] == 0 && s1[i] == s2[j]) {
                check_s1[i] = 0;
                check_s2[j] = 1;
                break;
            }
        }
    }

    // Nếu còn ký tự ở s1 chưa matched => không hợp lệ
    for (int i = 1; i < 5; i++) {
        if (check_s1[i] == 1) return false;
    }

    return true;
}

int main() {
    // Đọc file từ điển
    ifstream input("E:/TRR code/sgb-words.txt");
    if (!input) {
        cerr << "Khong the mo tep.\n";
        return 1;
    }

    vector<string> tu;
    string temp;
    while (input >> temp) {
        tu.push_back(temp);
    }
    input.close();

    int size = tu.size();
    vector<vector<int>> dothi(size, vector<int>(size, 0));

    // Tạo đồ thị: nối các từ nếu khác nhau 4 ký tự cuối
    for (int k = 0; k < size; k++) {
        for (int j = 0; j < size; j++) {
            if (k != j && check(tu[k], tu[j])) {
                dothi[k][j] = 1;  // Đồ thị có hướng
            }
        }
    }

    // Nhập từ bắt đầu và kết thúc
    string u, v;
    cout << "Nhap tu bat dau u: ";
    cin >> u;
    cout << "Nhap tu ket thuc v: ";
    cin >> v;

    // Tìm chỉ số của từ trong danh sách
    auto itU = find(tu.begin(), tu.end(), u);
    auto itV = find(tu.begin(), tu.end(), v);

    if (itU == tu.end() || itV == tu.end()) {
        cout << "Tu u hoac v khong co trong tu dien.\n";
    } else {
        int cso_u = distance(tu.begin(), itU);
        int cso_v = distance(tu.begin(), itV);
        dijkstra(dothi, cso_u, cso_v, tu);
    }

    return 0;
}
