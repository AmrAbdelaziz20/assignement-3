
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include <string>


using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image2 [SIZE][SIZE][RGB];
unsigned char new_image[SIZE][SIZE];
void loadImage(){
    char img[100];

    //message to the user
    cout << "Enter image name : ";
    cin >> img;
    //combine name with ".bmp"
    strcat(img, ".bmp");
    readRGBBMP(img, image);

}
void saveImage(){
    //to save image
    char svimg [100];
    cout << "Enter new image name : ";
    cin >> svimg;

    strcat(svimg, ".bmp");
    writeRGBBMP(svimg, image);
}
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
void saveimage_for_black_and_white(){
char svimg [100];
cout << "Enter new image name : ";
cin >> svimg;
strcat(svimg, ".bmp");
writeGSBMP(svimg, new_image);

}
void flippping_image_vertically(){// is to make the higherside is the lowerside and the inverse as well
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
void flippping_image_horizantally(){// is to make the right side is the left side and the inverse as well
for (int k = 0; k < (SIZE/2);k++){
    for (int l = 0; l < SIZE;l++){
        for (int n =0 ; n< RGB ; n++ ){
//we make a nested because we want to chech every row and every column
            swap(image[k][l][n] , image[SIZE-1-k][l][n]);//to flip the image horzantally we must inverse every row by making the size -1-l (256 - 1 - k)if l is 50 the 50th row should be 205
            }
        }
}
}
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
                //image[i][j] = image[i][j] / 2;
            }
        }
    }
}
void ShrinkImage(){
    int l = 0 , f = 0;
    int vshrink, result;

    cout << "1. 1/4 --> shrink value = 4" << endl;
    cout << "2. 1/2 --> shrink value = 2" << endl;
    cout << "3. 1/3 --> shrink value = 3" << endl;
    cout << endl;

    cout << "enter shrink amount : ";
    cin >> vshrink;

    result = SIZE / vshrink;
    for (int i = 0 ; i < result ; i++){
        for (int j = 0 ; j < result ; j++){
            for (int n = 0 ; n < RGB ; n++){
                image[i][j][n] = image[l][f][n];
                f = f + vshrink;
            }
        }
        f = 1;
        l = l + vshrink;
}
}
void BlurImage(){
    for (int i = 0 ; i < SIZE ; i++){
        for (int j = 0 ; j < SIZE ; j++){
            for (int n = 0 ; n < RGB ; n++){
                image[i][j][n] = (image[i][j][n] + image[i+1][j][n] + image[i][j+1][n] + image[i+1][j+1][n] + image[i-1][j][n] + image[i][j-1][n] + image[i-1][j-1][n] + image[i+2][j][n] + image[i][j+2][n] + image[i+2][j+2][n] + image[i-2][j][n] + image[i][j-2][n] + image[i-2][j-2][n] + image[i+3][j][n] + image[i][j+3][n] + image[i+3][j+3][n] + image[i-3][j][n] + image[i][j-3][n] + image[i-3][j-3][n]) / 19;
            }

        }
    }
}
int main(){
    int choice;
    cout << "Enter filter Number : ";
    cin >> choice;
    loadImage();
    if (choice == 3){
        Mergeimage();
    }
    else if (choice ==1 ){
        makethephotoblackandwhite();
        saveimage_for_black_and_white()
    }
    else if (choice == 2 ){
        flippping_image_horizantally();
    }
    else if (choice == 4 ){
        flippping_image_vertically();
    }        
        
    else if (choice == 6){
        mirror_the_lower_half_from_image();
    }
    else if (choice == 9){
        mirror_the_right_half_from_image();
    }
    else if (choice == 7){
        mirror_the_upper_half_from_image();
    }
    else if (choice == 8){
        mirror_the_left_half_from_image();
    }
    
    else if (choice == 10){
        BlurImage();
    }
/*    saveImage();
*/
    return 0;


}
