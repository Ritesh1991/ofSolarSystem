#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"


// Class of an astronomical object
class AstrObject
{
public:
    AstrObject(const string & name, const ofQuaternion & rot, double radius, const string & texture, unsigned orbit=0, const ofVec3f & p_pos=ofVec3f(0,0,0));
    ~AstrObject();

    // Getters
    const string &name()
    {
        return m_name;
    }
    double orbit()
    {
        return m_orbit;
    }
    double orbitRadius()
    {
        return m_orbitRadius;
    }
    const vector<ofQuaternion> & rotations()
    {
        return m_rotations;
    }
    double radius()
    {
        return m_obj.getRadius();
    }
    const ofVec3f position()
    {
        return m_obj.getPosition();    // doesn't return reference because would return temporary
    }
    ofImage &texture()
    {
        return m_texture;
    }
    ofSpherePrimitive & object()
    {
        return m_obj;
    }
    unsigned materialId()
    {
        return m_matId;
    }
    AstrObject *parent()
    {
        return m_parent;
    }
    bool    isSatellite()
    {
        return (m_parent != NULL);
    }
    bool    rotates()
    {
        return (m_rotations.size() != 0);
    }
    double  orbitSpeedFactor()
    {
        return m_orbitSpeedFactor;
    }
    double  rotationSpeedFactor()
    {
        return m_rotationSpeedFactor;
    }
    double  sizeFactor()
    {
        return m_sizeFactor;
    }

    // Setters
    void setRadius(double radius);
    void setRotations(const vector<ofQuaternion> & rots);
    void addRotation(const ofQuaternion & rot);
    void setOrbit(double orbit);
    void setOrbitRadius(double orbitRadius);
    void setTexture(const string & imagePath);
    void setPosition(const ofVec3f & pos);
    void setParent(AstrObject * parent, const ofVec3f & orbitCoords, double orbitPeriod=0, bool objParent=false);
    void setMaterialId(unsigned id);
    void setOrbitSpeedFactor(double newOSF);
    void setRotationSpeedFactor(double newRSF);

private:
    string m_name;
    double m_orbit;
    double m_orbitRadius;
    vector<ofQuaternion> m_rotations;
    double m_radius;
    ofImage m_texture;
    ofVec3f m_pos;
    ofSpherePrimitive m_obj;
    AstrObject *m_parent;
    vector<AstrObject *> m_sats;
    unsigned m_matId;
    double m_orbitSpeedFactor;
    double m_rotationSpeedFactor;
    double m_sizeFactor;
};


// Defining names to use as indexes to be more understandable
typedef enum Astres
{
    SUN = 0,
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE,
    MOON,
    CALLISTO,
    EUROPA,
    GANYMEDE,
    IO
} Astres;

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		// Drawing functions
		//------------------
		void draw();
		void drawScene(unsigned camNbr);
		void drawSaturnRing();
		void drawStars();
		void drawBorgFleet();
        //------------------
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// Dialog functions
		//------------------
        void manageDialog();
        void resetDialog(void (testApp::*newDialogFunc)(int));
        void defaultText(int code);
        void cameraText(int code);
        void changeCamTargetText(int code);
        void rotationText(int code);
        void scalingText(int code);
        void effectsText(int code);

        // Camera functions
        //-----------------
        void setupViewports();

        // Mouse picking functions
        //-------------------------
        int mousePickPlanet();
        void mousePickCamTarget(int x, int y, int button);
        void mousePickRotationTarget(int x, int y, int button);
        void mousePickScalingTarget(int x, int y, int button);


        // Objects
        vector<AstrObject *>  objects;
        ofSpherePrimitive stars;
        ofImage starTex;
        vector<ofMaterial> materials;
        ofLight pointLight;
        // Display configuration booleans & dialog
        bool bInfoText;
        bool bDrawOrbits;
        bool bMousePicking;
        bool bFullStop;
        bool bSaturnRing;
        stringstream dialog;
        // Callback functions
        void (testApp::*dialogFunc)(int);
        void (testApp::*buttonPressedFunc)(int, int, int);
        // Camera stuff
        ofEasyCam cams[4];
        int camTargetIds[4];
        ofRectangle viewports[4];
        unsigned n_cams;
        // Targets of operations
        unsigned targetCam;
        int mousePickedPlanet;
        int rotationTarget;
        // Special effects variables
        ofBoxPrimitive borgFleet[10];
        ofxAssimpModelLoader enterprise;
        ofImage borgImg;
        bool bDrawBorgs;
        ofSoundPlayer player;
        ofVideoPlayer vplayer;
};
