#include "clothing.h"
#include <string>
#include <iostream>
#include <set>
#include <sstream>
#include <cctype>
#include <iomanip>
using namespace std;


Clothing::Clothing(const string category,const string name, double price, int qty, const string size, const string brand): 
  Product(category, name, price, qty)
{
  this->size = size;
  this->brand = brand;


}

Clothing::~Clothing() {
}

set<string> Clothing::keywords() const
{
  /* As author and name are keywords they need to be seperated
    by word size greater >= 2 in order to be more generic and limited
  */
  set<string> related;
  string name = name_;
  string temp;
  string brand1 = brand;
  for (size_t i = 0; i < name.length(); ++i) {
      name[i] = std::tolower(name[i]);  
      if(isalnum(name[i]) != 0) {
          temp += name[i];
      }
      else{
        if(temp.length()>=2){
          related.insert(temp);
          temp.clear();
        }
        else{
          temp.clear();
        }
      }
    }

  if (temp.length()>= 2) {
    related.insert(temp);
  }
  else{
    temp.clear();
  }

  temp.clear();

  for (size_t i = 0; i < brand1.length(); ++i) {
        brand1[i] = std::tolower(brand1[i]);
        if(isalnum(brand1[i])!= 0) {
            temp += brand1[i];
        }
        else{
          if(temp.length() >= 2){
            related.insert(temp);
            temp.clear();
          }
          else{
            temp.clear();
          }
        }  
    }
    if(temp.length() >= 2){
      related.insert(temp);
    }

  return related;
}

string Clothing::displayString() const
{
  string output;
  std::ostringstream price;
  price << std::fixed << std::setprecision(2) << price_;
  string tempPrice = price.str();
  string tempQty = to_string(qty_);
  output += name_ + "\n" + "Size: " + size + " " + "Brand: " + brand + "\n" + tempPrice + " " + tempQty +  " left." +"\n";
  return output;
}

void Clothing::dump(ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size << "\n" << brand << endl;
}