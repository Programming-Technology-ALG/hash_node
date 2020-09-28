#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<math.h>

#define P 29
#define M 300000*2
#define words 300000

using namespace std;

ifstream fin("words.txt");

int kol = 0;

struct Node{
    Node* previous = nullptr;
    Node* next = nullptr;
    char c[30];
};

struct Hash
{
    int key = 0;
    Node* value = nullptr;
};

unsigned int fun(string s) {
    unsigned int a{ 0 };
    for (int i = 0; i < s.size(); i++)
        a = (a + s[i] * (int)pow(P, i)) % M;
    return a;
}

Node* makeNode(char* s) {
    Node* list = new Node;
    strcpy(list->c, s);
    return list;
}

Node* addNode(Node* list, char* s) {
    if (list == nullptr)
        list = makeNode(s);
    else
        list->next = addNode(list->next, s);
    return list;
}

bool search(Node* list, char * s) {
    if (strcmp(list->c, s) == 0) return true;
    if (list->next != nullptr) return search(list->next, s);
    return false;
}

int main() {
    Hash* table = new Hash[M];
    char exit[] = "/exit";
    char s[30];
    unsigned int k;
    for (int i = 0; i < words; i++) {
        fin>>s;
        k = fun(s);
        if (table[k].value != nullptr) kol++;
        table[k].value = addNode(table[k].value, s);
    }
    cout << "Последнее слово, внесченное в таблицу: " << s<<"\n";
    cout<<kol << " коллиции: \n\n";
    clock_t start;
    clock_t finish;
    int p = 0;
    for (int i = 0; i < words; i++)	{
        k = fun(s);
        if (table[k].value != nullptr && search(table[k].value, s))
            p++;
    }
    cout << p<<"Слов в таблицу внесено: \n";
    while (1) {
        cout << "\nДля выхода введите: /exit\n\n";
        cout << "Слово для помиска: ";
        cin >> s;
        start = clock();
        if (strcmp(exit, s) == 0)
            break;
        k = fun(s);
        if (table[k].value!=nullptr && search(table[k].value, s))
            cout << "Это слово есть в таблице\n";
        else
            cout << "Этого слова нет в табице\n";
        finish = clock();
        printf("Программа работала %.2f сек\n\n",(double) finish - start);
    }
    return 0;
}