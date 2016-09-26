#include <iostream>
#include <vector>

#define tam 11

using namespace std;

template<class T>
struct Nodo
{
    T dato;
    Nodo * next{};

    Nodo(){}
    Nodo(T d)
    {
        dato=d;
    }
};

template <class T>
struct comparador
{
    inline bool operator()(T x,T y)
    {
        return x!=y;
    }
};

template<class T>
class Lista
{
    public:

    typedef comparador<T> M;
    typedef Nodo<T> node;

    node * head{};
    M comp;

        Lista() {}

        bool find(T x,node **&p)
        {
            for(p=&head;*p && comp((*p)->dato,x);p=&((*p)->next));
            return !!(*p);
        }

        bool insert(T x)
        {
            node **p;
            if(find(x,p)) return 0;

            node *q=new node(x);
            q->next=*p;
            *p=q;
            return 1;
        }

        bool remove(T x)
        {
            node **p;
            if(!find(x,p)) return 0;

            node *q=*p;
            *p=q->next;
            delete q;

            return 1;
        }
        void recorre()
        {
            node **p;
            for(p=&head;*p;p=&((*p)->next))
                cout<<(*p)->dato<<" -> ";
            cout<<"//";
        }

        virtual ~Lista() {}
    protected:
    private:
};

template <class T>
struct FuncionDisp
{
    inline T operator()(T x)
    {
        return x%tam;
    }
};
struct traits
{
    typedef int T;
    typedef Lista<T> L;
    typedef FuncionDisp<T> F;

};


template<class Tr>
class HashTable
{
    public:

    typedef typename Tr::T T;
    typedef typename Tr::L list;
    typedef typename Tr::F funtion;
    typedef Nodo<T> node;

    list * table[tam];
    funtion fd;

        HashTable()
        {
            for(int i=0;i<tam;i++)
                table[i]=new list;
        }

        bool insert(T x)
        {
            T pos=fd(x);
            table[pos]->insert(x);
            return 1;
        }

        bool remove(T x)
        {
            T pos=fd(x);
            table[pos]->remove(x);
            return 1;
        }
        void recorre()
        {
            for(int i=0;i<tam;i++)
            {
                cout<<" [ "<<i<<" ]  -> ";
                table[i]->recorre();
                cout<<endl;
            }

        }

        virtual ~HashTable() {}
    protected:
    private:
};


int main()
{
    HashTable<traits> t;
    t.insert(4);
    t.insert(6);
    t.insert(8);
    t.insert(1);
    t.insert(12);
    t.insert(13);
    t.insert(21);
    t.insert(15);
    t.insert(11);
    t.insert(64);

    t.recorre();
    t.remove(1);
    t.recorre();

    return 0;
}
