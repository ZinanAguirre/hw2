#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include <string>
#include <set>
using namespace std;


class Clothing : public Product {
public:
  Clothing(const string category,const string name, double price, int qty, const string size, const string brand);
  ~Clothing();
  set<string> keywords() const;
  string displayString() const;
  void dump(ostream& os) const;

private:
  string size;
  string brand;
};
#endif