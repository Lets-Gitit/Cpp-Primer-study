# Chapter 5

---

## [ NULL & nullptr ]

- 모두 값이 없음을 나타내기 위해 사용됩니다.

**NULL**

- 문제점
    - 언어 차원 키워드가 아니라, 일반적으로 매크로로 정의된 값입니다.
    - 대부분의 경우 정수 리터럴 0 또는 (void*)0 으로 정의되어 있습니다.
        
        ```cpp
        #define NULL 0
        ```
        
    - 함수 오버로딩 시 예상치 못한 동작을 할 수 있습니다.
        
        ```cpp
        void func(int i) {
        	cout << "int 오버로드 호출" << endl;
        }
        
        void func(char* p) {
        	cout << "char* 오버로드 호출" << endl;
        }
        
        func(NULL);
        ```
        
        - func(int i) 가 호출됩니다.

**nullptr**

- 장점
    - 타입 안전성
        - 포인터 타입이므로, 포인터와 정수를 명확하게 구분할 수 있습니다.
    - 의도 명확화
        - 코드를 읽는 사람에게 nullptr는 명백하게 포인터가 없음을 의미한다는 것을 전달해 줍니다.
    - 오버로딩 문제 해결
        - NULL의 예시 코드에서 func(nullptr)를 호출하면, func(char* p) 함수가 올바르게 호출됩니다.

---

## [ range for ]

```cpp
for(auto i : MyList);

// 대략적으로 이렇게 컴파일러가 해석합니다.
{
	auto && __range = MyList;
	auto __begin = std::begin(__range);
	auto __end   = std::end(__range);
	
	for(; __begin != __end; ++__begin)
	{
		auto i = *__begin;
		
		// 내부 반복문 코드
	}
}
```

- range for문이 연속적인 메모리를 사용하는 데이터를 접근할 때는 일반 for문과 속도가 비슷합니다.
- 하지만, map, set, list와 같이 비연속 메모리를 순회하는 경우 일반 for문이 훨씬 빠릅니다.

---

## [ goto ]

- 프로그램의 실행 흐름을 특정 label로 무조건 점프 시키는 제어 구조입니다.

**장점**

- 중첩된 루프에서 한 번에 탈출해야할 때
    
    ```cpp
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (some_condition) goto exit_loop;  // 중첩 루프 탈출
        }
    }
    exit_loop:
    // 루프 탈출 후 코드
    ```
    
    - 코드가 더 짧아지고, 중첩 수준이 깊을 때 편리합니다.
- 오류 처리와 자원 관리의 간소화
    
    ```cpp
    #include <cstdio>
    
    int main() {
        FILE* file1 = fopen("file1.txt", "r");
        if (!file1) goto error;
    
        FILE* file2 = fopen("file2.txt", "r");
        if (!file2) goto cleanup_file1;
    
        // 정상 처리
        fclose(file2);
    cleanup_file1:
        fclose(file1);
        return 0;
    
    error:
        printf("Error occurred\n");
        return 1;
    }
    ```
    
    - 중복된 cleanup 코드를 피하고 오류 핸들링을 중앙화할 수 있습니다.
- 성능 최적화
    - 루프나 함수 호출보다 오버헤드가 적습니다.

**단점**

- 가독성과 이해의 어려움
- 제어 프름이 비선형이 되어 코드가 어디서 어디로 점프하는지 출적하기 어렵습니다.
- 스파게티코드를 작성하게 될 수 있습니다.
- goto가 섞이면, 함수 하나를 읽어도 전체 흐름을 파악하기 어렵습니다.
- 논리 오류와 버그 유발 위험
    - 점프가 어디서든 가능하므로, 중요한 코드 섹션을 건너 뛰거나 무한 루프에 빠질 위험이 큽니다.
    - 컴파일 타임에 잡히지 않고, 런타임에 크래시나 잘못된 결과를 초래합니다.
- 현대 언어와의 호환성 문제
    - 팀 프로젝트에서 코드 일관성을 해치고, 새로운 언어로 이식할 때 문제가 됩니다.

---

## [ std::exception ]

**정의와 포함 헤더**

- 정의
    - std;;exception 은 에외를 나태나는 기본 클래스입니다.
    - 표준 라이브러에서 발생하는 모든 에외가 이 클래스를 상속합니다.
- 목적
    - 에외 객체가 공통 인터페이스를 가지도록 하여, catch 블록에서 다형성을 활용할 수 있게 합니다.
- 특징
    - c11부터 멤버 함수에 noexception이 적용되어 에외가 발생하지 않음을 보장합니다.
    - c++26부터 모든 멤버 함수가 constexpr로 선언되어 상수 표현식에서 사용 가능합니다.

**파생된 주요 클래스**

- 논리 오류 ( stdexcept )
    - std::invalied_arguments : 함수에 유효하지 않은 인수가 전달되었을 때.
    - std::out_of_range : 인덱스가 범위를 벗어났을 때.
    - std::length_error : 컨테이너의 길이가 지나치게 길 때.
- 런타임 오류
    - std::runtime_error : 예측 불가능한 런타임 오류가 발생했을 때.
    - std::overflow_error : 산술 연산 결과가 오버플로우 되었을 때.
    - std::underflow_error : 산술 연산 결과가 언더플로 되었을 때.