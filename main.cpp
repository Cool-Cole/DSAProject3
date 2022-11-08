#include <iostream>
#include <fstream>
#include "CSVparse.h"
#include "pixelUpdate.h"

using namespace std;

void pixelUpdateLoader(){
    ifstream csv("./CSVData/example.csv");

    string line;

    while(getline(csv, line)){
        vector<string> temp = stringToVector(line, ',');

        for(auto it = temp.begin(); it != temp.end(); it++){
            cout << it->c_str() << endl;
        }

        cout << "uwu" << endl;
    }

}

int main() {
    cout << "Hello, World!" << endl;

    pixelUpdateLoader();

    return 0;
}
