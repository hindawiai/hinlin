<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Routines क्रम control of the AK4113 via I2C/4-wire serial पूर्णांकerface
 *  IEC958 (S/PDIF) receiver by Asahi Kasei
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Copyright (c) by Pavel Hofman <pavel.hofman@ivitera.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ak4113.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/info.h>

MODULE_AUTHOR("Pavel Hofman <pavel.hofman@ivitera.com>");
MODULE_DESCRIPTION("AK4113 IEC958 (S/PDIF) receiver by Asahi Kasei");
MODULE_LICENSE("GPL");

#घोषणा AK4113_ADDR			0x00 /* fixed address */

अटल व्योम ak4113_stats(काष्ठा work_काष्ठा *work);
अटल व्योम ak4113_init_regs(काष्ठा ak4113 *chip);


अटल व्योम reg_ग_लिखो(काष्ठा ak4113 *ak4113, अचिन्हित अक्षर reg,
		अचिन्हित अक्षर val)
अणु
	ak4113->ग_लिखो(ak4113->निजी_data, reg, val);
	अगर (reg < माप(ak4113->regmap))
		ak4113->regmap[reg] = val;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर reg_पढ़ो(काष्ठा ak4113 *ak4113, अचिन्हित अक्षर reg)
अणु
	वापस ak4113->पढ़ो(ak4113->निजी_data, reg);
पूर्ण

अटल व्योम snd_ak4113_मुक्त(काष्ठा ak4113 *chip)
अणु
	atomic_inc(&chip->wq_processing);	/* करोn't schedule new work */
	cancel_delayed_work_sync(&chip->work);
	kमुक्त(chip);
पूर्ण

अटल पूर्णांक snd_ak4113_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा ak4113 *chip = device->device_data;
	snd_ak4113_मुक्त(chip);
	वापस 0;
पूर्ण

पूर्णांक snd_ak4113_create(काष्ठा snd_card *card, ak4113_पढ़ो_t *पढ़ो,
		ak4113_ग_लिखो_t *ग_लिखो, स्थिर अचिन्हित अक्षर *pgm,
		व्योम *निजी_data, काष्ठा ak4113 **r_ak4113)
अणु
	काष्ठा ak4113 *chip;
	पूर्णांक err;
	अचिन्हित अक्षर reg;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =     snd_ak4113_dev_मुक्त,
	पूर्ण;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;
	spin_lock_init(&chip->lock);
	chip->card = card;
	chip->पढ़ो = पढ़ो;
	chip->ग_लिखो = ग_लिखो;
	chip->निजी_data = निजी_data;
	INIT_DELAYED_WORK(&chip->work, ak4113_stats);
	atomic_set(&chip->wq_processing, 0);
	mutex_init(&chip->reinit_mutex);

	क्रम (reg = 0; reg < AK4113_WRITABLE_REGS ; reg++)
		chip->regmap[reg] = pgm[reg];
	ak4113_init_regs(chip);

	chip->rcs0 = reg_पढ़ो(chip, AK4113_REG_RCS0) & ~(AK4113_QINT |
			AK4113_CINT | AK4113_STC);
	chip->rcs1 = reg_पढ़ो(chip, AK4113_REG_RCS1);
	chip->rcs2 = reg_पढ़ो(chip, AK4113_REG_RCS2);
	err = snd_device_new(card, SNDRV_DEV_CODEC, chip, &ops);
	अगर (err < 0)
		जाओ __fail;

	अगर (r_ak4113)
		*r_ak4113 = chip;
	वापस 0;

__fail:
	snd_ak4113_मुक्त(chip);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_ak4113_create);

व्योम snd_ak4113_reg_ग_लिखो(काष्ठा ak4113 *chip, अचिन्हित अक्षर reg,
		अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
	अगर (reg >= AK4113_WRITABLE_REGS)
		वापस;
	reg_ग_लिखो(chip, reg, (chip->regmap[reg] & ~mask) | val);
पूर्ण
EXPORT_SYMBOL_GPL(snd_ak4113_reg_ग_लिखो);

अटल व्योम ak4113_init_regs(काष्ठा ak4113 *chip)
अणु
	अचिन्हित अक्षर old = chip->regmap[AK4113_REG_PWRDN], reg;

	/* bring the chip to reset state and घातerकरोwn state */
	reg_ग_लिखो(chip, AK4113_REG_PWRDN, old & ~(AK4113_RST|AK4113_PWN));
	udelay(200);
	/* release reset, but leave घातerकरोwn */
	reg_ग_लिखो(chip, AK4113_REG_PWRDN, (old | AK4113_RST) & ~AK4113_PWN);
	udelay(200);
	क्रम (reg = 1; reg < AK4113_WRITABLE_REGS; reg++)
		reg_ग_लिखो(chip, reg, chip->regmap[reg]);
	/* release घातerकरोwn, everything is initialized now */
	reg_ग_लिखो(chip, AK4113_REG_PWRDN, old | AK4113_RST | AK4113_PWN);
पूर्ण

व्योम snd_ak4113_reinit(काष्ठा ak4113 *chip)
अणु
	अगर (atomic_inc_वापस(&chip->wq_processing) == 1)
		cancel_delayed_work_sync(&chip->work);
	mutex_lock(&chip->reinit_mutex);
	ak4113_init_regs(chip);
	mutex_unlock(&chip->reinit_mutex);
	/* bring up statistics / event queing */
	अगर (atomic_dec_and_test(&chip->wq_processing))
		schedule_delayed_work(&chip->work, HZ / 10);
पूर्ण
EXPORT_SYMBOL_GPL(snd_ak4113_reinit);

अटल अचिन्हित पूर्णांक बाह्यal_rate(अचिन्हित अक्षर rcs1)
अणु
	चयन (rcs1 & (AK4113_FS0|AK4113_FS1|AK4113_FS2|AK4113_FS3)) अणु
	हाल AK4113_FS_8000HZ:
		वापस 8000;
	हाल AK4113_FS_11025HZ:
		वापस 11025;
	हाल AK4113_FS_16000HZ:
		वापस 16000;
	हाल AK4113_FS_22050HZ:
		वापस 22050;
	हाल AK4113_FS_24000HZ:
		वापस 24000;
	हाल AK4113_FS_32000HZ:
		वापस 32000;
	हाल AK4113_FS_44100HZ:
		वापस 44100;
	हाल AK4113_FS_48000HZ:
		वापस 48000;
	हाल AK4113_FS_64000HZ:
		वापस 64000;
	हाल AK4113_FS_88200HZ:
		वापस 88200;
	हाल AK4113_FS_96000HZ:
		वापस 96000;
	हाल AK4113_FS_176400HZ:
		वापस 176400;
	हाल AK4113_FS_192000HZ:
		वापस 192000;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_ak4113_in_error_info(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = दीर्घ_उच्च;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_in_error_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4113 *chip = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&chip->lock);
	ucontrol->value.पूर्णांकeger.value[0] =
		chip->errors[kcontrol->निजी_value];
	chip->errors[kcontrol->निजी_value] = 0;
	spin_unlock_irq(&chip->lock);
	वापस 0;
पूर्ण

#घोषणा snd_ak4113_in_bit_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ak4113_in_bit_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4113 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर reg = kcontrol->निजी_value & 0xff;
	अचिन्हित अक्षर bit = (kcontrol->निजी_value >> 8) & 0xff;
	अचिन्हित अक्षर inv = (kcontrol->निजी_value >> 31) & 1;

	ucontrol->value.पूर्णांकeger.value[0] =
		((reg_पढ़ो(chip, reg) & (1 << bit)) ? 1 : 0) ^ inv;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_rx_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 5;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_rx_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4113 *chip = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] =
		(AK4113_IPS(chip->regmap[AK4113_REG_IO1]));
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_rx_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4113 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	u8 old_val;

	spin_lock_irq(&chip->lock);
	old_val = chip->regmap[AK4113_REG_IO1];
	change = ucontrol->value.पूर्णांकeger.value[0] != AK4113_IPS(old_val);
	अगर (change)
		reg_ग_लिखो(chip, AK4113_REG_IO1,
				(old_val & (~AK4113_IPS(0xff))) |
				(AK4113_IPS(ucontrol->value.पूर्णांकeger.value[0])));
	spin_unlock_irq(&chip->lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_ak4113_rate_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 192000;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_rate_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4113 *chip = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = बाह्यal_rate(reg_पढ़ो(chip,
				AK4113_REG_RCS1));
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_spdअगर_info(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4113 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित i;

	क्रम (i = 0; i < AK4113_REG_RXCSB_SIZE; i++)
		ucontrol->value.iec958.status[i] = reg_पढ़ो(chip,
				AK4113_REG_RXCSB0 + i);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	स_रखो(ucontrol->value.iec958.status, 0xff, AK4113_REG_RXCSB_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_spdअगर_pinfo(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0xffff;
	uinfo->count = 4;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_spdअगर_pget(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4113 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु पंचांगp;

	ucontrol->value.पूर्णांकeger.value[0] = 0xf8f2;
	ucontrol->value.पूर्णांकeger.value[1] = 0x4e1f;
	पंचांगp = reg_पढ़ो(chip, AK4113_REG_Pc0) |
		(reg_पढ़ो(chip, AK4113_REG_Pc1) << 8);
	ucontrol->value.पूर्णांकeger.value[2] = पंचांगp;
	पंचांगp = reg_पढ़ो(chip, AK4113_REG_Pd0) |
		(reg_पढ़ो(chip, AK4113_REG_Pd1) << 8);
	ucontrol->value.पूर्णांकeger.value[3] = पंचांगp;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_spdअगर_qinfo(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = AK4113_REG_QSUB_SIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4113_spdअगर_qget(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ak4113 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित i;

	क्रम (i = 0; i < AK4113_REG_QSUB_SIZE; i++)
		ucontrol->value.bytes.data[i] = reg_पढ़ो(chip,
				AK4113_REG_QSUB_ADDR + i);
	वापस 0;
पूर्ण

/* Don't क्रमget to change AK4113_CONTROLS define!!! */
अटल स्थिर काष्ठा snd_kcontrol_new snd_ak4113_iec958_controls[] = अणु
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Parity Errors",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ |
		SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4113_in_error_info,
	.get =		snd_ak4113_in_error_get,
	.निजी_value = AK4113_PARITY_ERRORS,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 V-Bit Errors",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ |
		SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4113_in_error_info,
	.get =		snd_ak4113_in_error_get,
	.निजी_value = AK4113_V_BIT_ERRORS,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 C-CRC Errors",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ |
		SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4113_in_error_info,
	.get =		snd_ak4113_in_error_get,
	.निजी_value = AK4113_CCRC_ERRORS,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Q-CRC Errors",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ |
		SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4113_in_error_info,
	.get =		snd_ak4113_in_error_get,
	.निजी_value = AK4113_QCRC_ERRORS,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 External Rate",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ |
		SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4113_rate_info,
	.get =		snd_ak4113_rate_get,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("", CAPTURE, MASK),
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.info =		snd_ak4113_spdअगर_mask_info,
	.get =		snd_ak4113_spdअगर_mask_get,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("", CAPTURE, DEFAULT),
	.access =	SNDRV_CTL_ELEM_ACCESS_READ |
		SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4113_spdअगर_info,
	.get =		snd_ak4113_spdअगर_get,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Preamble Capture Default",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ |
		SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4113_spdअगर_pinfo,
	.get =		snd_ak4113_spdअगर_pget,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Q-subcode Capture Default",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ |
		SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4113_spdअगर_qinfo,
	.get =		snd_ak4113_spdअगर_qget,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Audio",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ |
		SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4113_in_bit_info,
	.get =		snd_ak4113_in_bit_get,
	.निजी_value = (1<<31) | (1<<8) | AK4113_REG_RCS0,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 Non-PCM Bitstream",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ |
		SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4113_in_bit_info,
	.get =		snd_ak4113_in_bit_get,
	.निजी_value = (0<<8) | AK4113_REG_RCS1,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"IEC958 DTS Bitstream",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ |
		SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		snd_ak4113_in_bit_info,
	.get =		snd_ak4113_in_bit_get,
	.निजी_value = (1<<8) | AK4113_REG_RCS1,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		"AK4113 Input Select",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ |
		SNDRV_CTL_ELEM_ACCESS_WRITE,
	.info =		snd_ak4113_rx_info,
	.get =		snd_ak4113_rx_get,
	.put =		snd_ak4113_rx_put,
पूर्ण
पूर्ण;

अटल व्योम snd_ak4113_proc_regs_पढ़ो(काष्ठा snd_info_entry *entry,
		काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा ak4113 *ak4113 = entry->निजी_data;
	पूर्णांक reg, val;
	/* all ak4113 रेजिस्टरs 0x00 - 0x1c */
	क्रम (reg = 0; reg < 0x1d; reg++) अणु
		val = reg_पढ़ो(ak4113, reg);
		snd_iम_लिखो(buffer, "0x%02x = 0x%02x\n", reg, val);
	पूर्ण
पूर्ण

अटल व्योम snd_ak4113_proc_init(काष्ठा ak4113 *ak4113)
अणु
	snd_card_ro_proc_new(ak4113->card, "ak4113", ak4113,
			     snd_ak4113_proc_regs_पढ़ो);
पूर्ण

पूर्णांक snd_ak4113_build(काष्ठा ak4113 *ak4113,
		काष्ठा snd_pcm_substream *cap_substream)
अणु
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	अगर (snd_BUG_ON(!cap_substream))
		वापस -EINVAL;
	ak4113->substream = cap_substream;
	क्रम (idx = 0; idx < AK4113_CONTROLS; idx++) अणु
		kctl = snd_ctl_new1(&snd_ak4113_iec958_controls[idx], ak4113);
		अगर (kctl == शून्य)
			वापस -ENOMEM;
		kctl->id.device = cap_substream->pcm->device;
		kctl->id.subdevice = cap_substream->number;
		err = snd_ctl_add(ak4113->card, kctl);
		अगर (err < 0)
			वापस err;
		ak4113->kctls[idx] = kctl;
	पूर्ण
	snd_ak4113_proc_init(ak4113);
	/* trigger workq */
	schedule_delayed_work(&ak4113->work, HZ / 10);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_ak4113_build);

पूर्णांक snd_ak4113_बाह्यal_rate(काष्ठा ak4113 *ak4113)
अणु
	अचिन्हित अक्षर rcs1;

	rcs1 = reg_पढ़ो(ak4113, AK4113_REG_RCS1);
	वापस बाह्यal_rate(rcs1);
पूर्ण
EXPORT_SYMBOL_GPL(snd_ak4113_बाह्यal_rate);

पूर्णांक snd_ak4113_check_rate_and_errors(काष्ठा ak4113 *ak4113, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा snd_pcm_runसमय *runसमय =
		ak4113->substream ? ak4113->substream->runसमय : शून्य;
	अचिन्हित दीर्घ _flags;
	पूर्णांक res = 0;
	अचिन्हित अक्षर rcs0, rcs1, rcs2;
	अचिन्हित अक्षर c0, c1;

	rcs1 = reg_पढ़ो(ak4113, AK4113_REG_RCS1);
	अगर (flags & AK4113_CHECK_NO_STAT)
		जाओ __rate;
	rcs0 = reg_पढ़ो(ak4113, AK4113_REG_RCS0);
	rcs2 = reg_पढ़ो(ak4113, AK4113_REG_RCS2);
	spin_lock_irqsave(&ak4113->lock, _flags);
	अगर (rcs0 & AK4113_PAR)
		ak4113->errors[AK4113_PARITY_ERRORS]++;
	अगर (rcs0 & AK4113_V)
		ak4113->errors[AK4113_V_BIT_ERRORS]++;
	अगर (rcs2 & AK4113_CCRC)
		ak4113->errors[AK4113_CCRC_ERRORS]++;
	अगर (rcs2 & AK4113_QCRC)
		ak4113->errors[AK4113_QCRC_ERRORS]++;
	c0 = (ak4113->rcs0 & (AK4113_QINT | AK4113_CINT | AK4113_STC |
				AK4113_AUDION | AK4113_AUTO | AK4113_UNLCK)) ^
		(rcs0 & (AK4113_QINT | AK4113_CINT | AK4113_STC |
			 AK4113_AUDION | AK4113_AUTO | AK4113_UNLCK));
	c1 = (ak4113->rcs1 & (AK4113_DTSCD | AK4113_NPCM | AK4113_PEM |
				AK4113_DAT | 0xf0)) ^
		(rcs1 & (AK4113_DTSCD | AK4113_NPCM | AK4113_PEM |
			 AK4113_DAT | 0xf0));
	ak4113->rcs0 = rcs0 & ~(AK4113_QINT | AK4113_CINT | AK4113_STC);
	ak4113->rcs1 = rcs1;
	ak4113->rcs2 = rcs2;
	spin_unlock_irqrestore(&ak4113->lock, _flags);

	अगर (rcs0 & AK4113_PAR)
		snd_ctl_notअगरy(ak4113->card, SNDRV_CTL_EVENT_MASK_VALUE,
				&ak4113->kctls[0]->id);
	अगर (rcs0 & AK4113_V)
		snd_ctl_notअगरy(ak4113->card, SNDRV_CTL_EVENT_MASK_VALUE,
				&ak4113->kctls[1]->id);
	अगर (rcs2 & AK4113_CCRC)
		snd_ctl_notअगरy(ak4113->card, SNDRV_CTL_EVENT_MASK_VALUE,
				&ak4113->kctls[2]->id);
	अगर (rcs2 & AK4113_QCRC)
		snd_ctl_notअगरy(ak4113->card, SNDRV_CTL_EVENT_MASK_VALUE,
				&ak4113->kctls[3]->id);

	/* rate change */
	अगर (c1 & 0xf0)
		snd_ctl_notअगरy(ak4113->card, SNDRV_CTL_EVENT_MASK_VALUE,
				&ak4113->kctls[4]->id);

	अगर ((c1 & AK4113_PEM) | (c0 & AK4113_CINT))
		snd_ctl_notअगरy(ak4113->card, SNDRV_CTL_EVENT_MASK_VALUE,
				&ak4113->kctls[6]->id);
	अगर (c0 & AK4113_QINT)
		snd_ctl_notअगरy(ak4113->card, SNDRV_CTL_EVENT_MASK_VALUE,
				&ak4113->kctls[8]->id);

	अगर (c0 & AK4113_AUDION)
		snd_ctl_notअगरy(ak4113->card, SNDRV_CTL_EVENT_MASK_VALUE,
				&ak4113->kctls[9]->id);
	अगर (c1 & AK4113_NPCM)
		snd_ctl_notअगरy(ak4113->card, SNDRV_CTL_EVENT_MASK_VALUE,
				&ak4113->kctls[10]->id);
	अगर (c1 & AK4113_DTSCD)
		snd_ctl_notअगरy(ak4113->card, SNDRV_CTL_EVENT_MASK_VALUE,
				&ak4113->kctls[11]->id);

	अगर (ak4113->change_callback && (c0 | c1) != 0)
		ak4113->change_callback(ak4113, c0, c1);

__rate:
	/* compare rate */
	res = बाह्यal_rate(rcs1);
	अगर (!(flags & AK4113_CHECK_NO_RATE) && runसमय &&
			(runसमय->rate != res)) अणु
		snd_pcm_stream_lock_irqsave(ak4113->substream, _flags);
		अगर (snd_pcm_running(ak4113->substream)) अणु
			/*prपूर्णांकk(KERN_DEBUG "rate changed (%i <- %i)\n",
			 * runसमय->rate, res); */
			snd_pcm_stop(ak4113->substream,
					SNDRV_PCM_STATE_DRAINING);
			wake_up(&runसमय->sleep);
			res = 1;
		पूर्ण
		snd_pcm_stream_unlock_irqrestore(ak4113->substream, _flags);
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(snd_ak4113_check_rate_and_errors);

अटल व्योम ak4113_stats(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ak4113 *chip = container_of(work, काष्ठा ak4113, work.work);

	अगर (atomic_inc_वापस(&chip->wq_processing) == 1)
		snd_ak4113_check_rate_and_errors(chip, chip->check_flags);

	अगर (atomic_dec_and_test(&chip->wq_processing))
		schedule_delayed_work(&chip->work, HZ / 10);
पूर्ण

#अगर_घोषित CONFIG_PM
व्योम snd_ak4113_suspend(काष्ठा ak4113 *chip)
अणु
	atomic_inc(&chip->wq_processing); /* करोn't schedule new work */
	cancel_delayed_work_sync(&chip->work);
पूर्ण
EXPORT_SYMBOL(snd_ak4113_suspend);

व्योम snd_ak4113_resume(काष्ठा ak4113 *chip)
अणु
	atomic_dec(&chip->wq_processing);
	snd_ak4113_reinit(chip);
पूर्ण
EXPORT_SYMBOL(snd_ak4113_resume);
#पूर्ण_अगर
