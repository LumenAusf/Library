#ifndef LIBRARY_H
#define LIBRARY_H
#include <string>

class Library
{
    //======================= Книга (и так понятно) ==========================================
    class Book
    {
    public:
        std::string idb = "";       //Индекс книги
        std::string name = "";      //Название книги
        std::string author = "";    //Автор, это сильное заявление, проверять я его не буду
    };
    //======================= Читатель (ну мы же не звери) ===================================
    class User
    {
    public:
        std::string idu = "";       //Индекс Читателя
        std::string name = "";      //Имя читателя

        void GetBook();     //-------------------Даём Читателю нигу---------------------------
        void ReturnBook();  //-------------------Забираем книгу-------------------------------

    };
    //======================= Приватные методы ===============================================

    static bool ViewCatalog(char choice, std::string usr);      //**Просмотр каталогoв********
    void ViewUser();                                            //**Рабобта с Читателем*******
    static void Create(char choice);                            //**Создание книги/читателя***
    static void Delete(char choice, std::string id);            //**Удаление книги/читателя***
    //======================= Конец приватной вечеринки ======================================
public:
    void Start();
};

#endif // LIBRARY_H