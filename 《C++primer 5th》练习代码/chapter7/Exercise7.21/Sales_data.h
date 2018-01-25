/*
 @Date    : 2017-12-14 19:42:09
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
p271
 */

#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

using namespace std;

class Sales_data;
istream& read(istream&, Sales_data&);

class Sales_data
{
friend istream& read(istream&, Sales_data&);
friend ostream& print(ostream&, const Sales_data&);
friend Sales_data add(const Sales_data&, const Sales_data&);
public:
    Sales_data() = default;
    Sales_data(const string &s) : bookNo(s) {}
    Sales_data(const string &s, unsigned n, double p) :
        bookNo(s), units_sold(n), revenue(n * p) {}
    Sales_data(istream &is)
    {
        read(is, *this);
    }
    string isbn() const;
private:
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
    Sales_data& combine(const Sales_data&);
};

istream& read(istream&, Sales_data&);
ostream& print(ostream&, const Sales_data&);
Sales_data add(const Sales_data&, const Sales_data&);

string Sales_data :: isbn(void) const
{
    return bookNo;
}

Sales_data& Sales_data :: combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

#endif
