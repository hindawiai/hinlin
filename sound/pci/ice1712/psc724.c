<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble VT1724 (Envy24HT)
 *
 *   Lowlevel functions क्रम Philips PSC724 Ultimate Edge
 *
 *	Copyright (c) 2012 Ondrej Zary <linux@rainbow-software.org>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश "psc724.h"
#समावेश "wm8766.h"
#समावेश "wm8776.h"

काष्ठा psc724_spec अणु
	काष्ठा snd_wm8766 wm8766;
	काष्ठा snd_wm8776 wm8776;
	bool mute_all, jack_detect;
	काष्ठा snd_ice1712 *ice;
	काष्ठा delayed_work hp_work;
	bool hp_connected;
पूर्ण;

/****************************************************************************/
/*  PHILIPS PSC724 ULTIMATE EDGE                                            */
/****************************************************************************/
/*
 *  VT1722 (Envy24GT) - 6 outमाला_दो, 4 inमाला_दो (only 2 used), 24-bit/96kHz
 *
 *  प्रणाली configuration ICE_EEP2_SYSCONF=0x42
 *    XIN1 49.152MHz
 *    no MPU401
 *    one stereo ADC, no S/PDIF receiver
 *    three stereo DACs (FRONT, REAR, CENTER+LFE)
 *
 *  AC-Link configuration ICE_EEP2_ACLINK=0x80
 *    use I2S, not AC97
 *
 *  I2S converters feature ICE_EEP2_I2S=0x30
 *    I2S codec has no volume/mute control feature (bug!)
 *    I2S codec करोes not support 96KHz or 192KHz (bug!)
 *    I2S codec 24bits
 *
 *  S/PDIF configuration ICE_EEP2_SPDIF=0xc1
 *    Enable पूर्णांकegrated S/PDIF transmitter
 *    पूर्णांकernal S/PDIF out implemented
 *    No S/PDIF input
 *    External S/PDIF out implemented
 *
 *
 * ** connected chips **
 *
 *  WM8776
 *     2-channel DAC used क्रम मुख्य output and stereo ADC (with 10-channel MUX)
 *     AIN1: LINE IN, AIN2: CD/VIDEO, AIN3: AUX, AIN4: Front MIC, AIN5: Rear MIC
 *     Controlled by I2C using VT1722 I2C पूर्णांकerface:
 *          MODE (pin16) -- GND
 *          CE   (pin17) -- GND  I2C mode (address=0x34)
 *          DI   (pin18) -- SDA  (VT1722 pin70)
 *          CL   (pin19) -- SCLK (VT1722 pin71)
 *
 *  WM8766
 *      6-channel DAC used क्रम rear & center/LFE outमाला_दो (only 4 channels used)
 *      Controlled by SPI using VT1722 GPIO pins:
 *          MODE   (pin 1) -- GPIO19 (VT1722 pin99)
 *          ML/I2S (pin11) -- GPIO18 (VT1722 pin98)
 *          MC/IWL (pin12) -- GPIO17 (VT1722 pin97)
 *          MD/DM  (pin13) -- GPIO16 (VT1722 pin96)
 *          MUTE   (pin14) -- GPIO20 (VT1722 pin101)
 *
 *  GPIO14 is used as input क्रम headphone jack detection (1 = connected)
 *  GPIO22 is used as MUTE ALL output, grounding all 6 channels
 *
 * ** output pins and device names **
 *
 *   5.1ch name -- output connector color -- device (-D option)
 *
 *      FRONT 2ch                  -- green  -- plughw:0,0
 *      CENTER(Lch) SUBWOOFER(Rch) -- orange -- plughw:0,2,0
 *      REAR 2ch                   -- black  -- plughw:0,2,1
 */

/* codec access low-level functions */

#घोषणा GPIO_HP_JACK	(1 << 14)
#घोषणा GPIO_MUTE_SUR	(1 << 20)
#घोषणा GPIO_MUTE_ALL	(1 << 22)

#घोषणा JACK_INTERVAL	1000

#घोषणा PSC724_SPI_DELAY 1

#घोषणा PSC724_SPI_DATA	(1 << 16)
#घोषणा PSC724_SPI_CLK	(1 << 17)
#घोषणा PSC724_SPI_LOAD	(1 << 18)
#घोषणा PSC724_SPI_MASK	(PSC724_SPI_DATA | PSC724_SPI_CLK | PSC724_SPI_LOAD)

अटल व्योम psc724_wm8766_ग_लिखो(काष्ठा snd_wm8766 *wm, u16 addr, u16 data)
अणु
	काष्ठा psc724_spec *spec = container_of(wm, काष्ठा psc724_spec, wm8766);
	काष्ठा snd_ice1712 *ice = spec->ice;
	u32 st, bits;
	पूर्णांक i;

	snd_ice1712_save_gpio_status(ice);

	st = ((addr & 0x7f) << 9) | (data & 0x1ff);
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction | PSC724_SPI_MASK);
	snd_ice1712_gpio_set_mask(ice, ice->gpio.ग_लिखो_mask & ~PSC724_SPI_MASK);
	bits = snd_ice1712_gpio_पढ़ो(ice) & ~PSC724_SPI_MASK;
	snd_ice1712_gpio_ग_लिखो(ice, bits);

	क्रम (i = 0; i < 16; i++) अणु
		udelay(PSC724_SPI_DELAY);
		bits &= ~PSC724_SPI_CLK;
		/* MSB first */
		st <<= 1;
		अगर (st & 0x10000)
			bits |= PSC724_SPI_DATA;
		अन्यथा
			bits &= ~PSC724_SPI_DATA;
		snd_ice1712_gpio_ग_लिखो(ice, bits);
		/* CLOCK high */
		udelay(PSC724_SPI_DELAY);
		bits |= PSC724_SPI_CLK;
		snd_ice1712_gpio_ग_लिखो(ice, bits);
	पूर्ण
	/* LOAD high */
	udelay(PSC724_SPI_DELAY);
	bits |= PSC724_SPI_LOAD;
	snd_ice1712_gpio_ग_लिखो(ice, bits);
	/* LOAD low, DATA and CLOCK high */
	udelay(PSC724_SPI_DELAY);
	bits |= (PSC724_SPI_DATA | PSC724_SPI_CLK);
	snd_ice1712_gpio_ग_लिखो(ice, bits);

	snd_ice1712_restore_gpio_status(ice);
पूर्ण

अटल व्योम psc724_wm8776_ग_लिखो(काष्ठा snd_wm8776 *wm, u8 addr, u8 data)
अणु
	काष्ठा psc724_spec *spec = container_of(wm, काष्ठा psc724_spec, wm8776);

	snd_vt1724_ग_लिखो_i2c(spec->ice, 0x34, addr, data);
पूर्ण

/* mute all */

अटल व्योम psc724_set_master_चयन(काष्ठा snd_ice1712 *ice, bool on)
अणु
	अचिन्हित पूर्णांक bits = snd_ice1712_gpio_पढ़ो(ice);
	काष्ठा psc724_spec *spec = ice->spec;

	spec->mute_all = !on;
	अगर (on)
		bits &= ~(GPIO_MUTE_ALL | GPIO_MUTE_SUR);
	अन्यथा
		bits |= GPIO_MUTE_ALL | GPIO_MUTE_SUR;
	snd_ice1712_gpio_ग_लिखो(ice, bits);
पूर्ण

अटल bool psc724_get_master_चयन(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा psc724_spec *spec = ice->spec;

	वापस !spec->mute_all;
पूर्ण

/* jack detection */

अटल व्योम psc724_set_jack_state(काष्ठा snd_ice1712 *ice, bool hp_connected)
अणु
	काष्ठा psc724_spec *spec = ice->spec;
	काष्ठा snd_ctl_elem_id elem_id;
	काष्ठा snd_kcontrol *kctl;
	u16 घातer = spec->wm8776.regs[WM8776_REG_PWRDOWN] & ~WM8776_PWR_HPPD;

	psc724_set_master_चयन(ice, !hp_connected);
	अगर (!hp_connected)
		घातer |= WM8776_PWR_HPPD;
	snd_wm8776_set_घातer(&spec->wm8776, घातer);
	spec->hp_connected = hp_connected;
	/* notअगरy about master speaker mute change */
	स_रखो(&elem_id, 0, माप(elem_id));
	elem_id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	strscpy(elem_id.name, "Master Speakers Playback Switch",
						माप(elem_id.name));
	kctl = snd_ctl_find_id(ice->card, &elem_id);
	snd_ctl_notअगरy(ice->card, SNDRV_CTL_EVENT_MASK_VALUE, &kctl->id);
	/* and headphone mute change */
	strscpy(elem_id.name, spec->wm8776.ctl[WM8776_CTL_HP_SW].name,
						माप(elem_id.name));
	kctl = snd_ctl_find_id(ice->card, &elem_id);
	snd_ctl_notअगरy(ice->card, SNDRV_CTL_EVENT_MASK_VALUE, &kctl->id);
पूर्ण

अटल व्योम psc724_update_hp_jack_state(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा psc724_spec *spec = container_of(work, काष्ठा psc724_spec,
						hp_work.work);
	काष्ठा snd_ice1712 *ice = spec->ice;
	bool hp_connected = snd_ice1712_gpio_पढ़ो(ice) & GPIO_HP_JACK;

	schedule_delayed_work(&spec->hp_work, msecs_to_jअगरfies(JACK_INTERVAL));
	अगर (hp_connected == spec->hp_connected)
		वापस;
	psc724_set_jack_state(ice, hp_connected);
पूर्ण

अटल व्योम psc724_set_jack_detection(काष्ठा snd_ice1712 *ice, bool on)
अणु
	काष्ठा psc724_spec *spec = ice->spec;

	अगर (spec->jack_detect == on)
		वापस;

	spec->jack_detect = on;
	अगर (on) अणु
		bool hp_connected = snd_ice1712_gpio_पढ़ो(ice) & GPIO_HP_JACK;
		psc724_set_jack_state(ice, hp_connected);
		schedule_delayed_work(&spec->hp_work,
					msecs_to_jअगरfies(JACK_INTERVAL));
	पूर्ण अन्यथा
		cancel_delayed_work_sync(&spec->hp_work);
पूर्ण

अटल bool psc724_get_jack_detection(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा psc724_spec *spec = ice->spec;

	वापस spec->jack_detect;
पूर्ण

/* mixer controls */

काष्ठा psc724_control अणु
	स्थिर अक्षर *name;
	व्योम (*set)(काष्ठा snd_ice1712 *ice, bool on);
	bool (*get)(काष्ठा snd_ice1712 *ice);
पूर्ण;

अटल स्थिर काष्ठा psc724_control psc724_cont[] = अणु
	अणु
		.name = "Master Speakers Playback Switch",
		.set = psc724_set_master_चयन,
		.get = psc724_get_master_चयन,
	पूर्ण,
	अणु
		.name = "Headphone Jack Detection Playback Switch",
		.set = psc724_set_jack_detection,
		.get = psc724_get_jack_detection,
	पूर्ण,
पूर्ण;

अटल पूर्णांक psc724_ctl_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक n = kcontrol->निजी_value;

	ucontrol->value.पूर्णांकeger.value[0] = psc724_cont[n].get(ice);

	वापस 0;
पूर्ण

अटल पूर्णांक psc724_ctl_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक n = kcontrol->निजी_value;

	psc724_cont[n].set(ice, ucontrol->value.पूर्णांकeger.value[0]);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *front_volume	= "Front Playback Volume";
अटल स्थिर अक्षर *front_चयन	= "Front Playback Switch";
अटल स्थिर अक्षर *front_zc	= "Front Zero Cross Detect Playback Switch";
अटल स्थिर अक्षर *front_izd	= "Front Infinite Zero Detect Playback Switch";
अटल स्थिर अक्षर *front_phase	= "Front Phase Invert Playback Switch";
अटल स्थिर अक्षर *front_deemph	= "Front Deemphasis Playback Switch";
अटल स्थिर अक्षर *ain1_चयन	= "Line Capture Switch";
अटल स्थिर अक्षर *ain2_चयन	= "CD Capture Switch";
अटल स्थिर अक्षर *ain3_चयन	= "AUX Capture Switch";
अटल स्थिर अक्षर *ain4_चयन	= "Front Mic Capture Switch";
अटल स्थिर अक्षर *ain5_चयन	= "Rear Mic Capture Switch";
अटल स्थिर अक्षर *rear_volume	= "Surround Playback Volume";
अटल स्थिर अक्षर *clfe_volume	= "CLFE Playback Volume";
अटल स्थिर अक्षर *rear_चयन	= "Surround Playback Switch";
अटल स्थिर अक्षर *clfe_चयन	= "CLFE Playback Switch";
अटल स्थिर अक्षर *rear_phase	= "Surround Phase Invert Playback Switch";
अटल स्थिर अक्षर *clfe_phase	= "CLFE Phase Invert Playback Switch";
अटल स्थिर अक्षर *rear_deemph	= "Surround Deemphasis Playback Switch";
अटल स्थिर अक्षर *clfe_deemph	= "CLFE Deemphasis Playback Switch";
अटल स्थिर अक्षर *rear_clfe_izd = "Rear Infinite Zero Detect Playback Switch";
अटल स्थिर अक्षर *rear_clfe_zc	= "Rear Zero Cross Detect Playback Switch";

अटल पूर्णांक psc724_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा snd_kcontrol_new cont;
	काष्ठा snd_kcontrol *ctl;
	पूर्णांक err, i;
	काष्ठा psc724_spec *spec = ice->spec;

	spec->wm8776.ctl[WM8776_CTL_DAC_VOL].name = front_volume;
	spec->wm8776.ctl[WM8776_CTL_DAC_SW].name = front_चयन;
	spec->wm8776.ctl[WM8776_CTL_DAC_ZC_SW].name = front_zc;
	spec->wm8776.ctl[WM8776_CTL_AUX_SW].name = शून्य;
	spec->wm8776.ctl[WM8776_CTL_DAC_IZD_SW].name = front_izd;
	spec->wm8776.ctl[WM8776_CTL_PHASE_SW].name = front_phase;
	spec->wm8776.ctl[WM8776_CTL_DEEMPH_SW].name = front_deemph;
	spec->wm8776.ctl[WM8776_CTL_INPUT1_SW].name = ain1_चयन;
	spec->wm8776.ctl[WM8776_CTL_INPUT2_SW].name = ain2_चयन;
	spec->wm8776.ctl[WM8776_CTL_INPUT3_SW].name = ain3_चयन;
	spec->wm8776.ctl[WM8776_CTL_INPUT4_SW].name = ain4_चयन;
	spec->wm8776.ctl[WM8776_CTL_INPUT5_SW].name = ain5_चयन;
	snd_wm8776_build_controls(&spec->wm8776);
	spec->wm8766.ctl[WM8766_CTL_CH1_VOL].name = rear_volume;
	spec->wm8766.ctl[WM8766_CTL_CH2_VOL].name = clfe_volume;
	spec->wm8766.ctl[WM8766_CTL_CH3_VOL].name = शून्य;
	spec->wm8766.ctl[WM8766_CTL_CH1_SW].name = rear_चयन;
	spec->wm8766.ctl[WM8766_CTL_CH2_SW].name = clfe_चयन;
	spec->wm8766.ctl[WM8766_CTL_CH3_SW].name = शून्य;
	spec->wm8766.ctl[WM8766_CTL_PHASE1_SW].name = rear_phase;
	spec->wm8766.ctl[WM8766_CTL_PHASE2_SW].name = clfe_phase;
	spec->wm8766.ctl[WM8766_CTL_PHASE3_SW].name = शून्य;
	spec->wm8766.ctl[WM8766_CTL_DEEMPH1_SW].name = rear_deemph;
	spec->wm8766.ctl[WM8766_CTL_DEEMPH2_SW].name = clfe_deemph;
	spec->wm8766.ctl[WM8766_CTL_DEEMPH3_SW].name = शून्य;
	spec->wm8766.ctl[WM8766_CTL_IZD_SW].name = rear_clfe_izd;
	spec->wm8766.ctl[WM8766_CTL_ZC_SW].name = rear_clfe_zc;
	snd_wm8766_build_controls(&spec->wm8766);

	स_रखो(&cont, 0, माप(cont));
	cont.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	क्रम (i = 0; i < ARRAY_SIZE(psc724_cont); i++) अणु
		cont.निजी_value = i;
		cont.name = psc724_cont[i].name;
		cont.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
		cont.info = snd_ctl_boolean_mono_info;
		cont.get = psc724_ctl_get;
		cont.put = psc724_ctl_put;
		ctl = snd_ctl_new1(&cont, ice);
		अगर (!ctl)
			वापस -ENOMEM;
		err = snd_ctl_add(ice->card, ctl);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम psc724_set_pro_rate(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा psc724_spec *spec = ice->spec;
	/* restore codec volume settings after rate change (PMCLK stop) */
	snd_wm8776_volume_restore(&spec->wm8776);
	snd_wm8766_volume_restore(&spec->wm8766);
पूर्ण

/* घातer management */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक psc724_resume(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा psc724_spec *spec = ice->spec;

	snd_wm8776_resume(&spec->wm8776);
	snd_wm8766_resume(&spec->wm8766);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* init */

अटल पूर्णांक psc724_init(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा psc724_spec *spec;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;
	spec->ice = ice;

	ice->num_total_dacs = 6;
	ice->num_total_adcs = 2;
	spec->wm8776.ops.ग_लिखो = psc724_wm8776_ग_लिखो;
	spec->wm8776.card = ice->card;
	snd_wm8776_init(&spec->wm8776);
	spec->wm8766.ops.ग_लिखो = psc724_wm8766_ग_लिखो;
	spec->wm8766.card = ice->card;
#अगर_घोषित CONFIG_PM_SLEEP
	ice->pm_resume = psc724_resume;
	ice->pm_suspend_enabled = 1;
#पूर्ण_अगर
	snd_wm8766_init(&spec->wm8766);
	snd_wm8766_set_अगर(&spec->wm8766,
			WM8766_IF_FMT_I2S | WM8766_IF_IWL_24BIT);
	ice->gpio.set_pro_rate = psc724_set_pro_rate;
	INIT_DELAYED_WORK(&spec->hp_work, psc724_update_hp_jack_state);
	psc724_set_jack_detection(ice, true);
	वापस 0;
पूर्ण

अटल व्योम psc724_निकास(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा psc724_spec *spec = ice->spec;

	cancel_delayed_work_sync(&spec->hp_work);
पूर्ण

/* PSC724 has buggy EEPROM (no 96&192kHz, all FFh GPIOs), so override it here */
अटल स्थिर अचिन्हित अक्षर psc724_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]	= 0x42,	/* 49.152MHz, 1 ADC, 3 DACs */
	[ICE_EEP2_ACLINK]	= 0x80,	/* I2S */
	[ICE_EEP2_I2S]		= 0xf0,	/* I2S volume, 96kHz, 24bit */
	[ICE_EEP2_SPDIF]	= 0xc1,	/* spdअगर out-en, out-पूर्णांक, no input */
	/* GPIO outमाला_दो */
	[ICE_EEP2_GPIO_सूची2]	= 0x5f, /* MUTE_ALL,WM8766 MUTE/MODE/ML/MC/MD */
	/* GPIO ग_लिखो enable */
	[ICE_EEP2_GPIO_MASK]	= 0xff, /* पढ़ो-only */
	[ICE_EEP2_GPIO_MASK1]	= 0xff, /* पढ़ो-only */
	[ICE_EEP2_GPIO_MASK2]	= 0xa0, /* MUTE_ALL,WM8766 MUTE/MODE/ML/MC/MD */
	/* GPIO initial state */
	[ICE_EEP2_GPIO_STATE2]	= 0x20,	/* unmuted, all WM8766 pins low */
पूर्ण;

काष्ठा snd_ice1712_card_info snd_vt1724_psc724_cards[] = अणु
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_PSC724,
		.name = "Philips PSC724 Ultimate Edge",
		.model = "psc724",
		.chip_init = psc724_init,
		.chip_निकास = psc724_निकास,
		.build_controls = psc724_add_controls,
		.eeprom_size = माप(psc724_eeprom),
		.eeprom_data = psc724_eeprom,
	पूर्ण,
	अणुपूर्ण /*terminator*/
पूर्ण;
