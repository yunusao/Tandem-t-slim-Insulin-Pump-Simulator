#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include <QWidget>

namespace Ui {
class OptionsScreen;
}

class OptionsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsScreen(QWidget *parent = nullptr);
    ~OptionsScreen();

private:
    Ui::OptionsScreen *ui;
};

#endif // OPTIONSSCREEN_H
