<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015-2020, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>
#समावेश <soc/tegra/fuse.h>
#समावेश <soc/tegra/mc.h>

#समावेश "tegra210-emc.h"
#समावेश "tegra210-mc.h"

/* CLK_RST_CONTROLLER_CLK_SOURCE_EMC */
#घोषणा EMC_CLK_EMC_2X_CLK_SRC_SHIFT			29
#घोषणा EMC_CLK_EMC_2X_CLK_SRC_MASK			\
	(0x7 << EMC_CLK_EMC_2X_CLK_SRC_SHIFT)
#घोषणा EMC_CLK_SOURCE_PLLM_LJ				0x4
#घोषणा EMC_CLK_SOURCE_PLLMB_LJ				0x5
#घोषणा EMC_CLK_FORCE_CC_TRIGGER			BIT(27)
#घोषणा EMC_CLK_MC_EMC_SAME_FREQ			BIT(16)
#घोषणा EMC_CLK_EMC_2X_CLK_DIVISOR_SHIFT		0
#घोषणा EMC_CLK_EMC_2X_CLK_DIVISOR_MASK			\
	(0xff << EMC_CLK_EMC_2X_CLK_DIVISOR_SHIFT)

/* CLK_RST_CONTROLLER_CLK_SOURCE_EMC_DLL */
#घोषणा DLL_CLK_EMC_DLL_CLK_SRC_SHIFT			29
#घोषणा DLL_CLK_EMC_DLL_CLK_SRC_MASK			\
	(0x7 << DLL_CLK_EMC_DLL_CLK_SRC_SHIFT)
#घोषणा DLL_CLK_EMC_DLL_DDLL_CLK_SEL_SHIFT		10
#घोषणा DLL_CLK_EMC_DLL_DDLL_CLK_SEL_MASK		\
	(0x3 << DLL_CLK_EMC_DLL_DDLL_CLK_SEL_SHIFT)
#घोषणा PLLM_VCOA					0
#घोषणा PLLM_VCOB					1
#घोषणा EMC_DLL_SWITCH_OUT				2
#घोषणा DLL_CLK_EMC_DLL_CLK_DIVISOR_SHIFT		0
#घोषणा DLL_CLK_EMC_DLL_CLK_DIVISOR_MASK		\
	(0xff << DLL_CLK_EMC_DLL_CLK_DIVISOR_SHIFT)

/* MC_EMEM_ARB_MISC0 */
#घोषणा MC_EMEM_ARB_MISC0_EMC_SAME_FREQ			BIT(27)

/* EMC_DATA_BRLSHFT_X */
#घोषणा EMC0_EMC_DATA_BRLSHFT_0_INDEX	2
#घोषणा EMC1_EMC_DATA_BRLSHFT_0_INDEX	3
#घोषणा EMC0_EMC_DATA_BRLSHFT_1_INDEX	4
#घोषणा EMC1_EMC_DATA_BRLSHFT_1_INDEX	5

#घोषणा TRIM_REG(chan, rank, reg, byte)					\
	(((EMC_PMACRO_OB_DDLL_LONG_DQ_RANK ## rank ## _ ## reg ##	\
	   _OB_DDLL_LONG_DQ_RANK ## rank ## _BYTE ## byte ## _MASK &	\
	   next->trim_regs[EMC_PMACRO_OB_DDLL_LONG_DQ_RANK ##		\
				 rank ## _ ## reg ## _INDEX]) >>	\
	  EMC_PMACRO_OB_DDLL_LONG_DQ_RANK ## rank ## _ ## reg ##	\
	  _OB_DDLL_LONG_DQ_RANK ## rank ## _BYTE ## byte ## _SHIFT)	\
	 +								\
	 (((EMC_DATA_BRLSHFT_ ## rank ## _RANK ## rank ## _BYTE ##	\
	    byte ## _DATA_BRLSHFT_MASK &				\
	    next->trim_perch_regs[EMC ## chan ##			\
			      _EMC_DATA_BRLSHFT_ ## rank ## _INDEX]) >>	\
	   EMC_DATA_BRLSHFT_ ## rank ## _RANK ## rank ## _BYTE ##	\
	   byte ## _DATA_BRLSHFT_SHIFT) * 64))

#घोषणा CALC_TEMP(rank, reg, byte1, byte2, n)				\
	(((new[n] << EMC_PMACRO_OB_DDLL_LONG_DQ_RANK ## rank ## _ ##	\
	   reg ## _OB_DDLL_LONG_DQ_RANK ## rank ## _BYTE ## byte1 ## _SHIFT) & \
	  EMC_PMACRO_OB_DDLL_LONG_DQ_RANK ## rank ## _ ## reg ##	\
	  _OB_DDLL_LONG_DQ_RANK ## rank ## _BYTE ## byte1 ## _MASK)	\
	 |								\
	 ((new[n + 1] << EMC_PMACRO_OB_DDLL_LONG_DQ_RANK ## rank ## _ ##\
	   reg ## _OB_DDLL_LONG_DQ_RANK ## rank ## _BYTE ## byte2 ## _SHIFT) & \
	  EMC_PMACRO_OB_DDLL_LONG_DQ_RANK ## rank ## _ ## reg ##	\
	  _OB_DDLL_LONG_DQ_RANK ## rank ## _BYTE ## byte2 ## _MASK))

#घोषणा REFRESH_SPEEDUP(value, speedup) \
		(((value) & 0xffff0000) | ((value) & 0xffff) * (speedup))

#घोषणा LPDDR2_MR4_SRR GENMASK(2, 0)

अटल स्थिर काष्ठा tegra210_emc_sequence *tegra210_emc_sequences[] = अणु
	&tegra210_emc_r21021,
पूर्ण;

अटल स्थिर काष्ठा tegra210_emc_table_रेजिस्टर_offsets
tegra210_emc_table_रेजिस्टर_offsets = अणु
	.burst = अणु
		EMC_RC,
		EMC_RFC,
		EMC_RFCPB,
		EMC_REFCTRL2,
		EMC_RFC_SLR,
		EMC_RAS,
		EMC_RP,
		EMC_R2W,
		EMC_W2R,
		EMC_R2P,
		EMC_W2P,
		EMC_R2R,
		EMC_TPPD,
		EMC_CCDMW,
		EMC_RD_RCD,
		EMC_WR_RCD,
		EMC_RRD,
		EMC_REXT,
		EMC_WEXT,
		EMC_WDV_CHK,
		EMC_WDV,
		EMC_WSV,
		EMC_WEV,
		EMC_WDV_MASK,
		EMC_WS_DURATION,
		EMC_WE_DURATION,
		EMC_QUSE,
		EMC_QUSE_WIDTH,
		EMC_IBDLY,
		EMC_OBDLY,
		EMC_EINPUT,
		EMC_MRW6,
		EMC_EINPUT_DURATION,
		EMC_PUTERM_EXTRA,
		EMC_PUTERM_WIDTH,
		EMC_QRST,
		EMC_QSAFE,
		EMC_RDV,
		EMC_RDV_MASK,
		EMC_RDV_EARLY,
		EMC_RDV_EARLY_MASK,
		EMC_REFRESH,
		EMC_BURST_REFRESH_NUM,
		EMC_PRE_REFRESH_REQ_CNT,
		EMC_PDEX2WR,
		EMC_PDEX2RD,
		EMC_PCHG2PDEN,
		EMC_ACT2PDEN,
		EMC_AR2PDEN,
		EMC_RW2PDEN,
		EMC_CKE2PDEN,
		EMC_PDEX2CKE,
		EMC_PDEX2MRR,
		EMC_TXSR,
		EMC_TXSRDLL,
		EMC_TCKE,
		EMC_TCKESR,
		EMC_TPD,
		EMC_TFAW,
		EMC_TRPAB,
		EMC_TCLKSTABLE,
		EMC_TCLKSTOP,
		EMC_MRW7,
		EMC_TREFBW,
		EMC_ODT_WRITE,
		EMC_FBIO_CFG5,
		EMC_FBIO_CFG7,
		EMC_CFG_DIG_DLL,
		EMC_CFG_DIG_DLL_PERIOD,
		EMC_PMACRO_IB_RXRT,
		EMC_CFG_PIPE_1,
		EMC_CFG_PIPE_2,
		EMC_PMACRO_QUSE_DDLL_RANK0_4,
		EMC_PMACRO_QUSE_DDLL_RANK0_5,
		EMC_PMACRO_QUSE_DDLL_RANK1_4,
		EMC_PMACRO_QUSE_DDLL_RANK1_5,
		EMC_MRW8,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_4,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_5,
		EMC_PMACRO_OB_DDLL_LONG_DQS_RANK0_0,
		EMC_PMACRO_OB_DDLL_LONG_DQS_RANK0_1,
		EMC_PMACRO_OB_DDLL_LONG_DQS_RANK0_2,
		EMC_PMACRO_OB_DDLL_LONG_DQS_RANK0_3,
		EMC_PMACRO_OB_DDLL_LONG_DQS_RANK0_4,
		EMC_PMACRO_OB_DDLL_LONG_DQS_RANK0_5,
		EMC_PMACRO_OB_DDLL_LONG_DQS_RANK1_0,
		EMC_PMACRO_OB_DDLL_LONG_DQS_RANK1_1,
		EMC_PMACRO_OB_DDLL_LONG_DQS_RANK1_2,
		EMC_PMACRO_OB_DDLL_LONG_DQS_RANK1_3,
		EMC_PMACRO_OB_DDLL_LONG_DQS_RANK1_4,
		EMC_PMACRO_OB_DDLL_LONG_DQS_RANK1_5,
		EMC_PMACRO_DDLL_LONG_CMD_0,
		EMC_PMACRO_DDLL_LONG_CMD_1,
		EMC_PMACRO_DDLL_LONG_CMD_2,
		EMC_PMACRO_DDLL_LONG_CMD_3,
		EMC_PMACRO_DDLL_LONG_CMD_4,
		EMC_PMACRO_DDLL_SHORT_CMD_0,
		EMC_PMACRO_DDLL_SHORT_CMD_1,
		EMC_PMACRO_DDLL_SHORT_CMD_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE0_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE1_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE2_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE3_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE4_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE5_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE6_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE7_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD0_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD1_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD2_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD3_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE0_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE1_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE2_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE3_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE4_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE5_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE6_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE7_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD0_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD0_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD0_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD0_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD1_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD1_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD1_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD1_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD2_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD2_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD2_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD2_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD3_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD3_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD3_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD3_3,
		EMC_TXDSRVTTGEN,
		EMC_FDPD_CTRL_DQ,
		EMC_FDPD_CTRL_CMD,
		EMC_FBIO_SPARE,
		EMC_ZCAL_INTERVAL,
		EMC_ZCAL_WAIT_CNT,
		EMC_MRS_WAIT_CNT,
		EMC_MRS_WAIT_CNT2,
		EMC_AUTO_CAL_CHANNEL,
		EMC_DLL_CFG_0,
		EMC_DLL_CFG_1,
		EMC_PMACRO_AUTOCAL_CFG_COMMON,
		EMC_PMACRO_ZCTRL,
		EMC_CFG,
		EMC_CFG_PIPE,
		EMC_DYN_SELF_REF_CONTROL,
		EMC_QPOP,
		EMC_DQS_BRLSHFT_0,
		EMC_DQS_BRLSHFT_1,
		EMC_CMD_BRLSHFT_2,
		EMC_CMD_BRLSHFT_3,
		EMC_PMACRO_PAD_CFG_CTRL,
		EMC_PMACRO_DATA_PAD_RX_CTRL,
		EMC_PMACRO_CMD_PAD_RX_CTRL,
		EMC_PMACRO_DATA_RX_TERM_MODE,
		EMC_PMACRO_CMD_RX_TERM_MODE,
		EMC_PMACRO_CMD_PAD_TX_CTRL,
		EMC_PMACRO_DATA_PAD_TX_CTRL,
		EMC_PMACRO_COMMON_PAD_TX_CTRL,
		EMC_PMACRO_VTTGEN_CTRL_0,
		EMC_PMACRO_VTTGEN_CTRL_1,
		EMC_PMACRO_VTTGEN_CTRL_2,
		EMC_PMACRO_BRICK_CTRL_RFU1,
		EMC_PMACRO_CMD_BRICK_CTRL_FDPD,
		EMC_PMACRO_BRICK_CTRL_RFU2,
		EMC_PMACRO_DATA_BRICK_CTRL_FDPD,
		EMC_PMACRO_BG_BIAS_CTRL_0,
		EMC_CFG_3,
		EMC_PMACRO_TX_PWRD_0,
		EMC_PMACRO_TX_PWRD_1,
		EMC_PMACRO_TX_PWRD_2,
		EMC_PMACRO_TX_PWRD_3,
		EMC_PMACRO_TX_PWRD_4,
		EMC_PMACRO_TX_PWRD_5,
		EMC_CONFIG_SAMPLE_DELAY,
		EMC_PMACRO_TX_SEL_CLK_SRC_0,
		EMC_PMACRO_TX_SEL_CLK_SRC_1,
		EMC_PMACRO_TX_SEL_CLK_SRC_2,
		EMC_PMACRO_TX_SEL_CLK_SRC_3,
		EMC_PMACRO_TX_SEL_CLK_SRC_4,
		EMC_PMACRO_TX_SEL_CLK_SRC_5,
		EMC_PMACRO_DDLL_BYPASS,
		EMC_PMACRO_DDLL_PWRD_0,
		EMC_PMACRO_DDLL_PWRD_1,
		EMC_PMACRO_DDLL_PWRD_2,
		EMC_PMACRO_CMD_CTRL_0,
		EMC_PMACRO_CMD_CTRL_1,
		EMC_PMACRO_CMD_CTRL_2,
		EMC_TR_TIMING_0,
		EMC_TR_DVFS,
		EMC_TR_CTRL_1,
		EMC_TR_RDV,
		EMC_TR_QPOP,
		EMC_TR_RDV_MASK,
		EMC_MRW14,
		EMC_TR_QSAFE,
		EMC_TR_QRST,
		EMC_TRAINING_CTRL,
		EMC_TRAINING_SETTLE,
		EMC_TRAINING_VREF_SETTLE,
		EMC_TRAINING_CA_FINE_CTRL,
		EMC_TRAINING_CA_CTRL_MISC,
		EMC_TRAINING_CA_CTRL_MISC1,
		EMC_TRAINING_CA_VREF_CTRL,
		EMC_TRAINING_QUSE_CORS_CTRL,
		EMC_TRAINING_QUSE_FINE_CTRL,
		EMC_TRAINING_QUSE_CTRL_MISC,
		EMC_TRAINING_QUSE_VREF_CTRL,
		EMC_TRAINING_READ_FINE_CTRL,
		EMC_TRAINING_READ_CTRL_MISC,
		EMC_TRAINING_READ_VREF_CTRL,
		EMC_TRAINING_WRITE_FINE_CTRL,
		EMC_TRAINING_WRITE_CTRL_MISC,
		EMC_TRAINING_WRITE_VREF_CTRL,
		EMC_TRAINING_MPC,
		EMC_MRW15,
	पूर्ण,
	.trim = अणु
		EMC_PMACRO_IB_DDLL_LONG_DQS_RANK0_0,
		EMC_PMACRO_IB_DDLL_LONG_DQS_RANK0_1,
		EMC_PMACRO_IB_DDLL_LONG_DQS_RANK0_2,
		EMC_PMACRO_IB_DDLL_LONG_DQS_RANK0_3,
		EMC_PMACRO_IB_DDLL_LONG_DQS_RANK1_0,
		EMC_PMACRO_IB_DDLL_LONG_DQS_RANK1_1,
		EMC_PMACRO_IB_DDLL_LONG_DQS_RANK1_2,
		EMC_PMACRO_IB_DDLL_LONG_DQS_RANK1_3,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE0_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE0_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE0_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE1_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE1_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE1_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE2_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE2_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE2_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE3_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE3_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE3_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE4_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE4_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE4_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE5_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE5_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE5_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE6_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE6_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE6_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE7_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE7_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE7_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE0_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE0_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE0_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE1_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE1_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE1_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE2_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE2_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE2_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE3_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE3_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE3_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE4_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE4_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE4_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE5_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE5_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE5_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE6_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE6_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE6_2,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE7_0,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE7_1,
		EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE7_2,
		EMC_PMACRO_IB_VREF_DQS_0,
		EMC_PMACRO_IB_VREF_DQS_1,
		EMC_PMACRO_IB_VREF_DQ_0,
		EMC_PMACRO_IB_VREF_DQ_1,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_0,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_1,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_2,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_3,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_4,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_5,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_0,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_1,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_2,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_3,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE0_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE0_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE0_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE1_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE1_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE1_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE2_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE2_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE2_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE3_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE3_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE3_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE4_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE4_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE4_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE5_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE5_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE5_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE6_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE6_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE6_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE7_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE7_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE7_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD0_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD0_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD0_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD1_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD1_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD1_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD2_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD2_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD2_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD3_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD3_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD3_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE0_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE0_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE0_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE1_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE1_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE1_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE2_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE2_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE2_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE3_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE3_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE3_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE4_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE4_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE4_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE5_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE5_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE5_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE6_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE6_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE6_2,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE7_0,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE7_1,
		EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE7_2,
		EMC_PMACRO_QUSE_DDLL_RANK0_0,
		EMC_PMACRO_QUSE_DDLL_RANK0_1,
		EMC_PMACRO_QUSE_DDLL_RANK0_2,
		EMC_PMACRO_QUSE_DDLL_RANK0_3,
		EMC_PMACRO_QUSE_DDLL_RANK1_0,
		EMC_PMACRO_QUSE_DDLL_RANK1_1,
		EMC_PMACRO_QUSE_DDLL_RANK1_2,
		EMC_PMACRO_QUSE_DDLL_RANK1_3
	पूर्ण,
	.burst_mc = अणु
		MC_EMEM_ARB_CFG,
		MC_EMEM_ARB_OUTSTANDING_REQ,
		MC_EMEM_ARB_REFPB_HP_CTRL,
		MC_EMEM_ARB_REFPB_BANK_CTRL,
		MC_EMEM_ARB_TIMING_RCD,
		MC_EMEM_ARB_TIMING_RP,
		MC_EMEM_ARB_TIMING_RC,
		MC_EMEM_ARB_TIMING_RAS,
		MC_EMEM_ARB_TIMING_FAW,
		MC_EMEM_ARB_TIMING_RRD,
		MC_EMEM_ARB_TIMING_RAP2PRE,
		MC_EMEM_ARB_TIMING_WAP2PRE,
		MC_EMEM_ARB_TIMING_R2R,
		MC_EMEM_ARB_TIMING_W2W,
		MC_EMEM_ARB_TIMING_R2W,
		MC_EMEM_ARB_TIMING_CCDMW,
		MC_EMEM_ARB_TIMING_W2R,
		MC_EMEM_ARB_TIMING_RFCPB,
		MC_EMEM_ARB_DA_TURNS,
		MC_EMEM_ARB_DA_COVERS,
		MC_EMEM_ARB_MISC0,
		MC_EMEM_ARB_MISC1,
		MC_EMEM_ARB_MISC2,
		MC_EMEM_ARB_RING1_THROTTLE,
		MC_EMEM_ARB_DHYST_CTRL,
		MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_0,
		MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_1,
		MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_2,
		MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_3,
		MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_4,
		MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_5,
		MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_6,
		MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_7,
	पूर्ण,
	.la_scale = अणु
		MC_MLL_MPCORER_PTSA_RATE,
		MC_FTOP_PTSA_RATE,
		MC_PTSA_GRANT_DECREMENT,
		MC_LATENCY_ALLOWANCE_XUSB_0,
		MC_LATENCY_ALLOWANCE_XUSB_1,
		MC_LATENCY_ALLOWANCE_TSEC_0,
		MC_LATENCY_ALLOWANCE_SDMMCA_0,
		MC_LATENCY_ALLOWANCE_SDMMCAA_0,
		MC_LATENCY_ALLOWANCE_SDMMC_0,
		MC_LATENCY_ALLOWANCE_SDMMCAB_0,
		MC_LATENCY_ALLOWANCE_PPCS_0,
		MC_LATENCY_ALLOWANCE_PPCS_1,
		MC_LATENCY_ALLOWANCE_MPCORE_0,
		MC_LATENCY_ALLOWANCE_HC_0,
		MC_LATENCY_ALLOWANCE_HC_1,
		MC_LATENCY_ALLOWANCE_AVPC_0,
		MC_LATENCY_ALLOWANCE_GPU_0,
		MC_LATENCY_ALLOWANCE_GPU2_0,
		MC_LATENCY_ALLOWANCE_NVENC_0,
		MC_LATENCY_ALLOWANCE_NVDEC_0,
		MC_LATENCY_ALLOWANCE_VIC_0,
		MC_LATENCY_ALLOWANCE_VI2_0,
		MC_LATENCY_ALLOWANCE_ISP2_0,
		MC_LATENCY_ALLOWANCE_ISP2_1,
	पूर्ण,
	.burst_per_channel = अणु
		अणु .bank = 0, .offset = EMC_MRW10, पूर्ण,
		अणु .bank = 1, .offset = EMC_MRW10, पूर्ण,
		अणु .bank = 0, .offset = EMC_MRW11, पूर्ण,
		अणु .bank = 1, .offset = EMC_MRW11, पूर्ण,
		अणु .bank = 0, .offset = EMC_MRW12, पूर्ण,
		अणु .bank = 1, .offset = EMC_MRW12, पूर्ण,
		अणु .bank = 0, .offset = EMC_MRW13, पूर्ण,
		अणु .bank = 1, .offset = EMC_MRW13, पूर्ण,
	पूर्ण,
	.trim_per_channel = अणु
		अणु .bank = 0, .offset = EMC_CMD_BRLSHFT_0, पूर्ण,
		अणु .bank = 1, .offset = EMC_CMD_BRLSHFT_1, पूर्ण,
		अणु .bank = 0, .offset = EMC_DATA_BRLSHFT_0, पूर्ण,
		अणु .bank = 1, .offset = EMC_DATA_BRLSHFT_0, पूर्ण,
		अणु .bank = 0, .offset = EMC_DATA_BRLSHFT_1, पूर्ण,
		अणु .bank = 1, .offset = EMC_DATA_BRLSHFT_1, पूर्ण,
		अणु .bank = 0, .offset = EMC_QUSE_BRLSHFT_0, पूर्ण,
		अणु .bank = 1, .offset = EMC_QUSE_BRLSHFT_1, पूर्ण,
		अणु .bank = 0, .offset = EMC_QUSE_BRLSHFT_2, पूर्ण,
		अणु .bank = 1, .offset = EMC_QUSE_BRLSHFT_3, पूर्ण,
	पूर्ण,
	.vref_per_channel = अणु
		अणु
			.bank = 0,
			.offset = EMC_TRAINING_OPT_DQS_IB_VREF_RANK0,
		पूर्ण, अणु
			.bank = 1,
			.offset = EMC_TRAINING_OPT_DQS_IB_VREF_RANK0,
		पूर्ण, अणु
			.bank = 0,
			.offset = EMC_TRAINING_OPT_DQS_IB_VREF_RANK1,
		पूर्ण, अणु
			.bank = 1,
			.offset = EMC_TRAINING_OPT_DQS_IB_VREF_RANK1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम tegra210_emc_train(काष्ठा समयr_list *समयr)
अणु
	काष्ठा tegra210_emc *emc = from_समयr(emc, समयr, training);
	अचिन्हित दीर्घ flags;

	अगर (!emc->last)
		वापस;

	spin_lock_irqsave(&emc->lock, flags);

	अगर (emc->sequence->periodic_compensation)
		emc->sequence->periodic_compensation(emc);

	spin_unlock_irqrestore(&emc->lock, flags);

	mod_समयr(&emc->training,
		  jअगरfies + msecs_to_jअगरfies(emc->training_पूर्णांकerval));
पूर्ण

अटल व्योम tegra210_emc_training_start(काष्ठा tegra210_emc *emc)
अणु
	mod_समयr(&emc->training,
		  jअगरfies + msecs_to_jअगरfies(emc->training_पूर्णांकerval));
पूर्ण

अटल व्योम tegra210_emc_training_stop(काष्ठा tegra210_emc *emc)
अणु
	del_समयr(&emc->training);
पूर्ण

अटल अचिन्हित पूर्णांक tegra210_emc_get_temperature(काष्ठा tegra210_emc *emc)
अणु
	अचिन्हित दीर्घ flags;
	u32 value, max = 0;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&emc->lock, flags);

	क्रम (i = 0; i < emc->num_devices; i++) अणु
		value = tegra210_emc_mrr_पढ़ो(emc, i, 4);

		अगर (value & BIT(7))
			dev_dbg(emc->dev,
				"sensor reading changed for device %u: %08x\n",
				i, value);

		value = FIELD_GET(LPDDR2_MR4_SRR, value);
		अगर (value > max)
			max = value;
	पूर्ण

	spin_unlock_irqrestore(&emc->lock, flags);

	वापस max;
पूर्ण

अटल व्योम tegra210_emc_poll_refresh(काष्ठा समयr_list *समयr)
अणु
	काष्ठा tegra210_emc *emc = from_समयr(emc, समयr, refresh_समयr);
	अचिन्हित पूर्णांक temperature;

	अगर (!emc->debugfs.temperature)
		temperature = tegra210_emc_get_temperature(emc);
	अन्यथा
		temperature = emc->debugfs.temperature;

	अगर (temperature == emc->temperature)
		जाओ reset;

	चयन (temperature) अणु
	हाल 0 ... 3:
		/* temperature is fine, using regular refresh */
		dev_dbg(emc->dev, "switching to nominal refresh...\n");
		tegra210_emc_set_refresh(emc, TEGRA210_EMC_REFRESH_NOMINAL);
		अवरोध;

	हाल 4:
		dev_dbg(emc->dev, "switching to 2x refresh...\n");
		tegra210_emc_set_refresh(emc, TEGRA210_EMC_REFRESH_2X);
		अवरोध;

	हाल 5:
		dev_dbg(emc->dev, "switching to 4x refresh...\n");
		tegra210_emc_set_refresh(emc, TEGRA210_EMC_REFRESH_4X);
		अवरोध;

	हाल 6 ... 7:
		dev_dbg(emc->dev, "switching to throttle refresh...\n");
		tegra210_emc_set_refresh(emc, TEGRA210_EMC_REFRESH_THROTTLE);
		अवरोध;

	शेष:
		WARN(1, "invalid DRAM temperature state %u\n", temperature);
		वापस;
	पूर्ण

	emc->temperature = temperature;

reset:
	अगर (atomic_पढ़ो(&emc->refresh_poll) > 0) अणु
		अचिन्हित पूर्णांक पूर्णांकerval = emc->refresh_poll_पूर्णांकerval;
		अचिन्हित पूर्णांक समयout = msecs_to_jअगरfies(पूर्णांकerval);

		mod_समयr(&emc->refresh_समयr, jअगरfies + समयout);
	पूर्ण
पूर्ण

अटल व्योम tegra210_emc_poll_refresh_stop(काष्ठा tegra210_emc *emc)
अणु
	atomic_set(&emc->refresh_poll, 0);
	del_समयr_sync(&emc->refresh_समयr);
पूर्ण

अटल व्योम tegra210_emc_poll_refresh_start(काष्ठा tegra210_emc *emc)
अणु
	atomic_set(&emc->refresh_poll, 1);

	mod_समयr(&emc->refresh_समयr,
		  jअगरfies + msecs_to_jअगरfies(emc->refresh_poll_पूर्णांकerval));
पूर्ण

अटल पूर्णांक tegra210_emc_cd_max_state(काष्ठा thermal_cooling_device *cd,
				     अचिन्हित दीर्घ *state)
अणु
	*state = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_emc_cd_get_state(काष्ठा thermal_cooling_device *cd,
				     अचिन्हित दीर्घ *state)
अणु
	काष्ठा tegra210_emc *emc = cd->devdata;

	*state = atomic_पढ़ो(&emc->refresh_poll);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_emc_cd_set_state(काष्ठा thermal_cooling_device *cd,
				     अचिन्हित दीर्घ state)
अणु
	काष्ठा tegra210_emc *emc = cd->devdata;

	अगर (state == atomic_पढ़ो(&emc->refresh_poll))
		वापस 0;

	अगर (state)
		tegra210_emc_poll_refresh_start(emc);
	अन्यथा
		tegra210_emc_poll_refresh_stop(emc);

	वापस 0;
पूर्ण

अटल काष्ठा thermal_cooling_device_ops tegra210_emc_cd_ops = अणु
	.get_max_state = tegra210_emc_cd_max_state,
	.get_cur_state = tegra210_emc_cd_get_state,
	.set_cur_state = tegra210_emc_cd_set_state,
पूर्ण;

अटल व्योम tegra210_emc_set_घड़ी(काष्ठा tegra210_emc *emc, u32 clksrc)
अणु
	emc->sequence->set_घड़ी(emc, clksrc);

	अगर (emc->next->periodic_training)
		tegra210_emc_training_start(emc);
	अन्यथा
		tegra210_emc_training_stop(emc);
पूर्ण

अटल व्योम tegra210_change_dll_src(काष्ठा tegra210_emc *emc,
				    u32 clksrc)
अणु
	u32 dll_setting = emc->next->dll_clk_src;
	u32 emc_clk_src;
	u32 emc_clk_भाग;

	emc_clk_src = (clksrc & EMC_CLK_EMC_2X_CLK_SRC_MASK) >>
		       EMC_CLK_EMC_2X_CLK_SRC_SHIFT;
	emc_clk_भाग = (clksrc & EMC_CLK_EMC_2X_CLK_DIVISOR_MASK) >>
		       EMC_CLK_EMC_2X_CLK_DIVISOR_SHIFT;

	dll_setting &= ~(DLL_CLK_EMC_DLL_CLK_SRC_MASK |
			 DLL_CLK_EMC_DLL_CLK_DIVISOR_MASK);
	dll_setting |= emc_clk_src << DLL_CLK_EMC_DLL_CLK_SRC_SHIFT;
	dll_setting |= emc_clk_भाग << DLL_CLK_EMC_DLL_CLK_DIVISOR_SHIFT;

	dll_setting &= ~DLL_CLK_EMC_DLL_DDLL_CLK_SEL_MASK;
	अगर (emc_clk_src == EMC_CLK_SOURCE_PLLMB_LJ)
		dll_setting |= (PLLM_VCOB <<
				DLL_CLK_EMC_DLL_DDLL_CLK_SEL_SHIFT);
	अन्यथा अगर (emc_clk_src == EMC_CLK_SOURCE_PLLM_LJ)
		dll_setting |= (PLLM_VCOA <<
				DLL_CLK_EMC_DLL_DDLL_CLK_SEL_SHIFT);
	अन्यथा
		dll_setting |= (EMC_DLL_SWITCH_OUT <<
				DLL_CLK_EMC_DLL_DDLL_CLK_SEL_SHIFT);

	tegra210_clk_emc_dll_update_setting(dll_setting);

	अगर (emc->next->clk_out_enb_x_0_clk_enb_emc_dll)
		tegra210_clk_emc_dll_enable(true);
	अन्यथा
		tegra210_clk_emc_dll_enable(false);
पूर्ण

पूर्णांक tegra210_emc_set_refresh(काष्ठा tegra210_emc *emc,
			     क्रमागत tegra210_emc_refresh refresh)
अणु
	काष्ठा tegra210_emc_timing *timings;
	अचिन्हित दीर्घ flags;

	अगर ((emc->dram_type != DRAM_TYPE_LPDDR2 &&
	     emc->dram_type != DRAM_TYPE_LPDDR4) ||
	    !emc->last)
		वापस -ENODEV;

	अगर (refresh > TEGRA210_EMC_REFRESH_THROTTLE)
		वापस -EINVAL;

	अगर (refresh == emc->refresh)
		वापस 0;

	spin_lock_irqsave(&emc->lock, flags);

	अगर (refresh == TEGRA210_EMC_REFRESH_THROTTLE && emc->derated)
		timings = emc->derated;
	अन्यथा
		timings = emc->nominal;

	अगर (timings != emc->timings) अणु
		अचिन्हित पूर्णांक index = emc->last - emc->timings;
		u32 clksrc;

		clksrc = emc->provider.configs[index].value |
			 EMC_CLK_FORCE_CC_TRIGGER;

		emc->next = &timings[index];
		emc->timings = timings;

		tegra210_emc_set_घड़ी(emc, clksrc);
	पूर्ण अन्यथा अणु
		tegra210_emc_adjust_timing(emc, emc->last);
		tegra210_emc_timing_update(emc);

		अगर (refresh != TEGRA210_EMC_REFRESH_NOMINAL)
			emc_ग_लिखोl(emc, EMC_REF_REF_CMD, EMC_REF);
	पूर्ण

	spin_unlock_irqrestore(&emc->lock, flags);

	वापस 0;
पूर्ण

u32 tegra210_emc_mrr_पढ़ो(काष्ठा tegra210_emc *emc, अचिन्हित पूर्णांक chip,
			  अचिन्हित पूर्णांक address)
अणु
	u32 value, ret = 0;
	अचिन्हित पूर्णांक i;

	value = (chip & EMC_MRR_DEV_SEL_MASK) << EMC_MRR_DEV_SEL_SHIFT |
		(address & EMC_MRR_MA_MASK) << EMC_MRR_MA_SHIFT;
	emc_ग_लिखोl(emc, value, EMC_MRR);

	क्रम (i = 0; i < emc->num_channels; i++)
		WARN(tegra210_emc_रुको_क्रम_update(emc, i, EMC_EMC_STATUS,
						  EMC_EMC_STATUS_MRR_DIVLD, 1),
		     "Timed out waiting for MRR %u (ch=%u)\n", address, i);

	क्रम (i = 0; i < emc->num_channels; i++) अणु
		value = emc_channel_पढ़ोl(emc, i, EMC_MRR);
		value &= EMC_MRR_DATA_MASK;

		ret = (ret << 16) | value;
	पूर्ण

	वापस ret;
पूर्ण

व्योम tegra210_emc_करो_घड़ी_change(काष्ठा tegra210_emc *emc, u32 clksrc)
अणु
	पूर्णांक err;

	mc_पढ़ोl(emc->mc, MC_EMEM_ADR_CFG);
	emc_पढ़ोl(emc, EMC_INTSTATUS);

	tegra210_clk_emc_update_setting(clksrc);

	err = tegra210_emc_रुको_क्रम_update(emc, 0, EMC_INTSTATUS,
					   EMC_INTSTATUS_CLKCHANGE_COMPLETE,
					   true);
	अगर (err)
		dev_warn(emc->dev, "clock change completion error: %d\n", err);
पूर्ण

काष्ठा tegra210_emc_timing *tegra210_emc_find_timing(काष्ठा tegra210_emc *emc,
						     अचिन्हित दीर्घ rate)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < emc->num_timings; i++)
		अगर (emc->timings[i].rate * 1000UL == rate)
			वापस &emc->timings[i];

	वापस शून्य;
पूर्ण

पूर्णांक tegra210_emc_रुको_क्रम_update(काष्ठा tegra210_emc *emc, अचिन्हित पूर्णांक channel,
				 अचिन्हित पूर्णांक offset, u32 bit_mask, bool state)
अणु
	अचिन्हित पूर्णांक i;
	u32 value;

	क्रम (i = 0; i < EMC_STATUS_UPDATE_TIMEOUT; i++) अणु
		value = emc_channel_पढ़ोl(emc, channel, offset);
		अगर (!!(value & bit_mask) == state)
			वापस 0;

		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

व्योम tegra210_emc_set_shaकरोw_bypass(काष्ठा tegra210_emc *emc, पूर्णांक set)
अणु
	u32 emc_dbg = emc_पढ़ोl(emc, EMC_DBG);

	अगर (set)
		emc_ग_लिखोl(emc, emc_dbg | EMC_DBG_WRITE_MUX_ACTIVE, EMC_DBG);
	अन्यथा
		emc_ग_लिखोl(emc, emc_dbg & ~EMC_DBG_WRITE_MUX_ACTIVE, EMC_DBG);
पूर्ण

u32 tegra210_emc_get_dll_state(काष्ठा tegra210_emc_timing *next)
अणु
	अगर (next->emc_emrs & 0x1)
		वापस 0;

	वापस 1;
पूर्ण

व्योम tegra210_emc_timing_update(काष्ठा tegra210_emc *emc)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	emc_ग_लिखोl(emc, 0x1, EMC_TIMING_CONTROL);

	क्रम (i = 0; i < emc->num_channels; i++) अणु
		err |= tegra210_emc_रुको_क्रम_update(emc, i, EMC_EMC_STATUS,
						    EMC_EMC_STATUS_TIMING_UPDATE_STALLED,
						    false);
	पूर्ण

	अगर (err)
		dev_warn(emc->dev, "timing update error: %d\n", err);
पूर्ण

अचिन्हित दीर्घ tegra210_emc_actual_osc_घड़ीs(u32 in)
अणु
	अगर (in < 0x40)
		वापस in * 16;
	अन्यथा अगर (in < 0x80)
		वापस 2048;
	अन्यथा अगर (in < 0xc0)
		वापस 4096;
	अन्यथा
		वापस 8192;
पूर्ण

व्योम tegra210_emc_start_periodic_compensation(काष्ठा tegra210_emc *emc)
अणु
	u32 mpc_req = 0x4b;

	emc_ग_लिखोl(emc, mpc_req, EMC_MPC);
	mpc_req = emc_पढ़ोl(emc, EMC_MPC);
पूर्ण

u32 tegra210_emc_compensate(काष्ठा tegra210_emc_timing *next, u32 offset)
अणु
	u32 temp = 0, rate = next->rate / 1000;
	s32 delta[4], delta_taps[4];
	s32 new[] = अणु
		TRIM_REG(0, 0, 0, 0),
		TRIM_REG(0, 0, 0, 1),
		TRIM_REG(0, 0, 1, 2),
		TRIM_REG(0, 0, 1, 3),

		TRIM_REG(1, 0, 2, 4),
		TRIM_REG(1, 0, 2, 5),
		TRIM_REG(1, 0, 3, 6),
		TRIM_REG(1, 0, 3, 7),

		TRIM_REG(0, 1, 0, 0),
		TRIM_REG(0, 1, 0, 1),
		TRIM_REG(0, 1, 1, 2),
		TRIM_REG(0, 1, 1, 3),

		TRIM_REG(1, 1, 2, 4),
		TRIM_REG(1, 1, 2, 5),
		TRIM_REG(1, 1, 3, 6),
		TRIM_REG(1, 1, 3, 7)
	पूर्ण;
	अचिन्हित i;

	चयन (offset) अणु
	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_0:
	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_1:
	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_2:
	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_3:
	हाल EMC_DATA_BRLSHFT_0:
		delta[0] = 128 * (next->current_dram_clktree[C0D0U0] -
				  next->trained_dram_clktree[C0D0U0]);
		delta[1] = 128 * (next->current_dram_clktree[C0D0U1] -
				  next->trained_dram_clktree[C0D0U1]);
		delta[2] = 128 * (next->current_dram_clktree[C1D0U0] -
				  next->trained_dram_clktree[C1D0U0]);
		delta[3] = 128 * (next->current_dram_clktree[C1D0U1] -
				  next->trained_dram_clktree[C1D0U1]);

		delta_taps[0] = (delta[0] * (s32)rate) / 1000000;
		delta_taps[1] = (delta[1] * (s32)rate) / 1000000;
		delta_taps[2] = (delta[2] * (s32)rate) / 1000000;
		delta_taps[3] = (delta[3] * (s32)rate) / 1000000;

		क्रम (i = 0; i < 4; i++) अणु
			अगर ((delta_taps[i] > next->tree_margin) ||
			    (delta_taps[i] < (-1 * next->tree_margin))) अणु
				new[i * 2] = new[i * 2] + delta_taps[i];
				new[i * 2 + 1] = new[i * 2 + 1] +
							delta_taps[i];
			पूर्ण
		पूर्ण

		अगर (offset == EMC_DATA_BRLSHFT_0) अणु
			क्रम (i = 0; i < 8; i++)
				new[i] = new[i] / 64;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < 8; i++)
				new[i] = new[i] % 64;
		पूर्ण

		अवरोध;

	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_0:
	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_1:
	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_2:
	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_3:
	हाल EMC_DATA_BRLSHFT_1:
		delta[0] = 128 * (next->current_dram_clktree[C0D1U0] -
				  next->trained_dram_clktree[C0D1U0]);
		delta[1] = 128 * (next->current_dram_clktree[C0D1U1] -
				  next->trained_dram_clktree[C0D1U1]);
		delta[2] = 128 * (next->current_dram_clktree[C1D1U0] -
				  next->trained_dram_clktree[C1D1U0]);
		delta[3] = 128 * (next->current_dram_clktree[C1D1U1] -
				  next->trained_dram_clktree[C1D1U1]);

		delta_taps[0] = (delta[0] * (s32)rate) / 1000000;
		delta_taps[1] = (delta[1] * (s32)rate) / 1000000;
		delta_taps[2] = (delta[2] * (s32)rate) / 1000000;
		delta_taps[3] = (delta[3] * (s32)rate) / 1000000;

		क्रम (i = 0; i < 4; i++) अणु
			अगर ((delta_taps[i] > next->tree_margin) ||
			    (delta_taps[i] < (-1 * next->tree_margin))) अणु
				new[8 + i * 2] = new[8 + i * 2] +
							delta_taps[i];
				new[8 + i * 2 + 1] = new[8 + i * 2 + 1] +
							delta_taps[i];
			पूर्ण
		पूर्ण

		अगर (offset == EMC_DATA_BRLSHFT_1) अणु
			क्रम (i = 0; i < 8; i++)
				new[i + 8] = new[i + 8] / 64;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < 8; i++)
				new[i + 8] = new[i + 8] % 64;
		पूर्ण

		अवरोध;
	पूर्ण

	चयन (offset) अणु
	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_0:
		temp = CALC_TEMP(0, 0, 0, 1, 0);
		अवरोध;

	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_1:
		temp = CALC_TEMP(0, 1, 2, 3, 2);
		अवरोध;

	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_2:
		temp = CALC_TEMP(0, 2, 4, 5, 4);
		अवरोध;

	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_3:
		temp = CALC_TEMP(0, 3, 6, 7, 6);
		अवरोध;

	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_0:
		temp = CALC_TEMP(1, 0, 0, 1, 8);
		अवरोध;

	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_1:
		temp = CALC_TEMP(1, 1, 2, 3, 10);
		अवरोध;

	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_2:
		temp = CALC_TEMP(1, 2, 4, 5, 12);
		अवरोध;

	हाल EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_3:
		temp = CALC_TEMP(1, 3, 6, 7, 14);
		अवरोध;

	हाल EMC_DATA_BRLSHFT_0:
		temp = ((new[0] <<
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE0_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE0_DATA_BRLSHFT_MASK) |
		       ((new[1] <<
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE1_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE1_DATA_BRLSHFT_MASK) |
		       ((new[2] <<
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE2_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE2_DATA_BRLSHFT_MASK) |
		       ((new[3] <<
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE3_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE3_DATA_BRLSHFT_MASK) |
		       ((new[4] <<
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE4_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE4_DATA_BRLSHFT_MASK) |
		       ((new[5] <<
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE5_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE5_DATA_BRLSHFT_MASK) |
		       ((new[6] <<
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE6_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE6_DATA_BRLSHFT_MASK) |
		       ((new[7] <<
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE7_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_0_RANK0_BYTE7_DATA_BRLSHFT_MASK);
		अवरोध;

	हाल EMC_DATA_BRLSHFT_1:
		temp = ((new[8] <<
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE0_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE0_DATA_BRLSHFT_MASK) |
		       ((new[9] <<
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE1_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE1_DATA_BRLSHFT_MASK) |
		       ((new[10] <<
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE2_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE2_DATA_BRLSHFT_MASK) |
		       ((new[11] <<
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE3_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE3_DATA_BRLSHFT_MASK) |
		       ((new[12] <<
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE4_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE4_DATA_BRLSHFT_MASK) |
		       ((new[13] <<
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE5_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE5_DATA_BRLSHFT_MASK) |
		       ((new[14] <<
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE6_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE6_DATA_BRLSHFT_MASK) |
		       ((new[15] <<
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE7_DATA_BRLSHFT_SHIFT) &
			 EMC_DATA_BRLSHFT_1_RANK1_BYTE7_DATA_BRLSHFT_MASK);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस temp;
पूर्ण

u32 tegra210_emc_dll_prelock(काष्ठा tegra210_emc *emc, u32 clksrc)
अणु
	अचिन्हित पूर्णांक i;
	u32 value;

	value = emc_पढ़ोl(emc, EMC_CFG_DIG_DLL);
	value &= ~EMC_CFG_DIG_DLL_CFG_DLL_LOCK_LIMIT_MASK;
	value |= (3 << EMC_CFG_DIG_DLL_CFG_DLL_LOCK_LIMIT_SHIFT);
	value &= ~EMC_CFG_DIG_DLL_CFG_DLL_EN;
	value &= ~EMC_CFG_DIG_DLL_CFG_DLL_MODE_MASK;
	value |= (3 << EMC_CFG_DIG_DLL_CFG_DLL_MODE_SHIFT);
	value |= EMC_CFG_DIG_DLL_CFG_DLL_STALL_ALL_TRAFFIC;
	value &= ~EMC_CFG_DIG_DLL_CFG_DLL_STALL_RW_UNTIL_LOCK;
	value &= ~EMC_CFG_DIG_DLL_CFG_DLL_STALL_ALL_UNTIL_LOCK;
	emc_ग_लिखोl(emc, value, EMC_CFG_DIG_DLL);
	emc_ग_लिखोl(emc, 1, EMC_TIMING_CONTROL);

	क्रम (i = 0; i < emc->num_channels; i++)
		tegra210_emc_रुको_क्रम_update(emc, i, EMC_EMC_STATUS,
					     EMC_EMC_STATUS_TIMING_UPDATE_STALLED,
					     0);

	क्रम (i = 0; i < emc->num_channels; i++) अणु
		जबतक (true) अणु
			value = emc_channel_पढ़ोl(emc, i, EMC_CFG_DIG_DLL);
			अगर ((value & EMC_CFG_DIG_DLL_CFG_DLL_EN) == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	value = emc->next->burst_regs[EMC_DLL_CFG_0_INDEX];
	emc_ग_लिखोl(emc, value, EMC_DLL_CFG_0);

	value = emc_पढ़ोl(emc, EMC_DLL_CFG_1);
	value &= EMC_DLL_CFG_1_DDLLCAL_CTRL_START_TRIM_MASK;

	अगर (emc->next->rate >= 400000 && emc->next->rate < 600000)
		value |= 150;
	अन्यथा अगर (emc->next->rate >= 600000 && emc->next->rate < 800000)
		value |= 100;
	अन्यथा अगर (emc->next->rate >= 800000 && emc->next->rate < 1000000)
		value |= 70;
	अन्यथा अगर (emc->next->rate >= 1000000 && emc->next->rate < 1200000)
		value |= 30;
	अन्यथा
		value |= 20;

	emc_ग_लिखोl(emc, value, EMC_DLL_CFG_1);

	tegra210_change_dll_src(emc, clksrc);

	value = emc_पढ़ोl(emc, EMC_CFG_DIG_DLL);
	value |= EMC_CFG_DIG_DLL_CFG_DLL_EN;
	emc_ग_लिखोl(emc, value, EMC_CFG_DIG_DLL);

	tegra210_emc_timing_update(emc);

	क्रम (i = 0; i < emc->num_channels; i++) अणु
		जबतक (true) अणु
			value = emc_channel_पढ़ोl(emc, 0, EMC_CFG_DIG_DLL);
			अगर (value & EMC_CFG_DIG_DLL_CFG_DLL_EN)
				अवरोध;
		पूर्ण
	पूर्ण

	जबतक (true) अणु
		value = emc_पढ़ोl(emc, EMC_DIG_DLL_STATUS);

		अगर ((value & EMC_DIG_DLL_STATUS_DLL_PRIV_UPDATED) == 0)
			जारी;

		अगर ((value & EMC_DIG_DLL_STATUS_DLL_LOCK) == 0)
			जारी;

		अवरोध;
	पूर्ण

	value = emc_पढ़ोl(emc, EMC_DIG_DLL_STATUS);

	वापस value & EMC_DIG_DLL_STATUS_DLL_OUT_MASK;
पूर्ण

u32 tegra210_emc_dvfs_घातer_ramp_up(काष्ठा tegra210_emc *emc, u32 clk,
				    bool flip_backward)
अणु
	u32 cmd_pad, dq_pad, rfu1, cfg5, common_tx, ramp_up_रुको = 0;
	स्थिर काष्ठा tegra210_emc_timing *timing;

	अगर (flip_backward)
		timing = emc->last;
	अन्यथा
		timing = emc->next;

	cmd_pad = timing->burst_regs[EMC_PMACRO_CMD_PAD_TX_CTRL_INDEX];
	dq_pad = timing->burst_regs[EMC_PMACRO_DATA_PAD_TX_CTRL_INDEX];
	rfu1 = timing->burst_regs[EMC_PMACRO_BRICK_CTRL_RFU1_INDEX];
	cfg5 = timing->burst_regs[EMC_FBIO_CFG5_INDEX];
	common_tx = timing->burst_regs[EMC_PMACRO_COMMON_PAD_TX_CTRL_INDEX];

	cmd_pad |= EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQ_TX_DRVFORCEON;

	अगर (clk < 1000000 / DVFS_FGCG_MID_SPEED_THRESHOLD) अणु
		ccfअगरo_ग_लिखोl(emc, common_tx & 0xa,
			      EMC_PMACRO_COMMON_PAD_TX_CTRL, 0);
		ccfअगरo_ग_लिखोl(emc, common_tx & 0xf,
			      EMC_PMACRO_COMMON_PAD_TX_CTRL,
			      (100000 / clk) + 1);
		ramp_up_रुको += 100000;
	पूर्ण अन्यथा अणु
		ccfअगरo_ग_लिखोl(emc, common_tx | 0x8,
			      EMC_PMACRO_COMMON_PAD_TX_CTRL, 0);
	पूर्ण

	अगर (clk < 1000000 / DVFS_FGCG_HIGH_SPEED_THRESHOLD) अणु
		अगर (clk < 1000000 / IOBRICK_DCC_THRESHOLD) अणु
			cmd_pad |=
				EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQSP_TX_E_DCC |
				EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQSN_TX_E_DCC;
			cmd_pad &=
				~(EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQ_TX_E_DCC |
				  EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_CMD_TX_E_DCC);
			ccfअगरo_ग_लिखोl(emc, cmd_pad,
				      EMC_PMACRO_CMD_PAD_TX_CTRL,
				      (100000 / clk) + 1);
			ramp_up_रुको += 100000;

			dq_pad |=
				EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQSP_TX_E_DCC |
				EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQSN_TX_E_DCC;
			dq_pad &=
			       ~(EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQ_TX_E_DCC |
				 EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_CMD_TX_E_DCC);
			ccfअगरo_ग_लिखोl(emc, dq_pad,
				      EMC_PMACRO_DATA_PAD_TX_CTRL, 0);
			ccfअगरo_ग_लिखोl(emc, rfu1 & 0xfe40fe40,
				      EMC_PMACRO_BRICK_CTRL_RFU1, 0);
		पूर्ण अन्यथा अणु
			ccfअगरo_ग_लिखोl(emc, rfu1 & 0xfe40fe40,
				      EMC_PMACRO_BRICK_CTRL_RFU1,
				      (100000 / clk) + 1);
			ramp_up_रुको += 100000;
		पूर्ण

		ccfअगरo_ग_लिखोl(emc, rfu1 & 0xfeedfeed,
			      EMC_PMACRO_BRICK_CTRL_RFU1, (100000 / clk) + 1);
		ramp_up_रुको += 100000;

		अगर (clk < 1000000 / IOBRICK_DCC_THRESHOLD) अणु
			cmd_pad |=
				EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQSP_TX_E_DCC |
				EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQSN_TX_E_DCC |
				EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQ_TX_E_DCC |
				EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_CMD_TX_E_DCC;
			ccfअगरo_ग_लिखोl(emc, cmd_pad,
				      EMC_PMACRO_CMD_PAD_TX_CTRL,
				      (100000 / clk) + 1);
			ramp_up_रुको += 100000;

			dq_pad |=
				EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQSP_TX_E_DCC |
				EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQSN_TX_E_DCC |
				EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQ_TX_E_DCC |
				EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_CMD_TX_E_DCC;
			ccfअगरo_ग_लिखोl(emc, dq_pad,
				      EMC_PMACRO_DATA_PAD_TX_CTRL, 0);
			ccfअगरo_ग_लिखोl(emc, rfu1,
				      EMC_PMACRO_BRICK_CTRL_RFU1, 0);
		पूर्ण अन्यथा अणु
			ccfअगरo_ग_लिखोl(emc, rfu1,
				      EMC_PMACRO_BRICK_CTRL_RFU1,
				      (100000 / clk) + 1);
			ramp_up_रुको += 100000;
		पूर्ण

		ccfअगरo_ग_लिखोl(emc, cfg5 & ~EMC_FBIO_CFG5_CMD_TX_DIS,
			      EMC_FBIO_CFG5, (100000 / clk) + 10);
		ramp_up_रुको += 100000 + (10 * clk);
	पूर्ण अन्यथा अगर (clk < 1000000 / DVFS_FGCG_MID_SPEED_THRESHOLD) अणु
		ccfअगरo_ग_लिखोl(emc, rfu1 | 0x06000600,
			      EMC_PMACRO_BRICK_CTRL_RFU1, (100000 / clk) + 1);
		ccfअगरo_ग_लिखोl(emc, cfg5 & ~EMC_FBIO_CFG5_CMD_TX_DIS,
			      EMC_FBIO_CFG5, (100000 / clk) + 10);
		ramp_up_रुको += 100000 + 10 * clk;
	पूर्ण अन्यथा अणु
		ccfअगरo_ग_लिखोl(emc, rfu1 | 0x00000600,
			      EMC_PMACRO_BRICK_CTRL_RFU1, 0);
		ccfअगरo_ग_लिखोl(emc, cfg5 & ~EMC_FBIO_CFG5_CMD_TX_DIS,
			      EMC_FBIO_CFG5, 12);
		ramp_up_रुको += 12 * clk;
	पूर्ण

	cmd_pad &= ~EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQ_TX_DRVFORCEON;
	ccfअगरo_ग_लिखोl(emc, cmd_pad, EMC_PMACRO_CMD_PAD_TX_CTRL, 5);

	वापस ramp_up_रुको;
पूर्ण

u32 tegra210_emc_dvfs_घातer_ramp_करोwn(काष्ठा tegra210_emc *emc, u32 clk,
				      bool flip_backward)
अणु
	u32 ramp_करोwn_रुको = 0, cmd_pad, dq_pad, rfu1, cfg5, common_tx;
	स्थिर काष्ठा tegra210_emc_timing *entry;
	u32 seq_रुको;

	अगर (flip_backward)
		entry = emc->next;
	अन्यथा
		entry = emc->last;

	cmd_pad = entry->burst_regs[EMC_PMACRO_CMD_PAD_TX_CTRL_INDEX];
	dq_pad = entry->burst_regs[EMC_PMACRO_DATA_PAD_TX_CTRL_INDEX];
	rfu1 = entry->burst_regs[EMC_PMACRO_BRICK_CTRL_RFU1_INDEX];
	cfg5 = entry->burst_regs[EMC_FBIO_CFG5_INDEX];
	common_tx = entry->burst_regs[EMC_PMACRO_COMMON_PAD_TX_CTRL_INDEX];

	cmd_pad |= EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQ_TX_DRVFORCEON;

	ccfअगरo_ग_लिखोl(emc, cmd_pad, EMC_PMACRO_CMD_PAD_TX_CTRL, 0);
	ccfअगरo_ग_लिखोl(emc, cfg5 | EMC_FBIO_CFG5_CMD_TX_DIS,
		      EMC_FBIO_CFG5, 12);
	ramp_करोwn_रुको = 12 * clk;

	seq_रुको = (100000 / clk) + 1;

	अगर (clk < (1000000 / DVFS_FGCG_HIGH_SPEED_THRESHOLD)) अणु
		अगर (clk < (1000000 / IOBRICK_DCC_THRESHOLD)) अणु
			cmd_pad &=
				~(EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQ_TX_E_DCC |
				  EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_CMD_TX_E_DCC);
			cmd_pad |=
				EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQSP_TX_E_DCC |
				EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQSN_TX_E_DCC;
			ccfअगरo_ग_लिखोl(emc, cmd_pad,
				      EMC_PMACRO_CMD_PAD_TX_CTRL, seq_रुको);
			ramp_करोwn_रुको += 100000;

			dq_pad &=
			      ~(EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQ_TX_E_DCC |
				EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_CMD_TX_E_DCC);
			dq_pad |=
				EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQSP_TX_E_DCC |
				EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQSN_TX_E_DCC;
			ccfअगरo_ग_लिखोl(emc, dq_pad,
				      EMC_PMACRO_DATA_PAD_TX_CTRL, 0);
			ccfअगरo_ग_लिखोl(emc, rfu1 & ~0x01120112,
				      EMC_PMACRO_BRICK_CTRL_RFU1, 0);
		पूर्ण अन्यथा अणु
			ccfअगरo_ग_लिखोl(emc, rfu1 & ~0x01120112,
				      EMC_PMACRO_BRICK_CTRL_RFU1, seq_रुको);
			ramp_करोwn_रुको += 100000;
		पूर्ण

		ccfअगरo_ग_लिखोl(emc, rfu1 & ~0x01bf01bf,
			      EMC_PMACRO_BRICK_CTRL_RFU1, seq_रुको);
		ramp_करोwn_रुको += 100000;

		अगर (clk < (1000000 / IOBRICK_DCC_THRESHOLD)) अणु
			cmd_pad &=
				~(EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQ_TX_E_DCC |
				  EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_CMD_TX_E_DCC |
				  EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQSP_TX_E_DCC |
				  EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQSN_TX_E_DCC);
			ccfअगरo_ग_लिखोl(emc, cmd_pad,
				      EMC_PMACRO_CMD_PAD_TX_CTRL, seq_रुको);
			ramp_करोwn_रुको += 100000;

			dq_pad &=
			      ~(EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQ_TX_E_DCC |
				EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_CMD_TX_E_DCC |
				EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQSP_TX_E_DCC |
				EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQSN_TX_E_DCC);
			ccfअगरo_ग_लिखोl(emc, dq_pad,
				      EMC_PMACRO_DATA_PAD_TX_CTRL, 0);
			ccfअगरo_ग_लिखोl(emc, rfu1 & ~0x07ff07ff,
				      EMC_PMACRO_BRICK_CTRL_RFU1, 0);
		पूर्ण अन्यथा अणु
			ccfअगरo_ग_लिखोl(emc, rfu1 & ~0x07ff07ff,
				      EMC_PMACRO_BRICK_CTRL_RFU1, seq_रुको);
			ramp_करोwn_रुको += 100000;
		पूर्ण
	पूर्ण अन्यथा अणु
		ccfअगरo_ग_लिखोl(emc, rfu1 & ~0xffff07ff,
			      EMC_PMACRO_BRICK_CTRL_RFU1, seq_रुको + 19);
		ramp_करोwn_रुको += 100000 + (20 * clk);
	पूर्ण

	अगर (clk < (1000000 / DVFS_FGCG_MID_SPEED_THRESHOLD)) अणु
		ramp_करोwn_रुको += 100000;
		ccfअगरo_ग_लिखोl(emc, common_tx & ~0x5,
			      EMC_PMACRO_COMMON_PAD_TX_CTRL, seq_रुको);
		ramp_करोwn_रुको += 100000;
		ccfअगरo_ग_लिखोl(emc, common_tx & ~0xf,
			      EMC_PMACRO_COMMON_PAD_TX_CTRL, seq_रुको);
		ramp_करोwn_रुको += 100000;
		ccfअगरo_ग_लिखोl(emc, 0, 0, seq_रुको);
		ramp_करोwn_रुको += 100000;
	पूर्ण अन्यथा अणु
		ccfअगरo_ग_लिखोl(emc, common_tx & ~0xf,
			      EMC_PMACRO_COMMON_PAD_TX_CTRL, seq_रुको);
	पूर्ण

	वापस ramp_करोwn_रुको;
पूर्ण

व्योम tegra210_emc_reset_dram_clktree_values(काष्ठा tegra210_emc_timing *timing)
अणु
	timing->current_dram_clktree[C0D0U0] =
		timing->trained_dram_clktree[C0D0U0];
	timing->current_dram_clktree[C0D0U1] =
		timing->trained_dram_clktree[C0D0U1];
	timing->current_dram_clktree[C1D0U0] =
		timing->trained_dram_clktree[C1D0U0];
	timing->current_dram_clktree[C1D0U1] =
		timing->trained_dram_clktree[C1D0U1];
	timing->current_dram_clktree[C1D1U0] =
		timing->trained_dram_clktree[C1D1U0];
	timing->current_dram_clktree[C1D1U1] =
		timing->trained_dram_clktree[C1D1U1];
पूर्ण

अटल व्योम update_dll_control(काष्ठा tegra210_emc *emc, u32 value, bool state)
अणु
	अचिन्हित पूर्णांक i;

	emc_ग_लिखोl(emc, value, EMC_CFG_DIG_DLL);
	tegra210_emc_timing_update(emc);

	क्रम (i = 0; i < emc->num_channels; i++)
		tegra210_emc_रुको_क्रम_update(emc, i, EMC_CFG_DIG_DLL,
					     EMC_CFG_DIG_DLL_CFG_DLL_EN,
					     state);
पूर्ण

व्योम tegra210_emc_dll_disable(काष्ठा tegra210_emc *emc)
अणु
	u32 value;

	value = emc_पढ़ोl(emc, EMC_CFG_DIG_DLL);
	value &= ~EMC_CFG_DIG_DLL_CFG_DLL_EN;

	update_dll_control(emc, value, false);
पूर्ण

व्योम tegra210_emc_dll_enable(काष्ठा tegra210_emc *emc)
अणु
	u32 value;

	value = emc_पढ़ोl(emc, EMC_CFG_DIG_DLL);
	value |= EMC_CFG_DIG_DLL_CFG_DLL_EN;

	update_dll_control(emc, value, true);
पूर्ण

व्योम tegra210_emc_adjust_timing(काष्ठा tegra210_emc *emc,
				काष्ठा tegra210_emc_timing *timing)
अणु
	u32 dsr_cntrl = timing->burst_regs[EMC_DYN_SELF_REF_CONTROL_INDEX];
	u32 pre_ref = timing->burst_regs[EMC_PRE_REFRESH_REQ_CNT_INDEX];
	u32 ref = timing->burst_regs[EMC_REFRESH_INDEX];

	चयन (emc->refresh) अणु
	हाल TEGRA210_EMC_REFRESH_NOMINAL:
	हाल TEGRA210_EMC_REFRESH_THROTTLE:
		अवरोध;

	हाल TEGRA210_EMC_REFRESH_2X:
		ref = REFRESH_SPEEDUP(ref, 2);
		pre_ref = REFRESH_SPEEDUP(pre_ref, 2);
		dsr_cntrl = REFRESH_SPEEDUP(dsr_cntrl, 2);
		अवरोध;

	हाल TEGRA210_EMC_REFRESH_4X:
		ref = REFRESH_SPEEDUP(ref, 4);
		pre_ref = REFRESH_SPEEDUP(pre_ref, 4);
		dsr_cntrl = REFRESH_SPEEDUP(dsr_cntrl, 4);
		अवरोध;

	शेष:
		dev_warn(emc->dev, "failed to set refresh: %d\n", emc->refresh);
		वापस;
	पूर्ण

	emc_ग_लिखोl(emc, ref, emc->offsets->burst[EMC_REFRESH_INDEX]);
	emc_ग_लिखोl(emc, pre_ref,
		   emc->offsets->burst[EMC_PRE_REFRESH_REQ_CNT_INDEX]);
	emc_ग_लिखोl(emc, dsr_cntrl,
		   emc->offsets->burst[EMC_DYN_SELF_REF_CONTROL_INDEX]);
पूर्ण

अटल पूर्णांक tegra210_emc_set_rate(काष्ठा device *dev,
				 स्थिर काष्ठा tegra210_clk_emc_config *config)
अणु
	काष्ठा tegra210_emc *emc = dev_get_drvdata(dev);
	काष्ठा tegra210_emc_timing *timing = शून्य;
	अचिन्हित दीर्घ rate = config->rate;
	s64 last_change_delay;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	अगर (rate == emc->last->rate * 1000UL)
		वापस 0;

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		अगर (emc->timings[i].rate * 1000UL == rate) अणु
			timing = &emc->timings[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!timing)
		वापस -EINVAL;

	अगर (rate > 204000000 && !timing->trained)
		वापस -EINVAL;

	emc->next = timing;
	last_change_delay = kसमय_us_delta(kसमय_get(), emc->clkchange_समय);

	/* XXX use non-busy-looping sleep? */
	अगर ((last_change_delay >= 0) &&
	    (last_change_delay < emc->clkchange_delay))
		udelay(emc->clkchange_delay - (पूर्णांक)last_change_delay);

	spin_lock_irqsave(&emc->lock, flags);
	tegra210_emc_set_घड़ी(emc, config->value);
	emc->clkchange_समय = kसमय_get();
	emc->last = timing;
	spin_unlock_irqrestore(&emc->lock, flags);

	वापस 0;
पूर्ण

/*
 * debugfs पूर्णांकerface
 *
 * The memory controller driver exposes some files in debugfs that can be used
 * to control the EMC frequency. The top-level directory can be found here:
 *
 *   /sys/kernel/debug/emc
 *
 * It contains the following files:
 *
 *   - available_rates: This file contains a list of valid, space-separated
 *     EMC frequencies.
 *
 *   - min_rate: Writing a value to this file sets the given frequency as the
 *       न्यूनमान of the permitted range. If this is higher than the currently
 *       configured EMC frequency, this will cause the frequency to be
 *       increased so that it stays within the valid range.
 *
 *   - max_rate: Similarily to the min_rate file, writing a value to this file
 *       sets the given frequency as the उच्चमानing of the permitted range. If
 *       the value is lower than the currently configured EMC frequency, this
 *       will cause the frequency to be decreased so that it stays within the
 *       valid range.
 */

अटल bool tegra210_emc_validate_rate(काष्ठा tegra210_emc *emc,
				       अचिन्हित दीर्घ rate)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < emc->num_timings; i++)
		अगर (rate == emc->timings[i].rate * 1000UL)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक tegra210_emc_debug_available_rates_show(काष्ठा seq_file *s,
						   व्योम *data)
अणु
	काष्ठा tegra210_emc *emc = s->निजी;
	स्थिर अक्षर *prefix = "";
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		seq_म_लिखो(s, "%s%u", prefix, emc->timings[i].rate * 1000);
		prefix = " ";
	पूर्ण

	seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_emc_debug_available_rates_खोलो(काष्ठा inode *inode,
						   काष्ठा file *file)
अणु
	वापस single_खोलो(file, tegra210_emc_debug_available_rates_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations tegra210_emc_debug_available_rates_fops = अणु
	.खोलो = tegra210_emc_debug_available_rates_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल पूर्णांक tegra210_emc_debug_min_rate_get(व्योम *data, u64 *rate)
अणु
	काष्ठा tegra210_emc *emc = data;

	*rate = emc->debugfs.min_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_emc_debug_min_rate_set(व्योम *data, u64 rate)
अणु
	काष्ठा tegra210_emc *emc = data;
	पूर्णांक err;

	अगर (!tegra210_emc_validate_rate(emc, rate))
		वापस -EINVAL;

	err = clk_set_min_rate(emc->clk, rate);
	अगर (err < 0)
		वापस err;

	emc->debugfs.min_rate = rate;

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(tegra210_emc_debug_min_rate_fops,
			tegra210_emc_debug_min_rate_get,
			tegra210_emc_debug_min_rate_set, "%llu\n");

अटल पूर्णांक tegra210_emc_debug_max_rate_get(व्योम *data, u64 *rate)
अणु
	काष्ठा tegra210_emc *emc = data;

	*rate = emc->debugfs.max_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_emc_debug_max_rate_set(व्योम *data, u64 rate)
अणु
	काष्ठा tegra210_emc *emc = data;
	पूर्णांक err;

	अगर (!tegra210_emc_validate_rate(emc, rate))
		वापस -EINVAL;

	err = clk_set_max_rate(emc->clk, rate);
	अगर (err < 0)
		वापस err;

	emc->debugfs.max_rate = rate;

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(tegra210_emc_debug_max_rate_fops,
			tegra210_emc_debug_max_rate_get,
			tegra210_emc_debug_max_rate_set, "%llu\n");

अटल पूर्णांक tegra210_emc_debug_temperature_get(व्योम *data, u64 *temperature)
अणु
	काष्ठा tegra210_emc *emc = data;
	अचिन्हित पूर्णांक value;

	अगर (!emc->debugfs.temperature)
		value = tegra210_emc_get_temperature(emc);
	अन्यथा
		value = emc->debugfs.temperature;

	*temperature = value;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_emc_debug_temperature_set(व्योम *data, u64 temperature)
अणु
	काष्ठा tegra210_emc *emc = data;

	अगर (temperature > 7)
		वापस -EINVAL;

	emc->debugfs.temperature = temperature;

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(tegra210_emc_debug_temperature_fops,
			tegra210_emc_debug_temperature_get,
			tegra210_emc_debug_temperature_set, "%llu\n");

अटल व्योम tegra210_emc_debugfs_init(काष्ठा tegra210_emc *emc)
अणु
	काष्ठा device *dev = emc->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	emc->debugfs.min_rate = अच_दीर्घ_उच्च;
	emc->debugfs.max_rate = 0;

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		अगर (emc->timings[i].rate * 1000UL < emc->debugfs.min_rate)
			emc->debugfs.min_rate = emc->timings[i].rate * 1000UL;

		अगर (emc->timings[i].rate * 1000UL > emc->debugfs.max_rate)
			emc->debugfs.max_rate = emc->timings[i].rate * 1000UL;
	पूर्ण

	अगर (!emc->num_timings) अणु
		emc->debugfs.min_rate = clk_get_rate(emc->clk);
		emc->debugfs.max_rate = emc->debugfs.min_rate;
	पूर्ण

	err = clk_set_rate_range(emc->clk, emc->debugfs.min_rate,
				 emc->debugfs.max_rate);
	अगर (err < 0) अणु
		dev_err(dev, "failed to set rate range [%lu-%lu] for %pC\n",
			emc->debugfs.min_rate, emc->debugfs.max_rate,
			emc->clk);
		वापस;
	पूर्ण

	emc->debugfs.root = debugfs_create_dir("emc", शून्य);
	अगर (!emc->debugfs.root) अणु
		dev_err(dev, "failed to create debugfs directory\n");
		वापस;
	पूर्ण

	debugfs_create_file("available_rates", 0444, emc->debugfs.root, emc,
			    &tegra210_emc_debug_available_rates_fops);
	debugfs_create_file("min_rate", 0644, emc->debugfs.root, emc,
			    &tegra210_emc_debug_min_rate_fops);
	debugfs_create_file("max_rate", 0644, emc->debugfs.root, emc,
			    &tegra210_emc_debug_max_rate_fops);
	debugfs_create_file("temperature", 0644, emc->debugfs.root, emc,
			    &tegra210_emc_debug_temperature_fops);
पूर्ण

अटल व्योम tegra210_emc_detect(काष्ठा tegra210_emc *emc)
अणु
	u32 value;

	/* probe the number of connected DRAM devices */
	value = mc_पढ़ोl(emc->mc, MC_EMEM_ADR_CFG);

	अगर (value & MC_EMEM_ADR_CFG_EMEM_NUMDEV)
		emc->num_devices = 2;
	अन्यथा
		emc->num_devices = 1;

	/* probe the type of DRAM */
	value = emc_पढ़ोl(emc, EMC_FBIO_CFG5);
	emc->dram_type = value & 0x3;

	/* probe the number of channels */
	value = emc_पढ़ोl(emc, EMC_FBIO_CFG7);

	अगर ((value & EMC_FBIO_CFG7_CH1_ENABLE) &&
	    (value & EMC_FBIO_CFG7_CH0_ENABLE))
		emc->num_channels = 2;
	अन्यथा
		emc->num_channels = 1;
पूर्ण

अटल पूर्णांक tegra210_emc_validate_timings(काष्ठा tegra210_emc *emc,
					 काष्ठा tegra210_emc_timing *timings,
					 अचिन्हित पूर्णांक num_timings)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_timings; i++) अणु
		u32 min_volt = timings[i].min_volt;
		u32 rate = timings[i].rate;

		अगर (!rate)
			वापस -EINVAL;

		अगर ((i > 0) && ((rate <= timings[i - 1].rate) ||
		    (min_volt < timings[i - 1].min_volt)))
			वापस -EINVAL;

		अगर (timings[i].revision != timings[0].revision)
			जारी;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_emc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा thermal_cooling_device *cd;
	अचिन्हित दीर्घ current_rate;
	काष्ठा tegra210_emc *emc;
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	emc = devm_kzalloc(&pdev->dev, माप(*emc), GFP_KERNEL);
	अगर (!emc)
		वापस -ENOMEM;

	emc->clk = devm_clk_get(&pdev->dev, "emc");
	अगर (IS_ERR(emc->clk))
		वापस PTR_ERR(emc->clk);

	platक्रमm_set_drvdata(pdev, emc);
	spin_lock_init(&emc->lock);
	emc->dev = &pdev->dev;

	emc->mc = devm_tegra_memory_controller_get(&pdev->dev);
	अगर (IS_ERR(emc->mc))
		वापस PTR_ERR(emc->mc);

	emc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(emc->regs))
		वापस PTR_ERR(emc->regs);

	क्रम (i = 0; i < 2; i++) अणु
		emc->channel[i] = devm_platक्रमm_ioremap_resource(pdev, 1 + i);
		अगर (IS_ERR(emc->channel[i]))
			वापस PTR_ERR(emc->channel[i]);

	पूर्ण

	tegra210_emc_detect(emc);
	np = pdev->dev.of_node;

	/* attach to the nominal and (optional) derated tables */
	err = of_reserved_mem_device_init_by_name(emc->dev, np, "nominal");
	अगर (err < 0) अणु
		dev_err(emc->dev, "failed to get nominal EMC table: %d\n", err);
		वापस err;
	पूर्ण

	err = of_reserved_mem_device_init_by_name(emc->dev, np, "derated");
	अगर (err < 0 && err != -ENODEV) अणु
		dev_err(emc->dev, "failed to get derated EMC table: %d\n", err);
		जाओ release;
	पूर्ण

	/* validate the tables */
	अगर (emc->nominal) अणु
		err = tegra210_emc_validate_timings(emc, emc->nominal,
						    emc->num_timings);
		अगर (err < 0)
			जाओ release;
	पूर्ण

	अगर (emc->derated) अणु
		err = tegra210_emc_validate_timings(emc, emc->derated,
						    emc->num_timings);
		अगर (err < 0)
			जाओ release;
	पूर्ण

	/* शेष to the nominal table */
	emc->timings = emc->nominal;

	/* pick the current timing based on the current EMC घड़ी rate */
	current_rate = clk_get_rate(emc->clk) / 1000;

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		अगर (emc->timings[i].rate == current_rate) अणु
			emc->last = &emc->timings[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == emc->num_timings) अणु
		dev_err(emc->dev, "no EMC table entry found for %lu kHz\n",
			current_rate);
		err = -ENOENT;
		जाओ release;
	पूर्ण

	/* pick a compatible घड़ी change sequence क्रम the EMC table */
	क्रम (i = 0; i < ARRAY_SIZE(tegra210_emc_sequences); i++) अणु
		स्थिर काष्ठा tegra210_emc_sequence *sequence =
				tegra210_emc_sequences[i];

		अगर (emc->timings[0].revision == sequence->revision) अणु
			emc->sequence = sequence;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!emc->sequence) अणु
		dev_err(&pdev->dev, "sequence %u not supported\n",
			emc->timings[0].revision);
		err = -ENOTSUPP;
		जाओ release;
	पूर्ण

	emc->offsets = &tegra210_emc_table_रेजिस्टर_offsets;
	emc->refresh = TEGRA210_EMC_REFRESH_NOMINAL;

	emc->provider.owner = THIS_MODULE;
	emc->provider.dev = &pdev->dev;
	emc->provider.set_rate = tegra210_emc_set_rate;

	emc->provider.configs = devm_kसुस्मृति(&pdev->dev, emc->num_timings,
					     माप(*emc->provider.configs),
					     GFP_KERNEL);
	अगर (!emc->provider.configs) अणु
		err = -ENOMEM;
		जाओ release;
	पूर्ण

	emc->provider.num_configs = emc->num_timings;

	क्रम (i = 0; i < emc->provider.num_configs; i++) अणु
		काष्ठा tegra210_emc_timing *timing = &emc->timings[i];
		काष्ठा tegra210_clk_emc_config *config =
				&emc->provider.configs[i];
		u32 value;

		config->rate = timing->rate * 1000UL;
		config->value = timing->clk_src_emc;

		value = timing->burst_mc_regs[MC_EMEM_ARB_MISC0_INDEX];

		अगर ((value & MC_EMEM_ARB_MISC0_EMC_SAME_FREQ) == 0)
			config->same_freq = false;
		अन्यथा
			config->same_freq = true;
	पूर्ण

	err = tegra210_clk_emc_attach(emc->clk, &emc->provider);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to attach to EMC clock: %d\n", err);
		जाओ release;
	पूर्ण

	emc->clkchange_delay = 100;
	emc->training_पूर्णांकerval = 100;
	dev_set_drvdata(emc->dev, emc);

	समयr_setup(&emc->refresh_समयr, tegra210_emc_poll_refresh,
		    TIMER_DEFERRABLE);
	atomic_set(&emc->refresh_poll, 0);
	emc->refresh_poll_पूर्णांकerval = 1000;

	समयr_setup(&emc->training, tegra210_emc_train, 0);

	tegra210_emc_debugfs_init(emc);

	cd = devm_thermal_of_cooling_device_रेजिस्टर(emc->dev, np, "emc", emc,
						     &tegra210_emc_cd_ops);
	अगर (IS_ERR(cd)) अणु
		err = PTR_ERR(cd);
		dev_err(emc->dev, "failed to register cooling device: %d\n",
			err);
		जाओ detach;
	पूर्ण

	वापस 0;

detach:
	debugfs_हटाओ_recursive(emc->debugfs.root);
	tegra210_clk_emc_detach(emc->clk);
release:
	of_reserved_mem_device_release(emc->dev);

	वापस err;
पूर्ण

अटल पूर्णांक tegra210_emc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra210_emc *emc = platक्रमm_get_drvdata(pdev);

	debugfs_हटाओ_recursive(emc->debugfs.root);
	tegra210_clk_emc_detach(emc->clk);
	of_reserved_mem_device_release(emc->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra210_emc_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra210_emc *emc = dev_get_drvdata(dev);
	पूर्णांक err;

	err = clk_rate_exclusive_get(emc->clk);
	अगर (err < 0) अणु
		dev_err(emc->dev, "failed to acquire clock: %d\n", err);
		वापस err;
	पूर्ण

	emc->resume_rate = clk_get_rate(emc->clk);

	clk_set_rate(emc->clk, 204000000);
	tegra210_clk_emc_detach(emc->clk);

	dev_dbg(dev, "suspending at %lu Hz\n", clk_get_rate(emc->clk));

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra210_emc_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra210_emc *emc = dev_get_drvdata(dev);
	पूर्णांक err;

	err = tegra210_clk_emc_attach(emc->clk, &emc->provider);
	अगर (err < 0) अणु
		dev_err(dev, "failed to attach to EMC clock: %d\n", err);
		वापस err;
	पूर्ण

	clk_set_rate(emc->clk, emc->resume_rate);
	clk_rate_exclusive_put(emc->clk);

	dev_dbg(dev, "resuming at %lu Hz\n", clk_get_rate(emc->clk));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra210_emc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(tegra210_emc_suspend, tegra210_emc_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra210_emc_of_match[] = अणु
	अणु .compatible = "nvidia,tegra210-emc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra210_emc_of_match);

अटल काष्ठा platक्रमm_driver tegra210_emc_driver = अणु
	.driver = अणु
		.name = "tegra210-emc",
		.of_match_table = tegra210_emc_of_match,
		.pm = &tegra210_emc_pm_ops,
	पूर्ण,
	.probe = tegra210_emc_probe,
	.हटाओ = tegra210_emc_हटाओ,
पूर्ण;

module_platक्रमm_driver(tegra210_emc_driver);

MODULE_AUTHOR("Thierry Reding <treding@nvidia.com>");
MODULE_AUTHOR("Joseph Lo <josephl@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra210 EMC driver");
MODULE_LICENSE("GPL v2");
