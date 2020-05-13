// Name: Josh Falejczyk
// Program Overview: This program will provide functions that work in conjunction with main.c to convert a PPM (color) image to a PGM (grayscale) image in a variety of methods.
// Refer to image.h for general documentation on each function

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"


ImagePPM *readPPM(char *filename) { 

	FILE* fp = fopen(filename, "r"); // Setup of PPM input file
	if (fp == NULL) {

		return NULL;

	} else {

		ImagePPM *pImagePPM = malloc(sizeof(ImagePPM)); // Setup of ImagePPM object/reading in of PPM input file
		fscanf(fp, "%s", pImagePPM->magic);
		fscanf(fp, "%d%d", &pImagePPM->width, &pImagePPM->height);
		fscanf(fp, "%d", &pImagePPM->max_value);
		pImagePPM->pixels = malloc(sizeof(Pixel *) * pImagePPM->height);
		for (int i = 0; i < pImagePPM->height; i ++) {

			pImagePPM->pixels[i] = malloc(sizeof(Pixel) * pImagePPM->width);

		}

		for (int i = 0; i < pImagePPM->height; i ++) { // Read in each pixel by color

			for (int j = 0; j < pImagePPM->width; j ++) {

				fscanf(fp, "%d", &pImagePPM->pixels[i][j].red);
				fscanf(fp, "%d", &pImagePPM->pixels[i][j].green);
				fscanf(fp, "%d", &pImagePPM->pixels[i][j].blue);

			}

		}
		fclose(fp);


		return pImagePPM;

	}

}


int writePGM(ImagePGM *pImagePGM, char *filename) {

	FILE* fp = fopen(filename, "w"); // Setup of PGM output file
	if (fp == NULL) {

		return 0; // Unsuccessful output

	}

		fprintf(fp, "%s\n", "P2"); //  PGM magic identifier
		fprintf(fp, "%d %d %d\n", pImagePGM->width, pImagePGM->height, pImagePGM->max_value); // Output width, height, and max value
		for (int i = 0; i < pImagePGM->height; i ++) { // Output pixels

			for (int j = 0; j < pImagePGM->width; j ++) {

				fprintf(fp, "%d ", pImagePGM->pixels[i][j]);

			}
			fprintf(fp, "\n");

		}

		return 1; // Successful output

	

}


ImagePGM *extractRed(ImagePPM *pImagePPM) {

	ImagePGM* image; // Setup of ImagePGM object
	image = malloc(sizeof(ImagePGM));
	strcpy(image->magic, "P2");
	image->width = pImagePPM->width;
	image->height = pImagePPM->height;
	image->max_value = pImagePPM->max_value;
	
	image->pixels = malloc(sizeof(int *) * image->height); // Setup of pixels
        for (int i = 0; i < image->height; i ++) {

        	image->pixels[i] = malloc(sizeof(int) * image->width);

        }
	for (int i = 0; i < pImagePPM->height; i ++) { // Copy over/extract red pixels only

		for (int j = 0; j < pImagePPM->width; j ++) {

			image->pixels[i][j] = pImagePPM->pixels[i][j].red;

		}

	}


	return image;


}


ImagePGM *extractGreen(ImagePPM *pImagePPM) {

	ImagePGM* image; // Setup of ImagePGM object
        image = malloc(sizeof(ImagePGM));
        strcpy(image->magic, "P2");
        image->width = pImagePPM->width;
        image->height = pImagePPM->height;
        image->max_value = pImagePPM->max_value;

        image->pixels = malloc(sizeof(int *) * image->height); // Setup of pixels
        for (int i = 0; i < image->height; i ++) {

                image->pixels[i] = malloc(sizeof(int) * image->width);

        }
        for (int i = 0; i < pImagePPM->height; i ++) { // Copy over/extract green pixels only

                for (int j = 0; j < pImagePPM->width; j ++) {

                        image->pixels[i][j] = pImagePPM->pixels[i][j].green;

                }

        }


        return image;


}


ImagePGM *extractBlue(ImagePPM *pImagePPM) {

        ImagePGM* image; // Setup of ImagePGM object
        image = malloc(sizeof(ImagePGM));
        strcpy(image->magic, "P2");
        image->width = pImagePPM->width;
        image->height = pImagePPM->height;
        image->max_value = pImagePPM->max_value;

        image->pixels = malloc(sizeof(int *) * image->height); // Setup of pixels
        for (int i = 0; i < image->height; i ++) {

                image->pixels[i] = malloc(sizeof(int) * image->width);

        }
        for (int i = 0; i < pImagePPM->height; i ++) { // Copy over/extract blue pixels only

                for (int j = 0; j < pImagePPM->width; j ++) {

                        image->pixels[i][j] = pImagePPM->pixels[i][j].blue;

                }

        }


        return image;


}


ImagePGM *computeAverage(ImagePPM *pImagePPM) {

	double avg;
	ImagePGM* image; // Setup of ImagePGM object

	image = malloc(sizeof(ImagePGM));
        strcpy(image->magic, "P2");
        image->width = pImagePPM->width;
        image->height = pImagePPM->height;
        image->max_value = pImagePPM->max_value;
        image->pixels = malloc(sizeof(int *) * image->height);
        for (int i = 0; i < image->height; i ++) { // Setup of pixels

                image->pixels[i] = malloc(sizeof(int) * image->width);

        }

	for (int i = 0; i < pImagePPM->height; i ++) { // Create pixel values by computing average of ImagePPM pixels

		for (int j = 0; j < pImagePPM->width; j ++) {

			avg = (double)(pImagePPM->pixels[i][j].red + pImagePPM->pixels[i][j].green + pImagePPM->pixels[i][j].blue) / 3.0;
			image->pixels[i][j] = round(avg);

		}

	}

	
	return image;


}


ImagePGM *computeLightness(ImagePPM *pImagePPM) {

	ImagePGM* image; // Setup of ImagePGM object
	int min = pImagePPM->pixels[0][0].red;
	int max = pImagePPM->pixels[0][0].red;
	double lightness;

        image = malloc(sizeof(ImagePGM));
        strcpy(image->magic, "P2");
        image->width = pImagePPM->width;
        image->height = pImagePPM->height;
        image->max_value = pImagePPM->max_value;
        image->pixels = malloc(sizeof(int *) * image->height);
        for (int i = 0; i < image->height; i ++) { // Setup of pixels

                image->pixels[i] = malloc(sizeof(int) * image->width);

        }

	for (int i = 0; i < image->height; i ++) { // Use lightness as intensity

		for (int j = 0; j < image->width; j ++) {

			if (pImagePPM->pixels[i][j].red >= pImagePPM->pixels[i][j].green && pImagePPM->pixels[i][j].red >= pImagePPM->pixels[i][j].blue) { // Decide max for each pixel

				max = pImagePPM->pixels[i][j].red;

			} else if (pImagePPM->pixels[i][j].green >= pImagePPM->pixels[i][j].red && pImagePPM->pixels[i][j].green >= pImagePPM->pixels[i][j].blue) {

				max = pImagePPM->pixels[i][j].green;

			} else if (pImagePPM->pixels[i][j].blue >= pImagePPM->pixels[i][j].green && pImagePPM->pixels[i][j].blue >= pImagePPM->pixels[i][j].red) {

				max = pImagePPM->pixels[i][j].blue;

			}

			if (pImagePPM->pixels[i][j].red <= pImagePPM->pixels[i][j].green && pImagePPM->pixels[i][j].red <= pImagePPM->pixels[i][j].blue) { // Decide min for each pixel

                                min = pImagePPM->pixels[i][j].red;

                        } else if (pImagePPM->pixels[i][j].green <= pImagePPM->pixels[i][j].red && pImagePPM->pixels[i][j].green <= pImagePPM->pixels[i][j].blue) {

                                min = pImagePPM->pixels[i][j].green;

                        } else if (pImagePPM->pixels[i][j].blue <= pImagePPM->pixels[i][j].green && pImagePPM->pixels[i][j].blue <= pImagePPM->pixels[i][j].red) {

                                min = pImagePPM->pixels[i][j].blue;

                        }

			lightness = (double)((max + min) / 2.0); // Compute and add lightness for each pixel
			image->pixels[i][j] = round(lightness);

		}

	}


	return image;


}


ImagePGM *computeLuminosity(ImagePPM *pImagePPM) {

	ImagePGM* image; // Setup of ImagePGM object
	double luminosity;

        image = malloc(sizeof(ImagePGM));
        strcpy(image->magic, "P2");
        image->width = pImagePPM->width;
        image->height = pImagePPM->height;
        image->max_value = pImagePPM->max_value;
        image->pixels = malloc(sizeof(int *) * image->height);
        for (int i = 0; i < image->height; i ++) { // Setup of pixels

                image->pixels[i] = malloc(sizeof(int) * image->width);

        }

	for (int i = 0; i < pImagePPM->height; i ++) { // Compute and use luminosity for each pixel using formula

                for (int j = 0; j < pImagePPM->width; j ++) {

                        luminosity = (double)((.21 * pImagePPM->pixels[i][j].red) + (.72 * pImagePPM->pixels[i][j].green) + (.07 * pImagePPM->pixels[i][j].blue));
			image->pixels[i][j] = round(luminosity);

                }

        }


	return image;


}


void freeSpacePPM(ImagePPM *pImagePPM) {

	for (int i = 0; i < pImagePPM->height; i ++) { // Free each pixel

                free(pImagePPM->pixels[i]);

        }
        free(pImagePPM->pixels);
	free(pImagePPM);

}


void freeSpacePGM(ImagePGM *pImagePGM) {

	for (int i = 0; i < pImagePGM->height; i ++) { // Free each pixel

                free(pImagePGM->pixels[i]);

        }
        free(pImagePGM->pixels);
        free(pImagePGM);

}
