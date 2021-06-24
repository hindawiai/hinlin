<शैली गुरु>

/*
 * jazz16.c - driver क्रम Media Vision Jazz16 based soundcards.
 * Copyright (C) 2009 Krzysztof Helt <krzysztof.h1@wp.pl>
 * Based on patches posted by Rask Ingemann Lambertsen and Rene Herman.
 * Based on OSS Sound Blaster driver.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <यंत्र/dma.h>
#समावेश <linux/isa.h>
#समावेश <sound/core.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#समावेश <sound/sb.h>
#घोषणा SNDRV_LEGACY_FIND_FREE_IRQ
#घोषणा SNDRV_LEGACY_FIND_FREE_DMA
#समावेश <sound/initval.h>

#घोषणा PFX "jazz16: "

MODULE_DESCRIPTION("Media Vision Jazz16");
MODULE_AUTHOR("Krzysztof Helt <krzysztof.h1@wp.pl>");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;	/* Enable this card */
अटल अचिन्हित दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल अचिन्हित दीर्घ mpu_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;
अटल पूर्णांक mpu_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;
अटल पूर्णांक dma8[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;
अटल पूर्णांक dma16[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Media Vision Jazz16 based soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Media Vision Jazz16 based soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Media Vision Jazz16 based soundcard.");
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for jazz16 driver.");
module_param_hw_array(mpu_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 port # for jazz16 driver.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for jazz16 driver.");
module_param_hw_array(mpu_irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(mpu_irq, "MPU-401 IRQ # for jazz16 driver.");
module_param_hw_array(dma8, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma8, "DMA8 # for jazz16 driver.");
module_param_hw_array(dma16, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma16, "DMA16 # for jazz16 driver.");

#घोषणा SB_JAZZ16_WAKEUP	0xaf
#घोषणा SB_JAZZ16_SET_PORTS	0x50
#घोषणा SB_DSP_GET_JAZZ_BRD_REV	0xfa
#घोषणा SB_JAZZ16_SET_DMAINTR	0xfb
#घोषणा SB_DSP_GET_JAZZ_MODEL	0xfe

काष्ठा snd_card_jazz16 अणु
	काष्ठा snd_sb *chip;
पूर्ण;

अटल irqवापस_t jazz16_पूर्णांकerrupt(पूर्णांक irq, व्योम *chip)
अणु
	वापस snd_sb8dsp_पूर्णांकerrupt(chip);
पूर्ण

अटल पूर्णांक jazz16_configure_ports(अचिन्हित दीर्घ port,
				  अचिन्हित दीर्घ mpu_port, पूर्णांक idx)
अणु
	अचिन्हित अक्षर val;

	अगर (!request_region(0x201, 1, "jazz16 config")) अणु
		snd_prपूर्णांकk(KERN_ERR "config port region is already in use.\n");
		वापस -EBUSY;
	पूर्ण
	outb(SB_JAZZ16_WAKEUP - idx, 0x201);
	udelay(100);
	outb(SB_JAZZ16_SET_PORTS + idx, 0x201);
	udelay(100);
	val = port & 0x70;
	val |= (mpu_port & 0x30) >> 4;
	outb(val, 0x201);

	release_region(0x201, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक jazz16_detect_board(अचिन्हित दीर्घ port,
			       अचिन्हित दीर्घ mpu_port)
अणु
	पूर्णांक err;
	पूर्णांक val;
	काष्ठा snd_sb chip;

	अगर (!request_region(port, 0x10, "jazz16")) अणु
		snd_prपूर्णांकk(KERN_ERR "I/O port region is already in use.\n");
		वापस -EBUSY;
	पूर्ण
	/* just to call snd_sbdsp_command/reset/get_byte() */
	chip.port = port;

	err = snd_sbdsp_reset(&chip);
	अगर (err < 0)
		क्रम (val = 0; val < 4; val++) अणु
			err = jazz16_configure_ports(port, mpu_port, val);
			अगर (err < 0)
				अवरोध;

			err = snd_sbdsp_reset(&chip);
			अगर (!err)
				अवरोध;
		पूर्ण
	अगर (err < 0) अणु
		err = -ENODEV;
		जाओ err_unmap;
	पूर्ण
	अगर (!snd_sbdsp_command(&chip, SB_DSP_GET_JAZZ_BRD_REV)) अणु
		err = -EBUSY;
		जाओ err_unmap;
	पूर्ण
	val = snd_sbdsp_get_byte(&chip);
	अगर (val >= 0x30)
		snd_sbdsp_get_byte(&chip);

	अगर ((val & 0xf0) != 0x10) अणु
		err = -ENODEV;
		जाओ err_unmap;
	पूर्ण
	अगर (!snd_sbdsp_command(&chip, SB_DSP_GET_JAZZ_MODEL)) अणु
		err = -EBUSY;
		जाओ err_unmap;
	पूर्ण
	snd_sbdsp_get_byte(&chip);
	err = snd_sbdsp_get_byte(&chip);
	snd_prपूर्णांकd("Media Vision Jazz16 board detected: rev 0x%x, model 0x%x\n",
		   val, err);

	err = 0;

err_unmap:
	release_region(port, 0x10);
	वापस err;
पूर्ण

अटल पूर्णांक jazz16_configure_board(काष्ठा snd_sb *chip, पूर्णांक mpu_irq)
अणु
	अटल स्थिर अचिन्हित अक्षर jazz_irq_bits[] = अणु 0, 0, 2, 3, 0, 1, 0, 4,
						 0, 2, 5, 0, 0, 0, 0, 6 पूर्ण;
	अटल स्थिर अचिन्हित अक्षर jazz_dma_bits[] = अणु 0, 1, 0, 2, 0, 3, 0, 4 पूर्ण;

	अगर (jazz_dma_bits[chip->dma8] == 0 ||
	    jazz_dma_bits[chip->dma16] == 0 ||
	    jazz_irq_bits[chip->irq] == 0)
		वापस -EINVAL;

	अगर (!snd_sbdsp_command(chip, SB_JAZZ16_SET_DMAINTR))
		वापस -EBUSY;

	अगर (!snd_sbdsp_command(chip,
			       jazz_dma_bits[chip->dma8] |
			       (jazz_dma_bits[chip->dma16] << 4)))
		वापस -EBUSY;

	अगर (!snd_sbdsp_command(chip,
			       jazz_irq_bits[chip->irq] |
			       (jazz_irq_bits[mpu_irq] << 4)))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_jazz16_match(काष्ठा device *devptr, अचिन्हित पूर्णांक dev)
अणु
	अगर (!enable[dev])
		वापस 0;
	अगर (port[dev] == SNDRV_AUTO_PORT) अणु
		snd_prपूर्णांकk(KERN_ERR "please specify port\n");
		वापस 0;
	पूर्ण अन्यथा अगर (port[dev] == 0x200 || (port[dev] & ~0x270)) अणु
		snd_prपूर्णांकk(KERN_ERR "incorrect port specified\n");
		वापस 0;
	पूर्ण
	अगर (dma8[dev] != SNDRV_AUTO_DMA &&
	    dma8[dev] != 1 && dma8[dev] != 3) अणु
		snd_prपूर्णांकk(KERN_ERR "dma8 must be 1 or 3\n");
		वापस 0;
	पूर्ण
	अगर (dma16[dev] != SNDRV_AUTO_DMA &&
	    dma16[dev] != 5 && dma16[dev] != 7) अणु
		snd_prपूर्णांकk(KERN_ERR "dma16 must be 5 or 7\n");
		वापस 0;
	पूर्ण
	अगर (mpu_port[dev] != SNDRV_AUTO_PORT &&
	    (mpu_port[dev] & ~0x030) != 0x300) अणु
		snd_prपूर्णांकk(KERN_ERR "incorrect mpu_port specified\n");
		वापस 0;
	पूर्ण
	अगर (mpu_irq[dev] != SNDRV_AUTO_DMA &&
	    mpu_irq[dev] != 2 && mpu_irq[dev] != 3 &&
	    mpu_irq[dev] != 5 && mpu_irq[dev] != 7) अणु
		snd_prपूर्णांकk(KERN_ERR "mpu_irq must be 2, 3, 5 or 7\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक snd_jazz16_probe(काष्ठा device *devptr, अचिन्हित पूर्णांक dev)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_card_jazz16 *jazz16;
	काष्ठा snd_sb *chip;
	काष्ठा snd_opl3 *opl3;
	अटल स्थिर पूर्णांक possible_irqs[] = अणु2, 3, 5, 7, 9, 10, 15, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dmas8[] = अणु1, 3, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dmas16[] = अणु5, 7, -1पूर्ण;
	पूर्णांक err, xirq, xdma8, xdma16, xmpu_port, xmpu_irq;

	err = snd_card_new(devptr, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_card_jazz16), &card);
	अगर (err < 0)
		वापस err;

	jazz16 = card->निजी_data;

	xirq = irq[dev];
	अगर (xirq == SNDRV_AUTO_IRQ) अणु
		xirq = snd_legacy_find_मुक्त_irq(possible_irqs);
		अगर (xirq < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "unable to find a free IRQ\n");
			err = -EBUSY;
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण
	xdma8 = dma8[dev];
	अगर (xdma8 == SNDRV_AUTO_DMA) अणु
		xdma8 = snd_legacy_find_मुक्त_dma(possible_dmas8);
		अगर (xdma8 < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "unable to find a free DMA8\n");
			err = -EBUSY;
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण
	xdma16 = dma16[dev];
	अगर (xdma16 == SNDRV_AUTO_DMA) अणु
		xdma16 = snd_legacy_find_मुक्त_dma(possible_dmas16);
		अगर (xdma16 < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "unable to find a free DMA16\n");
			err = -EBUSY;
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण

	xmpu_port = mpu_port[dev];
	अगर (xmpu_port == SNDRV_AUTO_PORT)
		xmpu_port = 0;
	err = jazz16_detect_board(port[dev], xmpu_port);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "Media Vision Jazz16 board not detected\n");
		जाओ err_मुक्त;
	पूर्ण
	err = snd_sbdsp_create(card, port[dev], irq[dev],
			       jazz16_पूर्णांकerrupt,
			       dma8[dev], dma16[dev],
			       SB_HW_JAZZ16,
			       &chip);
	अगर (err < 0)
		जाओ err_मुक्त;

	xmpu_irq = mpu_irq[dev];
	अगर (xmpu_irq == SNDRV_AUTO_IRQ || mpu_port[dev] == SNDRV_AUTO_PORT)
		xmpu_irq = 0;
	err = jazz16_configure_board(chip, xmpu_irq);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "Media Vision Jazz16 configuration failed\n");
		जाओ err_मुक्त;
	पूर्ण

	jazz16->chip = chip;

	म_नकल(card->driver, "jazz16");
	म_नकल(card->लघुname, "Media Vision Jazz16");
	प्र_लिखो(card->दीर्घname,
		"Media Vision Jazz16 at 0x%lx, irq %d, dma8 %d, dma16 %d",
		port[dev], xirq, xdma8, xdma16);

	err = snd_sb8dsp_pcm(chip, 0);
	अगर (err < 0)
		जाओ err_मुक्त;
	err = snd_sbmixer_new(chip);
	अगर (err < 0)
		जाओ err_मुक्त;

	err = snd_opl3_create(card, chip->port, chip->port + 2,
			      OPL3_HW_AUTO, 1, &opl3);
	अगर (err < 0)
		snd_prपूर्णांकk(KERN_WARNING "no OPL device at 0x%lx-0x%lx\n",
			   chip->port, chip->port + 2);
	अन्यथा अणु
		err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य);
		अगर (err < 0)
			जाओ err_मुक्त;
	पूर्ण
	अगर (mpu_port[dev] > 0 && mpu_port[dev] != SNDRV_AUTO_PORT) अणु
		अगर (mpu_irq[dev] == SNDRV_AUTO_IRQ)
			mpu_irq[dev] = -1;

		अगर (snd_mpu401_uart_new(card, 0,
					MPU401_HW_MPU401,
					mpu_port[dev], 0,
					mpu_irq[dev],
					शून्य) < 0)
			snd_prपूर्णांकk(KERN_ERR "no MPU-401 device at 0x%lx\n",
					mpu_port[dev]);
	पूर्ण

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ err_मुक्त;

	dev_set_drvdata(devptr, card);
	वापस 0;

err_मुक्त:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_jazz16_हटाओ(काष्ठा device *devptr, अचिन्हित पूर्णांक dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(devptr);

	snd_card_मुक्त(card);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_jazz16_suspend(काष्ठा device *pdev, अचिन्हित पूर्णांक n,
			       pm_message_t state)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(pdev);
	काष्ठा snd_card_jazz16 *acard = card->निजी_data;
	काष्ठा snd_sb *chip = acard->chip;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_sbmixer_suspend(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_jazz16_resume(काष्ठा device *pdev, अचिन्हित पूर्णांक n)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(pdev);
	काष्ठा snd_card_jazz16 *acard = card->निजी_data;
	काष्ठा snd_sb *chip = acard->chip;

	snd_sbdsp_reset(chip);
	snd_sbmixer_resume(chip);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा isa_driver snd_jazz16_driver = अणु
	.match		= snd_jazz16_match,
	.probe		= snd_jazz16_probe,
	.हटाओ		= snd_jazz16_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_jazz16_suspend,
	.resume		= snd_jazz16_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= "jazz16"
	पूर्ण,
पूर्ण;

module_isa_driver(snd_jazz16_driver, SNDRV_CARDS);
