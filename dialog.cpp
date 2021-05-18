#include "dialog.h"
#include "ui_dialog.h"
#include "QHBoxLayout"
#include "QRegularExpressionValidator"
#include "QRegularExpression"
#include "QLineEdit"
#include "Dijkstra.cpp"
#include "unordered_set"
using namespace std;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QRegularExpression intRegEx("[1-9]\\d{0,3}");
    QValidator *intValidator = new QRegularExpressionValidator(intRegEx, this);
    ui->lineEdit_Min->setValidator(intValidator);
    ui->lineEdit_Max->setValidator(intValidator);
    ui->lineEdit_XFreq->setValidator(intValidator);

    QRegularExpression cellRegEx("[1-9X-X]\\d{0,3}w{0,1}");
    cellValidator = new QRegularExpressionValidator(cellRegEx, this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_GenMap_clicked()
{
    mapGridLayoutClear();

    int N = stoi(ui->lineEdit_N->text().toStdString());
    int M = stoi(ui->lineEdit_M->text().toStdString());
    int min = stoi(ui->lineEdit_Min->text().toStdString());
    int max = stoi(ui->lineEdit_Max->text().toStdString());

    if(ui->checkBox_IsRandomFill->isChecked())
    {
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<M; j++)
            {
                int random = min + (rand() % static_cast<int>(max - min + 1));
                mapGridLayoutAddCell(QString::number(random), i, j);
            }
        }
        generateXCellsForGridLayout(N, M);
    }
    else
    {
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<M; j++)
            {
                mapGridLayoutAddCell("1", i, j);
            }
        }
    }
}

void Dialog::mapGridLayoutClear()
{
    QLayoutItem* cell;
    while ((cell = ui->mapGridLayout->takeAt(0)) != NULL)
    {
        delete cell->widget();
        delete cell;
    }
}

void Dialog::mapGridLayoutAddCell(QString text, int i, int j)
{
    QLineEdit *le = new QLineEdit(text);
    le->setValidator(cellValidator);
    // addWidget(*Widget, row, column, rowspan, colspan)
    ui->mapGridLayout->addWidget(le, i, j, 1, 1);
}

void Dialog::generateXCellsForGridLayout(int N, int M)
{
    unordered_set<int> XLocations;
    int minXLocation = 2;
    int maxXLocation = N*M-1;
    int xFreq = stoi(ui->lineEdit_XFreq->text().toStdString());
    int desiredSize = N*M/xFreq;
    do
    {
        int randomLocation = minXLocation + (rand() % static_cast<int>(maxXLocation - minXLocation + 1));
        XLocations.insert(randomLocation);
    }
    while(XLocations.size() != desiredSize);
    for (int XLocation: XLocations)
    {
        int i = XLocation % M == 0 ? XLocation / M - 1 : XLocation / M;
        int j = XLocation % M == 0 ? M - 1 : XLocation - M * (XLocation / M) - 1;
        QLineEdit *currentCell = ((QLineEdit*)ui->mapGridLayout->itemAtPosition(i,j)->widget());
        currentCell->setText("X");
    }
}

void Dialog::on_pushButton_Solve_clicked()
{
    int N = stoi(ui->lineEdit_N->text().toStdString());
    int M = stoi(ui->lineEdit_M->text().toStdString());

    string **map = new string*[N];
    for(int i=0; i<N; i++)
    {
        map[i] = new string[M];
        for(int j=0; j<M; j++)
        {
            QLineEdit *currentCell = ((QLineEdit*)ui->mapGridLayout->itemAtPosition(i,j)->widget());
            *(map[i] + j) = currentCell->text().toStdString();
        }
    }
    CalculateRoverPath(map, N, M, ui);
}
