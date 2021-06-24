<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Routines क्रम control of the AK4114 via I2C and 4-wire serial पूर्णांकerface
 *  IEC958 (S/PDIF) receiver by Asahi Kasei
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ak4114.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/info.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("AK4114 IEC958 (S/PDIF) receiver by Asahi Kasei");
MODULE_LICENSE("GPL");

#घोषणा AK4114_ADDR			0x00 /* fixed address */

अटल व्योम ak4114_stats(काष्ठा work_काष्ठा *work);
अटल व्योम ak4114_init_regs(काष्ठा ak4114 *chip);

अटल व्योम reg_ग_लिखो(काष्ठा ak4114 *ak4114, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	ak4114->ग_लिखो(ak4114->निजी_data, reg, val);
	अगर (reg <= AK4114_REG_INT1_MASK)
		ak4114->regmap[reg] = val;
	अन्यथा अगर (reg >= AK4114_REG_TXCSB0 && reg <= AK4114_REG_TXCSB4)
		ak4114->txcsb[reg-AK4114_REG_TXCSB0] = val;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर reg_पढ़ो(काष्ठा ak4114 *ak4114, अचिन्हित अक्षर reg)
अणु
	वापस ak4114->पढ़ो(ak4114->निजी_data, reg);
पूर्ण

#अगर 0
अटल व्योम reg_dump(काष्ठा ak4114 *ak4114)
अणु
	पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG "AK4114 REG DUMP:\n");
	क्रम (i = 0; i < 0x20; i++)
		prपूर्णांकk(KERN_DEBUG "reg[%02x] = %02x (%02x)\n", i, reg_पढ़ो(ak4114, i), i < ARRAY_SIZE(ak4114->regmap) ? ak4114->regmap[i] : 0);
पूर्ण
#पूर्ण_अगर

अटल व्योम snd_ak4114_मुक्त(काष्ठा ak4114 *chip)
अणु
	atomic_inc(&chip->wq_processing);	/* करोn't schedule new work */
	cancel_delayed_work_sync(&chip->work);
	kमुक्त(chip);
पूर्ण

अटल पूर्णांक snd_ak4114_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा ak4114 *chip = device->device_data;
	snd_ak4114_मुक्त(chip);
	वापस 0;
पूर्ण

पूर्णांक snd_ak4114_create(काष्ठा snd_card *card,
		      ak4114_पढ़ो_t *पढ़ो, ak4114_ग_लिखो_t *ग_लिखो,
		      स्थिर अचिन्हित अक्षर pgm[6], स्थिर अचिन्हित अक्षर txcsb[5],
		      व्योम *निजी_data, काष्ठा ak4114 **r_ak4114)
अणु
	काष्ठा ak4114 *chip;
	पूर्णांक err = 0;
	अचिन्हित अक्षर reg;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =     snd_ak4114_dev_मुक्त,
	पूर्ण;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;
	spin_lock_init(&chip->lock);
	chip->card = card;
	chip->पढ़ो = पढ़ो;
	chip->ग_लिखो = ग_लिखो;
	chip->निजी_data = निजी_data;
	INIT_DELAYED_WORK(&chip->work, ak4114_stats);
	atomic_set(&chip->wq_processing, 0);
	mutex_init(&chip->reinit_mutex);

	क्रम (reg = 0; reg < 6; reg++)
		chip->regmap[reg] = pgm[reg];
	क्रम (reg = 0; reg < 5; reg++)
		chip->txcsb[reg] = txcsb[reg];

	ak4114_init_regs(chip);

	chip->rcs0 = reg_पढ़ो(chip, AK4114_REG_RCS0) & ~(AK4114_QINT | AK4114_CINT);
	chip->rcs1 = reg_पढ़ो(chip, AK4114_REG_RCS1);

	अगर ((err = snd_device_new(card, SNDRV_DEV_CODEC, chip, &ops)) < 0)
		जाओ __fail;

	अगर (r_ak4114)
		*r_ak4114 = chip;
	वापस 0;

      __fail:
	snd_ak4114_मुक्त(chip);
	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_ak4114_create);

व्योम snd_ak4114_reg_ग_लिखो(काष्ठा ak4114 *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
	अगर (reg <= AK4114_REG_INT1_MASK)
		reg_ग_लिखो(chip, reg, (chip->regmap[reg] & ~mask) | val);
	अन्यथा अगर (reg >= AK4114_REG_TXCSB0 && reg <= AK4114_REG_TXCSB4)
		reg_ग_लिखो(chip, reg,
			  (chip->txcsb[reg-AK4114_REG_TXCSB0] & ~mask) | val);
पूर्ण
EXPORT_SYMBOL(snd_ak4114_reg_ग_लिखो);

अटल व्योम ak4114_init_regs(काष्ठा ak4114 *chip)
अणु
	अचिन्हित अक्षर old = chip->regmap[AK4114_REG_PWRDN], reg;

	/* bring the chip to reset state and घातerकरोwn state */
	reg_ग_लिखो(chip, AK4114_REG_PWRDN, old & ~(AK4114_RST|AK4114_PWN));
	udelay(200);
	/* release reset, but leave घातerकरोwn */
	reg_ग_लिखो(chip, AK4114_REG_PWRDN, (old | AK4114_RST) & ~AK4114_PWN);
	udelay(200);
	क्रम (reg = 1; reg < 6; reg++)
		reg_ग_लिखो(chip, reg, chip->regmap[reg]);
	क्रम (reg = 0; reg < 5; reg++)
		reg_ग_लिखो(chip, reg + AK4114_REG_TXCSB0, chip->txcsb[reg]);
	/* release घातerकरोwn, everything is initialized now */
	reg_ग_लिखो(chip, AK4114_REG_PWRDN, old | AK4114_RST | AK4114_PWN);
पूर्ण

व्योम snd_ak4114_reinit(काष्ठा ak4114 *chip)
अणु
	अगर (atomic_inc_वापस(&chip->wq_processing) == 1)
		cancel_delayed_work_sync(&chip->work);
	mutex_lock(&chip->reinit_mutex);
	ak4114_init_regs(chip);
	mutex_unlock(&chip->reinit_mutex);
	/* bring up statistics / event queing */
	अगर (atomic_dec_and_test(&chip->wq_processing))
		schedule_delayed_work(&chip->work, HZ / 10);
पूर्ण
EXPORT_SYMBOL(snd_ak4114_reinit);

अटल अचिन्हित पूर्णांक बाह्यal_rate(अचिन्हित अक्षर rcs1)
अणु
	चयन (rcs1 & (AK4114_FS0|AK4114_FS1|AK4114_FS2|AK4114_FS3)) अणु
	हाल AK4114_FS_32000HZ: वापस 32000;
	हाल AK4114_FS_44100HZ: वापस 44100;
	हाल AK4114_FS_48000HZ: वापस 48000;
	हाल AK4114_FS_88200HZ: वापस 88200;
	हाल AK4114_FS_96000HZ: वापस 96000;
	हाल AK4114_FS_176400HZ: वापस 176400;
	हाल AK4114_FS_192000HZ: वापस 192000;
	शेष:		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_ak4114_in_error_info(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = दीर्घ_उच्च;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_in_error_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4114 *chip = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&chip->lock);
	ucontrol->value.पूर्णांकeger.value[0] =
		chip->errors[kcontrol->निजी_value];
	chip->errors[kcontrol->निजी_value] = 0;
	spin_unlock_irq(&chip->lock);
	वापस 0;
पूर्ण

#घोषणा snd_ak4114_in_bit_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ak4114_in_bit_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4114 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर reg = kcontrol->निजी_value & 0xff;
	अचिन्हित अक्षर bit = (kcontrol->निजी_value >> 8) & 0xff;
	अचिन्हित अक्षर inv = (kcontrol->निजी_value >> 31) & 1;

	ucontrol->value.पूर्णांकeger.value[0] = ((reg_पढ़ो(chip, reg) & (1 << bit)) ? 1 : 0) ^ inv;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_rate_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 192000;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_rate_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4114 *chip = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = बाह्यal_rate(reg_पढ़ो(chip, AK4114_REG_RCS1));
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_spdअगर_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4114 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित i;

	क्रम (i = 0; i < AK4114_REG_RXCSB_SIZE; i++)
		ucontrol->value.iec958.status[i] = reg_पढ़ो(chip, AK4114_REG_RXCSB0 + i);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_spdअगर_playback_get(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4114 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित i;

	क्रम (i = 0; i < AK4114_REG_TXCSB_SIZE; i++)
		ucontrol->value.iec958.status[i] = chip->txcsb[i];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_spdअगर_playback_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4114 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित i;

	क्रम (i = 0; i < AK4114_REG_TXCSB_SIZE; i++)
		reg_ग_लिखो(chip, AK4114_REG_TXCSB0 + i, ucontrol->value.iec958.status[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	स_रखो(ucontrol->value.iec958.status, 0xff, AK4114_REG_RXCSB_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_spdअगर_pinfo(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0xffff;
	uinfo->count = 4;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_spdअगर_pget(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4114 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु पंचांगp;

	ucontrol->value.पूर्णांकeger.value[0] = 0xf8f2;
	ucontrol->value.पूर्णांकeger.value[1] = 0x4e1f;
	पंचांगp = reg_पढ़ो(chip, AK4114_REG_Pc0) | (reg_पढ़ो(chip, AK4114_REG_Pc1) << 8);
	ucontrol->value.पूर्णांकeger.value[2] = पंचांगp;
	पंचांगp = reg_पढ़ो(chip, AK4114_REG_Pd0) | (reg_पढ़ो(chip, AK4114_REG_Pd1) << 8);
	ucontrol->value.पूर्णांकeger.value[3] = पंचांगp;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_spdअगर_qinfo(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = AK4114_REG_QSUB_SIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4114_spdअगर_qget(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4114 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित i;

	क्रम (i = 0; i < AK4114_REG_QSUB_SIZE; i++)
		ucontrol->value.bytes.data[i] = reg_पढ़ो(chip, AK4114_REG_QSUB_ADDR + i);
	वापस 0;
पूर्ण

/* Don't क्रमget to change AK4114_CONTROLS define!!! */
अटल स्थिर काष्ठा snd_kcontrol_new snd_ak4114_iec958_controls[] = अणु
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Parity Errors",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_in_error_info,
	.get =		snd_ak4114_in_error_get,
	.निजी_value = AK4114_PARITY_ERRORS,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 V-Bit Errors",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_in_error_info,
	.get =		snd_ak4114_in_error_get,
	.निजी_value = AK4114_V_BIT_ERRORS,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 C-CRC Errors",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_in_error_info,
	.get =		snd_ak4114_in_error_get,
	.निजी_value = AK4114_CCRC_ERRORS,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Q-CRC Errors",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_in_error_info,
	.get =		snd_ak4114_in_error_get,
	.निजी_value = AK4114_QCRC_ERRORS,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 External Rate",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_rate_info,
	.get =		snd_ak4114_rate_get,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,MASK),
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.info =		snd_ak4114_spdअगर_mask_info,
	.get =		snd_ak4114_spdअगर_mask_get,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_spdअगर_info,
	.get =		snd_ak4114_spdअगर_playback_get,
	.put =		snd_ak4114_spdअगर_playback_put,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",CAPTURE,MASK),
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.info =		snd_ak4114_spdअगर_mask_info,
	.get =		snd_ak4114_spdअगर_mask_get,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",CAPTURE,DEFAULT),
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_spdअगर_info,
	.get =		snd_ak4114_spdअगर_get,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Preamble Capture Default",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_spdअगर_pinfo,
	.get =		snd_ak4114_spdअगर_pget,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Q-subcode Capture Default",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_spdअगर_qinfo,
	.get =		snd_ak4114_spdअगर_qget,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Audio",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_in_bit_info,
	.get =		snd_ak4114_in_bit_get,
	.निजी_value = (1<<31) | (1<<8) | AK4114_REG_RCS0,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Non-PCM Bitstream",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_in_bit_info,
	.get =		snd_ak4114_in_bit_get,
	.निजी_value = (6<<8) | AK4114_REG_RCS0,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 DTS Bitstream",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_in_bit_info,
	.get =		snd_ak4114_in_bit_get,
	.निजी_value = (3<<8) | AK4114_REG_RCS0,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 PPL Lock Status",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4114_in_bit_info,
	.get =		snd_ak4114_in_bit_get,
	.निजी_value = (1<<31) | (4<<8) | AK4114_REG_RCS0,
पूर्ण
पूर्ण;


अटल व्योम snd_ak4114_proc_regs_पढ़ो(काष्ठा snd_info_entry *entry,
		काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा ak4114 *ak4114 = entry->निजी_data;
	पूर्णांक reg, val;
	/* all ak4114 रेजिस्टरs 0x00 - 0x1f */
	क्रम (reg = 0; reg < 0x20; reg++) अणु
		val = reg_पढ़ो(ak4114, reg);
		snd_iम_लिखो(buffer, "0x%02x = 0x%02x\n", reg, val);
	पूर्ण
पूर्ण

अटल व्योम snd_ak4114_proc_init(काष्ठा ak4114 *ak4114)
अणु
	snd_card_ro_proc_new(ak4114->card, "ak4114", ak4114,
			     snd_ak4114_proc_regs_पढ़ो);
पूर्ण

पूर्णांक snd_ak4114_build(काष्ठा ak4114 *ak4114,
		     काष्ठा snd_pcm_substream *ply_substream,
		     काष्ठा snd_pcm_substream *cap_substream)
अणु
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	अगर (snd_BUG_ON(!cap_substream))
		वापस -EINVAL;
	ak4114->playback_substream = ply_substream;
	ak4114->capture_substream = cap_substream;
	क्रम (idx = 0; idx < AK4114_CONTROLS; idx++) अणु
		kctl = snd_ctl_new1(&snd_ak4114_iec958_controls[idx], ak4114);
		अगर (kctl == शून्य)
			वापस -ENOMEM;
		अगर (म_माला(kctl->id.name, "Playback")) अणु
			अगर (ply_substream == शून्य) अणु
				snd_ctl_मुक्त_one(kctl);
				ak4114->kctls[idx] = शून्य;
				जारी;
			पूर्ण
			kctl->id.device = ply_substream->pcm->device;
			kctl->id.subdevice = ply_substream->number;
		पूर्ण अन्यथा अणु
			kctl->id.device = cap_substream->pcm->device;
			kctl->id.subdevice = cap_substream->number;
		पूर्ण
		err = snd_ctl_add(ak4114->card, kctl);
		अगर (err < 0)
			वापस err;
		ak4114->kctls[idx] = kctl;
	पूर्ण
	snd_ak4114_proc_init(ak4114);
	/* trigger workq */
	schedule_delayed_work(&ak4114->work, HZ / 10);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_ak4114_build);

/* notअगरy kcontrols अगर any parameters are changed */
अटल व्योम ak4114_notअगरy(काष्ठा ak4114 *ak4114,
			  अचिन्हित अक्षर rcs0, अचिन्हित अक्षर rcs1,
			  अचिन्हित अक्षर c0, अचिन्हित अक्षर c1)
अणु
	अगर (!ak4114->kctls[0])
		वापस;

	अगर (rcs0 & AK4114_PAR)
		snd_ctl_notअगरy(ak4114->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &ak4114->kctls[0]->id);
	अगर (rcs0 & AK4114_V)
		snd_ctl_notअगरy(ak4114->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &ak4114->kctls[1]->id);
	अगर (rcs1 & AK4114_CCRC)
		snd_ctl_notअगरy(ak4114->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &ak4114->kctls[2]->id);
	अगर (rcs1 & AK4114_QCRC)
		snd_ctl_notअगरy(ak4114->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &ak4114->kctls[3]->id);

	/* rate change */
	अगर (c1 & 0xf0)
		snd_ctl_notअगरy(ak4114->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &ak4114->kctls[4]->id);

	अगर ((c0 & AK4114_PEM) | (c0 & AK4114_CINT))
		snd_ctl_notअगरy(ak4114->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &ak4114->kctls[9]->id);
	अगर (c0 & AK4114_QINT)
		snd_ctl_notअगरy(ak4114->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &ak4114->kctls[10]->id);

	अगर (c0 & AK4114_AUDION)
		snd_ctl_notअगरy(ak4114->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &ak4114->kctls[11]->id);
	अगर (c0 & AK4114_AUTO)
		snd_ctl_notअगरy(ak4114->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &ak4114->kctls[12]->id);
	अगर (c0 & AK4114_DTSCD)
		snd_ctl_notअगरy(ak4114->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &ak4114->kctls[13]->id);
	अगर (c0 & AK4114_UNLCK)
		snd_ctl_notअगरy(ak4114->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &ak4114->kctls[14]->id);
पूर्ण

पूर्णांक snd_ak4114_बाह्यal_rate(काष्ठा ak4114 *ak4114)
अणु
	अचिन्हित अक्षर rcs1;

	rcs1 = reg_पढ़ो(ak4114, AK4114_REG_RCS1);
	वापस बाह्यal_rate(rcs1);
पूर्ण
EXPORT_SYMBOL(snd_ak4114_बाह्यal_rate);

पूर्णांक snd_ak4114_check_rate_and_errors(काष्ठा ak4114 *ak4114, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = ak4114->capture_substream ? ak4114->capture_substream->runसमय : शून्य;
	अचिन्हित दीर्घ _flags;
	पूर्णांक res = 0;
	अचिन्हित अक्षर rcs0, rcs1;
	अचिन्हित अक्षर c0, c1;

	rcs1 = reg_पढ़ो(ak4114, AK4114_REG_RCS1);
	अगर (flags & AK4114_CHECK_NO_STAT)
		जाओ __rate;
	rcs0 = reg_पढ़ो(ak4114, AK4114_REG_RCS0);
	spin_lock_irqsave(&ak4114->lock, _flags);
	अगर (rcs0 & AK4114_PAR)
		ak4114->errors[AK4114_PARITY_ERRORS]++;
	अगर (rcs1 & AK4114_V)
		ak4114->errors[AK4114_V_BIT_ERRORS]++;
	अगर (rcs1 & AK4114_CCRC)
		ak4114->errors[AK4114_CCRC_ERRORS]++;
	अगर (rcs1 & AK4114_QCRC)
		ak4114->errors[AK4114_QCRC_ERRORS]++;
	c0 = (ak4114->rcs0 & (AK4114_QINT | AK4114_CINT | AK4114_PEM | AK4114_AUDION | AK4114_AUTO | AK4114_UNLCK)) ^
                     (rcs0 & (AK4114_QINT | AK4114_CINT | AK4114_PEM | AK4114_AUDION | AK4114_AUTO | AK4114_UNLCK));
	c1 = (ak4114->rcs1 & 0xf0) ^ (rcs1 & 0xf0);
	ak4114->rcs0 = rcs0 & ~(AK4114_QINT | AK4114_CINT);
	ak4114->rcs1 = rcs1;
	spin_unlock_irqrestore(&ak4114->lock, _flags);

	ak4114_notअगरy(ak4114, rcs0, rcs1, c0, c1);
	अगर (ak4114->change_callback && (c0 | c1) != 0)
		ak4114->change_callback(ak4114, c0, c1);

      __rate:
	/* compare rate */
	res = बाह्यal_rate(rcs1);
	अगर (!(flags & AK4114_CHECK_NO_RATE) && runसमय && runसमय->rate != res) अणु
		snd_pcm_stream_lock_irqsave(ak4114->capture_substream, _flags);
		अगर (snd_pcm_running(ak4114->capture_substream)) अणु
			// prपूर्णांकk(KERN_DEBUG "rate changed (%i <- %i)\n", runसमय->rate, res);
			snd_pcm_stop(ak4114->capture_substream, SNDRV_PCM_STATE_DRAINING);
			res = 1;
		पूर्ण
		snd_pcm_stream_unlock_irqrestore(ak4114->capture_substream, _flags);
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL(snd_ak4114_check_rate_and_errors);

अटल व्योम ak4114_stats(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ak4114 *chip = container_of(work, काष्ठा ak4114, work.work);

	अगर (atomic_inc_वापस(&chip->wq_processing) == 1)
		snd_ak4114_check_rate_and_errors(chip, chip->check_flags);
	अगर (atomic_dec_and_test(&chip->wq_processing))
		schedule_delayed_work(&chip->work, HZ / 10);
पूर्ण

#अगर_घोषित CONFIG_PM
व्योम snd_ak4114_suspend(काष्ठा ak4114 *chip)
अणु
	atomic_inc(&chip->wq_processing); /* करोn't schedule new work */
	cancel_delayed_work_sync(&chip->work);
पूर्ण
EXPORT_SYMBOL(snd_ak4114_suspend);

व्योम snd_ak4114_resume(काष्ठा ak4114 *chip)
अणु
	atomic_dec(&chip->wq_processing);
	snd_ak4114_reinit(chip);
पूर्ण
EXPORT_SYMBOL(snd_ak4114_resume);
#पूर्ण_अगर
