<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Conexant Cx231xx audio extension
 *
 *  Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>
 *       Based on em28xx driver
 */

#समावेश "cx231xx.h"
#समावेश <linux/kernel.h>
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
#समावेश <media/v4l2-common.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "activates debug info");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;

अटल पूर्णांक cx231xx_isoc_audio_deinit(काष्ठा cx231xx *dev)
अणु
	पूर्णांक i;

	dev_dbg(dev->dev, "Stopping isoc\n");

	क्रम (i = 0; i < CX231XX_AUDIO_BUFS; i++) अणु
		अगर (dev->adev.urb[i]) अणु
			अगर (!irqs_disabled())
				usb_समाप्त_urb(dev->adev.urb[i]);
			अन्यथा
				usb_unlink_urb(dev->adev.urb[i]);

			usb_मुक्त_urb(dev->adev.urb[i]);
			dev->adev.urb[i] = शून्य;

			kमुक्त(dev->adev.transfer_buffer[i]);
			dev->adev.transfer_buffer[i] = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx231xx_bulk_audio_deinit(काष्ठा cx231xx *dev)
अणु
	पूर्णांक i;

	dev_dbg(dev->dev, "Stopping bulk\n");

	क्रम (i = 0; i < CX231XX_AUDIO_BUFS; i++) अणु
		अगर (dev->adev.urb[i]) अणु
			अगर (!irqs_disabled())
				usb_समाप्त_urb(dev->adev.urb[i]);
			अन्यथा
				usb_unlink_urb(dev->adev.urb[i]);

			usb_मुक्त_urb(dev->adev.urb[i]);
			dev->adev.urb[i] = शून्य;

			kमुक्त(dev->adev.transfer_buffer[i]);
			dev->adev.transfer_buffer[i] = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cx231xx_audio_isocirq(काष्ठा urb *urb)
अणु
	काष्ठा cx231xx *dev = urb->context;
	पूर्णांक i;
	अचिन्हित पूर्णांक oldptr;
	पूर्णांक period_elapsed = 0;
	पूर्णांक status;
	अचिन्हित अक्षर *cp;
	अचिन्हित पूर्णांक stride;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;

	अगर (dev->state & DEV_DISCONNECTED)
		वापस;

	चयन (urb->status) अणु
	हाल 0:		/* success */
	हाल -ETIMEDOUT:	/* NAK */
		अवरोध;
	हाल -ECONNRESET:	/* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:		/* error */
		dev_dbg(dev->dev, "urb completion error %d.\n",
			urb->status);
		अवरोध;
	पूर्ण

	अगर (atomic_पढ़ो(&dev->stream_started) == 0)
		वापस;

	अगर (dev->adev.capture_pcm_substream) अणु
		substream = dev->adev.capture_pcm_substream;
		runसमय = substream->runसमय;
		stride = runसमय->frame_bits >> 3;

		क्रम (i = 0; i < urb->number_of_packets; i++) अणु
			अचिन्हित दीर्घ flags;
			पूर्णांक length = urb->iso_frame_desc[i].actual_length /
				     stride;
			cp = (अचिन्हित अक्षर *)urb->transfer_buffer +
					      urb->iso_frame_desc[i].offset;

			अगर (!length)
				जारी;

			oldptr = dev->adev.hwptr_करोne_capture;
			अगर (oldptr + length >= runसमय->buffer_size) अणु
				अचिन्हित पूर्णांक cnt;

				cnt = runसमय->buffer_size - oldptr;
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
	अगर (status < 0) अणु
		dev_err(dev->dev,
			"resubmit of audio urb failed (error=%i)\n",
			status);
	पूर्ण
	वापस;
पूर्ण

अटल व्योम cx231xx_audio_bulkirq(काष्ठा urb *urb)
अणु
	काष्ठा cx231xx *dev = urb->context;
	अचिन्हित पूर्णांक oldptr;
	पूर्णांक period_elapsed = 0;
	पूर्णांक status;
	अचिन्हित अक्षर *cp;
	अचिन्हित पूर्णांक stride;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;

	अगर (dev->state & DEV_DISCONNECTED)
		वापस;

	चयन (urb->status) अणु
	हाल 0:		/* success */
	हाल -ETIMEDOUT:	/* NAK */
		अवरोध;
	हाल -ECONNRESET:	/* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:		/* error */
		dev_dbg(dev->dev, "urb completion error %d.\n",
			urb->status);
		अवरोध;
	पूर्ण

	अगर (atomic_पढ़ो(&dev->stream_started) == 0)
		वापस;

	अगर (dev->adev.capture_pcm_substream) अणु
		substream = dev->adev.capture_pcm_substream;
		runसमय = substream->runसमय;
		stride = runसमय->frame_bits >> 3;

		अगर (1) अणु
			अचिन्हित दीर्घ flags;
			पूर्णांक length = urb->actual_length /
				     stride;
			cp = (अचिन्हित अक्षर *)urb->transfer_buffer;

			oldptr = dev->adev.hwptr_करोne_capture;
			अगर (oldptr + length >= runसमय->buffer_size) अणु
				अचिन्हित पूर्णांक cnt;

				cnt = runसमय->buffer_size - oldptr;
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
	अगर (status < 0) अणु
		dev_err(dev->dev,
			"resubmit of audio urb failed (error=%i)\n",
			status);
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक cx231xx_init_audio_isoc(काष्ठा cx231xx *dev)
अणु
	पूर्णांक i, errCode;
	पूर्णांक sb_size;

	dev_dbg(dev->dev,
		"%s: Starting ISO AUDIO transfers\n", __func__);

	अगर (dev->state & DEV_DISCONNECTED)
		वापस -ENODEV;

	sb_size = CX231XX_ISO_NUM_AUDIO_PACKETS * dev->adev.max_pkt_size;

	क्रम (i = 0; i < CX231XX_AUDIO_BUFS; i++) अणु
		काष्ठा urb *urb;
		पूर्णांक j, k;

		dev->adev.transfer_buffer[i] = kदो_स्मृति(sb_size, GFP_ATOMIC);
		अगर (!dev->adev.transfer_buffer[i])
			वापस -ENOMEM;

		स_रखो(dev->adev.transfer_buffer[i], 0x80, sb_size);
		urb = usb_alloc_urb(CX231XX_ISO_NUM_AUDIO_PACKETS, GFP_ATOMIC);
		अगर (!urb) अणु
			क्रम (j = 0; j < i; j++) अणु
				usb_मुक्त_urb(dev->adev.urb[j]);
				kमुक्त(dev->adev.transfer_buffer[j]);
			पूर्ण
			वापस -ENOMEM;
		पूर्ण

		urb->dev = dev->udev;
		urb->context = dev;
		urb->pipe = usb_rcvisocpipe(dev->udev,
						dev->adev.end_poपूर्णांक_addr);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->transfer_buffer = dev->adev.transfer_buffer[i];
		urb->पूर्णांकerval = 1;
		urb->complete = cx231xx_audio_isocirq;
		urb->number_of_packets = CX231XX_ISO_NUM_AUDIO_PACKETS;
		urb->transfer_buffer_length = sb_size;

		क्रम (j = k = 0; j < CX231XX_ISO_NUM_AUDIO_PACKETS;
			j++, k += dev->adev.max_pkt_size) अणु
			urb->iso_frame_desc[j].offset = k;
			urb->iso_frame_desc[j].length = dev->adev.max_pkt_size;
		पूर्ण
		dev->adev.urb[i] = urb;
	पूर्ण

	क्रम (i = 0; i < CX231XX_AUDIO_BUFS; i++) अणु
		errCode = usb_submit_urb(dev->adev.urb[i], GFP_ATOMIC);
		अगर (errCode < 0) अणु
			cx231xx_isoc_audio_deinit(dev);
			वापस errCode;
		पूर्ण
	पूर्ण

	वापस errCode;
पूर्ण

अटल पूर्णांक cx231xx_init_audio_bulk(काष्ठा cx231xx *dev)
अणु
	पूर्णांक i, errCode;
	पूर्णांक sb_size;

	dev_dbg(dev->dev,
		"%s: Starting BULK AUDIO transfers\n", __func__);

	अगर (dev->state & DEV_DISCONNECTED)
		वापस -ENODEV;

	sb_size = CX231XX_NUM_AUDIO_PACKETS * dev->adev.max_pkt_size;

	क्रम (i = 0; i < CX231XX_AUDIO_BUFS; i++) अणु
		काष्ठा urb *urb;
		पूर्णांक j;

		dev->adev.transfer_buffer[i] = kदो_स्मृति(sb_size, GFP_ATOMIC);
		अगर (!dev->adev.transfer_buffer[i])
			वापस -ENOMEM;

		स_रखो(dev->adev.transfer_buffer[i], 0x80, sb_size);
		urb = usb_alloc_urb(CX231XX_NUM_AUDIO_PACKETS, GFP_ATOMIC);
		अगर (!urb) अणु
			क्रम (j = 0; j < i; j++) अणु
				usb_मुक्त_urb(dev->adev.urb[j]);
				kमुक्त(dev->adev.transfer_buffer[j]);
			पूर्ण
			वापस -ENOMEM;
		पूर्ण

		urb->dev = dev->udev;
		urb->context = dev;
		urb->pipe = usb_rcvbulkpipe(dev->udev,
						dev->adev.end_poपूर्णांक_addr);
		urb->transfer_flags = 0;
		urb->transfer_buffer = dev->adev.transfer_buffer[i];
		urb->complete = cx231xx_audio_bulkirq;
		urb->transfer_buffer_length = sb_size;

		dev->adev.urb[i] = urb;

	पूर्ण

	क्रम (i = 0; i < CX231XX_AUDIO_BUFS; i++) अणु
		errCode = usb_submit_urb(dev->adev.urb[i], GFP_ATOMIC);
		अगर (errCode < 0) अणु
			cx231xx_bulk_audio_deinit(dev);
			वापस errCode;
		पूर्ण
	पूर्ण

	वापस errCode;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_cx231xx_hw_capture = अणु
	.info = SNDRV_PCM_INFO_BLOCK_TRANSFER	|
	    SNDRV_PCM_INFO_MMAP			|
	    SNDRV_PCM_INFO_INTERLEAVED		|
	    SNDRV_PCM_INFO_MMAP_VALID,

	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,

	.rates = SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_KNOT,

	.rate_min = 48000,
	.rate_max = 48000,
	.channels_min = 2,
	.channels_max = 2,
	.buffer_bytes_max = 62720 * 8,	/* just about the value in usbaudio.c */
	.period_bytes_min = 64,		/* 12544/2, */
	.period_bytes_max = 12544,
	.periods_min = 2,
	.periods_max = 98,		/* 12544, */
पूर्ण;

अटल पूर्णांक snd_cx231xx_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cx231xx *dev = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक ret = 0;

	dev_dbg(dev->dev,
		"opening device and trying to acquire exclusive lock\n");

	अगर (dev->state & DEV_DISCONNECTED) अणु
		dev_err(dev->dev,
			"Can't open. the device was removed.\n");
		वापस -ENODEV;
	पूर्ण

	/* set alternate setting क्रम audio पूर्णांकerface */
	/* 1 - 48000 samples per sec */
	mutex_lock(&dev->lock);
	अगर (dev->USE_ISO)
		ret = cx231xx_set_alt_setting(dev, INDEX_AUDIO, 1);
	अन्यथा
		ret = cx231xx_set_alt_setting(dev, INDEX_AUDIO, 0);
	mutex_unlock(&dev->lock);
	अगर (ret < 0) अणु
		dev_err(dev->dev,
			"failed to set alternate setting !\n");

		वापस ret;
	पूर्ण

	runसमय->hw = snd_cx231xx_hw_capture;

	mutex_lock(&dev->lock);
	/* inक्रमm hardware to start streaming */
	ret = cx231xx_capture_start(dev, 1, Audio);

	dev->adev.users++;
	mutex_unlock(&dev->lock);

	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	dev->adev.capture_pcm_substream = substream;
	runसमय->निजी_data = dev;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cx231xx_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक ret;
	काष्ठा cx231xx *dev = snd_pcm_substream_chip(substream);

	dev_dbg(dev->dev, "closing device\n");

	/* inक्रमm hardware to stop streaming */
	mutex_lock(&dev->lock);
	ret = cx231xx_capture_start(dev, 0, Audio);

	/* set alternate setting क्रम audio पूर्णांकerface */
	/* 1 - 48000 samples per sec */
	ret = cx231xx_set_alt_setting(dev, INDEX_AUDIO, 0);
	अगर (ret < 0) अणु
		dev_err(dev->dev,
			"failed to set alternate setting !\n");

		mutex_unlock(&dev->lock);
		वापस ret;
	पूर्ण

	dev->adev.users--;
	mutex_unlock(&dev->lock);

	अगर (dev->adev.users == 0 && dev->adev.shutकरोwn == 1) अणु
		dev_dbg(dev->dev, "audio users: %d\n", dev->adev.users);
		dev_dbg(dev->dev, "disabling audio stream!\n");
		dev->adev.shutकरोwn = 0;
		dev_dbg(dev->dev, "released lock\n");
		अगर (atomic_पढ़ो(&dev->stream_started) > 0) अणु
			atomic_set(&dev->stream_started, 0);
			schedule_work(&dev->wq_trigger);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cx231xx_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cx231xx *dev = snd_pcm_substream_chip(substream);

	dev->adev.hwptr_करोne_capture = 0;
	dev->adev.capture_transfer_करोne = 0;

	वापस 0;
पूर्ण

अटल व्योम audio_trigger(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cx231xx *dev = container_of(work, काष्ठा cx231xx, wq_trigger);

	अगर (atomic_पढ़ो(&dev->stream_started)) अणु
		dev_dbg(dev->dev, "starting capture");
		अगर (is_fw_load(dev) == 0)
			cx25840_call(dev, core, load_fw);
		अगर (dev->USE_ISO)
			cx231xx_init_audio_isoc(dev);
		अन्यथा
			cx231xx_init_audio_bulk(dev);
	पूर्ण अन्यथा अणु
		dev_dbg(dev->dev, "stopping capture");
		cx231xx_isoc_audio_deinit(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_cx231xx_capture_trigger(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd)
अणु
	काष्ठा cx231xx *dev = snd_pcm_substream_chip(substream);
	पूर्णांक retval = 0;

	अगर (dev->state & DEV_DISCONNECTED)
		वापस -ENODEV;

	spin_lock(&dev->adev.slock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		atomic_set(&dev->stream_started, 1);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		atomic_set(&dev->stream_started, 0);
		अवरोध;
	शेष:
		retval = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock(&dev->adev.slock);

	schedule_work(&dev->wq_trigger);

	वापस retval;
पूर्ण

अटल snd_pcm_uframes_t snd_cx231xx_capture_poपूर्णांकer(काष्ठा snd_pcm_substream
						     *substream)
अणु
	काष्ठा cx231xx *dev;
	अचिन्हित दीर्घ flags;
	snd_pcm_uframes_t hwptr_करोne;

	dev = snd_pcm_substream_chip(substream);

	spin_lock_irqsave(&dev->adev.slock, flags);
	hwptr_करोne = dev->adev.hwptr_करोne_capture;
	spin_unlock_irqrestore(&dev->adev.slock, flags);

	वापस hwptr_करोne;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_cx231xx_pcm_capture = अणु
	.खोलो = snd_cx231xx_capture_खोलो,
	.बंद = snd_cx231xx_pcm_बंद,
	.prepare = snd_cx231xx_prepare,
	.trigger = snd_cx231xx_capture_trigger,
	.poपूर्णांकer = snd_cx231xx_capture_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक cx231xx_audio_init(काष्ठा cx231xx *dev)
अणु
	काष्ठा cx231xx_audio *adev = &dev->adev;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_card *card;
	अटल पूर्णांक devnr;
	पूर्णांक err;
	काष्ठा usb_पूर्णांकerface *uअगर;
	पूर्णांक i, isoc_pipe = 0;

	अगर (dev->has_alsa_audio != 1) अणु
		/* This device करोes not support the extension (in this हाल
		   the device is expecting the snd-usb-audio module or
		   करोesn't have analog audio support at all) */
		वापस 0;
	पूर्ण

	dev_dbg(dev->dev,
		"probing for cx231xx non standard usbaudio\n");

	err = snd_card_new(dev->dev, index[devnr], "Cx231xx Audio",
			   THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	spin_lock_init(&adev->slock);
	err = snd_pcm_new(card, "Cx231xx Audio", 0, 0, 1, &pcm);
	अगर (err < 0)
		जाओ err_मुक्त_card;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_cx231xx_pcm_capture);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);
	pcm->info_flags = 0;
	pcm->निजी_data = dev;
	strscpy(pcm->name, "Conexant cx231xx Capture", माप(pcm->name));
	strscpy(card->driver, "Cx231xx-Audio", माप(card->driver));
	strscpy(card->लघुname, "Cx231xx Audio", माप(card->लघुname));
	strscpy(card->दीर्घname, "Conexant cx231xx Audio", माप(card->दीर्घname));

	INIT_WORK(&dev->wq_trigger, audio_trigger);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ err_मुक्त_card;

	adev->sndcard = card;
	adev->udev = dev->udev;

	/* compute alternate max packet sizes क्रम Audio */
	uअगर =
	    dev->udev->actconfig->पूर्णांकerface[dev->current_pcb_config.
					    hs_config_info[0].पूर्णांकerface_info.
					    audio_index + 1];

	अगर (uअगर->altsetting[0].desc.bNumEndpoपूर्णांकs < isoc_pipe + 1) अणु
		err = -ENODEV;
		जाओ err_मुक्त_card;
	पूर्ण

	adev->end_poपूर्णांक_addr =
	    uअगर->altsetting[0].endpoपूर्णांक[isoc_pipe].desc.
			bEndpoपूर्णांकAddress;

	adev->num_alt = uअगर->num_altsetting;
	dev_info(dev->dev,
		"audio EndPoint Addr 0x%x, Alternate settings: %i\n",
		adev->end_poपूर्णांक_addr, adev->num_alt);
	adev->alt_max_pkt_size = kदो_स्मृति_array(32, adev->num_alt, GFP_KERNEL);
	अगर (!adev->alt_max_pkt_size) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_card;
	पूर्ण

	क्रम (i = 0; i < adev->num_alt; i++) अणु
		u16 पंचांगp;

		अगर (uअगर->altsetting[i].desc.bNumEndpoपूर्णांकs < isoc_pipe + 1) अणु
			err = -ENODEV;
			जाओ err_मुक्त_pkt_size;
		पूर्ण

		पंचांगp = le16_to_cpu(uअगर->altsetting[i].endpoपूर्णांक[isoc_pipe].desc.
				wMaxPacketSize);
		adev->alt_max_pkt_size[i] =
		    (पंचांगp & 0x07ff) * (((पंचांगp & 0x1800) >> 11) + 1);
		dev_dbg(dev->dev,
			"audio alternate setting %i, max size= %i\n", i,
			adev->alt_max_pkt_size[i]);
	पूर्ण

	वापस 0;

err_मुक्त_pkt_size:
	kमुक्त(adev->alt_max_pkt_size);
err_मुक्त_card:
	snd_card_मुक्त(card);

	वापस err;
पूर्ण

अटल पूर्णांक cx231xx_audio_fini(काष्ठा cx231xx *dev)
अणु
	अगर (dev == शून्य)
		वापस 0;

	अगर (dev->has_alsa_audio != 1) अणु
		/* This device करोes not support the extension (in this हाल
		   the device is expecting the snd-usb-audio module or
		   करोesn't have analog audio support at all) */
		वापस 0;
	पूर्ण

	अगर (dev->adev.sndcard) अणु
		snd_card_मुक्त_when_बंदd(dev->adev.sndcard);
		kमुक्त(dev->adev.alt_max_pkt_size);
		dev->adev.sndcard = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा cx231xx_ops audio_ops = अणु
	.id = CX231XX_AUDIO,
	.name = "Cx231xx Audio Extension",
	.init = cx231xx_audio_init,
	.fini = cx231xx_audio_fini,
पूर्ण;

अटल पूर्णांक __init cx231xx_alsa_रेजिस्टर(व्योम)
अणु
	वापस cx231xx_रेजिस्टर_extension(&audio_ops);
पूर्ण

अटल व्योम __निकास cx231xx_alsa_unरेजिस्टर(व्योम)
अणु
	cx231xx_unरेजिस्टर_extension(&audio_ops);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Srinivasa Deevi <srinivasa.deevi@conexant.com>");
MODULE_DESCRIPTION("Cx231xx Audio driver");

module_init(cx231xx_alsa_रेजिस्टर);
module_निकास(cx231xx_alsa_unरेजिस्टर);
