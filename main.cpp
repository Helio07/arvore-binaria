#include <iostream>
#include <windows.h>

using namespace std;

typedef struct Data{
    unsigned int dia ;
    unsigned int mes ;
    unsigned int ano ;
};

typedef struct Info{
    int matricula ;
    string cpf ;
    string nome ;
    string cargo ;
    string telefone ;
    Data data_nascimento ;
};

typedef struct No{
    string chave;
    Info * info ;
    No * esq ;
    No * dir ;
};

No * arvorePorCPF = NULL ;
No * arvorePorNome = NULL ;

void Menu();

No *pesquisa(No *raiz, string chave);
bool insere(No *&raiz, string num, Info *info);
No *consulta(No *raiz, string valor);
int retira(No *&raiz, string valor);
void cadastrarFuncionario();
No *pesquisarFuncionario();
void retirarFuncionario();
void imprimirTodosFuncionarios(No *atual = arvorePorNome);

int main()
{
  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_UTF8);
  int op;

  

  do{
      Menu();
      cout << "  opção: ";
      cin >> op;
      system("cls");

      switch (op){

      case 1:
        cadastrarFuncionario();
        cout << arvorePorNome->chave;
        system("cls");
        
        break;
      case 2:
        pesquisarFuncionario();
        system("pause");
        system("cls");
        break;
      case 3:
        retirarFuncionario();
        system("pause");
        system("cls");
        break;
    
      case 4:
        imprimirTodosFuncionarios();
        system("pause");
        system("cls");
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

No *pesquisa(No *raiz, string chave)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    else
    {
        if (chave < raiz->chave)
        {
            return pesquisa(raiz->esq, chave);
        }
        else if (chave > raiz->chave)
        {
            return pesquisa(raiz->dir, chave);
        }
        else
        {
            return raiz;
        }
    }
}

bool insere(No *&raiz, string num, Info *info)
{
    No *node = new No;

    node->chave = num;
    node->info = info;
    node->dir = NULL;
    node->esq = NULL;

    if (raiz == nullptr)
    {
        raiz = node;
        return true;
    }

    No *atual = raiz;
    No *pai = NULL;

    while (atual != nullptr)
    {
        pai = atual;
        int cmp = num.compare(atual->chave);
        if (cmp == 0){
            cout << "---Ja Cadastrado---";
            Sleep(1000);
            system("cls");
            return false;
        }

        cmp = atual->chave.compare(node->chave);
        if (cmp == -1)
        {
            atual = atual->dir;
        }
        else
        {
            atual = atual->esq;
        }
    }

    int cmp = pai->chave.compare(node->chave);
    if (cmp != 1) // auxFather->key <= node->key
    {
        pai->dir = node;
    }
    else
    {
        pai->esq = node;
    }
    return true;
}

No *consulta(No *raiz, string valor)
{
    No *atual = raiz;
    while (atual != NULL)
    {
        if (valor == atual->chave)
        {
            return atual;
        }
        else if (valor < atual->chave)
        {
            atual = atual->esq;
        }
        else
        {
            atual = atual->dir;
        }
    }
    return nullptr;
}

int retira(No *&raiz, string valor)
{
    if (raiz == nullptr)
        return false;

    No *aux = raiz;
    No *auxFather = nullptr;
    while (aux != nullptr)
    {
        int cmp = valor.compare(aux->chave);
        if (cmp == 0)
        {
            if (aux->esq == nullptr && aux->dir == nullptr)
            {
                if (auxFather == nullptr)
                    raiz = nullptr;
                else if (auxFather->esq == aux)
                    auxFather->esq = nullptr;
                else
                    auxFather->dir = nullptr;
                return true;
            }
            if (aux->esq == nullptr)
            {
                if (auxFather == nullptr)
                {
                    raiz = aux->dir;
                    return true;
                }
                int cmp = aux->chave.compare(auxFather->chave);
                if (cmp == -1)
                    auxFather->esq = aux->dir;
                else
                    auxFather->dir = aux->dir;
                return true;
            }
            if (aux->dir == nullptr)
            {
                if (auxFather == nullptr)
                {
                    raiz = aux->esq;
                    return true;
                }
                int cmp = aux->chave.compare(auxFather->chave);
                if (cmp == -1)
                    auxFather->esq = aux->esq;
                else
                    auxFather->dir = aux->esq;
                return true;
            }

            No *aux2 = aux->esq;
            No *aux2Father = aux;
            while (aux2->dir != nullptr)
            {
                aux2Father = aux2;
                aux2 = aux2->dir;
            }
            aux->chave = aux2->chave;
            aux->info = aux2->info;

            if (aux2Father->dir == aux2)
                aux2Father->dir = aux2->dir;
            else
                aux2Father->esq = aux2->dir;

            return true;
        }

        auxFather = aux;

        cmp = valor.compare(aux->chave);
        if (cmp == 1)
            aux = aux->dir;
        else
            aux = aux->esq;
    }

    return false;
}

void cadastrarFuncionario()
{
    Info fun;


    cout << "Matricula: ";
    cin >> fun.matricula;
    cin.ignore();
    cout << "CPF: ";
    getline(cin, fun.cpf);
    cout << "Nome: ";
    getline(cin, fun.nome);
    cout << "Telefone: ";
    getline(cin, fun.telefone);
    cout << "Cargo: ";
    getline(cin, fun.cargo);

    cout << "\nData de nascimento" << endl;
    cout << "Dia: ";
    cin >> fun.data_nascimento.dia;
    cout << "Mes: ";
    cin >> fun.data_nascimento.mes;
    cout << "Ano: ";
    cin >> fun.data_nascimento.ano;

    Info *info = new Info;

    info->cargo = fun.cargo;
    info->cpf = fun.cpf;
    info->nome = fun.nome;
    info->telefone = fun.telefone;

    info->data_nascimento.dia = fun.data_nascimento.dia;
    info->data_nascimento.mes = fun.data_nascimento.mes;
    info->data_nascimento.ano = fun.data_nascimento.ano;

    insere(arvorePorCPF, fun.cpf, info);
    insere(arvorePorNome, fun.nome, info);

    if (insere){
      cout << "---CADASTRADO COM SUCESSO---";
      Sleep(1000);
      system("cls");
    }
}

No *pesquisarFuncionario()
{
    cout << "Pesquisar por: \n(1) - Nome\n(2) - CPF\nSua opcao: ";
    int opcao;
    cin >> opcao;
    No *res;
    if (opcao == 1)
    {
        cout << "Digite o nome do funcionario: ";
        string nome;
        cin.ignore();
        getline(cin, nome);
        res = pesquisa(arvorePorNome, nome);
    }
    else if (opcao == 2)
    {
        cout << "Digite o cpf do funcionario: ";
        string cpf;
        cin.ignore();
        getline(cin, cpf);
        res = pesquisa(arvorePorCPF, cpf);
    }
    if (res != nullptr)
    {
        cout << "Funcionario encontrado!" << endl;
        cout << "\n-------------------------------\n";
        cout << "NOME: " << res->info->nome << endl;
        cout << "CPF: " << res->info->cpf << endl;
        cout << "CARGO: " << res->info->cargo << endl;
        cout << "TELEFONE: " << res->info->telefone << endl;
        cout << "Data de nascimento: " << atual->info->data_nascimento.dia <<"/"<< atual->info->data_nascimento.mes<<"/"<<atual->info->data_nascimento.ano << endl;
        cout << "\n-------------------------------\n";
    }
    else
    {
        cout << "Funcionario nao encontrado!" << endl;
    }
    return res;
}

void retirarFuncionario()
{
    No *no = pesquisarFuncionario();
    if (no == nullptr)
        return;
    retira(arvorePorNome, no->chave);
    retira(arvorePorCPF, no->chave);
    cout << "Funcionario removido!" << endl;
}

void imprimirTodosFuncionarios(No *atual)
{

    if (atual != nullptr)
    {
        imprimirTodosFuncionarios(atual->esq);
        cout << "\n-------------------------------\n";
        cout << "Matricula: " << atual->info->matricula << endl;
        cout << "NOME: " << atual->info->nome << endl;
        cout << "CPF: " << atual->info->cpf << endl;
        cout << "CARGO: " << atual->info->cargo << endl;
        cout << "TELEFONE: " << atual->info->telefone << endl;
        cout << "Data de nascimento: " << atual->info->data_nascimento.dia <<"/"<< atual->info->data_nascimento.mes<<"/"<<atual->info->data_nascimento.ano << endl;
        imprimirTodosFuncionarios(atual->dir);
    }
}