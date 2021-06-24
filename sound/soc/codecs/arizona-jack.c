<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * extcon-arizona.c - Extcon driver Wolfson Arizona devices
 *
 *  Copyright (C) 2012-2014 Wolfson Microelectronics plc
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/input.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <sound/jack.h>
#समावेश <sound/soc.h>

#समावेश <linux/mfd/arizona/core.h>
#समावेश <linux/mfd/arizona/pdata.h>
#समावेश <linux/mfd/arizona/रेजिस्टरs.h>
#समावेश <dt-bindings/mfd/arizona.h>

#समावेश "arizona.h"

#घोषणा ARIZONA_MAX_MICD_RANGE 8

/*
 * The hardware supports 8 ranges / buttons, but the snd-jack पूर्णांकerface
 * only supports 6 buttons (button 0-5).
 */
#घोषणा ARIZONA_MAX_MICD_BUTTONS 6

#घोषणा ARIZONA_MICD_CLAMP_MODE_JDL      0x4
#घोषणा ARIZONA_MICD_CLAMP_MODE_JDH      0x5
#घोषणा ARIZONA_MICD_CLAMP_MODE_JDL_GP5H 0x9
#घोषणा ARIZONA_MICD_CLAMP_MODE_JDH_GP5H 0xb

#घोषणा ARIZONA_TST_CAP_DEFAULT 0x3
#घोषणा ARIZONA_TST_CAP_CLAMP   0x1

#घोषणा ARIZONA_HPDET_MAX 10000

#घोषणा HPDET_DEBOUNCE 500
#घोषणा DEFAULT_MICD_TIMEOUT 2000

#घोषणा ARIZONA_HPDET_WAIT_COUNT 15
#घोषणा ARIZONA_HPDET_WAIT_DELAY_MS 20

#घोषणा QUICK_HEADPHONE_MAX_OHM 3
#घोषणा MICROPHONE_MIN_OHM      1257
#घोषणा MICROPHONE_MAX_OHM      30000

#घोषणा MICD_DBTIME_TWO_READINGS 2
#घोषणा MICD_DBTIME_FOUR_READINGS 4

#घोषणा MICD_LVL_1_TO_7 (ARIZONA_MICD_LVL_1 | ARIZONA_MICD_LVL_2 | \
			 ARIZONA_MICD_LVL_3 | ARIZONA_MICD_LVL_4 | \
			 ARIZONA_MICD_LVL_5 | ARIZONA_MICD_LVL_6 | \
			 ARIZONA_MICD_LVL_7)

#घोषणा MICD_LVL_0_TO_7 (ARIZONA_MICD_LVL_0 | MICD_LVL_1_TO_7)

#घोषणा MICD_LVL_0_TO_8 (MICD_LVL_0_TO_7 | ARIZONA_MICD_LVL_8)

अटल स्थिर काष्ठा arizona_micd_config micd_शेष_modes[] = अणु
	अणु ARIZONA_ACCDET_SRC, 1, 0 पूर्ण,
	अणु 0,                  2, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा arizona_micd_range micd_शेष_ranges[] = अणु
	अणु .max =  11, .key = BTN_0 पूर्ण,
	अणु .max =  28, .key = BTN_1 पूर्ण,
	अणु .max =  54, .key = BTN_2 पूर्ण,
	अणु .max = 100, .key = BTN_3 पूर्ण,
	अणु .max = 186, .key = BTN_4 पूर्ण,
	अणु .max = 430, .key = BTN_5 पूर्ण,
पूर्ण;

/* The number of levels in arizona_micd_levels valid क्रम button thresholds */
#घोषणा ARIZONA_NUM_MICD_BUTTON_LEVELS 64

अटल स्थिर पूर्णांक arizona_micd_levels[] = अणु
	3, 6, 8, 11, 13, 16, 18, 21, 23, 26, 28, 31, 34, 36, 39, 41, 44, 46,
	49, 52, 54, 57, 60, 62, 65, 67, 70, 73, 75, 78, 81, 83, 89, 94, 100,
	105, 111, 116, 122, 127, 139, 150, 161, 173, 186, 196, 209, 220, 245,
	270, 295, 321, 348, 375, 402, 430, 489, 550, 614, 681, 752, 903, 1071,
	1257, 30000,
पूर्ण;

अटल व्योम arizona_start_hpdet_acc_id(काष्ठा arizona_priv *info);

अटल व्योम arizona_extcon_hp_clamp(काष्ठा arizona_priv *info,
				    bool clamp)
अणु
	काष्ठा arizona *arizona = info->arizona;
	अचिन्हित पूर्णांक mask = 0, val = 0;
	अचिन्हित पूर्णांक cap_sel = 0;
	पूर्णांक ret;

	चयन (arizona->type) अणु
	हाल WM8998:
	हाल WM1814:
		mask = 0;
		अवरोध;
	हाल WM5110:
	हाल WM8280:
		mask = ARIZONA_HP1L_SHRTO | ARIZONA_HP1L_FLWR |
		       ARIZONA_HP1L_SHRTI;
		अगर (clamp) अणु
			val = ARIZONA_HP1L_SHRTO;
			cap_sel = ARIZONA_TST_CAP_CLAMP;
		पूर्ण अन्यथा अणु
			val = ARIZONA_HP1L_FLWR | ARIZONA_HP1L_SHRTI;
			cap_sel = ARIZONA_TST_CAP_DEFAULT;
		पूर्ण

		ret = regmap_update_bits(arizona->regmap,
					 ARIZONA_HP_TEST_CTRL_1,
					 ARIZONA_HP1_TST_CAP_SEL_MASK,
					 cap_sel);
		अगर (ret)
			dev_warn(arizona->dev, "Failed to set TST_CAP_SEL: %d\n", ret);
		अवरोध;
	शेष:
		mask = ARIZONA_RMV_SHRT_HP1L;
		अगर (clamp)
			val = ARIZONA_RMV_SHRT_HP1L;
		अवरोध;
	पूर्ण

	snd_soc_dapm_mutex_lock(arizona->dapm);

	arizona->hpdet_clamp = clamp;

	/* Keep the HP output stages disabled जबतक करोing the clamp */
	अगर (clamp) अणु
		ret = regmap_update_bits(arizona->regmap,
					 ARIZONA_OUTPUT_ENABLES_1,
					 ARIZONA_OUT1L_ENA |
					 ARIZONA_OUT1R_ENA, 0);
		अगर (ret)
			dev_warn(arizona->dev, "Failed to disable headphone outputs: %d\n", ret);
	पूर्ण

	अगर (mask) अणु
		ret = regmap_update_bits(arizona->regmap, ARIZONA_HP_CTRL_1L,
					 mask, val);
		अगर (ret)
			dev_warn(arizona->dev, "Failed to do clamp: %d\n", ret);

		ret = regmap_update_bits(arizona->regmap, ARIZONA_HP_CTRL_1R,
					 mask, val);
		अगर (ret)
			dev_warn(arizona->dev, "Failed to do clamp: %d\n", ret);
	पूर्ण

	/* Restore the desired state जबतक not करोing the clamp */
	अगर (!clamp) अणु
		ret = regmap_update_bits(arizona->regmap,
					 ARIZONA_OUTPUT_ENABLES_1,
					 ARIZONA_OUT1L_ENA |
					 ARIZONA_OUT1R_ENA, arizona->hp_ena);
		अगर (ret)
			dev_warn(arizona->dev, "Failed to restore headphone outputs: %d\n", ret);
	पूर्ण

	snd_soc_dapm_mutex_unlock(arizona->dapm);
पूर्ण

अटल व्योम arizona_extcon_set_mode(काष्ठा arizona_priv *info, पूर्णांक mode)
अणु
	काष्ठा arizona *arizona = info->arizona;

	mode %= info->micd_num_modes;

	gpiod_set_value_cansleep(info->micd_pol_gpio,
				 info->micd_modes[mode].gpio);

	regmap_update_bits(arizona->regmap, ARIZONA_MIC_DETECT_1,
			   ARIZONA_MICD_BIAS_SRC_MASK,
			   info->micd_modes[mode].bias <<
			   ARIZONA_MICD_BIAS_SRC_SHIFT);
	regmap_update_bits(arizona->regmap, ARIZONA_ACCESSORY_DETECT_MODE_1,
			   ARIZONA_ACCDET_SRC, info->micd_modes[mode].src);

	info->micd_mode = mode;

	dev_dbg(arizona->dev, "Set jack polarity to %d\n", mode);
पूर्ण

अटल स्थिर अक्षर *arizona_extcon_get_micbias(काष्ठा arizona_priv *info)
अणु
	चयन (info->micd_modes[0].bias) अणु
	हाल 1:
		वापस "MICBIAS1";
	हाल 2:
		वापस "MICBIAS2";
	हाल 3:
		वापस "MICBIAS3";
	शेष:
		वापस "MICVDD";
	पूर्ण
पूर्ण

अटल व्योम arizona_extcon_pulse_micbias(काष्ठा arizona_priv *info)
अणु
	काष्ठा arizona *arizona = info->arizona;
	स्थिर अक्षर *widget = arizona_extcon_get_micbias(info);
	काष्ठा snd_soc_dapm_context *dapm = arizona->dapm;
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	पूर्णांक ret;

	ret = snd_soc_component_क्रमce_enable_pin(component, widget);
	अगर (ret)
		dev_warn(arizona->dev, "Failed to enable %s: %d\n", widget, ret);

	snd_soc_dapm_sync(dapm);

	अगर (!arizona->pdata.micd_क्रमce_micbias) अणु
		ret = snd_soc_component_disable_pin(component, widget);
		अगर (ret)
			dev_warn(arizona->dev, "Failed to disable %s: %d\n", widget, ret);

		snd_soc_dapm_sync(dapm);
	पूर्ण
पूर्ण

अटल व्योम arizona_start_mic(काष्ठा arizona_priv *info)
अणु
	काष्ठा arizona *arizona = info->arizona;
	bool change;
	पूर्णांक ret;
	अचिन्हित पूर्णांक mode;

	/* Microphone detection can't use idle mode */
	pm_runसमय_get_sync(arizona->dev);

	अगर (info->detecting) अणु
		ret = regulator_allow_bypass(info->micvdd, false);
		अगर (ret)
			dev_err(arizona->dev, "Failed to regulate MICVDD: %d\n", ret);
	पूर्ण

	ret = regulator_enable(info->micvdd);
	अगर (ret)
		dev_err(arizona->dev, "Failed to enable MICVDD: %d\n", ret);

	अगर (info->micd_reva) अणु
		स्थिर काष्ठा reg_sequence reva[] = अणु
			अणु 0x80,  0x3 पूर्ण,
			अणु 0x294, 0x0 पूर्ण,
			अणु 0x80,  0x0 पूर्ण,
		पूर्ण;

		regmap_multi_reg_ग_लिखो(arizona->regmap, reva, ARRAY_SIZE(reva));
	पूर्ण

	अगर (info->detecting && arizona->pdata.micd_software_compare)
		mode = ARIZONA_ACCDET_MODE_ADC;
	अन्यथा
		mode = ARIZONA_ACCDET_MODE_MIC;

	regmap_update_bits(arizona->regmap,
			   ARIZONA_ACCESSORY_DETECT_MODE_1,
			   ARIZONA_ACCDET_MODE_MASK, mode);

	arizona_extcon_pulse_micbias(info);

	ret = regmap_update_bits_check(arizona->regmap, ARIZONA_MIC_DETECT_1,
				       ARIZONA_MICD_ENA, ARIZONA_MICD_ENA,
				       &change);
	अगर (ret < 0) अणु
		dev_err(arizona->dev, "Failed to enable micd: %d\n", ret);
	पूर्ण अन्यथा अगर (!change) अणु
		regulator_disable(info->micvdd);
		pm_runसमय_put_स्वतःsuspend(arizona->dev);
	पूर्ण
पूर्ण

अटल व्योम arizona_stop_mic(काष्ठा arizona_priv *info)
अणु
	काष्ठा arizona *arizona = info->arizona;
	स्थिर अक्षर *widget = arizona_extcon_get_micbias(info);
	काष्ठा snd_soc_dapm_context *dapm = arizona->dapm;
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	bool change = false;
	पूर्णांक ret;

	ret = regmap_update_bits_check(arizona->regmap, ARIZONA_MIC_DETECT_1,
				       ARIZONA_MICD_ENA, 0,
				       &change);
	अगर (ret < 0)
		dev_err(arizona->dev, "Failed to disable micd: %d\n", ret);

	ret = snd_soc_component_disable_pin(component, widget);
	अगर (ret)
		dev_warn(arizona->dev, "Failed to disable %s: %d\n", widget, ret);

	snd_soc_dapm_sync(dapm);

	अगर (info->micd_reva) अणु
		स्थिर काष्ठा reg_sequence reva[] = अणु
			अणु 0x80,  0x3 पूर्ण,
			अणु 0x294, 0x2 पूर्ण,
			अणु 0x80,  0x0 पूर्ण,
		पूर्ण;

		regmap_multi_reg_ग_लिखो(arizona->regmap, reva, ARRAY_SIZE(reva));
	पूर्ण

	ret = regulator_allow_bypass(info->micvdd, true);
	अगर (ret)
		dev_err(arizona->dev, "Failed to bypass MICVDD: %d\n", ret);

	अगर (change) अणु
		regulator_disable(info->micvdd);
		pm_runसमय_mark_last_busy(arizona->dev);
		pm_runसमय_put_स्वतःsuspend(arizona->dev);
	पूर्ण
पूर्ण

अटल काष्ठा अणु
	अचिन्हित पूर्णांक threshold;
	अचिन्हित पूर्णांक factor_a;
	अचिन्हित पूर्णांक factor_b;
पूर्ण arizona_hpdet_b_ranges[] = अणु
	अणु 100,  5528,   362464 पूर्ण,
	अणु 169, 11084,  6186851 पूर्ण,
	अणु 169, 11065, 65460395 पूर्ण,
पूर्ण;

#घोषणा ARIZONA_HPDET_B_RANGE_MAX 0x3fb

अटल काष्ठा अणु
	पूर्णांक min;
	पूर्णांक max;
पूर्ण arizona_hpdet_c_ranges[] = अणु
	अणु 0,       30 पूर्ण,
	अणु 8,      100 पूर्ण,
	अणु 100,   1000 पूर्ण,
	अणु 1000, 10000 पूर्ण,
पूर्ण;

अटल पूर्णांक arizona_hpdet_पढ़ो(काष्ठा arizona_priv *info)
अणु
	काष्ठा arizona *arizona = info->arizona;
	अचिन्हित पूर्णांक val, range;
	पूर्णांक ret;

	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_HEADPHONE_DETECT_2, &val);
	अगर (ret) अणु
		dev_err(arizona->dev, "Failed to read HPDET status: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (info->hpdet_ip_version) अणु
	हाल 0:
		अगर (!(val & ARIZONA_HP_DONE)) अणु
			dev_err(arizona->dev, "HPDET did not complete: %x\n", val);
			वापस -EAGAIN;
		पूर्ण

		val &= ARIZONA_HP_LVL_MASK;
		अवरोध;

	हाल 1:
		अगर (!(val & ARIZONA_HP_DONE_B)) अणु
			dev_err(arizona->dev, "HPDET did not complete: %x\n", val);
			वापस -EAGAIN;
		पूर्ण

		ret = regmap_पढ़ो(arizona->regmap, ARIZONA_HP_DACVAL, &val);
		अगर (ret) अणु
			dev_err(arizona->dev, "Failed to read HP value: %d\n", ret);
			वापस -EAGAIN;
		पूर्ण

		regmap_पढ़ो(arizona->regmap, ARIZONA_HEADPHONE_DETECT_1,
			    &range);
		range = (range & ARIZONA_HP_IMPEDANCE_RANGE_MASK)
			   >> ARIZONA_HP_IMPEDANCE_RANGE_SHIFT;

		अगर (range < ARRAY_SIZE(arizona_hpdet_b_ranges) - 1 &&
		    (val < arizona_hpdet_b_ranges[range].threshold ||
		     val >= ARIZONA_HPDET_B_RANGE_MAX)) अणु
			range++;
			dev_dbg(arizona->dev, "Moving to HPDET range %d\n", range);
			regmap_update_bits(arizona->regmap,
					   ARIZONA_HEADPHONE_DETECT_1,
					   ARIZONA_HP_IMPEDANCE_RANGE_MASK,
					   range <<
					   ARIZONA_HP_IMPEDANCE_RANGE_SHIFT);
			वापस -EAGAIN;
		पूर्ण

		/* If we go out of range report top of range */
		अगर (val < arizona_hpdet_b_ranges[range].threshold ||
		    val >= ARIZONA_HPDET_B_RANGE_MAX) अणु
			dev_dbg(arizona->dev, "Measurement out of range\n");
			वापस ARIZONA_HPDET_MAX;
		पूर्ण

		dev_dbg(arizona->dev, "HPDET read %d in range %d\n", val, range);

		val = arizona_hpdet_b_ranges[range].factor_b
			/ ((val * 100) -
			   arizona_hpdet_b_ranges[range].factor_a);
		अवरोध;

	हाल 2:
		अगर (!(val & ARIZONA_HP_DONE_B)) अणु
			dev_err(arizona->dev, "HPDET did not complete: %x\n", val);
			वापस -EAGAIN;
		पूर्ण

		val &= ARIZONA_HP_LVL_B_MASK;
		/* Convert to ohms, the value is in 0.5 ohm increments */
		val /= 2;

		regmap_पढ़ो(arizona->regmap, ARIZONA_HEADPHONE_DETECT_1,
			    &range);
		range = (range & ARIZONA_HP_IMPEDANCE_RANGE_MASK)
			   >> ARIZONA_HP_IMPEDANCE_RANGE_SHIFT;

		/* Skip up a range, or report? */
		अगर (range < ARRAY_SIZE(arizona_hpdet_c_ranges) - 1 &&
		    (val >= arizona_hpdet_c_ranges[range].max)) अणु
			range++;
			dev_dbg(arizona->dev, "Moving to HPDET range %d-%d\n",
				arizona_hpdet_c_ranges[range].min,
				arizona_hpdet_c_ranges[range].max);
			regmap_update_bits(arizona->regmap,
					   ARIZONA_HEADPHONE_DETECT_1,
					   ARIZONA_HP_IMPEDANCE_RANGE_MASK,
					   range <<
					   ARIZONA_HP_IMPEDANCE_RANGE_SHIFT);
			वापस -EAGAIN;
		पूर्ण

		अगर (range && (val < arizona_hpdet_c_ranges[range].min)) अणु
			dev_dbg(arizona->dev, "Reporting range boundary %d\n",
				arizona_hpdet_c_ranges[range].min);
			val = arizona_hpdet_c_ranges[range].min;
		पूर्ण
		अवरोध;

	शेष:
		dev_warn(arizona->dev, "Unknown HPDET IP revision %d\n", info->hpdet_ip_version);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(arizona->dev, "HP impedance %d ohms\n", val);
	वापस val;
पूर्ण

अटल पूर्णांक arizona_hpdet_करो_id(काष्ठा arizona_priv *info, पूर्णांक *पढ़ोing,
			       bool *mic)
अणु
	काष्ठा arizona *arizona = info->arizona;
	पूर्णांक id_gpio = arizona->pdata.hpdet_id_gpio;

	अगर (!arizona->pdata.hpdet_acc_id)
		वापस 0;

	/*
	 * If we're using HPDET क्रम accessory identअगरication we need
	 * to take multiple measurements, step through them in sequence.
	 */
	info->hpdet_res[info->num_hpdet_res++] = *पढ़ोing;

	/* Only check the mic directly अगर we didn't alपढ़ोy ID it */
	अगर (id_gpio && info->num_hpdet_res == 1) अणु
		dev_dbg(arizona->dev, "Measuring mic\n");

		regmap_update_bits(arizona->regmap,
				   ARIZONA_ACCESSORY_DETECT_MODE_1,
				   ARIZONA_ACCDET_MODE_MASK |
				   ARIZONA_ACCDET_SRC,
				   ARIZONA_ACCDET_MODE_HPR |
				   info->micd_modes[0].src);

		gpio_set_value_cansleep(id_gpio, 1);

		regmap_update_bits(arizona->regmap, ARIZONA_HEADPHONE_DETECT_1,
				   ARIZONA_HP_POLL, ARIZONA_HP_POLL);
		वापस -EAGAIN;
	पूर्ण

	/* OK, got both.  Now, compare... */
	dev_dbg(arizona->dev, "HPDET measured %d %d\n",
		info->hpdet_res[0], info->hpdet_res[1]);

	/* Take the headphone impedance क्रम the मुख्य report */
	*पढ़ोing = info->hpdet_res[0];

	/* Someबार we get false पढ़ोings due to slow insert */
	अगर (*पढ़ोing >= ARIZONA_HPDET_MAX && !info->hpdet_retried) अणु
		dev_dbg(arizona->dev, "Retrying high impedance\n");
		info->num_hpdet_res = 0;
		info->hpdet_retried = true;
		arizona_start_hpdet_acc_id(info);
		pm_runसमय_put(arizona->dev);
		वापस -EAGAIN;
	पूर्ण

	/*
	 * If we measure the mic as high impedance
	 */
	अगर (!id_gpio || info->hpdet_res[1] > 50) अणु
		dev_dbg(arizona->dev, "Detected mic\n");
		*mic = true;
		info->detecting = true;
	पूर्ण अन्यथा अणु
		dev_dbg(arizona->dev, "Detected headphone\n");
	पूर्ण

	/* Make sure everything is reset back to the real polarity */
	regmap_update_bits(arizona->regmap, ARIZONA_ACCESSORY_DETECT_MODE_1,
			   ARIZONA_ACCDET_SRC, info->micd_modes[0].src);

	वापस 0;
पूर्ण

अटल irqवापस_t arizona_hpdet_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा arizona_priv *info = data;
	काष्ठा arizona *arizona = info->arizona;
	पूर्णांक id_gpio = arizona->pdata.hpdet_id_gpio;
	पूर्णांक ret, पढ़ोing, state, report;
	bool mic = false;

	mutex_lock(&info->lock);

	/* If we got a spurious IRQ क्रम some reason then ignore it */
	अगर (!info->hpdet_active) अणु
		dev_warn(arizona->dev, "Spurious HPDET IRQ\n");
		mutex_unlock(&info->lock);
		वापस IRQ_NONE;
	पूर्ण

	/* If the cable was हटाओd जबतक measuring ignore the result */
	state = info->jack->status & SND_JACK_MECHANICAL;
	अगर (!state) अणु
		dev_dbg(arizona->dev, "Ignoring HPDET for removed cable\n");
		जाओ करोne;
	पूर्ण

	ret = arizona_hpdet_पढ़ो(info);
	अगर (ret == -EAGAIN)
		जाओ out;
	अन्यथा अगर (ret < 0)
		जाओ करोne;
	पढ़ोing = ret;

	/* Reset back to starting range */
	regmap_update_bits(arizona->regmap,
			   ARIZONA_HEADPHONE_DETECT_1,
			   ARIZONA_HP_IMPEDANCE_RANGE_MASK | ARIZONA_HP_POLL,
			   0);

	ret = arizona_hpdet_करो_id(info, &पढ़ोing, &mic);
	अगर (ret == -EAGAIN)
		जाओ out;
	अन्यथा अगर (ret < 0)
		जाओ करोne;

	/* Report high impedence cables as line outमाला_दो */
	अगर (पढ़ोing >= 5000)
		report = SND_JACK_LINEOUT;
	अन्यथा
		report = SND_JACK_HEADPHONE;

	snd_soc_jack_report(info->jack, report, SND_JACK_LINEOUT | SND_JACK_HEADPHONE);

करोne:
	/* Reset back to starting range */
	regmap_update_bits(arizona->regmap,
			   ARIZONA_HEADPHONE_DETECT_1,
			   ARIZONA_HP_IMPEDANCE_RANGE_MASK | ARIZONA_HP_POLL,
			   0);

	arizona_extcon_hp_clamp(info, false);

	अगर (id_gpio)
		gpio_set_value_cansleep(id_gpio, 0);

	/* If we have a mic then reenable MICDET */
	अगर (state && (mic || info->mic))
		arizona_start_mic(info);

	अगर (info->hpdet_active) अणु
		pm_runसमय_put_स्वतःsuspend(arizona->dev);
		info->hpdet_active = false;
	पूर्ण

	/* Do not set hp_det करोne when the cable has been unplugged */
	अगर (state)
		info->hpdet_करोne = true;

out:
	mutex_unlock(&info->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम arizona_identअगरy_headphone(काष्ठा arizona_priv *info)
अणु
	काष्ठा arizona *arizona = info->arizona;
	पूर्णांक ret;

	अगर (info->hpdet_करोne)
		वापस;

	dev_dbg(arizona->dev, "Starting HPDET\n");

	/* Make sure we keep the device enabled during the measurement */
	pm_runसमय_get_sync(arizona->dev);

	info->hpdet_active = true;

	arizona_stop_mic(info);

	arizona_extcon_hp_clamp(info, true);

	ret = regmap_update_bits(arizona->regmap,
				 ARIZONA_ACCESSORY_DETECT_MODE_1,
				 ARIZONA_ACCDET_MODE_MASK,
				 arizona->pdata.hpdet_channel);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to set HPDET mode: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = regmap_update_bits(arizona->regmap, ARIZONA_HEADPHONE_DETECT_1,
				 ARIZONA_HP_POLL, ARIZONA_HP_POLL);
	अगर (ret) अणु
		dev_err(arizona->dev, "Can't start HPDETL measurement: %d\n", ret);
		जाओ err;
	पूर्ण

	वापस;

err:
	arizona_extcon_hp_clamp(info, false);
	pm_runसमय_put_स्वतःsuspend(arizona->dev);

	/* Just report headphone */
	snd_soc_jack_report(info->jack, SND_JACK_HEADPHONE,
			    SND_JACK_LINEOUT | SND_JACK_HEADPHONE);

	अगर (info->mic)
		arizona_start_mic(info);

	info->hpdet_active = false;
पूर्ण

अटल व्योम arizona_start_hpdet_acc_id(काष्ठा arizona_priv *info)
अणु
	काष्ठा arizona *arizona = info->arizona;
	पूर्णांक hp_पढ़ोing = 32;
	bool mic;
	पूर्णांक ret;

	dev_dbg(arizona->dev, "Starting identification via HPDET\n");

	/* Make sure we keep the device enabled during the measurement */
	pm_runसमय_get_sync(arizona->dev);

	info->hpdet_active = true;

	arizona_extcon_hp_clamp(info, true);

	ret = regmap_update_bits(arizona->regmap,
				 ARIZONA_ACCESSORY_DETECT_MODE_1,
				 ARIZONA_ACCDET_SRC | ARIZONA_ACCDET_MODE_MASK,
				 info->micd_modes[0].src |
				 arizona->pdata.hpdet_channel);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to set HPDET mode: %d\n", ret);
		जाओ err;
	पूर्ण

	अगर (arizona->pdata.hpdet_acc_id_line) अणु
		ret = regmap_update_bits(arizona->regmap,
					 ARIZONA_HEADPHONE_DETECT_1,
					 ARIZONA_HP_POLL, ARIZONA_HP_POLL);
		अगर (ret) अणु
			dev_err(arizona->dev, "Can't start HPDETL measurement: %d\n", ret);
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		arizona_hpdet_करो_id(info, &hp_पढ़ोing, &mic);
	पूर्ण

	वापस;

err:
	/* Just report headphone */
	snd_soc_jack_report(info->jack, SND_JACK_HEADPHONE,
			    SND_JACK_LINEOUT | SND_JACK_HEADPHONE);

	info->hpdet_active = false;
पूर्ण

अटल व्योम arizona_micd_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा arizona_priv *info = container_of(work,
						काष्ठा arizona_priv,
						micd_समयout_work.work);

	mutex_lock(&info->lock);

	dev_dbg(info->arizona->dev, "MICD timed out, reporting HP\n");

	info->detecting = false;

	arizona_identअगरy_headphone(info);

	mutex_unlock(&info->lock);
पूर्ण

अटल पूर्णांक arizona_micd_adc_पढ़ो(काष्ठा arizona_priv *info)
अणु
	काष्ठा arizona *arizona = info->arizona;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* Must disable MICD beक्रमe we पढ़ो the ADCVAL */
	regmap_update_bits(arizona->regmap, ARIZONA_MIC_DETECT_1,
			   ARIZONA_MICD_ENA, 0);

	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_MIC_DETECT_4, &val);
	अगर (ret) अणु
		dev_err(arizona->dev, "Failed to read MICDET_ADCVAL: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_dbg(arizona->dev, "MICDET_ADCVAL: %x\n", val);

	val &= ARIZONA_MICDET_ADCVAL_MASK;
	अगर (val < ARRAY_SIZE(arizona_micd_levels))
		val = arizona_micd_levels[val];
	अन्यथा
		val = पूर्णांक_उच्च;

	अगर (val <= QUICK_HEADPHONE_MAX_OHM)
		val = ARIZONA_MICD_STS | ARIZONA_MICD_LVL_0;
	अन्यथा अगर (val <= MICROPHONE_MIN_OHM)
		val = ARIZONA_MICD_STS | ARIZONA_MICD_LVL_1;
	अन्यथा अगर (val <= MICROPHONE_MAX_OHM)
		val = ARIZONA_MICD_STS | ARIZONA_MICD_LVL_8;
	अन्यथा
		val = ARIZONA_MICD_LVL_8;

	वापस val;
पूर्ण

अटल पूर्णांक arizona_micd_पढ़ो(काष्ठा arizona_priv *info)
अणु
	काष्ठा arizona *arizona = info->arizona;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret, i;

	क्रम (i = 0; i < 10 && !(val & MICD_LVL_0_TO_8); i++) अणु
		ret = regmap_पढ़ो(arizona->regmap, ARIZONA_MIC_DETECT_3, &val);
		अगर (ret) अणु
			dev_err(arizona->dev, "Failed to read MICDET: %d\n", ret);
			वापस ret;
		पूर्ण

		dev_dbg(arizona->dev, "MICDET: %x\n", val);

		अगर (!(val & ARIZONA_MICD_VALID)) अणु
			dev_warn(arizona->dev, "Microphone detection state invalid\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (i == 10 && !(val & MICD_LVL_0_TO_8)) अणु
		dev_err(arizona->dev, "Failed to get valid MICDET value\n");
		वापस -EINVAL;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक arizona_micdet_पढ़ोing(व्योम *priv)
अणु
	काष्ठा arizona_priv *info = priv;
	काष्ठा arizona *arizona = info->arizona;
	पूर्णांक ret, val;

	अगर (info->detecting && arizona->pdata.micd_software_compare)
		ret = arizona_micd_adc_पढ़ो(info);
	अन्यथा
		ret = arizona_micd_पढ़ो(info);
	अगर (ret < 0)
		वापस ret;

	val = ret;

	/* Due to jack detect this should never happen */
	अगर (!(val & ARIZONA_MICD_STS)) अणु
		dev_warn(arizona->dev, "Detected open circuit\n");
		info->mic = false;
		info->detecting = false;
		arizona_identअगरy_headphone(info);
		वापस 0;
	पूर्ण

	/* If we got a high impedence we should have a headset, report it. */
	अगर (val & ARIZONA_MICD_LVL_8) अणु
		info->mic = true;
		info->detecting = false;

		arizona_identअगरy_headphone(info);

		snd_soc_jack_report(info->jack, SND_JACK_MICROPHONE, SND_JACK_MICROPHONE);

		/* Don't need to regulate क्रम button detection */
		ret = regulator_allow_bypass(info->micvdd, true);
		अगर (ret)
			dev_err(arizona->dev, "Failed to bypass MICVDD: %d\n", ret);

		वापस 0;
	पूर्ण

	/* If we detected a lower impedence during initial startup
	 * then we probably have the wrong polarity, flip it.  Don't
	 * करो this क्रम the lowest impedences to speed up detection of
	 * plain headphones.  If both polarities report a low
	 * impedence then give up and report headphones.
	 */
	अगर (val & MICD_LVL_1_TO_7) अणु
		अगर (info->jack_flips >= info->micd_num_modes * 10) अणु
			dev_dbg(arizona->dev, "Detected HP/line\n");

			info->detecting = false;

			arizona_identअगरy_headphone(info);
		पूर्ण अन्यथा अणु
			info->micd_mode++;
			अगर (info->micd_mode == info->micd_num_modes)
				info->micd_mode = 0;
			arizona_extcon_set_mode(info, info->micd_mode);

			info->jack_flips++;

			अगर (arizona->pdata.micd_software_compare)
				regmap_update_bits(arizona->regmap,
						   ARIZONA_MIC_DETECT_1,
						   ARIZONA_MICD_ENA,
						   ARIZONA_MICD_ENA);

			queue_delayed_work(प्रणाली_घातer_efficient_wq,
					   &info->micd_समयout_work,
					   msecs_to_jअगरfies(arizona->pdata.micd_समयout));
		पूर्ण

		वापस 0;
	पूर्ण

	/*
	 * If we're still detecting and we detect a short then we've
	 * got a headphone.
	 */
	dev_dbg(arizona->dev, "Headphone detected\n");
	info->detecting = false;

	arizona_identअगरy_headphone(info);

	वापस 0;
पूर्ण

अटल पूर्णांक arizona_button_पढ़ोing(व्योम *priv)
अणु
	काष्ठा arizona_priv *info = priv;
	काष्ठा arizona *arizona = info->arizona;
	पूर्णांक val, key, lvl;

	val = arizona_micd_पढ़ो(info);
	अगर (val < 0)
		वापस val;

	/*
	 * If we're still detecting and we detect a short then we've
	 * got a headphone.  Otherwise it's a button press.
	 */
	अगर (val & MICD_LVL_0_TO_7) अणु
		अगर (info->mic) अणु
			dev_dbg(arizona->dev, "Mic button detected\n");

			lvl = val & ARIZONA_MICD_LVL_MASK;
			lvl >>= ARIZONA_MICD_LVL_SHIFT;

			अगर (lvl && ffs(lvl) - 1 < info->num_micd_ranges) अणु
				key = ffs(lvl) - 1;
				snd_soc_jack_report(info->jack,
						    SND_JACK_BTN_0 >> key,
						    info->micd_button_mask);
			पूर्ण अन्यथा अणु
				dev_err(arizona->dev, "Button out of range\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_warn(arizona->dev, "Button with no mic: %x\n", val);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(arizona->dev, "Mic button released\n");
		snd_soc_jack_report(info->jack, 0, info->micd_button_mask);
		arizona_extcon_pulse_micbias(info);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम arizona_micd_detect(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा arizona_priv *info = container_of(work,
						काष्ठा arizona_priv,
						micd_detect_work.work);
	काष्ठा arizona *arizona = info->arizona;

	cancel_delayed_work_sync(&info->micd_समयout_work);

	mutex_lock(&info->lock);

	/* If the cable was हटाओd जबतक measuring ignore the result */
	अगर (!(info->jack->status & SND_JACK_MECHANICAL)) अणु
		dev_dbg(arizona->dev, "Ignoring MICDET for removed cable\n");
		mutex_unlock(&info->lock);
		वापस;
	पूर्ण

	अगर (info->detecting)
		arizona_micdet_पढ़ोing(info);
	अन्यथा
		arizona_button_पढ़ोing(info);

	pm_runसमय_mark_last_busy(arizona->dev);
	mutex_unlock(&info->lock);
पूर्ण

अटल irqवापस_t arizona_micdet(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा arizona_priv *info = data;
	काष्ठा arizona *arizona = info->arizona;
	पूर्णांक debounce = arizona->pdata.micd_detect_debounce;

	cancel_delayed_work_sync(&info->micd_detect_work);
	cancel_delayed_work_sync(&info->micd_समयout_work);

	mutex_lock(&info->lock);
	अगर (!info->detecting)
		debounce = 0;
	mutex_unlock(&info->lock);

	अगर (debounce)
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &info->micd_detect_work,
				   msecs_to_jअगरfies(debounce));
	अन्यथा
		arizona_micd_detect(&info->micd_detect_work.work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम arizona_hpdet_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा arizona_priv *info = container_of(work,
						काष्ठा arizona_priv,
						hpdet_work.work);

	mutex_lock(&info->lock);
	arizona_start_hpdet_acc_id(info);
	mutex_unlock(&info->lock);
पूर्ण

अटल पूर्णांक arizona_hpdet_रुको(काष्ठा arizona_priv *info)
अणु
	काष्ठा arizona *arizona = info->arizona;
	अचिन्हित पूर्णांक val;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARIZONA_HPDET_WAIT_COUNT; i++) अणु
		ret = regmap_पढ़ो(arizona->regmap, ARIZONA_HEADPHONE_DETECT_2,
				&val);
		अगर (ret) अणु
			dev_err(arizona->dev, "Failed to read HPDET state: %d\n", ret);
			वापस ret;
		पूर्ण

		चयन (info->hpdet_ip_version) अणु
		हाल 0:
			अगर (val & ARIZONA_HP_DONE)
				वापस 0;
			अवरोध;
		शेष:
			अगर (val & ARIZONA_HP_DONE_B)
				वापस 0;
			अवरोध;
		पूर्ण

		msleep(ARIZONA_HPDET_WAIT_DELAY_MS);
	पूर्ण

	dev_warn(arizona->dev, "HPDET did not appear to complete\n");

	वापस -ETIMEDOUT;
पूर्ण

अटल irqवापस_t arizona_jackdet(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा arizona_priv *info = data;
	काष्ठा arizona *arizona = info->arizona;
	अचिन्हित पूर्णांक val, present, mask;
	bool cancelled_hp, cancelled_mic;
	पूर्णांक ret, i;

	cancelled_hp = cancel_delayed_work_sync(&info->hpdet_work);
	cancelled_mic = cancel_delayed_work_sync(&info->micd_समयout_work);

	pm_runसमय_get_sync(arizona->dev);

	mutex_lock(&info->lock);

	अगर (info->micd_clamp) अणु
		mask = ARIZONA_MICD_CLAMP_STS;
		present = 0;
	पूर्ण अन्यथा अणु
		mask = ARIZONA_JD1_STS;
		अगर (arizona->pdata.jd_invert)
			present = 0;
		अन्यथा
			present = ARIZONA_JD1_STS;
	पूर्ण

	ret = regmap_पढ़ो(arizona->regmap, ARIZONA_AOD_IRQ_RAW_STATUS, &val);
	अगर (ret) अणु
		dev_err(arizona->dev, "Failed to read jackdet status: %d\n", ret);
		mutex_unlock(&info->lock);
		pm_runसमय_put_स्वतःsuspend(arizona->dev);
		वापस IRQ_NONE;
	पूर्ण

	val &= mask;
	अगर (val == info->last_jackdet) अणु
		dev_dbg(arizona->dev, "Suppressing duplicate JACKDET\n");
		अगर (cancelled_hp)
			queue_delayed_work(प्रणाली_घातer_efficient_wq,
					   &info->hpdet_work,
					   msecs_to_jअगरfies(HPDET_DEBOUNCE));

		अगर (cancelled_mic) अणु
			पूर्णांक micd_समयout = arizona->pdata.micd_समयout;

			queue_delayed_work(प्रणाली_घातer_efficient_wq,
					   &info->micd_समयout_work,
					   msecs_to_jअगरfies(micd_समयout));
		पूर्ण

		जाओ out;
	पूर्ण
	info->last_jackdet = val;

	अगर (info->last_jackdet == present) अणु
		dev_dbg(arizona->dev, "Detected jack\n");
		snd_soc_jack_report(info->jack, SND_JACK_MECHANICAL, SND_JACK_MECHANICAL);

		info->detecting = true;
		info->mic = false;
		info->jack_flips = 0;

		अगर (!arizona->pdata.hpdet_acc_id) अणु
			arizona_start_mic(info);
		पूर्ण अन्यथा अणु
			queue_delayed_work(प्रणाली_घातer_efficient_wq,
					   &info->hpdet_work,
					   msecs_to_jअगरfies(HPDET_DEBOUNCE));
		पूर्ण

		अगर (info->micd_clamp || !arizona->pdata.jd_invert)
			regmap_update_bits(arizona->regmap,
					   ARIZONA_JACK_DETECT_DEBOUNCE,
					   ARIZONA_MICD_CLAMP_DB |
					   ARIZONA_JD1_DB, 0);
	पूर्ण अन्यथा अणु
		dev_dbg(arizona->dev, "Detected jack removal\n");

		arizona_stop_mic(info);

		info->num_hpdet_res = 0;
		क्रम (i = 0; i < ARRAY_SIZE(info->hpdet_res); i++)
			info->hpdet_res[i] = 0;
		info->mic = false;
		info->hpdet_करोne = false;
		info->hpdet_retried = false;

		snd_soc_jack_report(info->jack, 0, ARIZONA_JACK_MASK | info->micd_button_mask);

		/*
		 * If the jack was हटाओd during a headphone detection we
		 * need to रुको क्रम the headphone detection to finish, as
		 * it can not be पातed. We करोn't want to be able to start
		 * a new headphone detection from a fresh insert until this
		 * one is finished.
		 */
		arizona_hpdet_रुको(info);

		regmap_update_bits(arizona->regmap,
				   ARIZONA_JACK_DETECT_DEBOUNCE,
				   ARIZONA_MICD_CLAMP_DB | ARIZONA_JD1_DB,
				   ARIZONA_MICD_CLAMP_DB | ARIZONA_JD1_DB);
	पूर्ण

out:
	/* Clear trig_sts to make sure DCVDD is not क्रमced up */
	regmap_ग_लिखो(arizona->regmap, ARIZONA_AOD_WKUP_AND_TRIG,
		     ARIZONA_MICD_CLAMP_FALL_TRIG_STS |
		     ARIZONA_MICD_CLAMP_RISE_TRIG_STS |
		     ARIZONA_JD1_FALL_TRIG_STS |
		     ARIZONA_JD1_RISE_TRIG_STS);

	mutex_unlock(&info->lock);

	pm_runसमय_mark_last_busy(arizona->dev);
	pm_runसमय_put_स्वतःsuspend(arizona->dev);

	वापस IRQ_HANDLED;
पूर्ण

/* Map a level onto a slot in the रेजिस्टर bank */
अटल व्योम arizona_micd_set_level(काष्ठा arizona *arizona, पूर्णांक index,
				   अचिन्हित पूर्णांक level)
अणु
	पूर्णांक reg;
	अचिन्हित पूर्णांक mask;

	reg = ARIZONA_MIC_DETECT_LEVEL_4 - (index / 2);

	अगर (!(index % 2)) अणु
		mask = 0x3f00;
		level <<= 8;
	पूर्ण अन्यथा अणु
		mask = 0x3f;
	पूर्ण

	/* Program the level itself */
	regmap_update_bits(arizona->regmap, reg, mask, level);
पूर्ण

अटल पूर्णांक arizona_extcon_get_micd_configs(काष्ठा device *dev,
					   काष्ठा arizona *arizona)
अणु
	स्थिर अक्षर * स्थिर prop = "wlf,micd-configs";
	स्थिर पूर्णांक entries_per_config = 3;
	काष्ठा arizona_micd_config *micd_configs;
	पूर्णांक nconfs, ret;
	पूर्णांक i, j;
	u32 *vals;

	nconfs = device_property_count_u32(arizona->dev, prop);
	अगर (nconfs <= 0)
		वापस 0;

	vals = kसुस्मृति(nconfs, माप(u32), GFP_KERNEL);
	अगर (!vals)
		वापस -ENOMEM;

	ret = device_property_पढ़ो_u32_array(arizona->dev, prop, vals, nconfs);
	अगर (ret < 0)
		जाओ out;

	nconfs /= entries_per_config;
	micd_configs = devm_kसुस्मृति(dev, nconfs, माप(*micd_configs),
				    GFP_KERNEL);
	अगर (!micd_configs) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0, j = 0; i < nconfs; ++i) अणु
		micd_configs[i].src = vals[j++] ? ARIZONA_ACCDET_SRC : 0;
		micd_configs[i].bias = vals[j++];
		micd_configs[i].gpio = vals[j++];
	पूर्ण

	arizona->pdata.micd_configs = micd_configs;
	arizona->pdata.num_micd_configs = nconfs;

out:
	kमुक्त(vals);
	वापस ret;
पूर्ण

अटल पूर्णांक arizona_extcon_device_get_pdata(काष्ठा device *dev,
					   काष्ठा arizona *arizona)
अणु
	काष्ठा arizona_pdata *pdata = &arizona->pdata;
	अचिन्हित पूर्णांक val = ARIZONA_ACCDET_MODE_HPL;
	पूर्णांक ret;

	device_property_पढ़ो_u32(arizona->dev, "wlf,hpdet-channel", &val);
	चयन (val) अणु
	हाल ARIZONA_ACCDET_MODE_HPL:
	हाल ARIZONA_ACCDET_MODE_HPR:
		pdata->hpdet_channel = val;
		अवरोध;
	शेष:
		dev_err(arizona->dev, "Wrong wlf,hpdet-channel DT value %d\n", val);
		pdata->hpdet_channel = ARIZONA_ACCDET_MODE_HPL;
	पूर्ण

	device_property_पढ़ो_u32(arizona->dev, "wlf,micd-detect-debounce",
				 &pdata->micd_detect_debounce);

	device_property_पढ़ो_u32(arizona->dev, "wlf,micd-bias-start-time",
				 &pdata->micd_bias_start_समय);

	device_property_पढ़ो_u32(arizona->dev, "wlf,micd-rate",
				 &pdata->micd_rate);

	device_property_पढ़ो_u32(arizona->dev, "wlf,micd-dbtime",
				 &pdata->micd_dbसमय);

	device_property_पढ़ो_u32(arizona->dev, "wlf,micd-timeout-ms",
				 &pdata->micd_समयout);

	pdata->micd_क्रमce_micbias = device_property_पढ़ो_bool(arizona->dev,
						"wlf,micd-force-micbias");

	pdata->micd_software_compare = device_property_पढ़ो_bool(arizona->dev,
						"wlf,micd-software-compare");

	pdata->jd_invert = device_property_पढ़ो_bool(arizona->dev,
						     "wlf,jd-invert");

	device_property_पढ़ो_u32(arizona->dev, "wlf,gpsw", &pdata->gpsw);

	pdata->jd_gpio5 = device_property_पढ़ो_bool(arizona->dev,
						    "wlf,use-jd2");
	pdata->jd_gpio5_nopull = device_property_पढ़ो_bool(arizona->dev,
						"wlf,use-jd2-nopull");

	ret = arizona_extcon_get_micd_configs(dev, arizona);
	अगर (ret < 0)
		dev_err(arizona->dev, "Failed to read micd configs: %d\n", ret);

	वापस 0;
पूर्ण

पूर्णांक arizona_jack_codec_dev_probe(काष्ठा arizona_priv *info, काष्ठा device *dev)
अणु
	काष्ठा arizona *arizona = info->arizona;
	काष्ठा arizona_pdata *pdata = &arizona->pdata;
	पूर्णांक ret, mode;

	अगर (!dev_get_platdata(arizona->dev))
		arizona_extcon_device_get_pdata(dev, arizona);

	info->micvdd = devm_regulator_get(dev, "MICVDD");
	अगर (IS_ERR(info->micvdd))
		वापस dev_err_probe(arizona->dev, PTR_ERR(info->micvdd), "getting MICVDD\n");

	mutex_init(&info->lock);
	info->last_jackdet = ~(ARIZONA_MICD_CLAMP_STS | ARIZONA_JD1_STS);
	INIT_DELAYED_WORK(&info->hpdet_work, arizona_hpdet_work);
	INIT_DELAYED_WORK(&info->micd_detect_work, arizona_micd_detect);
	INIT_DELAYED_WORK(&info->micd_समयout_work, arizona_micd_समयout_work);

	चयन (arizona->type) अणु
	हाल WM5102:
		चयन (arizona->rev) अणु
		हाल 0:
			info->micd_reva = true;
			अवरोध;
		शेष:
			info->micd_clamp = true;
			info->hpdet_ip_version = 1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल WM5110:
	हाल WM8280:
		चयन (arizona->rev) अणु
		हाल 0 ... 2:
			अवरोध;
		शेष:
			info->micd_clamp = true;
			info->hpdet_ip_version = 2;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल WM8998:
	हाल WM1814:
		info->micd_clamp = true;
		info->hpdet_ip_version = 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!pdata->micd_समयout)
		pdata->micd_समयout = DEFAULT_MICD_TIMEOUT;

	अगर (pdata->num_micd_configs) अणु
		info->micd_modes = pdata->micd_configs;
		info->micd_num_modes = pdata->num_micd_configs;
	पूर्ण अन्यथा अणु
		info->micd_modes = micd_शेष_modes;
		info->micd_num_modes = ARRAY_SIZE(micd_शेष_modes);
	पूर्ण

	अगर (arizona->pdata.gpsw > 0)
		regmap_update_bits(arizona->regmap, ARIZONA_GP_SWITCH_1,
				ARIZONA_SW1_MODE_MASK, arizona->pdata.gpsw);

	अगर (pdata->micd_pol_gpio > 0) अणु
		अगर (info->micd_modes[0].gpio)
			mode = GPIOF_OUT_INIT_HIGH;
		अन्यथा
			mode = GPIOF_OUT_INIT_LOW;

		ret = devm_gpio_request_one(dev, pdata->micd_pol_gpio,
					    mode, "MICD polarity");
		अगर (ret != 0) अणु
			dev_err(arizona->dev, "Failed to request GPIO%d: %d\n",
				pdata->micd_pol_gpio, ret);
			वापस ret;
		पूर्ण

		info->micd_pol_gpio = gpio_to_desc(pdata->micd_pol_gpio);
	पूर्ण अन्यथा अणु
		अगर (info->micd_modes[0].gpio)
			mode = GPIOD_OUT_HIGH;
		अन्यथा
			mode = GPIOD_OUT_LOW;

		/* We can't use devm here because we need to करो the get
		 * against the MFD device, as that is where the of_node
		 * will reside, but अगर we devm against that the GPIO
		 * will not be मुक्तd अगर the extcon driver is unloaded.
		 */
		info->micd_pol_gpio = gpiod_get_optional(arizona->dev,
							 "wlf,micd-pol",
							 mode);
		अगर (IS_ERR(info->micd_pol_gpio)) अणु
			ret = PTR_ERR(info->micd_pol_gpio);
			dev_err_probe(arizona->dev, ret, "getting microphone polarity GPIO\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (arizona->pdata.hpdet_id_gpio > 0) अणु
		ret = devm_gpio_request_one(dev, arizona->pdata.hpdet_id_gpio,
					    GPIOF_OUT_INIT_LOW,
					    "HPDET");
		अगर (ret != 0) अणु
			dev_err(arizona->dev, "Failed to request GPIO%d: %d\n",
				arizona->pdata.hpdet_id_gpio, ret);
			gpiod_put(info->micd_pol_gpio);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_jack_codec_dev_probe);

पूर्णांक arizona_jack_codec_dev_हटाओ(काष्ठा arizona_priv *info)
अणु
	gpiod_put(info->micd_pol_gpio);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arizona_jack_codec_dev_हटाओ);

अटल पूर्णांक arizona_jack_enable_jack_detect(काष्ठा arizona_priv *info,
					   काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा arizona *arizona = info->arizona;
	काष्ठा arizona_pdata *pdata = &arizona->pdata;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक clamp_mode;
	पूर्णांक jack_irq_fall, jack_irq_rise;
	पूर्णांक ret, i, j;

	अगर (arizona->pdata.micd_bias_start_समय)
		regmap_update_bits(arizona->regmap, ARIZONA_MIC_DETECT_1,
				   ARIZONA_MICD_BIAS_STARTTIME_MASK,
				   arizona->pdata.micd_bias_start_समय
				   << ARIZONA_MICD_BIAS_STARTTIME_SHIFT);

	अगर (arizona->pdata.micd_rate)
		regmap_update_bits(arizona->regmap, ARIZONA_MIC_DETECT_1,
				   ARIZONA_MICD_RATE_MASK,
				   arizona->pdata.micd_rate
				   << ARIZONA_MICD_RATE_SHIFT);

	चयन (arizona->pdata.micd_dbसमय) अणु
	हाल MICD_DBTIME_FOUR_READINGS:
		regmap_update_bits(arizona->regmap, ARIZONA_MIC_DETECT_1,
				   ARIZONA_MICD_DBTIME_MASK,
				   ARIZONA_MICD_DBTIME);
		अवरोध;
	हाल MICD_DBTIME_TWO_READINGS:
		regmap_update_bits(arizona->regmap, ARIZONA_MIC_DETECT_1,
				   ARIZONA_MICD_DBTIME_MASK, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	BUILD_BUG_ON(ARRAY_SIZE(arizona_micd_levels) <
		     ARIZONA_NUM_MICD_BUTTON_LEVELS);

	अगर (arizona->pdata.num_micd_ranges) अणु
		info->micd_ranges = pdata->micd_ranges;
		info->num_micd_ranges = pdata->num_micd_ranges;
	पूर्ण अन्यथा अणु
		info->micd_ranges = micd_शेष_ranges;
		info->num_micd_ranges = ARRAY_SIZE(micd_शेष_ranges);
	पूर्ण

	अगर (arizona->pdata.num_micd_ranges > ARIZONA_MAX_MICD_BUTTONS) अणु
		dev_err(arizona->dev, "Too many MICD ranges: %d > %d\n",
			arizona->pdata.num_micd_ranges, ARIZONA_MAX_MICD_BUTTONS);
		वापस -EINVAL;
	पूर्ण

	अगर (info->num_micd_ranges > 1) अणु
		क्रम (i = 1; i < info->num_micd_ranges; i++) अणु
			अगर (info->micd_ranges[i - 1].max >
			    info->micd_ranges[i].max) अणु
				dev_err(arizona->dev, "MICD ranges must be sorted\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Disable all buttons by शेष */
	regmap_update_bits(arizona->regmap, ARIZONA_MIC_DETECT_2,
			   ARIZONA_MICD_LVL_SEL_MASK, 0x81);

	/* Set up all the buttons the user specअगरied */
	क्रम (i = 0; i < info->num_micd_ranges; i++) अणु
		क्रम (j = 0; j < ARIZONA_NUM_MICD_BUTTON_LEVELS; j++)
			अगर (arizona_micd_levels[j] >= info->micd_ranges[i].max)
				अवरोध;

		अगर (j == ARIZONA_NUM_MICD_BUTTON_LEVELS) अणु
			dev_err(arizona->dev, "Unsupported MICD level %d\n",
				info->micd_ranges[i].max);
			वापस -EINVAL;
		पूर्ण

		dev_dbg(arizona->dev, "%d ohms for MICD threshold %d\n",
			arizona_micd_levels[j], i);

		arizona_micd_set_level(arizona, i, j);

		/* SND_JACK_BTN_# masks start with the most signअगरicant bit */
		info->micd_button_mask |= SND_JACK_BTN_0 >> i;
		snd_jack_set_key(jack->jack, SND_JACK_BTN_0 >> i,
				 info->micd_ranges[i].key);

		/* Enable reporting of that range */
		regmap_update_bits(arizona->regmap, ARIZONA_MIC_DETECT_2,
				   1 << i, 1 << i);
	पूर्ण

	/* Set all the reमुख्यing keys to a maximum */
	क्रम (; i < ARIZONA_MAX_MICD_RANGE; i++)
		arizona_micd_set_level(arizona, i, 0x3f);

	/*
	 * If we have a clamp use it, activating in conjunction with
	 * GPIO5 अगर that is connected क्रम jack detect operation.
	 */
	अगर (info->micd_clamp) अणु
		अगर (arizona->pdata.jd_gpio5) अणु
			/* Put the GPIO पूर्णांकo input mode with optional pull */
			val = 0xc101;
			अगर (arizona->pdata.jd_gpio5_nopull)
				val &= ~ARIZONA_GPN_PU;

			regmap_ग_लिखो(arizona->regmap, ARIZONA_GPIO5_CTRL,
				     val);

			अगर (arizona->pdata.jd_invert)
				clamp_mode = ARIZONA_MICD_CLAMP_MODE_JDH_GP5H;
			अन्यथा
				clamp_mode = ARIZONA_MICD_CLAMP_MODE_JDL_GP5H;
		पूर्ण अन्यथा अणु
			अगर (arizona->pdata.jd_invert)
				clamp_mode = ARIZONA_MICD_CLAMP_MODE_JDH;
			अन्यथा
				clamp_mode = ARIZONA_MICD_CLAMP_MODE_JDL;
		पूर्ण

		regmap_update_bits(arizona->regmap,
				   ARIZONA_MICD_CLAMP_CONTROL,
				   ARIZONA_MICD_CLAMP_MODE_MASK, clamp_mode);

		regmap_update_bits(arizona->regmap,
				   ARIZONA_JACK_DETECT_DEBOUNCE,
				   ARIZONA_MICD_CLAMP_DB,
				   ARIZONA_MICD_CLAMP_DB);
	पूर्ण

	arizona_extcon_set_mode(info, 0);

	info->jack = jack;

	pm_runसमय_get_sync(arizona->dev);

	अगर (info->micd_clamp) अणु
		jack_irq_rise = ARIZONA_IRQ_MICD_CLAMP_RISE;
		jack_irq_fall = ARIZONA_IRQ_MICD_CLAMP_FALL;
	पूर्ण अन्यथा अणु
		jack_irq_rise = ARIZONA_IRQ_JD_RISE;
		jack_irq_fall = ARIZONA_IRQ_JD_FALL;
	पूर्ण

	ret = arizona_request_irq(arizona, jack_irq_rise,
				  "JACKDET rise", arizona_jackdet, info);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to get JACKDET rise IRQ: %d\n", ret);
		जाओ err_pm;
	पूर्ण

	ret = arizona_set_irq_wake(arizona, jack_irq_rise, 1);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to set JD rise IRQ wake: %d\n", ret);
		जाओ err_rise;
	पूर्ण

	ret = arizona_request_irq(arizona, jack_irq_fall,
				  "JACKDET fall", arizona_jackdet, info);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to get JD fall IRQ: %d\n", ret);
		जाओ err_rise_wake;
	पूर्ण

	ret = arizona_set_irq_wake(arizona, jack_irq_fall, 1);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to set JD fall IRQ wake: %d\n", ret);
		जाओ err_fall;
	पूर्ण

	ret = arizona_request_irq(arizona, ARIZONA_IRQ_MICDET,
				  "MICDET", arizona_micdet, info);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to get MICDET IRQ: %d\n", ret);
		जाओ err_fall_wake;
	पूर्ण

	ret = arizona_request_irq(arizona, ARIZONA_IRQ_HPDET,
				  "HPDET", arizona_hpdet_irq, info);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to get HPDET IRQ: %d\n", ret);
		जाओ err_micdet;
	पूर्ण

	arizona_clk32k_enable(arizona);
	regmap_update_bits(arizona->regmap, ARIZONA_JACK_DETECT_DEBOUNCE,
			   ARIZONA_JD1_DB, ARIZONA_JD1_DB);
	regmap_update_bits(arizona->regmap, ARIZONA_JACK_DETECT_ANALOGUE,
			   ARIZONA_JD1_ENA, ARIZONA_JD1_ENA);

	ret = regulator_allow_bypass(info->micvdd, true);
	अगर (ret != 0)
		dev_warn(arizona->dev, "Failed to set MICVDD to bypass: %d\n", ret);

	pm_runसमय_put(arizona->dev);

	वापस 0;

err_micdet:
	arizona_मुक्त_irq(arizona, ARIZONA_IRQ_MICDET, info);
err_fall_wake:
	arizona_set_irq_wake(arizona, jack_irq_fall, 0);
err_fall:
	arizona_मुक्त_irq(arizona, jack_irq_fall, info);
err_rise_wake:
	arizona_set_irq_wake(arizona, jack_irq_rise, 0);
err_rise:
	arizona_मुक्त_irq(arizona, jack_irq_rise, info);
err_pm:
	pm_runसमय_put(arizona->dev);
	info->jack = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक arizona_jack_disable_jack_detect(काष्ठा arizona_priv *info)
अणु
	काष्ठा arizona *arizona = info->arizona;
	पूर्णांक jack_irq_rise, jack_irq_fall;
	bool change;
	पूर्णांक ret;

	अगर (!info->jack)
		वापस 0;

	अगर (info->micd_clamp) अणु
		jack_irq_rise = ARIZONA_IRQ_MICD_CLAMP_RISE;
		jack_irq_fall = ARIZONA_IRQ_MICD_CLAMP_FALL;
	पूर्ण अन्यथा अणु
		jack_irq_rise = ARIZONA_IRQ_JD_RISE;
		jack_irq_fall = ARIZONA_IRQ_JD_FALL;
	पूर्ण

	arizona_set_irq_wake(arizona, jack_irq_rise, 0);
	arizona_set_irq_wake(arizona, jack_irq_fall, 0);
	arizona_मुक्त_irq(arizona, ARIZONA_IRQ_HPDET, info);
	arizona_मुक्त_irq(arizona, ARIZONA_IRQ_MICDET, info);
	arizona_मुक्त_irq(arizona, jack_irq_rise, info);
	arizona_मुक्त_irq(arizona, jack_irq_fall, info);
	cancel_delayed_work_sync(&info->hpdet_work);
	cancel_delayed_work_sync(&info->micd_detect_work);
	cancel_delayed_work_sync(&info->micd_समयout_work);

	ret = regmap_update_bits_check(arizona->regmap, ARIZONA_MIC_DETECT_1,
				       ARIZONA_MICD_ENA, 0,
				       &change);
	अगर (ret < 0) अणु
		dev_err(arizona->dev, "Failed to disable micd on remove: %d\n", ret);
	पूर्ण अन्यथा अगर (change) अणु
		regulator_disable(info->micvdd);
		pm_runसमय_put(arizona->dev);
	पूर्ण

	regmap_update_bits(arizona->regmap,
			   ARIZONA_MICD_CLAMP_CONTROL,
			   ARIZONA_MICD_CLAMP_MODE_MASK, 0);
	regmap_update_bits(arizona->regmap, ARIZONA_JACK_DETECT_ANALOGUE,
			   ARIZONA_JD1_ENA, 0);
	arizona_clk32k_disable(arizona);
	info->jack = शून्य;

	वापस 0;
पूर्ण

पूर्णांक arizona_jack_set_jack(काष्ठा snd_soc_component *component,
			  काष्ठा snd_soc_jack *jack, व्योम *data)
अणु
	काष्ठा arizona_priv *info = snd_soc_component_get_drvdata(component);

	अगर (jack)
		वापस arizona_jack_enable_jack_detect(info, jack);
	अन्यथा
		वापस arizona_jack_disable_jack_detect(info);
पूर्ण
EXPORT_SYMBOL_GPL(arizona_jack_set_jack);
