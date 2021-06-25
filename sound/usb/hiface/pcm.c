<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux driver क्रम M2Tech hiFace compatible devices
 *
 * Copyright 2012-2013 (C) M2TECH S.r.l and Amarula Solutions B.V.
 *
 * Authors:  Michael Trimarchi <michael@amarulasolutions.com>
 *           Antonio Ospite <ao2@amarulasolutions.com>
 *
 * The driver is based on the work करोne in TerraTec DMX 6Fire USB
 */

#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>

#समावेश "pcm.h"
#समावेश "chip.h"

#घोषणा OUT_EP          0x2
#घोषणा PCM_N_URBS      8
#घोषणा PCM_PACKET_SIZE 4096
#घोषणा PCM_BUFFER_SIZE (2 * PCM_N_URBS * PCM_PACKET_SIZE)

काष्ठा pcm_urb अणु
	काष्ठा hअगरace_chip *chip;

	काष्ठा urb instance;
	काष्ठा usb_anchor submitted;
	u8 *buffer;
पूर्ण;

काष्ठा pcm_substream अणु
	spinlock_t lock;
	काष्ठा snd_pcm_substream *instance;

	bool active;
	snd_pcm_uframes_t dma_off;    /* current position in alsa dma_area */
	snd_pcm_uframes_t period_off; /* current position in current period */
पूर्ण;

क्रमागत अणु /* pcm streaming states */
	STREAM_DISABLED, /* no pcm streaming */
	STREAM_STARTING, /* pcm streaming requested, रुकोing to become पढ़ोy */
	STREAM_RUNNING,  /* pcm streaming running */
	STREAM_STOPPING
पूर्ण;

काष्ठा pcm_runसमय अणु
	काष्ठा hअगरace_chip *chip;
	काष्ठा snd_pcm *instance;

	काष्ठा pcm_substream playback;
	bool panic; /* अगर set driver won't करो anymore pcm on device */

	काष्ठा pcm_urb out_urbs[PCM_N_URBS];

	काष्ठा mutex stream_mutex;
	u8 stream_state; /* one of STREAM_XXX */
	u8 extra_freq;
	रुको_queue_head_t stream_रुको_queue;
	bool stream_रुको_cond;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु 44100, 48000, 88200, 96000, 176400, 192000,
				      352800, 384000 पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_extra_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list = rates,
	.mask = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware pcm_hw = अणु
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_PAUSE |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_BATCH,

	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,

	.rates = SNDRV_PCM_RATE_44100 |
		SNDRV_PCM_RATE_48000 |
		SNDRV_PCM_RATE_88200 |
		SNDRV_PCM_RATE_96000 |
		SNDRV_PCM_RATE_176400 |
		SNDRV_PCM_RATE_192000,

	.rate_min = 44100,
	.rate_max = 192000, /* changes in hअगरace_pcm_खोलो to support extra rates */
	.channels_min = 2,
	.channels_max = 2,
	.buffer_bytes_max = PCM_BUFFER_SIZE,
	.period_bytes_min = PCM_PACKET_SIZE,
	.period_bytes_max = PCM_BUFFER_SIZE,
	.periods_min = 2,
	.periods_max = 1024
पूर्ण;

/* message values used to change the sample rate */
#घोषणा HIFACE_SET_RATE_REQUEST 0xb0

#घोषणा HIFACE_RATE_44100  0x43
#घोषणा HIFACE_RATE_48000  0x4b
#घोषणा HIFACE_RATE_88200  0x42
#घोषणा HIFACE_RATE_96000  0x4a
#घोषणा HIFACE_RATE_176400 0x40
#घोषणा HIFACE_RATE_192000 0x48
#घोषणा HIFACE_RATE_352800 0x58
#घोषणा HIFACE_RATE_384000 0x68

अटल पूर्णांक hअगरace_pcm_set_rate(काष्ठा pcm_runसमय *rt, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा usb_device *device = rt->chip->dev;
	u16 rate_value;
	पूर्णांक ret;

	/* We are alपढ़ोy sure that the rate is supported here thanks to
	 * ALSA स्थिरraपूर्णांकs
	 */
	चयन (rate) अणु
	हाल 44100:
		rate_value = HIFACE_RATE_44100;
		अवरोध;
	हाल 48000:
		rate_value = HIFACE_RATE_48000;
		अवरोध;
	हाल 88200:
		rate_value = HIFACE_RATE_88200;
		अवरोध;
	हाल 96000:
		rate_value = HIFACE_RATE_96000;
		अवरोध;
	हाल 176400:
		rate_value = HIFACE_RATE_176400;
		अवरोध;
	हाल 192000:
		rate_value = HIFACE_RATE_192000;
		अवरोध;
	हाल 352800:
		rate_value = HIFACE_RATE_352800;
		अवरोध;
	हाल 384000:
		rate_value = HIFACE_RATE_384000;
		अवरोध;
	शेष:
		dev_err(&device->dev, "Unsupported rate %d\n", rate);
		वापस -EINVAL;
	पूर्ण

	/*
	 * USBIO: Venकरोr 0xb0(wValue=0x0043, wIndex=0x0000)
	 * 43 b0 43 00 00 00 00 00
	 * USBIO: Venकरोr 0xb0(wValue=0x004b, wIndex=0x0000)
	 * 43 b0 4b 00 00 00 00 00
	 * This control message करोesn't have any ack from the
	 * other side
	 */
	ret = usb_control_msg_send(device, 0,
				   HIFACE_SET_RATE_REQUEST,
				   USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
				   rate_value, 0, शून्य, 0, 100, GFP_KERNEL);
	अगर (ret)
		dev_err(&device->dev, "Error setting samplerate %d.\n", rate);

	वापस ret;
पूर्ण

अटल काष्ठा pcm_substream *hअगरace_pcm_get_substream(काष्ठा snd_pcm_substream
						      *alsa_sub)
अणु
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(alsa_sub);
	काष्ठा device *device = &rt->chip->dev->dev;

	अगर (alsa_sub->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस &rt->playback;

	dev_err(device, "Error getting pcm substream slot.\n");
	वापस शून्य;
पूर्ण

/* call with stream_mutex locked */
अटल व्योम hअगरace_pcm_stream_stop(काष्ठा pcm_runसमय *rt)
अणु
	पूर्णांक i, समय;

	अगर (rt->stream_state != STREAM_DISABLED) अणु
		rt->stream_state = STREAM_STOPPING;

		क्रम (i = 0; i < PCM_N_URBS; i++) अणु
			समय = usb_रुको_anchor_empty_समयout(
					&rt->out_urbs[i].submitted, 100);
			अगर (!समय)
				usb_समाप्त_anchored_urbs(
					&rt->out_urbs[i].submitted);
			usb_समाप्त_urb(&rt->out_urbs[i].instance);
		पूर्ण

		rt->stream_state = STREAM_DISABLED;
	पूर्ण
पूर्ण

/* call with stream_mutex locked */
अटल पूर्णांक hअगरace_pcm_stream_start(काष्ठा pcm_runसमय *rt)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (rt->stream_state == STREAM_DISABLED) अणु

		/* reset panic state when starting a new stream */
		rt->panic = false;

		/* submit our out urbs zero init */
		rt->stream_state = STREAM_STARTING;
		क्रम (i = 0; i < PCM_N_URBS; i++) अणु
			स_रखो(rt->out_urbs[i].buffer, 0, PCM_PACKET_SIZE);
			usb_anchor_urb(&rt->out_urbs[i].instance,
				       &rt->out_urbs[i].submitted);
			ret = usb_submit_urb(&rt->out_urbs[i].instance,
					     GFP_ATOMIC);
			अगर (ret) अणु
				hअगरace_pcm_stream_stop(rt);
				वापस ret;
			पूर्ण
		पूर्ण

		/* रुको क्रम first out urb to वापस (sent in in urb handler) */
		रुको_event_समयout(rt->stream_रुको_queue, rt->stream_रुको_cond,
				   HZ);
		अगर (rt->stream_रुको_cond) अणु
			काष्ठा device *device = &rt->chip->dev->dev;
			dev_dbg(device, "%s: Stream is running wakeup event\n",
				 __func__);
			rt->stream_state = STREAM_RUNNING;
		पूर्ण अन्यथा अणु
			hअगरace_pcm_stream_stop(rt);
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/* The hardware wants word-swapped 32-bit values */
अटल व्योम स_नकल_swahw32(u8 *dest, u8 *src, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < n / 4; i++)
		((u32 *)dest)[i] = swahw32(((u32 *)src)[i]);
पूर्ण

/* call with substream locked */
/* वापसs true अगर a period elapsed */
अटल bool hअगरace_pcm_playback(काष्ठा pcm_substream *sub, काष्ठा pcm_urb *urb)
अणु
	काष्ठा snd_pcm_runसमय *alsa_rt = sub->instance->runसमय;
	काष्ठा device *device = &urb->chip->dev->dev;
	u8 *source;
	अचिन्हित पूर्णांक pcm_buffer_size;

	WARN_ON(alsa_rt->क्रमmat != SNDRV_PCM_FORMAT_S32_LE);

	pcm_buffer_size = snd_pcm_lib_buffer_bytes(sub->instance);

	अगर (sub->dma_off + PCM_PACKET_SIZE <= pcm_buffer_size) अणु
		dev_dbg(device, "%s: (1) buffer_size %#x dma_offset %#x\n", __func__,
			 (अचिन्हित पूर्णांक) pcm_buffer_size,
			 (अचिन्हित पूर्णांक) sub->dma_off);

		source = alsa_rt->dma_area + sub->dma_off;
		स_नकल_swahw32(urb->buffer, source, PCM_PACKET_SIZE);
	पूर्ण अन्यथा अणु
		/* wrap around at end of ring buffer */
		अचिन्हित पूर्णांक len;

		dev_dbg(device, "%s: (2) buffer_size %#x dma_offset %#x\n", __func__,
			 (अचिन्हित पूर्णांक) pcm_buffer_size,
			 (अचिन्हित पूर्णांक) sub->dma_off);

		len = pcm_buffer_size - sub->dma_off;

		source = alsa_rt->dma_area + sub->dma_off;
		स_नकल_swahw32(urb->buffer, source, len);

		source = alsa_rt->dma_area;
		स_नकल_swahw32(urb->buffer + len, source,
			       PCM_PACKET_SIZE - len);
	पूर्ण
	sub->dma_off += PCM_PACKET_SIZE;
	अगर (sub->dma_off >= pcm_buffer_size)
		sub->dma_off -= pcm_buffer_size;

	sub->period_off += PCM_PACKET_SIZE;
	अगर (sub->period_off >= alsa_rt->period_size) अणु
		sub->period_off %= alsa_rt->period_size;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम hअगरace_pcm_out_urb_handler(काष्ठा urb *usb_urb)
अणु
	काष्ठा pcm_urb *out_urb = usb_urb->context;
	काष्ठा pcm_runसमय *rt = out_urb->chip->pcm;
	काष्ठा pcm_substream *sub;
	bool करो_period_elapsed = false;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (rt->panic || rt->stream_state == STREAM_STOPPING)
		वापस;

	अगर (unlikely(usb_urb->status == -ENOENT ||	/* unlinked */
		     usb_urb->status == -ENODEV ||	/* device हटाओd */
		     usb_urb->status == -ECONNRESET ||	/* unlinked */
		     usb_urb->status == -ESHUTDOWN)) अणु	/* device disabled */
		जाओ out_fail;
	पूर्ण

	अगर (rt->stream_state == STREAM_STARTING) अणु
		rt->stream_रुको_cond = true;
		wake_up(&rt->stream_रुको_queue);
	पूर्ण

	/* now send our playback data (अगर a मुक्त out urb was found) */
	sub = &rt->playback;
	spin_lock_irqsave(&sub->lock, flags);
	अगर (sub->active)
		करो_period_elapsed = hअगरace_pcm_playback(sub, out_urb);
	अन्यथा
		स_रखो(out_urb->buffer, 0, PCM_PACKET_SIZE);

	spin_unlock_irqrestore(&sub->lock, flags);

	अगर (करो_period_elapsed)
		snd_pcm_period_elapsed(sub->instance);

	ret = usb_submit_urb(&out_urb->instance, GFP_ATOMIC);
	अगर (ret < 0)
		जाओ out_fail;

	वापस;

out_fail:
	rt->panic = true;
पूर्ण

अटल पूर्णांक hअगरace_pcm_खोलो(काष्ठा snd_pcm_substream *alsa_sub)
अणु
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(alsa_sub);
	काष्ठा pcm_substream *sub = शून्य;
	काष्ठा snd_pcm_runसमय *alsa_rt = alsa_sub->runसमय;
	पूर्णांक ret;

	अगर (rt->panic)
		वापस -EPIPE;

	mutex_lock(&rt->stream_mutex);
	alsa_rt->hw = pcm_hw;

	अगर (alsa_sub->stream == SNDRV_PCM_STREAM_PLAYBACK)
		sub = &rt->playback;

	अगर (!sub) अणु
		काष्ठा device *device = &rt->chip->dev->dev;
		mutex_unlock(&rt->stream_mutex);
		dev_err(device, "Invalid stream type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (rt->extra_freq) अणु
		alsa_rt->hw.rates |= SNDRV_PCM_RATE_KNOT;
		alsa_rt->hw.rate_max = 384000;

		/* explicit स्थिरraपूर्णांकs needed as we added SNDRV_PCM_RATE_KNOT */
		ret = snd_pcm_hw_स्थिरraपूर्णांक_list(alsa_sub->runसमय, 0,
						 SNDRV_PCM_HW_PARAM_RATE,
						 &स्थिरraपूर्णांकs_extra_rates);
		अगर (ret < 0) अणु
			mutex_unlock(&rt->stream_mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	sub->instance = alsa_sub;
	sub->active = false;
	mutex_unlock(&rt->stream_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक hअगरace_pcm_बंद(काष्ठा snd_pcm_substream *alsa_sub)
अणु
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(alsa_sub);
	काष्ठा pcm_substream *sub = hअगरace_pcm_get_substream(alsa_sub);
	अचिन्हित दीर्घ flags;

	अगर (rt->panic)
		वापस 0;

	mutex_lock(&rt->stream_mutex);
	अगर (sub) अणु
		hअगरace_pcm_stream_stop(rt);

		/* deactivate substream */
		spin_lock_irqsave(&sub->lock, flags);
		sub->instance = शून्य;
		sub->active = false;
		spin_unlock_irqrestore(&sub->lock, flags);

	पूर्ण
	mutex_unlock(&rt->stream_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक hअगरace_pcm_prepare(काष्ठा snd_pcm_substream *alsa_sub)
अणु
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(alsa_sub);
	काष्ठा pcm_substream *sub = hअगरace_pcm_get_substream(alsa_sub);
	काष्ठा snd_pcm_runसमय *alsa_rt = alsa_sub->runसमय;
	पूर्णांक ret;

	अगर (rt->panic)
		वापस -EPIPE;
	अगर (!sub)
		वापस -ENODEV;

	mutex_lock(&rt->stream_mutex);

	hअगरace_pcm_stream_stop(rt);

	sub->dma_off = 0;
	sub->period_off = 0;

	अगर (rt->stream_state == STREAM_DISABLED) अणु

		ret = hअगरace_pcm_set_rate(rt, alsa_rt->rate);
		अगर (ret) अणु
			mutex_unlock(&rt->stream_mutex);
			वापस ret;
		पूर्ण
		ret = hअगरace_pcm_stream_start(rt);
		अगर (ret) अणु
			mutex_unlock(&rt->stream_mutex);
			वापस ret;
		पूर्ण
	पूर्ण
	mutex_unlock(&rt->stream_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक hअगरace_pcm_trigger(काष्ठा snd_pcm_substream *alsa_sub, पूर्णांक cmd)
अणु
	काष्ठा pcm_substream *sub = hअगरace_pcm_get_substream(alsa_sub);
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(alsa_sub);

	अगर (rt->panic)
		वापस -EPIPE;
	अगर (!sub)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		spin_lock_irq(&sub->lock);
		sub->active = true;
		spin_unlock_irq(&sub->lock);
		वापस 0;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		spin_lock_irq(&sub->lock);
		sub->active = false;
		spin_unlock_irq(&sub->lock);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल snd_pcm_uframes_t hअगरace_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *alsa_sub)
अणु
	काष्ठा pcm_substream *sub = hअगरace_pcm_get_substream(alsa_sub);
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(alsa_sub);
	अचिन्हित दीर्घ flags;
	snd_pcm_uframes_t dma_offset;

	अगर (rt->panic || !sub)
		वापस SNDRV_PCM_POS_XRUN;

	spin_lock_irqsave(&sub->lock, flags);
	dma_offset = sub->dma_off;
	spin_unlock_irqrestore(&sub->lock, flags);
	वापस bytes_to_frames(alsa_sub->runसमय, dma_offset);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops pcm_ops = अणु
	.खोलो = hअगरace_pcm_खोलो,
	.बंद = hअगरace_pcm_बंद,
	.prepare = hअगरace_pcm_prepare,
	.trigger = hअगरace_pcm_trigger,
	.poपूर्णांकer = hअगरace_pcm_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक hअगरace_pcm_init_urb(काष्ठा pcm_urb *urb,
			       काष्ठा hअगरace_chip *chip,
			       अचिन्हित पूर्णांक ep,
			       व्योम (*handler)(काष्ठा urb *))
अणु
	urb->chip = chip;
	usb_init_urb(&urb->instance);

	urb->buffer = kzalloc(PCM_PACKET_SIZE, GFP_KERNEL);
	अगर (!urb->buffer)
		वापस -ENOMEM;

	usb_fill_bulk_urb(&urb->instance, chip->dev,
			  usb_sndbulkpipe(chip->dev, ep), (व्योम *)urb->buffer,
			  PCM_PACKET_SIZE, handler, urb);
	अगर (usb_urb_ep_type_check(&urb->instance))
		वापस -EINVAL;
	init_usb_anchor(&urb->submitted);

	वापस 0;
पूर्ण

व्योम hअगरace_pcm_पात(काष्ठा hअगरace_chip *chip)
अणु
	काष्ठा pcm_runसमय *rt = chip->pcm;

	अगर (rt) अणु
		rt->panic = true;

		mutex_lock(&rt->stream_mutex);
		hअगरace_pcm_stream_stop(rt);
		mutex_unlock(&rt->stream_mutex);
	पूर्ण
पूर्ण

अटल व्योम hअगरace_pcm_destroy(काष्ठा hअगरace_chip *chip)
अणु
	काष्ठा pcm_runसमय *rt = chip->pcm;
	पूर्णांक i;

	क्रम (i = 0; i < PCM_N_URBS; i++)
		kमुक्त(rt->out_urbs[i].buffer);

	kमुक्त(chip->pcm);
	chip->pcm = शून्य;
पूर्ण

अटल व्योम hअगरace_pcm_मुक्त(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा pcm_runसमय *rt = pcm->निजी_data;

	अगर (rt)
		hअगरace_pcm_destroy(rt->chip);
पूर्ण

पूर्णांक hअगरace_pcm_init(काष्ठा hअगरace_chip *chip, u8 extra_freq)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा snd_pcm *pcm;
	काष्ठा pcm_runसमय *rt;

	rt = kzalloc(माप(*rt), GFP_KERNEL);
	अगर (!rt)
		वापस -ENOMEM;

	rt->chip = chip;
	rt->stream_state = STREAM_DISABLED;
	अगर (extra_freq)
		rt->extra_freq = 1;

	init_रुकोqueue_head(&rt->stream_रुको_queue);
	mutex_init(&rt->stream_mutex);
	spin_lock_init(&rt->playback.lock);

	क्रम (i = 0; i < PCM_N_URBS; i++) अणु
		ret = hअगरace_pcm_init_urb(&rt->out_urbs[i], chip, OUT_EP,
				    hअगरace_pcm_out_urb_handler);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	ret = snd_pcm_new(chip->card, "USB-SPDIF Audio", 0, 1, 0, &pcm);
	अगर (ret < 0) अणु
		dev_err(&chip->dev->dev, "Cannot create pcm instance\n");
		जाओ error;
	पूर्ण

	pcm->निजी_data = rt;
	pcm->निजी_मुक्त = hअगरace_pcm_मुक्त;

	strscpy(pcm->name, "USB-SPDIF Audio", माप(pcm->name));
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &pcm_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC,
				       शून्य, 0, 0);

	rt->instance = pcm;

	chip->pcm = rt;
	वापस 0;

error:
	क्रम (i = 0; i < PCM_N_URBS; i++)
		kमुक्त(rt->out_urbs[i].buffer);
	kमुक्त(rt);
	वापस ret;
पूर्ण
