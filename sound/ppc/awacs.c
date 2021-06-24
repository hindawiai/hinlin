<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PMac AWACS lowlevel functions
 *
 * Copyright (c) by Takashi Iwai <tiwai@suse.de>
 * code based on dmasound.c.
 */


#समावेश <linux/पन.स>
#समावेश <यंत्र/nvram.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश "pmac.h"


#अगर_घोषित CONFIG_ADB_CUDA
#घोषणा PMAC_AMP_AVAIL
#पूर्ण_अगर

#अगर_घोषित PMAC_AMP_AVAIL
काष्ठा awacs_amp अणु
	अचिन्हित अक्षर amp_master;
	अचिन्हित अक्षर amp_vol[2][2];
	अचिन्हित अक्षर amp_tone[2];
पूर्ण;

#घोषणा CHECK_CUDA_AMP() (sys_ctrler == SYS_CTRLER_CUDA)

#पूर्ण_अगर /* PMAC_AMP_AVAIL */


अटल व्योम snd_pmac_screamer_रुको(काष्ठा snd_pmac *chip)
अणु
	दीर्घ समयout = 2000;
	जबतक (!(in_le32(&chip->awacs->codec_stat) & MASK_VALID)) अणु
		mdelay(1);
		अगर (! --समयout) अणु
			snd_prपूर्णांकd("snd_pmac_screamer_wait timeout\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * ग_लिखो AWACS रेजिस्टर
 */
अटल व्योम
snd_pmac_awacs_ग_लिखो(काष्ठा snd_pmac *chip, पूर्णांक val)
अणु
	दीर्घ समयout = 5000000;

	अगर (chip->model == PMAC_SCREAMER)
		snd_pmac_screamer_रुको(chip);
	out_le32(&chip->awacs->codec_ctrl, val | (chip->subframe << 22));
	जबतक (in_le32(&chip->awacs->codec_ctrl) & MASK_NEWECMD) अणु
		अगर (! --समयout) अणु
			snd_prपूर्णांकd("snd_pmac_awacs_write timeout\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
snd_pmac_awacs_ग_लिखो_reg(काष्ठा snd_pmac *chip, पूर्णांक reg, पूर्णांक val)
अणु
	snd_pmac_awacs_ग_लिखो(chip, val | (reg << 12));
	chip->awacs_reg[reg] = val;
पूर्ण

अटल व्योम
snd_pmac_awacs_ग_लिखो_noreg(काष्ठा snd_pmac *chip, पूर्णांक reg, पूर्णांक val)
अणु
	snd_pmac_awacs_ग_लिखो(chip, val | (reg << 12));
पूर्ण

#अगर_घोषित CONFIG_PM
/* Recalibrate chip */
अटल व्योम screamer_recalibrate(काष्ठा snd_pmac *chip)
अणु
	अगर (chip->model != PMAC_SCREAMER)
		वापस;

	/* Sorry क्रम the horrible delays... I hope to get that improved
	 * by making the whole PM process asynchronous in a future version
	 */
	snd_pmac_awacs_ग_लिखो_noreg(chip, 1, chip->awacs_reg[1]);
	अगर (chip->manufacturer == 0x1)
		/* delay क्रम broken crystal part */
		msleep(750);
	snd_pmac_awacs_ग_लिखो_noreg(chip, 1,
				   chip->awacs_reg[1] | MASK_RECALIBRATE |
				   MASK_CMUTE | MASK_AMUTE);
	snd_pmac_awacs_ग_लिखो_noreg(chip, 1, chip->awacs_reg[1]);
	snd_pmac_awacs_ग_लिखो_noreg(chip, 6, chip->awacs_reg[6]);
पूर्ण

#अन्यथा
#घोषणा screamer_recalibrate(chip) /* NOP */
#पूर्ण_अगर


/*
 * additional callback to set the pcm क्रमmat
 */
अटल व्योम snd_pmac_awacs_set_क्रमmat(काष्ठा snd_pmac *chip)
अणु
	chip->awacs_reg[1] &= ~MASK_SAMPLERATE;
	chip->awacs_reg[1] |= chip->rate_index << 3;
	snd_pmac_awacs_ग_लिखो_reg(chip, 1, chip->awacs_reg[1]);
पूर्ण


/*
 * AWACS volume callbacks
 */
/*
 * volumes: 0-15 stereo
 */
अटल पूर्णांक snd_pmac_awacs_info_volume(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 15;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_awacs_get_volume(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक lshअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक inverted = (kcontrol->निजी_value >> 16) & 1;
	अचिन्हित दीर्घ flags;
	पूर्णांक vol[2];

	spin_lock_irqsave(&chip->reg_lock, flags);
	vol[0] = (chip->awacs_reg[reg] >> lshअगरt) & 0xf;
	vol[1] = chip->awacs_reg[reg] & 0xf;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (inverted) अणु
		vol[0] = 0x0f - vol[0];
		vol[1] = 0x0f - vol[1];
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = vol[0];
	ucontrol->value.पूर्णांकeger.value[1] = vol[1];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_awacs_put_volume(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक lshअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक inverted = (kcontrol->निजी_value >> 16) & 1;
	पूर्णांक val, oldval;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक vol[2];

	vol[0] = ucontrol->value.पूर्णांकeger.value[0];
	vol[1] = ucontrol->value.पूर्णांकeger.value[1];
	अगर (vol[0] > 0x0f || vol[1] > 0x0f)
		वापस -EINVAL;
	अगर (inverted) अणु
		vol[0] = 0x0f - vol[0];
		vol[1] = 0x0f - vol[1];
	पूर्ण
	vol[0] &= 0x0f;
	vol[1] &= 0x0f;
	spin_lock_irqsave(&chip->reg_lock, flags);
	oldval = chip->awacs_reg[reg];
	val = oldval & ~(0xf | (0xf << lshअगरt));
	val |= vol[0] << lshअगरt;
	val |= vol[1];
	अगर (oldval != val)
		snd_pmac_awacs_ग_लिखो_reg(chip, reg, val);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस oldval != reg;
पूर्ण


#घोषणा AWACS_VOLUME(xname, xreg, xshअगरt, xinverted) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = 0, \
  .info = snd_pmac_awacs_info_volume, \
  .get = snd_pmac_awacs_get_volume, \
  .put = snd_pmac_awacs_put_volume, \
  .निजी_value = (xreg) | ((xshअगरt) << 8) | ((xinverted) << 16) पूर्ण

/*
 * mute master/ogain क्रम AWACS: mono
 */
अटल पूर्णांक snd_pmac_awacs_get_चयन(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 16) & 1;
	पूर्णांक val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	val = (chip->awacs_reg[reg] >> shअगरt) & 1;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (invert)
		val = 1 - val;
	ucontrol->value.पूर्णांकeger.value[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_awacs_put_चयन(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 16) & 1;
	पूर्णांक mask = 1 << shअगरt;
	पूर्णांक val, changed;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	val = chip->awacs_reg[reg] & ~mask;
	अगर (ucontrol->value.पूर्णांकeger.value[0] != invert)
		val |= mask;
	changed = chip->awacs_reg[reg] != val;
	अगर (changed)
		snd_pmac_awacs_ग_लिखो_reg(chip, reg, val);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस changed;
पूर्ण

#घोषणा AWACS_SWITCH(xname, xreg, xshअगरt, xinvert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = 0, \
  .info = snd_pmac_boolean_mono_info, \
  .get = snd_pmac_awacs_get_चयन, \
  .put = snd_pmac_awacs_put_चयन, \
  .निजी_value = (xreg) | ((xshअगरt) << 8) | ((xinvert) << 16) पूर्ण


#अगर_घोषित PMAC_AMP_AVAIL
/*
 * controls क्रम perch/whisper extension cards, e.g. G3 desktop
 *
 * TDA7433 connected via i2c address 0x45 (= 0x8a),
 * accessed through cuda
 */
अटल व्योम awacs_set_cuda(पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा adb_request req;
	cuda_request(&req, शून्य, 5, CUDA_PACKET, CUDA_GET_SET_IIC, 0x8a,
			reg, val);
	जबतक (! req.complete)
		cuda_poll();
पूर्ण

/*
 * level = 0 - 14, 7 = 0 dB
 */
अटल व्योम awacs_amp_set_tone(काष्ठा awacs_amp *amp, पूर्णांक bass, पूर्णांक treble)
अणु
	amp->amp_tone[0] = bass;
	amp->amp_tone[1] = treble;
	अगर (bass > 7)
		bass = (14 - bass) + 8;
	अगर (treble > 7)
		treble = (14 - treble) + 8;
	awacs_set_cuda(2, (bass << 4) | treble);
पूर्ण

/*
 * vol = 0 - 31 (attenuation), 32 = mute bit, stereo
 */
अटल पूर्णांक awacs_amp_set_vol(काष्ठा awacs_amp *amp, पूर्णांक index,
			     पूर्णांक lvol, पूर्णांक rvol, पूर्णांक करो_check)
अणु
	अगर (करो_check && amp->amp_vol[index][0] == lvol &&
			amp->amp_vol[index][1] == rvol)
		वापस 0;
	awacs_set_cuda(3 + index, lvol);
	awacs_set_cuda(5 + index, rvol);
	amp->amp_vol[index][0] = lvol;
	amp->amp_vol[index][1] = rvol;
	वापस 1;
पूर्ण

/*
 * 0 = -79 dB, 79 = 0 dB, 99 = +20 dB
 */
अटल व्योम awacs_amp_set_master(काष्ठा awacs_amp *amp, पूर्णांक vol)
अणु
	amp->amp_master = vol;
	अगर (vol <= 79)
		vol = 32 + (79 - vol);
	अन्यथा
		vol = 32 - (vol - 79);
	awacs_set_cuda(1, vol);
पूर्ण

अटल व्योम awacs_amp_मुक्त(काष्ठा snd_pmac *chip)
अणु
	काष्ठा awacs_amp *amp = chip->mixer_data;
	अगर (!amp)
		वापस;
	kमुक्त(amp);
	chip->mixer_data = शून्य;
	chip->mixer_मुक्त = शून्य;
पूर्ण


/*
 * mixer controls
 */
अटल पूर्णांक snd_pmac_awacs_info_volume_amp(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 31;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_awacs_get_volume_amp(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक index = kcontrol->निजी_value;
	काष्ठा awacs_amp *amp = chip->mixer_data;

	ucontrol->value.पूर्णांकeger.value[0] = 31 - (amp->amp_vol[index][0] & 31);
	ucontrol->value.पूर्णांकeger.value[1] = 31 - (amp->amp_vol[index][1] & 31);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_awacs_put_volume_amp(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक index = kcontrol->निजी_value;
	पूर्णांक vol[2];
	काष्ठा awacs_amp *amp = chip->mixer_data;

	vol[0] = (31 - (ucontrol->value.पूर्णांकeger.value[0] & 31))
		| (amp->amp_vol[index][0] & 32);
	vol[1] = (31 - (ucontrol->value.पूर्णांकeger.value[1] & 31))
		| (amp->amp_vol[index][1] & 32);
	वापस awacs_amp_set_vol(amp, index, vol[0], vol[1], 1);
पूर्ण

अटल पूर्णांक snd_pmac_awacs_get_चयन_amp(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक index = kcontrol->निजी_value;
	काष्ठा awacs_amp *amp = chip->mixer_data;

	ucontrol->value.पूर्णांकeger.value[0] = (amp->amp_vol[index][0] & 32)
					? 0 : 1;
	ucontrol->value.पूर्णांकeger.value[1] = (amp->amp_vol[index][1] & 32)
					? 0 : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_awacs_put_चयन_amp(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक index = kcontrol->निजी_value;
	पूर्णांक vol[2];
	काष्ठा awacs_amp *amp = chip->mixer_data;

	vol[0] = (ucontrol->value.पूर्णांकeger.value[0] ? 0 : 32)
		| (amp->amp_vol[index][0] & 31);
	vol[1] = (ucontrol->value.पूर्णांकeger.value[1] ? 0 : 32)
		| (amp->amp_vol[index][1] & 31);
	वापस awacs_amp_set_vol(amp, index, vol[0], vol[1], 1);
पूर्ण

अटल पूर्णांक snd_pmac_awacs_info_tone_amp(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 14;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_awacs_get_tone_amp(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक index = kcontrol->निजी_value;
	काष्ठा awacs_amp *amp = chip->mixer_data;

	ucontrol->value.पूर्णांकeger.value[0] = amp->amp_tone[index];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_awacs_put_tone_amp(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक index = kcontrol->निजी_value;
	काष्ठा awacs_amp *amp = chip->mixer_data;
	अचिन्हित पूर्णांक val;

	val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (val > 14)
		वापस -EINVAL;
	अगर (val != amp->amp_tone[index]) अणु
		amp->amp_tone[index] = val;
		awacs_amp_set_tone(amp, amp->amp_tone[0], amp->amp_tone[1]);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_awacs_info_master_amp(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 99;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_awacs_get_master_amp(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा awacs_amp *amp = chip->mixer_data;

	ucontrol->value.पूर्णांकeger.value[0] = amp->amp_master;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_awacs_put_master_amp(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा awacs_amp *amp = chip->mixer_data;
	अचिन्हित पूर्णांक val;

	val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (val > 99)
		वापस -EINVAL;
	अगर (val != amp->amp_master) अणु
		amp->amp_master = val;
		awacs_amp_set_master(amp, amp->amp_master);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा AMP_CH_SPK	0
#घोषणा AMP_CH_HD	1

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_amp_vol[] = अणु
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Speaker Playback Volume",
	  .info = snd_pmac_awacs_info_volume_amp,
	  .get = snd_pmac_awacs_get_volume_amp,
	  .put = snd_pmac_awacs_put_volume_amp,
	  .निजी_value = AMP_CH_SPK,
	पूर्ण,
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Headphone Playback Volume",
	  .info = snd_pmac_awacs_info_volume_amp,
	  .get = snd_pmac_awacs_get_volume_amp,
	  .put = snd_pmac_awacs_put_volume_amp,
	  .निजी_value = AMP_CH_HD,
	पूर्ण,
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Tone Control - Bass",
	  .info = snd_pmac_awacs_info_tone_amp,
	  .get = snd_pmac_awacs_get_tone_amp,
	  .put = snd_pmac_awacs_put_tone_amp,
	  .निजी_value = 0,
	पूर्ण,
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Tone Control - Treble",
	  .info = snd_pmac_awacs_info_tone_amp,
	  .get = snd_pmac_awacs_get_tone_amp,
	  .put = snd_pmac_awacs_put_tone_amp,
	  .निजी_value = 1,
	पूर्ण,
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Amp Master Playback Volume",
	  .info = snd_pmac_awacs_info_master_amp,
	  .get = snd_pmac_awacs_get_master_amp,
	  .put = snd_pmac_awacs_put_master_amp,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_amp_hp_sw = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Headphone Playback Switch",
	.info = snd_pmac_boolean_stereo_info,
	.get = snd_pmac_awacs_get_चयन_amp,
	.put = snd_pmac_awacs_put_चयन_amp,
	.निजी_value = AMP_CH_HD,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_amp_spk_sw = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Speaker Playback Switch",
	.info = snd_pmac_boolean_stereo_info,
	.get = snd_pmac_awacs_get_चयन_amp,
	.put = snd_pmac_awacs_put_चयन_amp,
	.निजी_value = AMP_CH_SPK,
पूर्ण;

#पूर्ण_अगर /* PMAC_AMP_AVAIL */


/*
 * mic boost क्रम screamer
 */
अटल पूर्णांक snd_pmac_screamer_mic_boost_info(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 3;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_screamer_mic_boost_get(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक val = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (chip->awacs_reg[6] & MASK_MIC_BOOST)
		val |= 2;
	अगर (chip->awacs_reg[0] & MASK_GAINLINE)
		val |= 1;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_screamer_mic_boost_put(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक val0, val6;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	val0 = chip->awacs_reg[0] & ~MASK_GAINLINE;
	val6 = chip->awacs_reg[6] & ~MASK_MIC_BOOST;
	अगर (ucontrol->value.पूर्णांकeger.value[0] & 1)
		val0 |= MASK_GAINLINE;
	अगर (ucontrol->value.पूर्णांकeger.value[0] & 2)
		val6 |= MASK_MIC_BOOST;
	अगर (val0 != chip->awacs_reg[0]) अणु
		snd_pmac_awacs_ग_लिखो_reg(chip, 0, val0);
		changed = 1;
	पूर्ण
	अगर (val6 != chip->awacs_reg[6]) अणु
		snd_pmac_awacs_ग_लिखो_reg(chip, 6, val6);
		changed = 1;
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस changed;
पूर्ण

/*
 * lists of mixer elements
 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_mixers[] = अणु
	AWACS_SWITCH("Master Capture Switch", 1, SHIFT_LOOPTHRU, 0),
	AWACS_VOLUME("Master Capture Volume", 0, 4, 0),
/*	AWACS_SWITCH("Unknown Playback Switch", 6, SHIFT_PAROUT0, 0), */
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_screamer_mixers_beige[] = अणु
	AWACS_VOLUME("Master Playback Volume", 2, 6, 1),
	AWACS_VOLUME("Play-through Playback Volume", 5, 6, 1),
	AWACS_SWITCH("Line Capture Switch", 0, SHIFT_MUX_MIC, 0),
	AWACS_SWITCH("CD Capture Switch", 0, SHIFT_MUX_LINE, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_screamer_mixers_lo[] = अणु
	AWACS_VOLUME("Line out Playback Volume", 2, 6, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_screamer_mixers_imac[] = अणु
	AWACS_VOLUME("Play-through Playback Volume", 5, 6, 1),
	AWACS_SWITCH("CD Capture Switch", 0, SHIFT_MUX_CD, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_screamer_mixers_g4agp[] = अणु
	AWACS_VOLUME("Line out Playback Volume", 2, 6, 1),
	AWACS_VOLUME("Master Playback Volume", 5, 6, 1),
	AWACS_SWITCH("CD Capture Switch", 0, SHIFT_MUX_CD, 0),
	AWACS_SWITCH("Line Capture Switch", 0, SHIFT_MUX_MIC, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_mixers_pmac7500[] = अणु
	AWACS_VOLUME("Line out Playback Volume", 2, 6, 1),
	AWACS_SWITCH("CD Capture Switch", 0, SHIFT_MUX_CD, 0),
	AWACS_SWITCH("Line Capture Switch", 0, SHIFT_MUX_MIC, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_mixers_pmac5500[] = अणु
	AWACS_VOLUME("Headphone Playback Volume", 2, 6, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_mixers_pmac[] = अणु
	AWACS_VOLUME("Master Playback Volume", 2, 6, 1),
	AWACS_SWITCH("CD Capture Switch", 0, SHIFT_MUX_CD, 0),
पूर्ण;

/* FIXME: is this correct order?
 * screamer (घातerbook G3 pismo) seems to have dअगरferent bits...
 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_mixers2[] = अणु
	AWACS_SWITCH("Line Capture Switch", 0, SHIFT_MUX_LINE, 0),
	AWACS_SWITCH("Mic Capture Switch", 0, SHIFT_MUX_MIC, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_screamer_mixers2[] = अणु
	AWACS_SWITCH("Line Capture Switch", 0, SHIFT_MUX_MIC, 0),
	AWACS_SWITCH("Mic Capture Switch", 0, SHIFT_MUX_LINE, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_mixers2_pmac5500[] = अणु
	AWACS_SWITCH("CD Capture Switch", 0, SHIFT_MUX_CD, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_master_sw =
AWACS_SWITCH("Master Playback Switch", 1, SHIFT_HDMUTE, 1);

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_master_sw_imac =
AWACS_SWITCH("Line out Playback Switch", 1, SHIFT_HDMUTE, 1);

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_master_sw_pmac5500 =
AWACS_SWITCH("Headphone Playback Switch", 1, SHIFT_HDMUTE, 1);

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_mic_boost[] = अणु
	AWACS_SWITCH("Mic Boost Capture Switch", 0, SHIFT_GAINLINE, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_screamer_mic_boost[] = अणु
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Mic Boost Capture Volume",
	  .info = snd_pmac_screamer_mic_boost_info,
	  .get = snd_pmac_screamer_mic_boost_get,
	  .put = snd_pmac_screamer_mic_boost_put,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_mic_boost_pmac7500[] =
अणु
	AWACS_SWITCH("Line Boost Capture Switch", 0, SHIFT_GAINLINE, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_screamer_mic_boost_beige[] =
अणु
	AWACS_SWITCH("Line Boost Capture Switch", 0, SHIFT_GAINLINE, 0),
	AWACS_SWITCH("CD Boost Capture Switch", 6, SHIFT_MIC_BOOST, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_screamer_mic_boost_imac[] =
अणु
	AWACS_SWITCH("Line Boost Capture Switch", 0, SHIFT_GAINLINE, 0),
	AWACS_SWITCH("Mic Boost Capture Switch", 6, SHIFT_MIC_BOOST, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_speaker_vol[] = अणु
	AWACS_VOLUME("Speaker Playback Volume", 4, 6, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_speaker_sw =
AWACS_SWITCH("Speaker Playback Switch", 1, SHIFT_SPKMUTE, 1);

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_speaker_sw_imac1 =
AWACS_SWITCH("Speaker Playback Switch", 1, SHIFT_PAROUT1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_awacs_speaker_sw_imac2 =
AWACS_SWITCH("Speaker Playback Switch", 1, SHIFT_PAROUT1, 0);


/*
 * add new mixer elements to the card
 */
अटल पूर्णांक build_mixers(काष्ठा snd_pmac *chip, पूर्णांक nums,
			स्थिर काष्ठा snd_kcontrol_new *mixers)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < nums; i++) अणु
		err = snd_ctl_add(chip->card, snd_ctl_new1(&mixers[i], chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * restore all रेजिस्टरs
 */
अटल व्योम awacs_restore_all_regs(काष्ठा snd_pmac *chip)
अणु
	snd_pmac_awacs_ग_लिखो_noreg(chip, 0, chip->awacs_reg[0]);
	snd_pmac_awacs_ग_लिखो_noreg(chip, 1, chip->awacs_reg[1]);
	snd_pmac_awacs_ग_लिखो_noreg(chip, 2, chip->awacs_reg[2]);
	snd_pmac_awacs_ग_लिखो_noreg(chip, 4, chip->awacs_reg[4]);
	अगर (chip->model == PMAC_SCREAMER) अणु
		snd_pmac_awacs_ग_लिखो_noreg(chip, 5, chip->awacs_reg[5]);
		snd_pmac_awacs_ग_लिखो_noreg(chip, 6, chip->awacs_reg[6]);
		snd_pmac_awacs_ग_लिखो_noreg(chip, 7, chip->awacs_reg[7]);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम snd_pmac_awacs_suspend(काष्ठा snd_pmac *chip)
अणु
	snd_pmac_awacs_ग_लिखो_noreg(chip, 1, (chip->awacs_reg[1]
					     | MASK_AMUTE | MASK_CMUTE));
पूर्ण

अटल व्योम snd_pmac_awacs_resume(काष्ठा snd_pmac *chip)
अणु
	अगर (of_machine_is_compatible("PowerBook3,1")
	    || of_machine_is_compatible("PowerBook3,2")) अणु
		msleep(100);
		snd_pmac_awacs_ग_लिखो_reg(chip, 1,
			chip->awacs_reg[1] & ~MASK_PAROUT);
		msleep(300);
	पूर्ण

	awacs_restore_all_regs(chip);
	अगर (chip->model == PMAC_SCREAMER) अणु
		/* reset घातer bits in reg 6 */
		mdelay(5);
		snd_pmac_awacs_ग_लिखो_noreg(chip, 6, chip->awacs_reg[6]);
	पूर्ण
	screamer_recalibrate(chip);
#अगर_घोषित PMAC_AMP_AVAIL
	अगर (chip->mixer_data) अणु
		काष्ठा awacs_amp *amp = chip->mixer_data;
		awacs_amp_set_vol(amp, 0,
				  amp->amp_vol[0][0], amp->amp_vol[0][1], 0);
		awacs_amp_set_vol(amp, 1,
				  amp->amp_vol[1][0], amp->amp_vol[1][1], 0);
		awacs_amp_set_tone(amp, amp->amp_tone[0], amp->amp_tone[1]);
		awacs_amp_set_master(amp, amp->amp_master);
	पूर्ण
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

#घोषणा IS_PM7500 (of_machine_is_compatible("AAPL,7500") \
		|| of_machine_is_compatible("AAPL,8500") \
		|| of_machine_is_compatible("AAPL,9500"))
#घोषणा IS_PM5500 (of_machine_is_compatible("AAPL,e411"))
#घोषणा IS_BEIGE (of_machine_is_compatible("AAPL,Gossamer"))
#घोषणा IS_IMAC1 (of_machine_is_compatible("PowerMac2,1"))
#घोषणा IS_IMAC2 (of_machine_is_compatible("PowerMac2,2") \
		|| of_machine_is_compatible("PowerMac4,1"))
#घोषणा IS_G4AGP (of_machine_is_compatible("PowerMac3,1"))
#घोषणा IS_LOMBARD (of_machine_is_compatible("PowerBook1,1"))

अटल पूर्णांक imac1, imac2;

#अगर_घोषित PMAC_SUPPORT_AUTOMUTE
/*
 * स्वतः-mute stuffs
 */
अटल पूर्णांक snd_pmac_awacs_detect_headphone(काष्ठा snd_pmac *chip)
अणु
	वापस (in_le32(&chip->awacs->codec_stat) & chip->hp_stat_mask) ? 1 : 0;
पूर्ण

#अगर_घोषित PMAC_AMP_AVAIL
अटल पूर्णांक toggle_amp_mute(काष्ठा awacs_amp *amp, पूर्णांक index, पूर्णांक mute)
अणु
	पूर्णांक vol[2];
	vol[0] = amp->amp_vol[index][0] & 31;
	vol[1] = amp->amp_vol[index][1] & 31;
	अगर (mute) अणु
		vol[0] |= 32;
		vol[1] |= 32;
	पूर्ण
	वापस awacs_amp_set_vol(amp, index, vol[0], vol[1], 1);
पूर्ण
#पूर्ण_अगर

अटल व्योम snd_pmac_awacs_update_स्वतःmute(काष्ठा snd_pmac *chip, पूर्णांक करो_notअगरy)
अणु
	अगर (chip->स्वतः_mute) अणु
#अगर_घोषित PMAC_AMP_AVAIL
		अगर (chip->mixer_data) अणु
			काष्ठा awacs_amp *amp = chip->mixer_data;
			पूर्णांक changed;
			अगर (snd_pmac_awacs_detect_headphone(chip)) अणु
				changed = toggle_amp_mute(amp, AMP_CH_HD, 0);
				changed |= toggle_amp_mute(amp, AMP_CH_SPK, 1);
			पूर्ण अन्यथा अणु
				changed = toggle_amp_mute(amp, AMP_CH_HD, 1);
				changed |= toggle_amp_mute(amp, AMP_CH_SPK, 0);
			पूर्ण
			अगर (करो_notअगरy && ! changed)
				वापस;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			पूर्णांक reg = chip->awacs_reg[1]
				| (MASK_HDMUTE | MASK_SPKMUTE);
			अगर (imac1) अणु
				reg &= ~MASK_SPKMUTE;
				reg |= MASK_PAROUT1;
			पूर्ण अन्यथा अगर (imac2) अणु
				reg &= ~MASK_SPKMUTE;
				reg &= ~MASK_PAROUT1;
			पूर्ण
			अगर (snd_pmac_awacs_detect_headphone(chip))
				reg &= ~MASK_HDMUTE;
			अन्यथा अगर (imac1)
				reg &= ~MASK_PAROUT1;
			अन्यथा अगर (imac2)
				reg |= MASK_PAROUT1;
			अन्यथा
				reg &= ~MASK_SPKMUTE;
			अगर (करो_notअगरy && reg == chip->awacs_reg[1])
				वापस;
			snd_pmac_awacs_ग_लिखो_reg(chip, 1, reg);
		पूर्ण
		अगर (करो_notअगरy) अणु
			snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->master_sw_ctl->id);
			snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->speaker_sw_ctl->id);
			snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->hp_detect_ctl->id);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* PMAC_SUPPORT_AUTOMUTE */


/*
 * initialize chip
 */
पूर्णांक
snd_pmac_awacs_init(काष्ठा snd_pmac *chip)
अणु
	पूर्णांक pm7500 = IS_PM7500;
	पूर्णांक pm5500 = IS_PM5500;
	पूर्णांक beige = IS_BEIGE;
	पूर्णांक g4agp = IS_G4AGP;
	पूर्णांक lombard = IS_LOMBARD;
	पूर्णांक imac;
	पूर्णांक err, vol;
	काष्ठा snd_kcontrol *vmaster_sw, *vmaster_vol;
	काष्ठा snd_kcontrol *master_vol, *speaker_vol;

	imac1 = IS_IMAC1;
	imac2 = IS_IMAC2;
	imac = imac1 || imac2;
	/* looks like MASK_GAINLINE triggers something, so we set here
	 * as start-up
	 */
	chip->awacs_reg[0] = MASK_MUX_CD | 0xff | MASK_GAINLINE;
	chip->awacs_reg[1] = MASK_CMUTE | MASK_AMUTE;
	/* FIXME: Only machines with बाह्यal SRS module need MASK_PAROUT */
	अगर (chip->has_iic || chip->device_id == 0x5 ||
	    /* chip->_device_id == 0x8 || */
	    chip->device_id == 0xb)
		chip->awacs_reg[1] |= MASK_PAROUT;
	/* get शेष volume from nvram */
	// vol = (~nvram_पढ़ो_byte(0x1308) & 7) << 1;
	// vol = ((pmac_xpram_पढ़ो( 8 ) & 7 ) << 1 );
	vol = 0x0f; /* no, on alsa, muted as शेष */
	vol = vol + (vol << 6);
	chip->awacs_reg[2] = vol;
	chip->awacs_reg[4] = vol;
	अगर (chip->model == PMAC_SCREAMER) अणु
		/* FIXME: screamer has loopthru vol control */
		chip->awacs_reg[5] = vol;
		/* FIXME: maybe should be vol << 3 क्रम PCMCIA speaker */
		chip->awacs_reg[6] = MASK_MIC_BOOST;
		chip->awacs_reg[7] = 0;
	पूर्ण

	awacs_restore_all_regs(chip);
	chip->manufacturer = (in_le32(&chip->awacs->codec_stat) >> 8) & 0xf;
	screamer_recalibrate(chip);

	chip->revision = (in_le32(&chip->awacs->codec_stat) >> 12) & 0xf;
#अगर_घोषित PMAC_AMP_AVAIL
	अगर (chip->revision == 3 && chip->has_iic && CHECK_CUDA_AMP()) अणु
		काष्ठा awacs_amp *amp = kzalloc(माप(*amp), GFP_KERNEL);
		अगर (! amp)
			वापस -ENOMEM;
		chip->mixer_data = amp;
		chip->mixer_मुक्त = awacs_amp_मुक्त;
		/* mute and zero vol */
		awacs_amp_set_vol(amp, 0, 63, 63, 0);
		awacs_amp_set_vol(amp, 1, 63, 63, 0);
		awacs_amp_set_tone(amp, 7, 7); /* 0 dB */
		awacs_amp_set_master(amp, 79); /* 0 dB */
	पूर्ण
#पूर्ण_अगर /* PMAC_AMP_AVAIL */

	अगर (chip->hp_stat_mask == 0) अणु
		/* set headphone-jack detection bit */
		चयन (chip->model) अणु
		हाल PMAC_AWACS:
			chip->hp_stat_mask = pm7500 || pm5500 ? MASK_HDPCONN
				: MASK_LOCONN;
			अवरोध;
		हाल PMAC_SCREAMER:
			चयन (chip->device_id) अणु
			हाल 0x08:
			हाल 0x0B:
				chip->hp_stat_mask = imac
					? MASK_LOCONN_IMAC |
					MASK_HDPLCONN_IMAC |
					MASK_HDPRCONN_IMAC
					: MASK_HDPCONN;
				अवरोध;
			हाल 0x00:
			हाल 0x05:
				chip->hp_stat_mask = MASK_LOCONN;
				अवरोध;
			शेष:
				chip->hp_stat_mask = MASK_HDPCONN;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			snd_BUG();
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * build mixers
	 */
	म_नकल(chip->card->mixername, "PowerMac AWACS");

	err = build_mixers(chip, ARRAY_SIZE(snd_pmac_awacs_mixers),
				snd_pmac_awacs_mixers);
	अगर (err < 0)
		वापस err;
	अगर (beige || g4agp)
		;
	अन्यथा अगर (chip->model == PMAC_SCREAMER || pm5500)
		err = build_mixers(chip, ARRAY_SIZE(snd_pmac_screamer_mixers2),
				   snd_pmac_screamer_mixers2);
	अन्यथा अगर (!pm7500)
		err = build_mixers(chip, ARRAY_SIZE(snd_pmac_awacs_mixers2),
				   snd_pmac_awacs_mixers2);
	अगर (err < 0)
		वापस err;
	अगर (pm5500) अणु
		err = build_mixers(chip,
				   ARRAY_SIZE(snd_pmac_awacs_mixers2_pmac5500),
				   snd_pmac_awacs_mixers2_pmac5500);
		अगर (err < 0)
			वापस err;
	पूर्ण
	master_vol = शून्य;
	अगर (pm7500)
		err = build_mixers(chip,
				   ARRAY_SIZE(snd_pmac_awacs_mixers_pmac7500),
				   snd_pmac_awacs_mixers_pmac7500);
	अन्यथा अगर (pm5500)
		err = snd_ctl_add(chip->card,
		    (master_vol = snd_ctl_new1(snd_pmac_awacs_mixers_pmac5500,
						chip)));
	अन्यथा अगर (beige)
		err = build_mixers(chip,
				   ARRAY_SIZE(snd_pmac_screamer_mixers_beige),
				   snd_pmac_screamer_mixers_beige);
	अन्यथा अगर (imac || lombard) अणु
		err = snd_ctl_add(chip->card,
		    (master_vol = snd_ctl_new1(snd_pmac_screamer_mixers_lo,
						chip)));
		अगर (err < 0)
			वापस err;
		err = build_mixers(chip,
				   ARRAY_SIZE(snd_pmac_screamer_mixers_imac),
				   snd_pmac_screamer_mixers_imac);
	पूर्ण अन्यथा अगर (g4agp)
		err = build_mixers(chip,
				   ARRAY_SIZE(snd_pmac_screamer_mixers_g4agp),
				   snd_pmac_screamer_mixers_g4agp);
	अन्यथा
		err = build_mixers(chip,
				   ARRAY_SIZE(snd_pmac_awacs_mixers_pmac),
				   snd_pmac_awacs_mixers_pmac);
	अगर (err < 0)
		वापस err;
	chip->master_sw_ctl = snd_ctl_new1((pm7500 || imac || g4agp || lombard)
			? &snd_pmac_awacs_master_sw_imac
			: pm5500
			? &snd_pmac_awacs_master_sw_pmac5500
			: &snd_pmac_awacs_master_sw, chip);
	err = snd_ctl_add(chip->card, chip->master_sw_ctl);
	अगर (err < 0)
		वापस err;
#अगर_घोषित PMAC_AMP_AVAIL
	अगर (chip->mixer_data) अणु
		/* use amplअगरier.  the संकेत is connected from route A
		 * to the amp.  the amp has its headphone and speaker
		 * volumes and mute चयनes, so we use them instead of
		 * screamer रेजिस्टरs.
		 * in this हाल, it seems the route C is not used.
		 */
		err = build_mixers(chip, ARRAY_SIZE(snd_pmac_awacs_amp_vol),
					snd_pmac_awacs_amp_vol);
		अगर (err < 0)
			वापस err;
		/* overग_लिखो */
		chip->master_sw_ctl = snd_ctl_new1(&snd_pmac_awacs_amp_hp_sw,
							chip);
		err = snd_ctl_add(chip->card, chip->master_sw_ctl);
		अगर (err < 0)
			वापस err;
		chip->speaker_sw_ctl = snd_ctl_new1(&snd_pmac_awacs_amp_spk_sw,
							chip);
		err = snd_ctl_add(chip->card, chip->speaker_sw_ctl);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा
#पूर्ण_अगर /* PMAC_AMP_AVAIL */
	अणु
		/* route A = headphone, route C = speaker */
		err = snd_ctl_add(chip->card,
		    (speaker_vol = snd_ctl_new1(snd_pmac_awacs_speaker_vol,
						chip)));
		अगर (err < 0)
			वापस err;
		chip->speaker_sw_ctl = snd_ctl_new1(imac1
				? &snd_pmac_awacs_speaker_sw_imac1
				: imac2
				? &snd_pmac_awacs_speaker_sw_imac2
				: &snd_pmac_awacs_speaker_sw, chip);
		err = snd_ctl_add(chip->card, chip->speaker_sw_ctl);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (pm5500 || imac || lombard) अणु
		vmaster_sw = snd_ctl_make_भव_master(
			"Master Playback Switch", (अचिन्हित पूर्णांक *) शून्य);
		err = snd_ctl_add_follower_uncached(vmaster_sw,
						    chip->master_sw_ctl);
		अगर (err < 0)
			वापस err;
		err = snd_ctl_add_follower_uncached(vmaster_sw,
						    chip->speaker_sw_ctl);
		अगर (err < 0)
			वापस err;
		err = snd_ctl_add(chip->card, vmaster_sw);
		अगर (err < 0)
			वापस err;
		vmaster_vol = snd_ctl_make_भव_master(
			"Master Playback Volume", (अचिन्हित पूर्णांक *) शून्य);
		err = snd_ctl_add_follower(vmaster_vol, master_vol);
		अगर (err < 0)
			वापस err;
		err = snd_ctl_add_follower(vmaster_vol, speaker_vol);
		अगर (err < 0)
			वापस err;
		err = snd_ctl_add(chip->card, vmaster_vol);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (beige || g4agp)
		err = build_mixers(chip,
				ARRAY_SIZE(snd_pmac_screamer_mic_boost_beige),
				snd_pmac_screamer_mic_boost_beige);
	अन्यथा अगर (imac)
		err = build_mixers(chip,
				ARRAY_SIZE(snd_pmac_screamer_mic_boost_imac),
				snd_pmac_screamer_mic_boost_imac);
	अन्यथा अगर (chip->model == PMAC_SCREAMER)
		err = build_mixers(chip,
				ARRAY_SIZE(snd_pmac_screamer_mic_boost),
				snd_pmac_screamer_mic_boost);
	अन्यथा अगर (pm7500)
		err = build_mixers(chip,
				ARRAY_SIZE(snd_pmac_awacs_mic_boost_pmac7500),
				snd_pmac_awacs_mic_boost_pmac7500);
	अन्यथा
		err = build_mixers(chip, ARRAY_SIZE(snd_pmac_awacs_mic_boost),
				snd_pmac_awacs_mic_boost);
	अगर (err < 0)
		वापस err;

	/*
	 * set lowlevel callbacks
	 */
	chip->set_क्रमmat = snd_pmac_awacs_set_क्रमmat;
#अगर_घोषित CONFIG_PM
	chip->suspend = snd_pmac_awacs_suspend;
	chip->resume = snd_pmac_awacs_resume;
#पूर्ण_अगर
#अगर_घोषित PMAC_SUPPORT_AUTOMUTE
	err = snd_pmac_add_स्वतःmute(chip);
	अगर (err < 0)
		वापस err;
	chip->detect_headphone = snd_pmac_awacs_detect_headphone;
	chip->update_स्वतःmute = snd_pmac_awacs_update_स्वतःmute;
	snd_pmac_awacs_update_स्वतःmute(chip, 0); /* update the status only */
#पूर्ण_अगर
	अगर (chip->model == PMAC_SCREAMER) अणु
		snd_pmac_awacs_ग_लिखो_noreg(chip, 6, chip->awacs_reg[6]);
		snd_pmac_awacs_ग_लिखो_noreg(chip, 0, chip->awacs_reg[0]);
	पूर्ण

	वापस 0;
पूर्ण
