// Simular a herança genética do tipo sanguíneo

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Cada pessoa tem 2 pais e 2 alelos
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

// prototypes
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Gerador de números aleatórios com sementes
    srand(time(0));

    // Criar uma nova família com três gerações
    person *p = create_family(GENERATIONS);

    // Imprimir árvore genealógica dos tipos de sangue
    print_family(p, 0);

    // Liberar mémoria
    free_family(p);
}

// Criar um novo indivíduo com `gerações'.
person *create_family( int generations)
{
    // TODO: Alocar mémpria para uma novs pessoa
    person *nova_pessoa = malloc(sizeof(person));
    if(nova_pessoa== NULL)
    {
        return false;
    }
 
    // Geração com dados dos pais
    if (generations > 1)
    {
        // TODO: Recursivamente criar histórias de tipos de sangue para os pais
         nova_pessoa->parents[0] = create_family(generations-1);
         nova_pessoa->parents[1] = create_family(generations-1);
        // TODO: Atribuir alelos infantis alelos aleatórios com base nos pais
        nova_pessoa->alleles[0] = nova_pessoa->parents[0]->alleles[rand() % 2];
        nova_pessoa->alleles[1] = nova_pessoa->parents[1]->alleles[rand() % 2];
    }

    // Geração sem dados dos pais
    else
    {
        // TODO: mandar parents pointers apontar para NULL
        nova_pessoa->parents[0] = NULL;
        nova_pessoa->parents[1] = NULL;

        // TODO: Atribuir alelos alelos de forma aleatória
        nova_pessoa->alleles[0] = random_allele();
        nova_pessoa->alleles[1] = random_allele();
    }

    // TODO: Retornar pessoa recém-criada
    return nova_pessoa;
}

// Livre `p` e todos os antepassados do `p`.
void free_family(person *p)
{
    // TODO: Manusear a caixa base
    if(p == NULL)
    {
        return;
    }
    //Liberação dos pais
     free_family(p->parents[0]);
     free_family(p->parents[1]);   
    // liberar a crainça
    free(p);
}

// Imprima cada membro da família e seus alelos.
void print_family(person *p, int generation)
{
    // Estojo base de manuseio
    if (p == NULL)
    {
        return;
    }

    // Indentação de impressão
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // imprimir dados da pessoa
    printf("Geração %i, tipo sanguíneo %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Escolha aleatória de um alelo de tipo sanguíneo.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
