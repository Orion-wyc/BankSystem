cmake_minimum_required(VERSION 3.7)
project(BankManagementSystem)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp AccountData.h AccountData.cpp BankBook.h BankBook.cpp PersonalAccount.h PersonalAccount.cpp Loan.h)
add_executable(BankManagementSystem ${SOURCE_FILES})