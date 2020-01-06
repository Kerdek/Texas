#pragma once

#include "Texas/LoadResult.hpp"
#include "Texas/Result.hpp"
#include "Texas/ByteSpan.hpp"
#include "Texas/TextureDocument.hpp"
#include "Texas/OpenFile.hpp"
#include "Texas/OpenBuffer.hpp"

namespace Texas
{
	/*
		Loads the metadata from an image buffer, and stores data in Texas::OpenBuffer to prepare for loading imagedata.

		The returned struct can be used to allocate a buffer large enough to load the imagedata onto.
		This can be done with Texas::loadImageData().
	*/
	[[nodiscard]] LoadResult<OpenBuffer> loadFromBuffer(const std::byte* fileBuffer, std::size_t bufferLength);

	/*
		Loads the metadata from an image buffer, and stores data in Texas::OpenBuffer to prepare for loading imagedata.

		The returned struct can be used to allocate a buffer large enough to load the imagedata onto, as well as working memory.
		This can be done with Texas::loadImageData().
	*/
	[[nodiscard]] LoadResult<OpenBuffer> loadFromBuffer(ConstByteSpan inputBuffer);

	/*
		Loads the imagedata of a file opened with LoadFromBuffer into dstBuffer.

		Requirements:
			The file-buffer passed into Texas::loadFromBuffer() must NOT have changed since calling said function.
			
			dstBuffer MUST be ATLEAST the size returned by OpenBuffer::memoryRequired().

			workingMemory MUST be ATLEAST the size return by OpenBuffer::memoryRequired().
			If the size returned by OpenBuffer::workingMemoryRequired is 0, you can pass a default-constructed ByteSpan, or one that points to nullptr.
	*/
	[[nodiscard]] Result loadImageData(const OpenBuffer& file, ByteSpan dstBuffer, ByteSpan workingMemory);

	/*
		Loads the imagedata of a file opened with LoadFromBuffer into dstBuffer.

		Requirements:
			The file-buffer passed into Texas::loadFromBuffer() must NOT have changed since calling said function.

			dstBuffer MUST be ATLEAST the size returned by OpenBuffer::memoryRequired().

			workingMemory MUST be ATLEAST the size return by OpenBuffer::memoryRequired().
	*/
	[[nodiscard]] Result loadImageData(const OpenBuffer& file, std::byte* dstBuffer, std::size_t dstBufferSize, std::byte* workingMemory, std::size_t workingMemorySize);
}