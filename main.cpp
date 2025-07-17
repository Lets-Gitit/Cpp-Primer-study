#include <iostream>
#include "sales_data.h"

using namespace std;
/*
book1 0-201-70353-X 4 24.99
book2 0-201-70353-X 10 15.99

0-201-70353-X 4 24.99
0-201-70353-X 10 15.99
0-201-70353-X 14 18.5614
*/

int main(void)
{
	SalesBook::SALES_DATA book1;
	SalesBook::SALES_DATA book2;

	cin >> book1;
	cin >> book2;

	book1 += book2;
	cout << book1 << endl;

}