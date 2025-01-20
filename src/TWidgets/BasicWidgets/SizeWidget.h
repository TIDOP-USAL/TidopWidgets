#pragma once

#include <QWidget>
#include <QSize>

class QLabel;
class QSpinBox;
class QGroupBox;

class SizeWidget 
  : public QWidget
{
    Q_OBJECT

public:

    explicit SizeWidget(const QString &name, QWidget *parent = nullptr);
    ~SizeWidget();

    // Función para establecer el tamaño
    void setSize(const QSize &size);
    auto size() const -> QSize;

signals:

    void sizeChanged(const QSize &size);

private slots:

    void onWidthChanged(int width);
    void onHeightChanged(int height);
	
private:

    QGroupBox *mGroupBox;
    QLabel *mLabelWidth;
    QLabel *mLabelHeight;
    QSpinBox *mWidthSpinBox;
    QSpinBox *mHeightSpinBox;
	
};