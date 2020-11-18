#include <vector>
#include <iostream>
#include <list>
#include <iterator>
#include <memory>

#include "lab2.h"
int main()
{

/*
Лабораторная работа №2

initializer_list, move, forward, default, delete, move итераторы


Задание 1. Создайте класс, который должен быть "оберткой" для вектора с УНИКАЛЬНЫМИ значениями любого типа в заданном диапазоне.
Внимание: при инициализации НЕ нужно менять порядок значений, заданный пользователем! При наличии повторяющихся значений нужно оставить первое!
•	Для хранения элементов используйте std::vector
•	Реализуйте конструктор, который может принимать любое количество значений (значения могут повторяться)
•	Реализуйте метод добавления любого количества значений (значения могут повторяться)
•	Реализуйте метод удаления любого количества значений (значения могут повторяться)
•	Реализуйте метод сортировки, который будет принимать в качестве параметра признак по возрастанию / по убыванию
•	и другие (полезные на Ваш взгляд) методы	
*/
{
    std::cout << "---------- [1] ----------\n";

    MyVec<int> v{-10, 2, -5, 4, 3, 5, 4, 9, -11, 15};
    MyVec<int> v2{2};
    v.print();
    v2.print();

    std::cout << "min max: \n";
    v.setMinMax(-5, 5);
    v.print();

    std::cout << "add: \n";
    v.add({-10, 0, -3, -2 , 2, 3, 4, 5});
    v.print();

    std::cout << "del: \n";
    v.del({1, 2, 3, 4});
    v.print();

    std::cout << "sort: \n";
    v.sort([](const int& e1, const int& e2){return e1 < e2;});
    v.print();
}

//Задание 2. Реализуйте шаблонный класс, который является оберткой для очереди с элементами любого типа. 
//Очередь требуется реализовать посредством динамического массива, при этом использовать массив как циклический буфер.
//Пояснение: так как очередь – это специфическая структура данных, для которой новые данные помещаются в конец, а  «старые» данные изымаются из начала очереди =>
//если последний элемент массива задействован, то начало скорее всего уже освободилось => «закольцовываем» буфер, продолжая заполнять с нулевого элемента.
//Несмотря на указанную специфичность такой структуры данных, могут возникать ситуации, когда пользователь вызвал push(), а свободных элементов в очереди не осталось =>
//при необходимости массив следует «расширять».
//При реализации нужно обеспечить эффективную работу с динамической памятью=>
//•	предусмотреть наличие резервных элементов
//•	память без очевидной необходимости не перераспределять
//Внимание!
//1.	Очередь реализуем без использования «сырой памяти»! А эффективность достигаем за счет использования move-семантики
//2.	Очередь выводим на печать с помощью range-base-for
//Тестируем разработанный класс на приведенном ниже фрагменте. Следующий фрагмент должен работать не только корректно, но и эффективно:
{
    std::cout << "---------- [2] ----------\n";


    using MyString = std::string;

//ЗАДАНИЕ
    //MyQueue<MyString>  q1{ MyString(“AAA”), MyString (“qwerty”), MyString("asdf")};
    //использование MyQueue в диапазонном for:
//    for (auto& el : q1)  {  std::cout << el << ' '; }
//    MyString s(“abc”);
//    q1.push(s);
//    q1.push(MyString(“123”));
//    MyString s1 = q1.pop();
//    q1.push(“qqq”);
//    MyQueue < MyString >  q2 = q1;
//    MyQueue < MyString >  q22 = std::move(q1);

//    MyQueue < MyString >  q3{10, MyString (“!”)}; //очередь должна содержать 10 элементов со строкой «!»
//    q1 = q3;
//    q2 = MyQueue < MyString >  (5, MyString (“?”));
//    q1 = { MyString(“bbb”), MyString (“ssss”)};



    MyQueue0<MyString>  q1{ MyString("AAA"), MyString ("qwerty"), MyString("asdf")};
    q1.print();

    std::cout << "print with iterator: \n";

    for(MyQueue0<MyString>::iterator i = q1.begin(); i != q1.end(); ++i){
        std::cout << *i << " ";
    }
    std::cout << "\n";



    //использование MyQueue в диапазонном for:
    std::cout << "использование MyQueue в диапазонном for: \n";
    for (auto& el : q1)  {
        std::cout << el << ' ';
    }
    std::cout << std::endl;
    MyString s("abc");
    q1.push(s);
    q1.push(MyString("123"));
    MyString s1 = q1.pop();
    q1.push("qqq");
    MyQueue0<MyString>  q2 = q1;
    MyQueue0<MyString>  q22 = std::move(q1);

    MyQueue0<MyString>  q3{10, MyString ("!")}; //очередь должна содержать 10 элементов со строкой «!»
    q1 = q3;
    q2 = MyQueue0<MyString>(5, MyString ("?"));
    q1 = { MyString("bbb"), MyString ("ssss")};

}

//Задание 3. Реализуйте шаблон класса MyUniquePTR, который является оберткой для указателя на объект любого типа.
//Задача – класс должен обеспечивать единоличное владение динамически создаваемым объектом. Проверить функционирование шаблона на примере MyString:
{
        std::cout << "---------- [3] ----------\n";
        using MyString = std::string;

//      ЗАДАНИЕ:
//        MyUniquePTR<MyString> p1(new MyString (“abc”));
//        std:: cout<<p1->GetString();
//        p1->SetNewString(“qwerty”);
//        MyString  s2 = *p1;
//        //MyUniquePTR< MyString > p2=p1; //здесь компилятор должен выдавать ошибку =>
//        Исправьте!
//        If(p1) {std::cout<<”No object!”} //а это должно работать
//        MyUniquePTR< MyString > p3(new MyString (“vvv”));
//        //p3 = p2; //и здесь компилятор должен выдавать ошибку
//        vector< MyUniquePTR< MyString >> v; //как проинициализировать???
//        list< MyUniquePTR< MyString >> l;
//        //как скопировать из v в l ???



    MyUniquePTR<MyString> p1(new MyString ("abc"));
    std::cout << p1->c_str() << std::endl;

    //p1->SetNewString(“qwerty”);
    *p1 = std::string("qwerty"); // вызывается move
    std::cout << *p1 << "\n";

    MyString  s2 = *p1;

    //MyUniquePTR< MyString > p2=p1; //здесь компилятор должен выдавать ошибку =>

    //Исправьте!
    if(!p1)
        std::cout << "No object!\n";    //а это должно работать
    else
        std::cout << "p1: " << *p1 << "\n";

    //p3 = p2; //и здесь компилятор должен выдавать ошибку
    std::vector< MyUniquePTR< MyString >> v;
    //как проинициализировать???
    v.push_back(MyUniquePTR<MyString>(new MyString("asdf")));
    v.push_back(MyUniquePTR<MyString>(new MyString("1231")));
    v.push_back(MyUniquePTR<MyString>(new MyString("AKHDG")));

    std::list< MyUniquePTR< MyString >> l;
    //как скопировать из v в l ???
    //перемещение
    std::copy(std::move_iterator(v.begin()), std::move_iterator(v.end()), std::back_inserter(l));

    //или копирование
    //std::transform(v.begin(), v.end(), std::back_inserter(l), [](auto& e){ return MyUniquePTR<MyString>(new MyString(*e));});

    auto printUniqueCont = [](auto& c){
        for(auto& i : c) {
            if(i) std::cout << *i << " ";
            else  std::cout << i << " ";
        }
        std::cout << "\n";
    };
    std::cout << "v: \n";
    printUniqueCont(v);
    std::cout << "l: \n";
    printUniqueCont(l);
}




#if 0
    {
        std::cout << "test...\n";
        std::unique_ptr<std::string> stdP;

        MyUniquePTR<std::string> p(new std::string("mystring"));
        std::cout << "bool: " << (bool)p << "\n";
        std::cout << "*p: " << *p << "\n";


        MyUniquePTR<std::string> p2(std::move(p));
        std::cout << "move constructor p2: " << *p2 << " p: " << p << std::endl;

        MyUniquePTR<std::string> p3;
        p3 = std::move(p2);
        std::cout << "move operator= p3: " << *p3 << " p2: " << p2 << std::endl;
    }
#endif




	return 0;
}


