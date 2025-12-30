#include <cs50.h>
#include <stdio.h>

// Максимален брой кампании, които програмата може да пази
#define MAX 50

// ANSI цветови кодове – за оцветяване на текста в терминала
#define GREEN  "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET  "\x1b[0m"

// Структура, която описва една рекламна кампания
typedef struct
{
    string name;        // Име на кампанията
    string platform;    // Платформа (Facebook, Google и т.н.)
    float budget;       // Бюджет на кампанията
    int clicks;         // Брой кликове
    float revenue;      // Приход от кампанията
    float cpc;          // Цена на един клик (Cost Per Click)
    float roi;          // Възвръщаемост (%) – Return On Investment
} Campaign;

// Глобален масив за кампаниите
Campaign campaigns[MAX];

// Брояч – колко кампании са добавени
int count = 0;

// Декларации на функциите
void add_campaign(void);
void show_all(void);
void show_best(void);

int main(void)
{
    // Безкраен цикъл – програмата работи, докато не изберем Exit
    while (1)
    {
        // Меню
        printf("\n=== Simple Campaign Tracker ===\n");
        printf("1. Add campaign\n");
        printf("2. Show all campaigns\n");
        printf("3. Best campaign (by ROI)\n");
        printf("4. Exit\n");

        // Въвеждане на избор от потребителя
        int choice = get_int("Choose (1-4): ");

        // Проверка на избора
        if (choice == 1)
            add_campaign();
        else if (choice == 2)
            show_all();
        else if (choice == 3)
            show_best();
        else if (choice == 4)
        {
            printf("Goodbye!\n");
            return 0; // край на програмата
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }
}

// Функция за добавяне на нова кампания
void add_campaign(void)
{
    // Проверка дали масивът не е пълен
    if (count >= MAX)
    {
        printf("Campaign capacity reached.\n");
        return;
    }

    printf("\n--- Add Campaign ---\n");

    // Въвеждане на данни от потребителя
    string name = get_string("Name: ");
    string platform = get_string("Platform: ");
    float budget = get_float("Budget: ");
    int clicks = get_int("Clicks: ");
    float revenue = get_float("Revenue: ");

    // Проверка за невалидни (отрицателни) стойности
    if (budget < 0 || revenue < 0 || clicks < 0)
    {
        printf("Values must be non-negative.\n");
        return;
    }

    // Изчисляване на цена на клик
    float cpc = (clicks > 0) ? budget / clicks : 0;

    // Изчисляване на ROI в проценти
    float roi = (budget > 0) ? ((revenue - budget) / budget) * 100 : 0;

    // Записване на данните в масива
    campaigns[count].name = name;
    campaigns[count].platform = platform;
    campaigns[count].budget = budget;
    campaigns[count].clicks = clicks;
    campaigns[count].revenue = revenue;
    campaigns[count].cpc = cpc;
    campaigns[count].roi = roi;

    // Увеличаваме броя на кампаниите
    count++;

    // Потвърждение
    printf(GREEN "Campaign added successfully!\n" RESET);
}

// Функция за показване на всички кампании
void show_all(void)
{
    // Ако няма добавени кампании
    if (count == 0)
    {
        printf("No campaigns added yet.\n");
        return;
    }

    printf("\n--- All Campaigns ---\n");

    // Заглавен ред на таблицата
    printf("%-3s %-15s %-12s %-10s %-8s %-10s %-7s\n",
           "#", "Name", "Platform", "Budget", "Clicks", "Revenue", "ROI");

    // Печат на всяка кампания
    for (int i = 0; i < count; i++)
    {
        printf("%-3d %-15s %-12s %-10.2f %-8d %-10.2f %.2f%%\n",
               i + 1,
               campaigns[i].name,
               campaigns[i].platform,
               campaigns[i].budget,
               campaigns[i].clicks,
               campaigns[i].revenue,
               campaigns[i].roi);
    }
}

// Функция за показване на кампанията с най-висок ROI
void show_best(void)
{
    // Ако няма кампании
    if (count == 0)
    {
        printf("No campaigns added yet.\n");
        return;
    }

    // Приемаме първата кампания за най-добра
    int best = 0;

    // Търсим кампания с по-висок ROI
    for (int i = 1; i < count; i++)
    {
        if (campaigns[i].roi > campaigns[best].roi)
        {
            best = i;
        }
    }

    // Показване на най-добрата кампания
    printf("\n--- Best Campaign (by ROI) ---\n");
    printf("Name: " GREEN "%s" RESET "\n", campaigns[best].name);
    printf("Platform: %s\n", campaigns[best].platform);
    printf("ROI: " YELLOW "%.2f%%" RESET "\n", campaigns[best].roi);
}

