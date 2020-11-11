
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
	
	//������� 1. ����� ��������� �������� (Raw String Literals)
	//�������� ������, ��������: my name is "Marina"
	//�) ��� ������������� Raw String Literals
	//�) ����������� Raw String Literals
	//�) �������� ����������� (Delimeter)

	{
        std::cout << "----------------------- [1] ------------------------\n";
        std::cout << "My name is\"Dyadya Vasya\"" << std::endl;
        std::cout << R"(My name is "Dyadya Vasya")" << std::endl;
        std::cout << R"***(My name is "Dyadya Vasya")***" << std::endl;
        //__asm nop
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 2. ���������� ���������� ���������� � ������� constexpr-�������.
	//
	//���������/�����������: 
	//		- constexpr � ������� ������ �������� �� ������������ ���������� return <���������>; (����!)
	//		- �� ��� ��������� ����� �������� ����� ������ constexpr � �������, � ��������� �����������
	//		  ����� 
	//		- ���� �������� ����������� constexpr- ������� - ��� ���������, ���������� �������� ���������
	//		  �� ����� ����������

	//��������� ��� ����, ��� ���������� ��������� �������� �� ����� ���������� (���� � ��������
	//				��������� ������������ ���������, ��������� ����������� �� ����� ����������).
	//				��� �������� ���������� ������� ���������� ������ � ������������, �����������
	//				����������� constexpr-�������:

    {
        std::cout << "----------------------- [2] ------------------------\n";

        //��������:
        int ar[factorial(3)];
        cout << factorial(4) << endl;

		//���
        constexpr int n = factorial(5);
        int ar1[n];

		//����������:
        int m = 7;
        //constexpr int n1 = factorial(m); //error (must be constexpr)
        //int ar2[n1];
		
		//� ���?
        int n2 = factorial(m);
        //__asm nop
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 3a. ������� � ������� ����������������� �������� �� ��������� ������������� ����������
	//� ��������, ��������: ������ "100000000" -> � �������� 256
	//��������� ��������� ����������� �������� 0b
	//����� ����� ����������������� �������� �������� ������ � �������, ��������: 100000000_b
	//������� ������������ ���������������� ������� � ������������ ���������� - const char*

	//��� ��� ���� ���� � ���������, ������� ��������� �������� �� ����� ����������
	// => ���������� ���������������� ������� ����������� constexpr - �������
	//���������/�����������: 
	//		- constexpr � ������� ������ �������� �� ������������ ���������� return <���������>;
	//		- �� ��� ��������� ����� �������� ����� ������ constexpr � �������,
	//		- ������� ����� ���� ����������� (���� �������� ����� ������� - ��� ���������,
	//		  ���������� �������� ��������� ������ ����������� ������� �� ����� ����������)

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

	//������� 3b. ������� � ��������� �������� �������������, ��������: 256 -> "0b100000000"
	//��� ��� ������ ����� ���� ����� �����, �������� � ����� ���������� ������ std::string
	//=> ������������ �������� �� ����� ���� constexpr!
	//���������: ������������ std::bin ���� ��� => �������������� � �������� ������
	//�������� ������ �������
	//���������: ���������� �������� � ����� ���������� ��������� CHAR_BIT - <cstdint>

	{
        std::string sBin= 256_toBinStr;
        std::cout << "sBin: " << sBin << std::endl;
        //__asm nop
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 4�. constexpr - ������� 
	//������� ����� (������ ������?) ��� �������� � ��������������� ���������� ��������.
	//� ������ ������ ����:
	//	���������� ��� �������� ������������ � ������������� ��������,
	//	������ ��� ��������� ������� �� ��������
	//	����� ��� �������� - �������� �� ��������� �������� � ��������
	//	�����, ������� �������� ����� �������� ������� ���� � ��������� �������������� ��������:
	//							���� ����������� ���������, �� ��� � ����������
	//							���� ������ ������������ ��������, ���������� �����������
	//							���� ������ ������������� ��������, ���������� ������������

	//��������� ��� ����, ��� ���������� ��������� �������� �� ����� ����������. 
	//				��� �������� ���������� ������� ���������� ������ � ������������, �����������
	//				����������� constexpr-������:
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
	//������� 5. unique_ptr
	{
        std::cout << "----------------------- [5] ------------------------\n";

		//5.� - ���������� ���������� ���������� ���������
		{
			std::vector<std::string*> v = { new std::string("aa"), new std::string("bb"), new std::string("cc") };

            //������������ ��� ������
            for(const auto& i : v){
                std::cout << *i << " ";
            }
            std::cout << "\n";
		
            //__asm nop
			//???
		} //???

		//5.b - ������������� ������� 5.�:
		 //���������� ����������� std::unique_ptr: 
		 //����������� ���������� (��������� ��� ������ ������� ������������ std::unique_ptr), 
		 //���������� �������� ���������� �� ����������� ����������� ������� std::string, 
		 //���������������,
		 //� ������������ ��������
		 //
			
		{
            std::vector<std::unique_ptr<std::string>> v;
            v.emplace_back(new std::string("aa"));
            v.push_back(make_unique<std::string>("bb"));
            v.push_back(std::unique_ptr<std::string>(new std::string("cc")));

            //������������ ��� ������
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
		 //??? ����������� ����������� ��������� ��������?
		} //???

		{//5.c - ��������� ������� 5.b �������� ����������� �������� ���������� ������
		 //��������� ������� (��������, �������� ��������� �������: "AAA" -> "AAA_1")  
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

		{//5.d - ������������ ������ ��������	

		 //�������� unique_ptr, ������� �������� �������� ��� ������������� �������
		 //� ���������� std::string
		 //� ������� unique_ptr::operator[] ��������� ��������� ������ ����������
		 //����� ���������� ������������ ������?


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

		{//5.e - ������� ������������ �������� � ���������������� delete-������� (�������)
		 //����� �������� ������ ���������� �� ����������� ��������� �������
		 //�������� unique_ptr ��� ������ �������
		 //���������� ���������������� delete-������� (�������) ��� ����������� 
		 //������������ ������

			std::string* arStrPtr[] = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
            int n = sizeof(arStrPtr);

            std::cout << "std::unique_ptr<std::string*[], std::function<void(std::string*[])>>: \n";
            std::cout << "n: " << n << std::endl;


            if(0){

                //���� �� �������� - ��������

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

		{//5.f �������� � ��������� ������, ���������� unique_ptr ��� ���������� �� std::string
			//����������� ��������� copy() ���������� �������� ������� � ������ ������ � ���������� 
			//���� �� ����
			//���������: ������������ ��������� � ������ std::make_move_iterator

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
	//������� 6.shared_ptr + ���������������� delete-������� 

	//����������� ����������� ������ � ���� ������ (�������) �� ������ ���������� 
	//(��� ��������� ����� ����������� �������� ��� �������)
	//��� ��� ��� "��������" ����� �� ������� ���������� ���� ������ � ���� � ��� �� ����,
	//������� ������������ �� ����������� ������������ ����� � ��� �� ���������� FILE* =>
	//���������� �������� ��� ������ ��������� �������� shared_ptr
	//�. ������ �������� ������ �������/������� ���� ��� ������
	//�. ��� ��������� �������� ������ �������������� � �������������
	//�. ��������� �������� ��������� ������ ������� ����

	//���������: ����������� ������� ������ ����� � ������� ������� rand()

	{
        std::cout << "----------------------- [6] ------------------------\n";

	//"��������":
	//������� writer1, writer2

        std::shared_ptr<FILE> writer1 = std::shared_ptr<FILE>(fopen("tmp.txt", "w"), [](FILE* f){fclose(f);});
        std::shared_ptr<FILE> writer2 = writer1;

	//��������, ��������� ������:
	char ar1[] = "Writer1";
	char ar2[] = "Writer2";

	//�������� ����� �������� ��������� ������� ��������� ������ �� "���������" �������� � ����
	//���� �������
	//���������: ������� ������ ���������� � ���� ����������� ������� fputs()

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
	}//�������� �����???



	
}
