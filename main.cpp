#include <iostream>
#include <fstream>
#include "CSVparse.h"
#include "pixelUpdate.h"
#include "bplustree.h"

using namespace std;


#include <iostream>
#include <fstream>
#include "CSVparse.h"
#include "pixelUpdate.h"
#include "bplustree.h"

using namespace std;


int main() {
    cout << "Hewwo, World!" << endl;

    //pixelUpdateLoader();
    bplusTree node;
    /*node.insert(new pixelUpdate("ovTZk4GyTS1mDQnTbV+vDOCu1f+u6w+CkIZ6445vD4XN8alFy/6GtNkYp5MSic6Tjo/fBCCGe6oZKMAN3rEZHw=="));
    node.insert(new pixelUpdate("6NSgFa1CvIPly1VniNhlbrmoN3vgDFbMSKqh+c4TTfrr3dMib91oUWONX96g5PPcioIxedF24ldNOu/g5yqDrg=="));
    node.insert(new pixelUpdate("O5Oityp3Z3owzTuwM9XnMggpLcqKEumsOMKGhRiDTTImWbNLhLKmLI4gn1QPbaABqZqmFC/OmE/O732n39dGIQ=="));
    node.insert(new pixelUpdate("tc273UiqS0wKa6VwiOs/iz/t4LyPYrhL2Q347awn11IQQELrEzZBCmGe28NWM+O1IdfH4CieCpEnE5sHecW9Ow=="));
    node.insert(new pixelUpdate("OOWsU/HLb4UUkQwclDeXFtsJTOXMlAdNHiRpFA1Qk+SxUrJE7lpGFevfV9w+zImFimmNANlDdfN3kluz69M9MQ=="));*/
    /*node.insert(new pixelUpdate("5"));
    node.insert(new pixelUpdate("15"));
    node.insert(new pixelUpdate("25"));
    node.insert(new pixelUpdate("35"));
    node.insert(new pixelUpdate("45"));
    node.insert(new pixelUpdate("55"));
    node.insert(new pixelUpdate("40"));
    node.insert(new pixelUpdate("30"));
    node.insert(new pixelUpdate("20"));
    node.insert(new pixelUpdate("31"));
    node.insert(new pixelUpdate("56"));
    node.insert(new pixelUpdate("54"));
    node.insert(new pixelUpdate("32"));
    node.insert(new pixelUpdate("10"));*/
    ifstream csv("./CSVData/example.csv");
    string line;
    //Throws out the titles from the original csv.
    getline(csv, line);
    while(getline(csv, line)) {
        vector<string> pixelDataRAW = stringToVector(line, ',');
        node.insert(new pixelUpdate(pixelDataRAW.at(1)));
    }


    node.printbplusTree(node.getRoot());
    node.search("OOWsU/HLb4UUkQwclDeXFtsJTOXMlAdNHiRpFA1Qk+SxUrJE7lpGFevfV9w+zImFimmNANlDdfN3kluz69M9MQ==");
    //node.search("15");

    return 0;
}

