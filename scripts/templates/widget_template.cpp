#include "TWidgets/{Name}Widget/{Name}Widget.h"

#include <QApplication>
#include <QGridLayout>
{includes}

namespace TWidget
{{
{Name}Widget::{Name}Widget(QWidget *parent)
  : TWidget(parent)
{{
    {Name}Widget::initUI();
    {Name}Widget::initSignalAndSlots();
}}

{Name}Widget::~{Name}Widget()
{{
}}

void {Name}Widget::initUI()
{{
    setObjectName(QString("{ComponentName}Widget"));
    resize(380, 250);

    QGridLayout *gridLayout = new QGridLayout();
    setLayout(gridLayout);

{init_ui}

    retranslate();
    clear();
    update();
}}

void {Name}Widget::initSignalAndSlots()
{{
{connect_signals_and_slots}
}}

void {Name}Widget::retranslate()
{{
{translate_text}
}}

void {Name}Widget::clear()
{{
{clear_code}	
}}

void {Name}Widget::update()
{{
}}

{getter}
{setter}

}} // namespace TWidget
