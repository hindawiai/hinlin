<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/video/geode/display_gx1.c
 *   -- Geode GX1 display controller
 *
 * Copyright (C) 2005 Arcom Control Systems Ltd.
 *
 * Based on AMD's original 2.4 driver:
 *   Copyright (C) 2004 Advanced Micro Devices, Inc.
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/delay.h>

#समावेश "geodefb.h"
#समावेश "display_gx1.h"

अटल DEFINE_SPINLOCK(gx1_conf_reg_lock);

अटल u8 gx1_पढ़ो_conf_reg(u8 reg)
अणु
	u8 val, ccr3;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gx1_conf_reg_lock, flags);

	outb(CONFIG_CCR3, 0x22);
	ccr3 = inb(0x23);
	outb(CONFIG_CCR3, 0x22);
	outb(ccr3 | CONFIG_CCR3_MAPEN, 0x23);
	outb(reg, 0x22);
	val = inb(0x23);
	outb(CONFIG_CCR3, 0x22);
	outb(ccr3, 0x23);

	spin_unlock_irqrestore(&gx1_conf_reg_lock, flags);

	वापस val;
पूर्ण

अचिन्हित gx1_gx_base(व्योम)
अणु
	वापस (gx1_पढ़ो_conf_reg(CONFIG_GCR) & 0x03) << 30;
पूर्ण

पूर्णांक gx1_frame_buffer_size(व्योम)
अणु
	व्योम __iomem *mc_regs;
	u32 bank_cfg;
	पूर्णांक d;
	अचिन्हित dram_size = 0, fb_base;

	mc_regs = ioremap(gx1_gx_base() + 0x8400, 0x100);
	अगर (!mc_regs)
		वापस -ENOMEM;


	/* Calculate the total size of both DIMM0 and DIMM1. */
	bank_cfg = पढ़ोl(mc_regs + MC_BANK_CFG);

	क्रम (d = 0; d < 2; d++) अणु
		अगर ((bank_cfg & MC_BCFG_DIMM0_PG_SZ_MASK) != MC_BCFG_DIMM0_PG_SZ_NO_DIMM)
			dram_size += 0x400000 << ((bank_cfg & MC_BCFG_DIMM0_SZ_MASK) >> 8);
		bank_cfg >>= 16; /* look at DIMM1 next */
	पूर्ण

	fb_base = (पढ़ोl(mc_regs + MC_GBASE_ADD) & MC_GADD_GBADD_MASK) << 19;

	iounmap(mc_regs);

	वापस dram_size - fb_base;
पूर्ण

अटल व्योम gx1_set_mode(काष्ठा fb_info *info)
अणु
	काष्ठा geodefb_par *par = info->par;
	u32 gcfg, tcfg, ocfg, dclk_भाग, val;
	पूर्णांक hactive, hblankstart, hsyncstart, hsyncend, hblankend, htotal;
	पूर्णांक vactive, vblankstart, vsyncstart, vsyncend, vblankend, vtotal;

	/* Unlock the display controller रेजिस्टरs. */
	पढ़ोl(par->dc_regs + DC_UNLOCK);
	ग_लिखोl(DC_UNLOCK_CODE, par->dc_regs + DC_UNLOCK);

	gcfg = पढ़ोl(par->dc_regs + DC_GENERAL_CFG);
	tcfg = पढ़ोl(par->dc_regs + DC_TIMING_CFG);

	/* Blank the display and disable the timing generator. */
	tcfg &= ~(DC_TCFG_BLKE | DC_TCFG_TGEN);
	ग_लिखोl(tcfg, par->dc_regs + DC_TIMING_CFG);

	/* Wait क्रम pending memory requests beक्रमe disabling the FIFO load. */
	udelay(100);

	/* Disable FIFO load and compression. */
	gcfg &= ~(DC_GCFG_DFLE | DC_GCFG_CMPE | DC_GCFG_DECE);
	ग_लिखोl(gcfg, par->dc_regs + DC_GENERAL_CFG);

	/* Setup DCLK and its भागisor. */
	gcfg &= ~DC_GCFG_DCLK_MASK;
	ग_लिखोl(gcfg, par->dc_regs + DC_GENERAL_CFG);

	par->vid_ops->set_dclk(info);

	dclk_भाग = DC_GCFG_DCLK_DIV_1; /* FIXME: may need to भागide DCLK by 2 someबार? */
	gcfg |= dclk_भाग;
	ग_लिखोl(gcfg, par->dc_regs + DC_GENERAL_CFG);

	/* Wait क्रम the घड़ी generatation to settle.  This is needed since
	 * some of the रेजिस्टर ग_लिखोs that follow require that घड़ी to be
	 * present. */
	udelay(1000); /* FIXME: seems a little दीर्घ */

	/*
	 * Setup new mode.
	 */

	/* Clear all unused feature bits. */
	gcfg = DC_GCFG_VRDY | dclk_भाग;

	/* Set FIFO priority (शेष 6/5) and enable. */
	/* FIXME: increase fअगरo priority क्रम 1280x1024 modes? */
	gcfg |= (6 << DC_GCFG_DFHPEL_POS) | (5 << DC_GCFG_DFHPSL_POS) | DC_GCFG_DFLE;

	/* FIXME: Set pixel and line द्विगुन bits अगर necessary. */

	/* Framebuffer start offset. */
	ग_लिखोl(0, par->dc_regs + DC_FB_ST_OFFSET);

	/* Line delta and line buffer length. */
	ग_लिखोl(info->fix.line_length >> 2, par->dc_regs + DC_LINE_DELTA);
	ग_लिखोl(((info->var.xres * info->var.bits_per_pixel/8) >> 3) + 2,
	       par->dc_regs + DC_BUF_SIZE);

	/* Output configuration. Enable panel data, set pixel क्रमmat. */
	ocfg = DC_OCFG_PCKE | DC_OCFG_PDEL | DC_OCFG_PDEH;
	अगर (info->var.bits_per_pixel == 8) ocfg |= DC_OCFG_8BPP;

	/* Enable timing generator, sync and FP data. */
	tcfg = DC_TCFG_FPPE | DC_TCFG_HSYE | DC_TCFG_VSYE | DC_TCFG_BLKE
		| DC_TCFG_TGEN;

	/* Horizontal and vertical timings. */
	hactive = info->var.xres;
	hblankstart = hactive;
	hsyncstart = hblankstart + info->var.right_margin;
	hsyncend =  hsyncstart + info->var.hsync_len;
	hblankend = hsyncend + info->var.left_margin;
	htotal = hblankend;

	vactive = info->var.yres;
	vblankstart = vactive;
	vsyncstart = vblankstart + info->var.lower_margin;
	vsyncend =  vsyncstart + info->var.vsync_len;
	vblankend = vsyncend + info->var.upper_margin;
	vtotal = vblankend;

	val = (hactive - 1) | ((htotal - 1) << 16);
	ग_लिखोl(val, par->dc_regs + DC_H_TIMING_1);
	val = (hblankstart - 1) | ((hblankend - 1) << 16);
	ग_लिखोl(val, par->dc_regs + DC_H_TIMING_2);
	val = (hsyncstart - 1) | ((hsyncend - 1) << 16);
	ग_लिखोl(val, par->dc_regs + DC_H_TIMING_3);
	ग_लिखोl(val, par->dc_regs + DC_FP_H_TIMING);
	val = (vactive - 1) | ((vtotal - 1) << 16);
	ग_लिखोl(val, par->dc_regs + DC_V_TIMING_1);
	val = (vblankstart - 1) | ((vblankend - 1) << 16);
	ग_लिखोl(val, par->dc_regs + DC_V_TIMING_2);
	val = (vsyncstart - 1) | ((vsyncend - 1) << 16);
	ग_लिखोl(val, par->dc_regs + DC_V_TIMING_3);
	val = (vsyncstart - 2) | ((vsyncend - 2) << 16);
	ग_लिखोl(val, par->dc_regs + DC_FP_V_TIMING);

	/* Write final रेजिस्टर values. */
	ग_लिखोl(ocfg, par->dc_regs + DC_OUTPUT_CFG);
	ग_लिखोl(tcfg, par->dc_regs + DC_TIMING_CFG);
	udelay(1000); /* delay after TIMING_CFG. FIXME: perhaps a little दीर्घ */
	ग_लिखोl(gcfg, par->dc_regs + DC_GENERAL_CFG);

	par->vid_ops->configure_display(info);

	/* Relock display controller रेजिस्टरs */
	ग_लिखोl(0, par->dc_regs + DC_UNLOCK);

	/* FIXME: ग_लिखो line_length and bpp to Graphics Pipeline GP_BLT_STATUS
	 * रेजिस्टर. */
पूर्ण

अटल व्योम gx1_set_hw_palette_reg(काष्ठा fb_info *info, अचिन्हित regno,
				   अचिन्हित red, अचिन्हित green, अचिन्हित blue)
अणु
	काष्ठा geodefb_par *par = info->par;
	पूर्णांक val;

	/* Hardware palette is in RGB 6-6-6 क्रमmat. */
	val  = (red   <<  2) & 0x3f000;
	val |= (green >>  4) & 0x00fc0;
	val |= (blue  >> 10) & 0x0003f;

	ग_लिखोl(regno, par->dc_regs + DC_PAL_ADDRESS);
	ग_लिखोl(val, par->dc_regs + DC_PAL_DATA);
पूर्ण

स्थिर काष्ठा geode_dc_ops gx1_dc_ops = अणु
	.set_mode	 = gx1_set_mode,
	.set_palette_reg = gx1_set_hw_palette_reg,
पूर्ण;
