#include <string>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

string getUserInput();
void print(string msg);
string getAlgorithmAndFrameInput();
string getPageInput();
void accessPage(int pageNum);
void beldayReplacement(int pageNum);
void clockReplacement(int pageNum);
void fifoReplacement(int pageNum);
void lruReplacement(int pageNum);
void rollLeft(int pageNum);

string algorithm = "";
int frameNums;
int pageAccessCount = 0;

struct Page {
  int pageNum;
  int timeLastUsed;
  bool accessBit;
};

vector<Page> buffer;

int main() {
    string input = getAlgorithmAndFrameInput();
    while (input != "") {
        input = getPageInput();
        if (input == "") break;
        try {
            accessPage(stoi(input));
        } catch (const invalid_argument& ia) {
            break;
        }
    }
    print("Bye bye!");
    return 0;
}

string getUserInput() {
    string input;
    getline(cin, input);
    return input;
}

void print(string msg) {
    cout << msg;
}

string getAlgorithmAndFrameInput() {
    print("\nPick a page replacement algorithm \n(BELDAY, CLOCK, FIFO, LRU)\n\n");
    print("algorithm> ");

    string input = getUserInput();
    int pivot = input.find(" ");

    if (pivot < 0 || pivot > input.length()) return "";

    algorithm = input.substr(0, pivot);

    for (int i = 0; i < algorithm.length(); i++) 
        algorithm[i] = toupper(algorithm[i]);

    try {
        frameNums = stoi(input.substr(pivot));
    } catch (const invalid_argument& ia) {
        return "";
    }

    if (algorithm != "BELADY" 
     && algorithm != "CLOCK" 
     && algorithm != "FIFO" 
     && algorithm != "LRU"
    ) return "";

    return input;
}

string getPageInput() {
    print("page> ");
    return getUserInput();
}

void accessPage(int pageNum) {
    pageAccessCount++;
    // Iterate through cached pages
    for (int i = 0; i < buffer.size(); i++) {
        // HIT
        if (buffer.at(i).pageNum == pageNum) {
            buffer.at(i).accessBit = 1;
            buffer.at(i).timeLastUsed = pageAccessCount;
            cout << pageNum << "NF" << endl;
            return;
        }
    }
    // MISS
    cout << pageNum << "F";

    // If page replacement is required
    if (buffer.size() == frameNums) {
        if (algorithm == "BELADY") {
            beldayReplacement(pageNum);
        } else if (algorithm == "CLOCK") {
            clockReplacement(pageNum);
        } else if (algorithm == "FIFO") {
            fifoReplacement(pageNum);
        } else if (algorithm == "LRU") {
            lruReplacement(pageNum);
        }
    } else {
        struct Page page = createPage(pageNum);
        buffer.push_back(page);
        frameNums++;
    }
}

void beldayReplacement(int pageNum) {

}

struct Page createPage(int pageNum) {
    struct Page page;
    page.pageNum = pageNum;
    page.timeLastUsed = pageAccessCount;
    page.accessBit = true;
    return page;
}

void clockReplacement(int pageNum) {
    // Scan the buffer
    for (int i = 0; i < buffer.size(); i++) {
        // Check if access bit is set
        if (buffer.at(i).accessBit == true) {
            // Clear access bit
            buffer.at(i).accessBit = false;
        } else {
            // Replace page
            buffer.at(i) = createPage(pageNum);
        }
    }
}

void fifoReplacement(int pageNum) {
    // Remove first element placed in buffer
    rollLeft(pageNum);
    // Place accessed page into buffer
    struct Page page;
    page.pageNum = pageNum;
    buffer.push_back(page);
}

// Rolls the buffer array to the left, returns Page that rolls out.
void rollLeft(int pageNum) {
    struct Page removedPage = buffer.at(0);
    for (int i = 0; i < buffer.size()-1; i++) {
        buffer.at(i) = buffer.at(i+1);
    }
    buffer.pop_back();
    cout << " E" << removedPage.pageNum << endl;
}

void lruReplacement(int pageNum) {
    int oldestPageIndex = 0;
    // Find index of least recently used page in buffer
    for (int i = 0; i < buffer.size(); i++) {
        if (buffer.at(oldestPageIndex).timeLastUsed > buffer.at(i).timeLastUsed) {
            oldestPageIndex = i;
        }
    }
    // Replace least recently used page with accessed page in buffer
    struct Page page;
    page.pageNum = pageNum;
    page.timeLastUsed = pageAccessCount;
    buffer.at(oldestPageIndex) = page;
}



