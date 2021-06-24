<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
    card-ad1816a.c - driver क्रम ADI SoundPort AD1816A based soundcards.
    Copyright (C) 2000 by Massimo Piccioni <dafastidio@libero.it>

*/

#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/pnp.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/ad1816a.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>

#घोषणा PFX "ad1816a: "

MODULE_AUTHOR("Massimo Piccioni <dafastidio@libero.it>");
MODULE_DESCRIPTION("AD1816A, AD1815");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 1-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_ISAPNP;	/* Enable this card */
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल दीर्घ mpu_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल दीर्घ fm_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* Pnp setup */
अटल पूर्णांक mpu_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* Pnp setup */
अटल पूर्णांक dma1[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* PnP setup */
अटल पूर्णांक dma2[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* PnP setup */
अटल पूर्णांक घड़ीfreq[SNDRV_CARDS];

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for ad1816a based soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for ad1816a based soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable ad1816a based soundcard.");
module_param_array(घड़ीfreq, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(घड़ीfreq, "Clock frequency for ad1816a driver (default = 0).");

अटल स्थिर काष्ठा pnp_card_device_id snd_ad1816a_pnpids[] = अणु
	/* Analog Devices AD1815 */
	अणु .id = "ADS7150", .devs = अणु अणु .id = "ADS7150" पूर्ण, अणु .id = "ADS7151" पूर्ण पूर्ण पूर्ण,
	/* Analog Devices AD1816? */
	अणु .id = "ADS7180", .devs = अणु अणु .id = "ADS7180" पूर्ण, अणु .id = "ADS7181" पूर्ण पूर्ण पूर्ण,
	/* Analog Devices AD1816A - added by Kenneth Platz <kxp@atl.hp.com> */
	अणु .id = "ADS7181", .devs = अणु अणु .id = "ADS7180" पूर्ण, अणु .id = "ADS7181" पूर्ण पूर्ण पूर्ण,
	/* Analog Devices AD1816A - Aztech/Newcom SC-16 3D */
	अणु .id = "AZT1022", .devs = अणु अणु .id = "AZT1018" पूर्ण, अणु .id = "AZT2002" पूर्ण पूर्ण पूर्ण,
	/* Highscreen Sound-Boostar 16 3D - added by Stefan Behnel */
	अणु .id = "LWC1061", .devs = अणु अणु .id = "ADS7180" पूर्ण, अणु .id = "ADS7181" पूर्ण पूर्ण पूर्ण,
	/* Highscreen Sound-Boostar 16 3D */
	अणु .id = "MDK1605", .devs = अणु अणु .id = "ADS7180" पूर्ण, अणु .id = "ADS7181" पूर्ण पूर्ण पूर्ण,
	/* Shark Predator ISA - added by Ken Arromdee */
	अणु .id = "SMM7180", .devs = अणु अणु .id = "ADS7180" पूर्ण, अणु .id = "ADS7181" पूर्ण पूर्ण पूर्ण,
	/* Analog Devices AD1816A - Terratec AudioSystem EWS64 S */
	अणु .id = "TER1112", .devs = अणु अणु .id = "ADS7180" पूर्ण, अणु .id = "ADS7181" पूर्ण पूर्ण पूर्ण,
	/* Analog Devices AD1816A - Terratec AudioSystem EWS64 S */
	अणु .id = "TER1112", .devs = अणु अणु .id = "TER1100" पूर्ण, अणु .id = "TER1101" पूर्ण पूर्ण पूर्ण,
	/* Analog Devices AD1816A - Terratec Base 64 */
	अणु .id = "TER1411", .devs = अणु अणु .id = "ADS7180" पूर्ण, अणु .id = "ADS7181" पूर्ण पूर्ण पूर्ण,
	/* end */
	अणु .id = "" पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_ad1816a_pnpids);


#घोषणा	DRIVER_NAME	"snd-card-ad1816a"


अटल पूर्णांक snd_card_ad1816a_pnp(पूर्णांक dev, काष्ठा pnp_card_link *card,
				स्थिर काष्ठा pnp_card_device_id *id)
अणु
	काष्ठा pnp_dev *pdev;
	पूर्णांक err;

	pdev = pnp_request_card_device(card, id->devs[0].id, शून्य);
	अगर (pdev == शून्य)
		वापस -EBUSY;

	err = pnp_activate_dev(pdev);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "AUDIO PnP configure failure\n");
		वापस -EBUSY;
	पूर्ण

	port[dev] = pnp_port_start(pdev, 2);
	fm_port[dev] = pnp_port_start(pdev, 1);
	dma1[dev] = pnp_dma(pdev, 0);
	dma2[dev] = pnp_dma(pdev, 1);
	irq[dev] = pnp_irq(pdev, 0);

	pdev = pnp_request_card_device(card, id->devs[1].id, शून्य);
	अगर (pdev == शून्य) अणु
		mpu_port[dev] = -1;
		snd_prपूर्णांकk(KERN_WARNING PFX "MPU401 device busy, skipping.\n");
		वापस 0;
	पूर्ण

	err = pnp_activate_dev(pdev);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "MPU401 PnP configure failure\n");
		mpu_port[dev] = -1;
	पूर्ण अन्यथा अणु
		mpu_port[dev] = pnp_port_start(pdev, 0);
		mpu_irq[dev] = pnp_irq(pdev, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_card_ad1816a_probe(पूर्णांक dev, काष्ठा pnp_card_link *pcard,
				  स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	पूर्णांक error;
	काष्ठा snd_card *card;
	काष्ठा snd_ad1816a *chip;
	काष्ठा snd_opl3 *opl3;

	error = snd_card_new(&pcard->card->dev,
			     index[dev], id[dev], THIS_MODULE,
			     माप(काष्ठा snd_ad1816a), &card);
	अगर (error < 0)
		वापस error;
	chip = card->निजी_data;

	अगर ((error = snd_card_ad1816a_pnp(dev, pcard, pid))) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण

	अगर ((error = snd_ad1816a_create(card, port[dev],
					irq[dev],
					dma1[dev],
					dma2[dev],
					chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण
	अगर (घड़ीfreq[dev] >= 5000 && घड़ीfreq[dev] <= 100000)
		chip->घड़ी_freq = घड़ीfreq[dev];

	म_नकल(card->driver, "AD1816A");
	म_नकल(card->लघुname, "ADI SoundPort AD1816A");
	प्र_लिखो(card->दीर्घname, "%s, SS at 0x%lx, irq %d, dma %d&%d",
		card->लघुname, chip->port, irq[dev], dma1[dev], dma2[dev]);

	अगर ((error = snd_ad1816a_pcm(chip, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण

	अगर ((error = snd_ad1816a_mixer(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण

	error = snd_ad1816a_समयr(chip, 0);
	अगर (error < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण

	अगर (mpu_port[dev] > 0) अणु
		अगर (snd_mpu401_uart_new(card, 0, MPU401_HW_MPU401,
					mpu_port[dev], 0, mpu_irq[dev],
					शून्य) < 0)
			prपूर्णांकk(KERN_ERR PFX "no MPU-401 device at 0x%lx.\n", mpu_port[dev]);
	पूर्ण

	अगर (fm_port[dev] > 0) अणु
		अगर (snd_opl3_create(card,
				    fm_port[dev], fm_port[dev] + 2,
				    OPL3_HW_AUTO, 0, &opl3) < 0) अणु
			prपूर्णांकk(KERN_ERR PFX "no OPL device at 0x%lx-0x%lx.\n", fm_port[dev], fm_port[dev] + 2);
		पूर्ण अन्यथा अणु
			error = snd_opl3_hwdep_new(opl3, 0, 1, शून्य);
			अगर (error < 0) अणु
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

अटल अचिन्हित पूर्णांक ad1816a_devices;

अटल पूर्णांक snd_ad1816a_pnp_detect(काष्ठा pnp_card_link *card,
				  स्थिर काष्ठा pnp_card_device_id *id)
अणु
	अटल पूर्णांक dev;
	पूर्णांक res;

	क्रम ( ; dev < SNDRV_CARDS; dev++) अणु
		अगर (!enable[dev])
			जारी;
		res = snd_card_ad1816a_probe(dev, card, id);
		अगर (res < 0)
			वापस res;
		dev++;
		ad1816a_devices++;
		वापस 0;
	पूर्ण
        वापस -ENODEV;
पूर्ण

अटल व्योम snd_ad1816a_pnp_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_ad1816a_pnp_suspend(काष्ठा pnp_card_link *pcard,
				   pm_message_t state)
अणु
	काष्ठा snd_card *card = pnp_get_card_drvdata(pcard);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_ad1816a_suspend(card->निजी_data);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_pnp_resume(काष्ठा pnp_card_link *pcard)
अणु
	काष्ठा snd_card *card = pnp_get_card_drvdata(pcard);

	snd_ad1816a_resume(card->निजी_data);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pnp_card_driver ad1816a_pnpc_driver = अणु
	.flags		= PNP_DRIVER_RES_DISABLE,
	.name		= "ad1816a",
	.id_table	= snd_ad1816a_pnpids,
	.probe		= snd_ad1816a_pnp_detect,
	.हटाओ		= snd_ad1816a_pnp_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_ad1816a_pnp_suspend,
	.resume		= snd_ad1816a_pnp_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init alsa_card_ad1816a_init(व्योम)
अणु
	पूर्णांक err;

	err = pnp_रेजिस्टर_card_driver(&ad1816a_pnpc_driver);
	अगर (err)
		वापस err;

	अगर (!ad1816a_devices) अणु
		pnp_unरेजिस्टर_card_driver(&ad1816a_pnpc_driver);
#अगर_घोषित MODULE
		prपूर्णांकk(KERN_ERR "no AD1816A based soundcards found.\n");
#पूर्ण_अगर	/* MODULE */
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_card_ad1816a_निकास(व्योम)
अणु
	pnp_unरेजिस्टर_card_driver(&ad1816a_pnpc_driver);
पूर्ण

module_init(alsa_card_ad1816a_init)
module_निकास(alsa_card_ad1816a_निकास)
