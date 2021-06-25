<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * media.c - Media Controller specअगरic ALSA driver code
 *
 * Copyright (c) 2019 Shuah Khan <shuah@kernel.org>
 *
 */

/*
 * This file adds Media Controller support to the ALSA driver
 * to use the Media Controller API to share the tuner with DVB
 * and V4L2 drivers that control the media device.
 *
 * The media device is created based on the existing quirks framework.
 * Using this approach, the media controller API usage can be added क्रम
 * a specअगरic device.
 */

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश <sound/pcm.h>
#समावेश <sound/core.h>

#समावेश "usbaudio.h"
#समावेश "card.h"
#समावेश "mixer.h"
#समावेश "media.h"

पूर्णांक snd_media_stream_init(काष्ठा snd_usb_substream *subs, काष्ठा snd_pcm *pcm,
			  पूर्णांक stream)
अणु
	काष्ठा media_device *mdev;
	काष्ठा media_ctl *mctl;
	काष्ठा device *pcm_dev = &pcm->streams[stream].dev;
	u32 पूर्णांकf_type;
	पूर्णांक ret = 0;
	u16 mixer_pad;
	काष्ठा media_entity *entity;

	mdev = subs->stream->chip->media_dev;
	अगर (!mdev)
		वापस 0;

	अगर (subs->media_ctl)
		वापस 0;

	/* allocate media_ctl */
	mctl = kzalloc(माप(*mctl), GFP_KERNEL);
	अगर (!mctl)
		वापस -ENOMEM;

	mctl->media_dev = mdev;
	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		पूर्णांकf_type = MEDIA_INTF_T_ALSA_PCM_PLAYBACK;
		mctl->media_entity.function = MEDIA_ENT_F_AUDIO_PLAYBACK;
		mctl->media_pad.flags = MEDIA_PAD_FL_SOURCE;
		mixer_pad = 1;
	पूर्ण अन्यथा अणु
		पूर्णांकf_type = MEDIA_INTF_T_ALSA_PCM_CAPTURE;
		mctl->media_entity.function = MEDIA_ENT_F_AUDIO_CAPTURE;
		mctl->media_pad.flags = MEDIA_PAD_FL_SINK;
		mixer_pad = 2;
	पूर्ण
	mctl->media_entity.name = pcm->name;
	media_entity_pads_init(&mctl->media_entity, 1, &mctl->media_pad);
	ret =  media_device_रेजिस्टर_entity(mctl->media_dev,
					    &mctl->media_entity);
	अगर (ret)
		जाओ मुक्त_mctl;

	mctl->पूर्णांकf_devnode = media_devnode_create(mdev, पूर्णांकf_type, 0,
						  MAJOR(pcm_dev->devt),
						  MINOR(pcm_dev->devt));
	अगर (!mctl->पूर्णांकf_devnode) अणु
		ret = -ENOMEM;
		जाओ unरेजिस्टर_entity;
	पूर्ण
	mctl->पूर्णांकf_link = media_create_पूर्णांकf_link(&mctl->media_entity,
						 &mctl->पूर्णांकf_devnode->पूर्णांकf,
						 MEDIA_LNK_FL_ENABLED);
	अगर (!mctl->पूर्णांकf_link) अणु
		ret = -ENOMEM;
		जाओ devnode_हटाओ;
	पूर्ण

	/* create link between mixer and audio */
	media_device_क्रम_each_entity(entity, mdev) अणु
		चयन (entity->function) अणु
		हाल MEDIA_ENT_F_AUDIO_MIXER:
			ret = media_create_pad_link(entity, mixer_pad,
						    &mctl->media_entity, 0,
						    MEDIA_LNK_FL_ENABLED);
			अगर (ret)
				जाओ हटाओ_पूर्णांकf_link;
			अवरोध;
		पूर्ण
	पूर्ण

	subs->media_ctl = mctl;
	वापस 0;

हटाओ_पूर्णांकf_link:
	media_हटाओ_पूर्णांकf_link(mctl->पूर्णांकf_link);
devnode_हटाओ:
	media_devnode_हटाओ(mctl->पूर्णांकf_devnode);
unरेजिस्टर_entity:
	media_device_unरेजिस्टर_entity(&mctl->media_entity);
मुक्त_mctl:
	kमुक्त(mctl);
	वापस ret;
पूर्ण

व्योम snd_media_stream_delete(काष्ठा snd_usb_substream *subs)
अणु
	काष्ठा media_ctl *mctl = subs->media_ctl;

	अगर (mctl) अणु
		काष्ठा media_device *mdev;

		mdev = mctl->media_dev;
		अगर (mdev && media_devnode_is_रेजिस्टरed(mdev->devnode)) अणु
			media_devnode_हटाओ(mctl->पूर्णांकf_devnode);
			media_device_unरेजिस्टर_entity(&mctl->media_entity);
			media_entity_cleanup(&mctl->media_entity);
		पूर्ण
		kमुक्त(mctl);
		subs->media_ctl = शून्य;
	पूर्ण
पूर्ण

पूर्णांक snd_media_start_pipeline(काष्ठा snd_usb_substream *subs)
अणु
	काष्ठा media_ctl *mctl = subs->media_ctl;
	पूर्णांक ret = 0;

	अगर (!mctl)
		वापस 0;

	mutex_lock(&mctl->media_dev->graph_mutex);
	अगर (mctl->media_dev->enable_source)
		ret = mctl->media_dev->enable_source(&mctl->media_entity,
						     &mctl->media_pipe);
	mutex_unlock(&mctl->media_dev->graph_mutex);
	वापस ret;
पूर्ण

व्योम snd_media_stop_pipeline(काष्ठा snd_usb_substream *subs)
अणु
	काष्ठा media_ctl *mctl = subs->media_ctl;

	अगर (!mctl)
		वापस;

	mutex_lock(&mctl->media_dev->graph_mutex);
	अगर (mctl->media_dev->disable_source)
		mctl->media_dev->disable_source(&mctl->media_entity);
	mutex_unlock(&mctl->media_dev->graph_mutex);
पूर्ण

अटल पूर्णांक snd_media_mixer_init(काष्ठा snd_usb_audio *chip)
अणु
	काष्ठा device *ctl_dev = &chip->card->ctl_dev;
	काष्ठा media_पूर्णांकf_devnode *ctl_पूर्णांकf;
	काष्ठा usb_mixer_पूर्णांकerface *mixer;
	काष्ठा media_device *mdev = chip->media_dev;
	काष्ठा media_mixer_ctl *mctl;
	u32 पूर्णांकf_type = MEDIA_INTF_T_ALSA_CONTROL;
	पूर्णांक ret;

	अगर (!mdev)
		वापस -ENODEV;

	ctl_पूर्णांकf = chip->ctl_पूर्णांकf_media_devnode;
	अगर (!ctl_पूर्णांकf) अणु
		ctl_पूर्णांकf = media_devnode_create(mdev, पूर्णांकf_type, 0,
						MAJOR(ctl_dev->devt),
						MINOR(ctl_dev->devt));
		अगर (!ctl_पूर्णांकf)
			वापस -ENOMEM;
		chip->ctl_पूर्णांकf_media_devnode = ctl_पूर्णांकf;
	पूर्ण

	list_क्रम_each_entry(mixer, &chip->mixer_list, list) अणु

		अगर (mixer->media_mixer_ctl)
			जारी;

		/* allocate media_mixer_ctl */
		mctl = kzalloc(माप(*mctl), GFP_KERNEL);
		अगर (!mctl)
			वापस -ENOMEM;

		mctl->media_dev = mdev;
		mctl->media_entity.function = MEDIA_ENT_F_AUDIO_MIXER;
		mctl->media_entity.name = chip->card->mixername;
		mctl->media_pad[0].flags = MEDIA_PAD_FL_SINK;
		mctl->media_pad[1].flags = MEDIA_PAD_FL_SOURCE;
		mctl->media_pad[2].flags = MEDIA_PAD_FL_SOURCE;
		media_entity_pads_init(&mctl->media_entity, MEDIA_MIXER_PAD_MAX,
				  mctl->media_pad);
		ret =  media_device_रेजिस्टर_entity(mctl->media_dev,
						    &mctl->media_entity);
		अगर (ret) अणु
			kमुक्त(mctl);
			वापस ret;
		पूर्ण

		mctl->पूर्णांकf_link = media_create_पूर्णांकf_link(&mctl->media_entity,
							 &ctl_पूर्णांकf->पूर्णांकf,
							 MEDIA_LNK_FL_ENABLED);
		अगर (!mctl->पूर्णांकf_link) अणु
			media_device_unरेजिस्टर_entity(&mctl->media_entity);
			media_entity_cleanup(&mctl->media_entity);
			kमुक्त(mctl);
			वापस -ENOMEM;
		पूर्ण
		mctl->पूर्णांकf_devnode = ctl_पूर्णांकf;
		mixer->media_mixer_ctl = mctl;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_media_mixer_delete(काष्ठा snd_usb_audio *chip)
अणु
	काष्ठा usb_mixer_पूर्णांकerface *mixer;
	काष्ठा media_device *mdev = chip->media_dev;

	अगर (!mdev)
		वापस;

	list_क्रम_each_entry(mixer, &chip->mixer_list, list) अणु
		काष्ठा media_mixer_ctl *mctl;

		mctl = mixer->media_mixer_ctl;
		अगर (!mixer->media_mixer_ctl)
			जारी;

		अगर (media_devnode_is_रेजिस्टरed(mdev->devnode)) अणु
			media_device_unरेजिस्टर_entity(&mctl->media_entity);
			media_entity_cleanup(&mctl->media_entity);
		पूर्ण
		kमुक्त(mctl);
		mixer->media_mixer_ctl = शून्य;
	पूर्ण
	अगर (media_devnode_is_रेजिस्टरed(mdev->devnode))
		media_devnode_हटाओ(chip->ctl_पूर्णांकf_media_devnode);
	chip->ctl_पूर्णांकf_media_devnode = शून्य;
पूर्ण

पूर्णांक snd_media_device_create(काष्ठा snd_usb_audio *chip,
			काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	काष्ठा media_device *mdev;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(अगरace);
	पूर्णांक ret = 0;

	/* usb-audio driver is probed क्रम each usb पूर्णांकerface, and
	 * there are multiple पूर्णांकerfaces per device. Aव्योम calling
	 * media_device_usb_allocate() each समय usb_audio_probe()
	 * is called. Do it only once.
	 */
	अगर (chip->media_dev) अणु
		mdev = chip->media_dev;
		जाओ snd_mixer_init;
	पूर्ण

	mdev = media_device_usb_allocate(usbdev, KBUILD_MODNAME, THIS_MODULE);
	अगर (IS_ERR(mdev))
		वापस -ENOMEM;

	/* save media device - aव्योम lookups */
	chip->media_dev = mdev;

snd_mixer_init:
	/* Create media entities क्रम mixer and control dev */
	ret = snd_media_mixer_init(chip);
	/* media_device might be रेजिस्टरed, prपूर्णांक error and जारी */
	अगर (ret)
		dev_err(&usbdev->dev,
			"Couldn't create media mixer entities. Error: %d\n",
			ret);

	अगर (!media_devnode_is_रेजिस्टरed(mdev->devnode)) अणु
		/* करोnt'रेजिस्टर अगर snd_media_mixer_init() failed */
		अगर (ret)
			जाओ create_fail;

		/* रेजिस्टर media_device */
		ret = media_device_रेजिस्टर(mdev);
create_fail:
		अगर (ret) अणु
			snd_media_mixer_delete(chip);
			media_device_delete(mdev, KBUILD_MODNAME, THIS_MODULE);
			/* clear saved media_dev */
			chip->media_dev = शून्य;
			dev_err(&usbdev->dev,
				"Couldn't register media device. Error: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम snd_media_device_delete(काष्ठा snd_usb_audio *chip)
अणु
	काष्ठा media_device *mdev = chip->media_dev;
	काष्ठा snd_usb_stream *stream;

	/* release resources */
	list_क्रम_each_entry(stream, &chip->pcm_list, list) अणु
		snd_media_stream_delete(&stream->substream[0]);
		snd_media_stream_delete(&stream->substream[1]);
	पूर्ण

	snd_media_mixer_delete(chip);

	अगर (mdev) अणु
		media_device_delete(mdev, KBUILD_MODNAME, THIS_MODULE);
		chip->media_dev = शून्य;
	पूर्ण
पूर्ण
