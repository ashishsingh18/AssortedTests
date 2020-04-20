#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>

#include <itkImage.h>
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include <itkOrientImageFilter.h>
#include "itkCSVNumericObjectFileWriter.h"
#include "itkExtractImageFilter.h"
#include "itkImageIOFactory.h"

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

	//get image properties
	itk::ImageIOBase::Pointer itkImageIOBase;
	itkImageIOBase = itk::ImageIOFactory::CreateImageIO(inputFilename.toStdString().c_str(),itk::ImageIOFactory::ReadMode);
	if (!itkImageIOBase->CanReadFile(inputFilename.toStdString().c_str()))
	{
		std::cout << "Cannot read '" << inputFilename.toStdString() << "'\n";
	}

	itkImageIOBase->SetFileName(inputFilename.toStdString());
	itkImageIOBase->ReadImageInformation();

	int dims = itkImageIOBase->GetNumberOfDimensions();
	std::cout << " image dimensions = " << dims << std::endl;

	//store image dimensions
	int isize[4];
	for (int i = 0; i < dims; i++)
		isize[i] = itkImageIOBase->GetDimensions(i);

	//itk 
	using PixelType = short;
	constexpr unsigned int Dimension4D = 4;
	using ImageTypeDWI = itk::Image<PixelType, Dimension4D>;

	constexpr unsigned int Dimension3D = 3;
	using ImageType3D = itk::Image<PixelType, Dimension3D>;

	//read input image
	using ReaderType = itk::ImageFileReader<ImageTypeDWI>;

    ReaderType::Pointer reader = ReaderType::New();
    std::cout << "Begin file reading" << endl;
	reader->SetFileName(inputFilename.toStdString());
	reader->GetOutput();
	ImageTypeDWI::Pointer dwiimg = reader->GetOutput();

	//outputFilename = inputFilename + "_out.nii.gz";
	//writer->SetFileName(outputFilename.toStdString());
	//writer->SetInput(reader->GetOutput());
	//writer->Write();

	//std::cout << " input file read and re-written " << std::endl;

	//string,enum map of itk orientation
	std::map< itk::SpatialOrientation::ValidCoordinateOrientationFlags, std::string > m_CodeToString;
    // Map between axis string labels and SpatialOrientation

    // the "from" (neurological) convention is used here as per ITK
    // key = itk spatial orientation, value = axcode/acronym string
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

	//std::cout << " image dimensions = " << dwiimg->GetImageDimension() << std::endl;
	//ImageTypeDWI::RegionType region = dwiimg->GetLargestPossibleRegion();
	//ImageTypeDWI::SizeType   size = region.GetSize();
	//std::cout << " size = " << size[0] << std::endl;

    // generate axcode label mapping between the two orientations
    std::map<std::string, std::string> axcodeOrientationSwitchMap;
    for (auto it = m_CodeToString.begin(); it != m_CodeToString.end(); ++it){ // iterate through map
        std::string swappedAcronym;
        for (char ax : it->second) { // iterate through acronym
           // invert axis label
           swappedAcronym += vtkAnatomicalOrientation::AxisToChar(
                                vtkAnatomicalOrientation::AxisInverse(
                                    vtkAnatomicalOrientation::AxisFromChar(ax)));
        }
        axcodeOrientationSwitchMap[it->second] = swappedAcronym;
    }

    // generate "to" (radiological) convention mapping
    // key = itk spatial coordinate orientation, value = axcode/acronym string
    std::map< itk::SpatialOrientation::ValidCoordinateOrientationFlags, std::string > m_radiologicalCodeToString;
    for (auto it = m_CodeToString.begin(); it != m_CodeToString.end(); ++it) {
        m_radiologicalCodeToString[it->first] = axcodeOrientationSwitchMap[it->second]; //
    }

	// 4D image handling starts here
	// we extract individual 3D images from the input 4D image

	// set the sub-image properties
	typename ImageTypeDWI::IndexType regionIndex;
	typename ImageTypeDWI::SizeType regionSize;
	regionSize[0] = isize[0];
	regionSize[1] = isize[1];
	regionSize[2] = isize[2];
	regionSize[3] = 0;
	regionIndex[0] = 0;
	regionIndex[1] = 0;
	regionIndex[2] = 0;

	for (int i = 0; i < isize[3]; i++)
	{
		regionIndex[3] = i;
		typename ImageTypeDWI::RegionType desiredRegion(regionIndex, regionSize);

		auto filter = itk::ExtractImageFilter< ImageTypeDWI, ImageType3D >::New();
		filter->SetExtractionRegion(desiredRegion);
		filter->SetInput(dwiimg);
		filter->SetDirectionCollapseToSubmatrix();
		filter->Update();
		auto extractedImg = filter->GetOutput();

		//get orientation
		auto orientFilter = itk::OrientImageFilter< ImageType3D, ImageType3D >::New();
		orientFilter->SetInput(extractedImg);
		orientFilter->UseImageDirectionOn();
		orientFilter->SetDirectionTolerance(0);
		orientFilter->SetCoordinateTolerance(0);
		orientFilter->Update();
		std::cout << "image # " << i << " , orientation = " << m_CodeToString[orientFilter->GetGivenCoordinateOrientation()] << std::endl;
	}

	////use orient image filter to get orientation
	//auto orientFilter = itk::OrientImageFilter< ImageTypeDWI, ImageTypeDWI >::New();
	//orientFilter->SetInput(reader->GetOutput());
	//orientFilter->UseImageDirectionOn();
	//orientFilter->SetDirectionTolerance(0);
	//orientFilter->SetCoordinateTolerance(0);
	////orientFilter->SetDesiredCoordinateOrientation(itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RAI);
	//orientFilter->Update();
 //   std::cout << " input image orientation = " << m_CodeToString[orientFilter->GetGivenCoordinateOrientation()] << std::endl;
	//std::cout << orientFilter->GetPermuteOrder() << std::endl;

    std::cout << "Calculating necessary transform" << endl;
	//anatomical orientation transform
    std::string strCurrentOrientation("LAS");
    std::string strDesiredOrientation("LIA");
    vtkAnatomicalOrientation currentOrientation(strCurrentOrientation);
    // Change the above line to take the string-conversion of ITK OrientImageFilter's "GetGivenCoordinateOrientation"
    // (use either m_CodeToString or m_radiologicalCodeToString as desired/needed)
    vtkAnatomicalOrientation desiredOrientation;
    desiredOrientation.SetForAcronym(strDesiredOrientation);
    double transform[9] = { 0.0 };
    currentOrientation.GetTransformTo(desiredOrientation, transform);
	for (int i = 0; i < 9; i++)
        std::cout << transform[i] << " ";
	std::cout << endl;

	//read bvec
    std::cout << "Applying transform" << endl;

    MatrixType dataMatrix =	this->ReadBVecFile("C:\\workspace\\Data\\Testathon\\issue840\\reorient_bvecs\\dwi_las.bvec");
    MatrixType transformMatrix(3, 3, 9, transform); // read LAStoLPS transform into 3x3 vnl_matrix<double>

	//reorient bvec
    MatrixType resultMatrix(dataMatrix); // same shape as data
    resultMatrix = dataMatrix.transpose() * transformMatrix; // apply the transform
    resultMatrix.inplace_transpose(); // transpose back to original shape

	//write reorient bvec
    this->WriteCSVFiles(resultMatrix, "C:\\workspace\\Data\\\\Testathon\\issue840\\reorient_bvecs\\dwi_las_STANDALONE_to" + strDesiredOrientation + ".bvec");

}

void MainWindow::WriteCSVFiles(MatrixType matrix, std::string filename)
{
    std::cout << "Beginning file writing"  << endl;
    using WriterType = itk::CSVNumericObjectFileWriter<double>;
    WriterType::Pointer writer = WriterType::New();

    try {
        writer->SetInput(&matrix);
        writer->SetFileName(filename);
        writer->SetFieldDelimiterCharacter(' ');
        writer->Update();
    }
    catch (...) {
        std::cout << "File writing failed. Check permissions, etc." << endl;
        return;
    }

    QMessageBox::information(
            this, tr("ReorientBvecTest"), tr("Done writing to file."));

	std::cout << " print reoriented bvec " << std::endl;
	std::cout << matrix << std::endl;

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
