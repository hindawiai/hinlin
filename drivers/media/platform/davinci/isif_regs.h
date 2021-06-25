<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2008-2009 Texas Instruments Inc
 */
#अगर_अघोषित _ISIF_REGS_H
#घोषणा _ISIF_REGS_H

/* ISIF रेजिस्टरs relative offsets */
#घोषणा SYNCEN					0x00
#घोषणा MODESET					0x04
#घोषणा HDW					0x08
#घोषणा VDW					0x0c
#घोषणा PPLN					0x10
#घोषणा LPFR					0x14
#घोषणा SPH					0x18
#घोषणा LNH					0x1c
#घोषणा SLV0					0x20
#घोषणा SLV1					0x24
#घोषणा LNV					0x28
#घोषणा CULH					0x2c
#घोषणा CULV					0x30
#घोषणा HSIZE					0x34
#घोषणा SDOFST					0x38
#घोषणा CADU					0x3c
#घोषणा CADL					0x40
#घोषणा LINCFG0					0x44
#घोषणा LINCFG1					0x48
#घोषणा CCOLP					0x4c
#घोषणा CRGAIN					0x50
#घोषणा CGRGAIN					0x54
#घोषणा CGBGAIN					0x58
#घोषणा CBGAIN					0x5c
#घोषणा COFSTA					0x60
#घोषणा FLSHCFG0				0x64
#घोषणा FLSHCFG1				0x68
#घोषणा FLSHCFG2				0x6c
#घोषणा VDINT0					0x70
#घोषणा VDINT1					0x74
#घोषणा VDINT2					0x78
#घोषणा MISC					0x7c
#घोषणा CGAMMAWD				0x80
#घोषणा REC656IF				0x84
#घोषणा CCDCFG					0x88
/*****************************************************
* Defect Correction रेजिस्टरs
*****************************************************/
#घोषणा DFCCTL					0x8c
#घोषणा VDFSATLV				0x90
#घोषणा DFCMEMCTL				0x94
#घोषणा DFCMEM0					0x98
#घोषणा DFCMEM1					0x9c
#घोषणा DFCMEM2					0xa0
#घोषणा DFCMEM3					0xa4
#घोषणा DFCMEM4					0xa8
/****************************************************
* Black Clamp रेजिस्टरs
****************************************************/
#घोषणा CLAMPCFG				0xac
#घोषणा CLDCOFST				0xb0
#घोषणा CLSV					0xb4
#घोषणा CLHWIN0					0xb8
#घोषणा CLHWIN1					0xbc
#घोषणा CLHWIN2					0xc0
#घोषणा CLVRV					0xc4
#घोषणा CLVWIN0					0xc8
#घोषणा CLVWIN1					0xcc
#घोषणा CLVWIN2					0xd0
#घोषणा CLVWIN3					0xd4
/****************************************************
* Lense Shading Correction
****************************************************/
#घोषणा DATAHOFST				0xd8
#घोषणा DATAVOFST				0xdc
#घोषणा LSCHVAL					0xe0
#घोषणा LSCVVAL					0xe4
#घोषणा TWODLSCCFG				0xe8
#घोषणा TWODLSCOFST				0xec
#घोषणा TWODLSCINI				0xf0
#घोषणा TWODLSCGRBU				0xf4
#घोषणा TWODLSCGRBL				0xf8
#घोषणा TWODLSCGROF				0xfc
#घोषणा TWODLSCORBU				0x100
#घोषणा TWODLSCORBL				0x104
#घोषणा TWODLSCOROF				0x108
#घोषणा TWODLSCIRQEN				0x10c
#घोषणा TWODLSCIRQST				0x110
/****************************************************
* Data क्रमmatter
****************************************************/
#घोषणा FMTCFG					0x114
#घोषणा FMTPLEN					0x118
#घोषणा FMTSPH					0x11c
#घोषणा FMTLNH					0x120
#घोषणा FMTSLV					0x124
#घोषणा FMTLNV					0x128
#घोषणा FMTRLEN					0x12c
#घोषणा FMTHCNT					0x130
#घोषणा FMTAPTR_BASE				0x134
/* Below macro क्रम addresses FMTAPTR0 - FMTAPTR15 */
#घोषणा FMTAPTR(i)			(FMTAPTR_BASE + (i * 4))
#घोषणा FMTPGMVF0				0x174
#घोषणा FMTPGMVF1				0x178
#घोषणा FMTPGMAPU0				0x17c
#घोषणा FMTPGMAPU1				0x180
#घोषणा FMTPGMAPS0				0x184
#घोषणा FMTPGMAPS1				0x188
#घोषणा FMTPGMAPS2				0x18c
#घोषणा FMTPGMAPS3				0x190
#घोषणा FMTPGMAPS4				0x194
#घोषणा FMTPGMAPS5				0x198
#घोषणा FMTPGMAPS6				0x19c
#घोषणा FMTPGMAPS7				0x1a0
/************************************************
* Color Space Converter
************************************************/
#घोषणा CSCCTL					0x1a4
#घोषणा CSCM0					0x1a8
#घोषणा CSCM1					0x1ac
#घोषणा CSCM2					0x1b0
#घोषणा CSCM3					0x1b4
#घोषणा CSCM4					0x1b8
#घोषणा CSCM5					0x1bc
#घोषणा CSCM6					0x1c0
#घोषणा CSCM7					0x1c4
#घोषणा OBWIN0					0x1c8
#घोषणा OBWIN1					0x1cc
#घोषणा OBWIN2					0x1d0
#घोषणा OBWIN3					0x1d4
#घोषणा OBVAL0					0x1d8
#घोषणा OBVAL1					0x1dc
#घोषणा OBVAL2					0x1e0
#घोषणा OBVAL3					0x1e4
#घोषणा OBVAL4					0x1e8
#घोषणा OBVAL5					0x1ec
#घोषणा OBVAL6					0x1f0
#घोषणा OBVAL7					0x1f4
#घोषणा CLKCTL					0x1f8

/* Masks & Shअगरts below */
#घोषणा START_PX_HOR_MASK			0x7FFF
#घोषणा NUM_PX_HOR_MASK				0x7FFF
#घोषणा START_VER_ONE_MASK			0x7FFF
#घोषणा START_VER_TWO_MASK			0x7FFF
#घोषणा NUM_LINES_VER				0x7FFF

/* gain - offset masks */
#घोषणा GAIN_INTEGER_SHIFT			9
#घोषणा OFFSET_MASK				0xFFF
#घोषणा GAIN_SDRAM_EN_SHIFT			12
#घोषणा GAIN_IPIPE_EN_SHIFT			13
#घोषणा GAIN_H3A_EN_SHIFT			14
#घोषणा OFST_SDRAM_EN_SHIFT			8
#घोषणा OFST_IPIPE_EN_SHIFT			9
#घोषणा OFST_H3A_EN_SHIFT			10
#घोषणा GAIN_OFFSET_EN_MASK			0x7700

/* Culling */
#घोषणा CULL_PAT_EVEN_LINE_SHIFT		8

/* CCDCFG रेजिस्टर */
#घोषणा ISIF_YCINSWP_RAW			(0x00 << 4)
#घोषणा ISIF_YCINSWP_YCBCR			(0x01 << 4)
#घोषणा ISIF_CCDCFG_FIDMD_LATCH_VSYNC		(0x00 << 6)
#घोषणा ISIF_CCDCFG_WENLOG_AND			(0x00 << 8)
#घोषणा ISIF_CCDCFG_TRGSEL_WEN			(0x00 << 9)
#घोषणा ISIF_CCDCFG_EXTRG_DISABLE		(0x00 << 10)
#घोषणा ISIF_LATCH_ON_VSYNC_DISABLE		(0x01 << 15)
#घोषणा ISIF_LATCH_ON_VSYNC_ENABLE		(0x00 << 15)
#घोषणा ISIF_DATA_PACK_MASK			3
#घोषणा ISIF_DATA_PACK16			0
#घोषणा ISIF_DATA_PACK12			1
#घोषणा ISIF_DATA_PACK8				2
#घोषणा ISIF_PIX_ORDER_SHIFT			11
#घोषणा ISIF_BW656_ENABLE			(0x01 << 5)

/* MODESET रेजिस्टरs */
#घोषणा ISIF_VDHDOUT_INPUT			(0x00 << 0)
#घोषणा ISIF_INPUT_SHIFT			12
#घोषणा ISIF_RAW_INPUT_MODE			0
#घोषणा ISIF_FID_POL_SHIFT			4
#घोषणा ISIF_HD_POL_SHIFT			3
#घोषणा ISIF_VD_POL_SHIFT			2
#घोषणा ISIF_DATAPOL_NORMAL			0
#घोषणा ISIF_DATAPOL_SHIFT			6
#घोषणा ISIF_EXWEN_DISABLE			0
#घोषणा ISIF_EXWEN_SHIFT			5
#घोषणा ISIF_FRM_FMT_SHIFT			7
#घोषणा ISIF_DATASFT_SHIFT			8
#घोषणा ISIF_LPF_SHIFT				14
#घोषणा ISIF_LPF_MASK				1

/* GAMMAWD रेजिस्टरs */
#घोषणा ISIF_ALAW_GAMMA_WD_MASK			0xF
#घोषणा ISIF_ALAW_GAMMA_WD_SHIFT		1
#घोषणा ISIF_ALAW_ENABLE			1
#घोषणा ISIF_GAMMAWD_CFA_SHIFT			5

/* HSIZE रेजिस्टरs */
#घोषणा ISIF_HSIZE_FLIP_MASK			1
#घोषणा ISIF_HSIZE_FLIP_SHIFT			12

/* MISC रेजिस्टरs */
#घोषणा ISIF_DPCM_EN_SHIFT			12
#घोषणा ISIF_DPCM_PREDICTOR_SHIFT		13

/* Black clamp related */
#घोषणा ISIF_BC_MODE_COLOR_SHIFT		4
#घोषणा ISIF_HORZ_BC_MODE_SHIFT			1
#घोषणा ISIF_HORZ_BC_WIN_SEL_SHIFT		5
#घोषणा ISIF_HORZ_BC_PIX_LIMIT_SHIFT		6
#घोषणा ISIF_HORZ_BC_WIN_H_SIZE_SHIFT		8
#घोषणा ISIF_HORZ_BC_WIN_V_SIZE_SHIFT		12
#घोषणा	ISIF_VERT_BC_RST_VAL_SEL_SHIFT		4
#घोषणा ISIF_VERT_BC_LINE_AVE_COEF_SHIFT	8

/* VDFC रेजिस्टरs */
#घोषणा ISIF_VDFC_EN_SHIFT			4
#घोषणा ISIF_VDFC_CORR_MOD_SHIFT		5
#घोषणा ISIF_VDFC_CORR_WHOLE_LN_SHIFT		7
#घोषणा ISIF_VDFC_LEVEL_SHFT_SHIFT		8
#घोषणा ISIF_VDFC_POS_MASK			0x1FFF
#घोषणा ISIF_DFCMEMCTL_DFCMARST_SHIFT		2

/* CSC रेजिस्टरs */
#घोषणा ISIF_CSC_COEF_INTEG_MASK		7
#घोषणा ISIF_CSC_COEF_DECIMAL_MASK		0x1f
#घोषणा ISIF_CSC_COEF_INTEG_SHIFT		5
#घोषणा ISIF_CSCM_MSB_SHIFT			8
#घोषणा ISIF_DF_CSC_SPH_MASK			0x1FFF
#घोषणा ISIF_DF_CSC_LNH_MASK			0x1FFF
#घोषणा ISIF_DF_CSC_SLV_MASK			0x1FFF
#घोषणा ISIF_DF_CSC_LNV_MASK			0x1FFF
#घोषणा ISIF_DF_NUMLINES			0x7FFF
#घोषणा ISIF_DF_NUMPIX				0x1FFF

/* Offsets क्रम LSC/DFC/Gain */
#घोषणा ISIF_DATA_H_OFFSET_MASK			0x1FFF
#घोषणा ISIF_DATA_V_OFFSET_MASK			0x1FFF

/* Linearization */
#घोषणा ISIF_LIN_CORRSFT_SHIFT			4
#घोषणा ISIF_LIN_SCALE_FACT_INTEG_SHIFT		10


/* Pattern रेजिस्टरs */
#घोषणा ISIF_PG_EN				(1 << 3)
#घोषणा ISIF_SEL_PG_SRC				(3 << 4)
#घोषणा ISIF_PG_VD_POL_SHIFT			0
#घोषणा ISIF_PG_HD_POL_SHIFT			1

/*अक्रमom other junk*/
#घोषणा ISIF_SYNCEN_VDHDEN_MASK			(1 << 0)
#घोषणा ISIF_SYNCEN_WEN_MASK			(1 << 1)
#घोषणा ISIF_SYNCEN_WEN_SHIFT			1

#पूर्ण_अगर
