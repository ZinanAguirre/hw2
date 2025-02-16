#include "movie.h"
#include <string>
#include <iostream>
#include <set>
#include <sstream>
#include <cctype>
#include <iomanip>
using namespace std;


Movie::Movie(const string category,const string name, double price, int qty, const string genre, const string rating): 
  Product(category, name, price, qty)
{
  this->genre = genre;
  this->rating = rating;


}

Movie::~Movie() 
{
}

set<string> Movie::keywords() const
{
  /* As genre and name are keywords they need to be seperated
    by word size greater >= 2 in order to be more generic and limited
  */
  set<string> related;
  string name = name_;
  string genre1 = genre;

  for (size_t i = 0; i < name.length(); ++i) {
    name[i] = std::tolower(name[i]);  // Convert each character to lowercase
  }

  related.insert(name);

  for (size_t i = 0; i < genre1.length(); ++i) {
      genre1[i] = std::tolower(genre1[i]);  // Convert each character to lowercase
  }

  related.insert(genre1);

  std::string combined = name_ + " " + genre;
  std::istringstream iss(combined);
  std::string word;

  while (iss >> word) {
    string current = word;
    for (size_t i = 0; i < current.length(); ++i) {
      current[i] = std::tolower(current[i]);  // Convert each character to lowercase
    }
    related.insert(current);
  
  }

  return related;
}

string Movie::displayString() const
{
  string output;
  std::ostringstream price;
  price << std::fixed << std::setprecision(2) << price_;
  string tempPrice = price.str();
  string tempQty = to_string(qty_);
  output += name_ + "\n" + "Genre: " + genre + " " + "Rating: " + rating + "\n" + tempPrice + " " + tempQty + " left." + "\n";
  return output;
}

void Movie::dump(ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre << "\n" << rating << endl;
}