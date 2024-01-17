#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMainWindow>
#include <QQuaternion>
#include <QWheelEvent>

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    // Constructor for the OpenGLWindow class
    OpenGLWindow(const QColor& background, QMainWindow* parent);

    // Destructor for the OpenGLWindow class
    ~OpenGLWindow();

    // Update the data for rendering
    void updateData(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors);
    void updateNormals(const QVector<GLfloat>& normals);

    // Handle mouse move events
    void mouseMoveEvent(QMouseEvent* event) override;

;
    // Handle wheel events (mouse wheel)
    void wheelEvent(QWheelEvent* event) override;

    // Set the zoom factor for rendering
    void setZoomFactor(float& inZoom);

    void shaderWatcher();

    void updateAll();

    std::vector<double> boundingBox(QVector<GLfloat> mVerticesOfOrignalLine);
    QString readShaderSource(QString filePath);



protected:
    // Paint the OpenGL scene
    void paintGL() override;

    // Initialize the OpenGL context and resources
    void initializeGL() override;

private:
    // Reset the OpenGL context and cleanup resources
    void reset();


signals:
    // Signal emitted when the shape is updated
    void shapeUpdate();

private slots:
    QString readShader(QString filePath);

private:
    QOpenGLContext* mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;

    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;

    QList<QVector3D> mVertices;
    QList<QVector3D> mNormals;
    QOpenGLBuffer mVbo;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;

    QQuaternion rotationAngle;
    QPoint lastPos;
    QPoint mMousePos;
    QPoint mTranslatedMousePos;
    GLfloat mZoomFactor = 1.0f;

    QVector<GLfloat> mVerticesOfOrignalLine;
    QVector<GLfloat> mColorOfOrignalLine;
    QVector<GLfloat> mNormalsOfTriangle;

    int mTranslate = 0;
    int mCount = 0;
    int count = 0;
 
    bool mAnimating = false;

    std::vector<float> mouseCoordinates;
    QFileSystemWatcher* mShaderWatcher;

    GLint m_normals = 0;
    GLint m_matrixUniform_proj = 0;
    GLint m_matrixUniform_view = 0;
    GLint m_matrixUniform_model = 0;
    int m_lightPosLoc = 0;
    int m_normalMatrixLoc = 0;
    int mFlag = 0;
};
