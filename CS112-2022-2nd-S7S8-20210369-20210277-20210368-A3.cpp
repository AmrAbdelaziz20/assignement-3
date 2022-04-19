
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

#include <bits/stdc++.h>
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
void enlargeImage();
void shuffleImage();

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
          rotateImage();
          break;
        case '5':
          DarkenandLighten();
          break;
        case '6':
          detectEdges();
          break;
        case '7':
          enlargeImage();
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