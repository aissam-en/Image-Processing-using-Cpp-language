#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>

#include "image.h"

using namespace std;

// HW0 #3
// const Image& im: input image
// return the corresponding grayscale image
Image rgb_to_grayscale(const Image& im)
{
  assert(im.c == 3); // only accept RGB images
  Image gray(im.w,im.h,1); // create a new grayscale image (note: 1 channel)
  
  // TODO: calculate the pixels of 'gray'
  for(int j=0;j<im.h;j++)
    for(int i=0;i<im.w;i++)
      gray(i,j) = 0.299*im(i,j,0) + 0.587*im(i,j,1) + 0.114*im(i,j,2) ;
  
  return gray;
  
  NOT_IMPLEMENTED();
}



// Example function that changes the color of a grayscale image
Image grayscale_to_rgb(const Image& im, float r, float g, float b)
{
  assert(im.c == 1);
  Image rgb(im.w,im.h,3);
  
  for(int q2=0;q2<im.h;q2++)for(int q1=0;q1<im.w;q1++)
  {
    rgb(q1,q2,0)=r*im(q1,q2);
    rgb(q1,q2,1)=g*im(q1,q2);
    rgb(q1,q2,2)=b*im(q1,q2);
  }
  
  return rgb;
}



// HW0 #4
// Image& im: input image to be modified in-place
// int c: which channel to shift
// float v: how much to shift
void shift_image(Image& im, int c, float v)
{
  assert(c>=0 && c<im.c); // needs to be a valid channel
  
  // TODO: shift all the pixels at the specified channel
  
  for(int i=0;i<im.w;i++)
    for(int j=0;j<im.h;j++)
    {
      float px = im.data[pixel_address(im,i,j,c)] + v;
      set_pixel(im, i, j, c, px);
    }
  return;

  NOT_IMPLEMENTED();
}



// HW0 #8
// Image& im: input image to be modified in-place
// int c: which channel to scale
// float v: how much to scale
void scale_image(Image& im, int c, float v)
{
  assert(c>=0 && c<im.c); // needs to be a valid channel
  
  // TODO: scale all the pixels at the specified channel

  for(int i=0;i<im.w;i++)
    for(int j=0;j<im.h;j++)
    {
      float px = im.data[pixel_address(im,i,j,c)] * v;  //bdelt "+ v" b "* v"
      set_pixel(im, i, j, c, px);
    }
  
  return;

  NOT_IMPLEMENTED();
}



// HW0 #5
// Image& im: input image to be modified in-place
void clamp_image(Image& im)
{
  // TODO: clamp all the pixels in all channel to be between 0 and 1
  
  for(int i=0; i<im.w; i++)
    for(int j=0; j<im.h; j++)
      for(int c=0; c<im.c; c++)
      {
        if(im(i,j,c)<0.0) im(i,j,c)=0.0; //bdelt "0" b "0.0"
        if(im(i,j,c)>1.0) im(i,j,c)=1.0; //bdelt "1" b "1.0"
      }

  return;

  NOT_IMPLEMENTED();
}



// These might be handy
float max(float a, float b, float c)
{
  return max({a,b,c});
}

float min(float a, float b, float c)
{
  return min({a,b,c});
}

// HW0 #6
// Image& im: input image to be modified in-place
void rgb_to_hsv(Image& im)
{
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from RGB format to HSV format
  float V,m,C,S,H,h;
  for(int i=0; i<im.w; i++)
    for(int j=0; j<im.h; j++)
    {
      float R=im(i,j,0);
      float G=im(i,j,1);
      float B=im(i,j,2);
      
      V = max(R,G,B);
      m = min(R,G,B);
      C = V-m;
      if(R==0.0 && G==0.0 && B==0.0) S=0;
      else S = C/V;

        
      if(C==0) h=0; //bdelt "H" b "h"
      else          //zet "else {}"
      {
        if(V==R) h=(float)(G-B)/C;
        else if(V==G) h=2 + (float)(B-R)/C;
        else if(V==B) h=4 + (float)(R-G)/C;
      }  
        
      
      if(h/6 < 0) H=1+((float)h/6); //zet "/6"
      else H=(float)h/6;
        
      //if(H<0) H++;
        
      set_pixel(im, i, j, 0, H);
      set_pixel(im, i, j, 1, S);
      set_pixel(im, i, j, 2, V);  
    }
    
  return;

  NOT_IMPLEMENTED();
}



// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image& im)
{
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from HSV format to RGB format
  
  for(int i=0; i<im.w; i++)
    for(int j=0; j<im.h; j++)
    {
      float H=im(i,j,0);
      float S=im(i,j,1);
      float V=im(i,j,2);
            
      float C=V*S;
      float X=C*(1-abs(fmod(6.0*H,2) - 1));  
      float m=V-C;
            
      if(H>=0 && H<1.0/6)
      { set_pixel(im,i,j,0,C+m);  set_pixel(im,i,j,1,X+m);  set_pixel(im,i,j,2,m); }
            
      else if(H>=1.0/6 && H<2.0/6)
      { set_pixel(im,i,j,0,X+m);  set_pixel(im,i,j,1,C+m);  set_pixel(im,i,j,2,m); }
          
      else if(H>=2.0/6 && H<3.0/6)
      { set_pixel(im,i,j,0,m);  set_pixel(im,i,j,1,C+m);  set_pixel(im,i,j,2,X+m); }
            
      else if(H>=3.0/6 && H<4.0/6)
      { set_pixel(im,i,j,0,m);  set_pixel(im,i,j,1,X+m);  set_pixel(im,i,j,2,C+m); }
            
      else if(H>=4.0/6 && H<5.0/6)
      { set_pixel(im,i,j,0,X+m);  set_pixel(im,i,j,1,m);  set_pixel(im,i,j,2,C+m); }
            
      else if(H>=5.0/6 && H<1)
      { set_pixel(im,i,j,0,C+m);  set_pixel(im,i,j,1,m);  set_pixel(im,i,j,2,X+m); }

    }
        
  return;

  NOT_IMPLEMENTED();  
}



// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image& im)
{
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from RGB format to LCH format
  
  return;

  NOT_IMPLEMENTED(); 
}



// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image& im)
{
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from LCH format to RGB format
  
  return;

  NOT_IMPLEMENTED();
}



// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }
void Image::shift(int c, float v) { shift_image(*this,c,v); }
void Image::scale(int c, float v) { scale_image(*this,c,v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }
void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }
void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
void Image::RGBtoLCH(void) { rgb_to_lch(*this); }
