#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    string url;
    Node* prev;
    Node* next;

    Node(string url) : url(url), prev(nullptr), next(nullptr) {}
};

class BrowserHistory {
public:
    Node* head;    // Nút đầu tiên cho trang chủ
    Node* current; // Nút hiện tại trong lịch sử

    // Constructor để khởi tạo với URL trang chủ
    BrowserHistory(string homepage) {
        head = new Node(homepage);  // Bắt đầu với trang chủ
        current = head;             // Current trỏ đến nút đầu tiên
    }

    // Truy cập một URL mới và xóa lịch sử chuyển tiếp
    void visit(string url) {
        Node* newNode = new Node(url);
        current->next = newNode;   // Liên kết current với nút mới
        newNode->prev = current;   // Liên kết nút mới trở lại current
        current = newNode;         // Di chuyển current đến nút mới
        
        // Xóa lịch sử chuyển tiếp
        Node* temp = newNode->next;
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        newNode->next = nullptr;
    }

    // Di chuyển trở lại lịch sử theo số bước cho trước
    string back(int steps) {
        while (steps > 0 && current->prev != nullptr) {
            current = current->prev; // Di chuyển đến nút trước đó
            steps--;
        }
        return current->url; // Trả về URL hiện tại
    }

    // Di chuyển chuyển tiếp trong lịch sử theo số bước cho trước
    string forward(int steps) {
        while (steps > 0 && current->next != nullptr) {
            current = current->next; // Di chuyển đến nút tiếp theo
            steps--;
        }
        return current->url; // Trả về URL hiện tại
    }

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->url << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    ~BrowserHistory() {
        Node* temp;
        while (head) { // Dọn dẹp tất cả các nút bắt đầu từ head
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Hàm hiển thị menu cho người dùng
void showMenu() {
    cout << "\n--- MENU ---" << endl;
    cout << "1. Truy cập URL mới (visit)" << endl;
    cout << "2. Lùi về trang trước (back)" << endl;
    cout << "3. Tiến đến trang tiếp theo (forward)" << endl;
    cout << "4. Hiển thị lịch sử trình duyệt" << endl;
    cout << "5. Thoát chương trình" << endl;
    cout << "Lựa chọn của bạn: ";
}

// Hàm xử lý lịch sử trình duyệt và tương tác với người dùng
void processBrowserHistory() {
    string homepage;
    cout << "Nhập URL trang chủ: ";
    cin >> homepage; // Đọc URL trang chủ

    BrowserHistory* browserHistory = new BrowserHistory(homepage); // Tạo instance BrowserHistory

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string url;
                cout << "Nhập URL mới: ";
                cin >> url;
                browserHistory->visit(url);
                cout << "Đã truy cập: " << url << endl;
                break;
            }
            case 2: {
                int steps;
                cout << "Nhập số bước cần lùi: ";
                cin >> steps;
                cout << "URL hiện tại: " << browserHistory->back(steps) << endl;
                break;
            }
            case 3: {
                int steps;
                cout << "Nhập số bước cần tiến: ";
                cin >> steps;
                cout << "URL hiện tại: " << browserHistory->forward(steps) << endl;
                break;
            }
            case 4:
                cout << "Lịch sử trình duyệt: ";
                browserHistory->display();
                break;
            case 5:
                cout << "Thoát chương trình..." << endl;
                break;
            default:
                cout << "Lựa chọn không hợp lệ, vui lòng chọn lại." << endl;
        }
    } while (choice != 5);

    delete browserHistory;  // Dọn dẹp bộ nhớ
}

int main() {
    processBrowserHistory();  // Xử lý các lệnh lịch sử trình duyệt
    return 0;
}
