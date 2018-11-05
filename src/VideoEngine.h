/*
 *  BaseEngine.h
 *
 *  Created by jason van cleave on 2/10/14.
 *  Copyright 2014 jasonvancleave.com. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofAppEGLWindow.h"
#include "OMX_Maps.h"
#include "ofxOMXCameraSettings.h"
#include "DisplayController.h"

class VideoEngineListener
{
public:
    virtual void onRecordingComplete(string filePath)=0;
    virtual void onVideoEngineStart()=0;
    virtual void onVideoEngineClose()=0;

    
};

class VideoEngine
{
public:
	VideoEngine();
    ~VideoEngine();

	void setup(ofxOMXCameraSettings&, VideoEngineListener*, DisplayController* displayController_=NULL);
    int getFrameCounter();
	ofxOMXCameraSettings& getSettings();
    
    void startRecording();
    void stopRecording();
	OMX_HANDLETYPE camera;
	bool isOpen;
    bool isRecording;
    VideoEngineListener* listener;

    int frameCounter;
    void close();
    OMX_ERRORTYPE onCameraEventParamOrConfigChanged();
    bool isClosing;
    DisplayController* displayController;
protected:
	
    OMX_BUFFERHEADERTYPE* eglBuffer;

    ofxOMXCameraSettings settings;
	void configureCameraResolution();
	void configureEncoder();
	
	OMX_HANDLETYPE splitter;
	OMX_HANDLETYPE encoder;
	OMX_HANDLETYPE render;
	
	
	bool didWriteFile;
	
	int recordingBitRate;
	float numMBps;
	
	bool stopRequested;
	bool isStopping;
	
	void writeFile();
	
	ofBuffer recordingFileBuffer;
	OMX_BUFFERHEADERTYPE* encoderOutputBuffer;
	
	int recordedFrameCounter;
	
	static OMX_ERRORTYPE splitterEventHandlerCallback(OMX_HANDLETYPE, OMX_PTR, OMX_EVENTTYPE, OMX_U32, OMX_U32, OMX_PTR) {return OMX_ErrorNone;};
	static OMX_ERRORTYPE encoderEventHandlerCallback(OMX_HANDLETYPE, OMX_PTR, OMX_EVENTTYPE, OMX_U32, OMX_U32, OMX_PTR){return OMX_ErrorNone;};
	static OMX_ERRORTYPE encoderEmptyBufferDone( OMX_HANDLETYPE, OMX_PTR, OMX_BUFFERHEADERTYPE*){return OMX_ErrorNone;};   
    static OMX_ERRORTYPE renderEventHandlerCallback(OMX_HANDLETYPE, OMX_PTR, OMX_EVENTTYPE, OMX_U32, OMX_U32, OMX_PTR){return OMX_ErrorNone;};
	static OMX_ERRORTYPE renderEmptyBufferDone(OMX_HANDLETYPE, OMX_PTR, OMX_BUFFERHEADERTYPE*){return OMX_ErrorNone;};
    static OMX_ERRORTYPE directRenderFillBufferDone( OMX_HANDLETYPE, OMX_PTR, OMX_BUFFERHEADERTYPE*){return OMX_ErrorNone;};
    
    static OMX_ERRORTYPE textureRenderFillBufferDone( OMX_HANDLETYPE, OMX_PTR, OMX_BUFFERHEADERTYPE*);

    
    static OMX_ERRORTYPE encoderFillBufferDone(OMX_HANDLETYPE encoder, OMX_PTR engine, OMX_BUFFERHEADERTYPE* encoderOutputBuffer);
    static OMX_ERRORTYPE cameraEventHandlerCallback(OMX_HANDLETYPE camera, OMX_PTR videoModeEngine_, OMX_EVENTTYPE eEvent, OMX_U32 nData1, OMX_U32 nData2, OMX_PTR pEventData);



    
    
	
};
