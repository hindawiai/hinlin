<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "usbaudio.h"
#समावेश "helper.h"
#समावेश "card.h"
#समावेश "endpoint.h"
#समावेश "pcm.h"
#समावेश "clock.h"
#समावेश "quirks.h"

क्रमागत अणु
	EP_STATE_STOPPED,
	EP_STATE_RUNNING,
	EP_STATE_STOPPING,
पूर्ण;

/* पूर्णांकerface refcounting */
काष्ठा snd_usb_अगरace_ref अणु
	अचिन्हित अक्षर अगरace;
	bool need_setup;
	पूर्णांक खोलोed;
	काष्ठा list_head list;
पूर्ण;

/*
 * snd_usb_endpoपूर्णांक is a model that असलtracts everything related to an
 * USB endpoपूर्णांक and its streaming.
 *
 * There are functions to activate and deactivate the streaming URBs and
 * optional callbacks to let the pcm logic handle the actual content of the
 * packets क्रम playback and record. Thus, the bus streaming and the audio
 * handlers are fully decoupled.
 *
 * There are two dअगरferent types of endpoपूर्णांकs in audio applications.
 *
 * SND_USB_ENDPOINT_TYPE_DATA handles full audio data payload क्रम both
 * inbound and outbound traffic.
 *
 * SND_USB_ENDPOINT_TYPE_SYNC endpoपूर्णांकs are क्रम inbound traffic only and
 * expect the payload to carry Q10.14 / Q16.16 क्रमmatted sync inक्रमmation
 * (3 or 4 bytes).
 *
 * Each endpoपूर्णांक has to be configured prior to being used by calling
 * snd_usb_endpoपूर्णांक_set_params().
 *
 * The model incorporates a reference counting, so that multiple users
 * can call snd_usb_endpoपूर्णांक_start() and snd_usb_endpoपूर्णांक_stop(), and
 * only the first user will effectively start the URBs, and only the last
 * one to stop it will tear the URBs करोwn again.
 */

/*
 * convert a sampling rate पूर्णांकo our full speed क्रमmat (fs/1000 in Q16.16)
 * this will overflow at approx 524 kHz
 */
अटल अंतरभूत अचिन्हित get_usb_full_speed_rate(अचिन्हित पूर्णांक rate)
अणु
	वापस ((rate << 13) + 62) / 125;
पूर्ण

/*
 * convert a sampling rate पूर्णांकo USB high speed क्रमmat (fs/8000 in Q16.16)
 * this will overflow at approx 4 MHz
 */
अटल अंतरभूत अचिन्हित get_usb_high_speed_rate(अचिन्हित पूर्णांक rate)
अणु
	वापस ((rate << 10) + 62) / 125;
पूर्ण

/*
 * release a urb data
 */
अटल व्योम release_urb_ctx(काष्ठा snd_urb_ctx *u)
अणु
	अगर (u->buffer_size)
		usb_मुक्त_coherent(u->ep->chip->dev, u->buffer_size,
				  u->urb->transfer_buffer,
				  u->urb->transfer_dma);
	usb_मुक्त_urb(u->urb);
	u->urb = शून्य;
पूर्ण

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

अटल अंतरभूत bool ep_state_running(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	वापस atomic_पढ़ो(&ep->state) == EP_STATE_RUNNING;
पूर्ण

अटल अंतरभूत bool ep_state_update(काष्ठा snd_usb_endpoपूर्णांक *ep, पूर्णांक old, पूर्णांक new)
अणु
	वापस atomic_cmpxchg(&ep->state, old, new) == old;
पूर्ण

/**
 * snd_usb_endpoपूर्णांक_implicit_feedback_sink: Report endpoपूर्णांक usage type
 *
 * @ep: The snd_usb_endpoपूर्णांक
 *
 * Determine whether an endpoपूर्णांक is driven by an implicit feedback
 * data endpoपूर्णांक source.
 */
पूर्णांक snd_usb_endpoपूर्णांक_implicit_feedback_sink(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	वापस  ep->implicit_fb_sync && usb_pipeout(ep->pipe);
पूर्ण

/*
 * Return the number of samples to be sent in the next packet
 * क्रम streaming based on inक्रमmation derived from sync endpoपूर्णांकs
 *
 * This won't be used क्रम implicit feedback which takes the packet size
 * वापसed from the sync source
 */
अटल पूर्णांक slave_next_packet_size(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (ep->fill_max)
		वापस ep->maxframesize;

	spin_lock_irqsave(&ep->lock, flags);
	ep->phase = (ep->phase & 0xffff)
		+ (ep->freqm << ep->dataपूर्णांकerval);
	ret = min(ep->phase >> 16, ep->maxframesize);
	spin_unlock_irqrestore(&ep->lock, flags);

	वापस ret;
पूर्ण

/*
 * Return the number of samples to be sent in the next packet
 * क्रम adaptive and synchronous endpoपूर्णांकs
 */
अटल पूर्णांक next_packet_size(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	पूर्णांक ret;

	अगर (ep->fill_max)
		वापस ep->maxframesize;

	ep->sample_accum += ep->sample_rem;
	अगर (ep->sample_accum >= ep->pps) अणु
		ep->sample_accum -= ep->pps;
		ret = ep->packsize[1];
	पूर्ण अन्यथा अणु
		ret = ep->packsize[0];
	पूर्ण

	वापस ret;
पूर्ण

/*
 * snd_usb_endpoपूर्णांक_next_packet_size: Return the number of samples to be sent
 * in the next packet
 */
पूर्णांक snd_usb_endpoपूर्णांक_next_packet_size(काष्ठा snd_usb_endpoपूर्णांक *ep,
				      काष्ठा snd_urb_ctx *ctx, पूर्णांक idx)
अणु
	अगर (ctx->packet_size[idx])
		वापस ctx->packet_size[idx];
	अन्यथा अगर (ep->sync_source)
		वापस slave_next_packet_size(ep);
	अन्यथा
		वापस next_packet_size(ep);
पूर्ण

अटल व्योम call_retire_callback(काष्ठा snd_usb_endpoपूर्णांक *ep,
				 काष्ठा urb *urb)
अणु
	काष्ठा snd_usb_substream *data_subs;

	data_subs = READ_ONCE(ep->data_subs);
	अगर (data_subs && ep->retire_data_urb)
		ep->retire_data_urb(data_subs, urb);
पूर्ण

अटल व्योम retire_outbound_urb(काष्ठा snd_usb_endpoपूर्णांक *ep,
				काष्ठा snd_urb_ctx *urb_ctx)
अणु
	call_retire_callback(ep, urb_ctx->urb);
पूर्ण

अटल व्योम snd_usb_handle_sync_urb(काष्ठा snd_usb_endpoपूर्णांक *ep,
				    काष्ठा snd_usb_endpoपूर्णांक *sender,
				    स्थिर काष्ठा urb *urb);

अटल व्योम retire_inbound_urb(काष्ठा snd_usb_endpoपूर्णांक *ep,
			       काष्ठा snd_urb_ctx *urb_ctx)
अणु
	काष्ठा urb *urb = urb_ctx->urb;
	काष्ठा snd_usb_endpoपूर्णांक *sync_sink;

	अगर (unlikely(ep->skip_packets > 0)) अणु
		ep->skip_packets--;
		वापस;
	पूर्ण

	sync_sink = READ_ONCE(ep->sync_sink);
	अगर (sync_sink)
		snd_usb_handle_sync_urb(sync_sink, ep, urb);

	call_retire_callback(ep, urb);
पूर्ण

अटल व्योम prepare_silent_urb(काष्ठा snd_usb_endpoपूर्णांक *ep,
			       काष्ठा snd_urb_ctx *ctx)
अणु
	काष्ठा urb *urb = ctx->urb;
	अचिन्हित पूर्णांक offs = 0;
	अचिन्हित पूर्णांक extra = 0;
	__le32 packet_length;
	पूर्णांक i;

	/* For tx_length_quirk, put packet length at start of packet */
	अगर (ep->chip->tx_length_quirk)
		extra = माप(packet_length);

	क्रम (i = 0; i < ctx->packets; ++i) अणु
		अचिन्हित पूर्णांक offset;
		अचिन्हित पूर्णांक length;
		पूर्णांक counts;

		counts = snd_usb_endpoपूर्णांक_next_packet_size(ep, ctx, i);
		length = counts * ep->stride; /* number of silent bytes */
		offset = offs * ep->stride + extra * i;
		urb->iso_frame_desc[i].offset = offset;
		urb->iso_frame_desc[i].length = length + extra;
		अगर (extra) अणु
			packet_length = cpu_to_le32(length);
			स_नकल(urb->transfer_buffer + offset,
			       &packet_length, माप(packet_length));
		पूर्ण
		स_रखो(urb->transfer_buffer + offset + extra,
		       ep->silence_value, length);
		offs += counts;
	पूर्ण

	urb->number_of_packets = ctx->packets;
	urb->transfer_buffer_length = offs * ep->stride + ctx->packets * extra;
पूर्ण

/*
 * Prepare a PLAYBACK urb क्रम submission to the bus.
 */
अटल व्योम prepare_outbound_urb(काष्ठा snd_usb_endpoपूर्णांक *ep,
				 काष्ठा snd_urb_ctx *ctx)
अणु
	काष्ठा urb *urb = ctx->urb;
	अचिन्हित अक्षर *cp = urb->transfer_buffer;
	काष्ठा snd_usb_substream *data_subs;

	urb->dev = ep->chip->dev; /* we need to set this at each समय */

	चयन (ep->type) अणु
	हाल SND_USB_ENDPOINT_TYPE_DATA:
		data_subs = READ_ONCE(ep->data_subs);
		अगर (data_subs && ep->prepare_data_urb)
			ep->prepare_data_urb(data_subs, urb);
		अन्यथा /* no data provider, so send silence */
			prepare_silent_urb(ep, ctx);
		अवरोध;

	हाल SND_USB_ENDPOINT_TYPE_SYNC:
		अगर (snd_usb_get_speed(ep->chip->dev) >= USB_SPEED_HIGH) अणु
			/*
			 * fill the length and offset of each urb descriptor.
			 * the fixed 12.13 frequency is passed as 16.16 through the pipe.
			 */
			urb->iso_frame_desc[0].length = 4;
			urb->iso_frame_desc[0].offset = 0;
			cp[0] = ep->freqn;
			cp[1] = ep->freqn >> 8;
			cp[2] = ep->freqn >> 16;
			cp[3] = ep->freqn >> 24;
		पूर्ण अन्यथा अणु
			/*
			 * fill the length and offset of each urb descriptor.
			 * the fixed 10.14 frequency is passed through the pipe.
			 */
			urb->iso_frame_desc[0].length = 3;
			urb->iso_frame_desc[0].offset = 0;
			cp[0] = ep->freqn >> 2;
			cp[1] = ep->freqn >> 10;
			cp[2] = ep->freqn >> 18;
		पूर्ण

		अवरोध;
	पूर्ण
पूर्ण

/*
 * Prepare a CAPTURE or SYNC urb क्रम submission to the bus.
 */
अटल अंतरभूत व्योम prepare_inbound_urb(काष्ठा snd_usb_endpoपूर्णांक *ep,
				       काष्ठा snd_urb_ctx *urb_ctx)
अणु
	पूर्णांक i, offs;
	काष्ठा urb *urb = urb_ctx->urb;

	urb->dev = ep->chip->dev; /* we need to set this at each समय */

	चयन (ep->type) अणु
	हाल SND_USB_ENDPOINT_TYPE_DATA:
		offs = 0;
		क्रम (i = 0; i < urb_ctx->packets; i++) अणु
			urb->iso_frame_desc[i].offset = offs;
			urb->iso_frame_desc[i].length = ep->curpacksize;
			offs += ep->curpacksize;
		पूर्ण

		urb->transfer_buffer_length = offs;
		urb->number_of_packets = urb_ctx->packets;
		अवरोध;

	हाल SND_USB_ENDPOINT_TYPE_SYNC:
		urb->iso_frame_desc[0].length = min(4u, ep->syncmaxsize);
		urb->iso_frame_desc[0].offset = 0;
		अवरोध;
	पूर्ण
पूर्ण

/* notअगरy an error as XRUN to the asचिन्हित PCM data substream */
अटल व्योम notअगरy_xrun(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	काष्ठा snd_usb_substream *data_subs;

	data_subs = READ_ONCE(ep->data_subs);
	अगर (data_subs && data_subs->pcm_substream)
		snd_pcm_stop_xrun(data_subs->pcm_substream);
पूर्ण

अटल काष्ठा snd_usb_packet_info *
next_packet_fअगरo_enqueue(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	काष्ठा snd_usb_packet_info *p;

	p = ep->next_packet + (ep->next_packet_head + ep->next_packet_queued) %
		ARRAY_SIZE(ep->next_packet);
	ep->next_packet_queued++;
	वापस p;
पूर्ण

अटल काष्ठा snd_usb_packet_info *
next_packet_fअगरo_dequeue(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	काष्ठा snd_usb_packet_info *p;

	p = ep->next_packet + ep->next_packet_head;
	ep->next_packet_head++;
	ep->next_packet_head %= ARRAY_SIZE(ep->next_packet);
	ep->next_packet_queued--;
	वापस p;
पूर्ण

/*
 * Send output urbs that have been prepared previously. URBs are dequeued
 * from ep->पढ़ोy_playback_urbs and in हाल there aren't any available
 * or there are no packets that have been prepared, this function करोes
 * nothing.
 *
 * The reason why the functionality of sending and preparing URBs is separated
 * is that host controllers करोn't guarantee the order in which they वापस
 * inbound and outbound packets to their submitters.
 *
 * This function is only used क्रम implicit feedback endpoपूर्णांकs. For endpoपूर्णांकs
 * driven by dedicated sync endpoपूर्णांकs, URBs are immediately re-submitted
 * from their completion handler.
 */
अटल व्योम queue_pending_output_urbs(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	जबतक (ep_state_running(ep)) अणु

		अचिन्हित दीर्घ flags;
		काष्ठा snd_usb_packet_info *packet;
		काष्ठा snd_urb_ctx *ctx = शून्य;
		पूर्णांक err, i;

		spin_lock_irqsave(&ep->lock, flags);
		अगर (ep->next_packet_queued > 0 &&
		    !list_empty(&ep->पढ़ोy_playback_urbs)) अणु
			/* take URB out of FIFO */
			ctx = list_first_entry(&ep->पढ़ोy_playback_urbs,
					       काष्ठा snd_urb_ctx, पढ़ोy_list);
			list_del_init(&ctx->पढ़ोy_list);

			packet = next_packet_fअगरo_dequeue(ep);
		पूर्ण
		spin_unlock_irqrestore(&ep->lock, flags);

		अगर (ctx == शून्य)
			वापस;

		/* copy over the length inक्रमmation */
		क्रम (i = 0; i < packet->packets; i++)
			ctx->packet_size[i] = packet->packet_size[i];

		/* call the data handler to fill in playback data */
		prepare_outbound_urb(ep, ctx);

		err = usb_submit_urb(ctx->urb, GFP_ATOMIC);
		अगर (err < 0) अणु
			usb_audio_err(ep->chip,
				      "Unable to submit urb #%d: %d at %s\n",
				      ctx->index, err, __func__);
			notअगरy_xrun(ep);
			वापस;
		पूर्ण

		set_bit(ctx->index, &ep->active_mask);
	पूर्ण
पूर्ण

/*
 * complete callback क्रम urbs
 */
अटल व्योम snd_complete_urb(काष्ठा urb *urb)
अणु
	काष्ठा snd_urb_ctx *ctx = urb->context;
	काष्ठा snd_usb_endpoपूर्णांक *ep = ctx->ep;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (unlikely(urb->status == -ENOENT ||		/* unlinked */
		     urb->status == -ENODEV ||		/* device हटाओd */
		     urb->status == -ECONNRESET ||	/* unlinked */
		     urb->status == -ESHUTDOWN))	/* device disabled */
		जाओ निकास_clear;
	/* device disconnected */
	अगर (unlikely(atomic_पढ़ो(&ep->chip->shutकरोwn)))
		जाओ निकास_clear;

	अगर (unlikely(!ep_state_running(ep)))
		जाओ निकास_clear;

	अगर (usb_pipeout(ep->pipe)) अणु
		retire_outbound_urb(ep, ctx);
		/* can be stopped during retire callback */
		अगर (unlikely(!ep_state_running(ep)))
			जाओ निकास_clear;

		अगर (snd_usb_endpoपूर्णांक_implicit_feedback_sink(ep)) अणु
			spin_lock_irqsave(&ep->lock, flags);
			list_add_tail(&ctx->पढ़ोy_list, &ep->पढ़ोy_playback_urbs);
			clear_bit(ctx->index, &ep->active_mask);
			spin_unlock_irqrestore(&ep->lock, flags);
			queue_pending_output_urbs(ep);
			वापस;
		पूर्ण

		prepare_outbound_urb(ep, ctx);
		/* can be stopped during prepare callback */
		अगर (unlikely(!ep_state_running(ep)))
			जाओ निकास_clear;
	पूर्ण अन्यथा अणु
		retire_inbound_urb(ep, ctx);
		/* can be stopped during retire callback */
		अगर (unlikely(!ep_state_running(ep)))
			जाओ निकास_clear;

		prepare_inbound_urb(ep, ctx);
	पूर्ण

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err == 0)
		वापस;

	usb_audio_err(ep->chip, "cannot submit urb (err = %d)\n", err);
	notअगरy_xrun(ep);

निकास_clear:
	clear_bit(ctx->index, &ep->active_mask);
पूर्ण

/*
 * Find or create a refcount object क्रम the given पूर्णांकerface
 *
 * The objects are released altogether in snd_usb_endpoपूर्णांक_मुक्त_all()
 */
अटल काष्ठा snd_usb_अगरace_ref *
अगरace_ref_find(काष्ठा snd_usb_audio *chip, पूर्णांक अगरace)
अणु
	काष्ठा snd_usb_अगरace_ref *ip;

	list_क्रम_each_entry(ip, &chip->अगरace_ref_list, list)
		अगर (ip->अगरace == अगरace)
			वापस ip;

	ip = kzalloc(माप(*ip), GFP_KERNEL);
	अगर (!ip)
		वापस शून्य;
	ip->अगरace = अगरace;
	list_add_tail(&ip->list, &chip->अगरace_ref_list);
	वापस ip;
पूर्ण

/*
 * Get the existing endpoपूर्णांक object corresponding EP
 * Returns शून्य अगर not present.
 */
काष्ठा snd_usb_endpoपूर्णांक *
snd_usb_get_endpoपूर्णांक(काष्ठा snd_usb_audio *chip, पूर्णांक ep_num)
अणु
	काष्ठा snd_usb_endpoपूर्णांक *ep;

	list_क्रम_each_entry(ep, &chip->ep_list, list) अणु
		अगर (ep->ep_num == ep_num)
			वापस ep;
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा ep_type_name(type) \
	(type == SND_USB_ENDPOINT_TYPE_DATA ? "data" : "sync")

/**
 * snd_usb_add_endpoपूर्णांक: Add an endpoपूर्णांक to an USB audio chip
 *
 * @chip: The chip
 * @ep_num: The number of the endpoपूर्णांक to use
 * @type: SND_USB_ENDPOINT_TYPE_DATA or SND_USB_ENDPOINT_TYPE_SYNC
 *
 * If the requested endpoपूर्णांक has not been added to the given chip beक्रमe,
 * a new instance is created.
 *
 * Returns zero on success or a negative error code.
 *
 * New endpoपूर्णांकs will be added to chip->ep_list and मुक्तd by
 * calling snd_usb_endpoपूर्णांक_मुक्त_all().
 *
 * For SND_USB_ENDPOINT_TYPE_SYNC, the caller needs to guarantee that
 * bNumEndpoपूर्णांकs > 1 beक्रमehand.
 */
पूर्णांक snd_usb_add_endpoपूर्णांक(काष्ठा snd_usb_audio *chip, पूर्णांक ep_num, पूर्णांक type)
अणु
	काष्ठा snd_usb_endpoपूर्णांक *ep;
	bool is_playback;

	ep = snd_usb_get_endpoपूर्णांक(chip, ep_num);
	अगर (ep)
		वापस 0;

	usb_audio_dbg(chip, "Creating new %s endpoint #%x\n",
		      ep_type_name(type),
		      ep_num);
	ep = kzalloc(माप(*ep), GFP_KERNEL);
	अगर (!ep)
		वापस -ENOMEM;

	ep->chip = chip;
	spin_lock_init(&ep->lock);
	ep->type = type;
	ep->ep_num = ep_num;
	INIT_LIST_HEAD(&ep->पढ़ोy_playback_urbs);

	is_playback = ((ep_num & USB_ENDPOINT_सूची_MASK) == USB_सूची_OUT);
	ep_num &= USB_ENDPOINT_NUMBER_MASK;
	अगर (is_playback)
		ep->pipe = usb_sndisocpipe(chip->dev, ep_num);
	अन्यथा
		ep->pipe = usb_rcvisocpipe(chip->dev, ep_num);

	list_add_tail(&ep->list, &chip->ep_list);
	वापस 0;
पूर्ण

/* Set up syncपूर्णांकerval and maxsyncsize क्रम a sync EP */
अटल व्योम endpoपूर्णांक_set_syncपूर्णांकerval(काष्ठा snd_usb_audio *chip,
				      काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	काष्ठा usb_host_पूर्णांकerface *alts;
	काष्ठा usb_endpoपूर्णांक_descriptor *desc;

	alts = snd_usb_get_host_पूर्णांकerface(chip, ep->अगरace, ep->altsetting);
	अगर (!alts)
		वापस;

	desc = get_endpoपूर्णांक(alts, ep->ep_idx);
	अगर (desc->bLength >= USB_DT_ENDPOINT_AUDIO_SIZE &&
	    desc->bRefresh >= 1 && desc->bRefresh <= 9)
		ep->syncपूर्णांकerval = desc->bRefresh;
	अन्यथा अगर (snd_usb_get_speed(chip->dev) == USB_SPEED_FULL)
		ep->syncपूर्णांकerval = 1;
	अन्यथा अगर (desc->bInterval >= 1 && desc->bInterval <= 16)
		ep->syncपूर्णांकerval = desc->bInterval - 1;
	अन्यथा
		ep->syncपूर्णांकerval = 3;

	ep->syncmaxsize = le16_to_cpu(desc->wMaxPacketSize);
पूर्ण

अटल bool endpoपूर्णांक_compatible(काष्ठा snd_usb_endpoपूर्णांक *ep,
				स्थिर काष्ठा audioक्रमmat *fp,
				स्थिर काष्ठा snd_pcm_hw_params *params)
अणु
	अगर (!ep->खोलोed)
		वापस false;
	अगर (ep->cur_audiofmt != fp)
		वापस false;
	अगर (ep->cur_rate != params_rate(params) ||
	    ep->cur_क्रमmat != params_क्रमmat(params) ||
	    ep->cur_period_frames != params_period_size(params) ||
	    ep->cur_buffer_periods != params_periods(params))
		वापस false;
	वापस true;
पूर्ण

/*
 * Check whether the given fp and hw params are compatbile with the current
 * setup of the target EP क्रम implicit feedback sync
 */
bool snd_usb_endpoपूर्णांक_compatible(काष्ठा snd_usb_audio *chip,
				 काष्ठा snd_usb_endpoपूर्णांक *ep,
				 स्थिर काष्ठा audioक्रमmat *fp,
				 स्थिर काष्ठा snd_pcm_hw_params *params)
अणु
	bool ret;

	mutex_lock(&chip->mutex);
	ret = endpoपूर्णांक_compatible(ep, fp, params);
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

/*
 * snd_usb_endpoपूर्णांक_खोलो: Open the endpoपूर्णांक
 *
 * Called from hw_params to assign the endpoपूर्णांक to the substream.
 * It's reference-counted, and only the first खोलोer is allowed to set up
 * arbitrary parameters.  The later खोलोer must be compatible with the
 * क्रमmer खोलोed parameters.
 * The endpoपूर्णांक needs to be बंदd via snd_usb_endpoपूर्णांक_बंद() later.
 *
 * Note that this function करोesn't configure the endpoपूर्णांक.  The substream
 * needs to set it up later via snd_usb_endpoपूर्णांक_configure().
 */
काष्ठा snd_usb_endpoपूर्णांक *
snd_usb_endpoपूर्णांक_खोलो(काष्ठा snd_usb_audio *chip,
		      स्थिर काष्ठा audioक्रमmat *fp,
		      स्थिर काष्ठा snd_pcm_hw_params *params,
		      bool is_sync_ep)
अणु
	काष्ठा snd_usb_endpoपूर्णांक *ep;
	पूर्णांक ep_num = is_sync_ep ? fp->sync_ep : fp->endpoपूर्णांक;

	mutex_lock(&chip->mutex);
	ep = snd_usb_get_endpoपूर्णांक(chip, ep_num);
	अगर (!ep) अणु
		usb_audio_err(chip, "Cannot find EP 0x%x to open\n", ep_num);
		जाओ unlock;
	पूर्ण

	अगर (!ep->खोलोed) अणु
		अगर (is_sync_ep) अणु
			ep->अगरace = fp->sync_अगरace;
			ep->altsetting = fp->sync_altsetting;
			ep->ep_idx = fp->sync_ep_idx;
		पूर्ण अन्यथा अणु
			ep->अगरace = fp->अगरace;
			ep->altsetting = fp->altsetting;
			ep->ep_idx = fp->ep_idx;
		पूर्ण
		usb_audio_dbg(chip, "Open EP 0x%x, iface=%d:%d, idx=%d\n",
			      ep_num, ep->अगरace, ep->altsetting, ep->ep_idx);

		ep->अगरace_ref = अगरace_ref_find(chip, ep->अगरace);
		अगर (!ep->अगरace_ref) अणु
			ep = शून्य;
			जाओ unlock;
		पूर्ण

		ep->cur_audiofmt = fp;
		ep->cur_channels = fp->channels;
		ep->cur_rate = params_rate(params);
		ep->cur_क्रमmat = params_क्रमmat(params);
		ep->cur_frame_bytes = snd_pcm_क्रमmat_physical_width(ep->cur_क्रमmat) *
			ep->cur_channels / 8;
		ep->cur_period_frames = params_period_size(params);
		ep->cur_period_bytes = ep->cur_period_frames * ep->cur_frame_bytes;
		ep->cur_buffer_periods = params_periods(params);

		अगर (ep->type == SND_USB_ENDPOINT_TYPE_SYNC)
			endpoपूर्णांक_set_syncपूर्णांकerval(chip, ep);

		ep->implicit_fb_sync = fp->implicit_fb;
		ep->need_setup = true;

		usb_audio_dbg(chip, "  channels=%d, rate=%d, format=%s, period_bytes=%d, periods=%d, implicit_fb=%d\n",
			      ep->cur_channels, ep->cur_rate,
			      snd_pcm_क्रमmat_name(ep->cur_क्रमmat),
			      ep->cur_period_bytes, ep->cur_buffer_periods,
			      ep->implicit_fb_sync);

	पूर्ण अन्यथा अणु
		अगर (WARN_ON(!ep->अगरace_ref)) अणु
			ep = शून्य;
			जाओ unlock;
		पूर्ण

		अगर (!endpoपूर्णांक_compatible(ep, fp, params)) अणु
			usb_audio_err(chip, "Incompatible EP setup for 0x%x\n",
				      ep_num);
			ep = शून्य;
			जाओ unlock;
		पूर्ण

		usb_audio_dbg(chip, "Reopened EP 0x%x (count %d)\n",
			      ep_num, ep->खोलोed);
	पूर्ण

	अगर (!ep->अगरace_ref->खोलोed++)
		ep->अगरace_ref->need_setup = true;

	ep->खोलोed++;

 unlock:
	mutex_unlock(&chip->mutex);
	वापस ep;
पूर्ण

/*
 * snd_usb_endpoपूर्णांक_set_sync: Link data and sync endpoपूर्णांकs
 *
 * Pass शून्य to sync_ep to unlink again
 */
व्योम snd_usb_endpoपूर्णांक_set_sync(काष्ठा snd_usb_audio *chip,
			       काष्ठा snd_usb_endpoपूर्णांक *data_ep,
			       काष्ठा snd_usb_endpoपूर्णांक *sync_ep)
अणु
	data_ep->sync_source = sync_ep;
पूर्ण

/*
 * Set data endpoपूर्णांक callbacks and the asचिन्हित data stream
 *
 * Called at PCM trigger and cleanups.
 * Pass शून्य to deactivate each callback.
 */
व्योम snd_usb_endpoपूर्णांक_set_callback(काष्ठा snd_usb_endpoपूर्णांक *ep,
				   व्योम (*prepare)(काष्ठा snd_usb_substream *subs,
						   काष्ठा urb *urb),
				   व्योम (*retire)(काष्ठा snd_usb_substream *subs,
						  काष्ठा urb *urb),
				   काष्ठा snd_usb_substream *data_subs)
अणु
	ep->prepare_data_urb = prepare;
	ep->retire_data_urb = retire;
	WRITE_ONCE(ep->data_subs, data_subs);
पूर्ण

अटल पूर्णांक endpoपूर्णांक_set_पूर्णांकerface(काष्ठा snd_usb_audio *chip,
				  काष्ठा snd_usb_endpoपूर्णांक *ep,
				  bool set)
अणु
	पूर्णांक altset = set ? ep->altsetting : 0;
	पूर्णांक err;

	usb_audio_dbg(chip, "Setting usb interface %d:%d for EP 0x%x\n",
		      ep->अगरace, altset, ep->ep_num);
	err = usb_set_पूर्णांकerface(chip->dev, ep->अगरace, altset);
	अगर (err < 0) अणु
		usb_audio_err(chip, "%d:%d: usb_set_interface failed (%d)\n",
			      ep->अगरace, altset, err);
		वापस err;
	पूर्ण

	snd_usb_set_पूर्णांकerface_quirk(chip);
	वापस 0;
पूर्ण

/*
 * snd_usb_endpoपूर्णांक_बंद: Close the endpoपूर्णांक
 *
 * Unreference the alपढ़ोy खोलोed endpoपूर्णांक via snd_usb_endpoपूर्णांक_खोलो().
 */
व्योम snd_usb_endpoपूर्णांक_बंद(काष्ठा snd_usb_audio *chip,
			    काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	mutex_lock(&chip->mutex);
	usb_audio_dbg(chip, "Closing EP 0x%x (count %d)\n",
		      ep->ep_num, ep->खोलोed);

	अगर (!--ep->अगरace_ref->खोलोed)
		endpoपूर्णांक_set_पूर्णांकerface(chip, ep, false);

	अगर (!--ep->खोलोed) अणु
		ep->अगरace = 0;
		ep->altsetting = 0;
		ep->cur_audiofmt = शून्य;
		ep->cur_rate = 0;
		ep->अगरace_ref = शून्य;
		usb_audio_dbg(chip, "EP 0x%x closed\n", ep->ep_num);
	पूर्ण
	mutex_unlock(&chip->mutex);
पूर्ण

/* Prepare क्रम suspening EP, called from the मुख्य suspend handler */
व्योम snd_usb_endpoपूर्णांक_suspend(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	ep->need_setup = true;
	अगर (ep->अगरace_ref)
		ep->अगरace_ref->need_setup = true;
पूर्ण

/*
 *  रुको until all urbs are processed.
 */
अटल पूर्णांक रुको_clear_urbs(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	अचिन्हित दीर्घ end_समय = jअगरfies + msecs_to_jअगरfies(1000);
	पूर्णांक alive;

	अगर (atomic_पढ़ो(&ep->state) != EP_STATE_STOPPING)
		वापस 0;

	करो अणु
		alive = biपंचांगap_weight(&ep->active_mask, ep->nurbs);
		अगर (!alive)
			अवरोध;

		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));

	अगर (alive)
		usb_audio_err(ep->chip,
			"timeout: still %d active urbs on EP #%x\n",
			alive, ep->ep_num);

	अगर (ep_state_update(ep, EP_STATE_STOPPING, EP_STATE_STOPPED)) अणु
		ep->sync_sink = शून्य;
		snd_usb_endpoपूर्णांक_set_callback(ep, शून्य, शून्य, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

/* sync the pending stop operation;
 * this function itself करोesn't trigger the stop operation
 */
व्योम snd_usb_endpoपूर्णांक_sync_pending_stop(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	अगर (ep)
		रुको_clear_urbs(ep);
पूर्ण

/*
 * Stop active urbs
 *
 * This function moves the EP to STOPPING state अगर it's being RUNNING.
 */
अटल पूर्णांक stop_urbs(काष्ठा snd_usb_endpoपूर्णांक *ep, bool क्रमce)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!क्रमce && atomic_पढ़ो(&ep->running))
		वापस -EBUSY;

	अगर (!ep_state_update(ep, EP_STATE_RUNNING, EP_STATE_STOPPING))
		वापस 0;

	INIT_LIST_HEAD(&ep->पढ़ोy_playback_urbs);
	ep->next_packet_head = 0;
	ep->next_packet_queued = 0;

	क्रम (i = 0; i < ep->nurbs; i++) अणु
		अगर (test_bit(i, &ep->active_mask)) अणु
			अगर (!test_and_set_bit(i, &ep->unlink_mask)) अणु
				काष्ठा urb *u = ep->urb[i].urb;
				usb_unlink_urb(u);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * release an endpoपूर्णांक's urbs
 */
अटल पूर्णांक release_urbs(काष्ठा snd_usb_endpoपूर्णांक *ep, bool क्रमce)
अणु
	पूर्णांक i, err;

	/* route incoming urbs to nirvana */
	snd_usb_endpoपूर्णांक_set_callback(ep, शून्य, शून्य, शून्य);

	/* stop and unlink urbs */
	err = stop_urbs(ep, क्रमce);
	अगर (err)
		वापस err;

	रुको_clear_urbs(ep);

	क्रम (i = 0; i < ep->nurbs; i++)
		release_urb_ctx(&ep->urb[i]);

	usb_मुक्त_coherent(ep->chip->dev, SYNC_URBS * 4,
			  ep->syncbuf, ep->sync_dma);

	ep->syncbuf = शून्य;
	ep->nurbs = 0;
	वापस 0;
पूर्ण

/*
 * configure a data endpoपूर्णांक
 */
अटल पूर्णांक data_ep_set_params(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	काष्ठा snd_usb_audio *chip = ep->chip;
	अचिन्हित पूर्णांक maxsize, minsize, packs_per_ms, max_packs_per_urb;
	अचिन्हित पूर्णांक max_packs_per_period, urbs_per_period, urb_packs;
	अचिन्हित पूर्णांक max_urbs, i;
	स्थिर काष्ठा audioक्रमmat *fmt = ep->cur_audiofmt;
	पूर्णांक frame_bits = ep->cur_frame_bytes * 8;
	पूर्णांक tx_length_quirk = (chip->tx_length_quirk &&
			       usb_pipeout(ep->pipe));

	usb_audio_dbg(chip, "Setting params for data EP 0x%x, pipe 0x%x\n",
		      ep->ep_num, ep->pipe);

	अगर (ep->cur_क्रमmat == SNDRV_PCM_FORMAT_DSD_U16_LE && fmt->dsd_करोp) अणु
		/*
		 * When operating in DSD DOP mode, the size of a sample frame
		 * in hardware dअगरfers from the actual physical क्रमmat width
		 * because we need to make room क्रम the DOP markers.
		 */
		frame_bits += ep->cur_channels << 3;
	पूर्ण

	ep->dataपूर्णांकerval = fmt->dataपूर्णांकerval;
	ep->stride = frame_bits >> 3;

	चयन (ep->cur_क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_U8:
		ep->silence_value = 0x80;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_DSD_U8:
	हाल SNDRV_PCM_FORMAT_DSD_U16_LE:
	हाल SNDRV_PCM_FORMAT_DSD_U32_LE:
	हाल SNDRV_PCM_FORMAT_DSD_U16_BE:
	हाल SNDRV_PCM_FORMAT_DSD_U32_BE:
		ep->silence_value = 0x69;
		अवरोध;
	शेष:
		ep->silence_value = 0;
	पूर्ण

	/* assume max. frequency is 50% higher than nominal */
	ep->freqmax = ep->freqn + (ep->freqn >> 1);
	/* Round up freqmax to nearest पूर्णांकeger in order to calculate maximum
	 * packet size, which must represent a whole number of frames.
	 * This is accomplished by adding 0x0.ffff beक्रमe converting the
	 * Q16.16 क्रमmat पूर्णांकo पूर्णांकeger.
	 * In order to accurately calculate the maximum packet size when
	 * the data पूर्णांकerval is more than 1 (i.e. ep->dataपूर्णांकerval > 0),
	 * multiply by the data पूर्णांकerval prior to rounding. For instance,
	 * a freqmax of 41 kHz will result in a max packet size of 6 (5.125)
	 * frames with a data पूर्णांकerval of 1, but 11 (10.25) frames with a
	 * data पूर्णांकerval of 2.
	 * (ep->freqmax << ep->dataपूर्णांकerval overflows at 8.192 MHz क्रम the
	 * maximum dataपूर्णांकerval value of 3, at USB full speed, higher क्रम
	 * USB high speed, noting that ep->freqmax is in units of
	 * frames per packet in Q16.16 क्रमmat.)
	 */
	maxsize = (((ep->freqmax << ep->dataपूर्णांकerval) + 0xffff) >> 16) *
			 (frame_bits >> 3);
	अगर (tx_length_quirk)
		maxsize += माप(__le32); /* Space क्रम length descriptor */
	/* but wMaxPacketSize might reduce this */
	अगर (ep->maxpacksize && ep->maxpacksize < maxsize) अणु
		/* whatever fits पूर्णांकo a max. size packet */
		अचिन्हित पूर्णांक data_maxsize = maxsize = ep->maxpacksize;

		अगर (tx_length_quirk)
			/* Need to हटाओ the length descriptor to calc freq */
			data_maxsize -= माप(__le32);
		ep->freqmax = (data_maxsize / (frame_bits >> 3))
				<< (16 - ep->dataपूर्णांकerval);
	पूर्ण

	अगर (ep->fill_max)
		ep->curpacksize = ep->maxpacksize;
	अन्यथा
		ep->curpacksize = maxsize;

	अगर (snd_usb_get_speed(chip->dev) != USB_SPEED_FULL) अणु
		packs_per_ms = 8 >> ep->dataपूर्णांकerval;
		max_packs_per_urb = MAX_PACKS_HS;
	पूर्ण अन्यथा अणु
		packs_per_ms = 1;
		max_packs_per_urb = MAX_PACKS;
	पूर्ण
	अगर (ep->sync_source && !ep->implicit_fb_sync)
		max_packs_per_urb = min(max_packs_per_urb,
					1U << ep->sync_source->syncपूर्णांकerval);
	max_packs_per_urb = max(1u, max_packs_per_urb >> ep->dataपूर्णांकerval);

	/*
	 * Capture endpoपूर्णांकs need to use small URBs because there's no way
	 * to tell in advance where the next period will end, and we करोn't
	 * want the next URB to complete much after the period ends.
	 *
	 * Playback endpoपूर्णांकs with implicit sync much use the same parameters
	 * as their corresponding capture endpoपूर्णांक.
	 */
	अगर (usb_pipein(ep->pipe) || ep->implicit_fb_sync) अणु

		urb_packs = packs_per_ms;
		/*
		 * Wireless devices can poll at a max rate of once per 4ms.
		 * For dataपूर्णांकervals less than 5, increase the packet count to
		 * allow the host controller to use bursting to fill in the
		 * gaps.
		 */
		अगर (snd_usb_get_speed(chip->dev) == USB_SPEED_WIRELESS) अणु
			पूर्णांक पूर्णांकerval = ep->dataपूर्णांकerval;
			जबतक (पूर्णांकerval < 5) अणु
				urb_packs <<= 1;
				++पूर्णांकerval;
			पूर्ण
		पूर्ण
		/* make capture URBs <= 1 ms and smaller than a period */
		urb_packs = min(max_packs_per_urb, urb_packs);
		जबतक (urb_packs > 1 && urb_packs * maxsize >= ep->cur_period_bytes)
			urb_packs >>= 1;
		ep->nurbs = MAX_URBS;

	/*
	 * Playback endpoपूर्णांकs without implicit sync are adjusted so that
	 * a period fits as evenly as possible in the smallest number of
	 * URBs.  The total number of URBs is adjusted to the size of the
	 * ALSA buffer, subject to the MAX_URBS and MAX_QUEUE limits.
	 */
	पूर्ण अन्यथा अणु
		/* determine how small a packet can be */
		minsize = (ep->freqn >> (16 - ep->dataपूर्णांकerval)) *
				(frame_bits >> 3);
		/* with sync from device, assume it can be 12% lower */
		अगर (ep->sync_source)
			minsize -= minsize >> 3;
		minsize = max(minsize, 1u);

		/* how many packets will contain an entire ALSA period? */
		max_packs_per_period = DIV_ROUND_UP(ep->cur_period_bytes, minsize);

		/* how many URBs will contain a period? */
		urbs_per_period = DIV_ROUND_UP(max_packs_per_period,
				max_packs_per_urb);
		/* how many packets are needed in each URB? */
		urb_packs = DIV_ROUND_UP(max_packs_per_period, urbs_per_period);

		/* limit the number of frames in a single URB */
		ep->max_urb_frames = DIV_ROUND_UP(ep->cur_period_frames,
						  urbs_per_period);

		/* try to use enough URBs to contain an entire ALSA buffer */
		max_urbs = min((अचिन्हित) MAX_URBS,
				MAX_QUEUE * packs_per_ms / urb_packs);
		ep->nurbs = min(max_urbs, urbs_per_period * ep->cur_buffer_periods);
	पूर्ण

	/* allocate and initialize data urbs */
	क्रम (i = 0; i < ep->nurbs; i++) अणु
		काष्ठा snd_urb_ctx *u = &ep->urb[i];
		u->index = i;
		u->ep = ep;
		u->packets = urb_packs;
		u->buffer_size = maxsize * u->packets;

		अगर (fmt->fmt_type == UAC_FORMAT_TYPE_II)
			u->packets++; /* क्रम transfer delimiter */
		u->urb = usb_alloc_urb(u->packets, GFP_KERNEL);
		अगर (!u->urb)
			जाओ out_of_memory;

		u->urb->transfer_buffer =
			usb_alloc_coherent(chip->dev, u->buffer_size,
					   GFP_KERNEL, &u->urb->transfer_dma);
		अगर (!u->urb->transfer_buffer)
			जाओ out_of_memory;
		u->urb->pipe = ep->pipe;
		u->urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		u->urb->पूर्णांकerval = 1 << ep->dataपूर्णांकerval;
		u->urb->context = u;
		u->urb->complete = snd_complete_urb;
		INIT_LIST_HEAD(&u->पढ़ोy_list);
	पूर्ण

	वापस 0;

out_of_memory:
	release_urbs(ep, false);
	वापस -ENOMEM;
पूर्ण

/*
 * configure a sync endpoपूर्णांक
 */
अटल पूर्णांक sync_ep_set_params(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	काष्ठा snd_usb_audio *chip = ep->chip;
	पूर्णांक i;

	usb_audio_dbg(chip, "Setting params for sync EP 0x%x, pipe 0x%x\n",
		      ep->ep_num, ep->pipe);

	ep->syncbuf = usb_alloc_coherent(chip->dev, SYNC_URBS * 4,
					 GFP_KERNEL, &ep->sync_dma);
	अगर (!ep->syncbuf)
		वापस -ENOMEM;

	क्रम (i = 0; i < SYNC_URBS; i++) अणु
		काष्ठा snd_urb_ctx *u = &ep->urb[i];
		u->index = i;
		u->ep = ep;
		u->packets = 1;
		u->urb = usb_alloc_urb(1, GFP_KERNEL);
		अगर (!u->urb)
			जाओ out_of_memory;
		u->urb->transfer_buffer = ep->syncbuf + i * 4;
		u->urb->transfer_dma = ep->sync_dma + i * 4;
		u->urb->transfer_buffer_length = 4;
		u->urb->pipe = ep->pipe;
		u->urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		u->urb->number_of_packets = 1;
		u->urb->पूर्णांकerval = 1 << ep->syncपूर्णांकerval;
		u->urb->context = u;
		u->urb->complete = snd_complete_urb;
	पूर्ण

	ep->nurbs = SYNC_URBS;

	वापस 0;

out_of_memory:
	release_urbs(ep, false);
	वापस -ENOMEM;
पूर्ण

/*
 * snd_usb_endpoपूर्णांक_set_params: configure an snd_usb_endpoपूर्णांक
 *
 * Determine the number of URBs to be used on this endpoपूर्णांक.
 * An endpoपूर्णांक must be configured beक्रमe it can be started.
 * An endpoपूर्णांक that is alपढ़ोy running can not be reconfigured.
 */
अटल पूर्णांक snd_usb_endpoपूर्णांक_set_params(काष्ठा snd_usb_audio *chip,
				       काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	स्थिर काष्ठा audioक्रमmat *fmt = ep->cur_audiofmt;
	पूर्णांक err;

	/* release old buffers, अगर any */
	err = release_urbs(ep, false);
	अगर (err < 0)
		वापस err;

	ep->dataपूर्णांकerval = fmt->dataपूर्णांकerval;
	ep->maxpacksize = fmt->maxpacksize;
	ep->fill_max = !!(fmt->attributes & UAC_EP_CS_ATTR_FILL_MAX);

	अगर (snd_usb_get_speed(chip->dev) == USB_SPEED_FULL) अणु
		ep->freqn = get_usb_full_speed_rate(ep->cur_rate);
		ep->pps = 1000 >> ep->dataपूर्णांकerval;
	पूर्ण अन्यथा अणु
		ep->freqn = get_usb_high_speed_rate(ep->cur_rate);
		ep->pps = 8000 >> ep->dataपूर्णांकerval;
	पूर्ण

	ep->sample_rem = ep->cur_rate % ep->pps;
	ep->packsize[0] = ep->cur_rate / ep->pps;
	ep->packsize[1] = (ep->cur_rate + (ep->pps - 1)) / ep->pps;

	/* calculate the frequency in 16.16 क्रमmat */
	ep->freqm = ep->freqn;
	ep->freqshअगरt = पूर्णांक_न्यून;

	ep->phase = 0;

	चयन (ep->type) अणु
	हाल  SND_USB_ENDPOINT_TYPE_DATA:
		err = data_ep_set_params(ep);
		अवरोध;
	हाल  SND_USB_ENDPOINT_TYPE_SYNC:
		err = sync_ep_set_params(ep);
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	usb_audio_dbg(chip, "Set up %d URBS, ret=%d\n", ep->nurbs, err);

	अगर (err < 0)
		वापस err;

	/* some unit conversions in runसमय */
	ep->maxframesize = ep->maxpacksize / ep->cur_frame_bytes;
	ep->curframesize = ep->curpacksize / ep->cur_frame_bytes;

	वापस 0;
पूर्ण

/*
 * snd_usb_endpoपूर्णांक_configure: Configure the endpoपूर्णांक
 *
 * This function sets up the EP to be fully usable state.
 * It's called either from hw_params or prepare callback.
 * The function checks need_setup flag, and perfoms nothing unless needed,
 * so it's safe to call this multiple बार.
 *
 * This वापसs zero अगर unchanged, 1 अगर the configuration has changed,
 * or a negative error code.
 */
पूर्णांक snd_usb_endpoपूर्णांक_configure(काष्ठा snd_usb_audio *chip,
			       काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	bool अगरace_first;
	पूर्णांक err = 0;

	mutex_lock(&chip->mutex);
	अगर (WARN_ON(!ep->अगरace_ref))
		जाओ unlock;
	अगर (!ep->need_setup)
		जाओ unlock;

	/* If the पूर्णांकerface has been alपढ़ोy set up, just set EP parameters */
	अगर (!ep->अगरace_ref->need_setup) अणु
		/* sample rate setup of UAC1 is per endpoपूर्णांक, and we need
		 * to update at each EP configuration
		 */
		अगर (ep->cur_audiofmt->protocol == UAC_VERSION_1) अणु
			err = snd_usb_init_sample_rate(chip, ep->cur_audiofmt,
						       ep->cur_rate);
			अगर (err < 0)
				जाओ unlock;
		पूर्ण
		err = snd_usb_endpoपूर्णांक_set_params(chip, ep);
		अगर (err < 0)
			जाओ unlock;
		जाओ करोne;
	पूर्ण

	/* Need to deselect altsetting at first */
	endpoपूर्णांक_set_पूर्णांकerface(chip, ep, false);

	/* Some UAC1 devices (e.g. Yamaha THR10) need the host पूर्णांकerface
	 * to be set up beक्रमe parameter setups
	 */
	अगरace_first = ep->cur_audiofmt->protocol == UAC_VERSION_1;
	अगर (अगरace_first) अणु
		err = endpoपूर्णांक_set_पूर्णांकerface(chip, ep, true);
		अगर (err < 0)
			जाओ unlock;
	पूर्ण

	err = snd_usb_init_pitch(chip, ep->cur_audiofmt);
	अगर (err < 0)
		जाओ unlock;

	err = snd_usb_init_sample_rate(chip, ep->cur_audiofmt, ep->cur_rate);
	अगर (err < 0)
		जाओ unlock;

	err = snd_usb_endpoपूर्णांक_set_params(chip, ep);
	अगर (err < 0)
		जाओ unlock;

	err = snd_usb_select_mode_quirk(chip, ep->cur_audiofmt);
	अगर (err < 0)
		जाओ unlock;

	/* क्रम UAC2/3, enable the पूर्णांकerface altset here at last */
	अगर (!अगरace_first) अणु
		err = endpoपूर्णांक_set_पूर्णांकerface(chip, ep, true);
		अगर (err < 0)
			जाओ unlock;
	पूर्ण

	ep->अगरace_ref->need_setup = false;

 करोne:
	ep->need_setup = false;
	err = 1;

unlock:
	mutex_unlock(&chip->mutex);
	वापस err;
पूर्ण

/**
 * snd_usb_endpoपूर्णांक_start: start an snd_usb_endpoपूर्णांक
 *
 * @ep: the endpoपूर्णांक to start
 *
 * A call to this function will increment the running count of the endpoपूर्णांक.
 * In हाल it is not alपढ़ोy running, the URBs क्रम this endpoपूर्णांक will be
 * submitted. Otherwise, this function करोes nothing.
 *
 * Must be balanced to calls of snd_usb_endpoपूर्णांक_stop().
 *
 * Returns an error अगर the URB submission failed, 0 in all other हालs.
 */
पूर्णांक snd_usb_endpoपूर्णांक_start(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i;

	अगर (atomic_पढ़ो(&ep->chip->shutकरोwn))
		वापस -EBADFD;

	अगर (ep->sync_source)
		WRITE_ONCE(ep->sync_source->sync_sink, ep);

	usb_audio_dbg(ep->chip, "Starting %s EP 0x%x (running %d)\n",
		      ep_type_name(ep->type), ep->ep_num,
		      atomic_पढ़ो(&ep->running));

	/* alपढ़ोy running? */
	अगर (atomic_inc_वापस(&ep->running) != 1)
		वापस 0;

	ep->active_mask = 0;
	ep->unlink_mask = 0;
	ep->phase = 0;
	ep->sample_accum = 0;

	snd_usb_endpoपूर्णांक_start_quirk(ep);

	/*
	 * If this endpoपूर्णांक has a data endpoपूर्णांक as implicit feedback source,
	 * करोn't start the urbs here. Instead, mark them all as available,
	 * रुको क्रम the record urbs to वापस and queue the playback urbs
	 * from that context.
	 */

	अगर (!ep_state_update(ep, EP_STATE_STOPPED, EP_STATE_RUNNING))
		जाओ __error;

	अगर (snd_usb_endpoपूर्णांक_implicit_feedback_sink(ep) &&
	    !ep->chip->playback_first) अणु
		क्रम (i = 0; i < ep->nurbs; i++) अणु
			काष्ठा snd_urb_ctx *ctx = ep->urb + i;
			list_add_tail(&ctx->पढ़ोy_list, &ep->पढ़ोy_playback_urbs);
		पूर्ण

		usb_audio_dbg(ep->chip, "No URB submission due to implicit fb sync\n");
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ep->nurbs; i++) अणु
		काष्ठा urb *urb = ep->urb[i].urb;

		अगर (snd_BUG_ON(!urb))
			जाओ __error;

		अगर (usb_pipeout(ep->pipe)) अणु
			prepare_outbound_urb(ep, urb->context);
		पूर्ण अन्यथा अणु
			prepare_inbound_urb(ep, urb->context);
		पूर्ण

		err = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (err < 0) अणु
			usb_audio_err(ep->chip,
				"cannot submit urb %d, error %d: %s\n",
				i, err, usb_error_string(err));
			जाओ __error;
		पूर्ण
		set_bit(i, &ep->active_mask);
	पूर्ण

	usb_audio_dbg(ep->chip, "%d URBs submitted for EP 0x%x\n",
		      ep->nurbs, ep->ep_num);
	वापस 0;

__error:
	snd_usb_endpoपूर्णांक_stop(ep);
	वापस -EPIPE;
पूर्ण

/**
 * snd_usb_endpoपूर्णांक_stop: stop an snd_usb_endpoपूर्णांक
 *
 * @ep: the endpoपूर्णांक to stop (may be शून्य)
 *
 * A call to this function will decrement the running count of the endpoपूर्णांक.
 * In हाल the last user has requested the endpoपूर्णांक stop, the URBs will
 * actually be deactivated.
 *
 * Must be balanced to calls of snd_usb_endpoपूर्णांक_start().
 *
 * The caller needs to synchronize the pending stop operation via
 * snd_usb_endpoपूर्णांक_sync_pending_stop().
 */
व्योम snd_usb_endpoपूर्णांक_stop(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	अगर (!ep)
		वापस;

	usb_audio_dbg(ep->chip, "Stopping %s EP 0x%x (running %d)\n",
		      ep_type_name(ep->type), ep->ep_num,
		      atomic_पढ़ो(&ep->running));

	अगर (snd_BUG_ON(!atomic_पढ़ो(&ep->running)))
		वापस;

	अगर (!atomic_dec_वापस(&ep->running)) अणु
		अगर (ep->sync_source)
			WRITE_ONCE(ep->sync_source->sync_sink, शून्य);
		stop_urbs(ep, false);
	पूर्ण
पूर्ण

/**
 * snd_usb_endpoपूर्णांक_release: Tear करोwn an snd_usb_endpoपूर्णांक
 *
 * @ep: the endpoपूर्णांक to release
 *
 * This function करोes not care क्रम the endpoपूर्णांक's running count but will tear
 * करोwn all the streaming URBs immediately.
 */
व्योम snd_usb_endpoपूर्णांक_release(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	release_urbs(ep, true);
पूर्ण

/**
 * snd_usb_endpoपूर्णांक_मुक्त_all: Free the resources of an snd_usb_endpoपूर्णांक
 * @chip: The chip
 *
 * This मुक्त all endpoपूर्णांकs and those resources
 */
व्योम snd_usb_endpoपूर्णांक_मुक्त_all(काष्ठा snd_usb_audio *chip)
अणु
	काष्ठा snd_usb_endpoपूर्णांक *ep, *en;
	काष्ठा snd_usb_अगरace_ref *ip, *in;

	list_क्रम_each_entry_safe(ep, en, &chip->ep_list, list)
		kमुक्त(ep);

	list_क्रम_each_entry_safe(ip, in, &chip->अगरace_ref_list, list)
		kमुक्त(ip);
पूर्ण

/*
 * snd_usb_handle_sync_urb: parse an USB sync packet
 *
 * @ep: the endpoपूर्णांक to handle the packet
 * @sender: the sending endpoपूर्णांक
 * @urb: the received packet
 *
 * This function is called from the context of an endpoपूर्णांक that received
 * the packet and is used to let another endpoपूर्णांक object handle the payload.
 */
अटल व्योम snd_usb_handle_sync_urb(काष्ठा snd_usb_endpoपूर्णांक *ep,
				    काष्ठा snd_usb_endpoपूर्णांक *sender,
				    स्थिर काष्ठा urb *urb)
अणु
	पूर्णांक shअगरt;
	अचिन्हित पूर्णांक f;
	अचिन्हित दीर्घ flags;

	snd_BUG_ON(ep == sender);

	/*
	 * In हाल the endpoपूर्णांक is operating in implicit feedback mode, prepare
	 * a new outbound URB that has the same layout as the received packet
	 * and add it to the list of pending urbs. queue_pending_output_urbs()
	 * will take care of them later.
	 */
	अगर (snd_usb_endpoपूर्णांक_implicit_feedback_sink(ep) &&
	    atomic_पढ़ो(&ep->running)) अणु

		/* implicit feedback हाल */
		पूर्णांक i, bytes = 0;
		काष्ठा snd_urb_ctx *in_ctx;
		काष्ठा snd_usb_packet_info *out_packet;

		in_ctx = urb->context;

		/* Count overall packet size */
		क्रम (i = 0; i < in_ctx->packets; i++)
			अगर (urb->iso_frame_desc[i].status == 0)
				bytes += urb->iso_frame_desc[i].actual_length;

		/*
		 * skip empty packets. At least M-Audio's Fast Track Ultra stops
		 * streaming once it received a 0-byte OUT URB
		 */
		अगर (bytes == 0)
			वापस;

		spin_lock_irqsave(&ep->lock, flags);
		अगर (ep->next_packet_queued >= ARRAY_SIZE(ep->next_packet)) अणु
			spin_unlock_irqrestore(&ep->lock, flags);
			usb_audio_err(ep->chip,
				      "next package FIFO overflow EP 0x%x\n",
				      ep->ep_num);
			notअगरy_xrun(ep);
			वापस;
		पूर्ण

		out_packet = next_packet_fअगरo_enqueue(ep);

		/*
		 * Iterate through the inbound packet and prepare the lengths
		 * क्रम the output packet. The OUT packet we are about to send
		 * will have the same amount of payload bytes per stride as the
		 * IN packet we just received. Since the actual size is scaled
		 * by the stride, use the sender stride to calculate the length
		 * in हाल the number of channels dअगरfer between the implicitly
		 * fed-back endpoपूर्णांक and the synchronizing endpoपूर्णांक.
		 */

		out_packet->packets = in_ctx->packets;
		क्रम (i = 0; i < in_ctx->packets; i++) अणु
			अगर (urb->iso_frame_desc[i].status == 0)
				out_packet->packet_size[i] =
					urb->iso_frame_desc[i].actual_length / sender->stride;
			अन्यथा
				out_packet->packet_size[i] = 0;
		पूर्ण

		spin_unlock_irqrestore(&ep->lock, flags);
		queue_pending_output_urbs(ep);

		वापस;
	पूर्ण

	/*
	 * process after playback sync complete
	 *
	 * Full speed devices report feedback values in 10.14 क्रमmat as samples
	 * per frame, high speed devices in 16.16 क्रमmat as samples per
	 * microframe.
	 *
	 * Because the Audio Class 1 spec was written beक्रमe USB 2.0, many high
	 * speed devices use a wrong पूर्णांकerpretation, some others use an
	 * entirely dअगरferent क्रमmat.
	 *
	 * Thereक्रमe, we cannot predict what क्रमmat any particular device uses
	 * and must detect it स्वतःmatically.
	 */

	अगर (urb->iso_frame_desc[0].status != 0 ||
	    urb->iso_frame_desc[0].actual_length < 3)
		वापस;

	f = le32_to_cpup(urb->transfer_buffer);
	अगर (urb->iso_frame_desc[0].actual_length == 3)
		f &= 0x00ffffff;
	अन्यथा
		f &= 0x0fffffff;

	अगर (f == 0)
		वापस;

	अगर (unlikely(sender->tenor_fb_quirk)) अणु
		/*
		 * Devices based on Tenor 8802 chipsets (TEAC UD-H01
		 * and others) someबार change the feedback value
		 * by +/- 0x1.0000.
		 */
		अगर (f < ep->freqn - 0x8000)
			f += 0xf000;
		अन्यथा अगर (f > ep->freqn + 0x8000)
			f -= 0xf000;
	पूर्ण अन्यथा अगर (unlikely(ep->freqshअगरt == पूर्णांक_न्यून)) अणु
		/*
		 * The first समय we see a feedback value, determine its क्रमmat
		 * by shअगरting it left or right until it matches the nominal
		 * frequency value.  This assumes that the feedback करोes not
		 * dअगरfer from the nominal value more than +50% or -25%.
		 */
		shअगरt = 0;
		जबतक (f < ep->freqn - ep->freqn / 4) अणु
			f <<= 1;
			shअगरt++;
		पूर्ण
		जबतक (f > ep->freqn + ep->freqn / 2) अणु
			f >>= 1;
			shअगरt--;
		पूर्ण
		ep->freqshअगरt = shअगरt;
	पूर्ण अन्यथा अगर (ep->freqshअगरt >= 0)
		f <<= ep->freqshअगरt;
	अन्यथा
		f >>= -ep->freqshअगरt;

	अगर (likely(f >= ep->freqn - ep->freqn / 8 && f <= ep->freqmax)) अणु
		/*
		 * If the frequency looks valid, set it.
		 * This value is referred to in prepare_playback_urb().
		 */
		spin_lock_irqsave(&ep->lock, flags);
		ep->freqm = f;
		spin_unlock_irqrestore(&ep->lock, flags);
	पूर्ण अन्यथा अणु
		/*
		 * Out of range; maybe the shअगरt value is wrong.
		 * Reset it so that we स्वतःdetect again the next समय.
		 */
		ep->freqshअगरt = पूर्णांक_न्यून;
	पूर्ण
पूर्ण

