#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Node để biểu diễn một bài hát trong danh sách phát
class SongNode {
public:
    string song_name;
    SongNode* next;
    SongNode* prev;

    SongNode(const string& name) : song_name(name), next(nullptr), prev(nullptr) {}
};

// Lớp để biểu diễn trình phát nhạc
class MusicPlayer {
private:
    SongNode* head;
    SongNode* tail;
    SongNode* current;
    unordered_map<string, SongNode*> songMap; // Sử dụng bản đồ băm để tìm kiếm bài hát nhanh chóng

public:
    MusicPlayer() : head(nullptr), tail(nullptr), current(nullptr) {}

    // Thêm bài hát vào danh sách phát
    void addSong(const string& song_name) {
        if (songMap.find(song_name) != songMap.end()) return; // Bài hát đã tồn tại

        SongNode* newSong = new SongNode(song_name);
        songMap[song_name] = newSong;

        if (!head) { // Nếu danh sách phát trống
            head = tail = current = newSong;
            newSong->next = newSong;
            newSong->prev = newSong;
        } else {
            newSong->prev = tail;
            newSong->next = head;
            tail->next = newSong;
            head->prev = newSong;
            tail = newSong;
        }
    }

    // Phát bài hát tiếp theo
    void playNext() {
        if (!current) return; // Không có bài hát để phát
        current = current->next;
    }

    // Phát bài hát trước đó
    void playPrevious() {
        if (!current) return; // Không có bài hát để phát
        current = current->prev;
    }

    // Xóa bài hát khỏi danh sách phát
    void removeSong(const string& song_name) {
        if (songMap.find(song_name) == songMap.end()) return; // Không tìm thấy bài hát

        SongNode* songToRemove = songMap[song_name];

        if (songToRemove == head && songToRemove == tail) { // Chỉ có một bài hát trong danh sách
            head = tail = current = nullptr;
        } else if (songToRemove == head) { // Xóa bài hát đầu tiên
            head = head->next;
            tail->next = head;
            head->prev = tail;
            current = head;
        } else if (songToRemove == tail) { // Xóa bài hát cuối cùng
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
            current = tail;
        } else { // Xóa bài hát ở giữa
            songToRemove->prev->next = songToRemove->next;
            songToRemove->next->prev = songToRemove->prev;
            if (current == songToRemove) current = songToRemove->next;
        }

        songMap.erase(song_name);
        delete songToRemove;
    }

    // Hiển thị danh sách phát
    void displayPlaylist() {
        if (!head) {
            cout << "Playlist is empty." << endl;
            return;
        }

        SongNode* temp = head;
        bool first = true;
        do {
            if (!first) cout << " ";
            cout << temp->song_name;
            first = false;
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }
};

int main() {
    int n;
    cin >> n;

    MusicPlayer player;

    for (int i = 0; i < n; ++i) {
        string operation;
        cin >> operation;

        if (operation == "ADD") {
            string song_name;
            cin >> song_name;
            player.addSong(song_name);
        } else if (operation == "NEXT") {
            player.playNext();
        } else if (operation == "PREV") {
            player.playPrevious();
        } else if (operation == "REMOVE") {
            string song_name;
            cin >> song_name;
            player.removeSong(song_name);
        } else if (operation == "DISPLAY") {
            player.displayPlaylist();
        }
    }

    return 0;
}
