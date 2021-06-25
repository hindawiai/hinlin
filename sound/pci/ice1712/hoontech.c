<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble ICE1712 (Envy24)
 *
 *   Lowlevel functions क्रम Hoontech STDSP24
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 */      

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>

#समावेश "ice1712.h"
#समावेश "hoontech.h"

/* Hoontech-specअगरic setting */
काष्ठा hoontech_spec अणु
	अचिन्हित अक्षर boxbits[4];
	अचिन्हित पूर्णांक config;
	अचिन्हित लघु boxconfig[4];
पूर्ण;

अटल व्योम snd_ice1712_stdsp24_gpio_ग_लिखो(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर byte)
अणु
	byte |= ICE1712_STDSP24_CLOCK_BIT;
	udelay(100);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, byte);
	byte &= ~ICE1712_STDSP24_CLOCK_BIT;
	udelay(100);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, byte);
	byte |= ICE1712_STDSP24_CLOCK_BIT;
	udelay(100);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, byte);
पूर्ण

अटल व्योम snd_ice1712_stdsp24_darear(काष्ठा snd_ice1712 *ice, पूर्णांक activate)
अणु
	काष्ठा hoontech_spec *spec = ice->spec;
	mutex_lock(&ice->gpio_mutex);
	ICE1712_STDSP24_0_DAREAR(spec->boxbits, activate);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[0]);
	mutex_unlock(&ice->gpio_mutex);
पूर्ण

अटल व्योम snd_ice1712_stdsp24_mute(काष्ठा snd_ice1712 *ice, पूर्णांक activate)
अणु
	काष्ठा hoontech_spec *spec = ice->spec;
	mutex_lock(&ice->gpio_mutex);
	ICE1712_STDSP24_3_MUTE(spec->boxbits, activate);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[3]);
	mutex_unlock(&ice->gpio_mutex);
पूर्ण

अटल व्योम snd_ice1712_stdsp24_insel(काष्ठा snd_ice1712 *ice, पूर्णांक activate)
अणु
	काष्ठा hoontech_spec *spec = ice->spec;
	mutex_lock(&ice->gpio_mutex);
	ICE1712_STDSP24_3_INSEL(spec->boxbits, activate);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[3]);
	mutex_unlock(&ice->gpio_mutex);
पूर्ण

अटल व्योम snd_ice1712_stdsp24_box_channel(काष्ठा snd_ice1712 *ice, पूर्णांक box, पूर्णांक chn, पूर्णांक activate)
अणु
	काष्ठा hoontech_spec *spec = ice->spec;

	mutex_lock(&ice->gpio_mutex);

	/* select box */
	ICE1712_STDSP24_0_BOX(spec->boxbits, box);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[0]);

	/* prepare क्रम ग_लिखो */
	अगर (chn == 3)
		ICE1712_STDSP24_2_CHN4(spec->boxbits, 0);
	ICE1712_STDSP24_2_MIDI1(spec->boxbits, activate);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[2]);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[3]);

	ICE1712_STDSP24_1_CHN1(spec->boxbits, 1);
	ICE1712_STDSP24_1_CHN2(spec->boxbits, 1);
	ICE1712_STDSP24_1_CHN3(spec->boxbits, 1);
	ICE1712_STDSP24_2_CHN4(spec->boxbits, 1);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[1]);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[2]);
	udelay(100);
	अगर (chn == 3) अणु
		ICE1712_STDSP24_2_CHN4(spec->boxbits, 0);
		snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[2]);
	पूर्ण अन्यथा अणु
		चयन (chn) अणु
		हाल 0:	ICE1712_STDSP24_1_CHN1(spec->boxbits, 0); अवरोध;
		हाल 1:	ICE1712_STDSP24_1_CHN2(spec->boxbits, 0); अवरोध;
		हाल 2:	ICE1712_STDSP24_1_CHN3(spec->boxbits, 0); अवरोध;
		पूर्ण
		snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[1]);
	पूर्ण
	udelay(100);
	ICE1712_STDSP24_1_CHN1(spec->boxbits, 1);
	ICE1712_STDSP24_1_CHN2(spec->boxbits, 1);
	ICE1712_STDSP24_1_CHN3(spec->boxbits, 1);
	ICE1712_STDSP24_2_CHN4(spec->boxbits, 1);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[1]);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[2]);
	udelay(100);

	ICE1712_STDSP24_2_MIDI1(spec->boxbits, 0);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[2]);

	mutex_unlock(&ice->gpio_mutex);
पूर्ण

अटल व्योम snd_ice1712_stdsp24_box_midi(काष्ठा snd_ice1712 *ice, पूर्णांक box, पूर्णांक master)
अणु
	काष्ठा hoontech_spec *spec = ice->spec;

	mutex_lock(&ice->gpio_mutex);

	/* select box */
	ICE1712_STDSP24_0_BOX(spec->boxbits, box);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[0]);

	ICE1712_STDSP24_2_MIDIIN(spec->boxbits, 1);
	ICE1712_STDSP24_2_MIDI1(spec->boxbits, master);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[2]);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[3]);

	udelay(100);
	
	ICE1712_STDSP24_2_MIDIIN(spec->boxbits, 0);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[2]);
	
	mdelay(10);
	
	ICE1712_STDSP24_2_MIDIIN(spec->boxbits, 1);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[2]);

	mutex_unlock(&ice->gpio_mutex);
पूर्ण

अटल व्योम snd_ice1712_stdsp24_midi2(काष्ठा snd_ice1712 *ice, पूर्णांक activate)
अणु
	काष्ठा hoontech_spec *spec = ice->spec;
	mutex_lock(&ice->gpio_mutex);
	ICE1712_STDSP24_3_MIDI2(spec->boxbits, activate);
	snd_ice1712_stdsp24_gpio_ग_लिखो(ice, spec->boxbits[3]);
	mutex_unlock(&ice->gpio_mutex);
पूर्ण

अटल पूर्णांक hoontech_init(काष्ठा snd_ice1712 *ice, bool staudio)
अणु
	काष्ठा hoontech_spec *spec;
	पूर्णांक box, chn;

	ice->num_total_dacs = 8;
	ice->num_total_adcs = 8;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;

	ICE1712_STDSP24_SET_ADDR(spec->boxbits, 0);
	ICE1712_STDSP24_CLOCK(spec->boxbits, 0, 1);
	ICE1712_STDSP24_0_BOX(spec->boxbits, 0);
	ICE1712_STDSP24_0_DAREAR(spec->boxbits, 0);

	ICE1712_STDSP24_SET_ADDR(spec->boxbits, 1);
	ICE1712_STDSP24_CLOCK(spec->boxbits, 1, 1);
	ICE1712_STDSP24_1_CHN1(spec->boxbits, 1);
	ICE1712_STDSP24_1_CHN2(spec->boxbits, 1);
	ICE1712_STDSP24_1_CHN3(spec->boxbits, 1);
	
	ICE1712_STDSP24_SET_ADDR(spec->boxbits, 2);
	ICE1712_STDSP24_CLOCK(spec->boxbits, 2, 1);
	ICE1712_STDSP24_2_CHN4(spec->boxbits, 1);
	ICE1712_STDSP24_2_MIDIIN(spec->boxbits, 1);
	ICE1712_STDSP24_2_MIDI1(spec->boxbits, 0);

	ICE1712_STDSP24_SET_ADDR(spec->boxbits, 3);
	ICE1712_STDSP24_CLOCK(spec->boxbits, 3, 1);
	ICE1712_STDSP24_3_MIDI2(spec->boxbits, 0);
	ICE1712_STDSP24_3_MUTE(spec->boxbits, 1);
	ICE1712_STDSP24_3_INSEL(spec->boxbits, 0);

	/* let's go - activate only functions in first box */
	अगर (staudio)
		spec->config = ICE1712_STDSP24_MUTE;
	अन्यथा
		spec->config = 0;
			    /* ICE1712_STDSP24_MUTE |
			       ICE1712_STDSP24_INSEL |
			       ICE1712_STDSP24_DAREAR; */
	/*  These boxconfigs have caused problems in the past.
	 *  The code is not optimal, but should now enable a working config to
	 *  be achieved.
	 *  ** MIDI IN can only be configured on one box **
	 *  ICE1712_STDSP24_BOX_MIDI1 needs to be set क्रम that box.
	 *  Tests on a ADAC2000 box suggest the box config flags करो not
	 *  work as would be expected, and the inमाला_दो are crossed.
	 *  Setting ICE1712_STDSP24_BOX_MIDI1 and ICE1712_STDSP24_BOX_MIDI2
	 *  on the same box connects MIDI-In to both 401 uarts; both outमाला_दो
	 *  are then active on all boxes.
	 *  The शेष config here sets up everything on the first box.
	 *  Alan Horsपंचांगann  5.2.2008
	 */
	spec->boxconfig[0] = ICE1712_STDSP24_BOX_CHN1 |
				     ICE1712_STDSP24_BOX_CHN2 |
				     ICE1712_STDSP24_BOX_CHN3 |
				     ICE1712_STDSP24_BOX_CHN4 |
				     ICE1712_STDSP24_BOX_MIDI1 |
				     ICE1712_STDSP24_BOX_MIDI2;
	अगर (staudio) अणु
		spec->boxconfig[1] =
		spec->boxconfig[2] =
		spec->boxconfig[3] = spec->boxconfig[0];
	पूर्ण अन्यथा अणु
		spec->boxconfig[1] =
		spec->boxconfig[2] =
		spec->boxconfig[3] = 0;
	पूर्ण

	snd_ice1712_stdsp24_darear(ice,
		(spec->config & ICE1712_STDSP24_DAREAR) ? 1 : 0);
	snd_ice1712_stdsp24_mute(ice,
		(spec->config & ICE1712_STDSP24_MUTE) ? 1 : 0);
	snd_ice1712_stdsp24_insel(ice,
		(spec->config & ICE1712_STDSP24_INSEL) ? 1 : 0);
	क्रम (box = 0; box < 4; box++) अणु
		अगर (spec->boxconfig[box] & ICE1712_STDSP24_BOX_MIDI2)
                        snd_ice1712_stdsp24_midi2(ice, 1);
		क्रम (chn = 0; chn < 4; chn++)
			snd_ice1712_stdsp24_box_channel(ice, box, chn,
				(spec->boxconfig[box] & (1 << chn)) ? 1 : 0);
		अगर (spec->boxconfig[box] & ICE1712_STDSP24_BOX_MIDI1)
			snd_ice1712_stdsp24_box_midi(ice, box, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_hoontech_init(काष्ठा snd_ice1712 *ice)
अणु
	वापस hoontech_init(ice, false);
पूर्ण

अटल पूर्णांक snd_ice1712_staudio_init(काष्ठा snd_ice1712 *ice)
अणु
	वापस hoontech_init(ice, true);
पूर्ण

/*
 * AK4524 access
 */

/* start callback क्रम STDSP24 with modअगरied hardware */
अटल व्योम stdsp24_ak4524_lock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];
	अचिन्हित अक्षर पंचांगp;
	snd_ice1712_save_gpio_status(ice);
	पंचांगp =	ICE1712_STDSP24_SERIAL_DATA |
		ICE1712_STDSP24_SERIAL_CLOCK |
		ICE1712_STDSP24_AK4524_CS;
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_सूचीECTION,
			  ice->gpio.direction | पंचांगp);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_WRITE_MASK, ~पंचांगp);
पूर्ण

अटल पूर्णांक snd_ice1712_value_init(काष्ठा snd_ice1712 *ice)
अणु
	/* Hoontech STDSP24 with modअगरied hardware */
	अटल स्थिर काष्ठा snd_akm4xxx akm_stdsp24_mv = अणु
		.num_adcs = 2,
		.num_dacs = 2,
		.type = SND_AK4524,
		.ops = अणु
			.lock = stdsp24_ak4524_lock
		पूर्ण
	पूर्ण;

	अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_stdsp24_mv_priv = अणु
		.caddr = 2,
		.cअगर = 1, /* CIF high */
		.data_mask = ICE1712_STDSP24_SERIAL_DATA,
		.clk_mask = ICE1712_STDSP24_SERIAL_CLOCK,
		.cs_mask = ICE1712_STDSP24_AK4524_CS,
		.cs_addr = ICE1712_STDSP24_AK4524_CS,
		.cs_none = 0,
		.add_flags = 0,
	पूर्ण;

	पूर्णांक err;
	काष्ठा snd_akm4xxx *ak;

	/* set the analog DACs */
	ice->num_total_dacs = 2;

	/* set the analog ADCs */
	ice->num_total_adcs = 2;
	
	/* analog section */
	ak = ice->akm = kदो_स्मृति(माप(काष्ठा snd_akm4xxx), GFP_KERNEL);
	अगर (! ak)
		वापस -ENOMEM;
	ice->akm_codecs = 1;

	err = snd_ice1712_akm4xxx_init(ak, &akm_stdsp24_mv, &akm_stdsp24_mv_priv, ice);
	अगर (err < 0)
		वापस err;

	/* ak4524 controls */
	वापस snd_ice1712_akm4xxx_build_controls(ice);
पूर्ण

अटल पूर्णांक snd_ice1712_ez8_init(काष्ठा snd_ice1712 *ice)
अणु
	ice->gpio.ग_लिखो_mask = ice->eeprom.gpiomask;
	ice->gpio.direction = ice->eeprom.gpiodir;
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_WRITE_MASK, ice->eeprom.gpiomask);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_सूचीECTION, ice->eeprom.gpiodir);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, ice->eeprom.gpiostate);
	वापस 0;
पूर्ण


/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_ice1712_hoontech_cards[] = अणु
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_STDSP24,
		.name = "Hoontech SoundTrack Audio DSP24",
		.model = "dsp24",
		.chip_init = snd_ice1712_hoontech_init,
		.mpu401_1_name = "MIDI-1 Hoontech/STA DSP24",
		.mpu401_2_name = "MIDI-2 Hoontech/STA DSP24",
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_STDSP24_VALUE,	/* a dummy id */
		.name = "Hoontech SoundTrack Audio DSP24 Value",
		.model = "dsp24_value",
		.chip_init = snd_ice1712_value_init,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_STDSP24_MEDIA7_1,
		.name = "Hoontech STA DSP24 Media 7.1",
		.model = "dsp24_71",
		.chip_init = snd_ice1712_hoontech_init,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_EVENT_EZ8,	/* a dummy id */
		.name = "Event Electronics EZ8",
		.model = "ez8",
		.chip_init = snd_ice1712_ez8_init,
	पूर्ण,
	अणु
		/* STAudio ADCIII has the same SSID as Hoontech StA DSP24,
		 * thus identअगरied only via the explicit model option
		 */
		.subvenकरोr = ICE1712_SUBDEVICE_STAUDIO_ADCIII,	/* a dummy id */
		.name = "STAudio ADCIII",
		.model = "staudio",
		.chip_init = snd_ice1712_staudio_init,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;
