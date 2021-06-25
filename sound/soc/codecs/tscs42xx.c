<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// tscs42xx.c -- TSCS42xx ALSA SoC Audio driver
// Copyright 2017 Tempo Semiconductor, Inc.
// Author: Steven Eckhoff <steven.eckhoff.खोलोsource@gmail.com>

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/clk.h>
#समावेश <sound/tlv.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>

#समावेश "tscs42xx.h"

#घोषणा COEFF_SIZE 3
#घोषणा BIQUAD_COEFF_COUNT 5
#घोषणा BIQUAD_SIZE (COEFF_SIZE * BIQUAD_COEFF_COUNT)

#घोषणा COEFF_RAM_MAX_ADDR 0xcd
#घोषणा COEFF_RAM_COEFF_COUNT (COEFF_RAM_MAX_ADDR + 1)
#घोषणा COEFF_RAM_SIZE (COEFF_SIZE * COEFF_RAM_COEFF_COUNT)

काष्ठा tscs42xx अणु

	पूर्णांक bclk_ratio;
	पूर्णांक samplerate;
	काष्ठा mutex audio_params_lock;

	u8 coeff_ram[COEFF_RAM_SIZE];
	bool coeff_ram_synced;
	काष्ठा mutex coeff_ram_lock;

	काष्ठा mutex pll_lock;

	काष्ठा regmap *regmap;

	काष्ठा clk *sysclk;
	पूर्णांक sysclk_src_id;
पूर्ण;

काष्ठा coeff_ram_ctl अणु
	अचिन्हित पूर्णांक addr;
	काष्ठा soc_bytes_ext bytes_ext;
पूर्ण;

अटल bool tscs42xx_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल R_DACCRWRL:
	हाल R_DACCRWRM:
	हाल R_DACCRWRH:
	हाल R_DACCRRDL:
	हाल R_DACCRRDM:
	हाल R_DACCRRDH:
	हाल R_DACCRSTAT:
	हाल R_DACCRADDR:
	हाल R_PLLCTL0:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tscs42xx_precious(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल R_DACCRWRL:
	हाल R_DACCRWRM:
	हाल R_DACCRWRH:
	हाल R_DACCRRDL:
	हाल R_DACCRRDM:
	हाल R_DACCRRDH:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tscs42xx_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.अस्थिर_reg = tscs42xx_अस्थिर,
	.precious_reg = tscs42xx_precious,
	.max_रेजिस्टर = R_DACMBCREL3H,

	.cache_type = REGCACHE_RBTREE,
	.can_multi_ग_लिखो = true,
पूर्ण;

#घोषणा MAX_PLL_LOCK_20MS_WAITS 1
अटल bool plls_locked(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;
	पूर्णांक count = MAX_PLL_LOCK_20MS_WAITS;

	करो अणु
		ret = snd_soc_component_पढ़ो(component, R_PLLCTL0);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"Failed to read PLL lock status (%d)\n", ret);
			वापस false;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			वापस true;
		पूर्ण
		msleep(20);
	पूर्ण जबतक (count--);

	वापस false;
पूर्ण

अटल पूर्णांक sample_rate_to_pll_freq_out(पूर्णांक sample_rate)
अणु
	चयन (sample_rate) अणु
	हाल 11025:
	हाल 22050:
	हाल 44100:
	हाल 88200:
		वापस 112896000;
	हाल 8000:
	हाल 16000:
	हाल 32000:
	हाल 48000:
	हाल 96000:
		वापस 122880000;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा DACCRSTAT_MAX_TRYS 10
अटल पूर्णांक ग_लिखो_coeff_ram(काष्ठा snd_soc_component *component, u8 *coeff_ram,
	अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक coeff_cnt)
अणु
	काष्ठा tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	पूर्णांक cnt;
	पूर्णांक trys;
	पूर्णांक ret;

	क्रम (cnt = 0; cnt < coeff_cnt; cnt++, addr++) अणु

		क्रम (trys = 0; trys < DACCRSTAT_MAX_TRYS; trys++) अणु
			ret = snd_soc_component_पढ़ो(component, R_DACCRSTAT);
			अगर (ret < 0) अणु
				dev_err(component->dev,
					"Failed to read stat (%d)\n", ret);
				वापस ret;
			पूर्ण
			अगर (!ret)
				अवरोध;
		पूर्ण

		अगर (trys == DACCRSTAT_MAX_TRYS) अणु
			ret = -EIO;
			dev_err(component->dev,
				"dac coefficient write error (%d)\n", ret);
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(tscs42xx->regmap, R_DACCRADDR, addr);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"Failed to write dac ram address (%d)\n", ret);
			वापस ret;
		पूर्ण

		ret = regmap_bulk_ग_लिखो(tscs42xx->regmap, R_DACCRWRL,
			&coeff_ram[addr * COEFF_SIZE],
			COEFF_SIZE);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"Failed to write dac ram (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक घातer_up_audio_plls(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	पूर्णांक freq_out;
	पूर्णांक ret;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;

	freq_out = sample_rate_to_pll_freq_out(tscs42xx->samplerate);
	चयन (freq_out) अणु
	हाल 122880000: /* 48k */
		mask = RM_PLLCTL1C_PDB_PLL1;
		val = RV_PLLCTL1C_PDB_PLL1_ENABLE;
		अवरोध;
	हाल 112896000: /* 44.1k */
		mask = RM_PLLCTL1C_PDB_PLL2;
		val = RV_PLLCTL1C_PDB_PLL2_ENABLE;
		अवरोध;
	शेष:
		ret = -EINVAL;
		dev_err(component->dev,
				"Unrecognized PLL output freq (%d)\n", ret);
		वापस ret;
	पूर्ण

	mutex_lock(&tscs42xx->pll_lock);

	ret = snd_soc_component_update_bits(component, R_PLLCTL1C, mask, val);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to turn PLL on (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	अगर (!plls_locked(component)) अणु
		dev_err(component->dev, "Failed to lock plls\n");
		ret = -ENOMSG;
		जाओ निकास;
	पूर्ण

	ret = 0;
निकास:
	mutex_unlock(&tscs42xx->pll_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक घातer_करोwn_audio_plls(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	mutex_lock(&tscs42xx->pll_lock);

	ret = snd_soc_component_update_bits(component, R_PLLCTL1C,
			RM_PLLCTL1C_PDB_PLL1,
			RV_PLLCTL1C_PDB_PLL1_DISABLE);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to turn PLL off (%d)\n", ret);
		जाओ निकास;
	पूर्ण
	ret = snd_soc_component_update_bits(component, R_PLLCTL1C,
			RM_PLLCTL1C_PDB_PLL2,
			RV_PLLCTL1C_PDB_PLL2_DISABLE);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to turn PLL off (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	ret = 0;
निकास:
	mutex_unlock(&tscs42xx->pll_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक coeff_ram_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	काष्ठा coeff_ram_ctl *ctl =
		(काष्ठा coeff_ram_ctl *)kcontrol->निजी_value;
	काष्ठा soc_bytes_ext *params = &ctl->bytes_ext;

	mutex_lock(&tscs42xx->coeff_ram_lock);

	स_नकल(ucontrol->value.bytes.data,
		&tscs42xx->coeff_ram[ctl->addr * COEFF_SIZE], params->max);

	mutex_unlock(&tscs42xx->coeff_ram_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक coeff_ram_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	काष्ठा coeff_ram_ctl *ctl =
		(काष्ठा coeff_ram_ctl *)kcontrol->निजी_value;
	काष्ठा soc_bytes_ext *params = &ctl->bytes_ext;
	अचिन्हित पूर्णांक coeff_cnt = params->max / COEFF_SIZE;
	पूर्णांक ret;

	mutex_lock(&tscs42xx->coeff_ram_lock);

	tscs42xx->coeff_ram_synced = false;

	स_नकल(&tscs42xx->coeff_ram[ctl->addr * COEFF_SIZE],
		ucontrol->value.bytes.data, params->max);

	mutex_lock(&tscs42xx->pll_lock);

	अगर (plls_locked(component)) अणु
		ret = ग_लिखो_coeff_ram(component, tscs42xx->coeff_ram,
			ctl->addr, coeff_cnt);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"Failed to flush coeff ram cache (%d)\n", ret);
			जाओ निकास;
		पूर्ण
		tscs42xx->coeff_ram_synced = true;
	पूर्ण

	ret = 0;
निकास:
	mutex_unlock(&tscs42xx->pll_lock);

	mutex_unlock(&tscs42xx->coeff_ram_lock);

	वापस ret;
पूर्ण

/* Input L Capture Route */
अटल अक्षर स्थिर * स्थिर input_select_text[] = अणु
	"Line 1", "Line 2", "Line 3", "D2S"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत left_input_select_क्रमागत =
SOC_ENUM_SINGLE(R_INSELL, FB_INSELL, ARRAY_SIZE(input_select_text),
		input_select_text);

अटल स्थिर काष्ठा snd_kcontrol_new left_input_select =
SOC_DAPM_ENUM("LEFT_INPUT_SELECT_ENUM", left_input_select_क्रमागत);

/* Input R Capture Route */
अटल स्थिर काष्ठा soc_क्रमागत right_input_select_क्रमागत =
SOC_ENUM_SINGLE(R_INSELR, FB_INSELR, ARRAY_SIZE(input_select_text),
		input_select_text);

अटल स्थिर काष्ठा snd_kcontrol_new right_input_select =
SOC_DAPM_ENUM("RIGHT_INPUT_SELECT_ENUM", right_input_select_क्रमागत);

/* Input Channel Mapping */
अटल अक्षर स्थिर * स्थिर ch_map_select_text[] = अणु
	"Normal", "Left to Right", "Right to Left", "Swap"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत ch_map_select_क्रमागत =
SOC_ENUM_SINGLE(R_AIC2, FB_AIC2_ADCDSEL, ARRAY_SIZE(ch_map_select_text),
		ch_map_select_text);

अटल पूर्णांक dapm_vref_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	msleep(20);
	वापस 0;
पूर्ण

अटल पूर्णांक dapm_micb_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	msleep(20);
	वापस 0;
पूर्ण

अटल पूर्णांक pll_event(काष्ठा snd_soc_dapm_widget *w,
		     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	पूर्णांक ret;

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		ret = घातer_up_audio_plls(component);
	अन्यथा
		ret = घातer_करोwn_audio_plls(component);

	वापस ret;
पूर्ण

अटल पूर्णांक dac_event(काष्ठा snd_soc_dapm_widget *w,
		     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	mutex_lock(&tscs42xx->coeff_ram_lock);

	अगर (!tscs42xx->coeff_ram_synced) अणु
		ret = ग_लिखो_coeff_ram(component, tscs42xx->coeff_ram, 0x00,
			COEFF_RAM_COEFF_COUNT);
		अगर (ret < 0)
			जाओ निकास;
		tscs42xx->coeff_ram_synced = true;
	पूर्ण

	ret = 0;
निकास:
	mutex_unlock(&tscs42xx->coeff_ram_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget tscs42xx_dapm_widमाला_लो[] = अणु
	/* Vref */
	SND_SOC_DAPM_SUPPLY_S("Vref", 1, R_PWRM2, FB_PWRM2_VREF, 0,
		dapm_vref_event, SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_PRE_PMD),

	/* PLL */
	SND_SOC_DAPM_SUPPLY("PLL", SND_SOC_NOPM, 0, 0, pll_event,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* Headphone */
	SND_SOC_DAPM_DAC_E("DAC L", "HiFi Playback", R_PWRM2, FB_PWRM2_HPL, 0,
			dac_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_DAC_E("DAC R", "HiFi Playback", R_PWRM2, FB_PWRM2_HPR, 0,
			dac_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUTPUT("Headphone L"),
	SND_SOC_DAPM_OUTPUT("Headphone R"),

	/* Speaker */
	SND_SOC_DAPM_DAC_E("ClassD L", "HiFi Playback",
		R_PWRM2, FB_PWRM2_SPKL, 0,
		dac_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_DAC_E("ClassD R", "HiFi Playback",
		R_PWRM2, FB_PWRM2_SPKR, 0,
		dac_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUTPUT("Speaker L"),
	SND_SOC_DAPM_OUTPUT("Speaker R"),

	/* Capture */
	SND_SOC_DAPM_PGA("Analog In PGA L", R_PWRM1, FB_PWRM1_PGAL, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Analog In PGA R", R_PWRM1, FB_PWRM1_PGAR, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Analog Boost L", R_PWRM1, FB_PWRM1_BSTL, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Analog Boost R", R_PWRM1, FB_PWRM1_BSTR, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("ADC Mute", R_CNVRTR0, FB_CNVRTR0_HPOR, true, शून्य, 0),
	SND_SOC_DAPM_ADC("ADC L", "HiFi Capture", R_PWRM1, FB_PWRM1_ADCL, 0),
	SND_SOC_DAPM_ADC("ADC R", "HiFi Capture", R_PWRM1, FB_PWRM1_ADCR, 0),

	/* Capture Input */
	SND_SOC_DAPM_MUX("Input L Capture Route", R_PWRM2,
			FB_PWRM2_INSELL, 0, &left_input_select),
	SND_SOC_DAPM_MUX("Input R Capture Route", R_PWRM2,
			FB_PWRM2_INSELR, 0, &right_input_select),

	/* Digital Mic */
	SND_SOC_DAPM_SUPPLY_S("Digital Mic Enable", 2, R_DMICCTL,
		FB_DMICCTL_DMICEN, 0, शून्य,
		SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_PRE_PMD),

	/* Analog Mic */
	SND_SOC_DAPM_SUPPLY_S("Mic Bias", 2, R_PWRM1, FB_PWRM1_MICB,
		0, dapm_micb_event, SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_PRE_PMD),

	/* Line In */
	SND_SOC_DAPM_INPUT("Line In 1 L"),
	SND_SOC_DAPM_INPUT("Line In 1 R"),
	SND_SOC_DAPM_INPUT("Line In 2 L"),
	SND_SOC_DAPM_INPUT("Line In 2 R"),
	SND_SOC_DAPM_INPUT("Line In 3 L"),
	SND_SOC_DAPM_INPUT("Line In 3 R"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tscs42xx_पूर्णांकercon[] = अणु
	अणु"DAC L", शून्य, "PLL"पूर्ण,
	अणु"DAC R", शून्य, "PLL"पूर्ण,
	अणु"DAC L", शून्य, "Vref"पूर्ण,
	अणु"DAC R", शून्य, "Vref"पूर्ण,
	अणु"Headphone L", शून्य, "DAC L"पूर्ण,
	अणु"Headphone R", शून्य, "DAC R"पूर्ण,

	अणु"ClassD L", शून्य, "PLL"पूर्ण,
	अणु"ClassD R", शून्य, "PLL"पूर्ण,
	अणु"ClassD L", शून्य, "Vref"पूर्ण,
	अणु"ClassD R", शून्य, "Vref"पूर्ण,
	अणु"Speaker L", शून्य, "ClassD L"पूर्ण,
	अणु"Speaker R", शून्य, "ClassD R"पूर्ण,

	अणु"Input L Capture Route", शून्य, "Vref"पूर्ण,
	अणु"Input R Capture Route", शून्य, "Vref"पूर्ण,

	अणु"Mic Bias", शून्य, "Vref"पूर्ण,

	अणु"Input L Capture Route", "Line 1", "Line In 1 L"पूर्ण,
	अणु"Input R Capture Route", "Line 1", "Line In 1 R"पूर्ण,
	अणु"Input L Capture Route", "Line 2", "Line In 2 L"पूर्ण,
	अणु"Input R Capture Route", "Line 2", "Line In 2 R"पूर्ण,
	अणु"Input L Capture Route", "Line 3", "Line In 3 L"पूर्ण,
	अणु"Input R Capture Route", "Line 3", "Line In 3 R"पूर्ण,

	अणु"Analog In PGA L", शून्य, "Input L Capture Route"पूर्ण,
	अणु"Analog In PGA R", शून्य, "Input R Capture Route"पूर्ण,
	अणु"Analog Boost L", शून्य, "Analog In PGA L"पूर्ण,
	अणु"Analog Boost R", शून्य, "Analog In PGA R"पूर्ण,
	अणु"ADC Mute", शून्य, "Analog Boost L"पूर्ण,
	अणु"ADC Mute", शून्य, "Analog Boost R"पूर्ण,
	अणु"ADC L", शून्य, "PLL"पूर्ण,
	अणु"ADC R", शून्य, "PLL"पूर्ण,
	अणु"ADC L", शून्य, "ADC Mute"पूर्ण,
	अणु"ADC R", शून्य, "ADC Mute"पूर्ण,
पूर्ण;

/************
 * CONTROLS *
 ************/

अटल अक्षर स्थिर * स्थिर eq_band_enable_text[] = अणु
	"Prescale only",
	"Band1",
	"Band1:2",
	"Band1:3",
	"Band1:4",
	"Band1:5",
	"Band1:6",
पूर्ण;

अटल अक्षर स्थिर * स्थिर level_detection_text[] = अणु
	"Average",
	"Peak",
पूर्ण;

अटल अक्षर स्थिर * स्थिर level_detection_winकरोw_text[] = अणु
	"512 Samples",
	"64 Samples",
पूर्ण;

अटल अक्षर स्थिर * स्थिर compressor_ratio_text[] = अणु
	"Reserved", "1.5:1", "2:1", "3:1", "4:1", "5:1", "6:1",
	"7:1", "8:1", "9:1", "10:1", "11:1", "12:1", "13:1", "14:1",
	"15:1", "16:1", "17:1", "18:1", "19:1", "20:1",
पूर्ण;

अटल DECLARE_TLV_DB_SCALE(hpvol_scale, -8850, 75, 0);
अटल DECLARE_TLV_DB_SCALE(spkvol_scale, -7725, 75, 0);
अटल DECLARE_TLV_DB_SCALE(dacvol_scale, -9563, 38, 0);
अटल DECLARE_TLV_DB_SCALE(adcvol_scale, -7125, 38, 0);
अटल DECLARE_TLV_DB_SCALE(invol_scale, -1725, 75, 0);
अटल DECLARE_TLV_DB_SCALE(mic_boost_scale, 0, 1000, 0);
अटल DECLARE_TLV_DB_MINMAX(mugain_scale, 0, 4650);
अटल DECLARE_TLV_DB_MINMAX(compth_scale, -9562, 0);

अटल स्थिर काष्ठा soc_क्रमागत eq1_band_enable_क्रमागत =
	SOC_ENUM_SINGLE(R_CONFIG1, FB_CONFIG1_EQ1_BE,
		ARRAY_SIZE(eq_band_enable_text), eq_band_enable_text);

अटल स्थिर काष्ठा soc_क्रमागत eq2_band_enable_क्रमागत =
	SOC_ENUM_SINGLE(R_CONFIG1, FB_CONFIG1_EQ2_BE,
		ARRAY_SIZE(eq_band_enable_text), eq_band_enable_text);

अटल स्थिर काष्ठा soc_क्रमागत cle_level_detection_क्रमागत =
	SOC_ENUM_SINGLE(R_CLECTL, FB_CLECTL_LVL_MODE,
		ARRAY_SIZE(level_detection_text),
		level_detection_text);

अटल स्थिर काष्ठा soc_क्रमागत cle_level_detection_winकरोw_क्रमागत =
	SOC_ENUM_SINGLE(R_CLECTL, FB_CLECTL_WINDOWSEL,
		ARRAY_SIZE(level_detection_winकरोw_text),
		level_detection_winकरोw_text);

अटल स्थिर काष्ठा soc_क्रमागत mbc_level_detection_क्रमागतs[] = अणु
	SOC_ENUM_SINGLE(R_DACMBCCTL, FB_DACMBCCTL_LVLMODE1,
		ARRAY_SIZE(level_detection_text),
			level_detection_text),
	SOC_ENUM_SINGLE(R_DACMBCCTL, FB_DACMBCCTL_LVLMODE2,
		ARRAY_SIZE(level_detection_text),
			level_detection_text),
	SOC_ENUM_SINGLE(R_DACMBCCTL, FB_DACMBCCTL_LVLMODE3,
		ARRAY_SIZE(level_detection_text),
			level_detection_text),
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत mbc_level_detection_winकरोw_क्रमागतs[] = अणु
	SOC_ENUM_SINGLE(R_DACMBCCTL, FB_DACMBCCTL_WINSEL1,
		ARRAY_SIZE(level_detection_winकरोw_text),
			level_detection_winकरोw_text),
	SOC_ENUM_SINGLE(R_DACMBCCTL, FB_DACMBCCTL_WINSEL2,
		ARRAY_SIZE(level_detection_winकरोw_text),
			level_detection_winकरोw_text),
	SOC_ENUM_SINGLE(R_DACMBCCTL, FB_DACMBCCTL_WINSEL3,
		ARRAY_SIZE(level_detection_winकरोw_text),
			level_detection_winकरोw_text),
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत compressor_ratio_क्रमागत =
	SOC_ENUM_SINGLE(R_CMPRAT, FB_CMPRAT,
		ARRAY_SIZE(compressor_ratio_text), compressor_ratio_text);

अटल स्थिर काष्ठा soc_क्रमागत dac_mbc1_compressor_ratio_क्रमागत =
	SOC_ENUM_SINGLE(R_DACMBCRAT1, FB_DACMBCRAT1_RATIO,
		ARRAY_SIZE(compressor_ratio_text), compressor_ratio_text);

अटल स्थिर काष्ठा soc_क्रमागत dac_mbc2_compressor_ratio_क्रमागत =
	SOC_ENUM_SINGLE(R_DACMBCRAT2, FB_DACMBCRAT2_RATIO,
		ARRAY_SIZE(compressor_ratio_text), compressor_ratio_text);

अटल स्थिर काष्ठा soc_क्रमागत dac_mbc3_compressor_ratio_क्रमागत =
	SOC_ENUM_SINGLE(R_DACMBCRAT3, FB_DACMBCRAT3_RATIO,
		ARRAY_SIZE(compressor_ratio_text), compressor_ratio_text);

अटल पूर्णांक bytes_info_ext(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *ucontrol)
अणु
	काष्ठा coeff_ram_ctl *ctl =
		(काष्ठा coeff_ram_ctl *)kcontrol->निजी_value;
	काष्ठा soc_bytes_ext *params = &ctl->bytes_ext;

	ucontrol->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	ucontrol->count = params->max;

	वापस 0;
पूर्ण

#घोषणा COEFF_RAM_CTL(xname, xcount, xaddr) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = bytes_info_ext, \
	.get = coeff_ram_get, .put = coeff_ram_put, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा coeff_ram_ctl) अणु \
		.addr = xaddr, \
		.bytes_ext = अणु.max = xcount, पूर्ण, \
	पूर्ण \
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new tscs42xx_snd_controls[] = अणु
	/* Volumes */
	SOC_DOUBLE_R_TLV("Headphone Volume", R_HPVOLL, R_HPVOLR,
			FB_HPVOLL, 0x7F, 0, hpvol_scale),
	SOC_DOUBLE_R_TLV("Speaker Volume", R_SPKVOLL, R_SPKVOLR,
			FB_SPKVOLL, 0x7F, 0, spkvol_scale),
	SOC_DOUBLE_R_TLV("Master Volume", R_DACVOLL, R_DACVOLR,
			FB_DACVOLL, 0xFF, 0, dacvol_scale),
	SOC_DOUBLE_R_TLV("PCM Volume", R_ADCVOLL, R_ADCVOLR,
			FB_ADCVOLL, 0xFF, 0, adcvol_scale),
	SOC_DOUBLE_R_TLV("Input Volume", R_INVOLL, R_INVOLR,
			FB_INVOLL, 0x3F, 0, invol_scale),

	/* INSEL */
	SOC_DOUBLE_R_TLV("Mic Boost Volume", R_INSELL, R_INSELR,
			FB_INSELL_MICBSTL, FV_INSELL_MICBSTL_30DB,
			0, mic_boost_scale),

	/* Input Channel Map */
	SOC_ENUM("Input Channel Map", ch_map_select_क्रमागत),

	/* Mic Bias */
	SOC_SINGLE("Mic Bias Boost Switch", 0x71, 0x07, 1, 0),

	/* Headphone Auto Switching */
	SOC_SINGLE("Headphone Auto Switching Switch",
			R_CTL, FB_CTL_HPSWEN, 1, 0),
	SOC_SINGLE("Headphone Detect Polarity Toggle Switch",
			R_CTL, FB_CTL_HPSWPOL, 1, 0),

	/* Coefficient Ram */
	COEFF_RAM_CTL("Cascade1L BiQuad1", BIQUAD_SIZE, 0x00),
	COEFF_RAM_CTL("Cascade1L BiQuad2", BIQUAD_SIZE, 0x05),
	COEFF_RAM_CTL("Cascade1L BiQuad3", BIQUAD_SIZE, 0x0a),
	COEFF_RAM_CTL("Cascade1L BiQuad4", BIQUAD_SIZE, 0x0f),
	COEFF_RAM_CTL("Cascade1L BiQuad5", BIQUAD_SIZE, 0x14),
	COEFF_RAM_CTL("Cascade1L BiQuad6", BIQUAD_SIZE, 0x19),

	COEFF_RAM_CTL("Cascade1R BiQuad1", BIQUAD_SIZE, 0x20),
	COEFF_RAM_CTL("Cascade1R BiQuad2", BIQUAD_SIZE, 0x25),
	COEFF_RAM_CTL("Cascade1R BiQuad3", BIQUAD_SIZE, 0x2a),
	COEFF_RAM_CTL("Cascade1R BiQuad4", BIQUAD_SIZE, 0x2f),
	COEFF_RAM_CTL("Cascade1R BiQuad5", BIQUAD_SIZE, 0x34),
	COEFF_RAM_CTL("Cascade1R BiQuad6", BIQUAD_SIZE, 0x39),

	COEFF_RAM_CTL("Cascade1L Prescale", COEFF_SIZE, 0x1f),
	COEFF_RAM_CTL("Cascade1R Prescale", COEFF_SIZE, 0x3f),

	COEFF_RAM_CTL("Cascade2L BiQuad1", BIQUAD_SIZE, 0x40),
	COEFF_RAM_CTL("Cascade2L BiQuad2", BIQUAD_SIZE, 0x45),
	COEFF_RAM_CTL("Cascade2L BiQuad3", BIQUAD_SIZE, 0x4a),
	COEFF_RAM_CTL("Cascade2L BiQuad4", BIQUAD_SIZE, 0x4f),
	COEFF_RAM_CTL("Cascade2L BiQuad5", BIQUAD_SIZE, 0x54),
	COEFF_RAM_CTL("Cascade2L BiQuad6", BIQUAD_SIZE, 0x59),

	COEFF_RAM_CTL("Cascade2R BiQuad1", BIQUAD_SIZE, 0x60),
	COEFF_RAM_CTL("Cascade2R BiQuad2", BIQUAD_SIZE, 0x65),
	COEFF_RAM_CTL("Cascade2R BiQuad3", BIQUAD_SIZE, 0x6a),
	COEFF_RAM_CTL("Cascade2R BiQuad4", BIQUAD_SIZE, 0x6f),
	COEFF_RAM_CTL("Cascade2R BiQuad5", BIQUAD_SIZE, 0x74),
	COEFF_RAM_CTL("Cascade2R BiQuad6", BIQUAD_SIZE, 0x79),

	COEFF_RAM_CTL("Cascade2L Prescale", COEFF_SIZE, 0x5f),
	COEFF_RAM_CTL("Cascade2R Prescale", COEFF_SIZE, 0x7f),

	COEFF_RAM_CTL("Bass Extraction BiQuad1", BIQUAD_SIZE, 0x80),
	COEFF_RAM_CTL("Bass Extraction BiQuad2", BIQUAD_SIZE, 0x85),

	COEFF_RAM_CTL("Bass Non Linear Function 1", COEFF_SIZE, 0x8a),
	COEFF_RAM_CTL("Bass Non Linear Function 2", COEFF_SIZE, 0x8b),

	COEFF_RAM_CTL("Bass Limiter BiQuad", BIQUAD_SIZE, 0x8c),

	COEFF_RAM_CTL("Bass Cut Off BiQuad", BIQUAD_SIZE, 0x91),

	COEFF_RAM_CTL("Bass Mix", COEFF_SIZE, 0x96),

	COEFF_RAM_CTL("Treb Extraction BiQuad1", BIQUAD_SIZE, 0x97),
	COEFF_RAM_CTL("Treb Extraction BiQuad2", BIQUAD_SIZE, 0x9c),

	COEFF_RAM_CTL("Treb Non Linear Function 1", COEFF_SIZE, 0xa1),
	COEFF_RAM_CTL("Treb Non Linear Function 2", COEFF_SIZE, 0xa2),

	COEFF_RAM_CTL("Treb Limiter BiQuad", BIQUAD_SIZE, 0xa3),

	COEFF_RAM_CTL("Treb Cut Off BiQuad", BIQUAD_SIZE, 0xa8),

	COEFF_RAM_CTL("Treb Mix", COEFF_SIZE, 0xad),

	COEFF_RAM_CTL("3D", COEFF_SIZE, 0xae),

	COEFF_RAM_CTL("3D Mix", COEFF_SIZE, 0xaf),

	COEFF_RAM_CTL("MBC1 BiQuad1", BIQUAD_SIZE, 0xb0),
	COEFF_RAM_CTL("MBC1 BiQuad2", BIQUAD_SIZE, 0xb5),

	COEFF_RAM_CTL("MBC2 BiQuad1", BIQUAD_SIZE, 0xba),
	COEFF_RAM_CTL("MBC2 BiQuad2", BIQUAD_SIZE, 0xbf),

	COEFF_RAM_CTL("MBC3 BiQuad1", BIQUAD_SIZE, 0xc4),
	COEFF_RAM_CTL("MBC3 BiQuad2", BIQUAD_SIZE, 0xc9),

	/* EQ */
	SOC_SINGLE("EQ1 Switch", R_CONFIG1, FB_CONFIG1_EQ1_EN, 1, 0),
	SOC_SINGLE("EQ2 Switch", R_CONFIG1, FB_CONFIG1_EQ2_EN, 1, 0),
	SOC_ENUM("EQ1 Band Enable", eq1_band_enable_क्रमागत),
	SOC_ENUM("EQ2 Band Enable", eq2_band_enable_क्रमागत),

	/* CLE */
	SOC_ENUM("CLE Level Detect",
		cle_level_detection_क्रमागत),
	SOC_ENUM("CLE Level Detect Win",
		cle_level_detection_winकरोw_क्रमागत),
	SOC_SINGLE("Expander Switch",
		R_CLECTL, FB_CLECTL_EXP_EN, 1, 0),
	SOC_SINGLE("Limiter Switch",
		R_CLECTL, FB_CLECTL_LIMIT_EN, 1, 0),
	SOC_SINGLE("Comp Switch",
		R_CLECTL, FB_CLECTL_COMP_EN, 1, 0),
	SOC_SINGLE_TLV("CLE Make-Up Gain Volume",
		R_MUGAIN, FB_MUGAIN_CLEMUG, 0x1f, 0, mugain_scale),
	SOC_SINGLE_TLV("Comp Thresh Volume",
		R_COMPTH, FB_COMPTH, 0xff, 0, compth_scale),
	SOC_ENUM("Comp Ratio", compressor_ratio_क्रमागत),
	SND_SOC_BYTES("Comp Atk Time", R_CATKTCL, 2),

	/* Effects */
	SOC_SINGLE("3D Switch", R_FXCTL, FB_FXCTL_3DEN, 1, 0),
	SOC_SINGLE("Treble Switch", R_FXCTL, FB_FXCTL_TEEN, 1, 0),
	SOC_SINGLE("Treble Bypass Switch", R_FXCTL, FB_FXCTL_TNLFBYPASS, 1, 0),
	SOC_SINGLE("Bass Switch", R_FXCTL, FB_FXCTL_BEEN, 1, 0),
	SOC_SINGLE("Bass Bypass Switch", R_FXCTL, FB_FXCTL_BNLFBYPASS, 1, 0),

	/* MBC */
	SOC_SINGLE("MBC Band1 Switch", R_DACMBCEN, FB_DACMBCEN_MBCEN1, 1, 0),
	SOC_SINGLE("MBC Band2 Switch", R_DACMBCEN, FB_DACMBCEN_MBCEN2, 1, 0),
	SOC_SINGLE("MBC Band3 Switch", R_DACMBCEN, FB_DACMBCEN_MBCEN3, 1, 0),
	SOC_ENUM("MBC Band1 Level Detect",
		mbc_level_detection_क्रमागतs[0]),
	SOC_ENUM("MBC Band2 Level Detect",
		mbc_level_detection_क्रमागतs[1]),
	SOC_ENUM("MBC Band3 Level Detect",
		mbc_level_detection_क्रमागतs[2]),
	SOC_ENUM("MBC Band1 Level Detect Win",
		mbc_level_detection_winकरोw_क्रमागतs[0]),
	SOC_ENUM("MBC Band2 Level Detect Win",
		mbc_level_detection_winकरोw_क्रमागतs[1]),
	SOC_ENUM("MBC Band3 Level Detect Win",
		mbc_level_detection_winकरोw_क्रमागतs[2]),

	SOC_SINGLE("MBC1 Phase Invert Switch",
		R_DACMBCMUG1, FB_DACMBCMUG1_PHASE, 1, 0),
	SOC_SINGLE_TLV("DAC MBC1 Make-Up Gain Volume",
		R_DACMBCMUG1, FB_DACMBCMUG1_MUGAIN, 0x1f, 0, mugain_scale),
	SOC_SINGLE_TLV("DAC MBC1 Comp Thresh Volume",
		R_DACMBCTHR1, FB_DACMBCTHR1_THRESH, 0xff, 0, compth_scale),
	SOC_ENUM("DAC MBC1 Comp Ratio",
		dac_mbc1_compressor_ratio_क्रमागत),
	SND_SOC_BYTES("DAC MBC1 Comp Atk Time", R_DACMBCATK1L, 2),
	SND_SOC_BYTES("DAC MBC1 Comp Rel Time Const",
		R_DACMBCREL1L, 2),

	SOC_SINGLE("MBC2 Phase Invert Switch",
		R_DACMBCMUG2, FB_DACMBCMUG2_PHASE, 1, 0),
	SOC_SINGLE_TLV("DAC MBC2 Make-Up Gain Volume",
		R_DACMBCMUG2, FB_DACMBCMUG2_MUGAIN, 0x1f, 0, mugain_scale),
	SOC_SINGLE_TLV("DAC MBC2 Comp Thresh Volume",
		R_DACMBCTHR2, FB_DACMBCTHR2_THRESH, 0xff, 0, compth_scale),
	SOC_ENUM("DAC MBC2 Comp Ratio",
		dac_mbc2_compressor_ratio_क्रमागत),
	SND_SOC_BYTES("DAC MBC2 Comp Atk Time", R_DACMBCATK2L, 2),
	SND_SOC_BYTES("DAC MBC2 Comp Rel Time Const",
		R_DACMBCREL2L, 2),

	SOC_SINGLE("MBC3 Phase Invert Switch",
		R_DACMBCMUG3, FB_DACMBCMUG3_PHASE, 1, 0),
	SOC_SINGLE_TLV("DAC MBC3 Make-Up Gain Volume",
		R_DACMBCMUG3, FB_DACMBCMUG3_MUGAIN, 0x1f, 0, mugain_scale),
	SOC_SINGLE_TLV("DAC MBC3 Comp Thresh Volume",
		R_DACMBCTHR3, FB_DACMBCTHR3_THRESH, 0xff, 0, compth_scale),
	SOC_ENUM("DAC MBC3 Comp Ratio",
		dac_mbc3_compressor_ratio_क्रमागत),
	SND_SOC_BYTES("DAC MBC3 Comp Atk Time", R_DACMBCATK3L, 2),
	SND_SOC_BYTES("DAC MBC3 Comp Rel Time Const",
		R_DACMBCREL3L, 2),
पूर्ण;

अटल पूर्णांक setup_sample_क्रमmat(काष्ठा snd_soc_component *component,
		snd_pcm_क्रमmat_t क्रमmat)
अणु
	अचिन्हित पूर्णांक width;
	पूर्णांक ret;

	चयन (क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		width = RV_AIC1_WL_16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		width = RV_AIC1_WL_20;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		width = RV_AIC1_WL_24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		width = RV_AIC1_WL_32;
		अवरोध;
	शेष:
		ret = -EINVAL;
		dev_err(component->dev, "Unsupported format width (%d)\n", ret);
		वापस ret;
	पूर्ण
	ret = snd_soc_component_update_bits(component,
			R_AIC1, RM_AIC1_WL, width);
	अगर (ret < 0) अणु
		dev_err(component->dev,
				"Failed to set sample width (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक setup_sample_rate(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक rate)
अणु
	काष्ठा tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक br, bm;
	पूर्णांक ret;

	चयन (rate) अणु
	हाल 8000:
		br = RV_DACSR_DBR_32;
		bm = RV_DACSR_DBM_PT25;
		अवरोध;
	हाल 16000:
		br = RV_DACSR_DBR_32;
		bm = RV_DACSR_DBM_PT5;
		अवरोध;
	हाल 24000:
		br = RV_DACSR_DBR_48;
		bm = RV_DACSR_DBM_PT5;
		अवरोध;
	हाल 32000:
		br = RV_DACSR_DBR_32;
		bm = RV_DACSR_DBM_1;
		अवरोध;
	हाल 48000:
		br = RV_DACSR_DBR_48;
		bm = RV_DACSR_DBM_1;
		अवरोध;
	हाल 96000:
		br = RV_DACSR_DBR_48;
		bm = RV_DACSR_DBM_2;
		अवरोध;
	हाल 11025:
		br = RV_DACSR_DBR_44_1;
		bm = RV_DACSR_DBM_PT25;
		अवरोध;
	हाल 22050:
		br = RV_DACSR_DBR_44_1;
		bm = RV_DACSR_DBM_PT5;
		अवरोध;
	हाल 44100:
		br = RV_DACSR_DBR_44_1;
		bm = RV_DACSR_DBM_1;
		अवरोध;
	हाल 88200:
		br = RV_DACSR_DBR_44_1;
		bm = RV_DACSR_DBM_2;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported sample rate %d\n", rate);
		वापस -EINVAL;
	पूर्ण

	/* DAC and ADC share bit and frame घड़ी */
	ret = snd_soc_component_update_bits(component,
			R_DACSR, RM_DACSR_DBR, br);
	अगर (ret < 0) अणु
		dev_err(component->dev,
				"Failed to update register (%d)\n", ret);
		वापस ret;
	पूर्ण
	ret = snd_soc_component_update_bits(component,
			R_DACSR, RM_DACSR_DBM, bm);
	अगर (ret < 0) अणु
		dev_err(component->dev,
				"Failed to update register (%d)\n", ret);
		वापस ret;
	पूर्ण
	ret = snd_soc_component_update_bits(component,
			R_ADCSR, RM_DACSR_DBR, br);
	अगर (ret < 0) अणु
		dev_err(component->dev,
				"Failed to update register (%d)\n", ret);
		वापस ret;
	पूर्ण
	ret = snd_soc_component_update_bits(component,
			R_ADCSR, RM_DACSR_DBM, bm);
	अगर (ret < 0) अणु
		dev_err(component->dev,
				"Failed to update register (%d)\n", ret);
		वापस ret;
	पूर्ण

	mutex_lock(&tscs42xx->audio_params_lock);

	tscs42xx->samplerate = rate;

	mutex_unlock(&tscs42xx->audio_params_lock);

	वापस 0;
पूर्ण

काष्ठा reg_setting अणु
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक mask;
पूर्ण;

#घोषणा PLL_REG_SETTINGS_COUNT 13
काष्ठा pll_ctl अणु
	पूर्णांक input_freq;
	काष्ठा reg_setting settings[PLL_REG_SETTINGS_COUNT];
पूर्ण;

#घोषणा PLL_CTL(f, rt, rd, r1b_l, r9, ra, rb,		\
		rc, r12, r1b_h, re, rf, r10, r11)	\
	अणु						\
		.input_freq = f,			\
		.settings = अणु				\
			अणुR_TIMEBASE,  rt,   0xFFपूर्ण,	\
			अणुR_PLLCTLD,   rd,   0xFFपूर्ण,	\
			अणुR_PLLCTL1B, r1b_l, 0x0Fपूर्ण,	\
			अणुR_PLLCTL9,   r9,   0xFFपूर्ण,	\
			अणुR_PLLCTLA,   ra,   0xFFपूर्ण,	\
			अणुR_PLLCTLB,   rb,   0xFFपूर्ण,	\
			अणुR_PLLCTLC,   rc,   0xFFपूर्ण,	\
			अणुR_PLLCTL12, r12,   0xFFपूर्ण,	\
			अणुR_PLLCTL1B, r1b_h, 0xF0पूर्ण,	\
			अणुR_PLLCTLE,   re,   0xFFपूर्ण,	\
			अणुR_PLLCTLF,   rf,   0xFFपूर्ण,	\
			अणुR_PLLCTL10, r10,   0xFFपूर्ण,	\
			अणुR_PLLCTL11, r11,   0xFFपूर्ण,	\
		पूर्ण,					\
	पूर्ण

अटल स्थिर काष्ठा pll_ctl pll_ctls[] = अणु
	PLL_CTL(1411200, 0x05,
		0x39, 0x04, 0x07, 0x02, 0xC3, 0x04,
		0x1B, 0x10, 0x03, 0x03, 0xD0, 0x02),
	PLL_CTL(1536000, 0x05,
		0x1A, 0x04, 0x02, 0x03, 0xE0, 0x01,
		0x1A, 0x10, 0x02, 0x03, 0xB9, 0x01),
	PLL_CTL(2822400, 0x0A,
		0x23, 0x04, 0x07, 0x04, 0xC3, 0x04,
		0x22, 0x10, 0x05, 0x03, 0x58, 0x02),
	PLL_CTL(3072000, 0x0B,
		0x22, 0x04, 0x07, 0x03, 0x48, 0x03,
		0x1A, 0x10, 0x04, 0x03, 0xB9, 0x01),
	PLL_CTL(5644800, 0x15,
		0x23, 0x04, 0x0E, 0x04, 0xC3, 0x04,
		0x1A, 0x10, 0x08, 0x03, 0xE0, 0x01),
	PLL_CTL(6144000, 0x17,
		0x1A, 0x04, 0x08, 0x03, 0xE0, 0x01,
		0x1A, 0x10, 0x08, 0x03, 0xB9, 0x01),
	PLL_CTL(12000000, 0x2E,
		0x1B, 0x04, 0x19, 0x03, 0x00, 0x03,
		0x2A, 0x10, 0x19, 0x05, 0x98, 0x04),
	PLL_CTL(19200000, 0x4A,
		0x13, 0x04, 0x14, 0x03, 0x80, 0x01,
		0x1A, 0x10, 0x19, 0x03, 0xB9, 0x01),
	PLL_CTL(22000000, 0x55,
		0x2A, 0x04, 0x37, 0x05, 0x00, 0x06,
		0x22, 0x10, 0x26, 0x03, 0x49, 0x02),
	PLL_CTL(22579200, 0x57,
		0x22, 0x04, 0x31, 0x03, 0x20, 0x03,
		0x1A, 0x10, 0x1D, 0x03, 0xB3, 0x01),
	PLL_CTL(24000000, 0x5D,
		0x13, 0x04, 0x19, 0x03, 0x80, 0x01,
		0x1B, 0x10, 0x19, 0x05, 0x4C, 0x02),
	PLL_CTL(24576000, 0x5F,
		0x13, 0x04, 0x1D, 0x03, 0xB3, 0x01,
		0x22, 0x10, 0x40, 0x03, 0x72, 0x03),
	PLL_CTL(27000000, 0x68,
		0x22, 0x04, 0x4B, 0x03, 0x00, 0x04,
		0x2A, 0x10, 0x7D, 0x03, 0x20, 0x06),
	PLL_CTL(36000000, 0x8C,
		0x1B, 0x04, 0x4B, 0x03, 0x00, 0x03,
		0x2A, 0x10, 0x7D, 0x03, 0x98, 0x04),
	PLL_CTL(25000000, 0x61,
		0x1B, 0x04, 0x37, 0x03, 0x2B, 0x03,
		0x1A, 0x10, 0x2A, 0x03, 0x39, 0x02),
	PLL_CTL(26000000, 0x65,
		0x23, 0x04, 0x41, 0x05, 0x00, 0x06,
		0x1A, 0x10, 0x26, 0x03, 0xEF, 0x01),
	PLL_CTL(12288000, 0x2F,
		0x1A, 0x04, 0x12, 0x03, 0x1C, 0x02,
		0x22, 0x10, 0x20, 0x03, 0x72, 0x03),
	PLL_CTL(40000000, 0x9B,
		0x22, 0x08, 0x7D, 0x03, 0x80, 0x04,
		0x23, 0x10, 0x7D, 0x05, 0xE4, 0x06),
	PLL_CTL(512000, 0x01,
		0x22, 0x04, 0x01, 0x03, 0xD0, 0x02,
		0x1B, 0x10, 0x01, 0x04, 0x72, 0x03),
	PLL_CTL(705600, 0x02,
		0x22, 0x04, 0x02, 0x03, 0x15, 0x04,
		0x22, 0x10, 0x01, 0x04, 0x80, 0x02),
	PLL_CTL(1024000, 0x03,
		0x22, 0x04, 0x02, 0x03, 0xD0, 0x02,
		0x1B, 0x10, 0x02, 0x04, 0x72, 0x03),
	PLL_CTL(2048000, 0x07,
		0x22, 0x04, 0x04, 0x03, 0xD0, 0x02,
		0x1B, 0x10, 0x04, 0x04, 0x72, 0x03),
	PLL_CTL(2400000, 0x08,
		0x22, 0x04, 0x05, 0x03, 0x00, 0x03,
		0x23, 0x10, 0x05, 0x05, 0x98, 0x04),
पूर्ण;

अटल स्थिर काष्ठा pll_ctl *get_pll_ctl(पूर्णांक input_freq)
अणु
	पूर्णांक i;
	स्थिर काष्ठा pll_ctl *pll_ctl = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(pll_ctls); ++i)
		अगर (input_freq == pll_ctls[i].input_freq) अणु
			pll_ctl = &pll_ctls[i];
			अवरोध;
		पूर्ण

	वापस pll_ctl;
पूर्ण

अटल पूर्णांक set_pll_ctl_from_input_freq(काष्ठा snd_soc_component *component,
		स्थिर पूर्णांक input_freq)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	स्थिर काष्ठा pll_ctl *pll_ctl;

	pll_ctl = get_pll_ctl(input_freq);
	अगर (!pll_ctl) अणु
		ret = -EINVAL;
		dev_err(component->dev, "No PLL input entry for %d (%d)\n",
			input_freq, ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < PLL_REG_SETTINGS_COUNT; ++i) अणु
		ret = snd_soc_component_update_bits(component,
			pll_ctl->settings[i].addr,
			pll_ctl->settings[i].mask,
			pll_ctl->settings[i].val);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Failed to set pll ctl (%d)\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tscs42xx_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा snd_soc_dai *codec_dai)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक ret;

	ret = setup_sample_क्रमmat(component, params_क्रमmat(params));
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to setup sample format (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	ret = setup_sample_rate(component, params_rate(params));
	अगर (ret < 0) अणु
		dev_err(component->dev,
				"Failed to setup sample rate (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dac_mute(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;

	ret = snd_soc_component_update_bits(component,
			R_CNVRTR1, RM_CNVRTR1_DACMU,
		RV_CNVRTR1_DACMU_ENABLE);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to mute DAC (%d)\n",
				ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dac_unmute(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;

	ret = snd_soc_component_update_bits(component,
			R_CNVRTR1, RM_CNVRTR1_DACMU,
		RV_CNVRTR1_DACMU_DISABLE);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to unmute DAC (%d)\n",
				ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक adc_mute(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;

	ret = snd_soc_component_update_bits(component,
			R_CNVRTR0, RM_CNVRTR0_ADCMU, RV_CNVRTR0_ADCMU_ENABLE);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to mute ADC (%d)\n",
				ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक adc_unmute(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;

	ret = snd_soc_component_update_bits(component,
			R_CNVRTR0, RM_CNVRTR0_ADCMU, RV_CNVRTR0_ADCMU_DISABLE);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to unmute ADC (%d)\n",
				ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tscs42xx_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक ret;

	अगर (mute)
		अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
			ret = dac_mute(component);
		अन्यथा
			ret = adc_mute(component);
	अन्यथा
		अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
			ret = dac_unmute(component);
		अन्यथा
			ret = adc_unmute(component);

	वापस ret;
पूर्ण

अटल पूर्णांक tscs42xx_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक ret;

	/* Slave mode not supported since it needs always-on frame घड़ी */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ret = snd_soc_component_update_bits(component,
				R_AIC1, RM_AIC1_MS, RV_AIC1_MS_MASTER);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"Failed to set codec DAI master (%d)\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		dev_err(component->dev, "Unsupported format (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tscs42xx_set_dai_bclk_ratio(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक value;
	पूर्णांक ret = 0;

	चयन (ratio) अणु
	हाल 32:
		value = RV_DACSR_DBCM_32;
		अवरोध;
	हाल 40:
		value = RV_DACSR_DBCM_40;
		अवरोध;
	हाल 64:
		value = RV_DACSR_DBCM_64;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported bclk ratio (%d)\n", ret);
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component,
			R_DACSR, RM_DACSR_DBCM, value);
	अगर (ret < 0) अणु
		dev_err(component->dev,
				"Failed to set DAC BCLK ratio (%d)\n", ret);
		वापस ret;
	पूर्ण
	ret = snd_soc_component_update_bits(component,
			R_ADCSR, RM_ADCSR_ABCM, value);
	अगर (ret < 0) अणु
		dev_err(component->dev,
				"Failed to set ADC BCLK ratio (%d)\n", ret);
		वापस ret;
	पूर्ण

	mutex_lock(&tscs42xx->audio_params_lock);

	tscs42xx->bclk_ratio = ratio;

	mutex_unlock(&tscs42xx->audio_params_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tscs42xx_dai_ops = अणु
	.hw_params	= tscs42xx_hw_params,
	.mute_stream	= tscs42xx_mute_stream,
	.set_fmt	= tscs42xx_set_dai_fmt,
	.set_bclk_ratio = tscs42xx_set_dai_bclk_ratio,
पूर्ण;

अटल पूर्णांक part_is_valid(काष्ठा tscs42xx *tscs42xx)
अणु
	पूर्णांक val;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;

	ret = regmap_पढ़ो(tscs42xx->regmap, R_DEVIDH, &reg);
	अगर (ret < 0)
		वापस ret;

	val = reg << 8;
	ret = regmap_पढ़ो(tscs42xx->regmap, R_DEVIDL, &reg);
	अगर (ret < 0)
		वापस ret;

	val |= reg;

	चयन (val) अणु
	हाल 0x4A74:
	हाल 0x4A73:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक set_sysclk(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	अचिन्हित दीर्घ freq;
	पूर्णांक ret;

	चयन (tscs42xx->sysclk_src_id) अणु
	हाल TSCS42XX_PLL_SRC_XTAL:
	हाल TSCS42XX_PLL_SRC_MCLK1:
		ret = snd_soc_component_ग_लिखो(component, R_PLLREFSEL,
				RV_PLLREFSEL_PLL1_REF_SEL_XTAL_MCLK1 |
				RV_PLLREFSEL_PLL2_REF_SEL_XTAL_MCLK1);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"Failed to set pll reference input (%d)\n",
				ret);
			वापस ret;
		पूर्ण
		अवरोध;
	हाल TSCS42XX_PLL_SRC_MCLK2:
		ret = snd_soc_component_ग_लिखो(component, R_PLLREFSEL,
				RV_PLLREFSEL_PLL1_REF_SEL_MCLK2 |
				RV_PLLREFSEL_PLL2_REF_SEL_MCLK2);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"Failed to set PLL reference (%d)\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(component->dev, "pll src is unsupported\n");
		वापस -EINVAL;
	पूर्ण

	freq = clk_get_rate(tscs42xx->sysclk);
	ret = set_pll_ctl_from_input_freq(component, freq);
	अगर (ret < 0) अणु
		dev_err(component->dev,
			"Failed to setup PLL input freq (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tscs42xx_probe(काष्ठा snd_soc_component *component)
अणु
	वापस set_sysclk(component);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_tscs42xx = अणु
	.probe			= tscs42xx_probe,
	.dapm_widमाला_लो		= tscs42xx_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tscs42xx_dapm_widमाला_लो),
	.dapm_routes		= tscs42xx_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(tscs42xx_पूर्णांकercon),
	.controls		= tscs42xx_snd_controls,
	.num_controls		= ARRAY_SIZE(tscs42xx_snd_controls),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल अंतरभूत व्योम init_coeff_ram_cache(काष्ठा tscs42xx *tscs42xx)
अणु
	अटल स्थिर u8 norm_addrs[] = अणु
		0x00, 0x05, 0x0a, 0x0f, 0x14, 0x19, 0x1f, 0x20, 0x25, 0x2a,
		0x2f, 0x34, 0x39, 0x3f, 0x40, 0x45, 0x4a, 0x4f, 0x54, 0x59,
		0x5f, 0x60, 0x65, 0x6a, 0x6f, 0x74, 0x79, 0x7f, 0x80, 0x85,
		0x8c, 0x91, 0x96, 0x97, 0x9c, 0xa3, 0xa8, 0xad, 0xaf, 0xb0,
		0xb5, 0xba, 0xbf, 0xc4, 0xc9,
	पूर्ण;
	u8 *coeff_ram = tscs42xx->coeff_ram;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(norm_addrs); i++)
		coeff_ram[((norm_addrs[i] + 1) * COEFF_SIZE) - 1] = 0x40;
पूर्ण

#घोषणा TSCS42XX_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा TSCS42XX_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE \
	| SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver tscs42xx_dai = अणु
	.name = "tscs42xx-HiFi",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = TSCS42XX_RATES,
		.क्रमmats = TSCS42XX_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "HiFi Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = TSCS42XX_RATES,
		.क्रमmats = TSCS42XX_FORMATS,पूर्ण,
	.ops = &tscs42xx_dai_ops,
	.symmetric_rate = 1,
	.symmetric_channels = 1,
	.symmetric_sample_bits = 1,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence tscs42xx_patch[] = अणु
	अणु R_AIC2, RV_AIC2_BLRCM_DAC_BCLK_LRCLK_SHARED पूर्ण,
पूर्ण;

अटल अक्षर स्थिर * स्थिर src_names[TSCS42XX_PLL_SRC_CNT] = अणु
	"xtal", "mclk1", "mclk2"पूर्ण;

अटल पूर्णांक tscs42xx_i2c_probe(काष्ठा i2c_client *i2c,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tscs42xx *tscs42xx;
	पूर्णांक src;
	पूर्णांक ret;

	tscs42xx = devm_kzalloc(&i2c->dev, माप(*tscs42xx), GFP_KERNEL);
	अगर (!tscs42xx) अणु
		ret = -ENOMEM;
		dev_err(&i2c->dev,
			"Failed to allocate memory for data (%d)\n", ret);
		वापस ret;
	पूर्ण
	i2c_set_clientdata(i2c, tscs42xx);

	क्रम (src = TSCS42XX_PLL_SRC_XTAL; src < TSCS42XX_PLL_SRC_CNT; src++) अणु
		tscs42xx->sysclk = devm_clk_get(&i2c->dev, src_names[src]);
		अगर (!IS_ERR(tscs42xx->sysclk)) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (PTR_ERR(tscs42xx->sysclk) != -ENOENT) अणु
			ret = PTR_ERR(tscs42xx->sysclk);
			dev_err(&i2c->dev, "Failed to get sysclk (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण
	अगर (src == TSCS42XX_PLL_SRC_CNT) अणु
		ret = -EINVAL;
		dev_err(&i2c->dev, "Failed to get a valid clock name (%d)\n",
				ret);
		वापस ret;
	पूर्ण
	tscs42xx->sysclk_src_id = src;

	tscs42xx->regmap = devm_regmap_init_i2c(i2c, &tscs42xx_regmap);
	अगर (IS_ERR(tscs42xx->regmap)) अणु
		ret = PTR_ERR(tscs42xx->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap (%d)\n", ret);
		वापस ret;
	पूर्ण

	init_coeff_ram_cache(tscs42xx);

	ret = part_is_valid(tscs42xx);
	अगर (ret <= 0) अणु
		dev_err(&i2c->dev, "No valid part (%d)\n", ret);
		ret = -ENODEV;
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(tscs42xx->regmap, R_RESET, RV_RESET_ENABLE);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to reset device (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_रेजिस्टर_patch(tscs42xx->regmap, tscs42xx_patch,
			ARRAY_SIZE(tscs42xx_patch));
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to apply patch (%d)\n", ret);
		वापस ret;
	पूर्ण

	mutex_init(&tscs42xx->audio_params_lock);
	mutex_init(&tscs42xx->coeff_ram_lock);
	mutex_init(&tscs42xx->pll_lock);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_codec_dev_tscs42xx, &tscs42xx_dai, 1);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to register codec (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tscs42xx_i2c_id[] = अणु
	अणु "tscs42A1", 0 पूर्ण,
	अणु "tscs42A2", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tscs42xx_i2c_id);

अटल स्थिर काष्ठा of_device_id tscs42xx_of_match[] = अणु
	अणु .compatible = "tempo,tscs42A1", पूर्ण,
	अणु .compatible = "tempo,tscs42A2", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tscs42xx_of_match);

अटल काष्ठा i2c_driver tscs42xx_i2c_driver = अणु
	.driver = अणु
		.name = "tscs42xx",
		.of_match_table = tscs42xx_of_match,
	पूर्ण,
	.probe =    tscs42xx_i2c_probe,
	.id_table = tscs42xx_i2c_id,
पूर्ण;

module_i2c_driver(tscs42xx_i2c_driver);

MODULE_AUTHOR("Tempo Semiconductor <steven.eckhoff.opensource@gmail.com");
MODULE_DESCRIPTION("ASoC TSCS42xx driver");
MODULE_LICENSE("GPL");
