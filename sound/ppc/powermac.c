<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम PowerMac AWACS
 * Copyright (c) 2001 by Takashi Iwai <tiwai@suse.de>
 *   based on dmasound.c.
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश "pmac.h"
#समावेश "awacs.h"
#समावेश "burgundy.h"

#घोषणा CHIP_NAME "PMac"

MODULE_DESCRIPTION("PowerMac");
MODULE_LICENSE("GPL");

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;		/* Index 0-MAX */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;		/* ID क्रम this card */
अटल bool enable_beep = 1;

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for " CHIP_NAME " soundchip.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for " CHIP_NAME " soundchip.");
module_param(enable_beep, bool, 0444);
MODULE_PARM_DESC(enable_beep, "Enable beep using PCM.");

अटल काष्ठा platक्रमm_device *device;


/*
 */

अटल पूर्णांक snd_pmac_probe(काष्ठा platक्रमm_device *devptr)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_pmac *chip;
	अक्षर *name_ext;
	पूर्णांक err;

	err = snd_card_new(&devptr->dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	अगर ((err = snd_pmac_new(card, &chip)) < 0)
		जाओ __error;
	card->निजी_data = chip;

	चयन (chip->model) अणु
	हाल PMAC_BURGUNDY:
		म_नकल(card->driver, "PMac Burgundy");
		म_नकल(card->लघुname, "PowerMac Burgundy");
		प्र_लिखो(card->दीर्घname, "%s (Dev %d) Sub-frame %d",
			card->लघुname, chip->device_id, chip->subframe);
		अगर ((err = snd_pmac_burgundy_init(chip)) < 0)
			जाओ __error;
		अवरोध;
	हाल PMAC_DACA:
		म_नकल(card->driver, "PMac DACA");
		म_नकल(card->लघुname, "PowerMac DACA");
		प्र_लिखो(card->दीर्घname, "%s (Dev %d) Sub-frame %d",
			card->लघुname, chip->device_id, chip->subframe);
		अगर ((err = snd_pmac_daca_init(chip)) < 0)
			जाओ __error;
		अवरोध;
	हाल PMAC_TUMBLER:
	हाल PMAC_SNAPPER:
		name_ext = chip->model == PMAC_TUMBLER ? "Tumbler" : "Snapper";
		प्र_लिखो(card->driver, "PMac %s", name_ext);
		प्र_लिखो(card->लघुname, "PowerMac %s", name_ext);
		प्र_लिखो(card->दीर्घname, "%s (Dev %d) Sub-frame %d",
			card->लघुname, chip->device_id, chip->subframe);
		अगर ( snd_pmac_tumbler_init(chip) < 0 || snd_pmac_tumbler_post_init() < 0)
			जाओ __error;
		अवरोध;
	हाल PMAC_AWACS:
	हाल PMAC_SCREAMER:
		name_ext = chip->model == PMAC_SCREAMER ? "Screamer" : "AWACS";
		प्र_लिखो(card->driver, "PMac %s", name_ext);
		प्र_लिखो(card->लघुname, "PowerMac %s", name_ext);
		अगर (chip->is_pbook_3400)
			name_ext = " [PB3400]";
		अन्यथा अगर (chip->is_pbook_G3)
			name_ext = " [PBG3]";
		अन्यथा
			name_ext = "";
		प्र_लिखो(card->दीर्घname, "%s%s Rev %d",
			card->लघुname, name_ext, chip->revision);
		अगर ((err = snd_pmac_awacs_init(chip)) < 0)
			जाओ __error;
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_ERR "unsupported hardware %d\n", chip->model);
		err = -EINVAL;
		जाओ __error;
	पूर्ण

	अगर ((err = snd_pmac_pcm_new(chip)) < 0)
		जाओ __error;

	chip->initialized = 1;
	अगर (enable_beep)
		snd_pmac_attach_beep(chip);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0)
		जाओ __error;

	platक्रमm_set_drvdata(devptr, card);
	वापस 0;

__error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण


अटल पूर्णांक snd_pmac_हटाओ(काष्ठा platक्रमm_device *devptr)
अणु
	snd_card_मुक्त(platक्रमm_get_drvdata(devptr));
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_pmac_driver_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	snd_pmac_suspend(card->निजी_data);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_driver_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	snd_pmac_resume(card->निजी_data);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_pmac_pm, snd_pmac_driver_suspend, snd_pmac_driver_resume);
#घोषणा SND_PMAC_PM_OPS	&snd_pmac_pm
#अन्यथा
#घोषणा SND_PMAC_PM_OPS	शून्य
#पूर्ण_अगर

#घोषणा SND_PMAC_DRIVER		"snd_powermac"

अटल काष्ठा platक्रमm_driver snd_pmac_driver = अणु
	.probe		= snd_pmac_probe,
	.हटाओ		= snd_pmac_हटाओ,
	.driver		= अणु
		.name	= SND_PMAC_DRIVER,
		.pm	= SND_PMAC_PM_OPS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init alsa_card_pmac_init(व्योम)
अणु
	पूर्णांक err;

	अगर ((err = platक्रमm_driver_रेजिस्टर(&snd_pmac_driver)) < 0)
		वापस err;
	device = platक्रमm_device_रेजिस्टर_simple(SND_PMAC_DRIVER, -1, शून्य, 0);
	वापस 0;

पूर्ण

अटल व्योम __निकास alsa_card_pmac_निकास(व्योम)
अणु
	अगर (!IS_ERR(device))
		platक्रमm_device_unरेजिस्टर(device);
	platक्रमm_driver_unरेजिस्टर(&snd_pmac_driver);
पूर्ण

module_init(alsa_card_pmac_init)
module_निकास(alsa_card_pmac_निकास)
