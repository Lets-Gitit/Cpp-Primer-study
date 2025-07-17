#include "sales_data.h"
#include <string.h>

using namespace SalesBook;
using namespace std;

SALES_DATA::SALES_DATA()
{
	memset(&this->data, NULL, sizeof(INFO_T));
}
SALES_DATA::~SALES_DATA()
{

}

SALES_DATA& SALES_DATA::operator=(const SALES_DATA& Other)
{
	if (this != &Other)
 		memcpy(&this->data, &Other.data, sizeof(INFO_T));
	return *this;
}

SALES_DATA& SALES_DATA::operator+=(const SALES_DATA& Other)
{
	int total = this->data.totalSold + Other.data.totalSold;

	this->data.avg = (this->data.avg * this->data.totalSold + Other.data.avg * Other.data.totalSold)/ total;
	this->data.totalSold = total;
	return *this;
}


SALES_DATA SalesBook::operator+(const SALES_DATA& Left, const SALES_DATA& Right)
{
	SALES_DATA result = Left;
	result += Right;
	return result;
}
bool SalesBook::operator==(const SALES_DATA& Left, const SALES_DATA& Right)
{
	for (int i = 0; i < ISBN13_MAX_COUNT; i++)
		if (Left.data.isbnCode[i] != Right.data.isbnCode[i]) return false;
	return true;
}

std::istream& SalesBook::operator>>(std::istream& in,SALES_DATA& Data)
{
	in >> Data.data.isbnCode >> Data.data.totalSold >> Data.data.avg;
	return in;
}
std::ostream& SalesBook::operator<<(std::ostream& out,SALES_DATA& Data)
{
	out << Data.data.isbnCode << " " << Data.data.totalSold << " " << Data.data.avg;
	return out;
}
