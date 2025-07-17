#ifndef SALES_DATA_H
#define SALES_DATA_H

#define ISBN13_MAX_COUNT 13

#include <iostream>

namespace SalesBook {
	typedef struct INFO
	{
		char isbnCode[ISBN13_MAX_COUNT + 1];
		unsigned int totalSold;
		double avg;
	}INFO_T;


	class SALES_DATA {
	public:
		SALES_DATA();
		~SALES_DATA();
	
		SALES_DATA& operator=(const SALES_DATA& Other);
		SALES_DATA& operator+=(const SALES_DATA& Other);


		friend SALES_DATA operator+(const SALES_DATA& Left, const SALES_DATA& Right);
		friend bool operator==(const SALES_DATA& Left, const SALES_DATA& Right);
		friend std::istream& operator>>(std::istream& in,SALES_DATA& Data);
		friend std::ostream& operator<<(std::ostream& out,SALES_DATA& Data);
		
	private:
		INFO_T data;
	};
	std::istream& operator>>(std::istream&,SALES_DATA& Data);
	std::ostream& operator<<(std::ostream&,SALES_DATA& Data);

	SALES_DATA operator+(const SALES_DATA& Left, const SALES_DATA& Right);
	bool operator==(const SALES_DATA& Left, const SALES_DATA& Right);

}




#endif // !SALES_DATA_H
