#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int calculateDayOfWeek(int year, int month)
{
    // 如果是1月或2月，将其视为上一年的13月或14月
    if (month == 1 || month == 2)
    {
        month += 12;
        year -= 1;
    }

    int K = year % 100; // 年份的后两位
    int J = year / 100; // 年份的前两位

    // 蔡勒公式计算
    int h = ((13 * (month + 1)) / 5 + K + K / 4 + J / 4 + 5 * J+1) % 7;

    return h;
}

int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int year, int month)
{
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    default:
        return 0;
    }
}



void printCalendar(int year, int month)
{
    const char *monthNames[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};
    const char *daysOfWeek[] = {"Sun","Mon","Tue", "Wed", "Thu", "Fri", "Sat"};

    printf("\n     %s %d\n", monthNames[month - 1], year);
    for (int i = 0; i < 7; i++)
    {
        printf("%s ", daysOfWeek[i]);
    }
    printf("\n");

    int daysInMonth = getDaysInMonth(year, month);
    int startDay = calculateDayOfWeek(year, month); // 1号是星期几

    // 打印日历空格
    for (int i = 1; i < startDay; i++)
    {
        printf("    ");
    }

    // 打印日期
    for (int day = 1; day <= daysInMonth; day++)
    {
        printf("%3d ", day);
        if ((startDay + day - 1) % 7 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}

void navigateCalendar(int *year, int *month)
{
    int ch;
    do
    {
        system("cls"); // 清屏
        printCalendar(*year,*month);
        printf("Please Use Your Keyboard:<- ^ -> v(Press ESC to exit)\n");
        ch = getch();
        if (ch == 0 || ch == 224)
        {
            ch = getch(); // 获取第二个字节的键码...第二个是我们想要的
        }

        switch (ch)
        {
        case 72: // 上箭头表示上一年
            (*year)--;
            break;
        case 80: // 下箭头表示下一年
            (*year)++;
            break;
        case 75: // 左箭头表示上一个月
            (*month)--;
            if (*month < 1)
            {
                *month = 12;
                (*year)--;
            }
            break;
        case 77: // 右箭头表示下一个月
            (*month)++;
            if (*month > 12)
            {
                *month = 1;
                (*year)++;
            }
            break;
        }
    } while (ch != 27); // 27 是 ESC 的 ASCII 码，按下 ESC 键退出循环
}

int main()
{
    int year, month, day;
    int choice;
    int ch;
    
    // 输入年、月、日
    scanf("%d %d", &year, &month);

    // 计算星期几
    int dayOfWeek = calculateDayOfWeek(year, month);

    // 输出结果
    const char *daysOfWeek[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    do
    {
        printCalendar(year, month);
        printf("Please select an option: \n");
        printf("(1)Enter New Year Month***********\n");
        printf("(2)Switch between months and years\n");
        printf("(3)Quit***************************\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                system("cls");
                printf("Please Enter Year Month Day\n*****************************\nEg:2024 9\n");
                scanf("%d %d", &year, &month);
                break;
            case 2:
                system("cls");
                navigateCalendar(&year, &month);
                break;
            case 3:
                system("cls");
                printf("Existing......");
                      }

    } 
    while (choice != 3);

    return 0;
}
