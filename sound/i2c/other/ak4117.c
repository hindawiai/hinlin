<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Routines क्रम control of the AK4117 via 4-wire serial पूर्णांकerface
 *  IEC958 (S/PDIF) receiver by Asahi Kasei
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ak4117.h>
#समावेश <sound/asoundef.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("AK4117 IEC958 (S/PDIF) receiver by Asahi Kasei");
MODULE_LICENSE("GPL");

#घोषणा AK4117_ADDR			0x00 /* fixed address */

अटल व्योम snd_ak4117_समयr(काष्ठा समयr_list *t);

अटल व्योम reg_ग_लिखो(काष्ठा ak4117 *ak4117, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	ak4117->ग_लिखो(ak4117->निजी_data, reg, val);
	अगर (reg < माप(ak4117->regmap))
		ak4117->regmap[reg] = val;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर reg_पढ़ो(काष्ठा ak4117 *ak4117, अचिन्हित अक्षर reg)
अणु
	वापस ak4117->पढ़ो(ak4117->निजी_data, reg);
पूर्ण

#अगर 0
अटल व्योम reg_dump(काष्ठा ak4117 *ak4117)
अणु
	पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG "AK4117 REG DUMP:\n");
	क्रम (i = 0; i < 0x1b; i++)
		prपूर्णांकk(KERN_DEBUG "reg[%02x] = %02x (%02x)\n", i, reg_पढ़ो(ak4117, i), i < माप(ak4117->regmap) ? ak4117->regmap[i] : 0);
पूर्ण
#पूर्ण_अगर

अटल व्योम snd_ak4117_मुक्त(काष्ठा ak4117 *chip)
अणु
	del_समयr_sync(&chip->समयr);
	kमुक्त(chip);
पूर्ण

अटल पूर्णांक snd_ak4117_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा ak4117 *chip = device->device_data;
	snd_ak4117_मुक्त(chip);
	वापस 0;
पूर्ण

पूर्णांक snd_ak4117_create(काष्ठा snd_card *card, ak4117_पढ़ो_t *पढ़ो, ak4117_ग_लिखो_t *ग_लिखो,
		      स्थिर अचिन्हित अक्षर pgm[5], व्योम *निजी_data, काष्ठा ak4117 **r_ak4117)
अणु
	काष्ठा ak4117 *chip;
	पूर्णांक err = 0;
	अचिन्हित अक्षर reg;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =     snd_ak4117_dev_मुक्त,
	पूर्ण;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;
	spin_lock_init(&chip->lock);
	chip->card = card;
	chip->पढ़ो = पढ़ो;
	chip->ग_लिखो = ग_लिखो;
	chip->निजी_data = निजी_data;
	समयr_setup(&chip->समयr, snd_ak4117_समयr, 0);

	क्रम (reg = 0; reg < 5; reg++)
		chip->regmap[reg] = pgm[reg];
	snd_ak4117_reinit(chip);

	chip->rcs0 = reg_पढ़ो(chip, AK4117_REG_RCS0) & ~(AK4117_QINT | AK4117_CINT | AK4117_STC);
	chip->rcs1 = reg_पढ़ो(chip, AK4117_REG_RCS1);
	chip->rcs2 = reg_पढ़ो(chip, AK4117_REG_RCS2);

	अगर ((err = snd_device_new(card, SNDRV_DEV_CODEC, chip, &ops)) < 0)
		जाओ __fail;

	अगर (r_ak4117)
		*r_ak4117 = chip;
	वापस 0;

      __fail:
	snd_ak4117_मुक्त(chip);
	वापस err;
पूर्ण

व्योम snd_ak4117_reg_ग_लिखो(काष्ठा ak4117 *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
	अगर (reg >= 5)
		वापस;
	reg_ग_लिखो(chip, reg, (chip->regmap[reg] & ~mask) | val);
पूर्ण

व्योम snd_ak4117_reinit(काष्ठा ak4117 *chip)
अणु
	अचिन्हित अक्षर old = chip->regmap[AK4117_REG_PWRDN], reg;

	del_समयr(&chip->समयr);
	chip->init = 1;
	/* bring the chip to reset state and घातerकरोwn state */
	reg_ग_लिखो(chip, AK4117_REG_PWRDN, 0);
	udelay(200);
	/* release reset, but leave घातerकरोwn */
	reg_ग_लिखो(chip, AK4117_REG_PWRDN, (old | AK4117_RST) & ~AK4117_PWN);
	udelay(200);
	क्रम (reg = 1; reg < 5; reg++)
		reg_ग_लिखो(chip, reg, chip->regmap[reg]);
	/* release घातerकरोwn, everything is initialized now */
	reg_ग_लिखो(chip, AK4117_REG_PWRDN, old | AK4117_RST | AK4117_PWN);
	chip->init = 0;
	mod_समयr(&chip->समयr, 1 + jअगरfies);
पूर्ण

अटल अचिन्हित पूर्णांक बाह्यal_rate(अचिन्हित अक्षर rcs1)
अणु
	चयन (rcs1 & (AK4117_FS0|AK4117_FS1|AK4117_FS2|AK4117_FS3)) अणु
	हाल AK4117_FS_32000HZ: वापस 32000;
	हाल AK4117_FS_44100HZ: वापस 44100;
	हाल AK4117_FS_48000HZ: वापस 48000;
	हाल AK4117_FS_88200HZ: वापस 88200;
	हाल AK4117_FS_96000HZ: वापस 96000;
	हाल AK4117_FS_176400HZ: वापस 176400;
	हाल AK4117_FS_192000HZ: वापस 192000;
	शेष:		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_ak4117_in_error_info(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = दीर्घ_उच्च;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_in_error_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4117 *chip = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&chip->lock);
	ucontrol->value.पूर्णांकeger.value[0] =
		       chip->errors[kcontrol->निजी_value];
	chip->errors[kcontrol->निजी_value] = 0;
	spin_unlock_irq(&chip->lock);
	वापस 0;
पूर्ण

#घोषणा snd_ak4117_in_bit_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ak4117_in_bit_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4117 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर reg = kcontrol->निजी_value & 0xff;
	अचिन्हित अक्षर bit = (kcontrol->निजी_value >> 8) & 0xff;
	अचिन्हित अक्षर inv = (kcontrol->निजी_value >> 31) & 1;

	ucontrol->value.पूर्णांकeger.value[0] = ((reg_पढ़ो(chip, reg) & (1 << bit)) ? 1 : 0) ^ inv;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_rx_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_rx_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4117 *chip = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = (chip->regmap[AK4117_REG_IO] & AK4117_IPS) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_rx_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4117 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	u8 old_val;
	
	spin_lock_irq(&chip->lock);
	old_val = chip->regmap[AK4117_REG_IO];
	change = !!ucontrol->value.पूर्णांकeger.value[0] != ((old_val & AK4117_IPS) ? 1 : 0);
	अगर (change)
		reg_ग_लिखो(chip, AK4117_REG_IO, (old_val & ~AK4117_IPS) | (ucontrol->value.पूर्णांकeger.value[0] ? AK4117_IPS : 0));
	spin_unlock_irq(&chip->lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_ak4117_rate_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 192000;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_rate_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4117 *chip = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = बाह्यal_rate(reg_पढ़ो(chip, AK4117_REG_RCS1));
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_spdअगर_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4117 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित i;

	क्रम (i = 0; i < AK4117_REG_RXCSB_SIZE; i++)
		ucontrol->value.iec958.status[i] = reg_पढ़ो(chip, AK4117_REG_RXCSB0 + i);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	स_रखो(ucontrol->value.iec958.status, 0xff, AK4117_REG_RXCSB_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_spdअगर_pinfo(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0xffff;
	uinfo->count = 4;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_spdअगर_pget(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4117 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु पंचांगp;

	ucontrol->value.पूर्णांकeger.value[0] = 0xf8f2;
	ucontrol->value.पूर्णांकeger.value[1] = 0x4e1f;
	पंचांगp = reg_पढ़ो(chip, AK4117_REG_Pc0) | (reg_पढ़ो(chip, AK4117_REG_Pc1) << 8);
	ucontrol->value.पूर्णांकeger.value[2] = पंचांगp;
	पंचांगp = reg_पढ़ो(chip, AK4117_REG_Pd0) | (reg_पढ़ो(chip, AK4117_REG_Pd1) << 8);
	ucontrol->value.पूर्णांकeger.value[3] = पंचांगp;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_spdअगर_qinfo(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = AK4117_REG_QSUB_SIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4117_spdअगर_qget(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4117 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित i;

	क्रम (i = 0; i < AK4117_REG_QSUB_SIZE; i++)
		ucontrol->value.bytes.data[i] = reg_पढ़ो(chip, AK4117_REG_QSUB_ADDR + i);
	वापस 0;
पूर्ण

/* Don't क्रमget to change AK4117_CONTROLS define!!! */
अटल स्थिर काष्ठा snd_kcontrol_new snd_ak4117_iec958_controls[] = अणु
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Parity Errors",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4117_in_error_info,
	.get =		snd_ak4117_in_error_get,
	.निजी_value = AK4117_PARITY_ERRORS,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 V-Bit Errors",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4117_in_error_info,
	.get =		snd_ak4117_in_error_get,
	.निजी_value = AK4117_V_BIT_ERRORS,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 C-CRC Errors",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4117_in_error_info,
	.get =		snd_ak4117_in_error_get,
	.निजी_value = AK4117_CCRC_ERRORS,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Q-CRC Errors",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4117_in_error_info,
	.get =		snd_ak4117_in_error_get,
	.निजी_value = AK4117_QCRC_ERRORS,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 External Rate",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4117_rate_info,
	.get =		snd_ak4117_rate_get,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",CAPTURE,MASK),
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.info =		snd_ak4117_spdअगर_mask_info,
	.get =		snd_ak4117_spdअगर_mask_get,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",CAPTURE,DEFAULT),
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4117_spdअगर_info,
	.get =		snd_ak4117_spdअगर_get,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Preamble Capture Default",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4117_spdअगर_pinfo,
	.get =		snd_ak4117_spdअगर_pget,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Q-subcode Capture Default",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4117_spdअगर_qinfo,
	.get =		snd_ak4117_spdअगर_qget,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Audio",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4117_in_bit_info,
	.get =		snd_ak4117_in_bit_get,
	.निजी_value = (1<<31) | (3<<8) | AK4117_REG_RCS0,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Non-PCM Bitstream",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4117_in_bit_info,
	.get =		snd_ak4117_in_bit_get,
	.निजी_value = (5<<8) | AK4117_REG_RCS1,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 DTS Bitstream",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4117_in_bit_info,
	.get =		snd_ak4117_in_bit_get,
	.निजी_value = (6<<8) | AK4117_REG_RCS1,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"AK4117 Input Select",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_WRITE,
	.info =		snd_ak4117_rx_info,
	.get =		snd_ak4117_rx_get,
	.put =		snd_ak4117_rx_put,
पूर्ण
पूर्ण;

पूर्णांक snd_ak4117_build(काष्ठा ak4117 *ak4117, काष्ठा snd_pcm_substream *cap_substream)
अणु
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	अगर (snd_BUG_ON(!cap_substream))
		वापस -EINVAL;
	ak4117->substream = cap_substream;
	क्रम (idx = 0; idx < AK4117_CONTROLS; idx++) अणु
		kctl = snd_ctl_new1(&snd_ak4117_iec958_controls[idx], ak4117);
		अगर (kctl == शून्य)
			वापस -ENOMEM;
		kctl->id.device = cap_substream->pcm->device;
		kctl->id.subdevice = cap_substream->number;
		err = snd_ctl_add(ak4117->card, kctl);
		अगर (err < 0)
			वापस err;
		ak4117->kctls[idx] = kctl;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक snd_ak4117_बाह्यal_rate(काष्ठा ak4117 *ak4117)
अणु
	अचिन्हित अक्षर rcs1;

	rcs1 = reg_पढ़ो(ak4117, AK4117_REG_RCS1);
	वापस बाह्यal_rate(rcs1);
पूर्ण

पूर्णांक snd_ak4117_check_rate_and_errors(काष्ठा ak4117 *ak4117, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = ak4117->substream ? ak4117->substream->runसमय : शून्य;
	अचिन्हित दीर्घ _flags;
	पूर्णांक res = 0;
	अचिन्हित अक्षर rcs0, rcs1, rcs2;
	अचिन्हित अक्षर c0, c1;

	rcs1 = reg_पढ़ो(ak4117, AK4117_REG_RCS1);
	अगर (flags & AK4117_CHECK_NO_STAT)
		जाओ __rate;
	rcs0 = reg_पढ़ो(ak4117, AK4117_REG_RCS0);
	rcs2 = reg_पढ़ो(ak4117, AK4117_REG_RCS2);
	// prपूर्णांकk(KERN_DEBUG "AK IRQ: rcs0 = 0x%x, rcs1 = 0x%x, rcs2 = 0x%x\n", rcs0, rcs1, rcs2);
	spin_lock_irqsave(&ak4117->lock, _flags);
	अगर (rcs0 & AK4117_PAR)
		ak4117->errors[AK4117_PARITY_ERRORS]++;
	अगर (rcs0 & AK4117_V)
		ak4117->errors[AK4117_V_BIT_ERRORS]++;
	अगर (rcs2 & AK4117_CCRC)
		ak4117->errors[AK4117_CCRC_ERRORS]++;
	अगर (rcs2 & AK4117_QCRC)
		ak4117->errors[AK4117_QCRC_ERRORS]++;
	c0 = (ak4117->rcs0 & (AK4117_QINT | AK4117_CINT | AK4117_STC | AK4117_AUDION | AK4117_AUTO | AK4117_UNLCK)) ^
                     (rcs0 & (AK4117_QINT | AK4117_CINT | AK4117_STC | AK4117_AUDION | AK4117_AUTO | AK4117_UNLCK));
	c1 = (ak4117->rcs1 & (AK4117_DTSCD | AK4117_NPCM | AK4117_PEM | 0x0f)) ^
	             (rcs1 & (AK4117_DTSCD | AK4117_NPCM | AK4117_PEM | 0x0f));
	ak4117->rcs0 = rcs0 & ~(AK4117_QINT | AK4117_CINT | AK4117_STC);
	ak4117->rcs1 = rcs1;
	ak4117->rcs2 = rcs2;
	spin_unlock_irqrestore(&ak4117->lock, _flags);

	अगर (rcs0 & AK4117_PAR)
		snd_ctl_notअगरy(ak4117->card, SNDRV_CTL_EVENT_MASK_VALUE, &ak4117->kctls[0]->id);
	अगर (rcs0 & AK4117_V)
		snd_ctl_notअगरy(ak4117->card, SNDRV_CTL_EVENT_MASK_VALUE, &ak4117->kctls[1]->id);
	अगर (rcs2 & AK4117_CCRC)
		snd_ctl_notअगरy(ak4117->card, SNDRV_CTL_EVENT_MASK_VALUE, &ak4117->kctls[2]->id);
	अगर (rcs2 & AK4117_QCRC)
		snd_ctl_notअगरy(ak4117->card, SNDRV_CTL_EVENT_MASK_VALUE, &ak4117->kctls[3]->id);

	/* rate change */
	अगर (c1 & 0x0f)
		snd_ctl_notअगरy(ak4117->card, SNDRV_CTL_EVENT_MASK_VALUE, &ak4117->kctls[4]->id);

	अगर ((c1 & AK4117_PEM) | (c0 & AK4117_CINT))
		snd_ctl_notअगरy(ak4117->card, SNDRV_CTL_EVENT_MASK_VALUE, &ak4117->kctls[6]->id);
	अगर (c0 & AK4117_QINT)
		snd_ctl_notअगरy(ak4117->card, SNDRV_CTL_EVENT_MASK_VALUE, &ak4117->kctls[8]->id);

	अगर (c0 & AK4117_AUDION)
		snd_ctl_notअगरy(ak4117->card, SNDRV_CTL_EVENT_MASK_VALUE, &ak4117->kctls[9]->id);
	अगर (c1 & AK4117_NPCM)
		snd_ctl_notअगरy(ak4117->card, SNDRV_CTL_EVENT_MASK_VALUE, &ak4117->kctls[10]->id);
	अगर (c1 & AK4117_DTSCD)
		snd_ctl_notअगरy(ak4117->card, SNDRV_CTL_EVENT_MASK_VALUE, &ak4117->kctls[11]->id);
		
	अगर (ak4117->change_callback && (c0 | c1) != 0)
		ak4117->change_callback(ak4117, c0, c1);

      __rate:
	/* compare rate */
	res = बाह्यal_rate(rcs1);
	अगर (!(flags & AK4117_CHECK_NO_RATE) && runसमय && runसमय->rate != res) अणु
		snd_pcm_stream_lock_irqsave(ak4117->substream, _flags);
		अगर (snd_pcm_running(ak4117->substream)) अणु
			// prपूर्णांकk(KERN_DEBUG "rate changed (%i <- %i)\n", runसमय->rate, res);
			snd_pcm_stop(ak4117->substream, SNDRV_PCM_STATE_DRAINING);
			wake_up(&runसमय->sleep);
			res = 1;
		पूर्ण
		snd_pcm_stream_unlock_irqrestore(ak4117->substream, _flags);
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम snd_ak4117_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ak4117 *chip = from_समयr(chip, t, समयr);

	अगर (chip->init)
		वापस;
	snd_ak4117_check_rate_and_errors(chip, 0);
	mod_समयr(&chip->समयr, 1 + jअगरfies);
पूर्ण

EXPORT_SYMBOL(snd_ak4117_create);
EXPORT_SYMBOL(snd_ak4117_reg_ग_लिखो);
EXPORT_SYMBOL(snd_ak4117_reinit);
EXPORT_SYMBOL(snd_ak4117_build);
EXPORT_SYMBOL(snd_ak4117_बाह्यal_rate);
EXPORT_SYMBOL(snd_ak4117_check_rate_and_errors);
