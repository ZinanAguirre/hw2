#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include <string>
#include <set>
using namespace std;


class Book : public Product {
public:
  Book(const string category, const string name, double price, int qty, const string ISBN, const string author);
  ~Book();
  set<string> keywords() const;
  string displayString() const ;
  void dump(ostream& os) const;

private:
  string ISBN;
  string author;
};
#endif