<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC TWL6040 codec driver
 *
 * Author:	 Misael Lopez Cruz <x0052729@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/twl6040.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "twl6040.h"

क्रमागत twl6040_dai_id अणु
	TWL6040_DAI_LEGACY = 0,
	TWL6040_DAI_UL,
	TWL6040_DAI_DL1,
	TWL6040_DAI_DL2,
	TWL6040_DAI_VIB,
पूर्ण;

#घोषणा TWL6040_RATES		SNDRV_PCM_RATE_8000_96000
#घोषणा TWL6040_FORMATS	(SNDRV_PCM_FMTBIT_S32_LE)

#घोषणा TWL6040_OUTHS_0dB 0x00
#घोषणा TWL6040_OUTHS_M30dB 0x0F
#घोषणा TWL6040_OUTHF_0dB 0x03
#घोषणा TWL6040_OUTHF_M52dB 0x1D

#घोषणा TWL6040_CACHEREGNUM	(TWL6040_REG_STATUS + 1)

काष्ठा twl6040_jack_data अणु
	काष्ठा snd_soc_jack *jack;
	काष्ठा delayed_work work;
	पूर्णांक report;
पूर्ण;

/* codec निजी data */
काष्ठा twl6040_data अणु
	पूर्णांक plug_irq;
	पूर्णांक codec_घातered;
	पूर्णांक pll;
	पूर्णांक pll_घातer_mode;
	पूर्णांक hs_घातer_mode;
	पूर्णांक hs_घातer_mode_locked;
	bool dl1_unmuted;
	bool dl2_unmuted;
	u8 dl12_cache[TWL6040_REG_HFRCTL - TWL6040_REG_HSLCTL + 1];
	अचिन्हित पूर्णांक clk_in;
	अचिन्हित पूर्णांक sysclk;
	काष्ठा twl6040_jack_data hs_jack;
	काष्ठा snd_soc_component *component;
	काष्ठा mutex mutex;
पूर्ण;

/* set of rates क्रम each pll: low-घातer and high-perक्रमmance */
अटल स्थिर अचिन्हित पूर्णांक lp_rates[] = अणु
	8000,
	11250,
	16000,
	22500,
	32000,
	44100,
	48000,
	88200,
	96000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक hp_rates[] = अणु
	8000,
	16000,
	32000,
	48000,
	96000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list sysclk_स्थिरraपूर्णांकs[] = अणु
	अणु .count = ARRAY_SIZE(lp_rates), .list = lp_rates, पूर्ण,
	अणु .count = ARRAY_SIZE(hp_rates), .list = hp_rates, पूर्ण,
पूर्ण;

#घोषणा to_twl6040(component)	dev_get_drvdata((component)->dev->parent)

अटल अचिन्हित पूर्णांक twl6040_पढ़ो(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);
	काष्ठा twl6040 *twl6040 = to_twl6040(component);
	u8 value;

	अगर (reg >= TWL6040_CACHEREGNUM)
		वापस -EIO;

	चयन (reg) अणु
	हाल TWL6040_REG_HSLCTL:
	हाल TWL6040_REG_HSRCTL:
	हाल TWL6040_REG_EARCTL:
	हाल TWL6040_REG_HFLCTL:
	हाल TWL6040_REG_HFRCTL:
		value = priv->dl12_cache[reg - TWL6040_REG_HSLCTL];
		अवरोध;
	शेष:
		value = twl6040_reg_पढ़ो(twl6040, reg);
		अवरोध;
	पूर्ण

	वापस value;
पूर्ण

अटल bool twl6040_can_ग_लिखो_to_chip(काष्ठा snd_soc_component *component,
				  अचिन्हित पूर्णांक reg)
अणु
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);

	चयन (reg) अणु
	हाल TWL6040_REG_HSLCTL:
	हाल TWL6040_REG_HSRCTL:
	हाल TWL6040_REG_EARCTL:
		/* DL1 path */
		वापस priv->dl1_unmuted;
	हाल TWL6040_REG_HFLCTL:
	हाल TWL6040_REG_HFRCTL:
		वापस priv->dl2_unmuted;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम twl6040_update_dl12_cache(काष्ठा snd_soc_component *component,
					     u8 reg, u8 value)
अणु
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);

	चयन (reg) अणु
	हाल TWL6040_REG_HSLCTL:
	हाल TWL6040_REG_HSRCTL:
	हाल TWL6040_REG_EARCTL:
	हाल TWL6040_REG_HFLCTL:
	हाल TWL6040_REG_HFRCTL:
		priv->dl12_cache[reg - TWL6040_REG_HSLCTL] = value;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक twl6040_ग_लिखो(काष्ठा snd_soc_component *component,
			अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	काष्ठा twl6040 *twl6040 = to_twl6040(component);

	अगर (reg >= TWL6040_CACHEREGNUM)
		वापस -EIO;

	twl6040_update_dl12_cache(component, reg, value);
	अगर (twl6040_can_ग_लिखो_to_chip(component, reg))
		वापस twl6040_reg_ग_लिखो(twl6040, reg, value);
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम twl6040_init_chip(काष्ठा snd_soc_component *component)
अणु
	twl6040_पढ़ो(component, TWL6040_REG_TRIM1);
	twl6040_पढ़ो(component, TWL6040_REG_TRIM2);
	twl6040_पढ़ो(component, TWL6040_REG_TRIM3);
	twl6040_पढ़ो(component, TWL6040_REG_HSOTRIM);
	twl6040_पढ़ो(component, TWL6040_REG_HFOTRIM);

	/* Change chip शेषs */
	/* No imput selected क्रम microphone amplअगरiers */
	twl6040_ग_लिखो(component, TWL6040_REG_MICLCTL, 0x18);
	twl6040_ग_लिखो(component, TWL6040_REG_MICRCTL, 0x18);

	/*
	 * We need to lower the शेष gain values, so the ramp code
	 * can work correctly क्रम the first playback.
	 * This reduces the pop noise heard at the first playback.
	 */
	twl6040_ग_लिखो(component, TWL6040_REG_HSGAIN, 0xff);
	twl6040_ग_लिखो(component, TWL6040_REG_EARCTL, 0x1e);
	twl6040_ग_लिखो(component, TWL6040_REG_HFLGAIN, 0x1d);
	twl6040_ग_लिखो(component, TWL6040_REG_HFRGAIN, 0x1d);
	twl6040_ग_लिखो(component, TWL6040_REG_LINEGAIN, 0);
पूर्ण

/* set headset dac and driver घातer mode */
अटल पूर्णांक headset_घातer_mode(काष्ठा snd_soc_component *component, पूर्णांक high_perf)
अणु
	पूर्णांक hslctl, hsrctl;
	पूर्णांक mask = TWL6040_HSDRVMODE | TWL6040_HSDACMODE;

	hslctl = twl6040_पढ़ो(component, TWL6040_REG_HSLCTL);
	hsrctl = twl6040_पढ़ो(component, TWL6040_REG_HSRCTL);

	अगर (high_perf) अणु
		hslctl &= ~mask;
		hsrctl &= ~mask;
	पूर्ण अन्यथा अणु
		hslctl |= mask;
		hsrctl |= mask;
	पूर्ण

	twl6040_ग_लिखो(component, TWL6040_REG_HSLCTL, hslctl);
	twl6040_ग_लिखो(component, TWL6040_REG_HSRCTL, hsrctl);

	वापस 0;
पूर्ण

अटल पूर्णांक twl6040_hs_dac_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u8 hslctl, hsrctl;

	/*
	 * Workaround क्रम Headset DC offset caused pop noise:
	 * Both HS DAC need to be turned on (beक्रमe the HS driver) and off at
	 * the same समय.
	 */
	hslctl = twl6040_पढ़ो(component, TWL6040_REG_HSLCTL);
	hsrctl = twl6040_पढ़ो(component, TWL6040_REG_HSRCTL);
	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		hslctl |= TWL6040_HSDACENA;
		hsrctl |= TWL6040_HSDACENA;
	पूर्ण अन्यथा अणु
		hslctl &= ~TWL6040_HSDACENA;
		hsrctl &= ~TWL6040_HSDACENA;
	पूर्ण
	twl6040_ग_लिखो(component, TWL6040_REG_HSLCTL, hslctl);
	twl6040_ग_लिखो(component, TWL6040_REG_HSRCTL, hsrctl);

	msleep(1);
	वापस 0;
पूर्ण

अटल पूर्णांक twl6040_ep_drv_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		/* Earphone करोesn't support low घातer mode */
		priv->hs_घातer_mode_locked = 1;
		ret = headset_घातer_mode(component, 1);
	पूर्ण अन्यथा अणु
		priv->hs_घातer_mode_locked = 0;
		ret = headset_घातer_mode(component, priv->hs_घातer_mode);
	पूर्ण

	msleep(1);

	वापस ret;
पूर्ण

अटल व्योम twl6040_hs_jack_report(काष्ठा snd_soc_component *component,
				   काष्ठा snd_soc_jack *jack, पूर्णांक report)
अणु
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक status;

	mutex_lock(&priv->mutex);

	/* Sync status */
	status = twl6040_पढ़ो(component, TWL6040_REG_STATUS);
	अगर (status & TWL6040_PLUGCOMP)
		snd_soc_jack_report(jack, report, report);
	अन्यथा
		snd_soc_jack_report(jack, 0, report);

	mutex_unlock(&priv->mutex);
पूर्ण

व्योम twl6040_hs_jack_detect(काष्ठा snd_soc_component *component,
				काष्ठा snd_soc_jack *jack, पूर्णांक report)
अणु
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);
	काष्ठा twl6040_jack_data *hs_jack = &priv->hs_jack;

	hs_jack->jack = jack;
	hs_jack->report = report;

	twl6040_hs_jack_report(component, hs_jack->jack, hs_jack->report);
पूर्ण
EXPORT_SYMBOL_GPL(twl6040_hs_jack_detect);

अटल व्योम twl6040_accessory_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा twl6040_data *priv = container_of(work,
					काष्ठा twl6040_data, hs_jack.work.work);
	काष्ठा snd_soc_component *component = priv->component;
	काष्ठा twl6040_jack_data *hs_jack = &priv->hs_jack;

	twl6040_hs_jack_report(component, hs_jack->jack, hs_jack->report);
पूर्ण

/* audio पूर्णांकerrupt handler */
अटल irqवापस_t twl6040_audio_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा snd_soc_component *component = data;
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &priv->hs_jack.work, msecs_to_jअगरfies(200));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक twl6040_soc_dapm_put_vibra_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक val;

	/* Do not allow changes जबतक Input/FF efect is running */
	val = twl6040_पढ़ो(component, e->reg);
	अगर (val & TWL6040_VIBENA && !(val & TWL6040_VIBSEL))
		वापस -EBUSY;

	वापस snd_soc_dapm_put_क्रमागत_द्विगुन(kcontrol, ucontrol);
पूर्ण

/*
 * MICATT volume control:
 * from -6 to 0 dB in 6 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(mic_preamp_tlv, -600, 600, 0);

/*
 * MICGAIN volume control:
 * from 6 to 30 dB in 6 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(mic_amp_tlv, 600, 600, 0);

/*
 * AFMGAIN volume control:
 * from -18 to 24 dB in 6 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(afm_amp_tlv, -1800, 600, 0);

/*
 * HSGAIN volume control:
 * from -30 to 0 dB in 2 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(hs_tlv, -3000, 200, 0);

/*
 * HFGAIN volume control:
 * from -52 to 6 dB in 2 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(hf_tlv, -5200, 200, 0);

/*
 * EPGAIN volume control:
 * from -24 to 6 dB in 2 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(ep_tlv, -2400, 200, 0);

/* Left analog microphone selection */
अटल स्थिर अक्षर *twl6040_amicl_texts[] =
	अणु"Headset Mic", "Main Mic", "Aux/FM Left", "Off"पूर्ण;

/* Right analog microphone selection */
अटल स्थिर अक्षर *twl6040_amicr_texts[] =
	अणु"Headset Mic", "Sub Mic", "Aux/FM Right", "Off"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत twl6040_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(TWL6040_REG_MICLCTL, 3,
			ARRAY_SIZE(twl6040_amicl_texts), twl6040_amicl_texts),
	SOC_ENUM_SINGLE(TWL6040_REG_MICRCTL, 3,
			ARRAY_SIZE(twl6040_amicr_texts), twl6040_amicr_texts),
पूर्ण;

अटल स्थिर अक्षर *twl6040_hs_texts[] = अणु
	"Off", "HS DAC", "Line-In amp"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत twl6040_hs_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(TWL6040_REG_HSLCTL, 5, ARRAY_SIZE(twl6040_hs_texts),
			twl6040_hs_texts),
	SOC_ENUM_SINGLE(TWL6040_REG_HSRCTL, 5, ARRAY_SIZE(twl6040_hs_texts),
			twl6040_hs_texts),
पूर्ण;

अटल स्थिर अक्षर *twl6040_hf_texts[] = अणु
	"Off", "HF DAC", "Line-In amp"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत twl6040_hf_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(TWL6040_REG_HFLCTL, 2, ARRAY_SIZE(twl6040_hf_texts),
			twl6040_hf_texts),
	SOC_ENUM_SINGLE(TWL6040_REG_HFRCTL, 2, ARRAY_SIZE(twl6040_hf_texts),
			twl6040_hf_texts),
पूर्ण;

अटल स्थिर अक्षर *twl6040_vibrapath_texts[] = अणु
	"Input FF", "Audio PDM"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत twl6040_vibra_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(TWL6040_REG_VIBCTLL, 1,
			ARRAY_SIZE(twl6040_vibrapath_texts),
			twl6040_vibrapath_texts),
	SOC_ENUM_SINGLE(TWL6040_REG_VIBCTLR, 1,
			ARRAY_SIZE(twl6040_vibrapath_texts),
			twl6040_vibrapath_texts),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new amicl_control =
	SOC_DAPM_ENUM("Route", twl6040_क्रमागत[0]);

अटल स्थिर काष्ठा snd_kcontrol_new amicr_control =
	SOC_DAPM_ENUM("Route", twl6040_क्रमागत[1]);

/* Headset DAC playback चयनes */
अटल स्थिर काष्ठा snd_kcontrol_new hsl_mux_controls =
	SOC_DAPM_ENUM("Route", twl6040_hs_क्रमागत[0]);

अटल स्थिर काष्ठा snd_kcontrol_new hsr_mux_controls =
	SOC_DAPM_ENUM("Route", twl6040_hs_क्रमागत[1]);

/* Handsमुक्त DAC playback चयनes */
अटल स्थिर काष्ठा snd_kcontrol_new hfl_mux_controls =
	SOC_DAPM_ENUM("Route", twl6040_hf_क्रमागत[0]);

अटल स्थिर काष्ठा snd_kcontrol_new hfr_mux_controls =
	SOC_DAPM_ENUM("Route", twl6040_hf_क्रमागत[1]);

अटल स्थिर काष्ठा snd_kcontrol_new ep_path_enable_control =
	SOC_DAPM_SINGLE_VIRT("Switch", 1);

अटल स्थिर काष्ठा snd_kcontrol_new auxl_चयन_control =
	SOC_DAPM_SINGLE("Switch", TWL6040_REG_HFLCTL, 6, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new auxr_चयन_control =
	SOC_DAPM_SINGLE("Switch", TWL6040_REG_HFRCTL, 6, 1, 0);

/* Vibra playback चयनes */
अटल स्थिर काष्ठा snd_kcontrol_new vibral_mux_controls =
	SOC_DAPM_ENUM_EXT("Route", twl6040_vibra_क्रमागत[0],
		snd_soc_dapm_get_क्रमागत_द्विगुन,
		twl6040_soc_dapm_put_vibra_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new vibrar_mux_controls =
	SOC_DAPM_ENUM_EXT("Route", twl6040_vibra_क्रमागत[1],
		snd_soc_dapm_get_क्रमागत_द्विगुन,
		twl6040_soc_dapm_put_vibra_क्रमागत);

/* Headset घातer mode */
अटल स्थिर अक्षर *twl6040_घातer_mode_texts[] = अणु
	"Low-Power", "High-Performance",
पूर्ण;

अटल SOC_ENUM_SINGLE_EXT_DECL(twl6040_घातer_mode_क्रमागत,
				twl6040_घातer_mode_texts);

अटल पूर्णांक twl6040_headset_घातer_get_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = priv->hs_घातer_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक twl6040_headset_घातer_put_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक high_perf = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक ret = 0;

	अगर (!priv->hs_घातer_mode_locked)
		ret = headset_घातer_mode(component, high_perf);

	अगर (!ret)
		priv->hs_घातer_mode = high_perf;

	वापस ret;
पूर्ण

अटल पूर्णांक twl6040_pll_get_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = priv->pll_घातer_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक twl6040_pll_put_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);

	priv->pll_घातer_mode = ucontrol->value.क्रमागतerated.item[0];

	वापस 0;
पूर्ण

पूर्णांक twl6040_get_dl1_gain(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	अगर (snd_soc_dapm_get_pin_status(dapm, "EP"))
		वापस -1; /* -1dB */

	अगर (snd_soc_dapm_get_pin_status(dapm, "HSOR") ||
		snd_soc_dapm_get_pin_status(dapm, "HSOL")) अणु

		u8 val = twl6040_पढ़ो(component, TWL6040_REG_HSLCTL);
		अगर (val & TWL6040_HSDACMODE)
			/* HSDACL in LP mode */
			वापस -8; /* -8dB */
		अन्यथा
			/* HSDACL in HP mode */
			वापस -1; /* -1dB */
	पूर्ण
	वापस 0; /* 0dB */
पूर्ण
EXPORT_SYMBOL_GPL(twl6040_get_dl1_gain);

पूर्णांक twl6040_get_clk_id(काष्ठा snd_soc_component *component)
अणु
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);

	वापस priv->pll_घातer_mode;
पूर्ण
EXPORT_SYMBOL_GPL(twl6040_get_clk_id);

पूर्णांक twl6040_get_trim_value(काष्ठा snd_soc_component *component, क्रमागत twl6040_trim trim)
अणु
	अगर (unlikely(trim >= TWL6040_TRIM_INVAL))
		वापस -EINVAL;

	वापस twl6040_पढ़ो(component, TWL6040_REG_TRIM1 + trim);
पूर्ण
EXPORT_SYMBOL_GPL(twl6040_get_trim_value);

पूर्णांक twl6040_get_hs_step_size(काष्ठा snd_soc_component *component)
अणु
	काष्ठा twl6040 *twl6040 = to_twl6040(component);

	अगर (twl6040_get_revid(twl6040) < TWL6040_REV_ES1_3)
		/* For ES under ES_1.3 HS step is 2 mV */
		वापस 2;
	अन्यथा
		/* For ES_1.3 HS step is 1 mV */
		वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(twl6040_get_hs_step_size);

अटल स्थिर काष्ठा snd_kcontrol_new twl6040_snd_controls[] = अणु
	/* Capture gains */
	SOC_DOUBLE_TLV("Capture Preamplifier Volume",
		TWL6040_REG_MICGAIN, 6, 7, 1, 1, mic_preamp_tlv),
	SOC_DOUBLE_TLV("Capture Volume",
		TWL6040_REG_MICGAIN, 0, 3, 4, 0, mic_amp_tlv),

	/* AFM gains */
	SOC_DOUBLE_TLV("Aux FM Volume",
		TWL6040_REG_LINEGAIN, 0, 3, 7, 0, afm_amp_tlv),

	/* Playback gains */
	SOC_DOUBLE_TLV("Headset Playback Volume",
		TWL6040_REG_HSGAIN, 0, 4, 0xF, 1, hs_tlv),
	SOC_DOUBLE_R_TLV("Handsfree Playback Volume",
		TWL6040_REG_HFLGAIN, TWL6040_REG_HFRGAIN, 0, 0x1D, 1, hf_tlv),
	SOC_SINGLE_TLV("Earphone Playback Volume",
		TWL6040_REG_EARCTL, 1, 0xF, 1, ep_tlv),

	SOC_ENUM_EXT("Headset Power Mode", twl6040_घातer_mode_क्रमागत,
		twl6040_headset_घातer_get_क्रमागत,
		twl6040_headset_घातer_put_क्रमागत),

	/* Left HS PDM data routed to Right HSDAC */
	SOC_SINGLE("Headset Mono to Stereo Playback Switch",
		TWL6040_REG_HSRCTL, 7, 1, 0),

	/* Left HF PDM data routed to Right HFDAC */
	SOC_SINGLE("Handsfree Mono to Stereo Playback Switch",
		TWL6040_REG_HFRCTL, 5, 1, 0),

	SOC_ENUM_EXT("PLL Selection", twl6040_घातer_mode_क्रमागत,
		twl6040_pll_get_क्रमागत, twl6040_pll_put_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget twl6040_dapm_widमाला_लो[] = अणु
	/* Inमाला_दो */
	SND_SOC_DAPM_INPUT("MAINMIC"),
	SND_SOC_DAPM_INPUT("HSMIC"),
	SND_SOC_DAPM_INPUT("SUBMIC"),
	SND_SOC_DAPM_INPUT("AFML"),
	SND_SOC_DAPM_INPUT("AFMR"),

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("HSOL"),
	SND_SOC_DAPM_OUTPUT("HSOR"),
	SND_SOC_DAPM_OUTPUT("HFL"),
	SND_SOC_DAPM_OUTPUT("HFR"),
	SND_SOC_DAPM_OUTPUT("EP"),
	SND_SOC_DAPM_OUTPUT("AUXL"),
	SND_SOC_DAPM_OUTPUT("AUXR"),
	SND_SOC_DAPM_OUTPUT("VIBRAL"),
	SND_SOC_DAPM_OUTPUT("VIBRAR"),

	/* Analog input muxes क्रम the capture amplअगरiers */
	SND_SOC_DAPM_MUX("Analog Left Capture Route",
			SND_SOC_NOPM, 0, 0, &amicl_control),
	SND_SOC_DAPM_MUX("Analog Right Capture Route",
			SND_SOC_NOPM, 0, 0, &amicr_control),

	/* Analog capture PGAs */
	SND_SOC_DAPM_PGA("MicAmpL",
			TWL6040_REG_MICLCTL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MicAmpR",
			TWL6040_REG_MICRCTL, 0, 0, शून्य, 0),

	/* Auxiliary FM PGAs */
	SND_SOC_DAPM_PGA("AFMAmpL",
			TWL6040_REG_MICLCTL, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("AFMAmpR",
			TWL6040_REG_MICRCTL, 1, 0, शून्य, 0),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC Left", शून्य, TWL6040_REG_MICLCTL, 2, 0),
	SND_SOC_DAPM_ADC("ADC Right", शून्य, TWL6040_REG_MICRCTL, 2, 0),

	/* Microphone bias */
	SND_SOC_DAPM_SUPPLY("Headset Mic Bias",
			    TWL6040_REG_AMICBCTL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Main Mic Bias",
			    TWL6040_REG_AMICBCTL, 4, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Digital Mic1 Bias",
			    TWL6040_REG_DMICBCTL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Digital Mic2 Bias",
			    TWL6040_REG_DMICBCTL, 4, 0, शून्य, 0),

	/* DACs */
	SND_SOC_DAPM_DAC("HSDAC Left", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("HSDAC Right", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("HFDAC Left", शून्य, TWL6040_REG_HFLCTL, 0, 0),
	SND_SOC_DAPM_DAC("HFDAC Right", शून्य, TWL6040_REG_HFRCTL, 0, 0),
	/* Virtual DAC क्रम vibra path (DL4 channel) */
	SND_SOC_DAPM_DAC("VIBRA DAC", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MUX("Handsfree Left Playback",
			SND_SOC_NOPM, 0, 0, &hfl_mux_controls),
	SND_SOC_DAPM_MUX("Handsfree Right Playback",
			SND_SOC_NOPM, 0, 0, &hfr_mux_controls),
	/* Analog playback Muxes */
	SND_SOC_DAPM_MUX("Headset Left Playback",
			SND_SOC_NOPM, 0, 0, &hsl_mux_controls),
	SND_SOC_DAPM_MUX("Headset Right Playback",
			SND_SOC_NOPM, 0, 0, &hsr_mux_controls),

	SND_SOC_DAPM_MUX("Vibra Left Playback", SND_SOC_NOPM, 0, 0,
			&vibral_mux_controls),
	SND_SOC_DAPM_MUX("Vibra Right Playback", SND_SOC_NOPM, 0, 0,
			&vibrar_mux_controls),

	SND_SOC_DAPM_SWITCH("Earphone Playback", SND_SOC_NOPM, 0, 0,
			&ep_path_enable_control),
	SND_SOC_DAPM_SWITCH("AUXL Playback", SND_SOC_NOPM, 0, 0,
			&auxl_चयन_control),
	SND_SOC_DAPM_SWITCH("AUXR Playback", SND_SOC_NOPM, 0, 0,
			&auxr_चयन_control),

	/* Analog playback drivers */
	SND_SOC_DAPM_OUT_DRV("HF Left Driver",
			TWL6040_REG_HFLCTL, 4, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("HF Right Driver",
			TWL6040_REG_HFRCTL, 4, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("HS Left Driver",
			TWL6040_REG_HSLCTL, 2, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("HS Right Driver",
			TWL6040_REG_HSRCTL, 2, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV_E("Earphone Driver",
			TWL6040_REG_EARCTL, 0, 0, शून्य, 0,
			twl6040_ep_drv_event,
			SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUT_DRV("Vibra Left Driver",
			TWL6040_REG_VIBCTLL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Vibra Right Driver",
			TWL6040_REG_VIBCTLR, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Vibra Left Control", TWL6040_REG_VIBCTLL, 2, 0,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Vibra Right Control", TWL6040_REG_VIBCTLR, 2, 0,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("HSDAC Power", 1, SND_SOC_NOPM, 0, 0,
			      twl6040_hs_dac_event,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	/* Analog playback PGAs */
	SND_SOC_DAPM_PGA("HF Left PGA",
			TWL6040_REG_HFLCTL, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HF Right PGA",
			TWL6040_REG_HFRCTL, 1, 0, शून्य, 0),

पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon[] = अणु
	/* Stream -> DAC mapping */
	अणु"HSDAC Left", शून्य, "Legacy Playback"पूर्ण,
	अणु"HSDAC Left", शून्य, "Headset Playback"पूर्ण,
	अणु"HSDAC Right", शून्य, "Legacy Playback"पूर्ण,
	अणु"HSDAC Right", शून्य, "Headset Playback"पूर्ण,

	अणु"HFDAC Left", शून्य, "Legacy Playback"पूर्ण,
	अणु"HFDAC Left", शून्य, "Handsfree Playback"पूर्ण,
	अणु"HFDAC Right", शून्य, "Legacy Playback"पूर्ण,
	अणु"HFDAC Right", शून्य, "Handsfree Playback"पूर्ण,

	अणु"VIBRA DAC", शून्य, "Legacy Playback"पूर्ण,
	अणु"VIBRA DAC", शून्य, "Vibra Playback"पूर्ण,

	/* ADC -> Stream mapping */
	अणु"Legacy Capture" , शून्य, "ADC Left"पूर्ण,
	अणु"Capture", शून्य, "ADC Left"पूर्ण,
	अणु"Legacy Capture", शून्य, "ADC Right"पूर्ण,
	अणु"Capture" , शून्य, "ADC Right"पूर्ण,

	/* Capture path */
	अणु"Analog Left Capture Route", "Headset Mic", "HSMIC"पूर्ण,
	अणु"Analog Left Capture Route", "Main Mic", "MAINMIC"पूर्ण,
	अणु"Analog Left Capture Route", "Aux/FM Left", "AFML"पूर्ण,

	अणु"Analog Right Capture Route", "Headset Mic", "HSMIC"पूर्ण,
	अणु"Analog Right Capture Route", "Sub Mic", "SUBMIC"पूर्ण,
	अणु"Analog Right Capture Route", "Aux/FM Right", "AFMR"पूर्ण,

	अणु"MicAmpL", शून्य, "Analog Left Capture Route"पूर्ण,
	अणु"MicAmpR", शून्य, "Analog Right Capture Route"पूर्ण,

	अणु"ADC Left", शून्य, "MicAmpL"पूर्ण,
	अणु"ADC Right", शून्य, "MicAmpR"पूर्ण,

	/* AFM path */
	अणु"AFMAmpL", शून्य, "AFML"पूर्ण,
	अणु"AFMAmpR", शून्य, "AFMR"पूर्ण,

	अणु"HSDAC Left", शून्य, "HSDAC Power"पूर्ण,
	अणु"HSDAC Right", शून्य, "HSDAC Power"पूर्ण,

	अणु"Headset Left Playback", "HS DAC", "HSDAC Left"पूर्ण,
	अणु"Headset Left Playback", "Line-In amp", "AFMAmpL"पूर्ण,

	अणु"Headset Right Playback", "HS DAC", "HSDAC Right"पूर्ण,
	अणु"Headset Right Playback", "Line-In amp", "AFMAmpR"पूर्ण,

	अणु"HS Left Driver", शून्य, "Headset Left Playback"पूर्ण,
	अणु"HS Right Driver", शून्य, "Headset Right Playback"पूर्ण,

	अणु"HSOL", शून्य, "HS Left Driver"पूर्ण,
	अणु"HSOR", शून्य, "HS Right Driver"पूर्ण,

	/* Earphone playback path */
	अणु"Earphone Playback", "Switch", "HSDAC Left"पूर्ण,
	अणु"Earphone Driver", शून्य, "Earphone Playback"पूर्ण,
	अणु"EP", शून्य, "Earphone Driver"पूर्ण,

	अणु"Handsfree Left Playback", "HF DAC", "HFDAC Left"पूर्ण,
	अणु"Handsfree Left Playback", "Line-In amp", "AFMAmpL"पूर्ण,

	अणु"Handsfree Right Playback", "HF DAC", "HFDAC Right"पूर्ण,
	अणु"Handsfree Right Playback", "Line-In amp", "AFMAmpR"पूर्ण,

	अणु"HF Left PGA", शून्य, "Handsfree Left Playback"पूर्ण,
	अणु"HF Right PGA", शून्य, "Handsfree Right Playback"पूर्ण,

	अणु"HF Left Driver", शून्य, "HF Left PGA"पूर्ण,
	अणु"HF Right Driver", शून्य, "HF Right PGA"पूर्ण,

	अणु"HFL", शून्य, "HF Left Driver"पूर्ण,
	अणु"HFR", शून्य, "HF Right Driver"पूर्ण,

	अणु"AUXL Playback", "Switch", "HF Left PGA"पूर्ण,
	अणु"AUXR Playback", "Switch", "HF Right PGA"पूर्ण,

	अणु"AUXL", शून्य, "AUXL Playback"पूर्ण,
	अणु"AUXR", शून्य, "AUXR Playback"पूर्ण,

	/* Vibrator paths */
	अणु"Vibra Left Playback", "Audio PDM", "VIBRA DAC"पूर्ण,
	अणु"Vibra Right Playback", "Audio PDM", "VIBRA DAC"पूर्ण,

	अणु"Vibra Left Driver", शून्य, "Vibra Left Playback"पूर्ण,
	अणु"Vibra Right Driver", शून्य, "Vibra Right Playback"पूर्ण,
	अणु"Vibra Left Driver", शून्य, "Vibra Left Control"पूर्ण,
	अणु"Vibra Right Driver", शून्य, "Vibra Right Control"पूर्ण,

	अणु"VIBRAL", शून्य, "Vibra Left Driver"पूर्ण,
	अणु"VIBRAR", शून्य, "Vibra Right Driver"पूर्ण,
पूर्ण;

अटल पूर्णांक twl6040_set_bias_level(काष्ठा snd_soc_component *component,
				क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा twl6040 *twl6040 = to_twl6040(component);
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (priv->codec_घातered) अणु
			/* Select low घातer PLL in standby */
			ret = twl6040_set_pll(twl6040, TWL6040_SYSCLK_SEL_LPPLL,
					      32768, 19200000);
			अवरोध;
		पूर्ण

		ret = twl6040_घातer(twl6040, 1);
		अगर (ret)
			अवरोध;

		priv->codec_घातered = 1;

		/* Set बाह्यal boost GPO */
		twl6040_ग_लिखो(component, TWL6040_REG_GPOCTL, 0x02);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		अगर (!priv->codec_घातered)
			अवरोध;

		twl6040_घातer(twl6040, 0);
		priv->codec_घातered = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक twl6040_startup(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE,
				&sysclk_स्थिरraपूर्णांकs[priv->pll_घातer_mode]);

	वापस 0;
पूर्ण

अटल पूर्णांक twl6040_hw_params(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_pcm_hw_params *params,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक rate;

	rate = params_rate(params);
	चयन (rate) अणु
	हाल 11250:
	हाल 22500:
	हाल 44100:
	हाल 88200:
		/* These rates are not supported when HPPLL is in use */
		अगर (unlikely(priv->pll == TWL6040_SYSCLK_SEL_HPPLL)) अणु
			dev_err(component->dev, "HPPLL does not support rate %d\n",
				rate);
			वापस -EINVAL;
		पूर्ण
		priv->sysclk = 17640000;
		अवरोध;
	हाल 8000:
	हाल 16000:
	हाल 32000:
	हाल 48000:
	हाल 96000:
		priv->sysclk = 19200000;
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported rate %d\n", rate);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक twl6040_prepare(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा twl6040 *twl6040 = to_twl6040(component);
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	अगर (!priv->sysclk) अणु
		dev_err(component->dev,
			"no mclk configured, call set_sysclk() on init\n");
		वापस -EINVAL;
	पूर्ण

	ret = twl6040_set_pll(twl6040, priv->pll, priv->clk_in, priv->sysclk);
	अगर (ret) अणु
		dev_err(component->dev, "Can not set PLL (%d)\n", ret);
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक twl6040_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल TWL6040_SYSCLK_SEL_LPPLL:
	हाल TWL6040_SYSCLK_SEL_HPPLL:
		priv->pll = clk_id;
		priv->clk_in = freq;
		अवरोध;
	शेष:
		dev_err(component->dev, "unknown clk_id %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम twl6040_mute_path(काष्ठा snd_soc_component *component, क्रमागत twl6040_dai_id id,
			     पूर्णांक mute)
अणु
	काष्ठा twl6040 *twl6040 = to_twl6040(component);
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक hslctl, hsrctl, earctl;
	पूर्णांक hflctl, hfrctl;

	चयन (id) अणु
	हाल TWL6040_DAI_DL1:
		hslctl = twl6040_पढ़ो(component, TWL6040_REG_HSLCTL);
		hsrctl = twl6040_पढ़ो(component, TWL6040_REG_HSRCTL);
		earctl = twl6040_पढ़ो(component, TWL6040_REG_EARCTL);

		अगर (mute) अणु
			/* Power करोwn drivers and DACs */
			earctl &= ~0x01;
			hslctl &= ~(TWL6040_HSDRVENA | TWL6040_HSDACENA);
			hsrctl &= ~(TWL6040_HSDRVENA | TWL6040_HSDACENA);

		पूर्ण

		twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_EARCTL, earctl);
		twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_HSLCTL, hslctl);
		twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_HSRCTL, hsrctl);
		priv->dl1_unmuted = !mute;
		अवरोध;
	हाल TWL6040_DAI_DL2:
		hflctl = twl6040_पढ़ो(component, TWL6040_REG_HFLCTL);
		hfrctl = twl6040_पढ़ो(component, TWL6040_REG_HFRCTL);

		अगर (mute) अणु
			/* Power करोwn drivers and DACs */
			hflctl &= ~(TWL6040_HFDACENA | TWL6040_HFPGAENA |
				    TWL6040_HFDRVENA | TWL6040_HFSWENA);
			hfrctl &= ~(TWL6040_HFDACENA | TWL6040_HFPGAENA |
				    TWL6040_HFDRVENA | TWL6040_HFSWENA);
		पूर्ण

		twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_HFLCTL, hflctl);
		twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_HFRCTL, hfrctl);
		priv->dl2_unmuted = !mute;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक twl6040_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	चयन (dai->id) अणु
	हाल TWL6040_DAI_LEGACY:
		twl6040_mute_path(dai->component, TWL6040_DAI_DL1, mute);
		twl6040_mute_path(dai->component, TWL6040_DAI_DL2, mute);
		अवरोध;
	हाल TWL6040_DAI_DL1:
	हाल TWL6040_DAI_DL2:
		twl6040_mute_path(dai->component, dai->id, mute);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops twl6040_dai_ops = अणु
	.startup	= twl6040_startup,
	.hw_params	= twl6040_hw_params,
	.prepare	= twl6040_prepare,
	.set_sysclk	= twl6040_set_dai_sysclk,
	.mute_stream	= twl6040_mute_stream,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver twl6040_dai[] = अणु
अणु
	.name = "twl6040-legacy",
	.id = TWL6040_DAI_LEGACY,
	.playback = अणु
		.stream_name = "Legacy Playback",
		.channels_min = 1,
		.channels_max = 5,
		.rates = TWL6040_RATES,
		.क्रमmats = TWL6040_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Legacy Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = TWL6040_RATES,
		.क्रमmats = TWL6040_FORMATS,
	पूर्ण,
	.ops = &twl6040_dai_ops,
पूर्ण,
अणु
	.name = "twl6040-ul",
	.id = TWL6040_DAI_UL,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = TWL6040_RATES,
		.क्रमmats = TWL6040_FORMATS,
	पूर्ण,
	.ops = &twl6040_dai_ops,
पूर्ण,
अणु
	.name = "twl6040-dl1",
	.id = TWL6040_DAI_DL1,
	.playback = अणु
		.stream_name = "Headset Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = TWL6040_RATES,
		.क्रमmats = TWL6040_FORMATS,
	पूर्ण,
	.ops = &twl6040_dai_ops,
पूर्ण,
अणु
	.name = "twl6040-dl2",
	.id = TWL6040_DAI_DL2,
	.playback = अणु
		.stream_name = "Handsfree Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = TWL6040_RATES,
		.क्रमmats = TWL6040_FORMATS,
	पूर्ण,
	.ops = &twl6040_dai_ops,
पूर्ण,
अणु
	.name = "twl6040-vib",
	.id = TWL6040_DAI_VIB,
	.playback = अणु
		.stream_name = "Vibra Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.क्रमmats = TWL6040_FORMATS,
	पूर्ण,
	.ops = &twl6040_dai_ops,
पूर्ण,
पूर्ण;

अटल पूर्णांक twl6040_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा twl6040_data *priv;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(component->dev);
	पूर्णांक ret = 0;

	priv = devm_kzalloc(component->dev, माप(*priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस -ENOMEM;

	snd_soc_component_set_drvdata(component, priv);

	priv->component = component;

	priv->plug_irq = platक्रमm_get_irq(pdev, 0);
	अगर (priv->plug_irq < 0)
		वापस priv->plug_irq;

	INIT_DELAYED_WORK(&priv->hs_jack.work, twl6040_accessory_work);

	mutex_init(&priv->mutex);

	ret = request_thपढ़ोed_irq(priv->plug_irq, शून्य,
					twl6040_audio_handler,
					IRQF_NO_SUSPEND | IRQF_ONESHOT,
					"twl6040_irq_plug", component);
	अगर (ret) अणु
		dev_err(component->dev, "PLUG IRQ request failed: %d\n", ret);
		वापस ret;
	पूर्ण

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);
	twl6040_init_chip(component);

	वापस 0;
पूर्ण

अटल व्योम twl6040_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा twl6040_data *priv = snd_soc_component_get_drvdata(component);

	मुक्त_irq(priv->plug_irq, component);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_twl6040 = अणु
	.probe			= twl6040_probe,
	.हटाओ			= twl6040_हटाओ,
	.पढ़ो			= twl6040_पढ़ो,
	.ग_लिखो			= twl6040_ग_लिखो,
	.set_bias_level		= twl6040_set_bias_level,
	.controls		= twl6040_snd_controls,
	.num_controls		= ARRAY_SIZE(twl6040_snd_controls),
	.dapm_widमाला_लो		= twl6040_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(twl6040_dapm_widमाला_लो),
	.dapm_routes		= पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(पूर्णांकercon),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक twl6040_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				      &soc_component_dev_twl6040,
				      twl6040_dai, ARRAY_SIZE(twl6040_dai));
पूर्ण

अटल काष्ठा platक्रमm_driver twl6040_codec_driver = अणु
	.driver = अणु
		.name = "twl6040-codec",
	पूर्ण,
	.probe = twl6040_codec_probe,
पूर्ण;

module_platक्रमm_driver(twl6040_codec_driver);

MODULE_DESCRIPTION("ASoC TWL6040 codec driver");
MODULE_AUTHOR("Misael Lopez Cruz");
MODULE_LICENSE("GPL");
