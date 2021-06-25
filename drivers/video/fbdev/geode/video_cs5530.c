<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/video/geode/video_cs5530.c
 *   -- CS5530 video device
 *
 * Copyright (C) 2005 Arcom Control Systems Ltd.
 *
 * Based on AMD's original 2.4 driver:
 *   Copyright (C) 2004 Advanced Micro Devices, Inc.
 */
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/delay.h>

#समावेश "geodefb.h"
#समावेश "video_cs5530.h"

/*
 * CS5530 PLL table. This maps pixघड़ीs to the appropriate PLL रेजिस्टर
 * value.
 */
काष्ठा cs5530_pll_entry अणु
	दीर्घ pixघड़ी; /* ps */
	u32 pll_value;
पूर्ण;

अटल स्थिर काष्ठा cs5530_pll_entry cs5530_pll_table[] = अणु
	अणु 39721, 0x31C45801, पूर्ण, /*  25.1750 MHz */
	अणु 35308, 0x20E36802, पूर्ण, /*  28.3220 */
	अणु 31746, 0x33915801, पूर्ण, /*  31.5000 */
	अणु 27777, 0x31EC4801, पूर्ण, /*  36.0000 */
	अणु 26666, 0x21E22801, पूर्ण, /*  37.5000 */
	अणु 25000, 0x33088801, पूर्ण, /*  40.0000 */
	अणु 22271, 0x33E22801, पूर्ण, /*  44.9000 */
	अणु 20202, 0x336C4801, पूर्ण, /*  49.5000 */
	अणु 20000, 0x23088801, पूर्ण, /*  50.0000 */
	अणु 19860, 0x23088801, पूर्ण, /*  50.3500 */
	अणु 18518, 0x3708A801, पूर्ण, /*  54.0000 */
	अणु 17777, 0x23E36802, पूर्ण, /*  56.2500 */
	अणु 17733, 0x23E36802, पूर्ण, /*  56.3916 */
	अणु 17653, 0x23E36802, पूर्ण, /*  56.6444 */
	अणु 16949, 0x37C45801, पूर्ण, /*  59.0000 */
	अणु 15873, 0x23EC4801, पूर्ण, /*  63.0000 */
	अणु 15384, 0x37911801, पूर्ण, /*  65.0000 */
	अणु 14814, 0x37963803, पूर्ण, /*  67.5000 */
	अणु 14124, 0x37058803, पूर्ण, /*  70.8000 */
	अणु 13888, 0x3710C805, पूर्ण, /*  72.0000 */
	अणु 13333, 0x37E22801, पूर्ण, /*  75.0000 */
	अणु 12698, 0x27915801, पूर्ण, /*  78.7500 */
	अणु 12500, 0x37D8D802, पूर्ण, /*  80.0000 */
	अणु 11135, 0x27588802, पूर्ण, /*  89.8000 */
	अणु 10582, 0x27EC4802, पूर्ण, /*  94.5000 */
	अणु 10101, 0x27AC6803, पूर्ण, /*  99.0000 */
	अणु 10000, 0x27088801, पूर्ण, /* 100.0000 */
	अणु  9259, 0x2710C805, पूर्ण, /* 108.0000 */
	अणु  8888, 0x27E36802, पूर्ण, /* 112.5000 */
	अणु  7692, 0x27C58803, पूर्ण, /* 130.0000 */
	अणु  7407, 0x27316803, पूर्ण, /* 135.0000 */
	अणु  6349, 0x2F915801, पूर्ण, /* 157.5000 */
	अणु  6172, 0x2F08A801, पूर्ण, /* 162.0000 */
	अणु  5714, 0x2FB11802, पूर्ण, /* 175.0000 */
	अणु  5291, 0x2FEC4802, पूर्ण, /* 189.0000 */
	अणु  4950, 0x2F963803, पूर्ण, /* 202.0000 */
	अणु  4310, 0x2FB1B802, पूर्ण, /* 232.0000 */
पूर्ण;

अटल व्योम cs5530_set_dclk_frequency(काष्ठा fb_info *info)
अणु
	काष्ठा geodefb_par *par = info->par;
	पूर्णांक i;
	u32 value;
	दीर्घ min, dअगरf;

	/* Search the table क्रम the बंदst pixघड़ी. */
	value = cs5530_pll_table[0].pll_value;
	min = cs5530_pll_table[0].pixघड़ी - info->var.pixघड़ी;
	अगर (min < 0) min = -min;
	क्रम (i = 1; i < ARRAY_SIZE(cs5530_pll_table); i++) अणु
		dअगरf = cs5530_pll_table[i].pixघड़ी - info->var.pixघड़ी;
		अगर (dअगरf < 0L) dअगरf = -dअगरf;
		अगर (dअगरf < min) अणु
			min = dअगरf;
			value = cs5530_pll_table[i].pll_value;
		पूर्ण
	पूर्ण

	ग_लिखोl(value, par->vid_regs + CS5530_DOT_CLK_CONFIG);
	ग_लिखोl(value | 0x80000100, par->vid_regs + CS5530_DOT_CLK_CONFIG); /* set reset and bypass */
	udelay(500); /* रुको क्रम PLL to settle */
	ग_लिखोl(value & 0x7FFFFFFF, par->vid_regs + CS5530_DOT_CLK_CONFIG); /* clear reset */
	ग_लिखोl(value & 0x7FFFFEFF, par->vid_regs + CS5530_DOT_CLK_CONFIG); /* clear bypass */
पूर्ण

अटल व्योम cs5530_configure_display(काष्ठा fb_info *info)
अणु
	काष्ठा geodefb_par *par = info->par;
	u32 dcfg;

	dcfg = पढ़ोl(par->vid_regs + CS5530_DISPLAY_CONFIG);

	/* Clear bits from existing mode. */
	dcfg &= ~(CS5530_DCFG_CRT_SYNC_SKW_MASK | CS5530_DCFG_PWR_SEQ_DLY_MASK
		  | CS5530_DCFG_CRT_HSYNC_POL   | CS5530_DCFG_CRT_VSYNC_POL
		  | CS5530_DCFG_FP_PWR_EN       | CS5530_DCFG_FP_DATA_EN
		  | CS5530_DCFG_DAC_PWR_EN      | CS5530_DCFG_VSYNC_EN
		  | CS5530_DCFG_HSYNC_EN);

	/* Set शेष sync skew and घातer sequence delays.  */
	dcfg |= (CS5530_DCFG_CRT_SYNC_SKW_INIT | CS5530_DCFG_PWR_SEQ_DLY_INIT
		 | CS5530_DCFG_GV_PAL_BYP);

	/* Enable DACs, hsync and vsync क्रम CRTs */
	अगर (par->enable_crt) अणु
		dcfg |= CS5530_DCFG_DAC_PWR_EN;
		dcfg |= CS5530_DCFG_HSYNC_EN | CS5530_DCFG_VSYNC_EN;
	पूर्ण
	/* Enable panel घातer and data अगर using a flat panel. */
	अगर (par->panel_x > 0) अणु
		dcfg |= CS5530_DCFG_FP_PWR_EN;
		dcfg |= CS5530_DCFG_FP_DATA_EN;
	पूर्ण

	/* Sync polarities. */
	अगर (info->var.sync & FB_SYNC_HOR_HIGH_ACT)
		dcfg |= CS5530_DCFG_CRT_HSYNC_POL;
	अगर (info->var.sync & FB_SYNC_VERT_HIGH_ACT)
		dcfg |= CS5530_DCFG_CRT_VSYNC_POL;

	ग_लिखोl(dcfg, par->vid_regs + CS5530_DISPLAY_CONFIG);
पूर्ण

अटल पूर्णांक cs5530_blank_display(काष्ठा fb_info *info, पूर्णांक blank_mode)
अणु
	काष्ठा geodefb_par *par = info->par;
	u32 dcfg;
	पूर्णांक blank, hsync, vsync;

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		blank = 0; hsync = 1; vsync = 1;
		अवरोध;
	हाल FB_BLANK_NORMAL:
		blank = 1; hsync = 1; vsync = 1;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		blank = 1; hsync = 1; vsync = 0;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		blank = 1; hsync = 0; vsync = 1;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		blank = 1; hsync = 0; vsync = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dcfg = पढ़ोl(par->vid_regs + CS5530_DISPLAY_CONFIG);

	dcfg &= ~(CS5530_DCFG_DAC_BL_EN | CS5530_DCFG_DAC_PWR_EN
		  | CS5530_DCFG_HSYNC_EN | CS5530_DCFG_VSYNC_EN
		  | CS5530_DCFG_FP_DATA_EN | CS5530_DCFG_FP_PWR_EN);

	अगर (par->enable_crt) अणु
		अगर (!blank)
			dcfg |= CS5530_DCFG_DAC_BL_EN | CS5530_DCFG_DAC_PWR_EN;
		अगर (hsync)
			dcfg |= CS5530_DCFG_HSYNC_EN;
		अगर (vsync)
			dcfg |= CS5530_DCFG_VSYNC_EN;
	पूर्ण
	अगर (par->panel_x > 0) अणु
		अगर (!blank)
			dcfg |= CS5530_DCFG_FP_DATA_EN;
		अगर (hsync && vsync)
			dcfg |= CS5530_DCFG_FP_PWR_EN;
	पूर्ण

	ग_लिखोl(dcfg, par->vid_regs + CS5530_DISPLAY_CONFIG);

	वापस 0;
पूर्ण

स्थिर काष्ठा geode_vid_ops cs5530_vid_ops = अणु
	.set_dclk          = cs5530_set_dclk_frequency,
	.configure_display = cs5530_configure_display,
	.blank_display     = cs5530_blank_display,
पूर्ण;
