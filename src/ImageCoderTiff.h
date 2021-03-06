/* ImageCoderTiff.h
 * Copyright 2015 Marco Freudenberger.
 * 
 * This file is part of mfimage library.
 * 
 * Design and implementation by:
 * --------------------------------------------------
 * - Marco Freudenberger (Marco.Freudenberger@gmx.de)
 *
 */

#pragma once
#include "ImageCoder.h"

typedef struct tiff TIFF; // fwd decl
class ImageCoderTiff :
	public ImageCoder
{
public:
	ImageCoderTiff(Image* img);
	virtual ~ImageCoderTiff();
	
	virtual bool canDecode() override;
	virtual bool canEncode() override;
	virtual bool canEncode( PixelMode pixelMode ) override;
	virtual void read(const std::string & filename) override;
	virtual void read(std::istream & stream) override;
	virtual void write(const std::string & filename) override;
	virtual void write(std::ostream & stream) override;

protected:
	void readBilevelOrGray(TIFF* tif, uint32_t width, uint32_t height, double dpiX, double dpiY, uint16_t samplesPerPixel, uint16_t bitsPerSample, int extraAlphaSample, bool inverted, bool separated, uint16_t whiteLevel, uint16_t blackLevel, uint8_t* tiledImageBuffer );
	void readRGB(TIFF* tif, uint32_t width, uint32_t height, double dpiX, double dpiY, uint16_t samplesPerPixel, uint16_t bitsPerSample, int extraAlphaSample, bool separated, uint8_t* tiledImageBuffer);
	void readCMYK(TIFF* tif, uint32_t width, uint32_t height, double dpiX, double dpiY, uint16_t samplesPerPixel, uint16_t bitsPerSample, int extraAlphaSample, bool separated, uint8_t* tiledImageBuffer);
	void readRGBPalette(TIFF* tif, uint32_t width, uint32_t height, double dpiX, double dpiY, uint16_t samplesPerPixel, uint16_t bitsPerSample, int extraAlphaSample, bool separated, uint8_t* tiledImageBuffer);
	void readLab(TIFF* tif, uint16_t photometric, uint32_t width, uint32_t height, double dpiX, double dpiY, uint16_t samplesPerPixel, uint16_t bitsPerSample, int extraAlphaSample, bool separated, uint8_t* tiledImageBuffer);
	
private:
	uint32_t _tiles_planeSize;	// size (in bytes) of a single PLANE in the tiled buffer
	uint32_t _tiles_numPlanes;	// number of planes in the tiled buffer - 1 for continuous config
//	std::unique_ptr<uint8_t[]> _tiledImageBuffer;	// tiled image buffer - empty for non-tiled

	inline int readscanline(TIFF* tif, uint8_t* tiledImageBuffer, uint32_t scanlinesize, void* dest, uint32_t row, uint16_t sample=0 );
	void readAndClose(TIFF* tif);
	void writeAndClose(TIFF* tif);
	inline float calcLabL( uint16_t photometric, void* sample, uint16_t bitsPerSample );
	inline float calcLaba( uint16_t photometric, void* sample, uint16_t bitsPerSample );
	inline float calcLabb( uint16_t photometric, void* sample, uint16_t bitsPerSample );
	
};
