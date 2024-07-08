#include <iostream>
#include <ctime>

class Date {
private:
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
    size_t totalSeconds;
    static int totalObjects;
    int id;

public:
    Date():Date(1, 1, 2000, 0, 0, 0){}
    Date(int day, int month, int year, int hour, int minute, int second) {
        this->day = day;
        this->month = month;
        this->year = year;
        this->hour = hour;
        this->minute = minute;
        this->second = second;

        totalSeconds = calculateTotalSeconds();

        totalObjects++;
        id = totalObjects;
    }

    size_t calculateTotalSeconds() const {
        size_t totalSeconds = 0;

        totalSeconds += second;
        totalSeconds += minute * 60;
        totalSeconds += hour * 3600;

        // Вычисление дней в текущем году до начала текущего месяца
        for (int i = 1; i < month; ++i) {
            if (i == 2) { // Февраль
                totalSeconds += 28 * 86400; 
            }
            else if (i == 4 || i == 6 || i == 9 || i == 11) {
                totalSeconds += 30 * 86400; // Месяцы с 30 днями
            }
            else {
                totalSeconds += 31 * 86400; // Месяцы с 31 днем
            }
        }

        //totalSeconds += (day - 1) * 86400;

        //// Вычисление лет в секундах начиная с 2000 года
        //totalSeconds += (year - 2000) * 365 * 86400;

        return totalSeconds;
    }

    void printDate() const {
        std::cout << "Дата: " << day << "." << month << "." << year << " " << hour << ":" << minute << ":" << second << std::endl;
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }
    size_t getTotalSeconds() const { return totalSeconds; }
    static int getTotalObjects() { return totalObjects; }
    int getId() const { return id; }

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

int Date::totalObjects = 0;

int main() {
    setlocale(LC_ALL, "Russian");
    Date date1(1, 3, 2000, 00, 00, 00);
    Date date2(1, 2, 2000, 00, 00, 00);

    date1.printDate();
    date2.printDate();

    Date date3 = date1 - date2;
    date3.printDate();
    std::cout << "Разница в секундах: " << date3.getTotalSeconds() << std::endl;

    if (date1 > date2) {
        std::cout << "Дата1 больше Дата2" << std::endl;
    }

    if (date1 <= date2) {
        std::cout << "Дата1 не больше Дата2" << std::endl;
    }

    date2 = date1;
    date2.printDate();

    return 0;
}