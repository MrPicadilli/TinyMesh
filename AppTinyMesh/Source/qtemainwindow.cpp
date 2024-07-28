#include "qte.h"
#include "implicits.h"
#include "myFile/Node.h"
#include "myFile/Primitive.h"
#include "myFile/Operation.h"
#include "myFile/SDF.h"
#include "myFile/Transform.h"
#include "myFile/repeat.h"
#include "myFile/Bezier.h"
#include "ui_interfaceFlorent.h"

MainWindow::MainWindow() : QMainWindow(), uiw(new Ui::Assets)
{
	// Chargement de l'interface
    uiw->setupUi(this);

	// Chargement du GLWidget
	meshWidget = new MeshWidget;
	QGridLayout* GLlayout = new QGridLayout;
	GLlayout->addWidget(meshWidget, 0, 0);
	GLlayout->setContentsMargins(0, 0, 0, 0);
    uiw->widget_GL->setLayout(GLlayout);

	// Creation des connect
	CreateActions();

	meshWidget->SetCamera(Camera(Vector(10, 0, 0), Vector(0.0, 0.0, 0.0)));
}

MainWindow::~MainWindow()
{
	delete meshWidget;
}
/*
void MainWindow::CreateActions()
{
	// Buttons
    connect(uiw->boxMesh, SIGNAL(clicked()), this, SLOT(BoxMeshExample()));
    connect(uiw->sphereImplicit, SIGNAL(clicked()), this, SLOT(SphereImplicitExample()));
    connect(uiw->resetcameraButton, SIGNAL(clicked()), this, SLOT(ResetCamera()));
    connect(uiw->wireframe, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_1, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_2, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));

	// Widget edition
	connect(meshWidget, SIGNAL(_signalEditSceneLeft(const Ray&)), this, SLOT(editingSceneLeft(const Ray&)));
	connect(meshWidget, SIGNAL(_signalEditSceneRight(const Ray&)), this, SLOT(editingSceneRight(const Ray&)));
}
*/
void MainWindow::CreateActions()
{
    // Buttons
    connect(uiw->boxMesh, SIGNAL(clicked()), this, SLOT(BoxMeshExample()));
    connect(uiw->resetcameraButton, SIGNAL(clicked()), this, SLOT(ResetCamera()));

    //creativite
    connect(uiw->minion, SIGNAL(clicked()), this, SLOT(Minion()));
    connect(uiw->Oeil, SIGNAL(clicked()), this, SLOT(Oeil()));
    connect(uiw->Yokai, SIGNAL(clicked()), this, SLOT(Yokai()));
    connect(uiw->tester, SIGNAL(clicked()), this, SLOT(Tester()));

    //primitives
    connect(uiw->Sphere, SIGNAL(clicked()), this, SLOT(Sphere_example()));
    connect(uiw->Capsule, SIGNAL(clicked()), this, SLOT(Capsule_example()));
    connect(uiw->Cylindre_infini, SIGNAL(clicked()), this, SLOT(Infinite_cylinder_example()));
    connect(uiw->Cylindre_fini, SIGNAL(clicked()), this, SLOT(Finite_cylinder_example()));

    //operation
    connect(uiw->Exemple_union, SIGNAL(clicked()), this, SLOT(Union_example()));
    connect(uiw->Exemple_smooth_union, SIGNAL(clicked()), this, SLOT(Smooth_union_example()));
    connect(uiw->Exemple_intersection, SIGNAL(clicked()), this, SLOT(Intersection_example()));
    connect(uiw->Exemple_smooth_intersection, SIGNAL(clicked()), this, SLOT(Smooth_intersection_example()));
    connect(uiw->Exemple_difference, SIGNAL(clicked()), this, SLOT(Difference_example()));
    connect(uiw->Smooth_difference, SIGNAL(clicked()), this, SLOT(Smooth_difference_example()));

    //
    connect(uiw->wireframe, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_1, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_2, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));

    // Widget edition
    connect(meshWidget, SIGNAL(_signalEditSceneLeft(const Ray&)), this, SLOT(editingSceneLeft(const Ray&)));
    connect(meshWidget, SIGNAL(_signalEditSceneRight(const Ray&)), this, SLOT(editingSceneRight(const Ray&)));
}

void MainWindow::editingSceneLeft(const Ray&)
{
}

void MainWindow::editingSceneRight(const Ray&)
{
}

void MainWindow::BoxMeshExample()
{
	Mesh boxMesh = Mesh(Box(1.0));

	QVector<Color> cols;
	cols.resize(boxMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
		cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

	meshColor = MeshColor(boxMesh, cols, boxMesh.VertexIndexes());
	UpdateGeometry();
}

void MainWindow::SphereImplicitExample()
{
  AnalyticScalarField implicit;

  Mesh implicitMesh;
  implicit.Polygonize(31, implicitMesh, Box(2.0));

  QVector<Color> cols;
  cols.resize(implicitMesh.Vertexes());
  for (size_t i = 0; i < cols.size(); i++)
    cols[i] = Color(0.8, 0.8, 0.8);

  meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
  UpdateGeometry();
}


void MainWindow::Minion()
{
    Sphere* oeil_gauche = new Sphere(Vector(0, -2.5, 1), 1.0);
    Capsule* body = new Capsule(Vector(0, 0, 2), Vector(0, 0, -2), 3.0);

    Smooth_union* attache_oeil_gauche = new Smooth_union(oeil_gauche, body,0.5);

    Cone_capped* jambe_gauche = new Cone_capped(Vector(-1,0,-4),Vector(-1,0,-6), 1.0, 0.5);
    Cone_capped* jambe_droite = new Cone_capped(Vector(1, 0, -4), Vector(1, 0, -6), 1.0, 0.5);

    Smooth_union* attache_jambe = new Smooth_union(jambe_gauche, jambe_droite,2);

    Capsule* pied_gauche = new Capsule(Vector(-1, 0, -6), Vector(-1, -1, -6), 0.5);
    Capsule* pied_droit = new Capsule(Vector(1, 0, -6), Vector(1, -1, -6), 0.5);

    Union* attache_pied = new Union(pied_droit, pied_gauche);

    Capsule* bras_droit = new Capsule(Vector(-3, 0, 0), Vector(-4, 0, 4), 0.75);
    Capsule* bras_gauche = new Capsule(Vector(3, 0, 0), Vector(4, 0, 4), 0.75);

    Union* attache_bras = new Union(bras_droit, bras_gauche);

    Union* attache_bas_corps = new Union(attache_pied, attache_jambe);
    Smooth_union* attache_jambe_corp = new Smooth_union(attache_bas_corps, attache_oeil_gauche,1.5);

    Union* attache_bras_corp = new Union(attache_bras, attache_jambe_corp);


    SDF implicit(attache_bras_corp);
    Mesh implicitMesh;
    implicit.Polygonize(104, implicitMesh, Box(10.0));

    QVector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(0.8, 0.8, 0.8);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();

}
/* a faire encore :
* recursivite
* noise
* oeil sur la planete
* distortion
* erosion ou ajout par lancer de rayon
*/

void MainWindow::Oeil()
{
    Seed* contour = new Seed(Vector(0, 0, 0), Vector(0, 0, 0), 3);
    Cone_capped* cone = new Cone_capped(Vector(0, 0, 0), Vector(5, 0, 0), 0, 6);
    Smooth_substract* receptacle = new Smooth_substract(cone, contour, 1);
    Sphere* globe = new Sphere(Vector(1.3, 0, 0), 2);
    Smooth_union* oeil = new Smooth_union(receptacle, globe, 0.5);
    Generer_node(oeil);

}

void MainWindow::Tester()
{

    Mesh boxMesh = Mesh(Box(1.0));
    Seed* s1 = new Seed(Vector(0, 0, 0), Vector(0, 0, 0), 3);
    Ray_marching r1 = Ray_marching(s1, Vector(-10,0,0));
    Sphere_tracing rs1 = Sphere_tracing(s1, Vector(-10, 0, 0));

    Vector toucher = r1.Intercept(Vector(1, 0, 0));
    Vector touchers = rs1.Intercept(Vector(1, 0, 0));

    //Sphere* touch = new Sphere(toucher, 1);
    Ray_marching_machine_gun machine = Ray_marching_machine_gun(s1);

    Torsion_helico* contour = new Torsion_helico(s1,1);
    //Node* x = machine.generate_shot(20);
    Union* fini = new Union(machine.add_matiere_sphere_tracing(10), s1);
    Union* fini2 = new Union(machine.remove_matiere_ray_marching(10), s1);

    //Union* fini = new Union(touch, s1);

    Sphere* globe = new Sphere(Vector(0, 0, 0), 3);
    Noise* noise = new Noise(globe);



    Capsule* cap1 = new Capsule(Vector(0, -20, 0), Vector(0, 20, 0), 1.0);
    Capsule* cap2 = new Capsule(Vector(-20, 0, 0), Vector(20, 0, 0), 1.0);
    Melange* intersec = new Melange(cap1, cap2);

    Generer_node(fini2);

}

void MainWindow::Yokai()
{

    Capsule* cap = new Capsule(Vector(-1, 0, 0), Vector(1, 0, 0), 0.5);
    //Sphere* s1 = new Sphere(Vector(0, 0, 0), 0.5);
    Transform t = Translation(1, 0, 1);

    Seed* contour = new Seed(Vector(0, 0, 0), Vector(0, 0, 0), 3);
    Cone_capped* cone = new Cone_capped(Vector(0, 0, 0), Vector(5, 0, 0), 0, 6);
    Smooth_substract* receptacle = new Smooth_substract(cone, contour, 1);
    Sphere* globe = new Sphere(Vector(1.3, 0, 0), 2);
    Smooth_union* oeil = new Smooth_union(receptacle, globe, 0.5);
    Transform x = Scale(-5.0);
    Deformation* def = new Deformation(oeil, x);

    Deformation* defo = new Deformation(def, RotationZ(270));
    Infinite_repeat* infini = new Infinite_repeat(defo, 10);
    Clone* clo = new Clone(defo, t);
    Node* inf = infini->repeater(defo, 12,6.0, 14);
    Sphere* monde = new Sphere(Vector(0, 0, 0), 6);
    Union* yokai = new Union(monde, inf);


    //Intersection* u = new Intersection(e1, e2);
    //Union* def_cil = new Union(inf, cil);

    //std::cout << a << std::endl;
    Generer_node(yokai);

}
//primitive
void MainWindow::Sphere_example()
{
    Sphere* sphere = new Sphere(Vector(0, 0, 0), 3.0);
    Generer_node(sphere);

}

void MainWindow::Infinite_cylinder_example()
{
    Infinite_cylinder* cyl = new Infinite_cylinder(Vector(0, -4, 0), Vector(0, 4, 0), 1.0);
    Generer_node(cyl);
}

void MainWindow::Capsule_example()
{
    Capsule* cap1 = new Capsule(Vector(0, -4, 0), Vector(0, 4, 0), 1.0);
    Generer_node(cap1);
}

void MainWindow::Finite_cylinder_example()
{
    Cone_capped* cap1 = new Cone_capped(Vector(0, -4, 0), Vector(0, 4, 0),1,2);
    Generer_node(cap1);
}

//operation
void MainWindow::Union_example()
{
    Capsule* cap1 = new Capsule(Vector(0, -20, 0), Vector(0, 20, 0), 1.0);
    Capsule* cap2 = new Capsule(Vector(-20, 0, 0), Vector(20, 0, 0), 1.0);
    Union* uni = new Union(cap1, cap2);
    Generer_node(uni);
}

void MainWindow::Smooth_union_example()
{
    Capsule* cap1 = new Capsule(Vector(0, -20, 0), Vector(0, 20, 0), 1.0);
    Capsule* cap2 = new Capsule(Vector(-20, 0, 0), Vector(20, 0, 0), 1.0);
    Smooth_union* sm_uni = new Smooth_union(cap1, cap2,2);
    Generer_node(sm_uni);
}

void MainWindow::Intersection_example()
{
    Capsule* cap1 = new Capsule(Vector(0, -20, 0), Vector(0, 20, 0), 1.0);
    Capsule* cap2 = new Capsule(Vector(-20, 0, 0), Vector(20, 0, 0), 1.0);
    Intersection* intersec = new Intersection(cap1, cap2);
    Generer_node(intersec);
}

void MainWindow::Smooth_intersection_example()
{
    Capsule* cap1 = new Capsule(Vector(0, -20, 0), Vector(0, 20, 0), 1.0);
    Capsule* cap2 = new Capsule(Vector(-20, 0, 0), Vector(20, 0, 0), 1.0);
    Smooth_intersection* sm_intersec = new Smooth_intersection(cap1, cap2, 0.5);
    Generer_node(sm_intersec);
}

void MainWindow::Difference_example()
{
    Capsule* cap1 = new Capsule(Vector(0, -20, 0), Vector(0, 20, 0), 1.0);
    Capsule* cap2 = new Capsule(Vector(-20, 0, 0), Vector(20, 0, 0), 1.0);
    Substract* difference = new Substract(cap1, cap2);
    Generer_node(difference);

}

void MainWindow::Smooth_difference_example()
{
    Capsule* cap1 = new Capsule(Vector(0, -20, 0), Vector(0, 20, 0), 1.0);
    Capsule* cap2 = new Capsule(Vector(-20, 0, 0), Vector(20, 0, 0), 1.0);
    Smooth_substract* sm_difference = new Smooth_substract(cap1, cap2, 1);
    Generer_node(sm_difference);
}

void MainWindow::Generer_node(Node* n)
{
    SDF implicit(n);

    Mesh implicitMesh;
    implicit.Polygonize(208, implicitMesh, Box(10.0));

    QVector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (int i = 0; i < cols.size(); i++)
        cols[i] = Color(0.8, 0.8, 0.8);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();

}






void MainWindow::UpdateGeometry()
{
	meshWidget->ClearAll();
	meshWidget->AddMesh("BoxMesh", meshColor);

    uiw->lineEdit->setText(QString::number(meshColor.Vertexes()));
    uiw->lineEdit_2->setText(QString::number(meshColor.Triangles()));

	UpdateMaterial();
}

void MainWindow::UpdateMaterial()
{
    meshWidget->UseWireframeGlobal(uiw->wireframe->isChecked());

    if (uiw->radioShadingButton_1->isChecked())
		meshWidget->SetMaterialGlobal(MeshMaterial::Normal);
	else
		meshWidget->SetMaterialGlobal(MeshMaterial::Color);
}

void MainWindow::ResetCamera()
{
	meshWidget->SetCamera(Camera(Vector(-10.0), Vector(0.0)));
}
