//
//  main.cpp
//  lab1
//
//  Created by Pavel Ronaldo on 9/17/19.
//  Copyright © 2019 Pavel Ronaldo. All rights reserved.
//

/*
 Подчитать колечество прошедших дней между датами
 */

#include <iostream>
class Date{
private:
    bool leapyear;
    int day;
    int month;
    int year;
    bool leap(int)const;
    int maxday()const;
public:
    Date(int d,int m,int y):leapyear(leap(y)),day(d),month(m),year(y){};
    Date& operator+=(int);
    Date& operator-=(int);
    std::string operator-(Date&)const;
    bool operator==(Date&)const;
    friend std::ostream& operator<<(std::ostream&, const Date&);
};
bool Date::leap(int y)const{
    return ((y % 4 == 0 && y% 100 != 0) || y % 400);
}
int Date::maxday()const{
    int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(leapyear)days[1]=29;
    return days[month-1];
}
Date& Date::operator+=(int d){
    if(day+d>maxday()){
        d-=maxday()-day;
        if(++month>12){
            month=1;
            year++;
        }
        while(d/maxday()){
            if(++month>12){
                month=1;
                year++;
            }
            d-=maxday();
        }
        day=d;
    }
    else day+=d;
    return *this;
}
Date& Date::operator-=(int d){
    if(day-d<1){
        d-=day;
        if(--month==0){
            month=12;
            year--;
        }
        while(d/maxday()){
            d-=maxday();
            if(--month==0){
                month=12;
                year--;
            }
        }
        day=maxday()-d;
    }
    else day-=d;
    return *this;
}
#include <sstream> //stringstream
std::string Date::operator-(Date &dt)const{
    int d,m,y;
    if(year>=dt.year){
        y=year-dt.year;
        if(month>dt.month){
            m=month-dt.month;
            d=day+dt.maxday()-dt.day;
            if(d>dt.maxday())d-=dt.maxday();
            else --m;
            --y;
        }
        else {
            m=12-month+dt.month;
            d=dt.day+maxday()-day;
            if(d>maxday())d-=maxday();
            else --m;
        }
    }
    else {
        y=dt.year-year;
        if(month>dt.month){
            m=12-month+dt.month;
            d=day+dt.maxday()-dt.day;
            if(d>dt.maxday())d-=dt.maxday();
            else --m;
            --y;
        }
        else {
            m=dt.month-month;
            d=maxday()-day+dt.day;
            if(d>maxday())d-=maxday();
            else --m;
        }
    }
    std::string s;
    std::stringstream ss;
    ss<<d<<" days "<<m<<" month "<<y<<" years";
    getline(ss,s);
    return s;
}
bool Date::operator==(Date& dt)const{
    return day==dt.day && month==dt.month && year==dt.year;
}
std::ostream& operator<<(std::ostream &os, const Date &dt){
    std::string m[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    os<<dt.day<<" "<<m[dt.month-1]<<" "<<dt.year;
    return os;
}

int main(){
    int d,m,y,reduce,increase;
    std::cout<<"Enter first date (day month year): ";
    std::cin>>d>>m>>y;
    Date date(d,m,y);
    std::cout<<"Date = "<<date<<std::endl;
    std::cout<<"reduce  date by : ";//уменьшить дату на столько то дней
    std::cin>>reduce;
    date-=reduce;
    std::cout<<"Date = "<<date<<std::endl;
    std::cout<<"Increase date by : ";//увеличить дату
    std::cin>>increase;
    date+=increase;
    std::cout<<"Date = "<<date<<std::endl;
    std::cout<<"Enter second date (day month year): ";
    std::cin>>d>>m>>y;
    Date date2(d,m,y);
    std::cout<<"Date2 = "<<date2<<std::endl;
    std::cout<<"Dates are "<<(date==date2 ? "equal":"not equal")<<std::endl;
    std::cout<<"Date1 - Date2 = "<<date-date2<<std::endl;
    return 0;
}
 
