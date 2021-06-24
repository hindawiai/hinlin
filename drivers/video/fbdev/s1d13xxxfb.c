<शैली गुरु>
/* drivers/video/s1d13xxxfb.c
 *
 * (c) 2004 Simtec Electronics
 * (c) 2005 Thibaut VARENE <varenet@parisc-linux.org>
 * (c) 2009 Kristoffer Ericson <kristoffer.ericson@gmail.com>
 *
 * Driver क्रम Epson S1D13xxx series framebuffer chips
 *
 * Adapted from
 *  linux/drivers/video/skeletonfb.c
 *  linux/drivers/video/epson1355fb.c
 *  linux/drivers/video/epson/s1d13xxxfb.c (2.4 driver by Epson)
 *
 * TODO: - handle dual screen display (CRT and LCD at the same समय).
 *	 - check_var(), mode change, etc.
 *	 - probably not SMP safe :)
 *       - support all bitblt operations on all cards
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/fb.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश <video/s1d13xxxfb.h>

#घोषणा PFX	"s1d13xxxfb: "
#घोषणा BLIT	"s1d13xxxfb_bitblt: "

/*
 * set this to enable debugging on general functions
 */
#अगर 0
#घोषणा dbg(fmt, args...) करो अणु prपूर्णांकk(KERN_INFO fmt, ## args); पूर्ण जबतक(0)
#अन्यथा
#घोषणा dbg(fmt, args...) करो अणु no_prपूर्णांकk(KERN_INFO fmt, ## args); पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * set this to enable debugging on 2D acceleration
 */
#अगर 0
#घोषणा dbg_blit(fmt, args...) करो अणु prपूर्णांकk(KERN_INFO BLIT fmt, ## args); पूर्ण जबतक (0)
#अन्यथा
#घोषणा dbg_blit(fmt, args...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * we make sure only one bitblt operation is running
 */
अटल DEFINE_SPINLOCK(s1d13xxxfb_bitblt_lock);

/*
 * list of card production ids
 */
अटल स्थिर पूर्णांक s1d13xxxfb_prod_ids[] = अणु
	S1D13505_PROD_ID,
	S1D13506_PROD_ID,
	S1D13806_PROD_ID,
पूर्ण;

/*
 * List of card strings
 */
अटल स्थिर अक्षर *s1d13xxxfb_prod_names[] = अणु
	"S1D13505",
	"S1D13506",
	"S1D13806",
पूर्ण;

/*
 * here we define the शेष काष्ठा fb_fix_screeninfo
 */
अटल स्थिर काष्ठा fb_fix_screeninfo s1d13xxxfb_fix = अणु
	.id		= S1D_FBID,
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_PSEUDOCOLOR,
	.xpanstep	= 0,
	.ypanstep	= 1,
	.ywrapstep	= 0,
	.accel		= FB_ACCEL_NONE,
पूर्ण;

अटल अंतरभूत u8
s1d13xxxfb_पढ़ोreg(काष्ठा s1d13xxxfb_par *par, u16 regno)
अणु
	वापस पढ़ोb(par->regs + regno);
पूर्ण

अटल अंतरभूत व्योम
s1d13xxxfb_ग_लिखोreg(काष्ठा s1d13xxxfb_par *par, u16 regno, u8 value)
अणु
	ग_लिखोb(value, par->regs + regno);
पूर्ण

अटल अंतरभूत व्योम
s1d13xxxfb_runinit(काष्ठा s1d13xxxfb_par *par,
			स्थिर काष्ठा s1d13xxxfb_regval *initregs,
			स्थिर अचिन्हित पूर्णांक size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
        	अगर ((initregs[i].addr == S1DREG_DELAYOFF) ||
				(initregs[i].addr == S1DREG_DELAYON))
			mdelay((पूर्णांक)initregs[i].value);
        	अन्यथा अणु
			s1d13xxxfb_ग_लिखोreg(par, initregs[i].addr, initregs[i].value);
		पूर्ण
        पूर्ण

	/* make sure the hardware can cope with us */
	mdelay(1);
पूर्ण

अटल अंतरभूत व्योम
lcd_enable(काष्ठा s1d13xxxfb_par *par, पूर्णांक enable)
अणु
	u8 mode = s1d13xxxfb_पढ़ोreg(par, S1DREG_COM_DISP_MODE);

	अगर (enable)
		mode |= 0x01;
	अन्यथा
		mode &= ~0x01;

	s1d13xxxfb_ग_लिखोreg(par, S1DREG_COM_DISP_MODE, mode);
पूर्ण

अटल अंतरभूत व्योम
crt_enable(काष्ठा s1d13xxxfb_par *par, पूर्णांक enable)
अणु
	u8 mode = s1d13xxxfb_पढ़ोreg(par, S1DREG_COM_DISP_MODE);

	अगर (enable)
		mode |= 0x02;
	अन्यथा
		mode &= ~0x02;

	s1d13xxxfb_ग_लिखोreg(par, S1DREG_COM_DISP_MODE, mode);
पूर्ण


/*************************************************************
 framebuffer control functions
 *************************************************************/
अटल अंतरभूत व्योम
s1d13xxxfb_setup_pseuकरोcolour(काष्ठा fb_info *info)
अणु
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->var.red.length = 4;
	info->var.green.length = 4;
	info->var.blue.length = 4;
पूर्ण

अटल अंतरभूत व्योम
s1d13xxxfb_setup_truecolour(काष्ठा fb_info *info)
अणु
	info->fix.visual = FB_VISUAL_TRUECOLOR;
	info->var.bits_per_pixel = 16;

	info->var.red.length = 5;
	info->var.red.offset = 11;

	info->var.green.length = 6;
	info->var.green.offset = 5;

	info->var.blue.length = 5;
	info->var.blue.offset = 0;
पूर्ण

/**
 *      s1d13xxxfb_set_par - Alters the hardware state.
 *      @info: frame buffer काष्ठाure
 *
 *	Using the fb_var_screeninfo in fb_info we set the depth of the
 *	framebuffer. This function alters the par AND the
 *	fb_fix_screeninfo stored in fb_info. It करोesn't not alter var in
 *	fb_info since we are using that data. This means we depend on the
 *	data in var inside fb_info to be supported by the hardware.
 *	xxxfb_check_var is always called beक्रमe xxxfb_set_par to ensure this.
 *
 *	XXX TODO: ग_लिखो proper s1d13xxxfb_check_var(), without which that
 *	function is quite useless.
 */
अटल पूर्णांक
s1d13xxxfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा s1d13xxxfb_par *s1dfb = info->par;
	अचिन्हित पूर्णांक val;

	dbg("s1d13xxxfb_set_par: bpp=%d\n", info->var.bits_per_pixel);

	अगर ((s1dfb->display & 0x01))	/* LCD */
		val = s1d13xxxfb_पढ़ोreg(s1dfb, S1DREG_LCD_DISP_MODE);   /* पढ़ो colour control */
	अन्यथा	/* CRT */
		val = s1d13xxxfb_पढ़ोreg(s1dfb, S1DREG_CRT_DISP_MODE);   /* पढ़ो colour control */

	val &= ~0x07;

	चयन (info->var.bits_per_pixel) अणु
		हाल 4:
			dbg("pseudo colour 4\n");
			s1d13xxxfb_setup_pseuकरोcolour(info);
			val |= 2;
			अवरोध;
		हाल 8:
			dbg("pseudo colour 8\n");
			s1d13xxxfb_setup_pseuकरोcolour(info);
			val |= 3;
			अवरोध;
		हाल 16:
			dbg("true colour\n");
			s1d13xxxfb_setup_truecolour(info);
			val |= 5;
			अवरोध;

		शेष:
			dbg("bpp not supported!\n");
			वापस -EINVAL;
	पूर्ण

	dbg("writing %02x to display mode register\n", val);

	अगर ((s1dfb->display & 0x01))	/* LCD */
		s1d13xxxfb_ग_लिखोreg(s1dfb, S1DREG_LCD_DISP_MODE, val);
	अन्यथा	/* CRT */
		s1d13xxxfb_ग_लिखोreg(s1dfb, S1DREG_CRT_DISP_MODE, val);

	info->fix.line_length  = info->var.xres * info->var.bits_per_pixel;
	info->fix.line_length /= 8;

	dbg("setting line_length to %d\n", info->fix.line_length);

	dbg("done setup\n");

	वापस 0;
पूर्ण

/**
 *	s1d13xxxfb_setcolreg - sets a color रेजिस्टर.
 *	@regno: Which रेजिस्टर in the CLUT we are programming
 *	@red: The red value which can be up to 16 bits wide
 *	@green: The green value which can be up to 16 bits wide
 *	@blue:  The blue value which can be up to 16 bits wide.
 *	@transp: If supported the alpha value which can be up to 16 bits wide.
 *	@info: frame buffer info काष्ठाure
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 */
अटल पूर्णांक
s1d13xxxfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा s1d13xxxfb_par *s1dfb = info->par;
	अचिन्हित पूर्णांक pseuकरो_val;

	अगर (regno >= S1D_PALETTE_SIZE)
		वापस -EINVAL;

	dbg("s1d13xxxfb_setcolreg: %d: rgb=%d,%d,%d, tr=%d\n",
		    regno, red, green, blue, transp);

	अगर (info->var.grayscale)
		red = green = blue = (19595*red + 38470*green + 7471*blue) >> 16;

	चयन (info->fix.visual) अणु
		हाल FB_VISUAL_TRUECOLOR:
			अगर (regno >= 16)
				वापस -EINVAL;

			/* deal with creating pseuकरो-palette entries */

			pseuकरो_val  = (red   >> 11) << info->var.red.offset;
			pseuकरो_val |= (green >> 10) << info->var.green.offset;
			pseuकरो_val |= (blue  >> 11) << info->var.blue.offset;

			dbg("s1d13xxxfb_setcolreg: pseudo %d, val %08x\n",
				    regno, pseuकरो_val);

			((u32 *)info->pseuकरो_palette)[regno] = pseuकरो_val;

			अवरोध;
		हाल FB_VISUAL_PSEUDOCOLOR:
			s1d13xxxfb_ग_लिखोreg(s1dfb, S1DREG_LKUP_ADDR, regno);
			s1d13xxxfb_ग_लिखोreg(s1dfb, S1DREG_LKUP_DATA, red);
			s1d13xxxfb_ग_लिखोreg(s1dfb, S1DREG_LKUP_DATA, green);
			s1d13xxxfb_ग_लिखोreg(s1dfb, S1DREG_LKUP_DATA, blue);

			अवरोध;
		शेष:
			वापस -ENOSYS;
	पूर्ण

	dbg("s1d13xxxfb_setcolreg: done\n");

	वापस 0;
पूर्ण

/**
 *      s1d13xxxfb_blank - blanks the display.
 *      @blank_mode: the blank mode we want.
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *      Blank the screen अगर blank_mode != 0, अन्यथा unblank. Return 0 अगर
 *      blanking succeeded, != 0 अगर un-/blanking failed due to e.g. a
 *      video mode which करोesn't support it. Implements VESA suspend
 *      and घातerकरोwn modes on hardware that supports disabling hsync/vsync:
 *      blank_mode == 2: suspend vsync
 *      blank_mode == 3: suspend hsync
 *      blank_mode == 4: घातerकरोwn
 *
 *      Returns negative त्रुटि_सं on error, or zero on success.
 */
अटल पूर्णांक
s1d13xxxfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा s1d13xxxfb_par *par = info->par;

	dbg("s1d13xxxfb_blank: blank=%d, info=%p\n", blank_mode, info);

	चयन (blank_mode) अणु
		हाल FB_BLANK_UNBLANK:
		हाल FB_BLANK_NORMAL:
			अगर ((par->display & 0x01) != 0)
				lcd_enable(par, 1);
			अगर ((par->display & 0x02) != 0)
				crt_enable(par, 1);
			अवरोध;
		हाल FB_BLANK_VSYNC_SUSPEND:
		हाल FB_BLANK_HSYNC_SUSPEND:
			अवरोध;
		हाल FB_BLANK_POWERDOWN:
			lcd_enable(par, 0);
			crt_enable(par, 0);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	/* let fbcon करो a soft blank क्रम us */
	वापस ((blank_mode == FB_BLANK_NORMAL) ? 1 : 0);
पूर्ण

/**
 *	s1d13xxxfb_pan_display - Pans the display.
 *	@var: frame buffer variable screen काष्ठाure
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *	Pan (or wrap, depending on the `vmode' field) the display using the
 *	`yoffset' field of the `var' structure (`xoffset'  not yet supported).
 *	If the values करोn't fit, वापस -EINVAL.
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 */
अटल पूर्णांक
s1d13xxxfb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा s1d13xxxfb_par *par = info->par;
	u32 start;

	अगर (var->xoffset != 0)	/* not yet ... */
		वापस -EINVAL;

	अगर (var->yoffset + info->var.yres > info->var.yres_भव)
		वापस -EINVAL;

	start = (info->fix.line_length >> 1) * var->yoffset;

	अगर ((par->display & 0x01)) अणु
		/* LCD */
		s1d13xxxfb_ग_लिखोreg(par, S1DREG_LCD_DISP_START0, (start & 0xff));
		s1d13xxxfb_ग_लिखोreg(par, S1DREG_LCD_DISP_START1, ((start >> 8) & 0xff));
		s1d13xxxfb_ग_लिखोreg(par, S1DREG_LCD_DISP_START2, ((start >> 16) & 0x0f));
	पूर्ण अन्यथा अणु
		/* CRT */
		s1d13xxxfb_ग_लिखोreg(par, S1DREG_CRT_DISP_START0, (start & 0xff));
		s1d13xxxfb_ग_लिखोreg(par, S1DREG_CRT_DISP_START1, ((start >> 8) & 0xff));
		s1d13xxxfb_ग_लिखोreg(par, S1DREG_CRT_DISP_START2, ((start >> 16) & 0x0f));
	पूर्ण

	वापस 0;
पूर्ण

/************************************************************
 functions to handle bitblt acceleration
 ************************************************************/

/**
 *	bltbit_रुको_bitclear - रुकोs क्रम change in रेजिस्टर value
 *	@info : frambuffer काष्ठाure
 *	@bit  : value currently in रेजिस्टर
 *	@समयout : ...
 *
 *	रुकोs until value changes FROM bit
 *
 */
अटल u8
bltbit_रुको_bitclear(काष्ठा fb_info *info, u8 bit, पूर्णांक समयout)
अणु
	जबतक (s1d13xxxfb_पढ़ोreg(info->par, S1DREG_BBLT_CTL0) & bit) अणु
		udelay(10);
		अगर (!--समयout) अणु
			dbg_blit("wait_bitclear timeout\n");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस समयout;
पूर्ण

/*
 *	s1d13xxxfb_bitblt_copyarea - accelerated copyarea function
 *	@info : framebuffer काष्ठाure
 *	@area : fb_copyarea काष्ठाure
 *
 *	supports (atleast) S1D13506
 *
 */
अटल व्योम
s1d13xxxfb_bitblt_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	u32 dst, src;
	u32 stride;
	u16 reverse = 0;
	u16 sx = area->sx, sy = area->sy;
	u16 dx = area->dx, dy = area->dy;
	u16 width = area->width, height = area->height;
	u16 bpp;

	spin_lock(&s1d13xxxfb_bitblt_lock);

	/* bytes per xres line */
	bpp = (info->var.bits_per_pixel >> 3);
	stride = bpp * info->var.xres;

	/* reverse, calculate the last pixel in rectangle */
	अगर ((dy > sy) || ((dy == sy) && (dx >= sx))) अणु
		dst = (((dy + height - 1) * stride) + (bpp * (dx + width - 1)));
		src = (((sy + height - 1) * stride) + (bpp * (sx + width - 1)));
		reverse = 1;
	/* not reverse, calculate the first pixel in rectangle */
	पूर्ण अन्यथा अणु /* (y * xres) + (bpp * x) */
		dst = (dy * stride) + (bpp * dx);
		src = (sy * stride) + (bpp * sx);
	पूर्ण

	/* set source address */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_SRC_START0, (src & 0xff));
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_SRC_START1, (src >> 8) & 0x00ff);
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_SRC_START2, (src >> 16) & 0x00ff);

	/* set destination address */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_DST_START0, (dst & 0xff));
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_DST_START1, (dst >> 8) & 0x00ff);
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_DST_START2, (dst >> 16) & 0x00ff);

	/* program height and width */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_WIDTH0, (width & 0xff) - 1);
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_WIDTH1, (width >> 8));

	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_HEIGHT0, (height & 0xff) - 1);
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_HEIGHT1, (height >> 8));

	/* negative direction ROP */
	अगर (reverse == 1) अणु
		dbg_blit("(copyarea) negative rop\n");
		s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_OP, 0x03);
	पूर्ण अन्यथा /* positive direction ROP */ अणु
		s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_OP, 0x02);
		dbg_blit("(copyarea) positive rop\n");
	पूर्ण

	/* set क्रम rectangel mode and not linear */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_CTL0, 0x0);

	/* setup the bpp 1 = 16bpp, 0 = 8bpp*/
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_CTL1, (bpp >> 1));

	/* set words per xres */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_MEM_OFF0, (stride >> 1) & 0xff);
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_MEM_OFF1, (stride >> 9));

	dbg_blit("(copyarea) dx=%d, dy=%d\n", dx, dy);
	dbg_blit("(copyarea) sx=%d, sy=%d\n", sx, sy);
	dbg_blit("(copyarea) width=%d, height=%d\n", width - 1, height - 1);
	dbg_blit("(copyarea) stride=%d\n", stride);
	dbg_blit("(copyarea) bpp=%d=0x0%d, mem_offset1=%d, mem_offset2=%d\n", bpp, (bpp >> 1),
		(stride >> 1) & 0xff, stride >> 9);

	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_CC_EXP, 0x0c);

	/* initialize the engine */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_CTL0, 0x80);

	/* रुको to complete */
	bltbit_रुको_bitclear(info, 0x80, 8000);

	spin_unlock(&s1d13xxxfb_bitblt_lock);
पूर्ण

/**
 *	s1d13xxxfb_bitblt_solidfill - accelerated solidfill function
 *	@info : framebuffer काष्ठाure
 *	@rect : fb_fillrect काष्ठाure
 *
 *	supports (atleast 13506)
 *
 **/
अटल व्योम
s1d13xxxfb_bitblt_solidfill(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	u32 screen_stride, dest;
	u32 fg;
	u16 bpp = (info->var.bits_per_pixel >> 3);

	/* grab spinlock */
	spin_lock(&s1d13xxxfb_bitblt_lock);

	/* bytes per x width */
	screen_stride = (bpp * info->var.xres);

	/* bytes to starting poपूर्णांक */
	dest = ((rect->dy * screen_stride) + (bpp * rect->dx));

	dbg_blit("(solidfill) dx=%d, dy=%d, stride=%d, dest=%d\n"
		 "(solidfill) : rect_width=%d, rect_height=%d\n",
				rect->dx, rect->dy, screen_stride, dest,
				rect->width - 1, rect->height - 1);

	dbg_blit("(solidfill) : xres=%d, yres=%d, bpp=%d\n",
				info->var.xres, info->var.yres,
				info->var.bits_per_pixel);
	dbg_blit("(solidfill) : rop=%d\n", rect->rop);

	/* We split the destination पूर्णांकo the three रेजिस्टरs */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_DST_START0, (dest & 0x00ff));
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_DST_START1, ((dest >> 8) & 0x00ff));
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_DST_START2, ((dest >> 16) & 0x00ff));

	/* give inक्रमmation regarding rectangel width */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_WIDTH0, ((rect->width) & 0x00ff) - 1);
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_WIDTH1, (rect->width >> 8));

	/* give inक्रमmation regarding rectangel height */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_HEIGHT0, ((rect->height) & 0x00ff) - 1);
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_HEIGHT1, (rect->height >> 8));

	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR ||
		info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
		fg = ((u32 *)info->pseuकरो_palette)[rect->color];
		dbg_blit("(solidfill) truecolor/directcolor\n");
		dbg_blit("(solidfill) pseudo_palette[%d] = %d\n", rect->color, fg);
	पूर्ण अन्यथा अणु
		fg = rect->color;
		dbg_blit("(solidfill) color = %d\n", rect->color);
	पूर्ण

	/* set क्रमeground color */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_FGC0, (fg & 0xff));
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_FGC1, (fg >> 8) & 0xff);

	/* set rectangual region of memory (rectangle and not linear) */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_CTL0, 0x0);

	/* set operation mode SOLID_FILL */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_OP, BBLT_SOLID_FILL);

	/* set bits per pixel (1 = 16bpp, 0 = 8bpp) */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_CTL1, (info->var.bits_per_pixel >> 4));

	/* set the memory offset क्रम the bblt in word sizes */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_MEM_OFF0, (screen_stride >> 1) & 0x00ff);
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_MEM_OFF1, (screen_stride >> 9));

	/* and away we go.... */
	s1d13xxxfb_ग_लिखोreg(info->par, S1DREG_BBLT_CTL0, 0x80);

	/* रुको until its करोne */
	bltbit_रुको_bitclear(info, 0x80, 8000);

	/* let others play */
	spin_unlock(&s1d13xxxfb_bitblt_lock);
पूर्ण

/* framebuffer inक्रमmation काष्ठाures */
अटल काष्ठा fb_ops s1d13xxxfb_fbops = अणु
	.owner		= THIS_MODULE,
	.fb_set_par	= s1d13xxxfb_set_par,
	.fb_setcolreg	= s1d13xxxfb_setcolreg,
	.fb_blank	= s1d13xxxfb_blank,

	.fb_pan_display	= s1d13xxxfb_pan_display,

	/* माला_लो replaced at chip detection समय */
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल पूर्णांक s1d13xxxfb_width_tab[2][4] = अणु
	अणु4, 8, 16, -1पूर्ण,
	अणु9, 12, 18, -1पूर्ण,
पूर्ण;

/**
 *	s1d13xxxfb_fetch_hw_state - Configure the framebuffer according to
 *	hardware setup.
 *	@info: frame buffer काष्ठाure
 *
 *	We setup the framebuffer काष्ठाures according to the current
 *	hardware setup. On some machines, the BIOS will have filled
 *	the chip रेजिस्टरs with such info, on others, these values will
 *	have been written in some init procedure. In any हाल, the
 *	software values needs to match the hardware ones. This is what
 *	this function ensures.
 *
 *	Note: some of the hardcoded values here might need some love to
 *	work on various chips, and might need to no दीर्घer be hardcoded.
 */
अटल व्योम s1d13xxxfb_fetch_hw_state(काष्ठा fb_info *info)
अणु
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा fb_fix_screeninfo *fix = &info->fix;
	काष्ठा s1d13xxxfb_par *par = info->par;
	u8 panel, display;
	u16 offset;
	u32 xres, yres;
	u32 xres_भव, yres_भव;
	पूर्णांक bpp, lcd_bpp;
	पूर्णांक is_color, is_dual, is_tft;
	पूर्णांक lcd_enabled, crt_enabled;

	fix->type = FB_TYPE_PACKED_PIXELS;

	/* general info */
	par->display = s1d13xxxfb_पढ़ोreg(par, S1DREG_COM_DISP_MODE);
	crt_enabled = (par->display & 0x02) != 0;
	lcd_enabled = (par->display & 0x01) != 0;

	अगर (lcd_enabled && crt_enabled)
		prपूर्णांकk(KERN_WARNING PFX "Warning: LCD and CRT detected, using LCD\n");

	अगर (lcd_enabled)
		display = s1d13xxxfb_पढ़ोreg(par, S1DREG_LCD_DISP_MODE);
	अन्यथा	/* CRT */
		display = s1d13xxxfb_पढ़ोreg(par, S1DREG_CRT_DISP_MODE);

	bpp = display & 0x07;

	चयन (bpp) अणु
		हाल 2:	/* 4 bpp */
		हाल 3:	/* 8 bpp */
			var->bits_per_pixel = 8;
			var->red.offset = var->green.offset = var->blue.offset = 0;
			var->red.length = var->green.length = var->blue.length = 8;
			अवरोध;
		हाल 5:	/* 16 bpp */
			s1d13xxxfb_setup_truecolour(info);
			अवरोध;
		शेष:
			dbg("bpp: %i\n", bpp);
	पूर्ण
	fb_alloc_cmap(&info->cmap, 256, 0);

	/* LCD info */
	panel = s1d13xxxfb_पढ़ोreg(par, S1DREG_PANEL_TYPE);
	is_color = (panel & 0x04) != 0;
	is_dual = (panel & 0x02) != 0;
	is_tft = (panel & 0x01) != 0;
	lcd_bpp = s1d13xxxfb_width_tab[is_tft][(panel >> 4) & 3];

	अगर (lcd_enabled) अणु
		xres = (s1d13xxxfb_पढ़ोreg(par, S1DREG_LCD_DISP_HWIDTH) + 1) * 8;
		yres = (s1d13xxxfb_पढ़ोreg(par, S1DREG_LCD_DISP_VHEIGHT0) +
			((s1d13xxxfb_पढ़ोreg(par, S1DREG_LCD_DISP_VHEIGHT1) & 0x03) << 8) + 1);

		offset = (s1d13xxxfb_पढ़ोreg(par, S1DREG_LCD_MEM_OFF0) +
			((s1d13xxxfb_पढ़ोreg(par, S1DREG_LCD_MEM_OFF1) & 0x7) << 8));
	पूर्ण अन्यथा अणु /* crt */
		xres = (s1d13xxxfb_पढ़ोreg(par, S1DREG_CRT_DISP_HWIDTH) + 1) * 8;
		yres = (s1d13xxxfb_पढ़ोreg(par, S1DREG_CRT_DISP_VHEIGHT0) +
			((s1d13xxxfb_पढ़ोreg(par, S1DREG_CRT_DISP_VHEIGHT1) & 0x03) << 8) + 1);

		offset = (s1d13xxxfb_पढ़ोreg(par, S1DREG_CRT_MEM_OFF0) +
			((s1d13xxxfb_पढ़ोreg(par, S1DREG_CRT_MEM_OFF1) & 0x7) << 8));
	पूर्ण
	xres_भव = offset * 16 / var->bits_per_pixel;
	yres_भव = fix->smem_len / (offset * 2);

	var->xres		= xres;
	var->yres		= yres;
	var->xres_भव	= xres_भव;
	var->yres_भव	= yres_भव;
	var->xoffset		= var->yoffset = 0;

	fix->line_length	= offset * 2;

	var->grayscale		= !is_color;

	var->activate		= FB_ACTIVATE_NOW;

	dbg(PFX "bpp=%d, lcd_bpp=%d, "
		"crt_enabled=%d, lcd_enabled=%d\n",
		var->bits_per_pixel, lcd_bpp, crt_enabled, lcd_enabled);
	dbg(PFX "xres=%d, yres=%d, vxres=%d, vyres=%d "
		"is_color=%d, is_dual=%d, is_tft=%d\n",
		xres, yres, xres_भव, yres_भव, is_color, is_dual, is_tft);
पूर्ण

अटल व्योम __s1d13xxxfb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा s1d13xxxfb_par *par = शून्य;

	अगर (info) अणु
		par = info->par;
		अगर (par && par->regs) अणु
			/* disable output & enable घातersave */
			s1d13xxxfb_ग_लिखोreg(par, S1DREG_COM_DISP_MODE, 0x00);
			s1d13xxxfb_ग_लिखोreg(par, S1DREG_PS_CNF, 0x11);
			iounmap(par->regs);
		पूर्ण

		fb_dealloc_cmap(&info->cmap);

		अगर (info->screen_base)
			iounmap(info->screen_base);

		framebuffer_release(info);
	पूर्ण

	release_mem_region(pdev->resource[0].start,
			   resource_size(&pdev->resource[0]));
	release_mem_region(pdev->resource[1].start,
			   resource_size(&pdev->resource[1]));
पूर्ण

अटल पूर्णांक s1d13xxxfb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_framebuffer(info);
	__s1d13xxxfb_हटाओ(pdev);
	वापस 0;
पूर्ण

अटल पूर्णांक s1d13xxxfb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s1d13xxxfb_par *शेष_par;
	काष्ठा fb_info *info;
	काष्ठा s1d13xxxfb_pdata *pdata = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक i;
	u8 revision, prod_id;

	dbg("probe called: device is %p\n", pdev);

	prपूर्णांकk(KERN_INFO "Epson S1D13XXX FB Driver\n");

	/* enable platक्रमm-dependent hardware glue, अगर any */
	अगर (dev_get_platdata(&pdev->dev))
		pdata = dev_get_platdata(&pdev->dev);

	अगर (pdata && pdata->platक्रमm_init_video)
		pdata->platक्रमm_init_video();

	अगर (pdev->num_resources != 2) अणु
		dev_err(&pdev->dev, "invalid num_resources: %i\n",
		       pdev->num_resources);
		ret = -ENODEV;
		जाओ bail;
	पूर्ण

	/* resource[0] is VRAM, resource[1] is रेजिस्टरs */
	अगर (pdev->resource[0].flags != IORESOURCE_MEM
			|| pdev->resource[1].flags != IORESOURCE_MEM) अणु
		dev_err(&pdev->dev, "invalid resource type\n");
		ret = -ENODEV;
		जाओ bail;
	पूर्ण

	अगर (!request_mem_region(pdev->resource[0].start,
		resource_size(&pdev->resource[0]), "s1d13xxxfb mem")) अणु
		dev_dbg(&pdev->dev, "request_mem_region failed\n");
		ret = -EBUSY;
		जाओ bail;
	पूर्ण

	अगर (!request_mem_region(pdev->resource[1].start,
		resource_size(&pdev->resource[1]), "s1d13xxxfb regs")) अणु
		dev_dbg(&pdev->dev, "request_mem_region failed\n");
		ret = -EBUSY;
		जाओ bail;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा s1d13xxxfb_par) + माप(u32) * 256, &pdev->dev);
	अगर (!info) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);
	शेष_par = info->par;
	शेष_par->regs = ioremap(pdev->resource[1].start,
				    resource_size(&pdev->resource[1]));
	अगर (!शेष_par->regs) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to map registers\n");
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण
	info->pseuकरो_palette = शेष_par->pseuकरो_palette;

	info->screen_base = ioremap(pdev->resource[0].start,
				    resource_size(&pdev->resource[0]));

	अगर (!info->screen_base) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to map framebuffer\n");
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	/* production id is top 6 bits */
	prod_id = s1d13xxxfb_पढ़ोreg(शेष_par, S1DREG_REV_CODE) >> 2;
	/* revision id is lower 2 bits */
	revision = s1d13xxxfb_पढ़ोreg(शेष_par, S1DREG_REV_CODE) & 0x3;
	ret = -ENODEV;

	क्रम (i = 0; i < ARRAY_SIZE(s1d13xxxfb_prod_ids); i++) अणु
		अगर (prod_id == s1d13xxxfb_prod_ids[i]) अणु
			/* looks like we got it in our list */
			शेष_par->prod_id = prod_id;
			शेष_par->revision = revision;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ret) अणु
		prपूर्णांकk(KERN_INFO PFX "chip production id %i = %s\n",
			prod_id, s1d13xxxfb_prod_names[i]);
		prपूर्णांकk(KERN_INFO PFX "chip revision %i\n", revision);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO PFX
			"unknown chip production id %i, revision %i\n",
			prod_id, revision);
		prपूर्णांकk(KERN_INFO PFX "please contact maintainer\n");
		जाओ bail;
	पूर्ण

	info->fix = s1d13xxxfb_fix;
	info->fix.mmio_start = pdev->resource[1].start;
	info->fix.mmio_len = resource_size(&pdev->resource[1]);
	info->fix.smem_start = pdev->resource[0].start;
	info->fix.smem_len = resource_size(&pdev->resource[0]);

	prपूर्णांकk(KERN_INFO PFX "regs mapped at 0x%p, fb %d KiB mapped at 0x%p\n",
	       शेष_par->regs, info->fix.smem_len / 1024, info->screen_base);

	info->par = शेष_par;
	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
	info->fbops = &s1d13xxxfb_fbops;

	चयन(prod_id) अणु
	हाल S1D13506_PROD_ID:	/* activate acceleration */
		s1d13xxxfb_fbops.fb_fillrect = s1d13xxxfb_bitblt_solidfill;
		s1d13xxxfb_fbops.fb_copyarea = s1d13xxxfb_bitblt_copyarea;
		info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN |
			FBINFO_HWACCEL_FILLRECT | FBINFO_HWACCEL_COPYAREA;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* perक्रमm "manual" chip initialization, अगर needed */
	अगर (pdata && pdata->initregs)
		s1d13xxxfb_runinit(info->par, pdata->initregs, pdata->initregssize);

	s1d13xxxfb_fetch_hw_state(info);

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	fb_info(info, "%s frame buffer device\n", info->fix.id);

	वापस 0;

bail:
	__s1d13xxxfb_हटाओ(pdev);
	वापस ret;

पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक s1d13xxxfb_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा s1d13xxxfb_par *s1dfb = info->par;
	काष्ठा s1d13xxxfb_pdata *pdata = शून्य;

	/* disable display */
	lcd_enable(s1dfb, 0);
	crt_enable(s1dfb, 0);

	अगर (dev_get_platdata(&dev->dev))
		pdata = dev_get_platdata(&dev->dev);

#अगर 0
	अगर (!s1dfb->disp_save)
		s1dfb->disp_save = kदो_स्मृति(info->fix.smem_len, GFP_KERNEL);

	अगर (!s1dfb->disp_save) अणु
		prपूर्णांकk(KERN_ERR PFX "no memory to save screen\n");
		वापस -ENOMEM;
	पूर्ण

	स_नकल_fromio(s1dfb->disp_save, info->screen_base, info->fix.smem_len);
#अन्यथा
	s1dfb->disp_save = शून्य;
#पूर्ण_अगर

	अगर (!s1dfb->regs_save)
		s1dfb->regs_save = kदो_स्मृति(info->fix.mmio_len, GFP_KERNEL);

	अगर (!s1dfb->regs_save) अणु
		prपूर्णांकk(KERN_ERR PFX "no memory to save registers");
		वापस -ENOMEM;
	पूर्ण

	/* backup all रेजिस्टरs */
	स_नकल_fromio(s1dfb->regs_save, s1dfb->regs, info->fix.mmio_len);

	/* now activate घातer save mode */
	s1d13xxxfb_ग_लिखोreg(s1dfb, S1DREG_PS_CNF, 0x11);

	अगर (pdata && pdata->platक्रमm_suspend_video)
		वापस pdata->platक्रमm_suspend_video();
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक s1d13xxxfb_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा s1d13xxxfb_par *s1dfb = info->par;
	काष्ठा s1d13xxxfb_pdata *pdata = शून्य;

	/* awaken the chip */
	s1d13xxxfb_ग_लिखोreg(s1dfb, S1DREG_PS_CNF, 0x10);

	/* करो not let go until SDRAM "wakes up" */
	जबतक ((s1d13xxxfb_पढ़ोreg(s1dfb, S1DREG_PS_STATUS) & 0x01))
		udelay(10);

	अगर (dev_get_platdata(&dev->dev))
		pdata = dev_get_platdata(&dev->dev);

	अगर (s1dfb->regs_save) अणु
		/* will ग_लिखो RO regs, *should* get away with it :) */
		स_नकल_toio(s1dfb->regs, s1dfb->regs_save, info->fix.mmio_len);
		kमुक्त(s1dfb->regs_save);
	पूर्ण

	अगर (s1dfb->disp_save) अणु
		स_नकल_toio(info->screen_base, s1dfb->disp_save,
				info->fix.smem_len);
		kमुक्त(s1dfb->disp_save);	/* XXX kदो_स्मृति()'d when? */
	पूर्ण

	अगर ((s1dfb->display & 0x01) != 0)
		lcd_enable(s1dfb, 1);
	अगर ((s1dfb->display & 0x02) != 0)
		crt_enable(s1dfb, 1);

	अगर (pdata && pdata->platक्रमm_resume_video)
		वापस pdata->platक्रमm_resume_video();
	अन्यथा
		वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा platक्रमm_driver s1d13xxxfb_driver = अणु
	.probe		= s1d13xxxfb_probe,
	.हटाओ		= s1d13xxxfb_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= s1d13xxxfb_suspend,
	.resume		= s1d13xxxfb_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= S1D_DEVICENAME,
	पूर्ण,
पूर्ण;


अटल पूर्णांक __init
s1d13xxxfb_init(व्योम)
अणु

#अगर_अघोषित MODULE
	अगर (fb_get_options("s1d13xxxfb", शून्य))
		वापस -ENODEV;
#पूर्ण_अगर

	वापस platक्रमm_driver_रेजिस्टर(&s1d13xxxfb_driver);
पूर्ण


अटल व्योम __निकास
s1d13xxxfb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&s1d13xxxfb_driver);
पूर्ण

module_init(s1d13xxxfb_init);
module_निकास(s1d13xxxfb_निकास);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Framebuffer driver for S1D13xxx devices");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>, Thibaut VARENE <varenet@parisc-linux.org>");
