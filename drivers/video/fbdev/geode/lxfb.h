<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Geode LX framebuffer driver
 *
 * Copyright (C) 2006-2007, Advanced Micro Devices,Inc.
 * Copyright (c) 2008  Andres Salomon <dilinger@debian.org>
 */
#अगर_अघोषित _LXFB_H_
#घोषणा _LXFB_H_

#समावेश <linux/fb.h>

#घोषणा GP_REG_COUNT	(0x7c / 4)
#घोषणा DC_REG_COUNT	(0xf0 / 4)
#घोषणा VP_REG_COUNT	(0x158 / 8)
#घोषणा FP_REG_COUNT	(0x60 / 8)

#घोषणा DC_PAL_COUNT	0x104
#घोषणा DC_HFILT_COUNT	0x100
#घोषणा DC_VFILT_COUNT	0x100
#घोषणा VP_COEFF_SIZE	0x1000
#घोषणा VP_PAL_COUNT	0x100

#घोषणा OUTPUT_CRT   0x01
#घोषणा OUTPUT_PANEL 0x02

काष्ठा lxfb_par अणु
	पूर्णांक output;

	व्योम __iomem *gp_regs;
	व्योम __iomem *dc_regs;
	व्योम __iomem *vp_regs;
	पूर्णांक घातered_करोwn;

	/* रेजिस्टर state, क्रम घातer mgmt functionality */
	काष्ठा अणु
		uपूर्णांक64_t padsel;
		uपूर्णांक64_t करोtpll;
		uपूर्णांक64_t dfglcfg;
		uपूर्णांक64_t dcspare;
	पूर्ण msr;

	uपूर्णांक32_t gp[GP_REG_COUNT];
	uपूर्णांक32_t dc[DC_REG_COUNT];
	uपूर्णांक64_t vp[VP_REG_COUNT];
	uपूर्णांक64_t fp[FP_REG_COUNT];

	uपूर्णांक32_t dc_pal[DC_PAL_COUNT];
	uपूर्णांक32_t vp_pal[VP_PAL_COUNT];
	uपूर्णांक32_t hcoeff[DC_HFILT_COUNT * 2];
	uपूर्णांक32_t vcoeff[DC_VFILT_COUNT];
	uपूर्णांक32_t vp_coeff[VP_COEFF_SIZE / 4];
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक lx_get_pitch(अचिन्हित पूर्णांक xres, पूर्णांक bpp)
अणु
	वापस (((xres * (bpp >> 3)) + 7) & ~7);
पूर्ण

व्योम lx_set_mode(काष्ठा fb_info *);
अचिन्हित पूर्णांक lx_framebuffer_size(व्योम);
पूर्णांक lx_blank_display(काष्ठा fb_info *, पूर्णांक);
व्योम lx_set_palette_reg(काष्ठा fb_info *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
			अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);

पूर्णांक lx_घातerकरोwn(काष्ठा fb_info *info);
पूर्णांक lx_घातerup(काष्ठा fb_info *info);

/* Graphics Processor रेजिस्टरs (table 6-29 from the data book) */
क्रमागत gp_रेजिस्टरs अणु
	GP_DST_OFFSET = 0,
	GP_SRC_OFFSET,
	GP_STRIDE,
	GP_WID_HEIGHT,

	GP_SRC_COLOR_FG,
	GP_SRC_COLOR_BG,
	GP_PAT_COLOR_0,
	GP_PAT_COLOR_1,

	GP_PAT_COLOR_2,
	GP_PAT_COLOR_3,
	GP_PAT_COLOR_4,
	GP_PAT_COLOR_5,

	GP_PAT_DATA_0,
	GP_PAT_DATA_1,
	GP_RASTER_MODE,
	GP_VECTOR_MODE,

	GP_BLT_MODE,
	GP_BLT_STATUS,
	GP_HST_SRC,
	GP_BASE_OFFSET,

	GP_CMD_TOP,
	GP_CMD_BOT,
	GP_CMD_READ,
	GP_CMD_WRITE,

	GP_CH3_OFFSET,
	GP_CH3_MODE_STR,
	GP_CH3_WIDHI,
	GP_CH3_HSRC,

	GP_LUT_INDEX,
	GP_LUT_DATA,
	GP_INT_CNTRL, /* 0x78 */
पूर्ण;

#घोषणा GP_BLT_STATUS_CE		(1 << 4)	/* cmd buf empty */
#घोषणा GP_BLT_STATUS_PB		(1 << 0)	/* primitive busy */


/* Display Controller रेजिस्टरs (table 6-47 from the data book) */
क्रमागत dc_रेजिस्टरs अणु
	DC_UNLOCK = 0,
	DC_GENERAL_CFG,
	DC_DISPLAY_CFG,
	DC_ARB_CFG,

	DC_FB_ST_OFFSET,
	DC_CB_ST_OFFSET,
	DC_CURS_ST_OFFSET,
	DC_RSVD_0,

	DC_VID_Y_ST_OFFSET,
	DC_VID_U_ST_OFFSET,
	DC_VID_V_ST_OFFSET,
	DC_DV_TOP,

	DC_LINE_SIZE,
	DC_GFX_PITCH,
	DC_VID_YUV_PITCH,
	DC_RSVD_1,

	DC_H_ACTIVE_TIMING,
	DC_H_BLANK_TIMING,
	DC_H_SYNC_TIMING,
	DC_RSVD_2,

	DC_V_ACTIVE_TIMING,
	DC_V_BLANK_TIMING,
	DC_V_SYNC_TIMING,
	DC_FB_ACTIVE,

	DC_CURSOR_X,
	DC_CURSOR_Y,
	DC_RSVD_3,
	DC_LINE_CNT,

	DC_PAL_ADDRESS,
	DC_PAL_DATA,
	DC_DFIFO_DIAG,
	DC_CFIFO_DIAG,

	DC_VID_DS_DELTA,
	DC_GLIU0_MEM_OFFSET,
	DC_DV_CTL,
	DC_DV_ACCESS,

	DC_GFX_SCALE,
	DC_IRQ_FILT_CTL,
	DC_FILT_COEFF1,
	DC_FILT_COEFF2,

	DC_VBI_EVEN_CTL,
	DC_VBI_ODD_CTL,
	DC_VBI_HOR,
	DC_VBI_LN_ODD,

	DC_VBI_LN_EVEN,
	DC_VBI_PITCH,
	DC_CLR_KEY,
	DC_CLR_KEY_MASK,

	DC_CLR_KEY_X,
	DC_CLR_KEY_Y,
	DC_IRQ,
	DC_RSVD_4,

	DC_RSVD_5,
	DC_GENLK_CTL,
	DC_VID_EVEN_Y_ST_OFFSET,
	DC_VID_EVEN_U_ST_OFFSET,

	DC_VID_EVEN_V_ST_OFFSET,
	DC_V_ACTIVE_EVEN_TIMING,
	DC_V_BLANK_EVEN_TIMING,
	DC_V_SYNC_EVEN_TIMING,	/* 0xec */
पूर्ण;

#घोषणा DC_UNLOCK_LOCK			0x00000000
#घोषणा DC_UNLOCK_UNLOCK		0x00004758	/* magic value */

#घोषणा DC_GENERAL_CFG_FDTY		(1 << 17)
#घोषणा DC_GENERAL_CFG_DFHPEL_SHIFT	(12)
#घोषणा DC_GENERAL_CFG_DFHPSL_SHIFT	(8)
#घोषणा DC_GENERAL_CFG_VGAE		(1 << 7)
#घोषणा DC_GENERAL_CFG_DECE		(1 << 6)
#घोषणा DC_GENERAL_CFG_CMPE		(1 << 5)
#घोषणा DC_GENERAL_CFG_VIDE		(1 << 3)
#घोषणा DC_GENERAL_CFG_DFLE		(1 << 0)

#घोषणा DC_DISPLAY_CFG_VISL		(1 << 27)
#घोषणा DC_DISPLAY_CFG_PALB		(1 << 25)
#घोषणा DC_DISPLAY_CFG_DCEN		(1 << 24)
#घोषणा DC_DISPLAY_CFG_DISP_MODE_24BPP	(1 << 9)
#घोषणा DC_DISPLAY_CFG_DISP_MODE_16BPP	(1 << 8)
#घोषणा DC_DISPLAY_CFG_DISP_MODE_8BPP	(0)
#घोषणा DC_DISPLAY_CFG_TRUP		(1 << 6)
#घोषणा DC_DISPLAY_CFG_VDEN		(1 << 4)
#घोषणा DC_DISPLAY_CFG_GDEN		(1 << 3)
#घोषणा DC_DISPLAY_CFG_TGEN		(1 << 0)

#घोषणा DC_DV_TOP_DV_TOP_EN		(1 << 0)

#घोषणा DC_DV_CTL_DV_LINE_SIZE		((1 << 10) | (1 << 11))
#घोषणा DC_DV_CTL_DV_LINE_SIZE_1K	(0)
#घोषणा DC_DV_CTL_DV_LINE_SIZE_2K	(1 << 10)
#घोषणा DC_DV_CTL_DV_LINE_SIZE_4K	(1 << 11)
#घोषणा DC_DV_CTL_DV_LINE_SIZE_8K	((1 << 10) | (1 << 11))
#घोषणा DC_DV_CTL_CLEAR_DV_RAM		(1 << 0)

#घोषणा DC_IRQ_FILT_CTL_H_FILT_SEL	(1 << 10)

#घोषणा DC_CLR_KEY_CLR_KEY_EN		(1 << 24)

#घोषणा DC_IRQ_VIP_VSYNC_IRQ_STATUS	(1 << 21)	/* unकरोcumented? */
#घोषणा DC_IRQ_STATUS			(1 << 20)	/* unकरोcumented? */
#घोषणा DC_IRQ_VIP_VSYNC_LOSS_IRQ_MASK	(1 << 1)
#घोषणा DC_IRQ_MASK			(1 << 0)

#घोषणा DC_GENLK_CTL_FLICK_SEL_MASK	(0x0F << 28)
#घोषणा DC_GENLK_CTL_ALPHA_FLICK_EN	(1 << 25)
#घोषणा DC_GENLK_CTL_FLICK_EN		(1 << 24)
#घोषणा DC_GENLK_CTL_GENLK_EN		(1 << 18)


/*
 * Video Processor रेजिस्टरs (table 6-71).
 * There is space क्रम 64 bit values, but we never use more than the
 * lower 32 bits.  The actual रेजिस्टर save/restore code only bothers
 * to restore those 32 bits.
 */
क्रमागत vp_रेजिस्टरs अणु
	VP_VCFG = 0,
	VP_DCFG,

	VP_VX,
	VP_VY,

	VP_SCL,
	VP_VCK,

	VP_VCM,
	VP_PAR,

	VP_PDR,
	VP_SLR,

	VP_MISC,
	VP_CCS,

	VP_VYS,
	VP_VXS,

	VP_RSVD_0,
	VP_VDC,

	VP_RSVD_1,
	VP_CRC,

	VP_CRC32,
	VP_VDE,

	VP_CCK,
	VP_CCM,

	VP_CC1,
	VP_CC2,

	VP_A1X,
	VP_A1Y,

	VP_A1C,
	VP_A1T,

	VP_A2X,
	VP_A2Y,

	VP_A2C,
	VP_A2T,

	VP_A3X,
	VP_A3Y,

	VP_A3C,
	VP_A3T,

	VP_VRR,
	VP_AWT,

	VP_VTM,
	VP_VYE,

	VP_A1YE,
	VP_A2YE,

	VP_A3YE,	/* 0x150 */

	VP_VCR = 0x1000, /* 0x1000 - 0x1fff */
पूर्ण;

#घोषणा VP_VCFG_VID_EN			(1 << 0)

#घोषणा VP_DCFG_GV_GAM			(1 << 21)
#घोषणा VP_DCFG_PWR_SEQ_DELAY		((1 << 17) | (1 << 18) | (1 << 19))
#घोषणा VP_DCFG_PWR_SEQ_DELAY_DEFAULT	(1 << 19)	/* unकरोcumented */
#घोषणा VP_DCFG_CRT_SYNC_SKW		((1 << 14) | (1 << 15) | (1 << 16))
#घोषणा VP_DCFG_CRT_SYNC_SKW_DEFAULT	(1 << 16)
#घोषणा VP_DCFG_CRT_VSYNC_POL		(1 << 9)
#घोषणा VP_DCFG_CRT_HSYNC_POL		(1 << 8)
#घोषणा VP_DCFG_DAC_BL_EN		(1 << 3)
#घोषणा VP_DCFG_VSYNC_EN		(1 << 2)
#घोषणा VP_DCFG_HSYNC_EN		(1 << 1)
#घोषणा VP_DCFG_CRT_EN			(1 << 0)

#घोषणा VP_MISC_APWRDN			(1 << 11)
#घोषणा VP_MISC_DACPWRDN		(1 << 10)
#घोषणा VP_MISC_BYP_BOTH		(1 << 0)


/*
 * Flat Panel रेजिस्टरs (table 6-71).
 * Also 64 bit रेजिस्टरs; see above note about 32-bit handling.
 */

/* we're actually in the VP रेजिस्टर space, starting at address 0x400 */
#घोषणा VP_FP_START	0x400

क्रमागत fp_रेजिस्टरs अणु
	FP_PT1 = 0,
	FP_PT2,

	FP_PM,
	FP_DFC,

	FP_RSVD_0,
	FP_RSVD_1,

	FP_RSVD_2,
	FP_RSVD_3,

	FP_RSVD_4,
	FP_DCA,

	FP_DMD,
	FP_CRC, /* 0x458 */
पूर्ण;

#घोषणा FP_PT2_HSP			(1 << 22)
#घोषणा FP_PT2_VSP			(1 << 23)
#घोषणा FP_PT2_SCRC			(1 << 27)	/* shfclk मुक्त */

#घोषणा FP_PM_P				(1 << 24)	/* panel घातer ctl */
#घोषणा FP_PM_PANEL_PWR_UP		(1 << 3)	/* r/o */
#घोषणा FP_PM_PANEL_PWR_DOWN		(1 << 2)	/* r/o */
#घोषणा FP_PM_PANEL_OFF			(1 << 1)	/* r/o */
#घोषणा FP_PM_PANEL_ON			(1 << 0)	/* r/o */

#घोषणा FP_DFC_BC			((1 << 4) | (1 << 5) | (1 << 6))


/* रेजिस्टर access functions */

अटल अंतरभूत uपूर्णांक32_t पढ़ो_gp(काष्ठा lxfb_par *par, पूर्णांक reg)
अणु
	वापस पढ़ोl(par->gp_regs + 4*reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_gp(काष्ठा lxfb_par *par, पूर्णांक reg, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, par->gp_regs + 4*reg);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t पढ़ो_dc(काष्ठा lxfb_par *par, पूर्णांक reg)
अणु
	वापस पढ़ोl(par->dc_regs + 4*reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_dc(काष्ठा lxfb_par *par, पूर्णांक reg, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, par->dc_regs + 4*reg);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t पढ़ो_vp(काष्ठा lxfb_par *par, पूर्णांक reg)
अणु
	वापस पढ़ोl(par->vp_regs + 8*reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_vp(काष्ठा lxfb_par *par, पूर्णांक reg, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, par->vp_regs + 8*reg);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t पढ़ो_fp(काष्ठा lxfb_par *par, पूर्णांक reg)
अणु
	वापस पढ़ोl(par->vp_regs + 8*reg + VP_FP_START);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_fp(काष्ठा lxfb_par *par, पूर्णांक reg, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, par->vp_regs + 8*reg + VP_FP_START);
पूर्ण


/* MSRs are defined in linux/cs5535.h; their bitfields are here */

#घोषणा MSR_GLCP_DOTPLL_LOCK		(1 << 25)	/* r/o */
#घोषणा MSR_GLCP_DOTPLL_HALFPIX		(1 << 24)
#घोषणा MSR_GLCP_DOTPLL_BYPASS		(1 << 15)
#घोषणा MSR_GLCP_DOTPLL_DOTRESET	(1 << 0)

/* note: this is actually the VP's GLD_MSR_CONFIG */
#घोषणा MSR_LX_GLD_MSR_CONFIG_FMT	((1 << 3) | (1 << 4) | (1 << 5))
#घोषणा MSR_LX_GLD_MSR_CONFIG_FMT_FP	(1 << 3)
#घोषणा MSR_LX_GLD_MSR_CONFIG_FMT_CRT	(0)
#घोषणा MSR_LX_GLD_MSR_CONFIG_FPC	(1 << 15)	/* FP *and* CRT */

#घोषणा MSR_LX_MSR_PADSEL_TFT_SEL_LOW	0xDFFFFFFF	/* ??? */
#घोषणा MSR_LX_MSR_PADSEL_TFT_SEL_HIGH	0x0000003F	/* ??? */

#घोषणा MSR_LX_SPARE_MSR_DIS_CFIFO_HGO	(1 << 11)	/* unकरोcumented */
#घोषणा MSR_LX_SPARE_MSR_VFIFO_ARB_SEL	(1 << 10)	/* unकरोcumented */
#घोषणा MSR_LX_SPARE_MSR_WM_LPEN_OVRD	(1 << 9)	/* unकरोcumented */
#घोषणा MSR_LX_SPARE_MSR_LOAD_WM_LPEN_M	(1 << 8)	/* unकरोcumented */
#घोषणा MSR_LX_SPARE_MSR_DIS_INIT_V_PRI	(1 << 7)	/* unकरोcumented */
#घोषणा MSR_LX_SPARE_MSR_DIS_VIFO_WM	(1 << 6)
#घोषणा MSR_LX_SPARE_MSR_DIS_CWD_CHECK	(1 << 5)	/* unकरोcumented */
#घोषणा MSR_LX_SPARE_MSR_PIX8_PAN_FIX	(1 << 4)	/* unकरोcumented */
#घोषणा MSR_LX_SPARE_MSR_FIRST_REQ_MASK	(1 << 1)	/* unकरोcumented */

#पूर्ण_अगर
