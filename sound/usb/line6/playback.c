<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "capture.h"
#समावेश "driver.h"
#समावेश "pcm.h"
#समावेश "playback.h"

/*
	Software stereo volume control.
*/
अटल व्योम change_volume(काष्ठा urb *urb_out, पूर्णांक volume[],
			  पूर्णांक bytes_per_frame)
अणु
	पूर्णांक chn = 0;

	अगर (volume[0] == 256 && volume[1] == 256)
		वापस;		/* maximum volume - no change */

	अगर (bytes_per_frame == 4) अणु
		__le16 *p, *buf_end;

		p = (__le16 *)urb_out->transfer_buffer;
		buf_end = p + urb_out->transfer_buffer_length / माप(*p);

		क्रम (; p < buf_end; ++p) अणु
			लघु pv = le16_to_cpu(*p);
			पूर्णांक val = (pv * volume[chn & 1]) >> 8;
			pv = clamp(val, -0x8000, 0x7fff);
			*p = cpu_to_le16(pv);
			++chn;
		पूर्ण
	पूर्ण अन्यथा अगर (bytes_per_frame == 6) अणु
		अचिन्हित अक्षर *p, *buf_end;

		p = (अचिन्हित अक्षर *)urb_out->transfer_buffer;
		buf_end = p + urb_out->transfer_buffer_length;

		क्रम (; p < buf_end; p += 3) अणु
			पूर्णांक val;

			val = p[0] + (p[1] << 8) + ((चिन्हित अक्षर)p[2] << 16);
			val = (val * volume[chn & 1]) >> 8;
			val = clamp(val, -0x800000, 0x7fffff);
			p[0] = val;
			p[1] = val >> 8;
			p[2] = val >> 16;
			++chn;
		पूर्ण
	पूर्ण
पूर्ण

/*
	Create संकेत क्रम impulse response test.
*/
अटल व्योम create_impulse_test_संकेत(काष्ठा snd_line6_pcm *line6pcm,
				       काष्ठा urb *urb_out, पूर्णांक bytes_per_frame)
अणु
	पूर्णांक frames = urb_out->transfer_buffer_length / bytes_per_frame;

	अगर (bytes_per_frame == 4) अणु
		पूर्णांक i;
		लघु *pi = (लघु *)line6pcm->prev_fbuf;
		लघु *po = (लघु *)urb_out->transfer_buffer;

		क्रम (i = 0; i < frames; ++i) अणु
			po[0] = pi[0];
			po[1] = 0;
			pi += 2;
			po += 2;
		पूर्ण
	पूर्ण अन्यथा अगर (bytes_per_frame == 6) अणु
		पूर्णांक i, j;
		अचिन्हित अक्षर *pi = line6pcm->prev_fbuf;
		अचिन्हित अक्षर *po = urb_out->transfer_buffer;

		क्रम (i = 0; i < frames; ++i) अणु
			क्रम (j = 0; j < bytes_per_frame / 2; ++j)
				po[j] = pi[j];

			क्रम (; j < bytes_per_frame; ++j)
				po[j] = 0;

			pi += bytes_per_frame;
			po += bytes_per_frame;
		पूर्ण
	पूर्ण
	अगर (--line6pcm->impulse_count <= 0) अणु
		((अचिन्हित अक्षर *)(urb_out->transfer_buffer))[bytes_per_frame -
							      1] =
		    line6pcm->impulse_volume;
		line6pcm->impulse_count = line6pcm->impulse_period;
	पूर्ण
पूर्ण

/*
	Add संकेत to buffer क्रम software monitoring.
*/
अटल व्योम add_monitor_संकेत(काष्ठा urb *urb_out, अचिन्हित अक्षर *संकेत,
			       पूर्णांक volume, पूर्णांक bytes_per_frame)
अणु
	अगर (volume == 0)
		वापस;		/* zero volume - no change */

	अगर (bytes_per_frame == 4) अणु
		__le16 *pi, *po, *buf_end;

		pi = (__le16 *)संकेत;
		po = (__le16 *)urb_out->transfer_buffer;
		buf_end = po + urb_out->transfer_buffer_length / माप(*po);

		क्रम (; po < buf_end; ++pi, ++po) अणु
			लघु pov = le16_to_cpu(*po);
			लघु piv = le16_to_cpu(*pi);
			पूर्णांक val = pov + ((piv * volume) >> 8);
			pov = clamp(val, -0x8000, 0x7fff);
			*po = cpu_to_le16(pov);
		पूर्ण
	पूर्ण

	/*
	   We करोn't need to handle devices with 6 bytes per frame here
	   since they all support hardware monitoring.
	 */
पूर्ण

/*
	Find a मुक्त URB, prepare audio data, and submit URB.
	must be called in line6pcm->out.lock context
*/
अटल पूर्णांक submit_audio_out_urb(काष्ठा snd_line6_pcm *line6pcm)
अणु
	पूर्णांक index;
	पूर्णांक i, urb_size, urb_frames;
	पूर्णांक ret;
	स्थिर पूर्णांक bytes_per_frame =
		line6pcm->properties->bytes_per_channel *
		line6pcm->properties->playback_hw.channels_max;
	स्थिर पूर्णांक frame_increment =
		line6pcm->properties->rates.rats[0].num_min;
	स्थिर पूर्णांक frame_factor =
		line6pcm->properties->rates.rats[0].den *
		(line6pcm->line6->पूर्णांकervals_per_second / LINE6_ISO_INTERVAL);
	काष्ठा urb *urb_out;

	index = find_first_zero_bit(&line6pcm->out.active_urbs,
				    line6pcm->line6->iso_buffers);

	अगर (index < 0 || index >= line6pcm->line6->iso_buffers) अणु
		dev_err(line6pcm->line6->अगरcdev, "no free URB found\n");
		वापस -EINVAL;
	पूर्ण

	urb_out = line6pcm->out.urbs[index];
	urb_size = 0;

	/* TODO: this may not work क्रम LINE6_ISO_PACKETS != 1 */
	क्रम (i = 0; i < LINE6_ISO_PACKETS; ++i) अणु
		/* compute frame size क्रम given sampling rate */
		पूर्णांक fsize = 0;
		काष्ठा usb_iso_packet_descriptor *fout =
		    &urb_out->iso_frame_desc[i];

		fsize = line6pcm->prev_fsize;
		अगर (fsize == 0) अणु
			पूर्णांक n;

			line6pcm->out.count += frame_increment;
			n = line6pcm->out.count / frame_factor;
			line6pcm->out.count -= n * frame_factor;
			fsize = n;
		पूर्ण

		fsize *= bytes_per_frame;

		fout->offset = urb_size;
		fout->length = fsize;
		urb_size += fsize;
	पूर्ण

	अगर (urb_size == 0) अणु
		/* can't determine URB size */
		dev_err(line6pcm->line6->अगरcdev, "driver bug: urb_size = 0\n");
		वापस -EINVAL;
	पूर्ण

	urb_frames = urb_size / bytes_per_frame;
	urb_out->transfer_buffer =
	    line6pcm->out.buffer +
	    index * LINE6_ISO_PACKETS * line6pcm->max_packet_size_out;
	urb_out->transfer_buffer_length = urb_size;
	urb_out->context = line6pcm;

	अगर (test_bit(LINE6_STREAM_PCM, &line6pcm->out.running) &&
	    !test_bit(LINE6_FLAG_PAUSE_PLAYBACK, &line6pcm->flags)) अणु
		काष्ठा snd_pcm_runसमय *runसमय =
		    get_substream(line6pcm, SNDRV_PCM_STREAM_PLAYBACK)->runसमय;

		अगर (line6pcm->out.pos + urb_frames > runसमय->buffer_size) अणु
			/*
			   The transferred area goes over buffer boundary,
			   copy the data to the temp buffer.
			 */
			पूर्णांक len;

			len = runसमय->buffer_size - line6pcm->out.pos;

			अगर (len > 0) अणु
				स_नकल(urb_out->transfer_buffer,
				       runसमय->dma_area +
				       line6pcm->out.pos * bytes_per_frame,
				       len * bytes_per_frame);
				स_नकल(urb_out->transfer_buffer +
				       len * bytes_per_frame, runसमय->dma_area,
				       (urb_frames - len) * bytes_per_frame);
			पूर्ण अन्यथा
				dev_err(line6pcm->line6->अगरcdev, "driver bug: len = %d\n",
					len);
		पूर्ण अन्यथा अणु
			स_नकल(urb_out->transfer_buffer,
			       runसमय->dma_area +
			       line6pcm->out.pos * bytes_per_frame,
			       urb_out->transfer_buffer_length);
		पूर्ण

		line6pcm->out.pos += urb_frames;
		अगर (line6pcm->out.pos >= runसमय->buffer_size)
			line6pcm->out.pos -= runसमय->buffer_size;

		change_volume(urb_out, line6pcm->volume_playback,
			      bytes_per_frame);
	पूर्ण अन्यथा अणु
		स_रखो(urb_out->transfer_buffer, 0,
		       urb_out->transfer_buffer_length);
	पूर्ण

	spin_lock_nested(&line6pcm->in.lock, SINGLE_DEPTH_NESTING);
	अगर (line6pcm->prev_fbuf) अणु
		अगर (test_bit(LINE6_STREAM_IMPULSE, &line6pcm->out.running)) अणु
			create_impulse_test_संकेत(line6pcm, urb_out,
						   bytes_per_frame);
			अगर (test_bit(LINE6_STREAM_PCM, &line6pcm->in.running)) अणु
				line6_capture_copy(line6pcm,
						   urb_out->transfer_buffer,
						   urb_out->
						   transfer_buffer_length);
				line6_capture_check_period(line6pcm,
					urb_out->transfer_buffer_length);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!(line6pcm->line6->properties->capabilities & LINE6_CAP_HWMON)
			    && line6pcm->out.running && line6pcm->in.running)
				add_monitor_संकेत(urb_out, line6pcm->prev_fbuf,
						   line6pcm->volume_monitor,
						   bytes_per_frame);
		पूर्ण
		line6pcm->prev_fbuf = शून्य;
		line6pcm->prev_fsize = 0;
	पूर्ण
	spin_unlock(&line6pcm->in.lock);

	ret = usb_submit_urb(urb_out, GFP_ATOMIC);

	अगर (ret == 0)
		set_bit(index, &line6pcm->out.active_urbs);
	अन्यथा
		dev_err(line6pcm->line6->अगरcdev,
			"URB out #%d submission failed (%d)\n", index, ret);

	वापस 0;
पूर्ण

/*
	Submit all currently available playback URBs.
	must be called in line6pcm->out.lock context
 */
पूर्णांक line6_submit_audio_out_all_urbs(काष्ठा snd_line6_pcm *line6pcm)
अणु
	पूर्णांक ret = 0, i;

	क्रम (i = 0; i < line6pcm->line6->iso_buffers; ++i) अणु
		ret = submit_audio_out_urb(line6pcm);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
	Callback क्रम completed playback URB.
*/
अटल व्योम audio_out_callback(काष्ठा urb *urb)
अणु
	पूर्णांक i, index, length = 0, shutकरोwn = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा snd_line6_pcm *line6pcm = (काष्ठा snd_line6_pcm *)urb->context;
	काष्ठा snd_pcm_substream *substream =
	    get_substream(line6pcm, SNDRV_PCM_STREAM_PLAYBACK);
	स्थिर पूर्णांक bytes_per_frame =
		line6pcm->properties->bytes_per_channel *
		line6pcm->properties->playback_hw.channels_max;

#अगर USE_CLEAR_BUFFER_WORKAROUND
	स_रखो(urb->transfer_buffer, 0, urb->transfer_buffer_length);
#पूर्ण_अगर

	line6pcm->out.last_frame = urb->start_frame;

	/* find index of URB */
	क्रम (index = 0; index < line6pcm->line6->iso_buffers; index++)
		अगर (urb == line6pcm->out.urbs[index])
			अवरोध;

	अगर (index >= line6pcm->line6->iso_buffers)
		वापस;		/* URB has been unlinked asynchronously */

	क्रम (i = 0; i < LINE6_ISO_PACKETS; i++)
		length += urb->iso_frame_desc[i].length;

	spin_lock_irqsave(&line6pcm->out.lock, flags);

	अगर (test_bit(LINE6_STREAM_PCM, &line6pcm->out.running)) अणु
		काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

		line6pcm->out.pos_करोne +=
		    length / bytes_per_frame;

		अगर (line6pcm->out.pos_करोne >= runसमय->buffer_size)
			line6pcm->out.pos_करोne -= runसमय->buffer_size;
	पूर्ण

	clear_bit(index, &line6pcm->out.active_urbs);

	क्रम (i = 0; i < LINE6_ISO_PACKETS; i++)
		अगर (urb->iso_frame_desc[i].status == -EXDEV) अणु
			shutकरोwn = 1;
			अवरोध;
		पूर्ण

	अगर (test_and_clear_bit(index, &line6pcm->out.unlink_urbs))
		shutकरोwn = 1;

	अगर (!shutकरोwn) अणु
		submit_audio_out_urb(line6pcm);

		अगर (test_bit(LINE6_STREAM_PCM, &line6pcm->out.running)) अणु
			line6pcm->out.bytes += length;
			अगर (line6pcm->out.bytes >= line6pcm->out.period) अणु
				line6pcm->out.bytes %= line6pcm->out.period;
				spin_unlock(&line6pcm->out.lock);
				snd_pcm_period_elapsed(substream);
				spin_lock(&line6pcm->out.lock);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&line6pcm->out.lock, flags);
पूर्ण

/* खोलो playback callback */
अटल पूर्णांक snd_line6_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);

	err = snd_pcm_hw_स्थिरraपूर्णांक_ratdens(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
					    &line6pcm->properties->rates);
	अगर (err < 0)
		वापस err;

	runसमय->hw = line6pcm->properties->playback_hw;
	वापस 0;
पूर्ण

/* बंद playback callback */
अटल पूर्णांक snd_line6_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

/* playback चालकs */
स्थिर काष्ठा snd_pcm_ops snd_line6_playback_ops = अणु
	.खोलो = snd_line6_playback_खोलो,
	.बंद = snd_line6_playback_बंद,
	.hw_params = snd_line6_hw_params,
	.hw_मुक्त = snd_line6_hw_मुक्त,
	.prepare = snd_line6_prepare,
	.trigger = snd_line6_trigger,
	.poपूर्णांकer = snd_line6_poपूर्णांकer,
पूर्ण;

पूर्णांक line6_create_audio_out_urbs(काष्ठा snd_line6_pcm *line6pcm)
अणु
	काष्ठा usb_line6 *line6 = line6pcm->line6;
	पूर्णांक i;

	line6pcm->out.urbs = kसुस्मृति(line6->iso_buffers, माप(काष्ठा urb *),
				     GFP_KERNEL);
	अगर (line6pcm->out.urbs == शून्य)
		वापस -ENOMEM;

	/* create audio URBs and fill in स्थिरant values: */
	क्रम (i = 0; i < line6->iso_buffers; ++i) अणु
		काष्ठा urb *urb;

		/* URB क्रम audio out: */
		urb = line6pcm->out.urbs[i] =
		    usb_alloc_urb(LINE6_ISO_PACKETS, GFP_KERNEL);

		अगर (urb == शून्य)
			वापस -ENOMEM;

		urb->dev = line6->usbdev;
		urb->pipe =
		    usb_sndisocpipe(line6->usbdev,
				    line6->properties->ep_audio_w &
				    USB_ENDPOINT_NUMBER_MASK);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->start_frame = -1;
		urb->number_of_packets = LINE6_ISO_PACKETS;
		urb->पूर्णांकerval = LINE6_ISO_INTERVAL;
		urb->error_count = 0;
		urb->complete = audio_out_callback;
		अगर (usb_urb_ep_type_check(urb))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
