#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum EState { S, Ai, Ac, As, Bs, Cs, At, E, F };
enum ELexType { lSelect, lCase, lDefault, lEnd, lAs, lAo, lAm, lVar, lConst, lAt };
struct Lex {
    ELexType type;
    //int index;
    int pos;
    string lexem;
    Lex* next, * prev;
} *pFirst = NULL, * pLast = NULL;

int Syntax[10][13] =
{/*   0   1   2   3   4   5   6   7   8   9   10  11  12*/
    { 1,  13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13 },//lSelect
    { 13, 13, 3,  13, 13, 13, 13, 3,  13, 13, 13, 13, 13 },//lCase
    { 13, 13, 13, 13, 13, 13, 13, 8,  13, 13, 13, 13, 13 },//lDefault
    { 13, 13, 13, 13, 13, 13, 13, 9,  13, 13, 13, 13, 9 }, //lEnd
    { 13, 13, 13, 13, 13, 6,  13, 13, 13, 13, 11, 13, 13 },//lAs
    { 13, 13, 1,  13, 13, 13, 13, 6,  13, 13, 13, 13, 11 },//lAo
    { 13, 13, 1,  13, 13, 13, 13, 6,  13, 13, 13, 13, 11 },//lAm
    { 13, 2,  13, 13, 5,  13, 7,  13, 10, 13, 13, 12, 13 },//lVar
    { 13, 2,  13, 4,  13, 13, 7,  13, 13, 13, 13, 12, 13 },//lConst
    { 13, 13, 13, 13, 13, 13, 13, 4,  13, 13, 13, 13, 8 } //lAt
};

int const P[7][8] = {
    /*Ц  Б  = +,- *,/ ; E  F */
    { 2, 1, 3, 4, 5, 6, 7, 7 }, //S 
    { 1, 1, 3, 4, 5, 6, 7, 8 }, //Ai
    { 2, 7, 3, 4, 5, 6, 7, 8 }, //Ac
    { 2, 1, 7, 7, 7, 7, 7, 8 }, //As
    { 2, 1, 7, 7, 7, 7, 7, 8 }, //Bs
    { 2, 1, 7, 7, 7, 7, 7, 8 }, //Cs
    { 2, 1, 7, 7, 7, 7, 7, 8 }, //At
};
class ErrorFileExists
{
public:
    void Print()
    {
        cout << "Файла не существует либо он пуст" << endl;
    }
};
class ErrorLexAnalisis
{
private:
    const char* word;
public:
    ErrorLexAnalisis(const char* s) : word(s)
    { }
    void Print()
    {
        cout << "Ошибка лексического анализа: " << word << endl;
    }
};
class ErrorSyntaxAnalisis
{
private:
    const char* text;
    int position = -1;
public:
    ErrorSyntaxAnalisis(const char* s) : text(s)
    { }
    ErrorSyntaxAnalisis(const char* s, int pos) : text(s)
    {
        position = pos;
    }
public:
    void Print()
    {
        if (position != -1)
            cout << text << position << endl;
        else
            cout << text << endl;
    }
};

class LexAnalis
{
private:
    bool errorLex = false;
    int size;
    ifstream fin;

    ELexType typeKeywords(int i)
    {
        switch (i)
        {
        case 0: return lSelect;
        case 1: return lCase;
        case 2: return lDefault;
        default: return lEnd;
        }
    }
    ELexType typeSpecialCharacter(const char t)
    {
        switch (t)
        {
        case '=': return lAs;
        case '+': case '-':  return lAo;
        case '*': case '/':  return lAm;
        default: return lAt;
        }
    }
    int gettype(char c)
    {
        if (isdigit(c))
            return 0;
        else if (isalpha(c))
            return 1;
        else if (c == '=')
            return 2;
        else if (c == '+' || c == '-')
            return 3;
        else if (c == '*' || c == '/')
            return 4;
        else if (c == ';')
            return 5;
        else if (!c)
            return 7;
        else return 6;
    }
    void LexAnalysis(const char* word)
    {
        const char* str = word, * lexstart = word;
        int a, q = 0, prevQ;
        while ((q != 7) && (q != 8))
        {
            prevQ = q;

            a = gettype(*str);
            q = P[q][a];

            if (0 != prevQ && q != prevQ && q != 7) AddLex(prevQ, word, lexstart, str);
            if ((q != prevQ) && (q == 1 || q == 2 || q == 3 || q == 4 || q == 5 || q == 6))
                lexstart = str;
            if ((q != 7) && (q != 8)) str++;
        }
        if (q == 7)
            throw ErrorLexAnalisis(word);
    }
    bool isExistFile(const char* inputFile)
    {
        fin.open(inputFile);
        fin.seekg(0, ios::end);//устанавливаем курсор в конец файла
        size = (int)fin.tellg();
        fin.seekg(0, ios::beg);//устанавливаем курсор в начало файла 
        return (fin.is_open() && size);
    }
    void AddLex(int state, const char* txt, const char* lexPtr, const char* curPtr)
    {
        static int pos = 0;
        char keywords[4][8] = { "select", "case", "default", "end" };

        int k = strlen(lexPtr); //с какого символа начать(включительно)
        int m = strlen(curPtr); //до какого символа


        bool flag = false;

        char t[255];
        int i = 0;
        for (i = 0; i < k - m; ++i)//k - m сколько символов
        {
            t[i] = lexPtr[i];
        }
        t[i] = '\0';

        Lex* lex = new Lex;
        lex->prev = pLast;
        lex->next = NULL;
        if (pLast) pLast->next = lex;
        pLast = lex;
        if (!pFirst) pFirst = pLast;

        switch (state)
        {
        case 1:
        {
            ELexType type;
            for (int i = 0; i < sizeof keywords / sizeof keywords[0]; i++)
            {
                if (!strcmp(keywords[i], t))
                {
                    type = typeKeywords(i);

                    flag = true;
                    break;
                }
            }
            if (flag)
            {
                cout << t << " - ключевое слово" << endl;
                lex->lexem = t;
                lex->type = type;
                lex->pos = pos++;
            }
            else
            {
                cout << t << " - идентификатор" << endl;
                lex->lexem = t;
                lex->type = lVar;
                lex->pos = pos++;
            }
            break;
        }
        case 2:
        {
            lex->type = lConst;
            lex->pos = pos++;
            lex->lexem = t;
            cout << t << " - константа" << endl; break;
        }
        case 3: case 4: case 5: case 6:
        {
            lex->type = typeSpecialCharacter(*t);
            lex->pos = pos++;
            lex->lexem = t;
            cout << t << " - специальный символ" << endl; break;
        }
        }
    }
public:
    ~LexAnalis()
    {
        fin.close();
    }
    Lex* getListLexs(const char* inputFile)
    {
        if (isExistFile(inputFile))
        {
            char* text = new char[size];

            while (!fin.eof())
            {
                fin >> text;
                LexAnalysis(text);
            }
            delete[] text;
            cout << "Лексических ошибок нет" << endl;
            return pFirst;
        }
        else
        {
            throw ErrorFileExists();
            return NULL;
        }
    }
};

class SyntaxAnalis
{
private:
    bool parsing(Lex*& p)
    {
        int prevState = 0, state = 0;
        while (p)
        {
            prevState = state;
            state = Syntax[getLt(p->type)][prevState];

            if (state == 13)
            {
                Error(p, p->pos, p->lexem, prevState);
                return false;
            }
            p = p->next;
        }
        if (state != 9)
        {
            cout << "Ожидается end" << endl;
            return false;
        }
        return true;

    }
    void Error(Lex*& p, int pos, string& word, int state)
    {
        switch (state)
        {
        case 0: cout << "Перед '" + word + "'(позиция " << pos << ") ожидается " << "select" << endl; break;
        case 1: cout << "Перед '" + word + "'(позиция " << pos << ")  ожидается " << "переменная или константа" << endl; break;
        case 2: cout << "Перед '" + word + "'(позиция " << pos << ")  ожидается " << "арифметическая операция или case" << endl; break;
        case 3: cout << "Перед '" + word + "'(позиция " << pos << ")  ожидается " << "константа" << endl; break;
        case 4: cout << "Перед '" + word + "'(позиция " << pos << ")  ожидается " << "переменная" << endl; break;
        case 5: cout << "Перед '" + word + "'(позиция " << pos << ")  ожидается " << "операция присвоить" << endl; break;
        case 6: cout << "Перед '" + word + "'(позиция " << pos << ")  ожидается " << "переменная или константа" << endl; break;
        case 7: cout << "Перед '" + word + "'(позиция " << pos << ")  ожидается " << "case, default, end, арифметическая операция или ;" << endl; break;
        case 8: cout << "Перед '" + word + "'(позиция " << pos << ")  ожидается " << "переменная" << endl; break;
        case 9: cout << "Лишние символы после end" << endl; break;
        case 10: cout << "Перед '" + word + "'(позиция " << pos << ")  ожидается " << "операция присвоить" << endl; break;
        case 11: cout << "Перед '" + word + "'(позиция " << pos << ")  ожидается " << "переменная или константа" << endl; break;
        case 12: cout << "Перед '" + word + "'(позиция " << pos << ") ожидается " << "end, арифметическая операция, ;" << endl; break;
        }
    }
    int getLt(ELexType elt)
    {
        switch (elt)
        {
        case lSelect: return 0;
        case lCase: return 1;
        case lDefault: return 2;
        case lEnd: return 3;
        case lAs: return 4;
        case lAo: return 5;
        case lAm: return 6;
        case lVar: return 7;
        case lConst: return 8;
        case lAt: return 9;
        }
        return 0;
    }
public:
    SyntaxAnalis(Lex* p)
    {
        if (parsing(p))
            cout << "Синтаксических ошибок нет" << endl;
        else
            cout << "Синтаксическая ошибка" << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    LexAnalis lexem;

    try
    {
        SyntaxAnalis syntax(lexem.getListLexs("main.cpp"));
    }
    catch (ErrorFileExists& e)
    {
        e.Print();
    }
    catch (ErrorLexAnalisis& e)
    {
        e.Print();
    }
    catch (ErrorSyntaxAnalisis& e)
    {
        e.Print();
    }
    catch (...)
    {
        cout << "Неизвестная ошибка" << endl;
    }
    system("pause");
    return 0;
}