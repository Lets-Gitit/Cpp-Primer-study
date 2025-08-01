# Chapter 3

---

## Using

- 헤더에서 using 선언을 금지하는 이유
    - 헤더는 여러 소스 파일에 포함됩니다.
        - 하나의 헤더 파일은 여러 .cpp 파일에서 #include로 불러올 수 있습니다.
    - using 선언은 포함한 파일 전체에 영향을 미칩니다.
        - using을 선언한 헤더를 포함한 모든 소스 파일은 해당 네임스페이스에 정의된 모든 이름을 “전역”처럼 사용할 수 있게 됩니다.
    - 네임스페이스 보호 사라짐 → 이름 충돌 위험
        - 다른 라이블리들과 이름이 중복될 수 있습니다.
    - 예상치 못한 부작용 및 유지보수 어려움
        - 다른 라이브러리와 중복이 생겼을 때 문제를 찾기 어렵습니다.
        - 새로운 이름을 추가할 때 겹치는지 확인해야 합니다.st

---

## String

```cpp
string s3("value");
```

- 문자열 리터렁의 문자들만 복사합니다.
- 널 문자는 복사 대상에서 제외됩니다.
    - 실제로 s3에는 v, a, l, u, e 라는 5글자만 담깁니다.
    - std::string이 자체적으로 사이즈를 관리하기 때문에 별도의 널 문자가 필요없습니다.
- std::string은 문자열을 받을 때, 널 문자가 나오기 전까지만 복사합니다.

---

## Direct initialization

|  | Copy initialization | Direct initialization |
| --- | --- | --- |
| 사용형태 | Type var = value; | Type var(value); 또는
Type var{value}; |
| explicit 생성자 사용 가능? | 사용 불가 | 사용 가능 |
| 내부 동작 | 임시 객체 생성 뒤 복사 
( 또는 이동 ) | 직접 생성자 호출 |
| 오버로드된 생성자 선택 | 직접 초기화보다 덜 유연 | 가장 잘 맞는 생성자 직접 호출 |
- **explicit 키워드**
    - 암시적 변환 ( implicit conversion ) 방지
        - explicit이 붙지 않은 새성자는 타입이 다를 때도 자동으로 임시 객체를 생성해 타입 변환을 수행할 수 있습니다.
        - 자동 변환은 버그의 원인이 될 수 있고, 코드의 의도가 불분명해질 위험이 있습니다.
    - 사용 예시
        
        ```cpp
        class MyClass {
        	public:
        		explicit MyClass(int a) : m(a) {}
        	private:
        		int m;
        }
        ```
        
        - 위와 같이 선언을 했다면 다음과 같이 사용해야 합니다
            - MyClass obj1(10); , MyClass obj2 = MyClass(20);
        - 암시적 변환은 차단됩니다.
            - MyClass obj = 30; ( 불가합니다. )
    - 주요 특징
        - 괄호를 이용한 직접 초기화 ( Direct initialization ) 은 허용
        - = 을 이용한 복사 초기화 ( copy initialization ) 와 함수 인자 암시적 변환은 금지

---

## String 연산에서 자주 사요하는 연산자와 함수들

- os << s
    - s 문자열을 출력 스트림 (os, cout ) 에 출력
- is >> s
    - 입력 스트림 (is, cin) 에서 공백 기준으로 문자열 s를 입력
- getline(is, s)
    - 주요 특징
        - 개행 문자를 버린다.
            - getline이 반환하는 새 줄은 버려집니다.
        - 공백이 포함된 전체 줄을 읽어온다
            - getline은 줄의 끝까지 모드 읽고 문자열에 넣습니다.
        - 입력 스트림과 함께 사용
            - 표준 입력 외에도 파일 입력스트림 등 여러 입력 스트미과 함께 쓸 수 있습니다.
- s.empty()
    - s가 비어있으면 true, 아니면 fales 반환
- s.size()
    - s의 길이 (문자 개수) 반환
- s[n]
    - s의 n번째 문자에 접근
- s1 + s2
    - s1과 s2를 합쳐서 새로운 문자열 반환 ( 이어 붙이기 )
- s1 =  s2
    - s1에 s2 내용을 복사
- s1 == s2
    - 두 문자열이 같으면 true ( 대소문자 구분 )
- s1 ≠ s2
    - 두 문자열이 다르면 true

---

## std::string::size_type

- 클래스가 반환하는 문자열 길이, 인데스 등과 관련된 값의 자료형입니다.

1. 정확한 타입의 정체
    - std::string::size_type은 대부분의 구현에서 std::size_t의 별칭 입니다.
    - std::size_t는 플랫폼에 따라 크기가 달라지는 부호 없는 정수형입니다.
        - 32비트 컴퓨터에서는 보통 unsigned int
        - 64비트 컴퓨터에서는 보통 unsigned long, unsigned long long

---

## cctype Functions

- **isalnum 함수**
    - 특정 문자가 알파벳 또는 숫자 문자인지 확인하는 데 사용됩니다. 
    ( a-z, A-Z ) 또는 ( 0-9 ) 에 해당하는지 판별합니다.
        
        ```cpp
        int isalnum(int c);
        ```
        
        - 여기서 c는 검사할 문자 입니다.
    - 매개변수가 int인 이유
        
        [Integer Promotion](Integer%20Promotion%20240f95f2511c8098a30bee89e1196e48.md)
        
        1. EOF 처리를 위해
            - EOF는 -1로 정의되어 있습니다.
            - 이들 함수는 정상적인 문자값(0-255)와 EOF(-1)를 구분해야 하기 때문입니다.
            
            ```cpp
            char ch = getchar();
            if(ch == EOF){}
            ```
            
        
        1. 안전한게 값을 받기 위해
            
            ```cpp
            signed char ch = 255; // -1로 해설됨 (sign extension)
            if(isalnum(unsigned char)ch) {}
            ```
            

---

## Vector

- vector는 원소를 추가할 때 (push_back()) 현재 할당된 메모리 공간이 부족하면 더 큰 메모리 블록을 새로 할당하고 기존 원소들을 복사한 후 새로운 원소를 추가합니다.
- 효율적으로 사용할 수 있는 방법
    - **reserve() 함수**
        - 미리 필요한 만큼의 메모리를 할당합니다.
            
            ```cpp
            #include <vector>
            #include <iostream>
            
            int main() {
                std::vector<int> myVector;
                std::cout << "Initial capacity: " << myVector.capacity() << std::endl;
            
                // 1000개의 원소를 넣을 것을 예상하고 미리 메모리를 할당합니다.
                myVector.reserve(1000);
                std::cout << "Capacity after reserve(1000): " << myVector.capacity() << std::endl;
            
                // 1000개의 원소를 추가하는 동안 메모리 재할당이 발생하지 않습니다.
                for (int i = 0; i < 1000; ++i) {
                    myVector.push_back(i);
                }
                
                // 만약 reserve()를 사용하지 않았다면 capacity는 여러 번 증가했을 것입니다.
                std::cout << "Capacity after 1000 push_back: " << myVector.capacity() << std::endl;
                
                return 0;
            }
            ```
            
        - resize와 reserve 함수의 차이
            - resize
                - vector의 size를 n으로 만듭니다.
                - 만약 n이 현재 size보다 크다면 부족한 만큼 기본 값으로 초기화된 원소를 추가합니다.
                - capacity도 필요에 따라 증가시킵니다.
                - 원소의 개수를 확정하고 싶을 때 사용합니다.
            - reserve
                - vector의 capacity를 n으로 만듭니다.
                - size는 변경하지 않습니다.
                - 즉, 메모리만 미리 확보합니다.
                - 나중에 원소를 추가할 것을 대비해 미리 메모리만 확보하고 싶을 때 사용합니다.
    - **emplace_back(), push_back()**
        - push_back(value)    :   벡터의 끝에 요소를 추가합니다.
            
            ```cpp
            myIntVector.push_back(10);
            myIntVactor.push_back(20);
            myIntVactor.push_back(30;
            ```
            
            - 이미 생성된 객체를 vector의 끝에 추가합니다.
            - 객체를 복사하거나 이동하여 vector의 내부 메모리에 삽입합니다.
            - 생성된 객체를 그대로 사용합니다.
        
        - emplace_back()    :    벡터의 끝에 요소를 직접 생성합니다.
            
            ```cpp
            struct MyObject{
            	int x, y;
            	MyObject(int _x, int _y) : x(_x), y(_y) {}
            };
            
            eastl::vector<MyObject> myOBJVec;
            myOBJVec.emplace_back(100, 200) // MyObject(100, 200) 객체를 직접 생성
            ```
            
            - 객체를 복사하거나 이동하지 않고, 전달된 인자를 사용해 vector 내부 메모리에서 객체를 생성합니다.
            - 불필요한 복사나 임시 객체를 생성을 피할 수 있습니다.
            - push_back 보다 빠를 수 있습니다. ( 복사 / 이동을 피하고 싶을 때 )
    - **vector<bool> 피하기**
        1. 비트 압축 구현
            - vector<boo>은 메모리 절약을 위해 bool값을 각각 저장하지 않고, 비트필드에 여러 개의 bool을 압축해서 저장합니다.
            - 예를들어, 1바이트(8bit)에 8개의 bool 값을 저장하는 식입니다.
            - 그대로 실제로 vector<bool>내부에 bool 타입 원소가 존재하지 않습니다.
        2. reference 반환
            - vector<int>는 int&를 반환하지만, vector<bool>은 reference를 반환합니다.
            - 이 reference는 단일 비트에 대한 접근을 캡슐화하고, bool로 형변환이 불가합니다.
            - bool* p = &v와 같은 코드는 vector<int>에서는 되지만 vector<bool>에서는 컴파일 오류가 발생합니다.
        3. 호환성
            - reference 반환 때문에, 표준 컨테이너처럼 동작하지 않습니다.
            - 반복자 관련 연산, 표준 알고리즘 ( std::sort)에 넣었을 때 예상하지 못한 동작이나 호환성 문제가 발생할 수 있습니다.
        4. 성능 저하
            - 값 접근, 수정 시 단순 배열처럼 동작하지 않고 비트마스크 연산이 추가로 필요합니다.
            - 이로 인해 vector<int>보다 접근 속도가 느려질 수 있습니다.

---

## 배열을 사용해야 할 때와 vector를 사용해야 할 때

- 배열
    - 데이터 크기가 고정되고, 컴파일 타임에 크기를 알 수 있을 때
    - 성능이 매우 중요하거나, 메모리 사용을 최소화해야할 때 ( 최적화에 유리 )
    - c스타일 api와 상호작용할 때, 임베디드 시스템을 사용할 때.
    - 동적 할당없이 고정된 메모리만 사용하고 싶을 때.
- vector
    - 데이터 크기가 런타임에 변하거나, 미리 크기를 알 수 없을 때
    - 삽입, 삭제, 정렬 등 복잡한 작업이 필요할 때
    - 안전한 메모리 관리와 stl의 다양한 기능을 활용하고 싶을 때

---

## const_iterator

- 컨테이너의 요소를 순회하며 읽기만 가능하도록 설계된 반복자입니다.
- 일반 iterator와 달리, const_iterator를 통해 접근한 요소는 수정할 수 없습니다.

|  | iterator | const_iterator |
| --- | --- | --- |
| 수정 가능 | 요소 읽기 / 수정 모두 가능 | 요소 읽기만 가능 |
| 반환 메서드 | begin(), end() | cbegin(), cend() 또는 
const 객체의 begin(), end() |
| 사용  | 요소를 수정해야할 때 | 읽기 전용 순회, 상수 컨테이너 접근 |
| 호환성 | non const 컨테이너에서만 사용 | non const or const 컨테이너 모두 가능 |

---

## prtdiff_t

- cpp에서 두 포인터의 차이를 나타내기 위해 사용되는 부호 있는 정수 타입입니다.
- 주로 포인터 산술 연산이나 배열 인덱싱에서 사용됩니다.
- 특히, 음수 값이 필요한 경우에 적합합니다.

정의 및 특징

- 두 포인터가 가리키는 메모리 주소 간의 차이를 저장하는 부호있는 저웃 타입니다. 
( 일반적으로 배열의 요소 간 인덱스 차이를 나타냅니다. )
- int, long, long long 과 같은 타입으로 구현됩니다.

포인터 뺄셈

```cpp
#include <iostream>
#include <cstddef>

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int* p1 = &arr[1]; // arr[1]을 가리킴
    int* p2 = &arr[4]; // arr[4]를 가리킴

    std::ptrdiff_t diff = p2 - p1; // 인덱스 차이: 4 - 1 = 3
    std::cout << "Difference: " << diff << std::endl; // 출력: 3
    return 0;
}
```

- 배열의 크기를 구하거나할 때 사용합니다.
- 배열이 매우 클 때 int를 넘어갈 수 있어 std::ptrdiff_t가 더 안전합니다.

사용 이유

- 시스템에 따라 포인터 크기와 정수 타입이 다릅니다. ( 32bit, 64bit )
- ptrdiff_t은 플랫폼에 맞게 적절한 크기를 보장합니다.  ( 이식성이 높습니다. )
- 포인터 뺄셈의 결과가 음수일 수 있기 때문에 size_t보다는 prtdiff_t이 더 적절합니다.