#pragma once

#include "DTex/MetaData.hpp"

#include <vector>
#include <optional>

namespace DTex
{
	namespace detail
	{
		class PrivateAccessor;
	}

	class TextureDocument
	{
	public:
		/*
			Gets the file format of the file that was loaded.
		*/
		FileFormat GetSourceFileFormat() const;

		/*
			Returns the base dimensions of the loaded image.
		*/
		const Dimensions& GetBaseDimensions() const;

		/*
			Returns the dimensions of the mipmap at the specified miplevel.
			Use miplevel 0 for base dimensions.
			Returns an empty optional if MipLevel argument is equal or higher than GetMipLevelCount()
		*/
		std::optional<Dimensions> GetDimensions(uint32_t mipLevel = 0) const;

		/*
			Returns the pixel format of the loaded image.
		*/
		PixelFormat GetPixelFormat() const;

		/*
			Returns true if the PixelFormat of the image is a compressed type.
		*/
		bool IsCompressed() const;

		/*
			Returns the color space type of the loaded image.
		*/
		ColorSpace GetColorSpace() const;

		/*
			Returns the texture type of the loaded image.
		*/
		TextureType GetTextureType() const;

		/*
			Returns the total size required for storing all the mips and image array elements.
		*/
		size_t GetTotalSizeRequired() const;

		/*
			Returns the length of the mipmap chain of the loaded image.
		*/
		uint32_t GetMipLevelCount() const;

		/*
			Returns the offset for a given MipLevel from the start of a linear buffer.
			Returns an empty optional if MipLevel argument is equal or higher than GetMipLevelCount()
		*/
		std::optional<size_t> GetMipLevelOffset(uint32_t mipLevel) const;

		/*
			Returns the size of a given MipLevel in bytes.
			Returns an empty optional if MipLevel argument is equal or higher than GetMipLevelCount()
		*/
		std::optional<size_t> GetMipLevelSize(uint32_t mipLevel) const;

		uint32_t GetArrayLayerCount() const;

		/*
			Returns the size of the image at the specified mipLevel.
		*/
		std::optional<size_t> GetDataSize(uint32_t mipLevel) const;

		/*
			Gets a pointer to the imagedata of the specified mipLevel.
		*/
		std::optional<const uint8_t*> GetData(uint32_t mipLevel) const;

		uint8_t* GetInternalBufferData() const;

	private:
		MetaData metaData;

		std::vector<uint8_t> byteArray;

		friend class detail::PrivateAccessor;
	};

	using TexDoc = TextureDocument;
}

inline DTex::FileFormat DTex::TextureDocument::GetSourceFileFormat() const
{
	return metaData.srcFileFormat;
}

inline const DTex::Dimensions& DTex::TextureDocument::GetBaseDimensions() const
{
	return metaData.baseDimensions;
}

inline DTex::PixelFormat DTex::TextureDocument::GetPixelFormat() const
{
	return metaData.pixelFormat;
}

inline bool DTex::TextureDocument::IsCompressed() const
{
	return Tools::IsCompressed(metaData.pixelFormat);
}

inline DTex::ColorSpace DTex::TextureDocument::GetColorSpace() const
{
	return metaData.colorSpace;
}

inline DTex::TextureType DTex::TextureDocument::GetTextureType() const
{
	return Tools::ToTextureType(metaData.baseDimensions, metaData.arrayLayerCount);
}

inline uint32_t DTex::TextureDocument::GetMipLevelCount() const
{
	return metaData.mipLevelCount;
}

inline std::optional<size_t> DTex::TextureDocument::GetDataSize(uint32_t mipLevel) const
{
	if (mipLevel >= metaData.mipLevelCount)
		return {};

	return Tools::CalcImageDataSize_Unsafe(Tools::CalcMipmapDimensions(metaData.baseDimensions, mipLevel), metaData.pixelFormat);
}