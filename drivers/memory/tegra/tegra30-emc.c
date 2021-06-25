<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Tegra30 External Memory Controller driver
 *
 * Based on करोwnstream driver from NVIDIA and tegra124-emc.c
 * Copyright (C) 2011-2014 NVIDIA Corporation
 *
 * Author: Dmitry Osipenko <digetx@gmail.com>
 * Copyright (C) 2019 GRATE-DRIVER project
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>
#समावेश <linux/types.h>

#समावेश <soc/tegra/common.h>
#समावेश <soc/tegra/fuse.h>

#समावेश "mc.h"

#घोषणा EMC_INTSTATUS				0x000
#घोषणा EMC_INTMASK				0x004
#घोषणा EMC_DBG					0x008
#घोषणा EMC_CFG					0x00c
#घोषणा EMC_REFCTRL				0x020
#घोषणा EMC_TIMING_CONTROL			0x028
#घोषणा EMC_RC					0x02c
#घोषणा EMC_RFC					0x030
#घोषणा EMC_RAS					0x034
#घोषणा EMC_RP					0x038
#घोषणा EMC_R2W					0x03c
#घोषणा EMC_W2R					0x040
#घोषणा EMC_R2P					0x044
#घोषणा EMC_W2P					0x048
#घोषणा EMC_RD_RCD				0x04c
#घोषणा EMC_WR_RCD				0x050
#घोषणा EMC_RRD					0x054
#घोषणा EMC_REXT				0x058
#घोषणा EMC_WDV					0x05c
#घोषणा EMC_QUSE				0x060
#घोषणा EMC_QRST				0x064
#घोषणा EMC_QSAFE				0x068
#घोषणा EMC_RDV					0x06c
#घोषणा EMC_REFRESH				0x070
#घोषणा EMC_BURST_REFRESH_NUM			0x074
#घोषणा EMC_PDEX2WR				0x078
#घोषणा EMC_PDEX2RD				0x07c
#घोषणा EMC_PCHG2PDEN				0x080
#घोषणा EMC_ACT2PDEN				0x084
#घोषणा EMC_AR2PDEN				0x088
#घोषणा EMC_RW2PDEN				0x08c
#घोषणा EMC_TXSR				0x090
#घोषणा EMC_TCKE				0x094
#घोषणा EMC_TFAW				0x098
#घोषणा EMC_TRPAB				0x09c
#घोषणा EMC_TCLKSTABLE				0x0a0
#घोषणा EMC_TCLKSTOP				0x0a4
#घोषणा EMC_TREFBW				0x0a8
#घोषणा EMC_QUSE_EXTRA				0x0ac
#घोषणा EMC_ODT_WRITE				0x0b0
#घोषणा EMC_ODT_READ				0x0b4
#घोषणा EMC_WEXT				0x0b8
#घोषणा EMC_CTT					0x0bc
#घोषणा EMC_MRS_WAIT_CNT			0x0c8
#घोषणा EMC_MRS					0x0cc
#घोषणा EMC_EMRS				0x0d0
#घोषणा EMC_SELF_REF				0x0e0
#घोषणा EMC_MRW					0x0e8
#घोषणा EMC_XM2DQSPADCTRL3			0x0f8
#घोषणा EMC_FBIO_SPARE				0x100
#घोषणा EMC_FBIO_CFG5				0x104
#घोषणा EMC_FBIO_CFG6				0x114
#घोषणा EMC_CFG_RSV				0x120
#घोषणा EMC_AUTO_CAL_CONFIG			0x2a4
#घोषणा EMC_AUTO_CAL_INTERVAL			0x2a8
#घोषणा EMC_AUTO_CAL_STATUS			0x2ac
#घोषणा EMC_STATUS				0x2b4
#घोषणा EMC_CFG_2				0x2b8
#घोषणा EMC_CFG_DIG_DLL				0x2bc
#घोषणा EMC_CFG_DIG_DLL_PERIOD			0x2c0
#घोषणा EMC_CTT_DURATION			0x2d8
#घोषणा EMC_CTT_TERM_CTRL			0x2dc
#घोषणा EMC_ZCAL_INTERVAL			0x2e0
#घोषणा EMC_ZCAL_WAIT_CNT			0x2e4
#घोषणा EMC_ZQ_CAL				0x2ec
#घोषणा EMC_XM2CMDPADCTRL			0x2f0
#घोषणा EMC_XM2DQSPADCTRL2			0x2fc
#घोषणा EMC_XM2DQPADCTRL2			0x304
#घोषणा EMC_XM2CLKPADCTRL			0x308
#घोषणा EMC_XM2COMPPADCTRL			0x30c
#घोषणा EMC_XM2VTTGENPADCTRL			0x310
#घोषणा EMC_XM2VTTGENPADCTRL2			0x314
#घोषणा EMC_XM2QUSEPADCTRL			0x318
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
#घोषणा EMC_STALL_THEN_EXE_BEFORE_CLKCHANGE	0x3c8
#घोषणा EMC_STALL_THEN_EXE_AFTER_CLKCHANGE	0x3cc
#घोषणा EMC_UNSTALL_RW_AFTER_CLKCHANGE		0x3d0
#घोषणा EMC_SEL_DPD_CTRL			0x3d8
#घोषणा EMC_PRE_REFRESH_REQ_CNT			0x3dc
#घोषणा EMC_DYN_SELF_REF_CONTROL		0x3e0
#घोषणा EMC_TXSRDLL				0x3e4

#घोषणा EMC_STATUS_TIMING_UPDATE_STALLED	BIT(23)

#घोषणा EMC_MODE_SET_DLL_RESET			BIT(8)
#घोषणा EMC_MODE_SET_LONG_CNT			BIT(26)

#घोषणा EMC_SELF_REF_CMD_ENABLED		BIT(0)

#घोषणा DRAM_DEV_SEL_ALL			(0 << 30)
#घोषणा DRAM_DEV_SEL_0				(2 << 30)
#घोषणा DRAM_DEV_SEL_1				(1 << 30)
#घोषणा DRAM_BROADCAST(num) \
	((num) > 1 ? DRAM_DEV_SEL_ALL : DRAM_DEV_SEL_0)

#घोषणा EMC_ZQ_CAL_CMD				BIT(0)
#घोषणा EMC_ZQ_CAL_LONG				BIT(4)
#घोषणा EMC_ZQ_CAL_LONG_CMD_DEV0 \
	(DRAM_DEV_SEL_0 | EMC_ZQ_CAL_LONG | EMC_ZQ_CAL_CMD)
#घोषणा EMC_ZQ_CAL_LONG_CMD_DEV1 \
	(DRAM_DEV_SEL_1 | EMC_ZQ_CAL_LONG | EMC_ZQ_CAL_CMD)

#घोषणा EMC_DBG_READ_MUX_ASSEMBLY		BIT(0)
#घोषणा EMC_DBG_WRITE_MUX_ACTIVE		BIT(1)
#घोषणा EMC_DBG_FORCE_UPDATE			BIT(2)
#घोषणा EMC_DBG_CFG_PRIORITY			BIT(24)

#घोषणा EMC_CFG5_QUSE_MODE_SHIFT		13
#घोषणा EMC_CFG5_QUSE_MODE_MASK			(7 << EMC_CFG5_QUSE_MODE_SHIFT)

#घोषणा EMC_CFG5_QUSE_MODE_INTERNAL_LPBK	2
#घोषणा EMC_CFG5_QUSE_MODE_PULSE_INTERN		3

#घोषणा EMC_SEL_DPD_CTRL_QUSE_DPD_ENABLE	BIT(9)

#घोषणा EMC_XM2COMPPADCTRL_VREF_CAL_ENABLE	BIT(10)

#घोषणा EMC_XM2QUSEPADCTRL_IVREF_ENABLE		BIT(4)

#घोषणा EMC_XM2DQSPADCTRL2_VREF_ENABLE		BIT(5)
#घोषणा EMC_XM2DQSPADCTRL3_VREF_ENABLE		BIT(5)

#घोषणा EMC_AUTO_CAL_STATUS_ACTIVE		BIT(31)

#घोषणा	EMC_FBIO_CFG5_DRAM_TYPE_MASK		0x3

#घोषणा EMC_MRS_WAIT_CNT_SHORT_WAIT_MASK	0x3ff
#घोषणा EMC_MRS_WAIT_CNT_LONG_WAIT_SHIFT	16
#घोषणा EMC_MRS_WAIT_CNT_LONG_WAIT_MASK \
	(0x3ff << EMC_MRS_WAIT_CNT_LONG_WAIT_SHIFT)

#घोषणा EMC_REFCTRL_DEV_SEL_MASK		0x3
#घोषणा EMC_REFCTRL_ENABLE			BIT(31)
#घोषणा EMC_REFCTRL_ENABLE_ALL(num) \
	(((num) > 1 ? 0 : 2) | EMC_REFCTRL_ENABLE)
#घोषणा EMC_REFCTRL_DISABLE_ALL(num)		((num) > 1 ? 0 : 2)

#घोषणा EMC_CFG_PERIODIC_QRST			BIT(21)
#घोषणा EMC_CFG_DYN_SREF_ENABLE			BIT(28)

#घोषणा EMC_CLKCHANGE_REQ_ENABLE		BIT(0)
#घोषणा EMC_CLKCHANGE_PD_ENABLE			BIT(1)
#घोषणा EMC_CLKCHANGE_SR_ENABLE			BIT(2)

#घोषणा EMC_TIMING_UPDATE			BIT(0)

#घोषणा EMC_REFRESH_OVERFLOW_INT		BIT(3)
#घोषणा EMC_CLKCHANGE_COMPLETE_INT		BIT(4)

क्रमागत emc_dram_type अणु
	DRAM_TYPE_DDR3,
	DRAM_TYPE_DDR1,
	DRAM_TYPE_LPDDR2,
	DRAM_TYPE_DDR2,
पूर्ण;

क्रमागत emc_dll_change अणु
	DLL_CHANGE_NONE,
	DLL_CHANGE_ON,
	DLL_CHANGE_OFF
पूर्ण;

अटल स्थिर u16 emc_timing_रेजिस्टरs[] = अणु
	[0] = EMC_RC,
	[1] = EMC_RFC,
	[2] = EMC_RAS,
	[3] = EMC_RP,
	[4] = EMC_R2W,
	[5] = EMC_W2R,
	[6] = EMC_R2P,
	[7] = EMC_W2P,
	[8] = EMC_RD_RCD,
	[9] = EMC_WR_RCD,
	[10] = EMC_RRD,
	[11] = EMC_REXT,
	[12] = EMC_WEXT,
	[13] = EMC_WDV,
	[14] = EMC_QUSE,
	[15] = EMC_QRST,
	[16] = EMC_QSAFE,
	[17] = EMC_RDV,
	[18] = EMC_REFRESH,
	[19] = EMC_BURST_REFRESH_NUM,
	[20] = EMC_PRE_REFRESH_REQ_CNT,
	[21] = EMC_PDEX2WR,
	[22] = EMC_PDEX2RD,
	[23] = EMC_PCHG2PDEN,
	[24] = EMC_ACT2PDEN,
	[25] = EMC_AR2PDEN,
	[26] = EMC_RW2PDEN,
	[27] = EMC_TXSR,
	[28] = EMC_TXSRDLL,
	[29] = EMC_TCKE,
	[30] = EMC_TFAW,
	[31] = EMC_TRPAB,
	[32] = EMC_TCLKSTABLE,
	[33] = EMC_TCLKSTOP,
	[34] = EMC_TREFBW,
	[35] = EMC_QUSE_EXTRA,
	[36] = EMC_FBIO_CFG6,
	[37] = EMC_ODT_WRITE,
	[38] = EMC_ODT_READ,
	[39] = EMC_FBIO_CFG5,
	[40] = EMC_CFG_DIG_DLL,
	[41] = EMC_CFG_DIG_DLL_PERIOD,
	[42] = EMC_DLL_XFORM_DQS0,
	[43] = EMC_DLL_XFORM_DQS1,
	[44] = EMC_DLL_XFORM_DQS2,
	[45] = EMC_DLL_XFORM_DQS3,
	[46] = EMC_DLL_XFORM_DQS4,
	[47] = EMC_DLL_XFORM_DQS5,
	[48] = EMC_DLL_XFORM_DQS6,
	[49] = EMC_DLL_XFORM_DQS7,
	[50] = EMC_DLL_XFORM_QUSE0,
	[51] = EMC_DLL_XFORM_QUSE1,
	[52] = EMC_DLL_XFORM_QUSE2,
	[53] = EMC_DLL_XFORM_QUSE3,
	[54] = EMC_DLL_XFORM_QUSE4,
	[55] = EMC_DLL_XFORM_QUSE5,
	[56] = EMC_DLL_XFORM_QUSE6,
	[57] = EMC_DLL_XFORM_QUSE7,
	[58] = EMC_DLI_TRIM_TXDQS0,
	[59] = EMC_DLI_TRIM_TXDQS1,
	[60] = EMC_DLI_TRIM_TXDQS2,
	[61] = EMC_DLI_TRIM_TXDQS3,
	[62] = EMC_DLI_TRIM_TXDQS4,
	[63] = EMC_DLI_TRIM_TXDQS5,
	[64] = EMC_DLI_TRIM_TXDQS6,
	[65] = EMC_DLI_TRIM_TXDQS7,
	[66] = EMC_DLL_XFORM_DQ0,
	[67] = EMC_DLL_XFORM_DQ1,
	[68] = EMC_DLL_XFORM_DQ2,
	[69] = EMC_DLL_XFORM_DQ3,
	[70] = EMC_XM2CMDPADCTRL,
	[71] = EMC_XM2DQSPADCTRL2,
	[72] = EMC_XM2DQPADCTRL2,
	[73] = EMC_XM2CLKPADCTRL,
	[74] = EMC_XM2COMPPADCTRL,
	[75] = EMC_XM2VTTGENPADCTRL,
	[76] = EMC_XM2VTTGENPADCTRL2,
	[77] = EMC_XM2QUSEPADCTRL,
	[78] = EMC_XM2DQSPADCTRL3,
	[79] = EMC_CTT_TERM_CTRL,
	[80] = EMC_ZCAL_INTERVAL,
	[81] = EMC_ZCAL_WAIT_CNT,
	[82] = EMC_MRS_WAIT_CNT,
	[83] = EMC_AUTO_CAL_CONFIG,
	[84] = EMC_CTT,
	[85] = EMC_CTT_DURATION,
	[86] = EMC_DYN_SELF_REF_CONTROL,
	[87] = EMC_FBIO_SPARE,
	[88] = EMC_CFG_RSV,
पूर्ण;

काष्ठा emc_timing अणु
	अचिन्हित दीर्घ rate;

	u32 data[ARRAY_SIZE(emc_timing_रेजिस्टरs)];

	u32 emc_स्वतः_cal_पूर्णांकerval;
	u32 emc_mode_1;
	u32 emc_mode_2;
	u32 emc_mode_reset;
	u32 emc_zcal_cnt_दीर्घ;
	bool emc_cfg_periodic_qrst;
	bool emc_cfg_dyn_self_ref;
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
	काष्ठा icc_provider provider;
	काष्ठा notअगरier_block clk_nb;
	काष्ठा clk *clk;
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक irq;
	bool bad_state;

	काष्ठा emc_timing *new_timing;
	काष्ठा emc_timing *timings;
	अचिन्हित पूर्णांक num_timings;

	u32 mc_override;
	u32 emc_cfg;

	u32 emc_mode_1;
	u32 emc_mode_2;
	u32 emc_mode_reset;

	bool vref_cal_toggle : 1;
	bool zcal_दीर्घ : 1;
	bool dll_on : 1;

	काष्ठा अणु
		काष्ठा dentry *root;
		अचिन्हित दीर्घ min_rate;
		अचिन्हित दीर्घ max_rate;
	पूर्ण debugfs;

	/*
	 * There are multiple sources in the EMC driver which could request
	 * a min/max घड़ी rate, these rates are contained in this array.
	 */
	काष्ठा emc_rate_request requested_rate[EMC_RATE_TYPE_MAX];

	/* protect shared rate-change code path */
	काष्ठा mutex rate_lock;
पूर्ण;

अटल पूर्णांक emc_seq_update_timing(काष्ठा tegra_emc *emc)
अणु
	u32 val;
	पूर्णांक err;

	ग_लिखोl_relaxed(EMC_TIMING_UPDATE, emc->regs + EMC_TIMING_CONTROL);

	err = पढ़ोl_relaxed_poll_समयout_atomic(emc->regs + EMC_STATUS, val,
				!(val & EMC_STATUS_TIMING_UPDATE_STALLED),
				1, 200);
	अगर (err) अणु
		dev_err(emc->dev, "failed to update timing: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t tegra_emc_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_emc *emc = data;
	u32 पूर्णांकmask = EMC_REFRESH_OVERFLOW_INT;
	u32 status;

	status = पढ़ोl_relaxed(emc->regs + EMC_INTSTATUS) & पूर्णांकmask;
	अगर (!status)
		वापस IRQ_NONE;

	/* notअगरy about HW problem */
	अगर (status & EMC_REFRESH_OVERFLOW_INT)
		dev_err_ratelimited(emc->dev,
				    "refresh request overflow timeout\n");

	/* clear पूर्णांकerrupts */
	ग_लिखोl_relaxed(status, emc->regs + EMC_INTSTATUS);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा emc_timing *emc_find_timing(काष्ठा tegra_emc *emc,
					  अचिन्हित दीर्घ rate)
अणु
	काष्ठा emc_timing *timing = शून्य;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		अगर (emc->timings[i].rate >= rate) अणु
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

अटल bool emc_dqs_preset(काष्ठा tegra_emc *emc, काष्ठा emc_timing *timing,
			   bool *schmitt_to_vref)
अणु
	bool preset = false;
	u32 val;

	अगर (timing->data[71] & EMC_XM2DQSPADCTRL2_VREF_ENABLE) अणु
		val = पढ़ोl_relaxed(emc->regs + EMC_XM2DQSPADCTRL2);

		अगर (!(val & EMC_XM2DQSPADCTRL2_VREF_ENABLE)) अणु
			val |= EMC_XM2DQSPADCTRL2_VREF_ENABLE;
			ग_लिखोl_relaxed(val, emc->regs + EMC_XM2DQSPADCTRL2);

			preset = true;
		पूर्ण
	पूर्ण

	अगर (timing->data[78] & EMC_XM2DQSPADCTRL3_VREF_ENABLE) अणु
		val = पढ़ोl_relaxed(emc->regs + EMC_XM2DQSPADCTRL3);

		अगर (!(val & EMC_XM2DQSPADCTRL3_VREF_ENABLE)) अणु
			val |= EMC_XM2DQSPADCTRL3_VREF_ENABLE;
			ग_लिखोl_relaxed(val, emc->regs + EMC_XM2DQSPADCTRL3);

			preset = true;
		पूर्ण
	पूर्ण

	अगर (timing->data[77] & EMC_XM2QUSEPADCTRL_IVREF_ENABLE) अणु
		val = पढ़ोl_relaxed(emc->regs + EMC_XM2QUSEPADCTRL);

		अगर (!(val & EMC_XM2QUSEPADCTRL_IVREF_ENABLE)) अणु
			val |= EMC_XM2QUSEPADCTRL_IVREF_ENABLE;
			ग_लिखोl_relaxed(val, emc->regs + EMC_XM2QUSEPADCTRL);

			*schmitt_to_vref = true;
			preset = true;
		पूर्ण
	पूर्ण

	वापस preset;
पूर्ण

अटल पूर्णांक emc_prepare_mc_clk_cfg(काष्ठा tegra_emc *emc, अचिन्हित दीर्घ rate)
अणु
	काष्ठा tegra_mc *mc = emc->mc;
	अचिन्हित पूर्णांक misc0_index = 16;
	अचिन्हित पूर्णांक i;
	bool same;

	क्रम (i = 0; i < mc->num_timings; i++) अणु
		अगर (mc->timings[i].rate != rate)
			जारी;

		अगर (mc->timings[i].emem_data[misc0_index] & BIT(27))
			same = true;
		अन्यथा
			same = false;

		वापस tegra20_clk_prepare_emc_mc_same_freq(emc->clk, same);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक emc_prepare_timing_change(काष्ठा tegra_emc *emc, अचिन्हित दीर्घ rate)
अणु
	काष्ठा emc_timing *timing = emc_find_timing(emc, rate);
	क्रमागत emc_dll_change dll_change;
	क्रमागत emc_dram_type dram_type;
	bool schmitt_to_vref = false;
	अचिन्हित पूर्णांक pre_रुको = 0;
	bool qrst_used = false;
	अचिन्हित पूर्णांक dram_num;
	अचिन्हित पूर्णांक i;
	u32 fbio_cfg5;
	u32 emc_dbg;
	u32 val;
	पूर्णांक err;

	अगर (!timing || emc->bad_state)
		वापस -EINVAL;

	dev_dbg(emc->dev, "%s: using timing rate %lu for requested rate %lu\n",
		__func__, timing->rate, rate);

	emc->bad_state = true;

	err = emc_prepare_mc_clk_cfg(emc, rate);
	अगर (err) अणु
		dev_err(emc->dev, "mc clock preparation failed: %d\n", err);
		वापस err;
	पूर्ण

	emc->vref_cal_toggle = false;
	emc->mc_override = mc_पढ़ोl(emc->mc, MC_EMEM_ARB_OVERRIDE);
	emc->emc_cfg = पढ़ोl_relaxed(emc->regs + EMC_CFG);
	emc_dbg = पढ़ोl_relaxed(emc->regs + EMC_DBG);

	अगर (emc->dll_on == !!(timing->emc_mode_1 & 0x1))
		dll_change = DLL_CHANGE_NONE;
	अन्यथा अगर (timing->emc_mode_1 & 0x1)
		dll_change = DLL_CHANGE_ON;
	अन्यथा
		dll_change = DLL_CHANGE_OFF;

	emc->dll_on = !!(timing->emc_mode_1 & 0x1);

	अगर (timing->data[80] && !पढ़ोl_relaxed(emc->regs + EMC_ZCAL_INTERVAL))
		emc->zcal_दीर्घ = true;
	अन्यथा
		emc->zcal_दीर्घ = false;

	fbio_cfg5 = पढ़ोl_relaxed(emc->regs + EMC_FBIO_CFG5);
	dram_type = fbio_cfg5 & EMC_FBIO_CFG5_DRAM_TYPE_MASK;

	dram_num = tegra_mc_get_emem_device_count(emc->mc);

	/* disable dynamic self-refresh */
	अगर (emc->emc_cfg & EMC_CFG_DYN_SREF_ENABLE) अणु
		emc->emc_cfg &= ~EMC_CFG_DYN_SREF_ENABLE;
		ग_लिखोl_relaxed(emc->emc_cfg, emc->regs + EMC_CFG);

		pre_रुको = 5;
	पूर्ण

	/* update MC arbiter settings */
	val = mc_पढ़ोl(emc->mc, MC_EMEM_ARB_OUTSTANDING_REQ);
	अगर (!(val & MC_EMEM_ARB_OUTSTANDING_REQ_HOLDOFF_OVERRIDE) ||
	    ((val & MC_EMEM_ARB_OUTSTANDING_REQ_MAX_MASK) > 0x50)) अणु

		val = MC_EMEM_ARB_OUTSTANDING_REQ_LIMIT_ENABLE |
		      MC_EMEM_ARB_OUTSTANDING_REQ_HOLDOFF_OVERRIDE | 0x50;
		mc_ग_लिखोl(emc->mc, val, MC_EMEM_ARB_OUTSTANDING_REQ);
		mc_ग_लिखोl(emc->mc, MC_TIMING_UPDATE, MC_TIMING_CONTROL);
	पूर्ण

	अगर (emc->mc_override & MC_EMEM_ARB_OVERRIDE_EACK_MASK)
		mc_ग_लिखोl(emc->mc,
			  emc->mc_override & ~MC_EMEM_ARB_OVERRIDE_EACK_MASK,
			  MC_EMEM_ARB_OVERRIDE);

	/* check DQ/DQS VREF delay */
	अगर (emc_dqs_preset(emc, timing, &schmitt_to_vref)) अणु
		अगर (pre_रुको < 3)
			pre_रुको = 3;
	पूर्ण

	अगर (pre_रुको) अणु
		err = emc_seq_update_timing(emc);
		अगर (err)
			वापस err;

		udelay(pre_रुको);
	पूर्ण

	/* disable स्वतः-calibration अगर VREF mode is चयनing */
	अगर (timing->emc_स्वतः_cal_पूर्णांकerval) अणु
		val = पढ़ोl_relaxed(emc->regs + EMC_XM2COMPPADCTRL);
		val ^= timing->data[74];

		अगर (val & EMC_XM2COMPPADCTRL_VREF_CAL_ENABLE) अणु
			ग_लिखोl_relaxed(0, emc->regs + EMC_AUTO_CAL_INTERVAL);

			err = पढ़ोl_relaxed_poll_समयout_atomic(
				emc->regs + EMC_AUTO_CAL_STATUS, val,
				!(val & EMC_AUTO_CAL_STATUS_ACTIVE), 1, 300);
			अगर (err) अणु
				dev_err(emc->dev,
					"auto-cal finish timeout: %d\n", err);
				वापस err;
			पूर्ण

			emc->vref_cal_toggle = true;
		पूर्ण
	पूर्ण

	/* program shaकरोw रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(timing->data); i++) अणु
		/* EMC_XM2CLKPADCTRL should be programmed separately */
		अगर (i != 73)
			ग_लिखोl_relaxed(timing->data[i],
				       emc->regs + emc_timing_रेजिस्टरs[i]);
	पूर्ण

	err = tegra_mc_ग_लिखो_emem_configuration(emc->mc, timing->rate);
	अगर (err)
		वापस err;

	/* DDR3: predict MRS दीर्घ रुको count */
	अगर (dram_type == DRAM_TYPE_DDR3 && dll_change == DLL_CHANGE_ON) अणु
		u32 cnt = 512;

		अगर (emc->zcal_दीर्घ)
			cnt -= dram_num * 256;

		val = timing->data[82] & EMC_MRS_WAIT_CNT_SHORT_WAIT_MASK;
		अगर (cnt < val)
			cnt = val;

		val = timing->data[82] & ~EMC_MRS_WAIT_CNT_LONG_WAIT_MASK;
		val |= (cnt << EMC_MRS_WAIT_CNT_LONG_WAIT_SHIFT) &
			EMC_MRS_WAIT_CNT_LONG_WAIT_MASK;

		ग_लिखोl_relaxed(val, emc->regs + EMC_MRS_WAIT_CNT);
	पूर्ण

	/* this पढ़ो also completes the ग_लिखोs */
	val = पढ़ोl_relaxed(emc->regs + EMC_SEL_DPD_CTRL);

	अगर (!(val & EMC_SEL_DPD_CTRL_QUSE_DPD_ENABLE) && schmitt_to_vref) अणु
		u32 cur_mode, new_mode;

		cur_mode = fbio_cfg5 & EMC_CFG5_QUSE_MODE_MASK;
		cur_mode >>= EMC_CFG5_QUSE_MODE_SHIFT;

		new_mode = timing->data[39] & EMC_CFG5_QUSE_MODE_MASK;
		new_mode >>= EMC_CFG5_QUSE_MODE_SHIFT;

		अगर ((cur_mode != EMC_CFG5_QUSE_MODE_PULSE_INTERN &&
		     cur_mode != EMC_CFG5_QUSE_MODE_INTERNAL_LPBK) ||
		    (new_mode != EMC_CFG5_QUSE_MODE_PULSE_INTERN &&
		     new_mode != EMC_CFG5_QUSE_MODE_INTERNAL_LPBK))
			qrst_used = true;
	पूर्ण

	/* flow control marker 1 */
	ग_लिखोl_relaxed(0x1, emc->regs + EMC_STALL_THEN_EXE_BEFORE_CLKCHANGE);

	/* enable periodic reset */
	अगर (qrst_used) अणु
		ग_लिखोl_relaxed(emc_dbg | EMC_DBG_WRITE_MUX_ACTIVE,
			       emc->regs + EMC_DBG);
		ग_लिखोl_relaxed(emc->emc_cfg | EMC_CFG_PERIODIC_QRST,
			       emc->regs + EMC_CFG);
		ग_लिखोl_relaxed(emc_dbg, emc->regs + EMC_DBG);
	पूर्ण

	/* disable स्वतः-refresh to save समय after घड़ी change */
	ग_लिखोl_relaxed(EMC_REFCTRL_DISABLE_ALL(dram_num),
		       emc->regs + EMC_REFCTRL);

	/* turn off DLL and enter self-refresh on DDR3 */
	अगर (dram_type == DRAM_TYPE_DDR3) अणु
		अगर (dll_change == DLL_CHANGE_OFF)
			ग_लिखोl_relaxed(timing->emc_mode_1,
				       emc->regs + EMC_EMRS);

		ग_लिखोl_relaxed(DRAM_BROADCAST(dram_num) |
			       EMC_SELF_REF_CMD_ENABLED,
			       emc->regs + EMC_SELF_REF);
	पूर्ण

	/* flow control marker 2 */
	ग_लिखोl_relaxed(0x1, emc->regs + EMC_STALL_THEN_EXE_AFTER_CLKCHANGE);

	/* enable ग_लिखो-active MUX, update unshaकरोwed pad control */
	ग_लिखोl_relaxed(emc_dbg | EMC_DBG_WRITE_MUX_ACTIVE, emc->regs + EMC_DBG);
	ग_लिखोl_relaxed(timing->data[73], emc->regs + EMC_XM2CLKPADCTRL);

	/* restore periodic QRST and disable ग_लिखो-active MUX */
	val = !!(emc->emc_cfg & EMC_CFG_PERIODIC_QRST);
	अगर (qrst_used || timing->emc_cfg_periodic_qrst != val) अणु
		अगर (timing->emc_cfg_periodic_qrst)
			emc->emc_cfg |= EMC_CFG_PERIODIC_QRST;
		अन्यथा
			emc->emc_cfg &= ~EMC_CFG_PERIODIC_QRST;

		ग_लिखोl_relaxed(emc->emc_cfg, emc->regs + EMC_CFG);
	पूर्ण
	ग_लिखोl_relaxed(emc_dbg, emc->regs + EMC_DBG);

	/* निकास self-refresh on DDR3 */
	अगर (dram_type == DRAM_TYPE_DDR3)
		ग_लिखोl_relaxed(DRAM_BROADCAST(dram_num),
			       emc->regs + EMC_SELF_REF);

	/* set DRAM-mode रेजिस्टरs */
	अगर (dram_type == DRAM_TYPE_DDR3) अणु
		अगर (timing->emc_mode_1 != emc->emc_mode_1)
			ग_लिखोl_relaxed(timing->emc_mode_1,
				       emc->regs + EMC_EMRS);

		अगर (timing->emc_mode_2 != emc->emc_mode_2)
			ग_लिखोl_relaxed(timing->emc_mode_2,
				       emc->regs + EMC_EMRS);

		अगर (timing->emc_mode_reset != emc->emc_mode_reset ||
		    dll_change == DLL_CHANGE_ON) अणु
			val = timing->emc_mode_reset;
			अगर (dll_change == DLL_CHANGE_ON) अणु
				val |= EMC_MODE_SET_DLL_RESET;
				val |= EMC_MODE_SET_LONG_CNT;
			पूर्ण अन्यथा अणु
				val &= ~EMC_MODE_SET_DLL_RESET;
			पूर्ण
			ग_लिखोl_relaxed(val, emc->regs + EMC_MRS);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (timing->emc_mode_2 != emc->emc_mode_2)
			ग_लिखोl_relaxed(timing->emc_mode_2,
				       emc->regs + EMC_MRW);

		अगर (timing->emc_mode_1 != emc->emc_mode_1)
			ग_लिखोl_relaxed(timing->emc_mode_1,
				       emc->regs + EMC_MRW);
	पूर्ण

	emc->emc_mode_1 = timing->emc_mode_1;
	emc->emc_mode_2 = timing->emc_mode_2;
	emc->emc_mode_reset = timing->emc_mode_reset;

	/* issue ZCAL command अगर turning ZCAL on */
	अगर (emc->zcal_दीर्घ) अणु
		ग_लिखोl_relaxed(EMC_ZQ_CAL_LONG_CMD_DEV0,
			       emc->regs + EMC_ZQ_CAL);

		अगर (dram_num > 1)
			ग_लिखोl_relaxed(EMC_ZQ_CAL_LONG_CMD_DEV1,
				       emc->regs + EMC_ZQ_CAL);
	पूर्ण

	/* flow control marker 3 */
	ग_लिखोl_relaxed(0x1, emc->regs + EMC_UNSTALL_RW_AFTER_CLKCHANGE);

	/*
	 * Read and discard an arbitrary MC रेजिस्टर (Note: EMC रेजिस्टरs
	 * can't be used) to ensure the रेजिस्टर ग_लिखोs are completed.
	 */
	mc_पढ़ोl(emc->mc, MC_EMEM_ARB_OVERRIDE);

	वापस 0;
पूर्ण

अटल पूर्णांक emc_complete_timing_change(काष्ठा tegra_emc *emc,
				      अचिन्हित दीर्घ rate)
अणु
	काष्ठा emc_timing *timing = emc_find_timing(emc, rate);
	अचिन्हित पूर्णांक dram_num;
	पूर्णांक err;
	u32 v;

	err = पढ़ोl_relaxed_poll_समयout_atomic(emc->regs + EMC_INTSTATUS, v,
						v & EMC_CLKCHANGE_COMPLETE_INT,
						1, 100);
	अगर (err) अणु
		dev_err(emc->dev, "emc-car handshake timeout: %d\n", err);
		वापस err;
	पूर्ण

	/* re-enable स्वतः-refresh */
	dram_num = tegra_mc_get_emem_device_count(emc->mc);
	ग_लिखोl_relaxed(EMC_REFCTRL_ENABLE_ALL(dram_num),
		       emc->regs + EMC_REFCTRL);

	/* restore स्वतः-calibration */
	अगर (emc->vref_cal_toggle)
		ग_लिखोl_relaxed(timing->emc_स्वतः_cal_पूर्णांकerval,
			       emc->regs + EMC_AUTO_CAL_INTERVAL);

	/* restore dynamic self-refresh */
	अगर (timing->emc_cfg_dyn_self_ref) अणु
		emc->emc_cfg |= EMC_CFG_DYN_SREF_ENABLE;
		ग_लिखोl_relaxed(emc->emc_cfg, emc->regs + EMC_CFG);
	पूर्ण

	/* set number of घड़ीs to रुको after each ZQ command */
	अगर (emc->zcal_दीर्घ)
		ग_लिखोl_relaxed(timing->emc_zcal_cnt_दीर्घ,
			       emc->regs + EMC_ZCAL_WAIT_CNT);

	/* रुको क्रम ग_लिखोs to settle */
	udelay(2);

	/* update restored timing */
	err = emc_seq_update_timing(emc);
	अगर (!err)
		emc->bad_state = false;

	/* restore early ACK */
	mc_ग_लिखोl(emc->mc, emc->mc_override, MC_EMEM_ARB_OVERRIDE);

	वापस err;
पूर्ण

अटल पूर्णांक emc_unprepare_timing_change(काष्ठा tegra_emc *emc,
				       अचिन्हित दीर्घ rate)
अणु
	अगर (!emc->bad_state) अणु
		/* shouldn't ever happen in practice */
		dev_err(emc->dev, "timing configuration can't be reverted\n");
		emc->bad_state = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक emc_clk_change_notअगरy(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ msg, व्योम *data)
अणु
	काष्ठा tegra_emc *emc = container_of(nb, काष्ठा tegra_emc, clk_nb);
	काष्ठा clk_notअगरier_data *cnd = data;
	पूर्णांक err;

	चयन (msg) अणु
	हाल PRE_RATE_CHANGE:
		/*
		 * Disable पूर्णांकerrupt since पढ़ो accesses are prohibited after
		 * stalling.
		 */
		disable_irq(emc->irq);
		err = emc_prepare_timing_change(emc, cnd->new_rate);
		enable_irq(emc->irq);
		अवरोध;

	हाल ABORT_RATE_CHANGE:
		err = emc_unprepare_timing_change(emc, cnd->old_rate);
		अवरोध;

	हाल POST_RATE_CHANGE:
		err = emc_complete_timing_change(emc, cnd->new_rate);
		अवरोध;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक load_one_timing_from_dt(काष्ठा tegra_emc *emc,
				   काष्ठा emc_timing *timing,
				   काष्ठा device_node *node)
अणु
	u32 value;
	पूर्णांक err;

	err = of_property_पढ़ो_u32(node, "clock-frequency", &value);
	अगर (err) अणु
		dev_err(emc->dev, "timing %pOF: failed to read rate: %d\n",
			node, err);
		वापस err;
	पूर्ण

	timing->rate = value;

	err = of_property_पढ़ो_u32_array(node, "nvidia,emc-configuration",
					 timing->data,
					 ARRAY_SIZE(emc_timing_रेजिस्टरs));
	अगर (err) अणु
		dev_err(emc->dev,
			"timing %pOF: failed to read emc timing data: %d\n",
			node, err);
		वापस err;
	पूर्ण

#घोषणा EMC_READ_BOOL(prop, dtprop) \
	timing->prop = of_property_पढ़ो_bool(node, dtprop);

#घोषणा EMC_READ_U32(prop, dtprop) \
	err = of_property_पढ़ो_u32(node, dtprop, &timing->prop); \
	अगर (err) अणु \
		dev_err(emc->dev, \
			"timing %pOFn: failed to read " #prop ": %d\n", \
			node, err); \
		वापस err; \
	पूर्ण

	EMC_READ_U32(emc_स्वतः_cal_पूर्णांकerval, "nvidia,emc-auto-cal-interval")
	EMC_READ_U32(emc_mode_1, "nvidia,emc-mode-1")
	EMC_READ_U32(emc_mode_2, "nvidia,emc-mode-2")
	EMC_READ_U32(emc_mode_reset, "nvidia,emc-mode-reset")
	EMC_READ_U32(emc_zcal_cnt_दीर्घ, "nvidia,emc-zcal-cnt-long")
	EMC_READ_BOOL(emc_cfg_dyn_self_ref, "nvidia,emc-cfg-dyn-self-ref")
	EMC_READ_BOOL(emc_cfg_periodic_qrst, "nvidia,emc-cfg-periodic-qrst")

#अघोषित EMC_READ_U32
#अघोषित EMC_READ_BOOL

	dev_dbg(emc->dev, "%s: %pOF: rate %lu\n", __func__, node, timing->rate);

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_timings(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	स्थिर काष्ठा emc_timing *a = _a;
	स्थिर काष्ठा emc_timing *b = _b;

	अगर (a->rate < b->rate)
		वापस -1;

	अगर (a->rate > b->rate)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक emc_check_mc_timings(काष्ठा tegra_emc *emc)
अणु
	काष्ठा tegra_mc *mc = emc->mc;
	अचिन्हित पूर्णांक i;

	अगर (emc->num_timings != mc->num_timings) अणु
		dev_err(emc->dev, "emc/mc timings number mismatch: %u %u\n",
			emc->num_timings, mc->num_timings);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < mc->num_timings; i++) अणु
		अगर (emc->timings[i].rate != mc->timings[i].rate) अणु
			dev_err(emc->dev,
				"emc/mc timing rate mismatch: %lu %lu\n",
				emc->timings[i].rate, mc->timings[i].rate);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक emc_load_timings_from_dt(काष्ठा tegra_emc *emc,
				    काष्ठा device_node *node)
अणु
	काष्ठा device_node *child;
	काष्ठा emc_timing *timing;
	पूर्णांक child_count;
	पूर्णांक err;

	child_count = of_get_child_count(node);
	अगर (!child_count) अणु
		dev_err(emc->dev, "no memory timings in: %pOF\n", node);
		वापस -EINVAL;
	पूर्ण

	emc->timings = devm_kसुस्मृति(emc->dev, child_count, माप(*timing),
				    GFP_KERNEL);
	अगर (!emc->timings)
		वापस -ENOMEM;

	emc->num_timings = child_count;
	timing = emc->timings;

	क्रम_each_child_of_node(node, child) अणु
		err = load_one_timing_from_dt(emc, timing++, child);
		अगर (err) अणु
			of_node_put(child);
			वापस err;
		पूर्ण
	पूर्ण

	sort(emc->timings, emc->num_timings, माप(*timing), cmp_timings,
	     शून्य);

	err = emc_check_mc_timings(emc);
	अगर (err)
		वापस err;

	dev_info_once(emc->dev,
		      "got %u timings for RAM code %u (min %luMHz max %luMHz)\n",
		      emc->num_timings,
		      tegra_पढ़ो_ram_code(),
		      emc->timings[0].rate / 1000000,
		      emc->timings[emc->num_timings - 1].rate / 1000000);

	वापस 0;
पूर्ण

अटल काष्ठा device_node *emc_find_node_by_ram_code(काष्ठा device *dev)
अणु
	काष्ठा device_node *np;
	u32 value, ram_code;
	पूर्णांक err;

	अगर (of_get_child_count(dev->of_node) == 0) अणु
		dev_info_once(dev, "device-tree doesn't have memory timings\n");
		वापस शून्य;
	पूर्ण

	ram_code = tegra_पढ़ो_ram_code();

	क्रम_each_child_of_node(dev->of_node, np) अणु
		err = of_property_पढ़ो_u32(np, "nvidia,ram-code", &value);
		अगर (err || value != ram_code)
			जारी;

		वापस np;
	पूर्ण

	dev_err(dev, "no memory timings for RAM code %u found in device-tree\n",
		ram_code);

	वापस शून्य;
पूर्ण

अटल पूर्णांक emc_setup_hw(काष्ठा tegra_emc *emc)
अणु
	u32 पूर्णांकmask = EMC_REFRESH_OVERFLOW_INT;
	u32 fbio_cfg5, emc_cfg, emc_dbg;
	क्रमागत emc_dram_type dram_type;

	fbio_cfg5 = पढ़ोl_relaxed(emc->regs + EMC_FBIO_CFG5);
	dram_type = fbio_cfg5 & EMC_FBIO_CFG5_DRAM_TYPE_MASK;

	emc_cfg = पढ़ोl_relaxed(emc->regs + EMC_CFG_2);

	/* enable EMC and CAR to handshake on PLL भागider/source changes */
	emc_cfg |= EMC_CLKCHANGE_REQ_ENABLE;

	/* configure घड़ी change mode accordingly to DRAM type */
	चयन (dram_type) अणु
	हाल DRAM_TYPE_LPDDR2:
		emc_cfg |= EMC_CLKCHANGE_PD_ENABLE;
		emc_cfg &= ~EMC_CLKCHANGE_SR_ENABLE;
		अवरोध;

	शेष:
		emc_cfg &= ~EMC_CLKCHANGE_SR_ENABLE;
		emc_cfg &= ~EMC_CLKCHANGE_PD_ENABLE;
		अवरोध;
	पूर्ण

	ग_लिखोl_relaxed(emc_cfg, emc->regs + EMC_CFG_2);

	/* initialize पूर्णांकerrupt */
	ग_लिखोl_relaxed(पूर्णांकmask, emc->regs + EMC_INTMASK);
	ग_लिखोl_relaxed(0xffffffff, emc->regs + EMC_INTSTATUS);

	/* ensure that unwanted debug features are disabled */
	emc_dbg = पढ़ोl_relaxed(emc->regs + EMC_DBG);
	emc_dbg |= EMC_DBG_CFG_PRIORITY;
	emc_dbg &= ~EMC_DBG_READ_MUX_ASSEMBLY;
	emc_dbg &= ~EMC_DBG_WRITE_MUX_ACTIVE;
	emc_dbg &= ~EMC_DBG_FORCE_UPDATE;
	ग_लिखोl_relaxed(emc_dbg, emc->regs + EMC_DBG);

	वापस 0;
पूर्ण

अटल दीर्घ emc_round_rate(अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ min_rate,
			   अचिन्हित दीर्घ max_rate,
			   व्योम *arg)
अणु
	काष्ठा emc_timing *timing = शून्य;
	काष्ठा tegra_emc *emc = arg;
	अचिन्हित पूर्णांक i;

	अगर (!emc->num_timings)
		वापस clk_get_rate(emc->clk);

	min_rate = min(min_rate, emc->timings[emc->num_timings - 1].rate);

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		अगर (emc->timings[i].rate < rate && i != emc->num_timings - 1)
			जारी;

		अगर (emc->timings[i].rate > max_rate) अणु
			i = max(i, 1u) - 1;

			अगर (emc->timings[i].rate < min_rate)
				अवरोध;
		पूर्ण

		अगर (emc->timings[i].rate < min_rate)
			जारी;

		timing = &emc->timings[i];
		अवरोध;
	पूर्ण

	अगर (!timing) अणु
		dev_err(emc->dev, "no timing for rate %lu min %lu max %lu\n",
			rate, min_rate, max_rate);
		वापस -EINVAL;
	पूर्ण

	वापस timing->rate;
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

अटल पूर्णांक tegra_emc_debug_available_rates_show(काष्ठा seq_file *s, व्योम *data)
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

अटल पूर्णांक tegra_emc_debug_available_rates_खोलो(काष्ठा inode *inode,
						काष्ठा file *file)
अणु
	वापस single_खोलो(file, tegra_emc_debug_available_rates_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations tegra_emc_debug_available_rates_fops = अणु
	.खोलो = tegra_emc_debug_available_rates_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

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

DEFINE_SIMPLE_ATTRIBUTE(tegra_emc_debug_min_rate_fops,
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

DEFINE_SIMPLE_ATTRIBUTE(tegra_emc_debug_max_rate_fops,
			tegra_emc_debug_max_rate_get,
			tegra_emc_debug_max_rate_set, "%llu\n");

अटल व्योम tegra_emc_debugfs_init(काष्ठा tegra_emc *emc)
अणु
	काष्ठा device *dev = emc->dev;
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
	पूर्ण

	emc->debugfs.root = debugfs_create_dir("emc", शून्य);
	अगर (!emc->debugfs.root) अणु
		dev_err(emc->dev, "failed to create debugfs directory\n");
		वापस;
	पूर्ण

	debugfs_create_file("available_rates", 0444, emc->debugfs.root,
			    emc, &tegra_emc_debug_available_rates_fops);
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
	स्थिर अचिन्हित पूर्णांक dram_data_bus_width_bytes = 4;
	स्थिर अचिन्हित पूर्णांक ddr = 2;
	पूर्णांक err;

	/*
	 * Tegra30 EMC runs on a घड़ी rate of SDRAM bus.  This means that
	 * EMC घड़ी rate is twice smaller than the peak data rate because
	 * data is sampled on both EMC घड़ी edges.
	 */
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
	tegra20_clk_set_emc_round_callback(शून्य, शून्य);
पूर्ण

अटल व्योम devm_tegra_emc_unreg_clk_notअगरier(व्योम *data)
अणु
	काष्ठा tegra_emc *emc = data;

	clk_notअगरier_unरेजिस्टर(emc->clk, &emc->clk_nb);
पूर्ण

अटल पूर्णांक tegra_emc_init_clk(काष्ठा tegra_emc *emc)
अणु
	पूर्णांक err;

	tegra20_clk_set_emc_round_callback(emc_round_rate, emc);

	err = devm_add_action_or_reset(emc->dev, devm_tegra_emc_unset_callback,
				       शून्य);
	अगर (err)
		वापस err;

	emc->clk = devm_clk_get(emc->dev, शून्य);
	अगर (IS_ERR(emc->clk)) अणु
		dev_err(emc->dev, "failed to get EMC clock: %pe\n", emc->clk);
		वापस PTR_ERR(emc->clk);
	पूर्ण

	err = clk_notअगरier_रेजिस्टर(emc->clk, &emc->clk_nb);
	अगर (err) अणु
		dev_err(emc->dev, "failed to register clk notifier: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_add_action_or_reset(emc->dev,
				       devm_tegra_emc_unreg_clk_notअगरier, emc);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np;
	काष्ठा tegra_emc *emc;
	पूर्णांक err;

	emc = devm_kzalloc(&pdev->dev, माप(*emc), GFP_KERNEL);
	अगर (!emc)
		वापस -ENOMEM;

	emc->mc = devm_tegra_memory_controller_get(&pdev->dev);
	अगर (IS_ERR(emc->mc))
		वापस PTR_ERR(emc->mc);

	mutex_init(&emc->rate_lock);
	emc->clk_nb.notअगरier_call = emc_clk_change_notअगरy;
	emc->dev = &pdev->dev;

	np = emc_find_node_by_ram_code(&pdev->dev);
	अगर (np) अणु
		err = emc_load_timings_from_dt(emc, np);
		of_node_put(np);
		अगर (err)
			वापस err;
	पूर्ण

	emc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(emc->regs))
		वापस PTR_ERR(emc->regs);

	err = emc_setup_hw(emc);
	अगर (err)
		वापस err;

	err = platक्रमm_get_irq(pdev, 0);
	अगर (err < 0)
		वापस err;

	emc->irq = err;

	err = devm_request_irq(&pdev->dev, emc->irq, tegra_emc_isr, 0,
			       dev_name(&pdev->dev), emc);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to request irq: %d\n", err);
		वापस err;
	पूर्ण

	err = tegra_emc_init_clk(emc);
	अगर (err)
		वापस err;

	err = tegra_emc_opp_table_init(emc);
	अगर (err)
		वापस err;

	platक्रमm_set_drvdata(pdev, emc);
	tegra_emc_rate_requests_init(emc);
	tegra_emc_debugfs_init(emc);
	tegra_emc_पूर्णांकerconnect_init(emc);

	/*
	 * Don't allow the kernel module to be unloaded. Unloading adds some
	 * extra complनिकासy which करोesn't really worth the efक्रमt in a हाल of
	 * this driver.
	 */
	try_module_get(THIS_MODULE);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_emc *emc = dev_get_drvdata(dev);
	पूर्णांक err;

	/* take exclusive control over the घड़ी's rate */
	err = clk_rate_exclusive_get(emc->clk);
	अगर (err) अणु
		dev_err(emc->dev, "failed to acquire clk: %d\n", err);
		वापस err;
	पूर्ण

	/* suspending in a bad state will hang machine */
	अगर (WARN(emc->bad_state, "hardware in a bad state\n"))
		वापस -EINVAL;

	emc->bad_state = true;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_emc *emc = dev_get_drvdata(dev);

	emc_setup_hw(emc);
	emc->bad_state = false;

	clk_rate_exclusive_put(emc->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_emc_pm_ops = अणु
	.suspend = tegra_emc_suspend,
	.resume = tegra_emc_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_emc_of_match[] = अणु
	अणु .compatible = "nvidia,tegra30-emc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_emc_of_match);

अटल काष्ठा platक्रमm_driver tegra_emc_driver = अणु
	.probe = tegra_emc_probe,
	.driver = अणु
		.name = "tegra30-emc",
		.of_match_table = tegra_emc_of_match,
		.pm = &tegra_emc_pm_ops,
		.suppress_bind_attrs = true,
		.sync_state = icc_sync_state,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_emc_driver);

MODULE_AUTHOR("Dmitry Osipenko <digetx@gmail.com>");
MODULE_DESCRIPTION("NVIDIA Tegra30 EMC driver");
MODULE_LICENSE("GPL v2");
