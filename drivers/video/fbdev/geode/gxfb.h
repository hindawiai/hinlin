<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2008 Andres Salomon <dilinger@debian.org>
 *
 * Geode GX2 header inक्रमmation
 */
#अगर_अघोषित _GXFB_H_
#घोषणा _GXFB_H_

#समावेश <linux/पन.स>

#घोषणा GP_REG_COUNT   (0x50 / 4)
#घोषणा DC_REG_COUNT   (0x90 / 4)
#घोषणा VP_REG_COUNT   (0x138 / 8)
#घोषणा FP_REG_COUNT   (0x68 / 8)

#घोषणा DC_PAL_COUNT   0x104

काष्ठा gxfb_par अणु
	पूर्णांक enable_crt;
	व्योम __iomem *dc_regs;
	व्योम __iomem *vid_regs;
	व्योम __iomem *gp_regs;
	पूर्णांक घातered_करोwn;

	/* रेजिस्टर state, क्रम घातer management functionality */
	काष्ठा अणु
		uपूर्णांक64_t padsel;
		uपूर्णांक64_t करोtpll;
	पूर्ण msr;

	uपूर्णांक32_t gp[GP_REG_COUNT];
	uपूर्णांक32_t dc[DC_REG_COUNT];
	uपूर्णांक64_t vp[VP_REG_COUNT];
	uपूर्णांक64_t fp[FP_REG_COUNT];

	uपूर्णांक32_t pal[DC_PAL_COUNT];
पूर्ण;

अचिन्हित पूर्णांक gx_frame_buffer_size(व्योम);
पूर्णांक gx_line_delta(पूर्णांक xres, पूर्णांक bpp);
व्योम gx_set_mode(काष्ठा fb_info *info);
व्योम gx_set_hw_palette_reg(काष्ठा fb_info *info, अचिन्हित regno,
		अचिन्हित red, अचिन्हित green, अचिन्हित blue);

व्योम gx_set_dclk_frequency(काष्ठा fb_info *info);
व्योम gx_configure_display(काष्ठा fb_info *info);
पूर्णांक gx_blank_display(काष्ठा fb_info *info, पूर्णांक blank_mode);

पूर्णांक gx_घातerकरोwn(काष्ठा fb_info *info);
पूर्णांक gx_घातerup(काष्ठा fb_info *info);

/* Graphics Processor रेजिस्टरs (table 6-23 from the data book) */
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
	GP_BASE_OFFSET, /* 0x4c */
पूर्ण;

#घोषणा GP_BLT_STATUS_BLT_PENDING	(1 << 2)
#घोषणा GP_BLT_STATUS_BLT_BUSY		(1 << 0)


/* Display Controller रेजिस्टरs (table 6-38 from the data book) */
क्रमागत dc_रेजिस्टरs अणु
	DC_UNLOCK = 0,
	DC_GENERAL_CFG,
	DC_DISPLAY_CFG,
	DC_RSVD_0,

	DC_FB_ST_OFFSET,
	DC_CB_ST_OFFSET,
	DC_CURS_ST_OFFSET,
	DC_ICON_ST_OFFSET,

	DC_VID_Y_ST_OFFSET,
	DC_VID_U_ST_OFFSET,
	DC_VID_V_ST_OFFSET,
	DC_RSVD_1,

	DC_LINE_SIZE,
	DC_GFX_PITCH,
	DC_VID_YUV_PITCH,
	DC_RSVD_2,

	DC_H_ACTIVE_TIMING,
	DC_H_BLANK_TIMING,
	DC_H_SYNC_TIMING,
	DC_RSVD_3,

	DC_V_ACTIVE_TIMING,
	DC_V_BLANK_TIMING,
	DC_V_SYNC_TIMING,
	DC_RSVD_4,

	DC_CURSOR_X,
	DC_CURSOR_Y,
	DC_ICON_X,
	DC_LINE_CNT,

	DC_PAL_ADDRESS,
	DC_PAL_DATA,
	DC_DFIFO_DIAG,
	DC_CFIFO_DIAG,

	DC_VID_DS_DELTA,
	DC_GLIU0_MEM_OFFSET,
	DC_RSVD_5,
	DC_DV_ACC, /* 0x8c */
पूर्ण;

#घोषणा DC_UNLOCK_LOCK			0x00000000
#घोषणा DC_UNLOCK_UNLOCK		0x00004758	/* magic value */

#घोषणा DC_GENERAL_CFG_YUVM		(1 << 20)
#घोषणा DC_GENERAL_CFG_VDSE		(1 << 19)
#घोषणा DC_GENERAL_CFG_DFHPEL_SHIFT	12
#घोषणा DC_GENERAL_CFG_DFHPSL_SHIFT	8
#घोषणा DC_GENERAL_CFG_DECE		(1 << 6)
#घोषणा DC_GENERAL_CFG_CMPE		(1 << 5)
#घोषणा DC_GENERAL_CFG_VIDE		(1 << 3)
#घोषणा DC_GENERAL_CFG_ICNE		(1 << 2)
#घोषणा DC_GENERAL_CFG_CURE		(1 << 1)
#घोषणा DC_GENERAL_CFG_DFLE		(1 << 0)

#घोषणा DC_DISPLAY_CFG_A20M		(1 << 31)
#घोषणा DC_DISPLAY_CFG_A18M		(1 << 30)
#घोषणा DC_DISPLAY_CFG_PALB		(1 << 25)
#घोषणा DC_DISPLAY_CFG_DISP_MODE_24BPP	(1 << 9)
#घोषणा DC_DISPLAY_CFG_DISP_MODE_16BPP	(1 << 8)
#घोषणा DC_DISPLAY_CFG_DISP_MODE_8BPP	(0)
#घोषणा DC_DISPLAY_CFG_VDEN		(1 << 4)
#घोषणा DC_DISPLAY_CFG_GDEN		(1 << 3)
#घोषणा DC_DISPLAY_CFG_TGEN		(1 << 0)


/*
 * Video Processor रेजिस्टरs (table 6-54).
 * There is space क्रम 64 bit values, but we never use more than the
 * lower 32 bits.  The actual रेजिस्टर save/restore code only bothers
 * to restore those 32 bits.
 */
क्रमागत vp_रेजिस्टरs अणु
	VP_VCFG = 0,
	VP_DCFG,

	VP_VX,
	VP_VY,

	VP_VS,
	VP_VCK,

	VP_VCM,
	VP_GAR,

	VP_GDR,
	VP_RSVD_0,

	VP_MISC,
	VP_CCS,

	VP_RSVD_1,
	VP_RSVD_2,

	VP_RSVD_3,
	VP_VDC,

	VP_VCO,
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

	VP_VTM, /* 0x130 */
पूर्ण;

#घोषणा VP_VCFG_VID_EN			(1 << 0)

#घोषणा VP_DCFG_DAC_VREF		(1 << 26)
#घोषणा VP_DCFG_GV_GAM			(1 << 21)
#घोषणा VP_DCFG_VG_CK			(1 << 20)
#घोषणा VP_DCFG_CRT_SYNC_SKW_DEFAULT	(1 << 16)
#घोषणा VP_DCFG_CRT_SYNC_SKW		((1 << 14) | (1 << 15) | (1 << 16))
#घोषणा VP_DCFG_CRT_VSYNC_POL		(1 << 9)
#घोषणा VP_DCFG_CRT_HSYNC_POL		(1 << 8)
#घोषणा VP_DCFG_FP_DATA_EN		(1 << 7)	/* unकरोcumented */
#घोषणा VP_DCFG_FP_PWR_EN		(1 << 6)	/* unकरोcumented */
#घोषणा VP_DCFG_DAC_BL_EN		(1 << 3)
#घोषणा VP_DCFG_VSYNC_EN		(1 << 2)
#घोषणा VP_DCFG_HSYNC_EN		(1 << 1)
#घोषणा VP_DCFG_CRT_EN			(1 << 0)

#घोषणा VP_MISC_GAM_EN			(1 << 0)
#घोषणा VP_MISC_DACPWRDN		(1 << 10)
#घोषणा VP_MISC_APWRDN			(1 << 11)


/*
 * Flat Panel रेजिस्टरs (table 6-55).
 * Also 64 bit रेजिस्टरs; see above note about 32-bit handling.
 */

/* we're actually in the VP रेजिस्टर space, starting at address 0x400 */
#घोषणा VP_FP_START		0x400

क्रमागत fp_रेजिस्टरs अणु
	FP_PT1 = 0,
	FP_PT2,

	FP_PM,
	FP_DFC,

	FP_BLFSR,
	FP_RLFSR,

	FP_FMI,
	FP_FMD,

	FP_RSVD_0,
	FP_DCA,

	FP_DMD,
	FP_CRC,

	FP_FBB, /* 0x460 */
पूर्ण;

#घोषणा FP_PT1_VSIZE_SHIFT		16		/* unकरोcumented? */
#घोषणा FP_PT1_VSIZE_MASK		0x7FF0000	/* unकरोcumented? */

#घोषणा FP_PT2_HSP			(1 << 22)
#घोषणा FP_PT2_VSP			(1 << 23)

#घोषणा FP_PM_P				(1 << 24)       /* panel घातer on */
#घोषणा FP_PM_PANEL_PWR_UP		(1 << 3)        /* r/o */
#घोषणा FP_PM_PANEL_PWR_DOWN		(1 << 2)        /* r/o */
#घोषणा FP_PM_PANEL_OFF			(1 << 1)        /* r/o */
#घोषणा FP_PM_PANEL_ON			(1 << 0)        /* r/o */

#घोषणा FP_DFC_NFI			((1 << 4) | (1 << 5) | (1 << 6))


/* रेजिस्टर access functions */

अटल अंतरभूत uपूर्णांक32_t पढ़ो_gp(काष्ठा gxfb_par *par, पूर्णांक reg)
अणु
	वापस पढ़ोl(par->gp_regs + 4*reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_gp(काष्ठा gxfb_par *par, पूर्णांक reg, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, par->gp_regs + 4*reg);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t पढ़ो_dc(काष्ठा gxfb_par *par, पूर्णांक reg)
अणु
	वापस पढ़ोl(par->dc_regs + 4*reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_dc(काष्ठा gxfb_par *par, पूर्णांक reg, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, par->dc_regs + 4*reg);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t पढ़ो_vp(काष्ठा gxfb_par *par, पूर्णांक reg)
अणु
	वापस पढ़ोl(par->vid_regs + 8*reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_vp(काष्ठा gxfb_par *par, पूर्णांक reg, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, par->vid_regs + 8*reg);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t पढ़ो_fp(काष्ठा gxfb_par *par, पूर्णांक reg)
अणु
	वापस पढ़ोl(par->vid_regs + 8*reg + VP_FP_START);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_fp(काष्ठा gxfb_par *par, पूर्णांक reg, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, par->vid_regs + 8*reg + VP_FP_START);
पूर्ण


/* MSRs are defined in linux/cs5535.h; their bitfields are here */

#घोषणा MSR_GLCP_SYS_RSTPLL_DOTPOSTDIV3	(1 << 3)
#घोषणा MSR_GLCP_SYS_RSTPLL_DOTPREMULT2	(1 << 2)
#घोषणा MSR_GLCP_SYS_RSTPLL_DOTPREDIV2	(1 << 1)

#घोषणा MSR_GLCP_DOTPLL_LOCK		(1 << 25)	/* r/o */
#घोषणा MSR_GLCP_DOTPLL_BYPASS		(1 << 15)
#घोषणा MSR_GLCP_DOTPLL_DOTRESET	(1 << 0)

#घोषणा MSR_GX_MSR_PADSEL_MASK		0x3FFFFFFF	/* unकरोcumented? */
#घोषणा MSR_GX_MSR_PADSEL_TFT		0x1FFFFFFF	/* unकरोcumented? */

#घोषणा MSR_GX_GLD_MSR_CONFIG_FP	(1 << 3)

#पूर्ण_अगर
