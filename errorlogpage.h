#ifndef ERRORLOGPAGE_H
#define ERRORLOGPAGE_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class errorlogpage;
}

class errorlogpage : public QWidget
{
    Q_OBJECT

public:
    explicit errorlogpage(QWidget *parent = nullptr);
    ~errorlogpage();
    void loadErrors();

private slots:
    void on_backButton_clicked();

private:
    Ui::errorlogpage *ui;



};

#endif // ERRORLOGPAGE_H
