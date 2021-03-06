#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

int main(int argc, char *argv[]) {
  QCoreApplication apps(argc, argv);

  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

  db.setHostName("localhost");
  db.setDatabaseName("testdb");
  db.setUserName("root");
  db.setPassword("sari");

  if (db.open()) {
    qDebug() << "Koneksi ke MySQL SUKSES ... ";

    QSqlQuery query;

    // INSERT data
    // QString sqlInsert = "INSERT INTO phonebook VALUES(6, 'Anu', '081000006')";
    QString sqlUpdate = "UPDATE phonebook SET nohp = '081000007' WHERE id = 1";

    if (query.exec(sqlUpdate)) {
      qDebug() << "data telah di terUPDATE kan ke database";
    } else {
      qDebug() << "yaah GAGAL update datanya";
    }

  } else {
    qDebug() << "ERROR : " + db.lastError().text();
  }
  return apps.exec();
}
