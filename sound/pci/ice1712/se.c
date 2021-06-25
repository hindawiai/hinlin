<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble VT1724 (Envy24HT)
 *
 *   Lowlevel functions क्रम ONKYO WAVIO SE-90PCI and SE-200PCI
 *
 *	Copyright (c) 2007 Shin-ya Okada  sh_okada(at)d4.dion.ne.jp
 *                                        (at) -> @
 */      

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/tlv.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश "se.h"

काष्ठा se_spec अणु
	काष्ठा अणु
		अचिन्हित अक्षर ch1, ch2;
	पूर्ण vol[8];
पूर्ण;

/****************************************************************************/
/*  ONKYO WAVIO SE-200PCI                                                   */
/****************************************************************************/
/*
 *  प्रणाली configuration ICE_EEP2_SYSCONF=0x4b
 *    XIN1 49.152MHz
 *    not have UART
 *    one stereo ADC and a S/PDIF receiver connected
 *    four stereo DACs connected
 *
 *  AC-Link configuration ICE_EEP2_ACLINK=0x80
 *    use I2C, not use AC97
 *
 *  I2S converters feature ICE_EEP2_I2S=0x78
 *    I2S codec has no volume/mute control feature
 *    I2S codec supports 96KHz and 192KHz
 *    I2S codec 24bits
 *
 *  S/PDIF configuration ICE_EEP2_SPDIF=0xc3
 *    Enable पूर्णांकegrated S/PDIF transmitter
 *    पूर्णांकernal S/PDIF out implemented
 *    S/PDIF is stereo
 *    External S/PDIF out implemented
 *
 *
 * ** connected chips **
 *
 *  WM8740
 *      A 2ch-DAC of मुख्य outमाला_दो.
 *      It setuped as I2S mode by wire, so no way to setup from software.
 *      The sample-rate are स्वतःmatically changed. 
 *          ML/I2S (28pin) --------+
 *          MC/DM1 (27pin) -- 5V   |
 *          MD/DM0 (26pin) -- GND  |
 *          MUTEB  (25pin) -- NC   |
 *          MODE   (24pin) -- GND  |
 *          CSBIW  (23pin) --------+
 *                                 |
 *          RSTB   (22pin) --R(1K)-+
 *      Probably it reduce the noise from the control line.
 *
 *  WM8766
 *      A 6ch-DAC क्रम surrounds.
 *      It's control wire was connected to GPIOxx (3-wire serial पूर्णांकerface)
 *          ML/I2S (11pin) -- GPIO18
 *          MC/IWL (12pin) -- GPIO17
 *          MD/DM  (13pin) -- GPIO16
 *          MUTE   (14pin) -- GPIO01
 *
 *  WM8776
 *     A 2ch-ADC(with 10ch-selector) plus 2ch-DAC.
 *     It's control wire was connected to SDA/SCLK (2-wire serial पूर्णांकerface)
 *          MODE (16pin) -- R(1K) -- GND
 *          CE   (17pin) -- R(1K) -- GND  2-wire mode (address=0x34)
 *          DI   (18pin) -- SDA
 *          CL   (19pin) -- SCLK
 *
 *
 * ** output pins and device names **
 *
 *   7.1ch name -- output connector color -- device (-D option)
 *
 *      FRONT 2ch                  -- green  -- plughw:0,0
 *      CENTER(Lch) SUBWOOFER(Rch) -- black  -- plughw:0,2,0
 *      SURROUND 2ch               -- orange -- plughw:0,2,1
 *      SURROUND BACK 2ch          -- white  -- plughw:0,2,2
 *
 */


/****************************************************************************/
/*  WM8740 पूर्णांकerface                                                        */
/****************************************************************************/

अटल व्योम se200pci_WM8740_init(काष्ठा snd_ice1712 *ice)
अणु
	/* nothing to करो */
पूर्ण


अटल व्योम se200pci_WM8740_set_pro_rate(काष्ठा snd_ice1712 *ice,
						अचिन्हित पूर्णांक rate)
अणु
	/* nothing to करो */
पूर्ण


/****************************************************************************/
/*  WM8766 पूर्णांकerface                                                        */
/****************************************************************************/

अटल व्योम se200pci_WM8766_ग_लिखो(काष्ठा snd_ice1712 *ice,
					अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक st;
	अचिन्हित पूर्णांक bits;
	पूर्णांक i;
	स्थिर अचिन्हित पूर्णांक DATA  = 0x010000;
	स्थिर अचिन्हित पूर्णांक CLOCK = 0x020000;
	स्थिर अचिन्हित पूर्णांक LOAD  = 0x040000;
	स्थिर अचिन्हित पूर्णांक ALL_MASK = (DATA | CLOCK | LOAD);

	snd_ice1712_save_gpio_status(ice);

	st = ((addr & 0x7f) << 9) | (data & 0x1ff);
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction | ALL_MASK);
	snd_ice1712_gpio_set_mask(ice, ice->gpio.ग_लिखो_mask & ~ALL_MASK);
	bits = snd_ice1712_gpio_पढ़ो(ice) & ~ALL_MASK;

	snd_ice1712_gpio_ग_लिखो(ice, bits);
	क्रम (i = 0; i < 16; i++) अणु
		udelay(1);
		bits &= ~CLOCK;
		st = (st << 1);
		अगर (st & 0x10000)
			bits |= DATA;
		अन्यथा
			bits &= ~DATA;

		snd_ice1712_gpio_ग_लिखो(ice, bits);

		udelay(1);
		bits |= CLOCK;
		snd_ice1712_gpio_ग_लिखो(ice, bits);
	पूर्ण

	udelay(1);
	bits |= LOAD;
	snd_ice1712_gpio_ग_लिखो(ice, bits);

	udelay(1);
	bits |= (DATA | CLOCK);
	snd_ice1712_gpio_ग_लिखो(ice, bits);

	snd_ice1712_restore_gpio_status(ice);
पूर्ण

अटल व्योम se200pci_WM8766_set_volume(काष्ठा snd_ice1712 *ice, पूर्णांक ch,
					अचिन्हित पूर्णांक vol1, अचिन्हित पूर्णांक vol2)
अणु
	चयन (ch) अणु
	हाल 0:
		se200pci_WM8766_ग_लिखो(ice, 0x000, vol1);
		se200pci_WM8766_ग_लिखो(ice, 0x001, vol2 | 0x100);
		अवरोध;
	हाल 1:
		se200pci_WM8766_ग_लिखो(ice, 0x004, vol1);
		se200pci_WM8766_ग_लिखो(ice, 0x005, vol2 | 0x100);
		अवरोध;
	हाल 2:
		se200pci_WM8766_ग_लिखो(ice, 0x006, vol1);
		se200pci_WM8766_ग_लिखो(ice, 0x007, vol2 | 0x100);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम se200pci_WM8766_init(काष्ठा snd_ice1712 *ice)
अणु
	se200pci_WM8766_ग_लिखो(ice, 0x1f, 0x000); /* RESET ALL */
	udelay(10);

	se200pci_WM8766_set_volume(ice, 0, 0, 0); /* volume L=0 R=0 */
	se200pci_WM8766_set_volume(ice, 1, 0, 0); /* volume L=0 R=0 */
	se200pci_WM8766_set_volume(ice, 2, 0, 0); /* volume L=0 R=0 */

	se200pci_WM8766_ग_लिखो(ice, 0x03, 0x022); /* serial mode I2S-24bits */
	se200pci_WM8766_ग_लिखो(ice, 0x0a, 0x080); /* MCLK=256fs */
	se200pci_WM8766_ग_लिखो(ice, 0x12, 0x000); /* MDP=0 */
	se200pci_WM8766_ग_लिखो(ice, 0x15, 0x000); /* MDP=0 */
	se200pci_WM8766_ग_लिखो(ice, 0x09, 0x000); /* demp=off mute=off */

	se200pci_WM8766_ग_लिखो(ice, 0x02, 0x124); /* ch-assign L=L R=R RESET */
	se200pci_WM8766_ग_लिखो(ice, 0x02, 0x120); /* ch-assign L=L R=R */
पूर्ण

अटल व्योम se200pci_WM8766_set_pro_rate(काष्ठा snd_ice1712 *ice,
					अचिन्हित पूर्णांक rate)
अणु
	अगर (rate > 96000)
		se200pci_WM8766_ग_लिखो(ice, 0x0a, 0x000); /* MCLK=128fs */
	अन्यथा
		se200pci_WM8766_ग_लिखो(ice, 0x0a, 0x080); /* MCLK=256fs */
पूर्ण


/****************************************************************************/
/*  WM8776 पूर्णांकerface                                                        */
/****************************************************************************/

अटल व्योम se200pci_WM8776_ग_लिखो(काष्ठा snd_ice1712 *ice,
					अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक val;

	val = (addr << 9) | data;
	snd_vt1724_ग_लिखो_i2c(ice, 0x34, val >> 8, val & 0xff);
पूर्ण


अटल व्योम se200pci_WM8776_set_output_volume(काष्ठा snd_ice1712 *ice,
					अचिन्हित पूर्णांक vol1, अचिन्हित पूर्णांक vol2)
अणु
	se200pci_WM8776_ग_लिखो(ice, 0x03, vol1);
	se200pci_WM8776_ग_लिखो(ice, 0x04, vol2 | 0x100);
पूर्ण

अटल व्योम se200pci_WM8776_set_input_volume(काष्ठा snd_ice1712 *ice,
					अचिन्हित पूर्णांक vol1, अचिन्हित पूर्णांक vol2)
अणु
	se200pci_WM8776_ग_लिखो(ice, 0x0e, vol1);
	se200pci_WM8776_ग_लिखो(ice, 0x0f, vol2 | 0x100);
पूर्ण

अटल स्थिर अक्षर * स्थिर se200pci_sel[] = अणु
	"LINE-IN", "CD-IN", "MIC-IN", "ALL-MIX", शून्य
पूर्ण;

अटल व्योम se200pci_WM8776_set_input_selector(काष्ठा snd_ice1712 *ice,
					       अचिन्हित पूर्णांक sel)
अणु
	अटल स्थिर अचिन्हित अक्षर vals[] = अणु
		/* LINE, CD, MIC, ALL, GND */
		0x10, 0x04, 0x08, 0x1c, 0x03
	पूर्ण;
	अगर (sel > 4)
		sel = 4;
	se200pci_WM8776_ग_लिखो(ice, 0x15, vals[sel]);
पूर्ण

अटल व्योम se200pci_WM8776_set_afl(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक afl)
अणु
	/* AFL -- After Fader Listening */
	अगर (afl)
		se200pci_WM8776_ग_लिखो(ice, 0x16, 0x005);
	अन्यथा
		se200pci_WM8776_ग_लिखो(ice, 0x16, 0x001);
पूर्ण

अटल स्थिर अक्षर * स्थिर se200pci_agc[] = अणु
	"Off", "LimiterMode", "ALCMode", शून्य
पूर्ण;

अटल व्योम se200pci_WM8776_set_agc(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक agc)
अणु
	/* AGC -- Auto Gain Control of the input */
	चयन (agc) अणु
	हाल 0:
		se200pci_WM8776_ग_लिखो(ice, 0x11, 0x000); /* Off */
		अवरोध;
	हाल 1:
		se200pci_WM8776_ग_लिखो(ice, 0x10, 0x07b);
		se200pci_WM8776_ग_लिखो(ice, 0x11, 0x100); /* LimiterMode */
		अवरोध;
	हाल 2:
		se200pci_WM8776_ग_लिखो(ice, 0x10, 0x1fb);
		se200pci_WM8776_ग_लिखो(ice, 0x11, 0x100); /* ALCMode */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम se200pci_WM8776_init(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक i;
	अटल स्थिर अचिन्हित लघु शेष_values[] = अणु
		0x100, 0x100, 0x100,
		0x100, 0x100, 0x100,
		0x000, 0x090, 0x000, 0x000,
		0x022, 0x022, 0x022,
		0x008, 0x0cf, 0x0cf, 0x07b, 0x000,
		0x032, 0x000, 0x0a6, 0x001, 0x001
	पूर्ण;

	se200pci_WM8776_ग_लिखो(ice, 0x17, 0x000); /* reset all */
	/* ADC and DAC पूर्णांकerface is I2S 24bits mode */
 	/* The sample-rate are स्वतःmatically changed */
	udelay(10);
	/* BUT my board can not करो reset all, so I load all by manually. */
	क्रम (i = 0; i < ARRAY_SIZE(शेष_values); i++)
		se200pci_WM8776_ग_लिखो(ice, i, शेष_values[i]);

	se200pci_WM8776_set_input_selector(ice, 0);
	se200pci_WM8776_set_afl(ice, 0);
	se200pci_WM8776_set_agc(ice, 0);
	se200pci_WM8776_set_input_volume(ice, 0, 0);
	se200pci_WM8776_set_output_volume(ice, 0, 0);

	/* head phone mute and घातer करोwn */
	se200pci_WM8776_ग_लिखो(ice, 0x00, 0);
	se200pci_WM8776_ग_लिखो(ice, 0x01, 0);
	se200pci_WM8776_ग_लिखो(ice, 0x02, 0x100);
	se200pci_WM8776_ग_लिखो(ice, 0x0d, 0x080);
पूर्ण

अटल व्योम se200pci_WM8776_set_pro_rate(काष्ठा snd_ice1712 *ice,
						अचिन्हित पूर्णांक rate)
अणु
	/* nothing to करो */
पूर्ण


/****************************************************************************/
/*  runसमय पूर्णांकerface                                                       */
/****************************************************************************/

अटल व्योम se200pci_set_pro_rate(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate)
अणु
	se200pci_WM8740_set_pro_rate(ice, rate);
	se200pci_WM8766_set_pro_rate(ice, rate);
	se200pci_WM8776_set_pro_rate(ice, rate);
पूर्ण

काष्ठा se200pci_control अणु
	स्थिर अक्षर *name;
	क्रमागत अणु
		WM8766,
		WM8776in,
		WM8776out,
		WM8776sel,
		WM8776agc,
		WM8776afl
	पूर्ण target;
	क्रमागत अणु VOLUME1, VOLUME2, BOOLEAN, ENUM पूर्ण type;
	पूर्णांक ch;
	स्थिर अक्षर * स्थिर *member;
	स्थिर अक्षर *comment;
पूर्ण;

अटल स्थिर काष्ठा se200pci_control se200pci_cont[] = अणु
	अणु
		.name = "Front Playback Volume",
		.target = WM8776out,
		.type = VOLUME1,
		.comment = "Front(green)"
	पूर्ण,
	अणु
		.name = "Side Playback Volume",
		.target = WM8766,
		.type = VOLUME1,
		.ch = 1,
		.comment = "Surround(orange)"
	पूर्ण,
	अणु
		.name = "Surround Playback Volume",
		.target = WM8766,
		.type = VOLUME1,
		.ch = 2,
		.comment = "SurroundBack(white)"
	पूर्ण,
	अणु
		.name = "CLFE Playback Volume",
		.target = WM8766,
		.type = VOLUME1,
		.ch = 0,
		.comment = "Center(Lch)&SubWoofer(Rch)(black)"
	पूर्ण,
	अणु
		.name = "Capture Volume",
		.target = WM8776in,
		.type = VOLUME2
	पूर्ण,
	अणु
		.name = "Capture Select",
		.target = WM8776sel,
		.type = ENUM,
		.member = se200pci_sel
	पूर्ण,
	अणु
		.name = "AGC Capture Mode",
		.target = WM8776agc,
		.type = ENUM,
		.member = se200pci_agc
	पूर्ण,
	अणु
		.name = "AFL Bypass Playback Switch",
		.target = WM8776afl,
		.type = BOOLEAN
	पूर्ण
पूर्ण;

अटल पूर्णांक se200pci_get_क्रमागत_count(पूर्णांक n)
अणु
	स्थिर अक्षर * स्थिर *member;
	पूर्णांक c;

	member = se200pci_cont[n].member;
	अगर (!member)
		वापस 0;
	क्रम (c = 0; member[c]; c++)
		;
	वापस c;
पूर्ण

अटल पूर्णांक se200pci_cont_volume_info(काष्ठा snd_kcontrol *kc,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0; /* mute */
	uinfo->value.पूर्णांकeger.max = 0xff; /* 0dB */
	वापस 0;
पूर्ण

#घोषणा se200pci_cont_boolean_info	snd_ctl_boolean_mono_info

अटल पूर्णांक se200pci_cont_क्रमागत_info(काष्ठा snd_kcontrol *kc,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक n, c;

	n = kc->निजी_value;
	c = se200pci_get_क्रमागत_count(n);
	अगर (!c)
		वापस -EINVAL;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, c, se200pci_cont[n].member);
पूर्ण

अटल पूर्णांक se200pci_cont_volume_get(काष्ठा snd_kcontrol *kc,
				    काष्ठा snd_ctl_elem_value *uc)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kc);
	काष्ठा se_spec *spec = ice->spec;
	पूर्णांक n = kc->निजी_value;
	uc->value.पूर्णांकeger.value[0] = spec->vol[n].ch1;
	uc->value.पूर्णांकeger.value[1] = spec->vol[n].ch2;
	वापस 0;
पूर्ण

अटल पूर्णांक se200pci_cont_boolean_get(काष्ठा snd_kcontrol *kc,
				     काष्ठा snd_ctl_elem_value *uc)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kc);
	काष्ठा se_spec *spec = ice->spec;
	पूर्णांक n = kc->निजी_value;
	uc->value.पूर्णांकeger.value[0] = spec->vol[n].ch1;
	वापस 0;
पूर्ण

अटल पूर्णांक se200pci_cont_क्रमागत_get(काष्ठा snd_kcontrol *kc,
				  काष्ठा snd_ctl_elem_value *uc)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kc);
	काष्ठा se_spec *spec = ice->spec;
	पूर्णांक n = kc->निजी_value;
	uc->value.क्रमागतerated.item[0] = spec->vol[n].ch1;
	वापस 0;
पूर्ण

अटल व्योम se200pci_cont_update(काष्ठा snd_ice1712 *ice, पूर्णांक n)
अणु
	काष्ठा se_spec *spec = ice->spec;
	चयन (se200pci_cont[n].target) अणु
	हाल WM8766:
		se200pci_WM8766_set_volume(ice,
					   se200pci_cont[n].ch,
					   spec->vol[n].ch1,
					   spec->vol[n].ch2);
		अवरोध;

	हाल WM8776in:
		se200pci_WM8776_set_input_volume(ice,
						 spec->vol[n].ch1,
						 spec->vol[n].ch2);
		अवरोध;

	हाल WM8776out:
		se200pci_WM8776_set_output_volume(ice,
						  spec->vol[n].ch1,
						  spec->vol[n].ch2);
		अवरोध;

	हाल WM8776sel:
		se200pci_WM8776_set_input_selector(ice,
						   spec->vol[n].ch1);
		अवरोध;

	हाल WM8776agc:
		se200pci_WM8776_set_agc(ice, spec->vol[n].ch1);
		अवरोध;

	हाल WM8776afl:
		se200pci_WM8776_set_afl(ice, spec->vol[n].ch1);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक se200pci_cont_volume_put(काष्ठा snd_kcontrol *kc,
				    काष्ठा snd_ctl_elem_value *uc)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kc);
	काष्ठा se_spec *spec = ice->spec;
	पूर्णांक n = kc->निजी_value;
	अचिन्हित पूर्णांक vol1, vol2;
	पूर्णांक changed;

	changed = 0;
	vol1 = uc->value.पूर्णांकeger.value[0] & 0xff;
	vol2 = uc->value.पूर्णांकeger.value[1] & 0xff;
	अगर (spec->vol[n].ch1 != vol1) अणु
		spec->vol[n].ch1 = vol1;
		changed = 1;
	पूर्ण
	अगर (spec->vol[n].ch2 != vol2) अणु
		spec->vol[n].ch2 = vol2;
		changed = 1;
	पूर्ण
	अगर (changed)
		se200pci_cont_update(ice, n);

	वापस changed;
पूर्ण

अटल पूर्णांक se200pci_cont_boolean_put(काष्ठा snd_kcontrol *kc,
				     काष्ठा snd_ctl_elem_value *uc)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kc);
	काष्ठा se_spec *spec = ice->spec;
	पूर्णांक n = kc->निजी_value;
	अचिन्हित पूर्णांक vol1;

	vol1 = !!uc->value.पूर्णांकeger.value[0];
	अगर (spec->vol[n].ch1 != vol1) अणु
		spec->vol[n].ch1 = vol1;
		se200pci_cont_update(ice, n);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक se200pci_cont_क्रमागत_put(काष्ठा snd_kcontrol *kc,
				  काष्ठा snd_ctl_elem_value *uc)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kc);
	काष्ठा se_spec *spec = ice->spec;
	पूर्णांक n = kc->निजी_value;
	अचिन्हित पूर्णांक vol1;

	vol1 = uc->value.क्रमागतerated.item[0];
	अगर (vol1 >= se200pci_get_क्रमागत_count(n))
		वापस -EINVAL;
	अगर (spec->vol[n].ch1 != vol1) अणु
		spec->vol[n].ch1 = vol1;
		se200pci_cont_update(ice, n);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_gain1, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_gain2, -10350, 50, 1);

अटल पूर्णांक se200pci_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक i;
	काष्ठा snd_kcontrol_new cont;
	पूर्णांक err;

	स_रखो(&cont, 0, माप(cont));
	cont.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	क्रम (i = 0; i < ARRAY_SIZE(se200pci_cont); i++) अणु
		cont.निजी_value = i;
		cont.name = se200pci_cont[i].name;
		cont.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
		cont.tlv.p = शून्य;
		चयन (se200pci_cont[i].type) अणु
		हाल VOLUME1:
		हाल VOLUME2:
			cont.info = se200pci_cont_volume_info;
			cont.get = se200pci_cont_volume_get;
			cont.put = se200pci_cont_volume_put;
			cont.access |= SNDRV_CTL_ELEM_ACCESS_TLV_READ;
			अगर (se200pci_cont[i].type == VOLUME1)
				cont.tlv.p = db_scale_gain1;
			अन्यथा
				cont.tlv.p = db_scale_gain2;
			अवरोध;
		हाल BOOLEAN:
			cont.info = se200pci_cont_boolean_info;
			cont.get = se200pci_cont_boolean_get;
			cont.put = se200pci_cont_boolean_put;
			अवरोध;
		हाल ENUM:
			cont.info = se200pci_cont_क्रमागत_info;
			cont.get = se200pci_cont_क्रमागत_get;
			cont.put = se200pci_cont_क्रमागत_put;
			अवरोध;
		शेष:
			snd_BUG();
			वापस -EINVAL;
		पूर्ण
		err = snd_ctl_add(ice->card, snd_ctl_new1(&cont, ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण


/****************************************************************************/
/*  ONKYO WAVIO SE-90PCI                                                    */
/****************************************************************************/
/*
 *  प्रणाली configuration ICE_EEP2_SYSCONF=0x4b
 *  AC-Link configuration ICE_EEP2_ACLINK=0x80
 *  I2S converters feature ICE_EEP2_I2S=0x78
 *  S/PDIF configuration ICE_EEP2_SPDIF=0xc3
 *
 *  ** connected chip **
 *
 *   WM8716
 *      A 2ch-DAC of मुख्य outमाला_दो.
 *      It setuped as I2S mode by wire, so no way to setup from software.
 *         ML/I2S (28pin) -- +5V
 *         MC/DM1 (27pin) -- GND
 *         MC/DM0 (26pin) -- GND
 *         MUTEB  (25pin) -- खोलो (पूर्णांकernal pull-up)
 *         MODE   (24pin) -- GND
 *         CSBIWO (23pin) -- +5V
 *
 */

 /* Nothing to करो क्रम this chip. */


/****************************************************************************/
/*  probe/initialize/setup                                                  */
/****************************************************************************/

अटल पूर्णांक se_init(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा se_spec *spec;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;

	अगर (ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_SE90PCI) अणु
		ice->num_total_dacs = 2;
		ice->num_total_adcs = 0;
		ice->vt1720 = 1;
		वापस 0;

	पूर्ण अन्यथा अगर (ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_SE200PCI) अणु
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 2;
		se200pci_WM8740_init(ice);
		se200pci_WM8766_init(ice);
		se200pci_WM8776_init(ice);
		ice->gpio.set_pro_rate = se200pci_set_pro_rate;
		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक se_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक err;

	err = 0;
	/* nothing to करो क्रम VT1724_SUBDEVICE_SE90PCI */
	अगर (ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_SE200PCI)
		err = se200pci_add_controls(ice);

	वापस err;
पूर्ण


/****************************************************************************/
/*  entry poपूर्णांक                                                             */
/****************************************************************************/

अटल स्थिर अचिन्हित अक्षर se200pci_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]	= 0x4b,	/* 49.152Hz, spdअगर-in/ADC, 4DACs */
	[ICE_EEP2_ACLINK]	= 0x80,	/* I2S */
	[ICE_EEP2_I2S]		= 0x78,	/* 96k-ok, 24bit, 192k-ok */
	[ICE_EEP2_SPDIF]	= 0xc3,	/* out-en, out-पूर्णांक, spdअगर-in */

	[ICE_EEP2_GPIO_सूची]	= 0x02, /* WM8766 mute      1=output */
	[ICE_EEP2_GPIO_सूची1]	= 0x00, /* not used */
	[ICE_EEP2_GPIO_सूची2]	= 0x07, /* WM8766 ML/MC/MD  1=output */

	[ICE_EEP2_GPIO_MASK]	= 0x00, /* 0=writable */
	[ICE_EEP2_GPIO_MASK1]	= 0x00, /* 0=writable */
	[ICE_EEP2_GPIO_MASK2]	= 0x00, /* 0=writable */

	[ICE_EEP2_GPIO_STATE]	= 0x00, /* WM8766 mute=0 */
	[ICE_EEP2_GPIO_STATE1]	= 0x00, /* not used */
	[ICE_EEP2_GPIO_STATE2]	= 0x07, /* WM8766 ML/MC/MD */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर se90pci_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]	= 0x4b,	/* 49.152Hz, spdअगर-in/ADC, 4DACs */
	[ICE_EEP2_ACLINK]	= 0x80,	/* I2S */
	[ICE_EEP2_I2S]		= 0x78,	/* 96k-ok, 24bit, 192k-ok */
	[ICE_EEP2_SPDIF]	= 0xc3,	/* out-en, out-पूर्णांक, spdअगर-in */

	/* ALL GPIO bits are in input mode */
पूर्ण;

काष्ठा snd_ice1712_card_info snd_vt1724_se_cards[] = अणु
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_SE200PCI,
		.name = "ONKYO SE200PCI",
		.model = "se200pci",
		.chip_init = se_init,
		.build_controls = se_add_controls,
		.eeprom_size = माप(se200pci_eeprom),
		.eeprom_data = se200pci_eeprom,
	पूर्ण,
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_SE90PCI,
		.name = "ONKYO SE90PCI",
		.model = "se90pci",
		.chip_init = se_init,
		.build_controls = se_add_controls,
		.eeprom_size = माप(se90pci_eeprom),
		.eeprom_data = se90pci_eeprom,
	पूर्ण,
	अणुपूर्ण /*terminator*/
पूर्ण;
