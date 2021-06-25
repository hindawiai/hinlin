<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Gravis UltraSound Extreme soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/delay.h>
#समावेश <linux/समय.स>
#समावेश <linux/module.h>
#समावेश <यंत्र/dma.h>
#समावेश <sound/core.h>
#समावेश <sound/gus.h>
#समावेश <sound/es1688.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#घोषणा SNDRV_LEGACY_AUTO_PROBE
#घोषणा SNDRV_LEGACY_FIND_FREE_IRQ
#घोषणा SNDRV_LEGACY_FIND_FREE_DMA
#समावेश <sound/initval.h>

#घोषणा CRD_NAME "Gravis UltraSound Extreme"
#घोषणा DEV_NAME "gusextreme"

MODULE_DESCRIPTION(CRD_NAME);
MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;	/* Enable this card */
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x220,0x240,0x260 */
अटल दीर्घ gf1_port[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS) - 1] = -1पूर्ण; /* 0x210,0x220,0x230,0x240,0x250,0x260,0x270 */
अटल दीर्घ mpu_port[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS) - 1] = -1पूर्ण; /* 0x300,0x310,0x320 */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 5,7,9,10 */
अटल पूर्णांक mpu_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 5,7,9,10 */
अटल पूर्णांक gf1_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 2,3,5,9,11,12,15 */
अटल पूर्णांक dma8[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 0,1,3 */
अटल पूर्णांक dma1[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;
अटल पूर्णांक joystick_dac[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 29पूर्ण;
				/* 0 to 31, (0.59V-4.52V or 0.389V-2.98V) */
अटल पूर्णांक channels[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 24पूर्ण;
अटल पूर्णांक pcm_channels[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 2पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " CRD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " CRD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable " CRD_NAME " soundcard.");
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for " CRD_NAME " driver.");
module_param_hw_array(gf1_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(gf1_port, "GF1 port # for " CRD_NAME " driver (optional).");
module_param_hw_array(mpu_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 port # for " CRD_NAME " driver.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for " CRD_NAME " driver.");
module_param_hw_array(mpu_irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(mpu_irq, "MPU-401 IRQ # for " CRD_NAME " driver.");
module_param_hw_array(gf1_irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(gf1_irq, "GF1 IRQ # for " CRD_NAME " driver.");
module_param_hw_array(dma8, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma8, "8-bit DMA # for " CRD_NAME " driver.");
module_param_hw_array(dma1, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma1, "GF1 DMA # for " CRD_NAME " driver.");
module_param_array(joystick_dac, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(joystick_dac, "Joystick DAC level 0.59V-4.52V or 0.389V-2.98V for " CRD_NAME " driver.");
module_param_array(channels, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(channels, "GF1 channels for " CRD_NAME " driver.");
module_param_array(pcm_channels, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pcm_channels, "Reserved PCM channels for " CRD_NAME " driver.");

अटल पूर्णांक snd_gusextreme_match(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	वापस enable[n];
पूर्ण

अटल पूर्णांक snd_gusextreme_es1688_create(काष्ठा snd_card *card,
					काष्ठा snd_es1688 *chip,
					काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	अटल स्थिर दीर्घ possible_ports[] = अणु0x220, 0x240, 0x260पूर्ण;
	अटल स्थिर पूर्णांक possible_irqs[] = अणु5, 9, 10, 7, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dmas[] = अणु1, 3, 0, -1पूर्ण;

	पूर्णांक i, error;

	अगर (irq[n] == SNDRV_AUTO_IRQ) अणु
		irq[n] = snd_legacy_find_मुक्त_irq(possible_irqs);
		अगर (irq[n] < 0) अणु
			dev_err(dev, "unable to find a free IRQ for ES1688\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma8[n] == SNDRV_AUTO_DMA) अणु
		dma8[n] = snd_legacy_find_मुक्त_dma(possible_dmas);
		अगर (dma8[n] < 0) अणु
			dev_err(dev, "unable to find a free DMA for ES1688\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (port[n] != SNDRV_AUTO_PORT)
		वापस snd_es1688_create(card, chip, port[n], mpu_port[n],
				irq[n], mpu_irq[n], dma8[n], ES1688_HW_1688);

	i = 0;
	करो अणु
		port[n] = possible_ports[i];
		error = snd_es1688_create(card, chip, port[n], mpu_port[n],
				irq[n], mpu_irq[n], dma8[n], ES1688_HW_1688);
	पूर्ण जबतक (error < 0 && ++i < ARRAY_SIZE(possible_ports));

	वापस error;
पूर्ण

अटल पूर्णांक snd_gusextreme_gus_card_create(काष्ठा snd_card *card,
					  काष्ठा device *dev, अचिन्हित पूर्णांक n,
					  काष्ठा snd_gus_card **rgus)
अणु
	अटल स्थिर पूर्णांक possible_irqs[] = अणु11, 12, 15, 9, 5, 7, 3, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dmas[] = अणु5, 6, 7, 3, 1, -1पूर्ण;

	अगर (gf1_irq[n] == SNDRV_AUTO_IRQ) अणु
		gf1_irq[n] = snd_legacy_find_मुक्त_irq(possible_irqs);
		अगर (gf1_irq[n] < 0) अणु
			dev_err(dev, "unable to find a free IRQ for GF1\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma1[n] == SNDRV_AUTO_DMA) अणु
		dma1[n] = snd_legacy_find_मुक्त_dma(possible_dmas);
		अगर (dma1[n] < 0) अणु
			dev_err(dev, "unable to find a free DMA for GF1\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	वापस snd_gus_create(card, gf1_port[n], gf1_irq[n], dma1[n], -1,
			0, channels[n], pcm_channels[n], 0, rgus);
पूर्ण

अटल पूर्णांक snd_gusextreme_detect(काष्ठा snd_gus_card *gus,
				 काष्ठा snd_es1688 *es1688)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर d;

	/*
	 * This is मुख्य stuff - enable access to GF1 chip...
	 * I'm not sure, अगर this will work क्रम card which have
	 * ES1688 chip in another place than 0x220.
         *
         * I used reverse-engineering in DOSEMU. [--jk]
	 *
	 * ULTRINIT.EXE:
	 * 0x230 = 0,2,3
	 * 0x240 = 2,0,1
	 * 0x250 = 2,0,3
	 * 0x260 = 2,2,1
	 */

	spin_lock_irqsave(&es1688->mixer_lock, flags);
	snd_es1688_mixer_ग_लिखो(es1688, 0x40, 0x0b);	/* करोn't change!!! */
	spin_unlock_irqrestore(&es1688->mixer_lock, flags);

	spin_lock_irqsave(&es1688->reg_lock, flags);
	outb(gus->gf1.port & 0x040 ? 2 : 0, ES1688P(es1688, INIT1));
	outb(0, 0x201);
	outb(gus->gf1.port & 0x020 ? 2 : 0, ES1688P(es1688, INIT1));
	outb(0, 0x201);
	outb(gus->gf1.port & 0x010 ? 3 : 1, ES1688P(es1688, INIT1));
	spin_unlock_irqrestore(&es1688->reg_lock, flags);

	udelay(100);

	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 0);	/* reset GF1 */
	अगर (((d = snd_gf1_i_look8(gus, SNDRV_GF1_GB_RESET)) & 0x07) != 0) अणु
		snd_prपूर्णांकdd("[0x%lx] check 1 failed - 0x%x\n", gus->gf1.port, d);
		वापस -EIO;
	पूर्ण
	udelay(160);
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 1);	/* release reset */
	udelay(160);
	अगर (((d = snd_gf1_i_look8(gus, SNDRV_GF1_GB_RESET)) & 0x07) != 1) अणु
		snd_prपूर्णांकdd("[0x%lx] check 2 failed - 0x%x\n", gus->gf1.port, d);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_gusextreme_mixer(काष्ठा snd_card *card)
अणु
	काष्ठा snd_ctl_elem_id id1, id2;
	पूर्णांक error;

	स_रखो(&id1, 0, माप(id1));
	स_रखो(&id2, 0, माप(id2));
	id1.अगरace = id2.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;

	/* reassign AUX to SYNTHESIZER */
	म_नकल(id1.name, "Aux Playback Volume");
	म_नकल(id2.name, "Synth Playback Volume");
	error = snd_ctl_नाम_id(card, &id1, &id2);
	अगर (error < 0)
		वापस error;

	/* reassign Master Playback Switch to Synth Playback Switch */
	म_नकल(id1.name, "Master Playback Switch");
	म_नकल(id2.name, "Synth Playback Switch");
	error = snd_ctl_नाम_id(card, &id1, &id2);
	अगर (error < 0)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_gusextreme_probe(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_gus_card *gus;
	काष्ठा snd_es1688 *es1688;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक error;

	error = snd_card_new(dev, index[n], id[n], THIS_MODULE,
			     माप(काष्ठा snd_es1688), &card);
	अगर (error < 0)
		वापस error;

	es1688 = card->निजी_data;

	अगर (mpu_port[n] == SNDRV_AUTO_PORT)
		mpu_port[n] = 0;

	अगर (mpu_irq[n] > 15)
		mpu_irq[n] = -1;

	error = snd_gusextreme_es1688_create(card, es1688, dev, n);
	अगर (error < 0)
		जाओ out;

	अगर (gf1_port[n] < 0)
		gf1_port[n] = es1688->port + 0x20;

	error = snd_gusextreme_gus_card_create(card, dev, n, &gus);
	अगर (error < 0)
		जाओ out;

	error = snd_gusextreme_detect(gus, es1688);
	अगर (error < 0)
		जाओ out;

	gus->joystick_dac = joystick_dac[n];

	error = snd_gus_initialize(gus);
	अगर (error < 0)
		जाओ out;

	error = -ENODEV;
	अगर (!gus->ess_flag) अणु
		dev_err(dev, "GUS Extreme soundcard was not "
			"detected at 0x%lx\n", gus->gf1.port);
		जाओ out;
	पूर्ण
	gus->codec_flag = 1;

	error = snd_es1688_pcm(card, es1688, 0);
	अगर (error < 0)
		जाओ out;

	error = snd_es1688_mixer(card, es1688);
	अगर (error < 0)
		जाओ out;

	snd_component_add(card, "ES1688");

	अगर (pcm_channels[n] > 0) अणु
		error = snd_gf1_pcm_new(gus, 1, 1);
		अगर (error < 0)
			जाओ out;
	पूर्ण

	error = snd_gf1_new_mixer(gus);
	अगर (error < 0)
		जाओ out;

	error = snd_gusextreme_mixer(card);
	अगर (error < 0)
		जाओ out;

	अगर (snd_opl3_create(card, es1688->port, es1688->port + 2,
			OPL3_HW_OPL3, 0, &opl3) < 0)
		dev_warn(dev, "opl3 not detected at 0x%lx\n", es1688->port);
	अन्यथा अणु
		error = snd_opl3_hwdep_new(opl3, 0, 2, शून्य);
		अगर (error < 0)
			जाओ out;
	पूर्ण

	अगर (es1688->mpu_port >= 0x300) अणु
		error = snd_mpu401_uart_new(card, 0, MPU401_HW_ES1688,
				es1688->mpu_port, 0, mpu_irq[n], शून्य);
		अगर (error < 0)
			जाओ out;
	पूर्ण

	प्र_लिखो(card->दीर्घname, "Gravis UltraSound Extreme at 0x%lx, "
		"irq %i&%i, dma %i&%i", es1688->port,
		gus->gf1.irq, es1688->irq, gus->gf1.dma1, es1688->dma8);

	error = snd_card_रेजिस्टर(card);
	अगर (error < 0)
		जाओ out;

	dev_set_drvdata(dev, card);
	वापस 0;

out:	snd_card_मुक्त(card);
	वापस error;
पूर्ण

अटल व्योम snd_gusextreme_हटाओ(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	snd_card_मुक्त(dev_get_drvdata(dev));
पूर्ण

अटल काष्ठा isa_driver snd_gusextreme_driver = अणु
	.match		= snd_gusextreme_match,
	.probe		= snd_gusextreme_probe,
	.हटाओ		= snd_gusextreme_हटाओ,
#अगर 0	/* FIXME */
	.suspend	= snd_gusextreme_suspend,
	.resume		= snd_gusextreme_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण
पूर्ण;

module_isa_driver(snd_gusextreme_driver, SNDRV_CARDS);
