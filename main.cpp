#include <iostream>
#include <regex>
#include <sstream>
#include "Tree.h"

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

int main(){//parsing
    Tree tree;
    regex accPre("^printPreorder$");
    regex accIn("^printInorder$");
    regex accPost("^printPostorder$");
    regex accLevelCount("^printLevelCount$");
    regex accInsert("^insert \"([a-z A-Z]*)\" ([0-9]{8})$");
    regex accRemove("^remove ([0-9]{8})$");
    regex accRemoveIn("^removeInorder ([0-9]+)$");
    regex accNameSearch("^search \"([a-z A-Z]*)\"$");
    regex accIDSearch("^search ([0-9]{8})$");
    string line;
    getline(cin, line);
    int commands = stoi(line);
    for(int i = 0; i < commands; i++){
        getline(cin, line);
        istringstream command(line);
        if(regex_match(line, accPre)){
            tree.printPreOrder();
        }
        else if(regex_match(line, accIn)){
            tree.printInOrder();
        }
        else if(regex_match(line, accPost)){
            tree.printPostOrder();
        }
        else if(regex_match(line, accLevelCount)){
            tree.printLevelCount();
        }
        else if(regex_match(line, accInsert)){
            smatch matches;//smatch helps a lot with parsing, essentially substr
            if (regex_search(line, matches, accInsert)) {
                string name = matches[1].str();  // Extract name
                string id = matches[2].str();    // Extract ID
                if(!tree.idExists(id)){
                    tree.userInsert(id, name);
                    cout << "successful" << endl;
                }
                else{
                    cout << "unsuccessful" << endl;
                }
            }
        }
        //checking for edge cases in the input rather than actual function
        else if(regex_match(line, accRemove)){
            smatch matches;
            if(regex_search(line, matches, accRemove)){
                string id = matches[1].str();
                if(!tree.idExists(id)){
                    cout << "unsuccessful" << endl;
                }
                else{
                    tree.userRemove(id);
                    cout << "successful" << endl;
                }
            }
        }
        else if(regex_match(line, accRemoveIn)){
            smatch matches;
            if(regex_search(line, matches, accRemoveIn)){
                int N = stoi(matches[1].str());
                //n must be 1 less than amount of tree nodes
                if(N < 0 || N > tree.getNodeCount()-1){
                    cout << "unsuccessful" << endl;
                }
                else{
                    tree.removeInOrder(N);
                    cout << "successful" << endl;
                }
            }
        }
        else if(regex_match(line, accNameSearch)){
            smatch matches;
            if(regex_search(line, matches, accNameSearch)){
                string name = matches[1].str();
                tree.nameExists(name);
            }
        }
        else if (regex_match(line, accIDSearch)){
            smatch matches;
            if(regex_search(line, matches, accIDSearch)){
                string id = matches[1].str();
                if(tree.idExists(id)){
                    tree.printName(id);
                }
                else{
                    cout<< "unsuccessful" << endl;
                }
            }
        }
        else{
            cout << "unsuccessful" << endl;
        }
    }
    tree.~Tree();
    return 0;
}
