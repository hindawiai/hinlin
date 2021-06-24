<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PMac Tumbler/Snapper lowlevel functions
 *
 * Copyright (c) by Takashi Iwai <tiwai@suse.de>
 *
 *   Rene Rebe <rene.rebe@gmx.net>:
 *     * update from shaकरोw रेजिस्टरs on wakeup and headphone plug
 *     * स्वतःmatically toggle DRC on headphone plug
 */


#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश "pmac.h"
#समावेश "tumbler_volume.h"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) prपूर्णांकk(KERN_DEBUG fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

#घोषणा IS_G4DA (of_machine_is_compatible("PowerMac3,4"))

/* i2c address क्रम tumbler */
#घोषणा TAS_I2C_ADDR	0x34

/* रेजिस्टरs */
#घोषणा TAS_REG_MCS	0x01	/* मुख्य control */
#घोषणा TAS_REG_DRC	0x02
#घोषणा TAS_REG_VOL	0x04
#घोषणा TAS_REG_TREBLE	0x05
#घोषणा TAS_REG_BASS	0x06
#घोषणा TAS_REG_INPUT1	0x07
#घोषणा TAS_REG_INPUT2	0x08

/* tas3001c */
#घोषणा TAS_REG_PCM	TAS_REG_INPUT1
 
/* tas3004 */
#घोषणा TAS_REG_LMIX	TAS_REG_INPUT1
#घोषणा TAS_REG_RMIX	TAS_REG_INPUT2
#घोषणा TAS_REG_MCS2	0x43		/* मुख्य control 2 */
#घोषणा TAS_REG_ACS	0x40		/* analog control */

/* mono volumes क्रम tas3001c/tas3004 */
क्रमागत अणु
	VOL_IDX_PCM_MONO, /* tas3001c only */
	VOL_IDX_BASS, VOL_IDX_TREBLE,
	VOL_IDX_LAST_MONO
पूर्ण;

/* stereo volumes क्रम tas3004 */
क्रमागत अणु
	VOL_IDX_PCM, VOL_IDX_PCM2, VOL_IDX_ADC,
	VOL_IDX_LAST_MIX
पूर्ण;

काष्ठा pmac_gpio अणु
	अचिन्हित पूर्णांक addr;
	u8 active_val;
	u8 inactive_val;
	u8 active_state;
पूर्ण;

काष्ठा pmac_tumbler अणु
	काष्ठा pmac_keywest i2c;
	काष्ठा pmac_gpio audio_reset;
	काष्ठा pmac_gpio amp_mute;
	काष्ठा pmac_gpio line_mute;
	काष्ठा pmac_gpio line_detect;
	काष्ठा pmac_gpio hp_mute;
	काष्ठा pmac_gpio hp_detect;
	पूर्णांक headphone_irq;
	पूर्णांक lineout_irq;
	अचिन्हित पूर्णांक save_master_vol[2];
	अचिन्हित पूर्णांक master_vol[2];
	अचिन्हित पूर्णांक save_master_चयन[2];
	अचिन्हित पूर्णांक master_चयन[2];
	अचिन्हित पूर्णांक mono_vol[VOL_IDX_LAST_MONO];
	अचिन्हित पूर्णांक mix_vol[VOL_IDX_LAST_MIX][2]; /* stereo volumes क्रम tas3004 */
	पूर्णांक drc_range;
	पूर्णांक drc_enable;
	पूर्णांक capture_source;
	पूर्णांक anded_reset;
	पूर्णांक स्वतः_mute_notअगरy;
	पूर्णांक reset_on_sleep;
	u8  acs;
पूर्ण;


/*
 */

अटल पूर्णांक send_init_client(काष्ठा pmac_keywest *i2c, स्थिर अचिन्हित पूर्णांक *regs)
अणु
	जबतक (*regs > 0) अणु
		पूर्णांक err, count = 10;
		करो अणु
			err = i2c_smbus_ग_लिखो_byte_data(i2c->client,
							regs[0], regs[1]);
			अगर (err >= 0)
				अवरोध;
			DBG("(W) i2c error %d\n", err);
			mdelay(10);
		पूर्ण जबतक (count--);
		अगर (err < 0)
			वापस -ENXIO;
		regs += 2;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक tumbler_init_client(काष्ठा pmac_keywest *i2c)
अणु
	अटल स्थिर अचिन्हित पूर्णांक regs[] = अणु
		/* normal operation, SCLK=64fps, i2s output, i2s input, 16bit width */
		TAS_REG_MCS, (1<<6)|(2<<4)|(2<<2)|0,
		0, /* terminator */
	पूर्ण;
	DBG("(I) tumbler init client\n");
	वापस send_init_client(i2c, regs);
पूर्ण

अटल पूर्णांक snapper_init_client(काष्ठा pmac_keywest *i2c)
अणु
	अटल स्थिर अचिन्हित पूर्णांक regs[] = अणु
		/* normal operation, SCLK=64fps, i2s output, 16bit width */
		TAS_REG_MCS, (1<<6)|(2<<4)|0,
		/* normal operation, all-pass mode */
		TAS_REG_MCS2, (1<<1),
		/* normal output, no deemphasis, A input, घातer-up, line-in */
		TAS_REG_ACS, 0,
		0, /* terminator */
	पूर्ण;
	DBG("(I) snapper init client\n");
	वापस send_init_client(i2c, regs);
पूर्ण
	
/*
 * gpio access
 */
#घोषणा करो_gpio_ग_लिखो(gp, val) \
	pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य, (gp)->addr, val)
#घोषणा करो_gpio_पढ़ो(gp) \
	pmac_call_feature(PMAC_FTR_READ_GPIO, शून्य, (gp)->addr, 0)
#घोषणा tumbler_gpio_मुक्त(gp) /* NOP */

अटल व्योम ग_लिखो_audio_gpio(काष्ठा pmac_gpio *gp, पूर्णांक active)
अणु
	अगर (! gp->addr)
		वापस;
	active = active ? gp->active_val : gp->inactive_val;
	करो_gpio_ग_लिखो(gp, active);
	DBG("(I) gpio %x write %d\n", gp->addr, active);
पूर्ण

अटल पूर्णांक check_audio_gpio(काष्ठा pmac_gpio *gp)
अणु
	पूर्णांक ret;

	अगर (! gp->addr)
		वापस 0;

	ret = करो_gpio_पढ़ो(gp);

	वापस (ret & 0x1) == (gp->active_val & 0x1);
पूर्ण

अटल पूर्णांक पढ़ो_audio_gpio(काष्ठा pmac_gpio *gp)
अणु
	पूर्णांक ret;
	अगर (! gp->addr)
		वापस 0;
	ret = करो_gpio_पढ़ो(gp);
	ret = (ret & 0x02) !=0;
	वापस ret == gp->active_state;
पूर्ण

/*
 * update master volume
 */
अटल पूर्णांक tumbler_set_master_volume(काष्ठा pmac_tumbler *mix)
अणु
	अचिन्हित अक्षर block[6];
	अचिन्हित पूर्णांक left_vol, right_vol;
  
	अगर (! mix->i2c.client)
		वापस -ENODEV;
  
	अगर (! mix->master_चयन[0])
		left_vol = 0;
	अन्यथा अणु
		left_vol = mix->master_vol[0];
		अगर (left_vol >= ARRAY_SIZE(master_volume_table))
			left_vol = ARRAY_SIZE(master_volume_table) - 1;
		left_vol = master_volume_table[left_vol];
	पूर्ण
	अगर (! mix->master_चयन[1])
		right_vol = 0;
	अन्यथा अणु
		right_vol = mix->master_vol[1];
		अगर (right_vol >= ARRAY_SIZE(master_volume_table))
			right_vol = ARRAY_SIZE(master_volume_table) - 1;
		right_vol = master_volume_table[right_vol];
	पूर्ण

	block[0] = (left_vol >> 16) & 0xff;
	block[1] = (left_vol >> 8)  & 0xff;
	block[2] = (left_vol >> 0)  & 0xff;

	block[3] = (right_vol >> 16) & 0xff;
	block[4] = (right_vol >> 8)  & 0xff;
	block[5] = (right_vol >> 0)  & 0xff;
  
	अगर (i2c_smbus_ग_लिखो_i2c_block_data(mix->i2c.client, TAS_REG_VOL, 6,
					   block) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "failed to set volume \n");
		वापस -EINVAL;
	पूर्ण
	DBG("(I) succeeded to set volume (%u, %u)\n", left_vol, right_vol);
	वापस 0;
पूर्ण


/* output volume */
अटल पूर्णांक tumbler_info_master_volume(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = ARRAY_SIZE(master_volume_table) - 1;
	वापस 0;
पूर्ण

अटल पूर्णांक tumbler_get_master_volume(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix = chip->mixer_data;

	ucontrol->value.पूर्णांकeger.value[0] = mix->master_vol[0];
	ucontrol->value.पूर्णांकeger.value[1] = mix->master_vol[1];
	वापस 0;
पूर्ण

अटल पूर्णांक tumbler_put_master_volume(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix = chip->mixer_data;
	अचिन्हित पूर्णांक vol[2];
	पूर्णांक change;

	vol[0] = ucontrol->value.पूर्णांकeger.value[0];
	vol[1] = ucontrol->value.पूर्णांकeger.value[1];
	अगर (vol[0] >= ARRAY_SIZE(master_volume_table) ||
	    vol[1] >= ARRAY_SIZE(master_volume_table))
		वापस -EINVAL;
	change = mix->master_vol[0] != vol[0] ||
		mix->master_vol[1] != vol[1];
	अगर (change) अणु
		mix->master_vol[0] = vol[0];
		mix->master_vol[1] = vol[1];
		tumbler_set_master_volume(mix);
	पूर्ण
	वापस change;
पूर्ण

/* output चयन */
अटल पूर्णांक tumbler_get_master_चयन(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix = chip->mixer_data;

	ucontrol->value.पूर्णांकeger.value[0] = mix->master_चयन[0];
	ucontrol->value.पूर्णांकeger.value[1] = mix->master_चयन[1];
	वापस 0;
पूर्ण

अटल पूर्णांक tumbler_put_master_चयन(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix = chip->mixer_data;
	पूर्णांक change;

	change = mix->master_चयन[0] != ucontrol->value.पूर्णांकeger.value[0] ||
		mix->master_चयन[1] != ucontrol->value.पूर्णांकeger.value[1];
	अगर (change) अणु
		mix->master_चयन[0] = !!ucontrol->value.पूर्णांकeger.value[0];
		mix->master_चयन[1] = !!ucontrol->value.पूर्णांकeger.value[1];
		tumbler_set_master_volume(mix);
	पूर्ण
	वापस change;
पूर्ण


/*
 * TAS3001c dynamic range compression
 */

#घोषणा TAS3001_DRC_MAX		0x5f

अटल पूर्णांक tumbler_set_drc(काष्ठा pmac_tumbler *mix)
अणु
	अचिन्हित अक्षर val[2];

	अगर (! mix->i2c.client)
		वापस -ENODEV;
  
	अगर (mix->drc_enable) अणु
		val[0] = 0xc1; /* enable, 3:1 compression */
		अगर (mix->drc_range > TAS3001_DRC_MAX)
			val[1] = 0xf0;
		अन्यथा अगर (mix->drc_range < 0)
			val[1] = 0x91;
		अन्यथा
			val[1] = mix->drc_range + 0x91;
	पूर्ण अन्यथा अणु
		val[0] = 0;
		val[1] = 0;
	पूर्ण

	अगर (i2c_smbus_ग_लिखो_i2c_block_data(mix->i2c.client, TAS_REG_DRC,
					   2, val) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "failed to set DRC\n");
		वापस -EINVAL;
	पूर्ण
	DBG("(I) succeeded to set DRC (%u, %u)\n", val[0], val[1]);
	वापस 0;
पूर्ण

/*
 * TAS3004
 */

#घोषणा TAS3004_DRC_MAX		0xef

अटल पूर्णांक snapper_set_drc(काष्ठा pmac_tumbler *mix)
अणु
	अचिन्हित अक्षर val[6];

	अगर (! mix->i2c.client)
		वापस -ENODEV;
  
	अगर (mix->drc_enable)
		val[0] = 0x50; /* 3:1 above threshold */
	अन्यथा
		val[0] = 0x51; /* disabled */
	val[1] = 0x02; /* 1:1 below threshold */
	अगर (mix->drc_range > 0xef)
		val[2] = 0xef;
	अन्यथा अगर (mix->drc_range < 0)
		val[2] = 0x00;
	अन्यथा
		val[2] = mix->drc_range;
	val[3] = 0xb0;
	val[4] = 0x60;
	val[5] = 0xa0;

	अगर (i2c_smbus_ग_लिखो_i2c_block_data(mix->i2c.client, TAS_REG_DRC,
					   6, val) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "failed to set DRC\n");
		वापस -EINVAL;
	पूर्ण
	DBG("(I) succeeded to set DRC (%u, %u)\n", val[0], val[1]);
	वापस 0;
पूर्ण

अटल पूर्णांक tumbler_info_drc_value(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max =
		chip->model == PMAC_TUMBLER ? TAS3001_DRC_MAX : TAS3004_DRC_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक tumbler_get_drc_value(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix;
	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	ucontrol->value.पूर्णांकeger.value[0] = mix->drc_range;
	वापस 0;
पूर्ण

अटल पूर्णांक tumbler_put_drc_value(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix;
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (chip->model == PMAC_TUMBLER) अणु
		अगर (val > TAS3001_DRC_MAX)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (val > TAS3004_DRC_MAX)
			वापस -EINVAL;
	पूर्ण
	change = mix->drc_range != val;
	अगर (change) अणु
		mix->drc_range = val;
		अगर (chip->model == PMAC_TUMBLER)
			tumbler_set_drc(mix);
		अन्यथा
			snapper_set_drc(mix);
	पूर्ण
	वापस change;
पूर्ण

अटल पूर्णांक tumbler_get_drc_चयन(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix;
	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	ucontrol->value.पूर्णांकeger.value[0] = mix->drc_enable;
	वापस 0;
पूर्ण

अटल पूर्णांक tumbler_put_drc_चयन(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix;
	पूर्णांक change;

	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	change = mix->drc_enable != ucontrol->value.पूर्णांकeger.value[0];
	अगर (change) अणु
		mix->drc_enable = !!ucontrol->value.पूर्णांकeger.value[0];
		अगर (chip->model == PMAC_TUMBLER)
			tumbler_set_drc(mix);
		अन्यथा
			snapper_set_drc(mix);
	पूर्ण
	वापस change;
पूर्ण


/*
 * mono volumes
 */

काष्ठा tumbler_mono_vol अणु
	पूर्णांक index;
	पूर्णांक reg;
	पूर्णांक bytes;
	अचिन्हित पूर्णांक max;
	स्थिर अचिन्हित पूर्णांक *table;
पूर्ण;

अटल पूर्णांक tumbler_set_mono_volume(काष्ठा pmac_tumbler *mix,
				   स्थिर काष्ठा tumbler_mono_vol *info)
अणु
	अचिन्हित अक्षर block[4];
	अचिन्हित पूर्णांक vol;
	पूर्णांक i;
  
	अगर (! mix->i2c.client)
		वापस -ENODEV;
  
	vol = mix->mono_vol[info->index];
	अगर (vol >= info->max)
		vol = info->max - 1;
	vol = info->table[vol];
	क्रम (i = 0; i < info->bytes; i++)
		block[i] = (vol >> ((info->bytes - i - 1) * 8)) & 0xff;
	अगर (i2c_smbus_ग_लिखो_i2c_block_data(mix->i2c.client, info->reg,
					   info->bytes, block) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "failed to set mono volume %d\n",
			   info->index);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tumbler_info_mono(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा tumbler_mono_vol *info = (काष्ठा tumbler_mono_vol *)kcontrol->निजी_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = info->max - 1;
	वापस 0;
पूर्ण

अटल पूर्णांक tumbler_get_mono(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tumbler_mono_vol *info = (काष्ठा tumbler_mono_vol *)kcontrol->निजी_value;
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix;
	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	ucontrol->value.पूर्णांकeger.value[0] = mix->mono_vol[info->index];
	वापस 0;
पूर्ण

अटल पूर्णांक tumbler_put_mono(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tumbler_mono_vol *info = (काष्ठा tumbler_mono_vol *)kcontrol->निजी_value;
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix;
	अचिन्हित पूर्णांक vol;
	पूर्णांक change;

	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	vol = ucontrol->value.पूर्णांकeger.value[0];
	अगर (vol >= info->max)
		वापस -EINVAL;
	change = mix->mono_vol[info->index] != vol;
	अगर (change) अणु
		mix->mono_vol[info->index] = vol;
		tumbler_set_mono_volume(mix, info);
	पूर्ण
	वापस change;
पूर्ण

/* TAS3001c mono volumes */
अटल स्थिर काष्ठा tumbler_mono_vol tumbler_pcm_vol_info = अणु
	.index = VOL_IDX_PCM_MONO,
	.reg = TAS_REG_PCM,
	.bytes = 3,
	.max = ARRAY_SIZE(mixer_volume_table),
	.table = mixer_volume_table,
पूर्ण;

अटल स्थिर काष्ठा tumbler_mono_vol tumbler_bass_vol_info = अणु
	.index = VOL_IDX_BASS,
	.reg = TAS_REG_BASS,
	.bytes = 1,
	.max = ARRAY_SIZE(bass_volume_table),
	.table = bass_volume_table,
पूर्ण;

अटल स्थिर काष्ठा tumbler_mono_vol tumbler_treble_vol_info = अणु
	.index = VOL_IDX_TREBLE,
	.reg = TAS_REG_TREBLE,
	.bytes = 1,
	.max = ARRAY_SIZE(treble_volume_table),
	.table = treble_volume_table,
पूर्ण;

/* TAS3004 mono volumes */
अटल स्थिर काष्ठा tumbler_mono_vol snapper_bass_vol_info = अणु
	.index = VOL_IDX_BASS,
	.reg = TAS_REG_BASS,
	.bytes = 1,
	.max = ARRAY_SIZE(snapper_bass_volume_table),
	.table = snapper_bass_volume_table,
पूर्ण;

अटल स्थिर काष्ठा tumbler_mono_vol snapper_treble_vol_info = अणु
	.index = VOL_IDX_TREBLE,
	.reg = TAS_REG_TREBLE,
	.bytes = 1,
	.max = ARRAY_SIZE(snapper_treble_volume_table),
	.table = snapper_treble_volume_table,
पूर्ण;


#घोषणा DEFINE_MONO(xname,type) अणु \
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,\
	.name = xname, \
	.info = tumbler_info_mono, \
	.get = tumbler_get_mono, \
	.put = tumbler_put_mono, \
	.निजी_value = (अचिन्हित दीर्घ)(&tumbler_##type##_vol_info), \
पूर्ण

#घोषणा DEFINE_SNAPPER_MONO(xname,type) अणु \
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,\
	.name = xname, \
	.info = tumbler_info_mono, \
	.get = tumbler_get_mono, \
	.put = tumbler_put_mono, \
	.निजी_value = (अचिन्हित दीर्घ)(&snapper_##type##_vol_info), \
पूर्ण


/*
 * snapper mixer volumes
 */

अटल पूर्णांक snapper_set_mix_vol1(काष्ठा pmac_tumbler *mix, पूर्णांक idx, पूर्णांक ch, पूर्णांक reg)
अणु
	पूर्णांक i, j, vol;
	अचिन्हित अक्षर block[9];

	vol = mix->mix_vol[idx][ch];
	अगर (vol >= ARRAY_SIZE(mixer_volume_table)) अणु
		vol = ARRAY_SIZE(mixer_volume_table) - 1;
		mix->mix_vol[idx][ch] = vol;
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		vol = mix->mix_vol[i][ch];
		vol = mixer_volume_table[vol];
		क्रम (j = 0; j < 3; j++)
			block[i * 3 + j] = (vol >> ((2 - j) * 8)) & 0xff;
	पूर्ण
	अगर (i2c_smbus_ग_लिखो_i2c_block_data(mix->i2c.client, reg,
					   9, block) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "failed to set mono volume %d\n", reg);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snapper_set_mix_vol(काष्ठा pmac_tumbler *mix, पूर्णांक idx)
अणु
	अगर (! mix->i2c.client)
		वापस -ENODEV;
	अगर (snapper_set_mix_vol1(mix, idx, 0, TAS_REG_LMIX) < 0 ||
	    snapper_set_mix_vol1(mix, idx, 1, TAS_REG_RMIX) < 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक snapper_info_mix(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = ARRAY_SIZE(mixer_volume_table) - 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snapper_get_mix(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक idx = (पूर्णांक)kcontrol->निजी_value;
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix;
	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	ucontrol->value.पूर्णांकeger.value[0] = mix->mix_vol[idx][0];
	ucontrol->value.पूर्णांकeger.value[1] = mix->mix_vol[idx][1];
	वापस 0;
पूर्ण

अटल पूर्णांक snapper_put_mix(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक idx = (पूर्णांक)kcontrol->निजी_value;
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix;
	अचिन्हित पूर्णांक vol[2];
	पूर्णांक change;

	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	vol[0] = ucontrol->value.पूर्णांकeger.value[0];
	vol[1] = ucontrol->value.पूर्णांकeger.value[1];
	अगर (vol[0] >= ARRAY_SIZE(mixer_volume_table) ||
	    vol[1] >= ARRAY_SIZE(mixer_volume_table))
		वापस -EINVAL;
	change = mix->mix_vol[idx][0] != vol[0] ||
		mix->mix_vol[idx][1] != vol[1];
	अगर (change) अणु
		mix->mix_vol[idx][0] = vol[0];
		mix->mix_vol[idx][1] = vol[1];
		snapper_set_mix_vol(mix, idx);
	पूर्ण
	वापस change;
पूर्ण


/*
 * mute चयनes. FIXME: Turn that पूर्णांकo software mute when both outमाला_दो are muted
 * to aव्योम codec reset on ibook M7
 */

क्रमागत अणु TUMBLER_MUTE_HP, TUMBLER_MUTE_AMP, TUMBLER_MUTE_LINE पूर्ण;

अटल पूर्णांक tumbler_get_mute_चयन(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix;
	काष्ठा pmac_gpio *gp;
	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	चयन(kcontrol->निजी_value) अणु
	हाल TUMBLER_MUTE_HP:
		gp = &mix->hp_mute;	अवरोध;
	हाल TUMBLER_MUTE_AMP:
		gp = &mix->amp_mute;	अवरोध;
	हाल TUMBLER_MUTE_LINE:
		gp = &mix->line_mute;	अवरोध;
	शेष:
		gp = शून्य;
	पूर्ण
	अगर (gp == शून्य)
		वापस -EINVAL;
	ucontrol->value.पूर्णांकeger.value[0] = !check_audio_gpio(gp);
	वापस 0;
पूर्ण

अटल पूर्णांक tumbler_put_mute_चयन(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix;
	काष्ठा pmac_gpio *gp;
	पूर्णांक val;
#अगर_घोषित PMAC_SUPPORT_AUTOMUTE
	अगर (chip->update_स्वतःmute && chip->स्वतः_mute)
		वापस 0; /* करोn't touch in the स्वतः-mute mode */
#पूर्ण_अगर	
	अगर (! (mix = chip->mixer_data))
		वापस -ENODEV;
	चयन(kcontrol->निजी_value) अणु
	हाल TUMBLER_MUTE_HP:
		gp = &mix->hp_mute;	अवरोध;
	हाल TUMBLER_MUTE_AMP:
		gp = &mix->amp_mute;	अवरोध;
	हाल TUMBLER_MUTE_LINE:
		gp = &mix->line_mute;	अवरोध;
	शेष:
		gp = शून्य;
	पूर्ण
	अगर (gp == शून्य)
		वापस -EINVAL;
	val = ! check_audio_gpio(gp);
	अगर (val != ucontrol->value.पूर्णांकeger.value[0]) अणु
		ग_लिखो_audio_gpio(gp, ! ucontrol->value.पूर्णांकeger.value[0]);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snapper_set_capture_source(काष्ठा pmac_tumbler *mix)
अणु
	अगर (! mix->i2c.client)
		वापस -ENODEV;
	अगर (mix->capture_source)
		mix->acs |= 2;
	अन्यथा
		mix->acs &= ~2;
	वापस i2c_smbus_ग_लिखो_byte_data(mix->i2c.client, TAS_REG_ACS, mix->acs);
पूर्ण

अटल पूर्णांक snapper_info_capture_source(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु
		"Line", "Mic"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snapper_get_capture_source(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix = chip->mixer_data;

	ucontrol->value.क्रमागतerated.item[0] = mix->capture_source;
	वापस 0;
पूर्ण

अटल पूर्णांक snapper_put_capture_source(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा pmac_tumbler *mix = chip->mixer_data;
	पूर्णांक change;

	change = ucontrol->value.क्रमागतerated.item[0] != mix->capture_source;
	अगर (change) अणु
		mix->capture_source = !!ucontrol->value.क्रमागतerated.item[0];
		snapper_set_capture_source(mix);
	पूर्ण
	वापस change;
पूर्ण

#घोषणा DEFINE_SNAPPER_MIX(xname,idx,ofs) अणु \
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,\
	.name = xname, \
	.info = snapper_info_mix, \
	.get = snapper_get_mix, \
	.put = snapper_put_mix, \
	.index = idx,\
	.निजी_value = ofs, \
पूर्ण


/*
 */
अटल स्थिर काष्ठा snd_kcontrol_new tumbler_mixers[] = अणु
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Master Playback Volume",
	  .info = tumbler_info_master_volume,
	  .get = tumbler_get_master_volume,
	  .put = tumbler_put_master_volume
	पूर्ण,
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Master Playback Switch",
	  .info = snd_pmac_boolean_stereo_info,
	  .get = tumbler_get_master_चयन,
	  .put = tumbler_put_master_चयन
	पूर्ण,
	DEFINE_MONO("Tone Control - Bass", bass),
	DEFINE_MONO("Tone Control - Treble", treble),
	DEFINE_MONO("PCM Playback Volume", pcm),
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "DRC Range",
	  .info = tumbler_info_drc_value,
	  .get = tumbler_get_drc_value,
	  .put = tumbler_put_drc_value
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snapper_mixers[] = अणु
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Master Playback Volume",
	  .info = tumbler_info_master_volume,
	  .get = tumbler_get_master_volume,
	  .put = tumbler_put_master_volume
	पूर्ण,
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Master Playback Switch",
	  .info = snd_pmac_boolean_stereo_info,
	  .get = tumbler_get_master_चयन,
	  .put = tumbler_put_master_चयन
	पूर्ण,
	DEFINE_SNAPPER_MIX("PCM Playback Volume", 0, VOL_IDX_PCM),
	/* Alternative PCM is asचिन्हित to Mic analog loopback on iBook G4 */
	DEFINE_SNAPPER_MIX("Mic Playback Volume", 0, VOL_IDX_PCM2),
	DEFINE_SNAPPER_MIX("Monitor Mix Volume", 0, VOL_IDX_ADC),
	DEFINE_SNAPPER_MONO("Tone Control - Bass", bass),
	DEFINE_SNAPPER_MONO("Tone Control - Treble", treble),
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "DRC Range",
	  .info = tumbler_info_drc_value,
	  .get = tumbler_get_drc_value,
	  .put = tumbler_put_drc_value
	पूर्ण,
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Input Source", /* FIXME: "Capture Source" करोesn't work properly */
	  .info = snapper_info_capture_source,
	  .get = snapper_get_capture_source,
	  .put = snapper_put_capture_source
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tumbler_hp_sw = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Headphone Playback Switch",
	.info = snd_pmac_boolean_mono_info,
	.get = tumbler_get_mute_चयन,
	.put = tumbler_put_mute_चयन,
	.निजी_value = TUMBLER_MUTE_HP,
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new tumbler_speaker_sw = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Speaker Playback Switch",
	.info = snd_pmac_boolean_mono_info,
	.get = tumbler_get_mute_चयन,
	.put = tumbler_put_mute_चयन,
	.निजी_value = TUMBLER_MUTE_AMP,
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new tumbler_lineout_sw = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Line Out Playback Switch",
	.info = snd_pmac_boolean_mono_info,
	.get = tumbler_get_mute_चयन,
	.put = tumbler_put_mute_चयन,
	.निजी_value = TUMBLER_MUTE_LINE,
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new tumbler_drc_sw = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "DRC Switch",
	.info = snd_pmac_boolean_mono_info,
	.get = tumbler_get_drc_चयन,
	.put = tumbler_put_drc_चयन
पूर्ण;


#अगर_घोषित PMAC_SUPPORT_AUTOMUTE
/*
 * स्वतः-mute stuffs
 */
अटल पूर्णांक tumbler_detect_headphone(काष्ठा snd_pmac *chip)
अणु
	काष्ठा pmac_tumbler *mix = chip->mixer_data;
	पूर्णांक detect = 0;

	अगर (mix->hp_detect.addr)
		detect |= पढ़ो_audio_gpio(&mix->hp_detect);
	वापस detect;
पूर्ण

अटल पूर्णांक tumbler_detect_lineout(काष्ठा snd_pmac *chip)
अणु
	काष्ठा pmac_tumbler *mix = chip->mixer_data;
	पूर्णांक detect = 0;

	अगर (mix->line_detect.addr)
		detect |= पढ़ो_audio_gpio(&mix->line_detect);
	वापस detect;
पूर्ण

अटल व्योम check_mute(काष्ठा snd_pmac *chip, काष्ठा pmac_gpio *gp, पूर्णांक val, पूर्णांक करो_notअगरy,
		       काष्ठा snd_kcontrol *sw)
अणु
	अगर (check_audio_gpio(gp) != val) अणु
		ग_लिखो_audio_gpio(gp, val);
		अगर (करो_notअगरy)
			snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &sw->id);
	पूर्ण
पूर्ण

अटल काष्ठा work_काष्ठा device_change;
अटल काष्ठा snd_pmac *device_change_chip;

अटल व्योम device_change_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_pmac *chip = device_change_chip;
	काष्ठा pmac_tumbler *mix;
	पूर्णांक headphone, lineout;

	अगर (!chip)
		वापस;

	mix = chip->mixer_data;
	अगर (snd_BUG_ON(!mix))
		वापस;

	headphone = tumbler_detect_headphone(chip);
	lineout = tumbler_detect_lineout(chip);

	DBG("headphone: %d, lineout: %d\n", headphone, lineout);

	अगर (headphone || lineout) अणु
		/* unmute headphone/lineout & mute speaker */
		अगर (headphone)
			check_mute(chip, &mix->hp_mute, 0, mix->स्वतः_mute_notअगरy,
				   chip->master_sw_ctl);
		अगर (lineout && mix->line_mute.addr != 0)
			check_mute(chip, &mix->line_mute, 0, mix->स्वतः_mute_notअगरy,
				   chip->lineout_sw_ctl);
		अगर (mix->anded_reset)
			msleep(10);
		check_mute(chip, &mix->amp_mute, !IS_G4DA, mix->स्वतः_mute_notअगरy,
			   chip->speaker_sw_ctl);
	पूर्ण अन्यथा अणु
		/* unmute speaker, mute others */
		check_mute(chip, &mix->amp_mute, 0, mix->स्वतः_mute_notअगरy,
			   chip->speaker_sw_ctl);
		अगर (mix->anded_reset)
			msleep(10);
		check_mute(chip, &mix->hp_mute, 1, mix->स्वतः_mute_notअगरy,
			   chip->master_sw_ctl);
		अगर (mix->line_mute.addr != 0)
			check_mute(chip, &mix->line_mute, 1, mix->स्वतः_mute_notअगरy,
				   chip->lineout_sw_ctl);
	पूर्ण
	अगर (mix->स्वतः_mute_notअगरy)
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->hp_detect_ctl->id);

#अगर_घोषित CONFIG_SND_POWERMAC_AUTO_DRC
	mix->drc_enable = ! (headphone || lineout);
	अगर (mix->स्वतः_mute_notअगरy)
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->drc_sw_ctl->id);
	अगर (chip->model == PMAC_TUMBLER)
		tumbler_set_drc(mix);
	अन्यथा
		snapper_set_drc(mix);
#पूर्ण_अगर

	/* reset the master volume so the correct amplअगरication is applied */
	tumbler_set_master_volume(mix);
पूर्ण

अटल व्योम tumbler_update_स्वतःmute(काष्ठा snd_pmac *chip, पूर्णांक करो_notअगरy)
अणु
	अगर (chip->स्वतः_mute) अणु
		काष्ठा pmac_tumbler *mix;
		mix = chip->mixer_data;
		अगर (snd_BUG_ON(!mix))
			वापस;
		mix->स्वतः_mute_notअगरy = करो_notअगरy;
		schedule_work(&device_change);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* PMAC_SUPPORT_AUTOMUTE */


/* पूर्णांकerrupt - headphone plug changed */
अटल irqवापस_t headphone_पूर्णांकr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा snd_pmac *chip = devid;
	अगर (chip->update_स्वतःmute && chip->initialized) अणु
		chip->update_स्वतःmute(chip, 1);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

/* look क्रम audio-gpio device */
अटल काष्ठा device_node *find_audio_device(स्थिर अक्षर *name)
अणु
	काष्ठा device_node *gpiop;
	काष्ठा device_node *np;
  
	gpiop = of_find_node_by_name(शून्य, "gpio");
	अगर (! gpiop)
		वापस शून्य;
  
	क्रम (np = of_get_next_child(gpiop, शून्य); np;
			np = of_get_next_child(gpiop, np)) अणु
		स्थिर अक्षर *property = of_get_property(np, "audio-gpio", शून्य);
		अगर (property && म_भेद(property, name) == 0)
			अवरोध;
	पूर्ण  
	of_node_put(gpiop);
	वापस np;
पूर्ण

/* look क्रम audio-gpio device */
अटल काष्ठा device_node *find_compatible_audio_device(स्थिर अक्षर *name)
अणु
	काष्ठा device_node *gpiop;
	काष्ठा device_node *np;
  
	gpiop = of_find_node_by_name(शून्य, "gpio");
	अगर (!gpiop)
		वापस शून्य;
  
	क्रम (np = of_get_next_child(gpiop, शून्य); np;
			np = of_get_next_child(gpiop, np)) अणु
		अगर (of_device_is_compatible(np, name))
			अवरोध;
	पूर्ण  
	of_node_put(gpiop);
	वापस np;
पूर्ण

/* find an audio device and get its address */
अटल दीर्घ tumbler_find_device(स्थिर अक्षर *device, स्थिर अक्षर *platक्रमm,
				काष्ठा pmac_gpio *gp, पूर्णांक is_compatible)
अणु
	काष्ठा device_node *node;
	स्थिर u32 *base;
	u32 addr;
	दीर्घ ret;

	अगर (is_compatible)
		node = find_compatible_audio_device(device);
	अन्यथा
		node = find_audio_device(device);
	अगर (! node) अणु
		DBG("(W) cannot find audio device %s !\n", device);
		snd_prपूर्णांकdd("cannot find device %s\n", device);
		वापस -ENODEV;
	पूर्ण

	base = of_get_property(node, "AAPL,address", शून्य);
	अगर (! base) अणु
		base = of_get_property(node, "reg", शून्य);
		अगर (!base) अणु
			DBG("(E) cannot find address for device %s !\n", device);
			snd_prपूर्णांकd("cannot find address for device %s\n", device);
			of_node_put(node);
			वापस -ENODEV;
		पूर्ण
		addr = *base;
		अगर (addr < 0x50)
			addr += 0x50;
	पूर्ण अन्यथा
		addr = *base;

	gp->addr = addr & 0x0000ffff;
	/* Try to find the active state, शेष to 0 ! */
	base = of_get_property(node, "audio-gpio-active-state", शून्य);
	अगर (base) अणु
		gp->active_state = *base;
		gp->active_val = (*base) ? 0x5 : 0x4;
		gp->inactive_val = (*base) ? 0x4 : 0x5;
	पूर्ण अन्यथा अणु
		स्थिर u32 *prop = शून्य;
		gp->active_state = IS_G4DA
				&& !म_भेदन(device, "keywest-gpio1", 13);
		gp->active_val = 0x4;
		gp->inactive_val = 0x5;
		/* Here are some crude hacks to extract the GPIO polarity and
		 * खोलो collector inक्रमmations out of the करो-platक्रमm script
		 * as we करोn't yet have an पूर्णांकerpreter क्रम these things
		 */
		अगर (platक्रमm)
			prop = of_get_property(node, platक्रमm, शून्य);
		अगर (prop) अणु
			अगर (prop[3] == 0x9 && prop[4] == 0x9) अणु
				gp->active_val = 0xd;
				gp->inactive_val = 0xc;
			पूर्ण
			अगर (prop[3] == 0x1 && prop[4] == 0x1) अणु
				gp->active_val = 0x5;
				gp->inactive_val = 0x4;
			पूर्ण
		पूर्ण
	पूर्ण

	DBG("(I) GPIO device %s found, offset: %x, active state: %d !\n",
	    device, gp->addr, gp->active_state);

	ret = irq_of_parse_and_map(node, 0);
	of_node_put(node);
	वापस ret;
पूर्ण

/* reset audio */
अटल व्योम tumbler_reset_audio(काष्ठा snd_pmac *chip)
अणु
	काष्ठा pmac_tumbler *mix = chip->mixer_data;

	अगर (mix->anded_reset) अणु
		DBG("(I) codec anded reset !\n");
		ग_लिखो_audio_gpio(&mix->hp_mute, 0);
		ग_लिखो_audio_gpio(&mix->amp_mute, 0);
		msleep(200);
		ग_लिखो_audio_gpio(&mix->hp_mute, 1);
		ग_लिखो_audio_gpio(&mix->amp_mute, 1);
		msleep(100);
		ग_लिखो_audio_gpio(&mix->hp_mute, 0);
		ग_लिखो_audio_gpio(&mix->amp_mute, 0);
		msleep(100);
	पूर्ण अन्यथा अणु
		DBG("(I) codec normal reset !\n");

		ग_लिखो_audio_gpio(&mix->audio_reset, 0);
		msleep(200);
		ग_लिखो_audio_gpio(&mix->audio_reset, 1);
		msleep(100);
		ग_लिखो_audio_gpio(&mix->audio_reset, 0);
		msleep(100);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
/* suspend mixer */
अटल व्योम tumbler_suspend(काष्ठा snd_pmac *chip)
अणु
	काष्ठा pmac_tumbler *mix = chip->mixer_data;

	अगर (mix->headphone_irq >= 0)
		disable_irq(mix->headphone_irq);
	अगर (mix->lineout_irq >= 0)
		disable_irq(mix->lineout_irq);
	mix->save_master_चयन[0] = mix->master_चयन[0];
	mix->save_master_चयन[1] = mix->master_चयन[1];
	mix->save_master_vol[0] = mix->master_vol[0];
	mix->save_master_vol[1] = mix->master_vol[1];
	mix->master_चयन[0] = mix->master_चयन[1] = 0;
	tumbler_set_master_volume(mix);
	अगर (!mix->anded_reset) अणु
		ग_लिखो_audio_gpio(&mix->amp_mute, 1);
		ग_लिखो_audio_gpio(&mix->hp_mute, 1);
	पूर्ण
	अगर (chip->model == PMAC_SNAPPER) अणु
		mix->acs |= 1;
		i2c_smbus_ग_लिखो_byte_data(mix->i2c.client, TAS_REG_ACS, mix->acs);
	पूर्ण
	अगर (mix->anded_reset) अणु
		ग_लिखो_audio_gpio(&mix->amp_mute, 1);
		ग_लिखो_audio_gpio(&mix->hp_mute, 1);
	पूर्ण अन्यथा
		ग_लिखो_audio_gpio(&mix->audio_reset, 1);
पूर्ण

/* resume mixer */
अटल व्योम tumbler_resume(काष्ठा snd_pmac *chip)
अणु
	काष्ठा pmac_tumbler *mix = chip->mixer_data;

	mix->acs &= ~1;
	mix->master_चयन[0] = mix->save_master_चयन[0];
	mix->master_चयन[1] = mix->save_master_चयन[1];
	mix->master_vol[0] = mix->save_master_vol[0];
	mix->master_vol[1] = mix->save_master_vol[1];
	tumbler_reset_audio(chip);
	अगर (mix->i2c.client && mix->i2c.init_client) अणु
		अगर (mix->i2c.init_client(&mix->i2c) < 0)
			prपूर्णांकk(KERN_ERR "tumbler_init_client error\n");
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "tumbler: i2c is not initialized\n");
	अगर (chip->model == PMAC_TUMBLER) अणु
		tumbler_set_mono_volume(mix, &tumbler_pcm_vol_info);
		tumbler_set_mono_volume(mix, &tumbler_bass_vol_info);
		tumbler_set_mono_volume(mix, &tumbler_treble_vol_info);
		tumbler_set_drc(mix);
	पूर्ण अन्यथा अणु
		snapper_set_mix_vol(mix, VOL_IDX_PCM);
		snapper_set_mix_vol(mix, VOL_IDX_PCM2);
		snapper_set_mix_vol(mix, VOL_IDX_ADC);
		tumbler_set_mono_volume(mix, &snapper_bass_vol_info);
		tumbler_set_mono_volume(mix, &snapper_treble_vol_info);
		snapper_set_drc(mix);
		snapper_set_capture_source(mix);
	पूर्ण
	tumbler_set_master_volume(mix);
	अगर (chip->update_स्वतःmute)
		chip->update_स्वतःmute(chip, 0);
	अगर (mix->headphone_irq >= 0) अणु
		अचिन्हित अक्षर val;

		enable_irq(mix->headphone_irq);
		/* activate headphone status पूर्णांकerrupts */
		val = करो_gpio_पढ़ो(&mix->hp_detect);
		करो_gpio_ग_लिखो(&mix->hp_detect, val | 0x80);
	पूर्ण
	अगर (mix->lineout_irq >= 0)
		enable_irq(mix->lineout_irq);
पूर्ण
#पूर्ण_अगर

/* initialize tumbler */
अटल पूर्णांक tumbler_init(काष्ठा snd_pmac *chip)
अणु
	पूर्णांक irq;
	काष्ठा pmac_tumbler *mix = chip->mixer_data;

	अगर (tumbler_find_device("audio-hw-reset",
				"platform-do-hw-reset",
				&mix->audio_reset, 0) < 0)
		tumbler_find_device("hw-reset",
				    "platform-do-hw-reset",
				    &mix->audio_reset, 1);
	अगर (tumbler_find_device("amp-mute",
				"platform-do-amp-mute",
				&mix->amp_mute, 0) < 0)
		tumbler_find_device("amp-mute",
				    "platform-do-amp-mute",
				    &mix->amp_mute, 1);
	अगर (tumbler_find_device("headphone-mute",
				"platform-do-headphone-mute",
				&mix->hp_mute, 0) < 0)
		tumbler_find_device("headphone-mute",
				    "platform-do-headphone-mute",
				    &mix->hp_mute, 1);
	अगर (tumbler_find_device("line-output-mute",
				"platform-do-lineout-mute",
				&mix->line_mute, 0) < 0)
		tumbler_find_device("line-output-mute",
				   "platform-do-lineout-mute",
				    &mix->line_mute, 1);
	irq = tumbler_find_device("headphone-detect",
				  शून्य, &mix->hp_detect, 0);
	अगर (irq <= 0)
		irq = tumbler_find_device("headphone-detect",
					  शून्य, &mix->hp_detect, 1);
	अगर (irq <= 0)
		irq = tumbler_find_device("keywest-gpio15",
					  शून्य, &mix->hp_detect, 1);
	mix->headphone_irq = irq;
 	irq = tumbler_find_device("line-output-detect",
				  शून्य, &mix->line_detect, 0);
	अगर (irq <= 0)
		irq = tumbler_find_device("line-output-detect",
					  शून्य, &mix->line_detect, 1);
	अगर (IS_G4DA && irq <= 0)
		irq = tumbler_find_device("keywest-gpio16",
					  शून्य, &mix->line_detect, 1);
	mix->lineout_irq = irq;

	tumbler_reset_audio(chip);
  
	वापस 0;
पूर्ण

अटल व्योम tumbler_cleanup(काष्ठा snd_pmac *chip)
अणु
	काष्ठा pmac_tumbler *mix = chip->mixer_data;
	अगर (! mix)
		वापस;

	अगर (mix->headphone_irq >= 0)
		मुक्त_irq(mix->headphone_irq, chip);
	अगर (mix->lineout_irq >= 0)
		मुक्त_irq(mix->lineout_irq, chip);
	tumbler_gpio_मुक्त(&mix->audio_reset);
	tumbler_gpio_मुक्त(&mix->amp_mute);
	tumbler_gpio_मुक्त(&mix->hp_mute);
	tumbler_gpio_मुक्त(&mix->hp_detect);
	snd_pmac_keywest_cleanup(&mix->i2c);
	kमुक्त(mix);
	chip->mixer_data = शून्य;
पूर्ण

/* exported */
पूर्णांक snd_pmac_tumbler_init(काष्ठा snd_pmac *chip)
अणु
	पूर्णांक i, err;
	काष्ठा pmac_tumbler *mix;
	स्थिर u32 *paddr;
	काष्ठा device_node *tas_node, *np;
	अक्षर *chipname;

	request_module("i2c-powermac");

	mix = kzalloc(माप(*mix), GFP_KERNEL);
	अगर (! mix)
		वापस -ENOMEM;
	mix->headphone_irq = -1;

	chip->mixer_data = mix;
	chip->mixer_मुक्त = tumbler_cleanup;
	mix->anded_reset = 0;
	mix->reset_on_sleep = 1;

	क्रम_each_child_of_node(chip->node, np) अणु
		अगर (of_node_name_eq(np, "sound")) अणु
			अगर (of_get_property(np, "has-anded-reset", शून्य))
				mix->anded_reset = 1;
			अगर (of_get_property(np, "layout-id", शून्य))
				mix->reset_on_sleep = 0;
			of_node_put(np);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर ((err = tumbler_init(chip)) < 0)
		वापस err;

	/* set up TAS */
	tas_node = of_find_node_by_name(शून्य, "deq");
	अगर (tas_node == शून्य)
		tas_node = of_find_node_by_name(शून्य, "codec");
	अगर (tas_node == शून्य)
		वापस -ENODEV;

	paddr = of_get_property(tas_node, "i2c-address", शून्य);
	अगर (paddr == शून्य)
		paddr = of_get_property(tas_node, "reg", शून्य);
	अगर (paddr)
		mix->i2c.addr = (*paddr) >> 1;
	अन्यथा
		mix->i2c.addr = TAS_I2C_ADDR;
	of_node_put(tas_node);

	DBG("(I) TAS i2c address is: %x\n", mix->i2c.addr);

	अगर (chip->model == PMAC_TUMBLER) अणु
		mix->i2c.init_client = tumbler_init_client;
		mix->i2c.name = "TAS3001c";
		chipname = "Tumbler";
	पूर्ण अन्यथा अणु
		mix->i2c.init_client = snapper_init_client;
		mix->i2c.name = "TAS3004";
		chipname = "Snapper";
	पूर्ण

	अगर ((err = snd_pmac_keywest_init(&mix->i2c)) < 0)
		वापस err;

	/*
	 * build mixers
	 */
	प्र_लिखो(chip->card->mixername, "PowerMac %s", chipname);

	अगर (chip->model == PMAC_TUMBLER) अणु
		क्रम (i = 0; i < ARRAY_SIZE(tumbler_mixers); i++) अणु
			अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&tumbler_mixers[i], chip))) < 0)
				वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(snapper_mixers); i++) अणु
			अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snapper_mixers[i], chip))) < 0)
				वापस err;
		पूर्ण
	पूर्ण
	chip->master_sw_ctl = snd_ctl_new1(&tumbler_hp_sw, chip);
	अगर ((err = snd_ctl_add(chip->card, chip->master_sw_ctl)) < 0)
		वापस err;
	chip->speaker_sw_ctl = snd_ctl_new1(&tumbler_speaker_sw, chip);
	अगर ((err = snd_ctl_add(chip->card, chip->speaker_sw_ctl)) < 0)
		वापस err;
	अगर (mix->line_mute.addr != 0) अणु
		chip->lineout_sw_ctl = snd_ctl_new1(&tumbler_lineout_sw, chip);
		अगर ((err = snd_ctl_add(chip->card, chip->lineout_sw_ctl)) < 0)
			वापस err;
	पूर्ण
	chip->drc_sw_ctl = snd_ctl_new1(&tumbler_drc_sw, chip);
	अगर ((err = snd_ctl_add(chip->card, chip->drc_sw_ctl)) < 0)
		वापस err;

	/* set initial DRC range to 60% */
	अगर (chip->model == PMAC_TUMBLER)
		mix->drc_range = (TAS3001_DRC_MAX * 6) / 10;
	अन्यथा
		mix->drc_range = (TAS3004_DRC_MAX * 6) / 10;
	mix->drc_enable = 1; /* will be changed later अगर AUTO_DRC is set */
	अगर (chip->model == PMAC_TUMBLER)
		tumbler_set_drc(mix);
	अन्यथा
		snapper_set_drc(mix);

#अगर_घोषित CONFIG_PM
	chip->suspend = tumbler_suspend;
	chip->resume = tumbler_resume;
#पूर्ण_अगर

	INIT_WORK(&device_change, device_change_handler);
	device_change_chip = chip;

#अगर_घोषित PMAC_SUPPORT_AUTOMUTE
	अगर ((mix->headphone_irq >=0 || mix->lineout_irq >= 0)
	    && (err = snd_pmac_add_स्वतःmute(chip)) < 0)
		वापस err;
	chip->detect_headphone = tumbler_detect_headphone;
	chip->update_स्वतःmute = tumbler_update_स्वतःmute;
	tumbler_update_स्वतःmute(chip, 0); /* update the status only */

	/* activate headphone status पूर्णांकerrupts */
  	अगर (mix->headphone_irq >= 0) अणु
		अचिन्हित अक्षर val;
		अगर ((err = request_irq(mix->headphone_irq, headphone_पूर्णांकr, 0,
				       "Sound Headphone Detection", chip)) < 0)
			वापस 0;
		/* activate headphone status पूर्णांकerrupts */
		val = करो_gpio_पढ़ो(&mix->hp_detect);
		करो_gpio_ग_लिखो(&mix->hp_detect, val | 0x80);
	पूर्ण
  	अगर (mix->lineout_irq >= 0) अणु
		अचिन्हित अक्षर val;
		अगर ((err = request_irq(mix->lineout_irq, headphone_पूर्णांकr, 0,
				       "Sound Lineout Detection", chip)) < 0)
			वापस 0;
		/* activate headphone status पूर्णांकerrupts */
		val = करो_gpio_पढ़ो(&mix->line_detect);
		करो_gpio_ग_लिखो(&mix->line_detect, val | 0x80);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण
