#include <stdio.h>

// Khai báo mảng 3 chiều để đánh dấu trạng thái đã thăm (x: 0-10, y: 0-7, z: 0-4)
int Board[11][8][5];
int found = 0;  // Biến đánh dấu đã tìm được lời giải chưa

// Cấu trúc lưu trạng thái (dung tích của 3 bình x, y, z)
typedef struct {
    int x, y, z;
} State;

// Mảng lưu đường đi (tối đa 200 trạng thái), path_len là độ dài đường đi hiện tại
State path[200];
int path_len = 0;

// Hàm đệ quy để tìm đường rót nước giữa 3 bình sao cho có 2 lít trong bất kỳ bình nào
int loop(int x, int y, int z) {
    // Nếu một trong ba bình đạt được đúng 2 lít nước → đã tìm ra lời giải
    if (y == 2 || z == 2) {
        found = 1;
        // In ra toàn bộ đường đi
        for (int i = 0; i < path_len; i++) {
            printf("%d %d %d\n", path[i].x, path[i].y, path[i].z);
        }
        printf("%d %d %d\n", x, y, z); // In trạng thái cuối cùng
        return 0;
    }

    int a, b, c;

    // Nếu chưa tìm được lời giải thì tiếp tục thử các khả năng đổ nước
    if (found != 1) {
        // Nếu bình x có nước thì thử đổ từ x sang y và x sang z
        if (x > 0) {
            // Đổ x → y
            a = x; b = y; c = z;
            b += a;
            if (b > 7) { a = b - 7; b = 7; } else a = 0;
            if (Board[a][b][c] == 0) {
                Board[a][b][c] = 1;
                path[path_len++] = (State){a, b, c};
                loop(a, b, c);
                if (found == 1) return 0;
                path_len--; Board[a][b][c] = 0;
            }

            // Đổ x → z
            a = x; b = y; c = z;
            c += a;
            if (c > 4) { a = c - 4; c = 4; } else a = 0;
            if (Board[a][b][c] == 0) {
                Board[a][b][c] = 1;
                path[path_len++] = (State){a, b, c};
                loop(a, b, c);
                if (found == 1) return 0;
                path_len--; Board[a][b][c] = 0;
            }
        }

        // Nếu bình y có nước → đổ y → x, y → z
        if (y > 0) {
            // Đổ y → x
            a = x; b = y; c = z;
            a += b;
            if (a > 10) { b = a - 10; a = 10; } else b = 0;
            if (Board[a][b][c] == 0) {
                Board[a][b][c] = 1;
                path[path_len++] = (State){a, b, c};
                loop(a, b, c);
                if (found == 1) return 0;
                path_len--; Board[a][b][c] = 0;
            }

            // Đổ y → z
            a = x; b = y; c = z;
            c += b;
            if (c > 4) { b = c - 4; c = 4; } else b = 0;
            if (Board[a][b][c] == 0) {
                Board[a][b][c] = 1;
                path[path_len++] = (State){a, b, c};
                loop(a, b, c);
                if (found == 1) return 0;
                path_len--; Board[a][b][c] = 0;
            }
        }

        // Nếu bình z có nước → đổ z → x, z → y
        if (z > 0) {
            // Đổ z → x
            a = x; b = y; c = z;
            a += c;
            if (a > 10) { c = a - 10; a = 10; } else c = 0;
            if (Board[a][b][c] == 0) {
                Board[a][b][c] = 1;
                path[path_len++] = (State){a, b, c};
                loop(a, b, c);
                if (found == 1) return 0;
                path_len--; Board[a][b][c] = 0;
            }

            // Đổ z → y
            a = x; b = y; c = z;
            b += c;
            if (b > 7) { c = b - 7; b = 7; } else c = 0;
            if (Board[a][b][c] == 0) {
                Board[a][b][c] = 1;
                path[path_len++] = (State){a, b, c};
                loop(a, b, c);
                if (found == 1) return 0;
                path_len--; Board[a][b][c] = 0;
            }
        }
    }
    return 0;
}

int main() {
    // Khởi tạo trạng thái ban đầu: bình x có 0L, y có 7L, z có 4L
    Board[0][7][4] = 1;
    path[path_len++] = (State){0, 7, 4};  

    // Gọi hàm tìm kiếm lời giải
    loop(0, 7, 4);

    // In kết quả: 1 nếu tìm được, 0 nếu không
    printf("%d", found);
    return 0;
}
