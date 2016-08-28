#include <iostream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

template<class T>
class nodo{
public:
    T dato;
    nodo<T> * hijo[2];

    nodo(T x)
    {
        dato=x;
        hijo[0]=NULL;
        hijo[1]=NULL;
    }

};

template <class T>
class arbol{

public:
    T dato;
    nodo<T> * raiz;
    less<T>   m_cmp;

    arbol()
    {
        raiz=NULL;
    }

    bool buscar(T x,nodo<T> ** &p)
    {
        for(p=&raiz; (*p) && (*p)->dato!=x ; p=&((*p)->hijo[m_cmp((*p)->dato,x)]));
        return (*p);
    }

    bool insertar(T x)
    {
        nodo<T> ** p;
        if (buscar(x, p)) return 0;
        *p = new nodo<T>(x);

        return 1;
    }
    nodo<T> ** repetido(nodo<T> ** p)
    {
        p = &((*p)->hijo[0]);
        while ((*p)->hijo[1])
            p = &((*p)->hijo[1]);
        return p;
    }

    bool borrar(T x)
    {
        nodo<T> ** p;
        if (!buscar(x,p)) return 0;

        if ((*p)->hijo[0] && (*p)->hijo[1])
        {
            nodo<T> ** q = repetido(p);
            (*p)->dato = (*q)->dato;
            p = q;
        }
        nodo<T> * t = *p;
        *p = (*p)->hijo[(*p)->hijo[1]!=0];
        delete t;

        return 1;
    }


    nodo<T> * arbolLista(nodo<T> *r)
    {
        if (r==0)
            return 0;

        if(r->hijo[0]!=0)
        {
            nodo<T> * izq= arbolLista(r->hijo[0]);
            for (; izq->hijo[1] ; izq=izq->hijo[1]);
            izq->hijo[1] = r;
            r->hijo[0] = izq;
        }

        if(r->hijo[1]!=0)
        {
            nodo<T> *der = arbolLista(r->hijo[1]);
            for(;der->hijo[0];der=der->hijo[1]);
            der->hijo[0]=r;
            r->hijo[1]=der;
        }

        while (r->hijo[0]!= 0)
            r = r->hijo[0];
        return (r);
    }

    void imprimir()
    {
        if (!raiz)  return;

        queue<nodo<T>*> na, ns;
        na.push(raiz);
        bool end = true;

        while (!na.empty())
        {
            nodo<T>* aux = na.front();
            na.pop();
            if (aux and aux->dato>0)
            {
                if(aux){
                    std::cout <<""<<aux->dato << "  ";
                    ns.push(aux->hijo[0]);
                    ns.push(aux->hijo[1]);
                    end = false;
                }

                else{
                    std::cout <<" "<<aux->dato << "  ";
                    ns.push(aux->hijo[0]);
                    ns.push(aux->hijo[1]);
                    end = false;
                }

            }
            else{
                ns.push(NULL);ns.push(NULL);
            }
            if (na.empty())
            {
                std::cout << std::endl;
                if (end)
                    return;
                std::swap(na, ns);
                end = true;
            }
        }

    }


};




int main(int argc, const char * argv[])
{

    arbol<int> a;
    a.insertar(13);
    a.insertar(16);
    a.insertar(20);
    a.insertar(3);
    a.insertar(5);
    a.insertar(7);
    a.insertar(18);

    a.imprimir();

    nodo<int> * n = a.arbolLista(a.raiz);
    cout<<endl;
    while(n)
    {
        cout<<n->dato<<endl;
        n=n->hijo[1];
    }

    return 0;
}

