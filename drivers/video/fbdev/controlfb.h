<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * controlfb_hw.h: Constants of all sorts क्रम controlfb
 *
 * Copyright (C) 1998 Daniel Jacobowitz <dan@debian.org>
 *
 * Based on an awful lot of code, including:
 *
 * control.c: Console support क्रम PowerMac "control" display adaptor.
 * Copyright (C) 1996 Paul Mackerras.
 *
 * The so far unpublished platinumfb.c
 * Copyright (C) 1998 Jon Howell
 */

/*
 * Structure of the रेजिस्टरs क्रम the RADACAL colormap device.
 */
काष्ठा cmap_regs अणु
	अचिन्हित अक्षर addr;	/* index क्रम both cmap and misc रेजिस्टरs */
	अक्षर pad1[15];
	अचिन्हित अक्षर crsr;	/* cursor palette */
	अक्षर pad2[15];
	अचिन्हित अक्षर dat;	/* RADACAL misc रेजिस्टर data */
	अक्षर pad3[15];
	अचिन्हित अक्षर lut;	/* cmap data */
	अक्षर pad4[15];
पूर्ण;

/*
 * Structure of the रेजिस्टरs क्रम the "control" display adaptor.
 */
#घोषणा PAD(x)	अक्षर x[12]

काष्ठा preg अणु			/* padded रेजिस्टर */
	अचिन्हित r;
	अक्षर pad[12];
पूर्ण;

काष्ठा control_regs अणु
	काष्ठा preg vcount;	/* vertical counter */
	/* Vertical parameters are in units of 1/2 scan line */
	काष्ठा preg vswin;	/* between vsblank and vssync */
	काष्ठा preg vsblank;	/* vert start blank */
	काष्ठा preg veblank;	/* vert end blank (display start) */
	काष्ठा preg vewin;	/* between vesync and veblank */
	काष्ठा preg vesync;	/* vert end sync */
	काष्ठा preg vssync;	/* vert start sync */
	काष्ठा preg vperiod;	/* vert period */
	काष्ठा preg piped;	/* pipe delay hardware cursor */
	/* Horizontal params are in units of 2 pixels */
	काष्ठा preg hperiod;	/* horiz period - 2 */
	काष्ठा preg hsblank;	/* horiz start blank */
	काष्ठा preg heblank;	/* horiz end blank */
	काष्ठा preg hesync;	/* horiz end sync */
	काष्ठा preg hssync;	/* horiz start sync */
	काष्ठा preg heq;	/* half horiz sync len */
	काष्ठा preg hlfln;	/* half horiz period */
	काष्ठा preg hserr;	/* horiz period - horiz sync len */
	काष्ठा preg cnttst;
	काष्ठा preg ctrl;	/* display control */
	काष्ठा preg start_addr;	/* start address: 5 lsbs zero */
	काष्ठा preg pitch;	/* addrs dअगरf between scan lines */
	काष्ठा preg mon_sense;	/* monitor sense bits */
	काष्ठा preg vram_attr;	/* enable vram banks */
	काष्ठा preg mode;
	काष्ठा preg rfrcnt;	/* refresh count */
	काष्ठा preg पूर्णांकr_ena;	/* पूर्णांकerrupt enable */
	काष्ठा preg पूर्णांकr_stat;	/* पूर्णांकerrupt status */
	काष्ठा preg res[5];
पूर्ण;

काष्ठा control_regपूर्णांकs अणु
	/* Vertical parameters are in units of 1/2 scan line */
	अचिन्हित vswin;	/* between vsblank and vssync */
	अचिन्हित vsblank;	/* vert start blank */
	अचिन्हित veblank;	/* vert end blank (display start) */
	अचिन्हित vewin;	/* between vesync and veblank */
	अचिन्हित vesync;	/* vert end sync */
	अचिन्हित vssync;	/* vert start sync */
	अचिन्हित vperiod;	/* vert period */
	अचिन्हित piped;		/* pipe delay hardware cursor */
	/* Horizontal params are in units of 2 pixels */
	/* Except, apparently, क्रम hres > 1024 (or == 1280?) */
	अचिन्हित hperiod;	/* horiz period - 2 */
	अचिन्हित hsblank;	/* horiz start blank */
	अचिन्हित heblank;	/* horiz end blank */
	अचिन्हित hesync;	/* horiz end sync */
	अचिन्हित hssync;	/* horiz start sync */
	अचिन्हित heq;		/* half horiz sync len */
	अचिन्हित hlfln;		/* half horiz period */
	अचिन्हित hserr;		/* horiz period - horiz sync len */
पूर्ण;
	
/*
 * Dot घड़ी rate is
 * 3.9064MHz * 2**घड़ी_params[2] * घड़ी_params[1] / घड़ी_params[0].
 */
काष्ठा control_regvals अणु
	अचिन्हित regs[16];		/* क्रम vswin .. hserr */
	अचिन्हित अक्षर mode;
	अचिन्हित अक्षर radacal_ctrl;
	अचिन्हित अक्षर घड़ी_params[3];
पूर्ण;

#घोषणा CTRLFB_OFF 16	/* position of pixel 0 in frame buffer */


/*
 * Best cmode supported by control
 */
काष्ठा max_cmodes अणु
	पूर्णांक m[2];	/* 0: 2MB vram, 1: 4MB vram */
पूर्ण;

/*
 * Video modes supported by macmodes.c
 */
अटल काष्ठा max_cmodes control_mac_modes[] = अणु
	अणुअणु-1,-1पूर्णपूर्ण,	/* 512x384, 60Hz पूर्णांकerlaced (NTSC) */
	अणुअणु-1,-1पूर्णपूर्ण,	/* 512x384, 60Hz */
	अणुअणु-1,-1पूर्णपूर्ण,	/* 640x480, 50Hz पूर्णांकerlaced (PAL) */
	अणुअणु-1,-1पूर्णपूर्ण,	/* 640x480, 60Hz पूर्णांकerlaced (NTSC) */
	अणुअणु 2, 2पूर्णपूर्ण,	/* 640x480, 60Hz (VGA) */
	अणुअणु 2, 2पूर्णपूर्ण,	/* 640x480, 67Hz */
	अणुअणु-1,-1पूर्णपूर्ण,	/* 640x870, 75Hz (portrait) */
	अणुअणु-1,-1पूर्णपूर्ण,	/* 768x576, 50Hz (PAL full frame) */
	अणुअणु 2, 2पूर्णपूर्ण,	/* 800x600, 56Hz */
	अणुअणु 2, 2पूर्णपूर्ण,	/* 800x600, 60Hz */
	अणुअणु 2, 2पूर्णपूर्ण,	/* 800x600, 72Hz */
	अणुअणु 2, 2पूर्णपूर्ण,	/* 800x600, 75Hz */
	अणुअणु 1, 2पूर्णपूर्ण,	/* 832x624, 75Hz */
	अणुअणु 1, 2पूर्णपूर्ण,	/* 1024x768, 60Hz */
	अणुअणु 1, 2पूर्णपूर्ण,	/* 1024x768, 70Hz (or 72Hz?) */
	अणुअणु 1, 2पूर्णपूर्ण,	/* 1024x768, 75Hz (VESA) */
	अणुअणु 1, 2पूर्णपूर्ण,	/* 1024x768, 75Hz */
	अणुअणु 1, 2पूर्णपूर्ण,	/* 1152x870, 75Hz */
	अणुअणु 0, 1पूर्णपूर्ण,	/* 1280x960, 75Hz */
	अणुअणु 0, 1पूर्णपूर्ण,	/* 1280x1024, 75Hz */
	अणुअणु 1, 2पूर्णपूर्ण,	/* 1152x768, 60Hz */
	अणुअणु 0, 1पूर्णपूर्ण,	/* 1600x1024, 60Hz */
पूर्ण;

