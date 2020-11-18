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
//������� 1.
	/*
	���������� ������ ������� ��� ������ ����� ������������������� (vector, list, deque, set � ����������� �������), ������� ����� ���������:
	�	��� ������� ������ ����,
	�	��� � ��������� �� ������� ������ ���� (��������� ������������� ����������� => � ���� ������ ������� �������� �������� �� ������)
	���������: if constexpr
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
//������� 2.
	/* ���������� ������ ������� �������� ���� ��������.
    ���� ������ ��������� �������� ��������, �� ��� �������� ������� ����� ��������� �� �������� ������� ���������.
    ��� ���� �������� ������� � ������ �������� ������ ���� ������ � ���� �� ����.
	���������: if constexpr, is_same
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
//������� 3.
	/* 	���������� ������ ������� ������ �� ������ �������� ��������� ������ �������� (stack, queue, priority_queue)
	���������: if constexpr, is_same
	������������� ����� ��������, ���� � �������� �������� ���������.
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
//������� 4.
	{
        std::cout << "----------------------------- [4] ----------------------------------\n";
        //��� ������ ��������� ���� string

        std::string strings[] = {"abc", "123", "qwerty", "#$%"};


		//�� ���������� ��������� ������ ������ ������������ � ������������ ����������.
		//��������� ���������� ��������������� �������� �) ��� ����������� � �) ��� ��������� �������
		//��������� � �������!
		
		//� std::set "����������" �� �������� ������� ��� �����, ������� �������� ������ ����� 


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

		//� std::vector "����������" ������� ��� �����, ������� �������� ������ ����� 
		//������� �� �����
		//������� �����
		
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
		//���� "����������" ������� ��� �����, ������� �� �������� �� �������� ����, �� �������� ����
		//� ������ �������

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
//������� 5. 
	{
        std::cout << "----------------------------- [5] ----------------------------------\n";
        //����:
        std::string ar[] = {"my", "Hello", "World"};
		std::vector < std::shared_ptr<std::string>> v = {std::make_shared<std::string>("good"), std::make_shared<std::string>("bye")};
		


		//�) ��������� �������� � ������ ������� ��� ��������� �������, �� ������� �������� �������! 

        std::transform(std::begin(ar), std::end(ar), std::back_inserter(v), [](auto& e){
            return std::shared_ptr<std::string>(new std::string(std::move(e)));
        });


		//�) ������������� ������ �� �������� � ������� �� �����
        std::sort(v.begin(), v.end());

        std::cout << "sorted: \n";
        for(const auto& i : v){
            std::cout << *i << " ";
        }
        std::cout << std::endl;

		//�) ���������� ���������� ������������ ������


        //__asm nop
	}
	/***************************************************************/
		//������� 6. shared_ptr � weak_ptr
		//������� ��������������� ������ ����������� ������ human. � ������ ��������:
		//��� - string
		//�������� �������: ��� ��� ��� ���...
		//�������� - shared_ptr (�������� �� ������ ��������...)
		//���� - ��������� �� weak_ptr (����� �������� ����������� ������������)

		//������ ������ human:
		//����������� - ��� ������������� ����� � ��������
		//����������� �����������, �������� ������������, move ???
		//����������� ����� child() - 
		//				������ ������� ������� � ������� ������� ��� ����������� ��������
		//				+ ������������ ��� ����� ������� � ���������� � ��������

		//������ ����������� ����������� ��������������� ������ ��� ���������� ����������

	{
        std::cout << "----------------------------- [6] ----------------------------------\n";

		//������� ������ � ����-�� ���������� => "����-���� ��� �� ����, ��������, ���� � ���"
		//(�� ���� �� ����� ���� ��� ���� � ��� ����):


        std::shared_ptr<Human> grandM(new Human("Eva"));
        std::shared_ptr<Human> grandF(new Human("Adam"));
        //...

		//� ��� ��������� ���� - child():
        auto f = child(grandM, grandF, "Ivan");
        auto m = child(grandM, grandF, "Masha");

		//� � ����� � ���� ������� ���� ����:
        auto c1 = child(m, f, "Vasya");
        auto c2 = child(m, f, "Natasha");

        grandF->print();

		//...
        //__asm nop
	}



//***************************************************************/
//������� 7.

	/*���������������� deduction guide � ��� ������ ����� ���������� �������
	����� ������ ������, ������� ������������� ���������� ������������ ������ ���������
	����������� � ���������� ������ ����. */
/*
template<typename T, size_t size> class MyArray
	{
		T ar[size]; //��� ���������� ������������� ��������� �������� ���� �� ��������� �����?
		�
	};
        MyArray<int, 5> ar1;//MyArray<int,5>
        MyArray ar2{"ABC"}; //MyArray<char,4>
        int ar[] = { 1,2,3 };
        MyArray ar3{ ar };

*/

//��������� ���������� ����������������� ����������� �������� �������������.
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
