#include "avl.h"
using namespace std;

int main() {
    string cmd;
    int k, v;
    avltree tree;
    try {
        while (cin >> cmd ) {
            try { 
                if ( cmd == "r" ) { //reset the avl tree to base form
                    tree.reset();
                } else if ( cmd == "x" ) { // exit
                    exit(0);
                } else if ( cmd == "i" ) { //insert key valye pair
                    cin >> k >> v;
                    tree.insert(k, v);
                } else if ( cmd == "d" ) { //delete key
                    cin >> k;
                    tree.remove(k);
                } else if ( cmd == "s" ) { //search key
                    cin >> k;
                    tree.search(k);
                } else if (cmd == "p") { //print at root
                    tree.print();
                } else {
                    throw std::invalid_argument(cmd + " is Invalid syntasx");
                }
            } catch (std::invalid_argument & e) {
                std::cerr << e.what() << std::endl;
                exit(1);
            }  // catch
        }
    } catch(ios::failure &) {
        cerr << "invalid" << endl;
        exit(2);
    }
}