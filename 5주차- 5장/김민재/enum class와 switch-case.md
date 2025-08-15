- C++ 문법 정리: enum class와 switch-case의 활용

- switch case 문법 개요 
switch-case 문은 하나의 변수 값을 기준으로 여러 조건을 분기하여 실행할 수 있도록 하는 구조이다. 조건식으로 들어가는 변수는 정수형이어야 하며, 각 case는 해당 변수 값과 비교되는 상수값을 기준으로 실행된다. default는 어떠한 case에도 해당하지 않을 경우 실행되는 블록으로, if-else 문에서의 else와 유사한 역할을 수행한다.
switch (변수) {
    case 상수값:
        // 해당 값일 때 실행할 코드
        break;
    ...
    default:
        // 조건에 해당하지 않을 경우 실행할 코드
        break;
}

- 열거형(enum)과 enum class의 차이점
C에서는 상수값에 의미 있는 이름을 부여하기 위해 enum 또는 enum class를 사용한다. enum은 전통적인 열거형으로, 상수값이 전역 범위에 노출되며 암시적으로 int로 변환된다. 반면 enum class는 C11 이후 도입된 스코프 열거형으로, 이름 충돌을 방지하고 타입 안정성을 높이는 데 유리하다.
enum Colors { BLACK, WHITE, RED, GREEN, BLUE }; // 전통적 열거형
enum class Colors { BLACK, WHITE, RED, GREEN, BLUE }; // 스코프 열거형



- enum class와 switch-case의 결합
enum class는 자동으로 int로 변환되지 않기 때문에, switch 문에서 사용할 경우 명시적인 형 변환이 필요하다. 아래는 사용자로부터 색상 번호를 입력받아 해당 색상을 출력하는 예제이다.
```cpp
#include <iostream>
using namespace std;

enum class Colors { BLACK, WHITE, RED, GREEN, BLUE };

int main() {
    int input;
    cout << "색상 번호를 입력하세요 (0~4): ";
    cin >> input;

    Colors color = static_cast<Colors>(input); // 명시적 형 변환

    switch (color) {
        case Colors::BLACK:
            cout << "Black 선택됨\n";
            break;
        case Colors::WHITE:
            cout << "White 선택됨\n";
            break;
        case Colors::RED:
            cout << "Red 선택됨\n";
            break;
        case Colors::GREEN:
            cout << "Green 선택됨\n";
            break;
        case Colors::BLUE:
            cout << "Blue 선택됨\n";
            break;
        default:
            cout << "잘못된 입력입니다.\n";
            break;
    }

    return 0;
}
```

이처럼 enum class를 사용할 경우, switch 문 내에서 각 case에 해당하는 열거형 상수를 사용할 수 있으며, 조건식과 case 간의 타입을 맞추기 위해 static_cast를 활용한 형 변환이 필요하다.
