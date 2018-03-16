#include "ImageProcessing.h"

namespace QTools{
	namespace ImageProcessing
	{
		float compareMemoryImg(Gdiplus::Bitmap* img1, Gdiplus::Bitmap* img2){
			// Create bitmap data for later use to lock bits
			Gdiplus::BitmapData* bitmapData1 = new Gdiplus::BitmapData;
			Gdiplus::BitmapData* bitmapData2 = new Gdiplus::BitmapData;
			// initialize and instantiate variables
			float difference, per_diff = 0;
			unsigned int height, width, current_pixel_place = 0; // current_pixel_place used to calculations on bitmap because of its stride
			height = img1->GetHeight();
			width = img1->GetWidth();
			if(height > img2->GetHeight()) height = img2->GetHeight();
			if(width > img2->GetWidth()) width = img2->GetWidth();

			// create a rectangle of the length of the largest picture and lock it's bits
			// the lock is necessary for performance
			Gdiplus::Rect rect(0,0, width, height);
			img1->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, bitmapData1);
			img2->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, bitmapData2);

			// Set pointers to first part of bitmap line - must be unsigned char to read each byte correctly
			unsigned char* pixels_1 = (unsigned char*) bitmapData1->Scan0;
			unsigned char* pixels_2 = (unsigned char*) bitmapData2->Scan0;

			// Cycle through all bitmap information - compare
			// increment through each pixel, but multiply by 4 when calculating current pixel place
			// due to 4 bytes being read each time, Red Green Blue and Alpha values
			for(unsigned int x = 0; x < height; x++){
				for(unsigned int y = 0; y < width; y++){
					current_pixel_place = x * bitmapData1->Stride / 4 + y*4;

					//Compare first 3 values for each pixel, red green blue - not this order
					for(int z = 0; z < 2; z ++)
					{
						difference = (float) pixels_1[current_pixel_place + z] - pixels_2[current_pixel_place + z];
						if(difference < 0) difference *= -1;
						per_diff += difference;
					}
				}
			}
			// clean up
			img1->UnlockBits(bitmapData1);
			img2->UnlockBits(bitmapData2);
			delete bitmapData1;
			delete bitmapData2;
			DeleteObject(bitmapData1);
			DeleteObject(bitmapData2);

			// return percentage - added up all difference of colors / total pixels * (R + G + B possible values = 768)
			return (per_diff / (width * height * 768));
		}

		void cropBitmap(Gdiplus::Bitmap** img, int x, int y, int width, int height) {
			if((*img)->GetHeight() >= height + y && (*img)->GetWidth() >= width + x)
			{
				Gdiplus::Bitmap* temp = (*img)->Clone(x, y, width, height, PixelFormat32bppARGB);
				// delete bitmap before changing location
				delete *img;
				*img = temp;
			}
		}

		void cropBitmap(Gdiplus::Bitmap** img, Gdiplus::Bitmap** cropped_img, int x, int y, int width, int height) {
			// delete any current information at cropped pointer
			// pointer destination will be modified
			delete *cropped_img;
			*cropped_img = (*img)->Clone(x, y, width, height, PixelFormat32bppARGB);
		}
	}
}