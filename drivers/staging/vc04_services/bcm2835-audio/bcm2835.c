<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2011 Broadcom Corporation.  All rights reserved. */

#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश "bcm2835.h"

अटल bool enable_hdmi;
अटल bool enable_headphones;
अटल bool enable_compat_alsa = true;
अटल पूर्णांक num_channels = MAX_SUBSTREAMS;

module_param(enable_hdmi, bool, 0444);
MODULE_PARM_DESC(enable_hdmi, "Enables HDMI virtual audio device");
module_param(enable_headphones, bool, 0444);
MODULE_PARM_DESC(enable_headphones, "Enables Headphones virtual audio device");
module_param(enable_compat_alsa, bool, 0444);
MODULE_PARM_DESC(enable_compat_alsa,
		 "Enables ALSA compatibility virtual audio device");
module_param(num_channels, पूर्णांक, 0644);
MODULE_PARM_DESC(num_channels, "Number of audio channels (default: 8)");

अटल व्योम bcm2835_devm_मुक्त_vchi_ctx(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा bcm2835_vchi_ctx *vchi_ctx = res;

	bcm2835_मुक्त_vchi_ctx(vchi_ctx);
पूर्ण

अटल पूर्णांक bcm2835_devm_add_vchi_ctx(काष्ठा device *dev)
अणु
	काष्ठा bcm2835_vchi_ctx *vchi_ctx;
	पूर्णांक ret;

	vchi_ctx = devres_alloc(bcm2835_devm_मुक्त_vchi_ctx, माप(*vchi_ctx),
				GFP_KERNEL);
	अगर (!vchi_ctx)
		वापस -ENOMEM;

	ret = bcm2835_new_vchi_ctx(dev, vchi_ctx);
	अगर (ret) अणु
		devres_मुक्त(vchi_ctx);
		वापस ret;
	पूर्ण

	devres_add(dev, vchi_ctx);

	वापस 0;
पूर्ण

प्रकार पूर्णांक (*bcm2835_audio_newpcm_func)(काष्ठा bcm2835_chip *chip,
					 स्थिर अक्षर *name,
					 क्रमागत snd_bcm2835_route route,
					 u32 numchannels);

प्रकार पूर्णांक (*bcm2835_audio_newctl_func)(काष्ठा bcm2835_chip *chip);

काष्ठा bcm2835_audio_driver अणु
	काष्ठा device_driver driver;
	स्थिर अक्षर *लघुname;
	स्थिर अक्षर *दीर्घname;
	पूर्णांक minchannels;
	bcm2835_audio_newpcm_func newpcm;
	bcm2835_audio_newctl_func newctl;
	क्रमागत snd_bcm2835_route route;
पूर्ण;

अटल पूर्णांक bcm2835_audio_alsa_newpcm(काष्ठा bcm2835_chip *chip,
				     स्थिर अक्षर *name,
				     क्रमागत snd_bcm2835_route route,
				     u32 numchannels)
अणु
	पूर्णांक err;

	err = snd_bcm2835_new_pcm(chip, "bcm2835 ALSA", 0, AUDIO_DEST_AUTO,
				  numchannels - 1, false);
	अगर (err)
		वापस err;

	err = snd_bcm2835_new_pcm(chip, "bcm2835 IEC958/HDMI", 1, 0, 1, true);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_audio_simple_newpcm(काष्ठा bcm2835_chip *chip,
				       स्थिर अक्षर *name,
				       क्रमागत snd_bcm2835_route route,
				       u32 numchannels)
अणु
	वापस snd_bcm2835_new_pcm(chip, name, 0, route, numchannels, false);
पूर्ण

अटल काष्ठा bcm2835_audio_driver bcm2835_audio_alsa = अणु
	.driver = अणु
		.name = "bcm2835_alsa",
		.owner = THIS_MODULE,
	पूर्ण,
	.लघुname = "bcm2835 ALSA",
	.दीर्घname  = "bcm2835 ALSA",
	.minchannels = 2,
	.newpcm = bcm2835_audio_alsa_newpcm,
	.newctl = snd_bcm2835_new_ctl,
पूर्ण;

अटल काष्ठा bcm2835_audio_driver bcm2835_audio_hdmi = अणु
	.driver = अणु
		.name = "bcm2835_hdmi",
		.owner = THIS_MODULE,
	पूर्ण,
	.लघुname = "bcm2835 HDMI",
	.दीर्घname  = "bcm2835 HDMI",
	.minchannels = 1,
	.newpcm = bcm2835_audio_simple_newpcm,
	.newctl = snd_bcm2835_new_hdmi_ctl,
	.route = AUDIO_DEST_HDMI
पूर्ण;

अटल काष्ठा bcm2835_audio_driver bcm2835_audio_headphones = अणु
	.driver = अणु
		.name = "bcm2835_headphones",
		.owner = THIS_MODULE,
	पूर्ण,
	.लघुname = "bcm2835 Headphones",
	.दीर्घname  = "bcm2835 Headphones",
	.minchannels = 1,
	.newpcm = bcm2835_audio_simple_newpcm,
	.newctl = snd_bcm2835_new_headphones_ctl,
	.route = AUDIO_DEST_HEADPHONES
पूर्ण;

काष्ठा bcm2835_audio_drivers अणु
	काष्ठा bcm2835_audio_driver *audio_driver;
	स्थिर bool *is_enabled;
पूर्ण;

अटल काष्ठा bcm2835_audio_drivers children_devices[] = अणु
	अणु
		.audio_driver = &bcm2835_audio_alsa,
		.is_enabled = &enable_compat_alsa,
	पूर्ण,
	अणु
		.audio_driver = &bcm2835_audio_hdmi,
		.is_enabled = &enable_hdmi,
	पूर्ण,
	अणु
		.audio_driver = &bcm2835_audio_headphones,
		.is_enabled = &enable_headphones,
	पूर्ण,
पूर्ण;

अटल व्योम bcm2835_card_मुक्त(व्योम *data)
अणु
	snd_card_मुक्त(data);
पूर्ण

अटल पूर्णांक snd_add_child_device(काष्ठा device *dev,
				काष्ठा bcm2835_audio_driver *audio_driver,
				u32 numchans)
अणु
	काष्ठा bcm2835_chip *chip;
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_card_new(dev, -1, शून्य, THIS_MODULE, माप(*chip), &card);
	अगर (err < 0) अणु
		dev_err(dev, "Failed to create card");
		वापस err;
	पूर्ण

	chip = card->निजी_data;
	chip->card = card;
	chip->dev = dev;
	mutex_init(&chip->audio_mutex);

	chip->vchi_ctx = devres_find(dev,
				     bcm2835_devm_मुक्त_vchi_ctx, शून्य, शून्य);
	अगर (!chip->vchi_ctx) अणु
		err = -ENODEV;
		जाओ error;
	पूर्ण

	strscpy(card->driver, audio_driver->driver.name, माप(card->driver));
	strscpy(card->लघुname, audio_driver->लघुname, माप(card->लघुname));
	strscpy(card->दीर्घname, audio_driver->दीर्घname, माप(card->दीर्घname));

	err = audio_driver->newpcm(chip, audio_driver->लघुname,
		audio_driver->route,
		numchans);
	अगर (err) अणु
		dev_err(dev, "Failed to create pcm, error %d\n", err);
		जाओ error;
	पूर्ण

	err = audio_driver->newctl(chip);
	अगर (err) अणु
		dev_err(dev, "Failed to create controls, error %d\n", err);
		जाओ error;
	पूर्ण

	err = snd_card_रेजिस्टर(card);
	अगर (err) अणु
		dev_err(dev, "Failed to register card, error %d\n", err);
		जाओ error;
	पूर्ण

	dev_set_drvdata(dev, chip);

	err = devm_add_action(dev, bcm2835_card_मुक्त, card);
	अगर (err < 0) अणु
		dev_err(dev, "Failed to add devm action, err %d\n", err);
		जाओ error;
	पूर्ण

	dev_info(dev, "card created with %d channels\n", numchans);
	वापस 0;

 error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक snd_add_child_devices(काष्ठा device *device, u32 numchans)
अणु
	पूर्णांक extrachannels_per_driver = 0;
	पूर्णांक extrachannels_reमुख्यder = 0;
	पूर्णांक count_devices = 0;
	पूर्णांक extrachannels = 0;
	पूर्णांक minchannels = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(children_devices); i++)
		अगर (*children_devices[i].is_enabled)
			count_devices++;

	अगर (!count_devices)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(children_devices); i++)
		अगर (*children_devices[i].is_enabled)
			minchannels +=
				children_devices[i].audio_driver->minchannels;

	अगर (minchannels < numchans) अणु
		extrachannels = numchans - minchannels;
		extrachannels_per_driver = extrachannels / count_devices;
		extrachannels_reमुख्यder = extrachannels % count_devices;
	पूर्ण

	dev_dbg(device, "minchannels %d\n", minchannels);
	dev_dbg(device, "extrachannels %d\n", extrachannels);
	dev_dbg(device, "extrachannels_per_driver %d\n",
		extrachannels_per_driver);
	dev_dbg(device, "extrachannels_remainder %d\n",
		extrachannels_reमुख्यder);

	क्रम (i = 0; i < ARRAY_SIZE(children_devices); i++) अणु
		काष्ठा bcm2835_audio_driver *audio_driver;
		पूर्णांक numchannels_this_device;
		पूर्णांक err;

		अगर (!*children_devices[i].is_enabled)
			जारी;

		audio_driver = children_devices[i].audio_driver;

		अगर (audio_driver->minchannels > numchans) अणु
			dev_err(device,
				"Out of channels, needed %d but only %d left\n",
				audio_driver->minchannels,
				numchans);
			जारी;
		पूर्ण

		numchannels_this_device =
			audio_driver->minchannels + extrachannels_per_driver +
			extrachannels_reमुख्यder;
		extrachannels_reमुख्यder = 0;

		numchans -= numchannels_this_device;

		err = snd_add_child_device(device, audio_driver,
					   numchannels_this_device);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_bcm2835_alsa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err;

	अगर (num_channels <= 0 || num_channels > MAX_SUBSTREAMS) अणु
		num_channels = MAX_SUBSTREAMS;
		dev_warn(dev, "Illegal num_channels value, will use %u\n",
			 num_channels);
	पूर्ण

	err = bcm2835_devm_add_vchi_ctx(dev);
	अगर (err)
		वापस err;

	err = snd_add_child_devices(dev, num_channels);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक snd_bcm2835_alsa_suspend(काष्ठा platक्रमm_device *pdev,
				    pm_message_t state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bcm2835_alsa_resume(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver bcm2835_alsa_driver = अणु
	.probe = snd_bcm2835_alsa_probe,
#अगर_घोषित CONFIG_PM
	.suspend = snd_bcm2835_alsa_suspend,
	.resume = snd_bcm2835_alsa_resume,
#पूर्ण_अगर
	.driver = अणु
		.name = "bcm2835_audio",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm2835_alsa_driver);

MODULE_AUTHOR("Dom Cobley");
MODULE_DESCRIPTION("Alsa driver for BCM2835 chip");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bcm2835_audio");
