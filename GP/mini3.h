#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

//The following is the fragments
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
string clre = "\033[0m";

//The following is the answers
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
