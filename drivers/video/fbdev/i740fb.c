<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i740fb - framebuffer driver क्रम Intel740
 * Copyright (c) 2011 Ondrej Zary
 *
 * Based on old i740fb driver (c) 2001-2002 Andrey Ulanov <drey@rt.mipt.ru>
 * which was partially based on:
 *  VGA 16-color framebuffer driver (c) 1999 Ben Pfaff <pfaffben@debian.org>
 *	and Petr Vandrovec <VANDROVE@vc.cvut.cz>
 *  i740 driver from XFree86 (c) 1998-1999 Precision Insight, Inc., Cedar Park,
 *	Texas.
 *  i740fb by Patrick LERDA, v0.9
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/console.h>
#समावेश <video/vga.h>

#समावेश "i740_reg.h"

अटल अक्षर *mode_option;
अटल पूर्णांक mtrr = 1;

काष्ठा i740fb_par अणु
	अचिन्हित अक्षर __iomem *regs;
	bool has_sgram;
	पूर्णांक wc_cookie;
	bool ddc_रेजिस्टरed;
	काष्ठा i2c_adapter ddc_adapter;
	काष्ठा i2c_algo_bit_data ddc_algo;
	u32 pseuकरो_palette[16];
	काष्ठा mutex खोलो_lock;
	अचिन्हित पूर्णांक ref_count;

	u8 crtc[VGA_CRT_C];
	u8 atc[VGA_ATT_C];
	u8 gdc[VGA_GFX_C];
	u8 seq[VGA_SEQ_C];
	u8 misc;
	u8 vss;

	/* i740 specअगरic रेजिस्टरs */
	u8 display_cntl;
	u8 pixelpipe_cfg0;
	u8 pixelpipe_cfg1;
	u8 pixelpipe_cfg2;
	u8 video_clk2_m;
	u8 video_clk2_n;
	u8 video_clk2_mn_msbs;
	u8 video_clk2_भाग_sel;
	u8 pll_cntl;
	u8 address_mapping;
	u8 io_cntl;
	u8 bitblt_cntl;
	u8 ext_vert_total;
	u8 ext_vert_disp_end;
	u8 ext_vert_sync_start;
	u8 ext_vert_blank_start;
	u8 ext_horiz_total;
	u8 ext_horiz_blank;
	u8 ext_offset;
	u8 पूर्णांकerlace_cntl;
	u32 lmi_fअगरo_watermark;
	u8 ext_start_addr;
	u8 ext_start_addr_hi;
पूर्ण;

#घोषणा DACSPEED8	203
#घोषणा DACSPEED16	163
#घोषणा DACSPEED24_SG	136
#घोषणा DACSPEED24_SD	128
#घोषणा DACSPEED32	86

अटल स्थिर काष्ठा fb_fix_screeninfo i740fb_fix = अणु
	.id =		"i740fb",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_TRUECOLOR,
	.xpanstep =	8,
	.ypanstep =	1,
	.accel =	FB_ACCEL_NONE,
पूर्ण;

अटल अंतरभूत व्योम i740outb(काष्ठा i740fb_par *par, u16 port, u8 val)
अणु
	vga_mm_w(par->regs, port, val);
पूर्ण
अटल अंतरभूत u8 i740inb(काष्ठा i740fb_par *par, u16 port)
अणु
	वापस vga_mm_r(par->regs, port);
पूर्ण
अटल अंतरभूत व्योम i740outreg(काष्ठा i740fb_par *par, u16 port, u8 reg, u8 val)
अणु
	vga_mm_w_fast(par->regs, port, reg, val);
पूर्ण
अटल अंतरभूत u8 i740inreg(काष्ठा i740fb_par *par, u16 port, u8 reg)
अणु
	vga_mm_w(par->regs, port, reg);
	वापस vga_mm_r(par->regs, port+1);
पूर्ण
अटल अंतरभूत व्योम i740outreg_mask(काष्ठा i740fb_par *par, u16 port, u8 reg,
				   u8 val, u8 mask)
अणु
	vga_mm_w_fast(par->regs, port, reg, (val & mask)
		| (i740inreg(par, port, reg) & ~mask));
पूर्ण

#घोषणा REG_DDC_DRIVE	0x62
#घोषणा REG_DDC_STATE	0x63
#घोषणा DDC_SCL		(1 << 3)
#घोषणा DDC_SDA		(1 << 2)

अटल व्योम i740fb_ddc_setscl(व्योम *data, पूर्णांक val)
अणु
	काष्ठा i740fb_par *par = data;

	i740outreg_mask(par, XRX, REG_DDC_DRIVE, DDC_SCL, DDC_SCL);
	i740outreg_mask(par, XRX, REG_DDC_STATE, val ? DDC_SCL : 0, DDC_SCL);
पूर्ण

अटल व्योम i740fb_ddc_setsda(व्योम *data, पूर्णांक val)
अणु
	काष्ठा i740fb_par *par = data;

	i740outreg_mask(par, XRX, REG_DDC_DRIVE, DDC_SDA, DDC_SDA);
	i740outreg_mask(par, XRX, REG_DDC_STATE, val ? DDC_SDA : 0, DDC_SDA);
पूर्ण

अटल पूर्णांक i740fb_ddc_माला_लोcl(व्योम *data)
अणु
	काष्ठा i740fb_par *par = data;

	i740outreg_mask(par, XRX, REG_DDC_DRIVE, 0, DDC_SCL);

	वापस !!(i740inreg(par, XRX, REG_DDC_STATE) & DDC_SCL);
पूर्ण

अटल पूर्णांक i740fb_ddc_माला_लोda(व्योम *data)
अणु
	काष्ठा i740fb_par *par = data;

	i740outreg_mask(par, XRX, REG_DDC_DRIVE, 0, DDC_SDA);

	वापस !!(i740inreg(par, XRX, REG_DDC_STATE) & DDC_SDA);
पूर्ण

अटल पूर्णांक i740fb_setup_ddc_bus(काष्ठा fb_info *info)
अणु
	काष्ठा i740fb_par *par = info->par;

	strlcpy(par->ddc_adapter.name, info->fix.id,
		माप(par->ddc_adapter.name));
	par->ddc_adapter.owner		= THIS_MODULE;
	par->ddc_adapter.class		= I2C_CLASS_DDC;
	par->ddc_adapter.algo_data	= &par->ddc_algo;
	par->ddc_adapter.dev.parent	= info->device;
	par->ddc_algo.setsda		= i740fb_ddc_setsda;
	par->ddc_algo.setscl		= i740fb_ddc_setscl;
	par->ddc_algo.माला_लोda		= i740fb_ddc_माला_लोda;
	par->ddc_algo.माला_लोcl		= i740fb_ddc_माला_लोcl;
	par->ddc_algo.udelay		= 10;
	par->ddc_algo.समयout		= 20;
	par->ddc_algo.data		= par;

	i2c_set_adapdata(&par->ddc_adapter, par);

	वापस i2c_bit_add_bus(&par->ddc_adapter);
पूर्ण

अटल पूर्णांक i740fb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा i740fb_par *par = info->par;

	mutex_lock(&(par->खोलो_lock));
	par->ref_count++;
	mutex_unlock(&(par->खोलो_lock));

	वापस 0;
पूर्ण

अटल पूर्णांक i740fb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा i740fb_par *par = info->par;

	mutex_lock(&(par->खोलो_lock));
	अगर (par->ref_count == 0) अणु
		fb_err(info, "release called with zero refcount\n");
		mutex_unlock(&(par->खोलो_lock));
		वापस -EINVAL;
	पूर्ण

	par->ref_count--;
	mutex_unlock(&(par->खोलो_lock));

	वापस 0;
पूर्ण

अटल u32 i740_calc_fअगरo(काष्ठा i740fb_par *par, u32 freq, पूर्णांक bpp)
अणु
	/*
	 * Would like to calculate these values स्वतःmatically, but a generic
	 * algorithm करोes not seem possible.  Note: These FIFO water mark
	 * values were tested on several cards and seem to eliminate the
	 * all of the snow and vertical banding, but fine adjusपंचांगents will
	 * probably be required क्रम other cards.
	 */

	u32 wm;

	चयन (bpp) अणु
	हाल 8:
		अगर	(freq > 200)
			wm = 0x18120000;
		अन्यथा अगर (freq > 175)
			wm = 0x16110000;
		अन्यथा अगर (freq > 135)
			wm = 0x120E0000;
		अन्यथा
			wm = 0x100D0000;
		अवरोध;
	हाल 15:
	हाल 16:
		अगर (par->has_sgram) अणु
			अगर	(freq > 140)
				wm = 0x2C1D0000;
			अन्यथा अगर (freq > 120)
				wm = 0x2C180000;
			अन्यथा अगर (freq > 100)
				wm = 0x24160000;
			अन्यथा अगर (freq >  90)
				wm = 0x18120000;
			अन्यथा अगर (freq >  50)
				wm = 0x16110000;
			अन्यथा अगर (freq >  32)
				wm = 0x13100000;
			अन्यथा
				wm = 0x120E0000;
		पूर्ण अन्यथा अणु
			अगर	(freq > 160)
				wm = 0x28200000;
			अन्यथा अगर (freq > 140)
				wm = 0x2A1E0000;
			अन्यथा अगर (freq > 130)
				wm = 0x2B1A0000;
			अन्यथा अगर (freq > 120)
				wm = 0x2C180000;
			अन्यथा अगर (freq > 100)
				wm = 0x24180000;
			अन्यथा अगर (freq >  90)
				wm = 0x18120000;
			अन्यथा अगर (freq >  50)
				wm = 0x16110000;
			अन्यथा अगर (freq >  32)
				wm = 0x13100000;
			अन्यथा
				wm = 0x120E0000;
		पूर्ण
		अवरोध;
	हाल 24:
		अगर (par->has_sgram) अणु
			अगर	(freq > 130)
				wm = 0x31200000;
			अन्यथा अगर (freq > 120)
				wm = 0x2E200000;
			अन्यथा अगर (freq > 100)
				wm = 0x2C1D0000;
			अन्यथा अगर (freq >  80)
				wm = 0x25180000;
			अन्यथा अगर (freq >  64)
				wm = 0x24160000;
			अन्यथा अगर (freq >  49)
				wm = 0x18120000;
			अन्यथा अगर (freq >  32)
				wm = 0x16110000;
			अन्यथा
				wm = 0x13100000;
		पूर्ण अन्यथा अणु
			अगर	(freq > 120)
				wm = 0x311F0000;
			अन्यथा अगर (freq > 100)
				wm = 0x2C1D0000;
			अन्यथा अगर (freq >  80)
				wm = 0x25180000;
			अन्यथा अगर (freq >  64)
				wm = 0x24160000;
			अन्यथा अगर (freq >  49)
				wm = 0x18120000;
			अन्यथा अगर (freq >  32)
				wm = 0x16110000;
			अन्यथा
				wm = 0x13100000;
		पूर्ण
		अवरोध;
	हाल 32:
		अगर (par->has_sgram) अणु
			अगर	(freq >  80)
				wm = 0x2A200000;
			अन्यथा अगर (freq >  60)
				wm = 0x281A0000;
			अन्यथा अगर (freq >  49)
				wm = 0x25180000;
			अन्यथा अगर (freq >  32)
				wm = 0x18120000;
			अन्यथा
				wm = 0x16110000;
		पूर्ण अन्यथा अणु
			अगर	(freq >  80)
				wm = 0x29200000;
			अन्यथा अगर (freq >  60)
				wm = 0x281A0000;
			अन्यथा अगर (freq >  49)
				wm = 0x25180000;
			अन्यथा अगर (freq >  32)
				wm = 0x18120000;
			अन्यथा
				wm = 0x16110000;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस wm;
पूर्ण

/* घड़ी calculation from i740fb by Patrick LERDA */

#घोषणा I740_RFREQ		1000000
#घोषणा TARGET_MAX_N		30
#घोषणा I740_FFIX		(1 << 8)
#घोषणा I740_RFREQ_FIX		(I740_RFREQ / I740_FFIX)
#घोषणा I740_REF_FREQ		(6667 * I740_FFIX / 100)	/* 66.67 MHz */
#घोषणा I740_MAX_VCO_FREQ	(450 * I740_FFIX)		/* 450 MHz */

अटल व्योम i740_calc_vclk(u32 freq, काष्ठा i740fb_par *par)
अणु
	स्थिर u32 err_max    = freq / (200  * I740_RFREQ / I740_FFIX);
	स्थिर u32 err_target = freq / (1000 * I740_RFREQ / I740_FFIX);
	u32 err_best = 512 * I740_FFIX;
	u32 f_err, f_vco;
	पूर्णांक m_best = 0, n_best = 0, p_best = 0;
	पूर्णांक m, n;

	p_best = min(15, ilog2(I740_MAX_VCO_FREQ / (freq / I740_RFREQ_FIX)));
	f_vco = (freq * (1 << p_best)) / I740_RFREQ_FIX;
	freq = freq / I740_RFREQ_FIX;

	n = 2;
	करो अणु
		n++;
		m = ((f_vco * n) / I740_REF_FREQ + 2) / 4;

		अगर (m < 3)
			m = 3;

		अणु
			u32 f_out = (((m * I740_REF_FREQ * 4)
				 / n) + ((1 << p_best) / 2)) / (1 << p_best);

			f_err = (freq - f_out);

			अगर (असल(f_err) < err_max) अणु
				m_best = m;
				n_best = n;
				err_best = f_err;
			पूर्ण
		पूर्ण
	पूर्ण जबतक ((असल(f_err) >= err_target) &&
		 ((n <= TARGET_MAX_N) || (असल(err_best) > err_max)));

	अगर (असल(f_err) < err_target) अणु
		m_best = m;
		n_best = n;
	पूर्ण

	par->video_clk2_m = (m_best - 2) & 0xFF;
	par->video_clk2_n = (n_best - 2) & 0xFF;
	par->video_clk2_mn_msbs = ((((n_best - 2) >> 4) & VCO_N_MSBS)
				 | (((m_best - 2) >> 8) & VCO_M_MSBS));
	par->video_clk2_भाग_sel = ((p_best << 4) | REF_DIV_1);
पूर्ण

अटल पूर्णांक i740fb_decode_var(स्थिर काष्ठा fb_var_screeninfo *var,
			     काष्ठा i740fb_par *par, काष्ठा fb_info *info)
अणु
	/*
	 * Get the video params out of 'var'.
	 * If a value करोesn't fit, round it up, if it's too big, वापस -EINVAL.
	 */

	u32 xres, right, hslen, left, xtotal;
	u32 yres, lower, vslen, upper, ytotal;
	u32 vxres, xoffset, vyres, yoffset;
	u32 bpp, base, dacspeed24, mem;
	u8 r7;
	पूर्णांक i;

	dev_dbg(info->device, "decode_var: xres: %i, yres: %i, xres_v: %i, xres_v: %i\n",
		  var->xres, var->yres, var->xres_भव, var->xres_भव);
	dev_dbg(info->device, "	xoff: %i, yoff: %i, bpp: %i, graysc: %i\n",
		  var->xoffset, var->yoffset, var->bits_per_pixel,
		  var->grayscale);
	dev_dbg(info->device, "	activate: %i, nonstd: %i, vmode: %i\n",
		  var->activate, var->nonstd, var->vmode);
	dev_dbg(info->device, "	pixclock: %i, hsynclen:%i, vsynclen:%i\n",
		  var->pixघड़ी, var->hsync_len, var->vsync_len);
	dev_dbg(info->device, "	left: %i, right: %i, up:%i, lower:%i\n",
		  var->left_margin, var->right_margin, var->upper_margin,
		  var->lower_margin);


	bpp = var->bits_per_pixel;
	चयन (bpp) अणु
	हाल 1 ... 8:
		bpp = 8;
		अगर ((1000000 / var->pixघड़ी) > DACSPEED8) अणु
			dev_err(info->device, "requested pixclock %i MHz out of range (max. %i MHz at 8bpp)\n",
				1000000 / var->pixघड़ी, DACSPEED8);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 9 ... 15:
		bpp = 15;
		fallthrough;
	हाल 16:
		अगर ((1000000 / var->pixघड़ी) > DACSPEED16) अणु
			dev_err(info->device, "requested pixclock %i MHz out of range (max. %i MHz at 15/16bpp)\n",
				1000000 / var->pixघड़ी, DACSPEED16);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 17 ... 24:
		bpp = 24;
		dacspeed24 = par->has_sgram ? DACSPEED24_SG : DACSPEED24_SD;
		अगर ((1000000 / var->pixघड़ी) > dacspeed24) अणु
			dev_err(info->device, "requested pixclock %i MHz out of range (max. %i MHz at 24bpp)\n",
				1000000 / var->pixघड़ी, dacspeed24);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 25 ... 32:
		bpp = 32;
		अगर ((1000000 / var->pixघड़ी) > DACSPEED32) अणु
			dev_err(info->device, "requested pixclock %i MHz out of range (max. %i MHz at 32bpp)\n",
				1000000 / var->pixघड़ी, DACSPEED32);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	xres = ALIGN(var->xres, 8);
	vxres = ALIGN(var->xres_भव, 16);
	अगर (vxres < xres)
		vxres = xres;

	xoffset = ALIGN(var->xoffset, 8);
	अगर (xres + xoffset > vxres)
		xoffset = vxres - xres;

	left = ALIGN(var->left_margin, 8);
	right = ALIGN(var->right_margin, 8);
	hslen = ALIGN(var->hsync_len, 8);

	yres = var->yres;
	vyres = var->yres_भव;
	अगर (yres > vyres)
		vyres = yres;

	yoffset = var->yoffset;
	अगर (yres + yoffset > vyres)
		yoffset = vyres - yres;

	lower = var->lower_margin;
	vslen = var->vsync_len;
	upper = var->upper_margin;

	mem = vxres * vyres * ((bpp + 1) / 8);
	अगर (mem > info->screen_size) अणु
		dev_err(info->device, "not enough video memory (%d KB requested, %ld KB available)\n",
			mem >> 10, info->screen_size >> 10);
		वापस -ENOMEM;
	पूर्ण

	अगर (yoffset + yres > vyres)
		yoffset = vyres - yres;

	xtotal = xres + right + hslen + left;
	ytotal = yres + lower + vslen + upper;

	par->crtc[VGA_CRTC_H_TOTAL] = (xtotal >> 3) - 5;
	par->crtc[VGA_CRTC_H_DISP] = (xres >> 3) - 1;
	par->crtc[VGA_CRTC_H_BLANK_START] = ((xres + right) >> 3) - 1;
	par->crtc[VGA_CRTC_H_SYNC_START] = (xres + right) >> 3;
	par->crtc[VGA_CRTC_H_SYNC_END] = (((xres + right + hslen) >> 3) & 0x1F)
		| ((((xres + right + hslen) >> 3) & 0x20) << 2);
	par->crtc[VGA_CRTC_H_BLANK_END] = ((xres + right + hslen) >> 3 & 0x1F)
		| 0x80;

	par->crtc[VGA_CRTC_V_TOTAL] = ytotal - 2;

	r7 = 0x10;	/* disable linecompare */
	अगर (ytotal & 0x100)
		r7 |= 0x01;
	अगर (ytotal & 0x200)
		r7 |= 0x20;

	par->crtc[VGA_CRTC_PRESET_ROW] = 0;
	par->crtc[VGA_CRTC_MAX_SCAN] = 0x40;	/* 1 scanline, no linecmp */
	अगर (var->vmode & FB_VMODE_DOUBLE)
		par->crtc[VGA_CRTC_MAX_SCAN] |= 0x80;
	par->crtc[VGA_CRTC_CURSOR_START] = 0x00;
	par->crtc[VGA_CRTC_CURSOR_END] = 0x00;
	par->crtc[VGA_CRTC_CURSOR_HI] = 0x00;
	par->crtc[VGA_CRTC_CURSOR_LO] = 0x00;
	par->crtc[VGA_CRTC_V_DISP_END] = yres-1;
	अगर ((yres-1) & 0x100)
		r7 |= 0x02;
	अगर ((yres-1) & 0x200)
		r7 |= 0x40;

	par->crtc[VGA_CRTC_V_BLANK_START] = yres + lower - 1;
	par->crtc[VGA_CRTC_V_SYNC_START] = yres + lower - 1;
	अगर ((yres + lower - 1) & 0x100)
		r7 |= 0x0C;
	अगर ((yres + lower - 1) & 0x200) अणु
		par->crtc[VGA_CRTC_MAX_SCAN] |= 0x20;
		r7 |= 0x80;
	पूर्ण

	/* disabled IRQ */
	par->crtc[VGA_CRTC_V_SYNC_END] =
		((yres + lower - 1 + vslen) & 0x0F) & ~0x10;
	/* 0x7F क्रम VGA, but some SVGA chips require all 8 bits to be set */
	par->crtc[VGA_CRTC_V_BLANK_END] = (yres + lower - 1 + vslen) & 0xFF;

	par->crtc[VGA_CRTC_UNDERLINE] = 0x00;
	par->crtc[VGA_CRTC_MODE] = 0xC3 ;
	par->crtc[VGA_CRTC_LINE_COMPARE] = 0xFF;
	par->crtc[VGA_CRTC_OVERFLOW] = r7;

	par->vss = 0x00;	/* 3DA */

	क्रम (i = 0x00; i < 0x10; i++)
		par->atc[i] = i;
	par->atc[VGA_ATC_MODE] = 0x81;
	par->atc[VGA_ATC_OVERSCAN] = 0x00;	/* 0 क्रम EGA, 0xFF क्रम VGA */
	par->atc[VGA_ATC_PLANE_ENABLE] = 0x0F;
	par->atc[VGA_ATC_COLOR_PAGE] = 0x00;

	par->misc = 0xC3;
	अगर (var->sync & FB_SYNC_HOR_HIGH_ACT)
		par->misc &= ~0x40;
	अगर (var->sync & FB_SYNC_VERT_HIGH_ACT)
		par->misc &= ~0x80;

	par->seq[VGA_SEQ_CLOCK_MODE] = 0x01;
	par->seq[VGA_SEQ_PLANE_WRITE] = 0x0F;
	par->seq[VGA_SEQ_CHARACTER_MAP] = 0x00;
	par->seq[VGA_SEQ_MEMORY_MODE] = 0x06;

	par->gdc[VGA_GFX_SR_VALUE] = 0x00;
	par->gdc[VGA_GFX_SR_ENABLE] = 0x00;
	par->gdc[VGA_GFX_COMPARE_VALUE] = 0x00;
	par->gdc[VGA_GFX_DATA_ROTATE] = 0x00;
	par->gdc[VGA_GFX_PLANE_READ] = 0;
	par->gdc[VGA_GFX_MODE] = 0x02;
	par->gdc[VGA_GFX_MISC] = 0x05;
	par->gdc[VGA_GFX_COMPARE_MASK] = 0x0F;
	par->gdc[VGA_GFX_BIT_MASK] = 0xFF;

	base = (yoffset * vxres + (xoffset & ~7)) >> 2;
	चयन (bpp) अणु
	हाल 8:
		par->crtc[VGA_CRTC_OFFSET] = vxres >> 3;
		par->ext_offset = vxres >> 11;
		par->pixelpipe_cfg1 = DISPLAY_8BPP_MODE;
		par->bitblt_cntl = COLEXP_8BPP;
		अवरोध;
	हाल 15: /* 0rrrrrgg gggbbbbb */
	हाल 16: /* rrrrrggg gggbbbbb */
		par->pixelpipe_cfg1 = (var->green.length == 6) ?
			DISPLAY_16BPP_MODE : DISPLAY_15BPP_MODE;
		par->crtc[VGA_CRTC_OFFSET] = vxres >> 2;
		par->ext_offset = vxres >> 10;
		par->bitblt_cntl = COLEXP_16BPP;
		base *= 2;
		अवरोध;
	हाल 24:
		par->crtc[VGA_CRTC_OFFSET] = (vxres * 3) >> 3;
		par->ext_offset = (vxres * 3) >> 11;
		par->pixelpipe_cfg1 = DISPLAY_24BPP_MODE;
		par->bitblt_cntl = COLEXP_24BPP;
		base &= 0xFFFFFFFE; /* ...ignore the last bit. */
		base *= 3;
		अवरोध;
	हाल 32:
		par->crtc[VGA_CRTC_OFFSET] = vxres >> 1;
		par->ext_offset = vxres >> 9;
		par->pixelpipe_cfg1 = DISPLAY_32BPP_MODE;
		par->bitblt_cntl = COLEXP_RESERVED; /* Unimplemented on i740 */
		base *= 4;
		अवरोध;
	पूर्ण

	par->crtc[VGA_CRTC_START_LO] = base & 0x000000FF;
	par->crtc[VGA_CRTC_START_HI] = (base & 0x0000FF00) >>  8;
	par->ext_start_addr =
		((base & 0x003F0000) >> 16) | EXT_START_ADDR_ENABLE;
	par->ext_start_addr_hi = (base & 0x3FC00000) >> 22;

	par->pixelpipe_cfg0 = DAC_8_BIT;

	par->pixelpipe_cfg2 = DISPLAY_GAMMA_ENABLE | OVERLAY_GAMMA_ENABLE;
	par->io_cntl = EXTENDED_CRTC_CNTL;
	par->address_mapping = LINEAR_MODE_ENABLE | PAGE_MAPPING_ENABLE;
	par->display_cntl = HIRES_MODE;

	/* Set the MCLK freq */
	par->pll_cntl = PLL_MEMCLK_100000KHZ; /* 100 MHz -- use as शेष */

	/* Calculate the extended CRTC regs */
	par->ext_vert_total = (ytotal - 2) >> 8;
	par->ext_vert_disp_end = (yres - 1) >> 8;
	par->ext_vert_sync_start = (yres + lower) >> 8;
	par->ext_vert_blank_start = (yres + lower) >> 8;
	par->ext_horiz_total = ((xtotal >> 3) - 5) >> 8;
	par->ext_horiz_blank = (((xres + right) >> 3) & 0x40) >> 6;

	par->पूर्णांकerlace_cntl = INTERLACE_DISABLE;

	/* Set the overscan color to 0. (NOTE: This only affects >8bpp mode) */
	par->atc[VGA_ATC_OVERSCAN] = 0;

	/* Calculate VCLK that most बंदly matches the requested करोt घड़ी */
	i740_calc_vclk((((u32)1e9) / var->pixघड़ी) * (u32)(1e3), par);

	/* Since we program the घड़ीs ourselves, always use VCLK2. */
	par->misc |= 0x0C;

	/* Calculate the FIFO Watermark and Burst Length. */
	par->lmi_fअगरo_watermark =
		i740_calc_fअगरo(par, 1000000 / var->pixघड़ी, bpp);

	वापस 0;
पूर्ण

अटल पूर्णांक i740fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	चयन (var->bits_per_pixel) अणु
	हाल 8:
		var->red.offset	= var->green.offset = var->blue.offset = 0;
		var->red.length	= var->green.length = var->blue.length = 8;
		अवरोध;
	हाल 16:
		चयन (var->green.length) अणु
		शेष:
		हाल 5:
			var->red.offset = 10;
			var->green.offset = 5;
			var->blue.offset = 0;
			var->red.length	= 5;
			var->green.length = 5;
			var->blue.length = 5;
			अवरोध;
		हाल 6:
			var->red.offset = 11;
			var->green.offset = 5;
			var->blue.offset = 0;
			var->red.length = var->blue.length = 5;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 24:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length	= var->green.length = var->blue.length = 8;
		अवरोध;
	हाल 32:
		var->transp.offset = 24;
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->transp.length = 8;
		var->red.length = var->green.length = var->blue.length = 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (var->xres > var->xres_भव)
		var->xres_भव = var->xres;

	अगर (var->yres > var->yres_भव)
		var->yres_भव = var->yres;

	अगर (info->monspecs.hfmax && info->monspecs.vfmax &&
	    info->monspecs.dclkmax && fb_validate_mode(var, info) < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम vga_protect(काष्ठा i740fb_par *par)
अणु
	/* disable the display */
	i740outreg_mask(par, VGA_SEQ_I, VGA_SEQ_CLOCK_MODE, 0x20, 0x20);

	i740inb(par, 0x3DA);
	i740outb(par, VGA_ATT_W, 0x00);	/* enable palette access */
पूर्ण

अटल व्योम vga_unprotect(काष्ठा i740fb_par *par)
अणु
	/* reenable display */
	i740outreg_mask(par, VGA_SEQ_I, VGA_SEQ_CLOCK_MODE, 0, 0x20);

	i740inb(par, 0x3DA);
	i740outb(par, VGA_ATT_W, 0x20);	/* disable palette access */
पूर्ण

अटल पूर्णांक i740fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा i740fb_par *par = info->par;
	u32 itemp;
	पूर्णांक i;

	i = i740fb_decode_var(&info->var, par, info);
	अगर (i)
		वापस i;

	स_रखो(info->screen_base, 0, info->screen_size);

	vga_protect(par);

	i740outreg(par, XRX, DRAM_EXT_CNTL, DRAM_REFRESH_DISABLE);

	mdelay(1);

	i740outreg(par, XRX, VCLK2_VCO_M, par->video_clk2_m);
	i740outreg(par, XRX, VCLK2_VCO_N, par->video_clk2_n);
	i740outreg(par, XRX, VCLK2_VCO_MN_MSBS, par->video_clk2_mn_msbs);
	i740outreg(par, XRX, VCLK2_VCO_DIV_SEL, par->video_clk2_भाग_sel);

	i740outreg_mask(par, XRX, PIXPIPE_CONFIG_0,
			par->pixelpipe_cfg0 & DAC_8_BIT, 0x80);

	i740inb(par, 0x3DA);
	i740outb(par, 0x3C0, 0x00);

	/* update misc output रेजिस्टर */
	i740outb(par, VGA_MIS_W, par->misc | 0x01);

	/* synchronous reset on */
	i740outreg(par, VGA_SEQ_I, VGA_SEQ_RESET, 0x01);
	/* ग_लिखो sequencer रेजिस्टरs */
	i740outreg(par, VGA_SEQ_I, VGA_SEQ_CLOCK_MODE,
			par->seq[VGA_SEQ_CLOCK_MODE] | 0x20);
	क्रम (i = 2; i < VGA_SEQ_C; i++)
		i740outreg(par, VGA_SEQ_I, i, par->seq[i]);

	/* synchronous reset off */
	i740outreg(par, VGA_SEQ_I, VGA_SEQ_RESET, 0x03);

	/* deprotect CRT रेजिस्टरs 0-7 */
	i740outreg(par, VGA_CRT_IC, VGA_CRTC_V_SYNC_END,
			par->crtc[VGA_CRTC_V_SYNC_END]);

	/* ग_लिखो CRT रेजिस्टरs */
	क्रम (i = 0; i < VGA_CRT_C; i++)
		i740outreg(par, VGA_CRT_IC, i, par->crtc[i]);

	/* ग_लिखो graphics controller रेजिस्टरs */
	क्रम (i = 0; i < VGA_GFX_C; i++)
		i740outreg(par, VGA_GFX_I, i, par->gdc[i]);

	/* ग_लिखो attribute controller रेजिस्टरs */
	क्रम (i = 0; i < VGA_ATT_C; i++) अणु
		i740inb(par, VGA_IS1_RC);		/* reset flip-flop */
		i740outb(par, VGA_ATT_IW, i);
		i740outb(par, VGA_ATT_IW, par->atc[i]);
	पूर्ण

	i740inb(par, VGA_IS1_RC);
	i740outb(par, VGA_ATT_IW, 0x20);

	i740outreg(par, VGA_CRT_IC, EXT_VERT_TOTAL, par->ext_vert_total);
	i740outreg(par, VGA_CRT_IC, EXT_VERT_DISPLAY, par->ext_vert_disp_end);
	i740outreg(par, VGA_CRT_IC, EXT_VERT_SYNC_START,
			par->ext_vert_sync_start);
	i740outreg(par, VGA_CRT_IC, EXT_VERT_BLANK_START,
			par->ext_vert_blank_start);
	i740outreg(par, VGA_CRT_IC, EXT_HORIZ_TOTAL, par->ext_horiz_total);
	i740outreg(par, VGA_CRT_IC, EXT_HORIZ_BLANK, par->ext_horiz_blank);
	i740outreg(par, VGA_CRT_IC, EXT_OFFSET, par->ext_offset);
	i740outreg(par, VGA_CRT_IC, EXT_START_ADDR_HI, par->ext_start_addr_hi);
	i740outreg(par, VGA_CRT_IC, EXT_START_ADDR, par->ext_start_addr);

	i740outreg_mask(par, VGA_CRT_IC, INTERLACE_CNTL,
			par->पूर्णांकerlace_cntl, INTERLACE_ENABLE);
	i740outreg_mask(par, XRX, ADDRESS_MAPPING, par->address_mapping, 0x1F);
	i740outreg_mask(par, XRX, BITBLT_CNTL, par->bitblt_cntl, COLEXP_MODE);
	i740outreg_mask(par, XRX, DISPLAY_CNTL,
			par->display_cntl, VGA_WRAP_MODE | GUI_MODE);
	i740outreg_mask(par, XRX, PIXPIPE_CONFIG_0, par->pixelpipe_cfg0, 0x9B);
	i740outreg_mask(par, XRX, PIXPIPE_CONFIG_2, par->pixelpipe_cfg2, 0x0C);

	i740outreg(par, XRX, PLL_CNTL, par->pll_cntl);

	i740outreg_mask(par, XRX, PIXPIPE_CONFIG_1,
			par->pixelpipe_cfg1, DISPLAY_COLOR_MODE);

	itemp = पढ़ोl(par->regs + FWATER_BLC);
	itemp &= ~(LMI_BURST_LENGTH | LMI_FIFO_WATERMARK);
	itemp |= par->lmi_fअगरo_watermark;
	ग_लिखोl(itemp, par->regs + FWATER_BLC);

	i740outreg(par, XRX, DRAM_EXT_CNTL, DRAM_REFRESH_60HZ);

	i740outreg_mask(par, MRX, COL_KEY_CNTL_1, 0, BLANK_DISP_OVERLAY);
	i740outreg_mask(par, XRX, IO_CTNL,
			par->io_cntl, EXTENDED_ATTR_CNTL | EXTENDED_CRTC_CNTL);

	अगर (par->pixelpipe_cfg1 != DISPLAY_8BPP_MODE) अणु
		i740outb(par, VGA_PEL_MSK, 0xFF);
		i740outb(par, VGA_PEL_IW, 0x00);
		क्रम (i = 0; i < 256; i++) अणु
			itemp = (par->pixelpipe_cfg0 & DAC_8_BIT) ? i : i >> 2;
			i740outb(par, VGA_PEL_D, itemp);
			i740outb(par, VGA_PEL_D, itemp);
			i740outb(par, VGA_PEL_D, itemp);
		पूर्ण
	पूर्ण

	/* Wait क्रम screen to stabilize. */
	mdelay(50);
	vga_unprotect(par);

	info->fix.line_length =
			info->var.xres_भव * info->var.bits_per_pixel / 8;
	अगर (info->var.bits_per_pixel == 8)
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
	अन्यथा
		info->fix.visual = FB_VISUAL_TRUECOLOR;

	वापस 0;
पूर्ण

अटल पूर्णांक i740fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info)
अणु
	u32 r, g, b;

	dev_dbg(info->device, "setcolreg: regno: %i, red=%d, green=%d, blue=%d, transp=%d, bpp=%d\n",
		regno, red, green, blue, transp, info->var.bits_per_pixel);

	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_PSEUDOCOLOR:
		अगर (regno >= 256)
			वापस -EINVAL;
		i740outb(info->par, VGA_PEL_IW, regno);
		i740outb(info->par, VGA_PEL_D, red >> 8);
		i740outb(info->par, VGA_PEL_D, green >> 8);
		i740outb(info->par, VGA_PEL_D, blue >> 8);
		अवरोध;
	हाल FB_VISUAL_TRUECOLOR:
		अगर (regno >= 16)
			वापस -EINVAL;
		r = (red >> (16 - info->var.red.length))
			<< info->var.red.offset;
		b = (blue >> (16 - info->var.blue.length))
			<< info->var.blue.offset;
		g = (green >> (16 - info->var.green.length))
			<< info->var.green.offset;
		((u32 *) info->pseuकरो_palette)[regno] = r | g | b;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i740fb_pan_display(काष्ठा fb_var_screeninfo *var,
				 काष्ठा fb_info *info)
अणु
	काष्ठा i740fb_par *par = info->par;
	u32 base = (var->yoffset * info->var.xres_भव
		 + (var->xoffset & ~7)) >> 2;

	dev_dbg(info->device, "pan_display: xoffset: %i yoffset: %i base: %i\n",
		var->xoffset, var->yoffset, base);

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		अवरोध;
	हाल 15:
	हाल 16:
		base *= 2;
		अवरोध;
	हाल 24:
		/*
		 * The last bit करोes not seem to have any effect on the start
		 * address रेजिस्टर in 24bpp mode, so...
		 */
		base &= 0xFFFFFFFE; /* ...ignore the last bit. */
		base *= 3;
		अवरोध;
	हाल 32:
		base *= 4;
		अवरोध;
	पूर्ण

	par->crtc[VGA_CRTC_START_LO] = base & 0x000000FF;
	par->crtc[VGA_CRTC_START_HI] = (base & 0x0000FF00) >>  8;
	par->ext_start_addr_hi = (base & 0x3FC00000) >> 22;
	par->ext_start_addr =
			((base & 0x003F0000) >> 16) | EXT_START_ADDR_ENABLE;

	i740outreg(par, VGA_CRT_IC, VGA_CRTC_START_LO,  base & 0x000000FF);
	i740outreg(par, VGA_CRT_IC, VGA_CRTC_START_HI,
			(base & 0x0000FF00) >> 8);
	i740outreg(par, VGA_CRT_IC, EXT_START_ADDR_HI,
			(base & 0x3FC00000) >> 22);
	i740outreg(par, VGA_CRT_IC, EXT_START_ADDR,
			((base & 0x003F0000) >> 16) | EXT_START_ADDR_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक i740fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा i740fb_par *par = info->par;

	अचिन्हित अक्षर SEQ01;
	पूर्णांक DPMSSyncSelect;

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
	हाल FB_BLANK_NORMAL:
		SEQ01 = 0x00;
		DPMSSyncSelect = HSYNC_ON | VSYNC_ON;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		SEQ01 = 0x20;
		DPMSSyncSelect = HSYNC_ON | VSYNC_OFF;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		SEQ01 = 0x20;
		DPMSSyncSelect = HSYNC_OFF | VSYNC_ON;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		SEQ01 = 0x20;
		DPMSSyncSelect = HSYNC_OFF | VSYNC_OFF;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	/* Turn the screen on/off */
	i740outb(par, SRX, 0x01);
	SEQ01 |= i740inb(par, SRX + 1) & ~0x20;
	i740outb(par, SRX, 0x01);
	i740outb(par, SRX + 1, SEQ01);

	/* Set the DPMS mode */
	i740outreg(par, XRX, DPMS_SYNC_SELECT, DPMSSyncSelect);

	/* Let fbcon करो a soft blank क्रम us */
	वापस (blank_mode == FB_BLANK_NORMAL) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops i740fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो	= i740fb_खोलो,
	.fb_release	= i740fb_release,
	.fb_check_var	= i740fb_check_var,
	.fb_set_par	= i740fb_set_par,
	.fb_setcolreg	= i740fb_setcolreg,
	.fb_blank	= i740fb_blank,
	.fb_pan_display	= i740fb_pan_display,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

/* ------------------------------------------------------------------------- */

अटल पूर्णांक i740fb_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा fb_info *info;
	काष्ठा i740fb_par *par;
	पूर्णांक ret, पंचांगp;
	bool found = false;
	u8 *edid;

	info = framebuffer_alloc(माप(काष्ठा i740fb_par), &(dev->dev));
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	mutex_init(&par->खोलो_lock);

	info->var.activate = FB_ACTIVATE_NOW;
	info->var.bits_per_pixel = 8;
	info->fbops = &i740fb_ops;
	info->pseuकरो_palette = par->pseuकरो_palette;

	ret = pci_enable_device(dev);
	अगर (ret) अणु
		dev_err(info->device, "cannot enable PCI device\n");
		जाओ err_enable_device;
	पूर्ण

	ret = pci_request_regions(dev, info->fix.id);
	अगर (ret) अणु
		dev_err(info->device, "error requesting regions\n");
		जाओ err_request_regions;
	पूर्ण

	info->screen_base = pci_ioremap_wc_bar(dev, 0);
	अगर (!info->screen_base) अणु
		dev_err(info->device, "error remapping base\n");
		ret = -ENOMEM;
		जाओ err_ioremap_1;
	पूर्ण

	par->regs = pci_ioremap_bar(dev, 1);
	अगर (!par->regs) अणु
		dev_err(info->device, "error remapping MMIO\n");
		ret = -ENOMEM;
		जाओ err_ioremap_2;
	पूर्ण

	/* detect memory size */
	अगर ((i740inreg(par, XRX, DRAM_ROW_TYPE) & DRAM_ROW_1)
							== DRAM_ROW_1_SDRAM)
		i740outb(par, XRX, DRAM_ROW_BNDRY_1);
	अन्यथा
		i740outb(par, XRX, DRAM_ROW_BNDRY_0);
	info->screen_size = i740inb(par, XRX + 1) * 1024 * 1024;
	/* detect memory type */
	पंचांगp = i740inreg(par, XRX, DRAM_ROW_CNTL_LO);
	par->has_sgram = !((पंचांगp & DRAM_RAS_TIMING) ||
			   (पंचांगp & DRAM_RAS_PRECHARGE));

	fb_info(info, "Intel740 on %s, %ld KB %s\n",
		pci_name(dev), info->screen_size >> 10,
		par->has_sgram ? "SGRAM" : "SDRAM");

	info->fix = i740fb_fix;
	info->fix.mmio_start = pci_resource_start(dev, 1);
	info->fix.mmio_len = pci_resource_len(dev, 1);
	info->fix.smem_start = pci_resource_start(dev, 0);
	info->fix.smem_len = info->screen_size;
	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;

	अगर (i740fb_setup_ddc_bus(info) == 0) अणु
		par->ddc_रेजिस्टरed = true;
		edid = fb_ddc_पढ़ो(&par->ddc_adapter);
		अगर (edid) अणु
			fb_edid_to_monspecs(edid, &info->monspecs);
			kमुक्त(edid);
			अगर (!info->monspecs.modedb)
				dev_err(info->device,
					"error getting mode database\n");
			अन्यथा अणु
				स्थिर काष्ठा fb_videomode *m;

				fb_videomode_to_modelist(
					info->monspecs.modedb,
					info->monspecs.modedb_len,
					&info->modelist);
				m = fb_find_best_display(&info->monspecs,
							 &info->modelist);
				अगर (m) अणु
					fb_videomode_to_var(&info->var, m);
					/* fill all other info->var's fields */
					अगर (!i740fb_check_var(&info->var, info))
						found = true;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!mode_option && !found)
		mode_option = "640x480-8@60";

	अगर (mode_option) अणु
		ret = fb_find_mode(&info->var, info, mode_option,
				   info->monspecs.modedb,
				   info->monspecs.modedb_len,
				   शून्य, info->var.bits_per_pixel);
		अगर (!ret || ret == 4) अणु
			dev_err(info->device, "mode %s not found\n",
				mode_option);
			ret = -EINVAL;
		पूर्ण
	पूर्ण

	fb_destroy_modedb(info->monspecs.modedb);
	info->monspecs.modedb = शून्य;

	/* maximize भव vertical size क्रम fast scrolling */
	info->var.yres_भव = info->fix.smem_len * 8 /
			(info->var.bits_per_pixel * info->var.xres_भव);

	अगर (ret == -EINVAL)
		जाओ err_find_mode;

	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (ret) अणु
		dev_err(info->device, "cannot allocate colormap\n");
		जाओ err_alloc_cmap;
	पूर्ण

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret) अणु
		dev_err(info->device, "error registering framebuffer\n");
		जाओ err_reg_framebuffer;
	पूर्ण

	fb_info(info, "%s frame buffer device\n", info->fix.id);
	pci_set_drvdata(dev, info);
	अगर (mtrr)
		par->wc_cookie = arch_phys_wc_add(info->fix.smem_start,
						  info->fix.smem_len);
	वापस 0;

err_reg_framebuffer:
	fb_dealloc_cmap(&info->cmap);
err_alloc_cmap:
err_find_mode:
	अगर (par->ddc_रेजिस्टरed)
		i2c_del_adapter(&par->ddc_adapter);
	pci_iounmap(dev, par->regs);
err_ioremap_2:
	pci_iounmap(dev, info->screen_base);
err_ioremap_1:
	pci_release_regions(dev);
err_request_regions:
/*	pci_disable_device(dev); */
err_enable_device:
	framebuffer_release(info);
	वापस ret;
पूर्ण

अटल व्योम i740fb_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);

	अगर (info) अणु
		काष्ठा i740fb_par *par = info->par;
		arch_phys_wc_del(par->wc_cookie);
		unरेजिस्टर_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);
		अगर (par->ddc_रेजिस्टरed)
			i2c_del_adapter(&par->ddc_adapter);
		pci_iounmap(dev, par->regs);
		pci_iounmap(dev, info->screen_base);
		pci_release_regions(dev);
/*		pci_disable_device(dev); */
		framebuffer_release(info);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused i740fb_suspend(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा i740fb_par *par = info->par;

	console_lock();
	mutex_lock(&(par->खोलो_lock));

	/* करो nothing अगर framebuffer is not active */
	अगर (par->ref_count == 0) अणु
		mutex_unlock(&(par->खोलो_lock));
		console_unlock();
		वापस 0;
	पूर्ण

	fb_set_suspend(info, 1);

	mutex_unlock(&(par->खोलो_lock));
	console_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused i740fb_resume(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा i740fb_par *par = info->par;

	console_lock();
	mutex_lock(&(par->खोलो_lock));

	अगर (par->ref_count == 0)
		जाओ fail;

	i740fb_set_par(info);
	fb_set_suspend(info, 0);

fail:
	mutex_unlock(&(par->खोलो_lock));
	console_unlock();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops i740fb_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= i740fb_suspend,
	.resume		= i740fb_resume,
	.मुक्तze		= शून्य,
	.thaw		= i740fb_resume,
	.घातeroff	= i740fb_suspend,
	.restore	= i740fb_resume,
#पूर्ण_अगर /* CONFIG_PM_SLEEP */
पूर्ण;

#घोषणा I740_ID_PCI 0x00d1
#घोषणा I740_ID_AGP 0x7800

अटल स्थिर काष्ठा pci_device_id i740fb_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, I740_ID_PCI) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, I740_ID_AGP) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, i740fb_id_table);

अटल काष्ठा pci_driver i740fb_driver = अणु
	.name		= "i740fb",
	.id_table	= i740fb_id_table,
	.probe		= i740fb_probe,
	.हटाओ		= i740fb_हटाओ,
	.driver.pm	= &i740fb_pm_ops,
पूर्ण;

#अगर_अघोषित MODULE
अटल पूर्णांक  __init i740fb_setup(अक्षर *options)
अणु
	अक्षर *opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*opt)
			जारी;
		अन्यथा अगर (!म_भेदन(opt, "mtrr:", 5))
			mtrr = simple_म_से_अदीर्घ(opt + 5, शून्य, 0);
		अन्यथा
			mode_option = opt;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init i740fb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("i740fb", &option))
		वापस -ENODEV;
	i740fb_setup(option);
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&i740fb_driver);
पूर्ण

अटल व्योम __निकास i740fb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&i740fb_driver);
पूर्ण

module_init(i740fb_init);
module_निकास(i740fb_निकास);

MODULE_AUTHOR("(c) 2011 Ondrej Zary <linux@rainbow-software.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("fbdev driver for Intel740");

module_param(mode_option, अक्षरp, 0444);
MODULE_PARM_DESC(mode_option, "Default video mode ('640x480-8@60', etc)");

module_param(mtrr, पूर्णांक, 0444);
MODULE_PARM_DESC(mtrr, "Enable write-combining with MTRR (1=enable, 0=disable, default=1)");
