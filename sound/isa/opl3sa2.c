<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Yamaha OPL3-SA[2,3] soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>
#समावेश <linux/pnp.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/wss.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Yamaha OPL3SA2+");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_ISAPNP; /* Enable this card */
#अगर_घोषित CONFIG_PNP
अटल bool isapnp[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;
#पूर्ण_अगर
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0xf86,0x370,0x100 */
अटल दीर्घ sb_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x220,0x240,0x260 */
अटल दीर्घ wss_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;/* 0x530,0xe80,0xf40,0x604 */
अटल दीर्घ fm_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x388 */
अटल दीर्घ midi_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;/* 0x330,0x300 */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 0,1,3,5,9,11,12,15 */
अटल पूर्णांक dma1[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 1,3,5,6,7 */
अटल पूर्णांक dma2[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 1,3,5,6,7 */
अटल पूर्णांक opl3sa3_ymode[SNDRV_CARDS];   /* 0,1,2,3 */ /*SL Added*/

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for OPL3-SA soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for OPL3-SA soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable OPL3-SA soundcard.");
#अगर_घोषित CONFIG_PNP
module_param_array(isapnp, bool, शून्य, 0444);
MODULE_PARM_DESC(isapnp, "PnP detection for specified soundcard.");
#पूर्ण_अगर
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for OPL3-SA driver.");
module_param_hw_array(sb_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(sb_port, "SB port # for OPL3-SA driver.");
module_param_hw_array(wss_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(wss_port, "WSS port # for OPL3-SA driver.");
module_param_hw_array(fm_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(fm_port, "FM port # for OPL3-SA driver.");
module_param_hw_array(midi_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(midi_port, "MIDI port # for OPL3-SA driver.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for OPL3-SA driver.");
module_param_hw_array(dma1, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma1, "DMA1 # for OPL3-SA driver.");
module_param_hw_array(dma2, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma2, "DMA2 # for OPL3-SA driver.");
module_param_array(opl3sa3_ymode, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(opl3sa3_ymode, "Speaker size selection for 3D Enhancement mode: Desktop/Large Notebook/Small Notebook/HiFi.");

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक isa_रेजिस्टरed;
अटल पूर्णांक pnp_रेजिस्टरed;
अटल पूर्णांक pnpc_रेजिस्टरed;
#पूर्ण_अगर

/* control ports */
#घोषणा OPL3SA2_PM_CTRL		0x01
#घोषणा OPL3SA2_SYS_CTRL		0x02
#घोषणा OPL3SA2_IRQ_CONFIG	0x03
#घोषणा OPL3SA2_IRQ_STATUS	0x04
#घोषणा OPL3SA2_DMA_CONFIG	0x06
#घोषणा OPL3SA2_MASTER_LEFT	0x07
#घोषणा OPL3SA2_MASTER_RIGHT	0x08
#घोषणा OPL3SA2_MIC		0x09
#घोषणा OPL3SA2_MISC		0x0A

/* opl3sa3 only */
#घोषणा OPL3SA3_DGTL_DOWN	0x12
#घोषणा OPL3SA3_ANLG_DOWN	0x13
#घोषणा OPL3SA3_WIDE		0x14
#घोषणा OPL3SA3_BASS		0x15
#घोषणा OPL3SA3_TREBLE		0x16

/* घातer management bits */
#घोषणा OPL3SA2_PM_ADOWN		0x20
#घोषणा OPL3SA2_PM_PSV		0x04		
#घोषणा OPL3SA2_PM_PDN		0x02
#घोषणा OPL3SA2_PM_PDX		0x01

#घोषणा OPL3SA2_PM_D0	0x00
#घोषणा OPL3SA2_PM_D3	(OPL3SA2_PM_ADOWN|OPL3SA2_PM_PSV|OPL3SA2_PM_PDN|OPL3SA2_PM_PDX)

काष्ठा snd_opl3sa2 अणु
	पूर्णांक version;		/* 2 or 3 */
	अचिन्हित दीर्घ port;	/* control port */
	काष्ठा resource *res_port; /* control port resource */
	पूर्णांक irq;
	पूर्णांक single_dma;
	spinlock_t reg_lock;
	काष्ठा snd_hwdep *synth;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_wss *wss;
	अचिन्हित अक्षर ctlregs[0x20];
	पूर्णांक ymode;		/* SL added */
	काष्ठा snd_kcontrol *master_चयन;
	काष्ठा snd_kcontrol *master_volume;
पूर्ण;

#घोषणा PFX	"opl3sa2: "

#अगर_घोषित CONFIG_PNP

अटल स्थिर काष्ठा pnp_device_id snd_opl3sa2_pnpbiosids[] = अणु
	अणु .id = "YMH0021" पूर्ण,
	अणु .id = "NMX2210" पूर्ण,	/* Gateway Solo 2500 */
	अणु .id = "" पूर्ण		/* end */
पूर्ण;

MODULE_DEVICE_TABLE(pnp, snd_opl3sa2_pnpbiosids);

अटल स्थिर काष्ठा pnp_card_device_id snd_opl3sa2_pnpids[] = अणु
	/* Yamaha YMF719E-S (Genius Sound Maker 3DX) */
	अणु .id = "YMH0020", .devs = अणु अणु "YMH0021" पूर्ण पूर्ण पूर्ण,
	/* Yamaha OPL3-SA3 (पूर्णांकegrated on Intel's Pentium II AL440LX motherboard) */
	अणु .id = "YMH0030", .devs = अणु अणु "YMH0021" पूर्ण पूर्ण पूर्ण,
	/* Yamaha OPL3-SA2 */
	अणु .id = "YMH0800", .devs = अणु अणु "YMH0021" पूर्ण पूर्ण पूर्ण,
	/* Yamaha OPL3-SA2 */
	अणु .id = "YMH0801", .devs = अणु अणु "YMH0021" पूर्ण पूर्ण पूर्ण,
	/* NeoMagic MagicWave 3DX */
	अणु .id = "NMX2200", .devs = अणु अणु "YMH2210" पूर्ण पूर्ण पूर्ण,
	/* NeoMagic MagicWave 3D */
	अणु .id = "NMX2200", .devs = अणु अणु "NMX2210" पूर्ण पूर्ण पूर्ण,
	/* --- */
	अणु .id = "" पूर्ण	/* end */
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_opl3sa2_pnpids);

#पूर्ण_अगर /* CONFIG_PNP */


/* पढ़ो control port (w/o spinlock) */
अटल अचिन्हित अक्षर __snd_opl3sa2_पढ़ो(काष्ठा snd_opl3sa2 *chip, अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर result;
#अगर 0
	outb(0x1d, port);	/* password */
	prपूर्णांकk(KERN_DEBUG "read [0x%lx] = 0x%x\n", port, inb(port));
#पूर्ण_अगर
	outb(reg, chip->port);	/* रेजिस्टर */
	result = inb(chip->port + 1);
#अगर 0
	prपूर्णांकk(KERN_DEBUG "read [0x%lx] = 0x%x [0x%x]\n",
	       port, result, inb(port));
#पूर्ण_अगर
	वापस result;
पूर्ण

/* पढ़ो control port (with spinlock) */
अटल अचिन्हित अक्षर snd_opl3sa2_पढ़ो(काष्ठा snd_opl3sa2 *chip, अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर result;

	spin_lock_irqsave(&chip->reg_lock, flags);
	result = __snd_opl3sa2_पढ़ो(chip, reg);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस result;
पूर्ण

/* ग_लिखो control port (w/o spinlock) */
अटल व्योम __snd_opl3sa2_ग_लिखो(काष्ठा snd_opl3sa2 *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर value)
अणु
#अगर 0
	outb(0x1d, port);	/* password */
#पूर्ण_अगर
	outb(reg, chip->port);	/* रेजिस्टर */
	outb(value, chip->port + 1);
	chip->ctlregs[reg] = value;
पूर्ण

/* ग_लिखो control port (with spinlock) */
अटल व्योम snd_opl3sa2_ग_लिखो(काष्ठा snd_opl3sa2 *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर value)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&chip->reg_lock, flags);
	__snd_opl3sa2_ग_लिखो(chip, reg, value);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल पूर्णांक snd_opl3sa2_detect(काष्ठा snd_card *card)
अणु
	काष्ठा snd_opl3sa2 *chip = card->निजी_data;
	अचिन्हित दीर्घ port;
	अचिन्हित अक्षर पंचांगp, पंचांगp1;
	अक्षर str[2];

	port = chip->port;
	अगर ((chip->res_port = request_region(port, 2, "OPL3-SA control")) == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "can't grab port 0x%lx\n", port);
		वापस -EBUSY;
	पूर्ण
	/*
	snd_prपूर्णांकk(KERN_DEBUG "REG 0A = 0x%x\n",
		   snd_opl3sa2_पढ़ो(chip, 0x0a));
	*/
	chip->version = 0;
	पंचांगp = snd_opl3sa2_पढ़ो(chip, OPL3SA2_MISC);
	अगर (पंचांगp == 0xff) अणु
		snd_prपूर्णांकd("OPL3-SA [0x%lx] detect = 0x%x\n", port, पंचांगp);
		वापस -ENODEV;
	पूर्ण
	चयन (पंचांगp & 0x07) अणु
	हाल 0x01:
		chip->version = 2; /* YMF711 */
		अवरोध;
	शेष:
		chip->version = 3;
		/* 0x02 - standard */
		/* 0x03 - YM715B */
		/* 0x04 - YM719 - OPL-SA4? */
		/* 0x05 - OPL3-SA3 - Libretto 100 */
		/* 0x07 - unknown - Neomagic MagicWave 3D */
		अवरोध;
	पूर्ण
	str[0] = chip->version + '0';
	str[1] = 0;
	म_जोड़ो(card->लघुname, str);
	snd_opl3sa2_ग_लिखो(chip, OPL3SA2_MISC, पंचांगp ^ 7);
	अगर ((पंचांगp1 = snd_opl3sa2_पढ़ो(chip, OPL3SA2_MISC)) != पंचांगp) अणु
		snd_prपूर्णांकd("OPL3-SA [0x%lx] detect (1) = 0x%x (0x%x)\n", port, पंचांगp, पंचांगp1);
		वापस -ENODEV;
	पूर्ण
	/* try अगर the MIC रेजिस्टर is accessible */
	पंचांगp = snd_opl3sa2_पढ़ो(chip, OPL3SA2_MIC);
	snd_opl3sa2_ग_लिखो(chip, OPL3SA2_MIC, 0x8a);
	अगर (((पंचांगp1 = snd_opl3sa2_पढ़ो(chip, OPL3SA2_MIC)) & 0x9f) != 0x8a) अणु
		snd_prपूर्णांकd("OPL3-SA [0x%lx] detect (2) = 0x%x (0x%x)\n", port, पंचांगp, पंचांगp1);
		वापस -ENODEV;
	पूर्ण
	snd_opl3sa2_ग_लिखो(chip, OPL3SA2_MIC, 0x9f);
	/* initialization */
	/* Power Management - full on */
	snd_opl3sa2_ग_लिखो(chip, OPL3SA2_PM_CTRL, OPL3SA2_PM_D0);
	अगर (chip->version > 2) अणु
		/* ymode is bits 4&5 (of 0 to 7) on all but opl3sa2 versions */
		snd_opl3sa2_ग_लिखो(chip, OPL3SA2_SYS_CTRL, (chip->ymode << 4));
	पूर्ण अन्यथा अणु
		/* शेष क्रम opl3sa2 versions */
		snd_opl3sa2_ग_लिखो(chip, OPL3SA2_SYS_CTRL, 0x00);
	पूर्ण
	snd_opl3sa2_ग_लिखो(chip, OPL3SA2_IRQ_CONFIG, 0x0d);	/* Interrupt Channel Configuration - IRQ A = OPL3 + MPU + WSS */
	अगर (chip->single_dma) अणु
		snd_opl3sa2_ग_लिखो(chip, OPL3SA2_DMA_CONFIG, 0x03);	/* DMA Configuration - DMA A = WSS-R + WSS-P */
	पूर्ण अन्यथा अणु
		snd_opl3sa2_ग_लिखो(chip, OPL3SA2_DMA_CONFIG, 0x21);	/* DMA Configuration - DMA B = WSS-R, DMA A = WSS-P */
	पूर्ण
	snd_opl3sa2_ग_लिखो(chip, OPL3SA2_MISC, 0x80 | (पंचांगp & 7));	/* Miscellaneous - शेष */
	अगर (chip->version > 2) अणु
		snd_opl3sa2_ग_लिखो(chip, OPL3SA3_DGTL_DOWN, 0x00);	/* Digital Block Partial Power Down - शेष */
		snd_opl3sa2_ग_लिखो(chip, OPL3SA3_ANLG_DOWN, 0x00);	/* Analog Block Partial Power Down - शेष */
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t snd_opl3sa2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित लघु status;
	काष्ठा snd_card *card = dev_id;
	काष्ठा snd_opl3sa2 *chip;
	पूर्णांक handled = 0;

	अगर (card == शून्य)
		वापस IRQ_NONE;

	chip = card->निजी_data;
	status = snd_opl3sa2_पढ़ो(chip, OPL3SA2_IRQ_STATUS);

	अगर (status & 0x20) अणु
		handled = 1;
		snd_opl3_पूर्णांकerrupt(chip->synth);
	पूर्ण

	अगर ((status & 0x10) && chip->rmidi != शून्य) अणु
		handled = 1;
		snd_mpu401_uart_पूर्णांकerrupt(irq, chip->rmidi->निजी_data);
	पूर्ण

	अगर (status & 0x07) अणु	/* TI,CI,PI */
		handled = 1;
		snd_wss_पूर्णांकerrupt(irq, chip->wss);
	पूर्ण

	अगर (status & 0x40) अणु /* hardware volume change */
		handled = 1;
		/* पढ़ोing from Master Lch रेजिस्टर at 0x07 clears this bit */
		snd_opl3sa2_पढ़ो(chip, OPL3SA2_MASTER_RIGHT);
		snd_opl3sa2_पढ़ो(chip, OPL3SA2_MASTER_LEFT);
		अगर (chip->master_चयन && chip->master_volume) अणु
			snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE,
					&chip->master_चयन->id);
			snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE,
					&chip->master_volume->id);
		पूर्ण
	पूर्ण
	वापस IRQ_RETVAL(handled);
पूर्ण

#घोषणा OPL3SA2_SINGLE(xname, xindex, reg, shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_wss_info_single, \
  .get = snd_opl3sa2_get_single, .put = snd_opl3sa2_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24) पूर्ण
#घोषणा OPL3SA2_SINGLE_TLV(xname, xindex, reg, shअगरt, mask, invert, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .name = xname, .index = xindex, \
  .info = snd_wss_info_single, \
  .get = snd_opl3sa2_get_single, .put = snd_opl3sa2_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24), \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण

अटल पूर्णांक snd_opl3sa2_get_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_opl3sa2 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;

	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = (chip->ctlregs[reg] >> shअगरt) & mask;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl3sa2_put_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_opl3sa2 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक change;
	अचिन्हित लघु val, oval;
	
	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	अगर (invert)
		val = mask - val;
	val <<= shअगरt;
	spin_lock_irqsave(&chip->reg_lock, flags);
	oval = chip->ctlregs[reg];
	val = (oval & ~(mask << shअगरt)) | val;
	change = val != oval;
	__snd_opl3sa2_ग_लिखो(chip, reg, val);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

#घोषणा OPL3SA2_DOUBLE(xname, xindex, left_reg, right_reg, shअगरt_left, shअगरt_right, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_wss_info_द्विगुन, \
  .get = snd_opl3sa2_get_द्विगुन, .put = snd_opl3sa2_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | (shअगरt_right << 19) | (mask << 24) | (invert << 22) पूर्ण
#घोषणा OPL3SA2_DOUBLE_TLV(xname, xindex, left_reg, right_reg, shअगरt_left, shअगरt_right, mask, invert, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .name = xname, .index = xindex, \
  .info = snd_wss_info_द्विगुन, \
  .get = snd_opl3sa2_get_द्विगुन, .put = snd_opl3sa2_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | (shअगरt_right << 19) | (mask << 24) | (invert << 22), \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण

अटल पूर्णांक snd_opl3sa2_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_opl3sa2 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = (chip->ctlregs[left_reg] >> shअगरt_left) & mask;
	ucontrol->value.पूर्णांकeger.value[1] = (chip->ctlregs[right_reg] >> shअगरt_right) & mask;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (invert) अणु
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
		ucontrol->value.पूर्णांकeger.value[1] = mask - ucontrol->value.पूर्णांकeger.value[1];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl3sa2_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_opl3sa2 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	पूर्णांक change;
	अचिन्हित लघु val1, val2, oval1, oval2;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] & mask;
	val2 = ucontrol->value.पूर्णांकeger.value[1] & mask;
	अगर (invert) अणु
		val1 = mask - val1;
		val2 = mask - val2;
	पूर्ण
	val1 <<= shअगरt_left;
	val2 <<= shअगरt_right;
	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (left_reg != right_reg) अणु
		oval1 = chip->ctlregs[left_reg];
		oval2 = chip->ctlregs[right_reg];
		val1 = (oval1 & ~(mask << shअगरt_left)) | val1;
		val2 = (oval2 & ~(mask << shअगरt_right)) | val2;
		change = val1 != oval1 || val2 != oval2;
		__snd_opl3sa2_ग_लिखो(chip, left_reg, val1);
		__snd_opl3sa2_ग_लिखो(chip, right_reg, val2);
	पूर्ण अन्यथा अणु
		oval1 = chip->ctlregs[left_reg];
		val1 = (oval1 & ~((mask << shअगरt_left) | (mask << shअगरt_right))) | val1 | val2;
		change = val1 != oval1;
		__snd_opl3sa2_ग_लिखो(chip, left_reg, val1);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_master, -3000, 200, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_5bit_12db_max, -3450, 150, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_opl3sa2_controls[] = अणु
OPL3SA2_DOUBLE("Master Playback Switch", 0, 0x07, 0x08, 7, 7, 1, 1),
OPL3SA2_DOUBLE_TLV("Master Playback Volume", 0, 0x07, 0x08, 0, 0, 15, 1,
		   db_scale_master),
OPL3SA2_SINGLE("Mic Playback Switch", 0, 0x09, 7, 1, 1),
OPL3SA2_SINGLE_TLV("Mic Playback Volume", 0, 0x09, 0, 31, 1,
		   db_scale_5bit_12db_max),
OPL3SA2_SINGLE("ZV Port Switch", 0, 0x02, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_opl3sa2_tone_controls[] = अणु
OPL3SA2_DOUBLE("3D Control - Wide", 0, 0x14, 0x14, 4, 0, 7, 0),
OPL3SA2_DOUBLE("Tone Control - Bass", 0, 0x15, 0x15, 4, 0, 7, 0),
OPL3SA2_DOUBLE("Tone Control - Treble", 0, 0x16, 0x16, 4, 0, 7, 0)
पूर्ण;

अटल व्योम snd_opl3sa2_master_मुक्त(काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा snd_opl3sa2 *chip = snd_kcontrol_chip(kcontrol);
	chip->master_चयन = शून्य;
	chip->master_volume = शून्य;
पूर्ण

अटल पूर्णांक snd_opl3sa2_mixer(काष्ठा snd_card *card)
अणु
	काष्ठा snd_opl3sa2 *chip = card->निजी_data;
	काष्ठा snd_ctl_elem_id id1, id2;
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	स_रखो(&id1, 0, माप(id1));
	स_रखो(&id2, 0, माप(id2));
	id1.अगरace = id2.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	/* reassign AUX0 to CD */
        म_नकल(id1.name, "Aux Playback Switch");
        म_नकल(id2.name, "CD Playback Switch");
        अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "Cannot rename opl3sa2 control\n");
                वापस err;
	पूर्ण
        म_नकल(id1.name, "Aux Playback Volume");
        म_नकल(id2.name, "CD Playback Volume");
        अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "Cannot rename opl3sa2 control\n");
                वापस err;
	पूर्ण
	/* reassign AUX1 to FM */
        म_नकल(id1.name, "Aux Playback Switch"); id1.index = 1;
        म_नकल(id2.name, "FM Playback Switch");
        अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "Cannot rename opl3sa2 control\n");
                वापस err;
	पूर्ण
        म_नकल(id1.name, "Aux Playback Volume");
        म_नकल(id2.name, "FM Playback Volume");
        अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "Cannot rename opl3sa2 control\n");
                वापस err;
	पूर्ण
	/* add OPL3SA2 controls */
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_opl3sa2_controls); idx++) अणु
		अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_opl3sa2_controls[idx], chip))) < 0)
			वापस err;
		चयन (idx) अणु
		हाल 0: chip->master_चयन = kctl; kctl->निजी_मुक्त = snd_opl3sa2_master_मुक्त; अवरोध;
		हाल 1: chip->master_volume = kctl; kctl->निजी_मुक्त = snd_opl3sa2_master_मुक्त; अवरोध;
		पूर्ण
	पूर्ण
	अगर (chip->version > 2) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_opl3sa2_tone_controls); idx++)
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_opl3sa2_tone_controls[idx], chip))) < 0)
				वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* Power Management support functions */
#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_opl3sa2_suspend(काष्ठा snd_card *card, pm_message_t state)
अणु
	अगर (card) अणु
		काष्ठा snd_opl3sa2 *chip = card->निजी_data;

		snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
		chip->wss->suspend(chip->wss);
		/* घातer करोwn */
		snd_opl3sa2_ग_लिखो(chip, OPL3SA2_PM_CTRL, OPL3SA2_PM_D3);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl3sa2_resume(काष्ठा snd_card *card)
अणु
	काष्ठा snd_opl3sa2 *chip;
	पूर्णांक i;

	अगर (!card)
		वापस 0;

	chip = card->निजी_data;
	/* घातer up */
	snd_opl3sa2_ग_लिखो(chip, OPL3SA2_PM_CTRL, OPL3SA2_PM_D0);

	/* restore रेजिस्टरs */
	क्रम (i = 2; i <= 0x0a; i++) अणु
		अगर (i != OPL3SA2_IRQ_STATUS)
			snd_opl3sa2_ग_लिखो(chip, i, chip->ctlregs[i]);
	पूर्ण
	अगर (chip->version > 2) अणु
		क्रम (i = 0x12; i <= 0x16; i++)
			snd_opl3sa2_ग_लिखो(chip, i, chip->ctlregs[i]);
	पूर्ण
	/* restore wss */
	chip->wss->resume(chip->wss);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_opl3sa2_pnp(पूर्णांक dev, काष्ठा snd_opl3sa2 *chip,
			   काष्ठा pnp_dev *pdev)
अणु
	अगर (pnp_activate_dev(pdev) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "PnP configure failure (out of resources?)\n");
		वापस -EBUSY;
	पूर्ण
	sb_port[dev] = pnp_port_start(pdev, 0);
	wss_port[dev] = pnp_port_start(pdev, 1);
	fm_port[dev] = pnp_port_start(pdev, 2);
	midi_port[dev] = pnp_port_start(pdev, 3);
	port[dev] = pnp_port_start(pdev, 4);
	dma1[dev] = pnp_dma(pdev, 0);
	dma2[dev] = pnp_dma(pdev, 1);
	irq[dev] = pnp_irq(pdev, 0);
	snd_prपूर्णांकdd("%sPnP OPL3-SA: sb port=0x%lx, wss port=0x%lx, fm port=0x%lx, midi port=0x%lx\n",
		pnp_device_is_pnpbios(pdev) ? "BIOS" : "ISA", sb_port[dev], wss_port[dev], fm_port[dev], midi_port[dev]);
	snd_prपूर्णांकdd("%sPnP OPL3-SA: control port=0x%lx, dma1=%i, dma2=%i, irq=%i\n",
		pnp_device_is_pnpbios(pdev) ? "BIOS" : "ISA", port[dev], dma1[dev], dma2[dev], irq[dev]);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PNP */

अटल व्योम snd_opl3sa2_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_opl3sa2 *chip = card->निजी_data;
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, card);
	release_and_मुक्त_resource(chip->res_port);
पूर्ण

अटल पूर्णांक snd_opl3sa2_card_new(काष्ठा device *pdev, पूर्णांक dev,
				काष्ठा snd_card **cardp)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_opl3sa2 *chip;
	पूर्णांक err;

	err = snd_card_new(pdev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_opl3sa2), &card);
	अगर (err < 0)
		वापस err;
	म_नकल(card->driver, "OPL3SA2");
	म_नकल(card->लघुname, "Yamaha OPL3-SA");
	chip = card->निजी_data;
	spin_lock_init(&chip->reg_lock);
	chip->irq = -1;
	card->निजी_मुक्त = snd_opl3sa2_मुक्त;
	*cardp = card;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl3sa2_probe(काष्ठा snd_card *card, पूर्णांक dev)
अणु
	पूर्णांक xirq, xdma1, xdma2;
	काष्ठा snd_opl3sa2 *chip;
	काष्ठा snd_wss *wss;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक err;

	/* initialise this card from supplied (or शेष) parameter*/ 
	chip = card->निजी_data;
	chip->ymode = opl3sa3_ymode[dev] & 0x03 ;
	chip->port = port[dev];
	xirq = irq[dev];
	xdma1 = dma1[dev];
	xdma2 = dma2[dev];
	अगर (xdma2 < 0)
		chip->single_dma = 1;
	err = snd_opl3sa2_detect(card);
	अगर (err < 0)
		वापस err;
	err = request_irq(xirq, snd_opl3sa2_पूर्णांकerrupt, 0,
			  "OPL3-SA2", card);
	अगर (err) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "can't grab IRQ %d\n", xirq);
		वापस -ENODEV;
	पूर्ण
	chip->irq = xirq;
	card->sync_irq = chip->irq;
	err = snd_wss_create(card,
			     wss_port[dev] + 4, -1,
			     xirq, xdma1, xdma2,
			     WSS_HW_OPL3SA2, WSS_HWSHARE_IRQ, &wss);
	अगर (err < 0) अणु
		snd_prपूर्णांकd("Oops, WSS not detected at 0x%lx\n", wss_port[dev] + 4);
		वापस err;
	पूर्ण
	chip->wss = wss;
	err = snd_wss_pcm(wss, 0);
	अगर (err < 0)
		वापस err;
	err = snd_wss_mixer(wss);
	अगर (err < 0)
		वापस err;
	err = snd_opl3sa2_mixer(card);
	अगर (err < 0)
		वापस err;
	err = snd_wss_समयr(wss, 0);
	अगर (err < 0)
		वापस err;
	अगर (fm_port[dev] >= 0x340 && fm_port[dev] < 0x400) अणु
		अगर ((err = snd_opl3_create(card, fm_port[dev],
					   fm_port[dev] + 2,
					   OPL3_HW_OPL3, 0, &opl3)) < 0)
			वापस err;
		अगर ((err = snd_opl3_समयr_new(opl3, 1, 2)) < 0)
			वापस err;
		अगर ((err = snd_opl3_hwdep_new(opl3, 0, 1, &chip->synth)) < 0)
			वापस err;
	पूर्ण
	अगर (midi_port[dev] >= 0x300 && midi_port[dev] < 0x340) अणु
		अगर ((err = snd_mpu401_uart_new(card, 0, MPU401_HW_OPL3SA2,
					       midi_port[dev],
					       MPU401_INFO_IRQ_HOOK, -1,
					       &chip->rmidi)) < 0)
			वापस err;
	पूर्ण
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d, dma %d",
		card->लघुname, chip->port, xirq, xdma1);
	अगर (xdma2 >= 0)
		प्र_लिखो(card->दीर्घname + म_माप(card->दीर्घname), "&%d", xdma2);

	वापस snd_card_रेजिस्टर(card);
पूर्ण

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_opl3sa2_pnp_detect(काष्ठा pnp_dev *pdev,
				  स्थिर काष्ठा pnp_device_id *id)
अणु
	अटल पूर्णांक dev;
	पूर्णांक err;
	काष्ठा snd_card *card;

	अगर (pnp_device_is_isapnp(pdev))
		वापस -ENOENT;	/* we have another procedure - card */
	क्रम (; dev < SNDRV_CARDS; dev++) अणु
		अगर (enable[dev] && isapnp[dev])
			अवरोध;
	पूर्ण
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;

	err = snd_opl3sa2_card_new(&pdev->dev, dev, &card);
	अगर (err < 0)
		वापस err;
	अगर ((err = snd_opl3sa2_pnp(dev, card->निजी_data, pdev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_opl3sa2_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pnp_set_drvdata(pdev, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_opl3sa2_pnp_हटाओ(काष्ठा pnp_dev *pdev)
अणु
	snd_card_मुक्त(pnp_get_drvdata(pdev));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_opl3sa2_pnp_suspend(काष्ठा pnp_dev *pdev, pm_message_t state)
अणु
	वापस snd_opl3sa2_suspend(pnp_get_drvdata(pdev), state);
पूर्ण
अटल पूर्णांक snd_opl3sa2_pnp_resume(काष्ठा pnp_dev *pdev)
अणु
	वापस snd_opl3sa2_resume(pnp_get_drvdata(pdev));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pnp_driver opl3sa2_pnp_driver = अणु
	.name = "snd-opl3sa2-pnpbios",
	.id_table = snd_opl3sa2_pnpbiosids,
	.probe = snd_opl3sa2_pnp_detect,
	.हटाओ = snd_opl3sa2_pnp_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend = snd_opl3sa2_pnp_suspend,
	.resume = snd_opl3sa2_pnp_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक snd_opl3sa2_pnp_cdetect(काष्ठा pnp_card_link *pcard,
				   स्थिर काष्ठा pnp_card_device_id *id)
अणु
	अटल पूर्णांक dev;
	काष्ठा pnp_dev *pdev;
	पूर्णांक err;
	काष्ठा snd_card *card;

	pdev = pnp_request_card_device(pcard, id->devs[0].id, शून्य);
	अगर (pdev == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "can't get pnp device from id '%s'\n",
			   id->devs[0].id);
		वापस -EBUSY;
	पूर्ण
	क्रम (; dev < SNDRV_CARDS; dev++) अणु
		अगर (enable[dev] && isapnp[dev])
			अवरोध;
	पूर्ण
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;

	err = snd_opl3sa2_card_new(&pdev->dev, dev, &card);
	अगर (err < 0)
		वापस err;
	अगर ((err = snd_opl3sa2_pnp(dev, card->निजी_data, pdev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_opl3sa2_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pnp_set_card_drvdata(pcard, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_opl3sa2_pnp_cहटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_opl3sa2_pnp_csuspend(काष्ठा pnp_card_link *pcard, pm_message_t state)
अणु
	वापस snd_opl3sa2_suspend(pnp_get_card_drvdata(pcard), state);
पूर्ण
अटल पूर्णांक snd_opl3sa2_pnp_cresume(काष्ठा pnp_card_link *pcard)
अणु
	वापस snd_opl3sa2_resume(pnp_get_card_drvdata(pcard));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pnp_card_driver opl3sa2_pnpc_driver = अणु
	.flags = PNP_DRIVER_RES_DISABLE,
	.name = "snd-opl3sa2-cpnp",
	.id_table = snd_opl3sa2_pnpids,
	.probe = snd_opl3sa2_pnp_cdetect,
	.हटाओ = snd_opl3sa2_pnp_cहटाओ,
#अगर_घोषित CONFIG_PM
	.suspend = snd_opl3sa2_pnp_csuspend,
	.resume = snd_opl3sa2_pnp_cresume,
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर /* CONFIG_PNP */

अटल पूर्णांक snd_opl3sa2_isa_match(काष्ठा device *pdev,
				 अचिन्हित पूर्णांक dev)
अणु
	अगर (!enable[dev])
		वापस 0;
#अगर_घोषित CONFIG_PNP
	अगर (isapnp[dev])
		वापस 0;
#पूर्ण_अगर
	अगर (port[dev] == SNDRV_AUTO_PORT) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "specify port\n");
		वापस 0;
	पूर्ण
	अगर (wss_port[dev] == SNDRV_AUTO_PORT) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "specify wss_port\n");
		वापस 0;
	पूर्ण
	अगर (fm_port[dev] == SNDRV_AUTO_PORT) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "specify fm_port\n");
		वापस 0;
	पूर्ण
	अगर (midi_port[dev] == SNDRV_AUTO_PORT) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "specify midi_port\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक snd_opl3sa2_isa_probe(काष्ठा device *pdev,
				 अचिन्हित पूर्णांक dev)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_opl3sa2_card_new(pdev, dev, &card);
	अगर (err < 0)
		वापस err;
	अगर ((err = snd_opl3sa2_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	dev_set_drvdata(pdev, card);
	वापस 0;
पूर्ण

अटल व्योम snd_opl3sa2_isa_हटाओ(काष्ठा device *devptr,
				  अचिन्हित पूर्णांक dev)
अणु
	snd_card_मुक्त(dev_get_drvdata(devptr));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_opl3sa2_isa_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक n,
				   pm_message_t state)
अणु
	वापस snd_opl3sa2_suspend(dev_get_drvdata(dev), state);
पूर्ण

अटल पूर्णांक snd_opl3sa2_isa_resume(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	वापस snd_opl3sa2_resume(dev_get_drvdata(dev));
पूर्ण
#पूर्ण_अगर

#घोषणा DEV_NAME "opl3sa2"

अटल काष्ठा isa_driver snd_opl3sa2_isa_driver = अणु
	.match		= snd_opl3sa2_isa_match,
	.probe		= snd_opl3sa2_isa_probe,
	.हटाओ		= snd_opl3sa2_isa_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_opl3sa2_isa_suspend,
	.resume		= snd_opl3sa2_isa_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init alsa_card_opl3sa2_init(व्योम)
अणु
	पूर्णांक err;

	err = isa_रेजिस्टर_driver(&snd_opl3sa2_isa_driver, SNDRV_CARDS);
#अगर_घोषित CONFIG_PNP
	अगर (!err)
		isa_रेजिस्टरed = 1;

	err = pnp_रेजिस्टर_driver(&opl3sa2_pnp_driver);
	अगर (!err)
		pnp_रेजिस्टरed = 1;

	err = pnp_रेजिस्टर_card_driver(&opl3sa2_pnpc_driver);
	अगर (!err)
		pnpc_रेजिस्टरed = 1;

	अगर (isa_रेजिस्टरed || pnp_रेजिस्टरed)
		err = 0;
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __निकास alsa_card_opl3sa2_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (pnpc_रेजिस्टरed)
		pnp_unरेजिस्टर_card_driver(&opl3sa2_pnpc_driver);
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_driver(&opl3sa2_pnp_driver);
	अगर (isa_रेजिस्टरed)
#पूर्ण_अगर
		isa_unरेजिस्टर_driver(&snd_opl3sa2_isa_driver);
पूर्ण

module_init(alsa_card_opl3sa2_init)
module_निकास(alsa_card_opl3sa2_निकास)
