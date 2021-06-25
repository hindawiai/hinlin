<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   US-X2Y AUDIO
 *   Copyright (c) 2002-2004 by Karsten Wiese
 *
 *   based on
 *
 *   (Tentative) USB Audio Driver क्रम ALSA
 *
 *   Main and PCM part
 *
 *   Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 *
 *   Many codes borrowed from audio.c by 
 *	    Alan Cox (alan@lxorguk.ukuu.org.uk)
 *	    Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 */


#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/moduleparam.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "usx2y.h"
#समावेश "usbusx2y.h"

#घोषणा USX2Y_NRPACKS 4			/* Default value used क्रम nr of packs per urb.
					  1 to 4 have been tested ok on uhci.
					  To use 3 on ohci, you'd need a patch:
					  look क्रम "0000425-linux-2.6.9-rc4-mm1_ohci-hcd.patch.gz" on
					  "https://bugtrack.alsa-project.org/alsa-bug/bug_view_page.php?bug_id=0000425"
					  .
					  1, 2 and 4 work out of the box on ohci, अगर I recall correctly.
					  Bigger is safer operation,
					  smaller gives lower latencies.
					*/
#घोषणा USX2Y_NRPACKS_VARIABLE y	/* If your प्रणाली works ok with this module's parameter
					   nrpacks set to 1, you might as well comment 
					   this #घोषणा out, and thereby produce smaller, faster code.
					   You'd also set USX2Y_NRPACKS to 1 then.
					*/

#अगर_घोषित USX2Y_NRPACKS_VARIABLE
 अटल पूर्णांक nrpacks = USX2Y_NRPACKS; /* number of packets per urb */
 #घोषणा  nr_of_packs() nrpacks
 module_param(nrpacks, पूर्णांक, 0444);
 MODULE_PARM_DESC(nrpacks, "Number of packets per URB.");
#अन्यथा
 #घोषणा nr_of_packs() USX2Y_NRPACKS
#पूर्ण_अगर


अटल पूर्णांक usX2Y_urb_capt_retire(काष्ठा snd_usX2Y_substream *subs)
अणु
	काष्ठा urb	*urb = subs->completed_urb;
	काष्ठा snd_pcm_runसमय *runसमय = subs->pcm_substream->runसमय;
	अचिन्हित अक्षर	*cp;
	पूर्णांक 		i, len, lens = 0, hwptr_करोne = subs->hwptr_करोne;
	काष्ठा usX2Ydev	*usX2Y = subs->usX2Y;

	क्रम (i = 0; i < nr_of_packs(); i++) अणु
		cp = (अचिन्हित अक्षर*)urb->transfer_buffer + urb->iso_frame_desc[i].offset;
		अगर (urb->iso_frame_desc[i].status) अणु /* active? hmm, skip this */
			snd_prपूर्णांकk(KERN_ERR "active frame status %i. "
				   "Most probably some hardware problem.\n",
				   urb->iso_frame_desc[i].status);
			वापस urb->iso_frame_desc[i].status;
		पूर्ण
		len = urb->iso_frame_desc[i].actual_length / usX2Y->stride;
		अगर (! len) अणु
			snd_prपूर्णांकd("0 == len ERROR!\n");
			जारी;
		पूर्ण

		/* copy a data chunk */
		अगर ((hwptr_करोne + len) > runसमय->buffer_size) अणु
			पूर्णांक cnt = runसमय->buffer_size - hwptr_करोne;
			पूर्णांक blen = cnt * usX2Y->stride;
			स_नकल(runसमय->dma_area + hwptr_करोne * usX2Y->stride, cp, blen);
			स_नकल(runसमय->dma_area, cp + blen, len * usX2Y->stride - blen);
		पूर्ण अन्यथा अणु
			स_नकल(runसमय->dma_area + hwptr_करोne * usX2Y->stride, cp,
			       len * usX2Y->stride);
		पूर्ण
		lens += len;
		अगर ((hwptr_करोne += len) >= runसमय->buffer_size)
			hwptr_करोne -= runसमय->buffer_size;
	पूर्ण

	subs->hwptr_करोne = hwptr_करोne;
	subs->transfer_करोne += lens;
	/* update the poपूर्णांकer, call callback अगर necessary */
	अगर (subs->transfer_करोne >= runसमय->period_size) अणु
		subs->transfer_करोne -= runसमय->period_size;
		snd_pcm_period_elapsed(subs->pcm_substream);
	पूर्ण
	वापस 0;
पूर्ण
/*
 * prepare urb क्रम playback data pipe
 *
 * we copy the data directly from the pcm buffer.
 * the current position to be copied is held in hwptr field.
 * since a urb can handle only a single linear buffer, अगर the total
 * transferred area overflows the buffer boundary, we cannot send
 * it directly from the buffer.  thus the data is once copied to
 * a temporary buffer and urb poपूर्णांकs to that.
 */
अटल पूर्णांक usX2Y_urb_play_prepare(काष्ठा snd_usX2Y_substream *subs,
				  काष्ठा urb *cap_urb,
				  काष्ठा urb *urb)
अणु
	पूर्णांक count, counts, pack;
	काष्ठा usX2Ydev *usX2Y = subs->usX2Y;
	काष्ठा snd_pcm_runसमय *runसमय = subs->pcm_substream->runसमय;

	count = 0;
	क्रम (pack = 0; pack <  nr_of_packs(); pack++) अणु
		/* calculate the size of a packet */
		counts = cap_urb->iso_frame_desc[pack].actual_length / usX2Y->stride;
		count += counts;
		अगर (counts < 43 || counts > 50) अणु
			snd_prपूर्णांकk(KERN_ERR "should not be here with counts=%i\n", counts);
			वापस -EPIPE;
		पूर्ण
		/* set up descriptor */
		urb->iso_frame_desc[pack].offset = pack ?
			urb->iso_frame_desc[pack - 1].offset +
			urb->iso_frame_desc[pack - 1].length :
			0;
		urb->iso_frame_desc[pack].length = cap_urb->iso_frame_desc[pack].actual_length;
	पूर्ण
	अगर (atomic_पढ़ो(&subs->state) >= state_PRERUNNING)
		अगर (subs->hwptr + count > runसमय->buffer_size) अणु
			/* err, the transferred area goes over buffer boundary.
			 * copy the data to the temp buffer.
			 */
			पूर्णांक len;
			len = runसमय->buffer_size - subs->hwptr;
			urb->transfer_buffer = subs->पंचांगpbuf;
			स_नकल(subs->पंचांगpbuf, runसमय->dma_area +
			       subs->hwptr * usX2Y->stride, len * usX2Y->stride);
			स_नकल(subs->पंचांगpbuf + len * usX2Y->stride,
			       runसमय->dma_area, (count - len) * usX2Y->stride);
			subs->hwptr += count;
			subs->hwptr -= runसमय->buffer_size;
		पूर्ण अन्यथा अणु
			/* set the buffer poपूर्णांकer */
			urb->transfer_buffer = runसमय->dma_area + subs->hwptr * usX2Y->stride;
			अगर ((subs->hwptr += count) >= runसमय->buffer_size)
				subs->hwptr -= runसमय->buffer_size;
		पूर्ण
	अन्यथा
		urb->transfer_buffer = subs->पंचांगpbuf;
	urb->transfer_buffer_length = count * usX2Y->stride;
	वापस 0;
पूर्ण

/*
 * process after playback data complete
 *
 * update the current position and call callback अगर a period is processed.
 */
अटल व्योम usX2Y_urb_play_retire(काष्ठा snd_usX2Y_substream *subs, काष्ठा urb *urb)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = subs->pcm_substream->runसमय;
	पूर्णांक		len = urb->actual_length / subs->usX2Y->stride;

	subs->transfer_करोne += len;
	subs->hwptr_करोne +=  len;
	अगर (subs->hwptr_करोne >= runसमय->buffer_size)
		subs->hwptr_करोne -= runसमय->buffer_size;
	अगर (subs->transfer_करोne >= runसमय->period_size) अणु
		subs->transfer_करोne -= runसमय->period_size;
		snd_pcm_period_elapsed(subs->pcm_substream);
	पूर्ण
पूर्ण

अटल पूर्णांक usX2Y_urb_submit(काष्ठा snd_usX2Y_substream *subs, काष्ठा urb *urb, पूर्णांक frame)
अणु
	पूर्णांक err;
	अगर (!urb)
		वापस -ENODEV;
	urb->start_frame = (frame + NRURBS * nr_of_packs());  // let hcd करो rollover sanity checks
	urb->hcpriv = शून्य;
	urb->dev = subs->usX2Y->dev; /* we need to set this at each समय */
	अगर ((err = usb_submit_urb(urb, GFP_ATOMIC)) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "usb_submit_urb() returned %i\n", err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक usX2Y_usbframe_complete(काष्ठा snd_usX2Y_substream *capsubs,
					  काष्ठा snd_usX2Y_substream *playbacksubs,
					  पूर्णांक frame)
अणु
	पूर्णांक err, state;
	काष्ठा urb *urb = playbacksubs->completed_urb;

	state = atomic_पढ़ो(&playbacksubs->state);
	अगर (शून्य != urb) अणु
		अगर (state == state_RUNNING)
			usX2Y_urb_play_retire(playbacksubs, urb);
		अन्यथा अगर (state >= state_PRERUNNING)
			atomic_inc(&playbacksubs->state);
	पूर्ण अन्यथा अणु
		चयन (state) अणु
		हाल state_STARTING1:
			urb = playbacksubs->urb[0];
			atomic_inc(&playbacksubs->state);
			अवरोध;
		हाल state_STARTING2:
			urb = playbacksubs->urb[1];
			atomic_inc(&playbacksubs->state);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (urb) अणु
		अगर ((err = usX2Y_urb_play_prepare(playbacksubs, capsubs->completed_urb, urb)) ||
		    (err = usX2Y_urb_submit(playbacksubs, urb, frame))) अणु
			वापस err;
		पूर्ण
	पूर्ण

	playbacksubs->completed_urb = शून्य;

	state = atomic_पढ़ो(&capsubs->state);
	अगर (state >= state_PREPARED) अणु
		अगर (state == state_RUNNING) अणु
			अगर ((err = usX2Y_urb_capt_retire(capsubs)))
				वापस err;
		पूर्ण अन्यथा अगर (state >= state_PRERUNNING)
			atomic_inc(&capsubs->state);
		अगर ((err = usX2Y_urb_submit(capsubs, capsubs->completed_urb, frame)))
			वापस err;
	पूर्ण
	capsubs->completed_urb = शून्य;
	वापस 0;
पूर्ण


अटल व्योम usX2Y_clients_stop(काष्ठा usX2Ydev *usX2Y)
अणु
	पूर्णांक s, u;

	क्रम (s = 0; s < 4; s++) अणु
		काष्ठा snd_usX2Y_substream *subs = usX2Y->subs[s];
		अगर (subs) अणु
			snd_prपूर्णांकdd("%i %p state=%i\n", s, subs, atomic_पढ़ो(&subs->state));
			atomic_set(&subs->state, state_STOPPED);
		पूर्ण
	पूर्ण
	क्रम (s = 0; s < 4; s++) अणु
		काष्ठा snd_usX2Y_substream *subs = usX2Y->subs[s];
		अगर (subs) अणु
			अगर (atomic_पढ़ो(&subs->state) >= state_PRERUNNING)
				snd_pcm_stop_xrun(subs->pcm_substream);
			क्रम (u = 0; u < NRURBS; u++) अणु
				काष्ठा urb *urb = subs->urb[u];
				अगर (शून्य != urb)
					snd_prपूर्णांकdd("%i status=%i start_frame=%i\n",
						    u, urb->status, urb->start_frame);
			पूर्ण
		पूर्ण
	पूर्ण
	usX2Y->prepare_subs = शून्य;
	wake_up(&usX2Y->prepare_रुको_queue);
पूर्ण

अटल व्योम usX2Y_error_urb_status(काष्ठा usX2Ydev *usX2Y,
				   काष्ठा snd_usX2Y_substream *subs, काष्ठा urb *urb)
अणु
	snd_prपूर्णांकk(KERN_ERR "ep=%i stalled with status=%i\n", subs->endpoपूर्णांक, urb->status);
	urb->status = 0;
	usX2Y_clients_stop(usX2Y);
पूर्ण

अटल व्योम i_usX2Y_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा snd_usX2Y_substream *subs = urb->context;
	काष्ठा usX2Ydev *usX2Y = subs->usX2Y;

	अगर (unlikely(atomic_पढ़ो(&subs->state) < state_PREPARED)) अणु
		snd_prपूर्णांकdd("hcd_frame=%i ep=%i%s status=%i start_frame=%i\n",
			    usb_get_current_frame_number(usX2Y->dev),
			    subs->endpoपूर्णांक, usb_pipein(urb->pipe) ? "in" : "out",
			    urb->status, urb->start_frame);
		वापस;
	पूर्ण
	अगर (unlikely(urb->status)) अणु
		usX2Y_error_urb_status(usX2Y, subs, urb);
		वापस;
	पूर्ण

	subs->completed_urb = urb;

	अणु
		काष्ठा snd_usX2Y_substream *capsubs = usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE],
			*playbacksubs = usX2Y->subs[SNDRV_PCM_STREAM_PLAYBACK];
		अगर (capsubs->completed_urb &&
		    atomic_पढ़ो(&capsubs->state) >= state_PREPARED &&
		    (playbacksubs->completed_urb ||
		     atomic_पढ़ो(&playbacksubs->state) < state_PREPARED)) अणु
			अगर (!usX2Y_usbframe_complete(capsubs, playbacksubs, urb->start_frame))
				usX2Y->रुको_iso_frame += nr_of_packs();
			अन्यथा अणु
				snd_prपूर्णांकdd("\n");
				usX2Y_clients_stop(usX2Y);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usX2Y_urbs_set_complete(काष्ठा usX2Ydev * usX2Y,
				    व्योम (*complete)(काष्ठा urb *))
अणु
	पूर्णांक s, u;
	क्रम (s = 0; s < 4; s++) अणु
		काष्ठा snd_usX2Y_substream *subs = usX2Y->subs[s];
		अगर (शून्य != subs)
			क्रम (u = 0; u < NRURBS; u++) अणु
				काष्ठा urb * urb = subs->urb[u];
				अगर (शून्य != urb)
					urb->complete = complete;
			पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usX2Y_subs_startup_finish(काष्ठा usX2Ydev * usX2Y)
अणु
	usX2Y_urbs_set_complete(usX2Y, i_usX2Y_urb_complete);
	usX2Y->prepare_subs = शून्य;
पूर्ण

अटल व्योम i_usX2Y_subs_startup(काष्ठा urb *urb)
अणु
	काष्ठा snd_usX2Y_substream *subs = urb->context;
	काष्ठा usX2Ydev *usX2Y = subs->usX2Y;
	काष्ठा snd_usX2Y_substream *prepare_subs = usX2Y->prepare_subs;
	अगर (शून्य != prepare_subs)
		अगर (urb->start_frame == prepare_subs->urb[0]->start_frame) अणु
			usX2Y_subs_startup_finish(usX2Y);
			atomic_inc(&prepare_subs->state);
			wake_up(&usX2Y->prepare_रुको_queue);
		पूर्ण

	i_usX2Y_urb_complete(urb);
पूर्ण

अटल व्योम usX2Y_subs_prepare(काष्ठा snd_usX2Y_substream *subs)
अणु
	snd_prपूर्णांकdd("usX2Y_substream_prepare(%p) ep=%i urb0=%p urb1=%p\n",
		    subs, subs->endpoपूर्णांक, subs->urb[0], subs->urb[1]);
	/* reset the poपूर्णांकer */
	subs->hwptr = 0;
	subs->hwptr_करोne = 0;
	subs->transfer_करोne = 0;
पूर्ण


अटल व्योम usX2Y_urb_release(काष्ठा urb **urb, पूर्णांक मुक्त_tb)
अणु
	अगर (*urb) अणु
		usb_समाप्त_urb(*urb);
		अगर (मुक्त_tb)
			kमुक्त((*urb)->transfer_buffer);
		usb_मुक्त_urb(*urb);
		*urb = शून्य;
	पूर्ण
पूर्ण
/*
 * release a substreams urbs
 */
अटल व्योम usX2Y_urbs_release(काष्ठा snd_usX2Y_substream *subs)
अणु
	पूर्णांक i;
	snd_prपूर्णांकdd("usX2Y_urbs_release() %i\n", subs->endpoपूर्णांक);
	क्रम (i = 0; i < NRURBS; i++)
		usX2Y_urb_release(subs->urb + i,
				  subs != subs->usX2Y->subs[SNDRV_PCM_STREAM_PLAYBACK]);

	kमुक्त(subs->पंचांगpbuf);
	subs->पंचांगpbuf = शून्य;
पूर्ण
/*
 * initialize a substream's urbs
 */
अटल पूर्णांक usX2Y_urbs_allocate(काष्ठा snd_usX2Y_substream *subs)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक is_playback = subs == subs->usX2Y->subs[SNDRV_PCM_STREAM_PLAYBACK];
	काष्ठा usb_device *dev = subs->usX2Y->dev;

	pipe = is_playback ? usb_sndisocpipe(dev, subs->endpoपूर्णांक) :
			usb_rcvisocpipe(dev, subs->endpoपूर्णांक);
	subs->maxpacksize = usb_maxpacket(dev, pipe, is_playback);
	अगर (!subs->maxpacksize)
		वापस -EINVAL;

	अगर (is_playback && शून्य == subs->पंचांगpbuf) अणु	/* allocate a temporary buffer क्रम playback */
		subs->पंचांगpbuf = kसुस्मृति(nr_of_packs(), subs->maxpacksize, GFP_KERNEL);
		अगर (!subs->पंचांगpbuf)
			वापस -ENOMEM;
	पूर्ण
	/* allocate and initialize data urbs */
	क्रम (i = 0; i < NRURBS; i++) अणु
		काष्ठा urb **purb = subs->urb + i;
		अगर (*purb) अणु
			usb_समाप्त_urb(*purb);
			जारी;
		पूर्ण
		*purb = usb_alloc_urb(nr_of_packs(), GFP_KERNEL);
		अगर (शून्य == *purb) अणु
			usX2Y_urbs_release(subs);
			वापस -ENOMEM;
		पूर्ण
		अगर (!is_playback && !(*purb)->transfer_buffer) अणु
			/* allocate a capture buffer per urb */
			(*purb)->transfer_buffer =
				kदो_स्मृति_array(subs->maxpacksize,
					      nr_of_packs(), GFP_KERNEL);
			अगर (शून्य == (*purb)->transfer_buffer) अणु
				usX2Y_urbs_release(subs);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
		(*purb)->dev = dev;
		(*purb)->pipe = pipe;
		(*purb)->number_of_packets = nr_of_packs();
		(*purb)->context = subs;
		(*purb)->पूर्णांकerval = 1;
		(*purb)->complete = i_usX2Y_subs_startup;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम usX2Y_subs_startup(काष्ठा snd_usX2Y_substream *subs)
अणु
	काष्ठा usX2Ydev *usX2Y = subs->usX2Y;
	usX2Y->prepare_subs = subs;
	subs->urb[0]->start_frame = -1;
	wmb();
	usX2Y_urbs_set_complete(usX2Y, i_usX2Y_subs_startup);
पूर्ण

अटल पूर्णांक usX2Y_urbs_start(काष्ठा snd_usX2Y_substream *subs)
अणु
	पूर्णांक i, err;
	काष्ठा usX2Ydev *usX2Y = subs->usX2Y;

	अगर ((err = usX2Y_urbs_allocate(subs)) < 0)
		वापस err;
	subs->completed_urb = शून्य;
	क्रम (i = 0; i < 4; i++) अणु
		काष्ठा snd_usX2Y_substream *subs = usX2Y->subs[i];
		अगर (subs != शून्य && atomic_पढ़ो(&subs->state) >= state_PREPARED)
			जाओ start;
	पूर्ण

 start:
	usX2Y_subs_startup(subs);
	क्रम (i = 0; i < NRURBS; i++) अणु
		काष्ठा urb *urb = subs->urb[i];
		अगर (usb_pipein(urb->pipe)) अणु
			अचिन्हित दीर्घ pack;
			अगर (0 == i)
				atomic_set(&subs->state, state_STARTING3);
			urb->dev = usX2Y->dev;
			क्रम (pack = 0; pack < nr_of_packs(); pack++) अणु
				urb->iso_frame_desc[pack].offset = subs->maxpacksize * pack;
				urb->iso_frame_desc[pack].length = subs->maxpacksize;
			पूर्ण
			urb->transfer_buffer_length = subs->maxpacksize * nr_of_packs(); 
			अगर ((err = usb_submit_urb(urb, GFP_ATOMIC)) < 0) अणु
				snd_prपूर्णांकk (KERN_ERR "cannot submit datapipe for urb %d, err = %d\n", i, err);
				err = -EPIPE;
				जाओ cleanup;
			पूर्ण अन्यथा
				अगर (i == 0)
					usX2Y->रुको_iso_frame = urb->start_frame;
			urb->transfer_flags = 0;
		पूर्ण अन्यथा अणु
			atomic_set(&subs->state, state_STARTING1);
			अवरोध;
		पूर्ण
	पूर्ण
	err = 0;
	रुको_event(usX2Y->prepare_रुको_queue, शून्य == usX2Y->prepare_subs);
	अगर (atomic_पढ़ो(&subs->state) != state_PREPARED)
		err = -EPIPE;

 cleanup:
	अगर (err) अणु
		usX2Y_subs_startup_finish(usX2Y);
		usX2Y_clients_stop(usX2Y);		// something is completely wroong > stop evrything
	पूर्ण
	वापस err;
पूर्ण

/*
 * वापस the current pcm poपूर्णांकer.  just वापस the hwptr_करोne value.
 */
अटल snd_pcm_uframes_t snd_usX2Y_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_usX2Y_substream *subs = substream->runसमय->निजी_data;
	वापस subs->hwptr_करोne;
पूर्ण
/*
 * start/stop substream
 */
अटल पूर्णांक snd_usX2Y_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_usX2Y_substream *subs = substream->runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_prपूर्णांकdd("snd_usX2Y_pcm_trigger(START)\n");
		अगर (atomic_पढ़ो(&subs->state) == state_PREPARED &&
		    atomic_पढ़ो(&subs->usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE]->state) >= state_PREPARED) अणु
			atomic_set(&subs->state, state_PRERUNNING);
		पूर्ण अन्यथा अणु
			snd_prपूर्णांकdd("\n");
			वापस -EPIPE;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		snd_prपूर्णांकdd("snd_usX2Y_pcm_trigger(STOP)\n");
		अगर (atomic_पढ़ो(&subs->state) >= state_PRERUNNING)
			atomic_set(&subs->state, state_PREPARED);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * allocate a buffer, setup samplerate
 *
 * so far we use a physically linear buffer although packetize transfer
 * करोesn't need a continuous area.
 * अगर sg buffer is supported on the later version of alsa, we'll follow
 * that.
 */
अटल स्थिर काष्ठा s_c2
अणु
	अक्षर c1, c2;
पूर्ण
	SetRate44100[] =
अणु
	अणु 0x14, 0x08पूर्ण,	// this line sets 44100, well actually a little less
	अणु 0x18, 0x40पूर्ण,	// only tascam / frontier design knows the further lines .......
	अणु 0x18, 0x42पूर्ण,
	अणु 0x18, 0x45पूर्ण,
	अणु 0x18, 0x46पूर्ण,
	अणु 0x18, 0x48पूर्ण,
	अणु 0x18, 0x4Aपूर्ण,
	अणु 0x18, 0x4Cपूर्ण,
	अणु 0x18, 0x4Eपूर्ण,
	अणु 0x18, 0x50पूर्ण,
	अणु 0x18, 0x52पूर्ण,
	अणु 0x18, 0x54पूर्ण,
	अणु 0x18, 0x56पूर्ण,
	अणु 0x18, 0x58पूर्ण,
	अणु 0x18, 0x5Aपूर्ण,
	अणु 0x18, 0x5Cपूर्ण,
	अणु 0x18, 0x5Eपूर्ण,
	अणु 0x18, 0x60पूर्ण,
	अणु 0x18, 0x62पूर्ण,
	अणु 0x18, 0x64पूर्ण,
	अणु 0x18, 0x66पूर्ण,
	अणु 0x18, 0x68पूर्ण,
	अणु 0x18, 0x6Aपूर्ण,
	अणु 0x18, 0x6Cपूर्ण,
	अणु 0x18, 0x6Eपूर्ण,
	अणु 0x18, 0x70पूर्ण,
	अणु 0x18, 0x72पूर्ण,
	अणु 0x18, 0x74पूर्ण,
	अणु 0x18, 0x76पूर्ण,
	अणु 0x18, 0x78पूर्ण,
	अणु 0x18, 0x7Aपूर्ण,
	अणु 0x18, 0x7Cपूर्ण,
	अणु 0x18, 0x7Eपूर्ण
पूर्ण;
अटल स्थिर काष्ठा s_c2 SetRate48000[] =
अणु
	अणु 0x14, 0x09पूर्ण,	// this line sets 48000, well actually a little less
	अणु 0x18, 0x40पूर्ण,	// only tascam / frontier design knows the further lines .......
	अणु 0x18, 0x42पूर्ण,
	अणु 0x18, 0x45पूर्ण,
	अणु 0x18, 0x46पूर्ण,
	अणु 0x18, 0x48पूर्ण,
	अणु 0x18, 0x4Aपूर्ण,
	अणु 0x18, 0x4Cपूर्ण,
	अणु 0x18, 0x4Eपूर्ण,
	अणु 0x18, 0x50पूर्ण,
	अणु 0x18, 0x52पूर्ण,
	अणु 0x18, 0x54पूर्ण,
	अणु 0x18, 0x56पूर्ण,
	अणु 0x18, 0x58पूर्ण,
	अणु 0x18, 0x5Aपूर्ण,
	अणु 0x18, 0x5Cपूर्ण,
	अणु 0x18, 0x5Eपूर्ण,
	अणु 0x18, 0x60पूर्ण,
	अणु 0x18, 0x62पूर्ण,
	अणु 0x18, 0x64पूर्ण,
	अणु 0x18, 0x66पूर्ण,
	अणु 0x18, 0x68पूर्ण,
	अणु 0x18, 0x6Aपूर्ण,
	अणु 0x18, 0x6Cपूर्ण,
	अणु 0x18, 0x6Eपूर्ण,
	अणु 0x18, 0x70पूर्ण,
	अणु 0x18, 0x73पूर्ण,
	अणु 0x18, 0x74पूर्ण,
	अणु 0x18, 0x76पूर्ण,
	अणु 0x18, 0x78पूर्ण,
	अणु 0x18, 0x7Aपूर्ण,
	अणु 0x18, 0x7Cपूर्ण,
	अणु 0x18, 0x7Eपूर्ण
पूर्ण;
#घोषणा NOOF_SETRATE_URBS ARRAY_SIZE(SetRate48000)

अटल व्योम i_usX2Y_04Int(काष्ठा urb *urb)
अणु
	काष्ठा usX2Ydev *usX2Y = urb->context;
	
	अगर (urb->status)
		snd_prपूर्णांकk(KERN_ERR "snd_usX2Y_04Int() urb->status=%i\n", urb->status);
	अगर (0 == --usX2Y->US04->len)
		wake_up(&usX2Y->In04WaitQueue);
पूर्ण

अटल पूर्णांक usX2Y_rate_set(काष्ठा usX2Ydev *usX2Y, पूर्णांक rate)
अणु
	पूर्णांक			err = 0, i;
	काष्ठा snd_usX2Y_urbSeq	*us = शून्य;
	पूर्णांक			*usbdata = शून्य;
	स्थिर काष्ठा s_c2	*ra = rate == 48000 ? SetRate48000 : SetRate44100;

	अगर (usX2Y->rate != rate) अणु
		us = kzalloc(माप(*us) + माप(काष्ठा urb*) * NOOF_SETRATE_URBS, GFP_KERNEL);
		अगर (शून्य == us) अणु
			err = -ENOMEM;
			जाओ cleanup;
		पूर्ण
		usbdata = kदो_स्मृति_array(NOOF_SETRATE_URBS, माप(पूर्णांक),
					GFP_KERNEL);
		अगर (शून्य == usbdata) अणु
			err = -ENOMEM;
			जाओ cleanup;
		पूर्ण
		क्रम (i = 0; i < NOOF_SETRATE_URBS; ++i) अणु
			अगर (शून्य == (us->urb[i] = usb_alloc_urb(0, GFP_KERNEL))) अणु
				err = -ENOMEM;
				जाओ cleanup;
			पूर्ण
			((अक्षर*)(usbdata + i))[0] = ra[i].c1;
			((अक्षर*)(usbdata + i))[1] = ra[i].c2;
			usb_fill_bulk_urb(us->urb[i], usX2Y->dev, usb_sndbulkpipe(usX2Y->dev, 4),
					  usbdata + i, 2, i_usX2Y_04Int, usX2Y);
		पूर्ण
		err = usb_urb_ep_type_check(us->urb[0]);
		अगर (err < 0)
			जाओ cleanup;
		us->submitted =	0;
		us->len =	NOOF_SETRATE_URBS;
		usX2Y->US04 =	us;
		रुको_event_समयout(usX2Y->In04WaitQueue, 0 == us->len, HZ);
		usX2Y->US04 =	शून्य;
		अगर (us->len)
			err = -ENODEV;
	cleanup:
		अगर (us) अणु
			us->submitted =	2*NOOF_SETRATE_URBS;
			क्रम (i = 0; i < NOOF_SETRATE_URBS; ++i) अणु
				काष्ठा urb *urb = us->urb[i];
				अगर (!urb)
					जारी;
				अगर (urb->status) अणु
					अगर (!err)
						err = -ENODEV;
					usb_समाप्त_urb(urb);
				पूर्ण
				usb_मुक्त_urb(urb);
			पूर्ण
			usX2Y->US04 = शून्य;
			kमुक्त(usbdata);
			kमुक्त(us);
			अगर (!err)
				usX2Y->rate = rate;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण


अटल पूर्णांक usX2Y_क्रमmat_set(काष्ठा usX2Ydev *usX2Y, snd_pcm_क्रमmat_t क्रमmat)
अणु
	पूर्णांक alternate, err;
	काष्ठा list_head* p;
	अगर (क्रमmat == SNDRV_PCM_FORMAT_S24_3LE) अणु
		alternate = 2;
		usX2Y->stride = 6;
	पूर्ण अन्यथा अणु
		alternate = 1;
		usX2Y->stride = 4;
	पूर्ण
	list_क्रम_each(p, &usX2Y->midi_list) अणु
		snd_usbmidi_input_stop(p);
	पूर्ण
	usb_समाप्त_urb(usX2Y->In04urb);
	अगर ((err = usb_set_पूर्णांकerface(usX2Y->dev, 0, alternate))) अणु
		snd_prपूर्णांकk(KERN_ERR "usb_set_interface error \n");
		वापस err;
	पूर्ण
	usX2Y->In04urb->dev = usX2Y->dev;
	err = usb_submit_urb(usX2Y->In04urb, GFP_KERNEL);
	list_क्रम_each(p, &usX2Y->midi_list) अणु
		snd_usbmidi_input_start(p);
	पूर्ण
	usX2Y->क्रमmat = क्रमmat;
	usX2Y->rate = 0;
	वापस err;
पूर्ण


अटल पूर्णांक snd_usX2Y_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *hw_params)
अणु
	पूर्णांक			err = 0;
	अचिन्हित पूर्णांक		rate = params_rate(hw_params);
	snd_pcm_क्रमmat_t	क्रमmat = params_क्रमmat(hw_params);
	काष्ठा snd_card *card = substream->pstr->pcm->card;
	काष्ठा usX2Ydev	*dev = usX2Y(card);
	पूर्णांक i;

	mutex_lock(&usX2Y(card)->pcm_mutex);
	snd_prपूर्णांकdd("snd_usX2Y_hw_params(%p, %p)\n", substream, hw_params);
	/* all pcm substreams off one usX2Y have to operate at the same
	 * rate & क्रमmat
	 */
	क्रम (i = 0; i < dev->pcm_devs * 2; i++) अणु
		काष्ठा snd_usX2Y_substream *subs = dev->subs[i];
		काष्ठा snd_pcm_substream *test_substream;

		अगर (!subs)
			जारी;
		test_substream = subs->pcm_substream;
		अगर (!test_substream || test_substream == substream ||
		    !test_substream->runसमय)
			जारी;
		अगर ((test_substream->runसमय->क्रमmat &&
		     test_substream->runसमय->क्रमmat != क्रमmat) ||
		    (test_substream->runसमय->rate &&
		     test_substream->runसमय->rate != rate)) अणु
			err = -EINVAL;
			जाओ error;
		पूर्ण
	पूर्ण

 error:
	mutex_unlock(&usX2Y(card)->pcm_mutex);
	वापस err;
पूर्ण

/*
 * मुक्त the buffer
 */
अटल पूर्णांक snd_usX2Y_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_usX2Y_substream *subs = runसमय->निजी_data;
	mutex_lock(&subs->usX2Y->pcm_mutex);
	snd_prपूर्णांकdd("snd_usX2Y_hw_free(%p)\n", substream);

	अगर (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) अणु
		काष्ठा snd_usX2Y_substream *cap_subs = subs->usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE];
		atomic_set(&subs->state, state_STOPPED);
		usX2Y_urbs_release(subs);
		अगर (!cap_subs->pcm_substream ||
		    !cap_subs->pcm_substream->runसमय ||
		    !cap_subs->pcm_substream->runसमय->status ||
		    cap_subs->pcm_substream->runसमय->status->state < SNDRV_PCM_STATE_PREPARED) अणु
			atomic_set(&cap_subs->state, state_STOPPED);
			usX2Y_urbs_release(cap_subs);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा snd_usX2Y_substream *playback_subs = subs->usX2Y->subs[SNDRV_PCM_STREAM_PLAYBACK];
		अगर (atomic_पढ़ो(&playback_subs->state) < state_PREPARED) अणु
			atomic_set(&subs->state, state_STOPPED);
			usX2Y_urbs_release(subs);
		पूर्ण
	पूर्ण
	mutex_unlock(&subs->usX2Y->pcm_mutex);
	वापस 0;
पूर्ण
/*
 * prepare callback
 *
 * set क्रमmat and initialize urbs
 */
अटल पूर्णांक snd_usX2Y_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_usX2Y_substream *subs = runसमय->निजी_data;
	काष्ठा usX2Ydev *usX2Y = subs->usX2Y;
	काष्ठा snd_usX2Y_substream *capsubs = subs->usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE];
	पूर्णांक err = 0;
	snd_prपूर्णांकdd("snd_usX2Y_pcm_prepare(%p)\n", substream);

	mutex_lock(&usX2Y->pcm_mutex);
	usX2Y_subs_prepare(subs);
// Start hardware streams
// SyncStream first....
	अगर (atomic_पढ़ो(&capsubs->state) < state_PREPARED) अणु
		अगर (usX2Y->क्रमmat != runसमय->क्रमmat)
			अगर ((err = usX2Y_क्रमmat_set(usX2Y, runसमय->क्रमmat)) < 0)
				जाओ up_prepare_mutex;
		अगर (usX2Y->rate != runसमय->rate)
			अगर ((err = usX2Y_rate_set(usX2Y, runसमय->rate)) < 0)
				जाओ up_prepare_mutex;
		snd_prपूर्णांकdd("starting capture pipe for %s\n", subs == capsubs ? "self" : "playpipe");
		अगर (0 > (err = usX2Y_urbs_start(capsubs)))
			जाओ up_prepare_mutex;
	पूर्ण

	अगर (subs != capsubs && atomic_पढ़ो(&subs->state) < state_PREPARED)
		err = usX2Y_urbs_start(subs);

 up_prepare_mutex:
	mutex_unlock(&usX2Y->pcm_mutex);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_usX2Y_2c =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_BATCH),
	.क्रमmats =                 SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_3LE,
	.rates =                   SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000,
	.rate_min =                44100,
	.rate_max =                48000,
	.channels_min =            2,
	.channels_max =            2,
	.buffer_bytes_max =	(2*128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		1024,
	.fअगरo_size =              0
पूर्ण;



अटल पूर्णांक snd_usX2Y_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_usX2Y_substream	*subs = ((काष्ठा snd_usX2Y_substream **)
					 snd_pcm_substream_chip(substream))[substream->stream];
	काष्ठा snd_pcm_runसमय	*runसमय = substream->runसमय;

	अगर (subs->usX2Y->chip_status & USX2Y_STAT_CHIP_MMAP_PCM_URBS)
		वापस -EBUSY;

	runसमय->hw = snd_usX2Y_2c;
	runसमय->निजी_data = subs;
	subs->pcm_substream = substream;
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_PERIOD_TIME, 1000, 200000);
	वापस 0;
पूर्ण



अटल पूर्णांक snd_usX2Y_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_usX2Y_substream *subs = runसमय->निजी_data;

	subs->pcm_substream = शून्य;

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा snd_pcm_ops snd_usX2Y_pcm_ops =
अणु
	.खोलो =		snd_usX2Y_pcm_खोलो,
	.बंद =	snd_usX2Y_pcm_बंद,
	.hw_params =	snd_usX2Y_pcm_hw_params,
	.hw_मुक्त =	snd_usX2Y_pcm_hw_मुक्त,
	.prepare =	snd_usX2Y_pcm_prepare,
	.trigger =	snd_usX2Y_pcm_trigger,
	.poपूर्णांकer =	snd_usX2Y_pcm_poपूर्णांकer,
पूर्ण;


/*
 * मुक्त a usb stream instance
 */
अटल व्योम usX2Y_audio_stream_मुक्त(काष्ठा snd_usX2Y_substream **usX2Y_substream)
अणु
	पूर्णांक stream;

	क्रम_each_pcm_streams(stream) अणु
		kमुक्त(usX2Y_substream[stream]);
		usX2Y_substream[stream] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम snd_usX2Y_pcm_निजी_मुक्त(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_usX2Y_substream **usX2Y_stream = pcm->निजी_data;
	अगर (usX2Y_stream)
		usX2Y_audio_stream_मुक्त(usX2Y_stream);
पूर्ण

अटल पूर्णांक usX2Y_audio_stream_new(काष्ठा snd_card *card, पूर्णांक playback_endpoपूर्णांक, पूर्णांक capture_endpoपूर्णांक)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err, i;
	काष्ठा snd_usX2Y_substream **usX2Y_substream =
		usX2Y(card)->subs + 2 * usX2Y(card)->pcm_devs;

	क्रम (i = playback_endpoपूर्णांक ? SNDRV_PCM_STREAM_PLAYBACK : SNDRV_PCM_STREAM_CAPTURE;
	     i <= SNDRV_PCM_STREAM_CAPTURE; ++i) अणु
		usX2Y_substream[i] = kzalloc(माप(काष्ठा snd_usX2Y_substream), GFP_KERNEL);
		अगर (!usX2Y_substream[i])
			वापस -ENOMEM;

		usX2Y_substream[i]->usX2Y = usX2Y(card);
	पूर्ण

	अगर (playback_endpoपूर्णांक)
		usX2Y_substream[SNDRV_PCM_STREAM_PLAYBACK]->endpoपूर्णांक = playback_endpoपूर्णांक;
	usX2Y_substream[SNDRV_PCM_STREAM_CAPTURE]->endpoपूर्णांक = capture_endpoपूर्णांक;

	err = snd_pcm_new(card, NAME_ALLCAPS" Audio", usX2Y(card)->pcm_devs,
			  playback_endpoपूर्णांक ? 1 : 0, 1,
			  &pcm);
	अगर (err < 0) अणु
		usX2Y_audio_stream_मुक्त(usX2Y_substream);
		वापस err;
	पूर्ण

	अगर (playback_endpoपूर्णांक)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_usX2Y_pcm_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_usX2Y_pcm_ops);

	pcm->निजी_data = usX2Y_substream;
	pcm->निजी_मुक्त = snd_usX2Y_pcm_निजी_मुक्त;
	pcm->info_flags = 0;

	प्र_लिखो(pcm->name, NAME_ALLCAPS" Audio #%d", usX2Y(card)->pcm_devs);

	अगर (playback_endpoपूर्णांक) अणु
		snd_pcm_set_managed_buffer(pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream,
					   SNDRV_DMA_TYPE_CONTINUOUS,
					   शून्य,
					   64*1024, 128*1024);
	पूर्ण

	snd_pcm_set_managed_buffer(pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream,
				   SNDRV_DMA_TYPE_CONTINUOUS,
				   शून्य,
				   64*1024, 128*1024);
	usX2Y(card)->pcm_devs++;

	वापस 0;
पूर्ण

/*
 * create a chip instance and set its names.
 */
पूर्णांक usX2Y_audio_create(काष्ठा snd_card *card)
अणु
	पूर्णांक err = 0;
	
	INIT_LIST_HEAD(&usX2Y(card)->pcm_list);

	अगर (0 > (err = usX2Y_audio_stream_new(card, 0xA, 0x8)))
		वापस err;
	अगर (le16_to_cpu(usX2Y(card)->dev->descriptor.idProduct) == USB_ID_US428)
	     अगर (0 > (err = usX2Y_audio_stream_new(card, 0, 0xA)))
		     वापस err;
	अगर (le16_to_cpu(usX2Y(card)->dev->descriptor.idProduct) != USB_ID_US122)
		err = usX2Y_rate_set(usX2Y(card), 44100);	// Lets us428 recognize output-volume settings, disturbs us122.
	वापस err;
पूर्ण
