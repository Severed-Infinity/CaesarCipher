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
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>
#include <math.h>
#include <queue>

//  http://www.xarg.org/2010/05/cracking-a-caesar-cipher/
//  using the php script at the this like as a reference
//  for producing the following code

namespace cipher {
  
  /*
   * Enum for deciding on how to format extra characters in incoming strings
   */
  enum excessChar {
    NONE,
    SPACE,
    All
  };
  
  /*
   *  @param std::string
   *    text to trim
   *  @param Enum excessChar
   *    trimming option
   *  @return std::string
   *    the trimmed text
   *
   *  given a string of text decide how the text should be trimed
   *  to remove extra characters or not. returning the trimmed
   *  string.
   */
  static std::string removeExcessChars(std::string text, excessChar excessChar){
    std::string noSpaceString = "";
    for (int i = 0; i < text.size(); i++) {
      switch (excessChar) {
        case NONE:
          noSpaceString+=text[i];
          break;
        case SPACE:
          if(text[i] != ' '){
            noSpaceString+=text[i];
          }
          break;
        case All:
          if('a' <= ::tolower(text[i]) && ::tolower(text[i]) <= 'z'){
            noSpaceString+=text[i];
          }
          break;
        default:
          break;
      }
    }
    return noSpaceString;
  }
  
  namespace caesar {
    
    /*
     *  @param std::string
     *    text to be encrypted
     *  @param int
     *    the character encode offset
     *  @return std::string
     *    encrypted text
     *
     *  given a string of text loop through each character
     *  and find the encrypted letter using the offset in
     *  modulo 26, building an encrypted string
     */
    static std::string encrypt(std::string text, int offset){
      offset = offset % 26 + 26;
      std::string encryptedString = "";
      for (int i = 0; i < text.size(); ++i) {
        int ascii = text[i];
        if(97 <= ascii && ascii <= 123){
          encryptedString+=((ascii+offset+7)%26 + 97);
        } else if (65 <= ascii && ascii <= 91){
          encryptedString+=((ascii+offset+13)%26 + 65);
        } else  {
          encryptedString+=ascii;
        }
      }
      return encryptedString;
    }
    
    /*
     *  @param std::string
     *    text to be decrypted
     *  @param int
     *    the character encode offset
     *  @return std::string
     *    decrypted text
     *
     *  the decrypt function used when the offset is known,
     *  given a string of text and an offset loop through
     *  each character and find the decrypted letter using
     *  the reserve offset in modue 26, building a decrypted
     *  string.
     */
    static std::string decryptWithKey(std::string text, int offset){
      std::cout << "DECRYPTING WITH OFFSET: " << offset << std::endl;
      return caesar::encrypt(text, (26 - offset));
    }
    
    //  http://stackoverflow.com/questions/7875581/c-get-index-of-char-element-in-array
    //  for get position method
    //  http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
    //  for the sizeof porition
    
    //    static int getposition(int c, const int array[]) {
    //      for (size_t i = 0; i < (sizeof(array)/sizeof(array[0])) ; i++) {
    //        if (array[i] == c)
    //          return (int)i;
    //      }
    //      return -1;
    //    }
    
    
    /*
     *  @param T[]
     *    an array of type T (char or int in this instance)
     *  @param T
     *    type T (char or int)
     *  @return int
     *    the index of param 2 in param 1
     *
     *  a helper method.
     *  given an array of type T find the corresponding index
     *  of param 2 if foind within param 1.
     */
    template <typename T, size_t N>
    static int getposition(const T (&array)[N], const T c)
    {
      const T* end = array + N;
      const T* match = std::find(array, array+N, c);
      return (end==match)? -1 : (int)std::distance(array, match);
    }
    
    /*
     *  @param std::string
     *    text to be decrypted
     *  @return std::string
     *    call to decrypt with key
     *  @warning text length < 100
     *    throw a warning if the text length is less than 100
     *
     *  the decrypted function used when the offset is unknown,
     *  using a brute force method loop through the text to
     *  calculate the best possible offset.
     *  if the text length is less than 100 then the accuracy
     *  off guessing the offset is lower.
     *  return a call to the decrypt with key method using the
     *  best guess offset.
     */
    static std::string decrypt(std::string text){
      std::cout << "DECRYPTING WITH BRUTE FORCE" << std::endl;
      int max = 0;
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
      if (text.length() < 100) {
        std::string bestGuess = "ENCODED MESSAGE TO SHORT TO BE ACCURATE\nBEST GUESS\n";
        return caesar::decryptWithKey(bestGuess+text, (26 - getposition(search, max))%26);
      }
      return caesar::decryptWithKey(text, (26 - getposition(search, max))%26);
    }
  }
  
  
  
  
  namespace vigenere {
    
    /*
     *  @param char
     *    any character
     *  @return int
     *    the position of the character in the english alphabet
     *
     *  a helper funciton for calculating the offset of a
     *  characters position
     */
    static int offset(char ch) {
      int offset = 0;
      char array[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
        'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
        'y', 'z'};
      for (int i = 0; i < 26; i++) {
        if(array[i] == ch){
          offset = i;
          break;
        }
      }
      return (offset%26 +26);
    }
    
    /*
     *  @param char
     *    any character
     *  @return char
     *    the character at the reverse position in the alphabet
     *
     *  a helper funciton for calculating the character at the
     *  same distance from the end of the alphabet as the input
     *  character is from the start of the alphabet
     */
    static char offsetGetChar(char ch) {
      int offset = 0;
      char array[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
        'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
        'y', 'z'};
      for (int i = 0; i < 26; i++) {
        if(array[i] == ch){
          offset = i;
          break;
        }
      }
      
      std::cout << array[26-offset] << std::endl;
      return array[26-offset];
    }
    
    /*
     *  @param std::string
     *    text to be encrypted
     *  @param std::string
     *    key used to encrypt text
     *  @return std::string
     *    encrypted text
     *
     *  given a string of text and a key used to encrypt the
     *  text loop taking groups of characters that same length
     *  as the key and encoding each character corresponding
     *  to the its relative position character in the key as an
     *  offset in module 26. then return the encrypted string.
     */
    static std::string encrypt(std::string text, std::string key){
      std::string encryptedString = "";
      for (int i = 0; i < text.size(); ++i) {
        for (int j = 0; j < key.size(); j++) {
          int ascii = text[i];
          if (i%key.size() == j) {
            if(97 <= ascii && ascii <= 123){
              encryptedString+=((ascii+vigenere::offset(key[j])+7)%26 + 97);
              //              break;
            } else if (65 <= ascii && ascii <= 91){
              encryptedString+=((ascii+vigenere::offset(key[j])+13)%26 + 65);
              //              break;
            } else  {
              encryptedString+=ascii;
              //              break;
            }
          }
        }
      }
      return encryptedString;
    }
    
    /*
     *  @param std::string
     *    text to be decrypted
     *  @param std::string
     *    key used to decrypt text
     *  @return std::string
     *    decrypted text
     *
     *  given a string of text and a key used to decrypt the
     *  text loop taking groups of characters that same length
     *  as the key and decoding each character corresponding
     *  to the its relative position character in the key as an
     *  offset (then getting the reserve offset) in module 26.
     *  then return the encrypted string.
     */
    static std::string decryptWithKey(std::string text, std::string key){
      std::string decryptedString = "";
      for (int i = 0; i < text.size(); ++i) {
        for (int j = 0; j < key.size(); j++) {
          int ascii = text[i];
          if (i%key.size() == j) {
            if(97 <= ascii && ascii <= 123){
              decryptedString+=((ascii-vigenere::offset(key[j])+7)%26 + 97);
              //              break;
            } else if (65 <= ascii && ascii <= 91){
              decryptedString+=((ascii-vigenere::offset(key[j])+13)%26 + 65);
              //              break;
            } else  {
              decryptedString+=ascii;
              //              break;
            }
          }
        }
      }
      return decryptedString;
    }
    
    
    //    http://www.wikiwand.com/en/Index_of_coincidence
    //    for the index of coindence algorithm
    
    /*
     *  @param const std::string &
     *    encrypted text
     *  @return double
     *    index of coindence
     *
     *  @error coindence < 0.038466
     *    random text
     *  @error 0.052 > coindence or coindence > 0.070
     *    text is not in english
     *  @error 0.067 > coindence or coindence > 0.0667
     *    text maybe in english
     *
     *  given a string of text calculate its index of coindence
     *  (how likely a piece of text is a certain language) and
     *  then return the calculated index. 
     *  depending on how out of range the index of coindence is
     *  from the english language index of coindence throw
     *  various errors.
     */
    static double indexOfCoincidence(const std::string &text){
      std::string coindenceText = text;
      std::transform(coindenceText.begin(), coindenceText.end(), coindenceText.begin(), ::toupper);
      
      std::map<char, int> kappaTextMap;
      double sumKappaText = 0;
      double kappa = (coindenceText.length()*(coindenceText.length()-1));
      
      for (int i = 0; i < 26; i++) {
        for (int j = 0; j < coindenceText.size(); j++) {
          int numJ = 0;
          for (int k = j; k < coindenceText.size(); k++) {
            if (coindenceText[k] == coindenceText[j]) {
              numJ++;
            }
          }
          kappaTextMap.insert({coindenceText[j], numJ});
        }
      }
      
      for (auto it = kappaTextMap.begin(); it != kappaTextMap.end(); it++) {
//                std::cout << it->first << "\t" << it->second << std::endl;
        sumKappaText += it->second *(it->second -1);
      }
      
      double coindence = sumKappaText / kappa;
      //      std::cout << coindence << " = " << sumKappaText << "/" << kappa << std::endl;
      if (coindence < 0.038466) {
        std::cout << "ERROR: text appears to be random letters, index " << coindence << std::endl;
      } else if ( 0.052 > coindence || coindence > 0.070 ){
        std::cout << "ERROR: text is not an english message, index " << coindence << std::endl;
      } else if ( 0.067 > coindence || coindence > 0.0667 ){
        std::cout << "ERROR: text is likely not an english message, index " << coindence << std::endl;
      }
      return coindence;
    }
    
    //    http://crypto.stackexchange.com/questions/333/how-does-the-index-of-coincidence-work-in-the-kasiki-test
    //    used the freidman method algorithm, which is found on the index of coincidence wiki page but not on english version
    
    /*
     *  @param double
     *    index of coindence
     *  @param const std::string &
     *    encrypted text
     *  @return int
     *    keyword length
     *
     *  using friedmans method using the calculated index of coindence
     *  and the length of the encrypted message calculate the possible
     *  keyword length and return the lenght of the potential keyword.
     */
    static int friedmansMethod(double indexOfCoindence, const std::string &text){
      long k = text.length();
      double Es = 0.067;
      double n = 26;
      
      double keywordLenght = (((Es - (1/n))*k) /(((k-1)* indexOfCoindence) - (k *(1/n)) + Es));
      
//            std::cout << "Es:\t" << Es << "\nk:\t" << k << "\n1/n\t" << (1/n) << "\nIC\t" << indexOfCoindence<<  std::endl;
//      std::cout << keywordLenght << std::endl;
      return ceil(keywordLenght);
    }
    
    
//    https://www.youtube.com/watch?v=EABrpIipHBs
//    used the video as a reference
    
    /*
     *  @param const std::map<char, double> &
     *    character frequencies map
     *  @return std::vector<char>
     *    possible characters
     *    sorted by most likely to least likely
     *
     *  a helper function used to calculate the the relation-
     *  ship between a map of characters and their frequencies
     *  against frequencies of the english alphabet, returning
     *  a vector of possible characters in sorted by likelihood
     */
    static std::vector<char> correlationOfFrequencies(const std::map<char, double> &charFreq){
      char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
        'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
        'y', 'z'};
      double english[26] = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015,
                6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095,
                5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074};
//      double max = 0;
//      char key = '\0';
      std::priority_queue<std::pair<double, char>> possibleKey;
      for (int i = 0; i < 26; i++) {
        double x = 0;
        for (auto it = charFreq.begin(); it != charFreq.end(); it++) {
          int c = 0;
          for (int j = 0; j < 26; j++) {
            if (it->first == alphabet[j]) {
              c = j;
            }
          }
          double y = it->second*((english[(c-i)%26])*0.01);
//          std::cout << it->first << " " << y << " = " << it->second << "*((" << c << "-" << i << ")%26)"<< std::endl;
          x+=y;
        }
        possibleKey.push({x, alphabet[i]});
//        if(x > max){
//          max = x;
//          key = alphabet[i];
//        }
        
//        std::cout << "i: " << i << " " << x << std::endl;
      }
      std::vector<char> possibleKeyChars;
      for (int i = 0; i < 26; i++) {
        std::cout << possibleKey.top().second << " " << possibleKey.top().first << std::endl;
        possibleKeyChars.push_back(possibleKey.top().second);
        possibleKey.pop();
      }
      
//      std::cout << "max: " << max << "\nkey: " << key << std::endl;
      return possibleKeyChars;
    }
    
//    http://www.geeksforgeeks.org/print-all-combinations-of-given-length/
//    code below directly taken to get all key combinations with a slight modification
    
    // The main recursive method to print all possible strings of length k
    /*
     *  @param const std::string &
     *    encrypted text
     *  @param std::vector<std::vector<char>>
     *    possible keys
     *  @param std::string 
     *    key
     *  @param int
     *    size of possible key vector
     *  @param int
     *    length of the key
     *
     *  a recursive function used to print out all possible
     *  keys with the possible decrypted text alongside it.
     */
    static void printAllKLengthRec(const std::string &text, std::vector<std::vector<char>> possibleKeys, std::string key, int n, int k) {
      
      // Base case: k is 0, print prefix
      if (k == 0) {
        std::cout << key << std::endl;
        std::cout << decryptWithKey(text, key) << std::endl;
        return;
      }
      
      // One by one add all characters from set and recursively
      // call for k equals to k-1
      for (int i = 0; i < n; ++i) {
        
        // Next character of input added
//        std::string newPrefix = prefix + possibleKeys[i];
        for (int j = 0; j < possibleKeys[i].size(); j++) {
          printAllKLengthRec(text, possibleKeys, key + possibleKeys[i][j], n, k - 1);
        }
        
        // k is decreased, because we have added a new character
//        printAllKLengthRec(possibleKeys, prefix, n, k - 1);
      }
    }
    
    /*
     *  @param const std::string &
     *    encrypted text
     *  @param std::vector<std::vector<char>>
     *    possible keys
     *  @param int
     *    length of the key
     *
     *  a simplfied calling function for its recurive form.
     */
    static void printAllKLength(const std::string &text, std::vector<std::vector<char>> possibleKeys, int k) {
      int n = (int)possibleKeys.size();
      printAllKLengthRec(text, possibleKeys, "", n, k);
    }
    
    /*
     *  @param int
     *    keyword length
     *  @para const std::string &
     *    encrypted text
     *
     *  @error keyword length < 0
     *    negative keyword length
     *  
     *  given a keyword length and a string of encrypted 
     *  text calculate the frequency of characters by
     *  columns based on the keyword length.
     *  for each column calculate the correlation of
     *  frequency. then print out all possible keys along-
     *  side the potiental decrypted text.
     *
     *  return the best guess key... always null.
     */
    static std::string frequencyAnalysis(int keywordLength, const std::string &text){
      std::string key = "";
      if (keywordLength < 0) {
        std::cout << "ERROR: negative keyword length " << std::endl;
//        keywordLength = keywordLength*(-1);s
        return key;
      }
      std::vector<std::string> textColumns(keywordLength);
      std::vector<std::vector<char>> possibleKeys;
      
      for (int i = 0; i < text.size(); i++) {
        for (int j = 0; j < keywordLength; j++) {
          if (i%keywordLength == j) {
            textColumns[j] += text[i];
          }
        }
      }
      for (int i = 0; i < textColumns.size(); i++) {
        std::cout << textColumns[i] << std::endl;
//        frequency portion
//        count the letter occurances
        std::map<char, double> charFreq;
        double textLength = textColumns.at(i).size();
        for (int j = 0; j < textColumns.at(i).size(); j++) {
          double letterCount = 0;
          for (int k = j; k < textColumns.at(i).size(); k++) {
            if (textColumns.at(i).at(j) == textColumns.at(i).at(k)) {
              letterCount++;
            }
          }
          if(charFreq.count(textColumns.at(i).at(j)) == 0){
            double freq = letterCount/textLength;
//            std::cout << "freq "  << textColumns.at(i).at(j) << " " <<  freq << std::endl;
            charFreq.insert({textColumns.at(i).at(j), freq});
          }
          
//          std::cout << textColumns.at(i).at(j) << " " << letterCount << std::endl;
        }
        
        std::vector<char> possibleKeyChar = correlationOfFrequencies(charFreq);
        possibleKeys.push_back(possibleKeyChar);
        
        printAllKLength(text, possibleKeys, keywordLength);
        
//        calculate the best frequency of the letter
//        char bestChar = '\0';
//        double bestFreq = 0.0;
//        for (auto it = charFreq.begin(); it != charFreq.end(); it++) {
////          std::cout << it->first << " " << it->second/textColumns.at(i).size() << std::endl;
//          if (bestFreq < it->second/textColumns.at(i).size()) {
//            bestFreq = it->second/textColumns.at(i).size();
//            bestChar = it->first;
//          }
//        }
//        std::cout << "\n" << bestChar << " " << bestFreq << "\n" << std::endl;
      }
      
//      for (int i = 0; i <possibleKeys.size(); i++) {
//        std::string possibleKey = "";
//        for (int j = 0; j < possibleKeys.at(i).size(); j++) {
//          possibleKey += possibleKeys.at(i).at(j);
//          std::cout << "possible key " << possibleKey << std::endl;
//        }
//      }
      
      std::cout << key << std::endl;
      return key;
    }
    
    /*
     *  @param const std::string &
     *    encrypted text
     *  @param Enum excessChar
     *    trimming option
     *
     *  @error keyword length >= text length
     *    one time pad detected
     *
     *  a container function for calling the excess character
     *  option, followed by the index of coindence and freidmans
     *  method. using the results to calculate the possible key
     *  and decrypt the text.
     */
    static void decrypt(const std::string &text, excessChar excessChar){
      std::string message = "";
      switch (excessChar) {
        case NONE:
          message = removeExcessChars(text, excessChar);
          break;
        case SPACE:
          message = removeExcessChars(text, excessChar);
          break;
        case All:
          message = removeExcessChars(text, excessChar);
          break;
        default:
          break;
      }

      double index = cipher::vigenere::indexOfCoincidence(message);
      std::cout << "index: " << index << " normalised " << index*26 << std::endl;
      
      
      int keywordLength = cipher::vigenere::friedmansMethod(index, message);
      std::cout << "keyword length " << keywordLength << std::endl;
      if (text.length() <= keywordLength) {
        std::cout << "ERROR: one time pad detected" << std::endl;
        return;
      }
      
      std::string key = cipher::vigenere::frequencyAnalysis(keywordLength, message);
      std::cout << cipher::vigenere::decryptWithKey(message, key) << std::endl;
    }
    
    
    
    
//  various different attempts
    
//    static void frequencyAnalysis(int keywordLength, const std::string &text){
//      double english[26] = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015,
//        6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095,
//        5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074};
//      char array[keywordLength][text.size()];
//      
//      std::cout << "keyword length " << keywordLength << std::endl;
//      std::string key = "";
//      
//      for (int i = 0; i < keywordLength; i++) {
//        for (int j = 0; j < text.size(); j++) {
//          if (j%keywordLength == i) {
//            array[i][j] = text[j];
//          }
//        }
//      }
//      
//      
//      for (int i = 0; i < keywordLength; i++) {
//        std::map<char, int> frequency;
//        for (int j = 0; j < text.size(); j++) {
//          int numJ = 0;
//          
//          for (int k = j; k < text.size(); k++) {
//            if(text[k] == text[j]){
//              numJ++;
//            }
//          }
//          frequency.insert({text[j], numJ});
////          for (int i = 0; i < 26; i++) {
////            for (int j = 0; j < coindenceText.size(); j++) {
////              int numJ = 0;
////              for (int k = j; k < coindenceText.size(); k++) {
////                if (coindenceText[k] == coindenceText[j]) {
////                  numJ++;
////                }
////              }
////              kappaTextMap.insert({coindenceText[j], numJ});
////            }
////          }
////          if(array[i][j] == '\0'){
////            
////          } else {
////            std::cout << "array[" << i << "][" << j << "] " << array[i][j] << std::endl;
////          }
//          
//        }
//        char bestChar = '\0';
//        int bestFreq = 0;
//        for (auto it = frequency.begin(); it != frequency.end(); it++) {
//          std::cout << it->first << "\t" << it->second << std::endl;
//          if (it->second > bestFreq) {
//            bestFreq = it->second;
//            bestChar = it->first;
//          }
//        }
//        key+=bestChar;
//        std::cout << "best char at key position " << i << " " << bestChar << std::endl;
//        
//      }
//      std::cout << key << std::endl;
//    }
//    
//    static void freq2(int keywordLength, const std::string &text){
//      std::vector<std::string> keyMap(keywordLength);
//      char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
//        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
//        'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
//        'y', 'z'};
//      
//      std::string key ="";
//      std::cout << "building key map" << std::endl;
//      for (int i = 0; i < keyMap.size(); i++) {
//        for (int j = 0; j < text.size(); j++) {
//          if (j%keywordLength == i) {
//            keyMap[i] += text[j];
//          }
//        }
//      }
//      
//      std::cout << "finding key" << std::endl;
//      for (int i = 0; i < keyMap.size(); i++) {
//        std::cout << "analysing : " << keyMap[i] << std::endl;
//        int max = 0;
//        double weight[] = { 6.51, 1.89, 3.06, 5.08, 17.4,
//          1.66, 3.01, 4.76, 7.55, 0.27,
//          1.21, 3.44, 2.53, 9.78, 2.51,
//          0.29, 0.02, 7.00, 7.27, 6.15,
//          4.35, 0.67, 1.89, 0.03, 0.04,
//          1.13};
//        int ch[] = { 0, 0, 0, 0, 0,
//          0, 0, 0, 0, 0,
//          0, 0, 0, 0, 0,
//          0, 0, 0, 0, 0,
//          0, 0, 0, 0, 0,
//          0};
//        int search[] = { 0, 0, 0, 0, 0,
//          0, 0, 0, 0, 0,
//          0, 0, 0, 0, 0,
//          0, 0, 0, 0, 0,
//          0, 0, 0, 0, 0,
//          0};
////        std::cout << "building char array" << std::endl;
//        for (int j = 0; j < keyMap[i].size(); ++j) {
//          int ascii = ((keyMap[i][j] | 32) - 97);
//          if(0 < ascii && ascii < 26){
//            ++ch[ascii];
//          }
//        }
////        std::cout << "finding the max char" << std::endl;
//        for (int offset = 0; offset < 26; ++offset) {
////          std::cout << "inside loop" << std::endl;
//          for (int j = 0; j < 26; ++j) {
//            if (max < (search[offset]+=(0.01 * ch[j] * weight[(j + offset)%26]))) {
//              max = search[offset];
////              std::cout << max << std::endl;
//            }
//          }
//        }
//        std::cout << alphabet[max] << std::endl;
//        key+= alphabet[max];
//      }
//      std::cout << key << std::endl;
//    }
//
    
    //    https://www.ktbyte.com/paste/Cracking-Vigenere-Cipher-using-Frequency-Analysis-in-Java/PU4J4U65Us0m7WiS2J39
    //    used to create the splitInterLeave and for creating the decryption brute force method
//    
//    static std::vector<std::string> splitInterleave(std::string text, int keyLength){
//      //      std::cout << "enter" << std::endl;
//      std::vector<std::string> inter(keyLength);
//      for (int i = 0; i < keyLength; i++) {
//        inter[i] = "";
//      }
//      for (int j = 0; j < text.size(); j++) {
//        //        std::cout << j << std::endl;
//        //        std::cout << text[j] << std::endl;
//        inter[j % keyLength] += text[j];
//      }
//      std::cout << "returning " << std::endl;
//      return inter;
//    }
//    
//    static std::string minVigenre(std::string text){
//      std::string best = "";
//      for (int i = 65; i < 123; i++) {
//        if(91 > i && i < 97){
//          i = 97;
//        }
//        best = min(best, vigenere::decryptWithKey(text, (&"" [ (char)i])));
//      }
//      std::cout << best << std::endl;
//      return best;
//    }
//    
//    static void decrypt(std::string text, int maxKeySize){
//      std::string best;
//      for(int keyLength = 1; keyLength <= maxKeySize; keyLength++){
//        std::cout << "loop " << keyLength << std::endl;
//        std::vector<std::string> inter = vigenere::splitInterleave(text, keyLength);
//        std::vector<std::string> decryptedInterleave(keyLength);
//        
//        for (int i = 0; i < keyLength; i++) {
//          decryptedInterleave[i] = vigenere::minVigenre(inter[i]);
//        }
//        
//        std::stringstream decryptedMessage;
//        for (int j = 0; j < text.size(); j++) {
//          decryptedMessage << decryptedInterleave[j % keyLength][j/keyLength];
//          
//        }
//        std::cout << decryptedMessage.str() << std::endl;
//        best = min(best, decryptedMessage.str());
//        //        decryptedMessage = "";
//        //        std::cout << "temp best " << best << std::endl;
//      }
//      
//      std::cout << "best " << best << std::endl;
//    }
//    
    
    
    
    
  }
}

#endif /* defined(__CaesarCipher__CaesarCipher__) */
