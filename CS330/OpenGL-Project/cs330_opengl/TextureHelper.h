#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace TextureHelper
{

	/**
	 * Creates an OpenGL texture from an image file.
	 *
	 * @param[in] filename The name of the image file to load.
	 * @param[out] textureId The ID of the texture created.
	 * @return True if the texture was created successfully, false otherwise.
	 */
	inline bool CreateGlTextureFromFile(const char* filename, GLuint& textureId)
	{
		int imgWidth;
		int imgHeight;
		int imgNumChannels;

		// Set flip on load instead of hard coding an array reversal like the module tutorial
		stbi_set_flip_vertically_on_load(true);
		unsigned char* imgPxArray = stbi_load(filename, &imgWidth, &imgHeight, &imgNumChannels, 0);

		if (imgPxArray)
		{
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			if (imgNumChannels == 3)
				glTexImage2D(GL_TEXTURE_2D,
					0, GL_RGB8, 
					imgWidth, imgHeight, 0,
					GL_RGB, GL_UNSIGNED_BYTE, imgPxArray);
			else if (imgNumChannels == 4)
				glTexImage2D(GL_TEXTURE_2D, 
					0, GL_RGBA8,
					imgWidth, imgHeight, 0,
					GL_RGBA, GL_UNSIGNED_BYTE, imgPxArray);
			else
			{
				std::cout << "Unsupported number of channels." << std::endl;
				return false;
			}

			// generate mipmap for LODs
			glGenerateMipmap(GL_TEXTURE_2D);


			// free resources
			stbi_image_free(imgPxArray);
			glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

			return true;
		}
		return false;
	}


	/**
	 * Creates an OpenGL texture from an image file.
	 *
	 * @param[in] filename The name of the image file to load.
	 * @return The ID of the texture created. Zero is returned if the texture could not be created.
	 */
	inline GLuint CreateTexture(const char* filename)
	{
		GLuint texId;
		if (CreateGlTextureFromFile(filename, texId))
		{
			return texId;
		}
		return 0;
	}
}