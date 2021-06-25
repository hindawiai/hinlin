<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Geode LX framebuffer driver
 *
 * Copyright (C) 2006-2007, Advanced Micro Devices,Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>
#समावेश <linux/cs5535.h>

#समावेश "lxfb.h"

/* TODO
 * Support panel scaling
 * Add acceleration
 * Add support क्रम पूर्णांकerlacing (TV out)
 * Support compression
 */

/* This is the complete list of PLL frequencies that we can set -
 * we will choose the बंदst match to the incoming घड़ी.
 * freq is the frequency of the करोtघड़ी * 1000 (क्रम example,
 * 24823 = 24.983 Mhz).
 * pllval is the corresponding PLL value
*/

अटल स्थिर काष्ठा अणु
  अचिन्हित पूर्णांक pllval;
  अचिन्हित पूर्णांक freq;
पूर्ण pll_table[] = अणु
  अणु 0x000131AC,   6231 पूर्ण,
  अणु 0x0001215D,   6294 पूर्ण,
  अणु 0x00011087,   6750 पूर्ण,
  अणु 0x0001216C,   7081 पूर्ण,
  अणु 0x0001218D,   7140 पूर्ण,
  अणु 0x000110C9,   7800 पूर्ण,
  अणु 0x00013147,   7875 पूर्ण,
  अणु 0x000110A7,   8258 पूर्ण,
  अणु 0x00012159,   8778 पूर्ण,
  अणु 0x00014249,   8875 पूर्ण,
  अणु 0x00010057,   9000 पूर्ण,
  अणु 0x0001219A,   9472 पूर्ण,
  अणु 0x00012158,   9792 पूर्ण,
  अणु 0x00010045,  10000 पूर्ण,
  अणु 0x00010089,  10791 पूर्ण,
  अणु 0x000110E7,  11225 पूर्ण,
  अणु 0x00012136,  11430 पूर्ण,
  अणु 0x00013207,  12375 पूर्ण,
  अणु 0x00012187,  12500 पूर्ण,
  अणु 0x00014286,  14063 पूर्ण,
  अणु 0x000110E5,  15016 पूर्ण,
  अणु 0x00014214,  16250 पूर्ण,
  अणु 0x00011105,  17045 पूर्ण,
  अणु 0x000131E4,  18563 पूर्ण,
  अणु 0x00013183,  18750 पूर्ण,
  अणु 0x00014284,  19688 पूर्ण,
  अणु 0x00011104,  20400 पूर्ण,
  अणु 0x00016363,  23625 पूर्ण,
  अणु 0x000031AC,  24923 पूर्ण,
  अणु 0x0000215D,  25175 पूर्ण,
  अणु 0x00001087,  27000 पूर्ण,
  अणु 0x0000216C,  28322 पूर्ण,
  अणु 0x0000218D,  28560 पूर्ण,
  अणु 0x000010C9,  31200 पूर्ण,
  अणु 0x00003147,  31500 पूर्ण,
  अणु 0x000010A7,  33032 पूर्ण,
  अणु 0x00002159,  35112 पूर्ण,
  अणु 0x00004249,  35500 पूर्ण,
  अणु 0x00000057,  36000 पूर्ण,
  अणु 0x0000219A,  37889 पूर्ण,
  अणु 0x00002158,  39168 पूर्ण,
  अणु 0x00000045,  40000 पूर्ण,
  अणु 0x00000089,  43163 पूर्ण,
  अणु 0x000010E7,  44900 पूर्ण,
  अणु 0x00002136,  45720 पूर्ण,
  अणु 0x00003207,  49500 पूर्ण,
  अणु 0x00002187,  50000 पूर्ण,
  अणु 0x00004286,  56250 पूर्ण,
  अणु 0x000010E5,  60065 पूर्ण,
  अणु 0x00004214,  65000 पूर्ण,
  अणु 0x00001105,  68179 पूर्ण,
  अणु 0x000031E4,  74250 पूर्ण,
  अणु 0x00003183,  75000 पूर्ण,
  अणु 0x00004284,  78750 पूर्ण,
  अणु 0x00001104,  81600 पूर्ण,
  अणु 0x00006363,  94500 पूर्ण,
  अणु 0x00005303,  97520 पूर्ण,
  अणु 0x00002183, 100187 पूर्ण,
  अणु 0x00002122, 101420 पूर्ण,
  अणु 0x00001081, 108000 पूर्ण,
  अणु 0x00006201, 113310 पूर्ण,
  अणु 0x00000041, 119650 पूर्ण,
  अणु 0x000041A1, 129600 पूर्ण,
  अणु 0x00002182, 133500 पूर्ण,
  अणु 0x000041B1, 135000 पूर्ण,
  अणु 0x00000051, 144000 पूर्ण,
  अणु 0x000041E1, 148500 पूर्ण,
  अणु 0x000062D1, 157500 पूर्ण,
  अणु 0x000031A1, 162000 पूर्ण,
  अणु 0x00000061, 169203 पूर्ण,
  अणु 0x00004231, 172800 पूर्ण,
  अणु 0x00002151, 175500 पूर्ण,
  अणु 0x000052E1, 189000 पूर्ण,
  अणु 0x00000071, 192000 पूर्ण,
  अणु 0x00003201, 198000 पूर्ण,
  अणु 0x00004291, 202500 पूर्ण,
  अणु 0x00001101, 204750 पूर्ण,
  अणु 0x00007481, 218250 पूर्ण,
  अणु 0x00004170, 229500 पूर्ण,
  अणु 0x00006210, 234000 पूर्ण,
  अणु 0x00003140, 251182 पूर्ण,
  अणु 0x00006250, 261000 पूर्ण,
  अणु 0x000041C0, 278400 पूर्ण,
  अणु 0x00005220, 280640 पूर्ण,
  अणु 0x00000050, 288000 पूर्ण,
  अणु 0x000041E0, 297000 पूर्ण,
  अणु 0x00002130, 320207 पूर्ण
पूर्ण;


अटल व्योम lx_set_करोtpll(u32 pllval)
अणु
	u32 करोtpll_lo, करोtpll_hi;
	पूर्णांक i;

	rdmsr(MSR_GLCP_DOTPLL, करोtpll_lo, करोtpll_hi);

	अगर ((करोtpll_lo & MSR_GLCP_DOTPLL_LOCK) && (करोtpll_hi == pllval))
		वापस;

	करोtpll_hi = pllval;
	करोtpll_lo &= ~(MSR_GLCP_DOTPLL_BYPASS | MSR_GLCP_DOTPLL_HALFPIX);
	करोtpll_lo |= MSR_GLCP_DOTPLL_DOTRESET;

	wrmsr(MSR_GLCP_DOTPLL, करोtpll_lo, करोtpll_hi);

	/* Wait 100us क्रम the PLL to lock */

	udelay(100);

	/* Now, loop क्रम the lock bit */

	क्रम (i = 0; i < 1000; i++) अणु
		rdmsr(MSR_GLCP_DOTPLL, करोtpll_lo, करोtpll_hi);
		अगर (करोtpll_lo & MSR_GLCP_DOTPLL_LOCK)
			अवरोध;
	पूर्ण

	/* Clear the reset bit */

	करोtpll_lo &= ~MSR_GLCP_DOTPLL_DOTRESET;
	wrmsr(MSR_GLCP_DOTPLL, करोtpll_lo, करोtpll_hi);
पूर्ण

/* Set the घड़ी based on the frequency specअगरied by the current mode */

अटल व्योम lx_set_घड़ी(काष्ठा fb_info *info)
अणु
	अचिन्हित पूर्णांक dअगरf, min, best = 0;
	अचिन्हित पूर्णांक freq, i;

	freq = (अचिन्हित पूर्णांक) (1000000000 / info->var.pixघड़ी);

	min = असल(pll_table[0].freq - freq);

	क्रम (i = 0; i < ARRAY_SIZE(pll_table); i++) अणु
		dअगरf = असल(pll_table[i].freq - freq);
		अगर (dअगरf < min) अणु
			min = dअगरf;
			best = i;
		पूर्ण
	पूर्ण

	lx_set_करोtpll(pll_table[best].pllval & 0x00017FFF);
पूर्ण

अटल व्योम lx_graphics_disable(काष्ठा fb_info *info)
अणु
	काष्ठा lxfb_par *par = info->par;
	अचिन्हित पूर्णांक val, gcfg;

	/* Note:  This assumes that the video is in a quitet state */

	ग_लिखो_vp(par, VP_A1T, 0);
	ग_लिखो_vp(par, VP_A2T, 0);
	ग_लिखो_vp(par, VP_A3T, 0);

	/* Turn off the VGA and video enable */
	val = पढ़ो_dc(par, DC_GENERAL_CFG) & ~(DC_GENERAL_CFG_VGAE |
			DC_GENERAL_CFG_VIDE);

	ग_लिखो_dc(par, DC_GENERAL_CFG, val);

	val = पढ़ो_vp(par, VP_VCFG) & ~VP_VCFG_VID_EN;
	ग_लिखो_vp(par, VP_VCFG, val);

	ग_लिखो_dc(par, DC_IRQ, DC_IRQ_MASK | DC_IRQ_VIP_VSYNC_LOSS_IRQ_MASK |
			DC_IRQ_STATUS | DC_IRQ_VIP_VSYNC_IRQ_STATUS);

	val = पढ़ो_dc(par, DC_GENLK_CTL) & ~DC_GENLK_CTL_GENLK_EN;
	ग_लिखो_dc(par, DC_GENLK_CTL, val);

	val = पढ़ो_dc(par, DC_CLR_KEY);
	ग_लिखो_dc(par, DC_CLR_KEY, val & ~DC_CLR_KEY_CLR_KEY_EN);

	/* turn off the panel */
	ग_लिखो_fp(par, FP_PM, पढ़ो_fp(par, FP_PM) & ~FP_PM_P);

	val = पढ़ो_vp(par, VP_MISC) | VP_MISC_DACPWRDN;
	ग_लिखो_vp(par, VP_MISC, val);

	/* Turn off the display */

	val = पढ़ो_vp(par, VP_DCFG);
	ग_लिखो_vp(par, VP_DCFG, val & ~(VP_DCFG_CRT_EN | VP_DCFG_HSYNC_EN |
			VP_DCFG_VSYNC_EN | VP_DCFG_DAC_BL_EN));

	gcfg = पढ़ो_dc(par, DC_GENERAL_CFG);
	gcfg &= ~(DC_GENERAL_CFG_CMPE | DC_GENERAL_CFG_DECE);
	ग_लिखो_dc(par, DC_GENERAL_CFG, gcfg);

	/* Turn off the TGEN */
	val = पढ़ो_dc(par, DC_DISPLAY_CFG);
	val &= ~DC_DISPLAY_CFG_TGEN;
	ग_लिखो_dc(par, DC_DISPLAY_CFG, val);

	/* Wait 1000 usecs to ensure that the TGEN is clear */
	udelay(1000);

	/* Turn off the FIFO loader */

	gcfg &= ~DC_GENERAL_CFG_DFLE;
	ग_लिखो_dc(par, DC_GENERAL_CFG, gcfg);

	/* Lastly, रुको क्रम the GP to go idle */

	करो अणु
		val = पढ़ो_gp(par, GP_BLT_STATUS);
	पूर्ण जबतक ((val & GP_BLT_STATUS_PB) || !(val & GP_BLT_STATUS_CE));
पूर्ण

अटल व्योम lx_graphics_enable(काष्ठा fb_info *info)
अणु
	काष्ठा lxfb_par *par = info->par;
	u32 temp, config;

	/* Set the video request रेजिस्टर */
	ग_लिखो_vp(par, VP_VRR, 0);

	/* Set up the polarities */

	config = पढ़ो_vp(par, VP_DCFG);

	config &= ~(VP_DCFG_CRT_SYNC_SKW | VP_DCFG_PWR_SEQ_DELAY |
			VP_DCFG_CRT_HSYNC_POL | VP_DCFG_CRT_VSYNC_POL);

	config |= (VP_DCFG_CRT_SYNC_SKW_DEFAULT | VP_DCFG_PWR_SEQ_DELAY_DEFAULT
			| VP_DCFG_GV_GAM);

	अगर (info->var.sync & FB_SYNC_HOR_HIGH_ACT)
		config |= VP_DCFG_CRT_HSYNC_POL;

	अगर (info->var.sync & FB_SYNC_VERT_HIGH_ACT)
		config |= VP_DCFG_CRT_VSYNC_POL;

	अगर (par->output & OUTPUT_PANEL) अणु
		u32 msrlo, msrhi;

		ग_लिखो_fp(par, FP_PT1, 0);
		temp = FP_PT2_SCRC;

		अगर (!(info->var.sync & FB_SYNC_HOR_HIGH_ACT))
			temp |= FP_PT2_HSP;

		अगर (!(info->var.sync & FB_SYNC_VERT_HIGH_ACT))
			temp |= FP_PT2_VSP;

		ग_लिखो_fp(par, FP_PT2, temp);
		ग_लिखो_fp(par, FP_DFC, FP_DFC_BC);

		msrlo = MSR_LX_MSR_PADSEL_TFT_SEL_LOW;
		msrhi = MSR_LX_MSR_PADSEL_TFT_SEL_HIGH;

		wrmsr(MSR_LX_MSR_PADSEL, msrlo, msrhi);
	पूर्ण

	अगर (par->output & OUTPUT_CRT) अणु
		config |= VP_DCFG_CRT_EN | VP_DCFG_HSYNC_EN |
				VP_DCFG_VSYNC_EN | VP_DCFG_DAC_BL_EN;
	पूर्ण

	ग_लिखो_vp(par, VP_DCFG, config);

	/* Turn the CRT dacs back on */

	अगर (par->output & OUTPUT_CRT) अणु
		temp = पढ़ो_vp(par, VP_MISC);
		temp &= ~(VP_MISC_DACPWRDN | VP_MISC_APWRDN);
		ग_लिखो_vp(par, VP_MISC, temp);
	पूर्ण

	/* Turn the panel on (अगर it isn't alपढ़ोy) */
	अगर (par->output & OUTPUT_PANEL)
		ग_लिखो_fp(par, FP_PM, पढ़ो_fp(par, FP_PM) | FP_PM_P);
पूर्ण

अचिन्हित पूर्णांक lx_framebuffer_size(व्योम)
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

	/* The frame buffer size is reported by a VSM in VSA II */
	/* Virtual Register Class    = 0x02                     */
	/* VG_MEM_SIZE (1MB units)   = 0x00                     */

	outw(VSA_VR_UNLOCK, VSA_VRC_INDEX);
	outw(VSA_VR_MEM_SIZE, VSA_VRC_INDEX);

	val = (अचिन्हित पूर्णांक)(inw(VSA_VRC_DATA)) & 0xFE;
	वापस (val << 20);
पूर्ण

व्योम lx_set_mode(काष्ठा fb_info *info)
अणु
	काष्ठा lxfb_par *par = info->par;
	u64 msrval;

	अचिन्हित पूर्णांक max, dv, val, size;

	अचिन्हित पूर्णांक gcfg, dcfg;
	पूर्णांक hactive, hblankstart, hsyncstart, hsyncend, hblankend, htotal;
	पूर्णांक vactive, vblankstart, vsyncstart, vsyncend, vblankend, vtotal;

	/* Unlock the DC रेजिस्टरs */
	ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);

	lx_graphics_disable(info);

	lx_set_घड़ी(info);

	/* Set output mode */

	rdmsrl(MSR_LX_GLD_MSR_CONFIG, msrval);
	msrval &= ~MSR_LX_GLD_MSR_CONFIG_FMT;

	अगर (par->output & OUTPUT_PANEL) अणु
		msrval |= MSR_LX_GLD_MSR_CONFIG_FMT_FP;

		अगर (par->output & OUTPUT_CRT)
			msrval |= MSR_LX_GLD_MSR_CONFIG_FPC;
		अन्यथा
			msrval &= ~MSR_LX_GLD_MSR_CONFIG_FPC;
	पूर्ण अन्यथा
		msrval |= MSR_LX_GLD_MSR_CONFIG_FMT_CRT;

	wrmsrl(MSR_LX_GLD_MSR_CONFIG, msrval);

	/* Clear the various buffers */
	/* FIXME:  Adjust क्रम panning here */

	ग_लिखो_dc(par, DC_FB_ST_OFFSET, 0);
	ग_लिखो_dc(par, DC_CB_ST_OFFSET, 0);
	ग_लिखो_dc(par, DC_CURS_ST_OFFSET, 0);

	/* FIXME: Add support क्रम पूर्णांकerlacing */
	/* FIXME: Add support क्रम scaling */

	val = पढ़ो_dc(par, DC_GENLK_CTL);
	val &= ~(DC_GENLK_CTL_ALPHA_FLICK_EN | DC_GENLK_CTL_FLICK_EN |
			DC_GENLK_CTL_FLICK_SEL_MASK);

	/* Default scaling params */

	ग_लिखो_dc(par, DC_GFX_SCALE, (0x4000 << 16) | 0x4000);
	ग_लिखो_dc(par, DC_IRQ_FILT_CTL, 0);
	ग_लिखो_dc(par, DC_GENLK_CTL, val);

	/* FIXME:  Support compression */

	अगर (info->fix.line_length > 4096)
		dv = DC_DV_CTL_DV_LINE_SIZE_8K;
	अन्यथा अगर (info->fix.line_length > 2048)
		dv = DC_DV_CTL_DV_LINE_SIZE_4K;
	अन्यथा अगर (info->fix.line_length > 1024)
		dv = DC_DV_CTL_DV_LINE_SIZE_2K;
	अन्यथा
		dv = DC_DV_CTL_DV_LINE_SIZE_1K;

	max = info->fix.line_length * info->var.yres;
	max = (max + 0x3FF) & 0xFFFFFC00;

	ग_लिखो_dc(par, DC_DV_TOP, max | DC_DV_TOP_DV_TOP_EN);

	val = पढ़ो_dc(par, DC_DV_CTL) & ~DC_DV_CTL_DV_LINE_SIZE;
	ग_लिखो_dc(par, DC_DV_CTL, val | dv);

	size = info->var.xres * (info->var.bits_per_pixel >> 3);

	ग_लिखो_dc(par, DC_GFX_PITCH, info->fix.line_length >> 3);
	ग_लिखो_dc(par, DC_LINE_SIZE, (size + 7) >> 3);

	/* Set शेष watermark values */

	rdmsrl(MSR_LX_SPARE_MSR, msrval);

	msrval &= ~(MSR_LX_SPARE_MSR_DIS_CFIFO_HGO
			| MSR_LX_SPARE_MSR_VFIFO_ARB_SEL
			| MSR_LX_SPARE_MSR_LOAD_WM_LPEN_M
			| MSR_LX_SPARE_MSR_WM_LPEN_OVRD);
	msrval |= MSR_LX_SPARE_MSR_DIS_VIFO_WM |
			MSR_LX_SPARE_MSR_DIS_INIT_V_PRI;
	wrmsrl(MSR_LX_SPARE_MSR, msrval);

	gcfg = DC_GENERAL_CFG_DFLE;   /* Display fअगरo enable */
	gcfg |= (0x6 << DC_GENERAL_CFG_DFHPSL_SHIFT) | /* शेष priority */
			(0xb << DC_GENERAL_CFG_DFHPEL_SHIFT);
	gcfg |= DC_GENERAL_CFG_FDTY;  /* Set the frame dirty mode */

	dcfg  = DC_DISPLAY_CFG_VDEN;  /* Enable video data */
	dcfg |= DC_DISPLAY_CFG_GDEN;  /* Enable graphics */
	dcfg |= DC_DISPLAY_CFG_TGEN;  /* Turn on the timing generator */
	dcfg |= DC_DISPLAY_CFG_TRUP;  /* Update timings immediately */
	dcfg |= DC_DISPLAY_CFG_PALB;  /* Palette bypass in > 8 bpp modes */
	dcfg |= DC_DISPLAY_CFG_VISL;
	dcfg |= DC_DISPLAY_CFG_DCEN;  /* Always center the display */

	/* Set the current BPP mode */

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		dcfg |= DC_DISPLAY_CFG_DISP_MODE_8BPP;
		अवरोध;

	हाल 16:
		dcfg |= DC_DISPLAY_CFG_DISP_MODE_16BPP;
		अवरोध;

	हाल 32:
	हाल 24:
		dcfg |= DC_DISPLAY_CFG_DISP_MODE_24BPP;
		अवरोध;
	पूर्ण

	/* Now - set up the timings */

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

	ग_लिखो_dc(par, DC_H_ACTIVE_TIMING, (hactive - 1) | ((htotal - 1) << 16));
	ग_लिखो_dc(par, DC_H_BLANK_TIMING,
			(hblankstart - 1) | ((hblankend - 1) << 16));
	ग_लिखो_dc(par, DC_H_SYNC_TIMING,
			(hsyncstart - 1) | ((hsyncend - 1) << 16));

	ग_लिखो_dc(par, DC_V_ACTIVE_TIMING, (vactive - 1) | ((vtotal - 1) << 16));
	ग_लिखो_dc(par, DC_V_BLANK_TIMING,
			(vblankstart - 1) | ((vblankend - 1) << 16));
	ग_लिखो_dc(par, DC_V_SYNC_TIMING,
			(vsyncstart - 1) | ((vsyncend - 1) << 16));

	ग_लिखो_dc(par, DC_FB_ACTIVE,
			(info->var.xres - 1) << 16 | (info->var.yres - 1));

	/* And re-enable the graphics output */
	lx_graphics_enable(info);

	/* Write the two मुख्य configuration रेजिस्टरs */
	ग_लिखो_dc(par, DC_DISPLAY_CFG, dcfg);
	ग_लिखो_dc(par, DC_ARB_CFG, 0);
	ग_लिखो_dc(par, DC_GENERAL_CFG, gcfg);

	/* Lock the DC रेजिस्टरs */
	ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_LOCK);
पूर्ण

व्योम lx_set_palette_reg(काष्ठा fb_info *info, अचिन्हित regno,
			अचिन्हित red, अचिन्हित green, अचिन्हित blue)
अणु
	काष्ठा lxfb_par *par = info->par;
	पूर्णांक val;

	/* Hardware palette is in RGB 8-8-8 क्रमmat. */

	val  = (red   << 8) & 0xff0000;
	val |= (green)      & 0x00ff00;
	val |= (blue  >> 8) & 0x0000ff;

	ग_लिखो_dc(par, DC_PAL_ADDRESS, regno);
	ग_लिखो_dc(par, DC_PAL_DATA, val);
पूर्ण

पूर्णांक lx_blank_display(काष्ठा fb_info *info, पूर्णांक blank_mode)
अणु
	काष्ठा lxfb_par *par = info->par;
	u32 dcfg, misc, fp_pm;
	पूर्णांक blank, hsync, vsync;

	/* CRT घातer saving modes. */
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

	dcfg = पढ़ो_vp(par, VP_DCFG);
	dcfg &= ~(VP_DCFG_DAC_BL_EN | VP_DCFG_HSYNC_EN | VP_DCFG_VSYNC_EN |
			VP_DCFG_CRT_EN);
	अगर (!blank)
		dcfg |= VP_DCFG_DAC_BL_EN | VP_DCFG_CRT_EN;
	अगर (hsync)
		dcfg |= VP_DCFG_HSYNC_EN;
	अगर (vsync)
		dcfg |= VP_DCFG_VSYNC_EN;

	ग_लिखो_vp(par, VP_DCFG, dcfg);

	misc = पढ़ो_vp(par, VP_MISC);

	अगर (vsync && hsync)
		misc &= ~VP_MISC_DACPWRDN;
	अन्यथा
		misc |= VP_MISC_DACPWRDN;

	ग_लिखो_vp(par, VP_MISC, misc);

	/* Power on/off flat panel */

	अगर (par->output & OUTPUT_PANEL) अणु
		fp_pm = पढ़ो_fp(par, FP_PM);
		अगर (blank_mode == FB_BLANK_POWERDOWN)
			fp_pm &= ~FP_PM_P;
		अन्यथा
			fp_pm |= FP_PM_P;
		ग_लिखो_fp(par, FP_PM, fp_pm);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lx_save_regs(काष्ठा lxfb_par *par)
अणु
	uपूर्णांक32_t filt;
	पूर्णांक i;

	/* रुको क्रम the BLT engine to stop being busy */
	करो अणु
		i = पढ़ो_gp(par, GP_BLT_STATUS);
	पूर्ण जबतक ((i & GP_BLT_STATUS_PB) || !(i & GP_BLT_STATUS_CE));

	/* save MSRs */
	rdmsrl(MSR_LX_MSR_PADSEL, par->msr.padsel);
	rdmsrl(MSR_GLCP_DOTPLL, par->msr.करोtpll);
	rdmsrl(MSR_LX_GLD_MSR_CONFIG, par->msr.dfglcfg);
	rdmsrl(MSR_LX_SPARE_MSR, par->msr.dcspare);

	ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);

	/* save रेजिस्टरs */
	स_नकल(par->gp, par->gp_regs, माप(par->gp));
	स_नकल(par->dc, par->dc_regs, माप(par->dc));
	स_नकल(par->vp, par->vp_regs, माप(par->vp));
	स_नकल(par->fp, par->vp_regs + VP_FP_START, माप(par->fp));

	/* save the display controller palette */
	ग_लिखो_dc(par, DC_PAL_ADDRESS, 0);
	क्रम (i = 0; i < ARRAY_SIZE(par->dc_pal); i++)
		par->dc_pal[i] = पढ़ो_dc(par, DC_PAL_DATA);

	/* save the video processor palette */
	ग_लिखो_vp(par, VP_PAR, 0);
	क्रम (i = 0; i < ARRAY_SIZE(par->vp_pal); i++)
		par->vp_pal[i] = पढ़ो_vp(par, VP_PDR);

	/* save the horizontal filter coefficients */
	filt = par->dc[DC_IRQ_FILT_CTL] | DC_IRQ_FILT_CTL_H_FILT_SEL;
	क्रम (i = 0; i < ARRAY_SIZE(par->hcoeff); i += 2) अणु
		ग_लिखो_dc(par, DC_IRQ_FILT_CTL, (filt & 0xffffff00) | i);
		par->hcoeff[i] = पढ़ो_dc(par, DC_FILT_COEFF1);
		par->hcoeff[i + 1] = पढ़ो_dc(par, DC_FILT_COEFF2);
	पूर्ण

	/* save the vertical filter coefficients */
	filt &= ~DC_IRQ_FILT_CTL_H_FILT_SEL;
	क्रम (i = 0; i < ARRAY_SIZE(par->vcoeff); i++) अणु
		ग_लिखो_dc(par, DC_IRQ_FILT_CTL, (filt & 0xffffff00) | i);
		par->vcoeff[i] = पढ़ो_dc(par, DC_FILT_COEFF1);
	पूर्ण

	/* save video coeff ram */
	स_नकल(par->vp_coeff, par->vp_regs + VP_VCR, माप(par->vp_coeff));
पूर्ण

अटल व्योम lx_restore_gfx_proc(काष्ठा lxfb_par *par)
अणु
	पूर्णांक i;

	/* a bunch of रेजिस्टरs require GP_RASTER_MODE to be set first */
	ग_लिखो_gp(par, GP_RASTER_MODE, par->gp[GP_RASTER_MODE]);

	क्रम (i = 0; i < ARRAY_SIZE(par->gp); i++) अणु
		चयन (i) अणु
		हाल GP_RASTER_MODE:
		हाल GP_VECTOR_MODE:
		हाल GP_BLT_MODE:
		हाल GP_BLT_STATUS:
		हाल GP_HST_SRC:
			/* FIXME: restore LUT data */
		हाल GP_LUT_INDEX:
		हाल GP_LUT_DATA:
			/* करोn't restore these रेजिस्टरs */
			अवरोध;

		शेष:
			ग_लिखो_gp(par, i, par->gp[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम lx_restore_display_ctlr(काष्ठा lxfb_par *par)
अणु
	uपूर्णांक32_t filt;
	पूर्णांक i;

	wrmsrl(MSR_LX_SPARE_MSR, par->msr.dcspare);

	क्रम (i = 0; i < ARRAY_SIZE(par->dc); i++) अणु
		चयन (i) अणु
		हाल DC_UNLOCK:
			/* unlock the DC; runs first */
			ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);
			अवरोध;

		हाल DC_GENERAL_CFG:
		हाल DC_DISPLAY_CFG:
			/* disable all जबतक restoring */
			ग_लिखो_dc(par, i, 0);
			अवरोध;

		हाल DC_DV_CTL:
			/* set all ram to dirty */
			ग_लिखो_dc(par, i, par->dc[i] | DC_DV_CTL_CLEAR_DV_RAM);
			अवरोध;

		हाल DC_RSVD_1:
		हाल DC_RSVD_2:
		हाल DC_RSVD_3:
		हाल DC_LINE_CNT:
		हाल DC_PAL_ADDRESS:
		हाल DC_PAL_DATA:
		हाल DC_DFIFO_DIAG:
		हाल DC_CFIFO_DIAG:
		हाल DC_FILT_COEFF1:
		हाल DC_FILT_COEFF2:
		हाल DC_RSVD_4:
		हाल DC_RSVD_5:
			/* करोn't restore these रेजिस्टरs */
			अवरोध;

		शेष:
			ग_लिखो_dc(par, i, par->dc[i]);
		पूर्ण
	पूर्ण

	/* restore the palette */
	ग_लिखो_dc(par, DC_PAL_ADDRESS, 0);
	क्रम (i = 0; i < ARRAY_SIZE(par->dc_pal); i++)
		ग_लिखो_dc(par, DC_PAL_DATA, par->dc_pal[i]);

	/* restore the horizontal filter coefficients */
	filt = par->dc[DC_IRQ_FILT_CTL] | DC_IRQ_FILT_CTL_H_FILT_SEL;
	क्रम (i = 0; i < ARRAY_SIZE(par->hcoeff); i += 2) अणु
		ग_लिखो_dc(par, DC_IRQ_FILT_CTL, (filt & 0xffffff00) | i);
		ग_लिखो_dc(par, DC_FILT_COEFF1, par->hcoeff[i]);
		ग_लिखो_dc(par, DC_FILT_COEFF2, par->hcoeff[i + 1]);
	पूर्ण

	/* restore the vertical filter coefficients */
	filt &= ~DC_IRQ_FILT_CTL_H_FILT_SEL;
	क्रम (i = 0; i < ARRAY_SIZE(par->vcoeff); i++) अणु
		ग_लिखो_dc(par, DC_IRQ_FILT_CTL, (filt & 0xffffff00) | i);
		ग_लिखो_dc(par, DC_FILT_COEFF1, par->vcoeff[i]);
	पूर्ण
पूर्ण

अटल व्योम lx_restore_video_proc(काष्ठा lxfb_par *par)
अणु
	पूर्णांक i;

	wrmsrl(MSR_LX_GLD_MSR_CONFIG, par->msr.dfglcfg);
	wrmsrl(MSR_LX_MSR_PADSEL, par->msr.padsel);

	क्रम (i = 0; i < ARRAY_SIZE(par->vp); i++) अणु
		चयन (i) अणु
		हाल VP_VCFG:
		हाल VP_DCFG:
		हाल VP_PAR:
		हाल VP_PDR:
		हाल VP_CCS:
		हाल VP_RSVD_0:
		/* हाल VP_VDC: */ /* why should this not be restored? */
		हाल VP_RSVD_1:
		हाल VP_CRC32:
			/* करोn't restore these रेजिस्टरs */
			अवरोध;

		शेष:
			ग_लिखो_vp(par, i, par->vp[i]);
		पूर्ण
	पूर्ण

	/* restore video processor palette */
	ग_लिखो_vp(par, VP_PAR, 0);
	क्रम (i = 0; i < ARRAY_SIZE(par->vp_pal); i++)
		ग_लिखो_vp(par, VP_PDR, par->vp_pal[i]);

	/* restore video coeff ram */
	स_नकल(par->vp_regs + VP_VCR, par->vp_coeff, माप(par->vp_coeff));
पूर्ण

अटल व्योम lx_restore_regs(काष्ठा lxfb_par *par)
अणु
	पूर्णांक i;

	lx_set_करोtpll((u32) (par->msr.करोtpll >> 32));
	lx_restore_gfx_proc(par);
	lx_restore_display_ctlr(par);
	lx_restore_video_proc(par);

	/* Flat Panel */
	क्रम (i = 0; i < ARRAY_SIZE(par->fp); i++) अणु
		चयन (i) अणु
		हाल FP_PM:
		हाल FP_RSVD_0:
		हाल FP_RSVD_1:
		हाल FP_RSVD_2:
		हाल FP_RSVD_3:
		हाल FP_RSVD_4:
			/* करोn't restore these रेजिस्टरs */
			अवरोध;

		शेष:
			ग_लिखो_fp(par, i, par->fp[i]);
		पूर्ण
	पूर्ण

	/* control the panel */
	अगर (par->fp[FP_PM] & FP_PM_P) अणु
		/* घातer on the panel अगर not alपढ़ोy घातerअणुed,ingपूर्ण on */
		अगर (!(पढ़ो_fp(par, FP_PM) &
				(FP_PM_PANEL_ON|FP_PM_PANEL_PWR_UP)))
			ग_लिखो_fp(par, FP_PM, par->fp[FP_PM]);
	पूर्ण अन्यथा अणु
		/* घातer करोwn the panel अगर not alपढ़ोy घातerअणुed,ingपूर्ण करोwn */
		अगर (!(पढ़ो_fp(par, FP_PM) &
				(FP_PM_PANEL_OFF|FP_PM_PANEL_PWR_DOWN)))
			ग_लिखो_fp(par, FP_PM, par->fp[FP_PM]);
	पूर्ण

	/* turn everything on */
	ग_लिखो_vp(par, VP_VCFG, par->vp[VP_VCFG]);
	ग_लिखो_vp(par, VP_DCFG, par->vp[VP_DCFG]);
	ग_लिखो_dc(par, DC_DISPLAY_CFG, par->dc[DC_DISPLAY_CFG]);
	/* करो this last; it will enable the FIFO load */
	ग_लिखो_dc(par, DC_GENERAL_CFG, par->dc[DC_GENERAL_CFG]);

	/* lock the करोor behind us */
	ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_LOCK);
पूर्ण

पूर्णांक lx_घातerकरोwn(काष्ठा fb_info *info)
अणु
	काष्ठा lxfb_par *par = info->par;

	अगर (par->घातered_करोwn)
		वापस 0;

	lx_save_regs(par);
	lx_graphics_disable(info);

	par->घातered_करोwn = 1;
	वापस 0;
पूर्ण

पूर्णांक lx_घातerup(काष्ठा fb_info *info)
अणु
	काष्ठा lxfb_par *par = info->par;

	अगर (!par->घातered_करोwn)
		वापस 0;

	lx_restore_regs(par);

	par->घातered_करोwn = 0;
	वापस 0;
पूर्ण
