<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Gravis UltraSound MAX soundcard
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
#समावेश <sound/wss.h>
#घोषणा SNDRV_LEGACY_FIND_FREE_IRQ
#घोषणा SNDRV_LEGACY_FIND_FREE_DMA
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Gravis UltraSound MAX");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;	/* Enable this card */
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x220,0x230,0x240,0x250,0x260 */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 2,3,5,9,11,12,15 */
अटल पूर्णांक dma1[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 1,3,5,6,7 */
अटल पूर्णांक dma2[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 1,3,5,6,7 */
अटल पूर्णांक joystick_dac[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 29पूर्ण;
				/* 0 to 31, (0.59V-4.52V or 0.389V-2.98V) */
अटल पूर्णांक channels[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 24पूर्ण;
अटल पूर्णांक pcm_channels[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 2पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for GUS MAX soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for GUS MAX soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable GUS MAX soundcard.");
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for GUS MAX driver.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for GUS MAX driver.");
module_param_hw_array(dma1, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma1, "DMA1 # for GUS MAX driver.");
module_param_hw_array(dma2, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma2, "DMA2 # for GUS MAX driver.");
module_param_array(joystick_dac, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(joystick_dac, "Joystick DAC level 0.59V-4.52V or 0.389V-2.98V for GUS MAX driver.");
module_param_array(channels, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(channels, "Used GF1 channels for GUS MAX driver.");
module_param_array(pcm_channels, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pcm_channels, "Reserved PCM channels for GUS MAX driver.");

काष्ठा snd_gusmax अणु
	पूर्णांक irq;
	काष्ठा snd_card *card;
	काष्ठा snd_gus_card *gus;
	काष्ठा snd_wss *wss;
	अचिन्हित लघु gus_status_reg;
	अचिन्हित लघु pcm_status_reg;
पूर्ण;

#घोषणा PFX	"gusmax: "

अटल पूर्णांक snd_gusmax_detect(काष्ठा snd_gus_card *gus)
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

अटल irqवापस_t snd_gusmax_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_gusmax *maxcard = dev_id;
	पूर्णांक loop, max = 5;
	पूर्णांक handled = 0;

	करो अणु
		loop = 0;
		अगर (inb(maxcard->gus_status_reg)) अणु
			handled = 1;
			snd_gus_पूर्णांकerrupt(irq, maxcard->gus);
			loop++;
		पूर्ण
		अगर (inb(maxcard->pcm_status_reg) & 0x01) अणु /* IRQ bit is set? */
			handled = 1;
			snd_wss_पूर्णांकerrupt(irq, maxcard->wss);
			loop++;
		पूर्ण
	पूर्ण जबतक (loop && --max > 0);
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम snd_gusmax_init(पूर्णांक dev, काष्ठा snd_card *card,
			    काष्ठा snd_gus_card *gus)
अणु
	gus->equal_irq = 1;
	gus->codec_flag = 1;
	gus->joystick_dac = joystick_dac[dev];
	/* init control रेजिस्टर */
	gus->max_cntrl_val = (gus->gf1.port >> 4) & 0x0f;
	अगर (gus->gf1.dma1 > 3)
		gus->max_cntrl_val |= 0x10;
	अगर (gus->gf1.dma2 > 3)
		gus->max_cntrl_val |= 0x20;
	gus->max_cntrl_val |= 0x40;
	outb(gus->max_cntrl_val, GUSP(gus, MAXCNTRLPORT));
पूर्ण

अटल पूर्णांक snd_gusmax_mixer(काष्ठा snd_wss *chip)
अणु
	काष्ठा snd_card *card = chip->card;
	काष्ठा snd_ctl_elem_id id1, id2;
	पूर्णांक err;
	
	स_रखो(&id1, 0, माप(id1));
	स_रखो(&id2, 0, माप(id2));
	id1.अगरace = id2.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	/* reassign AUXA to SYNTHESIZER */
	म_नकल(id1.name, "Aux Playback Switch");
	म_नकल(id2.name, "Synth Playback Switch");
	अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0)
		वापस err;
	म_नकल(id1.name, "Aux Playback Volume");
	म_नकल(id2.name, "Synth Playback Volume");
	अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0)
		वापस err;
	/* reassign AUXB to CD */
	म_नकल(id1.name, "Aux Playback Switch"); id1.index = 1;
	म_नकल(id2.name, "CD Playback Switch");
	अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0)
		वापस err;
	म_नकल(id1.name, "Aux Playback Volume");
	म_नकल(id2.name, "CD Playback Volume");
	अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0)
		वापस err;
#अगर 0
	/* reassign Mono Input to MIC */
	अगर (snd_mixer_group_नाम(mixer,
				SNDRV_MIXER_IN_MONO, 0,
				SNDRV_MIXER_IN_MIC, 0) < 0)
		जाओ __error;
	अगर (snd_mixer_elem_नाम(mixer,
				SNDRV_MIXER_IN_MONO, 0, SNDRV_MIXER_ETYPE_INPUT,
				SNDRV_MIXER_IN_MIC, 0) < 0)
		जाओ __error;
	अगर (snd_mixer_elem_नाम(mixer,
				"Mono Capture Volume", 0, SNDRV_MIXER_ETYPE_VOLUME1,
				"Mic Capture Volume", 0) < 0)
		जाओ __error;
	अगर (snd_mixer_elem_नाम(mixer,
				"Mono Capture Switch", 0, SNDRV_MIXER_ETYPE_SWITCH1,
				"Mic Capture Switch", 0) < 0)
		जाओ __error;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम snd_gusmax_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_gusmax *maxcard = card->निजी_data;
	
	अगर (maxcard == शून्य)
		वापस;
	अगर (maxcard->irq >= 0)
		मुक्त_irq(maxcard->irq, (व्योम *)maxcard);
पूर्ण

अटल पूर्णांक snd_gusmax_match(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	वापस enable[dev];
पूर्ण

अटल पूर्णांक snd_gusmax_probe(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	अटल स्थिर पूर्णांक possible_irqs[] = अणु5, 11, 12, 9, 7, 15, 3, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dmas[] = अणु5, 6, 7, 1, 3, -1पूर्ण;
	पूर्णांक xirq, xdma1, xdma2, err;
	काष्ठा snd_card *card;
	काष्ठा snd_gus_card *gus = शून्य;
	काष्ठा snd_wss *wss;
	काष्ठा snd_gusmax *maxcard;

	err = snd_card_new(pdev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_gusmax), &card);
	अगर (err < 0)
		वापस err;
	card->निजी_मुक्त = snd_gusmax_मुक्त;
	maxcard = card->निजी_data;
	maxcard->card = card;
	maxcard->irq = -1;
	
	xirq = irq[dev];
	अगर (xirq == SNDRV_AUTO_IRQ) अणु
		अगर ((xirq = snd_legacy_find_मुक्त_irq(possible_irqs)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free IRQ\n");
			err = -EBUSY;
			जाओ _err;
		पूर्ण
	पूर्ण
	xdma1 = dma1[dev];
	अगर (xdma1 == SNDRV_AUTO_DMA) अणु
		अगर ((xdma1 = snd_legacy_find_मुक्त_dma(possible_dmas)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free DMA1\n");
			err = -EBUSY;
			जाओ _err;
		पूर्ण
	पूर्ण
	xdma2 = dma2[dev];
	अगर (xdma2 == SNDRV_AUTO_DMA) अणु
		अगर ((xdma2 = snd_legacy_find_मुक्त_dma(possible_dmas)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free DMA2\n");
			err = -EBUSY;
			जाओ _err;
		पूर्ण
	पूर्ण

	अगर (port[dev] != SNDRV_AUTO_PORT) अणु
		err = snd_gus_create(card,
				     port[dev],
				     -xirq, xdma1, xdma2,
				     0, channels[dev],
				     pcm_channels[dev],
				     0, &gus);
	पूर्ण अन्यथा अणु
		अटल स्थिर अचिन्हित दीर्घ possible_ports[] = अणु
			0x220, 0x230, 0x240, 0x250, 0x260
		पूर्ण;
		पूर्णांक i;
		क्रम (i = 0; i < ARRAY_SIZE(possible_ports); i++) अणु
			err = snd_gus_create(card,
					     possible_ports[i],
					     -xirq, xdma1, xdma2,
					     0, channels[dev],
					     pcm_channels[dev],
					     0, &gus);
			अगर (err >= 0) अणु
				port[dev] = possible_ports[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (err < 0)
		जाओ _err;

	अगर ((err = snd_gusmax_detect(gus)) < 0)
		जाओ _err;

	maxcard->gus_status_reg = gus->gf1.reg_irqstat;
	maxcard->pcm_status_reg = gus->gf1.port + 0x10c + 2;
	snd_gusmax_init(dev, card, gus);
	अगर ((err = snd_gus_initialize(gus)) < 0)
		जाओ _err;

	अगर (!gus->max_flag) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "GUS MAX soundcard was not detected at 0x%lx\n", gus->gf1.port);
		err = -ENODEV;
		जाओ _err;
	पूर्ण

	अगर (request_irq(xirq, snd_gusmax_पूर्णांकerrupt, 0, "GUS MAX", (व्योम *)maxcard)) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "unable to grab IRQ %d\n", xirq);
		err = -EBUSY;
		जाओ _err;
	पूर्ण
	maxcard->irq = xirq;
	card->sync_irq = maxcard->irq;

	err = snd_wss_create(card,
			     gus->gf1.port + 0x10c, -1, xirq,
			     xdma2 < 0 ? xdma1 : xdma2, xdma1,
			     WSS_HW_DETECT,
			     WSS_HWSHARE_IRQ |
			     WSS_HWSHARE_DMA1 |
			     WSS_HWSHARE_DMA2,
			     &wss);
	अगर (err < 0)
		जाओ _err;

	err = snd_wss_pcm(wss, 0);
	अगर (err < 0)
		जाओ _err;

	err = snd_wss_mixer(wss);
	अगर (err < 0)
		जाओ _err;

	err = snd_wss_समयr(wss, 2);
	अगर (err < 0)
		जाओ _err;

	अगर (pcm_channels[dev] > 0) अणु
		अगर ((err = snd_gf1_pcm_new(gus, 1, 1)) < 0)
			जाओ _err;
	पूर्ण
	err = snd_gusmax_mixer(wss);
	अगर (err < 0)
		जाओ _err;

	err = snd_gf1_rawmidi_new(gus, 0);
	अगर (err < 0)
		जाओ _err;

	प्र_लिखो(card->दीर्घname + म_माप(card->दीर्घname), " at 0x%lx, irq %i, dma %i", gus->gf1.port, xirq, xdma1);
	अगर (xdma2 >= 0)
		प्र_लिखो(card->दीर्घname + म_माप(card->दीर्घname), "&%i", xdma2);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ _err;
		
	maxcard->gus = gus;
	maxcard->wss = wss;

	dev_set_drvdata(pdev, card);
	वापस 0;

 _err:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_gusmax_हटाओ(काष्ठा device *devptr, अचिन्हित पूर्णांक dev)
अणु
	snd_card_मुक्त(dev_get_drvdata(devptr));
पूर्ण

#घोषणा DEV_NAME "gusmax"

अटल काष्ठा isa_driver snd_gusmax_driver = अणु
	.match		= snd_gusmax_match,
	.probe		= snd_gusmax_probe,
	.हटाओ		= snd_gusmax_हटाओ,
	/* FIXME: suspend/resume */
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण,
पूर्ण;

module_isa_driver(snd_gusmax_driver, SNDRV_CARDS);
