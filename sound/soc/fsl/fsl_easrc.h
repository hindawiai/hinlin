<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 NXP
 */

#अगर_अघोषित _FSL_EASRC_H
#घोषणा _FSL_EASRC_H

#समावेश <sound/asound.h>
#समावेश <linux/platक्रमm_data/dma-imx.h>

#समावेश "fsl_asrc_common.h"

/* EASRC Register Map */

/* ASRC Input Write FIFO */
#घोषणा REG_EASRC_WRFIFO(ctx)		(0x000 + 4 * (ctx))
/* ASRC Output Read FIFO */
#घोषणा REG_EASRC_RDFIFO(ctx)		(0x010 + 4 * (ctx))
/* ASRC Context Control */
#घोषणा REG_EASRC_CC(ctx)		(0x020 + 4 * (ctx))
/* ASRC Context Control Extended 1 */
#घोषणा REG_EASRC_CCE1(ctx)		(0x030 + 4 * (ctx))
/* ASRC Context Control Extended 2 */
#घोषणा REG_EASRC_CCE2(ctx)		(0x040 + 4 * (ctx))
/* ASRC Control Input Access */
#घोषणा REG_EASRC_CIA(ctx)		(0x050 + 4 * (ctx))
/* ASRC Datapath Processor Control Slot0 */
#घोषणा REG_EASRC_DPCS0R0(ctx)		(0x060 + 4 * (ctx))
#घोषणा REG_EASRC_DPCS0R1(ctx)		(0x070 + 4 * (ctx))
#घोषणा REG_EASRC_DPCS0R2(ctx)		(0x080 + 4 * (ctx))
#घोषणा REG_EASRC_DPCS0R3(ctx)		(0x090 + 4 * (ctx))
/* ASRC Datapath Processor Control Slot1 */
#घोषणा REG_EASRC_DPCS1R0(ctx)		(0x0A0 + 4 * (ctx))
#घोषणा REG_EASRC_DPCS1R1(ctx)		(0x0B0 + 4 * (ctx))
#घोषणा REG_EASRC_DPCS1R2(ctx)		(0x0C0 + 4 * (ctx))
#घोषणा REG_EASRC_DPCS1R3(ctx)		(0x0D0 + 4 * (ctx))
/* ASRC Context Output Control */
#घोषणा REG_EASRC_COC(ctx)		(0x0E0 + 4 * (ctx))
/* ASRC Control Output Access */
#घोषणा REG_EASRC_COA(ctx)		(0x0F0 + 4 * (ctx))
/* ASRC Sample FIFO Status */
#घोषणा REG_EASRC_SFS(ctx)		(0x100 + 4 * (ctx))
/* ASRC Resampling Ratio Low */
#घोषणा REG_EASRC_RRL(ctx)		(0x110 + 8 * (ctx))
/* ASRC Resampling Ratio High */
#घोषणा REG_EASRC_RRH(ctx)		(0x114 + 8 * (ctx))
/* ASRC Resampling Ratio Update Control */
#घोषणा REG_EASRC_RUC(ctx)		(0x130 + 4 * (ctx))
/* ASRC Resampling Ratio Update Rate */
#घोषणा REG_EASRC_RUR(ctx)		(0x140 + 4 * (ctx))
/* ASRC Resampling Center Tap Coefficient Low */
#घोषणा REG_EASRC_RCTCL			(0x150)
/* ASRC Resampling Center Tap Coefficient High */
#घोषणा REG_EASRC_RCTCH			(0x154)
/* ASRC Prefilter Coefficient FIFO */
#घोषणा REG_EASRC_PCF(ctx)		(0x160 + 4 * (ctx))
/* ASRC Context Resampling Coefficient Memory */
#घोषणा REG_EASRC_CRCM			0x170
/* ASRC Context Resampling Coefficient Control*/
#घोषणा REG_EASRC_CRCC			0x174
/* ASRC Interrupt Control */
#घोषणा REG_EASRC_IRQC			0x178
/* ASRC Interrupt Status Flags */
#घोषणा REG_EASRC_IRQF			0x17C
/* ASRC Channel Status 0 */
#घोषणा REG_EASRC_CS0(ctx)		(0x180 + 4 * (ctx))
/* ASRC Channel Status 1 */
#घोषणा REG_EASRC_CS1(ctx)		(0x190 + 4 * (ctx))
/* ASRC Channel Status 2 */
#घोषणा REG_EASRC_CS2(ctx)		(0x1A0 + 4 * (ctx))
/* ASRC Channel Status 3 */
#घोषणा REG_EASRC_CS3(ctx)		(0x1B0 + 4 * (ctx))
/* ASRC Channel Status 4 */
#घोषणा REG_EASRC_CS4(ctx)		(0x1C0 + 4 * (ctx))
/* ASRC Channel Status 5 */
#घोषणा REG_EASRC_CS5(ctx)		(0x1D0 + 4 * (ctx))
/* ASRC Debug Control Register */
#घोषणा REG_EASRC_DBGC			0x1E0
/* ASRC Debug Status Register */
#घोषणा REG_EASRC_DBGS			0x1E4

#घोषणा REG_EASRC_FIFO(x, ctx)		(x == IN ? REG_EASRC_WRFIFO(ctx) \
						: REG_EASRC_RDFIFO(ctx))

/* ASRC Context Control (CC) */
#घोषणा EASRC_CC_EN_SHIFT		31
#घोषणा EASRC_CC_EN_MASK		BIT(EASRC_CC_EN_SHIFT)
#घोषणा EASRC_CC_EN			BIT(EASRC_CC_EN_SHIFT)
#घोषणा EASRC_CC_STOP_SHIFT		29
#घोषणा EASRC_CC_STOP_MASK		BIT(EASRC_CC_STOP_SHIFT)
#घोषणा EASRC_CC_STOP			BIT(EASRC_CC_STOP_SHIFT)
#घोषणा EASRC_CC_FWMDE_SHIFT		28
#घोषणा EASRC_CC_FWMDE_MASK		BIT(EASRC_CC_FWMDE_SHIFT)
#घोषणा EASRC_CC_FWMDE			BIT(EASRC_CC_FWMDE_SHIFT)
#घोषणा EASRC_CC_FIFO_WTMK_SHIFT	16
#घोषणा EASRC_CC_FIFO_WTMK_WIDTH	7
#घोषणा EASRC_CC_FIFO_WTMK_MASK		((BIT(EASRC_CC_FIFO_WTMK_WIDTH) - 1) \
					 << EASRC_CC_FIFO_WTMK_SHIFT)
#घोषणा EASRC_CC_FIFO_WTMK(v)		(((v) << EASRC_CC_FIFO_WTMK_SHIFT) \
					 & EASRC_CC_FIFO_WTMK_MASK)
#घोषणा EASRC_CC_SAMPLE_POS_SHIFT	11
#घोषणा EASRC_CC_SAMPLE_POS_WIDTH	5
#घोषणा EASRC_CC_SAMPLE_POS_MASK	((BIT(EASRC_CC_SAMPLE_POS_WIDTH) - 1) \
					 << EASRC_CC_SAMPLE_POS_SHIFT)
#घोषणा EASRC_CC_SAMPLE_POS(v)		(((v) << EASRC_CC_SAMPLE_POS_SHIFT) \
					 & EASRC_CC_SAMPLE_POS_MASK)
#घोषणा EASRC_CC_ENDIANNESS_SHIFT	10
#घोषणा EASRC_CC_ENDIANNESS_MASK	BIT(EASRC_CC_ENDIANNESS_SHIFT)
#घोषणा EASRC_CC_ENDIANNESS		BIT(EASRC_CC_ENDIANNESS_SHIFT)
#घोषणा EASRC_CC_BPS_SHIFT		8
#घोषणा EASRC_CC_BPS_WIDTH		2
#घोषणा EASRC_CC_BPS_MASK		((BIT(EASRC_CC_BPS_WIDTH) - 1) \
					 << EASRC_CC_BPS_SHIFT)
#घोषणा EASRC_CC_BPS(v)			(((v) << EASRC_CC_BPS_SHIFT) \
					 & EASRC_CC_BPS_MASK)
#घोषणा EASRC_CC_FMT_SHIFT		7
#घोषणा EASRC_CC_FMT_MASK		BIT(EASRC_CC_FMT_SHIFT)
#घोषणा EASRC_CC_FMT			BIT(EASRC_CC_FMT_SHIFT)
#घोषणा EASRC_CC_INSIGN_SHIFT		6
#घोषणा EASRC_CC_INSIGN_MASK		BIT(EASRC_CC_INSIGN_SHIFT)
#घोषणा EASRC_CC_INSIGN			BIT(EASRC_CC_INSIGN_SHIFT)
#घोषणा EASRC_CC_CHEN_SHIFT		0
#घोषणा EASRC_CC_CHEN_WIDTH		5
#घोषणा EASRC_CC_CHEN_MASK		((BIT(EASRC_CC_CHEN_WIDTH) - 1) \
					 << EASRC_CC_CHEN_SHIFT)
#घोषणा EASRC_CC_CHEN(v)		(((v) << EASRC_CC_CHEN_SHIFT) \
					 & EASRC_CC_CHEN_MASK)

/* ASRC Context Control Extended 1 (CCE1) */
#घोषणा EASRC_CCE1_COEF_WS_SHIFT	25
#घोषणा EASRC_CCE1_COEF_WS_MASK		BIT(EASRC_CCE1_COEF_WS_SHIFT)
#घोषणा EASRC_CCE1_COEF_WS		BIT(EASRC_CCE1_COEF_WS_SHIFT)
#घोषणा EASRC_CCE1_COEF_MEM_RST_SHIFT	24
#घोषणा EASRC_CCE1_COEF_MEM_RST_MASK	BIT(EASRC_CCE1_COEF_MEM_RST_SHIFT)
#घोषणा EASRC_CCE1_COEF_MEM_RST		BIT(EASRC_CCE1_COEF_MEM_RST_SHIFT)
#घोषणा EASRC_CCE1_PF_EXP_SHIFT		16
#घोषणा EASRC_CCE1_PF_EXP_WIDTH		8
#घोषणा EASRC_CCE1_PF_EXP_MASK		((BIT(EASRC_CCE1_PF_EXP_WIDTH) - 1) \
					 << EASRC_CCE1_PF_EXP_SHIFT)
#घोषणा EASRC_CCE1_PF_EXP(v)		(((v) << EASRC_CCE1_PF_EXP_SHIFT) \
					 & EASRC_CCE1_PF_EXP_MASK)
#घोषणा EASRC_CCE1_PF_ST1_WBFP_SHIFT	9
#घोषणा EASRC_CCE1_PF_ST1_WBFP_MASK	BIT(EASRC_CCE1_PF_ST1_WBFP_SHIFT)
#घोषणा EASRC_CCE1_PF_ST1_WBFP		BIT(EASRC_CCE1_PF_ST1_WBFP_SHIFT)
#घोषणा EASRC_CCE1_PF_TSEN_SHIFT	8
#घोषणा EASRC_CCE1_PF_TSEN_MASK		BIT(EASRC_CCE1_PF_TSEN_SHIFT)
#घोषणा EASRC_CCE1_PF_TSEN		BIT(EASRC_CCE1_PF_TSEN_SHIFT)
#घोषणा EASRC_CCE1_RS_BYPASS_SHIFT	7
#घोषणा EASRC_CCE1_RS_BYPASS_MASK	BIT(EASRC_CCE1_RS_BYPASS_SHIFT)
#घोषणा EASRC_CCE1_RS_BYPASS		BIT(EASRC_CCE1_RS_BYPASS_SHIFT)
#घोषणा EASRC_CCE1_PF_BYPASS_SHIFT	6
#घोषणा EASRC_CCE1_PF_BYPASS_MASK	BIT(EASRC_CCE1_PF_BYPASS_SHIFT)
#घोषणा EASRC_CCE1_PF_BYPASS		BIT(EASRC_CCE1_PF_BYPASS_SHIFT)
#घोषणा EASRC_CCE1_RS_STOP_SHIFT	5
#घोषणा EASRC_CCE1_RS_STOP_MASK		BIT(EASRC_CCE1_RS_STOP_SHIFT)
#घोषणा EASRC_CCE1_RS_STOP		BIT(EASRC_CCE1_RS_STOP_SHIFT)
#घोषणा EASRC_CCE1_PF_STOP_SHIFT	4
#घोषणा EASRC_CCE1_PF_STOP_MASK		BIT(EASRC_CCE1_PF_STOP_SHIFT)
#घोषणा EASRC_CCE1_PF_STOP		BIT(EASRC_CCE1_PF_STOP_SHIFT)
#घोषणा EASRC_CCE1_RS_INIT_SHIFT	2
#घोषणा EASRC_CCE1_RS_INIT_WIDTH	2
#घोषणा EASRC_CCE1_RS_INIT_MASK		((BIT(EASRC_CCE1_RS_INIT_WIDTH) - 1) \
					 << EASRC_CCE1_RS_INIT_SHIFT)
#घोषणा EASRC_CCE1_RS_INIT(v)		(((v) << EASRC_CCE1_RS_INIT_SHIFT) \
					 & EASRC_CCE1_RS_INIT_MASK)
#घोषणा EASRC_CCE1_PF_INIT_SHIFT	0
#घोषणा EASRC_CCE1_PF_INIT_WIDTH	2
#घोषणा EASRC_CCE1_PF_INIT_MASK		((BIT(EASRC_CCE1_PF_INIT_WIDTH) - 1) \
					 << EASRC_CCE1_PF_INIT_SHIFT)
#घोषणा EASRC_CCE1_PF_INIT(v)		(((v) << EASRC_CCE1_PF_INIT_SHIFT) \
					 & EASRC_CCE1_PF_INIT_MASK)

/* ASRC Context Control Extended 2 (CCE2) */
#घोषणा EASRC_CCE2_ST2_TAPS_SHIFT	16
#घोषणा EASRC_CCE2_ST2_TAPS_WIDTH	9
#घोषणा EASRC_CCE2_ST2_TAPS_MASK	((BIT(EASRC_CCE2_ST2_TAPS_WIDTH) - 1) \
					 << EASRC_CCE2_ST2_TAPS_SHIFT)
#घोषणा EASRC_CCE2_ST2_TAPS(v)		(((v) << EASRC_CCE2_ST2_TAPS_SHIFT) \
					 & EASRC_CCE2_ST2_TAPS_MASK)
#घोषणा EASRC_CCE2_ST1_TAPS_SHIFT	0
#घोषणा EASRC_CCE2_ST1_TAPS_WIDTH	9
#घोषणा EASRC_CCE2_ST1_TAPS_MASK	((BIT(EASRC_CCE2_ST1_TAPS_WIDTH) - 1) \
					 << EASRC_CCE2_ST1_TAPS_SHIFT)
#घोषणा EASRC_CCE2_ST1_TAPS(v)		(((v) << EASRC_CCE2_ST1_TAPS_SHIFT) \
					 & EASRC_CCE2_ST1_TAPS_MASK)

/* ASRC Control Input Access (CIA) */
#घोषणा EASRC_CIA_ITER_SHIFT		16
#घोषणा EASRC_CIA_ITER_WIDTH		6
#घोषणा EASRC_CIA_ITER_MASK		((BIT(EASRC_CIA_ITER_WIDTH) - 1) \
					 << EASRC_CIA_ITER_SHIFT)
#घोषणा EASRC_CIA_ITER(v)		(((v) << EASRC_CIA_ITER_SHIFT) \
					 & EASRC_CIA_ITER_MASK)
#घोषणा EASRC_CIA_GRLEN_SHIFT		8
#घोषणा EASRC_CIA_GRLEN_WIDTH		6
#घोषणा EASRC_CIA_GRLEN_MASK		((BIT(EASRC_CIA_GRLEN_WIDTH) - 1) \
					 << EASRC_CIA_GRLEN_SHIFT)
#घोषणा EASRC_CIA_GRLEN(v)		(((v) << EASRC_CIA_GRLEN_SHIFT) \
					 & EASRC_CIA_GRLEN_MASK)
#घोषणा EASRC_CIA_ACCLEN_SHIFT		0
#घोषणा EASRC_CIA_ACCLEN_WIDTH		6
#घोषणा EASRC_CIA_ACCLEN_MASK		((BIT(EASRC_CIA_ACCLEN_WIDTH) - 1) \
					 << EASRC_CIA_ACCLEN_SHIFT)
#घोषणा EASRC_CIA_ACCLEN(v)		(((v) << EASRC_CIA_ACCLEN_SHIFT) \
					 & EASRC_CIA_ACCLEN_MASK)

/* ASRC Datapath Processor Control Slot0 Register0 (DPCS0R0) */
#घोषणा EASRC_DPCS0R0_MAXCH_SHIFT	24
#घोषणा EASRC_DPCS0R0_MAXCH_WIDTH	5
#घोषणा EASRC_DPCS0R0_MAXCH_MASK	((BIT(EASRC_DPCS0R0_MAXCH_WIDTH) - 1) \
					 << EASRC_DPCS0R0_MAXCH_SHIFT)
#घोषणा EASRC_DPCS0R0_MAXCH(v)		(((v) << EASRC_DPCS0R0_MAXCH_SHIFT) \
					 & EASRC_DPCS0R0_MAXCH_MASK)
#घोषणा EASRC_DPCS0R0_MINCH_SHIFT	16
#घोषणा EASRC_DPCS0R0_MINCH_WIDTH	5
#घोषणा EASRC_DPCS0R0_MINCH_MASK	((BIT(EASRC_DPCS0R0_MINCH_WIDTH) - 1) \
					 << EASRC_DPCS0R0_MINCH_SHIFT)
#घोषणा EASRC_DPCS0R0_MINCH(v)		(((v) << EASRC_DPCS0R0_MINCH_SHIFT) \
					 & EASRC_DPCS0R0_MINCH_MASK)
#घोषणा EASRC_DPCS0R0_NUMCH_SHIFT	8
#घोषणा EASRC_DPCS0R0_NUMCH_WIDTH	5
#घोषणा EASRC_DPCS0R0_NUMCH_MASK	((BIT(EASRC_DPCS0R0_NUMCH_WIDTH) - 1) \
					 << EASRC_DPCS0R0_NUMCH_SHIFT)
#घोषणा EASRC_DPCS0R0_NUMCH(v)		(((v) << EASRC_DPCS0R0_NUMCH_SHIFT) \
					 & EASRC_DPCS0R0_NUMCH_MASK)
#घोषणा EASRC_DPCS0R0_CTXNUM_SHIFT	1
#घोषणा EASRC_DPCS0R0_CTXNUM_WIDTH	2
#घोषणा EASRC_DPCS0R0_CTXNUM_MASK	((BIT(EASRC_DPCS0R0_CTXNUM_WIDTH) - 1) \
					 << EASRC_DPCS0R0_CTXNUM_SHIFT)
#घोषणा EASRC_DPCS0R0_CTXNUM(v)		(((v) << EASRC_DPCS0R0_CTXNUM_SHIFT) \
					 & EASRC_DPCS0R0_CTXNUM_MASK)
#घोषणा EASRC_DPCS0R0_EN_SHIFT		0
#घोषणा EASRC_DPCS0R0_EN_MASK		BIT(EASRC_DPCS0R0_EN_SHIFT)
#घोषणा EASRC_DPCS0R0_EN		BIT(EASRC_DPCS0R0_EN_SHIFT)

/* ASRC Datapath Processor Control Slot0 Register1 (DPCS0R1) */
#घोषणा EASRC_DPCS0R1_ST1_EXP_SHIFT	0
#घोषणा EASRC_DPCS0R1_ST1_EXP_WIDTH	13
#घोषणा EASRC_DPCS0R1_ST1_EXP_MASK	((BIT(EASRC_DPCS0R1_ST1_EXP_WIDTH) - 1) \
					 << EASRC_DPCS0R1_ST1_EXP_SHIFT)
#घोषणा EASRC_DPCS0R1_ST1_EXP(v)	(((v) << EASRC_DPCS0R1_ST1_EXP_SHIFT) \
					 & EASRC_DPCS0R1_ST1_EXP_MASK)

/* ASRC Datapath Processor Control Slot0 Register2 (DPCS0R2) */
#घोषणा EASRC_DPCS0R2_ST1_MA_SHIFT	16
#घोषणा EASRC_DPCS0R2_ST1_MA_WIDTH	13
#घोषणा EASRC_DPCS0R2_ST1_MA_MASK	((BIT(EASRC_DPCS0R2_ST1_MA_WIDTH) - 1) \
					 << EASRC_DPCS0R2_ST1_MA_SHIFT)
#घोषणा EASRC_DPCS0R2_ST1_MA(v)		(((v) << EASRC_DPCS0R2_ST1_MA_SHIFT) \
					 & EASRC_DPCS0R2_ST1_MA_MASK)
#घोषणा EASRC_DPCS0R2_ST1_SA_SHIFT	0
#घोषणा EASRC_DPCS0R2_ST1_SA_WIDTH	13
#घोषणा EASRC_DPCS0R2_ST1_SA_MASK	((BIT(EASRC_DPCS0R2_ST1_SA_WIDTH) - 1) \
					 << EASRC_DPCS0R2_ST1_SA_SHIFT)
#घोषणा EASRC_DPCS0R2_ST1_SA(v)		(((v) << EASRC_DPCS0R2_ST1_SA_SHIFT) \
					 & EASRC_DPCS0R2_ST1_SA_MASK)

/* ASRC Datapath Processor Control Slot0 Register3 (DPCS0R3) */
#घोषणा EASRC_DPCS0R3_ST2_MA_SHIFT	16
#घोषणा EASRC_DPCS0R3_ST2_MA_WIDTH	13
#घोषणा EASRC_DPCS0R3_ST2_MA_MASK	((BIT(EASRC_DPCS0R3_ST2_MA_WIDTH) - 1) \
					 << EASRC_DPCS0R3_ST2_MA_SHIFT)
#घोषणा EASRC_DPCS0R3_ST2_MA(v)		(((v) << EASRC_DPCS0R3_ST2_MA_SHIFT) \
					 & EASRC_DPCS0R3_ST2_MA_MASK)
#घोषणा EASRC_DPCS0R3_ST2_SA_SHIFT	0
#घोषणा EASRC_DPCS0R3_ST2_SA_WIDTH	13
#घोषणा EASRC_DPCS0R3_ST2_SA_MASK	((BIT(EASRC_DPCS0R3_ST2_SA_WIDTH) - 1) \
					 << EASRC_DPCS0R3_ST2_SA_SHIFT)
#घोषणा EASRC_DPCS0R3_ST2_SA(v)		(((v) << EASRC_DPCS0R3_ST2_SA_SHIFT) \
						 & EASRC_DPCS0R3_ST2_SA_MASK)

/* ASRC Context Output Control (COC) */
#घोषणा EASRC_COC_FWMDE_SHIFT		28
#घोषणा EASRC_COC_FWMDE_MASK		BIT(EASRC_COC_FWMDE_SHIFT)
#घोषणा EASRC_COC_FWMDE			BIT(EASRC_COC_FWMDE_SHIFT)
#घोषणा EASRC_COC_FIFO_WTMK_SHIFT	16
#घोषणा EASRC_COC_FIFO_WTMK_WIDTH	7
#घोषणा EASRC_COC_FIFO_WTMK_MASK	((BIT(EASRC_COC_FIFO_WTMK_WIDTH) - 1) \
					 << EASRC_COC_FIFO_WTMK_SHIFT)
#घोषणा EASRC_COC_FIFO_WTMK(v)		(((v) << EASRC_COC_FIFO_WTMK_SHIFT) \
					 & EASRC_COC_FIFO_WTMK_MASK)
#घोषणा EASRC_COC_SAMPLE_POS_SHIFT	11
#घोषणा EASRC_COC_SAMPLE_POS_WIDTH	5
#घोषणा EASRC_COC_SAMPLE_POS_MASK	((BIT(EASRC_COC_SAMPLE_POS_WIDTH) - 1) \
					 << EASRC_COC_SAMPLE_POS_SHIFT)
#घोषणा EASRC_COC_SAMPLE_POS(v)		(((v) << EASRC_COC_SAMPLE_POS_SHIFT) \
					 & EASRC_COC_SAMPLE_POS_MASK)
#घोषणा EASRC_COC_ENDIANNESS_SHIFT	10
#घोषणा EASRC_COC_ENDIANNESS_MASK	BIT(EASRC_COC_ENDIANNESS_SHIFT)
#घोषणा EASRC_COC_ENDIANNESS		BIT(EASRC_COC_ENDIANNESS_SHIFT)
#घोषणा EASRC_COC_BPS_SHIFT		8
#घोषणा EASRC_COC_BPS_WIDTH		2
#घोषणा EASRC_COC_BPS_MASK		((BIT(EASRC_COC_BPS_WIDTH) - 1) \
					 << EASRC_COC_BPS_SHIFT)
#घोषणा EASRC_COC_BPS(v)		(((v) << EASRC_COC_BPS_SHIFT) \
					 & EASRC_COC_BPS_MASK)
#घोषणा EASRC_COC_FMT_SHIFT		7
#घोषणा EASRC_COC_FMT_MASK		BIT(EASRC_COC_FMT_SHIFT)
#घोषणा EASRC_COC_FMT			BIT(EASRC_COC_FMT_SHIFT)
#घोषणा EASRC_COC_OUTSIGN_SHIFT		6
#घोषणा EASRC_COC_OUTSIGN_MASK		BIT(EASRC_COC_OUTSIGN_SHIFT)
#घोषणा EASRC_COC_OUTSIGN_OUT		BIT(EASRC_COC_OUTSIGN_SHIFT)
#घोषणा EASRC_COC_IEC_VDATA_SHIFT	2
#घोषणा EASRC_COC_IEC_VDATA_MASK	BIT(EASRC_COC_IEC_VDATA_SHIFT)
#घोषणा EASRC_COC_IEC_VDATA		BIT(EASRC_COC_IEC_VDATA_SHIFT)
#घोषणा EASRC_COC_IEC_EN_SHIFT		1
#घोषणा EASRC_COC_IEC_EN_MASK		BIT(EASRC_COC_IEC_EN_SHIFT)
#घोषणा EASRC_COC_IEC_EN		BIT(EASRC_COC_IEC_EN_SHIFT)
#घोषणा EASRC_COC_DITHER_EN_SHIFT	0
#घोषणा EASRC_COC_DITHER_EN_MASK	BIT(EASRC_COC_DITHER_EN_SHIFT)
#घोषणा EASRC_COC_DITHER_EN		BIT(EASRC_COC_DITHER_EN_SHIFT)

/* ASRC Control Output Access (COA) */
#घोषणा EASRC_COA_ITER_SHIFT		16
#घोषणा EASRC_COA_ITER_WIDTH		6
#घोषणा EASRC_COA_ITER_MASK		((BIT(EASRC_COA_ITER_WIDTH) - 1) \
					 << EASRC_COA_ITER_SHIFT)
#घोषणा EASRC_COA_ITER(v)		(((v) << EASRC_COA_ITER_SHIFT) \
					 & EASRC_COA_ITER_MASK)
#घोषणा EASRC_COA_GRLEN_SHIFT		8
#घोषणा EASRC_COA_GRLEN_WIDTH		6
#घोषणा EASRC_COA_GRLEN_MASK		((BIT(EASRC_COA_GRLEN_WIDTH) - 1) \
					 << EASRC_COA_GRLEN_SHIFT)
#घोषणा EASRC_COA_GRLEN(v)		(((v) << EASRC_COA_GRLEN_SHIFT) \
					 & EASRC_COA_GRLEN_MASK)
#घोषणा EASRC_COA_ACCLEN_SHIFT		0
#घोषणा EASRC_COA_ACCLEN_WIDTH		6
#घोषणा EASRC_COA_ACCLEN_MASK		((BIT(EASRC_COA_ACCLEN_WIDTH) - 1) \
					 << EASRC_COA_ACCLEN_SHIFT)
#घोषणा EASRC_COA_ACCLEN(v)		(((v) << EASRC_COA_ACCLEN_SHIFT) \
					 & EASRC_COA_ACCLEN_MASK)

/* ASRC Sample FIFO Status (SFS) */
#घोषणा EASRC_SFS_IWTMK_SHIFT		23
#घोषणा EASRC_SFS_IWTMK_MASK		BIT(EASRC_SFS_IWTMK_SHIFT)
#घोषणा EASRC_SFS_IWTMK			BIT(EASRC_SFS_IWTMK_SHIFT)
#घोषणा EASRC_SFS_NSGI_SHIFT		16
#घोषणा EASRC_SFS_NSGI_WIDTH		7
#घोषणा EASRC_SFS_NSGI_MASK		((BIT(EASRC_SFS_NSGI_WIDTH) - 1) \
					 << EASRC_SFS_NSGI_SHIFT)
#घोषणा EASRC_SFS_NSGI(v)		(((v) << EASRC_SFS_NSGI_SHIFT) \
					 & EASRC_SFS_NSGI_MASK)
#घोषणा EASRC_SFS_OWTMK_SHIFT		7
#घोषणा EASRC_SFS_OWTMK_MASK		BIT(EASRC_SFS_OWTMK_SHIFT)
#घोषणा EASRC_SFS_OWTMK			BIT(EASRC_SFS_OWTMK_SHIFT)
#घोषणा EASRC_SFS_NSGO_SHIFT		0
#घोषणा EASRC_SFS_NSGO_WIDTH		7
#घोषणा EASRC_SFS_NSGO_MASK		((BIT(EASRC_SFS_NSGO_WIDTH) - 1) \
					 << EASRC_SFS_NSGO_SHIFT)
#घोषणा EASRC_SFS_NSGO(v)		(((v) << EASRC_SFS_NSGO_SHIFT) \
					 & EASRC_SFS_NSGO_MASK)

/* ASRC Resampling Ratio Low (RRL) */
#घोषणा EASRC_RRL_RS_RL_SHIFT		0
#घोषणा EASRC_RRL_RS_RL_WIDTH		32
#घोषणा EASRC_RRL_RS_RL(v)		((v) << EASRC_RRL_RS_RL_SHIFT)

/* ASRC Resampling Ratio High (RRH) */
#घोषणा EASRC_RRH_RS_VLD_SHIFT		31
#घोषणा EASRC_RRH_RS_VLD_MASK		BIT(EASRC_RRH_RS_VLD_SHIFT)
#घोषणा EASRC_RRH_RS_VLD		BIT(EASRC_RRH_RS_VLD_SHIFT)
#घोषणा EASRC_RRH_RS_RH_SHIFT		0
#घोषणा EASRC_RRH_RS_RH_WIDTH		12
#घोषणा EASRC_RRH_RS_RH_MASK		((BIT(EASRC_RRH_RS_RH_WIDTH) - 1) \
					 << EASRC_RRH_RS_RH_SHIFT)
#घोषणा EASRC_RRH_RS_RH(v)		(((v) << EASRC_RRH_RS_RH_SHIFT) \
					 & EASRC_RRH_RS_RH_MASK)

/* ASRC Resampling Ratio Update Control (RSUC) */
#घोषणा EASRC_RSUC_RS_RM_SHIFT		0
#घोषणा EASRC_RSUC_RS_RM_WIDTH		32
#घोषणा EASRC_RSUC_RS_RM(v)		((v) << EASRC_RSUC_RS_RM_SHIFT)

/* ASRC Resampling Ratio Update Rate (RRUR) */
#घोषणा EASRC_RRUR_RRR_SHIFT		0
#घोषणा EASRC_RRUR_RRR_WIDTH		31
#घोषणा EASRC_RRUR_RRR_MASK		((BIT(EASRC_RRUR_RRR_WIDTH) - 1) \
					 << EASRC_RRUR_RRR_SHIFT)
#घोषणा EASRC_RRUR_RRR(v)		(((v) << EASRC_RRUR_RRR_SHIFT) \
					 & EASRC_RRUR_RRR_MASK)

/* ASRC Resampling Center Tap Coefficient Low (RCTCL) */
#घोषणा EASRC_RCTCL_RS_CL_SHIFT		0
#घोषणा EASRC_RCTCL_RS_CL_WIDTH		32
#घोषणा EASRC_RCTCL_RS_CL(v)		((v) << EASRC_RCTCL_RS_CL_SHIFT)

/* ASRC Resampling Center Tap Coefficient High (RCTCH) */
#घोषणा EASRC_RCTCH_RS_CH_SHIFT		0
#घोषणा EASRC_RCTCH_RS_CH_WIDTH		32
#घोषणा EASRC_RCTCH_RS_CH(v)		((v) << EASRC_RCTCH_RS_CH_SHIFT)

/* ASRC Prefilter Coefficient FIFO (PCF) */
#घोषणा EASRC_PCF_CD_SHIFT		0
#घोषणा EASRC_PCF_CD_WIDTH		32
#घोषणा EASRC_PCF_CD(v)			((v) << EASRC_PCF_CD_SHIFT)

/* ASRC Context Resampling Coefficient Memory (CRCM) */
#घोषणा EASRC_CRCM_RS_CWD_SHIFT		0
#घोषणा EASRC_CRCM_RS_CWD_WIDTH		32
#घोषणा EASRC_CRCM_RS_CWD(v)		((v) << EASRC_CRCM_RS_CWD_SHIFT)

/* ASRC Context Resampling Coefficient Control (CRCC) */
#घोषणा EASRC_CRCC_RS_CA_SHIFT		16
#घोषणा EASRC_CRCC_RS_CA_WIDTH		11
#घोषणा EASRC_CRCC_RS_CA_MASK		((BIT(EASRC_CRCC_RS_CA_WIDTH) - 1) \
					 << EASRC_CRCC_RS_CA_SHIFT)
#घोषणा EASRC_CRCC_RS_CA(v)		(((v) << EASRC_CRCC_RS_CA_SHIFT) \
					 & EASRC_CRCC_RS_CA_MASK)
#घोषणा EASRC_CRCC_RS_TAPS_SHIFT	1
#घोषणा EASRC_CRCC_RS_TAPS_WIDTH	2
#घोषणा EASRC_CRCC_RS_TAPS_MASK		((BIT(EASRC_CRCC_RS_TAPS_WIDTH) - 1) \
					 << EASRC_CRCC_RS_TAPS_SHIFT)
#घोषणा EASRC_CRCC_RS_TAPS(v)		(((v) << EASRC_CRCC_RS_TAPS_SHIFT) \
					 & EASRC_CRCC_RS_TAPS_MASK)
#घोषणा EASRC_CRCC_RS_CPR_SHIFT		0
#घोषणा EASRC_CRCC_RS_CPR_MASK		BIT(EASRC_CRCC_RS_CPR_SHIFT)
#घोषणा EASRC_CRCC_RS_CPR		BIT(EASRC_CRCC_RS_CPR_SHIFT)

/* ASRC Interrupt_Control (IC) */
#घोषणा EASRC_IRQC_RSDM_SHIFT		8
#घोषणा EASRC_IRQC_RSDM_WIDTH		4
#घोषणा EASRC_IRQC_RSDM_MASK		((BIT(EASRC_IRQC_RSDM_WIDTH) - 1) \
					 << EASRC_IRQC_RSDM_SHIFT)
#घोषणा EASRC_IRQC_RSDM(v)		(((v) << EASRC_IRQC_RSDM_SHIFT) \
					 & EASRC_IRQC_RSDM_MASK)
#घोषणा EASRC_IRQC_OERM_SHIFT		4
#घोषणा EASRC_IRQC_OERM_WIDTH		4
#घोषणा EASRC_IRQC_OERM_MASK		((BIT(EASRC_IRQC_OERM_WIDTH) - 1) \
					 << EASRC_IRQC_OERM_SHIFT)
#घोषणा EASRC_IRQC_OERM(v)		(((v) << EASRC_IRQC_OERM_SHIFT) \
					 & EASRC_IEQC_OERM_MASK)
#घोषणा EASRC_IRQC_IOM_SHIFT		0
#घोषणा EASRC_IRQC_IOM_WIDTH		4
#घोषणा EASRC_IRQC_IOM_MASK		((BIT(EASRC_IRQC_IOM_WIDTH) - 1) \
					 << EASRC_IRQC_IOM_SHIFT)
#घोषणा EASRC_IRQC_IOM(v)		(((v) << EASRC_IRQC_IOM_SHIFT) \
					 & EASRC_IRQC_IOM_MASK)

/* ASRC Interrupt Status Flags (ISF) */
#घोषणा EASRC_IRQF_RSD_SHIFT		8
#घोषणा EASRC_IRQF_RSD_WIDTH		4
#घोषणा EASRC_IRQF_RSD_MASK		((BIT(EASRC_IRQF_RSD_WIDTH) - 1) \
					 << EASRC_IRQF_RSD_SHIFT)
#घोषणा EASRC_IRQF_RSD(v)		(((v) << EASRC_IRQF_RSD_SHIFT) \
					 & EASRC_IRQF_RSD_MASK)
#घोषणा EASRC_IRQF_OER_SHIFT		4
#घोषणा EASRC_IRQF_OER_WIDTH		4
#घोषणा EASRC_IRQF_OER_MASK		((BIT(EASRC_IRQF_OER_WIDTH) - 1) \
					 << EASRC_IRQF_OER_SHIFT)
#घोषणा EASRC_IRQF_OER(v)		(((v) << EASRC_IRQF_OER_SHIFT) \
					 & EASRC_IRQF_OER_MASK)
#घोषणा EASRC_IRQF_IFO_SHIFT		0
#घोषणा EASRC_IRQF_IFO_WIDTH		4
#घोषणा EASRC_IRQF_IFO_MASK		((BIT(EASRC_IRQF_IFO_WIDTH) - 1) \
					 << EASRC_IRQF_IFO_SHIFT)
#घोषणा EASRC_IRQF_IFO(v)		(((v) << EASRC_IRQF_IFO_SHIFT) \
					 & EASRC_IRQF_IFO_MASK)

/* ASRC Context Channel STAT */
#घोषणा EASRC_CSx_CSx_SHIFT		0
#घोषणा EASRC_CSx_CSx_WIDTH		32
#घोषणा EASRC_CSx_CSx(v)		((v) << EASRC_CSx_CSx_SHIFT)

/* ASRC Debug Control Register */
#घोषणा EASRC_DBGC_DMS_SHIFT		0
#घोषणा EASRC_DBGC_DMS_WIDTH		6
#घोषणा EASRC_DBGC_DMS_MASK		((BIT(EASRC_DBGC_DMS_WIDTH) - 1) \
					 << EASRC_DBGC_DMS_SHIFT)
#घोषणा EASRC_DBGC_DMS(v)		(((v) << EASRC_DBGC_DMS_SHIFT) \
					 & EASRC_DBGC_DMS_MASK)

/* ASRC Debug Status Register */
#घोषणा EASRC_DBGS_DS_SHIFT		0
#घोषणा EASRC_DBGS_DS_WIDTH		32
#घोषणा EASRC_DBGS_DS(v)		((v) << EASRC_DBGS_DS_SHIFT)

/* General Constants */
#घोषणा EASRC_CTX_MAX_NUM		4
#घोषणा EASRC_RS_COEFF_MEM		0
#घोषणा EASRC_PF_COEFF_MEM		1

/* Prefilter स्थिरants */
#घोषणा EASRC_PF_ST1_ONLY		0
#घोषणा EASRC_PF_TWO_STAGE_MODE		1
#घोषणा EASRC_PF_ST1_COEFF_WR		0
#घोषणा EASRC_PF_ST2_COEFF_WR		1
#घोषणा EASRC_MAX_PF_TAPS		384

/* Resampling स्थिरants */
#घोषणा EASRC_RS_32_TAPS		0
#घोषणा EASRC_RS_64_TAPS		1
#घोषणा EASRC_RS_128_TAPS		2

/* Initialization mode */
#घोषणा EASRC_INIT_MODE_SW_CONTROL	0
#घोषणा EASRC_INIT_MODE_REPLICATE	1
#घोषणा EASRC_INIT_MODE_ZERO_FILL	2

/* FIFO watermarks */
#घोषणा FSL_EASRC_INPUTFIFO_WML		0x4
#घोषणा FSL_EASRC_OUTPUTFIFO_WML	0x1

#घोषणा EASRC_INPUTFIFO_THRESHOLD_MIN	0
#घोषणा EASRC_INPUTFIFO_THRESHOLD_MAX	127
#घोषणा EASRC_OUTPUTFIFO_THRESHOLD_MIN	0
#घोषणा EASRC_OUTPUTFIFO_THRESHOLD_MAX	63

#घोषणा EASRC_DMA_BUFFER_SIZE		(1024 * 48 * 9)
#घोषणा EASRC_MAX_BUFFER_SIZE		(1024 * 48)

#घोषणा FIRMWARE_MAGIC			0xDEAD
#घोषणा FIRMWARE_VERSION		1

#घोषणा PREFILTER_MEM_LEN		0x1800

क्रमागत easrc_word_width अणु
	EASRC_WIDTH_16_BIT = 0,
	EASRC_WIDTH_20_BIT = 1,
	EASRC_WIDTH_24_BIT = 2,
	EASRC_WIDTH_32_BIT = 3,
पूर्ण;

काष्ठा __attribute__((__packed__))  asrc_firmware_hdr अणु
	u32 magic;
	u32 पूर्णांकerp_scen;
	u32 prefil_scen;
	u32 firmware_version;
पूर्ण;

काष्ठा __attribute__((__packed__)) पूर्णांकerp_params अणु
	u32 magic;
	u32 num_taps;
	u32 num_phases;
	u64 center_tap;
	u64 coeff[8192];
पूर्ण;

काष्ठा __attribute__((__packed__)) prefil_params अणु
	u32 magic;
	u32 insr;
	u32 outsr;
	u32 st1_taps;
	u32 st2_taps;
	u32 st1_exp;
	u64 coeff[256];
पूर्ण;

काष्ठा dma_block अणु
	व्योम *dma_vaddr;
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक max_buf_size;
पूर्ण;

काष्ठा fsl_easrc_data_fmt अणु
	अचिन्हित पूर्णांक width : 2;
	अचिन्हित पूर्णांक endianness : 1;
	अचिन्हित पूर्णांक unsign : 1;
	अचिन्हित पूर्णांक भग्नing_poपूर्णांक : 1;
	अचिन्हित पूर्णांक iec958: 1;
	अचिन्हित पूर्णांक sample_pos: 5;
	अचिन्हित पूर्णांक addexp;
पूर्ण;

काष्ठा fsl_easrc_io_params अणु
	काष्ठा fsl_easrc_data_fmt fmt;
	अचिन्हित पूर्णांक group_len;
	अचिन्हित पूर्णांक iterations;
	अचिन्हित पूर्णांक access_len;
	अचिन्हित पूर्णांक fअगरo_wपंचांगk;
	अचिन्हित पूर्णांक sample_rate;
	अचिन्हित पूर्णांक sample_क्रमmat;
	अचिन्हित पूर्णांक norm_rate;
पूर्ण;

काष्ठा fsl_easrc_slot अणु
	bool busy;
	पूर्णांक ctx_index;
	पूर्णांक slot_index;
	पूर्णांक num_channel;  /* maximum is 8 */
	पूर्णांक min_channel;
	पूर्णांक max_channel;
	पूर्णांक pf_mem_used;
पूर्ण;

/**
 * fsl_easrc_ctx_priv: EASRC context निजी data
 *
 * @in_params: input parameter
 * @out_params:  output parameter
 * @st1_num_taps: tap number of stage 1
 * @st2_num_taps: tap number of stage 2
 * @st1_num_exp: exponent number of stage 1
 * @pf_init_mode: prefilter init mode
 * @rs_init_mode:  resample filter init mode
 * @ctx_streams: stream flag of ctx
 * @rs_ratio: resampler ratio
 * @st1_coeff: poपूर्णांकer of stage 1 coeff
 * @st2_coeff: poपूर्णांकer of stage 2 coeff
 * @in_filled_sample: input filled sample
 * @out_missed_sample: sample missed in output
 * @st1_addexp: exponent added क्रम stage1
 * @st2_addexp: exponent added क्रम stage2
 */
काष्ठा fsl_easrc_ctx_priv अणु
	काष्ठा fsl_easrc_io_params in_params;
	काष्ठा fsl_easrc_io_params out_params;
	अचिन्हित पूर्णांक st1_num_taps;
	अचिन्हित पूर्णांक st2_num_taps;
	अचिन्हित पूर्णांक st1_num_exp;
	अचिन्हित पूर्णांक pf_init_mode;
	अचिन्हित पूर्णांक rs_init_mode;
	अचिन्हित पूर्णांक ctx_streams;
	u64 rs_ratio;
	u64 *st1_coeff;
	u64 *st2_coeff;
	पूर्णांक in_filled_sample;
	पूर्णांक out_missed_sample;
	पूर्णांक st1_addexp;
	पूर्णांक st2_addexp;
पूर्ण;

/**
 * fsl_easrc_priv: EASRC निजी data
 *
 * @slot: slot setting
 * @firmware_hdr:  the header of firmware
 * @पूर्णांकerp: poपूर्णांकer to पूर्णांकerpolation filter coeff
 * @prefil: poपूर्णांकer to prefilter coeff
 * @fw: firmware of coeff table
 * @fw_name: firmware name
 * @rs_num_taps:  resample filter taps, 32, 64, or 128
 * @bps_iec958: bits per sample of iec958
 * @rs_coeff: resampler coefficient
 * @स्थिर_coeff: one tap prefilter coefficient
 * @firmware_loaded: firmware is loaded
 */
काष्ठा fsl_easrc_priv अणु
	काष्ठा fsl_easrc_slot slot[EASRC_CTX_MAX_NUM][2];
	काष्ठा asrc_firmware_hdr *firmware_hdr;
	काष्ठा पूर्णांकerp_params *पूर्णांकerp;
	काष्ठा prefil_params *prefil;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_name;
	अचिन्हित पूर्णांक rs_num_taps;
	अचिन्हित पूर्णांक bps_iec958[EASRC_CTX_MAX_NUM];
	u64 *rs_coeff;
	u64 स्थिर_coeff;
	पूर्णांक firmware_loaded;
पूर्ण;
#पूर्ण_अगर /* _FSL_EASRC_H */
