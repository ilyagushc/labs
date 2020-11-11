
#include <string>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>
#include <functional>
#include <list>

#include "lab_3.h"

using namespace std;

int main()
{
	
	//Задание 1. Сырые строковые литералы (Raw String Literals)
	//Выведите строку, например: my name is "Marina"
	//а) без использования Raw String Literals
	//б) посредством Raw String Literals
	//в) добавьте разделители (Delimeter)

	{
        std::cout << "----------------------- [1] ------------------------\n";
        std::cout << "My name is\"Dyadya Vasya\"" << std::endl;
        std::cout << R"(My name is "Dyadya Vasya")" << std::endl;
        std::cout << R"***(My name is "Dyadya Vasya")***" << std::endl;
        //__asm nop
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 2. Реализуйте вычисление факториала с помощью constexpr-функции.
	//
	//Подсказки/напоминания: 
	//		- constexpr – функция должна состоять из единственной инструкции return <выражение>; (пока!)
	//		- но это выражение может включать вызов другой constexpr – функции, в частности рекурсивный
	//		  вызов 
	//		- если параметр рекурсивной constexpr- функции - это константа, компилятор вычислит результат
	//		  на этапе компиляции

	//Проверьте тот факт, что компилятор вычисляет значение на этапе компиляции (если в качестве
	//				параметра используется константа, известная компилятору на этапе компиляции).
	//				Для проверки достаточно создать встроенный массив с размерностью, вычисляемой
	//				посредством constexpr-функции:

    {
        std::cout << "----------------------- [2] ------------------------\n";

        //Например:
        int ar[factorial(3)];
        cout << factorial(4) << endl;

		//или
        constexpr int n = factorial(5);
        int ar1[n];

		//попробуйте:
        int m = 7;
        //constexpr int n1 = factorial(m); //error (must be constexpr)
        //int ar2[n1];
		
		//а так?
        int n2 = factorial(m);
        //__asm nop
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 3a. Перевод с помощью пользовательского литерала из двоичного представления строкового
	//в значение, например: строку "100000000" -> в значение 256
	//Проверить результат посредством префикса 0b
	//Чтобы вызов пользовательского литерала выглядел просто и читаемо, например: 100000000_b
	//логично использовать пользовательский литерал с единственным параметром - const char*

	//Так как речь идет о литералах, логично вычислять значения на этапе компиляции
	// => реализуйте пользовательский литерал посредством constexpr - функций
	//Подсказка/напоминание: 
	//		- constexpr – функция должна состоять из единственной инструкции return <выражение>;
	//		- но это выражение может включать вызов другой constexpr – функции,
	//		- которая может быть рекурсивной (если параметр такой функции - это константа,
	//		  компилятор вычислит результат вызова рекурсивной функции на этапе компиляции)

	{
        std::cout << "----------------------- [3] ------------------------\n";
        auto res = 1010_mybin;
        std::cout << res << std::endl;
        auto res2 = 1111_mybin;
        std::cout << res2 << std::endl;

        std::cout << "constlen: " << constlen("12345") << "\n";
        std::cout << "constexpr bin: " << 100000000_constexpr_bin << std::endl;

        //__asm nop

	}

	//Задание 3b. Перевод в строковое двоичное представление, например: 256 -> "0b100000000"
	//Так как строка может быть любой длины, логичнее и проще возвращать объект std::string
	//=> возвращаемое значение не может быть constexpr!
	//Подсказка: манипулятора std::bin пока нет => преобразование в двоичную строку
	//придется делать вручную
	//Подсказка: количество разрядов в байте определяет константа CHAR_BIT - <cstdint>

	{
        std::string sBin= 256_toBinStr;
        std::cout << "sBin: " << sBin << std::endl;
        //__asm nop
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 4а. constexpr - объекты 
	//Создать класс (шаблон класса?) для хранения и манипулирования диапазоном значений.
	//В классе должны быть:
	//	переменные для хранения минимального и максимального значений,
	//	методы для получения каждого из значений
	//	метод для проверки - попадает ли указанное значение в диапазон
	//	метод, который получает любое значение данного типа и формирует результирующее значение:
	//							если принадлежит диапазону, то его и возвращаем
	//							если меньше минимального значения, возвращаем минимальное
	//							если больше максимального значения, возвращаем максимальное

	//Проверьте тот факт, что компилятор вычисляет значение на этапе компиляции. 
	//				Для проверки достаточно создать встроенный массив с размерностью, вычисляемой
	//				посредством constexpr-метода:
	{
        std::cout << "----------------------- [4] ------------------------\n";
        constexpr MinMax<int> mm{-10, 10};
        constexpr int min = mm.getMin();
        constexpr int max = mm.getMax();
        constexpr int test = mm.get(100);

        int arr1[max];
        int arr2[test];

        std::cout << "min: " << min << std::endl;
        std::cout << "max: " << max << std::endl;
        std::cout << "test(100): " << test << std::endl;

    //__asm nop
	}	

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 5. unique_ptr
	{
        std::cout << "----------------------- [5] ------------------------\n";

		//5.а - обеспечьте корректное выполнение фрагмента
		{
			std::vector<std::string*> v = { new std::string("aa"), new std::string("bb"), new std::string("cc") };

            //Распечатайте все строки
            for(const auto& i : v){
                std::cout << *i << " ";
            }
            std::cout << "\n";
		
            //__asm nop
			//???
		} //???

		//5.b - модифицируйте задание 5.а:
		 //обеспечьте посредством std::unique_ptr: 
		 //эффективное заполнение (вспомните про разные способы формирования std::unique_ptr), 
		 //безопасное хранение указателей на динамически создаваемые объекты std::string, 
		 //манипулирование,
		 //и освобождение ресурсов
		 //
			
		{
            std::vector<std::unique_ptr<std::string>> v;
            v.emplace_back(new std::string("aa"));
            v.push_back(make_unique<std::string>("bb"));
            v.push_back(std::unique_ptr<std::string>(new std::string("cc")));

            //Распечатайте все строки
            std::cout << "std::vector<std::unique_ptr<std::string>>: \n";
            for(const auto& i : v){
                std::cout << *i << " ";
            }
            std::cout << std::endl;

            v[1] = std::unique_ptr<std::string>(new std::string("123"));
            std::cout << "std::vector<std::unique_ptr<std::string>>: edited\n";
            for(const auto& i : v){
                std::cout << *i << " ";
            }
            std::cout << std::endl;

            //__asm nop
		 //??? Уничтожение динамически созданных объектов?
		} //???

		{//5.c - дополните задание 5.b добавьте возможность изменять хранящиеся строки
		 //следующим образом (например, добавить указанный суффикс: "AAA" -> "AAA_1")  
            std::vector<std::unique_ptr<std::string>> v;
            v.emplace_back(new std::string("aa"));
            v.push_back(make_unique<std::string>("bb"));
            v.push_back(std::unique_ptr<std::string>(new std::string("cc")));

            std::cout << "std::vector<std::unique_ptr<std::string>>: suffix\n";

            v[1] = std::unique_ptr<std::string>(new std::string(*v[1] + "_1"));
            for( auto& i : v){
                std::cout << *i << " ";
                *i += "lll";
            }
            std::cout << std::endl;

            //__asm nop
		}

		{//5.d - динамический массив объектов	

		 //Создайте unique_ptr, который является оберткой для динамического массива
		 //с элементами std::string
		 //С помощью unique_ptr::operator[] заполните обернутый массив значениями
		 //Когда происходит освобождения памяти?


            const int n = 10;
            std::unique_ptr<std::string[], std::function<void(std::string[])>> p(new std::string[n],
                    [](std::string data[]){ if(data != nullptr){delete[] data;}});


            for(int i=0; i<n; i++){
                p[i] = std::string(std::to_string(i));
            }

            std::cout << "std::unique_ptr<std::string[]>: ";
            for(int i=0; i<n; i++){
                std::cout << p[i] << " ";
            }
            std::cout << std::endl;

            //__asm nop
		}

		{//5.e - массивы динамических объектов и пользовательская delete-функция (функтор)
		 //Задан стековый массив указателей на динамически созданные объекты
		 //Создайте unique_ptr для такого массива
		 //Реализуйте пользовательскую delete-функцию (функтор) для корректного 
		 //освобождения памяти

			std::string* arStrPtr[] = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
            int n = sizeof(arStrPtr);

            std::cout << "std::unique_ptr<std::string*[], std::function<void(std::string*[])>>: \n";
            std::cout << "n: " << n << std::endl;


            if(0){

                //пока не работает - вылетает

                std::unique_ptr<std::string*[], std::function<void(std::string*[])>> p(arStrPtr,
                  [n](std::string* data[]){
                    for(int i=0; i<n; i++){
                        //delete data[i];
                    }
                });

                for(int i=0; i<n; i++){
                    std::cout << *p[i] << " ";
                }
                std::cout << std::endl;
            }
            //__asm nop
		}

		{//5.f Создайте и заполните вектор, содержащий unique_ptr для указателей на std::string
			//Посредством алгоритмя copy() скопируйте элементы вектора в пустой список с элементами 
			//того же типа
			//Подсказка: перемещающие итераторы и шаблон std::make_move_iterator

            std::vector<std::unique_ptr<std::string>> v;
            v.push_back(std::unique_ptr<std::string>(new std::string("123")));
            v.push_back(std::unique_ptr<std::string>(new std::string("456")));
            v.push_back(std::unique_ptr<std::string>(new std::string("789")));

            std::list<std::unique_ptr<std::string>> l;

            typedef  std::vector<std::unique_ptr<std::string>>::iterator vit;
            typedef  std::list<std::unique_ptr<std::string>>::iterator lit;
            std::copy(std::move_iterator<vit>(std::begin(v)),
                      std::move_iterator<vit>(std::end(v)),
                      std::inserter(l, std::begin(l)));


            std::cout << "move_iterator: \n";
            for(const auto& i : l){
                std::cout << *i << " ";
            }
            std::cout << "\n";


            //__asm nop

		}
        //__asm nop

	}

	////////////////////////////////////////////////////////////////////////////////
	//Задание 6.shared_ptr + пользовательская delete-функция 

	//Реализовать возможность записи в файл данных (строчек) из разных источников 
	//(для упрощения пусть источниками являются два массива)
	//Так как все "писатели" будут по очереди записывать свои данные в один и тот же файл,
	//логично предоставить им возможность пользоваться одним и тем же указателем FILE* =>
	//безопасной оберткой для такого указателя является shared_ptr
	//а. Первый владелец должен открыть/создать файл для записи
	//б. Все остальные писатели должны присоединиться к использованию
	//в. Последний владелец указателя должен закрыть файл

	//Подсказка: имитировать порядок записи можно с помощью функции rand()

	{
        std::cout << "----------------------- [6] ------------------------\n";

	//"писатели":
	//Создать writer1, writer2

        std::shared_ptr<FILE> writer1 = std::shared_ptr<FILE>(fopen("tmp.txt", "w"), [](FILE* f){fclose(f);});
        std::shared_ptr<FILE> writer2 = writer1;

	//например, источники данных:
	char ar1[] = "Writer1";
	char ar2[] = "Writer2";

	//заданное число итераций случайным образом позволяем одному из "писателей" записать в файл
	//свою строчку
	//Подсказка: строчки удобно записывать в файл посредством функции fputs()

    int n=10;
    for(int i=0; i<n; i++){
        srand(time(0));
        if(rand()%2){
            std::fputs(ar1, writer1.get());
        }
        else{
            std::fputs(ar2, writer2.get());
        }
    }


    //__asm nop
	}//закрытие файла???



	
}
