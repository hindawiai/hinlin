<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Edirol UA-101/UA-1000 driver
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "../usbaudio.h"
#समावेश "../midi.h"

MODULE_DESCRIPTION("Edirol UA-101/1000 driver");
MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_LICENSE("GPL v2");

/*
 * Should not be lower than the minimum scheduling delay of the host
 * controller.  Some Intel controllers need more than one frame; as दीर्घ as
 * that driver करोesn't tell us about this, use 1.5 frames just to be sure.
 */
#घोषणा MIN_QUEUE_LENGTH	12
/* Somewhat अक्रमom. */
#घोषणा MAX_QUEUE_LENGTH	30
/*
 * This magic value optimizes memory usage efficiency क्रम the UA-101's packet
 * sizes at all sample rates, taking पूर्णांकo account the stupid cache pool sizes
 * that usb_alloc_coherent() uses.
 */
#घोषणा DEFAULT_QUEUE_LENGTH	21

#घोषणा MAX_PACKET_SIZE		672 /* hardware specअगरic */
#घोषणा MAX_MEMORY_BUFFERS	DIV_ROUND_UP(MAX_QUEUE_LENGTH, \
					     PAGE_SIZE / MAX_PACKET_SIZE)

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;
अटल अचिन्हित पूर्णांक queue_length = 21;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "card index");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "enable card");
module_param(queue_length, uपूर्णांक, 0644);
MODULE_PARM_DESC(queue_length, "USB queue length in microframes, "
		 __stringअगरy(MIN_QUEUE_LENGTH)"-"__stringअगरy(MAX_QUEUE_LENGTH));

क्रमागत अणु
	INTF_PLAYBACK,
	INTF_CAPTURE,
	INTF_MIDI,

	INTF_COUNT
पूर्ण;

/* bits in काष्ठा ua101::states */
क्रमागत अणु
	USB_CAPTURE_RUNNING,
	USB_PLAYBACK_RUNNING,
	ALSA_CAPTURE_OPEN,
	ALSA_PLAYBACK_OPEN,
	ALSA_CAPTURE_RUNNING,
	ALSA_PLAYBACK_RUNNING,
	CAPTURE_URB_COMPLETED,
	PLAYBACK_URB_COMPLETED,
	DISCONNECTED,
पूर्ण;

काष्ठा ua101 अणु
	काष्ठा usb_device *dev;
	काष्ठा snd_card *card;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf[INTF_COUNT];
	पूर्णांक card_index;
	काष्ठा snd_pcm *pcm;
	काष्ठा list_head midi_list;
	u64 क्रमmat_bit;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक packets_per_second;
	spinlock_t lock;
	काष्ठा mutex mutex;
	अचिन्हित दीर्घ states;

	/* FIFO to synchronize playback rate to capture rate */
	अचिन्हित पूर्णांक rate_feedback_start;
	अचिन्हित पूर्णांक rate_feedback_count;
	u8 rate_feedback[MAX_QUEUE_LENGTH];

	काष्ठा list_head पढ़ोy_playback_urbs;
	काष्ठा work_काष्ठा playback_work;
	रुको_queue_head_t alsa_capture_रुको;
	रुको_queue_head_t rate_feedback_रुको;
	रुको_queue_head_t alsa_playback_रुको;
	काष्ठा ua101_stream अणु
		काष्ठा snd_pcm_substream *substream;
		अचिन्हित पूर्णांक usb_pipe;
		अचिन्हित पूर्णांक channels;
		अचिन्हित पूर्णांक frame_bytes;
		अचिन्हित पूर्णांक max_packet_bytes;
		अचिन्हित पूर्णांक period_pos;
		अचिन्हित पूर्णांक buffer_pos;
		अचिन्हित पूर्णांक queue_length;
		काष्ठा ua101_urb अणु
			काष्ठा urb urb;
			काष्ठा usb_iso_packet_descriptor iso_frame_desc[1];
			काष्ठा list_head पढ़ोy_list;
		पूर्ण *urbs[MAX_QUEUE_LENGTH];
		काष्ठा अणु
			अचिन्हित पूर्णांक size;
			व्योम *addr;
			dma_addr_t dma;
		पूर्ण buffers[MAX_MEMORY_BUFFERS];
	पूर्ण capture, playback;
पूर्ण;

अटल DEFINE_MUTEX(devices_mutex);
अटल अचिन्हित पूर्णांक devices_used;
अटल काष्ठा usb_driver ua101_driver;

अटल व्योम पात_alsa_playback(काष्ठा ua101 *ua);
अटल व्योम पात_alsa_capture(काष्ठा ua101 *ua);

अटल स्थिर अक्षर *usb_error_string(पूर्णांक err)
अणु
	चयन (err) अणु
	हाल -ENODEV:
		वापस "no device";
	हाल -ENOENT:
		वापस "endpoint not enabled";
	हाल -EPIPE:
		वापस "endpoint stalled";
	हाल -ENOSPC:
		वापस "not enough bandwidth";
	हाल -ESHUTDOWN:
		वापस "device disabled";
	हाल -EHOSTUNREACH:
		वापस "device suspended";
	हाल -EINVAL:
	हाल -EAGAIN:
	हाल -EFBIG:
	हाल -EMSGSIZE:
		वापस "internal error";
	शेष:
		वापस "unknown error";
	पूर्ण
पूर्ण

अटल व्योम पात_usb_capture(काष्ठा ua101 *ua)
अणु
	अगर (test_and_clear_bit(USB_CAPTURE_RUNNING, &ua->states)) अणु
		wake_up(&ua->alsa_capture_रुको);
		wake_up(&ua->rate_feedback_रुको);
	पूर्ण
पूर्ण

अटल व्योम पात_usb_playback(काष्ठा ua101 *ua)
अणु
	अगर (test_and_clear_bit(USB_PLAYBACK_RUNNING, &ua->states))
		wake_up(&ua->alsa_playback_रुको);
पूर्ण

अटल व्योम playback_urb_complete(काष्ठा urb *usb_urb)
अणु
	काष्ठा ua101_urb *urb = (काष्ठा ua101_urb *)usb_urb;
	काष्ठा ua101 *ua = urb->urb.context;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(urb->urb.status == -ENOENT ||	/* unlinked */
		     urb->urb.status == -ENODEV ||	/* device हटाओd */
		     urb->urb.status == -ECONNRESET ||	/* unlinked */
		     urb->urb.status == -ESHUTDOWN)) अणु	/* device disabled */
		पात_usb_playback(ua);
		पात_alsa_playback(ua);
		वापस;
	पूर्ण

	अगर (test_bit(USB_PLAYBACK_RUNNING, &ua->states)) अणु
		/* append URB to FIFO */
		spin_lock_irqsave(&ua->lock, flags);
		list_add_tail(&urb->पढ़ोy_list, &ua->पढ़ोy_playback_urbs);
		अगर (ua->rate_feedback_count > 0)
			queue_work(प्रणाली_highpri_wq, &ua->playback_work);
		ua->playback.substream->runसमय->delay -=
				urb->urb.iso_frame_desc[0].length /
						ua->playback.frame_bytes;
		spin_unlock_irqrestore(&ua->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम first_playback_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा ua101 *ua = urb->context;

	urb->complete = playback_urb_complete;
	playback_urb_complete(urb);

	set_bit(PLAYBACK_URB_COMPLETED, &ua->states);
	wake_up(&ua->alsa_playback_रुको);
पूर्ण

/* copy data from the ALSA ring buffer पूर्णांकo the URB buffer */
अटल bool copy_playback_data(काष्ठा ua101_stream *stream, काष्ठा urb *urb,
			       अचिन्हित पूर्णांक frames)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित पूर्णांक frame_bytes, frames1;
	स्थिर u8 *source;

	runसमय = stream->substream->runसमय;
	frame_bytes = stream->frame_bytes;
	source = runसमय->dma_area + stream->buffer_pos * frame_bytes;
	अगर (stream->buffer_pos + frames <= runसमय->buffer_size) अणु
		स_नकल(urb->transfer_buffer, source, frames * frame_bytes);
	पूर्ण अन्यथा अणु
		/* wrap around at end of ring buffer */
		frames1 = runसमय->buffer_size - stream->buffer_pos;
		स_नकल(urb->transfer_buffer, source, frames1 * frame_bytes);
		स_नकल(urb->transfer_buffer + frames1 * frame_bytes,
		       runसमय->dma_area, (frames - frames1) * frame_bytes);
	पूर्ण

	stream->buffer_pos += frames;
	अगर (stream->buffer_pos >= runसमय->buffer_size)
		stream->buffer_pos -= runसमय->buffer_size;
	stream->period_pos += frames;
	अगर (stream->period_pos >= runसमय->period_size) अणु
		stream->period_pos -= runसमय->period_size;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत व्योम add_with_wraparound(काष्ठा ua101 *ua,
				       अचिन्हित पूर्णांक *value, अचिन्हित पूर्णांक add)
अणु
	*value += add;
	अगर (*value >= ua->playback.queue_length)
		*value -= ua->playback.queue_length;
पूर्ण

अटल व्योम playback_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ua101 *ua = container_of(work, काष्ठा ua101, playback_work);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक frames;
	काष्ठा ua101_urb *urb;
	bool करो_period_elapsed = false;
	पूर्णांक err;

	अगर (unlikely(!test_bit(USB_PLAYBACK_RUNNING, &ua->states)))
		वापस;

	/*
	 * Synchronizing the playback rate to the capture rate is करोne by using
	 * the same sequence of packet sizes क्रम both streams.
	 * Submitting a playback URB thereक्रमe requires both a पढ़ोy URB and
	 * the size of the corresponding capture packet, i.e., both playback
	 * and capture URBs must have been completed.  Since the USB core करोes
	 * not guarantee that playback and capture complete callbacks are
	 * called alternately, we use two FIFOs क्रम packet sizes and पढ़ो URBs;
	 * submitting playback URBs is possible as दीर्घ as both FIFOs are
	 * nonempty.
	 */
	spin_lock_irqsave(&ua->lock, flags);
	जबतक (ua->rate_feedback_count > 0 &&
	       !list_empty(&ua->पढ़ोy_playback_urbs)) अणु
		/* take packet size out of FIFO */
		frames = ua->rate_feedback[ua->rate_feedback_start];
		add_with_wraparound(ua, &ua->rate_feedback_start, 1);
		ua->rate_feedback_count--;

		/* take URB out of FIFO */
		urb = list_first_entry(&ua->पढ़ोy_playback_urbs,
				       काष्ठा ua101_urb, पढ़ोy_list);
		list_del(&urb->पढ़ोy_list);

		/* fill packet with data or silence */
		urb->urb.iso_frame_desc[0].length =
			frames * ua->playback.frame_bytes;
		अगर (test_bit(ALSA_PLAYBACK_RUNNING, &ua->states))
			करो_period_elapsed |= copy_playback_data(&ua->playback,
								&urb->urb,
								frames);
		अन्यथा
			स_रखो(urb->urb.transfer_buffer, 0,
			       urb->urb.iso_frame_desc[0].length);

		/* and off you go ... */
		err = usb_submit_urb(&urb->urb, GFP_ATOMIC);
		अगर (unlikely(err < 0)) अणु
			spin_unlock_irqrestore(&ua->lock, flags);
			पात_usb_playback(ua);
			पात_alsa_playback(ua);
			dev_err(&ua->dev->dev, "USB request error %d: %s\n",
				err, usb_error_string(err));
			वापस;
		पूर्ण
		ua->playback.substream->runसमय->delay += frames;
	पूर्ण
	spin_unlock_irqrestore(&ua->lock, flags);
	अगर (करो_period_elapsed)
		snd_pcm_period_elapsed(ua->playback.substream);
पूर्ण

/* copy data from the URB buffer पूर्णांकo the ALSA ring buffer */
अटल bool copy_capture_data(काष्ठा ua101_stream *stream, काष्ठा urb *urb,
			      अचिन्हित पूर्णांक frames)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित पूर्णांक frame_bytes, frames1;
	u8 *dest;

	runसमय = stream->substream->runसमय;
	frame_bytes = stream->frame_bytes;
	dest = runसमय->dma_area + stream->buffer_pos * frame_bytes;
	अगर (stream->buffer_pos + frames <= runसमय->buffer_size) अणु
		स_नकल(dest, urb->transfer_buffer, frames * frame_bytes);
	पूर्ण अन्यथा अणु
		/* wrap around at end of ring buffer */
		frames1 = runसमय->buffer_size - stream->buffer_pos;
		स_नकल(dest, urb->transfer_buffer, frames1 * frame_bytes);
		स_नकल(runसमय->dma_area,
		       urb->transfer_buffer + frames1 * frame_bytes,
		       (frames - frames1) * frame_bytes);
	पूर्ण

	stream->buffer_pos += frames;
	अगर (stream->buffer_pos >= runसमय->buffer_size)
		stream->buffer_pos -= runसमय->buffer_size;
	stream->period_pos += frames;
	अगर (stream->period_pos >= runसमय->period_size) अणु
		stream->period_pos -= runसमय->period_size;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम capture_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा ua101 *ua = urb->context;
	काष्ठा ua101_stream *stream = &ua->capture;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक frames, ग_लिखो_ptr;
	bool करो_period_elapsed;
	पूर्णांक err;

	अगर (unlikely(urb->status == -ENOENT ||		/* unlinked */
		     urb->status == -ENODEV ||		/* device हटाओd */
		     urb->status == -ECONNRESET ||	/* unlinked */
		     urb->status == -ESHUTDOWN))	/* device disabled */
		जाओ stream_stopped;

	अगर (urb->status >= 0 && urb->iso_frame_desc[0].status >= 0)
		frames = urb->iso_frame_desc[0].actual_length /
			stream->frame_bytes;
	अन्यथा
		frames = 0;

	spin_lock_irqsave(&ua->lock, flags);

	अगर (frames > 0 && test_bit(ALSA_CAPTURE_RUNNING, &ua->states))
		करो_period_elapsed = copy_capture_data(stream, urb, frames);
	अन्यथा
		करो_period_elapsed = false;

	अगर (test_bit(USB_CAPTURE_RUNNING, &ua->states)) अणु
		err = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (unlikely(err < 0)) अणु
			spin_unlock_irqrestore(&ua->lock, flags);
			dev_err(&ua->dev->dev, "USB request error %d: %s\n",
				err, usb_error_string(err));
			जाओ stream_stopped;
		पूर्ण

		/* append packet size to FIFO */
		ग_लिखो_ptr = ua->rate_feedback_start;
		add_with_wraparound(ua, &ग_लिखो_ptr, ua->rate_feedback_count);
		ua->rate_feedback[ग_लिखो_ptr] = frames;
		अगर (ua->rate_feedback_count < ua->playback.queue_length) अणु
			ua->rate_feedback_count++;
			अगर (ua->rate_feedback_count ==
						ua->playback.queue_length)
				wake_up(&ua->rate_feedback_रुको);
		पूर्ण अन्यथा अणु
			/*
			 * Ring buffer overflow; this happens when the playback
			 * stream is not running.  Throw away the oldest entry,
			 * so that the playback stream, when it starts, sees
			 * the most recent packet sizes.
			 */
			add_with_wraparound(ua, &ua->rate_feedback_start, 1);
		पूर्ण
		अगर (test_bit(USB_PLAYBACK_RUNNING, &ua->states) &&
		    !list_empty(&ua->पढ़ोy_playback_urbs))
			queue_work(प्रणाली_highpri_wq, &ua->playback_work);
	पूर्ण

	spin_unlock_irqrestore(&ua->lock, flags);

	अगर (करो_period_elapsed)
		snd_pcm_period_elapsed(stream->substream);

	वापस;

stream_stopped:
	पात_usb_playback(ua);
	पात_usb_capture(ua);
	पात_alsa_playback(ua);
	पात_alsa_capture(ua);
पूर्ण

अटल व्योम first_capture_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा ua101 *ua = urb->context;

	urb->complete = capture_urb_complete;
	capture_urb_complete(urb);

	set_bit(CAPTURE_URB_COMPLETED, &ua->states);
	wake_up(&ua->alsa_capture_रुको);
पूर्ण

अटल पूर्णांक submit_stream_urbs(काष्ठा ua101 *ua, काष्ठा ua101_stream *stream)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < stream->queue_length; ++i) अणु
		पूर्णांक err = usb_submit_urb(&stream->urbs[i]->urb, GFP_KERNEL);
		अगर (err < 0) अणु
			dev_err(&ua->dev->dev, "USB request error %d: %s\n",
				err, usb_error_string(err));
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम समाप्त_stream_urbs(काष्ठा ua101_stream *stream)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < stream->queue_length; ++i)
		अगर (stream->urbs[i])
			usb_समाप्त_urb(&stream->urbs[i]->urb);
पूर्ण

अटल पूर्णांक enable_iso_पूर्णांकerface(काष्ठा ua101 *ua, अचिन्हित पूर्णांक पूर्णांकf_index)
अणु
	काष्ठा usb_host_पूर्णांकerface *alts;

	alts = ua->पूर्णांकf[पूर्णांकf_index]->cur_altsetting;
	अगर (alts->desc.bAlternateSetting != 1) अणु
		पूर्णांक err = usb_set_पूर्णांकerface(ua->dev,
					    alts->desc.bInterfaceNumber, 1);
		अगर (err < 0) अणु
			dev_err(&ua->dev->dev,
				"cannot initialize interface; error %d: %s\n",
				err, usb_error_string(err));
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम disable_iso_पूर्णांकerface(काष्ठा ua101 *ua, अचिन्हित पूर्णांक पूर्णांकf_index)
अणु
	काष्ठा usb_host_पूर्णांकerface *alts;

	अगर (!ua->पूर्णांकf[पूर्णांकf_index])
		वापस;

	alts = ua->पूर्णांकf[पूर्णांकf_index]->cur_altsetting;
	अगर (alts->desc.bAlternateSetting != 0) अणु
		पूर्णांक err = usb_set_पूर्णांकerface(ua->dev,
					    alts->desc.bInterfaceNumber, 0);
		अगर (err < 0 && !test_bit(DISCONNECTED, &ua->states))
			dev_warn(&ua->dev->dev,
				 "interface reset failed; error %d: %s\n",
				 err, usb_error_string(err));
	पूर्ण
पूर्ण

अटल व्योम stop_usb_capture(काष्ठा ua101 *ua)
अणु
	clear_bit(USB_CAPTURE_RUNNING, &ua->states);

	समाप्त_stream_urbs(&ua->capture);

	disable_iso_पूर्णांकerface(ua, INTF_CAPTURE);
पूर्ण

अटल पूर्णांक start_usb_capture(काष्ठा ua101 *ua)
अणु
	पूर्णांक err;

	अगर (test_bit(DISCONNECTED, &ua->states))
		वापस -ENODEV;

	अगर (test_bit(USB_CAPTURE_RUNNING, &ua->states))
		वापस 0;

	समाप्त_stream_urbs(&ua->capture);

	err = enable_iso_पूर्णांकerface(ua, INTF_CAPTURE);
	अगर (err < 0)
		वापस err;

	clear_bit(CAPTURE_URB_COMPLETED, &ua->states);
	ua->capture.urbs[0]->urb.complete = first_capture_urb_complete;
	ua->rate_feedback_start = 0;
	ua->rate_feedback_count = 0;

	set_bit(USB_CAPTURE_RUNNING, &ua->states);
	err = submit_stream_urbs(ua, &ua->capture);
	अगर (err < 0)
		stop_usb_capture(ua);
	वापस err;
पूर्ण

अटल व्योम stop_usb_playback(काष्ठा ua101 *ua)
अणु
	clear_bit(USB_PLAYBACK_RUNNING, &ua->states);

	समाप्त_stream_urbs(&ua->playback);

	cancel_work_sync(&ua->playback_work);

	disable_iso_पूर्णांकerface(ua, INTF_PLAYBACK);
पूर्ण

अटल पूर्णांक start_usb_playback(काष्ठा ua101 *ua)
अणु
	अचिन्हित पूर्णांक i, frames;
	काष्ठा urb *urb;
	पूर्णांक err = 0;

	अगर (test_bit(DISCONNECTED, &ua->states))
		वापस -ENODEV;

	अगर (test_bit(USB_PLAYBACK_RUNNING, &ua->states))
		वापस 0;

	समाप्त_stream_urbs(&ua->playback);
	cancel_work_sync(&ua->playback_work);

	err = enable_iso_पूर्णांकerface(ua, INTF_PLAYBACK);
	अगर (err < 0)
		वापस err;

	clear_bit(PLAYBACK_URB_COMPLETED, &ua->states);
	ua->playback.urbs[0]->urb.complete =
		first_playback_urb_complete;
	spin_lock_irq(&ua->lock);
	INIT_LIST_HEAD(&ua->पढ़ोy_playback_urbs);
	spin_unlock_irq(&ua->lock);

	/*
	 * We submit the initial URBs all at once, so we have to रुको क्रम the
	 * packet size FIFO to be full.
	 */
	रुको_event(ua->rate_feedback_रुको,
		   ua->rate_feedback_count >= ua->playback.queue_length ||
		   !test_bit(USB_CAPTURE_RUNNING, &ua->states) ||
		   test_bit(DISCONNECTED, &ua->states));
	अगर (test_bit(DISCONNECTED, &ua->states)) अणु
		stop_usb_playback(ua);
		वापस -ENODEV;
	पूर्ण
	अगर (!test_bit(USB_CAPTURE_RUNNING, &ua->states)) अणु
		stop_usb_playback(ua);
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < ua->playback.queue_length; ++i) अणु
		/* all initial URBs contain silence */
		spin_lock_irq(&ua->lock);
		frames = ua->rate_feedback[ua->rate_feedback_start];
		add_with_wraparound(ua, &ua->rate_feedback_start, 1);
		ua->rate_feedback_count--;
		spin_unlock_irq(&ua->lock);
		urb = &ua->playback.urbs[i]->urb;
		urb->iso_frame_desc[0].length =
			frames * ua->playback.frame_bytes;
		स_रखो(urb->transfer_buffer, 0,
		       urb->iso_frame_desc[0].length);
	पूर्ण

	set_bit(USB_PLAYBACK_RUNNING, &ua->states);
	err = submit_stream_urbs(ua, &ua->playback);
	अगर (err < 0)
		stop_usb_playback(ua);
	वापस err;
पूर्ण

अटल व्योम पात_alsa_capture(काष्ठा ua101 *ua)
अणु
	अगर (test_bit(ALSA_CAPTURE_RUNNING, &ua->states))
		snd_pcm_stop_xrun(ua->capture.substream);
पूर्ण

अटल व्योम पात_alsa_playback(काष्ठा ua101 *ua)
अणु
	अगर (test_bit(ALSA_PLAYBACK_RUNNING, &ua->states))
		snd_pcm_stop_xrun(ua->playback.substream);
पूर्ण

अटल पूर्णांक set_stream_hw(काष्ठा ua101 *ua, काष्ठा snd_pcm_substream *substream,
			 अचिन्हित पूर्णांक channels)
अणु
	पूर्णांक err;

	substream->runसमय->hw.info =
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_BATCH |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_FIFO_IN_FRAMES;
	substream->runसमय->hw.क्रमmats = ua->क्रमmat_bit;
	substream->runसमय->hw.rates = snd_pcm_rate_to_rate_bit(ua->rate);
	substream->runसमय->hw.rate_min = ua->rate;
	substream->runसमय->hw.rate_max = ua->rate;
	substream->runसमय->hw.channels_min = channels;
	substream->runसमय->hw.channels_max = channels;
	substream->runसमय->hw.buffer_bytes_max = 45000 * 1024;
	substream->runसमय->hw.period_bytes_min = 1;
	substream->runसमय->hw.period_bytes_max = अच_पूर्णांक_उच्च;
	substream->runसमय->hw.periods_min = 2;
	substream->runसमय->hw.periods_max = अच_पूर्णांक_उच्च;
	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
					   SNDRV_PCM_HW_PARAM_PERIOD_TIME,
					   1500000 / ua->packets_per_second,
					   अच_पूर्णांक_उच्च);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_स्थिरraपूर्णांक_msbits(substream->runसमय, 0, 32, 24);
	वापस err;
पूर्ण

अटल पूर्णांक capture_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ua101 *ua = substream->निजी_data;
	पूर्णांक err;

	ua->capture.substream = substream;
	err = set_stream_hw(ua, substream, ua->capture.channels);
	अगर (err < 0)
		वापस err;
	substream->runसमय->hw.fअगरo_size =
		DIV_ROUND_CLOSEST(ua->rate, ua->packets_per_second);
	substream->runसमय->delay = substream->runसमय->hw.fअगरo_size;

	mutex_lock(&ua->mutex);
	err = start_usb_capture(ua);
	अगर (err >= 0)
		set_bit(ALSA_CAPTURE_OPEN, &ua->states);
	mutex_unlock(&ua->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक playback_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ua101 *ua = substream->निजी_data;
	पूर्णांक err;

	ua->playback.substream = substream;
	err = set_stream_hw(ua, substream, ua->playback.channels);
	अगर (err < 0)
		वापस err;
	substream->runसमय->hw.fअगरo_size =
		DIV_ROUND_CLOSEST(ua->rate * ua->playback.queue_length,
				  ua->packets_per_second);

	mutex_lock(&ua->mutex);
	err = start_usb_capture(ua);
	अगर (err < 0)
		जाओ error;
	err = start_usb_playback(ua);
	अगर (err < 0) अणु
		अगर (!test_bit(ALSA_CAPTURE_OPEN, &ua->states))
			stop_usb_capture(ua);
		जाओ error;
	पूर्ण
	set_bit(ALSA_PLAYBACK_OPEN, &ua->states);
error:
	mutex_unlock(&ua->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक capture_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ua101 *ua = substream->निजी_data;

	mutex_lock(&ua->mutex);
	clear_bit(ALSA_CAPTURE_OPEN, &ua->states);
	अगर (!test_bit(ALSA_PLAYBACK_OPEN, &ua->states))
		stop_usb_capture(ua);
	mutex_unlock(&ua->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक playback_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ua101 *ua = substream->निजी_data;

	mutex_lock(&ua->mutex);
	stop_usb_playback(ua);
	clear_bit(ALSA_PLAYBACK_OPEN, &ua->states);
	अगर (!test_bit(ALSA_CAPTURE_OPEN, &ua->states))
		stop_usb_capture(ua);
	mutex_unlock(&ua->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक capture_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा ua101 *ua = substream->निजी_data;
	पूर्णांक err;

	mutex_lock(&ua->mutex);
	err = start_usb_capture(ua);
	mutex_unlock(&ua->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक playback_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा ua101 *ua = substream->निजी_data;
	पूर्णांक err;

	mutex_lock(&ua->mutex);
	err = start_usb_capture(ua);
	अगर (err >= 0)
		err = start_usb_playback(ua);
	mutex_unlock(&ua->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक capture_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ua101 *ua = substream->निजी_data;
	पूर्णांक err;

	mutex_lock(&ua->mutex);
	err = start_usb_capture(ua);
	mutex_unlock(&ua->mutex);
	अगर (err < 0)
		वापस err;

	/*
	 * The EHCI driver schedules the first packet of an iso stream at 10 ms
	 * in the future, i.e., no data is actually captured क्रम that दीर्घ.
	 * Take the रुको here so that the stream is known to be actually
	 * running when the start trigger has been called.
	 */
	रुको_event(ua->alsa_capture_रुको,
		   test_bit(CAPTURE_URB_COMPLETED, &ua->states) ||
		   !test_bit(USB_CAPTURE_RUNNING, &ua->states));
	अगर (test_bit(DISCONNECTED, &ua->states))
		वापस -ENODEV;
	अगर (!test_bit(USB_CAPTURE_RUNNING, &ua->states))
		वापस -EIO;

	ua->capture.period_pos = 0;
	ua->capture.buffer_pos = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक playback_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ua101 *ua = substream->निजी_data;
	पूर्णांक err;

	mutex_lock(&ua->mutex);
	err = start_usb_capture(ua);
	अगर (err >= 0)
		err = start_usb_playback(ua);
	mutex_unlock(&ua->mutex);
	अगर (err < 0)
		वापस err;

	/* see the comment in capture_pcm_prepare() */
	रुको_event(ua->alsa_playback_रुको,
		   test_bit(PLAYBACK_URB_COMPLETED, &ua->states) ||
		   !test_bit(USB_PLAYBACK_RUNNING, &ua->states));
	अगर (test_bit(DISCONNECTED, &ua->states))
		वापस -ENODEV;
	अगर (!test_bit(USB_PLAYBACK_RUNNING, &ua->states))
		वापस -EIO;

	substream->runसमय->delay = 0;
	ua->playback.period_pos = 0;
	ua->playback.buffer_pos = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक capture_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा ua101 *ua = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (!test_bit(USB_CAPTURE_RUNNING, &ua->states))
			वापस -EIO;
		set_bit(ALSA_CAPTURE_RUNNING, &ua->states);
		वापस 0;
	हाल SNDRV_PCM_TRIGGER_STOP:
		clear_bit(ALSA_CAPTURE_RUNNING, &ua->states);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक playback_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा ua101 *ua = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (!test_bit(USB_PLAYBACK_RUNNING, &ua->states))
			वापस -EIO;
		set_bit(ALSA_PLAYBACK_RUNNING, &ua->states);
		वापस 0;
	हाल SNDRV_PCM_TRIGGER_STOP:
		clear_bit(ALSA_PLAYBACK_RUNNING, &ua->states);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत snd_pcm_uframes_t ua101_pcm_poपूर्णांकer(काष्ठा ua101 *ua,
						  काष्ठा ua101_stream *stream)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक pos;

	spin_lock_irqsave(&ua->lock, flags);
	pos = stream->buffer_pos;
	spin_unlock_irqrestore(&ua->lock, flags);
	वापस pos;
पूर्ण

अटल snd_pcm_uframes_t capture_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा ua101 *ua = subs->निजी_data;

	वापस ua101_pcm_poपूर्णांकer(ua, &ua->capture);
पूर्ण

अटल snd_pcm_uframes_t playback_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा ua101 *ua = subs->निजी_data;

	वापस ua101_pcm_poपूर्णांकer(ua, &ua->playback);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops capture_pcm_ops = अणु
	.खोलो = capture_pcm_खोलो,
	.बंद = capture_pcm_बंद,
	.hw_params = capture_pcm_hw_params,
	.prepare = capture_pcm_prepare,
	.trigger = capture_pcm_trigger,
	.poपूर्णांकer = capture_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops playback_pcm_ops = अणु
	.खोलो = playback_pcm_खोलो,
	.बंद = playback_pcm_बंद,
	.hw_params = playback_pcm_hw_params,
	.prepare = playback_pcm_prepare,
	.trigger = playback_pcm_trigger,
	.poपूर्णांकer = playback_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा uac_क्रमmat_type_i_discrete_descriptor *
find_क्रमmat_descriptor(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_host_पूर्णांकerface *alt;
	u8 *extra;
	पूर्णांक extralen;

	अगर (पूर्णांकerface->num_altsetting != 2) अणु
		dev_err(&पूर्णांकerface->dev, "invalid num_altsetting\n");
		वापस शून्य;
	पूर्ण

	alt = &पूर्णांकerface->altsetting[0];
	अगर (alt->desc.bNumEndpoपूर्णांकs != 0) अणु
		dev_err(&पूर्णांकerface->dev, "invalid bNumEndpoints\n");
		वापस शून्य;
	पूर्ण

	alt = &पूर्णांकerface->altsetting[1];
	अगर (alt->desc.bNumEndpoपूर्णांकs != 1) अणु
		dev_err(&पूर्णांकerface->dev, "invalid bNumEndpoints\n");
		वापस शून्य;
	पूर्ण

	extra = alt->extra;
	extralen = alt->extralen;
	जबतक (extralen >= माप(काष्ठा usb_descriptor_header)) अणु
		काष्ठा uac_क्रमmat_type_i_discrete_descriptor *desc;

		desc = (काष्ठा uac_क्रमmat_type_i_discrete_descriptor *)extra;
		अगर (desc->bLength > extralen) अणु
			dev_err(&पूर्णांकerface->dev, "descriptor overflow\n");
			वापस शून्य;
		पूर्ण
		अगर (desc->bLength == UAC_FORMAT_TYPE_I_DISCRETE_DESC_SIZE(1) &&
		    desc->bDescriptorType == USB_DT_CS_INTERFACE &&
		    desc->bDescriptorSubtype == UAC_FORMAT_TYPE) अणु
			अगर (desc->bFormatType != UAC_FORMAT_TYPE_I_PCM ||
			    desc->bSamFreqType != 1) अणु
				dev_err(&पूर्णांकerface->dev,
					"invalid format type\n");
				वापस शून्य;
			पूर्ण
			वापस desc;
		पूर्ण
		extralen -= desc->bLength;
		extra += desc->bLength;
	पूर्ण
	dev_err(&पूर्णांकerface->dev, "sample format descriptor not found\n");
	वापस शून्य;
पूर्ण

अटल पूर्णांक detect_usb_क्रमmat(काष्ठा ua101 *ua)
अणु
	स्थिर काष्ठा uac_क्रमmat_type_i_discrete_descriptor *fmt_capture;
	स्थिर काष्ठा uac_क्रमmat_type_i_discrete_descriptor *fmt_playback;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd;
	अचिन्हित पूर्णांक rate2;

	fmt_capture = find_क्रमmat_descriptor(ua->पूर्णांकf[INTF_CAPTURE]);
	fmt_playback = find_क्रमmat_descriptor(ua->पूर्णांकf[INTF_PLAYBACK]);
	अगर (!fmt_capture || !fmt_playback)
		वापस -ENXIO;

	चयन (fmt_capture->bSubframeSize) अणु
	हाल 3:
		ua->क्रमmat_bit = SNDRV_PCM_FMTBIT_S24_3LE;
		अवरोध;
	हाल 4:
		ua->क्रमmat_bit = SNDRV_PCM_FMTBIT_S32_LE;
		अवरोध;
	शेष:
		dev_err(&ua->dev->dev, "sample width is not 24 or 32 bits\n");
		वापस -ENXIO;
	पूर्ण
	अगर (fmt_capture->bSubframeSize != fmt_playback->bSubframeSize) अणु
		dev_err(&ua->dev->dev,
			"playback/capture sample widths do not match\n");
		वापस -ENXIO;
	पूर्ण

	अगर (fmt_capture->bBitResolution != 24 ||
	    fmt_playback->bBitResolution != 24) अणु
		dev_err(&ua->dev->dev, "sample width is not 24 bits\n");
		वापस -ENXIO;
	पूर्ण

	ua->rate = combine_triple(fmt_capture->tSamFreq[0]);
	rate2 = combine_triple(fmt_playback->tSamFreq[0]);
	अगर (ua->rate != rate2) अणु
		dev_err(&ua->dev->dev,
			"playback/capture rates do not match: %u/%u\n",
			rate2, ua->rate);
		वापस -ENXIO;
	पूर्ण

	चयन (ua->dev->speed) अणु
	हाल USB_SPEED_FULL:
		ua->packets_per_second = 1000;
		अवरोध;
	हाल USB_SPEED_HIGH:
		ua->packets_per_second = 8000;
		अवरोध;
	शेष:
		dev_err(&ua->dev->dev, "unknown device speed\n");
		वापस -ENXIO;
	पूर्ण

	ua->capture.channels = fmt_capture->bNrChannels;
	ua->playback.channels = fmt_playback->bNrChannels;
	ua->capture.frame_bytes =
		fmt_capture->bSubframeSize * ua->capture.channels;
	ua->playback.frame_bytes =
		fmt_playback->bSubframeSize * ua->playback.channels;

	epd = &ua->पूर्णांकf[INTF_CAPTURE]->altsetting[1].endpoपूर्णांक[0].desc;
	अगर (!usb_endpoपूर्णांक_is_isoc_in(epd)) अणु
		dev_err(&ua->dev->dev, "invalid capture endpoint\n");
		वापस -ENXIO;
	पूर्ण
	ua->capture.usb_pipe = usb_rcvisocpipe(ua->dev, usb_endpoपूर्णांक_num(epd));
	ua->capture.max_packet_bytes = usb_endpoपूर्णांक_maxp(epd);

	epd = &ua->पूर्णांकf[INTF_PLAYBACK]->altsetting[1].endpoपूर्णांक[0].desc;
	अगर (!usb_endpoपूर्णांक_is_isoc_out(epd)) अणु
		dev_err(&ua->dev->dev, "invalid playback endpoint\n");
		वापस -ENXIO;
	पूर्ण
	ua->playback.usb_pipe = usb_sndisocpipe(ua->dev, usb_endpoपूर्णांक_num(epd));
	ua->playback.max_packet_bytes = usb_endpoपूर्णांक_maxp(epd);
	वापस 0;
पूर्ण

अटल पूर्णांक alloc_stream_buffers(काष्ठा ua101 *ua, काष्ठा ua101_stream *stream)
अणु
	अचिन्हित पूर्णांक reमुख्यing_packets, packets, packets_per_page, i;
	माप_प्रकार size;

	stream->queue_length = queue_length;
	stream->queue_length = max(stream->queue_length,
				   (अचिन्हित पूर्णांक)MIN_QUEUE_LENGTH);
	stream->queue_length = min(stream->queue_length,
				   (अचिन्हित पूर्णांक)MAX_QUEUE_LENGTH);

	/*
	 * The cache pool sizes used by usb_alloc_coherent() (128, 512, 2048) are
	 * quite bad when used with the packet sizes of this device (e.g. 280,
	 * 520, 624).  Thereक्रमe, we allocate and subभागide entire pages, using
	 * a smaller buffer only क्रम the last chunk.
	 */
	reमुख्यing_packets = stream->queue_length;
	packets_per_page = PAGE_SIZE / stream->max_packet_bytes;
	क्रम (i = 0; i < ARRAY_SIZE(stream->buffers); ++i) अणु
		packets = min(reमुख्यing_packets, packets_per_page);
		size = packets * stream->max_packet_bytes;
		stream->buffers[i].addr =
			usb_alloc_coherent(ua->dev, size, GFP_KERNEL,
					   &stream->buffers[i].dma);
		अगर (!stream->buffers[i].addr)
			वापस -ENOMEM;
		stream->buffers[i].size = size;
		reमुख्यing_packets -= packets;
		अगर (!reमुख्यing_packets)
			अवरोध;
	पूर्ण
	अगर (reमुख्यing_packets) अणु
		dev_err(&ua->dev->dev, "too many packets\n");
		वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम मुक्त_stream_buffers(काष्ठा ua101 *ua, काष्ठा ua101_stream *stream)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(stream->buffers); ++i)
		usb_मुक्त_coherent(ua->dev,
				  stream->buffers[i].size,
				  stream->buffers[i].addr,
				  stream->buffers[i].dma);
पूर्ण

अटल पूर्णांक alloc_stream_urbs(काष्ठा ua101 *ua, काष्ठा ua101_stream *stream,
			     व्योम (*urb_complete)(काष्ठा urb *))
अणु
	अचिन्हित max_packet_size = stream->max_packet_bytes;
	काष्ठा ua101_urb *urb;
	अचिन्हित पूर्णांक b, u = 0;

	क्रम (b = 0; b < ARRAY_SIZE(stream->buffers); ++b) अणु
		अचिन्हित पूर्णांक size = stream->buffers[b].size;
		u8 *addr = stream->buffers[b].addr;
		dma_addr_t dma = stream->buffers[b].dma;

		जबतक (size >= max_packet_size) अणु
			अगर (u >= stream->queue_length)
				जाओ bufsize_error;
			urb = kदो_स्मृति(माप(*urb), GFP_KERNEL);
			अगर (!urb)
				वापस -ENOMEM;
			usb_init_urb(&urb->urb);
			urb->urb.dev = ua->dev;
			urb->urb.pipe = stream->usb_pipe;
			urb->urb.transfer_flags = URB_NO_TRANSFER_DMA_MAP;
			urb->urb.transfer_buffer = addr;
			urb->urb.transfer_dma = dma;
			urb->urb.transfer_buffer_length = max_packet_size;
			urb->urb.number_of_packets = 1;
			urb->urb.पूर्णांकerval = 1;
			urb->urb.context = ua;
			urb->urb.complete = urb_complete;
			urb->urb.iso_frame_desc[0].offset = 0;
			urb->urb.iso_frame_desc[0].length = max_packet_size;
			stream->urbs[u++] = urb;
			size -= max_packet_size;
			addr += max_packet_size;
			dma += max_packet_size;
		पूर्ण
	पूर्ण
	अगर (u == stream->queue_length)
		वापस 0;
bufsize_error:
	dev_err(&ua->dev->dev, "internal buffer size error\n");
	वापस -ENXIO;
पूर्ण

अटल व्योम मुक्त_stream_urbs(काष्ठा ua101_stream *stream)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < stream->queue_length; ++i) अणु
		kमुक्त(stream->urbs[i]);
		stream->urbs[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_usb_related_resources(काष्ठा ua101 *ua,
				       काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	mutex_lock(&ua->mutex);
	मुक्त_stream_urbs(&ua->capture);
	मुक्त_stream_urbs(&ua->playback);
	mutex_unlock(&ua->mutex);
	मुक्त_stream_buffers(ua, &ua->capture);
	मुक्त_stream_buffers(ua, &ua->playback);

	क्रम (i = 0; i < ARRAY_SIZE(ua->पूर्णांकf); ++i) अणु
		mutex_lock(&ua->mutex);
		पूर्णांकf = ua->पूर्णांकf[i];
		ua->पूर्णांकf[i] = शून्य;
		mutex_unlock(&ua->mutex);
		अगर (पूर्णांकf) अणु
			usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
			अगर (पूर्णांकf != पूर्णांकerface)
				usb_driver_release_पूर्णांकerface(&ua101_driver,
							     पूर्णांकf);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ua101_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा ua101 *ua = card->निजी_data;

	mutex_destroy(&ua->mutex);
पूर्ण

अटल पूर्णांक ua101_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		       स्थिर काष्ठा usb_device_id *usb_id)
अणु
	अटल स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info midi_ep = अणु
		.out_cables = 0x0001,
		.in_cables = 0x0001
	पूर्ण;
	अटल स्थिर काष्ठा snd_usb_audio_quirk midi_quirk = अणु
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = &midi_ep
	पूर्ण;
	अटल स्थिर पूर्णांक पूर्णांकf_numbers[2][3] = अणु
		अणु	/* UA-101 */
			[INTF_PLAYBACK] = 0,
			[INTF_CAPTURE] = 1,
			[INTF_MIDI] = 2,
		पूर्ण,
		अणु	/* UA-1000 */
			[INTF_CAPTURE] = 1,
			[INTF_PLAYBACK] = 2,
			[INTF_MIDI] = 3,
		पूर्ण,
	पूर्ण;
	काष्ठा snd_card *card;
	काष्ठा ua101 *ua;
	अचिन्हित पूर्णांक card_index, i;
	पूर्णांक is_ua1000;
	स्थिर अक्षर *name;
	अक्षर usb_path[32];
	पूर्णांक err;

	is_ua1000 = usb_id->idProduct == 0x0044;

	अगर (पूर्णांकerface->altsetting->desc.bInterfaceNumber !=
	    पूर्णांकf_numbers[is_ua1000][0])
		वापस -ENODEV;

	mutex_lock(&devices_mutex);

	क्रम (card_index = 0; card_index < SNDRV_CARDS; ++card_index)
		अगर (enable[card_index] && !(devices_used & (1 << card_index)))
			अवरोध;
	अगर (card_index >= SNDRV_CARDS) अणु
		mutex_unlock(&devices_mutex);
		वापस -ENOENT;
	पूर्ण
	err = snd_card_new(&पूर्णांकerface->dev,
			   index[card_index], id[card_index], THIS_MODULE,
			   माप(*ua), &card);
	अगर (err < 0) अणु
		mutex_unlock(&devices_mutex);
		वापस err;
	पूर्ण
	card->निजी_मुक्त = ua101_card_मुक्त;
	ua = card->निजी_data;
	ua->dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	ua->card = card;
	ua->card_index = card_index;
	INIT_LIST_HEAD(&ua->midi_list);
	spin_lock_init(&ua->lock);
	mutex_init(&ua->mutex);
	INIT_LIST_HEAD(&ua->पढ़ोy_playback_urbs);
	INIT_WORK(&ua->playback_work, playback_work);
	init_रुकोqueue_head(&ua->alsa_capture_रुको);
	init_रुकोqueue_head(&ua->rate_feedback_रुको);
	init_रुकोqueue_head(&ua->alsa_playback_रुको);

	ua->पूर्णांकf[0] = पूर्णांकerface;
	क्रम (i = 1; i < ARRAY_SIZE(ua->पूर्णांकf); ++i) अणु
		ua->पूर्णांकf[i] = usb_अगरnum_to_अगर(ua->dev,
					      पूर्णांकf_numbers[is_ua1000][i]);
		अगर (!ua->पूर्णांकf[i]) अणु
			dev_err(&ua->dev->dev, "interface %u not found\n",
				पूर्णांकf_numbers[is_ua1000][i]);
			err = -ENXIO;
			जाओ probe_error;
		पूर्ण
		err = usb_driver_claim_पूर्णांकerface(&ua101_driver,
						 ua->पूर्णांकf[i], ua);
		अगर (err < 0) अणु
			ua->पूर्णांकf[i] = शून्य;
			err = -EBUSY;
			जाओ probe_error;
		पूर्ण
	पूर्ण

	err = detect_usb_क्रमmat(ua);
	अगर (err < 0)
		जाओ probe_error;

	name = usb_id->idProduct == 0x0044 ? "UA-1000" : "UA-101";
	म_नकल(card->driver, "UA-101");
	म_नकल(card->लघुname, name);
	usb_make_path(ua->dev, usb_path, माप(usb_path));
	snम_लिखो(ua->card->दीर्घname, माप(ua->card->दीर्घname),
		 "EDIROL %s (serial %s), %u Hz at %s, %s speed", name,
		 ua->dev->serial ? ua->dev->serial : "?", ua->rate, usb_path,
		 ua->dev->speed == USB_SPEED_HIGH ? "high" : "full");

	err = alloc_stream_buffers(ua, &ua->capture);
	अगर (err < 0)
		जाओ probe_error;
	err = alloc_stream_buffers(ua, &ua->playback);
	अगर (err < 0)
		जाओ probe_error;

	err = alloc_stream_urbs(ua, &ua->capture, capture_urb_complete);
	अगर (err < 0)
		जाओ probe_error;
	err = alloc_stream_urbs(ua, &ua->playback, playback_urb_complete);
	अगर (err < 0)
		जाओ probe_error;

	err = snd_pcm_new(card, name, 0, 1, 1, &ua->pcm);
	अगर (err < 0)
		जाओ probe_error;
	ua->pcm->निजी_data = ua;
	म_नकल(ua->pcm->name, name);
	snd_pcm_set_ops(ua->pcm, SNDRV_PCM_STREAM_PLAYBACK, &playback_pcm_ops);
	snd_pcm_set_ops(ua->pcm, SNDRV_PCM_STREAM_CAPTURE, &capture_pcm_ops);
	snd_pcm_set_managed_buffer_all(ua->pcm, SNDRV_DMA_TYPE_VMALLOC,
				       शून्य, 0, 0);

	err = snd_usbmidi_create(card, ua->पूर्णांकf[INTF_MIDI],
				 &ua->midi_list, &midi_quirk);
	अगर (err < 0)
		जाओ probe_error;

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ probe_error;

	usb_set_पूर्णांकfdata(पूर्णांकerface, ua);
	devices_used |= 1 << card_index;

	mutex_unlock(&devices_mutex);
	वापस 0;

probe_error:
	मुक्त_usb_related_resources(ua, पूर्णांकerface);
	snd_card_मुक्त(card);
	mutex_unlock(&devices_mutex);
	वापस err;
पूर्ण

अटल व्योम ua101_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ua101 *ua = usb_get_पूर्णांकfdata(पूर्णांकerface);
	काष्ठा list_head *midi;

	अगर (!ua)
		वापस;

	mutex_lock(&devices_mutex);

	set_bit(DISCONNECTED, &ua->states);
	wake_up(&ua->rate_feedback_रुको);

	/* make sure that userspace cannot create new requests */
	snd_card_disconnect(ua->card);

	/* make sure that there are no pending USB requests */
	list_क्रम_each(midi, &ua->midi_list)
		snd_usbmidi_disconnect(midi);
	पात_alsa_playback(ua);
	पात_alsa_capture(ua);
	mutex_lock(&ua->mutex);
	stop_usb_playback(ua);
	stop_usb_capture(ua);
	mutex_unlock(&ua->mutex);

	मुक्त_usb_related_resources(ua, पूर्णांकerface);

	devices_used &= ~(1 << ua->card_index);

	snd_card_मुक्त_when_बंदd(ua->card);

	mutex_unlock(&devices_mutex);
पूर्ण

अटल स्थिर काष्ठा usb_device_id ua101_ids[] = अणु
	अणु USB_DEVICE(0x0582, 0x0044) पूर्ण, /* UA-1000 high speed */
	अणु USB_DEVICE(0x0582, 0x007d) पूर्ण, /* UA-101 high speed */
	अणु USB_DEVICE(0x0582, 0x008d) पूर्ण, /* UA-101 full speed */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, ua101_ids);

अटल काष्ठा usb_driver ua101_driver = अणु
	.name = "snd-ua101",
	.id_table = ua101_ids,
	.probe = ua101_probe,
	.disconnect = ua101_disconnect,
#अगर 0
	.suspend = ua101_suspend,
	.resume = ua101_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(ua101_driver);
