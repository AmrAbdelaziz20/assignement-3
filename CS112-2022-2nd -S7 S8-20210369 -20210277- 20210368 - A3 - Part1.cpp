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
void flip_image();
void mirror_image();

int main() {
  cout << "Welcome to FCAI Photo Editor!\n";
  cout << "List of names of the available image files:\ncrowd / elephant / fruit / house / photographer\n";
  loadImage();
  cout << "MENU:\n1- Black and White Image\n2- Invert Image\n3- Merge Image\n";
  cout << "4- Rotate Image\n5- Darken and Lighten Image\n6- Detect Image Edges\n";
  cout << "Please enter the index of the desired operation: ";

  string choice;
  while (true){
    bool isNotOK = false;
    cin.ignore();
    cin >> choice;
    switch (choice)
    {
      case "1":
        blackandwhiteImage();
        break;
      case "2":
        invertImage();
        break;
      case "3":
        mergeImage();
        break;
      case "4":
        flip_image();
        break;      
      case "5":
        DarkenandLighten();
        break;
      case "6":
        rotateImage();
        break;
      case "7":
        detectEdges();
        break;
      case "a":
        mirror_image();
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
  //the next two functions one for flipping the image horizantally and verically 
  void flippping_image_vertically(){// is to make the higherside is the lowerside and the inverse as well
  for (int k = 0; k < (SIZE);k++){
              for (int l = 0; l < (SIZE/2);l++){
  //we make a nested because we want to chech every row and every column
              /*to flip the image vertically we must inverse every column by making the size -1-l (256 - 1 - l)
              * if l is 50 the 50th column should be 205*/
              swap(image[k][l] , image[k][SIZE-1-l]);
              }//this -1 in "[SIZE-1-l]" because if l is equal 256 it will be 256-1-256= -1 this is the last element in the array  
          }
  }
  void flippping_image_horizantally(){// is to make the right side is the left side and the inverse as well
  for (int k = 0; k < (SIZE/2);k++){
              for (int l = 0; l < SIZE;l++){
  //we make a nested because we want to chech every row and every column
              swap(image[k][l] , image[SIZE-1-k][l]);//to flip the image horzantally we must inverse every row by making the size -1-l (256 - 1 - k)if l is 50 the 50th row should be 205
              }
          }
  }
  void mirror_image(){
    int make_choice;
    cout<<"if you want to mirror the right half from the image choose 1 and if you want to mirror the down half of the image choose 2 and if you want to mirror the upper half choose 3 and if you want to mirror the left half choose 4   : ";
    cin>>make_choice;
    while (make_choice!=1 && make_choice!= 2 && make_choice != 3 &&  make_choice != 4 ){
        cout<<"if you want to mirror the right half from the image choose 1 and if you want to mirror the down half of the image choose 2 and if you want to mirror the upper half choose 3 and if you want to mirror the left half choose 4   :  : ";
        cin>>make_choice;
    }
    if (make_choice==1){
        mirror_the_right_half_from_image();
    }
    else if (make_choice==2){
        mirror_the_lower_half_from_image();
    }
    else if (make_choice==3){
        mirror_the_upper_half_from_image();
    }
    else if (make_choice==4){
        mirror_the_left_half_from_image();
    }
  }
  void flip_Image(){
    int choose;//we take an integer value 1 or 2 to make the user choose between flipping the image vertically or horizantally 
cout<<"welcome ya user ya habibi" <<endl<< "if you want to flip the image horizantally choose 1 and if you want to flip the image vertically choose 2 : "<<endl ;
cin>>choose;
while(choose!=1 && choose!=2){ // if the user choose a number not equal to 1 or 2  this loop will make choose 1 or 2 
    cout<<"welcome ya user ya habibi "<<endl<<"if you want to flip the image horizantally choose 1 and if you want to flip the image vertically choose 2 :";
    cin>>choose;
}
if (choose ==1){
    flipping_image_horizantally();//if the user choose 1 the image  will be flipped horizantally 
}
else if(choose == 2){
    flipping_image_vertically();//if the user  choose 2 the image  will be flipped vertically 
}
    
}
