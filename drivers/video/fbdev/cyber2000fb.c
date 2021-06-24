<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/video/cyber2000fb.c
 *
 *  Copyright (C) 1998-2002 Russell King
 *
 *  MIPS and 50xx घड़ी support
 *  Copyright (C) 2001 Bradley D. LaRonde <brad@ltc.com>
 *
 *  32 bit support, text color and panning fixes क्रम modes != 8 bit
 *  Copyright (C) 2002 Denis Oliver Kropp <करोk@directfb.org>
 *
 * Integraphics CyberPro 2000, 2010 and 5000 frame buffer device
 *
 * Based on cyberfb.c.
 *
 * Note that we now use the new fbcon fix, var and cmap scheme.  We करो
 * still have to check which console is the currently displayed one
 * however, especially क्रम the colourmap stuff.
 *
 * We also use the new hotplug PCI subप्रणाली.  I'm not sure अगर there
 * are any such cards, but I'm erring on the side of caution.  We don't
 * want to go pop just because someone करोes have one.
 *
 * Note that this करोesn't work fully in the हाल of multiple CyberPro
 * cards with grabbers.  We currently can only attach to the first
 * CyberPro card found.
 *
 * When we're in truecolour mode, we घातer करोwn the LUT RAM as a घातer
 * saving feature.  Also, when we enter any of the घातersaving modes
 * (except soft blanking) we घातer करोwn the RAMDACs.  This saves about
 * 1W, which is roughly 8% of the घातer consumption of a NetWinder
 * (which, incidentally, is about the same saving as a 2.5in hard disk
 * entering standby mode.)
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>


#अगर_घोषित __arm__
#समावेश <यंत्र/mach-types.h>
#पूर्ण_अगर

#समावेश "cyber2000fb.h"

काष्ठा cfb_info अणु
	काष्ठा fb_info		fb;
	काष्ठा display_चयन	*dispsw;
	अचिन्हित अक्षर		__iomem *region;
	अचिन्हित अक्षर		__iomem *regs;
	u_पूर्णांक			id;
	u_पूर्णांक			irq;
	पूर्णांक			func_use_count;
	u_दीर्घ			ref_ps;

	/*
	 * Clock भागisors
	 */
	u_पूर्णांक			भागisors[4];

	काष्ठा अणु
		u8 red, green, blue;
	पूर्ण palette[NR_PALETTE];

	u_अक्षर			mem_ctl1;
	u_अक्षर			mem_ctl2;
	u_अक्षर			mclk_mult;
	u_अक्षर			mclk_भाग;
	/*
	 * RAMDAC control रेजिस्टर is both of these or'ed together
	 */
	u_अक्षर			ramdac_ctrl;
	u_अक्षर			ramdac_घातerकरोwn;

	u32			pseuकरो_palette[16];

	spinlock_t		reg_b0_lock;

#अगर_घोषित CONFIG_FB_CYBER2000_DDC
	bool			ddc_रेजिस्टरed;
	काष्ठा i2c_adapter	ddc_adapter;
	काष्ठा i2c_algo_bit_data	ddc_algo;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_CYBER2000_I2C
	काष्ठा i2c_adapter	i2c_adapter;
	काष्ठा i2c_algo_bit_data i2c_algo;
#पूर्ण_अगर
पूर्ण;

अटल अक्षर *शेष_font = "Acorn8x8";
module_param(शेष_font, अक्षरp, 0);
MODULE_PARM_DESC(शेष_font, "Default font name");

/*
 * Our access methods.
 */
#घोषणा cyber2000fb_ग_लिखोl(val, reg, cfb)	ग_लिखोl(val, (cfb)->regs + (reg))
#घोषणा cyber2000fb_ग_लिखोw(val, reg, cfb)	ग_लिखोw(val, (cfb)->regs + (reg))
#घोषणा cyber2000fb_ग_लिखोb(val, reg, cfb)	ग_लिखोb(val, (cfb)->regs + (reg))

#घोषणा cyber2000fb_पढ़ोb(reg, cfb)		पढ़ोb((cfb)->regs + (reg))

अटल अंतरभूत व्योम
cyber2000_crtcw(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val, काष्ठा cfb_info *cfb)
अणु
	cyber2000fb_ग_लिखोw((reg & 255) | val << 8, 0x3d4, cfb);
पूर्ण

अटल अंतरभूत व्योम
cyber2000_grphw(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val, काष्ठा cfb_info *cfb)
अणु
	cyber2000fb_ग_लिखोw((reg & 255) | val << 8, 0x3ce, cfb);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
cyber2000_grphr(अचिन्हित पूर्णांक reg, काष्ठा cfb_info *cfb)
अणु
	cyber2000fb_ग_लिखोb(reg, 0x3ce, cfb);
	वापस cyber2000fb_पढ़ोb(0x3cf, cfb);
पूर्ण

अटल अंतरभूत व्योम
cyber2000_attrw(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val, काष्ठा cfb_info *cfb)
अणु
	cyber2000fb_पढ़ोb(0x3da, cfb);
	cyber2000fb_ग_लिखोb(reg, 0x3c0, cfb);
	cyber2000fb_पढ़ोb(0x3c1, cfb);
	cyber2000fb_ग_लिखोb(val, 0x3c0, cfb);
पूर्ण

अटल अंतरभूत व्योम
cyber2000_seqw(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val, काष्ठा cfb_info *cfb)
अणु
	cyber2000fb_ग_लिखोw((reg & 255) | val << 8, 0x3c4, cfb);
पूर्ण

/* -------------------- Hardware specअगरic routines ------------------------- */

/*
 * Hardware Cyber2000 Acceleration
 */
अटल व्योम
cyber2000fb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा cfb_info *cfb = container_of(info, काष्ठा cfb_info, fb);
	अचिन्हित दीर्घ dst, col;

	अगर (!(cfb->fb.var.accel_flags & FB_ACCELF_TEXT)) अणु
		cfb_fillrect(info, rect);
		वापस;
	पूर्ण

	cyber2000fb_ग_लिखोb(0, CO_REG_CONTROL, cfb);
	cyber2000fb_ग_लिखोw(rect->width - 1, CO_REG_PIXWIDTH, cfb);
	cyber2000fb_ग_लिखोw(rect->height - 1, CO_REG_PIXHEIGHT, cfb);

	col = rect->color;
	अगर (cfb->fb.var.bits_per_pixel > 8)
		col = ((u32 *)cfb->fb.pseuकरो_palette)[col];
	cyber2000fb_ग_लिखोl(col, CO_REG_FGCOLOUR, cfb);

	dst = rect->dx + rect->dy * cfb->fb.var.xres_भव;
	अगर (cfb->fb.var.bits_per_pixel == 24) अणु
		cyber2000fb_ग_लिखोb(dst, CO_REG_X_PHASE, cfb);
		dst *= 3;
	पूर्ण

	cyber2000fb_ग_लिखोl(dst, CO_REG_DEST_PTR, cfb);
	cyber2000fb_ग_लिखोb(CO_FG_MIX_SRC, CO_REG_FGMIX, cfb);
	cyber2000fb_ग_लिखोw(CO_CMD_L_PATTERN_FGCOL, CO_REG_CMD_L, cfb);
	cyber2000fb_ग_लिखोw(CO_CMD_H_BLITTER, CO_REG_CMD_H, cfb);
पूर्ण

अटल व्योम
cyber2000fb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *region)
अणु
	काष्ठा cfb_info *cfb = container_of(info, काष्ठा cfb_info, fb);
	अचिन्हित पूर्णांक cmd = CO_CMD_L_PATTERN_FGCOL;
	अचिन्हित दीर्घ src, dst;

	अगर (!(cfb->fb.var.accel_flags & FB_ACCELF_TEXT)) अणु
		cfb_copyarea(info, region);
		वापस;
	पूर्ण

	cyber2000fb_ग_लिखोb(0, CO_REG_CONTROL, cfb);
	cyber2000fb_ग_लिखोw(region->width - 1, CO_REG_PIXWIDTH, cfb);
	cyber2000fb_ग_लिखोw(region->height - 1, CO_REG_PIXHEIGHT, cfb);

	src = region->sx + region->sy * cfb->fb.var.xres_भव;
	dst = region->dx + region->dy * cfb->fb.var.xres_भव;

	अगर (region->sx < region->dx) अणु
		src += region->width - 1;
		dst += region->width - 1;
		cmd |= CO_CMD_L_INC_LEFT;
	पूर्ण

	अगर (region->sy < region->dy) अणु
		src += (region->height - 1) * cfb->fb.var.xres_भव;
		dst += (region->height - 1) * cfb->fb.var.xres_भव;
		cmd |= CO_CMD_L_INC_UP;
	पूर्ण

	अगर (cfb->fb.var.bits_per_pixel == 24) अणु
		cyber2000fb_ग_लिखोb(dst, CO_REG_X_PHASE, cfb);
		src *= 3;
		dst *= 3;
	पूर्ण
	cyber2000fb_ग_लिखोl(src, CO_REG_SRC1_PTR, cfb);
	cyber2000fb_ग_लिखोl(dst, CO_REG_DEST_PTR, cfb);
	cyber2000fb_ग_लिखोw(CO_FG_MIX_SRC, CO_REG_FGMIX, cfb);
	cyber2000fb_ग_लिखोw(cmd, CO_REG_CMD_L, cfb);
	cyber2000fb_ग_लिखोw(CO_CMD_H_FGSRCMAP | CO_CMD_H_BLITTER,
			   CO_REG_CMD_H, cfb);
पूर्ण

अटल व्योम
cyber2000fb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	cfb_imageblit(info, image);
	वापस;
पूर्ण

अटल पूर्णांक cyber2000fb_sync(काष्ठा fb_info *info)
अणु
	काष्ठा cfb_info *cfb = container_of(info, काष्ठा cfb_info, fb);
	पूर्णांक count = 100000;

	अगर (!(cfb->fb.var.accel_flags & FB_ACCELF_TEXT))
		वापस 0;

	जबतक (cyber2000fb_पढ़ोb(CO_REG_CONTROL, cfb) & CO_CTRL_BUSY) अणु
		अगर (!count--) अणु
			debug_म_लिखो("accel_wait timed out\n");
			cyber2000fb_ग_लिखोb(0, CO_REG_CONTROL, cfb);
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * ===========================================================================
 */

अटल अंतरभूत u32 convert_bitfield(u_पूर्णांक val, काष्ठा fb_bitfield *bf)
अणु
	u_पूर्णांक mask = (1 << bf->length) - 1;

	वापस (val >> (16 - bf->length) & mask) << bf->offset;
पूर्ण

/*
 *    Set a single color रेजिस्टर. Return != 0 क्रम invalid regno.
 */
अटल पूर्णांक
cyber2000fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
		      u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा cfb_info *cfb = container_of(info, काष्ठा cfb_info, fb);
	काष्ठा fb_var_screeninfo *var = &cfb->fb.var;
	u32 pseuकरो_val;
	पूर्णांक ret = 1;

	चयन (cfb->fb.fix.visual) अणु
	शेष:
		वापस 1;

	/*
	 * Pseuकरोcolour:
	 *	   8     8
	 * pixel --/--+--/-->  red lut  --> red dac
	 *	      |  8
	 *	      +--/--> green lut --> green dac
	 *	      |  8
	 *	      +--/-->  blue lut --> blue dac
	 */
	हाल FB_VISUAL_PSEUDOCOLOR:
		अगर (regno >= NR_PALETTE)
			वापस 1;

		red >>= 8;
		green >>= 8;
		blue >>= 8;

		cfb->palette[regno].red = red;
		cfb->palette[regno].green = green;
		cfb->palette[regno].blue = blue;

		cyber2000fb_ग_लिखोb(regno, 0x3c8, cfb);
		cyber2000fb_ग_लिखोb(red, 0x3c9, cfb);
		cyber2000fb_ग_लिखोb(green, 0x3c9, cfb);
		cyber2000fb_ग_लिखोb(blue, 0x3c9, cfb);
		वापस 0;

	/*
	 * Direct colour:
	 *	   n     rl
	 * pixel --/--+--/-->  red lut  --> red dac
	 *	      |  gl
	 *	      +--/--> green lut --> green dac
	 *	      |  bl
	 *	      +--/-->  blue lut --> blue dac
	 * n = bpp, rl = red length, gl = green length, bl = blue length
	 */
	हाल FB_VISUAL_सूचीECTCOLOR:
		red >>= 8;
		green >>= 8;
		blue >>= 8;

		अगर (var->green.length == 6 && regno < 64) अणु
			cfb->palette[regno << 2].green = green;

			/*
			 * The 6 bits of the green component are applied
			 * to the high 6 bits of the LUT.
			 */
			cyber2000fb_ग_लिखोb(regno << 2, 0x3c8, cfb);
			cyber2000fb_ग_लिखोb(cfb->palette[regno >> 1].red,
					   0x3c9, cfb);
			cyber2000fb_ग_लिखोb(green, 0x3c9, cfb);
			cyber2000fb_ग_लिखोb(cfb->palette[regno >> 1].blue,
					   0x3c9, cfb);

			green = cfb->palette[regno << 3].green;

			ret = 0;
		पूर्ण

		अगर (var->green.length >= 5 && regno < 32) अणु
			cfb->palette[regno << 3].red = red;
			cfb->palette[regno << 3].green = green;
			cfb->palette[regno << 3].blue = blue;

			/*
			 * The 5 bits of each colour component are
			 * applied to the high 5 bits of the LUT.
			 */
			cyber2000fb_ग_लिखोb(regno << 3, 0x3c8, cfb);
			cyber2000fb_ग_लिखोb(red, 0x3c9, cfb);
			cyber2000fb_ग_लिखोb(green, 0x3c9, cfb);
			cyber2000fb_ग_लिखोb(blue, 0x3c9, cfb);
			ret = 0;
		पूर्ण

		अगर (var->green.length == 4 && regno < 16) अणु
			cfb->palette[regno << 4].red = red;
			cfb->palette[regno << 4].green = green;
			cfb->palette[regno << 4].blue = blue;

			/*
			 * The 5 bits of each colour component are
			 * applied to the high 5 bits of the LUT.
			 */
			cyber2000fb_ग_लिखोb(regno << 4, 0x3c8, cfb);
			cyber2000fb_ग_लिखोb(red, 0x3c9, cfb);
			cyber2000fb_ग_लिखोb(green, 0x3c9, cfb);
			cyber2000fb_ग_लिखोb(blue, 0x3c9, cfb);
			ret = 0;
		पूर्ण

		/*
		 * Since this is only used क्रम the first 16 colours, we
		 * करोn't have to care about overflowing क्रम regno >= 32
		 */
		pseuकरो_val = regno << var->red.offset |
			     regno << var->green.offset |
			     regno << var->blue.offset;
		अवरोध;

	/*
	 * True colour:
	 *	   n     rl
	 * pixel --/--+--/--> red dac
	 *	      |  gl
	 *	      +--/--> green dac
	 *	      |  bl
	 *	      +--/--> blue dac
	 * n = bpp, rl = red length, gl = green length, bl = blue length
	 */
	हाल FB_VISUAL_TRUECOLOR:
		pseuकरो_val = convert_bitfield(transp ^ 0xffff, &var->transp);
		pseuकरो_val |= convert_bitfield(red, &var->red);
		pseuकरो_val |= convert_bitfield(green, &var->green);
		pseuकरो_val |= convert_bitfield(blue, &var->blue);
		ret = 0;
		अवरोध;
	पूर्ण

	/*
	 * Now set our pseuकरो palette क्रम the CFB16/24/32 drivers.
	 */
	अगर (regno < 16)
		((u32 *)cfb->fb.pseuकरो_palette)[regno] = pseuकरो_val;

	वापस ret;
पूर्ण

काष्ठा par_info अणु
	/*
	 * Hardware
	 */
	u_अक्षर	घड़ी_mult;
	u_अक्षर	घड़ी_भाग;
	u_अक्षर	extseqmisc;
	u_अक्षर	co_pixfmt;
	u_अक्षर	crtc_ofl;
	u_अक्षर	crtc[19];
	u_पूर्णांक	width;
	u_पूर्णांक	pitch;
	u_पूर्णांक	fetch;

	/*
	 * Other
	 */
	u_अक्षर	ramdac;
पूर्ण;

अटल स्थिर u_अक्षर crtc_idx[] = अणु
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18
पूर्ण;

अटल व्योम cyber2000fb_ग_लिखो_ramdac_ctrl(काष्ठा cfb_info *cfb)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक val = cfb->ramdac_ctrl | cfb->ramdac_घातerकरोwn;

	cyber2000fb_ग_लिखोb(0x56, 0x3ce, cfb);
	i = cyber2000fb_पढ़ोb(0x3cf, cfb);
	cyber2000fb_ग_लिखोb(i | 4, 0x3cf, cfb);
	cyber2000fb_ग_लिखोb(val, 0x3c6, cfb);
	cyber2000fb_ग_लिखोb(i, 0x3cf, cfb);
	/* prevent card lock-up observed on x86 with CyberPro 2000 */
	cyber2000fb_पढ़ोb(0x3cf, cfb);
पूर्ण

अटल व्योम cyber2000fb_set_timing(काष्ठा cfb_info *cfb, काष्ठा par_info *hw)
अणु
	u_पूर्णांक i;

	/*
	 * Blank palette
	 */
	क्रम (i = 0; i < NR_PALETTE; i++) अणु
		cyber2000fb_ग_लिखोb(i, 0x3c8, cfb);
		cyber2000fb_ग_लिखोb(0, 0x3c9, cfb);
		cyber2000fb_ग_लिखोb(0, 0x3c9, cfb);
		cyber2000fb_ग_लिखोb(0, 0x3c9, cfb);
	पूर्ण

	cyber2000fb_ग_लिखोb(0xef, 0x3c2, cfb);
	cyber2000_crtcw(0x11, 0x0b, cfb);
	cyber2000_attrw(0x11, 0x00, cfb);

	cyber2000_seqw(0x00, 0x01, cfb);
	cyber2000_seqw(0x01, 0x01, cfb);
	cyber2000_seqw(0x02, 0x0f, cfb);
	cyber2000_seqw(0x03, 0x00, cfb);
	cyber2000_seqw(0x04, 0x0e, cfb);
	cyber2000_seqw(0x00, 0x03, cfb);

	क्रम (i = 0; i < माप(crtc_idx); i++)
		cyber2000_crtcw(crtc_idx[i], hw->crtc[i], cfb);

	क्रम (i = 0x0a; i < 0x10; i++)
		cyber2000_crtcw(i, 0, cfb);

	cyber2000_grphw(EXT_CRT_VRTOFL, hw->crtc_ofl, cfb);
	cyber2000_grphw(0x00, 0x00, cfb);
	cyber2000_grphw(0x01, 0x00, cfb);
	cyber2000_grphw(0x02, 0x00, cfb);
	cyber2000_grphw(0x03, 0x00, cfb);
	cyber2000_grphw(0x04, 0x00, cfb);
	cyber2000_grphw(0x05, 0x60, cfb);
	cyber2000_grphw(0x06, 0x05, cfb);
	cyber2000_grphw(0x07, 0x0f, cfb);
	cyber2000_grphw(0x08, 0xff, cfb);

	/* Attribute controller रेजिस्टरs */
	क्रम (i = 0; i < 16; i++)
		cyber2000_attrw(i, i, cfb);

	cyber2000_attrw(0x10, 0x01, cfb);
	cyber2000_attrw(0x11, 0x00, cfb);
	cyber2000_attrw(0x12, 0x0f, cfb);
	cyber2000_attrw(0x13, 0x00, cfb);
	cyber2000_attrw(0x14, 0x00, cfb);

	/* PLL रेजिस्टरs */
	spin_lock(&cfb->reg_b0_lock);
	cyber2000_grphw(EXT_DCLK_MULT, hw->घड़ी_mult, cfb);
	cyber2000_grphw(EXT_DCLK_DIV, hw->घड़ी_भाग, cfb);
	cyber2000_grphw(EXT_MCLK_MULT, cfb->mclk_mult, cfb);
	cyber2000_grphw(EXT_MCLK_DIV, cfb->mclk_भाग, cfb);
	cyber2000_grphw(0x90, 0x01, cfb);
	cyber2000_grphw(0xb9, 0x80, cfb);
	cyber2000_grphw(0xb9, 0x00, cfb);
	spin_unlock(&cfb->reg_b0_lock);

	cfb->ramdac_ctrl = hw->ramdac;
	cyber2000fb_ग_लिखो_ramdac_ctrl(cfb);

	cyber2000fb_ग_लिखोb(0x20, 0x3c0, cfb);
	cyber2000fb_ग_लिखोb(0xff, 0x3c6, cfb);

	cyber2000_grphw(0x14, hw->fetch, cfb);
	cyber2000_grphw(0x15, ((hw->fetch >> 8) & 0x03) |
			      ((hw->pitch >> 4) & 0x30), cfb);
	cyber2000_grphw(EXT_SEQ_MISC, hw->extseqmisc, cfb);

	/*
	 * Set up accelerator रेजिस्टरs
	 */
	cyber2000fb_ग_लिखोw(hw->width, CO_REG_SRC_WIDTH, cfb);
	cyber2000fb_ग_लिखोw(hw->width, CO_REG_DEST_WIDTH, cfb);
	cyber2000fb_ग_लिखोb(hw->co_pixfmt, CO_REG_PIXFMT, cfb);
पूर्ण

अटल अंतरभूत पूर्णांक
cyber2000fb_update_start(काष्ठा cfb_info *cfb, काष्ठा fb_var_screeninfo *var)
अणु
	u_पूर्णांक base = var->yoffset * var->xres_भव + var->xoffset;

	base *= var->bits_per_pixel;

	/*
	 * Convert to bytes and shअगरt two extra bits because DAC
	 * can only start on 4 byte aligned data.
	 */
	base >>= 5;

	अगर (base >= 1 << 20)
		वापस -EINVAL;

	cyber2000_grphw(0x10, base >> 16 | 0x10, cfb);
	cyber2000_crtcw(0x0c, base >> 8, cfb);
	cyber2000_crtcw(0x0d, base, cfb);

	वापस 0;
पूर्ण

अटल पूर्णांक
cyber2000fb_decode_crtc(काष्ठा par_info *hw, काष्ठा cfb_info *cfb,
			काष्ठा fb_var_screeninfo *var)
अणु
	u_पूर्णांक Htotal, Hblankend, Hsyncend;
	u_पूर्णांक Vtotal, Vdispend, Vblankstart, Vblankend, Vsyncstart, Vsyncend;
#घोषणा ENCODE_BIT(v, b1, m, b2) ((((v) >> (b1)) & (m)) << (b2))

	hw->crtc[13] = hw->pitch;
	hw->crtc[17] = 0xe3;
	hw->crtc[14] = 0;
	hw->crtc[8]  = 0;

	Htotal     = var->xres + var->right_margin +
		     var->hsync_len + var->left_margin;

	अगर (Htotal > 2080)
		वापस -EINVAL;

	hw->crtc[0] = (Htotal >> 3) - 5;
	hw->crtc[1] = (var->xres >> 3) - 1;
	hw->crtc[2] = var->xres >> 3;
	hw->crtc[4] = (var->xres + var->right_margin) >> 3;

	Hblankend   = (Htotal - 4 * 8) >> 3;

	hw->crtc[3] = ENCODE_BIT(Hblankend,  0, 0x1f,  0) |
		      ENCODE_BIT(1,          0, 0x01,  7);

	Hsyncend    = (var->xres + var->right_margin + var->hsync_len) >> 3;

	hw->crtc[5] = ENCODE_BIT(Hsyncend,   0, 0x1f,  0) |
		      ENCODE_BIT(Hblankend,  5, 0x01,  7);

	Vdispend    = var->yres - 1;
	Vsyncstart  = var->yres + var->lower_margin;
	Vsyncend    = var->yres + var->lower_margin + var->vsync_len;
	Vtotal      = var->yres + var->lower_margin + var->vsync_len +
		      var->upper_margin - 2;

	अगर (Vtotal > 2047)
		वापस -EINVAL;

	Vblankstart = var->yres + 6;
	Vblankend   = Vtotal - 10;

	hw->crtc[6]  = Vtotal;
	hw->crtc[7]  = ENCODE_BIT(Vtotal,     8, 0x01,  0) |
			ENCODE_BIT(Vdispend,   8, 0x01,  1) |
			ENCODE_BIT(Vsyncstart, 8, 0x01,  2) |
			ENCODE_BIT(Vblankstart, 8, 0x01,  3) |
			ENCODE_BIT(1,          0, 0x01,  4) |
			ENCODE_BIT(Vtotal,     9, 0x01,  5) |
			ENCODE_BIT(Vdispend,   9, 0x01,  6) |
			ENCODE_BIT(Vsyncstart, 9, 0x01,  7);
	hw->crtc[9]  = ENCODE_BIT(0,          0, 0x1f,  0) |
			ENCODE_BIT(Vblankstart, 9, 0x01,  5) |
			ENCODE_BIT(1,          0, 0x01,  6);
	hw->crtc[10] = Vsyncstart;
	hw->crtc[11] = ENCODE_BIT(Vsyncend,   0, 0x0f,  0) |
		       ENCODE_BIT(1,          0, 0x01,  7);
	hw->crtc[12] = Vdispend;
	hw->crtc[15] = Vblankstart;
	hw->crtc[16] = Vblankend;
	hw->crtc[18] = 0xff;

	/*
	 * overflow - graphics reg 0x11
	 * 0=VTOTAL:10 1=VDEND:10 2=VRSTART:10 3=VBSTART:10
	 * 4=LINECOMP:10 5-IVIDEO 6=FIXCNT
	 */
	hw->crtc_ofl =
		ENCODE_BIT(Vtotal, 10, 0x01, 0) |
		ENCODE_BIT(Vdispend, 10, 0x01, 1) |
		ENCODE_BIT(Vsyncstart, 10, 0x01, 2) |
		ENCODE_BIT(Vblankstart, 10, 0x01, 3) |
		EXT_CRT_VRTOFL_LINECOMP10;

	/* woody: set the पूर्णांकerlaced bit... */
	/* FIXME: what about द्विगुनscan? */
	अगर ((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED)
		hw->crtc_ofl |= EXT_CRT_VRTOFL_INTERLACE;

	वापस 0;
पूर्ण

/*
 * The following was discovered by a good monitor, bit twiddling, theorising
 * and but mostly luck.  Strangely, it looks like everyone अन्यथाs' PLL!
 *
 * Clock रेजिस्टरs:
 *   fघड़ी = fpll / भाग2
 *   fpll   = fref * mult / भाग1
 * where:
 *   fref = 14.318MHz (69842ps)
 *   mult = reg0xb0.7:0
 *   भाग1 = (reg0xb1.5:0 + 1)
 *   भाग2 =  2^(reg0xb1.7:6)
 *   fpll should be between 115 and 260 MHz
 *  (8696ps and 3846ps)
 */
अटल पूर्णांक
cyber2000fb_decode_घड़ी(काष्ठा par_info *hw, काष्ठा cfb_info *cfb,
			 काष्ठा fb_var_screeninfo *var)
अणु
	u_दीर्घ pll_ps = var->pixघड़ी;
	स्थिर u_दीर्घ ref_ps = cfb->ref_ps;
	u_पूर्णांक भाग2, t_भाग1, best_भाग1, best_mult;
	पूर्णांक best_dअगरf;
	पूर्णांक vco;

	/*
	 * Step 1:
	 *   find भाग2 such that 115MHz < fpll < 260MHz
	 *   and 0 <= भाग2 < 4
	 */
	क्रम (भाग2 = 0; भाग2 < 4; भाग2++) अणु
		u_दीर्घ new_pll;

		new_pll = pll_ps / cfb->भागisors[भाग2];
		अगर (8696 > new_pll && new_pll > 3846) अणु
			pll_ps = new_pll;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (भाग2 == 4)
		वापस -EINVAL;

	/*
	 * Step 2:
	 *  Given pll_ps and ref_ps, find:
	 *    pll_ps * 0.995 < pll_ps_calc < pll_ps * 1.005
	 *  where अणु 1 < best_भाग1 < 32, 1 < best_mult < 256 पूर्ण
	 *    pll_ps_calc = best_भाग1 / (ref_ps * best_mult)
	 */
	best_dअगरf = 0x7fffffff;
	best_mult = 2;
	best_भाग1 = 32;
	क्रम (t_भाग1 = 2; t_भाग1 < 32; t_भाग1 += 1) अणु
		u_पूर्णांक rr, t_mult, t_pll_ps;
		पूर्णांक dअगरf;

		/*
		 * Find the multiplier क्रम this भागisor
		 */
		rr = ref_ps * t_भाग1;
		t_mult = (rr + pll_ps / 2) / pll_ps;

		/*
		 * Is the multiplier within the correct range?
		 */
		अगर (t_mult > 256 || t_mult < 2)
			जारी;

		/*
		 * Calculate the actual घड़ी period from this multiplier
		 * and भागisor, and estimate the error.
		 */
		t_pll_ps = (rr + t_mult / 2) / t_mult;
		dअगरf = pll_ps - t_pll_ps;
		अगर (dअगरf < 0)
			dअगरf = -dअगरf;

		अगर (dअगरf < best_dअगरf) अणु
			best_dअगरf = dअगरf;
			best_mult = t_mult;
			best_भाग1 = t_भाग1;
		पूर्ण

		/*
		 * If we hit an exact value, there is no poपूर्णांक in continuing.
		 */
		अगर (dअगरf == 0)
			अवरोध;
	पूर्ण

	/*
	 * Step 3:
	 *  combine values
	 */
	hw->घड़ी_mult = best_mult - 1;
	hw->घड़ी_भाग  = भाग2 << 6 | (best_भाग1 - 1);

	vco = ref_ps * best_भाग1 / best_mult;
	अगर ((ref_ps == 40690) && (vco < 5556))
		/* Set VFSEL when VCO > 180MHz (5.556 ps). */
		hw->घड़ी_भाग |= EXT_DCLK_DIV_VFSEL;

	वापस 0;
पूर्ण

/*
 *    Set the User Defined Part of the Display
 */
अटल पूर्णांक
cyber2000fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा cfb_info *cfb = container_of(info, काष्ठा cfb_info, fb);
	काष्ठा par_info hw;
	अचिन्हित पूर्णांक mem;
	पूर्णांक err;

	var->transp.msb_right	= 0;
	var->red.msb_right	= 0;
	var->green.msb_right	= 0;
	var->blue.msb_right	= 0;
	var->transp.offset	= 0;
	var->transp.length	= 0;

	चयन (var->bits_per_pixel) अणु
	हाल 8:	/* PSEUDOCOLOUR, 256 */
		var->red.offset		= 0;
		var->red.length		= 8;
		var->green.offset	= 0;
		var->green.length	= 8;
		var->blue.offset	= 0;
		var->blue.length	= 8;
		अवरोध;

	हाल 16:/* सूचीECTCOLOUR, 64k or 32k */
		चयन (var->green.length) अणु
		हाल 6: /* RGB565, 64k */
			var->red.offset		= 11;
			var->red.length		= 5;
			var->green.offset	= 5;
			var->green.length	= 6;
			var->blue.offset	= 0;
			var->blue.length	= 5;
			अवरोध;

		शेष:
		हाल 5: /* RGB555, 32k */
			var->red.offset		= 10;
			var->red.length		= 5;
			var->green.offset	= 5;
			var->green.length	= 5;
			var->blue.offset	= 0;
			var->blue.length	= 5;
			अवरोध;

		हाल 4: /* RGB444, 4k + transparency? */
			var->transp.offset	= 12;
			var->transp.length	= 4;
			var->red.offset		= 8;
			var->red.length		= 4;
			var->green.offset	= 4;
			var->green.length	= 4;
			var->blue.offset	= 0;
			var->blue.length	= 4;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 24:/* TRUECOLOUR, 16m */
		var->red.offset		= 16;
		var->red.length		= 8;
		var->green.offset	= 8;
		var->green.length	= 8;
		var->blue.offset	= 0;
		var->blue.length	= 8;
		अवरोध;

	हाल 32:/* TRUECOLOUR, 16m */
		var->transp.offset	= 24;
		var->transp.length	= 8;
		var->red.offset		= 16;
		var->red.length		= 8;
		var->green.offset	= 8;
		var->green.length	= 8;
		var->blue.offset	= 0;
		var->blue.length	= 8;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	mem = var->xres_भव * var->yres_भव * (var->bits_per_pixel / 8);
	अगर (mem > cfb->fb.fix.smem_len)
		var->yres_भव = cfb->fb.fix.smem_len * 8 /
				    (var->bits_per_pixel * var->xres_भव);

	अगर (var->yres > var->yres_भव)
		var->yres = var->yres_भव;
	अगर (var->xres > var->xres_भव)
		var->xres = var->xres_भव;

	err = cyber2000fb_decode_घड़ी(&hw, cfb, var);
	अगर (err)
		वापस err;

	err = cyber2000fb_decode_crtc(&hw, cfb, var);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक cyber2000fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा cfb_info *cfb = container_of(info, काष्ठा cfb_info, fb);
	काष्ठा fb_var_screeninfo *var = &cfb->fb.var;
	काष्ठा par_info hw;
	अचिन्हित पूर्णांक mem;

	hw.width = var->xres_भव;
	hw.ramdac = RAMDAC_VREFEN | RAMDAC_DAC8BIT;

	चयन (var->bits_per_pixel) अणु
	हाल 8:
		hw.co_pixfmt		= CO_PIXFMT_8BPP;
		hw.pitch		= hw.width >> 3;
		hw.extseqmisc		= EXT_SEQ_MISC_8;
		अवरोध;

	हाल 16:
		hw.co_pixfmt		= CO_PIXFMT_16BPP;
		hw.pitch		= hw.width >> 2;

		चयन (var->green.length) अणु
		हाल 6: /* RGB565, 64k */
			hw.extseqmisc	= EXT_SEQ_MISC_16_RGB565;
			अवरोध;
		हाल 5: /* RGB555, 32k */
			hw.extseqmisc	= EXT_SEQ_MISC_16_RGB555;
			अवरोध;
		हाल 4: /* RGB444, 4k + transparency? */
			hw.extseqmisc	= EXT_SEQ_MISC_16_RGB444;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अवरोध;

	हाल 24:/* TRUECOLOUR, 16m */
		hw.co_pixfmt		= CO_PIXFMT_24BPP;
		hw.width		*= 3;
		hw.pitch		= hw.width >> 3;
		hw.ramdac		|= (RAMDAC_BYPASS | RAMDAC_RAMPWRDN);
		hw.extseqmisc		= EXT_SEQ_MISC_24_RGB888;
		अवरोध;

	हाल 32:/* TRUECOLOUR, 16m */
		hw.co_pixfmt		= CO_PIXFMT_32BPP;
		hw.pitch		= hw.width >> 1;
		hw.ramdac		|= (RAMDAC_BYPASS | RAMDAC_RAMPWRDN);
		hw.extseqmisc		= EXT_SEQ_MISC_32;
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	/*
	 * Sigh, this is असलolutely disgusting, but caused by
	 * the way the fbcon developers want to separate out
	 * the "checking" and the "setting" of the video mode.
	 *
	 * If the mode is not suitable क्रम the hardware here,
	 * we can't prevent it being set by वापसing an error.
	 *
	 * In theory, since NetWinders contain just one VGA card,
	 * we should never end up hitting this problem.
	 */
	BUG_ON(cyber2000fb_decode_घड़ी(&hw, cfb, var) != 0);
	BUG_ON(cyber2000fb_decode_crtc(&hw, cfb, var) != 0);

	hw.width -= 1;
	hw.fetch = hw.pitch;
	अगर (!(cfb->mem_ctl2 & MEM_CTL2_64BIT))
		hw.fetch <<= 1;
	hw.fetch += 1;

	cfb->fb.fix.line_length = var->xres_भव * var->bits_per_pixel / 8;

	/*
	 * Same here - अगर the size of the video mode exceeds the
	 * available RAM, we can't prevent this mode being set.
	 *
	 * In theory, since NetWinders contain just one VGA card,
	 * we should never end up hitting this problem.
	 */
	mem = cfb->fb.fix.line_length * var->yres_भव;
	BUG_ON(mem > cfb->fb.fix.smem_len);

	/*
	 * 8bpp displays are always pseuकरो colour.  16bpp and above
	 * are direct colour or true colour, depending on whether
	 * the RAMDAC palettes are bypassed.  (Direct colour has
	 * palettes, true colour करोes not.)
	 */
	अगर (var->bits_per_pixel == 8)
		cfb->fb.fix.visual = FB_VISUAL_PSEUDOCOLOR;
	अन्यथा अगर (hw.ramdac & RAMDAC_BYPASS)
		cfb->fb.fix.visual = FB_VISUAL_TRUECOLOR;
	अन्यथा
		cfb->fb.fix.visual = FB_VISUAL_सूचीECTCOLOR;

	cyber2000fb_set_timing(cfb, &hw);
	cyber2000fb_update_start(cfb, var);

	वापस 0;
पूर्ण

/*
 *    Pan or Wrap the Display
 */
अटल पूर्णांक
cyber2000fb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा cfb_info *cfb = container_of(info, काष्ठा cfb_info, fb);

	अगर (cyber2000fb_update_start(cfb, var))
		वापस -EINVAL;

	cfb->fb.var.xoffset = var->xoffset;
	cfb->fb.var.yoffset = var->yoffset;

	अगर (var->vmode & FB_VMODE_YWRAP) अणु
		cfb->fb.var.vmode |= FB_VMODE_YWRAP;
	पूर्ण अन्यथा अणु
		cfb->fb.var.vmode &= ~FB_VMODE_YWRAP;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *    (Un)Blank the display.
 *
 *  Blank the screen अगर blank_mode != 0, अन्यथा unblank. If
 *  blank == शून्य then the caller blanks by setting the CLUT
 *  (Color Look Up Table) to all black. Return 0 अगर blanking
 *  succeeded, != 0 अगर un-/blanking failed due to e.g. a
 *  video mode which करोesn't support it. Implements VESA
 *  suspend and घातerकरोwn modes on hardware that supports
 *  disabling hsync/vsync:
 *    blank_mode == 2: suspend vsync
 *    blank_mode == 3: suspend hsync
 *    blank_mode == 4: घातerकरोwn
 *
 *  wms...Enable VESA DMPS compatible घातerकरोwn mode
 *  run "setterm -powersave powerdown" to take advantage
 */
अटल पूर्णांक cyber2000fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा cfb_info *cfb = container_of(info, काष्ठा cfb_info, fb);
	अचिन्हित पूर्णांक sync = 0;
	पूर्णांक i;

	चयन (blank) अणु
	हाल FB_BLANK_POWERDOWN:	/* घातerकरोwn - both sync lines करोwn */
		sync = EXT_SYNC_CTL_VS_0 | EXT_SYNC_CTL_HS_0;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:	/* hsync off */
		sync = EXT_SYNC_CTL_VS_NORMAL | EXT_SYNC_CTL_HS_0;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:	/* vsync off */
		sync = EXT_SYNC_CTL_VS_0 | EXT_SYNC_CTL_HS_NORMAL;
		अवरोध;
	हाल FB_BLANK_NORMAL:		/* soft blank */
	शेष:			/* unblank */
		अवरोध;
	पूर्ण

	cyber2000_grphw(EXT_SYNC_CTL, sync, cfb);

	अगर (blank <= 1) अणु
		/* turn on ramdacs */
		cfb->ramdac_घातerकरोwn &= ~(RAMDAC_DACPWRDN | RAMDAC_BYPASS |
					   RAMDAC_RAMPWRDN);
		cyber2000fb_ग_लिखो_ramdac_ctrl(cfb);
	पूर्ण

	/*
	 * Soft blank/unblank the display.
	 */
	अगर (blank) अणु	/* soft blank */
		क्रम (i = 0; i < NR_PALETTE; i++) अणु
			cyber2000fb_ग_लिखोb(i, 0x3c8, cfb);
			cyber2000fb_ग_लिखोb(0, 0x3c9, cfb);
			cyber2000fb_ग_लिखोb(0, 0x3c9, cfb);
			cyber2000fb_ग_लिखोb(0, 0x3c9, cfb);
		पूर्ण
	पूर्ण अन्यथा अणु	/* unblank */
		क्रम (i = 0; i < NR_PALETTE; i++) अणु
			cyber2000fb_ग_लिखोb(i, 0x3c8, cfb);
			cyber2000fb_ग_लिखोb(cfb->palette[i].red, 0x3c9, cfb);
			cyber2000fb_ग_लिखोb(cfb->palette[i].green, 0x3c9, cfb);
			cyber2000fb_ग_लिखोb(cfb->palette[i].blue, 0x3c9, cfb);
		पूर्ण
	पूर्ण

	अगर (blank >= 2) अणु
		/* turn off ramdacs */
		cfb->ramdac_घातerकरोwn |= RAMDAC_DACPWRDN | RAMDAC_BYPASS |
					 RAMDAC_RAMPWRDN;
		cyber2000fb_ग_लिखो_ramdac_ctrl(cfb);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops cyber2000fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= cyber2000fb_check_var,
	.fb_set_par	= cyber2000fb_set_par,
	.fb_setcolreg	= cyber2000fb_setcolreg,
	.fb_blank	= cyber2000fb_blank,
	.fb_pan_display	= cyber2000fb_pan_display,
	.fb_fillrect	= cyber2000fb_fillrect,
	.fb_copyarea	= cyber2000fb_copyarea,
	.fb_imageblit	= cyber2000fb_imageblit,
	.fb_sync	= cyber2000fb_sync,
पूर्ण;

/*
 * This is the only "static" reference to the पूर्णांकernal data काष्ठाures
 * of this driver.  It is here solely at the moment to support the other
 * CyberPro modules बाह्यal to this driver.
 */
अटल काष्ठा cfb_info *पूर्णांक_cfb_info;

/*
 * Enable access to the extended रेजिस्टरs
 */
व्योम cyber2000fb_enable_extregs(काष्ठा cfb_info *cfb)
अणु
	cfb->func_use_count += 1;

	अगर (cfb->func_use_count == 1) अणु
		पूर्णांक old;

		old = cyber2000_grphr(EXT_FUNC_CTL, cfb);
		old |= EXT_FUNC_CTL_EXTREGENBL;
		cyber2000_grphw(EXT_FUNC_CTL, old, cfb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cyber2000fb_enable_extregs);

/*
 * Disable access to the extended रेजिस्टरs
 */
व्योम cyber2000fb_disable_extregs(काष्ठा cfb_info *cfb)
अणु
	अगर (cfb->func_use_count == 1) अणु
		पूर्णांक old;

		old = cyber2000_grphr(EXT_FUNC_CTL, cfb);
		old &= ~EXT_FUNC_CTL_EXTREGENBL;
		cyber2000_grphw(EXT_FUNC_CTL, old, cfb);
	पूर्ण

	अगर (cfb->func_use_count == 0)
		prपूर्णांकk(KERN_ERR "disable_extregs: count = 0\n");
	अन्यथा
		cfb->func_use_count -= 1;
पूर्ण
EXPORT_SYMBOL(cyber2000fb_disable_extregs);

/*
 * Attach a capture/tv driver to the core CyberX0X0 driver.
 */
पूर्णांक cyber2000fb_attach(काष्ठा cyberpro_info *info, पूर्णांक idx)
अणु
	अगर (पूर्णांक_cfb_info != शून्य) अणु
		info->dev	      = पूर्णांक_cfb_info->fb.device;
#अगर_घोषित CONFIG_FB_CYBER2000_I2C
		info->i2c	      = &पूर्णांक_cfb_info->i2c_adapter;
#अन्यथा
		info->i2c	      = शून्य;
#पूर्ण_अगर
		info->regs	      = पूर्णांक_cfb_info->regs;
		info->irq             = पूर्णांक_cfb_info->irq;
		info->fb	      = पूर्णांक_cfb_info->fb.screen_base;
		info->fb_size	      = पूर्णांक_cfb_info->fb.fix.smem_len;
		info->info	      = पूर्णांक_cfb_info;

		strlcpy(info->dev_name, पूर्णांक_cfb_info->fb.fix.id,
			माप(info->dev_name));
	पूर्ण

	वापस पूर्णांक_cfb_info != शून्य;
पूर्ण
EXPORT_SYMBOL(cyber2000fb_attach);

/*
 * Detach a capture/tv driver from the core CyberX0X0 driver.
 */
व्योम cyber2000fb_detach(पूर्णांक idx)
अणु
पूर्ण
EXPORT_SYMBOL(cyber2000fb_detach);

#अगर_घोषित CONFIG_FB_CYBER2000_DDC

#घोषणा DDC_REG		0xb0
#घोषणा DDC_SCL_OUT	(1 << 0)
#घोषणा DDC_SDA_OUT	(1 << 4)
#घोषणा DDC_SCL_IN	(1 << 2)
#घोषणा DDC_SDA_IN	(1 << 6)

अटल व्योम cyber2000fb_enable_ddc(काष्ठा cfb_info *cfb)
	__acquires(&cfb->reg_b0_lock)
अणु
	spin_lock(&cfb->reg_b0_lock);
	cyber2000fb_ग_लिखोw(0x1bf, 0x3ce, cfb);
पूर्ण

अटल व्योम cyber2000fb_disable_ddc(काष्ठा cfb_info *cfb)
	__releases(&cfb->reg_b0_lock)
अणु
	cyber2000fb_ग_लिखोw(0x0bf, 0x3ce, cfb);
	spin_unlock(&cfb->reg_b0_lock);
पूर्ण


अटल व्योम cyber2000fb_ddc_setscl(व्योम *data, पूर्णांक val)
अणु
	काष्ठा cfb_info *cfb = data;
	अचिन्हित अक्षर reg;

	cyber2000fb_enable_ddc(cfb);
	reg = cyber2000_grphr(DDC_REG, cfb);
	अगर (!val)	/* bit is inverted */
		reg |= DDC_SCL_OUT;
	अन्यथा
		reg &= ~DDC_SCL_OUT;
	cyber2000_grphw(DDC_REG, reg, cfb);
	cyber2000fb_disable_ddc(cfb);
पूर्ण

अटल व्योम cyber2000fb_ddc_setsda(व्योम *data, पूर्णांक val)
अणु
	काष्ठा cfb_info *cfb = data;
	अचिन्हित अक्षर reg;

	cyber2000fb_enable_ddc(cfb);
	reg = cyber2000_grphr(DDC_REG, cfb);
	अगर (!val)	/* bit is inverted */
		reg |= DDC_SDA_OUT;
	अन्यथा
		reg &= ~DDC_SDA_OUT;
	cyber2000_grphw(DDC_REG, reg, cfb);
	cyber2000fb_disable_ddc(cfb);
पूर्ण

अटल पूर्णांक cyber2000fb_ddc_माला_लोcl(व्योम *data)
अणु
	काष्ठा cfb_info *cfb = data;
	पूर्णांक retval;

	cyber2000fb_enable_ddc(cfb);
	retval = !!(cyber2000_grphr(DDC_REG, cfb) & DDC_SCL_IN);
	cyber2000fb_disable_ddc(cfb);

	वापस retval;
पूर्ण

अटल पूर्णांक cyber2000fb_ddc_माला_लोda(व्योम *data)
अणु
	काष्ठा cfb_info *cfb = data;
	पूर्णांक retval;

	cyber2000fb_enable_ddc(cfb);
	retval = !!(cyber2000_grphr(DDC_REG, cfb) & DDC_SDA_IN);
	cyber2000fb_disable_ddc(cfb);

	वापस retval;
पूर्ण

अटल पूर्णांक cyber2000fb_setup_ddc_bus(काष्ठा cfb_info *cfb)
अणु
	strlcpy(cfb->ddc_adapter.name, cfb->fb.fix.id,
		माप(cfb->ddc_adapter.name));
	cfb->ddc_adapter.owner		= THIS_MODULE;
	cfb->ddc_adapter.class		= I2C_CLASS_DDC;
	cfb->ddc_adapter.algo_data	= &cfb->ddc_algo;
	cfb->ddc_adapter.dev.parent	= cfb->fb.device;
	cfb->ddc_algo.setsda		= cyber2000fb_ddc_setsda;
	cfb->ddc_algo.setscl		= cyber2000fb_ddc_setscl;
	cfb->ddc_algo.माला_लोda		= cyber2000fb_ddc_माला_लोda;
	cfb->ddc_algo.माला_लोcl		= cyber2000fb_ddc_माला_लोcl;
	cfb->ddc_algo.udelay		= 10;
	cfb->ddc_algo.समयout		= 20;
	cfb->ddc_algo.data		= cfb;

	i2c_set_adapdata(&cfb->ddc_adapter, cfb);

	वापस i2c_bit_add_bus(&cfb->ddc_adapter);
पूर्ण
#पूर्ण_अगर /* CONFIG_FB_CYBER2000_DDC */

#अगर_घोषित CONFIG_FB_CYBER2000_I2C
अटल व्योम cyber2000fb_i2c_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा cfb_info *cfb = data;
	अचिन्हित पूर्णांक latch2;

	spin_lock(&cfb->reg_b0_lock);
	latch2 = cyber2000_grphr(EXT_LATCH2, cfb);
	latch2 &= EXT_LATCH2_I2C_CLKEN;
	अगर (state)
		latch2 |= EXT_LATCH2_I2C_DATEN;
	cyber2000_grphw(EXT_LATCH2, latch2, cfb);
	spin_unlock(&cfb->reg_b0_lock);
पूर्ण

अटल व्योम cyber2000fb_i2c_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा cfb_info *cfb = data;
	अचिन्हित पूर्णांक latch2;

	spin_lock(&cfb->reg_b0_lock);
	latch2 = cyber2000_grphr(EXT_LATCH2, cfb);
	latch2 &= EXT_LATCH2_I2C_DATEN;
	अगर (state)
		latch2 |= EXT_LATCH2_I2C_CLKEN;
	cyber2000_grphw(EXT_LATCH2, latch2, cfb);
	spin_unlock(&cfb->reg_b0_lock);
पूर्ण

अटल पूर्णांक cyber2000fb_i2c_माला_लोda(व्योम *data)
अणु
	काष्ठा cfb_info *cfb = data;
	पूर्णांक ret;

	spin_lock(&cfb->reg_b0_lock);
	ret = !!(cyber2000_grphr(EXT_LATCH2, cfb) & EXT_LATCH2_I2C_DAT);
	spin_unlock(&cfb->reg_b0_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cyber2000fb_i2c_माला_लोcl(व्योम *data)
अणु
	काष्ठा cfb_info *cfb = data;
	पूर्णांक ret;

	spin_lock(&cfb->reg_b0_lock);
	ret = !!(cyber2000_grphr(EXT_LATCH2, cfb) & EXT_LATCH2_I2C_CLK);
	spin_unlock(&cfb->reg_b0_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cyber2000fb_i2c_रेजिस्टर(काष्ठा cfb_info *cfb)
अणु
	strlcpy(cfb->i2c_adapter.name, cfb->fb.fix.id,
		माप(cfb->i2c_adapter.name));
	cfb->i2c_adapter.owner = THIS_MODULE;
	cfb->i2c_adapter.algo_data = &cfb->i2c_algo;
	cfb->i2c_adapter.dev.parent = cfb->fb.device;
	cfb->i2c_algo.setsda = cyber2000fb_i2c_setsda;
	cfb->i2c_algo.setscl = cyber2000fb_i2c_setscl;
	cfb->i2c_algo.माला_लोda = cyber2000fb_i2c_माला_लोda;
	cfb->i2c_algo.माला_लोcl = cyber2000fb_i2c_माला_लोcl;
	cfb->i2c_algo.udelay = 5;
	cfb->i2c_algo.समयout = msecs_to_jअगरfies(100);
	cfb->i2c_algo.data = cfb;

	वापस i2c_bit_add_bus(&cfb->i2c_adapter);
पूर्ण

अटल व्योम cyber2000fb_i2c_unरेजिस्टर(काष्ठा cfb_info *cfb)
अणु
	i2c_del_adapter(&cfb->i2c_adapter);
पूर्ण
#अन्यथा
#घोषणा cyber2000fb_i2c_रेजिस्टर(cfb)	(0)
#घोषणा cyber2000fb_i2c_unरेजिस्टर(cfb)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * These parameters give
 * 640x480, hsync 31.5kHz, vsync 60Hz
 */
अटल स्थिर काष्ठा fb_videomode cyber2000fb_शेष_mode = अणु
	.refresh	= 60,
	.xres		= 640,
	.yres		= 480,
	.pixघड़ी	= 39722,
	.left_margin	= 56,
	.right_margin	= 16,
	.upper_margin	= 34,
	.lower_margin	= 9,
	.hsync_len	= 88,
	.vsync_len	= 2,
	.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	.vmode		= FB_VMODE_NONINTERLACED
पूर्ण;

अटल अक्षर igs_regs[] = अणु
	EXT_CRT_IRQ,		0,
	EXT_CRT_TEST,		0,
	EXT_SYNC_CTL,		0,
	EXT_SEG_WRITE_PTR,	0,
	EXT_SEG_READ_PTR,	0,
	EXT_BIU_MISC,		EXT_BIU_MISC_LIN_ENABLE |
				EXT_BIU_MISC_COP_ENABLE |
				EXT_BIU_MISC_COP_BFC,
	EXT_FUNC_CTL,		0,
	CURS_H_START,		0,
	CURS_H_START + 1,	0,
	CURS_H_PRESET,		0,
	CURS_V_START,		0,
	CURS_V_START + 1,	0,
	CURS_V_PRESET,		0,
	CURS_CTL,		0,
	EXT_ATTRIB_CTL,		EXT_ATTRIB_CTL_EXT,
	EXT_OVERSCAN_RED,	0,
	EXT_OVERSCAN_GREEN,	0,
	EXT_OVERSCAN_BLUE,	0,

	/* some of these are questionable when we have a BIOS */
	EXT_MEM_CTL0,		EXT_MEM_CTL0_7CLK |
				EXT_MEM_CTL0_RAS_1 |
				EXT_MEM_CTL0_MULTCAS,
	EXT_HIDDEN_CTL1,	0x30,
	EXT_FIFO_CTL,		0x0b,
	EXT_FIFO_CTL + 1,	0x17,
	0x76,			0x00,
	EXT_HIDDEN_CTL4,	0xc8
पूर्ण;

/*
 * Initialise the CyberPro hardware.  On the CyberPro5XXXX,
 * ensure that we're using the correct PLL (5XXX's may be
 * programmed to use an additional set of PLLs.)
 */
अटल व्योम cyberpro_init_hw(काष्ठा cfb_info *cfb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < माप(igs_regs); i += 2)
		cyber2000_grphw(igs_regs[i], igs_regs[i + 1], cfb);

	अगर (cfb->id == ID_CYBERPRO_5000) अणु
		अचिन्हित अक्षर val;
		cyber2000fb_ग_लिखोb(0xba, 0x3ce, cfb);
		val = cyber2000fb_पढ़ोb(0x3cf, cfb) & 0x80;
		cyber2000fb_ग_लिखोb(val, 0x3cf, cfb);
	पूर्ण
पूर्ण

अटल काष्ठा cfb_info *cyberpro_alloc_fb_info(अचिन्हित पूर्णांक id, अक्षर *name)
अणु
	काष्ठा cfb_info *cfb;

	cfb = kzalloc(माप(काष्ठा cfb_info), GFP_KERNEL);
	अगर (!cfb)
		वापस शून्य;


	cfb->id			= id;

	अगर (id == ID_CYBERPRO_5000)
		cfb->ref_ps	= 40690; /* 24.576 MHz */
	अन्यथा
		cfb->ref_ps	= 69842; /* 14.31818 MHz (69841?) */

	cfb->भागisors[0]	= 1;
	cfb->भागisors[1]	= 2;
	cfb->भागisors[2]	= 4;

	अगर (id == ID_CYBERPRO_2000)
		cfb->भागisors[3] = 8;
	अन्यथा
		cfb->भागisors[3] = 6;

	म_नकल(cfb->fb.fix.id, name);

	cfb->fb.fix.type	= FB_TYPE_PACKED_PIXELS;
	cfb->fb.fix.type_aux	= 0;
	cfb->fb.fix.xpanstep	= 0;
	cfb->fb.fix.ypanstep	= 1;
	cfb->fb.fix.ywrapstep	= 0;

	चयन (id) अणु
	हाल ID_IGA_1682:
		cfb->fb.fix.accel = 0;
		अवरोध;

	हाल ID_CYBERPRO_2000:
		cfb->fb.fix.accel = FB_ACCEL_IGS_CYBER2000;
		अवरोध;

	हाल ID_CYBERPRO_2010:
		cfb->fb.fix.accel = FB_ACCEL_IGS_CYBER2010;
		अवरोध;

	हाल ID_CYBERPRO_5000:
		cfb->fb.fix.accel = FB_ACCEL_IGS_CYBER5000;
		अवरोध;
	पूर्ण

	cfb->fb.var.nonstd	= 0;
	cfb->fb.var.activate	= FB_ACTIVATE_NOW;
	cfb->fb.var.height	= -1;
	cfb->fb.var.width	= -1;
	cfb->fb.var.accel_flags	= FB_ACCELF_TEXT;

	cfb->fb.fbops		= &cyber2000fb_ops;
	cfb->fb.flags		= FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
	cfb->fb.pseuकरो_palette	= cfb->pseuकरो_palette;

	spin_lock_init(&cfb->reg_b0_lock);

	fb_alloc_cmap(&cfb->fb.cmap, NR_PALETTE, 0);

	वापस cfb;
पूर्ण

अटल व्योम cyberpro_मुक्त_fb_info(काष्ठा cfb_info *cfb)
अणु
	अगर (cfb) अणु
		/*
		 * Free the colourmap
		 */
		fb_alloc_cmap(&cfb->fb.cmap, 0, 0);

		kमुक्त(cfb);
	पूर्ण
पूर्ण

/*
 * Parse Cyber2000fb options.  Usage:
 *  video=cyber2000:font:fontname
 */
#अगर_अघोषित MODULE
अटल पूर्णांक cyber2000fb_setup(अक्षर *options)
अणु
	अक्षर *opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*opt)
			जारी;

		अगर (म_भेदन(opt, "font:", 5) == 0) अणु
			अटल अक्षर शेष_font_storage[40];

			strlcpy(शेष_font_storage, opt + 5,
				माप(शेष_font_storage));
			शेष_font = शेष_font_storage;
			जारी;
		पूर्ण

		prपूर्णांकk(KERN_ERR "CyberPro20x0: unknown parameter: %s\n", opt);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर  /*  MODULE  */

/*
 * The CyberPro chips can be placed on many dअगरferent bus types.
 * This probe function is common to all bus types.  The bus-specअगरic
 * probe function is expected to have:
 *  - enabled access to the linear memory region
 *  - memory mapped access to the रेजिस्टरs
 *  - initialised mem_ctl1 and mem_ctl2 appropriately.
 */
अटल पूर्णांक cyberpro_common_probe(काष्ठा cfb_info *cfb)
अणु
	u_दीर्घ smem_size;
	u_पूर्णांक h_sync, v_sync;
	पूर्णांक err;

	cyberpro_init_hw(cfb);

	/*
	 * Get the video RAM size and width from the VGA रेजिस्टर.
	 * This should have been alपढ़ोy initialised by the BIOS,
	 * but अगर it's garbage, claim शेष 1MB VRAM (woody)
	 */
	cfb->mem_ctl1 = cyber2000_grphr(EXT_MEM_CTL1, cfb);
	cfb->mem_ctl2 = cyber2000_grphr(EXT_MEM_CTL2, cfb);

	/*
	 * Determine the size of the memory.
	 */
	चयन (cfb->mem_ctl2 & MEM_CTL2_SIZE_MASK) अणु
	हाल MEM_CTL2_SIZE_4MB:
		smem_size = 0x00400000;
		अवरोध;
	हाल MEM_CTL2_SIZE_2MB:
		smem_size = 0x00200000;
		अवरोध;
	हाल MEM_CTL2_SIZE_1MB:
		smem_size = 0x00100000;
		अवरोध;
	शेष:
		smem_size = 0x00100000;
		अवरोध;
	पूर्ण

	cfb->fb.fix.smem_len   = smem_size;
	cfb->fb.fix.mmio_len   = MMIO_SIZE;
	cfb->fb.screen_base    = cfb->region;

#अगर_घोषित CONFIG_FB_CYBER2000_DDC
	अगर (cyber2000fb_setup_ddc_bus(cfb) == 0)
		cfb->ddc_रेजिस्टरed = true;
#पूर्ण_अगर

	err = -EINVAL;
	अगर (!fb_find_mode(&cfb->fb.var, &cfb->fb, शून्य, शून्य, 0,
			  &cyber2000fb_शेष_mode, 8)) अणु
		prपूर्णांकk(KERN_ERR "%s: no valid mode found\n", cfb->fb.fix.id);
		जाओ failed;
	पूर्ण

	cfb->fb.var.yres_भव = cfb->fb.fix.smem_len * 8 /
			(cfb->fb.var.bits_per_pixel * cfb->fb.var.xres_भव);

	अगर (cfb->fb.var.yres_भव < cfb->fb.var.yres)
		cfb->fb.var.yres_भव = cfb->fb.var.yres;

/*	fb_set_var(&cfb->fb.var, -1, &cfb->fb); */

	/*
	 * Calculate the hsync and vsync frequencies.  Note that
	 * we split the 1e12 स्थिरant up so that we can preserve
	 * the precision and fit the results पूर्णांकo 32-bit रेजिस्टरs.
	 *  (1953125000 * 512 = 1e12)
	 */
	h_sync = 1953125000 / cfb->fb.var.pixघड़ी;
	h_sync = h_sync * 512 / (cfb->fb.var.xres + cfb->fb.var.left_margin +
		 cfb->fb.var.right_margin + cfb->fb.var.hsync_len);
	v_sync = h_sync / (cfb->fb.var.yres + cfb->fb.var.upper_margin +
		 cfb->fb.var.lower_margin + cfb->fb.var.vsync_len);

	prपूर्णांकk(KERN_INFO "%s: %dKiB VRAM, using %dx%d, %d.%03dkHz, %dHz\n",
		cfb->fb.fix.id, cfb->fb.fix.smem_len >> 10,
		cfb->fb.var.xres, cfb->fb.var.yres,
		h_sync / 1000, h_sync % 1000, v_sync);

	err = cyber2000fb_i2c_रेजिस्टर(cfb);
	अगर (err)
		जाओ failed;

	err = रेजिस्टर_framebuffer(&cfb->fb);
	अगर (err)
		cyber2000fb_i2c_unरेजिस्टर(cfb);

failed:
#अगर_घोषित CONFIG_FB_CYBER2000_DDC
	अगर (err && cfb->ddc_रेजिस्टरed)
		i2c_del_adapter(&cfb->ddc_adapter);
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम cyberpro_common_हटाओ(काष्ठा cfb_info *cfb)
अणु
	unरेजिस्टर_framebuffer(&cfb->fb);
#अगर_घोषित CONFIG_FB_CYBER2000_DDC
	अगर (cfb->ddc_रेजिस्टरed)
		i2c_del_adapter(&cfb->ddc_adapter);
#पूर्ण_अगर
	cyber2000fb_i2c_unरेजिस्टर(cfb);
पूर्ण

अटल व्योम cyberpro_common_resume(काष्ठा cfb_info *cfb)
अणु
	cyberpro_init_hw(cfb);

	/*
	 * Reprogram the MEM_CTL1 and MEM_CTL2 रेजिस्टरs
	 */
	cyber2000_grphw(EXT_MEM_CTL1, cfb->mem_ctl1, cfb);
	cyber2000_grphw(EXT_MEM_CTL2, cfb->mem_ctl2, cfb);

	/*
	 * Restore the old video mode and the palette.
	 * We also need to tell fbcon to redraw the console.
	 */
	cyber2000fb_set_par(&cfb->fb);
पूर्ण

/*
 * We need to wake up the CyberPro, and make sure its in linear memory
 * mode.  Unक्रमtunately, this is specअगरic to the platक्रमm and card that
 * we are running on.
 *
 * On x86 and ARM, should we be initialising the CyberPro first via the
 * IO रेजिस्टरs, and then the MMIO रेजिस्टरs to catch all हालs?  Can we
 * end up in the situation where the chip is in MMIO mode, but not awake
 * on an x86 प्रणाली?
 */
अटल पूर्णांक cyberpro_pci_enable_mmio(काष्ठा cfb_info *cfb)
अणु
	अचिन्हित अक्षर val;

#अगर defined(__sparc_v9__)
#त्रुटि "You lose, consult DaveM."
#या_अगर defined(__sparc__)
	/*
	 * SPARC करोes not have an "outb" inकाष्ठाion, so we generate
	 * I/O cycles storing पूर्णांकo a reserved memory space at
	 * physical address 0x3000000
	 */
	अचिन्हित अक्षर __iomem *iop;

	iop = ioremap(0x3000000, 0x5000);
	अगर (iop == शून्य) अणु
		prपूर्णांकk(KERN_ERR "iga5000: cannot map I/O\n");
		वापस -ENOMEM;
	पूर्ण

	ग_लिखोb(0x18, iop + 0x46e8);
	ग_लिखोb(0x01, iop + 0x102);
	ग_लिखोb(0x08, iop + 0x46e8);
	ग_लिखोb(EXT_BIU_MISC, iop + 0x3ce);
	ग_लिखोb(EXT_BIU_MISC_LIN_ENABLE, iop + 0x3cf);

	iounmap(iop);
#अन्यथा
	/*
	 * Most other machine types are "normal", so
	 * we use the standard IO-based wakeup.
	 */
	outb(0x18, 0x46e8);
	outb(0x01, 0x102);
	outb(0x08, 0x46e8);
	outb(EXT_BIU_MISC, 0x3ce);
	outb(EXT_BIU_MISC_LIN_ENABLE, 0x3cf);
#पूर्ण_अगर

	/*
	 * Allow the CyberPro to accept PCI burst accesses
	 */
	अगर (cfb->id == ID_CYBERPRO_2010) अणु
		prपूर्णांकk(KERN_INFO "%s: NOT enabling PCI bursts\n",
		       cfb->fb.fix.id);
	पूर्ण अन्यथा अणु
		val = cyber2000_grphr(EXT_BUS_CTL, cfb);
		अगर (!(val & EXT_BUS_CTL_PCIBURST_WRITE)) अणु
			prपूर्णांकk(KERN_INFO "%s: enabling PCI bursts\n",
				cfb->fb.fix.id);

			val |= EXT_BUS_CTL_PCIBURST_WRITE;

			अगर (cfb->id == ID_CYBERPRO_5000)
				val |= EXT_BUS_CTL_PCIBURST_READ;

			cyber2000_grphw(EXT_BUS_CTL, val, cfb);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cyberpro_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा cfb_info *cfb;
	अक्षर name[16];
	पूर्णांक err;

	प्र_लिखो(name, "CyberPro%4X", id->device);

	err = pci_enable_device(dev);
	अगर (err)
		वापस err;

	err = -ENOMEM;
	cfb = cyberpro_alloc_fb_info(id->driver_data, name);
	अगर (!cfb)
		जाओ failed_release;

	err = pci_request_regions(dev, cfb->fb.fix.id);
	अगर (err)
		जाओ failed_regions;

	cfb->irq = dev->irq;
	cfb->region = pci_ioremap_bar(dev, 0);
	अगर (!cfb->region) अणु
		err = -ENOMEM;
		जाओ failed_ioremap;
	पूर्ण

	cfb->regs = cfb->region + MMIO_OFFSET;
	cfb->fb.device = &dev->dev;
	cfb->fb.fix.mmio_start = pci_resource_start(dev, 0) + MMIO_OFFSET;
	cfb->fb.fix.smem_start = pci_resource_start(dev, 0);

	/*
	 * Bring up the hardware.  This is expected to enable access
	 * to the linear memory region, and allow access to the memory
	 * mapped रेजिस्टरs.  Also, mem_ctl1 and mem_ctl2 must be
	 * initialised.
	 */
	err = cyberpro_pci_enable_mmio(cfb);
	अगर (err)
		जाओ failed;

	/*
	 * Use MCLK from BIOS. FIXME: what about hotplug?
	 */
	cfb->mclk_mult = cyber2000_grphr(EXT_MCLK_MULT, cfb);
	cfb->mclk_भाग  = cyber2000_grphr(EXT_MCLK_DIV, cfb);

#अगर_घोषित __arm__
	/*
	 * MCLK on the NetWinder and the Shark is fixed at 75MHz
	 */
	अगर (machine_is_netwinder()) अणु
		cfb->mclk_mult = 0xdb;
		cfb->mclk_भाग  = 0x54;
	पूर्ण
#पूर्ण_अगर

	err = cyberpro_common_probe(cfb);
	अगर (err)
		जाओ failed;

	/*
	 * Our driver data
	 */
	pci_set_drvdata(dev, cfb);
	अगर (पूर्णांक_cfb_info == शून्य)
		पूर्णांक_cfb_info = cfb;

	वापस 0;

failed:
	iounmap(cfb->region);
failed_ioremap:
	pci_release_regions(dev);
failed_regions:
	cyberpro_मुक्त_fb_info(cfb);
failed_release:
	वापस err;
पूर्ण

अटल व्योम cyberpro_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा cfb_info *cfb = pci_get_drvdata(dev);

	अगर (cfb) अणु
		cyberpro_common_हटाओ(cfb);
		iounmap(cfb->region);
		cyberpro_मुक्त_fb_info(cfb);

		अगर (cfb == पूर्णांक_cfb_info)
			पूर्णांक_cfb_info = शून्य;

		pci_release_regions(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused cyberpro_pci_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

/*
 * Re-initialise the CyberPro hardware
 */
अटल पूर्णांक __maybe_unused cyberpro_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा cfb_info *cfb = dev_get_drvdata(dev);

	अगर (cfb) अणु
		cyberpro_pci_enable_mmio(cfb);
		cyberpro_common_resume(cfb);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pci_device_id cyberpro_pci_table[] = अणु
/*	Not yet
 *	अणु PCI_VENDOR_ID_INTERG, PCI_DEVICE_ID_INTERG_1682,
 *		PCI_ANY_ID, PCI_ANY_ID, 0, 0, ID_IGA_1682 पूर्ण,
 */
	अणु PCI_VENDOR_ID_INTERG, PCI_DEVICE_ID_INTERG_2000,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, ID_CYBERPRO_2000 पूर्ण,
	अणु PCI_VENDOR_ID_INTERG, PCI_DEVICE_ID_INTERG_2010,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, ID_CYBERPRO_2010 पूर्ण,
	अणु PCI_VENDOR_ID_INTERG, PCI_DEVICE_ID_INTERG_5000,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, ID_CYBERPRO_5000 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, cyberpro_pci_table);

अटल SIMPLE_DEV_PM_OPS(cyberpro_pci_pm_ops,
			 cyberpro_pci_suspend,
			 cyberpro_pci_resume);

अटल काष्ठा pci_driver cyberpro_driver = अणु
	.name		= "CyberPro",
	.probe		= cyberpro_pci_probe,
	.हटाओ		= cyberpro_pci_हटाओ,
	.driver.pm	= &cyberpro_pci_pm_ops,
	.id_table	= cyberpro_pci_table
पूर्ण;

/*
 * I करोn't think we can use the "module_init" stuff here because
 * the fbcon stuff may not be initialised yet.  Hence the #अगर_घोषित
 * around module_init.
 *
 * Tony: "module_init" is now required
 */
अटल पूर्णांक __init cyber2000fb_init(व्योम)
अणु
	पूर्णांक ret = -1, err;

#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("cyber2000fb", &option))
		वापस -ENODEV;
	cyber2000fb_setup(option);
#पूर्ण_अगर

	err = pci_रेजिस्टर_driver(&cyberpro_driver);
	अगर (!err)
		ret = 0;

	वापस ret ? err : 0;
पूर्ण
module_init(cyber2000fb_init);

अटल व्योम __निकास cyberpro_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cyberpro_driver);
पूर्ण
module_निकास(cyberpro_निकास);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("CyberPro 2000, 2010 and 5000 framebuffer driver");
MODULE_LICENSE("GPL");
