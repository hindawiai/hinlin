<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007, 2008 Karsten Wiese <fzu@wemgehoertderstaat.de>
 */

#समावेश <linux/usb.h>
#समावेश <linux/gfp.h>

#समावेश "usb_stream.h"


/*                             setup                                  */

अटल अचिन्हित usb_stream_next_packet_size(काष्ठा usb_stream_kernel *sk)
अणु
	काष्ठा usb_stream *s = sk->s;
	sk->out_phase_peeked = (sk->out_phase & 0xffff) + sk->freqn;
	वापस (sk->out_phase_peeked >> 16) * s->cfg.frame_size;
पूर्ण

अटल व्योम playback_prep_freqn(काष्ठा usb_stream_kernel *sk, काष्ठा urb *urb)
अणु
	काष्ठा usb_stream *s = sk->s;
	पूर्णांक pack, lb = 0;

	क्रम (pack = 0; pack < sk->n_o_ps; pack++) अणु
		पूर्णांक l = usb_stream_next_packet_size(sk);
		अगर (s->idle_outsize + lb + l > s->period_size)
			जाओ check;

		sk->out_phase = sk->out_phase_peeked;
		urb->iso_frame_desc[pack].offset = lb;
		urb->iso_frame_desc[pack].length = l;
		lb += l;
	पूर्ण
	snd_prपूर्णांकdd(KERN_DEBUG "%i\n", lb);

check:
	urb->number_of_packets = pack;
	urb->transfer_buffer_length = lb;
	s->idle_outsize += lb - s->period_size;
	snd_prपूर्णांकdd(KERN_DEBUG "idle=%i ul=%i ps=%i\n", s->idle_outsize,
		    lb, s->period_size);
पूर्ण

अटल पूर्णांक init_pipe_urbs(काष्ठा usb_stream_kernel *sk, अचिन्हित use_packsize,
			   काष्ठा urb **urbs, अक्षर *transfer,
			   काष्ठा usb_device *dev, पूर्णांक pipe)
अणु
	पूर्णांक u, p;
	पूर्णांक maxpacket = use_packsize ?
		use_packsize : usb_maxpacket(dev, pipe, usb_pipeout(pipe));
	पूर्णांक transfer_length = maxpacket * sk->n_o_ps;

	क्रम (u = 0; u < USB_STREAM_NURBS;
	     ++u, transfer += transfer_length) अणु
		काष्ठा urb *urb = urbs[u];
		काष्ठा usb_iso_packet_descriptor *desc;
		urb->transfer_buffer = transfer;
		urb->dev = dev;
		urb->pipe = pipe;
		urb->number_of_packets = sk->n_o_ps;
		urb->context = sk;
		urb->पूर्णांकerval = 1;
		अगर (usb_pipeout(pipe))
			जारी;
		अगर (usb_urb_ep_type_check(urb))
			वापस -EINVAL;

		urb->transfer_buffer_length = transfer_length;
		desc = urb->iso_frame_desc;
		desc->offset = 0;
		desc->length = maxpacket;
		क्रम (p = 1; p < sk->n_o_ps; ++p) अणु
			desc[p].offset = desc[p - 1].offset + maxpacket;
			desc[p].length = maxpacket;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_urbs(काष्ठा usb_stream_kernel *sk, अचिन्हित use_packsize,
		      काष्ठा usb_device *dev, पूर्णांक in_pipe, पूर्णांक out_pipe)
अणु
	काष्ठा usb_stream	*s = sk->s;
	अक्षर			*indata = (अक्षर *)s + माप(*s) +
					माप(काष्ठा usb_stream_packet) *
					s->inpackets;
	पूर्णांक			u;

	क्रम (u = 0; u < USB_STREAM_NURBS; ++u) अणु
		sk->inurb[u] = usb_alloc_urb(sk->n_o_ps, GFP_KERNEL);
		अगर (!sk->inurb[u])
			वापस -ENOMEM;

		sk->outurb[u] = usb_alloc_urb(sk->n_o_ps, GFP_KERNEL);
		अगर (!sk->outurb[u])
			वापस -ENOMEM;
	पूर्ण

	अगर (init_pipe_urbs(sk, use_packsize, sk->inurb, indata, dev, in_pipe) ||
	    init_pipe_urbs(sk, use_packsize, sk->outurb, sk->ग_लिखो_page, dev,
			   out_pipe))
		वापस -EINVAL;

	वापस 0;
पूर्ण


/*
 * convert a sampling rate पूर्णांकo our full speed क्रमmat (fs/1000 in Q16.16)
 * this will overflow at approx 524 kHz
 */
अटल अंतरभूत अचिन्हित get_usb_full_speed_rate(अचिन्हित rate)
अणु
	वापस ((rate << 13) + 62) / 125;
पूर्ण

/*
 * convert a sampling rate पूर्णांकo USB high speed क्रमmat (fs/8000 in Q16.16)
 * this will overflow at approx 4 MHz
 */
अटल अंतरभूत अचिन्हित get_usb_high_speed_rate(अचिन्हित rate)
अणु
	वापस ((rate << 10) + 62) / 125;
पूर्ण

व्योम usb_stream_मुक्त(काष्ठा usb_stream_kernel *sk)
अणु
	काष्ठा usb_stream *s;
	अचिन्हित u;

	क्रम (u = 0; u < USB_STREAM_NURBS; ++u) अणु
		usb_मुक्त_urb(sk->inurb[u]);
		sk->inurb[u] = शून्य;
		usb_मुक्त_urb(sk->outurb[u]);
		sk->outurb[u] = शून्य;
	पूर्ण

	s = sk->s;
	अगर (!s)
		वापस;

	मुक्त_pages_exact(sk->ग_लिखो_page, s->ग_लिखो_size);
	sk->ग_लिखो_page = शून्य;
	मुक्त_pages_exact(s, s->पढ़ो_size);
	sk->s = शून्य;
पूर्ण

काष्ठा usb_stream *usb_stream_new(काष्ठा usb_stream_kernel *sk,
				  काष्ठा usb_device *dev,
				  अचिन्हित in_endpoपूर्णांक, अचिन्हित out_endpoपूर्णांक,
				  अचिन्हित sample_rate, अचिन्हित use_packsize,
				  अचिन्हित period_frames, अचिन्हित frame_size)
अणु
	पूर्णांक packets, max_packsize;
	पूर्णांक in_pipe, out_pipe;
	पूर्णांक पढ़ो_size = माप(काष्ठा usb_stream);
	पूर्णांक ग_लिखो_size;
	पूर्णांक usb_frames = dev->speed == USB_SPEED_HIGH ? 8000 : 1000;

	in_pipe = usb_rcvisocpipe(dev, in_endpoपूर्णांक);
	out_pipe = usb_sndisocpipe(dev, out_endpoपूर्णांक);

	max_packsize = use_packsize ?
		use_packsize : usb_maxpacket(dev, in_pipe, 0);

	/*
		t_period = period_frames / sample_rate
		iso_packs = t_period / t_iso_frame
			= (period_frames / sample_rate) * (1 / t_iso_frame)
	*/

	packets = period_frames * usb_frames / sample_rate + 1;

	अगर (dev->speed == USB_SPEED_HIGH)
		packets = (packets + 7) & ~7;

	पढ़ो_size += packets * USB_STREAM_URBDEPTH *
		(max_packsize + माप(काष्ठा usb_stream_packet));

	max_packsize = usb_maxpacket(dev, out_pipe, 1);
	ग_लिखो_size = max_packsize * packets * USB_STREAM_URBDEPTH;

	अगर (पढ़ो_size >= 256*PAGE_SIZE || ग_लिखो_size >= 256*PAGE_SIZE) अणु
		snd_prपूर्णांकk(KERN_WARNING "a size exceeds 128*PAGE_SIZE\n");
		जाओ out;
	पूर्ण

	sk->s = alloc_pages_exact(पढ़ो_size,
				  GFP_KERNEL | __GFP_ZERO | __GFP_NOWARN);
	अगर (!sk->s) अणु
		pr_warn("us122l: couldn't allocate read buffer\n");
		जाओ out;
	पूर्ण
	sk->s->cfg.version = USB_STREAM_INTERFACE_VERSION;

	sk->s->पढ़ो_size = पढ़ो_size;

	sk->s->cfg.sample_rate = sample_rate;
	sk->s->cfg.frame_size = frame_size;
	sk->n_o_ps = packets;
	sk->s->inpackets = packets * USB_STREAM_URBDEPTH;
	sk->s->cfg.period_frames = period_frames;
	sk->s->period_size = frame_size * period_frames;

	sk->s->ग_लिखो_size = ग_लिखो_size;

	sk->ग_लिखो_page = alloc_pages_exact(ग_लिखो_size,
					   GFP_KERNEL | __GFP_ZERO | __GFP_NOWARN);
	अगर (!sk->ग_लिखो_page) अणु
		pr_warn("us122l: couldn't allocate write buffer\n");
		usb_stream_मुक्त(sk);
		वापस शून्य;
	पूर्ण

	/* calculate the frequency in 16.16 क्रमmat */
	अगर (dev->speed == USB_SPEED_FULL)
		sk->freqn = get_usb_full_speed_rate(sample_rate);
	अन्यथा
		sk->freqn = get_usb_high_speed_rate(sample_rate);

	अगर (init_urbs(sk, use_packsize, dev, in_pipe, out_pipe) < 0) अणु
		usb_stream_मुक्त(sk);
		वापस शून्य;
	पूर्ण

	sk->s->state = usb_stream_stopped;
out:
	वापस sk->s;
पूर्ण


/*                             start                                  */

अटल bool balance_check(काष्ठा usb_stream_kernel *sk, काष्ठा urb *urb)
अणु
	bool r;
	अगर (unlikely(urb->status)) अणु
		अगर (urb->status != -ESHUTDOWN && urb->status != -ENOENT)
			snd_prपूर्णांकk(KERN_WARNING "status=%i\n", urb->status);
		sk->iso_frame_balance = 0x7FFFFFFF;
		वापस false;
	पूर्ण
	r = sk->iso_frame_balance == 0;
	अगर (!r)
		sk->i_urb = urb;
	वापस r;
पूर्ण

अटल bool balance_playback(काष्ठा usb_stream_kernel *sk, काष्ठा urb *urb)
अणु
	sk->iso_frame_balance += urb->number_of_packets;
	वापस balance_check(sk, urb);
पूर्ण

अटल bool balance_capture(काष्ठा usb_stream_kernel *sk, काष्ठा urb *urb)
अणु
	sk->iso_frame_balance -= urb->number_of_packets;
	वापस balance_check(sk, urb);
पूर्ण

अटल व्योम subs_set_complete(काष्ठा urb **urbs, व्योम (*complete)(काष्ठा urb *))
अणु
	पूर्णांक u;

	क्रम (u = 0; u < USB_STREAM_NURBS; u++) अणु
		काष्ठा urb *urb = urbs[u];
		urb->complete = complete;
	पूर्ण
पूर्ण

अटल पूर्णांक usb_stream_prepare_playback(काष्ठा usb_stream_kernel *sk,
		काष्ठा urb *inurb)
अणु
	काष्ठा usb_stream *s = sk->s;
	काष्ठा urb *io;
	काष्ठा usb_iso_packet_descriptor *id, *od;
	पूर्णांक p = 0, lb = 0, l = 0;

	io = sk->idle_outurb;
	od = io->iso_frame_desc;

	क्रम (; s->sync_packet < 0; ++p, ++s->sync_packet) अणु
		काष्ठा urb *ii = sk->completed_inurb;
		id = ii->iso_frame_desc +
			ii->number_of_packets + s->sync_packet;
		l = id->actual_length;

		od[p].length = l;
		od[p].offset = lb;
		lb += l;
	पूर्ण

	क्रम (;
	     s->sync_packet < inurb->number_of_packets && p < sk->n_o_ps;
	     ++p, ++s->sync_packet) अणु
		l = inurb->iso_frame_desc[s->sync_packet].actual_length;

		अगर (s->idle_outsize + lb + l > s->period_size)
			जाओ check_ok;

		od[p].length = l;
		od[p].offset = lb;
		lb += l;
	पूर्ण

check_ok:
	s->sync_packet -= inurb->number_of_packets;
	अगर (unlikely(s->sync_packet < -2 || s->sync_packet > 0)) अणु
		snd_prपूर्णांकk(KERN_WARNING "invalid sync_packet = %i;"
			   " p=%i nop=%i %i %x %x %x > %x\n",
			   s->sync_packet, p, inurb->number_of_packets,
			   s->idle_outsize + lb + l,
			   s->idle_outsize, lb,  l,
			   s->period_size);
		वापस -1;
	पूर्ण
	अगर (unlikely(lb % s->cfg.frame_size)) अणु
		snd_prपूर्णांकk(KERN_WARNING"invalid outsize = %i\n",
			   lb);
		वापस -1;
	पूर्ण
	s->idle_outsize += lb - s->period_size;
	io->number_of_packets = p;
	io->transfer_buffer_length = lb;
	अगर (s->idle_outsize <= 0)
		वापस 0;

	snd_prपूर्णांकk(KERN_WARNING "idle=%i\n", s->idle_outsize);
	वापस -1;
पूर्ण

अटल व्योम prepare_inurb(पूर्णांक number_of_packets, काष्ठा urb *iu)
अणु
	काष्ठा usb_iso_packet_descriptor *id;
	पूर्णांक p;

	iu->number_of_packets = number_of_packets;
	id = iu->iso_frame_desc;
	id->offset = 0;
	क्रम (p = 0; p < iu->number_of_packets - 1; ++p)
		id[p + 1].offset = id[p].offset + id[p].length;

	iu->transfer_buffer_length =
		id[0].length * iu->number_of_packets;
पूर्ण

अटल पूर्णांक submit_urbs(काष्ठा usb_stream_kernel *sk,
		       काष्ठा urb *inurb, काष्ठा urb *outurb)
अणु
	पूर्णांक err;
	prepare_inurb(sk->idle_outurb->number_of_packets, sk->idle_inurb);
	err = usb_submit_urb(sk->idle_inurb, GFP_ATOMIC);
	अगर (err < 0)
		जाओ report_failure;

	sk->idle_inurb = sk->completed_inurb;
	sk->completed_inurb = inurb;
	err = usb_submit_urb(sk->idle_outurb, GFP_ATOMIC);
	अगर (err < 0)
		जाओ report_failure;

	sk->idle_outurb = sk->completed_outurb;
	sk->completed_outurb = outurb;
	वापस 0;

report_failure:
	snd_prपूर्णांकk(KERN_ERR "%i\n", err);
	वापस err;
पूर्ण

#अगर_घोषित DEBUG_LOOP_BACK
/*
  This loop_back() shows how to पढ़ो/ग_लिखो the period data.
 */
अटल व्योम loop_back(काष्ठा usb_stream *s)
अणु
	अक्षर *i, *o;
	पूर्णांक il, ol, l, p;
	काष्ठा urb *iu;
	काष्ठा usb_iso_packet_descriptor *id;

	o = s->playback1st_to;
	ol = s->playback1st_size;
	l = 0;

	अगर (s->insplit_pack >= 0) अणु
		iu = sk->idle_inurb;
		id = iu->iso_frame_desc;
		p = s->insplit_pack;
	पूर्ण अन्यथा
		जाओ second;
loop:
	क्रम (; p < iu->number_of_packets && l < s->period_size; ++p) अणु
		i = iu->transfer_buffer + id[p].offset;
		il = id[p].actual_length;
		अगर (l + il > s->period_size)
			il = s->period_size - l;
		अगर (il <= ol) अणु
			स_नकल(o, i, il);
			o += il;
			ol -= il;
		पूर्ण अन्यथा अणु
			स_नकल(o, i, ol);
			singen_6pack(o, ol);
			o = s->playback_to;
			स_नकल(o, i + ol, il - ol);
			o += il - ol;
			ol = s->period_size - s->playback1st_size;
		पूर्ण
		l += il;
	पूर्ण
	अगर (iu == sk->completed_inurb) अणु
		अगर (l != s->period_size)
			prपूर्णांकk(KERN_DEBUG"%s:%i %i\n", __func__, __LINE__,
			       l/(पूर्णांक)s->cfg.frame_size);

		वापस;
	पूर्ण
second:
	iu = sk->completed_inurb;
	id = iu->iso_frame_desc;
	p = 0;
	जाओ loop;

पूर्ण
#अन्यथा
अटल व्योम loop_back(काष्ठा usb_stream *s)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम stream_idle(काष्ठा usb_stream_kernel *sk,
			काष्ठा urb *inurb, काष्ठा urb *outurb)
अणु
	काष्ठा usb_stream *s = sk->s;
	पूर्णांक l, p;
	पूर्णांक insize = s->idle_insize;
	पूर्णांक urb_size = 0;

	s->inpacket_split = s->next_inpacket_split;
	s->inpacket_split_at = s->next_inpacket_split_at;
	s->next_inpacket_split = -1;
	s->next_inpacket_split_at = 0;

	क्रम (p = 0; p < inurb->number_of_packets; ++p) अणु
		काष्ठा usb_iso_packet_descriptor *id = inurb->iso_frame_desc;
		l = id[p].actual_length;
		अगर (unlikely(l == 0 || id[p].status)) अणु
			snd_prपूर्णांकk(KERN_WARNING "underrun, status=%u\n",
				   id[p].status);
			जाओ err_out;
		पूर्ण
		s->inpacket_head++;
		s->inpacket_head %= s->inpackets;
		अगर (s->inpacket_split == -1)
			s->inpacket_split = s->inpacket_head;

		s->inpacket[s->inpacket_head].offset =
			id[p].offset + (inurb->transfer_buffer - (व्योम *)s);
		s->inpacket[s->inpacket_head].length = l;
		अगर (insize + l > s->period_size &&
		    s->next_inpacket_split == -1) अणु
			s->next_inpacket_split = s->inpacket_head;
			s->next_inpacket_split_at = s->period_size - insize;
		पूर्ण
		insize += l;
		urb_size += l;
	पूर्ण
	s->idle_insize += urb_size - s->period_size;
	अगर (s->idle_insize < 0) अणु
		snd_prपूर्णांकk(KERN_WARNING "%i\n",
			   (s->idle_insize)/(पूर्णांक)s->cfg.frame_size);
		जाओ err_out;
	पूर्ण
	s->insize_करोne += urb_size;

	l = s->idle_outsize;
	s->outpacket[0].offset = (sk->idle_outurb->transfer_buffer -
				  sk->ग_लिखो_page) - l;

	अगर (usb_stream_prepare_playback(sk, inurb) < 0)
		जाओ err_out;

	s->outpacket[0].length = sk->idle_outurb->transfer_buffer_length + l;
	s->outpacket[1].offset = sk->completed_outurb->transfer_buffer -
		sk->ग_लिखो_page;

	अगर (submit_urbs(sk, inurb, outurb) < 0)
		जाओ err_out;

	loop_back(s);
	s->periods_करोne++;
	wake_up_all(&sk->sleep);
	वापस;
err_out:
	s->state = usb_stream_xrun;
	wake_up_all(&sk->sleep);
पूर्ण

अटल व्योम i_capture_idle(काष्ठा urb *urb)
अणु
	काष्ठा usb_stream_kernel *sk = urb->context;
	अगर (balance_capture(sk, urb))
		stream_idle(sk, urb, sk->i_urb);
पूर्ण

अटल व्योम i_playback_idle(काष्ठा urb *urb)
अणु
	काष्ठा usb_stream_kernel *sk = urb->context;
	अगर (balance_playback(sk, urb))
		stream_idle(sk, sk->i_urb, urb);
पूर्ण

अटल व्योम stream_start(काष्ठा usb_stream_kernel *sk,
			 काष्ठा urb *inurb, काष्ठा urb *outurb)
अणु
	काष्ठा usb_stream *s = sk->s;
	अगर (s->state >= usb_stream_sync1) अणु
		पूर्णांक l, p, max_dअगरf, max_dअगरf_0;
		पूर्णांक urb_size = 0;
		अचिन्हित frames_per_packet, min_frames = 0;
		frames_per_packet = (s->period_size - s->idle_insize);
		frames_per_packet <<= 8;
		frames_per_packet /=
			s->cfg.frame_size * inurb->number_of_packets;
		frames_per_packet++;

		max_dअगरf_0 = s->cfg.frame_size;
		अगर (s->cfg.period_frames >= 256)
			max_dअगरf_0 <<= 1;
		अगर (s->cfg.period_frames >= 1024)
			max_dअगरf_0 <<= 1;
		max_dअगरf = max_dअगरf_0;
		क्रम (p = 0; p < inurb->number_of_packets; ++p) अणु
			पूर्णांक dअगरf;
			l = inurb->iso_frame_desc[p].actual_length;
			urb_size += l;

			min_frames += frames_per_packet;
			dअगरf = urb_size -
				(min_frames >> 8) * s->cfg.frame_size;
			अगर (dअगरf < max_dअगरf) अणु
				snd_prपूर्णांकdd(KERN_DEBUG "%i %i %i %i\n",
					    s->insize_करोne,
					    urb_size / (पूर्णांक)s->cfg.frame_size,
					    inurb->number_of_packets, dअगरf);
				max_dअगरf = dअगरf;
			पूर्ण
		पूर्ण
		s->idle_insize -= max_dअगरf - max_dअगरf_0;
		s->idle_insize += urb_size - s->period_size;
		अगर (s->idle_insize < 0) अणु
			snd_prपूर्णांकk(KERN_WARNING "%i %i %i\n",
				   s->idle_insize, urb_size, s->period_size);
			वापस;
		पूर्ण अन्यथा अगर (s->idle_insize == 0) अणु
			s->next_inpacket_split =
				(s->inpacket_head + 1) % s->inpackets;
			s->next_inpacket_split_at = 0;
		पूर्ण अन्यथा अणु
			अचिन्हित split = s->inpacket_head;
			l = s->idle_insize;
			जबतक (l > s->inpacket[split].length) अणु
				l -= s->inpacket[split].length;
				अगर (split == 0)
					split = s->inpackets - 1;
				अन्यथा
					split--;
			पूर्ण
			s->next_inpacket_split = split;
			s->next_inpacket_split_at =
				s->inpacket[split].length - l;
		पूर्ण

		s->insize_करोne += urb_size;

		अगर (usb_stream_prepare_playback(sk, inurb) < 0)
			वापस;

	पूर्ण अन्यथा
		playback_prep_freqn(sk, sk->idle_outurb);

	अगर (submit_urbs(sk, inurb, outurb) < 0)
		वापस;

	अगर (s->state == usb_stream_sync1 && s->insize_करोne > 360000) अणु
		/* just guesswork                            ^^^^^^ */
		s->state = usb_stream_पढ़ोy;
		subs_set_complete(sk->inurb, i_capture_idle);
		subs_set_complete(sk->outurb, i_playback_idle);
	पूर्ण
पूर्ण

अटल व्योम i_capture_start(काष्ठा urb *urb)
अणु
	काष्ठा usb_iso_packet_descriptor *id = urb->iso_frame_desc;
	काष्ठा usb_stream_kernel *sk = urb->context;
	काष्ठा usb_stream *s = sk->s;
	पूर्णांक p;
	पूर्णांक empty = 0;

	अगर (urb->status) अणु
		snd_prपूर्णांकk(KERN_WARNING "status=%i\n", urb->status);
		वापस;
	पूर्ण

	क्रम (p = 0; p < urb->number_of_packets; ++p) अणु
		पूर्णांक l = id[p].actual_length;
		अगर (l < s->cfg.frame_size) अणु
			++empty;
			अगर (s->state >= usb_stream_sync0) अणु
				snd_prपूर्णांकk(KERN_WARNING "%i\n", l);
				वापस;
			पूर्ण
		पूर्ण
		s->inpacket_head++;
		s->inpacket_head %= s->inpackets;
		s->inpacket[s->inpacket_head].offset =
			id[p].offset + (urb->transfer_buffer - (व्योम *)s);
		s->inpacket[s->inpacket_head].length = l;
	पूर्ण
#अगर_घोषित SHOW_EMPTY
	अगर (empty) अणु
		prपूर्णांकk(KERN_DEBUG"%s:%i: %i", __func__, __LINE__,
		       urb->iso_frame_desc[0].actual_length);
		क्रम (pack = 1; pack < urb->number_of_packets; ++pack) अणु
			पूर्णांक l = urb->iso_frame_desc[pack].actual_length;
			prपूर्णांकk(KERN_CONT " %i", l);
		पूर्ण
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण
#पूर्ण_अगर
	अगर (!empty && s->state < usb_stream_sync1)
		++s->state;

	अगर (balance_capture(sk, urb))
		stream_start(sk, urb, sk->i_urb);
पूर्ण

अटल व्योम i_playback_start(काष्ठा urb *urb)
अणु
	काष्ठा usb_stream_kernel *sk = urb->context;
	अगर (balance_playback(sk, urb))
		stream_start(sk, sk->i_urb, urb);
पूर्ण

पूर्णांक usb_stream_start(काष्ठा usb_stream_kernel *sk)
अणु
	काष्ठा usb_stream *s = sk->s;
	पूर्णांक frame = 0, iters = 0;
	पूर्णांक u, err;
	पूर्णांक try = 0;

	अगर (s->state != usb_stream_stopped)
		वापस -EAGAIN;

	subs_set_complete(sk->inurb, i_capture_start);
	subs_set_complete(sk->outurb, i_playback_start);
	स_रखो(sk->ग_लिखो_page, 0, s->ग_लिखो_size);
करोtry:
	s->insize_करोne = 0;
	s->idle_insize = 0;
	s->idle_outsize = 0;
	s->sync_packet = -1;
	s->inpacket_head = -1;
	sk->iso_frame_balance = 0;
	++try;
	क्रम (u = 0; u < 2; u++) अणु
		काष्ठा urb *inurb = sk->inurb[u];
		काष्ठा urb *outurb = sk->outurb[u];
		playback_prep_freqn(sk, outurb);
		inurb->number_of_packets = outurb->number_of_packets;
		inurb->transfer_buffer_length =
			inurb->number_of_packets *
			inurb->iso_frame_desc[0].length;

		अगर (u == 0) अणु
			पूर्णांक now;
			काष्ठा usb_device *dev = inurb->dev;
			frame = usb_get_current_frame_number(dev);
			करो अणु
				now = usb_get_current_frame_number(dev);
				++iters;
			पूर्ण जबतक (now > -1 && now == frame);
		पूर्ण
		err = usb_submit_urb(inurb, GFP_ATOMIC);
		अगर (err < 0) अणु
			snd_prपूर्णांकk(KERN_ERR"usb_submit_urb(sk->inurb[%i])"
				   " returned %i\n", u, err);
			वापस err;
		पूर्ण
		err = usb_submit_urb(outurb, GFP_ATOMIC);
		अगर (err < 0) अणु
			snd_prपूर्णांकk(KERN_ERR"usb_submit_urb(sk->outurb[%i])"
				   " returned %i\n", u, err);
			वापस err;
		पूर्ण

		अगर (inurb->start_frame != outurb->start_frame) अणु
			snd_prपूर्णांकd(KERN_DEBUG
				   "u[%i] start_frames differ in:%u out:%u\n",
				   u, inurb->start_frame, outurb->start_frame);
			जाओ check_retry;
		पूर्ण
	पूर्ण
	snd_prपूर्णांकdd(KERN_DEBUG "%i %i\n", frame, iters);
	try = 0;
check_retry:
	अगर (try) अणु
		usb_stream_stop(sk);
		अगर (try < 5) अणु
			msleep(1500);
			snd_prपूर्णांकd(KERN_DEBUG "goto dotry;\n");
			जाओ करोtry;
		पूर्ण
		snd_prपूर्णांकk(KERN_WARNING"couldn't start"
			   " all urbs on the same start_frame.\n");
		वापस -EFAULT;
	पूर्ण

	sk->idle_inurb = sk->inurb[USB_STREAM_NURBS - 2];
	sk->idle_outurb = sk->outurb[USB_STREAM_NURBS - 2];
	sk->completed_inurb = sk->inurb[USB_STREAM_NURBS - 1];
	sk->completed_outurb = sk->outurb[USB_STREAM_NURBS - 1];

/* रुको, check */
	अणु
		पूर्णांक रुको_ms = 3000;
		जबतक (s->state != usb_stream_पढ़ोy && रुको_ms > 0) अणु
			snd_prपूर्णांकdd(KERN_DEBUG "%i\n", s->state);
			msleep(200);
			रुको_ms -= 200;
		पूर्ण
	पूर्ण

	वापस s->state == usb_stream_पढ़ोy ? 0 : -EFAULT;
पूर्ण


/*                             stop                                   */

व्योम usb_stream_stop(काष्ठा usb_stream_kernel *sk)
अणु
	पूर्णांक u;
	अगर (!sk->s)
		वापस;
	क्रम (u = 0; u < USB_STREAM_NURBS; ++u) अणु
		usb_समाप्त_urb(sk->inurb[u]);
		usb_समाप्त_urb(sk->outurb[u]);
	पूर्ण
	sk->s->state = usb_stream_stopped;
	msleep(400);
पूर्ण
