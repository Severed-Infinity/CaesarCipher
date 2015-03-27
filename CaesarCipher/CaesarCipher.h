//
//  CaesarCipher.h
//  CaesarCipher
//
//  Created by david swift on 26/03/2015.
//  Copyright (c) 2015 david swift. All rights reserved.
//

#ifndef __CaesarCipher__CaesarCipher__
#define __CaesarCipher__CaesarCipher__

#include <stdio.h>
#include <string>
#include <iostream>

//  http://www.xarg.org/2010/05/cracking-a-caesar-cipher/
//  using the php script at the this like as a reference
//  for producing the following code

namespace cipher {
  static std::string caesarEncrypt(std::string text, int offset){
    offset = offset % 26 + 26;
    std::string encryptedString = "";
    for (int i = 0; i < text.size(); ++i) {
      int ascii = text[i];
      if(97 <= ascii && ascii <= 123){
        encryptedString+=((ascii+offset+7)%26 + 97);
      } else if (65 <= ascii && ascii <= 91){
        encryptedString+=((text[i]+offset+13)%26 + 65);
      } else  {
        encryptedString+=text[i];
      }
    }
    return encryptedString;
  }
  
  static std::string caesarDecryptWithKey(std::string text, int offset){
    return caesarEncrypt(text, (26 - offset));
  }
  
//  http://stackoverflow.com/questions/7875581/c-get-index-of-char-element-in-array
//  for get position method
//  http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
//  for the sizeof porition
  
  static int getposition(int c, const int array[]) {
    for (size_t i = 0; i < (sizeof(array)/sizeof(array[0])) ; i++) {
      if (array[i] == c)
        return (int)i;
    }
    return -1;
  }
  
  static int caeserDecrypt(std::string text){
    char max = 0;
    double weight[] = { 6.51, 1.89, 3.06, 5.08, 17.4,
                        1.66, 3.01, 4.76, 7.55, 0.27,
                        1.21, 3.44, 2.53, 9.78, 2.51,
                        0.29, 0.02, 7.00, 7.27, 6.15,
                        4.35, 0.67, 1.89, 0.03, 0.04,
                        1.13};
    int ch[] = { 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0,
                  0};
    int search[] = { 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0,
                      0};
    for (int i = 0; i < text.size(); ++i) {
      int ascii = ((text[i] | 32) - 97);
      if(0 < ascii && ascii < 26){
        ++ch[ascii];
      }
    }
    
    for (int offset = 0; offset < 26; ++offset) {
      for (int i = 0; i < 26; ++i) {
        if (max < (search[offset]+=(0.01 * ch[i] * weight[(i + offset)%26]))) {
          max = search[offset];
        }
      }
    }
    
    for (int i = 0 ; i < 26; i++) {
      std::cout << search[i] << std::endl;
    }
    
    return (26 - getposition(max, search))%26;
  }
}

#endif /* defined(__CaesarCipher__CaesarCipher__) */
