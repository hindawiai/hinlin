<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 *  ATI Mach64 CT/VT/GT/LT Support
 */

#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>
#समावेश <video/mach64.h>
#समावेश "atyfb.h"
#अगर_घोषित CONFIG_PPC
#समावेश <यंत्र/machdep.h>
#पूर्ण_अगर

#अघोषित DEBUG

अटल पूर्णांक aty_valid_pll_ct (स्थिर काष्ठा fb_info *info, u32 vclk_per, काष्ठा pll_ct *pll);
अटल पूर्णांक aty_dsp_gt       (स्थिर काष्ठा fb_info *info, u32 bpp, काष्ठा pll_ct *pll);
अटल पूर्णांक aty_var_to_pll_ct(स्थिर काष्ठा fb_info *info, u32 vclk_per, u32 bpp, जोड़ aty_pll *pll);
अटल u32 aty_pll_to_var_ct(स्थिर काष्ठा fb_info *info, स्थिर जोड़ aty_pll *pll);

u8 aty_ld_pll_ct(पूर्णांक offset, स्थिर काष्ठा atyfb_par *par)
अणु
	u8 res;

	/* ग_लिखो addr byte */
	aty_st_8(CLOCK_CNTL_ADDR, (offset << 2) & PLL_ADDR, par);
	/* पढ़ो the रेजिस्टर value */
	res = aty_ld_8(CLOCK_CNTL_DATA, par);
	वापस res;
पूर्ण

अटल व्योम aty_st_pll_ct(पूर्णांक offset, u8 val, स्थिर काष्ठा atyfb_par *par)
अणु
	/* ग_लिखो addr byte */
	aty_st_8(CLOCK_CNTL_ADDR, ((offset << 2) & PLL_ADDR) | PLL_WR_EN, par);
	/* ग_लिखो the रेजिस्टर value */
	aty_st_8(CLOCK_CNTL_DATA, val & PLL_DATA, par);
	aty_st_8(CLOCK_CNTL_ADDR, ((offset << 2) & PLL_ADDR) & ~PLL_WR_EN, par);
पूर्ण

/*
 * by Daniel Mantione
 *                                  <daniel.mantione@मुक्तpascal.org>
 *
 *
 * ATI Mach64 CT घड़ी synthesis description.
 *
 * All घड़ीs on the Mach64 can be calculated using the same principle:
 *
 *       XTALIN * x * FB_DIV
 * CLK = ----------------------
 *       PLL_REF_DIV * POST_DIV
 *
 * XTALIN is a fixed speed घड़ी. Common speeds are 14.31 MHz and 29.50 MHz.
 * PLL_REF_DIV can be set by the user, but is the same क्रम all घड़ीs.
 * FB_DIV can be set by the user क्रम each घड़ी inभागidually, it should be set
 * between 128 and 255, the chip will generate a bad घड़ी संकेत क्रम too low
 * values.
 * x depends on the type of घड़ी; usually it is 2, but क्रम the MCLK it can also
 * be set to 4.
 * POST_DIV can be set by the user क्रम each घड़ी inभागidually, Possible values
 * are 1,2,4,8 and क्रम some घड़ीs other values are available too.
 * CLK is of course the घड़ी speed that is generated.
 *
 * The Mach64 has these घड़ीs:
 *
 * MCLK			The घड़ी rate of the chip
 * XCLK			The घड़ी rate of the on-chip memory
 * VCLK0		First pixel घड़ी of first CRT controller
 * VCLK1    Second pixel घड़ी of first CRT controller
 * VCLK2		Third pixel घड़ी of first CRT controller
 * VCLK3    Fourth pixel घड़ी of first CRT controller
 * VCLK			Selected pixel घड़ी, one of VCLK0, VCLK1, VCLK2, VCLK3
 * V2CLK		Pixel घड़ी of the second CRT controller.
 * SCLK			Multi-purpose घड़ी
 *
 * - MCLK and XCLK use the same FB_DIV
 * - VCLK0 .. VCLK3 use the same FB_DIV
 * - V2CLK is needed when the second CRTC is used (can be used क्रम dualhead);
 *   i.e. CRT monitor connected to laptop has dअगरferent resolution than built
 *   in LCD monitor.
 * - SCLK is not available on all cards; it is know to exist on the Rage LT-PRO,
 *   Rage XL and Rage Mobility. It is know not to exist on the Mach64 VT.
 * - V2CLK is not available on all cards, most likely only the Rage LT-PRO,
 *   the Rage XL and the Rage Mobility
 *
 * SCLK can be used to:
 * - Clock the chip instead of MCLK
 * - Replace XTALIN with a user defined frequency
 * - Generate the pixel घड़ी क्रम the LCD monitor (instead of VCLK)
 */

 /*
  * It can be quite hard to calculate XCLK and MCLK अगर they करोn't run at the
  * same frequency. Luckily, until now all cards that need asynchrone घड़ी
  * speeds seem to have SCLK.
  * So this driver uses SCLK to घड़ी the chip and XCLK to घड़ी the memory.
  */

/* ------------------------------------------------------------------------- */

/*
 *  PLL programming (Mach64 CT family)
 *
 *
 * This procedure sets the display fअगरo. The display fअगरo is a buffer that
 * contains data पढ़ो from the video memory that रुकोs to be processed by
 * the CRT controller.
 *
 * On the more modern Mach64 variants, the chip करोesn't calculate the
 * पूर्णांकerval after which the display fअगरo has to be reloaded from memory
 * स्वतःmatically, the driver has to करो it instead.
 */

#घोषणा Maximum_DSP_PRECISION 7
स्थिर u8 aty_postभागiders[8] = अणु1,2,4,8,3,5,6,12पूर्ण;

अटल पूर्णांक aty_dsp_gt(स्थिर काष्ठा fb_info *info, u32 bpp, काष्ठा pll_ct *pll)
अणु
	u32 dsp_off, dsp_on, dsp_xclks;
	u32 multiplier, भागider, ras_multiplier, ras_भागider, पंचांगp;
	u8 vshअगरt, xshअगरt;
	s8 dsp_precision;

	multiplier = ((u32)pll->mclk_fb_भाग) * pll->vclk_post_भाग_real;
	भागider = ((u32)pll->vclk_fb_भाग) * pll->xclk_ref_भाग;

	ras_multiplier = pll->xclkmaxrasdelay;
	ras_भागider = 1;

	अगर (bpp>=8)
		भागider = भागider * (bpp >> 2);

	vshअगरt = (6 - 2) - pll->xclk_post_भाग;	/* FIFO is 64 bits wide in accelerator mode ... */

	अगर (bpp == 0)
		vshअगरt--;	/* ... but only 32 bits in VGA mode. */

#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अगर (pll->xres != 0) अणु
		काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;

		multiplier = multiplier * par->lcd_width;
		भागider = भागider * pll->xres & ~7;

		ras_multiplier = ras_multiplier * par->lcd_width;
		ras_भागider = ras_भागider * pll->xres & ~7;
	पूर्ण
#पूर्ण_अगर
	/* If we करोn't do this, 32 bits for multiplier & divider won't be
	enough in certain situations! */
	जबतक (((multiplier | भागider) & 1) == 0) अणु
		multiplier = multiplier >> 1;
		भागider = भागider >> 1;
	पूर्ण

	/* Determine DSP precision first */
	पंचांगp = ((multiplier * pll->fअगरo_size) << vshअगरt) / भागider;

	क्रम (dsp_precision = -5;  पंचांगp;  dsp_precision++)
		पंचांगp >>= 1;
	अगर (dsp_precision < 0)
		dsp_precision = 0;
	अन्यथा अगर (dsp_precision > Maximum_DSP_PRECISION)
		dsp_precision = Maximum_DSP_PRECISION;

	xshअगरt = 6 - dsp_precision;
	vshअगरt += xshअगरt;

	/* Move on to dsp_off */
	dsp_off = ((multiplier * (pll->fअगरo_size - 1)) << vshअगरt) / भागider -
		(1 << (vshअगरt - xshअगरt));

/*    अगर (bpp == 0)
        dsp_on = ((multiplier * 20 << vshअगरt) + भागider) / भागider;
    अन्यथा */
	अणु
		dsp_on = ((multiplier << vshअगरt) + भागider) / भागider;
		पंचांगp = ((ras_multiplier << xshअगरt) + ras_भागider) / ras_भागider;
		अगर (dsp_on < पंचांगp)
			dsp_on = पंचांगp;
		dsp_on = dsp_on + (पंचांगp * 2) + (pll->xclkpagefaultdelay << xshअगरt);
	पूर्ण

	/* Calculate rounding factor and apply it to dsp_on */
	पंचांगp = ((1 << (Maximum_DSP_PRECISION - dsp_precision)) - 1) >> 1;
	dsp_on = ((dsp_on + पंचांगp) / (पंचांगp + 1)) * (पंचांगp + 1);

	अगर (dsp_on >= ((dsp_off / (पंचांगp + 1)) * (पंचांगp + 1))) अणु
		dsp_on = dsp_off - (multiplier << vshअगरt) / भागider;
		dsp_on = (dsp_on / (पंचांगp + 1)) * (पंचांगp + 1);
	पूर्ण

	/* Last but not least:  dsp_xclks */
	dsp_xclks = ((multiplier << (vshअगरt + 5)) + भागider) / भागider;

	/* Get रेजिस्टर values. */
	pll->dsp_on_off = (dsp_on << 16) + dsp_off;
	pll->dsp_config = (dsp_precision << 20) | (pll->dsp_loop_latency << 16) | dsp_xclks;
#अगर_घोषित DEBUG
	prपूर्णांकk("atyfb(%s): dsp_config 0x%08x, dsp_on_off 0x%08x\n",
		__func__, pll->dsp_config, pll->dsp_on_off);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक aty_valid_pll_ct(स्थिर काष्ठा fb_info *info, u32 vclk_per, काष्ठा pll_ct *pll)
अणु
	u32 q;
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	पूर्णांक pllvclk;

	/* FIXME: use the VTB/GTB /अणु3,6,12पूर्ण post भागiders अगर they're better suited */
	q = par->ref_clk_per * pll->pll_ref_भाग * 4 / vclk_per;
	अगर (q < 16*8 || q > 255*8) अणु
		prपूर्णांकk(KERN_CRIT "atyfb: vclk out of range\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		pll->vclk_post_भाग  = (q < 128*8);
		pll->vclk_post_भाग += (q <  64*8);
		pll->vclk_post_भाग += (q <  32*8);
	पूर्ण
	pll->vclk_post_भाग_real = aty_postभागiders[pll->vclk_post_भाग];
	//    pll->vclk_post_भाग <<= 6;
	pll->vclk_fb_भाग = q * pll->vclk_post_भाग_real / 8;
	pllvclk = (1000000 * 2 * pll->vclk_fb_भाग) /
		(par->ref_clk_per * pll->pll_ref_भाग);
#अगर_घोषित DEBUG
	prपूर्णांकk("atyfb(%s): pllvclk=%d MHz, vclk=%d MHz\n",
		__func__, pllvclk, pllvclk / pll->vclk_post_भाग_real);
#पूर्ण_अगर
	pll->pll_vclk_cntl = 0x03; /* VCLK = PLL_VCLK/VCLKx_POST */

	/* Set ECP (scaler/overlay घड़ी) भागider */
	अगर (par->pll_limits.ecp_max) अणु
		पूर्णांक ecp = pllvclk / pll->vclk_post_भाग_real;
		पूर्णांक ecp_भाग = 0;

		जबतक (ecp > par->pll_limits.ecp_max && ecp_भाग < 2) अणु
			ecp >>= 1;
			ecp_भाग++;
		पूर्ण
		pll->pll_vclk_cntl |= ecp_भाग << 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aty_var_to_pll_ct(स्थिर काष्ठा fb_info *info, u32 vclk_per, u32 bpp, जोड़ aty_pll *pll)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	पूर्णांक err;

	अगर ((err = aty_valid_pll_ct(info, vclk_per, &pll->ct)))
		वापस err;
	अगर (M64_HAS(GTB_DSP) && (err = aty_dsp_gt(info, bpp, &pll->ct)))
		वापस err;
	/*aty_calc_pll_ct(info, &pll->ct);*/
	वापस 0;
पूर्ण

अटल u32 aty_pll_to_var_ct(स्थिर काष्ठा fb_info *info, स्थिर जोड़ aty_pll *pll)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 ret;
	ret = par->ref_clk_per * pll->ct.pll_ref_भाग * pll->ct.vclk_post_भाग_real / pll->ct.vclk_fb_भाग / 2;
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अगर(pll->ct.xres > 0) अणु
		ret *= par->lcd_width;
		ret /= pll->ct.xres;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित DEBUG
	prपूर्णांकk("atyfb(%s): calculated 0x%08X(%i)\n", __func__, ret, ret);
#पूर्ण_अगर
	वापस ret;
पूर्ण

व्योम aty_set_pll_ct(स्थिर काष्ठा fb_info *info, स्थिर जोड़ aty_pll *pll)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 crtc_gen_cntl;
	u8 पंचांगp, पंचांगp2;

#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	u32 lcd_gen_cntrl = 0;
#पूर्ण_अगर

#अगर_घोषित DEBUG
	prपूर्णांकk("atyfb(%s): about to program:\n"
		"pll_ext_cntl=0x%02x pll_gen_cntl=0x%02x pll_vclk_cntl=0x%02x\n",
		__func__,
		pll->ct.pll_ext_cntl, pll->ct.pll_gen_cntl, pll->ct.pll_vclk_cntl);

	prपूर्णांकk("atyfb(%s): setting clock %lu for FeedBackDivider %i, ReferenceDivider %i, PostDivider %i(%i)\n",
		__func__,
		par->clk_wr_offset, pll->ct.vclk_fb_भाग,
		pll->ct.pll_ref_भाग, pll->ct.vclk_post_भाग, pll->ct.vclk_post_भाग_real);
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अगर (par->lcd_table != 0) अणु
		/* turn off LCD */
		lcd_gen_cntrl = aty_ld_lcd(LCD_GEN_CNTL, par);
		aty_st_lcd(LCD_GEN_CNTL, lcd_gen_cntrl & ~LCD_ON, par);
	पूर्ण
#पूर्ण_अगर
	aty_st_8(CLOCK_CNTL, par->clk_wr_offset | CLOCK_STROBE, par);

	/* Temporarily चयन to accelerator mode */
	crtc_gen_cntl = aty_ld_le32(CRTC_GEN_CNTL, par);
	अगर (!(crtc_gen_cntl & CRTC_EXT_DISP_EN))
		aty_st_le32(CRTC_GEN_CNTL, crtc_gen_cntl | CRTC_EXT_DISP_EN, par);

	/* Reset VCLK generator */
	aty_st_pll_ct(PLL_VCLK_CNTL, pll->ct.pll_vclk_cntl, par);

	/* Set post-भागider */
	पंचांगp2 = par->clk_wr_offset << 1;
	पंचांगp = aty_ld_pll_ct(VCLK_POST_DIV, par);
	पंचांगp &= ~(0x03U << पंचांगp2);
	पंचांगp |= ((pll->ct.vclk_post_भाग & 0x03U) << पंचांगp2);
	aty_st_pll_ct(VCLK_POST_DIV, पंचांगp, par);

	/* Set extended post-भागider */
	पंचांगp = aty_ld_pll_ct(PLL_EXT_CNTL, par);
	पंचांगp &= ~(0x10U << par->clk_wr_offset);
	पंचांगp &= 0xF0U;
	पंचांगp |= pll->ct.pll_ext_cntl;
	aty_st_pll_ct(PLL_EXT_CNTL, पंचांगp, par);

	/* Set feedback भागider */
	पंचांगp = VCLK0_FB_DIV + par->clk_wr_offset;
	aty_st_pll_ct(पंचांगp, (pll->ct.vclk_fb_भाग & 0xFFU), par);

	aty_st_pll_ct(PLL_GEN_CNTL, (pll->ct.pll_gen_cntl & (~(PLL_OVERRIDE | PLL_MCLK_RST))) | OSC_EN, par);

	/* End VCLK generator reset */
	aty_st_pll_ct(PLL_VCLK_CNTL, pll->ct.pll_vclk_cntl & ~(PLL_VCLK_RST), par);
	mdelay(5);

	aty_st_pll_ct(PLL_GEN_CNTL, pll->ct.pll_gen_cntl, par);
	aty_st_pll_ct(PLL_VCLK_CNTL, pll->ct.pll_vclk_cntl, par);
	mdelay(1);

	/* Restore mode रेजिस्टर */
	अगर (!(crtc_gen_cntl & CRTC_EXT_DISP_EN))
		aty_st_le32(CRTC_GEN_CNTL, crtc_gen_cntl, par);

	अगर (M64_HAS(GTB_DSP)) अणु
		u8 dll_cntl;

		अगर (M64_HAS(XL_DLL))
			dll_cntl = 0x80;
		अन्यथा अगर (par->ram_type >= SDRAM)
			dll_cntl = 0xa6;
		अन्यथा
			dll_cntl = 0xa0;
		aty_st_pll_ct(DLL_CNTL, dll_cntl, par);
		aty_st_pll_ct(VFC_CNTL, 0x1b, par);
		aty_st_le32(DSP_CONFIG, pll->ct.dsp_config, par);
		aty_st_le32(DSP_ON_OFF, pll->ct.dsp_on_off, par);

		mdelay(10);
		aty_st_pll_ct(DLL_CNTL, dll_cntl, par);
		mdelay(10);
		aty_st_pll_ct(DLL_CNTL, dll_cntl | 0x40, par);
		mdelay(10);
		aty_st_pll_ct(DLL_CNTL, dll_cntl & ~0x40, par);
	पूर्ण
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अगर (par->lcd_table != 0) अणु
		/* restore LCD */
		aty_st_lcd(LCD_GEN_CNTL, lcd_gen_cntrl, par);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम aty_get_pll_ct(स्थिर काष्ठा fb_info *info, जोड़ aty_pll *pll)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u8 पंचांगp, घड़ी;

	घड़ी = aty_ld_8(CLOCK_CNTL, par) & 0x03U;
	पंचांगp = घड़ी << 1;
	pll->ct.vclk_post_भाग = (aty_ld_pll_ct(VCLK_POST_DIV, par) >> पंचांगp) & 0x03U;

	pll->ct.pll_ext_cntl = aty_ld_pll_ct(PLL_EXT_CNTL, par) & 0x0FU;
	pll->ct.vclk_fb_भाग = aty_ld_pll_ct(VCLK0_FB_DIV + घड़ी, par) & 0xFFU;
	pll->ct.pll_ref_भाग = aty_ld_pll_ct(PLL_REF_DIV, par);
	pll->ct.mclk_fb_भाग = aty_ld_pll_ct(MCLK_FB_DIV, par);

	pll->ct.pll_gen_cntl = aty_ld_pll_ct(PLL_GEN_CNTL, par);
	pll->ct.pll_vclk_cntl = aty_ld_pll_ct(PLL_VCLK_CNTL, par);

	अगर (M64_HAS(GTB_DSP)) अणु
		pll->ct.dsp_config = aty_ld_le32(DSP_CONFIG, par);
		pll->ct.dsp_on_off = aty_ld_le32(DSP_ON_OFF, par);
	पूर्ण
पूर्ण

अटल पूर्णांक aty_init_pll_ct(स्थिर काष्ठा fb_info *info, जोड़ aty_pll *pll)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u8 mpost_भाग, xpost_भाग, sclk_post_भाग_real;
	u32 q, memcntl, trp;
	u32 dsp_config;
#अगर_घोषित DEBUG
	पूर्णांक pllmclk, pllsclk;
#पूर्ण_अगर
	pll->ct.pll_ext_cntl = aty_ld_pll_ct(PLL_EXT_CNTL, par);
	pll->ct.xclk_post_भाग = pll->ct.pll_ext_cntl & 0x07;
	pll->ct.xclk_ref_भाग = 1;
	चयन (pll->ct.xclk_post_भाग) अणु
	हाल 0:  हाल 1:  हाल 2:  हाल 3:
		अवरोध;

	हाल 4:
		pll->ct.xclk_ref_भाग = 3;
		pll->ct.xclk_post_भाग = 0;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_CRIT "atyfb: Unsupported xclk source:  %d.\n", pll->ct.xclk_post_भाग);
		वापस -EINVAL;
	पूर्ण
	pll->ct.mclk_fb_mult = 2;
	अगर(pll->ct.pll_ext_cntl & PLL_MFB_TIMES_4_2B) अणु
		pll->ct.mclk_fb_mult = 4;
		pll->ct.xclk_post_भाग -= 1;
	पूर्ण

#अगर_घोषित DEBUG
	prपूर्णांकk("atyfb(%s): mclk_fb_mult=%d, xclk_post_div=%d\n",
		__func__, pll->ct.mclk_fb_mult, pll->ct.xclk_post_भाग);
#पूर्ण_अगर

	memcntl = aty_ld_le32(MEM_CNTL, par);
	trp = (memcntl & 0x300) >> 8;

	pll->ct.xclkpagefaultdelay = ((memcntl & 0xc00) >> 10) + ((memcntl & 0x1000) >> 12) + trp + 2;
	pll->ct.xclkmaxrasdelay = ((memcntl & 0x70000) >> 16) + trp + 2;

	अगर (M64_HAS(FIFO_32)) अणु
		pll->ct.fअगरo_size = 32;
	पूर्ण अन्यथा अणु
		pll->ct.fअगरo_size = 24;
		pll->ct.xclkpagefaultdelay += 2;
		pll->ct.xclkmaxrasdelay += 3;
	पूर्ण

	चयन (par->ram_type) अणु
	हाल DRAM:
		अगर (info->fix.smem_len<=ONE_MB) अणु
			pll->ct.dsp_loop_latency = 10;
		पूर्ण अन्यथा अणु
			pll->ct.dsp_loop_latency = 8;
			pll->ct.xclkpagefaultdelay += 2;
		पूर्ण
		अवरोध;
	हाल EDO:
	हाल PSEUDO_EDO:
		अगर (info->fix.smem_len<=ONE_MB) अणु
			pll->ct.dsp_loop_latency = 9;
		पूर्ण अन्यथा अणु
			pll->ct.dsp_loop_latency = 8;
			pll->ct.xclkpagefaultdelay += 1;
		पूर्ण
		अवरोध;
	हाल SDRAM:
		अगर (info->fix.smem_len<=ONE_MB) अणु
			pll->ct.dsp_loop_latency = 11;
		पूर्ण अन्यथा अणु
			pll->ct.dsp_loop_latency = 10;
			pll->ct.xclkpagefaultdelay += 1;
		पूर्ण
		अवरोध;
	हाल SGRAM:
		pll->ct.dsp_loop_latency = 8;
		pll->ct.xclkpagefaultdelay += 3;
		अवरोध;
	शेष:
		pll->ct.dsp_loop_latency = 11;
		pll->ct.xclkpagefaultdelay += 3;
		अवरोध;
	पूर्ण

	अगर (pll->ct.xclkmaxrasdelay <= pll->ct.xclkpagefaultdelay)
		pll->ct.xclkmaxrasdelay = pll->ct.xclkpagefaultdelay + 1;

	/* Allow BIOS to override */
	dsp_config = aty_ld_le32(DSP_CONFIG, par);
	aty_ld_le32(DSP_ON_OFF, par);
	aty_ld_le32(VGA_DSP_CONFIG, par);
	aty_ld_le32(VGA_DSP_ON_OFF, par);

	अगर (dsp_config)
		pll->ct.dsp_loop_latency = (dsp_config & DSP_LOOP_LATENCY) >> 16;
#अगर 0
	FIXME: is it relevant क्रम us?
	अगर ((!dsp_on_off && !M64_HAS(RESET_3D)) ||
		((dsp_on_off == vga_dsp_on_off) &&
		(!dsp_config || !((dsp_config ^ vga_dsp_config) & DSP_XCLKS_PER_QW)))) अणु
		vga_dsp_on_off &= VGA_DSP_OFF;
		vga_dsp_config &= VGA_DSP_XCLKS_PER_QW;
		अगर (ATIDivide(vga_dsp_on_off, vga_dsp_config, 5, 1) > 24)
			pll->ct.fअगरo_size = 32;
		अन्यथा
			pll->ct.fअगरo_size = 24;
	पूर्ण
#पूर्ण_अगर
	/* Exit अगर the user करोes not want us to tamper with the घड़ी
	rates of her chip. */
	अगर (par->mclk_per == 0) अणु
		u8 mclk_fb_भाग, pll_ext_cntl;
		pll->ct.pll_ref_भाग = aty_ld_pll_ct(PLL_REF_DIV, par);
		pll_ext_cntl = aty_ld_pll_ct(PLL_EXT_CNTL, par);
		pll->ct.xclk_post_भाग_real = aty_postभागiders[pll_ext_cntl & 0x07];
		mclk_fb_भाग = aty_ld_pll_ct(MCLK_FB_DIV, par);
		अगर (pll_ext_cntl & PLL_MFB_TIMES_4_2B)
			mclk_fb_भाग <<= 1;
		pll->ct.mclk_fb_भाग = mclk_fb_भाग;
		वापस 0;
	पूर्ण

	pll->ct.pll_ref_भाग = par->pll_per * 2 * 255 / par->ref_clk_per;

	/* FIXME: use the VTB/GTB /3 post भागider अगर it's better suited */
	q = par->ref_clk_per * pll->ct.pll_ref_भाग * 8 /
		(pll->ct.mclk_fb_mult * par->xclk_per);

	अगर (q < 16*8 || q > 255*8) अणु
		prपूर्णांकk(KERN_CRIT "atxfb: xclk out of range\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		xpost_भाग  = (q < 128*8);
		xpost_भाग += (q <  64*8);
		xpost_भाग += (q <  32*8);
	पूर्ण
	pll->ct.xclk_post_भाग_real = aty_postभागiders[xpost_भाग];
	pll->ct.mclk_fb_भाग = q * pll->ct.xclk_post_भाग_real / 8;

#अगर_घोषित CONFIG_PPC
	अगर (machine_is(घातermac)) अणु
		/* Override PLL_EXT_CNTL & 0x07. */
		pll->ct.xclk_post_भाग = xpost_भाग;
		pll->ct.xclk_ref_भाग = 1;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित DEBUG
	pllmclk = (1000000 * pll->ct.mclk_fb_mult * pll->ct.mclk_fb_भाग) /
			(par->ref_clk_per * pll->ct.pll_ref_भाग);
	prपूर्णांकk("atyfb(%s): pllmclk=%d MHz, xclk=%d MHz\n",
		__func__, pllmclk, pllmclk / pll->ct.xclk_post_भाग_real);
#पूर्ण_अगर

	अगर (M64_HAS(SDRAM_MAGIC_PLL) && (par->ram_type >= SDRAM))
		pll->ct.pll_gen_cntl = OSC_EN;
	अन्यथा
		pll->ct.pll_gen_cntl = OSC_EN | DLL_PWDN /* | FORCE_DCLK_TRI_STATE */;

	अगर (M64_HAS(MAGIC_POSTDIV))
		pll->ct.pll_ext_cntl = 0;
	अन्यथा
		pll->ct.pll_ext_cntl = xpost_भाग;

	अगर (pll->ct.mclk_fb_mult == 4)
		pll->ct.pll_ext_cntl |= PLL_MFB_TIMES_4_2B;

	अगर (par->mclk_per == par->xclk_per) अणु
		pll->ct.pll_gen_cntl |= (xpost_भाग << 4); /* mclk == xclk */
	पूर्ण अन्यथा अणु
		/*
		* The chip घड़ी is not equal to the memory घड़ी.
		* Thereक्रमe we will use sclk to घड़ी the chip.
		*/
		pll->ct.pll_gen_cntl |= (6 << 4); /* mclk == sclk */

		q = par->ref_clk_per * pll->ct.pll_ref_भाग * 4 / par->mclk_per;
		अगर (q < 16*8 || q > 255*8) अणु
			prपूर्णांकk(KERN_CRIT "atyfb: mclk out of range\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			mpost_भाग  = (q < 128*8);
			mpost_भाग += (q <  64*8);
			mpost_भाग += (q <  32*8);
		पूर्ण
		sclk_post_भाग_real = aty_postभागiders[mpost_भाग];
		pll->ct.sclk_fb_भाग = q * sclk_post_भाग_real / 8;
		pll->ct.spll_cntl2 = mpost_भाग << 4;
#अगर_घोषित DEBUG
		pllsclk = (1000000 * 2 * pll->ct.sclk_fb_भाग) /
			(par->ref_clk_per * pll->ct.pll_ref_भाग);
		prपूर्णांकk("atyfb(%s): use sclk, pllsclk=%d MHz, sclk=mclk=%d MHz\n",
			__func__, pllsclk, pllsclk / sclk_post_भाग_real);
#पूर्ण_अगर
	पूर्ण

	/* Disable the extra precision pixel घड़ी controls since we करो not use them. */
	pll->ct.ext_vpll_cntl = aty_ld_pll_ct(EXT_VPLL_CNTL, par);
	pll->ct.ext_vpll_cntl &= ~(EXT_VPLL_EN | EXT_VPLL_VGA_EN | EXT_VPLL_INSYNC);

	वापस 0;
पूर्ण

अटल व्योम aty_resume_pll_ct(स्थिर काष्ठा fb_info *info,
			      जोड़ aty_pll *pll)
अणु
	काष्ठा atyfb_par *par = info->par;

	अगर (par->mclk_per != par->xclk_per) अणु
		/*
		* This disables the sclk, crashes the computer as reported:
		* aty_st_pll_ct(SPLL_CNTL2, 3, info);
		*
		* So it seems the sclk must be enabled beक्रमe it is used;
		* so PLL_GEN_CNTL must be programmed *after* the sclk.
		*/
		aty_st_pll_ct(SCLK_FB_DIV, pll->ct.sclk_fb_भाग, par);
		aty_st_pll_ct(SPLL_CNTL2, pll->ct.spll_cntl2, par);
		/*
		 * SCLK has been started. Wait क्रम the PLL to lock. 5 ms
		 * should be enough according to mach64 programmer's guide.
		 */
		mdelay(5);
	पूर्ण

	aty_st_pll_ct(PLL_REF_DIV, pll->ct.pll_ref_भाग, par);
	aty_st_pll_ct(PLL_GEN_CNTL, pll->ct.pll_gen_cntl, par);
	aty_st_pll_ct(MCLK_FB_DIV, pll->ct.mclk_fb_भाग, par);
	aty_st_pll_ct(PLL_EXT_CNTL, pll->ct.pll_ext_cntl, par);
	aty_st_pll_ct(EXT_VPLL_CNTL, pll->ct.ext_vpll_cntl, par);
पूर्ण

अटल पूर्णांक dummy(व्योम)
अणु
	वापस 0;
पूर्ण

स्थिर काष्ठा aty_dac_ops aty_dac_ct = अणु
	.set_dac	= (व्योम *) dummy,
पूर्ण;

स्थिर काष्ठा aty_pll_ops aty_pll_ct = अणु
	.var_to_pll	= aty_var_to_pll_ct,
	.pll_to_var	= aty_pll_to_var_ct,
	.set_pll	= aty_set_pll_ct,
	.get_pll	= aty_get_pll_ct,
	.init_pll	= aty_init_pll_ct,
	.resume_pll	= aty_resume_pll_ct,
पूर्ण;
