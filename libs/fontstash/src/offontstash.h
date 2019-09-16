//
// Copyright (c) 2009-2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
#ifndef GLFONTSTASH_H
#define GLFONTSTASH_H

FONScontext* glfonsCreate(int width, int height, int flags);
void glfonsDelete(FONScontext* ctx);

unsigned int glfonsRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

#endif

#ifdef GLFONTSTASH_IMPLEMENTATION

#include "ofMain.h"

struct GLFONScontext {
	ofImage* tex;
	ofVbo* vbo;
	int width, height;
};
typedef struct GLFONScontext GLFONScontext;

static int glfons__renderCreate(void* userPtr, int width, int height)
{
	GLFONScontext* gl = (GLFONScontext*)userPtr;
	// Create may be called multiple times, delete existing texture.
	if (gl->tex != 0) {
		delete gl->tex;
		gl->tex = 0;
	}

	if (gl->vbo == 0) {
		gl->vbo = new ofVbo();
	}

	gl->width = width;
	gl->height = height;

	gl->tex = new ofImage();
	gl->tex->allocate(width, height, OF_IMAGE_COLOR_ALPHA);
	return 1;
}

static int glfons__renderResize(void* userPtr, int width, int height)
{
	// Reuse create to resize too.
	return glfons__renderCreate(userPtr, width, height);
}

static void glfons__renderUpdate(void* userPtr, int* rect, const unsigned char* data)
{
	GLFONScontext* gl = (GLFONScontext*)userPtr;
	int w = rect[2] - rect[0];
	int h = rect[3] - rect[1];

	if (gl->tex == 0) return;

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			gl->tex->setColor(x + rect[0], y + rect[1], ofColor(255, data[(rect[1] + y) * gl->width + (rect[0] + x)]));
		}
	}

	gl->tex->update();
}


ofFloatColor rgbaToOf(unsigned int& col)
{
	ofFloatColor c;
	c.a = (col >> 24 & 0xff) / 255.0;
	c.b = (col >> 16 & 0xff) / 255.0;
	c.g = (col >> 8 & 0xff) / 255.0;
	c.r = (col >> 0 & 0xff) / 255.0;
	return c;
}

static void glfons__renderDraw(void* userPtr, const float* verts, const float* tcoords, const unsigned int* colors, int nverts)
{
	GLFONScontext* gl = (GLFONScontext*)userPtr;
	if (gl->tex == 0) return;

    /*
	// debug
	gl->tex->draw(0,0);
    return;
    */

	gl->tex->bind();

	gl->vbo->setVertexData((glm::vec2*)verts, nverts, GL_DYNAMIC_DRAW);
	gl->vbo->setTexCoordData(tcoords, nverts, GL_DYNAMIC_DRAW);
	/*
	vector<ofFloatColor> col;
	col.resize(nverts);
	for (int i = 0; i < nverts; i++)
	{
		col[i] = rgbaToOf(colors[i]);
	}
	gl->vbo->setColorData(col.data(), nverts, GL_DYNAMIC_DRAW);
	*/

	gl->vbo->draw(GL_TRIANGLES, 0, nverts);

	gl->tex->unbind();
}

static void glfons__renderDelete(void* userPtr)
{
	GLFONScontext* gl = (GLFONScontext*)userPtr;
	if (gl->tex != 0)
		delete gl->tex;
	gl->tex = 0;
	free(gl);

	if (gl->vbo != 0) {
		delete gl->vbo;
		gl->vbo = 0;
	}
}

FONScontext* glfonsCreate(int width, int height, int flags)
{
	FONSparams params;
	GLFONScontext* gl;

	gl = (GLFONScontext*)malloc(sizeof(GLFONScontext));
	if (gl == NULL) goto error;
	memset(gl, 0, sizeof(GLFONScontext));

	memset(&params, 0, sizeof(params));
	params.width = width;
	params.height = height;
	params.flags = (unsigned char)flags;
	params.renderCreate = glfons__renderCreate;
	params.renderResize = glfons__renderResize;
	params.renderUpdate = glfons__renderUpdate;
	params.renderDraw = glfons__renderDraw;
	params.renderDelete = glfons__renderDelete;
	params.userPtr = gl;

	return fonsCreateInternal(&params);

error:
	if (gl != NULL) free(gl);
	return NULL;
}

void glfonsDelete(FONScontext* ctx)
{
	fonsDeleteInternal(ctx);
}

unsigned int glfonsRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return (r) | (g << 8) | (b << 16) | (a << 24);
}

#endif
