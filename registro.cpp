#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
const char *arquivo = "diario.txt";

void inclusao();
void consulta();
void exclusao();

int op;
struct contato
{
    char nome[40];
    char email[60];
    char celular[9];

}; //definiçao
struct contato agenda[300];
int i;

void inclusao()
{
    if (i <= 300)
    {

        do
        {
            printf("Entre com o NOME: \n");
            scanf("%s", agenda[i].nome);
        } while (agenda[i].nome == "");

        do
        {
            printf("Entre com o E-MAIL: \n");
            scanf("%s", agenda[i].email);
        } while (agenda[i].email == "");

        do
        {
            printf("Entre com o TELEFONE: \n");
            scanf("%s", agenda[i].celular);
        } while (agenda[i].celular == "");

        i++;
        FILE *agenda_pont = fopen(arquivo, "w");
        fwrite(&agenda, sizeof(agenda), 1, agenda_pont);
        fclose(agenda_pont);
    }
    else
    {
        printf("Lotacao maxima atingida\n");
    }
};

void CarregarContatos()
{
  FILE *contactFile = fopen(arquivo, "rb"); /* r - leitura || rb - leitura binaria */

  if (contactFile == NULL)
    return;

  fseek(contactFile, 0, SEEK_END);
  long fileLength = ftell(contactFile);
  rewind(contactFile);

  if (fileLength > sizeof(contato)*300)
  {
    fread(&agenda, sizeof(contato)*300, 1, contactFile);
  }
  else
  {
    fread(&agenda, fileLength, 1, contactFile);
  }

  fclose(contactFile);
}


void consulta()
{
    if(strcmp (agenda[0].nome,"") == 0)
            printf("Lista vazia ! \n\n\n");
    for (int ex = 0; ex < 300; ex++)
    {
        if(strcmp (agenda[ex].nome,"") == 0)
            break;
        printf("Posicao %d\n Nome: %s\n e-mail: %s\n telefone: %s\n", ex, agenda[ex].nome, agenda[ex].email, agenda[ex].celular);
    }
};
void exclusao()
{
    char excluir[3] = "";
    printf("Deseja excluir o arquivo :[s/n] \n");
    scanf("%s", &excluir);
    if (strcmp(excluir, "s") == 0)
    {
        if (remove(arquivo) == 0){
            printf("Arquivo removido!\n\n");
            memset(&agenda, '\0', sizeof(contato)*300);
        }else
            printf("Erro ao remover o arquivo!\n\n");
    }
};

int main(void)
{
    CarregarContatos();
    do
    {
        printf("Entre com a operacao desejada\n 1-Inclusao\n 2-consulta\n 3-exclusao\n 4-sair\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            inclusao();
            break;
        case 2:
            consulta();
            break;
        case 3:
            exclusao();
            break;
        case 4:
            break;
        default:
            printf("Operação invalida\n Entre com uma operacao valida\n");
            break;
        }
    } while (op != 4);
};
