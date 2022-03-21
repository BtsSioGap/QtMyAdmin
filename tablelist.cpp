#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QDialog>
#include <QSqlRecord>
#include "ui_mainwindow.h"
#include "mainwindow.h"

void MainWindow::afficherTable()
{
    //affichage tableau principale
    QString txtReq;
    txtReq=("SHOW TABLES");
    QSqlQuery req(txtReq);
    qDebug()<<txtReq;
    while(req.next())
    {
        ui->listWidgetTablesList->addItem(req.value(0).toString());
    }
}

void MainWindow::on_listWidgetTablesList_itemClicked(QListWidgetItem *item)
{

//PIERRE ui->tableWidgetStructure

    //requête SQL pour afficher les champs de la table selectionner
    QString txtReq= "SELECT * FROM "+ui->listWidgetTablesList->currentItem()->text();
    QSqlQuery req(txtReq);
    qDebug()<<txtReq;

    //Initialisation du tableau structure dans le tab Structure
    ui->tableWidgetStructure->setRowCount(0);
    ui->tableWidgetStructure->setColumnCount(0);
    ui->tableWidgetStructure->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //initialisation nombre de champ pour le tableau structure dans le tab Structure
    QSqlRecord recordRequest = req.record();
    int nbChamp=recordRequest.count();
    ui->tableWidgetStructure->setColumnCount(nbChamp);

    //affichage des noms de colonne pour le tableau structure dans le tab Structure
    for(int noCol=0;noCol<nbChamp;noCol++)
    {
        ui->tableWidgetStructure->setHorizontalHeaderItem(noCol,new QTableWidgetItem(recordRequest.fieldName(noCol)));
    }

    //affichage des valeurs
    int compteur= 0;
    while(req.next())
    {
        // on insère la ligne
        ui->tableWidgetStructure->setRowCount(compteur+1);
        for(int counter = 0; counter < recordRequest.count(); counter++) {
            // on affiche l'item
            ui->tableWidgetStructure->setItem(compteur,counter,new QTableWidgetItem(req.value(counter).toString()));
        }
        // on ajoute une ligne
        compteur+=1;
    }

//fin ui->tableWidgetStructure


//MELVIN ui->tableWidgetRequestInsert

    //requête SQL pour afficher les valeurs
    QString txtReqType= "SHOW FIELDS FROM "+ui->listWidgetTablesList->currentItem()->text();
    QSqlQuery reqType(txtReqType);
    qDebug()<<txtReqType;

    //affiche dans ui->tableWidgetRequestInsert pour chaque champs, le nom, le type, un QLineEdit
    int noLigne=0;
    ui->tableWidgetRequestInsert->setColumnCount(3);
    ui->tableWidgetRequestInsert->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetRequestInsert->setHorizontalHeaderItem(0, new QTableWidgetItem("Nom du champ"));
    ui->tableWidgetRequestInsert->setHorizontalHeaderItem(1, new QTableWidgetItem("Type du champ"));
    ui->tableWidgetRequestInsert->setHorizontalHeaderItem(2, new QTableWidgetItem("Valeur saisie"));

    while(reqType.next())
    {
        noLigne++;
        ui->tableWidgetRequestInsert->setRowCount(noLigne);
        ui->tableWidgetRequestInsert->setItem(noLigne-1, 0, new QTableWidgetItem(reqType.value("Field").toString()));
        ui->tableWidgetRequestInsert->setItem(noLigne-1,1, new QTableWidgetItem(reqType.value("Type").toString()));
        ui->tableWidgetRequestInsert->setCellWidget(noLigne-1,2, new QLineEdit());

    }

//fin ui->tableWidgetRequestInsert 11/03 OK


//KEVIN ui->tableWidgetDeleteEntry

    //initialisation nombre de champ par tableau
    ui->tableWidgetDeleteEntry->setColumnCount(nbChamp);

    //affichage des noms de colonne de chaque tableau
    for(int noCol=0;noCol<nbChamp;noCol++)
    {
    ui->tableWidgetDeleteEntry->setHorizontalHeaderItem(noCol,new QTableWidgetItem(recordRequest.fieldName(noCol)));
    }

    //affichage des valeurs
    int compteur2= 0;
    while(req.next())
    {
        // on insère la ligne
        ui->tableWidgetDeleteEntry->setRowCount(compteur2+1);
        for(int counter = 0; counter < recordRequest.count(); counter++) {
            // on affiche l'item
            ui->tableWidgetDeleteEntry->setItem(compteur2,counter,new QTableWidgetItem(req.value(counter).toString()));
            ui->tableWidgetDeleteEntry->setItem(counter,0,new QTableWidgetItem(" "));
        }
        // on ajoute une ligne
        compteur2+=1;
    }
//fin ui->tableWidgetDeleteEntry

}

//MELVIN bouton insertion dans la table
void MainWindow::on_pushButtonInsertExecut_clicked()
{
    //selection de tous les champs
    QString txtReqInsert= "SELECT * FROM "+ui->listWidgetTablesList->currentItem()->text();
    QSqlQuery req(txtReqInsert);
    qDebug()<<txtReqInsert;
    QSqlRecord recordRequest = req.record();
    //compte le nombre qu'il y en a
    int nbChamp=recordRequest.count();
    qDebug()<<nbChamp;

    //boucle de récupération des données
    QString resultat;
    for(int i = 0; i < nbChamp; i++)
    {
        //pour chaque line edit récupération
        QString test=((QLineEdit *)(ui->tableWidgetRequestInsert->cellWidget(i,2)))->text();
        //si donnée vide ajouter NULL
        if(test.isEmpty())
        {
            test="NULL";
            resultat+="  "+test;
        }
        //si donnée pleine ajouter 'donnée'
        else
        {
            resultat+="  '"+test+"'";
        }
    }
    //separation de la liste
    QStringList listeElement=resultat.split("  ",Qt::SkipEmptyParts);
    qDebug()<<listeElement;

    //requete insertion base de données
    QString txtRequet="INSERT INTO "+ui->listWidgetTablesList->currentItem()->text()+" VALUES (";
    txtRequet+=listeElement.join(",");
    txtRequet+=");";
    qDebug()<<txtRequet;
    QSqlQuery query;

    // on exécute la requête
    if(query.exec(txtRequet)) {
        // la requête est fonctionnelle
        ui->statusBar->showMessage("The SQL request has been executed sucessfully.",3000);
    } else {
        // la requête n'est pas fonctionnelle
        ui->statusBar->showMessage(query.lastError().text(),3000);
    }



    // requête SQL pour afficher tout les champs
    QString txtReq= "SELECT * FROM "+ui->listWidgetTablesList->currentItem()->text();
    QSqlQuery req2(txtReq);
    qDebug()<<txtReq;

    int compteur= 0;

    //initialisation nombre de champ par tableau
    QSqlRecord recordRequest2 = req2.record();
    int nbChamp2=recordRequest2.count();
    ui->tableWidgetStructure->setColumnCount(nbChamp2);

    //affichage des noms de colonne de chaque tableau
    for(int noCol=0;noCol<nbChamp2;noCol++)
    {
        ui->tableWidgetStructure->setHorizontalHeaderItem(noCol,new QTableWidgetItem(recordRequest2.fieldName(noCol)));
    }

    //affichage des valeurs
    while(req2.next())
    {
        // on insère la ligne
        ui->tableWidgetStructure->setRowCount(compteur+1);
        for(int counter = 0; counter < recordRequest2.count(); counter++) {
            // on affiche l'item
            ui->tableWidgetStructure->setItem(compteur,counter,new QTableWidgetItem(req2.value(counter).toString()));
        }
        // on ajoute une ligne
        compteur+=1;
    }
}
//fin on_pushButtonInsertExecut_clicked 04/11 OK

