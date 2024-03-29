/*
 @Date    : 2018-01-16 15:51:10
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
p723
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>
#include "Sales_data.h"

using namespace std;

typedef tuple<vector<Sales_data>::size_type, vector<Sales_data>::const_iterator,
        vector<Sales_data>::const_iterator> matches;

vector<matches> findBoook(const vector<vector<Sales_data>> &files, const string &book)
{
    vector<matches> ret;
    for (auto it = files.cbegin(); it != files.cend(); ++it)
    {
        auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);
        if (found.first != found.second)
            ret.push_back(make_tuple(it - files.cbegin(), found.first, found.second));
    }
    return ret;
}

void reportResults(istream &in, ostream &os, const vector<vector<Sales_data>> &files)
{
    string s;
    while (in >> s)
    {
        auto trans = findBoook(files, s);
        if (trans.empty())
        {
            cout << s << " not found in any store" << endl;
            continue;
        }
        for (const auto &store : trans)
        {
            os << "store " << get<0>(store)+1 << " sales: "
            << accumulate(get<1>(store), get<2>(store), Sales_data(s)) << endl;
        }
    }
    return;
}

void readStoreData(vector<vector<Sales_data>> &files)
{
    set<string> storeData{"store1", "store2", "store3", "store4"};
    for (auto &eachStore : storeData)
    {
        ifstream fin(eachStore);
        vector<Sales_data> eachStoreData;
        string eachTrans;
        while (getline(fin, eachTrans))
        {
            istringstream sin(eachTrans);
            string isbn;
            int n;
            double price;
            sin >> isbn >> n >> price;
            Sales_data item(isbn, n, price);
            eachStoreData.push_back(item);
        }
        sort(eachStoreData.begin(), eachStoreData.end(), compareIsbn);
        files.push_back(eachStoreData);
    }
    return;
}

int main(int argc, char const *argv[])
{
    vector<vector<Sales_data>> files;
    readStoreData(files);
    reportResults(cin, cout, files);
    return 0;
}
