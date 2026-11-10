#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FLASK_SIZE 3

#define RESET "\033[0m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

typedef struct
{
    int liquid[FLASK_SIZE];
    int count;
} bottle;

const char *get_color(int color)
{

    switch (color)
    {

    case 1:
        return BG_GREEN;

    case 2:
        return BG_RED;

    case 3:
        return BG_YELLOW;

    case 4:
        return BG_BLUE;

    case 5:
        return BG_MAGENTA;

    case 6:
        return BG_CYAN;

    default:
        return BG_WHITE;
    }
}

void shuffle(int arr[], int size)
{

    for (int i = size - 1; i > 0; i--)
    {

        int j = rand() % (i + 1);

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void init_bottles(bottle bottles[], int n)
{

    int total = (n - 1) * FLASK_SIZE;

    int *colors = malloc(total * sizeof(int));

    if (colors == NULL)
    {

        printf("Memory allocation failed.\n");
        exit(1);
    }

    int k = 0;

    for (int color = 1; color <= n - 1; color++)
    {

        for (int j = 0; j < FLASK_SIZE; j++)
        {

            colors[k] = color;
            k++;
        }
    }

    shuffle(colors, total);

    for (int i = 0; i < n; i++)
    {

        bottles[i].count = 0;

        for (int j = 0; j < FLASK_SIZE; j++)
        {

            bottles[i].liquid[j] = 0;
        }
    }

    k = 0;

    for (int i = 0; i < n - 1; i++)
    {

        for (int j = 0; j < FLASK_SIZE; j++)
        {

            bottles[i].liquid[j] = colors[k];
            bottles[i].count++;

            k++;
        }
    }

    for (int i = n - 1; i > 0; i--)
    {

        int j = rand() % (i + 1);

        bottle temp = bottles[i];
        bottles[i] = bottles[j];
        bottles[j] = temp;
    }

    free(colors);
}

void display_bottles(bottle bottles[], int n)
{

    printf("\n");

    for (int row = FLASK_SIZE - 1; row >= 0; row--)
    {

        for (int i = 0; i < n; i++)
        {

            printf("|");

            if (row < bottles[i].count)
            {

                int color = bottles[i].liquid[row];

                printf("%s  %s", get_color(color), RESET);
            }
            else
            {

                printf("  ");
            }

            printf("| ");
        }

        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {

        printf(" %d   ", i + 1);
    }

    printf("\n\n");
}

int is_valid_step(bottle bottles[], int from, int to)
{

    if (from == to)
    {
        return 0;
    }

    if (bottles[from].count == 0)
    {
        return 0;
    }

    if (bottles[to].count == FLASK_SIZE)
    {
        return 0;
    }

    int source_color =
        bottles[from].liquid[bottles[from].count - 1];

    if (bottles[to].count == 0)
    {
        return 1;
    }

    int target_color =
        bottles[to].liquid[bottles[to].count - 1];

    return source_color == target_color;
}

void make_step(bottle bottles[], int from, int to)
{

    if (!is_valid_step(bottles, from, to))
    {

        printf("Invalid step!\n");
        return;
    }

    int color =
        bottles[from].liquid[bottles[from].count - 1];

    bottles[from].count--;

    bottles[to].liquid[bottles[to].count] = color;

    bottles[to].count++;
}

int is_finished(bottle bottles[], int n)
{

    for (int i = 0; i < n; i++)
    {

        if (bottles[i].count == 0)
        {
            continue;
        }

        if (bottles[i].count != FLASK_SIZE)
        {
            return 0;
        }

        int first = bottles[i].liquid[0];

        for (int j = 1; j < FLASK_SIZE; j++)
        {

            if (bottles[i].liquid[j] != first)
            {
                return 0;
            }
        }
    }

    return 1;
}

int read_input(int n, char text[])
{

    char ch;

    printf("%s", text);

    scanf(" %c", &ch);

    if (ch == 'q' || ch == 'Q')
    {
        return -1;
    }

    if (ch < '1' || ch > '7')
    {

        printf("Invalid input!\n");
        return 0;
    }

    int number = ch - '0';

    if (number < 1 || number > n)
    {

        printf("Invalid bottle number!\n");
        return 0;
    }

    return number;
}

int main()
{

    srand(time(NULL));

    int n;

    printf("Enter the number of bottles (2-7): ");

    scanf("%d", &n);

    if (n <= 1 || n >= 8)
    {

        printf("Invalid bottle count.\n");
        return 1;
    }

    bottle *bottles = malloc(n * sizeof(bottle));

    if (bottles == NULL)
    {

        printf("Memory allocation failed.\n");
        return 1;
    }

    init_bottles(bottles, n);

    while (!is_finished(bottles, n))
    {

        display_bottles(bottles, n);

        char from_text[50];
        char to_text[50];

        sprintf(from_text, "From (1-%d, q=quit): ", n);
        sprintf(to_text, "To (1-%d, q=quit): ", n);

        int from = read_input(n, from_text);

        if (from == -1)
        {

            printf("Game ended.\n");

            free(bottles);
            return 0;
        }

        if (from == 0)
        {
            continue;
        }

        int to = read_input(n, to_text);

        if (to == -1)
        {

            printf("Game ended.\n");

            free(bottles);
            return 0;
        }

        if (to == 0)
        {
            continue;
        }

        make_step(bottles, from - 1, to - 1);
    }

    display_bottles(bottles, n);

    printf("Congratulations!\n");

    free(bottles);

    return 0;
}
