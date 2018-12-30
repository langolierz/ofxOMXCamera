#pragma once

#include "OMX_Maps.h"

#define MEGABYTE_IN_BITS 8388608



class ofxOMXPhotoGrabberListener
{
public:
    virtual void onTakePhotoComplete(string filePath)=0;
    virtual void onPhotoGrabberEngineStart() = 0;
    
};

class ofxOMXVideoGrabberListener
{
public:
    virtual void onRecordingComplete(string filePath)=0;
};

class ofxOMXCameraSettings
{
public:
    
	int sensorWidth;
	int sensorHeight;
	int framerate;
    int sensorMode;
	
	bool enableTexture;
	bool enablePixels;
	string recordingFilePath;
    float recordingBitrateMB;
    bool LED;
    int LED_PIN;
    string meteringType;
    bool autoISO;
    int ISO;
    bool autoShutter;
    int shutterSpeed;
    int sharpness;   // -100 to 100
    int contrast;    // -100 to 100 
    int brightness;  //    0 to 100
    int saturation;  // -100 to 100 
    int dreLevel;    //   -4 to 4
    ofRectangle drawCropRectangle;
    ofRectangle drawRectangle;
    ofRectangle sensorCropRectangle;//percentage, e.g. 0, 0, 100(% width), 100(% sensorHeight)

    
    int zoomLevel;
    string mirror; 
    int rotation;
    string imageFilter;
    string extraImageFilter;
    string exposurePreset;
    int evCompensation;
    string whiteBalance;
    float whiteBalanceGainR;
    float whiteBalanceGainB;
    bool burstModeEnabled;
    bool flickerCancellation;
    bool frameStabilization;
    bool doDisableSoftwareSharpen;
    bool doDisableSoftwareSaturation;
    
    int stillPreviewWidth;
    int stillPreviewHeight;
    int stillQuality;
    bool enableRaw;
    bool enableStillPreview;
    string savedPhotosFolderName;
    int cameraDeviceID;
    float isoNormalized;
    float shutterSpeedNormalized;
    float zoomLevelNormalized;
    
    
    bool enableExtraVideoFilter;
    FilterParamConfig imageFilterParamConfig;
    FilterParamConfig extraImageFilterParamConfig;

    ofxOMXPhotoGrabberListener* photoGrabberListener;
    ofxOMXVideoGrabberListener* videoGrabberListener;

    
  
    int displayAlpha;
    int displayLayer;
	ofxOMXCameraSettings()
	{
        
        photoGrabberListener = NULL;
        videoGrabberListener = NULL;
        OMX_Init();
        resetValues();
        
        
        //ofJson test  = GetFilterParamConfigJson();
        
	}
	
    void resetValues()
    {
        sensorWidth = 1280;
        sensorHeight = 720;
        framerate = 30;
        sensorMode = 0;
        enableTexture = true;
        enablePixels = false;
        recordingFilePath = "";
        recordingBitrateMB = 2.0;
        exposurePreset = "Auto";
        meteringType = "Average";
        autoISO = true;
        ISO = 0;
        autoShutter = true;
        shutterSpeed = 0;
        sharpness=-50;
        contrast=-10;
        brightness=50;
        saturation=0;
        frameStabilization=false;
        flickerCancellation = false;
        whiteBalance="Auto";
        whiteBalanceGainR = 0;
        whiteBalanceGainB = 0;
        dreLevel=0;
        drawCropRectangle.set(0,0,0,0);
        sensorCropRectangle.set(0,0,100,100);

        
        zoomLevel=0;
        rotation=0;
        mirror="None";
        doDisableSoftwareSharpen = false;
        doDisableSoftwareSaturation = false;
        LED = false;
        stillPreviewWidth = 640;
        stillPreviewHeight = 480;
        stillQuality = 100;
        enableRaw = false;
        enableStillPreview = true;
        burstModeEnabled = false;
        savedPhotosFolderName = "photos";
        cameraDeviceID = 0;
        LED_PIN = 5; //RPI1: 5, RPI2: 32, RPI3: 134
        
        isoNormalized = 0;
        shutterSpeedNormalized = 0;
        zoomLevelNormalized = 0;
        displayAlpha = 255;
        displayLayer  = 0;
        imageFilter="None";
        enableExtraVideoFilter = false;
        extraImageFilter="None";
    }
    
    
    
    
    
    bool exists(ofJson& json, const string& key)
    {
        return json.find(key) != json.end();
    }
    bool parseJSON(const string& jsonString)
    {
        ofLog() << "jsonString: " << jsonString;
        
        ofJson json = ofJson::parse(jsonString);
        
        if(json.is_null())
        {
            return false;
        }
        if(exists(json, "sensorWidth")) sensorWidth = json["sensorWidth"].get<int>();
        if(exists(json, "sensorHeight")) sensorHeight = json["sensorHeight"].get<int>();
        if(exists(json, "framerate")) framerate = json["framerate"].get<int>();
        if(exists(json, "sensorMode")) sensorMode = json["sensorMode"].get<int>();
        
        if(exists(json, "enableTexture")) enableTexture = json["enableTexture"].get<bool>();
        if(exists(json, "enablePixels")) enablePixels = json["enablePixels"].get<bool>();
        
        
        if(exists(json, "exposurePreset")) exposurePreset = json["exposurePreset"].get<string>();
        if(exists(json, "meteringType")) meteringType = json["meteringType"].get<string>();
        if(exists(json, "imageFilter")) imageFilter = json["imageFilter"].get<string>();
        if(exists(json, "extraImageFilter")) extraImageFilter = json["extraImageFilter"].get<string>();
        if(exists(json, "imageFilterParamConfig")) imageFilterParamConfig.fromJSON(json["imageFilterParamConfig"]);
        if(exists(json, "extraImageFilterParamConfig")) extraImageFilterParamConfig.fromJSON(json["extraImageFilterParamConfig"]);

        
        
        if(exists(json, "autoISO")) autoISO = json["autoISO"].get<bool>();
        if(exists(json, "ISO")) ISO = json["ISO"].get<int>();
        
        
        if(exists(json, "autoShutter")) autoShutter = json["autoShutter"].get<bool>();
        if(exists(json, "shutterSpeed")) shutterSpeed = json["shutterSpeed"].get<int>();
        
        if(exists(json, "sharpness")) sharpness = json["sharpness"].get<int>();
        if(exists(json, "contrast")) contrast = json["contrast"].get<int>();
        if(exists(json, "brightness")) brightness = json["brightness"].get<int>();
        if(exists(json, "saturation")) saturation = json["saturation"].get<int>();

        
        if(exists(json, "frameStabilization")) frameStabilization = json["frameStabilization"].get<bool>();
        if(exists(json, "flickerCancellation")) flickerCancellation = json["flickerCancellation"].get<bool>();
        if(exists(json, "dreLevel")) dreLevel = json["dreLevel"].get<int>();
        if(exists(json, "drawCropRectangle"))
        {
            drawCropRectangle.set(json["drawCropRectangle"]["x"].get<int>(),
                              json["drawCropRectangle"]["y"].get<int>(),
                              json["drawCropRectangle"]["width"].get<int>(),
                              json["drawCropRectangle"]["height"].get<int>());

        }
        if(exists(json, "drawRectangle"))
        {
            drawRectangle.set(json["drawRectangle"]["x"].get<int>(),
                              json["drawRectangle"]["y"].get<int>(),
                              json["drawRectangle"]["width"].get<int>(),
                              json["drawRectangle"]["height"].get<int>());
            
        }
        if(exists(json, "sensorCropRectangle"))
        {
            sensorCropRectangle.set(json["sensorCropRectangle"]["x"].get<int>(),
                                    json["sensorCropRectangle"]["y"].get<int>(),
                                    json["sensorCropRectangle"]["width"].get<int>(),
                                    json["sensorCropRectangle"]["height"].get<int>());
            
        }
        
        if(exists(json, "zoomLevel")) zoomLevel = json["zoomLevel"].get<float>();
        if(exists(json, "rotation")) rotation = json["rotation"].get<int>();
        if(exists(json, "mirror")) mirror = json["mirror"].get<string>();
        if(exists(json, "doDisableSoftwareSharpen")) doDisableSoftwareSharpen = json["doDisableSoftwareSharpen"].get<bool>();
        if(exists(json, "doDisableSoftwareSaturation")) doDisableSoftwareSaturation = json["doDisableSoftwareSaturation"].get<bool>();
        if(exists(json, "LED")) LED = json["LED"].get<bool>();
        if(exists(json, "LED_PIN")) LED_PIN = json["LED_PIN"].get<int>();

        
        if(exists(json, "stillPreviewWidth")) stillPreviewWidth = json["stillPreviewWidth"].get<int>();
        if(exists(json, "stillPreviewHeight")) stillPreviewHeight = json["stillPreviewHeight"].get<int>();
        if(exists(json, "stillQuality")) stillQuality = json["stillQuality"].get<int>();
        if(exists(json, "enableRaw")) enableRaw = json["enableRaw"].get<bool>();
        if(exists(json, "enableStillPreview")) enableStillPreview = json["enableStillPreview"].get<bool>();
        if(exists(json, "burstModeEnabled")) burstModeEnabled = json["burstModeEnabled"].get<bool>();
        if(exists(json, "savedPhotosFolderName")) savedPhotosFolderName = json["savedPhotosFolderName"].get<string>();
        if(exists(json, "recordingBitrateMB")) recordingBitrateMB = json["recordingBitrateMB"].get<float>();
        if(exists(json, "cameraDeviceID")) cameraDeviceID = json["cameraDeviceID"].get<float>();
        if(exists(json, "whiteBalance")) whiteBalance = json["whiteBalance"].get<string>();
        if(exists(json, "whiteBalanceGainR")) whiteBalanceGainR = json["whiteBalanceGainR"].get<float>();
        if(exists(json, "whiteBalanceGainB")) whiteBalanceGainB = json["whiteBalanceGainB"].get<float>();
        if(exists(json, "isoNormalized")) isoNormalized = json["isoNormalized"].get<float>();
        if(exists(json, "shutterSpeedNormalized")) shutterSpeedNormalized = json["shutterSpeedNormalized"].get<float>();
        if(exists(json, "zoomLevelNormalized")) zoomLevelNormalized = json["zoomLevelNormalized"].get<float>();
        if(exists(json, "displayAlpha")) displayAlpha = json["displayAlpha"].get<int>();
        if(exists(json, "displayLayer")) displayLayer = json["displayLayer"].get<int>();
        if(exists(json, "enableExtraVideoFilter")) enableExtraVideoFilter = json["enableExtraVideoFilter"].get<bool>();

        
        
        return true;


    }   
    
    ofJson toJSON()
    {
        ofJson result;
        
        result["sensorWidth"]=sensorWidth;
        result["sensorHeight"]=sensorHeight;
        result["framerate"]=framerate;
        result["sensorMode"]=sensorMode;
        result["enableTexture"]=enableTexture;
        result["enablePixels"]=enablePixels;
        result["exposurePreset"]=exposurePreset;

        result["meteringType"]=meteringType;
        result["autoISO"]=autoISO;
        result["ISO"]=ISO;
        result["autoShutter"]=autoShutter;
        result["shutterSpeed"]=shutterSpeed;
        result["sharpness"]=sharpness;
        result["contrast"]=contrast;
        result["brightness"]=brightness;
        result["saturation"]=saturation;
        result["frameStabilization"]=frameStabilization;
        result["flickerCancellation"]=flickerCancellation;
        result["dreLevel"]=dreLevel;
        
        result["drawCropRectangle"]["x"]= drawCropRectangle.x;
        result["drawCropRectangle"]["y"]= drawCropRectangle.y;
        result["drawCropRectangle"]["width"]= drawCropRectangle.width;
        result["drawCropRectangle"]["height"]= drawCropRectangle.height;
        
        result["drawRectangle"]["x"]= drawRectangle.x;
        result["drawRectangle"]["y"]= drawRectangle.y;
        result["drawRectangle"]["width"]= drawRectangle.width;
        result["drawRectangle"]["height"]= drawRectangle.height;
        
        result["sensorCropRectangle"]["x"]= sensorCropRectangle.x;
        result["sensorCropRectangle"]["y"]= sensorCropRectangle.y;
        result["sensorCropRectangle"]["width"]= sensorCropRectangle.width;
        result["sensorCropRectangle"]["height"]= sensorCropRectangle.height;
        
        
        
        result["displayAlpha"] = displayAlpha;
        result["displayLayer"] = displayLayer;

        
        result["zoomLevel"]=zoomLevel;
        result["rotation"]=rotation;
        result["mirror"]=mirror;
        result["doDisableSoftwareSharpen"]=doDisableSoftwareSharpen;
        result["doDisableSoftwareSaturation"]=doDisableSoftwareSaturation;
        result["LED"]=LED;
        result["LED_PIN"]=LED_PIN;
        result["stillPreviewWidth"]=stillPreviewWidth;
        result["stillPreviewHeight"]=stillPreviewHeight;
        result["stillQuality"]=stillQuality;
        result["enableRaw"]=enableRaw;
        result["enableStillPreview"]=enableStillPreview;
        result["burstModeEnabled"]=burstModeEnabled;
        result["savedPhotosFolderName"]=savedPhotosFolderName;
        result["recordingBitrateMB"]=recordingBitrateMB;
        result["cameraDeviceID"]=cameraDeviceID;

        
        result["whiteBalance"]=whiteBalance;
        result["whiteBalanceGainR"]=whiteBalanceGainR;
        result["whiteBalanceGainB"]=whiteBalanceGainB;

        result["isoNormalized"]=isoNormalized;
        result["shutterSpeedNormalized"]=shutterSpeedNormalized;
        result["zoomLevelNormalized"]=zoomLevelNormalized;
        result["enableExtraVideoFilter"]=enableExtraVideoFilter;
        result["imageFilter"]=imageFilter;
        result["extraImageFilter"] = extraImageFilter;
        result["imageFilterParamConfig"] = imageFilterParamConfig.toJSON();
        result["extraImageFilterParamConfig"] = extraImageFilterParamConfig.toJSON();

        
        return result;
    }
    
    void saveJSONFile(string path="")
    {
        if(path == "")
        {
            path = "settings.json";
        }
        ofSavePrettyJson(path, toJSON());
    }
    
    string toString()
    {
        stringstream info;
        info << "sensorWidth " << sensorWidth << endl;
        info << "sensorHeight " << sensorHeight << endl;
        info << "framerate " << framerate << endl;
        info << "sensorMode " << sensorMode << endl;
        info << "enableTexture " << enableTexture << endl;
        info << "enablePixels " << enablePixels << endl;
        info << "exposurePreset " << exposurePreset << endl;


        
        info << "meteringType " << meteringType << endl;
        info << "autoISO " << autoISO << endl;
        info << "ISO " << ISO << endl;
        info << "isoNormalized " << isoNormalized << endl;
        info << "autoShutter " << autoShutter << endl;
        info << "shutterSpeed " << shutterSpeed << endl;
        info << "shutterSpeedNormalized " << shutterSpeedNormalized << endl;
        info << "sharpness " << sharpness << endl;
        info << "contrast " << contrast << endl;
        info << "brightness " << brightness << endl;
        info << "saturation " << saturation << endl;
        info << "frameStabilization " << frameStabilization << endl;
        info << "flickerCancellation " << flickerCancellation << endl;
        info << "dreLevel " << dreLevel << endl;
        info << "drawCropRectangle " << drawCropRectangle << endl;
        info << "drawRectangle " << drawRectangle << endl;
        info << "sensorCropRectangle " << sensorCropRectangle << endl;

        
        info << "displayAlpha " << displayAlpha << endl;
        info << "displayLayer " << displayLayer << endl;
        info << "zoomLevel " << zoomLevel << endl;
        info << "zoomLevelNormalized " << zoomLevelNormalized << endl;
        info << "rotation " << rotation << endl;
        info << "mirror " << mirror << endl;
        info << "doDisableSoftwareSharpen " << doDisableSoftwareSharpen << endl;
        info << "doDisableSoftwareSaturation " << doDisableSoftwareSaturation << endl;
        info << "LED " << LED << endl;
        info << "LED_PIN " << LED_PIN << endl;
        info << "stillPreviewWidth " << stillPreviewWidth << endl;
        info << "stillPreviewHeight " << stillPreviewHeight << endl;
        info << "stillQuality " << stillQuality << endl;
        info << "enableRaw " << enableRaw << endl;
        info << "enableStillPreview " << enableStillPreview << endl;
        info << "burstModeEnabled " << burstModeEnabled << endl;
        info << "savedPhotosFolderName " << savedPhotosFolderName << endl;
        info << "recordingBitrateMB " << recordingBitrateMB << endl;
        info << "cameraDeviceID" << cameraDeviceID << endl;
        info << "whiteBalance " << whiteBalance << endl;
        info << "whiteBalanceGainR " << whiteBalanceGainR << endl;
        info << "whiteBalanceGainB " << whiteBalanceGainB << endl;
        info << "enableExtraVideoFilter " << enableExtraVideoFilter << endl;
        info << "imageFilter " << imageFilter << endl;
        info << "extraImageFilter " << extraImageFilter << endl;
        
        return info.str();
    }
    
/*
    https://www.raspberrypi.org/blog/new-camera-mode-released/
    
    2592×1944 1-15fps, video or stills mode, Full sensor full FOV, default stills capture
    1920×1080 1-30fps, video mode, 1080p30 cropped
    1296×972 1-42fps, video mode, 4:3 aspect binned full FOV. Used for stills preview in raspistill.
    1296×730 1-49fps, video mode, 16:9 aspect , binned, full FOV (width), used for 720p
    640×480 42.1-60fps, video mode, up to VGAp60 binned
    640×480 60.1-90fps, video mode, up to VGAp90 binned
 */
    enum RPI_CAMERA_PRESET 
    {
        PRESET_FASTEST_480P,
        PRESET_FASTEST_720P,
        PRESET_FASTEST_FRAME_RATE,
        PRESET_HIGHEST_RES,
        PRESET_HIGHEST_RES_TEXTURE,
        PRESET_HIGHEST_RES_NONTEXTURE,
        
        PRESET_1080P_30FPS_TEXTURE,
        PRESET_1080P_30FPS_NONTEXTURE,
        PRESET_1080P_30FPS,
        
        PRESET_720P_40FPS_NONTEXTURE,
        PRESET_720P_30FPS_NONTEXTURE,
        
        PRESET_720P_40FPS_TEXTURE,
        PRESET_720P_30FPS_TEXTURE,
        
        PRESET_720P_40FPS,
        PRESET_720P_30FPS,
        
        PRESET_480P_90FPS_TEXTURE,
        PRESET_480P_60FPS_TEXTURE,
        PRESET_480P_40FPS_TEXTURE,
        PRESET_480P_30FPS_TEXTURE,
        
        PRESET_480P_90FPS_NONTEXTURE,
        PRESET_480P_60FPS_NONTEXTURE,
        PRESET_480P_40FPS_NONTEXTURE,
        PRESET_480P_30FPS_NONTEXTURE,
        
        PRESET_480P_90FPS,
        PRESET_480P_60FPS,
        PRESET_480P_40FPS,
        PRESET_480P_30FPS,
    };
    void applyPreset(RPI_CAMERA_PRESET preset)
    {
        switch(preset)
        {
            case PRESET_1080P_30FPS_TEXTURE :
            case PRESET_HIGHEST_RES_TEXTURE :
            {
                sensorWidth = 1920;
                sensorHeight = 1080;
                framerate = 30;
                enableTexture=false;
                break;
            }
                
            case PRESET_1080P_30FPS_NONTEXTURE :
            case PRESET_HIGHEST_RES_NONTEXTURE :
            {
                sensorWidth = 1920;
                sensorHeight = 1080;
                framerate = 30;
                enableTexture=false;
                break;
            }
                
            case PRESET_1080P_30FPS :
            case PRESET_HIGHEST_RES :
            {
                sensorWidth = 1920;
                sensorHeight = 1080;
                framerate = 30;
                break;
            }
                
            case PRESET_720P_40FPS_TEXTURE :
            {
                sensorWidth = 1280;
                sensorHeight = 720;
                framerate = 40;
                enableTexture=true;
                break;
            }
                
            case PRESET_720P_40FPS_NONTEXTURE :
            {
                sensorWidth = 1280;
                sensorHeight = 720;
                framerate = 40;
                enableTexture=false;
                break;
            }
                
            case PRESET_720P_40FPS :
            case PRESET_FASTEST_720P:
            {
                sensorWidth = 1280;
                sensorHeight = 720;
                framerate = 40;
                break;
            }
            case PRESET_720P_30FPS :
            {
                sensorWidth = 1280;
                sensorHeight = 720;
                framerate = 30;
                break;
            }
                
                
            case PRESET_720P_30FPS_TEXTURE :
            {
                sensorWidth = 1280;
                sensorHeight = 720;
                framerate = 30;
                enableTexture=true;
                break;
            }
                
            case PRESET_720P_30FPS_NONTEXTURE :
            {
                sensorWidth = 1280;
                sensorHeight = 720;
                framerate = 30;
                enableTexture=false;
                break;
            }
                
            case PRESET_480P_90FPS_TEXTURE :
            {
                sensorWidth = 640;
                sensorHeight = 480;
                framerate = 90;
                enableTexture=true;
                break;
            } 
            case PRESET_480P_60FPS_TEXTURE :
            {
                sensorWidth = 640;
                sensorHeight = 480;
                framerate = 60;
                enableTexture=true;
                break;
            }    
                
            case PRESET_480P_40FPS_TEXTURE :
            {
                sensorWidth = 640;
                sensorHeight = 480;
                framerate = 40;
                enableTexture=true;
                break;
            }    
                
                
            case PRESET_480P_30FPS_TEXTURE :
            {
                sensorWidth = 640;
                sensorHeight = 480;
                framerate = 30;
                enableTexture=true;
                break;
            }
                
            case PRESET_480P_90FPS_NONTEXTURE :
            {
                sensorWidth = 640;
                sensorHeight = 480;
                framerate = 90;
                enableTexture=false;
                break;
            } 
            case PRESET_480P_60FPS_NONTEXTURE :
            {
                sensorWidth = 640;
                sensorHeight = 480;
                framerate = 60;
                enableTexture=false;
                break;
            } 
            case PRESET_480P_40FPS_NONTEXTURE :
            {
                sensorWidth = 640;
                sensorHeight = 480;
                framerate = 40;
                enableTexture=false;
                break;
            } 
                
            case PRESET_480P_30FPS_NONTEXTURE :
            {
                sensorWidth = 640;
                sensorHeight = 480;
                framerate = 30;
                enableTexture=false;
                break;
            }
                
            case PRESET_480P_90FPS :
            case PRESET_FASTEST_480P:
            case PRESET_FASTEST_FRAME_RATE :
            {
                sensorWidth = 640;
                sensorHeight = 480;
                framerate = 90;
                break;
            }
                
            case PRESET_480P_60FPS :
            {
                sensorWidth = 640;
                sensorHeight = 480;
                framerate = 60;
                break;
            }
                
            case PRESET_480P_40FPS :
            {
                sensorWidth = 640;
                sensorHeight = 480;
                framerate = 40;
                break;
            }
                
            case PRESET_480P_30FPS :
            {
                sensorWidth = 640;
                sensorHeight = 480;
                framerate = 30;
                break;
            }
                
            default:
            {
                sensorWidth = 1280;
                sensorHeight = 720;
                framerate = 30;
                break;
            }
                
        }
    }
};
