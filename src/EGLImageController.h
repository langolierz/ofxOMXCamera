#pragma once
#include "ofMain.h"
#include "ofAppEGLWindow.h"
#include "OMX_Maps.h"

class EGLImageController
{
public:
    
    
    EGLImageKHR eglImage;
    EGLDisplay display;
    EGLContext context;
    OMX_BUFFERHEADERTYPE* eglBuffer;
    ofTexture texture;
    ofAppEGLWindow* appEGLWindow;
    EGLImageController()
    {
        eglImage = NULL;
        display = NULL;
        context = NULL;
        appEGLWindow = NULL;
    }
    
    ~EGLImageController()
    {
        close();
    }
    
    void close()
    {
        destroyEGLImage();
        eglImage = NULL;
        display = NULL;
        context = NULL;
        appEGLWindow = NULL;
        
    }
    
    /*
    bool generateEGLImage(int videoWidth, int videoHeight)
    {
        bool success = false;
        bool needsRegeneration = false;
        
        if (!texture.isAllocated())
        {
            needsRegeneration = true;
        }
        else
        {
            if (texture.getWidth() != videoWidth && texture.getHeight() != videoHeight)
            {
                needsRegeneration = true;
            }
        }
        
        if (!fbo.isAllocated())
        {
            needsRegeneration = true;
        }
        else
        {
            if (fbo.getWidth() != videoWidth && fbo.getHeight() != videoHeight)
            {
                needsRegeneration = true;
            }
        }
        
        if(!needsRegeneration)
        {
            //ofLogVerbose(__func__) << "NO CHANGES NEEDED - RETURNING EARLY";
            return true;
        }
        
        if (appEGLWindow == NULL)
        {
            appEGLWindow = (ofAppEGLWindow *) ofGetWindowPtr();
        }
        
        if (appEGLWindow == NULL)
        {
            ofLogError(__func__) << "appEGLWindow is NULL - RETURNING";
            return false;
        }
        if (display == NULL)
        {
            display = appEGLWindow->getEglDisplay();
        }
        if (context == NULL)
        {
            context = appEGLWindow->getEglContext();
        }
        
        if (display == NULL)
        {
            ofLogError(__func__) << "display is NULL - RETURNING";
            return false;
        }
        if (context == NULL)
        {
            ofLogError(__func__) << "context is NULL - RETURNING";
            return false;
        }
        
        if (needsRegeneration)
        {
            
            fbo.allocate(videoWidth, videoHeight, GL_RGBA);
            texture.allocate(videoWidth, videoHeight, GL_RGBA);
            texture.setTextureWrap(GL_REPEAT, GL_REPEAT);
            textureID = texture.getTextureData().textureID;
        }
        
        ofLog() << "textureID: " << textureID;
        ofLog() << "tex.isAllocated(): " << texture.isAllocated();
        ofLog() << "videoWidth: " << videoWidth;
        ofLog() << "videoHeight: " << videoHeight;
        ofLog() << "pixels: " << videoHeight;
        
        // setup first texture
        int dataSize = videoWidth * videoHeight * 4;
        
        if (pixels && needsRegeneration)
        {
            delete[] pixels;
            pixels = NULL;
        }
        
        if (pixels == NULL)
        {
            pixels = new unsigned char[dataSize];
        }
        ofLog() << "dataSize: " << dataSize;
        
        //memset(pixels, 0xff, dataSize);  // white texture, opaque
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, videoWidth, videoHeight, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        
        
        if (eglImage && needsRegeneration)
        {
            destroyEGLImage();
        }
        
        // Create EGL Image
        eglImage = eglCreateImageKHR(display, context, EGL_GL_TEXTURE_2D_KHR, (EGLClientBuffer)textureID, NULL);
        
        if (eglImage == EGL_NO_IMAGE_KHR)
        {
            ofLog()    << "Create EGLImage FAIL <---------------- :(";
            
        }
        else
        {
            success = true;
            ofLog()  << "Create EGLImage PASS <---------------- :)";
        }
        return success;
        
    }
    */
    void generateEGLImage(int width, int height)
    {
        
        ofAppEGLWindow *appEGLWindow = (ofAppEGLWindow *) ofGetWindowPtr();
        display = appEGLWindow->getEglDisplay();
        context = appEGLWindow->getEglContext();
        
        
        texture.allocate(width, height, GL_RGBA);
        //texture.getTextureData().bFlipTexture = true;
        
        texture.setTextureWrap(GL_REPEAT, GL_REPEAT);
        GLuint textureID = texture.getTextureData().textureID;
        
        glEnable(GL_TEXTURE_2D);
        
        // setup first texture
        int dataSize = width * height * 4;
        
        GLubyte* pixelData = new GLubyte [dataSize];
        
        
        memset(pixelData, 0xff, dataSize);  // white texture, opaque
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
        
        delete[] pixelData;
        
        
        // Create EGL Image
        eglImage = eglCreateImageKHR(
                                     display,
                                     context,
                                     EGL_GL_TEXTURE_2D_KHR,
                                     (EGLClientBuffer)textureID,
                                     0);
        glDisable(GL_TEXTURE_2D);
        if (eglImage == EGL_NO_IMAGE_KHR)
        {
            ofLogError()    << "Create EGLImage FAIL";
            return;
        }
        else
        {
            ofLogVerbose(__func__)    << "Create EGLImage PASS";
        }
    }
    
    void destroyEGLImage()
    {
        
        
        if (eglImage)
        {
            if (appEGLWindow == NULL)
            {
                appEGLWindow = (ofAppEGLWindow *) ofGetWindowPtr();
            }
            
            if(!appEGLWindow) return;
            
            if (display == NULL)
            {
                display = appEGLWindow->getEglDisplay();
            }
            
            if(!display) return;

            if (!eglDestroyImageKHR(display, eglImage))
            {
                ofLog() << __func__ << " FAIL <---------------- :(";
            }else
            {
                ofLog() << __func__ << " PASS <---------------- :)";
            }
            eglImage = NULL;
        }
        
    }
};
