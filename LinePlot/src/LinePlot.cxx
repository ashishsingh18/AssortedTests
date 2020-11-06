#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartXY.h>
#include <vtkTable.h>
#include <vtkPlot.h>
#include <vtkFloatArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkPen.h>
#include <map>
 
void CreateChart(vtkChartXY* chart, std::map<std::string, std::vector<float>*>* map)
{
	for (std::map<std::string, std::vector<float>*>::iterator itr = map->begin(); itr != map->end(); ++itr)
	{
		vtkNew< vtkTable> table;

		for (vtkIdType i = 0; i < itr->second->size(); i++)
		{
			table->SetValue(i, 0, i);
			table->SetValue(i, 1, itr->second->at(i));
		}

		vtkPlot *line = chart->AddPlot(vtkChart::POINTS);
		line->SetInputData(table, 0, 1);
		line->SetColor(0, 255, 0, 255);
		line->SetWidth(1.0);
	}
}

int main(int, char *[])
{
  // Create a table with some points in it
  vtkSmartPointer<vtkTable> table = 
    vtkSmartPointer<vtkTable>::New();
 
  vtkSmartPointer<vtkFloatArray> arrX = 
    vtkSmartPointer<vtkFloatArray>::New();
  arrX->SetName("X Axis");
  table->AddColumn(arrX);
 
  vtkSmartPointer<vtkFloatArray> arrC = 
    vtkSmartPointer<vtkFloatArray>::New();
  arrC->SetName("Cosine");
  table->AddColumn(arrC);
 
  vtkSmartPointer<vtkFloatArray> arrS = 
    vtkSmartPointer<vtkFloatArray>::New();
  arrS->SetName("Sine");
  table->AddColumn(arrS);
 
  // Fill in the table with some example values
  int numPoints = 69;
  float inc = 7.5 / (numPoints-1);
  table->SetNumberOfRows(numPoints);
  std::vector<float> v1, v2, v3, v4;
  for (int i = 0; i < numPoints; ++i)
  {
    table->SetValue(i, 0, i * inc);
    table->SetValue(i, 1, cos(i * inc));
    table->SetValue(i, 2, sin(i * inc));
	v1.push_back(i*inc);
	v2.push_back(cos(v1[i]));
	v3.push_back(sin(v1[i]));
	v4.push_back(i);
  }
 
  v2.push_back(7.1);
  v2.push_back(7.5);

  for (int i = 0; i < numPoints; i++)
	  v3.push_back(sin(v1[i]));

  v4.push_back(70);
  v4.push_back(71);
  v4.push_back(72);

  std::map<std::string, std::vector<float>*> map;
  map["v1"] = &v1;
  map["v2"] = &v2;
  map["v3"] = &v3;
  map["v4"] = &v4;

  
  for (std::map<std::string, std::vector<float>*>::iterator itr = map.begin(); itr != map.end(); ++itr)
  {
	  std::for_each(itr->second->begin(), itr->second->end(), [](float v) {cout << v << " "; });
	  std::cout << " written " << std::endl;
  }

  // Set up the view
  vtkSmartPointer<vtkContextView> view = 
    vtkSmartPointer<vtkContextView>::New();
  view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
 
  // Add multiple line plots, setting the colors etc
  vtkSmartPointer<vtkChartXY> chart = 
    vtkSmartPointer<vtkChartXY>::New();
  view->GetScene()->AddItem(chart);
  vtkPlot *line = chart->AddPlot(vtkChart::LINE);
  line->SetInputData(table, 0, 1);
  line->SetColor(0, 255, 0, 255);
  line->SetWidth(1.0);
  line = chart->AddPlot(vtkChart::LINE);
  line->SetInputData(table, 0, 2);
  line->SetColor(255, 0, 0, 255);
  line->SetWidth(5.0);

  CreateChart(chart, &map);

  // For dotted line, the line type can be from 2 to 5 for different dash/dot
  // patterns (see enum in vtkPen containing DASH_LINE, value 2):
#ifndef WIN32
  line->GetPen()->SetLineType(vtkPen::DASH_LINE);
#endif
  // (ifdef-ed out on Windows because DASH_LINE does not work on Windows
  //  machines with built-in Intel HD graphics card...)

  //view->GetRenderWindow()->SetMultiSamples(0);

  // Start interactor
  view->GetRenderWindow()->Render();
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();
 
  return EXIT_SUCCESS;
}
