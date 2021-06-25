<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#अगर_अघोषित _D71_REG_H_
#घोषणा _D71_REG_H_

/* Common block रेजिस्टरs offset */
#घोषणा BLK_BLOCK_INFO		0x000
#घोषणा BLK_PIPELINE_INFO	0x004
#घोषणा BLK_MAX_LINE_SIZE	0x008
#घोषणा BLK_VALID_INPUT_ID0	0x020
#घोषणा BLK_OUTPUT_ID0		0x060
#घोषणा BLK_INPUT_ID0		0x080
#घोषणा BLK_IRQ_RAW_STATUS	0x0A0
#घोषणा BLK_IRQ_CLEAR		0x0A4
#घोषणा BLK_IRQ_MASK		0x0A8
#घोषणा BLK_IRQ_STATUS		0x0AC
#घोषणा BLK_STATUS		0x0B0
#घोषणा BLK_INFO		0x0C0
#घोषणा BLK_CONTROL		0x0D0
#घोषणा BLK_SIZE		0x0D4
#घोषणा BLK_IN_SIZE		0x0E0

#घोषणा BLK_P0_PTR_LOW		0x100
#घोषणा BLK_P0_PTR_HIGH		0x104
#घोषणा BLK_P0_STRIDE		0x108
#घोषणा BLK_P1_PTR_LOW		0x110
#घोषणा BLK_P1_PTR_HIGH		0x114
#घोषणा BLK_P1_STRIDE		0x118
#घोषणा BLK_P2_PTR_LOW		0x120
#घोषणा BLK_P2_PTR_HIGH		0x124

#घोषणा BLOCK_INFO_N_SUBBLKS(x)	((x) & 0x000F)
#घोषणा BLOCK_INFO_BLK_ID(x)	(((x) & 0x00F0) >> 4)
#घोषणा BLOCK_INFO_BLK_TYPE(x)	(((x) & 0xFF00) >> 8)
#घोषणा BLOCK_INFO_INPUT_ID(x)	((x) & 0xFFF0)
#घोषणा BLOCK_INFO_TYPE_ID(x)	(((x) & 0x0FF0) >> 4)

#घोषणा PIPELINE_INFO_N_OUTPUTS(x)	((x) & 0x000F)
#घोषणा PIPELINE_INFO_N_VALID_INPUTS(x)	(((x) & 0x0F00) >> 8)

/* Common block control रेजिस्टर bits */
#घोषणा BLK_CTRL_EN		BIT(0)
/* Common size macro */
#घोषणा HV_SIZE(h, v)		(((h) & 0x1FFF) + (((v) & 0x1FFF) << 16))
#घोषणा HV_OFFSET(h, v)		(((h) & 0xFFF) + (((v) & 0xFFF) << 16))
#घोषणा HV_CROP(h, v)		(((h) & 0xFFF) + (((v) & 0xFFF) << 16))

/* AD_CONTROL रेजिस्टर */
#घोषणा AD_CONTROL		0x160

/* AD_CONTROL रेजिस्टर bits */
#घोषणा AD_AEN			BIT(0)
#घोषणा AD_YT			BIT(1)
#घोषणा AD_BS			BIT(2)
#घोषणा AD_WB			BIT(3)
#घोषणा AD_TH			BIT(4)

/* Global Control Unit */
#घोषणा GLB_ARCH_ID		0x000
#घोषणा GLB_CORE_ID		0x004
#घोषणा GLB_CORE_INFO		0x008
#घोषणा GLB_IRQ_STATUS		0x010

#घोषणा GCU_CONFIG_VALID0	0x0D4
#घोषणा GCU_CONFIG_VALID1	0x0D8

/* GCU_CONTROL_BITS */
#घोषणा GCU_CONTROL_MODE(x)	((x) & 0x7)
#घोषणा GCU_CONTROL_SRST	BIT(16)

/* GCU_CONFIGURATION रेजिस्टरs */
#घोषणा GCU_CONFIGURATION_ID0	0x100
#घोषणा GCU_CONFIGURATION_ID1	0x104

/* GCU configuration */
#घोषणा GCU_MAX_LINE_SIZE(x)	((x) & 0xFFFF)
#घोषणा GCU_MAX_NUM_LINES(x)	((x) >> 16)
#घोषणा GCU_NUM_RICH_LAYERS(x)	((x) & 0x7)
#घोषणा GCU_NUM_PIPELINES(x)	(((x) >> 3) & 0x7)
#घोषणा GCU_NUM_SCALERS(x)	(((x) >> 6) & 0x7)
#घोषणा GCU_DISPLAY_SPLIT_EN(x)	(((x) >> 16) & 0x1)
#घोषणा GCU_DISPLAY_TBU_EN(x)	(((x) >> 17) & 0x1)

/* GCU opmode */
#घोषणा INACTIVE_MODE		0
#घोषणा TBU_CONNECT_MODE	1
#घोषणा TBU_DISCONNECT_MODE	2
#घोषणा DO0_ACTIVE_MODE		3
#घोषणा DO1_ACTIVE_MODE		4
#घोषणा DO01_ACTIVE_MODE	5

/* GLB_IRQ_STATUS bits */
#घोषणा GLB_IRQ_STATUS_GCU	BIT(0)
#घोषणा GLB_IRQ_STATUS_LPU0	BIT(8)
#घोषणा GLB_IRQ_STATUS_LPU1	BIT(9)
#घोषणा GLB_IRQ_STATUS_ATU0	BIT(10)
#घोषणा GLB_IRQ_STATUS_ATU1	BIT(11)
#घोषणा GLB_IRQ_STATUS_ATU2	BIT(12)
#घोषणा GLB_IRQ_STATUS_ATU3	BIT(13)
#घोषणा GLB_IRQ_STATUS_CU0	BIT(16)
#घोषणा GLB_IRQ_STATUS_CU1	BIT(17)
#घोषणा GLB_IRQ_STATUS_DOU0	BIT(24)
#घोषणा GLB_IRQ_STATUS_DOU1	BIT(25)

#घोषणा GLB_IRQ_STATUS_PIPE0	(GLB_IRQ_STATUS_LPU0 |\
				 GLB_IRQ_STATUS_ATU0 |\
				 GLB_IRQ_STATUS_ATU1 |\
				 GLB_IRQ_STATUS_CU0 |\
				 GLB_IRQ_STATUS_DOU0)

#घोषणा GLB_IRQ_STATUS_PIPE1	(GLB_IRQ_STATUS_LPU1 |\
				 GLB_IRQ_STATUS_ATU2 |\
				 GLB_IRQ_STATUS_ATU3 |\
				 GLB_IRQ_STATUS_CU1 |\
				 GLB_IRQ_STATUS_DOU1)

#घोषणा GLB_IRQ_STATUS_ATU	(GLB_IRQ_STATUS_ATU0 |\
				 GLB_IRQ_STATUS_ATU1 |\
				 GLB_IRQ_STATUS_ATU2 |\
				 GLB_IRQ_STATUS_ATU3)

/* GCU_IRQ_BITS */
#घोषणा GCU_IRQ_CVAL0		BIT(0)
#घोषणा GCU_IRQ_CVAL1		BIT(1)
#घोषणा GCU_IRQ_MODE		BIT(4)
#घोषणा GCU_IRQ_ERR		BIT(11)

/* GCU_STATUS_BITS */
#घोषणा GCU_STATUS_MODE(x)	((x) & 0x7)
#घोषणा GCU_STATUS_MERR		BIT(4)
#घोषणा GCU_STATUS_TCS0		BIT(8)
#घोषणा GCU_STATUS_TCS1		BIT(9)
#घोषणा GCU_STATUS_ACTIVE	BIT(31)

/* GCU_CONFIG_VALIDx BITS */
#घोषणा GCU_CONFIG_CVAL		BIT(0)

/* PERIPHERAL रेजिस्टरs */
#घोषणा PERIPH_MAX_LINE_SIZE	BIT(0)
#घोषणा PERIPH_NUM_RICH_LAYERS	BIT(4)
#घोषणा PERIPH_SPLIT_EN		BIT(8)
#घोषणा PERIPH_TBU_EN		BIT(12)
#घोषणा PERIPH_AFBC_DMA_EN	BIT(16)
#घोषणा PERIPH_CONFIGURATION_ID	0x1D4

/* LPU रेजिस्टर */
#घोषणा LPU_TBU_STATUS		0x0B4
#घोषणा LPU_RAXI_CONTROL	0x0D0
#घोषणा LPU_WAXI_CONTROL	0x0D4
#घोषणा LPU_TBU_CONTROL		0x0D8

/* LPU_xAXI_CONTROL_BITS */
#घोषणा TO_RAXI_AOUTSTDCAPB(x)	(x)
#घोषणा TO_RAXI_BOUTSTDCAPB(x)	((x) << 8)
#घोषणा TO_RAXI_BEN(x)		((x) << 15)
#घोषणा TO_xAXI_BURSTLEN(x)	((x) << 16)
#घोषणा TO_xAXI_AxQOS(x)	((x) << 24)
#घोषणा TO_xAXI_ORD(x)		((x) << 31)
#घोषणा TO_WAXI_OUTSTDCAPB(x)	(x)

#घोषणा RAXI_AOUTSTDCAPB_MASK	0x7F
#घोषणा RAXI_BOUTSTDCAPB_MASK	0x7F00
#घोषणा RAXI_BEN_MASK		BIT(15)
#घोषणा xAXI_BURSTLEN_MASK	0x3F0000
#घोषणा xAXI_AxQOS_MASK		0xF000000
#घोषणा xAXI_ORD_MASK		BIT(31)
#घोषणा WAXI_OUTSTDCAPB_MASK	0x3F

/* LPU_TBU_CONTROL BITS */
#घोषणा TO_TBU_DOUTSTDCAPB(x)	(x)
#घोषणा TBU_DOUTSTDCAPB_MASK	0x3F

/* LPU_IRQ_BITS */
#घोषणा LPU_IRQ_OVR		BIT(9)
#घोषणा LPU_IRQ_IBSY		BIT(10)
#घोषणा LPU_IRQ_ERR		BIT(11)
#घोषणा LPU_IRQ_EOW		BIT(12)
#घोषणा LPU_IRQ_PL0		BIT(13)

/* LPU_STATUS_BITS */
#घोषणा LPU_STATUS_AXIED(x)	((x) & 0xF)
#घोषणा LPU_STATUS_AXIE		BIT(4)
#घोषणा LPU_STATUS_AXIRP	BIT(5)
#घोषणा LPU_STATUS_AXIWP	BIT(6)
#घोषणा LPU_STATUS_FEMPTY	BIT(11)
#घोषणा LPU_STATUS_FFULL	BIT(14)
#घोषणा LPU_STATUS_ACE0		BIT(16)
#घोषणा LPU_STATUS_ACE1		BIT(17)
#घोषणा LPU_STATUS_ACE2		BIT(18)
#घोषणा LPU_STATUS_ACE3		BIT(19)
#घोषणा LPU_STATUS_ACTIVE	BIT(31)

#घोषणा AXIEID_MASK		0xF
#घोषणा AXIE_MASK		LPU_STATUS_AXIE
#घोषणा AXIRP_MASK		LPU_STATUS_AXIRP
#घोषणा AXIWP_MASK		LPU_STATUS_AXIWP

#घोषणा FROM_AXIEID(reg)	((reg) & AXIEID_MASK)
#घोषणा TO_AXIE(x)		((x) << 4)
#घोषणा FROM_AXIRP(reg)		(((reg) & AXIRP_MASK) >> 5)
#घोषणा FROM_AXIWP(reg)		(((reg) & AXIWP_MASK) >> 6)

/* LPU_TBU_STATUS_BITS */
#घोषणा LPU_TBU_STATUS_TCF	BIT(1)
#घोषणा LPU_TBU_STATUS_TTNG	BIT(2)
#घोषणा LPU_TBU_STATUS_TITR	BIT(8)
#घोषणा LPU_TBU_STATUS_TEMR	BIT(16)
#घोषणा LPU_TBU_STATUS_TTF	BIT(31)

/* LPU_TBU_CONTROL BITS */
#घोषणा LPU_TBU_CTRL_TLBPEN	BIT(16)

/* CROSSBAR CONTROL BITS */
#घोषणा CBU_INPUT_CTRL_EN	BIT(0)
#घोषणा CBU_NUM_INPUT_IDS	5
#घोषणा CBU_NUM_OUTPUT_IDS	5

/* CU रेजिस्टर */
#घोषणा CU_BG_COLOR		0x0DC
#घोषणा CU_INPUT0_SIZE		0x0E0
#घोषणा CU_INPUT0_OFFSET	0x0E4
#घोषणा CU_INPUT0_CONTROL	0x0E8
#घोषणा CU_INPUT1_SIZE		0x0F0
#घोषणा CU_INPUT1_OFFSET	0x0F4
#घोषणा CU_INPUT1_CONTROL	0x0F8
#घोषणा CU_INPUT2_SIZE		0x100
#घोषणा CU_INPUT2_OFFSET	0x104
#घोषणा CU_INPUT2_CONTROL	0x108
#घोषणा CU_INPUT3_SIZE		0x110
#घोषणा CU_INPUT3_OFFSET	0x114
#घोषणा CU_INPUT3_CONTROL	0x118
#घोषणा CU_INPUT4_SIZE		0x120
#घोषणा CU_INPUT4_OFFSET	0x124
#घोषणा CU_INPUT4_CONTROL	0x128

#घोषणा CU_PER_INPUT_REGS	4

#घोषणा CU_NUM_INPUT_IDS	5
#घोषणा CU_NUM_OUTPUT_IDS	1

/* CU control रेजिस्टर bits */
#घोषणा CU_CTRL_COPROC		BIT(0)

/* CU_IRQ_BITS */
#घोषणा CU_IRQ_OVR		BIT(9)
#घोषणा CU_IRQ_ERR		BIT(11)

/* CU_STATUS_BITS */
#घोषणा CU_STATUS_CPE		BIT(0)
#घोषणा CU_STATUS_ZME		BIT(1)
#घोषणा CU_STATUS_CFGE		BIT(2)
#घोषणा CU_STATUS_ACTIVE	BIT(31)

/* CU input control रेजिस्टर bits */
#घोषणा CU_INPUT_CTRL_EN	BIT(0)
#घोषणा CU_INPUT_CTRL_PAD	BIT(1)
#घोषणा CU_INPUT_CTRL_PMUL	BIT(2)
#घोषणा CU_INPUT_CTRL_ALPHA(x)	(((x) & 0xFF) << 8)

/* DOU रेजिस्टर */

/* DOU_IRQ_BITS */
#घोषणा DOU_IRQ_UND		BIT(8)
#घोषणा DOU_IRQ_ERR		BIT(11)
#घोषणा DOU_IRQ_PL0		BIT(13)
#घोषणा DOU_IRQ_PL1		BIT(14)

/* DOU_STATUS_BITS */
#घोषणा DOU_STATUS_DRIFTTO	BIT(0)
#घोषणा DOU_STATUS_FRAMETO	BIT(1)
#घोषणा DOU_STATUS_TETO		BIT(2)
#घोषणा DOU_STATUS_CSCE		BIT(8)
#घोषणा DOU_STATUS_ACTIVE	BIT(31)

/* Layer रेजिस्टरs */
#घोषणा LAYER_INFO		0x0C0
#घोषणा LAYER_R_CONTROL		0x0D4
#घोषणा LAYER_FMT		0x0D8
#घोषणा LAYER_LT_COEFFTAB	0x0DC
#घोषणा LAYER_PALPHA		0x0E4

#घोषणा LAYER_YUV_RGB_COEFF0	0x130

#घोषणा LAYER_AD_H_CROP		0x164
#घोषणा LAYER_AD_V_CROP		0x168

#घोषणा LAYER_RGB_RGB_COEFF0	0x170

/* L_CONTROL_BITS */
#घोषणा L_EN			BIT(0)
#घोषणा L_IT			BIT(4)
#घोषणा L_R2R			BIT(5)
#घोषणा L_FT			BIT(6)
#घोषणा L_ROT(x)		(((x) & 3) << 8)
#घोषणा L_HFLIP			BIT(10)
#घोषणा L_VFLIP			BIT(11)
#घोषणा L_TBU_EN		BIT(16)
#घोषणा L_A_RCACHE(x)		(((x) & 0xF) << 28)
#घोषणा L_ROT_R0		0
#घोषणा L_ROT_R90		1
#घोषणा L_ROT_R180		2
#घोषणा L_ROT_R270		3

/* LAYER_R_CONTROL BITS */
#घोषणा LR_CHI422_BILINEAR	0
#घोषणा LR_CHI422_REPLICATION	1
#घोषणा LR_CHI420_JPEG		(0 << 2)
#घोषणा LR_CHI420_MPEG		(1 << 2)

#घोषणा L_ITSEL(x)		((x) & 0xFFF)
#घोषणा L_FTSEL(x)		(((x) & 0xFFF) << 16)

#घोषणा LAYER_PER_PLANE_REGS	4

/* Layer_WR रेजिस्टरs */
#घोषणा LAYER_WR_PROG_LINE	0x0D4
#घोषणा LAYER_WR_FORMAT		0x0D8

/* Layer_WR control bits */
#घोषणा LW_OFM			BIT(4)
#घोषणा LW_LALPHA(x)		(((x) & 0xFF) << 8)
#घोषणा LW_A_WCACHE(x)		(((x) & 0xF) << 28)
#घोषणा LW_TBU_EN		BIT(16)

#घोषणा AxCACHE_MASK		0xF0000000

/* Layer AXI R/W cache setting */
#घोषणा AxCACHE_B		BIT(0)	/* Bufferable */
#घोषणा AxCACHE_M		BIT(1)	/* Modअगरiable */
#घोषणा AxCACHE_RA		BIT(2)	/* Read-Allocate */
#घोषणा AxCACHE_WA		BIT(3)	/* Write-Allocate */

/* Layer info bits */
#घोषणा L_INFO_RF		BIT(0)
#घोषणा L_INFO_CM		BIT(1)
#घोषणा L_INFO_ABUF_SIZE(x)	(((x) >> 4) & 0x7)
#घोषणा L_INFO_YUV_MAX_LINESZ(x)	(((x) >> 16) & 0xFFFF)

/* Scaler रेजिस्टरs */
#घोषणा SC_COEFFTAB		0x0DC
#घोषणा SC_OUT_SIZE		0x0E4
#घोषणा SC_H_CROP		0x0E8
#घोषणा SC_V_CROP		0x0EC
#घोषणा SC_H_INIT_PH		0x0F0
#घोषणा SC_H_DELTA_PH		0x0F4
#घोषणा SC_V_INIT_PH		0x0F8
#घोषणा SC_V_DELTA_PH		0x0FC
#घोषणा SC_ENH_LIMITS		0x130
#घोषणा SC_ENH_COEFF0		0x134

#घोषणा SC_MAX_ENH_COEFF	9

/* SC_CTRL_BITS */
#घोषणा SC_CTRL_SCL		BIT(0)
#घोषणा SC_CTRL_LS		BIT(1)
#घोषणा SC_CTRL_AP		BIT(4)
#घोषणा SC_CTRL_IENH		BIT(8)
#घोषणा SC_CTRL_RGBSM		BIT(16)
#घोषणा SC_CTRL_ASM		BIT(17)

#घोषणा SC_VTSEL(vtal)		((vtal) << 16)

#घोषणा SC_NUM_INPUTS_IDS	1
#घोषणा SC_NUM_OUTPUTS_IDS	1

#घोषणा MG_NUM_INPUTS_IDS	2
#घोषणा MG_NUM_OUTPUTS_IDS	1

/* Merger रेजिस्टरs */
#घोषणा MG_INPUT_ID0		BLK_INPUT_ID0
#घोषणा MG_INPUT_ID1		(MG_INPUT_ID0 + 4)
#घोषणा MG_SIZE			BLK_SIZE

/* Splitter रेजिस्टरs */
#घोषणा SP_OVERLAP_SIZE		0xD8

/* Backend रेजिस्टरs */
#घोषणा BS_INFO			0x0C0
#घोषणा BS_PROG_LINE		0x0D4
#घोषणा BS_PREFETCH_LINE	0x0D8
#घोषणा BS_BG_COLOR		0x0DC
#घोषणा BS_ACTIVESIZE		0x0E0
#घोषणा BS_HINTERVALS		0x0E4
#घोषणा BS_VINTERVALS		0x0E8
#घोषणा BS_SYNC			0x0EC
#घोषणा BS_DRIFT_TO		0x100
#घोषणा BS_FRAME_TO		0x104
#घोषणा BS_TE_TO		0x108
#घोषणा BS_T0_INTERVAL		0x110
#घोषणा BS_T1_INTERVAL		0x114
#घोषणा BS_T2_INTERVAL		0x118
#घोषणा BS_CRC0_LOW		0x120
#घोषणा BS_CRC0_HIGH		0x124
#घोषणा BS_CRC1_LOW		0x128
#घोषणा BS_CRC1_HIGH		0x12C
#घोषणा BS_USER			0x130

/* BS control रेजिस्टर bits */
#घोषणा BS_CTRL_EN		BIT(0)
#घोषणा BS_CTRL_VM		BIT(1)
#घोषणा BS_CTRL_BM		BIT(2)
#घोषणा BS_CTRL_HMASK		BIT(4)
#घोषणा BS_CTRL_VD		BIT(5)
#घोषणा BS_CTRL_TE		BIT(8)
#घोषणा BS_CTRL_TS		BIT(9)
#घोषणा BS_CTRL_TM		BIT(12)
#घोषणा BS_CTRL_DL		BIT(16)
#घोषणा BS_CTRL_SBS		BIT(17)
#घोषणा BS_CTRL_CRC		BIT(18)
#घोषणा BS_CTRL_PM		BIT(20)

/* BS active size/पूर्णांकervals */
#घोषणा BS_H_INTVALS(hfp, hbp)	(((hfp) & 0xFFF) + (((hbp) & 0x3FF) << 16))
#घोषणा BS_V_INTVALS(vfp, vbp)  (((vfp) & 0x3FFF) + (((vbp) & 0xFF) << 16))

/* BS_SYNC bits */
#घोषणा BS_SYNC_HSW(x)		((x) & 0x3FF)
#घोषणा BS_SYNC_HSP		BIT(12)
#घोषणा BS_SYNC_VSW(x)		(((x) & 0xFF) << 16)
#घोषणा BS_SYNC_VSP		BIT(28)

#घोषणा BS_NUM_INPUT_IDS	0
#घोषणा BS_NUM_OUTPUT_IDS	0

/* Image process रेजिस्टरs */
#घोषणा IPS_DEPTH		0x0D8
#घोषणा IPS_RGB_RGB_COEFF0	0x130
#घोषणा IPS_RGB_YUV_COEFF0	0x170

#घोषणा IPS_DEPTH_MARK		0xF

/* IPS control रेजिस्टर bits */
#घोषणा IPS_CTRL_RGB		BIT(0)
#घोषणा IPS_CTRL_FT		BIT(4)
#घोषणा IPS_CTRL_YUV		BIT(8)
#घोषणा IPS_CTRL_CHD422		BIT(9)
#घोषणा IPS_CTRL_CHD420		BIT(10)
#घोषणा IPS_CTRL_LPF		BIT(11)
#घोषणा IPS_CTRL_DITH		BIT(12)
#घोषणा IPS_CTRL_CLAMP		BIT(16)
#घोषणा IPS_CTRL_SBS		BIT(17)

/* IPS info रेजिस्टर bits */
#घोषणा IPS_INFO_CHD420		BIT(10)

#घोषणा IPS_NUM_INPUT_IDS	2
#घोषणा IPS_NUM_OUTPUT_IDS	1

/* FT_COEFF block रेजिस्टरs */
#घोषणा FT_COEFF0		0x80
#घोषणा GLB_IT_COEFF		0x80

/* GLB_SC_COEFF रेजिस्टरs */
#घोषणा GLB_SC_COEFF_ADDR	0x0080
#घोषणा GLB_SC_COEFF_DATA	0x0084
#घोषणा GLB_LT_COEFF_DATA	0x0080

#घोषणा GLB_SC_COEFF_MAX_NUM	1024
#घोषणा GLB_LT_COEFF_NUM	65
/* GLB_SC_ADDR */
#घोषणा SC_COEFF_R_ADDR		BIT(18)
#घोषणा SC_COEFF_G_ADDR		BIT(17)
#घोषणा SC_COEFF_B_ADDR		BIT(16)

#घोषणा SC_COEFF_DATA(x, y)	(((y) & 0xFFFF) | (((x) & 0xFFFF) << 16))

क्रमागत d71_blk_type अणु
	D71_BLK_TYPE_GCU		= 0x00,
	D71_BLK_TYPE_LPU		= 0x01,
	D71_BLK_TYPE_CU			= 0x02,
	D71_BLK_TYPE_DOU		= 0x03,
	D71_BLK_TYPE_AEU		= 0x04,
	D71_BLK_TYPE_GLB_LT_COEFF	= 0x05,
	D71_BLK_TYPE_GLB_SCL_COEFF	= 0x06, /* SH/SV scaler coeff */
	D71_BLK_TYPE_GLB_SC_COEFF	= 0x07,
	D71_BLK_TYPE_PERIPH		= 0x08,
	D71_BLK_TYPE_LPU_TRUSTED	= 0x09,
	D71_BLK_TYPE_AEU_TRUSTED	= 0x0A,
	D71_BLK_TYPE_LPU_LAYER		= 0x10,
	D71_BLK_TYPE_LPU_WB_LAYER	= 0x11,
	D71_BLK_TYPE_CU_SPLITTER	= 0x20,
	D71_BLK_TYPE_CU_SCALER		= 0x21,
	D71_BLK_TYPE_CU_MERGER		= 0x22,
	D71_BLK_TYPE_DOU_IPS		= 0x30,
	D71_BLK_TYPE_DOU_BS		= 0x31,
	D71_BLK_TYPE_DOU_FT_COEFF	= 0x32,
	D71_BLK_TYPE_AEU_DS		= 0x40,
	D71_BLK_TYPE_AEU_AES		= 0x41,
	D71_BLK_TYPE_RESERVED		= 0xFF
पूर्ण;

/* Constant of components */
#घोषणा D71_MAX_PIPELINE		2
#घोषणा D71_PIPELINE_MAX_SCALERS	2
#घोषणा D71_PIPELINE_MAX_LAYERS		4

#घोषणा D71_MAX_GLB_IT_COEFF		3
#घोषणा D71_MAX_GLB_SCL_COEFF		4

#घोषणा D71_MAX_LAYERS_PER_LPU		4
#घोषणा D71_BLOCK_MAX_INPUT		9
#घोषणा D71_BLOCK_MAX_OUTPUT		5
#घोषणा D71_MAX_SC_PER_CU		2

#घोषणा D71_BLOCK_OFFSET_PERIPH		0xFE00
#घोषणा D71_BLOCK_SIZE			0x0200

#घोषणा D71_DEFAULT_PREPRETCH_LINE	5
#घोषणा D71_BUS_WIDTH_16_BYTES		16

#घोषणा D71_SC_MAX_UPSCALING		64
#घोषणा D71_SC_MAX_DOWNSCALING		6
#घोषणा D71_SC_SPLIT_OVERLAP		8
#घोषणा D71_SC_ENH_SPLIT_OVERLAP	1

#घोषणा D71_MG_MIN_MERGED_SIZE		4
#घोषणा D71_MG_MAX_MERGED_HSIZE		4032
#घोषणा D71_MG_MAX_MERGED_VSIZE		4096

#घोषणा D71_PALPHA_DEF_MAP		0xFFAA5500
#घोषणा D71_LAYER_CONTROL_DEFAULT	0x30000000
#घोषणा D71_WB_LAYER_CONTROL_DEFAULT	0x3000FF00
#घोषणा D71_BS_CONTROL_DEFAULT		0x00000002

काष्ठा block_header अणु
	u32 block_info;
	u32 pipeline_info;
	u32 input_ids[D71_BLOCK_MAX_INPUT];
	u32 output_ids[D71_BLOCK_MAX_OUTPUT];
पूर्ण;

अटल अंतरभूत u32 get_block_type(काष्ठा block_header *blk)
अणु
	वापस BLOCK_INFO_BLK_TYPE(blk->block_info);
पूर्ण

#पूर्ण_अगर /* !_D71_REG_H_ */
