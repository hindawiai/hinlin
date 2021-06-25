<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/video/pvr2fb.c
 *
 * Frame buffer and fbcon support क्रम the NEC PowerVR2 found within the Sega
 * Dreamcast.
 *
 * Copyright (c) 2001 M. R. Brown <mrbrown@0xd6.org>
 * Copyright (c) 2001 - 2008  Paul Mundt <lethal@linux-sh.org>
 *
 * This driver is mostly based on the excellent amअगरb and vfb sources.  It uses
 * an odd scheme क्रम converting hardware values to/from framebuffer values,
 * here are some hacked-up क्रमmulas:
 *
 *  The Dreamcast has screen offsets from each side of its four borders and
 *  the start offsets of the display winकरोw.  I used these values to calculate
 *  'pseudo' values (think of them as placeholders) क्रम the fb video mode, so
 *  that when it came समय to convert these values back पूर्णांकo their hardware
 *  values, I could just add mode- specअगरic offsets to get the correct mode
 *  settings:
 *
 *      left_margin = diwstart_h - borderstart_h;
 *      right_margin = borderstop_h - (diwstart_h + xres);
 *      upper_margin = diwstart_v - borderstart_v;
 *      lower_margin = borderstop_v - (diwstart_h + yres);
 *
 *      hsync_len = borderstart_h + (hsync_total - borderstop_h);
 *      vsync_len = borderstart_v + (vsync_total - borderstop_v);
 *
 *  Then, when it's समय to convert back to hardware settings, the only
 *  स्थिरants are the borderstart_* offsets, all other values are derived from
 *  the fb video mode:
 *
 *      // PAL
 *      borderstart_h = 116;
 *      borderstart_v = 44;
 *      ...
 *      borderstop_h = borderstart_h + hsync_total - hsync_len;
 *      ...
 *      diwstart_v = borderstart_v - upper_margin;
 *
 *  However, in the current implementation, the borderstart values haven't had
 *  the benefit of being fully researched, so some modes may be broken.
 */

#अघोषित DEBUG

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#अगर_घोषित CONFIG_SH_DREAMCAST
#समावेश <यंत्र/machvec.h>
#समावेश <mach-dreamcast/mach/sysasic.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PVR2_DMA
#समावेश <linux/pagemap.h>
#समावेश <mach/dma.h>
#समावेश <यंत्र/dma.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_SH_STORE_QUEUES
#समावेश <linux/uaccess.h>
#समावेश <cpu/sq.h>
#पूर्ण_अगर

#अगर_अघोषित PCI_DEVICE_ID_NEC_NEON250
#  define PCI_DEVICE_ID_NEC_NEON250	0x0067
#पूर्ण_अगर

/* 2D video रेजिस्टरs */
#घोषणा DISP_BASE	par->mmio_base
#घोषणा DISP_BRDRCOLR (DISP_BASE + 0x40)
#घोषणा DISP_DIWMODE (DISP_BASE + 0x44)
#घोषणा DISP_DIWADDRL (DISP_BASE + 0x50)
#घोषणा DISP_DIWADDRS (DISP_BASE + 0x54)
#घोषणा DISP_DIWSIZE (DISP_BASE + 0x5c)
#घोषणा DISP_SYNCCONF (DISP_BASE + 0xd0)
#घोषणा DISP_BRDRHORZ (DISP_BASE + 0xd4)
#घोषणा DISP_SYNCSIZE (DISP_BASE + 0xd8)
#घोषणा DISP_BRDRVERT (DISP_BASE + 0xdc)
#घोषणा DISP_DIWCONF (DISP_BASE + 0xe8)
#घोषणा DISP_DIWHSTRT (DISP_BASE + 0xec)
#घोषणा DISP_DIWVSTRT (DISP_BASE + 0xf0)
#घोषणा DISP_PIXDEPTH (DISP_BASE + 0x108)

/* Pixel घड़ीs, one क्रम TV output, द्विगुनd क्रम VGA output */
#घोषणा TV_CLK 74239
#घोषणा VGA_CLK 37119

/* This is क्रम 60Hz - the VTOTAL is द्विगुनd क्रम पूर्णांकerlaced modes */
#घोषणा PAL_HTOTAL 863
#घोषणा PAL_VTOTAL 312
#घोषणा NTSC_HTOTAL 857
#घोषणा NTSC_VTOTAL 262

/* Supported cable types */
क्रमागत अणु CT_VGA, CT_NONE, CT_RGB, CT_COMPOSITE पूर्ण;

/* Supported video output types */
क्रमागत अणु VO_PAL, VO_NTSC, VO_VGA पूर्ण;

/* Supported palette types */
क्रमागत अणु PAL_ARGB1555, PAL_RGB565, PAL_ARGB4444, PAL_ARGB8888 पूर्ण;

काष्ठा pvr2_params अणु अचिन्हित पूर्णांक val; अक्षर *name; पूर्ण;
अटल काष्ठा pvr2_params cables[] = अणु
	अणु CT_VGA, "VGA" पूर्ण, अणु CT_RGB, "RGB" पूर्ण, अणु CT_COMPOSITE, "COMPOSITE" पूर्ण,
पूर्ण;

अटल काष्ठा pvr2_params outमाला_दो[] = अणु
	अणु VO_PAL, "PAL" पूर्ण, अणु VO_NTSC, "NTSC" पूर्ण, अणु VO_VGA, "VGA" पूर्ण,
पूर्ण;

/*
 * This describes the current video mode
 */

अटल काष्ठा pvr2fb_par अणु
	अचिन्हित पूर्णांक hsync_total;	/* Clocks/line */
	अचिन्हित पूर्णांक vsync_total;	/* Lines/field */
	अचिन्हित पूर्णांक borderstart_h;
	अचिन्हित पूर्णांक borderstop_h;
	अचिन्हित पूर्णांक borderstart_v;
	अचिन्हित पूर्णांक borderstop_v;
	अचिन्हित पूर्णांक diwstart_h;	/* Horizontal offset of the display field */
	अचिन्हित पूर्णांक diwstart_v;	/* Vertical offset of the display field, क्रम
				   पूर्णांकerlaced modes, this is the दीर्घ field */
	अचिन्हित दीर्घ disp_start;	/* Address of image within VRAM */
	अचिन्हित अक्षर is_पूर्णांकerlaced;	/* Is the display पूर्णांकerlaced? */
	अचिन्हित अक्षर is_द्विगुनscan;	/* Are scanlines output twice? (द्विगुनscan) */
	अचिन्हित अक्षर is_lowres;	/* Is horizontal pixel-करोubling enabled? */

	व्योम __iomem *mmio_base;	/* MMIO base */
	u32 palette[16];
पूर्ण *currentpar;

अटल काष्ठा fb_info *fb_info;

अटल काष्ठा fb_fix_screeninfo pvr2_fix = अणु
	.id =		"NEC PowerVR2",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_TRUECOLOR,
	.ypanstep =	1,
	.ywrapstep =	1,
	.accel =	FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo pvr2_var = अणु
	.xres =		640,
	.yres =		480,
	.xres_भव =	640,
	.yres_भव = 480,
	.bits_per_pixel	=16,
	.red =		अणु 11, 5, 0 पूर्ण,
	.green =	अणु  5, 6, 0 पूर्ण,
	.blue =		अणु  0, 5, 0 पूर्ण,
	.activate =	FB_ACTIVATE_NOW,
	.height =	-1,
	.width =	-1,
	.vmode =	FB_VMODE_NONINTERLACED,
पूर्ण;

अटल पूर्णांक cable_type = CT_VGA;
अटल पूर्णांक video_output = VO_VGA;

अटल पूर्णांक nopan = 0;
अटल पूर्णांक nowrap = 1;

/*
 * We करो all updating, blanking, etc. during the vertical retrace period
 */
अटल अचिन्हित पूर्णांक करो_vmode_full = 0;	/* Change the video mode */
अटल अचिन्हित पूर्णांक करो_vmode_pan = 0;	/* Update the video mode */
अटल लघु करो_blank = 0;		/* (Un)Blank the screen */

अटल अचिन्हित पूर्णांक is_blanked = 0;		/* Is the screen blanked? */

#अगर_घोषित CONFIG_SH_STORE_QUEUES
अटल अचिन्हित दीर्घ pvr2fb_map;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PVR2_DMA
अटल अचिन्हित पूर्णांक shdma = PVR2_CASCADE_CHAN;
अटल अचिन्हित पूर्णांक pvr2dma = ONCHIP_NR_DMA_CHANNELS;
#पूर्ण_अगर

अटल काष्ठा fb_videomode pvr2_modedb[] = अणु
    /*
     * Broadcast video modes (PAL and NTSC).  I'm unfamiliar with
     * PAL-M and PAL-N, but from what I've पढ़ो both modes parallel PAL and
     * NTSC, so it shouldn't be a problem (I hope).
     */

    अणु
	/* 640x480 @ 60Hz पूर्णांकerlaced (NTSC) */
	"ntsc_640x480i", 60, 640, 480, TV_CLK, 38, 33, 0, 18, 146, 26,
	FB_SYNC_BROADCAST, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
    पूर्ण, अणु
	/* 640x240 @ 60Hz (NTSC) */
	/* XXX: Broken! Don't use... */
	"ntsc_640x240", 60, 640, 240, TV_CLK, 38, 33, 0, 0, 146, 22,
	FB_SYNC_BROADCAST, FB_VMODE_YWRAP
    पूर्ण, अणु
	/* 640x480 @ 60hz (VGA) */
	"vga_640x480", 60, 640, 480, VGA_CLK, 38, 33, 0, 18, 146, 26,
	0, FB_VMODE_YWRAP
    पूर्ण,
पूर्ण;

#घोषणा NUM_TOTAL_MODES  ARRAY_SIZE(pvr2_modedb)

#घोषणा DEFMODE_NTSC	0
#घोषणा DEFMODE_PAL	0
#घोषणा DEFMODE_VGA	2

अटल पूर्णांक deभ_शेषe = DEFMODE_NTSC;
अटल अक्षर *mode_option = शून्य;

अटल अंतरभूत व्योम pvr2fb_set_pal_type(अचिन्हित पूर्णांक type)
अणु
	काष्ठा pvr2fb_par *par = (काष्ठा pvr2fb_par *)fb_info->par;

	fb_ग_लिखोl(type, par->mmio_base + 0x108);
पूर्ण

अटल अंतरभूत व्योम pvr2fb_set_pal_entry(काष्ठा pvr2fb_par *par,
					अचिन्हित पूर्णांक regno,
					अचिन्हित पूर्णांक val)
अणु
	fb_ग_लिखोl(val, par->mmio_base + 0x1000 + (4 * regno));
पूर्ण

अटल पूर्णांक pvr2fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	करो_blank = blank ? blank : -1;
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_line_length(पूर्णांक xres_भव, पूर्णांक bpp)
अणु
	वापस (अचिन्हित दीर्घ)((((xres_भव*bpp)+31)&~31) >> 3);
पूर्ण

अटल व्योम set_color_bitfields(काष्ठा fb_var_screeninfo *var)
अणु
	चयन (var->bits_per_pixel) अणु
	    हाल 16:        /* RGB 565 */
		pvr2fb_set_pal_type(PAL_RGB565);
		var->red.offset = 11;    var->red.length = 5;
		var->green.offset = 5;   var->green.length = 6;
		var->blue.offset = 0;    var->blue.length = 5;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	    हाल 24:        /* RGB 888 */
		var->red.offset = 16;    var->red.length = 8;
		var->green.offset = 8;   var->green.length = 8;
		var->blue.offset = 0;    var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		अवरोध;
	    हाल 32:        /* ARGB 8888 */
		pvr2fb_set_pal_type(PAL_ARGB8888);
		var->red.offset = 16;    var->red.length = 8;
		var->green.offset = 8;   var->green.length = 8;
		var->blue.offset = 0;    var->blue.length = 8;
		var->transp.offset = 24; var->transp.length = 8;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pvr2fb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			    अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
                            अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा pvr2fb_par *par = (काष्ठा pvr2fb_par *)info->par;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (regno > info->cmap.len)
		वापस 1;

	/*
	 * We only support the hardware palette क्रम 16 and 32bpp. It's also
	 * expected that the palette क्रमmat has been set by the समय we get
	 * here, so we करोn't waste समय setting it again.
	 */
	चयन (info->var.bits_per_pixel) अणु
	    हाल 16: /* RGB 565 */
		पंचांगp =  (red   & 0xf800)       |
		      ((green & 0xfc00) >> 5) |
		      ((blue  & 0xf800) >> 11);

		pvr2fb_set_pal_entry(par, regno, पंचांगp);
		अवरोध;
	    हाल 24: /* RGB 888 */
		red >>= 8; green >>= 8; blue >>= 8;
		पंचांगp = (red << 16) | (green << 8) | blue;
		अवरोध;
	    हाल 32: /* ARGB 8888 */
		red >>= 8; green >>= 8; blue >>= 8;
		पंचांगp = (transp << 24) | (red << 16) | (green << 8) | blue;

		pvr2fb_set_pal_entry(par, regno, पंचांगp);
		अवरोध;
	    शेष:
		pr_debug("Invalid bit depth %d?!?\n", info->var.bits_per_pixel);
		वापस 1;
	पूर्ण

	अगर (regno < 16)
		((u32*)(info->pseuकरो_palette))[regno] = पंचांगp;

	वापस 0;
पूर्ण

/*
 * Determine the cable type and initialize the cable output क्रमmat.  Don't करो
 * anything अगर the cable type has been overidden (via "cable:XX").
 */

#घोषणा PCTRA ((व्योम __iomem *)0xff80002c)
#घोषणा PDTRA ((व्योम __iomem *)0xff800030)
#घोषणा VOUTC ((व्योम __iomem *)0xa0702c00)

अटल पूर्णांक pvr2_init_cable(व्योम)
अणु
	अगर (cable_type < 0) अणु
		fb_ग_लिखोl((fb_पढ़ोl(PCTRA) & 0xfff0ffff) | 0x000a0000,
	                  PCTRA);
		cable_type = (fb_पढ़ोw(PDTRA) >> 8) & 3;
	पूर्ण

	/* Now select the output क्रमmat (either composite or other) */
	/* XXX: Save the previous val first, as this reg is also AICA
	  related */
	अगर (cable_type == CT_COMPOSITE)
		fb_ग_लिखोl(3 << 8, VOUTC);
	अन्यथा अगर (cable_type == CT_RGB)
		fb_ग_लिखोl(1 << 9, VOUTC);
	अन्यथा
		fb_ग_लिखोl(0, VOUTC);

	वापस cable_type;
पूर्ण

अटल पूर्णांक pvr2fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा pvr2fb_par *par = (काष्ठा pvr2fb_par *)info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	अचिन्हित दीर्घ line_length;
	अचिन्हित पूर्णांक vtotal;

	/*
	 * XXX: It's possible that a user could use a VGA box, change the cable
	 * type in hardware (i.e. चयन from VGA<->composite), then change
	 * modes (i.e. चयनing to another VT).  If that happens we should
	 * स्वतःmagically change the output क्रमmat to cope, but currently I
	 * करोn't have a VGA box to make sure this works properly.
	 */
	cable_type = pvr2_init_cable();
	अगर (cable_type == CT_VGA && video_output != VO_VGA)
		video_output = VO_VGA;

	var->vmode &= FB_VMODE_MASK;
	अगर (var->vmode & FB_VMODE_INTERLACED && video_output != VO_VGA)
		par->is_पूर्णांकerlaced = 1;
	/*
	 * XXX: Need to be more creative with this (i.e. allow द्विगुनcan क्रम
	 * PAL/NTSC output).
	 */
	अगर (var->vmode & FB_VMODE_DOUBLE && video_output == VO_VGA)
		par->is_द्विगुनscan = 1;

	par->hsync_total = var->left_margin + var->xres + var->right_margin +
	                   var->hsync_len;
	par->vsync_total = var->upper_margin + var->yres + var->lower_margin +
	                   var->vsync_len;

	अगर (var->sync & FB_SYNC_BROADCAST) अणु
		vtotal = par->vsync_total;
		अगर (par->is_पूर्णांकerlaced)
			vtotal /= 2;
		अगर (vtotal > (PAL_VTOTAL + NTSC_VTOTAL)/2) अणु
			/* XXX: Check क्रम start values here... */
			/* XXX: Check hardware क्रम PAL-compatibility */
			par->borderstart_h = 116;
			par->borderstart_v = 44;
		पूर्ण अन्यथा अणु
			/* NTSC video output */
			par->borderstart_h = 126;
			par->borderstart_v = 18;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* VGA mode */
		/* XXX: What अन्यथा needs to be checked? */
		/*
		 * XXX: We have a little मुक्तकरोm in VGA modes, what ranges
		 * should be here (i.e. hsync/vsync totals, etc.)?
		 */
		par->borderstart_h = 126;
		par->borderstart_v = 40;
	पूर्ण

	/* Calculate the reमुख्यding offsets */
	par->diwstart_h = par->borderstart_h + var->left_margin;
	par->diwstart_v = par->borderstart_v + var->upper_margin;
	par->borderstop_h = par->diwstart_h + var->xres +
			    var->right_margin;
	par->borderstop_v = par->diwstart_v + var->yres +
			    var->lower_margin;

	अगर (!par->is_पूर्णांकerlaced)
		par->borderstop_v /= 2;
	अगर (info->var.xres < 640)
		par->is_lowres = 1;

	line_length = get_line_length(var->xres_भव, var->bits_per_pixel);
	par->disp_start = info->fix.smem_start + (line_length * var->yoffset) * line_length;
	info->fix.line_length = line_length;
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा pvr2fb_par *par = (काष्ठा pvr2fb_par *)info->par;
	अचिन्हित पूर्णांक vtotal, hsync_total;
	अचिन्हित दीर्घ line_length;

	अगर (var->pixघड़ी != TV_CLK && var->pixघड़ी != VGA_CLK) अणु
		pr_debug("Invalid pixclock value %d\n", var->pixघड़ी);
		वापस -EINVAL;
	पूर्ण

	अगर (var->xres < 320)
		var->xres = 320;
	अगर (var->yres < 240)
		var->yres = 240;
	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;
	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;

	अगर (var->bits_per_pixel <= 16)
		var->bits_per_pixel = 16;
	अन्यथा अगर (var->bits_per_pixel <= 24)
		var->bits_per_pixel = 24;
	अन्यथा अगर (var->bits_per_pixel <= 32)
		var->bits_per_pixel = 32;

	set_color_bitfields(var);

	अगर (var->vmode & FB_VMODE_YWRAP) अणु
		अगर (var->xoffset || var->yoffset >= var->yres_भव) अणु
			var->xoffset = var->yoffset = 0;
		पूर्ण अन्यथा अणु
			अगर (var->xoffset > var->xres_भव - var->xres ||
			    var->yoffset > var->yres_भव - var->yres)
				var->xoffset = var->yoffset = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		var->xoffset = var->yoffset = 0;
	पूर्ण

	/*
	 * XXX: Need to be more creative with this (i.e. allow द्विगुनcan क्रम
	 * PAL/NTSC output).
	 */
	अगर (var->yres < 480 && video_output == VO_VGA)
		var->vmode |= FB_VMODE_DOUBLE;

	अगर (video_output != VO_VGA) अणु
		var->sync |= FB_SYNC_BROADCAST;
		var->vmode |= FB_VMODE_INTERLACED;
	पूर्ण अन्यथा अणु
		var->sync &= ~FB_SYNC_BROADCAST;
		var->vmode &= ~FB_VMODE_INTERLACED;
		var->vmode |= FB_VMODE_NONINTERLACED;
	पूर्ण

	अगर ((var->activate & FB_ACTIVATE_MASK) != FB_ACTIVATE_TEST) अणु
		var->right_margin = par->borderstop_h -
				   (par->diwstart_h + var->xres);
		var->left_margin  = par->diwstart_h - par->borderstart_h;
		var->hsync_len    = par->borderstart_h +
		                   (par->hsync_total - par->borderstop_h);

		var->upper_margin = par->diwstart_v - par->borderstart_v;
		var->lower_margin = par->borderstop_v -
				   (par->diwstart_v + var->yres);
		var->vsync_len    = par->borderstop_v +
				   (par->vsync_total - par->borderstop_v);
	पूर्ण

	hsync_total = var->left_margin + var->xres + var->right_margin +
		      var->hsync_len;
	vtotal = var->upper_margin + var->yres + var->lower_margin +
		 var->vsync_len;

	अगर (var->sync & FB_SYNC_BROADCAST) अणु
		अगर (var->vmode & FB_VMODE_INTERLACED)
			vtotal /= 2;
		अगर (vtotal > (PAL_VTOTAL + NTSC_VTOTAL)/2) अणु
			/* PAL video output */
			/* XXX: Should be using a range here ... ? */
			अगर (hsync_total != PAL_HTOTAL) अणु
				pr_debug("invalid hsync total for PAL\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* NTSC video output */
			अगर (hsync_total != NTSC_HTOTAL) अणु
				pr_debug("invalid hsync total for NTSC\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Check memory sizes */
	line_length = get_line_length(var->xres_भव, var->bits_per_pixel);
	अगर (line_length * var->yres_भव > info->fix.smem_len)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम pvr2_update_display(काष्ठा fb_info *info)
अणु
	काष्ठा pvr2fb_par *par = (काष्ठा pvr2fb_par *) info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;

	/* Update the start address of the display image */
	fb_ग_लिखोl(par->disp_start, DISP_DIWADDRL);
	fb_ग_लिखोl(par->disp_start +
		  get_line_length(var->xoffset+var->xres, var->bits_per_pixel),
	          DISP_DIWADDRS);
पूर्ण

/*
 * Initialize the video mode.  Currently, the 16bpp and 24bpp modes aren't
 * very stable.  It's probably due to the fact that a lot of the 2D video
 * रेजिस्टरs are still unकरोcumented.
 */

अटल व्योम pvr2_init_display(काष्ठा fb_info *info)
अणु
	काष्ठा pvr2fb_par *par = (काष्ठा pvr2fb_par *) info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	अचिन्हित पूर्णांक diw_height, diw_width, diw_modulo = 1;
	अचिन्हित पूर्णांक bytesperpixel = var->bits_per_pixel >> 3;

	/* hsync and vsync totals */
	fb_ग_लिखोl((par->vsync_total << 16) | par->hsync_total, DISP_SYNCSIZE);

	/* column height, modulo, row width */
	/* since we're "panning" within vram, we need to offset things based
	 * on the offset from the भव x start to our real gfx. */
	अगर (video_output != VO_VGA && par->is_पूर्णांकerlaced)
		diw_modulo += info->fix.line_length / 4;
	diw_height = (par->is_पूर्णांकerlaced ? var->yres / 2 : var->yres);
	diw_width = get_line_length(var->xres, var->bits_per_pixel) / 4;
	fb_ग_लिखोl((diw_modulo << 20) | (--diw_height << 10) | --diw_width,
	          DISP_DIWSIZE);

	/* display address, दीर्घ and लघु fields */
	fb_ग_लिखोl(par->disp_start, DISP_DIWADDRL);
	fb_ग_लिखोl(par->disp_start +
	          get_line_length(var->xoffset+var->xres, var->bits_per_pixel),
	          DISP_DIWADDRS);

	/* border horizontal, border vertical, border color */
	fb_ग_लिखोl((par->borderstart_h << 16) | par->borderstop_h, DISP_BRDRHORZ);
	fb_ग_लिखोl((par->borderstart_v << 16) | par->borderstop_v, DISP_BRDRVERT);
	fb_ग_लिखोl(0, DISP_BRDRCOLR);

	/* display winकरोw start position */
	fb_ग_लिखोl(par->diwstart_h, DISP_DIWHSTRT);
	fb_ग_लिखोl((par->diwstart_v << 16) | par->diwstart_v, DISP_DIWVSTRT);

	/* misc. settings */
	fb_ग_लिखोl((0x16 << 16) | par->is_lowres, DISP_DIWCONF);

	/* घड़ी द्विगुनr (क्रम VGA), scan द्विगुनr, display enable */
	fb_ग_लिखोl(((video_output == VO_VGA) << 23) |
	          (par->is_द्विगुनscan << 1) | 1, DISP_DIWMODE);

	/* bits per pixel */
	fb_ग_लिखोl(fb_पढ़ोl(DISP_DIWMODE) | (--bytesperpixel << 2), DISP_DIWMODE);
	fb_ग_लिखोl(bytesperpixel << 2, DISP_PIXDEPTH);

	/* video enable, color sync, पूर्णांकerlace,
	 * hsync and vsync polarity (currently unused) */
	fb_ग_लिखोl(0x100 | ((par->is_पूर्णांकerlaced /*|4*/) << 4), DISP_SYNCCONF);
पूर्ण

/* Simulate blanking by making the border cover the entire screen */

#घोषणा BLANK_BIT (1<<3)

अटल व्योम pvr2_करो_blank(व्योम)
अणु
	काष्ठा pvr2fb_par *par = currentpar;
	अचिन्हित दीर्घ diwconf;

	diwconf = fb_पढ़ोl(DISP_DIWCONF);
	अगर (करो_blank > 0)
		fb_ग_लिखोl(diwconf | BLANK_BIT, DISP_DIWCONF);
	अन्यथा
		fb_ग_लिखोl(diwconf & ~BLANK_BIT, DISP_DIWCONF);

	is_blanked = करो_blank > 0 ? करो_blank : 0;
पूर्ण

अटल irqवापस_t __maybe_unused pvr2fb_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fb_info *info = dev_id;

	अगर (करो_vmode_pan || करो_vmode_full)
		pvr2_update_display(info);
	अगर (करो_vmode_full)
		pvr2_init_display(info);
	अगर (करो_vmode_pan)
		करो_vmode_pan = 0;
	अगर (करो_vmode_full)
		करो_vmode_full = 0;
	अगर (करो_blank) अणु
		pvr2_करो_blank();
		करो_blank = 0;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_PVR2_DMA
अटल sमाप_प्रकार pvr2fb_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ dst, start, end, len;
	अचिन्हित पूर्णांक nr_pages;
	काष्ठा page **pages;
	पूर्णांक ret, i;

	nr_pages = (count + PAGE_SIZE - 1) >> PAGE_SHIFT;

	pages = kदो_स्मृति_array(nr_pages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages)
		वापस -ENOMEM;

	ret = pin_user_pages_fast((अचिन्हित दीर्घ)buf, nr_pages, FOLL_WRITE, pages);
	अगर (ret < nr_pages) अणु
		अगर (ret < 0) अणु
			/*
			 *  Clamp the अचिन्हित nr_pages to zero so that the
			 *  error handling works. And leave ret at whatever
			 *  -त्रुटि_सं value was वापसed from GUP.
			 */
			nr_pages = 0;
		पूर्ण अन्यथा अणु
			nr_pages = ret;
			/*
			 * Use -EINVAL to represent a mildly desperate guess at
			 * why we got fewer pages (maybe even zero pages) than
			 * requested.
			 */
			ret = -EINVAL;
		पूर्ण
		जाओ out_unmap;
	पूर्ण

	dma_configure_channel(shdma, 0x12c1);

	dst   = (अचिन्हित दीर्घ)fb_info->screen_base + *ppos;
	start = (अचिन्हित दीर्घ)page_address(pages[0]);
	end   = (अचिन्हित दीर्घ)page_address(pages[nr_pages]);
	len   = nr_pages << PAGE_SHIFT;

	/* Half-assed contig check */
	अगर (start + len == end) अणु
		/* As we करो this in one shot, it's either all or nothing.. */
		अगर ((*ppos + len) > fb_info->fix.smem_len) अणु
			ret = -ENOSPC;
			जाओ out_unmap;
		पूर्ण

		dma_ग_लिखो(shdma, start, 0, len);
		dma_ग_लिखो(pvr2dma, 0, dst, len);
		dma_रुको_क्रम_completion(pvr2dma);

		जाओ out;
	पूर्ण

	/* Not contiguous, ग_लिखोout per-page instead.. */
	क्रम (i = 0; i < nr_pages; i++, dst += PAGE_SIZE) अणु
		अगर ((*ppos + (i << PAGE_SHIFT)) > fb_info->fix.smem_len) अणु
			ret = -ENOSPC;
			जाओ out_unmap;
		पूर्ण

		dma_ग_लिखो_page(shdma, (अचिन्हित दीर्घ)page_address(pages[i]), 0);
		dma_ग_लिखो_page(pvr2dma, 0, dst);
		dma_रुको_क्रम_completion(pvr2dma);
	पूर्ण

out:
	*ppos += count;
	ret = count;

out_unmap:
	unpin_user_pages(pages, nr_pages);
	kमुक्त(pages);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PVR2_DMA */

अटल स्थिर काष्ठा fb_ops pvr2fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_setcolreg	= pvr2fb_setcolreg,
	.fb_blank	= pvr2fb_blank,
	.fb_check_var	= pvr2fb_check_var,
	.fb_set_par	= pvr2fb_set_par,
#अगर_घोषित CONFIG_PVR2_DMA
	.fb_ग_लिखो	= pvr2fb_ग_लिखो,
#पूर्ण_अगर
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

#अगर_अघोषित MODULE
अटल पूर्णांक pvr2_get_param_val(स्थिर काष्ठा pvr2_params *p, स्थिर अक्षर *s,
			      पूर्णांक size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (!strnहालcmp(p[i].name, s, म_माप(s)))
			वापस p[i].val;
	पूर्ण
	वापस -1;
पूर्ण
#पूर्ण_अगर

अटल अक्षर *pvr2_get_param_name(स्थिर काष्ठा pvr2_params *p, पूर्णांक val,
			  पूर्णांक size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (p[i].val == val)
			वापस p[i].name;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * pvr2fb_common_init
 *
 * Common init code क्रम the PVR2 chips.
 *
 * This mostly takes care of the common aspects of the fb setup and
 * registration. It's expected that the board-specअगरic init code has
 * alपढ़ोy setup pvr2_fix with something meaningful at this poपूर्णांक.
 *
 * Device info reporting is also करोne here, as well as picking a sane
 * शेष from the modedb. For board-specअगरic modelines, simply define
 * a per-board modedb.
 *
 * Also worth noting is that the cable and video output types are likely
 * always going to be VGA क्रम the PCI-based PVR2 boards, but we leave this
 * in क्रम flexibility anyways. Who knows, maybe someone has tv-out on a
 * PCI-based version of these things ;-)
 */
अटल पूर्णांक __maybe_unused pvr2fb_common_init(व्योम)
अणु
	काष्ठा pvr2fb_par *par = currentpar;
	अचिन्हित दीर्घ modememused, rev;

	fb_info->screen_base = ioremap(pvr2_fix.smem_start,
					       pvr2_fix.smem_len);

	अगर (!fb_info->screen_base) अणु
		prपूर्णांकk(KERN_ERR "pvr2fb: Failed to remap smem space\n");
		जाओ out_err;
	पूर्ण

	par->mmio_base = ioremap(pvr2_fix.mmio_start,
					 pvr2_fix.mmio_len);
	अगर (!par->mmio_base) अणु
		prपूर्णांकk(KERN_ERR "pvr2fb: Failed to remap mmio space\n");
		जाओ out_err;
	पूर्ण

	fb_स_रखो(fb_info->screen_base, 0, pvr2_fix.smem_len);

	pvr2_fix.ypanstep	= nopan  ? 0 : 1;
	pvr2_fix.ywrapstep	= nowrap ? 0 : 1;

	fb_info->fbops		= &pvr2fb_ops;
	fb_info->fix		= pvr2_fix;
	fb_info->par		= currentpar;
	fb_info->pseuकरो_palette	= currentpar->palette;
	fb_info->flags		= FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;

	अगर (video_output == VO_VGA)
		deभ_शेषe = DEFMODE_VGA;

	अगर (!mode_option)
		mode_option = "640x480@60";

	अगर (!fb_find_mode(&fb_info->var, fb_info, mode_option, pvr2_modedb,
	                  NUM_TOTAL_MODES, &pvr2_modedb[deभ_शेषe], 16))
		fb_info->var = pvr2_var;

	fb_alloc_cmap(&fb_info->cmap, 256, 0);

	अगर (रेजिस्टर_framebuffer(fb_info) < 0)
		जाओ out_err;
	/*Must ग_लिखो PIXDEPTH to रेजिस्टर beक्रमe anything is displayed - so क्रमce init */
	pvr2_init_display(fb_info);

	modememused = get_line_length(fb_info->var.xres_भव,
				      fb_info->var.bits_per_pixel);
	modememused *= fb_info->var.yres_भव;

	rev = fb_पढ़ोl(par->mmio_base + 0x04);

	fb_info(fb_info, "%s (rev %ld.%ld) frame buffer device, using %ldk/%ldk of video memory\n",
		fb_info->fix.id, (rev >> 4) & 0x0f, rev & 0x0f,
		modememused >> 10,
		(अचिन्हित दीर्घ)(fb_info->fix.smem_len >> 10));
	fb_info(fb_info, "Mode %dx%d-%d pitch = %ld cable: %s video output: %s\n",
		fb_info->var.xres, fb_info->var.yres,
		fb_info->var.bits_per_pixel,
		get_line_length(fb_info->var.xres, fb_info->var.bits_per_pixel),
		pvr2_get_param_name(cables, cable_type, 3),
		pvr2_get_param_name(outमाला_दो, video_output, 3));

#अगर_घोषित CONFIG_SH_STORE_QUEUES
	fb_notice(fb_info, "registering with SQ API\n");

	pvr2fb_map = sq_remap(fb_info->fix.smem_start, fb_info->fix.smem_len,
			      fb_info->fix.id, PAGE_SHARED);

	fb_notice(fb_info, "Mapped video memory to SQ addr 0x%lx\n",
		  pvr2fb_map);
#पूर्ण_अगर

	वापस 0;

out_err:
	अगर (fb_info->screen_base)
		iounmap(fb_info->screen_base);
	अगर (par->mmio_base)
		iounmap(par->mmio_base);

	वापस -ENXIO;
पूर्ण

#अगर_घोषित CONFIG_SH_DREAMCAST
अटल पूर्णांक __init pvr2fb_dc_init(व्योम)
अणु
	अगर (!mach_is_dreamcast())
		वापस -ENXIO;

	/* Make a guess at the monitor based on the attached cable */
	अगर (pvr2_init_cable() == CT_VGA) अणु
		fb_info->monspecs.hfmin = 30000;
		fb_info->monspecs.hfmax = 70000;
		fb_info->monspecs.vfmin = 60;
		fb_info->monspecs.vfmax = 60;
	पूर्ण अन्यथा अणु
		/* Not VGA, using a TV (taken from acornfb) */
		fb_info->monspecs.hfmin = 15469;
		fb_info->monspecs.hfmax = 15781;
		fb_info->monspecs.vfmin = 49;
		fb_info->monspecs.vfmax = 51;
	पूर्ण

	/*
	 * XXX: This needs to pull शेष video output via BIOS or other means
	 */
	अगर (video_output < 0) अणु
		अगर (cable_type == CT_VGA) अणु
			video_output = VO_VGA;
		पूर्ण अन्यथा अणु
			video_output = VO_NTSC;
		पूर्ण
	पूर्ण

	/*
	 * Nothing exciting about the DC PVR2 .. only a measly 8MiB.
	 */
	pvr2_fix.smem_start	= 0xa5000000;	/* RAM starts here */
	pvr2_fix.smem_len	= 8 << 20;

	pvr2_fix.mmio_start	= 0xa05f8000;	/* रेजिस्टरs start here */
	pvr2_fix.mmio_len	= 0x2000;

	अगर (request_irq(HW_EVENT_VSYNC, pvr2fb_पूर्णांकerrupt, IRQF_SHARED,
	                "pvr2 VBL handler", fb_info)) अणु
		वापस -EBUSY;
	पूर्ण

#अगर_घोषित CONFIG_PVR2_DMA
	अगर (request_dma(pvr2dma, "pvr2") != 0) अणु
		मुक्त_irq(HW_EVENT_VSYNC, fb_info);
		वापस -EBUSY;
	पूर्ण
#पूर्ण_अगर

	वापस pvr2fb_common_init();
पूर्ण

अटल व्योम pvr2fb_dc_निकास(व्योम)
अणु
	अगर (fb_info->screen_base) अणु
		iounmap(fb_info->screen_base);
		fb_info->screen_base = शून्य;
	पूर्ण
	अगर (currentpar->mmio_base) अणु
		iounmap(currentpar->mmio_base);
		currentpar->mmio_base = शून्य;
	पूर्ण

	मुक्त_irq(HW_EVENT_VSYNC, fb_info);
#अगर_घोषित CONFIG_PVR2_DMA
	मुक्त_dma(pvr2dma);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर /* CONFIG_SH_DREAMCAST */

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक pvr2fb_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "pvr2fb: PCI enable failed\n");
		वापस ret;
	पूर्ण

	ret = pci_request_regions(pdev, "pvr2fb");
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "pvr2fb: PCI request regions failed\n");
		वापस ret;
	पूर्ण

	/*
	 * Slightly more exciting than the DC PVR2 .. 16MiB!
	 */
	pvr2_fix.smem_start	= pci_resource_start(pdev, 0);
	pvr2_fix.smem_len	= pci_resource_len(pdev, 0);

	pvr2_fix.mmio_start	= pci_resource_start(pdev, 1);
	pvr2_fix.mmio_len	= pci_resource_len(pdev, 1);

	fb_info->device		= &pdev->dev;

	वापस pvr2fb_common_init();
पूर्ण

अटल व्योम pvr2fb_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	अगर (fb_info->screen_base) अणु
		iounmap(fb_info->screen_base);
		fb_info->screen_base = शून्य;
	पूर्ण
	अगर (currentpar->mmio_base) अणु
		iounmap(currentpar->mmio_base);
		currentpar->mmio_base = शून्य;
	पूर्ण

	pci_release_regions(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pvr2fb_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_NEC, PCI_DEVICE_ID_NEC_NEON250,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, pvr2fb_pci_tbl);

अटल काष्ठा pci_driver pvr2fb_pci_driver = अणु
	.name		= "pvr2fb",
	.id_table	= pvr2fb_pci_tbl,
	.probe		= pvr2fb_pci_probe,
	.हटाओ		= pvr2fb_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init pvr2fb_pci_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&pvr2fb_pci_driver);
पूर्ण

अटल व्योम pvr2fb_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pvr2fb_pci_driver);
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

/*
 * Parse command arguments.  Supported arguments are:
 *    inverse                             Use inverse color maps
 *    cable:composite|rgb|vga             Override the video cable type
 *    output:NTSC|PAL|VGA                 Override the video output क्रमmat
 *
 *    <xres>x<yres>[-<bpp>][@<refresh>]   or,
 *    <name>[-<bpp>][@<refresh>]          Startup using this video mode
 */

#अगर_अघोषित MODULE
अटल पूर्णांक __init pvr2fb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;
	अक्षर cable_arg[80];
	अक्षर output_arg[80];

	अगर (!options || !*options)
		वापस 0;

	cable_arg[0] = output_arg[0] = 0;

	जबतक ((this_opt = strsep(&options, ","))) अणु
		अगर (!*this_opt)
			जारी;
		अगर (!म_भेद(this_opt, "inverse")) अणु
			fb_invert_cmaps();
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "cable:", 6)) अणु
			म_नकल(cable_arg, this_opt + 6);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "output:", 7)) अणु
			म_नकल(output_arg, this_opt + 7);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "nopan", 5)) अणु
			nopan = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "nowrap", 6)) अणु
			nowrap = 1;
		पूर्ण अन्यथा अणु
			mode_option = this_opt;
		पूर्ण
	पूर्ण

	अगर (*cable_arg)
		cable_type = pvr2_get_param_val(cables, cable_arg, 3);
	अगर (*output_arg)
		video_output = pvr2_get_param_val(outमाला_दो, output_arg, 3);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pvr2_board अणु
	पूर्णांक (*init)(व्योम);
	व्योम (*निकास)(व्योम);
	अक्षर name[16];
पूर्ण board_driver[] __refdata = अणु
#अगर_घोषित CONFIG_SH_DREAMCAST
	अणु pvr2fb_dc_init, pvr2fb_dc_निकास, "Sega DC PVR2" पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI
	अणु pvr2fb_pci_init, pvr2fb_pci_निकास, "PCI PVR2" पूर्ण,
#पूर्ण_अगर
	अणु 0, पूर्ण,
पूर्ण;

अटल पूर्णांक __init pvr2fb_init(व्योम)
अणु
	पूर्णांक i, ret = -ENODEV;

#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("pvr2fb", &option))
		वापस -ENODEV;
	pvr2fb_setup(option);
#पूर्ण_अगर

	fb_info = framebuffer_alloc(माप(काष्ठा pvr2fb_par), शून्य);
	अगर (!fb_info)
		वापस -ENOMEM;

	currentpar = fb_info->par;

	क्रम (i = 0; i < ARRAY_SIZE(board_driver); i++) अणु
		काष्ठा pvr2_board *pvr_board = board_driver + i;

		अगर (!pvr_board->init)
			जारी;

		ret = pvr_board->init();

		अगर (ret != 0) अणु
			prपूर्णांकk(KERN_ERR "pvr2fb: Failed init of %s device\n",
				pvr_board->name);
			framebuffer_release(fb_info);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास pvr2fb_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(board_driver); i++) अणु
		काष्ठा pvr2_board *pvr_board = board_driver + i;

		अगर (pvr_board->निकास)
			pvr_board->निकास();
	पूर्ण

#अगर_घोषित CONFIG_SH_STORE_QUEUES
	sq_unmap(pvr2fb_map);
#पूर्ण_अगर

	unरेजिस्टर_framebuffer(fb_info);
	framebuffer_release(fb_info);
पूर्ण

module_init(pvr2fb_init);
module_निकास(pvr2fb_निकास);

MODULE_AUTHOR("Paul Mundt <lethal@linux-sh.org>, M. R. Brown <mrbrown@0xd6.org>");
MODULE_DESCRIPTION("Framebuffer driver for NEC PowerVR 2 based graphics boards");
MODULE_LICENSE("GPL");
