using namespace std;
#include "mydatastore.h"
#include <sstream>
#include <iomanip>


MyDataStore::MyDataStore()
{

}

// Will deallocate all the memory that was created from makeProduct()
MyDataStore::~MyDataStore()
{
  for (std::set<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
      delete *it;  
  }

  for (std::set<User*>::iterator it = users.begin(); it != users.end(); ++it) {
      delete *it;  
  }
}

void MyDataStore::addProduct(Product* p)
{
  // Will insert to the sets of products from input database
  products.insert(p);

  /*To help create a relationship of common keywords and products
  as a user adds product, it will look at its keywords, and for each keywords
  they will be inserted to the keywords map. Then the prodcut will be inserted
  in the keyword's set of common products. Since keys cannot be repeated, it will not 
  create a new one and just be inserted into the queue it is related
  */
  set<string> current = p->keywords();
  for(set<string>::iterator it = current.begin(); it != current.end(); ++it){
    keywords[*it].insert(p);
  }
}

// Add users to the set users of database
void MyDataStore::addUser(User* u)
{
  users.insert(u);
}


std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  std::vector<Product*> combined;
  
  // change it to a set to allow set intersection function
  std::set<std::string> lowerTerms(terms.begin(), terms.end());

    // 0 means user inputted AND 
  if (type == 0) {  

      // We will look at every product in database
      for (std::set<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
        Product* curr = *it;

        // Find the set of keywords associated with the product
        std::set<std::string> currentKeywords = curr->keywords();
        
        // Produce a set that has all same elements from each products keywords and terms inputted
        std::set<std::string> intersection = setIntersection(currentKeywords, lowerTerms);
        
        // If they are the same size after intersection to the terms then they should be equal
        if (intersection.size() == lowerTerms.size()) {
          combined.push_back(curr);
        }
      }
  } 
  else { 
    /* Will go through every terms and see if it is in keyword map. If it is 
    then it will go to the value which is set of products that are matching a keyword,
    and since it is union then you can combine all of them to the vector.
    */
    for (std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it) {
      std::map<std::string, std::set<Product*>>::iterator it1 = keywords.find(*it);
      if (it1 != keywords.end()) {
        for (std::set<Product*>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
          combined.push_back(*it2);
        }
      }
    }
  }

    return combined;
}

void MyDataStore:: dump(std::ostream& ofile)
{
  ofile<< "<products>\n";
  if(!products.empty()){
    for(set<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
    Product* current = *it;
    current->dump(ofile);
  }
  }

  ofile << "</products>\n";
  ofile << "<users>\n";
  
  if(!users.empty()){
     for(set<User*>::iterator it = users.begin(); it != users.end(); ++it) {
     User* current = *it;
     current->dump(ofile);
    }
  }

  ofile << "</users>";

}

void MyDataStore::quit(std::ostream& ofile)
{
  for(set<User*>::iterator it = users.begin(); it != users.end(); ++it) {
    User* current = *it;
    ofile << current->getName() << current->getBalance() << "\n";
  }

  for(set<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
    Product* current = *it;
    ofile << current->getName() << "\n" << current->getQty() << "\n";
  }
}

// Easily add to usercart by map, as user as key and product as value
void MyDataStore::addToCart(User* u,Product* p)
{
   userCarts[u].push(p);
      
}

/* With user as parameter we will check if it is in usercart map,
is so then with the queue as its value, can iterate through each product.
Creating a temparory copy queue will be beneficial to not remove actual elements
as we are only viewing 
*/
void MyDataStore::viewCart(User* u) 
{
    int itemCount = 0;
    std::map<User*, std::queue<Product*>>::iterator it = userCarts.find(u);
    if(it == userCarts.end()){
      cout << "Invalid username";
      return;
    }
    else {
      std::queue<Product*> temp = it->second;
      while(!temp.empty()){
        itemCount += 1;
        cout << "Item " << itemCount << "\n";
        Product* now = temp.front();
        cout << now->displayString(); 
        temp.pop();
      }
    }

}

void MyDataStore::buyCart(User* u)
{
    std::map<User*, std::queue<Product*>>::iterator it = userCarts.find(u);
    if(it == userCarts.end()){
      cout << "Invalid username";
      return;
    }
    else {
      // By reference will get queue of username cart into current
      std::queue<Product*>& current = it->second;

      // this will be a new tempory queue that will be used if user cannot buy product
      std::queue<Product*> temp;
      Product* start = current.front();

      //Will remove all products from the cart
      while(!current.empty()){
        if((start->getQty() > 0) && ((it->first->getBalance()) >= (start->getPrice()))) {
            current.pop();
            start->subtractQty(1);
            it->first->deductAmount(start->getPrice());
            start = current.front();
        }
      // This else function will allow to save the products that could not be bought
        else{
          temp.push(current.front());
          current.pop();
        }
      }

      // Assign back the products that could not be bought to actual queue and not copy
      current = temp;
    }
}

// When user inputs username string, to find user we will look through users set of database
User* MyDataStore::findUser(std::string username) {
  for(std::set<User*>::iterator it = users.begin(); it != users.end(); ++it){
    User* curr = *it;
    if(curr->getName() == username) {
      return *it;
    }
  }
  return nullptr;
  
}
