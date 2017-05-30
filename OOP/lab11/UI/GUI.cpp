#include "GUI.h"

GUI::GUI(Controller* _ctrl)
{
	this->ctrl = _ctrl;
	this->setup_gui();
	this->connect_gui();
}

void	GUI::setup_gui()
{
	this->setContentsMargins(10, 10, 10, 10);
	QHBoxLayout* main_lay = new QHBoxLayout(this);
	QVBoxLayout* left_lay = new QVBoxLayout();
	QVBoxLayout* right_lay = new QVBoxLayout();


	QHBoxLayout* title_lay = new QHBoxLayout();
		QLabel* lbl_title = new QLabel(QObject::tr("title"));
		lbl_title->setAlignment(Qt::AlignCenter);
		this->txt_title = new QLineEdit();

	QHBoxLayout* desc_lay = new QHBoxLayout();
		QLabel* lbl_desc = new QLabel(QObject::tr("description"));
		lbl_desc->setAlignment(Qt::AlignCenter);
		this->txt_desc = new QLineEdit();

	QHBoxLayout* type_lay = new QHBoxLayout();
		QLabel* lbl_type = new QLabel(QObject::tr("type"));
		lbl_type->setAlignment(Qt::AlignCenter);
		this->txt_type = new QLineEdit();

	QHBoxLayout* dur_lay = new QHBoxLayout();
		QLabel* lbl_dur = new QLabel(QObject::tr("duration"));
		lbl_dur->setAlignment(Qt::AlignCenter);
		this->txt_dur = new QLineEdit();

	QHBoxLayout* op_lay = new QHBoxLayout();
		this->add_btn = new QPushButton(QObject::tr("&Add"));
		this->upd_btn = new QPushButton(QObject::tr("Updat&e"));
		this->rm_btn = new QPushButton(QObject::tr("&Remove"));
	QHBoxLayout* fil_lay = new QHBoxLayout();
		this->fil_desc = new QPushButton(QObject::tr("FilterBy&Desc"));
		this->fil_type = new QPushButton(QObject::tr("FilterBy&Type"));
		this->fil_search = new QPushButton(QObject::tr("&Search"));

	activities = new QListWidget();
	new QListWidgetItem("Item1", activities);
	new QListWidgetItem("Item2", activities);

	main_lay->addLayout(left_lay);
	main_lay->addLayout(right_lay);

	title_lay->addWidget(lbl_title);
	title_lay->addStretch();
	title_lay->addWidget(txt_title);
	desc_lay->addWidget(lbl_desc);
	desc_lay->addStretch();
	desc_lay->addWidget(txt_desc);
	type_lay->addWidget(lbl_type);
	type_lay->addStretch();
	type_lay->addWidget(txt_type);
	dur_lay->addWidget(lbl_dur);
	dur_lay->addStretch();
	dur_lay->addWidget(txt_dur);
	op_lay->addWidget(add_btn);
	op_lay->addWidget(upd_btn);
	op_lay->addWidget(rm_btn);
	fil_lay->addWidget(fil_desc);
	fil_lay->addWidget(fil_type);
	fil_lay->addWidget(fil_search);

	right_lay->addLayout(title_lay);
	right_lay->addLayout(desc_lay);
	right_lay->addLayout(type_lay);
	right_lay->addLayout(dur_lay);
	right_lay->addLayout(op_lay);
	right_lay->addLayout(fil_lay);

	QHBoxLayout* sort_lay = new QHBoxLayout();
		this->sort_title_btn = new QPushButton(QObject::tr("SortByTit&le"));
		this->sort_desc_btn = new QPushButton(QObject::tr("SortByDes&c"));
		this->sort_type_btn = new QPushButton(QObject::tr("SortByT&ype"));

	left_lay->addWidget(activities);
	left_lay->addLayout(sort_lay);

	sort_lay->addWidget(sort_title_btn);
	sort_lay->addWidget(sort_desc_btn);
	sort_lay->addWidget(sort_type_btn);
}

void	GUI::connect_gui()
{
	QObject::connect(add_btn, SIGNAL(clicked()), this, SLOT(add()));
	QObject::connect(upd_btn, SIGNAL(clicked()), this, SLOT(edit()));
	QObject::connect(rm_btn, SIGNAL(clicked()), this, SLOT(remove()));
}

void	GUI::add()
{
	string	title;
	string	desc;
	string	type;
	int		dur;
	string	input;

	title = this->txt_title->displayText().toStdString();
	desc = this->txt_desc->displayText().toStdString();
	type = this->txt_type->displayText().toStdString();
	input = this->txt_dur->displayText().toStdString();

	if (!(this->ctrl->isvalid_title(title) && this->ctrl->isvalid_number(input) && this->ctrl->isvalid_type(type) && this->ctrl->isvalid_description(desc) && !input.empty()))
		return;

	dur = stoi(input);
	try
	{
		this->controller->add(title, description, type, duration);
	}
	catch (const not_unique& e)
	{
		return;
	}

	this->txt_title->clear();
	this->txt_dur->clear();
	this->txt_type->clear();
	this->txt_desc->clear();

	string	str = "";

	str += title + "; " + desc + "; " + type + "; " + input;

	new QListWidgetItem(QString::fromStdString(str), activities);
}

void	GUI::edit()
{
	string	title;
	string	type;
	string	dur;
	string	desc;

	title = this->txt_title->displayText().toStdString();
	desc = this->txt_desc->displayText().toStdString();
	type = this->txt_type->displayText().toStdString();
	dur = this->txt_dur->displayText().toStdString();

	if (this->ctrl->exists(title) || !this->ctrl->isvalid_title(title))
		return;

	this->ctrl->edit(title, desc, type, dur);

	this->txt_title->clear();
	this->txt_dur->clear();
	this->txt_type->clear();
	this->txt_desc->clear();
}

void	GUI::remove()
{
	string	title;

	title = this->txt_title->displayText().toStdString();
	if (!this->ctrl->isvalid_title(title))
		return;
	try
	{
 		this->ctrl->remove(title);
		this->txt_title->clear();
	}
	catch (const invalid_argument& e)
	{}
}
