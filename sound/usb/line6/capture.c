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

/*
	Find a मुक्त URB and submit it.
	must be called in line6pcm->in.lock context
*/
अटल पूर्णांक submit_audio_in_urb(काष्ठा snd_line6_pcm *line6pcm)
अणु
	पूर्णांक index;
	पूर्णांक i, urb_size;
	पूर्णांक ret;
	काष्ठा urb *urb_in;

	index = find_first_zero_bit(&line6pcm->in.active_urbs,
				    line6pcm->line6->iso_buffers);

	अगर (index < 0 || index >= line6pcm->line6->iso_buffers) अणु
		dev_err(line6pcm->line6->अगरcdev, "no free URB found\n");
		वापस -EINVAL;
	पूर्ण

	urb_in = line6pcm->in.urbs[index];
	urb_size = 0;

	क्रम (i = 0; i < LINE6_ISO_PACKETS; ++i) अणु
		काष्ठा usb_iso_packet_descriptor *fin =
		    &urb_in->iso_frame_desc[i];
		fin->offset = urb_size;
		fin->length = line6pcm->max_packet_size_in;
		urb_size += line6pcm->max_packet_size_in;
	पूर्ण

	urb_in->transfer_buffer =
	    line6pcm->in.buffer +
	    index * LINE6_ISO_PACKETS * line6pcm->max_packet_size_in;
	urb_in->transfer_buffer_length = urb_size;
	urb_in->context = line6pcm;

	ret = usb_submit_urb(urb_in, GFP_ATOMIC);

	अगर (ret == 0)
		set_bit(index, &line6pcm->in.active_urbs);
	अन्यथा
		dev_err(line6pcm->line6->अगरcdev,
			"URB in #%d submission failed (%d)\n", index, ret);

	वापस 0;
पूर्ण

/*
	Submit all currently available capture URBs.
	must be called in line6pcm->in.lock context
*/
पूर्णांक line6_submit_audio_in_all_urbs(काष्ठा snd_line6_pcm *line6pcm)
अणु
	पूर्णांक ret = 0, i;

	क्रम (i = 0; i < line6pcm->line6->iso_buffers; ++i) अणु
		ret = submit_audio_in_urb(line6pcm);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
	Copy data पूर्णांकo ALSA capture buffer.
*/
व्योम line6_capture_copy(काष्ठा snd_line6_pcm *line6pcm, अक्षर *fbuf, पूर्णांक fsize)
अणु
	काष्ठा snd_pcm_substream *substream =
	    get_substream(line6pcm, SNDRV_PCM_STREAM_CAPTURE);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	स्थिर पूर्णांक bytes_per_frame =
		line6pcm->properties->bytes_per_channel *
		line6pcm->properties->capture_hw.channels_max;
	पूर्णांक frames = fsize / bytes_per_frame;

	अगर (runसमय == शून्य)
		वापस;

	अगर (line6pcm->in.pos_करोne + frames > runसमय->buffer_size) अणु
		/*
		   The transferred area goes over buffer boundary,
		   copy two separate chunks.
		 */
		पूर्णांक len;

		len = runसमय->buffer_size - line6pcm->in.pos_करोne;

		अगर (len > 0) अणु
			स_नकल(runसमय->dma_area +
			       line6pcm->in.pos_करोne * bytes_per_frame, fbuf,
			       len * bytes_per_frame);
			स_नकल(runसमय->dma_area, fbuf + len * bytes_per_frame,
			       (frames - len) * bytes_per_frame);
		पूर्ण अन्यथा अणु
			/* this is somewhat paranoid */
			dev_err(line6pcm->line6->अगरcdev,
				"driver bug: len = %d\n", len);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* copy single chunk */
		स_नकल(runसमय->dma_area +
		       line6pcm->in.pos_करोne * bytes_per_frame, fbuf, fsize);
	पूर्ण

	line6pcm->in.pos_करोne += frames;
	अगर (line6pcm->in.pos_करोne >= runसमय->buffer_size)
		line6pcm->in.pos_करोne -= runसमय->buffer_size;
पूर्ण

व्योम line6_capture_check_period(काष्ठा snd_line6_pcm *line6pcm, पूर्णांक length)
अणु
	काष्ठा snd_pcm_substream *substream =
	    get_substream(line6pcm, SNDRV_PCM_STREAM_CAPTURE);

	line6pcm->in.bytes += length;
	अगर (line6pcm->in.bytes >= line6pcm->in.period) अणु
		line6pcm->in.bytes %= line6pcm->in.period;
		spin_unlock(&line6pcm->in.lock);
		snd_pcm_period_elapsed(substream);
		spin_lock(&line6pcm->in.lock);
	पूर्ण
पूर्ण

/*
 * Callback क्रम completed capture URB.
 */
अटल व्योम audio_in_callback(काष्ठा urb *urb)
अणु
	पूर्णांक i, index, length = 0, shutकरोwn = 0;
	अचिन्हित दीर्घ flags;

	काष्ठा snd_line6_pcm *line6pcm = (काष्ठा snd_line6_pcm *)urb->context;

	line6pcm->in.last_frame = urb->start_frame;

	/* find index of URB */
	क्रम (index = 0; index < line6pcm->line6->iso_buffers; ++index)
		अगर (urb == line6pcm->in.urbs[index])
			अवरोध;

	spin_lock_irqsave(&line6pcm->in.lock, flags);

	क्रम (i = 0; i < LINE6_ISO_PACKETS; ++i) अणु
		अक्षर *fbuf;
		पूर्णांक fsize;
		काष्ठा usb_iso_packet_descriptor *fin = &urb->iso_frame_desc[i];

		अगर (fin->status == -EXDEV) अणु
			shutकरोwn = 1;
			अवरोध;
		पूर्ण

		fbuf = urb->transfer_buffer + fin->offset;
		fsize = fin->actual_length;

		अगर (fsize > line6pcm->max_packet_size_in) अणु
			dev_err(line6pcm->line6->अगरcdev,
				"driver and/or device bug: packet too large (%d > %d)\n",
				fsize, line6pcm->max_packet_size_in);
		पूर्ण

		length += fsize;

		BUILD_BUG_ON_MSG(LINE6_ISO_PACKETS != 1,
			"The following code assumes LINE6_ISO_PACKETS == 1");
		/* TODO:
		 * Also, अगर iso_buffers != 2, the prev frame is almost अक्रमom at
		 * playback side.
		 * This needs to be redeचिन्हित. It should be "stable", but we may
		 * experience sync problems on such high-speed configs.
		 */

		line6pcm->prev_fbuf = fbuf;
		line6pcm->prev_fsize = fsize /
			(line6pcm->properties->bytes_per_channel *
			line6pcm->properties->capture_hw.channels_max);

		अगर (!test_bit(LINE6_STREAM_IMPULSE, &line6pcm->in.running) &&
		    test_bit(LINE6_STREAM_PCM, &line6pcm->in.running) &&
		    fsize > 0)
			line6_capture_copy(line6pcm, fbuf, fsize);
	पूर्ण

	clear_bit(index, &line6pcm->in.active_urbs);

	अगर (test_and_clear_bit(index, &line6pcm->in.unlink_urbs))
		shutकरोwn = 1;

	अगर (!shutकरोwn) अणु
		submit_audio_in_urb(line6pcm);

		अगर (!test_bit(LINE6_STREAM_IMPULSE, &line6pcm->in.running) &&
		    test_bit(LINE6_STREAM_PCM, &line6pcm->in.running))
			line6_capture_check_period(line6pcm, length);
	पूर्ण

	spin_unlock_irqrestore(&line6pcm->in.lock, flags);
पूर्ण

/* खोलो capture callback */
अटल पूर्णांक snd_line6_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);

	err = snd_pcm_hw_स्थिरraपूर्णांक_ratdens(runसमय, 0,
					    SNDRV_PCM_HW_PARAM_RATE,
					    &line6pcm->properties->rates);
	अगर (err < 0)
		वापस err;

	line6_pcm_acquire(line6pcm, LINE6_STREAM_CAPTURE_HELPER, false);

	runसमय->hw = line6pcm->properties->capture_hw;
	वापस 0;
पूर्ण

/* बंद capture callback */
अटल पूर्णांक snd_line6_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);

	line6_pcm_release(line6pcm, LINE6_STREAM_CAPTURE_HELPER);
	वापस 0;
पूर्ण

/* capture चालकs */
स्थिर काष्ठा snd_pcm_ops snd_line6_capture_ops = अणु
	.खोलो = snd_line6_capture_खोलो,
	.बंद = snd_line6_capture_बंद,
	.hw_params = snd_line6_hw_params,
	.hw_मुक्त = snd_line6_hw_मुक्त,
	.prepare = snd_line6_prepare,
	.trigger = snd_line6_trigger,
	.poपूर्णांकer = snd_line6_poपूर्णांकer,
पूर्ण;

पूर्णांक line6_create_audio_in_urbs(काष्ठा snd_line6_pcm *line6pcm)
अणु
	काष्ठा usb_line6 *line6 = line6pcm->line6;
	पूर्णांक i;

	line6pcm->in.urbs = kसुस्मृति(line6->iso_buffers, माप(काष्ठा urb *),
				    GFP_KERNEL);
	अगर (line6pcm->in.urbs == शून्य)
		वापस -ENOMEM;

	/* create audio URBs and fill in स्थिरant values: */
	क्रम (i = 0; i < line6->iso_buffers; ++i) अणु
		काष्ठा urb *urb;

		/* URB क्रम audio in: */
		urb = line6pcm->in.urbs[i] =
		    usb_alloc_urb(LINE6_ISO_PACKETS, GFP_KERNEL);

		अगर (urb == शून्य)
			वापस -ENOMEM;

		urb->dev = line6->usbdev;
		urb->pipe =
		    usb_rcvisocpipe(line6->usbdev,
				    line6->properties->ep_audio_r &
				    USB_ENDPOINT_NUMBER_MASK);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->start_frame = -1;
		urb->number_of_packets = LINE6_ISO_PACKETS;
		urb->पूर्णांकerval = LINE6_ISO_INTERVAL;
		urb->error_count = 0;
		urb->complete = audio_in_callback;
		अगर (usb_urb_ep_type_check(urb))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
