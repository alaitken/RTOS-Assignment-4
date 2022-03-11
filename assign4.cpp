#include <string>
#include <iostream>
#include <vector>
using namespace std;

string getUserInput();
void print(string msg);
string getAlgorithmAndFrameInput();
string getPageInput();
void accessPage(int pageNum);

string algorithm = "";
int frameNums;

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
    print("algorithm> ");

    string input = getUserInput();
    int pivot = input.find(" ");

    if (pivot < 0 || pivot > input.length()) return "";

    algorithm = input.substr(0, pivot);

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

    // cout << algorithm << endl;
    // cout << frameNums << endl;

    return input;
}

string getPageInput() {
    print("page> ");
    return getUserInput();
}

void accessPage(int pageNum) {
    if (algorithm == "BELADY") {
        beldayReplacement();
    } else if (algorithm == "CLOCK") {
        clockReplacement();
    } else if (algorithm == "FIFO") {
        fifoReplacement();
    } else if (algorithm == "LRU") {
        lruReplacement();
    }
}

void beldayReplacement() {

}

void clockReplacement() {
    
}

void fifoReplacement() {
    
}

void lruReplacement() {
    
}



