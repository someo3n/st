/* See LICENSE file for copyright and license details. */

/*
 * appearance
 *
 * font: see http://freedesktop.org/software/fontconfig/fontconfig-user.html
 */
static char *font = "mono:pixelsize=14:antialias=true:autohint=true";
/* Spare fonts */
static char *font2[] = {
	"Noto Color Emoji:pixelsize=14:antialias=true:autohint=true"
/*	"Inconsolata for Powerline:pixelsize=12:antialias=true:autohint=true", */
/*	"Hack Nerd Font Mono:pixelsize=11:antialias=true:autohint=true", */
};

static int borderpx = 2;

/*
 * What program is execed by st depends of these precedence rules:
 * 1: program passed with -e
 * 2: scroll and/or utmp
 * 3: SHELL environment variable
 * 4: value of shell in /etc/passwd
 * 5: value of shell in config.h
 */
static char *shell = "/bin/sh";
char *utmp = NULL;
/* scroll program: to enable use a string like "scroll" */
char *scroll = NULL;
char *stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400";

/* identification sequence returned in DA and DECID */
char *vtiden = "\033[?62;4c"; /* VT200 family (62) with sixel (4) */

/* sixel rgb byte order: LSBFirst or MSBFirst */
int const sixelbyteorder = LSBFirst;

/* Kerning / character bounding-box multipliers */
static float cwscale = 1.0;
static float chscale = 1.0;

/*
 * word delimiter string
 *
 * More advanced example: L" `'\"()[]{}"
 */
wchar_t *worddelimiters = L" ";

/* selection timeouts (in milliseconds) */
static unsigned int doubleclicktimeout = 300;
static unsigned int tripleclicktimeout = 600;

/* alt screens */
int allowaltscreen = 1;

/* allow certain non-interactive (insecure) window operations such as:
   setting the clipboard text */
int allowwindowops = 0;

/*
 * draw latency range in ms - from new content/keypress/etc until drawing.
 * within this range, st draws when content stops arriving (idle). mostly it's
 * near minlatency, but it waits longer for slow updates to avoid partial draw.
 * low minlatency will tear/flicker more, as it can "detect" idle too early.
 */
static double minlatency = 2;
static double maxlatency = 33;

/*
 * Synchronized-Update timeout in ms
 * https://gitlab.com/gnachman/iterm2/-/wikis/synchronized-updates-spec
 */
static uint su_timeout = 200;

/*
 * blinking timeout (set to 0 to disable blinking) for the terminal blinking
 * attribute.
 */
static unsigned int blinktimeout = 800;

/*
 * thickness of underline and bar cursors
 */
static unsigned int cursorthickness = 3;

/* Hide the X cursor whenever a key is pressed. 0: off, 1: on */
int hidecursor = 1;

/*
 * 1: render most of the lines/blocks characters without using the font for
 *    perfect alignment between cells (U2500 - U259F except dashes/diagonals).
 *    Bold affects lines thickness if boxdraw_bold is not 0. Italic is ignored.
 * 0: disable (render all U25XX glyphs normally from the font).
 */
const int boxdraw = 0;
const int boxdraw_bold = 0;

/* braille (U28XX):  1: render as adjacent "pixels",  0: use font */
const int boxdraw_braille = 0;

/*
 * bell volume. It must be a value between -100 and 100. Use 0 for disabling
 * it
 */
static int bellvolume = 0;

/* default TERM value */
char *termname = "st-256color";

/*
 * spaces per tab
 *
 * When you are changing this value, don't forget to adapt the »it« value in
 * the st.info and appropriately install the st.info in the environment where
 * you use this st version.
 *
 *	it#$tabspaces,
 *
 * Secondly make sure your kernel is not expanding tabs. When running `stty
 * -a` »tab0« should appear. You can tell the terminal to not expand tabs by
 *  running following command:
 *
 *	stty tabs
 */
unsigned int tabspaces = 8;

/*
 * drag and drop escape characters
 *
 * this will add a '\' before any characters specified in the string.
 */
char *xdndescchar = " !\"#$&'()*;<>?[\\]^`{|}~";

/* Tokyo Night ST theme - based on kitty config by Folke Lemaitre */
/* Terminal colors (16 first used in escape sequence) */
static const char *colorname[] = {
	/* 8 normal colors */
	"#15161e", /* black   */
	"#f7768e", /* red     */
	"#9ece6a", /* green   */
	"#e0af68", /* yellow  */
	"#7aa2f7", /* blue    */
	"#bb9af7", /* magenta */
	"#7dcfff", /* cyan    */
	"#a9b1d6", /* white   */

	/* 8 bright colors */
	"#414868", /* bright black   */
	"#f7768e", /* bright red     */
	"#9ece6a", /* bright green   */
	"#e0af68", /* bright yellow  */
	"#7aa2f7", /* bright blue    */
	"#bb9af7", /* bright magenta */
	"#7dcfff", /* bright cyan    */
	"#c0caf5", /* bright white   */

	[255] = 0,

	/* more colors can be added after 255 to use with DefaultXX */
	"#c0caf5", /* 256: foreground */
	"#1a1b26", /* 257: background */
	"#7aa2f7", /* 258: cursor color */
	"#1a1b26", /* 259: cursor text (reverse cursor fg) */
};

unsigned int defaultbg = 257;
unsigned int defaultfg = 256;
unsigned int defaultcs = 258;
unsigned int defaultrcs = 259;

/*
 * Default shape of cursor
 * 2: Block ("█")
 * 4: Underline ("_")
 * 6: Bar ("|")
 * 7: Snowman ("☃")
 */
static unsigned int cursorshape = 2;

/*
 * Default columns and rows numbers
 */

static unsigned int cols = 80;
static unsigned int rows = 24;

/*
 * Whether to use pixel geometry or cell geometry
 */

static Geometry geometry = CellGeometry; // or PixelGeometry to use the below size
static unsigned int width = 564;
static unsigned int height = 364;

/*
 * Default shape of the mouse cursor
 */
static char* mouseshape = "xterm";

/*
 * Color used to display font attributes when fontconfig selected a font which
 * doesn't match the ones requested.
 */
static unsigned int defaultattr = 11;

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",         STRING,  &font },
		{ "color0",       STRING,  &colorname[0] },
		{ "color1",       STRING,  &colorname[1] },
		{ "color2",       STRING,  &colorname[2] },
		{ "color3",       STRING,  &colorname[3] },
		{ "color4",       STRING,  &colorname[4] },
		{ "color5",       STRING,  &colorname[5] },
		{ "color6",       STRING,  &colorname[6] },
		{ "color7",       STRING,  &colorname[7] },
		{ "color8",       STRING,  &colorname[8] },
		{ "color9",       STRING,  &colorname[9] },
		{ "color10",      STRING,  &colorname[10] },
		{ "color11",      STRING,  &colorname[11] },
		{ "color12",      STRING,  &colorname[12] },
		{ "color13",      STRING,  &colorname[13] },
		{ "color14",      STRING,  &colorname[14] },
		{ "color15",      STRING,  &colorname[15] },
		{ "background",   STRING,  &colorname[258] },
		{ "foreground",   STRING,  &colorname[259] },
		{ "cursorColor",  STRING,  &colorname[256] },
		{ "termname",     STRING,  &termname },
		{ "shell",        STRING,  &shell },
		{ "minlatency",   INTEGER, &minlatency },
		{ "maxlatency",   INTEGER, &maxlatency },
		{ "blinktimeout", INTEGER, &blinktimeout },
		{ "bellvolume",   INTEGER, &bellvolume },
		{ "tabspaces",    INTEGER, &tabspaces },
		{ "borderpx",     INTEGER, &borderpx },
		{ "cwscale",      FLOAT,   &cwscale },
		{ "chscale",      FLOAT,   &chscale },
};

/*
 * Force mouse select/shortcuts while mask is active (when MODE_MOUSE is set).
 * Note that if you want to use ShiftMask with selmasks, set this to an other
 * modifier, set to 0 to not use it.
 */
static uint forcemousemod = ShiftMask;

/*
 * Internal mouse shortcuts.
 * Beware that overloading Button1 will disable the selection.
 */
static MouseShortcut mshortcuts[] = {
	/* mask                 button   function        argument       release  screen */
	{ XK_ANY_MOD,           Button2, clippaste,      {.i = 0},      1 },
	{ ShiftMask,            Button4, kscrollup,      {.i = 4},      0, S_PRI},
	{ ShiftMask,            Button5, kscrolldown,    {.i = 4},      0, S_PRI},
	{ XK_ANY_MOD,           Button4, ttysend,        {.s = "\031"} },
	{ XK_ANY_MOD,           Button5, ttysend,        {.s = "\005"} },
};

/* Internal keyboard shortcuts. */
#define MODKEY Mod1Mask
#define TERMMOD (ControlMask|ShiftMask)

static char *openurlcmd[] = { "/bin/sh", "-c",
	"xurls | dmenu -l 10 -w $WINDOWID | xargs -r open",
	"externalpipe", NULL };

static char *setbgcolorcmd[] = { "/bin/sh", "-c",
	"printf '\033]11;#008000\007'",
	"externalpipein", NULL };

static Shortcut shortcuts[] = {
	/* mask                 keysym          function         argument   screen */
	{ XK_ANY_MOD,           XK_Break,       sendbreak,       {.i =  0} },
	{ ControlMask,          XK_Print,       toggleprinter,   {.i =  0} },
	{ ShiftMask,            XK_Print,       printscreen,     {.i =  0} },
	{ XK_ANY_MOD,           XK_Print,       printsel,        {.i =  0} },
	{ TERMMOD,              XK_plus,        zoom,            {.f = +2} },
	{ TERMMOD,              XK_underscore,  zoom,            {.f = -2} },
	{ TERMMOD,              XK_Home,        zoomreset,       {.f =  0} },
	{ TERMMOD,              XK_C,           clipcopy,        {.i =  0} },
	{ TERMMOD,              XK_V,           clippaste,       {.i =  0} },
	{ ShiftMask,            XK_Page_Up,     kscrollup,       {.i = -1}, S_PRI },
	{ ShiftMask,            XK_Page_Down,   kscrolldown,     {.i = -1}, S_PRI },
	{ TERMMOD,              XK_Y,           clippaste,       {.i =  0} },
	{ ShiftMask,            XK_Insert,      clippaste,       {.i =  0} },
	{ TERMMOD,              XK_Num_Lock,    numlock,         {.i =  0} },
	{ TERMMOD,              XK_Return,      newterm,         {.i =  0} },
};

/*
 * Special keys (change & recompile st.info accordingly)
 *
 * Mask value:
 * * Use XK_ANY_MOD to match the key no matter modifiers state
 * * Use XK_NO_MOD to match the key alone (no modifiers)
 * appkey value:
 * * 0: no value
 * * > 0: keypad application mode enabled
 * *   = 2: term.numlock = 1
 * * < 0: keypad application mode disabled
 * appcursor value:
 * * 0: no value
 * * > 0: cursor application mode enabled
 * * < 0: cursor application mode disabled
 *
 * Be careful with the order of the definitions because st searches in
 * this table sequentially, so any XK_ANY_MOD must be in the last
 * position for a key.
 */

/*
 * State bits to ignore when matching key or button events.  By default,
 * numlock (Mod2Mask) and keyboard layout (XK_SWITCH_MOD) are ignored.
 */
static uint ignoremod = Mod2Mask|XK_SWITCH_MOD;

/*
 * Selection types' masks.
 * Use the same masks as usual.
 * Button1Mask is always unset, to make masks match between ButtonPress.
 * ButtonRelease and MotionNotify.
 * If no match is found, regular selection is used.
 */
static uint selmasks[] = {
	[SEL_RECTANGULAR] = Mod1Mask,
};

/*
 * Printable characters in ASCII, used to estimate the advance width
 * of single wide characters.
 */
static char ascii_printable[] =
	" !\"#$%&'()*+,-./0123456789:;<=>?"
	"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
	"`abcdefghijklmnopqrstuvwxyz{|}~";

/**
 * Undercurl style. Set UNDERCURL_STYLE to one of the available styles.
 *
 * Curly: Dunno how to draw it *shrug*
 *  _   _   _   _
 * ( ) ( ) ( ) ( )
 *	 (_) (_) (_) (_)
 *
 * Spiky:
 * /\  /\   /\	/\
 *   \/  \/	  \/
 *
 * Capped:
 *	_     _     _
 * / \   / \   / \
 *    \_/   \_/
 */
// Available styles
#define UNDERCURL_CURLY 0
#define UNDERCURL_SPIKY 1
#define UNDERCURL_CAPPED 2
// Active style
#define UNDERCURL_STYLE UNDERCURL_SPIKY
