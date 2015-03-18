#include <SDL.h>
#include <SDL_image.h>

/* Load Image from file function */
SDL_Surface *load_Image (char *filename)
{
	//We are going to take an image in as a parameter
	//and return a pointer to the optimized vers.

	//temporarily store the image here
	SDL_Surface* loadedImage = NULL;

	//because we need to optimize it
	SDL_Surface* finalImage = NULL;

	/* Getting the image from the file system and attaching 
	an address to the pointer.  Just in case you haven't noticed,
	from previous verisons of this code, the LoadBMP function was
	used.  Including the SDL Image header allows me to load image
	formats other than but still including BMP files */
	loadedImage = IMG_Load(filename);

	//if my pointer is not null / if i was able to get the image successfully
	if( loadedImage != NULL)
	{
		//we will optimize the image for SDL
		//this will create a new version of the image
		//in the same format as the screen
		finalImage = SDL_DisplayFormat( loadedImage );

		//the "loadedImage" has been optimized for showing now
		//we no longer need the original image, it is literally
		//of no use to us.
		SDL_FreeSurface (loadedImage);

		//optimizing it here rather than when it is blitted (drawn to surface)
		//is more efficient.  chances are you may need this image again; but now
		//since you optimize it when it is first loaded, it doesn't need to be
		//optimized again upon drawing it to the surface

		/* Color Keying - some sprites have backgrounds in them that we don't need
		(ex. player spritesheet with a green background).  You don't want that back-
		ground to show up in game. */
		if (finalImage != NULL)
		{
			//This creates a color key, in other words, defines that color I want to get rid of.
			Uint32 colorkey = SDL_MapRGB( finalImage->format, 0, 0xFF, 0xFF );
			
			//This statement says: Take the optimized image (1st argument), and take this color (3rd argument) out of it.
			//The 2nd argument exists because the "SetColorKey" function can do other things other than get rid of a color.
			//But I probably won't be using it for any other reason.  So, "SRCCOLORKEY" says "I want to use the color key func.".
			SDL_SetColorKey (finalImage, SDL_SRCCOLORKEY, colorkey);
		}
	}

	//returns pointer to the optimized image
	return finalImage;
}

/* Displaying Image function */
void show_Surface (float x, float y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	//Temporary rectangle used to tell function where to display source surface on screen
	SDL_Rect offset;

	//Taking in the positions given to the function
	offset.x = (int)x;
	offset.y = (int)y;

	//Displaying the surface
	SDL_BlitSurface( source, clip, destination, &offset);
}