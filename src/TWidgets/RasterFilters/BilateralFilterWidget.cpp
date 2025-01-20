#include "TWidgets/RasterFilters/BilateralFilterWidget.h"

#include <QApplication>
#include <QGridLayout>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpinBox>

namespace TWidget
{
BilateralFilterWidget::BilateralFilterWidget(QWidget *parent)
  : TWidget(parent)
{
    BilateralFilterWidget::initUI();
    BilateralFilterWidget::initSignalAndSlots();
}

BilateralFilterWidget::~BilateralFilterWidget()
{
}

void BilateralFilterWidget::initUI()
{
    setObjectName(QString("BilateralFilterWidget"));
    resize(380, 250);

    QGridLayout *gridLayout = new QGridLayout();
    setLayout(gridLayout);

    mLabelDiameter = new QLabel(this);
    gridLayout->addWidget(mLabelDiameter, 0, 0);
    mDiameter = new QSpinBox(this);
    gridLayout->addWidget(mDiameter, 0, 1);
    mDiameter->setToolTip(QString::fromUtf8("Diameter of the pixel neighborhood"));
    mLabelSigmacolor = new QLabel(this);
    gridLayout->addWidget(mLabelSigmacolor, 1, 0);
    mSigmacolor = new QDoubleSpinBox(this);
    gridLayout->addWidget(mSigmacolor, 1, 1);
    mSigmacolor->setToolTip(QString::fromUtf8("Controls the filter's sensitivity to intensity differences"));
    mLabelSigmaspace = new QLabel(this);
    gridLayout->addWidget(mLabelSigmaspace, 2, 0);
    mSigmaspace = new QDoubleSpinBox(this);
    gridLayout->addWidget(mSigmaspace, 2, 1);
    mSigmaspace->setToolTip(QString::fromUtf8("Controls the filter's sensitivity to spatial distance"));
    mLabelBordertype = new QLabel(this);
    gridLayout->addWidget(mLabelBordertype, 3, 0);
    mBordertype = new QComboBox(this);
    gridLayout->addWidget(mBordertype, 3, 1);
    mBordertype->setToolTip(QString::fromUtf8("Method for border extrapolation"));
    mDiameter->setMinimum(1);
    mDiameter->setMaximum(100);
    mDiameter->setValue(15);
    mSigmacolor->setMinimum(0.);
    mSigmacolor->setMaximum(100.);
    mSigmacolor->setValue(0.0);
    mSigmaspace->setMinimum(0.);
    mSigmaspace->setMaximum(100.);
    mSigmaspace->setValue(0.0);
    mBordertype->addItem("constant");
    mBordertype->addItem("replicate");
    mBordertype->addItem("reflect");
    mBordertype->addItem("wrap");
    mBordertype->addItem("transparent");
    mBordertype->addItem("default");
    mBordertype->addItem("isolated");
    mBordertype->setCurrentText("default");

    retranslate();
    clear();
    update();
}

void BilateralFilterWidget::initSignalAndSlots()
{
    connect(mDiameter, QOverload<int>::of(&QSpinBox::valueChanged), this, &BilateralFilterWidget::update);
    connect(mSigmacolor, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &BilateralFilterWidget::update);
    connect(mSigmaspace, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &BilateralFilterWidget::update);
    connect(mBordertype, &QComboBox::currentTextChanged, this, &BilateralFilterWidget::update);
}

void BilateralFilterWidget::retranslate()
{
    mLabelDiameter->setText(QApplication::translate("BilateralFilterWidget", "Diameter", nullptr));
    mLabelSigmacolor->setText(QApplication::translate("BilateralFilterWidget", "Sigma Color", nullptr));
    mLabelSigmaspace->setText(QApplication::translate("BilateralFilterWidget", "Sigma Space", nullptr));
    mLabelBordertype->setText(QApplication::translate("BilateralFilterWidget", "Border Type", nullptr));
}

void BilateralFilterWidget::clear()
{
    mDiameter->setValue(15);
    mSigmacolor->setValue(0.0);
    mSigmaspace->setValue(0.0);
    mBordertype->setCurrentText("default");	
}

void BilateralFilterWidget::update()
{
}

int BilateralFilterWidget::diameter() const
{
    return mDiameter->value();
}
double BilateralFilterWidget::sigmaColor() const
{
    return mSigmacolor->value();
}
double BilateralFilterWidget::sigmaSpace() const
{
    return mSigmaspace->value();
}
QString BilateralFilterWidget::borderType() const
{
    return mBordertype->currentText();
}
void BilateralFilterWidget::setDiameter(int value)
{
    mDiameter->setValue(value);
}
void BilateralFilterWidget::setSigmacolor(double value)
{
    mSigmacolor->setValue(value);
}
void BilateralFilterWidget::setSigmaspace(double value)
{
    mSigmaspace->setValue(value);
}
void BilateralFilterWidget::setBordertype(const QString& value)
{
    mBordertype->setCurrentText(value);
}

} // namespace TWidget
