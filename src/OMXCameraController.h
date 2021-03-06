#pragma once

#include "ofxOMXCameraSettings.h"
#include "DisplayController.h"
#include "ImageFXController.h"

enum MIRROR
{
    MIRROR_NONE=OMX_MirrorNone,
    MIRROR_VERTICAL=OMX_MirrorVertical,
    MIRROR_HORIZONTAL=OMX_MirrorHorizontal,
    MIRROR_BOTH=OMX_MirrorBoth,
};

enum ROTATION
{
    ROTATION_0=0,
    ROTATION_90=90,
    ROTATION_180=180,
    ROTATION_270=270,
};


class OMXCameraController
{
public:
    
    OMXCameraController();
    virtual ~OMXCameraController(){};
    OMX_HANDLETYPE camera;

    int getLEDPin();
    bool hasGPIOProgram;
    ofxOMXCameraSettings settings;
    
    void checkBurstMode();
    void checkFlickerCancellation();
    OMX_ERRORTYPE applyMirror();

    OMX_ERRORTYPE applyRotation();
    OMX_ERRORTYPE applyCurrentMeteringMode();
    OMX_ERRORTYPE applyExposure();
    OMX_ERRORTYPE updateSensorCrop();
    
    OMX_CONFIG_EXPOSURECONTROLTYPE exposurePresetConfig;
    
    OMX_CONFIG_SHARPNESSTYPE sharpnessConfig;
    OMX_CONFIG_FRAMESTABTYPE framestabilizationConfig;
    OMX_CONFIG_CONTRASTTYPE contrastConfig;
    OMX_CONFIG_BRIGHTNESSTYPE brightnessConfig;
    OMX_CONFIG_SATURATIONTYPE saturationConfig;
    OMX_CONFIG_WHITEBALCONTROLTYPE whiteBalanceConfig;
    
    

    
    OMX_CONFIG_BOOLEANTYPE burstModeConfig;
    OMX_CONFIG_SCALEFACTORTYPE digitalZoomConfig;
    
    OMX_CONFIG_FLICKERCANCELTYPE flickerCancelConfig;
    OMX_CONFIG_DYNAMICRANGEEXPANSIONTYPE dreConfig;
    OMX_CONFIG_INPUTCROPTYPE sensorCropConfig;
    
    
    
    OMX_CONFIG_ROTATIONTYPE rotationConfig;
    OMX_CONFIG_MIRRORTYPE mirrorConfig;
    
    OMX_CONFIG_BOOLEANTYPE disableSoftwareSharpenConfig;
    OMX_CONFIG_BOOLEANTYPE disableSoftwareSaturationConfig;
    OMX_CONFIG_CUSTOMAWBGAINSTYPE whiteBalanceGainsConfig;
    
    
    void reset();
    void resetValues();
    void applyAllSettings();
    
    void setSharpness(int);
    int getSharpness() { return settings.sharpness; }
    
    void setContrast(int);
    int getContrast() { return settings.contrast; }
    
    void setBrightness(int);
    int getBrightness() { return settings.brightness; }
    
    void setSaturation(int);
    int getSaturation()        { return settings.saturation; }
    
    void setFrameStabilization(bool doStabilization);
    bool getFrameStabilization(){ return settings.frameStabilization;}
    
    
    
    void setDRE(int level);
    int getDRE() { return settings.dreLevel; }
    
    void toggleLED();
    void setLEDState(bool status);
    bool getLEDState() { return settings.LED; }
    
    OMX_ERRORTYPE setFlickerCancellation(OMX_COMMONFLICKERCANCELTYPE);
    void setFlickerCancellation(bool);
    void enableFlickerCancellation();
    void disableFlickerCancellation();
    bool isFlickerCancellationEnabled() { return settings.flickerCancellation; }
    //TODO: enable explict 50/60 hz
    
    
    OMX_ERRORTYPE setSensorCrop(ofRectangle&);
    ofRectangle& getDrawCropRectangle() { return settings.drawCropRectangle; }
    OMX_ERRORTYPE setSensorCrop(int left, int top, int width, int height);
    ofRectangle& getSensorCropRectangle() { return settings.sensorCropRectangle; }
    vector<int> zoomLevels;
    OMX_ERRORTYPE setDigitalZoom();
    OMX_ERRORTYPE zoomIn();
    OMX_ERRORTYPE zoomOut();
    OMX_ERRORTYPE resetZoom();
    OMX_ERRORTYPE setZoomLevelNormalized(float);
    float getZoomLevelNormalized();
    
    OMX_ERRORTYPE setMirror(int);
    OMX_ERRORTYPE setMirror(string);
    string getMirror();
    
    OMX_ERRORTYPE setRotation(int);
    OMX_ERRORTYPE setRotation(ROTATION);
    OMX_ERRORTYPE rotateClockwise();
    OMX_ERRORTYPE rotateCounterClockwise();
    int getRotation();
    
    
    void enableAnnotation();
    void setZeroShutterLag(bool value);
    OMX_ERRORTYPE setColorDenoise(bool doColorDenoise);
    
    
#pragma mark IMAGE FILTERS    
    ImageFXController imageFXController;
    ImageFXController extraImageFXController;
    
    OMX_ERRORTYPE setColorEnhancement(bool doEnhance, int u, int v);
    OMX_ERRORTYPE setImageFilter(OMX_IMAGEFILTERTYPE imageFilter_, vector<int>& params);
    OMX_ERRORTYPE setImageFilter(OMX_IMAGEFILTERTYPE);
    OMX_ERRORTYPE setImageFilter(string);
    string getImageFilter();
    
    OMX_ERRORTYPE setExtraImageFilter(string imageFilter);
    OMX_ERRORTYPE setExtraImageFilter(OMX_IMAGEFILTERTYPE imageFilter_, vector<int>& params);

    
    OMX_ERRORTYPE setExposurePreset(OMX_EXPOSURECONTROLTYPE);
    OMX_ERRORTYPE setExposurePreset(string);
    string getExposurePreset();
    
    OMX_ERRORTYPE setEvCompensation(int); //-4 to 4
    int getEvCompensation();
    
    OMX_ERRORTYPE setWhiteBalance(OMX_WHITEBALCONTROLTYPE);
    OMX_ERRORTYPE setWhiteBalance(string);
    string getWhiteBalance();
    OMX_ERRORTYPE setWhiteBalanceGainR(float);
    OMX_ERRORTYPE setWhiteBalanceGainB(float);
    float getWhiteBalanceGainR(){return settings.whiteBalanceGainR; }
    float getWhiteBalanceGainB(){return settings.whiteBalanceGainB; }

    OMX_ERRORTYPE setAutoShutter(bool);
    bool getAutoShutter();
    int getShutterSpeed();
    
    OMX_ERRORTYPE setShutterSpeed(int shutterSpeedMicroSeconds);
    OMX_ERRORTYPE setShutterSpeedNormalized(float value);
    float getShutterSpeedNormalized();

    OMX_ERRORTYPE setMeteringType(OMX_METERINGTYPE);
    OMX_ERRORTYPE setMeteringType(string);
    string getMeteringType();
    
    OMX_ERRORTYPE setSoftwareSharpening(bool);
    OMX_ERRORTYPE enableSoftwareSharpening();
    OMX_ERRORTYPE disableSoftwareSharpening();
    bool isSoftwareSharpeningEnabled() {return settings.doDisableSoftwareSharpen;}
    
    OMX_ERRORTYPE setSoftwareSaturation(bool);
    OMX_ERRORTYPE enableSoftwareSaturation();
    OMX_ERRORTYPE disableSoftwareSaturation();
    bool isSoftwareSaturationEnabled() {return settings.doDisableSoftwareSaturation;}
    
    void setBurstMode(bool);
    bool isBurstModeEnabled(){ return settings.burstModeEnabled;}
    
    vector<int>isoLevels;
    OMX_ERRORTYPE setISO(int ISO);
    int getISO();
    OMX_ERRORTYPE setISONormalized(float);
    float getISOLevelNormalized();
    
    OMX_ERRORTYPE setAutoISO(bool);
    bool getAutoISO();
    
    OMX_CONFIG_EXPOSUREVALUETYPE exposureConfig;
    
    
    string printExposure();
    
    string currentStateToString();
    void saveStateToFile(string fileName="");
    

    DisplayController displayController;
    void setDisplayAlpha(int);
    void setDisplayLayer(int);
    void setDisplayRotation(int);
    void setDisplayDrawRectangle(ofRectangle&);
    void setDisplayCropRectangle(ofRectangle&);
    void setDisplayMirror(bool);
    
    
    
    virtual void setup(ofxOMXCameraSettings&)=0;
    virtual void close() = 0;
    virtual bool isReady() = 0;;
    virtual void draw() =0;
    virtual void draw(int x, int y)=0;
    virtual void draw(int x, int y, int width, int height)=0;
    virtual void draw(ofRectangle&)=0;
    
    virtual int getWidth() = 0;
    virtual int getHeight()= 0;

    bool isTextureEnabled(){  return settings.enableTexture; }
    ofPixels& getPixels();
    GLuint getTextureID();
    ofTexture& getTextureReference();
    ofFbo& getFboReference();

    void enablePixels();
    void disablePixels();
    unsigned char * getRawPixels();
    bool pixelsRequested;
   
    
    int cameraOutputPort;
};

