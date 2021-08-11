#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void init_myarray(int* const ptrMyarr1, size_t  myarray_size);

void printed_myarray(int const* const ptrMyarr1, size_t myarray_size);

void initial_matrix(int** const matrix, size_t const rows, size_t const cols);

void printed_matrix(int const* const* const matrix, size_t const rows, size_t const cols);

void concatenation(string const& filename_in_1, string const& filename_in_2, string const& filename_out);

bool user_word_in_file(string const& user_word, string const& namefile);

int main()
{
    //task 1: Выделить в памяти динамический одномерный массив типа int. Размер массива запросить у пользователя. Инициализировать его числами степенями двойки: 1, 2, 4, 8, 16, 32, 64, 128 … Вывести массив на экран. Не забыть освободить память. =) Разбить программу на функции.
    {
        int* ptrMyarr1;
        int myarray_size;

        cout << "Enter size of your array, please: \n";
        cin >> myarray_size;

        if (myarray_size <= 0)
        {
            cerr << "Enter integer size for your array:\n";
            return 1;
        }

        ptrMyarr1 = new (nothrow) int[myarray_size];

        if (ptrMyarr1 != nullptr)
        {
            init_myarray(ptrMyarr1, myarray_size);
            printed_myarray(ptrMyarr1, myarray_size);

            delete[] ptrMyarr1;
            ptrMyarr1 = nullptr;
        }
        else
        {
            cerr << "The program cannot allocate memory for your array\n";
            return 1;
        }
    }

    {
        //task 2: Динамически выделить матрицу 4х4 типа int. Инициализировать ее псевдослучайными числами через функцию rand. Вывести на экран. Разбейте вашу программу на функции которые вызываются из main.

        int** matrix;
        size_t const A = 4;
        size_t const B = 4;

        matrix = new int*[A];
        for (size_t i = 0; i < A; i++)
            matrix[i] = new int[B];

        initial_matrix(matrix, A, B);
        std::cout << "This is a matrix:\n";
        printed_matrix(matrix, A, B);

        for (size_t i = 0; i < A; i++)
            delete[] matrix[i];
        delete[] matrix;
        matrix = nullptr;
    }

    //task 3: Написать программу, которая создаст два текстовых файла (*.txt), примерно по 50-100 символов в каждом (особого значения не имеет с каким именно содержимым). Имена файлов запросить у пользователя.

    {
        string filename_1;
        string filename_2;

        cout << "Enter the two names of the files that will be created:\n->";
        cin >> filename_1 >> filename_2;

        ofstream file_1("filename_1.txt");
        ofstream file_2("filename_2.txt");

        srand(time(nullptr));

        for (size_t i = 49; i < 100; i++)
        {
            file_1 << i << '\n';
        }

        for (size_t i = 49; i < 100; i++)
        {
            file_2 << rand() << '\n';
        }

        file_1.close();
        file_2.close();

        ///task 4: * Написать функцию, «склеивающую» эти файлы в третий текстовый файл (имя файлов спросить у пользователя).
        {
            string merge_files;

            cout << "Enter the name for 2 previous files for further merge it:\n->";
            cin >> merge_files;

            concatenation(filename_1, filename_2, merge_files);
        }
    }

    //task 5: * Написать программу, которая проверяет присутствует ли указанное пользователем при запуске программы слово в указанном пользователем файле (для простоты работаем только с латиницей). Используем функцию find которая есть в строках std::string.
    {
        string user_word;
        string namefile;

        cout << "Enter word for search him in file:\n->";
        cin >> user_word;

        cout << " Enter the name of the file where you want to search for this word:\n";
        cin >> namefile;

        if (user_word_in_file(user_word, namefile))
        {
                cout << "File is found! "
                << user_word
                << "in file"
                << namefile
                << '\n';
        }

        else
        {
                cout << "The program could not find the desired file "
                << user_word
                << "in file"
                << namefile
                << '\n';
        }

        return 0;
    }

}
        void init_myarray(int* const ptrMyarr1, size_t  myarray_size)
        {
        if (myarray_size > 2 << sizeof(int))
        myarray_size = 2 << sizeof(int);
        for (size_t i = 0; i < myarray_size; i++)
        ptrMyarr1[i] = 1 << i;
        }

        void printed_myarray(int const* const ptrMyarr1, size_t const myarray_size)
        {
        for (size_t i = 0; i < myarray_size; i++)
        cout << ptrMyarr1[i] << " ";
        cout << '\n';
        }

        void initial_matrix(int** const matrix, size_t const rows, size_t const cols)
        {
            srand(time(nullptr));

            for (size_t i = 0; i < rows; i++)
            {
                for (size_t j = 0; j < cols; j++)
                {
                    matrix[i][j] = rand();
                }
            }
        }

        void printed_matrix(int const* const* const matrix, size_t const rows, size_t const cols)
        {
            for (size_t i = 0; i < rows; i++) {
                for (size_t j = 0; j < cols; j++) {
                    cout << matrix[i][j] << " ";
                }
                cout << '\n';
            }
        }

        void concatenation(string const& filename_in_1, string const& filename_in_2, string const& filename_out)
        {
            string line_buf;

            ifstream file_in_1(filename_in_1);
            ifstream file_in_2(filename_in_2);
            ofstream file_out("filename_out.txt");

            if (file_in_1.is_open())
            {
                while (!file_in_1.eof())
                {
                    std::getline(file_in_1, line_buf);
                    file_out << line_buf << '\n';
                }
                file_in_1.close();
            }

            if (file_in_2.is_open()) 
            {
                while (!file_in_2.eof())
                {
                    std::getline(file_in_2, line_buf);
                    file_out << line_buf << '\n';
                }
                file_in_2.close();
            }
            file_out.close();
        }

        bool user_word_in_file(string const& user_word, string const& namefile)
        {
            string line_buf;

            ifstream file(namefile);

            if (!file.is_open()) 
            {
                cerr << "File not found\n";
                return false;
            }

            while (!file.eof())
            {
                getline(file, line_buf);

                if (line_buf.find(user_word) != string::npos)
                {
                    return true;
                }
            }

            return false;
        }