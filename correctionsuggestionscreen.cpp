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
        QString fullText = ui->labelBGValue->text();  // e.g. "4\nmmol/L"
        QString bg = fullText.split("\n").first();    // Extract just the "4"

        emit correctionConfirmed(bg);           // ✅ Send it exactly as-is

        this->hide();

        if (parentWidget()) {
            parentWidget()->show();  // Show BolusScreen
        }
    });

}

CorrectionSuggestionScreen::~CorrectionSuggestionScreen()
{
    delete ui;
}

void CorrectionSuggestionScreen::setBG(QString bg)
{
    ui->labelBGValue->setText(bg + " mmol/L");
}

void CorrectionSuggestionScreen::setIOB(QString iob)
{
    ui->labelIOBValue->setText(iob + " u");
}
