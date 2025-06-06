// 1. 은행 계좌를 모델링한 CustomerAccount 클래스를 구현하며,
//    예외 처리를 사용하여 입금(deposit)과 출금(withdraw) 시 발생할 수 있는 오류를 처리

#include <iostream>
#include <string>

// 2-1. 입금 또는 출금 시 발생하는 예외 상황을 처리하기 위한 클래스.
//  예외 발생 시 구체적인 오류 메시지와 관련 금액을 저장하여, 호출자가 어떤 문제가 발생했는지 알 수 있도록 함.
class AccountException {
private:
    std::string message;  // 에러 메시지 저장.
    int amount;  // 문제가 된 금액을 저장 (예: 음수 입금액 또는 잔고 초과 출금액).
public:
    // 생성자: 메시지와 금액을 초기화.
    AccountException(const std::string& msg, int amt) : message(msg), amount(amt) {}
    // 예외 정보를 조회하기 위한 getter 메서드.
    std::string getMessage() const { return message; }
    int getAmount() const { return amount; }
};

// 2-2. 은행 계좌의 잔고를 관리하며, 입금과 출금을 처리하는 클래스.
//   계좌의 상태를 관리하며, 잘못된 입력(음수 입금, 잔고 초과 출금)을 예외로 처리함.
class CustomerAccount {
    int balance;   // 계좌의 현재 잔고를 저장.

public:
    // 생성자: 초기 잔고를 설정 (기본값 0).
    CustomerAccount(int b = 0) : balance(b) {}
    // 현재 잔고를 반환.
    int getBalance() const { return balance; }
    
    //* 금액을 입금, 입금액이 0 이하일 때 AccountException을 던짐.
    //* 성공 시 잔고를 업데이트하고 새로운 잔고를 반환.
    int deposit(int amount) {
        if (amount <= 0) {
            throw AccountException("입금 금액은 양수여야 합니다", amount);
        }
        balance += amount;
        return balance;
    }
    
    //* 금액을 출금, 출금액이 잔고보다 클 때 AccountException을 던짐.
    //* 성공 시 잔고를 업데이트하고 새로운 잔고를 반환.
    int withdraw(int amount) {
        if (amount > balance) {
            throw AccountException("출금하기에 잔고가 부족합니다", amount);
        }
        balance -= amount;
        return balance;
    }
};

// main() 함수에서 예외 처리 테스트
int main() {
    CustomerAccount account(1000); // 초기 잔고 1000

    // 테스트 1: 정상적인 입금
    // 500원 입금 → 잔고 1000 → 1500.
    try {
        std::cout << "초기 잔고: " << account.getBalance() << std::endl;
        int newBalance = account.deposit(500);
        std::cout << "500원 입금 후: " << newBalance << std::endl;
    } catch (const AccountException& e) {
        std::cout << "오류: " << e.getMessage() << ", 금액: " << e.getAmount() << std::endl;
    }

    // 테스트 2: 음수 입금 (예외 발생)
    // 음수 입금: -100원 입금 시도 → 예외 발생, 잔고 변화 없음.
    try {
        account.deposit(-100);
    } catch (const AccountException& e) {
        std::cout << "오류: " << e.getMessage() << ", 금액: " << e.getAmount() << std::endl;
    }

    // 테스트 3: 정상적인 출금
    // 정상 출금: 300원 출금 → 잔고 1500 → 1200.
    try {
        int newBalance = account.withdraw(300);
        std::cout << "300원 출금 후: " << newBalance << std::endl;
    } catch (const AccountException& e) {
        std::cout << "오류: " << e.getMessage() << ", 금액: " << e.getAmount() << std::endl;
    }

    // 테스트 4: 잔고 초과 출금 (예외 발생)
    // 잔고 초과 출금: 2000원 출금 시도 → 예외 발생, 잔고 변화 없음.
    try {
        account.withdraw(2000);
    } catch (const AccountException& e) {
        std::cout << "오류: " << e.getMessage() << ", 금액: " << e.getAmount() << std::endl;
    }

    // 최종 잔고 출력 - 계좌 상태 확인.
    std::cout << "최종 잔고: " << account.getBalance() << std::endl;

    return 0;
}