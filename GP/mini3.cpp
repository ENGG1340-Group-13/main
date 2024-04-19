#include <iostream>
#include "mini3.h"
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// REMEMBER to enlarge your output screen!!!

//The followings are the fragments
//A
string p1 = "  *\n **\n***\n";
//B
string p2 = "*  \n** \n***\n";
//C
string p3 = "  *\n  *\n***\n";
//D
string p4 = "*  \n*  \n***\n";
//E
string p5 = " **\n **\n***\n";
//F
string p6 = "** \n** \n***\n";
//G
string p7 = "***\n***\n***\n";

string L1_r = "*** ***\n*** ***\n*** ***\n\n";
string L2_r = "*** *** ***\n*** *** ***\n*** *** ***\n\n";

//The following is designed to change the color
string yellow = "\033[33m";
string blue = "\033[34m";
string green = "\033[32m";
string red = "\033[31m";
string clre = "\033[0m";

//The following are the answers
//Answer to L1.gi1
string a1 = yellow + "  * *  \n ** ** \n*** ***\n\n" + L1_r + L1_r + clre;
//Answer to L1.gi2
string a2 = yellow + "  * *  \n  * *  \n*** ***\n\n" + L1_r + L1_r + clre;
//Answer to L1.gi3
string a3 = yellow + " ** ** \n ** ** \n*** ***\n\n" + L1_r + L1_r + clre;
//Answer to L2.gi4
string a4 = yellow + "  * *  \n ** *  \n*** ***\n\n" + L1_r + L1_r + clre;
//Answer to L2.gi1
string a5 = yellow + "  * *** *  \n ** *** ** \n*** *** ***\n\n" + L2_r + L2_r + clre;
//Answer to L2.gi2
string a6 = yellow + "  * *    **\n ** *    **\n*** *** ***\n\n" + L2_r + L2_r + clre;
//Answer to L2.gi3
string a7 = yellow + "  * *** ** \n  * *** ** \n*** *** ***\n\n" + L2_r + L2_r + clre;
//Answer to L2.gi4
string a8 = yellow + "*    ** *  \n*    ** ** \n*** *** ***\n\n" + L2_r + L2_r + clre;

//The given shapes in Level 1
string gi1 = green + "*** ***\n*** ***\n**   **\n*     *\n" + clre;
string gi2 = green + "*** ***\n*** ***\n**   **\n**   **\n" + clre;
string gi3 = green + "*** ***\n*** ***\n*     *\n*     *\n" + clre;
string gi4 = green + "*** ***\n*** ***\n**   **\n*    **\n" + clre;
vector<string>L1gi;
vector<string>L1a2;
vector<string>L1a3;
vector<string>L1a4;
map < string, vector<string> > L1m;

//The given shapes in Level 2
string gi5 = green + "*** *** ***\n*** *** ***\n**       **\n*         *\n" + clre;
string gi6 = green + "*** *** ***\n*** *** ***\n**   ** *  \n*    ** *  \n" + clre;
string gi7 = green + "*** *** ***\n*** *** ***\n**        *\n**        *\n" + clre;
string gi8 = green + "*** *** ***\n*** *** ***\n ** *    **\n ** *     *\n" + clre;
vector<string>L2gi;
vector<string>L2a6;
vector<string>L2a7;
vector<string>L2a8;
map < string, vector<string> > L2m;

//These are the public variables that can be used in every functions
bool win = false;
string l1 = "A:  B:  C:  D:  E:  F:  G: \n";
string frag = blue + "Fragments: \n" + l1 + "  * *     * *    ** **  ***\n" + " ** **    * *    ** **  ***\n" + "*** *** *** *** *** *** ***\n" + clre;

//This is a function judging whether the player can pass in level 1
void f_L1(bool &win) {
    string ans2,ans3,ans4;
    L1gi.push_back(gi2);
    L1gi.push_back(gi3);
    L1gi.push_back(gi4);
    L1a2.push_back("CDGGGG");
    L1a2.push_back(a2);
    L1a3.push_back("EFGGGG");
    L1a3.push_back(a3);
    L1a4.push_back("ADGGGG");
    L1a4.push_back(a4);
    L1m[gi2] = L1a2;
    L1m[gi3] = L1a3;
    L1m[gi4] = L1a4;
    cout << "Welcome to LEVEL1!!!" << "\n" << "In this level, you will organize your fragments in a 3*2 block (each block is a 3*3 '*') with the order of completing the first row fromleft to right and go to the next row." << endl;
    cout << "If you still can't understand, don't worry! Let's have a look on an example!" << endl;
    cout << "when given the protein like this: " << "\n" << green << "*** ***\n*** ***\n**   **\n*     *\n" << clre << "You can escape by listing the fragments ABGGGG, which outputs" << "\n" << a1;
    sleep(1);
    cout << "Now get ready for fighting against the cells!!!" << endl;
    cout << "===============CASE 1!!===============" << endl;
    srand(time(NULL));
    int rindex2 = rand()%3;
    string truegi2 = L1gi[rindex2];
    cout << truegi2 << frag << "Your answer is: ";
    getline(cin, ans2);
    swap(L1gi[rindex2], L1gi[2]);
    L1gi.pop_back();
    if ( ans2 == L1m[truegi2][0]) {
        cout << L1m[truegi2][1];
        cout << "Great escape!\nReady for the 2nd one?" << endl;
        sleep(1);
        cout << "===============CASE 2!!!===============" << endl;
        srand(time(NULL));
        int rindex3 = rand()%2;
        string truegi3 = L1gi[rindex3];
        cout << truegi3 << frag << "Your answer is: ";
        getline(cin, ans3);
        swap(L1gi[rindex3], L1gi[1]);
        L1gi.pop_back();
        if ( ans3 == L1m[truegi3][0] ) {
            cout << L1m[truegi3][1];
            cout << "Excellent!\nReady for the last one?" << endl;
            sleep(1);
            cout << "===============CASE 3!!!===============" << endl;
            cout << L1gi[0] << frag << "Your answer is: ";
            getline(cin, ans4);
            if ( ans4 == L1m[L1gi[0]][0] ) {
                cout << L1m[L1gi[0]][1];
                cout << "What a great job!! You have escaped from all the immune cells!!" << endl;
                win = true;
            } else {
                return;
            }
        }else{
            return;
        }
    }else{
        return;
    }
}

//This is a function judging whether the player can pass in level 2
void f_L2(bool &win) {
    string ans6,ans7,ans8;
    L2gi.push_back(gi6);
    L2gi.push_back(gi7);
    L2gi.push_back(gi8);
    L2a6.push_back("ADEGGGGGG");
    L2a6.push_back(a6);
    L2a7.push_back("CGFGGGGGG");
    L2a7.push_back(a7);
    L2a8.push_back("DEBGGGGGG");
    L2a8.push_back(a8);
    L2m[gi6] = L2a6;
    L2m[gi7] = L2a7;
    L2m[gi8] = L2a8;
    cout << "Welcome to LEVEL2!!!" << "\n" << "In this level, you will organize your fragments in a 3*3 block (each block is a 3*3 '*') with the order of completing the first row fromleft to right and go to the next row." << endl;
    cout << "If you still can't understand, don't worry! Let's have a look on an example!" << endl;
    cout << "when given the protein like this: " << "\n" << green << "*** *** ***\n*** *** ***\n**       **\n*         *\n" << clre << "You can escape by listing the fragments AGBGGGGGG" << "\n" << a5;
    sleep(1);
    cout << "Now get ready for fighting against the cells!!!" << endl;
    cout << "===============CASE 1!!===============" << endl;
    srand(time(NULL));
    int rindex6 = rand()%3;
    string truegi6 = L2gi[rindex6];
    cout << truegi6 << frag << "Your answer is: ";
    getline(cin, ans6);
    swap(L2gi[rindex6], L2gi[2]);
    L2gi.pop_back();
    if ( ans6 == L2m[truegi6][0]) {
        cout << L2m[truegi6][1];
        cout << "Great escape!\nReady for the 2nd one?" << endl;
        sleep(1);
        cout << "===============CASE 2!!!===============" << endl;
        srand(time(NULL));
        int rindex7 = rand()%2;
        string truegi7 = L1gi[rindex7];
        cout << truegi7 << frag << "Your answer is: ";
        getline(cin, ans7);
        swap(L2gi[rindex7], L2gi[1]);
        L2gi.pop_back();
        if ( ans7 == L2m[truegi7][0] ) {
            cout << L2m[truegi7][1];
            cout << "Excellent!\nReady for the last one?" << endl;
            sleep(1);
            cout << "===============CASE 3!!!===============" << endl;
            cout << L2gi[0] << frag << "Your answer is: ";
            getline(cin, ans8);
            if ( ans8 == L2m[L2gi[0]][0] ) {
                cout << L2m[L2gi[0]][1];
                cout << "What a great job!! You have escaped from all the immune cells!!" << endl;
                win = true;
            } else {
                return;
            }
        }else{
            return;
        }
    }else{
        return;
    }
}

//This is the main funtion showing rules and judging the final result
int main(){
    int level;
    string levels;

    cout << "Welcome to the THIRD layer of the immune system -- the SPECIFIC IMMUNE SYSTEM!" << endl;
    cout << "In this layer, you will meet some SPECIFIC IMMUNE CELLS~~~" << endl;
    cout << "To get rid of their hunts, you should change the receptor on your protein coat to make the cells believe you are a member in the body." << endl;
    cout << "So, please select the correct fragments and list them in order according to the shape given by the immune cells."  << endl;
    cout << frag;
    /*cout << "Reminds that if you fail to pass one case, you will immediatedly quit of the game, and you can't get supplement of your blood flow." << endl;
    cout << "However, if you successfully pass all the cases in Level1, your blood flow and defense level will both increase 25%. If you pass all the cases in Level2, your blood flow and defense level will reach to 100%!!!" << endl;*/
    sleep(1);
    cout << "Please select the level you want to challenge first: (1 for Level 1, 2 for Level 2)" << endl;
    while (true) {
        getline(cin, levels);
        // Check if the input is empty or contains only whitespace
        if (levels.find_first_not_of(' ') == string::npos) {
            cout << "Invalid input. Please enter a valid level number." << endl;
            continue;
        }
        // Convert the input to an integer
        level = stoi(levels);
        // Check if the input is valid
        if (level == 1 || level == 2) {
            break;
        } else {
            cout << "Invalid input. Please enter a valid level number." << endl;
        }
    }
    if (level == 1) {
        f_L1(win);
    } else {
        f_L2(win);
    } 
    if (win) {
        cout << "CONGRATULATIONS!!! You have passed all the cases!" << endl;
    }else{
        cout << red << "Aho! You failed!" << clre << endl;
    }
    return 0;
}
