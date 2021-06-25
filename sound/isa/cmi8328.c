<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम C-Media CMI8328-based soundcards, such as AudioExcel AV500
 * Copyright (c) 2012 Ondrej Zary
 *
 * AudioExcel AV500 card consists of:
 *  - CMI8328 - मुख्य chip (SB Pro emulation, gameport, OPL3, MPU401, CD-ROM)
 *  - CS4231A - WSS codec
 *  - Dream SAM9233+GMS950400+RAM+ROM: Wavetable MIDI, connected to MPU401
 */

#समावेश <linux/init.h>
#समावेश <linux/isa.h>
#समावेश <linux/module.h>
#समावेश <linux/gameport.h>
#समावेश <यंत्र/dma.h>
#समावेश <sound/core.h>
#समावेश <sound/wss.h>
#समावेश <sound/opl3.h>
#समावेश <sound/mpu401.h>
#घोषणा SNDRV_LEGACY_FIND_FREE_IOPORT
#घोषणा SNDRV_LEGACY_FIND_FREE_IRQ
#घोषणा SNDRV_LEGACY_FIND_FREE_DMA
#समावेश <sound/initval.h>

MODULE_AUTHOR("Ondrej Zary <linux@rainbow-software.org>");
MODULE_DESCRIPTION("C-Media CMI8328");
MODULE_LICENSE("GPL");

#अगर IS_ENABLED(CONFIG_GAMEPORT)
#घोषणा SUPPORT_JOYSTICK 1
#पूर्ण_अगर

/* I/O port is configured by jumpers on the card to one of these */
अटल स्थिर पूर्णांक cmi8328_ports[] = अणु 0x530, 0xe80, 0xf40, 0x604 पूर्ण;
#घोषणा CMI8328_MAX	ARRAY_SIZE(cmi8328_ports)

अटल पूर्णांक index[CMI8328_MAX] =     अणु[0 ... (CMI8328_MAX-1)] = -1पूर्ण;
अटल अक्षर *id[CMI8328_MAX] =      अणु[0 ... (CMI8328_MAX-1)] = शून्यपूर्ण;
अटल दीर्घ port[CMI8328_MAX] =     अणु[0 ... (CMI8328_MAX-1)] = SNDRV_AUTO_PORTपूर्ण;
अटल पूर्णांक irq[CMI8328_MAX] =       अणु[0 ... (CMI8328_MAX-1)] = SNDRV_AUTO_IRQपूर्ण;
अटल पूर्णांक dma1[CMI8328_MAX] =      अणु[0 ... (CMI8328_MAX-1)] = SNDRV_AUTO_DMAपूर्ण;
अटल पूर्णांक dma2[CMI8328_MAX] =      अणु[0 ... (CMI8328_MAX-1)] = SNDRV_AUTO_DMAपूर्ण;
अटल दीर्घ mpuport[CMI8328_MAX] =  अणु[0 ... (CMI8328_MAX-1)] = SNDRV_AUTO_PORTपूर्ण;
अटल पूर्णांक mpuirq[CMI8328_MAX] =    अणु[0 ... (CMI8328_MAX-1)] = SNDRV_AUTO_IRQपूर्ण;
#अगर_घोषित SUPPORT_JOYSTICK
अटल bool gameport[CMI8328_MAX] = अणु[0 ... (CMI8328_MAX-1)] = trueपूर्ण;
#पूर्ण_अगर

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for CMI8328 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for CMI8328 soundcard.");

module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for CMI8328 driver.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for CMI8328 driver.");
module_param_hw_array(dma1, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma1, "DMA1 for CMI8328 driver.");
module_param_hw_array(dma2, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma2, "DMA2 for CMI8328 driver.");

module_param_hw_array(mpuport, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpuport, "MPU-401 port # for CMI8328 driver.");
module_param_hw_array(mpuirq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(mpuirq, "IRQ # for CMI8328 MPU-401 port.");
#अगर_घोषित SUPPORT_JOYSTICK
module_param_array(gameport, bool, शून्य, 0444);
MODULE_PARM_DESC(gameport, "Enable gameport.");
#पूर्ण_अगर

काष्ठा snd_cmi8328 अणु
	u16 port;
	u8 cfg[3];
	u8 wss_cfg;
	काष्ठा snd_card *card;
	काष्ठा snd_wss *wss;
#अगर_घोषित SUPPORT_JOYSTICK
	काष्ठा gameport *gameport;
#पूर्ण_अगर
पूर्ण;

/* CMI8328 configuration रेजिस्टरs */
#घोषणा CFG1 0x61
#घोषणा CFG1_SB_DISABLE	(1 << 0)
#घोषणा CFG1_GAMEPORT	(1 << 1)
/*
 * bit 0:    SB: 0=enabled, 1=disabled
 * bit 1:    gameport: 0=disabled, 1=enabled
 * bits 2-4: SB IRQ: 001=3, 010=5, 011=7, 100=9, 101=10, 110=11
 * bits 5-6: SB DMA: 00=disabled (when SB disabled), 01=DMA0, 10=DMA1, 11=DMA3
 * bit 7:    SB port: 0=0x220, 1=0x240
 */
#घोषणा CFG2 0x62
#घोषणा CFG2_MPU_ENABLE (1 << 2)
/*
 * bits 0-1: CD-ROM mode: 00=disabled, 01=Panasonic, 10=Sony/Mitsumi/Wearnes,
			  11=IDE
 * bit 2:    MPU401: 0=disabled, 1=enabled
 * bits 3-4: MPU401 IRQ: 00=3, 01=5, 10=7, 11=9,
 * bits 5-7: MPU401 port: 000=0x300, 001=0x310, 010=0x320, 011=0x330, 100=0x332,
			  101=0x334, 110=0x336
 */
#घोषणा CFG3 0x63
/*
 * bits 0-2: CD-ROM IRQ: 000=disabled, 001=3, 010=5, 011=7, 100=9, 101=10,
			 110=11
 * bits 3-4: CD-ROM DMA: 00=disabled, 01=DMA0, 10=DMA1, 11=DMA3
 * bits 5-7: CD-ROM port: 000=0x300, 001=0x310, 010=0x320, 011=0x330, 100=0x340,
			  101=0x350, 110=0x360, 111=0x370
 */

अटल u8 snd_cmi8328_cfg_पढ़ो(u16 port, u8 reg)
अणु
	outb(0x43, port + 3);
	outb(0x21, port + 3);
	outb(reg, port + 3);
	वापस inb(port);
पूर्ण

अटल व्योम snd_cmi8328_cfg_ग_लिखो(u16 port, u8 reg, u8 val)
अणु
	outb(0x43, port + 3);
	outb(0x21, port + 3);
	outb(reg, port + 3);
	outb(val, port + 3);	/* yes, value goes to the same port as index */
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम snd_cmi8328_cfg_save(u16 port, u8 cfg[])
अणु
	cfg[0] = snd_cmi8328_cfg_पढ़ो(port, CFG1);
	cfg[1] = snd_cmi8328_cfg_पढ़ो(port, CFG2);
	cfg[2] = snd_cmi8328_cfg_पढ़ो(port, CFG3);
पूर्ण

अटल व्योम snd_cmi8328_cfg_restore(u16 port, u8 cfg[])
अणु
	snd_cmi8328_cfg_ग_लिखो(port, CFG1, cfg[0]);
	snd_cmi8328_cfg_ग_लिखो(port, CFG2, cfg[1]);
	snd_cmi8328_cfg_ग_लिखो(port, CFG3, cfg[2]);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक snd_cmi8328_mixer(काष्ठा snd_wss *chip)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_ctl_elem_id id1, id2;
	पूर्णांक err;

	card = chip->card;

	स_रखो(&id1, 0, माप(id1));
	स_रखो(&id2, 0, माप(id2));
	id1.अगरace = id2.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	/* नाम AUX0 चयन to CD */
	म_नकल(id1.name, "Aux Playback Switch");
	म_नकल(id2.name, "CD Playback Switch");
	err = snd_ctl_नाम_id(card, &id1, &id2);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "error renaming control\n");
		वापस err;
	पूर्ण
	/* नाम AUX0 volume to CD */
	म_नकल(id1.name, "Aux Playback Volume");
	म_नकल(id2.name, "CD Playback Volume");
	err = snd_ctl_नाम_id(card, &id1, &id2);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "error renaming control\n");
		वापस err;
	पूर्ण
	/* नाम AUX1 चयन to Synth */
	म_नकल(id1.name, "Aux Playback Switch");
	id1.index = 1;
	म_नकल(id2.name, "Synth Playback Switch");
	err = snd_ctl_नाम_id(card, &id1, &id2);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "error renaming control\n");
		वापस err;
	पूर्ण
	/* नाम AUX1 volume to Synth */
	म_नकल(id1.name, "Aux Playback Volume");
	id1.index = 1;
	म_नकल(id2.name, "Synth Playback Volume");
	err = snd_ctl_नाम_id(card, &id1, &id2);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "error renaming control\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* find index of an item in "-1"-ended array */
अटल पूर्णांक array_find(स्थिर पूर्णांक array[], पूर्णांक item)
अणु
	पूर्णांक i;

	क्रम (i = 0; array[i] != -1; i++)
		अगर (array[i] == item)
			वापस i;

	वापस -1;
पूर्ण
/* the same क्रम दीर्घ */
अटल पूर्णांक array_find_l(स्थिर दीर्घ array[], दीर्घ item)
अणु
	पूर्णांक i;

	क्रम (i = 0; array[i] != -1; i++)
		अगर (array[i] == item)
			वापस i;

	वापस -1;
पूर्ण

अटल पूर्णांक snd_cmi8328_probe(काष्ठा device *pdev, अचिन्हित पूर्णांक ndev)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_opl3 *opl3;
	काष्ठा snd_cmi8328 *cmi;
#अगर_घोषित SUPPORT_JOYSTICK
	काष्ठा resource *res;
#पूर्ण_अगर
	पूर्णांक err, pos;
	अटल स्थिर दीर्घ mpu_ports[] = अणु 0x330, 0x300, 0x310, 0x320, 0x332, 0x334,
				   0x336, -1 पूर्ण;
	अटल स्थिर u8 mpu_port_bits[] = अणु 3, 0, 1, 2, 4, 5, 6 पूर्ण;
	अटल स्थिर पूर्णांक mpu_irqs[] = अणु 9, 7, 5, 3, -1 पूर्ण;
	अटल स्थिर u8 mpu_irq_bits[] = अणु 3, 2, 1, 0 पूर्ण;
	अटल स्थिर पूर्णांक irqs[] = अणु 9, 10, 11, 7, -1 पूर्ण;
	अटल स्थिर u8 irq_bits[] = अणु 2, 3, 4, 1 पूर्ण;
	अटल स्थिर पूर्णांक dma1s[] = अणु 3, 1, 0, -1 पूर्ण;
	अटल स्थिर u8 dma_bits[] = अणु 3, 2, 1 पूर्ण;
	अटल स्थिर पूर्णांक dma2s[][2] = अणु अणु1, -1पूर्ण, अणु0, -1पूर्ण, अणु-1, -1पूर्ण, अणु0, -1पूर्ण पूर्ण;
	u16 port = cmi8328_ports[ndev];
	u8 val;

	/* 0xff is invalid configuration (but settable - hope it isn't set) */
	अगर (snd_cmi8328_cfg_पढ़ो(port, CFG1) == 0xff)
		वापस -ENODEV;
	/* the SB disable bit must NEVER EVER be cleared or the WSS dies */
	snd_cmi8328_cfg_ग_लिखो(port, CFG1, CFG1_SB_DISABLE);
	अगर (snd_cmi8328_cfg_पढ़ो(port, CFG1) != CFG1_SB_DISABLE)
		वापस -ENODEV;
	/* disable everything first */
	snd_cmi8328_cfg_ग_लिखो(port, CFG2, 0);	/* disable CDROM and MPU401 */
	snd_cmi8328_cfg_ग_लिखो(port, CFG3, 0);	/* disable CDROM IRQ and DMA */

	अगर (irq[ndev] == SNDRV_AUTO_IRQ) अणु
		irq[ndev] = snd_legacy_find_मुक्त_irq(irqs);
		अगर (irq[ndev] < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "unable to find a free IRQ\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma1[ndev] == SNDRV_AUTO_DMA) अणु
		dma1[ndev] = snd_legacy_find_मुक्त_dma(dma1s);
		अगर (dma1[ndev] < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "unable to find a free DMA1\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma2[ndev] == SNDRV_AUTO_DMA) अणु
		dma2[ndev] = snd_legacy_find_मुक्त_dma(dma2s[dma1[ndev] % 4]);
		अगर (dma2[ndev] < 0) अणु
			snd_prपूर्णांकk(KERN_WARNING "unable to find a free DMA2, full-duplex will not work\n");
			dma2[ndev] = -1;
		पूर्ण
	पूर्ण
	/* configure WSS IRQ... */
	pos = array_find(irqs, irq[ndev]);
	अगर (pos < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "invalid IRQ %d\n", irq[ndev]);
		वापस -EINVAL;
	पूर्ण
	val = irq_bits[pos] << 3;
	/* ...and DMA... */
	pos = array_find(dma1s, dma1[ndev]);
	अगर (pos < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "invalid DMA1 %d\n", dma1[ndev]);
		वापस -EINVAL;
	पूर्ण
	val |= dma_bits[pos];
	/* ...and DMA2 */
	अगर (dma2[ndev] >= 0 && dma1[ndev] != dma2[ndev]) अणु
		pos = array_find(dma2s[dma1[ndev]], dma2[ndev]);
		अगर (pos < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "invalid DMA2 %d\n", dma2[ndev]);
			वापस -EINVAL;
		पूर्ण
		val |= 0x04; /* enable separate capture DMA */
	पूर्ण
	outb(val, port);

	err = snd_card_new(pdev, index[ndev], id[ndev], THIS_MODULE,
			   माप(काष्ठा snd_cmi8328), &card);
	अगर (err < 0)
		वापस err;
	cmi = card->निजी_data;
	cmi->card = card;
	cmi->port = port;
	cmi->wss_cfg = val;

	err = snd_wss_create(card, port + 4, -1, irq[ndev], dma1[ndev],
			dma2[ndev], WSS_HW_DETECT, 0, &cmi->wss);
	अगर (err < 0)
		जाओ error;

	err = snd_wss_pcm(cmi->wss, 0);
	अगर (err < 0)
		जाओ error;

	err = snd_wss_mixer(cmi->wss);
	अगर (err < 0)
		जाओ error;
	err = snd_cmi8328_mixer(cmi->wss);
	अगर (err < 0)
		जाओ error;

	अगर (snd_wss_समयr(cmi->wss, 0) < 0)
		snd_prपूर्णांकk(KERN_WARNING "error initializing WSS timer\n");

	अगर (mpuport[ndev] == SNDRV_AUTO_PORT) अणु
		mpuport[ndev] = snd_legacy_find_मुक्त_ioport(mpu_ports, 2);
		अगर (mpuport[ndev] < 0)
			snd_prपूर्णांकk(KERN_ERR "unable to find a free MPU401 port\n");
	पूर्ण
	अगर (mpuirq[ndev] == SNDRV_AUTO_IRQ) अणु
		mpuirq[ndev] = snd_legacy_find_मुक्त_irq(mpu_irqs);
		अगर (mpuirq[ndev] < 0)
			snd_prपूर्णांकk(KERN_ERR "unable to find a free MPU401 IRQ\n");
	पूर्ण
	/* enable and configure MPU401 */
	अगर (mpuport[ndev] > 0 && mpuirq[ndev] > 0) अणु
		val = CFG2_MPU_ENABLE;
		pos = array_find_l(mpu_ports, mpuport[ndev]);
		अगर (pos < 0)
			snd_prपूर्णांकk(KERN_WARNING "invalid MPU401 port 0x%lx\n",
								mpuport[ndev]);
		अन्यथा अणु
			val |= mpu_port_bits[pos] << 5;
			pos = array_find(mpu_irqs, mpuirq[ndev]);
			अगर (pos < 0)
				snd_prपूर्णांकk(KERN_WARNING "invalid MPU401 IRQ %d\n",
								mpuirq[ndev]);
			अन्यथा अणु
				val |= mpu_irq_bits[pos] << 3;
				snd_cmi8328_cfg_ग_लिखो(port, CFG2, val);
				अगर (snd_mpu401_uart_new(card, 0,
						MPU401_HW_MPU401, mpuport[ndev],
						0, mpuirq[ndev], शून्य) < 0)
					snd_prपूर्णांकk(KERN_ERR "error initializing MPU401\n");
			पूर्ण
		पूर्ण
	पूर्ण
	/* OPL3 is hardwired to 0x388 and cannot be disabled */
	अगर (snd_opl3_create(card, 0x388, 0x38a, OPL3_HW_AUTO, 0, &opl3) < 0)
		snd_prपूर्णांकk(KERN_ERR "error initializing OPL3\n");
	अन्यथा
		अगर (snd_opl3_hwdep_new(opl3, 0, 1, शून्य) < 0)
			snd_prपूर्णांकk(KERN_WARNING "error initializing OPL3 hwdep\n");

	म_नकल(card->driver, "CMI8328");
	म_नकल(card->लघुname, "C-Media CMI8328");
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d, dma %d,%d",
		card->लघुname, cmi->wss->port, irq[ndev], dma1[ndev],
		(dma2[ndev] >= 0) ? dma2[ndev] : dma1[ndev]);

	dev_set_drvdata(pdev, card);
	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ error;
#अगर_घोषित SUPPORT_JOYSTICK
	अगर (!gameport[ndev])
		वापस 0;
	/* gameport is hardwired to 0x200 */
	res = request_region(0x200, 8, "CMI8328 gameport");
	अगर (!res)
		snd_prपूर्णांकk(KERN_WARNING "unable to allocate gameport I/O port\n");
	अन्यथा अणु
		काष्ठा gameport *gp = cmi->gameport = gameport_allocate_port();
		अगर (!cmi->gameport)
			release_and_मुक्त_resource(res);
		अन्यथा अणु
			gameport_set_name(gp, "CMI8328 Gameport");
			gameport_set_phys(gp, "%s/gameport0", dev_name(pdev));
			gameport_set_dev_parent(gp, pdev);
			gp->io = 0x200;
			gameport_set_port_data(gp, res);
			/* Enable gameport */
			snd_cmi8328_cfg_ग_लिखो(port, CFG1,
					CFG1_SB_DISABLE | CFG1_GAMEPORT);
			gameport_रेजिस्टर_port(gp);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
error:
	snd_card_मुक्त(card);

	वापस err;
पूर्ण

अटल व्योम snd_cmi8328_हटाओ(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(pdev);
	काष्ठा snd_cmi8328 *cmi = card->निजी_data;

#अगर_घोषित SUPPORT_JOYSTICK
	अगर (cmi->gameport) अणु
		काष्ठा resource *res = gameport_get_port_data(cmi->gameport);
		gameport_unरेजिस्टर_port(cmi->gameport);
		release_and_मुक्त_resource(res);
	पूर्ण
#पूर्ण_अगर
	/* disable everything */
	snd_cmi8328_cfg_ग_लिखो(cmi->port, CFG1, CFG1_SB_DISABLE);
	snd_cmi8328_cfg_ग_लिखो(cmi->port, CFG2, 0);
	snd_cmi8328_cfg_ग_लिखो(cmi->port, CFG3, 0);
	snd_card_मुक्त(card);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_cmi8328_suspend(काष्ठा device *pdev, अचिन्हित पूर्णांक n,
				pm_message_t state)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(pdev);
	काष्ठा snd_cmi8328 *cmi;

	अगर (!card)	/* ignore असलent devices */
		वापस 0;
	cmi = card->निजी_data;
	snd_cmi8328_cfg_save(cmi->port, cmi->cfg);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	cmi->wss->suspend(cmi->wss);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmi8328_resume(काष्ठा device *pdev, अचिन्हित पूर्णांक n)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(pdev);
	काष्ठा snd_cmi8328 *cmi;

	अगर (!card)	/* ignore असलent devices */
		वापस 0;
	cmi = card->निजी_data;
	snd_cmi8328_cfg_restore(cmi->port, cmi->cfg);
	outb(cmi->wss_cfg, cmi->port);
	cmi->wss->resume(cmi->wss);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा isa_driver snd_cmi8328_driver = अणु
	.probe		= snd_cmi8328_probe,
	.हटाओ		= snd_cmi8328_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_cmi8328_suspend,
	.resume		= snd_cmi8328_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= "cmi8328"
	पूर्ण,
पूर्ण;

module_isa_driver(snd_cmi8328_driver, CMI8328_MAX);
