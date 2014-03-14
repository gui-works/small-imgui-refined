//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
// Copyright (c) 2011-2014 Mario 'rlyeh' Rodriguez
// Copyright (c) 2013 Florian Deconinck
// Copyright (c) 2013 Adrien Herubel
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

// Source altered and distributed from https://github.com/r-lyeh/imgui

#ifndef IMGUI_HPP
#define IMGUI_HPP

#include <string>
#include <vector>

enum imguiIntersection
{
        IMGUI_SECTION_INSIDE = -1,
        IMGUI_SECTION_BORDER = 0,
        IMGUI_SECTION_OUTSIDE = 1
};

enum imguiMouseButton
{
        IMGUI_MBUT_LEFT = 0x01,
        IMGUI_MBUT_RIGHT = 0x02,
};

enum imguiTextAlign // same than fontstash
{
        // Horizontal align
        IMGUI_ALIGN_LEFT         = 1<<0, // Default
        IMGUI_ALIGN_CENTER       = 1<<1,
        IMGUI_ALIGN_RIGHT        = 1<<2,
        // Vertical align
        IMGUI_ALIGN_TOP          = 1<<3,
        IMGUI_ALIGN_MIDDLE       = 1<<4,
        IMGUI_ALIGN_BOTTOM       = 1<<5,
        IMGUI_ALIGN_BASELINE     = 1<<6  // Default
};

void imguiBeginFrame(int mx, int my, unsigned char mbut, int scroll, unsigned unicode=0);
void imguiEndFrame();

// masking

bool imguiBeginScrollArea(const char* name, int x, int y, int w, int h, int* scroll=0);
void imguiEndScrollArea();

// layout

void imguiIndent();
void imguiUnindent();
void imguiSeparator();
void imguiSeparatorLine();

void imguiStackPush();
 int imguiStackSet( int stackpos );
void imguiSpaceDiv();
void imguiSpaceMul();
void imguiSpaceShift();
void imguiSpaceUnshift();

//void imguiTab();
//void imguiTabLine();
//void imguiFeed();

// widgets

bool imguiButton(const char* text);
bool imguiCheck(const char* text, bool checked);
bool imguiCollapse(const char* text, const char* subtext, bool checked);
bool imguiItem(const char* text);
bool imguiText(const char* text);
bool imguiTextInput(const char* text, std::vector<unsigned> &utf32);
void imguiLabel(const char* text);
void imguiValue(const char* text);
bool imguiSlider(const char* text, float* val, float vmin, float vmax, float vinc, const char *format = "%d");
bool imguiRange(const char* text, float* val0, float* val1, float vmin, float vmax, float vinc, const char *format = "%d - %d");
bool imguiList(const char* text, size_t n_options, const char** options, int &choosing, int &choice, int *scrollY = 0);
bool imguiRadio(const char* text, size_t n_options, const char** options, int &clicked);
void imguiPair(const char *text, const char *value);
void imguiProgressBar(const char* text, float val, bool show_decimals = false);
bool imguiBitmask(const char* text, unsigned* mask, int bits);
bool imguiRotatorySlider(const char *text, float *val, float vmin, float vmax, float vinc, const char *format = "%d");
bool imguiQuadRange(const char* text, float *val0, float *val1, float vmin, float vmax, float vinc, float *valLO, float *valHI, const char *format = "%d - %d");
bool imguiXYSlider(const char* text, float* valx, float * valy, float height, float vinc, const char *format = "(%d,%d)");

//bool imguiLink();
//      bool imguiImage();
//bool imguiUnlink();

// rendering
void imguiDrawText(int x, int y, imguiTextAlign align, const char* text, unsigned int color);
void imguiDrawLine(float x0, float y0, float x1, float y1, float r, unsigned int color);
void imguiDrawLines( const std::vector<float> &points2d, float r, unsigned int color);
void imguiDrawRoundedRect(float x, float y, float w, float h, float r, unsigned int color);
void imguiDrawRect(float x, float y, float w, float h, unsigned int color);
void imguiDrawArc(float x, float y, float radius, float from, float to, unsigned int color);
void imguiDrawCircle(float x, float y, float radius, unsigned int color);

// text
int imguiTextLength(const char *text);
// utf32 to utf8
std::string imguiTextConv(const std::vector<unsigned>& utf32 );
// ascii to utf32
std::vector<unsigned> imguiTextConv(const std::string& ascii );

// color
unsigned int imguiHSLA(float h, float s, float l, unsigned char a=255);
unsigned int imguiRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);
void imguiPushColor( unsigned int col );
void imguiPopColor();
void imguiPushColorTheme();

//
int imguiShowDialog( const char *text, int *answer );

// enable
void imguiPushEnable( int enabled = 1 );
void imguiPopEnable();

// mouse
enum {
        IMGUI_MOUSE_ARROW = 1,
        IMGUI_MOUSE_HAND = 2
};
int imguiGetMouseCursor();

// tweens
void imguiTween( int mode );

// Pull render interface.
enum imguiGfxCmdType
{
        IMGUI_GFXCMD_RECT,
        IMGUI_GFXCMD_TRIANGLE,
        IMGUI_GFXCMD_LINE,
        IMGUI_GFXCMD_TEXT,
        IMGUI_GFXCMD_SCISSOR,
        IMGUI_GFXCMD_ARC
};

struct imguiGfxRect
{
        short x,y,w,h,r;
};

struct imguiGfxText
{
        short x,y,align;
        const char* text;
};

struct imguiGfxLine
{
        short x0,y0,x1,y1,r;
};

struct imguiGfxArc
{
        short x,y;
        float r,t0,t1,w;
};

struct imguiGfxCmd
{
        char type;
        char flags;
        char pad[2];
        unsigned int col;
        union
        {
                imguiGfxLine line;
                imguiGfxRect rect;
                imguiGfxText text;
                imguiGfxArc  arc;
        };
};

const imguiGfxCmd* imguiGetRenderQueue();
int imguiGetRenderQueueSize();

#endif // IMGUI_HPP
