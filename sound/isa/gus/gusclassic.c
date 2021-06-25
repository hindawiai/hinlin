<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Gravis UltraSound Classic soundcard
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
#घोषणा SNDRV_LEGACY_FIND_FREE_IRQ
#घोषणा SNDRV_LEGACY_FIND_FREE_DMA
#समावेश <sound/initval.h>

#घोषणा CRD_NAME "Gravis UltraSound Classic"
#घोषणा DEV_NAME "gusclassic"

MODULE_DESCRIPTION(CRD_NAME);
MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;	/* Enable this card */
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x220,0x230,0x240,0x250,0x260 */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 3,5,9,11,12,15 */
अटल पूर्णांक dma1[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 1,3,5,6,7 */
अटल पूर्णांक dma2[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 1,3,5,6,7 */
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
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for " CRD_NAME " driver.");
module_param_hw_array(dma1, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma1, "DMA1 # for " CRD_NAME " driver.");
module_param_hw_array(dma2, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma2, "DMA2 # for " CRD_NAME " driver.");
module_param_array(joystick_dac, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(joystick_dac, "Joystick DAC level 0.59V-4.52V or 0.389V-2.98V for " CRD_NAME " driver.");
module_param_array(channels, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(channels, "GF1 channels for " CRD_NAME " driver.");
module_param_array(pcm_channels, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pcm_channels, "Reserved PCM channels for " CRD_NAME " driver.");

अटल पूर्णांक snd_gusclassic_match(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	वापस enable[n];
पूर्ण

अटल पूर्णांक snd_gusclassic_create(काष्ठा snd_card *card,
				 काष्ठा device *dev, अचिन्हित पूर्णांक n,
				 काष्ठा snd_gus_card **rgus)
अणु
	अटल स्थिर दीर्घ possible_ports[] = अणु0x220, 0x230, 0x240, 0x250, 0x260पूर्ण;
	अटल स्थिर पूर्णांक possible_irqs[] = अणु5, 11, 12, 9, 7, 15, 3, 4, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dmas[] = अणु5, 6, 7, 1, 3, -1पूर्ण;

	पूर्णांक i, error;

	अगर (irq[n] == SNDRV_AUTO_IRQ) अणु
		irq[n] = snd_legacy_find_मुक्त_irq(possible_irqs);
		अगर (irq[n] < 0) अणु
			dev_err(dev, "unable to find a free IRQ\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma1[n] == SNDRV_AUTO_DMA) अणु
		dma1[n] = snd_legacy_find_मुक्त_dma(possible_dmas);
		अगर (dma1[n] < 0) अणु
			dev_err(dev, "unable to find a free DMA1\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma2[n] == SNDRV_AUTO_DMA) अणु
		dma2[n] = snd_legacy_find_मुक्त_dma(possible_dmas);
		अगर (dma2[n] < 0) अणु
			dev_err(dev, "unable to find a free DMA2\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (port[n] != SNDRV_AUTO_PORT)
		वापस snd_gus_create(card, port[n], irq[n], dma1[n], dma2[n],
				0, channels[n], pcm_channels[n], 0, rgus);

	i = 0;
	करो अणु
		port[n] = possible_ports[i];
		error = snd_gus_create(card, port[n], irq[n], dma1[n], dma2[n],
				0, channels[n], pcm_channels[n], 0, rgus);
	पूर्ण जबतक (error < 0 && ++i < ARRAY_SIZE(possible_ports));

	वापस error;
पूर्ण

अटल पूर्णांक snd_gusclassic_detect(काष्ठा snd_gus_card *gus)
अणु
	अचिन्हित अक्षर d;

	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 0);	/* reset GF1 */
	अगर (((d = snd_gf1_i_look8(gus, SNDRV_GF1_GB_RESET)) & 0x07) != 0) अणु
		snd_prपूर्णांकdd("[0x%lx] check 1 failed - 0x%x\n", gus->gf1.port, d);
		वापस -ENODEV;
	पूर्ण
	udelay(160);
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 1);	/* release reset */
	udelay(160);
	अगर (((d = snd_gf1_i_look8(gus, SNDRV_GF1_GB_RESET)) & 0x07) != 1) अणु
		snd_prपूर्णांकdd("[0x%lx] check 2 failed - 0x%x\n", gus->gf1.port, d);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gusclassic_probe(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_gus_card *gus;
	पूर्णांक error;

	error = snd_card_new(dev, index[n], id[n], THIS_MODULE, 0, &card);
	अगर (error < 0)
		वापस error;

	अगर (pcm_channels[n] < 2)
		pcm_channels[n] = 2;

	error = snd_gusclassic_create(card, dev, n, &gus);
	अगर (error < 0)
		जाओ out;

	error = snd_gusclassic_detect(gus);
	अगर (error < 0)
		जाओ out;

	gus->joystick_dac = joystick_dac[n];

	error = snd_gus_initialize(gus);
	अगर (error < 0)
		जाओ out;

	error = -ENODEV;
	अगर (gus->max_flag || gus->ess_flag) अणु
		dev_err(dev, "GUS Classic or ACE soundcard was "
			"not detected at 0x%lx\n", gus->gf1.port);
		जाओ out;
	पूर्ण

	error = snd_gf1_new_mixer(gus);
	अगर (error < 0)
		जाओ out;

	error = snd_gf1_pcm_new(gus, 0, 0);
	अगर (error < 0)
		जाओ out;

	अगर (!gus->ace_flag) अणु
		error = snd_gf1_rawmidi_new(gus, 0);
		अगर (error < 0)
			जाओ out;
	पूर्ण

	प्र_लिखो(card->दीर्घname + म_माप(card->दीर्घname),
		" at 0x%lx, irq %d, dma %d",
		gus->gf1.port, gus->gf1.irq, gus->gf1.dma1);

	अगर (gus->gf1.dma2 >= 0)
		प्र_लिखो(card->दीर्घname + म_माप(card->दीर्घname),
			"&%d", gus->gf1.dma2);

	error = snd_card_रेजिस्टर(card);
	अगर (error < 0)
		जाओ out;

	dev_set_drvdata(dev, card);
	वापस 0;

out:	snd_card_मुक्त(card);
	वापस error;
पूर्ण

अटल व्योम snd_gusclassic_हटाओ(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	snd_card_मुक्त(dev_get_drvdata(dev));
पूर्ण

अटल काष्ठा isa_driver snd_gusclassic_driver = अणु
	.match		= snd_gusclassic_match,
	.probe		= snd_gusclassic_probe,
	.हटाओ		= snd_gusclassic_हटाओ,
#अगर 0	/* FIXME */
	.suspend	= snd_gusclassic_suspend,
	.हटाओ		= snd_gusclassic_हटाओ,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण
पूर्ण;

module_isa_driver(snd_gusclassic_driver, SNDRV_CARDS);
