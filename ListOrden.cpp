#include <iostream>
#include <stack>
using namespace std;

template <class T>
struct Node
{
    Node();
    Node(T x)
    {
        data = x;
        next = NULL;
    }
    Node<T> * next;
    T data;
};


template <class T>
struct List
{
    int tam;
    List(int tam);
    Node<T> * head;
    bool buscar(T x,Node<T> ** &p);
    void insertar(T x);
    void remover(T x);
    void invertir();
    void print();
    void ordenar();
};

template <class T>
List<T>::List(int tamno){
    head = NULL;
    tam=tamno;
}

template <class T>
bool List<T>::buscar(T x,Node<T> ** &p){
    for(p=&head; *p!=NULL; p=&(*p)->next){
        if ((*p)->data == x) return 1;
    }
    return 0;
}

template <class T>
void List<T>::insertar(T x){
    Node<T> ** p;
    if(buscar(x,p)) return;
    *p = new Node<T>(x);

    return;
}

template <class T>
void List<T>::remover(T x){
    Node<T>** p;
    if(!buscar(x,p)) return;
    Node<T>* q = *p;
    *p = q->next;
    delete q;
}

template <class T>
void List<T>::invertir()
{
    Node<T> * prev=NULL;
    Node<T> * aux=NULL;
    Node<T> * temp=head;
    while(temp)
    {
        aux=temp->next;
        temp->next=prev;
        prev=temp;
        temp=aux;
    }
    head=prev;
}



template <class T>
void List<T>::ordenar()
{
    if (head != 0)
    {
        Node<T>* temp = 0;
        Node<T>* aux = 0;
        Node<T>* menor = head;
        int pos = 0;

        for (int i = 0; i < tam; i++)
        {
            while (menor->next != 0)
            {
                aux = menor->next;
                if (menor->data > aux->data)
                {
                    pos = 1;
                    menor->next = aux->next;
                    aux->next = menor;
                    if (temp != 0)
                        temp->next = aux;
                    temp = aux;
                    if (head == menor)
                        head = aux;
                }
                else
                {
                    temp = menor;
                    menor = menor->next;
                }
            }
            if (pos == 0)
                break;
            else
            {
                temp = 0;
                menor = head;
                pos = 0;
            }
        }
    }
}

template <class T>
void List<T>::print(){
    Node<T> ** p;
    for(p=&head; *p!=NULL; p=&(*p)->next){
        cout << (*p)->data<<"  ";
    }
}

int main(){
    List<int> l(10);

    l.insertar(23);
    l.insertar(12);
    l.insertar(21);
    l.insertar(6);
    l.insertar(16);
    l.insertar(3);
    l.insertar(7);
    l.insertar(40);
    l.insertar(1);
    l.insertar(19);
    l.print();
    cout << endl;
    l.ordenar();
    l.print();

    return 0;
}

