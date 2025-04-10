#include "dialogvs.h"
#include "ui_dialogvs.h"
#include "QSqlError"
#include "QMessageBox"
#include "dialogdocprint.h"

DialogVS::DialogVS(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogVS)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    dbglobal = QSqlDatabase::addDatabase("QSQLITE");

    // глобальная бд
    dbglobal.setHostName("localhost"); // хост бд
    dbglobal.setDatabaseName("mydb1"); // имя
    dbglobal.setUserName("root"); // имя user бд
    dbglobal.setPassword("mypassword"); // пароль


    bool connected = dbglobal.open();
    if (!connected) {
        QMessageBox::critical( // Диалог с сообщением об ошибке.
            parent,                      // Родительский виджет.
            QObject::tr("Database Error"),   // Заголовок.
            dbglobal.lastError().text());          // Текст сообщения.
        qDebug("no open global");
        //return false;  //Вернуть признак неудачного подключения.
    }else{
        dbglobal.open();
        qDebug("open global");
        if (dbglobal.open()){

            query = new QSqlQuery(dbglobal);
            query->exec("create table Vozr(IDArUserAr TEXT, Number TEXT, NameInstr TEXT, Prise INTEGER, UslVZ TEXT);");
            model = new QSqlTableModel(this, dbglobal);
            model->setTable("Vozr");
            model->select();

            query->exec("create table Rem(IDVozrRemAr TEXT,Number TEXT,Neispr TEXT,DataRem TEXT,Prise INTEGER);");
            modelSER = new QSqlTableModel(this, dbglobal);
            modelSER->setTable("Rem");
            modelSER->select();


            ui->tableView->setModel(model);
            ui->tableView_2->setModel(modelSER);
        } else{
            dbglobal.close();
            QSqlDatabase::removeDatabase(dbglobal.connectionName());
        }


    }
    db.setDatabaseName("./BD.db");
    // проверка локальной бд
    if (!dbglobal.open()) {
        db.open();
        qDebug("open localhost");
        if (db.open()){
            query = new QSqlQuery(db);
            query->exec("create table Vozr(IDArUserAr TEXT, Number TEXT, NameInstr TEXT, Prise INTEGER, UslVZ TEXT);");
            model = new QSqlTableModel(this, db);
            model->setTable("Vozr");
            model->select();

            query->exec("create table Rem(IDVozrRemAr TEXT,Number TEXT,Neispr TEXT,DataRem TEXT,Prise INTEGER);");
            modelSER = new QSqlTableModel(this, db);
            modelSER->setTable("Rem");
            modelSER->select();
            db.close();
            ui->tableView->setModel(model);
            ui->tableView_2->setModel(modelSER);
        }
        else {
            qDebug("no open localhost");
            db.close();
            QSqlDatabase::removeDatabase(db.connectionName());
        }
    }

}

DialogVS::~DialogVS()
{
    delete ui;
}

void DialogVS::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}


void DialogVS::on_tableView_2_clicked(const QModelIndex &index)
{
    row2 = index.row();
}


void DialogVS::on_pushButton_2_clicked()
{
    model->removeRow(row);
}


void DialogVS::on_pushButton_5_clicked()
{
    modelSER->removeRow(row2);
}


void DialogVS::on_pushButton_clicked()
{
    model->insertRow(model->rowCount());
}


void DialogVS::on_pushButton_4_clicked()
{
    modelSER->insertRow(modelSER->rowCount());
}


void DialogVS::on_pushButton_3_clicked()
{
    modelSER->select();
    model->select();
}


void DialogVS::on_pushButton_6_clicked()
{
    DialogDocPrint dialogPrint;
    //close();
    dialogPrint.setModal(true);
    dialogPrint.exec();
}

