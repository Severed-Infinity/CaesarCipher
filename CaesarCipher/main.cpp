//
//  main.cpp
//  CaesarCipher
//
//  Created by david swift on 26/03/2015.
//  Copyright (c) 2015 david swift. All rights reserved.
//

#include <iostream>
#include "CaesarCipher.h"

int main(int argc, const char * argv[]) {
    
    std::string test = "Whose woods these are I think I know His house is in the village though He will not see me stopping here To watch his woods fill up with snow My little horse must think it queer To stop without a farmhouse near Between the woods and frozen lake The darkest evening of the year He gives his harness bells a shake To ask if there is some mistake The only other sounds the sweep Of easy wind and downy flake The woods are lovely dark and deep But I have promises to keep And miles to go before I sleep And miles to go before I sleep";
    int key = 2;
    std::string encrypt = cipher::caesarEncrypt(test, key);
    std::cout << encrypt << std::endl;
    std::cout << cipher::caesarDecryptWithKey(encrypt, key) << std::endl;
    
    std::cout << cipher::caeserDecrypt(encrypt) << std::endl;
    return 0;
}
