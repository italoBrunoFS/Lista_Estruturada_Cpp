#include <iostream>

class No {
public:
    int Valor;
    No* Prox_no;
    No() { Prox_no = nullptr; }
};

class ListaEncadeada {
private:
    No* cabeca;
    int tamanho;

public:
    ListaEncadeada() {
        cabeca = nullptr;
        tamanho = 0;
    }

    bool ListaVazia() {
        return tamanho == 0;
    }

    int GetTamanho() {
        return tamanho;
    }

    int ObterElemento(int pos) {
        No* aux = cabeca;
        int cont = 1;
        if (ListaVazia() || pos < 1 || pos > tamanho) return -1;
        while (cont < pos) {
            aux = aux->Prox_no;
            cont++;
        }
        return aux->Valor;
    }

    bool ModificarElemento(int pos, int dado) {
        No* aux = cabeca;
        int cont = 1;
        if (ListaVazia() || pos < 1 || pos > tamanho) return false;
        while (cont < pos) {
            aux = aux->Prox_no;
            cont++;
        }
        aux->Valor = dado;
        return true;
    }

    int ObterPosicao(int dado) {
        if (ListaVazia()) return -1;
        No* aux = cabeca;
        int cont = 1;
        while (cont <= tamanho) {
            if (dado == aux->Valor) return cont;
            aux = aux->Prox_no;
            cont++;
        }
        return -1;
    }

    bool InsereInicio(int dado) {
        No* novo = new No();
        novo->Valor = dado;
        novo->Prox_no = cabeca;
        cabeca = novo;
        tamanho++;
        return true;
    }

    bool InsereMeio(int pos, int dado) {
        No* novo = new No();
        novo->Valor = dado;
        No* aux = cabeca;
        int cont = 1;
        while (cont < pos - 1) {
            aux = aux->Prox_no;
            cont++;
        }
        if (aux == nullptr) return false;
        novo->Prox_no = aux->Prox_no;
        aux->Prox_no = novo;
        tamanho++;
        return true;
    }

    bool InsereFinal(int dado) {
        No* novo = new No();
        novo->Valor = dado;
        novo->Prox_no = nullptr;
        No* aux = cabeca;
        while (aux->Prox_no != nullptr) {
            aux = aux->Prox_no;
        }
        aux->Prox_no = novo;
        tamanho++;
        return true;
    }

    bool Inserir(int pos, int dado) {
        if (ListaVazia() && pos != 1) return false;
        if (pos == 1) return InsereInicio(dado);
        if (pos == tamanho + 1) return InsereFinal(dado);
        return InsereMeio(pos, dado);
    }

    int RemoverInicio() {
        No* aux = cabeca;
        int dado = aux->Valor;
        cabeca = aux->Prox_no;
        delete aux;
        tamanho--;
        return dado;
    }

    int RemoverMeio(int pos) {
        No* aux1 = cabeca;
        int count = 1;
        while (count < pos - 1) {
            aux1 = aux1->Prox_no;
            count++;
        }
        No* aux2 = aux1->Prox_no;
        int dado = aux2->Valor;
        aux1->Prox_no = aux2->Prox_no;
        delete aux2;
        tamanho--;
        return dado;
    }

    int Remover(int pos) {
        if (ListaVazia() || pos > tamanho + 1) return -1;
        if (pos == 1) return RemoverInicio();
        return RemoverMeio(pos);
    }

    void Imprimir() {
        if (ListaVazia()) {
            std::cout << "Lista Vazia!" << std::endl;
        } else {
            No* aux = cabeca;
            int count = 1;
            while (count <= tamanho) {
                std::cout << aux->Valor << " ";
                aux = aux->Prox_no;
                count++;
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    ListaEncadeada lista;
    std::cout << "Nova lista criada!\nMenu:\n1- Inserir Elemento\n2- Remover Elemento\n3- Modificar Elemento\n4- Obter Elemento\n5- Verificar se a Lista está Vazia\n6- Obter Posição\n7- Tamanho da Lista\n8- Exibir Lista\n9- Sair\n";
    int n;
    std::cin >> n;
    while (n != 9) {
        switch (n) {
        case 1: {
            int NumElementos;
            std::cout << "Digite quantos elementos quer inserir na lista: ";
            std::cin >> NumElementos;
            for (int i = 0; i < NumElementos; i++) {
                int Elemento, pos1;
                std::cout << "Digite o elemento que deseja adicionar a lista: ";
                std::cin >> Elemento;
                std::cout << "Digite a posição onde quer inserir o elemento: ";
                std::cin >> pos1;
                if (!lista.Inserir(pos1, Elemento)) {
                    throw std::invalid_argument("Erro ao inserir elemento!");
                }
            }
            std::cout << "Todos os Elementos inseridos com Sucesso!\n";
            break;
        }
        case 2: {
            int pos2;
            std::cout << "Digite a posição do elemento que quer remover: ";
            std::cin >> pos2;
            if (lista.Remover(pos2) != -1) {
                std::cout << "Removido Com Sucesso!\n";
            }
            break;
        }
        case 3: {
            int pos3, valor;
            std::cout << "Digite a posição do elemento que quer modificar: ";
            std::cin >> pos3;
            std::cout << "Digite o novo valor: ";
            std::cin >> valor;
            if (lista.ModificarElemento(pos3, valor)) {
                std::cout << "Modificado Com Sucesso!\n";
            }
            break;
        }
        case 4: {
            int pos4;
            std::cout << "Digite a posição do elemento que quer obter: ";
            std::cin >> pos4;
            std::cout << "Valor na posição: " << lista.ObterElemento(pos4) << "\n";
            break;
        }
        case 5:
            std::cout << (lista.ListaVazia() ? "A lista está vazia.\n" : "A lista não está vazia.\n");
            break;
        case 6:
            int num;
            std::cout << "Qual o elemento que quer obter? ";
            std::cin >> num;
            std::cout << "Elemento encontrado na posição " << lista.ObterPosicao(num) << "\n";
            break;
        case 7:
            std::cout << "Tamanho: " << lista.GetTamanho() << "\n";
            break;
        case 8:
            lista.Imprimir();
            break;
        default:
            std::cout << "Opção Inválida!\n";
            break;
        }
        std::cin >> n;
    }
}
