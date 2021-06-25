<शैली गुरु>
/*
 *      linux/drivers/video/maxinefb.c
 *
 *	DECstation 5000/xx onboard framebuffer support ... derived from:
 *	"HP300 Topcat framebuffer support (derived from macfb of all things)
 *	Phil Blundell <philb@gnu.org> 1998", the original code can be
 *      found in the file hpfb.c in the same directory.
 *
 *      DECstation related code Copyright (C) 1999,2000,2001 by
 *      Michael Engel <engel@unix-ag.org> and
 *      Karsten Merker <merker@linuxtag.org>.
 *      This file is subject to the terms and conditions of the GNU General
 *      Public License.  See the file COPYING in the मुख्य directory of this
 *      archive क्रम more details.
 *
 */

/*
 * Changes:
 * 2001/01/27 हटाओd debugging and testing code, fixed fb_ops
 *            initialization which had caused a crash beक्रमe,
 *            general cleanup, first official release (KM)
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/fb.h>
#समावेश <video/maxinefb.h>

/* bootinfo.h defines the machine type values, needed when checking */
/* whether are really running on a maxine, KM                       */
#समावेश <यंत्र/bootinfo.h>

अटल काष्ठा fb_info fb_info;

अटल स्थिर काष्ठा fb_var_screeninfo maxinefb_defined = अणु
	.xres =		1024,
	.yres =		768,
	.xres_भव =	1024,
	.yres_भव =	768,
	.bits_per_pixel =8,
	.activate =	FB_ACTIVATE_NOW,
	.height =	-1,
	.width =	-1,
	.vmode =	FB_VMODE_NONINTERLACED,
पूर्ण;

अटल काष्ठा fb_fix_screeninfo maxinefb_fix __initdata = अणु
	.id =		"Maxine",
	.smem_len =	(1024*768),
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_PSEUDOCOLOR,
	.line_length =	1024,
पूर्ण;

/* Handle the funny Inmos RamDAC/video controller ... */

व्योम maxinefb_ims332_ग_लिखो_रेजिस्टर(पूर्णांक regno, रेजिस्टर अचिन्हित पूर्णांक val)
अणु
	रेजिस्टर अचिन्हित अक्षर *regs = (अक्षर *) MAXINEFB_IMS332_ADDRESS;
	अचिन्हित अक्षर *wptr;

	wptr = regs + 0xa0000 + (regno << 4);
	*((अस्थिर अचिन्हित पूर्णांक *) (regs)) = (val >> 8) & 0xff00;
	*((अस्थिर अचिन्हित लघु *) (wptr)) = val;
पूर्ण

अचिन्हित पूर्णांक maxinefb_ims332_पढ़ो_रेजिस्टर(पूर्णांक regno)
अणु
	रेजिस्टर अचिन्हित अक्षर *regs = (अक्षर *) MAXINEFB_IMS332_ADDRESS;
	अचिन्हित अक्षर *rptr;
	रेजिस्टर अचिन्हित पूर्णांक j, k;

	rptr = regs + 0x80000 + (regno << 4);
	j = *((अस्थिर अचिन्हित लघु *) rptr);
	k = *((अस्थिर अचिन्हित लघु *) regs);

	वापस (j & 0xffff) | ((k & 0xff00) << 8);
पूर्ण

/* Set the palette */
अटल पूर्णांक maxinefb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			      अचिन्हित blue, अचिन्हित transp, काष्ठा fb_info *info)
अणु
	/* value to be written पूर्णांकo the palette reg. */
	अचिन्हित दीर्घ hw_colorvalue = 0;

	अगर (regno > 255)
		वापस 1;

	red   >>= 8;    /* The cmap fields are 16 bits    */
	green >>= 8;    /* wide, but the harware colormap */
	blue  >>= 8;    /* रेजिस्टरs are only 8 bits wide */

	hw_colorvalue = (blue << 16) + (green << 8) + (red);

	maxinefb_ims332_ग_लिखो_रेजिस्टर(IMS332_REG_COLOR_PALETTE + regno,
				       hw_colorvalue);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops maxinefb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_setcolreg	= maxinefb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

पूर्णांक __init maxinefb_init(व्योम)
अणु
	अचिन्हित दीर्घ fboff;
	अचिन्हित दीर्घ fb_start;
	पूर्णांक i;

	अगर (fb_get_options("maxinefb", शून्य))
		वापस -ENODEV;

	/* Validate we're on the proper machine type */
	अगर (mips_machtype != MACH_DS5000_XX) अणु
		वापस -EINVAL;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Maxinefb: Personal DECstation detected\n");
	prपूर्णांकk(KERN_INFO "Maxinefb: initializing onboard framebuffer\n");

	/* Framebuffer display memory base address */
	fb_start = DS5000_xx_ONBOARD_FBMEM_START;

	/* Clear screen */
	क्रम (fboff = fb_start; fboff < fb_start + 0x1ffff; fboff++)
		*(अस्थिर अचिन्हित अक्षर *)fboff = 0x0;

	maxinefb_fix.smem_start = fb_start;
	
	/* erase hardware cursor */
	क्रम (i = 0; i < 512; i++) अणु
		maxinefb_ims332_ग_लिखो_रेजिस्टर(IMS332_REG_CURSOR_RAM + i,
					       0);
		/*
		   अगर (i&0x8 == 0)
		   maxinefb_ims332_ग_लिखो_रेजिस्टर (IMS332_REG_CURSOR_RAM + i, 0x0f);
		   अन्यथा
		   maxinefb_ims332_ग_लिखो_रेजिस्टर (IMS332_REG_CURSOR_RAM + i, 0xf0);
		 */
	पूर्ण

	fb_info.fbops = &maxinefb_ops;
	fb_info.screen_base = (अक्षर *)maxinefb_fix.smem_start;
	fb_info.var = maxinefb_defined;
	fb_info.fix = maxinefb_fix;
	fb_info.flags = FBINFO_DEFAULT;

	fb_alloc_cmap(&fb_info.cmap, 256, 0);

	अगर (रेजिस्टर_framebuffer(&fb_info) < 0)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम __निकास maxinefb_निकास(व्योम)
अणु
	unरेजिस्टर_framebuffer(&fb_info);
पूर्ण

#अगर_घोषित MODULE
MODULE_LICENSE("GPL");
#पूर्ण_अगर
module_init(maxinefb_init);
module_निकास(maxinefb_निकास);

