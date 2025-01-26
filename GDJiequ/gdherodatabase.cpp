#include "gdherodatabase.h"
#include "ui_gdherodatabase.h"

GDHeroDatabase::GDHeroDatabase(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GDHeroDatabase)
{
    ui->setupUi(this);
    ui->frame_2->setGeometry(QRect(1077, 0, 100, 610));
    initForm();
    connect(ui->actOpen, SIGNAL(triggered()), this, SLOT(actOpenTriggered()));
    connect(ui->actAppend, SIGNAL(triggered()), this, SLOT(actAppendHeroTriggered()));
    connect(ui->actInsertHero, SIGNAL(triggered()), this, SLOT(actInsertHeroTriggered()));
    connect(ui->actDelete, SIGNAL(triggered()), this, SLOT(actDeleteHeroTriggered()));
    connect(ui->actFirstHero, SIGNAL(triggered()), this, SLOT(actFirstHeroTriggered()));
    connect(ui->actLastHero, SIGNAL(triggered()), this, SLOT(actLastHeroTriggered()));
    connect(ui->actPreviousHero, SIGNAL(triggered()), this, SLOT(actPreviousTriggered()));
    connect(ui->actNextHero, SIGNAL(triggered()), this, SLOT(actNextTriggered()));
    connect(ui->actSubmit, SIGNAL(triggered()), this, SLOT(actSubmitTriggered()));
    connect(ui->actRevert, SIGNAL(triggered()), this, SLOT(actRevertTriggered()));
    connect(ui->actLoadPhoto, SIGNAL(triggered()), this, SLOT(actLoadPhotoTriggered()));
    connect(ui->rBtnAsc, SIGNAL(clicked()), this, SLOT(rBtnAscClicked()));
    connect(ui->rBtnDes, SIGNAL(clicked()), this, SLOT(rBtnDesClicked()));
    connect(ui->comboOrderField, SIGNAL(currentIndexChanged(int)), this, SLOT(comboOrderFieldCurrentIndexChanged(int)));
    connect(ui->pBtnSearch, SIGNAL(clicked()), this, SLOT(pBtnSearchClicked()));
}

GDHeroDatabase::~GDHeroDatabase()
{
    delete ui;
}

void GDHeroDatabase::initForm()
{ // 初始化英雄表格
    this->setAttribute(Qt::WA_DeleteOnClose);
    Qt::WindowFlags flags = this->windowFlags();
    this->setWindowFlags(flags | Qt::Window);
}


void GDHeroDatabase::openTable()
{ // 打开英雄数据表
    theRelationalModel = new QSqlRelationalTableModel(this, db);
    theRelationalModel->setTable("hero");
    theRelationalModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    theRelationalModel->setSort(theRelationalModel->fieldIndex("HeroNo"), Qt::AscendingOrder);
    if(!theRelationalModel->select()) {
        QMessageBox::warning(this, "错误", "打开英雄数据表失败\n"+theRelationalModel->lastError().text());
    }
    theRelationalModel->setHeaderData(theRelationalModel->fieldIndex("HeroNo"), Qt::Horizontal, "英雄编号");
    theRelationalModel->setHeaderData(theRelationalModel->fieldIndex("HeroName"), Qt::Horizontal, "英雄名");
    theRelationalModel->setHeaderData(theRelationalModel->fieldIndex("HeroGender"), Qt::Horizontal, "性别");
    theRelationalModel->setHeaderData(theRelationalModel->fieldIndex("HeroGradient"), Qt::Horizontal, "梯度");
    theRelationalModel->setHeaderData(theRelationalModel->fieldIndex("Selectivity"), Qt::Horizontal, "选取率(%)");
    theRelationalModel->setHeaderData(theRelationalModel->fieldIndex("Successity"), Qt::Horizontal, "天选率(%)");
    theRelationalModel->setHeaderData(theRelationalModel->fieldIndex("Skin"), Qt::Horizontal, "皮肤");
    theRelationalModel->setHeaderData(theRelationalModel->fieldIndex("Skill"), Qt::Horizontal, "技能");
    theSelection = new QItemSelectionModel(theRelationalModel);
    ui->tableView->setModel(theRelationalModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers); // 不可编辑
    ui->tableView->setColumnHidden(theRelationalModel->fieldIndex("Photo"), true);
    connect(theSelection, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    connect(theSelection, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(on_currentRowChanged(QModelIndex,QModelIndex)));

    QStringList skin;
    skin << "001" << "002" << "003" << "004" << "005" << "006";
    bool isEditable = true;
    comboDelegate = new GDComboDelegate();
    comboDelegate->setItem(isEditable, skin);    
    ui->tableView->setItemDelegateForColumn(theRelationalModel->fieldIndex("Skin"), comboDelegate);
    readOnlyDelegate = new GDReadOnlyDelegate();
    ui->tableView->setItemDelegateForColumn(theRelationalModel->fieldIndex("HeroNo"), readOnlyDelegate);
    ui->tableView->setItemDelegateForColumn(theRelationalModel->fieldIndex("HeroName"), readOnlyDelegate);
    ui->tableView->setItemDelegateForColumn(theRelationalModel->fieldIndex("HeroGender"), readOnlyDelegate);
    ui->tableView->setItemDelegateForColumn(theRelationalModel->fieldIndex("HeroGradient"), readOnlyDelegate);
    ui->tableView->setItemDelegateForColumn(theRelationalModel->fieldIndex("Selectivity"), readOnlyDelegate);
    ui->tableView->setItemDelegateForColumn(theRelationalModel->fieldIndex("Successity"), readOnlyDelegate);

    dataMapper = new QDataWidgetMapper(this); // 数据模型
    dataMapper->setModel(theRelationalModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    dataMapper->addMapping(ui->lEditHeroNo, theRelationalModel->fieldIndex("HeroNo"));
    dataMapper->addMapping(ui->lEditName, theRelationalModel->fieldIndex("Heroname"));
    dataMapper->addMapping(ui->lEditGender, theRelationalModel->fieldIndex("HeroGender"));
    dataMapper->addMapping(ui->lEditGradient, theRelationalModel->fieldIndex("HeroGradient"));
    dataMapper->addMapping(ui->lEditSelect, theRelationalModel->fieldIndex("Selectivity"));
    dataMapper->addMapping(ui->lEditWin, theRelationalModel->fieldIndex("Successity"));
    dataMapper->addMapping(ui->lEditSkin, theRelationalModel->fieldIndex("Skin"));
    dataMapper->addMapping(ui->lEditSkill, theRelationalModel->fieldIndex("Skill"));
    dataMapper->addMapping(ui->pixmapInfo, theRelationalModel->fieldIndex("Photo"));
    dataMapper->toFirst();

    getFieldNames();

    ui->actOpen->setEnabled(false);
    ui->actAppend->setEnabled(false);
    ui->actDelete->setEnabled(false);
    ui->actInsertHero->setEnabled(false);
    ui->actLoadPhoto->setEnabled(false);
}

void GDHeroDatabase::refreshTableView()
{ // 刷新视图
    int index = dataMapper->currentIndex();
    QModelIndex curIndex = theRelationalModel->index(index, 1);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}

void GDHeroDatabase::getFieldNames()
{ // 得到字段名列表
    if(theRelationalModel->rowCount() == 0) {
        return;
    }
    QSqlRecord fieldList = theRelationalModel->record();
    for(int i = 0; i < fieldList.count()-1; i++) {
        ui->comboOrderField->addItem(fieldList.fieldName(i));
    }
}

void GDHeroDatabase::on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{ // 当前行发生变化
    Q_UNUSED(previous);
    dataMapper->setCurrentModelIndex(current);
    bool first = (current.row() == 0);
    bool last = (current.row() == theRelationalModel->rowCount()-1);
    ui->actFirstHero->setEnabled(!first);
    ui->actPreviousHero->setEnabled(!first);
    ui->actNextHero->setEnabled(!last);
    ui->actLastHero->setEnabled(!last);
    if(!current.isValid()) {
        ui->pixmapInfo->clear();
        return;
    }
    int curRow = current.row();
    QSqlRecord record = theRelationalModel->record(curRow);
    if(record.value("Photo").isNull()) {
        ui->pixmapInfo->clear();
    }else {
        QByteArray arrayData = record.value("Photo").toByteArray();
        QPixmap pic;
        pic.loadFromData(arrayData);
        ui->pixmapInfo->setPixmap(pic.scaledToWidth(ui->pixmapInfo->width()));
    }
}

void GDHeroDatabase::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{ // 当前项发生改变
    Q_UNUSED(current);
    Q_UNUSED(previous);
    ui->actSubmit->setEnabled(theRelationalModel->isDirty());
    ui->actRevert->setEnabled(theRelationalModel->isDirty());
}

void GDHeroDatabase::actOpenTriggered()
{ // 打开数据库
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
    db = QSqlDatabase::addDatabase("QMYSQL"); // 添加MySQL驱动
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("wgy3258642106");
    db.setDatabaseName("demo");
    if(!db.open()) {
        QMessageBox::warning(this, "错误", "打开数据库失败");
        return;
    }
    openTable();
}

void GDHeroDatabase::actAppendHeroTriggered()
{ // 添加一位新英雄
    theRelationalModel->insertRow(theRelationalModel->rowCount());
    QModelIndex curIndex = theRelationalModel->index(theRelationalModel->rowCount(), 0);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
    theRelationalModel->setData(theRelationalModel->index(curIndex.row(), 0), theRelationalModel->rowCount()+300);
}

void GDHeroDatabase::actInsertHeroTriggered()
{ // 插入一位新英雄
    QModelIndex curIndex = ui->tableView->currentIndex();
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    theRelationalModel->insertRow(curIndex.row());
}

void GDHeroDatabase::actDeleteHeroTriggered()
{ // 删除一位英雄
    QModelIndex curIndex = ui->tableView->currentIndex();
    theRelationalModel->removeRow(curIndex.row());

}

void GDHeroDatabase::actFirstHeroTriggered()
{ // 首位英雄
    dataMapper->toFirst();
    refreshTableView();
}

void GDHeroDatabase::actLastHeroTriggered()
{ // 末位英雄
    dataMapper->toLast();
    refreshTableView();
}

void GDHeroDatabase::actPreviousTriggered()
{ // 前一位英雄
    dataMapper->toPrevious();
    refreshTableView();
}

void GDHeroDatabase::actNextTriggered()
{ // 后一位英雄
    dataMapper->toNext();
    refreshTableView();
}

void GDHeroDatabase::actSubmitTriggered()
{ // 提交数据到数据库
    bool res = theRelationalModel->submitAll();
    if(!res) {
        QMessageBox::warning(this, "错误", "提交数据失败，错误信息\n"+theRelationalModel->lastError().text());
        return;
    }else {
        ui->actSubmit->setEnabled(false);
        ui->actRevert->setEnabled(false);
    }
}

void GDHeroDatabase::actRevertTriggered()
{ // 滚回数据
    theRelationalModel->revertAll();
    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
}

void GDHeroDatabase::actLoadPhotoTriggered()
{ // 加载图片
    QString photo = QFileDialog::getOpenFileName(this, "选择图片", "", "英雄图片(*.png *.jpg)");
    if(photo.isEmpty()) return;
    QFile file(photo);
    file.open(QIODevice::ReadOnly);
    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();
    QSqlRecord record = theRelationalModel->record(theSelection->currentIndex().row());
    record.setValue("Photo", byteArray);
    theRelationalModel->setRecord(theSelection->currentIndex().row(), record);
    QPixmap pic;
    pic.loadFromData(byteArray);
    ui->pixmapInfo->setPixmap(pic.scaledToWidth(ui->pixmapInfo->width()));
}

void GDHeroDatabase::rBtnAscClicked()
{ // 按字段名升序排列
    theRelationalModel->setSort(ui->comboOrderField->currentIndex(), Qt::AscendingOrder);
    theRelationalModel->select();
}

void GDHeroDatabase::rBtnDesClicked()
{ // 按字段名降序排列
    theRelationalModel->setSort(ui->comboOrderField->currentIndex(), Qt::DescendingOrder);
    theRelationalModel->select();
}

void GDHeroDatabase::comboOrderFieldCurrentIndexChanged(int index)
{ // 选择字段排序
    if(ui->rBtnAsc->isChecked()) {
        theRelationalModel->setSort(index, Qt::AscendingOrder);
        theRelationalModel->select();
    }else if (ui->rBtnDes->isChecked()) {
        theRelationalModel->setSort(index, Qt::DescendingOrder);
        theRelationalModel->select();
    }
}

void GDHeroDatabase::pBtnSearchClicked()
{ // 点击搜索按钮
    for(int i = 0; i < theRelationalModel->rowCount(); i++) {
        QString dataSet;
        QSqlRecord record = theRelationalModel->record(i);
        dataSet.append(record.value("Heroname").toString());
        dataSet.append(record.value("HeroGender").toString());
        dataSet.append(record.value("HeroGradient").toString());
        if(ui->tableView->isRowHidden(i)) {
            ui->tableView->setRowHidden(i, false);
        }
        if(!dataSet.contains(ui->lEditSearch->text())) {
            ui->tableView->setRowHidden(i, true);
        }
    }
}
