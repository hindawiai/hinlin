<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) 2007 Advanced Micro Devices, Inc.
 *   Copyright (C) 2008 Andres Salomon <dilinger@debian.org>
 */
#समावेश <linux/fb.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/msr.h>
#समावेश <linux/cs5535.h>
#समावेश <यंत्र/delay.h>

#समावेश "gxfb.h"

अटल व्योम gx_save_regs(काष्ठा gxfb_par *par)
अणु
	पूर्णांक i;

	/* रुको क्रम the BLT engine to stop being busy */
	करो अणु
		i = पढ़ो_gp(par, GP_BLT_STATUS);
	पूर्ण जबतक (i & (GP_BLT_STATUS_BLT_PENDING | GP_BLT_STATUS_BLT_BUSY));

	/* save MSRs */
	rdmsrl(MSR_GX_MSR_PADSEL, par->msr.padsel);
	rdmsrl(MSR_GLCP_DOTPLL, par->msr.करोtpll);

	ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);

	/* save रेजिस्टरs */
	स_नकल(par->gp, par->gp_regs, माप(par->gp));
	स_नकल(par->dc, par->dc_regs, माप(par->dc));
	स_नकल(par->vp, par->vid_regs, माप(par->vp));
	स_नकल(par->fp, par->vid_regs + VP_FP_START, माप(par->fp));

	/* save the palette */
	ग_लिखो_dc(par, DC_PAL_ADDRESS, 0);
	क्रम (i = 0; i < ARRAY_SIZE(par->pal); i++)
		par->pal[i] = पढ़ो_dc(par, DC_PAL_DATA);
पूर्ण

अटल व्योम gx_set_करोtpll(uपूर्णांक32_t करोtpll_hi)
अणु
	uपूर्णांक32_t करोtpll_lo;
	पूर्णांक i;

	rdmsrl(MSR_GLCP_DOTPLL, करोtpll_lo);
	करोtpll_lo |= MSR_GLCP_DOTPLL_DOTRESET;
	करोtpll_lo &= ~MSR_GLCP_DOTPLL_BYPASS;
	wrmsr(MSR_GLCP_DOTPLL, करोtpll_lo, करोtpll_hi);

	/* रुको क्रम the PLL to lock */
	क्रम (i = 0; i < 200; i++) अणु
		rdmsrl(MSR_GLCP_DOTPLL, करोtpll_lo);
		अगर (करोtpll_lo & MSR_GLCP_DOTPLL_LOCK)
			अवरोध;
		udelay(1);
	पूर्ण

	/* PLL set, unlock */
	करोtpll_lo &= ~MSR_GLCP_DOTPLL_DOTRESET;
	wrmsr(MSR_GLCP_DOTPLL, करोtpll_lo, करोtpll_hi);
पूर्ण

अटल व्योम gx_restore_gfx_proc(काष्ठा gxfb_par *par)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(par->gp); i++) अणु
		चयन (i) अणु
		हाल GP_VECTOR_MODE:
		हाल GP_BLT_MODE:
		हाल GP_BLT_STATUS:
		हाल GP_HST_SRC:
			/* करोn't restore these रेजिस्टरs */
			अवरोध;
		शेष:
			ग_लिखो_gp(par, i, par->gp[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gx_restore_display_ctlr(काष्ठा gxfb_par *par)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(par->dc); i++) अणु
		चयन (i) अणु
		हाल DC_UNLOCK:
			/* unlock the DC; runs first */
			ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);
			अवरोध;

		हाल DC_GENERAL_CFG:
			/* ग_लिखो without the enables */
			ग_लिखो_dc(par, i, par->dc[i] & ~(DC_GENERAL_CFG_VIDE |
					DC_GENERAL_CFG_ICNE |
					DC_GENERAL_CFG_CURE |
					DC_GENERAL_CFG_DFLE));
			अवरोध;

		हाल DC_DISPLAY_CFG:
			/* ग_लिखो without the enables */
			ग_लिखो_dc(par, i, par->dc[i] & ~(DC_DISPLAY_CFG_VDEN |
					DC_DISPLAY_CFG_GDEN |
					DC_DISPLAY_CFG_TGEN));
			अवरोध;

		हाल DC_RSVD_0:
		हाल DC_RSVD_1:
		हाल DC_RSVD_2:
		हाल DC_RSVD_3:
		हाल DC_RSVD_4:
		हाल DC_LINE_CNT:
		हाल DC_PAL_ADDRESS:
		हाल DC_PAL_DATA:
		हाल DC_DFIFO_DIAG:
		हाल DC_CFIFO_DIAG:
		हाल DC_RSVD_5:
			/* करोn't restore these रेजिस्टरs */
			अवरोध;
		शेष:
			ग_लिखो_dc(par, i, par->dc[i]);
		पूर्ण
	पूर्ण

	/* restore the palette */
	ग_लिखो_dc(par, DC_PAL_ADDRESS, 0);
	क्रम (i = 0; i < ARRAY_SIZE(par->pal); i++)
		ग_लिखो_dc(par, DC_PAL_DATA, par->pal[i]);
पूर्ण

अटल व्योम gx_restore_video_proc(काष्ठा gxfb_par *par)
अणु
	पूर्णांक i;

	wrmsrl(MSR_GX_MSR_PADSEL, par->msr.padsel);

	क्रम (i = 0; i < ARRAY_SIZE(par->vp); i++) अणु
		चयन (i) अणु
		हाल VP_VCFG:
			/* करोn't enable video yet */
			ग_लिखो_vp(par, i, par->vp[i] & ~VP_VCFG_VID_EN);
			अवरोध;

		हाल VP_DCFG:
			/* करोn't enable CRT yet */
			ग_लिखो_vp(par, i, par->vp[i] &
					~(VP_DCFG_DAC_BL_EN | VP_DCFG_VSYNC_EN |
					VP_DCFG_HSYNC_EN | VP_DCFG_CRT_EN));
			अवरोध;

		हाल VP_GAR:
		हाल VP_GDR:
		हाल VP_RSVD_0:
		हाल VP_RSVD_1:
		हाल VP_RSVD_2:
		हाल VP_RSVD_3:
		हाल VP_CRC32:
		हाल VP_AWT:
		हाल VP_VTM:
			/* करोn't restore these रेजिस्टरs */
			अवरोध;
		शेष:
			ग_लिखो_vp(par, i, par->vp[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gx_restore_regs(काष्ठा gxfb_par *par)
अणु
	पूर्णांक i;

	gx_set_करोtpll((uपूर्णांक32_t) (par->msr.करोtpll >> 32));
	gx_restore_gfx_proc(par);
	gx_restore_display_ctlr(par);
	gx_restore_video_proc(par);

	/* Flat Panel */
	क्रम (i = 0; i < ARRAY_SIZE(par->fp); i++) अणु
		अगर (i != FP_PM && i != FP_RSVD_0)
			ग_लिखो_fp(par, i, par->fp[i]);
	पूर्ण
पूर्ण

अटल व्योम gx_disable_graphics(काष्ठा gxfb_par *par)
अणु
	/* shut करोwn the engine */
	ग_लिखो_vp(par, VP_VCFG, par->vp[VP_VCFG] & ~VP_VCFG_VID_EN);
	ग_लिखो_vp(par, VP_DCFG, par->vp[VP_DCFG] & ~(VP_DCFG_DAC_BL_EN |
			VP_DCFG_VSYNC_EN | VP_DCFG_HSYNC_EN | VP_DCFG_CRT_EN));

	/* turn off the flat panel */
	ग_लिखो_fp(par, FP_PM, par->fp[FP_PM] & ~FP_PM_P);


	/* turn off display */
	ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);
	ग_लिखो_dc(par, DC_GENERAL_CFG, par->dc[DC_GENERAL_CFG] &
			~(DC_GENERAL_CFG_VIDE | DC_GENERAL_CFG_ICNE |
			DC_GENERAL_CFG_CURE | DC_GENERAL_CFG_DFLE));
	ग_लिखो_dc(par, DC_DISPLAY_CFG, par->dc[DC_DISPLAY_CFG] &
			~(DC_DISPLAY_CFG_VDEN | DC_DISPLAY_CFG_GDEN |
			DC_DISPLAY_CFG_TGEN));
	ग_लिखो_dc(par, DC_UNLOCK, DC_UNLOCK_LOCK);
पूर्ण

अटल व्योम gx_enable_graphics(काष्ठा gxfb_par *par)
अणु
	uपूर्णांक32_t fp;

	fp = पढ़ो_fp(par, FP_PM);
	अगर (par->fp[FP_PM] & FP_PM_P) अणु
		/* घातer on the panel अगर not alपढ़ोy घातerअणुed,ingपूर्ण on */
		अगर (!(fp & (FP_PM_PANEL_ON|FP_PM_PANEL_PWR_UP)))
			ग_लिखो_fp(par, FP_PM, par->fp[FP_PM]);
	पूर्ण अन्यथा अणु
		/* घातer करोwn the panel अगर not alपढ़ोy घातerअणुed,ingपूर्ण करोwn */
		अगर (!(fp & (FP_PM_PANEL_OFF|FP_PM_PANEL_PWR_DOWN)))
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

पूर्णांक gx_घातerकरोwn(काष्ठा fb_info *info)
अणु
	काष्ठा gxfb_par *par = info->par;

	अगर (par->घातered_करोwn)
		वापस 0;

	gx_save_regs(par);
	gx_disable_graphics(par);

	par->घातered_करोwn = 1;
	वापस 0;
पूर्ण

पूर्णांक gx_घातerup(काष्ठा fb_info *info)
अणु
	काष्ठा gxfb_par *par = info->par;

	अगर (!par->घातered_करोwn)
		वापस 0;

	gx_restore_regs(par);
	gx_enable_graphics(par);

	par->घातered_करोwn  = 0;
	वापस 0;
पूर्ण
