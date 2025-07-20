#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Hàm inDFS: Duyệt và in các từ trong thành phần liên thông mạnh bằng DFS
void inDFS(vector<vector<int>>& dothi, int size, int dinh, vector<bool>& visited, vector<string>& word);

// Hàm DFS1: DFS để lưu thứ tự hoàn thành vào stack (dùng trong thuật toán Kosaraju)
void DFS1(vector<vector<int>>& dothi, int size, int dinh, vector<bool>& visited, vector<int>& stack) {
  visited[dinh] = true;
  for (int i = 0; i < size; i++) {
    if (dothi[dinh][i] == 1 && !visited[i]) {
      DFS1(dothi, size, i, visited, stack);
    }
  }
  stack.push_back(dinh);  // Sau khi duyệt xong đỉnh thì đưa vào stack
}

// Hàm DFS2: Duyệt trên đồ thị chuyển vị (transpose)
void DFS2(vector<vector<int>>& dothi, int size, int dinh, vector<bool>& visited) {
  visited[dinh] = true;
  for (int i = 0; i < size; i++) {
    if (dothi[i][dinh] == 1 && !visited[i]) {
      DFS2(dothi, size, i, visited);
    }
  }
}

// Hàm ktra: Kiểm tra xem s1 có thể biến thành s2 bằng cách tráo vị trí 4 ký tự cuối hay không
bool ktra(const string& s1, const string& s2) {
  vector<int> check_s1(5, 1);  // đánh dấu ký tự chưa khớp ở s1
  vector<int> check_s2(5, 0);  // đánh dấu ký tự đã khớp ở s2
  for (int i = 1; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (check_s1[i] == 1 && check_s2[j] == 0 && s1[i] == s2[j]) {
        check_s1[i] = 0;
        check_s2[j] = 1;
        break;
      }
    }
  }

  // Nếu còn ký tự chưa match ở s1 -> không thoả
  for (int i = 1; i < 5; i++) {
    if (check_s1[i] == 1) {
      return false;
    }
  }

  return true;
}

// Hàm stpltmanh: Tìm và in ra thành phần liên thông mạnh chứa từ được nhập
void stpltmanh(vector<vector<int>>& dothi, int size, int u, vector<bool>& visited, vector<string>& word) {
  vector<int> stack;
  visited[u] = true;

  // DFS lần đầu để lấy stack
  DFS1(dothi, size, u, visited, stack);

  // Tạo đồ thị chuyển vị
  vector<vector<int>> transpose(size, vector<int>(size, 0));
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      transpose[i][j] = dothi[j][i];
    }
  }

  fill(visited.begin(), visited.end(), false);
  int stpltm = 0;

  // Duyệt các đỉnh theo thứ tự stack để in ra thành phần liên thông mạnh
  for (int i = stack.size() - 1; i >= 0; i--) {
    int dinh = stack[i];
    if (!visited[dinh]) {
      stpltm++;
      cout << "Cac tu cung thanh phan lien thong manh: ";
      inDFS(dothi, size, dinh, visited, word);
      cout << endl;
    }
  }
}

// Hàm inDFS: duyệt và in ra các từ trong 1 thành phần liên thông mạnh
void inDFS(vector<vector<int>>& dothi, int size, int dinh, vector<bool>& visited, vector<string>& word) {
  cout << word[dinh] << " ";
  visited[dinh] = true;
  for (int i = 0; i < size; i++) {
    if (dothi[dinh][i] == 1 && !visited[i]) {
      inDFS(dothi, size, i, visited, word);
    }
  }
}

int main() {
  // Đọc dữ liệu từ file
  ifstream input("E:/TRR code/sgb-words.txt");
  if (!input) {
    cerr << "Khong the mo tep. \n";
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

  // Xây dựng ma trận kề cho đồ thị
  for (int k = 0; k < size; k++) {
    for (int j = 0; j < size; j++) {
      if (k != j) {
        if (ktra(tu[k], tu[j])) {
          dothi[k][j] = 1;
        }
      }
    }
  }

  vector<int> stack;
  vector<bool> visited(size, false);

  // DFS để đổ vào stack theo thứ tự kết thúc
  for (int i = 0; i < size; i++) {
    if (!visited[i]) {
      DFS1(dothi, size, i, visited, stack);
    }
  }

  // Tạo đồ thị chuyển vị
  vector<vector<int>> doicho(size, vector<int>(size, 0));
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      doicho[i][j] = dothi[j][i];
    }
  }

  fill(visited.begin(), visited.end(), false);
  int stpltm = 0;

  // Duyệt DFS trên đồ thị chuyển vị theo thứ tự stack
  for (int i = stack.size() - 1; i >= 0; i--) {
    int vertex = stack[i];
    if (!visited[vertex]) {
      stpltm++;
      DFS2(doicho, size, vertex, visited);
    }
  }

  cout << "so thanh phan lien thong manh: " << stpltm << endl;

  // Nhập từ cần tìm thành phần liên thông mạnh
  string thutunhat;
  cout << "Nhap tu thu nhat: ";
  cin >> thutunhat;

  // Tìm vị trí từ trong danh sách
  auto res = find(tu.begin(), tu.end(), thutunhat);
  if (res == tu.end()) {
    cout << "Tu thu nhat khong hop le.\n";
  } else {
    int cso_u = distance(tu.begin(), res);
    vector<bool> visited(size, false);
    stpltmanh(dothi, size, cso_u, visited, tu);
  }

  return 0;
}
