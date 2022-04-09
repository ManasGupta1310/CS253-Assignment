#include <bits/stdc++.h>
using namespace std;

bool isLeap(int y)
{
    if (y % 100 != 0 && y % 4 == 0 || y % 400 == 0)
        return true;

    return false;
}

int offsetDays(int d, int m, int y)
{
    int offset = d;

    switch (m - 1)
    {
    case 11:
        offset += 30;
    case 10:
        offset += 31;
    case 9:
        offset += 30;
    case 8:
        offset += 31;
    case 7:
        offset += 31;
    case 6:
        offset += 30;
    case 5:
        offset += 31;
    case 4:
        offset += 30;
    case 3:
        offset += 31;
    case 2:
        offset += 28;
    case 1:
        offset += 31;
    }

    if (isLeap(y) && m > 2)
        offset += 1;

    return offset;
}

void revoffsetDays(int offset, int y, int *d, int *m)
{
    int month[13] = {0, 31, 28, 31, 30, 31, 30,
                     31, 31, 30, 31, 30, 31};

    if (isLeap(y))
        month[2] = 29;

    int i;
    for (i = 1; i <= 12; i++)
    {
        if (offset <= month[i])
            break;
        offset = offset - month[i];
    }

    *d = offset;
    *m = i;
}

//-------------------------------------------------------------------------------------------

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date(int day, int month, int year)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    string addDays(int x)
    {
        int offset1 = offsetDays(day, month, year);
        int remDays = isLeap(year) ? (366 - offset1) : (365 - offset1);

        int year2, offset2;
        if (x <= remDays)
        {
            year2 = year;
            offset2 = offset1 + x;
        }

        else
        {
            x -= remDays;
            year2 = year + 1;
            int year2days = isLeap(year2) ? 366 : 365;
            while (x >= year2days)
            {
                x -= year2days;
                year2++;
                year2days = isLeap(year2) ? 366 : 365;
            }
            offset2 = x;
        }

        int month2, date2;
        revoffsetDays(offset2, year2, &date2, &month2);

        string s = to_string(date2) + "/" + to_string(month2) + "/" + to_string(year2);
        return s;
    }
};
