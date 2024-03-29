#include "Apartment_Manager_Qt.h"


Apartment_Manager_Qt::Apartment_Manager_Qt(Service& sv, QWidget *parent): QMainWindow(parent), serv{ sv }
{
	setWindowIcon(QIcon(":/Apartment_Manager_Qt/Resources/ap.png"));
	ui.setupUi(this);
	init_gui_comps();
	//reload_list(sv.get_all());
	connect_signals_slots();
}

void Apartment_Manager_Qt::init_gui_comps()
{
	table_list->setModel(mod);
	table_list->show();
	this->setWindowTitle("Manager for the apartments");
	cos_wnd = new QWidget();
	cos_wnd->setAttribute(Qt::WA_QuitOnClose, false);
	cos_wnd->setWindowTitle("List of apartments");
	QVBoxLayout *l1 = new QVBoxLayout();
	QHBoxLayout *l2 = new QHBoxLayout();
	QWidget *cos_w = new QWidget();
	cos = new QListWidget();
	cos_wnd->setLayout(l1);
	QWidget *bt1 = new QWidget();
	bt1->setLayout(l2);
	goleste_cos = new QPushButton("Empty list");
	save_cos = new QPushButton("Save list to CSV");
	l2->addWidget(goleste_cos);
	l2->addWidget(save_cos);
	l1->addWidget(cos);
	l1->addWidget(bt1);


	filterz_wnd = new QWidget();
	filterz_wnd->setAttribute(Qt::WA_QuitOnClose, false);
	filterz_wnd->setWindowTitle("Filtered list");
	QVBoxLayout *li3 = new QVBoxLayout();
	filterz_wnd->setLayout(li3);
	filterz_list = new QListWidget();
	li3->addWidget(filterz_list);
	filterz_wnd->setWindowModality(Qt::ApplicationModal);




	types_wnd = new QWidget();
	types_wnd->setAttribute(Qt::WA_QuitOnClose, false);
	types_wnd->setWindowTitle("Filtered list");
	QVBoxLayout *l3 = new QVBoxLayout();
	types_wnd->setLayout(l3);
	types_list = new QListWidget();
	l3->addWidget(types_list);
	types_wnd->setWindowModality(Qt::ApplicationModal);



	QWidget *wnd = new QWidget();
	this->setCentralWidget(wnd);
	QHBoxLayout *hLay = new QHBoxLayout();
	QVBoxLayout *vLay = new QVBoxLayout();
	QWidget* detalii = new QWidget();
	QFormLayout *detalii_ly = new QFormLayout();
	detalii->setLayout(detalii_ly);
	QWidget *input = new QWidget();
	QWidget *add_update = new QWidget();
	QWidget *filterz = new QWidget();
	input_nume = new QLineEdit();
	input_ap = new QLineEdit();
	input_tip = new QLineEdit();
	input_supraf = new QLineEdit();


	detalii_ly->addRow("Nume:", input_nume);
	detalii_ly->addRow("Ap:", input_ap);
	detalii_ly->addRow("Tip:", input_tip);
	detalii_ly->addRow("Supraf:", input_supraf);

	QHBoxLayout *add_update_l = new QHBoxLayout();
	add = new QPushButton("Add");
	update = new QPushButton("Update");
	add_update_l->addWidget(add);
	add_update_l->addWidget(update);
	QHBoxLayout *filterz_l = new QHBoxLayout();
	filtrare_tip = new QPushButton("FilterByType");
	filtrare_supraf = new QPushButton("FilterBySurfaceArea");
	QWidget *undo_cos = new QWidget();
	QHBoxLayout *undo_cos_l = new QHBoxLayout();
	undo_cos->setLayout(undo_cos_l);
	undo = new QPushButton("Undo");
	all_types = new QPushButton("Show all types");
	show_cos = new QPushButton("Show apartment list");
	show_rdonly = new QPushButton("Show readonly apartment list");
	undo_cos_l->addWidget(undo);
	undo_cos_l->addWidget(all_types);
	undo_cos_l->addWidget(show_cos);
	filterz_l->addWidget(filtrare_tip);
	filterz_l->addWidget(filtrare_supraf);
	QWidget *random_cos = new QWidget();
	QHBoxLayout *random_l = new QHBoxLayout();
	random = new QPushButton("Add random apts to the list");
	random_l->addStretch();
	random_l->addWidget(show_rdonly);
	random_l->addWidget(random);
	random_cos->setLayout(random_l);
	add_update->setLayout(add_update_l);
	filterz->setLayout(filterz_l);
	vLay->addWidget(detalii);
	vLay->addWidget(add_update);
	vLay->addWidget(filterz);
	vLay->addWidget(random_cos);
	vLay->addWidget(undo_cos);
	vLay->addStretch();
	input->setLayout(vLay);
	QWidget *lista = new QWidget();
	QVBoxLayout *vLay2 = new QVBoxLayout();
	//list = new QListWidget();
	list = new QTableWidget();
	//list->setSelectionBehavior(QAbstractItemView::SelectRows);
	//vLay2->addWidget(list);
	table_list->setSelectionBehavior(QAbstractItemView::SelectRows);
	vLay2->addWidget(table_list);
	QHBoxLayout *hLay2 = new QHBoxLayout();
	remove = new QPushButton("Remove");
	remove->setEnabled(false);
	sort_name = new QPushButton("SortByName");
	sort_supraf = new QPushButton("SortBySurface");
	sort_type = new QPushButton("SortByType");
	add_cos = new QPushButton("Add to apt list");
	add_cos->setEnabled(false);
	QWidget *butoane = new QWidget();
	butoane->setLayout(hLay2);
	vLay2->addWidget(butoane);
	hLay2->addWidget(remove);
	hLay2->addWidget(sort_name);
	hLay2->addWidget(sort_supraf);
	hLay2->addWidget(sort_type);
	hLay2->addWidget(add_cos);
	lista->setLayout(vLay2);
	hLay->addWidget(lista);
	hLay->addStretch();
	hLay->addWidget(input);
	wnd->setLayout(hLay);
}

void Apartment_Manager_Qt::reload_list(std::vector<Locatar> l)
{
	mod->timerTikTak(l);
}

void Apartment_Manager_Qt::reload_cos(std::vector<Locatar> l)
{
	cos->clear();
	for (auto& x : l) {
		QListWidgetItem* it = new QListWidgetItem(QString::number(x.get_apartament()), cos);
		it->setData(Qt::UserRole, QString::fromStdString(x.get_nume()));
		it->setData(257, QString::fromStdString(x.get_tip()));
		it->setData(258, QString::number(x.get_suprafata()));
		//list->addItem(QString::fromStdString(x.get_nume()));
	}
}

void Apartment_Manager_Qt::reload_filterz(std::vector<Locatar> l)
{
	filterz_list->clear();
	for (auto& x : l) {
		QListWidgetItem* it = new QListWidgetItem(QString::number(x.get_apartament()), filterz_list);
		it->setData(Qt::UserRole, QString::fromStdString(x.get_nume()));
		it->setData(257, QString::fromStdString(x.get_tip()));
		it->setData(258, QString::number(x.get_suprafata()));
		//list->addItem(QString::fromStdString(x.get_nume()));
	}
}

void Apartment_Manager_Qt::reload_types(std::vector<DTO> l)
{
	types_list->clear();
	for (auto& x : l) {
		QString text = QString::fromStdString(x.get_tip()) + " -> " + QString::number(x.get_nr());
		QListWidgetItem *it = new QListWidgetItem(text, types_list);
		it->setData(Qt::UserRole, QString::fromStdString(x.get_tip()));
	}
}

void Apartment_Manager_Qt::connect_signals_slots()
{
	QObject::connect(sort_name, &QPushButton::clicked, [&]() {
		reload_list(serv.sortare_nume());
	});

	QObject::connect(sort_supraf, &QPushButton::clicked, [&]() {
		reload_list(serv.sortare_suprafata());
	});

	QObject::connect(sort_type, &QPushButton::clicked, [&]() {
		reload_list(serv.sortare_apartament());
	});

	QObject::connect(filtrare_tip, &QPushButton::clicked, [&]() {
		std::string tip = input_tip->text().toStdString();
		if (!filterz_wnd->isVisible()) {
			filterz_wnd->show();
		}
		reload_filterz(serv.filtrare_apartament(tip));
	});

	QObject::connect(random, &QPushButton::clicked, [&]() {
		bool ok;
		int ap = QInputDialog::getInt(this, "Random add", "Number of apartments to add:", 0, 0, 2147483647, 1, &ok);
		if (ok) {
			serv.populeaza(ap);
			reload_cos(serv.get_cos());
		}
		else {
			QMessageBox::information(this, "Invalid input",
				"You must input the maximum amount of apartments to be added to the list as an integer!");
		}
		notify();
	});

	QObject::connect(filtrare_supraf, &QPushButton::clicked, this, [&]() {
		bool ok;
		int supraf = input_supraf->text().toInt(&ok);
		if (ok) {
			if (!filterz_wnd->isVisible()) {
				filterz_wnd->show();
			}
			reload_filterz(serv.filtrare_suprafata(supraf));
		}
		else {
			QMessageBox::information(this, "Invalid input", "Surface area must be an integer!");
		}
	});

	QObject::connect(add, &QPushButton::clicked, [&]() {
		bool ok;
		std::string s1 = input_nume->text().toStdString();
		std::string s2 = input_tip->text().toStdString();
		int s3 = input_ap->text().toInt(&ok);
		if (!ok) {
			QMessageBox::information(this, "Invalid input", "Apartment must be an interger, try again!");
		}
		else {
			int s4 = input_supraf->text().toInt(&ok);
			if (!ok) {
				QMessageBox::information(this, "Invalid input", "Surface area must be an integer, try again!");
			}
			else {
				try {
					serv.add(s1, s2, s3, s4);
				}
				catch (std::exception) {
					QMessageBox::information(this, "Invalid input", "Apartment is already registered!");
				}
				reload_list(serv.get_all());
			}
		}
	});

	QObject::connect(update, &QPushButton::clicked, [&]() {
		bool ok;
		std::string s1 = input_nume->text().toStdString();
		std::string s2 = input_tip->text().toStdString();
		int s3 = input_ap->text().toInt(&ok);
		if (!ok) {
			QMessageBox::information(this, "Invalid input", "Apartment must be an interger, try again!");
		}
		else {
			int s4 = input_supraf->text().toInt(&ok);
			if (!ok) {
				QMessageBox::information(this, "Invalid input", "Surface area must be an integer, try again!");
			}
			else {
				try {
					serv.update(s1, s2, s3, s4);
				}
				catch (std::exception) {
					QMessageBox::information(this, "Invalid input", "Apartment is already registered!");
				}
				reload_list(serv.get_all());
			}
		}
	});

	QObject::connect(remove, &QPushButton::clicked, this, [&]() {
		QItemSelectionModel *select = table_list->selectionModel();
		if(select->selectedRows().isEmpty()) {
			QMessageBox::information(this, "Invalid input", "Nothing was selected to be removed!");
		}
		else {
			auto sel = table_list->selectionModel()->selectedRows();
			auto index1 = this->table_list->model()->index(sel.at(0).row(), 0);
			//serv.del(sel->data(259).toInt());
			serv.del(this->table_list->model()->itemData(index1)[Qt::DisplayRole].toInt());
			//serv.del(sel->text().toInt());
			reload_list(serv.get_all());
		}
	});

	/*QObject::connect(list, &QListWidget::itemSelectionChanged, this, [&]() {
		if (list->selectedItems().isEmpty()) {
			input_nume->setText("");
			input_tip->setText("");
			input_ap->setText("");
			input_supraf->setText("");
			add_cos->setEnabled(false);
			remove->setEnabled(false);
		}
		else {
			auto sel = list->selectedItems().at(0);
			input_ap->setText(sel->data(259).toString());
			input_nume->setText(sel->data(Qt::UserRole).toString());
			input_tip->setText(sel->data(257).toString());
			input_supraf->setText(sel->data(258).toString());
			remove->setEnabled(true);
			add_cos->setEnabled(true);
		}
	});*/

	
	QObject::connect(table_list->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&]() {
		if (table_list->selectionModel()->selectedRows().isEmpty()) {
			input_nume->setText("");
			input_tip->setText("");
			input_ap->setText("");
			input_supraf->setText("");
			add_cos->setEnabled(false);
			remove->setEnabled(false);
		}
		else {
			auto sel = table_list->selectionModel()->selectedRows();
			auto index1 = this->table_list->model()->index(sel.at(0).row(), 0);
			auto index2 = this->table_list->model()->index(sel.at(0).row(), 1);
			auto index3 = this->table_list->model()->index(sel.at(0).row(), 2);
			auto index4 = this->table_list->model()->index(sel.at(0).row(), 3);
			input_ap->setText(this->table_list->model()->itemData(index1)[Qt::DisplayRole].toString());
			input_nume->setText(this->table_list->model()->itemData(index2)[Qt::DisplayRole].toString());
			input_tip->setText(this->table_list->model()->itemData(index3)[Qt::DisplayRole].toString());
			input_supraf->setText(this->table_list->model()->itemData(index4)[Qt::DisplayRole].toString());
			remove->setEnabled(true);
			add_cos->setEnabled(true);
		}
	});

	QObject::connect(undo, &QPushButton::clicked, this, [&]() {
		try {
			serv.undo_me();
			reload_list(serv.get_all());
		}
		catch (std::exception) {
			QMessageBox::information(this, "Invalid input", "No action to be undone!");
		}
	});

	QObject::connect(all_types, &QPushButton::clicked, this, [&]() {
		if (!types_wnd->isVisible()) {
			types_wnd->show();
		}
		reload_types(serv.get_all_types());
	});

	QObject::connect(show_cos, &QPushButton::clicked, this, [&]() {
		/*if (!cos_wnd->isVisible()) {
			cos_wnd->show();
			reload_cos(serv.get_cos());
		}*/
		CosWidget* cos = new CosWidget(serv, *this);
		cos->show();
		//addObservers(cos);
		//cos->addObservers();
	});

	QObject::connect(show_rdonly, &QPushButton::clicked, this, [&]() {
		/*if (!cos_wnd->isVisible()) {
			cos_wnd->show();
			reload_cos(serv.get_cos());
		}*/
		CosRDONLY* cos = new CosRDONLY(serv, *this);
		cos->show();
		//addObservers(cos);
	});

	QObject::connect(add_cos, &QPushButton::clicked, this, [&]() {
		if (table_list->selectionModel()->selectedRows().isEmpty()) {
			QMessageBox::information(this, "Invalid input", "Nothing was selected in order to be added!");
		}
		else {
			auto sel = table_list->selectionModel()->selectedRows();
			auto index1 = this->table_list->model()->index(sel.at(0).row(), 0);
			int ap = this->table_list->model()->itemData(index1)[Qt::DisplayRole].toString().toInt();
			//ap = sel->data(259).toInt();
			serv.adauga_cos(ap);
			reload_cos(serv.get_cos());
		}
		notify();
	});

	QObject::connect(goleste_cos, &QPushButton::clicked, this, [&]() {
		serv.goleste_cos();
		reload_cos(serv.get_cos());
		notify();
	});

	QObject::connect(save_cos, &QPushButton::clicked, this, [&]() {
		int r = QMessageBox::warning(this, "Apartments", "Are you sure you want to save this to the CSV?", QMessageBox::Save | QMessageBox::Cancel);
		if (r == QMessageBox::Save) {
			serv.salveaza_cos();
		}
	});
}
