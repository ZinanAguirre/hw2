#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

  std::set<std::string> keywords;

  //Given a long string of words, the sstream will allow to look at every word from space
  std::istringstream line(rawWords);

  std::string current;
  
  /* This function will for every word/phrase, will follow the condition
      that it is at least two characters and seperated by punctuation.
  */
  while(line >> current){
      std::string temp;
      for(unsigned int i = 0; i < current.size(); ++i){
          if(ispunct(current[i]) != 0){
              temp += tolower(current[i]);
          }
          else if (current[i] == '-'){
              temp += current[i];
          }
          else {
              if (temp.size() >= 2){
                keywords.insert(temp);
                temp.clear();
              }
              else {
                temp.clear();
              }
          }
    }
      if(temp.size() >= 2){
        keywords.insert(temp); 
      }
      else{
        temp.clear();
      } 
  }
  return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
