# RayTracing Engine in C++ 
Default Image ![image](https://github.com/user-attachments/assets/a3e3edf1-7f57-4879-86c0-b6f5ba8462f1)

# How to install
I have a CMake file you can use to generate a build, please build it with release mode. Then once you have the project loaded add an "img" folder into same folder where the project is setup. Once done you should be able to run the program! After the program is finished a PPM file will be generated in the img file.

# Things I have learned during this process
## How to analyze and improve performance
During the first few iterations of this project I had a lot of performance problems. Right now, I can render at 1920 x 1080 in about 50 seconds on both my laptop and desktop.
Originally It would have taken 7 minutes! That is  a crazy improvement! To understand where my problem was coming from I used the built in performance profiler within Visual Studio. Here, before multi threading, I was able to determine a few issues. 
First, within a few functions I was calling very expensive functions. For example, in the Matrix::Invert function I was calling the Matrix::Deterimanant function twice.
By removing one call and storing it in a variable I saw an approximate 25% increase in performance. There was another case where I was inverted a matrix twice in one function and I had similar success but only calling it once and store that value to be used later.  

Second, I learned how to use multithreading. In this project specifically I have to do a lot of math calculations. at 1920 x 1080 thats around two million pixels that I have to calculate individually! At the beginning I really was doing them one by one and boy was that slow. So I watched a video from CPP Con on multithreading and determined I needed to use Futures and Async threads to avoid the race condition and speed up my engine. As of right now I am proccess about 30 cols at a time and that significantly improved how quickly I can generate my image.

Third, I learned how to use visual studios performance profiler. I have never made a project that required as many computations as this one does and to find out where I was leaking performance learning the performance profiler was a gamer changer. This is where I learned about the functions causing performance issues because I was calling the same function twice in one function instead of storing the value.

# The fun stuff
## This project, as of now, generates a PPM image file of a 2D scene with Ray Tracing applied to it to make it feel 3D.
This engine I created is made from scratch. There are a few key components to understand what is happening to generate the image. 
## First is the Tuple object. A Tuple is used to represent a pos, direction in space, or a color. 
A Tuple is compromised of four float values x y z w. The first floats are pos data and the final float is used to mark wether the current Tuple is a position in space or a vector. A 1.0 represents a point, a 0.0 represents a vector. Another thing A Tuple can represent is a color. In this case all that matters is the first three floats which can represent R G B. Realisitcally each representation of 
a Tuple should be its own class. Within the Tuple class there are basic math operations as well as more niche use case operations such as finding the DOT PRODUCT.
## Second is the Canvas. This is where we store each pixels color data in.
In this class you can modify individual pixels or even just get the specific pixel data.
## Next is the PPM file. Here is where we actually generate the PPM file. 
It takes a reference to a canvas and generates a PPM image file based on that canvas.
## Next we have the very important Matrix class. Self explanitory but it represents a Matrix.
Here I have some basic Matrix operations. You Can add two matricies, multiply them together, or get the inverse of the matrix.
On top of multiplying matricies together we can mutiply a Tuple by a matrix to get a new tuple. This is very important and is used to move Tuples in the 3D space.
I also have some Matrix Utility functions that do not operate on a matrix but instead generates a new one based on the function arguments. 
For example, The Tranlation Matrix function in the MatrixUtil namespace takes x y z arguments and generates a matrix that will translate a given point in the x y z directions.
## Next we have the Material class, this class is apart of a future class and stores data about how light should affect a surface.
It stores data such as how much ambient light is absorbed or diffused across the surface. Given that information it can generate a color. The lighting function takes 
a bunch of data such as the direction to a light source, the angle the light is hitting, where the camera is, how where the surface is pointing towards, and if it is in a 
shadow. 
## Next we have the Sphere class.
A Sphere is an object in 3D space. It has matrix which stores any transformations to the sphere. A Material that stores how the surface of the sphere works and an ID. It also has a function to find the normal at any point on the sphere. Also, before any sphere is transformed it is positioned at the origin of the world, (0, 0, 0).
## We are almost to the fun stuff. The next class is the Intersection class. This holds data relevant to a Ray, an object discussed further down.
An intersection is a way to combine data for a Ray, a future object. When a ray is casted into the world it might intersect a sphere and thus we need to know how long it took for that ray to cast and what sphere it hit. Thus we have store the object hit and how long it took for the ray to reach the sphere.
## Finally, into the fun stuff we have the Ray class. A fundamental piece of any Ray Tracer.
A Ray consists of an origin(A point), a direction(A direction) and a collection intersections. When a ray is casted into the scene we need to know what objects it hit, thus the collection of intersections. Also we need to know where it started from as well as the direction it is going in. 
### Ray Functions
Ray::Position returns a point in space after the ray travels x time.<br>
Ray::Cast takes a sphere and cast towards it and determines if there is a hit or not.<br>
Ray::SortIntersection sorts all of the intersections from lowest to highest.<br>
Ray::Hit Returns the first obj to be hit. For example if the the ray hits an obj A after 2 seconds and then another obj B at 1 second we know since it took a smaller amount of time to hit obj B it was hit first and that obj A was hit after.<br>
Ray::transform transforms the ray wether that is scaling, translating or rotating.<br>
## Next we have the Light class. This object represents a light in the scene. It has a position in the world, as well as a color(intensity).
This object is simple it just holds information about a light source.
## Next we have the World Class. 
This object stores a collection of spheres and a light. 
We also have a data struct that contains information required to light the material of a sphere in the scene such as the direction towards the camera, direction the point is facing(the normal), the point we are checking, the object we are lighting, how long it took for the ray to hit the point on the object and some more math information
### World Functions
World::CastRay takes a ray and cast it into the world.<br>
World::PrepareData takes the unmanipulated data and does a few calculations to prepare it to be used in the lighting function.<br>
World::IsShadowed determines if the point we are looking at is behind another object.<br>
World::ShadeHit takes the now prepared data and returns the color of that point on that object in the 3D scene.<br>
## Finally, we have the Camera class which looks into the world.<br>
This class stores a few bits of data. Such as the FOV of the camera, where the camera is in the world, its canvas to draw to, how big each pixel within the canvas will be, the width and height of the canvas, as where the middle of the width and height are.
We also have a special data structure which store the current pixels x and y values and what color it is.
### Camera Functions
On creation the camera calculates how large each pixel using Camera::CalculatePixelSize.<br>
Camera::RayForPixel determines the pixel we are calculating the color for.<br>
Camera::CalculatePixelData determines the color of a pixel and stores it.<br>
Camera::ProcessPixelData takes a collection PixelData and writes them to the canvas.<br>
Camera::GenerateCanvas generates the canvas using Aysnc and futures to generate pixel data for multiple colums of pixels all at once and stores it in a collection of Future pixel data. Then it takes that pixel data and write it to the canvas.<br>
# EXTRAS
## I have simulations that generate different images using different functions. 
### Bullet Sim
For example, the Bullet Sim just creates a projectile and shoots it through this 2D world and plots its path on the canvas.
### Clock Sim
creates points in a circle simulating a clock ticking. Just all at once haha.
### SphereSim
This function takes a bool. For true it renders a sphere in a world with shadows and proper lighting, for false it runs renders the silhouette of that same sphere.
### SceneSim
This function generates a fully fleshed world with lights and walls and multiple spheres. 









