#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "itkCSVArray2DFileReader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	typedef itk::CSVArray2DFileReader<double> CSVFileReaderType;
	typedef vnl_matrix<double> MatrixType;
	
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	void WriteCSVFiles(MatrixType matrix, QString filename);
	MatrixType ReadBVecFile(QString filename);

public slots:
    void OnOpenFileButtonClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
