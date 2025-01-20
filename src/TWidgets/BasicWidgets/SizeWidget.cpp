#include "TWidgets/BasicWidgets/SizeWidget.h"

#include <QGridLayout>
#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>

SizeWidget::SizeWidget(const QString &name, QWidget *parent)
  : QWidget(parent), 
    mGroupBox(new QGroupBox(name, this)),
    mLabelWidth(new QLabel("Width:", this)),
    mLabelHeight(new QLabel("Height:", this)),
    mWidthSpinBox(new QSpinBox(this)),
    mHeightSpinBox(new QSpinBox(this))
{
    this->setWindowTitle("SizeWidget");

    QGridLayout *layout = new QGridLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    layout->addWidget(mGroupBox);

    QGridLayout *propertiesLayout = new QGridLayout();
    mGroupBox->setLayout(propertiesLayout);

    propertiesLayout->addWidget(mLabelWidth, 0, 0);
    propertiesLayout->addWidget(mWidthSpinBox, 0, 1);
    propertiesLayout->addWidget(mLabelHeight, 1, 0);
    propertiesLayout->addWidget(mHeightSpinBox, 1, 1);

    // Configuración de los SpinBoxes
    mWidthSpinBox->setMinimum(0); // Ancho mínimo
    mHeightSpinBox->setMinimum(0); // Alto mínimo

    // Establecer valores iniciales
    //mWidthSpinBox->setValue(defaultValue.width());
    //mHeightSpinBox->setValue(defaultValue.height());

    // Conectar las señales de los SpinBox a sus slots correspondientes
    connect(mWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onWidthChanged(int)));
    connect(mHeightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onHeightChanged(int)));

}

SizeWidget::~SizeWidget()
{
}

void SizeWidget::setSize(const QSize &size)
{
    mWidthSpinBox->setValue(size.width());
    mHeightSpinBox->setValue(size.height());
}

auto SizeWidget::size() const -> QSize
{
    return QSize(mWidthSpinBox->value(), mHeightSpinBox->value());
}

void SizeWidget::onWidthChanged(int width)
{
    // Emitir la señal sizeChanged cuando el valor del ancho cambie
    emit sizeChanged(QSize(width, mHeightSpinBox->value()));
}

void SizeWidget::onHeightChanged(int height)
{
    // Emitir la señal sizeChanged cuando el valor de la altura cambie
    emit sizeChanged(QSize(mWidthSpinBox->value(), height));
}