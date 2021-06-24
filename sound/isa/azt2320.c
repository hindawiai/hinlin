<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    card-azt2320.c - driver क्रम Aztech Systems AZT2320 based soundcards.
    Copyright (C) 1999-2000 by Massimo Piccioni <dafastidio@libero.it>

*/

/*
    This driver should provide support क्रम most Aztech AZT2320 based cards.
    Several AZT2316 chips are also supported/tested, but स्वतःprobe करोesn't
    work: all module option have to be set.

    No करोcs available क्रम us at Aztech headquarters !!!   Unbelievable ...
    No other help obtained.

    Thanks to Rainer Wiesner <rainer.wiesner@01019मुक्तnet.de> क्रम the WSS
    activation method (full-duplex audio!).
*/

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/pnp.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/wss.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>

#घोषणा PFX "azt2320: "

MODULE_AUTHOR("Massimo Piccioni <dafastidio@libero.it>");
MODULE_DESCRIPTION("Aztech Systems AZT2320");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_ISAPNP; /* Enable this card */
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल दीर्घ wss_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल दीर्घ mpu_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल दीर्घ fm_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* Pnp setup */
अटल पूर्णांक mpu_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* Pnp setup */
अटल पूर्णांक dma1[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* PnP setup */
अटल पूर्णांक dma2[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* PnP setup */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for azt2320 based soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for azt2320 based soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable azt2320 based soundcard.");

काष्ठा snd_card_azt2320 अणु
	पूर्णांक dev_no;
	काष्ठा pnp_dev *dev;
	काष्ठा pnp_dev *devmpu;
	काष्ठा snd_wss *chip;
पूर्ण;

अटल स्थिर काष्ठा pnp_card_device_id snd_azt2320_pnpids[] = अणु
	/* PRO16V */
	अणु .id = "AZT1008", .devs = अणु अणु "AZT1008" पूर्ण, अणु "AZT2001" पूर्ण, पूर्ण पूर्ण,
	/* Aztech Sound Galaxy 16 */
	अणु .id = "AZT2320", .devs = अणु अणु "AZT0001" पूर्ण, अणु "AZT0002" पूर्ण, पूर्ण पूर्ण,
	/* Packard Bell Sound III 336 AM/SP */
	अणु .id = "AZT3000", .devs = अणु अणु "AZT1003" पूर्ण, अणु "AZT2001" पूर्ण, पूर्ण पूर्ण,
	/* AT3300 */
	अणु .id = "AZT3002", .devs = अणु अणु "AZT1004" पूर्ण, अणु "AZT2001" पूर्ण, पूर्ण पूर्ण,
	/* --- */
	अणु .id = "AZT3005", .devs = अणु अणु "AZT1003" पूर्ण, अणु "AZT2001" पूर्ण, पूर्ण पूर्ण,
	/* --- */
	अणु .id = "AZT3011", .devs = अणु अणु "AZT1003" पूर्ण, अणु "AZT2001" पूर्ण, पूर्ण पूर्ण,
	अणु .id = "" पूर्ण	/* end */
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_azt2320_pnpids);

#घोषणा	DRIVER_NAME	"snd-card-azt2320"

अटल पूर्णांक snd_card_azt2320_pnp(पूर्णांक dev, काष्ठा snd_card_azt2320 *acard,
				काष्ठा pnp_card_link *card,
				स्थिर काष्ठा pnp_card_device_id *id)
अणु
	काष्ठा pnp_dev *pdev;
	पूर्णांक err;

	acard->dev = pnp_request_card_device(card, id->devs[0].id, शून्य);
	अगर (acard->dev == शून्य)
		वापस -ENODEV;

	acard->devmpu = pnp_request_card_device(card, id->devs[1].id, शून्य);

	pdev = acard->dev;

	err = pnp_activate_dev(pdev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "AUDIO pnp configure failure\n");
		वापस err;
	पूर्ण
	port[dev] = pnp_port_start(pdev, 0);
	fm_port[dev] = pnp_port_start(pdev, 1);
	wss_port[dev] = pnp_port_start(pdev, 2);
	dma1[dev] = pnp_dma(pdev, 0);
	dma2[dev] = pnp_dma(pdev, 1);
	irq[dev] = pnp_irq(pdev, 0);

	pdev = acard->devmpu;
	अगर (pdev != शून्य) अणु
		err = pnp_activate_dev(pdev);
		अगर (err < 0)
			जाओ __mpu_error;
		mpu_port[dev] = pnp_port_start(pdev, 0);
		mpu_irq[dev] = pnp_irq(pdev, 0);
	पूर्ण अन्यथा अणु
	     __mpu_error:
	     	अगर (pdev) अणु
		     	pnp_release_card_device(pdev);
	     		snd_prपूर्णांकk(KERN_ERR PFX "MPU401 pnp configure failure, skipping\n");
	     	पूर्ण
	     	acard->devmpu = शून्य;
	     	mpu_port[dev] = -1;
	पूर्ण

	वापस 0;
पूर्ण

/* same of snd_sbdsp_command by Jaroslav Kysela */
अटल पूर्णांक snd_card_azt2320_command(अचिन्हित दीर्घ port, अचिन्हित अक्षर val)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ limit;

	limit = jअगरfies + HZ / 10;
	क्रम (i = 50000; i && समय_after(limit, jअगरfies); i--)
		अगर (!(inb(port + 0x0c) & 0x80)) अणु
			outb(val, port + 0x0c);
			वापस 0;
		पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक snd_card_azt2320_enable_wss(अचिन्हित दीर्घ port)
अणु
	पूर्णांक error;

	अगर ((error = snd_card_azt2320_command(port, 0x09)))
		वापस error;
	अगर ((error = snd_card_azt2320_command(port, 0x00)))
		वापस error;

	mdelay(5);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_card_azt2320_probe(पूर्णांक dev,
				  काष्ठा pnp_card_link *pcard,
				  स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	पूर्णांक error;
	काष्ठा snd_card *card;
	काष्ठा snd_card_azt2320 *acard;
	काष्ठा snd_wss *chip;
	काष्ठा snd_opl3 *opl3;

	error = snd_card_new(&pcard->card->dev,
			     index[dev], id[dev], THIS_MODULE,
			     माप(काष्ठा snd_card_azt2320), &card);
	अगर (error < 0)
		वापस error;
	acard = card->निजी_data;

	अगर ((error = snd_card_azt2320_pnp(dev, acard, pcard, pid))) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण

	अगर ((error = snd_card_azt2320_enable_wss(port[dev]))) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण

	error = snd_wss_create(card, wss_port[dev], -1,
			       irq[dev],
			       dma1[dev], dma2[dev],
			       WSS_HW_DETECT, 0, &chip);
	अगर (error < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण

	म_नकल(card->driver, "AZT2320");
	म_नकल(card->लघुname, "Aztech AZT2320");
	प्र_लिखो(card->दीर्घname, "%s, WSS at 0x%lx, irq %i, dma %i&%i",
		card->लघुname, chip->port, irq[dev], dma1[dev], dma2[dev]);

	error = snd_wss_pcm(chip, 0);
	अगर (error < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण
	error = snd_wss_mixer(chip);
	अगर (error < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण
	error = snd_wss_समयr(chip, 0);
	अगर (error < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण

	अगर (mpu_port[dev] > 0 && mpu_port[dev] != SNDRV_AUTO_PORT) अणु
		अगर (snd_mpu401_uart_new(card, 0, MPU401_HW_AZT2320,
				mpu_port[dev], 0,
				mpu_irq[dev], शून्य) < 0)
			snd_prपूर्णांकk(KERN_ERR PFX "no MPU-401 device at 0x%lx\n", mpu_port[dev]);
	पूर्ण

	अगर (fm_port[dev] > 0 && fm_port[dev] != SNDRV_AUTO_PORT) अणु
		अगर (snd_opl3_create(card,
				    fm_port[dev], fm_port[dev] + 2,
				    OPL3_HW_AUTO, 0, &opl3) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "no OPL device at 0x%lx-0x%lx\n",
				   fm_port[dev], fm_port[dev] + 2);
		पूर्ण अन्यथा अणु
			अगर ((error = snd_opl3_समयr_new(opl3, 1, 2)) < 0) अणु
				snd_card_मुक्त(card);
				वापस error;
			पूर्ण
			अगर ((error = snd_opl3_hwdep_new(opl3, 0, 1, शून्य)) < 0) अणु
				snd_card_मुक्त(card);
				वापस error;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((error = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण
	pnp_set_card_drvdata(pcard, card);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक azt2320_devices;

अटल पूर्णांक snd_azt2320_pnp_detect(काष्ठा pnp_card_link *card,
				  स्थिर काष्ठा pnp_card_device_id *id)
अणु
	अटल पूर्णांक dev;
	पूर्णांक res;

	क्रम ( ; dev < SNDRV_CARDS; dev++) अणु
		अगर (!enable[dev])
			जारी;
		res = snd_card_azt2320_probe(dev, card, id);
		अगर (res < 0)
			वापस res;
		dev++;
		azt2320_devices++;
		वापस 0;
	पूर्ण
        वापस -ENODEV;
पूर्ण

अटल व्योम snd_azt2320_pnp_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_azt2320_pnp_suspend(काष्ठा pnp_card_link *pcard, pm_message_t state)
अणु
	काष्ठा snd_card *card = pnp_get_card_drvdata(pcard);
	काष्ठा snd_card_azt2320 *acard = card->निजी_data;
	काष्ठा snd_wss *chip = acard->chip;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	chip->suspend(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_azt2320_pnp_resume(काष्ठा pnp_card_link *pcard)
अणु
	काष्ठा snd_card *card = pnp_get_card_drvdata(pcard);
	काष्ठा snd_card_azt2320 *acard = card->निजी_data;
	काष्ठा snd_wss *chip = acard->chip;

	chip->resume(chip);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pnp_card_driver azt2320_pnpc_driver = अणु
	.flags          = PNP_DRIVER_RES_DISABLE,
	.name           = "azt2320",
	.id_table       = snd_azt2320_pnpids,
	.probe          = snd_azt2320_pnp_detect,
	.हटाओ         = snd_azt2320_pnp_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_azt2320_pnp_suspend,
	.resume		= snd_azt2320_pnp_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init alsa_card_azt2320_init(व्योम)
अणु
	पूर्णांक err;

	err = pnp_रेजिस्टर_card_driver(&azt2320_pnpc_driver);
	अगर (err)
		वापस err;

	अगर (!azt2320_devices) अणु
		pnp_unरेजिस्टर_card_driver(&azt2320_pnpc_driver);
#अगर_घोषित MODULE
		snd_prपूर्णांकk(KERN_ERR "no AZT2320 based soundcards found\n");
#पूर्ण_अगर
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_card_azt2320_निकास(व्योम)
अणु
	pnp_unरेजिस्टर_card_driver(&azt2320_pnpc_driver);
पूर्ण

module_init(alsa_card_azt2320_init)
module_निकास(alsa_card_azt2320_निकास)
