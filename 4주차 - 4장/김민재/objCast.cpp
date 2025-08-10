#include <iostream>
using namespace std;

struct DATA {
	int a;
	int b;
};

class DataINT2 {	
	public:
		DataINT2(int a, int b)
		{
			this->data.a = a;
			this->data.b = b;
		}
		~DataINT2()
		{
		}

		int calc1()
		{
			return this->data.a + this->data.b;
		}

		DATA getData() 
		{
			return data; 
		}
	private:
		DATA data;
};

class Vector2i {
public:	
	Vector2i(int a, int b)
	{
		this->data.a = a;
		this->data.b = b;
	}

	Vector2i(DataINT2 DINT2)
	{
		this->data = DINT2.getData();
	}

	~Vector2i()
	{
	}

	int calc2()
	{
		return this->data.a * this->data.b;
	}
private:
	DATA data;

};


int main(void)
{

	/*
	*  reinterpret_cast로 DataINT2*를 Vector2i*로 변환하는 것은 매우 위험, 또한 C++ 표준에서는 권장x
	•	두 클래스(DataINT2, Vector2i)는 서로 상속 관계가 없고, 생성자/소멸자/멤버 함수가 다릅니다.
	•	메모리 레이아웃이 우연히 같더라도, 멤버 함수 호출 시 정의되지 않은 동작(undefined behavior)이 발생할 수 있습니다.
	•	특히, Vector2i의 생성자와 소멸자가 호출되지 않으므로 객체의 수명 관리가 올바르게 되지 않습니다.
	•	reinterpret_cast는 주로 저수준 메모리 조작에 사용되며, 일반적인 클래스 포인터 변환에는 적합하지 않습니다.
	•	이런 캐스팅은 디버깅이 매우 어려운 버그를 유발할 수 있습니다.
	
	*/
	DataINT2* d = new DataINT2(4 , 5);
	Vector2i* v = reinterpret_cast<Vector2i*>(d);
	/*
	* reinterpret_cast
	* https://learn.microsoft.com/ko-kr/cpp/cpp/reinterpret-cast-operator?view=msvc-170
	* 포인터가 다른 포인터 형식으로 변환될 수 있도록 합니다. 또한 정수 계열 형식이 포인터 형식으로 변환될 수 있도록 하고 그 반대로도 변환될 수 있도록 합니다.
	reinterpret_cast < type-id > ( expression )
	설명
	운영자의 오용은 reinterpret_cast 쉽게 안전하지 않을 수 있습니다. 원하는 변환이 본질적으로 낮은 수준이 아닌 한 다른 캐스트 연산자 중 하나를 사용해야 합니다.
	연산자는 reinterpret_cast One_class* char* int*Unrelated_class*본질적으로 안전하지 않은 변환에 사용할 수 있습니다.
	원래 형식으로 reinterpret_cast 다시 캐스팅되는 것 이외의 다른 용도로는 결과를 안전하게 사용할 수 없습니다. 다른 용도로 사용하는 경우에는 기껏해야 이식할 수 없는 결과가 생성됩니다.
	연산자는 reinterpret_cast , volatile또는 __unaligned 특성을 캐스팅const할 수 없습니다. 이러한 특성을 제거하는 방법에 대한 자세한 내용은 const_cast Operator를 참조하세요.
	reinterpret_cast 연산자는 null 포인터 값을 대상 형식의 null 포인터 값으로 변환합니다.
	실제로 사용하는 reinterpret_cast 것은 두 개의 고유 값이 거의 동일한 인덱스로 끝나지 않는 방식으로 값을 인덱스로 매핑하는 해시 함수입니다.
	*/
	cout << v->calc2() << endl;

	/*
	안전한 방법
	변환 생성자나 혹은 변환 함수 따로 제작해야한다.
	혹은 데이터만을 따로 꺼내어 복사해야한다.
	즉 객체로 데이터를 생성한 경우 DataINT2 -> Vector2i 로 데이터만 옮겨주는 별또의 로더가 필요!
	*/
	DataINT2* safe_d = new DataINT2(4, 5);
	Vector2i* safe_v = new Vector2i(*d);

	cout << safe_v->calc2() << endl;


	return 0;
}