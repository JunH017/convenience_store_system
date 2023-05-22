#include "seller.h"

void seller::set_day_today()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t curtime = std::chrono::system_clock::to_time_t(now);
    tm* localT = localtime(&curtime);

    int Date = (localT->tm_year % 100) * 10000 + (localT->tm_mon + 1) * 100 + localT->tm_mday;
    this->cur_date = Date;
}

seller::seller() {
        init_product_income_map();
        set_day_today();
        this->income = 0;
        this->password = "1q2we3e4r!";
}

bool seller::check_Password(std::string pass_input) {
    if (this->password == pass_input) return true;
    else return false;
}

void seller::init_product_income_map()
{
    product_income_pair.insert(std::make_pair("����", 0));
    product_income_pair.insert(std::make_pair("�ﰢ���", 0));
    product_income_pair.insert(std::make_pair("Ŀ��", 0));
    product_income_pair.insert(std::make_pair("���", 0));
    product_income_pair.insert(std::make_pair("��", 0));
}

void seller::clear_seller_income() { this->income = 0; }

void seller::end_Day()
{
    
    day_income_pair.insert(std::make_pair(this->cur_date, this->income));
}

