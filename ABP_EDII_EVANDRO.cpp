
#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <algorithm> // para valor máximo
#include <vector> // para classe vetor

using namespace std;

class No{
	public:
		int valor;
		No *esq;
		No *dir;
		No();
};

class Arvore{
	public:
		int qtde;
		No *raiz;
		Arvore();
		void inserir(int num, No *&no);
		void pesquisar(int num, No *&no);
		bool remover(int num, No *&no);
		void antecessor(No *&q, No *&r);
		void preOrdem(No *&no);
		void central(No *&no);
		void posOrdem(No *&no);
        int maiorNo(No *&no);
		int menorNo(No *&no);
		int somaNos(No *&no);
		int quantNos2filhos(No *&no);
		int quantNos1filho(No *&no);
		int quantNosFolha(No *&no);
		int nivelNo(int num, int nivel, No *&no);
		bool guardaCaminho(No *&no, vector<int> &vet, int num);
		void caminhoNo(int num, No *&no);
		int alturaArvore(No *&no);

};

Arvore::Arvore(){
	qtde = 0;
	raiz = NULL;
}

No::No(){
	valor = 0;
	esq = NULL;
	dir = NULL;
}

void Arvore::inserir(int num, No *&no){
	if (no == NULL){
		No *novo = new No();
		novo->valor = num;
		no = novo;
		qtde++;
		cout << "Valor " << num << " inserido com sucesso!" << endl;
	}else{
		if (num < no->valor){
			inserir(num, no->esq);
		}else{
			if (num > no->valor){
				inserir(num, no->dir);
			}else{
				cout << "Erro: Valor " << num << " já existe na árvore!" << endl;
			}
		}
	}
}

void Arvore::pesquisar(int num, No *&no){
	if (no == NULL){
		cout << "Valor " << num << " não está presente na árvore!" << endl;
	}else{
		if (num < no->valor){
			pesquisar(num, no->esq);
		}else{
			if (num > no->valor){
				pesquisar(num, no->dir);
			}else{
				cout << "Valor " << num << " encontrado na árvore!" << endl;
			}
		}
	}
}

bool Arvore::remover(int num, No *&no){
	No *aux;
	if (no == NULL){
		return false;
	}else{
		if (num < no->valor){
			remover(num, no->esq);
		}else{
			if (num > no->valor){
				remover(num, no->dir);
			}else{
				if (no->dir == NULL){
					aux = no;
					no = no->esq;
					delete(aux);
					qtde--;
					if (qtde == 0)
						raiz = NULL;
				}else{
					if (no->esq == NULL){
						aux = no;
						no = no->dir;
						delete(aux);
						qtde--;
						if (qtde == 0)
							raiz = NULL;
					}else{
						antecessor(no, no->esq);
					}
				}
			}
		}
		return true;
	}
}

void Arvore::antecessor(No *&q, No *&r){
	if (r->dir != NULL){
		antecessor(q, r->dir);
	}else{
		q->valor = r->valor;
		q = r;
		r = r->esq;
		delete(q);
		qtde--;
		if (qtde == 0)
			raiz = NULL;
	}
}

void Arvore::preOrdem(No *&no){
	if (no != NULL){
		cout << no->valor << " ";
		preOrdem(no->esq);
		preOrdem(no->dir);
	}
}

void Arvore::central(No *&no){
	if (no != NULL){
		central(no->esq);
		cout << no->valor << " ";
		central(no->dir);
	}
}

void Arvore::posOrdem(No *&no){
	if (no != NULL){
		posOrdem(no->esq);
		posOrdem(no->dir);
		cout << no->valor << " ";
	}
}
int Arvore::maiorNo(No *&no)
{
    if(no == NULL){
        cout<<"Erro: Arvore Vazia!"<<endl;
    }
    while(no->dir != NULL){
        no = no->dir;
    }
    return no->valor;
}

int Arvore::menorNo(No *&no)
{
    if(no == NULL){
        cout<<"Erro: Arvore Vazia!"<<endl;
    }
    else{
        if((no->esq != NULL) &&(no->esq->valor < no->valor)){
        menorNo(no->esq);
        }else
            return no->valor;
    }
}

int Arvore::somaNos(No *&no)
{

    if(no == NULL){
        return 0;
    }else{
        return no->valor + somaNos(no->esq) + somaNos(no->dir);
    }
}
int Arvore::quantNos2filhos(No *&no){
    int quant = 0;
    if(no == NULL) {
        return 0;
    }
    quant = quantNos2filhos(no->esq) + quantNos2filhos(no->dir);
    if((no->esq != NULL) && (no->dir != NULL))
        quant++;
        return quant;
}
int Arvore::quantNos1filho(No *&no){
    if(no == NULL)
        return 0;
    else{
        if((no->esq == NULL)&&(no->dir == NULL))
            return 0;
    else
        if((no->esq != NULL)&&(no->dir != NULL))
            return quantNos1filho(no->esq) + quantNos1filho(no->dir);
    else
        return quantNos1filho(no->esq) + quantNos1filho(no->dir) + 1;
}
}

int Arvore::quantNosFolha(No *&no){

    if(no == NULL)
        return 0;
    if((no->esq == NULL) && (no->dir == NULL))
        return 1;
    else
        return quantNosFolha(no->esq) + quantNosFolha(no->dir);
}
int Arvore::nivelNo(int num, int nivel, No *&no){
        if (no == NULL)
        return 0;

    if (no->valor == num) //Se o valor do nó for igual ao valor da raiz retorna nivel
        return nivel;

    int proximoNivel = nivelNo(num, nivel + 1, no->esq); //caminha pra esquerda e soma 1 no valor do nivel

    if (proximoNivel != 0)
        return proximoNivel;

    proximoNivel = nivelNo(num, nivel + 1, no->dir);

    return proximoNivel;
}
bool Arvore::guardaCaminho(No *&no, vector<int> &vet, int num){
    if(no == NULL)
        return false;
    vet.push_back(no->valor); //vetor recebe o valor do no
    if(no->valor == num)
        return true;
    if((guardaCaminho(no->esq, vet, num) || (guardaCaminho(no->dir, vet, num))))
        return true;
    vet.pop_back(); //Caso o nó não esteja presente nem na esquerda e nem na direita ele será retirado do vetor
    return false;
}

void Arvore::caminhoNo(int num, No *&no){
    vector<int> vet;// variavel da classe vetor criada para armazenar os valores do caminho

    if(guardaCaminho(no, vet, num)){
            cout<<"Caminho ate o no: ";
        for(int i=0; i < vet.size()-1; i++) //vet.size()-1 elimina o no que está sendo verificado
            cout<<vet[i]<< " ";
    }
    else
        cout<<"Caminho inexistente"<<endl;
}
int Arvore::alturaArvore(No *&no)
{
    if (no == NULL)
        return 0;
    int alturaEsq = alturaArvore(no->esq) + 1;
    int alturaDir = alturaArvore(no->dir) + 1;
    int alturaTotal = max(alturaEsq, alturaDir);
        return alturaTotal;
}

int main(){
	setlocale(LC_ALL,"");
	int opcao, num, maior;
	Arvore t;
	while(1){
		system("cls");
        cout <<"1 -  Inserir"<<endl;
		cout <<"2 -  Pesquisar"<<endl;
		cout <<"3 -  Remover"<<endl;
		cout <<"4 -  Pre-Ordem"<<endl;
		cout <<"5 -  Central"<<endl;
		cout <<"6 -  Pos-Ordem"<<endl;
		cout <<"7 -  Maior nó"<<endl;
		cout <<"8 -  Menor nó"<<endl;
		cout <<"9 -  Soma de todos os nós"<<endl;
		cout <<"10 - Quantidade de nós com 2 filhos"<<endl;
		cout <<"11 - Quantidade de nós com 1 filho"<<endl;
		cout <<"12 - Quantidade de nós folha"<<endl;
		cout <<"13 - Nivel de um determinado nó"<<endl;
		cout <<"14 - Caminho até um determinado nó"<<endl;
		cout <<"15 - Altura da arvore"<<endl;
		cout <<"0  - Sair"<<endl;
		cout <<"Digite a opcao desejada: ";
		cin >> opcao;

		if(opcao == 1){
			cout << "Digite o valor a ser inserido: ";
			cin >> num;
			if (t.raiz == NULL){
				No *novo = new No();
				novo->valor = num;
				t.raiz = novo;
				t.qtde++;
				cout << "Valor " << num << " inserido com sucesso!" << endl;
			}else{
				No *aux = t.raiz;
				t.inserir(num, aux);
			}
			system("pause");
		}
		if(opcao == 2){
			cout << "Digite o valor a ser pesquisado: ";
			cin >> num;
			No *aux = t.raiz;
			t.pesquisar(num, aux);
			system("pause");
		}
		if(opcao == 3){
			cout << "Digite o valor a ser removido: ";
			cin >> num;
			No *aux = t.raiz;
			if (t.remover(num, aux)){
				cout << "Valor " << num << " removido da árvore!" << endl;
			}else{
				cout << "Valor " << num << " não está presente na árvore!" << endl;
			}
			system("pause");
		}
		if(opcao == 4){
			No *aux = t.raiz;
			t.preOrdem(aux);
			system("pause");
		}
		if(opcao == 5){
			No *aux = t.raiz;
			t.central(aux);
			system("pause");
		}
		if(opcao == 6){
			No *aux = t.raiz;
			t.posOrdem(aux);
			system("pause");
		}
		if(opcao == 7){
            No *aux = t.raiz;
            cout<<"O maior no eh: "<<t.maiorNo(aux)<<endl;
            system("pause");
		}
		if(opcao == 8){
            No *aux = t.raiz;
            cout<<"O menor no eh: "<<t.menorNo(aux)<<endl;
            system("pause");
		}
        if(opcao == 9){
            No *aux = t.raiz;
            t.somaNos(aux);
            cout<<"Soma dos nos = "<<t.somaNos(aux)<<endl;
            system("pause");
		}
        if(opcao == 10){
        No *aux = t.raiz;
        t.quantNos2filhos(aux);
        cout<<t.quantNos2filhos(aux)<<" eh a quantidade de nos com 2 filhos"<<endl;
        system("pause");
		}
		if(opcao == 11){
            No *aux = t.raiz;
            t.quantNos1filho(aux);
            cout<<t.quantNos1filho(aux)<<" eh a quantidade de nos com 1 filho"<<endl;
            system("pause");
		}
		if(opcao == 12){
            No *aux = t.raiz;
            t.quantNosFolha(aux);
            cout<<"A quantidade de nos folha eh: "<<t.quantNosFolha(aux)<<endl;
            system("pause");
		}
		if(opcao == 13){
            int nivel=0;
            cout<<"Informe o numero do no: ";
            cin>>num;
            No *aux = t.raiz;
            t.nivelNo(num, nivel, aux);
            cout<<"O nivel do no "<<num<<" eh: "<<t.nivelNo(num, nivel, aux)<<endl;
            system("pause");
		}
        if(opcao == 14){
            cout<<"Informe o numero do no para verificar o caminho: ";
            cin>>num;
            No *aux = t.raiz;
            t.caminhoNo(num, aux);
            system("pause");
		}
        if(opcao == 15){
            No *aux = t.raiz;
            cout<<"A altura da arvore eh: "<< t.alturaArvore(aux) <<endl;
            system("pause");
		}
		if(opcao == 0)
            break;
	}
	system("pause");
	return 0;
}
