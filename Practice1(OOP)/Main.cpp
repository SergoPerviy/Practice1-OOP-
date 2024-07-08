#include <iostream>


class Date {
private:
    size_t day;
    size_t month;
    size_t year;
    size_t hour;
    size_t minute;
    size_t second;
    size_t totalSeconds;
    static size_t totalObjects;
    size_t id;

public:
    Date():Date(1, 1, 2000){}
    Date(size_t day, size_t month, size_t year, size_t hour = 0, size_t minute = 0, size_t second = 0) {
        this->day = day;
        this->month = month;
        this->year = year;
        this->hour = hour;
        this->minute = minute;
        this->second = second;

        totalSeconds = calculateTotalSeconds();
        
        ++totalObjects;
        id = totalObjects;
    }

    Date(const Date& other) {
        day = other.day;
        month = other.month;
        year = other.year;
        hour = other.hour;
        minute = other.minute;
        second = other.second;
        totalSeconds = other.totalSeconds;
        ++totalObjects;
        id = totalObjects;
    }

    Date(size_t second) {
        for (size_t i = 1; i < 13; ++i) {
            if (i == 2) { 
                day = second / 365 % 28;
            }
            else if (i == 4 || i == 6 || i == 9 || i == 11) {
                day = second / 365 % 30; 
            }
            else {
                day = second / 365 % 31; 
            }
        }
        hour = second / 365 % 24;
        minute = second / 365 / 24 % 60;
        this->second = second % 60;
        year = second / 365;
        month = second / 365 % 12;
        ++totalObjects;
        id = totalObjects;        
    }

    size_t calculateTotalSeconds() const {
        size_t totalSeconds = 0;

        totalSeconds += second;
        totalSeconds += minute * 60;
        totalSeconds += hour * 3600;

        // Вычисление дней в текущем году до начала текущего месяца
        for (size_t i = 1; i < month; ++i) {
            if (i == 2) { 
                totalSeconds += 28 * 86400; 
            }
            else if (i == 4 || i == 6 || i == 9 || i == 11) {
                totalSeconds += 30 * 86400; 
            }
            else {
                totalSeconds += 31 * 86400; 
            }
        }

        // Вычисление лет в секундах начиная с 2000 года
        totalSeconds += (year - 2000) * 365 * 86400;

        return totalSeconds;
    }

    void printDate() const {
        std::cout << "Дата: " << day << "." << month << "." << year << " " << hour << ":" << minute << ":" << second << std::endl;
    }

    size_t getDay() const { return day; }
    size_t getMonth() const { return month; }
    size_t getYear() const { return year; }
    size_t getHour() const { return hour; }
    size_t getMinute() const { return minute; }
    size_t getSecond() const { return second; }
    size_t getTotalSeconds() const { return totalSeconds; }
    static size_t getTotalObjects() { return totalObjects; }
    size_t getId() const { return id; }

    //Метод вычитания
    Date operator-(const Date& other) const {
        size_t diffInSeconds = totalSeconds - other.totalSeconds;
        return Date(0, 0, 0, 0, 0, diffInSeconds);
    }

    //Метод присваивания
    Date& operator=(const Date& other) {
        day = other.day;
        month = other.month;
        year = other.year;
        hour = other.hour;
        minute = other.minute;
        second = other.second;
        totalSeconds = other.totalSeconds;
        return *this;
    }

    //Методы сравнения
    bool operator>(const Date& other) const {
        return totalSeconds > other.totalSeconds;
    }

    bool operator<(const Date& other) const {
        return totalSeconds < other.totalSeconds;
    }

    bool operator>=(const Date& other) const {
        return totalSeconds >= other.totalSeconds;
    }

    bool operator<=(const Date& other) const {
        return totalSeconds <= other.totalSeconds;
    }

    bool operator!=(const Date& other) const {
        return totalSeconds != other.totalSeconds;
    }

    bool operator==(const Date& other) const {
        return totalSeconds == other.totalSeconds;
    }
};

size_t Date::totalObjects = 0;

int main() {
    setlocale(LC_ALL, "Russian");

    //Создание объектов класса
    Date date1(1, 2, 2001, 00, 00, 00);
    Date date2(1, 1, 2001, 00, 00, 00);
    Date date3;
    Date date4(100000);
    

    //Демонстрация работы функции вывода в консоль
    date1.printDate();
    date2.printDate();
    date3.printDate();
    date4.printDate();

    //Демонстрация работы подсчета секунд прошедших с 1 января 2000 г.

    std::cout << "Разница в секундах Дата1: " << date1.getTotalSeconds() << std::endl;
    std::cout << "Разница в секундах Дата2: " << date2.getTotalSeconds() << std::endl;
    std::cout << "Разница в секундах Дата3: " << date3.getTotalSeconds() << std::endl;

    //Демонстрация работы метода вычитания
    (date1 - (date2)).printDate();

    //Демонстрация работы методов сравнения
    if (date1 > date2) {
        std::cout << "Дата1 больше Дата2" << std::endl;
    }

    if (date1 <= date2) {
        std::cout << "Дата1 не больше Дата2" << std::endl;
    }

    //Демонстрация работы метода присваивания
    date2 = date1;
    date2.printDate();

    //Демонстрация работы геттров
    std::cout << date1.getDay() << std::endl;
    std::cout << date1.getMonth() << std::endl;
    std::cout << date1.getYear() << std::endl;
    std::cout << date1.getHour() << std::endl;
    std::cout << date1.getMinute() << std::endl;
    std::cout << date1.getSecond() << std::endl;

    //Демонстрация работы метода получения id
    std::cout << "Дата1 id: " << date1.getId() << std::endl;
    std::cout << "Дата2 id: " << date2.getId() << std::endl;
    std::cout << "Дата3 id: " << date3.getId() << std::endl;

    //Демонстрация работы метода получения общего количества объектов:
    std::cout << "Общее количество объектов класса: " << Date::getTotalObjects() << std::endl;

    return 0;
}