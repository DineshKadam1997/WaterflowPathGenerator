# WaterflowPathGenerator
 
## Overview
The Waterflow Path Generator application is designed to create and visualize Waterflow Path on a terrain, in a three-dimensional space. It consists of three dynamic-link libraries (DLLs): Geometry, Reader, and WaterflowGenerator. The application also includes a visualization component for interactive viewing.
 
## File Structure
The application is structured into three main components:
 
### 1. Geometry DLL
#### Files:
- **Point3D.h/cpp**: Defines a 3D point class with x, y, and z coordinates.
    - `Point3D(double inX, double inY, double inZ = 0)`: Constructor for Point3D.
    - `~Point3D()`: Destructor for Point3D.
    - `double x() const`: Returns the x-coordinate of the point.
    - `double y() const`: Returns the y-coordinate of the point.
    - `double z() const`: Returns the z-coordinate of the point.
    - `void setX(double inX)`: Sets the x-coordinate of the point.
    - `void setY(double inY)`: Sets the y-coordinate of the point.
    - `void setZ(double inZ)`: Sets the z-coordinate of the point.
 
- **Triangle.h/cpp**: Represents a 3D triangle using three Point3D vertices.
    - `Triangle(Point3D p1, Point3D p2, Point3D p3)`: Constructor for Triangle.
    - `~Triangle()`: Destructor for Triangle.
    - `Point3D p1() const`: Returns the first vertex of the triangle.
    - `Point3D p2() const`: Returns the second vertex of the triangle.
    - `Point3D p3() const`: Returns the third vertex of the triangle.
 
- **Triangulation.h/cpp**: Manages a collection of triangles forming a 3D mesh.
    - `Triangulation(const std::vector<Triangle>& inTriangles)`: Constructor for Triangulation.
    - `~Triangulation()`: Destructor for Triangulation.
    - `std::vector<Triangle> getTriangles() const`: Returns the collection of triangles.
 
### 2. Reader DLL
#### Files:
- **Reader.h/cpp**: Implements a class for reading various types of data files, including vertices, colors, and STL files.
    - `Reader()`: Constructor for Reader class.
    - `vector<float> readVertex(string filePath)`: Reads and returns vertex data from the specified file path.
    - `vector<float> readColors(string filePath)`: Reads color data from the specified file path.
    - `vector<float> readSTL(string filePath)`: Reads STL file data from the specified file path.
 
- **TriangleInfo**: Structure defining information about a triangle, including normals, vertices, and attribute byte count.
 
### 3. WaterflowGenerator DLL
#### Files:
- **WaterflowGenerator.h/cpp**: Provides a class for creating Waterflow Path.
    - `WaterflowGenerator()`: Constructor for WaterflowGenerator class.
    - `std::vector<Point3D> GeneratePath(string filePath)`: Adds a Waterflow Path Generator.
 
 
### 4. Application Visualizer
#### Files:
- **Visualizer.h/cpp**: Main application class utilizing Qt for the user interface.
    - `Visualizer(QWindow* parent = nullptr)`: Constructor for the Visualizer class.
    - `~Visualizer()`: Destructor for the Visualizer class.
    - `void setupUi()`: Sets up the user interface.
    - `void readVertex(std::string filePath)`: Reads vertex data from the specified file path.
    - `void readColors(std::string filePath)`: Reads color data from the specified file path.
    - `void zoomSlider(int value)`: Handles zoom slider changes.
    - `void browseSTL()`: Handles the STL file browsing.
    - `void readSTL()`: Reads STL file data.
 
- **OpenGLWindow.h/cpp**: Handles rendering and OpenGL integration.
 
- **Reader.h**: Includes functions for reading vertices, colors, and STL files.
 
- **WaterGenerator.h**: Includes functions for creating Waterflow Path.
 
 
### 5. Software Tools
 
1. `C++`: The primary programming language for the application.
 
2. `QT`: The Qt framework is utilized for the development of the graphical user interface (GUI) components.
 
3. `OpenGL`: OpenGL is employed for rendering 3D graphics, enhancing the visualization capabilities of the application.
 
4. `Visual Studio`: The project is developed and built using the Visual Studio integrated development environment.
 
5. `Git`: Git is used for version control and collaborative development, allowing for easy tracking of changes and contributions.
