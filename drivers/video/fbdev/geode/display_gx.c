<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Geode GX display controller.
 *
 *   Copyright (C) 2005 Arcom Control Systems Ltd.
 *
 *   Portions from AMD's original 2.4 driver:
 *     Copyright (C) 2004 Advanced Micro Devices, Inc.
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/delay.h>
#समावेश <linux/cs5535.h>

#समावेश "gxfb.h"

अचिन्हित पूर्णांक gx_frame_buffer_size(व्योम)
अणु
	अचिन्हित पूर्णांक val;

	अगर (!cs5535_has_vsa2()) अणु
		uपूर्णांक32_t hi, lo;

		/* The number of pages is (PMAX - PMIN)+1 */
		rdmsr(MSR_GLIU_P2D_RO0, lo, hi);

		/* PMAX */
		val = ((hi & 0xff) << 12) | ((lo & 0xfff00000) >> 20);
		/* PMIN */
		val -= (lo & 0x000fffff);
		val += 1;

		/* The page size is 4k */
		वापस (val << 12);
	पूर्ण

	/* FB size can be obtained from the VSA II */
	/* Virtual रेजिस्टर class = 0x02 */
	/* VG_MEM_SIZE(512Kb units) = 0x00 */

	outw(VSA_VR_UNLOCK, VSA_VRC_INDEX);
	outw(VSA_VR_MEM_SIZE, VSA_VRC_INDEX);

	val = (अचिन्हित पूर्णांक)(inw(VSA_VRC_DATA)) & 0xFFl;
	वापस (val << 19);
पूर्ण

पूर्णांक gx_line_delta(पूर्णांक xres, पूर्णांक bpp)
अणु
	/* Must be a multiple of 8 bytes. */
	वापस (xres * (bpp >> 3) + 7) & ~0x7;
पूर्ण

व्योम gx_set_mode(काष्ठा fb_info *info)
अणु
	काष्ठा gxfb_par *par = info->par;
	u32 gcfg, dcfg;
	पूर्णांक hactive, hblankstart, hsyncstart, hsyncend, hblankend, htotal;
	पूर्णांक vactive, vblankstart, vsyncstart, vsyncend, vblankend, vtotal;

	/* Unlock the display controller रेजिस्टरs. */
	ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);

	gcfg = पढ़ो_dc(par, DC_GENERAL_CFG);
	dcfg = पढ़ो_dc(par, DC_DISPLAY_CFG);

	/* Disable the timing generator. */
	dcfg &= ~DC_DISPLAY_CFG_TGEN;
	ग_लिखो_dc(par, DC_DISPLAY_CFG, dcfg);

	/* Wait क्रम pending memory requests beक्रमe disabling the FIFO load. */
	udelay(100);

	/* Disable FIFO load and compression. */
	gcfg &= ~(DC_GENERAL_CFG_DFLE | DC_GENERAL_CFG_CMPE |
			DC_GENERAL_CFG_DECE);
	ग_लिखो_dc(par, DC_GENERAL_CFG, gcfg);

	/* Setup DCLK and its भागisor. */
	gx_set_dclk_frequency(info);

	/*
	 * Setup new mode.
	 */

	/* Clear all unused feature bits. */
	gcfg &= DC_GENERAL_CFG_YUVM | DC_GENERAL_CFG_VDSE;
	dcfg = 0;

	/* Set FIFO priority (शेष 6/5) and enable. */
	/* FIXME: increase fअगरo priority क्रम 1280x1024 and higher modes? */
	gcfg |= (6 << DC_GENERAL_CFG_DFHPEL_SHIFT) |
		(5 << DC_GENERAL_CFG_DFHPSL_SHIFT) | DC_GENERAL_CFG_DFLE;

	/* Framebuffer start offset. */
	ग_लिखो_dc(par, DC_FB_ST_OFFSET, 0);

	/* Line delta and line buffer length. */
	ग_लिखो_dc(par, DC_GFX_PITCH, info->fix.line_length >> 3);
	ग_लिखो_dc(par, DC_LINE_SIZE,
		((info->var.xres * info->var.bits_per_pixel/8) >> 3) + 2);


	/* Enable graphics and video data and unmask address lines. */
	dcfg |= DC_DISPLAY_CFG_GDEN | DC_DISPLAY_CFG_VDEN |
		DC_DISPLAY_CFG_A20M | DC_DISPLAY_CFG_A18M;

	/* Set pixel क्रमmat. */
	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		dcfg |= DC_DISPLAY_CFG_DISP_MODE_8BPP;
		अवरोध;
	हाल 16:
		dcfg |= DC_DISPLAY_CFG_DISP_MODE_16BPP;
		अवरोध;
	हाल 32:
		dcfg |= DC_DISPLAY_CFG_DISP_MODE_24BPP;
		dcfg |= DC_DISPLAY_CFG_PALB;
		अवरोध;
	पूर्ण

	/* Enable timing generator. */
	dcfg |= DC_DISPLAY_CFG_TGEN;

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

	ग_लिखो_dc(par, DC_H_ACTIVE_TIMING, (hactive - 1)    |
			((htotal - 1) << 16));
	ग_लिखो_dc(par, DC_H_BLANK_TIMING, (hblankstart - 1) |
			((hblankend - 1) << 16));
	ग_लिखो_dc(par, DC_H_SYNC_TIMING, (hsyncstart - 1)   |
			((hsyncend - 1) << 16));

	ग_लिखो_dc(par, DC_V_ACTIVE_TIMING, (vactive - 1)    |
			((vtotal - 1) << 16));
	ग_लिखो_dc(par, DC_V_BLANK_TIMING, (vblankstart - 1) |
			((vblankend - 1) << 16));
	ग_लिखो_dc(par, DC_V_SYNC_TIMING, (vsyncstart - 1)   |
			((vsyncend - 1) << 16));

	/* Write final रेजिस्टर values. */
	ग_लिखो_dc(par, DC_DISPLAY_CFG, dcfg);
	ग_लिखो_dc(par, DC_GENERAL_CFG, gcfg);

	gx_configure_display(info);

	/* Relock display controller रेजिस्टरs */
	ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_LOCK);
पूर्ण

व्योम gx_set_hw_palette_reg(काष्ठा fb_info *info, अचिन्हित regno,
		अचिन्हित red, अचिन्हित green, अचिन्हित blue)
अणु
	काष्ठा gxfb_par *par = info->par;
	पूर्णांक val;

	/* Hardware palette is in RGB 8-8-8 क्रमmat. */
	val  = (red   << 8) & 0xff0000;
	val |= (green)      & 0x00ff00;
	val |= (blue  >> 8) & 0x0000ff;

	ग_लिखो_dc(par, DC_PAL_ADDRESS, regno);
	ग_लिखो_dc(par, DC_PAL_DATA, val);
पूर्ण
