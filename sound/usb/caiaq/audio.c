<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (c) 2006-2008 Daniel Mack, Karsten Wiese
*/

#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/usb.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>

#समावेश "device.h"
#समावेश "audio.h"

#घोषणा N_URBS			32
#घोषणा CLOCK_DRIFT_TOLERANCE	5
#घोषणा FRAMES_PER_URB		8
#घोषणा BYTES_PER_FRAME		512
#घोषणा CHANNELS_PER_STREAM	2
#घोषणा BYTES_PER_SAMPLE	3
#घोषणा BYTES_PER_SAMPLE_USB	4
#घोषणा MAX_BUFFER_SIZE		(128*1024)
#घोषणा MAX_ENDPOINT_SIZE	512

#घोषणा ENDPOINT_CAPTURE	2
#घोषणा ENDPOINT_PLAYBACK	6

#घोषणा MAKE_CHECKBYTE(cdev,stream,i) \
	(stream << 1) | (~(i / (cdev->n_streams * BYTES_PER_SAMPLE_USB)) & 1)

अटल स्थिर काष्ठा snd_pcm_hardware snd_usb_caiaq_pcm_hardware = अणु
	.info 		= (SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
			   SNDRV_PCM_INFO_BLOCK_TRANSFER),
	.क्रमmats 	= SNDRV_PCM_FMTBIT_S24_3BE,
	.rates 		= (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |
			   SNDRV_PCM_RATE_96000),
	.rate_min	= 44100,
	.rate_max	= 0, /* will overग_लिखो later */
	.channels_min	= CHANNELS_PER_STREAM,
	.channels_max	= CHANNELS_PER_STREAM,
	.buffer_bytes_max = MAX_BUFFER_SIZE,
	.period_bytes_min = 128,
	.period_bytes_max = MAX_BUFFER_SIZE,
	.periods_min	= 1,
	.periods_max	= 1024,
पूर्ण;

अटल व्योम
activate_substream(काष्ठा snd_usb_caiaqdev *cdev,
	           काष्ठा snd_pcm_substream *sub)
अणु
	spin_lock(&cdev->spinlock);

	अगर (sub->stream == SNDRV_PCM_STREAM_PLAYBACK)
		cdev->sub_playback[sub->number] = sub;
	अन्यथा
		cdev->sub_capture[sub->number] = sub;

	spin_unlock(&cdev->spinlock);
पूर्ण

अटल व्योम
deactivate_substream(काष्ठा snd_usb_caiaqdev *cdev,
		     काष्ठा snd_pcm_substream *sub)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&cdev->spinlock, flags);

	अगर (sub->stream == SNDRV_PCM_STREAM_PLAYBACK)
		cdev->sub_playback[sub->number] = शून्य;
	अन्यथा
		cdev->sub_capture[sub->number] = शून्य;

	spin_unlock_irqrestore(&cdev->spinlock, flags);
पूर्ण

अटल पूर्णांक
all_substreams_zero(काष्ठा snd_pcm_substream **subs)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < MAX_STREAMS; i++)
		अगर (subs[i] != शून्य)
			वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक stream_start(काष्ठा snd_usb_caiaqdev *cdev)
अणु
	पूर्णांक i, ret;
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p)\n", __func__, cdev);

	अगर (cdev->streaming)
		वापस -EINVAL;

	स_रखो(cdev->sub_playback, 0, माप(cdev->sub_playback));
	स_रखो(cdev->sub_capture, 0, माप(cdev->sub_capture));
	cdev->input_panic = 0;
	cdev->output_panic = 0;
	cdev->first_packet = 4;
	cdev->streaming = 1;
	cdev->warned = 0;

	क्रम (i = 0; i < N_URBS; i++) अणु
		ret = usb_submit_urb(cdev->data_urbs_in[i], GFP_ATOMIC);
		अगर (ret) अणु
			dev_err(dev, "unable to trigger read #%d! (ret %d)\n",
				i, ret);
			cdev->streaming = 0;
			वापस -EPIPE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम stream_stop(काष्ठा snd_usb_caiaqdev *cdev)
अणु
	पूर्णांक i;
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p)\n", __func__, cdev);
	अगर (!cdev->streaming)
		वापस;

	cdev->streaming = 0;

	क्रम (i = 0; i < N_URBS; i++) अणु
		usb_समाप्त_urb(cdev->data_urbs_in[i]);

		अगर (test_bit(i, &cdev->outurb_active_mask))
			usb_समाप्त_urb(cdev->data_urbs_out[i]);
	पूर्ण

	cdev->outurb_active_mask = 0;
पूर्ण

अटल पूर्णांक snd_usb_caiaq_substream_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_usb_caiaqdev *cdev = snd_pcm_substream_chip(substream);
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p)\n", __func__, substream);
	substream->runसमय->hw = cdev->pcm_info;
	snd_pcm_limit_hw_rates(substream->runसमय);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_usb_caiaq_substream_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_usb_caiaqdev *cdev = snd_pcm_substream_chip(substream);
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p)\n", __func__, substream);
	अगर (all_substreams_zero(cdev->sub_playback) &&
	    all_substreams_zero(cdev->sub_capture)) अणु
		/* when the last client has stopped streaming,
		 * all sample rates are allowed again */
		stream_stop(cdev);
		cdev->pcm_info.rates = cdev->samplerates;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_usb_caiaq_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *sub)
अणु
	काष्ठा snd_usb_caiaqdev *cdev = snd_pcm_substream_chip(sub);
	deactivate_substream(cdev, sub);
	वापस 0;
पूर्ण

/* this should probably go upstream */
#अगर SNDRV_PCM_RATE_5512 != 1 << 0 || SNDRV_PCM_RATE_192000 != 1 << 12
#त्रुटि "Change this table"
#पूर्ण_अगर

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु 5512, 8000, 11025, 16000, 22050, 32000, 44100,
				48000, 64000, 88200, 96000, 176400, 192000 पूर्ण;

अटल पूर्णांक snd_usb_caiaq_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक bytes_per_sample, bpp, ret, i;
	पूर्णांक index = substream->number;
	काष्ठा snd_usb_caiaqdev *cdev = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p)\n", __func__, substream);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		पूर्णांक out_pos;

		चयन (cdev->spec.data_alignment) अणु
		हाल 0:
		हाल 2:
			out_pos = BYTES_PER_SAMPLE + 1;
			अवरोध;
		हाल 3:
		शेष:
			out_pos = 0;
			अवरोध;
		पूर्ण

		cdev->period_out_count[index] = out_pos;
		cdev->audio_out_buf_pos[index] = out_pos;
	पूर्ण अन्यथा अणु
		पूर्णांक in_pos;

		चयन (cdev->spec.data_alignment) अणु
		हाल 0:
			in_pos = BYTES_PER_SAMPLE + 2;
			अवरोध;
		हाल 2:
			in_pos = BYTES_PER_SAMPLE;
			अवरोध;
		हाल 3:
		शेष:
			in_pos = 0;
			अवरोध;
		पूर्ण

		cdev->period_in_count[index] = in_pos;
		cdev->audio_in_buf_pos[index] = in_pos;
	पूर्ण

	अगर (cdev->streaming)
		वापस 0;

	/* the first client that खोलोs a stream defines the sample rate
	 * setting क्रम all subsequent calls, until the last client बंदd. */
	क्रम (i=0; i < ARRAY_SIZE(rates); i++)
		अगर (runसमय->rate == rates[i])
			cdev->pcm_info.rates = 1 << i;

	snd_pcm_limit_hw_rates(runसमय);

	bytes_per_sample = BYTES_PER_SAMPLE;
	अगर (cdev->spec.data_alignment >= 2)
		bytes_per_sample++;

	bpp = ((runसमय->rate / 8000) + CLOCK_DRIFT_TOLERANCE)
		* bytes_per_sample * CHANNELS_PER_STREAM * cdev->n_streams;

	अगर (bpp > MAX_ENDPOINT_SIZE)
		bpp = MAX_ENDPOINT_SIZE;

	ret = snd_usb_caiaq_set_audio_params(cdev, runसमय->rate,
					     runसमय->sample_bits, bpp);
	अगर (ret)
		वापस ret;

	ret = stream_start(cdev);
	अगर (ret)
		वापस ret;

	cdev->output_running = 0;
	रुको_event_समयout(cdev->prepare_रुको_queue, cdev->output_running, HZ);
	अगर (!cdev->output_running) अणु
		stream_stop(cdev);
		वापस -EPIPE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_usb_caiaq_pcm_trigger(काष्ठा snd_pcm_substream *sub, पूर्णांक cmd)
अणु
	काष्ठा snd_usb_caiaqdev *cdev = snd_pcm_substream_chip(sub);
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p) cmd %d\n", __func__, sub, cmd);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		activate_substream(cdev, sub);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		deactivate_substream(cdev, sub);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
snd_usb_caiaq_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *sub)
अणु
	पूर्णांक index = sub->number;
	काष्ठा snd_usb_caiaqdev *cdev = snd_pcm_substream_chip(sub);
	snd_pcm_uframes_t ptr;

	spin_lock(&cdev->spinlock);

	अगर (cdev->input_panic || cdev->output_panic) अणु
		ptr = SNDRV_PCM_POS_XRUN;
		जाओ unlock;
	पूर्ण

	अगर (sub->stream == SNDRV_PCM_STREAM_PLAYBACK)
		ptr = bytes_to_frames(sub->runसमय,
					cdev->audio_out_buf_pos[index]);
	अन्यथा
		ptr = bytes_to_frames(sub->runसमय,
					cdev->audio_in_buf_pos[index]);

unlock:
	spin_unlock(&cdev->spinlock);
	वापस ptr;
पूर्ण

/* चालकs क्रम both playback and capture */
अटल स्थिर काष्ठा snd_pcm_ops snd_usb_caiaq_ops = अणु
	.खोलो =		snd_usb_caiaq_substream_खोलो,
	.बंद =	snd_usb_caiaq_substream_बंद,
	.hw_मुक्त =	snd_usb_caiaq_pcm_hw_मुक्त,
	.prepare =	snd_usb_caiaq_pcm_prepare,
	.trigger =	snd_usb_caiaq_pcm_trigger,
	.poपूर्णांकer =	snd_usb_caiaq_pcm_poपूर्णांकer,
पूर्ण;

अटल व्योम check_क्रम_elapsed_periods(काष्ठा snd_usb_caiaqdev *cdev,
				      काष्ठा snd_pcm_substream **subs)
अणु
	पूर्णांक stream, pb, *cnt;
	काष्ठा snd_pcm_substream *sub;

	क्रम (stream = 0; stream < cdev->n_streams; stream++) अणु
		sub = subs[stream];
		अगर (!sub)
			जारी;

		pb = snd_pcm_lib_period_bytes(sub);
		cnt = (sub->stream == SNDRV_PCM_STREAM_PLAYBACK) ?
					&cdev->period_out_count[stream] :
					&cdev->period_in_count[stream];

		अगर (*cnt >= pb) अणु
			snd_pcm_period_elapsed(sub);
			*cnt %= pb;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_in_urb_mode0(काष्ठा snd_usb_caiaqdev *cdev,
			      स्थिर काष्ठा urb *urb,
			      स्थिर काष्ठा usb_iso_packet_descriptor *iso)
अणु
	अचिन्हित अक्षर *usb_buf = urb->transfer_buffer + iso->offset;
	काष्ठा snd_pcm_substream *sub;
	पूर्णांक stream, i;

	अगर (all_substreams_zero(cdev->sub_capture))
		वापस;

	क्रम (i = 0; i < iso->actual_length;) अणु
		क्रम (stream = 0; stream < cdev->n_streams; stream++, i++) अणु
			sub = cdev->sub_capture[stream];
			अगर (sub) अणु
				काष्ठा snd_pcm_runसमय *rt = sub->runसमय;
				अक्षर *audio_buf = rt->dma_area;
				पूर्णांक sz = frames_to_bytes(rt, rt->buffer_size);
				audio_buf[cdev->audio_in_buf_pos[stream]++]
					= usb_buf[i];
				cdev->period_in_count[stream]++;
				अगर (cdev->audio_in_buf_pos[stream] == sz)
					cdev->audio_in_buf_pos[stream] = 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_in_urb_mode2(काष्ठा snd_usb_caiaqdev *cdev,
			      स्थिर काष्ठा urb *urb,
			      स्थिर काष्ठा usb_iso_packet_descriptor *iso)
अणु
	अचिन्हित अक्षर *usb_buf = urb->transfer_buffer + iso->offset;
	अचिन्हित अक्षर check_byte;
	काष्ठा snd_pcm_substream *sub;
	पूर्णांक stream, i;

	क्रम (i = 0; i < iso->actual_length;) अणु
		अगर (i % (cdev->n_streams * BYTES_PER_SAMPLE_USB) == 0) अणु
			क्रम (stream = 0;
			     stream < cdev->n_streams;
			     stream++, i++) अणु
				अगर (cdev->first_packet)
					जारी;

				check_byte = MAKE_CHECKBYTE(cdev, stream, i);

				अगर ((usb_buf[i] & 0x3f) != check_byte)
					cdev->input_panic = 1;

				अगर (usb_buf[i] & 0x80)
					cdev->output_panic = 1;
			पूर्ण
		पूर्ण
		cdev->first_packet = 0;

		क्रम (stream = 0; stream < cdev->n_streams; stream++, i++) अणु
			sub = cdev->sub_capture[stream];
			अगर (cdev->input_panic)
				usb_buf[i] = 0;

			अगर (sub) अणु
				काष्ठा snd_pcm_runसमय *rt = sub->runसमय;
				अक्षर *audio_buf = rt->dma_area;
				पूर्णांक sz = frames_to_bytes(rt, rt->buffer_size);
				audio_buf[cdev->audio_in_buf_pos[stream]++] =
					usb_buf[i];
				cdev->period_in_count[stream]++;
				अगर (cdev->audio_in_buf_pos[stream] == sz)
					cdev->audio_in_buf_pos[stream] = 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_in_urb_mode3(काष्ठा snd_usb_caiaqdev *cdev,
			      स्थिर काष्ठा urb *urb,
			      स्थिर काष्ठा usb_iso_packet_descriptor *iso)
अणु
	अचिन्हित अक्षर *usb_buf = urb->transfer_buffer + iso->offset;
	काष्ठा device *dev = caiaqdev_to_dev(cdev);
	पूर्णांक stream, i;

	/* paranoia check */
	अगर (iso->actual_length % (BYTES_PER_SAMPLE_USB * CHANNELS_PER_STREAM))
		वापस;

	क्रम (i = 0; i < iso->actual_length;) अणु
		क्रम (stream = 0; stream < cdev->n_streams; stream++) अणु
			काष्ठा snd_pcm_substream *sub = cdev->sub_capture[stream];
			अक्षर *audio_buf = शून्य;
			पूर्णांक c, n, sz = 0;

			अगर (sub && !cdev->input_panic) अणु
				काष्ठा snd_pcm_runसमय *rt = sub->runसमय;
				audio_buf = rt->dma_area;
				sz = frames_to_bytes(rt, rt->buffer_size);
			पूर्ण

			क्रम (c = 0; c < CHANNELS_PER_STREAM; c++) अणु
				/* 3 audio data bytes, followed by 1 check byte */
				अगर (audio_buf) अणु
					क्रम (n = 0; n < BYTES_PER_SAMPLE; n++) अणु
						audio_buf[cdev->audio_in_buf_pos[stream]++] = usb_buf[i+n];

						अगर (cdev->audio_in_buf_pos[stream] == sz)
							cdev->audio_in_buf_pos[stream] = 0;
					पूर्ण

					cdev->period_in_count[stream] += BYTES_PER_SAMPLE;
				पूर्ण

				i += BYTES_PER_SAMPLE;

				अगर (usb_buf[i] != ((stream << 1) | c) &&
				    !cdev->first_packet) अणु
					अगर (!cdev->input_panic)
						dev_warn(dev, " EXPECTED: %02x got %02x, c %d, stream %d, i %d\n",
							 ((stream << 1) | c), usb_buf[i], c, stream, i);
					cdev->input_panic = 1;
				पूर्ण

				i++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (cdev->first_packet > 0)
		cdev->first_packet--;
पूर्ण

अटल व्योम पढ़ो_in_urb(काष्ठा snd_usb_caiaqdev *cdev,
			स्थिर काष्ठा urb *urb,
			स्थिर काष्ठा usb_iso_packet_descriptor *iso)
अणु
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	अगर (!cdev->streaming)
		वापस;

	अगर (iso->actual_length < cdev->bpp)
		वापस;

	चयन (cdev->spec.data_alignment) अणु
	हाल 0:
		पढ़ो_in_urb_mode0(cdev, urb, iso);
		अवरोध;
	हाल 2:
		पढ़ो_in_urb_mode2(cdev, urb, iso);
		अवरोध;
	हाल 3:
		पढ़ो_in_urb_mode3(cdev, urb, iso);
		अवरोध;
	पूर्ण

	अगर ((cdev->input_panic || cdev->output_panic) && !cdev->warned) अणु
		dev_warn(dev, "streaming error detected %s %s\n",
				cdev->input_panic ? "(input)" : "",
				cdev->output_panic ? "(output)" : "");
		cdev->warned = 1;
	पूर्ण
पूर्ण

अटल व्योम fill_out_urb_mode_0(काष्ठा snd_usb_caiaqdev *cdev,
				काष्ठा urb *urb,
				स्थिर काष्ठा usb_iso_packet_descriptor *iso)
अणु
	अचिन्हित अक्षर *usb_buf = urb->transfer_buffer + iso->offset;
	काष्ठा snd_pcm_substream *sub;
	पूर्णांक stream, i;

	क्रम (i = 0; i < iso->length;) अणु
		क्रम (stream = 0; stream < cdev->n_streams; stream++, i++) अणु
			sub = cdev->sub_playback[stream];
			अगर (sub) अणु
				काष्ठा snd_pcm_runसमय *rt = sub->runसमय;
				अक्षर *audio_buf = rt->dma_area;
				पूर्णांक sz = frames_to_bytes(rt, rt->buffer_size);
				usb_buf[i] =
					audio_buf[cdev->audio_out_buf_pos[stream]];
				cdev->period_out_count[stream]++;
				cdev->audio_out_buf_pos[stream]++;
				अगर (cdev->audio_out_buf_pos[stream] == sz)
					cdev->audio_out_buf_pos[stream] = 0;
			पूर्ण अन्यथा
				usb_buf[i] = 0;
		पूर्ण

		/* fill in the check bytes */
		अगर (cdev->spec.data_alignment == 2 &&
		    i % (cdev->n_streams * BYTES_PER_SAMPLE_USB) ==
		        (cdev->n_streams * CHANNELS_PER_STREAM))
			क्रम (stream = 0; stream < cdev->n_streams; stream++, i++)
				usb_buf[i] = MAKE_CHECKBYTE(cdev, stream, i);
	पूर्ण
पूर्ण

अटल व्योम fill_out_urb_mode_3(काष्ठा snd_usb_caiaqdev *cdev,
				काष्ठा urb *urb,
				स्थिर काष्ठा usb_iso_packet_descriptor *iso)
अणु
	अचिन्हित अक्षर *usb_buf = urb->transfer_buffer + iso->offset;
	पूर्णांक stream, i;

	क्रम (i = 0; i < iso->length;) अणु
		क्रम (stream = 0; stream < cdev->n_streams; stream++) अणु
			काष्ठा snd_pcm_substream *sub = cdev->sub_playback[stream];
			अक्षर *audio_buf = शून्य;
			पूर्णांक c, n, sz = 0;

			अगर (sub) अणु
				काष्ठा snd_pcm_runसमय *rt = sub->runसमय;
				audio_buf = rt->dma_area;
				sz = frames_to_bytes(rt, rt->buffer_size);
			पूर्ण

			क्रम (c = 0; c < CHANNELS_PER_STREAM; c++) अणु
				क्रम (n = 0; n < BYTES_PER_SAMPLE; n++) अणु
					अगर (audio_buf) अणु
						usb_buf[i+n] = audio_buf[cdev->audio_out_buf_pos[stream]++];

						अगर (cdev->audio_out_buf_pos[stream] == sz)
							cdev->audio_out_buf_pos[stream] = 0;
					पूर्ण अन्यथा अणु
						usb_buf[i+n] = 0;
					पूर्ण
				पूर्ण

				अगर (audio_buf)
					cdev->period_out_count[stream] += BYTES_PER_SAMPLE;

				i += BYTES_PER_SAMPLE;

				/* fill in the check byte pattern */
				usb_buf[i++] = (stream << 1) | c;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम fill_out_urb(काष्ठा snd_usb_caiaqdev *cdev,
				काष्ठा urb *urb,
				स्थिर काष्ठा usb_iso_packet_descriptor *iso)
अणु
	चयन (cdev->spec.data_alignment) अणु
	हाल 0:
	हाल 2:
		fill_out_urb_mode_0(cdev, urb, iso);
		अवरोध;
	हाल 3:
		fill_out_urb_mode_3(cdev, urb, iso);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_completed(काष्ठा urb *urb)
अणु
	काष्ठा snd_usb_caiaq_cb_info *info = urb->context;
	काष्ठा snd_usb_caiaqdev *cdev;
	काष्ठा device *dev;
	काष्ठा urb *out = शून्य;
	पूर्णांक i, frame, len, send_it = 0, outframe = 0;
	अचिन्हित दीर्घ flags;
	माप_प्रकार offset = 0;

	अगर (urb->status || !info)
		वापस;

	cdev = info->cdev;
	dev = caiaqdev_to_dev(cdev);

	अगर (!cdev->streaming)
		वापस;

	/* find an unused output urb that is unused */
	क्रम (i = 0; i < N_URBS; i++)
		अगर (test_and_set_bit(i, &cdev->outurb_active_mask) == 0) अणु
			out = cdev->data_urbs_out[i];
			अवरोध;
		पूर्ण

	अगर (!out) अणु
		dev_err(dev, "Unable to find an output urb to use\n");
		जाओ requeue;
	पूर्ण

	/* पढ़ो the recently received packet and send back one which has
	 * the same layout */
	क्रम (frame = 0; frame < FRAMES_PER_URB; frame++) अणु
		अगर (urb->iso_frame_desc[frame].status)
			जारी;

		len = urb->iso_frame_desc[outframe].actual_length;
		out->iso_frame_desc[outframe].length = len;
		out->iso_frame_desc[outframe].actual_length = 0;
		out->iso_frame_desc[outframe].offset = offset;
		offset += len;

		अगर (len > 0) अणु
			spin_lock_irqsave(&cdev->spinlock, flags);
			fill_out_urb(cdev, out, &out->iso_frame_desc[outframe]);
			पढ़ो_in_urb(cdev, urb, &urb->iso_frame_desc[frame]);
			spin_unlock_irqrestore(&cdev->spinlock, flags);
			check_क्रम_elapsed_periods(cdev, cdev->sub_playback);
			check_क्रम_elapsed_periods(cdev, cdev->sub_capture);
			send_it = 1;
		पूर्ण

		outframe++;
	पूर्ण

	अगर (send_it) अणु
		out->number_of_packets = outframe;
		usb_submit_urb(out, GFP_ATOMIC);
	पूर्ण अन्यथा अणु
		काष्ठा snd_usb_caiaq_cb_info *oinfo = out->context;
		clear_bit(oinfo->index, &cdev->outurb_active_mask);
	पूर्ण

requeue:
	/* re-submit inbound urb */
	क्रम (frame = 0; frame < FRAMES_PER_URB; frame++) अणु
		urb->iso_frame_desc[frame].offset = BYTES_PER_FRAME * frame;
		urb->iso_frame_desc[frame].length = BYTES_PER_FRAME;
		urb->iso_frame_desc[frame].actual_length = 0;
	पूर्ण

	urb->number_of_packets = FRAMES_PER_URB;
	usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल व्योम ग_लिखो_completed(काष्ठा urb *urb)
अणु
	काष्ठा snd_usb_caiaq_cb_info *info = urb->context;
	काष्ठा snd_usb_caiaqdev *cdev = info->cdev;

	अगर (!cdev->output_running) अणु
		cdev->output_running = 1;
		wake_up(&cdev->prepare_रुको_queue);
	पूर्ण

	clear_bit(info->index, &cdev->outurb_active_mask);
पूर्ण

अटल काष्ठा urb **alloc_urbs(काष्ठा snd_usb_caiaqdev *cdev, पूर्णांक dir, पूर्णांक *ret)
अणु
	पूर्णांक i, frame;
	काष्ठा urb **urbs;
	काष्ठा usb_device *usb_dev = cdev->chip.dev;
	अचिन्हित पूर्णांक pipe;

	pipe = (dir == SNDRV_PCM_STREAM_PLAYBACK) ?
		usb_sndisocpipe(usb_dev, ENDPOINT_PLAYBACK) :
		usb_rcvisocpipe(usb_dev, ENDPOINT_CAPTURE);

	urbs = kदो_स्मृति_array(N_URBS, माप(*urbs), GFP_KERNEL);
	अगर (!urbs) अणु
		*ret = -ENOMEM;
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < N_URBS; i++) अणु
		urbs[i] = usb_alloc_urb(FRAMES_PER_URB, GFP_KERNEL);
		अगर (!urbs[i]) अणु
			*ret = -ENOMEM;
			वापस urbs;
		पूर्ण

		urbs[i]->transfer_buffer =
			kदो_स्मृति_array(BYTES_PER_FRAME, FRAMES_PER_URB,
				      GFP_KERNEL);
		अगर (!urbs[i]->transfer_buffer) अणु
			*ret = -ENOMEM;
			वापस urbs;
		पूर्ण

		क्रम (frame = 0; frame < FRAMES_PER_URB; frame++) अणु
			काष्ठा usb_iso_packet_descriptor *iso =
				&urbs[i]->iso_frame_desc[frame];

			iso->offset = BYTES_PER_FRAME * frame;
			iso->length = BYTES_PER_FRAME;
		पूर्ण

		urbs[i]->dev = usb_dev;
		urbs[i]->pipe = pipe;
		urbs[i]->transfer_buffer_length = FRAMES_PER_URB
						* BYTES_PER_FRAME;
		urbs[i]->context = &cdev->data_cb_info[i];
		urbs[i]->पूर्णांकerval = 1;
		urbs[i]->number_of_packets = FRAMES_PER_URB;
		urbs[i]->complete = (dir == SNDRV_PCM_STREAM_CAPTURE) ?
					पढ़ो_completed : ग_लिखो_completed;
	पूर्ण

	*ret = 0;
	वापस urbs;
पूर्ण

अटल व्योम मुक्त_urbs(काष्ठा urb **urbs)
अणु
	पूर्णांक i;

	अगर (!urbs)
		वापस;

	क्रम (i = 0; i < N_URBS; i++) अणु
		अगर (!urbs[i])
			जारी;

		usb_समाप्त_urb(urbs[i]);
		kमुक्त(urbs[i]->transfer_buffer);
		usb_मुक्त_urb(urbs[i]);
	पूर्ण

	kमुक्त(urbs);
पूर्ण

पूर्णांक snd_usb_caiaq_audio_init(काष्ठा snd_usb_caiaqdev *cdev)
अणु
	पूर्णांक i, ret;
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	cdev->n_audio_in  = max(cdev->spec.num_analog_audio_in,
			       cdev->spec.num_digital_audio_in) /
				CHANNELS_PER_STREAM;
	cdev->n_audio_out = max(cdev->spec.num_analog_audio_out,
			       cdev->spec.num_digital_audio_out) /
				CHANNELS_PER_STREAM;
	cdev->n_streams = max(cdev->n_audio_in, cdev->n_audio_out);

	dev_dbg(dev, "cdev->n_audio_in = %d\n", cdev->n_audio_in);
	dev_dbg(dev, "cdev->n_audio_out = %d\n", cdev->n_audio_out);
	dev_dbg(dev, "cdev->n_streams = %d\n", cdev->n_streams);

	अगर (cdev->n_streams > MAX_STREAMS) अणु
		dev_err(dev, "unable to initialize device, too many streams.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cdev->n_streams < 1) अणु
		dev_err(dev, "bogus number of streams: %d\n", cdev->n_streams);
		वापस -EINVAL;
	पूर्ण

	ret = snd_pcm_new(cdev->chip.card, cdev->product_name, 0,
			cdev->n_audio_out, cdev->n_audio_in, &cdev->pcm);

	अगर (ret < 0) अणु
		dev_err(dev, "snd_pcm_new() returned %d\n", ret);
		वापस ret;
	पूर्ण

	cdev->pcm->निजी_data = cdev;
	strscpy(cdev->pcm->name, cdev->product_name, माप(cdev->pcm->name));

	स_रखो(cdev->sub_playback, 0, माप(cdev->sub_playback));
	स_रखो(cdev->sub_capture, 0, माप(cdev->sub_capture));

	स_नकल(&cdev->pcm_info, &snd_usb_caiaq_pcm_hardware,
			माप(snd_usb_caiaq_pcm_hardware));

	/* setup samplerates */
	cdev->samplerates = cdev->pcm_info.rates;
	चयन (cdev->chip.usb_id) अणु
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AK1):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_RIGKONTROL3):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_SESSIONIO):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_GUITARRIGMOBILE):
		cdev->samplerates |= SNDRV_PCM_RATE_192000;
		fallthrough;
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AUDIO2DJ):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AUDIO4DJ):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AUDIO8DJ):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORAUDIO2):
		cdev->samplerates |= SNDRV_PCM_RATE_88200;
		अवरोध;
	पूर्ण

	snd_pcm_set_ops(cdev->pcm, SNDRV_PCM_STREAM_PLAYBACK,
				&snd_usb_caiaq_ops);
	snd_pcm_set_ops(cdev->pcm, SNDRV_PCM_STREAM_CAPTURE,
				&snd_usb_caiaq_ops);
	snd_pcm_set_managed_buffer_all(cdev->pcm, SNDRV_DMA_TYPE_VMALLOC,
				       शून्य, 0, 0);

	cdev->data_cb_info =
		kदो_स्मृति_array(N_URBS, माप(काष्ठा snd_usb_caiaq_cb_info),
					GFP_KERNEL);

	अगर (!cdev->data_cb_info)
		वापस -ENOMEM;

	cdev->outurb_active_mask = 0;
	BUILD_BUG_ON(N_URBS > (माप(cdev->outurb_active_mask) * 8));

	क्रम (i = 0; i < N_URBS; i++) अणु
		cdev->data_cb_info[i].cdev = cdev;
		cdev->data_cb_info[i].index = i;
	पूर्ण

	cdev->data_urbs_in = alloc_urbs(cdev, SNDRV_PCM_STREAM_CAPTURE, &ret);
	अगर (ret < 0) अणु
		kमुक्त(cdev->data_cb_info);
		मुक्त_urbs(cdev->data_urbs_in);
		वापस ret;
	पूर्ण

	cdev->data_urbs_out = alloc_urbs(cdev, SNDRV_PCM_STREAM_PLAYBACK, &ret);
	अगर (ret < 0) अणु
		kमुक्त(cdev->data_cb_info);
		मुक्त_urbs(cdev->data_urbs_in);
		मुक्त_urbs(cdev->data_urbs_out);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम snd_usb_caiaq_audio_मुक्त(काष्ठा snd_usb_caiaqdev *cdev)
अणु
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	dev_dbg(dev, "%s(%p)\n", __func__, cdev);
	stream_stop(cdev);
	मुक्त_urbs(cdev->data_urbs_in);
	मुक्त_urbs(cdev->data_urbs_out);
	kमुक्त(cdev->data_cb_info);
पूर्ण

