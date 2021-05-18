#ifndef DIALOG_H
#define DIALOG_H

#include "QDialog"
#include "QRegularExpressionValidator"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_GenMap_clicked();
    void on_pushButton_Solve_clicked();

private:
    Ui::Dialog *ui;
    QValidator *cellValidator;

    void generateXCellsForGridLayout(int N, int M);
    void mapGridLayoutClear();
    void mapGridLayoutAddCell(QString text, int i, int j);
};
#endif // DIALOG_H
