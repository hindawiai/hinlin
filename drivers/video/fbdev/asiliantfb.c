<शैली गुरु>
/*
 * drivers/video/asiliantfb.c
 *  frame buffer driver क्रम Asiliant 69000 chip
 *  Copyright (C) 2001-2003 Saito.K & Jeanne
 *
 *  from driver/video/chipsfb.c and,
 *
 *  drivers/video/asiliantfb.c -- frame buffer device क्रम
 *  Asiliant 69030 chip (क्रमmerly Intel, क्रमmerly Chips & Technologies)
 *  Author: apc@agelectronics.co.uk
 *  Copyright (C) 2000 AG Electronics
 *  Note: the data sheets करोn't seem to be available from Asiliant.
 *  They are available by searching developer.पूर्णांकel.com, but are not otherwise
 *  linked to.
 *
 *  This driver should be portable with minimal efक्रमt to the 69000 display
 *  chip, and to the twin-display mode of the 69030.
 *  Contains code from Thomas Hhenleitner <th@visuelle-maschinen.de> (thanks)
 *
 *  Derived from the CT65550 driver chipsfb.c:
 *  Copyright (C) 1998 Paul Mackerras
 *  ...which was derived from the Powermac "chips" driver:
 *  Copyright (C) 1997 Fabio Riccardi.
 *  And from the frame buffer device क्रम Open Firmware-initialized devices:
 *  Copyright (C) 1997 Geert Uytterhoeven.
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/पन.स>

/* Built in घड़ी of the 69030 */
अटल स्थिर अचिन्हित Fref = 14318180;

#घोषणा mmio_base (p->screen_base + 0x400000)

#घोषणा mm_ग_लिखो_ind(num, val, ap, dp)	करो अणु \
	ग_लिखोb((num), mmio_base + (ap)); ग_लिखोb((val), mmio_base + (dp)); \
पूर्ण जबतक (0)

अटल व्योम mm_ग_लिखो_xr(काष्ठा fb_info *p, u8 reg, u8 data)
अणु
	mm_ग_लिखो_ind(reg, data, 0x7ac, 0x7ad);
पूर्ण
#घोषणा ग_लिखो_xr(num, val)	mm_ग_लिखो_xr(p, num, val)

अटल व्योम mm_ग_लिखो_fr(काष्ठा fb_info *p, u8 reg, u8 data)
अणु
	mm_ग_लिखो_ind(reg, data, 0x7a0, 0x7a1);
पूर्ण
#घोषणा ग_लिखो_fr(num, val)	mm_ग_लिखो_fr(p, num, val)

अटल व्योम mm_ग_लिखो_cr(काष्ठा fb_info *p, u8 reg, u8 data)
अणु
	mm_ग_लिखो_ind(reg, data, 0x7a8, 0x7a9);
पूर्ण
#घोषणा ग_लिखो_cr(num, val)	mm_ग_लिखो_cr(p, num, val)

अटल व्योम mm_ग_लिखो_gr(काष्ठा fb_info *p, u8 reg, u8 data)
अणु
	mm_ग_लिखो_ind(reg, data, 0x79c, 0x79d);
पूर्ण
#घोषणा ग_लिखो_gr(num, val)	mm_ग_लिखो_gr(p, num, val)

अटल व्योम mm_ग_लिखो_sr(काष्ठा fb_info *p, u8 reg, u8 data)
अणु
	mm_ग_लिखो_ind(reg, data, 0x788, 0x789);
पूर्ण
#घोषणा ग_लिखो_sr(num, val)	mm_ग_लिखो_sr(p, num, val)

अटल व्योम mm_ग_लिखो_ar(काष्ठा fb_info *p, u8 reg, u8 data)
अणु
	पढ़ोb(mmio_base + 0x7b4);
	mm_ग_लिखो_ind(reg, data, 0x780, 0x780);
पूर्ण
#घोषणा ग_लिखो_ar(num, val)	mm_ग_लिखो_ar(p, num, val)

अटल पूर्णांक asiliantfb_pci_init(काष्ठा pci_dev *dp, स्थिर काष्ठा pci_device_id *);
अटल पूर्णांक asiliantfb_check_var(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info);
अटल पूर्णांक asiliantfb_set_par(काष्ठा fb_info *info);
अटल पूर्णांक asiliantfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
				u_पूर्णांक transp, काष्ठा fb_info *info);

अटल स्थिर काष्ठा fb_ops asiliantfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= asiliantfb_check_var,
	.fb_set_par	= asiliantfb_set_par,
	.fb_setcolreg	= asiliantfb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

/* Calculate the ratios क्रम the करोt घड़ीs without using a single दीर्घ दीर्घ
 * value */
अटल व्योम asiliant_calc_dclk2(u32 *ppixघड़ी, u8 *dclk2_m, u8 *dclk2_n, u8 *dclk2_भाग)
अणु
	अचिन्हित pixघड़ी = *ppixघड़ी;
	अचिन्हित Ftarget = 1000000 * (1000000 / pixघड़ी);
	अचिन्हित n;
	अचिन्हित best_error = 0xffffffff;
	अचिन्हित best_m = 0xffffffff,
	         best_n = 0xffffffff;
	अचिन्हित ratio;
	अचिन्हित reमुख्यder;
	अचिन्हित अक्षर भागisor = 0;

	/* Calculate the frequency required. This is hard enough. */
	ratio = 1000000 / pixघड़ी;
	reमुख्यder = 1000000 % pixघड़ी;
	Ftarget = 1000000 * ratio + (1000000 * reमुख्यder) / pixघड़ी;

	जबतक (Ftarget < 100000000) अणु
		भागisor += 0x10;
		Ftarget <<= 1;
	पूर्ण

	ratio = Ftarget / Fref;
	reमुख्यder = Ftarget % Fref;

	/* This expresses the स्थिरraपूर्णांक that 150kHz <= Fref/n <= 5Mhz,
	 * together with 3 <= n <= 257. */
	क्रम (n = 3; n <= 257; n++) अणु
		अचिन्हित m = n * ratio + (n * reमुख्यder) / Fref;

		/* 3 <= m <= 257 */
		अगर (m >= 3 && m <= 257) अणु
			अचिन्हित new_error = Ftarget * n >= Fref * m ?
					       ((Ftarget * n) - (Fref * m)) : ((Fref * m) - (Ftarget * n));
			अगर (new_error < best_error) अणु
				best_n = n;
				best_m = m;
				best_error = new_error;
			पूर्ण
		पूर्ण
		/* But अगर VLD = 4, then 4m <= 1028 */
		अन्यथा अगर (m <= 1028) अणु
			/* remember there are still only 8-bits of precision in m, so
			 * aव्योम over-optimistic error calculations */
			अचिन्हित new_error = Ftarget * n >= Fref * (m & ~3) ?
					       ((Ftarget * n) - (Fref * (m & ~3))) : ((Fref * (m & ~3)) - (Ftarget * n));
			अगर (new_error < best_error) अणु
				best_n = n;
				best_m = m;
				best_error = new_error;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (best_m > 257)
		best_m >>= 2;	/* भागide m by 4, and leave VCO loop भागide at 4 */
	अन्यथा
		भागisor |= 4;	/* or set VCO loop भागide to 1 */
	*dclk2_m = best_m - 2;
	*dclk2_n = best_n - 2;
	*dclk2_भाग = भागisor;
	*ppixघड़ी = pixघड़ी;
	वापस;
पूर्ण

अटल व्योम asiliant_set_timing(काष्ठा fb_info *p)
अणु
	अचिन्हित hd = p->var.xres / 8;
	अचिन्हित hs = (p->var.xres + p->var.right_margin) / 8;
       	अचिन्हित he = (p->var.xres + p->var.right_margin + p->var.hsync_len) / 8;
	अचिन्हित ht = (p->var.left_margin + p->var.xres + p->var.right_margin + p->var.hsync_len) / 8;
	अचिन्हित vd = p->var.yres;
	अचिन्हित vs = p->var.yres + p->var.lower_margin;
	अचिन्हित ve = p->var.yres + p->var.lower_margin + p->var.vsync_len;
	अचिन्हित vt = p->var.upper_margin + p->var.yres + p->var.lower_margin + p->var.vsync_len;
	अचिन्हित wd = (p->var.xres_भव * ((p->var.bits_per_pixel+7)/8)) / 8;

	अगर ((p->var.xres == 640) && (p->var.yres == 480) && (p->var.pixघड़ी == 39722)) अणु
	  ग_लिखो_fr(0x01, 0x02);  /* LCD */
	पूर्ण अन्यथा अणु
	  ग_लिखो_fr(0x01, 0x01);  /* CRT */
	पूर्ण

	ग_लिखो_cr(0x11, (ve - 1) & 0x0f);
	ग_लिखो_cr(0x00, (ht - 5) & 0xff);
	ग_लिखो_cr(0x01, hd - 1);
	ग_लिखो_cr(0x02, hd);
	ग_लिखो_cr(0x03, ((ht - 1) & 0x1f) | 0x80);
	ग_लिखो_cr(0x04, hs);
	ग_लिखो_cr(0x05, (((ht - 1) & 0x20) <<2) | (he & 0x1f));
	ग_लिखो_cr(0x3c, (ht - 1) & 0xc0);
	ग_लिखो_cr(0x06, (vt - 2) & 0xff);
	ग_लिखो_cr(0x30, (vt - 2) >> 8);
	ग_लिखो_cr(0x07, 0x00);
	ग_लिखो_cr(0x08, 0x00);
	ग_लिखो_cr(0x09, 0x00);
	ग_लिखो_cr(0x10, (vs - 1) & 0xff);
	ग_लिखो_cr(0x32, ((vs - 1) >> 8) & 0xf);
	ग_लिखो_cr(0x11, ((ve - 1) & 0x0f) | 0x80);
	ग_लिखो_cr(0x12, (vd - 1) & 0xff);
	ग_लिखो_cr(0x31, ((vd - 1) & 0xf00) >> 8);
	ग_लिखो_cr(0x13, wd & 0xff);
	ग_लिखो_cr(0x41, (wd & 0xf00) >> 8);
	ग_लिखो_cr(0x15, (vs - 1) & 0xff);
	ग_लिखो_cr(0x33, ((vs - 1) >> 8) & 0xf);
	ग_लिखो_cr(0x38, ((ht - 5) & 0x100) >> 8);
	ग_लिखो_cr(0x16, (vt - 1) & 0xff);
	ग_लिखो_cr(0x18, 0x00);

	अगर (p->var.xres == 640) अणु
	  ग_लिखोb(0xc7, mmio_base + 0x784);	/* set misc output reg */
	पूर्ण अन्यथा अणु
	  ग_लिखोb(0x07, mmio_base + 0x784);	/* set misc output reg */
	पूर्ण
पूर्ण

अटल पूर्णांक asiliantfb_check_var(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *p)
अणु
	अचिन्हित दीर्घ Ftarget, ratio, reमुख्यder;

	ratio = 1000000 / var->pixघड़ी;
	reमुख्यder = 1000000 % var->pixघड़ी;
	Ftarget = 1000000 * ratio + (1000000 * reमुख्यder) / var->pixघड़ी;

	/* First check the स्थिरraपूर्णांक that the maximum post-VCO भागisor is 32,
	 * and the maximum Fvco is 220MHz */
	अगर (Ftarget > 220000000 || Ftarget < 3125000) अणु
		prपूर्णांकk(KERN_ERR "asiliantfb dotclock must be between 3.125 and 220MHz\n");
		वापस -ENXIO;
	पूर्ण
	var->xres_भव = var->xres;
	var->yres_भव = var->yres;

	अगर (var->bits_per_pixel == 24) अणु
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = var->blue.length = var->green.length = 8;
	पूर्ण अन्यथा अगर (var->bits_per_pixel == 16) अणु
		चयन (var->red.offset) अणु
			हाल 11:
				var->green.length = 6;
				अवरोध;
			हाल 10:
				var->green.length = 5;
				अवरोध;
			शेष:
				वापस -EINVAL;
		पूर्ण
		var->green.offset = 5;
		var->blue.offset = 0;
		var->red.length = var->blue.length = 5;
	पूर्ण अन्यथा अगर (var->bits_per_pixel == 8) अणु
		var->red.offset = var->green.offset = var->blue.offset = 0;
		var->red.length = var->green.length = var->blue.length = 8;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक asiliantfb_set_par(काष्ठा fb_info *p)
अणु
	u8 dclk2_m;		/* Holds m-2 value क्रम रेजिस्टर */
	u8 dclk2_n;		/* Holds n-2 value क्रम रेजिस्टर */
	u8 dclk2_भाग;		/* Holds भागisor biपंचांगask */

	/* Set pixघड़ी */
	asiliant_calc_dclk2(&p->var.pixघड़ी, &dclk2_m, &dclk2_n, &dclk2_भाग);

	/* Set color depth */
	अगर (p->var.bits_per_pixel == 24) अणु
		ग_लिखो_xr(0x81, 0x16);	/* 24 bit packed color mode */
		ग_लिखो_xr(0x82, 0x00);	/* Disable palettes */
		ग_लिखो_xr(0x20, 0x20);	/* 24 bit blitter mode */
	पूर्ण अन्यथा अगर (p->var.bits_per_pixel == 16) अणु
		अगर (p->var.red.offset == 11)
			ग_लिखो_xr(0x81, 0x15);	/* 16 bit color mode */
		अन्यथा
			ग_लिखो_xr(0x81, 0x14);	/* 15 bit color mode */
		ग_लिखो_xr(0x82, 0x00);	/* Disable palettes */
		ग_लिखो_xr(0x20, 0x10);	/* 16 bit blitter mode */
	पूर्ण अन्यथा अगर (p->var.bits_per_pixel == 8) अणु
		ग_लिखो_xr(0x0a, 0x02);	/* Linear */
		ग_लिखो_xr(0x81, 0x12);	/* 8 bit color mode */
		ग_लिखो_xr(0x82, 0x00);	/* Graphics gamma enable */
		ग_लिखो_xr(0x20, 0x00);	/* 8 bit blitter mode */
	पूर्ण
	p->fix.line_length = p->var.xres * (p->var.bits_per_pixel >> 3);
	p->fix.visual = (p->var.bits_per_pixel == 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	ग_लिखो_xr(0xc4, dclk2_m);
	ग_लिखो_xr(0xc5, dclk2_n);
	ग_लिखो_xr(0xc7, dclk2_भाग);
	/* Set up the CR रेजिस्टरs */
	asiliant_set_timing(p);
	वापस 0;
पूर्ण

अटल पूर्णांक asiliantfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			     u_पूर्णांक transp, काष्ठा fb_info *p)
अणु
	अगर (regno > 255)
		वापस 1;
	red >>= 8;
	green >>= 8;
	blue >>= 8;

        /* Set hardware palete */
	ग_लिखोb(regno, mmio_base + 0x790);
	udelay(1);
	ग_लिखोb(red, mmio_base + 0x791);
	ग_लिखोb(green, mmio_base + 0x791);
	ग_लिखोb(blue, mmio_base + 0x791);

	अगर (regno < 16) अणु
		चयन(p->var.red.offset) अणु
		हाल 10: /* RGB 555 */
			((u32 *)(p->pseuकरो_palette))[regno] =
				((red & 0xf8) << 7) |
				((green & 0xf8) << 2) |
				((blue & 0xf8) >> 3);
			अवरोध;
		हाल 11: /* RGB 565 */
			((u32 *)(p->pseuकरो_palette))[regno] =
				((red & 0xf8) << 8) |
				((green & 0xfc) << 3) |
				((blue & 0xf8) >> 3);
			अवरोध;
		हाल 16: /* RGB 888 */
			((u32 *)(p->pseuकरो_palette))[regno] =
				(red << 16)  |
				(green << 8) |
				(blue);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा chips_init_reg अणु
	अचिन्हित अक्षर addr;
	अचिन्हित अक्षर data;
पूर्ण;

अटल काष्ठा chips_init_reg chips_init_sr[] =
अणु
	अणु0x00, 0x03पूर्ण,		/* Reset रेजिस्टर */
	अणु0x01, 0x01पूर्ण,		/* Clocking mode */
	अणु0x02, 0x0fपूर्ण,		/* Plane mask */
	अणु0x04, 0x0eपूर्ण		/* Memory mode */
पूर्ण;

अटल काष्ठा chips_init_reg chips_init_gr[] =
अणु
        अणु0x03, 0x00पूर्ण,		/* Data rotate */
	अणु0x05, 0x00पूर्ण,		/* Graphics mode */
	अणु0x06, 0x01पूर्ण,		/* Miscellaneous */
	अणु0x08, 0x00पूर्ण		/* Bit mask */
पूर्ण;

अटल काष्ठा chips_init_reg chips_init_ar[] =
अणु
	अणु0x10, 0x01पूर्ण,		/* Mode control */
	अणु0x11, 0x00पूर्ण,		/* Overscan */
	अणु0x12, 0x0fपूर्ण,		/* Memory plane enable */
	अणु0x13, 0x00पूर्ण		/* Horizontal pixel panning */
पूर्ण;

अटल काष्ठा chips_init_reg chips_init_cr[] =
अणु
	अणु0x0c, 0x00पूर्ण,		/* Start address high */
	अणु0x0d, 0x00पूर्ण,		/* Start address low */
	अणु0x40, 0x00पूर्ण,		/* Extended Start Address */
	अणु0x41, 0x00पूर्ण,		/* Extended Start Address */
	अणु0x14, 0x00पूर्ण,		/* Underline location */
	अणु0x17, 0xe3पूर्ण,		/* CRT mode control */
	अणु0x70, 0x00पूर्ण		/* Interlace control */
पूर्ण;


अटल काष्ठा chips_init_reg chips_init_fr[] =
अणु
	अणु0x01, 0x02पूर्ण,
	अणु0x03, 0x08पूर्ण,
	अणु0x08, 0xccपूर्ण,
	अणु0x0a, 0x08पूर्ण,
	अणु0x18, 0x00पूर्ण,
	अणु0x1e, 0x80पूर्ण,
	अणु0x40, 0x83पूर्ण,
	अणु0x41, 0x00पूर्ण,
	अणु0x48, 0x13पूर्ण,
	अणु0x4d, 0x60पूर्ण,
	अणु0x4e, 0x0fपूर्ण,

	अणु0x0b, 0x01पूर्ण,

	अणु0x21, 0x51पूर्ण,
	अणु0x22, 0x1dपूर्ण,
	अणु0x23, 0x5fपूर्ण,
	अणु0x20, 0x4fपूर्ण,
	अणु0x34, 0x00पूर्ण,
	अणु0x24, 0x51पूर्ण,
	अणु0x25, 0x00पूर्ण,
	अणु0x27, 0x0bपूर्ण,
	अणु0x26, 0x00पूर्ण,
	अणु0x37, 0x80पूर्ण,
	अणु0x33, 0x0bपूर्ण,
	अणु0x35, 0x11पूर्ण,
	अणु0x36, 0x02पूर्ण,
	अणु0x31, 0xeaपूर्ण,
	अणु0x32, 0x0cपूर्ण,
	अणु0x30, 0xdfपूर्ण,
	अणु0x10, 0x0cपूर्ण,
	अणु0x11, 0xe0पूर्ण,
	अणु0x12, 0x50पूर्ण,
	अणु0x13, 0x00पूर्ण,
	अणु0x16, 0x03पूर्ण,
	अणु0x17, 0xbdपूर्ण,
	अणु0x1a, 0x00पूर्ण,
पूर्ण;


अटल काष्ठा chips_init_reg chips_init_xr[] =
अणु
	अणु0xce, 0x00पूर्ण,		/* set शेष memory घड़ी */
	अणु0xcc, 200 पूर्ण,	        /* MCLK ratio M */
	अणु0xcd, 18  पूर्ण,	        /* MCLK ratio N */
	अणु0xce, 0x90पूर्ण,		/* MCLK भागisor = 2 */

	अणु0xc4, 209 पूर्ण,
	अणु0xc5, 118 पूर्ण,
	अणु0xc7, 32  पूर्ण,
	अणु0xcf, 0x06पूर्ण,
	अणु0x09, 0x01पूर्ण,		/* IO Control - CRT controller extensions */
	अणु0x0a, 0x02पूर्ण,		/* Frame buffer mapping */
	अणु0x0b, 0x01पूर्ण,		/* PCI burst ग_लिखो */
	अणु0x40, 0x03पूर्ण,		/* Memory access control */
	अणु0x80, 0x82पूर्ण,		/* Pixel pipeline configuration 0 */
	अणु0x81, 0x12पूर्ण,		/* Pixel pipeline configuration 1 */
	अणु0x82, 0x08पूर्ण,		/* Pixel pipeline configuration 2 */

	अणु0xd0, 0x0fपूर्ण,
	अणु0xd1, 0x01पूर्ण,
पूर्ण;

अटल व्योम chips_hw_init(काष्ठा fb_info *p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(chips_init_xr); ++i)
		ग_लिखो_xr(chips_init_xr[i].addr, chips_init_xr[i].data);
	ग_लिखो_xr(0x81, 0x12);
	ग_लिखो_xr(0x82, 0x08);
	ग_लिखो_xr(0x20, 0x00);
	क्रम (i = 0; i < ARRAY_SIZE(chips_init_sr); ++i)
		ग_लिखो_sr(chips_init_sr[i].addr, chips_init_sr[i].data);
	क्रम (i = 0; i < ARRAY_SIZE(chips_init_gr); ++i)
		ग_लिखो_gr(chips_init_gr[i].addr, chips_init_gr[i].data);
	क्रम (i = 0; i < ARRAY_SIZE(chips_init_ar); ++i)
		ग_लिखो_ar(chips_init_ar[i].addr, chips_init_ar[i].data);
	/* Enable video output in attribute index रेजिस्टर */
	ग_लिखोb(0x20, mmio_base + 0x780);
	क्रम (i = 0; i < ARRAY_SIZE(chips_init_cr); ++i)
		ग_लिखो_cr(chips_init_cr[i].addr, chips_init_cr[i].data);
	क्रम (i = 0; i < ARRAY_SIZE(chips_init_fr); ++i)
		ग_लिखो_fr(chips_init_fr[i].addr, chips_init_fr[i].data);
पूर्ण

अटल स्थिर काष्ठा fb_fix_screeninfo asiliantfb_fix = अणु
	.id =		"Asiliant 69000",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_PSEUDOCOLOR,
	.accel =	FB_ACCEL_NONE,
	.line_length =	640,
	.smem_len =	0x200000,	/* 2MB */
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo asiliantfb_var = अणु
	.xres 		= 640,
	.yres 		= 480,
	.xres_भव 	= 640,
	.yres_भव 	= 480,
	.bits_per_pixel = 8,
	.red 		= अणु .length = 8 पूर्ण,
	.green 		= अणु .length = 8 पूर्ण,
	.blue 		= अणु .length = 8 पूर्ण,
	.height 	= -1,
	.width 		= -1,
	.vmode 		= FB_VMODE_NONINTERLACED,
	.pixघड़ी 	= 39722,
	.left_margin 	= 48,
	.right_margin 	= 16,
	.upper_margin 	= 33,
	.lower_margin 	= 10,
	.hsync_len 	= 96,
	.vsync_len 	= 2,
पूर्ण;

अटल पूर्णांक init_asiliant(काष्ठा fb_info *p, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक err;

	p->fix			= asiliantfb_fix;
	p->fix.smem_start	= addr;
	p->var			= asiliantfb_var;
	p->fbops		= &asiliantfb_ops;
	p->flags		= FBINFO_DEFAULT;

	err = fb_alloc_cmap(&p->cmap, 256, 0);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "C&T 69000 fb failed to alloc cmap memory\n");
		वापस err;
	पूर्ण

	err = रेजिस्टर_framebuffer(p);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "C&T 69000 framebuffer failed to register\n");
		fb_dealloc_cmap(&p->cmap);
		वापस err;
	पूर्ण

	fb_info(p, "Asiliant 69000 frame buffer (%dK RAM detected)\n",
		p->fix.smem_len / 1024);

	ग_लिखोb(0xff, mmio_base + 0x78c);
	chips_hw_init(p);
	वापस 0;
पूर्ण

अटल पूर्णांक asiliantfb_pci_init(काष्ठा pci_dev *dp,
			       स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित दीर्घ addr, size;
	काष्ठा fb_info *p;
	पूर्णांक err;

	अगर ((dp->resource[0].flags & IORESOURCE_MEM) == 0)
		वापस -ENODEV;
	addr = pci_resource_start(dp, 0);
	size = pci_resource_len(dp, 0);
	अगर (addr == 0)
		वापस -ENODEV;
	अगर (!request_mem_region(addr, size, "asiliantfb"))
		वापस -EBUSY;

	p = framebuffer_alloc(माप(u32) * 16, &dp->dev);
	अगर (!p)	अणु
		release_mem_region(addr, size);
		वापस -ENOMEM;
	पूर्ण
	p->pseuकरो_palette = p->par;
	p->par = शून्य;

	p->screen_base = ioremap(addr, 0x800000);
	अगर (p->screen_base == शून्य) अणु
		release_mem_region(addr, size);
		framebuffer_release(p);
		वापस -ENOMEM;
	पूर्ण

	pci_ग_लिखो_config_dword(dp, 4, 0x02800083);
	ग_लिखोb(3, p->screen_base + 0x400784);

	err = init_asiliant(p, addr);
	अगर (err) अणु
		iounmap(p->screen_base);
		release_mem_region(addr, size);
		framebuffer_release(p);
		वापस err;
	पूर्ण

	pci_set_drvdata(dp, p);
	वापस 0;
पूर्ण

अटल व्योम asiliantfb_हटाओ(काष्ठा pci_dev *dp)
अणु
	काष्ठा fb_info *p = pci_get_drvdata(dp);

	unरेजिस्टर_framebuffer(p);
	fb_dealloc_cmap(&p->cmap);
	iounmap(p->screen_base);
	release_mem_region(pci_resource_start(dp, 0), pci_resource_len(dp, 0));
	framebuffer_release(p);
पूर्ण

अटल स्थिर काष्ठा pci_device_id asiliantfb_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_CT, PCI_DEVICE_ID_CT_69000, PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, asiliantfb_pci_tbl);

अटल काष्ठा pci_driver asiliantfb_driver = अणु
	.name =		"asiliantfb",
	.id_table =	asiliantfb_pci_tbl,
	.probe =	asiliantfb_pci_init,
	.हटाओ =	asiliantfb_हटाओ,
पूर्ण;

अटल पूर्णांक __init asiliantfb_init(व्योम)
अणु
	अगर (fb_get_options("asiliantfb", शून्य))
		वापस -ENODEV;

	वापस pci_रेजिस्टर_driver(&asiliantfb_driver);
पूर्ण

module_init(asiliantfb_init);

अटल व्योम __निकास asiliantfb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&asiliantfb_driver);
पूर्ण

MODULE_LICENSE("GPL");
