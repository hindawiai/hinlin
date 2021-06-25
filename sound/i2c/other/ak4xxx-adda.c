<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम AK4524 / AK4528 / AK4529 / AK4355 / AK4358 / AK4381
 *   AD and DA converters
 *
 *	Copyright (c) 2000-2004 Jaroslav Kysela <perex@perex.cz>,
 *				Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश <sound/ak4xxx-adda.h>
#समावेश <sound/info.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>, Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("Routines for control of AK452x / AK43xx  AD/DA converters");
MODULE_LICENSE("GPL");

/* ग_लिखो the given रेजिस्टर and save the data to the cache */
व्योम snd_akm4xxx_ग_लिखो(काष्ठा snd_akm4xxx *ak, पूर्णांक chip, अचिन्हित अक्षर reg,
		       अचिन्हित अक्षर val)
अणु
	ak->ops.lock(ak, chip);
	ak->ops.ग_लिखो(ak, chip, reg, val);

	/* save the data */
	snd_akm4xxx_set(ak, chip, reg, val);
	ak->ops.unlock(ak, chip);
पूर्ण

EXPORT_SYMBOL(snd_akm4xxx_ग_लिखो);

/* reset procedure क्रम AK4524 and AK4528 */
अटल व्योम ak4524_reset(काष्ठा snd_akm4xxx *ak, पूर्णांक state)
अणु
	अचिन्हित पूर्णांक chip;
	अचिन्हित अक्षर reg;

	क्रम (chip = 0; chip < ak->num_dacs/2; chip++) अणु
		snd_akm4xxx_ग_लिखो(ak, chip, 0x01, state ? 0x00 : 0x03);
		अगर (state)
			जारी;
		/* DAC volumes */
		क्रम (reg = 0x04; reg < ak->total_regs; reg++)
			snd_akm4xxx_ग_लिखो(ak, chip, reg,
					  snd_akm4xxx_get(ak, chip, reg));
	पूर्ण
पूर्ण

/* reset procedure क्रम AK4355 and AK4358 */
अटल व्योम ak435X_reset(काष्ठा snd_akm4xxx *ak, पूर्णांक state)
अणु
	अचिन्हित अक्षर reg;

	अगर (state) अणु
		snd_akm4xxx_ग_लिखो(ak, 0, 0x01, 0x02); /* reset and soft-mute */
		वापस;
	पूर्ण
	क्रम (reg = 0x00; reg < ak->total_regs; reg++)
		अगर (reg != 0x01)
			snd_akm4xxx_ग_लिखो(ak, 0, reg,
					  snd_akm4xxx_get(ak, 0, reg));
	snd_akm4xxx_ग_लिखो(ak, 0, 0x01, 0x01); /* un-reset, unmute */
पूर्ण

/* reset procedure क्रम AK4381 */
अटल व्योम ak4381_reset(काष्ठा snd_akm4xxx *ak, पूर्णांक state)
अणु
	अचिन्हित पूर्णांक chip;
	अचिन्हित अक्षर reg;
	क्रम (chip = 0; chip < ak->num_dacs/2; chip++) अणु
		snd_akm4xxx_ग_लिखो(ak, chip, 0x00, state ? 0x0c : 0x0f);
		अगर (state)
			जारी;
		क्रम (reg = 0x01; reg < ak->total_regs; reg++)
			snd_akm4xxx_ग_लिखो(ak, chip, reg,
					  snd_akm4xxx_get(ak, chip, reg));
	पूर्ण
पूर्ण

/*
 * reset the AKM codecs
 * @state: 1 = reset codec, 0 = restore the रेजिस्टरs
 *
 * निश्चित the reset operation and restores the रेजिस्टर values to the chips.
 */
व्योम snd_akm4xxx_reset(काष्ठा snd_akm4xxx *ak, पूर्णांक state)
अणु
	चयन (ak->type) अणु
	हाल SND_AK4524:
	हाल SND_AK4528:
	हाल SND_AK4620:
		ak4524_reset(ak, state);
		अवरोध;
	हाल SND_AK4529:
		/* FIXME: needed क्रम ak4529? */
		अवरोध;
	हाल SND_AK4355:
		ak435X_reset(ak, state);
		अवरोध;
	हाल SND_AK4358:
		ak435X_reset(ak, state);
		अवरोध;
	हाल SND_AK4381:
		ak4381_reset(ak, state);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

EXPORT_SYMBOL(snd_akm4xxx_reset);


/*
 * Volume conversion table क्रम non-linear volumes
 * from -63.5dB (mute) to 0dB step 0.5dB
 *
 * Used क्रम AK4524/AK4620 input/ouput attenuation, AK4528, and
 * AK5365 input attenuation
 */
अटल स्थिर अचिन्हित अक्षर vol_cvt_datt[128] = अणु
	0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04,
	0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x06, 0x06,
	0x06, 0x07, 0x07, 0x08, 0x08, 0x08, 0x09, 0x0a,
	0x0a, 0x0b, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x0f,
	0x10, 0x10, 0x11, 0x12, 0x12, 0x13, 0x13, 0x14,
	0x15, 0x16, 0x17, 0x17, 0x18, 0x19, 0x1a, 0x1c,
	0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x23,
	0x24, 0x25, 0x26, 0x28, 0x29, 0x2a, 0x2b, 0x2d,
	0x2e, 0x30, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
	0x37, 0x38, 0x39, 0x3b, 0x3c, 0x3e, 0x3f, 0x40,
	0x41, 0x42, 0x43, 0x44, 0x46, 0x47, 0x48, 0x4a,
	0x4b, 0x4d, 0x4e, 0x50, 0x51, 0x52, 0x53, 0x54,
	0x55, 0x56, 0x58, 0x59, 0x5b, 0x5c, 0x5e, 0x5f,
	0x60, 0x61, 0x62, 0x64, 0x65, 0x66, 0x67, 0x69,
	0x6a, 0x6c, 0x6d, 0x6f, 0x70, 0x71, 0x72, 0x73,
	0x75, 0x76, 0x77, 0x79, 0x7a, 0x7c, 0x7d, 0x7f,
पूर्ण;

/*
 * dB tables
 */
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_vol_datt, -6350, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_8bit, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_7bit, -6350, 50, 1);
अटल स्थिर DECLARE_TLV_DB_LINEAR(db_scale_linear, TLV_DB_GAIN_MUTE, 0);

/*
 * initialize all the ak4xxx chips
 */
व्योम snd_akm4xxx_init(काष्ठा snd_akm4xxx *ak)
अणु
	अटल स्थिर अचिन्हित अक्षर inits_ak4524[] = अणु
		0x00, 0x07, /* 0: all घातer up */
		0x01, 0x00, /* 1: ADC/DAC reset */
		0x02, 0x60, /* 2: 24bit I2S */
		0x03, 0x19, /* 3: deemphasis off */
		0x01, 0x03, /* 1: ADC/DAC enable */
		0x04, 0x00, /* 4: ADC left muted */
		0x05, 0x00, /* 5: ADC right muted */
		0x06, 0x00, /* 6: DAC left muted */
		0x07, 0x00, /* 7: DAC right muted */
		0xff, 0xff
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर inits_ak4528[] = अणु
		0x00, 0x07, /* 0: all घातer up */
		0x01, 0x00, /* 1: ADC/DAC reset */
		0x02, 0x60, /* 2: 24bit I2S */
		0x03, 0x0d, /* 3: deemphasis off, turn LR highpass filters on */
		0x01, 0x03, /* 1: ADC/DAC enable */
		0x04, 0x00, /* 4: ADC left muted */
		0x05, 0x00, /* 5: ADC right muted */
		0xff, 0xff
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर inits_ak4529[] = अणु
		0x09, 0x01, /* 9: ATS=0, RSTN=1 */
		0x0a, 0x3f, /* A: all घातer up, no zero/overflow detection */
		0x00, 0x0c, /* 0: TDM=0, 24bit I2S, SMUTE=0 */
		0x01, 0x00, /* 1: ACKS=0, ADC, loop off */
		0x02, 0xff, /* 2: LOUT1 muted */
		0x03, 0xff, /* 3: ROUT1 muted */
		0x04, 0xff, /* 4: LOUT2 muted */
		0x05, 0xff, /* 5: ROUT2 muted */
		0x06, 0xff, /* 6: LOUT3 muted */
		0x07, 0xff, /* 7: ROUT3 muted */
		0x0b, 0xff, /* B: LOUT4 muted */
		0x0c, 0xff, /* C: ROUT4 muted */
		0x08, 0x55, /* 8: deemphasis all off */
		0xff, 0xff
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर inits_ak4355[] = अणु
		0x01, 0x02, /* 1: reset and soft-mute */
		0x00, 0x06, /* 0: mode3(i2s), disable स्वतः-घड़ी detect,
			     * disable DZF, sharp roll-off, RSTN#=0 */
		0x02, 0x0e, /* 2: DA's घातer up, normal speed, RSTN#=0 */
		// 0x02, 0x2e, /* quad speed */
		0x03, 0x01, /* 3: de-emphasis off */
		0x04, 0x00, /* 4: LOUT1 volume muted */
		0x05, 0x00, /* 5: ROUT1 volume muted */
		0x06, 0x00, /* 6: LOUT2 volume muted */
		0x07, 0x00, /* 7: ROUT2 volume muted */
		0x08, 0x00, /* 8: LOUT3 volume muted */
		0x09, 0x00, /* 9: ROUT3 volume muted */
		0x0a, 0x00, /* a: DATT speed=0, ignore DZF */
		0x01, 0x01, /* 1: un-reset, unmute */
		0xff, 0xff
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर inits_ak4358[] = अणु
		0x01, 0x02, /* 1: reset and soft-mute */
		0x00, 0x06, /* 0: mode3(i2s), disable स्वतः-घड़ी detect,
			     * disable DZF, sharp roll-off, RSTN#=0 */
		0x02, 0x4e, /* 2: DA's घातer up, normal speed, RSTN#=0 */
		/* 0x02, 0x6e,*/ /* quad speed */
		0x03, 0x01, /* 3: de-emphasis off */
		0x04, 0x00, /* 4: LOUT1 volume muted */
		0x05, 0x00, /* 5: ROUT1 volume muted */
		0x06, 0x00, /* 6: LOUT2 volume muted */
		0x07, 0x00, /* 7: ROUT2 volume muted */
		0x08, 0x00, /* 8: LOUT3 volume muted */
		0x09, 0x00, /* 9: ROUT3 volume muted */
		0x0b, 0x00, /* b: LOUT4 volume muted */
		0x0c, 0x00, /* c: ROUT4 volume muted */
		0x0a, 0x00, /* a: DATT speed=0, ignore DZF */
		0x01, 0x01, /* 1: un-reset, unmute */
		0xff, 0xff
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर inits_ak4381[] = अणु
		0x00, 0x0c, /* 0: mode3(i2s), disable स्वतः-घड़ी detect */
		0x01, 0x02, /* 1: de-emphasis off, normal speed,
			     * sharp roll-off, DZF off */
		// 0x01, 0x12, /* quad speed */
		0x02, 0x00, /* 2: DZF disabled */
		0x03, 0x00, /* 3: LATT 0 */
		0x04, 0x00, /* 4: RATT 0 */
		0x00, 0x0f, /* 0: घातer-up, un-reset */
		0xff, 0xff
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर inits_ak4620[] = अणु
		0x00, 0x07, /* 0: normal */
		0x01, 0x00, /* 0: reset */
		0x01, 0x02, /* 1: RSTAD */
		0x01, 0x03, /* 1: RSTDA */
		0x01, 0x0f, /* 1: normal */
		0x02, 0x60, /* 2: 24bit I2S */
		0x03, 0x01, /* 3: deemphasis off */
		0x04, 0x00, /* 4: LIN muted */
		0x05, 0x00, /* 5: RIN muted */
		0x06, 0x00, /* 6: LOUT muted */
		0x07, 0x00, /* 7: ROUT muted */
		0xff, 0xff
	पूर्ण;

	पूर्णांक chip;
	स्थिर अचिन्हित अक्षर *ptr, *inits;
	अचिन्हित अक्षर reg, data;

	स_रखो(ak->images, 0, माप(ak->images));
	स_रखो(ak->volumes, 0, माप(ak->volumes));

	चयन (ak->type) अणु
	हाल SND_AK4524:
		inits = inits_ak4524;
		ak->num_chips = ak->num_dacs / 2;
		ak->name = "ak4524";
		ak->total_regs = 0x08;
		अवरोध;
	हाल SND_AK4528:
		inits = inits_ak4528;
		ak->num_chips = ak->num_dacs / 2;
		ak->name = "ak4528";
		ak->total_regs = 0x06;
		अवरोध;
	हाल SND_AK4529:
		inits = inits_ak4529;
		ak->num_chips = 1;
		ak->name = "ak4529";
		ak->total_regs = 0x0d;
		अवरोध;
	हाल SND_AK4355:
		inits = inits_ak4355;
		ak->num_chips = 1;
		ak->name = "ak4355";
		ak->total_regs = 0x0b;
		अवरोध;
	हाल SND_AK4358:
		inits = inits_ak4358;
		ak->num_chips = 1;
		ak->name = "ak4358";
		ak->total_regs = 0x10;
		अवरोध;
	हाल SND_AK4381:
		inits = inits_ak4381;
		ak->num_chips = ak->num_dacs / 2;
		ak->name = "ak4381";
		ak->total_regs = 0x05;
		अवरोध;
	हाल SND_AK5365:
		/* FIXME: any init sequence? */
		ak->num_chips = 1;
		ak->name = "ak5365";
		ak->total_regs = 0x08;
		वापस;
	हाल SND_AK4620:
		inits = inits_ak4620;
		ak->num_chips = ak->num_dacs / 2;
		ak->name = "ak4620";
		ak->total_regs = 0x08;
		अवरोध;
	शेष:
		snd_BUG();
		वापस;
	पूर्ण

	क्रम (chip = 0; chip < ak->num_chips; chip++) अणु
		ptr = inits;
		जबतक (*ptr != 0xff) अणु
			reg = *ptr++;
			data = *ptr++;
			snd_akm4xxx_ग_लिखो(ak, chip, reg, data);
			udelay(10);
		पूर्ण
	पूर्ण
पूर्ण

EXPORT_SYMBOL(snd_akm4xxx_init);

/*
 * Mixer callbacks
 */
#घोषणा AK_IPGA 			(1<<20)	/* including IPGA */
#घोषणा AK_VOL_CVT 			(1<<21)	/* need dB conversion */
#घोषणा AK_NEEDSMSB 			(1<<22)	/* need MSB update bit */
#घोषणा AK_INVERT 			(1<<23)	/* data is inverted */
#घोषणा AK_GET_CHIP(val)		(((val) >> 8) & 0xff)
#घोषणा AK_GET_ADDR(val)		((val) & 0xff)
#घोषणा AK_GET_SHIFT(val)		(((val) >> 16) & 0x0f)
#घोषणा AK_GET_VOL_CVT(val)		(((val) >> 21) & 1)
#घोषणा AK_GET_IPGA(val)		(((val) >> 20) & 1)
#घोषणा AK_GET_NEEDSMSB(val)		(((val) >> 22) & 1)
#घोषणा AK_GET_INVERT(val)		(((val) >> 23) & 1)
#घोषणा AK_GET_MASK(val)		(((val) >> 24) & 0xff)
#घोषणा AK_COMPOSE(chip,addr,shअगरt,mask) \
	(((chip) << 8) | (addr) | ((shअगरt) << 16) | ((mask) << 24))

अटल पूर्णांक snd_akm4xxx_volume_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अचिन्हित पूर्णांक mask = AK_GET_MASK(kcontrol->निजी_value);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_akm4xxx_volume_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	पूर्णांक chip = AK_GET_CHIP(kcontrol->निजी_value);
	पूर्णांक addr = AK_GET_ADDR(kcontrol->निजी_value);

	ucontrol->value.पूर्णांकeger.value[0] = snd_akm4xxx_get_vol(ak, chip, addr);
	वापस 0;
पूर्ण

अटल पूर्णांक put_ak_reg(काष्ठा snd_kcontrol *kcontrol, पूर्णांक addr,
		      अचिन्हित अक्षर nval)
अणु
	काष्ठा snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक mask = AK_GET_MASK(kcontrol->निजी_value);
	पूर्णांक chip = AK_GET_CHIP(kcontrol->निजी_value);

	अगर (snd_akm4xxx_get_vol(ak, chip, addr) == nval)
		वापस 0;

	snd_akm4xxx_set_vol(ak, chip, addr, nval);
	अगर (AK_GET_VOL_CVT(kcontrol->निजी_value) && nval < 128)
		nval = vol_cvt_datt[nval];
	अगर (AK_GET_IPGA(kcontrol->निजी_value) && nval >= 128)
		nval++; /* need to correct + 1 since both 127 and 128 are 0dB */
	अगर (AK_GET_INVERT(kcontrol->निजी_value))
		nval = mask - nval;
	अगर (AK_GET_NEEDSMSB(kcontrol->निजी_value))
		nval |= 0x80;
	/* prपूर्णांकk(KERN_DEBUG "DEBUG - AK writing reg: chip %x addr %x,
	   nval %x\न", chip, addr, nval); */
	snd_akm4xxx_ग_लिखो(ak, chip, addr, nval);
	वापस 1;
पूर्ण

अटल पूर्णांक snd_akm4xxx_volume_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित पूर्णांक mask = AK_GET_MASK(kcontrol->निजी_value);
	अचिन्हित पूर्णांक val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (val > mask)
		वापस -EINVAL;
	वापस put_ak_reg(kcontrol, AK_GET_ADDR(kcontrol->निजी_value), val);
पूर्ण

अटल पूर्णांक snd_akm4xxx_stereo_volume_info(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अचिन्हित पूर्णांक mask = AK_GET_MASK(kcontrol->निजी_value);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_akm4xxx_stereo_volume_get(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	पूर्णांक chip = AK_GET_CHIP(kcontrol->निजी_value);
	पूर्णांक addr = AK_GET_ADDR(kcontrol->निजी_value);

	ucontrol->value.पूर्णांकeger.value[0] = snd_akm4xxx_get_vol(ak, chip, addr);
	ucontrol->value.पूर्णांकeger.value[1] = snd_akm4xxx_get_vol(ak, chip, addr+1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_akm4xxx_stereo_volume_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक addr = AK_GET_ADDR(kcontrol->निजी_value);
	अचिन्हित पूर्णांक mask = AK_GET_MASK(kcontrol->निजी_value);
	अचिन्हित पूर्णांक val[2];
	पूर्णांक change;

	val[0] = ucontrol->value.पूर्णांकeger.value[0];
	val[1] = ucontrol->value.पूर्णांकeger.value[1];
	अगर (val[0] > mask || val[1] > mask)
		वापस -EINVAL;
	change = put_ak_reg(kcontrol, addr, val[0]);
	change |= put_ak_reg(kcontrol, addr + 1, val[1]);
	वापस change;
पूर्ण

अटल पूर्णांक snd_akm4xxx_deemphasis_info(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"44.1kHz", "Off", "48kHz", "32kHz",
	पूर्ण;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 4, texts);
पूर्ण

अटल पूर्णांक snd_akm4xxx_deemphasis_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	पूर्णांक chip = AK_GET_CHIP(kcontrol->निजी_value);
	पूर्णांक addr = AK_GET_ADDR(kcontrol->निजी_value);
	पूर्णांक shअगरt = AK_GET_SHIFT(kcontrol->निजी_value);
	ucontrol->value.क्रमागतerated.item[0] =
		(snd_akm4xxx_get(ak, chip, addr) >> shअगरt) & 3;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_akm4xxx_deemphasis_put(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	पूर्णांक chip = AK_GET_CHIP(kcontrol->निजी_value);
	पूर्णांक addr = AK_GET_ADDR(kcontrol->निजी_value);
	पूर्णांक shअगरt = AK_GET_SHIFT(kcontrol->निजी_value);
	अचिन्हित अक्षर nval = ucontrol->value.क्रमागतerated.item[0] & 3;
	पूर्णांक change;
	
	nval = (nval << shअगरt) |
		(snd_akm4xxx_get(ak, chip, addr) & ~(3 << shअगरt));
	change = snd_akm4xxx_get(ak, chip, addr) != nval;
	अगर (change)
		snd_akm4xxx_ग_लिखो(ak, chip, addr, nval);
	वापस change;
पूर्ण

#घोषणा ak4xxx_चयन_info	snd_ctl_boolean_mono_info

अटल पूर्णांक ak4xxx_चयन_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	पूर्णांक chip = AK_GET_CHIP(kcontrol->निजी_value);
	पूर्णांक addr = AK_GET_ADDR(kcontrol->निजी_value);
	पूर्णांक shअगरt = AK_GET_SHIFT(kcontrol->निजी_value);
	पूर्णांक invert = AK_GET_INVERT(kcontrol->निजी_value);
	/* we observe the (1<<shअगरt) bit only */
	अचिन्हित अक्षर val = snd_akm4xxx_get(ak, chip, addr) & (1<<shअगरt);
	अगर (invert)
		val = ! val;
	ucontrol->value.पूर्णांकeger.value[0] = (val & (1<<shअगरt)) != 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ak4xxx_चयन_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	पूर्णांक chip = AK_GET_CHIP(kcontrol->निजी_value);
	पूर्णांक addr = AK_GET_ADDR(kcontrol->निजी_value);
	पूर्णांक shअगरt = AK_GET_SHIFT(kcontrol->निजी_value);
	पूर्णांक invert = AK_GET_INVERT(kcontrol->निजी_value);
	दीर्घ flag = ucontrol->value.पूर्णांकeger.value[0];
	अचिन्हित अक्षर val, oval;
	पूर्णांक change;

	अगर (invert)
		flag = ! flag;
	oval = snd_akm4xxx_get(ak, chip, addr);
	अगर (flag)
		val = oval | (1<<shअगरt);
	अन्यथा
		val = oval & ~(1<<shअगरt);
	change = (oval != val);
	अगर (change)
		snd_akm4xxx_ग_लिखो(ak, chip, addr, val);
	वापस change;
पूर्ण

#घोषणा AK5365_NUM_INPUTS 5

अटल पूर्णांक ak4xxx_capture_num_inमाला_दो(काष्ठा snd_akm4xxx *ak, पूर्णांक mixer_ch)
अणु
	पूर्णांक num_names;
	स्थिर अक्षर **input_names;

	input_names = ak->adc_info[mixer_ch].input_names;
	num_names = 0;
	जबतक (num_names < AK5365_NUM_INPUTS && input_names[num_names])
		++num_names;
	वापस num_names;
पूर्ण

अटल पूर्णांक ak4xxx_capture_source_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	पूर्णांक mixer_ch = AK_GET_SHIFT(kcontrol->निजी_value);
	अचिन्हित पूर्णांक num_names;

	num_names = ak4xxx_capture_num_inमाला_दो(ak, mixer_ch);
	अगर (!num_names)
		वापस -EINVAL;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, num_names,
				 ak->adc_info[mixer_ch].input_names);
पूर्ण

अटल पूर्णांक ak4xxx_capture_source_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	पूर्णांक chip = AK_GET_CHIP(kcontrol->निजी_value);
	पूर्णांक addr = AK_GET_ADDR(kcontrol->निजी_value);
	पूर्णांक mask = AK_GET_MASK(kcontrol->निजी_value);
	अचिन्हित अक्षर val;

	val = snd_akm4xxx_get(ak, chip, addr) & mask;
	ucontrol->value.क्रमागतerated.item[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक ak4xxx_capture_source_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	पूर्णांक mixer_ch = AK_GET_SHIFT(kcontrol->निजी_value);
	पूर्णांक chip = AK_GET_CHIP(kcontrol->निजी_value);
	पूर्णांक addr = AK_GET_ADDR(kcontrol->निजी_value);
	पूर्णांक mask = AK_GET_MASK(kcontrol->निजी_value);
	अचिन्हित अक्षर oval, val;
	पूर्णांक num_names = ak4xxx_capture_num_inमाला_दो(ak, mixer_ch);

	अगर (ucontrol->value.क्रमागतerated.item[0] >= num_names)
		वापस -EINVAL;

	oval = snd_akm4xxx_get(ak, chip, addr);
	val = oval & ~mask;
	val |= ucontrol->value.क्रमागतerated.item[0] & mask;
	अगर (val != oval) अणु
		snd_akm4xxx_ग_लिखो(ak, chip, addr, val);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * build AK4xxx controls
 */

अटल पूर्णांक build_dac_controls(काष्ठा snd_akm4xxx *ak)
अणु
	पूर्णांक idx, err, mixer_ch, num_stereo;
	काष्ठा snd_kcontrol_new knew;

	mixer_ch = 0;
	क्रम (idx = 0; idx < ak->num_dacs; ) अणु
		/* mute control क्रम Revolution 7.1 - AK4381 */
		अगर (ak->type == SND_AK4381 
				&&  ak->dac_info[mixer_ch].चयन_name) अणु
			स_रखो(&knew, 0, माप(knew));
			knew.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
			knew.count = 1;
			knew.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
			knew.name = ak->dac_info[mixer_ch].चयन_name;
			knew.info = ak4xxx_चयन_info;
			knew.get = ak4xxx_चयन_get;
			knew.put = ak4xxx_चयन_put;
			knew.access = 0;
			/* रेजिस्टर 1, bit 0 (SMUTE): 0 = normal operation,
			   1 = mute */
			knew.निजी_value =
				AK_COMPOSE(idx/2, 1, 0, 0) | AK_INVERT;
			err = snd_ctl_add(ak->card, snd_ctl_new1(&knew, ak));
			अगर (err < 0)
				वापस err;
		पूर्ण
		स_रखो(&knew, 0, माप(knew));
		अगर (! ak->dac_info || ! ak->dac_info[mixer_ch].name) अणु
			knew.name = "DAC Volume";
			knew.index = mixer_ch + ak->idx_offset * 2;
			num_stereo = 1;
		पूर्ण अन्यथा अणु
			knew.name = ak->dac_info[mixer_ch].name;
			num_stereo = ak->dac_info[mixer_ch].num_channels;
		पूर्ण
		knew.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		knew.count = 1;
		knew.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ;
		अगर (num_stereo == 2) अणु
			knew.info = snd_akm4xxx_stereo_volume_info;
			knew.get = snd_akm4xxx_stereo_volume_get;
			knew.put = snd_akm4xxx_stereo_volume_put;
		पूर्ण अन्यथा अणु
			knew.info = snd_akm4xxx_volume_info;
			knew.get = snd_akm4xxx_volume_get;
			knew.put = snd_akm4xxx_volume_put;
		पूर्ण
		चयन (ak->type) अणु
		हाल SND_AK4524:
			/* रेजिस्टर 6 & 7 */
			knew.निजी_value =
				AK_COMPOSE(idx/2, (idx%2) + 6, 0, 127) |
				AK_VOL_CVT;
			knew.tlv.p = db_scale_vol_datt;
			अवरोध;
		हाल SND_AK4528:
			/* रेजिस्टर 4 & 5 */
			knew.निजी_value =
				AK_COMPOSE(idx/2, (idx%2) + 4, 0, 127) |
				AK_VOL_CVT;
			knew.tlv.p = db_scale_vol_datt;
			अवरोध;
		हाल SND_AK4529: अणु
			/* रेजिस्टरs 2-7 and b,c */
			पूर्णांक val = idx < 6 ? idx + 2 : (idx - 6) + 0xb;
			knew.निजी_value =
				AK_COMPOSE(0, val, 0, 255) | AK_INVERT;
			knew.tlv.p = db_scale_8bit;
			अवरोध;
		पूर्ण
		हाल SND_AK4355:
			/* रेजिस्टर 4-9, chip #0 only */
			knew.निजी_value = AK_COMPOSE(0, idx + 4, 0, 255);
			knew.tlv.p = db_scale_8bit;
			अवरोध;
		हाल SND_AK4358: अणु
			/* रेजिस्टर 4-9 and 11-12, chip #0 only */
			पूर्णांक  addr = idx < 6 ? idx + 4 : idx + 5;
			knew.निजी_value =
				AK_COMPOSE(0, addr, 0, 127) | AK_NEEDSMSB;
			knew.tlv.p = db_scale_7bit;
			अवरोध;
		पूर्ण
		हाल SND_AK4381:
			/* रेजिस्टर 3 & 4 */
			knew.निजी_value =
				AK_COMPOSE(idx/2, (idx%2) + 3, 0, 255);
			knew.tlv.p = db_scale_linear;
			अवरोध;
		हाल SND_AK4620:
			/* रेजिस्टर 6 & 7 */
			knew.निजी_value =
				AK_COMPOSE(idx/2, (idx%2) + 6, 0, 255);
			knew.tlv.p = db_scale_linear;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		err = snd_ctl_add(ak->card, snd_ctl_new1(&knew, ak));
		अगर (err < 0)
			वापस err;

		idx += num_stereo;
		mixer_ch++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक build_adc_controls(काष्ठा snd_akm4xxx *ak)
अणु
	पूर्णांक idx, err, mixer_ch, num_stereo, max_steps;
	काष्ठा snd_kcontrol_new knew;

	mixer_ch = 0;
	अगर (ak->type == SND_AK4528)
		वापस 0;	/* no controls */
	क्रम (idx = 0; idx < ak->num_adcs;) अणु
		स_रखो(&knew, 0, माप(knew));
		अगर (! ak->adc_info || ! ak->adc_info[mixer_ch].name) अणु
			knew.name = "ADC Volume";
			knew.index = mixer_ch + ak->idx_offset * 2;
			num_stereo = 1;
		पूर्ण अन्यथा अणु
			knew.name = ak->adc_info[mixer_ch].name;
			num_stereo = ak->adc_info[mixer_ch].num_channels;
		पूर्ण
		knew.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		knew.count = 1;
		knew.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ;
		अगर (num_stereo == 2) अणु
			knew.info = snd_akm4xxx_stereo_volume_info;
			knew.get = snd_akm4xxx_stereo_volume_get;
			knew.put = snd_akm4xxx_stereo_volume_put;
		पूर्ण अन्यथा अणु
			knew.info = snd_akm4xxx_volume_info;
			knew.get = snd_akm4xxx_volume_get;
			knew.put = snd_akm4xxx_volume_put;
		पूर्ण
		/* रेजिस्टर 4 & 5 */
		अगर (ak->type == SND_AK5365)
			max_steps = 152;
		अन्यथा
			max_steps = 164;
		knew.निजी_value =
			AK_COMPOSE(idx/2, (idx%2) + 4, 0, max_steps) |
			AK_VOL_CVT | AK_IPGA;
		knew.tlv.p = db_scale_vol_datt;
		err = snd_ctl_add(ak->card, snd_ctl_new1(&knew, ak));
		अगर (err < 0)
			वापस err;

		अगर (ak->type == SND_AK5365 && (idx % 2) == 0) अणु
			अगर (! ak->adc_info || 
			    ! ak->adc_info[mixer_ch].चयन_name) अणु
				knew.name = "Capture Switch";
				knew.index = mixer_ch + ak->idx_offset * 2;
			पूर्ण अन्यथा
				knew.name = ak->adc_info[mixer_ch].चयन_name;
			knew.info = ak4xxx_चयन_info;
			knew.get = ak4xxx_चयन_get;
			knew.put = ak4xxx_चयन_put;
			knew.access = 0;
			/* रेजिस्टर 2, bit 0 (SMUTE): 0 = normal operation,
			   1 = mute */
			knew.निजी_value =
				AK_COMPOSE(idx/2, 2, 0, 0) | AK_INVERT;
			err = snd_ctl_add(ak->card, snd_ctl_new1(&knew, ak));
			अगर (err < 0)
				वापस err;

			स_रखो(&knew, 0, माप(knew));
			अगर (!ak->adc_info ||
				!ak->adc_info[mixer_ch].selector_name) अणु
				knew.name = "Capture Channel";
				knew.index = mixer_ch + ak->idx_offset * 2;
			पूर्ण अन्यथा
				knew.name = ak->adc_info[mixer_ch].selector_name;

			knew.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
			knew.info = ak4xxx_capture_source_info;
			knew.get = ak4xxx_capture_source_get;
			knew.put = ak4xxx_capture_source_put;
			knew.access = 0;
			/* input selector control: reg. 1, bits 0-2.
			 * mis-use 'shift' to pass mixer_ch */
			knew.निजी_value
				= AK_COMPOSE(idx/2, 1, mixer_ch, 0x07);
			err = snd_ctl_add(ak->card, snd_ctl_new1(&knew, ak));
			अगर (err < 0)
				वापस err;
		पूर्ण

		idx += num_stereo;
		mixer_ch++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक build_deemphasis(काष्ठा snd_akm4xxx *ak, पूर्णांक num_emphs)
अणु
	पूर्णांक idx, err;
	काष्ठा snd_kcontrol_new knew;

	क्रम (idx = 0; idx < num_emphs; idx++) अणु
		स_रखो(&knew, 0, माप(knew));
		knew.name = "Deemphasis";
		knew.index = idx + ak->idx_offset;
		knew.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		knew.count = 1;
		knew.info = snd_akm4xxx_deemphasis_info;
		knew.get = snd_akm4xxx_deemphasis_get;
		knew.put = snd_akm4xxx_deemphasis_put;
		चयन (ak->type) अणु
		हाल SND_AK4524:
		हाल SND_AK4528:
		हाल SND_AK4620:
			/* रेजिस्टर 3 */
			knew.निजी_value = AK_COMPOSE(idx, 3, 0, 0);
			अवरोध;
		हाल SND_AK4529: अणु
			पूर्णांक shअगरt = idx == 3 ? 6 : (2 - idx) * 2;
			/* रेजिस्टर 8 with shअगरt */
			knew.निजी_value = AK_COMPOSE(0, 8, shअगरt, 0);
			अवरोध;
		पूर्ण
		हाल SND_AK4355:
		हाल SND_AK4358:
			knew.निजी_value = AK_COMPOSE(idx, 3, 0, 0);
			अवरोध;
		हाल SND_AK4381:
			knew.निजी_value = AK_COMPOSE(idx, 1, 1, 0);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		err = snd_ctl_add(ak->card, snd_ctl_new1(&knew, ak));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम proc_regs_पढ़ो(काष्ठा snd_info_entry *entry,
		काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_akm4xxx *ak = entry->निजी_data;
	पूर्णांक reg, val, chip;
	क्रम (chip = 0; chip < ak->num_chips; chip++) अणु
		क्रम (reg = 0; reg < ak->total_regs; reg++) अणु
			val =  snd_akm4xxx_get(ak, chip, reg);
			snd_iम_लिखो(buffer, "chip %d: 0x%02x = 0x%02x\n", chip,
					reg, val);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक proc_init(काष्ठा snd_akm4xxx *ak)
अणु
	वापस snd_card_ro_proc_new(ak->card, ak->name, ak, proc_regs_पढ़ो);
पूर्ण

पूर्णांक snd_akm4xxx_build_controls(काष्ठा snd_akm4xxx *ak)
अणु
	पूर्णांक err, num_emphs;

	err = build_dac_controls(ak);
	अगर (err < 0)
		वापस err;

	err = build_adc_controls(ak);
	अगर (err < 0)
		वापस err;
	अगर (ak->type == SND_AK4355 || ak->type == SND_AK4358)
		num_emphs = 1;
	अन्यथा अगर (ak->type == SND_AK4620)
		num_emphs = 0;
	अन्यथा
		num_emphs = ak->num_dacs / 2;
	err = build_deemphasis(ak, num_emphs);
	अगर (err < 0)
		वापस err;
	err = proc_init(ak);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_akm4xxx_build_controls);
