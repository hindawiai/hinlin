<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/soc/tegra/pmc.c
 *
 * Copyright (c) 2010 Google, Inc
 * Copyright (c) 2018-2020, NVIDIA CORPORATION. All rights reserved.
 *
 * Author:
 *	Colin Cross <ccross@google.com>
 */

#घोषणा pr_fmt(fmt) "tegra-pmc: " fmt

#समावेश <linux/arm-smccc.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/clk-conf.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <soc/tegra/common.h>
#समावेश <soc/tegra/fuse.h>
#समावेश <soc/tegra/pmc.h>

#समावेश <dt-bindings/पूर्णांकerrupt-controller/arm-gic.h>
#समावेश <dt-bindings/pinctrl/pinctrl-tegra-io-pad.h>
#समावेश <dt-bindings/gpio/tegra186-gpपन.स>
#समावेश <dt-bindings/gpio/tegra194-gpपन.स>
#समावेश <dt-bindings/soc/tegra-pmc.h>

#घोषणा PMC_CNTRL			0x0
#घोषणा  PMC_CNTRL_INTR_POLARITY	BIT(17) /* inverts INTR polarity */
#घोषणा  PMC_CNTRL_CPU_PWRREQ_OE	BIT(16) /* CPU pwr req enable */
#घोषणा  PMC_CNTRL_CPU_PWRREQ_POLARITY	BIT(15) /* CPU pwr req polarity */
#घोषणा  PMC_CNTRL_SIDE_EFFECT_LP0	BIT(14) /* LP0 when CPU pwr gated */
#घोषणा  PMC_CNTRL_SYSCLK_OE		BIT(11) /* प्रणाली घड़ी enable */
#घोषणा  PMC_CNTRL_SYSCLK_POLARITY	BIT(10) /* sys clk polarity */
#घोषणा  PMC_CNTRL_PWRREQ_POLARITY	BIT(8)
#घोषणा  PMC_CNTRL_BLINK_EN		7
#घोषणा  PMC_CNTRL_MAIN_RST		BIT(4)

#घोषणा PMC_WAKE_MASK			0x0c
#घोषणा PMC_WAKE_LEVEL			0x10
#घोषणा PMC_WAKE_STATUS			0x14
#घोषणा PMC_SW_WAKE_STATUS		0x18
#घोषणा PMC_DPD_PADS_ORIDE		0x1c
#घोषणा  PMC_DPD_PADS_ORIDE_BLINK	20

#घोषणा DPD_SAMPLE			0x020
#घोषणा  DPD_SAMPLE_ENABLE		BIT(0)
#घोषणा  DPD_SAMPLE_DISABLE		(0 << 0)

#घोषणा PWRGATE_TOGGLE			0x30
#घोषणा  PWRGATE_TOGGLE_START		BIT(8)

#घोषणा REMOVE_CLAMPING			0x34

#घोषणा PWRGATE_STATUS			0x38

#घोषणा PMC_BLINK_TIMER			0x40
#घोषणा PMC_IMPL_E_33V_PWR		0x40

#घोषणा PMC_PWR_DET			0x48

#घोषणा PMC_SCRATCH0_MODE_RECOVERY	BIT(31)
#घोषणा PMC_SCRATCH0_MODE_BOOTLOADER	BIT(30)
#घोषणा PMC_SCRATCH0_MODE_RCM		BIT(1)
#घोषणा PMC_SCRATCH0_MODE_MASK		(PMC_SCRATCH0_MODE_RECOVERY | \
					 PMC_SCRATCH0_MODE_BOOTLOADER | \
					 PMC_SCRATCH0_MODE_RCM)

#घोषणा PMC_CPUPWRGOOD_TIMER		0xc8
#घोषणा PMC_CPUPWROFF_TIMER		0xcc
#घोषणा PMC_COREPWRGOOD_TIMER		0x3c
#घोषणा PMC_COREPWROFF_TIMER		0xe0

#घोषणा PMC_PWR_DET_VALUE		0xe4

#घोषणा PMC_USB_DEBOUNCE_DEL		0xec
#घोषणा PMC_USB_AO			0xf0

#घोषणा PMC_SCRATCH41			0x140

#घोषणा PMC_WAKE2_MASK			0x160
#घोषणा PMC_WAKE2_LEVEL			0x164
#घोषणा PMC_WAKE2_STATUS		0x168
#घोषणा PMC_SW_WAKE2_STATUS		0x16c

#घोषणा PMC_CLK_OUT_CNTRL		0x1a8
#घोषणा  PMC_CLK_OUT_MUX_MASK		GENMASK(1, 0)
#घोषणा PMC_SENSOR_CTRL			0x1b0
#घोषणा  PMC_SENSOR_CTRL_SCRATCH_WRITE	BIT(2)
#घोषणा  PMC_SENSOR_CTRL_ENABLE_RST	BIT(1)

#घोषणा  PMC_RST_STATUS_POR		0
#घोषणा  PMC_RST_STATUS_WATCHDOG	1
#घोषणा  PMC_RST_STATUS_SENSOR		2
#घोषणा  PMC_RST_STATUS_SW_MAIN		3
#घोषणा  PMC_RST_STATUS_LP0		4
#घोषणा  PMC_RST_STATUS_AOTAG		5

#घोषणा IO_DPD_REQ			0x1b8
#घोषणा  IO_DPD_REQ_CODE_IDLE		(0U << 30)
#घोषणा  IO_DPD_REQ_CODE_OFF		(1U << 30)
#घोषणा  IO_DPD_REQ_CODE_ON		(2U << 30)
#घोषणा  IO_DPD_REQ_CODE_MASK		(3U << 30)

#घोषणा IO_DPD_STATUS			0x1bc
#घोषणा IO_DPD2_REQ			0x1c0
#घोषणा IO_DPD2_STATUS			0x1c4
#घोषणा SEL_DPD_TIM			0x1c8

#घोषणा PMC_UTMIP_UHSIC_TRIGGERS	0x1ec
#घोषणा PMC_UTMIP_UHSIC_SAVED_STATE	0x1f0

#घोषणा PMC_UTMIP_TERM_PAD_CFG		0x1f8
#घोषणा PMC_UTMIP_UHSIC_SLEEP_CFG	0x1fc
#घोषणा PMC_UTMIP_UHSIC_FAKE		0x218

#घोषणा PMC_SCRATCH54			0x258
#घोषणा  PMC_SCRATCH54_DATA_SHIFT	8
#घोषणा  PMC_SCRATCH54_ADDR_SHIFT	0

#घोषणा PMC_SCRATCH55			0x25c
#घोषणा  PMC_SCRATCH55_RESET_TEGRA	BIT(31)
#घोषणा  PMC_SCRATCH55_CNTRL_ID_SHIFT	27
#घोषणा  PMC_SCRATCH55_PINMUX_SHIFT	24
#घोषणा  PMC_SCRATCH55_16BITOP		BIT(15)
#घोषणा  PMC_SCRATCH55_CHECKSUM_SHIFT	16
#घोषणा  PMC_SCRATCH55_I2CSLV1_SHIFT	0

#घोषणा  PMC_UTMIP_UHSIC_LINE_WAKEUP	0x26c

#घोषणा PMC_UTMIP_BIAS_MASTER_CNTRL	0x270
#घोषणा PMC_UTMIP_MASTER_CONFIG		0x274
#घोषणा PMC_UTMIP_UHSIC2_TRIGGERS	0x27c
#घोषणा PMC_UTMIP_MASTER2_CONFIG	0x29c

#घोषणा GPU_RG_CNTRL			0x2d4

#घोषणा PMC_UTMIP_PAD_CFG0		0x4c0
#घोषणा PMC_UTMIP_UHSIC_SLEEP_CFG1	0x4d0
#घोषणा PMC_UTMIP_SLEEPWALK_P3		0x4e0
/* Tegra186 and later */
#घोषणा WAKE_AOWAKE_CNTRL(x) (0x000 + ((x) << 2))
#घोषणा WAKE_AOWAKE_CNTRL_LEVEL (1 << 3)
#घोषणा WAKE_AOWAKE_MASK_W(x) (0x180 + ((x) << 2))
#घोषणा WAKE_AOWAKE_MASK_R(x) (0x300 + ((x) << 2))
#घोषणा WAKE_AOWAKE_STATUS_W(x) (0x30c + ((x) << 2))
#घोषणा WAKE_AOWAKE_STATUS_R(x) (0x48c + ((x) << 2))
#घोषणा WAKE_AOWAKE_TIER0_ROUTING(x) (0x4b4 + ((x) << 2))
#घोषणा WAKE_AOWAKE_TIER1_ROUTING(x) (0x4c0 + ((x) << 2))
#घोषणा WAKE_AOWAKE_TIER2_ROUTING(x) (0x4cc + ((x) << 2))

#घोषणा WAKE_AOWAKE_CTRL 0x4f4
#घोषणा  WAKE_AOWAKE_CTRL_INTR_POLARITY BIT(0)

/* क्रम secure PMC */
#घोषणा TEGRA_SMC_PMC		0xc2fffe00
#घोषणा  TEGRA_SMC_PMC_READ	0xaa
#घोषणा  TEGRA_SMC_PMC_WRITE	0xbb

काष्ठा pmc_clk अणु
	काष्ठा clk_hw	hw;
	अचिन्हित दीर्घ	offs;
	u32		mux_shअगरt;
	u32		क्रमce_en_shअगरt;
पूर्ण;

#घोषणा to_pmc_clk(_hw) container_of(_hw, काष्ठा pmc_clk, hw)

काष्ठा pmc_clk_gate अणु
	काष्ठा clk_hw	hw;
	अचिन्हित दीर्घ	offs;
	u32		shअगरt;
पूर्ण;

#घोषणा to_pmc_clk_gate(_hw) container_of(_hw, काष्ठा pmc_clk_gate, hw)

काष्ठा pmc_clk_init_data अणु
	अक्षर *name;
	स्थिर अक्षर *स्थिर *parents;
	पूर्णांक num_parents;
	पूर्णांक clk_id;
	u8 mux_shअगरt;
	u8 क्रमce_en_shअगरt;
पूर्ण;

अटल स्थिर अक्षर * स्थिर clk_out1_parents[] = अणु "osc", "osc_div2",
	"osc_div4", "extern1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर clk_out2_parents[] = अणु "osc", "osc_div2",
	"osc_div4", "extern2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर clk_out3_parents[] = अणु "osc", "osc_div2",
	"osc_div4", "extern3",
पूर्ण;

अटल स्थिर काष्ठा pmc_clk_init_data tegra_pmc_clks_data[] = अणु
	अणु
		.name = "pmc_clk_out_1",
		.parents = clk_out1_parents,
		.num_parents = ARRAY_SIZE(clk_out1_parents),
		.clk_id = TEGRA_PMC_CLK_OUT_1,
		.mux_shअगरt = 6,
		.क्रमce_en_shअगरt = 2,
	पूर्ण,
	अणु
		.name = "pmc_clk_out_2",
		.parents = clk_out2_parents,
		.num_parents = ARRAY_SIZE(clk_out2_parents),
		.clk_id = TEGRA_PMC_CLK_OUT_2,
		.mux_shअगरt = 14,
		.क्रमce_en_shअगरt = 10,
	पूर्ण,
	अणु
		.name = "pmc_clk_out_3",
		.parents = clk_out3_parents,
		.num_parents = ARRAY_SIZE(clk_out3_parents),
		.clk_id = TEGRA_PMC_CLK_OUT_3,
		.mux_shअगरt = 22,
		.क्रमce_en_shअगरt = 18,
	पूर्ण,
पूर्ण;

काष्ठा tegra_घातergate अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	काष्ठा tegra_pmc *pmc;
	अचिन्हित पूर्णांक id;
	काष्ठा clk **clks;
	अचिन्हित पूर्णांक num_clks;
	अचिन्हित दीर्घ *clk_rates;
	काष्ठा reset_control *reset;
पूर्ण;

काष्ठा tegra_io_pad_soc अणु
	क्रमागत tegra_io_pad id;
	अचिन्हित पूर्णांक dpd;
	अचिन्हित पूर्णांक voltage;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा tegra_pmc_regs अणु
	अचिन्हित पूर्णांक scratch0;
	अचिन्हित पूर्णांक dpd_req;
	अचिन्हित पूर्णांक dpd_status;
	अचिन्हित पूर्णांक dpd2_req;
	अचिन्हित पूर्णांक dpd2_status;
	अचिन्हित पूर्णांक rst_status;
	अचिन्हित पूर्णांक rst_source_shअगरt;
	अचिन्हित पूर्णांक rst_source_mask;
	अचिन्हित पूर्णांक rst_level_shअगरt;
	अचिन्हित पूर्णांक rst_level_mask;
पूर्ण;

काष्ठा tegra_wake_event अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक irq;
	काष्ठा अणु
		अचिन्हित पूर्णांक instance;
		अचिन्हित पूर्णांक pin;
	पूर्ण gpio;
पूर्ण;

#घोषणा TEGRA_WAKE_IRQ(_name, _id, _irq)		\
	अणु						\
		.name = _name,				\
		.id = _id,				\
		.irq = _irq,				\
		.gpio = अणु				\
			.instance = अच_पूर्णांक_उच्च,		\
			.pin = अच_पूर्णांक_उच्च,		\
		पूर्ण,					\
	पूर्ण

#घोषणा TEGRA_WAKE_GPIO(_name, _id, _instance, _pin)	\
	अणु						\
		.name = _name,				\
		.id = _id,				\
		.irq = 0,				\
		.gpio = अणु				\
			.instance = _instance,		\
			.pin = _pin,			\
		पूर्ण,					\
	पूर्ण

काष्ठा tegra_pmc_soc अणु
	अचिन्हित पूर्णांक num_घातergates;
	स्थिर अक्षर *स्थिर *घातergates;
	अचिन्हित पूर्णांक num_cpu_घातergates;
	स्थिर u8 *cpu_घातergates;

	bool has_tsense_reset;
	bool has_gpu_clamps;
	bool needs_mbist_war;
	bool has_impl_33v_pwr;
	bool maybe_tz_only;

	स्थिर काष्ठा tegra_io_pad_soc *io_pads;
	अचिन्हित पूर्णांक num_io_pads;

	स्थिर काष्ठा pinctrl_pin_desc *pin_descs;
	अचिन्हित पूर्णांक num_pin_descs;

	स्थिर काष्ठा tegra_pmc_regs *regs;
	व्योम (*init)(काष्ठा tegra_pmc *pmc);
	व्योम (*setup_irq_polarity)(काष्ठा tegra_pmc *pmc,
				   काष्ठा device_node *np,
				   bool invert);
	पूर्णांक (*irq_set_wake)(काष्ठा irq_data *data, अचिन्हित पूर्णांक on);
	पूर्णांक (*irq_set_type)(काष्ठा irq_data *data, अचिन्हित पूर्णांक type);
	पूर्णांक (*घातergate_set)(काष्ठा tegra_pmc *pmc, अचिन्हित पूर्णांक id,
			     bool new_state);

	स्थिर अक्षर * स्थिर *reset_sources;
	अचिन्हित पूर्णांक num_reset_sources;
	स्थिर अक्षर * स्थिर *reset_levels;
	अचिन्हित पूर्णांक num_reset_levels;

	/*
	 * These describe events that can wake the प्रणाली from sleep (i.e.
	 * LP0 or SC7). Wakeup from other sleep states (such as LP1 or LP2)
	 * are dealt with in the LIC.
	 */
	स्थिर काष्ठा tegra_wake_event *wake_events;
	अचिन्हित पूर्णांक num_wake_events;

	स्थिर काष्ठा pmc_clk_init_data *pmc_clks_data;
	अचिन्हित पूर्णांक num_pmc_clks;
	bool has_blink_output;
	bool has_usb_sleepwalk;
पूर्ण;

/**
 * काष्ठा tegra_pmc - NVIDIA Tegra PMC
 * @dev: poपूर्णांकer to PMC device काष्ठाure
 * @base: poपूर्णांकer to I/O remapped रेजिस्टर region
 * @wake: poपूर्णांकer to I/O remapped region क्रम WAKE रेजिस्टरs
 * @aotag: poपूर्णांकer to I/O remapped region क्रम AOTAG रेजिस्टरs
 * @scratch: poपूर्णांकer to I/O remapped region क्रम scratch रेजिस्टरs
 * @clk: poपूर्णांकer to pclk घड़ी
 * @soc: poपूर्णांकer to SoC data काष्ठाure
 * @tz_only: flag specअगरying अगर the PMC can only be accessed via TrustZone
 * @debugfs: poपूर्णांकer to debugfs entry
 * @rate: currently configured rate of pclk
 * @suspend_mode: lowest suspend mode available
 * @cpu_good_समय: CPU घातer good समय (in microseconds)
 * @cpu_off_समय: CPU घातer off समय (in microsecends)
 * @core_osc_समय: core घातer good OSC समय (in microseconds)
 * @core_pmu_समय: core घातer good PMU समय (in microseconds)
 * @core_off_समय: core घातer off समय (in microseconds)
 * @corereq_high: core घातer request is active-high
 * @sysclkreq_high: प्रणाली घड़ी request is active-high
 * @combined_req: combined घातer request क्रम CPU & core
 * @cpu_pwr_good_en: CPU घातer good संकेत is enabled
 * @lp0_vec_phys: physical base address of the LP0 warm boot code
 * @lp0_vec_size: size of the LP0 warm boot code
 * @घातergates_available: Biपंचांगap of available घातer gates
 * @घातergates_lock: mutex क्रम घातer gate रेजिस्टर access
 * @pctl_dev: pin controller exposed by the PMC
 * @करोमुख्य: IRQ करोमुख्य provided by the PMC
 * @irq: chip implementation क्रम the IRQ करोमुख्य
 * @clk_nb: pclk घड़ी changes handler
 */
काष्ठा tegra_pmc अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	व्योम __iomem *wake;
	व्योम __iomem *aotag;
	व्योम __iomem *scratch;
	काष्ठा clk *clk;
	काष्ठा dentry *debugfs;

	स्थिर काष्ठा tegra_pmc_soc *soc;
	bool tz_only;

	अचिन्हित दीर्घ rate;

	क्रमागत tegra_suspend_mode suspend_mode;
	u32 cpu_good_समय;
	u32 cpu_off_समय;
	u32 core_osc_समय;
	u32 core_pmu_समय;
	u32 core_off_समय;
	bool corereq_high;
	bool sysclkreq_high;
	bool combined_req;
	bool cpu_pwr_good_en;
	u32 lp0_vec_phys;
	u32 lp0_vec_size;
	DECLARE_BITMAP(घातergates_available, TEGRA_POWERGATE_MAX);

	काष्ठा mutex घातergates_lock;

	काष्ठा pinctrl_dev *pctl_dev;

	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा irq_chip irq;

	काष्ठा notअगरier_block clk_nb;
पूर्ण;

अटल काष्ठा tegra_pmc *pmc = &(काष्ठा tegra_pmc) अणु
	.base = शून्य,
	.suspend_mode = TEGRA_SUSPEND_NONE,
पूर्ण;

अटल अंतरभूत काष्ठा tegra_घातergate *
to_घातergate(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	वापस container_of(करोमुख्य, काष्ठा tegra_घातergate, genpd);
पूर्ण

अटल u32 tegra_pmc_पढ़ोl(काष्ठा tegra_pmc *pmc, अचिन्हित दीर्घ offset)
अणु
	काष्ठा arm_smccc_res res;

	अगर (pmc->tz_only) अणु
		arm_smccc_smc(TEGRA_SMC_PMC, TEGRA_SMC_PMC_READ, offset, 0, 0,
			      0, 0, 0, &res);
		अगर (res.a0) अणु
			अगर (pmc->dev)
				dev_warn(pmc->dev, "%s(): SMC failed: %lu\n",
					 __func__, res.a0);
			अन्यथा
				pr_warn("%s(): SMC failed: %lu\n", __func__,
					res.a0);
		पूर्ण

		वापस res.a1;
	पूर्ण

	वापस पढ़ोl(pmc->base + offset);
पूर्ण

अटल व्योम tegra_pmc_ग_लिखोl(काष्ठा tegra_pmc *pmc, u32 value,
			     अचिन्हित दीर्घ offset)
अणु
	काष्ठा arm_smccc_res res;

	अगर (pmc->tz_only) अणु
		arm_smccc_smc(TEGRA_SMC_PMC, TEGRA_SMC_PMC_WRITE, offset,
			      value, 0, 0, 0, 0, &res);
		अगर (res.a0) अणु
			अगर (pmc->dev)
				dev_warn(pmc->dev, "%s(): SMC failed: %lu\n",
					 __func__, res.a0);
			अन्यथा
				pr_warn("%s(): SMC failed: %lu\n", __func__,
					res.a0);
		पूर्ण
	पूर्ण अन्यथा अणु
		ग_लिखोl(value, pmc->base + offset);
	पूर्ण
पूर्ण

अटल u32 tegra_pmc_scratch_पढ़ोl(काष्ठा tegra_pmc *pmc, अचिन्हित दीर्घ offset)
अणु
	अगर (pmc->tz_only)
		वापस tegra_pmc_पढ़ोl(pmc, offset);

	वापस पढ़ोl(pmc->scratch + offset);
पूर्ण

अटल व्योम tegra_pmc_scratch_ग_लिखोl(काष्ठा tegra_pmc *pmc, u32 value,
				     अचिन्हित दीर्घ offset)
अणु
	अगर (pmc->tz_only)
		tegra_pmc_ग_लिखोl(pmc, value, offset);
	अन्यथा
		ग_लिखोl(value, pmc->scratch + offset);
पूर्ण

/*
 * TODO Figure out a way to call this with the काष्ठा tegra_pmc * passed in.
 * This currently करोesn't work because पढ़ोx_poll_समयout() can only operate
 * on functions that take a single argument.
 */
अटल अंतरभूत bool tegra_घातergate_state(पूर्णांक id)
अणु
	अगर (id == TEGRA_POWERGATE_3D && pmc->soc->has_gpu_clamps)
		वापस (tegra_pmc_पढ़ोl(pmc, GPU_RG_CNTRL) & 0x1) == 0;
	अन्यथा
		वापस (tegra_pmc_पढ़ोl(pmc, PWRGATE_STATUS) & BIT(id)) != 0;
पूर्ण

अटल अंतरभूत bool tegra_घातergate_is_valid(काष्ठा tegra_pmc *pmc, पूर्णांक id)
अणु
	वापस (pmc->soc && pmc->soc->घातergates[id]);
पूर्ण

अटल अंतरभूत bool tegra_घातergate_is_available(काष्ठा tegra_pmc *pmc, पूर्णांक id)
अणु
	वापस test_bit(id, pmc->घातergates_available);
पूर्ण

अटल पूर्णांक tegra_घातergate_lookup(काष्ठा tegra_pmc *pmc, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!pmc || !pmc->soc || !name)
		वापस -EINVAL;

	क्रम (i = 0; i < pmc->soc->num_घातergates; i++) अणु
		अगर (!tegra_घातergate_is_valid(pmc, i))
			जारी;

		अगर (!म_भेद(name, pmc->soc->घातergates[i]))
			वापस i;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक tegra20_घातergate_set(काष्ठा tegra_pmc *pmc, अचिन्हित पूर्णांक id,
				 bool new_state)
अणु
	अचिन्हित पूर्णांक retries = 100;
	bool status;
	पूर्णांक ret;

	/*
	 * As per TRM करोcumentation, the toggle command will be dropped by PMC
	 * अगर there is contention with a HW-initiated toggling (i.e. CPU core
	 * घातer-gated), the command should be retried in that हाल.
	 */
	करो अणु
		tegra_pmc_ग_लिखोl(pmc, PWRGATE_TOGGLE_START | id, PWRGATE_TOGGLE);

		/* रुको क्रम PMC to execute the command */
		ret = पढ़ोx_poll_समयout(tegra_घातergate_state, id, status,
					 status == new_state, 1, 10);
	पूर्ण जबतक (ret == -ETIMEDOUT && retries--);

	वापस ret;
पूर्ण

अटल अंतरभूत bool tegra_घातergate_toggle_पढ़ोy(काष्ठा tegra_pmc *pmc)
अणु
	वापस !(tegra_pmc_पढ़ोl(pmc, PWRGATE_TOGGLE) & PWRGATE_TOGGLE_START);
पूर्ण

अटल पूर्णांक tegra114_घातergate_set(काष्ठा tegra_pmc *pmc, अचिन्हित पूर्णांक id,
				  bool new_state)
अणु
	bool status;
	पूर्णांक err;

	/* रुको जबतक PMC घातer gating is contended */
	err = पढ़ोx_poll_समयout(tegra_घातergate_toggle_पढ़ोy, pmc, status,
				 status == true, 1, 100);
	अगर (err)
		वापस err;

	tegra_pmc_ग_लिखोl(pmc, PWRGATE_TOGGLE_START | id, PWRGATE_TOGGLE);

	/* रुको क्रम PMC to accept the command */
	err = पढ़ोx_poll_समयout(tegra_घातergate_toggle_पढ़ोy, pmc, status,
				 status == true, 1, 100);
	अगर (err)
		वापस err;

	/* रुको क्रम PMC to execute the command */
	err = पढ़ोx_poll_समयout(tegra_घातergate_state, id, status,
				 status == new_state, 10, 100000);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/**
 * tegra_घातergate_set() - set the state of a partition
 * @pmc: घातer management controller
 * @id: partition ID
 * @new_state: new state of the partition
 */
अटल पूर्णांक tegra_घातergate_set(काष्ठा tegra_pmc *pmc, अचिन्हित पूर्णांक id,
			       bool new_state)
अणु
	पूर्णांक err;

	अगर (id == TEGRA_POWERGATE_3D && pmc->soc->has_gpu_clamps)
		वापस -EINVAL;

	mutex_lock(&pmc->घातergates_lock);

	अगर (tegra_घातergate_state(id) == new_state) अणु
		mutex_unlock(&pmc->घातergates_lock);
		वापस 0;
	पूर्ण

	err = pmc->soc->घातergate_set(pmc, id, new_state);

	mutex_unlock(&pmc->घातergates_lock);

	वापस err;
पूर्ण

अटल पूर्णांक __tegra_घातergate_हटाओ_clamping(काष्ठा tegra_pmc *pmc,
					     अचिन्हित पूर्णांक id)
अणु
	u32 mask;

	mutex_lock(&pmc->घातergates_lock);

	/*
	 * On Tegra124 and later, the clamps क्रम the GPU are controlled by a
	 * separate रेजिस्टर (with dअगरferent semantics).
	 */
	अगर (id == TEGRA_POWERGATE_3D) अणु
		अगर (pmc->soc->has_gpu_clamps) अणु
			tegra_pmc_ग_लिखोl(pmc, 0, GPU_RG_CNTRL);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Tegra 2 has a bug where PCIE and VDE clamping masks are
	 * swapped relatively to the partition ids
	 */
	अगर (id == TEGRA_POWERGATE_VDEC)
		mask = (1 << TEGRA_POWERGATE_PCIE);
	अन्यथा अगर (id == TEGRA_POWERGATE_PCIE)
		mask = (1 << TEGRA_POWERGATE_VDEC);
	अन्यथा
		mask = (1 << id);

	tegra_pmc_ग_लिखोl(pmc, mask, REMOVE_CLAMPING);

out:
	mutex_unlock(&pmc->घातergates_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_घातergate_prepare_घड़ीs(काष्ठा tegra_घातergate *pg)
अणु
	अचिन्हित दीर्घ safe_rate = 100 * 1000 * 1000;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < pg->num_clks; i++) अणु
		pg->clk_rates[i] = clk_get_rate(pg->clks[i]);

		अगर (!pg->clk_rates[i]) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (pg->clk_rates[i] <= safe_rate)
			जारी;

		/*
		 * We करोn't know whether voltage state is okay क्रम the
		 * current घड़ी rate, hence it's better to temporally
		 * चयन घड़ी to a safe rate which is suitable क्रम
		 * all voltages, beक्रमe enabling the घड़ी.
		 */
		err = clk_set_rate(pg->clks[i], safe_rate);
		अगर (err)
			जाओ out;
	पूर्ण

	वापस 0;

out:
	जबतक (i--)
		clk_set_rate(pg->clks[i], pg->clk_rates[i]);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_घातergate_unprepare_घड़ीs(काष्ठा tegra_घातergate *pg)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < pg->num_clks; i++) अणु
		err = clk_set_rate(pg->clks[i], pg->clk_rates[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_घातergate_disable_घड़ीs(काष्ठा tegra_घातergate *pg)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pg->num_clks; i++)
		clk_disable_unprepare(pg->clks[i]);
पूर्ण

अटल पूर्णांक tegra_घातergate_enable_घड़ीs(काष्ठा tegra_घातergate *pg)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < pg->num_clks; i++) अणु
		err = clk_prepare_enable(pg->clks[i]);
		अगर (err)
			जाओ out;
	पूर्ण

	वापस 0;

out:
	जबतक (i--)
		clk_disable_unprepare(pg->clks[i]);

	वापस err;
पूर्ण

पूर्णांक __weak tegra210_clk_handle_mbist_war(अचिन्हित पूर्णांक id)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_घातergate_घातer_up(काष्ठा tegra_घातergate *pg,
				    bool disable_घड़ीs)
अणु
	पूर्णांक err;

	err = reset_control_निश्चित(pg->reset);
	अगर (err)
		वापस err;

	usleep_range(10, 20);

	err = tegra_घातergate_set(pg->pmc, pg->id, true);
	अगर (err < 0)
		वापस err;

	usleep_range(10, 20);

	err = tegra_घातergate_prepare_घड़ीs(pg);
	अगर (err)
		जाओ घातergate_off;

	err = tegra_घातergate_enable_घड़ीs(pg);
	अगर (err)
		जाओ unprepare_clks;

	usleep_range(10, 20);

	err = __tegra_घातergate_हटाओ_clamping(pg->pmc, pg->id);
	अगर (err)
		जाओ disable_clks;

	usleep_range(10, 20);

	err = reset_control_deनिश्चित(pg->reset);
	अगर (err)
		जाओ घातergate_off;

	usleep_range(10, 20);

	अगर (pg->pmc->soc->needs_mbist_war)
		err = tegra210_clk_handle_mbist_war(pg->id);
	अगर (err)
		जाओ disable_clks;

	अगर (disable_घड़ीs)
		tegra_घातergate_disable_घड़ीs(pg);

	err = tegra_घातergate_unprepare_घड़ीs(pg);
	अगर (err)
		वापस err;

	वापस 0;

disable_clks:
	tegra_घातergate_disable_घड़ीs(pg);
	usleep_range(10, 20);

unprepare_clks:
	tegra_घातergate_unprepare_घड़ीs(pg);

घातergate_off:
	tegra_घातergate_set(pg->pmc, pg->id, false);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_घातergate_घातer_करोwn(काष्ठा tegra_घातergate *pg)
अणु
	पूर्णांक err;

	err = tegra_घातergate_prepare_घड़ीs(pg);
	अगर (err)
		वापस err;

	err = tegra_घातergate_enable_घड़ीs(pg);
	अगर (err)
		जाओ unprepare_clks;

	usleep_range(10, 20);

	err = reset_control_निश्चित(pg->reset);
	अगर (err)
		जाओ disable_clks;

	usleep_range(10, 20);

	tegra_घातergate_disable_घड़ीs(pg);

	usleep_range(10, 20);

	err = tegra_घातergate_set(pg->pmc, pg->id, false);
	अगर (err)
		जाओ निश्चित_resets;

	err = tegra_घातergate_unprepare_घड़ीs(pg);
	अगर (err)
		वापस err;

	वापस 0;

निश्चित_resets:
	tegra_घातergate_enable_घड़ीs(pg);
	usleep_range(10, 20);
	reset_control_deनिश्चित(pg->reset);
	usleep_range(10, 20);

disable_clks:
	tegra_घातergate_disable_घड़ीs(pg);

unprepare_clks:
	tegra_घातergate_unprepare_घड़ीs(pg);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_genpd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा tegra_घातergate *pg = to_घातergate(करोमुख्य);
	काष्ठा device *dev = pg->pmc->dev;
	पूर्णांक err;

	err = tegra_घातergate_घातer_up(pg, true);
	अगर (err) अणु
		dev_err(dev, "failed to turn on PM domain %s: %d\n",
			pg->genpd.name, err);
		जाओ out;
	पूर्ण

	reset_control_release(pg->reset);

out:
	वापस err;
पूर्ण

अटल पूर्णांक tegra_genpd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा tegra_घातergate *pg = to_घातergate(करोमुख्य);
	काष्ठा device *dev = pg->pmc->dev;
	पूर्णांक err;

	err = reset_control_acquire(pg->reset);
	अगर (err < 0) अणु
		dev_err(dev, "failed to acquire resets for PM domain %s: %d\n",
			pg->genpd.name, err);
		वापस err;
	पूर्ण

	err = tegra_घातergate_घातer_करोwn(pg);
	अगर (err) अणु
		dev_err(dev, "failed to turn off PM domain %s: %d\n",
			pg->genpd.name, err);
		reset_control_release(pg->reset);
	पूर्ण

	वापस err;
पूर्ण

/**
 * tegra_घातergate_घातer_on() - घातer on partition
 * @id: partition ID
 */
पूर्णांक tegra_घातergate_घातer_on(अचिन्हित पूर्णांक id)
अणु
	अगर (!tegra_घातergate_is_available(pmc, id))
		वापस -EINVAL;

	वापस tegra_घातergate_set(pmc, id, true);
पूर्ण
EXPORT_SYMBOL(tegra_घातergate_घातer_on);

/**
 * tegra_घातergate_घातer_off() - घातer off partition
 * @id: partition ID
 */
पूर्णांक tegra_घातergate_घातer_off(अचिन्हित पूर्णांक id)
अणु
	अगर (!tegra_घातergate_is_available(pmc, id))
		वापस -EINVAL;

	वापस tegra_घातergate_set(pmc, id, false);
पूर्ण
EXPORT_SYMBOL(tegra_घातergate_घातer_off);

/**
 * tegra_घातergate_is_घातered() - check अगर partition is घातered
 * @pmc: घातer management controller
 * @id: partition ID
 */
अटल पूर्णांक tegra_घातergate_is_घातered(काष्ठा tegra_pmc *pmc, अचिन्हित पूर्णांक id)
अणु
	अगर (!tegra_घातergate_is_valid(pmc, id))
		वापस -EINVAL;

	वापस tegra_घातergate_state(id);
पूर्ण

/**
 * tegra_घातergate_हटाओ_clamping() - हटाओ घातer clamps क्रम partition
 * @id: partition ID
 */
पूर्णांक tegra_घातergate_हटाओ_clamping(अचिन्हित पूर्णांक id)
अणु
	अगर (!tegra_घातergate_is_available(pmc, id))
		वापस -EINVAL;

	वापस __tegra_घातergate_हटाओ_clamping(pmc, id);
पूर्ण
EXPORT_SYMBOL(tegra_घातergate_हटाओ_clamping);

/**
 * tegra_घातergate_sequence_घातer_up() - घातer up partition
 * @id: partition ID
 * @clk: घड़ी क्रम partition
 * @rst: reset क्रम partition
 *
 * Must be called with clk disabled, and वापसs with clk enabled.
 */
पूर्णांक tegra_घातergate_sequence_घातer_up(अचिन्हित पूर्णांक id, काष्ठा clk *clk,
				      काष्ठा reset_control *rst)
अणु
	काष्ठा tegra_घातergate *pg;
	पूर्णांक err;

	अगर (!tegra_घातergate_is_available(pmc, id))
		वापस -EINVAL;

	pg = kzalloc(माप(*pg), GFP_KERNEL);
	अगर (!pg)
		वापस -ENOMEM;

	pg->clk_rates = kzalloc(माप(*pg->clk_rates), GFP_KERNEL);
	अगर (!pg->clk_rates) अणु
		kमुक्त(pg->clks);
		वापस -ENOMEM;
	पूर्ण

	pg->id = id;
	pg->clks = &clk;
	pg->num_clks = 1;
	pg->reset = rst;
	pg->pmc = pmc;

	err = tegra_घातergate_घातer_up(pg, false);
	अगर (err)
		dev_err(pmc->dev, "failed to turn on partition %d: %d\n", id,
			err);

	kमुक्त(pg->clk_rates);
	kमुक्त(pg);

	वापस err;
पूर्ण
EXPORT_SYMBOL(tegra_घातergate_sequence_घातer_up);

/**
 * tegra_get_cpu_घातergate_id() - convert from CPU ID to partition ID
 * @pmc: घातer management controller
 * @cpuid: CPU partition ID
 *
 * Returns the partition ID corresponding to the CPU partition ID or a
 * negative error code on failure.
 */
अटल पूर्णांक tegra_get_cpu_घातergate_id(काष्ठा tegra_pmc *pmc,
				      अचिन्हित पूर्णांक cpuid)
अणु
	अगर (pmc->soc && cpuid < pmc->soc->num_cpu_घातergates)
		वापस pmc->soc->cpu_घातergates[cpuid];

	वापस -EINVAL;
पूर्ण

/**
 * tegra_pmc_cpu_is_घातered() - check अगर CPU partition is घातered
 * @cpuid: CPU partition ID
 */
bool tegra_pmc_cpu_is_घातered(अचिन्हित पूर्णांक cpuid)
अणु
	पूर्णांक id;

	id = tegra_get_cpu_घातergate_id(pmc, cpuid);
	अगर (id < 0)
		वापस false;

	वापस tegra_घातergate_is_घातered(pmc, id);
पूर्ण

/**
 * tegra_pmc_cpu_घातer_on() - घातer on CPU partition
 * @cpuid: CPU partition ID
 */
पूर्णांक tegra_pmc_cpu_घातer_on(अचिन्हित पूर्णांक cpuid)
अणु
	पूर्णांक id;

	id = tegra_get_cpu_घातergate_id(pmc, cpuid);
	अगर (id < 0)
		वापस id;

	वापस tegra_घातergate_set(pmc, id, true);
पूर्ण

/**
 * tegra_pmc_cpu_हटाओ_clamping() - हटाओ घातer clamps क्रम CPU partition
 * @cpuid: CPU partition ID
 */
पूर्णांक tegra_pmc_cpu_हटाओ_clamping(अचिन्हित पूर्णांक cpuid)
अणु
	पूर्णांक id;

	id = tegra_get_cpu_घातergate_id(pmc, cpuid);
	अगर (id < 0)
		वापस id;

	वापस tegra_घातergate_हटाओ_clamping(id);
पूर्ण

अटल पूर्णांक tegra_pmc_restart_notअगरy(काष्ठा notअगरier_block *this,
				    अचिन्हित दीर्घ action, व्योम *data)
अणु
	स्थिर अक्षर *cmd = data;
	u32 value;

	value = tegra_pmc_scratch_पढ़ोl(pmc, pmc->soc->regs->scratch0);
	value &= ~PMC_SCRATCH0_MODE_MASK;

	अगर (cmd) अणु
		अगर (म_भेद(cmd, "recovery") == 0)
			value |= PMC_SCRATCH0_MODE_RECOVERY;

		अगर (म_भेद(cmd, "bootloader") == 0)
			value |= PMC_SCRATCH0_MODE_BOOTLOADER;

		अगर (म_भेद(cmd, "forced-recovery") == 0)
			value |= PMC_SCRATCH0_MODE_RCM;
	पूर्ण

	tegra_pmc_scratch_ग_लिखोl(pmc, value, pmc->soc->regs->scratch0);

	/* reset everything but PMC_SCRATCH0 and PMC_RST_STATUS */
	value = tegra_pmc_पढ़ोl(pmc, PMC_CNTRL);
	value |= PMC_CNTRL_MAIN_RST;
	tegra_pmc_ग_लिखोl(pmc, value, PMC_CNTRL);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block tegra_pmc_restart_handler = अणु
	.notअगरier_call = tegra_pmc_restart_notअगरy,
	.priority = 128,
पूर्ण;

अटल पूर्णांक घातergate_show(काष्ठा seq_file *s, व्योम *data)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक status;

	seq_म_लिखो(s, " powergate powered\n");
	seq_म_लिखो(s, "------------------\n");

	क्रम (i = 0; i < pmc->soc->num_घातergates; i++) अणु
		status = tegra_घातergate_is_घातered(pmc, i);
		अगर (status < 0)
			जारी;

		seq_म_लिखो(s, " %9s %7s\n", pmc->soc->घातergates[i],
			   status ? "yes" : "no");
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(घातergate);

अटल पूर्णांक tegra_घातergate_debugfs_init(व्योम)
अणु
	pmc->debugfs = debugfs_create_file("powergate", S_IRUGO, शून्य, शून्य,
					   &घातergate_fops);
	अगर (!pmc->debugfs)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_घातergate_of_get_clks(काष्ठा tegra_घातergate *pg,
				       काष्ठा device_node *np)
अणु
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i, count;
	पूर्णांक err;

	count = of_clk_get_parent_count(np);
	अगर (count == 0)
		वापस -ENODEV;

	pg->clks = kसुस्मृति(count, माप(clk), GFP_KERNEL);
	अगर (!pg->clks)
		वापस -ENOMEM;

	pg->clk_rates = kसुस्मृति(count, माप(*pg->clk_rates), GFP_KERNEL);
	अगर (!pg->clk_rates) अणु
		kमुक्त(pg->clks);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		pg->clks[i] = of_clk_get(np, i);
		अगर (IS_ERR(pg->clks[i])) अणु
			err = PTR_ERR(pg->clks[i]);
			जाओ err;
		पूर्ण
	पूर्ण

	pg->num_clks = count;

	वापस 0;

err:
	जबतक (i--)
		clk_put(pg->clks[i]);

	kमुक्त(pg->clk_rates);
	kमुक्त(pg->clks);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_घातergate_of_get_resets(काष्ठा tegra_घातergate *pg,
					 काष्ठा device_node *np, bool off)
अणु
	काष्ठा device *dev = pg->pmc->dev;
	पूर्णांक err;

	pg->reset = of_reset_control_array_get_exclusive_released(np);
	अगर (IS_ERR(pg->reset)) अणु
		err = PTR_ERR(pg->reset);
		dev_err(dev, "failed to get device resets: %d\n", err);
		वापस err;
	पूर्ण

	err = reset_control_acquire(pg->reset);
	अगर (err < 0) अणु
		pr_err("failed to acquire resets: %d\n", err);
		जाओ out;
	पूर्ण

	अगर (off) अणु
		err = reset_control_निश्चित(pg->reset);
	पूर्ण अन्यथा अणु
		err = reset_control_deनिश्चित(pg->reset);
		अगर (err < 0)
			जाओ out;

		reset_control_release(pg->reset);
	पूर्ण

out:
	अगर (err) अणु
		reset_control_release(pg->reset);
		reset_control_put(pg->reset);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक tegra_घातergate_add(काष्ठा tegra_pmc *pmc, काष्ठा device_node *np)
अणु
	काष्ठा device *dev = pmc->dev;
	काष्ठा tegra_घातergate *pg;
	पूर्णांक id, err = 0;
	bool off;

	pg = kzalloc(माप(*pg), GFP_KERNEL);
	अगर (!pg)
		वापस -ENOMEM;

	id = tegra_घातergate_lookup(pmc, np->name);
	अगर (id < 0) अणु
		dev_err(dev, "powergate lookup failed for %pOFn: %d\n", np, id);
		err = -ENODEV;
		जाओ मुक्त_mem;
	पूर्ण

	/*
	 * Clear the bit क्रम this घातergate so it cannot be managed
	 * directly via the legacy APIs क्रम controlling घातergates.
	 */
	clear_bit(id, pmc->घातergates_available);

	pg->id = id;
	pg->genpd.name = np->name;
	pg->genpd.घातer_off = tegra_genpd_घातer_off;
	pg->genpd.घातer_on = tegra_genpd_घातer_on;
	pg->pmc = pmc;

	off = !tegra_घातergate_is_घातered(pmc, pg->id);

	err = tegra_घातergate_of_get_clks(pg, np);
	अगर (err < 0) अणु
		dev_err(dev, "failed to get clocks for %pOFn: %d\n", np, err);
		जाओ set_available;
	पूर्ण

	err = tegra_घातergate_of_get_resets(pg, np, off);
	अगर (err < 0) अणु
		dev_err(dev, "failed to get resets for %pOFn: %d\n", np, err);
		जाओ हटाओ_clks;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_PM_GENERIC_DOMAINS)) अणु
		अगर (off)
			WARN_ON(tegra_घातergate_घातer_up(pg, true));

		जाओ हटाओ_resets;
	पूर्ण

	err = pm_genpd_init(&pg->genpd, शून्य, off);
	अगर (err < 0) अणु
		dev_err(dev, "failed to initialise PM domain %pOFn: %d\n", np,
		       err);
		जाओ हटाओ_resets;
	पूर्ण

	err = of_genpd_add_provider_simple(np, &pg->genpd);
	अगर (err < 0) अणु
		dev_err(dev, "failed to add PM domain provider for %pOFn: %d\n",
			np, err);
		जाओ हटाओ_genpd;
	पूर्ण

	dev_dbg(dev, "added PM domain %s\n", pg->genpd.name);

	वापस 0;

हटाओ_genpd:
	pm_genpd_हटाओ(&pg->genpd);

हटाओ_resets:
	reset_control_put(pg->reset);

हटाओ_clks:
	जबतक (pg->num_clks--)
		clk_put(pg->clks[pg->num_clks]);

	kमुक्त(pg->clks);

set_available:
	set_bit(id, pmc->घातergates_available);

मुक्त_mem:
	kमुक्त(pg);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_घातergate_init(काष्ठा tegra_pmc *pmc,
				काष्ठा device_node *parent)
अणु
	काष्ठा device_node *np, *child;
	पूर्णांक err = 0;

	np = of_get_child_by_name(parent, "powergates");
	अगर (!np)
		वापस 0;

	क्रम_each_child_of_node(np, child) अणु
		err = tegra_घातergate_add(pmc, child);
		अगर (err < 0) अणु
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण

	of_node_put(np);

	वापस err;
पूर्ण

अटल व्योम tegra_घातergate_हटाओ(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा tegra_घातergate *pg = to_घातergate(genpd);

	reset_control_put(pg->reset);

	जबतक (pg->num_clks--)
		clk_put(pg->clks[pg->num_clks]);

	kमुक्त(pg->clks);

	set_bit(pg->id, pmc->घातergates_available);

	kमुक्त(pg);
पूर्ण

अटल व्योम tegra_घातergate_हटाओ_all(काष्ठा device_node *parent)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	काष्ठा device_node *np, *child;

	np = of_get_child_by_name(parent, "powergates");
	अगर (!np)
		वापस;

	क्रम_each_child_of_node(np, child) अणु
		of_genpd_del_provider(child);

		genpd = of_genpd_हटाओ_last(child);
		अगर (IS_ERR(genpd))
			जारी;

		tegra_घातergate_हटाओ(genpd);
	पूर्ण

	of_node_put(np);
पूर्ण

अटल स्थिर काष्ठा tegra_io_pad_soc *
tegra_io_pad_find(काष्ठा tegra_pmc *pmc, क्रमागत tegra_io_pad id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pmc->soc->num_io_pads; i++)
		अगर (pmc->soc->io_pads[i].id == id)
			वापस &pmc->soc->io_pads[i];

	वापस शून्य;
पूर्ण

अटल पूर्णांक tegra_io_pad_get_dpd_रेजिस्टर_bit(काष्ठा tegra_pmc *pmc,
					     क्रमागत tegra_io_pad id,
					     अचिन्हित दीर्घ *request,
					     अचिन्हित दीर्घ *status,
					     u32 *mask)
अणु
	स्थिर काष्ठा tegra_io_pad_soc *pad;

	pad = tegra_io_pad_find(pmc, id);
	अगर (!pad) अणु
		dev_err(pmc->dev, "invalid I/O pad ID %u\n", id);
		वापस -ENOENT;
	पूर्ण

	अगर (pad->dpd == अच_पूर्णांक_उच्च)
		वापस -ENOTSUPP;

	*mask = BIT(pad->dpd % 32);

	अगर (pad->dpd < 32) अणु
		*status = pmc->soc->regs->dpd_status;
		*request = pmc->soc->regs->dpd_req;
	पूर्ण अन्यथा अणु
		*status = pmc->soc->regs->dpd2_status;
		*request = pmc->soc->regs->dpd2_req;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_io_pad_prepare(काष्ठा tegra_pmc *pmc, क्रमागत tegra_io_pad id,
				अचिन्हित दीर्घ *request, अचिन्हित दीर्घ *status,
				u32 *mask)
अणु
	अचिन्हित दीर्घ rate, value;
	पूर्णांक err;

	err = tegra_io_pad_get_dpd_रेजिस्टर_bit(pmc, id, request, status, mask);
	अगर (err)
		वापस err;

	अगर (pmc->clk) अणु
		rate = pmc->rate;
		अगर (!rate) अणु
			dev_err(pmc->dev, "failed to get clock rate\n");
			वापस -ENODEV;
		पूर्ण

		tegra_pmc_ग_लिखोl(pmc, DPD_SAMPLE_ENABLE, DPD_SAMPLE);

		/* must be at least 200 ns, in APB (PCLK) घड़ी cycles */
		value = DIV_ROUND_UP(1000000000, rate);
		value = DIV_ROUND_UP(200, value);
		tegra_pmc_ग_लिखोl(pmc, value, SEL_DPD_TIM);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_io_pad_poll(काष्ठा tegra_pmc *pmc, अचिन्हित दीर्घ offset,
			     u32 mask, u32 val, अचिन्हित दीर्घ समयout)
अणु
	u32 value;

	समयout = jअगरfies + msecs_to_jअगरfies(समयout);

	जबतक (समय_after(समयout, jअगरfies)) अणु
		value = tegra_pmc_पढ़ोl(pmc, offset);
		अगर ((value & mask) == val)
			वापस 0;

		usleep_range(250, 1000);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम tegra_io_pad_unprepare(काष्ठा tegra_pmc *pmc)
अणु
	अगर (pmc->clk)
		tegra_pmc_ग_लिखोl(pmc, DPD_SAMPLE_DISABLE, DPD_SAMPLE);
पूर्ण

/**
 * tegra_io_pad_घातer_enable() - enable घातer to I/O pad
 * @id: Tegra I/O pad ID क्रम which to enable घातer
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक tegra_io_pad_घातer_enable(क्रमागत tegra_io_pad id)
अणु
	अचिन्हित दीर्घ request, status;
	u32 mask;
	पूर्णांक err;

	mutex_lock(&pmc->घातergates_lock);

	err = tegra_io_pad_prepare(pmc, id, &request, &status, &mask);
	अगर (err < 0) अणु
		dev_err(pmc->dev, "failed to prepare I/O pad: %d\n", err);
		जाओ unlock;
	पूर्ण

	tegra_pmc_ग_लिखोl(pmc, IO_DPD_REQ_CODE_OFF | mask, request);

	err = tegra_io_pad_poll(pmc, status, mask, 0, 250);
	अगर (err < 0) अणु
		dev_err(pmc->dev, "failed to enable I/O pad: %d\n", err);
		जाओ unlock;
	पूर्ण

	tegra_io_pad_unprepare(pmc);

unlock:
	mutex_unlock(&pmc->घातergates_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(tegra_io_pad_घातer_enable);

/**
 * tegra_io_pad_घातer_disable() - disable घातer to I/O pad
 * @id: Tegra I/O pad ID क्रम which to disable घातer
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक tegra_io_pad_घातer_disable(क्रमागत tegra_io_pad id)
अणु
	अचिन्हित दीर्घ request, status;
	u32 mask;
	पूर्णांक err;

	mutex_lock(&pmc->घातergates_lock);

	err = tegra_io_pad_prepare(pmc, id, &request, &status, &mask);
	अगर (err < 0) अणु
		dev_err(pmc->dev, "failed to prepare I/O pad: %d\n", err);
		जाओ unlock;
	पूर्ण

	tegra_pmc_ग_लिखोl(pmc, IO_DPD_REQ_CODE_ON | mask, request);

	err = tegra_io_pad_poll(pmc, status, mask, mask, 250);
	अगर (err < 0) अणु
		dev_err(pmc->dev, "failed to disable I/O pad: %d\n", err);
		जाओ unlock;
	पूर्ण

	tegra_io_pad_unprepare(pmc);

unlock:
	mutex_unlock(&pmc->घातergates_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(tegra_io_pad_घातer_disable);

अटल पूर्णांक tegra_io_pad_is_घातered(काष्ठा tegra_pmc *pmc, क्रमागत tegra_io_pad id)
अणु
	अचिन्हित दीर्घ request, status;
	u32 mask, value;
	पूर्णांक err;

	err = tegra_io_pad_get_dpd_रेजिस्टर_bit(pmc, id, &request, &status,
						&mask);
	अगर (err)
		वापस err;

	value = tegra_pmc_पढ़ोl(pmc, status);

	वापस !(value & mask);
पूर्ण

अटल पूर्णांक tegra_io_pad_set_voltage(काष्ठा tegra_pmc *pmc, क्रमागत tegra_io_pad id,
				    पूर्णांक voltage)
अणु
	स्थिर काष्ठा tegra_io_pad_soc *pad;
	u32 value;

	pad = tegra_io_pad_find(pmc, id);
	अगर (!pad)
		वापस -ENOENT;

	अगर (pad->voltage == अच_पूर्णांक_उच्च)
		वापस -ENOTSUPP;

	mutex_lock(&pmc->घातergates_lock);

	अगर (pmc->soc->has_impl_33v_pwr) अणु
		value = tegra_pmc_पढ़ोl(pmc, PMC_IMPL_E_33V_PWR);

		अगर (voltage == TEGRA_IO_PAD_VOLTAGE_1V8)
			value &= ~BIT(pad->voltage);
		अन्यथा
			value |= BIT(pad->voltage);

		tegra_pmc_ग_लिखोl(pmc, value, PMC_IMPL_E_33V_PWR);
	पूर्ण अन्यथा अणु
		/* ग_लिखो-enable PMC_PWR_DET_VALUE[pad->voltage] */
		value = tegra_pmc_पढ़ोl(pmc, PMC_PWR_DET);
		value |= BIT(pad->voltage);
		tegra_pmc_ग_लिखोl(pmc, value, PMC_PWR_DET);

		/* update I/O voltage */
		value = tegra_pmc_पढ़ोl(pmc, PMC_PWR_DET_VALUE);

		अगर (voltage == TEGRA_IO_PAD_VOLTAGE_1V8)
			value &= ~BIT(pad->voltage);
		अन्यथा
			value |= BIT(pad->voltage);

		tegra_pmc_ग_लिखोl(pmc, value, PMC_PWR_DET_VALUE);
	पूर्ण

	mutex_unlock(&pmc->घातergates_lock);

	usleep_range(100, 250);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_io_pad_get_voltage(काष्ठा tegra_pmc *pmc, क्रमागत tegra_io_pad id)
अणु
	स्थिर काष्ठा tegra_io_pad_soc *pad;
	u32 value;

	pad = tegra_io_pad_find(pmc, id);
	अगर (!pad)
		वापस -ENOENT;

	अगर (pad->voltage == अच_पूर्णांक_उच्च)
		वापस -ENOTSUPP;

	अगर (pmc->soc->has_impl_33v_pwr)
		value = tegra_pmc_पढ़ोl(pmc, PMC_IMPL_E_33V_PWR);
	अन्यथा
		value = tegra_pmc_पढ़ोl(pmc, PMC_PWR_DET_VALUE);

	अगर ((value & BIT(pad->voltage)) == 0)
		वापस TEGRA_IO_PAD_VOLTAGE_1V8;

	वापस TEGRA_IO_PAD_VOLTAGE_3V3;
पूर्ण

/**
 * tegra_io_rail_घातer_on() - enable घातer to I/O rail
 * @id: Tegra I/O pad ID क्रम which to enable घातer
 *
 * See also: tegra_io_pad_घातer_enable()
 */
पूर्णांक tegra_io_rail_घातer_on(अचिन्हित पूर्णांक id)
अणु
	वापस tegra_io_pad_घातer_enable(id);
पूर्ण
EXPORT_SYMBOL(tegra_io_rail_घातer_on);

/**
 * tegra_io_rail_घातer_off() - disable घातer to I/O rail
 * @id: Tegra I/O pad ID क्रम which to disable घातer
 *
 * See also: tegra_io_pad_घातer_disable()
 */
पूर्णांक tegra_io_rail_घातer_off(अचिन्हित पूर्णांक id)
अणु
	वापस tegra_io_pad_घातer_disable(id);
पूर्ण
EXPORT_SYMBOL(tegra_io_rail_घातer_off);

#अगर_घोषित CONFIG_PM_SLEEP
क्रमागत tegra_suspend_mode tegra_pmc_get_suspend_mode(व्योम)
अणु
	वापस pmc->suspend_mode;
पूर्ण

व्योम tegra_pmc_set_suspend_mode(क्रमागत tegra_suspend_mode mode)
अणु
	अगर (mode < TEGRA_SUSPEND_NONE || mode >= TEGRA_MAX_SUSPEND_MODE)
		वापस;

	pmc->suspend_mode = mode;
पूर्ण

व्योम tegra_pmc_enter_suspend_mode(क्रमागत tegra_suspend_mode mode)
अणु
	अचिन्हित दीर्घ दीर्घ rate = 0;
	u64 ticks;
	u32 value;

	चयन (mode) अणु
	हाल TEGRA_SUSPEND_LP1:
		rate = 32768;
		अवरोध;

	हाल TEGRA_SUSPEND_LP2:
		rate = pmc->rate;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (WARN_ON_ONCE(rate == 0))
		rate = 100000000;

	ticks = pmc->cpu_good_समय * rate + USEC_PER_SEC - 1;
	करो_भाग(ticks, USEC_PER_SEC);
	tegra_pmc_ग_लिखोl(pmc, ticks, PMC_CPUPWRGOOD_TIMER);

	ticks = pmc->cpu_off_समय * rate + USEC_PER_SEC - 1;
	करो_भाग(ticks, USEC_PER_SEC);
	tegra_pmc_ग_लिखोl(pmc, ticks, PMC_CPUPWROFF_TIMER);

	value = tegra_pmc_पढ़ोl(pmc, PMC_CNTRL);
	value &= ~PMC_CNTRL_SIDE_EFFECT_LP0;
	value |= PMC_CNTRL_CPU_PWRREQ_OE;
	tegra_pmc_ग_लिखोl(pmc, value, PMC_CNTRL);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tegra_pmc_parse_dt(काष्ठा tegra_pmc *pmc, काष्ठा device_node *np)
अणु
	u32 value, values[2];

	अगर (of_property_पढ़ो_u32(np, "nvidia,suspend-mode", &value)) अणु
	पूर्ण अन्यथा अणु
		चयन (value) अणु
		हाल 0:
			pmc->suspend_mode = TEGRA_SUSPEND_LP0;
			अवरोध;

		हाल 1:
			pmc->suspend_mode = TEGRA_SUSPEND_LP1;
			अवरोध;

		हाल 2:
			pmc->suspend_mode = TEGRA_SUSPEND_LP2;
			अवरोध;

		शेष:
			pmc->suspend_mode = TEGRA_SUSPEND_NONE;
			अवरोध;
		पूर्ण
	पूर्ण

	pmc->suspend_mode = tegra_pm_validate_suspend_mode(pmc->suspend_mode);

	अगर (of_property_पढ़ो_u32(np, "nvidia,cpu-pwr-good-time", &value))
		pmc->suspend_mode = TEGRA_SUSPEND_NONE;

	pmc->cpu_good_समय = value;

	अगर (of_property_पढ़ो_u32(np, "nvidia,cpu-pwr-off-time", &value))
		pmc->suspend_mode = TEGRA_SUSPEND_NONE;

	pmc->cpu_off_समय = value;

	अगर (of_property_पढ़ो_u32_array(np, "nvidia,core-pwr-good-time",
				       values, ARRAY_SIZE(values)))
		pmc->suspend_mode = TEGRA_SUSPEND_NONE;

	pmc->core_osc_समय = values[0];
	pmc->core_pmu_समय = values[1];

	अगर (of_property_पढ़ो_u32(np, "nvidia,core-pwr-off-time", &value))
		pmc->suspend_mode = TEGRA_SUSPEND_NONE;

	pmc->core_off_समय = value;

	pmc->corereq_high = of_property_पढ़ो_bool(np,
				"nvidia,core-power-req-active-high");

	pmc->sysclkreq_high = of_property_पढ़ो_bool(np,
				"nvidia,sys-clock-req-active-high");

	pmc->combined_req = of_property_पढ़ो_bool(np,
				"nvidia,combined-power-req");

	pmc->cpu_pwr_good_en = of_property_पढ़ो_bool(np,
				"nvidia,cpu-pwr-good-en");

	अगर (of_property_पढ़ो_u32_array(np, "nvidia,lp0-vec", values,
				       ARRAY_SIZE(values)))
		अगर (pmc->suspend_mode == TEGRA_SUSPEND_LP0)
			pmc->suspend_mode = TEGRA_SUSPEND_LP1;

	pmc->lp0_vec_phys = values[0];
	pmc->lp0_vec_size = values[1];

	वापस 0;
पूर्ण

अटल व्योम tegra_pmc_init(काष्ठा tegra_pmc *pmc)
अणु
	अगर (pmc->soc->init)
		pmc->soc->init(pmc);
पूर्ण

अटल व्योम tegra_pmc_init_tsense_reset(काष्ठा tegra_pmc *pmc)
अणु
	अटल स्थिर अक्षर disabled[] = "emergency thermal reset disabled";
	u32 pmu_addr, ctrl_id, reg_addr, reg_data, pinmux;
	काष्ठा device *dev = pmc->dev;
	काष्ठा device_node *np;
	u32 value, checksum;

	अगर (!pmc->soc->has_tsense_reset)
		वापस;

	np = of_get_child_by_name(pmc->dev->of_node, "i2c-thermtrip");
	अगर (!np) अणु
		dev_warn(dev, "i2c-thermtrip node not found, %s.\n", disabled);
		वापस;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "nvidia,i2c-controller-id", &ctrl_id)) अणु
		dev_err(dev, "I2C controller ID missing, %s.\n", disabled);
		जाओ out;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "nvidia,bus-addr", &pmu_addr)) अणु
		dev_err(dev, "nvidia,bus-addr missing, %s.\n", disabled);
		जाओ out;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "nvidia,reg-addr", &reg_addr)) अणु
		dev_err(dev, "nvidia,reg-addr missing, %s.\n", disabled);
		जाओ out;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "nvidia,reg-data", &reg_data)) अणु
		dev_err(dev, "nvidia,reg-data missing, %s.\n", disabled);
		जाओ out;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "nvidia,pinmux-id", &pinmux))
		pinmux = 0;

	value = tegra_pmc_पढ़ोl(pmc, PMC_SENSOR_CTRL);
	value |= PMC_SENSOR_CTRL_SCRATCH_WRITE;
	tegra_pmc_ग_लिखोl(pmc, value, PMC_SENSOR_CTRL);

	value = (reg_data << PMC_SCRATCH54_DATA_SHIFT) |
		(reg_addr << PMC_SCRATCH54_ADDR_SHIFT);
	tegra_pmc_ग_लिखोl(pmc, value, PMC_SCRATCH54);

	value = PMC_SCRATCH55_RESET_TEGRA;
	value |= ctrl_id << PMC_SCRATCH55_CNTRL_ID_SHIFT;
	value |= pinmux << PMC_SCRATCH55_PINMUX_SHIFT;
	value |= pmu_addr << PMC_SCRATCH55_I2CSLV1_SHIFT;

	/*
	 * Calculate checksum of SCRATCH54, SCRATCH55 fields. Bits 23:16 will
	 * contain the checksum and are currently zero, so they are not added.
	 */
	checksum = reg_addr + reg_data + (value & 0xff) + ((value >> 8) & 0xff)
		+ ((value >> 24) & 0xff);
	checksum &= 0xff;
	checksum = 0x100 - checksum;

	value |= checksum << PMC_SCRATCH55_CHECKSUM_SHIFT;

	tegra_pmc_ग_लिखोl(pmc, value, PMC_SCRATCH55);

	value = tegra_pmc_पढ़ोl(pmc, PMC_SENSOR_CTRL);
	value |= PMC_SENSOR_CTRL_ENABLE_RST;
	tegra_pmc_ग_लिखोl(pmc, value, PMC_SENSOR_CTRL);

	dev_info(pmc->dev, "emergency thermal reset enabled\n");

out:
	of_node_put(np);
पूर्ण

अटल पूर्णांक tegra_io_pad_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctl_dev)
अणु
	काष्ठा tegra_pmc *pmc = pinctrl_dev_get_drvdata(pctl_dev);

	वापस pmc->soc->num_io_pads;
पूर्ण

अटल स्थिर अक्षर *tegra_io_pad_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctl,
						       अचिन्हित पूर्णांक group)
अणु
	काष्ठा tegra_pmc *pmc = pinctrl_dev_get_drvdata(pctl);

	वापस pmc->soc->io_pads[group].name;
पूर्ण

अटल पूर्णांक tegra_io_pad_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctl_dev,
					       अचिन्हित पूर्णांक group,
					       स्थिर अचिन्हित पूर्णांक **pins,
					       अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा tegra_pmc *pmc = pinctrl_dev_get_drvdata(pctl_dev);

	*pins = &pmc->soc->io_pads[group].id;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops tegra_io_pad_pinctrl_ops = अणु
	.get_groups_count = tegra_io_pad_pinctrl_get_groups_count,
	.get_group_name = tegra_io_pad_pinctrl_get_group_name,
	.get_group_pins = tegra_io_pad_pinctrl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinconf_generic_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक tegra_io_pad_pinconf_get(काष्ठा pinctrl_dev *pctl_dev,
				    अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	काष्ठा tegra_pmc *pmc = pinctrl_dev_get_drvdata(pctl_dev);
	स्थिर काष्ठा tegra_io_pad_soc *pad;
	पूर्णांक ret;
	u32 arg;

	pad = tegra_io_pad_find(pmc, pin);
	अगर (!pad)
		वापस -EINVAL;

	चयन (param) अणु
	हाल PIN_CONFIG_POWER_SOURCE:
		ret = tegra_io_pad_get_voltage(pmc, pad->id);
		अगर (ret < 0)
			वापस ret;

		arg = ret;
		अवरोध;

	हाल PIN_CONFIG_MODE_LOW_POWER:
		ret = tegra_io_pad_is_घातered(pmc, pad->id);
		अगर (ret < 0)
			वापस ret;

		arg = !ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_io_pad_pinconf_set(काष्ठा pinctrl_dev *pctl_dev,
				    अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *configs,
				    अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा tegra_pmc *pmc = pinctrl_dev_get_drvdata(pctl_dev);
	स्थिर काष्ठा tegra_io_pad_soc *pad;
	क्रमागत pin_config_param param;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	u32 arg;

	pad = tegra_io_pad_find(pmc, pin);
	अगर (!pad)
		वापस -EINVAL;

	क्रम (i = 0; i < num_configs; ++i) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_MODE_LOW_POWER:
			अगर (arg)
				err = tegra_io_pad_घातer_disable(pad->id);
			अन्यथा
				err = tegra_io_pad_घातer_enable(pad->id);
			अगर (err)
				वापस err;
			अवरोध;
		हाल PIN_CONFIG_POWER_SOURCE:
			अगर (arg != TEGRA_IO_PAD_VOLTAGE_1V8 &&
			    arg != TEGRA_IO_PAD_VOLTAGE_3V3)
				वापस -EINVAL;
			err = tegra_io_pad_set_voltage(pmc, pad->id, arg);
			अगर (err)
				वापस err;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops tegra_io_pad_pinconf_ops = अणु
	.pin_config_get = tegra_io_pad_pinconf_get,
	.pin_config_set = tegra_io_pad_pinconf_set,
	.is_generic = true,
पूर्ण;

अटल काष्ठा pinctrl_desc tegra_pmc_pctl_desc = अणु
	.pctlops = &tegra_io_pad_pinctrl_ops,
	.confops = &tegra_io_pad_pinconf_ops,
पूर्ण;

अटल पूर्णांक tegra_pmc_pinctrl_init(काष्ठा tegra_pmc *pmc)
अणु
	पूर्णांक err;

	अगर (!pmc->soc->num_pin_descs)
		वापस 0;

	tegra_pmc_pctl_desc.name = dev_name(pmc->dev);
	tegra_pmc_pctl_desc.pins = pmc->soc->pin_descs;
	tegra_pmc_pctl_desc.npins = pmc->soc->num_pin_descs;

	pmc->pctl_dev = devm_pinctrl_रेजिस्टर(pmc->dev, &tegra_pmc_pctl_desc,
					      pmc);
	अगर (IS_ERR(pmc->pctl_dev)) अणु
		err = PTR_ERR(pmc->pctl_dev);
		dev_err(pmc->dev, "failed to register pin controller: %d\n",
			err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार reset_reason_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 value;

	value = tegra_pmc_पढ़ोl(pmc, pmc->soc->regs->rst_status);
	value &= pmc->soc->regs->rst_source_mask;
	value >>= pmc->soc->regs->rst_source_shअगरt;

	अगर (WARN_ON(value >= pmc->soc->num_reset_sources))
		वापस प्र_लिखो(buf, "%s\n", "UNKNOWN");

	वापस प्र_लिखो(buf, "%s\n", pmc->soc->reset_sources[value]);
पूर्ण

अटल DEVICE_ATTR_RO(reset_reason);

अटल sमाप_प्रकार reset_level_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 value;

	value = tegra_pmc_पढ़ोl(pmc, pmc->soc->regs->rst_status);
	value &= pmc->soc->regs->rst_level_mask;
	value >>= pmc->soc->regs->rst_level_shअगरt;

	अगर (WARN_ON(value >= pmc->soc->num_reset_levels))
		वापस प्र_लिखो(buf, "%s\n", "UNKNOWN");

	वापस प्र_लिखो(buf, "%s\n", pmc->soc->reset_levels[value]);
पूर्ण

अटल DEVICE_ATTR_RO(reset_level);

अटल व्योम tegra_pmc_reset_sysfs_init(काष्ठा tegra_pmc *pmc)
अणु
	काष्ठा device *dev = pmc->dev;
	पूर्णांक err = 0;

	अगर (pmc->soc->reset_sources) अणु
		err = device_create_file(dev, &dev_attr_reset_reason);
		अगर (err < 0)
			dev_warn(dev,
				 "failed to create attr \"reset_reason\": %d\n",
				 err);
	पूर्ण

	अगर (pmc->soc->reset_levels) अणु
		err = device_create_file(dev, &dev_attr_reset_level);
		अगर (err < 0)
			dev_warn(dev,
				 "failed to create attr \"reset_level\": %d\n",
				 err);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_pmc_irq_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
				   काष्ठा irq_fwspec *fwspec,
				   अचिन्हित दीर्घ *hwirq,
				   अचिन्हित पूर्णांक *type)
अणु
	अगर (WARN_ON(fwspec->param_count < 2))
		वापस -EINVAL;

	*hwirq = fwspec->param[0];
	*type = fwspec->param[1];

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pmc_irq_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			       अचिन्हित पूर्णांक num_irqs, व्योम *data)
अणु
	काष्ठा tegra_pmc *pmc = करोमुख्य->host_data;
	स्थिर काष्ठा tegra_pmc_soc *soc = pmc->soc;
	काष्ठा irq_fwspec *fwspec = data;
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	अगर (WARN_ON(num_irqs > 1))
		वापस -EINVAL;

	क्रम (i = 0; i < soc->num_wake_events; i++) अणु
		स्थिर काष्ठा tegra_wake_event *event = &soc->wake_events[i];

		अगर (fwspec->param_count == 2) अणु
			काष्ठा irq_fwspec spec;

			अगर (event->id != fwspec->param[0])
				जारी;

			err = irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq,
							    event->id,
							    &pmc->irq, pmc);
			अगर (err < 0)
				अवरोध;

			spec.fwnode = &pmc->dev->of_node->fwnode;
			spec.param_count = 3;
			spec.param[0] = GIC_SPI;
			spec.param[1] = event->irq;
			spec.param[2] = fwspec->param[1];

			err = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq,
							   num_irqs, &spec);

			अवरोध;
		पूर्ण

		अगर (fwspec->param_count == 3) अणु
			अगर (event->gpio.instance != fwspec->param[0] ||
			    event->gpio.pin != fwspec->param[1])
				जारी;

			err = irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq,
							    event->id,
							    &pmc->irq, pmc);

			/* GPIO hierarchies stop at the PMC level */
			अगर (!err && करोमुख्य->parent)
 				err = irq_करोमुख्य_disconnect_hierarchy(करोमुख्य->parent,
								      virq);
			अवरोध;
		पूर्ण
	पूर्ण

	/* If there is no wake-up event, there is no PMC mapping */
	अगर (i == soc->num_wake_events)
		err = irq_करोमुख्य_disconnect_hierarchy(करोमुख्य, virq);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops tegra_pmc_irq_करोमुख्य_ops = अणु
	.translate = tegra_pmc_irq_translate,
	.alloc = tegra_pmc_irq_alloc,
पूर्ण;

अटल पूर्णांक tegra210_pmc_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा tegra_pmc *pmc = irq_data_get_irq_chip_data(data);
	अचिन्हित पूर्णांक offset, bit;
	u32 value;

	offset = data->hwirq / 32;
	bit = data->hwirq % 32;

	/* clear wake status */
	tegra_pmc_ग_लिखोl(pmc, 0, PMC_SW_WAKE_STATUS);
	tegra_pmc_ग_लिखोl(pmc, 0, PMC_SW_WAKE2_STATUS);

	tegra_pmc_ग_लिखोl(pmc, 0, PMC_WAKE_STATUS);
	tegra_pmc_ग_लिखोl(pmc, 0, PMC_WAKE2_STATUS);

	/* enable PMC wake */
	अगर (data->hwirq >= 32)
		offset = PMC_WAKE2_MASK;
	अन्यथा
		offset = PMC_WAKE_MASK;

	value = tegra_pmc_पढ़ोl(pmc, offset);

	अगर (on)
		value |= BIT(bit);
	अन्यथा
		value &= ~BIT(bit);

	tegra_pmc_ग_लिखोl(pmc, value, offset);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_pmc_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा tegra_pmc *pmc = irq_data_get_irq_chip_data(data);
	अचिन्हित पूर्णांक offset, bit;
	u32 value;

	offset = data->hwirq / 32;
	bit = data->hwirq % 32;

	अगर (data->hwirq >= 32)
		offset = PMC_WAKE2_LEVEL;
	अन्यथा
		offset = PMC_WAKE_LEVEL;

	value = tegra_pmc_पढ़ोl(pmc, offset);

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_LEVEL_HIGH:
		value |= BIT(bit);
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_LEVEL_LOW:
		value &= ~BIT(bit);
		अवरोध;

	हाल IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING:
		value ^= BIT(bit);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	tegra_pmc_ग_लिखोl(pmc, value, offset);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_pmc_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा tegra_pmc *pmc = irq_data_get_irq_chip_data(data);
	अचिन्हित पूर्णांक offset, bit;
	u32 value;

	offset = data->hwirq / 32;
	bit = data->hwirq % 32;

	/* clear wake status */
	ग_लिखोl(0x1, pmc->wake + WAKE_AOWAKE_STATUS_W(data->hwirq));

	/* route wake to tier 2 */
	value = पढ़ोl(pmc->wake + WAKE_AOWAKE_TIER2_ROUTING(offset));

	अगर (!on)
		value &= ~(1 << bit);
	अन्यथा
		value |= 1 << bit;

	ग_लिखोl(value, pmc->wake + WAKE_AOWAKE_TIER2_ROUTING(offset));

	/* enable wakeup event */
	ग_लिखोl(!!on, pmc->wake + WAKE_AOWAKE_MASK_W(data->hwirq));

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_pmc_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा tegra_pmc *pmc = irq_data_get_irq_chip_data(data);
	u32 value;

	value = पढ़ोl(pmc->wake + WAKE_AOWAKE_CNTRL(data->hwirq));

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_LEVEL_HIGH:
		value |= WAKE_AOWAKE_CNTRL_LEVEL;
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_LEVEL_LOW:
		value &= ~WAKE_AOWAKE_CNTRL_LEVEL;
		अवरोध;

	हाल IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING:
		value ^= WAKE_AOWAKE_CNTRL_LEVEL;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(value, pmc->wake + WAKE_AOWAKE_CNTRL(data->hwirq));

	वापस 0;
पूर्ण

अटल व्योम tegra_irq_mask_parent(काष्ठा irq_data *data)
अणु
	अगर (data->parent_data)
		irq_chip_mask_parent(data);
पूर्ण

अटल व्योम tegra_irq_unmask_parent(काष्ठा irq_data *data)
अणु
	अगर (data->parent_data)
		irq_chip_unmask_parent(data);
पूर्ण

अटल व्योम tegra_irq_eoi_parent(काष्ठा irq_data *data)
अणु
	अगर (data->parent_data)
		irq_chip_eoi_parent(data);
पूर्ण

अटल पूर्णांक tegra_irq_set_affinity_parent(काष्ठा irq_data *data,
					 स्थिर काष्ठा cpumask *dest,
					 bool क्रमce)
अणु
	अगर (data->parent_data)
		वापस irq_chip_set_affinity_parent(data, dest, क्रमce);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tegra_pmc_irq_init(काष्ठा tegra_pmc *pmc)
अणु
	काष्ठा irq_करोमुख्य *parent = शून्य;
	काष्ठा device_node *np;

	np = of_irq_find_parent(pmc->dev->of_node);
	अगर (np) अणु
		parent = irq_find_host(np);
		of_node_put(np);
	पूर्ण

	अगर (!parent)
		वापस 0;

	pmc->irq.name = dev_name(pmc->dev);
	pmc->irq.irq_mask = tegra_irq_mask_parent;
	pmc->irq.irq_unmask = tegra_irq_unmask_parent;
	pmc->irq.irq_eoi = tegra_irq_eoi_parent;
	pmc->irq.irq_set_affinity = tegra_irq_set_affinity_parent;
	pmc->irq.irq_set_type = pmc->soc->irq_set_type;
	pmc->irq.irq_set_wake = pmc->soc->irq_set_wake;

	pmc->करोमुख्य = irq_करोमुख्य_add_hierarchy(parent, 0, 96, pmc->dev->of_node,
					       &tegra_pmc_irq_करोमुख्य_ops, pmc);
	अगर (!pmc->करोमुख्य) अणु
		dev_err(pmc->dev, "failed to allocate domain\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pmc_clk_notअगरy_cb(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ action, व्योम *ptr)
अणु
	काष्ठा tegra_pmc *pmc = container_of(nb, काष्ठा tegra_pmc, clk_nb);
	काष्ठा clk_notअगरier_data *data = ptr;

	चयन (action) अणु
	हाल PRE_RATE_CHANGE:
		mutex_lock(&pmc->घातergates_lock);
		अवरोध;

	हाल POST_RATE_CHANGE:
		pmc->rate = data->new_rate;
		fallthrough;

	हाल ABORT_RATE_CHANGE:
		mutex_unlock(&pmc->घातergates_lock);
		अवरोध;

	शेष:
		WARN_ON_ONCE(1);
		वापस notअगरier_from_त्रुटि_सं(-EINVAL);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम pmc_clk_fence_udelay(u32 offset)
अणु
	tegra_pmc_पढ़ोl(pmc, offset);
	/* pmc clk propagation delay 2 us */
	udelay(2);
पूर्ण

अटल u8 pmc_clk_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा pmc_clk *clk = to_pmc_clk(hw);
	u32 val;

	val = tegra_pmc_पढ़ोl(pmc, clk->offs) >> clk->mux_shअगरt;
	val &= PMC_CLK_OUT_MUX_MASK;

	वापस val;
पूर्ण

अटल पूर्णांक pmc_clk_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा pmc_clk *clk = to_pmc_clk(hw);
	u32 val;

	val = tegra_pmc_पढ़ोl(pmc, clk->offs);
	val &= ~(PMC_CLK_OUT_MUX_MASK << clk->mux_shअगरt);
	val |= index << clk->mux_shअगरt;
	tegra_pmc_ग_लिखोl(pmc, val, clk->offs);
	pmc_clk_fence_udelay(clk->offs);

	वापस 0;
पूर्ण

अटल पूर्णांक pmc_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा pmc_clk *clk = to_pmc_clk(hw);
	u32 val;

	val = tegra_pmc_पढ़ोl(pmc, clk->offs) & BIT(clk->क्रमce_en_shअगरt);

	वापस val ? 1 : 0;
पूर्ण

अटल व्योम pmc_clk_set_state(अचिन्हित दीर्घ offs, u32 shअगरt, पूर्णांक state)
अणु
	u32 val;

	val = tegra_pmc_पढ़ोl(pmc, offs);
	val = state ? (val | BIT(shअगरt)) : (val & ~BIT(shअगरt));
	tegra_pmc_ग_लिखोl(pmc, val, offs);
	pmc_clk_fence_udelay(offs);
पूर्ण

अटल पूर्णांक pmc_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pmc_clk *clk = to_pmc_clk(hw);

	pmc_clk_set_state(clk->offs, clk->क्रमce_en_shअगरt, 1);

	वापस 0;
पूर्ण

अटल व्योम pmc_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pmc_clk *clk = to_pmc_clk(hw);

	pmc_clk_set_state(clk->offs, clk->क्रमce_en_shअगरt, 0);
पूर्ण

अटल स्थिर काष्ठा clk_ops pmc_clk_ops = अणु
	.get_parent = pmc_clk_mux_get_parent,
	.set_parent = pmc_clk_mux_set_parent,
	.determine_rate = __clk_mux_determine_rate,
	.is_enabled = pmc_clk_is_enabled,
	.enable = pmc_clk_enable,
	.disable = pmc_clk_disable,
पूर्ण;

अटल काष्ठा clk *
tegra_pmc_clk_out_रेजिस्टर(काष्ठा tegra_pmc *pmc,
			   स्थिर काष्ठा pmc_clk_init_data *data,
			   अचिन्हित दीर्घ offset)
अणु
	काष्ठा clk_init_data init;
	काष्ठा pmc_clk *pmc_clk;

	pmc_clk = devm_kzalloc(pmc->dev, माप(*pmc_clk), GFP_KERNEL);
	अगर (!pmc_clk)
		वापस ERR_PTR(-ENOMEM);

	init.name = data->name;
	init.ops = &pmc_clk_ops;
	init.parent_names = data->parents;
	init.num_parents = data->num_parents;
	init.flags = CLK_SET_RATE_NO_REPARENT | CLK_SET_RATE_PARENT |
		     CLK_SET_PARENT_GATE;

	pmc_clk->hw.init = &init;
	pmc_clk->offs = offset;
	pmc_clk->mux_shअगरt = data->mux_shअगरt;
	pmc_clk->क्रमce_en_shअगरt = data->क्रमce_en_shअगरt;

	वापस clk_रेजिस्टर(शून्य, &pmc_clk->hw);
पूर्ण

अटल पूर्णांक pmc_clk_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा pmc_clk_gate *gate = to_pmc_clk_gate(hw);

	वापस tegra_pmc_पढ़ोl(pmc, gate->offs) & BIT(gate->shअगरt) ? 1 : 0;
पूर्ण

अटल पूर्णांक pmc_clk_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pmc_clk_gate *gate = to_pmc_clk_gate(hw);

	pmc_clk_set_state(gate->offs, gate->shअगरt, 1);

	वापस 0;
पूर्ण

अटल व्योम pmc_clk_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा pmc_clk_gate *gate = to_pmc_clk_gate(hw);

	pmc_clk_set_state(gate->offs, gate->shअगरt, 0);
पूर्ण

अटल स्थिर काष्ठा clk_ops pmc_clk_gate_ops = अणु
	.is_enabled = pmc_clk_gate_is_enabled,
	.enable = pmc_clk_gate_enable,
	.disable = pmc_clk_gate_disable,
पूर्ण;

अटल काष्ठा clk *
tegra_pmc_clk_gate_रेजिस्टर(काष्ठा tegra_pmc *pmc, स्थिर अक्षर *name,
			    स्थिर अक्षर *parent_name, अचिन्हित दीर्घ offset,
			    u32 shअगरt)
अणु
	काष्ठा clk_init_data init;
	काष्ठा pmc_clk_gate *gate;

	gate = devm_kzalloc(pmc->dev, माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &pmc_clk_gate_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = 0;

	gate->hw.init = &init;
	gate->offs = offset;
	gate->shअगरt = shअगरt;

	वापस clk_रेजिस्टर(शून्य, &gate->hw);
पूर्ण

अटल व्योम tegra_pmc_घड़ी_रेजिस्टर(काष्ठा tegra_pmc *pmc,
				     काष्ठा device_node *np)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_onecell_data *clk_data;
	अचिन्हित पूर्णांक num_clks;
	पूर्णांक i, err;

	num_clks = pmc->soc->num_pmc_clks;
	अगर (pmc->soc->has_blink_output)
		num_clks += 1;

	अगर (!num_clks)
		वापस;

	clk_data = devm_kदो_स्मृति(pmc->dev, माप(*clk_data), GFP_KERNEL);
	अगर (!clk_data)
		वापस;

	clk_data->clks = devm_kसुस्मृति(pmc->dev, TEGRA_PMC_CLK_MAX,
				      माप(*clk_data->clks), GFP_KERNEL);
	अगर (!clk_data->clks)
		वापस;

	clk_data->clk_num = TEGRA_PMC_CLK_MAX;

	क्रम (i = 0; i < TEGRA_PMC_CLK_MAX; i++)
		clk_data->clks[i] = ERR_PTR(-ENOENT);

	क्रम (i = 0; i < pmc->soc->num_pmc_clks; i++) अणु
		स्थिर काष्ठा pmc_clk_init_data *data;

		data = pmc->soc->pmc_clks_data + i;

		clk = tegra_pmc_clk_out_रेजिस्टर(pmc, data, PMC_CLK_OUT_CNTRL);
		अगर (IS_ERR(clk)) अणु
			dev_warn(pmc->dev, "unable to register clock %s: %d\n",
				 data->name, PTR_ERR_OR_ZERO(clk));
			वापस;
		पूर्ण

		err = clk_रेजिस्टर_clkdev(clk, data->name, शून्य);
		अगर (err) अणु
			dev_warn(pmc->dev,
				 "unable to register %s clock lookup: %d\n",
				 data->name, err);
			वापस;
		पूर्ण

		clk_data->clks[data->clk_id] = clk;
	पूर्ण

	अगर (pmc->soc->has_blink_output) अणु
		tegra_pmc_ग_लिखोl(pmc, 0x0, PMC_BLINK_TIMER);
		clk = tegra_pmc_clk_gate_रेजिस्टर(pmc,
						  "pmc_blink_override",
						  "clk_32k",
						  PMC_DPD_PADS_ORIDE,
						  PMC_DPD_PADS_ORIDE_BLINK);
		अगर (IS_ERR(clk)) अणु
			dev_warn(pmc->dev,
				 "unable to register pmc_blink_override: %d\n",
				 PTR_ERR_OR_ZERO(clk));
			वापस;
		पूर्ण

		clk = tegra_pmc_clk_gate_रेजिस्टर(pmc, "pmc_blink",
						  "pmc_blink_override",
						  PMC_CNTRL,
						  PMC_CNTRL_BLINK_EN);
		अगर (IS_ERR(clk)) अणु
			dev_warn(pmc->dev,
				 "unable to register pmc_blink: %d\n",
				 PTR_ERR_OR_ZERO(clk));
			वापस;
		पूर्ण

		err = clk_रेजिस्टर_clkdev(clk, "pmc_blink", शून्य);
		अगर (err) अणु
			dev_warn(pmc->dev,
				 "unable to register pmc_blink lookup: %d\n",
				 err);
			वापस;
		पूर्ण

		clk_data->clks[TEGRA_PMC_CLK_BLINK] = clk;
	पूर्ण

	err = of_clk_add_provider(np, of_clk_src_onecell_get, clk_data);
	अगर (err)
		dev_warn(pmc->dev, "failed to add pmc clock provider: %d\n",
			 err);
पूर्ण

अटल स्थिर काष्ठा regmap_range pmc_usb_sleepwalk_ranges[] = अणु
	regmap_reg_range(PMC_USB_DEBOUNCE_DEL, PMC_USB_AO),
	regmap_reg_range(PMC_UTMIP_UHSIC_TRIGGERS, PMC_UTMIP_UHSIC_SAVED_STATE),
	regmap_reg_range(PMC_UTMIP_TERM_PAD_CFG, PMC_UTMIP_UHSIC_FAKE),
	regmap_reg_range(PMC_UTMIP_UHSIC_LINE_WAKEUP, PMC_UTMIP_UHSIC_LINE_WAKEUP),
	regmap_reg_range(PMC_UTMIP_BIAS_MASTER_CNTRL, PMC_UTMIP_MASTER_CONFIG),
	regmap_reg_range(PMC_UTMIP_UHSIC2_TRIGGERS, PMC_UTMIP_MASTER2_CONFIG),
	regmap_reg_range(PMC_UTMIP_PAD_CFG0, PMC_UTMIP_UHSIC_SLEEP_CFG1),
	regmap_reg_range(PMC_UTMIP_SLEEPWALK_P3, PMC_UTMIP_SLEEPWALK_P3),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table pmc_usb_sleepwalk_table = अणु
	.yes_ranges = pmc_usb_sleepwalk_ranges,
	.n_yes_ranges = ARRAY_SIZE(pmc_usb_sleepwalk_ranges),
पूर्ण;

अटल पूर्णांक tegra_pmc_regmap_पढ़ोl(व्योम *context, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक *value)
अणु
	काष्ठा tegra_pmc *pmc = context;

	*value = tegra_pmc_पढ़ोl(pmc, offset);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pmc_regmap_ग_लिखोl(व्योम *context, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक value)
अणु
	काष्ठा tegra_pmc *pmc = context;

	tegra_pmc_ग_लिखोl(pmc, value, offset);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config usb_sleepwalk_regmap_config = अणु
	.name = "usb_sleepwalk",
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.fast_io = true,
	.rd_table = &pmc_usb_sleepwalk_table,
	.wr_table = &pmc_usb_sleepwalk_table,
	.reg_पढ़ो = tegra_pmc_regmap_पढ़ोl,
	.reg_ग_लिखो = tegra_pmc_regmap_ग_लिखोl,
पूर्ण;

अटल पूर्णांक tegra_pmc_regmap_init(काष्ठा tegra_pmc *pmc)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक err;

	अगर (pmc->soc->has_usb_sleepwalk) अणु
		regmap = devm_regmap_init(pmc->dev, शून्य, pmc, &usb_sleepwalk_regmap_config);
		अगर (IS_ERR(regmap)) अणु
			err = PTR_ERR(regmap);
			dev_err(pmc->dev, "failed to allocate register map (%d)\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *base;
	काष्ठा resource *res;
	पूर्णांक err;

	/*
	 * Early initialisation should have configured an initial
	 * रेजिस्टर mapping and setup the soc data poपूर्णांकer. If these
	 * are not valid then something went badly wrong!
	 */
	अगर (WARN_ON(!pmc->base || !pmc->soc))
		वापस -ENODEV;

	err = tegra_pmc_parse_dt(pmc, pdev->dev.of_node);
	अगर (err < 0)
		वापस err;

	/* take over the memory region from the early initialization */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "wake");
	अगर (res) अणु
		pmc->wake = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(pmc->wake))
			वापस PTR_ERR(pmc->wake);
	पूर्ण अन्यथा अणु
		pmc->wake = base;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "aotag");
	अगर (res) अणु
		pmc->aotag = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(pmc->aotag))
			वापस PTR_ERR(pmc->aotag);
	पूर्ण अन्यथा अणु
		pmc->aotag = base;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "scratch");
	अगर (res) अणु
		pmc->scratch = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(pmc->scratch))
			वापस PTR_ERR(pmc->scratch);
	पूर्ण अन्यथा अणु
		pmc->scratch = base;
	पूर्ण

	pmc->clk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(pmc->clk)) अणु
		err = PTR_ERR(pmc->clk);

		अगर (err != -ENOENT) अणु
			dev_err(&pdev->dev, "failed to get pclk: %d\n", err);
			वापस err;
		पूर्ण

		pmc->clk = शून्य;
	पूर्ण

	/*
	 * PCLK घड़ी rate can't be retrieved using CLK API because it
	 * causes lockup अगर CPU enters LP2 idle state from some other
	 * CLK notअगरier, hence we're caching the rate's value locally.
	 */
	अगर (pmc->clk) अणु
		pmc->clk_nb.notअगरier_call = tegra_pmc_clk_notअगरy_cb;
		err = clk_notअगरier_रेजिस्टर(pmc->clk, &pmc->clk_nb);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"failed to register clk notifier\n");
			वापस err;
		पूर्ण

		pmc->rate = clk_get_rate(pmc->clk);
	पूर्ण

	pmc->dev = &pdev->dev;

	tegra_pmc_init(pmc);

	tegra_pmc_init_tsense_reset(pmc);

	tegra_pmc_reset_sysfs_init(pmc);

	अगर (IS_ENABLED(CONFIG_DEBUG_FS)) अणु
		err = tegra_घातergate_debugfs_init();
		अगर (err < 0)
			जाओ cleanup_sysfs;
	पूर्ण

	err = रेजिस्टर_restart_handler(&tegra_pmc_restart_handler);
	अगर (err) अणु
		dev_err(&pdev->dev, "unable to register restart handler, %d\n",
			err);
		जाओ cleanup_debugfs;
	पूर्ण

	err = tegra_pmc_pinctrl_init(pmc);
	अगर (err)
		जाओ cleanup_restart_handler;

	err = tegra_pmc_regmap_init(pmc);
	अगर (err < 0)
		जाओ cleanup_restart_handler;

	err = tegra_घातergate_init(pmc, pdev->dev.of_node);
	अगर (err < 0)
		जाओ cleanup_घातergates;

	err = tegra_pmc_irq_init(pmc);
	अगर (err < 0)
		जाओ cleanup_घातergates;

	mutex_lock(&pmc->घातergates_lock);
	iounmap(pmc->base);
	pmc->base = base;
	mutex_unlock(&pmc->घातergates_lock);

	tegra_pmc_घड़ी_रेजिस्टर(pmc, pdev->dev.of_node);
	platक्रमm_set_drvdata(pdev, pmc);

	वापस 0;

cleanup_घातergates:
	tegra_घातergate_हटाओ_all(pdev->dev.of_node);
cleanup_restart_handler:
	unरेजिस्टर_restart_handler(&tegra_pmc_restart_handler);
cleanup_debugfs:
	debugfs_हटाओ(pmc->debugfs);
cleanup_sysfs:
	device_हटाओ_file(&pdev->dev, &dev_attr_reset_reason);
	device_हटाओ_file(&pdev->dev, &dev_attr_reset_level);
	clk_notअगरier_unरेजिस्टर(pmc->clk, &pmc->clk_nb);

	वापस err;
पूर्ण

#अगर defined(CONFIG_PM_SLEEP) && defined(CONFIG_ARM)
अटल पूर्णांक tegra_pmc_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_pmc *pmc = dev_get_drvdata(dev);

	tegra_pmc_ग_लिखोl(pmc, virt_to_phys(tegra_resume), PMC_SCRATCH41);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pmc_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_pmc *pmc = dev_get_drvdata(dev);

	tegra_pmc_ग_लिखोl(pmc, 0x0, PMC_SCRATCH41);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tegra_pmc_pm_ops, tegra_pmc_suspend, tegra_pmc_resume);

#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर tegra20_घातergates[] = अणु
	[TEGRA_POWERGATE_CPU] = "cpu",
	[TEGRA_POWERGATE_3D] = "3d",
	[TEGRA_POWERGATE_VENC] = "venc",
	[TEGRA_POWERGATE_VDEC] = "vdec",
	[TEGRA_POWERGATE_PCIE] = "pcie",
	[TEGRA_POWERGATE_L2] = "l2",
	[TEGRA_POWERGATE_MPE] = "mpe",
पूर्ण;

अटल स्थिर काष्ठा tegra_pmc_regs tegra20_pmc_regs = अणु
	.scratch0 = 0x50,
	.dpd_req = 0x1b8,
	.dpd_status = 0x1bc,
	.dpd2_req = 0x1c0,
	.dpd2_status = 0x1c4,
	.rst_status = 0x1b4,
	.rst_source_shअगरt = 0x0,
	.rst_source_mask = 0x7,
	.rst_level_shअगरt = 0x0,
	.rst_level_mask = 0x0,
पूर्ण;

अटल व्योम tegra20_pmc_init(काष्ठा tegra_pmc *pmc)
अणु
	u32 value, osc, pmu, off;

	/* Always enable CPU घातer request */
	value = tegra_pmc_पढ़ोl(pmc, PMC_CNTRL);
	value |= PMC_CNTRL_CPU_PWRREQ_OE;
	tegra_pmc_ग_लिखोl(pmc, value, PMC_CNTRL);

	value = tegra_pmc_पढ़ोl(pmc, PMC_CNTRL);

	अगर (pmc->sysclkreq_high)
		value &= ~PMC_CNTRL_SYSCLK_POLARITY;
	अन्यथा
		value |= PMC_CNTRL_SYSCLK_POLARITY;

	अगर (pmc->corereq_high)
		value &= ~PMC_CNTRL_PWRREQ_POLARITY;
	अन्यथा
		value |= PMC_CNTRL_PWRREQ_POLARITY;

	/* configure the output polarity जबतक the request is tristated */
	tegra_pmc_ग_लिखोl(pmc, value, PMC_CNTRL);

	/* now enable the request */
	value = tegra_pmc_पढ़ोl(pmc, PMC_CNTRL);
	value |= PMC_CNTRL_SYSCLK_OE;
	tegra_pmc_ग_लिखोl(pmc, value, PMC_CNTRL);

	/* program core timings which are applicable only क्रम suspend state */
	अगर (pmc->suspend_mode != TEGRA_SUSPEND_NONE) अणु
		osc = DIV_ROUND_UP(pmc->core_osc_समय * 8192, 1000000);
		pmu = DIV_ROUND_UP(pmc->core_pmu_समय * 32768, 1000000);
		off = DIV_ROUND_UP(pmc->core_off_समय * 32768, 1000000);
		tegra_pmc_ग_लिखोl(pmc, ((osc << 8) & 0xff00) | (pmu & 0xff),
				 PMC_COREPWRGOOD_TIMER);
		tegra_pmc_ग_लिखोl(pmc, off, PMC_COREPWROFF_TIMER);
	पूर्ण
पूर्ण

अटल व्योम tegra20_pmc_setup_irq_polarity(काष्ठा tegra_pmc *pmc,
					   काष्ठा device_node *np,
					   bool invert)
अणु
	u32 value;

	value = tegra_pmc_पढ़ोl(pmc, PMC_CNTRL);

	अगर (invert)
		value |= PMC_CNTRL_INTR_POLARITY;
	अन्यथा
		value &= ~PMC_CNTRL_INTR_POLARITY;

	tegra_pmc_ग_लिखोl(pmc, value, PMC_CNTRL);
पूर्ण

अटल स्थिर काष्ठा tegra_pmc_soc tegra20_pmc_soc = अणु
	.num_घातergates = ARRAY_SIZE(tegra20_घातergates),
	.घातergates = tegra20_घातergates,
	.num_cpu_घातergates = 0,
	.cpu_घातergates = शून्य,
	.has_tsense_reset = false,
	.has_gpu_clamps = false,
	.needs_mbist_war = false,
	.has_impl_33v_pwr = false,
	.maybe_tz_only = false,
	.num_io_pads = 0,
	.io_pads = शून्य,
	.num_pin_descs = 0,
	.pin_descs = शून्य,
	.regs = &tegra20_pmc_regs,
	.init = tegra20_pmc_init,
	.setup_irq_polarity = tegra20_pmc_setup_irq_polarity,
	.घातergate_set = tegra20_घातergate_set,
	.reset_sources = शून्य,
	.num_reset_sources = 0,
	.reset_levels = शून्य,
	.num_reset_levels = 0,
	.pmc_clks_data = शून्य,
	.num_pmc_clks = 0,
	.has_blink_output = true,
	.has_usb_sleepwalk = false,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra30_घातergates[] = अणु
	[TEGRA_POWERGATE_CPU] = "cpu0",
	[TEGRA_POWERGATE_3D] = "3d0",
	[TEGRA_POWERGATE_VENC] = "venc",
	[TEGRA_POWERGATE_VDEC] = "vdec",
	[TEGRA_POWERGATE_PCIE] = "pcie",
	[TEGRA_POWERGATE_L2] = "l2",
	[TEGRA_POWERGATE_MPE] = "mpe",
	[TEGRA_POWERGATE_HEG] = "heg",
	[TEGRA_POWERGATE_SATA] = "sata",
	[TEGRA_POWERGATE_CPU1] = "cpu1",
	[TEGRA_POWERGATE_CPU2] = "cpu2",
	[TEGRA_POWERGATE_CPU3] = "cpu3",
	[TEGRA_POWERGATE_CELP] = "celp",
	[TEGRA_POWERGATE_3D1] = "3d1",
पूर्ण;

अटल स्थिर u8 tegra30_cpu_घातergates[] = अणु
	TEGRA_POWERGATE_CPU,
	TEGRA_POWERGATE_CPU1,
	TEGRA_POWERGATE_CPU2,
	TEGRA_POWERGATE_CPU3,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra30_reset_sources[] = अणु
	"POWER_ON_RESET",
	"WATCHDOG",
	"SENSOR",
	"SW_MAIN",
	"LP0"
पूर्ण;

अटल स्थिर काष्ठा tegra_pmc_soc tegra30_pmc_soc = अणु
	.num_घातergates = ARRAY_SIZE(tegra30_घातergates),
	.घातergates = tegra30_घातergates,
	.num_cpu_घातergates = ARRAY_SIZE(tegra30_cpu_घातergates),
	.cpu_घातergates = tegra30_cpu_घातergates,
	.has_tsense_reset = true,
	.has_gpu_clamps = false,
	.needs_mbist_war = false,
	.has_impl_33v_pwr = false,
	.maybe_tz_only = false,
	.num_io_pads = 0,
	.io_pads = शून्य,
	.num_pin_descs = 0,
	.pin_descs = शून्य,
	.regs = &tegra20_pmc_regs,
	.init = tegra20_pmc_init,
	.setup_irq_polarity = tegra20_pmc_setup_irq_polarity,
	.घातergate_set = tegra20_घातergate_set,
	.reset_sources = tegra30_reset_sources,
	.num_reset_sources = ARRAY_SIZE(tegra30_reset_sources),
	.reset_levels = शून्य,
	.num_reset_levels = 0,
	.pmc_clks_data = tegra_pmc_clks_data,
	.num_pmc_clks = ARRAY_SIZE(tegra_pmc_clks_data),
	.has_blink_output = true,
	.has_usb_sleepwalk = false,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra114_घातergates[] = अणु
	[TEGRA_POWERGATE_CPU] = "crail",
	[TEGRA_POWERGATE_3D] = "3d",
	[TEGRA_POWERGATE_VENC] = "venc",
	[TEGRA_POWERGATE_VDEC] = "vdec",
	[TEGRA_POWERGATE_MPE] = "mpe",
	[TEGRA_POWERGATE_HEG] = "heg",
	[TEGRA_POWERGATE_CPU1] = "cpu1",
	[TEGRA_POWERGATE_CPU2] = "cpu2",
	[TEGRA_POWERGATE_CPU3] = "cpu3",
	[TEGRA_POWERGATE_CELP] = "celp",
	[TEGRA_POWERGATE_CPU0] = "cpu0",
	[TEGRA_POWERGATE_C0NC] = "c0nc",
	[TEGRA_POWERGATE_C1NC] = "c1nc",
	[TEGRA_POWERGATE_DIS] = "dis",
	[TEGRA_POWERGATE_DISB] = "disb",
	[TEGRA_POWERGATE_XUSBA] = "xusba",
	[TEGRA_POWERGATE_XUSBB] = "xusbb",
	[TEGRA_POWERGATE_XUSBC] = "xusbc",
पूर्ण;

अटल स्थिर u8 tegra114_cpu_घातergates[] = अणु
	TEGRA_POWERGATE_CPU0,
	TEGRA_POWERGATE_CPU1,
	TEGRA_POWERGATE_CPU2,
	TEGRA_POWERGATE_CPU3,
पूर्ण;

अटल स्थिर काष्ठा tegra_pmc_soc tegra114_pmc_soc = अणु
	.num_घातergates = ARRAY_SIZE(tegra114_घातergates),
	.घातergates = tegra114_घातergates,
	.num_cpu_घातergates = ARRAY_SIZE(tegra114_cpu_घातergates),
	.cpu_घातergates = tegra114_cpu_घातergates,
	.has_tsense_reset = true,
	.has_gpu_clamps = false,
	.needs_mbist_war = false,
	.has_impl_33v_pwr = false,
	.maybe_tz_only = false,
	.num_io_pads = 0,
	.io_pads = शून्य,
	.num_pin_descs = 0,
	.pin_descs = शून्य,
	.regs = &tegra20_pmc_regs,
	.init = tegra20_pmc_init,
	.setup_irq_polarity = tegra20_pmc_setup_irq_polarity,
	.घातergate_set = tegra114_घातergate_set,
	.reset_sources = tegra30_reset_sources,
	.num_reset_sources = ARRAY_SIZE(tegra30_reset_sources),
	.reset_levels = शून्य,
	.num_reset_levels = 0,
	.pmc_clks_data = tegra_pmc_clks_data,
	.num_pmc_clks = ARRAY_SIZE(tegra_pmc_clks_data),
	.has_blink_output = true,
	.has_usb_sleepwalk = false,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_घातergates[] = अणु
	[TEGRA_POWERGATE_CPU] = "crail",
	[TEGRA_POWERGATE_3D] = "3d",
	[TEGRA_POWERGATE_VENC] = "venc",
	[TEGRA_POWERGATE_PCIE] = "pcie",
	[TEGRA_POWERGATE_VDEC] = "vdec",
	[TEGRA_POWERGATE_MPE] = "mpe",
	[TEGRA_POWERGATE_HEG] = "heg",
	[TEGRA_POWERGATE_SATA] = "sata",
	[TEGRA_POWERGATE_CPU1] = "cpu1",
	[TEGRA_POWERGATE_CPU2] = "cpu2",
	[TEGRA_POWERGATE_CPU3] = "cpu3",
	[TEGRA_POWERGATE_CELP] = "celp",
	[TEGRA_POWERGATE_CPU0] = "cpu0",
	[TEGRA_POWERGATE_C0NC] = "c0nc",
	[TEGRA_POWERGATE_C1NC] = "c1nc",
	[TEGRA_POWERGATE_SOR] = "sor",
	[TEGRA_POWERGATE_DIS] = "dis",
	[TEGRA_POWERGATE_DISB] = "disb",
	[TEGRA_POWERGATE_XUSBA] = "xusba",
	[TEGRA_POWERGATE_XUSBB] = "xusbb",
	[TEGRA_POWERGATE_XUSBC] = "xusbc",
	[TEGRA_POWERGATE_VIC] = "vic",
	[TEGRA_POWERGATE_IRAM] = "iram",
पूर्ण;

अटल स्थिर u8 tegra124_cpu_घातergates[] = अणु
	TEGRA_POWERGATE_CPU0,
	TEGRA_POWERGATE_CPU1,
	TEGRA_POWERGATE_CPU2,
	TEGRA_POWERGATE_CPU3,
पूर्ण;

#घोषणा TEGRA_IO_PAD(_id, _dpd, _voltage, _name)	\
	((काष्ठा tegra_io_pad_soc) अणु			\
		.id	= (_id),			\
		.dpd	= (_dpd),			\
		.voltage = (_voltage),			\
		.name	= (_name),			\
	पूर्ण)

#घोषणा TEGRA_IO_PIN_DESC(_id, _dpd, _voltage, _name)	\
	((काष्ठा pinctrl_pin_desc) अणु			\
		.number = (_id),			\
		.name	= (_name)			\
	पूर्ण)

#घोषणा TEGRA124_IO_PAD_TABLE(_pad)                                   \
	/* .id                          .dpd  .voltage  .name */      \
	_pad(TEGRA_IO_PAD_AUDIO,        17,   अच_पूर्णांक_उच्च, "audio"),     \
	_pad(TEGRA_IO_PAD_BB,           15,   अच_पूर्णांक_उच्च, "bb"),        \
	_pad(TEGRA_IO_PAD_CAM,          36,   अच_पूर्णांक_उच्च, "cam"),       \
	_pad(TEGRA_IO_PAD_COMP,         22,   अच_पूर्णांक_उच्च, "comp"),      \
	_pad(TEGRA_IO_PAD_CSIA,         0,    अच_पूर्णांक_उच्च, "csia"),      \
	_pad(TEGRA_IO_PAD_CSIB,         1,    अच_पूर्णांक_उच्च, "csb"),       \
	_pad(TEGRA_IO_PAD_CSIE,         44,   अच_पूर्णांक_उच्च, "cse"),       \
	_pad(TEGRA_IO_PAD_DSI,          2,    अच_पूर्णांक_उच्च, "dsi"),       \
	_pad(TEGRA_IO_PAD_DSIB,         39,   अच_पूर्णांक_उच्च, "dsib"),      \
	_pad(TEGRA_IO_PAD_DSIC,         40,   अच_पूर्णांक_उच्च, "dsic"),      \
	_pad(TEGRA_IO_PAD_DSID,         41,   अच_पूर्णांक_उच्च, "dsid"),      \
	_pad(TEGRA_IO_PAD_HDMI,         28,   अच_पूर्णांक_उच्च, "hdmi"),      \
	_pad(TEGRA_IO_PAD_HSIC,         19,   अच_पूर्णांक_उच्च, "hsic"),      \
	_pad(TEGRA_IO_PAD_HV,           38,   अच_पूर्णांक_उच्च, "hv"),        \
	_pad(TEGRA_IO_PAD_LVDS,         57,   अच_पूर्णांक_उच्च, "lvds"),      \
	_pad(TEGRA_IO_PAD_MIPI_BIAS,    3,    अच_पूर्णांक_उच्च, "mipi-bias"), \
	_pad(TEGRA_IO_PAD_न_अंकD,         13,   अच_पूर्णांक_उच्च, "nand"),      \
	_pad(TEGRA_IO_PAD_PEX_BIAS,     4,    अच_पूर्णांक_उच्च, "pex-bias"),  \
	_pad(TEGRA_IO_PAD_PEX_CLK1,     5,    अच_पूर्णांक_उच्च, "pex-clk1"),  \
	_pad(TEGRA_IO_PAD_PEX_CLK2,     6,    अच_पूर्णांक_उच्च, "pex-clk2"),  \
	_pad(TEGRA_IO_PAD_PEX_CNTRL,    32,   अच_पूर्णांक_उच्च, "pex-cntrl"), \
	_pad(TEGRA_IO_PAD_SDMMC1,       33,   अच_पूर्णांक_उच्च, "sdmmc1"),    \
	_pad(TEGRA_IO_PAD_SDMMC3,       34,   अच_पूर्णांक_उच्च, "sdmmc3"),    \
	_pad(TEGRA_IO_PAD_SDMMC4,       35,   अच_पूर्णांक_उच्च, "sdmmc4"),    \
	_pad(TEGRA_IO_PAD_SYS_DDC,      58,   अच_पूर्णांक_उच्च, "sys_ddc"),   \
	_pad(TEGRA_IO_PAD_UART,         14,   अच_पूर्णांक_उच्च, "uart"),      \
	_pad(TEGRA_IO_PAD_USB0,         9,    अच_पूर्णांक_उच्च, "usb0"),      \
	_pad(TEGRA_IO_PAD_USB1,         10,   अच_पूर्णांक_उच्च, "usb1"),      \
	_pad(TEGRA_IO_PAD_USB2,         11,   अच_पूर्णांक_उच्च, "usb2"),      \
	_pad(TEGRA_IO_PAD_USB_BIAS,     12,   अच_पूर्णांक_उच्च, "usb_bias")

अटल स्थिर काष्ठा tegra_io_pad_soc tegra124_io_pads[] = अणु
	TEGRA124_IO_PAD_TABLE(TEGRA_IO_PAD)
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc tegra124_pin_descs[] = अणु
	TEGRA124_IO_PAD_TABLE(TEGRA_IO_PIN_DESC)
पूर्ण;

अटल स्थिर काष्ठा tegra_pmc_soc tegra124_pmc_soc = अणु
	.num_घातergates = ARRAY_SIZE(tegra124_घातergates),
	.घातergates = tegra124_घातergates,
	.num_cpu_घातergates = ARRAY_SIZE(tegra124_cpu_घातergates),
	.cpu_घातergates = tegra124_cpu_घातergates,
	.has_tsense_reset = true,
	.has_gpu_clamps = true,
	.needs_mbist_war = false,
	.has_impl_33v_pwr = false,
	.maybe_tz_only = false,
	.num_io_pads = ARRAY_SIZE(tegra124_io_pads),
	.io_pads = tegra124_io_pads,
	.num_pin_descs = ARRAY_SIZE(tegra124_pin_descs),
	.pin_descs = tegra124_pin_descs,
	.regs = &tegra20_pmc_regs,
	.init = tegra20_pmc_init,
	.setup_irq_polarity = tegra20_pmc_setup_irq_polarity,
	.घातergate_set = tegra114_घातergate_set,
	.reset_sources = tegra30_reset_sources,
	.num_reset_sources = ARRAY_SIZE(tegra30_reset_sources),
	.reset_levels = शून्य,
	.num_reset_levels = 0,
	.pmc_clks_data = tegra_pmc_clks_data,
	.num_pmc_clks = ARRAY_SIZE(tegra_pmc_clks_data),
	.has_blink_output = true,
	.has_usb_sleepwalk = true,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra210_घातergates[] = अणु
	[TEGRA_POWERGATE_CPU] = "crail",
	[TEGRA_POWERGATE_3D] = "3d",
	[TEGRA_POWERGATE_VENC] = "venc",
	[TEGRA_POWERGATE_PCIE] = "pcie",
	[TEGRA_POWERGATE_MPE] = "mpe",
	[TEGRA_POWERGATE_SATA] = "sata",
	[TEGRA_POWERGATE_CPU1] = "cpu1",
	[TEGRA_POWERGATE_CPU2] = "cpu2",
	[TEGRA_POWERGATE_CPU3] = "cpu3",
	[TEGRA_POWERGATE_CPU0] = "cpu0",
	[TEGRA_POWERGATE_C0NC] = "c0nc",
	[TEGRA_POWERGATE_SOR] = "sor",
	[TEGRA_POWERGATE_DIS] = "dis",
	[TEGRA_POWERGATE_DISB] = "disb",
	[TEGRA_POWERGATE_XUSBA] = "xusba",
	[TEGRA_POWERGATE_XUSBB] = "xusbb",
	[TEGRA_POWERGATE_XUSBC] = "xusbc",
	[TEGRA_POWERGATE_VIC] = "vic",
	[TEGRA_POWERGATE_IRAM] = "iram",
	[TEGRA_POWERGATE_NVDEC] = "nvdec",
	[TEGRA_POWERGATE_NVJPG] = "nvjpg",
	[TEGRA_POWERGATE_AUD] = "aud",
	[TEGRA_POWERGATE_DFD] = "dfd",
	[TEGRA_POWERGATE_VE2] = "ve2",
पूर्ण;

अटल स्थिर u8 tegra210_cpu_घातergates[] = अणु
	TEGRA_POWERGATE_CPU0,
	TEGRA_POWERGATE_CPU1,
	TEGRA_POWERGATE_CPU2,
	TEGRA_POWERGATE_CPU3,
पूर्ण;

#घोषणा TEGRA210_IO_PAD_TABLE(_pad)                                        \
	/*   .id                        .dpd     .voltage  .name */        \
	_pad(TEGRA_IO_PAD_AUDIO,       17,       5,        "audio"),       \
	_pad(TEGRA_IO_PAD_AUDIO_HV,    61,       18,       "audio-hv"),    \
	_pad(TEGRA_IO_PAD_CAM,         36,       10,       "cam"),         \
	_pad(TEGRA_IO_PAD_CSIA,        0,        अच_पूर्णांक_उच्च, "csia"),        \
	_pad(TEGRA_IO_PAD_CSIB,        1,        अच_पूर्णांक_उच्च, "csib"),        \
	_pad(TEGRA_IO_PAD_CSIC,        42,       अच_पूर्णांक_उच्च, "csic"),        \
	_pad(TEGRA_IO_PAD_CSID,        43,       अच_पूर्णांक_उच्च, "csid"),        \
	_pad(TEGRA_IO_PAD_CSIE,        44,       अच_पूर्णांक_उच्च, "csie"),        \
	_pad(TEGRA_IO_PAD_CSIF,        45,       अच_पूर्णांक_उच्च, "csif"),        \
	_pad(TEGRA_IO_PAD_DBG,         25,       19,       "dbg"),         \
	_pad(TEGRA_IO_PAD_DEBUG_NONAO, 26,       अच_पूर्णांक_उच्च, "debug-nonao"), \
	_pad(TEGRA_IO_PAD_DMIC,        50,       20,       "dmic"),        \
	_pad(TEGRA_IO_PAD_DP,          51,       अच_पूर्णांक_उच्च, "dp"),          \
	_pad(TEGRA_IO_PAD_DSI,         2,        अच_पूर्णांक_उच्च, "dsi"),         \
	_pad(TEGRA_IO_PAD_DSIB,        39,       अच_पूर्णांक_उच्च, "dsib"),        \
	_pad(TEGRA_IO_PAD_DSIC,        40,       अच_पूर्णांक_उच्च, "dsic"),        \
	_pad(TEGRA_IO_PAD_DSID,        41,       अच_पूर्णांक_उच्च, "dsid"),        \
	_pad(TEGRA_IO_PAD_EMMC,        35,       अच_पूर्णांक_उच्च, "emmc"),        \
	_pad(TEGRA_IO_PAD_EMMC2,       37,       अच_पूर्णांक_उच्च, "emmc2"),       \
	_pad(TEGRA_IO_PAD_GPIO,        27,       21,       "gpio"),        \
	_pad(TEGRA_IO_PAD_HDMI,        28,       अच_पूर्णांक_उच्च, "hdmi"),        \
	_pad(TEGRA_IO_PAD_HSIC,        19,       अच_पूर्णांक_उच्च, "hsic"),        \
	_pad(TEGRA_IO_PAD_LVDS,        57,       अच_पूर्णांक_उच्च, "lvds"),        \
	_pad(TEGRA_IO_PAD_MIPI_BIAS,   3,        अच_पूर्णांक_उच्च, "mipi-bias"),   \
	_pad(TEGRA_IO_PAD_PEX_BIAS,    4,        अच_पूर्णांक_उच्च, "pex-bias"),    \
	_pad(TEGRA_IO_PAD_PEX_CLK1,    5,        अच_पूर्णांक_उच्च, "pex-clk1"),    \
	_pad(TEGRA_IO_PAD_PEX_CLK2,    6,        अच_पूर्णांक_उच्च, "pex-clk2"),    \
	_pad(TEGRA_IO_PAD_PEX_CNTRL,   अच_पूर्णांक_उच्च, 11,       "pex-cntrl"),   \
	_pad(TEGRA_IO_PAD_SDMMC1,      33,       12,       "sdmmc1"),      \
	_pad(TEGRA_IO_PAD_SDMMC3,      34,       13,       "sdmmc3"),      \
	_pad(TEGRA_IO_PAD_SPI,         46,       22,       "spi"),         \
	_pad(TEGRA_IO_PAD_SPI_HV,      47,       23,       "spi-hv"),      \
	_pad(TEGRA_IO_PAD_UART,        14,       2,        "uart"),        \
	_pad(TEGRA_IO_PAD_USB0,        9,        अच_पूर्णांक_उच्च, "usb0"),        \
	_pad(TEGRA_IO_PAD_USB1,        10,       अच_पूर्णांक_उच्च, "usb1"),        \
	_pad(TEGRA_IO_PAD_USB2,        11,       अच_पूर्णांक_उच्च, "usb2"),        \
	_pad(TEGRA_IO_PAD_USB3,        18,       अच_पूर्णांक_उच्च, "usb3"),        \
	_pad(TEGRA_IO_PAD_USB_BIAS,    12,       अच_पूर्णांक_उच्च, "usb-bias")

अटल स्थिर काष्ठा tegra_io_pad_soc tegra210_io_pads[] = अणु
	TEGRA210_IO_PAD_TABLE(TEGRA_IO_PAD)
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc tegra210_pin_descs[] = अणु
	TEGRA210_IO_PAD_TABLE(TEGRA_IO_PIN_DESC)
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra210_reset_sources[] = अणु
	"POWER_ON_RESET",
	"WATCHDOG",
	"SENSOR",
	"SW_MAIN",
	"LP0",
	"AOTAG"
पूर्ण;

अटल स्थिर काष्ठा tegra_wake_event tegra210_wake_events[] = अणु
	TEGRA_WAKE_IRQ("rtc", 16, 2),
	TEGRA_WAKE_IRQ("pmu", 51, 86),
पूर्ण;

अटल स्थिर काष्ठा tegra_pmc_soc tegra210_pmc_soc = अणु
	.num_घातergates = ARRAY_SIZE(tegra210_घातergates),
	.घातergates = tegra210_घातergates,
	.num_cpu_घातergates = ARRAY_SIZE(tegra210_cpu_घातergates),
	.cpu_घातergates = tegra210_cpu_घातergates,
	.has_tsense_reset = true,
	.has_gpu_clamps = true,
	.needs_mbist_war = true,
	.has_impl_33v_pwr = false,
	.maybe_tz_only = true,
	.num_io_pads = ARRAY_SIZE(tegra210_io_pads),
	.io_pads = tegra210_io_pads,
	.num_pin_descs = ARRAY_SIZE(tegra210_pin_descs),
	.pin_descs = tegra210_pin_descs,
	.regs = &tegra20_pmc_regs,
	.init = tegra20_pmc_init,
	.setup_irq_polarity = tegra20_pmc_setup_irq_polarity,
	.घातergate_set = tegra114_घातergate_set,
	.irq_set_wake = tegra210_pmc_irq_set_wake,
	.irq_set_type = tegra210_pmc_irq_set_type,
	.reset_sources = tegra210_reset_sources,
	.num_reset_sources = ARRAY_SIZE(tegra210_reset_sources),
	.reset_levels = शून्य,
	.num_reset_levels = 0,
	.num_wake_events = ARRAY_SIZE(tegra210_wake_events),
	.wake_events = tegra210_wake_events,
	.pmc_clks_data = tegra_pmc_clks_data,
	.num_pmc_clks = ARRAY_SIZE(tegra_pmc_clks_data),
	.has_blink_output = true,
	.has_usb_sleepwalk = true,
पूर्ण;

#घोषणा TEGRA186_IO_PAD_TABLE(_pad)                                          \
	/*   .id                        .dpd      .voltage  .name */         \
	_pad(TEGRA_IO_PAD_CSIA,         0,        अच_पूर्णांक_उच्च, "csia"),         \
	_pad(TEGRA_IO_PAD_CSIB,         1,        अच_पूर्णांक_उच्च, "csib"),         \
	_pad(TEGRA_IO_PAD_DSI,          2,        अच_पूर्णांक_उच्च, "dsi"),          \
	_pad(TEGRA_IO_PAD_MIPI_BIAS,    3,        अच_पूर्णांक_उच्च, "mipi-bias"),    \
	_pad(TEGRA_IO_PAD_PEX_CLK_BIAS, 4,        अच_पूर्णांक_उच्च, "pex-clk-bias"), \
	_pad(TEGRA_IO_PAD_PEX_CLK3,     5,        अच_पूर्णांक_उच्च, "pex-clk3"),     \
	_pad(TEGRA_IO_PAD_PEX_CLK2,     6,        अच_पूर्णांक_उच्च, "pex-clk2"),     \
	_pad(TEGRA_IO_PAD_PEX_CLK1,     7,        अच_पूर्णांक_उच्च, "pex-clk1"),     \
	_pad(TEGRA_IO_PAD_USB0,         9,        अच_पूर्णांक_उच्च, "usb0"),         \
	_pad(TEGRA_IO_PAD_USB1,         10,       अच_पूर्णांक_उच्च, "usb1"),         \
	_pad(TEGRA_IO_PAD_USB2,         11,       अच_पूर्णांक_उच्च, "usb2"),         \
	_pad(TEGRA_IO_PAD_USB_BIAS,     12,       अच_पूर्णांक_उच्च, "usb-bias"),     \
	_pad(TEGRA_IO_PAD_UART,         14,       अच_पूर्णांक_उच्च, "uart"),         \
	_pad(TEGRA_IO_PAD_AUDIO,        17,       अच_पूर्णांक_उच्च, "audio"),        \
	_pad(TEGRA_IO_PAD_HSIC,         19,       अच_पूर्णांक_उच्च, "hsic"),         \
	_pad(TEGRA_IO_PAD_DBG,          25,       अच_पूर्णांक_उच्च, "dbg"),          \
	_pad(TEGRA_IO_PAD_HDMI_DP0,     28,       अच_पूर्णांक_उच्च, "hdmi-dp0"),     \
	_pad(TEGRA_IO_PAD_HDMI_DP1,     29,       अच_पूर्णांक_उच्च, "hdmi-dp1"),     \
	_pad(TEGRA_IO_PAD_PEX_CNTRL,    32,       अच_पूर्णांक_उच्च, "pex-cntrl"),    \
	_pad(TEGRA_IO_PAD_SDMMC2_HV,    34,       5,        "sdmmc2-hv"),    \
	_pad(TEGRA_IO_PAD_SDMMC4,       36,       अच_पूर्णांक_उच्च, "sdmmc4"),       \
	_pad(TEGRA_IO_PAD_CAM,          38,       अच_पूर्णांक_उच्च, "cam"),          \
	_pad(TEGRA_IO_PAD_DSIB,         40,       अच_पूर्णांक_उच्च, "dsib"),         \
	_pad(TEGRA_IO_PAD_DSIC,         41,       अच_पूर्णांक_उच्च, "dsic"),         \
	_pad(TEGRA_IO_PAD_DSID,         42,       अच_पूर्णांक_उच्च, "dsid"),         \
	_pad(TEGRA_IO_PAD_CSIC,         43,       अच_पूर्णांक_उच्च, "csic"),         \
	_pad(TEGRA_IO_PAD_CSID,         44,       अच_पूर्णांक_उच्च, "csid"),         \
	_pad(TEGRA_IO_PAD_CSIE,         45,       अच_पूर्णांक_उच्च, "csie"),         \
	_pad(TEGRA_IO_PAD_CSIF,         46,       अच_पूर्णांक_उच्च, "csif"),         \
	_pad(TEGRA_IO_PAD_SPI,          47,       अच_पूर्णांक_उच्च, "spi"),          \
	_pad(TEGRA_IO_PAD_UFS,          49,       अच_पूर्णांक_उच्च, "ufs"),          \
	_pad(TEGRA_IO_PAD_DMIC_HV,      52,       2,        "dmic-hv"),	     \
	_pad(TEGRA_IO_PAD_EDP,          53,       अच_पूर्णांक_उच्च, "edp"),          \
	_pad(TEGRA_IO_PAD_SDMMC1_HV,    55,       4,        "sdmmc1-hv"),    \
	_pad(TEGRA_IO_PAD_SDMMC3_HV,    56,       6,        "sdmmc3-hv"),    \
	_pad(TEGRA_IO_PAD_CONN,         60,       अच_पूर्णांक_उच्च, "conn"),         \
	_pad(TEGRA_IO_PAD_AUDIO_HV,     61,       1,        "audio-hv"),     \
	_pad(TEGRA_IO_PAD_AO_HV,        अच_पूर्णांक_उच्च, 0,        "ao-hv")

अटल स्थिर काष्ठा tegra_io_pad_soc tegra186_io_pads[] = अणु
	TEGRA186_IO_PAD_TABLE(TEGRA_IO_PAD)
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc tegra186_pin_descs[] = अणु
	TEGRA186_IO_PAD_TABLE(TEGRA_IO_PIN_DESC)
पूर्ण;

अटल स्थिर काष्ठा tegra_pmc_regs tegra186_pmc_regs = अणु
	.scratch0 = 0x2000,
	.dpd_req = 0x74,
	.dpd_status = 0x78,
	.dpd2_req = 0x7c,
	.dpd2_status = 0x80,
	.rst_status = 0x70,
	.rst_source_shअगरt = 0x2,
	.rst_source_mask = 0x3c,
	.rst_level_shअगरt = 0x0,
	.rst_level_mask = 0x3,
पूर्ण;

अटल व्योम tegra186_pmc_setup_irq_polarity(काष्ठा tegra_pmc *pmc,
					    काष्ठा device_node *np,
					    bool invert)
अणु
	काष्ठा resource regs;
	व्योम __iomem *wake;
	u32 value;
	पूर्णांक index;

	index = of_property_match_string(np, "reg-names", "wake");
	अगर (index < 0) अणु
		dev_err(pmc->dev, "failed to find PMC wake registers\n");
		वापस;
	पूर्ण

	of_address_to_resource(np, index, &regs);

	wake = ioremap(regs.start, resource_size(&regs));
	अगर (!wake) अणु
		dev_err(pmc->dev, "failed to map PMC wake registers\n");
		वापस;
	पूर्ण

	value = पढ़ोl(wake + WAKE_AOWAKE_CTRL);

	अगर (invert)
		value |= WAKE_AOWAKE_CTRL_INTR_POLARITY;
	अन्यथा
		value &= ~WAKE_AOWAKE_CTRL_INTR_POLARITY;

	ग_लिखोl(value, wake + WAKE_AOWAKE_CTRL);

	iounmap(wake);
पूर्ण

अटल स्थिर अक्षर * स्थिर tegra186_reset_sources[] = अणु
	"SYS_RESET",
	"AOWDT",
	"MCCPLEXWDT",
	"BPMPWDT",
	"SCEWDT",
	"SPEWDT",
	"APEWDT",
	"BCCPLEXWDT",
	"SENSOR",
	"AOTAG",
	"VFSENSOR",
	"SWREST",
	"SC7",
	"HSM",
	"CORESIGHT"
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra186_reset_levels[] = अणु
	"L0", "L1", "L2", "WARM"
पूर्ण;

अटल स्थिर काष्ठा tegra_wake_event tegra186_wake_events[] = अणु
	TEGRA_WAKE_IRQ("pmu", 24, 209),
	TEGRA_WAKE_GPIO("power", 29, 1, TEGRA186_AON_GPIO(FF, 0)),
	TEGRA_WAKE_IRQ("rtc", 73, 10),
पूर्ण;

अटल स्थिर काष्ठा tegra_pmc_soc tegra186_pmc_soc = अणु
	.num_घातergates = 0,
	.घातergates = शून्य,
	.num_cpu_घातergates = 0,
	.cpu_घातergates = शून्य,
	.has_tsense_reset = false,
	.has_gpu_clamps = false,
	.needs_mbist_war = false,
	.has_impl_33v_pwr = true,
	.maybe_tz_only = false,
	.num_io_pads = ARRAY_SIZE(tegra186_io_pads),
	.io_pads = tegra186_io_pads,
	.num_pin_descs = ARRAY_SIZE(tegra186_pin_descs),
	.pin_descs = tegra186_pin_descs,
	.regs = &tegra186_pmc_regs,
	.init = शून्य,
	.setup_irq_polarity = tegra186_pmc_setup_irq_polarity,
	.irq_set_wake = tegra186_pmc_irq_set_wake,
	.irq_set_type = tegra186_pmc_irq_set_type,
	.reset_sources = tegra186_reset_sources,
	.num_reset_sources = ARRAY_SIZE(tegra186_reset_sources),
	.reset_levels = tegra186_reset_levels,
	.num_reset_levels = ARRAY_SIZE(tegra186_reset_levels),
	.num_wake_events = ARRAY_SIZE(tegra186_wake_events),
	.wake_events = tegra186_wake_events,
	.pmc_clks_data = शून्य,
	.num_pmc_clks = 0,
	.has_blink_output = false,
	.has_usb_sleepwalk = false,
पूर्ण;

#घोषणा TEGRA194_IO_PAD_TABLE(_pad)                                              \
	/*   .id                          .dpd      .voltage  .name */           \
	_pad(TEGRA_IO_PAD_CSIA,           0,        अच_पूर्णांक_उच्च, "csia"),           \
	_pad(TEGRA_IO_PAD_CSIB,           1,        अच_पूर्णांक_उच्च, "csib"),           \
	_pad(TEGRA_IO_PAD_MIPI_BIAS,      3,        अच_पूर्णांक_उच्च, "mipi-bias"),      \
	_pad(TEGRA_IO_PAD_PEX_CLK_BIAS,   4,        अच_पूर्णांक_उच्च, "pex-clk-bias"),   \
	_pad(TEGRA_IO_PAD_PEX_CLK3,       5,        अच_पूर्णांक_उच्च, "pex-clk3"),       \
	_pad(TEGRA_IO_PAD_PEX_CLK2,       6,        अच_पूर्णांक_उच्च, "pex-clk2"),       \
	_pad(TEGRA_IO_PAD_PEX_CLK1,       7,        अच_पूर्णांक_उच्च, "pex-clk1"),       \
	_pad(TEGRA_IO_PAD_EQOS,           8,        अच_पूर्णांक_उच्च, "eqos"),           \
	_pad(TEGRA_IO_PAD_PEX_CLK_2_BIAS, 9,        अच_पूर्णांक_उच्च, "pex-clk-2-bias"), \
	_pad(TEGRA_IO_PAD_PEX_CLK_2,      10,       अच_पूर्णांक_उच्च, "pex-clk-2"),      \
	_pad(TEGRA_IO_PAD_DAP3,           11,       अच_पूर्णांक_उच्च, "dap3"),           \
	_pad(TEGRA_IO_PAD_DAP5,           12,       अच_पूर्णांक_उच्च, "dap5"),           \
	_pad(TEGRA_IO_PAD_UART,           14,       अच_पूर्णांक_उच्च, "uart"),           \
	_pad(TEGRA_IO_PAD_PWR_CTL,        15,       अच_पूर्णांक_उच्च, "pwr-ctl"),        \
	_pad(TEGRA_IO_PAD_SOC_GPIO53,     16,       अच_पूर्णांक_उच्च, "soc-gpio53"),     \
	_pad(TEGRA_IO_PAD_AUDIO,          17,       अच_पूर्णांक_उच्च, "audio"),          \
	_pad(TEGRA_IO_PAD_GP_PWM2,        18,       अच_पूर्णांक_उच्च, "gp-pwm2"),        \
	_pad(TEGRA_IO_PAD_GP_PWM3,        19,       अच_पूर्णांक_उच्च, "gp-pwm3"),        \
	_pad(TEGRA_IO_PAD_SOC_GPIO12,     20,       अच_पूर्णांक_उच्च, "soc-gpio12"),     \
	_pad(TEGRA_IO_PAD_SOC_GPIO13,     21,       अच_पूर्णांक_उच्च, "soc-gpio13"),     \
	_pad(TEGRA_IO_PAD_SOC_GPIO10,     22,       अच_पूर्णांक_उच्च, "soc-gpio10"),     \
	_pad(TEGRA_IO_PAD_UART4,          23,       अच_पूर्णांक_उच्च, "uart4"),          \
	_pad(TEGRA_IO_PAD_UART5,          24,       अच_पूर्णांक_उच्च, "uart5"),          \
	_pad(TEGRA_IO_PAD_DBG,            25,       अच_पूर्णांक_उच्च, "dbg"),            \
	_pad(TEGRA_IO_PAD_HDMI_DP3,       26,       अच_पूर्णांक_उच्च, "hdmi-dp3"),       \
	_pad(TEGRA_IO_PAD_HDMI_DP2,       27,       अच_पूर्णांक_उच्च, "hdmi-dp2"),       \
	_pad(TEGRA_IO_PAD_HDMI_DP0,       28,       अच_पूर्णांक_उच्च, "hdmi-dp0"),       \
	_pad(TEGRA_IO_PAD_HDMI_DP1,       29,       अच_पूर्णांक_उच्च, "hdmi-dp1"),       \
	_pad(TEGRA_IO_PAD_PEX_CNTRL,      32,       अच_पूर्णांक_उच्च, "pex-cntrl"),      \
	_pad(TEGRA_IO_PAD_PEX_CTL2,       33,       अच_पूर्णांक_उच्च, "pex-ctl2"),       \
	_pad(TEGRA_IO_PAD_PEX_L0_RST_N,   34,       अच_पूर्णांक_उच्च, "pex-l0-rst"),     \
	_pad(TEGRA_IO_PAD_PEX_L1_RST_N,   35,       अच_पूर्णांक_उच्च, "pex-l1-rst"),     \
	_pad(TEGRA_IO_PAD_SDMMC4,         36,       अच_पूर्णांक_उच्च, "sdmmc4"),         \
	_pad(TEGRA_IO_PAD_PEX_L5_RST_N,   37,       अच_पूर्णांक_उच्च, "pex-l5-rst"),     \
	_pad(TEGRA_IO_PAD_CAM,            38,       अच_पूर्णांक_उच्च, "cam"),            \
	_pad(TEGRA_IO_PAD_CSIC,           43,       अच_पूर्णांक_उच्च, "csic"),           \
	_pad(TEGRA_IO_PAD_CSID,           44,       अच_पूर्णांक_उच्च, "csid"),           \
	_pad(TEGRA_IO_PAD_CSIE,           45,       अच_पूर्णांक_उच्च, "csie"),           \
	_pad(TEGRA_IO_PAD_CSIF,           46,       अच_पूर्णांक_उच्च, "csif"),           \
	_pad(TEGRA_IO_PAD_SPI,            47,       अच_पूर्णांक_उच्च, "spi"),            \
	_pad(TEGRA_IO_PAD_UFS,            49,       अच_पूर्णांक_उच्च, "ufs"),            \
	_pad(TEGRA_IO_PAD_CSIG,           50,       अच_पूर्णांक_उच्च, "csig"),           \
	_pad(TEGRA_IO_PAD_CSIH,           51,       अच_पूर्णांक_उच्च, "csih"),           \
	_pad(TEGRA_IO_PAD_EDP,            53,       अच_पूर्णांक_उच्च, "edp"),            \
	_pad(TEGRA_IO_PAD_SDMMC1_HV,      55,       4,        "sdmmc1-hv"),      \
	_pad(TEGRA_IO_PAD_SDMMC3_HV,      56,       6,        "sdmmc3-hv"),      \
	_pad(TEGRA_IO_PAD_CONN,           60,       अच_पूर्णांक_उच्च, "conn"),           \
	_pad(TEGRA_IO_PAD_AUDIO_HV,       61,       1,        "audio-hv"),       \
	_pad(TEGRA_IO_PAD_AO_HV,          अच_पूर्णांक_उच्च, 0,        "ao-hv")

अटल स्थिर काष्ठा tegra_io_pad_soc tegra194_io_pads[] = अणु
	TEGRA194_IO_PAD_TABLE(TEGRA_IO_PAD)
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc tegra194_pin_descs[] = अणु
	TEGRA194_IO_PAD_TABLE(TEGRA_IO_PIN_DESC)
पूर्ण;

अटल स्थिर काष्ठा tegra_pmc_regs tegra194_pmc_regs = अणु
	.scratch0 = 0x2000,
	.dpd_req = 0x74,
	.dpd_status = 0x78,
	.dpd2_req = 0x7c,
	.dpd2_status = 0x80,
	.rst_status = 0x70,
	.rst_source_shअगरt = 0x2,
	.rst_source_mask = 0x7c,
	.rst_level_shअगरt = 0x0,
	.rst_level_mask = 0x3,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra194_reset_sources[] = अणु
	"SYS_RESET_N",
	"AOWDT",
	"BCCPLEXWDT",
	"BPMPWDT",
	"SCEWDT",
	"SPEWDT",
	"APEWDT",
	"LCCPLEXWDT",
	"SENSOR",
	"AOTAG",
	"VFSENSOR",
	"MAINSWRST",
	"SC7",
	"HSM",
	"CSITE",
	"RCEWDT",
	"PVA0WDT",
	"PVA1WDT",
	"L1A_ASYNC",
	"BPMPBOOT",
	"FUSECRC",
पूर्ण;

अटल स्थिर काष्ठा tegra_wake_event tegra194_wake_events[] = अणु
	TEGRA_WAKE_IRQ("pmu", 24, 209),
	TEGRA_WAKE_GPIO("power", 29, 1, TEGRA194_AON_GPIO(EE, 4)),
	TEGRA_WAKE_IRQ("rtc", 73, 10),
पूर्ण;

अटल स्थिर काष्ठा tegra_pmc_soc tegra194_pmc_soc = अणु
	.num_घातergates = 0,
	.घातergates = शून्य,
	.num_cpu_घातergates = 0,
	.cpu_घातergates = शून्य,
	.has_tsense_reset = false,
	.has_gpu_clamps = false,
	.needs_mbist_war = false,
	.has_impl_33v_pwr = true,
	.maybe_tz_only = false,
	.num_io_pads = ARRAY_SIZE(tegra194_io_pads),
	.io_pads = tegra194_io_pads,
	.num_pin_descs = ARRAY_SIZE(tegra194_pin_descs),
	.pin_descs = tegra194_pin_descs,
	.regs = &tegra194_pmc_regs,
	.init = शून्य,
	.setup_irq_polarity = tegra186_pmc_setup_irq_polarity,
	.irq_set_wake = tegra186_pmc_irq_set_wake,
	.irq_set_type = tegra186_pmc_irq_set_type,
	.reset_sources = tegra194_reset_sources,
	.num_reset_sources = ARRAY_SIZE(tegra194_reset_sources),
	.reset_levels = tegra186_reset_levels,
	.num_reset_levels = ARRAY_SIZE(tegra186_reset_levels),
	.num_wake_events = ARRAY_SIZE(tegra194_wake_events),
	.wake_events = tegra194_wake_events,
	.pmc_clks_data = शून्य,
	.num_pmc_clks = 0,
	.has_blink_output = false,
	.has_usb_sleepwalk = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_pmc_regs tegra234_pmc_regs = अणु
	.scratch0 = 0x2000,
	.dpd_req = 0,
	.dpd_status = 0,
	.dpd2_req = 0,
	.dpd2_status = 0,
	.rst_status = 0x70,
	.rst_source_shअगरt = 0x2,
	.rst_source_mask = 0xfc,
	.rst_level_shअगरt = 0x0,
	.rst_level_mask = 0x3,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra234_reset_sources[] = अणु
	"SYS_RESET_N",
	"AOWDT",
	"BCCPLEXWDT",
	"BPMPWDT",
	"SCEWDT",
	"SPEWDT",
	"APEWDT",
	"LCCPLEXWDT",
	"SENSOR",
	"AOTAG",
	"VFSENSOR",
	"MAINSWRST",
	"SC7",
	"HSM",
	"CSITE",
	"RCEWDT",
	"PVA0WDT",
	"PVA1WDT",
	"L1A_ASYNC",
	"BPMPBOOT",
	"FUSECRC",
पूर्ण;

अटल स्थिर काष्ठा tegra_pmc_soc tegra234_pmc_soc = अणु
	.num_घातergates = 0,
	.घातergates = शून्य,
	.num_cpu_घातergates = 0,
	.cpu_घातergates = शून्य,
	.has_tsense_reset = false,
	.has_gpu_clamps = false,
	.needs_mbist_war = false,
	.has_impl_33v_pwr = true,
	.maybe_tz_only = false,
	.num_io_pads = 0,
	.io_pads = शून्य,
	.num_pin_descs = 0,
	.pin_descs = शून्य,
	.regs = &tegra234_pmc_regs,
	.init = शून्य,
	.setup_irq_polarity = tegra186_pmc_setup_irq_polarity,
	.irq_set_wake = tegra186_pmc_irq_set_wake,
	.irq_set_type = tegra186_pmc_irq_set_type,
	.reset_sources = tegra234_reset_sources,
	.num_reset_sources = ARRAY_SIZE(tegra234_reset_sources),
	.reset_levels = tegra186_reset_levels,
	.num_reset_levels = ARRAY_SIZE(tegra186_reset_levels),
	.num_wake_events = 0,
	.wake_events = शून्य,
	.pmc_clks_data = शून्य,
	.num_pmc_clks = 0,
	.has_blink_output = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_pmc_match[] = अणु
	अणु .compatible = "nvidia,tegra234-pmc", .data = &tegra234_pmc_soc पूर्ण,
	अणु .compatible = "nvidia,tegra194-pmc", .data = &tegra194_pmc_soc पूर्ण,
	अणु .compatible = "nvidia,tegra186-pmc", .data = &tegra186_pmc_soc पूर्ण,
	अणु .compatible = "nvidia,tegra210-pmc", .data = &tegra210_pmc_soc पूर्ण,
	अणु .compatible = "nvidia,tegra132-pmc", .data = &tegra124_pmc_soc पूर्ण,
	अणु .compatible = "nvidia,tegra124-pmc", .data = &tegra124_pmc_soc पूर्ण,
	अणु .compatible = "nvidia,tegra114-pmc", .data = &tegra114_pmc_soc पूर्ण,
	अणु .compatible = "nvidia,tegra30-pmc", .data = &tegra30_pmc_soc पूर्ण,
	अणु .compatible = "nvidia,tegra20-pmc", .data = &tegra20_pmc_soc पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_pmc_driver = अणु
	.driver = अणु
		.name = "tegra-pmc",
		.suppress_bind_attrs = true,
		.of_match_table = tegra_pmc_match,
#अगर defined(CONFIG_PM_SLEEP) && defined(CONFIG_ARM)
		.pm = &tegra_pmc_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe = tegra_pmc_probe,
पूर्ण;
builtin_platक्रमm_driver(tegra_pmc_driver);

अटल bool __init tegra_pmc_detect_tz_only(काष्ठा tegra_pmc *pmc)
अणु
	u32 value, saved;

	saved = पढ़ोl(pmc->base + pmc->soc->regs->scratch0);
	value = saved ^ 0xffffffff;

	अगर (value == 0xffffffff)
		value = 0xdeadbeef;

	/* ग_लिखो pattern and पढ़ो it back */
	ग_लिखोl(value, pmc->base + pmc->soc->regs->scratch0);
	value = पढ़ोl(pmc->base + pmc->soc->regs->scratch0);

	/* अगर we पढ़ो all-zeroes, access is restricted to TZ only */
	अगर (value == 0) अणु
		pr_info("access to PMC is restricted to TZ\n");
		वापस true;
	पूर्ण

	/* restore original value */
	ग_लिखोl(saved, pmc->base + pmc->soc->regs->scratch0);

	वापस false;
पूर्ण

/*
 * Early initialization to allow access to रेजिस्टरs in the very early boot
 * process.
 */
अटल पूर्णांक __init tegra_pmc_early_init(व्योम)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np;
	काष्ठा resource regs;
	अचिन्हित पूर्णांक i;
	bool invert;

	mutex_init(&pmc->घातergates_lock);

	np = of_find_matching_node_and_match(शून्य, tegra_pmc_match, &match);
	अगर (!np) अणु
		/*
		 * Fall back to legacy initialization क्रम 32-bit ARM only. All
		 * 64-bit ARM device tree files क्रम Tegra are required to have
		 * a PMC node.
		 *
		 * This is क्रम backwards-compatibility with old device trees
		 * that didn't contain a PMC node. Note that in this हाल the
		 * SoC data can't be matched and thereक्रमe घातergating is
		 * disabled.
		 */
		अगर (IS_ENABLED(CONFIG_ARM) && soc_is_tegra()) अणु
			pr_warn("DT node not found, powergating disabled\n");

			regs.start = 0x7000e400;
			regs.end = 0x7000e7ff;
			regs.flags = IORESOURCE_MEM;

			pr_warn("Using memory region %pR\n", &regs);
		पूर्ण अन्यथा अणु
			/*
			 * At this poपूर्णांक we're not running on Tegra, so play
			 * nice with multi-platक्रमm kernels.
			 */
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Extract inक्रमmation from the device tree अगर we've found a
		 * matching node.
		 */
		अगर (of_address_to_resource(np, 0, &regs) < 0) अणु
			pr_err("failed to get PMC registers\n");
			of_node_put(np);
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	pmc->base = ioremap(regs.start, resource_size(&regs));
	अगर (!pmc->base) अणु
		pr_err("failed to map PMC registers\n");
		of_node_put(np);
		वापस -ENXIO;
	पूर्ण

	अगर (np) अणु
		pmc->soc = match->data;

		अगर (pmc->soc->maybe_tz_only)
			pmc->tz_only = tegra_pmc_detect_tz_only(pmc);

		/* Create a biपंचांगap of the available and valid partitions */
		क्रम (i = 0; i < pmc->soc->num_घातergates; i++)
			अगर (pmc->soc->घातergates[i])
				set_bit(i, pmc->घातergates_available);

		/*
		 * Invert the पूर्णांकerrupt polarity अगर a PMC device tree node
		 * exists and contains the nvidia,invert-पूर्णांकerrupt property.
		 */
		invert = of_property_पढ़ो_bool(np, "nvidia,invert-interrupt");

		pmc->soc->setup_irq_polarity(pmc, np, invert);

		of_node_put(np);
	पूर्ण

	वापस 0;
पूर्ण
early_initcall(tegra_pmc_early_init);
