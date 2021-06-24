<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Apple Onboard Audio driver क्रम Toonie codec
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 *
 * This is a driver क्रम the toonie codec chip. This chip is present
 * on the Mac Mini and is nothing but a DAC.
 */
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
MODULE_AUTHOR("Johannes Berg <johannes@sipsolutions.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("toonie codec driver for snd-aoa");

#समावेश "../aoa.h"
#समावेश "../soundbus/soundbus.h"


#घोषणा PFX "snd-aoa-codec-toonie: "

काष्ठा toonie अणु
	काष्ठा aoa_codec	codec;
पूर्ण;
#घोषणा codec_to_toonie(c) container_of(c, काष्ठा toonie, codec)

अटल पूर्णांक toonie_dev_रेजिस्टर(काष्ठा snd_device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_device_ops ops = अणु
	.dev_रेजिस्टर = toonie_dev_रेजिस्टर,
पूर्ण;

अटल काष्ठा transfer_info toonie_transfers[] = अणु
	/* This thing *only* has analog output,
	 * the rates are taken from Info.plist
	 * from Darwin. */
	अणु
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_BE |
			   SNDRV_PCM_FMTBIT_S24_BE,
		.rates = SNDRV_PCM_RATE_32000 |
			 SNDRV_PCM_RATE_44100 |
			 SNDRV_PCM_RATE_48000 |
			 SNDRV_PCM_RATE_88200 |
			 SNDRV_PCM_RATE_96000,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक toonie_usable(काष्ठा codec_info_item *cii,
			 काष्ठा transfer_info *ti,
			 काष्ठा transfer_info *out)
अणु
	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक toonie_suspend(काष्ठा codec_info_item *cii, pm_message_t state)
अणु
	/* can we turn it off somehow? */
	वापस 0;
पूर्ण

अटल पूर्णांक toonie_resume(काष्ठा codec_info_item *cii)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा codec_info toonie_codec_info = अणु
	.transfers = toonie_transfers,
	.sysघड़ी_factor = 256,
	.bus_factor = 64,
	.owner = THIS_MODULE,
	.usable = toonie_usable,
#अगर_घोषित CONFIG_PM
	.suspend = toonie_suspend,
	.resume = toonie_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक toonie_init_codec(काष्ठा aoa_codec *codec)
अणु
	काष्ठा toonie *toonie = codec_to_toonie(codec);

	/* nothing connected? what a joke! */
	अगर (toonie->codec.connected != 1)
		वापस -ENOTCONN;

	अगर (aoa_snd_device_new(SNDRV_DEV_CODEC, toonie, &ops)) अणु
		prपूर्णांकk(KERN_ERR PFX "failed to create toonie snd device!\n");
		वापस -ENODEV;
	पूर्ण

	अगर (toonie->codec.soundbus_dev->attach_codec(toonie->codec.soundbus_dev,
						     aoa_get_card(),
						     &toonie_codec_info, toonie)) अणु
		prपूर्णांकk(KERN_ERR PFX "error creating toonie pcm\n");
		snd_device_मुक्त(aoa_get_card(), toonie);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम toonie_निकास_codec(काष्ठा aoa_codec *codec)
अणु
	काष्ठा toonie *toonie = codec_to_toonie(codec);

	अगर (!toonie->codec.soundbus_dev) अणु
		prपूर्णांकk(KERN_ERR PFX "toonie_exit_codec called without soundbus_dev!\n");
		वापस;
	पूर्ण
	toonie->codec.soundbus_dev->detach_codec(toonie->codec.soundbus_dev, toonie);
पूर्ण

अटल काष्ठा toonie *toonie;

अटल पूर्णांक __init toonie_init(व्योम)
अणु
	toonie = kzalloc(माप(काष्ठा toonie), GFP_KERNEL);

	अगर (!toonie)
		वापस -ENOMEM;

	strscpy(toonie->codec.name, "toonie", माप(toonie->codec.name));
	toonie->codec.owner = THIS_MODULE;
	toonie->codec.init = toonie_init_codec;
	toonie->codec.निकास = toonie_निकास_codec;

	अगर (aoa_codec_रेजिस्टर(&toonie->codec)) अणु
		kमुक्त(toonie);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास toonie_निकास(व्योम)
अणु
	aoa_codec_unरेजिस्टर(&toonie->codec);
	kमुक्त(toonie);
पूर्ण

module_init(toonie_init);
module_निकास(toonie_निकास);
