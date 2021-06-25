<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * rcar_du_regs.h  --  R-Car Display Unit Registers Definitions
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __RCAR_DU_REGS_H__
#घोषणा __RCAR_DU_REGS_H__

#घोषणा DU0_REG_OFFSET		0x00000
#घोषणा DU1_REG_OFFSET		0x30000
#घोषणा DU2_REG_OFFSET		0x40000
#घोषणा DU3_REG_OFFSET		0x70000

/* -----------------------------------------------------------------------------
 * Display Control Registers
 */

#घोषणा DSYSR			0x00000	/* display 1 */
#घोषणा DSYSR_ILTS		(1 << 29)
#घोषणा DSYSR_DSEC		(1 << 20)
#घोषणा DSYSR_IUPD		(1 << 16)
#घोषणा DSYSR_DRES		(1 << 9)
#घोषणा DSYSR_DEN		(1 << 8)
#घोषणा DSYSR_TVM_MASTER	(0 << 6)
#घोषणा DSYSR_TVM_SWITCH	(1 << 6)
#घोषणा DSYSR_TVM_TVSYNC	(2 << 6)
#घोषणा DSYSR_TVM_MASK		(3 << 6)
#घोषणा DSYSR_SCM_INT_NONE	(0 << 4)
#घोषणा DSYSR_SCM_INT_SYNC	(2 << 4)
#घोषणा DSYSR_SCM_INT_VIDEO	(3 << 4)
#घोषणा DSYSR_SCM_MASK		(3 << 4)

#घोषणा DSMR			0x00004
#घोषणा DSMR_VSPM		(1 << 28)
#घोषणा DSMR_ODPM		(1 << 27)
#घोषणा DSMR_DIPM_DISP		(0 << 25)
#घोषणा DSMR_DIPM_CSYNC		(1 << 25)
#घोषणा DSMR_DIPM_DE		(3 << 25)
#घोषणा DSMR_DIPM_MASK		(3 << 25)
#घोषणा DSMR_CSPM		(1 << 24)
#घोषणा DSMR_DIL		(1 << 19)
#घोषणा DSMR_VSL		(1 << 18)
#घोषणा DSMR_HSL		(1 << 17)
#घोषणा DSMR_DDIS		(1 << 16)
#घोषणा DSMR_CDEL		(1 << 15)
#घोषणा DSMR_CDEM_CDE		(0 << 13)
#घोषणा DSMR_CDEM_LOW		(2 << 13)
#घोषणा DSMR_CDEM_HIGH		(3 << 13)
#घोषणा DSMR_CDEM_MASK		(3 << 13)
#घोषणा DSMR_CDED		(1 << 12)
#घोषणा DSMR_ODEV		(1 << 8)
#घोषणा DSMR_CSY_VH_OR		(0 << 6)
#घोषणा DSMR_CSY_333		(2 << 6)
#घोषणा DSMR_CSY_222		(3 << 6)
#घोषणा DSMR_CSY_MASK		(3 << 6)

#घोषणा DSSR			0x00008
#घोषणा DSSR_VC1FB_DSA0		(0 << 30)
#घोषणा DSSR_VC1FB_DSA1		(1 << 30)
#घोषणा DSSR_VC1FB_DSA2		(2 << 30)
#घोषणा DSSR_VC1FB_INIT		(3 << 30)
#घोषणा DSSR_VC1FB_MASK		(3 << 30)
#घोषणा DSSR_VC0FB_DSA0		(0 << 28)
#घोषणा DSSR_VC0FB_DSA1		(1 << 28)
#घोषणा DSSR_VC0FB_DSA2		(2 << 28)
#घोषणा DSSR_VC0FB_INIT		(3 << 28)
#घोषणा DSSR_VC0FB_MASK		(3 << 28)
#घोषणा DSSR_DFB(n)		(1 << ((n)+15))
#घोषणा DSSR_TVR		(1 << 15)
#घोषणा DSSR_FRM		(1 << 14)
#घोषणा DSSR_VBK		(1 << 11)
#घोषणा DSSR_RINT		(1 << 9)
#घोषणा DSSR_HBK		(1 << 8)
#घोषणा DSSR_ADC(n)		(1 << ((n)-1))

#घोषणा DSRCR			0x0000c
#घोषणा DSRCR_TVCL		(1 << 15)
#घोषणा DSRCR_FRCL		(1 << 14)
#घोषणा DSRCR_VBCL		(1 << 11)
#घोषणा DSRCR_RICL		(1 << 9)
#घोषणा DSRCR_HBCL		(1 << 8)
#घोषणा DSRCR_ADCL(n)		(1 << ((n)-1))
#घोषणा DSRCR_MASK		0x0000cbff

#घोषणा DIER			0x00010
#घोषणा DIER_TVE		(1 << 15)
#घोषणा DIER_FRE		(1 << 14)
#घोषणा DIER_VBE		(1 << 11)
#घोषणा DIER_RIE		(1 << 9)
#घोषणा DIER_HBE		(1 << 8)
#घोषणा DIER_ADCE(n)		(1 << ((n)-1))

#घोषणा CPCR			0x00014
#घोषणा CPCR_CP4CE		(1 << 19)
#घोषणा CPCR_CP3CE		(1 << 18)
#घोषणा CPCR_CP2CE		(1 << 17)
#घोषणा CPCR_CP1CE		(1 << 16)

#घोषणा DPPR			0x00018
#घोषणा DPPR_DPE(n)		(1 << ((n)*4-1))
#घोषणा DPPR_DPS(n, p)		(((p)-1) << DPPR_DPS_SHIFT(n))
#घोषणा DPPR_DPS_SHIFT(n)	(((n)-1)*4)
#घोषणा DPPR_BPP16		(DPPR_DPE(8) | DPPR_DPS(8, 1))	/* plane1 */
#घोषणा DPPR_BPP32_P1		(DPPR_DPE(7) | DPPR_DPS(7, 1))
#घोषणा DPPR_BPP32_P2		(DPPR_DPE(8) | DPPR_DPS(8, 2))
#घोषणा DPPR_BPP32		(DPPR_BPP32_P1 | DPPR_BPP32_P2)	/* plane1 & 2 */

#घोषणा DEFR			0x00020
#घोषणा DEFR_CODE		(0x7773 << 16)
#घोषणा DEFR_EXSL		(1 << 12)
#घोषणा DEFR_EXVL		(1 << 11)
#घोषणा DEFR_EXUP		(1 << 5)
#घोषणा DEFR_VCUP		(1 << 4)
#घोषणा DEFR_DEFE		(1 << 0)

#घोषणा DAPCR			0x00024
#घोषणा DAPCR_CODE		(0x7773 << 16)
#घोषणा DAPCR_AP2E		(1 << 4)
#घोषणा DAPCR_AP1E		(1 << 0)

#घोषणा DCPCR			0x00028
#घोषणा DCPCR_CODE		(0x7773 << 16)
#घोषणा DCPCR_CA2B		(1 << 13)
#घोषणा DCPCR_CD2F		(1 << 12)
#घोषणा DCPCR_DC2E		(1 << 8)
#घोषणा DCPCR_CAB		(1 << 5)
#घोषणा DCPCR_CDF		(1 << 4)
#घोषणा DCPCR_DCE		(1 << 0)

#घोषणा DEFR2			0x00034
#घोषणा DEFR2_CODE		(0x7775 << 16)
#घोषणा DEFR2_DEFE2G		(1 << 0)

#घोषणा DEFR3			0x00038
#घोषणा DEFR3_CODE		(0x7776 << 16)
#घोषणा DEFR3_EVDA		(1 << 14)
#घोषणा DEFR3_EVDM_1		(1 << 12)
#घोषणा DEFR3_EVDM_2		(2 << 12)
#घोषणा DEFR3_EVDM_3		(3 << 12)
#घोषणा DEFR3_VMSM2_EMA		(1 << 6)
#घोषणा DEFR3_VMSM1_ENA		(1 << 4)
#घोषणा DEFR3_DEFE3		(1 << 0)

#घोषणा DEFR4			0x0003c
#घोषणा DEFR4_CODE		(0x7777 << 16)
#घोषणा DEFR4_LRUO		(1 << 5)
#घोषणा DEFR4_SPCE		(1 << 4)

#घोषणा DVCSR			0x000d0
#घोषणा DVCSR_VCnFB2_DSA0(n)	(0 << ((n)*2+16))
#घोषणा DVCSR_VCnFB2_DSA1(n)	(1 << ((n)*2+16))
#घोषणा DVCSR_VCnFB2_DSA2(n)	(2 << ((n)*2+16))
#घोषणा DVCSR_VCnFB2_INIT(n)	(3 << ((n)*2+16))
#घोषणा DVCSR_VCnFB2_MASK(n)	(3 << ((n)*2+16))
#घोषणा DVCSR_VCnFB_DSA0(n)	(0 << ((n)*2))
#घोषणा DVCSR_VCnFB_DSA1(n)	(1 << ((n)*2))
#घोषणा DVCSR_VCnFB_DSA2(n)	(2 << ((n)*2))
#घोषणा DVCSR_VCnFB_INIT(n)	(3 << ((n)*2))
#घोषणा DVCSR_VCnFB_MASK(n)	(3 << ((n)*2))

#घोषणा DEFR5			0x000e0
#घोषणा DEFR5_CODE		(0x66 << 24)
#घोषणा DEFR5_YCRGB2_DIS	(0 << 14)
#घोषणा DEFR5_YCRGB2_PRI1	(1 << 14)
#घोषणा DEFR5_YCRGB2_PRI2	(2 << 14)
#घोषणा DEFR5_YCRGB2_PRI3	(3 << 14)
#घोषणा DEFR5_YCRGB2_MASK	(3 << 14)
#घोषणा DEFR5_YCRGB1_DIS	(0 << 12)
#घोषणा DEFR5_YCRGB1_PRI1	(1 << 12)
#घोषणा DEFR5_YCRGB1_PRI2	(2 << 12)
#घोषणा DEFR5_YCRGB1_PRI3	(3 << 12)
#घोषणा DEFR5_YCRGB1_MASK	(3 << 12)
#घोषणा DEFR5_DEFE5		(1 << 0)

#घोषणा DDLTR			0x000e4
#घोषणा DDLTR_CODE		(0x7766 << 16)
#घोषणा DDLTR_DLAR2		(1 << 6)
#घोषणा DDLTR_DLAY2		(1 << 5)
#घोषणा DDLTR_DLAY1		(1 << 1)

#घोषणा DEFR6			0x000e8
#घोषणा DEFR6_CODE		(0x7778 << 16)
#घोषणा DEFR6_ODPM12_DSMR	(0 << 10)
#घोषणा DEFR6_ODPM12_DISP	(2 << 10)
#घोषणा DEFR6_ODPM12_CDE	(3 << 10)
#घोषणा DEFR6_ODPM12_MASK	(3 << 10)
#घोषणा DEFR6_ODPM02_DSMR	(0 << 8)
#घोषणा DEFR6_ODPM02_DISP	(2 << 8)
#घोषणा DEFR6_ODPM02_CDE	(3 << 8)
#घोषणा DEFR6_ODPM02_MASK	(3 << 8)
#घोषणा DEFR6_TCNE1		(1 << 6)
#घोषणा DEFR6_TCNE0		(1 << 4)
#घोषणा DEFR6_MLOS1		(1 << 2)
#घोषणा DEFR6_DEFAULT		(DEFR6_CODE | DEFR6_TCNE1)

#घोषणा DEFR7			0x000ec
#घोषणा DEFR7_CODE		(0x7779 << 16)
#घोषणा DEFR7_CMME1		BIT(6)
#घोषणा DEFR7_CMME0		BIT(4)

/* -----------------------------------------------------------------------------
 * R8A7790-only Control Registers
 */

#घोषणा DD1SSR			0x20008
#घोषणा DD1SSR_TVR		(1 << 15)
#घोषणा DD1SSR_FRM		(1 << 14)
#घोषणा DD1SSR_BUF		(1 << 12)
#घोषणा DD1SSR_VBK		(1 << 11)
#घोषणा DD1SSR_RINT		(1 << 9)
#घोषणा DD1SSR_HBK		(1 << 8)
#घोषणा DD1SSR_ADC(n)		(1 << ((n)-1))

#घोषणा DD1SRCR			0x2000c
#घोषणा DD1SRCR_TVR		(1 << 15)
#घोषणा DD1SRCR_FRM		(1 << 14)
#घोषणा DD1SRCR_BUF		(1 << 12)
#घोषणा DD1SRCR_VBK		(1 << 11)
#घोषणा DD1SRCR_RINT		(1 << 9)
#घोषणा DD1SRCR_HBK		(1 << 8)
#घोषणा DD1SRCR_ADC(n)		(1 << ((n)-1))

#घोषणा DD1IER			0x20010
#घोषणा DD1IER_TVR		(1 << 15)
#घोषणा DD1IER_FRM		(1 << 14)
#घोषणा DD1IER_BUF		(1 << 12)
#घोषणा DD1IER_VBK		(1 << 11)
#घोषणा DD1IER_RINT		(1 << 9)
#घोषणा DD1IER_HBK		(1 << 8)
#घोषणा DD1IER_ADC(n)		(1 << ((n)-1))

#घोषणा DEFR8			0x20020
#घोषणा DEFR8_CODE		(0x7790 << 16)
#घोषणा DEFR8_VSCS		(1 << 6)
#घोषणा DEFR8_DRGBS_DU(n)	((n) << 4)
#घोषणा DEFR8_DRGBS_MASK	(3 << 4)
#घोषणा DEFR8_DEFE8		(1 << 0)

#घोषणा DOFLR			0x20024
#घोषणा DOFLR_CODE		(0x7790 << 16)
#घोषणा DOFLR_HSYCFL1		(1 << 13)
#घोषणा DOFLR_VSYCFL1		(1 << 12)
#घोषणा DOFLR_ODDFL1		(1 << 11)
#घोषणा DOFLR_DISPFL1		(1 << 10)
#घोषणा DOFLR_CDEFL1		(1 << 9)
#घोषणा DOFLR_RGBFL1		(1 << 8)
#घोषणा DOFLR_HSYCFL0		(1 << 5)
#घोषणा DOFLR_VSYCFL0		(1 << 4)
#घोषणा DOFLR_ODDFL0		(1 << 3)
#घोषणा DOFLR_DISPFL0		(1 << 2)
#घोषणा DOFLR_CDEFL0		(1 << 1)
#घोषणा DOFLR_RGBFL0		(1 << 0)

#घोषणा DIDSR			0x20028
#घोषणा DIDSR_CODE		(0x7790 << 16)
#घोषणा DIDSR_LCDS_DCLKIN(n)	(0 << (8 + (n) * 2))
#घोषणा DIDSR_LCDS_LVDS0(n)	(2 << (8 + (n) * 2))
#घोषणा DIDSR_LCDS_LVDS1(n)	(3 << (8 + (n) * 2))
#घोषणा DIDSR_LCDS_MASK(n)	(3 << (8 + (n) * 2))
#घोषणा DIDSR_PDCS_CLK(n, clk)	(clk << ((n) * 2))
#घोषणा DIDSR_PDCS_MASK(n)	(3 << ((n) * 2))

#घोषणा DEFR10			0x20038
#घोषणा DEFR10_CODE		(0x7795 << 16)
#घोषणा DEFR10_VSPF1_RGB	(0 << 14)
#घोषणा DEFR10_VSPF1_YC		(1 << 14)
#घोषणा DEFR10_DOCF1_RGB	(0 << 12)
#घोषणा DEFR10_DOCF1_YC		(1 << 12)
#घोषणा DEFR10_YCDF0_YCBCR444	(0 << 11)
#घोषणा DEFR10_YCDF0_YCBCR422	(1 << 11)
#घोषणा DEFR10_VSPF0_RGB	(0 << 10)
#घोषणा DEFR10_VSPF0_YC		(1 << 10)
#घोषणा DEFR10_DOCF0_RGB	(0 << 8)
#घोषणा DEFR10_DOCF0_YC		(1 << 8)
#घोषणा DEFR10_TSEL_H3_TCON1	(0 << 1) /* DEFR102 रेजिस्टर only (DU2/DU3) */
#घोषणा DEFR10_DEFE10		(1 << 0)

#घोषणा DPLLCR			0x20044
#घोषणा DPLLCR_CODE		(0x95 << 24)
#घोषणा DPLLCR_PLCS1		(1 << 23)
/*
 * PLCS0 is bit 21, but H3 ES1.x requires bit 20 to be set as well. As bit 20
 * isn't implemented by other SoC in the Gen3 family it can safely be set
 * unconditionally.
 */
#घोषणा DPLLCR_PLCS0		(3 << 20)
#घोषणा DPLLCR_CLKE		(1 << 18)
#घोषणा DPLLCR_FDPLL(n)		((n) << 12)
#घोषणा DPLLCR_N(n)		((n) << 5)
#घोषणा DPLLCR_M(n)		((n) << 3)
#घोषणा DPLLCR_STBY		(1 << 2)
#घोषणा DPLLCR_INCS_DOTCLKIN0	(0 << 0)
#घोषणा DPLLCR_INCS_DOTCLKIN1	(1 << 1)

#घोषणा DPLLC2R			0x20048
#घोषणा DPLLC2R_CODE		(0x95 << 24)
#घोषणा DPLLC2R_SELC		(1 << 12)
#घोषणा DPLLC2R_M(n)		((n) << 8)
#घोषणा DPLLC2R_FDPLL(n)	((n) << 0)

/* -----------------------------------------------------------------------------
 * Display Timing Generation Registers
 */

#घोषणा HDSR			0x00040
#घोषणा HDER			0x00044
#घोषणा VDSR			0x00048
#घोषणा VDER			0x0004c
#घोषणा HCR			0x00050
#घोषणा HSWR			0x00054
#घोषणा VCR			0x00058
#घोषणा VSPR			0x0005c
#घोषणा EQWR			0x00060
#घोषणा SPWR			0x00064
#घोषणा CLAMPSR			0x00070
#घोषणा CLAMPWR			0x00074
#घोषणा DESR			0x00078
#घोषणा DEWR			0x0007c

/* -----------------------------------------------------------------------------
 * Display Attribute Registers
 */

#घोषणा CP1TR			0x00080
#घोषणा CP2TR			0x00084
#घोषणा CP3TR			0x00088
#घोषणा CP4TR			0x0008c

#घोषणा DOOR			0x00090
#घोषणा DOOR_RGB(r, g, b)	(((r) << 18) | ((g) << 10) | ((b) << 2))
#घोषणा CDER			0x00094
#घोषणा CDER_RGB(r, g, b)	(((r) << 18) | ((g) << 10) | ((b) << 2))
#घोषणा BPOR			0x00098
#घोषणा BPOR_RGB(r, g, b)	(((r) << 18) | ((g) << 10) | ((b) << 2))

#घोषणा RINTOFSR		0x0009c

#घोषणा DSHPR			0x000c8
#घोषणा DSHPR_CODE		(0x7776 << 16)
#घोषणा DSHPR_PRIH		(0xa << 4)
#घोषणा DSHPR_PRIL_BPP16	(0x8 << 0)
#घोषणा DSHPR_PRIL_BPP32	(0x9 << 0)

/* -----------------------------------------------------------------------------
 * Display Plane Registers
 */

#घोषणा PLANE_OFF		0x00100

#घोषणा PnMR			0x00100 /* plane 1 */
#घोषणा PnMR_VISL_VIN0		(0 << 26)	/* use Video Input 0 */
#घोषणा PnMR_VISL_VIN1		(1 << 26)	/* use Video Input 1 */
#घोषणा PnMR_VISL_VIN2		(2 << 26)	/* use Video Input 2 */
#घोषणा PnMR_VISL_VIN3		(3 << 26)	/* use Video Input 3 */
#घोषणा PnMR_YCDF_YUYV		(1 << 20)	/* YUYV क्रमmat */
#घोषणा PnMR_TC_R		(0 << 17)	/* Tranparent color is PnTC1R */
#घोषणा PnMR_TC_CP		(1 << 17)	/* Tranparent color is color palette */
#घोषणा PnMR_WAE		(1 << 16)	/* Wrap around Enable */
#घोषणा PnMR_SPIM_TP		(0 << 12)	/* Transparent Color */
#घोषणा PnMR_SPIM_ALP		(1 << 12)	/* Alpha Blending */
#घोषणा PnMR_SPIM_EOR		(2 << 12)	/* EOR */
#घोषणा PnMR_SPIM_TP_OFF	(1 << 14)	/* No Transparent Color */
#घोषणा PnMR_CPSL_CP1		(0 << 8)	/* Color Palette selected 1 */
#घोषणा PnMR_CPSL_CP2		(1 << 8)	/* Color Palette selected 2 */
#घोषणा PnMR_CPSL_CP3		(2 << 8)	/* Color Palette selected 3 */
#घोषणा PnMR_CPSL_CP4		(3 << 8)	/* Color Palette selected 4 */
#घोषणा PnMR_DC			(1 << 7)	/* Display Area Change */
#घोषणा PnMR_BM_MD		(0 << 4)	/* Manual Display Change Mode */
#घोषणा PnMR_BM_AR		(1 << 4)	/* Auto Rendering Mode */
#घोषणा PnMR_BM_AD		(2 << 4)	/* Auto Display Change Mode */
#घोषणा PnMR_BM_VC		(3 << 4)	/* Video Capture Mode */
#घोषणा PnMR_DDDF_8BPP		(0 << 0)	/* 8bit */
#घोषणा PnMR_DDDF_16BPP		(1 << 0)	/* 16bit or 32bit */
#घोषणा PnMR_DDDF_ARGB		(2 << 0)	/* ARGB */
#घोषणा PnMR_DDDF_YC		(3 << 0)	/* YC */
#घोषणा PnMR_DDDF_MASK		(3 << 0)

#घोषणा PnMWR			0x00104

#घोषणा PnALPHAR		0x00108
#घोषणा PnALPHAR_ABIT_1		(0 << 12)
#घोषणा PnALPHAR_ABIT_0		(1 << 12)
#घोषणा PnALPHAR_ABIT_X		(2 << 12)

#घोषणा PnDSXR			0x00110
#घोषणा PnDSYR			0x00114
#घोषणा PnDPXR			0x00118
#घोषणा PnDPYR			0x0011c

#घोषणा PnDSA0R			0x00120
#घोषणा PnDSA1R			0x00124
#घोषणा PnDSA2R			0x00128
#घोषणा PnDSA_MASK		0xfffffff0

#घोषणा PnSPXR			0x00130
#घोषणा PnSPYR			0x00134
#घोषणा PnWASPR			0x00138
#घोषणा PnWAMWR			0x0013c

#घोषणा PnBTR			0x00140

#घोषणा PnTC1R			0x00144
#घोषणा PnTC2R			0x00148
#घोषणा PnTC3R			0x0014c
#घोषणा PnTC3R_CODE		(0x66 << 24)

#घोषणा PnMLR			0x00150

#घोषणा PnSWAPR			0x00180
#घोषणा PnSWAPR_DIGN		(1 << 4)
#घोषणा PnSWAPR_SPQW		(1 << 3)
#घोषणा PnSWAPR_SPLW		(1 << 2)
#घोषणा PnSWAPR_SPWD		(1 << 1)
#घोषणा PnSWAPR_SPBY		(1 << 0)

#घोषणा PnDDCR			0x00184
#घोषणा PnDDCR_CODE		(0x7775 << 16)
#घोषणा PnDDCR_LRGB1		(1 << 11)
#घोषणा PnDDCR_LRGB0		(1 << 10)

#घोषणा PnDDCR2			0x00188
#घोषणा PnDDCR2_CODE		(0x7776 << 16)
#घोषणा PnDDCR2_NV21		(1 << 5)
#घोषणा PnDDCR2_Y420		(1 << 4)
#घोषणा PnDDCR2_DIVU		(1 << 1)
#घोषणा PnDDCR2_DIVY		(1 << 0)

#घोषणा PnDDCR4			0x00190
#घोषणा PnDDCR4_CODE		(0x7766 << 16)
#घोषणा PnDDCR4_VSPS		(1 << 13)
#घोषणा PnDDCR4_SDFS_RGB	(0 << 4)
#घोषणा PnDDCR4_SDFS_YC		(5 << 4)
#घोषणा PnDDCR4_SDFS_MASK	(7 << 4)
#घोषणा PnDDCR4_EDF_NONE	(0 << 0)
#घोषणा PnDDCR4_EDF_ARGB8888	(1 << 0)
#घोषणा PnDDCR4_EDF_RGB888	(2 << 0)
#घोषणा PnDDCR4_EDF_RGB666	(3 << 0)
#घोषणा PnDDCR4_EDF_MASK	(7 << 0)

#घोषणा APnMR			0x0a100
#घोषणा APnMR_WAE		(1 << 16)	/* Wrap around Enable */
#घोषणा APnMR_DC		(1 << 7)	/* Display Area Change */
#घोषणा APnMR_BM_MD		(0 << 4)	/* Manual Display Change Mode */
#घोषणा APnMR_BM_AD		(2 << 4)	/* Auto Display Change Mode */

#घोषणा APnMWR			0x0a104

#घोषणा APnDSXR			0x0a110
#घोषणा APnDSYR			0x0a114
#घोषणा APnDPXR			0x0a118
#घोषणा APnDPYR			0x0a11c

#घोषणा APnDSA0R		0x0a120
#घोषणा APnDSA1R		0x0a124
#घोषणा APnDSA2R		0x0a128

#घोषणा APnSPXR			0x0a130
#घोषणा APnSPYR			0x0a134
#घोषणा APnWASPR		0x0a138
#घोषणा APnWAMWR		0x0a13c

#घोषणा APnBTR			0x0a140

#घोषणा APnMLR			0x0a150
#घोषणा APnSWAPR		0x0a180

/* -----------------------------------------------------------------------------
 * Display Capture Registers
 */

#घोषणा DCMR			0x0c100
#घोषणा DCMWR			0x0c104
#घोषणा DCSAR			0x0c120
#घोषणा DCMLR			0x0c150

/* -----------------------------------------------------------------------------
 * Color Palette Registers
 */

#घोषणा CP1_000R		0x01000
#घोषणा CP1_255R		0x013fc
#घोषणा CP2_000R		0x02000
#घोषणा CP2_255R		0x023fc
#घोषणा CP3_000R		0x03000
#घोषणा CP3_255R		0x033fc
#घोषणा CP4_000R		0x04000
#घोषणा CP4_255R		0x043fc

/* -----------------------------------------------------------------------------
 * External Synchronization Control Registers
 */

#घोषणा ESCR02			0x10000
#घोषणा ESCR13			0x01000
#घोषणा ESCR_DCLKOINV		(1 << 25)
#घोषणा ESCR_DCLKSEL_DCLKIN	(0 << 20)
#घोषणा ESCR_DCLKSEL_CLKS	(1 << 20)
#घोषणा ESCR_DCLKSEL_MASK	(1 << 20)
#घोषणा ESCR_DCLKDIS		(1 << 16)
#घोषणा ESCR_SYNCSEL_OFF	(0 << 8)
#घोषणा ESCR_SYNCSEL_EXVSYNC	(2 << 8)
#घोषणा ESCR_SYNCSEL_EXHSYNC	(3 << 8)
#घोषणा ESCR_FRQSEL_MASK	(0x3f << 0)

#घोषणा OTAR02			0x10004
#घोषणा OTAR13			0x01004

/* -----------------------------------------------------------------------------
 * Dual Display Output Control Registers
 */

#घोषणा DORCR			0x11000
#घोषणा DORCR_PG2T		(1 << 30)
#घोषणा DORCR_DK2S		(1 << 28)
#घोषणा DORCR_PG2D_DS1		(0 << 24)
#घोषणा DORCR_PG2D_DS2		(1 << 24)
#घोषणा DORCR_PG2D_FIX0		(2 << 24)
#घोषणा DORCR_PG2D_DOOR		(3 << 24)
#घोषणा DORCR_PG2D_MASK		(3 << 24)
#घोषणा DORCR_DR1D		(1 << 21)
#घोषणा DORCR_PG1D_DS1		(0 << 16)
#घोषणा DORCR_PG1D_DS2		(1 << 16)
#घोषणा DORCR_PG1D_FIX0		(2 << 16)
#घोषणा DORCR_PG1D_DOOR		(3 << 16)
#घोषणा DORCR_PG1D_MASK		(3 << 16)
#घोषणा DORCR_RGPV		(1 << 4)
#घोषणा DORCR_DPRS		(1 << 0)

#घोषणा DPTSR			0x11004
#घोषणा DPTSR_PnDK(n)		(1 << ((n) + 16))
#घोषणा DPTSR_PnTS(n)		(1 << (n))

#घोषणा DAPTSR			0x11008
#घोषणा DAPTSR_APnDK(n)		(1 << ((n) + 16))
#घोषणा DAPTSR_APnTS(n)		(1 << (n))

#घोषणा DS1PR			0x11020
#घोषणा DS2PR			0x11024

/* -----------------------------------------------------------------------------
 * YC-RGB Conversion Coefficient Registers
 */

#घोषणा YNCR			0x11080
#घोषणा YNOR			0x11084
#घोषणा CRNOR			0x11088
#घोषणा CBNOR			0x1108c
#घोषणा RCRCR			0x11090
#घोषणा GCRCR			0x11094
#घोषणा GCBCR			0x11098
#घोषणा BCBCR			0x1109c

#पूर्ण_अगर /* __RCAR_DU_REGS_H__ */
