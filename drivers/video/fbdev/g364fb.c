<शैली गुरु>
/* $Id: g364fb.c,v 1.3 1998/08/28 22:43:00 tsbogend Exp $
 *
 * linux/drivers/video/g364fb.c -- Mips Magnum frame buffer device
 *
 * (C) 1998 Thomas Bogenकरोerfer
 *
 *  This driver is based on tgafb.c
 *
 *	Copyright (C) 1997 Geert Uytterhoeven 
 *	Copyright (C) 1995  Jay Estabrook
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/jazz.h>

/* 
 * Various defines क्रम the G364
 */
#घोषणा G364_MEM_BASE   0xe4400000
#घोषणा G364_PORT_BASE  0xe4000000
#घोषणा ID_REG 		0xe4000000	/* Read only */
#घोषणा BOOT_REG 	0xe4080000
#घोषणा TIMING_REG 	0xe4080108	/* to 0x080170 - DON'T TOUCH! */
#घोषणा DISPLAY_REG 	0xe4080118
#घोषणा VDISPLAY_REG 	0xe4080150
#घोषणा MASK_REG 	0xe4080200
#घोषणा CTLA_REG 	0xe4080300
#घोषणा CURS_TOGGLE 	0x800000
#घोषणा BIT_PER_PIX	0x700000	/* bits 22 to 20 of Control A */
#घोषणा DELAY_SAMPLE    0x080000
#घोषणा PORT_INTER	0x040000
#घोषणा PIX_PIPE_DEL	0x030000	/* bits 17 and 16 of Control A */
#घोषणा PIX_PIPE_DEL2	0x008000	/* same as above - करोn't ask me why */
#घोषणा TR_CYCLE_TOG	0x004000
#घोषणा VRAM_ADR_INC	0x003000	/* bits 13 and 12 of Control A */
#घोषणा BLANK_OFF	0x000800
#घोषणा FORCE_BLANK	0x000400
#घोषणा BLK_FUN_SWTCH	0x000200
#घोषणा BLANK_IO	0x000100
#घोषणा BLANK_LEVEL	0x000080
#घोषणा A_VID_FORM	0x000040
#घोषणा D_SYNC_FORM	0x000020
#घोषणा FRAME_FLY_PAT	0x000010
#घोषणा OP_MODE		0x000008
#घोषणा INTL_STAND	0x000004
#घोषणा SCRN_FORM	0x000002
#घोषणा ENABLE_VTG	0x000001
#घोषणा TOP_REG 	0xe4080400
#घोषणा CURS_PAL_REG 	0xe4080508	/* to 0x080518 */
#घोषणा CHKSUM_REG 	0xe4080600	/* to 0x080610 - unused */
#घोषणा CURS_POS_REG 	0xe4080638
#घोषणा CLR_PAL_REG 	0xe4080800	/* to 0x080ff8 */
#घोषणा CURS_PAT_REG 	0xe4081000	/* to 0x081ff8 */
#घोषणा MON_ID_REG 	0xe4100000	/* unused */
#घोषणा RESET_REG 	0xe4180000	/* Write only */

अटल काष्ठा fb_info fb_info;

अटल काष्ठा fb_fix_screeninfo fb_fix __initdata = अणु
	.id 		= "G364 8plane",
	.smem_start 	= 0x40000000,	/* physical address */
	.type 		= FB_TYPE_PACKED_PIXELS,
	.visual 	= FB_VISUAL_PSEUDOCOLOR,
	.ypanstep 	= 1,
	.accel 		= FB_ACCEL_NONE,
पूर्ण;

अटल काष्ठा fb_var_screeninfo fb_var __initdata = अणु
	.bits_per_pixel = 8,
	.red 		= अणु 0, 8, 0 पूर्ण,
      	.green 		= अणु 0, 8, 0 पूर्ण,
      	.blue		= अणु 0, 8, 0 पूर्ण,
      	.activate	= FB_ACTIVATE_NOW,
      	.height		= -1,
      	.width		= -1,
      	.pixघड़ी	= 39722,
      	.left_margin	= 40,
      	.right_margin	= 24,
      	.upper_margin	= 32,
      	.lower_margin	= 11,
      	.hsync_len 	= 96,
      	.vsync_len 	= 2,
      	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

/*
 *  Interface used by the world
 */
पूर्णांक g364fb_init(व्योम);

अटल पूर्णांक g364fb_pan_display(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info);
अटल पूर्णांक g364fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green,
			    u_पूर्णांक blue, u_पूर्णांक transp,
			    काष्ठा fb_info *info);
अटल पूर्णांक g364fb_blank(पूर्णांक blank, काष्ठा fb_info *info);

अटल स्थिर काष्ठा fb_ops g364fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_setcolreg	= g364fb_setcolreg,
	.fb_pan_display	= g364fb_pan_display,
	.fb_blank	= g364fb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

/*
 *  Pan or Wrap the Display
 *
 *  This call looks only at xoffset, yoffset and the FB_VMODE_YWRAP flag
 */
अटल पूर्णांक g364fb_pan_display(काष्ठा fb_var_screeninfo *var, 
			      काष्ठा fb_info *info)
अणु
	अगर (var->xoffset ||
	    var->yoffset + info->var.yres > info->var.yres_भव)
		वापस -EINVAL;

	*(अचिन्हित पूर्णांक *) TOP_REG = var->yoffset * info->var.xres;
	वापस 0;
पूर्ण

/*
 *  Blank the display.
 */
अटल पूर्णांक g364fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	अगर (blank)
		*(अचिन्हित पूर्णांक *) CTLA_REG |= FORCE_BLANK;
	अन्यथा
		*(अचिन्हित पूर्णांक *) CTLA_REG &= ~FORCE_BLANK;
	वापस 0;
पूर्ण

/*
 *  Set a single color रेजिस्टर. Return != 0 क्रम invalid regno.
 */
अटल पूर्णांक g364fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green,
			    u_पूर्णांक blue, u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	अस्थिर अचिन्हित पूर्णांक *ptr = (अस्थिर अचिन्हित पूर्णांक *) CLR_PAL_REG;

	अगर (regno > 255)
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	ptr[regno << 1] = (red << 16) | (green << 8) | blue;

	वापस 0;
पूर्ण

/*
 *  Initialisation
 */
पूर्णांक __init g364fb_init(व्योम)
अणु
	अस्थिर अचिन्हित पूर्णांक *curs_pal_ptr =
	    (अस्थिर अचिन्हित पूर्णांक *) CURS_PAL_REG;
	पूर्णांक mem, i;

	अगर (fb_get_options("g364fb", शून्य))
		वापस -ENODEV;

	/* TBD: G364 detection */

	/* get the resolution set by ARC console */
	*(अस्थिर अचिन्हित पूर्णांक *) CTLA_REG &= ~ENABLE_VTG;
	fb_var.xres =
	    (*((अस्थिर अचिन्हित पूर्णांक *) DISPLAY_REG) & 0x00ffffff) * 4;
	fb_var.yres =
	    (*((अस्थिर अचिन्हित पूर्णांक *) VDISPLAY_REG) & 0x00ffffff) / 2;
	*(अस्थिर अचिन्हित पूर्णांक *) CTLA_REG |= ENABLE_VTG;

	/* setup cursor */
	curs_pal_ptr[0] |= 0x00ffffff;
	curs_pal_ptr[2] |= 0x00ffffff;
	curs_pal_ptr[4] |= 0x00ffffff;

	/*
	 * first set the whole cursor to transparent
	 */
	क्रम (i = 0; i < 512; i++)
		*(अचिन्हित लघु *) (CURS_PAT_REG + i * 8) = 0;

	/*
	 * चयन the last two lines to cursor palette 3
	 * we assume here, that FONTSIZE_X is 8
	 */
	*(अचिन्हित लघु *) (CURS_PAT_REG + 14 * 64) = 0xffff;
	*(अचिन्हित लघु *) (CURS_PAT_REG + 15 * 64) = 0xffff;
	fb_var.xres_भव = fb_var.xres;
	fb_fix.line_length = fb_var.xres_भव * fb_var.bits_per_pixel / 8;
	fb_fix.smem_start = 0x40000000;	/* physical address */
	/* get size of video memory; this is special क्रम the JAZZ hardware */
	mem = (r4030_पढ़ो_reg32(JAZZ_R4030_CONFIG) >> 8) & 3;
	fb_fix.smem_len = (1 << (mem * 2)) * 512 * 1024;
	fb_var.yres_भव = fb_fix.smem_len / fb_var.xres;

	fb_info.fbops = &g364fb_ops;
	fb_info.screen_base = (अक्षर *) G364_MEM_BASE;	/* भव kernel address */
	fb_info.var = fb_var;
	fb_info.fix = fb_fix;
	fb_info.flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;

	fb_alloc_cmap(&fb_info.cmap, 255, 0);

	अगर (रेजिस्टर_framebuffer(&fb_info) < 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

module_init(g364fb_init);
MODULE_LICENSE("GPL");
