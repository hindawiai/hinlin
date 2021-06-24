<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble VT1724 (Envy24HT)
 *
 *   Lowlevel functions क्रम Terratec Aureon cards
 *
 *	Copyright (c) 2003 Takashi Iwai <tiwai@suse.de>
 *
 * NOTES:
 *
 * - we reuse the काष्ठा snd_akm4xxx record क्रम storing the wm8770 codec data.
 *   both wm and akm codecs are pretty similar, so we can पूर्णांकegrate
 *   both controls in the future, once अगर wm codecs are reused in
 *   many boards.
 *
 * - DAC digital volumes are not implemented in the mixer.
 *   अगर they show better response than DAC analog volumes, we can use them
 *   instead.
 *
 *   Lowlevel functions क्रम AudioTrak Prodigy 7.1 (and possibly 192) cards
 *      Copyright (c) 2003 Dimitromanolakis Apostolos <apostol@cs.utoronto.ca>
 *
 *   version 0.82: Stable / not all features work yet (no communication with AC97 secondary)
 *       added 64x/128x oversampling चयन (should be 64x only क्रम 96khz)
 *       fixed some recording labels (still need to check the rest)
 *       recording is working probably thanks to correct wm8770 initialization
 *
 *   version 0.5: Initial release:
 *           working: analog output, mixer, headphone amplअगरier चयन
 *       not working: prety much everything अन्यथा, at least i could verअगरy that
 *                    we have no digital output, no capture, pretty bad clicks and poops
 *                    on mixer चयन and other coll stuff.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश "aureon.h"
#समावेश <sound/tlv.h>

/* AC97 रेजिस्टर cache क्रम Aureon */
काष्ठा aureon_spec अणु
	अचिन्हित लघु stac9744[64];
	अचिन्हित पूर्णांक cs8415_mux;
	अचिन्हित लघु master[2];
	अचिन्हित लघु vol[8];
	अचिन्हित अक्षर pca9554_out;
पूर्ण;

/* WM8770 रेजिस्टरs */
#घोषणा WM_DAC_ATTEN		0x00	/* DAC1-8 analog attenuation */
#घोषणा WM_DAC_MASTER_ATTEN	0x08	/* DAC master analog attenuation */
#घोषणा WM_DAC_DIG_ATTEN	0x09	/* DAC1-8 digital attenuation */
#घोषणा WM_DAC_DIG_MASTER_ATTEN	0x11	/* DAC master digital attenuation */
#घोषणा WM_PHASE_SWAP		0x12	/* DAC phase */
#घोषणा WM_DAC_CTRL1		0x13	/* DAC control bits */
#घोषणा WM_MUTE			0x14	/* mute controls */
#घोषणा WM_DAC_CTRL2		0x15	/* de-emphasis and zefo-flag */
#घोषणा WM_INT_CTRL		0x16	/* पूर्णांकerface control */
#घोषणा WM_MASTER		0x17	/* master घड़ी and mode */
#घोषणा WM_POWERDOWN		0x18	/* घातer-करोwn controls */
#घोषणा WM_ADC_GAIN		0x19	/* ADC gain L(19)/R(1a) */
#घोषणा WM_ADC_MUX		0x1b	/* input MUX */
#घोषणा WM_OUT_MUX1		0x1c	/* output MUX */
#घोषणा WM_OUT_MUX2		0x1e	/* output MUX */
#घोषणा WM_RESET		0x1f	/* software reset */

/* CS8415A रेजिस्टरs */
#घोषणा CS8415_CTRL1	0x01
#घोषणा CS8415_CTRL2	0x02
#घोषणा CS8415_QSUB		0x14
#घोषणा CS8415_RATIO	0x1E
#घोषणा CS8415_C_BUFFER	0x20
#घोषणा CS8415_ID		0x7F

/* PCA9554 रेजिस्टरs */
#घोषणा PCA9554_DEV     0x40            /* I2C device address */
#घोषणा PCA9554_IN      0x00            /* input port */
#घोषणा PCA9554_OUT     0x01            /* output port */
#घोषणा PCA9554_INVERT  0x02            /* input invert */
#घोषणा PCA9554_सूची     0x03            /* port directions */

/*
 * Aureon Universe additional controls using PCA9554
 */

/*
 * Send data to pca9554
 */
अटल व्योम aureon_pca9554_ग_लिखो(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर reg,
				 अचिन्हित अक्षर data)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक i, j;
	अचिन्हित अक्षर dev = PCA9554_DEV;  /* ID 0100000, ग_लिखो */
	अचिन्हित अक्षर val = 0;

	पंचांगp = snd_ice1712_gpio_पढ़ो(ice);

	snd_ice1712_gpio_set_mask(ice, ~(AUREON_SPI_MOSI|AUREON_SPI_CLK|
					 AUREON_WM_RW|AUREON_WM_CS|
					 AUREON_CS8415_CS));
	पंचांगp |= AUREON_WM_RW;
	पंचांगp |= AUREON_CS8415_CS | AUREON_WM_CS; /* disable SPI devices */

	पंचांगp &= ~AUREON_SPI_MOSI;
	पंचांगp &= ~AUREON_SPI_CLK;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(50);

	/*
	 * send i2c stop condition and start condition
	 * to obtain sane state
	 */
	पंचांगp |= AUREON_SPI_CLK;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(50);
	पंचांगp |= AUREON_SPI_MOSI;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(100);
	पंचांगp &= ~AUREON_SPI_MOSI;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(50);
	पंचांगp &= ~AUREON_SPI_CLK;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(100);
	/*
	 * send device address, command and value,
	 * skipping ack cycles in between
	 */
	क्रम (j = 0; j < 3; j++) अणु
		चयन (j) अणु
		हाल 0:
			val = dev;
			अवरोध;
		हाल 1:
			val = reg;
			अवरोध;
		हाल 2:
			val = data;
			अवरोध;
		पूर्ण
		क्रम (i = 7; i >= 0; i--) अणु
			पंचांगp &= ~AUREON_SPI_CLK;
			snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
			udelay(40);
			अगर (val & (1 << i))
				पंचांगp |= AUREON_SPI_MOSI;
			अन्यथा
				पंचांगp &= ~AUREON_SPI_MOSI;
			snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
			udelay(40);
			पंचांगp |= AUREON_SPI_CLK;
			snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
			udelay(40);
		पूर्ण
		पंचांगp &= ~AUREON_SPI_CLK;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(40);
		पंचांगp |= AUREON_SPI_CLK;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(40);
		पंचांगp &= ~AUREON_SPI_CLK;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(40);
	पूर्ण
	पंचांगp &= ~AUREON_SPI_CLK;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(40);
	पंचांगp &= ~AUREON_SPI_MOSI;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(40);
	पंचांगp |= AUREON_SPI_CLK;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(50);
	पंचांगp |= AUREON_SPI_MOSI;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(100);
पूर्ण

अटल पूर्णांक aureon_universe_inmux_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] =
		अणु"Internal Aux", "Wavetable", "Rear Line-In"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक aureon_universe_inmux_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा aureon_spec *spec = ice->spec;
	ucontrol->value.क्रमागतerated.item[0] = spec->pca9554_out;
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_universe_inmux_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा aureon_spec *spec = ice->spec;
	अचिन्हित अक्षर oval, nval;
	पूर्णांक change;

	nval = ucontrol->value.क्रमागतerated.item[0];
	अगर (nval >= 3)
		वापस -EINVAL;
	snd_ice1712_save_gpio_status(ice);
	oval = spec->pca9554_out;
	change = (oval != nval);
	अगर (change) अणु
		aureon_pca9554_ग_लिखो(ice, PCA9554_OUT, nval);
		spec->pca9554_out = nval;
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);
	वापस change;
पूर्ण


अटल व्योम aureon_ac97_ग_लिखो(काष्ठा snd_ice1712 *ice, अचिन्हित लघु reg,
			      अचिन्हित लघु val)
अणु
	काष्ठा aureon_spec *spec = ice->spec;
	अचिन्हित पूर्णांक पंचांगp;

	/* Send address to XILINX chip */
	पंचांगp = (snd_ice1712_gpio_पढ़ो(ice) & ~0xFF) | (reg & 0x7F);
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(10);
	पंचांगp |= AUREON_AC97_ADDR;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(10);
	पंचांगp &= ~AUREON_AC97_ADDR;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(10);

	/* Send low-order byte to XILINX chip */
	पंचांगp &= ~AUREON_AC97_DATA_MASK;
	पंचांगp |= val & AUREON_AC97_DATA_MASK;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(10);
	पंचांगp |= AUREON_AC97_DATA_LOW;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(10);
	पंचांगp &= ~AUREON_AC97_DATA_LOW;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(10);

	/* Send high-order byte to XILINX chip */
	पंचांगp &= ~AUREON_AC97_DATA_MASK;
	पंचांगp |= (val >> 8) & AUREON_AC97_DATA_MASK;

	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(10);
	पंचांगp |= AUREON_AC97_DATA_HIGH;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(10);
	पंचांगp &= ~AUREON_AC97_DATA_HIGH;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(10);

	/* Inकाष्ठा XILINX chip to parse the data to the STAC9744 chip */
	पंचांगp |= AUREON_AC97_COMMIT;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(10);
	पंचांगp &= ~AUREON_AC97_COMMIT;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(10);

	/* Store the data in out निजी buffer */
	spec->stac9744[(reg & 0x7F) >> 1] = val;
पूर्ण

अटल अचिन्हित लघु aureon_ac97_पढ़ो(काष्ठा snd_ice1712 *ice, अचिन्हित लघु reg)
अणु
	काष्ठा aureon_spec *spec = ice->spec;
	वापस spec->stac9744[(reg & 0x7F) >> 1];
पूर्ण

/*
 * Initialize STAC9744 chip
 */
अटल पूर्णांक aureon_ac97_init(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा aureon_spec *spec = ice->spec;
	पूर्णांक i;
	अटल स्थिर अचिन्हित लघु ac97_शेषs[] = अणु
		0x00, 0x9640,
		0x02, 0x8000,
		0x04, 0x8000,
		0x06, 0x8000,
		0x0C, 0x8008,
		0x0E, 0x8008,
		0x10, 0x8808,
		0x12, 0x8808,
		0x14, 0x8808,
		0x16, 0x8808,
		0x18, 0x8808,
		0x1C, 0x8000,
		0x26, 0x000F,
		0x28, 0x0201,
		0x2C, 0xBB80,
		0x32, 0xBB80,
		0x7C, 0x8384,
		0x7E, 0x7644,
		(अचिन्हित लघु)-1
	पूर्ण;
	अचिन्हित पूर्णांक पंचांगp;

	/* Cold reset */
	पंचांगp = (snd_ice1712_gpio_पढ़ो(ice) | AUREON_AC97_RESET) & ~AUREON_AC97_DATA_MASK;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(3);

	पंचांगp &= ~AUREON_AC97_RESET;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(3);

	पंचांगp |= AUREON_AC97_RESET;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(3);

	स_रखो(&spec->stac9744, 0, माप(spec->stac9744));
	क्रम (i = 0; ac97_शेषs[i] != (अचिन्हित लघु)-1; i += 2)
		spec->stac9744[(ac97_शेषs[i]) >> 1] = ac97_शेषs[i+1];

	/* Unmute AC'97 master volume permanently - muting is करोne by WM8770 */
	aureon_ac97_ग_लिखो(ice, AC97_MASTER, 0x0000);

	वापस 0;
पूर्ण

#घोषणा AUREON_AC97_STEREO	0x80

/*
 * AC'97 volume controls
 */
अटल पूर्णांक aureon_ac97_vol_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = kcontrol->निजी_value & AUREON_AC97_STEREO ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 31;
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_ac97_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु vol;

	mutex_lock(&ice->gpio_mutex);

	vol = aureon_ac97_पढ़ो(ice, kcontrol->निजी_value & 0x7F);
	ucontrol->value.पूर्णांकeger.value[0] = 0x1F - (vol & 0x1F);
	अगर (kcontrol->निजी_value & AUREON_AC97_STEREO)
		ucontrol->value.पूर्णांकeger.value[1] = 0x1F - ((vol >> 8) & 0x1F);

	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_ac97_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु ovol, nvol;
	पूर्णांक change;

	snd_ice1712_save_gpio_status(ice);

	ovol = aureon_ac97_पढ़ो(ice, kcontrol->निजी_value & 0x7F);
	nvol = (0x1F - ucontrol->value.पूर्णांकeger.value[0]) & 0x001F;
	अगर (kcontrol->निजी_value & AUREON_AC97_STEREO)
		nvol |= ((0x1F - ucontrol->value.पूर्णांकeger.value[1]) << 8) & 0x1F00;
	nvol |= ovol & ~0x1F1F;

	change = (ovol != nvol);
	अगर (change)
		aureon_ac97_ग_लिखो(ice, kcontrol->निजी_value & 0x7F, nvol);

	snd_ice1712_restore_gpio_status(ice);

	वापस change;
पूर्ण

/*
 * AC'97 mute controls
 */
#घोषणा aureon_ac97_mute_info	snd_ctl_boolean_mono_info

अटल पूर्णांक aureon_ac97_mute_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	mutex_lock(&ice->gpio_mutex);

	ucontrol->value.पूर्णांकeger.value[0] = aureon_ac97_पढ़ो(ice,
			kcontrol->निजी_value & 0x7F) & 0x8000 ? 0 : 1;

	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_ac97_mute_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु ovol, nvol;
	पूर्णांक change;

	snd_ice1712_save_gpio_status(ice);

	ovol = aureon_ac97_पढ़ो(ice, kcontrol->निजी_value & 0x7F);
	nvol = (ucontrol->value.पूर्णांकeger.value[0] ? 0x0000 : 0x8000) | (ovol & ~0x8000);

	change = (ovol != nvol);
	अगर (change)
		aureon_ac97_ग_लिखो(ice, kcontrol->निजी_value & 0x7F, nvol);

	snd_ice1712_restore_gpio_status(ice);

	वापस change;
पूर्ण

/*
 * AC'97 mute controls
 */
#घोषणा aureon_ac97_micboost_info	snd_ctl_boolean_mono_info

अटल पूर्णांक aureon_ac97_micboost_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	mutex_lock(&ice->gpio_mutex);

	ucontrol->value.पूर्णांकeger.value[0] = aureon_ac97_पढ़ो(ice, AC97_MIC) & 0x0020 ? 0 : 1;

	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_ac97_micboost_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु ovol, nvol;
	पूर्णांक change;

	snd_ice1712_save_gpio_status(ice);

	ovol = aureon_ac97_पढ़ो(ice, AC97_MIC);
	nvol = (ucontrol->value.पूर्णांकeger.value[0] ? 0x0000 : 0x0020) | (ovol & ~0x0020);

	change = (ovol != nvol);
	अगर (change)
		aureon_ac97_ग_लिखो(ice, AC97_MIC, nvol);

	snd_ice1712_restore_gpio_status(ice);

	वापस change;
पूर्ण

/*
 * ग_लिखो data in the SPI mode
 */
अटल व्योम aureon_spi_ग_लिखो(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक cs, अचिन्हित पूर्णांक data, पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक i;
	अचिन्हित पूर्णांक mosi, clk;

	पंचांगp = snd_ice1712_gpio_पढ़ो(ice);

	अगर (ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_PRODIGY71LT ||
	    ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_PRODIGY71XT) अणु
		snd_ice1712_gpio_set_mask(ice, ~(PRODIGY_SPI_MOSI|PRODIGY_SPI_CLK|PRODIGY_WM_CS));
		mosi = PRODIGY_SPI_MOSI;
		clk = PRODIGY_SPI_CLK;
	पूर्ण अन्यथा अणु
		snd_ice1712_gpio_set_mask(ice, ~(AUREON_WM_RW|AUREON_SPI_MOSI|AUREON_SPI_CLK|
						 AUREON_WM_CS|AUREON_CS8415_CS));
		mosi = AUREON_SPI_MOSI;
		clk = AUREON_SPI_CLK;

		पंचांगp |= AUREON_WM_RW;
	पूर्ण

	पंचांगp &= ~cs;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);

	क्रम (i = bits - 1; i >= 0; i--) अणु
		पंचांगp &= ~clk;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);
		अगर (data & (1 << i))
			पंचांगp |= mosi;
		अन्यथा
			पंचांगp &= ~mosi;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);
		पंचांगp |= clk;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);
	पूर्ण

	पंचांगp &= ~clk;
	पंचांगp |= cs;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
	पंचांगp |= clk;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
पूर्ण

/*
 * Read data in SPI mode
 */
अटल व्योम aureon_spi_पढ़ो(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक cs,
		अचिन्हित पूर्णांक data, पूर्णांक bits, अचिन्हित अक्षर *buffer, पूर्णांक size)
अणु
	पूर्णांक i, j;
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = (snd_ice1712_gpio_पढ़ो(ice) & ~AUREON_SPI_CLK) | AUREON_CS8415_CS|AUREON_WM_CS;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	पंचांगp &= ~cs;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);

	क्रम (i = bits-1; i >= 0; i--) अणु
		अगर (data & (1 << i))
			पंचांगp |= AUREON_SPI_MOSI;
		अन्यथा
			पंचांगp &= ~AUREON_SPI_MOSI;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);

		पंचांगp |= AUREON_SPI_CLK;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);

		पंचांगp &= ~AUREON_SPI_CLK;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);
	पूर्ण

	क्रम (j = 0; j < size; j++) अणु
		अचिन्हित अक्षर outdata = 0;
		क्रम (i = 7; i >= 0; i--) अणु
			पंचांगp = snd_ice1712_gpio_पढ़ो(ice);
			outdata <<= 1;
			outdata |= (पंचांगp & AUREON_SPI_MISO) ? 1 : 0;
			udelay(1);

			पंचांगp |= AUREON_SPI_CLK;
			snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
			udelay(1);

			पंचांगp &= ~AUREON_SPI_CLK;
			snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
			udelay(1);
		पूर्ण
		buffer[j] = outdata;
	पूर्ण

	पंचांगp |= cs;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
पूर्ण

अटल अचिन्हित अक्षर aureon_cs8415_get(काष्ठा snd_ice1712 *ice, पूर्णांक reg)
अणु
	अचिन्हित अक्षर val;
	aureon_spi_ग_लिखो(ice, AUREON_CS8415_CS, 0x2000 | reg, 16);
	aureon_spi_पढ़ो(ice, AUREON_CS8415_CS, 0x21, 8, &val, 1);
	वापस val;
पूर्ण

अटल व्योम aureon_cs8415_पढ़ो(काष्ठा snd_ice1712 *ice, पूर्णांक reg,
				अचिन्हित अक्षर *buffer, पूर्णांक size)
अणु
	aureon_spi_ग_लिखो(ice, AUREON_CS8415_CS, 0x2000 | reg, 16);
	aureon_spi_पढ़ो(ice, AUREON_CS8415_CS, 0x21, 8, buffer, size);
पूर्ण

अटल व्योम aureon_cs8415_put(काष्ठा snd_ice1712 *ice, पूर्णांक reg,
						अचिन्हित अक्षर val)
अणु
	aureon_spi_ग_लिखो(ice, AUREON_CS8415_CS, 0x200000 | (reg << 8) | val, 24);
पूर्ण

/*
 * get the current रेजिस्टर value of WM codec
 */
अटल अचिन्हित लघु wm_get(काष्ठा snd_ice1712 *ice, पूर्णांक reg)
अणु
	reg <<= 1;
	वापस ((अचिन्हित लघु)ice->akm[0].images[reg] << 8) |
		ice->akm[0].images[reg + 1];
पूर्ण

/*
 * set the रेजिस्टर value of WM codec
 */
अटल व्योम wm_put_nocache(काष्ठा snd_ice1712 *ice, पूर्णांक reg, अचिन्हित लघु val)
अणु
	aureon_spi_ग_लिखो(ice,
			 ((ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_PRODIGY71LT ||
			   ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_PRODIGY71XT) ?
			 PRODIGY_WM_CS : AUREON_WM_CS),
			(reg << 9) | (val & 0x1ff), 16);
पूर्ण

/*
 * set the रेजिस्टर value of WM codec and remember it
 */
अटल व्योम wm_put(काष्ठा snd_ice1712 *ice, पूर्णांक reg, अचिन्हित लघु val)
अणु
	wm_put_nocache(ice, reg, val);
	reg <<= 1;
	ice->akm[0].images[reg] = val >> 8;
	ice->akm[0].images[reg + 1] = val;
पूर्ण

/*
 */
#घोषणा aureon_mono_bool_info		snd_ctl_boolean_mono_info

/*
 * AC'97 master playback mute controls (Mute on WM8770 chip)
 */
#घोषणा aureon_ac97_mmute_info		snd_ctl_boolean_mono_info

अटल पूर्णांक aureon_ac97_mmute_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	mutex_lock(&ice->gpio_mutex);

	ucontrol->value.पूर्णांकeger.value[0] = (wm_get(ice, WM_OUT_MUX1) >> 1) & 0x01;

	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_ac97_mmute_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु ovol, nvol;
	पूर्णांक change;

	snd_ice1712_save_gpio_status(ice);

	ovol = wm_get(ice, WM_OUT_MUX1);
	nvol = (ovol & ~0x02) | (ucontrol->value.पूर्णांकeger.value[0] ? 0x02 : 0x00);
	change = (ovol != nvol);
	अगर (change)
		wm_put(ice, WM_OUT_MUX1, nvol);

	snd_ice1712_restore_gpio_status(ice);

	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_wm_dac, -10000, 100, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_wm_pcm, -6400, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_wm_adc, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_ac97_master, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_ac97_gain, -3450, 150, 0);

#घोषणा WM_VOL_MAX	100
#घोषणा WM_VOL_CNT	101	/* 0dB .. -100dB */
#घोषणा WM_VOL_MUTE	0x8000

अटल व्योम wm_set_vol(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक index, अचिन्हित लघु vol, अचिन्हित लघु master)
अणु
	अचिन्हित अक्षर nvol;

	अगर ((master & WM_VOL_MUTE) || (vol & WM_VOL_MUTE)) अणु
		nvol = 0;
	पूर्ण अन्यथा अणु
		nvol = ((vol % WM_VOL_CNT) * (master % WM_VOL_CNT)) /
								WM_VOL_MAX;
		nvol += 0x1b;
	पूर्ण

	wm_put(ice, index, nvol);
	wm_put_nocache(ice, index, 0x180 | nvol);
पूर्ण

/*
 * DAC mute control
 */
#घोषणा wm_pcm_mute_info	snd_ctl_boolean_mono_info

अटल पूर्णांक wm_pcm_mute_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	mutex_lock(&ice->gpio_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = (wm_get(ice, WM_MUTE) & 0x10) ? 0 : 1;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_pcm_mute_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु nval, oval;
	पूर्णांक change;

	snd_ice1712_save_gpio_status(ice);
	oval = wm_get(ice, WM_MUTE);
	nval = (oval & ~0x10) | (ucontrol->value.पूर्णांकeger.value[0] ? 0 : 0x10);
	change = (oval != nval);
	अगर (change)
		wm_put(ice, WM_MUTE, nval);
	snd_ice1712_restore_gpio_status(ice);

	वापस change;
पूर्ण

/*
 * Master volume attenuation mixer control
 */
अटल पूर्णांक wm_master_vol_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = WM_VOL_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_master_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा aureon_spec *spec = ice->spec;
	पूर्णांक i;
	क्रम (i = 0; i < 2; i++)
		ucontrol->value.पूर्णांकeger.value[i] =
			spec->master[i] & ~WM_VOL_MUTE;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_master_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा aureon_spec *spec = ice->spec;
	पूर्णांक ch, change = 0;

	snd_ice1712_save_gpio_status(ice);
	क्रम (ch = 0; ch < 2; ch++) अणु
		अचिन्हित पूर्णांक vol = ucontrol->value.पूर्णांकeger.value[ch];
		अगर (vol > WM_VOL_MAX)
			vol = WM_VOL_MAX;
		vol |= spec->master[ch] & WM_VOL_MUTE;
		अगर (vol != spec->master[ch]) अणु
			पूर्णांक dac;
			spec->master[ch] = vol;
			क्रम (dac = 0; dac < ice->num_total_dacs; dac += 2)
				wm_set_vol(ice, WM_DAC_ATTEN + dac + ch,
					   spec->vol[dac + ch],
					   spec->master[ch]);
			change = 1;
		पूर्ण
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);
	वापस change;
पूर्ण

/*
 * DAC volume attenuation mixer control
 */
अटल पूर्णांक wm_vol_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक voices = kcontrol->निजी_value >> 8;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = voices;
	uinfo->value.पूर्णांकeger.min = 0;		/* mute (-101dB) */
	uinfo->value.पूर्णांकeger.max = WM_VOL_MAX;	/* 0dB */
	वापस 0;
पूर्ण

अटल पूर्णांक wm_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा aureon_spec *spec = ice->spec;
	पूर्णांक i, ofs, voices;

	voices = kcontrol->निजी_value >> 8;
	ofs = kcontrol->निजी_value & 0xff;
	क्रम (i = 0; i < voices; i++)
		ucontrol->value.पूर्णांकeger.value[i] =
			spec->vol[ofs+i] & ~WM_VOL_MUTE;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा aureon_spec *spec = ice->spec;
	पूर्णांक i, idx, ofs, voices;
	पूर्णांक change = 0;

	voices = kcontrol->निजी_value >> 8;
	ofs = kcontrol->निजी_value & 0xff;
	snd_ice1712_save_gpio_status(ice);
	क्रम (i = 0; i < voices; i++) अणु
		अचिन्हित पूर्णांक vol = ucontrol->value.पूर्णांकeger.value[i];
		अगर (vol > WM_VOL_MAX)
			vol = WM_VOL_MAX;
		vol |= spec->vol[ofs+i] & WM_VOL_MUTE;
		अगर (vol != spec->vol[ofs+i]) अणु
			spec->vol[ofs+i] = vol;
			idx  = WM_DAC_ATTEN + ofs + i;
			wm_set_vol(ice, idx, spec->vol[ofs + i],
				   spec->master[i]);
			change = 1;
		पूर्ण
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);
	वापस change;
पूर्ण

/*
 * WM8770 mute control
 */
अटल पूर्णांक wm_mute_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = kcontrol->निजी_value >> 8;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_mute_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा aureon_spec *spec = ice->spec;
	पूर्णांक voices, ofs, i;

	voices = kcontrol->निजी_value >> 8;
	ofs = kcontrol->निजी_value & 0xFF;

	क्रम (i = 0; i < voices; i++)
		ucontrol->value.पूर्णांकeger.value[i] =
			(spec->vol[ofs + i] & WM_VOL_MUTE) ? 0 : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_mute_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा aureon_spec *spec = ice->spec;
	पूर्णांक change = 0, voices, ofs, i;

	voices = kcontrol->निजी_value >> 8;
	ofs = kcontrol->निजी_value & 0xFF;

	snd_ice1712_save_gpio_status(ice);
	क्रम (i = 0; i < voices; i++) अणु
		पूर्णांक val = (spec->vol[ofs + i] & WM_VOL_MUTE) ? 0 : 1;
		अगर (ucontrol->value.पूर्णांकeger.value[i] != val) अणु
			spec->vol[ofs + i] &= ~WM_VOL_MUTE;
			spec->vol[ofs + i] |=
				ucontrol->value.पूर्णांकeger.value[i] ? 0 : WM_VOL_MUTE;
			wm_set_vol(ice, ofs + i, spec->vol[ofs + i],
				   spec->master[i]);
			change = 1;
		पूर्ण
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);

	वापस change;
पूर्ण

/*
 * WM8770 master mute control
 */
#घोषणा wm_master_mute_info		snd_ctl_boolean_stereo_info

अटल पूर्णांक wm_master_mute_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा aureon_spec *spec = ice->spec;

	ucontrol->value.पूर्णांकeger.value[0] =
		(spec->master[0] & WM_VOL_MUTE) ? 0 : 1;
	ucontrol->value.पूर्णांकeger.value[1] =
		(spec->master[1] & WM_VOL_MUTE) ? 0 : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_master_mute_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा aureon_spec *spec = ice->spec;
	पूर्णांक change = 0, i;

	snd_ice1712_save_gpio_status(ice);
	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक val = (spec->master[i] & WM_VOL_MUTE) ? 0 : 1;
		अगर (ucontrol->value.पूर्णांकeger.value[i] != val) अणु
			पूर्णांक dac;
			spec->master[i] &= ~WM_VOL_MUTE;
			spec->master[i] |=
				ucontrol->value.पूर्णांकeger.value[i] ? 0 : WM_VOL_MUTE;
			क्रम (dac = 0; dac < ice->num_total_dacs; dac += 2)
				wm_set_vol(ice, WM_DAC_ATTEN + dac + i,
					   spec->vol[dac + i],
					   spec->master[i]);
			change = 1;
		पूर्ण
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);

	वापस change;
पूर्ण

/* digital master volume */
#घोषणा PCM_0dB 0xff
#घोषणा PCM_RES 128	/* -64dB */
#घोषणा PCM_MIN (PCM_0dB - PCM_RES)
अटल पूर्णांक wm_pcm_vol_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;		/* mute (-64dB) */
	uinfo->value.पूर्णांकeger.max = PCM_RES;	/* 0dB */
	वापस 0;
पूर्ण

अटल पूर्णांक wm_pcm_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	mutex_lock(&ice->gpio_mutex);
	val = wm_get(ice, WM_DAC_DIG_MASTER_ATTEN) & 0xff;
	val = val > PCM_MIN ? (val - PCM_MIN) : 0;
	ucontrol->value.पूर्णांकeger.value[0] = val;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_pcm_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु ovol, nvol;
	पूर्णांक change = 0;

	nvol = ucontrol->value.पूर्णांकeger.value[0];
	अगर (nvol > PCM_RES)
		वापस -EINVAL;
	snd_ice1712_save_gpio_status(ice);
	nvol = (nvol ? (nvol + PCM_MIN) : 0) & 0xff;
	ovol = wm_get(ice, WM_DAC_DIG_MASTER_ATTEN) & 0xff;
	अगर (ovol != nvol) अणु
		wm_put(ice, WM_DAC_DIG_MASTER_ATTEN, nvol); /* prelatch */
		wm_put_nocache(ice, WM_DAC_DIG_MASTER_ATTEN, nvol | 0x100); /* update */
		change = 1;
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);
	वापस change;
पूर्ण

/*
 * ADC mute control
 */
#घोषणा wm_adc_mute_info		snd_ctl_boolean_stereo_info

अटल पूर्णांक wm_adc_mute_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;
	पूर्णांक i;

	mutex_lock(&ice->gpio_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		val = wm_get(ice, WM_ADC_GAIN + i);
		ucontrol->value.पूर्णांकeger.value[i] = ~val>>5 & 0x1;
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_adc_mute_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु new, old;
	पूर्णांक i, change = 0;

	snd_ice1712_save_gpio_status(ice);
	क्रम (i = 0; i < 2; i++) अणु
		old = wm_get(ice, WM_ADC_GAIN + i);
		new = (~ucontrol->value.पूर्णांकeger.value[i]<<5&0x20) | (old&~0x20);
		अगर (new != old) अणु
			wm_put(ice, WM_ADC_GAIN + i, new);
			change = 1;
		पूर्ण
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);

	वापस change;
पूर्ण

/*
 * ADC gain mixer control
 */
अटल पूर्णांक wm_adc_vol_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;		/* -12dB */
	uinfo->value.पूर्णांकeger.max = 0x1f;	/* 19dB */
	वापस 0;
पूर्ण

अटल पूर्णांक wm_adc_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, idx;
	अचिन्हित लघु vol;

	mutex_lock(&ice->gpio_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		idx = WM_ADC_GAIN + i;
		vol = wm_get(ice, idx) & 0x1f;
		ucontrol->value.पूर्णांकeger.value[i] = vol;
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_adc_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, idx;
	अचिन्हित लघु ovol, nvol;
	पूर्णांक change = 0;

	snd_ice1712_save_gpio_status(ice);
	क्रम (i = 0; i < 2; i++) अणु
		idx  = WM_ADC_GAIN + i;
		nvol = ucontrol->value.पूर्णांकeger.value[i] & 0x1f;
		ovol = wm_get(ice, idx);
		अगर ((ovol & 0x1f) != nvol) अणु
			wm_put(ice, idx, nvol | (ovol & ~0x1f));
			change = 1;
		पूर्ण
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);
	वापस change;
पूर्ण

/*
 * ADC input mux mixer control
 */
अटल पूर्णांक wm_adc_mux_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"CD",		/* AIN1 */
		"Aux",		/* AIN2 */
		"Line",		/* AIN3 */
		"Mic",		/* AIN4 */
		"AC97"		/* AIN5 */
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर universe_texts[] = अणु
		"Aux1",		/* AIN1 */
		"CD",		/* AIN2 */
		"Phono",	/* AIN3 */
		"Line",		/* AIN4 */
		"Aux2",		/* AIN5 */
		"Mic",		/* AIN6 */
		"Aux3",		/* AIN7 */
		"AC97"		/* AIN8 */
	पूर्ण;
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	अगर (ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_AUREON71_UNIVERSE)
		वापस snd_ctl_क्रमागत_info(uinfo, 2, 8, universe_texts);
	अन्यथा
		वापस snd_ctl_क्रमागत_info(uinfo, 2, 5, texts);
पूर्ण

अटल पूर्णांक wm_adc_mux_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	mutex_lock(&ice->gpio_mutex);
	val = wm_get(ice, WM_ADC_MUX);
	ucontrol->value.क्रमागतerated.item[0] = val & 7;
	ucontrol->value.क्रमागतerated.item[1] = (val >> 4) & 7;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_adc_mux_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु oval, nval;
	पूर्णांक change;

	snd_ice1712_save_gpio_status(ice);
	oval = wm_get(ice, WM_ADC_MUX);
	nval = oval & ~0x77;
	nval |= ucontrol->value.क्रमागतerated.item[0] & 7;
	nval |= (ucontrol->value.क्रमागतerated.item[1] & 7) << 4;
	change = (oval != nval);
	अगर (change)
		wm_put(ice, WM_ADC_MUX, nval);
	snd_ice1712_restore_gpio_status(ice);
	वापस change;
पूर्ण

/*
 * CS8415 Input mux
 */
अटल पूर्णांक aureon_cs8415_mux_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अटल स्थिर अक्षर * स्थिर aureon_texts[] = अणु
		"CD",		/* RXP0 */
		"Optical"	/* RXP1 */
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर prodigy_texts[] = अणु
		"CD",
		"Coax"
	पूर्ण;
	अगर (ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_PRODIGY71)
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, prodigy_texts);
	अन्यथा
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, aureon_texts);
पूर्ण

अटल पूर्णांक aureon_cs8415_mux_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा aureon_spec *spec = ice->spec;

	/* snd_ice1712_save_gpio_status(ice); */
	/* val = aureon_cs8415_get(ice, CS8415_CTRL2); */
	ucontrol->value.क्रमागतerated.item[0] = spec->cs8415_mux;
	/* snd_ice1712_restore_gpio_status(ice); */
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_cs8415_mux_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा aureon_spec *spec = ice->spec;
	अचिन्हित लघु oval, nval;
	पूर्णांक change;

	snd_ice1712_save_gpio_status(ice);
	oval = aureon_cs8415_get(ice, CS8415_CTRL2);
	nval = oval & ~0x07;
	nval |= ucontrol->value.क्रमागतerated.item[0] & 7;
	change = (oval != nval);
	अगर (change)
		aureon_cs8415_put(ice, CS8415_CTRL2, nval);
	snd_ice1712_restore_gpio_status(ice);
	spec->cs8415_mux = ucontrol->value.क्रमागतerated.item[0];
	वापस change;
पूर्ण

अटल पूर्णांक aureon_cs8415_rate_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 192000;
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_cs8415_rate_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर ratio;
	ratio = aureon_cs8415_get(ice, CS8415_RATIO);
	ucontrol->value.पूर्णांकeger.value[0] = (पूर्णांक)((अचिन्हित पूर्णांक)ratio * 750);
	वापस 0;
पूर्ण

/*
 * CS8415A Mute
 */
#घोषणा aureon_cs8415_mute_info		snd_ctl_boolean_mono_info

अटल पूर्णांक aureon_cs8415_mute_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	snd_ice1712_save_gpio_status(ice);
	ucontrol->value.पूर्णांकeger.value[0] = (aureon_cs8415_get(ice, CS8415_CTRL1) & 0x20) ? 0 : 1;
	snd_ice1712_restore_gpio_status(ice);
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_cs8415_mute_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर oval, nval;
	पूर्णांक change;
	snd_ice1712_save_gpio_status(ice);
	oval = aureon_cs8415_get(ice, CS8415_CTRL1);
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		nval = oval & ~0x20;
	अन्यथा
		nval = oval | 0x20;
	change = (oval != nval);
	अगर (change)
		aureon_cs8415_put(ice, CS8415_CTRL1, nval);
	snd_ice1712_restore_gpio_status(ice);
	वापस change;
पूर्ण

/*
 * CS8415A Q-Sub info
 */
अटल पूर्णांक aureon_cs8415_qsub_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = 10;
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_cs8415_qsub_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	snd_ice1712_save_gpio_status(ice);
	aureon_cs8415_पढ़ो(ice, CS8415_QSUB, ucontrol->value.bytes.data, 10);
	snd_ice1712_restore_gpio_status(ice);

	वापस 0;
पूर्ण

अटल पूर्णांक aureon_cs8415_spdअगर_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_cs8415_mask_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	स_रखो(ucontrol->value.iec958.status, 0xFF, 24);
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_cs8415_spdअगर_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	snd_ice1712_save_gpio_status(ice);
	aureon_cs8415_पढ़ो(ice, CS8415_C_BUFFER, ucontrol->value.iec958.status, 24);
	snd_ice1712_restore_gpio_status(ice);
	वापस 0;
पूर्ण

/*
 * Headphone Amplअगरier
 */
अटल पूर्णांक aureon_set_headphone_amp(काष्ठा snd_ice1712 *ice, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक पंचांगp, पंचांगp2;

	पंचांगp2 = पंचांगp = snd_ice1712_gpio_पढ़ो(ice);
	अगर (enable)
		अगर (ice->eeprom.subvenकरोr != VT1724_SUBDEVICE_PRODIGY71LT &&
		    ice->eeprom.subvenकरोr != VT1724_SUBDEVICE_PRODIGY71XT)
			पंचांगp |= AUREON_HP_SEL;
		अन्यथा
			पंचांगp |= PRODIGY_HP_SEL;
	अन्यथा
		अगर (ice->eeprom.subvenकरोr != VT1724_SUBDEVICE_PRODIGY71LT &&
		    ice->eeprom.subvenकरोr != VT1724_SUBDEVICE_PRODIGY71XT)
			पंचांगp &= ~AUREON_HP_SEL;
		अन्यथा
			पंचांगp &= ~PRODIGY_HP_SEL;
	अगर (पंचांगp != पंचांगp2) अणु
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_get_headphone_amp(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक पंचांगp = snd_ice1712_gpio_पढ़ो(ice);

	वापस (पंचांगp & AUREON_HP_SEL) != 0;
पूर्ण

#घोषणा aureon_hpamp_info	snd_ctl_boolean_mono_info

अटल पूर्णांक aureon_hpamp_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = aureon_get_headphone_amp(ice);
	वापस 0;
पूर्ण


अटल पूर्णांक aureon_hpamp_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	वापस aureon_set_headphone_amp(ice, ucontrol->value.पूर्णांकeger.value[0]);
पूर्ण

/*
 * Deemphasis
 */

#घोषणा aureon_deemp_info	snd_ctl_boolean_mono_info

अटल पूर्णांक aureon_deemp_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = (wm_get(ice, WM_DAC_CTRL2) & 0xf) == 0xf;
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_deemp_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक temp, temp2;
	temp2 = temp = wm_get(ice, WM_DAC_CTRL2);
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		temp |= 0xf;
	अन्यथा
		temp &= ~0xf;
	अगर (temp != temp2) अणु
		wm_put(ice, WM_DAC_CTRL2, temp);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * ADC Oversampling
 */
अटल पूर्णांक aureon_oversampling_info(काष्ठा snd_kcontrol *k, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु "128x", "64x"	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक aureon_oversampling_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = (wm_get(ice, WM_MASTER) & 0x8) == 0x8;
	वापस 0;
पूर्ण

अटल पूर्णांक aureon_oversampling_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक temp, temp2;
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	temp2 = temp = wm_get(ice, WM_MASTER);

	अगर (ucontrol->value.क्रमागतerated.item[0])
		temp |= 0x8;
	अन्यथा
		temp &= ~0x8;

	अगर (temp != temp2) अणु
		wm_put(ice, WM_MASTER, temp);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * mixers
 */

अटल स्थिर काष्ठा snd_kcontrol_new aureon_dac_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Master Playback Switch",
		.info = wm_master_mute_info,
		.get = wm_master_mute_get,
		.put = wm_master_mute_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Master Playback Volume",
		.info = wm_master_vol_info,
		.get = wm_master_vol_get,
		.put = wm_master_vol_put,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Front Playback Switch",
		.info = wm_mute_info,
		.get = wm_mute_get,
		.put = wm_mute_put,
		.निजी_value = (2 << 8) | 0
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Front Playback Volume",
		.info = wm_vol_info,
		.get = wm_vol_get,
		.put = wm_vol_put,
		.निजी_value = (2 << 8) | 0,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Rear Playback Switch",
		.info = wm_mute_info,
		.get = wm_mute_get,
		.put = wm_mute_put,
		.निजी_value = (2 << 8) | 2
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Rear Playback Volume",
		.info = wm_vol_info,
		.get = wm_vol_get,
		.put = wm_vol_put,
		.निजी_value = (2 << 8) | 2,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Center Playback Switch",
		.info = wm_mute_info,
		.get = wm_mute_get,
		.put = wm_mute_put,
		.निजी_value = (1 << 8) | 4
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Center Playback Volume",
		.info = wm_vol_info,
		.get = wm_vol_get,
		.put = wm_vol_put,
		.निजी_value = (1 << 8) | 4,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "LFE Playback Switch",
		.info = wm_mute_info,
		.get = wm_mute_get,
		.put = wm_mute_put,
		.निजी_value = (1 << 8) | 5
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "LFE Playback Volume",
		.info = wm_vol_info,
		.get = wm_vol_get,
		.put = wm_vol_put,
		.निजी_value = (1 << 8) | 5,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Side Playback Switch",
		.info = wm_mute_info,
		.get = wm_mute_get,
		.put = wm_mute_put,
		.निजी_value = (2 << 8) | 6
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Side Playback Volume",
		.info = wm_vol_info,
		.get = wm_vol_get,
		.put = wm_vol_put,
		.निजी_value = (2 << 8) | 6,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "PCM Playback Switch",
		.info = wm_pcm_mute_info,
		.get = wm_pcm_mute_get,
		.put = wm_pcm_mute_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "PCM Playback Volume",
		.info = wm_pcm_vol_info,
		.get = wm_pcm_vol_get,
		.put = wm_pcm_vol_put,
		.tlv = अणु .p = db_scale_wm_pcm पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Capture Switch",
		.info = wm_adc_mute_info,
		.get = wm_adc_mute_get,
		.put = wm_adc_mute_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Capture Volume",
		.info = wm_adc_vol_info,
		.get = wm_adc_vol_get,
		.put = wm_adc_vol_put,
		.tlv = अणु .p = db_scale_wm_adc पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Capture Source",
		.info = wm_adc_mux_info,
		.get = wm_adc_mux_get,
		.put = wm_adc_mux_put,
		.निजी_value = 5
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "External Amplifier",
		.info = aureon_hpamp_info,
		.get = aureon_hpamp_get,
		.put = aureon_hpamp_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "DAC Deemphasis Switch",
		.info = aureon_deemp_info,
		.get = aureon_deemp_get,
		.put = aureon_deemp_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "ADC Oversampling",
		.info = aureon_oversampling_info,
		.get = aureon_oversampling_get,
		.put = aureon_oversampling_put
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ac97_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "AC97 Playback Switch",
		.info = aureon_ac97_mmute_info,
		.get = aureon_ac97_mmute_get,
		.put = aureon_ac97_mmute_put,
		.निजी_value = AC97_MASTER
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "AC97 Playback Volume",
		.info = aureon_ac97_vol_info,
		.get = aureon_ac97_vol_get,
		.put = aureon_ac97_vol_put,
		.निजी_value = AC97_MASTER|AUREON_AC97_STEREO,
		.tlv = अणु .p = db_scale_ac97_master पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "CD Playback Switch",
		.info = aureon_ac97_mute_info,
		.get = aureon_ac97_mute_get,
		.put = aureon_ac97_mute_put,
		.निजी_value = AC97_CD
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "CD Playback Volume",
		.info = aureon_ac97_vol_info,
		.get = aureon_ac97_vol_get,
		.put = aureon_ac97_vol_put,
		.निजी_value = AC97_CD|AUREON_AC97_STEREO,
		.tlv = अणु .p = db_scale_ac97_gain पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Aux Playback Switch",
		.info = aureon_ac97_mute_info,
		.get = aureon_ac97_mute_get,
		.put = aureon_ac97_mute_put,
		.निजी_value = AC97_AUX,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Aux Playback Volume",
		.info = aureon_ac97_vol_info,
		.get = aureon_ac97_vol_get,
		.put = aureon_ac97_vol_put,
		.निजी_value = AC97_AUX|AUREON_AC97_STEREO,
		.tlv = अणु .p = db_scale_ac97_gain पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Line Playback Switch",
		.info = aureon_ac97_mute_info,
		.get = aureon_ac97_mute_get,
		.put = aureon_ac97_mute_put,
		.निजी_value = AC97_LINE
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Line Playback Volume",
		.info = aureon_ac97_vol_info,
		.get = aureon_ac97_vol_get,
		.put = aureon_ac97_vol_put,
		.निजी_value = AC97_LINE|AUREON_AC97_STEREO,
		.tlv = अणु .p = db_scale_ac97_gain पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Mic Playback Switch",
		.info = aureon_ac97_mute_info,
		.get = aureon_ac97_mute_get,
		.put = aureon_ac97_mute_put,
		.निजी_value = AC97_MIC
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Mic Playback Volume",
		.info = aureon_ac97_vol_info,
		.get = aureon_ac97_vol_get,
		.put = aureon_ac97_vol_put,
		.निजी_value = AC97_MIC,
		.tlv = अणु .p = db_scale_ac97_gain पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Mic Boost (+20dB)",
		.info = aureon_ac97_micboost_info,
		.get = aureon_ac97_micboost_get,
		.put = aureon_ac97_micboost_put
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new universe_ac97_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "AC97 Playback Switch",
		.info = aureon_ac97_mmute_info,
		.get = aureon_ac97_mmute_get,
		.put = aureon_ac97_mmute_put,
		.निजी_value = AC97_MASTER
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "AC97 Playback Volume",
		.info = aureon_ac97_vol_info,
		.get = aureon_ac97_vol_get,
		.put = aureon_ac97_vol_put,
		.निजी_value = AC97_MASTER|AUREON_AC97_STEREO,
		.tlv = अणु .p = db_scale_ac97_master पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "CD Playback Switch",
		.info = aureon_ac97_mute_info,
		.get = aureon_ac97_mute_get,
		.put = aureon_ac97_mute_put,
		.निजी_value = AC97_AUX
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "CD Playback Volume",
		.info = aureon_ac97_vol_info,
		.get = aureon_ac97_vol_get,
		.put = aureon_ac97_vol_put,
		.निजी_value = AC97_AUX|AUREON_AC97_STEREO,
		.tlv = अणु .p = db_scale_ac97_gain पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Phono Playback Switch",
		.info = aureon_ac97_mute_info,
		.get = aureon_ac97_mute_get,
		.put = aureon_ac97_mute_put,
		.निजी_value = AC97_CD
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Phono Playback Volume",
		.info = aureon_ac97_vol_info,
		.get = aureon_ac97_vol_get,
		.put = aureon_ac97_vol_put,
		.निजी_value = AC97_CD|AUREON_AC97_STEREO,
		.tlv = अणु .p = db_scale_ac97_gain पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Line Playback Switch",
		.info = aureon_ac97_mute_info,
		.get = aureon_ac97_mute_get,
		.put = aureon_ac97_mute_put,
		.निजी_value = AC97_LINE
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Line Playback Volume",
		.info = aureon_ac97_vol_info,
		.get = aureon_ac97_vol_get,
		.put = aureon_ac97_vol_put,
		.निजी_value = AC97_LINE|AUREON_AC97_STEREO,
		.tlv = अणु .p = db_scale_ac97_gain पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Mic Playback Switch",
		.info = aureon_ac97_mute_info,
		.get = aureon_ac97_mute_get,
		.put = aureon_ac97_mute_put,
		.निजी_value = AC97_MIC
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Mic Playback Volume",
		.info = aureon_ac97_vol_info,
		.get = aureon_ac97_vol_get,
		.put = aureon_ac97_vol_put,
		.निजी_value = AC97_MIC,
		.tlv = अणु .p = db_scale_ac97_gain पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Mic Boost (+20dB)",
		.info = aureon_ac97_micboost_info,
		.get = aureon_ac97_micboost_get,
		.put = aureon_ac97_micboost_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Aux Playback Switch",
		.info = aureon_ac97_mute_info,
		.get = aureon_ac97_mute_get,
		.put = aureon_ac97_mute_put,
		.निजी_value = AC97_VIDEO,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Aux Playback Volume",
		.info = aureon_ac97_vol_info,
		.get = aureon_ac97_vol_get,
		.put = aureon_ac97_vol_put,
		.निजी_value = AC97_VIDEO|AUREON_AC97_STEREO,
		.tlv = अणु .p = db_scale_ac97_gain पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Aux Source",
		.info = aureon_universe_inmux_info,
		.get = aureon_universe_inmux_get,
		.put = aureon_universe_inmux_put
	पूर्ण

पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cs8415_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, SWITCH),
		.info = aureon_cs8415_mute_info,
		.get = aureon_cs8415_mute_get,
		.put = aureon_cs8415_mute_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, NONE) "Source",
		.info = aureon_cs8415_mux_info,
		.get = aureon_cs8415_mux_get,
		.put = aureon_cs8415_mux_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("Q-subcode ", CAPTURE, DEFAULT),
		.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = aureon_cs8415_qsub_info,
		.get = aureon_cs8415_qsub_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, MASK),
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.info = aureon_cs8415_spdअगर_info,
		.get = aureon_cs8415_mask_get
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, DEFAULT),
		.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = aureon_cs8415_spdअगर_info,
		.get = aureon_cs8415_spdअगर_get
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, NONE) "Rate",
		.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = aureon_cs8415_rate_info,
		.get = aureon_cs8415_rate_get
	पूर्ण
पूर्ण;

अटल पूर्णांक aureon_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक i, counts;
	पूर्णांक err;

	counts = ARRAY_SIZE(aureon_dac_controls);
	अगर (ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_AUREON51_SKY)
		counts -= 2; /* no side */
	क्रम (i = 0; i < counts; i++) अणु
		err = snd_ctl_add(ice->card, snd_ctl_new1(&aureon_dac_controls[i], ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm_controls); i++) अणु
		err = snd_ctl_add(ice->card, snd_ctl_new1(&wm_controls[i], ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_AUREON71_UNIVERSE) अणु
		क्रम (i = 0; i < ARRAY_SIZE(universe_ac97_controls); i++) अणु
			err = snd_ctl_add(ice->card, snd_ctl_new1(&universe_ac97_controls[i], ice));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण अन्यथा अगर (ice->eeprom.subvenकरोr != VT1724_SUBDEVICE_PRODIGY71LT &&
		 ice->eeprom.subvenकरोr != VT1724_SUBDEVICE_PRODIGY71XT) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ac97_controls); i++) अणु
			err = snd_ctl_add(ice->card, snd_ctl_new1(&ac97_controls[i], ice));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (ice->eeprom.subvenकरोr != VT1724_SUBDEVICE_PRODIGY71LT &&
	    ice->eeprom.subvenकरोr != VT1724_SUBDEVICE_PRODIGY71XT) अणु
		अचिन्हित अक्षर id;
		snd_ice1712_save_gpio_status(ice);
		id = aureon_cs8415_get(ice, CS8415_ID);
		अगर (id != 0x41)
			dev_info(ice->card->dev,
				 "No CS8415 chip. Skipping CS8415 controls.\n");
		अन्यथा अगर ((id & 0x0F) != 0x01)
			dev_info(ice->card->dev,
				 "Detected unsupported CS8415 rev. (%c)\n",
				 (अक्षर)((id & 0x0F) + 'A' - 1));
		अन्यथा अणु
			क्रम (i = 0; i < ARRAY_SIZE(cs8415_controls); i++) अणु
				काष्ठा snd_kcontrol *kctl;
				err = snd_ctl_add(ice->card, (kctl = snd_ctl_new1(&cs8415_controls[i], ice)));
				अगर (err < 0)
					वापस err;
				अगर (i > 1)
					kctl->id.device = ice->pcm->device;
			पूर्ण
		पूर्ण
		snd_ice1712_restore_gpio_status(ice);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * reset the chip
 */
अटल पूर्णांक aureon_reset(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित लघु wm_inits_aureon[] = अणु
		/* These come first to reduce init pop noise */
		0x1b, 0x044,		/* ADC Mux (AC'97 source) */
		0x1c, 0x00B,		/* Out Mux1 (VOUT1 = DAC+AUX, VOUT2 = DAC) */
		0x1d, 0x009,		/* Out Mux2 (VOUT2 = DAC, VOUT3 = DAC) */

		0x18, 0x000,		/* All घातer-up */

		0x16, 0x122,		/* I2S, normal polarity, 24bit */
		0x17, 0x022,		/* 256fs, slave mode */
		0x00, 0,		/* DAC1 analog mute */
		0x01, 0,		/* DAC2 analog mute */
		0x02, 0,		/* DAC3 analog mute */
		0x03, 0,		/* DAC4 analog mute */
		0x04, 0,		/* DAC5 analog mute */
		0x05, 0,		/* DAC6 analog mute */
		0x06, 0,		/* DAC7 analog mute */
		0x07, 0,		/* DAC8 analog mute */
		0x08, 0x100,		/* master analog mute */
		0x09, 0xff,		/* DAC1 digital full */
		0x0a, 0xff,		/* DAC2 digital full */
		0x0b, 0xff,		/* DAC3 digital full */
		0x0c, 0xff,		/* DAC4 digital full */
		0x0d, 0xff,		/* DAC5 digital full */
		0x0e, 0xff,		/* DAC6 digital full */
		0x0f, 0xff,		/* DAC7 digital full */
		0x10, 0xff,		/* DAC8 digital full */
		0x11, 0x1ff,		/* master digital full */
		0x12, 0x000,		/* phase normal */
		0x13, 0x090,		/* unmute DAC L/R */
		0x14, 0x000,		/* all unmute */
		0x15, 0x000,		/* no deemphasis, no ZFLG */
		0x19, 0x000,		/* -12dB ADC/L */
		0x1a, 0x000,		/* -12dB ADC/R */
		(अचिन्हित लघु)-1
	पूर्ण;
	अटल स्थिर अचिन्हित लघु wm_inits_prodigy[] = अणु

		/* These come first to reduce init pop noise */
		0x1b, 0x000,		/* ADC Mux */
		0x1c, 0x009,		/* Out Mux1 */
		0x1d, 0x009,		/* Out Mux2 */

		0x18, 0x000,		/* All घातer-up */

		0x16, 0x022,		/* I2S, normal polarity, 24bit, high-pass on */
		0x17, 0x006,		/* 128fs, slave mode */

		0x00, 0,		/* DAC1 analog mute */
		0x01, 0,		/* DAC2 analog mute */
		0x02, 0,		/* DAC3 analog mute */
		0x03, 0,		/* DAC4 analog mute */
		0x04, 0,		/* DAC5 analog mute */
		0x05, 0,		/* DAC6 analog mute */
		0x06, 0,		/* DAC7 analog mute */
		0x07, 0,		/* DAC8 analog mute */
		0x08, 0x100,		/* master analog mute */

		0x09, 0x7f,		/* DAC1 digital full */
		0x0a, 0x7f,		/* DAC2 digital full */
		0x0b, 0x7f,		/* DAC3 digital full */
		0x0c, 0x7f,		/* DAC4 digital full */
		0x0d, 0x7f,		/* DAC5 digital full */
		0x0e, 0x7f,		/* DAC6 digital full */
		0x0f, 0x7f,		/* DAC7 digital full */
		0x10, 0x7f,		/* DAC8 digital full */
		0x11, 0x1FF,		/* master digital full */

		0x12, 0x000,		/* phase normal */
		0x13, 0x090,		/* unmute DAC L/R */
		0x14, 0x000,		/* all unmute */
		0x15, 0x000,		/* no deemphasis, no ZFLG */

		0x19, 0x000,		/* -12dB ADC/L */
		0x1a, 0x000,		/* -12dB ADC/R */
		(अचिन्हित लघु)-1

	पूर्ण;
	अटल स्थिर अचिन्हित लघु cs_inits[] = अणु
		0x0441, /* RUN */
		0x0180, /* no mute, OMCK output on RMCK pin */
		0x0201, /* S/PDIF source on RXP1 */
		0x0605, /* slave, 24bit, MSB on second OSCLK, SDOUT क्रम right channel when OLRCK is high */
		(अचिन्हित लघु)-1
	पूर्ण;
	अचिन्हित पूर्णांक पंचांगp;
	स्थिर अचिन्हित लघु *p;
	पूर्णांक err;
	काष्ठा aureon_spec *spec = ice->spec;

	err = aureon_ac97_init(ice);
	अगर (err != 0)
		वापस err;

	snd_ice1712_gpio_set_dir(ice, 0x5fffff); /* fix this क्रम the समय being */

	/* reset the wm codec as the SPI mode */
	snd_ice1712_save_gpio_status(ice);
	snd_ice1712_gpio_set_mask(ice, ~(AUREON_WM_RESET|AUREON_WM_CS|AUREON_CS8415_CS|AUREON_HP_SEL));

	पंचांगp = snd_ice1712_gpio_पढ़ो(ice);
	पंचांगp &= ~AUREON_WM_RESET;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
	पंचांगp |= AUREON_WM_CS | AUREON_CS8415_CS;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
	पंचांगp |= AUREON_WM_RESET;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);

	/* initialize WM8770 codec */
	अगर (ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_PRODIGY71 ||
		ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_PRODIGY71LT ||
		ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_PRODIGY71XT)
		p = wm_inits_prodigy;
	अन्यथा
		p = wm_inits_aureon;
	क्रम (; *p != (अचिन्हित लघु)-1; p += 2)
		wm_put(ice, p[0], p[1]);

	/* initialize CS8415A codec */
	अगर (ice->eeprom.subvenकरोr != VT1724_SUBDEVICE_PRODIGY71LT &&
	    ice->eeprom.subvenकरोr != VT1724_SUBDEVICE_PRODIGY71XT) अणु
		क्रम (p = cs_inits; *p != (अचिन्हित लघु)-1; p++)
			aureon_spi_ग_लिखो(ice, AUREON_CS8415_CS, *p | 0x200000, 24);
		spec->cs8415_mux = 1;

		aureon_set_headphone_amp(ice, 1);
	पूर्ण

	snd_ice1712_restore_gpio_status(ice);

	/* initialize PCA9554 pin directions & set शेष input */
	aureon_pca9554_ग_लिखो(ice, PCA9554_सूची, 0x00);
	aureon_pca9554_ग_लिखो(ice, PCA9554_OUT, 0x00);   /* पूर्णांकernal AUX */
	वापस 0;
पूर्ण

/*
 * suspend/resume
 */
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक aureon_resume(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा aureon_spec *spec = ice->spec;
	पूर्णांक err, i;

	err = aureon_reset(ice);
	अगर (err != 0)
		वापस err;

	/* workaround क्रम poking volume with alsamixer after resume:
	 * just set stored volume again */
	क्रम (i = 0; i < ice->num_total_dacs; i++)
		wm_set_vol(ice, i, spec->vol[i], spec->master[i % 2]);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * initialize the chip
 */
अटल पूर्णांक aureon_init(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा aureon_spec *spec;
	पूर्णांक i, err;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;

	अगर (ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_AUREON51_SKY) अणु
		ice->num_total_dacs = 6;
		ice->num_total_adcs = 2;
	पूर्ण अन्यथा अणु
		/* aureon 7.1 and prodigy 7.1 */
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 2;
	पूर्ण

	/* to remember the रेजिस्टर values of CS8415 */
	ice->akm = kzalloc(माप(काष्ठा snd_akm4xxx), GFP_KERNEL);
	अगर (!ice->akm)
		वापस -ENOMEM;
	ice->akm_codecs = 1;

	err = aureon_reset(ice);
	अगर (err != 0)
		वापस err;

	spec->master[0] = WM_VOL_MUTE;
	spec->master[1] = WM_VOL_MUTE;
	क्रम (i = 0; i < ice->num_total_dacs; i++) अणु
		spec->vol[i] = WM_VOL_MUTE;
		wm_set_vol(ice, i, spec->vol[i], spec->master[i % 2]);
	पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
	ice->pm_resume = aureon_resume;
	ice->pm_suspend_enabled = 1;
#पूर्ण_अगर

	वापस 0;
पूर्ण


/*
 * Aureon boards करोn't provide the EEPROM data except क्रम the venकरोr IDs.
 * hence the driver needs to sets up it properly.
 */

अटल स्थिर अचिन्हित अक्षर aureon51_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x0a,	/* घड़ी 512, spdअगर-in/ADC, 3DACs */
	[ICE_EEP2_ACLINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0xfc,	/* vol, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-पूर्णांक, spdअगर-in */
	[ICE_EEP2_GPIO_सूची]    = 0xff,
	[ICE_EEP2_GPIO_सूची1]   = 0xff,
	[ICE_EEP2_GPIO_सूची2]   = 0x5f,
	[ICE_EEP2_GPIO_MASK]   = 0x00,
	[ICE_EEP2_GPIO_MASK1]  = 0x00,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,
	[ICE_EEP2_GPIO_STATE]  = 0x00,
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर aureon71_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x0b,	/* घड़ी 512, spdअगर-in/ADC, 4DACs */
	[ICE_EEP2_ACLINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0xfc,	/* vol, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-पूर्णांक, spdअगर-in */
	[ICE_EEP2_GPIO_सूची]    = 0xff,
	[ICE_EEP2_GPIO_सूची1]   = 0xff,
	[ICE_EEP2_GPIO_सूची2]   = 0x5f,
	[ICE_EEP2_GPIO_MASK]   = 0x00,
	[ICE_EEP2_GPIO_MASK1]  = 0x00,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,
	[ICE_EEP2_GPIO_STATE]  = 0x00,
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,
पूर्ण;
#घोषणा prodigy71_eeprom aureon71_eeprom

अटल स्थिर अचिन्हित अक्षर aureon71_universe_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x2b,	/* घड़ी 512, mpu401, spdअगर-in/ADC,
					 * 4DACs
					 */
	[ICE_EEP2_ACLINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0xfc,	/* vol, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-पूर्णांक, spdअगर-in */
	[ICE_EEP2_GPIO_सूची]    = 0xff,
	[ICE_EEP2_GPIO_सूची1]   = 0xff,
	[ICE_EEP2_GPIO_सूची2]   = 0x5f,
	[ICE_EEP2_GPIO_MASK]   = 0x00,
	[ICE_EEP2_GPIO_MASK1]  = 0x00,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,
	[ICE_EEP2_GPIO_STATE]  = 0x00,
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर prodigy71lt_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x4b,	/* घड़ी 384, spdअगर-in/ADC, 4DACs */
	[ICE_EEP2_ACLINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0xfc,	/* vol, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-पूर्णांक, spdअगर-in */
	[ICE_EEP2_GPIO_सूची]    = 0xff,
	[ICE_EEP2_GPIO_सूची1]   = 0xff,
	[ICE_EEP2_GPIO_सूची2]   = 0x5f,
	[ICE_EEP2_GPIO_MASK]   = 0x00,
	[ICE_EEP2_GPIO_MASK1]  = 0x00,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,
	[ICE_EEP2_GPIO_STATE]  = 0x00,
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,
पूर्ण;
#घोषणा prodigy71xt_eeprom prodigy71lt_eeprom

/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_vt1724_aureon_cards[] = अणु
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_AUREON51_SKY,
		.name = "Terratec Aureon 5.1-Sky",
		.model = "aureon51",
		.chip_init = aureon_init,
		.build_controls = aureon_add_controls,
		.eeprom_size = माप(aureon51_eeprom),
		.eeprom_data = aureon51_eeprom,
		.driver = "Aureon51",
	पूर्ण,
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_AUREON71_SPACE,
		.name = "Terratec Aureon 7.1-Space",
		.model = "aureon71",
		.chip_init = aureon_init,
		.build_controls = aureon_add_controls,
		.eeprom_size = माप(aureon71_eeprom),
		.eeprom_data = aureon71_eeprom,
		.driver = "Aureon71",
	पूर्ण,
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_AUREON71_UNIVERSE,
		.name = "Terratec Aureon 7.1-Universe",
		.model = "universe",
		.chip_init = aureon_init,
		.build_controls = aureon_add_controls,
		.eeprom_size = माप(aureon71_universe_eeprom),
		.eeprom_data = aureon71_universe_eeprom,
		.driver = "Aureon71Univ", /* keep in 15 letters */
	पूर्ण,
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_PRODIGY71,
		.name = "Audiotrak Prodigy 7.1",
		.model = "prodigy71",
		.chip_init = aureon_init,
		.build_controls = aureon_add_controls,
		.eeprom_size = माप(prodigy71_eeprom),
		.eeprom_data = prodigy71_eeprom,
		.driver = "Prodigy71", /* should be identical with Aureon71 */
	पूर्ण,
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_PRODIGY71LT,
		.name = "Audiotrak Prodigy 7.1 LT",
		.model = "prodigy71lt",
		.chip_init = aureon_init,
		.build_controls = aureon_add_controls,
		.eeprom_size = माप(prodigy71lt_eeprom),
		.eeprom_data = prodigy71lt_eeprom,
		.driver = "Prodigy71LT",
	पूर्ण,
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_PRODIGY71XT,
		.name = "Audiotrak Prodigy 7.1 XT",
		.model = "prodigy71xt",
		.chip_init = aureon_init,
		.build_controls = aureon_add_controls,
		.eeprom_size = माप(prodigy71xt_eeprom),
		.eeprom_data = prodigy71xt_eeprom,
		.driver = "Prodigy71LT",
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;
