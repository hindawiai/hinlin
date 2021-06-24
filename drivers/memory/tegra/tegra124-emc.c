<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author:
 *	Mikko Perttunen <mperttunen@nvidia.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/sort.h>
#समावेश <linux/माला.स>

#समावेश <soc/tegra/fuse.h>
#समावेश <soc/tegra/mc.h>

#समावेश "mc.h"

#घोषणा EMC_FBIO_CFG5				0x104
#घोषणा	EMC_FBIO_CFG5_DRAM_TYPE_MASK		0x3
#घोषणा	EMC_FBIO_CFG5_DRAM_TYPE_SHIFT		0
#घोषणा EMC_FBIO_CFG5_DRAM_WIDTH_X64		BIT(4)

#घोषणा EMC_INTSTATUS				0x0
#घोषणा EMC_INTSTATUS_CLKCHANGE_COMPLETE	BIT(4)

#घोषणा EMC_CFG					0xc
#घोषणा EMC_CFG_DRAM_CLKSTOP_PD			BIT(31)
#घोषणा EMC_CFG_DRAM_CLKSTOP_SR			BIT(30)
#घोषणा EMC_CFG_DRAM_ACPD			BIT(29)
#घोषणा EMC_CFG_DYN_SREF			BIT(28)
#घोषणा EMC_CFG_PWR_MASK			((0xF << 28) | BIT(18))
#घोषणा EMC_CFG_DSR_VTTGEN_DRV_EN		BIT(18)

#घोषणा EMC_REFCTRL				0x20
#घोषणा EMC_REFCTRL_DEV_SEL_SHIFT		0
#घोषणा EMC_REFCTRL_ENABLE			BIT(31)

#घोषणा EMC_TIMING_CONTROL			0x28
#घोषणा EMC_RC					0x2c
#घोषणा EMC_RFC					0x30
#घोषणा EMC_RAS					0x34
#घोषणा EMC_RP					0x38
#घोषणा EMC_R2W					0x3c
#घोषणा EMC_W2R					0x40
#घोषणा EMC_R2P					0x44
#घोषणा EMC_W2P					0x48
#घोषणा EMC_RD_RCD				0x4c
#घोषणा EMC_WR_RCD				0x50
#घोषणा EMC_RRD					0x54
#घोषणा EMC_REXT				0x58
#घोषणा EMC_WDV					0x5c
#घोषणा EMC_QUSE				0x60
#घोषणा EMC_QRST				0x64
#घोषणा EMC_QSAFE				0x68
#घोषणा EMC_RDV					0x6c
#घोषणा EMC_REFRESH				0x70
#घोषणा EMC_BURST_REFRESH_NUM			0x74
#घोषणा EMC_PDEX2WR				0x78
#घोषणा EMC_PDEX2RD				0x7c
#घोषणा EMC_PCHG2PDEN				0x80
#घोषणा EMC_ACT2PDEN				0x84
#घोषणा EMC_AR2PDEN				0x88
#घोषणा EMC_RW2PDEN				0x8c
#घोषणा EMC_TXSR				0x90
#घोषणा EMC_TCKE				0x94
#घोषणा EMC_TFAW				0x98
#घोषणा EMC_TRPAB				0x9c
#घोषणा EMC_TCLKSTABLE				0xa0
#घोषणा EMC_TCLKSTOP				0xa4
#घोषणा EMC_TREFBW				0xa8
#घोषणा EMC_ODT_WRITE				0xb0
#घोषणा EMC_ODT_READ				0xb4
#घोषणा EMC_WEXT				0xb8
#घोषणा EMC_CTT					0xbc
#घोषणा EMC_RFC_SLR				0xc0
#घोषणा EMC_MRS_WAIT_CNT2			0xc4

#घोषणा EMC_MRS_WAIT_CNT			0xc8
#घोषणा EMC_MRS_WAIT_CNT_SHORT_WAIT_SHIFT	0
#घोषणा EMC_MRS_WAIT_CNT_SHORT_WAIT_MASK	\
	(0x3FF << EMC_MRS_WAIT_CNT_SHORT_WAIT_SHIFT)
#घोषणा EMC_MRS_WAIT_CNT_LONG_WAIT_SHIFT	16
#घोषणा EMC_MRS_WAIT_CNT_LONG_WAIT_MASK		\
	(0x3FF << EMC_MRS_WAIT_CNT_LONG_WAIT_SHIFT)

#घोषणा EMC_MRS					0xcc
#घोषणा EMC_MODE_SET_DLL_RESET			BIT(8)
#घोषणा EMC_MODE_SET_LONG_CNT			BIT(26)
#घोषणा EMC_EMRS				0xd0
#घोषणा EMC_REF					0xd4
#घोषणा EMC_PRE					0xd8

#घोषणा EMC_SELF_REF				0xe0
#घोषणा EMC_SELF_REF_CMD_ENABLED		BIT(0)
#घोषणा EMC_SELF_REF_DEV_SEL_SHIFT		30

#घोषणा EMC_MRW					0xe8

#घोषणा EMC_MRR					0xec
#घोषणा EMC_MRR_MA_SHIFT			16
#घोषणा LPDDR2_MR4_TEMP_SHIFT			0

#घोषणा EMC_XM2DQSPADCTRL3			0xf8
#घोषणा EMC_FBIO_SPARE				0x100

#घोषणा EMC_FBIO_CFG6				0x114
#घोषणा EMC_EMRS2				0x12c
#घोषणा EMC_MRW2				0x134
#घोषणा EMC_MRW4				0x13c
#घोषणा EMC_EINPUT				0x14c
#घोषणा EMC_EINPUT_DURATION			0x150
#घोषणा EMC_PUTERM_EXTRA			0x154
#घोषणा EMC_TCKESR				0x158
#घोषणा EMC_TPD					0x15c

#घोषणा EMC_AUTO_CAL_CONFIG			0x2a4
#घोषणा EMC_AUTO_CAL_CONFIG_AUTO_CAL_START	BIT(31)
#घोषणा EMC_AUTO_CAL_INTERVAL			0x2a8
#घोषणा EMC_AUTO_CAL_STATUS			0x2ac
#घोषणा EMC_AUTO_CAL_STATUS_ACTIVE		BIT(31)
#घोषणा EMC_STATUS				0x2b4
#घोषणा EMC_STATUS_TIMING_UPDATE_STALLED	BIT(23)

#घोषणा EMC_CFG_2				0x2b8
#घोषणा EMC_CFG_2_MODE_SHIFT			0
#घोषणा EMC_CFG_2_DIS_STP_OB_CLK_DURING_NON_WR	BIT(6)

#घोषणा EMC_CFG_DIG_DLL				0x2bc
#घोषणा EMC_CFG_DIG_DLL_PERIOD			0x2c0
#घोषणा EMC_RDV_MASK				0x2cc
#घोषणा EMC_WDV_MASK				0x2d0
#घोषणा EMC_CTT_DURATION			0x2d8
#घोषणा EMC_CTT_TERM_CTRL			0x2dc
#घोषणा EMC_ZCAL_INTERVAL			0x2e0
#घोषणा EMC_ZCAL_WAIT_CNT			0x2e4

#घोषणा EMC_ZQ_CAL				0x2ec
#घोषणा EMC_ZQ_CAL_CMD				BIT(0)
#घोषणा EMC_ZQ_CAL_LONG				BIT(4)
#घोषणा EMC_ZQ_CAL_LONG_CMD_DEV0		\
	(DRAM_DEV_SEL_0 | EMC_ZQ_CAL_LONG | EMC_ZQ_CAL_CMD)
#घोषणा EMC_ZQ_CAL_LONG_CMD_DEV1		\
	(DRAM_DEV_SEL_1 | EMC_ZQ_CAL_LONG | EMC_ZQ_CAL_CMD)

#घोषणा EMC_XM2CMDPADCTRL			0x2f0
#घोषणा EMC_XM2DQSPADCTRL			0x2f8
#घोषणा EMC_XM2DQSPADCTRL2			0x2fc
#घोषणा EMC_XM2DQSPADCTRL2_RX_FT_REC_ENABLE	BIT(0)
#घोषणा EMC_XM2DQSPADCTRL2_VREF_ENABLE		BIT(5)
#घोषणा EMC_XM2DQPADCTRL			0x300
#घोषणा EMC_XM2DQPADCTRL2			0x304
#घोषणा EMC_XM2CLKPADCTRL			0x308
#घोषणा EMC_XM2COMPPADCTRL			0x30c
#घोषणा EMC_XM2VTTGENPADCTRL			0x310
#घोषणा EMC_XM2VTTGENPADCTRL2			0x314
#घोषणा EMC_XM2VTTGENPADCTRL3			0x318
#घोषणा EMC_XM2DQSPADCTRL4			0x320
#घोषणा EMC_DLL_XFORM_DQS0			0x328
#घोषणा EMC_DLL_XFORM_DQS1			0x32c
#घोषणा EMC_DLL_XFORM_DQS2			0x330
#घोषणा EMC_DLL_XFORM_DQS3			0x334
#घोषणा EMC_DLL_XFORM_DQS4			0x338
#घोषणा EMC_DLL_XFORM_DQS5			0x33c
#घोषणा EMC_DLL_XFORM_DQS6			0x340
#घोषणा EMC_DLL_XFORM_DQS7			0x344
#घोषणा EMC_DLL_XFORM_QUSE0			0x348
#घोषणा EMC_DLL_XFORM_QUSE1			0x34c
#घोषणा EMC_DLL_XFORM_QUSE2			0x350
#घोषणा EMC_DLL_XFORM_QUSE3			0x354
#घोषणा EMC_DLL_XFORM_QUSE4			0x358
#घोषणा EMC_DLL_XFORM_QUSE5			0x35c
#घोषणा EMC_DLL_XFORM_QUSE6			0x360
#घोषणा EMC_DLL_XFORM_QUSE7			0x364
#घोषणा EMC_DLL_XFORM_DQ0			0x368
#घोषणा EMC_DLL_XFORM_DQ1			0x36c
#घोषणा EMC_DLL_XFORM_DQ2			0x370
#घोषणा EMC_DLL_XFORM_DQ3			0x374
#घोषणा EMC_DLI_TRIM_TXDQS0			0x3a8
#घोषणा EMC_DLI_TRIM_TXDQS1			0x3ac
#घोषणा EMC_DLI_TRIM_TXDQS2			0x3b0
#घोषणा EMC_DLI_TRIM_TXDQS3			0x3b4
#घोषणा EMC_DLI_TRIM_TXDQS4			0x3b8
#घोषणा EMC_DLI_TRIM_TXDQS5			0x3bc
#घोषणा EMC_DLI_TRIM_TXDQS6			0x3c0
#घोषणा EMC_DLI_TRIM_TXDQS7			0x3c4
#घोषणा EMC_STALL_THEN_EXE_AFTER_CLKCHANGE	0x3cc
#घोषणा EMC_SEL_DPD_CTRL			0x3d8
#घोषणा EMC_SEL_DPD_CTRL_DATA_SEL_DPD		BIT(8)
#घोषणा EMC_SEL_DPD_CTRL_ODT_SEL_DPD		BIT(5)
#घोषणा EMC_SEL_DPD_CTRL_RESET_SEL_DPD		BIT(4)
#घोषणा EMC_SEL_DPD_CTRL_CA_SEL_DPD		BIT(3)
#घोषणा EMC_SEL_DPD_CTRL_CLK_SEL_DPD		BIT(2)
#घोषणा EMC_SEL_DPD_CTRL_DDR3_MASK	\
	((0xf << 2) | BIT(8))
#घोषणा EMC_SEL_DPD_CTRL_MASK \
	((0x3 << 2) | BIT(5) | BIT(8))
#घोषणा EMC_PRE_REFRESH_REQ_CNT			0x3dc
#घोषणा EMC_DYN_SELF_REF_CONTROL		0x3e0
#घोषणा EMC_TXSRDLL				0x3e4
#घोषणा EMC_CCFIFO_ADDR				0x3e8
#घोषणा EMC_CCFIFO_DATA				0x3ec
#घोषणा EMC_CCFIFO_STATUS			0x3f0
#घोषणा EMC_CDB_CNTL_1				0x3f4
#घोषणा EMC_CDB_CNTL_2				0x3f8
#घोषणा EMC_XM2CLKPADCTRL2			0x3fc
#घोषणा EMC_AUTO_CAL_CONFIG2			0x458
#घोषणा EMC_AUTO_CAL_CONFIG3			0x45c
#घोषणा EMC_IBDLY				0x468
#घोषणा EMC_DLL_XFORM_ADDR0			0x46c
#घोषणा EMC_DLL_XFORM_ADDR1			0x470
#घोषणा EMC_DLL_XFORM_ADDR2			0x474
#घोषणा EMC_DSR_VTTGEN_DRV			0x47c
#घोषणा EMC_TXDSRVTTGEN				0x480
#घोषणा EMC_XM2CMDPADCTRL4			0x484
#घोषणा EMC_XM2CMDPADCTRL5			0x488
#घोषणा EMC_DLL_XFORM_DQS8			0x4a0
#घोषणा EMC_DLL_XFORM_DQS9			0x4a4
#घोषणा EMC_DLL_XFORM_DQS10			0x4a8
#घोषणा EMC_DLL_XFORM_DQS11			0x4ac
#घोषणा EMC_DLL_XFORM_DQS12			0x4b0
#घोषणा EMC_DLL_XFORM_DQS13			0x4b4
#घोषणा EMC_DLL_XFORM_DQS14			0x4b8
#घोषणा EMC_DLL_XFORM_DQS15			0x4bc
#घोषणा EMC_DLL_XFORM_QUSE8			0x4c0
#घोषणा EMC_DLL_XFORM_QUSE9			0x4c4
#घोषणा EMC_DLL_XFORM_QUSE10			0x4c8
#घोषणा EMC_DLL_XFORM_QUSE11			0x4cc
#घोषणा EMC_DLL_XFORM_QUSE12			0x4d0
#घोषणा EMC_DLL_XFORM_QUSE13			0x4d4
#घोषणा EMC_DLL_XFORM_QUSE14			0x4d8
#घोषणा EMC_DLL_XFORM_QUSE15			0x4dc
#घोषणा EMC_DLL_XFORM_DQ4			0x4e0
#घोषणा EMC_DLL_XFORM_DQ5			0x4e4
#घोषणा EMC_DLL_XFORM_DQ6			0x4e8
#घोषणा EMC_DLL_XFORM_DQ7			0x4ec
#घोषणा EMC_DLI_TRIM_TXDQS8			0x520
#घोषणा EMC_DLI_TRIM_TXDQS9			0x524
#घोषणा EMC_DLI_TRIM_TXDQS10			0x528
#घोषणा EMC_DLI_TRIM_TXDQS11			0x52c
#घोषणा EMC_DLI_TRIM_TXDQS12			0x530
#घोषणा EMC_DLI_TRIM_TXDQS13			0x534
#घोषणा EMC_DLI_TRIM_TXDQS14			0x538
#घोषणा EMC_DLI_TRIM_TXDQS15			0x53c
#घोषणा EMC_CDB_CNTL_3				0x540
#घोषणा EMC_XM2DQSPADCTRL5			0x544
#घोषणा EMC_XM2DQSPADCTRL6			0x548
#घोषणा EMC_XM2DQPADCTRL3			0x54c
#घोषणा EMC_DLL_XFORM_ADDR3			0x550
#घोषणा EMC_DLL_XFORM_ADDR4			0x554
#घोषणा EMC_DLL_XFORM_ADDR5			0x558
#घोषणा EMC_CFG_PIPE				0x560
#घोषणा EMC_QPOP				0x564
#घोषणा EMC_QUSE_WIDTH				0x568
#घोषणा EMC_PUTERM_WIDTH			0x56c
#घोषणा EMC_BGBIAS_CTL0				0x570
#घोषणा EMC_BGBIAS_CTL0_BIAS0_DSC_E_PWRD_IBIAS_RX BIT(3)
#घोषणा EMC_BGBIAS_CTL0_BIAS0_DSC_E_PWRD_IBIAS_VTTGEN BIT(2)
#घोषणा EMC_BGBIAS_CTL0_BIAS0_DSC_E_PWRD	BIT(1)
#घोषणा EMC_PUTERM_ADJ				0x574

#घोषणा DRAM_DEV_SEL_ALL			0
#घोषणा DRAM_DEV_SEL_0				(2 << 30)
#घोषणा DRAM_DEV_SEL_1				(1 << 30)

#घोषणा EMC_CFG_POWER_FEATURES_MASK		\
	(EMC_CFG_DYN_SREF | EMC_CFG_DRAM_ACPD | EMC_CFG_DRAM_CLKSTOP_SR | \
	EMC_CFG_DRAM_CLKSTOP_PD | EMC_CFG_DSR_VTTGEN_DRV_EN)
#घोषणा EMC_REFCTRL_DEV_SEL(n) (((n > 1) ? 0 : 2) << EMC_REFCTRL_DEV_SEL_SHIFT)
#घोषणा EMC_DRAM_DEV_SEL(n) ((n > 1) ? DRAM_DEV_SEL_ALL : DRAM_DEV_SEL_0)

/* Maximum amount of समय in us. to रुको क्रम changes to become effective */
#घोषणा EMC_STATUS_UPDATE_TIMEOUT		1000

क्रमागत emc_dram_type अणु
	DRAM_TYPE_DDR3 = 0,
	DRAM_TYPE_DDR1 = 1,
	DRAM_TYPE_LPDDR3 = 2,
	DRAM_TYPE_DDR2 = 3
पूर्ण;

क्रमागत emc_dll_change अणु
	DLL_CHANGE_NONE,
	DLL_CHANGE_ON,
	DLL_CHANGE_OFF
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ emc_burst_regs[] = अणु
	EMC_RC,
	EMC_RFC,
	EMC_RFC_SLR,
	EMC_RAS,
	EMC_RP,
	EMC_R2W,
	EMC_W2R,
	EMC_R2P,
	EMC_W2P,
	EMC_RD_RCD,
	EMC_WR_RCD,
	EMC_RRD,
	EMC_REXT,
	EMC_WEXT,
	EMC_WDV,
	EMC_WDV_MASK,
	EMC_QUSE,
	EMC_QUSE_WIDTH,
	EMC_IBDLY,
	EMC_EINPUT,
	EMC_EINPUT_DURATION,
	EMC_PUTERM_EXTRA,
	EMC_PUTERM_WIDTH,
	EMC_PUTERM_ADJ,
	EMC_CDB_CNTL_1,
	EMC_CDB_CNTL_2,
	EMC_CDB_CNTL_3,
	EMC_QRST,
	EMC_QSAFE,
	EMC_RDV,
	EMC_RDV_MASK,
	EMC_REFRESH,
	EMC_BURST_REFRESH_NUM,
	EMC_PRE_REFRESH_REQ_CNT,
	EMC_PDEX2WR,
	EMC_PDEX2RD,
	EMC_PCHG2PDEN,
	EMC_ACT2PDEN,
	EMC_AR2PDEN,
	EMC_RW2PDEN,
	EMC_TXSR,
	EMC_TXSRDLL,
	EMC_TCKE,
	EMC_TCKESR,
	EMC_TPD,
	EMC_TFAW,
	EMC_TRPAB,
	EMC_TCLKSTABLE,
	EMC_TCLKSTOP,
	EMC_TREFBW,
	EMC_FBIO_CFG6,
	EMC_ODT_WRITE,
	EMC_ODT_READ,
	EMC_FBIO_CFG5,
	EMC_CFG_DIG_DLL,
	EMC_CFG_DIG_DLL_PERIOD,
	EMC_DLL_XFORM_DQS0,
	EMC_DLL_XFORM_DQS1,
	EMC_DLL_XFORM_DQS2,
	EMC_DLL_XFORM_DQS3,
	EMC_DLL_XFORM_DQS4,
	EMC_DLL_XFORM_DQS5,
	EMC_DLL_XFORM_DQS6,
	EMC_DLL_XFORM_DQS7,
	EMC_DLL_XFORM_DQS8,
	EMC_DLL_XFORM_DQS9,
	EMC_DLL_XFORM_DQS10,
	EMC_DLL_XFORM_DQS11,
	EMC_DLL_XFORM_DQS12,
	EMC_DLL_XFORM_DQS13,
	EMC_DLL_XFORM_DQS14,
	EMC_DLL_XFORM_DQS15,
	EMC_DLL_XFORM_QUSE0,
	EMC_DLL_XFORM_QUSE1,
	EMC_DLL_XFORM_QUSE2,
	EMC_DLL_XFORM_QUSE3,
	EMC_DLL_XFORM_QUSE4,
	EMC_DLL_XFORM_QUSE5,
	EMC_DLL_XFORM_QUSE6,
	EMC_DLL_XFORM_QUSE7,
	EMC_DLL_XFORM_ADDR0,
	EMC_DLL_XFORM_ADDR1,
	EMC_DLL_XFORM_ADDR2,
	EMC_DLL_XFORM_ADDR3,
	EMC_DLL_XFORM_ADDR4,
	EMC_DLL_XFORM_ADDR5,
	EMC_DLL_XFORM_QUSE8,
	EMC_DLL_XFORM_QUSE9,
	EMC_DLL_XFORM_QUSE10,
	EMC_DLL_XFORM_QUSE11,
	EMC_DLL_XFORM_QUSE12,
	EMC_DLL_XFORM_QUSE13,
	EMC_DLL_XFORM_QUSE14,
	EMC_DLL_XFORM_QUSE15,
	EMC_DLI_TRIM_TXDQS0,
	EMC_DLI_TRIM_TXDQS1,
	EMC_DLI_TRIM_TXDQS2,
	EMC_DLI_TRIM_TXDQS3,
	EMC_DLI_TRIM_TXDQS4,
	EMC_DLI_TRIM_TXDQS5,
	EMC_DLI_TRIM_TXDQS6,
	EMC_DLI_TRIM_TXDQS7,
	EMC_DLI_TRIM_TXDQS8,
	EMC_DLI_TRIM_TXDQS9,
	EMC_DLI_TRIM_TXDQS10,
	EMC_DLI_TRIM_TXDQS11,
	EMC_DLI_TRIM_TXDQS12,
	EMC_DLI_TRIM_TXDQS13,
	EMC_DLI_TRIM_TXDQS14,
	EMC_DLI_TRIM_TXDQS15,
	EMC_DLL_XFORM_DQ0,
	EMC_DLL_XFORM_DQ1,
	EMC_DLL_XFORM_DQ2,
	EMC_DLL_XFORM_DQ3,
	EMC_DLL_XFORM_DQ4,
	EMC_DLL_XFORM_DQ5,
	EMC_DLL_XFORM_DQ6,
	EMC_DLL_XFORM_DQ7,
	EMC_XM2CMDPADCTRL,
	EMC_XM2CMDPADCTRL4,
	EMC_XM2CMDPADCTRL5,
	EMC_XM2DQPADCTRL2,
	EMC_XM2DQPADCTRL3,
	EMC_XM2CLKPADCTRL,
	EMC_XM2CLKPADCTRL2,
	EMC_XM2COMPPADCTRL,
	EMC_XM2VTTGENPADCTRL,
	EMC_XM2VTTGENPADCTRL2,
	EMC_XM2VTTGENPADCTRL3,
	EMC_XM2DQSPADCTRL3,
	EMC_XM2DQSPADCTRL4,
	EMC_XM2DQSPADCTRL5,
	EMC_XM2DQSPADCTRL6,
	EMC_DSR_VTTGEN_DRV,
	EMC_TXDSRVTTGEN,
	EMC_FBIO_SPARE,
	EMC_ZCAL_WAIT_CNT,
	EMC_MRS_WAIT_CNT2,
	EMC_CTT,
	EMC_CTT_DURATION,
	EMC_CFG_PIPE,
	EMC_DYN_SELF_REF_CONTROL,
	EMC_QPOP
पूर्ण;

काष्ठा emc_timing अणु
	अचिन्हित दीर्घ rate;

	u32 emc_burst_data[ARRAY_SIZE(emc_burst_regs)];

	u32 emc_स्वतः_cal_config;
	u32 emc_स्वतः_cal_config2;
	u32 emc_स्वतः_cal_config3;
	u32 emc_स्वतः_cal_पूर्णांकerval;
	u32 emc_bgbias_ctl0;
	u32 emc_cfg;
	u32 emc_cfg_2;
	u32 emc_ctt_term_ctrl;
	u32 emc_mode_1;
	u32 emc_mode_2;
	u32 emc_mode_4;
	u32 emc_mode_reset;
	u32 emc_mrs_रुको_cnt;
	u32 emc_sel_dpd_ctrl;
	u32 emc_xm2dqspadctrl2;
	u32 emc_zcal_cnt_दीर्घ;
	u32 emc_zcal_पूर्णांकerval;
पूर्ण;

क्रमागत emc_rate_request_type अणु
	EMC_RATE_DEBUG,
	EMC_RATE_ICC,
	EMC_RATE_TYPE_MAX,
पूर्ण;

काष्ठा emc_rate_request अणु
	अचिन्हित दीर्घ min_rate;
	अचिन्हित दीर्घ max_rate;
पूर्ण;

काष्ठा tegra_emc अणु
	काष्ठा device *dev;

	काष्ठा tegra_mc *mc;

	व्योम __iomem *regs;

	काष्ठा clk *clk;

	क्रमागत emc_dram_type dram_type;
	अचिन्हित पूर्णांक dram_bus_width;
	अचिन्हित पूर्णांक dram_num;

	काष्ठा emc_timing last_timing;
	काष्ठा emc_timing *timings;
	अचिन्हित पूर्णांक num_timings;

	काष्ठा अणु
		काष्ठा dentry *root;
		अचिन्हित दीर्घ min_rate;
		अचिन्हित दीर्घ max_rate;
	पूर्ण debugfs;

	काष्ठा icc_provider provider;

	/*
	 * There are multiple sources in the EMC driver which could request
	 * a min/max घड़ी rate, these rates are contained in this array.
	 */
	काष्ठा emc_rate_request requested_rate[EMC_RATE_TYPE_MAX];

	/* protect shared rate-change code path */
	काष्ठा mutex rate_lock;
पूर्ण;

/* Timing change sequence functions */

अटल व्योम emc_ccfअगरo_ग_लिखोl(काष्ठा tegra_emc *emc, u32 value,
			      अचिन्हित दीर्घ offset)
अणु
	ग_लिखोl(value, emc->regs + EMC_CCFIFO_DATA);
	ग_लिखोl(offset, emc->regs + EMC_CCFIFO_ADDR);
पूर्ण

अटल व्योम emc_seq_update_timing(काष्ठा tegra_emc *emc)
अणु
	अचिन्हित पूर्णांक i;
	u32 value;

	ग_लिखोl(1, emc->regs + EMC_TIMING_CONTROL);

	क्रम (i = 0; i < EMC_STATUS_UPDATE_TIMEOUT; ++i) अणु
		value = पढ़ोl(emc->regs + EMC_STATUS);
		अगर ((value & EMC_STATUS_TIMING_UPDATE_STALLED) == 0)
			वापस;
		udelay(1);
	पूर्ण

	dev_err(emc->dev, "timing update timed out\n");
पूर्ण

अटल व्योम emc_seq_disable_स्वतः_cal(काष्ठा tegra_emc *emc)
अणु
	अचिन्हित पूर्णांक i;
	u32 value;

	ग_लिखोl(0, emc->regs + EMC_AUTO_CAL_INTERVAL);

	क्रम (i = 0; i < EMC_STATUS_UPDATE_TIMEOUT; ++i) अणु
		value = पढ़ोl(emc->regs + EMC_AUTO_CAL_STATUS);
		अगर ((value & EMC_AUTO_CAL_STATUS_ACTIVE) == 0)
			वापस;
		udelay(1);
	पूर्ण

	dev_err(emc->dev, "auto cal disable timed out\n");
पूर्ण

अटल व्योम emc_seq_रुको_clkchange(काष्ठा tegra_emc *emc)
अणु
	अचिन्हित पूर्णांक i;
	u32 value;

	क्रम (i = 0; i < EMC_STATUS_UPDATE_TIMEOUT; ++i) अणु
		value = पढ़ोl(emc->regs + EMC_INTSTATUS);
		अगर (value & EMC_INTSTATUS_CLKCHANGE_COMPLETE)
			वापस;
		udelay(1);
	पूर्ण

	dev_err(emc->dev, "clock change timed out\n");
पूर्ण

अटल काष्ठा emc_timing *tegra_emc_find_timing(काष्ठा tegra_emc *emc,
						अचिन्हित दीर्घ rate)
अणु
	काष्ठा emc_timing *timing = शून्य;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		अगर (emc->timings[i].rate == rate) अणु
			timing = &emc->timings[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!timing) अणु
		dev_err(emc->dev, "no timing for rate %lu\n", rate);
		वापस शून्य;
	पूर्ण

	वापस timing;
पूर्ण

अटल पूर्णांक tegra_emc_prepare_timing_change(काष्ठा tegra_emc *emc,
					   अचिन्हित दीर्घ rate)
अणु
	काष्ठा emc_timing *timing = tegra_emc_find_timing(emc, rate);
	काष्ठा emc_timing *last = &emc->last_timing;
	क्रमागत emc_dll_change dll_change;
	अचिन्हित पूर्णांक pre_रुको = 0;
	u32 val, val2, mask;
	bool update = false;
	अचिन्हित पूर्णांक i;

	अगर (!timing)
		वापस -ENOENT;

	अगर ((last->emc_mode_1 & 0x1) == (timing->emc_mode_1 & 0x1))
		dll_change = DLL_CHANGE_NONE;
	अन्यथा अगर (timing->emc_mode_1 & 0x1)
		dll_change = DLL_CHANGE_ON;
	अन्यथा
		dll_change = DLL_CHANGE_OFF;

	/* Clear CLKCHANGE_COMPLETE पूर्णांकerrupts */
	ग_लिखोl(EMC_INTSTATUS_CLKCHANGE_COMPLETE, emc->regs + EMC_INTSTATUS);

	/* Disable dynamic self-refresh */
	val = पढ़ोl(emc->regs + EMC_CFG);
	अगर (val & EMC_CFG_PWR_MASK) अणु
		val &= ~EMC_CFG_POWER_FEATURES_MASK;
		ग_लिखोl(val, emc->regs + EMC_CFG);

		pre_रुको = 5;
	पूर्ण

	/* Disable SEL_DPD_CTRL क्रम घड़ी change */
	अगर (emc->dram_type == DRAM_TYPE_DDR3)
		mask = EMC_SEL_DPD_CTRL_DDR3_MASK;
	अन्यथा
		mask = EMC_SEL_DPD_CTRL_MASK;

	val = पढ़ोl(emc->regs + EMC_SEL_DPD_CTRL);
	अगर (val & mask) अणु
		val &= ~mask;
		ग_लिखोl(val, emc->regs + EMC_SEL_DPD_CTRL);
	पूर्ण

	/* Prepare DQ/DQS क्रम घड़ी change */
	val = पढ़ोl(emc->regs + EMC_BGBIAS_CTL0);
	val2 = last->emc_bgbias_ctl0;
	अगर (!(timing->emc_bgbias_ctl0 &
	      EMC_BGBIAS_CTL0_BIAS0_DSC_E_PWRD_IBIAS_RX) &&
	    (val & EMC_BGBIAS_CTL0_BIAS0_DSC_E_PWRD_IBIAS_RX)) अणु
		val2 &= ~EMC_BGBIAS_CTL0_BIAS0_DSC_E_PWRD_IBIAS_RX;
		update = true;
	पूर्ण

	अगर ((val & EMC_BGBIAS_CTL0_BIAS0_DSC_E_PWRD) ||
	    (val & EMC_BGBIAS_CTL0_BIAS0_DSC_E_PWRD_IBIAS_VTTGEN)) अणु
		update = true;
	पूर्ण

	अगर (update) अणु
		ग_लिखोl(val2, emc->regs + EMC_BGBIAS_CTL0);
		अगर (pre_रुको < 5)
			pre_रुको = 5;
	पूर्ण

	update = false;
	val = पढ़ोl(emc->regs + EMC_XM2DQSPADCTRL2);
	अगर (timing->emc_xm2dqspadctrl2 & EMC_XM2DQSPADCTRL2_VREF_ENABLE &&
	    !(val & EMC_XM2DQSPADCTRL2_VREF_ENABLE)) अणु
		val |= EMC_XM2DQSPADCTRL2_VREF_ENABLE;
		update = true;
	पूर्ण

	अगर (timing->emc_xm2dqspadctrl2 & EMC_XM2DQSPADCTRL2_RX_FT_REC_ENABLE &&
	    !(val & EMC_XM2DQSPADCTRL2_RX_FT_REC_ENABLE)) अणु
		val |= EMC_XM2DQSPADCTRL2_RX_FT_REC_ENABLE;
		update = true;
	पूर्ण

	अगर (update) अणु
		ग_लिखोl(val, emc->regs + EMC_XM2DQSPADCTRL2);
		अगर (pre_रुको < 30)
			pre_रुको = 30;
	पूर्ण

	/* Wait to settle */
	अगर (pre_रुको) अणु
		emc_seq_update_timing(emc);
		udelay(pre_रुको);
	पूर्ण

	/* Program CTT_TERM control */
	अगर (last->emc_ctt_term_ctrl != timing->emc_ctt_term_ctrl) अणु
		emc_seq_disable_स्वतः_cal(emc);
		ग_लिखोl(timing->emc_ctt_term_ctrl,
		       emc->regs + EMC_CTT_TERM_CTRL);
		emc_seq_update_timing(emc);
	पूर्ण

	/* Program burst shaकरोw रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(timing->emc_burst_data); ++i)
		ग_लिखोl(timing->emc_burst_data[i],
		       emc->regs + emc_burst_regs[i]);

	ग_लिखोl(timing->emc_xm2dqspadctrl2, emc->regs + EMC_XM2DQSPADCTRL2);
	ग_लिखोl(timing->emc_zcal_पूर्णांकerval, emc->regs + EMC_ZCAL_INTERVAL);

	tegra_mc_ग_लिखो_emem_configuration(emc->mc, timing->rate);

	val = timing->emc_cfg & ~EMC_CFG_POWER_FEATURES_MASK;
	emc_ccfअगरo_ग_लिखोl(emc, val, EMC_CFG);

	/* Program AUTO_CAL_CONFIG */
	अगर (timing->emc_स्वतः_cal_config2 != last->emc_स्वतः_cal_config2)
		emc_ccfअगरo_ग_लिखोl(emc, timing->emc_स्वतः_cal_config2,
				  EMC_AUTO_CAL_CONFIG2);

	अगर (timing->emc_स्वतः_cal_config3 != last->emc_स्वतः_cal_config3)
		emc_ccfअगरo_ग_लिखोl(emc, timing->emc_स्वतः_cal_config3,
				  EMC_AUTO_CAL_CONFIG3);

	अगर (timing->emc_स्वतः_cal_config != last->emc_स्वतः_cal_config) अणु
		val = timing->emc_स्वतः_cal_config;
		val &= EMC_AUTO_CAL_CONFIG_AUTO_CAL_START;
		emc_ccfअगरo_ग_लिखोl(emc, val, EMC_AUTO_CAL_CONFIG);
	पूर्ण

	/* DDR3: predict MRS दीर्घ रुको count */
	अगर (emc->dram_type == DRAM_TYPE_DDR3 &&
	    dll_change == DLL_CHANGE_ON) अणु
		u32 cnt = 512;

		अगर (timing->emc_zcal_पूर्णांकerval != 0 &&
		    last->emc_zcal_पूर्णांकerval == 0)
			cnt -= emc->dram_num * 256;

		val = (timing->emc_mrs_रुको_cnt
			& EMC_MRS_WAIT_CNT_SHORT_WAIT_MASK)
			>> EMC_MRS_WAIT_CNT_SHORT_WAIT_SHIFT;
		अगर (cnt < val)
			cnt = val;

		val = timing->emc_mrs_रुको_cnt
			& ~EMC_MRS_WAIT_CNT_LONG_WAIT_MASK;
		val |= (cnt << EMC_MRS_WAIT_CNT_LONG_WAIT_SHIFT)
			& EMC_MRS_WAIT_CNT_LONG_WAIT_MASK;

		ग_लिखोl(val, emc->regs + EMC_MRS_WAIT_CNT);
	पूर्ण

	val = timing->emc_cfg_2;
	val &= ~EMC_CFG_2_DIS_STP_OB_CLK_DURING_NON_WR;
	emc_ccfअगरo_ग_लिखोl(emc, val, EMC_CFG_2);

	/* DDR3: Turn off DLL and enter self-refresh */
	अगर (emc->dram_type == DRAM_TYPE_DDR3 && dll_change == DLL_CHANGE_OFF)
		emc_ccfअगरo_ग_लिखोl(emc, timing->emc_mode_1, EMC_EMRS);

	/* Disable refresh controller */
	emc_ccfअगरo_ग_लिखोl(emc, EMC_REFCTRL_DEV_SEL(emc->dram_num),
			  EMC_REFCTRL);
	अगर (emc->dram_type == DRAM_TYPE_DDR3)
		emc_ccfअगरo_ग_लिखोl(emc, EMC_DRAM_DEV_SEL(emc->dram_num) |
				       EMC_SELF_REF_CMD_ENABLED,
				  EMC_SELF_REF);

	/* Flow control marker */
	emc_ccfअगरo_ग_लिखोl(emc, 1, EMC_STALL_THEN_EXE_AFTER_CLKCHANGE);

	/* DDR3: Exit self-refresh */
	अगर (emc->dram_type == DRAM_TYPE_DDR3)
		emc_ccfअगरo_ग_लिखोl(emc, EMC_DRAM_DEV_SEL(emc->dram_num),
				  EMC_SELF_REF);
	emc_ccfअगरo_ग_लिखोl(emc, EMC_REFCTRL_DEV_SEL(emc->dram_num) |
			       EMC_REFCTRL_ENABLE,
			  EMC_REFCTRL);

	/* Set DRAM mode रेजिस्टरs */
	अगर (emc->dram_type == DRAM_TYPE_DDR3) अणु
		अगर (timing->emc_mode_1 != last->emc_mode_1)
			emc_ccfअगरo_ग_लिखोl(emc, timing->emc_mode_1, EMC_EMRS);
		अगर (timing->emc_mode_2 != last->emc_mode_2)
			emc_ccfअगरo_ग_लिखोl(emc, timing->emc_mode_2, EMC_EMRS2);

		अगर ((timing->emc_mode_reset != last->emc_mode_reset) ||
		    dll_change == DLL_CHANGE_ON) अणु
			val = timing->emc_mode_reset;
			अगर (dll_change == DLL_CHANGE_ON) अणु
				val |= EMC_MODE_SET_DLL_RESET;
				val |= EMC_MODE_SET_LONG_CNT;
			पूर्ण अन्यथा अणु
				val &= ~EMC_MODE_SET_DLL_RESET;
			पूर्ण
			emc_ccfअगरo_ग_लिखोl(emc, val, EMC_MRS);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (timing->emc_mode_2 != last->emc_mode_2)
			emc_ccfअगरo_ग_लिखोl(emc, timing->emc_mode_2, EMC_MRW2);
		अगर (timing->emc_mode_1 != last->emc_mode_1)
			emc_ccfअगरo_ग_लिखोl(emc, timing->emc_mode_1, EMC_MRW);
		अगर (timing->emc_mode_4 != last->emc_mode_4)
			emc_ccfअगरo_ग_लिखोl(emc, timing->emc_mode_4, EMC_MRW4);
	पूर्ण

	/*  Issue ZCAL command अगर turning ZCAL on */
	अगर (timing->emc_zcal_पूर्णांकerval != 0 && last->emc_zcal_पूर्णांकerval == 0) अणु
		emc_ccfअगरo_ग_लिखोl(emc, EMC_ZQ_CAL_LONG_CMD_DEV0, EMC_ZQ_CAL);
		अगर (emc->dram_num > 1)
			emc_ccfअगरo_ग_लिखोl(emc, EMC_ZQ_CAL_LONG_CMD_DEV1,
					  EMC_ZQ_CAL);
	पूर्ण

	/*  Write to RO रेजिस्टर to हटाओ stall after change */
	emc_ccfअगरo_ग_लिखोl(emc, 0, EMC_CCFIFO_STATUS);

	अगर (timing->emc_cfg_2 & EMC_CFG_2_DIS_STP_OB_CLK_DURING_NON_WR)
		emc_ccfअगरo_ग_लिखोl(emc, timing->emc_cfg_2, EMC_CFG_2);

	/* Disable AUTO_CAL क्रम घड़ी change */
	emc_seq_disable_स्वतः_cal(emc);

	/* Read रेजिस्टर to रुको until programming has settled */
	पढ़ोl(emc->regs + EMC_INTSTATUS);

	वापस 0;
पूर्ण

अटल व्योम tegra_emc_complete_timing_change(काष्ठा tegra_emc *emc,
					     अचिन्हित दीर्घ rate)
अणु
	काष्ठा emc_timing *timing = tegra_emc_find_timing(emc, rate);
	काष्ठा emc_timing *last = &emc->last_timing;
	u32 val;

	अगर (!timing)
		वापस;

	/* Wait until the state machine has settled */
	emc_seq_रुको_clkchange(emc);

	/* Restore AUTO_CAL */
	अगर (timing->emc_ctt_term_ctrl != last->emc_ctt_term_ctrl)
		ग_लिखोl(timing->emc_स्वतः_cal_पूर्णांकerval,
		       emc->regs + EMC_AUTO_CAL_INTERVAL);

	/* Restore dynamic self-refresh */
	अगर (timing->emc_cfg & EMC_CFG_PWR_MASK)
		ग_लिखोl(timing->emc_cfg, emc->regs + EMC_CFG);

	/* Set ZCAL रुको count */
	ग_लिखोl(timing->emc_zcal_cnt_दीर्घ, emc->regs + EMC_ZCAL_WAIT_CNT);

	/* LPDDR3: Turn off BGBIAS अगर low frequency */
	अगर (emc->dram_type == DRAM_TYPE_LPDDR3 &&
	    timing->emc_bgbias_ctl0 &
	      EMC_BGBIAS_CTL0_BIAS0_DSC_E_PWRD_IBIAS_RX) अणु
		val = timing->emc_bgbias_ctl0;
		val |= EMC_BGBIAS_CTL0_BIAS0_DSC_E_PWRD_IBIAS_VTTGEN;
		val |= EMC_BGBIAS_CTL0_BIAS0_DSC_E_PWRD;
		ग_लिखोl(val, emc->regs + EMC_BGBIAS_CTL0);
	पूर्ण अन्यथा अणु
		अगर (emc->dram_type == DRAM_TYPE_DDR3 &&
		    पढ़ोl(emc->regs + EMC_BGBIAS_CTL0) !=
		      timing->emc_bgbias_ctl0) अणु
			ग_लिखोl(timing->emc_bgbias_ctl0,
			       emc->regs + EMC_BGBIAS_CTL0);
		पूर्ण

		ग_लिखोl(timing->emc_स्वतः_cal_पूर्णांकerval,
		       emc->regs + EMC_AUTO_CAL_INTERVAL);
	पूर्ण

	/* Wait क्रम timing to settle */
	udelay(2);

	/* Reprogram SEL_DPD_CTRL */
	ग_लिखोl(timing->emc_sel_dpd_ctrl, emc->regs + EMC_SEL_DPD_CTRL);
	emc_seq_update_timing(emc);

	emc->last_timing = *timing;
पूर्ण

/* Initialization and deinitialization */

अटल व्योम emc_पढ़ो_current_timing(काष्ठा tegra_emc *emc,
				    काष्ठा emc_timing *timing)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(emc_burst_regs); ++i)
		timing->emc_burst_data[i] =
			पढ़ोl(emc->regs + emc_burst_regs[i]);

	timing->emc_cfg = पढ़ोl(emc->regs + EMC_CFG);

	timing->emc_स्वतः_cal_पूर्णांकerval = 0;
	timing->emc_zcal_cnt_दीर्घ = 0;
	timing->emc_mode_1 = 0;
	timing->emc_mode_2 = 0;
	timing->emc_mode_4 = 0;
	timing->emc_mode_reset = 0;
पूर्ण

अटल पूर्णांक emc_init(काष्ठा tegra_emc *emc)
अणु
	emc->dram_type = पढ़ोl(emc->regs + EMC_FBIO_CFG5);

	अगर (emc->dram_type & EMC_FBIO_CFG5_DRAM_WIDTH_X64)
		emc->dram_bus_width = 64;
	अन्यथा
		emc->dram_bus_width = 32;

	dev_info_once(emc->dev, "%ubit DRAM bus\n", emc->dram_bus_width);

	emc->dram_type &= EMC_FBIO_CFG5_DRAM_TYPE_MASK;
	emc->dram_type >>= EMC_FBIO_CFG5_DRAM_TYPE_SHIFT;

	emc->dram_num = tegra_mc_get_emem_device_count(emc->mc);

	emc_पढ़ो_current_timing(emc, &emc->last_timing);

	वापस 0;
पूर्ण

अटल पूर्णांक load_one_timing_from_dt(काष्ठा tegra_emc *emc,
				   काष्ठा emc_timing *timing,
				   काष्ठा device_node *node)
अणु
	u32 value;
	पूर्णांक err;

	err = of_property_पढ़ो_u32(node, "clock-frequency", &value);
	अगर (err) अणु
		dev_err(emc->dev, "timing %pOFn: failed to read rate: %d\n",
			node, err);
		वापस err;
	पूर्ण

	timing->rate = value;

	err = of_property_पढ़ो_u32_array(node, "nvidia,emc-configuration",
					 timing->emc_burst_data,
					 ARRAY_SIZE(timing->emc_burst_data));
	अगर (err) अणु
		dev_err(emc->dev,
			"timing %pOFn: failed to read emc burst data: %d\n",
			node, err);
		वापस err;
	पूर्ण

#घोषणा EMC_READ_PROP(prop, dtprop) अणु \
	err = of_property_पढ़ो_u32(node, dtprop, &timing->prop); \
	अगर (err) अणु \
		dev_err(emc->dev, "timing %pOFn: failed to read " #prop ": %d\n", \
			node, err); \
		वापस err; \
	पूर्ण \
पूर्ण

	EMC_READ_PROP(emc_स्वतः_cal_config, "nvidia,emc-auto-cal-config")
	EMC_READ_PROP(emc_स्वतः_cal_config2, "nvidia,emc-auto-cal-config2")
	EMC_READ_PROP(emc_स्वतः_cal_config3, "nvidia,emc-auto-cal-config3")
	EMC_READ_PROP(emc_स्वतः_cal_पूर्णांकerval, "nvidia,emc-auto-cal-interval")
	EMC_READ_PROP(emc_bgbias_ctl0, "nvidia,emc-bgbias-ctl0")
	EMC_READ_PROP(emc_cfg, "nvidia,emc-cfg")
	EMC_READ_PROP(emc_cfg_2, "nvidia,emc-cfg-2")
	EMC_READ_PROP(emc_ctt_term_ctrl, "nvidia,emc-ctt-term-ctrl")
	EMC_READ_PROP(emc_mode_1, "nvidia,emc-mode-1")
	EMC_READ_PROP(emc_mode_2, "nvidia,emc-mode-2")
	EMC_READ_PROP(emc_mode_4, "nvidia,emc-mode-4")
	EMC_READ_PROP(emc_mode_reset, "nvidia,emc-mode-reset")
	EMC_READ_PROP(emc_mrs_रुको_cnt, "nvidia,emc-mrs-wait-cnt")
	EMC_READ_PROP(emc_sel_dpd_ctrl, "nvidia,emc-sel-dpd-ctrl")
	EMC_READ_PROP(emc_xm2dqspadctrl2, "nvidia,emc-xm2dqspadctrl2")
	EMC_READ_PROP(emc_zcal_cnt_दीर्घ, "nvidia,emc-zcal-cnt-long")
	EMC_READ_PROP(emc_zcal_पूर्णांकerval, "nvidia,emc-zcal-interval")

#अघोषित EMC_READ_PROP

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_timings(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	स्थिर काष्ठा emc_timing *a = _a;
	स्थिर काष्ठा emc_timing *b = _b;

	अगर (a->rate < b->rate)
		वापस -1;
	अन्यथा अगर (a->rate == b->rate)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक tegra_emc_load_timings_from_dt(काष्ठा tegra_emc *emc,
					  काष्ठा device_node *node)
अणु
	पूर्णांक child_count = of_get_child_count(node);
	काष्ठा device_node *child;
	काष्ठा emc_timing *timing;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक err;

	emc->timings = devm_kसुस्मृति(emc->dev, child_count, माप(*timing),
				    GFP_KERNEL);
	अगर (!emc->timings)
		वापस -ENOMEM;

	emc->num_timings = child_count;

	क्रम_each_child_of_node(node, child) अणु
		timing = &emc->timings[i++];

		err = load_one_timing_from_dt(emc, timing, child);
		अगर (err) अणु
			of_node_put(child);
			वापस err;
		पूर्ण
	पूर्ण

	sort(emc->timings, emc->num_timings, माप(*timing), cmp_timings,
	     शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_emc_of_match[] = अणु
	अणु .compatible = "nvidia,tegra124-emc" पूर्ण,
	अणु .compatible = "nvidia,tegra132-emc" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_emc_of_match);

अटल काष्ठा device_node *
tegra_emc_find_node_by_ram_code(काष्ठा device_node *node, u32 ram_code)
अणु
	काष्ठा device_node *np;
	पूर्णांक err;

	क्रम_each_child_of_node(node, np) अणु
		u32 value;

		err = of_property_पढ़ो_u32(np, "nvidia,ram-code", &value);
		अगर (err || (value != ram_code))
			जारी;

		वापस np;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम tegra_emc_rate_requests_init(काष्ठा tegra_emc *emc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < EMC_RATE_TYPE_MAX; i++) अणु
		emc->requested_rate[i].min_rate = 0;
		emc->requested_rate[i].max_rate = अच_दीर्घ_उच्च;
	पूर्ण
पूर्ण

अटल पूर्णांक emc_request_rate(काष्ठा tegra_emc *emc,
			    अचिन्हित दीर्घ new_min_rate,
			    अचिन्हित दीर्घ new_max_rate,
			    क्रमागत emc_rate_request_type type)
अणु
	काष्ठा emc_rate_request *req = emc->requested_rate;
	अचिन्हित दीर्घ min_rate = 0, max_rate = अच_दीर्घ_उच्च;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	/* select minimum and maximum rates among the requested rates */
	क्रम (i = 0; i < EMC_RATE_TYPE_MAX; i++, req++) अणु
		अगर (i == type) अणु
			min_rate = max(new_min_rate, min_rate);
			max_rate = min(new_max_rate, max_rate);
		पूर्ण अन्यथा अणु
			min_rate = max(req->min_rate, min_rate);
			max_rate = min(req->max_rate, max_rate);
		पूर्ण
	पूर्ण

	अगर (min_rate > max_rate) अणु
		dev_err_ratelimited(emc->dev, "%s: type %u: out of range: %lu %lu\n",
				    __func__, type, min_rate, max_rate);
		वापस -दुस्फल;
	पूर्ण

	/*
	 * EMC rate-changes should go via OPP API because it manages voltage
	 * changes.
	 */
	err = dev_pm_opp_set_rate(emc->dev, min_rate);
	अगर (err)
		वापस err;

	emc->requested_rate[type].min_rate = new_min_rate;
	emc->requested_rate[type].max_rate = new_max_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक emc_set_min_rate(काष्ठा tegra_emc *emc, अचिन्हित दीर्घ rate,
			    क्रमागत emc_rate_request_type type)
अणु
	काष्ठा emc_rate_request *req = &emc->requested_rate[type];
	पूर्णांक ret;

	mutex_lock(&emc->rate_lock);
	ret = emc_request_rate(emc, rate, req->max_rate, type);
	mutex_unlock(&emc->rate_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक emc_set_max_rate(काष्ठा tegra_emc *emc, अचिन्हित दीर्घ rate,
			    क्रमागत emc_rate_request_type type)
अणु
	काष्ठा emc_rate_request *req = &emc->requested_rate[type];
	पूर्णांक ret;

	mutex_lock(&emc->rate_lock);
	ret = emc_request_rate(emc, req->min_rate, rate, type);
	mutex_unlock(&emc->rate_lock);

	वापस ret;
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

अटल bool tegra_emc_validate_rate(काष्ठा tegra_emc *emc, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < emc->num_timings; i++)
		अगर (rate == emc->timings[i].rate)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक tegra_emc_debug_available_rates_show(काष्ठा seq_file *s,
						व्योम *data)
अणु
	काष्ठा tegra_emc *emc = s->निजी;
	स्थिर अक्षर *prefix = "";
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		seq_म_लिखो(s, "%s%lu", prefix, emc->timings[i].rate);
		prefix = " ";
	पूर्ण

	seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(tegra_emc_debug_available_rates);

अटल पूर्णांक tegra_emc_debug_min_rate_get(व्योम *data, u64 *rate)
अणु
	काष्ठा tegra_emc *emc = data;

	*rate = emc->debugfs.min_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_debug_min_rate_set(व्योम *data, u64 rate)
अणु
	काष्ठा tegra_emc *emc = data;
	पूर्णांक err;

	अगर (!tegra_emc_validate_rate(emc, rate))
		वापस -EINVAL;

	err = emc_set_min_rate(emc, rate, EMC_RATE_DEBUG);
	अगर (err < 0)
		वापस err;

	emc->debugfs.min_rate = rate;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(tegra_emc_debug_min_rate_fops,
			tegra_emc_debug_min_rate_get,
			tegra_emc_debug_min_rate_set, "%llu\n");

अटल पूर्णांक tegra_emc_debug_max_rate_get(व्योम *data, u64 *rate)
अणु
	काष्ठा tegra_emc *emc = data;

	*rate = emc->debugfs.max_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_debug_max_rate_set(व्योम *data, u64 rate)
अणु
	काष्ठा tegra_emc *emc = data;
	पूर्णांक err;

	अगर (!tegra_emc_validate_rate(emc, rate))
		वापस -EINVAL;

	err = emc_set_max_rate(emc, rate, EMC_RATE_DEBUG);
	अगर (err < 0)
		वापस err;

	emc->debugfs.max_rate = rate;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(tegra_emc_debug_max_rate_fops,
			tegra_emc_debug_max_rate_get,
			tegra_emc_debug_max_rate_set, "%llu\n");

अटल व्योम emc_debugfs_init(काष्ठा device *dev, काष्ठा tegra_emc *emc)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	emc->debugfs.min_rate = अच_दीर्घ_उच्च;
	emc->debugfs.max_rate = 0;

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		अगर (emc->timings[i].rate < emc->debugfs.min_rate)
			emc->debugfs.min_rate = emc->timings[i].rate;

		अगर (emc->timings[i].rate > emc->debugfs.max_rate)
			emc->debugfs.max_rate = emc->timings[i].rate;
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
			    &tegra_emc_debug_available_rates_fops);
	debugfs_create_file("min_rate", 0644, emc->debugfs.root,
			    emc, &tegra_emc_debug_min_rate_fops);
	debugfs_create_file("max_rate", 0644, emc->debugfs.root,
			    emc, &tegra_emc_debug_max_rate_fops);
पूर्ण

अटल अंतरभूत काष्ठा tegra_emc *
to_tegra_emc_provider(काष्ठा icc_provider *provider)
अणु
	वापस container_of(provider, काष्ठा tegra_emc, provider);
पूर्ण

अटल काष्ठा icc_node_data *
emc_of_icc_xlate_extended(काष्ठा of_phandle_args *spec, व्योम *data)
अणु
	काष्ठा icc_provider *provider = data;
	काष्ठा icc_node_data *ndata;
	काष्ठा icc_node *node;

	/* External Memory is the only possible ICC route */
	list_क्रम_each_entry(node, &provider->nodes, node_list) अणु
		अगर (node->id != TEGRA_ICC_EMEM)
			जारी;

		ndata = kzalloc(माप(*ndata), GFP_KERNEL);
		अगर (!ndata)
			वापस ERR_PTR(-ENOMEM);

		/*
		 * SRC and DST nodes should have matching TAG in order to have
		 * it set by शेष क्रम a requested path.
		 */
		ndata->tag = TEGRA_MC_ICC_TAG_ISO;
		ndata->node = node;

		वापस ndata;
	पूर्ण

	वापस ERR_PTR(-EPROBE_DEFER);
पूर्ण

अटल पूर्णांक emc_icc_set(काष्ठा icc_node *src, काष्ठा icc_node *dst)
अणु
	काष्ठा tegra_emc *emc = to_tegra_emc_provider(dst->provider);
	अचिन्हित दीर्घ दीर्घ peak_bw = icc_units_to_bps(dst->peak_bw);
	अचिन्हित दीर्घ दीर्घ avg_bw = icc_units_to_bps(dst->avg_bw);
	अचिन्हित दीर्घ दीर्घ rate = max(avg_bw, peak_bw);
	अचिन्हित पूर्णांक dram_data_bus_width_bytes;
	स्थिर अचिन्हित पूर्णांक ddr = 2;
	पूर्णांक err;

	/*
	 * Tegra124 EMC runs on a घड़ी rate of SDRAM bus. This means that
	 * EMC घड़ी rate is twice smaller than the peak data rate because
	 * data is sampled on both EMC घड़ी edges.
	 */
	dram_data_bus_width_bytes = emc->dram_bus_width / 8;
	करो_भाग(rate, ddr * dram_data_bus_width_bytes);
	rate = min_t(u64, rate, U32_MAX);

	err = emc_set_min_rate(emc, rate, EMC_RATE_ICC);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_पूर्णांकerconnect_init(काष्ठा tegra_emc *emc)
अणु
	स्थिर काष्ठा tegra_mc_soc *soc = emc->mc->soc;
	काष्ठा icc_node *node;
	पूर्णांक err;

	emc->provider.dev = emc->dev;
	emc->provider.set = emc_icc_set;
	emc->provider.data = &emc->provider;
	emc->provider.aggregate = soc->icc_ops->aggregate;
	emc->provider.xlate_extended = emc_of_icc_xlate_extended;

	err = icc_provider_add(&emc->provider);
	अगर (err)
		जाओ err_msg;

	/* create External Memory Controller node */
	node = icc_node_create(TEGRA_ICC_EMC);
	अगर (IS_ERR(node)) अणु
		err = PTR_ERR(node);
		जाओ del_provider;
	पूर्ण

	node->name = "External Memory Controller";
	icc_node_add(node, &emc->provider);

	/* link External Memory Controller to External Memory (DRAM) */
	err = icc_link_create(node, TEGRA_ICC_EMEM);
	अगर (err)
		जाओ हटाओ_nodes;

	/* create External Memory node */
	node = icc_node_create(TEGRA_ICC_EMEM);
	अगर (IS_ERR(node)) अणु
		err = PTR_ERR(node);
		जाओ हटाओ_nodes;
	पूर्ण

	node->name = "External Memory (DRAM)";
	icc_node_add(node, &emc->provider);

	वापस 0;

हटाओ_nodes:
	icc_nodes_हटाओ(&emc->provider);
del_provider:
	icc_provider_del(&emc->provider);
err_msg:
	dev_err(emc->dev, "failed to initialize ICC: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_emc_opp_table_init(काष्ठा tegra_emc *emc)
अणु
	u32 hw_version = BIT(tegra_sku_info.soc_speeकरो_id);
	काष्ठा opp_table *hw_opp_table;
	पूर्णांक err;

	hw_opp_table = dev_pm_opp_set_supported_hw(emc->dev, &hw_version, 1);
	err = PTR_ERR_OR_ZERO(hw_opp_table);
	अगर (err) अणु
		dev_err(emc->dev, "failed to set OPP supported HW: %d\n", err);
		वापस err;
	पूर्ण

	err = dev_pm_opp_of_add_table(emc->dev);
	अगर (err) अणु
		अगर (err == -ENODEV)
			dev_err(emc->dev, "OPP table not found, please update your device tree\n");
		अन्यथा
			dev_err(emc->dev, "failed to add OPP table: %d\n", err);

		जाओ put_hw_table;
	पूर्ण

	dev_info_once(emc->dev, "OPP HW ver. 0x%x, current clock rate %lu MHz\n",
		      hw_version, clk_get_rate(emc->clk) / 1000000);

	/* first dummy rate-set initializes voltage state */
	err = dev_pm_opp_set_rate(emc->dev, clk_get_rate(emc->clk));
	अगर (err) अणु
		dev_err(emc->dev, "failed to initialize OPP clock: %d\n", err);
		जाओ हटाओ_table;
	पूर्ण

	वापस 0;

हटाओ_table:
	dev_pm_opp_of_हटाओ_table(emc->dev);
put_hw_table:
	dev_pm_opp_put_supported_hw(hw_opp_table);

	वापस err;
पूर्ण

अटल व्योम devm_tegra_emc_unset_callback(व्योम *data)
अणु
	tegra124_clk_set_emc_callbacks(शून्य, शून्य);
पूर्ण

अटल पूर्णांक tegra_emc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np;
	काष्ठा tegra_emc *emc;
	u32 ram_code;
	पूर्णांक err;

	emc = devm_kzalloc(&pdev->dev, माप(*emc), GFP_KERNEL);
	अगर (!emc)
		वापस -ENOMEM;

	mutex_init(&emc->rate_lock);
	emc->dev = &pdev->dev;

	emc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(emc->regs))
		वापस PTR_ERR(emc->regs);

	emc->mc = devm_tegra_memory_controller_get(&pdev->dev);
	अगर (IS_ERR(emc->mc))
		वापस PTR_ERR(emc->mc);

	ram_code = tegra_पढ़ो_ram_code();

	np = tegra_emc_find_node_by_ram_code(pdev->dev.of_node, ram_code);
	अगर (np) अणु
		err = tegra_emc_load_timings_from_dt(emc, np);
		of_node_put(np);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		dev_info_once(&pdev->dev,
			      "no memory timings for RAM code %u found in DT\n",
			      ram_code);
	पूर्ण

	err = emc_init(emc);
	अगर (err) अणु
		dev_err(&pdev->dev, "EMC initialization failed: %d\n", err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, emc);

	tegra124_clk_set_emc_callbacks(tegra_emc_prepare_timing_change,
				       tegra_emc_complete_timing_change);

	err = devm_add_action_or_reset(&pdev->dev, devm_tegra_emc_unset_callback,
				       शून्य);
	अगर (err)
		वापस err;

	emc->clk = devm_clk_get(&pdev->dev, "emc");
	अगर (IS_ERR(emc->clk)) अणु
		err = PTR_ERR(emc->clk);
		dev_err(&pdev->dev, "failed to get EMC clock: %d\n", err);
		वापस err;
	पूर्ण

	err = tegra_emc_opp_table_init(emc);
	अगर (err)
		वापस err;

	tegra_emc_rate_requests_init(emc);

	अगर (IS_ENABLED(CONFIG_DEBUG_FS))
		emc_debugfs_init(&pdev->dev, emc);

	tegra_emc_पूर्णांकerconnect_init(emc);

	/*
	 * Don't allow the kernel module to be unloaded. Unloading adds some
	 * extra complनिकासy which करोesn't really worth the efक्रमt in a हाल of
	 * this driver.
	 */
	try_module_get(THIS_MODULE);

	वापस 0;
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_emc_driver = अणु
	.probe = tegra_emc_probe,
	.driver = अणु
		.name = "tegra-emc",
		.of_match_table = tegra_emc_of_match,
		.suppress_bind_attrs = true,
		.sync_state = icc_sync_state,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_emc_driver);

MODULE_AUTHOR("Mikko Perttunen <mperttunen@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra124 EMC driver");
MODULE_LICENSE("GPL v2");
