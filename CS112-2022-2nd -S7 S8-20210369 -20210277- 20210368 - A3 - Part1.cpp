/*
Program Name: Grayscale Photo Editor
Program Purpose: Edit grayscale bitmap images
Version: 1.0
Last Modification Date: 7/4/2022
Authors: Mahmoud Hosam Sakr / Amr Abdelaziz Farrag / Mahmoud Ramadan Mohamed
ID: 20210368 / 20210277 / 20210369
Group: S7-S8
Institution: FCAI - CU
Presented to: Dr. Mohamed El Ramly
Teaching Assistant: Eng. Abdulrahman Abdulmonem
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "bmplib.cpp"
using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char image2 [SIZE][SIZE];

void loadImage();
void saveImage();
void invertImage();
void rotateImage();
void blackandwhiteImage();
void detectEdges();
void mergeImage();
void DarkenandLighten();

int main() {
  cout << "Welcome to FCAI Photo Editor!\n";
  cout << "List of names of the available image files:\ncrowd / elephant / fruit / house / photographer\n";
  loadImage();
  cout << "MENU:\n1- Black and White Image\n2- Invert Image\n3- Merge Image\n";
  cout << "4- Rotate Image\n5- Darken and Lighten Image\n6- Detect Image Edges\n";
  cout << "Please enter the index of the desired operation: ";

  int choice;
  while (true){
    bool isNotOK = false;
    cin.ignore();
    cin >> choice;
    switch (choice)
    {
      case 1:
        blackandwhiteImage();
        break;
      case 2:
        invertImage();
        break;
      case 3:
        mergeImage();
        break;
      case 4:
        rotateImage();
        break;
      case 5:
        DarkenandLighten();
        break;
      case 6:
        detectEdges();
        break;
      default:
        cout << "Invalid operation. Please enter a valid operation index: ";
        isNotOK = true;
        break;
    }
    if (isNotOK){
      continue;
    }
    else{
      break;
    }
  }
  saveImage();
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

//_________________________________________
void invertImage() {
  // making black pixels white and vice versa
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
      image[i][j] = abs(image[i][j] - 255);
    }
  }
}

//_________________________________________
void rotateImage() {
  int deg;
  cout << "Please enter the degree with which you want to rotate the image: ";
  while (true){
    bool isInvalid = false;
    cin.ignore();
    cin >> deg;
    switch (deg)
    {
      case 90:
      // rotating the image 180 degrees by swapping the value of the current row
      // with the corresponding row in the end of the image
        for (int i = 0; i < SIZE / 2; i++) {
          for (int j = 0; j < SIZE; j++) {
            swap(image[i][j], image[255-i][j]);
          }
        }
      // transposing the previous image matrix
        for (int i = 0; i < SIZE; i++) {
          for (int j = i; j < SIZE; j++) {
            swap(image[i][j], image[j][i]);
          }
        }
        break;
      
      // rotating the image 180 degrees by swapping the value of the current row
      // with the corresponding row in the end of the image
      case 180:
        for (int i = 0; i < SIZE / 2; i++) {
          for (int j = 0; j < SIZE; j++) {
            swap(image[i][j], image[255-i][j]);
          }
        }
        break;
      
      // transposing the original image matrix
      case 270:
        for (int i = 0; i < SIZE; i++) {
          for (int j = i; j < SIZE; j++) {
            swap(image[i][j], image[j][i]);
          }
        }
        break;

      default:
      cout << "Invalid degree of rotation. Please enter a valid rotation degree: ";
      isInvalid = true;
      break;
    }
    if (isInvalid){
      continue;
    }
    else{
      break;
    }
  }
}

//_________________________________________
void blackandwhiteImage() {
  for(int i = 0 ;i < SIZE ; i++) {
      for(int j = 0 ; j < SIZE ; j++) {
          if (image [i][j]>127)
              image[i][j]=255 ; // change the darker pixels into black ones
          else
              image[i][j]=0;    // change the brighter pixels into white ones
      }
  }
}

//_________________________________________
void detectEdges() {
  // converting the image into b/w image to detect edges easily
  for(int i = 0 ;i < SIZE ; i++) {
      for(int j = 0 ; j < SIZE ; j++) {
          if (image [i][j]>127)
              image[i][j]=255 ; // change the darker pixels into black ones
          else
              image[i][j]=0;    // change the brighter pixels into white ones
      }
  }

  for(int i=0 ; i<SIZE ;i++) {
    for(int j=0 ;j<SIZE ;j++) {
      // if the pixel colors of two neighbor pixels aren't the same
      // then the pixel to the left is an interior pixel
      if (image[i][j]!=image[i+1][j+1])  
          image[i][j]=0;
      
      // if the pixel colors of two neighbor pixels are the same
      // then the pixel to the left is an edge
      else if(image[i][j] == image[i+1][j+1]) 
          image[i][j]=255;
    }
  }
}

//_________________________________________
void mergeImage(){
  // image 2 for merging
  char img2[100];

  cout << "Enter image to merge : ";
  cin >> img2;
  //combine with .bmp
  strcat(img2, ".bmp");
  readGSBMP(img2, image2);

  for (int i = 0 ; i < SIZE ; i++){
    for (int j = 0 ; j < SIZE ; j++){
        image[i][j] = (image[i][j] + image2[i][j]) / 2;
    }
  }
}

//_________________________________________
void DarkenandLighten(){
    int choice2;
    
    cout << "Choose what you want to do: \n 1. Lighten image\n2. Darken image\n";
    while (true) {
      bool isUnavailable = false;
      cout << "Please enter the index of the desired operation: ";
      cin.ignore();
      cin >> choice2;
      switch (choice2)
      {
        case 1:
          for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE ; j++){
              image[i][j] =  image[i][j] + ((255 - image[i][j])) / 2;
            }
          }
          break;

        case 2:
          for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE ; j++){
              image[i][j] = image[i][j] / 2;
            }
          }
          break;

        default:
          cout << "Invalid operation index. Please enter a valid index: ";
          isUnavailable = true;
          break;
      }
      
      if (isUnavailable) {
        continue;
      }
      else {
        break;
      }
  }
}