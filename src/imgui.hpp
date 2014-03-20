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
        IMGUI_MOUSE_BUTTON_LEFT = 0x01,
        IMGUI_MOUSE_BUTTON_RIGHT = 0x02,
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

// imguiPushLayout(Vert/Horiz);
// imguiPopLayout();

//void imguiTab();
//void imguiTabLine();
//void imguiFeed();

// widgets

bool imguiButton(const char* text);
bool imguiCheck(const char* text, bool checked);
bool imguiCollapse(const char* text, const char* subtext, bool checked);
bool imguiItem(const char* text);
bool imguiText(const char* text);
bool imguiTextInput(const char* text, std::vector<unsigned> &utf32, bool isPassword = false);
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
bool imguiLoadingBar( int flow = 0, float radius = 25.f );
bool imguiIcon( unsigned icon );
 int imguiToolbar( const std::vector<unsigned> &icons );

// control
bool imguiWheel( unsigned id );
bool imguiClicked( unsigned id );
bool imguiClicked2( unsigned id );
bool imguiTrigger( unsigned id );
bool imguiHold( unsigned id );
bool imguiRelease( unsigned id );
bool imguiIdle( unsigned id );
bool imguiDrag( unsigned id );
bool imguiDrop( unsigned id );
bool imguiOver( unsigned id );
bool imguiHot( unsigned id );
bool imguiActive( unsigned id );
unsigned imguiId();

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
std::string imguiTextConv( const unsigned &utf32 );
std::string imguiTextConv( const std::vector<unsigned>& utf32 );
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

// feed
void imguiBack(); // \r
void imguiNext(); // \n

// mouse
enum {
        IMGUI_MOUSE_ICON_ARROW = 1,
        IMGUI_MOUSE_ICON_HAND = 2
};
int imguiGetMouseCursor();

// tweens
void imguiTween( unsigned mode );

// built-in icons (http://www.entypo.com)

enum {
        IMGUI_ICON_PHONE = 0x1F4DE,
        IMGUI_ICON_MOBILE = 0x1F4F1,
        IMGUI_ICON_MOUSE = 0xE789,
        IMGUI_ICON_ADDRESS = 0xE723,
        IMGUI_ICON_MAIL = 0x2709,
        IMGUI_ICON_PAPER_PLANE = 0x1F53F,
        IMGUI_ICON_PENCIL = 0x270E,
        IMGUI_ICON_FEATHER = 0x2712,
        IMGUI_ICON_ATTACH = 0x1F4CE,
        IMGUI_ICON_INBOX = 0xE777,
        IMGUI_ICON_REPLY = 0xE712,
        IMGUI_ICON_REPLY_ALL = 0xE713,
        IMGUI_ICON_FORWARD = 0x27A6,
        IMGUI_ICON_USER = 0x1F464,
        IMGUI_ICON_USERS = 0x1F465,
        IMGUI_ICON_ADD_USER = 0xE700,
        IMGUI_ICON_VCARD = 0xE722,
        IMGUI_ICON_EXPORT = 0xE715,
        IMGUI_ICON_LOCATION = 0xE724,
        IMGUI_ICON_MAP = 0xE727,
        IMGUI_ICON_COMPASS = 0xE728,
        IMGUI_ICON_DIRECTION = 0x27A2,
        IMGUI_ICON_HAIR_CROSS = 0x1F3AF,
        IMGUI_ICON_SHARE = 0xE73C,
        IMGUI_ICON_SHAREABLE = 0xE73E,
        IMGUI_ICON_HEART = 0x2665,
        IMGUI_ICON_HEART_EMPTY = 0x2661,
        IMGUI_ICON_STAR = 0x2605,
        IMGUI_ICON_STAR_EMPTY = 0x2606,
        IMGUI_ICON_THUMBS_UP = 0x1F44D,
        IMGUI_ICON_THUMBS_DOWN = 0x1F44E,
        IMGUI_ICON_CHAT = 0xE720,
        IMGUI_ICON_COMMENT = 0xE718,
        IMGUI_ICON_QUOTE = 0x275E,
        IMGUI_ICON_HOME = 0x2302,
        IMGUI_ICON_POPUP = 0xE74C,
        IMGUI_ICON_SEARCH = 0x1F50D,
        IMGUI_ICON_FLASHLIGHT = 0x1F526,
        IMGUI_ICON_PRINT = 0xE716,
        IMGUI_ICON_BELL = 0x1F514,
        IMGUI_ICON_LINK = 0x1F517,
        IMGUI_ICON_FLAG = 0x2691,
        IMGUI_ICON_COG = 0x2699,
        IMGUI_ICON_TOOLS = 0x2692,
        IMGUI_ICON_TROPHY = 0x1F3C6,
        IMGUI_ICON_TAG = 0xE70C,
        IMGUI_ICON_CAMERA = 0x1F4F7,
        IMGUI_ICON_MEGAPHONE = 0x1F4E3,
        IMGUI_ICON_MOON = 0x263D,
        IMGUI_ICON_PALETTE = 0x1F3A8,
        IMGUI_ICON_LEAF = 0x1F342,
        IMGUI_ICON_NOTE = 0x266A,
        IMGUI_ICON_BEAMED_NOTE = 0x266B,
        IMGUI_ICON_NEW = 0x1F4A5,
        IMGUI_ICON_GRADUATION_CAP = 0x1F393,
        IMGUI_ICON_BOOK = 0x1F4D5,
        IMGUI_ICON_NEWSPAPER = 0x1F4F0,
        IMGUI_ICON_BAG = 0x1F45C,
        IMGUI_ICON_AIRPLANE = 0x2708,
        IMGUI_ICON_LIFEBUOY = 0xE788,
        IMGUI_ICON_EYE = 0xE70A,
        IMGUI_ICON_CLOCK = 0x1F554,
        IMGUI_ICON_MIC = 0x1F3A4,
        IMGUI_ICON_CALENDAR = 0x1F4C5,
        IMGUI_ICON_FLASH = 0x26A1,
        IMGUI_ICON_THUNDER_CLOUD = 0x26C8,
        IMGUI_ICON_DROPLET = 0x1F4A7,
        IMGUI_ICON_CD = 0x1F4BF,
        IMGUI_ICON_BRIEFCASE = 0x1F4BC,
        IMGUI_ICON_AIR = 0x1F4A8,
        IMGUI_ICON_HOURGLASS = 0x23F3,
        IMGUI_ICON_GAUGE = 0x1F6C7,
        IMGUI_ICON_LANGUAGE = 0x1F394,
        IMGUI_ICON_NETWORK = 0xE776,
        IMGUI_ICON_KEY = 0x1F511,
        IMGUI_ICON_BATTERY = 0x1F50B,
        IMGUI_ICON_BUCKET = 0x1F4FE,
        IMGUI_ICON_MAGNET = 0xE7A1,
        IMGUI_ICON_DRIVE = 0x1F4FD,
        IMGUI_ICON_CUP = 0x2615,
        IMGUI_ICON_ROCKET = 0x1F680,
        IMGUI_ICON_BRUSH = 0xE79A,
        IMGUI_ICON_SUITCASE = 0x1F6C6,
        IMGUI_ICON_TRAFFIC_CONE = 0x1F6C8,
        IMGUI_ICON_GLOBE = 0x1F30E,
        IMGUI_ICON_KEYBOARD = 0x2328,
        IMGUI_ICON_BROWSER = 0xE74E,
        IMGUI_ICON_PUBLISH = 0xE74D,
        IMGUI_ICON_PROGRESS_3 = 0xE76B,
        IMGUI_ICON_PROGRESS_2 = 0xE76A,
        IMGUI_ICON_PROGRESS_1 = 0xE769,
        IMGUI_ICON_PROGRESS_0 = 0xE768,
        IMGUI_ICON_LIGHT_DOWN = 0x1F505,
        IMGUI_ICON_LIGHT_UP = 0x1F506,
        IMGUI_ICON_ADJUST = 0x25D1,
        IMGUI_ICON_CODE = 0xE714,
        IMGUI_ICON_MONITOR = 0x1F4BB,
        IMGUI_ICON_INFINITY = 0x221E,
        IMGUI_ICON_LIGHT_BULB = 0x1F4A1,
        IMGUI_ICON_CREDIT_CARD = 0x1F4B3,
        IMGUI_ICON_DATABASE = 0x1F4F8,
        IMGUI_ICON_VOICEMAIL = 0x2707,
        IMGUI_ICON_CLIPBOARD = 0x1F4CB,
        IMGUI_ICON_CART = 0xE73D,
        IMGUI_ICON_BOX = 0x1F4E6,
        IMGUI_ICON_TICKET = 0x1F3AB,
        IMGUI_ICON_RSS = 0xE73A,
        IMGUI_ICON_SIGNAL = 0x1F4F6,
        IMGUI_ICON_THERMOMETER = 0x1F4FF,
        IMGUI_ICON_WATER = 0x1F4A6,
        IMGUI_ICON_SWEDEN = 0xF601,
        IMGUI_ICON_LINE_GRAPH = 0x1F4C8,
        IMGUI_ICON_PIE_CHART = 0x25F4,
        IMGUI_ICON_BAR_GRAPH = 0x1F4CA,
        IMGUI_ICON_AREA_GRAPH = 0x1F53E,
        IMGUI_ICON_LOCK = 0x1F512,
        IMGUI_ICON_LOCK_OPEN = 0x1F513,
        IMGUI_ICON_LOGOUT = 0xE741,
        IMGUI_ICON_LOGIN = 0xE740,
        IMGUI_ICON_CHECK = 0x2713,
        IMGUI_ICON_CROSS = 0x274C,
        IMGUI_ICON_SQUARED_MINUS = 0x229F,
        IMGUI_ICON_SQUARED_PLUS = 0x229E,
        IMGUI_ICON_SQUARED_CROSS = 0x274E,
        IMGUI_ICON_CIRCLED_MINUS = 0x2296,
        IMGUI_ICON_CIRCLED_PLUS = 0x2295,
        IMGUI_ICON_CIRCLED_CROSS = 0x2716,
        IMGUI_ICON_MINUS = 0x2796,
        IMGUI_ICON_PLUS = 0x2795,
        IMGUI_ICON_ERASE = 0x232B,
        IMGUI_ICON_BLOCK = 0x1F6AB,
        IMGUI_ICON_INFO = 0x2139,
        IMGUI_ICON_CIRCLED_INFO = 0xE705,
        IMGUI_ICON_HELP = 0x2753,
        IMGUI_ICON_CIRCLED_HELP = 0xE704,
        IMGUI_ICON_WARNING = 0x26A0,
        IMGUI_ICON_CYCLE = 0x1F504,
        IMGUI_ICON_CW = 0x27F3,
        IMGUI_ICON_CCW = 0x27F2,
        IMGUI_ICON_SHUFFLE = 0x1F500,
        IMGUI_ICON_BACK = 0x1F519,
        IMGUI_ICON_LEVEL_DOWN = 0x21B3,
        IMGUI_ICON_RETWEET = 0xE717,
        IMGUI_ICON_LOOP = 0x1F501,
        IMGUI_ICON_BACK_IN_TIME = 0xE771,
        IMGUI_ICON_LEVEL_UP = 0x21B0,
        IMGUI_ICON_SWITCH = 0x21C6,
        IMGUI_ICON_NUMBERED_LIST = 0xE005,
        IMGUI_ICON_ADD_TO_LIST = 0xE003,
        IMGUI_ICON_LAYOUT = 0x268F,
        IMGUI_ICON_LIST = 0x2630,
        IMGUI_ICON_TEXT_DOC = 0x1F4C4,
        IMGUI_ICON_TEXT_DOC_INVERTED = 0xE731,
        IMGUI_ICON_DOC = 0xE730,
        IMGUI_ICON_DOCS = 0xE736,
        IMGUI_ICON_LANDSCAPE_DOC = 0xE737,
        IMGUI_ICON_PICTURE = 0x1F304,
        IMGUI_ICON_VIDEO = 0x1F3AC,
        IMGUI_ICON_MUSIC = 0x1F3B5,
        IMGUI_ICON_FOLDER = 0x1F4C1,
        IMGUI_ICON_ARCHIVE = 0xE800,
        IMGUI_ICON_TRASH = 0xE729,
        IMGUI_ICON_UPLOAD = 0x1F4E4,
        IMGUI_ICON_DOWNLOAD = 0x1F4E5,
        IMGUI_ICON_SAVE = 0x1F4BE,
        IMGUI_ICON_INSTALL = 0xE778,
        IMGUI_ICON_CLOUD = 0x2601,
        IMGUI_ICON_UPLOAD_CLOUD = 0xE711,
        IMGUI_ICON_BOOKMARK = 0x1F516,
        IMGUI_ICON_BOOKMARKS = 0x1F4D1,
        IMGUI_ICON_OPEN_BOOK = 0x1F4D6,
        IMGUI_ICON_PLAY = 0x25B6,
        IMGUI_ICON_PAUSE = 0x2016,
        IMGUI_ICON_RECORD = 0x25CF,
        IMGUI_ICON_STOP = 0x25A0,
        IMGUI_ICON_FF = 0x23E9,
        IMGUI_ICON_FB = 0x23EA,
        IMGUI_ICON_TO_START = 0x23EE,
        IMGUI_ICON_TO_END = 0x23ED,
        IMGUI_ICON_RESIZE_FULL = 0xE744,
        IMGUI_ICON_RESIZE_SMALL = 0xE746,
        IMGUI_ICON_VOLUME = 0x23F7,
        IMGUI_ICON_SOUND = 0x1F50A,
        IMGUI_ICON_MUTE = 0x1F507,
        IMGUI_ICON_FLOW_CASCADE = 0x1F568,
        IMGUI_ICON_FLOW_BRANCH = 0x1F569,
        IMGUI_ICON_FLOW_TREE = 0x1F56A,
        IMGUI_ICON_FLOW_LINE = 0x1F56B,
        IMGUI_ICON_FLOW_PARALLEL = 0x1F56C,
        IMGUI_ICON_LEFT_BOLD = 0xE4AD,
        IMGUI_ICON_DOWN_BOLD = 0xE4B0,
        IMGUI_ICON_UP_BOLD = 0xE4AF,
        IMGUI_ICON_RIGHT_BOLD = 0xE4AE,
        IMGUI_ICON_LEFT = 0x2B05,
        IMGUI_ICON_DOWN = 0x2B07,
        IMGUI_ICON_UP = 0x2B06,
        IMGUI_ICON_RIGHT = 0x27A1,
        IMGUI_ICON_CIRCLED_LEFT = 0xE759,
        IMGUI_ICON_CIRCLED_DOWN = 0xE758,
        IMGUI_ICON_CIRCLED_UP = 0xE75B,
        IMGUI_ICON_CIRCLED_RIGHT = 0xE75A,
        IMGUI_ICON_TRIANGLE_LEFT = 0x25C2,
        IMGUI_ICON_TRIANGLE_DOWN = 0x25BE,
        IMGUI_ICON_TRIANGLE_UP = 0x25B4,
        IMGUI_ICON_TRIANGLE_RIGHT = 0x25B8,
        IMGUI_ICON_CHEVRON_LEFT = 0xE75D,
        IMGUI_ICON_CHEVRON_DOWN = 0xE75C,
        IMGUI_ICON_CHEVRON_UP = 0xE75F,
        IMGUI_ICON_CHEVRON_RIGHT = 0xE75E,
        IMGUI_ICON_CHEVRON_SMALL_LEFT = 0xE761,
        IMGUI_ICON_CHEVRON_SMALL_DOWN = 0xE760,
        IMGUI_ICON_CHEVRON_SMALL_UP = 0xE763,
        IMGUI_ICON_CHEVRON_SMALL_RIGHT = 0xE762,
        IMGUI_ICON_CHEVRON_THIN_LEFT = 0xE765,
        IMGUI_ICON_CHEVRON_THIN_DOWN = 0xE764,
        IMGUI_ICON_CHEVRON_THIN_UP = 0xE767,
        IMGUI_ICON_CHEVRON_THIN_RIGHT = 0xE766,
        IMGUI_ICON_LEFT_THIN = 0x2190,
        IMGUI_ICON_DOWN_THIN = 0x2193,
        IMGUI_ICON_UP_THIN = 0x2191,
        IMGUI_ICON_RIGHT_THIN = 0x2192,
        IMGUI_ICON_ARROW_COMBO = 0xE74F,
        IMGUI_ICON_THREE_DOTS = 0x23F6,
        IMGUI_ICON_TWO_DOTS = 0x23F5,
        IMGUI_ICON_DOT = 0x23F4,
        IMGUI_ICON_CC = 0x1F545,
        IMGUI_ICON_CC_BY = 0x1F546,
        IMGUI_ICON_CC_NC = 0x1F547,
        IMGUI_ICON_CC_NC_EU = 0x1F548,
        IMGUI_ICON_CC_NC_JP = 0x1F549,
        IMGUI_ICON_CC_SA = 0x1F54A,
        IMGUI_ICON_CC_ND = 0x1F54B,
        IMGUI_ICON_CC_PD = 0x1F54C,
        IMGUI_ICON_CC_ZERO = 0x1F54D,
        IMGUI_ICON_CC_SHARE = 0x1F54E,
        IMGUI_ICON_CC_REMIX = 0x1F54F,
        IMGUI_ICON_DB_LOGO = 0x1F5F9,
        IMGUI_ICON_DB_SHAPE = 0x1F5FA
};

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

imguiGfxRect imguiRect( unsigned id );

const imguiGfxCmd* imguiGetRenderQueue();
int imguiGetRenderQueueSize();

#endif // IMGUI_HPP
