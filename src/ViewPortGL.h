#pragma once

#include <functional>
#include <list>
#include "WindowInterface.h"
#include "ShaderInterface.h"
#include "KeyInputListener.h"
#include "Color.h"

class ViewPortGL {


public:
    /**
    * Opens a new Window with the given title, width and height.
    */
    ViewPortGL(string title, int width, int height);

    ~ViewPortGL();

    /**
    * Returns true if a signal occurred that commands the window to close.
    */
    bool windowShouldClose();

    /**
    * Swaps the background-buffer to the front and vice versa.
    */
    void swapBuffers();

    /**
    * Returns the width of the window's drawing area in pixels.
    */
    int getXSize();
    /**
    * Returns the height of the window's drawing area in pixels.
    */
    int getYSize();


    inline float getMinX() {
        return -aspectRatio;
    }

    inline float getMaxX() {
        return aspectRatio;
    }

    inline float getMinY() {
        return -1.0f;
    }

    inline float getMaxY() {
        return 1.0f;
    }

    inline float getWidth() {
        return 2*aspectRatio;
    }

    inline float getHeight() {
        return 2.0f;
    }



    /**
    * Clears the background of the window, filling it with black color.
    * Just fills the background-buffer, so a change is visible only after
    * a call to swapBuffers().
    */
    void clearViewPort();

    /**
    * Prepares the window to draw the specified pixel with coordinates (x,y)
    * and the color with the given rgb-components.
    * The actual drawing of the pixel will happen when you call drawPixels()
    * (and switch buffers using swapBuffers()).
    */
    void preparePix(int x, int y, int red, int green, int blue);




    /**
    * Prepares the window to draw the specified pixel with coordinates (x,y)
    * and the given color with the given rgb-components.
    * The actual drawing of the pixel will happen when you call drawPixels()
    * (and switch buffers using swapBuffers()).
    */
    void preparePix(int x, int y, const Color& c);


    /**
    * Prepares the window to draw the specified line with end-coordinates (x1, y1) and (x2, y2)
    * and the color with the given rgb-components.
    * The actual drawing of the line will happen when you call drawLines()
    * (and switch buffers using swapBuffers()).
    */
    void prepareLine(int x1, int y1, int x2, int y2, int red, int green, int blue);


    /**
    * Prepares the window to draw the specified line with end-coordinates (x1, y1) and (x2, y2)
    * and the given color.
    * The actual drawing of the line will happen when you call drawLines()
    * (and switch buffers using swapBuffers()).
    */
    void prepareLine(int x1, int y1, int x2, int y2, const Color& c);


    /**
    * Prepares the window to draw the specified line with end-coordinates (x1, y1) and (x2, y2).
    * The color is specified for the end-points by the given rgb-values and interpolated
    * between these two colors.
    * The actual drawing of the line will happen when you call drawLines()
    * (and switch buffers using swapBuffers()).
    */
    void prepareLine(int x1, int y1, int x2, int y2, int red1, int green1, int blue1, int red2, int green2, int blue2);


    /**
    * Prepares the window to draw the specified line with end-coordinates (x1, y1) and (x2, y2).
    * The color is specified for the end-points by the given Color instances.
    * The actual drawing of the line will happen when you call drawLines()
    * (and switch buffers using swapBuffers()).
    */
    void prepareLine(int x1, int y1, int x2, int y2, const Color& c1, const Color& c2);


    /**
    * Prepares the window to draw the specified triangles with coordinates 
    * (x1, y1), (x2, y2), and (x3, y3).
    * The color is specified for the edge-points by the given rgb-values and interpolated
    * between these three colors.
    * The actual drawing of the triangle will happen when you call drawTriangles()
    * (and switch buffers using swapBuffers()).
    */
    void prepareTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
        int red1, int green1, int blue1, int red2, int green2, int blue2, int red3, int green3, int blue3);


    /**
    * Prepares the window to draw the specified triangles with coordinates
    * (x1, y1), (x2, y2), and (x3, y3).
    * The color is specified for the edge-points by the given Color-instances.
    * The actual drawing of the triangle will happen when you call drawTriangles()
    * (and switch buffers using swapBuffers()).
    */
    void prepareTriangle(int x1, int y1, int x2, int y2, int x3, int y3, 
        const Color& c1, const Color& c2, const Color& c3);


    /**
    * Prepares the window to draw the specified triangles with coordinates
    * (x1, y1), (x2, y2), and (x3, y3).
    * The color is specified by an rgb-values for the whole triangle.
    * The actual drawing of the triangle will happen when you call drawTriangles()
    * (and switch buffers using swapBuffers()).
    */
    void prepareTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int red, int green, int blue);


    /**
    * Prepares the window to draw the specified triangles with coordinates
    * (x1, y1), (x2, y2), and (x3, y3).
    * The color is specified by the given Color instance
    * The actual drawing of the triangle will happen when you call drawTriangles()
    * (and switch buffers using swapBuffers()).
    */
    void prepareTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color& c);


    /**
    * Prepares the window to draw the specified, filled rectangle where the coordinate
    * off the upper left corner is given by (x, y) and ist dimensions are given
    * by arguments width and height.
    * The color is specified for the edge-points by the given Color instances.
    * The actual drawing of the rectangle will happen when you call drawTriangles()
    * (and switch buffers using swapBuffers()).
    */
    void prepareBlock(int x, int y, int blWidth, int blHeight,
        const Color& c1, const Color& c2, const Color& c3, const Color& c4);



    /**
    * Prepares the window to draw the specified, filled rectangle where the coordinate
    * off the upper left corner is given by (x, y) and ist dimensions are given
    * by arguments width and height.
    * The color is specified for the edge-points by the given rgb-values and interpolated
    * between these four colors.
    * The actual drawing of the rectangle will happen when you call drawTriangles()
    * (and switch buffers using swapBuffers()).
    */
    void prepareBlock(int x, int y, int blWidth, int blHeight,
        int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3, int r4, int g4, int b4);



    /**
    * Prepares the window to draw the specified, filled rectangle where the coordinate
    * off the upper left corner is given by (x, y) and ist dimensions are given
    * by arguments width and height.
    * The color of the whole block is specified by the given Color instance.
    * The actual drawing of the rectangle will happen when you call drawTriangles()
    * (and switch buffers using swapBuffers()).
    */
    void prepareBlock(int x, int y, int blWidth, int blHeight, const Color& c);


    /**
    * Prepares the window to draw the specified, filled rectangle where the coordinate
    * off the upper left corner is given by (x, y) and ist dimensions are given
    * by arguments width and height.
    * The color of the whole block is specified via red, green, and blue components.
    * The actual drawing of the rectangle will happen when you call drawTriangles()
    * (and switch buffers using swapBuffers()).
    */
    void prepareBlock(int x, int y, int blWidth, int blHeight, int r, int g, int b);



    void preparePix(float x, float y, int red, int green, int blue);
    void preparePix(float x, float y, const Color& c);
    void prepareLine(float x1, float y1, float x2, float y2, int red1, int green1, int blue1, int red2, int green2, int blue2);
    void prepareLine(float x1, float y1, float x2, float y2, const Color& c1, const Color& c2);
    void prepareLine(float x1, float y1, float x2, float y2, const Color& c);
    void prepareLine(float x1, float y1, float x2, float y2, int red, int green, int blue);
    void prepareTriangle(float x1, float y1, float x2, float y2, float x3, float y3, int red1, int green1, int blue1, int red2, int green2, int blue2, int red3, int green3, int blue3);
    void prepareTriangle(float x1, float y1, float x2, float y2, float x3, float y3, int red, int green, int blue);
    void prepareTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const Color& c1, const Color& c2, const Color& c3);
    void prepareTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const Color& c);
    void prepareBlock(float x, float y, float blWidth, float blHeight, int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3, int r4, int g4, int b4);
    void prepareBlock(float x, float y, float blWidth, float blHeight, const Color& c1, const Color& c2, const Color& c3, const Color& c4);
    void prepareBlock(float x, float y, float blWidth, float blHeight, const Color& c);






    /**
    * Triggers the drawing of all pixels, that were prepared using sendPix since the
    * last call to drawPixels(). All these pixels are drawn to the background buffer
    * i.e. they will not appear on screen until the next call of swapBuffers().
    */
    void sendPixels();

    /**
    * Triggers the drawing of all lines, that were prepared using a sendLine method since the
    * last call to drawLines(). All these lines are drawn to the background buffer
    * i.e. they will not appear on screen until the next call of swapBuffers().
    */
    void sendLines();

    /**
    * Triggers the drawing of all triangles, that were prepared using either sendTriangle or sendlock
    * since the last call to drawTriangles(). All these triangles are drawn to the background buffer
    * i.e. they will not appear on screen until the next call of swapBuffers().
    */
    void sendTriangles();

    static int getMaxNumberOfPreparedPixels();
    static int getMaxNumberOfPreparedLines();
    static int getMaxNumberOfPreparedTriangles();

    static void addKeyListener(function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>);
    static void notifyAllKeyListeners(GLFWwindow* window, int key, int scancode, int action, int mods);



private:
    const static int PIXDATA_ARRAY_SIZE = 5000000; // permits a maximum of 1 million points
    const static int LINEDATA_ARRAY_SIZE = 1000000; // permits a maximum of 100000 lines
    const static int TRIANGLEDATA_ARRAY_SIZE = 1500000; // permits a maximum of 100000 triangles


    int width;
    int height;
    float aspectRatio;
    float* pixelData;
    float* lineData;
    float* triangleData;
    int pixelDataPointer;
    int lineDataPointer;
    int triangleDataPointer;

    GLuint pixelDataVAO;
    GLuint pixelDataVBO;
    GLuint lineDataVAO;
    GLuint lineDataVBO;
    GLuint triangleDataVAO;
    GLuint triangleDataVBO;


    GLFWwindow* getWindId();
    void enableDepthTest();
    void disableDepthTest();
    void initPlain2DShaders();
    void execDrawing2DPrimitives();


    WindowInterface* win;
    ShaderInterface* shader;
    ShaderInterface* plain2DPixelShader;

    static list<function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>> keyListeners;


    std::pair<GLuint, GLuint> setupGLPointColorBuf();
    void initStaticBuffers();



};

