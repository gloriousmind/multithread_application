#include "widget.h"
#include "ui_widget.h"

    MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    main_layout = new QVBoxLayout(this);
    buttons_layout = new QHBoxLayout;
    data_model = new QStandardItemModel(this);
    data_view = new QTableView(this);
    main_layout->addWidget(data_view);
    main_layout->addLayout(buttons_layout);
    buttons_layout->addWidget(ui->pushButton);
    buttons_layout->addWidget(ui->pushButton_2);
    buttons_layout->addWidget(ui->pushButton_3);
    buttons_layout->addWidget(ui->pushButton_4);
    ui->pushButton_4->setEnabled(false);
    connect(ui->pushButton, &QPushButton::clicked, this, &MyWidget::connect_database);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MyWidget::disconnect_database);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MyWidget::view_display_control);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MyWidget::update_database);

}

void MyWidget::connect_database()
{
    data_view->setModel(nullptr);
    data_model->clear();
    model_row_size = 0;
    ui->pushButton_3->setText("显示数据");
    manager = new Controller(this);
    connect(manager->cur_worker, &Worker::connection_status, this, &MyWidget::handle_connection_status);
    connect(manager->cur_worker, &Worker::database_data, this, &MyWidget::handle_connection_data);
    manager->startWork();

}

void MyWidget::disconnect_database()
{
    ui->pushButton_4->setEnabled(false);
    manager->endWork();
}

void MyWidget::update_database()
{
    data_view->setModel(nullptr);
    data_model->clear();
    model_row_size = 0;
    ui->pushButton_3->setText("显示数据");
    manager->updateWork();
}

void MyWidget::view_display_control()
{
    if (ui->pushButton_3->text() == "显示数据")
    {
        data_view->setModel(data_model);
        data_view->resizeColumnsToContents();
        ui->pushButton_3->setText("隐藏显示");
    }
    else
    {
        data_view->setModel(nullptr);
        ui->pushButton_3->setText("显示数据");
    }
}

void MyWidget::handle_connection_status(bool connected)
{
    if (connected)
    {
        QMessageBox::information(this, "连接状态", "数据库连接成功!");
        ui->pushButton_4->setEnabled(true);
    }
    else
    {
        QMessageBox::information(this, "连接状态", "数据库连接失败!");
        ui->pushButton_3->setEnabled(false);
    }
}

void MyWidget::handle_connection_data(QVariantList record)
{
    data_model->insertRow(model_row_size++);
    data_view->verticalHeader()->setVisible(false);
    int column = 0;
    for (QVariant &value : record)
    {
        QStandardItem *item = new QStandardItem(value.toString());
        data_model->setItem(model_row_size - 1, column++, item);
    }
}

MyWidget::~MyWidget()
{
    delete ui;
}
