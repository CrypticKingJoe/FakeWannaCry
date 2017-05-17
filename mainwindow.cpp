#include "mainwindow.h"
#include <QDateTime>
#include <QGridLayout>
#include <QLayout>
#include <QImage>
#include <QPainter>
#include <QSettings>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Load svg
    Image = new QSvgWidget(":/WanaCrypt0r.svg");
    DiscountProgress = new QSvgWidget(":/progress.svg");
    MoneyLostProgress = new QSvgWidget(":/progress.svg");
    BTCIcon = new QSvgWidget(":/bitcoinAccept.svg");
    // UI
    QSettings *Settings = new QSettings;
    Settings->beginGroup("FakeWannCry");
    Discount = new QFrame;
    PaymentRaised = new QLabel;
    PaymentRaised->setStyleSheet("color: yellow");
    PaymentRaised->setText((!Settings->value("PaymentRasied").isNull()) ? Settings->value("PaymentRasied").toString() : "Payment will be raised on:");
    uint Toworrow;
    // Get or Set timestamp
    if (!Settings->value("DiscountExpired").isNull()) {
        Toworrow = Settings->value("DiscountExpired").toUInt();
    } else {
        Toworrow = QDateTime::currentDateTime().addDays(1).toTime_t();
        Settings->setValue("DiscountExpired", QVariant(Toworrow));
    }
    DiscountTimeLeft = new QLabel;
    DiscountTimeLeft->setStyleSheet("color: white");
    DiscountTimeLeft->setText(QDateTime::fromTime_t(Toworrow).toString("M/d/yyyy hh:mm:ss") + "\nTime Left");
    DiscountTime = new QLCDNumber(Discount);
    DiscountTime->setDigitCount(12);
    DiscountProgress = new QSvgWidget(":/progress.svg");
    MoneyLost = new QFrame;
    YourFilesLost = new QLabel;
    YourFilesLost->setStyleSheet("color: yellow");
    YourFilesLost->setText((!Settings->value("YourFilesLost").isNull()) ? Settings->value("YourFilesLost").toString() : "Your files will be lost on:");
    uint Days;
    // Get or Set timestamp
    if (!Settings->value("MoneyLostExpired").isNull()) {
        Days = Settings->value("MoneyLostExpired").toUInt();
    } else {
        Days = QDateTime::currentDateTime().addDays(3).toTime_t();
        Settings->setValue("MoneyLostExpired", QVariant(Days));
    }
    MoneyLostTimeLeft = new QLabel;
    MoneyLostTimeLeft->setStyleSheet("color: white");
    MoneyLostTimeLeft->setText(QDateTime::fromTime_t(Days).toString("M/d/yyyy hh:mm:ss") + "\nTime Left");
    MoneyLostTime = new QLCDNumber(MoneyLost);
    MoneyLostTime->setDigitCount(12);
    MoneyLostProgress = new QSvgWidget(":/progress.svg");
    MoneyLostProgress->setMaximumSize(210, 80);
    Oops = new QLabel;
    Oops->setStyleSheet("color: white; font-weight: bold");
    Oops->setText((!Settings->value("Oops").isNull()) ? Settings->value("Oops").toString() : "Oops, Your files have been encrypted!");
    Send = new QLabel;
    Send->setText((!Settings->value("Send").isNull()) ? Settings->value("Send").toString() : "Send $300 worth of bitcoin to this address:");
    Language = new QComboBox;
    Language->setStyleSheet("background: white");
    Language->addItem("Chinese");
    Language->addItem("English");
    Text = new QTextEdit;
    Text->setReadOnly(true);
    Text->setStyleSheet("background: white");
    Text->setText((!Settings->value("Text").isNull()) ? Settings->value("Text").toString() : "");
    BTCAddress = new QLabel;
    BTCAddress->setText("");
    Copy = new QPushButton;
    Copy->setText("Copy");
    CheckPayment = new QPushButton;
    CheckPayment->setText((!Settings->value("CheckPayment").isNull()) ? Settings->value("CheckPayment").toString() : "Check Payment");
    Decrypt = new QPushButton;
    Decrypt->setText((!Settings->value("Decrypt").isNull()) ? Settings->value("Decrypt").toString() : "Decrypt");
    AboutBTC = new QLabel;
    AboutBTC->setOpenExternalLinks(true);
    AboutBTC->setText("<a href='https://bitcoin.org/en/' style='color: white'>About bitcoin</a>");
    HowToBuyBTC = new QLabel;
    HowToBuyBTC->setOpenExternalLinks(true);
    HowToBuyBTC->setText("<a href='https://bitcoin.org/en/exchanges' style='color: white'>How to buy bitcoin?</a>");
    ContactUs = new QLabel;
    ContactUs->setOpenExternalLinks(true);
    ContactUs->setText("<strong><a href='https://github.com/iVanilla/FakeWannaCry' style='color: white'>Contcat Us</a></strong>");
    Settings->endGroup();
    // Layout
    QGridLayout *DiscountLayout = new QGridLayout;
    DiscountLayout->addWidget(PaymentRaised, 0, 1);
    DiscountLayout->addWidget(DiscountTimeLeft, 1, 1);
    DiscountLayout->addWidget(DiscountTime, 2, 1);
    DiscountLayout->addWidget(DiscountProgress, 1, 2);
    Discount->setLayout(DiscountLayout);
    QGridLayout *MoneyLostLayout = new QGridLayout;
    MoneyLostLayout->addWidget(YourFilesLost, 0, 1);
    MoneyLostLayout->addWidget(MoneyLostTimeLeft, 1, 1);
    MoneyLostLayout->addWidget(MoneyLostTime, 2, 1);
    MoneyLostLayout->addWidget(MoneyLostProgress, 1, 2);
    MoneyLost->setLayout(MoneyLostLayout);
    QVBoxLayout *LinkLayout = new QVBoxLayout;
    LinkLayout->addWidget(AboutBTC);
    LinkLayout->addWidget(HowToBuyBTC);
    LinkLayout->addWidget(ContactUs);
    QVBoxLayout *LeftLayout = new QVBoxLayout;
    LeftLayout->addWidget(Image);
    LeftLayout->addWidget(Discount);
    LeftLayout->addWidget(MoneyLost);
    LeftLayout->addLayout(LinkLayout);
    QHBoxLayout *TopLayout = new QHBoxLayout;
    TopLayout->addWidget(Oops);
    TopLayout->addWidget(Language);
    QGridLayout *BottomLayout = new QGridLayout;
    BottomLayout->addWidget(BTCIcon, 0, 1);
    BottomLayout->addWidget(Send, 0, 2);
    BottomLayout->addWidget(BTCAddress, 1, 2);
    BottomLayout->addWidget(CheckPayment, 2, 1);
    BottomLayout->addWidget(Decrypt, 2, 2);
    QVBoxLayout *RightLayout = new QVBoxLayout;
    RightLayout->addLayout(TopLayout);
    RightLayout->addWidget(Text);
    RightLayout->addLayout(BottomLayout);
    QHBoxLayout *MainLayout = new QHBoxLayout;
    MainLayout->addLayout(LeftLayout);
    MainLayout->addLayout(RightLayout);
    QWidget *MainWidget = new QWidget;
    MainWidget->setLayout(MainLayout);
    // Window settings
    setWindowTitle("Wanna Decrypt0r 3.0");
    setStyleSheet("background: #A20000");
    setMinimumSize(640, 480);
    setCentralWidget(MainWidget);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint&  ~Qt::WindowMinimizeButtonHint);
    // Stat timer
    Timer = new QTimer;
    // Connect singals to slots
    connect(Timer, SIGNAL(timeout()), this, SLOT(ShowTime()));
    Timer->start(1000);
    ShowTime();
}

void MainWindow::Resize(QResizeEvent *event)
{

}

void MainWindow::ShowTime()
{
    QSettings *Settings = new QSettings;
    Settings->beginGroup("FakeWannaCry");
    // Get toworrow time
    uint Seconds = Settings->value("DiscountExpired").toUInt() - QDateTime::currentDateTime().toTime_t();
    QString Elapsed = QDateTime::fromTime_t(Seconds).toString("dd:hh:mm:ss");
    qDebug("exp = %i", Seconds);
    DiscountTime->display(Elapsed);
    // Get days time
    Seconds = Settings->value("MoneyLostExpired").toUInt() - QDateTime::currentDateTime().toTime_t();
    Elapsed = QDateTime::fromTime_t(Seconds).toString("dd:hh:mm:ss");
    qDebug("exp2 = %i", Seconds);
    MoneyLostTime->display(Elapsed);
    Settings->endGroup();
}
