#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLabel>
#include "controller.h"
#include <QBoxLayout>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QDateTime>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private slots:
    void connect_database();
    void disconnect_database();
    void update_database();
    void handle_connection_status(bool connected);
    void handle_connection_data(QVariantList record);
    void view_display_control();

private:
    Ui::Widget *ui;
    Controller *manager;
    QVBoxLayout *main_layout;
    QHBoxLayout *buttons_layout;
    QTableView *data_view;
    QStandardItemModel *data_model;
    int model_row_size = 0;
};
#endif // MYWIDGET_H
