#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include "datastore.h"
#include "util.h"


class MyDataStore: public DataStore
{
  public:
      MyDataStore();
      virtual ~MyDataStore();
      void addProduct(Product* p);
      void addUser(User* u);
      std::vector<Product*> search(std::vector<std::string>& terms, int type);
      void dump(std::ostream& ofile);

      /* User will input a username and product from database to add to cart.
        These values will be added into a map where the key is the users and 
        values are queus of products that will represent as their carts.
      */
      void addToCart(User* u,Product* p);

      //User can view the usernames' cart of products using the map 
      void viewCart(User* u);

      // Will buy as many items from the usernames's cart 
      void buyCart(User* u);

      void quit(std::ostream& ofile);

      // Helper function to find users given the string of name of username that is inputted 
      User* findUser(std::string username);
      
  private:
  std::set<User*> users;
  std::set<Product*> products;
  std::map<User*, std::queue<Product*>> userCarts;
  std::map<std::string, std::set<Product*>> keywords;


};
#endif