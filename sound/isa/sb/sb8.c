<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम SoundBlaster 1.0/2.0/Pro soundcards and compatible
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/sb.h>
#समावेश <sound/opl3.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Sound Blaster 1.0/2.0/Pro");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;	/* Enable this card */
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x220,0x240,0x260 */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 5,7,9,10 */
अटल पूर्णांक dma8[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 1,3 */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Sound Blaster soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Sound Blaster soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Sound Blaster soundcard.");
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for SB8 driver.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for SB8 driver.");
module_param_hw_array(dma8, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma8, "8-bit DMA # for SB8 driver.");

काष्ठा snd_sb8 अणु
	काष्ठा resource *fm_res;	/* used to block FM i/o region क्रम legacy cards */
	काष्ठा snd_sb *chip;
पूर्ण;

अटल irqवापस_t snd_sb8_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_sb *chip = dev_id;

	अगर (chip->खोलो & SB_OPEN_PCM) अणु
		वापस snd_sb8dsp_पूर्णांकerrupt(chip);
	पूर्ण अन्यथा अणु
		वापस snd_sb8dsp_midi_पूर्णांकerrupt(chip);
	पूर्ण
पूर्ण

अटल व्योम snd_sb8_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_sb8 *acard = card->निजी_data;

	अगर (acard == शून्य)
		वापस;
	release_and_मुक्त_resource(acard->fm_res);
पूर्ण

अटल पूर्णांक snd_sb8_match(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	अगर (!enable[dev])
		वापस 0;
	अगर (irq[dev] == SNDRV_AUTO_IRQ) अणु
		dev_err(pdev, "please specify irq\n");
		वापस 0;
	पूर्ण
	अगर (dma8[dev] == SNDRV_AUTO_DMA) अणु
		dev_err(pdev, "please specify dma8\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक snd_sb8_probe(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	काष्ठा snd_sb *chip;
	काष्ठा snd_card *card;
	काष्ठा snd_sb8 *acard;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक err;

	err = snd_card_new(pdev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_sb8), &card);
	अगर (err < 0)
		वापस err;
	acard = card->निजी_data;
	card->निजी_मुक्त = snd_sb8_मुक्त;

	/*
	 * Block the 0x388 port to aव्योम PnP conflicts.
	 * No need to check this value after request_region,
	 * as we never करो anything with it.
	 */
	acard->fm_res = request_region(0x388, 4, "SoundBlaster FM");

	अगर (port[dev] != SNDRV_AUTO_PORT) अणु
		अगर ((err = snd_sbdsp_create(card, port[dev], irq[dev],
					    snd_sb8_पूर्णांकerrupt,
					    dma8[dev],
					    -1,
					    SB_HW_AUTO,
					    &chip)) < 0)
			जाओ _err;
	पूर्ण अन्यथा अणु
		/* स्वतः-probe legacy ports */
		अटल स्थिर अचिन्हित दीर्घ possible_ports[] = अणु
			0x220, 0x240, 0x260,
		पूर्ण;
		पूर्णांक i;
		क्रम (i = 0; i < ARRAY_SIZE(possible_ports); i++) अणु
			err = snd_sbdsp_create(card, possible_ports[i],
					       irq[dev],
					       snd_sb8_पूर्णांकerrupt,
					       dma8[dev],
					       -1,
					       SB_HW_AUTO,
					       &chip);
			अगर (err >= 0) अणु
				port[dev] = possible_ports[i];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i >= ARRAY_SIZE(possible_ports)) अणु
			err = -EINVAL;
			जाओ _err;
		पूर्ण
	पूर्ण
	acard->chip = chip;
			
	अगर (chip->hardware >= SB_HW_16) अणु
		अगर (chip->hardware == SB_HW_ALS100)
			snd_prपूर्णांकk(KERN_WARNING "ALS100 chip detected at 0x%lx, try snd-als100 module\n",
				    port[dev]);
		अन्यथा
			snd_prपूर्णांकk(KERN_WARNING "SB 16 chip detected at 0x%lx, try snd-sb16 module\n",
				   port[dev]);
		err = -ENODEV;
		जाओ _err;
	पूर्ण

	अगर ((err = snd_sb8dsp_pcm(chip, 0)) < 0)
		जाओ _err;

	अगर ((err = snd_sbmixer_new(chip)) < 0)
		जाओ _err;

	अगर (chip->hardware == SB_HW_10 || chip->hardware == SB_HW_20) अणु
		अगर ((err = snd_opl3_create(card, chip->port + 8, 0,
					   OPL3_HW_AUTO, 1,
					   &opl3)) < 0) अणु
			snd_prपूर्णांकk(KERN_WARNING "sb8: no OPL device at 0x%lx\n", chip->port + 8);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((err = snd_opl3_create(card, chip->port, chip->port + 2,
					   OPL3_HW_AUTO, 1,
					   &opl3)) < 0) अणु
			snd_prपूर्णांकk(KERN_WARNING "sb8: no OPL device at 0x%lx-0x%lx\n",
				   chip->port, chip->port + 2);
		पूर्ण
	पूर्ण
	अगर (err >= 0) अणु
		अगर ((err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य)) < 0)
			जाओ _err;
	पूर्ण

	अगर ((err = snd_sb8dsp_midi(chip, 0)) < 0)
		जाओ _err;

	म_नकल(card->driver, chip->hardware == SB_HW_PRO ? "SB Pro" : "SB8");
	म_नकल(card->लघुname, chip->name);
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d, dma %d",
		chip->name,
		chip->port,
		irq[dev], dma8[dev]);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0)
		जाओ _err;

	dev_set_drvdata(pdev, card);
	वापस 0;

 _err:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_sb8_हटाओ(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	snd_card_मुक्त(dev_get_drvdata(pdev));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_sb8_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक n,
			   pm_message_t state)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_sb8 *acard = card->निजी_data;
	काष्ठा snd_sb *chip = acard->chip;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_sbmixer_suspend(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb8_resume(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_sb8 *acard = card->निजी_data;
	काष्ठा snd_sb *chip = acard->chip;

	snd_sbdsp_reset(chip);
	snd_sbmixer_resume(chip);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा DEV_NAME "sb8"

अटल काष्ठा isa_driver snd_sb8_driver = अणु
	.match		= snd_sb8_match,
	.probe		= snd_sb8_probe,
	.हटाओ		= snd_sb8_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_sb8_suspend,
	.resume		= snd_sb8_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DEV_NAME 
	पूर्ण,
पूर्ण;

module_isa_driver(snd_sb8_driver, SNDRV_CARDS);
