<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * da7219-aad.c - Dialog DA7219 ALSA SoC AAD Driver
 *
 * Copyright (c) 2015 Dialog Semiconductor Ltd.
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/property.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/da7219.h>

#समावेश "da7219.h"
#समावेश "da7219-aad.h"


/*
 * Detection control
 */

व्योम da7219_aad_jack_det(काष्ठा snd_soc_component *component, काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);

	da7219->aad->jack = jack;
	da7219->aad->jack_inserted = false;

	/* Send an initial empty report */
	snd_soc_jack_report(jack, 0, DA7219_AAD_REPORT_ALL_MASK);

	/* Enable/Disable jack detection */
	snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
			    DA7219_ACCDET_EN_MASK,
			    (jack ? DA7219_ACCDET_EN_MASK : 0));
पूर्ण
EXPORT_SYMBOL_GPL(da7219_aad_jack_det);

/*
 * Button/HPTest work
 */

अटल व्योम da7219_aad_btn_det_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da7219_aad_priv *da7219_aad =
		container_of(work, काष्ठा da7219_aad_priv, btn_det_work);
	काष्ठा snd_soc_component *component = da7219_aad->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	u8 statusa, micbias_ctrl;
	bool micbias_up = false;
	पूर्णांक retries = 0;

	/* Drive headphones/lineout */
	snd_soc_component_update_bits(component, DA7219_HP_L_CTRL,
			    DA7219_HP_L_AMP_OE_MASK,
			    DA7219_HP_L_AMP_OE_MASK);
	snd_soc_component_update_bits(component, DA7219_HP_R_CTRL,
			    DA7219_HP_R_AMP_OE_MASK,
			    DA7219_HP_R_AMP_OE_MASK);

	/* Make sure mic bias is up */
	snd_soc_dapm_क्रमce_enable_pin(dapm, "Mic Bias");
	snd_soc_dapm_sync(dapm);

	करो अणु
		statusa = snd_soc_component_पढ़ो(component, DA7219_ACCDET_STATUS_A);
		अगर (statusa & DA7219_MICBIAS_UP_STS_MASK)
			micbias_up = true;
		अन्यथा अगर (retries++ < DA7219_AAD_MICBIAS_CHK_RETRIES)
			msleep(DA7219_AAD_MICBIAS_CHK_DELAY);
	पूर्ण जबतक ((!micbias_up) && (retries < DA7219_AAD_MICBIAS_CHK_RETRIES));

	अगर (retries >= DA7219_AAD_MICBIAS_CHK_RETRIES)
		dev_warn(component->dev, "Mic bias status check timed out");

	da7219->micbias_on_event = true;

	/*
	 * Mic bias pulse required to enable mic, must be करोne beक्रमe enabling
	 * button detection to prevent erroneous button पढ़ोings.
	 */
	अगर (da7219_aad->micbias_pulse_lvl && da7219_aad->micbias_pulse_समय) अणु
		/* Pulse higher level voltage */
		micbias_ctrl = snd_soc_component_पढ़ो(component, DA7219_MICBIAS_CTRL);
		snd_soc_component_update_bits(component, DA7219_MICBIAS_CTRL,
				    DA7219_MICBIAS1_LEVEL_MASK,
				    da7219_aad->micbias_pulse_lvl);
		msleep(da7219_aad->micbias_pulse_समय);
		snd_soc_component_ग_लिखो(component, DA7219_MICBIAS_CTRL, micbias_ctrl);

	पूर्ण

	snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
			    DA7219_BUTTON_CONFIG_MASK,
			    da7219_aad->btn_cfg);
पूर्ण

अटल व्योम da7219_aad_hptest_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da7219_aad_priv *da7219_aad =
		container_of(work, काष्ठा da7219_aad_priv, hptest_work);
	काष्ठा snd_soc_component *component = da7219_aad->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);

	__le16 tonegen_freq_hptest;
	u8 pll_srm_sts, pll_ctrl, gain_ramp_ctrl, accdet_cfg8;
	पूर्णांक report = 0, ret;

	/* Lock DAPM, Kcontrols affected by this test and the PLL */
	snd_soc_dapm_mutex_lock(dapm);
	mutex_lock(&da7219->ctrl_lock);
	mutex_lock(&da7219->pll_lock);

	/* Ensure MCLK is available क्रम HP test procedure */
	अगर (da7219->mclk) अणु
		ret = clk_prepare_enable(da7219->mclk);
		अगर (ret) अणु
			dev_err(component->dev, "Failed to enable mclk - %d\n", ret);
			mutex_unlock(&da7219->pll_lock);
			mutex_unlock(&da7219->ctrl_lock);
			snd_soc_dapm_mutex_unlock(dapm);
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * If MCLK not present, then we're using the पूर्णांकernal oscillator and
	 * require dअगरferent frequency settings to achieve the same result.
	 *
	 * If MCLK is present, but PLL is not enabled then we enable it here to
	 * ensure a consistent detection procedure.
	 */
	pll_srm_sts = snd_soc_component_पढ़ो(component, DA7219_PLL_SRM_STS);
	अगर (pll_srm_sts & DA7219_PLL_SRM_STS_MCLK) अणु
		tonegen_freq_hptest = cpu_to_le16(DA7219_AAD_HPTEST_RAMP_FREQ);

		pll_ctrl = snd_soc_component_पढ़ो(component, DA7219_PLL_CTRL);
		अगर ((pll_ctrl & DA7219_PLL_MODE_MASK) == DA7219_PLL_MODE_BYPASS)
			da7219_set_pll(component, DA7219_SYSCLK_PLL,
				       DA7219_PLL_FREQ_OUT_98304);
	पूर्ण अन्यथा अणु
		tonegen_freq_hptest = cpu_to_le16(DA7219_AAD_HPTEST_RAMP_FREQ_INT_OSC);
	पूर्ण

	/* Ensure gain ramping at fastest rate */
	gain_ramp_ctrl = snd_soc_component_पढ़ो(component, DA7219_GAIN_RAMP_CTRL);
	snd_soc_component_ग_लिखो(component, DA7219_GAIN_RAMP_CTRL, DA7219_GAIN_RAMP_RATE_X8);

	/* Bypass cache so it saves current settings */
	regcache_cache_bypass(da7219->regmap, true);

	/* Make sure Tone Generator is disabled */
	snd_soc_component_ग_लिखो(component, DA7219_TONE_GEN_CFG1, 0);

	/* Enable HPTest block, 1KOhms check */
	snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_8,
			    DA7219_HPTEST_EN_MASK | DA7219_HPTEST_RES_SEL_MASK,
			    DA7219_HPTEST_EN_MASK |
			    DA7219_HPTEST_RES_SEL_1KOHMS);

	/* Set gains to 0db */
	snd_soc_component_ग_लिखो(component, DA7219_DAC_L_GAIN, DA7219_DAC_DIGITAL_GAIN_0DB);
	snd_soc_component_ग_लिखो(component, DA7219_DAC_R_GAIN, DA7219_DAC_DIGITAL_GAIN_0DB);
	snd_soc_component_ग_लिखो(component, DA7219_HP_L_GAIN, DA7219_HP_AMP_GAIN_0DB);
	snd_soc_component_ग_लिखो(component, DA7219_HP_R_GAIN, DA7219_HP_AMP_GAIN_0DB);

	/* Disable DAC filters, EQs and soft mute */
	snd_soc_component_update_bits(component, DA7219_DAC_FILTERS1, DA7219_HPF_MODE_MASK,
			    0);
	snd_soc_component_update_bits(component, DA7219_DAC_FILTERS4, DA7219_DAC_EQ_EN_MASK,
			    0);
	snd_soc_component_update_bits(component, DA7219_DAC_FILTERS5,
			    DA7219_DAC_SOFTMUTE_EN_MASK, 0);

	/* Enable HP left & right paths */
	snd_soc_component_update_bits(component, DA7219_CP_CTRL, DA7219_CP_EN_MASK,
			    DA7219_CP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_DIG_ROUTING_DAC,
			    DA7219_DAC_L_SRC_MASK | DA7219_DAC_R_SRC_MASK,
			    DA7219_DAC_L_SRC_TONEGEN |
			    DA7219_DAC_R_SRC_TONEGEN);
	snd_soc_component_update_bits(component, DA7219_DAC_L_CTRL,
			    DA7219_DAC_L_EN_MASK | DA7219_DAC_L_MUTE_EN_MASK,
			    DA7219_DAC_L_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_DAC_R_CTRL,
			    DA7219_DAC_R_EN_MASK | DA7219_DAC_R_MUTE_EN_MASK,
			    DA7219_DAC_R_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_MIXOUT_L_SELECT,
			    DA7219_MIXOUT_L_MIX_SELECT_MASK,
			    DA7219_MIXOUT_L_MIX_SELECT_MASK);
	snd_soc_component_update_bits(component, DA7219_MIXOUT_R_SELECT,
			    DA7219_MIXOUT_R_MIX_SELECT_MASK,
			    DA7219_MIXOUT_R_MIX_SELECT_MASK);
	snd_soc_component_update_bits(component, DA7219_DROUTING_ST_OUTFILT_1L,
			    DA7219_OUTFILT_ST_1L_SRC_MASK,
			    DA7219_DMIX_ST_SRC_OUTFILT1L);
	snd_soc_component_update_bits(component, DA7219_DROUTING_ST_OUTFILT_1R,
			    DA7219_OUTFILT_ST_1R_SRC_MASK,
			    DA7219_DMIX_ST_SRC_OUTFILT1R);
	snd_soc_component_update_bits(component, DA7219_MIXOUT_L_CTRL,
			    DA7219_MIXOUT_L_AMP_EN_MASK,
			    DA7219_MIXOUT_L_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_MIXOUT_R_CTRL,
			    DA7219_MIXOUT_R_AMP_EN_MASK,
			    DA7219_MIXOUT_R_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_HP_L_CTRL,
			    DA7219_HP_L_AMP_OE_MASK | DA7219_HP_L_AMP_EN_MASK,
			    DA7219_HP_L_AMP_OE_MASK | DA7219_HP_L_AMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7219_HP_R_CTRL,
			    DA7219_HP_R_AMP_OE_MASK | DA7219_HP_R_AMP_EN_MASK,
			    DA7219_HP_R_AMP_OE_MASK | DA7219_HP_R_AMP_EN_MASK);
	msleep(DA7219_SETTLING_DELAY);
	snd_soc_component_update_bits(component, DA7219_HP_L_CTRL,
			    DA7219_HP_L_AMP_MUTE_EN_MASK |
			    DA7219_HP_L_AMP_MIN_GAIN_EN_MASK, 0);
	snd_soc_component_update_bits(component, DA7219_HP_R_CTRL,
			    DA7219_HP_R_AMP_MUTE_EN_MASK |
			    DA7219_HP_R_AMP_MIN_GAIN_EN_MASK, 0);

	/*
	 * If we're running from the पूर्णांकernal oscillator then give audio paths
	 * समय to settle beक्रमe running test.
	 */
	अगर (!(pll_srm_sts & DA7219_PLL_SRM_STS_MCLK))
		msleep(DA7219_AAD_HPTEST_INT_OSC_PATH_DELAY);

	/* Configure & start Tone Generator */
	snd_soc_component_ग_लिखो(component, DA7219_TONE_GEN_ON_PER, DA7219_BEEP_ON_PER_MASK);
	regmap_raw_ग_लिखो(da7219->regmap, DA7219_TONE_GEN_FREQ1_L,
			 &tonegen_freq_hptest, माप(tonegen_freq_hptest));
	snd_soc_component_update_bits(component, DA7219_TONE_GEN_CFG2,
			    DA7219_SWG_SEL_MASK | DA7219_TONE_GEN_GAIN_MASK,
			    DA7219_SWG_SEL_SRAMP |
			    DA7219_TONE_GEN_GAIN_MINUS_15DB);
	snd_soc_component_ग_लिखो(component, DA7219_TONE_GEN_CFG1, DA7219_START_STOPN_MASK);

	msleep(DA7219_AAD_HPTEST_PERIOD);

	/* Grab comparator पढ़ोing */
	accdet_cfg8 = snd_soc_component_पढ़ो(component, DA7219_ACCDET_CONFIG_8);
	अगर (accdet_cfg8 & DA7219_HPTEST_COMP_MASK)
		report |= SND_JACK_HEADPHONE;
	अन्यथा
		report |= SND_JACK_LINEOUT;

	/* Stop tone generator */
	snd_soc_component_ग_लिखो(component, DA7219_TONE_GEN_CFG1, 0);

	msleep(DA7219_AAD_HPTEST_PERIOD);

	/* Restore original settings from cache */
	regcache_mark_dirty(da7219->regmap);
	regcache_sync_region(da7219->regmap, DA7219_HP_L_CTRL,
			     DA7219_HP_R_CTRL);
	msleep(DA7219_SETTLING_DELAY);
	regcache_sync_region(da7219->regmap, DA7219_MIXOUT_L_CTRL,
			     DA7219_MIXOUT_R_CTRL);
	regcache_sync_region(da7219->regmap, DA7219_DROUTING_ST_OUTFILT_1L,
			     DA7219_DROUTING_ST_OUTFILT_1R);
	regcache_sync_region(da7219->regmap, DA7219_MIXOUT_L_SELECT,
			     DA7219_MIXOUT_R_SELECT);
	regcache_sync_region(da7219->regmap, DA7219_DAC_L_CTRL,
			     DA7219_DAC_R_CTRL);
	regcache_sync_region(da7219->regmap, DA7219_DIG_ROUTING_DAC,
			     DA7219_DIG_ROUTING_DAC);
	regcache_sync_region(da7219->regmap, DA7219_CP_CTRL, DA7219_CP_CTRL);
	regcache_sync_region(da7219->regmap, DA7219_DAC_FILTERS5,
			     DA7219_DAC_FILTERS5);
	regcache_sync_region(da7219->regmap, DA7219_DAC_FILTERS4,
			     DA7219_DAC_FILTERS1);
	regcache_sync_region(da7219->regmap, DA7219_HP_L_GAIN,
			     DA7219_HP_R_GAIN);
	regcache_sync_region(da7219->regmap, DA7219_DAC_L_GAIN,
			     DA7219_DAC_R_GAIN);
	regcache_sync_region(da7219->regmap, DA7219_TONE_GEN_ON_PER,
			     DA7219_TONE_GEN_ON_PER);
	regcache_sync_region(da7219->regmap, DA7219_TONE_GEN_FREQ1_L,
			     DA7219_TONE_GEN_FREQ1_U);
	regcache_sync_region(da7219->regmap, DA7219_TONE_GEN_CFG1,
			     DA7219_TONE_GEN_CFG2);

	regcache_cache_bypass(da7219->regmap, false);

	/* Disable HPTest block */
	snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_8,
			    DA7219_HPTEST_EN_MASK, 0);

	/*
	 * If we're running from the पूर्णांकernal oscillator then give audio paths
	 * समय to settle beक्रमe allowing headphones to be driven as required.
	 */
	अगर (!(pll_srm_sts & DA7219_PLL_SRM_STS_MCLK))
		msleep(DA7219_AAD_HPTEST_INT_OSC_PATH_DELAY);

	/* Restore gain ramping rate */
	snd_soc_component_ग_लिखो(component, DA7219_GAIN_RAMP_CTRL, gain_ramp_ctrl);

	/* Drive Headphones/lineout */
	snd_soc_component_update_bits(component, DA7219_HP_L_CTRL, DA7219_HP_L_AMP_OE_MASK,
			    DA7219_HP_L_AMP_OE_MASK);
	snd_soc_component_update_bits(component, DA7219_HP_R_CTRL, DA7219_HP_R_AMP_OE_MASK,
			    DA7219_HP_R_AMP_OE_MASK);

	/* Restore PLL to previous configuration, अगर re-configured */
	अगर ((pll_srm_sts & DA7219_PLL_SRM_STS_MCLK) &&
	    ((pll_ctrl & DA7219_PLL_MODE_MASK) == DA7219_PLL_MODE_BYPASS))
		da7219_set_pll(component, DA7219_SYSCLK_MCLK, 0);

	/* Remove MCLK, अगर previously enabled */
	अगर (da7219->mclk)
		clk_disable_unprepare(da7219->mclk);

	mutex_unlock(&da7219->pll_lock);
	mutex_unlock(&da7219->ctrl_lock);
	snd_soc_dapm_mutex_unlock(dapm);

	/*
	 * Only send report अगर jack hasn't been हटाओd during process,
	 * otherwise it's invalid and we drop it.
	 */
	अगर (da7219_aad->jack_inserted)
		snd_soc_jack_report(da7219_aad->jack, report,
				    SND_JACK_HEADSET | SND_JACK_LINEOUT);
पूर्ण


/*
 * IRQ
 */

अटल irqवापस_t da7219_aad_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da7219_aad_priv *da7219_aad = data;
	काष्ठा snd_soc_component *component = da7219_aad->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	u8 events[DA7219_AAD_IRQ_REG_MAX];
	u8 statusa;
	पूर्णांक i, report = 0, mask = 0;

	/* Read current IRQ events */
	regmap_bulk_पढ़ो(da7219->regmap, DA7219_ACCDET_IRQ_EVENT_A,
			 events, DA7219_AAD_IRQ_REG_MAX);

	अगर (!events[DA7219_AAD_IRQ_REG_A] && !events[DA7219_AAD_IRQ_REG_B])
		वापस IRQ_NONE;

	/* Read status रेजिस्टर क्रम jack insertion & type status */
	statusa = snd_soc_component_पढ़ो(component, DA7219_ACCDET_STATUS_A);

	/* Clear events */
	regmap_bulk_ग_लिखो(da7219->regmap, DA7219_ACCDET_IRQ_EVENT_A,
			  events, DA7219_AAD_IRQ_REG_MAX);

	dev_dbg(component->dev, "IRQ events = 0x%x|0x%x, status = 0x%x\n",
		events[DA7219_AAD_IRQ_REG_A], events[DA7219_AAD_IRQ_REG_B],
		statusa);

	अगर (statusa & DA7219_JACK_INSERTION_STS_MASK) अणु
		/* Jack Insertion */
		अगर (events[DA7219_AAD_IRQ_REG_A] &
		    DA7219_E_JACK_INSERTED_MASK) अणु
			report |= SND_JACK_MECHANICAL;
			mask |= SND_JACK_MECHANICAL;
			da7219_aad->jack_inserted = true;
		पूर्ण

		/* Jack type detection */
		अगर (events[DA7219_AAD_IRQ_REG_A] &
		    DA7219_E_JACK_DETECT_COMPLETE_MASK) अणु
			/*
			 * If 4-pole, then enable button detection, अन्यथा perक्रमm
			 * HP impedance test to determine output type to report.
			 *
			 * We schedule work here as the tasks themselves can
			 * take समय to complete, and in particular क्रम hptest
			 * we want to be able to check अगर the jack was हटाओd
			 * during the procedure as this will invalidate the
			 * result. By करोing this as work, the IRQ thपढ़ो can
			 * handle a removal, and we can check at the end of
			 * hptest अगर we have a valid result or not.
			 */
			अगर (statusa & DA7219_JACK_TYPE_STS_MASK) अणु
				report |= SND_JACK_HEADSET;
				mask |=	SND_JACK_HEADSET | SND_JACK_LINEOUT;
				schedule_work(&da7219_aad->btn_det_work);
			पूर्ण अन्यथा अणु
				schedule_work(&da7219_aad->hptest_work);
			पूर्ण
		पूर्ण

		/* Button support क्रम 4-pole jack */
		अगर (statusa & DA7219_JACK_TYPE_STS_MASK) अणु
			क्रम (i = 0; i < DA7219_AAD_MAX_BUTTONS; ++i) अणु
				/* Button Press */
				अगर (events[DA7219_AAD_IRQ_REG_B] &
				    (DA7219_E_BUTTON_A_PRESSED_MASK << i)) अणु
					report |= SND_JACK_BTN_0 >> i;
					mask |= SND_JACK_BTN_0 >> i;
				पूर्ण
			पूर्ण
			snd_soc_jack_report(da7219_aad->jack, report, mask);

			क्रम (i = 0; i < DA7219_AAD_MAX_BUTTONS; ++i) अणु
				/* Button Release */
				अगर (events[DA7219_AAD_IRQ_REG_B] &
				    (DA7219_E_BUTTON_A_RELEASED_MASK >> i)) अणु
					report &= ~(SND_JACK_BTN_0 >> i);
					mask |= SND_JACK_BTN_0 >> i;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Jack removal */
		अगर (events[DA7219_AAD_IRQ_REG_A] & DA7219_E_JACK_REMOVED_MASK) अणु
			report = 0;
			mask |= DA7219_AAD_REPORT_ALL_MASK;
			da7219_aad->jack_inserted = false;

			/* Un-drive headphones/lineout */
			snd_soc_component_update_bits(component, DA7219_HP_R_CTRL,
					    DA7219_HP_R_AMP_OE_MASK, 0);
			snd_soc_component_update_bits(component, DA7219_HP_L_CTRL,
					    DA7219_HP_L_AMP_OE_MASK, 0);

			/* Ensure button detection disabled */
			snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
					    DA7219_BUTTON_CONFIG_MASK, 0);

			da7219->micbias_on_event = false;

			/* Disable mic bias */
			snd_soc_dapm_disable_pin(dapm, "Mic Bias");
			snd_soc_dapm_sync(dapm);

			/* Cancel any pending work */
			cancel_work_sync(&da7219_aad->btn_det_work);
			cancel_work_sync(&da7219_aad->hptest_work);
		पूर्ण
	पूर्ण

	snd_soc_jack_report(da7219_aad->jack, report, mask);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * DT/ACPI to pdata conversion
 */

अटल क्रमागत da7219_aad_micbias_pulse_lvl
	da7219_aad_fw_micbias_pulse_lvl(काष्ठा device *dev, u32 val)
अणु
	चयन (val) अणु
	हाल 2800:
		वापस DA7219_AAD_MICBIAS_PULSE_LVL_2_8V;
	हाल 2900:
		वापस DA7219_AAD_MICBIAS_PULSE_LVL_2_9V;
	शेष:
		dev_warn(dev, "Invalid micbias pulse level");
		वापस DA7219_AAD_MICBIAS_PULSE_LVL_OFF;
	पूर्ण
पूर्ण

अटल क्रमागत da7219_aad_btn_cfg
	da7219_aad_fw_btn_cfg(काष्ठा device *dev, u32 val)
अणु
	चयन (val) अणु
	हाल 2:
		वापस DA7219_AAD_BTN_CFG_2MS;
	हाल 5:
		वापस DA7219_AAD_BTN_CFG_5MS;
	हाल 10:
		वापस DA7219_AAD_BTN_CFG_10MS;
	हाल 50:
		वापस DA7219_AAD_BTN_CFG_50MS;
	हाल 100:
		वापस DA7219_AAD_BTN_CFG_100MS;
	हाल 200:
		वापस DA7219_AAD_BTN_CFG_200MS;
	हाल 500:
		वापस DA7219_AAD_BTN_CFG_500MS;
	शेष:
		dev_warn(dev, "Invalid button config");
		वापस DA7219_AAD_BTN_CFG_10MS;
	पूर्ण
पूर्ण

अटल क्रमागत da7219_aad_mic_det_thr
	da7219_aad_fw_mic_det_thr(काष्ठा device *dev, u32 val)
अणु
	चयन (val) अणु
	हाल 200:
		वापस DA7219_AAD_MIC_DET_THR_200_OHMS;
	हाल 500:
		वापस DA7219_AAD_MIC_DET_THR_500_OHMS;
	हाल 750:
		वापस DA7219_AAD_MIC_DET_THR_750_OHMS;
	हाल 1000:
		वापस DA7219_AAD_MIC_DET_THR_1000_OHMS;
	शेष:
		dev_warn(dev, "Invalid mic detect threshold");
		वापस DA7219_AAD_MIC_DET_THR_500_OHMS;
	पूर्ण
पूर्ण

अटल क्रमागत da7219_aad_jack_ins_deb
	da7219_aad_fw_jack_ins_deb(काष्ठा device *dev, u32 val)
अणु
	चयन (val) अणु
	हाल 5:
		वापस DA7219_AAD_JACK_INS_DEB_5MS;
	हाल 10:
		वापस DA7219_AAD_JACK_INS_DEB_10MS;
	हाल 20:
		वापस DA7219_AAD_JACK_INS_DEB_20MS;
	हाल 50:
		वापस DA7219_AAD_JACK_INS_DEB_50MS;
	हाल 100:
		वापस DA7219_AAD_JACK_INS_DEB_100MS;
	हाल 200:
		वापस DA7219_AAD_JACK_INS_DEB_200MS;
	हाल 500:
		वापस DA7219_AAD_JACK_INS_DEB_500MS;
	हाल 1000:
		वापस DA7219_AAD_JACK_INS_DEB_1S;
	शेष:
		dev_warn(dev, "Invalid jack insert debounce");
		वापस DA7219_AAD_JACK_INS_DEB_20MS;
	पूर्ण
पूर्ण

अटल क्रमागत da7219_aad_jack_det_rate
	da7219_aad_fw_jack_det_rate(काष्ठा device *dev, स्थिर अक्षर *str)
अणु
	अगर (!म_भेद(str, "32ms_64ms")) अणु
		वापस DA7219_AAD_JACK_DET_RATE_32_64MS;
	पूर्ण अन्यथा अगर (!म_भेद(str, "64ms_128ms")) अणु
		वापस DA7219_AAD_JACK_DET_RATE_64_128MS;
	पूर्ण अन्यथा अगर (!म_भेद(str, "128ms_256ms")) अणु
		वापस DA7219_AAD_JACK_DET_RATE_128_256MS;
	पूर्ण अन्यथा अगर (!म_भेद(str, "256ms_512ms")) अणु
		वापस DA7219_AAD_JACK_DET_RATE_256_512MS;
	पूर्ण अन्यथा अणु
		dev_warn(dev, "Invalid jack detect rate");
		वापस DA7219_AAD_JACK_DET_RATE_256_512MS;
	पूर्ण
पूर्ण

अटल क्रमागत da7219_aad_jack_rem_deb
	da7219_aad_fw_jack_rem_deb(काष्ठा device *dev, u32 val)
अणु
	चयन (val) अणु
	हाल 1:
		वापस DA7219_AAD_JACK_REM_DEB_1MS;
	हाल 5:
		वापस DA7219_AAD_JACK_REM_DEB_5MS;
	हाल 10:
		वापस DA7219_AAD_JACK_REM_DEB_10MS;
	हाल 20:
		वापस DA7219_AAD_JACK_REM_DEB_20MS;
	शेष:
		dev_warn(dev, "Invalid jack removal debounce");
		वापस DA7219_AAD_JACK_REM_DEB_1MS;
	पूर्ण
पूर्ण

अटल क्रमागत da7219_aad_btn_avg
	da7219_aad_fw_btn_avg(काष्ठा device *dev, u32 val)
अणु
	चयन (val) अणु
	हाल 1:
		वापस DA7219_AAD_BTN_AVG_1;
	हाल 2:
		वापस DA7219_AAD_BTN_AVG_2;
	हाल 4:
		वापस DA7219_AAD_BTN_AVG_4;
	हाल 8:
		वापस DA7219_AAD_BTN_AVG_8;
	शेष:
		dev_warn(dev, "Invalid button average value");
		वापस DA7219_AAD_BTN_AVG_2;
	पूर्ण
पूर्ण

अटल क्रमागत da7219_aad_adc_1bit_rpt
	da7219_aad_fw_adc_1bit_rpt(काष्ठा device *dev, u32 val)
अणु
	चयन (val) अणु
	हाल 1:
		वापस DA7219_AAD_ADC_1BIT_RPT_1;
	हाल 2:
		वापस DA7219_AAD_ADC_1BIT_RPT_2;
	हाल 4:
		वापस DA7219_AAD_ADC_1BIT_RPT_4;
	हाल 8:
		वापस DA7219_AAD_ADC_1BIT_RPT_8;
	शेष:
		dev_warn(dev, "Invalid ADC 1-bit repeat value");
		वापस DA7219_AAD_ADC_1BIT_RPT_1;
	पूर्ण
पूर्ण

अटल काष्ठा da7219_aad_pdata *da7219_aad_fw_to_pdata(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा fwnode_handle *aad_np;
	काष्ठा da7219_aad_pdata *aad_pdata;
	स्थिर अक्षर *fw_str;
	u32 fw_val32;

	aad_np = device_get_named_child_node(dev, "da7219_aad");
	अगर (!aad_np)
		वापस शून्य;

	aad_pdata = devm_kzalloc(dev, माप(*aad_pdata), GFP_KERNEL);
	अगर (!aad_pdata)
		वापस शून्य;

	aad_pdata->irq = i2c->irq;

	अगर (fwnode_property_पढ़ो_u32(aad_np, "dlg,micbias-pulse-lvl",
				     &fw_val32) >= 0)
		aad_pdata->micbias_pulse_lvl =
			da7219_aad_fw_micbias_pulse_lvl(dev, fw_val32);
	अन्यथा
		aad_pdata->micbias_pulse_lvl = DA7219_AAD_MICBIAS_PULSE_LVL_OFF;

	अगर (fwnode_property_पढ़ो_u32(aad_np, "dlg,micbias-pulse-time",
				     &fw_val32) >= 0)
		aad_pdata->micbias_pulse_समय = fw_val32;

	अगर (fwnode_property_पढ़ो_u32(aad_np, "dlg,btn-cfg", &fw_val32) >= 0)
		aad_pdata->btn_cfg = da7219_aad_fw_btn_cfg(dev, fw_val32);
	अन्यथा
		aad_pdata->btn_cfg = DA7219_AAD_BTN_CFG_10MS;

	अगर (fwnode_property_पढ़ो_u32(aad_np, "dlg,mic-det-thr", &fw_val32) >= 0)
		aad_pdata->mic_det_thr =
			da7219_aad_fw_mic_det_thr(dev, fw_val32);
	अन्यथा
		aad_pdata->mic_det_thr = DA7219_AAD_MIC_DET_THR_500_OHMS;

	अगर (fwnode_property_पढ़ो_u32(aad_np, "dlg,jack-ins-deb", &fw_val32) >= 0)
		aad_pdata->jack_ins_deb =
			da7219_aad_fw_jack_ins_deb(dev, fw_val32);
	अन्यथा
		aad_pdata->jack_ins_deb = DA7219_AAD_JACK_INS_DEB_20MS;

	अगर (!fwnode_property_पढ़ो_string(aad_np, "dlg,jack-det-rate", &fw_str))
		aad_pdata->jack_det_rate =
			da7219_aad_fw_jack_det_rate(dev, fw_str);
	अन्यथा
		aad_pdata->jack_det_rate = DA7219_AAD_JACK_DET_RATE_256_512MS;

	अगर (fwnode_property_पढ़ो_u32(aad_np, "dlg,jack-rem-deb", &fw_val32) >= 0)
		aad_pdata->jack_rem_deb =
			da7219_aad_fw_jack_rem_deb(dev, fw_val32);
	अन्यथा
		aad_pdata->jack_rem_deb = DA7219_AAD_JACK_REM_DEB_1MS;

	अगर (fwnode_property_पढ़ो_u32(aad_np, "dlg,a-d-btn-thr", &fw_val32) >= 0)
		aad_pdata->a_d_btn_thr = (u8) fw_val32;
	अन्यथा
		aad_pdata->a_d_btn_thr = 0xA;

	अगर (fwnode_property_पढ़ो_u32(aad_np, "dlg,d-b-btn-thr", &fw_val32) >= 0)
		aad_pdata->d_b_btn_thr = (u8) fw_val32;
	अन्यथा
		aad_pdata->d_b_btn_thr = 0x16;

	अगर (fwnode_property_पढ़ो_u32(aad_np, "dlg,b-c-btn-thr", &fw_val32) >= 0)
		aad_pdata->b_c_btn_thr = (u8) fw_val32;
	अन्यथा
		aad_pdata->b_c_btn_thr = 0x21;

	अगर (fwnode_property_पढ़ो_u32(aad_np, "dlg,c-mic-btn-thr", &fw_val32) >= 0)
		aad_pdata->c_mic_btn_thr = (u8) fw_val32;
	अन्यथा
		aad_pdata->c_mic_btn_thr = 0x3E;

	अगर (fwnode_property_पढ़ो_u32(aad_np, "dlg,btn-avg", &fw_val32) >= 0)
		aad_pdata->btn_avg = da7219_aad_fw_btn_avg(dev, fw_val32);
	अन्यथा
		aad_pdata->btn_avg = DA7219_AAD_BTN_AVG_2;

	अगर (fwnode_property_पढ़ो_u32(aad_np, "dlg,adc-1bit-rpt", &fw_val32) >= 0)
		aad_pdata->adc_1bit_rpt =
			da7219_aad_fw_adc_1bit_rpt(dev, fw_val32);
	अन्यथा
		aad_pdata->adc_1bit_rpt = DA7219_AAD_ADC_1BIT_RPT_1;

	वापस aad_pdata;
पूर्ण

अटल व्योम da7219_aad_handle_pdata(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा da7219_aad_priv *da7219_aad = da7219->aad;
	काष्ठा da7219_pdata *pdata = da7219->pdata;

	अगर ((pdata) && (pdata->aad_pdata)) अणु
		काष्ठा da7219_aad_pdata *aad_pdata = pdata->aad_pdata;
		u8 cfg, mask;

		da7219_aad->irq = aad_pdata->irq;

		चयन (aad_pdata->micbias_pulse_lvl) अणु
		हाल DA7219_AAD_MICBIAS_PULSE_LVL_2_8V:
		हाल DA7219_AAD_MICBIAS_PULSE_LVL_2_9V:
			da7219_aad->micbias_pulse_lvl =
				(aad_pdata->micbias_pulse_lvl <<
				 DA7219_MICBIAS1_LEVEL_SHIFT);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		da7219_aad->micbias_pulse_समय = aad_pdata->micbias_pulse_समय;

		चयन (aad_pdata->btn_cfg) अणु
		हाल DA7219_AAD_BTN_CFG_2MS:
		हाल DA7219_AAD_BTN_CFG_5MS:
		हाल DA7219_AAD_BTN_CFG_10MS:
		हाल DA7219_AAD_BTN_CFG_50MS:
		हाल DA7219_AAD_BTN_CFG_100MS:
		हाल DA7219_AAD_BTN_CFG_200MS:
		हाल DA7219_AAD_BTN_CFG_500MS:
			da7219_aad->btn_cfg  = (aad_pdata->btn_cfg <<
						DA7219_BUTTON_CONFIG_SHIFT);
		पूर्ण

		cfg = 0;
		mask = 0;
		चयन (aad_pdata->mic_det_thr) अणु
		हाल DA7219_AAD_MIC_DET_THR_200_OHMS:
		हाल DA7219_AAD_MIC_DET_THR_500_OHMS:
		हाल DA7219_AAD_MIC_DET_THR_750_OHMS:
		हाल DA7219_AAD_MIC_DET_THR_1000_OHMS:
			cfg |= (aad_pdata->mic_det_thr <<
				DA7219_MIC_DET_THRESH_SHIFT);
			mask |= DA7219_MIC_DET_THRESH_MASK;
		पूर्ण
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1, mask, cfg);

		cfg = 0;
		mask = 0;
		चयन (aad_pdata->jack_ins_deb) अणु
		हाल DA7219_AAD_JACK_INS_DEB_5MS:
		हाल DA7219_AAD_JACK_INS_DEB_10MS:
		हाल DA7219_AAD_JACK_INS_DEB_20MS:
		हाल DA7219_AAD_JACK_INS_DEB_50MS:
		हाल DA7219_AAD_JACK_INS_DEB_100MS:
		हाल DA7219_AAD_JACK_INS_DEB_200MS:
		हाल DA7219_AAD_JACK_INS_DEB_500MS:
		हाल DA7219_AAD_JACK_INS_DEB_1S:
			cfg |= (aad_pdata->jack_ins_deb <<
				DA7219_JACKDET_DEBOUNCE_SHIFT);
			mask |= DA7219_JACKDET_DEBOUNCE_MASK;
		पूर्ण
		चयन (aad_pdata->jack_det_rate) अणु
		हाल DA7219_AAD_JACK_DET_RATE_32_64MS:
		हाल DA7219_AAD_JACK_DET_RATE_64_128MS:
		हाल DA7219_AAD_JACK_DET_RATE_128_256MS:
		हाल DA7219_AAD_JACK_DET_RATE_256_512MS:
			cfg |= (aad_pdata->jack_det_rate <<
				DA7219_JACK_DETECT_RATE_SHIFT);
			mask |= DA7219_JACK_DETECT_RATE_MASK;
		पूर्ण
		चयन (aad_pdata->jack_rem_deb) अणु
		हाल DA7219_AAD_JACK_REM_DEB_1MS:
		हाल DA7219_AAD_JACK_REM_DEB_5MS:
		हाल DA7219_AAD_JACK_REM_DEB_10MS:
		हाल DA7219_AAD_JACK_REM_DEB_20MS:
			cfg |= (aad_pdata->jack_rem_deb <<
				DA7219_JACKDET_REM_DEB_SHIFT);
			mask |= DA7219_JACKDET_REM_DEB_MASK;
		पूर्ण
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_2, mask, cfg);

		snd_soc_component_ग_लिखो(component, DA7219_ACCDET_CONFIG_3,
			      aad_pdata->a_d_btn_thr);
		snd_soc_component_ग_लिखो(component, DA7219_ACCDET_CONFIG_4,
			      aad_pdata->d_b_btn_thr);
		snd_soc_component_ग_लिखो(component, DA7219_ACCDET_CONFIG_5,
			      aad_pdata->b_c_btn_thr);
		snd_soc_component_ग_लिखो(component, DA7219_ACCDET_CONFIG_6,
			      aad_pdata->c_mic_btn_thr);

		cfg = 0;
		mask = 0;
		चयन (aad_pdata->btn_avg) अणु
		हाल DA7219_AAD_BTN_AVG_1:
		हाल DA7219_AAD_BTN_AVG_2:
		हाल DA7219_AAD_BTN_AVG_4:
		हाल DA7219_AAD_BTN_AVG_8:
			cfg |= (aad_pdata->btn_avg <<
				DA7219_BUTTON_AVERAGE_SHIFT);
			mask |= DA7219_BUTTON_AVERAGE_MASK;
		पूर्ण
		चयन (aad_pdata->adc_1bit_rpt) अणु
		हाल DA7219_AAD_ADC_1BIT_RPT_1:
		हाल DA7219_AAD_ADC_1BIT_RPT_2:
		हाल DA7219_AAD_ADC_1BIT_RPT_4:
		हाल DA7219_AAD_ADC_1BIT_RPT_8:
			cfg |= (aad_pdata->adc_1bit_rpt <<
			       DA7219_ADC_1_BIT_REPEAT_SHIFT);
			mask |= DA7219_ADC_1_BIT_REPEAT_MASK;
		पूर्ण
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_7, mask, cfg);
	पूर्ण
पूर्ण


/*
 * Suspend/Resume
 */

व्योम da7219_aad_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा da7219_aad_priv *da7219_aad = da7219->aad;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	u8 micbias_ctrl;

	अगर (da7219_aad->jack) अणु
		/* Disable jack detection during suspend */
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
				    DA7219_ACCDET_EN_MASK, 0);

		/*
		 * If we have a 4-pole jack inserted, then micbias will be
		 * enabled. We can disable micbias here, and keep a note to
		 * re-enable it on resume. If jack removal occurred during
		 * suspend then this will be dealt with through the IRQ handler.
		 */
		अगर (da7219_aad->jack_inserted) अणु
			micbias_ctrl = snd_soc_component_पढ़ो(component, DA7219_MICBIAS_CTRL);
			अगर (micbias_ctrl & DA7219_MICBIAS1_EN_MASK) अणु
				snd_soc_dapm_disable_pin(dapm, "Mic Bias");
				snd_soc_dapm_sync(dapm);
				da7219_aad->micbias_resume_enable = true;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम da7219_aad_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा da7219_aad_priv *da7219_aad = da7219->aad;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	अगर (da7219_aad->jack) अणु
		/* Re-enable micbias अगर previously enabled क्रम 4-pole jack */
		अगर (da7219_aad->jack_inserted &&
		    da7219_aad->micbias_resume_enable) अणु
			snd_soc_dapm_क्रमce_enable_pin(dapm, "Mic Bias");
			snd_soc_dapm_sync(dapm);
			da7219_aad->micbias_resume_enable = false;
		पूर्ण

		/* Re-enable jack detection */
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
				    DA7219_ACCDET_EN_MASK,
				    DA7219_ACCDET_EN_MASK);
	पूर्ण
पूर्ण


/*
 * Init/Exit
 */

पूर्णांक da7219_aad_init(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा da7219_aad_priv *da7219_aad = da7219->aad;
	u8 mask[DA7219_AAD_IRQ_REG_MAX];
	पूर्णांक ret;

	da7219_aad->component = component;

	/* Handle any DT/ACPI/platक्रमm data */
	da7219_aad_handle_pdata(component);

	/* Disable button detection */
	snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
			    DA7219_BUTTON_CONFIG_MASK, 0);

	INIT_WORK(&da7219_aad->btn_det_work, da7219_aad_btn_det_work);
	INIT_WORK(&da7219_aad->hptest_work, da7219_aad_hptest_work);

	ret = request_thपढ़ोed_irq(da7219_aad->irq, शून्य,
				   da7219_aad_irq_thपढ़ो,
				   IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				   "da7219-aad", da7219_aad);
	अगर (ret) अणु
		dev_err(component->dev, "Failed to request IRQ: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Unmask AAD IRQs */
	स_रखो(mask, 0, DA7219_AAD_IRQ_REG_MAX);
	regmap_bulk_ग_लिखो(da7219->regmap, DA7219_ACCDET_IRQ_MASK_A,
			  &mask, DA7219_AAD_IRQ_REG_MAX);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(da7219_aad_init);

व्योम da7219_aad_निकास(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	काष्ठा da7219_aad_priv *da7219_aad = da7219->aad;
	u8 mask[DA7219_AAD_IRQ_REG_MAX];

	/* Mask off AAD IRQs */
	स_रखो(mask, DA7219_BYTE_MASK, DA7219_AAD_IRQ_REG_MAX);
	regmap_bulk_ग_लिखो(da7219->regmap, DA7219_ACCDET_IRQ_MASK_A,
			  mask, DA7219_AAD_IRQ_REG_MAX);

	मुक्त_irq(da7219_aad->irq, da7219_aad);

	cancel_work_sync(&da7219_aad->btn_det_work);
	cancel_work_sync(&da7219_aad->hptest_work);
पूर्ण
EXPORT_SYMBOL_GPL(da7219_aad_निकास);

/*
 * AAD related I2C probe handling
 */

पूर्णांक da7219_aad_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा da7219_priv *da7219 = i2c_get_clientdata(i2c);
	काष्ठा device *dev = &i2c->dev;
	काष्ठा da7219_aad_priv *da7219_aad;

	da7219_aad = devm_kzalloc(dev, माप(*da7219_aad), GFP_KERNEL);
	अगर (!da7219_aad)
		वापस -ENOMEM;

	da7219->aad = da7219_aad;

	/* Retrieve any DT/ACPI/platक्रमm data */
	अगर (da7219->pdata && !da7219->pdata->aad_pdata)
		da7219->pdata->aad_pdata = da7219_aad_fw_to_pdata(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(da7219_aad_probe);

MODULE_DESCRIPTION("ASoC DA7219 AAD Driver");
MODULE_AUTHOR("Adam Thomson <Adam.Thomson.Opensource@diasemi.com>");
MODULE_LICENSE("GPL");
