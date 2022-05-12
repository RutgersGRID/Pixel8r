/**
 * Getting Started with Capture.
 * 
 * Reading and displaying an ifkeymage from an attached Capture device. 
 */

import processing.video.*;
import peasy.*;

PeasyCam pcam;
Capture cam;
boolean record;
boolean reset = false;
int  mode = 0;
int modes = 4; //starting at 0
boolean snap = false;
int num = 0;

PImage img;  // The source image
int cellsize = 2; // Dimensions of each cell in the grid
float fcellsize = float(cellsize);
int columns, rows;   // Number of columns and rows in our system
float zfactor = 2.5;

void setup() {
  // size(1200, 800, P3D);
  //size(1920, 1080, P3D);
  //Full screen works, and it needs the P3D value passed in.
  fullScreen(P3D);


  String[] cameras = Capture.list();

  if (cameras.length == 0) {
    println("There are no cameras available for capture.");
    exit();
  } else {
    println("Available cameras:");
    for (int i = 0; i < cameras.length; i++) {
      println(cameras[i]);
    }
  }


  // If no device is specified, will just use the default.  
  //cam = new Capture(this, 320, 240);
  //cam = new Capture(this, 320, 240, "Logitech Camera", 30);
  // Microsoft® LifeCam HD-3000
  //FaceTime HD Camera,size=320x180,fps=30
  //cam = new Capture(this, 320, 240, "FaceTime HD Camera", 30);
  cam = new Capture(this, 320, 240, "Microsoft® LifeCam HD-3000", 30);


  pcam = new PeasyCam(this, width);
  pcam.setMinimumDistance(100);
  pcam.setMaximumDistance(700);   

  img = loadImage("moo.jpg"); 
  img.resize(cam.width, cam.height);

  //img = cam.read();
  columns = cam.width / cellsize;  // Calculate # of columns
  rows = cam.height / cellsize;  // Calculate # of rows
  cam.start();
}


void draw() {
  background(0);
  img = cam;
  if (cam.available())
  {
    cam.read();
    cam.loadPixels();
    //***chunck

    // Begin loop for columns
    for ( int i = 0; i < columns; i++) {
      // Begin loop for rows
      for ( int j = 0; j < rows; j++) {
        int x = i*cellsize + cellsize/2;  // x position
        int y = j*cellsize + cellsize/2;  // y position
        int loc = x + y*cam.width;  // Pixel array location
        color c = cam.pixels[loc];  // Grab the color

        //float z = grayscale(c);
        float z = grayscale(img.pixels[loc])*zfactor;
        // Calculate a z position as a function of mouseX and pixel brightness
        //float z = (1000 / float(width)) * brightness(cam.pixels[loc]) - 20.0;
        //  float z = (mouseY / float(width)) * brightness(cam.pixels[loc]) - 20.0;
        // Translate to the location, set fill and stroke, and draw the rect
        pushMatrix();
        // translate(x + 200, y + 100);
        // rectMode(CENTER);
        //rect(0, 0, cellsize, cellsize);
        //ellipseMode(CENTER);
        //ellipse(0, 0, cellsize, cellsize);
        //box(cellsize, cellsize, cellsize);
        switch  (mode) {
        case 0:
          translate(x-160, y-120, z );
          fill(c, 204);
          noStroke();
          box(cellsize, cellsize, cellsize);
          break;
        case 1:
          translate(x-160, y-120, cellsize );
          fill(c, 204);
          noStroke();
          box(cellsize, cellsize, z);
          break;
        case 2:
          translate(x-160, y-120, z );
          fill(c, 204);
          noStroke();
          box(cellsize, cellsize, z);
          break;
        case 3:
          translate(x-160, y-120, z );
          fill(c, 204);
          noStroke();
          box(cellsize, cellsize, 0);
          break;
        case 4:
          translate(x-160, y-120, z );
          fill(c, 204);
          noStroke();
          ellipse(0, 0, cellsize, cellsize);
          break;
        default: 
          translate(x-160, y-120, cellsize );
          fill(c, 204);
          noStroke();
          box(cellsize, cellsize, cellsize);
          break;
        }
        //sphere(fcellsize);
        popMatrix();
      }
    }
  }
  /*
  if (record) {
   //export an x3d file, change to OBJExport for obj
   x3D = (MeshExport) createGraphics(320, 240, "nervoussystem.obj.X3DExport", "lc.x3d");
   x3D.setColor(true);
   x3D.beginDraw();
   //drawNoise(x3D);
   }
   */

  //image(cam, 140, 0);
  /*
  if (record) {
   x3D.endDraw();
   x3D.dispose();
   record = false;
   }
   */
  if (record) {
    record = false;
  }
  if (snap) {
    snap = false;
  }
  if (reset) {
    pcam.reset();
    zfactor = 1;
    reset = false;
  }
} 

//convert RGB to grayscale
int grayscale(color _c) {  
  //extract RGB values
  int r = (_c >> 16) & 0xFF;
  int g = (_c >> 8) & 0xFF;
  int b = _c & 0xFF;

  //typical NTSC color to luminosity conversion
  int intensity = int(0.2989*r + 0.5870*g + 0.1140*b);
  if (intensity> 0) intensity=int(map(intensity, 0, 255, 0, 100));
  return intensity;
}

void keyPressed() {
  // use a key press so that it doesn't make a million files
  if (key == 'a') {
    zfactor += .5;
    println("zFactor: " + zfactor);
  }
  if (key == 'd') {
    zfactor -= .5;
    println("zFactor: " + zfactor);
  }
  if (key == 'r') record = true;
  if (key == 'w') 
  {
    if (mode < modes) 
    {
      mode++;
    } else
    {
      mode = 0;
    }
  }

  if (key == ' ') {
    key = 0;
    zfactor = 2;
    reset = true;
    println("reset: " + zfactor);
  }
  if (key == 'g') {
    //num++;
    saveFrame("./output/bgphoto####.png" );
    //img = loadImage("bgphoto" + num + ".png"); 
    img = cam;

    // img = image(cam, 0, 0, cam.width, cam.height);
    img.resize(cam.width, cam.height);
  }
}
