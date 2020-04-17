#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>

#include <itkImage.h>
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include <itkOrientImageFilter.h>
#include "itkCSVNumericObjectFileWriter.h"

#include "vtkSmartPointer.h"
#include <vtkNIFTIImageReader.h>
#include <vtkImageData.h>
#include "vtkAnatomicalOrientation.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //signals/slots
    connect(ui->openfileBtn,SIGNAL(clicked()),this,SLOT(OnOpenFileButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnOpenFileButtonClicked()
{
	qDebug() << " OnOpenFileButtonClicked " << endl;

	QString inputFilename, outputFilename;

	inputFilename = QFileDialog::getOpenFileName(this, tr("Open File"),
		QDir::currentPath(),
		tr("Images (*.nii.gz)"));

	//from here on the code becomes ugly and unstructured

	//itk 
	using PixelType = short;
	constexpr unsigned int Dimension = 3;
	using ImageType = itk::Image<PixelType, Dimension>;

	using ReaderType = itk::ImageFileReader<ImageType>;

    ReaderType::Pointer reader = ReaderType::New();

    std::cout << "Begin file reading" << endl;
	reader->SetFileName(inputFilename.toStdString());
	reader->GetOutput();

	//outputFilename = inputFilename + "_out.nii.gz";
	//writer->SetFileName(outputFilename.toStdString());
	//writer->SetInput(reader->GetOutput());
	//writer->Write();

	//std::cout << " input file read and re-written " << std::endl;

	//string,enum map of itk orientation
	std::map< itk::SpatialOrientation::ValidCoordinateOrientationFlags, std::string > m_CodeToString;
	// Map between axis string labels and SpatialOrientation
    // "from" conventions are used here (I think)
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RIP] = "RIP";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_LIP] = "LIP";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RSP] = "RSP";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_LSP] = "LSP";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RIA] = "RIA";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_LIA] = "LIA";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RSA] = "RSA";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_LSA] = "LSA";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_IRP] = "IRP";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_ILP] = "ILP";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_SRP] = "SRP";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_SLP] = "SLP";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_IRA] = "IRA";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_ILA] = "ILA";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_SRA] = "SRA";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_SLA] = "SLA";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RPI] = "RPI";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_LPI] = "LPI";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RAI] = "RAI";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_LAI] = "LAI";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RPS] = "RPS";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_LPS] = "LPS";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RAS] = "RAS";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_LAS] = "LAS";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_PRI] = "PRI";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_PLI] = "PLI";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_ARI] = "ARI";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_ALI] = "ALI";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_PRS] = "PRS";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_PLS] = "PLS";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_ARS] = "ARS";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_ALS] = "ALS";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_IPR] = "IPR";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_SPR] = "SPR";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_IAR] = "IAR";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_SAR] = "SAR";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_IPL] = "IPL";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_SPL] = "SPL";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_IAL] = "IAL";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_SAL] = "SAL";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_PIR] = "PIR";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_PSR] = "PSR";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_AIR] = "AIR";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_ASR] = "ASR";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_PIL] = "PIL";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_PSL] = "PSL";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_AIL] = "AIL";
	m_CodeToString[itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_ASL] = "ASL";


	//use orient image filter to get orientation
	auto orientFilter = itk::OrientImageFilter< ImageType, ImageType >::New();
	orientFilter->SetInput(reader->GetOutput());
	orientFilter->UseImageDirectionOn();
	orientFilter->SetDirectionTolerance(0);
	orientFilter->SetCoordinateTolerance(0);
	//orientFilter->SetDesiredCoordinateOrientation(itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RAI);
	orientFilter->Update();
    std::cout << " input image orientation = " << m_CodeToString[orientFilter->GetGivenCoordinateOrientation()] << std::endl;
	std::cout << orientFilter->GetPermuteOrder() << std::endl;

    std::cout << "Calculating necessary transform" << endl;
	//anatomical orientation transform
	vtkAnatomicalOrientation orientmatrix("LAS");
	double LAStoLPS[9] = { 0.0 };
	orientmatrix.GetTransformTo(vtkAnatomicalOrientation::LPS, LAStoLPS);
	for (int i = 0; i < 9; i++)
		std::cout << LAStoLPS[i] << " ";
	std::cout << endl;


	//read bvec
    std::cout << "Applying transform" << endl;
    MatrixType dataMatrix =	this->ReadBVecFile("E:\\moba\\orientations\\dwi_las.bvec");
    MatrixType transformMatrix(3, 3, 9, LAStoLPS); // read LAStoLPS transform into 3x3 vnl_matrix<double>

    MatrixType resultMatrix(dataMatrix); // same shape as data
    resultMatrix = dataMatrix.transpose() * transformMatrix; // apply the transform
    resultMatrix.inplace_transpose(); // transpose back to original shape

    this->WriteCSVFiles(resultMatrix, "E:/moba/orientations/test_output/dwi_las_toLPS.bvec");


}

void MainWindow::WriteCSVFiles(MatrixType matrix, QString filename)
{
	//std::ofstream myfile;
	//myfile.open(filename.toStdString());
	//for (unsigned int index1 = 0; index1 < matrix.Size(); index1++)
		//myfile << std::to_string(inputdata[index1]) << ",";

	//myfile << "\n";
	//myfile.close();

    std::cout << "Beginning file writing"  << endl;
    using WriterType = itk::CSVNumericObjectFileWriter<double>;
    WriterType::Pointer writer = WriterType::New();

    try {
        writer->SetInput(&matrix);
        writer->SetFileName(filename.toStdString());
        writer->SetFieldDelimiterCharacter(' ');
        writer->Update();
    }
    catch (...) {
        std::cout << "File writing failed. Check permissions, etc." << endl;
        return;
    }

    QMessageBox::information(
            this, tr("ReorientBvecTest"), tr("Done writing to file."));

	std::cout << matrix;
	std::cout << endl;

}


MainWindow::MatrixType MainWindow::ReadBVecFile(QString filename)
{
	//read bvec file
	CSVFileReaderType::Pointer csvreader = CSVFileReaderType::New();

    itk::SizeValueType rows;
    itk::SizeValueType cols;
	try
	{
		csvreader->SetFileName(filename.toStdString());
		csvreader->SetFieldDelimiterCharacter(' ');
		csvreader->HasColumnHeadersOff();
		csvreader->HasRowHeadersOff();
		csvreader->Parse();
        csvreader->GetDataDimension(rows, cols);
	}
	catch (const std::exception& e1)
	{
		std::cout << "Cannot find the file bvec file. Error code : " + std::string(e1.what());
	}
    MatrixType dataMatrix(rows, cols); // give data matrix a definite size
    dataMatrix = csvreader->GetArray2DDataObject()->GetMatrix();
	return dataMatrix;
}
