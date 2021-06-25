<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * clk-dfll.c - Tegra DFLL घड़ी source common code
 *
 * Copyright (C) 2012-2019 NVIDIA Corporation. All rights reserved.
 *
 * Aleksandr Frid <afrid@nvidia.com>
 * Paul Walmsley <pwalmsley@nvidia.com>
 *
 * This library is क्रम the DVCO and DFLL IP blocks on the Tegra124
 * SoC. These IP blocks together are also known at NVIDIA as
 * "CL-DVFS". To try to aव्योम confusion, this code refers to them
 * collectively as the "DFLL."
 *
 * The DFLL is a root घड़ीsource which tolerates some amount of
 * supply voltage noise. Tegra124 uses it to घड़ी the fast CPU
 * complex when the target CPU speed is above a particular rate. The
 * DFLL can be operated in either खोलो-loop mode or बंदd-loop mode.
 * In खोलो-loop mode, the DFLL generates an output घड़ी appropriate
 * to the supply voltage. In बंदd-loop mode, when configured with a
 * target frequency, the DFLL minimizes supply voltage जबतक
 * delivering an average frequency equal to the target.
 *
 * Devices घड़ीed by the DFLL must be able to tolerate frequency
 * variation. In the हाल of the CPU, it's important to note that the
 * CPU cycle समय will vary. This has implications क्रम
 * perक्रमmance-measurement code and any code that relies on the CPU
 * cycle समय to delay क्रम a certain length of समय.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/seq_file.h>

#समावेश "clk-dfll.h"
#समावेश "cvb.h"

/*
 * DFLL control रेजिस्टरs - access via dfll_अणुपढ़ोl,ग_लिखोlपूर्ण
 */

/* DFLL_CTRL: DFLL control रेजिस्टर */
#घोषणा DFLL_CTRL			0x00
#घोषणा DFLL_CTRL_MODE_MASK		0x03

/* DFLL_CONFIG: DFLL sample rate control */
#घोषणा DFLL_CONFIG			0x04
#घोषणा DFLL_CONFIG_DIV_MASK		0xff
#घोषणा DFLL_CONFIG_DIV_PRESCALE	32

/* DFLL_PARAMS: tuning coefficients क्रम बंदd loop पूर्णांकegrator */
#घोषणा DFLL_PARAMS			0x08
#घोषणा DFLL_PARAMS_CG_SCALE		(0x1 << 24)
#घोषणा DFLL_PARAMS_FORCE_MODE_SHIFT	22
#घोषणा DFLL_PARAMS_FORCE_MODE_MASK	(0x3 << DFLL_PARAMS_FORCE_MODE_SHIFT)
#घोषणा DFLL_PARAMS_CF_PARAM_SHIFT	16
#घोषणा DFLL_PARAMS_CF_PARAM_MASK	(0x3f << DFLL_PARAMS_CF_PARAM_SHIFT)
#घोषणा DFLL_PARAMS_CI_PARAM_SHIFT	8
#घोषणा DFLL_PARAMS_CI_PARAM_MASK	(0x7 << DFLL_PARAMS_CI_PARAM_SHIFT)
#घोषणा DFLL_PARAMS_CG_PARAM_SHIFT	0
#घोषणा DFLL_PARAMS_CG_PARAM_MASK	(0xff << DFLL_PARAMS_CG_PARAM_SHIFT)

/* DFLL_TUNE0: delay line configuration रेजिस्टर 0 */
#घोषणा DFLL_TUNE0			0x0c

/* DFLL_TUNE1: delay line configuration रेजिस्टर 1 */
#घोषणा DFLL_TUNE1			0x10

/* DFLL_FREQ_REQ: target DFLL frequency control */
#घोषणा DFLL_FREQ_REQ			0x14
#घोषणा DFLL_FREQ_REQ_FORCE_ENABLE	(0x1 << 28)
#घोषणा DFLL_FREQ_REQ_FORCE_SHIFT	16
#घोषणा DFLL_FREQ_REQ_FORCE_MASK	(0xfff << DFLL_FREQ_REQ_FORCE_SHIFT)
#घोषणा FORCE_MAX			2047
#घोषणा FORCE_MIN			-2048
#घोषणा DFLL_FREQ_REQ_SCALE_SHIFT	8
#घोषणा DFLL_FREQ_REQ_SCALE_MASK	(0xff << DFLL_FREQ_REQ_SCALE_SHIFT)
#घोषणा DFLL_FREQ_REQ_SCALE_MAX		256
#घोषणा DFLL_FREQ_REQ_FREQ_VALID	(0x1 << 7)
#घोषणा DFLL_FREQ_REQ_MULT_SHIFT	0
#घोषणा DFLL_FREQ_REG_MULT_MASK		(0x7f << DFLL_FREQ_REQ_MULT_SHIFT)
#घोषणा FREQ_MAX			127

/* DFLL_DROOP_CTRL: droop prevention control */
#घोषणा DFLL_DROOP_CTRL			0x1c

/* DFLL_OUTPUT_CFG: बंदd loop mode control रेजिस्टरs */
/* NOTE: access via dfll_i2c_अणुपढ़ोl,ग_लिखोlपूर्ण */
#घोषणा DFLL_OUTPUT_CFG			0x20
#घोषणा DFLL_OUTPUT_CFG_I2C_ENABLE	(0x1 << 30)
#घोषणा OUT_MASK			0x3f
#घोषणा DFLL_OUTPUT_CFG_SAFE_SHIFT	24
#घोषणा DFLL_OUTPUT_CFG_SAFE_MASK	\
		(OUT_MASK << DFLL_OUTPUT_CFG_SAFE_SHIFT)
#घोषणा DFLL_OUTPUT_CFG_MAX_SHIFT	16
#घोषणा DFLL_OUTPUT_CFG_MAX_MASK	\
		(OUT_MASK << DFLL_OUTPUT_CFG_MAX_SHIFT)
#घोषणा DFLL_OUTPUT_CFG_MIN_SHIFT	8
#घोषणा DFLL_OUTPUT_CFG_MIN_MASK	\
		(OUT_MASK << DFLL_OUTPUT_CFG_MIN_SHIFT)
#घोषणा DFLL_OUTPUT_CFG_PWM_DELTA	(0x1 << 7)
#घोषणा DFLL_OUTPUT_CFG_PWM_ENABLE	(0x1 << 6)
#घोषणा DFLL_OUTPUT_CFG_PWM_DIV_SHIFT	0
#घोषणा DFLL_OUTPUT_CFG_PWM_DIV_MASK	\
		(OUT_MASK << DFLL_OUTPUT_CFG_PWM_DIV_SHIFT)

/* DFLL_OUTPUT_FORCE: बंदd loop mode voltage क्रमcing control */
#घोषणा DFLL_OUTPUT_FORCE		0x24
#घोषणा DFLL_OUTPUT_FORCE_ENABLE	(0x1 << 6)
#घोषणा DFLL_OUTPUT_FORCE_VALUE_SHIFT	0
#घोषणा DFLL_OUTPUT_FORCE_VALUE_MASK	\
		(OUT_MASK << DFLL_OUTPUT_FORCE_VALUE_SHIFT)

/* DFLL_MONITOR_CTRL: पूर्णांकernal monitor data source control */
#घोषणा DFLL_MONITOR_CTRL		0x28
#घोषणा DFLL_MONITOR_CTRL_FREQ		6

/* DFLL_MONITOR_DATA: पूर्णांकernal monitor data output */
#घोषणा DFLL_MONITOR_DATA		0x2c
#घोषणा DFLL_MONITOR_DATA_NEW_MASK	(0x1 << 16)
#घोषणा DFLL_MONITOR_DATA_VAL_SHIFT	0
#घोषणा DFLL_MONITOR_DATA_VAL_MASK	(0xFFFF << DFLL_MONITOR_DATA_VAL_SHIFT)

/*
 * I2C output control रेजिस्टरs - access via dfll_i2c_अणुपढ़ोl,ग_लिखोlपूर्ण
 */

/* DFLL_I2C_CFG: I2C controller configuration रेजिस्टर */
#घोषणा DFLL_I2C_CFG			0x40
#घोषणा DFLL_I2C_CFG_ARB_ENABLE		(0x1 << 20)
#घोषणा DFLL_I2C_CFG_HS_CODE_SHIFT	16
#घोषणा DFLL_I2C_CFG_HS_CODE_MASK	(0x7 << DFLL_I2C_CFG_HS_CODE_SHIFT)
#घोषणा DFLL_I2C_CFG_PACKET_ENABLE	(0x1 << 15)
#घोषणा DFLL_I2C_CFG_SIZE_SHIFT		12
#घोषणा DFLL_I2C_CFG_SIZE_MASK		(0x7 << DFLL_I2C_CFG_SIZE_SHIFT)
#घोषणा DFLL_I2C_CFG_SLAVE_ADDR_10	(0x1 << 10)
#घोषणा DFLL_I2C_CFG_SLAVE_ADDR_SHIFT_7BIT	1
#घोषणा DFLL_I2C_CFG_SLAVE_ADDR_SHIFT_10BIT	0

/* DFLL_I2C_VDD_REG_ADDR: PMIC I2C address क्रम बंदd loop mode */
#घोषणा DFLL_I2C_VDD_REG_ADDR		0x44

/* DFLL_I2C_STS: I2C controller status */
#घोषणा DFLL_I2C_STS			0x48
#घोषणा DFLL_I2C_STS_I2C_LAST_SHIFT	1
#घोषणा DFLL_I2C_STS_I2C_REQ_PENDING	0x1

/* DFLL_INTR_STS: DFLL पूर्णांकerrupt status रेजिस्टर */
#घोषणा DFLL_INTR_STS			0x5c

/* DFLL_INTR_EN: DFLL पूर्णांकerrupt enable रेजिस्टर */
#घोषणा DFLL_INTR_EN			0x60
#घोषणा DFLL_INTR_MIN_MASK		0x1
#घोषणा DFLL_INTR_MAX_MASK		0x2

/*
 * Integrated I2C controller रेजिस्टरs - relative to td->i2c_controller_base
 */

/* DFLL_I2C_CLK_DIVISOR: I2C controller घड़ी भागisor */
#घोषणा DFLL_I2C_CLK_DIVISOR		0x6c
#घोषणा DFLL_I2C_CLK_DIVISOR_MASK	0xffff
#घोषणा DFLL_I2C_CLK_DIVISOR_FS_SHIFT	16
#घोषणा DFLL_I2C_CLK_DIVISOR_HS_SHIFT	0
#घोषणा DFLL_I2C_CLK_DIVISOR_PREDIV	8
#घोषणा DFLL_I2C_CLK_DIVISOR_HSMODE_PREDIV	12

/*
 * Other स्थिरants
 */

/* MAX_DFLL_VOLTAGES: number of LUT entries in the DFLL IP block */
#घोषणा MAX_DFLL_VOLTAGES		33

/*
 * REF_CLK_CYC_PER_DVCO_SAMPLE: the number of ref_clk cycles that the hardware
 *    पूर्णांकegrates the DVCO counter over - used क्रम debug rate monitoring and
 *    droop control
 */
#घोषणा REF_CLK_CYC_PER_DVCO_SAMPLE	4

/*
 * REF_CLOCK_RATE: the DFLL reference घड़ी rate currently supported by this
 * driver, in Hz
 */
#घोषणा REF_CLOCK_RATE			51000000UL

#घोषणा DVCO_RATE_TO_MULT(rate, ref_rate)	((rate) / ((ref_rate) / 2))
#घोषणा MULT_TO_DVCO_RATE(mult, ref_rate)	((mult) * ((ref_rate) / 2))

/**
 * क्रमागत dfll_ctrl_mode - DFLL hardware operating mode
 * @DFLL_UNINITIALIZED: (uninitialized state - not in hardware bitfield)
 * @DFLL_DISABLED: DFLL not generating an output घड़ी
 * @DFLL_OPEN_LOOP: DVCO running, but DFLL not adjusting voltage
 * @DFLL_CLOSED_LOOP: DVCO running, and DFLL adjusting voltage to match
 *		      the requested rate
 *
 * The पूर्णांकeger corresponding to the last two states, minus one, is
 * written to the DFLL hardware to change operating modes.
 */
क्रमागत dfll_ctrl_mode अणु
	DFLL_UNINITIALIZED = 0,
	DFLL_DISABLED = 1,
	DFLL_OPEN_LOOP = 2,
	DFLL_CLOSED_LOOP = 3,
पूर्ण;

/**
 * क्रमागत dfll_tune_range - voltage range that the driver believes it's in
 * @DFLL_TUNE_UNINITIALIZED: DFLL tuning not yet programmed
 * @DFLL_TUNE_LOW: DFLL in the low-voltage range (or खोलो-loop mode)
 *
 * Some DFLL tuning parameters may need to change depending on the
 * DVCO's voltage; these states represent the ranges that the driver
 * supports. These are software states; these values are never
 * written पूर्णांकo रेजिस्टरs.
 */
क्रमागत dfll_tune_range अणु
	DFLL_TUNE_UNINITIALIZED = 0,
	DFLL_TUNE_LOW = 1,
पूर्ण;


क्रमागत tegra_dfll_pmu_अगर अणु
	TEGRA_DFLL_PMU_I2C = 0,
	TEGRA_DFLL_PMU_PWM = 1,
पूर्ण;

/**
 * काष्ठा dfll_rate_req - target DFLL rate request data
 * @rate: target frequency, after the postscaling
 * @dvco_target_rate: target frequency, after the postscaling
 * @lut_index: LUT index at which voltage the dvco_target_rate will be reached
 * @mult_bits: value to program to the MULT bits of the DFLL_FREQ_REQ रेजिस्टर
 * @scale_bits: value to program to the SCALE bits of the DFLL_FREQ_REQ रेजिस्टर
 */
काष्ठा dfll_rate_req अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ dvco_target_rate;
	पूर्णांक lut_index;
	u8 mult_bits;
	u8 scale_bits;
पूर्ण;

काष्ठा tegra_dfll अणु
	काष्ठा device			*dev;
	काष्ठा tegra_dfll_soc_data	*soc;

	व्योम __iomem			*base;
	व्योम __iomem			*i2c_base;
	व्योम __iomem			*i2c_controller_base;
	व्योम __iomem			*lut_base;

	काष्ठा regulator		*vdd_reg;
	काष्ठा clk			*soc_clk;
	काष्ठा clk			*ref_clk;
	काष्ठा clk			*i2c_clk;
	काष्ठा clk			*dfll_clk;
	काष्ठा reset_control		*dvco_rst;
	अचिन्हित दीर्घ			ref_rate;
	अचिन्हित दीर्घ			i2c_clk_rate;
	अचिन्हित दीर्घ			dvco_rate_min;

	क्रमागत dfll_ctrl_mode		mode;
	क्रमागत dfll_tune_range		tune_range;
	काष्ठा dentry			*debugfs_dir;
	काष्ठा clk_hw			dfll_clk_hw;
	स्थिर अक्षर			*output_घड़ी_name;
	काष्ठा dfll_rate_req		last_req;
	अचिन्हित दीर्घ			last_unrounded_rate;

	/* Parameters from DT */
	u32				droop_ctrl;
	u32				sample_rate;
	u32				क्रमce_mode;
	u32				cf;
	u32				ci;
	u32				cg;
	bool				cg_scale;

	/* I2C पूर्णांकerface parameters */
	u32				i2c_fs_rate;
	u32				i2c_reg;
	u32				i2c_slave_addr;

	/* lut array entries are regulator framework selectors or PWM values*/
	अचिन्हित			lut[MAX_DFLL_VOLTAGES];
	अचिन्हित दीर्घ			lut_uv[MAX_DFLL_VOLTAGES];
	पूर्णांक				lut_size;
	u8				lut_bottom, lut_min, lut_max, lut_safe;

	/* PWM पूर्णांकerface */
	क्रमागत tegra_dfll_pmu_अगर		pmu_अगर;
	अचिन्हित दीर्घ			pwm_rate;
	काष्ठा pinctrl			*pwm_pin;
	काष्ठा pinctrl_state		*pwm_enable_state;
	काष्ठा pinctrl_state		*pwm_disable_state;
	u32				reg_init_uV;
पूर्ण;

#घोषणा clk_hw_to_dfll(_hw) container_of(_hw, काष्ठा tegra_dfll, dfll_clk_hw)

/* mode_name: map numeric DFLL modes to names क्रम मित्रly console messages */
अटल स्थिर अक्षर * स्थिर mode_name[] = अणु
	[DFLL_UNINITIALIZED] = "uninitialized",
	[DFLL_DISABLED] = "disabled",
	[DFLL_OPEN_LOOP] = "open_loop",
	[DFLL_CLOSED_LOOP] = "closed_loop",
पूर्ण;

/*
 * Register accessors
 */

अटल अंतरभूत u32 dfll_पढ़ोl(काष्ठा tegra_dfll *td, u32 offs)
अणु
	वापस __raw_पढ़ोl(td->base + offs);
पूर्ण

अटल अंतरभूत व्योम dfll_ग_लिखोl(काष्ठा tegra_dfll *td, u32 val, u32 offs)
अणु
	WARN_ON(offs >= DFLL_I2C_CFG);
	__raw_ग_लिखोl(val, td->base + offs);
पूर्ण

अटल अंतरभूत व्योम dfll_wmb(काष्ठा tegra_dfll *td)
अणु
	dfll_पढ़ोl(td, DFLL_CTRL);
पूर्ण

/* I2C output control रेजिस्टरs - क्रम addresses above DFLL_I2C_CFG */

अटल अंतरभूत u32 dfll_i2c_पढ़ोl(काष्ठा tegra_dfll *td, u32 offs)
अणु
	वापस __raw_पढ़ोl(td->i2c_base + offs);
पूर्ण

अटल अंतरभूत व्योम dfll_i2c_ग_लिखोl(काष्ठा tegra_dfll *td, u32 val, u32 offs)
अणु
	__raw_ग_लिखोl(val, td->i2c_base + offs);
पूर्ण

अटल अंतरभूत व्योम dfll_i2c_wmb(काष्ठा tegra_dfll *td)
अणु
	dfll_i2c_पढ़ोl(td, DFLL_I2C_CFG);
पूर्ण

/**
 * dfll_is_running - is the DFLL currently generating a घड़ी?
 * @td: DFLL instance
 *
 * If the DFLL is currently generating an output घड़ी संकेत, वापस
 * true; otherwise वापस false.
 */
अटल bool dfll_is_running(काष्ठा tegra_dfll *td)
अणु
	वापस td->mode >= DFLL_OPEN_LOOP;
पूर्ण

/*
 * Runसमय PM suspend/resume callbacks
 */

/**
 * tegra_dfll_runसमय_resume - enable all घड़ीs needed by the DFLL
 * @dev: DFLL device *
 *
 * Enable all घड़ीs needed by the DFLL. Assumes that clk_prepare()
 * has alपढ़ोy been called on all the घड़ीs.
 *
 * XXX Should also handle context restore when वापसing from off.
 */
पूर्णांक tegra_dfll_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_dfll *td = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_enable(td->ref_clk);
	अगर (ret) अणु
		dev_err(dev, "could not enable ref clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_enable(td->soc_clk);
	अगर (ret) अणु
		dev_err(dev, "could not enable register clock: %d\n", ret);
		clk_disable(td->ref_clk);
		वापस ret;
	पूर्ण

	ret = clk_enable(td->i2c_clk);
	अगर (ret) अणु
		dev_err(dev, "could not enable i2c clock: %d\n", ret);
		clk_disable(td->soc_clk);
		clk_disable(td->ref_clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tegra_dfll_runसमय_resume);

/**
 * tegra_dfll_runसमय_suspend - disable all घड़ीs needed by the DFLL
 * @dev: DFLL device *
 *
 * Disable all घड़ीs needed by the DFLL. Assumes that other code
 * will later call clk_unprepare().
 */
पूर्णांक tegra_dfll_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_dfll *td = dev_get_drvdata(dev);

	clk_disable(td->ref_clk);
	clk_disable(td->soc_clk);
	clk_disable(td->i2c_clk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tegra_dfll_runसमय_suspend);

/*
 * DFLL tuning operations (per-voltage-range tuning settings)
 */

/**
 * dfll_tune_low - tune to DFLL and CPU settings valid क्रम any voltage
 * @td: DFLL instance
 *
 * Tune the DFLL oscillator parameters and the CPU घड़ी shaper क्रम
 * the low-voltage range. These settings are valid क्रम any voltage,
 * but may not be optimal.
 */
अटल व्योम dfll_tune_low(काष्ठा tegra_dfll *td)
अणु
	td->tune_range = DFLL_TUNE_LOW;

	dfll_ग_लिखोl(td, td->soc->cvb->cpu_dfll_data.tune0_low, DFLL_TUNE0);
	dfll_ग_लिखोl(td, td->soc->cvb->cpu_dfll_data.tune1, DFLL_TUNE1);
	dfll_wmb(td);

	अगर (td->soc->set_घड़ी_प्रकारrimmers_low)
		td->soc->set_घड़ी_प्रकारrimmers_low();
पूर्ण

/*
 * Output घड़ी scaler helpers
 */

/**
 * dfll_scale_dvco_rate - calculate scaled rate from the DVCO rate
 * @scale_bits: घड़ी scaler value (bits in the DFLL_FREQ_REQ_SCALE field)
 * @dvco_rate: the DVCO rate
 *
 * Apply the same scaling क्रमmula that the DFLL hardware uses to scale
 * the DVCO rate.
 */
अटल अचिन्हित दीर्घ dfll_scale_dvco_rate(पूर्णांक scale_bits,
					  अचिन्हित दीर्घ dvco_rate)
अणु
	वापस (u64)dvco_rate * (scale_bits + 1) / DFLL_FREQ_REQ_SCALE_MAX;
पूर्ण

/*
 * DFLL mode चयनing
 */

/**
 * dfll_set_mode - change the DFLL control mode
 * @td: DFLL instance
 * @mode: DFLL control mode (see क्रमागत dfll_ctrl_mode)
 *
 * Change the DFLL's operating mode between disabled, खोलो-loop mode,
 * and बंदd-loop mode, or vice versa.
 */
अटल व्योम dfll_set_mode(काष्ठा tegra_dfll *td,
			  क्रमागत dfll_ctrl_mode mode)
अणु
	td->mode = mode;
	dfll_ग_लिखोl(td, mode - 1, DFLL_CTRL);
	dfll_wmb(td);
पूर्ण

/*
 * DVCO rate control
 */

अटल अचिन्हित दीर्घ get_dvco_rate_below(काष्ठा tegra_dfll *td, u8 out_min)
अणु
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ rate, prev_rate;
	अचिन्हित दीर्घ uv, min_uv;

	min_uv = td->lut_uv[out_min];
	क्रम (rate = 0, prev_rate = 0; ; rate++) अणु
		opp = dev_pm_opp_find_freq_उच्चमान(td->soc->dev, &rate);
		अगर (IS_ERR(opp))
			अवरोध;

		uv = dev_pm_opp_get_voltage(opp);
		dev_pm_opp_put(opp);

		अगर (uv && uv > min_uv)
			वापस prev_rate;

		prev_rate = rate;
	पूर्ण

	वापस prev_rate;
पूर्ण

/*
 * DFLL-to-I2C controller पूर्णांकerface
 */

/**
 * dfll_i2c_set_output_enabled - enable/disable I2C PMIC voltage requests
 * @td: DFLL instance
 * @enable: whether to enable or disable the I2C voltage requests
 *
 * Set the master enable control क्रम I2C control value updates. If disabled,
 * then I2C control messages are inhibited, regardless of the DFLL mode.
 */
अटल पूर्णांक dfll_i2c_set_output_enabled(काष्ठा tegra_dfll *td, bool enable)
अणु
	u32 val;

	val = dfll_i2c_पढ़ोl(td, DFLL_OUTPUT_CFG);

	अगर (enable)
		val |= DFLL_OUTPUT_CFG_I2C_ENABLE;
	अन्यथा
		val &= ~DFLL_OUTPUT_CFG_I2C_ENABLE;

	dfll_i2c_ग_लिखोl(td, val, DFLL_OUTPUT_CFG);
	dfll_i2c_wmb(td);

	वापस 0;
पूर्ण


/*
 * DFLL-to-PWM controller पूर्णांकerface
 */

/**
 * dfll_pwm_set_output_enabled - enable/disable PWM voltage requests
 * @td: DFLL instance
 * @enable: whether to enable or disable the PWM voltage requests
 *
 * Set the master enable control क्रम PWM control value updates. If disabled,
 * then the PWM संकेत is not driven. Also configure the PWM output pad
 * to the appropriate state.
 */
अटल पूर्णांक dfll_pwm_set_output_enabled(काष्ठा tegra_dfll *td, bool enable)
अणु
	पूर्णांक ret;
	u32 val, भाग;

	अगर (enable) अणु
		ret = pinctrl_select_state(td->pwm_pin, td->pwm_enable_state);
		अगर (ret < 0) अणु
			dev_err(td->dev, "setting enable state failed\n");
			वापस -EINVAL;
		पूर्ण
		val = dfll_पढ़ोl(td, DFLL_OUTPUT_CFG);
		val &= ~DFLL_OUTPUT_CFG_PWM_DIV_MASK;
		भाग = DIV_ROUND_UP(td->ref_rate, td->pwm_rate);
		val |= (भाग << DFLL_OUTPUT_CFG_PWM_DIV_SHIFT)
				& DFLL_OUTPUT_CFG_PWM_DIV_MASK;
		dfll_ग_लिखोl(td, val, DFLL_OUTPUT_CFG);
		dfll_wmb(td);

		val |= DFLL_OUTPUT_CFG_PWM_ENABLE;
		dfll_ग_लिखोl(td, val, DFLL_OUTPUT_CFG);
		dfll_wmb(td);
	पूर्ण अन्यथा अणु
		ret = pinctrl_select_state(td->pwm_pin, td->pwm_disable_state);
		अगर (ret < 0)
			dev_warn(td->dev, "setting disable state failed\n");

		val = dfll_पढ़ोl(td, DFLL_OUTPUT_CFG);
		val &= ~DFLL_OUTPUT_CFG_PWM_ENABLE;
		dfll_ग_लिखोl(td, val, DFLL_OUTPUT_CFG);
		dfll_wmb(td);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dfll_set_क्रमce_output_value - set fixed value क्रम क्रमce output
 * @td: DFLL instance
 * @out_val: value to क्रमce output
 *
 * Set the fixed value क्रम क्रमce output, DFLL will output this value when
 * क्रमce output is enabled.
 */
अटल u32 dfll_set_क्रमce_output_value(काष्ठा tegra_dfll *td, u8 out_val)
अणु
	u32 val = dfll_पढ़ोl(td, DFLL_OUTPUT_FORCE);

	val = (val & DFLL_OUTPUT_FORCE_ENABLE) | (out_val & OUT_MASK);
	dfll_ग_लिखोl(td, val, DFLL_OUTPUT_FORCE);
	dfll_wmb(td);

	वापस dfll_पढ़ोl(td, DFLL_OUTPUT_FORCE);
पूर्ण

/**
 * dfll_set_क्रमce_output_enabled - enable/disable क्रमce output
 * @td: DFLL instance
 * @enable: whether to enable or disable the क्रमce output
 *
 * Set the enable control क्रम fouce output with fixed value.
 */
अटल व्योम dfll_set_क्रमce_output_enabled(काष्ठा tegra_dfll *td, bool enable)
अणु
	u32 val = dfll_पढ़ोl(td, DFLL_OUTPUT_FORCE);

	अगर (enable)
		val |= DFLL_OUTPUT_FORCE_ENABLE;
	अन्यथा
		val &= ~DFLL_OUTPUT_FORCE_ENABLE;

	dfll_ग_लिखोl(td, val, DFLL_OUTPUT_FORCE);
	dfll_wmb(td);
पूर्ण

/**
 * dfll_क्रमce_output - क्रमce output a fixed value
 * @td: DFLL instance
 * @out_sel: value to क्रमce output
 *
 * Set the fixed value क्रम क्रमce output, DFLL will output this value.
 */
अटल पूर्णांक dfll_क्रमce_output(काष्ठा tegra_dfll *td, अचिन्हित पूर्णांक out_sel)
अणु
	u32 val;

	अगर (out_sel > OUT_MASK)
		वापस -EINVAL;

	val = dfll_set_क्रमce_output_value(td, out_sel);
	अगर ((td->mode < DFLL_CLOSED_LOOP) &&
	    !(val & DFLL_OUTPUT_FORCE_ENABLE)) अणु
		dfll_set_क्रमce_output_enabled(td, true);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dfll_load_lut - load the voltage lookup table
 * @td: काष्ठा tegra_dfll *
 *
 * Load the voltage-to-PMIC रेजिस्टर value lookup table पूर्णांकo the DFLL
 * IP block memory. Look-up tables can be loaded at any समय.
 */
अटल व्योम dfll_load_i2c_lut(काष्ठा tegra_dfll *td)
अणु
	पूर्णांक i, lut_index;
	u32 val;

	क्रम (i = 0; i < MAX_DFLL_VOLTAGES; i++) अणु
		अगर (i < td->lut_min)
			lut_index = td->lut_min;
		अन्यथा अगर (i > td->lut_max)
			lut_index = td->lut_max;
		अन्यथा
			lut_index = i;

		val = regulator_list_hardware_vsel(td->vdd_reg,
						     td->lut[lut_index]);
		__raw_ग_लिखोl(val, td->lut_base + i * 4);
	पूर्ण

	dfll_i2c_wmb(td);
पूर्ण

/**
 * dfll_init_i2c_अगर - set up the DFLL's DFLL-I2C पूर्णांकerface
 * @td: DFLL instance
 *
 * During DFLL driver initialization, program the DFLL-I2C पूर्णांकerface
 * with the PMU slave address, vdd रेजिस्टर offset, and transfer mode.
 * This data is used by the DFLL to स्वतःmatically स्थिरruct I2C
 * voltage-set commands, which are then passed to the DFLL's पूर्णांकernal
 * I2C controller.
 */
अटल व्योम dfll_init_i2c_अगर(काष्ठा tegra_dfll *td)
अणु
	u32 val;

	अगर (td->i2c_slave_addr > 0x7f) अणु
		val = td->i2c_slave_addr << DFLL_I2C_CFG_SLAVE_ADDR_SHIFT_10BIT;
		val |= DFLL_I2C_CFG_SLAVE_ADDR_10;
	पूर्ण अन्यथा अणु
		val = td->i2c_slave_addr << DFLL_I2C_CFG_SLAVE_ADDR_SHIFT_7BIT;
	पूर्ण
	val |= DFLL_I2C_CFG_SIZE_MASK;
	val |= DFLL_I2C_CFG_ARB_ENABLE;
	dfll_i2c_ग_लिखोl(td, val, DFLL_I2C_CFG);

	dfll_i2c_ग_लिखोl(td, td->i2c_reg, DFLL_I2C_VDD_REG_ADDR);

	val = DIV_ROUND_UP(td->i2c_clk_rate, td->i2c_fs_rate * 8);
	BUG_ON(!val || (val > DFLL_I2C_CLK_DIVISOR_MASK));
	val = (val - 1) << DFLL_I2C_CLK_DIVISOR_FS_SHIFT;

	/* शेष hs भागisor just in हाल */
	val |= 1 << DFLL_I2C_CLK_DIVISOR_HS_SHIFT;
	__raw_ग_लिखोl(val, td->i2c_controller_base + DFLL_I2C_CLK_DIVISOR);
	dfll_i2c_wmb(td);
पूर्ण

/**
 * dfll_init_out_अगर - prepare DFLL-to-PMIC पूर्णांकerface
 * @td: DFLL instance
 *
 * During DFLL driver initialization or resume from context loss,
 * disable the I2C command output to the PMIC, set safe voltage and
 * output limits, and disable and clear limit पूर्णांकerrupts.
 */
अटल व्योम dfll_init_out_अगर(काष्ठा tegra_dfll *td)
अणु
	u32 val;

	td->lut_min = td->lut_bottom;
	td->lut_max = td->lut_size - 1;
	td->lut_safe = td->lut_min + (td->lut_min < td->lut_max ? 1 : 0);

	/* clear DFLL_OUTPUT_CFG beक्रमe setting new value */
	dfll_ग_लिखोl(td, 0, DFLL_OUTPUT_CFG);
	dfll_wmb(td);

	val = (td->lut_safe << DFLL_OUTPUT_CFG_SAFE_SHIFT) |
	      (td->lut_max << DFLL_OUTPUT_CFG_MAX_SHIFT) |
	      (td->lut_min << DFLL_OUTPUT_CFG_MIN_SHIFT);
	dfll_ग_लिखोl(td, val, DFLL_OUTPUT_CFG);
	dfll_wmb(td);

	dfll_ग_लिखोl(td, 0, DFLL_OUTPUT_FORCE);
	dfll_i2c_ग_लिखोl(td, 0, DFLL_INTR_EN);
	dfll_i2c_ग_लिखोl(td, DFLL_INTR_MAX_MASK | DFLL_INTR_MIN_MASK,
			DFLL_INTR_STS);

	अगर (td->pmu_अगर == TEGRA_DFLL_PMU_PWM) अणु
		u32 vinit = td->reg_init_uV;
		पूर्णांक vstep = td->soc->alignment.step_uv;
		अचिन्हित दीर्घ vmin = td->lut_uv[0];

		/* set initial voltage */
		अगर ((vinit >= vmin) && vstep) अणु
			अचिन्हित पूर्णांक vsel;

			vsel = DIV_ROUND_UP((vinit - vmin), vstep);
			dfll_क्रमce_output(td, vsel);
		पूर्ण
	पूर्ण अन्यथा अणु
		dfll_load_i2c_lut(td);
		dfll_init_i2c_अगर(td);
	पूर्ण
पूर्ण

/*
 * Set/get the DFLL's targeted output घड़ी rate
 */

/**
 * find_lut_index_क्रम_rate - determine I2C LUT index क्रम given DFLL rate
 * @td: DFLL instance
 * @rate: घड़ी rate
 *
 * Determines the index of a I2C LUT entry क्रम a voltage that approximately
 * produces the given DFLL घड़ी rate. This is used when क्रमcing a value
 * to the पूर्णांकegrator during rate changes. Returns -ENOENT अगर a suitable
 * LUT index is not found.
 */
अटल पूर्णांक find_lut_index_क्रम_rate(काष्ठा tegra_dfll *td, अचिन्हित दीर्घ rate)
अणु
	काष्ठा dev_pm_opp *opp;
	पूर्णांक i, align_step;

	opp = dev_pm_opp_find_freq_उच्चमान(td->soc->dev, &rate);
	अगर (IS_ERR(opp))
		वापस PTR_ERR(opp);

	align_step = dev_pm_opp_get_voltage(opp) / td->soc->alignment.step_uv;
	dev_pm_opp_put(opp);

	क्रम (i = td->lut_bottom; i < td->lut_size; i++) अणु
		अगर ((td->lut_uv[i] / td->soc->alignment.step_uv) >= align_step)
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/**
 * dfll_calculate_rate_request - calculate DFLL parameters क्रम a given rate
 * @td: DFLL instance
 * @req: DFLL-rate-request काष्ठाure
 * @rate: the desired DFLL rate
 *
 * Populate the DFLL-rate-request record @req fields with the scale_bits
 * and mult_bits fields, based on the target input rate. Returns 0 upon
 * success, or -EINVAL अगर the requested rate in req->rate is too high
 * or low क्रम the DFLL to generate.
 */
अटल पूर्णांक dfll_calculate_rate_request(काष्ठा tegra_dfll *td,
				       काष्ठा dfll_rate_req *req,
				       अचिन्हित दीर्घ rate)
अणु
	u32 val;

	/*
	 * If requested rate is below the minimum DVCO rate, active the scaler.
	 * In the future the DVCO minimum voltage should be selected based on
	 * chip temperature and the actual minimum rate should be calibrated
	 * at runसमय.
	 */
	req->scale_bits = DFLL_FREQ_REQ_SCALE_MAX - 1;
	अगर (rate < td->dvco_rate_min) अणु
		पूर्णांक scale;

		scale = DIV_ROUND_CLOSEST(rate / 1000 * DFLL_FREQ_REQ_SCALE_MAX,
					  td->dvco_rate_min / 1000);
		अगर (!scale) अणु
			dev_err(td->dev, "%s: Rate %lu is too low\n",
				__func__, rate);
			वापस -EINVAL;
		पूर्ण
		req->scale_bits = scale - 1;
		rate = td->dvco_rate_min;
	पूर्ण

	/* Convert requested rate पूर्णांकo frequency request and scale settings */
	val = DVCO_RATE_TO_MULT(rate, td->ref_rate);
	अगर (val > FREQ_MAX) अणु
		dev_err(td->dev, "%s: Rate %lu is above dfll range\n",
			__func__, rate);
		वापस -EINVAL;
	पूर्ण
	req->mult_bits = val;
	req->dvco_target_rate = MULT_TO_DVCO_RATE(req->mult_bits, td->ref_rate);
	req->rate = dfll_scale_dvco_rate(req->scale_bits,
					 req->dvco_target_rate);
	req->lut_index = find_lut_index_क्रम_rate(td, req->dvco_target_rate);
	अगर (req->lut_index < 0)
		वापस req->lut_index;

	वापस 0;
पूर्ण

/**
 * dfll_set_frequency_request - start the frequency change operation
 * @td: DFLL instance
 * @req: rate request काष्ठाure
 *
 * Tell the DFLL to try to change its output frequency to the
 * frequency represented by @req. DFLL must be in बंदd-loop mode.
 */
अटल व्योम dfll_set_frequency_request(काष्ठा tegra_dfll *td,
				       काष्ठा dfll_rate_req *req)
अणु
	u32 val = 0;
	पूर्णांक क्रमce_val;
	पूर्णांक coef = 128; /* FIXME: td->cg_scale? */;

	क्रमce_val = (req->lut_index - td->lut_safe) * coef / td->cg;
	क्रमce_val = clamp(क्रमce_val, FORCE_MIN, FORCE_MAX);

	val |= req->mult_bits << DFLL_FREQ_REQ_MULT_SHIFT;
	val |= req->scale_bits << DFLL_FREQ_REQ_SCALE_SHIFT;
	val |= ((u32)क्रमce_val << DFLL_FREQ_REQ_FORCE_SHIFT) &
		DFLL_FREQ_REQ_FORCE_MASK;
	val |= DFLL_FREQ_REQ_FREQ_VALID | DFLL_FREQ_REQ_FORCE_ENABLE;

	dfll_ग_लिखोl(td, val, DFLL_FREQ_REQ);
	dfll_wmb(td);
पूर्ण

/**
 * tegra_dfll_request_rate - set the next rate क्रम the DFLL to tune to
 * @td: DFLL instance
 * @rate: घड़ी rate to target
 *
 * Convert the requested घड़ी rate @rate पूर्णांकo the DFLL control logic
 * settings. In बंदd-loop mode, update new settings immediately to
 * adjust DFLL output rate accordingly. Otherwise, just save them
 * until the next चयन to बंदd loop. Returns 0 upon success,
 * -EPERM अगर the DFLL driver has not yet been initialized, or -EINVAL
 * अगर @rate is outside the DFLL's tunable range.
 */
अटल पूर्णांक dfll_request_rate(काष्ठा tegra_dfll *td, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक ret;
	काष्ठा dfll_rate_req req;

	अगर (td->mode == DFLL_UNINITIALIZED) अणु
		dev_err(td->dev, "%s: Cannot set DFLL rate in %s mode\n",
			__func__, mode_name[td->mode]);
		वापस -EPERM;
	पूर्ण

	ret = dfll_calculate_rate_request(td, &req, rate);
	अगर (ret)
		वापस ret;

	td->last_unrounded_rate = rate;
	td->last_req = req;

	अगर (td->mode == DFLL_CLOSED_LOOP)
		dfll_set_frequency_request(td, &td->last_req);

	वापस 0;
पूर्ण

/*
 * DFLL enable/disable & खोलो-loop <-> बंदd-loop transitions
 */

/**
 * dfll_disable - चयन from खोलो-loop mode to disabled mode
 * @td: DFLL instance
 *
 * Switch from OPEN_LOOP state to DISABLED state. Returns 0 upon success
 * or -EPERM अगर the DFLL is not currently in खोलो-loop mode.
 */
अटल पूर्णांक dfll_disable(काष्ठा tegra_dfll *td)
अणु
	अगर (td->mode != DFLL_OPEN_LOOP) अणु
		dev_err(td->dev, "cannot disable DFLL in %s mode\n",
			mode_name[td->mode]);
		वापस -EINVAL;
	पूर्ण

	dfll_set_mode(td, DFLL_DISABLED);
	pm_runसमय_put_sync(td->dev);

	वापस 0;
पूर्ण

/**
 * dfll_enable - चयन a disabled DFLL to खोलो-loop mode
 * @td: DFLL instance
 *
 * Switch from DISABLED state to OPEN_LOOP state. Returns 0 upon success
 * or -EPERM अगर the DFLL is not currently disabled.
 */
अटल पूर्णांक dfll_enable(काष्ठा tegra_dfll *td)
अणु
	अगर (td->mode != DFLL_DISABLED) अणु
		dev_err(td->dev, "cannot enable DFLL in %s mode\n",
			mode_name[td->mode]);
		वापस -EPERM;
	पूर्ण

	pm_runसमय_get_sync(td->dev);
	dfll_set_mode(td, DFLL_OPEN_LOOP);

	वापस 0;
पूर्ण

/**
 * dfll_set_खोलो_loop_config - prepare to चयन to खोलो-loop mode
 * @td: DFLL instance
 *
 * Prepare to चयन the DFLL to खोलो-loop mode. This चयनes the
 * DFLL to the low-voltage tuning range, ensures that I2C output
 * क्रमcing is disabled, and disables the output घड़ी rate scaler.
 * The DFLL's low-voltage tuning range parameters must be
 * अक्षरacterized to keep the करोwnstream device stable at any DVCO
 * input voltage. No वापस value.
 */
अटल व्योम dfll_set_खोलो_loop_config(काष्ठा tegra_dfll *td)
अणु
	u32 val;

	/* always tune low (safe) in खोलो loop */
	अगर (td->tune_range != DFLL_TUNE_LOW)
		dfll_tune_low(td);

	val = dfll_पढ़ोl(td, DFLL_FREQ_REQ);
	val |= DFLL_FREQ_REQ_SCALE_MASK;
	val &= ~DFLL_FREQ_REQ_FORCE_ENABLE;
	dfll_ग_लिखोl(td, val, DFLL_FREQ_REQ);
	dfll_wmb(td);
पूर्ण

/**
 * tegra_dfll_lock - चयन from खोलो-loop to बंदd-loop mode
 * @td: DFLL instance
 *
 * Switch from OPEN_LOOP state to CLOSED_LOOP state. Returns 0 upon success,
 * -EINVAL अगर the DFLL's target rate hasn't been set yet, or -EPERM अगर the
 * DFLL is not currently in खोलो-loop mode.
 */
अटल पूर्णांक dfll_lock(काष्ठा tegra_dfll *td)
अणु
	काष्ठा dfll_rate_req *req = &td->last_req;

	चयन (td->mode) अणु
	हाल DFLL_CLOSED_LOOP:
		वापस 0;

	हाल DFLL_OPEN_LOOP:
		अगर (req->rate == 0) अणु
			dev_err(td->dev, "%s: Cannot lock DFLL at rate 0\n",
				__func__);
			वापस -EINVAL;
		पूर्ण

		अगर (td->pmu_अगर == TEGRA_DFLL_PMU_PWM)
			dfll_pwm_set_output_enabled(td, true);
		अन्यथा
			dfll_i2c_set_output_enabled(td, true);

		dfll_set_mode(td, DFLL_CLOSED_LOOP);
		dfll_set_frequency_request(td, req);
		dfll_set_क्रमce_output_enabled(td, false);
		वापस 0;

	शेष:
		BUG_ON(td->mode > DFLL_CLOSED_LOOP);
		dev_err(td->dev, "%s: Cannot lock DFLL in %s mode\n",
			__func__, mode_name[td->mode]);
		वापस -EPERM;
	पूर्ण
पूर्ण

/**
 * tegra_dfll_unlock - चयन from बंदd-loop to खोलो-loop mode
 * @td: DFLL instance
 *
 * Switch from CLOSED_LOOP state to OPEN_LOOP state. Returns 0 upon success,
 * or -EPERM अगर the DFLL is not currently in खोलो-loop mode.
 */
अटल पूर्णांक dfll_unlock(काष्ठा tegra_dfll *td)
अणु
	चयन (td->mode) अणु
	हाल DFLL_CLOSED_LOOP:
		dfll_set_खोलो_loop_config(td);
		dfll_set_mode(td, DFLL_OPEN_LOOP);
		अगर (td->pmu_अगर == TEGRA_DFLL_PMU_PWM)
			dfll_pwm_set_output_enabled(td, false);
		अन्यथा
			dfll_i2c_set_output_enabled(td, false);
		वापस 0;

	हाल DFLL_OPEN_LOOP:
		वापस 0;

	शेष:
		BUG_ON(td->mode > DFLL_CLOSED_LOOP);
		dev_err(td->dev, "%s: Cannot unlock DFLL in %s mode\n",
			__func__, mode_name[td->mode]);
		वापस -EPERM;
	पूर्ण
पूर्ण

/*
 * Clock framework पूर्णांकegration
 *
 * When the DFLL is being controlled by the CCF, always enter बंदd loop
 * mode when the clk is enabled. This requires that a DFLL rate request
 * has been set beक्रमehand, which implies that a clk_set_rate() call is
 * always required beक्रमe a clk_enable().
 */

अटल पूर्णांक dfll_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_dfll *td = clk_hw_to_dfll(hw);

	वापस dfll_is_running(td);
पूर्ण

अटल पूर्णांक dfll_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_dfll *td = clk_hw_to_dfll(hw);
	पूर्णांक ret;

	ret = dfll_enable(td);
	अगर (ret)
		वापस ret;

	ret = dfll_lock(td);
	अगर (ret)
		dfll_disable(td);

	वापस ret;
पूर्ण

अटल व्योम dfll_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_dfll *td = clk_hw_to_dfll(hw);
	पूर्णांक ret;

	ret = dfll_unlock(td);
	अगर (!ret)
		dfll_disable(td);
पूर्ण

अटल अचिन्हित दीर्घ dfll_clk_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_dfll *td = clk_hw_to_dfll(hw);

	वापस td->last_unrounded_rate;
पूर्ण

/* Must use determine_rate since it allows क्रम rates exceeding 2^31-1 */
अटल पूर्णांक dfll_clk_determine_rate(काष्ठा clk_hw *hw,
				   काष्ठा clk_rate_request *clk_req)
अणु
	काष्ठा tegra_dfll *td = clk_hw_to_dfll(hw);
	काष्ठा dfll_rate_req req;
	पूर्णांक ret;

	ret = dfll_calculate_rate_request(td, &req, clk_req->rate);
	अगर (ret)
		वापस ret;

	/*
	 * Don't set the rounded rate, since it doesn't really matter as
	 * the output rate will be voltage controlled anyway, and cpufreq
	 * freaks out अगर any rounding happens.
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक dfll_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_dfll *td = clk_hw_to_dfll(hw);

	वापस dfll_request_rate(td, rate);
पूर्ण

अटल स्थिर काष्ठा clk_ops dfll_clk_ops = अणु
	.is_enabled	= dfll_clk_is_enabled,
	.enable		= dfll_clk_enable,
	.disable	= dfll_clk_disable,
	.recalc_rate	= dfll_clk_recalc_rate,
	.determine_rate	= dfll_clk_determine_rate,
	.set_rate	= dfll_clk_set_rate,
पूर्ण;

अटल काष्ठा clk_init_data dfll_clk_init_data = अणु
	.ops		= &dfll_clk_ops,
	.num_parents	= 0,
पूर्ण;

/**
 * dfll_रेजिस्टर_clk - रेजिस्टर the DFLL output घड़ी with the घड़ी framework
 * @td: DFLL instance
 *
 * Register the DFLL's output घड़ी with the Linux घड़ी framework and रेजिस्टर
 * the DFLL driver as an OF घड़ी provider. Returns 0 upon success or -EINVAL
 * or -ENOMEM upon failure.
 */
अटल पूर्णांक dfll_रेजिस्टर_clk(काष्ठा tegra_dfll *td)
अणु
	पूर्णांक ret;

	dfll_clk_init_data.name = td->output_घड़ी_name;
	td->dfll_clk_hw.init = &dfll_clk_init_data;

	td->dfll_clk = clk_रेजिस्टर(td->dev, &td->dfll_clk_hw);
	अगर (IS_ERR(td->dfll_clk)) अणु
		dev_err(td->dev, "DFLL clock registration error\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_clk_add_provider(td->dev->of_node, of_clk_src_simple_get,
				  td->dfll_clk);
	अगर (ret) अणु
		dev_err(td->dev, "of_clk_add_provider() failed\n");

		clk_unरेजिस्टर(td->dfll_clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dfll_unरेजिस्टर_clk - unरेजिस्टर the DFLL output घड़ी
 * @td: DFLL instance
 *
 * Unरेजिस्टर the DFLL's output घड़ी from the Linux घड़ी framework
 * and from clkdev. No वापस value.
 */
अटल व्योम dfll_unरेजिस्टर_clk(काष्ठा tegra_dfll *td)
अणु
	of_clk_del_provider(td->dev->of_node);
	clk_unरेजिस्टर(td->dfll_clk);
	td->dfll_clk = शून्य;
पूर्ण

/*
 * Debugfs पूर्णांकerface
 */

#अगर_घोषित CONFIG_DEBUG_FS
/*
 * Monitor control
 */

/**
 * dfll_calc_monitored_rate - convert DFLL_MONITOR_DATA_VAL rate पूर्णांकo real freq
 * @monitor_data: value पढ़ो from the DFLL_MONITOR_DATA_VAL bitfield
 * @ref_rate: DFLL reference घड़ी rate
 *
 * Convert @monitor_data from DFLL_MONITOR_DATA_VAL units पूर्णांकo cycles
 * per second. Returns the converted value.
 */
अटल u64 dfll_calc_monitored_rate(u32 monitor_data,
				    अचिन्हित दीर्घ ref_rate)
अणु
	वापस monitor_data * (ref_rate / REF_CLK_CYC_PER_DVCO_SAMPLE);
पूर्ण

/**
 * dfll_पढ़ो_monitor_rate - वापस the DFLL's output rate from पूर्णांकernal monitor
 * @td: DFLL instance
 *
 * If the DFLL is enabled, वापस the last rate reported by the DFLL's
 * पूर्णांकernal monitoring hardware. This works in both खोलो-loop and
 * बंदd-loop mode, and takes the output scaler setting पूर्णांकo account.
 * Assumes that the monitor was programmed to monitor frequency beक्रमe
 * the sample period started. If the driver believes that the DFLL is
 * currently uninitialized or disabled, it will वापस 0, since
 * otherwise the DFLL monitor data रेजिस्टर will वापस the last
 * measured rate from when the DFLL was active.
 */
अटल u64 dfll_पढ़ो_monitor_rate(काष्ठा tegra_dfll *td)
अणु
	u32 v, s;
	u64 pre_scaler_rate, post_scaler_rate;

	अगर (!dfll_is_running(td))
		वापस 0;

	v = dfll_पढ़ोl(td, DFLL_MONITOR_DATA);
	v = (v & DFLL_MONITOR_DATA_VAL_MASK) >> DFLL_MONITOR_DATA_VAL_SHIFT;
	pre_scaler_rate = dfll_calc_monitored_rate(v, td->ref_rate);

	s = dfll_पढ़ोl(td, DFLL_FREQ_REQ);
	s = (s & DFLL_FREQ_REQ_SCALE_MASK) >> DFLL_FREQ_REQ_SCALE_SHIFT;
	post_scaler_rate = dfll_scale_dvco_rate(s, pre_scaler_rate);

	वापस post_scaler_rate;
पूर्ण

अटल पूर्णांक attr_enable_get(व्योम *data, u64 *val)
अणु
	काष्ठा tegra_dfll *td = data;

	*val = dfll_is_running(td);

	वापस 0;
पूर्ण
अटल पूर्णांक attr_enable_set(व्योम *data, u64 val)
अणु
	काष्ठा tegra_dfll *td = data;

	वापस val ? dfll_enable(td) : dfll_disable(td);
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(enable_fops, attr_enable_get, attr_enable_set,
			 "%llu\n");

अटल पूर्णांक attr_lock_get(व्योम *data, u64 *val)
अणु
	काष्ठा tegra_dfll *td = data;

	*val = (td->mode == DFLL_CLOSED_LOOP);

	वापस 0;
पूर्ण
अटल पूर्णांक attr_lock_set(व्योम *data, u64 val)
अणु
	काष्ठा tegra_dfll *td = data;

	वापस val ? dfll_lock(td) :  dfll_unlock(td);
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(lock_fops, attr_lock_get, attr_lock_set, "%llu\n");

अटल पूर्णांक attr_rate_get(व्योम *data, u64 *val)
अणु
	काष्ठा tegra_dfll *td = data;

	*val = dfll_पढ़ो_monitor_rate(td);

	वापस 0;
पूर्ण

अटल पूर्णांक attr_rate_set(व्योम *data, u64 val)
अणु
	काष्ठा tegra_dfll *td = data;

	वापस dfll_request_rate(td, val);
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(rate_fops, attr_rate_get, attr_rate_set, "%llu\n");

अटल पूर्णांक attr_रेजिस्टरs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	u32 val, offs;
	काष्ठा tegra_dfll *td = s->निजी;

	seq_माला_दो(s, "CONTROL REGISTERS:\n");
	क्रम (offs = 0; offs <= DFLL_MONITOR_DATA; offs += 4) अणु
		अगर (offs == DFLL_OUTPUT_CFG)
			val = dfll_i2c_पढ़ोl(td, offs);
		अन्यथा
			val = dfll_पढ़ोl(td, offs);
		seq_म_लिखो(s, "[0x%02x] = 0x%08x\n", offs, val);
	पूर्ण

	seq_माला_दो(s, "\nI2C and INTR REGISTERS:\n");
	क्रम (offs = DFLL_I2C_CFG; offs <= DFLL_I2C_STS; offs += 4)
		seq_म_लिखो(s, "[0x%02x] = 0x%08x\n", offs,
			   dfll_i2c_पढ़ोl(td, offs));
	क्रम (offs = DFLL_INTR_STS; offs <= DFLL_INTR_EN; offs += 4)
		seq_म_लिखो(s, "[0x%02x] = 0x%08x\n", offs,
			   dfll_i2c_पढ़ोl(td, offs));

	अगर (td->pmu_अगर == TEGRA_DFLL_PMU_I2C) अणु
		seq_माला_दो(s, "\nINTEGRATED I2C CONTROLLER REGISTERS:\n");
		offs = DFLL_I2C_CLK_DIVISOR;
		seq_म_लिखो(s, "[0x%02x] = 0x%08x\n", offs,
			   __raw_पढ़ोl(td->i2c_controller_base + offs));

		seq_माला_दो(s, "\nLUT:\n");
		क्रम (offs = 0; offs <  4 * MAX_DFLL_VOLTAGES; offs += 4)
			seq_म_लिखो(s, "[0x%02x] = 0x%08x\n", offs,
				   __raw_पढ़ोl(td->lut_base + offs));
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(attr_रेजिस्टरs);

अटल व्योम dfll_debug_init(काष्ठा tegra_dfll *td)
अणु
	काष्ठा dentry *root;

	अगर (!td || (td->mode == DFLL_UNINITIALIZED))
		वापस;

	root = debugfs_create_dir("tegra_dfll_fcpu", शून्य);
	td->debugfs_dir = root;

	debugfs_create_file_unsafe("enable", 0644, root, td,
				   &enable_fops);
	debugfs_create_file_unsafe("lock", 0444, root, td, &lock_fops);
	debugfs_create_file_unsafe("rate", 0444, root, td, &rate_fops);
	debugfs_create_file("registers", 0444, root, td, &attr_रेजिस्टरs_fops);
पूर्ण

#अन्यथा
अटल व्योम अंतरभूत dfll_debug_init(काष्ठा tegra_dfll *td) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/*
 * DFLL initialization
 */

/**
 * dfll_set_शेष_params - program non-output related DFLL parameters
 * @td: DFLL instance
 *
 * During DFLL driver initialization or resume from context loss,
 * program parameters क्रम the बंदd loop पूर्णांकegrator, DVCO tuning,
 * voltage droop control and monitor control.
 */
अटल व्योम dfll_set_शेष_params(काष्ठा tegra_dfll *td)
अणु
	u32 val;

	val = DIV_ROUND_UP(td->ref_rate, td->sample_rate * 32);
	BUG_ON(val > DFLL_CONFIG_DIV_MASK);
	dfll_ग_लिखोl(td, val, DFLL_CONFIG);

	val = (td->क्रमce_mode << DFLL_PARAMS_FORCE_MODE_SHIFT) |
		(td->cf << DFLL_PARAMS_CF_PARAM_SHIFT) |
		(td->ci << DFLL_PARAMS_CI_PARAM_SHIFT) |
		(td->cg << DFLL_PARAMS_CG_PARAM_SHIFT) |
		(td->cg_scale ? DFLL_PARAMS_CG_SCALE : 0);
	dfll_ग_लिखोl(td, val, DFLL_PARAMS);

	dfll_tune_low(td);
	dfll_ग_लिखोl(td, td->droop_ctrl, DFLL_DROOP_CTRL);
	dfll_ग_लिखोl(td, DFLL_MONITOR_CTRL_FREQ, DFLL_MONITOR_CTRL);
पूर्ण

/**
 * dfll_init_clks - clk_get() the DFLL source घड़ीs
 * @td: DFLL instance
 *
 * Call clk_get() on the DFLL source घड़ीs and save the poपूर्णांकers क्रम later
 * use. Returns 0 upon success or error (see devm_clk_get) अगर one or more
 * of the घड़ीs couldn't be looked up.
 */
अटल पूर्णांक dfll_init_clks(काष्ठा tegra_dfll *td)
अणु
	td->ref_clk = devm_clk_get(td->dev, "ref");
	अगर (IS_ERR(td->ref_clk)) अणु
		dev_err(td->dev, "missing ref clock\n");
		वापस PTR_ERR(td->ref_clk);
	पूर्ण

	td->soc_clk = devm_clk_get(td->dev, "soc");
	अगर (IS_ERR(td->soc_clk)) अणु
		dev_err(td->dev, "missing soc clock\n");
		वापस PTR_ERR(td->soc_clk);
	पूर्ण

	td->i2c_clk = devm_clk_get(td->dev, "i2c");
	अगर (IS_ERR(td->i2c_clk)) अणु
		dev_err(td->dev, "missing i2c clock\n");
		वापस PTR_ERR(td->i2c_clk);
	पूर्ण
	td->i2c_clk_rate = clk_get_rate(td->i2c_clk);

	वापस 0;
पूर्ण

/**
 * dfll_init - Prepare the DFLL IP block क्रम use
 * @td: DFLL instance
 *
 * Do everything necessary to prepare the DFLL IP block क्रम use. The
 * DFLL will be left in DISABLED state. Called by dfll_probe().
 * Returns 0 upon success, or passes aदीर्घ the error from whatever
 * function वापसed it.
 */
अटल पूर्णांक dfll_init(काष्ठा tegra_dfll *td)
अणु
	पूर्णांक ret;

	td->ref_rate = clk_get_rate(td->ref_clk);
	अगर (td->ref_rate != REF_CLOCK_RATE) अणु
		dev_err(td->dev, "unexpected ref clk rate %lu, expecting %lu",
			td->ref_rate, REF_CLOCK_RATE);
		वापस -EINVAL;
	पूर्ण

	reset_control_deनिश्चित(td->dvco_rst);

	ret = clk_prepare(td->ref_clk);
	अगर (ret) अणु
		dev_err(td->dev, "failed to prepare ref_clk\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare(td->soc_clk);
	अगर (ret) अणु
		dev_err(td->dev, "failed to prepare soc_clk\n");
		जाओ di_err1;
	पूर्ण

	ret = clk_prepare(td->i2c_clk);
	अगर (ret) अणु
		dev_err(td->dev, "failed to prepare i2c_clk\n");
		जाओ di_err2;
	पूर्ण

	td->last_unrounded_rate = 0;

	pm_runसमय_enable(td->dev);
	pm_runसमय_get_sync(td->dev);

	dfll_set_mode(td, DFLL_DISABLED);
	dfll_set_शेष_params(td);

	अगर (td->soc->init_घड़ी_प्रकारrimmers)
		td->soc->init_घड़ी_प्रकारrimmers();

	dfll_set_खोलो_loop_config(td);

	dfll_init_out_अगर(td);

	pm_runसमय_put_sync(td->dev);

	वापस 0;

di_err2:
	clk_unprepare(td->soc_clk);
di_err1:
	clk_unprepare(td->ref_clk);

	reset_control_निश्चित(td->dvco_rst);

	वापस ret;
पूर्ण

/**
 * tegra_dfll_suspend - check DFLL is disabled
 * @dev: DFLL instance
 *
 * DFLL घड़ी should be disabled by the CPUFreq driver. So, make
 * sure it is disabled and disable all घड़ीs needed by the DFLL.
 */
पूर्णांक tegra_dfll_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_dfll *td = dev_get_drvdata(dev);

	अगर (dfll_is_running(td)) अणु
		dev_err(td->dev, "DFLL still enabled while suspending\n");
		वापस -EBUSY;
	पूर्ण

	reset_control_निश्चित(td->dvco_rst);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tegra_dfll_suspend);

/**
 * tegra_dfll_resume - reinitialize DFLL on resume
 * @dev: DFLL instance
 *
 * DFLL is disabled and reset during suspend and resume.
 * So, reinitialize the DFLL IP block back क्रम use.
 * DFLL घड़ी is enabled later in बंदd loop mode by CPUFreq
 * driver beक्रमe चयनing its घड़ी source to DFLL output.
 */
पूर्णांक tegra_dfll_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_dfll *td = dev_get_drvdata(dev);

	reset_control_deनिश्चित(td->dvco_rst);

	pm_runसमय_get_sync(td->dev);

	dfll_set_mode(td, DFLL_DISABLED);
	dfll_set_शेष_params(td);

	अगर (td->soc->init_घड़ी_प्रकारrimmers)
		td->soc->init_घड़ी_प्रकारrimmers();

	dfll_set_खोलो_loop_config(td);

	dfll_init_out_अगर(td);

	pm_runसमय_put_sync(td->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tegra_dfll_resume);

/*
 * DT data fetch
 */

/*
 * Find a PMIC voltage रेजिस्टर-to-voltage mapping क्रम the given voltage.
 * An exact voltage match is required.
 */
अटल पूर्णांक find_vdd_map_entry_exact(काष्ठा tegra_dfll *td, पूर्णांक uV)
अणु
	पूर्णांक i, n_voltages, reg_uV,reg_volt_id, align_step;

	अगर (WARN_ON(td->pmu_अगर == TEGRA_DFLL_PMU_PWM))
		वापस -EINVAL;

	align_step = uV / td->soc->alignment.step_uv;
	n_voltages = regulator_count_voltages(td->vdd_reg);
	क्रम (i = 0; i < n_voltages; i++) अणु
		reg_uV = regulator_list_voltage(td->vdd_reg, i);
		अगर (reg_uV < 0)
			अवरोध;

		reg_volt_id = reg_uV / td->soc->alignment.step_uv;

		अगर (align_step == reg_volt_id)
			वापस i;
	पूर्ण

	dev_err(td->dev, "no voltage map entry for %d uV\n", uV);
	वापस -EINVAL;
पूर्ण

/*
 * Find a PMIC voltage रेजिस्टर-to-voltage mapping क्रम the given voltage,
 * rounding up to the बंदst supported voltage.
 * */
अटल पूर्णांक find_vdd_map_entry_min(काष्ठा tegra_dfll *td, पूर्णांक uV)
अणु
	पूर्णांक i, n_voltages, reg_uV, reg_volt_id, align_step;

	अगर (WARN_ON(td->pmu_अगर == TEGRA_DFLL_PMU_PWM))
		वापस -EINVAL;

	align_step = uV / td->soc->alignment.step_uv;
	n_voltages = regulator_count_voltages(td->vdd_reg);
	क्रम (i = 0; i < n_voltages; i++) अणु
		reg_uV = regulator_list_voltage(td->vdd_reg, i);
		अगर (reg_uV < 0)
			अवरोध;

		reg_volt_id = reg_uV / td->soc->alignment.step_uv;

		अगर (align_step <= reg_volt_id)
			वापस i;
	पूर्ण

	dev_err(td->dev, "no voltage map entry rounding to %d uV\n", uV);
	वापस -EINVAL;
पूर्ण

/*
 * dfll_build_pwm_lut - build the PWM regulator lookup table
 * @td: DFLL instance
 * @v_max: Vmax from OPP table
 *
 * Look-up table in h/w is ignored when PWM is used as DFLL पूर्णांकerface to PMIC.
 * In this हाल बंदd loop output is controlling duty cycle directly. The s/w
 * look-up that maps PWM duty cycle to voltage is still built by this function.
 */
अटल पूर्णांक dfll_build_pwm_lut(काष्ठा tegra_dfll *td, अचिन्हित दीर्घ v_max)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ rate, reg_volt;
	u8 lut_bottom = MAX_DFLL_VOLTAGES;
	पूर्णांक v_min = td->soc->cvb->min_millivolts * 1000;

	क्रम (i = 0; i < MAX_DFLL_VOLTAGES; i++) अणु
		reg_volt = td->lut_uv[i];

		/* since opp voltage is exact mv */
		reg_volt = (reg_volt / 1000) * 1000;
		अगर (reg_volt > v_max)
			अवरोध;

		td->lut[i] = i;
		अगर ((lut_bottom == MAX_DFLL_VOLTAGES) && (reg_volt >= v_min))
			lut_bottom = i;
	पूर्ण

	/* determine voltage boundaries */
	td->lut_size = i;
	अगर ((lut_bottom == MAX_DFLL_VOLTAGES) ||
	    (lut_bottom + 1 >= td->lut_size)) अणु
		dev_err(td->dev, "no voltage above DFLL minimum %d mV\n",
			td->soc->cvb->min_millivolts);
		वापस -EINVAL;
	पूर्ण
	td->lut_bottom = lut_bottom;

	/* determine rate boundaries */
	rate = get_dvco_rate_below(td, td->lut_bottom);
	अगर (!rate) अणु
		dev_err(td->dev, "no opp below DFLL minimum voltage %d mV\n",
			td->soc->cvb->min_millivolts);
		वापस -EINVAL;
	पूर्ण
	td->dvco_rate_min = rate;

	वापस 0;
पूर्ण

/**
 * dfll_build_i2c_lut - build the I2C voltage रेजिस्टर lookup table
 * @td: DFLL instance
 * @v_max: Vmax from OPP table
 *
 * The DFLL hardware has 33 bytes of look-up table RAM that must be filled with
 * PMIC voltage रेजिस्टर values that span the entire DFLL operating range.
 * This function builds the look-up table based on the OPP table provided by
 * the soc-specअगरic platक्रमm driver (td->soc->opp_dev) and the PMIC
 * रेजिस्टर-to-voltage mapping queried from the regulator framework.
 *
 * On success, fills in td->lut and वापसs 0, or -err on failure.
 */
अटल पूर्णांक dfll_build_i2c_lut(काष्ठा tegra_dfll *td, अचिन्हित दीर्घ v_max)
अणु
	अचिन्हित दीर्घ rate, v, v_opp;
	पूर्णांक ret = -EINVAL;
	पूर्णांक j, selector, lut;

	v = td->soc->cvb->min_millivolts * 1000;
	lut = find_vdd_map_entry_exact(td, v);
	अगर (lut < 0)
		जाओ out;
	td->lut[0] = lut;
	td->lut_bottom = 0;

	क्रम (j = 1, rate = 0; ; rate++) अणु
		काष्ठा dev_pm_opp *opp;

		opp = dev_pm_opp_find_freq_उच्चमान(td->soc->dev, &rate);
		अगर (IS_ERR(opp))
			अवरोध;
		v_opp = dev_pm_opp_get_voltage(opp);

		अगर (v_opp <= td->soc->cvb->min_millivolts * 1000)
			td->dvco_rate_min = dev_pm_opp_get_freq(opp);

		dev_pm_opp_put(opp);

		क्रम (;;) अणु
			v += max(1UL, (v_max - v) / (MAX_DFLL_VOLTAGES - j));
			अगर (v >= v_opp)
				अवरोध;

			selector = find_vdd_map_entry_min(td, v);
			अगर (selector < 0)
				जाओ out;
			अगर (selector != td->lut[j - 1])
				td->lut[j++] = selector;
		पूर्ण

		v = (j == MAX_DFLL_VOLTAGES - 1) ? v_max : v_opp;
		selector = find_vdd_map_entry_exact(td, v);
		अगर (selector < 0)
			जाओ out;
		अगर (selector != td->lut[j - 1])
			td->lut[j++] = selector;

		अगर (v >= v_max)
			अवरोध;
	पूर्ण
	td->lut_size = j;

	अगर (!td->dvco_rate_min)
		dev_err(td->dev, "no opp above DFLL minimum voltage %d mV\n",
			td->soc->cvb->min_millivolts);
	अन्यथा अणु
		ret = 0;
		क्रम (j = 0; j < td->lut_size; j++)
			td->lut_uv[j] =
				regulator_list_voltage(td->vdd_reg,
						       td->lut[j]);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक dfll_build_lut(काष्ठा tegra_dfll *td)
अणु
	अचिन्हित दीर्घ rate, v_max;
	काष्ठा dev_pm_opp *opp;

	rate = अच_दीर्घ_उच्च;
	opp = dev_pm_opp_find_freq_न्यूनमान(td->soc->dev, &rate);
	अगर (IS_ERR(opp)) अणु
		dev_err(td->dev, "couldn't get vmax opp, empty opp table?\n");
		वापस -EINVAL;
	पूर्ण
	v_max = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	अगर (td->pmu_अगर == TEGRA_DFLL_PMU_PWM)
		वापस dfll_build_pwm_lut(td, v_max);
	अन्यथा
		वापस dfll_build_i2c_lut(td, v_max);
पूर्ण

/**
 * पढ़ो_dt_param - helper function क्रम पढ़ोing required parameters from the DT
 * @td: DFLL instance
 * @param: DT property name
 * @dest: output poपूर्णांकer क्रम the value पढ़ो
 *
 * Read a required numeric parameter from the DFLL device node, or complain
 * अगर the property करोesn't exist. Returns a boolean indicating success क्रम
 * easy chaining of multiple calls to this function.
 */
अटल bool पढ़ो_dt_param(काष्ठा tegra_dfll *td, स्थिर अक्षर *param, u32 *dest)
अणु
	पूर्णांक err = of_property_पढ़ो_u32(td->dev->of_node, param, dest);

	अगर (err < 0) अणु
		dev_err(td->dev, "failed to read DT parameter %s: %d\n",
			param, err);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * dfll_fetch_i2c_params - query PMIC I2C params from DT & regulator subप्रणाली
 * @td: DFLL instance
 *
 * Read all the parameters required क्रम operation in I2C mode. The parameters
 * can originate from the device tree or the regulator subप्रणाली.
 * Returns 0 on success or -err on failure.
 */
अटल पूर्णांक dfll_fetch_i2c_params(काष्ठा tegra_dfll *td)
अणु
	काष्ठा regmap *regmap;
	काष्ठा device *i2c_dev;
	काष्ठा i2c_client *i2c_client;
	पूर्णांक vsel_reg, vsel_mask;
	पूर्णांक ret;

	अगर (!पढ़ो_dt_param(td, "nvidia,i2c-fs-rate", &td->i2c_fs_rate))
		वापस -EINVAL;

	regmap = regulator_get_regmap(td->vdd_reg);
	i2c_dev = regmap_get_device(regmap);
	i2c_client = to_i2c_client(i2c_dev);

	td->i2c_slave_addr = i2c_client->addr;

	ret = regulator_get_hardware_vsel_रेजिस्टर(td->vdd_reg,
						   &vsel_reg,
						   &vsel_mask);
	अगर (ret < 0) अणु
		dev_err(td->dev,
			"regulator unsuitable for DFLL I2C operation\n");
		वापस -EINVAL;
	पूर्ण
	td->i2c_reg = vsel_reg;

	वापस 0;
पूर्ण

अटल पूर्णांक dfll_fetch_pwm_params(काष्ठा tegra_dfll *td)
अणु
	पूर्णांक ret, i;
	u32 pwm_period;

	अगर (!td->soc->alignment.step_uv || !td->soc->alignment.offset_uv) अणु
		dev_err(td->dev,
			"Missing step or alignment info for PWM regulator");
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < MAX_DFLL_VOLTAGES; i++)
		td->lut_uv[i] = td->soc->alignment.offset_uv +
				i * td->soc->alignment.step_uv;

	ret = पढ़ो_dt_param(td, "nvidia,pwm-tristate-microvolts",
			    &td->reg_init_uV);
	अगर (!ret) अणु
		dev_err(td->dev, "couldn't get initialized voltage\n");
		वापस -EINVAL;
	पूर्ण

	ret = पढ़ो_dt_param(td, "nvidia,pwm-period-nanoseconds", &pwm_period);
	अगर (!ret) अणु
		dev_err(td->dev, "couldn't get PWM period\n");
		वापस -EINVAL;
	पूर्ण
	td->pwm_rate = (NSEC_PER_SEC / pwm_period) * (MAX_DFLL_VOLTAGES - 1);

	td->pwm_pin = devm_pinctrl_get(td->dev);
	अगर (IS_ERR(td->pwm_pin)) अणु
		dev_err(td->dev, "DT: missing pinctrl device\n");
		वापस PTR_ERR(td->pwm_pin);
	पूर्ण

	td->pwm_enable_state = pinctrl_lookup_state(td->pwm_pin,
						    "dvfs_pwm_enable");
	अगर (IS_ERR(td->pwm_enable_state)) अणु
		dev_err(td->dev, "DT: missing pwm enabled state\n");
		वापस PTR_ERR(td->pwm_enable_state);
	पूर्ण

	td->pwm_disable_state = pinctrl_lookup_state(td->pwm_pin,
						     "dvfs_pwm_disable");
	अगर (IS_ERR(td->pwm_disable_state)) अणु
		dev_err(td->dev, "DT: missing pwm disabled state\n");
		वापस PTR_ERR(td->pwm_disable_state);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dfll_fetch_common_params - पढ़ो DFLL parameters from the device tree
 * @td: DFLL instance
 *
 * Read all the DT parameters that are common to both I2C and PWM operation.
 * Returns 0 on success or -EINVAL on any failure.
 */
अटल पूर्णांक dfll_fetch_common_params(काष्ठा tegra_dfll *td)
अणु
	bool ok = true;

	ok &= पढ़ो_dt_param(td, "nvidia,droop-ctrl", &td->droop_ctrl);
	ok &= पढ़ो_dt_param(td, "nvidia,sample-rate", &td->sample_rate);
	ok &= पढ़ो_dt_param(td, "nvidia,force-mode", &td->क्रमce_mode);
	ok &= पढ़ो_dt_param(td, "nvidia,cf", &td->cf);
	ok &= पढ़ो_dt_param(td, "nvidia,ci", &td->ci);
	ok &= पढ़ो_dt_param(td, "nvidia,cg", &td->cg);
	td->cg_scale = of_property_पढ़ो_bool(td->dev->of_node,
					     "nvidia,cg-scale");

	अगर (of_property_पढ़ो_string(td->dev->of_node, "clock-output-names",
				    &td->output_घड़ी_name)) अणु
		dev_err(td->dev, "missing clock-output-names property\n");
		ok = false;
	पूर्ण

	वापस ok ? 0 : -EINVAL;
पूर्ण

/*
 * API exported to per-SoC platक्रमm drivers
 */

/**
 * tegra_dfll_रेजिस्टर - probe a Tegra DFLL device
 * @pdev: DFLL platक्रमm_device *
 * @soc: Per-SoC पूर्णांकegration and अक्षरacterization data क्रम this DFLL instance
 *
 * Probe and initialize a DFLL device instance. Intended to be called
 * by a SoC-specअगरic shim driver that passes in per-SoC पूर्णांकegration
 * and configuration data via @soc. Returns 0 on success or -err on failure.
 */
पूर्णांक tegra_dfll_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
			काष्ठा tegra_dfll_soc_data *soc)
अणु
	काष्ठा resource *mem;
	काष्ठा tegra_dfll *td;
	पूर्णांक ret;

	अगर (!soc) अणु
		dev_err(&pdev->dev, "no tegra_dfll_soc_data provided\n");
		वापस -EINVAL;
	पूर्ण

	td = devm_kzalloc(&pdev->dev, माप(*td), GFP_KERNEL);
	अगर (!td)
		वापस -ENOMEM;
	td->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, td);

	td->soc = soc;

	td->dvco_rst = devm_reset_control_get(td->dev, "dvco");
	अगर (IS_ERR(td->dvco_rst)) अणु
		dev_err(td->dev, "couldn't get dvco reset\n");
		वापस PTR_ERR(td->dvco_rst);
	पूर्ण

	ret = dfll_fetch_common_params(td);
	अगर (ret) अणु
		dev_err(td->dev, "couldn't parse device tree parameters\n");
		वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_bool(td->dev->of_node, "nvidia,pwm-to-pmic")) अणु
		td->pmu_अगर = TEGRA_DFLL_PMU_PWM;
		ret = dfll_fetch_pwm_params(td);
	पूर्ण अन्यथा  अणु
		td->vdd_reg = devm_regulator_get(td->dev, "vdd-cpu");
		अगर (IS_ERR(td->vdd_reg)) अणु
			dev_err(td->dev, "couldn't get vdd_cpu regulator\n");
			वापस PTR_ERR(td->vdd_reg);
		पूर्ण
		td->pmu_अगर = TEGRA_DFLL_PMU_I2C;
		ret = dfll_fetch_i2c_params(td);
	पूर्ण
	अगर (ret)
		वापस ret;

	ret = dfll_build_lut(td);
	अगर (ret) अणु
		dev_err(td->dev, "couldn't build LUT\n");
		वापस ret;
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mem) अणु
		dev_err(td->dev, "no control register resource\n");
		वापस -ENODEV;
	पूर्ण

	td->base = devm_ioremap(td->dev, mem->start, resource_size(mem));
	अगर (!td->base) अणु
		dev_err(td->dev, "couldn't ioremap DFLL control registers\n");
		वापस -ENODEV;
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!mem) अणु
		dev_err(td->dev, "no i2c_base resource\n");
		वापस -ENODEV;
	पूर्ण

	td->i2c_base = devm_ioremap(td->dev, mem->start, resource_size(mem));
	अगर (!td->i2c_base) अणु
		dev_err(td->dev, "couldn't ioremap i2c_base resource\n");
		वापस -ENODEV;
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	अगर (!mem) अणु
		dev_err(td->dev, "no i2c_controller_base resource\n");
		वापस -ENODEV;
	पूर्ण

	td->i2c_controller_base = devm_ioremap(td->dev, mem->start,
					       resource_size(mem));
	अगर (!td->i2c_controller_base) अणु
		dev_err(td->dev,
			"couldn't ioremap i2c_controller_base resource\n");
		वापस -ENODEV;
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 3);
	अगर (!mem) अणु
		dev_err(td->dev, "no lut_base resource\n");
		वापस -ENODEV;
	पूर्ण

	td->lut_base = devm_ioremap(td->dev, mem->start, resource_size(mem));
	अगर (!td->lut_base) अणु
		dev_err(td->dev,
			"couldn't ioremap lut_base resource\n");
		वापस -ENODEV;
	पूर्ण

	ret = dfll_init_clks(td);
	अगर (ret) अणु
		dev_err(&pdev->dev, "DFLL clock init error\n");
		वापस ret;
	पूर्ण

	/* Enable the घड़ीs and set the device up */
	ret = dfll_init(td);
	अगर (ret)
		वापस ret;

	ret = dfll_रेजिस्टर_clk(td);
	अगर (ret) अणु
		dev_err(&pdev->dev, "DFLL clk registration failed\n");
		वापस ret;
	पूर्ण

	dfll_debug_init(td);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tegra_dfll_रेजिस्टर);

/**
 * tegra_dfll_unरेजिस्टर - release all of the DFLL driver resources क्रम a device
 * @pdev: DFLL platक्रमm_device *
 *
 * Unbind this driver from the DFLL hardware device represented by
 * @pdev. The DFLL must be disabled क्रम this to succeed. Returns a
 * soc poपूर्णांकer upon success or -EBUSY अगर the DFLL is still active.
 */
काष्ठा tegra_dfll_soc_data *tegra_dfll_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_dfll *td = platक्रमm_get_drvdata(pdev);

	/* Try to prevent removal जबतक the DFLL is active */
	अगर (td->mode != DFLL_DISABLED) अणु
		dev_err(&pdev->dev,
			"must disable DFLL before removing driver\n");
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	debugfs_हटाओ_recursive(td->debugfs_dir);

	dfll_unरेजिस्टर_clk(td);
	pm_runसमय_disable(&pdev->dev);

	clk_unprepare(td->ref_clk);
	clk_unprepare(td->soc_clk);
	clk_unprepare(td->i2c_clk);

	reset_control_निश्चित(td->dvco_rst);

	वापस td->soc;
पूर्ण
EXPORT_SYMBOL(tegra_dfll_unरेजिस्टर);
