#pragma once

#include <QWidget>
#include <QEvent>

namespace TWidget
{

class TWidget
  : public QWidget
{

    Q_OBJECT

public:
  
    TWidget(QWidget *parent)
      : QWidget(parent)
    {
    }
  
    ~TWidget() override {}

private:

    /*!
     * \brief Widget Initialization
     */
    virtual void initUI() = 0;
    virtual void initSignalAndSlots() = 0;

public slots:

    /*!
     * \brief Clear the widget
     */
    virtual void clear() = 0;

private slots:

    virtual void update() = 0;
    virtual void retranslate() = 0;
    
// QWidget interface

protected:

    void changeEvent(QEvent *event) override
    {
        if (event->type() == QEvent::LanguageChange) {
            this->retranslate();
        }
    }

};

} // TWidget