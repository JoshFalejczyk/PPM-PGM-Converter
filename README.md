# PPM-PGM-Converter

This is a project from Fall 2018 for my CS100 course.  It converts a PPM (color) image to PGM (grayscale) given an input file like the example in the repository.  Functions found in image.c include extractions of red, green, and blue from each pixel, and conversion from PPM to PGM using methods of average pixel value, lightness range, and luminosity.  Main.c then tests and runs the functions.

To Run: 
1. Compile image.c and main.c using "gcc -Wall -std=c99 image.c main.c".
2. Run using "./a.exe (a.out if on Mac) function ppm-file pgm-file", or for example, "./a.exe average image1 image2".

Credit:
-The skeleton of the project such as the main.c runner and image.h files were written and supplied by my professor Dr. Jingyuan "Alex" Zhang and the University of Alabama's Computer Science Department.
-The image.c file was written by myself.
