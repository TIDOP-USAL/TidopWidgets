#include <QApplication>
#include <QMainWindow>

#include "TWidgets/RasterFilters/BilateralFilterWidget.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Crear una ventana principal
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Bilateral Filter");

    // Instanciar el widget
    TWidget::BilateralFilterWidget *bilateral_filter = new TWidget::BilateralFilterWidget(&mainWindow);

    // Configurar el widget con valores iniciales
    //testWidget->setMass(100);
    //jpegWidget->setTrack("Tesla Model S");
    //jpegWidget->setWheelbase(true);

    // Mostrar el widget en la ventana principal
    mainWindow.setCentralWidget(bilateral_filter);
    mainWindow.resize(400, 300);
    mainWindow.show();

    // Iniciar la aplicación
    return app.exec();
}
