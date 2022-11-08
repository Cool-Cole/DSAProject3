#include <iostream>
#include <fstream>
#include "CSVparse.h"
#include "pixelUpdate.h"

using namespace std;

void pixelUpdateLoader(){
    ifstream csv("/CSVData/example.csv");

    string timestamp, user_id, pixel_color, coordinate;

    while(getline(csv, timestamp, ',')){
        getline(csv, user_id, ',');
        getline(csv, pixel_color, ',');
        getline(csv, pixel_color, ',');
        getline(csv, coordinate, ',');

        cout << "uwu" << endl;
    }

}

int main() {
    cout << "Hello, World!" << endl;
    // Dylan was here
    return 0;
}
