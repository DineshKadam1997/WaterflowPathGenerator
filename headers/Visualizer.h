#pragma once
#include <QtWidgets/QMainWindow>
#include "OpenGLWindow.h"
#include "Reader.h"
#include <Qvector>
#include <bitset>
#include <string>
#include <cstdint> // Include this header for uint16_t and uint32_t

class OpenGLWindow;

class Visualizer : public QMainWindow {
    Q_OBJECT

public:
    // Constructor for the Visualizer class
    Visualizer(QWindow* parent = nullptr);

    // Destructor for the Visualizer class
    ~Visualizer();

private:
    // Helper function to set up the user interface
    void setupUi();

private slots:
    // Slot function to handle changes in the zoom slider
    void zoomSlider(int value);

    // Slot function to browse and select an STL file
    void browseSTL();

    // Slot function to read and process the vertices from an STL file
    void readSTL();

    void generateWaterflow();

    //Slot for reaset
    void reset();

public:
    QVector<GLfloat>mNormals;

private:
    QWidget* mCentralWidget;
    OpenGLWindow* mRenderer;
    QLineEdit* mLineEdit;

    QPushButton* mpushButton;
    QPushButton* mResetButton;
    QPushButton* mpushButtonRead;
    QPushButton* mBrowseButton;
    QPushButton* mGenerateWaterflowButton;


    QVector<GLfloat>mVertices;

    QVector<GLfloat>mColors;

    vector<GLfloat>mTempVertices;
    vector<GLfloat>mTempColors;

    std::string mFileName;
    QString mText;
};
