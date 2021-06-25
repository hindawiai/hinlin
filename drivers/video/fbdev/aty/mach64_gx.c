<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 *  ATI Mach64 GX Support
 */

#समावेश <linux/delay.h>
#समावेश <linux/fb.h>

#समावेश <यंत्र/पन.स>

#समावेश <video/mach64.h>
#समावेश "atyfb.h"

/* Definitions क्रम the ICS 2595 == ATI 18818_1 Clockchip */

#घोषणा REF_FREQ_2595       1432	/*  14.33 MHz  (exact   14.31818) */
#घोषणा REF_DIV_2595          46	/* really 43 on ICS 2595 !!!  */
				  /* ohne Prescaler */
#घोषणा MAX_FREQ_2595      15938	/* 159.38 MHz  (really 170.486) */
#घोषणा MIN_FREQ_2595       8000	/*  80.00 MHz  (        85.565) */
				  /* mit Prescaler 2, 4, 8 */
#घोषणा ABS_MIN_FREQ_2595   1000	/*  10.00 MHz  (really  10.697) */
#घोषणा N_ADJ_2595           257

#घोषणा STOP_BITS_2595     0x1800


#घोषणा MIN_N_408		2

#घोषणा MIN_N_1703		6

#घोषणा MIN_M		2
#घोषणा MAX_M		30
#घोषणा MIN_N		35
#घोषणा MAX_N		255-8


    /*
     *  Support Functions
     */

अटल व्योम aty_dac_waste4(स्थिर काष्ठा atyfb_par *par)
अणु
	(व्योम) aty_ld_8(DAC_REGS, par);

	(व्योम) aty_ld_8(DAC_REGS + 2, par);
	(व्योम) aty_ld_8(DAC_REGS + 2, par);
	(व्योम) aty_ld_8(DAC_REGS + 2, par);
	(व्योम) aty_ld_8(DAC_REGS + 2, par);
पूर्ण

अटल व्योम aty_StrobeClock(स्थिर काष्ठा atyfb_par *par)
अणु
	u8 पंचांगp;

	udelay(26);

	पंचांगp = aty_ld_8(CLOCK_CNTL, par);
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset, पंचांगp | CLOCK_STROBE, par);
	वापस;
पूर्ण


    /*
     *  IBM RGB514 DAC and Clock Chip
     */

अटल व्योम aty_st_514(पूर्णांक offset, u8 val, स्थिर काष्ठा atyfb_par *par)
अणु
	aty_st_8(DAC_CNTL, 1, par);
	/* right addr byte */
	aty_st_8(DAC_W_INDEX, offset & 0xff, par);
	/* left addr byte */
	aty_st_8(DAC_DATA, (offset >> 8) & 0xff, par);
	aty_st_8(DAC_MASK, val, par);
	aty_st_8(DAC_CNTL, 0, par);
पूर्ण

अटल पूर्णांक aty_set_dac_514(स्थिर काष्ठा fb_info *info,
			   स्थिर जोड़ aty_pll *pll, u32 bpp, u32 accel)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	अटल काष्ठा अणु
		u8 pixel_dly;
		u8 misc2_cntl;
		u8 pixel_rep;
		u8 pixel_cntl_index;
		u8 pixel_cntl_v1;
	पूर्ण tab[3] = अणु
		अणु
		0, 0x41, 0x03, 0x71, 0x45पूर्ण,	/* 8 bpp */
		अणु
		0, 0x45, 0x04, 0x0c, 0x01पूर्ण,	/* 555 */
		अणु
		0, 0x45, 0x06, 0x0e, 0x00पूर्ण,	/* XRGB */
	पूर्ण;
	पूर्णांक i;

	चयन (bpp) अणु
	हाल 8:
	शेष:
		i = 0;
		अवरोध;
	हाल 16:
		i = 1;
		अवरोध;
	हाल 32:
		i = 2;
		अवरोध;
	पूर्ण
	aty_st_514(0x90, 0x00, par);	/* VRAM Mask Low */
	aty_st_514(0x04, tab[i].pixel_dly, par);	/* Horizontal Sync Control */
	aty_st_514(0x05, 0x00, par);	/* Power Management */
	aty_st_514(0x02, 0x01, par);	/* Misc Clock Control */
	aty_st_514(0x71, tab[i].misc2_cntl, par);	/* Misc Control 2 */
	aty_st_514(0x0a, tab[i].pixel_rep, par);	/* Pixel Format */
	aty_st_514(tab[i].pixel_cntl_index, tab[i].pixel_cntl_v1, par);
	/* Misc Control 2 / 16 BPP Control / 32 BPP Control */
	वापस 0;
पूर्ण

अटल पूर्णांक aty_var_to_pll_514(स्थिर काष्ठा fb_info *info, u32 vclk_per,
			      u32 bpp, जोड़ aty_pll *pll)
अणु
	/*
	 *  FIXME: use real calculations instead of using fixed values from the old
	 *         driver
	 */
	अटल काष्ठा अणु
		u32 limit;	/* pixlock rounding limit (arbitrary) */
		u8 m;		/* (df<<6) | vco_भाग_count */
		u8 n;		/* ref_भाग_count */
	पूर्ण RGB514_घड़ीs[7] = अणु
		अणु
		8000, (3 << 6) | 20, 9पूर्ण,	/*  7395 ps / 135.2273 MHz */
		अणु
		10000, (1 << 6) | 19, 3पूर्ण,	/*  9977 ps / 100.2273 MHz */
		अणु
		13000, (1 << 6) | 2, 3पूर्ण,	/* 12509 ps /  79.9432 MHz */
		अणु
		14000, (2 << 6) | 8, 7पूर्ण,	/* 13394 ps /  74.6591 MHz */
		अणु
		16000, (1 << 6) | 44, 6पूर्ण,	/* 15378 ps /  65.0284 MHz */
		अणु
		25000, (1 << 6) | 15, 5पूर्ण,	/* 17460 ps /  57.2727 MHz */
		अणु
		50000, (0 << 6) | 53, 7पूर्ण,	/* 33145 ps /  30.1705 MHz */
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(RGB514_घड़ीs); i++)
		अगर (vclk_per <= RGB514_घड़ीs[i].limit) अणु
			pll->ibm514.m = RGB514_घड़ीs[i].m;
			pll->ibm514.n = RGB514_घड़ीs[i].n;
			वापस 0;
		पूर्ण
	वापस -EINVAL;
पूर्ण

अटल u32 aty_pll_514_to_var(स्थिर काष्ठा fb_info *info,
			      स्थिर जोड़ aty_pll *pll)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u8 df, vco_भाग_count, ref_भाग_count;

	df = pll->ibm514.m >> 6;
	vco_भाग_count = pll->ibm514.m & 0x3f;
	ref_भाग_count = pll->ibm514.n;

	वापस ((par->ref_clk_per * ref_भाग_count) << (3 - df))/
	    		(vco_भाग_count + 65);
पूर्ण

अटल व्योम aty_set_pll_514(स्थिर काष्ठा fb_info *info,
			    स्थिर जोड़ aty_pll *pll)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;

	aty_st_514(0x06, 0x02, par);	/* DAC Operation */
	aty_st_514(0x10, 0x01, par);	/* PLL Control 1 */
	aty_st_514(0x70, 0x01, par);	/* Misc Control 1 */
	aty_st_514(0x8f, 0x1f, par);	/* PLL Ref. Divider Input */
	aty_st_514(0x03, 0x00, par);	/* Sync Control */
	aty_st_514(0x05, 0x00, par);	/* Power Management */
	aty_st_514(0x20, pll->ibm514.m, par);	/* F0 / M0 */
	aty_st_514(0x21, pll->ibm514.n, par);	/* F1 / N0 */
पूर्ण

स्थिर काष्ठा aty_dac_ops aty_dac_ibm514 = अणु
	.set_dac	= aty_set_dac_514,
पूर्ण;

स्थिर काष्ठा aty_pll_ops aty_pll_ibm514 = अणु
	.var_to_pll	= aty_var_to_pll_514,
	.pll_to_var	= aty_pll_514_to_var,
	.set_pll	= aty_set_pll_514,
पूर्ण;


    /*
     *  ATI 68860-B DAC
     */

अटल पूर्णांक aty_set_dac_ATI68860_B(स्थिर काष्ठा fb_info *info,
				  स्थिर जोड़ aty_pll *pll, u32 bpp,
				  u32 accel)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 gModeReg, devSetupRegA, temp, mask;

	gModeReg = 0;
	devSetupRegA = 0;

	चयन (bpp) अणु
	हाल 8:
		gModeReg = 0x83;
		devSetupRegA =
		    0x60 | 0x00 /*(info->mach64DAC8Bit ? 0x00 : 0x01) */ ;
		अवरोध;
	हाल 15:
		gModeReg = 0xA0;
		devSetupRegA = 0x60;
		अवरोध;
	हाल 16:
		gModeReg = 0xA1;
		devSetupRegA = 0x60;
		अवरोध;
	हाल 24:
		gModeReg = 0xC0;
		devSetupRegA = 0x60;
		अवरोध;
	हाल 32:
		gModeReg = 0xE3;
		devSetupRegA = 0x60;
		अवरोध;
	पूर्ण

	अगर (!accel) अणु
		gModeReg = 0x80;
		devSetupRegA = 0x61;
	पूर्ण

	temp = aty_ld_8(DAC_CNTL, par);
	aty_st_8(DAC_CNTL, (temp & ~DAC_EXT_SEL_RS2) | DAC_EXT_SEL_RS3,
		 par);

	aty_st_8(DAC_REGS + 2, 0x1D, par);
	aty_st_8(DAC_REGS + 3, gModeReg, par);
	aty_st_8(DAC_REGS, 0x02, par);

	temp = aty_ld_8(DAC_CNTL, par);
	aty_st_8(DAC_CNTL, temp | DAC_EXT_SEL_RS2 | DAC_EXT_SEL_RS3, par);

	अगर (info->fix.smem_len < ONE_MB)
		mask = 0x04;
	अन्यथा अगर (info->fix.smem_len == ONE_MB)
		mask = 0x08;
	अन्यथा
		mask = 0x0C;

	/* The following assumes that the BIOS has correctly set R7 of the
	 * Device Setup Register A at boot समय.
	 */
#घोषणा A860_DELAY_L	0x80

	temp = aty_ld_8(DAC_REGS, par);
	aty_st_8(DAC_REGS, (devSetupRegA | mask) | (temp & A860_DELAY_L),
		 par);
	temp = aty_ld_8(DAC_CNTL, par);
	aty_st_8(DAC_CNTL, (temp & ~(DAC_EXT_SEL_RS2 | DAC_EXT_SEL_RS3)),
		 par);

	aty_st_le32(BUS_CNTL, 0x890e20f1, par);
	aty_st_le32(DAC_CNTL, 0x47052100, par);
	वापस 0;
पूर्ण

स्थिर काष्ठा aty_dac_ops aty_dac_ati68860b = अणु
	.set_dac	= aty_set_dac_ATI68860_B,
पूर्ण;


    /*
     *  AT&T 21C498 DAC
     */

अटल पूर्णांक aty_set_dac_ATT21C498(स्थिर काष्ठा fb_info *info,
				 स्थिर जोड़ aty_pll *pll, u32 bpp,
				 u32 accel)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 करोtClock;
	पूर्णांक muxmode = 0;
	पूर्णांक DACMask = 0;

	करोtClock = 100000000 / pll->ics2595.period_in_ps;

	चयन (bpp) अणु
	हाल 8:
		अगर (करोtClock > 8000) अणु
			DACMask = 0x24;
			muxmode = 1;
		पूर्ण अन्यथा
			DACMask = 0x04;
		अवरोध;
	हाल 15:
		DACMask = 0x16;
		अवरोध;
	हाल 16:
		DACMask = 0x36;
		अवरोध;
	हाल 24:
		DACMask = 0xE6;
		अवरोध;
	हाल 32:
		DACMask = 0xE6;
		अवरोध;
	पूर्ण

	अगर (1 /* info->mach64DAC8Bit */ )
		DACMask |= 0x02;

	aty_dac_waste4(par);
	aty_st_8(DAC_REGS + 2, DACMask, par);

	aty_st_le32(BUS_CNTL, 0x890e20f1, par);
	aty_st_le32(DAC_CNTL, 0x00072000, par);
	वापस muxmode;
पूर्ण

स्थिर काष्ठा aty_dac_ops aty_dac_att21c498 = अणु
	.set_dac	= aty_set_dac_ATT21C498,
पूर्ण;


    /*
     *  ATI 18818 / ICS 2595 Clock Chip
     */

अटल पूर्णांक aty_var_to_pll_18818(स्थिर काष्ठा fb_info *info, u32 vclk_per,
				u32 bpp, जोड़ aty_pll *pll)
अणु
	u32 MHz100;		/* in 0.01 MHz */
	u32 program_bits;
	u32 post_भागider;

	/* Calculate the programming word */
	MHz100 = 100000000 / vclk_per;

	program_bits = -1;
	post_भागider = 1;

	अगर (MHz100 > MAX_FREQ_2595) अणु
		MHz100 = MAX_FREQ_2595;
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (MHz100 < ABS_MIN_FREQ_2595) अणु
		program_bits = 0;	/* MHz100 = 257 */
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		जबतक (MHz100 < MIN_FREQ_2595) अणु
			MHz100 *= 2;
			post_भागider *= 2;
		पूर्ण
	पूर्ण
	MHz100 *= 1000;
	MHz100 = (REF_DIV_2595 * MHz100) / REF_FREQ_2595;
 
	MHz100 += 500;		/* + 0.5 round */
	MHz100 /= 1000;

	अगर (program_bits == -1) अणु
		program_bits = MHz100 - N_ADJ_2595;
		चयन (post_भागider) अणु
		हाल 1:
			program_bits |= 0x0600;
			अवरोध;
		हाल 2:
			program_bits |= 0x0400;
			अवरोध;
		हाल 4:
			program_bits |= 0x0200;
			अवरोध;
		हाल 8:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	program_bits |= STOP_BITS_2595;

	pll->ics2595.program_bits = program_bits;
	pll->ics2595.locationAddr = 0;
	pll->ics2595.post_भागider = post_भागider;
	pll->ics2595.period_in_ps = vclk_per;

	वापस 0;
पूर्ण

अटल u32 aty_pll_18818_to_var(स्थिर काष्ठा fb_info *info,
				स्थिर जोड़ aty_pll *pll)
अणु
	वापस (pll->ics2595.period_in_ps);	/* शेष क्रम now */
पूर्ण

अटल व्योम aty_ICS2595_put1bit(u8 data, स्थिर काष्ठा atyfb_par *par)
अणु
	u8 पंचांगp;

	data &= 0x01;
	पंचांगp = aty_ld_8(CLOCK_CNTL, par);
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset,
		 (पंचांगp & ~0x04) | (data << 2), par);

	पंचांगp = aty_ld_8(CLOCK_CNTL, par);
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset, (पंचांगp & ~0x08) | (0 << 3),
		 par);

	aty_StrobeClock(par);

	पंचांगp = aty_ld_8(CLOCK_CNTL, par);
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset, (पंचांगp & ~0x08) | (1 << 3),
		 par);

	aty_StrobeClock(par);
	वापस;
पूर्ण

अटल व्योम aty_set_pll18818(स्थिर काष्ठा fb_info *info,
			     स्थिर जोड़ aty_pll *pll)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 program_bits;
	u32 locationAddr;

	u32 i;

	u8 old_घड़ी_cntl;
	u8 old_crtc_ext_disp;

	old_घड़ी_cntl = aty_ld_8(CLOCK_CNTL, par);
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset, 0, par);

	old_crtc_ext_disp = aty_ld_8(CRTC_GEN_CNTL + 3, par);
	aty_st_8(CRTC_GEN_CNTL + 3,
		 old_crtc_ext_disp | (CRTC_EXT_DISP_EN >> 24), par);

	mdelay(15);		/* delay क्रम 50 (15) ms */

	program_bits = pll->ics2595.program_bits;
	locationAddr = pll->ics2595.locationAddr;

	/* Program the घड़ी chip */
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset, 0, par);	/* Strobe = 0 */
	aty_StrobeClock(par);
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset, 1, par);	/* Strobe = 0 */
	aty_StrobeClock(par);

	aty_ICS2595_put1bit(1, par);	/* Send start bits */
	aty_ICS2595_put1bit(0, par);	/* Start bit */
	aty_ICS2595_put1bit(0, par);	/* Read / ~Write */

	क्रम (i = 0; i < 5; i++) अणु	/* Location 0..4 */
		aty_ICS2595_put1bit(locationAddr & 1, par);
		locationAddr >>= 1;
	पूर्ण

	क्रम (i = 0; i < 8 + 1 + 2 + 2; i++) अणु
		aty_ICS2595_put1bit(program_bits & 1, par);
		program_bits >>= 1;
	पूर्ण

	mdelay(1);		/* delay क्रम 1 ms */

	(व्योम) aty_ld_8(DAC_REGS, par);	/* Clear DAC Counter */
	aty_st_8(CRTC_GEN_CNTL + 3, old_crtc_ext_disp, par);
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset,
		 old_घड़ी_cntl | CLOCK_STROBE, par);

	mdelay(50);		/* delay क्रम 50 (15) ms */
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset,
		 ((pll->ics2595.locationAddr & 0x0F) | CLOCK_STROBE), par);
	वापस;
पूर्ण

स्थिर काष्ठा aty_pll_ops aty_pll_ati18818_1 = अणु
	.var_to_pll	= aty_var_to_pll_18818,
	.pll_to_var	= aty_pll_18818_to_var,
	.set_pll	= aty_set_pll18818,
पूर्ण;


    /*
     *  STG 1703 Clock Chip
     */

अटल पूर्णांक aty_var_to_pll_1703(स्थिर काष्ठा fb_info *info, u32 vclk_per,
			       u32 bpp, जोड़ aty_pll *pll)
अणु
	u32 mhz100;		/* in 0.01 MHz */
	u32 program_bits;
	/* u32 post_भागider; */
	u32 mach64MinFreq, mach64MaxFreq, mach64RefFreq;
	u32 temp, tempB;
	u16 reमुख्यder, preReमुख्यder;
	लघु भागider = 0, tempA;

	/* Calculate the programming word */
	mhz100 = 100000000 / vclk_per;
	mach64MinFreq = MIN_FREQ_2595;
	mach64MaxFreq = MAX_FREQ_2595;
	mach64RefFreq = REF_FREQ_2595;	/* 14.32 MHz */

	/* Calculate program word */
	अगर (mhz100 == 0)
		program_bits = 0xE0;
	अन्यथा अणु
		अगर (mhz100 < mach64MinFreq)
			mhz100 = mach64MinFreq;
		अगर (mhz100 > mach64MaxFreq)
			mhz100 = mach64MaxFreq;

		भागider = 0;
		जबतक (mhz100 < (mach64MinFreq << 3)) अणु
			mhz100 <<= 1;
			भागider += 0x20;
		पूर्ण

		temp = (अचिन्हित पूर्णांक) (mhz100);
		temp = (अचिन्हित पूर्णांक) (temp * (MIN_N_1703 + 2));
		temp -= (लघु) (mach64RefFreq << 1);

		tempA = MIN_N_1703;
		preReमुख्यder = 0xffff;

		करो अणु
			tempB = temp;
			reमुख्यder = tempB % mach64RefFreq;
			tempB = tempB / mach64RefFreq;

			अगर ((tempB & 0xffff) <= 127
			    && (reमुख्यder <= preReमुख्यder)) अणु
				preReमुख्यder = reमुख्यder;
				भागider &= ~0x1f;
				भागider |= tempA;
				भागider =
				    (भागider & 0x00ff) +
				    ((tempB & 0xff) << 8);
			पूर्ण

			temp += mhz100;
			tempA++;
		पूर्ण जबतक (tempA <= (MIN_N_1703 << 1));

		program_bits = भागider;
	पूर्ण

	pll->ics2595.program_bits = program_bits;
	pll->ics2595.locationAddr = 0;
	pll->ics2595.post_भागider = भागider;	/* fuer nix */
	pll->ics2595.period_in_ps = vclk_per;

	वापस 0;
पूर्ण

अटल u32 aty_pll_1703_to_var(स्थिर काष्ठा fb_info *info,
			       स्थिर जोड़ aty_pll *pll)
अणु
	वापस (pll->ics2595.period_in_ps);	/* शेष क्रम now */
पूर्ण

अटल व्योम aty_set_pll_1703(स्थिर काष्ठा fb_info *info,
			     स्थिर जोड़ aty_pll *pll)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 program_bits;
	u32 locationAddr;

	अक्षर old_crtc_ext_disp;

	old_crtc_ext_disp = aty_ld_8(CRTC_GEN_CNTL + 3, par);
	aty_st_8(CRTC_GEN_CNTL + 3,
		 old_crtc_ext_disp | (CRTC_EXT_DISP_EN >> 24), par);

	program_bits = pll->ics2595.program_bits;
	locationAddr = pll->ics2595.locationAddr;

	/* Program घड़ी */
	aty_dac_waste4(par);

	(व्योम) aty_ld_8(DAC_REGS + 2, par);
	aty_st_8(DAC_REGS + 2, (locationAddr << 1) + 0x20, par);
	aty_st_8(DAC_REGS + 2, 0, par);
	aty_st_8(DAC_REGS + 2, (program_bits & 0xFF00) >> 8, par);
	aty_st_8(DAC_REGS + 2, (program_bits & 0xFF), par);

	(व्योम) aty_ld_8(DAC_REGS, par);	/* Clear DAC Counter */
	aty_st_8(CRTC_GEN_CNTL + 3, old_crtc_ext_disp, par);
	वापस;
पूर्ण

स्थिर काष्ठा aty_pll_ops aty_pll_stg1703 = अणु
	.var_to_pll	= aty_var_to_pll_1703,
	.pll_to_var	= aty_pll_1703_to_var,
	.set_pll	= aty_set_pll_1703,
पूर्ण;


    /*
     *  Chrontel 8398 Clock Chip
     */

अटल पूर्णांक aty_var_to_pll_8398(स्थिर काष्ठा fb_info *info, u32 vclk_per,
			       u32 bpp, जोड़ aty_pll *pll)
अणु
	u32 tempA, tempB, fOut, दीर्घMHz100, dअगरf, preDअगरf;

	u32 mhz100;		/* in 0.01 MHz */
	u32 program_bits;
	/* u32 post_भागider; */
	u32 mach64MinFreq, mach64MaxFreq;
	u16 m, n, k = 0, save_m, save_n, twoToKth;

	/* Calculate the programming word */
	mhz100 = 100000000 / vclk_per;
	mach64MinFreq = MIN_FREQ_2595;
	mach64MaxFreq = MAX_FREQ_2595;

	save_m = 0;
	save_n = 0;

	/* Calculate program word */
	अगर (mhz100 == 0)
		program_bits = 0xE0;
	अन्यथा अणु
		अगर (mhz100 < mach64MinFreq)
			mhz100 = mach64MinFreq;
		अगर (mhz100 > mach64MaxFreq)
			mhz100 = mach64MaxFreq;

		दीर्घMHz100 = mhz100 * 256 / 100;	/* 8 bit scale this */

		जबतक (mhz100 < (mach64MinFreq << 3)) अणु
			mhz100 <<= 1;
			k++;
		पूर्ण

		twoToKth = 1 << k;
		dअगरf = 0;
		preDअगरf = 0xFFFFFFFF;

		क्रम (m = MIN_M; m <= MAX_M; m++) अणु
			क्रम (n = MIN_N; n <= MAX_N; n++) अणु
				tempA = 938356;		/* 14.31818 * 65536 */
				tempA *= (n + 8);	/* 43..256 */
				tempB = twoToKth * 256;
				tempB *= (m + 2);	/* 4..32 */
				fOut = tempA / tempB;	/* 8 bit scale */

				अगर (दीर्घMHz100 > fOut)
					dअगरf = दीर्घMHz100 - fOut;
				अन्यथा
					dअगरf = fOut - दीर्घMHz100;

				अगर (dअगरf < preDअगरf) अणु
					save_m = m;
					save_n = n;
					preDअगरf = dअगरf;
				पूर्ण
			पूर्ण
		पूर्ण

		program_bits = (k << 6) + (save_m) + (save_n << 8);
	पूर्ण

	pll->ics2595.program_bits = program_bits;
	pll->ics2595.locationAddr = 0;
	pll->ics2595.post_भागider = 0;
	pll->ics2595.period_in_ps = vclk_per;

	वापस 0;
पूर्ण

अटल u32 aty_pll_8398_to_var(स्थिर काष्ठा fb_info *info,
			       स्थिर जोड़ aty_pll *pll)
अणु
	वापस (pll->ics2595.period_in_ps);	/* शेष क्रम now */
पूर्ण

अटल व्योम aty_set_pll_8398(स्थिर काष्ठा fb_info *info,
			     स्थिर जोड़ aty_pll *pll)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 program_bits;
	u32 locationAddr;

	अक्षर old_crtc_ext_disp;
	अक्षर पंचांगp;

	old_crtc_ext_disp = aty_ld_8(CRTC_GEN_CNTL + 3, par);
	aty_st_8(CRTC_GEN_CNTL + 3,
		 old_crtc_ext_disp | (CRTC_EXT_DISP_EN >> 24), par);

	program_bits = pll->ics2595.program_bits;
	locationAddr = pll->ics2595.locationAddr;

	/* Program घड़ी */
	पंचांगp = aty_ld_8(DAC_CNTL, par);
	aty_st_8(DAC_CNTL, पंचांगp | DAC_EXT_SEL_RS2 | DAC_EXT_SEL_RS3, par);

	aty_st_8(DAC_REGS, locationAddr, par);
	aty_st_8(DAC_REGS + 1, (program_bits & 0xff00) >> 8, par);
	aty_st_8(DAC_REGS + 1, (program_bits & 0xff), par);

	पंचांगp = aty_ld_8(DAC_CNTL, par);
	aty_st_8(DAC_CNTL, (पंचांगp & ~DAC_EXT_SEL_RS2) | DAC_EXT_SEL_RS3,
		 par);

	(व्योम) aty_ld_8(DAC_REGS, par);	/* Clear DAC Counter */
	aty_st_8(CRTC_GEN_CNTL + 3, old_crtc_ext_disp, par);

	वापस;
पूर्ण

स्थिर काष्ठा aty_pll_ops aty_pll_ch8398 = अणु
	.var_to_pll	= aty_var_to_pll_8398,
	.pll_to_var	= aty_pll_8398_to_var,
	.set_pll	= aty_set_pll_8398,
पूर्ण;


    /*
     *  AT&T 20C408 Clock Chip
     */

अटल पूर्णांक aty_var_to_pll_408(स्थिर काष्ठा fb_info *info, u32 vclk_per,
			      u32 bpp, जोड़ aty_pll *pll)
अणु
	u32 mhz100;		/* in 0.01 MHz */
	u32 program_bits;
	/* u32 post_भागider; */
	u32 mach64MinFreq, mach64MaxFreq, mach64RefFreq;
	u32 temp, tempB;
	u16 reमुख्यder, preReमुख्यder;
	लघु भागider = 0, tempA;

	/* Calculate the programming word */
	mhz100 = 100000000 / vclk_per;
	mach64MinFreq = MIN_FREQ_2595;
	mach64MaxFreq = MAX_FREQ_2595;
	mach64RefFreq = REF_FREQ_2595;	/* 14.32 MHz */

	/* Calculate program word */
	अगर (mhz100 == 0)
		program_bits = 0xFF;
	अन्यथा अणु
		अगर (mhz100 < mach64MinFreq)
			mhz100 = mach64MinFreq;
		अगर (mhz100 > mach64MaxFreq)
			mhz100 = mach64MaxFreq;

		जबतक (mhz100 < (mach64MinFreq << 3)) अणु
			mhz100 <<= 1;
			भागider += 0x40;
		पूर्ण

		temp = (अचिन्हित पूर्णांक) mhz100;
		temp = (अचिन्हित पूर्णांक) (temp * (MIN_N_408 + 2));
		temp -= ((लघु) (mach64RefFreq << 1));

		tempA = MIN_N_408;
		preReमुख्यder = 0xFFFF;

		करो अणु
			tempB = temp;
			reमुख्यder = tempB % mach64RefFreq;
			tempB = tempB / mach64RefFreq;
			अगर (((tempB & 0xFFFF) <= 255)
			    && (reमुख्यder <= preReमुख्यder)) अणु
				preReमुख्यder = reमुख्यder;
				भागider &= ~0x3f;
				भागider |= tempA;
				भागider =
				    (भागider & 0x00FF) +
				    ((tempB & 0xFF) << 8);
			पूर्ण
			temp += mhz100;
			tempA++;
		पूर्ण जबतक (tempA <= 32);

		program_bits = भागider;
	पूर्ण

	pll->ics2595.program_bits = program_bits;
	pll->ics2595.locationAddr = 0;
	pll->ics2595.post_भागider = भागider;	/* fuer nix */
	pll->ics2595.period_in_ps = vclk_per;

	वापस 0;
पूर्ण

अटल u32 aty_pll_408_to_var(स्थिर काष्ठा fb_info *info,
			      स्थिर जोड़ aty_pll *pll)
अणु
	वापस (pll->ics2595.period_in_ps);	/* शेष क्रम now */
पूर्ण

अटल व्योम aty_set_pll_408(स्थिर काष्ठा fb_info *info,
			    स्थिर जोड़ aty_pll *pll)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 program_bits;
	u32 locationAddr;

	u8 पंचांगpA, पंचांगpB, पंचांगpC;
	अक्षर old_crtc_ext_disp;

	old_crtc_ext_disp = aty_ld_8(CRTC_GEN_CNTL + 3, par);
	aty_st_8(CRTC_GEN_CNTL + 3,
		 old_crtc_ext_disp | (CRTC_EXT_DISP_EN >> 24), par);

	program_bits = pll->ics2595.program_bits;
	locationAddr = pll->ics2595.locationAddr;

	/* Program घड़ी */
	aty_dac_waste4(par);
	पंचांगpB = aty_ld_8(DAC_REGS + 2, par) | 1;
	aty_dac_waste4(par);
	aty_st_8(DAC_REGS + 2, पंचांगpB, par);

	पंचांगpA = पंचांगpB;
	पंचांगpC = पंचांगpA;
	पंचांगpA |= 8;
	पंचांगpB = 1;

	aty_st_8(DAC_REGS, पंचांगpB, par);
	aty_st_8(DAC_REGS + 2, पंचांगpA, par);

	udelay(400);		/* delay क्रम 400 us */

	locationAddr = (locationAddr << 2) + 0x40;
	पंचांगpB = locationAddr;
	पंचांगpA = program_bits >> 8;

	aty_st_8(DAC_REGS, पंचांगpB, par);
	aty_st_8(DAC_REGS + 2, पंचांगpA, par);

	पंचांगpB = locationAddr + 1;
	पंचांगpA = (u8) program_bits;

	aty_st_8(DAC_REGS, पंचांगpB, par);
	aty_st_8(DAC_REGS + 2, पंचांगpA, par);

	पंचांगpB = locationAddr + 2;
	पंचांगpA = 0x77;

	aty_st_8(DAC_REGS, पंचांगpB, par);
	aty_st_8(DAC_REGS + 2, पंचांगpA, par);

	udelay(400);		/* delay क्रम 400 us */
	पंचांगpA = पंचांगpC & (~(1 | 8));
	पंचांगpB = 1;

	aty_st_8(DAC_REGS, पंचांगpB, par);
	aty_st_8(DAC_REGS + 2, पंचांगpA, par);

	(व्योम) aty_ld_8(DAC_REGS, par);	/* Clear DAC Counter */
	aty_st_8(CRTC_GEN_CNTL + 3, old_crtc_ext_disp, par);
	वापस;
पूर्ण

स्थिर काष्ठा aty_pll_ops aty_pll_att20c408 = अणु
	.var_to_pll	= aty_var_to_pll_408,
	.pll_to_var	= aty_pll_408_to_var,
	.set_pll	= aty_set_pll_408,
पूर्ण;


    /*
     *  Unsupported DAC and Clock Chip
     */

अटल पूर्णांक aty_set_dac_unsupported(स्थिर काष्ठा fb_info *info,
				   स्थिर जोड़ aty_pll *pll, u32 bpp,
				   u32 accel)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;

	aty_st_le32(BUS_CNTL, 0x890e20f1, par);
	aty_st_le32(DAC_CNTL, 0x47052100, par);
	/* new in 2.2.3p1 from Geert. ???????? */
	aty_st_le32(BUS_CNTL, 0x590e10ff, par);
	aty_st_le32(DAC_CNTL, 0x47012100, par);
	वापस 0;
पूर्ण

अटल पूर्णांक dummy(व्योम)
अणु
	वापस 0;
पूर्ण

स्थिर काष्ठा aty_dac_ops aty_dac_unsupported = अणु
	.set_dac	= aty_set_dac_unsupported,
पूर्ण;

स्थिर काष्ठा aty_pll_ops aty_pll_unsupported = अणु
	.var_to_pll	= (व्योम *) dummy,
	.pll_to_var	= (व्योम *) dummy,
	.set_pll	= (व्योम *) dummy,
पूर्ण;
