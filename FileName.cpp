#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <sstream>
#include <iomanip>
#include <ctime>
#pragma warning(disable:4996)

//��Ʒid���庯��
int generateId() {
    static int id = 10000000;  // ��̬����id����ʼ��Ϊ0
    return ++id;  // ����id������
}

//��Ʒ����
class commodityitem {
public:
    int id_commodity;//��Ʒ����
    std::string name_commodity;//��Ʒ����
    std::string category_commodity;//��Ʒ���
    double price_commodity;//��Ʒ�۸�
    int all_commodity;//��Ʒ����
    int warranty_commodity;//��Ʒ������

    commodityitem(int Id,std::string name, std::string category,double price,int all,int warranty)
        :id_commodity(Id),name_commodity(name),category_commodity(category),price_commodity(price),all_commodity(all),warranty_commodity(warranty)
    {
    }
    
};

//��Ʒ��̬���鴴���Լ���ʼ��
class Commodity {
public:
    std::vector<commodityitem> items;//������̬���飬�洢ÿһ����Ʒ
    int size = items.size();
    void additem(std::string name, std::string category, double price, int all, int warranty) {
        commodityitem newitem(generateId(), name, category, price, all, warranty);
        items.push_back(newitem);
    }//��ʼ��+��������β��

};//��Ʒ�����������Ʒ

//�ֿ��¼��ز���
class WarehouseItem
{
public:
    //int id_commodity;//��Ʒ����
    std::string name_commodity;//��Ʒ����
    std::string transactionTime;//ʱ��
    int quantity;//����
    std::string handler;//������

//���캯����ʼ��
    WarehouseItem(std::string time, int qty, std::string person)
        : transactionTime(time), quantity(qty), handler(person)
    {
    }

    WarehouseItem(std::string name,std::string time, int qty, std::string person)
        : name_commodity(name),transactionTime(time), quantity(qty), handler(person)
    {
    }//���캯������

//���ز���ʱ��
    std::string getTransactionTime()
    {
        return transactionTime;
    }
//���ز�������
    int getQuantity() 
    {
        return quantity;
    }
//����ִ����
    std::string getHandler()
    {
        return handler;
    }
};//�ֿ���Ʒ�࣬�洢��Ʒ����Ϣ

//�ֿ��¼��̬���鴴���Լ���ʼ��
class Warehouse
{
public:
    std::vector<WarehouseItem> items;//������̬���飬ÿ������Ԫ�ض���warehouseitem��ÿ���ֿ���Ʒ�ࣩ

    void addItem(std::string name,std::string time, int qty, std::string handler)
    {
        WarehouseItem newItem(name,time, qty, handler);
        items.push_back(newItem);
    }

    void addItem( std::string time, int qty, std::string handler)
    {
        WarehouseItem newItem(time, qty, handler);
        items.push_back(newItem);
    }//���ú�������ֿ�������µ���Ʒ��Ϣ������ʱ�䣬������������Ա
};//�ֿ��࣬����ֿ��е���Ʒ

////////////////////////////////////////////
//����ȫ�ֱ���
Commodity commodity;
Warehouse warehouse;
////////////////////////////////////////////

//ʱ���ַ���ת��tm�ṹ��
void trans(std::string Time, tm& time) {
    // ��ʼ��һ��std::tm�ṹ��
    std::istringstream iss(Time);
    std::string token;

    // �ֽ����
    std::getline(iss, token, '-');
    time.tm_year = std::stoi(token) - 1900;

    // �ֽ��·�
    std::getline(iss, token, '-');
    time.tm_mon = std::stoi(token) - 1;

    // �ֽ�����
    std::getline(iss, token, '-');
    time.tm_mday = std::stoi(token);

    // �ֽ�Сʱ
    std::getline(iss, token, ':');
    time.tm_hour = std::stoi(token);

    // �ֽ����
    std::getline(iss, token);
    time.tm_min = std::stoi(token);
}

//ʱ��ȽϺ���
double time_compare(std::string time_str1, std::string time_str2) {
    //һ��Ϊ������
    int day = 60 * 60 * 24;
    //����tm�࣬���ڴ洢����ʱ��
    struct tm time1_t = {}, time2_t = {};
    //���ַ������ʱ�����ת��������ṹ����
    trans(time_str1, time1_t);
    trans(time_str2, time2_t);
    //������ʱ��ת��Ϊ����Ϊ��λ������
    time_t time1 = mktime(&time1_t);
    time_t time2 = mktime(&time2_t);
    if (time1 != -1 && time2 != -1) {
        //����ʱ���ֵ
        double time_diff = difftime(time2, time1);
        return time_diff/day;
    }
    else {
        std::cout << "���ڽ�������" << std::endl;
        return -1;
    }
}

//��ȡ��ǰʱ��
std::string gettime() {
    // ��ȡ��ǰʱ��
    std::time_t currentTime = std::time(nullptr);

    // ��ʱ��ת��Ϊ����ʱ��
    std::tm* localTime = std::localtime(&currentTime);

    // �ӱ���ʱ������ȡ�ꡢ�¡��ա�Сʱ�����Ӻ���
    int year = localTime->tm_year + 1900;   // ����Ǵ�1900������ģ�������Ҫ����1900
    int month = localTime->tm_mon + 1;      // �·��Ǵ�0��ʼ�ģ�������Ҫ����1
    int day = localTime->tm_mday;
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    //���minutes<10���������ȱ�ٵ�0
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

//�˺�������֤
bool login(std::string username, std::string passwork) {
    //�����˺��������֤
    std::string Username = "Admin";
    std::string Passwork = "123456";
    if (username == Username && passwork == Passwork) 
        return true;
    else
        return false;
}//�˺�������֤

//��Ʒ������
void commodity_ruku() {
    std::string name;
    std::cout << "������Ʒ����" << std::endl;
    std::cin >> name;//��������
    int item = 0;//�����,�ж���Ʒ�Ƿ����
    //���Ȳ��Ҳֿ����Ƿ���ڸ����ֵ���Ʒ�������ڣ����ڴ˻������޸ģ��������ڣ��������
    for (int i = 0; i < commodity.items.size(); i++) {
        if (commodity.items[i].name_commodity == name) {
            std::cout << "�Ѵ��ڸ���Ʒ���������ʱ�䣬����������������" << std::endl;
            std::string time; int count; std::string people;
            std::cin >> time >> count >> people;//¼����ز���
            if (count < 0) {
                std::cout << "����������" << std::endl;
                return;
            }
            std::tm time_temp = {};
            trans(time, time_temp);
            if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31||time_temp.tm_mon<0||time_temp.tm_mon>11) {
                std::cout << "ʱ�䷶Χ�������˳��˴β���" << std::endl;
                return;
            }
            else {
                commodity.items[i].all_commodity = commodity.items[i].all_commodity + count;//ԭ�л����������䶯
                warehouse.addItem(commodity.items[i].name_commodity, time, count, people);//��¼�˴β���
                std::cout << "�Ѽ�¼�˴β���" << std::endl;
                item = 1;
            }
        }
    }
    if (item == 0) {
        std::cout << "�ֿ���δ���и���Ʒ����������Ʒ��Ϣ(��𣬼۸�������������)" << std::endl;
        std::string category; double price; int all, warranty;
        std::cin >> category >> price >> all >> warranty;//¼����Ʒ��ز���
        
        std::cout << "�������ʱ���������" << std::endl;
        std::string time, people;
        std::cin >> time >> people;
        std::tm time_temp = {};
        trans(time, time_temp);
        if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31  ||time_temp.tm_mon < 0 || time_temp.tm_mon>11) {
            std::cout << "ʱ�䷶Χ�������˳��˴β���" << std::endl;
            return;
        }
        else {
            commodity.additem(name, category, price, all, warranty);//������Ʒ�б�
            warehouse.addItem(name, time, all, people);//��¼�˴β���
        }
        
    }
}

//��Ʒ�������
void commodity_chuku() {
    std::string name;
    std::cout << "����Ҫ�������Ʒ����" << std::endl;
    std::cin >> name;
    int item = 0;//�����
    for (int i = 0; i < commodity.items.size(); i++) {
        if (name.compare(commodity.items[i].name_commodity) == 0 ) {
            item = 1;
            std::string time, people; int count;
            std::cout << "�������ʱ�䣬������������" << std::endl;
            std::cin >> time >> count >> people;
            if (count < 0) {
                std::cout << "�����������" << std::endl;
                return;
            }
            if (commodity.items[i].all_commodity < count)//�жϴ�����������
                std::cout << "����Ʒ������㣬�޷�����" << std::endl;
            else {
                std::tm time_temp = {};
                trans(time, time_temp);
                if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31  || time_temp.tm_mon < 0 || time_temp.tm_mon>11) {
                    std::cout << "ʱ�䷶Χ�������˳��˴β���" << std::endl;
                    return;
                }
                warehouse.addItem(name,time,count,people);//��¼�˴β���
                commodity.items[i].all_commodity = commodity.items[i].all_commodity - count;//��ȥ��������
                std::cout << "��Ʒ�ѳ��⣬�Ѽ�¼�˴β���" << std::endl;
            }
        }
    }
    if (item == 0)
        std::cout << "�����ڸ���Ʒ" << std::endl;
}

//��Ʒ�۸�����
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

//��Ʒ����������
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

//��Ʒ�������
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

//��ӡcommodity�����г�Ա
void Printf_commodity() {
    std::cout << "��Ʒ����      ����      ���      �۸�      ����      �����ڣ��죩" << std::endl;
    for (int i = 0; i < commodity.items.size(); i++) {
        std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
            << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
    }
}//��ӡ�����Ʒ��

//��ȡ�ļ�����Ʒ��Ϣ
void fileread_commodity() {
    std::ifstream file("=-=.txt"); // ���ļ�
    if (file.is_open()) { // ����ļ��Ƿ�ɹ���
        std::string line;
        while (std::getline(file, line)) { // ���ж�ȡ�ļ�����,ֱ���ļ�β
            std::stringstream ss(line);//����ȡ��������ת��Ϊ�ַ���
            std::string token;
            std::vector<std::string> tokens;//����ת���ַ�������
            while (std::getline(ss, token, ' ')) {
                tokens.push_back(token);
            }
            //��ss���ַ�����������С�ַ���
            if (tokens.size() == 5) {//�����������Ϊһ��
                std::string name = tokens[0];
                std::string category = tokens[1];
                double price = std::stod(tokens[2]);
                int all = std::stoi(tokens[3]);
                int warranty = std::stoi(tokens[4]);
                commodity.additem(name, category, price, all, warranty);
            }
        }
        file.close(); // �ر��ļ�
    }
    else {
        std::cout << "�޷����ļ�" << std::endl;
    }
}

//����Ʒ��Ϣд���ļ�
void filewrite_commodity() {
    std::ofstream file("=-=.txt"); // ���ļ�
    if (file.is_open()) {
        for (int i = 0; i < commodity.items.size(); i++) {
            file << commodity.items[i].name_commodity << " " << commodity.items[i].category_commodity << " " << commodity.items[i].price_commodity << " " << commodity.items[i].all_commodity << " " << commodity.items[i].warranty_commodity << std::endl;
        }
        file.close();
        std::cout << "�����ѳɹ�д���ļ�" << std::endl;
    }
    else {
        std::cout << "�޷����ļ�" << std::endl;
    }
}//����Ʒ��Ϣд���ļ�

//�ֿ��ȡ�ļ�
void fileread_warehouse() {
    std::ifstream file("warehouse.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);//��line���ַ�����ת��Ϊ�ַ������͸�ss
            std::vector<std::string> wares;
            std::string ware;
            //��ss�ַ����Կո�Ϊ������Ϊ����ַ���
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
        std::cout << "�޷����ļ�" << std::endl;
    }

}

//�ֿ�д���ļ�
void filewrite_warehouse() {
    std::ofstream opFile("warehouse.txt");
    if (opFile.is_open()) {
        for (int i = 0; i < warehouse.items.size(); i++) {
            opFile << warehouse.items[i].name_commodity << ' ' << warehouse.items[i].transactionTime << ' ' << warehouse.items[i].quantity << ' ' << warehouse.items[i].handler << std::endl;
        }
        opFile.close();
        std::cout << "�����ɹ�" << std::endl;
    }
    else {
        std::cout << "����ʧ��" << std::endl;
    }
}

//��Ʒ��ѯ
void find_commodity() {
    std::cout << "******************************************************************" << std::endl;
    std::cout << "           ѡ���ѯ������1�������ѯ   2�����ֲ�ѯ" << std::endl;
    std::cout << "******************************************************************" << std::endl;
    int temp = 0;
    std::string name;
    switch (_getch()) {
    case '1':
        system("cls");
        int id;
        std::cout << "������Ʒ����" << std::endl;
        std::cin >> id;
        for (int i = 0; i < commodity.items.size(); i++) {
            if (commodity.items[i].id_commodity == id) {
                std::cout << "���ڲֿ��в�ѯ������Ʒ������Ʒ��Ϣ����" << std::endl;
                std::cout << "��Ʒ����      ����      ���      �۸�      ����      �����ڣ��죩" << std::endl;
                std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
                    << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
                temp = 1;
            }
        }
        if (temp == 0) {
            std::cout << "δ�ڲֿ��в�ѯ������Ʒ��Ϣ" << std::endl;
        }
        break;
    case '2':
        system("cls");
        std::cout << "������Ʒ����" << std::endl;
        std::cin >> name;
        for (int i = 0; i < commodity.items.size(); i++) {
            if (commodity.items[i].name_commodity == name) {
                std::cout << "���ڲֿ��в�ѯ������Ʒ������Ʒ��Ϣ����" << std::endl;
                std::cout << "��Ʒ����      ����      ���      �۸�      ����      �����ڣ��죩" << std::endl;
                std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
                    << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
                temp = 1;
            }
        }
        if (temp == 0) {
            std::cout << "δ�ڲֿ��в�ѯ������Ʒ��Ϣ" << std::endl;
        }
        break;
    default:
        std::cout << "������������" << std::endl;
        break;
    }
}

//���ʱ���ѯ
void time_ruku() {
    std::cout << "�������ʱ�䷶Χ,��ʽ��year-month-day-time" << std::endl;
    std::cout << "��ʼʱ��:";
    std::string time_start;
    std::cin >> time_start;
    std::cout << "����ʱ��;";
    std::string time_end;
    std::cin >> time_end;
    std::tm time_temp = {};
    trans(time_start, time_temp);
    if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31 || time_temp.tm_mon < 0 || time_temp.tm_mon>11) {
        std::cout << "ʱ�䷶Χ�������˳��˴β���" << std::endl;
        return;
    }
    trans(time_end, time_temp);
    if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31 || time_temp.tm_mon < 0 || time_temp.tm_mon>11) {
        std::cout << "ʱ�䷶Χ�������˳��˴β���" << std::endl;
        return;
    }
    std::cout << "��Ʒ����        ����ʱ��        ��������       ������" << std::endl;
    for (int i = 0; i < warehouse.items.size(); i++) {
        if (time_start <= warehouse.items[i].transactionTime && time_end >= warehouse.items[i].transactionTime&&warehouse.items[i].quantity>0) {
            std::cout << std::setw(10) << warehouse.items[i].name_commodity << std::setw(20) << warehouse.items[i].transactionTime <<
                std::setw(11) << warehouse.items[i].quantity << std::setw(15) << warehouse.items[i].handler << std::endl;
        }
    }
}

//����ʱ���ѯ
void time_chuku() {
    std::cout << "�������ʱ�䷶Χ,��ʽ��year-month-day-time" << std::endl;
    std::cout << "��ʼʱ��:";
    std::string time_start;
    std::cin >> time_start;
    std::cout << "����ʱ��;";
    std::string time_end;
    std::cin >> time_end;
    std::tm time_temp = {};
    trans(time_start, time_temp);
    if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31 || time_temp.tm_mon < 0 || time_temp.tm_mon>11) {
        std::cout << "ʱ�䷶Χ�������˳��˴β���" << std::endl;
        return;
    }
    trans(time_end, time_temp);
    if (time_temp.tm_year < 0 || time_temp.tm_hour >= 24 || time_temp.tm_hour < 0 || time_temp.tm_mday < 0 || time_temp.tm_mday>31 || time_temp.tm_mon < 0 || time_temp.tm_mon>11) {
        std::cout << "ʱ�䷶Χ�������˳��˴β���" << std::endl;
        return;
    }
    std::cout << "��Ʒ����        ����ʱ��        ��������       ������" << std::endl;
    for (int i = 0; i < warehouse.items.size(); i++) {
        if (time_start <= warehouse.items[i].transactionTime && time_end >= warehouse.items[i].transactionTime&&warehouse.items[i].quantity<0) {
            std::cout << std::setw(10) << warehouse.items[i].name_commodity << std::setw(20) << warehouse.items[i].transactionTime <<
                std::setw(11) << warehouse.items[i].quantity << std::setw(15) << warehouse.items[i].handler << std::endl;
        }
    }
}

//���ݴ����ѯĳ����Ʒ�������Ϣ
void id_churu() {
    std::cout << "�����ѯ��Ʒ����" << std::endl;
    int id;
    std::cin >> id;
    std::string name;
    for (int i = 0; i < commodity.items.size(); i++) {
        if (id == commodity.items[i].id_commodity) {
            name = commodity.items[i].name_commodity;
            break;
        }     
    }
    std::cout << "ѡ��������ͣ�1��������Ϣ   2�������Ϣ   3��all" << std::endl;
    
    switch (_getch()) {
    std::cout << "��Ʒ����        ����ʱ��        ��������       ������" << std::endl;
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
        std::cout << "��������" << std::endl;
        break;
    }
}

//�ֿ����-���
void browse_classify() {
    std::cout << "�����ѯ���" << std::endl;
    std::string classify;
    std::cin >> classify;
    std::cout << "��Ʒ����      ����      ���      �۸�      ����      �����ڣ��죩" << std::endl;
    for (int i = 0; i < commodity.items.size(); i++) {
        if (classify == commodity.items[i].category_commodity) {
            std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
                << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
        }
   }
}

//���Ԥ��(����)
void warranty_all_commodity() {
    std::cout << "��ܰ���ѣ�" << std::endl;
    for (int i = 0; i < commodity.items.size(); i++) {
        if (commodity.items[i].all_commodity <= 10) {
            std::cout << "��Ʒ" << commodity.items[i].name_commodity << "�������Ϊ" << commodity.items[i].all_commodity << ",����10,�뼰ʱ����" << std::endl;
        }
    }
}

//��ѯĳ�������˵����в�����������
void find_handler() {
    std::cout << "������Ҫ��ѯ�����˵�����" << std::endl;
    std::string handler; std::cin >> handler;
    std::cout << "��ز�����Ϣ����" << std::endl;
    std::cout << "��Ʒ����           ����ʱ��           ��������      ������" << std::endl;
    for (int i = 0; i < warehouse.items.size(); i++) {
        if (handler == warehouse.items[i].handler) {
            std::cout << std::setw(10) << warehouse.items[i].name_commodity << std::setw(20) << warehouse.items[i].transactionTime <<
                std::setw(10) << warehouse.items[i].quantity << std::setw(15) << warehouse.items[i].handler << std::endl;
        }
    }
}

//�޸���Ʒ��ĳ��ֵ(����)
void change_element() {
    std::cout << "������Ҫ�������Ե���Ʒ����" << std::endl;
    std::string name; std::cin >> name; int temp = 0;
    std::cout << "Ŀǰ��Ʒ��ϢΪ" << std::endl;
    std::cout << "��Ʒ����      ����      ���      �۸�      ����      �����ڣ��죩" << std::endl;
    for (int i = 0; i < commodity.items.size(); i++) {
        if (commodity.items[i].name_commodity == name) {
            temp = i;
            std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
                << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
        }
    }
    system("pause");
    std::cout << "ѡ����Ҫ���ĵ�����" << std::endl;
    std::cout << "1����Ʒ����   2����Ʒ���   3����Ʒ�۸�   4����Ʒ����   5����Ʒ������" << std::endl;
    switch (_getch()) {
    case '1':
        std::cout << "�������޸ĺ��ֵ" << std::endl;
        std::cin >> name;
        commodity.items[temp].name_commodity = name;
        std::cout << "���ĳɹ�,���ĺ���Ʒ��ϢΪ" << std::endl;
        std::cout << "��Ʒ����      ����      ���      �۸�      ����      �����ڣ��죩" << std::endl;
        std::cout << std::setw(8) << commodity.items[temp].id_commodity << std::setw(10) << commodity.items[temp].name_commodity << std::setw(10) << commodity.items[temp].category_commodity << std::setw(10) << commodity.items[temp].price_commodity
            << std::setw(10) << commodity.items[temp].all_commodity << std::setw(10) << commodity.items[temp].warranty_commodity << std::endl;
        break;
    case '2':
        std::cout << "�������޸ĺ��ֵ" << std::endl;
        std::cin >> commodity.items[temp].category_commodity;
        std::cout << "���ĳɹ�,���ĺ���Ʒ��ϢΪ" << std::endl;
        std::cout << "��Ʒ����      ����      ���      �۸�      ����      �����ڣ��죩" << std::endl;
        std::cout << std::setw(8) << commodity.items[temp].id_commodity << std::setw(10) << commodity.items[temp].name_commodity << std::setw(10) << commodity.items[temp].category_commodity << std::setw(10) << commodity.items[temp].price_commodity
            << std::setw(10) << commodity.items[temp].all_commodity << std::setw(10) << commodity.items[temp].warranty_commodity << std::endl;
        break;
    case '3':
        std::cout << "�������޸ĺ��ֵ" << std::endl;
        std::cin >> commodity.items[temp].price_commodity;
        std::cout << "���ĳɹ�,���ĺ���Ʒ��ϢΪ" << std::endl;
        std::cout << "��Ʒ����      ����      ���      �۸�      ����      �����ڣ��죩" << std::endl;
        std::cout << std::setw(8) << commodity.items[temp].id_commodity << std::setw(10) << commodity.items[temp].name_commodity << std::setw(10) << commodity.items[temp].category_commodity << std::setw(10) << commodity.items[temp].price_commodity
            << std::setw(10) << commodity.items[temp].all_commodity << std::setw(10) << commodity.items[temp].warranty_commodity << std::endl;
        break;
    case '4':
        std::cout << "�������޸ĺ��ֵ" << std::endl;
        std::cin >> commodity.items[temp].all_commodity;
        std::cout << "���ĳɹ�,���ĺ���Ʒ��ϢΪ" << std::endl;
        std::cout << "��Ʒ����      ����      ���      �۸�      ����      �����ڣ��죩" << std::endl;
        std::cout << std::setw(8) << commodity.items[temp].id_commodity << std::setw(10) << commodity.items[temp].name_commodity << std::setw(10) << commodity.items[temp].category_commodity << std::setw(10) << commodity.items[temp].price_commodity
            << std::setw(10) << commodity.items[temp].all_commodity << std::setw(10) << commodity.items[temp].warranty_commodity << std::endl;
        break;
    case '5':
        std::cout << "�������޸ĺ��ֵ" << std::endl;
        std::cin >> commodity.items[temp].warranty_commodity;
        std::cout << "���ĳɹ�,���ĺ���Ʒ��ϢΪ" << std::endl;
        std::cout << "��Ʒ����      ����      ���      �۸�      ����      �����ڣ��죩" << std::endl;
        std::cout << std::setw(8) << commodity.items[temp].id_commodity << std::setw(10) << commodity.items[temp].name_commodity << std::setw(10) << commodity.items[temp].category_commodity << std::setw(10) << commodity.items[temp].price_commodity
            << std::setw(10) << commodity.items[temp].all_commodity << std::setw(10) << commodity.items[temp].warranty_commodity << std::endl;
        break;
    default:
        std::cout << "��������" << std::endl;
        break;
    }

}

//��ӡ���вֿ����(����)
void Print_warehouse() {
    std::cout << "��Ʒ����        ����ʱ��        ��������       ������" << std::endl;
    for (int i = 0; i < warehouse.items.size(); i++) {
        std::cout << std::setw(10) << warehouse.items[i].name_commodity << std::setw(20) << warehouse.items[i].transactionTime <<
            std::setw(11) << warehouse.items[i].quantity << std::setw(15) << warehouse.items[i].handler << std::endl;
    }
}

//��֤��������(����)
bool limited_login() {
    int temp = 0;
    while (temp < 3) {
        system("cls");
        temp++;
        std::cout << "�������˺ţ�";
        std::string name; std::cin >> name;
        std::cout << std::endl << "���������룺";
        std::string password; std::cin >> password;
        if (login(name, password)) {
            std::cout << "��֤�ɹ�" << std::endl;
            return 1;
        }
        else {
            std::cout << "��֤ʧ��" << std::endl;
            std::cout << "ʣ��" << (3 - temp) << "����֤����" << std::endl;
            system("pause");
        }
    }
    return 0;
}

//��ʽ����Ʒ(����)
void formatting_commodity() {
    std::cout << "�Ƿ���Ѵ���Ʒ��Ϣ���и�ʽ������(�ò��������棬��������ǣ�,��ִ�У�������yes������ִ�У�������no���������ַ�" << std::endl;
    std::string option;
    std::cin >> option;
    if (option == "yes") {
        delete[] & commodity;
    }
    else {
        std::cout << "���˳����β���" << std::endl;
    }
}

//��ʽ���ֿ�(����)
void formatting_warehouse() {
    std::cout << "�Ƿ���Ѵ���Ʒ��Ϣ���и�ʽ������(�ò��������棬��������ǣ�,��ִ�У�������yes������ִ�У�������no���������ַ�" << std::endl;
    std::string option;
    std::cin >> option;
    if (option == "yes") {
        delete[] & warehouse;
    }
    else {
        std::cout << "���˳����β���" << std::endl;
    }
}

//�ֿ����-�ѹ���
void browse_warranty() {
    std::cout << "��Ʒ����      ����      ���      �۸�      ����      �����ڣ��죩" << std::endl;
    for (int i = 0; i < commodity.items.size(); i++) {
        //��¼����һ�ε���Ʒ���ʱ��
        std::string start_time = "2000-10-01-10:01";
        for (int j = 0; j < warehouse.items.size(); j++) {
            if (commodity.items[i].name_commodity == warehouse.items[j].name_commodity&&warehouse.items[j].quantity>0) {
                if (time_compare(start_time, warehouse.items[j].transactionTime) > 0) {
                        start_time = warehouse.items[j].transactionTime;
                }
            }
        }
        //����һ�ε���Ʒ���ʱ���뵱ǰʱ�����Աȣ�����ֵ���ڱ����ڣ�����ڣ����������Ϣ
        if (time_compare(start_time, gettime()) > commodity.items[i].warranty_commodity ) {
            std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
                << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
        }
    }
}

//�ֿ����-��Ҫ����
void browse_willwarranty() {
    std::cout << "��Ʒ����      ����      ���      �۸�      ����      �����ڣ��죩" << std::endl;
    for (int i = 0; i < commodity.items.size(); i++) {
        //��¼����һ�ε���Ʒ���ʱ��
        std::string start_time = "2000-10-01-10:01";
        for (int j = 0; j < warehouse.items.size(); j++) {
            if (commodity.items[i].name_commodity == warehouse.items[j].name_commodity && warehouse.items[j].quantity > 0) {
                if (time_compare(start_time, warehouse.items[j].transactionTime) > 0) {
                    start_time = warehouse.items[j].transactionTime;
                }
            }
        }
        //����һ�ε���Ʒ���ʱ���뵱ǰʱ�����Աȣ�����ֵ>0,<10��������ڣ����������Ϣ
        double d = commodity.items[i].warranty_commodity-time_compare(start_time, gettime());
        if (d >0&& d<10) {
            std::cout << std::setw(8) << commodity.items[i].id_commodity << std::setw(10) << commodity.items[i].name_commodity << std::setw(10) << commodity.items[i].category_commodity << std::setw(10) << commodity.items[i].price_commodity
                << std::setw(10) << commodity.items[i].all_commodity << std::setw(10) << commodity.items[i].warranty_commodity << std::endl;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

//�˵�
void menu() {
    int a=1;
    while (1) {
        system("cls");
        std::cout << "******************************************************************" << std::endl;
        std::cout << "                         ѡ��Ҫ���еĲ���" << std::endl;
        std::cout << "******************************************************************" << std::endl;
        std::cout << "1,��Ʒ��������      2,���      3,��Ʒ����     4,��ѯ   " << std::endl;
        std::cout << "5,��Ʒ��Ϣ�޸�        6,��ʽ��    7,����" << std::endl;
        std::cout << "******************************************************************" << std::endl;
        switch (_getch()) {
        case '1': 
            system("cls");
            a = 1;
            while (a==1) {
                std::cout << "******************************************************************" << std::endl;
                std::cout << "                        ѡ��Ҫ���еĲ���" << std::endl;
                std::cout << "******************************************************************" << std::endl;
                std::cout << "1,��Ʒ����            2,��Ʒ���           3,������һ��" << std::endl;
                std::cout << "******************************************************************" << std::endl;
                switch (_getch()) {
                case '1':
                    system("cls");
                    std::cout << "��Ʒ����" << std::endl;
                    commodity_chuku();
                    Printf_commodity();
                    system("pause");
                    system("cls");
                    break;
                case '2':
                    system("cls");
                    std::cout << "��Ʒ���" << std::endl;
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
                std::cout << "                          ѡ������ķ�ʽ                   " << std::endl;
                std::cout << "******************************************************************" << std::endl;
                std::cout << "1,���ĳ��ʱ�������Ʒ   2,����ѹ�����Ʒ     3,���ĳһ����Ʒ    "<<
                std::endl << "4,���ĳ��ʱ�������Ʒ   5,�����Ҫ������Ʒ   6,���������Ʒ      "<<
                std::endl <<" 7,����ֿ����в���       8,������һ��   "<<std::endl;
                std::cout << "******************************************************************" << std::endl;
                switch (_getch()) {
                case '1':
                    system("cls");
                    std::cout << "ĳ��ʱ�������Ʒ" << std::endl;
                    time_chuku();
                    system("pause");
                    system("cls");
                    break;
                case '2':
                    system("cls");
                    std::cout << "�ѹ�����Ʒ(������Ʒ�������ʱ�䵽��ǰ���������ʱ������Ʒ�����ڵ�����)" << std::endl;
                    browse_warranty();
                    system("pause");
                    system("cls");
                    break;
                case '3':
                    system("cls");
                    std::cout << "ĳһ����Ʒ" << std::endl;
                    browse_classify();
                    system("pause");
                    system("cls");
                    break;
                case '4':
                    system("cls");
                    std::cout << "ĳ��ʱ�������Ʒ" << std::endl;
                    time_ruku();
                    system("pause");
                    system("cls");
                    break;
                case '5':
                    system("cls");
                    std::cout << "��Ҫ������Ʒ(������Ʒ�������ʱ�䵽��ǰ���������ʱ������Ʒ�����ڵ�����)" << std::endl;
                    browse_willwarranty();
                    system("pause");
                    system("cls");
                    break;
                
                case '6':
                    system("cls");
                    std::cout << "������Ʒ" << std::endl;
                    Printf_commodity();
                    system("pause");
                    system("cls");
                    break;
                case '7':
                    system("cls");
                    std::cout << "���г�������" << std::endl;
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
                std::cout << "                       ѡ��Ҫ���еĲ���" << std::endl;
                std::cout << "******************************************************************" << std::endl;
                std::cout << "   1,����������   2,�۸�����   3,�������   4,������һ��" << std::endl;
                std::cout << "******************************************************************" << std::endl;
                switch (_getch()) {
                case '1':
                    system("cls");
                    std::cout << "������" << std::endl;
                    sort_warranty();
                    Printf_commodity();
                    system("pause");
                    break;
                case '2':
                    system("cls");
                    std::cout << "�۸�" << std::endl;
                    sort_price();
                    Printf_commodity();
                    system("pause");
                    break;
                case '3':
                    system("cls");
                    std::cout << "���" << std::endl;
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
                std::cout << "                            ѡ��Ҫ���еĲ���" << std::endl;
                std::cout << "***********************************************************************" << std::endl;
                std::cout << "1,��ѯ��Ʒ������Ϣ   2,��ѯ��Ʒ�������Ϣ   3,��ѯĳ�������ߵ����в���" << std::endl<<
                             "4,������һ��" << std::endl;
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
                std::cout << "                            ѡ��Ҫ���еĲ���" << std::endl;
                std::cout << "***********************************************************************" << std::endl;
                std::cout << "        1,��ʽ����Ʒ��Ϣ       2,��ʽ���ֿ���Ϣ      3,������һ��" << std::endl;
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
            std::cout << "����" << std::endl;
            filewrite_commodity();
            filewrite_warehouse();
            system("pause");
            return;
        default:
            break;
        }
    }
}//�������˵������˵�

int main()
{   
    if (limited_login()) {
        std::cout << "����ϵͳ" << std::endl;
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
        std::cout << "�˳�ϵͳ" << std::endl;
        return 0;
    }
    system("cls");
    Printf_commodity();
    Print_warehouse();

    return 0;
}


