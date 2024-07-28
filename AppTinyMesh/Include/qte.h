#ifndef __Qte__
#define __Qte__

#include <QtWidgets/qmainwindow.h>
#include "realtime.h"
#include "meshcolor.h"
#include "myFile/SDF.h"
QT_BEGIN_NAMESPACE
	namespace Ui { class Assets; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
  Ui::Assets* uiw;           //!< Interface

  MeshWidget* meshWidget;   //!< Viewer
  MeshColor meshColor;		//!< Mesh.

public:
  MainWindow();
  ~MainWindow();
  void CreateActions();
  void UpdateGeometry();

public slots:
  void editingSceneLeft(const Ray&);
  void editingSceneRight(const Ray&);
  void BoxMeshExample();
  void SphereImplicitExample();
  //creation nouvelle :
    void Minion();
    void Oeil();
    void Yokai();
    void Tester();
    //primitif
    void Sphere_example();
    void Infinite_cylinder_example();
    void Capsule_example();
    void Finite_cylinder_example();
    //operation
    void Union_example();
    void Smooth_union_example();
    void Intersection_example();
    void Smooth_intersection_example();
    void Difference_example();
    void Smooth_difference_example();

    void Generer_node(Node *n);

  void ResetCamera();
  void UpdateMaterial();
};

#endif
