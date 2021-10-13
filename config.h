#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const float scalepreview     = 2.4;      /* Tag preview scaling */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 42;	/* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int user_bv            = 35;	/* 0 means that dwm will calculate bar padding, >= 1 means dwm will user_bh as bar padding */
static const char *fonts[]          = { "TeX Gyre Bonum Math:size=16" };
static const char dmenufont[]       = "TeX Gyre Bonum Math:size=16";
static const char col_gray1[]       = "#28303c"; /* dwm old col_cyan, used for dmenu only */
static const char col_gray2[]       = "#1E242D"; /* unselected window border */
static const char col_gray3[]       = "#A8AEB5"; /* unselected tag */
static const char col_gray4[]       = "#e9f6fe"; /* selected tag */
static const char col_gray5[]       = "#e9f6fe"; /* selected window border */
static const char col_cyan[]        = "#1E242D"; /* dwm default color */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_cyan,  col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray5 },
};

/* tagging */
static const char *tags[] = { " ", " ", "∬", "", "?", "", "","", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance    title       tags mask     isfloating   monitor */
	 { "Gimp",            NULL,       NULL,       0,            1,           -1 },
	 { "thunderbird",     NULL,       NULL,       1 << 5,       0,           -1 },
	 { "feh",             NULL,       NULL,       0,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_cyan, "-nf", col_gray3, "-sb", col_gray1, "-sf", col_gray4, NULL };
static const char *poweroffcmd[]= {"powermenu.sh", NULL};
static const char *gnomecmd[]= {"launcher_.sh", NULL};
static const char *leftclickstatuscmd[]= {"/usr/bin/run_with_left_mouse_click.sh", NULL};
static const char *termcmd[]    = {"xfce4-terminal", NULL};
static const char *mutecmd[]    = {"volmute.sh", NULL};
static const char *volupcmd[]   = {"volup.sh", NULL};
static const char *voldowncmd[] = {"voldown.sh", NULL};
static const char *roficmd[]    = {"launcher.sh", NULL };
static const char *brightness_up[]    = {"bright.sh","up", NULL };
static const char *brightness_down[]  = {"bright.sh","down", NULL };
static const char *xfce4_screenshooter[]= {"xfce4-screenshooter", NULL };
static const char *rightclickstatuscmd[]= {"/usr/bin/run_with_right_mouse_click.sh", NULL};

static Key keys[] = {
	/* modifier                     key        			        function        argument */
	{ MODKEY,                       XK_p,      			        spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, 			        spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      			        togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      			        rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      			        rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      			        focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      			        focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      			        incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      			        incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      			        setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      			        setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      			        setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      			        setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,     			        setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, 			        zoom,           {0} },
	{ MODKEY,                       XK_0,    			        view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      			        killclient,     {0} },
	{ MODKEY,                       XK_t,      			        setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      			        setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      			        setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,                       		setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  			        setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  			        togglefloating, {0} },
	{ MODKEY,                       XK_Tab,                     		view,           {.ui = ~0 } },
	{ MODKEY,                       XK_Tab,                                 setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_Tab,                     		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      			        tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  			        focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 			        focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  			        tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 			        tagmon,         {.i = +1 } },
	{ 0, 				XF86XK_AudioMute,          		spawn,		{.v = mutecmd } },
	{ 0, 				XF86XK_AudioLowerVolume,   		spawn,		{.v = voldowncmd } },
	{ 0, 				XF86XK_AudioRaiseVolume,   		spawn,          {.v = volupcmd } },
	{ 0,				XK_Print,  			        spawn,          {.v = xfce4_screenshooter } },
	{ MODKEY, 			XK_r, 	   			        spawn, 	   	{.v = roficmd } },
	{ 0,                            XF86XK_MonBrightnessUp,   		spawn, 		{.v = brightness_up } },
	{ 0,                            XF86XK_MonBrightnessDown, 		spawn, 		{.v = brightness_down } },
	{ MODKEY|ShiftMask,	            XK_p,	 			spawn,          {.v = poweroffcmd } },
	{ MODKEY|ShiftMask,	            XK_r,	 			spawn,          {.v = gnomecmd } },
	{ MODKEY,                       XK_o,      			        winview,        {0} },
	TAGKEYS(                        XK_1,                      			        0)
	TAGKEYS(                        XK_2,                      			        1)
	TAGKEYS(                        XK_3,                      			        2)
	TAGKEYS(                        XK_4,                      			        3)
	TAGKEYS(                        XK_5,                      			        4)
	TAGKEYS(                        XK_6,                      			        5)
	TAGKEYS(                        XK_7,                      			        6)
	TAGKEYS(                        XK_8,                      			        7)
	TAGKEYS(                        XK_9,                      			        8)
	{ MODKEY|ShiftMask,             XK_q,      			        quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      	button          function        argument */
	{ ClkLtSymbol,          0,              	Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              	Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              	Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              	Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              	Button1,        spawn,          {.v = leftclickstatuscmd } },
	{ ClkStatusText,        0,                  	Button3,        spawn,          {.v = rightclickstatuscmd } },
	{ ClkClientWin,         MODKEY|ShiftMask,         	Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         	Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         	Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,			Button1,	zoom,           {0} },
	{ ClkClientWin,		MODKEY|ShiftMask,       Button1,	setlayout,      {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,   	Button3,	winview,        {0} },
	{ ClkClientWin,         MODKEY,         	Button4,	setmfact,       {.f = -0.05} },
	{ ClkClientWin,         MODKEY,         	Button5,	setmfact,       {.f = +0.05} },
	{ ClkClientWin,		MODKEY|ShiftMask,       Button5,      	setcfact,       {.f = +0.25} },
	{ ClkClientWin,		MODKEY|ShiftMask,       Button4,      	setcfact,       {.f = -0.25} },
	{ ClkTagBar,            0,              	Button1,        view,           {0} },
	{ ClkTagBar,            0,              	Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         	Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         	Button3,        toggletag,      {0} },
	{ ClkTagBar,            MODKEY|ShiftMask,   Button1,        spawn,          {.v = leftclickstatuscmd } },
	{ ClkTagBar,            MODKEY|ShiftMask,   Button3,        spawn,          {.v = rightclickstatuscmd } },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 0} },
};
