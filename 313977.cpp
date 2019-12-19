#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

template <typename TT>
class Matrix
{
private:
    int row, column;
    TT **matrix;

public:
    Matrix()
    {
        this->row = 10;
        this->column = 10;
        this->matrix = new TT *[10];
        for (int i = 0; i < 10; i++)
        {
            this->matrix[i] = new TT[10];
            for (int j = 0; j < column; j++)
            {
                this->matrix[i][j] = 0;
            }
        }
    }
    Matrix(int row, int column, TT value)
    {
        this->row = row;
        this->column = column;
        this->matrix = new TT *[row];
        for (int i = 0; i < row; i++)
        {
            this->matrix[i] = new TT[column];
            for (int j = 0; j < column; j++)
            {
                this->matrix[i][j] = value;
            }
        }
    }
    Matrix(int row, int column, char type)
    {
        this->row = row;
        this->column = column;
        if (type == 'e')
        {
            this->matrix = new TT *[row];
            for (int i = 0; i < row; i++)
            {
                this->matrix[i] = new TT[column];
                for (int j = 0; j < column; j++)
                {
                    this->matrix[i][j] = (i == j ? 1 : 0);
                }
            }
        }
        else if (type == 'r')
        {
            this->matrix = new TT *[row];
            for (int i = 0; i < row; i++)
            {
                this->matrix[i] = new TT[column];
                for (int j = 0; j < column; j++)
                {
                    this->matrix[i][j] = rand() % 256;
                }
            }
        }
    }
    ~Matrix()
    {
        for (int i = 0; i < this->row; i++)
        {
            delete this->matrix[i];
        }
        delete this->matrix;
    }
    void resize(int row, int column)
    {
        TT **temp = new TT *[row];
        for (int i = 0; i < row; i++)
        {
            temp[i] = new TT[column];
        }

        if (this->row < row && this->column < column)
        {
        }
        else
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    temp[i][j] = this->matrix[i][j];
                }
            }
        }
        this->~Matrix();
        this->row = row;
        this->column = column;
        this->matrix = new TT *[row];
        for (int i = 0; i < row; i++)
        {
            this->matrix[i] = new TT[column];
            for (int j = 0; j < column; j++)
            {
                this->matrix[i][j] = temp[i][j];
            }
        }
        for (int i = 0; i < this->row; i++)
        {
            delete[] temp[i];
        }
        delete[] temp;
    }
    void Print()
    {
        cout << endl;
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->column; j++)
            {
                cout << this->matrix[i][j] << (j == this->column - 1 ? "" : " - ");
            }
            cout << endl;
        }
    }

    void Print(string dosya)
    {
        ofstream dosyayaz("file.txt");
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->column; j++)
            {
                dosyayaz << this->matrix[i][j] << (j == this->column - 1 ? "" : " - ");
            }
            dosyayaz << endl;
        }
        dosyayaz.close();
    }
    int getValue(int i, int j)
    {
        return this->matrix[i][j];
    }
    void addValue(int r, int c, TT val)
    {
        this->matrix[r][c] = val;
    }
    void T()
    {
        cout << endl;
        TT **temp = new TT *[column];
        for (int i = 0; i < column; i++)
        {
            temp[i] = new TT[row];
        }
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->column; j++)
            {
                temp[j][i] = matrix[i][j];
            }
        }
        for (int i = 0; i < this->column; i++)
        {
            for (int j = 0; j < this->row; j++)
            {
                cout << temp[i][j] << (j == this->row - 1 ? "" : " - ");
            }
            cout << endl;
        }
    }
    Matrix<TT> &operator+(const Matrix<TT> &m2)
    {
        Matrix<TT> *temp = new Matrix<TT>(m2.row, m2.column, 0);
        temp->row = m2.row;
        temp->column = m2.column;
        for (int i = 0; i < m2.row; i++)
        {
            for (int j = 0; j < m2.column; j++)
            {
                temp->matrix[i][j] = this->matrix[i][j] + m2.matrix[i][j];
            }
        }
        return *temp;
    }
    Matrix<TT> &operator-(const Matrix<TT> &m3)
    {
        Matrix<TT> *temp = new Matrix<TT>(m3.row, m3.column, 0);
        temp->row = m3.row;
        temp->column = m3.column;

        for (int i = 0; i < m3.row; i++)
        {
            for (int j = 0; j < m3.column; j++)
            {
                temp->matrix[i][j] = this->matrix[i][j] - m3.matrix[i][j];
            }
        }
        return *temp;
    }
    Matrix<TT> &operator*(const Matrix<TT> &m4)
    {
        Matrix<TT> *temp = new Matrix<TT>(this->row, m4.column, 0);
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < m4.column; j++)
            {
                for (int k = 0; k < this->column; k++)
                {
                    temp->matrix[i][j] += this->matrix[i][k] * m4.matrix[k][j];
                }
            }
        }
        return *temp;
    }

    Matrix<TT> &operator+(TT num)
    {
        Matrix<TT> *temp = new Matrix<TT>(this->row, this->column, 0);
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->column; j++)
            {
                temp->matrix[i][j] = this->matrix[i][j] + num;
            }
        }

        return *temp;
    }
    Matrix<TT> &operator-(TT num)
    {
        Matrix<TT> *temp = new Matrix<TT>(this->row, this->column, 0);
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->column; j++)
            {
                temp->matrix[i][j] = this->matrix[i][j] - num;
            }
        }

        return *temp;
    }
    Matrix<TT> &operator*(TT num)
    {
        Matrix<TT> *temp = new Matrix<TT>(this->row, this->column, 0);
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->column; j++)
            {
                temp->matrix[i][j] = this->matrix[i][j] * num;
            }
        }

        return *temp;
    }
    Matrix<TT> &operator/(TT num)
    {
        Matrix<TT> *temp = new Matrix<TT>(this->row, this->column, 0);
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->column; j++)
            {
                temp->matrix[i][j] = this->matrix[i][j] / num;
            }
        }

        return *temp;
    }
    Matrix<TT> &operator%(TT num)
    {
        Matrix<TT> *temp = new Matrix<TT>(this->row, this->column, 0);
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->column; j++)
            {
                temp->matrix[i][j] = this->matrix[i][j] % num;
            }
        }

        return *temp;
    }
    Matrix<TT> &operator^(TT num)
    {
        Matrix<TT> *temp = new Matrix<TT>(this->row, this->column, 0);
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->column; j++)
            {
                temp->matrix[i][j] = 1;
            }
        }

        for (int k = 0; k < num; k++)
        {

            for (int i = 0; i < this->row; i++)
            {
                for (int j = 0; j < this->column; j++)
                {
                    temp->matrix[i][j] = temp->matrix[i][j] * this->matrix[i][j];
                }
            }
        }

        return *temp;
    }
    int determinant(Matrix<TT> *matrix, int n)
    {
        int det = 0;
        int x = 0;
        int subi = 0;
        int subj = 0;
        Matrix<TT> *submatrix = new Matrix<TT>(n - 1, n - 1, 0);
        if (n == 2) //2x2'lik matris determinanti
            det = ((matrix->matrix[0][0] * matrix->matrix[1][1]) - (matrix->matrix[1][0] * matrix->matrix[0][1]));
        else if (n == 3) //3x3'lük matris determinantı
            det = ((matrix->matrix[0][0] * matrix->matrix[1][1] * matrix->matrix[2][2] + matrix->matrix[0][1] * matrix->matrix[1][2] * matrix->matrix[2][0] + matrix->matrix[0][2] * matrix->matrix[1][0] * matrix->matrix[2][1]) - (matrix->matrix[2][0] * matrix->matrix[1][1] * matrix->matrix[0][2] + matrix->matrix[2][1] * matrix->matrix[1][2] * matrix->matrix[0][0] + matrix->matrix[2][2] * matrix->matrix[1][0] * matrix->matrix[0][1]));
        else if (matrix->row == matrix->column)
        {
            for (int i = 0; i < n; i++) //Toplam aij*det(Aij) dedigimiz i. satir.
            {
                for (int j = 0; j < n; j++) //Matrisler arası işlem için j. sütun
                {
                    for (int k = 0; k < n; k++) //Matrisler arası işlem için k. satır
                    {
                        if (j == x)
                            continue;
                        else if (k == i)
                            continue;
                        else
                        {
                            if (j != 0)
                                subj = j - 1;
                            else
                                subj = 0;
                            if (k < i)
                                subi = k;
                            else if (k > i)
                                subi = k - 1;
                            submatrix->matrix[subi][subj] = matrix->matrix[k][j];
                        }
                    }
                }
                subi = 0;
                subj = 0;
                submatrix->Print();
                //int iaa=determinant(submatrix, n - 1);
                det = det + (pow(-1, i) * matrix->matrix[i][0] * determinant(submatrix, n - 1));
            }
        }
        else
        {
            cout << "Matrisin satir ve sutun sayilari esit olmalidir." << endl;
            return -1;
        }
        cout << "det: " << det << endl;
        return det;
    }
    void InverseOfMAtris()
    {
        /*TT** temp = new TT * [row];
		for (int i = 0; i < row; i++)
		{
			temp[i] = new TT[column];
		}*/
        float **temp = new float *[this->column];
        for (int i = 0; i < column; i++)
        {
            temp[i] = new float[row];
        }
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->column; j++)
            {
                if (i == j)
                {
                    temp[i][j] = 1;
                }
                else
                {
                    temp[i][j] = 0;
                }
            }
        }
        //birim matrisi yazdır.
        cout << endl
             << "Birim matris:\n";
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->column; j++)
            {
                cout << temp[i][j] << (j == this->column - 1 ? "" : " \t ");
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
        float d = 0.0, k = 0.0;
        for (int i = 0; i < this->row; i++)
        {
            d = (float)matrix[i][i];
            for (int j = 0; j < this->column; j++)
            {
                matrix[i][j] = matrix[i][j] / d;
                //(float)this->matrix[i][j] = (float)matrix[i][j] / (float)d;
                temp[i][j] = (float)temp[i][j] / (float)d;
            }
            for (int x = 0; x < this->row; x++)
            {
                if (x != i)
                {
                    k = (float)matrix[x][i];
                    for (int j = 0; j < this->column; j++)
                    {
                        matrix[x][j] = matrix[x][j] - (matrix[i][j] * k);
                        temp[x][j] = temp[x][j] - (temp[i][j] * k);
                    }
                }
            }
        }
        cout << endl
             << "Matrisin tersi:" << endl;
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->column; j++)
            {
                cout << temp[i][j] << (j == this->column - 1 ? "" : " \t ");
            }
            cout << endl;
        }
    }
};

template <typename TT>
class Table : public Matrix<TT>
{
private:
    string *row = new string[10];
    string *col = new string[10];
    int rowCount, colCount;
    Matrix<int> *tableMatrix = new Matrix<int>(10, 10, 0);

public:
    Table()
    {
        string row2[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        string col2[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
        for (int i = 0; i < 10; i++)
        {
            row[i] = row2[i];
            col[i] = col2[i];
        }
        rowCount = 10;
        colCount = 10;
        tableMatrix->resize(10, 10);
    }

    Table(int r, int c, int d)
    {
        string row2[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        string col2[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
        for (int i = 0; i < 10; i++)
        {
            row[i] = row2[i];
            col[i] = col2[i];
        }
        rowCount = r;
        colCount = c;
        tableMatrix->resize(r, c);
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                tableMatrix->addValue(i, j, d);
            }
        }
    }

    Table(int r, int c, char ch)
    {
        string row2[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        string col2[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
        for (int i = 0; i < 10; i++)
        {
            row[i] = row2[i];
            col[i] = col2[i];
        }
        rowCount = r;
        colCount = c;
        if (ch == 'r')
        {
            Matrix<int> *newM = new Matrix<int>(r, c, ch);
            tableMatrix->resize(r, c);
            for (int i = 0; i < r; i++)
            {
                for (int j = 0; j < c; j++)
                {
                    tableMatrix->addValue(i, j, newM->getValue(i, j));
                }
            }
        }
    }

    TT itemAt(int r, int c)
    {
        return tableMatrix->getValue(r, c);
    }


    TT itemAt(string rs, string cs)
    {
        int r = 0, c = 0;
        for (int i = 0; i < rowCount; i++)
        {
            if (rs == row[i])
            {
                r = i;
            }
        }
        for (int i = 0; i < colCount; i++)
        {
            if (cs == col[i])
            {
                c = i;
            }
        }
        return tableMatrix->getValue(r, c);
    }
    void setRowNames(string s[], int n)
    {
        row->resize(n);
        for (int i = 0; i < n; i++)
        {
            row[i] = s[i];
        }
    }
    void setColNames(string s[], int n)
    {
        col->resize(n);
        for (int i = 0; i < n; i++)
        {
            col[i] = s[i];
        }
    }
    void PrintTable()
    {
        cout << "\t";
        for (int i = 0; i < colCount; i++)
        {
            cout << col[i] << "\t";
        }
        cout << endl;
        for (int i = 0; i < rowCount; i++)
        {
            cout << row[i] << "\t";
            for (int j = 0; j < colCount; j++)
            {
                cout << tableMatrix->getValue(i, j) << "\t";
            }
            cout << endl;
        }
    }
};

int main()
{
    srand(time(NULL));
    int allChoise = 0;
    while (allChoise != 3)
    {
        cout << "Matris islemleri icin 1'e basin." << endl;
        cout << "Table islemleri icin 2'ye basin." << endl;
        cout << "Cikmak icin 3'e basin." << endl;
        cin >> allChoise;
        if (allChoise == 1)
        {
            int request;
            int row, row2;
            int column, column2;
            char letter;
            int num;
            Matrix<int> *firstMatrix;
            Matrix<int> *secondMatrix;
            Matrix<int> *resultMatrix;

            cout << "1. matris islemleri:" << endl;
            cout << "standart matris icin 1'i" << endl;
            cout << "istenilen boyutta matris icin 2'yi" << endl;
            cin >> request;
            if (request == 1)
            {
                firstMatrix = new Matrix<int>();
                firstMatrix->Print();
            }
            else if (request == 2)
            {
                cout << "matrisin sutununu giriniz : ";
                cin >> row;
                cout << "matrisin satirini giriniz : ";
                cin >> column;

                while (isdigit(row) != 0 && isdigit(column) != 0 && row < 0 && column < 0)
                {
                    cout << "hatali tuslama " << endl;
                    cout << "matrisin satirini giriniz : ";
                    cin >> row;
                    cout << "matrisin sutununu giriniz : ";
                    cin >> column;
                }
                cout << "ozel matrisler icin 1, istenilen sayi icin 2" << endl;
                cin >> request;
                if (request == 1)
                {
                    cout << "birim matris icin 1, random sayili matris icin 2" << endl;
                    cin >> request;
                    while (request != 1 && request != 2)
                    {
                        cout << "yanlis tuslama" << endl;
                        cout << "birim matris icin 1, random sayili matris icin 2" << endl;
                        cin >> request;
                    }
                    if (request == 2)
                    {
                        firstMatrix = new Matrix<int>(row, column, 'r');
                        firstMatrix->Print();
                    }
                    else if (request == 1)
                    {
                        while (row != column)
                        {
                            cout << "satir ve sutun esit degil.tekrar satir ve sutun giriniz." << endl;
                            cin >> row;
                            cin >> column;
                        }
                        firstMatrix = new Matrix<int>(row, column, 'e');
                        firstMatrix->Print();
                    }
                }
                else if (request == 2)
                {
                    cout << "matrisinizi doldurmak istediginiz sayiyi giriniz : ";
                    cin >> num;
                    while (isdigit(num) != 0)
                    {
                        cout << "sayi giriniz : ";
                        cout << "matrisinizi doldurmak istediginiz sayiyi giriniz : ";
                        cin >> num;
                    }
                    firstMatrix = new Matrix<int>(row, column, num);
                    firstMatrix->Print();
                }
            }
            cout << "matris olustu" << endl;
            cout << "matris olusturup yeniden boyutlandirmak icin 1'i,ekrana yazdirmak icin 2'i, matrisi dosyaya yazdirmak icin 3'u  ";
            cout << "matrisin transpozu icin 4,iki matrisle islem yapmak icin 5'i." << endl;
            cin >> request;
            while (request != 1 && request != 2 && request != 3 && request != 4 && request != 5 && request != 6)
            {
                cout << "hatali giris :" << endl;
                cin >> request;
            }
            if (request == 1)
            {
                cout << "sutun ve satiri giriniz: ";
                cin >> row;
                cin >> column;
                while (isdigit(row) != 0 && isdigit(column) != 0 && row < 0 && column < 0)
                {
                    cout << "hatali giris" << endl;
                    cin >> row;
                    cin >> column;
                }
                firstMatrix->resize(row, column);
                firstMatrix->Print();
            }
            else if (request == 2)
            {
                firstMatrix->Print();
            }
            else if (request == 3)
            {
                firstMatrix->Print("file.txt");
            }
            else if (request == 4)
            {
                firstMatrix->T();
                firstMatrix->Print();
            }
            else if (request == 5)
            {
                cout << "";
            }
            //2. matris islemleri
            cout << "2. matris islemleri:" << endl;
            cout<<"NOT: 2 matrisi toplamak ve cikarmak istiyorsaniz boyutlari esit olmali"<<endl;
            cout<<"matris carpmasi yapmak istiyorsaniz 1. matrisin satir boyutuyla 3. matrisin sutun boyutu esit olmali."<<endl;
            cout << "standart matris icin 1'i" << endl;
            cout << "istenilen boyutta matris icin 2'yi" << endl;
            cin >> request;
            if (request == 1)
            {
                secondMatrix = new Matrix<int>();
                secondMatrix->Print();
            }
            else if (request == 2)
            {
                cout << "matrisin sutununu giriniz : ";
                cin >> row2;
                cout << "matrisin satirini giriniz : ";
                cin >> column2;
                cout << "ozel matrisler icin 1, istenilen sayi icin 2" << endl;
                cin >> request;
                while (isdigit(row2) != 0 && isdigit(column2) != 0 && row2 < 0 && column2 < 0)
                {
                    cout << "hatali tuslama " << endl;
                    cout << "matrisin satirini giriniz : ";
                    cin >> row2;
                    cout << "matrisin sutununu giriniz : ";
                    cin >> column2;
                }

                if (request == 1)
                {
                    cout << "birim matris icin 1, random sayili matris icin 2" << endl;
                    cin >> request;
                    while (request != 1 && request != 2)
                    {
                        cout << "yanlis tuslama tekrar tuslayın" << endl;
                        cout << "birim matris icin 1, random sayili matris icin 2" << endl;
                        cin >> request;
                    }
                    if (request == 2)
                    {
                        secondMatrix = new Matrix<int>(row2, column2, 'r');
                        secondMatrix->Print();
                    }
                    else if (request == 1)
                    {
                        secondMatrix = new Matrix<int>(row2, column2, 'e');
                        secondMatrix->Print();
                    }
                }
                else if (request == 2)
                {
                    cout << "matrisinizi doldurmak istediginiz sayiyi giriniz : ";
                    cin >> num;
                    while (isdigit(num) != 0)
                    {
                        cout << "sayi giriniz : ";
                        cout << "matrisinizi doldurmak istediginiz sayiyi giriniz : ";
                        cin >> num;
                    }
                    secondMatrix = new Matrix<int>(row2, column2, num);
                    secondMatrix->Print();
                }
            }
            cout << "matris olustu" << endl;
            cout << "matris olusturup yeniden boyutlandirmak icin 1'i,ekrana yazdirmak icin 2'i, matrisi dosyaya yazdirmak icin 3'u  ";
            cout << "matrisin transpozu icin 4,iki matrisle islem yapmak icin 5'i." << endl;
            cin >> request;
            while (request != 1 && request != 2 && request != 3 && request != 4 && request != 5 && request != 6)
            {
                cout << "hatali giris :" << endl;
                cin >> request;
            }
            if (request == 1)
            {
                cout << "sutun ve satiri giriniz: ";
                cin >> row2;
                cin >> column2;
                while (isdigit(row) != 0 && isdigit(column) != 0 && row < 0 && column < 0)
                {
                    cout << "hatali giris" << endl;
                    cin >> row2;
                    cin >> column2;
                }
                secondMatrix->resize(row2, column2);
                secondMatrix->Print();
            }
            else if (request == 2)
            {
                secondMatrix->Print();
            }
            else if (request == 3)
            {
                secondMatrix->Print("file.txt");
            }
            else if (request == 4)
            {
                secondMatrix->T();
            }
            else if (request == 5)
            {
                cout << "";
            }

            cout << "Operator islemleri:" << endl;
            cout << "1. matris: " << endl;
            firstMatrix->Print();
            cout << endl
                 << "2. matris: " << endl;
            secondMatrix->Print();

            cout << endl
                 << endl;
            cout << "Skaler islemler icin 1, matrisler arasi islemler icin 2." << endl;
            int choice;
            cin >> choice;
            while (choice != 1 && choice != 2)
            {
                cout << "yanlis tuslama" << endl;
                cout << "Skaler islemler icin 1, matrisler arasi islemler icin 2." << endl;
                cin >> choice;
            }
            if (choice == 1)
            {
                int scalerNum = 0;

                cout << "Toplama icin 1, cikarma icin 2, carpma icin 3, bolme icin 4, mod alma icin 5, us alma icin 6." << endl;
                int ChoiceScaler = 0;
                //z = new Matrix<int>(row,column2,0);
                cin >> ChoiceScaler;
                while (ChoiceScaler != 1 && ChoiceScaler != 2 && ChoiceScaler != 3 && ChoiceScaler != 4 && ChoiceScaler != 5 && ChoiceScaler != 6)
                {
                    cout << "yanlis tuslama" << endl;
                    cout << "Toplama icin 1, cikarma icin 2, carpma icin 3, bolme icin 4, mod alma icin 5, us alma icin 6." << endl;
                    cin >> ChoiceScaler;
                }
                cout << "Skaler islem yapmak istediginiz sayıyı girin.";
                cout << "Sayı: ";
                cin >> scalerNum;
                if (ChoiceScaler == 1)
                {
                    *firstMatrix = *firstMatrix + scalerNum;
                    firstMatrix->Print();
                }

                else if (ChoiceScaler == 2)
                {
                    *firstMatrix = *firstMatrix - scalerNum;
                    firstMatrix->Print();
                }

                else if (ChoiceScaler == 3)
                {
                    *firstMatrix = *firstMatrix * scalerNum;
                    firstMatrix->Print();
                }
                else if (ChoiceScaler == 4)
                {

                    *firstMatrix = *firstMatrix / scalerNum;
                    firstMatrix->Print();
                }
                else if (ChoiceScaler == 5)
                {
                    *firstMatrix = *firstMatrix % scalerNum;
                    firstMatrix->Print();
                }
                else if (ChoiceScaler == 6)
                {
                    *firstMatrix = *firstMatrix ^ scalerNum;
                    firstMatrix->Print();
                }

            }

                else if (choice == 2)
                {
                    int choiceMatrix = 0;
                    cout << "Toplama icin 1, Cikarma icin 2, Carpma icin 3 giriniz. Matris tersi ve determinant icin 4'u girin." << endl;
                    cin >> choiceMatrix;
                    resultMatrix = new Matrix<int>(row, column2, 0);
                    while (choiceMatrix != 1 && choiceMatrix != 2 && choiceMatrix != 3 && choiceMatrix != 4)
                    {
                        cout << "yanlis tuslama" << endl;
                        cout << "Toplama icin 1, Cikarma icin 2, Carpma icin 3 giriniz. Matris tersi ve determinant icin 4'u girin." << endl;
                        cin >> choiceMatrix;
                    }
                    if (choiceMatrix == 1 && choiceMatrix == 2)
                    {
                                            
                            cout << "2 matrisi toplamak ve cikarmak icin matris boyutlari esit olmali." << endl;
                        
                    }
                    if (choiceMatrix == 1)
                    {
                        *resultMatrix = *firstMatrix + *secondMatrix;
                        resultMatrix->Print();
                    }
                    else if (choiceMatrix == 2)
                    {
                        *resultMatrix = *firstMatrix - *secondMatrix;
                        resultMatrix->Print();
                    }
                    else if (choiceMatrix == 3)
                    {
                        *resultMatrix = *firstMatrix * *secondMatrix;
                        resultMatrix->Print();
                    }
                    else if (choiceMatrix == 4)
                    {
                        cout << "Matris: " << endl;
                        firstMatrix->Print();
                        int sec = 0;
                        cout << endl
                             << "Matrisin tersi icin 1, determinanti icin 2";
                        cin >> sec;
                        while (sec != 1 && sec != 2)
                        {
                            cout << "yanlis tuslama" << endl;
                            cout << endl
                                 << "Matrisin tersi icin 1, determinanti icin 2";
                            cin >> sec;
                        }
                        if (sec == 1)
                        {
                            firstMatrix->InverseOfMAtris();
                            cout << "Matris tersi:" << endl;
                            firstMatrix->Print();
                        }
                        else if (sec == 2)
                        {
                            firstMatrix->determinant(firstMatrix, row);
                            cout << "Matris determinanti:" << endl;
                            firstMatrix->Print();
                        }
                    }
                }
        }
        else if (allChoise == 2)
        {
            int choice = 0;
            while (choice != 9)
            {
                cout << endl
                     << endl;
                cout << "Lutfen yapmak istediginiz islemi seciniz." << endl;
                cout << "Default table olusturmak icin 1'e basin." << endl;
                cout << "d degerine sahip rxc boyutlu table olusturmak icin 2'ye basın." << endl;
                cout << "rxc boyutlu random table olusturmak icin 3'e basın." << endl;
                cout << "Cikmak icin 9'a basın." << endl;
                cout << "Giris: ";
                cin >> choice;
                while (choice != 1 && choice != 2 && choice != 3 && choice != 9)
                {
                    cout << "yanlis tuslama" << endl;
                    cout << "Lutfen yapmak istediginiz islemi seciniz." << endl;
                    cout << "Default table olusturmak icin 1'e basin." << endl;
                    cout << "d degerine sahip rxc boyutlu table olusturmak icin 2'ye basın." << endl;
                    cout << "rxc boyutlu random table olusturmak icin 3'e basın." << endl;
                    cout << "Cikmak icin 9'a basın." << endl;
                    cout << "Giris: ";
                    cin >> choice;
                }
                if (choice == 1)
                {
                    Table<int> *mTable = new Table<int>();
                    int choice2 = 0;
                    while (choice2 != 9)
                    {
                        cout << endl;
                        cout << "[r,c] indisindeki degeri dondurmek icin 1'e basin." << endl;
                        cout << "satir ve sutundaki degeri dondurmek icin 2'ye basın." << endl;
                        cout << "Satir isimlerini guncellemek icin 3'e basın." << endl;
                        cout << "Sutun isimlerini guncellemek icin 4'e basın." << endl;
                        cout << "Tabloyu yazdirmak icin 5'e basın." << endl;
                        cout << "Cikmak icin 9'a basin." << endl;
                        cout << "Giris: ";
                        cin >> choice2;

                        while (choice2 != 1 && choice2 != 2 && choice2 != 3 && choice2 != 4 && choice2 != 5 && choice2 != 9)
                        {
                            cout << "yanlis tuslama " << endl;
                            cout << "[r,c] indisindeki degeri dondurmek icin 1'e basin." << endl;
                            cout << "satir ve sutundaki degeri dondurmek icin 2'ye basın." << endl;
                            cout << "Satir isimlerini guncellemek icin 3'e basın." << endl;
                            cout << "Sutun isimlerini guncellemek icin 4'e basın." << endl;
                            cout << "Tabloyu yazdirmak icin 5'e basın." << endl;
                            cout << "Cikmak icin 9'a basin." << endl;
                            cout << "Giris: ";
                            cin >> choice2;
                        }

                        if (choice2 == 1)
                        {
                            int r, c;
                            cout << "Satir: ";
                            cin >> r;
                            cout << "Sutun: ";
                            cin >> c;
                            int sonuc = mTable->itemAt(r, c);
                            cout << "Deger: " << sonuc << endl;
                        }
                        else if (choice2 == 2)
                        {
                            string rs, cs;
                            cout << "Satir ismi giriniz: " << endl;
                            cin >> rs;
                            cout << "Sutun ismi giriniz: " << endl;
                            cin >> cs;
                            int sonuc = mTable->itemAt(rs, cs);
                        }
                        else if (choice2 == 3)
                        {
                            int n;
                            cout << "Guncel dizi sayisini giriniz.";
                            cin >> n;
                            string *s = new string[n];
                            cout << "Satır isimlerini giriniz." << endl;
                            for (int i = 0; i < n; i++)
                            {
                                cout << i << ". eleman: ";
                                cin >> s[i];
                            }
                            mTable->setRowNames(s, n);
                        }
                        else if (choice2 == 4)
                        {
                            int n;
                            cout << "Guncel dizi sayisini giriniz.";
                            cin >> n;
                            string *s = new string[n];
                            cout << "Sutun isimlerini giriniz." << endl;
                            for (int i = 0; i < n; i++)
                            {
                                cout << i << ". eleman: ";
                                cin >> s[i];
                            }
                            mTable->setColNames(s, n);
                        }
                        else if (choice2 == 5)
                        {
                            mTable->PrintTable();
                        }
                        else if (choice2 != 9)
                            cout << "Yanlis secim yapildi." << endl;
                    }
                }
                else if (choice == 2)
                {
                    int r = 0;
                    int c = 0;
                    int d = 0;
                    cout << "Lutfen satir, sutun ve eleman degerlerini giriniz." << endl;
                    cout << "Satir: ";
                    cin >> r;
                    cout << "sutun: ";
                    cin >> c;
                    cout << "Deger: ";
                    cin >> d;
                    Table<int> *mTable = new Table<int>(r, c, d);
                    int choice2 = 0;
                    while (choice2 != 9)
                    {
                        cout << endl;
                        cout << "[r,c] indisindeki degeri dondurmek icin 1'e basin." << endl;
                        cout << "satir ve sutundaki degeri dondurmek icin 2'ye basın." << endl;
                        cout << "Satir isimlerini guncellemek icin 3'e basın." << endl;
                        cout << "Sutun isimlerini guncellemek icin 4'e basın." << endl;
                        cout << "Tabloyu yazdirmak icin 5'e basın." << endl;
                        cout << "Cikmak icin 9'a basin." << endl;
                        cout << "Giris: ";
                        cin >> choice2;
                        if (choice2 == 1)
                        {
                            int r, c;
                            cout << "Satır: ";
                            cin >> r;
                            cout << "Sutun: ";
                            cin >> c;
                            int result = mTable->itemAt(r, c);
                            cout << "Deger: " << result << endl;
                        }
                        else if (choice2 == 2)
                        {
                            string rs, cs;
                            cout << "Satir ismi giriniz: " << endl;
                            cin >> rs;
                            cout << "Sutun ismi giriniz: " << endl;
                            cin >> cs;
                            int result = mTable->itemAt(rs, cs);
                        }
                        else if (choice2 == 3)
                        {
                            int n;
                            cout << "Guncel dizi sayisini giriniz.";
                            cin >> n;
                            string *s = new string[n];
                            cout << "Satir isimlerini giriniz." << endl;
                            for (int i = 0; i < n; i++)
                            {
                                cout << i << ". eleman: ";
                                cin >> s[i];
                            }
                            mTable->setRowNames(s, n);
                        }
                        else if (choice2 == 4)
                        {
                            int n;
                            cout << "Guncel dizi sayisini giriniz.";
                            cin >> n;
                            string *s = new string[n];
                            cout << "Sutun isimlerini giriniz." << endl;
                            for (int i = 0; i < n; i++)
                            {
                                cout << i << ". eleman: ";
                                cin >> s[i];
                            }
                            mTable->setColNames(s, n);
                        }
                        else if (choice2 == 5)
                        {
                            mTable->PrintTable();
                        }
                        else if (choice2 != 9)
                            cout << "Yanlis secim yapildi." << endl;
                    }
                }
                else if (choice == 3)
                {
                    int r = 0;
                    int c = 0;
                    cout << "Lutfen satir, sutun ve eleman degerlerini giriniz." << endl;
                    cout << "Satir: ";
                    cin >> r;
                    cout << "Sutun: ";
                    cin >> c;
                    Table<int> *mTable = new Table<int>(r, c, 'r');
                    int choice2 = 0;
                    while (choice2 != 9)
                    {
                        cout << endl;
                        cout << "[r,c] indisindeki degeri dondurmek icin 1'e basin." << endl;
                        cout << "satir ve sutundaki degeri dondurmek icin 2'ye basın." << endl;
                        cout << "Satir isimlerini guncellemek icin 3'e basın." << endl;
                        cout << "Sutun isimlerini guncellemek icin 4'e basın." << endl;
                        cout << "Tabloyu yazdirmak icin 5'e basın." << endl;
                        cout << "Cikmak icin 9'a basin." << endl;
                        cout << "Giris: ";
                        cin >> choice2;
                        if (choice2 == 1)
                        {
                            int r, c;
                            cout << "Satir: ";
                            cin >> r;
                            cout << "Sutun: ";
                            cin >> c;
                            int result = mTable->itemAt(r, c);
                            cout << "Deger: " << result << endl;
                        }
                        else if (choice2 == 2)
                        {
                            string rs, cs;
                            cout << "Satir ismi giriniz: " << endl;
                            cin >> rs;
                            cout << "Sutun ismi giriniz: " << endl;
                            cin >> cs;
                            int result = mTable->itemAt(rs, cs);
                        }
                        else if (choice2 == 3)
                        {
                            int n;
                            cout << "Guncel dizi sayisini giriniz.";
                            cin >> n;
                            string *s = new string[n];
                            cout << "Satir isimlerini giriniz." << endl;
                            for (int i = 0; i < n; i++)
                            {
                                cout << i << ". eleman: ";
                                cin >> s[i];
                            }
                            mTable->setRowNames(s, n);
                        }
                        else if (choice2 == 4)
                        {
                            int n;
                            cout << "Guncel dizi sayisini giriniz.";
                            cin >> n;
                            string *s = new string[n];
                            cout << "Sutun isimlerini giriniz." << endl;
                            for (int i = 0; i < n; i++)
                            {
                                cout << i << ". eleman: ";
                                cin >> s[i];
                            }
                            mTable->setColNames(s, n);
                        }
                        else if (choice2 == 5)
                        {
                            mTable->PrintTable();
                        }
                        else if (choice2 != 9)
                            cout << "Yanlis secim yapildi." << endl;
                    }
                }
                else if (choice != 9)
                    cout << "Yanlis giris yaptiniz." << endl;
            }
        }
        else if (allChoise != 3)
            cout << "Yanlis secim yapildi." << endl;
    }
}
