<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble VT1724 (Envy24HT)
 *
 *   Lowlevel functions क्रम ESI Juli@ cards
 *
 *	Copyright (c) 2004 Jaroslav Kysela <perex@perex.cz>
 *	              2008 Pavel Hofman <dustin@seznam.cz>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <sound/core.h>
#समावेश <sound/tlv.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश "juli.h"

काष्ठा juli_spec अणु
	काष्ठा ak4114 *ak4114;
	अचिन्हित पूर्णांक analog:1;
पूर्ण;

/*
 * chip addresses on I2C bus
 */
#घोषणा AK4114_ADDR		0x20		/* S/PDIF receiver */
#घोषणा AK4358_ADDR		0x22		/* DAC */

/*
 * Juli करोes not use the standard ICE1724 घड़ी scheme. Juli's ice1724 chip is
 * supplied by बाह्यal घड़ी provided by Xilinx array and MK73-1 PLL frequency
 * multiplier. Actual frequency is set by ice1724 GPIOs hooked to the Xilinx.
 *
 * The घड़ी circuitry is supplied by the two ice1724 crystals. This
 * arrangement allows to generate independent घड़ी संकेत क्रम AK4114's input
 * rate detection circuit. As a result, Juli, unlike most other
 * ice1724+ak4114-based cards, detects spdअगर input rate correctly.
 * This fact is applied in the driver, allowing to modअगरy PCM stream rate
 * parameter according to the actual input rate.
 *
 * Juli uses the reमुख्यing three stereo-channels of its DAC to optionally
 * monitor analog input, digital input, and digital output. The corresponding
 * I2S संकेतs are routed by Xilinx, controlled by GPIOs.
 *
 * The master mute is implemented using output muting transistors (GPIO) in
 * combination with smuting the DAC.
 *
 * The card itself has no HW master volume control, implemented using the
 * vmaster control.
 *
 * TODO:
 * researching and fixing the input monitors
 */

/*
 * GPIO pins
 */
#घोषणा GPIO_FREQ_MASK		(3<<0)
#घोषणा GPIO_FREQ_32KHZ		(0<<0)
#घोषणा GPIO_FREQ_44KHZ		(1<<0)
#घोषणा GPIO_FREQ_48KHZ		(2<<0)
#घोषणा GPIO_MULTI_MASK		(3<<2)
#घोषणा GPIO_MULTI_4X		(0<<2)
#घोषणा GPIO_MULTI_2X		(1<<2)
#घोषणा GPIO_MULTI_1X		(2<<2)		/* also बाह्यal */
#घोषणा GPIO_MULTI_HALF		(3<<2)
#घोषणा GPIO_INTERNAL_CLOCK	(1<<4)		/* 0 = बाह्यal, 1 = पूर्णांकernal */
#घोषणा GPIO_CLOCK_MASK		(1<<4)
#घोषणा GPIO_ANALOG_PRESENT	(1<<5)		/* RO only: 0 = present */
#घोषणा GPIO_RXMCLK_SEL		(1<<7)		/* must be 0 */
#घोषणा GPIO_AK5385A_CKS0	(1<<8)
#घोषणा GPIO_AK5385A_DFS1	(1<<9)
#घोषणा GPIO_AK5385A_DFS0	(1<<10)
#घोषणा GPIO_DIGOUT_MONITOR	(1<<11)		/* 1 = active */
#घोषणा GPIO_DIGIN_MONITOR	(1<<12)		/* 1 = active */
#घोषणा GPIO_ANAIN_MONITOR	(1<<13)		/* 1 = active */
#घोषणा GPIO_AK5385A_CKS1	(1<<14)		/* must be 0 */
#घोषणा GPIO_MUTE_CONTROL	(1<<15)		/* output mute, 1 = muted */

#घोषणा GPIO_RATE_MASK		(GPIO_FREQ_MASK | GPIO_MULTI_MASK | \
		GPIO_CLOCK_MASK)
#घोषणा GPIO_AK5385A_MASK	(GPIO_AK5385A_CKS0 | GPIO_AK5385A_DFS0 | \
		GPIO_AK5385A_DFS1 | GPIO_AK5385A_CKS1)

#घोषणा JULI_PCM_RATE	(SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 | \
		SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | \
		SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_64000 | \
		SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 | \
		SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000)

#घोषणा GPIO_RATE_16000		(GPIO_FREQ_32KHZ | GPIO_MULTI_HALF | \
		GPIO_INTERNAL_CLOCK)
#घोषणा GPIO_RATE_22050		(GPIO_FREQ_44KHZ | GPIO_MULTI_HALF | \
		GPIO_INTERNAL_CLOCK)
#घोषणा GPIO_RATE_24000		(GPIO_FREQ_48KHZ | GPIO_MULTI_HALF | \
		GPIO_INTERNAL_CLOCK)
#घोषणा GPIO_RATE_32000		(GPIO_FREQ_32KHZ | GPIO_MULTI_1X | \
		GPIO_INTERNAL_CLOCK)
#घोषणा GPIO_RATE_44100		(GPIO_FREQ_44KHZ | GPIO_MULTI_1X | \
		GPIO_INTERNAL_CLOCK)
#घोषणा GPIO_RATE_48000		(GPIO_FREQ_48KHZ | GPIO_MULTI_1X | \
		GPIO_INTERNAL_CLOCK)
#घोषणा GPIO_RATE_64000		(GPIO_FREQ_32KHZ | GPIO_MULTI_2X | \
		GPIO_INTERNAL_CLOCK)
#घोषणा GPIO_RATE_88200		(GPIO_FREQ_44KHZ | GPIO_MULTI_2X | \
		GPIO_INTERNAL_CLOCK)
#घोषणा GPIO_RATE_96000		(GPIO_FREQ_48KHZ | GPIO_MULTI_2X | \
		GPIO_INTERNAL_CLOCK)
#घोषणा GPIO_RATE_176400	(GPIO_FREQ_44KHZ | GPIO_MULTI_4X | \
		GPIO_INTERNAL_CLOCK)
#घोषणा GPIO_RATE_192000	(GPIO_FREQ_48KHZ | GPIO_MULTI_4X | \
		GPIO_INTERNAL_CLOCK)

/*
 * Initial setup of the conversion array GPIO <-> rate
 */
अटल स्थिर अचिन्हित पूर्णांक juli_rates[] = अणु
	16000, 22050, 24000, 32000,
	44100, 48000, 64000, 88200,
	96000, 176400, 192000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio_vals[] = अणु
	GPIO_RATE_16000, GPIO_RATE_22050, GPIO_RATE_24000, GPIO_RATE_32000,
	GPIO_RATE_44100, GPIO_RATE_48000, GPIO_RATE_64000, GPIO_RATE_88200,
	GPIO_RATE_96000, GPIO_RATE_176400, GPIO_RATE_192000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list juli_rates_info = अणु
	.count = ARRAY_SIZE(juli_rates),
	.list = juli_rates,
	.mask = 0,
पूर्ण;

अटल पूर्णांक get_gpio_val(पूर्णांक rate)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(juli_rates); i++)
		अगर (juli_rates[i] == rate)
			वापस gpio_vals[i];
	वापस 0;
पूर्ण

अटल व्योम juli_ak4114_ग_लिखो(व्योम *निजी_data, अचिन्हित अक्षर reg,
				अचिन्हित अक्षर val)
अणु
	snd_vt1724_ग_लिखो_i2c((काष्ठा snd_ice1712 *)निजी_data, AK4114_ADDR,
				reg, val);
पूर्ण

अटल अचिन्हित अक्षर juli_ak4114_पढ़ो(व्योम *निजी_data, अचिन्हित अक्षर reg)
अणु
	वापस snd_vt1724_पढ़ो_i2c((काष्ठा snd_ice1712 *)निजी_data,
					AK4114_ADDR, reg);
पूर्ण

/*
 * If SPDIF capture and slaved to SPDIF-IN, setting runसमय rate
 * to the बाह्यal rate
 */
अटल व्योम juli_spdअगर_in_खोलो(काष्ठा snd_ice1712 *ice,
				काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा juli_spec *spec = ice->spec;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक rate;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK ||
			!ice->is_spdअगर_master(ice))
		वापस;
	rate = snd_ak4114_बाह्यal_rate(spec->ak4114);
	अगर (rate >= runसमय->hw.rate_min && rate <= runसमय->hw.rate_max) अणु
		runसमय->hw.rate_min = rate;
		runसमय->hw.rate_max = rate;
	पूर्ण
पूर्ण

/*
 * AK4358 section
 */

अटल व्योम juli_akm_lock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
पूर्ण

अटल व्योम juli_akm_unlock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
पूर्ण

अटल व्योम juli_akm_ग_लिखो(काष्ठा snd_akm4xxx *ak, पूर्णांक chip,
			   अचिन्हित अक्षर addr, अचिन्हित अक्षर data)
अणु
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];
	 
	अगर (snd_BUG_ON(chip))
		वापस;
	snd_vt1724_ग_लिखो_i2c(ice, AK4358_ADDR, addr, data);
पूर्ण

/*
 * change the rate of envy24HT, AK4358, AK5385
 */
अटल व्योम juli_akm_set_rate_val(काष्ठा snd_akm4xxx *ak, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित अक्षर old, पंचांगp, ak4358_dfs;
	अचिन्हित पूर्णांक ak5385_pins, old_gpio, new_gpio;
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];
	काष्ठा juli_spec *spec = ice->spec;

	अगर (rate == 0)  /* no hपूर्णांक - S/PDIF input is master or the new spdअगर
			   input rate undetected, simply वापस */
		वापस;

	/* adjust DFS on codecs */
	अगर (rate > 96000)  अणु
		ak4358_dfs = 2;
		ak5385_pins = GPIO_AK5385A_DFS1 | GPIO_AK5385A_CKS0;
	पूर्ण अन्यथा अगर (rate > 48000) अणु
		ak4358_dfs = 1;
		ak5385_pins = GPIO_AK5385A_DFS0;
	पूर्ण अन्यथा अणु
		ak4358_dfs = 0;
		ak5385_pins = 0;
	पूर्ण
	/* AK5385 first, since it requires cold reset affecting both codecs */
	old_gpio = ice->gpio.get_data(ice);
	new_gpio =  (old_gpio & ~GPIO_AK5385A_MASK) | ak5385_pins;
	/* dev_dbg(ice->card->dev, "JULI - ak5385 set_rate_val: new gpio 0x%x\n",
		new_gpio); */
	ice->gpio.set_data(ice, new_gpio);

	/* cold reset */
	old = inb(ICEMT1724(ice, AC97_CMD));
	outb(old | VT1724_AC97_COLD, ICEMT1724(ice, AC97_CMD));
	udelay(1);
	outb(old & ~VT1724_AC97_COLD, ICEMT1724(ice, AC97_CMD));

	/* AK4358 */
	/* set new value, reset DFS */
	पंचांगp = snd_akm4xxx_get(ak, 0, 2);
	snd_akm4xxx_reset(ak, 1);
	पंचांगp = snd_akm4xxx_get(ak, 0, 2);
	पंचांगp &= ~(0x03 << 4);
	पंचांगp |= ak4358_dfs << 4;
	snd_akm4xxx_set(ak, 0, 2, पंचांगp);
	snd_akm4xxx_reset(ak, 0);

	/* reinit ak4114 */
	snd_ak4114_reinit(spec->ak4114);
पूर्ण

#घोषणा AK_DAC(xname, xch)	अणु .name = xname, .num_channels = xch पूर्ण
#घोषणा PCM_VOLUME		"PCM Playback Volume"
#घोषणा MONITOR_AN_IN_VOLUME	"Monitor Analog In Volume"
#घोषणा MONITOR_DIG_IN_VOLUME	"Monitor Digital In Volume"
#घोषणा MONITOR_DIG_OUT_VOLUME	"Monitor Digital Out Volume"

अटल स्थिर काष्ठा snd_akm4xxx_dac_channel juli_dac[] = अणु
	AK_DAC(PCM_VOLUME, 2),
	AK_DAC(MONITOR_AN_IN_VOLUME, 2),
	AK_DAC(MONITOR_DIG_OUT_VOLUME, 2),
	AK_DAC(MONITOR_DIG_IN_VOLUME, 2),
पूर्ण;


अटल स्थिर काष्ठा snd_akm4xxx akm_juli_dac = अणु
	.type = SND_AK4358,
	.num_dacs = 8,	/* DAC1 - analog out
			   DAC2 - analog in monitor
			   DAC3 - digital out monitor
			   DAC4 - digital in monitor
			 */
	.ops = अणु
		.lock = juli_akm_lock,
		.unlock = juli_akm_unlock,
		.ग_लिखो = juli_akm_ग_लिखो,
		.set_rate_val = juli_akm_set_rate_val
	पूर्ण,
	.dac_info = juli_dac,
पूर्ण;

#घोषणा juli_mute_info		snd_ctl_boolean_mono_info

अटल पूर्णांक juli_mute_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	val = ice->gpio.get_data(ice) & (अचिन्हित पूर्णांक) kcontrol->निजी_value;
	अगर (kcontrol->निजी_value == GPIO_MUTE_CONTROL)
		/* val 0 = संकेत on */
		ucontrol->value.पूर्णांकeger.value[0] = (val) ? 0 : 1;
	अन्यथा
		/* val 1 = संकेत on */
		ucontrol->value.पूर्णांकeger.value[0] = (val) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक juli_mute_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक old_gpio, new_gpio;
	old_gpio = ice->gpio.get_data(ice);
	अगर (ucontrol->value.पूर्णांकeger.value[0]) अणु
		/* unmute */
		अगर (kcontrol->निजी_value == GPIO_MUTE_CONTROL) अणु
			/* 0 = संकेत on */
			new_gpio = old_gpio & ~GPIO_MUTE_CONTROL;
			/* un-smuting DAC */
			snd_akm4xxx_ग_लिखो(ice->akm, 0, 0x01, 0x01);
		पूर्ण अन्यथा
			/* 1 = संकेत on */
			new_gpio =  old_gpio |
				(अचिन्हित पूर्णांक) kcontrol->निजी_value;
	पूर्ण अन्यथा अणु
		/* mute */
		अगर (kcontrol->निजी_value == GPIO_MUTE_CONTROL) अणु
			/* 1 = संकेत off */
			new_gpio = old_gpio | GPIO_MUTE_CONTROL;
			/* smuting DAC */
			snd_akm4xxx_ग_लिखो(ice->akm, 0, 0x01, 0x03);
		पूर्ण अन्यथा
			/* 0 = संकेत off */
			new_gpio =  old_gpio &
				~((अचिन्हित पूर्णांक) kcontrol->निजी_value);
	पूर्ण
	/* dev_dbg(ice->card->dev,
		"JULI - mute/unmute: control_value: 0x%x, old_gpio: 0x%x, "
		"new_gpio 0x%x\n",
		(अचिन्हित पूर्णांक)ucontrol->value.पूर्णांकeger.value[0], old_gpio,
		new_gpio); */
	अगर (old_gpio != new_gpio) अणु
		ice->gpio.set_data(ice, new_gpio);
		वापस 1;
	पूर्ण
	/* no change */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new juli_mute_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Master Playback Switch",
		.info = juli_mute_info,
		.get = juli_mute_get,
		.put = juli_mute_put,
		.निजी_value = GPIO_MUTE_CONTROL,
	पूर्ण,
	/* Although the following functionality respects the succपूर्णांक NDA'd
	 * करोcumentation from the card manufacturer, and the same way of
	 * operation is coded in OSS Juli driver, only Digital Out monitor
	 * seems to work. Surprisingly, Analog input monitor outमाला_दो Digital
	 * output data. The two are independent, as enabling both द्विगुनs
	 * volume of the monitor sound.
	 *
	 * Checking traces on the board suggests the functionality described
	 * by the manufacturer is correct - I2S from ADC and AK4114
	 * go to ICE as well as to Xilinx, I2S inमाला_दो of DAC2,3,4 (the monitor
	 * inमाला_दो) are fed from Xilinx.
	 *
	 * I even checked traces on board and coded a support in driver क्रम
	 * an alternative possibility - the unused I2S ICE output channels
	 * चयनed to HW-IN/SPDIF-IN and providing the monitoring संकेत to
	 * the DAC - to no avail. The I2S outमाला_दो seem to be unconnected.
	 *
	 * The winकरोws driver supports the monitoring correctly.
	 */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Monitor Analog In Switch",
		.info = juli_mute_info,
		.get = juli_mute_get,
		.put = juli_mute_put,
		.निजी_value = GPIO_ANAIN_MONITOR,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Monitor Digital Out Switch",
		.info = juli_mute_info,
		.get = juli_mute_get,
		.put = juli_mute_put,
		.निजी_value = GPIO_DIGOUT_MONITOR,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Monitor Digital In Switch",
		.info = juli_mute_info,
		.get = juli_mute_get,
		.put = juli_mute_put,
		.निजी_value = GPIO_DIGIN_MONITOR,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर follower_vols[] = अणु
	PCM_VOLUME,
	MONITOR_AN_IN_VOLUME,
	MONITOR_DIG_IN_VOLUME,
	MONITOR_DIG_OUT_VOLUME,
	शून्य
पूर्ण;

अटल
DECLARE_TLV_DB_SCALE(juli_master_db_scale, -6350, 50, 1);

अटल काष्ठा snd_kcontrol *ctl_find(काष्ठा snd_card *card,
				     स्थिर अक्षर *name)
अणु
	काष्ठा snd_ctl_elem_id sid = अणु0पूर्ण;

	strscpy(sid.name, name, माप(sid.name));
	sid.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	वापस snd_ctl_find_id(card, &sid);
पूर्ण

अटल व्योम add_followers(काष्ठा snd_card *card,
			  काष्ठा snd_kcontrol *master,
			  स्थिर अक्षर * स्थिर *list)
अणु
	क्रम (; *list; list++) अणु
		काष्ठा snd_kcontrol *follower = ctl_find(card, *list);
		/* dev_dbg(card->dev, "add_followers - %s\n", *list); */
		अगर (follower) अणु
			/* dev_dbg(card->dev, "follower %s found\n", *list); */
			snd_ctl_add_follower(master, follower);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक juli_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा juli_spec *spec = ice->spec;
	पूर्णांक err;
	अचिन्हित पूर्णांक i;
	काष्ठा snd_kcontrol *vmaster;

	err = snd_ice1712_akm4xxx_build_controls(ice);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < ARRAY_SIZE(juli_mute_controls); i++) अणु
		err = snd_ctl_add(ice->card,
				snd_ctl_new1(&juli_mute_controls[i], ice));
		अगर (err < 0)
			वापस err;
	पूर्ण
	/* Create भव master control */
	vmaster = snd_ctl_make_भव_master("Master Playback Volume",
					      juli_master_db_scale);
	अगर (!vmaster)
		वापस -ENOMEM;
	add_followers(ice->card, vmaster, follower_vols);
	err = snd_ctl_add(ice->card, vmaster);
	अगर (err < 0)
		वापस err;

	/* only capture SPDIF over AK4114 */
	वापस snd_ak4114_build(spec->ak4114, शून्य,
			ice->pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream);
पूर्ण

/*
 * suspend/resume
 * */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक juli_resume(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा snd_akm4xxx *ak = ice->akm;
	काष्ठा juli_spec *spec = ice->spec;
	/* akm4358 un-reset, un-mute */
	snd_akm4xxx_reset(ak, 0);
	/* reinit ak4114 */
	snd_ak4114_resume(spec->ak4114);
	वापस 0;
पूर्ण

अटल पूर्णांक juli_suspend(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा snd_akm4xxx *ak = ice->akm;
	काष्ठा juli_spec *spec = ice->spec;
	/* akm4358 reset and soft-mute */
	snd_akm4xxx_reset(ak, 1);
	snd_ak4114_suspend(spec->ak4114);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * initialize the chip
 */

अटल अंतरभूत पूर्णांक juli_is_spdअगर_master(काष्ठा snd_ice1712 *ice)
अणु
	वापस (ice->gpio.get_data(ice) & GPIO_INTERNAL_CLOCK) ? 0 : 1;
पूर्ण

अटल अचिन्हित पूर्णांक juli_get_rate(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर result;

	result =  ice->gpio.get_data(ice) & GPIO_RATE_MASK;
	क्रम (i = 0; i < ARRAY_SIZE(gpio_vals); i++)
		अगर (gpio_vals[i] == result)
			वापस juli_rates[i];
	वापस 0;
पूर्ण

/* setting new rate */
अटल व्योम juli_set_rate(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक old, new;
	अचिन्हित अक्षर val;

	old = ice->gpio.get_data(ice);
	new =  (old & ~GPIO_RATE_MASK) | get_gpio_val(rate);
	/* dev_dbg(ice->card->dev, "JULI - set_rate: old %x, new %x\n",
			old & GPIO_RATE_MASK,
			new & GPIO_RATE_MASK); */

	ice->gpio.set_data(ice, new);
	/* चयनing to बाह्यal घड़ी - supplied by बाह्यal circuits */
	val = inb(ICEMT1724(ice, RATE));
	outb(val | VT1724_SPDIF_MASTER, ICEMT1724(ice, RATE));
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर juli_set_mclk(काष्ठा snd_ice1712 *ice,
					  अचिन्हित पूर्णांक rate)
अणु
	/* no change in master घड़ी */
	वापस 0;
पूर्ण

/* setting घड़ी to बाह्यal - SPDIF */
अटल पूर्णांक juli_set_spdअगर_घड़ी(काष्ठा snd_ice1712 *ice, पूर्णांक type)
अणु
	अचिन्हित पूर्णांक old;
	old = ice->gpio.get_data(ice);
	/* बाह्यal घड़ी (= 0), multiply 1x, 48kHz */
	ice->gpio.set_data(ice, (old & ~GPIO_RATE_MASK) | GPIO_MULTI_1X |
			GPIO_FREQ_48KHZ);
	वापस 0;
पूर्ण

/* Called when ak4114 detects change in the input SPDIF stream */
अटल व्योम juli_ak4114_change(काष्ठा ak4114 *ak4114, अचिन्हित अक्षर c0,
			       अचिन्हित अक्षर c1)
अणु
	काष्ठा snd_ice1712 *ice = ak4114->change_callback_निजी;
	पूर्णांक rate;
	अगर (ice->is_spdअगर_master(ice) && c1) अणु
		/* only क्रम SPDIF master mode, rate was changed */
		rate = snd_ak4114_बाह्यal_rate(ak4114);
		/* dev_dbg(ice->card->dev, "ak4114 - input rate changed to %d\n",
				rate); */
		juli_akm_set_rate_val(ice->akm, rate);
	पूर्ण
पूर्ण

अटल पूर्णांक juli_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित अक्षर ak4114_init_vals[] = अणु
		/* AK4117_REG_PWRDN */	AK4114_RST | AK4114_PWN |
					AK4114_OCKS0 | AK4114_OCKS1,
		/* AK4114_REQ_FORMAT */	AK4114_DIF_I24I2S,
		/* AK4114_REG_IO0 */	AK4114_TX1E,
		/* AK4114_REG_IO1 */	AK4114_EFH_1024 | AK4114_DIT |
					AK4114_IPS(1),
		/* AK4114_REG_INT0_MASK */ 0,
		/* AK4114_REG_INT1_MASK */ 0
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर ak4114_init_txcsb[] = अणु
		0x41, 0x02, 0x2c, 0x00, 0x00
	पूर्ण;
	पूर्णांक err;
	काष्ठा juli_spec *spec;
	काष्ठा snd_akm4xxx *ak;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;

	err = snd_ak4114_create(ice->card,
				juli_ak4114_पढ़ो,
				juli_ak4114_ग_लिखो,
				ak4114_init_vals, ak4114_init_txcsb,
				ice, &spec->ak4114);
	अगर (err < 0)
		वापस err;
	/* callback क्रम codecs rate setting */
	spec->ak4114->change_callback = juli_ak4114_change;
	spec->ak4114->change_callback_निजी = ice;
	/* AK4114 in Juli can detect बाह्यal rate correctly */
	spec->ak4114->check_flags = 0;

#अगर 0
/*
 * it seems that the analog करोughter board detection करोes not work reliably, so
 * क्रमce the analog flag; it should be very rare (अगर ever) to come at Juli@
 * used without the analog daughter board
 */
	spec->analog = (ice->gpio.get_data(ice) & GPIO_ANALOG_PRESENT) ? 0 : 1;
#अन्यथा
	spec->analog = 1;
#पूर्ण_अगर

	अगर (spec->analog) अणु
		dev_info(ice->card->dev, "juli@: analog I/O detected\n");
		ice->num_total_dacs = 2;
		ice->num_total_adcs = 2;

		ice->akm = kzalloc(माप(काष्ठा snd_akm4xxx), GFP_KERNEL);
		ak = ice->akm;
		अगर (!ak)
			वापस -ENOMEM;
		ice->akm_codecs = 1;
		err = snd_ice1712_akm4xxx_init(ak, &akm_juli_dac, शून्य, ice);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* juli is घड़ीed by Xilinx array */
	ice->hw_rates = &juli_rates_info;
	ice->is_spdअगर_master = juli_is_spdअगर_master;
	ice->get_rate = juli_get_rate;
	ice->set_rate = juli_set_rate;
	ice->set_mclk = juli_set_mclk;
	ice->set_spdअगर_घड़ी = juli_set_spdअगर_घड़ी;

	ice->spdअगर.ops.खोलो = juli_spdअगर_in_खोलो;

#अगर_घोषित CONFIG_PM_SLEEP
	ice->pm_resume = juli_resume;
	ice->pm_suspend = juli_suspend;
	ice->pm_suspend_enabled = 1;
#पूर्ण_अगर

	वापस 0;
पूर्ण


/*
 * Juli@ boards करोn't provide the EEPROM data except क्रम the venकरोr IDs.
 * hence the driver needs to sets up it properly.
 */

अटल स्थिर अचिन्हित अक्षर juli_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x2b,	/* घड़ी 512, mpu401, 1xADC, 1xDACs,
					   SPDIF in */
	[ICE_EEP2_ACLINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0xf8,	/* vol, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-पूर्णांक, spdअगर-in */
	[ICE_EEP2_GPIO_सूची]    = 0x9f,	/* 5, 6:inमाला_दो; 7, 4-0 outमाला_दो*/
	[ICE_EEP2_GPIO_सूची1]   = 0xff,
	[ICE_EEP2_GPIO_सूची2]   = 0x7f,
	[ICE_EEP2_GPIO_MASK]   = 0x60,	/* 5, 6: locked; 7, 4-0 writable */
	[ICE_EEP2_GPIO_MASK1]  = 0x00,  /* 0-7 writable */
	[ICE_EEP2_GPIO_MASK2]  = 0x7f,
	[ICE_EEP2_GPIO_STATE]  = GPIO_FREQ_48KHZ | GPIO_MULTI_1X |
	       GPIO_INTERNAL_CLOCK,	/* पूर्णांकernal घड़ी, multiple 1x, 48kHz*/
	[ICE_EEP2_GPIO_STATE1] = 0x00,	/* unmuted */
	[ICE_EEP2_GPIO_STATE2] = 0x00,
पूर्ण;

/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_vt1724_juli_cards[] = अणु
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_JULI,
		.name = "ESI Juli@",
		.model = "juli",
		.chip_init = juli_init,
		.build_controls = juli_add_controls,
		.eeprom_size = माप(juli_eeprom),
		.eeprom_data = juli_eeprom,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;
