/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "st-256color"
#define BROWSER "firefox"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static unsigned int gappih          = 20;       /* horiz inner gap between windows */
static unsigned int gappiv          = 10;       /* vert inner gap between windows */
static unsigned int gappoh          = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov          = 30;       /* vert outer gap between windows and screen edge */
static int swallowfloating          = 0;        /* 1 means swallow floating windows by default */
static int smartgaps                = 0;        /* 1 means no outer gap when there is only one window */
static const char *fonts[]          = { "IBM Plex Mono:size=16" };
static const char dmenufont[]       = "IBM Plex Mono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "80x24", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance    title           tags mask   isfloating  isterminal  noswallow  monitor */
	{ "Gimp",        NULL,       NULL,           0,          1,          0,          0,         -1 },
	{ "Firefox",     NULL,       NULL,           1 << 8,     0,          0,          0,         -1 },
	{ TERMCLASS,     NULL,       NULL,           0,          0,          1,          0,         -1 },
	{ NULL,          NULL,       "Event Tester", 0,          0,          0,          1,         -1 },
	{ TERMCLASS,     "spterm",   NULL,           SPTAG(0),   1,          1,          0,         -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[@]",      spiral },  /* first entry is default */
	{ "[\\]",     dwindle },

	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },

	{ "[]=",      tile },

	{ "[M]",      monocle },

	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *thunarcmd[] = { "thunar", NULL };
static const char *wallnextcmd[] = { "/bin/sh", "-c", "printf 'next\\n' > \"${XDG_RUNTIME_DIR:-/tmp}/wallpaper-slideshow-$UID.fifo\"", NULL };

#include <X11/XF86keysym.h>
#include "shift-tools.c"

static const Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY|ShiftMask,		XK_Return,     togglescratch,          {.ui = 0} },
	{ MODKEY,			XK_d,          spawn,                  {.v = dmenucmd } },
	{ MODKEY,			XK_Return,     spawn,                  {.v = termcmd } },
	{ MODKEY,			XK_e,          spawn,                  {.v = thunarcmd } },
	{ MODKEY,			XK_w,          spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },

	{ ShiftMask,			XK_plus,       spawn,                  {.v = wallnextcmd } },
	{ Mod1Mask,			XK_d,          toggledesktop,          {0} },

	{ MODKEY,			XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,			XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY,			XK_space,      rotatestack,            {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_space,      rotatestack,            {.i = -1 } },

	{ MODKEY,			XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,			XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY,			XK_o,          incnmaster,             {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,          incnmaster,             {.i = -1 } },

	{ MODKEY,			XK_q,          killclient,             {0} },
	{ MODKEY,			XK_z,          zoom,                   {0} },
	{ MODKEY|ShiftMask,		XK_c,          togglefloating,         {0} },
	{ MODKEY,			XK_b,          togglebar,              {0} },
	{ MODKEY,			XK_Tab,        view,                   {0} },

	{ MODKEY,			XK_y,          setlayout,              {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,		XK_y,          setlayout,              {.v = &layouts[1]} },
	{ MODKEY,			XK_i,          setlayout,              {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,		XK_i,          setlayout,              {.v = &layouts[3]} },
	{ MODKEY,			XK_t,          setlayout,              {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,		XK_u,          setlayout,              {.v = &layouts[5]} },
	{ MODKEY,			XK_f,          togglefullscr,          {0} },
	{ MODKEY|ShiftMask,		XK_f,          setlayout,              {.v = &layouts[6]} },
	{ MODKEY,			XK_c,          setlayout,              {0} },

	{ MODKEY,			XK_s,          togglesticky,           {0} },

	{ MODKEY,			XK_a,          togglegaps,             {0} },
	{ MODKEY|ShiftMask,		XK_a,          defaultgaps,            {0} },
	{ MODKEY|ShiftMask,		XK_z,          incrgaps,               {.i = +3 } },
	{ MODKEY|ShiftMask,		XK_x,          incrgaps,               {.i = -3 } },

	{ MODKEY,			XK_g,          shiftview,              {.i = -1 } },
	{ MODKEY|ShiftMask,		XK_g,          shifttag,               {.i = -1 } },
	{ MODKEY,			XK_semicolon,  shiftview,              {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_semicolon,  shifttag,               {.i = +1 } },

	TAGKEYS(			XK_1,          0)
	TAGKEYS(			XK_2,          1)
	TAGKEYS(			XK_3,          2)
	TAGKEYS(			XK_4,          3)
	TAGKEYS(			XK_5,          4)
	TAGKEYS(			XK_6,          5)
	TAGKEYS(			XK_7,          6)
	TAGKEYS(			XK_8,          7)
	TAGKEYS(			XK_9,          8)
	{ MODKEY,			XK_0,          view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,          tag,                    {.ui = ~0 } },

	{ MODKEY,			XK_Left,       focusmon,               {.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Left,       tagmon,                 {.i = -1 } },
	{ MODKEY,			XK_Right,      focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Right,      tagmon,                 {.i = +1 } },

	{ MODKEY|ShiftMask,		XK_q,          quit,                   {0} },

	{ 0, XF86XK_AudioRaiseVolume,                  spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+ --limit 1.0; pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioLowerVolume,                  spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioMute,                         spawn,                  SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; pkill -RTMIN+10 dwmblocks") },

	{ 0, XF86XK_MonBrightnessUp,                   spawn,                  SHCMD("brightnessctl -q -c backlight set +5%; pkill -RTMIN+2 dwmblocks") },
	{ 0, XF86XK_MonBrightnessDown,                 spawn,                  SHCMD("brightnessctl -q -c backlight set 5%-; pkill -RTMIN+2 dwmblocks") },

	{ 0, XK_Print,                                 spawn,                  SHCMD("maim \"$HOME/Pictures/Screenshots/$(date +'%Y-%m-%d_%H-%M-%S').png\"") },
	{ ShiftMask, XK_Print,                         spawn,                  SHCMD("maim -s \"$HOME/Pictures/Screenshots/$(date +'%Y-%m-%d_%H-%M-%S').png\"") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[6]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

