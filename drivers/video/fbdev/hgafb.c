<शैली गुरु>
/*
 * linux/drivers/video/hgafb.c -- Hercules graphics adaptor frame buffer device
 * 
 *      Created 25 Nov 1999 by Ferenc Bakonyi (fero@drama.obuda.kanकरो.hu)
 *      Based on skeletonfb.c by Geert Uytterhoeven and
 *               mdacon.c by Andrew Apted
 *
 * History:
 *
 * - Revision 0.1.8 (23 Oct 2002): Ported to new framebuffer api.
 * 
 * - Revision 0.1.7 (23 Jan 2001): fix crash resulting from MDA only cards 
 *				   being detected as Hercules.	 (Paul G.)
 * - Revision 0.1.6 (17 Aug 2000): new style काष्ठाs
 *                                 करोcumentation
 * - Revision 0.1.5 (13 Mar 2000): spinlocks instead of saveflags();cli();etc
 *                                 minor fixes
 * - Revision 0.1.4 (24 Jan 2000): fixed a bug in hga_card_detect() क्रम 
 *                                  HGA-only प्रणालीs
 * - Revision 0.1.3 (22 Jan 2000): modअगरied क्रम the new fb_info काष्ठाure
 *                                 screen is cleared after rmmod
 *                                 भव resolutions
 *                                 module parameter 'nologo={0|1}'
 *                                 the most important: boot logo :)
 * - Revision 0.1.0  (6 Dec 1999): faster scrolling and minor fixes
 * - First release  (25 Nov 1999)
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/vga.h>

#अगर 0
#घोषणा DPRINTK(args...) prपूर्णांकk(KERN_DEBUG __खाता__": " ##args)
#अन्यथा
#घोषणा DPRINTK(args...)
#पूर्ण_अगर

#अगर 0
#घोषणा CHKINFO(ret) अगर (info != &fb_info) अणु prपूर्णांकk(KERN_DEBUG __खाता__": This should never happen, line:%d \n", __LINE__); वापस ret; पूर्ण
#अन्यथा
#घोषणा CHKINFO(ret)
#पूर्ण_अगर

/* Description of the hardware layout */

अटल व्योम __iomem *hga_vram;			/* Base of video memory */
अटल अचिन्हित दीर्घ hga_vram_len;		/* Size of video memory */

#घोषणा HGA_ROWADDR(row) ((row%4)*8192 + (row>>2)*90)
#घोषणा HGA_TXT			0
#घोषणा HGA_GFX			1

अटल अंतरभूत u8 __iomem * rowaddr(काष्ठा fb_info *info, u_पूर्णांक row)
अणु
	वापस info->screen_base + HGA_ROWADDR(row);
पूर्ण

अटल पूर्णांक hga_mode = -1;			/* 0 = txt, 1 = gfx mode */

अटल क्रमागत अणु TYPE_HERC, TYPE_HERCPLUS, TYPE_HERCCOLOR पूर्ण hga_type;
अटल अक्षर *hga_type_name;

#घोषणा HGA_INDEX_PORT		0x3b4		/* Register select port */
#घोषणा HGA_VALUE_PORT		0x3b5		/* Register value port */
#घोषणा HGA_MODE_PORT		0x3b8		/* Mode control port */
#घोषणा HGA_STATUS_PORT		0x3ba		/* Status and Config port */
#घोषणा HGA_GFX_PORT		0x3bf		/* Graphics control port */

/* HGA रेजिस्टर values */

#घोषणा HGA_CURSOR_BLINKING	0x00
#घोषणा HGA_CURSOR_OFF		0x20
#घोषणा HGA_CURSOR_SLOWBLINK	0x60

#घोषणा HGA_MODE_GRAPHICS	0x02
#घोषणा HGA_MODE_VIDEO_EN	0x08
#घोषणा HGA_MODE_BLINK_EN	0x20
#घोषणा HGA_MODE_GFX_PAGE1	0x80

#घोषणा HGA_STATUS_HSYNC	0x01
#घोषणा HGA_STATUS_VSYNC	0x80
#घोषणा HGA_STATUS_VIDEO	0x08

#घोषणा HGA_CONFIG_COL132	0x08
#घोषणा HGA_GFX_MODE_EN		0x01
#घोषणा HGA_GFX_PAGE_EN		0x02

/* Global locks */

अटल DEFINE_SPINLOCK(hga_reg_lock);

/* Framebuffer driver काष्ठाures */

अटल स्थिर काष्ठा fb_var_screeninfo hga_शेष_var = अणु
	.xres		= 720,
	.yres 		= 348,
	.xres_भव 	= 720,
	.yres_भव	= 348,
	.bits_per_pixel = 1,
	.red 		= अणु0, 1, 0पूर्ण,
	.green 		= अणु0, 1, 0पूर्ण,
	.blue 		= अणु0, 1, 0पूर्ण,
	.transp 	= अणु0, 0, 0पूर्ण,
	.height 	= -1,
	.width 		= -1,
पूर्ण;

अटल काष्ठा fb_fix_screeninfo hga_fix = अणु
	.id 		= "HGA",
	.type 		= FB_TYPE_PACKED_PIXELS,	/* (not sure) */
	.visual 	= FB_VISUAL_MONO10,
	.xpanstep 	= 8,
	.ypanstep 	= 8,
	.line_length 	= 90,
	.accel 		= FB_ACCEL_NONE
पूर्ण;

/* Don't assume that tty1 will be the initial current console. */
अटल पूर्णांक release_io_port = 0;
अटल पूर्णांक release_io_ports = 0;
अटल bool nologo = 0;

/* -------------------------------------------------------------------------
 *
 * Low level hardware functions
 *
 * ------------------------------------------------------------------------- */

अटल व्योम ग_लिखो_hga_b(अचिन्हित पूर्णांक val, अचिन्हित अक्षर reg)
अणु
	outb_p(reg, HGA_INDEX_PORT); 
	outb_p(val, HGA_VALUE_PORT);
पूर्ण

अटल व्योम ग_लिखो_hga_w(अचिन्हित पूर्णांक val, अचिन्हित अक्षर reg)
अणु
	outb_p(reg,   HGA_INDEX_PORT); outb_p(val >> 8,   HGA_VALUE_PORT);
	outb_p(reg+1, HGA_INDEX_PORT); outb_p(val & 0xff, HGA_VALUE_PORT);
पूर्ण

अटल पूर्णांक test_hga_b(अचिन्हित अक्षर val, अचिन्हित अक्षर reg)
अणु
	outb_p(reg, HGA_INDEX_PORT); 
	outb  (val, HGA_VALUE_PORT);
	udelay(20); val = (inb_p(HGA_VALUE_PORT) == val);
	वापस val;
पूर्ण

अटल व्योम hga_clear_screen(व्योम)
अणु
	अचिन्हित अक्षर fillअक्षर = 0xbf; /* magic */
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hga_reg_lock, flags);
	अगर (hga_mode == HGA_TXT)
		fillअक्षर = ' ';
	अन्यथा अगर (hga_mode == HGA_GFX)
		fillअक्षर = 0x00;
	spin_unlock_irqrestore(&hga_reg_lock, flags);
	अगर (fillअक्षर != 0xbf)
		स_रखो_io(hga_vram, fillअक्षर, hga_vram_len);
पूर्ण

अटल व्योम hga_txt_mode(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hga_reg_lock, flags);
	outb_p(HGA_MODE_VIDEO_EN | HGA_MODE_BLINK_EN, HGA_MODE_PORT);
	outb_p(0x00, HGA_GFX_PORT);
	outb_p(0x00, HGA_STATUS_PORT);

	ग_लिखो_hga_b(0x61, 0x00);	/* horizontal total */
	ग_लिखो_hga_b(0x50, 0x01);	/* horizontal displayed */
	ग_लिखो_hga_b(0x52, 0x02);	/* horizontal sync pos */
	ग_लिखो_hga_b(0x0f, 0x03);	/* horizontal sync width */

	ग_लिखो_hga_b(0x19, 0x04);	/* vertical total */
	ग_लिखो_hga_b(0x06, 0x05);	/* vertical total adjust */
	ग_लिखो_hga_b(0x19, 0x06);	/* vertical displayed */
	ग_लिखो_hga_b(0x19, 0x07);	/* vertical sync pos */

	ग_लिखो_hga_b(0x02, 0x08);	/* पूर्णांकerlace mode */
	ग_लिखो_hga_b(0x0d, 0x09);	/* maximum scanline */
	ग_लिखो_hga_b(0x0c, 0x0a);	/* cursor start */
	ग_लिखो_hga_b(0x0d, 0x0b);	/* cursor end */

	ग_लिखो_hga_w(0x0000, 0x0c);	/* start address */
	ग_लिखो_hga_w(0x0000, 0x0e);	/* cursor location */

	hga_mode = HGA_TXT;
	spin_unlock_irqrestore(&hga_reg_lock, flags);
पूर्ण

अटल व्योम hga_gfx_mode(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hga_reg_lock, flags);
	outb_p(0x00, HGA_STATUS_PORT);
	outb_p(HGA_GFX_MODE_EN, HGA_GFX_PORT);
	outb_p(HGA_MODE_VIDEO_EN | HGA_MODE_GRAPHICS, HGA_MODE_PORT);

	ग_लिखो_hga_b(0x35, 0x00);	/* horizontal total */
	ग_लिखो_hga_b(0x2d, 0x01);	/* horizontal displayed */
	ग_लिखो_hga_b(0x2e, 0x02);	/* horizontal sync pos */
	ग_लिखो_hga_b(0x07, 0x03);	/* horizontal sync width */

	ग_लिखो_hga_b(0x5b, 0x04);	/* vertical total */
	ग_लिखो_hga_b(0x02, 0x05);	/* vertical total adjust */
	ग_लिखो_hga_b(0x57, 0x06);	/* vertical displayed */
	ग_लिखो_hga_b(0x57, 0x07);	/* vertical sync pos */

	ग_लिखो_hga_b(0x02, 0x08);	/* पूर्णांकerlace mode */
	ग_लिखो_hga_b(0x03, 0x09);	/* maximum scanline */
	ग_लिखो_hga_b(0x00, 0x0a);	/* cursor start */
	ग_लिखो_hga_b(0x00, 0x0b);	/* cursor end */

	ग_लिखो_hga_w(0x0000, 0x0c);	/* start address */
	ग_लिखो_hga_w(0x0000, 0x0e);	/* cursor location */

	hga_mode = HGA_GFX;
	spin_unlock_irqrestore(&hga_reg_lock, flags);
पूर्ण

अटल व्योम hga_show_logo(काष्ठा fb_info *info)
अणु
/*
	व्योम __iomem *dest = hga_vram;
	अक्षर *logo = linux_logo_bw;
	पूर्णांक x, y;
	
	क्रम (y = 134; y < 134 + 80 ; y++) * this needs some cleanup *
		क्रम (x = 0; x < 10 ; x++)
			ग_लिखोb(~*(logo++),(dest + HGA_ROWADDR(y) + x + 40));
*/
पूर्ण

अटल व्योम hga_pan(अचिन्हित पूर्णांक xoffset, अचिन्हित पूर्णांक yoffset)
अणु
	अचिन्हित पूर्णांक base;
	अचिन्हित दीर्घ flags;
	
	base = (yoffset / 8) * 90 + xoffset;
	spin_lock_irqsave(&hga_reg_lock, flags);
	ग_लिखो_hga_w(base, 0x0c);	/* start address */
	spin_unlock_irqrestore(&hga_reg_lock, flags);
	DPRINTK("hga_pan: base:%d\n", base);
पूर्ण

अटल व्योम hga_blank(पूर्णांक blank_mode)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hga_reg_lock, flags);
	अगर (blank_mode) अणु
		outb_p(0x00, HGA_MODE_PORT);	/* disable video */
	पूर्ण अन्यथा अणु
		outb_p(HGA_MODE_VIDEO_EN | HGA_MODE_GRAPHICS, HGA_MODE_PORT);
	पूर्ण
	spin_unlock_irqrestore(&hga_reg_lock, flags);
पूर्ण

अटल पूर्णांक hga_card_detect(व्योम)
अणु
	पूर्णांक count = 0;
	व्योम __iomem *p, *q;
	अचिन्हित लघु p_save, q_save;

	hga_vram_len  = 0x08000;

	hga_vram = ioremap(0xb0000, hga_vram_len);
	अगर (!hga_vram)
		वापस -ENOMEM;

	अगर (request_region(0x3b0, 12, "hgafb"))
		release_io_ports = 1;
	अगर (request_region(0x3bf, 1, "hgafb"))
		release_io_port = 1;

	/* करो a memory check */

	p = hga_vram;
	q = hga_vram + 0x01000;

	p_save = पढ़ोw(p); q_save = पढ़ोw(q);

	ग_लिखोw(0xaa55, p); अगर (पढ़ोw(p) == 0xaa55) count++;
	ग_लिखोw(0x55aa, p); अगर (पढ़ोw(p) == 0x55aa) count++;
	ग_लिखोw(p_save, p);

	अगर (count != 2)
		जाओ error;

	/* Ok, there is definitely a card रेजिस्टरing at the correct
	 * memory location, so now we करो an I/O port test.
	 */
	
	अगर (!test_hga_b(0x66, 0x0f))	    /* cursor low रेजिस्टर */
		जाओ error;

	अगर (!test_hga_b(0x99, 0x0f))     /* cursor low रेजिस्टर */
		जाओ error;

	/* See अगर the card is a Hercules, by checking whether the vsync
	 * bit of the status रेजिस्टर is changing.  This test lasts क्रम
	 * approximately 1/10th of a second.
	 */
	
	p_save = q_save = inb_p(HGA_STATUS_PORT) & HGA_STATUS_VSYNC;

	क्रम (count=0; count < 50000 && p_save == q_save; count++) अणु
		q_save = inb(HGA_STATUS_PORT) & HGA_STATUS_VSYNC;
		udelay(2);
	पूर्ण

	अगर (p_save == q_save) 
		जाओ error;

	चयन (inb_p(HGA_STATUS_PORT) & 0x70) अणु
		हाल 0x10:
			hga_type = TYPE_HERCPLUS;
			hga_type_name = "HerculesPlus";
			अवरोध;
		हाल 0x50:
			hga_type = TYPE_HERCCOLOR;
			hga_type_name = "HerculesColor";
			अवरोध;
		शेष:
			hga_type = TYPE_HERC;
			hga_type_name = "Hercules";
			अवरोध;
	पूर्ण
	वापस 0;
error:
	अगर (release_io_ports)
		release_region(0x3b0, 12);
	अगर (release_io_port)
		release_region(0x3bf, 1);

	iounmap(hga_vram);

	pr_err("hgafb: HGA card not detected.\n");

	वापस -EINVAL;
पूर्ण

/**
 *	hgafb_खोलो - खोलो the framebuffer device
 *	@info: poपूर्णांकer to fb_info object containing info क्रम current hga board
 *	@init: खोलो by console प्रणाली or userland.
 */

अटल पूर्णांक hgafb_खोलो(काष्ठा fb_info *info, पूर्णांक init)
अणु
	hga_gfx_mode();
	hga_clear_screen();
	अगर (!nologo) hga_show_logo(info);
	वापस 0;
पूर्ण

/**
 *	hgafb_release - खोलो the framebuffer device
 *	@info: poपूर्णांकer to fb_info object containing info क्रम current hga board
 *	@init: खोलो by console प्रणाली or userland.
 */

अटल पूर्णांक hgafb_release(काष्ठा fb_info *info, पूर्णांक init)
अणु
	hga_txt_mode();
	hga_clear_screen();
	वापस 0;
पूर्ण

/**
 *	hgafb_setcolreg - set color रेजिस्टरs
 *	@regno:रेजिस्टर index to set
 *	@red:red value, unused
 *	@green:green value, unused
 *	@blue:blue value, unused
 *	@transp:transparency value, unused
 *	@info:unused
 *
 *	This callback function is used to set the color रेजिस्टरs of a HGA
 *	board. Since we have only two fixed colors only @regno is checked.
 *	A zero is वापसed on success and 1 क्रम failure.
 */

अटल पूर्णांक hgafb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			   u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	अगर (regno > 1)
		वापस 1;
	वापस 0;
पूर्ण

/**
 *	hga_pan_display - pan or wrap the display
 *	@var:contains new xoffset, yoffset and vmode values
 *	@info:poपूर्णांकer to fb_info object containing info क्रम current hga board
 *
 *	This function looks only at xoffset, yoffset and the %FB_VMODE_YWRAP
 *	flag in @var. If input parameters are correct it calls hga_pan() to 
 *	program the hardware. @info->var is updated to the new values.
 *	A zero is वापसed on success and %-EINVAL क्रम failure.
 */

अटल पूर्णांक hgafb_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	अगर (var->vmode & FB_VMODE_YWRAP) अणु
		अगर (var->yoffset >= info->var.yres_भव ||
		    var->xoffset)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (var->xoffset + info->var.xres > info->var.xres_भव
		 || var->yoffset + info->var.yres > info->var.yres_भव
		 || var->yoffset % 8)
			वापस -EINVAL;
	पूर्ण

	hga_pan(var->xoffset, var->yoffset);
	वापस 0;
पूर्ण

/**
 *	hgafb_blank - (un)blank the screen
 *	@blank_mode:blanking method to use
 *	@info:unused
 *	
 *	Blank the screen अगर blank_mode != 0, अन्यथा unblank. 
 *	Implements VESA suspend and घातerकरोwn modes on hardware that supports 
 *	disabling hsync/vsync:
 *		@blank_mode == 2 means suspend vsync,
 *		@blank_mode == 3 means suspend hsync,
 *		@blank_mode == 4 means घातerकरोwn.
 */

अटल पूर्णांक hgafb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	hga_blank(blank_mode);
	वापस 0;
पूर्ण

/*
 * Accel functions
 */
अटल व्योम hgafb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	u_पूर्णांक rows, y;
	u8 __iomem *dest;

	y = rect->dy;

	क्रम (rows = rect->height; rows--; y++) अणु
		dest = rowaddr(info, y) + (rect->dx >> 3);
		चयन (rect->rop) अणु
		हाल ROP_COPY:
			स_रखो_io(dest, rect->color, (rect->width >> 3));
			अवरोध;
		हाल ROP_XOR:
			fb_ग_लिखोb(~(fb_पढ़ोb(dest)), dest);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hgafb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	u_पूर्णांक rows, y1, y2;
	u8 __iomem *src;
	u8 __iomem *dest;

	अगर (area->dy <= area->sy) अणु
		y1 = area->sy;
		y2 = area->dy;

		क्रम (rows = area->height; rows--; ) अणु
			src = rowaddr(info, y1) + (area->sx >> 3);
			dest = rowaddr(info, y2) + (area->dx >> 3);
			स_हटाओ(dest, src, (area->width >> 3));
			y1++;
			y2++;
		पूर्ण
	पूर्ण अन्यथा अणु
		y1 = area->sy + area->height - 1;
		y2 = area->dy + area->height - 1;

		क्रम (rows = area->height; rows--;) अणु
			src = rowaddr(info, y1) + (area->sx >> 3);
			dest = rowaddr(info, y2) + (area->dx >> 3);
			स_हटाओ(dest, src, (area->width >> 3));
			y1--;
			y2--;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hgafb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	u8 __iomem *dest;
	u8 *cdat = (u8 *) image->data;
	u_पूर्णांक rows, y = image->dy;
	u_पूर्णांक x;
	u8 d;

	क्रम (rows = image->height; rows--; y++) अणु
		क्रम (x = 0; x < image->width; x+= 8) अणु
			d = *cdat++;
			dest = rowaddr(info, y) + ((image->dx + x)>> 3);
			fb_ग_लिखोb(d, dest);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा fb_ops hgafb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो	= hgafb_खोलो,
	.fb_release	= hgafb_release,
	.fb_setcolreg	= hgafb_setcolreg,
	.fb_pan_display	= hgafb_pan_display,
	.fb_blank	= hgafb_blank,
	.fb_fillrect	= hgafb_fillrect,
	.fb_copyarea	= hgafb_copyarea,
	.fb_imageblit	= hgafb_imageblit,
पूर्ण;
		
/* ------------------------------------------------------------------------- *
 *
 * Functions in fb_info
 * 
 * ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
    
	/*
	 *  Initialization
	 */

अटल पूर्णांक hgafb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info;
	पूर्णांक ret;

	ret = hga_card_detect();
	अगर (ret)
		वापस ret;

	prपूर्णांकk(KERN_INFO "hgafb: %s with %ldK of memory detected.\n",
		hga_type_name, hga_vram_len/1024);

	info = framebuffer_alloc(0, &pdev->dev);
	अगर (!info) अणु
		iounmap(hga_vram);
		वापस -ENOMEM;
	पूर्ण

	hga_fix.smem_start = (अचिन्हित दीर्घ)hga_vram;
	hga_fix.smem_len = hga_vram_len;

	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
	info->var = hga_शेष_var;
	info->fix = hga_fix;
	info->monspecs.hfmin = 0;
	info->monspecs.hfmax = 0;
	info->monspecs.vfmin = 10000;
	info->monspecs.vfmax = 10000;
	info->monspecs.dpms = 0;
	info->fbops = &hgafb_ops;
	info->screen_base = hga_vram;

        अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		framebuffer_release(info);
		iounmap(hga_vram);
		वापस -EINVAL;
	पूर्ण

	fb_info(info, "%s frame buffer device\n", info->fix.id);
	platक्रमm_set_drvdata(pdev, info);
	वापस 0;
पूर्ण

अटल पूर्णांक hgafb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);

	hga_txt_mode();
	hga_clear_screen();

	अगर (info) अणु
		unरेजिस्टर_framebuffer(info);
		framebuffer_release(info);
	पूर्ण

	iounmap(hga_vram);

	अगर (release_io_ports)
		release_region(0x3b0, 12);

	अगर (release_io_port)
		release_region(0x3bf, 1);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hgafb_driver = अणु
	.probe = hgafb_probe,
	.हटाओ = hgafb_हटाओ,
	.driver = अणु
		.name = "hgafb",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *hgafb_device;

अटल पूर्णांक __init hgafb_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (fb_get_options("hgafb", शून्य))
		वापस -ENODEV;

	ret = platक्रमm_driver_रेजिस्टर(&hgafb_driver);

	अगर (!ret) अणु
		hgafb_device = platक्रमm_device_रेजिस्टर_simple("hgafb", 0, शून्य, 0);

		अगर (IS_ERR(hgafb_device)) अणु
			platक्रमm_driver_unरेजिस्टर(&hgafb_driver);
			ret = PTR_ERR(hgafb_device);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास hgafb_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(hgafb_device);
	platक्रमm_driver_unरेजिस्टर(&hgafb_driver);
पूर्ण

/* -------------------------------------------------------------------------
 *
 *  Modularization
 *
 * ------------------------------------------------------------------------- */

MODULE_AUTHOR("Ferenc Bakonyi (fero@drama.obuda.kando.hu)");
MODULE_DESCRIPTION("FBDev driver for Hercules Graphics Adaptor");
MODULE_LICENSE("GPL");

module_param(nologo, bool, 0);
MODULE_PARM_DESC(nologo, "Disables startup logo if != 0 (default=0)");
module_init(hgafb_init);
module_निकास(hgafb_निकास);
