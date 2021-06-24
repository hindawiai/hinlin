<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A devfreq driver क्रम NVIDIA Tegra SoCs
 *
 * Copyright (c) 2014 NVIDIA CORPORATION. All rights reserved.
 * Copyright (C) 2014 Google, Inc
 */

#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/reset.h>
#समावेश <linux/workqueue.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "governor.h"

#घोषणा ACTMON_GLB_STATUS					0x0
#घोषणा ACTMON_GLB_PERIOD_CTRL					0x4

#घोषणा ACTMON_DEV_CTRL						0x0
#घोषणा ACTMON_DEV_CTRL_K_VAL_SHIFT				10
#घोषणा ACTMON_DEV_CTRL_ENB_PERIODIC				BIT(18)
#घोषणा ACTMON_DEV_CTRL_AVG_BELOW_WMARK_EN			BIT(20)
#घोषणा ACTMON_DEV_CTRL_AVG_ABOVE_WMARK_EN			BIT(21)
#घोषणा ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_NUM_SHIFT	23
#घोषणा ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_NUM_SHIFT	26
#घोषणा ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_EN		BIT(29)
#घोषणा ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_EN		BIT(30)
#घोषणा ACTMON_DEV_CTRL_ENB					BIT(31)

#घोषणा ACTMON_DEV_CTRL_STOP					0x00000000

#घोषणा ACTMON_DEV_UPPER_WMARK					0x4
#घोषणा ACTMON_DEV_LOWER_WMARK					0x8
#घोषणा ACTMON_DEV_INIT_AVG					0xc
#घोषणा ACTMON_DEV_AVG_UPPER_WMARK				0x10
#घोषणा ACTMON_DEV_AVG_LOWER_WMARK				0x14
#घोषणा ACTMON_DEV_COUNT_WEIGHT					0x18
#घोषणा ACTMON_DEV_AVG_COUNT					0x20
#घोषणा ACTMON_DEV_INTR_STATUS					0x24

#घोषणा ACTMON_INTR_STATUS_CLEAR				0xffffffff

#घोषणा ACTMON_DEV_INTR_CONSECUTIVE_UPPER			BIT(31)
#घोषणा ACTMON_DEV_INTR_CONSECUTIVE_LOWER			BIT(30)

#घोषणा ACTMON_ABOVE_WMARK_WINDOW				1
#घोषणा ACTMON_BELOW_WMARK_WINDOW				3
#घोषणा ACTMON_BOOST_FREQ_STEP					16000

/*
 * ACTMON_AVERAGE_WINDOW_LOG2: शेष value क्रम @DEV_CTRL_K_VAL, which
 * translates to 2 ^ (K_VAL + 1). ex: 2 ^ (6 + 1) = 128
 */
#घोषणा ACTMON_AVERAGE_WINDOW_LOG2			6
#घोषणा ACTMON_SAMPLING_PERIOD				12 /* ms */
#घोषणा ACTMON_DEFAULT_AVG_BAND				6  /* 1/10 of % */

#घोषणा KHZ							1000

#घोषणा KHZ_MAX						(अच_दीर्घ_उच्च / KHZ)

/* Assume that the bus is saturated अगर the utilization is 25% */
#घोषणा BUS_SATURATION_RATIO					25

/**
 * काष्ठा tegra_devfreq_device_config - configuration specअगरic to an ACTMON
 * device
 *
 * Coefficients and thresholds are percentages unless otherwise noted
 */
काष्ठा tegra_devfreq_device_config अणु
	u32		offset;
	u32		irq_mask;

	/* Factors applied to boost_freq every consecutive watermark breach */
	अचिन्हित पूर्णांक	boost_up_coeff;
	अचिन्हित पूर्णांक	boost_करोwn_coeff;

	/* Define the watermark bounds when applied to the current avg */
	अचिन्हित पूर्णांक	boost_up_threshold;
	अचिन्हित पूर्णांक	boost_करोwn_threshold;

	/*
	 * Threshold of activity (cycles translated to kHz) below which the
	 * CPU frequency isn't to be taken पूर्णांकo account. This is to aव्योम
	 * increasing the EMC frequency when the CPU is very busy but not
	 * accessing the bus often.
	 */
	u32		avg_dependency_threshold;
पूर्ण;

क्रमागत tegra_acपंचांगon_device अणु
	MCALL = 0,
	MCCPU,
पूर्ण;

अटल स्थिर काष्ठा tegra_devfreq_device_config tegra124_device_configs[] = अणु
	अणु
		/* MCALL: All memory accesses (including from the CPUs) */
		.offset = 0x1c0,
		.irq_mask = 1 << 26,
		.boost_up_coeff = 200,
		.boost_करोwn_coeff = 50,
		.boost_up_threshold = 60,
		.boost_करोwn_threshold = 40,
	पूर्ण,
	अणु
		/* MCCPU: memory accesses from the CPUs */
		.offset = 0x200,
		.irq_mask = 1 << 25,
		.boost_up_coeff = 800,
		.boost_करोwn_coeff = 40,
		.boost_up_threshold = 27,
		.boost_करोwn_threshold = 10,
		.avg_dependency_threshold = 16000, /* 16MHz in kHz units */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_devfreq_device_config tegra30_device_configs[] = अणु
	अणु
		/* MCALL: All memory accesses (including from the CPUs) */
		.offset = 0x1c0,
		.irq_mask = 1 << 26,
		.boost_up_coeff = 200,
		.boost_करोwn_coeff = 50,
		.boost_up_threshold = 20,
		.boost_करोwn_threshold = 10,
	पूर्ण,
	अणु
		/* MCCPU: memory accesses from the CPUs */
		.offset = 0x200,
		.irq_mask = 1 << 25,
		.boost_up_coeff = 800,
		.boost_करोwn_coeff = 40,
		.boost_up_threshold = 27,
		.boost_करोwn_threshold = 10,
		.avg_dependency_threshold = 16000, /* 16MHz in kHz units */
	पूर्ण,
पूर्ण;

/**
 * काष्ठा tegra_devfreq_device - state specअगरic to an ACTMON device
 *
 * Frequencies are in kHz.
 */
काष्ठा tegra_devfreq_device अणु
	स्थिर काष्ठा tegra_devfreq_device_config *config;
	व्योम __iomem *regs;

	/* Average event count sampled in the last पूर्णांकerrupt */
	u32 avg_count;

	/*
	 * Extra frequency to increase the target by due to consecutive
	 * watermark breaches.
	 */
	अचिन्हित दीर्घ boost_freq;

	/* Optimal frequency calculated from the stats क्रम this device */
	अचिन्हित दीर्घ target_freq;
पूर्ण;

काष्ठा tegra_devfreq_soc_data अणु
	स्थिर काष्ठा tegra_devfreq_device_config *configs;
	/* Weight value क्रम count measurements */
	अचिन्हित पूर्णांक count_weight;
पूर्ण;

काष्ठा tegra_devfreq अणु
	काष्ठा devfreq		*devfreq;
	काष्ठा opp_table	*opp_table;

	काष्ठा reset_control	*reset;
	काष्ठा clk		*घड़ी;
	व्योम __iomem		*regs;

	काष्ठा clk		*emc_घड़ी;
	अचिन्हित दीर्घ		max_freq;
	अचिन्हित दीर्घ		cur_freq;
	काष्ठा notअगरier_block	clk_rate_change_nb;

	काष्ठा delayed_work	cpufreq_update_work;
	काष्ठा notअगरier_block	cpu_rate_change_nb;

	काष्ठा tegra_devfreq_device devices[2];

	अचिन्हित पूर्णांक		irq;

	bool			started;

	स्थिर काष्ठा tegra_devfreq_soc_data *soc;
पूर्ण;

काष्ठा tegra_acपंचांगon_emc_ratio अणु
	अचिन्हित दीर्घ cpu_freq;
	अचिन्हित दीर्घ emc_freq;
पूर्ण;

अटल स्थिर काष्ठा tegra_acपंचांगon_emc_ratio acपंचांगon_emc_ratios[] = अणु
	अणु 1400000,    KHZ_MAX पूर्ण,
	अणु 1200000,    750000 पूर्ण,
	अणु 1100000,    600000 पूर्ण,
	अणु 1000000,    500000 पूर्ण,
	अणु  800000,    375000 पूर्ण,
	अणु  500000,    200000 पूर्ण,
	अणु  250000,    100000 पूर्ण,
पूर्ण;

अटल u32 acपंचांगon_पढ़ोl(काष्ठा tegra_devfreq *tegra, u32 offset)
अणु
	वापस पढ़ोl_relaxed(tegra->regs + offset);
पूर्ण

अटल व्योम acपंचांगon_ग_लिखोl(काष्ठा tegra_devfreq *tegra, u32 val, u32 offset)
अणु
	ग_लिखोl_relaxed(val, tegra->regs + offset);
पूर्ण

अटल u32 device_पढ़ोl(काष्ठा tegra_devfreq_device *dev, u32 offset)
अणु
	वापस पढ़ोl_relaxed(dev->regs + offset);
पूर्ण

अटल व्योम device_ग_लिखोl(काष्ठा tegra_devfreq_device *dev, u32 val,
			  u32 offset)
अणु
	ग_लिखोl_relaxed(val, dev->regs + offset);
पूर्ण

अटल अचिन्हित दीर्घ करो_percent(अचिन्हित दीर्घ दीर्घ val, अचिन्हित पूर्णांक pct)
अणु
	val = val * pct;
	करो_भाग(val, 100);

	/*
	 * High freq + high boosting percent + large polling पूर्णांकerval are
	 * resulting in पूर्णांकeger overflow when watermarks are calculated.
	 */
	वापस min_t(u64, val, U32_MAX);
पूर्ण

अटल व्योम tegra_devfreq_update_avg_wmark(काष्ठा tegra_devfreq *tegra,
					   काष्ठा tegra_devfreq_device *dev)
अणु
	u32 avg_band_freq = tegra->max_freq * ACTMON_DEFAULT_AVG_BAND / KHZ;
	u32 band = avg_band_freq * tegra->devfreq->profile->polling_ms;
	u32 avg;

	avg = min(dev->avg_count, U32_MAX - band);
	device_ग_लिखोl(dev, avg + band, ACTMON_DEV_AVG_UPPER_WMARK);

	avg = max(dev->avg_count, band);
	device_ग_लिखोl(dev, avg - band, ACTMON_DEV_AVG_LOWER_WMARK);
पूर्ण

अटल व्योम tegra_devfreq_update_wmark(काष्ठा tegra_devfreq *tegra,
				       काष्ठा tegra_devfreq_device *dev)
अणु
	u32 val = tegra->cur_freq * tegra->devfreq->profile->polling_ms;

	device_ग_लिखोl(dev, करो_percent(val, dev->config->boost_up_threshold),
		      ACTMON_DEV_UPPER_WMARK);

	device_ग_लिखोl(dev, करो_percent(val, dev->config->boost_करोwn_threshold),
		      ACTMON_DEV_LOWER_WMARK);
पूर्ण

अटल व्योम acपंचांगon_isr_device(काष्ठा tegra_devfreq *tegra,
			      काष्ठा tegra_devfreq_device *dev)
अणु
	u32 पूर्णांकr_status, dev_ctrl;

	dev->avg_count = device_पढ़ोl(dev, ACTMON_DEV_AVG_COUNT);
	tegra_devfreq_update_avg_wmark(tegra, dev);

	पूर्णांकr_status = device_पढ़ोl(dev, ACTMON_DEV_INTR_STATUS);
	dev_ctrl = device_पढ़ोl(dev, ACTMON_DEV_CTRL);

	अगर (पूर्णांकr_status & ACTMON_DEV_INTR_CONSECUTIVE_UPPER) अणु
		/*
		 * new_boost = min(old_boost * up_coef + step, max_freq)
		 */
		dev->boost_freq = करो_percent(dev->boost_freq,
					     dev->config->boost_up_coeff);
		dev->boost_freq += ACTMON_BOOST_FREQ_STEP;

		dev_ctrl |= ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_EN;

		अगर (dev->boost_freq >= tegra->max_freq) अणु
			dev_ctrl &= ~ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_EN;
			dev->boost_freq = tegra->max_freq;
		पूर्ण
	पूर्ण अन्यथा अगर (पूर्णांकr_status & ACTMON_DEV_INTR_CONSECUTIVE_LOWER) अणु
		/*
		 * new_boost = old_boost * करोwn_coef
		 * or 0 अगर (old_boost * करोwn_coef < step / 2)
		 */
		dev->boost_freq = करो_percent(dev->boost_freq,
					     dev->config->boost_करोwn_coeff);

		dev_ctrl |= ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_EN;

		अगर (dev->boost_freq < (ACTMON_BOOST_FREQ_STEP >> 1)) अणु
			dev_ctrl &= ~ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_EN;
			dev->boost_freq = 0;
		पूर्ण
	पूर्ण

	device_ग_लिखोl(dev, dev_ctrl, ACTMON_DEV_CTRL);

	device_ग_लिखोl(dev, ACTMON_INTR_STATUS_CLEAR, ACTMON_DEV_INTR_STATUS);
पूर्ण

अटल अचिन्हित दीर्घ acपंचांगon_cpu_to_emc_rate(काष्ठा tegra_devfreq *tegra,
					    अचिन्हित दीर्घ cpu_freq)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर काष्ठा tegra_acपंचांगon_emc_ratio *ratio = acपंचांगon_emc_ratios;

	क्रम (i = 0; i < ARRAY_SIZE(acपंचांगon_emc_ratios); i++, ratio++) अणु
		अगर (cpu_freq >= ratio->cpu_freq) अणु
			अगर (ratio->emc_freq >= tegra->max_freq)
				वापस tegra->max_freq;
			अन्यथा
				वापस ratio->emc_freq;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ acपंचांगon_device_target_freq(काष्ठा tegra_devfreq *tegra,
					       काष्ठा tegra_devfreq_device *dev)
अणु
	अचिन्हित पूर्णांक avg_sustain_coef;
	अचिन्हित दीर्घ target_freq;

	target_freq = dev->avg_count / tegra->devfreq->profile->polling_ms;
	avg_sustain_coef = 100 * 100 / dev->config->boost_up_threshold;
	target_freq = करो_percent(target_freq, avg_sustain_coef);

	वापस target_freq;
पूर्ण

अटल व्योम acपंचांगon_update_target(काष्ठा tegra_devfreq *tegra,
				 काष्ठा tegra_devfreq_device *dev)
अणु
	अचिन्हित दीर्घ cpu_freq = 0;
	अचिन्हित दीर्घ अटल_cpu_emc_freq = 0;

	dev->target_freq = acपंचांगon_device_target_freq(tegra, dev);

	अगर (dev->config->avg_dependency_threshold &&
	    dev->config->avg_dependency_threshold <= dev->target_freq) अणु
		cpu_freq = cpufreq_quick_get(0);
		अटल_cpu_emc_freq = acपंचांगon_cpu_to_emc_rate(tegra, cpu_freq);

		dev->target_freq += dev->boost_freq;
		dev->target_freq = max(dev->target_freq, अटल_cpu_emc_freq);
	पूर्ण अन्यथा अणु
		dev->target_freq += dev->boost_freq;
	पूर्ण
पूर्ण

अटल irqवापस_t acपंचांगon_thपढ़ो_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_devfreq *tegra = data;
	bool handled = false;
	अचिन्हित पूर्णांक i;
	u32 val;

	mutex_lock(&tegra->devfreq->lock);

	val = acपंचांगon_पढ़ोl(tegra, ACTMON_GLB_STATUS);
	क्रम (i = 0; i < ARRAY_SIZE(tegra->devices); i++) अणु
		अगर (val & tegra->devices[i].config->irq_mask) अणु
			acपंचांगon_isr_device(tegra, tegra->devices + i);
			handled = true;
		पूर्ण
	पूर्ण

	अगर (handled)
		update_devfreq(tegra->devfreq);

	mutex_unlock(&tegra->devfreq->lock);

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक tegra_acपंचांगon_clk_notअगरy_cb(काष्ठा notअगरier_block *nb,
				      अचिन्हित दीर्घ action, व्योम *ptr)
अणु
	काष्ठा clk_notअगरier_data *data = ptr;
	काष्ठा tegra_devfreq *tegra;
	काष्ठा tegra_devfreq_device *dev;
	अचिन्हित पूर्णांक i;

	अगर (action != POST_RATE_CHANGE)
		वापस NOTIFY_OK;

	tegra = container_of(nb, काष्ठा tegra_devfreq, clk_rate_change_nb);

	tegra->cur_freq = data->new_rate / KHZ;

	क्रम (i = 0; i < ARRAY_SIZE(tegra->devices); i++) अणु
		dev = &tegra->devices[i];

		tegra_devfreq_update_wmark(tegra, dev);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम tegra_acपंचांगon_delayed_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tegra_devfreq *tegra = container_of(work, काष्ठा tegra_devfreq,
						   cpufreq_update_work.work);

	mutex_lock(&tegra->devfreq->lock);
	update_devfreq(tegra->devfreq);
	mutex_unlock(&tegra->devfreq->lock);
पूर्ण

अटल अचिन्हित दीर्घ
tegra_acपंचांगon_cpufreq_contribution(काष्ठा tegra_devfreq *tegra,
				  अचिन्हित पूर्णांक cpu_freq)
अणु
	काष्ठा tegra_devfreq_device *acपंचांगon_dev = &tegra->devices[MCCPU];
	अचिन्हित दीर्घ अटल_cpu_emc_freq, dev_freq;

	dev_freq = acपंचांगon_device_target_freq(tegra, acपंचांगon_dev);

	/* check whether CPU's freq is taken पूर्णांकo account at all */
	अगर (dev_freq < acपंचांगon_dev->config->avg_dependency_threshold)
		वापस 0;

	अटल_cpu_emc_freq = acपंचांगon_cpu_to_emc_rate(tegra, cpu_freq);

	अगर (dev_freq + acपंचांगon_dev->boost_freq >= अटल_cpu_emc_freq)
		वापस 0;

	वापस अटल_cpu_emc_freq;
पूर्ण

अटल पूर्णांक tegra_acपंचांगon_cpu_notअगरy_cb(काष्ठा notअगरier_block *nb,
				      अचिन्हित दीर्घ action, व्योम *ptr)
अणु
	काष्ठा cpufreq_freqs *freqs = ptr;
	काष्ठा tegra_devfreq *tegra;
	अचिन्हित दीर्घ old, new, delay;

	अगर (action != CPUFREQ_POSTCHANGE)
		वापस NOTIFY_OK;

	tegra = container_of(nb, काष्ठा tegra_devfreq, cpu_rate_change_nb);

	/*
	 * Quickly check whether CPU frequency should be taken पूर्णांकo account
	 * at all, without blocking CPUFreq's core.
	 */
	अगर (mutex_trylock(&tegra->devfreq->lock)) अणु
		old = tegra_acपंचांगon_cpufreq_contribution(tegra, freqs->old);
		new = tegra_acपंचांगon_cpufreq_contribution(tegra, freqs->new);
		mutex_unlock(&tegra->devfreq->lock);

		/*
		 * If CPU's frequency shouldn't be taken पूर्णांकo account at
		 * the moment, then there is no need to update the devfreq's
		 * state because ISR will re-check CPU's frequency on the
		 * next पूर्णांकerrupt.
		 */
		अगर (old == new)
			वापस NOTIFY_OK;
	पूर्ण

	/*
	 * CPUFreq driver should support CPUFREQ_ASYNC_NOTIFICATION in order
	 * to allow asynchronous notअगरications. This means we can't block
	 * here क्रम too दीर्घ, otherwise CPUFreq's core will complain with a
	 * warning splat.
	 */
	delay = msecs_to_jअगरfies(ACTMON_SAMPLING_PERIOD);
	schedule_delayed_work(&tegra->cpufreq_update_work, delay);

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम tegra_acपंचांगon_configure_device(काष्ठा tegra_devfreq *tegra,
					  काष्ठा tegra_devfreq_device *dev)
अणु
	u32 val = 0;

	/* reset boosting on governor's restart */
	dev->boost_freq = 0;

	dev->target_freq = tegra->cur_freq;

	dev->avg_count = tegra->cur_freq * tegra->devfreq->profile->polling_ms;
	device_ग_लिखोl(dev, dev->avg_count, ACTMON_DEV_INIT_AVG);

	tegra_devfreq_update_avg_wmark(tegra, dev);
	tegra_devfreq_update_wmark(tegra, dev);

	device_ग_लिखोl(dev, tegra->soc->count_weight, ACTMON_DEV_COUNT_WEIGHT);
	device_ग_लिखोl(dev, ACTMON_INTR_STATUS_CLEAR, ACTMON_DEV_INTR_STATUS);

	val |= ACTMON_DEV_CTRL_ENB_PERIODIC;
	val |= (ACTMON_AVERAGE_WINDOW_LOG2 - 1)
		<< ACTMON_DEV_CTRL_K_VAL_SHIFT;
	val |= (ACTMON_BELOW_WMARK_WINDOW - 1)
		<< ACTMON_DEV_CTRL_CONSECUTIVE_BELOW_WMARK_NUM_SHIFT;
	val |= (ACTMON_ABOVE_WMARK_WINDOW - 1)
		<< ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_NUM_SHIFT;
	val |= ACTMON_DEV_CTRL_AVG_ABOVE_WMARK_EN;
	val |= ACTMON_DEV_CTRL_AVG_BELOW_WMARK_EN;
	val |= ACTMON_DEV_CTRL_CONSECUTIVE_ABOVE_WMARK_EN;
	val |= ACTMON_DEV_CTRL_ENB;

	device_ग_लिखोl(dev, val, ACTMON_DEV_CTRL);
पूर्ण

अटल व्योम tegra_acपंचांगon_stop_devices(काष्ठा tegra_devfreq *tegra)
अणु
	काष्ठा tegra_devfreq_device *dev = tegra->devices;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tegra->devices); i++, dev++) अणु
		device_ग_लिखोl(dev, ACTMON_DEV_CTRL_STOP, ACTMON_DEV_CTRL);
		device_ग_लिखोl(dev, ACTMON_INTR_STATUS_CLEAR,
			      ACTMON_DEV_INTR_STATUS);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_acपंचांगon_resume(काष्ठा tegra_devfreq *tegra)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (!tegra->devfreq->profile->polling_ms || !tegra->started)
		वापस 0;

	acपंचांगon_ग_लिखोl(tegra, tegra->devfreq->profile->polling_ms - 1,
		      ACTMON_GLB_PERIOD_CTRL);

	/*
	 * CLK notअगरications are needed in order to reconfigure the upper
	 * consecutive watermark in accordance to the actual घड़ी rate
	 * to aव्योम unnecessary upper पूर्णांकerrupts.
	 */
	err = clk_notअगरier_रेजिस्टर(tegra->emc_घड़ी,
				    &tegra->clk_rate_change_nb);
	अगर (err) अणु
		dev_err(tegra->devfreq->dev.parent,
			"Failed to register rate change notifier\n");
		वापस err;
	पूर्ण

	tegra->cur_freq = clk_get_rate(tegra->emc_घड़ी) / KHZ;

	क्रम (i = 0; i < ARRAY_SIZE(tegra->devices); i++)
		tegra_acपंचांगon_configure_device(tegra, &tegra->devices[i]);

	/*
	 * We are estimating CPU's memory bandwidth requirement based on
	 * amount of memory accesses and प्रणाली's load, judging by CPU's
	 * frequency. We also करोn't want to receive events about CPU's
	 * frequency transaction when governor is stopped, hence notअगरier
	 * is रेजिस्टरed dynamically.
	 */
	err = cpufreq_रेजिस्टर_notअगरier(&tegra->cpu_rate_change_nb,
					CPUFREQ_TRANSITION_NOTIFIER);
	अगर (err) अणु
		dev_err(tegra->devfreq->dev.parent,
			"Failed to register rate change notifier: %d\n", err);
		जाओ err_stop;
	पूर्ण

	enable_irq(tegra->irq);

	वापस 0;

err_stop:
	tegra_acपंचांगon_stop_devices(tegra);

	clk_notअगरier_unरेजिस्टर(tegra->emc_घड़ी, &tegra->clk_rate_change_nb);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_acपंचांगon_start(काष्ठा tegra_devfreq *tegra)
अणु
	पूर्णांक ret = 0;

	अगर (!tegra->started) अणु
		tegra->started = true;

		ret = tegra_acपंचांगon_resume(tegra);
		अगर (ret)
			tegra->started = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम tegra_acपंचांगon_छोड़ो(काष्ठा tegra_devfreq *tegra)
अणु
	अगर (!tegra->devfreq->profile->polling_ms || !tegra->started)
		वापस;

	disable_irq(tegra->irq);

	cpufreq_unरेजिस्टर_notअगरier(&tegra->cpu_rate_change_nb,
				    CPUFREQ_TRANSITION_NOTIFIER);

	cancel_delayed_work_sync(&tegra->cpufreq_update_work);

	tegra_acपंचांगon_stop_devices(tegra);

	clk_notअगरier_unरेजिस्टर(tegra->emc_घड़ी, &tegra->clk_rate_change_nb);
पूर्ण

अटल व्योम tegra_acपंचांगon_stop(काष्ठा tegra_devfreq *tegra)
अणु
	tegra_acपंचांगon_छोड़ो(tegra);
	tegra->started = false;
पूर्ण

अटल पूर्णांक tegra_devfreq_target(काष्ठा device *dev, अचिन्हित दीर्घ *freq,
				u32 flags)
अणु
	काष्ठा dev_pm_opp *opp;
	पूर्णांक ret;

	opp = devfreq_recommended_opp(dev, freq, flags);
	अगर (IS_ERR(opp)) अणु
		dev_err(dev, "Failed to find opp for %lu Hz\n", *freq);
		वापस PTR_ERR(opp);
	पूर्ण

	ret = dev_pm_opp_set_opp(dev, opp);
	dev_pm_opp_put(opp);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_devfreq_get_dev_status(काष्ठा device *dev,
					काष्ठा devfreq_dev_status *stat)
अणु
	काष्ठा tegra_devfreq *tegra = dev_get_drvdata(dev);
	काष्ठा tegra_devfreq_device *acपंचांगon_dev;
	अचिन्हित दीर्घ cur_freq;

	cur_freq = READ_ONCE(tegra->cur_freq);

	/* To be used by the tegra governor */
	stat->निजी_data = tegra;

	/* The below are to be used by the other governors */
	stat->current_frequency = cur_freq * KHZ;

	acपंचांगon_dev = &tegra->devices[MCALL];

	/* Number of cycles spent on memory access */
	stat->busy_समय = device_पढ़ोl(acपंचांगon_dev, ACTMON_DEV_AVG_COUNT);

	/* The bus can be considered to be saturated way beक्रमe 100% */
	stat->busy_समय *= 100 / BUS_SATURATION_RATIO;

	/* Number of cycles in a sampling period */
	stat->total_समय = tegra->devfreq->profile->polling_ms * cur_freq;

	stat->busy_समय = min(stat->busy_समय, stat->total_समय);

	वापस 0;
पूर्ण

अटल काष्ठा devfreq_dev_profile tegra_devfreq_profile = अणु
	.polling_ms	= ACTMON_SAMPLING_PERIOD,
	.target		= tegra_devfreq_target,
	.get_dev_status	= tegra_devfreq_get_dev_status,
पूर्ण;

अटल पूर्णांक tegra_governor_get_target(काष्ठा devfreq *devfreq,
				     अचिन्हित दीर्घ *freq)
अणु
	काष्ठा devfreq_dev_status *stat;
	काष्ठा tegra_devfreq *tegra;
	काष्ठा tegra_devfreq_device *dev;
	अचिन्हित दीर्घ target_freq = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = devfreq_update_stats(devfreq);
	अगर (err)
		वापस err;

	stat = &devfreq->last_status;

	tegra = stat->निजी_data;

	क्रम (i = 0; i < ARRAY_SIZE(tegra->devices); i++) अणु
		dev = &tegra->devices[i];

		acपंचांगon_update_target(tegra, dev);

		target_freq = max(target_freq, dev->target_freq);
	पूर्ण

	/*
	 * tegra-devfreq driver operates with KHz units, जबतक OPP table
	 * entries use Hz units. Hence we need to convert the units क्रम the
	 * devfreq core.
	 */
	*freq = target_freq * KHZ;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_governor_event_handler(काष्ठा devfreq *devfreq,
					अचिन्हित पूर्णांक event, व्योम *data)
अणु
	काष्ठा tegra_devfreq *tegra = dev_get_drvdata(devfreq->dev.parent);
	अचिन्हित पूर्णांक *new_delay = data;
	पूर्णांक ret = 0;

	/*
	 * Couple devfreq-device with the governor early because it is
	 * needed at the moment of governor's start (used by ISR).
	 */
	tegra->devfreq = devfreq;

	चयन (event) अणु
	हाल DEVFREQ_GOV_START:
		devfreq_monitor_start(devfreq);
		ret = tegra_acपंचांगon_start(tegra);
		अवरोध;

	हाल DEVFREQ_GOV_STOP:
		tegra_acपंचांगon_stop(tegra);
		devfreq_monitor_stop(devfreq);
		अवरोध;

	हाल DEVFREQ_GOV_UPDATE_INTERVAL:
		/*
		 * ACTMON hardware supports up to 256 milliseconds क्रम the
		 * sampling period.
		 */
		अगर (*new_delay > 256) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		tegra_acपंचांगon_छोड़ो(tegra);
		devfreq_update_पूर्णांकerval(devfreq, new_delay);
		ret = tegra_acपंचांगon_resume(tegra);
		अवरोध;

	हाल DEVFREQ_GOV_SUSPEND:
		tegra_acपंचांगon_stop(tegra);
		devfreq_monitor_suspend(devfreq);
		अवरोध;

	हाल DEVFREQ_GOV_RESUME:
		devfreq_monitor_resume(devfreq);
		ret = tegra_acपंचांगon_start(tegra);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा devfreq_governor tegra_devfreq_governor = अणु
	.name = "tegra_actmon",
	.attrs = DEVFREQ_GOV_ATTR_POLLING_INTERVAL,
	.flags = DEVFREQ_GOV_FLAG_IMMUTABLE
		| DEVFREQ_GOV_FLAG_IRQ_DRIVEN,
	.get_target_freq = tegra_governor_get_target,
	.event_handler = tegra_governor_event_handler,
पूर्ण;

अटल पूर्णांक tegra_devfreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 hw_version = BIT(tegra_sku_info.soc_speeकरो_id);
	काष्ठा tegra_devfreq_device *dev;
	काष्ठा tegra_devfreq *tegra;
	काष्ठा devfreq *devfreq;
	अचिन्हित पूर्णांक i;
	दीर्घ rate;
	पूर्णांक err;

	tegra = devm_kzalloc(&pdev->dev, माप(*tegra), GFP_KERNEL);
	अगर (!tegra)
		वापस -ENOMEM;

	tegra->soc = of_device_get_match_data(&pdev->dev);

	tegra->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(tegra->regs))
		वापस PTR_ERR(tegra->regs);

	tegra->reset = devm_reset_control_get(&pdev->dev, "actmon");
	अगर (IS_ERR(tegra->reset)) अणु
		dev_err(&pdev->dev, "Failed to get reset\n");
		वापस PTR_ERR(tegra->reset);
	पूर्ण

	tegra->घड़ी = devm_clk_get(&pdev->dev, "actmon");
	अगर (IS_ERR(tegra->घड़ी)) अणु
		dev_err(&pdev->dev, "Failed to get actmon clock\n");
		वापस PTR_ERR(tegra->घड़ी);
	पूर्ण

	tegra->emc_घड़ी = devm_clk_get(&pdev->dev, "emc");
	अगर (IS_ERR(tegra->emc_घड़ी))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(tegra->emc_घड़ी),
				     "Failed to get emc clock\n");

	err = platक्रमm_get_irq(pdev, 0);
	अगर (err < 0)
		वापस err;

	tegra->irq = err;

	irq_set_status_flags(tegra->irq, IRQ_NOAUTOEN);

	err = devm_request_thपढ़ोed_irq(&pdev->dev, tegra->irq, शून्य,
					acपंचांगon_thपढ़ो_isr, IRQF_ONESHOT,
					"tegra-devfreq", tegra);
	अगर (err) अणु
		dev_err(&pdev->dev, "Interrupt request failed: %d\n", err);
		वापस err;
	पूर्ण

	tegra->opp_table = dev_pm_opp_set_supported_hw(&pdev->dev,
						       &hw_version, 1);
	err = PTR_ERR_OR_ZERO(tegra->opp_table);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to set supported HW: %d\n", err);
		वापस err;
	पूर्ण

	err = dev_pm_opp_of_add_table_noclk(&pdev->dev, 0);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to add OPP table: %d\n", err);
		जाओ put_hw;
	पूर्ण

	err = clk_prepare_enable(tegra->घड़ी);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Failed to prepare and enable ACTMON clock\n");
		जाओ हटाओ_table;
	पूर्ण

	err = reset_control_reset(tegra->reset);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to reset hardware: %d\n", err);
		जाओ disable_clk;
	पूर्ण

	rate = clk_round_rate(tegra->emc_घड़ी, अच_दीर्घ_उच्च);
	अगर (rate < 0) अणु
		dev_err(&pdev->dev, "Failed to round clock rate: %ld\n", rate);
		err = rate;
		जाओ disable_clk;
	पूर्ण

	tegra->max_freq = rate / KHZ;

	क्रम (i = 0; i < ARRAY_SIZE(tegra->devices); i++) अणु
		dev = tegra->devices + i;
		dev->config = tegra->soc->configs + i;
		dev->regs = tegra->regs + dev->config->offset;
	पूर्ण

	platक्रमm_set_drvdata(pdev, tegra);

	tegra->clk_rate_change_nb.notअगरier_call = tegra_acपंचांगon_clk_notअगरy_cb;
	tegra->cpu_rate_change_nb.notअगरier_call = tegra_acपंचांगon_cpu_notअगरy_cb;

	INIT_DELAYED_WORK(&tegra->cpufreq_update_work,
			  tegra_acपंचांगon_delayed_update);

	err = devfreq_add_governor(&tegra_devfreq_governor);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to add governor: %d\n", err);
		जाओ हटाओ_opps;
	पूर्ण

	tegra_devfreq_profile.initial_freq = clk_get_rate(tegra->emc_घड़ी);

	devfreq = devfreq_add_device(&pdev->dev, &tegra_devfreq_profile,
				     "tegra_actmon", शून्य);
	अगर (IS_ERR(devfreq)) अणु
		err = PTR_ERR(devfreq);
		जाओ हटाओ_governor;
	पूर्ण

	वापस 0;

हटाओ_governor:
	devfreq_हटाओ_governor(&tegra_devfreq_governor);

हटाओ_opps:
	dev_pm_opp_हटाओ_all_dynamic(&pdev->dev);

	reset_control_reset(tegra->reset);
disable_clk:
	clk_disable_unprepare(tegra->घड़ी);
हटाओ_table:
	dev_pm_opp_of_हटाओ_table(&pdev->dev);
put_hw:
	dev_pm_opp_put_supported_hw(tegra->opp_table);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_devfreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_devfreq *tegra = platक्रमm_get_drvdata(pdev);

	devfreq_हटाओ_device(tegra->devfreq);
	devfreq_हटाओ_governor(&tegra_devfreq_governor);

	reset_control_reset(tegra->reset);
	clk_disable_unprepare(tegra->घड़ी);

	dev_pm_opp_of_हटाओ_table(&pdev->dev);
	dev_pm_opp_put_supported_hw(tegra->opp_table);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tegra_devfreq_soc_data tegra124_soc = अणु
	.configs = tegra124_device_configs,

	/*
	 * Activity counter is incremented every 256 memory transactions,
	 * and each transaction takes 4 EMC घड़ीs.
	 */
	.count_weight = 4 * 256,
पूर्ण;

अटल स्थिर काष्ठा tegra_devfreq_soc_data tegra30_soc = अणु
	.configs = tegra30_device_configs,
	.count_weight = 2 * 256,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_devfreq_of_match[] = अणु
	अणु .compatible = "nvidia,tegra30-actmon",  .data = &tegra30_soc, पूर्ण,
	अणु .compatible = "nvidia,tegra124-actmon", .data = &tegra124_soc, पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, tegra_devfreq_of_match);

अटल काष्ठा platक्रमm_driver tegra_devfreq_driver = अणु
	.probe	= tegra_devfreq_probe,
	.हटाओ	= tegra_devfreq_हटाओ,
	.driver = अणु
		.name = "tegra-devfreq",
		.of_match_table = tegra_devfreq_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_devfreq_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Tegra devfreq driver");
MODULE_AUTHOR("Tomeu Vizoso <tomeu.vizoso@collabora.com>");
