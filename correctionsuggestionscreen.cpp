#include "correctionsuggestionscreen.h"
#include "ui_correctionsuggestionscreen.h"

CorrectionSuggestionScreen::CorrectionSuggestionScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorrectionSuggestionScreen)
{
    ui->setupUi(this);

    connect(ui->homeButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // Hide CorrectionSuggestionScreen

        if (parentWidget()) {
            parentWidget()->hide();  // Hide BGScreen

            if (parentWidget()->parentWidget()) {
                parentWidget()->parentWidget()->parentWidget()->show();  // Show HomeScreen
            }
        }
    });

    connect(ui->confirmButton, &QPushButton::clicked, this, [=]() {
        emit correctionConfirmed(bgValueRaw);           // ✅ Send it exactly as-is

        this->hide();

        if (parentWidget()) {
            parentWidget()->show();  // Show BolusScreen
        }
    });

    connect(ui->cancelButton, &QPushButton::clicked, this, [=]() {
        this->hide();  // Hide this screen

        if (parentWidget()) {
            parentWidget()->show();  // Show the BGScreen again
        }
    });


}

CorrectionSuggestionScreen::~CorrectionSuggestionScreen()
{
    delete ui;
}

void CorrectionSuggestionScreen::setBG(QString bg)
{
    bgValueRaw = bg;
    ui->labelBGValue->setText(bg + " mmol/L");
}

void CorrectionSuggestionScreen::setIOB(QString iob)
{
    ui->labelIOBValue->setText(iob + " u");
}

void CorrectionSuggestionScreen::setBGMessageBasedOnValue(float bg)
{
    float target = 5.0;  // You can make this dynamic later if needed

    if (bg < target) {
        ui->labelMessage->setText("Your BG is Below Target\nReduce Bolus Calculation?");
    } else {
        ui->labelMessage->setText("Your BG is Above Target\nAdd Correction Bolus?");
    }
}
