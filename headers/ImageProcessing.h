#ifndef IMG_PROCESSING
#define IMG_PROCESSING

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

namespace QTools{
	namespace ImageProcessing
	{
		/**
		 * Compares two bitmaps using overall amount of red, green, and blue
		 * @param  img1 pointer to first bitmap
		 * @param  img2 pointer to second bitmap
		 * @return      the difference between the bitmaps
		 */
		float compareMemoryImg(Gdiplus::Bitmap* img1, Gdiplus::Bitmap* img2);

		/**
		 * Crops a bitmap according to the given parameters. Modifies the original bitmap
		 * @param img    bitmap to be cropped
		 * @param x      x coordinate to start cropping
		 * @param y      y coordinate to start cropping
		 * @param width  width from x coordinate to crop the image
		 * @param height height from y coordinate to crop the image
		 */
		void cropBitmap(Gdiplus::Bitmap** img, int x, int y, int width, int height);

		/**
		 * Crops a bitmap according to the given parameters. Creates a cropped bitmap being pointed to by cropped_img
		 * @param img    bitmap to be cropped
		 * @param cropped_img new bitmap, cropped according to parameter
		 * @param x      x coordinate to start cropping
		 * @param y      y coordinate to start cropping
		 * @param width  width from x coordinate to crop the image
		 * @param height height from y coordinate to crop the image
		 */
		void cropBitmap(Gdiplus::Bitmap** img, Gdiplus::Bitmap** cropped_img, int x, int y, int width, int height);
	}
}

#endif