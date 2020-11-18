#include "lab_4.h"

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <list>
#include <memory>
#include <stack>
#include <queue>
//#include <priority_queue>


int Human::cnt = 0;

int main()
{
	
/***************************************************************/
//Задание 1.
	/*
	Реализуйте шаблон функции для печати любых последовательностей (vector, list, deque, set и встроенного массива), которые могут содержать:
	•	как объекты любого типа,
	•	так и указатели на объекты любого типа (указатели распечатывать неинтересно => в этом случае следует получать значение по адресу)
	Подсказки: if constexpr
	*/
	{
        std::cout << "----------------------------- [1] ----------------------------------\n";


        std::vector <std::string> v{"123", "456", "asd"};
        print(v);
        std::list <std::string*> l{new std::string("123"), new std::string("asd")};
        print(l);

        for(auto & i : l)
            delete i;

        std::deque <std::shared_ptr<std::string>> d{std::make_shared<std::string>("123"), std::make_shared<std::string>("321")};
        print(d);

	}

/***************************************************************/
//Задание 2.
	/* Реализуйте шаблон функции сложения двух значений.
    Если первое слагаемое является вектором, то все элементы вектора нужно увеличить на значение второго параметра.
    При этом элементы вектора и второй параметр должны быть одного и того же типа.
	Подсказки: if constexpr, is_same
	*/
	{
        std::cout << "----------------------------- [2] ----------------------------------\n";
        std::vector<int> vi{1, 2, 3};
        std::vector<double> vd{1, 2, 3};
        int elem{10};
        sum2elem(vi, elem);
        print(vi);
        sum2elem(vd, elem);
        print(vd);

        std::vector<std::string> vs{"123", "123", "123"};
        std::string s("add");
        sum2elem(vs, s);
        print(vs);
    }


	/***************************************************************/
//Задание 3.
	/* 	Реализуйте шаблон функции вывода на печать значений элементов любого адаптера (stack, queue, priority_queue)
	Подсказки: if constexpr, is_same
	Предусмотрите вывод значений, если в адаптере хранятся указатели.
	*/
	{
        std::cout << "----------------------------- [3] ----------------------------------\n";

        std::stack <int> s;
        for(auto i : {1, 2, 3, 4, 5}){
            s.push(i);
        }
        std::queue <int> q;
        for(auto i : {1, 2, 3, 4, 5}){
            q.push(i);
        }
        std::priority_queue <int> p;
        for(auto i : {1, 2, 3, 4, 5}){
            p.push(i);
        }


        printAdapt(s);
        printAdapt(q);
        printAdapt(p);
    }

/***************************************************************/
//Задание 4.
	{
        std::cout << "----------------------------- [4] ----------------------------------\n";
        //Дан массив элементов типа string

        std::string strings[] = {"abc", "123", "qwerty", "#$%"};


		//До завершения фрагмента строки должны существовать в единственном экземпляре.
		//Требуется обеспечить манипулирование строками а) без копирования и б) без изменения порядка
		//элементов в массиве!
		
		//В std::set "складываем" по алфавиту обертки для строк, которые содержат только буквы 


        std::set<std::shared_ptr<std::string>> set;
        for(const auto& s : strings){
            std::string res;

            bool ok{false};
            for(const auto e : s){
                if((e >= 'a' && e <= 'z') || (e >= 'A' && e <= 'Z')){
                    ok = true;
                }
                else{
                    ok = false;
                    break;
                }
            }
            if(ok){
                set.insert(std::shared_ptr<std::string>(new std::string(std::move(s))));
            }

        }
		

        //__asm nop
		/******************************************************************************************/

		//В std::vector "складываем" обертки для строк, которые содержат только цифры 
		//Выводим на экран
		//Находим сумму
		
        std::vector<std::shared_ptr<std::string>> vec;
        for(const auto& s : strings){

            bool ok{true};
            for(const auto e : s){
                if(!(e >= '0' && e <= '9')){
                    ok = false;
                    break;
                }
            }
            if(ok){
                vec.push_back(std::shared_ptr<std::string>(new std::string(std::move(s))));
            }

        }


		/******************************************************************************************/
		//сюда "складываем" обертки для строк, которые не содержат ни символов букв, ни символов цифр
		//и просто выводим

        std::vector<std::shared_ptr<std::string>> vec2;

        for(const auto& s : strings){

            bool ok{false};
            for(const auto e : s){
                if((e >= 'a' && e <= 'z') || (e >= 'A' && e <= 'Z') || (e >='0' && e <='9')){
                    ok = false;
                    break;
                }
                else{
                    ok = true;
                }
            }
            if(ok){
                vec2.push_back(std::shared_ptr<std::string>(new std::string(std::move(s))));
            }
        }


        std::cout << "set: \n";
        for(const auto& i : set){
            std::cout << *i << " ";
        }
        std::cout << "\n";

        std::cout << "vec: \n";
        for(const auto& i : vec){
            std::cout << *i << " ";
        }
        std::cout << "\n";

        std::cout << "vec2: \n";
        for(const auto& i : vec2){
            std::cout << *i << " ";
        }
        std::cout << "\n";

	}

	
/******************************************************************************************/
//Задание 5. 
	{
        std::cout << "----------------------------- [5] ----------------------------------\n";
        //Дано:
        std::string ar[] = {"my", "Hello", "World"};
		std::vector < std::shared_ptr<std::string>> v = {std::make_shared<std::string>("good"), std::make_shared<std::string>("bye")};
		


		//а) Требуется добавить в вектор обертки для элементов массива, НЕ копируя элементы массива! 

        std::transform(std::begin(ar), std::end(ar), std::back_inserter(v), [](auto& e){
            return std::shared_ptr<std::string>(new std::string(std::move(e)));
        });


		//б) Отсортировать вектор по алфавиту и вывести на экран
        std::sort(v.begin(), v.end());

        std::cout << "sorted: \n";
        for(const auto& i : v){
            std::cout << *i << " ";
        }
        std::cout << std::endl;

		//в) Обеспечить корректное освобождение памяти


        //__asm nop
	}
	/***************************************************************/
		//Задание 6. shared_ptr и weak_ptr
		//Создаем генеалогическое дерево посредством класса human. В классе хранятся:
		//имя - string
		//возможно признак: жив или уже нет...
		//родители - shared_ptr (родители не всегда известны...)
		//дети - контейнер из weak_ptr (чтобы избежать циклических зависимостей)

		//Методы класса human:
		//конструктор - для инициализации имени и признака
		//конструктор копирования, оператор присваивания, move ???
		//статический метод child() - 
		//				должен создать создать и вернуть обертку для родившегося человека
		//				+ сформировать все связи ребенка с родителями и наоборот

		//Ввести возможность распечатать генеалогическое дерево для указанного индивидума

	{
        std::cout << "----------------------------- [6] ----------------------------------\n";

		//История должна с кого-то начинаться => "Жили-были дед да баба, например, Адам и Ева"
		//(то есть на самом деле два деда и две бабы):


        std::shared_ptr<Human> grandM(new Human("Eva"));
        std::shared_ptr<Human> grandF(new Human("Adam"));
        //...

		//у них появились дети - child():
        auto f = child(grandM, grandF, "Ivan");
        auto m = child(grandM, grandF, "Masha");

		//а у детей в свою очередь свои дети:
        auto c1 = child(m, f, "Vasya");
        auto c2 = child(m, f, "Natasha");

        grandF->print();

		//...
        //__asm nop
	}



//***************************************************************/
//Задание 7.

	/*Пользовательский deduction guide – для вывода типов параметров шаблона
	Задан шаблон класса, который инкапсулирует внедренный ограниченный массив известной
	размерности с элементами любого типа. */
/*
template<typename T, size_t size> class MyArray
	{
		T ar[size]; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?
		…
	};
        MyArray<int, 5> ar1;//MyArray<int,5>
        MyArray ar2{"ABC"}; //MyArray<char,4>
        int ar[] = { 1,2,3 };
        MyArray ar3{ ar };

*/

//Требуется обеспечить работоспособность приведенных примеров использования.
	{
        std::cout << "----------------------------- [7] ----------------------------------\n";



        MyArray<int, 5> ar1;//MyArray<int,5>
        print0(ar1.ar);

        MyArray ar2{"ABC"}; //MyArray<char,4>
        print0(ar2.ar);

        int ar[] = { 1,2,3 };
        MyArray ar3{ ar };
        print0(ar3.ar);

	}


    //__asm nop

}
