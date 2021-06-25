<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cx20442.c  --  CX20442 ALSA Soc Audio driver
 *
 * Copyright 2009 Janusz Krzysztofik <jkrzyszt@tis.icnet.pl>
 *
 * Initially based on sound/soc/codecs/wm8400.c
 * Copyright 2008, 2009 Wolfson Microelectronics PLC.
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/tty.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

#समावेश "cx20442.h"


काष्ठा cx20442_priv अणु
	काष्ठा tty_काष्ठा *tty;
	काष्ठा regulator *por;
	u8 reg_cache;
पूर्ण;

#घोषणा CX20442_PM		0x0

#घोषणा CX20442_TELIN		0
#घोषणा CX20442_TELOUT		1
#घोषणा CX20442_MIC		2
#घोषणा CX20442_SPKOUT		3
#घोषणा CX20442_AGC		4

अटल स्थिर काष्ठा snd_soc_dapm_widget cx20442_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("TELOUT"),
	SND_SOC_DAPM_OUTPUT("SPKOUT"),
	SND_SOC_DAPM_OUTPUT("AGCOUT"),

	SND_SOC_DAPM_MIXER("SPKOUT Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("TELOUT Amp", CX20442_PM, CX20442_TELOUT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SPKOUT Amp", CX20442_PM, CX20442_SPKOUT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SPKOUT AGC", CX20442_PM, CX20442_AGC, 0, शून्य, 0),

	SND_SOC_DAPM_DAC("DAC", "Playback", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC", "Capture", SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MIXER("Input Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_MICBIAS("TELIN Bias", CX20442_PM, CX20442_TELIN, 0),
	SND_SOC_DAPM_MICBIAS("MIC Bias", CX20442_PM, CX20442_MIC, 0),

	SND_SOC_DAPM_PGA("MIC AGC", CX20442_PM, CX20442_AGC, 0, शून्य, 0),

	SND_SOC_DAPM_INPUT("TELIN"),
	SND_SOC_DAPM_INPUT("MIC"),
	SND_SOC_DAPM_INPUT("AGCIN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cx20442_audio_map[] = अणु
	अणु"TELOUT", शून्य, "TELOUT Amp"पूर्ण,

	अणु"SPKOUT", शून्य, "SPKOUT Mixer"पूर्ण,
	अणु"SPKOUT Mixer", शून्य, "SPKOUT Amp"पूर्ण,

	अणु"TELOUT Amp", शून्य, "DAC"पूर्ण,
	अणु"SPKOUT Amp", शून्य, "DAC"पूर्ण,

	अणु"SPKOUT Mixer", शून्य, "SPKOUT AGC"पूर्ण,
	अणु"SPKOUT AGC", शून्य, "AGCIN"पूर्ण,

	अणु"AGCOUT", शून्य, "MIC AGC"पूर्ण,
	अणु"MIC AGC", शून्य, "MIC"पूर्ण,

	अणु"MIC Bias", शून्य, "MIC"पूर्ण,
	अणु"Input Mixer", शून्य, "MIC Bias"पूर्ण,

	अणु"TELIN Bias", शून्य, "TELIN"पूर्ण,
	अणु"Input Mixer", शून्य, "TELIN Bias"पूर्ण,

	अणु"ADC", शून्य, "Input Mixer"पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक cx20442_पढ़ो_reg_cache(काष्ठा snd_soc_component *component,
					   अचिन्हित पूर्णांक reg)
अणु
	काष्ठा cx20442_priv *cx20442 = snd_soc_component_get_drvdata(component);

	अगर (reg >= 1)
		वापस -EINVAL;

	वापस cx20442->reg_cache;
पूर्ण

क्रमागत v253_vls अणु
	V253_VLS_NONE = 0,
	V253_VLS_T,
	V253_VLS_L,
	V253_VLS_LT,
	V253_VLS_S,
	V253_VLS_ST,
	V253_VLS_M,
	V253_VLS_MST,
	V253_VLS_S1,
	V253_VLS_S1T,
	V253_VLS_MS1T,
	V253_VLS_M1,
	V253_VLS_M1ST,
	V253_VLS_M1S1T,
	V253_VLS_H,
	V253_VLS_HT,
	V253_VLS_MS,
	V253_VLS_MS1,
	V253_VLS_M1S,
	V253_VLS_M1S1,
	V253_VLS_TEST,
पूर्ण;

अटल पूर्णांक cx20442_pm_to_v253_vls(u8 value)
अणु
	चयन (value & ~(1 << CX20442_AGC)) अणु
	हाल 0:
		वापस V253_VLS_T;
	हाल (1 << CX20442_SPKOUT):
	हाल (1 << CX20442_MIC):
	हाल (1 << CX20442_SPKOUT) | (1 << CX20442_MIC):
		वापस V253_VLS_M1S1;
	हाल (1 << CX20442_TELOUT):
	हाल (1 << CX20442_TELIN):
	हाल (1 << CX20442_TELOUT) | (1 << CX20442_TELIN):
		वापस V253_VLS_L;
	हाल (1 << CX20442_TELOUT) | (1 << CX20442_MIC):
		वापस V253_VLS_NONE;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल पूर्णांक cx20442_pm_to_v253_vsp(u8 value)
अणु
	चयन (value & ~(1 << CX20442_AGC)) अणु
	हाल (1 << CX20442_SPKOUT):
	हाल (1 << CX20442_MIC):
	हाल (1 << CX20442_SPKOUT) | (1 << CX20442_MIC):
		वापस (bool)(value & (1 << CX20442_AGC));
	पूर्ण
	वापस (value & (1 << CX20442_AGC)) ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक cx20442_ग_लिखो(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक reg,
							अचिन्हित पूर्णांक value)
अणु
	काष्ठा cx20442_priv *cx20442 = snd_soc_component_get_drvdata(component);
	पूर्णांक vls, vsp, old, len;
	अक्षर buf[18];

	अगर (reg >= 1)
		वापस -EINVAL;

	/* tty and ग_लिखो poपूर्णांकers required क्रम talking to the modem
	 * are expected to be set by the line discipline initialization code */
	अगर (!cx20442->tty || !cx20442->tty->ops->ग_लिखो)
		वापस -EIO;

	old = cx20442->reg_cache;
	cx20442->reg_cache = value;

	vls = cx20442_pm_to_v253_vls(value);
	अगर (vls < 0)
		वापस vls;

	vsp = cx20442_pm_to_v253_vsp(value);
	अगर (vsp < 0)
		वापस vsp;

	अगर ((vls == V253_VLS_T) ||
			(vls == cx20442_pm_to_v253_vls(old))) अणु
		अगर (vsp == cx20442_pm_to_v253_vsp(old))
			वापस 0;
		len = snम_लिखो(buf, ARRAY_SIZE(buf), "at+vsp=%d\r", vsp);
	पूर्ण अन्यथा अगर (vsp == cx20442_pm_to_v253_vsp(old))
		len = snम_लिखो(buf, ARRAY_SIZE(buf), "at+vls=%d\r", vls);
	अन्यथा
		len = snम_लिखो(buf, ARRAY_SIZE(buf),
					"at+vls=%d;+vsp=%d\r", vls, vsp);

	अगर (unlikely(len > (ARRAY_SIZE(buf) - 1)))
		वापस -ENOMEM;

	dev_dbg(component->dev, "%s: %s\n", __func__, buf);
	अगर (cx20442->tty->ops->ग_लिखो(cx20442->tty, buf, len) != len)
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * Line discpline related code
 *
 * Any of the callback functions below can be used in two ways:
 * 1) रेजिस्टरd by a machine driver as one of line discipline operations,
 * 2) called from a machine's provided line discipline callback function
 *    in हाल when extra machine specअगरic code must be run as well.
 */

/* Modem init: echo off, digital speaker off, quiet off, voice mode */
अटल स्थिर अक्षर *v253_init = "ate0m0q0+fclass=8\r";

/* Line discipline .खोलो() */
अटल पूर्णांक v253_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक ret, len = म_माप(v253_init);

	/* Doesn't make sense without ग_लिखो callback */
	अगर (!tty->ops->ग_लिखो)
		वापस -EINVAL;

	/* Won't work अगर no codec poपूर्णांकer has been passed by a card driver */
	अगर (!tty->disc_data)
		वापस -ENODEV;

	tty->receive_room = 16;
	अगर (tty->ops->ग_लिखो(tty, v253_init, len) != len) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण
	/* Actual setup will be perक्रमmed after the modem responds. */
	वापस 0;
err:
	tty->disc_data = शून्य;
	वापस ret;
पूर्ण

/* Line discipline .बंद() */
अटल व्योम v253_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा snd_soc_component *component = tty->disc_data;
	काष्ठा cx20442_priv *cx20442;

	tty->disc_data = शून्य;

	अगर (!component)
		वापस;

	cx20442 = snd_soc_component_get_drvdata(component);

	/* Prevent the codec driver from further accessing the modem */
	cx20442->tty = शून्य;
	component->card->pop_समय = 0;
पूर्ण

/* Line discipline .hangup() */
अटल पूर्णांक v253_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	v253_बंद(tty);
	वापस 0;
पूर्ण

/* Line discipline .receive_buf() */
अटल व्योम v253_receive(काष्ठा tty_काष्ठा *tty,
				स्थिर अचिन्हित अक्षर *cp, अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा snd_soc_component *component = tty->disc_data;
	काष्ठा cx20442_priv *cx20442;

	अगर (!component)
		वापस;

	cx20442 = snd_soc_component_get_drvdata(component);

	अगर (!cx20442->tty) अणु
		/* First modem response, complete setup procedure */

		/* Set up codec driver access to modem controls */
		cx20442->tty = tty;
		component->card->pop_समय = 1;
	पूर्ण
पूर्ण

/* Line discipline .ग_लिखो_wakeup() */
अटल व्योम v253_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
पूर्ण

काष्ठा tty_ldisc_ops v253_ops = अणु
	.name = "cx20442",
	.owner = THIS_MODULE,
	.खोलो = v253_खोलो,
	.बंद = v253_बंद,
	.hangup = v253_hangup,
	.receive_buf = v253_receive,
	.ग_लिखो_wakeup = v253_wakeup,
पूर्ण;
EXPORT_SYMBOL_GPL(v253_ops);


/*
 * Codec DAI
 */

अटल काष्ठा snd_soc_dai_driver cx20442_dai = अणु
	.name = "cx20442-voice",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक cx20442_set_bias_level(काष्ठा snd_soc_component *component,
		क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा cx20442_priv *cx20442 = snd_soc_component_get_drvdata(component);
	पूर्णांक err = 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (snd_soc_component_get_bias_level(component) != SND_SOC_BIAS_STANDBY)
			अवरोध;
		अगर (IS_ERR(cx20442->por))
			err = PTR_ERR(cx20442->por);
		अन्यथा
			err = regulator_enable(cx20442->por);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) != SND_SOC_BIAS_PREPARE)
			अवरोध;
		अगर (IS_ERR(cx20442->por))
			err = PTR_ERR(cx20442->por);
		अन्यथा
			err = regulator_disable(cx20442->por);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक cx20442_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cx20442_priv *cx20442;

	cx20442 = kzalloc(माप(काष्ठा cx20442_priv), GFP_KERNEL);
	अगर (cx20442 == शून्य)
		वापस -ENOMEM;

	cx20442->por = regulator_get(component->dev, "POR");
	अगर (IS_ERR(cx20442->por)) अणु
		पूर्णांक err = PTR_ERR(cx20442->por);

		dev_warn(component->dev, "failed to get POR supply (%d)", err);
		/*
		 * When running on a non-dt platक्रमm and requested regulator
		 * is not available, regulator_get() never वापसs
		 * -EPROBE_DEFER as it is not able to justअगरy अगर the regulator
		 * may still appear later.  On the other hand, the board can
		 * still set full स्थिरraपूर्णांकs flag at late_initcall in order
		 * to inकाष्ठा regulator_get() to वापस a dummy one अगर
		 * sufficient.  Hence, अगर we get -ENODEV here, let's convert
		 * it to -EPROBE_DEFER and रुको क्रम the board to decide or
		 * let Deferred Probe infraकाष्ठाure handle this error.
		 */
		अगर (err == -ENODEV)
			err = -EPROBE_DEFER;
		kमुक्त(cx20442);
		वापस err;
	पूर्ण

	cx20442->tty = शून्य;

	snd_soc_component_set_drvdata(component, cx20442);
	component->card->pop_समय = 0;

	वापस 0;
पूर्ण

/* घातer करोwn chip */
अटल व्योम cx20442_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cx20442_priv *cx20442 = snd_soc_component_get_drvdata(component);

	अगर (cx20442->tty) अणु
		काष्ठा tty_काष्ठा *tty = cx20442->tty;
		tty_hangup(tty);
	पूर्ण

	अगर (!IS_ERR(cx20442->por)) अणु
		/* should be alपढ़ोy in STANDBY, hence disabled */
		regulator_put(cx20442->por);
	पूर्ण

	snd_soc_component_set_drvdata(component, शून्य);
	kमुक्त(cx20442);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver cx20442_component_dev = अणु
	.probe			= cx20442_component_probe,
	.हटाओ			= cx20442_component_हटाओ,
	.set_bias_level		= cx20442_set_bias_level,
	.पढ़ो			= cx20442_पढ़ो_reg_cache,
	.ग_लिखो			= cx20442_ग_लिखो,
	.dapm_widमाला_लो		= cx20442_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cx20442_dapm_widमाला_लो),
	.dapm_routes		= cx20442_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(cx20442_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक cx20442_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&cx20442_component_dev, &cx20442_dai, 1);
पूर्ण

अटल काष्ठा platक्रमm_driver cx20442_platक्रमm_driver = अणु
	.driver = अणु
		.name = "cx20442-codec",
		पूर्ण,
	.probe = cx20442_platक्रमm_probe,
पूर्ण;

module_platक्रमm_driver(cx20442_platक्रमm_driver);

MODULE_DESCRIPTION("ASoC CX20442-11 voice modem codec driver");
MODULE_AUTHOR("Janusz Krzysztofik");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:cx20442-codec");
