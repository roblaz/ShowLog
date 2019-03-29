#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString inputLine;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Log File"), "",
        tr("Log Files (*.log)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        while(!in.atEnd()) {
            inputLine = in.readLine();
            text.append(inputLine);

        }
        std::sort (text.begin(), text.end());

        for(QStringList::Iterator iS = text.begin(); iS != text.end(); ++iS)
            ui->textEdit->append(*iS);

        file.close();
    }
}
