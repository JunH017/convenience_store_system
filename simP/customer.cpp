#include "customer.h"

void Point::addPoint(int amount) {
    value += amount;
}

void Point::subPoint(int amount) {
    value -= amount;
}

void Customer::addName(const std::string& newName) {
    names.push_back(newName);
    points.push_back(Point());
}

void Customer::changeName(const std::string& oldName, const std::string& newName) {
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i] == oldName) {
            names[i] = newName;
            return;
        }
    }
}

void Customer::setPoint(const std::string& name, int value) { //사용자 이름별 포인트 적립
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i] == name) {
            points[i].value = value;
            return;
        }
    }
}

int Customer::showPoint(const std::string& name) const {
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i] == name) {
            return points[i].value;
        }
    }
    return 0;  // 해당 이름을 찾지 못한 경우 기본값인 0 반환
}
