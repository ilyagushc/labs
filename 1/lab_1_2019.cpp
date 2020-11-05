//Практика 1:
// enum class
// initializer_list и универсальные списки инициализации
// auto
// decltype
// lambda 

#include "lab1.h"

#include <vector>
#include <list>
#include <set>
#include <deque>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <type_traits>
#include <iterator>
#include <string.h>
#include <cmath>


auto print = [](const auto& c) {
	for (const auto& i : c) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
};

std::string operator-(const std::string& s) {
	std::string res;
	for (const auto c : s) {
		if (c >= 'A' &&  c <= 'Z') {
			res += std::tolower(c);
			continue;
		}
		if (c >= 'a' && c <= 'z') {
			res += std::toupper(c);
			continue;
		}
		res += c;
	}
	return res;
}


int main()
{	

	std::cout << "LAB1\n";

	//Задание 1. 
	{
		std::cout << "---------- [1] ----------\n";
		enum class months :uint8_t { January, February, March/*...*/ };
		enum class weekDays :uint8_t { Monday, Tuesday /*...*/ };

		months m = months::January;
		//а) уберите проблемы (это значит, что КОМПИЛЯТОР не
		//должен позволять программисту осуществлять опасные
		//сравнения!)

		//if (m == months::Monday) { /*...*/ }
		if (m == months::January) { /*...*/ }

		//б) оптимизируйте использование памяти
		months year[] = { months::January, months::February, months::March };
		size_t n = sizeof(year); //???
		std::cout << "sizeof(year): " << n << std::endl;

        //__asm nop
	}


/**********************************************************/
	//Задание 2. Создайте и с помощью списка инициализации
	//заполните значениями вектор с элементами - string
	//С помощью range-based for преобразуйте все буквы в 	
	//верхний регистр а остальные символы должны остаться
	//неизменными
	{
		std::cout << "---------- [2] ----------\n";

		std::vector <std::string> v{"abc", "ABC", "aBc"};
		auto print = [](const auto& v) {
			for (const auto& i : v) {
				std::cout << i << " ";
			}
			std::cout << std::endl;
		};

		print(v);

		for (auto& str : v) {
			for (auto& ch : str) {
				ch = std::toupper(ch);
			}
		}
		std::cout << "to upper: \n";
		print(v);

        //__asm nop
	}


/**********************************************************/
	///Задание 3. Создайте и заполните значениями
	//map таким образом, чтобы он содержал в качестве ключа
	//букву, а в качестве значения отсортированную по 
	//алфавиту совокупность слов (string), начинающихся с
	//этой буквы
	
	//3а. Проинициализируйте map "вручную" посредством списка инициализации
	//С помощью range-based for и structured binding
 	//распечатайте содержимое, например: A: any, apple, away
	{
		std::cout << "---------- [3a] ----------\n";

		std::map<char, std::set<std::string>> map{
			{'A', {"any", "apple",  "away"}},
			{'B', {"black", "back", "bad", "bed"}},
			{'C', {"cat", "clock"}}
		};

		for (const auto& [key, val] : map) {
			std::cout << key << ": ";
			for (const auto& v : val) {
				std::cout << v << ",";
			}
			std::cout << "\b " << std::endl;
		}


        //__asm nop
	}

	//3б. Создайте пустой map и используйте заданный массив
	//для выполнения задания.
	//С помощью range-based for и structured binding
	//распечатайте содержимое, например: A: any, apple, away
	{
		std::cout << "---------- [3b] ----------\n";

		//дано (например):
		const char* s[] = { "yong", "away", "bar", "any", "son", "apple" };
		std::map<char, std::set<std::string>> map;
		for (const auto& i : s) {
			if (!strlen(i)) {
				continue;
			}
			map[i[0]].insert(i);
		}
		for (const auto& [key, val] : map) {
			std::cout << key << ": ";
			for (const auto& v : val) {
				std::cout << v << ",";
			}
			std::cout << "\b " << std::endl;
		}


        //__asm nop
	}


/*********************************************************/
	//Задание 4. создать функцию для вывода на печать
	//элементов последовательностей, заданных ниже:
	{
		std::cout << "---------- [4] ----------\n";

		auto PrintAnyCont = [](const auto& c) {
			for (const auto& i : c) {
				std::cout << i << " ";
			}
			std::cout << std::endl;
		};


		std::vector<double> vd = { 1.1,2.2,3.3 };
		PrintAnyCont(vd);

		std::list<double> list = { 1.1,2.2,3.3 };
		PrintAnyCont(list);

		std::string s("abc");
		PrintAnyCont(s);
				
		int ar[] = { 1, 2, 3 };
		PrintAnyCont(ar);

		std::initializer_list<int> il{ 3,4,5 };
		PrintAnyCont(il);		

        //__asm nop
	}


/********************************************************/
	///Задание 5. 	
	//Cоздать функцию для "отрицания" значений, например:
	//было: {1, -2, 5}, стало: {-1, 2, -5})
	//изменение объектов типа std::string может выглядеть "aBc1" -> "AbC1"
	//элементов последовательностей, заданных ниже:
	{
		std::cout << "---------- [5] ----------\n";

		auto NegateAll = [](auto& c) mutable {
			for (auto& i : c) {
				i = -i;
			}
		};

		
		std::vector<double> vd{ 1.1,2.2,3.3 };
		print(vd);
		NegateAll(vd);
		print(vd);

		std::list<std::string> ls{ "aBc", "Qwerty", "n12" };
		print(ls);
		NegateAll(ls);
		print(ls);

		int ar[]{ 1, -2, 3 };
		print(ar);
		NegateAll(ar);
		print(ar);
		
        //__asm nop

	}

	
/********************************************************/
	//Задание 6. Реализовать функцию сортировки по модулю
	//элементов последовательностей, заданных ниже
	//Собственно для сортировки можно использовать обобщенный
	//алгоритм sort(), а для задания условия - лямбда-функцию
	{
		std::cout << "---------- [6] ----------\n";

		auto absSort = [](auto& c) {
			std::sort(std::begin(c), std::end(c), [](auto& e1, auto& e2) {
				return abs(e1) < abs(e2);
			});
		};

		std::vector<double> vd = { -3.3,  2.2, -1.1 };
		print(vd);
		absSort(vd);
		print(vd);


		int ar[] = { -3, 2, -1 };
		print(ar);
		absSort(ar);
		print(ar);

        //__asm nop
	}


/********************************************************/
	//Задание 7.
	//Напишите функцию, которая будет формировать и
	//возвращать вектор, каждый элемент 
	//которого является суммой элементов двух 
	//последовательностей РАЗНОЙ длины
	//и с элементами РАЗНОГО типа.

	//Подсказка 1: так как последовательности могут быть
	//разной длины, логично сделать размер результирующего
	//вектора максимальным из двух
	 
	//Подсказка 2: подумайте о возможности использования
	//алгоритмов copy() и transform(), в котором 
	//трансформирующее действие удобно в свою очередь
	//задавать лямбда-функцией

	//например:
	{

		std::cout << "---------- [7] ----------\n";

        auto SumCont0 = [](const auto& c1, const auto& c2)
        {
            std::vector<decltype (*std::begin(c1)+ *std::begin(c2))> res;
            int n1 = std::size(c1), n2 = std::size(c2);
            if (n1 < n2) {
                std::transform(std::begin(c1), std::end(c1), std::begin(c2), std::back_inserter(res), [](const auto& i1, const auto& i2) {
                    return i1 + i2;
                    });
                auto it = std::begin(c2);
                std::advance(it, std::size(c1));
                std::copy(it, std::end(c2), std::back_inserter(res));
                return res;
            }
            else {
                std::transform(std::begin(c2), std::end(c2), std::begin(c1), std::back_inserter(res), [](const auto& i1, const auto& i2) {
                    return i1 + i2;
                    });
                auto it = std::begin(c1);
                std::advance(it, std::size(c2));
                std::copy(it, std::end(c1), std::back_inserter(res));
                return res;
            }
        };





		std::vector<int> v{ 1,2,3,4 };
		std::list<double> l{ 1.1, 2.2, 3.3, 4.4, 5.5 };


        auto sum = SumCont0(v, l);
        std::cout << "C1: ";
        print(v);
        std::cout << "C2: ";
        print(l);
        std::cout << "Sum: ";
        print(sum);

		

		std::list<int> ll{ 1, 2, 3, 4, 5, 6, 7, 8 };
		double ar[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };


        auto sum2 = SumCont0(ar, ll);
        std::cout << "C1: ";
        print(ll);
        std::cout << "C2: ";
        print(ar);
        std::cout << "Sum: ";
        print(sum2);



		std::set<std::string> s{ "abc", "qwerty", "my"};
		std::deque<const char*> d{ "111", "22" };
        auto sum3 = SumCont0(s, d);
		std::cout << "C1: ";
		print(s);
		std::cout << "C2: ";
		print(d);
		std::cout << "Sum: ";
		print(sum3);

        //__asm nop
	}


/********************************************************/	
	//Задание 8. Реализуйте функцию, которая принимает следующие параметры:	
	//сформированную последовательность любого типа с элементами любого типа, 
	//два (пустых) контейнера любого типа из vector, list, deque, set 
	//с элементами того же типа, что и у сформированной последовательности 

	//Функция должна "разложить" значения заданной последовательности в два пустых контейнера 
	//согласно заданному условию. Условие задать лябда-функцией
	//Исходная последовательность при этом не меняется
	{
		std::cout << "---------- [8] ----------\n";

		//Например:
		std::vector<int> v{ 1,2,3,4,5 };
		std::list<int> l; //сюда четные
		std::deque<int> d; //а сюда нечетные


        auto Separate = [](const auto& c1, auto& c2, auto& c3, auto func){
            auto ins2 = std::insert_iterator(c2, std::begin(c2));
            auto ins3 = std::insert_iterator(c3, std::begin(c3));
            for(const auto& i : c1){
                if(func(i)){
                    ins2 = i;
                }
                else{
                    ins3 = i;
                }
            }
        };


        Separate(v, l, d, [](const auto& e){return !std::fmod(e, 2);});
        std::cout << "v: ";
        print(v);
        std::cout << "l: ";
        print(l);
        std::cout << "d: ";
        print(d);




        //__asm nop
	}


/********************************************************/
	//Задание 9. C помощью алгоритма for_each()!!! 
	//(а не count_if()) посчитать сколько букв в верхнем
	//регистре.
	//  Использовать лямбда функцию
	{
		std::cout << "---------- [9] ----------\n";

		char s[] = "Hello World!";
        int cnt{0};
        std::for_each(std::begin(s), std::end(s), [&cnt](const auto& e){
            if(e >= 'A' && e <= 'Z'){
                cnt++;
            }
        });
        std::cout << "cnt: " << cnt;

		
        //__asm nop
	}


/********************************************************/
	//Задание 10. Реализовать конвертацию enum в строковое представление  - enumToString
	// и наоборот - stringToEnum

	std::cout << "---------- [10] ----------\n";

	//Подсказки: 
	//***********
	//1. Соответствующие именованным константам строки все равно нужно где-то хранить =>
	//1.1 Именованные константы в перечислении должны быть уникальными => соответствующие строки
	//тоже должны быть уникальными, => уникальные строки могут быть использованы в качестве
	//ключа в std::map
	
	//1.2 а вот значения (соответствующие именованым константам)
	//могут быть любыми и даже могут повторяться (упрощаем задачу, считая, что значения НЕ повторяются) 
	//=> подходит контейнер std::map<string,<значение> >
	
	//1.3 Согласно стандарту С++11 переменные перечислимого типа могут быть разного размера и типа,
	//а хотелось бы обеспечить универсальную конвертацию 
	
	//***********
	//2. Так как типы перечислений разные, то enumToString и stringToEnum должны быть шаблонными
	//2.1 Пользователь может ошибиться или злонамеренно передать в функции значения, которым
	//   ничего не соответствует => защита!
	//2.2 В функциях enumToString и stringToEnum (в зависимости от типа перечисления) нужно будет
	//   анализировать соответствующий используемому типу перечисления контейнер
	
	//***********
	//3. Чтобы действия с map<string, <значение> > не зависили от типа перечисления, логично реализовать "обертку":
/*
template<typename T> struct EnumMap
{
	static std::map<std::string, T> m_eMap;
	static const auto& getMap() { return m_eMap; }
};
*/

	//***********

	{
	//Например:
/*
		COLORS c1;
		try {
			c1 = stringToEnum<COLORS>("blue");
		}
		catch (...)
		{
		//...
		}

	
		auto Str = enumToString(c1);
*/

        //__asm nop
	}

	return 0;
}
