#include "CppUnitTest.h"
#include "../brightener.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace brighteningtest
{
	TEST_CLASS(BrighteningTest)
	{
	public:

        struct PixelData
        {
            int pixel0;
            int pixel1;
            int pixel2;
            int pixel3;
        };

        std::shared_ptr<Image> TestSetup(const PixelData& pixelData, const int& rows, const int& columns)
        {
            auto image = std::make_shared<Image>(rows, columns);
			image->pixels[0] = pixelData.pixel0; image->pixels[1] = pixelData.pixel1;
			image->pixels[2] = pixelData.pixel2; image->pixels[3] = pixelData.pixel3;

            return image;
        }

		
		TEST_METHOD(BrightensWholeImage)
		{
            PixelData pixelData;
            pixelData.pixel0 = 45;
            pixelData.pixel1 = 55;
            pixelData.pixel2 = 65;
            pixelData.pixel3 = 254;
			auto image = TestSetup(pixelData, 2, 2);

			ImageBrightener brightener(image);
			int attenuatedCount = brightener.BrightenWholeImage();
			Assert::AreEqual(1, attenuatedCount);
			Assert::AreEqual(90, int(image->pixels[2]));
		}

		TEST_METHOD(BrightensWithAnotherImage)
		{
            PixelData pixelData;
            pixelData.pixel0 = 45;
            pixelData.pixel1 = 55;
            pixelData.pixel2 = 65;
            pixelData.pixel3 = 75;
			auto image = TestSetup(pixelData, 2, 2);
            ImageBrightener brightener(image);
            
            // Test by brightening only the right part
            pixelData.pixel0 = 0;
            pixelData.pixel1 = 25;
            pixelData.pixel2 = 0;
            pixelData.pixel1 = 25;
            auto brighteningImage = TestSetup(pixelData, 2, 2);


            int attenuatedCount = 0;
            const bool succeeded = brightener.AddBrighteningImage(brighteningImage, attenuatedCount);
            Assert::IsTrue(succeeded);
            Assert::AreEqual(45, int(image->pixels[0])); // left-side pixel is unchanged
            Assert::AreEqual(80, int(image->pixels[1])); // right-side pixel is brightened
            Assert::AreEqual(0, attenuatedCount);
		}
	};
}
