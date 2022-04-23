/*
Program Name: RGB Photo Editor
Program Purpose: Edit RGB bitmap images
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
unsigned char image[SIZE][SIZE][RGB];
unsigned char new_image[SIZE][SIZE];
unsigned char image2 [SIZE][SIZE][RGB];
void loadImage();
void saveImage();
void saveimage_for_black_and_white();
void makethephotoblackandwhite();
void saveImage2();
void invertImage();
void rotateImage();
void blackandwhiteImage();
void detectEdges();
void Mergeimage();
void DarkenandLighten();
void enlargeImage();
void shuffleImage();
void ShrinkImage();
void flip_image();
void BlurImage();
void mirror_image();
void mirror_the_right_half_from_image();
void mirror_the_lower_half_from_image();
void mirror_the_upper_half_from_image();
void mirror_the_left_half_from_image();
void flipping_image_vertically();
void flipping_image_horizantally();
//________________________________________
int main() {
  cout << "Welcome to FCAI Photo Editor!\n";
  while (true)
  {
    // listing the photos available in the same directory as the source code
    cout << "List of names of the available image files:\ncrowd / elephant / fruit / house / photographer\n";
    // loading the image into a 2d array
    loadImage();
    cout << "MENU:\n1- Black and White Image\n2- Invert Image\n3- Merge Image\n";
    cout << "4-Flip Image\n5- Rotate Image\n6- Darken and Lighten Image\n7- Detect Image Edges\n";
    cout << "8- Enlarge Image\n9- Shrink Image\na- Mirror Image\nb- Shuffle Image\nc- Blur Image";
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
          saveimage_for_black_and_white();
          break;
        case '2':
          invertImage();
          saveImage();
          break;
        case '3':
          Mergeimage();
          saveImage();
          break;
        case '4':
          flip_image();
          saveImage();
          break;
        case '5':
          DarkenandLighten();
          saveImage();
          break;
        case '6':
          rotateImage();
          saveImage();
          break;
        case '7':
          makethephotoblackandwhite();
          detectEdges();
          saveImage();
          break;
        case '8':
          enlargeImage();
          saveImage();
          break;
        case '9':
            ShrinkImage();
            saveImage2();
            break;
        case 'a':
          mirror_image();
          saveImage();
          break;
        case 'b':
          shuffleImage();
          saveImage();
          break;
        case 'c':
          BlurImage();
          saveImage();
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

//________________________________________
void loadImage(){
    char img[100];

    //message to the user
    cout << "Enter image name : ";
    cin >> img;
    //combine name with ".bmp"
    strcat(img, ".bmp");
    readRGBBMP(img, image);

}
//________________________________________
void saveImage(){
    //to save image
    char svimg [100];
    cout << "Enter new image name : ";
    cin >> svimg;

    strcat(svimg, ".bmp");
    writeRGBBMP(svimg, image);
}
//________________________________________
void saveImage2(){
    //for saving another image for shrink filter
    char svimg2 [100];
    cout << "Enter new image name : ";
    cin >> svimg2;

    strcat(svimg2, ".bmp");
    writeRGBBMP(svimg2, image2);
}
//________________________________________
//the next function mirror the right half image
void mirror_the_right_half_from_image(){
    // a nested loop to chech rows and columns
    for(int i=0 ;i<SIZE ;i++){
        for(int j=0 ; j< SIZE ; j++){
            for (int n =0 ; n< RGB ; n++ ){
            if(i>=0 && j<128)//the "128"to mirror the first 128 columns only and the other 128 won't change
            image[i][j][n]=image[i][255-j][n];//255-j to mirror the right half only
            }
        }

    }
}
//________________________________________
//the next function to mirror down half image
void mirror_the_lower_half_from_image(){
    // a nested loop to chech rows and columns
    for(int i=0 ;i<SIZE ;i++){
        for(int j=0 ; j< SIZE ; j++){
            for (int n =0 ; n< RGB ; n++ ){
                if(i<128 && j>=0)//the "128"to mirror the first 128 rows only and the other 128 won't change
                image[i][j][n]=image[255-i][j][n];//255-i to mirror the lower half only
            }
        }
    }
}
//________________________________________
//the next function mirror the upper half image
void mirror_the_upper_half_from_image(){
    for(int i=0 ;i<SIZE ;i++){
        for(int j=0 ; j< SIZE ; j++){
            for (int n =0 ; n< RGB ; n++ ){
                if(i>=128 && j>=0)//the "128"to mirror the first 128 rows only and the other 128 won't change
                image[i][j][n]=image[255-i][j][n];//255-i to mirror the upper half only
        }
    }

}
}
//________________________________________
//the next function mirror the left half image
void mirror_the_left_half_from_image(){
    for(int i=0 ;i<SIZE ;i++){
        for(int j=0 ; j< SIZE ; j++){
            for (int n =0 ; n< RGB ; n++ ){
            if(i>=0 && j>=128)//the "128"to mirror the first 128 columns only and the other 128 won't change
            image[i][j][n]=image[i][255-j][n];//255-j to mirror the left half only
        }
    }

}
}
//________________________________________
void detect_image_edges(){//function to detect the image after make the photo black and white
    for(int i=0 ; i<SIZE ;i++){
        for(int j=0 ;j<SIZE ;j++){
            if (new_image[i][j]!= new_image[i+1][j+1]){// if two pixels are after each other havenot the same color it will be white
                new_image[i][j]=0;
            }
            else if(new_image[i][j] == new_image[i+1][j+1]){// if two pixels are after each other havenot the same color it will be black
                new_image[i][j]=255;

        }
    }
}
}
//________________________________________
void makethephotoblackandwhite(){
    for ( int k = 0 ; k < SIZE ; k++ ) {
            for ( int l = 0 ; l < SIZE ; l++ ) {
                unsigned char r = image[k][l][0];
                unsigned char g = image[k][l][1];
                unsigned char b = image[k][l][2];
                new_image[k][l] = (unsigned char)(.299*r + .587*g + .114*b);
            }
        }
    for(int i = 0 ;i < SIZE ; i++){//nested loop will iterate the 2d array (rows and columns)
        for(int j = 0 ; j < SIZE ; j++){

                if (new_image[i][j]> 127)
                    new_image[i][j] = 255 ; //make it black
                else
                    new_image[i][j] = 0;    //make it white
            }


    }
}
//________________________________________
void saveimage_for_black_and_white(){
char svimg [100];
cout << "Enter new image name : ";
cin >> svimg;
strcat(svimg, ".bmp");
writeGSBMP(svimg, new_image);

}
//________________________________________
void flipping_image_vertically(){// is to make the higherside is the lowerside and the inverse as well
for (int k = 0; k < (SIZE);k++){
            for (int l = 0; l < (SIZE/2);l++){
                for (int n =0 ; n< RGB ; n++ ){//we make a nested because we want to chech every row and every column
            /*to flip the image vertically we must inverse every column by making the size -1-l (256 - 1 - l)
            * if l is 50 the 50th column should be 205*/
            swap(image[k][l][n] , image[k][SIZE-1-l][n]);
            }//this -1 in "[SIZE-1-l]" because if l is equal 256 it will be 256-1-256= -1 this is the last element in the array
        }
}
}
//________________________________________
void flipping_image_horizantally(){// is to make the right side is the left side and the inverse as well
for (int k = 0; k < (SIZE/2);k++){
    for (int l = 0; l < SIZE;l++){
        for (int n =0 ; n< RGB ; n++ ){
//we make a nested because we want to chech every row and every column
            swap(image[k][l][n] , image[SIZE-1-k][l][n]);//to flip the image horzantally we must inverse every row by making the size -1-l (256 - 1 - k)if l is 50 the 50th row should be 205
            }
        }
}
}
//________________________________________
void Mergeimage(){
    // image 2 for merging
    char img2[100];



    cout << "Enter image to merge : ";
    cin >> img2;
    //combine with .bmp
    strcat(img2, ".bmp");
    readRGBBMP(img2, image2);

    for (int i = 0 ; i < SIZE ; i++){
        for (int j = 0 ; j < SIZE ; j++){
            for (int n = 0 ; n < RGB ; n++){
               image[i][j][n] = (image[i][j][n] + image2[i][j][n]) / 2;
            }
        }
    }


}
//________________________________________
void DarkenandLighten(){
    int choice2;
    cout << "1. Lighten image" << endl << "2. Darken image" << endl;
    cin >> choice2;
    if (choice2 == 1){
        for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE ; j++){
                for (int n = 0 ; n < RGB ; n++){
                  image[i][j][n] =  image[i][j][n] + ((255 - image[i][j][n])) / 2;
                }
            }
        }

    }else if (choice2 == 2){
        for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE ; j++){
                for (int n = 0 ; n < RGB ; n++){
                    image[i][j][n] = image[i][j][n] / 2;
                }
            }
        }
    }
}
//________________________________________
void ShrinkImage(){
   // char img2[100]
    int l = 0 , f = 0;
    int vshrink, result; // vshrink is the value of the shrink

    cout << "1. 1/4 --> shrink value = 4" << endl;
    cout << "2. 1/2 --> shrink value = 2" << endl;
    cout << "3. 1/3 --> shrink value = 3" << endl;
    cout << endl;

    cout << "enter shrink amount : ";
    cin >> vshrink;

    //for dividing the size of the image
    result = SIZE / vshrink;
    for (int i = 0 ; i < result ; i++){
        for (int j = 0 ; j < result ; j++){
            for (int n = 0 ; n < RGB ; n++){
                image2[i][j][n-2] = image[l][f][n-2];
                image2[i][j][n-1] = image[l][f][n-1];
                image2[i][j][n] = image[l][f][n];
            }
            f = f + vshrink;
        }
        f = 1;
        l = l + vshrink;
}
}
//________________________________________
void BlurImage(){
    for (int i = 0 ; i < SIZE ; i++){
        for (int j = 0 ; j < SIZE ; j++){
            for (int n = 0 ; n < RGB ; n++){
                    //adding adjacent pixels in one pixel
                image[i][j][n] = (image[i][j][n] + image[i+1][j][n] + image[i][j+1][n] + image[i+1][j+1][n] + image[i-1][j][n] + image[i][j-1][n] + image[i-1][j-1][n] + image[i+2][j][n] + image[i][j+2][n] + image[i+2][j+2][n] + image[i-2][j][n] + image[i][j-2][n] + image[i-2][j-2][n] + image[i+3][j][n] + image[i][j+3][n] + image[i+3][j+3][n] + image[i-3][j][n] + image[i][j-3][n] + image[i-3][j-3][n]) / 19;
            }

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
  //_________________________________________
  void flip_image(){
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
//_________________________________________
void invertImage() {
  // making black pixels white and vice versa
    for (int k = 0; k < RGB; k++){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
            image[i][j][k] = abs(image[i][j][k] - 255);
            }
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
        for (int k = 0; k < RGB; k++){
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE; j++) {
                    swap(image[i][j][k], image[255-i][j][k]);
                }
            }
        }
      // transposing the previous image matrix
        for (int k = 0; k < RGB; k++) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = i; j < SIZE; j++) {
                    swap(image[i][j][k], image[j][i][k]);
                }
            }
        }
        break;

      // rotating the image 180 degrees by swapping the value of the current row
      // with the corresponding row in the end of the image
      case 180:
        for (int k = 0; k < RGB; k++){
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE; j++) {
                    swap(image[i][j][k], image[255-i][j][k]);
                }
            }
        }
        break;

      // transposing the original image matrix
      case 270:
        for (int k = 0; k < RGB; k++) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = i; j < SIZE; j++) {
                    swap(image[i][j][k], image[j][i][k]);
                }
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
  for (int k = 0; k < RGB; k++) {
    for (int i = starti, x = 0 ; i < endi; i++, x+=2){
        for (int j = startj, l = 0 ; j < endj; j++, l+=2){
        image2[x][l][k] = image2[x][l+1][k] = image2[x+1][l][k] = image2[x+1][l+1][k] = image[i][j][k];
        }
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
    int start_x[] = {0, 0, SIZE / 2, SIZE / 2};

    // looping over both images and assigning the desired quad to the temporary image
    for (int k = 0; k < RGB; k++) {
        for (int i = starti, x = start_x[ltr]; i < endi; i++, x++) {
            for (int j = startj, l = start_l[ltr]; j < endj; j++, l++) {
                image2[x][l][k] = image[i][j][k];
            }
        }
    }
  }

  // overwriting the original image with the shuffled image
  for (int k = 0; k < RGB; k++) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
        swap(image[i][j][k], image2[i][j][k]);
        }
    }
  }
}

