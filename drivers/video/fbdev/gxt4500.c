<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Frame buffer device क्रम IBM GXT4500P/6500P and GXT4000P/6000P
 * display adaptors
 *
 * Copyright (C) 2006 Paul Mackerras, IBM Corp. <paulus@samba.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/fb.h>
#समावेश <linux/console.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>

#घोषणा PCI_DEVICE_ID_IBM_GXT4500P	0x21c
#घोषणा PCI_DEVICE_ID_IBM_GXT6500P	0x21b
#घोषणा PCI_DEVICE_ID_IBM_GXT4000P	0x16e
#घोषणा PCI_DEVICE_ID_IBM_GXT6000P	0x170

/* GXT4500P रेजिस्टरs */

/* Registers in PCI config space */
#घोषणा CFG_ENDIAN0		0x40

/* Misc control/status रेजिस्टरs */
#घोषणा STATUS			0x1000
#घोषणा CTRL_REG0		0x1004
#घोषणा   CR0_HALT_DMA			0x4
#घोषणा   CR0_RASTER_RESET		0x8
#घोषणा   CR0_GEOM_RESET		0x10
#घोषणा   CR0_MEM_CTRLER_RESET		0x20

/* Framebuffer control रेजिस्टरs */
#घोषणा FB_AB_CTRL		0x1100
#घोषणा FB_CD_CTRL		0x1104
#घोषणा FB_WID_CTRL		0x1108
#घोषणा FB_Z_CTRL		0x110c
#घोषणा FB_VGA_CTRL		0x1110
#घोषणा REFRESH_AB_CTRL		0x1114
#घोषणा REFRESH_CD_CTRL		0x1118
#घोषणा FB_OVL_CTRL		0x111c
#घोषणा   FB_CTRL_TYPE			0x80000000
#घोषणा   FB_CTRL_WIDTH_MASK		0x007f0000
#घोषणा   FB_CTRL_WIDTH_SHIFT		16
#घोषणा   FB_CTRL_START_SEG_MASK	0x00003fff

#घोषणा REFRESH_START		0x1098
#घोषणा REFRESH_SIZE		0x109c

/* "Direct" framebuffer access रेजिस्टरs */
#घोषणा DFA_FB_A		0x11e0
#घोषणा DFA_FB_B		0x11e4
#घोषणा DFA_FB_C		0x11e8
#घोषणा DFA_FB_D		0x11ec
#घोषणा   DFA_FB_ENABLE			0x80000000
#घोषणा   DFA_FB_BASE_MASK		0x03f00000
#घोषणा   DFA_FB_STRIDE_1k		0x00000000
#घोषणा   DFA_FB_STRIDE_2k		0x00000010
#घोषणा   DFA_FB_STRIDE_4k		0x00000020
#घोषणा   DFA_PIX_8BIT			0x00000000
#घोषणा   DFA_PIX_16BIT_565		0x00000001
#घोषणा   DFA_PIX_16BIT_1555		0x00000002
#घोषणा   DFA_PIX_24BIT			0x00000004
#घोषणा   DFA_PIX_32BIT			0x00000005

/* maps DFA_PIX_* to pixel size in bytes */
अटल स्थिर अचिन्हित अक्षर pixsize[] = अणु
	1, 2, 2, 2, 4, 4
पूर्ण;

/* Display timing generator रेजिस्टरs */
#घोषणा DTG_CONTROL		0x1900
#घोषणा   DTG_CTL_SCREEN_REFRESH	2
#घोषणा   DTG_CTL_ENABLE		1
#घोषणा DTG_HORIZ_EXTENT	0x1904
#घोषणा DTG_HORIZ_DISPLAY	0x1908
#घोषणा DTG_HSYNC_START		0x190c
#घोषणा DTG_HSYNC_END		0x1910
#घोषणा DTG_HSYNC_END_COMP	0x1914
#घोषणा DTG_VERT_EXTENT		0x1918
#घोषणा DTG_VERT_DISPLAY	0x191c
#घोषणा DTG_VSYNC_START		0x1920
#घोषणा DTG_VSYNC_END		0x1924
#घोषणा DTG_VERT_SHORT		0x1928

/* PLL/RAMDAC रेजिस्टरs */
#घोषणा DISP_CTL		0x402c
#घोषणा   DISP_CTL_OFF			2
#घोषणा SYNC_CTL		0x4034
#घोषणा   SYNC_CTL_SYNC_ON_RGB		1
#घोषणा   SYNC_CTL_SYNC_OFF		2
#घोषणा   SYNC_CTL_HSYNC_INV		8
#घोषणा   SYNC_CTL_VSYNC_INV		0x10
#घोषणा   SYNC_CTL_HSYNC_OFF		0x20
#घोषणा   SYNC_CTL_VSYNC_OFF		0x40

#घोषणा PLL_M			0x4040
#घोषणा PLL_N			0x4044
#घोषणा PLL_POSTDIV		0x4048
#घोषणा PLL_C			0x404c

/* Hardware cursor */
#घोषणा CURSOR_X		0x4078
#घोषणा CURSOR_Y		0x407c
#घोषणा CURSOR_HOTSPOT		0x4080
#घोषणा CURSOR_MODE		0x4084
#घोषणा   CURSOR_MODE_OFF		0
#घोषणा   CURSOR_MODE_4BPP		1
#घोषणा CURSOR_PIXMAP		0x5000
#घोषणा CURSOR_CMAP		0x7400

/* Winकरोw attribute table */
#घोषणा WAT_FMT			0x4100
#घोषणा   WAT_FMT_24BIT			0
#घोषणा   WAT_FMT_16BIT_565		1
#घोषणा   WAT_FMT_16BIT_1555		2
#घोषणा   WAT_FMT_32BIT			3	/* 0 vs. 3 is a guess */
#घोषणा   WAT_FMT_8BIT_332		9
#घोषणा   WAT_FMT_8BIT			0xa
#घोषणा   WAT_FMT_NO_CMAP		4	/* ORd in to other values */
#घोषणा WAT_CMAP_OFFSET		0x4104		/* 4-bit value माला_लो << 6 */
#घोषणा WAT_CTRL		0x4108
#घोषणा   WAT_CTRL_SEL_B		1	/* select B buffer अगर 1 */
#घोषणा   WAT_CTRL_NO_INC		2
#घोषणा WAT_GAMMA_CTRL		0x410c
#घोषणा   WAT_GAMMA_DISABLE		1	/* disables gamma cmap */
#घोषणा WAT_OVL_CTRL		0x430c		/* controls overlay */

/* Indexed by DFA_PIX_* values */
अटल स्थिर अचिन्हित अक्षर watfmt[] = अणु
	WAT_FMT_8BIT, WAT_FMT_16BIT_565, WAT_FMT_16BIT_1555, 0,
	WAT_FMT_24BIT, WAT_FMT_32BIT
पूर्ण;

/* Colormap array; 1k entries of 4 bytes each */
#घोषणा CMAP			0x6000

#घोषणा पढ़ोreg(par, reg)	पढ़ोl((par)->regs + (reg))
#घोषणा ग_लिखोreg(par, reg, val)	ग_लिखोl((val), (par)->regs + (reg))

काष्ठा gxt4500_par अणु
	व्योम __iomem *regs;
	पूर्णांक wc_cookie;
	पूर्णांक pixfmt;		/* pixel क्रमmat, see DFA_PIX_* values */

	/* PLL parameters */
	पूर्णांक refclk_ps;		/* ref घड़ी period in picoseconds */
	पूर्णांक pll_m;		/* ref घड़ी भागisor */
	पूर्णांक pll_n;		/* VCO भागisor */
	पूर्णांक pll_pd1;		/* first post-भागisor */
	पूर्णांक pll_pd2;		/* second post-भागisor */

	u32 pseuकरो_palette[16];	/* used in color blits */
पूर्ण;

/* mode requested by user */
अटल अक्षर *mode_option;

/* शेष mode: 1280x1024 @ 60 Hz, 8 bpp */
अटल स्थिर काष्ठा fb_videomode शेषmode = अणु
	.refresh = 60,
	.xres = 1280,
	.yres = 1024,
	.pixघड़ी = 9295,
	.left_margin = 248,
	.right_margin = 48,
	.upper_margin = 38,
	.lower_margin = 1,
	.hsync_len = 112,
	.vsync_len = 3,
	.vmode = FB_VMODE_NONINTERLACED
पूर्ण;

/* List of supported cards */
क्रमागत gxt_cards अणु
	GXT4500P,
	GXT6500P,
	GXT4000P,
	GXT6000P
पूर्ण;

/* Card-specअगरic inक्रमmation */
अटल स्थिर काष्ठा cardinfo अणु
	पूर्णांक	refclk_ps;	/* period of PLL reference घड़ी in ps */
	स्थिर अक्षर *cardname;
पूर्ण cardinfo[] = अणु
	[GXT4500P] = अणु .refclk_ps = 9259, .cardname = "IBM GXT4500P" पूर्ण,
	[GXT6500P] = अणु .refclk_ps = 9259, .cardname = "IBM GXT6500P" पूर्ण,
	[GXT4000P] = अणु .refclk_ps = 40000, .cardname = "IBM GXT4000P" पूर्ण,
	[GXT6000P] = अणु .refclk_ps = 40000, .cardname = "IBM GXT6000P" पूर्ण,
पूर्ण;

/*
 * The refclk and VCO भागiders appear to use a linear feedback shअगरt
 * रेजिस्टर, which माला_लो reloaded when it reaches a terminal value, at
 * which poपूर्णांक the भागider output is toggled.  Thus one can obtain
 * whatever भागisor is required by putting the appropriate value पूर्णांकo
 * the reload रेजिस्टर.  For a भागisor of N, one माला_दो the value from
 * the LFSR sequence that comes N-1 places beक्रमe the terminal value
 * पूर्णांकo the reload रेजिस्टर.
 */

अटल स्थिर अचिन्हित अक्षर mभागtab[] = अणु
/* 1 */		      0x3f, 0x00, 0x20, 0x10, 0x28, 0x14, 0x2a, 0x15, 0x0a,
/* 10 */	0x25, 0x32, 0x19, 0x0c, 0x26, 0x13, 0x09, 0x04, 0x22, 0x11,
/* 20 */	0x08, 0x24, 0x12, 0x29, 0x34, 0x1a, 0x2d, 0x36, 0x1b, 0x0d,
/* 30 */	0x06, 0x23, 0x31, 0x38, 0x1c, 0x2e, 0x17, 0x0b, 0x05, 0x02,
/* 40 */	0x21, 0x30, 0x18, 0x2c, 0x16, 0x2b, 0x35, 0x3a, 0x1d, 0x0e,
/* 50 */	0x27, 0x33, 0x39, 0x3c, 0x1e, 0x2f, 0x37, 0x3b, 0x3d, 0x3e,
/* 60 */	0x1f, 0x0f, 0x07, 0x03, 0x01,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर nभागtab[] = अणु
/* 2 */		            0x00, 0x80, 0xc0, 0xe0, 0xf0, 0x78, 0xbc, 0x5e,
/* 10 */	0x2f, 0x17, 0x0b, 0x85, 0xc2, 0xe1, 0x70, 0x38, 0x9c, 0x4e,
/* 20 */	0xa7, 0xd3, 0xe9, 0xf4, 0xfa, 0xfd, 0xfe, 0x7f, 0xbf, 0xdf,
/* 30 */	0xef, 0x77, 0x3b, 0x1d, 0x8e, 0xc7, 0xe3, 0x71, 0xb8, 0xdc,
/* 40 */	0x6e, 0xb7, 0x5b, 0x2d, 0x16, 0x8b, 0xc5, 0xe2, 0xf1, 0xf8,
/* 50 */	0xfc, 0x7e, 0x3f, 0x9f, 0xcf, 0x67, 0xb3, 0xd9, 0x6c, 0xb6,
/* 60 */	0xdb, 0x6d, 0x36, 0x9b, 0x4d, 0x26, 0x13, 0x89, 0xc4, 0x62,
/* 70 */	0xb1, 0xd8, 0xec, 0xf6, 0xfb, 0x7d, 0xbe, 0x5f, 0xaf, 0x57,
/* 80 */	0x2b, 0x95, 0x4a, 0x25, 0x92, 0x49, 0xa4, 0x52, 0x29, 0x94,
/* 90 */	0xca, 0x65, 0xb2, 0x59, 0x2c, 0x96, 0xcb, 0xe5, 0xf2, 0x79,
/* 100 */	0x3c, 0x1e, 0x0f, 0x07, 0x83, 0x41, 0x20, 0x90, 0x48, 0x24,
/* 110 */	0x12, 0x09, 0x84, 0x42, 0xa1, 0x50, 0x28, 0x14, 0x8a, 0x45,
/* 120 */	0xa2, 0xd1, 0xe8, 0x74, 0xba, 0xdd, 0xee, 0xf7, 0x7b, 0x3d,
/* 130 */	0x9e, 0x4f, 0x27, 0x93, 0xc9, 0xe4, 0x72, 0x39, 0x1c, 0x0e,
/* 140 */	0x87, 0xc3, 0x61, 0x30, 0x18, 0x8c, 0xc6, 0x63, 0x31, 0x98,
/* 150 */	0xcc, 0xe6, 0x73, 0xb9, 0x5c, 0x2e, 0x97, 0x4b, 0xa5, 0xd2,
/* 160 */	0x69,
पूर्ण;

अटल पूर्णांक calc_pll(पूर्णांक period_ps, काष्ठा gxt4500_par *par)
अणु
	पूर्णांक m, n, pभाग1, pभाग2, postभाग;
	पूर्णांक pll_period, best_error, t, पूर्णांकf;

	/* only deal with range 5MHz - 300MHz */
	अगर (period_ps < 3333 || period_ps > 200000)
		वापस -1;

	best_error = 1000000;
	क्रम (pभाग1 = 1; pभाग1 <= 8; ++pभाग1) अणु
		क्रम (pभाग2 = 1; pभाग2 <= pभाग1; ++pभाग2) अणु
			postभाग = pभाग1 * pभाग2;
			pll_period = DIV_ROUND_UP(period_ps, postभाग);
			/* keep pll in range 350..600 MHz */
			अगर (pll_period < 1666 || pll_period > 2857)
				जारी;
			क्रम (m = 1; m <= 64; ++m) अणु
				पूर्णांकf = m * par->refclk_ps;
				अगर (पूर्णांकf > 500000)
					अवरोध;
				n = पूर्णांकf * postभाग / period_ps;
				अगर (n < 3 || n > 160)
					जारी;
				t = par->refclk_ps * m * postभाग / n;
				t -= period_ps;
				अगर (t >= 0 && t < best_error) अणु
					par->pll_m = m;
					par->pll_n = n;
					par->pll_pd1 = pभाग1;
					par->pll_pd2 = pभाग2;
					best_error = t;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (best_error == 1000000)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक calc_pixघड़ी(काष्ठा gxt4500_par *par)
अणु
	वापस par->refclk_ps * par->pll_m * par->pll_pd1 * par->pll_pd2
		/ par->pll_n;
पूर्ण

अटल पूर्णांक gxt4500_var_to_par(काष्ठा fb_var_screeninfo *var,
			      काष्ठा gxt4500_par *par)
अणु
	अगर (var->xres + var->xoffset > var->xres_भव ||
	    var->yres + var->yoffset > var->yres_भव ||
	    var->xres_भव > 4096)
		वापस -EINVAL;
	अगर ((var->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTERLACED)
		वापस -EINVAL;

	अगर (calc_pll(var->pixघड़ी, par) < 0)
		वापस -EINVAL;

	चयन (var->bits_per_pixel) अणु
	हाल 32:
		अगर (var->transp.length)
			par->pixfmt = DFA_PIX_32BIT;
		अन्यथा
			par->pixfmt = DFA_PIX_24BIT;
		अवरोध;
	हाल 24:
		par->pixfmt = DFA_PIX_24BIT;
		अवरोध;
	हाल 16:
		अगर (var->green.length == 5)
			par->pixfmt = DFA_PIX_16BIT_1555;
		अन्यथा
			par->pixfmt = DFA_PIX_16BIT_565;
		अवरोध;
	हाल 8:
		par->pixfmt = DFA_PIX_8BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_bitfield eightbits = अणु0, 8पूर्ण;
अटल स्थिर काष्ठा fb_bitfield nobits = अणु0, 0पूर्ण;

अटल व्योम gxt4500_unpack_pixfmt(काष्ठा fb_var_screeninfo *var,
				  पूर्णांक pixfmt)
अणु
	var->bits_per_pixel = pixsize[pixfmt] * 8;
	var->red = eightbits;
	var->green = eightbits;
	var->blue = eightbits;
	var->transp = nobits;

	चयन (pixfmt) अणु
	हाल DFA_PIX_16BIT_565:
		var->red.length = 5;
		var->green.length = 6;
		var->blue.length = 5;
		अवरोध;
	हाल DFA_PIX_16BIT_1555:
		var->red.length = 5;
		var->green.length = 5;
		var->blue.length = 5;
		var->transp.length = 1;
		अवरोध;
	हाल DFA_PIX_32BIT:
		var->transp.length = 8;
		अवरोध;
	पूर्ण
	अगर (pixfmt != DFA_PIX_8BIT) अणु
		var->blue.offset = 0;
		var->green.offset = var->blue.length;
		var->red.offset = var->green.offset + var->green.length;
		अगर (var->transp.length)
			var->transp.offset =
				var->red.offset + var->red.length;
	पूर्ण
पूर्ण

अटल पूर्णांक gxt4500_check_var(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	काष्ठा gxt4500_par par;
	पूर्णांक err;

	par = *(काष्ठा gxt4500_par *)info->par;
	err = gxt4500_var_to_par(var, &par);
	अगर (!err) अणु
		var->pixघड़ी = calc_pixघड़ी(&par);
		gxt4500_unpack_pixfmt(var, par.pixfmt);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक gxt4500_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा gxt4500_par *par = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	पूर्णांक err;
	u32 ctrlreg, पंचांगp;
	अचिन्हित पूर्णांक dfa_ctl, pixfmt, stride;
	अचिन्हित पूर्णांक wid_tiles, i;
	अचिन्हित पूर्णांक prefetch_pix, htot;
	काष्ठा gxt4500_par save_par;

	save_par = *par;
	err = gxt4500_var_to_par(var, par);
	अगर (err) अणु
		*par = save_par;
		वापस err;
	पूर्ण

	/* turn off DTG क्रम now */
	ctrlreg = पढ़ोreg(par, DTG_CONTROL);
	ctrlreg &= ~(DTG_CTL_ENABLE | DTG_CTL_SCREEN_REFRESH);
	ग_लिखोreg(par, DTG_CONTROL, ctrlreg);

	/* set PLL रेजिस्टरs */
	पंचांगp = पढ़ोreg(par, PLL_C) & ~0x7f;
	अगर (par->pll_n < 38)
		पंचांगp |= 0x29;
	अगर (par->pll_n < 69)
		पंचांगp |= 0x35;
	अन्यथा अगर (par->pll_n < 100)
		पंचांगp |= 0x76;
	अन्यथा
		पंचांगp |= 0x7e;
	ग_लिखोreg(par, PLL_C, पंचांगp);
	ग_लिखोreg(par, PLL_M, mभागtab[par->pll_m - 1]);
	ग_लिखोreg(par, PLL_N, nभागtab[par->pll_n - 2]);
	पंचांगp = ((8 - par->pll_pd2) << 3) | (8 - par->pll_pd1);
	अगर (par->pll_pd1 == 8 || par->pll_pd2 == 8) अणु
		/* work around erratum */
		ग_लिखोreg(par, PLL_POSTDIV, पंचांगp | 0x9);
		udelay(1);
	पूर्ण
	ग_लिखोreg(par, PLL_POSTDIV, पंचांगp);
	msleep(20);

	/* turn off hardware cursor */
	ग_लिखोreg(par, CURSOR_MODE, CURSOR_MODE_OFF);

	/* reset raster engine */
	ग_लिखोreg(par, CTRL_REG0, CR0_RASTER_RESET | (CR0_RASTER_RESET << 16));
	udelay(10);
	ग_लिखोreg(par, CTRL_REG0, CR0_RASTER_RESET << 16);

	/* set display timing generator रेजिस्टरs */
	htot = var->xres + var->left_margin + var->right_margin +
		var->hsync_len;
	ग_लिखोreg(par, DTG_HORIZ_EXTENT, htot - 1);
	ग_लिखोreg(par, DTG_HORIZ_DISPLAY, var->xres - 1);
	ग_लिखोreg(par, DTG_HSYNC_START, var->xres + var->right_margin - 1);
	ग_लिखोreg(par, DTG_HSYNC_END,
		 var->xres + var->right_margin + var->hsync_len - 1);
	ग_लिखोreg(par, DTG_HSYNC_END_COMP,
		 var->xres + var->right_margin + var->hsync_len - 1);
	ग_लिखोreg(par, DTG_VERT_EXTENT,
		 var->yres + var->upper_margin + var->lower_margin +
		 var->vsync_len - 1);
	ग_लिखोreg(par, DTG_VERT_DISPLAY, var->yres - 1);
	ग_लिखोreg(par, DTG_VSYNC_START, var->yres + var->lower_margin - 1);
	ग_लिखोreg(par, DTG_VSYNC_END,
		 var->yres + var->lower_margin + var->vsync_len - 1);
	prefetch_pix = 3300000 / var->pixघड़ी;
	अगर (prefetch_pix >= htot)
		prefetch_pix = htot - 1;
	ग_लिखोreg(par, DTG_VERT_SHORT, htot - prefetch_pix - 1);
	ctrlreg |= DTG_CTL_ENABLE | DTG_CTL_SCREEN_REFRESH;
	ग_लिखोreg(par, DTG_CONTROL, ctrlreg);

	/* calculate stride in DFA aperture */
	अगर (var->xres_भव > 2048) अणु
		stride = 4096;
		dfa_ctl = DFA_FB_STRIDE_4k;
	पूर्ण अन्यथा अगर (var->xres_भव > 1024) अणु
		stride = 2048;
		dfa_ctl = DFA_FB_STRIDE_2k;
	पूर्ण अन्यथा अणु
		stride = 1024;
		dfa_ctl = DFA_FB_STRIDE_1k;
	पूर्ण

	/* Set up framebuffer definition */
	wid_tiles = (var->xres_भव + 63) >> 6;

	/* XXX add proper FB allocation here someday */
	ग_लिखोreg(par, FB_AB_CTRL, FB_CTRL_TYPE | (wid_tiles << 16) | 0);
	ग_लिखोreg(par, REFRESH_AB_CTRL, FB_CTRL_TYPE | (wid_tiles << 16) | 0);
	ग_लिखोreg(par, FB_CD_CTRL, FB_CTRL_TYPE | (wid_tiles << 16) | 0);
	ग_लिखोreg(par, REFRESH_CD_CTRL, FB_CTRL_TYPE | (wid_tiles << 16) | 0);
	ग_लिखोreg(par, REFRESH_START, (var->xoffset << 16) | var->yoffset);
	ग_लिखोreg(par, REFRESH_SIZE, (var->xres << 16) | var->yres);

	/* Set up framebuffer access by CPU */

	pixfmt = par->pixfmt;
	dfa_ctl |= DFA_FB_ENABLE | pixfmt;
	ग_लिखोreg(par, DFA_FB_A, dfa_ctl);

	/*
	 * Set up winकरोw attribute table.
	 * We set all WAT entries the same so it करोesn't matter what the
	 * winकरोw ID (WID) plane contains.
	 */
	क्रम (i = 0; i < 32; ++i) अणु
		ग_लिखोreg(par, WAT_FMT + (i << 4), watfmt[pixfmt]);
		ग_लिखोreg(par, WAT_CMAP_OFFSET + (i << 4), 0);
		ग_लिखोreg(par, WAT_CTRL + (i << 4), 0);
		ग_लिखोreg(par, WAT_GAMMA_CTRL + (i << 4), WAT_GAMMA_DISABLE);
	पूर्ण

	/* Set sync polarity etc. */
	ctrlreg = पढ़ोreg(par, SYNC_CTL) &
		~(SYNC_CTL_SYNC_ON_RGB | SYNC_CTL_HSYNC_INV |
		  SYNC_CTL_VSYNC_INV);
	अगर (var->sync & FB_SYNC_ON_GREEN)
		ctrlreg |= SYNC_CTL_SYNC_ON_RGB;
	अगर (!(var->sync & FB_SYNC_HOR_HIGH_ACT))
		ctrlreg |= SYNC_CTL_HSYNC_INV;
	अगर (!(var->sync & FB_SYNC_VERT_HIGH_ACT))
		ctrlreg |= SYNC_CTL_VSYNC_INV;
	ग_लिखोreg(par, SYNC_CTL, ctrlreg);

	info->fix.line_length = stride * pixsize[pixfmt];
	info->fix.visual = (pixfmt == DFA_PIX_8BIT)? FB_VISUAL_PSEUDOCOLOR:
		FB_VISUAL_सूचीECTCOLOR;

	वापस 0;
पूर्ण

अटल पूर्णांक gxt4500_setcolreg(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक red,
			     अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			     अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	u32 cmap_entry;
	काष्ठा gxt4500_par *par = info->par;

	अगर (reg > 1023)
		वापस 1;
	cmap_entry = ((transp & 0xff00) << 16) | ((red & 0xff00) << 8) |
		(green & 0xff00) | (blue >> 8);
	ग_लिखोreg(par, CMAP + reg * 4, cmap_entry);

	अगर (reg < 16 && par->pixfmt != DFA_PIX_8BIT) अणु
		u32 *pal = info->pseuकरो_palette;
		u32 val = reg;
		चयन (par->pixfmt) अणु
		हाल DFA_PIX_16BIT_565:
			val |= (reg << 11) | (reg << 5);
			अवरोध;
		हाल DFA_PIX_16BIT_1555:
			val |= (reg << 10) | (reg << 5);
			अवरोध;
		हाल DFA_PIX_32BIT:
			val |= (reg << 24);
			fallthrough;
		हाल DFA_PIX_24BIT:
			val |= (reg << 16) | (reg << 8);
			अवरोध;
		पूर्ण
		pal[reg] = val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gxt4500_pan_display(काष्ठा fb_var_screeninfo *var,
			       काष्ठा fb_info *info)
अणु
	काष्ठा gxt4500_par *par = info->par;

	अगर (var->xoffset & 7)
		वापस -EINVAL;
	अगर (var->xoffset + info->var.xres > info->var.xres_भव ||
	    var->yoffset + info->var.yres > info->var.yres_भव)
		वापस -EINVAL;

	ग_लिखोreg(par, REFRESH_START, (var->xoffset << 16) | var->yoffset);
	वापस 0;
पूर्ण

अटल पूर्णांक gxt4500_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा gxt4500_par *par = info->par;
	पूर्णांक ctrl, dctl;

	ctrl = पढ़ोreg(par, SYNC_CTL);
	ctrl &= ~(SYNC_CTL_SYNC_OFF | SYNC_CTL_HSYNC_OFF | SYNC_CTL_VSYNC_OFF);
	dctl = पढ़ोreg(par, DISP_CTL);
	dctl |= DISP_CTL_OFF;
	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:
		dctl &= ~DISP_CTL_OFF;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		ctrl |= SYNC_CTL_SYNC_OFF;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		ctrl |= SYNC_CTL_HSYNC_OFF;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		ctrl |= SYNC_CTL_VSYNC_OFF;
		अवरोध;
	शेष: ;
	पूर्ण
	ग_लिखोreg(par, SYNC_CTL, ctrl);
	ग_लिखोreg(par, DISP_CTL, dctl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_fix_screeninfo gxt4500_fix = अणु
	.id = "IBM GXT4500P",
	.type = FB_TYPE_PACKED_PIXELS,
	.visual = FB_VISUAL_PSEUDOCOLOR,
	.xpanstep = 8,
	.ypanstep = 1,
	.mmio_len = 0x20000,
पूर्ण;

अटल स्थिर काष्ठा fb_ops gxt4500_ops = अणु
	.owner = THIS_MODULE,
	.fb_check_var = gxt4500_check_var,
	.fb_set_par = gxt4500_set_par,
	.fb_setcolreg = gxt4500_setcolreg,
	.fb_pan_display = gxt4500_pan_display,
	.fb_blank = gxt4500_blank,
	.fb_fillrect = cfb_fillrect,
	.fb_copyarea = cfb_copyarea,
	.fb_imageblit = cfb_imageblit,
पूर्ण;

/* PCI functions */
अटल पूर्णांक gxt4500_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ reg_phys, fb_phys;
	काष्ठा gxt4500_par *par;
	काष्ठा fb_info *info;
	काष्ठा fb_var_screeninfo var;
	क्रमागत gxt_cards cardtype;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "gxt4500: cannot enable PCI device: %d\n",
			err);
		वापस err;
	पूर्ण

	reg_phys = pci_resource_start(pdev, 0);
	अगर (!request_mem_region(reg_phys, pci_resource_len(pdev, 0),
				"gxt4500 regs")) अणु
		dev_err(&pdev->dev, "gxt4500: cannot get registers\n");
		जाओ err_nodev;
	पूर्ण

	fb_phys = pci_resource_start(pdev, 1);
	अगर (!request_mem_region(fb_phys, pci_resource_len(pdev, 1),
				"gxt4500 FB")) अणु
		dev_err(&pdev->dev, "gxt4500: cannot get framebuffer\n");
		जाओ err_मुक्त_regs;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा gxt4500_par), &pdev->dev);
	अगर (!info)
		जाओ err_मुक्त_fb;

	par = info->par;
	cardtype = ent->driver_data;
	par->refclk_ps = cardinfo[cardtype].refclk_ps;
	info->fix = gxt4500_fix;
	strlcpy(info->fix.id, cardinfo[cardtype].cardname,
		माप(info->fix.id));
	info->pseuकरो_palette = par->pseuकरो_palette;

	info->fix.mmio_start = reg_phys;
	par->regs = pci_ioremap_bar(pdev, 0);
	अगर (!par->regs) अणु
		dev_err(&pdev->dev, "gxt4500: cannot map registers\n");
		जाओ err_मुक्त_all;
	पूर्ण

	info->fix.smem_start = fb_phys;
	info->fix.smem_len = pci_resource_len(pdev, 1);
	info->screen_base = pci_ioremap_wc_bar(pdev, 1);
	अगर (!info->screen_base) अणु
		dev_err(&pdev->dev, "gxt4500: cannot map framebuffer\n");
		जाओ err_unmap_regs;
	पूर्ण

	pci_set_drvdata(pdev, info);

	par->wc_cookie = arch_phys_wc_add(info->fix.smem_start,
					  info->fix.smem_len);

#अगर_घोषित __BIG_ENDIAN
	/* Set byte-swapping क्रम DFA aperture क्रम all pixel sizes */
	pci_ग_लिखो_config_dword(pdev, CFG_ENDIAN0, 0x333300);
#अन्यथा /* __LITTLE_ENDIAN */
	/* not sure what this means but fgl23 driver करोes that */
	pci_ग_लिखो_config_dword(pdev, CFG_ENDIAN0, 0x2300);
/*	pci_ग_लिखो_config_dword(pdev, CFG_ENDIAN0 + 4, 0x400000);*/
	pci_ग_लिखो_config_dword(pdev, CFG_ENDIAN0 + 8, 0x98530000);
#पूर्ण_अगर

	info->fbops = &gxt4500_ops;
	info->flags = FBINFO_FLAG_DEFAULT | FBINFO_HWACCEL_XPAN |
					    FBINFO_HWACCEL_YPAN;

	err = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (err) अणु
		dev_err(&pdev->dev, "gxt4500: cannot allocate cmap\n");
		जाओ err_unmap_all;
	पूर्ण

	gxt4500_blank(FB_BLANK_UNBLANK, info);

	अगर (!fb_find_mode(&var, info, mode_option, शून्य, 0, &शेषmode, 8)) अणु
		dev_err(&pdev->dev, "gxt4500: cannot find valid video mode\n");
		जाओ err_मुक्त_cmap;
	पूर्ण
	info->var = var;
	अगर (gxt4500_set_par(info)) अणु
		prपूर्णांकk(KERN_ERR "gxt4500: cannot set video mode\n");
		जाओ err_मुक्त_cmap;
	पूर्ण

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		dev_err(&pdev->dev, "gxt4500: cannot register framebuffer\n");
		जाओ err_मुक्त_cmap;
	पूर्ण
	fb_info(info, "%s frame buffer device\n", info->fix.id);

	वापस 0;

 err_मुक्त_cmap:
	fb_dealloc_cmap(&info->cmap);
 err_unmap_all:
	iounmap(info->screen_base);
 err_unmap_regs:
	iounmap(par->regs);
 err_मुक्त_all:
	framebuffer_release(info);
 err_मुक्त_fb:
	release_mem_region(fb_phys, pci_resource_len(pdev, 1));
 err_मुक्त_regs:
	release_mem_region(reg_phys, pci_resource_len(pdev, 0));
 err_nodev:
	वापस -ENODEV;
पूर्ण

अटल व्योम gxt4500_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा gxt4500_par *par;

	अगर (!info)
		वापस;
	par = info->par;
	unरेजिस्टर_framebuffer(info);
	arch_phys_wc_del(par->wc_cookie);
	fb_dealloc_cmap(&info->cmap);
	iounmap(par->regs);
	iounmap(info->screen_base);
	release_mem_region(pci_resource_start(pdev, 0),
			   pci_resource_len(pdev, 0));
	release_mem_region(pci_resource_start(pdev, 1),
			   pci_resource_len(pdev, 1));
	framebuffer_release(info);
पूर्ण

/* supported chipsets */
अटल स्थिर काष्ठा pci_device_id gxt4500_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_GXT4500P),
	  .driver_data = GXT4500P पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_GXT6500P),
	  .driver_data = GXT6500P पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_GXT4000P),
	  .driver_data = GXT4000P पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_GXT6000P),
	  .driver_data = GXT6000P पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, gxt4500_pci_tbl);

अटल काष्ठा pci_driver gxt4500_driver = अणु
	.name = "gxt4500",
	.id_table = gxt4500_pci_tbl,
	.probe = gxt4500_probe,
	.हटाओ = gxt4500_हटाओ,
पूर्ण;

अटल पूर्णांक gxt4500_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अगर (fb_get_options("gxt4500", &mode_option))
		वापस -ENODEV;
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&gxt4500_driver);
पूर्ण
module_init(gxt4500_init);

अटल व्योम __निकास gxt4500_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&gxt4500_driver);
पूर्ण
module_निकास(gxt4500_निकास);

MODULE_AUTHOR("Paul Mackerras <paulus@samba.org>");
MODULE_DESCRIPTION("FBDev driver for IBM GXT4500P/6500P and GXT4000P/6000P");
MODULE_LICENSE("GPL");
module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Specify resolution as \"<xres>x<yres>[-<bpp>][@<refresh>]\"");
