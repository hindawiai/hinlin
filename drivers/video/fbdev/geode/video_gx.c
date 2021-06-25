<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Geode GX video processor device.
 *
 *   Copyright (C) 2006 Arcom Control Systems Ltd.
 *
 *   Portions from AMD's original 2.4 driver:
 *     Copyright (C) 2004 Advanced Micro Devices, Inc.
 */
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/msr.h>
#समावेश <linux/cs5535.h>

#समावेश "gxfb.h"


/*
 * Tables of रेजिस्टर settings क्रम various DOTCLKs.
 */
काष्ठा gx_pll_entry अणु
	दीर्घ pixघड़ी; /* ps */
	u32 sys_rstpll_bits;
	u32 करोtpll_value;
पूर्ण;

#घोषणा POSTDIV3 ((u32)MSR_GLCP_SYS_RSTPLL_DOTPOSTDIV3)
#घोषणा PREMULT2 ((u32)MSR_GLCP_SYS_RSTPLL_DOTPREMULT2)
#घोषणा PREDIV2  ((u32)MSR_GLCP_SYS_RSTPLL_DOTPOSTDIV3)

अटल स्थिर काष्ठा gx_pll_entry gx_pll_table_48MHz[] = अणु
	अणु 40123, POSTDIV3,	    0x00000BF2 पूर्ण,	/*  24.9230 */
	अणु 39721, 0,		    0x00000037 पूर्ण,	/*  25.1750 */
	अणु 35308, POSTDIV3|PREMULT2, 0x00000B1A पूर्ण,	/*  28.3220 */
	अणु 31746, POSTDIV3,	    0x000002D2 पूर्ण,	/*  31.5000 */
	अणु 27777, POSTDIV3|PREMULT2, 0x00000FE2 पूर्ण,	/*  36.0000 */
	अणु 26666, POSTDIV3,	    0x0000057A पूर्ण,	/*  37.5000 */
	अणु 25000, POSTDIV3,	    0x0000030A पूर्ण,	/*  40.0000 */
	अणु 22271, 0,		    0x00000063 पूर्ण,	/*  44.9000 */
	अणु 20202, 0,		    0x0000054B पूर्ण,	/*  49.5000 */
	अणु 20000, 0,		    0x0000026E पूर्ण,	/*  50.0000 */
	अणु 19860, PREMULT2,	    0x00000037 पूर्ण,	/*  50.3500 */
	अणु 18518, POSTDIV3|PREMULT2, 0x00000B0D पूर्ण,	/*  54.0000 */
	अणु 17777, 0,		    0x00000577 पूर्ण,	/*  56.2500 */
	अणु 17733, 0,		    0x000007F7 पूर्ण,	/*  56.3916 */
	अणु 17653, 0,		    0x0000057B पूर्ण,	/*  56.6444 */
	अणु 16949, PREMULT2,	    0x00000707 पूर्ण,	/*  59.0000 */
	अणु 15873, POSTDIV3|PREMULT2, 0x00000B39 पूर्ण,	/*  63.0000 */
	अणु 15384, POSTDIV3|PREMULT2, 0x00000B45 पूर्ण,	/*  65.0000 */
	अणु 14814, POSTDIV3|PREMULT2, 0x00000FC1 पूर्ण,	/*  67.5000 */
	अणु 14124, POSTDIV3,	    0x00000561 पूर्ण,	/*  70.8000 */
	अणु 13888, POSTDIV3,	    0x000007E1 पूर्ण,	/*  72.0000 */
	अणु 13426, PREMULT2,	    0x00000F4A पूर्ण,	/*  74.4810 */
	अणु 13333, 0,		    0x00000052 पूर्ण,	/*  75.0000 */
	अणु 12698, 0,		    0x00000056 पूर्ण,	/*  78.7500 */
	अणु 12500, POSTDIV3|PREMULT2, 0x00000709 पूर्ण,	/*  80.0000 */
	अणु 11135, PREMULT2,	    0x00000262 पूर्ण,	/*  89.8000 */
	अणु 10582, 0,		    0x000002D2 पूर्ण,	/*  94.5000 */
	अणु 10101, PREMULT2,	    0x00000B4A पूर्ण,	/*  99.0000 */
	अणु 10000, PREMULT2,	    0x00000036 पूर्ण,	/* 100.0000 */
	अणु  9259, 0,		    0x000007E2 पूर्ण,	/* 108.0000 */
	अणु  8888, 0,		    0x000007F6 पूर्ण,	/* 112.5000 */
	अणु  7692, POSTDIV3|PREMULT2, 0x00000FB0 पूर्ण,	/* 130.0000 */
	अणु  7407, POSTDIV3|PREMULT2, 0x00000B50 पूर्ण,	/* 135.0000 */
	अणु  6349, 0,		    0x00000055 पूर्ण,	/* 157.5000 */
	अणु  6172, 0,		    0x000009C1 पूर्ण,	/* 162.0000 */
	अणु  5787, PREMULT2,	    0x0000002D पूर्ण,	/* 172.798  */
	अणु  5698, 0,		    0x000002C1 पूर्ण,	/* 175.5000 */
	अणु  5291, 0,		    0x000002D1 पूर्ण,	/* 189.0000 */
	अणु  4938, 0,		    0x00000551 पूर्ण,	/* 202.5000 */
	अणु  4357, 0,		    0x0000057D पूर्ण,	/* 229.5000 */
पूर्ण;

अटल स्थिर काष्ठा gx_pll_entry gx_pll_table_14MHz[] = अणु
	अणु 39721, 0, 0x00000037 पूर्ण,	/*  25.1750 */
	अणु 35308, 0, 0x00000B7B पूर्ण,	/*  28.3220 */
	अणु 31746, 0, 0x000004D3 पूर्ण,	/*  31.5000 */
	अणु 27777, 0, 0x00000BE3 पूर्ण,	/*  36.0000 */
	अणु 26666, 0, 0x0000074F पूर्ण,	/*  37.5000 */
	अणु 25000, 0, 0x0000050B पूर्ण,	/*  40.0000 */
	अणु 22271, 0, 0x00000063 पूर्ण,	/*  44.9000 */
	अणु 20202, 0, 0x0000054B पूर्ण,	/*  49.5000 */
	अणु 20000, 0, 0x0000026E पूर्ण,	/*  50.0000 */
	अणु 19860, 0, 0x000007C3 पूर्ण,	/*  50.3500 */
	अणु 18518, 0, 0x000007E3 पूर्ण,	/*  54.0000 */
	अणु 17777, 0, 0x00000577 पूर्ण,	/*  56.2500 */
	अणु 17733, 0, 0x000002FB पूर्ण,	/*  56.3916 */
	अणु 17653, 0, 0x0000057B पूर्ण,	/*  56.6444 */
	अणु 16949, 0, 0x0000058B पूर्ण,	/*  59.0000 */
	अणु 15873, 0, 0x0000095E पूर्ण,	/*  63.0000 */
	अणु 15384, 0, 0x0000096A पूर्ण,	/*  65.0000 */
	अणु 14814, 0, 0x00000BC2 पूर्ण,	/*  67.5000 */
	अणु 14124, 0, 0x0000098A पूर्ण,	/*  70.8000 */
	अणु 13888, 0, 0x00000BE2 पूर्ण,	/*  72.0000 */
	अणु 13333, 0, 0x00000052 पूर्ण,	/*  75.0000 */
	अणु 12698, 0, 0x00000056 पूर्ण,	/*  78.7500 */
	अणु 12500, 0, 0x0000050A पूर्ण,	/*  80.0000 */
	अणु 11135, 0, 0x0000078E पूर्ण,	/*  89.8000 */
	अणु 10582, 0, 0x000002D2 पूर्ण,	/*  94.5000 */
	अणु 10101, 0, 0x000011F6 पूर्ण,	/*  99.0000 */
	अणु 10000, 0, 0x0000054E पूर्ण,	/* 100.0000 */
	अणु  9259, 0, 0x000007E2 पूर्ण,	/* 108.0000 */
	अणु  8888, 0, 0x000002FA पूर्ण,	/* 112.5000 */
	अणु  7692, 0, 0x00000BB1 पूर्ण,	/* 130.0000 */
	अणु  7407, 0, 0x00000975 पूर्ण,	/* 135.0000 */
	अणु  6349, 0, 0x00000055 पूर्ण,	/* 157.5000 */
	अणु  6172, 0, 0x000009C1 पूर्ण,	/* 162.0000 */
	अणु  5698, 0, 0x000002C1 पूर्ण,	/* 175.5000 */
	अणु  5291, 0, 0x00000539 पूर्ण,	/* 189.0000 */
	अणु  4938, 0, 0x00000551 पूर्ण,	/* 202.5000 */
	अणु  4357, 0, 0x0000057D पूर्ण,	/* 229.5000 */
पूर्ण;

व्योम gx_set_dclk_frequency(काष्ठा fb_info *info)
अणु
	स्थिर काष्ठा gx_pll_entry *pll_table;
	पूर्णांक pll_table_len;
	पूर्णांक i, best_i;
	दीर्घ min, dअगरf;
	u64 करोtpll, sys_rstpll;
	पूर्णांक समयout = 1000;

	/* Rev. 1 Geode GXs use a 14 MHz reference घड़ी instead of 48 MHz. */
	अगर (cpu_data(0).x86_stepping == 1) अणु
		pll_table = gx_pll_table_14MHz;
		pll_table_len = ARRAY_SIZE(gx_pll_table_14MHz);
	पूर्ण अन्यथा अणु
		pll_table = gx_pll_table_48MHz;
		pll_table_len = ARRAY_SIZE(gx_pll_table_48MHz);
	पूर्ण

	/* Search the table क्रम the बंदst pixघड़ी. */
	best_i = 0;
	min = असल(pll_table[0].pixघड़ी - info->var.pixघड़ी);
	क्रम (i = 1; i < pll_table_len; i++) अणु
		dअगरf = असल(pll_table[i].pixघड़ी - info->var.pixघड़ी);
		अगर (dअगरf < min) अणु
			min = dअगरf;
			best_i = i;
		पूर्ण
	पूर्ण

	rdmsrl(MSR_GLCP_SYS_RSTPLL, sys_rstpll);
	rdmsrl(MSR_GLCP_DOTPLL, करोtpll);

	/* Program new M, N and P. */
	करोtpll &= 0x00000000ffffffffull;
	करोtpll |= (u64)pll_table[best_i].करोtpll_value << 32;
	करोtpll |= MSR_GLCP_DOTPLL_DOTRESET;
	करोtpll &= ~MSR_GLCP_DOTPLL_BYPASS;

	wrmsrl(MSR_GLCP_DOTPLL, करोtpll);

	/* Program भागiders. */
	sys_rstpll &= ~( MSR_GLCP_SYS_RSTPLL_DOTPREDIV2
			 | MSR_GLCP_SYS_RSTPLL_DOTPREMULT2
			 | MSR_GLCP_SYS_RSTPLL_DOTPOSTDIV3 );
	sys_rstpll |= pll_table[best_i].sys_rstpll_bits;

	wrmsrl(MSR_GLCP_SYS_RSTPLL, sys_rstpll);

	/* Clear reset bit to start PLL. */
	करोtpll &= ~(MSR_GLCP_DOTPLL_DOTRESET);
	wrmsrl(MSR_GLCP_DOTPLL, करोtpll);

	/* Wait क्रम LOCK bit. */
	करो अणु
		rdmsrl(MSR_GLCP_DOTPLL, करोtpll);
	पूर्ण जबतक (समयout-- && !(करोtpll & MSR_GLCP_DOTPLL_LOCK));
पूर्ण

अटल व्योम
gx_configure_tft(काष्ठा fb_info *info)
अणु
	काष्ठा gxfb_par *par = info->par;
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ fp;

	/* Set up the DF pad select MSR */

	rdmsrl(MSR_GX_MSR_PADSEL, val);
	val &= ~MSR_GX_MSR_PADSEL_MASK;
	val |= MSR_GX_MSR_PADSEL_TFT;
	wrmsrl(MSR_GX_MSR_PADSEL, val);

	/* Turn off the panel */

	fp = पढ़ो_fp(par, FP_PM);
	fp &= ~FP_PM_P;
	ग_लिखो_fp(par, FP_PM, fp);

	/* Set timing 1 */

	fp = पढ़ो_fp(par, FP_PT1);
	fp &= FP_PT1_VSIZE_MASK;
	fp |= info->var.yres << FP_PT1_VSIZE_SHIFT;
	ग_लिखो_fp(par, FP_PT1, fp);

	/* Timing 2 */
	/* Set bits that are always on क्रम TFT */

	fp = 0x0F100000;

	/* Configure sync polarity */

	अगर (!(info->var.sync & FB_SYNC_VERT_HIGH_ACT))
		fp |= FP_PT2_VSP;

	अगर (!(info->var.sync & FB_SYNC_HOR_HIGH_ACT))
		fp |= FP_PT2_HSP;

	ग_लिखो_fp(par, FP_PT2, fp);

	/*  Set the dither control */
	ग_लिखो_fp(par, FP_DFC, FP_DFC_NFI);

	/* Enable the FP data and घातer (in हाल the BIOS didn't) */

	fp = पढ़ो_vp(par, VP_DCFG);
	fp |= VP_DCFG_FP_PWR_EN | VP_DCFG_FP_DATA_EN;
	ग_लिखो_vp(par, VP_DCFG, fp);

	/* Unblank the panel */

	fp = पढ़ो_fp(par, FP_PM);
	fp |= FP_PM_P;
	ग_लिखो_fp(par, FP_PM, fp);
पूर्ण

व्योम gx_configure_display(काष्ठा fb_info *info)
अणु
	काष्ठा gxfb_par *par = info->par;
	u32 dcfg, misc;

	/* Write the display configuration */
	dcfg = पढ़ो_vp(par, VP_DCFG);

	/* Disable hsync and vsync */
	dcfg &= ~(VP_DCFG_VSYNC_EN | VP_DCFG_HSYNC_EN);
	ग_लिखो_vp(par, VP_DCFG, dcfg);

	/* Clear bits from existing mode. */
	dcfg &= ~(VP_DCFG_CRT_SYNC_SKW
		  | VP_DCFG_CRT_HSYNC_POL   | VP_DCFG_CRT_VSYNC_POL
		  | VP_DCFG_VSYNC_EN        | VP_DCFG_HSYNC_EN);

	/* Set शेष sync skew.  */
	dcfg |= VP_DCFG_CRT_SYNC_SKW_DEFAULT;

	/* Enable hsync and vsync. */
	dcfg |= VP_DCFG_HSYNC_EN | VP_DCFG_VSYNC_EN;

	misc = पढ़ो_vp(par, VP_MISC);

	/* Disable gamma correction */
	misc |= VP_MISC_GAM_EN;

	अगर (par->enable_crt) अणु

		/* Power up the CRT DACs */
		misc &= ~(VP_MISC_APWRDN | VP_MISC_DACPWRDN);
		ग_लिखो_vp(par, VP_MISC, misc);

		/* Only change the sync polarities अगर we are running
		 * in CRT mode.  The FP polarities will be handled in
		 * gxfb_configure_tft */
		अगर (!(info->var.sync & FB_SYNC_HOR_HIGH_ACT))
			dcfg |= VP_DCFG_CRT_HSYNC_POL;
		अगर (!(info->var.sync & FB_SYNC_VERT_HIGH_ACT))
			dcfg |= VP_DCFG_CRT_VSYNC_POL;
	पूर्ण अन्यथा अणु
		/* Power करोwn the CRT DACs अगर in FP mode */
		misc |= (VP_MISC_APWRDN | VP_MISC_DACPWRDN);
		ग_लिखो_vp(par, VP_MISC, misc);
	पूर्ण

	/* Enable the display logic */
	/* Set up the DACS to blank normally */

	dcfg |= VP_DCFG_CRT_EN | VP_DCFG_DAC_BL_EN;

	/* Enable the बाह्यal DAC VREF? */

	ग_लिखो_vp(par, VP_DCFG, dcfg);

	/* Set up the flat panel (अगर it is enabled) */

	अगर (par->enable_crt == 0)
		gx_configure_tft(info);
पूर्ण

पूर्णांक gx_blank_display(काष्ठा fb_info *info, पूर्णांक blank_mode)
अणु
	काष्ठा gxfb_par *par = info->par;
	u32 dcfg, fp_pm;
	पूर्णांक blank, hsync, vsync, crt;

	/* CRT घातer saving modes. */
	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		blank = 0; hsync = 1; vsync = 1; crt = 1;
		अवरोध;
	हाल FB_BLANK_NORMAL:
		blank = 1; hsync = 1; vsync = 1; crt = 1;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		blank = 1; hsync = 1; vsync = 0; crt = 1;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		blank = 1; hsync = 0; vsync = 1; crt = 1;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		blank = 1; hsync = 0; vsync = 0; crt = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	dcfg = पढ़ो_vp(par, VP_DCFG);
	dcfg &= ~(VP_DCFG_DAC_BL_EN | VP_DCFG_HSYNC_EN | VP_DCFG_VSYNC_EN |
			VP_DCFG_CRT_EN);
	अगर (!blank)
		dcfg |= VP_DCFG_DAC_BL_EN;
	अगर (hsync)
		dcfg |= VP_DCFG_HSYNC_EN;
	अगर (vsync)
		dcfg |= VP_DCFG_VSYNC_EN;
	अगर (crt)
		dcfg |= VP_DCFG_CRT_EN;
	ग_लिखो_vp(par, VP_DCFG, dcfg);

	/* Power on/off flat panel. */

	अगर (par->enable_crt == 0) अणु
		fp_pm = पढ़ो_fp(par, FP_PM);
		अगर (blank_mode == FB_BLANK_POWERDOWN)
			fp_pm &= ~FP_PM_P;
		अन्यथा
			fp_pm |= FP_PM_P;
		ग_लिखो_fp(par, FP_PM, fp_pm);
	पूर्ण

	वापस 0;
पूर्ण
