#include <iostream>
#include <string>
using namespace std;

class Token {
public:
    Token* next;
    string tokenID;
    int expiredTime;

    Token(string id, int time) : tokenID(id), next(nullptr), expiredTime(time) {}
};

class AuthenticationManager {
public:
    Token* head;
    int timeToLive;

    AuthenticationManager(int ttl) {
        timeToLive = ttl;
        head = nullptr;
    }

    // Tạo một token mới
    void generate(string tokenID, int currentTime) {
        Token* newToken = new Token(tokenID, currentTime + timeToLive);
        // Thêm token vào đầu danh sách
        newToken->next = head;
        head = newToken;	
    }

    // Gia hạn một token chưa hết hạn
    void renew(string tokenID, int currentTime) {
        Token* temp = head;
        while (temp != nullptr) {
            if (temp->tokenID == tokenID && temp->expiredTime > currentTime) {
                temp->expiredTime = currentTime + timeToLive;
                return; // Thoát sau khi token được gia hạn
            }
            temp = temp->next;
        }
    }

    // Đếm số lượng token chưa hết hạn và loại bỏ các token đã hết hạn
    int countUnexpiredTokens(int currentTime) {
        int count = 0;
        Token* temp = head;
        Token* prev = nullptr;

        while (temp != nullptr) {
            if (temp->expiredTime > currentTime) {
                count++; // Đếm token chưa hết hạn
                prev = temp; // Giữ vị trí của token chưa hết hạn cuối cùng
            } else {
                // Loại bỏ token đã hết hạn
                if (prev == nullptr) {
                    head = temp->next; // Cập nhật head nếu token đã hết hạn nằm ở đầu danh sách
                } else {
                    prev->next = temp->next; // Bỏ qua token đã hết hạn
                }
                Token* deletedToken = temp; // Lưu token đã hết hạn
                temp = temp->next; // Di chuyển đến token tiếp theo
                delete deletedToken; // Xóa token đã hết hạn
                continue; // Bỏ qua vòng lặp hiện tại
            }
            temp = temp->next; // Di chuyển đến token tiếp theo
        }
        return count; // Trả về số lượng token chưa hết hạn
    }
};

int main() {
    string initial;
    cin >> initial;
    cin.ignore();
    int timeToLive;
    cin >> timeToLive; // Đọc timeToLive
    AuthenticationManager* authManager = new AuthenticationManager(timeToLive);
    cout << "null" << endl; // Xuất ra cho hàm khởi tạo

    string command;
    while (cin >> command) {
        if (command == "generate") {
            string tokenId;
            int currentTime;
            cin >> tokenId >> currentTime; 
            authManager->generate(tokenId, currentTime);
            cout << "null" << endl; // Xuất ra cho generate
        } else if (command == "renew") {
            string tokenId;
            int currentTime;
            cin >> tokenId >> currentTime; 
            authManager->renew(tokenId, currentTime);
            cout << "null" << endl; // Xuất ra cho renew
        } else if (command == "countUnexpiredTokens") {
            int currentTime;
            cin >> currentTime; 
            cout << authManager->countUnexpiredTokens(currentTime) << endl; // Xuất ra số lượng token chưa hết hạn
        }
    }

    delete authManager; // Dọn dẹp bộ nhớ
    return 0;
}
