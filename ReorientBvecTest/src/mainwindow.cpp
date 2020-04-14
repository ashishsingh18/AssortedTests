#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>

#include <itkImage.h>
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include <itkOrientImageFilter.h>


#include "vtkSmartPointer.h"
#include <vtkNIFTIImageReader.h>
#include <vtkImageData.h>
#include "vtkAnatomicalOrientation.h"

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
	using WriterType = itk::ImageFileWriter<ImageType>;

	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();

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
	std::cout << " input image orientatation = " << m_CodeToString[orientFilter->GetGivenCoordinateOrientation()] << std::endl;
	std::cout << orientFilter->GetPermuteOrder() << std::endl;

	//anatomical orientation transform
	vtkAnatomicalOrientation orientmatrix("LAS");
	double LAStoLPS[9] = { 0.0 };
	orientmatrix.GetTransformTo(vtkAnatomicalOrientation::LPS, LAStoLPS);
	for (int i = 0; i < 9; i++)
		std::cout << LAStoLPS[i] << " ";
	std::cout << endl;

	//read bvec
	MatrixType dataMatrix =	this->ReadBVecFile("C:\\workspace\\Data\\Testathon\\issue840\\reorient_bvecs\\dwi_las.bvec");
	this->WriteCSVFiles(dataMatrix, "C:\workspace\Data\Testathon\issue840\reorient_bvecs\vnlout.txt");
}

void MainWindow::WriteCSVFiles(MatrixType matrix, QString filename)
{
	//std::ofstream myfile;
	//myfile.open(filename.toStdString());
	//for (unsigned int index1 = 0; index1 < matrix.Size(); index1++)
		//myfile << std::to_string(inputdata[index1]) << ",";

	//myfile << "\n";
	//myfile.close();
	std::cout << matrix;
	std::cout << endl;
}


MainWindow::MatrixType MainWindow::ReadBVecFile(QString filename)
{
	//read bvec file
	CSVFileReaderType::Pointer csvreader = CSVFileReaderType::New();
	MatrixType dataMatrix;
	try
	{
		csvreader->SetFileName(filename.toStdString());
		csvreader->SetFieldDelimiterCharacter(' ');
		csvreader->HasColumnHeadersOff();
		csvreader->HasRowHeadersOff();
		csvreader->Parse();
		dataMatrix = csvreader->GetArray2DDataObject()->GetMatrix();

	}
	catch (const std::exception& e1)
	{
		std::cout << "Cannot find the file bvec file. Error code : " + std::string(e1.what());
	}
	return dataMatrix;
}
