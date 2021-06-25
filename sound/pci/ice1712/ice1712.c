<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble ICE1712 (Envy24)
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 */

/*
  NOTES:
  - spdअगर nonaudio consumer mode करोes not work (at least with my
    Sony STR-DB830)
*/

/*
 * Changes:
 *
 *  2002.09.09	Takashi Iwai <tiwai@suse.de>
 *	split the code to several files.  each low-level routine
 *	is stored in the local file and called from registration
 *	function from card_info काष्ठा.
 *
 *  2002.11.26	James Stafक्रमd <jstafक्रमd@ampltd.com>
 *	Added support क्रम VT1724 (Envy24HT)
 *	I have left out support क्रम 176.4 and 192 KHz क्रम the moment.
 *  I also haven't करोne anything with the पूर्णांकernal S/PDIF transmitter or the MPU-401
 *
 *  2003.02.20  Taksahi Iwai <tiwai@suse.de>
 *	Split vt1724 part to an independent driver.
 *	The GPIO is accessed through the callback functions now.
 *
 * 2004.03.31 Doug McLain <nostar@comcast.net>
 *    Added support क्रम Event Electronics EZ8 card to hoontech.c.
 */


#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>
#समावेश <sound/cs8427.h>
#समावेश <sound/info.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश <sound/asoundef.h>

#समावेश "ice1712.h"

/* lowlevel routines */
#समावेश "delta.h"
#समावेश "ews.h"
#समावेश "hoontech.h"

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("ICEnsemble ICE1712 (Envy24)");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;/* Enable this card */
अटल अक्षर *model[SNDRV_CARDS];
अटल bool omni[SNDRV_CARDS];				/* Delta44 & 66 Omni I/O support */
अटल पूर्णांक cs8427_समयout[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS-1)] = 500पूर्ण; /* CS8427 S/PDIF transceiver reset समयout value in msec */
अटल पूर्णांक dxr_enable[SNDRV_CARDS];			/* DXR enable क्रम DMX6FIRE */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for ICE1712 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for ICE1712 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable ICE1712 soundcard.");
module_param_array(omni, bool, शून्य, 0444);
MODULE_PARM_DESC(omni, "Enable Midiman M-Audio Delta Omni I/O support.");
module_param_array(cs8427_समयout, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(cs8427_समयout, "Define reset timeout for cs8427 chip in msec resolution.");
module_param_array(model, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(model, "Use the given board model.");
module_param_array(dxr_enable, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(dxr_enable, "Enable DXR support for Terratec DMX6FIRE.");


अटल स्थिर काष्ठा pci_device_id snd_ice1712_ids[] = अणु
	अणु PCI_VDEVICE(ICE, PCI_DEVICE_ID_ICE_1712), 0 पूर्ण,   /* ICE1712 */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_ice1712_ids);

अटल पूर्णांक snd_ice1712_build_pro_mixer(काष्ठा snd_ice1712 *ice);
अटल पूर्णांक snd_ice1712_build_controls(काष्ठा snd_ice1712 *ice);

अटल पूर्णांक PRO_RATE_LOCKED;
अटल पूर्णांक PRO_RATE_RESET = 1;
अटल अचिन्हित पूर्णांक PRO_RATE_DEFAULT = 44100;

/*
 *  Basic I/O
 */

/* check whether the घड़ी mode is spdअगर-in */
अटल अंतरभूत पूर्णांक is_spdअगर_master(काष्ठा snd_ice1712 *ice)
अणु
	वापस (inb(ICEMT(ice, RATE)) & ICE1712_SPDIF_MASTER) ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_pro_rate_locked(काष्ठा snd_ice1712 *ice)
अणु
	वापस is_spdअगर_master(ice) || PRO_RATE_LOCKED;
पूर्ण

अटल अंतरभूत व्योम snd_ice1712_ds_ग_लिखो(काष्ठा snd_ice1712 *ice, u8 channel, u8 addr, u32 data)
अणु
	outb((channel << 4) | addr, ICEDS(ice, INDEX));
	outl(data, ICEDS(ice, DATA));
पूर्ण

अटल अंतरभूत u32 snd_ice1712_ds_पढ़ो(काष्ठा snd_ice1712 *ice, u8 channel, u8 addr)
अणु
	outb((channel << 4) | addr, ICEDS(ice, INDEX));
	वापस inl(ICEDS(ice, DATA));
पूर्ण

अटल व्योम snd_ice1712_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97,
				   अचिन्हित लघु reg,
				   अचिन्हित लघु val)
अणु
	काष्ठा snd_ice1712 *ice = ac97->निजी_data;
	पूर्णांक पंचांग;
	अचिन्हित अक्षर old_cmd = 0;

	क्रम (पंचांग = 0; पंचांग < 0x10000; पंचांग++) अणु
		old_cmd = inb(ICEREG(ice, AC97_CMD));
		अगर (old_cmd & (ICE1712_AC97_WRITE | ICE1712_AC97_READ))
			जारी;
		अगर (!(old_cmd & ICE1712_AC97_READY))
			जारी;
		अवरोध;
	पूर्ण
	outb(reg, ICEREG(ice, AC97_INDEX));
	outw(val, ICEREG(ice, AC97_DATA));
	old_cmd &= ~(ICE1712_AC97_PBK_VSR | ICE1712_AC97_CAP_VSR);
	outb(old_cmd | ICE1712_AC97_WRITE, ICEREG(ice, AC97_CMD));
	क्रम (पंचांग = 0; पंचांग < 0x10000; पंचांग++)
		अगर ((inb(ICEREG(ice, AC97_CMD)) & ICE1712_AC97_WRITE) == 0)
			अवरोध;
पूर्ण

अटल अचिन्हित लघु snd_ice1712_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
					    अचिन्हित लघु reg)
अणु
	काष्ठा snd_ice1712 *ice = ac97->निजी_data;
	पूर्णांक पंचांग;
	अचिन्हित अक्षर old_cmd = 0;

	क्रम (पंचांग = 0; पंचांग < 0x10000; पंचांग++) अणु
		old_cmd = inb(ICEREG(ice, AC97_CMD));
		अगर (old_cmd & (ICE1712_AC97_WRITE | ICE1712_AC97_READ))
			जारी;
		अगर (!(old_cmd & ICE1712_AC97_READY))
			जारी;
		अवरोध;
	पूर्ण
	outb(reg, ICEREG(ice, AC97_INDEX));
	outb(old_cmd | ICE1712_AC97_READ, ICEREG(ice, AC97_CMD));
	क्रम (पंचांग = 0; पंचांग < 0x10000; पंचांग++)
		अगर ((inb(ICEREG(ice, AC97_CMD)) & ICE1712_AC97_READ) == 0)
			अवरोध;
	अगर (पंचांग >= 0x10000)		/* समयout */
		वापस ~0;
	वापस inw(ICEREG(ice, AC97_DATA));
पूर्ण

/*
 * pro ac97 section
 */

अटल व्योम snd_ice1712_pro_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97,
				       अचिन्हित लघु reg,
				       अचिन्हित लघु val)
अणु
	काष्ठा snd_ice1712 *ice = ac97->निजी_data;
	पूर्णांक पंचांग;
	अचिन्हित अक्षर old_cmd = 0;

	क्रम (पंचांग = 0; पंचांग < 0x10000; पंचांग++) अणु
		old_cmd = inb(ICEMT(ice, AC97_CMD));
		अगर (old_cmd & (ICE1712_AC97_WRITE | ICE1712_AC97_READ))
			जारी;
		अगर (!(old_cmd & ICE1712_AC97_READY))
			जारी;
		अवरोध;
	पूर्ण
	outb(reg, ICEMT(ice, AC97_INDEX));
	outw(val, ICEMT(ice, AC97_DATA));
	old_cmd &= ~(ICE1712_AC97_PBK_VSR | ICE1712_AC97_CAP_VSR);
	outb(old_cmd | ICE1712_AC97_WRITE, ICEMT(ice, AC97_CMD));
	क्रम (पंचांग = 0; पंचांग < 0x10000; पंचांग++)
		अगर ((inb(ICEMT(ice, AC97_CMD)) & ICE1712_AC97_WRITE) == 0)
			अवरोध;
पूर्ण


अटल अचिन्हित लघु snd_ice1712_pro_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
						अचिन्हित लघु reg)
अणु
	काष्ठा snd_ice1712 *ice = ac97->निजी_data;
	पूर्णांक पंचांग;
	अचिन्हित अक्षर old_cmd = 0;

	क्रम (पंचांग = 0; पंचांग < 0x10000; पंचांग++) अणु
		old_cmd = inb(ICEMT(ice, AC97_CMD));
		अगर (old_cmd & (ICE1712_AC97_WRITE | ICE1712_AC97_READ))
			जारी;
		अगर (!(old_cmd & ICE1712_AC97_READY))
			जारी;
		अवरोध;
	पूर्ण
	outb(reg, ICEMT(ice, AC97_INDEX));
	outb(old_cmd | ICE1712_AC97_READ, ICEMT(ice, AC97_CMD));
	क्रम (पंचांग = 0; पंचांग < 0x10000; पंचांग++)
		अगर ((inb(ICEMT(ice, AC97_CMD)) & ICE1712_AC97_READ) == 0)
			अवरोध;
	अगर (पंचांग >= 0x10000)		/* समयout */
		वापस ~0;
	वापस inw(ICEMT(ice, AC97_DATA));
पूर्ण

/*
 * consumer ac97 digital mix
 */
#घोषणा snd_ice1712_digmix_route_ac97_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ice1712_digmix_route_ac97_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = inb(ICEMT(ice, MONITOR_ROUTECTRL)) & ICE1712_ROUTE_AC97 ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_digmix_route_ac97_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val, nval;

	spin_lock_irq(&ice->reg_lock);
	val = inb(ICEMT(ice, MONITOR_ROUTECTRL));
	nval = val & ~ICE1712_ROUTE_AC97;
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		nval |= ICE1712_ROUTE_AC97;
	outb(nval, ICEMT(ice, MONITOR_ROUTECTRL));
	spin_unlock_irq(&ice->reg_lock);
	वापस val != nval;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_mixer_digmix_route_ac97 = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Digital Mixer To AC97",
	.info = snd_ice1712_digmix_route_ac97_info,
	.get = snd_ice1712_digmix_route_ac97_get,
	.put = snd_ice1712_digmix_route_ac97_put,
पूर्ण;


/*
 * gpio operations
 */
अटल व्योम snd_ice1712_set_gpio_dir(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक data)
अणु
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_सूचीECTION, data);
	inb(ICEREG(ice, DATA)); /* dummy पढ़ो क्रम pci-posting */
पूर्ण

अटल अचिन्हित पूर्णांक snd_ice1712_get_gpio_dir(काष्ठा snd_ice1712 *ice)
अणु
	वापस snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_सूचीECTION);
पूर्ण

अटल अचिन्हित पूर्णांक snd_ice1712_get_gpio_mask(काष्ठा snd_ice1712 *ice)
अणु
	वापस snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_WRITE_MASK);
पूर्ण

अटल व्योम snd_ice1712_set_gpio_mask(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक data)
अणु
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_WRITE_MASK, data);
	inb(ICEREG(ice, DATA)); /* dummy पढ़ो क्रम pci-posting */
पूर्ण

अटल अचिन्हित पूर्णांक snd_ice1712_get_gpio_data(काष्ठा snd_ice1712 *ice)
अणु
	वापस snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_DATA);
पूर्ण

अटल व्योम snd_ice1712_set_gpio_data(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक val)
अणु
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, val);
	inb(ICEREG(ice, DATA)); /* dummy पढ़ो क्रम pci-posting */
पूर्ण

/*
 *
 * CS8427 पूर्णांकerface
 *
 */

/*
 * change the input घड़ी selection
 * spdअगर_घड़ी = 1 - IEC958 input, 0 - Envy24
 */
अटल पूर्णांक snd_ice1712_cs8427_set_input_घड़ी(काष्ठा snd_ice1712 *ice, पूर्णांक spdअगर_घड़ी)
अणु
	अचिन्हित अक्षर reg[2] = अणु 0x80 | 4, 0 पूर्ण;   /* CS8427 स्वतः increment | रेजिस्टर number 4 + data */
	अचिन्हित अक्षर val, nval;
	पूर्णांक res = 0;

	snd_i2c_lock(ice->i2c);
	अगर (snd_i2c_sendbytes(ice->cs8427, reg, 1) != 1) अणु
		snd_i2c_unlock(ice->i2c);
		वापस -EIO;
	पूर्ण
	अगर (snd_i2c_पढ़ोbytes(ice->cs8427, &val, 1) != 1) अणु
		snd_i2c_unlock(ice->i2c);
		वापस -EIO;
	पूर्ण
	nval = val & 0xf0;
	अगर (spdअगर_घड़ी)
		nval |= 0x01;
	अन्यथा
		nval |= 0x04;
	अगर (val != nval) अणु
		reg[1] = nval;
		अगर (snd_i2c_sendbytes(ice->cs8427, reg, 2) != 2) अणु
			res = -EIO;
		पूर्ण अन्यथा अणु
			res++;
		पूर्ण
	पूर्ण
	snd_i2c_unlock(ice->i2c);
	वापस res;
पूर्ण

/*
 * spdअगर callbacks
 */
अटल व्योम खोलो_cs8427(काष्ठा snd_ice1712 *ice, काष्ठा snd_pcm_substream *substream)
अणु
	snd_cs8427_iec958_active(ice->cs8427, 1);
पूर्ण

अटल व्योम बंद_cs8427(काष्ठा snd_ice1712 *ice, काष्ठा snd_pcm_substream *substream)
अणु
	snd_cs8427_iec958_active(ice->cs8427, 0);
पूर्ण

अटल व्योम setup_cs8427(काष्ठा snd_ice1712 *ice, पूर्णांक rate)
अणु
	snd_cs8427_iec958_pcm(ice->cs8427, rate);
पूर्ण

/*
 * create and initialize callbacks क्रम cs8427 पूर्णांकerface
 */
पूर्णांक snd_ice1712_init_cs8427(काष्ठा snd_ice1712 *ice, पूर्णांक addr)
अणु
	पूर्णांक err;

	err = snd_cs8427_create(ice->i2c, addr,
		(ice->cs8427_समयout * HZ) / 1000, &ice->cs8427);
	अगर (err < 0) अणु
		dev_err(ice->card->dev, "CS8427 initialization failed\n");
		वापस err;
	पूर्ण
	ice->spdअगर.ops.खोलो = खोलो_cs8427;
	ice->spdअगर.ops.बंद = बंद_cs8427;
	ice->spdअगर.ops.setup_rate = setup_cs8427;
	वापस 0;
पूर्ण

अटल व्योम snd_ice1712_set_input_घड़ी_source(काष्ठा snd_ice1712 *ice, पूर्णांक spdअगर_is_master)
अणु
	/* change CS8427 घड़ी source too */
	अगर (ice->cs8427)
		snd_ice1712_cs8427_set_input_घड़ी(ice, spdअगर_is_master);
	/* notअगरy ak4524 chip as well */
	अगर (spdअगर_is_master) अणु
		अचिन्हित पूर्णांक i;
		क्रम (i = 0; i < ice->akm_codecs; i++) अणु
			अगर (ice->akm[i].ops.set_rate_val)
				ice->akm[i].ops.set_rate_val(&ice->akm[i], 0);
		पूर्ण
	पूर्ण
पूर्ण

/*
 *  Interrupt handler
 */

अटल irqवापस_t snd_ice1712_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_ice1712 *ice = dev_id;
	अचिन्हित अक्षर status;
	पूर्णांक handled = 0;

	जबतक (1) अणु
		status = inb(ICEREG(ice, IRQSTAT));
		अगर (status == 0)
			अवरोध;
		handled = 1;
		अगर (status & ICE1712_IRQ_MPU1) अणु
			अगर (ice->rmidi[0])
				snd_mpu401_uart_पूर्णांकerrupt(irq, ice->rmidi[0]->निजी_data);
			outb(ICE1712_IRQ_MPU1, ICEREG(ice, IRQSTAT));
			status &= ~ICE1712_IRQ_MPU1;
		पूर्ण
		अगर (status & ICE1712_IRQ_TIMER)
			outb(ICE1712_IRQ_TIMER, ICEREG(ice, IRQSTAT));
		अगर (status & ICE1712_IRQ_MPU2) अणु
			अगर (ice->rmidi[1])
				snd_mpu401_uart_पूर्णांकerrupt(irq, ice->rmidi[1]->निजी_data);
			outb(ICE1712_IRQ_MPU2, ICEREG(ice, IRQSTAT));
			status &= ~ICE1712_IRQ_MPU2;
		पूर्ण
		अगर (status & ICE1712_IRQ_PROPCM) अणु
			अचिन्हित अक्षर mtstat = inb(ICEMT(ice, IRQ));
			अगर (mtstat & ICE1712_MULTI_PBKSTATUS) अणु
				अगर (ice->playback_pro_substream)
					snd_pcm_period_elapsed(ice->playback_pro_substream);
				outb(ICE1712_MULTI_PBKSTATUS, ICEMT(ice, IRQ));
			पूर्ण
			अगर (mtstat & ICE1712_MULTI_CAPSTATUS) अणु
				अगर (ice->capture_pro_substream)
					snd_pcm_period_elapsed(ice->capture_pro_substream);
				outb(ICE1712_MULTI_CAPSTATUS, ICEMT(ice, IRQ));
			पूर्ण
		पूर्ण
		अगर (status & ICE1712_IRQ_FM)
			outb(ICE1712_IRQ_FM, ICEREG(ice, IRQSTAT));
		अगर (status & ICE1712_IRQ_PBKDS) अणु
			u32 idx;
			u16 pbkstatus;
			काष्ठा snd_pcm_substream *substream;
			pbkstatus = inw(ICEDS(ice, INTSTAT));
			/* dev_dbg(ice->card->dev, "pbkstatus = 0x%x\n", pbkstatus); */
			क्रम (idx = 0; idx < 6; idx++) अणु
				अगर ((pbkstatus & (3 << (idx * 2))) == 0)
					जारी;
				substream = ice->playback_con_substream_ds[idx];
				अगर (substream != शून्य)
					snd_pcm_period_elapsed(substream);
				outw(3 << (idx * 2), ICEDS(ice, INTSTAT));
			पूर्ण
			outb(ICE1712_IRQ_PBKDS, ICEREG(ice, IRQSTAT));
		पूर्ण
		अगर (status & ICE1712_IRQ_CONCAP) अणु
			अगर (ice->capture_con_substream)
				snd_pcm_period_elapsed(ice->capture_con_substream);
			outb(ICE1712_IRQ_CONCAP, ICEREG(ice, IRQSTAT));
		पूर्ण
		अगर (status & ICE1712_IRQ_CONPBK) अणु
			अगर (ice->playback_con_substream)
				snd_pcm_period_elapsed(ice->playback_con_substream);
			outb(ICE1712_IRQ_CONPBK, ICEREG(ice, IRQSTAT));
		पूर्ण
	पूर्ण
	वापस IRQ_RETVAL(handled);
पूर्ण


/*
 *  PCM part - consumer I/O
 */

अटल पूर्णांक snd_ice1712_playback_trigger(काष्ठा snd_pcm_substream *substream,
					पूर्णांक cmd)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	पूर्णांक result = 0;
	u32 पंचांगp;

	spin_lock(&ice->reg_lock);
	पंचांगp = snd_ice1712_पढ़ो(ice, ICE1712_IREG_PBK_CTRL);
	अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
		पंचांगp |= 1;
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		पंचांगp &= ~1;
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_PAUSE_PUSH) अणु
		पंचांगp |= 2;
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_PAUSE_RELEASE) अणु
		पंचांगp &= ~2;
	पूर्ण अन्यथा अणु
		result = -EINVAL;
	पूर्ण
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_PBK_CTRL, पंचांगp);
	spin_unlock(&ice->reg_lock);
	वापस result;
पूर्ण

अटल पूर्णांक snd_ice1712_playback_ds_trigger(काष्ठा snd_pcm_substream *substream,
					   पूर्णांक cmd)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	पूर्णांक result = 0;
	u32 पंचांगp;

	spin_lock(&ice->reg_lock);
	पंचांगp = snd_ice1712_ds_पढ़ो(ice, substream->number * 2, ICE1712_DSC_CONTROL);
	अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
		पंचांगp |= 1;
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		पंचांगp &= ~1;
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_PAUSE_PUSH) अणु
		पंचांगp |= 2;
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_PAUSE_RELEASE) अणु
		पंचांगp &= ~2;
	पूर्ण अन्यथा अणु
		result = -EINVAL;
	पूर्ण
	snd_ice1712_ds_ग_लिखो(ice, substream->number * 2, ICE1712_DSC_CONTROL, पंचांगp);
	spin_unlock(&ice->reg_lock);
	वापस result;
पूर्ण

अटल पूर्णांक snd_ice1712_capture_trigger(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	पूर्णांक result = 0;
	u8 पंचांगp;

	spin_lock(&ice->reg_lock);
	पंचांगp = snd_ice1712_पढ़ो(ice, ICE1712_IREG_CAP_CTRL);
	अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
		पंचांगp |= 1;
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		पंचांगp &= ~1;
	पूर्ण अन्यथा अणु
		result = -EINVAL;
	पूर्ण
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_CAP_CTRL, पंचांगp);
	spin_unlock(&ice->reg_lock);
	वापस result;
पूर्ण

अटल पूर्णांक snd_ice1712_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	u32 period_size, buf_size, rate, पंचांगp;

	period_size = (snd_pcm_lib_period_bytes(substream) >> 2) - 1;
	buf_size = snd_pcm_lib_buffer_bytes(substream) - 1;
	पंचांगp = 0x0000;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		पंचांगp |= 0x10;
	अगर (runसमय->channels == 2)
		पंचांगp |= 0x08;
	rate = (runसमय->rate * 8192) / 375;
	अगर (rate > 0x000fffff)
		rate = 0x000fffff;
	spin_lock_irq(&ice->reg_lock);
	outb(0, ice->ddma_port + 15);
	outb(ICE1712_DMA_MODE_WRITE | ICE1712_DMA_AUTOINIT, ice->ddma_port + 0x0b);
	outl(runसमय->dma_addr, ice->ddma_port + 0);
	outw(buf_size, ice->ddma_port + 4);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_PBK_RATE_LO, rate & 0xff);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_PBK_RATE_MID, (rate >> 8) & 0xff);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_PBK_RATE_HI, (rate >> 16) & 0xff);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_PBK_CTRL, पंचांगp);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_PBK_COUNT_LO, period_size & 0xff);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_PBK_COUNT_HI, period_size >> 8);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_PBK_LEFT, 0);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_PBK_RIGHT, 0);
	spin_unlock_irq(&ice->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_playback_ds_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	u32 period_size, rate, पंचांगp, chn;

	period_size = snd_pcm_lib_period_bytes(substream) - 1;
	पंचांगp = 0x0064;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		पंचांगp &= ~0x04;
	अगर (runसमय->channels == 2)
		पंचांगp |= 0x08;
	rate = (runसमय->rate * 8192) / 375;
	अगर (rate > 0x000fffff)
		rate = 0x000fffff;
	ice->playback_con_active_buf[substream->number] = 0;
	ice->playback_con_virt_addr[substream->number] = runसमय->dma_addr;
	chn = substream->number * 2;
	spin_lock_irq(&ice->reg_lock);
	snd_ice1712_ds_ग_लिखो(ice, chn, ICE1712_DSC_ADDR0, runसमय->dma_addr);
	snd_ice1712_ds_ग_लिखो(ice, chn, ICE1712_DSC_COUNT0, period_size);
	snd_ice1712_ds_ग_लिखो(ice, chn, ICE1712_DSC_ADDR1, runसमय->dma_addr + (runसमय->periods > 1 ? period_size + 1 : 0));
	snd_ice1712_ds_ग_लिखो(ice, chn, ICE1712_DSC_COUNT1, period_size);
	snd_ice1712_ds_ग_लिखो(ice, chn, ICE1712_DSC_RATE, rate);
	snd_ice1712_ds_ग_लिखो(ice, chn, ICE1712_DSC_VOLUME, 0);
	snd_ice1712_ds_ग_लिखो(ice, chn, ICE1712_DSC_CONTROL, पंचांगp);
	अगर (runसमय->channels == 2) अणु
		snd_ice1712_ds_ग_लिखो(ice, chn + 1, ICE1712_DSC_RATE, rate);
		snd_ice1712_ds_ग_लिखो(ice, chn + 1, ICE1712_DSC_VOLUME, 0);
	पूर्ण
	spin_unlock_irq(&ice->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	u32 period_size, buf_size;
	u8 पंचांगp;

	period_size = (snd_pcm_lib_period_bytes(substream) >> 2) - 1;
	buf_size = snd_pcm_lib_buffer_bytes(substream) - 1;
	पंचांगp = 0x06;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		पंचांगp &= ~0x04;
	अगर (runसमय->channels == 2)
		पंचांगp &= ~0x02;
	spin_lock_irq(&ice->reg_lock);
	outl(ice->capture_con_virt_addr = runसमय->dma_addr, ICEREG(ice, CONCAP_ADDR));
	outw(buf_size, ICEREG(ice, CONCAP_COUNT));
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_CAP_COUNT_HI, period_size >> 8);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_CAP_COUNT_LO, period_size & 0xff);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_CAP_CTRL, पंचांगp);
	spin_unlock_irq(&ice->reg_lock);
	snd_ac97_set_rate(ice->ac97, AC97_PCM_LR_ADC_RATE, runसमय->rate);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_ice1712_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	माप_प्रकार ptr;

	अगर (!(snd_ice1712_पढ़ो(ice, ICE1712_IREG_PBK_CTRL) & 1))
		वापस 0;
	ptr = runसमय->buffer_size - inw(ice->ddma_port + 4);
	ptr = bytes_to_frames(substream->runसमय, ptr);
	अगर (ptr == runसमय->buffer_size)
		ptr = 0;
	वापस ptr;
पूर्ण

अटल snd_pcm_uframes_t snd_ice1712_playback_ds_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	u8 addr;
	माप_प्रकार ptr;

	अगर (!(snd_ice1712_ds_पढ़ो(ice, substream->number * 2, ICE1712_DSC_CONTROL) & 1))
		वापस 0;
	अगर (ice->playback_con_active_buf[substream->number])
		addr = ICE1712_DSC_ADDR1;
	अन्यथा
		addr = ICE1712_DSC_ADDR0;
	ptr = snd_ice1712_ds_पढ़ो(ice, substream->number * 2, addr) -
		ice->playback_con_virt_addr[substream->number];
	ptr = bytes_to_frames(substream->runसमय, ptr);
	अगर (ptr == substream->runसमय->buffer_size)
		ptr = 0;
	वापस ptr;
पूर्ण

अटल snd_pcm_uframes_t snd_ice1712_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	अगर (!(snd_ice1712_पढ़ो(ice, ICE1712_IREG_CAP_CTRL) & 1))
		वापस 0;
	ptr = inl(ICEREG(ice, CONCAP_ADDR)) - ice->capture_con_virt_addr;
	ptr = bytes_to_frames(substream->runसमय, ptr);
	अगर (ptr == substream->runसमय->buffer_size)
		ptr = 0;
	वापस ptr;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_ice1712_playback = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_PAUSE),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(64*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(64*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_ice1712_playback_ds = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_PAUSE),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		2,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_ice1712_capture = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(64*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(64*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक snd_ice1712_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	ice->playback_con_substream = substream;
	runसमय->hw = snd_ice1712_playback;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_playback_ds_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	u32 पंचांगp;

	ice->playback_con_substream_ds[substream->number] = substream;
	runसमय->hw = snd_ice1712_playback_ds;
	spin_lock_irq(&ice->reg_lock);
	पंचांगp = inw(ICEDS(ice, INTMASK)) & ~(1 << (substream->number * 2));
	outw(पंचांगp, ICEDS(ice, INTMASK));
	spin_unlock_irq(&ice->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	ice->capture_con_substream = substream;
	runसमय->hw = snd_ice1712_capture;
	runसमय->hw.rates = ice->ac97->rates[AC97_RATES_ADC];
	अगर (!(runसमय->hw.rates & SNDRV_PCM_RATE_8000))
		runसमय->hw.rate_min = 48000;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	ice->playback_con_substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_playback_ds_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	u32 पंचांगp;

	spin_lock_irq(&ice->reg_lock);
	पंचांगp = inw(ICEDS(ice, INTMASK)) | (3 << (substream->number * 2));
	outw(पंचांगp, ICEDS(ice, INTMASK));
	spin_unlock_irq(&ice->reg_lock);
	ice->playback_con_substream_ds[substream->number] = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	ice->capture_con_substream = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_ice1712_playback_ops = अणु
	.खोलो =		snd_ice1712_playback_खोलो,
	.बंद =	snd_ice1712_playback_बंद,
	.prepare =	snd_ice1712_playback_prepare,
	.trigger =	snd_ice1712_playback_trigger,
	.poपूर्णांकer =	snd_ice1712_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ice1712_playback_ds_ops = अणु
	.खोलो =		snd_ice1712_playback_ds_खोलो,
	.बंद =	snd_ice1712_playback_ds_बंद,
	.prepare =	snd_ice1712_playback_ds_prepare,
	.trigger =	snd_ice1712_playback_ds_trigger,
	.poपूर्णांकer =	snd_ice1712_playback_ds_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ice1712_capture_ops = अणु
	.खोलो =		snd_ice1712_capture_खोलो,
	.बंद =	snd_ice1712_capture_बंद,
	.prepare =	snd_ice1712_capture_prepare,
	.trigger =	snd_ice1712_capture_trigger,
	.poपूर्णांकer =	snd_ice1712_capture_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_ice1712_pcm(काष्ठा snd_ice1712 *ice, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(ice->card, "ICE1712 consumer", device, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ice1712_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ice1712_capture_ops);

	pcm->निजी_data = ice;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "ICE1712 consumer");
	ice->pcm = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &ice->pci->dev, 64*1024, 64*1024);

	dev_warn(ice->card->dev,
		 "Consumer PCM code does not work well at the moment --jk\n");

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pcm_ds(काष्ठा snd_ice1712 *ice, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(ice->card, "ICE1712 consumer (DS)", device, 6, 0, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ice1712_playback_ds_ops);

	pcm->निजी_data = ice;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "ICE1712 consumer (DS)");
	ice->pcm_ds = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &ice->pci->dev, 64*1024, 128*1024);

	वापस 0;
पूर्ण

/*
 *  PCM code - professional part (multitrack)
 */

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु 8000, 9600, 11025, 12000, 16000, 22050, 24000,
				32000, 44100, 48000, 64000, 88200, 96000 पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list = rates,
	.mask = 0,
पूर्ण;

अटल पूर्णांक snd_ice1712_pro_trigger(काष्ठा snd_pcm_substream *substream,
				   पूर्णांक cmd)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	अणु
		अचिन्हित पूर्णांक what;
		अचिन्हित पूर्णांक old;
		अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
			वापस -EINVAL;
		what = ICE1712_PLAYBACK_PAUSE;
		snd_pcm_trigger_करोne(substream, substream);
		spin_lock(&ice->reg_lock);
		old = inl(ICEMT(ice, PLAYBACK_CONTROL));
		अगर (cmd == SNDRV_PCM_TRIGGER_PAUSE_PUSH)
			old |= what;
		अन्यथा
			old &= ~what;
		outl(old, ICEMT(ice, PLAYBACK_CONTROL));
		spin_unlock(&ice->reg_lock);
		अवरोध;
	पूर्ण
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_STOP:
	अणु
		अचिन्हित पूर्णांक what = 0;
		अचिन्हित पूर्णांक old;
		काष्ठा snd_pcm_substream *s;

		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			अगर (s == ice->playback_pro_substream) अणु
				what |= ICE1712_PLAYBACK_START;
				snd_pcm_trigger_करोne(s, substream);
			पूर्ण अन्यथा अगर (s == ice->capture_pro_substream) अणु
				what |= ICE1712_CAPTURE_START_SHADOW;
				snd_pcm_trigger_करोne(s, substream);
			पूर्ण
		पूर्ण
		spin_lock(&ice->reg_lock);
		old = inl(ICEMT(ice, PLAYBACK_CONTROL));
		अगर (cmd == SNDRV_PCM_TRIGGER_START)
			old |= what;
		अन्यथा
			old &= ~what;
		outl(old, ICEMT(ice, PLAYBACK_CONTROL));
		spin_unlock(&ice->reg_lock);
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 */
अटल व्योम snd_ice1712_set_pro_rate(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate, पूर्णांक क्रमce)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर val, old;
	अचिन्हित पूर्णांक i;

	चयन (rate) अणु
	हाल 8000: val = 6; अवरोध;
	हाल 9600: val = 3; अवरोध;
	हाल 11025: val = 10; अवरोध;
	हाल 12000: val = 2; अवरोध;
	हाल 16000: val = 5; अवरोध;
	हाल 22050: val = 9; अवरोध;
	हाल 24000: val = 1; अवरोध;
	हाल 32000: val = 4; अवरोध;
	हाल 44100: val = 8; अवरोध;
	हाल 48000: val = 0; अवरोध;
	हाल 64000: val = 15; अवरोध;
	हाल 88200: val = 11; अवरोध;
	हाल 96000: val = 7; अवरोध;
	शेष:
		snd_BUG();
		val = 0;
		rate = 48000;
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&ice->reg_lock, flags);
	अगर (inb(ICEMT(ice, PLAYBACK_CONTROL)) & (ICE1712_CAPTURE_START_SHADOW|
						 ICE1712_PLAYBACK_PAUSE|
						 ICE1712_PLAYBACK_START)) अणु
__out:
		spin_unlock_irqrestore(&ice->reg_lock, flags);
		वापस;
	पूर्ण
	अगर (!क्रमce && is_pro_rate_locked(ice))
		जाओ __out;

	old = inb(ICEMT(ice, RATE));
	अगर (!क्रमce && old == val)
		जाओ __out;

	ice->cur_rate = rate;
	outb(val, ICEMT(ice, RATE));
	spin_unlock_irqrestore(&ice->reg_lock, flags);

	अगर (ice->gpio.set_pro_rate)
		ice->gpio.set_pro_rate(ice, rate);
	क्रम (i = 0; i < ice->akm_codecs; i++) अणु
		अगर (ice->akm[i].ops.set_rate_val)
			ice->akm[i].ops.set_rate_val(&ice->akm[i], rate);
	पूर्ण
	अगर (ice->spdअगर.ops.setup_rate)
		ice->spdअगर.ops.setup_rate(ice, rate);
पूर्ण

अटल पूर्णांक snd_ice1712_playback_pro_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	ice->playback_pro_size = snd_pcm_lib_buffer_bytes(substream);
	spin_lock_irq(&ice->reg_lock);
	outl(substream->runसमय->dma_addr, ICEMT(ice, PLAYBACK_ADDR));
	outw((ice->playback_pro_size >> 2) - 1, ICEMT(ice, PLAYBACK_SIZE));
	outw((snd_pcm_lib_period_bytes(substream) >> 2) - 1, ICEMT(ice, PLAYBACK_COUNT));
	spin_unlock_irq(&ice->reg_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_playback_pro_hw_params(काष्ठा snd_pcm_substream *substream,
					      काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	snd_ice1712_set_pro_rate(ice, params_rate(hw_params), 0);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_capture_pro_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	ice->capture_pro_size = snd_pcm_lib_buffer_bytes(substream);
	spin_lock_irq(&ice->reg_lock);
	outl(substream->runसमय->dma_addr, ICEMT(ice, CAPTURE_ADDR));
	outw((ice->capture_pro_size >> 2) - 1, ICEMT(ice, CAPTURE_SIZE));
	outw((snd_pcm_lib_period_bytes(substream) >> 2) - 1, ICEMT(ice, CAPTURE_COUNT));
	spin_unlock_irq(&ice->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_capture_pro_hw_params(काष्ठा snd_pcm_substream *substream,
					     काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	snd_ice1712_set_pro_rate(ice, params_rate(hw_params), 0);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_ice1712_playback_pro_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	अगर (!(inl(ICEMT(ice, PLAYBACK_CONTROL)) & ICE1712_PLAYBACK_START))
		वापस 0;
	ptr = ice->playback_pro_size - (inw(ICEMT(ice, PLAYBACK_SIZE)) << 2);
	ptr = bytes_to_frames(substream->runसमय, ptr);
	अगर (ptr == substream->runसमय->buffer_size)
		ptr = 0;
	वापस ptr;
पूर्ण

अटल snd_pcm_uframes_t snd_ice1712_capture_pro_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	अगर (!(inl(ICEMT(ice, PLAYBACK_CONTROL)) & ICE1712_CAPTURE_START_SHADOW))
		वापस 0;
	ptr = ice->capture_pro_size - (inw(ICEMT(ice, CAPTURE_SIZE)) << 2);
	ptr = bytes_to_frames(substream->runसमय, ptr);
	अगर (ptr == substream->runसमय->buffer_size)
		ptr = 0;
	वापस ptr;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_ice1712_playback_pro = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_LE,
	.rates =		SNDRV_PCM_RATE_KNOT | SNDRV_PCM_RATE_8000_96000,
	.rate_min =		4000,
	.rate_max =		96000,
	.channels_min =		10,
	.channels_max =		10,
	.buffer_bytes_max =	(256*1024),
	.period_bytes_min =	10 * 4 * 2,
	.period_bytes_max =	131040,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_ice1712_capture_pro = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_LE,
	.rates =		SNDRV_PCM_RATE_KNOT | SNDRV_PCM_RATE_8000_96000,
	.rate_min =		4000,
	.rate_max =		96000,
	.channels_min =		12,
	.channels_max =		12,
	.buffer_bytes_max =	(256*1024),
	.period_bytes_min =	12 * 4 * 2,
	.period_bytes_max =	131040,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक snd_ice1712_playback_pro_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	ice->playback_pro_substream = substream;
	runसमय->hw = snd_ice1712_playback_pro;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE, &hw_स्थिरraपूर्णांकs_rates);
	अगर (is_pro_rate_locked(ice)) अणु
		runसमय->hw.rate_min = PRO_RATE_DEFAULT;
		runसमय->hw.rate_max = PRO_RATE_DEFAULT;
	पूर्ण

	अगर (ice->spdअगर.ops.खोलो)
		ice->spdअगर.ops.खोलो(ice, substream);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_capture_pro_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	ice->capture_pro_substream = substream;
	runसमय->hw = snd_ice1712_capture_pro;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE, &hw_स्थिरraपूर्णांकs_rates);
	अगर (is_pro_rate_locked(ice)) अणु
		runसमय->hw.rate_min = PRO_RATE_DEFAULT;
		runसमय->hw.rate_max = PRO_RATE_DEFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_playback_pro_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	अगर (PRO_RATE_RESET)
		snd_ice1712_set_pro_rate(ice, PRO_RATE_DEFAULT, 0);
	ice->playback_pro_substream = शून्य;
	अगर (ice->spdअगर.ops.बंद)
		ice->spdअगर.ops.बंद(ice, substream);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_capture_pro_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	अगर (PRO_RATE_RESET)
		snd_ice1712_set_pro_rate(ice, PRO_RATE_DEFAULT, 0);
	ice->capture_pro_substream = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_ice1712_playback_pro_ops = अणु
	.खोलो =		snd_ice1712_playback_pro_खोलो,
	.बंद =	snd_ice1712_playback_pro_बंद,
	.hw_params =	snd_ice1712_playback_pro_hw_params,
	.prepare =	snd_ice1712_playback_pro_prepare,
	.trigger =	snd_ice1712_pro_trigger,
	.poपूर्णांकer =	snd_ice1712_playback_pro_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ice1712_capture_pro_ops = अणु
	.खोलो =		snd_ice1712_capture_pro_खोलो,
	.बंद =	snd_ice1712_capture_pro_बंद,
	.hw_params =	snd_ice1712_capture_pro_hw_params,
	.prepare =	snd_ice1712_capture_pro_prepare,
	.trigger =	snd_ice1712_pro_trigger,
	.poपूर्णांकer =	snd_ice1712_capture_pro_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_ice1712_pcm_profi(काष्ठा snd_ice1712 *ice, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(ice->card, "ICE1712 multi", device, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ice1712_playback_pro_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ice1712_capture_pro_ops);

	pcm->निजी_data = ice;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "ICE1712 multi");

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &ice->pci->dev, 256*1024, 256*1024);

	ice->pcm_pro = pcm;

	अगर (ice->cs8427) अणु
		/* assign channels to iec958 */
		err = snd_cs8427_iec958_build(ice->cs8427,
					      pcm->streams[0].substream,
					      pcm->streams[1].substream);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस snd_ice1712_build_pro_mixer(ice);
पूर्ण

/*
 *  Mixer section
 */

अटल व्योम snd_ice1712_update_volume(काष्ठा snd_ice1712 *ice, पूर्णांक index)
अणु
	अचिन्हित पूर्णांक vol = ice->pro_volumes[index];
	अचिन्हित लघु val = 0;

	val |= (vol & 0x8000) == 0 ? (96 - (vol & 0x7f)) : 0x7f;
	val |= ((vol & 0x80000000) == 0 ? (96 - ((vol >> 16) & 0x7f)) : 0x7f) << 8;
	outb(index, ICEMT(ice, MONITOR_INDEX));
	outw(val, ICEMT(ice, MONITOR_VOLUME));
पूर्ण

#घोषणा snd_ice1712_pro_mixer_चयन_info	snd_ctl_boolean_stereo_info

अटल पूर्णांक snd_ice1712_pro_mixer_चयन_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक priv_idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id) +
		kcontrol->निजी_value;

	spin_lock_irq(&ice->reg_lock);
	ucontrol->value.पूर्णांकeger.value[0] =
		!((ice->pro_volumes[priv_idx] >> 15) & 1);
	ucontrol->value.पूर्णांकeger.value[1] =
		!((ice->pro_volumes[priv_idx] >> 31) & 1);
	spin_unlock_irq(&ice->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_mixer_चयन_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक priv_idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id) +
		kcontrol->निजी_value;
	अचिन्हित पूर्णांक nval, change;

	nval = (ucontrol->value.पूर्णांकeger.value[0] ? 0 : 0x00008000) |
	       (ucontrol->value.पूर्णांकeger.value[1] ? 0 : 0x80000000);
	spin_lock_irq(&ice->reg_lock);
	nval |= ice->pro_volumes[priv_idx] & ~0x80008000;
	change = nval != ice->pro_volumes[priv_idx];
	ice->pro_volumes[priv_idx] = nval;
	snd_ice1712_update_volume(ice, priv_idx);
	spin_unlock_irq(&ice->reg_lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_mixer_volume_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 96;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_mixer_volume_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक priv_idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id) +
		kcontrol->निजी_value;

	spin_lock_irq(&ice->reg_lock);
	ucontrol->value.पूर्णांकeger.value[0] =
		(ice->pro_volumes[priv_idx] >> 0) & 127;
	ucontrol->value.पूर्णांकeger.value[1] =
		(ice->pro_volumes[priv_idx] >> 16) & 127;
	spin_unlock_irq(&ice->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_mixer_volume_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक priv_idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id) +
		kcontrol->निजी_value;
	अचिन्हित पूर्णांक nval, change;

	nval = (ucontrol->value.पूर्णांकeger.value[0] & 127) |
	       ((ucontrol->value.पूर्णांकeger.value[1] & 127) << 16);
	spin_lock_irq(&ice->reg_lock);
	nval |= ice->pro_volumes[priv_idx] & ~0x007f007f;
	change = nval != ice->pro_volumes[priv_idx];
	ice->pro_volumes[priv_idx] = nval;
	snd_ice1712_update_volume(ice, priv_idx);
	spin_unlock_irq(&ice->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_playback, -14400, 150, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_multi_playback_ctrls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Multi Playback Switch",
		.info = snd_ice1712_pro_mixer_चयन_info,
		.get = snd_ice1712_pro_mixer_चयन_get,
		.put = snd_ice1712_pro_mixer_चयन_put,
		.निजी_value = 0,
		.count = 10,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Multi Playback Volume",
		.info = snd_ice1712_pro_mixer_volume_info,
		.get = snd_ice1712_pro_mixer_volume_get,
		.put = snd_ice1712_pro_mixer_volume_put,
		.निजी_value = 0,
		.count = 10,
		.tlv = अणु .p = db_scale_playback पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_multi_capture_analog_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "H/W Multi Capture Switch",
	.info = snd_ice1712_pro_mixer_चयन_info,
	.get = snd_ice1712_pro_mixer_चयन_get,
	.put = snd_ice1712_pro_mixer_चयन_put,
	.निजी_value = 10,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_multi_capture_spdअगर_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = SNDRV_CTL_NAME_IEC958("Multi ", CAPTURE, SWITCH),
	.info = snd_ice1712_pro_mixer_चयन_info,
	.get = snd_ice1712_pro_mixer_चयन_get,
	.put = snd_ice1712_pro_mixer_चयन_put,
	.निजी_value = 18,
	.count = 2,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_multi_capture_analog_volume = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.name = "H/W Multi Capture Volume",
	.info = snd_ice1712_pro_mixer_volume_info,
	.get = snd_ice1712_pro_mixer_volume_get,
	.put = snd_ice1712_pro_mixer_volume_put,
	.निजी_value = 10,
	.tlv = अणु .p = db_scale_playback पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_multi_capture_spdअगर_volume = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = SNDRV_CTL_NAME_IEC958("Multi ", CAPTURE, VOLUME),
	.info = snd_ice1712_pro_mixer_volume_info,
	.get = snd_ice1712_pro_mixer_volume_get,
	.put = snd_ice1712_pro_mixer_volume_put,
	.निजी_value = 18,
	.count = 2,
पूर्ण;

अटल पूर्णांक snd_ice1712_build_pro_mixer(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा snd_card *card = ice->card;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	/* multi-channel mixer */
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_ice1712_multi_playback_ctrls); idx++) अणु
		err = snd_ctl_add(card, snd_ctl_new1(&snd_ice1712_multi_playback_ctrls[idx], ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (ice->num_total_adcs > 0) अणु
		काष्ठा snd_kcontrol_new पंचांगp = snd_ice1712_multi_capture_analog_चयन;
		पंचांगp.count = ice->num_total_adcs;
		err = snd_ctl_add(card, snd_ctl_new1(&पंचांगp, ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = snd_ctl_add(card, snd_ctl_new1(&snd_ice1712_multi_capture_spdअगर_चयन, ice));
	अगर (err < 0)
		वापस err;

	अगर (ice->num_total_adcs > 0) अणु
		काष्ठा snd_kcontrol_new पंचांगp = snd_ice1712_multi_capture_analog_volume;
		पंचांगp.count = ice->num_total_adcs;
		err = snd_ctl_add(card, snd_ctl_new1(&पंचांगp, ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = snd_ctl_add(card, snd_ctl_new1(&snd_ice1712_multi_capture_spdअगर_volume, ice));
	अगर (err < 0)
		वापस err;

	/* initialize volumes */
	क्रम (idx = 0; idx < 10; idx++) अणु
		ice->pro_volumes[idx] = 0x80008000;	/* mute */
		snd_ice1712_update_volume(ice, idx);
	पूर्ण
	क्रम (idx = 10; idx < 10 + ice->num_total_adcs; idx++) अणु
		ice->pro_volumes[idx] = 0x80008000;	/* mute */
		snd_ice1712_update_volume(ice, idx);
	पूर्ण
	क्रम (idx = 18; idx < 20; idx++) अणु
		ice->pro_volumes[idx] = 0x80008000;	/* mute */
		snd_ice1712_update_volume(ice, idx);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_ice1712_mixer_मुक्त_ac97(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_ice1712 *ice = ac97->निजी_data;
	ice->ac97 = शून्य;
पूर्ण

अटल पूर्णांक snd_ice1712_ac97_mixer(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक err, bus_num = 0;
	काष्ठा snd_ac97_ढाँचा ac97;
	काष्ठा snd_ac97_bus *pbus;
	अटल स्थिर काष्ठा snd_ac97_bus_ops con_ops = अणु
		.ग_लिखो = snd_ice1712_ac97_ग_लिखो,
		.पढ़ो = snd_ice1712_ac97_पढ़ो,
	पूर्ण;
	अटल स्थिर काष्ठा snd_ac97_bus_ops pro_ops = अणु
		.ग_लिखो = snd_ice1712_pro_ac97_ग_लिखो,
		.पढ़ो = snd_ice1712_pro_ac97_पढ़ो,
	पूर्ण;

	अगर (ice_has_con_ac97(ice)) अणु
		err = snd_ac97_bus(ice->card, bus_num++, &con_ops, शून्य, &pbus);
		अगर (err < 0)
			वापस err;
		स_रखो(&ac97, 0, माप(ac97));
		ac97.निजी_data = ice;
		ac97.निजी_मुक्त = snd_ice1712_mixer_मुक्त_ac97;
		err = snd_ac97_mixer(pbus, &ac97, &ice->ac97);
		अगर (err < 0)
			dev_warn(ice->card->dev,
				 "cannot initialize ac97 for consumer, skipped\n");
		अन्यथा अणु
			वापस snd_ctl_add(ice->card,
			snd_ctl_new1(&snd_ice1712_mixer_digmix_route_ac97,
				     ice));
		पूर्ण
	पूर्ण

	अगर (!(ice->eeprom.data[ICE_EEP1_ACLINK] & ICE1712_CFG_PRO_I2S)) अणु
		err = snd_ac97_bus(ice->card, bus_num, &pro_ops, शून्य, &pbus);
		अगर (err < 0)
			वापस err;
		स_रखो(&ac97, 0, माप(ac97));
		ac97.निजी_data = ice;
		ac97.निजी_मुक्त = snd_ice1712_mixer_मुक्त_ac97;
		err = snd_ac97_mixer(pbus, &ac97, &ice->ac97);
		अगर (err < 0)
			dev_warn(ice->card->dev,
				 "cannot initialize pro ac97, skipped\n");
		अन्यथा
			वापस 0;
	पूर्ण
	/* I2S mixer only */
	म_जोड़ो(ice->card->mixername, "ICE1712 - multitrack");
	वापस 0;
पूर्ण

/*
 *
 */

अटल अंतरभूत अचिन्हित पूर्णांक eeprom_द्विगुन(काष्ठा snd_ice1712 *ice, पूर्णांक idx)
अणु
	वापस (अचिन्हित पूर्णांक)ice->eeprom.data[idx] | ((अचिन्हित पूर्णांक)ice->eeprom.data[idx + 1] << 8);
पूर्ण

अटल व्योम snd_ice1712_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ice1712 *ice = entry->निजी_data;
	अचिन्हित पूर्णांक idx;

	snd_iम_लिखो(buffer, "%s\n\n", ice->card->दीर्घname);
	snd_iम_लिखो(buffer, "EEPROM:\n");

	snd_iम_लिखो(buffer, "  Subvendor        : 0x%x\n", ice->eeprom.subvenकरोr);
	snd_iम_लिखो(buffer, "  Size             : %i bytes\n", ice->eeprom.size);
	snd_iम_लिखो(buffer, "  Version          : %i\n", ice->eeprom.version);
	snd_iम_लिखो(buffer, "  Codec            : 0x%x\n", ice->eeprom.data[ICE_EEP1_CODEC]);
	snd_iम_लिखो(buffer, "  ACLink           : 0x%x\n", ice->eeprom.data[ICE_EEP1_ACLINK]);
	snd_iम_लिखो(buffer, "  I2S ID           : 0x%x\n", ice->eeprom.data[ICE_EEP1_I2SID]);
	snd_iम_लिखो(buffer, "  S/PDIF           : 0x%x\n", ice->eeprom.data[ICE_EEP1_SPDIF]);
	snd_iम_लिखो(buffer, "  GPIO mask        : 0x%x\n", ice->eeprom.gpiomask);
	snd_iम_लिखो(buffer, "  GPIO state       : 0x%x\n", ice->eeprom.gpiostate);
	snd_iम_लिखो(buffer, "  GPIO direction   : 0x%x\n", ice->eeprom.gpiodir);
	snd_iम_लिखो(buffer, "  AC'97 main       : 0x%x\n", eeprom_द्विगुन(ice, ICE_EEP1_AC97_MAIN_LO));
	snd_iम_लिखो(buffer, "  AC'97 pcm        : 0x%x\n", eeprom_द्विगुन(ice, ICE_EEP1_AC97_PCM_LO));
	snd_iम_लिखो(buffer, "  AC'97 record     : 0x%x\n", eeprom_द्विगुन(ice, ICE_EEP1_AC97_REC_LO));
	snd_iम_लिखो(buffer, "  AC'97 record src : 0x%x\n", ice->eeprom.data[ICE_EEP1_AC97_RECSRC]);
	क्रम (idx = 0; idx < 4; idx++)
		snd_iम_लिखो(buffer, "  DAC ID #%i        : 0x%x\n", idx, ice->eeprom.data[ICE_EEP1_DAC_ID + idx]);
	क्रम (idx = 0; idx < 4; idx++)
		snd_iम_लिखो(buffer, "  ADC ID #%i        : 0x%x\n", idx, ice->eeprom.data[ICE_EEP1_ADC_ID + idx]);
	क्रम (idx = 0x1c; idx < ice->eeprom.size; idx++)
		snd_iम_लिखो(buffer, "  Extra #%02i        : 0x%x\n", idx, ice->eeprom.data[idx]);

	snd_iम_लिखो(buffer, "\nRegisters:\n");
	snd_iम_लिखो(buffer, "  PSDOUT03         : 0x%04x\n", (अचिन्हित)inw(ICEMT(ice, ROUTE_PSDOUT03)));
	snd_iम_लिखो(buffer, "  CAPTURE          : 0x%08x\n", inl(ICEMT(ice, ROUTE_CAPTURE)));
	snd_iम_लिखो(buffer, "  SPDOUT           : 0x%04x\n", (अचिन्हित)inw(ICEMT(ice, ROUTE_SPDOUT)));
	snd_iम_लिखो(buffer, "  RATE             : 0x%02x\n", (अचिन्हित)inb(ICEMT(ice, RATE)));
	snd_iम_लिखो(buffer, "  GPIO_DATA        : 0x%02x\n", (अचिन्हित)snd_ice1712_get_gpio_data(ice));
	snd_iम_लिखो(buffer, "  GPIO_WRITE_MASK  : 0x%02x\n", (अचिन्हित)snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_WRITE_MASK));
	snd_iम_लिखो(buffer, "  GPIO_DIRECTION   : 0x%02x\n", (अचिन्हित)snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_सूचीECTION));
पूर्ण

अटल व्योम snd_ice1712_proc_init(काष्ठा snd_ice1712 *ice)
अणु
	snd_card_ro_proc_new(ice->card, "ice1712", ice, snd_ice1712_proc_पढ़ो);
पूर्ण

/*
 *
 */

अटल पूर्णांक snd_ice1712_eeprom_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = माप(काष्ठा snd_ice1712_eeprom);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_eeprom_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	स_नकल(ucontrol->value.bytes.data, &ice->eeprom, माप(ice->eeprom));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_eeprom = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
	.name = "ICE1712 EEPROM",
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.info = snd_ice1712_eeprom_info,
	.get = snd_ice1712_eeprom_get
पूर्ण;

/*
 */
अटल पूर्णांक snd_ice1712_spdअगर_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_spdअगर_शेष_get(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अगर (ice->spdअगर.ops.शेष_get)
		ice->spdअगर.ops.शेष_get(ice, ucontrol);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_spdअगर_शेष_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अगर (ice->spdअगर.ops.शेष_put)
		वापस ice->spdअगर.ops.शेष_put(ice, ucontrol);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_spdअगर_शेष =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
	.info =		snd_ice1712_spdअगर_info,
	.get =		snd_ice1712_spdअगर_शेष_get,
	.put =		snd_ice1712_spdअगर_शेष_put
पूर्ण;

अटल पूर्णांक snd_ice1712_spdअगर_maskc_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अगर (ice->spdअगर.ops.शेष_get) अणु
		ucontrol->value.iec958.status[0] = IEC958_AES0_NONAUDIO |
						     IEC958_AES0_PROFESSIONAL |
						     IEC958_AES0_CON_NOT_COPYRIGHT |
						     IEC958_AES0_CON_EMPHASIS;
		ucontrol->value.iec958.status[1] = IEC958_AES1_CON_ORIGINAL |
						     IEC958_AES1_CON_CATEGORY;
		ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS;
	पूर्ण अन्यथा अणु
		ucontrol->value.iec958.status[0] = 0xff;
		ucontrol->value.iec958.status[1] = 0xff;
		ucontrol->value.iec958.status[2] = 0xff;
		ucontrol->value.iec958.status[3] = 0xff;
		ucontrol->value.iec958.status[4] = 0xff;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_spdअगर_maskp_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अगर (ice->spdअगर.ops.शेष_get) अणु
		ucontrol->value.iec958.status[0] = IEC958_AES0_NONAUDIO |
						     IEC958_AES0_PROFESSIONAL |
						     IEC958_AES0_PRO_FS |
						     IEC958_AES0_PRO_EMPHASIS;
		ucontrol->value.iec958.status[1] = IEC958_AES1_PRO_MODE;
	पूर्ण अन्यथा अणु
		ucontrol->value.iec958.status[0] = 0xff;
		ucontrol->value.iec958.status[1] = 0xff;
		ucontrol->value.iec958.status[2] = 0xff;
		ucontrol->value.iec958.status[3] = 0xff;
		ucontrol->value.iec958.status[4] = 0xff;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_spdअगर_maskc =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("", PLAYBACK, CON_MASK),
	.info =		snd_ice1712_spdअगर_info,
	.get =		snd_ice1712_spdअगर_maskc_get,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_spdअगर_maskp =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("", PLAYBACK, PRO_MASK),
	.info =		snd_ice1712_spdअगर_info,
	.get =		snd_ice1712_spdअगर_maskp_get,
पूर्ण;

अटल पूर्णांक snd_ice1712_spdअगर_stream_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अगर (ice->spdअगर.ops.stream_get)
		ice->spdअगर.ops.stream_get(ice, ucontrol);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_spdअगर_stream_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अगर (ice->spdअगर.ops.stream_put)
		वापस ice->spdअगर.ops.stream_put(ice, ucontrol);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_spdअगर_stream =
अणु
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_INACTIVE),
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("", PLAYBACK, PCM_STREAM),
	.info =		snd_ice1712_spdअगर_info,
	.get =		snd_ice1712_spdअगर_stream_get,
	.put =		snd_ice1712_spdअगर_stream_put
पूर्ण;

पूर्णांक snd_ice1712_gpio_get(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर mask = kcontrol->निजी_value & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value & (1<<24)) ? 1 : 0;

	snd_ice1712_save_gpio_status(ice);
	ucontrol->value.पूर्णांकeger.value[0] =
		(snd_ice1712_gpio_पढ़ो(ice) & mask ? 1 : 0) ^ invert;
	snd_ice1712_restore_gpio_status(ice);
	वापस 0;
पूर्ण

पूर्णांक snd_ice1712_gpio_put(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर mask = kcontrol->निजी_value & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value & (1<<24)) ? mask : 0;
	अचिन्हित पूर्णांक val, nval;

	अगर (kcontrol->निजी_value & (1 << 31))
		वापस -EPERM;
	nval = (ucontrol->value.पूर्णांकeger.value[0] ? mask : 0) ^ invert;
	snd_ice1712_save_gpio_status(ice);
	val = snd_ice1712_gpio_पढ़ो(ice);
	nval |= val & ~mask;
	अगर (val != nval)
		snd_ice1712_gpio_ग_लिखो(ice, nval);
	snd_ice1712_restore_gpio_status(ice);
	वापस val != nval;
पूर्ण

/*
 *  rate
 */
अटल पूर्णांक snd_ice1712_pro_पूर्णांकernal_घड़ी_info(काष्ठा snd_kcontrol *kcontrol,
					       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"8000",		/* 0: 6 */
		"9600",		/* 1: 3 */
		"11025",	/* 2: 10 */
		"12000",	/* 3: 2 */
		"16000",	/* 4: 5 */
		"22050",	/* 5: 9 */
		"24000",	/* 6: 1 */
		"32000",	/* 7: 4 */
		"44100",	/* 8: 8 */
		"48000",	/* 9: 0 */
		"64000",	/* 10: 15 */
		"88200",	/* 11: 11 */
		"96000",	/* 12: 7 */
		"IEC958 Input",	/* 13: -- */
	पूर्ण;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 14, texts);
पूर्ण

अटल पूर्णांक snd_ice1712_pro_पूर्णांकernal_घड़ी_get(काष्ठा snd_kcontrol *kcontrol,
					      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अटल स्थिर अचिन्हित अक्षर xlate[16] = अणु
		9, 6, 3, 1, 7, 4, 0, 12, 8, 5, 2, 11, 255, 255, 255, 10
	पूर्ण;
	अचिन्हित अक्षर val;

	spin_lock_irq(&ice->reg_lock);
	अगर (is_spdअगर_master(ice)) अणु
		ucontrol->value.क्रमागतerated.item[0] = 13;
	पूर्ण अन्यथा अणु
		val = xlate[inb(ICEMT(ice, RATE)) & 15];
		अगर (val == 255) अणु
			snd_BUG();
			val = 0;
		पूर्ण
		ucontrol->value.क्रमागतerated.item[0] = val;
	पूर्ण
	spin_unlock_irq(&ice->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_पूर्णांकernal_घड़ी_put(काष्ठा snd_kcontrol *kcontrol,
					      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अटल स्थिर अचिन्हित पूर्णांक xrate[13] = अणु
		8000, 9600, 11025, 12000, 16000, 22050, 24000,
		32000, 44100, 48000, 64000, 88200, 96000
	पूर्ण;
	अचिन्हित अक्षर oval;
	पूर्णांक change = 0;

	spin_lock_irq(&ice->reg_lock);
	oval = inb(ICEMT(ice, RATE));
	अगर (ucontrol->value.क्रमागतerated.item[0] == 13) अणु
		outb(oval | ICE1712_SPDIF_MASTER, ICEMT(ice, RATE));
	पूर्ण अन्यथा अणु
		PRO_RATE_DEFAULT = xrate[ucontrol->value.पूर्णांकeger.value[0] % 13];
		spin_unlock_irq(&ice->reg_lock);
		snd_ice1712_set_pro_rate(ice, PRO_RATE_DEFAULT, 1);
		spin_lock_irq(&ice->reg_lock);
	पूर्ण
	change = inb(ICEMT(ice, RATE)) != oval;
	spin_unlock_irq(&ice->reg_lock);

	अगर ((oval & ICE1712_SPDIF_MASTER) !=
	    (inb(ICEMT(ice, RATE)) & ICE1712_SPDIF_MASTER))
		snd_ice1712_set_input_घड़ी_source(ice, is_spdअगर_master(ice));

	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_pro_पूर्णांकernal_घड़ी = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Multi Track Internal Clock",
	.info = snd_ice1712_pro_पूर्णांकernal_घड़ी_info,
	.get = snd_ice1712_pro_पूर्णांकernal_घड़ी_get,
	.put = snd_ice1712_pro_पूर्णांकernal_घड़ी_put
पूर्ण;

अटल पूर्णांक snd_ice1712_pro_पूर्णांकernal_घड़ी_शेष_info(काष्ठा snd_kcontrol *kcontrol,
						       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"8000",		/* 0: 6 */
		"9600",		/* 1: 3 */
		"11025",	/* 2: 10 */
		"12000",	/* 3: 2 */
		"16000",	/* 4: 5 */
		"22050",	/* 5: 9 */
		"24000",	/* 6: 1 */
		"32000",	/* 7: 4 */
		"44100",	/* 8: 8 */
		"48000",	/* 9: 0 */
		"64000",	/* 10: 15 */
		"88200",	/* 11: 11 */
		"96000",	/* 12: 7 */
		/* "IEC958 Input",	13: -- */
	पूर्ण;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 13, texts);
पूर्ण

अटल पूर्णांक snd_ice1712_pro_पूर्णांकernal_घड़ी_शेष_get(काष्ठा snd_kcontrol *kcontrol,
						      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक val;
	अटल स्थिर अचिन्हित पूर्णांक xrate[13] = अणु
		8000, 9600, 11025, 12000, 16000, 22050, 24000,
		32000, 44100, 48000, 64000, 88200, 96000
	पूर्ण;

	क्रम (val = 0; val < 13; val++) अणु
		अगर (xrate[val] == PRO_RATE_DEFAULT)
			अवरोध;
	पूर्ण

	ucontrol->value.क्रमागतerated.item[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_पूर्णांकernal_घड़ी_शेष_put(काष्ठा snd_kcontrol *kcontrol,
						      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अटल स्थिर अचिन्हित पूर्णांक xrate[13] = अणु
		8000, 9600, 11025, 12000, 16000, 22050, 24000,
		32000, 44100, 48000, 64000, 88200, 96000
	पूर्ण;
	अचिन्हित अक्षर oval;
	पूर्णांक change = 0;

	oval = PRO_RATE_DEFAULT;
	PRO_RATE_DEFAULT = xrate[ucontrol->value.पूर्णांकeger.value[0] % 13];
	change = PRO_RATE_DEFAULT != oval;

	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_pro_पूर्णांकernal_घड़ी_शेष = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Multi Track Internal Clock Default",
	.info = snd_ice1712_pro_पूर्णांकernal_घड़ी_शेष_info,
	.get = snd_ice1712_pro_पूर्णांकernal_घड़ी_शेष_get,
	.put = snd_ice1712_pro_पूर्णांकernal_घड़ी_शेष_put
पूर्ण;

#घोषणा snd_ice1712_pro_rate_locking_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ice1712_pro_rate_locking_get(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = PRO_RATE_LOCKED;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_rate_locking_put(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक change = 0, nval;

	nval = ucontrol->value.पूर्णांकeger.value[0] ? 1 : 0;
	spin_lock_irq(&ice->reg_lock);
	change = PRO_RATE_LOCKED != nval;
	PRO_RATE_LOCKED = nval;
	spin_unlock_irq(&ice->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_pro_rate_locking = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Multi Track Rate Locking",
	.info = snd_ice1712_pro_rate_locking_info,
	.get = snd_ice1712_pro_rate_locking_get,
	.put = snd_ice1712_pro_rate_locking_put
पूर्ण;

#घोषणा snd_ice1712_pro_rate_reset_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ice1712_pro_rate_reset_get(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = PRO_RATE_RESET;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_rate_reset_put(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक change = 0, nval;

	nval = ucontrol->value.पूर्णांकeger.value[0] ? 1 : 0;
	spin_lock_irq(&ice->reg_lock);
	change = PRO_RATE_RESET != nval;
	PRO_RATE_RESET = nval;
	spin_unlock_irq(&ice->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_pro_rate_reset = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Multi Track Rate Reset",
	.info = snd_ice1712_pro_rate_reset_info,
	.get = snd_ice1712_pro_rate_reset_get,
	.put = snd_ice1712_pro_rate_reset_put
पूर्ण;

/*
 * routing
 */
अटल पूर्णांक snd_ice1712_pro_route_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"PCM Out", /* 0 */
		"H/W In 0", "H/W In 1", "H/W In 2", "H/W In 3", /* 1-4 */
		"H/W In 4", "H/W In 5", "H/W In 6", "H/W In 7", /* 5-8 */
		"IEC958 In L", "IEC958 In R", /* 9-10 */
		"Digital Mixer", /* 11 - optional */
	पूर्ण;
	पूर्णांक num_items = snd_ctl_get_ioffidx(kcontrol, &uinfo->id) < 2 ? 12 : 11;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, num_items, texts);
पूर्ण

अटल पूर्णांक snd_ice1712_pro_route_analog_get(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अचिन्हित पूर्णांक val, cval;

	spin_lock_irq(&ice->reg_lock);
	val = inw(ICEMT(ice, ROUTE_PSDOUT03));
	cval = inl(ICEMT(ice, ROUTE_CAPTURE));
	spin_unlock_irq(&ice->reg_lock);

	val >>= ((idx % 2) * 8) + ((idx / 2) * 2);
	val &= 3;
	cval >>= ((idx / 2) * 8) + ((idx % 2) * 4);
	अगर (val == 1 && idx < 2)
		ucontrol->value.क्रमागतerated.item[0] = 11;
	अन्यथा अगर (val == 2)
		ucontrol->value.क्रमागतerated.item[0] = (cval & 7) + 1;
	अन्यथा अगर (val == 3)
		ucontrol->value.क्रमागतerated.item[0] = ((cval >> 3) & 1) + 9;
	अन्यथा
		ucontrol->value.क्रमागतerated.item[0] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_route_analog_put(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, shअगरt;
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अचिन्हित पूर्णांक val, old_val, nval;

	/* update PSDOUT */
	अगर (ucontrol->value.क्रमागतerated.item[0] >= 11)
		nval = idx < 2 ? 1 : 0; /* dig mixer (or pcm) */
	अन्यथा अगर (ucontrol->value.क्रमागतerated.item[0] >= 9)
		nval = 3; /* spdअगर in */
	अन्यथा अगर (ucontrol->value.क्रमागतerated.item[0] >= 1)
		nval = 2; /* analog in */
	अन्यथा
		nval = 0; /* pcm */
	shअगरt = ((idx % 2) * 8) + ((idx / 2) * 2);
	spin_lock_irq(&ice->reg_lock);
	val = old_val = inw(ICEMT(ice, ROUTE_PSDOUT03));
	val &= ~(0x03 << shअगरt);
	val |= nval << shअगरt;
	change = val != old_val;
	अगर (change)
		outw(val, ICEMT(ice, ROUTE_PSDOUT03));
	spin_unlock_irq(&ice->reg_lock);
	अगर (nval < 2) /* dig mixer of pcm */
		वापस change;

	/* update CAPTURE */
	spin_lock_irq(&ice->reg_lock);
	val = old_val = inl(ICEMT(ice, ROUTE_CAPTURE));
	shअगरt = ((idx / 2) * 8) + ((idx % 2) * 4);
	अगर (nval == 2) अणु /* analog in */
		nval = ucontrol->value.क्रमागतerated.item[0] - 1;
		val &= ~(0x07 << shअगरt);
		val |= nval << shअगरt;
	पूर्ण अन्यथा अणु /* spdअगर in */
		nval = (ucontrol->value.क्रमागतerated.item[0] - 9) << 3;
		val &= ~(0x08 << shअगरt);
		val |= nval << shअगरt;
	पूर्ण
	अगर (val != old_val) अणु
		change = 1;
		outl(val, ICEMT(ice, ROUTE_CAPTURE));
	पूर्ण
	spin_unlock_irq(&ice->reg_lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_route_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अचिन्हित पूर्णांक val, cval;
	val = inw(ICEMT(ice, ROUTE_SPDOUT));
	cval = (val >> (idx * 4 + 8)) & 0x0f;
	val = (val >> (idx * 2)) & 0x03;
	अगर (val == 1)
		ucontrol->value.क्रमागतerated.item[0] = 11;
	अन्यथा अगर (val == 2)
		ucontrol->value.क्रमागतerated.item[0] = (cval & 7) + 1;
	अन्यथा अगर (val == 3)
		ucontrol->value.क्रमागतerated.item[0] = ((cval >> 3) & 1) + 9;
	अन्यथा
		ucontrol->value.क्रमागतerated.item[0] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_route_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, shअगरt;
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अचिन्हित पूर्णांक val, old_val, nval;

	/* update SPDOUT */
	spin_lock_irq(&ice->reg_lock);
	val = old_val = inw(ICEMT(ice, ROUTE_SPDOUT));
	अगर (ucontrol->value.क्रमागतerated.item[0] >= 11)
		nval = 1;
	अन्यथा अगर (ucontrol->value.क्रमागतerated.item[0] >= 9)
		nval = 3;
	अन्यथा अगर (ucontrol->value.क्रमागतerated.item[0] >= 1)
		nval = 2;
	अन्यथा
		nval = 0;
	shअगरt = idx * 2;
	val &= ~(0x03 << shअगरt);
	val |= nval << shअगरt;
	shअगरt = idx * 4 + 8;
	अगर (nval == 2) अणु
		nval = ucontrol->value.क्रमागतerated.item[0] - 1;
		val &= ~(0x07 << shअगरt);
		val |= nval << shअगरt;
	पूर्ण अन्यथा अगर (nval == 3) अणु
		nval = (ucontrol->value.क्रमागतerated.item[0] - 9) << 3;
		val &= ~(0x08 << shअगरt);
		val |= nval << shअगरt;
	पूर्ण
	change = val != old_val;
	अगर (change)
		outw(val, ICEMT(ice, ROUTE_SPDOUT));
	spin_unlock_irq(&ice->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_mixer_pro_analog_route = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "H/W Playback Route",
	.info = snd_ice1712_pro_route_info,
	.get = snd_ice1712_pro_route_analog_get,
	.put = snd_ice1712_pro_route_analog_put,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_mixer_pro_spdअगर_route = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, NONE) "Route",
	.info = snd_ice1712_pro_route_info,
	.get = snd_ice1712_pro_route_spdअगर_get,
	.put = snd_ice1712_pro_route_spdअगर_put,
	.count = 2,
पूर्ण;


अटल पूर्णांक snd_ice1712_pro_volume_rate_info(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_volume_rate_get(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = inb(ICEMT(ice, MONITOR_RATE));
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_volume_rate_put(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;

	spin_lock_irq(&ice->reg_lock);
	change = inb(ICEMT(ice, MONITOR_RATE)) != ucontrol->value.पूर्णांकeger.value[0];
	outb(ucontrol->value.पूर्णांकeger.value[0], ICEMT(ice, MONITOR_RATE));
	spin_unlock_irq(&ice->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_mixer_pro_volume_rate = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Multi Track Volume Rate",
	.info = snd_ice1712_pro_volume_rate_info,
	.get = snd_ice1712_pro_volume_rate_get,
	.put = snd_ice1712_pro_volume_rate_put
पूर्ण;

अटल पूर्णांक snd_ice1712_pro_peak_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 22;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_pro_peak_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx;

	spin_lock_irq(&ice->reg_lock);
	क्रम (idx = 0; idx < 22; idx++) अणु
		outb(idx, ICEMT(ice, MONITOR_PEAKINDEX));
		ucontrol->value.पूर्णांकeger.value[idx] = inb(ICEMT(ice, MONITOR_PEAKDATA));
	पूर्ण
	spin_unlock_irq(&ice->reg_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_mixer_pro_peak = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name = "Multi Track Peak",
	.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info = snd_ice1712_pro_peak_info,
	.get = snd_ice1712_pro_peak_get
पूर्ण;

/*
 *
 */

/*
 * list of available boards
 */
अटल स्थिर काष्ठा snd_ice1712_card_info *card_tables[] = अणु
	snd_ice1712_hoontech_cards,
	snd_ice1712_delta_cards,
	snd_ice1712_ews_cards,
	शून्य,
पूर्ण;

अटल अचिन्हित अक्षर snd_ice1712_पढ़ो_i2c(काष्ठा snd_ice1712 *ice,
					  अचिन्हित अक्षर dev,
					  अचिन्हित अक्षर addr)
अणु
	दीर्घ t = 0x10000;

	outb(addr, ICEREG(ice, I2C_BYTE_ADDR));
	outb(dev & ~ICE1712_I2C_WRITE, ICEREG(ice, I2C_DEV_ADDR));
	जबतक (t-- > 0 && (inb(ICEREG(ice, I2C_CTRL)) & ICE1712_I2C_BUSY)) ;
	वापस inb(ICEREG(ice, I2C_DATA));
पूर्ण

अटल पूर्णांक snd_ice1712_पढ़ो_eeprom(काष्ठा snd_ice1712 *ice,
				   स्थिर अक्षर *modelname)
अणु
	पूर्णांक dev = ICE_I2C_EEPROM_ADDR;	/* I2C EEPROM device address */
	अचिन्हित पूर्णांक i, size;
	स्थिर काष्ठा snd_ice1712_card_info * स्थिर *tbl, *c;

	अगर (!modelname || !*modelname) अणु
		ice->eeprom.subvenकरोr = 0;
		अगर ((inb(ICEREG(ice, I2C_CTRL)) & ICE1712_I2C_EEPROM) != 0)
			ice->eeprom.subvenकरोr = (snd_ice1712_पढ़ो_i2c(ice, dev, 0x00) << 0) |
				(snd_ice1712_पढ़ो_i2c(ice, dev, 0x01) << 8) |
				(snd_ice1712_पढ़ो_i2c(ice, dev, 0x02) << 16) |
				(snd_ice1712_पढ़ो_i2c(ice, dev, 0x03) << 24);
		अगर (ice->eeprom.subvenकरोr == 0 ||
		    ice->eeprom.subvenकरोr == (अचिन्हित पूर्णांक)-1) अणु
			/* invalid subvenकरोr from EEPROM, try the PCI subststem ID instead */
			u16 venकरोr, device;
			pci_पढ़ो_config_word(ice->pci, PCI_SUBSYSTEM_VENDOR_ID, &venकरोr);
			pci_पढ़ो_config_word(ice->pci, PCI_SUBSYSTEM_ID, &device);
			ice->eeprom.subvenकरोr = ((अचिन्हित पूर्णांक)swab16(venकरोr) << 16) | swab16(device);
			अगर (ice->eeprom.subvenकरोr == 0 || ice->eeprom.subvenकरोr == (अचिन्हित पूर्णांक)-1) अणु
				dev_err(ice->card->dev,
					"No valid ID is found\n");
				वापस -ENXIO;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (tbl = card_tables; *tbl; tbl++) अणु
		क्रम (c = *tbl; c->subvenकरोr; c++) अणु
			अगर (modelname && c->model && !म_भेद(modelname, c->model)) अणु
				dev_info(ice->card->dev,
					 "Using board model %s\n", c->name);
				ice->eeprom.subvenकरोr = c->subvenकरोr;
			पूर्ण अन्यथा अगर (c->subvenकरोr != ice->eeprom.subvenकरोr)
				जारी;
			अगर (!c->eeprom_size || !c->eeprom_data)
				जाओ found;
			/* अगर the EEPROM is given by the driver, use it */
			dev_dbg(ice->card->dev, "using the defined eeprom..\n");
			ice->eeprom.version = 1;
			ice->eeprom.size = c->eeprom_size + 6;
			स_नकल(ice->eeprom.data, c->eeprom_data, c->eeprom_size);
			जाओ पढ़ो_skipped;
		पूर्ण
	पूर्ण
	dev_warn(ice->card->dev, "No matching model found for ID 0x%x\n",
	       ice->eeprom.subvenकरोr);

 found:
	ice->eeprom.size = snd_ice1712_पढ़ो_i2c(ice, dev, 0x04);
	अगर (ice->eeprom.size < 6)
		ice->eeprom.size = 32; /* FIXME: any cards without the correct size? */
	अन्यथा अगर (ice->eeprom.size > 32) अणु
		dev_err(ice->card->dev,
			"invalid EEPROM (size = %i)\n", ice->eeprom.size);
		वापस -EIO;
	पूर्ण
	ice->eeprom.version = snd_ice1712_पढ़ो_i2c(ice, dev, 0x05);
	अगर (ice->eeprom.version != 1) अणु
		dev_err(ice->card->dev, "invalid EEPROM version %i\n",
			   ice->eeprom.version);
		/* वापस -EIO; */
	पूर्ण
	size = ice->eeprom.size - 6;
	क्रम (i = 0; i < size; i++)
		ice->eeprom.data[i] = snd_ice1712_पढ़ो_i2c(ice, dev, i + 6);

 पढ़ो_skipped:
	ice->eeprom.gpiomask = ice->eeprom.data[ICE_EEP1_GPIO_MASK];
	ice->eeprom.gpiostate = ice->eeprom.data[ICE_EEP1_GPIO_STATE];
	ice->eeprom.gpiodir = ice->eeprom.data[ICE_EEP1_GPIO_सूची];

	वापस 0;
पूर्ण



अटल पूर्णांक snd_ice1712_chip_init(काष्ठा snd_ice1712 *ice)
अणु
	outb(ICE1712_RESET | ICE1712_NATIVE, ICEREG(ice, CONTROL));
	udelay(200);
	outb(ICE1712_NATIVE, ICEREG(ice, CONTROL));
	udelay(200);
	अगर (ice->eeprom.subvenकरोr == ICE1712_SUBDEVICE_DMX6FIRE &&
	    !ice->dxr_enable)
		/*  Set eeprom value to limit active ADCs and DACs to 6;
		 *  Also disable AC97 as no hardware in standard 6fire card/box
		 *  Note: DXR extensions are not currently supported
		 */
		ice->eeprom.data[ICE_EEP1_CODEC] = 0x3a;
	pci_ग_लिखो_config_byte(ice->pci, 0x60, ice->eeprom.data[ICE_EEP1_CODEC]);
	pci_ग_लिखो_config_byte(ice->pci, 0x61, ice->eeprom.data[ICE_EEP1_ACLINK]);
	pci_ग_लिखो_config_byte(ice->pci, 0x62, ice->eeprom.data[ICE_EEP1_I2SID]);
	pci_ग_लिखो_config_byte(ice->pci, 0x63, ice->eeprom.data[ICE_EEP1_SPDIF]);
	अगर (ice->eeprom.subvenकरोr != ICE1712_SUBDEVICE_STDSP24 &&
	    ice->eeprom.subvenकरोr != ICE1712_SUBDEVICE_STAUDIO_ADCIII) अणु
		ice->gpio.ग_लिखो_mask = ice->eeprom.gpiomask;
		ice->gpio.direction = ice->eeprom.gpiodir;
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_WRITE_MASK,
				  ice->eeprom.gpiomask);
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_सूचीECTION,
				  ice->eeprom.gpiodir);
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA,
				  ice->eeprom.gpiostate);
	पूर्ण अन्यथा अणु
		ice->gpio.ग_लिखो_mask = 0xc0;
		ice->gpio.direction = 0xff;
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_WRITE_MASK, 0xc0);
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_सूचीECTION, 0xff);
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA,
				  ICE1712_STDSP24_CLOCK_BIT);
	पूर्ण
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_PRO_POWERDOWN, 0);
	अगर (!(ice->eeprom.data[ICE_EEP1_CODEC] & ICE1712_CFG_NO_CON_AC97)) अणु
		outb(ICE1712_AC97_WARM, ICEREG(ice, AC97_CMD));
		udelay(100);
		outb(0, ICEREG(ice, AC97_CMD));
		udelay(200);
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_CONSUMER_POWERDOWN, 0);
	पूर्ण
	snd_ice1712_set_pro_rate(ice, 48000, 1);
	/* unmask used पूर्णांकerrupts */
	outb(((ice->eeprom.data[ICE_EEP1_CODEC] & ICE1712_CFG_2xMPU401) == 0 ?
	      ICE1712_IRQ_MPU2 : 0) |
	     ((ice->eeprom.data[ICE_EEP1_CODEC] & ICE1712_CFG_NO_CON_AC97) ?
	      ICE1712_IRQ_PBKDS | ICE1712_IRQ_CONCAP | ICE1712_IRQ_CONPBK : 0),
	     ICEREG(ice, IRQMASK));
	outb(0x00, ICEMT(ice, IRQ));

	वापस 0;
पूर्ण

पूर्णांक snd_ice1712_spdअगर_build_controls(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक err;
	काष्ठा snd_kcontrol *kctl;

	अगर (snd_BUG_ON(!ice->pcm_pro))
		वापस -EIO;
	err = snd_ctl_add(ice->card, kctl = snd_ctl_new1(&snd_ice1712_spdअगर_शेष, ice));
	अगर (err < 0)
		वापस err;
	kctl->id.device = ice->pcm_pro->device;
	err = snd_ctl_add(ice->card, kctl = snd_ctl_new1(&snd_ice1712_spdअगर_maskc, ice));
	अगर (err < 0)
		वापस err;
	kctl->id.device = ice->pcm_pro->device;
	err = snd_ctl_add(ice->card, kctl = snd_ctl_new1(&snd_ice1712_spdअगर_maskp, ice));
	अगर (err < 0)
		वापस err;
	kctl->id.device = ice->pcm_pro->device;
	err = snd_ctl_add(ice->card, kctl = snd_ctl_new1(&snd_ice1712_spdअगर_stream, ice));
	अगर (err < 0)
		वापस err;
	kctl->id.device = ice->pcm_pro->device;
	ice->spdअगर.stream_ctl = kctl;
	वापस 0;
पूर्ण


अटल पूर्णांक snd_ice1712_build_controls(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक err;

	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_eeprom, ice));
	अगर (err < 0)
		वापस err;
	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_pro_पूर्णांकernal_घड़ी, ice));
	अगर (err < 0)
		वापस err;
	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_pro_पूर्णांकernal_घड़ी_शेष, ice));
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_pro_rate_locking, ice));
	अगर (err < 0)
		वापस err;
	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_pro_rate_reset, ice));
	अगर (err < 0)
		वापस err;

	अगर (ice->num_total_dacs > 0) अणु
		काष्ठा snd_kcontrol_new पंचांगp = snd_ice1712_mixer_pro_analog_route;
		पंचांगp.count = ice->num_total_dacs;
		err = snd_ctl_add(ice->card, snd_ctl_new1(&पंचांगp, ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_mixer_pro_spdअगर_route, ice));
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_mixer_pro_volume_rate, ice));
	अगर (err < 0)
		वापस err;
	वापस snd_ctl_add(ice->card,
			   snd_ctl_new1(&snd_ice1712_mixer_pro_peak, ice));
पूर्ण

अटल पूर्णांक snd_ice1712_मुक्त(काष्ठा snd_ice1712 *ice)
अणु
	अगर (!ice->port)
		जाओ __hw_end;
	/* mask all पूर्णांकerrupts */
	outb(ICE1712_MULTI_CAPTURE | ICE1712_MULTI_PLAYBACK, ICEMT(ice, IRQ));
	outb(0xff, ICEREG(ice, IRQMASK));
	/* --- */
__hw_end:
	अगर (ice->irq >= 0)
		मुक्त_irq(ice->irq, ice);

	अगर (ice->port)
		pci_release_regions(ice->pci);
	snd_ice1712_akm4xxx_मुक्त(ice);
	pci_disable_device(ice->pci);
	kमुक्त(ice->spec);
	kमुक्त(ice);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_ice1712 *ice = device->device_data;
	वापस snd_ice1712_मुक्त(ice);
पूर्ण

अटल पूर्णांक snd_ice1712_create(काष्ठा snd_card *card,
			      काष्ठा pci_dev *pci,
			      स्थिर अक्षर *modelname,
			      पूर्णांक omni,
			      पूर्णांक cs8427_समयout,
			      पूर्णांक dxr_enable,
			      काष्ठा snd_ice1712 **r_ice1712)
अणु
	काष्ठा snd_ice1712 *ice;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_ice1712_dev_मुक्त,
	पूर्ण;

	*r_ice1712 = शून्य;

	/* enable PCI device */
	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;
	/* check, अगर we can restrict PCI DMA transfers to 28 bits */
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(28))) अणु
		dev_err(card->dev,
			"architecture does not support 28bit PCI busmaster DMA\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण

	ice = kzalloc(माप(*ice), GFP_KERNEL);
	अगर (ice == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	ice->omni = omni ? 1 : 0;
	अगर (cs8427_समयout < 1)
		cs8427_समयout = 1;
	अन्यथा अगर (cs8427_समयout > 1000)
		cs8427_समयout = 1000;
	ice->cs8427_समयout = cs8427_समयout;
	ice->dxr_enable = dxr_enable;
	spin_lock_init(&ice->reg_lock);
	mutex_init(&ice->gpio_mutex);
	mutex_init(&ice->i2c_mutex);
	mutex_init(&ice->खोलो_mutex);
	ice->gpio.set_mask = snd_ice1712_set_gpio_mask;
	ice->gpio.get_mask = snd_ice1712_get_gpio_mask;
	ice->gpio.set_dir = snd_ice1712_set_gpio_dir;
	ice->gpio.get_dir = snd_ice1712_get_gpio_dir;
	ice->gpio.set_data = snd_ice1712_set_gpio_data;
	ice->gpio.get_data = snd_ice1712_get_gpio_data;

	ice->spdअगर.cs8403_bits =
		ice->spdअगर.cs8403_stream_bits = (0x01 |	/* consumer क्रमmat */
						 0x10 |	/* no emphasis */
						 0x20);	/* PCM encoder/decoder */
	ice->card = card;
	ice->pci = pci;
	ice->irq = -1;
	pci_set_master(pci);
	/* disable legacy emulation */
	pci_ग_लिखो_config_word(ice->pci, 0x40, 0x807f);
	pci_ग_लिखो_config_word(ice->pci, 0x42, 0x0006);
	snd_ice1712_proc_init(ice);

	card->निजी_data = ice;

	err = pci_request_regions(pci, "ICE1712");
	अगर (err < 0) अणु
		kमुक्त(ice);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	ice->port = pci_resource_start(pci, 0);
	ice->ddma_port = pci_resource_start(pci, 1);
	ice->dmapath_port = pci_resource_start(pci, 2);
	ice->profi_port = pci_resource_start(pci, 3);

	अगर (request_irq(pci->irq, snd_ice1712_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, ice)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_ice1712_मुक्त(ice);
		वापस -EIO;
	पूर्ण

	ice->irq = pci->irq;
	card->sync_irq = ice->irq;

	अगर (snd_ice1712_पढ़ो_eeprom(ice, modelname) < 0) अणु
		snd_ice1712_मुक्त(ice);
		वापस -EIO;
	पूर्ण
	अगर (snd_ice1712_chip_init(ice) < 0) अणु
		snd_ice1712_मुक्त(ice);
		वापस -EIO;
	पूर्ण

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, ice, &ops);
	अगर (err < 0) अणु
		snd_ice1712_मुक्त(ice);
		वापस err;
	पूर्ण

	*r_ice1712 = ice;
	वापस 0;
पूर्ण


/*
 *
 * Registration
 *
 */

अटल काष्ठा snd_ice1712_card_info no_matched;

अटल पूर्णांक snd_ice1712_probe(काष्ठा pci_dev *pci,
			     स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_ice1712 *ice;
	पूर्णांक pcm_dev = 0, err;
	स्थिर काष्ठा snd_ice1712_card_info * स्थिर *tbl, *c;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

	म_नकल(card->driver, "ICE1712");
	म_नकल(card->लघुname, "ICEnsemble ICE1712");

	err = snd_ice1712_create(card, pci, model[dev], omni[dev],
		cs8427_समयout[dev], dxr_enable[dev], &ice);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	क्रम (tbl = card_tables; *tbl; tbl++) अणु
		क्रम (c = *tbl; c->subvenकरोr; c++) अणु
			अगर (c->subvenकरोr == ice->eeprom.subvenकरोr) अणु
				ice->card_info = c;
				म_नकल(card->लघुname, c->name);
				अगर (c->driver) /* specअगरic driver? */
					म_नकल(card->driver, c->driver);
				अगर (c->chip_init) अणु
					err = c->chip_init(ice);
					अगर (err < 0) अणु
						snd_card_मुक्त(card);
						वापस err;
					पूर्ण
				पूर्ण
				जाओ __found;
			पूर्ण
		पूर्ण
	पूर्ण
	c = &no_matched;
 __found:

	err = snd_ice1712_pcm_profi(ice, pcm_dev++);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	अगर (ice_has_con_ac97(ice)) अणु
		err = snd_ice1712_pcm(ice, pcm_dev++);
		अगर (err < 0) अणु
			snd_card_मुक्त(card);
			वापस err;
		पूर्ण
	पूर्ण

	err = snd_ice1712_ac97_mixer(ice);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	err = snd_ice1712_build_controls(ice);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	अगर (c->build_controls) अणु
		err = c->build_controls(ice);
		अगर (err < 0) अणु
			snd_card_मुक्त(card);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (ice_has_con_ac97(ice)) अणु
		err = snd_ice1712_pcm_ds(ice, pcm_dev++);
		अगर (err < 0) अणु
			snd_card_मुक्त(card);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (!c->no_mpu401) अणु
		err = snd_mpu401_uart_new(card, 0, MPU401_HW_ICE1712,
			ICEREG(ice, MPU1_CTRL),
			c->mpu401_1_info_flags |
			MPU401_INFO_INTEGRATED | MPU401_INFO_IRQ_HOOK,
			-1, &ice->rmidi[0]);
		अगर (err < 0) अणु
			snd_card_मुक्त(card);
			वापस err;
		पूर्ण
		अगर (c->mpu401_1_name)
			/*  Preferred name available in card_info */
			snम_लिखो(ice->rmidi[0]->name,
				 माप(ice->rmidi[0]->name),
				 "%s %d", c->mpu401_1_name, card->number);

		अगर (ice->eeprom.data[ICE_EEP1_CODEC] & ICE1712_CFG_2xMPU401) अणु
			/*  2nd port used  */
			err = snd_mpu401_uart_new(card, 1, MPU401_HW_ICE1712,
				ICEREG(ice, MPU2_CTRL),
				c->mpu401_2_info_flags |
				MPU401_INFO_INTEGRATED | MPU401_INFO_IRQ_HOOK,
				-1, &ice->rmidi[1]);

			अगर (err < 0) अणु
				snd_card_मुक्त(card);
				वापस err;
			पूर्ण
			अगर (c->mpu401_2_name)
				/*  Preferred name available in card_info */
				snम_लिखो(ice->rmidi[1]->name,
					 माप(ice->rmidi[1]->name),
					 "%s %d", c->mpu401_2_name,
					 card->number);
		पूर्ण
	पूर्ण

	snd_ice1712_set_input_घड़ी_source(ice, 0);

	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %i",
		card->लघुname, ice->port, ice->irq);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_ice1712_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा snd_card *card = pci_get_drvdata(pci);
	काष्ठा snd_ice1712 *ice = card->निजी_data;

	अगर (ice->card_info && ice->card_info->chip_निकास)
		ice->card_info->chip_निकास(ice);
	snd_card_मुक्त(card);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_ice1712_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_ice1712 *ice = card->निजी_data;

	अगर (!ice->pm_suspend_enabled)
		वापस 0;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

	snd_ac97_suspend(ice->ac97);

	spin_lock_irq(&ice->reg_lock);
	ice->pm_saved_is_spdअगर_master = is_spdअगर_master(ice);
	ice->pm_saved_spdअगर_ctrl = inw(ICEMT(ice, ROUTE_SPDOUT));
	ice->pm_saved_route = inw(ICEMT(ice, ROUTE_PSDOUT03));
	spin_unlock_irq(&ice->reg_lock);

	अगर (ice->pm_suspend)
		ice->pm_suspend(ice);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_ice1712 *ice = card->निजी_data;
	पूर्णांक rate;

	अगर (!ice->pm_suspend_enabled)
		वापस 0;

	अगर (ice->cur_rate)
		rate = ice->cur_rate;
	अन्यथा
		rate = PRO_RATE_DEFAULT;

	अगर (snd_ice1712_chip_init(ice) < 0) अणु
		snd_card_disconnect(card);
		वापस -EIO;
	पूर्ण

	ice->cur_rate = rate;

	अगर (ice->pm_resume)
		ice->pm_resume(ice);

	अगर (ice->pm_saved_is_spdअगर_master) अणु
		/* चयनing to बाह्यal घड़ी via SPDIF */
		spin_lock_irq(&ice->reg_lock);
		outb(inb(ICEMT(ice, RATE)) | ICE1712_SPDIF_MASTER,
			ICEMT(ice, RATE));
		spin_unlock_irq(&ice->reg_lock);
		snd_ice1712_set_input_घड़ी_source(ice, 1);
	पूर्ण अन्यथा अणु
		/* पूर्णांकernal on-card घड़ी */
		snd_ice1712_set_pro_rate(ice, rate, 1);
		snd_ice1712_set_input_घड़ी_source(ice, 0);
	पूर्ण

	outw(ice->pm_saved_spdअगर_ctrl, ICEMT(ice, ROUTE_SPDOUT));
	outw(ice->pm_saved_route, ICEMT(ice, ROUTE_PSDOUT03));

	snd_ac97_resume(ice->ac97);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_ice1712_pm, snd_ice1712_suspend, snd_ice1712_resume);
#घोषणा SND_VT1712_PM_OPS	&snd_ice1712_pm
#अन्यथा
#घोषणा SND_VT1712_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver ice1712_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_ice1712_ids,
	.probe = snd_ice1712_probe,
	.हटाओ = snd_ice1712_हटाओ,
	.driver = अणु
		.pm = SND_VT1712_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(ice1712_driver);
