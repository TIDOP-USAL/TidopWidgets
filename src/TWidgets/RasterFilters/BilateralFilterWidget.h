#pragma once

#include "TWidgets/TidopWidget.h"

class QDialogButtonBox;
class QComboBox;
class QDoubleSpinBox;
class QLabel;
class QSpinBox;

namespace TWidget
{
class BilateralFilterWidget
  : public TWidget
{
    Q_OBJECT

public:
    BilateralFilterWidget(QWidget *parent = nullptr);
    ~BilateralFilterWidget() override;
public:

    int diameter() const;
    double sigmaColor() const;
    double sigmaSpace() const;
    QString borderType() const;
public slots:
  
    void setDiameter(int value);
    void setSigmacolor(double value);
    void setSigmaspace(double value);
    void setBordertype(const QString& value);

private:
    void initUI() override;
    void initSignalAndSlots() override;

public slots:
    void clear() override;

private slots:
    void update() override;
    void retranslate() override;

protected:
    QLabel *mLabelDiameter;
    QLabel *mLabelSigmacolor;
    QLabel *mLabelSigmaspace;
    QLabel *mLabelBordertype;
    QSpinBox *mDiameter;
    QDoubleSpinBox *mSigmacolor;
    QDoubleSpinBox *mSigmaspace;
    QComboBox *mBordertype;
    QDialogButtonBox *mButtonBox;
};
} // namespace TWidget