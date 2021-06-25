<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PMac DACA lowlevel functions
 *
 * Copyright (c) by Takashi Iwai <tiwai@suse.de>
 */


#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश "pmac.h"

/* i2c address */
#घोषणा DACA_I2C_ADDR	0x4d

/* रेजिस्टरs */
#घोषणा DACA_REG_SR	0x01
#घोषणा DACA_REG_AVOL	0x02
#घोषणा DACA_REG_GCFG	0x03

/* maximum volume value */
#घोषणा DACA_VOL_MAX	0x38


काष्ठा pmac_daca अणु
	काष्ठा pmac_keywest i2c;
	पूर्णांक left_vol, right_vol;
	अचिन्हित पूर्णांक deemphasis : 1;
	अचिन्हित पूर्णांक amp_on : 1;
पूर्ण;


/*
 * initialize / detect DACA
 */
अटल पूर्णांक daca_init_client(काष्ठा pmac_keywest *i2c)
अणु
	अचिन्हित लघु wdata = 0x00;
	/* SR: no swap, 1bit delay, 32-48kHz */
	/* GCFG: घातer amp inverted, DAC on */
	अगर (i2c_smbus_ग_लिखो_byte_data(i2c->client, DACA_REG_SR, 0x08) < 0 ||
	    i2c_smbus_ग_लिखो_byte_data(i2c->client, DACA_REG_GCFG, 0x05) < 0)
		वापस -EINVAL;
	वापस i2c_smbus_ग_लिखो_block_data(i2c->client, DACA_REG_AVOL,
					  2, (अचिन्हित अक्षर*)&wdata);
पूर्ण

/*
 * update volume
 */
अटल पूर्णांक daca_set_volume(काष्ठा pmac_daca *mix)
अणु
	अचिन्हित अक्षर data[2];
  
	अगर (! mix->i2c.client)
		वापस -ENODEV;
  
	अगर (mix->left_vol > DACA_VOL_MAX)
		data[0] = DACA_VOL_MAX;
	अन्यथा
		data[0] = mix->left_vol;
	अगर (mix->right_vol > DACA_VOL_MAX)
		data[1] = DACA_VOL_MAX;
	अन्यथा
		data[1] = mix->right_vol;
	data[1] |= mix->deemphasis ? 0x40 : 0;
	अगर (i2c_smbus_ग_लिखो_block_data(mix->i2c.client, DACA_REG_AVOL,
				       2, data) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "failed to set volume \n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


/* deemphasis चयन */
#घोषणा daca_info_deemphasis		snd_ctl_boolean_mono_info

अटल पूर्णांक daca_get_deemphasis(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_daca *mix;
	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	ucontrol->value.पूर्णांकeger.value[0] = mix->deemphasis ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक daca_put_deemphasis(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_daca *mix;
	पूर्णांक change;

	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	change = mix->deemphasis != ucontrol->value.पूर्णांकeger.value[0];
	अगर (change) अणु
		mix->deemphasis = !!ucontrol->value.पूर्णांकeger.value[0];
		daca_set_volume(mix);
	पूर्ण
	वापस change;
पूर्ण

/* output volume */
अटल पूर्णांक daca_info_volume(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = DACA_VOL_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक daca_get_volume(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_daca *mix;
	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	ucontrol->value.पूर्णांकeger.value[0] = mix->left_vol;
	ucontrol->value.पूर्णांकeger.value[1] = mix->right_vol;
	वापस 0;
पूर्ण

अटल पूर्णांक daca_put_volume(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_daca *mix;
	अचिन्हित पूर्णांक vol[2];
	पूर्णांक change;

	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	vol[0] = ucontrol->value.पूर्णांकeger.value[0];
	vol[1] = ucontrol->value.पूर्णांकeger.value[1];
	अगर (vol[0] > DACA_VOL_MAX || vol[1] > DACA_VOL_MAX)
		वापस -EINVAL;
	change = mix->left_vol != vol[0] ||
		mix->right_vol != vol[1];
	अगर (change) अणु
		mix->left_vol = vol[0];
		mix->right_vol = vol[1];
		daca_set_volume(mix);
	पूर्ण
	वापस change;
पूर्ण

/* amplअगरier चयन */
#घोषणा daca_info_amp	daca_info_deemphasis

अटल पूर्णांक daca_get_amp(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_daca *mix;
	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	ucontrol->value.पूर्णांकeger.value[0] = mix->amp_on ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक daca_put_amp(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_daca *mix;
	पूर्णांक change;

	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	change = mix->amp_on != ucontrol->value.पूर्णांकeger.value[0];
	अगर (change) अणु
		mix->amp_on = !!ucontrol->value.पूर्णांकeger.value[0];
		i2c_smbus_ग_लिखो_byte_data(mix->i2c.client, DACA_REG_GCFG,
					  mix->amp_on ? 0x05 : 0x04);
	पूर्ण
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new daca_mixers[] = अणु
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Deemphasis Switch",
	  .info = daca_info_deemphasis,
	  .get = daca_get_deemphasis,
	  .put = daca_put_deemphasis
	पूर्ण,
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Master Playback Volume",
	  .info = daca_info_volume,
	  .get = daca_get_volume,
	  .put = daca_put_volume
	पूर्ण,
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Power Amplifier Switch",
	  .info = daca_info_amp,
	  .get = daca_get_amp,
	  .put = daca_put_amp
	पूर्ण,
पूर्ण;


#अगर_घोषित CONFIG_PM
अटल व्योम daca_resume(काष्ठा snd_pmac *chip)
अणु
	काष्ठा pmac_daca *mix = chip->mixer_data;
	i2c_smbus_ग_लिखो_byte_data(mix->i2c.client, DACA_REG_SR, 0x08);
	i2c_smbus_ग_लिखो_byte_data(mix->i2c.client, DACA_REG_GCFG,
				  mix->amp_on ? 0x05 : 0x04);
	daca_set_volume(mix);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */


अटल व्योम daca_cleanup(काष्ठा snd_pmac *chip)
अणु
	काष्ठा pmac_daca *mix = chip->mixer_data;
	अगर (! mix)
		वापस;
	snd_pmac_keywest_cleanup(&mix->i2c);
	kमुक्त(mix);
	chip->mixer_data = शून्य;
पूर्ण

/* exported */
पूर्णांक snd_pmac_daca_init(काष्ठा snd_pmac *chip)
अणु
	पूर्णांक i, err;
	काष्ठा pmac_daca *mix;

	request_module("i2c-powermac");

	mix = kzalloc(माप(*mix), GFP_KERNEL);
	अगर (! mix)
		वापस -ENOMEM;
	chip->mixer_data = mix;
	chip->mixer_मुक्त = daca_cleanup;
	mix->amp_on = 1; /* शेष on */

	mix->i2c.addr = DACA_I2C_ADDR;
	mix->i2c.init_client = daca_init_client;
	mix->i2c.name = "DACA";
	अगर ((err = snd_pmac_keywest_init(&mix->i2c)) < 0)
		वापस err;

	/*
	 * build mixers
	 */
	म_नकल(chip->card->mixername, "PowerMac DACA");

	क्रम (i = 0; i < ARRAY_SIZE(daca_mixers); i++) अणु
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&daca_mixers[i], chip))) < 0)
			वापस err;
	पूर्ण

#अगर_घोषित CONFIG_PM
	chip->resume = daca_resume;
#पूर्ण_अगर

	वापस 0;
पूर्ण
