#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int FOID = 0;
int INGID = 0;
int successs = 0;
string ingname, foodname, foodprice, menuname, ingcheck,un,ps;
int ingcount, foodcount, CIng, idcount, midcount, trucount, idcheckformenu,
    idcheckforfood;
vector<string> ings;
vector<string> foods;
void transferdata(string name, int cing) {
  ifstream myfile("ingredient.txt");
  ofstream out_file{"copy.txt"};
  if (myfile && out_file) {
    while (myfile >> ingname >> CIng) {
      if (ingname == name) {
        out_file << ingname << " " << cing << "\n";
      } else
        out_file << ingname << " " << CIng << "\n";
    }
  } else {
    printf("Cannot read File");
  }
  myfile.close();
  out_file.close();
  if (remove("ingredient.txt") == 0) {
    cout << endl;
  }
  if (rename("copy.txt", "ingredient.txt") != 0)
    cout << endl;
}
bool changeCIng(string keyword) {
  ifstream myfile("ingredient.txt");
  while (myfile >> ingname >> CIng) {
    if (keyword == ingname) {
      CIng -= 1;
      transferdata(ingname, CIng);
    }
  }

  return false;
}
bool searchIng(string keyword) {
  ifstream myfile("ingredient.txt");
  while (myfile >> ingname >> CIng) {
    if (keyword == ingname && CIng > 0) {
      return true;
    }
  }
  return false;
}
bool searchAvIng(int id, int count) {
  trucount = 0;
  ifstream filee;
  filee.open("foodingred.txt", ios::in);
  ifstream ming("ingredient.txt");
  if (filee.is_open()) {
    string line;
    while (filee >> line) {
      if (int(line[0]) >= 48 && int(line[0]) <= 57 &&
          (int(line[0]) - 48) == id) {
        idcheckforfood = id;
        ;
      }
      if (int(line[0]) >= 48 && int(line[0]) <= 57 &&
          (int(line[0]) - 48) == (id + 1)) {
        break;

      } else if (int(line[0]) < 48 ||
                 int(line[0]) > 57 && idcheckforfood == id) {
        stringstream ss(line);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> ings(begin, end);
        for (int i = 0; i < ings.size(); i++) {
          if (searchIng(ings[i])) {
            trucount++;
          }
        }
      }
    }
    filee.close();
  }
  if ((trucount) == ingcount) {
    return true;
  }
  return false;
}
bool ShowFood(string fn) {
  ifstream myfile("food.txt");
  ifstream somefile("foodingred.txt");
  while (myfile >> foodname >> foodprice >> ingcount >> idcount) {
    if (fn == foodname && searchAvIng(idcount, ingcount)) {
      return true;
    }
  }
  return false;
}
void showFoods(string fn) {
  ifstream myfile("food.txt");
  while (myfile >> foodname >> foodprice >> ingcount >> idcount) {
    if (foodname == fn && ShowFood(fn)) {
      cout << fn << " " << foodprice << " " << idcount << endl;
    }
  }
}
void searchAvfood(int count, int id) {
  ifstream filee;
  filee.open("menufood.txt", ios::in);
  if (filee.is_open()) {
    string line;
    while (filee >> line) {
      if (int(line[0]) >= 48 && int(line[0]) <= 57 &&
          (int(line[0]) - 48) == id) {
        idcheckformenu = id;
        ;
      }
      if (int(line[0]) >= 48 && int(line[0]) <= 57 &&
          (int(line[0]) - 48) == (id + 1)) {
        break;

      } else if (int(line[0]) < 48 ||
                 int(line[0]) > 57 && idcheckformenu == id) {
        stringstream S(line);
        istream_iterator<string> begin(S);
        istream_iterator<string> end;
        vector<string> foods(begin, end);
        for (int i = 0; i < foods.size(); i++) {
          showFoods(foods[i]);
        }
      }
    }
  }
  filee.close();
}
void showmenu() {
  cout << "Menu List: " << endl;
  ifstream myfile("menu.txt");
  ifstream somefile("menufood.txt");
  while (myfile >> menuname >> foodcount >> midcount) {
    cout << menuname << ": " << endl;
    searchAvfood(foodcount, midcount);
    cout << endl;
  }
}
void changeAvIng(int id, int count) {
  idcheckforfood = 0;
  trucount = 0;
  ifstream filee;
  filee.open("foodingred.txt", ios::in);
  ifstream ming("ingredient.txt");
  if (filee.is_open()) {
    string line;
    while (filee >> line) {
      if (int(line[0]) > 47 && int(line[0]) < 58 && (int(line[0]) - 48) == id) {
        idcheckforfood = id;
        ;
      }
      if (int(line[0]) >= 48 && int(line[0]) <= 57 &&
          (int(line[0]) - 48) == (id + 1)) {
        break;

      } else if (int(line[0]) > 64 && int(line[0]) < 91 &&
                     idcheckforfood == id ||
                 int(line[0]) > 96 && int(line[0]) < 123 &&
                     idcheckforfood == id) {
        stringstream ss(line);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> ings(begin, end);
        successs = 0;
        for (int i = 0; i < ings.size(); i++) {
          if (searchIng(ings[i])) {
            changeCIng(ings[i]);
            successs++;
            if (successs == count)
              return;
          }
        }
      } else
        cout << line << endl;
    }
    filee.close();
  }
}
void OrderFood(int id) {
  ifstream myfile("food.txt");
  ifstream somefile("foodingred.txt");
  while (myfile >> foodname >> foodprice >> ingcount >> idcount) {
    if (id == idcount && searchAvIng(idcount, ingcount)) {
      changeAvIng(idcount, ingcount);
    } else {
      // throw wrongException
    }
  }
}
void CutomerOrder() {
  int choice;
  cout << endl << "What would you like to order?" << endl;
  showmenu();
  cout << "Please enter food ID: ";
  cin >> choice;
  OrderFood(choice);
}
void self_exit() {
  cout << "\n\n\n\t\tThank You for using Turan services!";
  exit(0);
}
void customer() {
  int choice;
  while (true) {
    cout << "\n\n\n\t\t\tTuran Services";
    cout << "\n\n\t1. Order Food\n\t2. Exit\n\t> ";
    cin >> choice;
    switch (choice) {
    case 1:
      CutomerOrder();
      break;
    case 2:
      self_exit();
      break;
    default:
      cout << "\n\n\tInvalid Input!";
    }
  }
}
bool searchFood(string keyword) {
  ifstream myfile("food.txt");
  while (myfile >> foodname) {
    if (keyword == foodname) {
      system("cls");
      return true;
    }
  }
  cout << "\nNo such Food is found!";
  return false;
}
void showIngredients() {
  cout << "Ingredient List: " << endl;
  ifstream myfile("ingredient.txt");
  while (myfile >> ingname) {
    cout << ingname << endl;
  }
}
void addIngredient() {
  ofstream phone("ingredient.txt", ios::app);
  cout << "\n\n\tEnter Ingredient name : ";
  cin >> ingname;
  CIng = 12;
  if (phone.is_open()) {
    phone << ingname << " " << CIng << endl;
    cout << "\n\tIngedient saved successfully !";
  } else {
    cout << "\n\tError in opening record!";
  }

  cout << endl << endl;
  phone.close();
}
void addFood() {
  ofstream phone("food.txt", ios::app);
  cout << "\n\n\tEnter Food name : ";
  cin >> foodname;
  cout << "\n\tEnter Food Price : ";
  cin >> foodprice;
  cout << "\n\tEnter Ingredient Count : ";
  cin >> ingcount;
  idcount = ++INGID;
  if (phone.is_open()) {
    phone << endl
          << foodname << " " << foodprice << " " << ingcount << " " << idcount
          << " ";
  } else {
    cout << "\n\tError in opening record!";
  }

  cout << endl << endl;
  phone.close();
  for (int i = 0; i < ingcount; i++) {
    cout << "\n\tEnter Ingredient Name : ";
    cin >> ingname;
    if (searchIng(ingname))
      ings.push_back(ingname);
  }
  if (phone.is_open()) {
    phone << endl << foodname << " " << foodprice << " ";
  } else {
    cout << "\n\tError in opening record!";
  }

  cout << endl << endl;
  phone.close();
  ofstream dev("foodingred.txt", ios::app);
  if (dev.is_open()) {
    dev << idcount << " "<<endl;
    for (int i = 0; i < ingcount; i++) {
      dev << ings[i] << " ";
    }
    dev << endl;
    dev.close();
  }
}
void addMenu() {
  ofstream phone("menu.txt", ios::app);
  cout << "\n\n\tEnter Menu name : ";
  cin >> menuname;
  cout << "\n\tEnter Food Count : ";
  cin >> foodcount;
  midcount = ++FOID;
  if (phone.is_open()) {
    phone << endl << menuname << " " << foodcount << " " << midcount << " ";
  } else {
  }

  cout << endl << endl;
  phone.close();
  for (int i = 0; i < foodcount; i++) {
    cout << "\n\tEnter Food Name : ";
    cin >> foodname;
    if (searchFood(foodname))
      foods.push_back(foodname);
  }
  if (phone.is_open()) {
    phone << endl << menuname << " ";
  } else {
    cout << "\n\tError in opening record!";
  }

  cout << endl << endl;
  phone.close();
  ofstream dev("menufood.txt", ios::app);
  if (dev.is_open()) {
    dev << midcount << " "<<endl;
    for (int i = 0; i < foodcount; i++) {
      dev << foods[i] << " ";
    }
    dev << endl;
    dev.close();
  }
}
void admin() {
  int choice;
  while (1) {
    cout << "\n\n\n\t\t\tTuran Services";
    cout << "\n\n\t1. Add Ing\n\t2. Add food"
            "\n\t3. Add Menu\n\t4. Show Ingredients\n\t5. Exit\n\t> ";
    cin >> choice;

    switch (choice) {
    case 1:
      addIngredient();
      break;

    case 2:
      addFood();
      break;

    case 3:
      addMenu();
      break;
    case 4:
      showIngredients();
      break;
    case 5:
      self_exit();
      break;
    default:
      cout << "\n\n\tInvalid Input!";
    }
  }
}
void login(){
  string username,password;
  cout<<"HIII!!! Please login!!"<<endl;
  cin>>username>>password;
  ifstream myfile("admin.txt");
  while (myfile >> un>> ps) {
    if (username == un &&password==ps) {
      admin();
    }
    else{customer();}
  }
}
int main() {login(); }