<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ams-delta.c  --  SoC audio क्रम Amstrad E3 (Delta) videophone
 *
 * Copyright (C) 2009 Janusz Krzysztofik <jkrzyszt@tis.icnet.pl>
 *
 * Initially based on sound/soc/omap/osk5912.x
 * Copyright (C) 2008 Mistral Solutions
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/tty.h>
#समावेश <linux/module.h>

#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#समावेश <यंत्र/mach-types.h>

#समावेश <linux/platक्रमm_data/asoc-ti-mcbsp.h>

#समावेश "omap-mcbsp.h"
#समावेश "../codecs/cx20442.h"

अटल काष्ठा gpio_desc *handset_mute;
अटल काष्ठा gpio_desc *handsमुक्त_mute;

अटल पूर्णांक ams_delta_event_handset(काष्ठा snd_soc_dapm_widget *w,
				   काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	gpiod_set_value_cansleep(handset_mute, !SND_SOC_DAPM_EVENT_ON(event));
	वापस 0;
पूर्ण

अटल पूर्णांक ams_delta_event_handsमुक्त(काष्ठा snd_soc_dapm_widget *w,
				     काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	gpiod_set_value_cansleep(handsमुक्त_mute, !SND_SOC_DAPM_EVENT_ON(event));
	वापस 0;
पूर्ण

/* Board specअगरic DAPM widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget ams_delta_dapm_widमाला_लो[] = अणु
	/* Handset */
	SND_SOC_DAPM_MIC("Mouthpiece", शून्य),
	SND_SOC_DAPM_HP("Earpiece", ams_delta_event_handset),
	/* Handsमुक्त/Speakerphone */
	SND_SOC_DAPM_MIC("Microphone", शून्य),
	SND_SOC_DAPM_SPK("Speaker", ams_delta_event_handsमुक्त),
पूर्ण;

/* How they are connected to codec pins */
अटल स्थिर काष्ठा snd_soc_dapm_route ams_delta_audio_map[] = अणु
	अणु"TELIN", शून्य, "Mouthpiece"पूर्ण,
	अणु"Earpiece", शून्य, "TELOUT"पूर्ण,

	अणु"MIC", शून्य, "Microphone"पूर्ण,
	अणु"Speaker", शून्य, "SPKOUT"पूर्ण,
पूर्ण;

/*
 * Controls, functional after the modem line discipline is activated.
 */

/* Virtual चयन: audio input/output स्थिरellations */
अटल स्थिर अक्षर *ams_delta_audio_mode[] =
	अणु"Mixed", "Handset", "Handsfree", "Speakerphone"पूर्ण;

/* Selection <-> pin translation */
#घोषणा AMS_DELTA_MOUTHPIECE	0
#घोषणा AMS_DELTA_EARPIECE	1
#घोषणा AMS_DELTA_MICROPHONE	2
#घोषणा AMS_DELTA_SPEAKER	3
#घोषणा AMS_DELTA_AGC		4

#घोषणा AMS_DELTA_MIXED		((1 << AMS_DELTA_EARPIECE) | \
						(1 << AMS_DELTA_MICROPHONE))
#घोषणा AMS_DELTA_HANDSET	((1 << AMS_DELTA_MOUTHPIECE) | \
						(1 << AMS_DELTA_EARPIECE))
#घोषणा AMS_DELTA_HANDSFREE	((1 << AMS_DELTA_MICROPHONE) | \
						(1 << AMS_DELTA_SPEAKER))
#घोषणा AMS_DELTA_SPEAKERPHONE	(AMS_DELTA_HANDSFREE | (1 << AMS_DELTA_AGC))

अटल स्थिर अचिन्हित लघु ams_delta_audio_mode_pins[] = अणु
	AMS_DELTA_MIXED,
	AMS_DELTA_HANDSET,
	AMS_DELTA_HANDSFREE,
	AMS_DELTA_SPEAKERPHONE,
पूर्ण;

अटल अचिन्हित लघु ams_delta_audio_agc;

/*
 * Used क्रम passing a codec काष्ठाure poपूर्णांकer
 * from the board initialization code to the tty line discipline.
 */
अटल काष्ठा snd_soc_component *cx20442_codec;

अटल पूर्णांक ams_delta_set_audio_mode(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm = &card->dapm;
	काष्ठा soc_क्रमागत *control = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित लघु pins;
	पूर्णांक pin, changed = 0;

	/* Refuse any mode changes अगर we are not able to control the codec. */
	अगर (!cx20442_codec->card->pop_समय)
		वापस -EUNATCH;

	अगर (ucontrol->value.क्रमागतerated.item[0] >= control->items)
		वापस -EINVAL;

	snd_soc_dapm_mutex_lock(dapm);

	/* Translate selection to biपंचांगap */
	pins = ams_delta_audio_mode_pins[ucontrol->value.क्रमागतerated.item[0]];

	/* Setup pins after corresponding bits अगर changed */
	pin = !!(pins & (1 << AMS_DELTA_MOUTHPIECE));

	अगर (pin != snd_soc_dapm_get_pin_status(dapm, "Mouthpiece")) अणु
		changed = 1;
		अगर (pin)
			snd_soc_dapm_enable_pin_unlocked(dapm, "Mouthpiece");
		अन्यथा
			snd_soc_dapm_disable_pin_unlocked(dapm, "Mouthpiece");
	पूर्ण
	pin = !!(pins & (1 << AMS_DELTA_EARPIECE));
	अगर (pin != snd_soc_dapm_get_pin_status(dapm, "Earpiece")) अणु
		changed = 1;
		अगर (pin)
			snd_soc_dapm_enable_pin_unlocked(dapm, "Earpiece");
		अन्यथा
			snd_soc_dapm_disable_pin_unlocked(dapm, "Earpiece");
	पूर्ण
	pin = !!(pins & (1 << AMS_DELTA_MICROPHONE));
	अगर (pin != snd_soc_dapm_get_pin_status(dapm, "Microphone")) अणु
		changed = 1;
		अगर (pin)
			snd_soc_dapm_enable_pin_unlocked(dapm, "Microphone");
		अन्यथा
			snd_soc_dapm_disable_pin_unlocked(dapm, "Microphone");
	पूर्ण
	pin = !!(pins & (1 << AMS_DELTA_SPEAKER));
	अगर (pin != snd_soc_dapm_get_pin_status(dapm, "Speaker")) अणु
		changed = 1;
		अगर (pin)
			snd_soc_dapm_enable_pin_unlocked(dapm, "Speaker");
		अन्यथा
			snd_soc_dapm_disable_pin_unlocked(dapm, "Speaker");
	पूर्ण
	pin = !!(pins & (1 << AMS_DELTA_AGC));
	अगर (pin != ams_delta_audio_agc) अणु
		ams_delta_audio_agc = pin;
		changed = 1;
		अगर (pin)
			snd_soc_dapm_enable_pin_unlocked(dapm, "AGCIN");
		अन्यथा
			snd_soc_dapm_disable_pin_unlocked(dapm, "AGCIN");
	पूर्ण

	अगर (changed)
		snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);

	वापस changed;
पूर्ण

अटल पूर्णांक ams_delta_get_audio_mode(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm = &card->dapm;
	अचिन्हित लघु pins, mode;

	pins = ((snd_soc_dapm_get_pin_status(dapm, "Mouthpiece") <<
							AMS_DELTA_MOUTHPIECE) |
			(snd_soc_dapm_get_pin_status(dapm, "Earpiece") <<
							AMS_DELTA_EARPIECE));
	अगर (pins)
		pins |= (snd_soc_dapm_get_pin_status(dapm, "Microphone") <<
							AMS_DELTA_MICROPHONE);
	अन्यथा
		pins = ((snd_soc_dapm_get_pin_status(dapm, "Microphone") <<
							AMS_DELTA_MICROPHONE) |
			(snd_soc_dapm_get_pin_status(dapm, "Speaker") <<
							AMS_DELTA_SPEAKER) |
			(ams_delta_audio_agc << AMS_DELTA_AGC));

	क्रम (mode = 0; mode < ARRAY_SIZE(ams_delta_audio_mode); mode++)
		अगर (pins == ams_delta_audio_mode_pins[mode])
			अवरोध;

	अगर (mode >= ARRAY_SIZE(ams_delta_audio_mode))
		वापस -EINVAL;

	ucontrol->value.क्रमागतerated.item[0] = mode;

	वापस 0;
पूर्ण

अटल SOC_ENUM_SINGLE_EXT_DECL(ams_delta_audio_क्रमागत,
				      ams_delta_audio_mode);

अटल स्थिर काष्ठा snd_kcontrol_new ams_delta_audio_controls[] = अणु
	SOC_ENUM_EXT("Audio Mode", ams_delta_audio_क्रमागत,
			ams_delta_get_audio_mode, ams_delta_set_audio_mode),
पूर्ण;

/* Hook चयन */
अटल काष्ठा snd_soc_jack ams_delta_hook_चयन;
अटल काष्ठा snd_soc_jack_gpio ams_delta_hook_चयन_gpios[] = अणु
	अणु
		.name = "hook_switch",
		.report = SND_JACK_HEADSET,
		.invert = 1,
		.debounce_समय = 150,
	पूर्ण
पूर्ण;

/* After we are able to control the codec over the modem,
 * the hook चयन can be used क्रम dynamic DAPM reconfiguration. */
अटल काष्ठा snd_soc_jack_pin ams_delta_hook_चयन_pins[] = अणु
	/* Handset */
	अणु
		.pin = "Mouthpiece",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
	अणु
		.pin = "Earpiece",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
	/* Handsमुक्त */
	अणु
		.pin = "Microphone",
		.mask = SND_JACK_MICROPHONE,
		.invert = 1,
	पूर्ण,
	अणु
		.pin = "Speaker",
		.mask = SND_JACK_HEADPHONE,
		.invert = 1,
	पूर्ण,
पूर्ण;


/*
 * Modem line discipline, required क्रम making above controls functional.
 * Activated from userspace with ldattach, possibly invoked from udev rule.
 */

/* To actually apply any modem controlled configuration changes to the codec,
 * we must connect codec DAI pins to the modem क्रम a moment.  Be careful not
 * to पूर्णांकerfere with our digital mute function that shares the same hardware. */
अटल काष्ठा समयr_list cx81801_समयr;
अटल bool cx81801_cmd_pending;
अटल bool ams_delta_muted;
अटल DEFINE_SPINLOCK(ams_delta_lock);
अटल काष्ठा gpio_desc *gpiod_modem_codec;

अटल व्योम cx81801_समयout(काष्ठा समयr_list *unused)
अणु
	पूर्णांक muted;

	spin_lock(&ams_delta_lock);
	cx81801_cmd_pending = 0;
	muted = ams_delta_muted;
	spin_unlock(&ams_delta_lock);

	/* Reconnect the codec DAI back from the modem to the CPU DAI
	 * only अगर digital mute still off */
	अगर (!muted)
		gpiod_set_value(gpiod_modem_codec, 0);
पूर्ण

/* Line discipline .खोलो() */
अटल पूर्णांक cx81801_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक ret;

	अगर (!cx20442_codec)
		वापस -ENODEV;

	/*
	 * Pass the codec काष्ठाure poपूर्णांकer क्रम use by other ldisc callbacks,
	 * both the card and the codec specअगरic parts.
	 */
	tty->disc_data = cx20442_codec;

	ret = v253_ops.खोलो(tty);

	अगर (ret < 0)
		tty->disc_data = शून्य;

	वापस ret;
पूर्ण

/* Line discipline .बंद() */
अटल व्योम cx81801_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा snd_soc_component *component = tty->disc_data;
	काष्ठा snd_soc_dapm_context *dapm = &component->card->dapm;

	del_समयr_sync(&cx81801_समयr);

	/* Prevent the hook चयन from further changing the DAPM pins */
	INIT_LIST_HEAD(&ams_delta_hook_चयन.pins);

	अगर (!component)
		वापस;

	v253_ops.बंद(tty);

	/* Revert back to शेष audio input/output स्थिरellation */
	snd_soc_dapm_mutex_lock(dapm);

	snd_soc_dapm_disable_pin_unlocked(dapm, "Mouthpiece");
	snd_soc_dapm_enable_pin_unlocked(dapm, "Earpiece");
	snd_soc_dapm_enable_pin_unlocked(dapm, "Microphone");
	snd_soc_dapm_disable_pin_unlocked(dapm, "Speaker");
	snd_soc_dapm_disable_pin_unlocked(dapm, "AGCIN");

	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

/* Line discipline .hangup() */
अटल पूर्णांक cx81801_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	cx81801_बंद(tty);
	वापस 0;
पूर्ण

/* Line discipline .receive_buf() */
अटल व्योम cx81801_receive(काष्ठा tty_काष्ठा *tty,
				स्थिर अचिन्हित अक्षर *cp, अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा snd_soc_component *component = tty->disc_data;
	स्थिर अचिन्हित अक्षर *c;
	पूर्णांक apply, ret;

	अगर (!component)
		वापस;

	अगर (!component->card->pop_समय) अणु
		/* First modem response, complete setup procedure */

		/* Initialize समयr used क्रम config pulse generation */
		समयr_setup(&cx81801_समयr, cx81801_समयout, 0);

		v253_ops.receive_buf(tty, cp, fp, count);

		/* Link hook चयन to DAPM pins */
		ret = snd_soc_jack_add_pins(&ams_delta_hook_चयन,
					ARRAY_SIZE(ams_delta_hook_चयन_pins),
					ams_delta_hook_चयन_pins);
		अगर (ret)
			dev_warn(component->dev,
				"Failed to link hook switch to DAPM pins, "
				"will continue with hook switch unlinked.\n");

		वापस;
	पूर्ण

	v253_ops.receive_buf(tty, cp, fp, count);

	क्रम (c = &cp[count - 1]; c >= cp; c--) अणु
		अगर (*c != '\r')
			जारी;
		/* Complete modem response received, apply config to codec */

		spin_lock_bh(&ams_delta_lock);
		mod_समयr(&cx81801_समयr, jअगरfies + msecs_to_jअगरfies(150));
		apply = !ams_delta_muted && !cx81801_cmd_pending;
		cx81801_cmd_pending = 1;
		spin_unlock_bh(&ams_delta_lock);

		/* Apply config pulse by connecting the codec to the modem
		 * अगर not alपढ़ोy करोne */
		अगर (apply)
			gpiod_set_value(gpiod_modem_codec, 1);
		अवरोध;
	पूर्ण
पूर्ण

/* Line discipline .ग_लिखो_wakeup() */
अटल व्योम cx81801_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	v253_ops.ग_लिखो_wakeup(tty);
पूर्ण

अटल काष्ठा tty_ldisc_ops cx81801_ops = अणु
	.name = "cx81801",
	.owner = THIS_MODULE,
	.खोलो = cx81801_खोलो,
	.बंद = cx81801_बंद,
	.hangup = cx81801_hangup,
	.receive_buf = cx81801_receive,
	.ग_लिखो_wakeup = cx81801_wakeup,
पूर्ण;


/*
 * Even अगर not very useful, the sound card can still work without any of the
 * above functionality activated.  You can still control its audio input/output
 * स्थिरellation and speakerphone gain from userspace by issuing AT commands
 * over the modem port.
 */

अटल काष्ठा snd_soc_ops ams_delta_ops;


/* Digital mute implemented using modem/CPU multiplexer.
 * Shares hardware with codec config pulse generation */
अटल bool ams_delta_muted = 1;

अटल पूर्णांक ams_delta_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	पूर्णांक apply;

	अगर (ams_delta_muted == mute)
		वापस 0;

	spin_lock_bh(&ams_delta_lock);
	ams_delta_muted = mute;
	apply = !cx81801_cmd_pending;
	spin_unlock_bh(&ams_delta_lock);

	अगर (apply)
		gpiod_set_value(gpiod_modem_codec, !!mute);
	वापस 0;
पूर्ण

/* Our codec DAI probably करोesn't have its own .ops काष्ठाure */
अटल स्थिर काष्ठा snd_soc_dai_ops ams_delta_dai_ops = अणु
	.mute_stream = ams_delta_mute,
	.no_capture_mute = 1,
पूर्ण;

/* Will be used अगर the codec ever has its own digital_mute function */
अटल पूर्णांक ams_delta_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस ams_delta_mute(शून्य, 0, substream->stream);
पूर्ण

अटल व्योम ams_delta_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	ams_delta_mute(शून्य, 1, substream->stream);
पूर्ण


/*
 * Card initialization
 */

अटल पूर्णांक ams_delta_cx20442_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dapm_context *dapm = &card->dapm;
	पूर्णांक ret;
	/* Codec is पढ़ोy, now add/activate board specअगरic controls */

	/* Store a poपूर्णांकer to the codec काष्ठाure क्रम tty ldisc use */
	cx20442_codec = asoc_rtd_to_codec(rtd, 0)->component;

	/* Add hook चयन - can be used to control the codec from userspace
	 * even अगर line discipline fails */
	ret = snd_soc_card_jack_new(card, "hook_switch", SND_JACK_HEADSET,
				    &ams_delta_hook_चयन, शून्य, 0);
	अगर (ret)
		dev_warn(card->dev,
				"Failed to allocate resources for hook switch, "
				"will continue without one.\n");
	अन्यथा अणु
		ret = snd_soc_jack_add_gpiods(card->dev, &ams_delta_hook_चयन,
					ARRAY_SIZE(ams_delta_hook_चयन_gpios),
					ams_delta_hook_चयन_gpios);
		अगर (ret)
			dev_warn(card->dev,
				"Failed to set up hook switch GPIO line, "
				"will continue with hook switch inactive.\n");
	पूर्ण

	gpiod_modem_codec = devm_gpiod_get(card->dev, "modem_codec",
					   GPIOD_OUT_HIGH);
	अगर (IS_ERR(gpiod_modem_codec)) अणु
		dev_warn(card->dev, "Failed to obtain modem_codec GPIO\n");
		वापस 0;
	पूर्ण

	/* Set up digital mute अगर not provided by the codec */
	अगर (!codec_dai->driver->ops) अणु
		codec_dai->driver->ops = &ams_delta_dai_ops;
	पूर्ण अन्यथा अणु
		ams_delta_ops.startup = ams_delta_startup;
		ams_delta_ops.shutकरोwn = ams_delta_shutकरोwn;
	पूर्ण

	/* Register optional line discipline क्रम over the modem control */
	ret = tty_रेजिस्टर_ldisc(N_V253, &cx81801_ops);
	अगर (ret) अणु
		dev_warn(card->dev,
				"Failed to register line discipline, "
				"will continue without any controls.\n");
		वापस 0;
	पूर्ण

	/* Set up initial pin स्थिरellation */
	snd_soc_dapm_disable_pin(dapm, "Mouthpiece");
	snd_soc_dapm_disable_pin(dapm, "Speaker");
	snd_soc_dapm_disable_pin(dapm, "AGCIN");
	snd_soc_dapm_disable_pin(dapm, "AGCOUT");

	वापस 0;
पूर्ण

/* DAI glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(cx20442,
	DAILINK_COMP_ARRAY(COMP_CPU("omap-mcbsp.1")),
	DAILINK_COMP_ARRAY(COMP_CODEC("cx20442-codec", "cx20442-voice")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("omap-mcbsp.1")));

अटल काष्ठा snd_soc_dai_link ams_delta_dai_link = अणु
	.name = "CX20442",
	.stream_name = "CX20442",
	.init = ams_delta_cx20442_init,
	.ops = &ams_delta_ops,
	.dai_fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBM_CFM,
	SND_SOC_DAILINK_REG(cx20442),
पूर्ण;

/* Audio card driver */
अटल काष्ठा snd_soc_card ams_delta_audio_card = अणु
	.name = "AMS_DELTA",
	.owner = THIS_MODULE,
	.dai_link = &ams_delta_dai_link,
	.num_links = 1,

	.controls = ams_delta_audio_controls,
	.num_controls = ARRAY_SIZE(ams_delta_audio_controls),
	.dapm_widमाला_लो = ams_delta_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(ams_delta_dapm_widमाला_लो),
	.dapm_routes = ams_delta_audio_map,
	.num_dapm_routes = ARRAY_SIZE(ams_delta_audio_map),
पूर्ण;

/* Module init/निकास */
अटल पूर्णांक ams_delta_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &ams_delta_audio_card;
	पूर्णांक ret;

	card->dev = &pdev->dev;

	handset_mute = devm_gpiod_get(card->dev, "handset_mute",
				      GPIOD_OUT_HIGH);
	अगर (IS_ERR(handset_mute))
		वापस PTR_ERR(handset_mute);

	handsमुक्त_mute = devm_gpiod_get(card->dev, "handsfree_mute",
					GPIOD_OUT_HIGH);
	अगर (IS_ERR(handsमुक्त_mute))
		वापस PTR_ERR(handsमुक्त_mute);

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);
		card->dev = शून्य;
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ams_delta_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);

	अगर (tty_unरेजिस्टर_ldisc(N_V253) != 0)
		dev_warn(&pdev->dev,
			"failed to unregister V253 line discipline\n");

	snd_soc_unरेजिस्टर_card(card);
	card->dev = शून्य;
	वापस 0;
पूर्ण

#घोषणा DRV_NAME "ams-delta-audio"

अटल काष्ठा platक्रमm_driver ams_delta_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.probe = ams_delta_probe,
	.हटाओ = ams_delta_हटाओ,
पूर्ण;

module_platक्रमm_driver(ams_delta_driver);

MODULE_AUTHOR("Janusz Krzysztofik <jkrzyszt@tis.icnet.pl>");
MODULE_DESCRIPTION("ALSA SoC driver for Amstrad E3 (Delta) videophone");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
