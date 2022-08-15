#include <iostream>
#include <windows.h>
 
using namespace std;

typedef struct Data{
    unsigned int dia ;
    unsigned int mes ;
    unsigned int ano ;
};

typedef struct Endereco{
    char logradouro [30];
    int numero ;
    char bairro [20];
    char cidade [20];
    char estado [2];
    char cep [10];
};

typedef struct Info{
    int matricula ;
    char cpf [14];
    char nome [50];
    char cargo [30];
    char telefone [15];
    Data data_nascimento ;
    Endereco endereco ;
};

typedef struct No{
    Info * info ;
    No * esq ;
    No * dir ;
};

No * arvorePorCPF = NULL ;
No * arvorePorNome = NULL ;


void Menu();
Info Cadastra_Funcionario();
void insere(Info *Info, No *funcionario);

 
int main() {
  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_UTF8);
  int op;
  Info fun;

  

  do{
      Menu();
      cout << "  opção: ";
      cin >> op;
      system("cls");

      switch (op){

      case 1:
        fun = Cadastra_Funcionario();
        insere(&fun, &arvorePorCPF);
        
        break;
      case 2:
        
        break;
      case 3:
        
        break;
    
      case 4:
        
        break;
        
      default:
        break;
      }
    } while (op != 5);
  
 
  cout << endl << endl;
  system("pause");
  return 0;
}

void Menu() {    
     cout<<"  \n        ����������������������������������������������������������������";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        �                     MENU PRINCIPAL                           �";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        ����������������������������������������������������������������";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        � 1 - Cadastrar funcionario                                    �";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        � 2 - Buscar funcionario                                       �";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        � 3 - Remover funcionario                                      �";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        � 4 - Imprimir                                                 �";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        � 5 - SAIR                                                     �";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        ����������������������������������������������������������������\n\n";
}

Info Cadastra_Funcionario(){
    
    Info fun;

    cout << "Matricula: ";
    cin >> fun.matricula; 
    cout << "Cpf[14]: ";
    cin >> fun.cpf;
    cout << "Nome: ";
    cin >> fun.nome;
    cout << "Cargo: ";
    cin >> fun.cargo;
    cout << "Telefone[15]: ";
    cin >> fun.telefone;

    cout << "\nData de nascimento" <<endl;
    cout << "dia: ";
    cin >> fun.data_nascimento.dia;
    cout << "Mes: ";
    cin >> fun.data_nascimento.mes;
    cout << "Ano: ";
    cin >> fun.data_nascimento.ano;

    cout << "\nENDEREÇO\n";
    cout << "logradouro: ";
    cin >> fun.endereco.logradouro;
    cout << "numero: ";
    cin >> fun.endereco.numero;
    cout << "bairro: ";
    cin >> fun.endereco.bairro;
    cout << "cidade: ";
    cin >> fun.endereco.cidade;
    cout << "estado: ";
    cin >> fun.endereco.estado;
    cout << "cep: ";
    cin >> fun.endereco.cep;

  return fun;
}

int insere(Info *fun, No *funcionario)
{
    No *novo = new No;
    
    novo->info = fun ;
    novo->dir = NULL;
    novo->esq = NULL;

    if (arvorePorCPF == NULL)
    {
        arvorePorCPF = novo;
        return 1;
    }

    No *atual = arvorePorCPF;
    No *pai = NULL;

    while (atual != NULL)
    {
        pai = atual;

        if (fun->cpf < atual->info->cpf)
        {
            atual = atual->esq;
        }
        else
        {
            atual = atual->dir;
        }
    }

    if (fun->cpf < pai->info->cpf)
    {
        pai->esq = novo;
    }
    else
    {
        pai->dir = novo;
    }

    return 1;
}

