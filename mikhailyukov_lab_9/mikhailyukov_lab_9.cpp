﻿#include <iostream>
using namespace std;

class Tree {
public:
    static void SetTiresCount()
    {
        cout << "Введите число ярусов дерева: ";
        int EnteredTiresCount = 0;
        bool NumberIsNotNatural = true;
        do {
            EnteredTiresCount = GetIntegerNumber();
            NumberIsNotNatural = (EnteredTiresCount < 1);
            if (NumberIsNotNatural) {
                cout << "Ошибка: число не натуральное\n";
                cout << "Введите данные снова: ";
            }
        } while (NumberIsNotNatural);
        TiresCount = EnteredTiresCount;
    }

    void BuildTree(Tree*& Node, int NumberOfPreviousTier = 0) {
        int NumberOfCurrentTier = NumberOfPreviousTier + 1;
        if (NumberOfCurrentTier < TiresCount) {
            for (int i = 0; i < BranchesCount; i++) {
                Branche[i] = new Tree;
                (*this->Branche[i]).BuildTree(this->Branche[i], NumberOfCurrentTier);
            }
        }
    }

    void PrintTree(Tree*& Node, int NumberOfPreviousTier = 0)
    {
        int CurrentTire = NumberOfPreviousTier + 1;
        if (Node != NULL)
        {
            for (int i = 0; i < BranchesCount / 2; i++) {
                (*this->Branche[i]).PrintTree(this->Branche[i], CurrentTire);
            }

            for (int i = 0; i < CurrentTire - 1; i++) {
                cout << "   ";
            }
            cout << this->Data << "\n";

            for (int i = BranchesCount / 2; i < BranchesCount; i++) {
                (*this->Branche[i]).PrintTree(this->Branche[i], CurrentTire);
                if ((CurrentTire == TiresCount - 1) && (i == BranchesCount - 1)) {
                    cout << "\n";
                }
            }
        }
    }

    void DeleteTree(Tree*& Node) {
        if (Node != NULL)
        {
            for (int i = 0; i < BranchesCount; i++) {
                (*this->Branche[i]).DeleteTree(this->Branche[i]);
            }
            delete Node;
            Node = NULL;
        }
    }

    Tree() {
        this->Data = rand() % 10;
        for (int i = 0; i < BranchesCount; i++) {
            this->Branche[i] = NULL;
        }
    }

private:
    static int GetIntegerNumber()
    {
        int Number = 0;
        bool DataIsNotNumber = true;
        while (DataIsNotNumber)
        {
            int Number;
            cin >> Number;
            DataIsNotNumber = cin.fail();
            if (DataIsNotNumber)
            {
                cout << "Ошибка: вы ввели не число\n";
                cout << "Введите данные снова: ";
                cin.clear();
                cin.ignore(32767, '\n');
            }
            else {
                cin.ignore(32767, '\n');
                return Number;
            }
        }       
    }

    int Data;
    static int TiresCount;
    static const int BranchesCount = 3;
    Tree* Branche[BranchesCount];
};

int Tree::TiresCount = 0;

int main()
{
    setlocale(LC_ALL, "Russian");

    Tree::SetTiresCount();

    Tree* RootPtr = new Tree;
    (*RootPtr).BuildTree(RootPtr);

    (*RootPtr).PrintTree(RootPtr);

    (*RootPtr).DeleteTree(RootPtr);

    return 0;
}