#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <sstream>
#include <iomanip>
#include <ctime>
#pragma warning(disable:4996)

//商品id定义函数
int generateId() {
    static int id = 10000000;  // 静态变量id，初始化为0
    return ++id;  // 自增id并返回
}

//商品参数
class commodityitem {
public:
    int id_commodity;//商品代码
    std::string name_commodity;//商品名称
    std::string category_commodity;//商品类别
    double price_commodity;//商品价格
    int all_commodity;//商品总量
    int warranty_commodity;//商品保质期

    commodityitem(int Id,std::string name, std::string category,double price,int all,int warranty)
        :id_commodity(Id),name_commodity(name),category_commodity(category),price_commodity(price),all_commodity(all),warranty_commodity(warranty)
    {
    }
    
};

//商品动态数组创建以及初始化
class Commodity {
public:
    std::vector<commodityitem> items;//创建动态数组，存储每一个商品
    int size = items.size();
    void additem(std::string name, std::string category, double price, int all, int warranty) {
        commodityitem newitem(generateId(), name, category, price, all, warranty);
        items.push_back(newitem);
    }//初始化+插入数组尾部

};//商品类包含所有商品

//仓库记录相关参数
class WarehouseItem
{
public:
    //int id_commodity;//商品代码
    std::string name_commodity;//商品名称
    std::string transactionTime;//时间
    int quantity;//数量
    std::string handler;//经办人

//构造函数初始化
    WarehouseItem(std::string time, int qty, std::string person)
        : transactionTime(time), quantity(qty), handler(person)
    {
    }

    WarehouseItem(std::string name,std::string time, int qty, std::string person)
        : name_commodity(name),transactionTime(time), quantity(qty), handler(person)
    {
    }//构造函数重载

//返回操作时间
    std::string getTransactionTime()
    {
        return transactionTime;
    }
//返回操作数量
    int getQuantity() 
    {
        return quantity;
    }
//返回执行人
    std::string getHandler()
    {
        return handler;
    }
};//仓库商品类，存储商品的信息

//仓库记录动态数组创建以及初始化
class Warehouse
{
public:
    std::vector<WarehouseItem> items;//创建动态数组，每个数组元素都是warehouseitem（每件仓库商品类）

    void addItem(std::string name,std::string time, int qty, std::string handler)
    {
        WarehouseItem newItem(name,time, qty, handler);
        items.push_back(newItem);
    }

    void addItem( std::string time, int qty, std::string handler)
    {
        WarehouseItem newItem(time, qty, handler);
        items.push_back(newItem);
    }//调用函数，向仓库中添加新的物品信息，包括时间，数量，处理人员
};//仓库类，管理仓库中的物品

////////////////////////////////////////////
//定义全局变量
Commodity commodity;
Warehouse warehouse;
////////////////////////////////////////////

//时间字符串转换tm结构体
void trans(std::string Time, tm& time) {
    // 初始化一个std::tm结构体
    std::istringstream iss(Time);
    std::string token;

    // 分解年份
    std::getline(iss, token, '-');
    time.tm_year = std::stoi(token) - 1900;

    // 分解月份
    std::getline(iss, token, '-');
    time.tm_mon = std::stoi(token) - 1;

    // 分解日期
    std::getline(iss, token, '-');
    time.tm_mday = std::stoi(token);

    // 分解小时
    std::getline(iss, token, ':');
    time.tm_hour = std::stoi(token);

    // 分解分钟
    std::getline(iss, token);
    time.tm_min = std::stoi(token);
}

//时间比较函数
double time_compare(std::string time_str1, std::string time_str2) {
    //一天为多少秒
    int day = 60 * 60 * 24;
    //创建tm类，用于存储两个时间
    struct tm time1_t = {}, time2_t = {};
    //对字符串类的时间进行转换并存入结构体中
    trans(time_str1, time1_t);
    trans(time_str2, time2_t);
    //将所存时间转化为以秒为单位的数字
    time_t time1 = mktime(&time1_t);
    time_t time2 = mktime(&time2_t);
    if (time1 != -1 && time2 != -1) {
        //计算时间差值
        double time_diff = difftime(time2, time1);
        return time_diff/day;
    }
    else {
        std::cout << "日期解析错误" << std::endl;
        return -1;
    }
}

//获取当前时间
std::string gettime() {
    // 获取当前时间
    std::time_t currentTime = std::time(nullptr);

    // 将时间转换为本地时间
    std::tm* localTime = std::localtime(&currentTime);

    // 从本地时间中提取年、月、日、小时、分钟和秒
    int year = localTime->tm_year + 1900;   // 年份是从1900年起算的，所以需要加上1900
    int month = localTime->tm_mon + 1;      // 月份是从0开始的，所以需要加上1
    int day = localTime->tm_mday;
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    //如果minutes<10，则补齐分钟缺少的0
    std::string str = std::to_string(minute);
    if (minute < 10) {
        int currentLength = str.length();
        if (currentLength < 2) {
            int numZerosToAdd = 2 - currentLength;
            std::string zeros(numZerosToAdd, '0');
            str = zeros + str;
        }
    }
    std::string time = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) + "-" + std::to_string(hour) + ":" + str;
    return time;
}

//账号密码验证
bool login(std::string username, std::string passwork) {
    //进行账号密码的验证
    std::string Username = "Admin";
    std::string Passwork = "123456";
    if (username == Username && passwork == Passwork) 
        return true;
    else
        return false;
}//账号密码验证

//商品入库操作
void commodity_ruku() {
    std::string name;
    std::cout << "输入商品名称" << std::endl;
    std::cin >> name;//输入名字
    int item = 0;//插个眼,判断商品是否存在
    //首先查找仓库中是否存在该名字的商品，若存在，则在此基础上修改，若不存在，则新入库
    for (int i = 0; i < commodity.items.size(); i++) {
        if (commodity.items[i].name_commodity == name) {
            std::cout << "已存在该商品，输入更改时间，更改数量，操作人" << std::endl;
            std::string time; int count; std::string people;
            std::cin >> time >> count >> people;//录入相关参数
            if (count < 0) {
                std::cout << "入库参数错误" << std::endl;
                return;
            }
            std::tm time_temp = {};
            trans(time, time_temp);
            if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31||time_temp.tm_mon<0||time_temp.tm_mon>11) {
                std::cout << "时间范围出错，已退出此次操作" << std::endl;
                return;
            }
            else {
                commodity.items[i].all_commodity = commodity.items[i].all_commodity + count;//原有基础上数量变动
                warehouse.addItem(commodity.items[i].name_commodity, time, count, people);//记录此次操作
                std::cout << "已记录此次操作" << std::endl;
                item = 1;
            }
        }
    }
    if (item == 0) {
        std::cout << "仓库中未存有该商品，请输入商品信息(类别，价格，总量，保质期)" << std::endl;
        std::string category; double price; int all, warranty;
        std::cin >> category >> price >> all >> warranty;//录入商品相关参数
        
        std::cout << "输入操作时间与操作人" << std::endl;
        std::string time, people;
        std::cin >> time >> people;
        std::tm time_temp = {};
        trans(time, time_temp);
        if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31  ||time_temp.tm_mon < 0 || time_temp.tm_mon>11) {
            std::cout << "时间范围出错，已退出此次操作" << std::endl;
            return;
        }
        else {
            commodity.additem(name, category, price, all, warranty);//插入商品列表
            warehouse.addItem(name, time, all, people);//记录此次操作
        }
        
    }
}

//商品出库操作
void commodity_chuku() {
    std::string name;
    std::cout << "输入要出库的商品名字" << std::endl;
    std::cin >> name;
    int item = 0;//插个眼
    for (int i = 0; i < commodity.items.size(); i++) {
        if (name.compare(commodity.items[i].name_commodity) == 0 ) {
            item = 1;
            std::string time, people; int count;
            std::cout << "输入操作时间，数量，操作人" << std::endl;
            std::cin >> time >> count >> people;
            if (count < 0) {
                std::cout << "出库参数出错" << std::endl;
                return;
            }
            if (commodity.items[i].all_commodity < count)//判断存货量与出货量
                std::cout << "该商品存货不足，无法出货" << std::endl;
            else {
                std::tm time_temp = {};
                trans(time, time_temp);
                if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31  || time_temp.tm_mon < 0 || time_temp.tm_mon>11) {
                    std::cout << "时间范围出错，已退出此次操作" << std::endl;
                    return;
                }
                warehouse.addItem(name,time,count,people);//记录此次操作
                commodity.items[i].all_commodity = commodity.items[i].all_commodity - count;//减去出库数量
                std::cout << "商品已出库，已记录此次操作" << std::endl;
            }
        }
    }
    if (item == 0)
        std::cout << "不存在该商品" << std::endl;
}

//商品价格排序
void sort_price() {
    for (int i = 0; i < commodity.items.size()-1; i++) {
        for (int j = 0; j < commodity.items.size() - i - 1; j++) {
            if (commodity.items[j].price_commodity < commodity.items[j+1].price_commodity) {
                commodityitem item = commodity.items[j];
                commodity.items[j] = commodity.items[j + 1];
                commodity.items[j + 1] = item;
            }
        }
    }
}

//商品保质期排序
void sort_warranty() {
    for (int i = 0; i < commodity.items.size() - 1; i++) {
        for (int j = 0; j < commodity.items.size() - i - 1; j++) {
            if (commodity.items[j].warranty_commodity < commodity.items[j + 1].warranty_commodity) {
                commodityitem item = commodity.items[j];
                commodity.items[j] = commodity.items[j + 1];
                commodity.items[j + 1] = item;
            }
        }
    }
}

//商品类别排序
void sort_category(){
    for (int i = 0; i < commodity.items.size() - 1; i++) {
        for (int j = 0; j < commodity.items.size() - i - 1; j++) {
            if (commodity.items[j].category_commodity < commodity.items[j + 1].category_commodity) {
                commodityitem item = commodity.items[j];
                commodity.items[j] = commodity.items[j + 1];
                commodity.items[j + 1] = item;
         }
        }
    }
}

//打印commodity类所有成员
void Printf_commodity() {
    std::cout << "商品代码      名称      类别      价格      总量      保质期（天）" << std::endl;
    for (int i = 0; i < commodity.items.size(); i++) {
        std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
            << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
    }
}//打印输出商品表单

//读取文件内商品信息
void fileread_commodity() {
    std::ifstream file("=-=.txt"); // 打开文件
    if (file.is_open()) { // 检查文件是否成功打开
        std::string line;
        while (std::getline(file, line)) { // 逐行读取文件内容,直到文件尾
            std::stringstream ss(line);//将读取的数据流转化为字符串
            std::string token;
            std::vector<std::string> tokens;//建立转换字符串数组
            while (std::getline(ss, token, ' ')) {
                tokens.push_back(token);
            }
            //对ss的字符串拆解成数个小字符串
            if (tokens.size() == 5) {//参数共五个，为一轮
                std::string name = tokens[0];
                std::string category = tokens[1];
                double price = std::stod(tokens[2]);
                int all = std::stoi(tokens[3]);
                int warranty = std::stoi(tokens[4]);
                commodity.additem(name, category, price, all, warranty);
            }
        }
        file.close(); // 关闭文件
    }
    else {
        std::cout << "无法打开文件" << std::endl;
    }
}

//将商品信息写入文件
void filewrite_commodity() {
    std::ofstream file("=-=.txt"); // 打开文件
    if (file.is_open()) {
        for (int i = 0; i < commodity.items.size(); i++) {
            file << commodity.items[i].name_commodity << " " << commodity.items[i].category_commodity << " " << commodity.items[i].price_commodity << " " << commodity.items[i].all_commodity << " " << commodity.items[i].warranty_commodity << std::endl;
        }
        file.close();
        std::cout << "数据已成功写入文件" << std::endl;
    }
    else {
        std::cout << "无法打开文件" << std::endl;
    }
}//将商品信息写入文件

//仓库读取文件
void fileread_warehouse() {
    std::ifstream file("warehouse.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);//将line内字符串流转换为字符串类型给ss
            std::vector<std::string> wares;
            std::string ware;
            //将ss字符串以空格为间隔拆分为多个字符串
            while (std::getline(ss, ware, ' ')) {
                wares.push_back(ware);
            }
            if (wares.size() == 4) {
                std::string name = wares[0];
                std::string time = wares[1];
                int count = std::stoi(wares[2]);
                std::string people = wares[3];
                warehouse.addItem(name, time, count, people);
            }
        }
    }
    else {
        std::cout << "无法打开文件" << std::endl;
    }

}

//仓库写入文件
void filewrite_warehouse() {
    std::ofstream opFile("warehouse.txt");
    if (opFile.is_open()) {
        for (int i = 0; i < warehouse.items.size(); i++) {
            opFile << warehouse.items[i].name_commodity << ' ' << warehouse.items[i].transactionTime << ' ' << warehouse.items[i].quantity << ' ' << warehouse.items[i].handler << std::endl;
        }
        opFile.close();
        std::cout << "操作成功" << std::endl;
    }
    else {
        std::cout << "操作失败" << std::endl;
    }
}

//商品查询
void find_commodity() {
    std::cout << "******************************************************************" << std::endl;
    std::cout << "           选择查询方法：1，代码查询   2，名字查询" << std::endl;
    std::cout << "******************************************************************" << std::endl;
    int temp = 0;
    std::string name;
    switch (_getch()) {
    case '1':
        system("cls");
        int id;
        std::cout << "输入商品代码" << std::endl;
        std::cin >> id;
        for (int i = 0; i < commodity.items.size(); i++) {
            if (commodity.items[i].id_commodity == id) {
                std::cout << "已在仓库中查询到此商品，该商品信息如下" << std::endl;
                std::cout << "商品代码      名称      类别      价格      总量      保质期（天）" << std::endl;
                std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
                    << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
                temp = 1;
            }
        }
        if (temp == 0) {
            std::cout << "未在仓库中查询到该商品信息" << std::endl;
        }
        break;
    case '2':
        system("cls");
        std::cout << "输入商品名称" << std::endl;
        std::cin >> name;
        for (int i = 0; i < commodity.items.size(); i++) {
            if (commodity.items[i].name_commodity == name) {
                std::cout << "已在仓库中查询到此商品，该商品信息如下" << std::endl;
                std::cout << "商品代码      名称      类别      价格      总量      保质期（天）" << std::endl;
                std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
                    << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
                temp = 1;
            }
        }
        if (temp == 0) {
            std::cout << "未在仓库中查询到该商品信息" << std::endl;
        }
        break;
    default:
        std::cout << "？？？？？？" << std::endl;
        break;
    }
}

//入库时间查询
void time_ruku() {
    std::cout << "输入入库时间范围,格式；year-month-day-time" << std::endl;
    std::cout << "起始时间:";
    std::string time_start;
    std::cin >> time_start;
    std::cout << "结束时间;";
    std::string time_end;
    std::cin >> time_end;
    std::tm time_temp = {};
    trans(time_start, time_temp);
    if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31 || time_temp.tm_mon < 0 || time_temp.tm_mon>11) {
        std::cout << "时间范围出错，已退出此次操作" << std::endl;
        return;
    }
    trans(time_end, time_temp);
    if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31 || time_temp.tm_mon < 0 || time_temp.tm_mon>11) {
        std::cout << "时间范围出错，已退出此次操作" << std::endl;
        return;
    }
    std::cout << "商品名称        操作时间        操作数量       操作人" << std::endl;
    for (int i = 0; i < warehouse.items.size(); i++) {
        if (time_start <= warehouse.items[i].transactionTime && time_end >= warehouse.items[i].transactionTime&&warehouse.items[i].quantity>0) {
            std::cout << std::setw(10) << warehouse.items[i].name_commodity << std::setw(20) << warehouse.items[i].transactionTime <<
                std::setw(11) << warehouse.items[i].quantity << std::setw(15) << warehouse.items[i].handler << std::endl;
        }
    }
}

//出库时间查询
void time_chuku() {
    std::cout << "输入出库时间范围,格式；year-month-day-time" << std::endl;
    std::cout << "起始时间:";
    std::string time_start;
    std::cin >> time_start;
    std::cout << "结束时间;";
    std::string time_end;
    std::cin >> time_end;
    std::tm time_temp = {};
    trans(time_start, time_temp);
    if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31 || time_temp.tm_mon < 0 || time_temp.tm_mon>11) {
        std::cout << "时间范围出错，已退出此次操作" << std::endl;
        return;
    }
    trans(time_end, time_temp);
    if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31 || time_temp.tm_mon < 0 || time_temp.tm_mon>11) {
        std::cout << "时间范围出错，已退出此次操作" << std::endl;
        return;
    }
    std::cout << "商品名称        操作时间        操作数量       操作人" << std::endl;
    for (int i = 0; i < warehouse.items.size(); i++) {
        if (time_start <= warehouse.items[i].transactionTime && time_end >= warehouse.items[i].transactionTime&&warehouse.items[i].quantity<0) {
            std::cout << std::setw(10) << warehouse.items[i].name_commodity << std::setw(20) << warehouse.items[i].transactionTime <<
                std::setw(11) << warehouse.items[i].quantity << std::setw(15) << warehouse.items[i].handler << std::endl;
        }
    }
}

//根据代码查询某个商品出入库信息
void id_churu() {
    std::cout << "输入查询商品代码" << std::endl;
    int id;
    std::cin >> id;
    std::string name;
    for (int i = 0; i < commodity.items.size(); i++) {
        if (id == commodity.items[i].id_commodity) {
            name = commodity.items[i].name_commodity;
            break;
        }     
    }
    std::cout << "选择输出类型：1，出库信息   2，入库信息   3，all" << std::endl;
    
    switch (_getch()) {
    std::cout << "商品名称        操作时间        操作数量       操作人" << std::endl;
    case '1':
        system("cls");
        for (int i = 0; i < warehouse.items.size(); i++) {
            if (name == warehouse.items[i].name_commodity&&warehouse.items[i].quantity<0) {
                std::cout << std::setw(8) << warehouse.items[i].transactionTime << std::setw(20) << warehouse.items[i].quantity << std::setw(8) << warehouse.items[i].handler << std::endl;
            }
        }
        break;
    case '2':
        system("cls");
        for (int i = 0; i < warehouse.items.size(); i++) {
            if (name == warehouse.items[i].name_commodity && warehouse.items[i].quantity > 0) {
                std::cout << std::setw(8) << warehouse.items[i].transactionTime << std::setw(8) << warehouse.items[i].quantity << std::setw(8) << warehouse.items[i].handler << std::endl;
            }
        }
        break;
    case '3':
        system("cls");
        for (int i = 0; i < warehouse.items.size(); i++) {
            if (name == warehouse.items[i].name_commodity ) {
                std::cout << std::setw(8) << warehouse.items[i].transactionTime << std::setw(8) << warehouse.items[i].quantity << std::setw(8) << warehouse.items[i].handler << std::endl;
            }
        }
        break;
    default:
        std::cout << "参数错误" << std::endl;
        break;
    }
}

//仓库浏览-类别
void browse_classify() {
    std::cout << "输入查询类别" << std::endl;
    std::string classify;
    std::cin >> classify;
    std::cout << "商品代码      名称      类别      价格      总量      保质期（天）" << std::endl;
    for (int i = 0; i < commodity.items.size(); i++) {
        if (classify == commodity.items[i].category_commodity) {
            std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
                << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
        }
   }
}

//库存预警(新增)
void warranty_all_commodity() {
    std::cout << "温馨提醒：" << std::endl;
    for (int i = 0; i < commodity.items.size(); i++) {
        if (commodity.items[i].all_commodity <= 10) {
            std::cout << "商品" << commodity.items[i].name_commodity << "库存数量为" << commodity.items[i].all_commodity << ",不足10,请及时补充" << std::endl;
        }
    }
}

//查询某个操作人的所有操作（新增）
void find_handler() {
    std::cout << "输入需要查询操作人的名字" << std::endl;
    std::string handler; std::cin >> handler;
    std::cout << "相关操作信息如下" << std::endl;
    std::cout << "商品名称           操作时间           操作数量      操作人" << std::endl;
    for (int i = 0; i < warehouse.items.size(); i++) {
        if (handler == warehouse.items[i].handler) {
            std::cout << std::setw(10) << warehouse.items[i].name_commodity << std::setw(20) << warehouse.items[i].transactionTime <<
                std::setw(10) << warehouse.items[i].quantity << std::setw(15) << warehouse.items[i].handler << std::endl;
        }
    }
}

//修改商品的某个值(新增)
void change_element() {
    std::cout << "输入需要更改属性的商品名字" << std::endl;
    std::string name; std::cin >> name; int temp = 0;
    std::cout << "目前商品信息为" << std::endl;
    std::cout << "商品代码      名称      类别      价格      总量      保质期（天）" << std::endl;
    for (int i = 0; i < commodity.items.size(); i++) {
        if (commodity.items[i].name_commodity == name) {
            temp = i;
            std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
                << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
        }
    }
    system("pause");
    std::cout << "选择需要更改的属性" << std::endl;
    std::cout << "1，商品名称   2，商品类别   3，商品价格   4，商品数量   5，商品保质期" << std::endl;
    switch (_getch()) {
    case '1':
        std::cout << "请输入修改后的值" << std::endl;
        std::cin >> name;
        commodity.items[temp].name_commodity = name;
        std::cout << "更改成功,更改后商品信息为" << std::endl;
        std::cout << "商品代码      名称      类别      价格      总量      保质期（天）" << std::endl;
        std::cout << std::setw(8) << commodity.items[temp].id_commodity << std::setw(10) << commodity.items[temp].name_commodity << std::setw(10) << commodity.items[temp].category_commodity << std::setw(10) << commodity.items[temp].price_commodity
            << std::setw(10) << commodity.items[temp].all_commodity << std::setw(10) << commodity.items[temp].warranty_commodity << std::endl;
        break;
    case '2':
        std::cout << "请输入修改后的值" << std::endl;
        std::cin >> commodity.items[temp].category_commodity;
        std::cout << "更改成功,更改后商品信息为" << std::endl;
        std::cout << "商品代码      名称      类别      价格      总量      保质期（天）" << std::endl;
        std::cout << std::setw(8) << commodity.items[temp].id_commodity << std::setw(10) << commodity.items[temp].name_commodity << std::setw(10) << commodity.items[temp].category_commodity << std::setw(10) << commodity.items[temp].price_commodity
            << std::setw(10) << commodity.items[temp].all_commodity << std::setw(10) << commodity.items[temp].warranty_commodity << std::endl;
        break;
    case '3':
        std::cout << "请输入修改后的值" << std::endl;
        std::cin >> commodity.items[temp].price_commodity;
        std::cout << "更改成功,更改后商品信息为" << std::endl;
        std::cout << "商品代码      名称      类别      价格      总量      保质期（天）" << std::endl;
        std::cout << std::setw(8) << commodity.items[temp].id_commodity << std::setw(10) << commodity.items[temp].name_commodity << std::setw(10) << commodity.items[temp].category_commodity << std::setw(10) << commodity.items[temp].price_commodity
            << std::setw(10) << commodity.items[temp].all_commodity << std::setw(10) << commodity.items[temp].warranty_commodity << std::endl;
        break;
    case '4':
        std::cout << "请输入修改后的值" << std::endl;
        std::cin >> commodity.items[temp].all_commodity;
        std::cout << "更改成功,更改后商品信息为" << std::endl;
        std::cout << "商品代码      名称      类别      价格      总量      保质期（天）" << std::endl;
        std::cout << std::setw(8) << commodity.items[temp].id_commodity << std::setw(10) << commodity.items[temp].name_commodity << std::setw(10) << commodity.items[temp].category_commodity << std::setw(10) << commodity.items[temp].price_commodity
            << std::setw(10) << commodity.items[temp].all_commodity << std::setw(10) << commodity.items[temp].warranty_commodity << std::endl;
        break;
    case '5':
        std::cout << "请输入修改后的值" << std::endl;
        std::cin >> commodity.items[temp].warranty_commodity;
        std::cout << "更改成功,更改后商品信息为" << std::endl;
        std::cout << "商品代码      名称      类别      价格      总量      保质期（天）" << std::endl;
        std::cout << std::setw(8) << commodity.items[temp].id_commodity << std::setw(10) << commodity.items[temp].name_commodity << std::setw(10) << commodity.items[temp].category_commodity << std::setw(10) << commodity.items[temp].price_commodity
            << std::setw(10) << commodity.items[temp].all_commodity << std::setw(10) << commodity.items[temp].warranty_commodity << std::endl;
        break;
    default:
        std::cout << "参数错误" << std::endl;
        break;
    }

}

//打印所有仓库操作(新增)
void Print_warehouse() {
    std::cout << "商品名称        操作时间        操作数量       操作人" << std::endl;
    for (int i = 0; i < warehouse.items.size(); i++) {
        std::cout << std::setw(10) << warehouse.items[i].name_commodity << std::setw(20) << warehouse.items[i].transactionTime <<
            std::setw(11) << warehouse.items[i].quantity << std::setw(15) << warehouse.items[i].handler << std::endl;
    }
}

//验证次数限制(新增)
bool limited_login() {
    int temp = 0;
    while (temp < 3) {
        system("cls");
        temp++;
        std::cout << "请输入账号：";
        std::string name; std::cin >> name;
        std::cout << std::endl << "请输入密码：";
        std::string password; std::cin >> password;
        if (login(name, password)) {
            std::cout << "验证成功" << std::endl;
            return 1;
        }
        else {
            std::cout << "验证失败" << std::endl;
            std::cout << "剩余" << (3 - temp) << "次验证机会" << std::endl;
            system("pause");
        }
    }
    return 0;
}

//格式化商品(新增)
void formatting_commodity() {
    std::cout << "是否对已存商品信息进行格式化操作(该操作不可逆，请谨慎考虑）,若执行，请输入yes，若不执行，请输入no或者其它字符" << std::endl;
    std::string option;
    std::cin >> option;
    if (option == "yes") {
        delete[] & commodity;
    }
    else {
        std::cout << "已退出本次操作" << std::endl;
    }
}

//格式化仓库(新增)
void formatting_warehouse() {
    std::cout << "是否对已存商品信息进行格式化操作(该操作不可逆，请谨慎考虑）,若执行，请输入yes，若不执行，请输入no或者其它字符" << std::endl;
    std::string option;
    std::cin >> option;
    if (option == "yes") {
        delete[] & warehouse;
    }
    else {
        std::cout << "已退出本次操作" << std::endl;
    }
}

//仓库浏览-已过期
void browse_warranty() {
    std::cout << "商品代码      名称      类别      价格      总量      保质期（天）" << std::endl;
    for (int i = 0; i < commodity.items.size(); i++) {
        //记录最新一次的商品入库时间
        std::string start_time = "2000-10-01-10:01";
        for (int j = 0; j < warehouse.items.size(); j++) {
            if (commodity.items[i].name_commodity == warehouse.items[j].name_commodity&&warehouse.items[j].quantity>0) {
                if (time_compare(start_time, warehouse.items[j].transactionTime) > 0) {
                        start_time = warehouse.items[j].transactionTime;
                }
            }
        }
        //最新一次的商品入库时间与当前时间做对比，若差值大于保质期，则过期，输出所有信息
        if (time_compare(start_time, gettime()) > commodity.items[i].warranty_commodity ) {
            std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
                << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
        }
    }
}

//仓库浏览-将要过期
void browse_willwarranty() {
    std::cout << "商品代码      名称      类别      价格      总量      保质期（天）" << std::endl;
    for (int i = 0; i < commodity.items.size(); i++) {
        //记录最新一次的商品入库时间
        std::string start_time = "2000-10-01-10:01";
        for (int j = 0; j < warehouse.items.size(); j++) {
            if (commodity.items[i].name_commodity == warehouse.items[j].name_commodity && warehouse.items[j].quantity > 0) {
                if (time_compare(start_time, warehouse.items[j].transactionTime) > 0) {
                    start_time = warehouse.items[j].transactionTime;
                }
            }
        }
        //最新一次的商品入库时间与当前时间做对比，若差值>0,<10，则差不多过期，输出所有信息
        double d = commodity.items[i].warranty_commodity-time_compare(start_time, gettime());
        if (d >0&& d<10) {
            std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
                << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

//菜单
void menu() {
    int a=1;
    while (1) {
        system("cls");
        std::cout << "******************************************************************" << std::endl;
        std::cout << "                         选择要进行的操作" << std::endl;
        std::cout << "******************************************************************" << std::endl;
        std::cout << "1,商品出入库管理      2,浏览      3,商品排序     4,查询   " << std::endl;
        std::cout << "5,商品信息修改        6,格式化    7,结束" << std::endl;
        std::cout << "******************************************************************" << std::endl;
        switch (_getch()) {
        case '1': 
            system("cls");
            a = 1;
            while (a==1) {
                std::cout << "******************************************************************" << std::endl;
                std::cout << "                        选择要进行的操作" << std::endl;
                std::cout << "******************************************************************" << std::endl;
                std::cout << "1,商品出库            2,商品入库           3,返回上一级" << std::endl;
                std::cout << "******************************************************************" << std::endl;
                switch (_getch()) {
                case '1':
                    system("cls");
                    std::cout << "商品出库" << std::endl;
                    commodity_chuku();
                    Printf_commodity();
                    system("pause");
                    system("cls");
                    break;
                case '2':
                    system("cls");
                    std::cout << "商品入库" << std::endl;
                    commodity_ruku();
                    Printf_commodity();
                    system("pause");
                    system("cls");
                    break;
                default:
                    a = 0;
                    break;
                }
            }
            break;
        case '2':
            system("cls");
            a = 1;
            while (a == 1) {
                std::cout << "******************************************************************" << std::endl;
                std::cout << "                          选择浏览的方式                   " << std::endl;
                std::cout << "******************************************************************" << std::endl;
                std::cout << "1,浏览某段时间出库商品   2,浏览已过期商品     3,浏览某一类商品    "<<
                std::endl << "4,浏览某段时间入库商品   5,浏览将要过期商品   6,浏览所有商品      "<<
                std::endl <<" 7,浏览仓库所有操作       8,返回上一级   "<<std::endl;
                std::cout << "******************************************************************" << std::endl;
                switch (_getch()) {
                case '1':
                    system("cls");
                    std::cout << "某段时间出库商品" << std::endl;
                    time_chuku();
                    system("pause");
                    system("cls");
                    break;
                case '2':
                    system("cls");
                    std::cout << "已过期商品(按照商品最新入库时间到当前计算机本地时间与商品保质期的排序)" << std::endl;
                    browse_warranty();
                    system("pause");
                    system("cls");
                    break;
                case '3':
                    system("cls");
                    std::cout << "某一类商品" << std::endl;
                    browse_classify();
                    system("pause");
                    system("cls");
                    break;
                case '4':
                    system("cls");
                    std::cout << "某段时间入库商品" << std::endl;
                    time_ruku();
                    system("pause");
                    system("cls");
                    break;
                case '5':
                    system("cls");
                    std::cout << "将要过期商品(按照商品最新入库时间到当前计算机本地时间与商品保质期的排序)" << std::endl;
                    browse_willwarranty();
                    system("pause");
                    system("cls");
                    break;
                
                case '6':
                    system("cls");
                    std::cout << "所有商品" << std::endl;
                    Printf_commodity();
                    system("pause");
                    system("cls");
                    break;
                case '7':
                    system("cls");
                    std::cout << "所有出入库操作" << std::endl;
                    Print_warehouse();
                    system("pause");
                    system("cls");
                    break;
                case '8':
                    a = 0;
                    system("cls");
                    break;
                default:
                    system("cls");
                    system("pause");
                    break;
                }
            }
            break;
        case '3':
            system("cls");
            a = 1;
            while (a == 1) {
                std::cout << "******************************************************************" << std::endl;
                std::cout << "                       选择要进行的操作" << std::endl;
                std::cout << "******************************************************************" << std::endl;
                std::cout << "   1,保质期排序   2,价格排序   3,类别排序   4,返回上一级" << std::endl;
                std::cout << "******************************************************************" << std::endl;
                switch (_getch()) {
                case '1':
                    system("cls");
                    std::cout << "保质期" << std::endl;
                    sort_warranty();
                    Printf_commodity();
                    system("pause");
                    break;
                case '2':
                    system("cls");
                    std::cout << "价格" << std::endl;
                    sort_price();
                    Printf_commodity();
                    system("pause");
                    break;
                case '3':
                    system("cls");
                    std::cout << "类别" << std::endl;
                    sort_category();
                    Printf_commodity();
                    system("pause");
                    break;
                case '4':
                    a = 0;
                    system("cls");
                    break;
                default:
                    system("cls");
                    system("pause");
                    break;
                }
           }
            break;
        case '4':
            system("cls");
            a = 1;
            while (a == 1) {
                std::cout << "***********************************************************************" << std::endl;
                std::cout << "                            选择要进行的操作" << std::endl;
                std::cout << "***********************************************************************" << std::endl;
                std::cout << "1,查询商品基本信息   2,查询商品出入库信息   3,查询某个操作者的所有操作" << std::endl<<
                             "4,返回上一级" << std::endl;
                std::cout << "***********************************************************************" << std::endl;
                switch (_getch()) {
                case '1':
                    system("cls");
                    find_commodity();
                    system("pause");
                    break;
                case '2':
                    system("cls");
                    id_churu();
                    system("pause");
                    break;
                case '3':
                    system("cls");
                    find_handler();
                    system("pause");
                    break;
                case '4':
                    system("cls");
                    a = 0;
                    break;
                default:
                    system("cls");
                    system("pause");
                    break;
                }
            }
            break;
        case '5':
            system("cls");
            change_element();
            system("pause");
            break;
        case '6':
            system("cls");
            a = 1;
            while (a == 1) {
                std::cout << "***********************************************************************" << std::endl;
                std::cout << "                            选择要进行的操作" << std::endl;
                std::cout << "***********************************************************************" << std::endl;
                std::cout << "        1,格式化商品信息       2,格式化仓库信息      3,返回上一级" << std::endl;
                std::cout << "***********************************************************************" << std::endl;
                switch (_getch()) {
                case '1':
                    system("cls");
                    formatting_commodity();
                    system("pause");
                    break;
                case '2':
                    system("cls");
                    formatting_warehouse();
                    system("pause");
                    break;
                case '3':
                    system("cls");
                    a = 0;
                    break;
                default:
                    system("cls");
                    system("pause");
                    break;
                }
            }
            system("pause");
            break;
        case '7':
            std::cout << "结束" << std::endl;
            filewrite_commodity();
            filewrite_warehouse();
            system("pause");
            return;
        default:
            break;
        }
    }
}//函数主菜单，副菜单

int main()
{   
    if (limited_login()) {
        std::cout << "进入系统" << std::endl;
        system("pause");
        system("cls");
        fileread_commodity();
        fileread_warehouse();
        warranty_all_commodity();
        Printf_commodity();
        system("pause");
        menu();
    }
    else {
        std::cout << "退出系统" << std::endl;
        return 0;
    }
    system("cls");
    Printf_commodity();
    Print_warehouse();

    return 0;
}


