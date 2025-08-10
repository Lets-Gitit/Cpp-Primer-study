# std::bad_cast

---

- <typeinfo> 에 정의 돼 있습니다.
- std::exception을 상속합니다.
- std::exception의 what 메서드를 사용할 수 있습니다.

## [ 발생하는 경우 ]

- & (참조) * (포인터) 로 다운캐스팅이나 크로스캐스팅을 시도할 때, 요청한 타입으로 안전하게 캐스팅할 수 없는 경우 발생합니다.
- 다형적 클래스에서 잘못된 타입으로 캐스팅을 시도할 때 발생합니다.

1. **참조 타입으로 다운캐스팅 실패**
- 클래스 잠조를 파생 클래스 참조로 캐스팅하려고 할 때, 실제 객체가 요청된 파생 클래스의 인스턴스가 아닌 경우에 발생합니다.
    
    ```cpp
    // bad_cast example
    #include <iostream>       // std::cout
    #include <typeinfo>       // std::bad_cast
    
    class Base {virtual void member(){}};
    class Derived : Base {};
    
    int main () {
      try
      {
        Base b;
        Derived& rd = dynamic_cast<Derived&>(b);
      }
      catch (std::bad_cast& bc)
      {
         std::cerr << "bad_cast caught: " << bc.what() << '\n';
      }
      return 0;
    }
    ```
    
    - base 객체는 Base 타입이므로 Derived로 캐스팅할 수 없습니다.

1. **포인터 타입으로 다운캐스팅 실패**
- 포인터의 경우, dynamic_cast가 실패하면 nullptr를 반환합니다.
- 따라서 포인터에서는 std::bad_cast가 발생하지 않습니다.
    
    ```cpp
    #include <iostream>
    #include <typeinfo>
    
    class Base {
    public:
        virtual ~Base() {}
    };
    
    class Derived : public Base {};
    
    int main() {
        Base* base = new Base();
        Derived* derived = dynamic_cast<Derived*>(base); // 실패 시 nullptr 반환
        if (derived == nullptr) {
            std::cout << "Cast failed: nullptr returned" << std::endl;
        }
        delete base;
        return 0;
    }
    ```
    

1. **크로스캐스팅 실패**
- 다중 상속 상황에서, 한 파생 클래스에서 다른 파생 클래스로 캐스팅을 시도할 때, 실제 객체가 목표 타입과 호환되지 않으면 std::bad_cast가 발생합니다.
    
    ```cpp
    #include <iostream>
    #include <typeinfo>
    
    class Base1 {
    public:
        virtual ~Base1() {}
    };
    
    class Base2 {
    public:
        virtual ~Base2() {}
    };
    
    class Derived : public Base1, public Base2 {};
    
    int main() {
        try {
            Base1* base1 = new Derived();
            Base2& base2 = dynamic_cast<Base2&>(*base1); // 성공: Derived는 Base2를 상속
            std::cout << "Cast succeeded" << std::endl;
            
            Base1* base1_only = new Base1();
            Base2& base2_invalid = dynamic_cast<Base2&>(*base1_only); // 실패: Base1은 Base2가 아님
        } catch (const std::bad_cast& e) {
            std::cout << "Bad cast: " << e.what() << std::endl;
        }
        return 0;
    }
    ```
    

---

## [ 기본 생성자 ]

```cpp
bad_cast() throw();   // until c++11 
bad_cast() noexcept;  // since c++11
```

- throw()
    - C++11 이전 표준까지 사용했습니다.
    - 생성자가 예외를 던지지 않음을 명시하는 예외사항입니다.
        
        →  throw = “ 이 함수는 그 어떤 예외도 전지지 않을것 “ 
        →  std::unexpected() 가 호출됩니다. 
        
        - expression : 몸체 안에서 예외를 실제로 던질 때 상용합니다.
        - specification : 어떤 종류의 예외를 던질 수 있는지 명시합니다.
    - 런타임 오버헤드
        - 런타임에 추가적인 코드를 생성해야 합니다.
    - 유지보수 어려움
        - 새로운 예외를 던지게 되면, 그 함수를 호출하는 상위 함수의 예외 사항까지 연쇄적으로 수정해야 합니다.
- noexcept
    - 컴파일 타임에 예외를 던지지 않음을 보장합니다.
    - 예외 처리와 관련된 복잡한 코드를 생성하지 않습니다.

---

## [ 복사 생성자 ]

```cpp
bad_cast( const bad_cast& other) throw();
bad_cast( const bad_cast& other) noexcept;
```

- throw
    - throw 되면, 이 예외 객체는 일반적인 메모리 공간이 아닌 특별한 공간에 생성됩니다.
    - bad_cast 객체를 복사하는 생성자입니다.
    - const bad_cast& other는 복사할 원본 개게를 참조합니다.
    - throw 사양으로 예외를 던지지 않음

- noexcept
    - 예외보장이 강화되었습니다.
    - 만약 예외가 발생하면, 프로그램은 예외를 처리하려는 시도조차 하지 않고 즉시 std::terminate()를 호출하여 강제 종료됩니다.

Tip)

- 객체를 옮길 때 ( move semantics ) noexcept가 보장되면, vector와 같은 컨테이너들이 훨씬 효율적으로 내부 메모리를 재할당할 수 있습니다.

---

## [ 생성자 ]

- 새로운 bad_cast 객체를 생성하며, 이 객체는 구현 정의된 null-terminate 바이트 문자열을 가지고 있습니다.
- 이 문자열은 what() 멤버 함수를 통해 접근할 수 있습니다.
    - c 스타일 문자열을 사용하기 위해서 null-terminate를 사용합니다.
        
        ```cpp
        ['c'] ['a'] ['s'] ['t'] ['\0']
        ```
        

1. **Default constructor**
    - 매개변수 없이 객체를 생성합니다.
    - 예외가 발생한 상황을 나타내는 기본 메시지를 가진 객체를 만듭니다.
        
        ```cpp
        #include <typeinfo>
        #include <iostream>
        
        int main() {
            try {
                std::bad_cast bc;  // 기본 생성자 호출
                throw bc;
            } catch (const std::bad_cast& e) {
                std::cout << "Caught: " << e.what() << std::endl;  // 출력: 구현에 따라 "std::bad_cast" 등
            }
            return 0;
        }
        ```
        

1. **Copy constructor**
    - 기존 bad_cast 객체의 내용을 복사하여 새 객체를 만듭니다.
    - 만약 새 객체 (*this)와 원본 객체 (other)가 둘다 동적 타입 이 std::bad_cast라면, std::strcmp(what(), other.what()) == 0 이 성립합니다.
        
        ```cpp
        #include <typeinfo>
        #include <iostream>
        #include <cstring>  // std::strcmp 위해
        
        int main() {
            try {
                std::bad_cast bc1;  // 기본 생성자
                std::bad_cast bc2 = bc1;  // 복사 생성자 호출
                if (std::strcmp(bc1.what(), bc2.what()) == 0) {
                    std::cout << "what() strings are equal: " << bc1.what() << std::endl;
                }
                throw bc2;
            } catch (const std::bad_cast& e) {
                std::cout << "Caught: " << e.what() << std::endl;
            }
            return 0;
        }
        ```