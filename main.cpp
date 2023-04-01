#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Book.h"
#include <vector>
#include "sort.h"
#include <map>


int linear_search(std::vector<Book> &arr, int start, int end, const std::string b)
{
    for (int i = start; i <end; i++)
    {
        if (arr[i].name == b)
            return i;
    }
    return -1;
}
//



int binary_search(std::vector<Book> &arr,  int r,std::string x)
{
    int l = 0 ;
    while (l <= r)
    {
        int m = l + (r - l) / 2;

        int res = -1000;   //some random value assigned because if res is already 0 then
        //it will always return 0
        if (x == (arr[m].name))
            res = 0;


        // Check if x is present at mid
        if (res == 0)
            return m;

        // If x greater, ignore left half
        if (x > (arr[m].name))
            l = m + 1;

            // If x is smaller, ignore right half
        else
            r = m - 1;
    }

    return -1;
}

int main() {
    int data_amnts[11] = {1000, 50000,100000, 200000,300000,400000,500000,600000,700000,800000,1000000};
    std::string line;
    std::string name1, name2, name3, title1, title2;
    std::vector<Book> books(1000000);
    std::multimap<std::string, Book> m1;
    std::multimap <std::string, Book> :: iterator m1_iter;
    typedef std::pair <std::string, Book> pr;
    int year1, number1, n=0;

    std::ifstream is("no-tab-file.txt"); // открываем файл для чтения
    if (is.is_open()) {

        while (getline(is, line)) {
            std::istringstream iss(line);  // поток для считывания данных из строки
            iss >> name1 >> name2 >> name3 >> title1 >> title2 >> year1 >> number1;

            std::string fio = name1 + " " + name2 + " " + name3;
            title1 += " " + title2;
            books[n].name = fio;
            books[n].title = title1;
            books[n].year = year1;
            books[n].number = number1;
            m1.insert ( pr ( fio, books[n] ) );
            n++;
        }
    } else
        std::cout << "File could not be opened\n";

    is.close();     // закрываем файл
    quickSort(books, 0, books.size() - 1);

   std::cout << "LinearSearch:\n";
   for (int amount : data_amnts) {
       std::vector<Book> arr;
       int a = 0;
       while (arr.size() != amount) {
           arr.push_back(books[a]);
           a += 1;
       }

       std::string key = arr[amount-1].name;

       int en = arr.size()-1;
       auto start = std::chrono::steady_clock::now();

       linear_search(arr,0,en,key);

       auto end = std::chrono::steady_clock::now();
       auto dif = end - start;

       std::cout << amount <<' '<< std::chrono::duration<double, std::micro>(dif).count() << "\n";
       //std::cout << i <<' '<< key<< '\n';
   }

//
   std::cout << "\nBinarySearch(sorted):\n";
    std::vector<Book> books_s;
    int a = 0;
    while (books_s.size() != books.size()) {
        books_s.push_back(books[a]);
        a += 1;
    }


    //quickSort(books_s, 0, books_s.size() - 1);
   for (int amount : data_amnts) {
       std::vector<Book> sorted;
       int a = 0;
       while (sorted.size() != amount) {
           sorted.push_back(books_s[a]);
           a += 1;
       }

       std::string key = sorted[amount-1].name;
       auto starts = std::chrono::steady_clock::now();

       binary_search(sorted, sorted.size() - 1, key);

       auto ends = std::chrono::steady_clock::now();
       auto diffs = ends - starts;
       std::cout << amount <<" "<< std::chrono::duration<double, std::micro>(diffs).count() << "\n";

   }


   std::cout << "\nBinarySearch+sort:\n";
  for (int amount : data_amnts) {
       std::vector<Book> sorted;
       int a = 0;
       while (sorted.size() != amount) {
           sorted.push_back(books[a]);
           a += 1;
       }
      std::string key = sorted[amount-1].name;
       auto starts = std::chrono::steady_clock::now();
       quickSort(sorted, 0, sorted.size() - 1);
       linear_search(sorted, 0, sorted.size() - 1, key);

       auto ends = std::chrono::steady_clock::now();
       auto diffs = ends - starts;
       std::cout << amount <<" "<< std::chrono::duration<double, std::micro>(diffs).count() << "\n";

   }

  std::cout<<"\nMultimap:\n";
    for (int amount : data_amnts) {
        std::multimap<std::string, Book> m2;
        int a = 0;
        while (m2.size() != amount) {
            m2.insert(pr(books[a].name,books[a]));
            a += 1;
        }
        std::string key = m2.rbegin()->first;
        auto starts = std::chrono::steady_clock::now();
        m2.find(key);
        auto ends = std::chrono::steady_clock::now();
        auto diffs = ends - starts;
        std::cout  << amount <<" "<< std::chrono::duration<double, std::micro>(diffs).count() << "\n";
    }

}
