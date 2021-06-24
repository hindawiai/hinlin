<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_regs.h  --  R-Car VSP1 Registers Definitions
 *
 * Copyright (C) 2013 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __VSP1_REGS_H__
#घोषणा __VSP1_REGS_H__

/* -----------------------------------------------------------------------------
 * General Control Registers
 */

#घोषणा VI6_CMD(n)			(0x0000 + (n) * 4)
#घोषणा VI6_CMD_UPDHDR			BIT(4)
#घोषणा VI6_CMD_STRCMD			BIT(0)

#घोषणा VI6_CLK_DCSWT			0x0018
#घोषणा VI6_CLK_DCSWT_CSTPW_MASK	(0xff << 8)
#घोषणा VI6_CLK_DCSWT_CSTPW_SHIFT	8
#घोषणा VI6_CLK_DCSWT_CSTRW_MASK	(0xff << 0)
#घोषणा VI6_CLK_DCSWT_CSTRW_SHIFT	0

#घोषणा VI6_SRESET			0x0028
#घोषणा VI6_SRESET_SRTS(n)		BIT(n)

#घोषणा VI6_STATUS			0x0038
#घोषणा VI6_STATUS_FLD_STD(n)		BIT((n) + 28)
#घोषणा VI6_STATUS_SYS_ACT(n)		BIT((n) + 8)

#घोषणा VI6_WPF_IRQ_ENB(n)		(0x0048 + (n) * 12)
#घोषणा VI6_WFP_IRQ_ENB_DFEE		BIT(1)
#घोषणा VI6_WFP_IRQ_ENB_FREE		BIT(0)

#घोषणा VI6_WPF_IRQ_STA(n)		(0x004c + (n) * 12)
#घोषणा VI6_WFP_IRQ_STA_DFE		BIT(1)
#घोषणा VI6_WFP_IRQ_STA_FRE		BIT(0)

#घोषणा VI6_DISP_IRQ_ENB(n)		(0x0078 + (n) * 60)
#घोषणा VI6_DISP_IRQ_ENB_DSTE		BIT(8)
#घोषणा VI6_DISP_IRQ_ENB_MAEE		BIT(5)
#घोषणा VI6_DISP_IRQ_ENB_LNEE(n)	BIT(n)

#घोषणा VI6_DISP_IRQ_STA(n)		(0x007c + (n) * 60)
#घोषणा VI6_DISP_IRQ_STA_DST		BIT(8)
#घोषणा VI6_DISP_IRQ_STA_MAE		BIT(5)
#घोषणा VI6_DISP_IRQ_STA_LNE(n)		BIT(n)

#घोषणा VI6_WPF_LINE_COUNT(n)		(0x0084 + (n) * 4)
#घोषणा VI6_WPF_LINE_COUNT_MASK		(0x1fffff << 0)

/* -----------------------------------------------------------------------------
 * Display List Control Registers
 */

#घोषणा VI6_DL_CTRL			0x0100
#घोषणा VI6_DL_CTRL_AR_WAIT_MASK	(0xffff << 16)
#घोषणा VI6_DL_CTRL_AR_WAIT_SHIFT	16
#घोषणा VI6_DL_CTRL_DC2			BIT(12)
#घोषणा VI6_DL_CTRL_DC1			BIT(8)
#घोषणा VI6_DL_CTRL_DC0			BIT(4)
#घोषणा VI6_DL_CTRL_CFM0		BIT(2)
#घोषणा VI6_DL_CTRL_NH0			BIT(1)
#घोषणा VI6_DL_CTRL_DLE			BIT(0)

#घोषणा VI6_DL_HDR_ADDR(n)		(0x0104 + (n) * 4)

#घोषणा VI6_DL_SWAP			0x0114
#घोषणा VI6_DL_SWAP_LWS			BIT(2)
#घोषणा VI6_DL_SWAP_WDS			BIT(1)
#घोषणा VI6_DL_SWAP_BTS			BIT(0)

#घोषणा VI6_DL_EXT_CTRL(n)		(0x011c + (n) * 36)
#घोषणा VI6_DL_EXT_CTRL_NWE		BIT(16)
#घोषणा VI6_DL_EXT_CTRL_POLINT_MASK	(0x3f << 8)
#घोषणा VI6_DL_EXT_CTRL_POLINT_SHIFT	8
#घोषणा VI6_DL_EXT_CTRL_DLPRI		BIT(5)
#घोषणा VI6_DL_EXT_CTRL_EXPRI		BIT(4)
#घोषणा VI6_DL_EXT_CTRL_EXT		BIT(0)

#घोषणा VI6_DL_EXT_AUTOFLD_INT		BIT(0)

#घोषणा VI6_DL_BODY_SIZE		0x0120
#घोषणा VI6_DL_BODY_SIZE_UPD		BIT(24)
#घोषणा VI6_DL_BODY_SIZE_BS_MASK	(0x1ffff << 0)
#घोषणा VI6_DL_BODY_SIZE_BS_SHIFT	0

/* -----------------------------------------------------------------------------
 * RPF Control Registers
 */

#घोषणा VI6_RPF_OFFSET			0x100

#घोषणा VI6_RPF_SRC_BSIZE		0x0300
#घोषणा VI6_RPF_SRC_BSIZE_BHSIZE_MASK	(0x1fff << 16)
#घोषणा VI6_RPF_SRC_BSIZE_BHSIZE_SHIFT	16
#घोषणा VI6_RPF_SRC_BSIZE_BVSIZE_MASK	(0x1fff << 0)
#घोषणा VI6_RPF_SRC_BSIZE_BVSIZE_SHIFT	0

#घोषणा VI6_RPF_SRC_ESIZE		0x0304
#घोषणा VI6_RPF_SRC_ESIZE_EHSIZE_MASK	(0x1fff << 16)
#घोषणा VI6_RPF_SRC_ESIZE_EHSIZE_SHIFT	16
#घोषणा VI6_RPF_SRC_ESIZE_EVSIZE_MASK	(0x1fff << 0)
#घोषणा VI6_RPF_SRC_ESIZE_EVSIZE_SHIFT	0

#घोषणा VI6_RPF_INFMT			0x0308
#घोषणा VI6_RPF_INFMT_VIR		BIT(28)
#घोषणा VI6_RPF_INFMT_CIPM		BIT(16)
#घोषणा VI6_RPF_INFMT_SPYCS		BIT(15)
#घोषणा VI6_RPF_INFMT_SPUVS		BIT(14)
#घोषणा VI6_RPF_INFMT_CEXT_ZERO		(0 << 12)
#घोषणा VI6_RPF_INFMT_CEXT_EXT		(1 << 12)
#घोषणा VI6_RPF_INFMT_CEXT_ONE		(2 << 12)
#घोषणा VI6_RPF_INFMT_CEXT_MASK		(3 << 12)
#घोषणा VI6_RPF_INFMT_RDTM_BT601	(0 << 9)
#घोषणा VI6_RPF_INFMT_RDTM_BT601_EXT	(1 << 9)
#घोषणा VI6_RPF_INFMT_RDTM_BT709	(2 << 9)
#घोषणा VI6_RPF_INFMT_RDTM_BT709_EXT	(3 << 9)
#घोषणा VI6_RPF_INFMT_RDTM_MASK		(7 << 9)
#घोषणा VI6_RPF_INFMT_CSC		BIT(8)
#घोषणा VI6_RPF_INFMT_RDFMT_MASK	(0x7f << 0)
#घोषणा VI6_RPF_INFMT_RDFMT_SHIFT	0

#घोषणा VI6_RPF_DSWAP			0x030c
#घोषणा VI6_RPF_DSWAP_A_LLS		BIT(11)
#घोषणा VI6_RPF_DSWAP_A_LWS		BIT(10)
#घोषणा VI6_RPF_DSWAP_A_WDS		BIT(9)
#घोषणा VI6_RPF_DSWAP_A_BTS		BIT(8)
#घोषणा VI6_RPF_DSWAP_P_LLS		BIT(3)
#घोषणा VI6_RPF_DSWAP_P_LWS		BIT(2)
#घोषणा VI6_RPF_DSWAP_P_WDS		BIT(1)
#घोषणा VI6_RPF_DSWAP_P_BTS		BIT(0)

#घोषणा VI6_RPF_LOC			0x0310
#घोषणा VI6_RPF_LOC_HCOORD_MASK		(0x1fff << 16)
#घोषणा VI6_RPF_LOC_HCOORD_SHIFT	16
#घोषणा VI6_RPF_LOC_VCOORD_MASK		(0x1fff << 0)
#घोषणा VI6_RPF_LOC_VCOORD_SHIFT	0

#घोषणा VI6_RPF_ALPH_SEL		0x0314
#घोषणा VI6_RPF_ALPH_SEL_ASEL_PACKED	(0 << 28)
#घोषणा VI6_RPF_ALPH_SEL_ASEL_8B_PLANE	(1 << 28)
#घोषणा VI6_RPF_ALPH_SEL_ASEL_SELECT	(2 << 28)
#घोषणा VI6_RPF_ALPH_SEL_ASEL_1B_PLANE	(3 << 28)
#घोषणा VI6_RPF_ALPH_SEL_ASEL_FIXED	(4 << 28)
#घोषणा VI6_RPF_ALPH_SEL_ASEL_MASK	(7 << 28)
#घोषणा VI6_RPF_ALPH_SEL_ASEL_SHIFT	28
#घोषणा VI6_RPF_ALPH_SEL_IROP_MASK	(0xf << 24)
#घोषणा VI6_RPF_ALPH_SEL_IROP_SHIFT	24
#घोषणा VI6_RPF_ALPH_SEL_BSEL		BIT(23)
#घोषणा VI6_RPF_ALPH_SEL_AEXT_ZERO	(0 << 18)
#घोषणा VI6_RPF_ALPH_SEL_AEXT_EXT	(1 << 18)
#घोषणा VI6_RPF_ALPH_SEL_AEXT_ONE	(2 << 18)
#घोषणा VI6_RPF_ALPH_SEL_AEXT_MASK	(3 << 18)
#घोषणा VI6_RPF_ALPH_SEL_ALPHA1_MASK	(0xff << 8)
#घोषणा VI6_RPF_ALPH_SEL_ALPHA1_SHIFT	8
#घोषणा VI6_RPF_ALPH_SEL_ALPHA0_MASK	(0xff << 0)
#घोषणा VI6_RPF_ALPH_SEL_ALPHA0_SHIFT	0

#घोषणा VI6_RPF_VRTCOL_SET		0x0318
#घोषणा VI6_RPF_VRTCOL_SET_LAYA_MASK	(0xff << 24)
#घोषणा VI6_RPF_VRTCOL_SET_LAYA_SHIFT	24
#घोषणा VI6_RPF_VRTCOL_SET_LAYR_MASK	(0xff << 16)
#घोषणा VI6_RPF_VRTCOL_SET_LAYR_SHIFT	16
#घोषणा VI6_RPF_VRTCOL_SET_LAYG_MASK	(0xff << 8)
#घोषणा VI6_RPF_VRTCOL_SET_LAYG_SHIFT	8
#घोषणा VI6_RPF_VRTCOL_SET_LAYB_MASK	(0xff << 0)
#घोषणा VI6_RPF_VRTCOL_SET_LAYB_SHIFT	0

#घोषणा VI6_RPF_MSK_CTRL		0x031c
#घोषणा VI6_RPF_MSK_CTRL_MSK_EN		BIT(24)
#घोषणा VI6_RPF_MSK_CTRL_MGR_MASK	(0xff << 16)
#घोषणा VI6_RPF_MSK_CTRL_MGR_SHIFT	16
#घोषणा VI6_RPF_MSK_CTRL_MGG_MASK	(0xff << 8)
#घोषणा VI6_RPF_MSK_CTRL_MGG_SHIFT	8
#घोषणा VI6_RPF_MSK_CTRL_MGB_MASK	(0xff << 0)
#घोषणा VI6_RPF_MSK_CTRL_MGB_SHIFT	0

#घोषणा VI6_RPF_MSK_SET0		0x0320
#घोषणा VI6_RPF_MSK_SET1		0x0324
#घोषणा VI6_RPF_MSK_SET_MSA_MASK	(0xff << 24)
#घोषणा VI6_RPF_MSK_SET_MSA_SHIFT	24
#घोषणा VI6_RPF_MSK_SET_MSR_MASK	(0xff << 16)
#घोषणा VI6_RPF_MSK_SET_MSR_SHIFT	16
#घोषणा VI6_RPF_MSK_SET_MSG_MASK	(0xff << 8)
#घोषणा VI6_RPF_MSK_SET_MSG_SHIFT	8
#घोषणा VI6_RPF_MSK_SET_MSB_MASK	(0xff << 0)
#घोषणा VI6_RPF_MSK_SET_MSB_SHIFT	0

#घोषणा VI6_RPF_CKEY_CTRL		0x0328
#घोषणा VI6_RPF_CKEY_CTRL_CV		BIT(4)
#घोषणा VI6_RPF_CKEY_CTRL_SAPE1		BIT(1)
#घोषणा VI6_RPF_CKEY_CTRL_SAPE0		BIT(0)

#घोषणा VI6_RPF_CKEY_SET0		0x032c
#घोषणा VI6_RPF_CKEY_SET1		0x0330
#घोषणा VI6_RPF_CKEY_SET_AP_MASK	(0xff << 24)
#घोषणा VI6_RPF_CKEY_SET_AP_SHIFT	24
#घोषणा VI6_RPF_CKEY_SET_R_MASK		(0xff << 16)
#घोषणा VI6_RPF_CKEY_SET_R_SHIFT	16
#घोषणा VI6_RPF_CKEY_SET_GY_MASK	(0xff << 8)
#घोषणा VI6_RPF_CKEY_SET_GY_SHIFT	8
#घोषणा VI6_RPF_CKEY_SET_B_MASK		(0xff << 0)
#घोषणा VI6_RPF_CKEY_SET_B_SHIFT	0

#घोषणा VI6_RPF_SRCM_PSTRIDE		0x0334
#घोषणा VI6_RPF_SRCM_PSTRIDE_Y_SHIFT	16
#घोषणा VI6_RPF_SRCM_PSTRIDE_C_SHIFT	0

#घोषणा VI6_RPF_SRCM_ASTRIDE		0x0338
#घोषणा VI6_RPF_SRCM_PSTRIDE_A_SHIFT	0

#घोषणा VI6_RPF_SRCM_ADDR_Y		0x033c
#घोषणा VI6_RPF_SRCM_ADDR_C0		0x0340
#घोषणा VI6_RPF_SRCM_ADDR_C1		0x0344
#घोषणा VI6_RPF_SRCM_ADDR_AI		0x0348

#घोषणा VI6_RPF_MULT_ALPHA		0x036c
#घोषणा VI6_RPF_MULT_ALPHA_A_MMD_NONE	(0 << 12)
#घोषणा VI6_RPF_MULT_ALPHA_A_MMD_RATIO	(1 << 12)
#घोषणा VI6_RPF_MULT_ALPHA_P_MMD_NONE	(0 << 8)
#घोषणा VI6_RPF_MULT_ALPHA_P_MMD_RATIO	(1 << 8)
#घोषणा VI6_RPF_MULT_ALPHA_P_MMD_IMAGE	(2 << 8)
#घोषणा VI6_RPF_MULT_ALPHA_P_MMD_BOTH	(3 << 8)
#घोषणा VI6_RPF_MULT_ALPHA_RATIO_MASK	(0xff << 0)
#घोषणा VI6_RPF_MULT_ALPHA_RATIO_SHIFT	0

/* -----------------------------------------------------------------------------
 * WPF Control Registers
 */

#घोषणा VI6_WPF_OFFSET			0x100

#घोषणा VI6_WPF_SRCRPF			0x1000
#घोषणा VI6_WPF_SRCRPF_VIRACT_DIS	(0 << 28)
#घोषणा VI6_WPF_SRCRPF_VIRACT_SUB	(1 << 28)
#घोषणा VI6_WPF_SRCRPF_VIRACT_MST	(2 << 28)
#घोषणा VI6_WPF_SRCRPF_VIRACT_MASK	(3 << 28)
#घोषणा VI6_WPF_SRCRPF_VIRACT2_DIS	(0 << 24)
#घोषणा VI6_WPF_SRCRPF_VIRACT2_SUB	(1 << 24)
#घोषणा VI6_WPF_SRCRPF_VIRACT2_MST	(2 << 24)
#घोषणा VI6_WPF_SRCRPF_VIRACT2_MASK	(3 << 24)
#घोषणा VI6_WPF_SRCRPF_RPF_ACT_DIS(n)	(0 << ((n) * 2))
#घोषणा VI6_WPF_SRCRPF_RPF_ACT_SUB(n)	(1 << ((n) * 2))
#घोषणा VI6_WPF_SRCRPF_RPF_ACT_MST(n)	(2 << ((n) * 2))
#घोषणा VI6_WPF_SRCRPF_RPF_ACT_MASK(n)	(3 << ((n) * 2))

#घोषणा VI6_WPF_HSZCLIP			0x1004
#घोषणा VI6_WPF_VSZCLIP			0x1008
#घोषणा VI6_WPF_SZCLIP_EN		BIT(28)
#घोषणा VI6_WPF_SZCLIP_OFST_MASK	(0xff << 16)
#घोषणा VI6_WPF_SZCLIP_OFST_SHIFT	16
#घोषणा VI6_WPF_SZCLIP_SIZE_MASK	(0xfff << 0)
#घोषणा VI6_WPF_SZCLIP_SIZE_SHIFT	0

#घोषणा VI6_WPF_OUTFMT			0x100c
#घोषणा VI6_WPF_OUTFMT_PDV_MASK		(0xff << 24)
#घोषणा VI6_WPF_OUTFMT_PDV_SHIFT	24
#घोषणा VI6_WPF_OUTFMT_PXA		BIT(23)
#घोषणा VI6_WPF_OUTFMT_ROT		BIT(18)
#घोषणा VI6_WPF_OUTFMT_HFLP		BIT(17)
#घोषणा VI6_WPF_OUTFMT_FLP		BIT(16)
#घोषणा VI6_WPF_OUTFMT_SPYCS		BIT(15)
#घोषणा VI6_WPF_OUTFMT_SPUVS		BIT(14)
#घोषणा VI6_WPF_OUTFMT_DITH_DIS		(0 << 12)
#घोषणा VI6_WPF_OUTFMT_DITH_EN		(3 << 12)
#घोषणा VI6_WPF_OUTFMT_DITH_MASK	(3 << 12)
#घोषणा VI6_WPF_OUTFMT_WRTM_BT601	(0 << 9)
#घोषणा VI6_WPF_OUTFMT_WRTM_BT601_EXT	(1 << 9)
#घोषणा VI6_WPF_OUTFMT_WRTM_BT709	(2 << 9)
#घोषणा VI6_WPF_OUTFMT_WRTM_BT709_EXT	(3 << 9)
#घोषणा VI6_WPF_OUTFMT_WRTM_MASK	(7 << 9)
#घोषणा VI6_WPF_OUTFMT_CSC		BIT(8)
#घोषणा VI6_WPF_OUTFMT_WRFMT_MASK	(0x7f << 0)
#घोषणा VI6_WPF_OUTFMT_WRFMT_SHIFT	0

#घोषणा VI6_WPF_DSWAP			0x1010
#घोषणा VI6_WPF_DSWAP_P_LLS		BIT(3)
#घोषणा VI6_WPF_DSWAP_P_LWS		BIT(2)
#घोषणा VI6_WPF_DSWAP_P_WDS		BIT(1)
#घोषणा VI6_WPF_DSWAP_P_BTS		BIT(0)

#घोषणा VI6_WPF_RNDCTRL			0x1014
#घोषणा VI6_WPF_RNDCTRL_CBRM		BIT(28)
#घोषणा VI6_WPF_RNDCTRL_ABRM_TRUNC	(0 << 24)
#घोषणा VI6_WPF_RNDCTRL_ABRM_ROUND	(1 << 24)
#घोषणा VI6_WPF_RNDCTRL_ABRM_THRESH	(2 << 24)
#घोषणा VI6_WPF_RNDCTRL_ABRM_MASK	(3 << 24)
#घोषणा VI6_WPF_RNDCTRL_ATHRESH_MASK	(0xff << 16)
#घोषणा VI6_WPF_RNDCTRL_ATHRESH_SHIFT	16
#घोषणा VI6_WPF_RNDCTRL_CLMD_FULL	(0 << 12)
#घोषणा VI6_WPF_RNDCTRL_CLMD_CLIP	(1 << 12)
#घोषणा VI6_WPF_RNDCTRL_CLMD_EXT	(2 << 12)
#घोषणा VI6_WPF_RNDCTRL_CLMD_MASK	(3 << 12)

#घोषणा VI6_WPF_ROT_CTRL		0x1018
#घोषणा VI6_WPF_ROT_CTRL_LN16		BIT(17)
#घोषणा VI6_WPF_ROT_CTRL_LMEM_WD_MASK	(0x1fff << 0)
#घोषणा VI6_WPF_ROT_CTRL_LMEM_WD_SHIFT	0

#घोषणा VI6_WPF_DSTM_STRIDE_Y		0x101c
#घोषणा VI6_WPF_DSTM_STRIDE_C		0x1020
#घोषणा VI6_WPF_DSTM_ADDR_Y		0x1024
#घोषणा VI6_WPF_DSTM_ADDR_C0		0x1028
#घोषणा VI6_WPF_DSTM_ADDR_C1		0x102c

#घोषणा VI6_WPF_WRBCK_CTRL(n)		(0x1034 + (n) * 0x100)
#घोषणा VI6_WPF_WRBCK_CTRL_WBMD		BIT(0)

/* -----------------------------------------------------------------------------
 * UIF Control Registers
 */

#घोषणा VI6_UIF_OFFSET			0x100

#घोषणा VI6_UIF_DISCOM_DOCMCR		0x1c00
#घोषणा VI6_UIF_DISCOM_DOCMCR_CMPRU	BIT(16)
#घोषणा VI6_UIF_DISCOM_DOCMCR_CMPR	BIT(0)

#घोषणा VI6_UIF_DISCOM_DOCMSTR		0x1c04
#घोषणा VI6_UIF_DISCOM_DOCMSTR_CMPPRE	BIT(1)
#घोषणा VI6_UIF_DISCOM_DOCMSTR_CMPST	BIT(0)

#घोषणा VI6_UIF_DISCOM_DOCMCLSTR	0x1c08
#घोषणा VI6_UIF_DISCOM_DOCMCLSTR_CMPCLPRE	BIT(1)
#घोषणा VI6_UIF_DISCOM_DOCMCLSTR_CMPCLST	BIT(0)

#घोषणा VI6_UIF_DISCOM_DOCMIENR		0x1c0c
#घोषणा VI6_UIF_DISCOM_DOCMIENR_CMPPREIEN	BIT(1)
#घोषणा VI6_UIF_DISCOM_DOCMIENR_CMPIEN		BIT(0)

#घोषणा VI6_UIF_DISCOM_DOCMMDR		0x1c10
#घोषणा VI6_UIF_DISCOM_DOCMMDR_INTHRH(n)	((n) << 16)

#घोषणा VI6_UIF_DISCOM_DOCMPMR		0x1c14
#घोषणा VI6_UIF_DISCOM_DOCMPMR_CMPDFF(n)	((n) << 17)
#घोषणा VI6_UIF_DISCOM_DOCMPMR_CMPDFA(n)	((n) << 8)
#घोषणा VI6_UIF_DISCOM_DOCMPMR_CMPDAUF		BIT(7)
#घोषणा VI6_UIF_DISCOM_DOCMPMR_SEL(n)		((n) << 0)

#घोषणा VI6_UIF_DISCOM_DOCMECRCR	0x1c18
#घोषणा VI6_UIF_DISCOM_DOCMCCRCR	0x1c1c
#घोषणा VI6_UIF_DISCOM_DOCMSPXR		0x1c20
#घोषणा VI6_UIF_DISCOM_DOCMSPYR		0x1c24
#घोषणा VI6_UIF_DISCOM_DOCMSZXR		0x1c28
#घोषणा VI6_UIF_DISCOM_DOCMSZYR		0x1c2c

/* -----------------------------------------------------------------------------
 * DPR Control Registers
 */

#घोषणा VI6_DPR_RPF_ROUTE(n)		(0x2000 + (n) * 4)

#घोषणा VI6_DPR_WPF_FPORCH(n)		(0x2014 + (n) * 4)
#घोषणा VI6_DPR_WPF_FPORCH_FP_WPFN	(5 << 8)

#घोषणा VI6_DPR_SRU_ROUTE		0x2024
#घोषणा VI6_DPR_UDS_ROUTE(n)		(0x2028 + (n) * 4)
#घोषणा VI6_DPR_LUT_ROUTE		0x203c
#घोषणा VI6_DPR_CLU_ROUTE		0x2040
#घोषणा VI6_DPR_HST_ROUTE		0x2044
#घोषणा VI6_DPR_HSI_ROUTE		0x2048
#घोषणा VI6_DPR_BRU_ROUTE		0x204c
#घोषणा VI6_DPR_ILV_BRS_ROUTE		0x2050
#घोषणा VI6_DPR_ROUTE_BRSSEL		BIT(28)
#घोषणा VI6_DPR_ROUTE_FXA_MASK		(0xff << 16)
#घोषणा VI6_DPR_ROUTE_FXA_SHIFT		16
#घोषणा VI6_DPR_ROUTE_FP_MASK		(0x3f << 8)
#घोषणा VI6_DPR_ROUTE_FP_SHIFT		8
#घोषणा VI6_DPR_ROUTE_RT_MASK		(0x3f << 0)
#घोषणा VI6_DPR_ROUTE_RT_SHIFT		0

#घोषणा VI6_DPR_HGO_SMPPT		0x2054
#घोषणा VI6_DPR_HGT_SMPPT		0x2058
#घोषणा VI6_DPR_SMPPT_TGW_MASK		(7 << 8)
#घोषणा VI6_DPR_SMPPT_TGW_SHIFT		8
#घोषणा VI6_DPR_SMPPT_PT_MASK		(0x3f << 0)
#घोषणा VI6_DPR_SMPPT_PT_SHIFT		0

#घोषणा VI6_DPR_UIF_ROUTE(n)		(0x2074 + (n) * 4)

#घोषणा VI6_DPR_NODE_RPF(n)		(n)
#घोषणा VI6_DPR_NODE_UIF(n)		(12 + (n))
#घोषणा VI6_DPR_NODE_SRU		16
#घोषणा VI6_DPR_NODE_UDS(n)		(17 + (n))
#घोषणा VI6_DPR_NODE_LUT		22
#घोषणा VI6_DPR_NODE_BRU_IN(n)		(((n) <= 3) ? 23 + (n) : 49)
#घोषणा VI6_DPR_NODE_BRU_OUT		27
#घोषणा VI6_DPR_NODE_CLU		29
#घोषणा VI6_DPR_NODE_HST		30
#घोषणा VI6_DPR_NODE_HSI		31
#घोषणा VI6_DPR_NODE_BRS_IN(n)		(38 + (n))
#घोषणा VI6_DPR_NODE_LIF		55		/* Gen2 only */
#घोषणा VI6_DPR_NODE_WPF(n)		(56 + (n))
#घोषणा VI6_DPR_NODE_UNUSED		63

/* -----------------------------------------------------------------------------
 * SRU Control Registers
 */

#घोषणा VI6_SRU_CTRL0			0x2200
#घोषणा VI6_SRU_CTRL0_PARAM0_MASK	(0x1ff << 16)
#घोषणा VI6_SRU_CTRL0_PARAM0_SHIFT	16
#घोषणा VI6_SRU_CTRL0_PARAM1_MASK	(0x1f << 8)
#घोषणा VI6_SRU_CTRL0_PARAM1_SHIFT	8
#घोषणा VI6_SRU_CTRL0_MODE_UPSCALE	(4 << 4)
#घोषणा VI6_SRU_CTRL0_PARAM2		BIT(3)
#घोषणा VI6_SRU_CTRL0_PARAM3		BIT(2)
#घोषणा VI6_SRU_CTRL0_PARAM4		BIT(1)
#घोषणा VI6_SRU_CTRL0_EN		BIT(0)

#घोषणा VI6_SRU_CTRL1			0x2204
#घोषणा VI6_SRU_CTRL1_PARAM5		0x7ff

#घोषणा VI6_SRU_CTRL2			0x2208
#घोषणा VI6_SRU_CTRL2_PARAM6_SHIFT	16
#घोषणा VI6_SRU_CTRL2_PARAM7_SHIFT	8
#घोषणा VI6_SRU_CTRL2_PARAM8_SHIFT	0

/* -----------------------------------------------------------------------------
 * UDS Control Registers
 */

#घोषणा VI6_UDS_OFFSET			0x100

#घोषणा VI6_UDS_CTRL			0x2300
#घोषणा VI6_UDS_CTRL_AMD		BIT(30)
#घोषणा VI6_UDS_CTRL_FMD		BIT(29)
#घोषणा VI6_UDS_CTRL_BLADV		BIT(28)
#घोषणा VI6_UDS_CTRL_AON		BIT(25)
#घोषणा VI6_UDS_CTRL_ATHON		BIT(24)
#घोषणा VI6_UDS_CTRL_BC			BIT(20)
#घोषणा VI6_UDS_CTRL_NE_A		BIT(19)
#घोषणा VI6_UDS_CTRL_NE_RCR		BIT(18)
#घोषणा VI6_UDS_CTRL_NE_GY		BIT(17)
#घोषणा VI6_UDS_CTRL_NE_BCB		BIT(16)
#घोषणा VI6_UDS_CTRL_AMDSLH		BIT(2)
#घोषणा VI6_UDS_CTRL_TDIPC		BIT(1)

#घोषणा VI6_UDS_SCALE			0x2304
#घोषणा VI6_UDS_SCALE_HMANT_MASK	(0xf << 28)
#घोषणा VI6_UDS_SCALE_HMANT_SHIFT	28
#घोषणा VI6_UDS_SCALE_HFRAC_MASK	(0xfff << 16)
#घोषणा VI6_UDS_SCALE_HFRAC_SHIFT	16
#घोषणा VI6_UDS_SCALE_VMANT_MASK	(0xf << 12)
#घोषणा VI6_UDS_SCALE_VMANT_SHIFT	12
#घोषणा VI6_UDS_SCALE_VFRAC_MASK	(0xfff << 0)
#घोषणा VI6_UDS_SCALE_VFRAC_SHIFT	0

#घोषणा VI6_UDS_ALPTH			0x2308
#घोषणा VI6_UDS_ALPTH_TH1_MASK		(0xff << 8)
#घोषणा VI6_UDS_ALPTH_TH1_SHIFT		8
#घोषणा VI6_UDS_ALPTH_TH0_MASK		(0xff << 0)
#घोषणा VI6_UDS_ALPTH_TH0_SHIFT		0

#घोषणा VI6_UDS_ALPVAL			0x230c
#घोषणा VI6_UDS_ALPVAL_VAL2_MASK	(0xff << 16)
#घोषणा VI6_UDS_ALPVAL_VAL2_SHIFT	16
#घोषणा VI6_UDS_ALPVAL_VAL1_MASK	(0xff << 8)
#घोषणा VI6_UDS_ALPVAL_VAL1_SHIFT	8
#घोषणा VI6_UDS_ALPVAL_VAL0_MASK	(0xff << 0)
#घोषणा VI6_UDS_ALPVAL_VAL0_SHIFT	0

#घोषणा VI6_UDS_PASS_BWIDTH		0x2310
#घोषणा VI6_UDS_PASS_BWIDTH_H_MASK	(0x7f << 16)
#घोषणा VI6_UDS_PASS_BWIDTH_H_SHIFT	16
#घोषणा VI6_UDS_PASS_BWIDTH_V_MASK	(0x7f << 0)
#घोषणा VI6_UDS_PASS_BWIDTH_V_SHIFT	0

#घोषणा VI6_UDS_HPHASE			0x2314
#घोषणा VI6_UDS_HPHASE_HSTP_MASK	(0xfff << 16)
#घोषणा VI6_UDS_HPHASE_HSTP_SHIFT	16
#घोषणा VI6_UDS_HPHASE_HEDP_MASK	(0xfff << 0)
#घोषणा VI6_UDS_HPHASE_HEDP_SHIFT	0

#घोषणा VI6_UDS_IPC			0x2318
#घोषणा VI6_UDS_IPC_FIELD		BIT(27)
#घोषणा VI6_UDS_IPC_VEDP_MASK		(0xfff << 0)
#घोषणा VI6_UDS_IPC_VEDP_SHIFT		0

#घोषणा VI6_UDS_HSZCLIP			0x231c
#घोषणा VI6_UDS_HSZCLIP_HCEN		BIT(28)
#घोषणा VI6_UDS_HSZCLIP_HCL_OFST_MASK	(0xff << 16)
#घोषणा VI6_UDS_HSZCLIP_HCL_OFST_SHIFT	16
#घोषणा VI6_UDS_HSZCLIP_HCL_SIZE_MASK	(0x1fff << 0)
#घोषणा VI6_UDS_HSZCLIP_HCL_SIZE_SHIFT	0

#घोषणा VI6_UDS_CLIP_SIZE		0x2324
#घोषणा VI6_UDS_CLIP_SIZE_HSIZE_MASK	(0x1fff << 16)
#घोषणा VI6_UDS_CLIP_SIZE_HSIZE_SHIFT	16
#घोषणा VI6_UDS_CLIP_SIZE_VSIZE_MASK	(0x1fff << 0)
#घोषणा VI6_UDS_CLIP_SIZE_VSIZE_SHIFT	0

#घोषणा VI6_UDS_FILL_COLOR		0x2328
#घोषणा VI6_UDS_FILL_COLOR_RFILC_MASK	(0xff << 16)
#घोषणा VI6_UDS_FILL_COLOR_RFILC_SHIFT	16
#घोषणा VI6_UDS_FILL_COLOR_GFILC_MASK	(0xff << 8)
#घोषणा VI6_UDS_FILL_COLOR_GFILC_SHIFT	8
#घोषणा VI6_UDS_FILL_COLOR_BFILC_MASK	(0xff << 0)
#घोषणा VI6_UDS_FILL_COLOR_BFILC_SHIFT	0

/* -----------------------------------------------------------------------------
 * LUT Control Registers
 */

#घोषणा VI6_LUT_CTRL			0x2800
#घोषणा VI6_LUT_CTRL_EN			BIT(0)

/* -----------------------------------------------------------------------------
 * CLU Control Registers
 */

#घोषणा VI6_CLU_CTRL			0x2900
#घोषणा VI6_CLU_CTRL_AAI		BIT(28)
#घोषणा VI6_CLU_CTRL_MVS		BIT(24)
#घोषणा VI6_CLU_CTRL_AX1I_2D		(3 << 14)
#घोषणा VI6_CLU_CTRL_AX2I_2D		(1 << 12)
#घोषणा VI6_CLU_CTRL_OS0_2D		(3 << 8)
#घोषणा VI6_CLU_CTRL_OS1_2D		(1 << 6)
#घोषणा VI6_CLU_CTRL_OS2_2D		(3 << 4)
#घोषणा VI6_CLU_CTRL_M2D		BIT(1)
#घोषणा VI6_CLU_CTRL_EN			BIT(0)

/* -----------------------------------------------------------------------------
 * HST Control Registers
 */

#घोषणा VI6_HST_CTRL			0x2a00
#घोषणा VI6_HST_CTRL_EN			BIT(0)

/* -----------------------------------------------------------------------------
 * HSI Control Registers
 */

#घोषणा VI6_HSI_CTRL			0x2b00
#घोषणा VI6_HSI_CTRL_EN			BIT(0)

/* -----------------------------------------------------------------------------
 * BRS and BRU Control Registers
 */

#घोषणा VI6_ROP_NOP			0
#घोषणा VI6_ROP_AND			1
#घोषणा VI6_ROP_AND_REV			2
#घोषणा VI6_ROP_COPY			3
#घोषणा VI6_ROP_AND_INV			4
#घोषणा VI6_ROP_CLEAR			5
#घोषणा VI6_ROP_XOR			6
#घोषणा VI6_ROP_OR			7
#घोषणा VI6_ROP_NOR			8
#घोषणा VI6_ROP_EQUIV			9
#घोषणा VI6_ROP_INVERT			10
#घोषणा VI6_ROP_OR_REV			11
#घोषणा VI6_ROP_COPY_INV		12
#घोषणा VI6_ROP_OR_INV			13
#घोषणा VI6_ROP_न_अंकD			14
#घोषणा VI6_ROP_SET			15

#घोषणा VI6_BRU_BASE			0x2c00
#घोषणा VI6_BRS_BASE			0x3900

#घोषणा VI6_BRU_INCTRL			0x0000
#घोषणा VI6_BRU_INCTRL_NRM		BIT(28)
#घोषणा VI6_BRU_INCTRL_DnON		(1 << (16 + (n)))
#घोषणा VI6_BRU_INCTRL_DITHn_OFF	(0 << ((n) * 4))
#घोषणा VI6_BRU_INCTRL_DITHn_18BPP	(1 << ((n) * 4))
#घोषणा VI6_BRU_INCTRL_DITHn_16BPP	(2 << ((n) * 4))
#घोषणा VI6_BRU_INCTRL_DITHn_15BPP	(3 << ((n) * 4))
#घोषणा VI6_BRU_INCTRL_DITHn_12BPP	(4 << ((n) * 4))
#घोषणा VI6_BRU_INCTRL_DITHn_8BPP	(5 << ((n) * 4))
#घोषणा VI6_BRU_INCTRL_DITHn_MASK	(7 << ((n) * 4))
#घोषणा VI6_BRU_INCTRL_DITHn_SHIFT	((n) * 4)

#घोषणा VI6_BRU_VIRRPF_SIZE		0x0004
#घोषणा VI6_BRU_VIRRPF_SIZE_HSIZE_MASK	(0x1fff << 16)
#घोषणा VI6_BRU_VIRRPF_SIZE_HSIZE_SHIFT	16
#घोषणा VI6_BRU_VIRRPF_SIZE_VSIZE_MASK	(0x1fff << 0)
#घोषणा VI6_BRU_VIRRPF_SIZE_VSIZE_SHIFT	0

#घोषणा VI6_BRU_VIRRPF_LOC		0x0008
#घोषणा VI6_BRU_VIRRPF_LOC_HCOORD_MASK	(0x1fff << 16)
#घोषणा VI6_BRU_VIRRPF_LOC_HCOORD_SHIFT	16
#घोषणा VI6_BRU_VIRRPF_LOC_VCOORD_MASK	(0x1fff << 0)
#घोषणा VI6_BRU_VIRRPF_LOC_VCOORD_SHIFT	0

#घोषणा VI6_BRU_VIRRPF_COL		0x000c
#घोषणा VI6_BRU_VIRRPF_COL_A_MASK	(0xff << 24)
#घोषणा VI6_BRU_VIRRPF_COL_A_SHIFT	24
#घोषणा VI6_BRU_VIRRPF_COL_RCR_MASK	(0xff << 16)
#घोषणा VI6_BRU_VIRRPF_COL_RCR_SHIFT	16
#घोषणा VI6_BRU_VIRRPF_COL_GY_MASK	(0xff << 8)
#घोषणा VI6_BRU_VIRRPF_COL_GY_SHIFT	8
#घोषणा VI6_BRU_VIRRPF_COL_BCB_MASK	(0xff << 0)
#घोषणा VI6_BRU_VIRRPF_COL_BCB_SHIFT	0

#घोषणा VI6_BRU_CTRL(n)			(0x0010 + (n) * 8 + ((n) <= 3 ? 0 : 4))
#घोषणा VI6_BRU_CTRL_RBC		BIT(31)
#घोषणा VI6_BRU_CTRL_DSTSEL_BRUIN(n)	(((n) <= 3 ? (n) : (n)+1) << 20)
#घोषणा VI6_BRU_CTRL_DSTSEL_VRPF	(4 << 20)
#घोषणा VI6_BRU_CTRL_DSTSEL_MASK	(7 << 20)
#घोषणा VI6_BRU_CTRL_SRCSEL_BRUIN(n)	(((n) <= 3 ? (n) : (n)+1) << 16)
#घोषणा VI6_BRU_CTRL_SRCSEL_VRPF	(4 << 16)
#घोषणा VI6_BRU_CTRL_SRCSEL_MASK	(7 << 16)
#घोषणा VI6_BRU_CTRL_CROP(rop)		((rop) << 4)
#घोषणा VI6_BRU_CTRL_CROP_MASK		(0xf << 4)
#घोषणा VI6_BRU_CTRL_AROP(rop)		((rop) << 0)
#घोषणा VI6_BRU_CTRL_AROP_MASK		(0xf << 0)

#घोषणा VI6_BRU_BLD(n)			(0x0014 + (n) * 8 + ((n) <= 3 ? 0 : 4))
#घोषणा VI6_BRU_BLD_CBES		BIT(31)
#घोषणा VI6_BRU_BLD_CCMDX_DST_A		(0 << 28)
#घोषणा VI6_BRU_BLD_CCMDX_255_DST_A	(1 << 28)
#घोषणा VI6_BRU_BLD_CCMDX_SRC_A		(2 << 28)
#घोषणा VI6_BRU_BLD_CCMDX_255_SRC_A	(3 << 28)
#घोषणा VI6_BRU_BLD_CCMDX_COEFX		(4 << 28)
#घोषणा VI6_BRU_BLD_CCMDX_MASK		(7 << 28)
#घोषणा VI6_BRU_BLD_CCMDY_DST_A		(0 << 24)
#घोषणा VI6_BRU_BLD_CCMDY_255_DST_A	(1 << 24)
#घोषणा VI6_BRU_BLD_CCMDY_SRC_A		(2 << 24)
#घोषणा VI6_BRU_BLD_CCMDY_255_SRC_A	(3 << 24)
#घोषणा VI6_BRU_BLD_CCMDY_COEFY		(4 << 24)
#घोषणा VI6_BRU_BLD_CCMDY_MASK		(7 << 24)
#घोषणा VI6_BRU_BLD_CCMDY_SHIFT		24
#घोषणा VI6_BRU_BLD_ABES		BIT(23)
#घोषणा VI6_BRU_BLD_ACMDX_DST_A		(0 << 20)
#घोषणा VI6_BRU_BLD_ACMDX_255_DST_A	(1 << 20)
#घोषणा VI6_BRU_BLD_ACMDX_SRC_A		(2 << 20)
#घोषणा VI6_BRU_BLD_ACMDX_255_SRC_A	(3 << 20)
#घोषणा VI6_BRU_BLD_ACMDX_COEFX		(4 << 20)
#घोषणा VI6_BRU_BLD_ACMDX_MASK		(7 << 20)
#घोषणा VI6_BRU_BLD_ACMDY_DST_A		(0 << 16)
#घोषणा VI6_BRU_BLD_ACMDY_255_DST_A	(1 << 16)
#घोषणा VI6_BRU_BLD_ACMDY_SRC_A		(2 << 16)
#घोषणा VI6_BRU_BLD_ACMDY_255_SRC_A	(3 << 16)
#घोषणा VI6_BRU_BLD_ACMDY_COEFY		(4 << 16)
#घोषणा VI6_BRU_BLD_ACMDY_MASK		(7 << 16)
#घोषणा VI6_BRU_BLD_COEFX_MASK		(0xff << 8)
#घोषणा VI6_BRU_BLD_COEFX_SHIFT		8
#घोषणा VI6_BRU_BLD_COEFY_MASK		(0xff << 0)
#घोषणा VI6_BRU_BLD_COEFY_SHIFT		0

#घोषणा VI6_BRU_ROP			0x0030	/* Only available on BRU */
#घोषणा VI6_BRU_ROP_DSTSEL_BRUIN(n)	(((n) <= 3 ? (n) : (n)+1) << 20)
#घोषणा VI6_BRU_ROP_DSTSEL_VRPF		(4 << 20)
#घोषणा VI6_BRU_ROP_DSTSEL_MASK		(7 << 20)
#घोषणा VI6_BRU_ROP_CROP(rop)		((rop) << 4)
#घोषणा VI6_BRU_ROP_CROP_MASK		(0xf << 4)
#घोषणा VI6_BRU_ROP_AROP(rop)		((rop) << 0)
#घोषणा VI6_BRU_ROP_AROP_MASK		(0xf << 0)

/* -----------------------------------------------------------------------------
 * HGO Control Registers
 */

#घोषणा VI6_HGO_OFFSET			0x3000
#घोषणा VI6_HGO_OFFSET_HOFFSET_SHIFT	16
#घोषणा VI6_HGO_OFFSET_VOFFSET_SHIFT	0
#घोषणा VI6_HGO_SIZE			0x3004
#घोषणा VI6_HGO_SIZE_HSIZE_SHIFT	16
#घोषणा VI6_HGO_SIZE_VSIZE_SHIFT	0
#घोषणा VI6_HGO_MODE			0x3008
#घोषणा VI6_HGO_MODE_STEP		BIT(10)
#घोषणा VI6_HGO_MODE_MAXRGB		BIT(7)
#घोषणा VI6_HGO_MODE_OFSB_R		BIT(6)
#घोषणा VI6_HGO_MODE_OFSB_G		BIT(5)
#घोषणा VI6_HGO_MODE_OFSB_B		BIT(4)
#घोषणा VI6_HGO_MODE_HRATIO_SHIFT	2
#घोषणा VI6_HGO_MODE_VRATIO_SHIFT	0
#घोषणा VI6_HGO_LB_TH			0x300c
#घोषणा VI6_HGO_LBn_H(n)		(0x3010 + (n) * 8)
#घोषणा VI6_HGO_LBn_V(n)		(0x3014 + (n) * 8)
#घोषणा VI6_HGO_R_HISTO(n)		(0x3030 + (n) * 4)
#घोषणा VI6_HGO_R_MAXMIN		0x3130
#घोषणा VI6_HGO_R_SUM			0x3134
#घोषणा VI6_HGO_R_LB_DET		0x3138
#घोषणा VI6_HGO_G_HISTO(n)		(0x3140 + (n) * 4)
#घोषणा VI6_HGO_G_MAXMIN		0x3240
#घोषणा VI6_HGO_G_SUM			0x3244
#घोषणा VI6_HGO_G_LB_DET		0x3248
#घोषणा VI6_HGO_B_HISTO(n)		(0x3250 + (n) * 4)
#घोषणा VI6_HGO_B_MAXMIN		0x3350
#घोषणा VI6_HGO_B_SUM			0x3354
#घोषणा VI6_HGO_B_LB_DET		0x3358
#घोषणा VI6_HGO_EXT_HIST_ADDR		0x335c
#घोषणा VI6_HGO_EXT_HIST_DATA		0x3360
#घोषणा VI6_HGO_REGRST			0x33fc
#घोषणा VI6_HGO_REGRST_RCLEA		BIT(0)

/* -----------------------------------------------------------------------------
 * HGT Control Registers
 */

#घोषणा VI6_HGT_OFFSET			0x3400
#घोषणा VI6_HGT_OFFSET_HOFFSET_SHIFT	16
#घोषणा VI6_HGT_OFFSET_VOFFSET_SHIFT	0
#घोषणा VI6_HGT_SIZE			0x3404
#घोषणा VI6_HGT_SIZE_HSIZE_SHIFT	16
#घोषणा VI6_HGT_SIZE_VSIZE_SHIFT	0
#घोषणा VI6_HGT_MODE			0x3408
#घोषणा VI6_HGT_MODE_HRATIO_SHIFT	2
#घोषणा VI6_HGT_MODE_VRATIO_SHIFT	0
#घोषणा VI6_HGT_HUE_AREA(n)		(0x340c + (n) * 4)
#घोषणा VI6_HGT_HUE_AREA_LOWER_SHIFT	16
#घोषणा VI6_HGT_HUE_AREA_UPPER_SHIFT	0
#घोषणा VI6_HGT_LB_TH			0x3424
#घोषणा VI6_HGT_LBn_H(n)		(0x3428 + (n) * 8)
#घोषणा VI6_HGT_LBn_V(n)		(0x342c + (n) * 8)
#घोषणा VI6_HGT_HISTO(m, n)		(0x3450 + (m) * 128 + (n) * 4)
#घोषणा VI6_HGT_MAXMIN			0x3750
#घोषणा VI6_HGT_SUM			0x3754
#घोषणा VI6_HGT_LB_DET			0x3758
#घोषणा VI6_HGT_REGRST			0x37fc
#घोषणा VI6_HGT_REGRST_RCLEA		BIT(0)

/* -----------------------------------------------------------------------------
 * LIF Control Registers
 */

#घोषणा VI6_LIF_OFFSET			(-0x100)

#घोषणा VI6_LIF_CTRL			0x3b00
#घोषणा VI6_LIF_CTRL_OBTH_MASK		(0x7ff << 16)
#घोषणा VI6_LIF_CTRL_OBTH_SHIFT		16
#घोषणा VI6_LIF_CTRL_CFMT		BIT(4)
#घोषणा VI6_LIF_CTRL_REQSEL		BIT(1)
#घोषणा VI6_LIF_CTRL_LIF_EN		BIT(0)

#घोषणा VI6_LIF_CSBTH			0x3b04
#घोषणा VI6_LIF_CSBTH_HBTH_MASK		(0x7ff << 16)
#घोषणा VI6_LIF_CSBTH_HBTH_SHIFT	16
#घोषणा VI6_LIF_CSBTH_LBTH_MASK		(0x7ff << 0)
#घोषणा VI6_LIF_CSBTH_LBTH_SHIFT	0

#घोषणा VI6_LIF_LBA			0x3b0c
#घोषणा VI6_LIF_LBA_LBA0		BIT(31)
#घोषणा VI6_LIF_LBA_LBA1_MASK		(0xfff << 16)
#घोषणा VI6_LIF_LBA_LBA1_SHIFT		16

/* -----------------------------------------------------------------------------
 * Security Control Registers
 */

#घोषणा VI6_SECURITY_CTRL0		0x3d00
#घोषणा VI6_SECURITY_CTRL1		0x3d04

/* -----------------------------------------------------------------------------
 * IP Version Registers
 */

#घोषणा VI6_IP_VERSION			0x3f00
#घोषणा VI6_IP_VERSION_MASK		(0xffff << 0)
#घोषणा VI6_IP_VERSION_MODEL_MASK	(0xff << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPS_H2	(0x09 << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPR_H2	(0x0a << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPD_GEN2	(0x0b << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPS_M2	(0x0c << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPS_V2H	(0x12 << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPD_V2H	(0x13 << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPI_GEN3	(0x14 << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPBD_GEN3	(0x15 << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPBC_GEN3	(0x16 << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPD_GEN3	(0x17 << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPD_V3	(0x18 << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPDL_GEN3	(0x19 << 8)
#घोषणा VI6_IP_VERSION_MODEL_VSPBS_GEN3	(0x1a << 8)
#घोषणा VI6_IP_VERSION_SOC_MASK		(0xff << 0)
#घोषणा VI6_IP_VERSION_SOC_H2		(0x01 << 0)
#घोषणा VI6_IP_VERSION_SOC_V2H		(0x01 << 0)
#घोषणा VI6_IP_VERSION_SOC_V3M		(0x01 << 0)
#घोषणा VI6_IP_VERSION_SOC_M2		(0x02 << 0)
#घोषणा VI6_IP_VERSION_SOC_M3W		(0x02 << 0)
#घोषणा VI6_IP_VERSION_SOC_V3H		(0x02 << 0)
#घोषणा VI6_IP_VERSION_SOC_H3		(0x03 << 0)
#घोषणा VI6_IP_VERSION_SOC_D3		(0x04 << 0)
#घोषणा VI6_IP_VERSION_SOC_M3N		(0x04 << 0)
#घोषणा VI6_IP_VERSION_SOC_E3		(0x04 << 0)

/* -----------------------------------------------------------------------------
 * RPF CLUT Registers
 */

#घोषणा VI6_CLUT_TABLE			0x4000

/* -----------------------------------------------------------------------------
 * 1D LUT Registers
 */

#घोषणा VI6_LUT_TABLE			0x7000

/* -----------------------------------------------------------------------------
 * 3D LUT Registers
 */

#घोषणा VI6_CLU_ADDR			0x7400
#घोषणा VI6_CLU_DATA			0x7404

/* -----------------------------------------------------------------------------
 * Formats
 */

#घोषणा VI6_FMT_RGB_332			0x00
#घोषणा VI6_FMT_XRGB_4444		0x01
#घोषणा VI6_FMT_RGBX_4444		0x02
#घोषणा VI6_FMT_XRGB_1555		0x04
#घोषणा VI6_FMT_RGBX_5551		0x05
#घोषणा VI6_FMT_RGB_565			0x06
#घोषणा VI6_FMT_AXRGB_86666		0x07
#घोषणा VI6_FMT_RGBXA_66668		0x08
#घोषणा VI6_FMT_XRGBA_66668		0x09
#घोषणा VI6_FMT_ARGBX_86666		0x0a
#घोषणा VI6_FMT_AXRXGXB_8262626		0x0b
#घोषणा VI6_FMT_XRXGXBA_2626268		0x0c
#घोषणा VI6_FMT_ARXGXBX_8626262		0x0d
#घोषणा VI6_FMT_RXGXBXA_6262628		0x0e
#घोषणा VI6_FMT_XRGB_6666		0x0f
#घोषणा VI6_FMT_RGBX_6666		0x10
#घोषणा VI6_FMT_XRXGXB_262626		0x11
#घोषणा VI6_FMT_RXGXBX_626262		0x12
#घोषणा VI6_FMT_ARGB_8888		0x13
#घोषणा VI6_FMT_RGBA_8888		0x14
#घोषणा VI6_FMT_RGB_888			0x15
#घोषणा VI6_FMT_XRGXGB_763763		0x16
#घोषणा VI6_FMT_XXRGB_86666		0x17
#घोषणा VI6_FMT_BGR_888			0x18
#घोषणा VI6_FMT_ARGB_4444		0x19
#घोषणा VI6_FMT_RGBA_4444		0x1a
#घोषणा VI6_FMT_ARGB_1555		0x1b
#घोषणा VI6_FMT_RGBA_5551		0x1c
#घोषणा VI6_FMT_ABGR_4444		0x1d
#घोषणा VI6_FMT_BGRA_4444		0x1e
#घोषणा VI6_FMT_ABGR_1555		0x1f
#घोषणा VI6_FMT_BGRA_5551		0x20
#घोषणा VI6_FMT_XBXGXR_262626		0x21
#घोषणा VI6_FMT_ABGR_8888		0x22
#घोषणा VI6_FMT_XXRGB_88565		0x23

#घोषणा VI6_FMT_Y_UV_444		0x40
#घोषणा VI6_FMT_Y_UV_422		0x41
#घोषणा VI6_FMT_Y_UV_420		0x42
#घोषणा VI6_FMT_YUV_444			0x46
#घोषणा VI6_FMT_YUYV_422		0x47
#घोषणा VI6_FMT_YYUV_422		0x48
#घोषणा VI6_FMT_YUV_420			0x49
#घोषणा VI6_FMT_Y_U_V_444		0x4a
#घोषणा VI6_FMT_Y_U_V_422		0x4b
#घोषणा VI6_FMT_Y_U_V_420		0x4c

#पूर्ण_अगर /* __VSP1_REGS_H__ */
