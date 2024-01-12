#include "stdafx.h"
#include "Visualizer.h"
#include "Point3D.h"
#include "WaterflowGenerator.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;


//Constructor 
Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
    //connect statements for signal and slots.
    connect(mpushButtonRead, &QPushButton::clicked, this, &Visualizer::readSTL);
    connect(mBrowseButton, &QPushButton::clicked, this, &Visualizer::browseSTL);
    connect(mResetButton, &QPushButton::clicked, this, &Visualizer::reset);
    connect(mGenerateWaterflowButton, &QPushButton::clicked, this, &Visualizer::generateWaterflow);
}

Visualizer::~Visualizer()
{

}

void Visualizer::reset()
{
    mText = "Window Cleared successfully";
    mLineEdit->setText(mText);
    mRenderer->updateAll();
}

//UI implementation
void Visualizer::setupUi()
{
    setMinimumSize(600, 400);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout* buttonLayout = new QHBoxLayout;

    mBrowseButton = new QPushButton("Browse STL", this);
    mBrowseButton->setObjectName("mpushButton");
    buttonLayout->addWidget(mBrowseButton);

    mpushButtonRead = new QPushButton("Render STL", this);
    mpushButtonRead->setObjectName("mpushButton");
    buttonLayout->addWidget(mpushButtonRead);

    mGenerateWaterflowButton = new QPushButton("Generate Waterflow", this);
    mGenerateWaterflowButton->setObjectName("mpushButton");
    buttonLayout->addWidget(mGenerateWaterflowButton);

    mResetButton = new QPushButton("Reset Window", this);
    mResetButton->setObjectName("mpushButton");
    buttonLayout->addWidget(mResetButton);

    mainLayout->addLayout(buttonLayout);

    mLineEdit = new QLineEdit(this);
    mLineEdit->setObjectName("lineEdit");

    mainLayout->addWidget(mLineEdit);

    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);

    mRenderer->setMinimumSize(200, 200);

    mRenderer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(mRenderer);

    centralWidget->setLayout(mainLayout);

    setWindowTitle(QCoreApplication::translate("Waterflow Path Generator", "Waterflow Path Generator", nullptr));
}



// slot to browse file
void Visualizer::browseSTL()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "", tr("STL Files(*.stl);; All Files(*)"));
    if (!fileName.isEmpty())
    {
        mFileName = fileName.toStdString();
        mText = "File browsed successfully";
        mLineEdit->setText(mText);
    }
}

// slot to zoom 
void Visualizer::zoomSlider(int value)
{
    GLfloat zoomFactor = 0.5 + (value / 100.0) * 1.0;
    mRenderer->setZoomFactor(zoomFactor);
}

// slot to read stl file
void Visualizer::readSTL()
{

    std::string filePath = mFileName;
    Reader read;
    std::vector<float> mTempNormals;
    mTempVertices = read.readSTL(mFileName, mTempNormals);
    for (int i = 0; i < mTempNormals.size(); i += 3)
    {
        mNormals << mTempNormals[i] << mTempNormals[i + 1] << mTempNormals[i + 2];
    }
    if (mTempVertices.size() != 0)
    {
        for (int i = 0; i < mTempVertices.size(); i += 12)
        {

            mVertices << mTempVertices[i] << mTempVertices[i + 1] << mTempVertices[i + 2];
            mVertices << mTempVertices[i + 3] << mTempVertices[i + 4] << mTempVertices[i + 5];
            mVertices << mTempVertices[i + 6] << mTempVertices[i + 7] << mTempVertices[i + 8];
            mVertices << mTempVertices[i + 9] << mTempVertices[i + 10] << mTempVertices[i + 11];


            mColors << 0.0f << 1.0f << 1.0f;
            mColors << 1.0f << 1.0f << 0.0f;
            mColors << 1.0f << 0.0f << 1.0f;
            mColors << 0.0f << 0.0f << 1.0f;
        }

        mRenderer->updateData(mVertices, mColors);
        mRenderer->updateNormals(mNormals);
        mText = "File is Loaded successfully";
        mLineEdit->setText(mText);
        mVertices.clear();
        mColors.clear();
    }
    else
    {
        mText = "Unable To Load A File";
        mLineEdit->setText(mText);
    }
}

void Visualizer::generateWaterflow()
{
    WaterflowGenerator w;

    std::vector<Point3D> points = w.ReadVector(mFileName);

    for (int i = 0; i < points.size(); i++)
    {
        mVertices << points[i].x() * 0.1 << points[i].y() * 0.1 << points[i].z() * 0.1;
        mColors << 1.0f << 1.0f << 0.0f;
    }

    mRenderer->updateData(mVertices, mColors);
    mRenderer->updateNormals(mNormals);
    mText = "File is Loaded successfully";
    mLineEdit->setText(mText);
    mVertices.clear();
    mColors.clear();
}
