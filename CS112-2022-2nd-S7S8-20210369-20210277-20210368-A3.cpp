
/*
Program Name: Grayscale Photo Editor
Program Purpose: Edit grayscale bitmap images
Version: 1.2
Last Modification Date: 19/4/2022
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
#include "bmplib.cpp"
#include <string>
#include <bits/stdc++.h>
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
void enlargeImage();
void shuffleImage();
void flip_image();
void mirror_image();
void mirror_the_right_half_from_image();
void mirror_the_lower_half_from_image();
void mirror_the_upper_half_from_image();
void mirror_the_left_half_from_image();
void flippping_image_vertically();
void flippping_image_horizantally();
int main() {
  cout << "Welcome to FCAI Photo Editor!\n";
  while (true)
  {
    // listing the photos available in the same directory as the source code
    cout << "List of names of the available image files:\ncrowd / elephant / fruit / house / photographer\n";
    // loading the image into a 2d array
    loadImage();
    cout << "MENU:\n1- Black and White Image\n2- Invert Image\n3- Merge Image\n";
    cout << "4- Rotate Image\n5- Darken and Lighten Image\n6- Detect Image Edges\n";
    cout << "7- Enlarge Image\nb- Shuffle Image\n";
    cout << "Please enter the index of the desired operation: ";


    char choice;
    while (true){
      bool isNotOK = false;
      cin.ignore();
      // receiving the user's choice and applying the corresponding filters
      cin >> choice;
      switch (choice)
      {
        case '1':
          blackandwhiteImage();
          break;
        case '2':
          invertImage();
          break;
        case '3':
          mergeImage();
          break;
        case '4':
          flip_image();
          break;
        case '5':
          DarkenandLighten();
          break;
        case '6':
          rotateImage();
          break;
        case '7':
          detectEdges();
          break;
        case '8':
          enlargeImage();
          break;
        case 'a':
          mirror_image();
          break;      
        case 'b':
          shuffleImage();
          break;
        default:
          // defending against bad input
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

    // saving the image and asking if the user wants to quit
    saveImage();
    cout << "Do you want to exit?\n";
    string exitorno;
    cin.ignore();
    getline(cin, exitorno);
    for (int i = 0; i < exitorno.size(); i++)
      exitorno[i] = tolower(exitorno[i]);
    
    if (exitorno == "yes")
    {
      exit(0);
    }
  }
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
    
    cout << "Choose what you want to do: \n 1- Lighten image\n2- Darken image\n";
    while (true) {
      bool isUnavailable = false;
      cout << "Please enter the index of the desired operation: ";
      cin.ignore();
      cin >> choice2;
      switch (choice2)
      {
        // Lightening the image by increasing the level of light in each pixel
        case 1:
          for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE ; j++){
              image[i][j] =  image[i][j] + ((255 - image[i][j])) / 2;
            }
          }
          break;

        // Darkening the image by decreasing the level of light in each pixel
        case 2:
          for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE ; j++){
              image[i][j] = image[i][j] / 2;
            }
          }
          break;

        // checking for bad input
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

//_________________________________________
void enlargeImage() {
  int choice, starti, startj, endi, endj;
  while (true) {
    bool isUnavailable = false;
    // asking the user to input the quad order
    cout << "Please enter the order of the quad you want to enlarge 1, 2, 3 or 4: ";
    cin.ignore();
    cin >> choice;
    // detecting the start and end coordinates based on the user's input
    switch (choice)
    {
      case 1:
        starti = startj = 0;
        endi = endj = SIZE / 2;
      break;
    
      case 2:
        starti = 0;
        startj = endi = SIZE / 2;
        endj = SIZE;
        break;

      case 3:
        startj = 0;
        starti = endj = SIZE / 2;
        endi = SIZE;
        break;
      
      case 4:
        starti = startj = SIZE / 2;
        endi = endj = SIZE;
        break;
      
      // checking for bad input
      default:
        cout << "Invalid quad order. Please enter a valid order: ";
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

  // applying the nearest neighbor algorithm by copying the quad into a temporary image and zooming in by a 4x scale
  for (int i = starti, k = 0 ; i < endi; i++, k+=2){
    for (int j = startj, l = 0 ; j < endj; j++, l+=2){
      image2[k][l] = image2[k][l+1] = image2[k+1][l] = image2[k+1][l+1] = image[i][j];
    }
  }
  
  // overwriting the original image with the enlarged image
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      swap(image[i][j], image2[i][j]);
    }
  }
}

//_________________________________________
void shuffleImage() {
  string order;
  // asking the user for the shuffle order
  cout << "Please enter the order of the shuffled image in the format n1 n2 n3 n4 , n = {1,2,3,4} : ";
  cin.ignore();
  getline(cin, order);
  // removing spaces
  regex r (" ");
  order = regex_replace(order, r, "");

  int starti, endi;
  int startj, endj;
  // looping 4 times to apply the 4-quad shuffle
  for (int ltr = 0; ltr < 4; ltr++) {
    // detecting the start and end coordinates based on the user's input
    switch (order[ltr])
    {
    case '1':
      starti = startj = 0;
      endi = endj = SIZE / 2;
      break;
    
    case '2':
      starti = 0;
      startj = endi = SIZE / 2;
      endj = SIZE;
      break;

    case '3':
      startj = 0;
      starti = endj = SIZE / 2;
      endi = SIZE;
      break;
    
    case '4':
      starti = startj = SIZE / 2;
      endi = endj = SIZE;
      break;
    }

    // detecting the beginning and ending of the temporary image based on the iteration either iteration 1, 2, 3 or 4
    int start_l[] = {0, SIZE / 2, 0, SIZE / 2};
    int start_k[] = {0, 0, SIZE / 2, SIZE / 2};

    // looping over both images and assigning the desired quad to the temporary image
    for (int i = starti, k = start_k[ltr]; i < endi; i++, k++) {
      for (int j = startj, l = start_l[ltr]; j < endj; j++, l++) {
        image2[k][l] = image[i][j];
      }
    }
  }
  
  // overwriting the original image with the shuffled image
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      swap(image[i][j], image2[i][j]);
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
//the next function mirror the right half image 
void mirror_the_right_half_from_image(){
    // a nested loop to chech rows and columns 
    for(int i=0 ;i<SIZE ;i++){
        for(int j=0 ; j< SIZE ; j++){
            if(i>=0 && j<128)//the "128"to mirror the first 128 columns only and the other 128 won't change 
            image[i][j]=image[i][255-j];//255-j to mirror the right half only 
        }
    }
    
}
//the next function to mirror down half image 
void mirror_the_lower_half_from_image(){
    // a nested loop to chech rows and columns 
    for(int i=0 ;i<SIZE ;i++){
        for(int j=0 ; j< SIZE ; j++){
            if(i<128 && j>=0)//the "128"to mirror the first 128 rows only and the other 128 won't change
            image[i][j]=image[255-i][j];//255-i to mirror the lower half only
        }
    }
    
}
//the next function mirror the upper half image 
void mirror_the_upper_half_from_image(){
    for(int i=0 ;i<SIZE ;i++){
        for(int j=0 ; j< SIZE ; j++){
            if(i>=128 && j>=0)//the "128"to mirror the first 128 rows only and the other 128 won't change
            image[i][j]=image[255-i][j];//255-i to mirror the upper half only
        }
    }
    
}
//the next function mirror the left half image 
void mirror_the_left_half_from_image(){
    for(int i=0 ;i<SIZE ;i++){
        for(int j=0 ; j< SIZE ; j++){
            if(i>=0 && j>=128)//the "128"to mirror the first 128 columns only and the other 128 won't change
            image[i][j]=image[i][255-j];//255-j to mirror the left half only 
        }
    }
    
}
