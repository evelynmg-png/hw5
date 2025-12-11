#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
//#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle_help(
    int index,
    std::string& current,
    const std::string& in,
    std::string& float_left,
    const std::set<std::string>& dict,
    std::set<std::string>& result);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> result;
    // if ( in.empty()){
    //   return result;//no input 
    // }
    string current = in;

    string float_copy = floating;

    wordle_help(0, current, in, float_copy, dict, result);

    return result;

    // need to read in which has size/ letters in palce "-"
    // helper fucntion that looks through in
    //another that looks at the floating 
    // once that is determined we can look through dictionary 

    // if i do it this way will I i call a recurive fucntion for world itset?

}

// Define any helper functions here
void wordle_help(
    int index,
    std::string& current,
    const std::string& in,
    std::string& float_left,
    const std::set<std::string>& dict,
    std::set<std::string>& result)
    {
      

      // base cast checking that therrs no slots 
      int slots = in.size() - index;
      if ((int)float_left.size() > slots){
        return;
      }

      // prune implemention 


      //string current = in;
      // base case  where there are no more flaoting words
      //length has been met so that mesn a word has been created
      // if word is created and exsits in dictioanry then add to set
      if((int)in.size() == index){// compre ogioanl size with the word beign created 
        if (float_left.empty() && dict.count(current) == 1 ){// or floating_left[index]==NULL
           
            result.insert(current);  
          
        }
        return;
      }

      

      //looking for fixed letter to add into the word
      if (in[index] != '-'){
        current[index]= in[index];
        wordle_help(index+1, current, in, float_left, dict, result);
        return;
      }
      
      // try and find differen comobo of what potential word can go there
      // focus just on floats  
      //size_t float_size = float_left.size();
      for (size_t i=0; float_left.size() > i; i++){

        current[index]= float_left[i];

        char use = float_left[i];
        float_left[i] = float_left[float_left.size() -1];
        float_left[float_left.size() -1] = use;
        // string float_next = float_left;
        // char removed = float_left[i];
        // float_left.erase(i,1);
        float_left.pop_back();
        wordle_help(index+1, current, in, float_left, dict, result);
        float_left.push_back(use);
        float_left[float_left.size() -1] = float_left[i];
        float_left[i] = use;
          
      } 

      // any other letter in dicitonary 
      //char c = 'a';// might have to move outside/ if not it will continue to reset
      int remaining_slots = in.size() - index - 1;
      if ((int) float_left.size() <= remaining_slots){
        // as i loop will be finding possible combos
        for (char c='a'; c <= 'z'; c++){
          bool found = false;
          for (size_t i=0; i < float_left.size(); i++){
            if (float_left[i] == c){
              found = true;
              break;
            }
          }
          if (!found){ 
            current[index] = c;
            wordle_help(index+1, current, in, float_left, dict, result);

          }
          
        } 
      } 
      



    }