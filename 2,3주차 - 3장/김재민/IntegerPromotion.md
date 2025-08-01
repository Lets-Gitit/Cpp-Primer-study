# Integer Promotion

---

## 규칙

1. 자동 승격
    - char, short 같은 작은 정수 타입들은 연산 시 자동으로 int로 승격됩니다.
2. 승격 조건
    - 원래 타입의 모든 값이 int로 표현 가능하면 int로, 그렇지 않으면 unsigned int로 승격됩니다.

```cpp
char a = 30, b = 40, c = 10;
char d = (a * b) / c;
printf("%d", d);             // 결과 = 120
```