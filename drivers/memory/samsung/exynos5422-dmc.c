<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 * Author: Lukasz Luba <l.luba@partner.samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/devfreq-event.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश "../jedec_ddr.h"
#समावेश "../of_memory.h"

अटल पूर्णांक irqmode;
module_param(irqmode, पूर्णांक, 0644);
MODULE_PARM_DESC(irqmode, "Enable IRQ mode (0=off [default], 1=on)");

#घोषणा EXYNOS5_DREXI_TIMINGAREF		(0x0030)
#घोषणा EXYNOS5_DREXI_TIMINGROW0		(0x0034)
#घोषणा EXYNOS5_DREXI_TIMINGDATA0		(0x0038)
#घोषणा EXYNOS5_DREXI_TIMINGPOWER0		(0x003C)
#घोषणा EXYNOS5_DREXI_TIMINGROW1		(0x00E4)
#घोषणा EXYNOS5_DREXI_TIMINGDATA1		(0x00E8)
#घोषणा EXYNOS5_DREXI_TIMINGPOWER1		(0x00EC)
#घोषणा CDREX_PAUSE				(0x2091c)
#घोषणा CDREX_LPDDR3PHY_CON3			(0x20a20)
#घोषणा CDREX_LPDDR3PHY_CLKM_SRC		(0x20700)
#घोषणा EXYNOS5_TIMING_SET_SWI			BIT(28)
#घोषणा USE_MX_MSPLL_TIMINGS			(1)
#घोषणा USE_BPLL_TIMINGS			(0)
#घोषणा EXYNOS5_AREF_NORMAL			(0x2e)

#घोषणा DREX_PPCCLKCON		(0x0130)
#घोषणा DREX_PEREV2CONFIG	(0x013c)
#घोषणा DREX_PMNC_PPC		(0xE000)
#घोषणा DREX_CNTENS_PPC		(0xE010)
#घोषणा DREX_CNTENC_PPC		(0xE020)
#घोषणा DREX_INTENS_PPC		(0xE030)
#घोषणा DREX_INTENC_PPC		(0xE040)
#घोषणा DREX_FLAG_PPC		(0xE050)
#घोषणा DREX_PMCNT2_PPC		(0xE130)

/*
 * A value क्रम रेजिस्टर DREX_PMNC_PPC which should be written to reset
 * the cycle counter CCNT (a reference wall घड़ी). It sets zero to the
 * CCNT counter.
 */
#घोषणा CC_RESET		BIT(2)

/*
 * A value क्रम रेजिस्टर DREX_PMNC_PPC which करोes the reset of all perक्रमmance
 * counters to zero.
 */
#घोषणा PPC_COUNTER_RESET	BIT(1)

/*
 * Enables all configured counters (including cycle counter). The value should
 * be written to the रेजिस्टर DREX_PMNC_PPC.
 */
#घोषणा PPC_ENABLE		BIT(0)

/* A value क्रम रेजिस्टर DREX_PPCCLKCON which enables perक्रमmance events घड़ी.
 * Must be written beक्रमe first access to the perक्रमmance counters रेजिस्टर
 * set, otherwise it could crash.
 */
#घोषणा PEREV_CLK_EN		BIT(0)

/*
 * Values which are used to enable counters, पूर्णांकerrupts or configure flags of
 * the perक्रमmance counters. They configure counter 2 and cycle counter.
 */
#घोषणा PERF_CNT2		BIT(2)
#घोषणा PERF_CCNT		BIT(31)

/*
 * Perक्रमmance event types which are used क्रम setting the preferred event
 * to track in the counters.
 * There is a set of dअगरferent types, the values are from range 0 to 0x6f.
 * These settings should be written to the configuration रेजिस्टर which manages
 * the type of the event (रेजिस्टर DREX_PEREV2CONFIG).
 */
#घोषणा READ_TRANSFER_CH0	(0x6d)
#घोषणा READ_TRANSFER_CH1	(0x6f)

#घोषणा PERF_COUNTER_START_VALUE 0xff000000
#घोषणा PERF_EVENT_UP_DOWN_THRESHOLD 900000000ULL

/**
 * काष्ठा dmc_opp_table - Operating level desciption
 * @freq_hz:		target frequency in Hz
 * @volt_uv:		target voltage in uV
 *
 * Covers frequency and voltage settings of the DMC operating mode.
 */
काष्ठा dmc_opp_table अणु
	u32 freq_hz;
	u32 volt_uv;
पूर्ण;

/**
 * काष्ठा exynos5_dmc - मुख्य काष्ठाure describing DMC device
 * @dev:		DMC device
 * @df:			devfreq device काष्ठाure वापसed by devfreq framework
 * @gov_data:		configuration of devfreq governor
 * @base_drexi0:	DREX0 रेजिस्टरs mapping
 * @base_drexi1:	DREX1 रेजिस्टरs mapping
 * @clk_regmap:		regmap क्रम घड़ी controller रेजिस्टरs
 * @lock:		protects curr_rate and frequency/voltage setting section
 * @curr_rate:		current frequency
 * @curr_volt:		current voltage
 * @opp:		OPP table
 * @opp_count:		number of 'opp' elements
 * @timings_arr_size:	number of 'timings' elements
 * @timing_row:		values क्रम timing row रेजिस्टर, क्रम each OPP
 * @timing_data:	values क्रम timing data रेजिस्टर, क्रम each OPP
 * @timing_घातer:	balues क्रम timing घातer रेजिस्टर, क्रम each OPP
 * @timings:		DDR memory timings, from device tree
 * @min_tck:		DDR memory minimum timing values, from device tree
 * @bypass_timing_row:	value क्रम timing row रेजिस्टर क्रम bypass timings
 * @bypass_timing_data:	value क्रम timing data रेजिस्टर क्रम bypass timings
 * @bypass_timing_घातer:	value क्रम timing घातer रेजिस्टर क्रम bypass
 *				timings
 * @vdd_mअगर:		Memory पूर्णांकerface regulator
 * @fout_spll:		घड़ी: SPLL
 * @fout_bpll:		घड़ी: BPLL
 * @mout_spll:		घड़ी: mux SPLL
 * @mout_bpll:		घड़ी: mux BPLL
 * @mout_mclk_cdrex:	घड़ी: mux mclk_cdrex
 * @mout_mx_mspll_ccore:	घड़ी: mux mx_mspll_ccore
 * @counter:		devfreq events
 * @num_counters:	number of 'counter' elements
 * @last_overflow_ts:	समय (in ns) of last overflow of each DREX
 * @load:		utilization in percents
 * @total:		total समय between devfreq events
 * @in_irq_mode:	whether running in पूर्णांकerrupt mode (true)
 *			or polling (false)
 *
 * The मुख्य काष्ठाure क्रम the Dynamic Memory Controller which covers घड़ीs,
 * memory regions, HW inक्रमmation, parameters and current operating mode.
 */
काष्ठा exynos5_dmc अणु
	काष्ठा device *dev;
	काष्ठा devfreq *df;
	काष्ठा devfreq_simple_ondemand_data gov_data;
	व्योम __iomem *base_drexi0;
	व्योम __iomem *base_drexi1;
	काष्ठा regmap *clk_regmap;
	/* Protects curr_rate and frequency/voltage setting section */
	काष्ठा mutex lock;
	अचिन्हित दीर्घ curr_rate;
	अचिन्हित दीर्घ curr_volt;
	काष्ठा dmc_opp_table *opp;
	पूर्णांक opp_count;
	u32 timings_arr_size;
	u32 *timing_row;
	u32 *timing_data;
	u32 *timing_घातer;
	स्थिर काष्ठा lpddr3_timings *timings;
	स्थिर काष्ठा lpddr3_min_tck *min_tck;
	u32 bypass_timing_row;
	u32 bypass_timing_data;
	u32 bypass_timing_घातer;
	काष्ठा regulator *vdd_mअगर;
	काष्ठा clk *fout_spll;
	काष्ठा clk *fout_bpll;
	काष्ठा clk *mout_spll;
	काष्ठा clk *mout_bpll;
	काष्ठा clk *mout_mclk_cdrex;
	काष्ठा clk *mout_mx_mspll_ccore;
	काष्ठा devfreq_event_dev **counter;
	पूर्णांक num_counters;
	u64 last_overflow_ts[2];
	अचिन्हित दीर्घ load;
	अचिन्हित दीर्घ total;
	bool in_irq_mode;
पूर्ण;

#घोषणा TIMING_FIELD(t_name, t_bit_beg, t_bit_end) \
	अणु .name = t_name, .bit_beg = t_bit_beg, .bit_end = t_bit_end पूर्ण

#घोषणा TIMING_VAL2REG(timing, t_val)			\
(अणु							\
		u32 __val;				\
		__val = (t_val) << (timing)->bit_beg;	\
		__val;					\
पूर्ण)

काष्ठा timing_reg अणु
	अक्षर *name;
	पूर्णांक bit_beg;
	पूर्णांक bit_end;
	अचिन्हित पूर्णांक val;
पूर्ण;

अटल स्थिर काष्ठा timing_reg timing_row_reg_fields[] = अणु
	TIMING_FIELD("tRFC", 24, 31),
	TIMING_FIELD("tRRD", 20, 23),
	TIMING_FIELD("tRP", 16, 19),
	TIMING_FIELD("tRCD", 12, 15),
	TIMING_FIELD("tRC", 6, 11),
	TIMING_FIELD("tRAS", 0, 5),
पूर्ण;

अटल स्थिर काष्ठा timing_reg timing_data_reg_fields[] = अणु
	TIMING_FIELD("tWTR", 28, 31),
	TIMING_FIELD("tWR", 24, 27),
	TIMING_FIELD("tRTP", 20, 23),
	TIMING_FIELD("tW2W-C2C", 14, 14),
	TIMING_FIELD("tR2R-C2C", 12, 12),
	TIMING_FIELD("WL", 8, 11),
	TIMING_FIELD("tDQSCK", 4, 7),
	TIMING_FIELD("RL", 0, 3),
पूर्ण;

अटल स्थिर काष्ठा timing_reg timing_घातer_reg_fields[] = अणु
	TIMING_FIELD("tFAW", 26, 31),
	TIMING_FIELD("tXSR", 16, 25),
	TIMING_FIELD("tXP", 8, 15),
	TIMING_FIELD("tCKE", 4, 7),
	TIMING_FIELD("tMRD", 0, 3),
पूर्ण;

#घोषणा TIMING_COUNT (ARRAY_SIZE(timing_row_reg_fields) + \
		      ARRAY_SIZE(timing_data_reg_fields) + \
		      ARRAY_SIZE(timing_घातer_reg_fields))

अटल पूर्णांक exynos5_counters_set_event(काष्ठा exynos5_dmc *dmc)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < dmc->num_counters; i++) अणु
		अगर (!dmc->counter[i])
			जारी;
		ret = devfreq_event_set_event(dmc->counter[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक exynos5_counters_enable_edev(काष्ठा exynos5_dmc *dmc)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < dmc->num_counters; i++) अणु
		अगर (!dmc->counter[i])
			जारी;
		ret = devfreq_event_enable_edev(dmc->counter[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक exynos5_counters_disable_edev(काष्ठा exynos5_dmc *dmc)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < dmc->num_counters; i++) अणु
		अगर (!dmc->counter[i])
			जारी;
		ret = devfreq_event_disable_edev(dmc->counter[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * find_target_freq_idx() - Finds requested frequency in local DMC configuration
 * @dmc:	device क्रम which the inक्रमmation is checked
 * @target_rate:	requested frequency in KHz
 *
 * Seeks in the local DMC driver काष्ठाure क्रम the requested frequency value
 * and वापसs index or error value.
 */
अटल पूर्णांक find_target_freq_idx(काष्ठा exynos5_dmc *dmc,
				अचिन्हित दीर्घ target_rate)
अणु
	पूर्णांक i;

	क्रम (i = dmc->opp_count - 1; i >= 0; i--)
		अगर (dmc->opp[i].freq_hz <= target_rate)
			वापस i;

	वापस -EINVAL;
पूर्ण

/**
 * exynos5_चयन_timing_regs() - Changes bank रेजिस्टर set क्रम DRAM timings
 * @dmc:	device क्रम which the new settings is going to be applied
 * @set:	boolean variable passing set value
 *
 * Changes the रेजिस्टर set, which holds timing parameters.
 * There is two रेजिस्टर sets: 0 and 1. The रेजिस्टर set 0
 * is used in normal operation when the घड़ी is provided from मुख्य PLL.
 * The bank रेजिस्टर set 1 is used when the मुख्य PLL frequency is going to be
 * changed and the घड़ी is taken from alternative, stable source.
 * This function चयनes between these banks according to the
 * currently used घड़ी source.
 */
अटल पूर्णांक exynos5_चयन_timing_regs(काष्ठा exynos5_dmc *dmc, bool set)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(dmc->clk_regmap, CDREX_LPDDR3PHY_CON3, &reg);
	अगर (ret)
		वापस ret;

	अगर (set)
		reg |= EXYNOS5_TIMING_SET_SWI;
	अन्यथा
		reg &= ~EXYNOS5_TIMING_SET_SWI;

	regmap_ग_लिखो(dmc->clk_regmap, CDREX_LPDDR3PHY_CON3, reg);

	वापस 0;
पूर्ण

/**
 * exynos5_init_freq_table() - Initialized PM OPP framework
 * @dmc:	DMC device क्रम which the frequencies are used क्रम OPP init
 * @profile:	devfreq device's profile
 *
 * Populate the devfreq device's OPP table based on current frequency, voltage.
 */
अटल पूर्णांक exynos5_init_freq_table(काष्ठा exynos5_dmc *dmc,
				   काष्ठा devfreq_dev_profile *profile)
अणु
	पूर्णांक i, ret;
	पूर्णांक idx;
	अचिन्हित दीर्घ freq;

	ret = devm_pm_opp_of_add_table(dmc->dev);
	अगर (ret < 0) अणु
		dev_err(dmc->dev, "Failed to get OPP table\n");
		वापस ret;
	पूर्ण

	dmc->opp_count = dev_pm_opp_get_opp_count(dmc->dev);

	dmc->opp = devm_kदो_स्मृति_array(dmc->dev, dmc->opp_count,
				      माप(काष्ठा dmc_opp_table), GFP_KERNEL);
	अगर (!dmc->opp)
		वापस -ENOMEM;

	idx = dmc->opp_count - 1;
	क्रम (i = 0, freq = अच_दीर्घ_उच्च; i < dmc->opp_count; i++, freq--) अणु
		काष्ठा dev_pm_opp *opp;

		opp = dev_pm_opp_find_freq_न्यूनमान(dmc->dev, &freq);
		अगर (IS_ERR(opp))
			वापस PTR_ERR(opp);

		dmc->opp[idx - i].freq_hz = freq;
		dmc->opp[idx - i].volt_uv = dev_pm_opp_get_voltage(opp);

		dev_pm_opp_put(opp);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * exynos5_set_bypass_dram_timings() - Low-level changes of the DRAM timings
 * @dmc:	device क्रम which the new settings is going to be applied
 *
 * Low-level function क्रम changing timings क्रम DRAM memory घड़ीing from
 * 'bypass' घड़ी source (fixed frequency @400MHz).
 * It uses timing bank रेजिस्टरs set 1.
 */
अटल व्योम exynos5_set_bypass_dram_timings(काष्ठा exynos5_dmc *dmc)
अणु
	ग_लिखोl(EXYNOS5_AREF_NORMAL,
	       dmc->base_drexi0 + EXYNOS5_DREXI_TIMINGAREF);

	ग_लिखोl(dmc->bypass_timing_row,
	       dmc->base_drexi0 + EXYNOS5_DREXI_TIMINGROW1);
	ग_लिखोl(dmc->bypass_timing_row,
	       dmc->base_drexi1 + EXYNOS5_DREXI_TIMINGROW1);
	ग_लिखोl(dmc->bypass_timing_data,
	       dmc->base_drexi0 + EXYNOS5_DREXI_TIMINGDATA1);
	ग_लिखोl(dmc->bypass_timing_data,
	       dmc->base_drexi1 + EXYNOS5_DREXI_TIMINGDATA1);
	ग_लिखोl(dmc->bypass_timing_घातer,
	       dmc->base_drexi0 + EXYNOS5_DREXI_TIMINGPOWER1);
	ग_लिखोl(dmc->bypass_timing_घातer,
	       dmc->base_drexi1 + EXYNOS5_DREXI_TIMINGPOWER1);
पूर्ण

/**
 * exynos5_dram_change_timings() - Low-level changes of the DRAM final timings
 * @dmc:	device क्रम which the new settings is going to be applied
 * @target_rate:	target frequency of the DMC
 *
 * Low-level function क्रम changing timings क्रम DRAM memory operating from मुख्य
 * घड़ी source (BPLL), which can have dअगरferent frequencies. Thus, each
 * frequency must have corresponding timings रेजिस्टर values in order to keep
 * the needed delays.
 * It uses timing bank रेजिस्टरs set 0.
 */
अटल पूर्णांक exynos5_dram_change_timings(काष्ठा exynos5_dmc *dmc,
				       अचिन्हित दीर्घ target_rate)
अणु
	पूर्णांक idx;

	क्रम (idx = dmc->opp_count - 1; idx >= 0; idx--)
		अगर (dmc->opp[idx].freq_hz <= target_rate)
			अवरोध;

	अगर (idx < 0)
		वापस -EINVAL;

	ग_लिखोl(EXYNOS5_AREF_NORMAL,
	       dmc->base_drexi0 + EXYNOS5_DREXI_TIMINGAREF);

	ग_लिखोl(dmc->timing_row[idx],
	       dmc->base_drexi0 + EXYNOS5_DREXI_TIMINGROW0);
	ग_लिखोl(dmc->timing_row[idx],
	       dmc->base_drexi1 + EXYNOS5_DREXI_TIMINGROW0);
	ग_लिखोl(dmc->timing_data[idx],
	       dmc->base_drexi0 + EXYNOS5_DREXI_TIMINGDATA0);
	ग_लिखोl(dmc->timing_data[idx],
	       dmc->base_drexi1 + EXYNOS5_DREXI_TIMINGDATA0);
	ग_लिखोl(dmc->timing_घातer[idx],
	       dmc->base_drexi0 + EXYNOS5_DREXI_TIMINGPOWER0);
	ग_लिखोl(dmc->timing_घातer[idx],
	       dmc->base_drexi1 + EXYNOS5_DREXI_TIMINGPOWER0);

	वापस 0;
पूर्ण

/**
 * exynos5_dmc_align_target_voltage() - Sets the final voltage क्रम the DMC
 * @dmc:	device क्रम which it is going to be set
 * @target_volt:	new voltage which is chosen to be final
 *
 * Function tries to align voltage to the safe level क्रम 'normal' mode.
 * It checks the need of higher voltage and changes the value. The target
 * voltage might be lower that currently set and still the प्रणाली will be
 * stable.
 */
अटल पूर्णांक exynos5_dmc_align_target_voltage(काष्ठा exynos5_dmc *dmc,
					    अचिन्हित दीर्घ target_volt)
अणु
	पूर्णांक ret = 0;

	अगर (dmc->curr_volt <= target_volt)
		वापस 0;

	ret = regulator_set_voltage(dmc->vdd_mअगर, target_volt,
				    target_volt);
	अगर (!ret)
		dmc->curr_volt = target_volt;

	वापस ret;
पूर्ण

/**
 * exynos5_dmc_align_bypass_voltage() - Sets the voltage क्रम the DMC
 * @dmc:	device क्रम which it is going to be set
 * @target_volt:	new voltage which is chosen to be final
 *
 * Function tries to align voltage to the safe level क्रम the 'bypass' mode.
 * It checks the need of higher voltage and changes the value.
 * The target voltage must not be less than currently needed, because
 * क्रम current frequency the device might become unstable.
 */
अटल पूर्णांक exynos5_dmc_align_bypass_voltage(काष्ठा exynos5_dmc *dmc,
					    अचिन्हित दीर्घ target_volt)
अणु
	पूर्णांक ret = 0;

	अगर (dmc->curr_volt >= target_volt)
		वापस 0;

	ret = regulator_set_voltage(dmc->vdd_mअगर, target_volt,
				    target_volt);
	अगर (!ret)
		dmc->curr_volt = target_volt;

	वापस ret;
पूर्ण

/**
 * exynos5_dmc_align_bypass_dram_timings() - Chooses and sets DRAM timings
 * @dmc:	device क्रम which it is going to be set
 * @target_rate:	new frequency which is chosen to be final
 *
 * Function changes the DRAM timings क्रम the temporary 'bypass' mode.
 */
अटल पूर्णांक exynos5_dmc_align_bypass_dram_timings(काष्ठा exynos5_dmc *dmc,
						 अचिन्हित दीर्घ target_rate)
अणु
	पूर्णांक idx = find_target_freq_idx(dmc, target_rate);

	अगर (idx < 0)
		वापस -EINVAL;

	exynos5_set_bypass_dram_timings(dmc);

	वापस 0;
पूर्ण

/**
 * exynos5_dmc_चयन_to_bypass_configuration() - Switching to temporary घड़ी
 * @dmc:	DMC device क्रम which the चयनing is going to happen
 * @target_rate:	new frequency which is going to be set as a final
 * @target_volt:	new voltage which is going to be set as a final
 *
 * Function configures DMC and घड़ीs क्रम operating in temporary 'bypass' mode.
 * This mode is used only temporary but अगर required, changes voltage and timings
 * क्रम DRAM chips. It चयनes the मुख्य घड़ी to stable घड़ी source क्रम the
 * period of the मुख्य PLL reconfiguration.
 */
अटल पूर्णांक
exynos5_dmc_चयन_to_bypass_configuration(काष्ठा exynos5_dmc *dmc,
					   अचिन्हित दीर्घ target_rate,
					   अचिन्हित दीर्घ target_volt)
अणु
	पूर्णांक ret;

	/*
	 * Having higher voltage क्रम a particular frequency करोes not harm
	 * the chip. Use it क्रम the temporary frequency change when one
	 * voltage manipulation might be aव्योमed.
	 */
	ret = exynos5_dmc_align_bypass_voltage(dmc, target_volt);
	अगर (ret)
		वापस ret;

	/*
	 * Longer delays क्रम DRAM करोes not cause crash, the opposite करोes.
	 */
	ret = exynos5_dmc_align_bypass_dram_timings(dmc, target_rate);
	अगर (ret)
		वापस ret;

	/*
	 * Delays are दीर्घ enough, so use them क्रम the new coming घड़ी.
	 */
	ret = exynos5_चयन_timing_regs(dmc, USE_MX_MSPLL_TIMINGS);

	वापस ret;
पूर्ण

/**
 * exynos5_dmc_change_freq_and_volt() - Changes voltage and frequency of the DMC
 * using safe procedure
 * @dmc:	device क्रम which the frequency is going to be changed
 * @target_rate:	requested new frequency
 * @target_volt:	requested voltage which corresponds to the new frequency
 *
 * The DMC frequency change procedure requires a few steps.
 * The मुख्य requirement is to change the घड़ी source in the clk mux
 * क्रम the समय of मुख्य घड़ी PLL locking. The assumption is that the
 * alternative घड़ी source set as parent is stable.
 * The second parent's clock frequency is fixed to 400MHz, it is named 'bypass'
 * घड़ी. This requires alignment in DRAM timing parameters क्रम the new
 * T-period. There is two bank sets क्रम keeping DRAM
 * timings: set 0 and set 1. The set 0 is used when मुख्य घड़ी source is
 * chosen. The 2nd set of regs is used क्रम 'bypass' घड़ी. Switching between
 * the two bank sets is part of the process.
 * The voltage must also be aligned to the minimum required level. There is
 * this पूर्णांकermediate step with चयनing to 'bypass' parent घड़ी source.
 * अगर the old voltage is lower, it requires an increase of the voltage level.
 * The complनिकासy of the voltage manipulation is hidden in low level function.
 * In this function there is last alignment of the voltage level at the end.
 */
अटल पूर्णांक
exynos5_dmc_change_freq_and_volt(काष्ठा exynos5_dmc *dmc,
				 अचिन्हित दीर्घ target_rate,
				 अचिन्हित दीर्घ target_volt)
अणु
	पूर्णांक ret;

	ret = exynos5_dmc_चयन_to_bypass_configuration(dmc, target_rate,
							 target_volt);
	अगर (ret)
		वापस ret;

	/*
	 * Voltage is set at least to a level needed क्रम this frequency,
	 * so चयनing घड़ी source is safe now.
	 */
	clk_prepare_enable(dmc->fout_spll);
	clk_prepare_enable(dmc->mout_spll);
	clk_prepare_enable(dmc->mout_mx_mspll_ccore);

	ret = clk_set_parent(dmc->mout_mclk_cdrex, dmc->mout_mx_mspll_ccore);
	अगर (ret)
		जाओ disable_घड़ीs;

	/*
	 * We are safe to increase the timings क्रम current bypass frequency.
	 * Thanks to this the settings will be पढ़ोy क्रम the upcoming घड़ी
	 * source change.
	 */
	exynos5_dram_change_timings(dmc, target_rate);

	clk_set_rate(dmc->fout_bpll, target_rate);

	ret = exynos5_चयन_timing_regs(dmc, USE_BPLL_TIMINGS);
	अगर (ret)
		जाओ disable_घड़ीs;

	ret = clk_set_parent(dmc->mout_mclk_cdrex, dmc->mout_bpll);
	अगर (ret)
		जाओ disable_घड़ीs;

	/*
	 * Make sure अगर the voltage is not from 'bypass' settings and align to
	 * the right level क्रम घातer efficiency.
	 */
	ret = exynos5_dmc_align_target_voltage(dmc, target_volt);

disable_घड़ीs:
	clk_disable_unprepare(dmc->mout_mx_mspll_ccore);
	clk_disable_unprepare(dmc->mout_spll);
	clk_disable_unprepare(dmc->fout_spll);

	वापस ret;
पूर्ण

/**
 * exynos5_dmc_get_volt_freq() - Gets the frequency and voltage from the OPP
 * table.
 * @dmc:	device क्रम which the frequency is going to be changed
 * @freq:       requested frequency in KHz
 * @target_rate:	वापसed frequency which is the same or lower than
 *			requested
 * @target_volt:	वापसed voltage which corresponds to the वापसed
 *			frequency
 * @flags:	devfreq flags provided क्रम this frequency change request
 *
 * Function माला_लो requested frequency and checks OPP framework क्रम needed
 * frequency and voltage. It populates the values 'target_rate' and
 * 'target_volt' or वापसs error value when OPP framework fails.
 */
अटल पूर्णांक exynos5_dmc_get_volt_freq(काष्ठा exynos5_dmc *dmc,
				     अचिन्हित दीर्घ *freq,
				     अचिन्हित दीर्घ *target_rate,
				     अचिन्हित दीर्घ *target_volt, u32 flags)
अणु
	काष्ठा dev_pm_opp *opp;

	opp = devfreq_recommended_opp(dmc->dev, freq, flags);
	अगर (IS_ERR(opp))
		वापस PTR_ERR(opp);

	*target_rate = dev_pm_opp_get_freq(opp);
	*target_volt = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	वापस 0;
पूर्ण

/**
 * exynos5_dmc_target() - Function responsible क्रम changing frequency of DMC
 * @dev:	device क्रम which the frequency is going to be changed
 * @freq:	requested frequency in KHz
 * @flags:	flags provided क्रम this frequency change request
 *
 * An entry function provided to the devfreq framework which provides frequency
 * change of the DMC. The function माला_लो the possible rate from OPP table based
 * on requested frequency. It calls the next function responsible क्रम the
 * frequency and voltage change. In हाल of failure, करोes not set 'curr_rate'
 * and वापसs error value to the framework.
 */
अटल पूर्णांक exynos5_dmc_target(काष्ठा device *dev, अचिन्हित दीर्घ *freq,
			      u32 flags)
अणु
	काष्ठा exynos5_dmc *dmc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ target_rate = 0;
	अचिन्हित दीर्घ target_volt = 0;
	पूर्णांक ret;

	ret = exynos5_dmc_get_volt_freq(dmc, freq, &target_rate, &target_volt,
					flags);

	अगर (ret)
		वापस ret;

	अगर (target_rate == dmc->curr_rate)
		वापस 0;

	mutex_lock(&dmc->lock);

	ret = exynos5_dmc_change_freq_and_volt(dmc, target_rate, target_volt);

	अगर (ret) अणु
		mutex_unlock(&dmc->lock);
		वापस ret;
	पूर्ण

	dmc->curr_rate = target_rate;

	mutex_unlock(&dmc->lock);
	वापस 0;
पूर्ण

/**
 * exynos5_counters_get() - Gets the perक्रमmance counters values.
 * @dmc:	device क्रम which the counters are going to be checked
 * @load_count:	variable which is populated with counter value
 * @total_count:	variable which is used as 'wall clock' reference
 *
 * Function which provides perक्रमmance counters values. It sums up counters क्रम
 * two DMC channels. The 'total_count' is used as a reference and max value.
 * The ratio 'load_count/total_count' shows the busy percentage [0%, 100%].
 */
अटल पूर्णांक exynos5_counters_get(काष्ठा exynos5_dmc *dmc,
				अचिन्हित दीर्घ *load_count,
				अचिन्हित दीर्घ *total_count)
अणु
	अचिन्हित दीर्घ total = 0;
	काष्ठा devfreq_event_data event;
	पूर्णांक ret, i;

	*load_count = 0;

	/* Take पूर्णांकo account only पढ़ो+ग_लिखो counters, but stop all */
	क्रम (i = 0; i < dmc->num_counters; i++) अणु
		अगर (!dmc->counter[i])
			जारी;

		ret = devfreq_event_get_event(dmc->counter[i], &event);
		अगर (ret < 0)
			वापस ret;

		*load_count += event.load_count;

		अगर (total < event.total_count)
			total = event.total_count;
	पूर्ण

	*total_count = total;

	वापस 0;
पूर्ण

/**
 * exynos5_dmc_start_perf_events() - Setup and start perक्रमmance event counters
 * @dmc:	device क्रम which the counters are going to be checked
 * @beg_value:	initial value क्रम the counter
 *
 * Function which enables needed counters, पूर्णांकerrupts and sets initial values
 * then starts the counters.
 */
अटल व्योम exynos5_dmc_start_perf_events(काष्ठा exynos5_dmc *dmc,
					  u32 beg_value)
अणु
	/* Enable पूर्णांकerrupts क्रम counter 2 */
	ग_लिखोl(PERF_CNT2, dmc->base_drexi0 + DREX_INTENS_PPC);
	ग_लिखोl(PERF_CNT2, dmc->base_drexi1 + DREX_INTENS_PPC);

	/* Enable counter 2 and CCNT  */
	ग_लिखोl(PERF_CNT2 | PERF_CCNT, dmc->base_drexi0 + DREX_CNTENS_PPC);
	ग_लिखोl(PERF_CNT2 | PERF_CCNT, dmc->base_drexi1 + DREX_CNTENS_PPC);

	/* Clear overflow flag क्रम all counters */
	ग_लिखोl(PERF_CNT2 | PERF_CCNT, dmc->base_drexi0 + DREX_FLAG_PPC);
	ग_लिखोl(PERF_CNT2 | PERF_CCNT, dmc->base_drexi1 + DREX_FLAG_PPC);

	/* Reset all counters */
	ग_लिखोl(CC_RESET | PPC_COUNTER_RESET, dmc->base_drexi0 + DREX_PMNC_PPC);
	ग_लिखोl(CC_RESET | PPC_COUNTER_RESET, dmc->base_drexi1 + DREX_PMNC_PPC);

	/*
	 * Set start value क्रम the counters, the number of samples that
	 * will be gathered is calculated as: 0xffffffff - beg_value
	 */
	ग_लिखोl(beg_value, dmc->base_drexi0 + DREX_PMCNT2_PPC);
	ग_लिखोl(beg_value, dmc->base_drexi1 + DREX_PMCNT2_PPC);

	/* Start all counters */
	ग_लिखोl(PPC_ENABLE, dmc->base_drexi0 + DREX_PMNC_PPC);
	ग_लिखोl(PPC_ENABLE, dmc->base_drexi1 + DREX_PMNC_PPC);
पूर्ण

/**
 * exynos5_dmc_perf_events_calc() - Calculate utilization
 * @dmc:	device क्रम which the counters are going to be checked
 * @dअगरf_ts:	समय between last पूर्णांकerrupt and current one
 *
 * Function which calculates needed utilization क्रम the devfreq governor.
 * It prepares values क्रम 'busy_time' and 'total_time' based on elapsed समय
 * between पूर्णांकerrupts, which approximates utilization.
 */
अटल व्योम exynos5_dmc_perf_events_calc(काष्ठा exynos5_dmc *dmc, u64 dअगरf_ts)
अणु
	/*
	 * This is a simple algorithm क्रम managing traffic on DMC.
	 * When there is almost no load the counters overflow every 4s,
	 * no mater the DMC frequency.
	 * The high load might be approximated using linear function.
	 * Knowing that, simple calculation can provide 'busy_time' and
	 * 'total_time' to the devfreq governor which picks up target
	 * frequency.
	 * We want a fast ramp up and slow decay in frequency change function.
	 */
	अगर (dअगरf_ts < PERF_EVENT_UP_DOWN_THRESHOLD) अणु
		/*
		 * Set higher utilization क्रम the simple_ondemand governor.
		 * The governor should increase the frequency of the DMC.
		 */
		dmc->load = 70;
		dmc->total = 100;
	पूर्ण अन्यथा अणु
		/*
		 * Set low utilization क्रम the simple_ondemand governor.
		 * The governor should decrease the frequency of the DMC.
		 */
		dmc->load = 35;
		dmc->total = 100;
	पूर्ण

	dev_dbg(dmc->dev, "diff_ts=%llu\n", dअगरf_ts);
पूर्ण

/**
 * exynos5_dmc_perf_events_check() - Checks the status of the counters
 * @dmc:	device क्रम which the counters are going to be checked
 *
 * Function which is called from thपढ़ोed IRQ to check the counters state
 * and to call approximation क्रम the needed utilization.
 */
अटल व्योम exynos5_dmc_perf_events_check(काष्ठा exynos5_dmc *dmc)
अणु
	u32 val;
	u64 dअगरf_ts, ts;

	ts = kसमय_get_ns();

	/* Stop all counters */
	ग_लिखोl(0, dmc->base_drexi0 + DREX_PMNC_PPC);
	ग_लिखोl(0, dmc->base_drexi1 + DREX_PMNC_PPC);

	/* Check the source in पूर्णांकerrupt flag रेजिस्टरs (which channel) */
	val = पढ़ोl(dmc->base_drexi0 + DREX_FLAG_PPC);
	अगर (val) अणु
		dअगरf_ts = ts - dmc->last_overflow_ts[0];
		dmc->last_overflow_ts[0] = ts;
		dev_dbg(dmc->dev, "drex0 0xE050 val= 0x%08x\n",  val);
	पूर्ण अन्यथा अणु
		val = पढ़ोl(dmc->base_drexi1 + DREX_FLAG_PPC);
		dअगरf_ts = ts - dmc->last_overflow_ts[1];
		dmc->last_overflow_ts[1] = ts;
		dev_dbg(dmc->dev, "drex1 0xE050 val= 0x%08x\n",  val);
	पूर्ण

	exynos5_dmc_perf_events_calc(dmc, dअगरf_ts);

	exynos5_dmc_start_perf_events(dmc, PERF_COUNTER_START_VALUE);
पूर्ण

/**
 * exynos5_dmc_enable_perf_events() - Enable perक्रमmance events
 * @dmc:	device क्रम which the counters are going to be checked
 *
 * Function which is setup needed environment and enables counters.
 */
अटल व्योम exynos5_dmc_enable_perf_events(काष्ठा exynos5_dmc *dmc)
अणु
	u64 ts;

	/* Enable Perक्रमmance Event Clock */
	ग_लिखोl(PEREV_CLK_EN, dmc->base_drexi0 + DREX_PPCCLKCON);
	ग_लिखोl(PEREV_CLK_EN, dmc->base_drexi1 + DREX_PPCCLKCON);

	/* Select पढ़ो transfers as perक्रमmance event2 */
	ग_लिखोl(READ_TRANSFER_CH0, dmc->base_drexi0 + DREX_PEREV2CONFIG);
	ग_लिखोl(READ_TRANSFER_CH1, dmc->base_drexi1 + DREX_PEREV2CONFIG);

	ts = kसमय_get_ns();
	dmc->last_overflow_ts[0] = ts;
	dmc->last_overflow_ts[1] = ts;

	/* Devfreq shouldn't be faster than initialization, play safe though. */
	dmc->load = 99;
	dmc->total = 100;
पूर्ण

/**
 * exynos5_dmc_disable_perf_events() - Disable perक्रमmance events
 * @dmc:	device क्रम which the counters are going to be checked
 *
 * Function which stops, disables perक्रमmance event counters and पूर्णांकerrupts.
 */
अटल व्योम exynos5_dmc_disable_perf_events(काष्ठा exynos5_dmc *dmc)
अणु
	/* Stop all counters */
	ग_लिखोl(0, dmc->base_drexi0 + DREX_PMNC_PPC);
	ग_लिखोl(0, dmc->base_drexi1 + DREX_PMNC_PPC);

	/* Disable पूर्णांकerrupts क्रम counter 2 */
	ग_लिखोl(PERF_CNT2, dmc->base_drexi0 + DREX_INTENC_PPC);
	ग_लिखोl(PERF_CNT2, dmc->base_drexi1 + DREX_INTENC_PPC);

	/* Disable counter 2 and CCNT  */
	ग_लिखोl(PERF_CNT2 | PERF_CCNT, dmc->base_drexi0 + DREX_CNTENC_PPC);
	ग_लिखोl(PERF_CNT2 | PERF_CCNT, dmc->base_drexi1 + DREX_CNTENC_PPC);

	/* Clear overflow flag क्रम all counters */
	ग_लिखोl(PERF_CNT2 | PERF_CCNT, dmc->base_drexi0 + DREX_FLAG_PPC);
	ग_लिखोl(PERF_CNT2 | PERF_CCNT, dmc->base_drexi1 + DREX_FLAG_PPC);
पूर्ण

/**
 * exynos5_dmc_get_status() - Read current DMC perक्रमmance statistics.
 * @dev:	device क्रम which the statistics are requested
 * @stat:	काष्ठाure which has statistic fields
 *
 * Function पढ़ोs the DMC perक्रमmance counters and calculates 'busy_time'
 * and 'total_time'. To protect from overflow, the values are shअगरted right
 * by 10. After पढ़ो out the counters are setup to count again.
 */
अटल पूर्णांक exynos5_dmc_get_status(काष्ठा device *dev,
				  काष्ठा devfreq_dev_status *stat)
अणु
	काष्ठा exynos5_dmc *dmc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ load, total;
	पूर्णांक ret;

	अगर (dmc->in_irq_mode) अणु
		mutex_lock(&dmc->lock);
		stat->current_frequency = dmc->curr_rate;
		mutex_unlock(&dmc->lock);

		stat->busy_समय = dmc->load;
		stat->total_समय = dmc->total;
	पूर्ण अन्यथा अणु
		ret = exynos5_counters_get(dmc, &load, &total);
		अगर (ret < 0)
			वापस -EINVAL;

		/* To protect from overflow, भागide by 1024 */
		stat->busy_समय = load >> 10;
		stat->total_समय = total >> 10;

		ret = exynos5_counters_set_event(dmc);
		अगर (ret < 0) अणु
			dev_err(dev, "could not set event counter\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * exynos5_dmc_get_cur_freq() - Function वापसs current DMC frequency
 * @dev:	device क्रम which the framework checks operating frequency
 * @freq:	वापसed frequency value
 *
 * It वापसs the currently used frequency of the DMC. The real operating
 * frequency might be lower when the घड़ी source value could not be भागided
 * to the requested value.
 */
अटल पूर्णांक exynos5_dmc_get_cur_freq(काष्ठा device *dev, अचिन्हित दीर्घ *freq)
अणु
	काष्ठा exynos5_dmc *dmc = dev_get_drvdata(dev);

	mutex_lock(&dmc->lock);
	*freq = dmc->curr_rate;
	mutex_unlock(&dmc->lock);

	वापस 0;
पूर्ण

/*
 * exynos5_dmc_df_profile - Devfreq governor's profile काष्ठाure
 *
 * It provides to the devfreq framework needed functions and polling period.
 */
अटल काष्ठा devfreq_dev_profile exynos5_dmc_df_profile = अणु
	.समयr = DEVFREQ_TIMER_DELAYED,
	.target = exynos5_dmc_target,
	.get_dev_status = exynos5_dmc_get_status,
	.get_cur_freq = exynos5_dmc_get_cur_freq,
पूर्ण;

/**
 * exynos5_dmc_align_init_freq() - Align initial frequency value
 * @dmc:	device क्रम which the frequency is going to be set
 * @bootloader_init_freq:	initial frequency set by the bootloader in KHz
 *
 * The initial bootloader frequency, which is present during boot, might be
 * dअगरferent that supported frequency values in the driver. It is possible
 * due to dअगरferent PLL settings or used PLL as a source.
 * This function provides the 'initial_freq' क्रम the devfreq framework
 * statistics engine which supports only रेजिस्टरed values. Thus, some alignment
 * must be made.
 */
अटल अचिन्हित दीर्घ
exynos5_dmc_align_init_freq(काष्ठा exynos5_dmc *dmc,
			    अचिन्हित दीर्घ bootloader_init_freq)
अणु
	अचिन्हित दीर्घ aligned_freq;
	पूर्णांक idx;

	idx = find_target_freq_idx(dmc, bootloader_init_freq);
	अगर (idx >= 0)
		aligned_freq = dmc->opp[idx].freq_hz;
	अन्यथा
		aligned_freq = dmc->opp[dmc->opp_count - 1].freq_hz;

	वापस aligned_freq;
पूर्ण

/**
 * create_timings_aligned() - Create रेजिस्टर values and align with standard
 * @dmc:	device क्रम which the frequency is going to be set
 * @reg_timing_row:	array to fill with values क्रम timing row रेजिस्टर
 * @reg_timing_data:	array to fill with values क्रम timing data रेजिस्टर
 * @reg_timing_घातer:	array to fill with values क्रम timing घातer रेजिस्टर
 * @clk_period_ps:	the period of the घड़ी, known as tCK
 *
 * The function calculates timings and creates a रेजिस्टर value पढ़ोy क्रम
 * a frequency transition. The रेजिस्टर contains a few timings. They are
 * shअगरted by a known offset. The timing value is calculated based on memory
 * specyfication: minimal समय required and minimal cycles required.
 */
अटल पूर्णांक create_timings_aligned(काष्ठा exynos5_dmc *dmc, u32 *reg_timing_row,
				  u32 *reg_timing_data, u32 *reg_timing_घातer,
				  u32 clk_period_ps)
अणु
	u32 val;
	स्थिर काष्ठा timing_reg *reg;

	अगर (clk_period_ps == 0)
		वापस -EINVAL;

	*reg_timing_row = 0;
	*reg_timing_data = 0;
	*reg_timing_घातer = 0;

	val = dmc->timings->tRFC / clk_period_ps;
	val += dmc->timings->tRFC % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tRFC);
	reg = &timing_row_reg_fields[0];
	*reg_timing_row |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tRRD / clk_period_ps;
	val += dmc->timings->tRRD % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tRRD);
	reg = &timing_row_reg_fields[1];
	*reg_timing_row |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tRPab / clk_period_ps;
	val += dmc->timings->tRPab % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tRPab);
	reg = &timing_row_reg_fields[2];
	*reg_timing_row |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tRCD / clk_period_ps;
	val += dmc->timings->tRCD % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tRCD);
	reg = &timing_row_reg_fields[3];
	*reg_timing_row |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tRC / clk_period_ps;
	val += dmc->timings->tRC % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tRC);
	reg = &timing_row_reg_fields[4];
	*reg_timing_row |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tRAS / clk_period_ps;
	val += dmc->timings->tRAS % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tRAS);
	reg = &timing_row_reg_fields[5];
	*reg_timing_row |= TIMING_VAL2REG(reg, val);

	/* data related timings */
	val = dmc->timings->tWTR / clk_period_ps;
	val += dmc->timings->tWTR % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tWTR);
	reg = &timing_data_reg_fields[0];
	*reg_timing_data |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tWR / clk_period_ps;
	val += dmc->timings->tWR % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tWR);
	reg = &timing_data_reg_fields[1];
	*reg_timing_data |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tRTP / clk_period_ps;
	val += dmc->timings->tRTP % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tRTP);
	reg = &timing_data_reg_fields[2];
	*reg_timing_data |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tW2W_C2C / clk_period_ps;
	val += dmc->timings->tW2W_C2C % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tW2W_C2C);
	reg = &timing_data_reg_fields[3];
	*reg_timing_data |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tR2R_C2C / clk_period_ps;
	val += dmc->timings->tR2R_C2C % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tR2R_C2C);
	reg = &timing_data_reg_fields[4];
	*reg_timing_data |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tWL / clk_period_ps;
	val += dmc->timings->tWL % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tWL);
	reg = &timing_data_reg_fields[5];
	*reg_timing_data |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tDQSCK / clk_period_ps;
	val += dmc->timings->tDQSCK % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tDQSCK);
	reg = &timing_data_reg_fields[6];
	*reg_timing_data |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tRL / clk_period_ps;
	val += dmc->timings->tRL % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tRL);
	reg = &timing_data_reg_fields[7];
	*reg_timing_data |= TIMING_VAL2REG(reg, val);

	/* घातer related timings */
	val = dmc->timings->tFAW / clk_period_ps;
	val += dmc->timings->tFAW % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tFAW);
	reg = &timing_घातer_reg_fields[0];
	*reg_timing_घातer |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tXSR / clk_period_ps;
	val += dmc->timings->tXSR % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tXSR);
	reg = &timing_घातer_reg_fields[1];
	*reg_timing_घातer |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tXP / clk_period_ps;
	val += dmc->timings->tXP % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tXP);
	reg = &timing_घातer_reg_fields[2];
	*reg_timing_घातer |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tCKE / clk_period_ps;
	val += dmc->timings->tCKE % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tCKE);
	reg = &timing_घातer_reg_fields[3];
	*reg_timing_घातer |= TIMING_VAL2REG(reg, val);

	val = dmc->timings->tMRD / clk_period_ps;
	val += dmc->timings->tMRD % clk_period_ps ? 1 : 0;
	val = max(val, dmc->min_tck->tMRD);
	reg = &timing_घातer_reg_fields[4];
	*reg_timing_घातer |= TIMING_VAL2REG(reg, val);

	वापस 0;
पूर्ण

/**
 * of_get_dram_timings() - helper function क्रम parsing DT settings क्रम DRAM
 * @dmc:        device क्रम which the frequency is going to be set
 *
 * The function parses DT entries with DRAM inक्रमmation.
 */
अटल पूर्णांक of_get_dram_timings(काष्ठा exynos5_dmc *dmc)
अणु
	पूर्णांक ret = 0;
	पूर्णांक idx;
	काष्ठा device_node *np_ddr;
	u32 freq_mhz, clk_period_ps;

	np_ddr = of_parse_phandle(dmc->dev->of_node, "device-handle", 0);
	अगर (!np_ddr) अणु
		dev_warn(dmc->dev, "could not find 'device-handle' in DT\n");
		वापस -EINVAL;
	पूर्ण

	dmc->timing_row = devm_kदो_स्मृति_array(dmc->dev, TIMING_COUNT,
					     माप(u32), GFP_KERNEL);
	अगर (!dmc->timing_row)
		वापस -ENOMEM;

	dmc->timing_data = devm_kदो_स्मृति_array(dmc->dev, TIMING_COUNT,
					      माप(u32), GFP_KERNEL);
	अगर (!dmc->timing_data)
		वापस -ENOMEM;

	dmc->timing_घातer = devm_kदो_स्मृति_array(dmc->dev, TIMING_COUNT,
					       माप(u32), GFP_KERNEL);
	अगर (!dmc->timing_घातer)
		वापस -ENOMEM;

	dmc->timings = of_lpddr3_get_ddr_timings(np_ddr, dmc->dev,
						 DDR_TYPE_LPDDR3,
						 &dmc->timings_arr_size);
	अगर (!dmc->timings) अणु
		of_node_put(np_ddr);
		dev_warn(dmc->dev, "could not get timings from DT\n");
		वापस -EINVAL;
	पूर्ण

	dmc->min_tck = of_lpddr3_get_min_tck(np_ddr, dmc->dev);
	अगर (!dmc->min_tck) अणु
		of_node_put(np_ddr);
		dev_warn(dmc->dev, "could not get tck from DT\n");
		वापस -EINVAL;
	पूर्ण

	/* Sorted array of OPPs with frequency ascending */
	क्रम (idx = 0; idx < dmc->opp_count; idx++) अणु
		freq_mhz = dmc->opp[idx].freq_hz / 1000000;
		clk_period_ps = 1000000 / freq_mhz;

		ret = create_timings_aligned(dmc, &dmc->timing_row[idx],
					     &dmc->timing_data[idx],
					     &dmc->timing_घातer[idx],
					     clk_period_ps);
	पूर्ण

	of_node_put(np_ddr);

	/* Take the highest frequency's timings as 'bypass' */
	dmc->bypass_timing_row = dmc->timing_row[idx - 1];
	dmc->bypass_timing_data = dmc->timing_data[idx - 1];
	dmc->bypass_timing_घातer = dmc->timing_घातer[idx - 1];

	वापस ret;
पूर्ण

/**
 * exynos5_dmc_init_clks() - Initialize घड़ीs needed क्रम DMC operation.
 * @dmc:	DMC काष्ठाure containing needed fields
 *
 * Get the needed घड़ीs defined in DT device, enable and set the right parents.
 * Read current frequency and initialize the initial rate क्रम governor.
 */
अटल पूर्णांक exynos5_dmc_init_clks(काष्ठा exynos5_dmc *dmc)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ target_volt = 0;
	अचिन्हित दीर्घ target_rate = 0;
	अचिन्हित पूर्णांक पंचांगp;

	dmc->fout_spll = devm_clk_get(dmc->dev, "fout_spll");
	अगर (IS_ERR(dmc->fout_spll))
		वापस PTR_ERR(dmc->fout_spll);

	dmc->fout_bpll = devm_clk_get(dmc->dev, "fout_bpll");
	अगर (IS_ERR(dmc->fout_bpll))
		वापस PTR_ERR(dmc->fout_bpll);

	dmc->mout_mclk_cdrex = devm_clk_get(dmc->dev, "mout_mclk_cdrex");
	अगर (IS_ERR(dmc->mout_mclk_cdrex))
		वापस PTR_ERR(dmc->mout_mclk_cdrex);

	dmc->mout_bpll = devm_clk_get(dmc->dev, "mout_bpll");
	अगर (IS_ERR(dmc->mout_bpll))
		वापस PTR_ERR(dmc->mout_bpll);

	dmc->mout_mx_mspll_ccore = devm_clk_get(dmc->dev,
						"mout_mx_mspll_ccore");
	अगर (IS_ERR(dmc->mout_mx_mspll_ccore))
		वापस PTR_ERR(dmc->mout_mx_mspll_ccore);

	dmc->mout_spll = devm_clk_get(dmc->dev, "ff_dout_spll2");
	अगर (IS_ERR(dmc->mout_spll)) अणु
		dmc->mout_spll = devm_clk_get(dmc->dev, "mout_sclk_spll");
		अगर (IS_ERR(dmc->mout_spll))
			वापस PTR_ERR(dmc->mout_spll);
	पूर्ण

	/*
	 * Convert frequency to KHz values and set it क्रम the governor.
	 */
	dmc->curr_rate = clk_get_rate(dmc->mout_mclk_cdrex);
	dmc->curr_rate = exynos5_dmc_align_init_freq(dmc, dmc->curr_rate);
	exynos5_dmc_df_profile.initial_freq = dmc->curr_rate;

	ret = exynos5_dmc_get_volt_freq(dmc, &dmc->curr_rate, &target_rate,
					&target_volt, 0);
	अगर (ret)
		वापस ret;

	dmc->curr_volt = target_volt;

	ret = clk_set_parent(dmc->mout_mx_mspll_ccore, dmc->mout_spll);
	अगर (ret)
		वापस ret;

	clk_prepare_enable(dmc->fout_bpll);
	clk_prepare_enable(dmc->mout_bpll);

	/*
	 * Some bootloaders करो not set घड़ी routes correctly.
	 * Stop one path in घड़ीs to PHY.
	 */
	regmap_पढ़ो(dmc->clk_regmap, CDREX_LPDDR3PHY_CLKM_SRC, &पंचांगp);
	पंचांगp &= ~(BIT(1) | BIT(0));
	regmap_ग_लिखो(dmc->clk_regmap, CDREX_LPDDR3PHY_CLKM_SRC, पंचांगp);

	वापस 0;
पूर्ण

/**
 * exynos5_perक्रमmance_counters_init() - Initializes perक्रमmance DMC's counters
 * @dmc:	DMC क्रम which it करोes the setup
 *
 * Initialization of perक्रमmance counters in DMC क्रम estimating usage.
 * The counter's values are used क्रम calculation of a memory bandwidth and based
 * on that the governor changes the frequency.
 * The counters are not used when the governor is GOVERNOR_USERSPACE.
 */
अटल पूर्णांक exynos5_perक्रमmance_counters_init(काष्ठा exynos5_dmc *dmc)
अणु
	पूर्णांक counters_size;
	पूर्णांक ret, i;

	dmc->num_counters = devfreq_event_get_edev_count(dmc->dev,
							"devfreq-events");
	अगर (dmc->num_counters < 0) अणु
		dev_err(dmc->dev, "could not get devfreq-event counters\n");
		वापस dmc->num_counters;
	पूर्ण

	counters_size = माप(काष्ठा devfreq_event_dev) * dmc->num_counters;
	dmc->counter = devm_kzalloc(dmc->dev, counters_size, GFP_KERNEL);
	अगर (!dmc->counter)
		वापस -ENOMEM;

	क्रम (i = 0; i < dmc->num_counters; i++) अणु
		dmc->counter[i] =
			devfreq_event_get_edev_by_phandle(dmc->dev,
						"devfreq-events", i);
		अगर (IS_ERR_OR_शून्य(dmc->counter[i]))
			वापस -EPROBE_DEFER;
	पूर्ण

	ret = exynos5_counters_enable_edev(dmc);
	अगर (ret < 0) अणु
		dev_err(dmc->dev, "could not enable event counter\n");
		वापस ret;
	पूर्ण

	ret = exynos5_counters_set_event(dmc);
	अगर (ret < 0) अणु
		exynos5_counters_disable_edev(dmc);
		dev_err(dmc->dev, "could not set event counter\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * exynos5_dmc_set_छोड़ो_on_चयनing() - Controls a छोड़ो feature in DMC
 * @dmc:	device which is used क्रम changing this feature
 *
 * There is a need of pausing DREX DMC when भागider or MUX in घड़ी tree
 * changes its configuration. In such situation access to the memory is blocked
 * in DMC स्वतःmatically. This feature is used when घड़ी frequency change
 * request appears and touches घड़ी tree.
 */
अटल अंतरभूत पूर्णांक exynos5_dmc_set_छोड़ो_on_चयनing(काष्ठा exynos5_dmc *dmc)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(dmc->clk_regmap, CDREX_PAUSE, &val);
	अगर (ret)
		वापस ret;

	val |= 1UL;
	regmap_ग_लिखो(dmc->clk_regmap, CDREX_PAUSE, val);

	वापस 0;
पूर्ण

अटल irqवापस_t dmc_irq_thपढ़ो(पूर्णांक irq, व्योम *priv)
अणु
	पूर्णांक res;
	काष्ठा exynos5_dmc *dmc = priv;

	mutex_lock(&dmc->df->lock);
	exynos5_dmc_perf_events_check(dmc);
	res = update_devfreq(dmc->df);
	mutex_unlock(&dmc->df->lock);

	अगर (res)
		dev_warn(dmc->dev, "devfreq failed with %d\n", res);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * exynos5_dmc_probe() - Probe function क्रम the DMC driver
 * @pdev:	platक्रमm device क्रम which the driver is going to be initialized
 *
 * Initialize basic components: घड़ीs, regulators, perक्रमmance counters, etc.
 * Read out product version and based on the inक्रमmation setup
 * पूर्णांकernal काष्ठाures क्रम the controller (frequency and voltage) and क्रम DRAM
 * memory parameters: timings क्रम each operating frequency.
 * Register new devfreq device क्रम controlling DVFS of the DMC.
 */
अटल पूर्णांक exynos5_dmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा exynos5_dmc *dmc;
	पूर्णांक irq[2];

	dmc = devm_kzalloc(dev, माप(*dmc), GFP_KERNEL);
	अगर (!dmc)
		वापस -ENOMEM;

	mutex_init(&dmc->lock);

	dmc->dev = dev;
	platक्रमm_set_drvdata(pdev, dmc);

	dmc->base_drexi0 = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dmc->base_drexi0))
		वापस PTR_ERR(dmc->base_drexi0);

	dmc->base_drexi1 = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(dmc->base_drexi1))
		वापस PTR_ERR(dmc->base_drexi1);

	dmc->clk_regmap = syscon_regmap_lookup_by_phandle(np,
							  "samsung,syscon-clk");
	अगर (IS_ERR(dmc->clk_regmap))
		वापस PTR_ERR(dmc->clk_regmap);

	ret = exynos5_init_freq_table(dmc, &exynos5_dmc_df_profile);
	अगर (ret) अणु
		dev_warn(dev, "couldn't initialize frequency settings\n");
		वापस ret;
	पूर्ण

	dmc->vdd_mअगर = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(dmc->vdd_mअगर)) अणु
		ret = PTR_ERR(dmc->vdd_mअगर);
		वापस ret;
	पूर्ण

	ret = exynos5_dmc_init_clks(dmc);
	अगर (ret)
		वापस ret;

	ret = of_get_dram_timings(dmc);
	अगर (ret) अणु
		dev_warn(dev, "couldn't initialize timings settings\n");
		जाओ हटाओ_घड़ीs;
	पूर्ण

	ret = exynos5_dmc_set_छोड़ो_on_चयनing(dmc);
	अगर (ret) अणु
		dev_warn(dev, "couldn't get access to PAUSE register\n");
		जाओ हटाओ_घड़ीs;
	पूर्ण

	/* There is two modes in which the driver works: polling or IRQ */
	irq[0] = platक्रमm_get_irq_byname(pdev, "drex_0");
	irq[1] = platक्रमm_get_irq_byname(pdev, "drex_1");
	अगर (irq[0] > 0 && irq[1] > 0 && irqmode) अणु
		ret = devm_request_thपढ़ोed_irq(dev, irq[0], शून्य,
						dmc_irq_thपढ़ो, IRQF_ONESHOT,
						dev_name(dev), dmc);
		अगर (ret) अणु
			dev_err(dev, "couldn't grab IRQ\n");
			जाओ हटाओ_घड़ीs;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(dev, irq[1], शून्य,
						dmc_irq_thपढ़ो, IRQF_ONESHOT,
						dev_name(dev), dmc);
		अगर (ret) अणु
			dev_err(dev, "couldn't grab IRQ\n");
			जाओ हटाओ_घड़ीs;
		पूर्ण

		/*
		 * Setup शेष thresholds क्रम the devfreq governor.
		 * The values are chosen based on experiments.
		 */
		dmc->gov_data.upthreshold = 55;
		dmc->gov_data.करोwndअगरferential = 5;

		exynos5_dmc_enable_perf_events(dmc);

		dmc->in_irq_mode = 1;
	पूर्ण अन्यथा अणु
		ret = exynos5_perक्रमmance_counters_init(dmc);
		अगर (ret) अणु
			dev_warn(dev, "couldn't probe performance counters\n");
			जाओ हटाओ_घड़ीs;
		पूर्ण

		/*
		 * Setup शेष thresholds क्रम the devfreq governor.
		 * The values are chosen based on experiments.
		 */
		dmc->gov_data.upthreshold = 10;
		dmc->gov_data.करोwndअगरferential = 5;

		exynos5_dmc_df_profile.polling_ms = 100;
	पूर्ण

	dmc->df = devm_devfreq_add_device(dev, &exynos5_dmc_df_profile,
					  DEVFREQ_GOV_SIMPLE_ONDEMAND,
					  &dmc->gov_data);

	अगर (IS_ERR(dmc->df)) अणु
		ret = PTR_ERR(dmc->df);
		जाओ err_devfreq_add;
	पूर्ण

	अगर (dmc->in_irq_mode)
		exynos5_dmc_start_perf_events(dmc, PERF_COUNTER_START_VALUE);

	dev_info(dev, "DMC initialized, in irq mode: %d\n", dmc->in_irq_mode);

	वापस 0;

err_devfreq_add:
	अगर (dmc->in_irq_mode)
		exynos5_dmc_disable_perf_events(dmc);
	अन्यथा
		exynos5_counters_disable_edev(dmc);
हटाओ_घड़ीs:
	clk_disable_unprepare(dmc->mout_bpll);
	clk_disable_unprepare(dmc->fout_bpll);

	वापस ret;
पूर्ण

/**
 * exynos5_dmc_हटाओ() - Remove function क्रम the platक्रमm device
 * @pdev:	platक्रमm device which is going to be हटाओd
 *
 * The function relies on 'devm' framework function which स्वतःmatically
 * clean the device's resources. It just calls explicitly disable function क्रम
 * the perक्रमmance counters.
 */
अटल पूर्णांक exynos5_dmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos5_dmc *dmc = dev_get_drvdata(&pdev->dev);

	अगर (dmc->in_irq_mode)
		exynos5_dmc_disable_perf_events(dmc);
	अन्यथा
		exynos5_counters_disable_edev(dmc);

	clk_disable_unprepare(dmc->mout_bpll);
	clk_disable_unprepare(dmc->fout_bpll);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id exynos5_dmc_of_match[] = अणु
	अणु .compatible = "samsung,exynos5422-dmc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos5_dmc_of_match);

अटल काष्ठा platक्रमm_driver exynos5_dmc_platdrv = अणु
	.probe	= exynos5_dmc_probe,
	.हटाओ = exynos5_dmc_हटाओ,
	.driver = अणु
		.name	= "exynos5-dmc",
		.of_match_table = exynos5_dmc_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(exynos5_dmc_platdrv);
MODULE_DESCRIPTION("Driver for Exynos5422 Dynamic Memory Controller dynamic frequency and voltage change");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Lukasz Luba");
