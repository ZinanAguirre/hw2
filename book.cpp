#include "book.h"
#include <string>
#include <iostream>
#include <set>
#include <sstream>
#include <cctype>
#include <iomanip>
using namespace std;


Book::Book(const string category, const string name, double price, int qty, const string ISBN, const string author) :
 Product(category, name, price, qty)
{
  this->ISBN = ISBN;
  this->author = author;


}

Book::~Book()
{
 
}

set<string> Book::keywords() const
{
  set<string> related;
  string name = name_;
  string author1 = author;
  
  for (size_t i = 0; i < name.length(); ++i) {
      name[i] = std::tolower(name[i]);  // Convert each character to lowercase
  }

  related.insert(name);

  for (size_t i = 0; i < author1.length(); ++i) {
      author1[i] = std::tolower(author1[i]);  // Convert each character to lowercase
  }

  related.insert(author1);
  related.insert(ISBN);

  /* As author and name are keywords they need to be seperated
    by word size greater >= 2 in order to be more generic and limited
  */
  string combined = name_ + " " + author;
  std::istringstream iss(combined);
  string word;

  while (iss >> word) {
    string current = word;
    for (size_t i = 0; i < current.length(); ++i) {
        current[i] = std::tolower(current[i]);  // Convert each character to lowercase
    }
    related.insert(current);
  }

  return related;
}

string Book::displayString() const
{
  string output;
  std::ostringstream price;
  price << std::fixed << std::setprecision(2) << price_;
  string tempPrice = price.str();
  string tempQty = to_string(qty_);
  output += name_ + "\n" + "Author: " + author + " " + "ISBN: " + ISBN + "\n" + tempPrice + " " + tempQty + " left." + "\n";
  return output;
}

void Book::dump(ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" <<ISBN << "\n" << author << endl;
}