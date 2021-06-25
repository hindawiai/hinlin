<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
    card-als100.c - driver क्रम Avance Logic ALS100 based soundcards.
    Copyright (C) 1999-2000 by Massimo Piccioni <dafastidio@libero.it>
    Copyright (C) 1999-2002 by Massimo Piccioni <dafastidio@libero.it>

    Thanks to Pierfrancesco 'qM2' Passerini.

    Generalised क्रम soundcards based on DT-0196 and ALS-007 chips
    by Jonathan Woithe <jwoithe@just42.net>: June 2002.

*/

#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <linux/समय.स>
#समावेश <linux/pnp.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#समावेश <sound/sb.h>

#घोषणा PFX "als100: "

MODULE_DESCRIPTION("Avance Logic ALS007/ALS1X0");
MODULE_AUTHOR("Massimo Piccioni <dafastidio@libero.it>");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;	/* Enable this card */
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल दीर्घ mpu_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल दीर्घ fm_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* PnP setup */
अटल पूर्णांक mpu_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* PnP setup */
अटल पूर्णांक dma8[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* PnP setup */
अटल पूर्णांक dma16[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* PnP setup */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Avance Logic based soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Avance Logic based soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Avance Logic based soundcard.");

MODULE_ALIAS("snd-dt019x");

काष्ठा snd_card_als100 अणु
	काष्ठा pnp_dev *dev;
	काष्ठा pnp_dev *devmpu;
	काष्ठा pnp_dev *devopl;
	काष्ठा snd_sb *chip;
पूर्ण;

अटल स्थिर काष्ठा pnp_card_device_id snd_als100_pnpids[] = अणु
	/* DT197A30 */
	अणु .id = "RWB1688",
	  .devs = अणु अणु "@@@0001" पूर्ण, अणु "@X@0001" पूर्ण, अणु "@H@0001" पूर्ण पूर्ण,
	  .driver_data = SB_HW_DT019X पूर्ण,
	/* DT0196 / ALS-007 */
	अणु .id = "ALS0007",
	  .devs = अणु अणु "@@@0001" पूर्ण, अणु "@X@0001" पूर्ण, अणु "@H@0001" पूर्ण पूर्ण,
	  .driver_data = SB_HW_DT019X पूर्ण,
	/* ALS100 - PRO16PNP */
	अणु .id = "ALS0001",
	  .devs = अणु अणु "@@@0001" पूर्ण, अणु "@X@0001" पूर्ण, अणु "@H@0001" पूर्ण पूर्ण,
	  .driver_data = SB_HW_ALS100 पूर्ण,
	/* ALS110 - MF1000 - Digimate 3D Sound */
	अणु .id = "ALS0110",
	  .devs = अणु अणु "@@@1001" पूर्ण, अणु "@X@1001" पूर्ण, अणु "@H@1001" पूर्ण पूर्ण,
	  .driver_data = SB_HW_ALS100 पूर्ण,
	/* ALS120 */
	अणु .id = "ALS0120",
	  .devs = अणु अणु "@@@2001" पूर्ण, अणु "@X@2001" पूर्ण, अणु "@H@2001" पूर्ण पूर्ण,
	  .driver_data = SB_HW_ALS100 पूर्ण,
	/* ALS200 */
	अणु .id = "ALS0200",
	  .devs = अणु अणु "@@@0020" पूर्ण, अणु "@X@0020" पूर्ण, अणु "@H@0001" पूर्ण पूर्ण,
	  .driver_data = SB_HW_ALS100 पूर्ण,
	/* ALS200 OEM */
	अणु .id = "ALS0200",
	  .devs = अणु अणु "@@@0020" पूर्ण, अणु "@X@0020" पूर्ण, अणु "@H@0020" पूर्ण पूर्ण,
	  .driver_data = SB_HW_ALS100 पूर्ण,
	/* RTL3000 */
	अणु .id = "RTL3000",
	  .devs = अणु अणु "@@@2001" पूर्ण, अणु "@X@2001" पूर्ण, अणु "@H@2001" पूर्ण पूर्ण,
	  .driver_data = SB_HW_ALS100 पूर्ण,
	अणु .id = "" पूर्ण /* end */
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_als100_pnpids);

अटल पूर्णांक snd_card_als100_pnp(पूर्णांक dev, काष्ठा snd_card_als100 *acard,
			       काष्ठा pnp_card_link *card,
			       स्थिर काष्ठा pnp_card_device_id *id)
अणु
	काष्ठा pnp_dev *pdev;
	पूर्णांक err;

	acard->dev = pnp_request_card_device(card, id->devs[0].id, शून्य);
	अगर (acard->dev == शून्य)
		वापस -ENODEV;

	acard->devmpu = pnp_request_card_device(card, id->devs[1].id, acard->dev);
	acard->devopl = pnp_request_card_device(card, id->devs[2].id, acard->dev);

	pdev = acard->dev;

	err = pnp_activate_dev(pdev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "AUDIO pnp configure failure\n");
		वापस err;
	पूर्ण
	port[dev] = pnp_port_start(pdev, 0);
	अगर (id->driver_data == SB_HW_DT019X)
		dma8[dev] = pnp_dma(pdev, 0);
	अन्यथा अणु
		dma8[dev] = pnp_dma(pdev, 1);
		dma16[dev] = pnp_dma(pdev, 0);
	पूर्ण
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

	pdev = acard->devopl;
	अगर (pdev != शून्य) अणु
		err = pnp_activate_dev(pdev);
		अगर (err < 0)
			जाओ __fm_error;
		fm_port[dev] = pnp_port_start(pdev, 0);
	पूर्ण अन्यथा अणु
	      __fm_error:
	     	अगर (pdev) अणु
		     	pnp_release_card_device(pdev);
	     		snd_prपूर्णांकk(KERN_ERR PFX "OPL3 pnp configure failure, skipping\n");
	     	पूर्ण
	     	acard->devopl = शून्य;
	     	fm_port[dev] = -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_card_als100_probe(पूर्णांक dev,
				 काष्ठा pnp_card_link *pcard,
				 स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	पूर्णांक error;
	काष्ठा snd_sb *chip;
	काष्ठा snd_card *card;
	काष्ठा snd_card_als100 *acard;
	काष्ठा snd_opl3 *opl3;

	error = snd_card_new(&pcard->card->dev,
			     index[dev], id[dev], THIS_MODULE,
			     माप(काष्ठा snd_card_als100), &card);
	अगर (error < 0)
		वापस error;
	acard = card->निजी_data;

	अगर ((error = snd_card_als100_pnp(dev, acard, pcard, pid))) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण

	अगर (pid->driver_data == SB_HW_DT019X)
		dma16[dev] = -1;

	error = snd_sbdsp_create(card, port[dev], irq[dev],
				  snd_sb16dsp_पूर्णांकerrupt,
				  dma8[dev], dma16[dev],
				  pid->driver_data,
				  &chip);
	अगर (error < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण
	acard->chip = chip;

	अगर (pid->driver_data == SB_HW_DT019X) अणु
		म_नकल(card->driver, "DT-019X");
		म_नकल(card->लघुname, "Diamond Tech. DT-019X");
		snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
			 "Diamond Tech. DT-019X, %s at 0x%lx, irq %d, dma %d",
			 chip->name, chip->port, irq[dev], dma8[dev]);
	पूर्ण अन्यथा अणु
		म_नकल(card->driver, "ALS100");
		म_नकल(card->लघुname, "Avance Logic ALS100");
		snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
			 "Avance Logic ALS100, %s at 0x%lx, irq %d, dma %d&%d",
			 chip->name, chip->port, irq[dev], dma8[dev],
			 dma16[dev]);
	पूर्ण

	अगर ((error = snd_sb16dsp_pcm(chip, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण

	अगर ((error = snd_sbmixer_new(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण

	अगर (mpu_port[dev] > 0 && mpu_port[dev] != SNDRV_AUTO_PORT) अणु
		पूर्णांक mpu_type = MPU401_HW_ALS100;

		अगर (mpu_irq[dev] == SNDRV_AUTO_IRQ)
			mpu_irq[dev] = -1;

		अगर (pid->driver_data == SB_HW_DT019X)
			mpu_type = MPU401_HW_MPU401;

		अगर (snd_mpu401_uart_new(card, 0,
					mpu_type,
					mpu_port[dev], 0, 
					mpu_irq[dev],
					शून्य) < 0)
			snd_prपूर्णांकk(KERN_ERR PFX "no MPU-401 device at 0x%lx\n", mpu_port[dev]);
	पूर्ण

	अगर (fm_port[dev] > 0 && fm_port[dev] != SNDRV_AUTO_PORT) अणु
		अगर (snd_opl3_create(card,
				    fm_port[dev], fm_port[dev] + 2,
				    OPL3_HW_AUTO, 0, &opl3) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "no OPL device at 0x%lx-0x%lx\n",
				   fm_port[dev], fm_port[dev] + 2);
		पूर्ण अन्यथा अणु
			अगर ((error = snd_opl3_समयr_new(opl3, 0, 1)) < 0) अणु
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

अटल अचिन्हित पूर्णांक als100_devices;

अटल पूर्णांक snd_als100_pnp_detect(काष्ठा pnp_card_link *card,
				 स्थिर काष्ठा pnp_card_device_id *id)
अणु
	अटल पूर्णांक dev;
	पूर्णांक res;

	क्रम ( ; dev < SNDRV_CARDS; dev++) अणु
		अगर (!enable[dev])
			जारी;
		res = snd_card_als100_probe(dev, card, id);
		अगर (res < 0)
			वापस res;
		dev++;
		als100_devices++;
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल व्योम snd_als100_pnp_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_als100_pnp_suspend(काष्ठा pnp_card_link *pcard, pm_message_t state)
अणु
	काष्ठा snd_card *card = pnp_get_card_drvdata(pcard);
	काष्ठा snd_card_als100 *acard = card->निजी_data;
	काष्ठा snd_sb *chip = acard->chip;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_sbmixer_suspend(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als100_pnp_resume(काष्ठा pnp_card_link *pcard)
अणु
	काष्ठा snd_card *card = pnp_get_card_drvdata(pcard);
	काष्ठा snd_card_als100 *acard = card->निजी_data;
	काष्ठा snd_sb *chip = acard->chip;

	snd_sbdsp_reset(chip);
	snd_sbmixer_resume(chip);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pnp_card_driver als100_pnpc_driver = अणु
	.flags          = PNP_DRIVER_RES_DISABLE,
	.name		= "als100",
        .id_table       = snd_als100_pnpids,
        .probe          = snd_als100_pnp_detect,
	.हटाओ		= snd_als100_pnp_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_als100_pnp_suspend,
	.resume		= snd_als100_pnp_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init alsa_card_als100_init(व्योम)
अणु
	पूर्णांक err;

	err = pnp_रेजिस्टर_card_driver(&als100_pnpc_driver);
	अगर (err)
		वापस err;

	अगर (!als100_devices) अणु
		pnp_unरेजिस्टर_card_driver(&als100_pnpc_driver);
#अगर_घोषित MODULE
		snd_prपूर्णांकk(KERN_ERR "no Avance Logic based soundcards found\n");
#पूर्ण_अगर
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_card_als100_निकास(व्योम)
अणु
	pnp_unरेजिस्टर_card_driver(&als100_pnpc_driver);
पूर्ण

module_init(alsa_card_als100_init)
module_निकास(alsa_card_als100_निकास)
