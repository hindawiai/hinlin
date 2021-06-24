<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2005-2009 Texas Instruments Inc
 */
#अगर_अघोषित _DM355_CCDC_REGS_H
#घोषणा _DM355_CCDC_REGS_H

/**************************************************************************\
* Register OFFSET Definitions
\**************************************************************************/
#घोषणा SYNCEN				0x00
#घोषणा MODESET				0x04
#घोषणा HDWIDTH				0x08
#घोषणा VDWIDTH				0x0c
#घोषणा PPLN				0x10
#घोषणा LPFR				0x14
#घोषणा SPH				0x18
#घोषणा NPH				0x1c
#घोषणा SLV0				0x20
#घोषणा SLV1				0x24
#घोषणा NLV				0x28
#घोषणा CULH				0x2c
#घोषणा CULV				0x30
#घोषणा HSIZE				0x34
#घोषणा SDOFST				0x38
#घोषणा STADRH				0x3c
#घोषणा STADRL				0x40
#घोषणा CLAMP				0x44
#घोषणा DCSUB				0x48
#घोषणा COLPTN				0x4c
#घोषणा BLKCMP0				0x50
#घोषणा BLKCMP1				0x54
#घोषणा MEDFILT				0x58
#घोषणा RYEGAIN				0x5c
#घोषणा GRCYGAIN			0x60
#घोषणा GBGGAIN				0x64
#घोषणा BMGGAIN				0x68
#घोषणा OFFSET				0x6c
#घोषणा OUTCLIP				0x70
#घोषणा VDINT0				0x74
#घोषणा VDINT1				0x78
#घोषणा RSV0				0x7c
#घोषणा GAMMAWD				0x80
#घोषणा REC656IF			0x84
#घोषणा CCDCFG				0x88
#घोषणा FMTCFG				0x8c
#घोषणा FMTPLEN				0x90
#घोषणा FMTSPH				0x94
#घोषणा FMTLNH				0x98
#घोषणा FMTSLV				0x9c
#घोषणा FMTLNV				0xa0
#घोषणा FMTRLEN				0xa4
#घोषणा FMTHCNT				0xa8
#घोषणा FMT_ADDR_PTR_B			0xac
#घोषणा FMT_ADDR_PTR(i)			(FMT_ADDR_PTR_B + (i * 4))
#घोषणा FMTPGM_VF0			0xcc
#घोषणा FMTPGM_VF1			0xd0
#घोषणा FMTPGM_AP0			0xd4
#घोषणा FMTPGM_AP1			0xd8
#घोषणा FMTPGM_AP2			0xdc
#घोषणा FMTPGM_AP3                      0xe0
#घोषणा FMTPGM_AP4                      0xe4
#घोषणा FMTPGM_AP5                      0xe8
#घोषणा FMTPGM_AP6                      0xec
#घोषणा FMTPGM_AP7                      0xf0
#घोषणा LSCCFG1                         0xf4
#घोषणा LSCCFG2                         0xf8
#घोषणा LSCH0                           0xfc
#घोषणा LSCV0                           0x100
#घोषणा LSCKH                           0x104
#घोषणा LSCKV                           0x108
#घोषणा LSCMEMCTL                       0x10c
#घोषणा LSCMEMD                         0x110
#घोषणा LSCMEMQ                         0x114
#घोषणा DFCCTL                          0x118
#घोषणा DFCVSAT                         0x11c
#घोषणा DFCMEMCTL                       0x120
#घोषणा DFCMEM0                         0x124
#घोषणा DFCMEM1                         0x128
#घोषणा DFCMEM2                         0x12c
#घोषणा DFCMEM3                         0x130
#घोषणा DFCMEM4                         0x134
#घोषणा CSCCTL                          0x138
#घोषणा CSCM0                           0x13c
#घोषणा CSCM1                           0x140
#घोषणा CSCM2                           0x144
#घोषणा CSCM3                           0x148
#घोषणा CSCM4                           0x14c
#घोषणा CSCM5                           0x150
#घोषणा CSCM6                           0x154
#घोषणा CSCM7                           0x158
#घोषणा DATAOFST			0x15c
#घोषणा CCDC_REG_LAST			DATAOFST
/**************************************************************
*	Define क्रम various रेजिस्टर bit mask and shअगरts क्रम CCDC
*
**************************************************************/
#घोषणा CCDC_RAW_IP_MODE			0
#घोषणा CCDC_VDHDOUT_INPUT			0
#घोषणा CCDC_YCINSWP_RAW			(0 << 4)
#घोषणा CCDC_EXWEN_DISABLE			0
#घोषणा CCDC_DATAPOL_NORMAL			0
#घोषणा CCDC_CCDCFG_FIDMD_LATCH_VSYNC		0
#घोषणा CCDC_CCDCFG_FIDMD_NO_LATCH_VSYNC	(1 << 6)
#घोषणा CCDC_CCDCFG_WENLOG_AND			0
#घोषणा CCDC_CCDCFG_TRGSEL_WEN			0
#घोषणा CCDC_CCDCFG_EXTRG_DISABLE		0
#घोषणा CCDC_CFA_MOSAIC				0
#घोषणा CCDC_Y8POS_SHIFT			11

#घोषणा CCDC_VDC_DFCVSAT_MASK			0x3fff
#घोषणा CCDC_DATAOFST_MASK			0x0ff
#घोषणा CCDC_DATAOFST_H_SHIFT			0
#घोषणा CCDC_DATAOFST_V_SHIFT			8
#घोषणा CCDC_GAMMAWD_CFA_MASK			1
#घोषणा CCDC_GAMMAWD_CFA_SHIFT			5
#घोषणा CCDC_GAMMAWD_INPUT_SHIFT		2
#घोषणा CCDC_FID_POL_MASK			1
#घोषणा CCDC_FID_POL_SHIFT			4
#घोषणा CCDC_HD_POL_MASK			1
#घोषणा CCDC_HD_POL_SHIFT			3
#घोषणा CCDC_VD_POL_MASK			1
#घोषणा CCDC_VD_POL_SHIFT			2
#घोषणा CCDC_VD_POL_NEGATIVE			(1 << 2)
#घोषणा CCDC_FRM_FMT_MASK			1
#घोषणा CCDC_FRM_FMT_SHIFT			7
#घोषणा CCDC_DATA_SZ_MASK			7
#घोषणा CCDC_DATA_SZ_SHIFT			8
#घोषणा CCDC_VDHDOUT_MASK			1
#घोषणा CCDC_VDHDOUT_SHIFT			0
#घोषणा CCDC_EXWEN_MASK				1
#घोषणा CCDC_EXWEN_SHIFT			5
#घोषणा CCDC_INPUT_MODE_MASK			3
#घोषणा CCDC_INPUT_MODE_SHIFT			12
#घोषणा CCDC_PIX_FMT_MASK			3
#घोषणा CCDC_PIX_FMT_SHIFT			12
#घोषणा CCDC_DATAPOL_MASK			1
#घोषणा CCDC_DATAPOL_SHIFT			6
#घोषणा CCDC_WEN_ENABLE				(1 << 1)
#घोषणा CCDC_VDHDEN_ENABLE			(1 << 16)
#घोषणा CCDC_LPF_ENABLE				(1 << 14)
#घोषणा CCDC_ALAW_ENABLE			1
#घोषणा CCDC_ALAW_GAMMA_WD_MASK			7
#घोषणा CCDC_REC656IF_BT656_EN			3

#घोषणा CCDC_FMTCFG_FMTMODE_MASK		3
#घोषणा CCDC_FMTCFG_FMTMODE_SHIFT		1
#घोषणा CCDC_FMTCFG_LNUM_MASK			3
#घोषणा CCDC_FMTCFG_LNUM_SHIFT			4
#घोषणा CCDC_FMTCFG_ADDRINC_MASK		7
#घोषणा CCDC_FMTCFG_ADDRINC_SHIFT		8

#घोषणा CCDC_CCDCFG_FIDMD_SHIFT			6
#घोषणा	CCDC_CCDCFG_WENLOG_SHIFT		8
#घोषणा CCDC_CCDCFG_TRGSEL_SHIFT		9
#घोषणा CCDC_CCDCFG_EXTRG_SHIFT			10
#घोषणा CCDC_CCDCFG_MSBINVI_SHIFT		13

#घोषणा CCDC_HSIZE_FLIP_SHIFT			12
#घोषणा CCDC_HSIZE_FLIP_MASK			1
#घोषणा CCDC_HSIZE_VAL_MASK			0xFFF
#घोषणा CCDC_SDOFST_FIELD_INTERLEAVED		0x249
#घोषणा CCDC_SDOFST_INTERLACE_INVERSE		0x4B6D
#घोषणा CCDC_SDOFST_INTERLACE_NORMAL		0x0B6D
#घोषणा CCDC_SDOFST_PROGRESSIVE_INVERSE		0x4000
#घोषणा CCDC_SDOFST_PROGRESSIVE_NORMAL		0
#घोषणा CCDC_START_PX_HOR_MASK			0x7FFF
#घोषणा CCDC_NUM_PX_HOR_MASK			0x7FFF
#घोषणा CCDC_START_VER_ONE_MASK			0x7FFF
#घोषणा CCDC_START_VER_TWO_MASK			0x7FFF
#घोषणा CCDC_NUM_LINES_VER			0x7FFF

#घोषणा CCDC_BLK_CLAMP_ENABLE			(1 << 15)
#घोषणा CCDC_BLK_SGAIN_MASK			0x1F
#घोषणा CCDC_BLK_ST_PXL_MASK			0x1FFF
#घोषणा CCDC_BLK_SAMPLE_LN_MASK			3
#घोषणा CCDC_BLK_SAMPLE_LN_SHIFT		13

#घोषणा CCDC_NUM_LINE_CALC_MASK			3
#घोषणा CCDC_NUM_LINE_CALC_SHIFT		14

#घोषणा CCDC_BLK_DC_SUB_MASK			0x3FFF
#घोषणा CCDC_BLK_COMP_MASK			0xFF
#घोषणा CCDC_BLK_COMP_GB_COMP_SHIFT		8
#घोषणा CCDC_BLK_COMP_GR_COMP_SHIFT		0
#घोषणा CCDC_BLK_COMP_R_COMP_SHIFT		8
#घोषणा CCDC_LATCH_ON_VSYNC_DISABLE		(1 << 15)
#घोषणा CCDC_LATCH_ON_VSYNC_ENABLE		(0 << 15)
#घोषणा CCDC_FPC_ENABLE				(1 << 15)
#घोषणा CCDC_FPC_FPC_NUM_MASK			0x7FFF
#घोषणा CCDC_DATA_PACK_ENABLE			(1 << 11)
#घोषणा CCDC_FMT_HORZ_FMTLNH_MASK		0x1FFF
#घोषणा CCDC_FMT_HORZ_FMTSPH_MASK		0x1FFF
#घोषणा CCDC_FMT_HORZ_FMTSPH_SHIFT		16
#घोषणा CCDC_FMT_VERT_FMTLNV_MASK		0x1FFF
#घोषणा CCDC_FMT_VERT_FMTSLV_MASK		0x1FFF
#घोषणा CCDC_FMT_VERT_FMTSLV_SHIFT		16
#घोषणा CCDC_VP_OUT_VERT_NUM_MASK		0x3FFF
#घोषणा CCDC_VP_OUT_VERT_NUM_SHIFT		17
#घोषणा CCDC_VP_OUT_HORZ_NUM_MASK		0x1FFF
#घोषणा CCDC_VP_OUT_HORZ_NUM_SHIFT		4
#घोषणा CCDC_VP_OUT_HORZ_ST_MASK		0xF

#घोषणा CCDC_CSC_COEF_INTEG_MASK		7
#घोषणा CCDC_CSC_COEF_DECIMAL_MASK		0x1f
#घोषणा CCDC_CSC_COEF_INTEG_SHIFT		5
#घोषणा CCDC_CSCM_MSB_SHIFT			8
#घोषणा CCDC_CSC_ENABLE				1
#घोषणा CCDC_CSC_DEC_MAX			32

#घोषणा CCDC_MFILT1_SHIFT			10
#घोषणा CCDC_MFILT2_SHIFT			8
#घोषणा CCDC_MED_FILT_THRESH			0x3FFF
#घोषणा CCDC_LPF_MASK				1
#घोषणा CCDC_LPF_SHIFT				14
#घोषणा CCDC_OFFSET_MASK			0x3FF
#घोषणा CCDC_DATASFT_MASK			7
#घोषणा CCDC_DATASFT_SHIFT			8

#घोषणा CCDC_DF_ENABLE				1

#घोषणा CCDC_FMTPLEN_P0_MASK			0xF
#घोषणा CCDC_FMTPLEN_P1_MASK			0xF
#घोषणा CCDC_FMTPLEN_P2_MASK			7
#घोषणा CCDC_FMTPLEN_P3_MASK			7
#घोषणा CCDC_FMTPLEN_P0_SHIFT			0
#घोषणा CCDC_FMTPLEN_P1_SHIFT			4
#घोषणा CCDC_FMTPLEN_P2_SHIFT			8
#घोषणा CCDC_FMTPLEN_P3_SHIFT			12

#घोषणा CCDC_FMTSPH_MASK			0x1FFF
#घोषणा CCDC_FMTLNH_MASK			0x1FFF
#घोषणा CCDC_FMTSLV_MASK			0x1FFF
#घोषणा CCDC_FMTLNV_MASK			0x7FFF
#घोषणा CCDC_FMTRLEN_MASK			0x1FFF
#घोषणा CCDC_FMTHCNT_MASK			0x1FFF

#घोषणा CCDC_ADP_INIT_MASK			0x1FFF
#घोषणा CCDC_ADP_LINE_SHIFT			13
#घोषणा CCDC_ADP_LINE_MASK			3
#घोषणा CCDC_FMTPGN_APTR_MASK			7

#घोषणा CCDC_DFCCTL_GDFCEN_MASK			1
#घोषणा CCDC_DFCCTL_VDFCEN_MASK			1
#घोषणा CCDC_DFCCTL_VDFC_DISABLE		(0 << 4)
#घोषणा CCDC_DFCCTL_VDFCEN_SHIFT		4
#घोषणा CCDC_DFCCTL_VDFCSL_MASK			3
#घोषणा CCDC_DFCCTL_VDFCSL_SHIFT		5
#घोषणा CCDC_DFCCTL_VDFCUDA_MASK		1
#घोषणा CCDC_DFCCTL_VDFCUDA_SHIFT		7
#घोषणा CCDC_DFCCTL_VDFLSFT_MASK		3
#घोषणा CCDC_DFCCTL_VDFLSFT_SHIFT		8
#घोषणा CCDC_DFCMEMCTL_DFCMARST_MASK		1
#घोषणा CCDC_DFCMEMCTL_DFCMARST_SHIFT		2
#घोषणा CCDC_DFCMEMCTL_DFCMWR_MASK		1
#घोषणा CCDC_DFCMEMCTL_DFCMWR_SHIFT		0
#घोषणा CCDC_DFCMEMCTL_INC_ADDR			(0 << 2)

#घोषणा CCDC_LSCCFG_GFTSF_MASK			7
#घोषणा CCDC_LSCCFG_GFTSF_SHIFT			1
#घोषणा CCDC_LSCCFG_GFTINV_MASK			0xf
#घोषणा CCDC_LSCCFG_GFTINV_SHIFT		4
#घोषणा CCDC_LSC_GFTABLE_SEL_MASK		3
#घोषणा CCDC_LSC_GFTABLE_EPEL_SHIFT		8
#घोषणा CCDC_LSC_GFTABLE_OPEL_SHIFT		10
#घोषणा CCDC_LSC_GFTABLE_EPOL_SHIFT		12
#घोषणा CCDC_LSC_GFTABLE_OPOL_SHIFT		14
#घोषणा CCDC_LSC_GFMODE_MASK			3
#घोषणा CCDC_LSC_GFMODE_SHIFT			4
#घोषणा CCDC_LSC_DISABLE			0
#घोषणा CCDC_LSC_ENABLE				1
#घोषणा CCDC_LSC_TABLE1_SLC			0
#घोषणा CCDC_LSC_TABLE2_SLC			1
#घोषणा CCDC_LSC_TABLE3_SLC			2
#घोषणा CCDC_LSC_MEMADDR_RESET			(1 << 2)
#घोषणा CCDC_LSC_MEMADDR_INCR			(0 << 2)
#घोषणा CCDC_LSC_FRAC_MASK_T1			0xFF
#घोषणा CCDC_LSC_INT_MASK			3
#घोषणा CCDC_LSC_FRAC_MASK			0x3FFF
#घोषणा CCDC_LSC_CENTRE_MASK			0x3FFF
#घोषणा CCDC_LSC_COEF_MASK			0xff
#घोषणा CCDC_LSC_COEFL_SHIFT			0
#घोषणा CCDC_LSC_COEFU_SHIFT			8
#घोषणा CCDC_GAIN_MASK				0x7FF
#घोषणा CCDC_SYNCEN_VDHDEN_MASK			(1 << 0)
#घोषणा CCDC_SYNCEN_WEN_MASK			(1 << 1)
#घोषणा CCDC_SYNCEN_WEN_SHIFT			1

/* Power on Defaults in hardware */
#घोषणा MODESET_DEFAULT				0x200
#घोषणा CULH_DEFAULT				0xFFFF
#घोषणा CULV_DEFAULT				0xFF
#घोषणा GAIN_DEFAULT				256
#घोषणा OUTCLIP_DEFAULT				0x3FFF
#घोषणा LSCCFG2_DEFAULT				0xE

#पूर्ण_अगर
