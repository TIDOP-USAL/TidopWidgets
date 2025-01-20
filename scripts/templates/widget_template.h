#pragma once

#include "TWidgets/TidopWidget.h"

class QDialogButtonBox;
{forward_declaration}

namespace TWidget
{{
class {Name}Widget
  : public TWidget
{{
    Q_OBJECT

public:
    {Name}Widget(QWidget *parent = nullptr);
    ~{Name}Widget() override;
public:

{getter}
public slots:
  
{setter}

private:
    void initUI() override;
    void initSignalAndSlots() override;

public slots:
    void clear() override;

private slots:
    void update() override;
    void retranslate() override;

protected:
{dataMembers}
    QDialogButtonBox *mButtonBox;
}};
}} // namespace TWidget