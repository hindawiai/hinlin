<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PC-Speaker driver क्रम Linux
 *
 * Copyright (C) 1997-2001  David Woodhouse
 * Copyright (C) 2001-2008  Stas Sergeev
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mm.h>
#समावेश "pcsp_input.h"
#समावेश "pcsp.h"

MODULE_AUTHOR("Stas Sergeev <stsp@users.sourceforge.net>");
MODULE_DESCRIPTION("PC-Speaker driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pcspkr");

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;	/* Index 0-MAX */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;	/* ID क्रम this card */
अटल bool enable = SNDRV_DEFAULT_ENABLE1;	/* Enable this card */
अटल bool nopcm;	/* Disable PCM capability of the driver */

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for pcsp soundcard.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for pcsp soundcard.");
module_param(enable, bool, 0444);
MODULE_PARM_DESC(enable, "Enable PC-Speaker sound.");
module_param(nopcm, bool, 0444);
MODULE_PARM_DESC(nopcm, "Disable PC-Speaker PCM sound. Only beeps remain.");

काष्ठा snd_pcsp pcsp_chip;

अटल पूर्णांक snd_pcsp_create(काष्ठा snd_card *card)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु पूर्ण;
	अचिन्हित पूर्णांक resolution = hrसमयr_resolution;
	पूर्णांक err, भाग, min_भाग, order;

	अगर (!nopcm) अणु
		अगर (resolution > PCSP_MAX_PERIOD_NS) अणु
			prपूर्णांकk(KERN_ERR "PCSP: Timer resolution is not sufficient "
				"(%unS)\n", resolution);
			prपूर्णांकk(KERN_ERR "PCSP: Make sure you have HPET and ACPI "
				"enabled.\n");
			prपूर्णांकk(KERN_ERR "PCSP: Turned into nopcm mode.\n");
			nopcm = 1;
		पूर्ण
	पूर्ण

	अगर (loops_per_jअगरfy >= PCSP_MIN_LPJ && resolution <= PCSP_MIN_PERIOD_NS)
		min_भाग = MIN_DIV;
	अन्यथा
		min_भाग = MAX_DIV;
#अगर PCSP_DEBUG
	prपूर्णांकk(KERN_DEBUG "PCSP: lpj=%li, min_div=%i, res=%u\n",
	       loops_per_jअगरfy, min_भाग, resolution);
#पूर्ण_अगर

	भाग = MAX_DIV / min_भाग;
	order = fls(भाग) - 1;

	pcsp_chip.max_treble = min(order, PCSP_MAX_TREBLE);
	pcsp_chip.treble = min(pcsp_chip.max_treble, PCSP_DEFAULT_TREBLE);
	pcsp_chip.playback_ptr = 0;
	pcsp_chip.period_ptr = 0;
	atomic_set(&pcsp_chip.समयr_active, 0);
	pcsp_chip.enable = 1;
	pcsp_chip.pcspkr = 1;

	spin_lock_init(&pcsp_chip.substream_lock);

	pcsp_chip.card = card;
	pcsp_chip.port = 0x61;
	pcsp_chip.irq = -1;
	pcsp_chip.dma = -1;

	/* Register device */
	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, &pcsp_chip, &ops);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_card_pcsp_probe(पूर्णांक devnum, काष्ठा device *dev)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	अगर (devnum != 0)
		वापस -EINVAL;

	hrसमयr_init(&pcsp_chip.समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	pcsp_chip.समयr.function = pcsp_करो_समयr;

	err = snd_card_new(dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	err = snd_pcsp_create(card);
	अगर (err < 0)
		जाओ मुक्त_card;

	अगर (!nopcm) अणु
		err = snd_pcsp_new_pcm(&pcsp_chip);
		अगर (err < 0)
			जाओ मुक्त_card;
	पूर्ण
	err = snd_pcsp_new_mixer(&pcsp_chip, nopcm);
	अगर (err < 0)
		जाओ मुक्त_card;

	म_नकल(card->driver, "PC-Speaker");
	म_नकल(card->लघुname, "pcsp");
	प्र_लिखो(card->दीर्घname, "Internal PC-Speaker at port 0x%x",
		pcsp_chip.port);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ मुक्त_card;

	वापस 0;

मुक्त_card:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक alsa_card_pcsp_init(काष्ठा device *dev)
अणु
	पूर्णांक err;

	err = snd_card_pcsp_probe(0, dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "PC-Speaker initialization failed.\n");
		वापस err;
	पूर्ण

	/* Well, CONFIG_DEBUG_PAGEALLOC makes the sound horrible. Lets alert */
	अगर (debug_pagealloc_enabled()) अणु
		prपूर्णांकk(KERN_WARNING "PCSP: CONFIG_DEBUG_PAGEALLOC is enabled, "
		       "which may make the sound noisy.\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम alsa_card_pcsp_निकास(काष्ठा snd_pcsp *chip)
अणु
	snd_card_मुक्त(chip->card);
पूर्ण

अटल पूर्णांक pcsp_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक err;

	err = pcspkr_input_init(&pcsp_chip.input_dev, &dev->dev);
	अगर (err < 0)
		वापस err;

	err = alsa_card_pcsp_init(&dev->dev);
	अगर (err < 0) अणु
		pcspkr_input_हटाओ(pcsp_chip.input_dev);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(dev, &pcsp_chip);
	वापस 0;
पूर्ण

अटल पूर्णांक pcsp_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा snd_pcsp *chip = platक्रमm_get_drvdata(dev);
	pcspkr_input_हटाओ(chip->input_dev);
	alsa_card_pcsp_निकास(chip);
	वापस 0;
पूर्ण

अटल व्योम pcsp_stop_beep(काष्ठा snd_pcsp *chip)
अणु
	pcsp_sync_stop(chip);
	pcspkr_stop_sound();
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pcsp_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_pcsp *chip = dev_get_drvdata(dev);
	pcsp_stop_beep(chip);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pcsp_pm, pcsp_suspend, शून्य);
#घोषणा PCSP_PM_OPS	&pcsp_pm
#अन्यथा
#घोषणा PCSP_PM_OPS	शून्य
#पूर्ण_अगर	/* CONFIG_PM_SLEEP */

अटल व्योम pcsp_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा snd_pcsp *chip = platक्रमm_get_drvdata(dev);
	pcsp_stop_beep(chip);
पूर्ण

अटल काष्ठा platक्रमm_driver pcsp_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= "pcspkr",
		.pm	= PCSP_PM_OPS,
	पूर्ण,
	.probe		= pcsp_probe,
	.हटाओ		= pcsp_हटाओ,
	.shutकरोwn	= pcsp_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init pcsp_init(व्योम)
अणु
	अगर (!enable)
		वापस -ENODEV;
	वापस platक्रमm_driver_रेजिस्टर(&pcsp_platक्रमm_driver);
पूर्ण

अटल व्योम __निकास pcsp_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&pcsp_platक्रमm_driver);
पूर्ण

module_init(pcsp_init);
module_निकास(pcsp_निकास);
