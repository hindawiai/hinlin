<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Empiatech em28x1 audio extension
//
// Copyright (C) 2006 Markus Rechberger <mrechberger@gmail.com>
//
// Copyright (C) 2007-2016 Mauro Carvalho Chehab
//	- Port to work with the in-kernel driver
//	- Cleanups, fixes, alsa-controls, etc.
//
// This driver is based on my previous au600 usb pstn audio driver
// and inherits all the copyrights
//
// This program is मुक्त software; you can redistribute it and/or modअगरy
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License क्रम more details.

#समावेश "em28xx.h"

#समावेश <linux/kernel.h>
#समावेश <linux/usb.h>
#समावेश <linux/init.h>
#समावेश <linux/sound.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/soundcard.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/info.h>
#समावेश <sound/initval.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश <sound/ac97_codec.h>
#समावेश <media/v4l2-common.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "activates debug info");

#घोषणा EM28XX_MAX_AUDIO_BUFS		5
#घोषणा EM28XX_MIN_AUDIO_PACKETS	64

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)						\
		dev_prपूर्णांकk(KERN_DEBUG, &dev->पूर्णांकf->dev,			\
			   "video: %s: " fmt, __func__, ## arg);	\
पूर्ण जबतक (0)

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;

अटल पूर्णांक em28xx_deinit_isoc_audio(काष्ठा em28xx *dev)
अणु
	पूर्णांक i;

	dprपूर्णांकk("Stopping isoc\n");
	क्रम (i = 0; i < dev->adev.num_urb; i++) अणु
		काष्ठा urb *urb = dev->adev.urb[i];

		अगर (!irqs_disabled())
			usb_समाप्त_urb(urb);
		अन्यथा
			usb_unlink_urb(urb);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम em28xx_audio_isocirq(काष्ठा urb *urb)
अणु
	काष्ठा em28xx            *dev = urb->context;
	पूर्णांक                      i;
	अचिन्हित पूर्णांक             oldptr;
	पूर्णांक                      period_elapsed = 0;
	पूर्णांक                      status;
	अचिन्हित अक्षर            *cp;
	अचिन्हित पूर्णांक             stride;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय   *runसमय;

	अगर (dev->disconnected) अणु
		dprपूर्णांकk("device disconnected while streaming. URB status=%d.\n",
			urb->status);
		atomic_set(&dev->adev.stream_started, 0);
		वापस;
	पूर्ण

	चयन (urb->status) अणु
	हाल 0:             /* success */
	हाल -ETIMEDOUT:    /* NAK */
		अवरोध;
	हाल -ECONNRESET:   /* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:            /* error */
		dprपूर्णांकk("urb completion error %d.\n", urb->status);
		अवरोध;
	पूर्ण

	अगर (atomic_पढ़ो(&dev->adev.stream_started) == 0)
		वापस;

	अगर (dev->adev.capture_pcm_substream) अणु
		substream = dev->adev.capture_pcm_substream;
		runसमय = substream->runसमय;
		stride = runसमय->frame_bits >> 3;

		क्रम (i = 0; i < urb->number_of_packets; i++) अणु
			अचिन्हित दीर्घ flags;
			पूर्णांक length =
			    urb->iso_frame_desc[i].actual_length / stride;
			cp = (अचिन्हित अक्षर *)urb->transfer_buffer +
			    urb->iso_frame_desc[i].offset;

			अगर (!length)
				जारी;

			oldptr = dev->adev.hwptr_करोne_capture;
			अगर (oldptr + length >= runसमय->buffer_size) अणु
				अचिन्हित पूर्णांक cnt =
				    runसमय->buffer_size - oldptr;
				स_नकल(runसमय->dma_area + oldptr * stride, cp,
				       cnt * stride);
				स_नकल(runसमय->dma_area, cp + cnt * stride,
				       length * stride - cnt * stride);
			पूर्ण अन्यथा अणु
				स_नकल(runसमय->dma_area + oldptr * stride, cp,
				       length * stride);
			पूर्ण

			snd_pcm_stream_lock_irqsave(substream, flags);

			dev->adev.hwptr_करोne_capture += length;
			अगर (dev->adev.hwptr_करोne_capture >=
			    runसमय->buffer_size)
				dev->adev.hwptr_करोne_capture -=
				    runसमय->buffer_size;

			dev->adev.capture_transfer_करोne += length;
			अगर (dev->adev.capture_transfer_करोne >=
			    runसमय->period_size) अणु
				dev->adev.capture_transfer_करोne -=
				    runसमय->period_size;
				period_elapsed = 1;
			पूर्ण

			snd_pcm_stream_unlock_irqrestore(substream, flags);
		पूर्ण
		अगर (period_elapsed)
			snd_pcm_period_elapsed(substream);
	पूर्ण
	urb->status = 0;

	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status < 0)
		dev_err(&dev->पूर्णांकf->dev,
			"resubmit of audio urb failed (error=%i)\n",
			status);
पूर्ण

अटल पूर्णांक em28xx_init_audio_isoc(काष्ठा em28xx *dev)
अणु
	पूर्णांक       i, err;

	dprपूर्णांकk("Starting isoc transfers\n");

	/* Start streaming */
	क्रम (i = 0; i < dev->adev.num_urb; i++) अणु
		स_रखो(dev->adev.transfer_buffer[i], 0x80,
		       dev->adev.urb[i]->transfer_buffer_length);

		err = usb_submit_urb(dev->adev.urb[i], GFP_ATOMIC);
		अगर (err) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"submit of audio urb failed (error=%i)\n",
				err);
			em28xx_deinit_isoc_audio(dev);
			atomic_set(&dev->adev.stream_started, 0);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_em28xx_hw_capture = अणु
	.info = SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP           |
		SNDRV_PCM_INFO_INTERLEAVED    |
		SNDRV_PCM_INFO_BATCH	      |
		SNDRV_PCM_INFO_MMAP_VALID,

	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,

	.rates = SNDRV_PCM_RATE_48000,

	.rate_min = 48000,
	.rate_max = 48000,
	.channels_min = 2,
	.channels_max = 2,
	.buffer_bytes_max = 62720 * 8,	/* just about the value in usbaudio.c */

	/*
	 * The period is 12.288 bytes. Allow a 10% of variation aदीर्घ its
	 * value, in order to aव्योम overruns/underruns due to some घड़ी
	 * drअगरt.
	 *
	 * FIXME: This period assumes 64 packets, and a 48000 PCM rate.
	 * Calculate it dynamically.
	 */
	.period_bytes_min = 11059,
	.period_bytes_max = 13516,

	.periods_min = 2,
	.periods_max = 98,		/* 12544, */
पूर्ण;

अटल पूर्णांक snd_em28xx_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा em28xx *dev = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक nonblock, ret = 0;

	अगर (!dev) अणु
		pr_err("em28xx-audio: BUG: em28xx can't find device struct. Can't proceed with open\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dev->disconnected)
		वापस -ENODEV;

	dprपूर्णांकk("opening device and trying to acquire exclusive lock\n");

	nonblock = !!(substream->f_flags & O_NONBLOCK);
	अगर (nonblock) अणु
		अगर (!mutex_trylock(&dev->lock))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		mutex_lock(&dev->lock);
	पूर्ण

	runसमय->hw = snd_em28xx_hw_capture;

	अगर (dev->adev.users == 0) अणु
		अगर (!dev->alt || dev->is_audio_only) अणु
			काष्ठा usb_device *udev;

			udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);

			अगर (dev->is_audio_only)
				/* audio is on a separate पूर्णांकerface */
				dev->alt = 1;
			अन्यथा
				/* audio is on the same पूर्णांकerface as video */
				dev->alt = 7;
				/*
				 * FIXME: The पूर्णांकention seems to be to select
				 * the alt setting with the largest
				 * wMaxPacketSize क्रम the video endpoपूर्णांक.
				 * At least dev->alt should be used instead, but
				 * we should probably not touch it at all अगर it
				 * is alपढ़ोy >0, because wMaxPacketSize of the
				 * audio endpoपूर्णांकs seems to be the same क्रम all.
				 */
			dprपूर्णांकk("changing alternate number on interface %d to %d\n",
				dev->अगरnum, dev->alt);
			usb_set_पूर्णांकerface(udev, dev->अगरnum, dev->alt);
		पूर्ण

		/* Sets volume, mute, etc */
		dev->mute = 0;
		ret = em28xx_audio_analog_set(dev);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	kref_get(&dev->ref);
	dev->adev.users++;
	mutex_unlock(&dev->lock);

	/* Dynamically adjust the period size */
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
				     dev->adev.period * 95 / 100,
				     dev->adev.period * 105 / 100);

	dev->adev.capture_pcm_substream = substream;

	वापस 0;
err:
	mutex_unlock(&dev->lock);

	dev_err(&dev->पूर्णांकf->dev,
		"Error while configuring em28xx mixer\n");
	वापस ret;
पूर्ण

अटल पूर्णांक snd_em28xx_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा em28xx *dev = snd_pcm_substream_chip(substream);

	dprपूर्णांकk("closing device\n");

	dev->mute = 1;
	mutex_lock(&dev->lock);
	dev->adev.users--;
	अगर (atomic_पढ़ो(&dev->adev.stream_started) > 0) अणु
		atomic_set(&dev->adev.stream_started, 0);
		schedule_work(&dev->adev.wq_trigger);
	पूर्ण

	em28xx_audio_analog_set(dev);
	mutex_unlock(&dev->lock);
	kref_put(&dev->ref, em28xx_मुक्त_device);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_em28xx_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा em28xx *dev = snd_pcm_substream_chip(substream);

	अगर (dev->disconnected)
		वापस -ENODEV;

	dev->adev.hwptr_करोne_capture = 0;
	dev->adev.capture_transfer_करोne = 0;

	वापस 0;
पूर्ण

अटल व्योम audio_trigger(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा em28xx_audio *adev =
			    container_of(work, काष्ठा em28xx_audio, wq_trigger);
	काष्ठा em28xx *dev = container_of(adev, काष्ठा em28xx, adev);

	अगर (atomic_पढ़ो(&adev->stream_started)) अणु
		dprपूर्णांकk("starting capture");
		em28xx_init_audio_isoc(dev);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("stopping capture");
		em28xx_deinit_isoc_audio(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_em28xx_capture_trigger(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक cmd)
अणु
	काष्ठा em28xx *dev = snd_pcm_substream_chip(substream);
	पूर्णांक retval = 0;

	अगर (dev->disconnected)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_START:
		atomic_set(&dev->adev.stream_started, 1);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		atomic_set(&dev->adev.stream_started, 0);
		अवरोध;
	शेष:
		retval = -EINVAL;
	पूर्ण
	schedule_work(&dev->adev.wq_trigger);
	वापस retval;
पूर्ण

अटल snd_pcm_uframes_t snd_em28xx_capture_poपूर्णांकer(काष्ठा snd_pcm_substream
						    *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा em28xx *dev;
	snd_pcm_uframes_t hwptr_करोne;

	dev = snd_pcm_substream_chip(substream);
	अगर (dev->disconnected)
		वापस SNDRV_PCM_POS_XRUN;

	spin_lock_irqsave(&dev->adev.slock, flags);
	hwptr_करोne = dev->adev.hwptr_करोne_capture;
	spin_unlock_irqrestore(&dev->adev.slock, flags);

	वापस hwptr_करोne;
पूर्ण

/*
 * AC97 volume control support
 */
अटल पूर्णांक em28xx_vol_info(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_info *info)
अणु
	काष्ठा em28xx *dev = snd_kcontrol_chip(kcontrol);

	अगर (dev->disconnected)
		वापस -ENODEV;

	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = 2;
	info->value.पूर्णांकeger.min = 0;
	info->value.पूर्णांकeger.max = 0x1f;

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_vol_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा em28xx *dev = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_pcm_substream *substream = dev->adev.capture_pcm_substream;
	u16 val = (0x1f - (value->value.पूर्णांकeger.value[0] & 0x1f)) |
		  (0x1f - (value->value.पूर्णांकeger.value[1] & 0x1f)) << 8;
	पूर्णांक nonblock = 0;
	पूर्णांक rc;

	अगर (dev->disconnected)
		वापस -ENODEV;

	अगर (substream)
		nonblock = !!(substream->f_flags & O_NONBLOCK);
	अगर (nonblock) अणु
		अगर (!mutex_trylock(&dev->lock))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		mutex_lock(&dev->lock);
	पूर्ण
	rc = em28xx_पढ़ो_ac97(dev, kcontrol->निजी_value);
	अगर (rc < 0)
		जाओ err;

	val |= rc & 0x8000;	/* Preserve the mute flag */

	rc = em28xx_ग_लिखो_ac97(dev, kcontrol->निजी_value, val);
	अगर (rc < 0)
		जाओ err;

	dprपूर्णांकk("%sleft vol %d, right vol %d (0x%04x) to ac97 volume control 0x%04x\n",
		(val & 0x8000) ? "muted " : "",
		0x1f - ((val >> 8) & 0x1f), 0x1f - (val & 0x1f),
		val, (पूर्णांक)kcontrol->निजी_value);

err:
	mutex_unlock(&dev->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक em28xx_vol_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा em28xx *dev = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_pcm_substream *substream = dev->adev.capture_pcm_substream;
	पूर्णांक nonblock = 0;
	पूर्णांक val;

	अगर (dev->disconnected)
		वापस -ENODEV;

	अगर (substream)
		nonblock = !!(substream->f_flags & O_NONBLOCK);
	अगर (nonblock) अणु
		अगर (!mutex_trylock(&dev->lock))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		mutex_lock(&dev->lock);
	पूर्ण
	val = em28xx_पढ़ो_ac97(dev, kcontrol->निजी_value);
	mutex_unlock(&dev->lock);
	अगर (val < 0)
		वापस val;

	dprपूर्णांकk("%sleft vol %d, right vol %d (0x%04x) from ac97 volume control 0x%04x\n",
		(val & 0x8000) ? "muted " : "",
		0x1f - ((val >> 8) & 0x1f), 0x1f - (val & 0x1f),
		val, (पूर्णांक)kcontrol->निजी_value);

	value->value.पूर्णांकeger.value[0] = 0x1f - (val & 0x1f);
	value->value.पूर्णांकeger.value[1] = 0x1f - ((val >> 8) & 0x1f);

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_vol_put_mute(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा em28xx *dev = snd_kcontrol_chip(kcontrol);
	u16 val = value->value.पूर्णांकeger.value[0];
	काष्ठा snd_pcm_substream *substream = dev->adev.capture_pcm_substream;
	पूर्णांक nonblock = 0;
	पूर्णांक rc;

	अगर (dev->disconnected)
		वापस -ENODEV;

	अगर (substream)
		nonblock = !!(substream->f_flags & O_NONBLOCK);
	अगर (nonblock) अणु
		अगर (!mutex_trylock(&dev->lock))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		mutex_lock(&dev->lock);
	पूर्ण
	rc = em28xx_पढ़ो_ac97(dev, kcontrol->निजी_value);
	अगर (rc < 0)
		जाओ err;

	अगर (val)
		rc &= 0x1f1f;
	अन्यथा
		rc |= 0x8000;

	rc = em28xx_ग_लिखो_ac97(dev, kcontrol->निजी_value, rc);
	अगर (rc < 0)
		जाओ err;

	dprपूर्णांकk("%sleft vol %d, right vol %d (0x%04x) to ac97 volume control 0x%04x\n",
		(val & 0x8000) ? "muted " : "",
		0x1f - ((val >> 8) & 0x1f), 0x1f - (val & 0x1f),
		val, (पूर्णांक)kcontrol->निजी_value);

err:
	mutex_unlock(&dev->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक em28xx_vol_get_mute(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा em28xx *dev = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_pcm_substream *substream = dev->adev.capture_pcm_substream;
	पूर्णांक nonblock = 0;
	पूर्णांक val;

	अगर (dev->disconnected)
		वापस -ENODEV;

	अगर (substream)
		nonblock = !!(substream->f_flags & O_NONBLOCK);
	अगर (nonblock) अणु
		अगर (!mutex_trylock(&dev->lock))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		mutex_lock(&dev->lock);
	पूर्ण
	val = em28xx_पढ़ो_ac97(dev, kcontrol->निजी_value);
	mutex_unlock(&dev->lock);
	अगर (val < 0)
		वापस val;

	अगर (val & 0x8000)
		value->value.पूर्णांकeger.value[0] = 0;
	अन्यथा
		value->value.पूर्णांकeger.value[0] = 1;

	dprपूर्णांकk("%sleft vol %d, right vol %d (0x%04x) from ac97 volume control 0x%04x\n",
		(val & 0x8000) ? "muted " : "",
		0x1f - ((val >> 8) & 0x1f), 0x1f - (val & 0x1f),
		val, (पूर्णांक)kcontrol->निजी_value);

	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(em28xx_db_scale, -3450, 150, 0);

अटल पूर्णांक em28xx_cvol_new(काष्ठा snd_card *card, काष्ठा em28xx *dev,
			   अक्षर *name, पूर्णांक id)
अणु
	पूर्णांक err;
	अक्षर ctl_name[44];
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_kcontrol_new पंचांगp;

	स_रखो(&पंचांगp, 0, माप(पंचांगp));
	पंचांगp.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	पंचांगp.निजी_value = id;
	पंचांगp.name  = ctl_name;

	/* Add Mute Control */
	प्र_लिखो(ctl_name, "%s Switch", name);
	पंचांगp.get  = em28xx_vol_get_mute;
	पंचांगp.put  = em28xx_vol_put_mute;
	पंचांगp.info = snd_ctl_boolean_mono_info;
	kctl = snd_ctl_new1(&पंचांगp, dev);
	err = snd_ctl_add(card, kctl);
	अगर (err < 0)
		वापस err;
	dprपूर्णांकk("Added control %s for ac97 volume control 0x%04x\n",
		ctl_name, id);

	स_रखो(&पंचांगp, 0, माप(पंचांगp));
	पंचांगp.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	पंचांगp.निजी_value = id;
	पंचांगp.name  = ctl_name;

	/* Add Volume Control */
	प्र_लिखो(ctl_name, "%s Volume", name);
	पंचांगp.get   = em28xx_vol_get;
	पंचांगp.put   = em28xx_vol_put;
	पंचांगp.info  = em28xx_vol_info;
	पंचांगp.tlv.p = em28xx_db_scale;
	kctl = snd_ctl_new1(&पंचांगp, dev);
	err = snd_ctl_add(card, kctl);
	अगर (err < 0)
		वापस err;
	dprपूर्णांकk("Added control %s for ac97 volume control 0x%04x\n",
		ctl_name, id);

	वापस 0;
पूर्ण

/*
 * रेजिस्टर/unरेजिस्टर code and data
 */
अटल स्थिर काष्ठा snd_pcm_ops snd_em28xx_pcm_capture = अणु
	.खोलो      = snd_em28xx_capture_खोलो,
	.बंद     = snd_em28xx_pcm_बंद,
	.prepare   = snd_em28xx_prepare,
	.trigger   = snd_em28xx_capture_trigger,
	.poपूर्णांकer   = snd_em28xx_capture_poपूर्णांकer,
पूर्ण;

अटल व्योम em28xx_audio_मुक्त_urb(काष्ठा em28xx *dev)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	पूर्णांक i;

	क्रम (i = 0; i < dev->adev.num_urb; i++) अणु
		काष्ठा urb *urb = dev->adev.urb[i];

		अगर (!urb)
			जारी;

		usb_मुक्त_coherent(udev, urb->transfer_buffer_length,
				  dev->adev.transfer_buffer[i],
				  urb->transfer_dma);

		usb_मुक्त_urb(urb);
	पूर्ण
	kमुक्त(dev->adev.urb);
	kमुक्त(dev->adev.transfer_buffer);
	dev->adev.num_urb = 0;
पूर्ण

/* high bandwidth multiplier, as encoded in highspeed endpoपूर्णांक descriptors */
अटल पूर्णांक em28xx_audio_ep_packet_size(काष्ठा usb_device *udev,
				       काष्ठा usb_endpoपूर्णांक_descriptor *e)
अणु
	पूर्णांक size = le16_to_cpu(e->wMaxPacketSize);

	अगर (udev->speed == USB_SPEED_HIGH)
		वापस (size & 0x7ff) *  (1 + (((size) >> 11) & 0x03));

	वापस size & 0x7ff;
पूर्ण

अटल पूर्णांक em28xx_audio_urb_init(काष्ठा em28xx *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_endpoपूर्णांक_descriptor *e, *ep = शून्य;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	पूर्णांक                 i, ep_size, पूर्णांकerval, num_urb, npackets;
	पूर्णांक		    urb_size, bytes_per_transfer;
	u8 alt;

	अगर (dev->अगरnum)
		alt = 1;
	अन्यथा
		alt = 7;

	पूर्णांकf = usb_अगरnum_to_अगर(udev, dev->अगरnum);

	अगर (पूर्णांकf->num_altsetting <= alt) अणु
		dev_err(&dev->पूर्णांकf->dev, "alt %d doesn't exist on interface %d\n",
			dev->अगरnum, alt);
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < पूर्णांकf->altsetting[alt].desc.bNumEndpoपूर्णांकs; i++) अणु
		e = &पूर्णांकf->altsetting[alt].endpoपूर्णांक[i].desc;
		अगर (!usb_endpoपूर्णांक_dir_in(e))
			जारी;
		अगर (e->bEndpoपूर्णांकAddress == EM28XX_EP_AUDIO) अणु
			ep = e;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ep) अणु
		dev_err(&dev->पूर्णांकf->dev, "Couldn't find an audio endpoint");
		वापस -ENODEV;
	पूर्ण

	ep_size = em28xx_audio_ep_packet_size(udev, ep);
	पूर्णांकerval = 1 << (ep->bInterval - 1);

	dev_info(&dev->पूर्णांकf->dev,
		 "Endpoint 0x%02x %s on intf %d alt %d interval = %d, size %d\n",
		 EM28XX_EP_AUDIO, usb_speed_string(udev->speed),
		 dev->अगरnum, alt, पूर्णांकerval, ep_size);

	/* Calculate the number and size of URBs to better fit the audio samples */

	/*
	 * Estimate the number of bytes per DMA transfer.
	 *
	 * This is given by the bit rate (क्रम now, only 48000 Hz) multiplied
	 * by 2 channels and 2 bytes/sample भागided by the number of microframe
	 * पूर्णांकervals and by the microframe rate (125 us)
	 */
	bytes_per_transfer = DIV_ROUND_UP(48000 * 2 * 2, 125 * पूर्णांकerval);

	/*
	 * Estimate the number of transfer URBs. Don't let it go past the
	 * maximum number of URBs that is known to be supported by the device.
	 */
	num_urb = DIV_ROUND_UP(bytes_per_transfer, ep_size);
	अगर (num_urb > EM28XX_MAX_AUDIO_BUFS)
		num_urb = EM28XX_MAX_AUDIO_BUFS;

	/*
	 * Now that we know the number of bytes per transfer and the number of
	 * URBs, estimate the typical size of an URB, in order to adjust the
	 * minimal number of packets.
	 */
	urb_size = bytes_per_transfer / num_urb;

	/*
	 * Now, calculate the amount of audio packets to be filled on each
	 * URB. In order to preserve the old behaviour, use a minimal
	 * threshold क्रम this value.
	 */
	npackets = EM28XX_MIN_AUDIO_PACKETS;
	अगर (urb_size > ep_size * npackets)
		npackets = DIV_ROUND_UP(urb_size, ep_size);

	dev_info(&dev->पूर्णांकf->dev,
		 "Number of URBs: %d, with %d packets and %d size\n",
		 num_urb, npackets, urb_size);

	/* Estimate the bytes per period */
	dev->adev.period = urb_size * npackets;

	/* Allocate space to store the number of URBs to be used */

	dev->adev.transfer_buffer = kसुस्मृति(num_urb,
					    माप(*dev->adev.transfer_buffer),
					    GFP_KERNEL);
	अगर (!dev->adev.transfer_buffer)
		वापस -ENOMEM;

	dev->adev.urb = kसुस्मृति(num_urb, माप(*dev->adev.urb), GFP_KERNEL);
	अगर (!dev->adev.urb) अणु
		kमुक्त(dev->adev.transfer_buffer);
		वापस -ENOMEM;
	पूर्ण

	/* Alloc memory क्रम each URB and क्रम each transfer buffer */
	dev->adev.num_urb = num_urb;
	क्रम (i = 0; i < num_urb; i++) अणु
		काष्ठा urb *urb;
		पूर्णांक j, k;
		व्योम *buf;

		urb = usb_alloc_urb(npackets, GFP_KERNEL);
		अगर (!urb) अणु
			em28xx_audio_मुक्त_urb(dev);
			वापस -ENOMEM;
		पूर्ण
		dev->adev.urb[i] = urb;

		buf = usb_alloc_coherent(udev, npackets * ep_size, GFP_KERNEL,
					 &urb->transfer_dma);
		अगर (!buf) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"usb_alloc_coherent failed!\n");
			em28xx_audio_मुक्त_urb(dev);
			वापस -ENOMEM;
		पूर्ण
		dev->adev.transfer_buffer[i] = buf;

		urb->dev = udev;
		urb->context = dev;
		urb->pipe = usb_rcvisocpipe(udev, EM28XX_EP_AUDIO);
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
		urb->transfer_buffer = buf;
		urb->पूर्णांकerval = पूर्णांकerval;
		urb->complete = em28xx_audio_isocirq;
		urb->number_of_packets = npackets;
		urb->transfer_buffer_length = ep_size * npackets;

		क्रम (j = k = 0; j < npackets; j++, k += ep_size) अणु
			urb->iso_frame_desc[j].offset = k;
			urb->iso_frame_desc[j].length = ep_size;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_audio_init(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_audio *adev = &dev->adev;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	काष्ठा snd_pcm      *pcm;
	काष्ठा snd_card     *card;
	अटल पूर्णांक          devnr;
	पूर्णांक		    err;

	अगर (dev->usb_audio_type != EM28XX_USB_AUDIO_VENDOR) अणु
		/*
		 * This device करोes not support the extension (in this हाल
		 * the device is expecting the snd-usb-audio module or
		 * करोesn't have analog audio support at all)
		 */
		वापस 0;
	पूर्ण

	dev_info(&dev->पूर्णांकf->dev, "Binding audio extension\n");

	kref_get(&dev->ref);

	dev_info(&dev->पूर्णांकf->dev,
		 "em28xx-audio.c: Copyright (C) 2006 Markus Rechberger\n");
	dev_info(&dev->पूर्णांकf->dev,
		 "em28xx-audio.c: Copyright (C) 2007-2016 Mauro Carvalho Chehab\n");

	err = snd_card_new(&dev->पूर्णांकf->dev, index[devnr], "Em28xx Audio",
			   THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	spin_lock_init(&adev->slock);
	adev->sndcard = card;
	adev->udev = udev;

	err = snd_pcm_new(card, "Em28xx Audio", 0, 0, 1, &pcm);
	अगर (err < 0)
		जाओ card_मुक्त;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_em28xx_pcm_capture);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);
	pcm->info_flags = 0;
	pcm->निजी_data = dev;
	strscpy(pcm->name, "Empia 28xx Capture", माप(pcm->name));

	strscpy(card->driver, "Em28xx-Audio", माप(card->driver));
	strscpy(card->लघुname, "Em28xx Audio", माप(card->लघुname));
	strscpy(card->दीर्घname, "Empia Em28xx Audio", माप(card->दीर्घname));

	INIT_WORK(&adev->wq_trigger, audio_trigger);

	अगर (dev->audio_mode.ac97 != EM28XX_NO_AC97) अणु
		em28xx_cvol_new(card, dev, "Video", AC97_VIDEO);
		em28xx_cvol_new(card, dev, "Line In", AC97_LINE);
		em28xx_cvol_new(card, dev, "Phone", AC97_PHONE);
		em28xx_cvol_new(card, dev, "Microphone", AC97_MIC);
		em28xx_cvol_new(card, dev, "CD", AC97_CD);
		em28xx_cvol_new(card, dev, "AUX", AC97_AUX);
		em28xx_cvol_new(card, dev, "PCM", AC97_PCM);

		em28xx_cvol_new(card, dev, "Master", AC97_MASTER);
		em28xx_cvol_new(card, dev, "Line", AC97_HEADPHONE);
		em28xx_cvol_new(card, dev, "Mono", AC97_MASTER_MONO);
		em28xx_cvol_new(card, dev, "LFE", AC97_CENTER_LFE_MASTER);
		em28xx_cvol_new(card, dev, "Surround", AC97_SURROUND_MASTER);
	पूर्ण

	err = em28xx_audio_urb_init(dev);
	अगर (err)
		जाओ card_मुक्त;

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ urb_मुक्त;

	dev_info(&dev->पूर्णांकf->dev, "Audio extension successfully initialized\n");
	वापस 0;

urb_मुक्त:
	em28xx_audio_मुक्त_urb(dev);

card_मुक्त:
	snd_card_मुक्त(card);
	adev->sndcard = शून्य;

	वापस err;
पूर्ण

अटल पूर्णांक em28xx_audio_fini(काष्ठा em28xx *dev)
अणु
	अगर (!dev)
		वापस 0;

	अगर (dev->usb_audio_type != EM28XX_USB_AUDIO_VENDOR) अणु
		/*
		 * This device करोes not support the extension (in this हाल
		 * the device is expecting the snd-usb-audio module or
		 * करोesn't have analog audio support at all)
		 */
		वापस 0;
	पूर्ण

	dev_info(&dev->पूर्णांकf->dev, "Closing audio extension\n");

	अगर (dev->adev.sndcard) अणु
		snd_card_disconnect(dev->adev.sndcard);
		flush_work(&dev->adev.wq_trigger);

		em28xx_audio_मुक्त_urb(dev);

		snd_card_मुक्त(dev->adev.sndcard);
		dev->adev.sndcard = शून्य;
	पूर्ण

	kref_put(&dev->ref, em28xx_मुक्त_device);
	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_audio_suspend(काष्ठा em28xx *dev)
अणु
	अगर (!dev)
		वापस 0;

	अगर (dev->usb_audio_type != EM28XX_USB_AUDIO_VENDOR)
		वापस 0;

	dev_info(&dev->पूर्णांकf->dev, "Suspending audio extension\n");
	em28xx_deinit_isoc_audio(dev);
	atomic_set(&dev->adev.stream_started, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_audio_resume(काष्ठा em28xx *dev)
अणु
	अगर (!dev)
		वापस 0;

	अगर (dev->usb_audio_type != EM28XX_USB_AUDIO_VENDOR)
		वापस 0;

	dev_info(&dev->पूर्णांकf->dev, "Resuming audio extension\n");
	/* Nothing to करो other than schedule_work() ?? */
	schedule_work(&dev->adev.wq_trigger);
	वापस 0;
पूर्ण

अटल काष्ठा em28xx_ops audio_ops = अणु
	.id   = EM28XX_AUDIO,
	.name = "Em28xx Audio Extension",
	.init = em28xx_audio_init,
	.fini = em28xx_audio_fini,
	.suspend = em28xx_audio_suspend,
	.resume = em28xx_audio_resume,
पूर्ण;

अटल पूर्णांक __init em28xx_alsa_रेजिस्टर(व्योम)
अणु
	वापस em28xx_रेजिस्टर_extension(&audio_ops);
पूर्ण

अटल व्योम __निकास em28xx_alsa_unरेजिस्टर(व्योम)
अणु
	em28xx_unरेजिस्टर_extension(&audio_ops);
पूर्ण

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Markus Rechberger <mrechberger@gmail.com>");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_DESCRIPTION(DRIVER_DESC " - audio interface");
MODULE_VERSION(EM28XX_VERSION);

module_init(em28xx_alsa_रेजिस्टर);
module_निकास(em28xx_alsa_unरेजिस्टर);
