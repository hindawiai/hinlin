<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * Input event codes
 *
 *    *** IMPORTANT ***
 * This file is not only included from C-code but also from devicetree source
 * files. As such this file MUST only contain comments and defines.
 *
 * Copyright (c) 1999-2002 Vojtech Pavlik
 * Copyright (c) 2015 Hans de Goede <hdegoede@redhat.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */
#अगर_अघोषित _UAPI_INPUT_EVENT_CODES_H
#घोषणा _UAPI_INPUT_EVENT_CODES_H

/*
 * Device properties and quirks
 */

#घोषणा INPUT_PROP_POINTER		0x00	/* needs a poपूर्णांकer */
#घोषणा INPUT_PROP_सूचीECT		0x01	/* direct input devices */
#घोषणा INPUT_PROP_BUTTONPAD		0x02	/* has button(s) under pad */
#घोषणा INPUT_PROP_SEMI_MT		0x03	/* touch rectangle only */
#घोषणा INPUT_PROP_TOPBUTTONPAD		0x04	/* softbuttons at top of pad */
#घोषणा INPUT_PROP_POINTING_STICK	0x05	/* is a poपूर्णांकing stick */
#घोषणा INPUT_PROP_ACCELEROMETER	0x06	/* has accelerometer */

#घोषणा INPUT_PROP_MAX			0x1f
#घोषणा INPUT_PROP_CNT			(INPUT_PROP_MAX + 1)

/*
 * Event types
 */

#घोषणा EV_SYN			0x00
#घोषणा EV_KEY			0x01
#घोषणा EV_REL			0x02
#घोषणा EV_ABS			0x03
#घोषणा EV_MSC			0x04
#घोषणा EV_SW			0x05
#घोषणा EV_LED			0x11
#घोषणा EV_SND			0x12
#घोषणा EV_REP			0x14
#घोषणा EV_FF			0x15
#घोषणा EV_PWR			0x16
#घोषणा EV_FF_STATUS		0x17
#घोषणा EV_MAX			0x1f
#घोषणा EV_CNT			(EV_MAX+1)

/*
 * Synchronization events.
 */

#घोषणा SYN_REPORT		0
#घोषणा SYN_CONFIG		1
#घोषणा SYN_MT_REPORT		2
#घोषणा SYN_DROPPED		3
#घोषणा SYN_MAX			0xf
#घोषणा SYN_CNT			(SYN_MAX+1)

/*
 * Keys and buttons
 *
 * Most of the keys/buttons are modeled after USB HUT 1.12
 * (see http://www.usb.org/developers/hidpage).
 * Abbreviations in the comments:
 * AC - Application Control
 * AL - Application Launch Button
 * SC - System Control
 */

#घोषणा KEY_RESERVED		0
#घोषणा KEY_ESC			1
#घोषणा KEY_1			2
#घोषणा KEY_2			3
#घोषणा KEY_3			4
#घोषणा KEY_4			5
#घोषणा KEY_5			6
#घोषणा KEY_6			7
#घोषणा KEY_7			8
#घोषणा KEY_8			9
#घोषणा KEY_9			10
#घोषणा KEY_0			11
#घोषणा KEY_MINUS		12
#घोषणा KEY_EQUAL		13
#घोषणा KEY_BACKSPACE		14
#घोषणा KEY_TAB			15
#घोषणा KEY_Q			16
#घोषणा KEY_W			17
#घोषणा KEY_E			18
#घोषणा KEY_R			19
#घोषणा KEY_T			20
#घोषणा KEY_Y			21
#घोषणा KEY_U			22
#घोषणा KEY_I			23
#घोषणा KEY_O			24
#घोषणा KEY_P			25
#घोषणा KEY_LEFTBRACE		26
#घोषणा KEY_RIGHTBRACE		27
#घोषणा KEY_ENTER		28
#घोषणा KEY_LEFTCTRL		29
#घोषणा KEY_A			30
#घोषणा KEY_S			31
#घोषणा KEY_D			32
#घोषणा KEY_F			33
#घोषणा KEY_G			34
#घोषणा KEY_H			35
#घोषणा KEY_J			36
#घोषणा KEY_K			37
#घोषणा KEY_L			38
#घोषणा KEY_SEMICOLON		39
#घोषणा KEY_APOSTROPHE		40
#घोषणा KEY_GRAVE		41
#घोषणा KEY_LEFTSHIFT		42
#घोषणा KEY_BACKSLASH		43
#घोषणा KEY_Z			44
#घोषणा KEY_X			45
#घोषणा KEY_C			46
#घोषणा KEY_V			47
#घोषणा KEY_B			48
#घोषणा KEY_N			49
#घोषणा KEY_M			50
#घोषणा KEY_COMMA		51
#घोषणा KEY_DOT			52
#घोषणा KEY_SLASH		53
#घोषणा KEY_RIGHTSHIFT		54
#घोषणा KEY_KPASTERISK		55
#घोषणा KEY_LEFTALT		56
#घोषणा KEY_SPACE		57
#घोषणा KEY_CAPSLOCK		58
#घोषणा KEY_F1			59
#घोषणा KEY_F2			60
#घोषणा KEY_F3			61
#घोषणा KEY_F4			62
#घोषणा KEY_F5			63
#घोषणा KEY_F6			64
#घोषणा KEY_F7			65
#घोषणा KEY_F8			66
#घोषणा KEY_F9			67
#घोषणा KEY_F10			68
#घोषणा KEY_NUMLOCK		69
#घोषणा KEY_SCROLLLOCK		70
#घोषणा KEY_KP7			71
#घोषणा KEY_KP8			72
#घोषणा KEY_KP9			73
#घोषणा KEY_KPMINUS		74
#घोषणा KEY_KP4			75
#घोषणा KEY_KP5			76
#घोषणा KEY_KP6			77
#घोषणा KEY_KPPLUS		78
#घोषणा KEY_KP1			79
#घोषणा KEY_KP2			80
#घोषणा KEY_KP3			81
#घोषणा KEY_KP0			82
#घोषणा KEY_KPDOT		83

#घोषणा KEY_ZENKAKUHANKAKU	85
#घोषणा KEY_102ND		86
#घोषणा KEY_F11			87
#घोषणा KEY_F12			88
#घोषणा KEY_RO			89
#घोषणा KEY_KATAKANA		90
#घोषणा KEY_HIRAGANA		91
#घोषणा KEY_HENKAN		92
#घोषणा KEY_KATAKANAHIRAGANA	93
#घोषणा KEY_MUHENKAN		94
#घोषणा KEY_KPJPCOMMA		95
#घोषणा KEY_KPENTER		96
#घोषणा KEY_RIGHTCTRL		97
#घोषणा KEY_KPSLASH		98
#घोषणा KEY_SYSRQ		99
#घोषणा KEY_RIGHTALT		100
#घोषणा KEY_LINEFEED		101
#घोषणा KEY_HOME		102
#घोषणा KEY_UP			103
#घोषणा KEY_PAGEUP		104
#घोषणा KEY_LEFT		105
#घोषणा KEY_RIGHT		106
#घोषणा KEY_END			107
#घोषणा KEY_DOWN		108
#घोषणा KEY_PAGEDOWN		109
#घोषणा KEY_INSERT		110
#घोषणा KEY_DELETE		111
#घोषणा KEY_MACRO		112
#घोषणा KEY_MUTE		113
#घोषणा KEY_VOLUMEDOWN		114
#घोषणा KEY_VOLUMEUP		115
#घोषणा KEY_POWER		116	/* SC System Power Down */
#घोषणा KEY_KPEQUAL		117
#घोषणा KEY_KPPLUSMINUS		118
#घोषणा KEY_PAUSE		119
#घोषणा KEY_SCALE		120	/* AL Compiz Scale (Expose) */

#घोषणा KEY_KPCOMMA		121
#घोषणा KEY_HANGEUL		122
#घोषणा KEY_HANGUEL		KEY_HANGEUL
#घोषणा KEY_HANJA		123
#घोषणा KEY_YEN			124
#घोषणा KEY_LEFTMETA		125
#घोषणा KEY_RIGHTMETA		126
#घोषणा KEY_COMPOSE		127

#घोषणा KEY_STOP		128	/* AC Stop */
#घोषणा KEY_AGAIN		129
#घोषणा KEY_PROPS		130	/* AC Properties */
#घोषणा KEY_UNDO		131	/* AC Unकरो */
#घोषणा KEY_FRONT		132
#घोषणा KEY_COPY		133	/* AC Copy */
#घोषणा KEY_OPEN		134	/* AC Open */
#घोषणा KEY_PASTE		135	/* AC Paste */
#घोषणा KEY_FIND		136	/* AC Search */
#घोषणा KEY_CUT			137	/* AC Cut */
#घोषणा KEY_HELP		138	/* AL Integrated Help Center */
#घोषणा KEY_MENU		139	/* Menu (show menu) */
#घोषणा KEY_CALC		140	/* AL Calculator */
#घोषणा KEY_SETUP		141
#घोषणा KEY_SLEEP		142	/* SC System Sleep */
#घोषणा KEY_WAKEUP		143	/* System Wake Up */
#घोषणा KEY_खाता		144	/* AL Local Machine Browser */
#घोषणा KEY_SENDखाता		145
#घोषणा KEY_DELETEखाता		146
#घोषणा KEY_XFER		147
#घोषणा KEY_PROG1		148
#घोषणा KEY_PROG2		149
#घोषणा KEY_WWW			150	/* AL Internet Browser */
#घोषणा KEY_MSDOS		151
#घोषणा KEY_COFFEE		152	/* AL Terminal Lock/Screensaver */
#घोषणा KEY_SCREENLOCK		KEY_COFFEE
#घोषणा KEY_ROTATE_DISPLAY	153	/* Display orientation क्रम e.g. tablets */
#घोषणा KEY_सूचीECTION		KEY_ROTATE_DISPLAY
#घोषणा KEY_CYCLEWINDOWS	154
#घोषणा KEY_MAIL		155
#घोषणा KEY_BOOKMARKS		156	/* AC Bookmarks */
#घोषणा KEY_COMPUTER		157
#घोषणा KEY_BACK		158	/* AC Back */
#घोषणा KEY_FORWARD		159	/* AC Forward */
#घोषणा KEY_CLOSECD		160
#घोषणा KEY_EJECTCD		161
#घोषणा KEY_EJECTCLOSECD	162
#घोषणा KEY_NEXTSONG		163
#घोषणा KEY_PLAYPAUSE		164
#घोषणा KEY_PREVIOUSSONG	165
#घोषणा KEY_STOPCD		166
#घोषणा KEY_RECORD		167
#घोषणा KEY_REWIND		168
#घोषणा KEY_PHONE		169	/* Media Select Telephone */
#घोषणा KEY_ISO			170
#घोषणा KEY_CONFIG		171	/* AL Consumer Control Configuration */
#घोषणा KEY_HOMEPAGE		172	/* AC Home */
#घोषणा KEY_REFRESH		173	/* AC Refresh */
#घोषणा KEY_EXIT		174	/* AC Exit */
#घोषणा KEY_MOVE		175
#घोषणा KEY_EDIT		176
#घोषणा KEY_SCROLLUP		177
#घोषणा KEY_SCROLLDOWN		178
#घोषणा KEY_KPLEFTPAREN		179
#घोषणा KEY_KPRIGHTPAREN	180
#घोषणा KEY_NEW			181	/* AC New */
#घोषणा KEY_REDO		182	/* AC Reकरो/Repeat */

#घोषणा KEY_F13			183
#घोषणा KEY_F14			184
#घोषणा KEY_F15			185
#घोषणा KEY_F16			186
#घोषणा KEY_F17			187
#घोषणा KEY_F18			188
#घोषणा KEY_F19			189
#घोषणा KEY_F20			190
#घोषणा KEY_F21			191
#घोषणा KEY_F22			192
#घोषणा KEY_F23			193
#घोषणा KEY_F24			194

#घोषणा KEY_PLAYCD		200
#घोषणा KEY_PAUSECD		201
#घोषणा KEY_PROG3		202
#घोषणा KEY_PROG4		203
#घोषणा KEY_DASHBOARD		204	/* AL Dashboard */
#घोषणा KEY_SUSPEND		205
#घोषणा KEY_CLOSE		206	/* AC Close */
#घोषणा KEY_PLAY		207
#घोषणा KEY_FASTFORWARD		208
#घोषणा KEY_BASSBOOST		209
#घोषणा KEY_PRINT		210	/* AC Prपूर्णांक */
#घोषणा KEY_HP			211
#घोषणा KEY_CAMERA		212
#घोषणा KEY_SOUND		213
#घोषणा KEY_QUESTION		214
#घोषणा KEY_EMAIL		215
#घोषणा KEY_CHAT		216
#घोषणा KEY_SEARCH		217
#घोषणा KEY_CONNECT		218
#घोषणा KEY_FIन_अंकCE		219	/* AL Checkbook/Finance */
#घोषणा KEY_SPORT		220
#घोषणा KEY_SHOP		221
#घोषणा KEY_ALTERASE		222
#घोषणा KEY_CANCEL		223	/* AC Cancel */
#घोषणा KEY_BRIGHTNESSDOWN	224
#घोषणा KEY_BRIGHTNESSUP	225
#घोषणा KEY_MEDIA		226

#घोषणा KEY_SWITCHVIDEOMODE	227	/* Cycle between available video
					   outमाला_दो (Monitor/LCD/TV-out/etc) */
#घोषणा KEY_KBDILLUMTOGGLE	228
#घोषणा KEY_KBDILLUMDOWN	229
#घोषणा KEY_KBDILLUMUP		230

#घोषणा KEY_SEND		231	/* AC Send */
#घोषणा KEY_REPLY		232	/* AC Reply */
#घोषणा KEY_FORWARDMAIL		233	/* AC Forward Msg */
#घोषणा KEY_SAVE		234	/* AC Save */
#घोषणा KEY_DOCUMENTS		235

#घोषणा KEY_BATTERY		236

#घोषणा KEY_BLUETOOTH		237
#घोषणा KEY_WLAN		238
#घोषणा KEY_UWB			239

#घोषणा KEY_UNKNOWN		240

#घोषणा KEY_VIDEO_NEXT		241	/* drive next video source */
#घोषणा KEY_VIDEO_PREV		242	/* drive previous video source */
#घोषणा KEY_BRIGHTNESS_CYCLE	243	/* brightness up, after max is min */
#घोषणा KEY_BRIGHTNESS_AUTO	244	/* Set Auto Brightness: manual
					  brightness control is off,
					  rely on ambient */
#घोषणा KEY_BRIGHTNESS_ZERO	KEY_BRIGHTNESS_AUTO
#घोषणा KEY_DISPLAY_OFF		245	/* display device to off state */

#घोषणा KEY_WWAN		246	/* Wireless WAN (LTE, UMTS, GSM, etc.) */
#घोषणा KEY_WIMAX		KEY_WWAN
#घोषणा KEY_RFKILL		247	/* Key that controls all radios */

#घोषणा KEY_MICMUTE		248	/* Mute / unmute the microphone */

/* Code 255 is reserved क्रम special needs of AT keyboard driver */

#घोषणा BTN_MISC		0x100
#घोषणा BTN_0			0x100
#घोषणा BTN_1			0x101
#घोषणा BTN_2			0x102
#घोषणा BTN_3			0x103
#घोषणा BTN_4			0x104
#घोषणा BTN_5			0x105
#घोषणा BTN_6			0x106
#घोषणा BTN_7			0x107
#घोषणा BTN_8			0x108
#घोषणा BTN_9			0x109

#घोषणा BTN_MOUSE		0x110
#घोषणा BTN_LEFT		0x110
#घोषणा BTN_RIGHT		0x111
#घोषणा BTN_MIDDLE		0x112
#घोषणा BTN_SIDE		0x113
#घोषणा BTN_EXTRA		0x114
#घोषणा BTN_FORWARD		0x115
#घोषणा BTN_BACK		0x116
#घोषणा BTN_TASK		0x117

#घोषणा BTN_JOYSTICK		0x120
#घोषणा BTN_TRIGGER		0x120
#घोषणा BTN_THUMB		0x121
#घोषणा BTN_THUMB2		0x122
#घोषणा BTN_TOP			0x123
#घोषणा BTN_TOP2		0x124
#घोषणा BTN_PINKIE		0x125
#घोषणा BTN_BASE		0x126
#घोषणा BTN_BASE2		0x127
#घोषणा BTN_BASE3		0x128
#घोषणा BTN_BASE4		0x129
#घोषणा BTN_BASE5		0x12a
#घोषणा BTN_BASE6		0x12b
#घोषणा BTN_DEAD		0x12f

#घोषणा BTN_GAMEPAD		0x130
#घोषणा BTN_SOUTH		0x130
#घोषणा BTN_A			BTN_SOUTH
#घोषणा BTN_EAST		0x131
#घोषणा BTN_B			BTN_EAST
#घोषणा BTN_C			0x132
#घोषणा BTN_NORTH		0x133
#घोषणा BTN_X			BTN_NORTH
#घोषणा BTN_WEST		0x134
#घोषणा BTN_Y			BTN_WEST
#घोषणा BTN_Z			0x135
#घोषणा BTN_TL			0x136
#घोषणा BTN_TR			0x137
#घोषणा BTN_TL2			0x138
#घोषणा BTN_TR2			0x139
#घोषणा BTN_SELECT		0x13a
#घोषणा BTN_START		0x13b
#घोषणा BTN_MODE		0x13c
#घोषणा BTN_THUMBL		0x13d
#घोषणा BTN_THUMBR		0x13e

#घोषणा BTN_DIGI		0x140
#घोषणा BTN_TOOL_PEN		0x140
#घोषणा BTN_TOOL_RUBBER		0x141
#घोषणा BTN_TOOL_BRUSH		0x142
#घोषणा BTN_TOOL_PENCIL		0x143
#घोषणा BTN_TOOL_AIRBRUSH	0x144
#घोषणा BTN_TOOL_FINGER		0x145
#घोषणा BTN_TOOL_MOUSE		0x146
#घोषणा BTN_TOOL_LENS		0x147
#घोषणा BTN_TOOL_QUINTTAP	0x148	/* Five fingers on trackpad */
#घोषणा BTN_STYLUS3		0x149
#घोषणा BTN_TOUCH		0x14a
#घोषणा BTN_STYLUS		0x14b
#घोषणा BTN_STYLUS2		0x14c
#घोषणा BTN_TOOL_DOUBLETAP	0x14d
#घोषणा BTN_TOOL_TRIPLETAP	0x14e
#घोषणा BTN_TOOL_QUADTAP	0x14f	/* Four fingers on trackpad */

#घोषणा BTN_WHEEL		0x150
#घोषणा BTN_GEAR_DOWN		0x150
#घोषणा BTN_GEAR_UP		0x151

#घोषणा KEY_OK			0x160
#घोषणा KEY_SELECT		0x161
#घोषणा KEY_GOTO		0x162
#घोषणा KEY_CLEAR		0x163
#घोषणा KEY_POWER2		0x164
#घोषणा KEY_OPTION		0x165
#घोषणा KEY_INFO		0x166	/* AL OEM Features/Tips/Tutorial */
#घोषणा KEY_TIME		0x167
#घोषणा KEY_VENDOR		0x168
#घोषणा KEY_ARCHIVE		0x169
#घोषणा KEY_PROGRAM		0x16a	/* Media Select Program Guide */
#घोषणा KEY_CHANNEL		0x16b
#घोषणा KEY_FAVORITES		0x16c
#घोषणा KEY_EPG			0x16d
#घोषणा KEY_PVR			0x16e	/* Media Select Home */
#घोषणा KEY_MHP			0x16f
#घोषणा KEY_LANGUAGE		0x170
#घोषणा KEY_TITLE		0x171
#घोषणा KEY_SUBTITLE		0x172
#घोषणा KEY_ANGLE		0x173
#घोषणा KEY_FULL_SCREEN		0x174	/* AC View Toggle */
#घोषणा KEY_ZOOM		KEY_FULL_SCREEN
#घोषणा KEY_MODE		0x175
#घोषणा KEY_KEYBOARD		0x176
#घोषणा KEY_ASPECT_RATIO	0x177	/* HUTRR37: Aspect */
#घोषणा KEY_SCREEN		KEY_ASPECT_RATIO
#घोषणा KEY_PC			0x178	/* Media Select Computer */
#घोषणा KEY_TV			0x179	/* Media Select TV */
#घोषणा KEY_TV2			0x17a	/* Media Select Cable */
#घोषणा KEY_VCR			0x17b	/* Media Select VCR */
#घोषणा KEY_VCR2		0x17c	/* VCR Plus */
#घोषणा KEY_SAT			0x17d	/* Media Select Satellite */
#घोषणा KEY_SAT2		0x17e
#घोषणा KEY_CD			0x17f	/* Media Select CD */
#घोषणा KEY_TAPE		0x180	/* Media Select Tape */
#घोषणा KEY_RADIO		0x181
#घोषणा KEY_TUNER		0x182	/* Media Select Tuner */
#घोषणा KEY_PLAYER		0x183
#घोषणा KEY_TEXT		0x184
#घोषणा KEY_DVD			0x185	/* Media Select DVD */
#घोषणा KEY_AUX			0x186
#घोषणा KEY_MP3			0x187
#घोषणा KEY_AUDIO		0x188	/* AL Audio Browser */
#घोषणा KEY_VIDEO		0x189	/* AL Movie Browser */
#घोषणा KEY_सूचीECTORY		0x18a
#घोषणा KEY_LIST		0x18b
#घोषणा KEY_MEMO		0x18c	/* Media Select Messages */
#घोषणा KEY_CALENDAR		0x18d
#घोषणा KEY_RED			0x18e
#घोषणा KEY_GREEN		0x18f
#घोषणा KEY_YELLOW		0x190
#घोषणा KEY_BLUE		0x191
#घोषणा KEY_CHANNELUP		0x192	/* Channel Increment */
#घोषणा KEY_CHANNELDOWN		0x193	/* Channel Decrement */
#घोषणा KEY_FIRST		0x194
#घोषणा KEY_LAST		0x195	/* Recall Last */
#घोषणा KEY_AB			0x196
#घोषणा KEY_NEXT		0x197
#घोषणा KEY_RESTART		0x198
#घोषणा KEY_SLOW		0x199
#घोषणा KEY_SHUFFLE		0x19a
#घोषणा KEY_BREAK		0x19b
#घोषणा KEY_PREVIOUS		0x19c
#घोषणा KEY_DIGITS		0x19d
#घोषणा KEY_TEEN		0x19e
#घोषणा KEY_TWEN		0x19f
#घोषणा KEY_VIDEOPHONE		0x1a0	/* Media Select Video Phone */
#घोषणा KEY_GAMES		0x1a1	/* Media Select Games */
#घोषणा KEY_ZOOMIN		0x1a2	/* AC Zoom In */
#घोषणा KEY_ZOOMOUT		0x1a3	/* AC Zoom Out */
#घोषणा KEY_ZOOMRESET		0x1a4	/* AC Zoom */
#घोषणा KEY_WORDPROCESSOR	0x1a5	/* AL Word Processor */
#घोषणा KEY_EDITOR		0x1a6	/* AL Text Editor */
#घोषणा KEY_SPREADSHEET		0x1a7	/* AL Spपढ़ोsheet */
#घोषणा KEY_GRAPHICSEDITOR	0x1a8	/* AL Graphics Editor */
#घोषणा KEY_PRESENTATION	0x1a9	/* AL Presentation App */
#घोषणा KEY_DATABASE		0x1aa	/* AL Database App */
#घोषणा KEY_NEWS		0x1ab	/* AL Newsपढ़ोer */
#घोषणा KEY_VOICEMAIL		0x1ac	/* AL Voicemail */
#घोषणा KEY_ADDRESSBOOK		0x1ad	/* AL Contacts/Address Book */
#घोषणा KEY_MESSENGER		0x1ae	/* AL Instant Messaging */
#घोषणा KEY_DISPLAYTOGGLE	0x1af	/* Turn display (LCD) on and off */
#घोषणा KEY_BRIGHTNESS_TOGGLE	KEY_DISPLAYTOGGLE
#घोषणा KEY_SPELLCHECK		0x1b0   /* AL Spell Check */
#घोषणा KEY_LOGOFF		0x1b1   /* AL Logoff */

#घोषणा KEY_DOLLAR		0x1b2
#घोषणा KEY_EURO		0x1b3

#घोषणा KEY_FRAMEBACK		0x1b4	/* Consumer - transport controls */
#घोषणा KEY_FRAMEFORWARD	0x1b5
#घोषणा KEY_CONTEXT_MENU	0x1b6	/* GenDesc - प्रणाली context menu */
#घोषणा KEY_MEDIA_REPEAT	0x1b7	/* Consumer - transport control */
#घोषणा KEY_10CHANNELSUP	0x1b8	/* 10 channels up (10+) */
#घोषणा KEY_10CHANNELSDOWN	0x1b9	/* 10 channels करोwn (10-) */
#घोषणा KEY_IMAGES		0x1ba	/* AL Image Browser */
#घोषणा KEY_NOTIFICATION_CENTER	0x1bc	/* Show/hide the notअगरication center */
#घोषणा KEY_PICKUP_PHONE	0x1bd	/* Answer incoming call */
#घोषणा KEY_HANGUP_PHONE	0x1be	/* Decline incoming call */

#घोषणा KEY_DEL_EOL		0x1c0
#घोषणा KEY_DEL_EOS		0x1c1
#घोषणा KEY_INS_LINE		0x1c2
#घोषणा KEY_DEL_LINE		0x1c3

#घोषणा KEY_FN			0x1d0
#घोषणा KEY_FN_ESC		0x1d1
#घोषणा KEY_FN_F1		0x1d2
#घोषणा KEY_FN_F2		0x1d3
#घोषणा KEY_FN_F3		0x1d4
#घोषणा KEY_FN_F4		0x1d5
#घोषणा KEY_FN_F5		0x1d6
#घोषणा KEY_FN_F6		0x1d7
#घोषणा KEY_FN_F7		0x1d8
#घोषणा KEY_FN_F8		0x1d9
#घोषणा KEY_FN_F9		0x1da
#घोषणा KEY_FN_F10		0x1db
#घोषणा KEY_FN_F11		0x1dc
#घोषणा KEY_FN_F12		0x1dd
#घोषणा KEY_FN_1		0x1de
#घोषणा KEY_FN_2		0x1df
#घोषणा KEY_FN_D		0x1e0
#घोषणा KEY_FN_E		0x1e1
#घोषणा KEY_FN_F		0x1e2
#घोषणा KEY_FN_S		0x1e3
#घोषणा KEY_FN_B		0x1e4
#घोषणा KEY_FN_RIGHT_SHIFT	0x1e5

#घोषणा KEY_BRL_DOT1		0x1f1
#घोषणा KEY_BRL_DOT2		0x1f2
#घोषणा KEY_BRL_DOT3		0x1f3
#घोषणा KEY_BRL_DOT4		0x1f4
#घोषणा KEY_BRL_DOT5		0x1f5
#घोषणा KEY_BRL_DOT6		0x1f6
#घोषणा KEY_BRL_DOT7		0x1f7
#घोषणा KEY_BRL_DOT8		0x1f8
#घोषणा KEY_BRL_DOT9		0x1f9
#घोषणा KEY_BRL_DOT10		0x1fa

#घोषणा KEY_NUMERIC_0		0x200	/* used by phones, remote controls, */
#घोषणा KEY_NUMERIC_1		0x201	/* and other keypads */
#घोषणा KEY_NUMERIC_2		0x202
#घोषणा KEY_NUMERIC_3		0x203
#घोषणा KEY_NUMERIC_4		0x204
#घोषणा KEY_NUMERIC_5		0x205
#घोषणा KEY_NUMERIC_6		0x206
#घोषणा KEY_NUMERIC_7		0x207
#घोषणा KEY_NUMERIC_8		0x208
#घोषणा KEY_NUMERIC_9		0x209
#घोषणा KEY_NUMERIC_STAR	0x20a
#घोषणा KEY_NUMERIC_POUND	0x20b
#घोषणा KEY_NUMERIC_A		0x20c	/* Phone key A - HUT Telephony 0xb9 */
#घोषणा KEY_NUMERIC_B		0x20d
#घोषणा KEY_NUMERIC_C		0x20e
#घोषणा KEY_NUMERIC_D		0x20f

#घोषणा KEY_CAMERA_FOCUS	0x210
#घोषणा KEY_WPS_BUTTON		0x211	/* WiFi Protected Setup key */

#घोषणा KEY_TOUCHPAD_TOGGLE	0x212	/* Request चयन touchpad on or off */
#घोषणा KEY_TOUCHPAD_ON		0x213
#घोषणा KEY_TOUCHPAD_OFF	0x214

#घोषणा KEY_CAMERA_ZOOMIN	0x215
#घोषणा KEY_CAMERA_ZOOMOUT	0x216
#घोषणा KEY_CAMERA_UP		0x217
#घोषणा KEY_CAMERA_DOWN		0x218
#घोषणा KEY_CAMERA_LEFT		0x219
#घोषणा KEY_CAMERA_RIGHT	0x21a

#घोषणा KEY_ATTENDANT_ON	0x21b
#घोषणा KEY_ATTENDANT_OFF	0x21c
#घोषणा KEY_ATTENDANT_TOGGLE	0x21d	/* Attendant call on or off */
#घोषणा KEY_LIGHTS_TOGGLE	0x21e	/* Reading light on or off */

#घोषणा BTN_DPAD_UP		0x220
#घोषणा BTN_DPAD_DOWN		0x221
#घोषणा BTN_DPAD_LEFT		0x222
#घोषणा BTN_DPAD_RIGHT		0x223

#घोषणा KEY_ALS_TOGGLE		0x230	/* Ambient light sensor */
#घोषणा KEY_ROTATE_LOCK_TOGGLE	0x231	/* Display rotation lock */

#घोषणा KEY_BUTTONCONFIG		0x240	/* AL Button Configuration */
#घोषणा KEY_TASKMANAGER		0x241	/* AL Task/Project Manager */
#घोषणा KEY_JOURNAL		0x242	/* AL Log/Journal/Timecard */
#घोषणा KEY_CONTROLPANEL		0x243	/* AL Control Panel */
#घोषणा KEY_APPSELECT		0x244	/* AL Select Task/Application */
#घोषणा KEY_SCREENSAVER		0x245	/* AL Screen Saver */
#घोषणा KEY_VOICECOMMAND		0x246	/* Listening Voice Command */
#घोषणा KEY_ASSISTANT		0x247	/* AL Context-aware desktop assistant */
#घोषणा KEY_KBD_LAYOUT_NEXT	0x248	/* AC Next Keyboard Layout Select */
#घोषणा KEY_EMOJI_PICKER	0x249	/* Show/hide emoji picker (HUTRR101) */

#घोषणा KEY_BRIGHTNESS_MIN		0x250	/* Set Brightness to Minimum */
#घोषणा KEY_BRIGHTNESS_MAX		0x251	/* Set Brightness to Maximum */

#घोषणा KEY_KBDINPUTASSIST_PREV		0x260
#घोषणा KEY_KBDINPUTASSIST_NEXT		0x261
#घोषणा KEY_KBDINPUTASSIST_PREVGROUP		0x262
#घोषणा KEY_KBDINPUTASSIST_NEXTGROUP		0x263
#घोषणा KEY_KBDINPUTASSIST_ACCEPT		0x264
#घोषणा KEY_KBDINPUTASSIST_CANCEL		0x265

/* Diagonal movement keys */
#घोषणा KEY_RIGHT_UP			0x266
#घोषणा KEY_RIGHT_DOWN			0x267
#घोषणा KEY_LEFT_UP			0x268
#घोषणा KEY_LEFT_DOWN			0x269

#घोषणा KEY_ROOT_MENU			0x26a /* Show Device's Root Menu */
/* Show Top Menu of the Media (e.g. DVD) */
#घोषणा KEY_MEDIA_TOP_MENU		0x26b
#घोषणा KEY_NUMERIC_11			0x26c
#घोषणा KEY_NUMERIC_12			0x26d
/*
 * Toggle Audio Description: refers to an audio service that helps blind and
 * visually impaired consumers understand the action in a program. Note: in
 * some countries this is referred to as "Video Description".
 */
#घोषणा KEY_AUDIO_DESC			0x26e
#घोषणा KEY_3D_MODE			0x26f
#घोषणा KEY_NEXT_FAVORITE		0x270
#घोषणा KEY_STOP_RECORD			0x271
#घोषणा KEY_PAUSE_RECORD		0x272
#घोषणा KEY_VOD				0x273 /* Video on Demand */
#घोषणा KEY_UNMUTE			0x274
#घोषणा KEY_FASTREVERSE			0x275
#घोषणा KEY_SLOWREVERSE			0x276
/*
 * Control a data application associated with the currently viewed channel,
 * e.g. teletext or data broadcast application (MHEG, MHP, HbbTV, etc.)
 */
#घोषणा KEY_DATA			0x277
#घोषणा KEY_ONSCREEN_KEYBOARD		0x278
/* Electronic privacy screen control */
#घोषणा KEY_PRIVACY_SCREEN_TOGGLE	0x279

/* Select an area of screen to be copied */
#घोषणा KEY_SELECTIVE_SCREENSHOT	0x27a

/*
 * Some keyboards have keys which करो not have a defined meaning, these keys
 * are पूर्णांकended to be programmed / bound to macros by the user. For most
 * keyboards with these macro-keys the key-sequence to inject, or action to
 * take, is all handled by software on the host side. So from the kernel's
 * poपूर्णांक of view these are just normal keys.
 *
 * The KEY_MACRO# codes below are पूर्णांकended क्रम such keys, which may be labeled
 * e.g. G1-G18, or S1 - S30. The KEY_MACRO# codes MUST NOT be used क्रम keys
 * where the marking on the key करोes indicate a defined meaning / purpose.
 *
 * The KEY_MACRO# codes MUST also NOT be used as fallback क्रम when no existing
 * KEY_FOO define matches the marking / purpose. In this हाल a new KEY_FOO
 * define MUST be added.
 */
#घोषणा KEY_MACRO1			0x290
#घोषणा KEY_MACRO2			0x291
#घोषणा KEY_MACRO3			0x292
#घोषणा KEY_MACRO4			0x293
#घोषणा KEY_MACRO5			0x294
#घोषणा KEY_MACRO6			0x295
#घोषणा KEY_MACRO7			0x296
#घोषणा KEY_MACRO8			0x297
#घोषणा KEY_MACRO9			0x298
#घोषणा KEY_MACRO10			0x299
#घोषणा KEY_MACRO11			0x29a
#घोषणा KEY_MACRO12			0x29b
#घोषणा KEY_MACRO13			0x29c
#घोषणा KEY_MACRO14			0x29d
#घोषणा KEY_MACRO15			0x29e
#घोषणा KEY_MACRO16			0x29f
#घोषणा KEY_MACRO17			0x2a0
#घोषणा KEY_MACRO18			0x2a1
#घोषणा KEY_MACRO19			0x2a2
#घोषणा KEY_MACRO20			0x2a3
#घोषणा KEY_MACRO21			0x2a4
#घोषणा KEY_MACRO22			0x2a5
#घोषणा KEY_MACRO23			0x2a6
#घोषणा KEY_MACRO24			0x2a7
#घोषणा KEY_MACRO25			0x2a8
#घोषणा KEY_MACRO26			0x2a9
#घोषणा KEY_MACRO27			0x2aa
#घोषणा KEY_MACRO28			0x2ab
#घोषणा KEY_MACRO29			0x2ac
#घोषणा KEY_MACRO30			0x2ad

/*
 * Some keyboards with the macro-keys described above have some extra keys
 * क्रम controlling the host-side software responsible क्रम the macro handling:
 * -A macro recording start/stop key. Note that not all keyboards which emit
 *  KEY_MACRO_RECORD_START will also emit KEY_MACRO_RECORD_STOP अगर
 *  KEY_MACRO_RECORD_STOP is not advertised, then KEY_MACRO_RECORD_START
 *  should be पूर्णांकerpreted as a recording start/stop toggle;
 * -Keys क्रम चयनing between dअगरferent macro (pre)sets, either a key क्रम
 *  cycling through the configured presets or keys to directly select a preset.
 */
#घोषणा KEY_MACRO_RECORD_START		0x2b0
#घोषणा KEY_MACRO_RECORD_STOP		0x2b1
#घोषणा KEY_MACRO_PRESET_CYCLE		0x2b2
#घोषणा KEY_MACRO_PRESET1		0x2b3
#घोषणा KEY_MACRO_PRESET2		0x2b4
#घोषणा KEY_MACRO_PRESET3		0x2b5

/*
 * Some keyboards have a buildin LCD panel where the contents are controlled
 * by the host. Often these have a number of keys directly below the LCD
 * पूर्णांकended क्रम controlling a menu shown on the LCD. These keys often करोn't
 * have any labeling so we just name them KEY_KBD_LCD_MENU#
 */
#घोषणा KEY_KBD_LCD_MENU1		0x2b8
#घोषणा KEY_KBD_LCD_MENU2		0x2b9
#घोषणा KEY_KBD_LCD_MENU3		0x2ba
#घोषणा KEY_KBD_LCD_MENU4		0x2bb
#घोषणा KEY_KBD_LCD_MENU5		0x2bc

#घोषणा BTN_TRIGGER_HAPPY		0x2c0
#घोषणा BTN_TRIGGER_HAPPY1		0x2c0
#घोषणा BTN_TRIGGER_HAPPY2		0x2c1
#घोषणा BTN_TRIGGER_HAPPY3		0x2c2
#घोषणा BTN_TRIGGER_HAPPY4		0x2c3
#घोषणा BTN_TRIGGER_HAPPY5		0x2c4
#घोषणा BTN_TRIGGER_HAPPY6		0x2c5
#घोषणा BTN_TRIGGER_HAPPY7		0x2c6
#घोषणा BTN_TRIGGER_HAPPY8		0x2c7
#घोषणा BTN_TRIGGER_HAPPY9		0x2c8
#घोषणा BTN_TRIGGER_HAPPY10		0x2c9
#घोषणा BTN_TRIGGER_HAPPY11		0x2ca
#घोषणा BTN_TRIGGER_HAPPY12		0x2cb
#घोषणा BTN_TRIGGER_HAPPY13		0x2cc
#घोषणा BTN_TRIGGER_HAPPY14		0x2cd
#घोषणा BTN_TRIGGER_HAPPY15		0x2ce
#घोषणा BTN_TRIGGER_HAPPY16		0x2cf
#घोषणा BTN_TRIGGER_HAPPY17		0x2d0
#घोषणा BTN_TRIGGER_HAPPY18		0x2d1
#घोषणा BTN_TRIGGER_HAPPY19		0x2d2
#घोषणा BTN_TRIGGER_HAPPY20		0x2d3
#घोषणा BTN_TRIGGER_HAPPY21		0x2d4
#घोषणा BTN_TRIGGER_HAPPY22		0x2d5
#घोषणा BTN_TRIGGER_HAPPY23		0x2d6
#घोषणा BTN_TRIGGER_HAPPY24		0x2d7
#घोषणा BTN_TRIGGER_HAPPY25		0x2d8
#घोषणा BTN_TRIGGER_HAPPY26		0x2d9
#घोषणा BTN_TRIGGER_HAPPY27		0x2da
#घोषणा BTN_TRIGGER_HAPPY28		0x2db
#घोषणा BTN_TRIGGER_HAPPY29		0x2dc
#घोषणा BTN_TRIGGER_HAPPY30		0x2dd
#घोषणा BTN_TRIGGER_HAPPY31		0x2de
#घोषणा BTN_TRIGGER_HAPPY32		0x2df
#घोषणा BTN_TRIGGER_HAPPY33		0x2e0
#घोषणा BTN_TRIGGER_HAPPY34		0x2e1
#घोषणा BTN_TRIGGER_HAPPY35		0x2e2
#घोषणा BTN_TRIGGER_HAPPY36		0x2e3
#घोषणा BTN_TRIGGER_HAPPY37		0x2e4
#घोषणा BTN_TRIGGER_HAPPY38		0x2e5
#घोषणा BTN_TRIGGER_HAPPY39		0x2e6
#घोषणा BTN_TRIGGER_HAPPY40		0x2e7

/* We aव्योम low common keys in module aliases so they करोn't get huge. */
#घोषणा KEY_MIN_INTERESTING	KEY_MUTE
#घोषणा KEY_MAX			0x2ff
#घोषणा KEY_CNT			(KEY_MAX+1)

/*
 * Relative axes
 */

#घोषणा REL_X			0x00
#घोषणा REL_Y			0x01
#घोषणा REL_Z			0x02
#घोषणा REL_RX			0x03
#घोषणा REL_RY			0x04
#घोषणा REL_RZ			0x05
#घोषणा REL_HWHEEL		0x06
#घोषणा REL_DIAL		0x07
#घोषणा REL_WHEEL		0x08
#घोषणा REL_MISC		0x09
/*
 * 0x0a is reserved and should not be used in input drivers.
 * It was used by HID as REL_MISC+1 and userspace needs to detect अगर
 * the next REL_* event is correct or is just REL_MISC + n.
 * We define here REL_RESERVED so userspace can rely on it and detect
 * the situation described above.
 */
#घोषणा REL_RESERVED		0x0a
#घोषणा REL_WHEEL_HI_RES	0x0b
#घोषणा REL_HWHEEL_HI_RES	0x0c
#घोषणा REL_MAX			0x0f
#घोषणा REL_CNT			(REL_MAX+1)

/*
 * Absolute axes
 */

#घोषणा ABS_X			0x00
#घोषणा ABS_Y			0x01
#घोषणा ABS_Z			0x02
#घोषणा ABS_RX			0x03
#घोषणा ABS_RY			0x04
#घोषणा ABS_RZ			0x05
#घोषणा ABS_THROTTLE		0x06
#घोषणा ABS_RUDDER		0x07
#घोषणा ABS_WHEEL		0x08
#घोषणा ABS_GAS			0x09
#घोषणा ABS_BRAKE		0x0a
#घोषणा ABS_HAT0X		0x10
#घोषणा ABS_HAT0Y		0x11
#घोषणा ABS_HAT1X		0x12
#घोषणा ABS_HAT1Y		0x13
#घोषणा ABS_HAT2X		0x14
#घोषणा ABS_HAT2Y		0x15
#घोषणा ABS_HAT3X		0x16
#घोषणा ABS_HAT3Y		0x17
#घोषणा ABS_PRESSURE		0x18
#घोषणा ABS_DISTANCE		0x19
#घोषणा ABS_TILT_X		0x1a
#घोषणा ABS_TILT_Y		0x1b
#घोषणा ABS_TOOL_WIDTH		0x1c

#घोषणा ABS_VOLUME		0x20

#घोषणा ABS_MISC		0x28

/*
 * 0x2e is reserved and should not be used in input drivers.
 * It was used by HID as ABS_MISC+6 and userspace needs to detect अगर
 * the next ABS_* event is correct or is just ABS_MISC + n.
 * We define here ABS_RESERVED so userspace can rely on it and detect
 * the situation described above.
 */
#घोषणा ABS_RESERVED		0x2e

#घोषणा ABS_MT_SLOT		0x2f	/* MT slot being modअगरied */
#घोषणा ABS_MT_TOUCH_MAJOR	0x30	/* Major axis of touching ellipse */
#घोषणा ABS_MT_TOUCH_MINOR	0x31	/* Minor axis (omit अगर circular) */
#घोषणा ABS_MT_WIDTH_MAJOR	0x32	/* Major axis of approaching ellipse */
#घोषणा ABS_MT_WIDTH_MINOR	0x33	/* Minor axis (omit अगर circular) */
#घोषणा ABS_MT_ORIENTATION	0x34	/* Ellipse orientation */
#घोषणा ABS_MT_POSITION_X	0x35	/* Center X touch position */
#घोषणा ABS_MT_POSITION_Y	0x36	/* Center Y touch position */
#घोषणा ABS_MT_TOOL_TYPE	0x37	/* Type of touching device */
#घोषणा ABS_MT_BLOB_ID		0x38	/* Group a set of packets as a blob */
#घोषणा ABS_MT_TRACKING_ID	0x39	/* Unique ID of initiated contact */
#घोषणा ABS_MT_PRESSURE		0x3a	/* Pressure on contact area */
#घोषणा ABS_MT_DISTANCE		0x3b	/* Contact hover distance */
#घोषणा ABS_MT_TOOL_X		0x3c	/* Center X tool position */
#घोषणा ABS_MT_TOOL_Y		0x3d	/* Center Y tool position */


#घोषणा ABS_MAX			0x3f
#घोषणा ABS_CNT			(ABS_MAX+1)

/*
 * Switch events
 */

#घोषणा SW_LID			0x00  /* set = lid shut */
#घोषणा SW_TABLET_MODE		0x01  /* set = tablet mode */
#घोषणा SW_HEADPHONE_INSERT	0x02  /* set = inserted */
#घोषणा SW_RFKILL_ALL		0x03  /* rfसमाप्त master चयन, type "any"
					 set = radio enabled */
#घोषणा SW_RADIO		SW_RFKILL_ALL	/* deprecated */
#घोषणा SW_MICROPHONE_INSERT	0x04  /* set = inserted */
#घोषणा SW_DOCK			0x05  /* set = plugged पूर्णांकo करोck */
#घोषणा SW_LINEOUT_INSERT	0x06  /* set = inserted */
#घोषणा SW_JACK_PHYSICAL_INSERT 0x07  /* set = mechanical चयन set */
#घोषणा SW_VIDEOOUT_INSERT	0x08  /* set = inserted */
#घोषणा SW_CAMERA_LENS_COVER	0x09  /* set = lens covered */
#घोषणा SW_KEYPAD_SLIDE		0x0a  /* set = keypad slide out */
#घोषणा SW_FRONT_PROXIMITY	0x0b  /* set = front proximity sensor active */
#घोषणा SW_ROTATE_LOCK		0x0c  /* set = rotate locked/disabled */
#घोषणा SW_LINEIN_INSERT	0x0d  /* set = inserted */
#घोषणा SW_MUTE_DEVICE		0x0e  /* set = device disabled */
#घोषणा SW_PEN_INSERTED		0x0f  /* set = pen inserted */
#घोषणा SW_MACHINE_COVER	0x10  /* set = cover बंदd */
#घोषणा SW_MAX			0x10
#घोषणा SW_CNT			(SW_MAX+1)

/*
 * Misc events
 */

#घोषणा MSC_SERIAL		0x00
#घोषणा MSC_PULSELED		0x01
#घोषणा MSC_GESTURE		0x02
#घोषणा MSC_RAW			0x03
#घोषणा MSC_SCAN		0x04
#घोषणा MSC_TIMESTAMP		0x05
#घोषणा MSC_MAX			0x07
#घोषणा MSC_CNT			(MSC_MAX+1)

/*
 * LEDs
 */

#घोषणा LED_NUML		0x00
#घोषणा LED_CAPSL		0x01
#घोषणा LED_SCROLLL		0x02
#घोषणा LED_COMPOSE		0x03
#घोषणा LED_KANA		0x04
#घोषणा LED_SLEEP		0x05
#घोषणा LED_SUSPEND		0x06
#घोषणा LED_MUTE		0x07
#घोषणा LED_MISC		0x08
#घोषणा LED_MAIL		0x09
#घोषणा LED_CHARGING		0x0a
#घोषणा LED_MAX			0x0f
#घोषणा LED_CNT			(LED_MAX+1)

/*
 * Autorepeat values
 */

#घोषणा REP_DELAY		0x00
#घोषणा REP_PERIOD		0x01
#घोषणा REP_MAX			0x01
#घोषणा REP_CNT			(REP_MAX+1)

/*
 * Sounds
 */

#घोषणा SND_CLICK		0x00
#घोषणा SND_BELL		0x01
#घोषणा SND_TONE		0x02
#घोषणा SND_MAX			0x07
#घोषणा SND_CNT			(SND_MAX+1)

#पूर्ण_अगर
