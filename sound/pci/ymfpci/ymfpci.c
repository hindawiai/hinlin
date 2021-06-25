<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  The driver क्रम the Yamaha's DS1/DS1E cards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/समय.स>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश "ymfpci.h"
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Yamaha DS-1 PCI");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
अटल दीर्घ fm_port[SNDRV_CARDS];
अटल दीर्घ mpu_port[SNDRV_CARDS];
#अगर_घोषित SUPPORT_JOYSTICK
अटल दीर्घ joystick_port[SNDRV_CARDS];
#पूर्ण_अगर
अटल bool rear_चयन[SNDRV_CARDS];

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for the Yamaha DS-1 PCI soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for the Yamaha DS-1 PCI soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Yamaha DS-1 soundcard.");
module_param_hw_array(mpu_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 Port.");
module_param_hw_array(fm_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(fm_port, "FM OPL-3 Port.");
#अगर_घोषित SUPPORT_JOYSTICK
module_param_hw_array(joystick_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(joystick_port, "Joystick port address");
#पूर्ण_अगर
module_param_array(rear_चयन, bool, शून्य, 0444);
MODULE_PARM_DESC(rear_चयन, "Enable shared rear/line-in switch");

अटल स्थिर काष्ठा pci_device_id snd_ymfpci_ids[] = अणु
	अणु PCI_VDEVICE(YAMAHA, 0x0004), 0, पूर्ण,   /* YMF724 */
	अणु PCI_VDEVICE(YAMAHA, 0x000d), 0, पूर्ण,   /* YMF724F */
	अणु PCI_VDEVICE(YAMAHA, 0x000a), 0, पूर्ण,   /* YMF740 */
	अणु PCI_VDEVICE(YAMAHA, 0x000c), 0, पूर्ण,   /* YMF740C */
	अणु PCI_VDEVICE(YAMAHA, 0x0010), 0, पूर्ण,   /* YMF744 */
	अणु PCI_VDEVICE(YAMAHA, 0x0012), 0, पूर्ण,   /* YMF754 */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_ymfpci_ids);

#अगर_घोषित SUPPORT_JOYSTICK
अटल पूर्णांक snd_ymfpci_create_gameport(काष्ठा snd_ymfpci *chip, पूर्णांक dev,
				      पूर्णांक legacy_ctrl, पूर्णांक legacy_ctrl2)
अणु
	काष्ठा gameport *gp;
	काष्ठा resource *r = शून्य;
	पूर्णांक io_port = joystick_port[dev];

	अगर (!io_port)
		वापस -ENODEV;

	अगर (chip->pci->device >= 0x0010) अणु /* YMF 744/754 */

		अगर (io_port == 1) अणु
			/* स्वतः-detect */
			अगर (!(io_port = pci_resource_start(chip->pci, 2)))
				वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (io_port == 1) अणु
			/* स्वतः-detect */
			क्रम (io_port = 0x201; io_port <= 0x205; io_port++) अणु
				अगर (io_port == 0x203)
					जारी;
				अगर ((r = request_region(io_port, 1, "YMFPCI gameport")) != शून्य)
					अवरोध;
			पूर्ण
			अगर (!r) अणु
				dev_err(chip->card->dev,
					"no gameport ports available\n");
				वापस -EBUSY;
			पूर्ण
		पूर्ण
		चयन (io_port) अणु
		हाल 0x201: legacy_ctrl2 |= 0 << 6; अवरोध;
		हाल 0x202: legacy_ctrl2 |= 1 << 6; अवरोध;
		हाल 0x204: legacy_ctrl2 |= 2 << 6; अवरोध;
		हाल 0x205: legacy_ctrl2 |= 3 << 6; अवरोध;
		शेष:
			dev_err(chip->card->dev,
				"invalid joystick port %#x", io_port);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!r && !(r = request_region(io_port, 1, "YMFPCI gameport"))) अणु
		dev_err(chip->card->dev,
			"joystick port %#x is in use.\n", io_port);
		वापस -EBUSY;
	पूर्ण

	chip->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(chip->card->dev,
			"cannot allocate memory for gameport\n");
		release_and_मुक्त_resource(r);
		वापस -ENOMEM;
	पूर्ण


	gameport_set_name(gp, "Yamaha YMF Gameport");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(chip->pci));
	gameport_set_dev_parent(gp, &chip->pci->dev);
	gp->io = io_port;
	gameport_set_port_data(gp, r);

	अगर (chip->pci->device >= 0x0010) /* YMF 744/754 */
		pci_ग_लिखो_config_word(chip->pci, PCIR_DSXG_JOYBASE, io_port);

	pci_ग_लिखो_config_word(chip->pci, PCIR_DSXG_LEGACY, legacy_ctrl | YMFPCI_LEGACY_JPEN);
	pci_ग_लिखो_config_word(chip->pci, PCIR_DSXG_ELEGACY, legacy_ctrl2);

	gameport_रेजिस्टर_port(chip->gameport);

	वापस 0;
पूर्ण

व्योम snd_ymfpci_मुक्त_gameport(काष्ठा snd_ymfpci *chip)
अणु
	अगर (chip->gameport) अणु
		काष्ठा resource *r = gameport_get_port_data(chip->gameport);

		gameport_unरेजिस्टर_port(chip->gameport);
		chip->gameport = शून्य;

		release_and_मुक्त_resource(r);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक snd_ymfpci_create_gameport(काष्ठा snd_ymfpci *chip, पूर्णांक dev, पूर्णांक l, पूर्णांक l2) अणु वापस -ENOSYS; पूर्ण
व्योम snd_ymfpci_मुक्त_gameport(काष्ठा snd_ymfpci *chip) अणु पूर्ण
#पूर्ण_अगर /* SUPPORT_JOYSTICK */

अटल पूर्णांक snd_card_ymfpci_probe(काष्ठा pci_dev *pci,
				 स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा resource *fm_res = शून्य;
	काष्ठा resource *mpu_res = शून्य;
	काष्ठा snd_ymfpci *chip;
	काष्ठा snd_opl3 *opl3;
	स्थिर अक्षर *str, *model;
	पूर्णांक err;
	u16 legacy_ctrl, legacy_ctrl2, old_legacy_ctrl;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

	चयन (pci_id->device) अणु
	हाल 0x0004: str = "YMF724";  model = "DS-1"; अवरोध;
	हाल 0x000d: str = "YMF724F"; model = "DS-1"; अवरोध;
	हाल 0x000a: str = "YMF740";  model = "DS-1L"; अवरोध;
	हाल 0x000c: str = "YMF740C"; model = "DS-1L"; अवरोध;
	हाल 0x0010: str = "YMF744";  model = "DS-1S"; अवरोध;
	हाल 0x0012: str = "YMF754";  model = "DS-1E"; अवरोध;
	शेष: model = str = "???"; अवरोध;
	पूर्ण

	legacy_ctrl = 0;
	legacy_ctrl2 = 0x0800;	/* SBEN = 0, SMOD = 01, LAD = 0 */

	अगर (pci_id->device >= 0x0010) अणु /* YMF 744/754 */
		अगर (fm_port[dev] == 1) अणु
			/* स्वतः-detect */
			fm_port[dev] = pci_resource_start(pci, 1);
		पूर्ण
		अगर (fm_port[dev] > 0 &&
		    (fm_res = request_region(fm_port[dev], 4, "YMFPCI OPL3")) != शून्य) अणु
			legacy_ctrl |= YMFPCI_LEGACY_FMEN;
			pci_ग_लिखो_config_word(pci, PCIR_DSXG_FMBASE, fm_port[dev]);
		पूर्ण
		अगर (mpu_port[dev] == 1) अणु
			/* स्वतः-detect */
			mpu_port[dev] = pci_resource_start(pci, 1) + 0x20;
		पूर्ण
		अगर (mpu_port[dev] > 0 &&
		    (mpu_res = request_region(mpu_port[dev], 2, "YMFPCI MPU401")) != शून्य) अणु
			legacy_ctrl |= YMFPCI_LEGACY_MEN;
			pci_ग_लिखो_config_word(pci, PCIR_DSXG_MPU401BASE, mpu_port[dev]);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (fm_port[dev]) अणु
		हाल 0x388: legacy_ctrl2 |= 0; अवरोध;
		हाल 0x398: legacy_ctrl2 |= 1; अवरोध;
		हाल 0x3a0: legacy_ctrl2 |= 2; अवरोध;
		हाल 0x3a8: legacy_ctrl2 |= 3; अवरोध;
		शेष: fm_port[dev] = 0; अवरोध;
		पूर्ण
		अगर (fm_port[dev] > 0 &&
		    (fm_res = request_region(fm_port[dev], 4, "YMFPCI OPL3")) != शून्य) अणु
			legacy_ctrl |= YMFPCI_LEGACY_FMEN;
		पूर्ण अन्यथा अणु
			legacy_ctrl2 &= ~YMFPCI_LEGACY2_FMIO;
			fm_port[dev] = 0;
		पूर्ण
		चयन (mpu_port[dev]) अणु
		हाल 0x330: legacy_ctrl2 |= 0 << 4; अवरोध;
		हाल 0x300: legacy_ctrl2 |= 1 << 4; अवरोध;
		हाल 0x332: legacy_ctrl2 |= 2 << 4; अवरोध;
		हाल 0x334: legacy_ctrl2 |= 3 << 4; अवरोध;
		शेष: mpu_port[dev] = 0; अवरोध;
		पूर्ण
		अगर (mpu_port[dev] > 0 &&
		    (mpu_res = request_region(mpu_port[dev], 2, "YMFPCI MPU401")) != शून्य) अणु
			legacy_ctrl |= YMFPCI_LEGACY_MEN;
		पूर्ण अन्यथा अणु
			legacy_ctrl2 &= ~YMFPCI_LEGACY2_MPUIO;
			mpu_port[dev] = 0;
		पूर्ण
	पूर्ण
	अगर (mpu_res) अणु
		legacy_ctrl |= YMFPCI_LEGACY_MIEN;
		legacy_ctrl2 |= YMFPCI_LEGACY2_IMOD;
	पूर्ण
	pci_पढ़ो_config_word(pci, PCIR_DSXG_LEGACY, &old_legacy_ctrl);
	pci_ग_लिखो_config_word(pci, PCIR_DSXG_LEGACY, legacy_ctrl);
	pci_ग_लिखो_config_word(pci, PCIR_DSXG_ELEGACY, legacy_ctrl2);
	अगर ((err = snd_ymfpci_create(card, pci,
				     old_legacy_ctrl,
			 	     &chip)) < 0) अणु
		release_and_मुक्त_resource(mpu_res);
		release_and_मुक्त_resource(fm_res);
		जाओ मुक्त_card;
	पूर्ण
	chip->fm_res = fm_res;
	chip->mpu_res = mpu_res;
	card->निजी_data = chip;

	म_नकल(card->driver, str);
	प्र_लिखो(card->लघुname, "Yamaha %s (%s)", model, str);
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %i",
		card->लघुname,
		chip->reg_area_phys,
		chip->irq);
	err = snd_ymfpci_pcm(chip, 0);
	अगर (err < 0)
		जाओ मुक्त_card;

	err = snd_ymfpci_pcm_spdअगर(chip, 1);
	अगर (err < 0)
		जाओ मुक्त_card;

	err = snd_ymfpci_mixer(chip, rear_चयन[dev]);
	अगर (err < 0)
		जाओ मुक्त_card;

	अगर (chip->ac97->ext_id & AC97_EI_SDAC) अणु
		err = snd_ymfpci_pcm_4ch(chip, 2);
		अगर (err < 0)
			जाओ मुक्त_card;

		err = snd_ymfpci_pcm2(chip, 3);
		अगर (err < 0)
			जाओ मुक्त_card;
	पूर्ण
	err = snd_ymfpci_समयr(chip, 0);
	अगर (err < 0)
		जाओ मुक्त_card;

	अगर (chip->mpu_res) अणु
		अगर ((err = snd_mpu401_uart_new(card, 0, MPU401_HW_YMFPCI,
					       mpu_port[dev],
					       MPU401_INFO_INTEGRATED |
					       MPU401_INFO_IRQ_HOOK,
					       -1, &chip->rawmidi)) < 0) अणु
			dev_warn(card->dev,
				 "cannot initialize MPU401 at 0x%lx, skipping...\n",
				 mpu_port[dev]);
			legacy_ctrl &= ~YMFPCI_LEGACY_MIEN; /* disable MPU401 irq */
			pci_ग_लिखो_config_word(pci, PCIR_DSXG_LEGACY, legacy_ctrl);
		पूर्ण
	पूर्ण
	अगर (chip->fm_res) अणु
		अगर ((err = snd_opl3_create(card,
					   fm_port[dev],
					   fm_port[dev] + 2,
					   OPL3_HW_OPL3, 1, &opl3)) < 0) अणु
			dev_warn(card->dev,
				 "cannot initialize FM OPL3 at 0x%lx, skipping...\n",
				 fm_port[dev]);
			legacy_ctrl &= ~YMFPCI_LEGACY_FMEN;
			pci_ग_लिखो_config_word(pci, PCIR_DSXG_LEGACY, legacy_ctrl);
		पूर्ण अन्यथा अगर ((err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य)) < 0) अणु
			dev_err(card->dev, "cannot create opl3 hwdep\n");
			जाओ मुक्त_card;
		पूर्ण
	पूर्ण

	snd_ymfpci_create_gameport(chip, dev, legacy_ctrl, legacy_ctrl2);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ मुक्त_card;

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;

मुक्त_card:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_card_ymfpci_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver ymfpci_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_ymfpci_ids,
	.probe = snd_card_ymfpci_probe,
	.हटाओ = snd_card_ymfpci_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.driver = अणु
		.pm = &snd_ymfpci_pm,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(ymfpci_driver);
