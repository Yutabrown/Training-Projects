// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
    char *mom;
    char *dad;
}
person;

int GENERATIONS;
const int INDENT_LENGTH = 4;

person *create_family(int generations, char mom_alleles[2], char dad_alleles[2]);
void print_family(person *p, int generation);
void free_family(person *p);
char random_mom_alleles(char mom_alleles[2]);
char random_dad_alleles(char dad_alleles[2]);
char o_allele(char mom_alleles[2], char dad_alleles[2]);
void sort_alleles(char alleles[2]);

int main(void)
{
    // Seed random number generator
    srand(time(0));

    char mom_alleles[2];
    char dad_alleles[2];

    // Cria um novo filho
    person *child = malloc(sizeof(person));

    // Há 6 pares de alelos, cada par com 2 alelos
    char allele_pairs[6][2] =
    {
        {'A', 'A'},
        {'A', 'B'},
        {'A', 'O'},
        {'B', 'B'},
        {'B', 'O'},
        {'O', 'O'}
    };

    //Verifica se os alelos são válidos
    bool valid_mom_alleles = false;
    bool valid_dad_alleles = false;

    while(!valid_mom_alleles || !valid_dad_alleles)
    {
        child->mom = malloc(256); // Alocar memória para o nome da mãe
        printf("\nNome da mãe: ");
        scanf(" %255s", child->mom);

        printf("\nInsira os alelos da mãe: ");
        scanf(" %c%c", &mom_alleles[0], &mom_alleles[1]);

        for(int i = 0; i < 6; i++)
        {
            if ((mom_alleles[0] == allele_pairs[i][0] && mom_alleles[1] == allele_pairs[i][1]) ||
                (mom_alleles[0] == allele_pairs[i][1] && mom_alleles[1] == allele_pairs[i][0]))
            {
                valid_mom_alleles = true;
                printf("\nPar de alelos da mãe válido.\n");
                break;
            }
        }

        if(!valid_mom_alleles)
        {
            printf("\nInsira um par de alelos da mãe que seja válido. \n");
        }

        child->dad = malloc(256); // Alocar memória para o nome do pai
        printf("\nNome do pai: ");
        scanf(" %255s", child->dad);

        printf("\nInsira os alelos do pai: ");
        scanf(" %c%c", &dad_alleles[0], &dad_alleles[1]);

        for(int i = 0; i < 6; i++)
        {
            if ((dad_alleles[0] == allele_pairs[i][0] && dad_alleles[1] == allele_pairs[i][1]) ||
                (dad_alleles[0] == allele_pairs[i][1] && dad_alleles[1] == allele_pairs[i][0]))
            {
                valid_dad_alleles = true;
                printf("\nPar de alelos do pai válido.\n");
                break;
            }
        }

        if(!valid_dad_alleles)
        {
            printf("\nInsira um par de alelos do pai que seja válido. \n");
        }
    }

    printf("Quantidade de gerações a simular: ");
    scanf(" %d", &GENERATIONS);

    // Create a new family with three generations
    person *p = create_family(GENERATIONS, mom_alleles, dad_alleles);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
    free(child);
}

// Create a new individual with `generations`
person *create_family(int generations, char mom_alleles[2], char dad_alleles[2])
{
    // Allocate memory for new person
    person *p = malloc(sizeof(person));

    // Generation with parent data
    if (generations > 1)
    {
        // Create blood type histories for parents
        p->parents[0] = create_family(generations - 1, mom_alleles, dad_alleles);
        p->parents[1] = create_family(generations - 1, mom_alleles, dad_alleles);

        // Randomly assign child alleles based on parents
        p->alleles[0] = random_mom_alleles(mom_alleles);
        p->alleles[1] = random_dad_alleles(dad_alleles);

        o_allele(mom_alleles, dad_alleles);

        sort_alleles(mom_alleles);
        sort_alleles(dad_alleles);

    }

    // Generation without parent data
    else
    {
        // Set parent pointers to NULL
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // Randomly assign child alleles based on parents
        p->alleles[0] = random_mom_alleles(mom_alleles);
        p->alleles[1] = random_dad_alleles(dad_alleles);

        sort_alleles(mom_alleles);
        sort_alleles(dad_alleles);

    }

    // Return newly created person
    return p;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case
    if (p->parents[0] == NULL && p->parents[1] == NULL)
    {
        free(p); // Free the memory of the current person
        return;   // Return to the previous level of recursion
    }

    // TODO: Free parents
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // TODO: Free child
    free(p);
}

int LAST_GENERATION = -1;

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_mom_alleles(char mom_alleles[2])
{
    int random_choice = rand() % 2;

    if (random_choice == 0)
    {
        return mom_alleles[0];
    }

    else
    {
        return mom_alleles[1];
    }
}

char random_dad_alleles(char dad_alleles[2])
{
    int random_choice = rand() % 2;
    
    if (random_choice == 0)
    {
        return dad_alleles[0];
    }
    
    else
    {
        return dad_alleles[1];
    }
}

char o_allele(char mom_alleles[2], char dad_alleles[2])
{

    if (mom_alleles[0] == dad_alleles[0] || mom_alleles[1] == dad_alleles[1] ||
        mom_alleles[0] == dad_alleles[1] || mom_alleles[1] == dad_alleles[0])
    {
        int random_choice = rand() % 2;

        if (random_choice == 0)
        {
            int chosen_mom_allele = rand() % 2;
            if (chosen_mom_allele == 0)
            {
                mom_alleles[0] = 'O';
                return mom_alleles[0];
            }

            else if (chosen_mom_allele == 1)
            {
                mom_alleles[1] = 'O';
                return mom_alleles[1];
            }
        }

        else if (random_choice == 1)
        {
            int chosen_dad_allele = rand() % 2;
            if (chosen_dad_allele == 0)
            {
                dad_alleles[0] = 'O';
                return dad_alleles[0];
            }

            else if (chosen_dad_allele == 1)
            {
                dad_alleles[1] = 'O';
                return dad_alleles[1];
            }
        }
    }
}

void sort_alleles(char alleles[2])
{
    int i, j;
    char temp;

    for(i = 0; i < 1; i++)
    {
        for(j = 0; j < 1 - i; j++)
        {
            if(alleles[j] > alleles[j + 1])
            {
                temp = alleles[j];
                alleles[j] = alleles[j + 1];
                alleles[j + 1] = temp;
            }
        }
    }
}
