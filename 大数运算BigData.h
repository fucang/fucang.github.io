#ifndef __BIG_DATA_H__
#define __BIG_DATA_H__

#include <assert.h>
#include <string>


typedef long long INT64;

//#define MININT64 -9223372036854775808 // 编译器检查有错
//
//#define MAXINT64 +9223372036854775807 

const INT64 MININT64 = +9223372036854775807 + 1;
const INT64 MAXINT64 = +9223372036854775807;

class BigData
{
	friend std::ostream& operator<<(std::ostream& _cout, const BigData& bigData);
public:
	BigData(INT64 value = 0xCCCCCCCCCCCCCCCC);
	BigData(const char* str);
	BigData operator+(const BigData& bigData);
	BigData operator-(const BigData& bigData);
	BigData operator*(const BigData& bigdata);
	BigData operator/(const BigData& bigdata);
protected:
	void _Int64ToStr();
	bool _IsINT64OverFlow()const;
	std::string AddStr(const BigData& bigData)const;
	std::string SubStr(const BigData& bigData)const;
	std::string MulStr(const BigData& bigData)const;
	std::string DivStr(const BigData& bigData)const;
	bool IsLeftStrBig(const char* pLeft, int iLSize, const char* pRight, int iRSize)const;
	char LoopSub(char* pLeft, int iLSize, const char* pRight, int iRSize)const;
private:
	INT64 _value;
	std::string _pData;
}; 

std::ostream& operator<<(std::ostream& _cout, const BigData& bigData);

#endif /*__BIG_DATA_H__*/
