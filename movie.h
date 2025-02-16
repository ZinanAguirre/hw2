#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include <string>
#include <set>
using namespace std;


class Movie : public Product {
public:
  Movie(const string category, const string name, double price, int qty, const string genre, const string rating);
  ~Movie();
  set<string> keywords() const;
  string displayString() const;
  void dump(ostream& os) const;

private:
  string genre;
  string rating;
};
#endif