#include "library.h"
#include <fstream>
#include <iostream>
#include <vector>

void Library::User::GetBook()
{
    std::fstream file;
    char choice;
    Book book;
    std::vector<int> v;
    int value;

    system("clear");
    if(!ViewCatalog('b', ""))
    {
        std::getchar();
        return;
    }
    std::cout << "\nВведите номер книги или q для возврата в меню: ";
    std::cin >> book.idb;
    if(book.idb == "q")
        return;
    file.open("./book/" + book.idb, std::ios::in);
    if(!file)
    {
        std::cout << "\n Такой книги нету";
        std::getchar();
        std::getchar();
        GetBook();
        return;
    }
    std::getline(file, book.name);
    file.close();
    do
    {
        system("clear");
        std::cout << name << " <- " << book.name << "\n\n";
        std::cout << "Для выдачи книги нажмите 1\n";
        std::cout << "Для возврата в предыдущее меню нажмите q\n";
        std::cin >> choice;
        switch (choice) {
        case '1':
        {
            file.open("./user/" + idu, std::ios::in);
            std::getline(file, name);
            if(file.eof())
            {
                file.close();
                file.open("./user/" + idu, std::ios::out);
                file << name << "\n" << book.idb;
                file.close();
            }else
            {
                while(!file.eof())
                {
                    file >> value;
                    v.push_back(value);
                }
                file.close();
                file.open("./user/" + idu, std::ios::out);
                file << name << "\n" <<v.at(0);
                for(unsigned int i = 1; i < v.size(); i++)
                {
                    file << ' ' << v.at(i);
                }
                file << ' ' << book.idb;
                file.close();
            }
            file.open("./book/" + book.idb, std::ios::in);
            std::getline(file, book.name);
            if(file.eof())
            {
                file.close();
                file.open("./book/" + book.idb, std::ios::out);
                file << book.name << "\n";
                file << idu;
                file.close();
            }else
            {
                v.clear();
                while(!file.eof())
                {
                    file >> value;
                    v.push_back(value);
                }
                file.close();
                file.open("./book/" + book.idb, std::ios::out);
                file << book.name << "\n" << v.at(0);
                for(unsigned int i = 1; i < v.size(); i++)
                {
                    file << ' ' << v.at(i);
                }
                file << ' ' << idu;
                file.close();
            }
        }
        case 'q':
        return;
        break;
        }
    }while(true);
}
void Library::User::ReturnBook()
{
    std::fstream file;
    std::string id, bname;
    std::vector<int> v;
    char choice;
    int value;

    system("clear");
    if(!ViewCatalog('d', idu))
    {
        std::getchar();
        return;
    }
    std::cout << "\nВведите ID книги или q для выхода ";
    std::cin >> id;
    if(id == "q")
        return;
    file.open("./user/" + idu, std::ios::in);
    bool flag = false;
    std::getline(file, name);
    while (!file.eof())
    {
        file >> value;
        if(std::to_string(value) != id)
        {
            v.push_back(value);
        }else
            flag = true;
    }
    file.close();
    if(flag == false)
    {
        std::cout << "\n Такой книги нету";
        std::getchar();
        std::getchar();
        ReturnBook();
        return;
    }
    file.open("./book/" + id, std::ios::in);
    std::getline(file, bname);
    file.close();
    do
    {
        system("clear");
        std::cout << name << " -> " << bname << "\n\n";
        std::cout << "Для возврата книги нажмите 1\n";
        std::cout << "Для возврата в предыдущее меню нажмите q\n";
        std::cin >> choice;
        switch (choice)
        {
        case '1':
        {
            file.open("./user/" + idu, std::ios::out);
            file << name ;
            if(!v.empty() )
                file << "\n" << v.at(0);
            for(unsigned int i = 1; i < v.size(); i++)
            {
                file << ' ' << v.at(i);
            }
            file.close();
        }
        case 'q':
        return;
        break;
        }
    }while(true);


}
//======================= Приватные методы ===============================================
void Library::ViewUser()
{
    std::fstream file;
    char choice;
    User user;

    system("clear");
    if(!ViewCatalog('u', ""))
    {
        std::getchar();
        return;
    }
    std::cout << "\nВведите номер читателя или q для возврата в меню: ";
    std::cin >> user.idu;
    if(user.idu == "q")
        return;
    file.open("./user/" + user.idu, std::ios::in);
    if(!file)
    {
        std::cout << "\n Такого читателя нету";
        std::getchar();
        std::getchar();
        ViewUser();
        return;
    }
    std::getline(file, user.name);
    file.close();
    do
    {
        system("clear");
        std::cout << user.name << "\n\n";
        std::cout << "Для выдачи книги нажмите 1\n";
        std::cout << "Для изъятия книги нажмите 2\n";
        std::cout << "Для просмотра долгов нажмите 3\n";
        std::cout << "Для удаления Читателя нажмите 4\n\n";
        std::cout << "Для возврата в главное меню нажмите q\n";
        std::cin >> choice;
        switch (choice) {
            case '1':
                user.GetBook();
                break;
            case '2':
                user.ReturnBook();
                break;
            case '3':
                ViewCatalog('d',user.idu);
                std::getchar();
                break;
            case '4':
                Delete('u',user.idu);
                return;
                break;
            case 'q':
                return;
                break;
        }
    }while(true);

}
bool Library::ViewCatalog(char choice, std::string usr)
{
    std::fstream file,file2;
    std::string path, name;
    int value;

    if(choice == 'b' || choice == 'd')
    {
        path = "./book/";
    }else
    {
        path = "./user/";
    }
    if(choice == 'b' || choice == 'u')
    {
        file.open(path + "cat", std::ios::in);
        file >> value;
    }else
    {
        file.open("./user/" + usr, std::ios::in);
        std::getline(file, name);
    }
    system("clear");
    if(!file.eof() && file)
    {
        while(!file.eof())
        {
            file >> value;
            file2.open(path + std::to_string(value), std::ios::in);
            std::getline(file2, name);
            file2.close();
            std::cout <<"ID: " << value << "\t" << name << "\n";
        }
        file.close();
        std::getchar();
        return true;
    }else
    {
        std::cout << "Список пуст";
        std::getchar();
        return false;
    }
}
void Library::Create(char choice)
{
    std::fstream file;
    int value = 0;
    std::string path, name, message;
    std::vector<int> vec;

    if(choice == 'b')
    {
        path = "./book/";
        message = " название книги ";
    }else
    {
        path = "./user/";
        message = " имя читателя ";
    }
    file.open(path + "cat", std::ios::in);
    file >> value;
    if(!file.eof())
    {
        value++;
        vec.push_back(value);
        while(!file.eof())
        {
            file >> value;
            vec.push_back(value);
        }
        value = vec.at(0);
    }else
    {
        vec.push_back(value);
    }
    file.close();
    system("clear");
    std::cout << "Введите" << message;
    std::getchar();
    std::getline(std::cin, name);
    file.open(path + std::to_string(value), std::ios::out);
    file << name;
    file.close();
    file.open(path + "cat", std::ios::out);
    file << vec.at(0);
    for(unsigned int i = 1; i < vec.size(); i++)
    {
        file << ' ' << vec.at(i);
    }
    file << ' ' << value;
    file.close();
    std::cout <<"\nID \"" << name << "\" : " << value;
    std::getchar();
}
void Library::Delete(char choice, std::string id)
{
    std::string name, path, path2;
    std::fstream file;
    char vote;
    std::vector<int> v, v2, v3;
    int value, value2;

    system("clear");
    if(choice == 'b')
    {
        path = "./user/";
        if(!ViewCatalog('b', ""))
        {
            std::getchar();
            return;
        }
        std::cout << "\nВведите номер книги или q для возврата в меню: ";
        std::cin >> id;
        if(id == "q")
            return;
        file.open("./book/" + id, std::ios::in);
        path2 = "./book/";
        if(!file)
        {
            std::cout << "\n Такой книги нету";
            std::getchar();
            std::getchar();
            Delete('b',"");
            return;
        }
    }else
    {
        path = "./book/";
        path2 = "./user/";
        file.open("./user/" + id, std::ios::in);
    }
    std::getline(file, name);
    if(!file.eof())
    {
        std::cout << "\nВНИМАНИЕ ";
        if(choice == 'b')
        {
            std::cout << "\nЭта книга сдаётся читателю";
        }else
        {
            std::cout << "\nЭтот читатель не вернул книгу";
        }
        std::cout <<"\nНажмите 1 чтобы продолжить или q для выхода: ";
        std::cin >> vote;
        if(vote == 'q')
            return;
        while(!file.eof())
        {
            file >> value;
            v.push_back(value);
        }
        file.close();
        for(unsigned int i = 0; i < v.size(); i++)
        {
            file.open(path + std::to_string(v.at(i)), std::ios::in);
            std::getline(file, name);
            while(!file.eof())
            {
                file >> value;
                if(std::to_string(value) != id)
                    v2.push_back(value);
            }
            file.close();
            file.open(path + std::to_string(v.at(i)), std::ios::out);
            file << name << "\n";
            if(v2.size() > 0)
                file << v2.at(0);
            for(unsigned int j = 1; j < v2.size(); j++)
            {
                file << ' ' << v2.at(j);
            }
            file.close();
        }
    }
    file.close();
    //v2.clear();
    path = "rm " + path2 + id;
    system(path.c_str());//"rm " + path2.c_str() + id.c_str());
    file.open(path2 + "cat", std::ios::in);
    file >> value2;
    while(!file.eof())
    {
        file >> value;
        if(std::to_string(value) != id)
            v3.push_back(value);
    }
    file.close();
    file.open(path2 + "cat", std::ios::out);
    file << value2 << "\n";
    if(v3.size() > 0)
        file << v3.at(0);
    for(unsigned int j = 1; j < v3.size(); j++)
    {
        file << ' ' << v3.at(j);
    }
    file.close();


}

//======================= Конец приватной вечеринки ======================================
void Library::Start()
{
    std::fstream file;
    char tmpChar;

    file.open("./book/cat", std::ios::in);
    if(!file)
    {
        system("mkdir book");
        file.open("./book/cat", std::ios::out);
        file.close();
    } else
        file.close();
    file.open("./user/cat", std::ios::in);
    if(!file)
    {
        system("mkdir user");
        file.open("./user/cat", std::ios::out);
        file.close();
    } else
        file.close();
    do
    {
        system("clear");
        std::cout << "----------------Читатели------------------\n";
        std::cout << "Для создания нового читателя нажмите \t1\n";
        std::cout << "Для просмотра читателя нажмите \t\t2\n";
        std::cout << "Для просмотра списка читателей нажмите \t3\n\n";
        std::cout << "------------------Книги-------------------\n";
        std::cout << "Для записи новой книги нажмите \t\t4\n";
        std::cout << "Для удаления книги нажмите \t\t5\n";
        std::cout << "Для просмотра списка книг нажмите \t6\n\n";
        std::cout << "Для выхода нажмите q\n";
        std::cin >> tmpChar;
        switch (tmpChar) {
        case '1':
        {
            Create('u');
            break;
        }
        case '2':
        {
            ViewUser();
            break;
        }
        case '3':
        {
            ViewCatalog('u',"");
            std::getchar();
            break;
        }
        case '4':
        {
            Create('b');
            break;
        }
        case '5':
        {
            Delete('b',"");
            break;
        }
        case '6':
        {
            ViewCatalog('b',"");
            std::getchar();
            break;
        }
        default:
            break;
        }
    }while(tmpChar != 'q');
}
