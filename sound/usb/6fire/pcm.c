<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux driver क्रम TerraTec DMX 6Fire USB
 *
 * PCM driver
 *
 * Author:	Torsten Schenk <torsten.schenk@zoho.com>
 * Created:	Jan 01, 2011
 * Copyright:	(C) Torsten Schenk
 */

#समावेश "pcm.h"
#समावेश "chip.h"
#समावेश "comm.h"
#समावेश "control.h"

क्रमागत अणु
	OUT_N_CHANNELS = 6, IN_N_CHANNELS = 4
पूर्ण;

/* keep next two synced with
 * FW_EP_W_MAX_PACKET_SIZE[] and RATES_MAX_PACKET_SIZE
 * and CONTROL_RATE_XXX in control.h */
अटल स्थिर पूर्णांक rates_in_packet_size[] = अणु 228, 228, 420, 420, 404, 404 पूर्ण;
अटल स्थिर पूर्णांक rates_out_packet_size[] = अणु 228, 228, 420, 420, 604, 604 पूर्ण;
अटल स्थिर पूर्णांक rates[] = अणु 44100, 48000, 88200, 96000, 176400, 192000 पूर्ण;
अटल स्थिर पूर्णांक rates_alsaid[] = अणु
	SNDRV_PCM_RATE_44100, SNDRV_PCM_RATE_48000,
	SNDRV_PCM_RATE_88200, SNDRV_PCM_RATE_96000,
	SNDRV_PCM_RATE_176400, SNDRV_PCM_RATE_192000 पूर्ण;

क्रमागत अणु /* settings क्रम pcm */
	OUT_EP = 6, IN_EP = 2, MAX_बफ_मानE = 128 * 1024
पूर्ण;

क्रमागत अणु /* pcm streaming states */
	STREAM_DISABLED, /* no pcm streaming */
	STREAM_STARTING, /* pcm streaming requested, रुकोing to become पढ़ोy */
	STREAM_RUNNING, /* pcm streaming running */
	STREAM_STOPPING
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware pcm_hw = अणु
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_BATCH,

	.क्रमmats = SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE,

	.rates = SNDRV_PCM_RATE_44100 |
		SNDRV_PCM_RATE_48000 |
		SNDRV_PCM_RATE_88200 |
		SNDRV_PCM_RATE_96000 |
		SNDRV_PCM_RATE_176400 |
		SNDRV_PCM_RATE_192000,

	.rate_min = 44100,
	.rate_max = 192000,
	.channels_min = 1,
	.channels_max = 0, /* set in pcm_खोलो, depending on capture/playback */
	.buffer_bytes_max = MAX_बफ_मानE,
	.period_bytes_min = PCM_N_PACKETS_PER_URB * (PCM_MAX_PACKET_SIZE - 4),
	.period_bytes_max = MAX_बफ_मानE,
	.periods_min = 2,
	.periods_max = 1024
पूर्ण;

अटल पूर्णांक usb6fire_pcm_set_rate(काष्ठा pcm_runसमय *rt)
अणु
	पूर्णांक ret;
	काष्ठा control_runसमय *ctrl_rt = rt->chip->control;

	ctrl_rt->usb_streaming = false;
	ret = ctrl_rt->update_streaming(ctrl_rt);
	अगर (ret < 0) अणु
		dev_err(&rt->chip->dev->dev,
			"error stopping streaming while setting samplerate %d.\n",
			rates[rt->rate]);
		वापस ret;
	पूर्ण

	ret = ctrl_rt->set_rate(ctrl_rt, rt->rate);
	अगर (ret < 0) अणु
		dev_err(&rt->chip->dev->dev,
			"error setting samplerate %d.\n",
			rates[rt->rate]);
		वापस ret;
	पूर्ण

	ret = ctrl_rt->set_channels(ctrl_rt, OUT_N_CHANNELS, IN_N_CHANNELS,
			false, false);
	अगर (ret < 0) अणु
		dev_err(&rt->chip->dev->dev,
			"error initializing channels while setting samplerate %d.\n",
			rates[rt->rate]);
		वापस ret;
	पूर्ण

	ctrl_rt->usb_streaming = true;
	ret = ctrl_rt->update_streaming(ctrl_rt);
	अगर (ret < 0) अणु
		dev_err(&rt->chip->dev->dev,
			"error starting streaming while setting samplerate %d.\n",
			rates[rt->rate]);
		वापस ret;
	पूर्ण

	rt->in_n_analog = IN_N_CHANNELS;
	rt->out_n_analog = OUT_N_CHANNELS;
	rt->in_packet_size = rates_in_packet_size[rt->rate];
	rt->out_packet_size = rates_out_packet_size[rt->rate];
	वापस 0;
पूर्ण

अटल काष्ठा pcm_substream *usb6fire_pcm_get_substream(
		काष्ठा snd_pcm_substream *alsa_sub)
अणु
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(alsa_sub);

	अगर (alsa_sub->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस &rt->playback;
	अन्यथा अगर (alsa_sub->stream == SNDRV_PCM_STREAM_CAPTURE)
		वापस &rt->capture;
	dev_err(&rt->chip->dev->dev, "error getting pcm substream slot.\n");
	वापस शून्य;
पूर्ण

/* call with stream_mutex locked */
अटल व्योम usb6fire_pcm_stream_stop(काष्ठा pcm_runसमय *rt)
अणु
	पूर्णांक i;
	काष्ठा control_runसमय *ctrl_rt = rt->chip->control;

	अगर (rt->stream_state != STREAM_DISABLED) अणु

		rt->stream_state = STREAM_STOPPING;

		क्रम (i = 0; i < PCM_N_URBS; i++) अणु
			usb_समाप्त_urb(&rt->in_urbs[i].instance);
			usb_समाप्त_urb(&rt->out_urbs[i].instance);
		पूर्ण
		ctrl_rt->usb_streaming = false;
		ctrl_rt->update_streaming(ctrl_rt);
		rt->stream_state = STREAM_DISABLED;
	पूर्ण
पूर्ण

/* call with stream_mutex locked */
अटल पूर्णांक usb6fire_pcm_stream_start(काष्ठा pcm_runसमय *rt)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक k;
	काष्ठा usb_iso_packet_descriptor *packet;

	अगर (rt->stream_state == STREAM_DISABLED) अणु
		/* submit our in urbs */
		rt->stream_रुको_cond = false;
		rt->stream_state = STREAM_STARTING;
		क्रम (i = 0; i < PCM_N_URBS; i++) अणु
			क्रम (k = 0; k < PCM_N_PACKETS_PER_URB; k++) अणु
				packet = &rt->in_urbs[i].packets[k];
				packet->offset = k * rt->in_packet_size;
				packet->length = rt->in_packet_size;
				packet->actual_length = 0;
				packet->status = 0;
			पूर्ण
			ret = usb_submit_urb(&rt->in_urbs[i].instance,
					GFP_ATOMIC);
			अगर (ret) अणु
				usb6fire_pcm_stream_stop(rt);
				वापस ret;
			पूर्ण
		पूर्ण

		/* रुको क्रम first out urb to वापस (sent in in urb handler) */
		रुको_event_समयout(rt->stream_रुको_queue, rt->stream_रुको_cond,
				HZ);
		अगर (rt->stream_रुको_cond)
			rt->stream_state = STREAM_RUNNING;
		अन्यथा अणु
			usb6fire_pcm_stream_stop(rt);
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* call with substream locked */
अटल व्योम usb6fire_pcm_capture(काष्ठा pcm_substream *sub, काष्ठा pcm_urb *urb)
अणु
	पूर्णांक i;
	पूर्णांक frame;
	पूर्णांक frame_count;
	अचिन्हित पूर्णांक total_length = 0;
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(sub->instance);
	काष्ठा snd_pcm_runसमय *alsa_rt = sub->instance->runसमय;
	u32 *src = शून्य;
	u32 *dest = (u32 *) (alsa_rt->dma_area + sub->dma_off
			* (alsa_rt->frame_bits >> 3));
	u32 *dest_end = (u32 *) (alsa_rt->dma_area + alsa_rt->buffer_size
			* (alsa_rt->frame_bits >> 3));
	पूर्णांक bytes_per_frame = alsa_rt->channels << 2;

	क्रम (i = 0; i < PCM_N_PACKETS_PER_URB; i++) अणु
		/* at least 4 header bytes क्रम valid packet.
		 * after that: 32 bits per sample क्रम analog channels */
		अगर (urb->packets[i].actual_length > 4)
			frame_count = (urb->packets[i].actual_length - 4)
					/ (rt->in_n_analog << 2);
		अन्यथा
			frame_count = 0;

		अगर (alsa_rt->क्रमmat == SNDRV_PCM_FORMAT_S24_LE)
			src = (u32 *) (urb->buffer + total_length);
		अन्यथा अगर (alsa_rt->क्रमmat == SNDRV_PCM_FORMAT_S32_LE)
			src = (u32 *) (urb->buffer - 1 + total_length);
		अन्यथा
			वापस;
		src++; /* skip leading 4 bytes of every packet */
		total_length += urb->packets[i].length;
		क्रम (frame = 0; frame < frame_count; frame++) अणु
			स_नकल(dest, src, bytes_per_frame);
			dest += alsa_rt->channels;
			src += rt->in_n_analog;
			sub->dma_off++;
			sub->period_off++;
			अगर (dest == dest_end) अणु
				sub->dma_off = 0;
				dest = (u32 *) alsa_rt->dma_area;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* call with substream locked */
अटल व्योम usb6fire_pcm_playback(काष्ठा pcm_substream *sub,
		काष्ठा pcm_urb *urb)
अणु
	पूर्णांक i;
	पूर्णांक frame;
	पूर्णांक frame_count;
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(sub->instance);
	काष्ठा snd_pcm_runसमय *alsa_rt = sub->instance->runसमय;
	u32 *src = (u32 *) (alsa_rt->dma_area + sub->dma_off
			* (alsa_rt->frame_bits >> 3));
	u32 *src_end = (u32 *) (alsa_rt->dma_area + alsa_rt->buffer_size
			* (alsa_rt->frame_bits >> 3));
	u32 *dest;
	पूर्णांक bytes_per_frame = alsa_rt->channels << 2;

	अगर (alsa_rt->क्रमmat == SNDRV_PCM_FORMAT_S32_LE)
		dest = (u32 *) (urb->buffer - 1);
	अन्यथा अगर (alsa_rt->क्रमmat == SNDRV_PCM_FORMAT_S24_LE)
		dest = (u32 *) (urb->buffer);
	अन्यथा अणु
		dev_err(&rt->chip->dev->dev, "Unknown sample format.");
		वापस;
	पूर्ण

	क्रम (i = 0; i < PCM_N_PACKETS_PER_URB; i++) अणु
		/* at least 4 header bytes क्रम valid packet.
		 * after that: 32 bits per sample क्रम analog channels */
		अगर (urb->packets[i].length > 4)
			frame_count = (urb->packets[i].length - 4)
					/ (rt->out_n_analog << 2);
		अन्यथा
			frame_count = 0;
		dest++; /* skip leading 4 bytes of every frame */
		क्रम (frame = 0; frame < frame_count; frame++) अणु
			स_नकल(dest, src, bytes_per_frame);
			src += alsa_rt->channels;
			dest += rt->out_n_analog;
			sub->dma_off++;
			sub->period_off++;
			अगर (src == src_end) अणु
				src = (u32 *) alsa_rt->dma_area;
				sub->dma_off = 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usb6fire_pcm_in_urb_handler(काष्ठा urb *usb_urb)
अणु
	काष्ठा pcm_urb *in_urb = usb_urb->context;
	काष्ठा pcm_urb *out_urb = in_urb->peer;
	काष्ठा pcm_runसमय *rt = in_urb->chip->pcm;
	काष्ठा pcm_substream *sub;
	अचिन्हित दीर्घ flags;
	पूर्णांक total_length = 0;
	पूर्णांक frame_count;
	पूर्णांक frame;
	पूर्णांक channel;
	पूर्णांक i;
	u8 *dest;

	अगर (usb_urb->status || rt->panic || rt->stream_state == STREAM_STOPPING)
		वापस;
	क्रम (i = 0; i < PCM_N_PACKETS_PER_URB; i++)
		अगर (in_urb->packets[i].status) अणु
			rt->panic = true;
			वापस;
		पूर्ण

	अगर (rt->stream_state == STREAM_DISABLED) अणु
		dev_err(&rt->chip->dev->dev,
			"internal error: stream disabled in in-urb handler.\n");
		वापस;
	पूर्ण

	/* receive our capture data */
	sub = &rt->capture;
	spin_lock_irqsave(&sub->lock, flags);
	अगर (sub->active) अणु
		usb6fire_pcm_capture(sub, in_urb);
		अगर (sub->period_off >= sub->instance->runसमय->period_size) अणु
			sub->period_off %= sub->instance->runसमय->period_size;
			spin_unlock_irqrestore(&sub->lock, flags);
			snd_pcm_period_elapsed(sub->instance);
		पूर्ण अन्यथा
			spin_unlock_irqrestore(&sub->lock, flags);
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&sub->lock, flags);

	/* setup out urb काष्ठाure */
	क्रम (i = 0; i < PCM_N_PACKETS_PER_URB; i++) अणु
		out_urb->packets[i].offset = total_length;
		out_urb->packets[i].length = (in_urb->packets[i].actual_length
				- 4) / (rt->in_n_analog << 2)
				* (rt->out_n_analog << 2) + 4;
		out_urb->packets[i].status = 0;
		total_length += out_urb->packets[i].length;
	पूर्ण
	स_रखो(out_urb->buffer, 0, total_length);

	/* now send our playback data (अगर a मुक्त out urb was found) */
	sub = &rt->playback;
	spin_lock_irqsave(&sub->lock, flags);
	अगर (sub->active) अणु
		usb6fire_pcm_playback(sub, out_urb);
		अगर (sub->period_off >= sub->instance->runसमय->period_size) अणु
			sub->period_off %= sub->instance->runसमय->period_size;
			spin_unlock_irqrestore(&sub->lock, flags);
			snd_pcm_period_elapsed(sub->instance);
		पूर्ण अन्यथा
			spin_unlock_irqrestore(&sub->lock, flags);
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&sub->lock, flags);

	/* setup the 4th byte of each sample (0x40 क्रम analog channels) */
	dest = out_urb->buffer;
	क्रम (i = 0; i < PCM_N_PACKETS_PER_URB; i++)
		अगर (out_urb->packets[i].length >= 4) अणु
			frame_count = (out_urb->packets[i].length - 4)
					/ (rt->out_n_analog << 2);
			*(dest++) = 0xaa;
			*(dest++) = 0xaa;
			*(dest++) = frame_count;
			*(dest++) = 0x00;
			क्रम (frame = 0; frame < frame_count; frame++)
				क्रम (channel = 0;
						channel < rt->out_n_analog;
						channel++) अणु
					dest += 3; /* skip sample data */
					*(dest++) = 0x40;
				पूर्ण
		पूर्ण
	usb_submit_urb(&out_urb->instance, GFP_ATOMIC);
	usb_submit_urb(&in_urb->instance, GFP_ATOMIC);
पूर्ण

अटल व्योम usb6fire_pcm_out_urb_handler(काष्ठा urb *usb_urb)
अणु
	काष्ठा pcm_urb *urb = usb_urb->context;
	काष्ठा pcm_runसमय *rt = urb->chip->pcm;

	अगर (rt->stream_state == STREAM_STARTING) अणु
		rt->stream_रुको_cond = true;
		wake_up(&rt->stream_रुको_queue);
	पूर्ण
पूर्ण

अटल पूर्णांक usb6fire_pcm_खोलो(काष्ठा snd_pcm_substream *alsa_sub)
अणु
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(alsa_sub);
	काष्ठा pcm_substream *sub = शून्य;
	काष्ठा snd_pcm_runसमय *alsa_rt = alsa_sub->runसमय;

	अगर (rt->panic)
		वापस -EPIPE;

	mutex_lock(&rt->stream_mutex);
	alsa_rt->hw = pcm_hw;

	अगर (alsa_sub->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (rt->rate < ARRAY_SIZE(rates))
			alsa_rt->hw.rates = rates_alsaid[rt->rate];
		alsa_rt->hw.channels_max = OUT_N_CHANNELS;
		sub = &rt->playback;
	पूर्ण अन्यथा अगर (alsa_sub->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		अगर (rt->rate < ARRAY_SIZE(rates))
			alsa_rt->hw.rates = rates_alsaid[rt->rate];
		alsa_rt->hw.channels_max = IN_N_CHANNELS;
		sub = &rt->capture;
	पूर्ण

	अगर (!sub) अणु
		mutex_unlock(&rt->stream_mutex);
		dev_err(&rt->chip->dev->dev, "invalid stream type.\n");
		वापस -EINVAL;
	पूर्ण

	sub->instance = alsa_sub;
	sub->active = false;
	mutex_unlock(&rt->stream_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_pcm_बंद(काष्ठा snd_pcm_substream *alsa_sub)
अणु
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(alsa_sub);
	काष्ठा pcm_substream *sub = usb6fire_pcm_get_substream(alsa_sub);
	अचिन्हित दीर्घ flags;

	अगर (rt->panic)
		वापस 0;

	mutex_lock(&rt->stream_mutex);
	अगर (sub) अणु
		/* deactivate substream */
		spin_lock_irqsave(&sub->lock, flags);
		sub->instance = शून्य;
		sub->active = false;
		spin_unlock_irqrestore(&sub->lock, flags);

		/* all substreams बंदd? अगर so, stop streaming */
		अगर (!rt->playback.instance && !rt->capture.instance) अणु
			usb6fire_pcm_stream_stop(rt);
			rt->rate = ARRAY_SIZE(rates);
		पूर्ण
	पूर्ण
	mutex_unlock(&rt->stream_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_pcm_prepare(काष्ठा snd_pcm_substream *alsa_sub)
अणु
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(alsa_sub);
	काष्ठा pcm_substream *sub = usb6fire_pcm_get_substream(alsa_sub);
	काष्ठा snd_pcm_runसमय *alsa_rt = alsa_sub->runसमय;
	पूर्णांक ret;

	अगर (rt->panic)
		वापस -EPIPE;
	अगर (!sub)
		वापस -ENODEV;

	mutex_lock(&rt->stream_mutex);
	sub->dma_off = 0;
	sub->period_off = 0;

	अगर (rt->stream_state == STREAM_DISABLED) अणु
		क्रम (rt->rate = 0; rt->rate < ARRAY_SIZE(rates); rt->rate++)
			अगर (alsa_rt->rate == rates[rt->rate])
				अवरोध;
		अगर (rt->rate == ARRAY_SIZE(rates)) अणु
			mutex_unlock(&rt->stream_mutex);
			dev_err(&rt->chip->dev->dev,
				"invalid rate %d in prepare.\n",
				alsa_rt->rate);
			वापस -EINVAL;
		पूर्ण

		ret = usb6fire_pcm_set_rate(rt);
		अगर (ret) अणु
			mutex_unlock(&rt->stream_mutex);
			वापस ret;
		पूर्ण
		ret = usb6fire_pcm_stream_start(rt);
		अगर (ret) अणु
			mutex_unlock(&rt->stream_mutex);
			dev_err(&rt->chip->dev->dev,
				"could not start pcm stream.\n");
			वापस ret;
		पूर्ण
	पूर्ण
	mutex_unlock(&rt->stream_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_pcm_trigger(काष्ठा snd_pcm_substream *alsa_sub, पूर्णांक cmd)
अणु
	काष्ठा pcm_substream *sub = usb6fire_pcm_get_substream(alsa_sub);
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(alsa_sub);
	अचिन्हित दीर्घ flags;

	अगर (rt->panic)
		वापस -EPIPE;
	अगर (!sub)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		spin_lock_irqsave(&sub->lock, flags);
		sub->active = true;
		spin_unlock_irqrestore(&sub->lock, flags);
		वापस 0;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		spin_lock_irqsave(&sub->lock, flags);
		sub->active = false;
		spin_unlock_irqrestore(&sub->lock, flags);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल snd_pcm_uframes_t usb6fire_pcm_poपूर्णांकer(
		काष्ठा snd_pcm_substream *alsa_sub)
अणु
	काष्ठा pcm_substream *sub = usb6fire_pcm_get_substream(alsa_sub);
	काष्ठा pcm_runसमय *rt = snd_pcm_substream_chip(alsa_sub);
	अचिन्हित दीर्घ flags;
	snd_pcm_uframes_t ret;

	अगर (rt->panic || !sub)
		वापस SNDRV_PCM_POS_XRUN;

	spin_lock_irqsave(&sub->lock, flags);
	ret = sub->dma_off;
	spin_unlock_irqrestore(&sub->lock, flags);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops pcm_ops = अणु
	.खोलो = usb6fire_pcm_खोलो,
	.बंद = usb6fire_pcm_बंद,
	.prepare = usb6fire_pcm_prepare,
	.trigger = usb6fire_pcm_trigger,
	.poपूर्णांकer = usb6fire_pcm_poपूर्णांकer,
पूर्ण;

अटल व्योम usb6fire_pcm_init_urb(काष्ठा pcm_urb *urb,
				  काष्ठा sfire_chip *chip, bool in, पूर्णांक ep,
				  व्योम (*handler)(काष्ठा urb *))
अणु
	urb->chip = chip;
	usb_init_urb(&urb->instance);
	urb->instance.transfer_buffer = urb->buffer;
	urb->instance.transfer_buffer_length =
			PCM_N_PACKETS_PER_URB * PCM_MAX_PACKET_SIZE;
	urb->instance.dev = chip->dev;
	urb->instance.pipe = in ? usb_rcvisocpipe(chip->dev, ep)
			: usb_sndisocpipe(chip->dev, ep);
	urb->instance.पूर्णांकerval = 1;
	urb->instance.complete = handler;
	urb->instance.context = urb;
	urb->instance.number_of_packets = PCM_N_PACKETS_PER_URB;
पूर्ण

अटल पूर्णांक usb6fire_pcm_buffers_init(काष्ठा pcm_runसमय *rt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCM_N_URBS; i++) अणु
		rt->out_urbs[i].buffer = kसुस्मृति(PCM_MAX_PACKET_SIZE,
						 PCM_N_PACKETS_PER_URB,
						 GFP_KERNEL);
		अगर (!rt->out_urbs[i].buffer)
			वापस -ENOMEM;
		rt->in_urbs[i].buffer = kसुस्मृति(PCM_MAX_PACKET_SIZE,
						PCM_N_PACKETS_PER_URB,
						GFP_KERNEL);
		अगर (!rt->in_urbs[i].buffer)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम usb6fire_pcm_buffers_destroy(काष्ठा pcm_runसमय *rt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCM_N_URBS; i++) अणु
		kमुक्त(rt->out_urbs[i].buffer);
		kमुक्त(rt->in_urbs[i].buffer);
	पूर्ण
पूर्ण

पूर्णांक usb6fire_pcm_init(काष्ठा sfire_chip *chip)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा snd_pcm *pcm;
	काष्ठा pcm_runसमय *rt =
			kzalloc(माप(काष्ठा pcm_runसमय), GFP_KERNEL);

	अगर (!rt)
		वापस -ENOMEM;

	ret = usb6fire_pcm_buffers_init(rt);
	अगर (ret) अणु
		usb6fire_pcm_buffers_destroy(rt);
		kमुक्त(rt);
		वापस ret;
	पूर्ण

	rt->chip = chip;
	rt->stream_state = STREAM_DISABLED;
	rt->rate = ARRAY_SIZE(rates);
	init_रुकोqueue_head(&rt->stream_रुको_queue);
	mutex_init(&rt->stream_mutex);

	spin_lock_init(&rt->playback.lock);
	spin_lock_init(&rt->capture.lock);

	क्रम (i = 0; i < PCM_N_URBS; i++) अणु
		usb6fire_pcm_init_urb(&rt->in_urbs[i], chip, true, IN_EP,
				usb6fire_pcm_in_urb_handler);
		usb6fire_pcm_init_urb(&rt->out_urbs[i], chip, false, OUT_EP,
				usb6fire_pcm_out_urb_handler);

		rt->in_urbs[i].peer = &rt->out_urbs[i];
		rt->out_urbs[i].peer = &rt->in_urbs[i];
	पूर्ण

	ret = snd_pcm_new(chip->card, "DMX6FireUSB", 0, 1, 1, &pcm);
	अगर (ret < 0) अणु
		usb6fire_pcm_buffers_destroy(rt);
		kमुक्त(rt);
		dev_err(&chip->dev->dev, "cannot create pcm instance.\n");
		वापस ret;
	पूर्ण

	pcm->निजी_data = rt;
	म_नकल(pcm->name, "DMX 6Fire USB");
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &pcm_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &pcm_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);

	rt->instance = pcm;

	chip->pcm = rt;
	वापस 0;
पूर्ण

व्योम usb6fire_pcm_पात(काष्ठा sfire_chip *chip)
अणु
	काष्ठा pcm_runसमय *rt = chip->pcm;
	पूर्णांक i;

	अगर (rt) अणु
		rt->panic = true;

		अगर (rt->playback.instance)
			snd_pcm_stop_xrun(rt->playback.instance);

		अगर (rt->capture.instance)
			snd_pcm_stop_xrun(rt->capture.instance);

		क्रम (i = 0; i < PCM_N_URBS; i++) अणु
			usb_poison_urb(&rt->in_urbs[i].instance);
			usb_poison_urb(&rt->out_urbs[i].instance);
		पूर्ण

	पूर्ण
पूर्ण

व्योम usb6fire_pcm_destroy(काष्ठा sfire_chip *chip)
अणु
	काष्ठा pcm_runसमय *rt = chip->pcm;

	usb6fire_pcm_buffers_destroy(rt);
	kमुक्त(rt);
	chip->pcm = शून्य;
पूर्ण
