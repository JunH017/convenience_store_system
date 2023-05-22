#include "seller.h"
using namespace std;

void seller::set_day_today()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t curtime = chrono::system_clock::to_time_t(now);
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

bool seller::check_Password(string pass_input) {
    if (this->password == pass_input) return true;
    else return false;
}

void seller::init_product_income_map()
{
    product_income_pair.insert(make_pair("����", 0));
    product_income_pair.insert(make_pair("�ﰢ���", 0));
    product_income_pair.insert(make_pair("Ŀ��", 0));
    product_income_pair.insert(make_pair("���", 0));
    product_income_pair.insert(make_pair("��", 0));
}

void seller::clear_seller_income() { this->income = 0; }

void seller::day_plus_one() {
    int year = this->cur_date / 10000;
    int month = (this->cur_date % 10000) / 100;
    int day = this->cur_date % 100;
    
    int month_D[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        month_D[1] = 29;
    day += 1;

    if (day > month_D[month - 1]) {
        day = 1; month += 1;
        if (month > 12)
        {
            month = 1; year += 1;
        }
    }
    this->cur_date = year * 10000 + month * 100 + day;
}

void seller::end_Day()
{
    day_income_pair.insert(make_pair(this->cur_date, this->income));
    cout << "���� ���� �����մϴ�. ";
    day_plus_one();
}

void seller::show_Data() {
    for (const auto& product : product_income_pair) {
        cout << "��ǰ �� : " << product.first << "�� ������ " << product.second * get_price(product.first) << "��" << endl;
    }
    cout << endl << endl;
    for (const auto& day : day_income_pair) {
        cout << day.first << " : " << day.second << "��" << endl;
    }
}

// ���� �Ϸ� �Ǿ��� ���, �� �Լ� ȣ��. ���ڴ� ��ǰ��, ��ǰ ����
void seller::payment_complete(string name, int count)
{
    for (auto& product : product_income_pair) {
        if (product.first == name) {
            product.second += count;
            this->income += count * get_price(name);
        }
    }
}

int seller::get_price(string name)
{
    if (name == "����")
        return 2500;
    else if (name == "�ﰢ���")
        return 1500;
    else if (name == "Ŀ��")
        return 2000;
    else if (name == "���")
        return 4500;
    else if (name == "��")
        return 3000;
    else
        return 0;
}

void seller::load_product_csv()
{
}

void seller::load_date_csv()
{
    int date;
    int income;
    string test;
    fstream fs;
    fs.open("test.csv", ios::in);
    if (!fs) {
        cout << "" << " ���� ����" << endl;
    }

    while (!fs.eof()) {
        getline(fs, test, ',');
        
    }
}

void seller::save_product_csv()
{
}

void seller::save_date_csv()
{
}
