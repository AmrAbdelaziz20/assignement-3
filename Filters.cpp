/*
programming 1
assignement 3
name : Amr Abdelaziz Farrag             Id:202102777





*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include <string>


using namespace std;
unsigned char image[SIZE][SIZE][RGB];
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

int main(){
    int  choose ;
    str choice ;
    cout<<"1- Black & White Filter"
    <<endl<<"2- Invert Filter"
    <<endl<<"3- Merge Filter"
    <<endl<<"4- Flip Image"
    <<endl<<"5- Darken and Lighten Image"
    <<endl<<"6- Rotate Image"
    <<endl<<"7- Detect Image Edges "
    <<endl<<"8- Enlarge Image"
    <<endl<<"9- Shrink Image"
    <<endl<<"a- Mirror 1/2 Image"
    <<endl<<"b- Shuffle Image"
    <<endl<<"c- Blur Image"
    <<endl<<"s- Save the image to a file"
    <<endl<<"0- Exit"<<endl;
    cout << "Enter filter Number : ";
    cin >> choice;
    loadImage();
    if (choice == "1" ){
        makethephotoblackandwhite();
        saveimage_for_black_and_white()
    }
    else if (choice == "4" ){
        cout<<"if you want to flip image horizantally choose 1 or  if you want to flip image vertically choose 2: ";
        cin>>choose;
        if (choose == 1 )
            flippping_image_horizantally();
            saveImage();
        else if (choose == 2)
            flippping_image_vertically();
            saveImage();
    }
    
    
    else if (choice == "a")
        cout<<"if you want to mirror image lower half choose 1 or if you want to mirror upper half image choose 2 or if you want to mirror right half image choose 3 or if you want to mirror left half image choose 4: ";
        cin>>choose;
        if (choose == 1){
            mirror_the_lower_half_from_image();
            saveImage();
        }
        else if (choose == 3){
            mirror_the_right_half_from_image();
            saveImage();
        }
        else if (choose == 2){
            mirror_the_upper_half_from_image();
            saveImage();
        }
        else if (choose == 4){
            mirror_the_left_half_from_image();
            saveImage();
        }
    
    return 0;


}
