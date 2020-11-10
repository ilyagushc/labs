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
    std::cout << "---------- [2] ----------\n";


    using MyString = std::string;

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


//Задание 3. Реализуйте шаблон класса MyUniquePTR, который является оберткой для указателя на объект любого типа.
//Задача – класс должен обеспечивать единоличное владение динамически создаваемым объектом. Проверить функционирование шаблона на примере MyString:
{
    std::cout << "---------- [3] ----------\n";

    using MyString = std::string;

    MyUniquePTR<MyString> p1(new MyString ("abc"));
    //std::cout << p1->GetString();
    std::cout << p1->c_str() << std::endl;

    //p1->SetNewString(“qwerty”);
    *p1 = std::string("qwerty"); // вызывается move
    std::cout << *p1 << "\n";

    MyString  s2 = *p1;

    //error!!!
    //MyUniquePTR< MyString > p2=p1; //здесь компилятор должен выдавать ошибку =>

    //Исправьте!
    if(p1) {
        std::cout << "No object!\n";    //а это должно работать
    }
    else{
        std::cout << "p1 not null object!\n";
    }

    ///TODO: рабочий перемещающий конструктор и = !!!
//    {
//        std::unique_ptr<std::string> stdP;

//        MyUniquePTR<std::string> p(new std::string("mystring"));
//        std::cout << "bool: " << (bool)p << "\n";
//        std::cout << "*p: " << *p << "\n";

//        //MyUniquePTR<std::string> p2(std::move(p));
//        MyUniquePTR<std::string> p3(MyUniquePTR<std::string>(new std::string("new_string")));
//        std::cout << "move constructor p3: " << *p3 << std::endl;

//        MyUniquePTR<std::string> p4;
//        p4 = std::move(p3);
//        //p4.operator=(std::move(p3));

//        std::cout << "move= p3: " << p3 << "\n";
//        std::cout << "move= p4: " << p4 << "\n";
//    }


{
        std::unique_ptr<std::string> p(new std::string("123"));
        std::vector<std::unique_ptr<std::string>> v;
        //{std::unique_ptr(new std::string("asdf")); };
        //v.push_back(std::unique_ptr(new std::string("asdf")));
        //v.push_back(std::make_unique<std::string>(new std::string("sdr")));
        std::unique_ptr<std::string> tmp(new std::string("asdf"));
        v.push_back(std::move(tmp));
}


    MyUniquePTR< MyString > p2(new MyString ("vvv"));
    //p2 = p1; //и здесь компилятор должен выдавать ошибку

    std::vector< MyUniquePTR< MyString >> v(10);
    //v.reserve(10);
    //v.push_back(MyUniquePTR<MyString>(new MyString("123")));
    MyUniquePTR<std::string> tmp(new std::string("123"));
    //v.push_back(std::move(tmp));
    //v.emplace_back(new MyString("sdf"));



    //v.push_back(std::move(tmp));
    //v.push_back( MyUniquePTR<MyString>(new MyString("123")) );
    //v.emplace_back( new MyString("123") );
//        MyUniquePTR<MyString>(new MyString("456")),
//        MyUniquePTR<MyString>(new MyString("789"))
//    }; //как проинициализировать???

//    std::cout << "vector: ";
//    for(auto& e : v){
//        std::cout << *e << " ";
//    }
    std::cout << "\n";

//    std::list<MyUniquePTR<MyString>> l;
//    std::copy(std::move_iterator<decltype (v.begin())>(v.begin()),
//              std::move_iterator<decltype (v.end())>(v.end()),
//              std::back_inserter(l));

    //как скопировать из v в l ???

}


	return 0;
}


