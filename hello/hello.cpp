#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include <vector>

#ifdef dDOUBLE
#define dsDrawSphere dsDrawSphereD
#define dsDrawBox dsDrawBoxD
#define dsDrawCylinder dsDrawCylinderD
#define dsDrawCapsule dsDrawCapsuleD
#define dsDrawLine dsDrawLineD
#endif

class Shape {
public:
  virtual void draw() = 0;
};

class Sphere : public Shape {
protected:
  dBodyID m_body;
  dGeomID m_geom;

public:
  Sphere(dWorldID world, dSpaceID space) {
    dReal radius = 0.5;

    // 生成
    m_body = dBodyCreate( world );
    m_geom = dCreateSphere(space, radius);
    dGeomSetBody(m_geom, m_body);

    // 位置設定
    dBodySetPosition(m_body, -3.0, 0.0, 3.0);

    // 質量設定
    dMass m;
    dMassSetZero(&m);
    dMassSetSphereTotal(&m, 1.0, radius);
    dBodySetMass(m_body, &m);
  }
  ~Sphere() {
    dBodyDestroy(m_body);
    dGeomDestroy(m_geom);
  }

  virtual void draw() {
    //dsSetTexture (DS_CHECKERED);
    dsSetTexture (DS_WOOD);
    //dsSetColor( 1.0f, 1.0f, 0.0f ); // RGB Color
    dsSetColorAlpha(0.75, 0.3, 0.3, 1.0);
    dsDrawSphere( dGeomGetPosition( m_geom ),
        dGeomGetRotation( m_geom ),
        dGeomSphereGetRadius(m_geom) );
  }
};

class Box : public Shape {
protected:
  dBodyID m_body;
  dGeomID m_geom;

public:
  Box(dWorldID world, dSpaceID space) {
    dVector3 lengths = {1.0, 1.0, 1.0};

    // 生成
    m_body = dBodyCreate( world );
    m_geom = dCreateBox(space, lengths[0], lengths[1], lengths[2]);
    dGeomSetBody(m_geom, m_body);

    // 質量設定
    dMass m;
    dMassSetZero(&m);
    dMassSetBoxTotal(&m, 1.0, lengths[0], lengths[1], lengths[2]);
    dBodySetMass(m_body, &m);

    // 位置設定
    dBodySetPosition(m_body, -1.0, 0.0, 3.0);
    // 姿勢設定
//    dMatrix3 r, r1, r2, r3, r4;
//    dRFromAxisAndAngle(r1, 1.0, 0.0, 0.0, 0.0*M_PI/180.0); // x-axis
//    dRFromAxisAndAngle(r2, 0.0, 1.0, 0.0, 0.0*M_PI/180.0); // y-axis
//    dRFromAxisAndAngle(r3, 0.0, 0.0, 1.0, 0.0*M_PI/180.0); // z-axis
//    dMultiply0_333(r4, r1, r2);
//    dMultiply0_333(r, r3, r4);
//    dBodySetRotation(m_body, r);
    dQuaternion q, q1, q2, q3, q4;
    dQFromAxisAndAngle(q1, 1.0, 0.0, 0.0, 0.0*M_PI/180.0); // x-axis
    dQFromAxisAndAngle(q2, 0.0, 1.0, 0.0, 0.0*M_PI/180.0); // y-axis
    dQFromAxisAndAngle(q3, 0.0, 0.0, 1.0, 45.0*M_PI/180.0); // z-axis
    dQMultiply0(q4, q1, q2);
    dQMultiply0(q, q3, q4);
    dBodySetQuaternion(m_body, q);
  }
  ~Box() {
    dBodyDestroy(m_body);
    dGeomDestroy(m_geom);
  }

  virtual void draw() {
    dVector3 lengths;
    dGeomBoxGetLengths(m_geom, lengths);
    //dsSetTexture (DS_CHECKERED);
    dsSetTexture (DS_WOOD);
    //dsSetColor( 1.0f, 1.0f, 0.0f ); // RGB Color
    dsSetColorAlpha(0, 0.75, 0.5, 1.0);
    dsDrawBox( dGeomGetPosition( m_geom ),
        dGeomGetRotation( m_geom ),
        lengths );
  }
};

class Cylinder : public Shape {
protected:
  dBodyID m_body;
  dGeomID m_geom;

public:
  Cylinder(dWorldID world, dSpaceID space) {
    dReal radius = 0.5;
    dReal length = 1.0;

    // 生成
    m_body = dBodyCreate( world );
    m_geom = dCreateCylinder(space, radius, length);
    dGeomSetBody(m_geom, m_body);

    // 質量設定
    dMass m;
    dMassSetZero(&m);
    dMassSetCylinderTotal(&m, 1.0, 1, radius, length);
    dBodySetMass(m_body, &m);

    // 位置設定
    dBodySetPosition(m_body, 1.0, 0.0, 3.0);

    // 姿勢設定
    dQuaternion q, q1, q2, q3, q4;
    dQFromAxisAndAngle(q1, 1.0, 0.0, 0.0, 0.0*M_PI/180.0); // x-axis
    dQFromAxisAndAngle(q2, 0.0, 1.0, 0.0, 0.0*M_PI/180.0); // y-axis
    dQFromAxisAndAngle(q3, 0.0, 0.0, 1.0, 0.0*M_PI/180.0); // z-axis
    dQMultiply0(q4, q1, q2);
    dQMultiply0(q, q3, q4);
    dBodySetQuaternion(m_body, q);
  }
  ~Cylinder() {
    dBodyDestroy(m_body);
    dGeomDestroy(m_geom);
  }

  virtual void draw() {
    dReal radius, length;
    dGeomCylinderGetParams(m_geom, &radius, &length);
    //dsSetTexture (DS_CHECKERED);
    dsSetTexture (DS_WOOD);
    //dsSetColor( 1.0f, 1.0f, 0.0f ); // RGB Color
    dsSetColorAlpha(0.75, 0.75, 0.3, 1.0);
    dsDrawCylinder( dGeomGetPosition( m_geom ),
        dGeomGetRotation( m_geom ),
        length, radius );
  }
};

class Capsule : public Shape {
protected:
  dBodyID m_body;
  dGeomID m_geom;

public:
  Capsule(dWorldID world, dSpaceID space) {
    dReal radius = 0.5;
    dReal length = 1.0;

    // 生成
    m_body = dBodyCreate( world );
    m_geom = dCreateCapsule(space, radius, length);
    dGeomSetBody(m_geom, m_body);

    // 質量設定
    dMass m;
    dMassSetZero(&m);
    dMassSetCapsuleTotal(&m, 1.0, 1, radius, length);
    dBodySetMass(m_body, &m);

    // 位置設定
    dBodySetPosition(m_body, 3.0, 0.0, 3.0);

    // 姿勢設定
    dQuaternion q, q1, q2, q3, q4;
    dQFromAxisAndAngle(q1, 1.0, 0.0, 0.0, 0.0*M_PI/180.0); // x-axis
    dQFromAxisAndAngle(q2, 0.0, 1.0, 0.0, 0.0*M_PI/180.0); // y-axis
    dQFromAxisAndAngle(q3, 0.0, 0.0, 1.0, 0.0*M_PI/180.0); // z-axis
    dQMultiply0(q4, q1, q2);
    dQMultiply0(q, q3, q4);
    dBodySetQuaternion(m_body, q);
  }
  ~Capsule() {
    dBodyDestroy(m_body);
    dGeomDestroy(m_geom);
  }

  virtual void draw() {
    dReal radius, length;
    dGeomCapsuleGetParams(m_geom, &radius, &length);
    //dsSetTexture (DS_CHECKERED);
    dsSetTexture (DS_WOOD);
    //dsSetColor( 1.0f, 1.0f, 0.0f ); // RGB Color
    dsSetColorAlpha(0.75, 0.75, 0.75, 1.0);
    dsDrawCapsule( dGeomGetPosition( m_geom ),
        dGeomGetRotation( m_geom ),
        length, radius );
  }
};

static std::vector<Shape*> shapeList;
static dWorldID world;
static dSpaceID space;
static dJointGroupID contact_group;

// 衝突検出用関数
static void nearCallback( void *data, dGeomID o1, dGeomID o2 )
{
  static const int MAX_CONTACTS = 4;
  dBodyID b1 = dGeomGetBody( o1 );
  dBodyID b2 = dGeomGetBody( o2 );

  if ( b1 && b2 && dAreConnectedExcluding( b1, b2, dJointTypeContact ) )
    return;

  dContact contact[MAX_CONTACTS];
  int numc = dCollide( o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof( dContact ) ); 
  if (numc > 0) {
    for (int i=0; i<numc; i++) {
      // 物体同士の接触時のパラメータ設定
      contact[i].surface.mode = dContactBounce | dContactSoftCFM;
      contact[i].surface.mu = dInfinity;   // 摩擦係数
      contact[i].surface.bounce = 0.5;     // 反発係数
      contact[i].surface.soft_cfm = 0.01;  // CFM設定
      // 衝突の発生
      dJointID c = dJointCreateContact( world, contact_group, contact+i );
      // 接触ジョイント生成
      dJointAttach( c, b1, b2 ); // 接触ジョイント接続
    }
  }
}

// start simulation - set viewpoint
static void start()
{
  static float xyz[3] = { 0.f, 5.f, 3.f };
  static float hpr[3] = { -90.f, -15.f, 0.f };

  dsSetViewpoint( xyz, hpr ); // カメラ位置と方向設定
}

// simulation loop
static void simLoop( int pause )
{
  // Ctl+p が押されたらifに入らない
  if (!pause) {
    dSpaceCollide( space, 0, &nearCallback ); // 衝突検出
    dWorldStep( world, 0.01 );
    dJointGroupEmpty( contact_group );
  }

  // Shapeの表示
  std::vector<Shape*>::iterator it = shapeList.begin();
  while (it != shapeList.end()) {
    (*it)->draw();
    ++it;
  }
}


int main( int argc, char* argv[] )
{
  // setup pointers to drawstuff callback functions
  dsFunctions fn;
  fn.version = DS_VERSION;
  fn.start   = &start;
  fn.step    = &simLoop;
  fn.command = 0;
  fn.stop    = 0;
  fn.path_to_textures = "../textures";

  // ODE初期化
  dInitODE2(0);
  dAllocateODEDataForThread(dAllocateMaskAll);

  // World,Space生成
  world = dWorldCreate();
  dWorldSetGravity(world, 0.0, 0.0, -9.8);
  dWorldSetCFM (world,1e-5);
  dWorldSetLinearDamping(world, 0.00001);
  dWorldSetAngularDamping(world, 0.005);
  dWorldSetMaxAngularSpeed(world, 200);
  dWorldSetERP(world, 0.2);
  dWorldSetContactSurfaceLayer (world,0.001);
  space = dSimpleSpaceCreate (0);
  contact_group = dJointGroupCreate(0);

  // 地面生成
  dCreatePlane(space, 0, 0, 1, 0);

  // シェイプ生成
  shapeList.push_back(new Box(world, space));
  shapeList.push_back(new Sphere(world, space));
  shapeList.push_back(new Cylinder(world, space));
  shapeList.push_back(new Capsule(world, space));

  dsSimulationLoop(argc, argv, 320, 240, &fn);

  dJointGroupDestroy(contact_group);
  dWorldDestroy(world);
  dSpaceDestroy(space);
  return 0;
}

