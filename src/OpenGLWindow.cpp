#pragma once
#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <tuple>
#include <GL/glu.h>
#include <cmath>
#include <algorithm>


// OpenGLWindow constructor initializes member variables with default values
OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
    mBackground(background), mZoomFactor(1.0f) {
    setParent(parent);
    setMinimumSize(1500, 800);
    QStringList file_lists = { "Vertex.glsl" ,"Fragment.glsl" };
    mShaderWatcher = new QFileSystemWatcher(file_lists, this);
    connect(mShaderWatcher, &QFileSystemWatcher::fileChanged, this, &OpenGLWindow::shaderWatcher);
}



// OpenGLWindow destructor, releases allocated resources
OpenGLWindow::~OpenGLWindow() {
    reset();
}

// Reset function to release OpenGL resources and disconnect signals
void OpenGLWindow::reset() {
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

// Set the zoom factor for the scene and trigger an update
void OpenGLWindow::setZoomFactor(float& inZoom) {
    mZoomFactor = inZoom;
    update();
}

// Set the tower height and trigger an update


std::vector<double> OpenGLWindow::boundingBox(QVector<GLfloat> mVerticesOfOrignalLine)
{
    std::vector<double> mboundingBox;
    double minX = DBL_MAX;
    double minY = DBL_MAX;
    double minZ = DBL_MAX;
    double maxX = DBL_MIN;
    double maxY = DBL_MIN;
    double maxZ = DBL_MIN;

    std::string line;
    for(int i=9;i< mVerticesOfOrignalLine.size();i+=3)
    {
        double x = mVerticesOfOrignalLine[i];
        double y = mVerticesOfOrignalLine[i+1];
        double z = mVerticesOfOrignalLine[i+2];
            // Update bounding box coordinates
        minX = std::min(minX, x);
        minY = std::min(minY, y);
        minZ = std::min(minZ, z);
        maxX = std::max(maxX, x);
        maxY = std::max(maxY, y);
        maxZ = std::max(maxZ, z);
        
    }
    mboundingBox.push_back(minX);
    mboundingBox.push_back(minY);
    mboundingBox.push_back(minZ);
    mboundingBox.push_back(maxX);
    mboundingBox.push_back(maxY);
    mboundingBox.push_back(maxZ);

    return mboundingBox;
}

// Paint the OpenGL scene, drawing tower and wireframe
void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    mProgram->bind();
    QMatrix4x4 matrix_proj;
    QMatrix4x4 matrix_view;
    QMatrix4x4 matrix_model;



    matrix_model.setToIdentity();
    matrix_model.rotate(rotationAngle);

    //matrix_model.setToIdentity();
    matrix_proj.ortho(-40.0f, 40.0f, -40.0f, 40.0f, -100.0f, 100.0f);

    matrix_view.setToIdentity();
    matrix_view.translate(0, 0, -20);
    matrix_view.scale(mZoomFactor);

    mProgram->setUniformValue(m_matrixUniform_proj, matrix_proj);
    mProgram->setUniformValue(m_matrixUniform_view, matrix_view);
    mProgram->setUniformValue(m_matrixUniform_model, matrix_model);
    mProgram->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 90));

    QMatrix3x3 normalMatrix = matrix_model.normalMatrix();
    mProgram->setUniformValue(m_normalMatrixLoc, normalMatrix);

    GLfloat* verticesData = mVerticesOfOrignalLine.data();
    GLfloat* normalData = mNormalsOfTriangle.data();
    GLfloat* colorsData = mColorOfOrignalLine.data();

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, verticesData);
    glVertexAttribPointer(m_normals, 3, GL_FLOAT, GL_FALSE, 0, normalData);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colorsData);

    glEnableVertexAttribArray(m_colAttr);
    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_normals);

    // Draw the lines
    glDrawArrays(GL_TRIANGLES, 0, mVerticesOfOrignalLine.size() / 3);

    // Configure vertex attribute pointers and enable them
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0,0);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0,0);
    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    // Draw the wireframe as lines
    glDrawArrays(GL_LINE_LOOP, 0,0);

    // Configure vertex attribute pointers and enable them
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0,0);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    // Draw the wireframe as lines
    glDrawArrays(GL_LINES, 0, 0);



}

// Initialize OpenGL, shaders, and program
void OpenGLWindow::initializeGL()
{
    QString qvertexShaderSource = readShader("Vertex.glsl");
    QString qfragmentShaderSource = readShader("Fragment.glsl");

    rotationAngle = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, 0.0f); // Initialize rotation angle

    initializeOpenGLFunctions();
    setMouseTracking(true);

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, qvertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, qfragmentShaderSource);
    mProgram->bindAttributeLocation("vertex", 0);
    mProgram->bindAttributeLocation("normal", 1);

    mProgram->link();

    m_posAttr = mProgram->attributeLocation("posAttr");
    m_normals = mProgram->attributeLocation("normalAttr");
    m_matrixUniform_proj = mProgram->uniformLocation("u_ProjMatrix");
    m_matrixUniform_view = mProgram->uniformLocation("u_viewMatrix");
    m_matrixUniform_model = mProgram->uniformLocation("u_modelMatrix");
    m_normalMatrixLoc = mProgram->uniformLocation("normalMatrix");
    m_lightPosLoc = mProgram->uniformLocation("lightPos");
}

void OpenGLWindow::shaderWatcher()
{
    QString vertexShaderSource = readShader("Vertex.glsl");
    QString fragmentShaderSource = readShader("Fragment.glsl");

    mProgram->release();
    mProgram->removeAllShaders();
    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
}

void OpenGLWindow::updateAll()
{
    
    mZoomFactor = 1.0f;
    mFlag = 0;
    mCount = 0;
    mVerticesOfOrignalLine.clear();
    mColorOfOrignalLine.clear();
    
    update();
}

QString OpenGLWindow::readShader(QString filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "Invalid file";

    QTextStream stream(&file);
    QString line = stream.readLine();

    while (!stream.atEnd()) {
        line.append(stream.readLine());
    }
    file.close();
    return line;
}

// Handle mouse wheel events to zoom in/out
void OpenGLWindow::wheelEvent(QWheelEvent* event)
{
    int delta = event->angleDelta().y();

    // Adjust the zoom factor based on the mouse wheel movement
    if (delta > 0)
    {
        // Zoom in
        mZoomFactor *= 1.1f;
    }
    else {
        // Zoom out
        mZoomFactor /= 1.1f;
    }
    update();
}

void OpenGLWindow::updateData(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors) {
    mVerticesOfOrignalLine += vertices;
    mColorOfOrignalLine += colors;
    mFlag = 1;
    update();
}

void OpenGLWindow::updateNormals(const QVector<GLfloat>& normals) {
    mNormalsOfTriangle += normals;
    update();
}

QString OpenGLWindow::readShaderSource(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Could not open file: " << filePath;
        return "";
    }

    QTextStream stream(&file);
    return stream.readAll();
}

// Handle mouse move events to rotate the scene
void OpenGLWindow::mouseMoveEvent(QMouseEvent* event) {
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        // Create rotation quaternions based on mouse movement
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

        // Combine rotations and update rotation angle
        rotationAngle = rotX * rotY * rotationAngle;
        update();
    }

    // Update last mouse position
    lastPos = event->pos();
}