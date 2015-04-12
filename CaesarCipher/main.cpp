//
//  main.cpp
//  CaesarCipher
//
//  Created by david swift on 26/03/2015.
//  Copyright (c) 2015 david swift. All rights reserved.
//

#include <iostream>
#include "CaesarCipher.h"
#include <array>
//#include <map>

int main(int argc, const char * argv[]) {
    
    std::string test = "Whose woods these are I think I know His house is in the village though He will not see me stopping here To watch his woods fill up with snow My little horse must think it queer To stop without a farmhouse near Between the woods and frozen lake The darkest evening of the year He gives his harness bells a shake To ask if there is some mistake The only other sounds the sweep Of easy wind and downy flake The woods are lovely dark and deep But I have promises to keep And miles to go before I sleep And miles to go before I sleep";
    std::string test2 = "Welcome to the jungle";
    std::string test3 = "david";
    std::string test4 = "helloworld";
//    int key = 2;
//    std::string encrypt = cipher::caesar::encrypt(test, key);
//    std::cout << encrypt << std::endl;
//    std::string encrypt2 = cipher::caesar::encrypt(test2, 3);
//    std::cout << encrypt2 << std::endl;
//    std::string encrypt3 = cipher::caesar::encrypt(test3, 4);
//    std::cout << encrypt3 << std::endl;
//    std::cout << cipher::caesar::decryptWithKey(encrypt2, 3) << std::endl;
    
//    std::cout << cipher::caesar::decrypt(encrypt2) << "\n" << std::endl;
    
    std::cout << "Vigenere Cipher" << "\n" << test2 << std::endl;
    std::string ca = "qmcmfvw zsukdidg mn t mssu sn t cmnfv wbel lbrgxcmff xrxpw soh mtcqsmedx doafw shxitphy vlpdt con, jsm brsppv ivmtx dpgxpy t rmjm aims osmiiwzwupte xjik dileztzbre ywsofvs hq cwmpop lrv hvexy xgxirbyk gwir rzyj iiaw wsgl jok elw hmre hmli xhx dyf jr hxc iqfw ago wzf'w ghyi dvgy by xzf wkr hmli hitxsfew lnnc ao xhx doq xmta omsnsnwd pmdc ig elw toy ptxz emafzrvt eh yzpdpa hxc hgxr th l fjjhgx mc s gsugeeao ahxci jpgkbyk zpvsx aigqpe xlx ebvsaxedmsw itik fzekjsff wmbwik bw yhf hjjjt ilwl ule ywsofvs msel hvop ds aogrxomtmc hbrl ffasiltws xaqtw sqtetc sf ule lssjf aabemfh xo mlow zsu theq dpifm mf ule ulgc xmta jsms leto mf ule vwsmew ago cgv've zzrw mycr tr lii sdj aaul dblqgohs efgq jr tap wcz aims habqogow dvgy by xzf wkr hmli hitxsfew aa amuuyrx jsmsweeq sf b xrttr ao e smlxapr wbel hmesmtgaoi phcxwsw wbel dpskbyk ymesl emwt wuwoifmc shxigoi il elwsi am elw uyrgdxami tap kasp wbel lii ktwiaessvztw fcel wyuz mn msi klc wbel vjemhyhk mycr tr lii sdj aaul dblqgohs efgq jr tap wcz aims habqogow si puvj mf ule lvc ojxh wteeprdl wyuz mn msi klc wbel vjemhyhk mycr tr lii sdj aaul dblqgohs ts pmdc ig elw toy ptxz emafzrvt puvj mf ule lvc ojxh wteeprdl wyuz mn msi klc wbel vjemhyhk";
    
    std::string caNoSpace = cipher::removeExcessChars(ca, cipher::excessChar::SPACE);
    std::string encryptV = cipher::vigenere::encrypt(test2 , "bcd");
    std::cout << "encrypted: \n" <<  encryptV <<"\n"<< std::endl;
//    std::cout << "decrypted: \n" << cipher::vigenere::decryptWithKey(encryptV, "bcd") << std::endl;
//    std::cout << "\nCA test \n" << ca << std::endl;
    std::string cain = "picture yourself in a boat on a river with tangerine trees and marmalade skies somebody calls you, you answer quite slowly a girl with kaleidoscope eyes cellophane flowers of yellow and green towering over your head look for the girl with the sun in her eyes and she's gone lucy in the sky with diamonds lucy in the sky with diamonds lucy in the sky with diamonds ah follow her down to a bridge by a fountain where rocking horse people eat marshmallow pies everyone smiles as you drift past the flowers that grow so incredibly high newspaper taxis appear on the shore waiting to take you away climb in the back with your head in the clouds and you're gone lucy in the sky with diamonds lucy in the sky with diamonds lucy in the sky with diamonds ah picture yourself on a train in a station with plasticine porters with looking glass ties suddenly someone is there at the turnstile the girl with the kaleidoscope eyes lucy in the sky with diamonds lucy in the sky with diamonds lucy in the sky with diamonds ah lucy in the sky with diamonds lucy in the sky with diamonds lucy in the sky with diamonds ah lucy in the sky with diamonds lucy in the sky with diamonds lucy in the sky with diamonds";
    std::string caout = cipher::vigenere::encrypt(cain, "beatles");
//    std::cout << caout << std::endl;
//    std::cout << cipher::vigenere::decryptWithKey(caout, "beatles") << std::endl;
    
//    cipher::vigenere::decrypt(caNoSpace, 7);
    
//    double index = cipher::vigenere::indexOfCoincidence(encryptV);
//    std::cout << "index: " << index << " normalised " << index*26 << std::endl;
//    int keywordLength = cipher::vigenere::friedmansMethod(index, encryptV);
//    std::cout << "keyword length " << keywordLength << std::endl;
//    std::string key = cipher::vigenere::freqAnal(keywordLength, encryptV);
//    std::cout << cipher::vigenere::decryptWithKey(encryptV, key) << std::endl;
    cipher::vigenere::decrypt(ca, cipher::excessChar::SPACE);
    return 0;
}
