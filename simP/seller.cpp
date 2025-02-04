#include "seller.h"

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
    product_income_pair.insert(make_pair("과자", 0));
    product_income_pair.insert(make_pair("삼각김밥", 0));
    product_income_pair.insert(make_pair("커피", 0));
    product_income_pair.insert(make_pair("담배", 0));
    product_income_pair.insert(make_pair("빵", 0));
}

void seller::refund(string name, int n, product* p)
{
    for (int i = 0; i < 5; i++)
    {
        if(p[i].get_name() == name){
            p[i].stock_plus(n);
        }
    }
}

void seller::clear_seller_income() { this->income = 0; }

product * seller::init_product_info()
{
    product* p = new product[5]{product("과자"), product("삼각김밥"), product("커피"),product("담배"), product("빵")};
    return p;
}

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

// end_Day가 실행되면, 날짜가 다음날로 바뀜과 동시에, csv 파일 생성 또는 최신화.
void seller::end_Day(product *p)
{
    day_income_pair.insert(make_pair(this->cur_date, this->income));
    cout << "다음 날로 변경합니다. ";
    for (int i = 0; i < 5; i++)
    {
        p[i].stock_fill();
    }
    day_plus_one();
}

void seller::show_Data() {
    for (const auto& product : product_income_pair) {
        cout << "상품 명 : " << product.first << "의 매출은 " << product.second * get_price(product.first) << "원" << endl;
    }
    cout << endl << endl;
    for (const auto& day : day_income_pair) {
        cout << day.first << " : " << day.second << "원" << endl;
    }
}

// 결제 완료 되었을 경우, 이 함수 호출. 인자는 상품명, 상품 갯수
void seller::payment_complete(string name, int count, product * p)
{
    for (auto& product : product_income_pair) {
        if (product.first == name) {
            for (int i = 0; i < 5; i++)
                if (p[i].get_name() == name)
                    p[i].stock_minus(count);
            product.second += count;
            this->income += count * get_price(name);
        }
    }
}

int seller::get_price(string name)
{
    if (name == "과자")
        return 2500;
    else if (name == "삼각김밥")
        return 1500;
    else if (name == "커피")
        return 2000;
    else if (name == "담배")
        return 4500;
    else if (name == "빵")
        return 3000;
    else
        return 0;
}

void seller::init_csv()
{
    // 파일 생성
    ofstream fs("product_income.csv");
    ofstream fs1("date_income.csv");
    fs.close();
    fs1.close();
}

void seller::load_product_csv()
{
    string name;
    int income;
    string test;
    fstream fs("product_income.csv", ios::in);
    if (!fs) {
        cout << "" << " 열기 오류" << endl;
    }
    this->product_income_pair.clear();
    while (!fs.eof()) {
        getline(fs, test, ',');
        name = test;
        getline(fs, test, ',');
        income = stoi(test);
        this->product_income_pair.insert(make_pair(name, income));
    }
}

// 경고, 현재까지의 매출을 csv 파일로 미리 save 하지 않은 경우, 입력되었던 매출이 다 날아감
void seller::load_date_csv()
{
    int date;
    int income;
    string test;
    fstream fs("date_income.csv", ios::in);
    if (!fs) {
        cout << "" << " 열기 오류" << endl;
    }
    this->day_income_pair.clear();
    while (!fs.eof()) {
        getline(fs, test, ',');
        date = stoi(test);
        getline(fs, test, ',');
        income = stoi(test);
        this->day_income_pair.insert(make_pair(date, income));
    }
}

void seller::save_product_csv()
{
    ofstream fs("product_income.csv", ios::app);
    for (auto& product : product_income_pair)
    {
        fs << product.first << ',' << product.second << '\n';
    }
}

void seller::save_date_csv()
{
    ofstream fs("date_income.csv", ios::app);
    for (auto& day : day_income_pair)
    {
        fs << day.first << ',' << day.second << '\n';
    }
}
