<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

/* USX2Y "rawusb" aka hwdep_pcm implementation

 Its usb's unableness to atomically handle घातer of 2 period sized data chuncs
 at standard samplerates,
 what led to this part of the usx2y module: 
 It provides the alsa kernel half of the usx2y-alsa-jack driver pair.
 The pair uses a hardware dependent alsa-device क्रम mmaped pcm transport.
 Advantage achieved:
         The usb_hc moves pcm data from/पूर्णांकo memory via DMA.
         That memory is mmaped by jack's usx2y driver.
         Jack's usx2y driver is the first/last to पढ़ो/ग_लिखो pcm data.
         Read/ग_लिखो is a combination of घातer of 2 period shaping and
         भग्न/पूर्णांक conversation.
         Compared to मुख्यline alsa/jack we leave out घातer of 2 period shaping inside
         snd-usb-usx2y which needs स_नकल() and additional buffers.
         As a side effect possible unwanted pcm-data coruption resulting of
         standard alsa's snd-usb-usx2y period shaping scheme falls away.
         Result is sane jack operation at buffering schemes करोwn to 128frames,
         2 periods.
         plain usx2y alsa mode is able to achieve 64frames, 4periods, but only at the
         cost of easier triggered i.e. aeolus xruns (128 or 256frames,
         2periods works but is useless cause of crackling).

 This is a first "proof of concept" implementation.
 Later, functionalities should migrate to more appropriate places:
 Userland:
 - The jackd could mmap its भग्न-pcm buffers directly from alsa-lib.
 - alsa-lib could provide घातer of 2 period sized shaping combined with पूर्णांक/भग्न
   conversation.
   Currently the usx2y jack driver provides above 2 services.
 Kernel:
 - rawusb dma pcm buffer transport should go to snd-usb-lib, so also snd-usb-audio
   devices can use it.
   Currently rawusb dma pcm buffer transport (this file) is only available to snd-usb-usx2y. 
*/

#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश "usbusx2yaudio.c"

#अगर defined(USX2Y_NRPACKS_VARIABLE) || USX2Y_NRPACKS == 1

#समावेश <sound/hwdep.h>


अटल पूर्णांक usX2Y_usbpcm_urb_capt_retire(काष्ठा snd_usX2Y_substream *subs)
अणु
	काष्ठा urb	*urb = subs->completed_urb;
	काष्ठा snd_pcm_runसमय *runसमय = subs->pcm_substream->runसमय;
	पूर्णांक 		i, lens = 0, hwptr_करोne = subs->hwptr_करोne;
	काष्ठा usX2Ydev	*usX2Y = subs->usX2Y;
	अगर (0 > usX2Y->hwdep_pcm_shm->capture_iso_start) अणु //FIXME
		पूर्णांक head = usX2Y->hwdep_pcm_shm->captured_iso_head + 1;
		अगर (head >= ARRAY_SIZE(usX2Y->hwdep_pcm_shm->captured_iso))
			head = 0;
		usX2Y->hwdep_pcm_shm->capture_iso_start = head;
		snd_prपूर्णांकdd("cap start %i\n", head);
	पूर्ण
	क्रम (i = 0; i < nr_of_packs(); i++) अणु
		अगर (urb->iso_frame_desc[i].status) अणु /* active? hmm, skip this */
			snd_prपूर्णांकk(KERN_ERR "active frame status %i. Most probably some hardware problem.\n", urb->iso_frame_desc[i].status);
			वापस urb->iso_frame_desc[i].status;
		पूर्ण
		lens += urb->iso_frame_desc[i].actual_length / usX2Y->stride;
	पूर्ण
	अगर ((hwptr_करोne += lens) >= runसमय->buffer_size)
		hwptr_करोne -= runसमय->buffer_size;
	subs->hwptr_करोne = hwptr_करोne;
	subs->transfer_करोne += lens;
	/* update the poपूर्णांकer, call callback अगर necessary */
	अगर (subs->transfer_करोne >= runसमय->period_size) अणु
		subs->transfer_करोne -= runसमय->period_size;
		snd_pcm_period_elapsed(subs->pcm_substream);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक usX2Y_iso_frames_per_buffer(काष्ठा snd_pcm_runसमय *runसमय,
					      काष्ठा usX2Ydev * usX2Y)
अणु
	वापस (runसमय->buffer_size * 1000) / usX2Y->rate + 1;	//FIXME: so far only correct period_size == 2^x ?
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
अटल पूर्णांक usX2Y_hwdep_urb_play_prepare(काष्ठा snd_usX2Y_substream *subs,
					काष्ठा urb *urb)
अणु
	पूर्णांक count, counts, pack;
	काष्ठा usX2Ydev *usX2Y = subs->usX2Y;
	काष्ठा snd_usX2Y_hwdep_pcm_shm *shm = usX2Y->hwdep_pcm_shm;
	काष्ठा snd_pcm_runसमय *runसमय = subs->pcm_substream->runसमय;

	अगर (0 > shm->playback_iso_start) अणु
		shm->playback_iso_start = shm->captured_iso_head -
			usX2Y_iso_frames_per_buffer(runसमय, usX2Y);
		अगर (0 > shm->playback_iso_start)
			shm->playback_iso_start += ARRAY_SIZE(shm->captured_iso);
		shm->playback_iso_head = shm->playback_iso_start;
	पूर्ण

	count = 0;
	क्रम (pack = 0; pack < nr_of_packs(); pack++) अणु
		/* calculate the size of a packet */
		counts = shm->captured_iso[shm->playback_iso_head].length / usX2Y->stride;
		अगर (counts < 43 || counts > 50) अणु
			snd_prपूर्णांकk(KERN_ERR "should not be here with counts=%i\n", counts);
			वापस -EPIPE;
		पूर्ण
		/* set up descriptor */
		urb->iso_frame_desc[pack].offset = shm->captured_iso[shm->playback_iso_head].offset;
		urb->iso_frame_desc[pack].length = shm->captured_iso[shm->playback_iso_head].length;
		अगर (atomic_पढ़ो(&subs->state) != state_RUNNING)
			स_रखो((अक्षर *)urb->transfer_buffer + urb->iso_frame_desc[pack].offset, 0,
			       urb->iso_frame_desc[pack].length);
		अगर (++shm->playback_iso_head >= ARRAY_SIZE(shm->captured_iso))
			shm->playback_iso_head = 0;
		count += counts;
	पूर्ण
	urb->transfer_buffer_length = count * usX2Y->stride;
	वापस 0;
पूर्ण


अटल अंतरभूत व्योम usX2Y_usbpcm_urb_capt_iso_advance(काष्ठा snd_usX2Y_substream *subs,
						     काष्ठा urb *urb)
अणु
	पूर्णांक pack;
	क्रम (pack = 0; pack < nr_of_packs(); ++pack) अणु
		काष्ठा usb_iso_packet_descriptor *desc = urb->iso_frame_desc + pack;
		अगर (शून्य != subs) अणु
			काष्ठा snd_usX2Y_hwdep_pcm_shm *shm = subs->usX2Y->hwdep_pcm_shm;
			पूर्णांक head = shm->captured_iso_head + 1;
			अगर (head >= ARRAY_SIZE(shm->captured_iso))
				head = 0;
			shm->captured_iso[head].frame = urb->start_frame + pack;
			shm->captured_iso[head].offset = desc->offset;
			shm->captured_iso[head].length = desc->actual_length;
			shm->captured_iso_head = head;
			shm->captured_iso_frames++;
		पूर्ण
		अगर ((desc->offset += desc->length * NRURBS*nr_of_packs()) +
		    desc->length >= SSS)
			desc->offset -= (SSS - desc->length);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक usX2Y_usbpcm_usbframe_complete(काष्ठा snd_usX2Y_substream *capsubs,
						 काष्ठा snd_usX2Y_substream *capsubs2,
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
		अगर ((err = usX2Y_hwdep_urb_play_prepare(playbacksubs, urb)) ||
		    (err = usX2Y_urb_submit(playbacksubs, urb, frame))) अणु
			वापस err;
		पूर्ण
	पूर्ण
	
	playbacksubs->completed_urb = शून्य;

	state = atomic_पढ़ो(&capsubs->state);
	अगर (state >= state_PREPARED) अणु
		अगर (state == state_RUNNING) अणु
			अगर ((err = usX2Y_usbpcm_urb_capt_retire(capsubs)))
				वापस err;
		पूर्ण अन्यथा अगर (state >= state_PRERUNNING)
			atomic_inc(&capsubs->state);
		usX2Y_usbpcm_urb_capt_iso_advance(capsubs, capsubs->completed_urb);
		अगर (शून्य != capsubs2)
			usX2Y_usbpcm_urb_capt_iso_advance(शून्य, capsubs2->completed_urb);
		अगर ((err = usX2Y_urb_submit(capsubs, capsubs->completed_urb, frame)))
			वापस err;
		अगर (शून्य != capsubs2)
			अगर ((err = usX2Y_urb_submit(capsubs2, capsubs2->completed_urb, frame)))
				वापस err;
	पूर्ण
	capsubs->completed_urb = शून्य;
	अगर (शून्य != capsubs2)
		capsubs2->completed_urb = शून्य;
	वापस 0;
पूर्ण


अटल व्योम i_usX2Y_usbpcm_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा snd_usX2Y_substream *subs = urb->context;
	काष्ठा usX2Ydev *usX2Y = subs->usX2Y;
	काष्ठा snd_usX2Y_substream *capsubs, *capsubs2, *playbacksubs;

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
	capsubs = usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE];
	capsubs2 = usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE + 2];
	playbacksubs = usX2Y->subs[SNDRV_PCM_STREAM_PLAYBACK];
	अगर (capsubs->completed_urb && atomic_पढ़ो(&capsubs->state) >= state_PREPARED &&
	    (शून्य == capsubs2 || capsubs2->completed_urb) &&
	    (playbacksubs->completed_urb || atomic_पढ़ो(&playbacksubs->state) < state_PREPARED)) अणु
		अगर (!usX2Y_usbpcm_usbframe_complete(capsubs, capsubs2, playbacksubs, urb->start_frame))
			usX2Y->रुको_iso_frame += nr_of_packs();
		अन्यथा अणु
			snd_prपूर्णांकdd("\n");
			usX2Y_clients_stop(usX2Y);
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम usX2Y_hwdep_urb_release(काष्ठा urb **urb)
अणु
	usb_समाप्त_urb(*urb);
	usb_मुक्त_urb(*urb);
	*urb = शून्य;
पूर्ण

/*
 * release a substream
 */
अटल व्योम usX2Y_usbpcm_urbs_release(काष्ठा snd_usX2Y_substream *subs)
अणु
	पूर्णांक i;
	snd_prपूर्णांकdd("snd_usX2Y_urbs_release() %i\n", subs->endpoपूर्णांक);
	क्रम (i = 0; i < NRURBS; i++)
		usX2Y_hwdep_urb_release(subs->urb + i);
पूर्ण

अटल व्योम usX2Y_usbpcm_subs_startup_finish(काष्ठा usX2Ydev * usX2Y)
अणु
	usX2Y_urbs_set_complete(usX2Y, i_usX2Y_usbpcm_urb_complete);
	usX2Y->prepare_subs = शून्य;
पूर्ण

अटल व्योम i_usX2Y_usbpcm_subs_startup(काष्ठा urb *urb)
अणु
	काष्ठा snd_usX2Y_substream *subs = urb->context;
	काष्ठा usX2Ydev *usX2Y = subs->usX2Y;
	काष्ठा snd_usX2Y_substream *prepare_subs = usX2Y->prepare_subs;
	अगर (शून्य != prepare_subs &&
	    urb->start_frame == prepare_subs->urb[0]->start_frame) अणु
		atomic_inc(&prepare_subs->state);
		अगर (prepare_subs == usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE]) अणु
			काष्ठा snd_usX2Y_substream *cap_subs2 = usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE + 2];
			अगर (cap_subs2 != शून्य)
				atomic_inc(&cap_subs2->state);
		पूर्ण
		usX2Y_usbpcm_subs_startup_finish(usX2Y);
		wake_up(&usX2Y->prepare_रुको_queue);
	पूर्ण

	i_usX2Y_usbpcm_urb_complete(urb);
पूर्ण

/*
 * initialize a substream's urbs
 */
अटल पूर्णांक usX2Y_usbpcm_urbs_allocate(काष्ठा snd_usX2Y_substream *subs)
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

	/* allocate and initialize data urbs */
	क्रम (i = 0; i < NRURBS; i++) अणु
		काष्ठा urb **purb = subs->urb + i;
		अगर (*purb) अणु
			usb_समाप्त_urb(*purb);
			जारी;
		पूर्ण
		*purb = usb_alloc_urb(nr_of_packs(), GFP_KERNEL);
		अगर (शून्य == *purb) अणु
			usX2Y_usbpcm_urbs_release(subs);
			वापस -ENOMEM;
		पूर्ण
		(*purb)->transfer_buffer = is_playback ?
			subs->usX2Y->hwdep_pcm_shm->playback : (
				subs->endpoपूर्णांक == 0x8 ?
				subs->usX2Y->hwdep_pcm_shm->capture0x8 :
				subs->usX2Y->hwdep_pcm_shm->capture0xA);

		(*purb)->dev = dev;
		(*purb)->pipe = pipe;
		(*purb)->number_of_packets = nr_of_packs();
		(*purb)->context = subs;
		(*purb)->पूर्णांकerval = 1;
		(*purb)->complete = i_usX2Y_usbpcm_subs_startup;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * मुक्त the buffer
 */
अटल पूर्णांक snd_usX2Y_usbpcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_usX2Y_substream *subs = runसमय->निजी_data,
		*cap_subs2 = subs->usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE + 2];
	mutex_lock(&subs->usX2Y->pcm_mutex);
	snd_prपूर्णांकdd("snd_usX2Y_usbpcm_hw_free(%p)\n", substream);

	अगर (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) अणु
		काष्ठा snd_usX2Y_substream *cap_subs = subs->usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE];
		atomic_set(&subs->state, state_STOPPED);
		usX2Y_usbpcm_urbs_release(subs);
		अगर (!cap_subs->pcm_substream ||
		    !cap_subs->pcm_substream->runसमय ||
		    !cap_subs->pcm_substream->runसमय->status ||
		    cap_subs->pcm_substream->runसमय->status->state < SNDRV_PCM_STATE_PREPARED) अणु
			atomic_set(&cap_subs->state, state_STOPPED);
			अगर (शून्य != cap_subs2)
				atomic_set(&cap_subs2->state, state_STOPPED);
			usX2Y_usbpcm_urbs_release(cap_subs);
			अगर (शून्य != cap_subs2)
				usX2Y_usbpcm_urbs_release(cap_subs2);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा snd_usX2Y_substream *playback_subs = subs->usX2Y->subs[SNDRV_PCM_STREAM_PLAYBACK];
		अगर (atomic_पढ़ो(&playback_subs->state) < state_PREPARED) अणु
			atomic_set(&subs->state, state_STOPPED);
			अगर (शून्य != cap_subs2)
				atomic_set(&cap_subs2->state, state_STOPPED);
			usX2Y_usbpcm_urbs_release(subs);
			अगर (शून्य != cap_subs2)
				usX2Y_usbpcm_urbs_release(cap_subs2);
		पूर्ण
	पूर्ण
	mutex_unlock(&subs->usX2Y->pcm_mutex);
	वापस 0;
पूर्ण

अटल व्योम usX2Y_usbpcm_subs_startup(काष्ठा snd_usX2Y_substream *subs)
अणु
	काष्ठा usX2Ydev * usX2Y = subs->usX2Y;
	usX2Y->prepare_subs = subs;
	subs->urb[0]->start_frame = -1;
	smp_wmb();	// Make sure above modअगरications are seen by i_usX2Y_subs_startup()
	usX2Y_urbs_set_complete(usX2Y, i_usX2Y_usbpcm_subs_startup);
पूर्ण

अटल पूर्णांक usX2Y_usbpcm_urbs_start(काष्ठा snd_usX2Y_substream *subs)
अणु
	पूर्णांक	p, u, err,
		stream = subs->pcm_substream->stream;
	काष्ठा usX2Ydev *usX2Y = subs->usX2Y;

	अगर (SNDRV_PCM_STREAM_CAPTURE == stream) अणु
		usX2Y->hwdep_pcm_shm->captured_iso_head = -1;
		usX2Y->hwdep_pcm_shm->captured_iso_frames = 0;
	पूर्ण

	क्रम (p = 0; 3 >= (stream + p); p += 2) अणु
		काष्ठा snd_usX2Y_substream *subs = usX2Y->subs[stream + p];
		अगर (subs != शून्य) अणु
			अगर ((err = usX2Y_usbpcm_urbs_allocate(subs)) < 0)
				वापस err;
			subs->completed_urb = शून्य;
		पूर्ण
	पूर्ण

	क्रम (p = 0; p < 4; p++) अणु
		काष्ठा snd_usX2Y_substream *subs = usX2Y->subs[p];
		अगर (subs != शून्य && atomic_पढ़ो(&subs->state) >= state_PREPARED)
			जाओ start;
	पूर्ण

 start:
	usX2Y_usbpcm_subs_startup(subs);
	क्रम (u = 0; u < NRURBS; u++) अणु
		क्रम (p = 0; 3 >= (stream + p); p += 2) अणु
			काष्ठा snd_usX2Y_substream *subs = usX2Y->subs[stream + p];
			अगर (subs != शून्य) अणु
				काष्ठा urb *urb = subs->urb[u];
				अगर (usb_pipein(urb->pipe)) अणु
					अचिन्हित दीर्घ pack;
					अगर (0 == u)
						atomic_set(&subs->state, state_STARTING3);
					urb->dev = usX2Y->dev;
					क्रम (pack = 0; pack < nr_of_packs(); pack++) अणु
						urb->iso_frame_desc[pack].offset = subs->maxpacksize * (pack + u * nr_of_packs());
						urb->iso_frame_desc[pack].length = subs->maxpacksize;
					पूर्ण
					urb->transfer_buffer_length = subs->maxpacksize * nr_of_packs(); 
					अगर ((err = usb_submit_urb(urb, GFP_KERNEL)) < 0) अणु
						snd_prपूर्णांकk (KERN_ERR "cannot usb_submit_urb() for urb %d, err = %d\n", u, err);
						err = -EPIPE;
						जाओ cleanup;
					पूर्ण  अन्यथा अणु
						snd_prपूर्णांकdd("%i\n", urb->start_frame);
						अगर (u == 0)
							usX2Y->रुको_iso_frame = urb->start_frame;
					पूर्ण
					urb->transfer_flags = 0;
				पूर्ण अन्यथा अणु
					atomic_set(&subs->state, state_STARTING1);
					अवरोध;
				पूर्ण			
			पूर्ण
		पूर्ण
	पूर्ण
	err = 0;
	रुको_event(usX2Y->prepare_रुको_queue, शून्य == usX2Y->prepare_subs);
	अगर (atomic_पढ़ो(&subs->state) != state_PREPARED)
		err = -EPIPE;
		
 cleanup:
	अगर (err) अणु
		usX2Y_subs_startup_finish(usX2Y);	// Call it now
		usX2Y_clients_stop(usX2Y);		// something is completely wroong > stop evrything			
	पूर्ण
	वापस err;
पूर्ण

/*
 * prepare callback
 *
 * set क्रमmat and initialize urbs
 */
अटल पूर्णांक snd_usX2Y_usbpcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_usX2Y_substream *subs = runसमय->निजी_data;
	काष्ठा usX2Ydev *usX2Y = subs->usX2Y;
	काष्ठा snd_usX2Y_substream *capsubs = subs->usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE];
	पूर्णांक err = 0;
	snd_prपूर्णांकdd("snd_usX2Y_pcm_prepare(%p)\n", substream);

	अगर (शून्य == usX2Y->hwdep_pcm_shm) अणु
		usX2Y->hwdep_pcm_shm = alloc_pages_exact(माप(काष्ठा snd_usX2Y_hwdep_pcm_shm),
							 GFP_KERNEL);
		अगर (!usX2Y->hwdep_pcm_shm)
			वापस -ENOMEM;
		स_रखो(usX2Y->hwdep_pcm_shm, 0, माप(काष्ठा snd_usX2Y_hwdep_pcm_shm));
	पूर्ण

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
		snd_prपूर्णांकdd("starting capture pipe for %s\n", subs == capsubs ?
			    "self" : "playpipe");
		अगर (0 > (err = usX2Y_usbpcm_urbs_start(capsubs)))
			जाओ up_prepare_mutex;
	पूर्ण

	अगर (subs != capsubs) अणु
		usX2Y->hwdep_pcm_shm->playback_iso_start = -1;
		अगर (atomic_पढ़ो(&subs->state) < state_PREPARED) अणु
			जबतक (usX2Y_iso_frames_per_buffer(runसमय, usX2Y) >
			       usX2Y->hwdep_pcm_shm->captured_iso_frames) अणु
				snd_prपूर्णांकdd("Wait: iso_frames_per_buffer=%i,"
					    "captured_iso_frames=%i\n",
					    usX2Y_iso_frames_per_buffer(runसमय, usX2Y),
					    usX2Y->hwdep_pcm_shm->captured_iso_frames);
				अगर (msleep_पूर्णांकerruptible(10)) अणु
					err = -ERESTARTSYS;
					जाओ up_prepare_mutex;
				पूर्ण
			पूर्ण 
			अगर (0 > (err = usX2Y_usbpcm_urbs_start(subs)))
				जाओ up_prepare_mutex;
		पूर्ण
		snd_prपूर्णांकdd("Ready: iso_frames_per_buffer=%i,captured_iso_frames=%i\n",
			    usX2Y_iso_frames_per_buffer(runसमय, usX2Y),
			    usX2Y->hwdep_pcm_shm->captured_iso_frames);
	पूर्ण अन्यथा
		usX2Y->hwdep_pcm_shm->capture_iso_start = -1;

 up_prepare_mutex:
	mutex_unlock(&usX2Y->pcm_mutex);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_usX2Y_4c =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =                 SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_3LE,
	.rates =                   SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000,
	.rate_min =                44100,
	.rate_max =                48000,
	.channels_min =            2,
	.channels_max =            4,
	.buffer_bytes_max =	(2*128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		1024,
	.fअगरo_size =              0
पूर्ण;



अटल पूर्णांक snd_usX2Y_usbpcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_usX2Y_substream	*subs = ((काष्ठा snd_usX2Y_substream **)
					 snd_pcm_substream_chip(substream))[substream->stream];
	काष्ठा snd_pcm_runसमय	*runसमय = substream->runसमय;

	अगर (!(subs->usX2Y->chip_status & USX2Y_STAT_CHIP_MMAP_PCM_URBS))
		वापस -EBUSY;

	runसमय->hw = SNDRV_PCM_STREAM_PLAYBACK == substream->stream ? snd_usX2Y_2c :
		(subs->usX2Y->subs[3] ? snd_usX2Y_4c : snd_usX2Y_2c);
	runसमय->निजी_data = subs;
	subs->pcm_substream = substream;
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_PERIOD_TIME, 1000, 200000);
	वापस 0;
पूर्ण


अटल पूर्णांक snd_usX2Y_usbpcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_usX2Y_substream *subs = runसमय->निजी_data;

	subs->pcm_substream = शून्य;
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा snd_pcm_ops snd_usX2Y_usbpcm_ops =
अणु
	.खोलो =		snd_usX2Y_usbpcm_खोलो,
	.बंद =	snd_usX2Y_usbpcm_बंद,
	.hw_params =	snd_usX2Y_pcm_hw_params,
	.hw_मुक्त =	snd_usX2Y_usbpcm_hw_मुक्त,
	.prepare =	snd_usX2Y_usbpcm_prepare,
	.trigger =	snd_usX2Y_pcm_trigger,
	.poपूर्णांकer =	snd_usX2Y_pcm_poपूर्णांकer,
पूर्ण;


अटल पूर्णांक usX2Y_pcms_busy_check(काष्ठा snd_card *card)
अणु
	काष्ठा usX2Ydev	*dev = usX2Y(card);
	पूर्णांक i;

	क्रम (i = 0; i < dev->pcm_devs * 2; i++) अणु
		काष्ठा snd_usX2Y_substream *subs = dev->subs[i];
		अगर (subs && subs->pcm_substream &&
		    SUBSTREAM_BUSY(subs->pcm_substream))
			वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_usX2Y_hwdep_pcm_खोलो(काष्ठा snd_hwdep *hw, काष्ठा file *file)
अणु
	काष्ठा snd_card *card = hw->card;
	पूर्णांक err;

	mutex_lock(&usX2Y(card)->pcm_mutex);
	err = usX2Y_pcms_busy_check(card);
	अगर (!err)
		usX2Y(card)->chip_status |= USX2Y_STAT_CHIP_MMAP_PCM_URBS;
	mutex_unlock(&usX2Y(card)->pcm_mutex);
	वापस err;
पूर्ण


अटल पूर्णांक snd_usX2Y_hwdep_pcm_release(काष्ठा snd_hwdep *hw, काष्ठा file *file)
अणु
	काष्ठा snd_card *card = hw->card;
	पूर्णांक err;

	mutex_lock(&usX2Y(card)->pcm_mutex);
	err = usX2Y_pcms_busy_check(card);
	अगर (!err)
		usX2Y(hw->card)->chip_status &= ~USX2Y_STAT_CHIP_MMAP_PCM_URBS;
	mutex_unlock(&usX2Y(card)->pcm_mutex);
	वापस err;
पूर्ण


अटल व्योम snd_usX2Y_hwdep_pcm_vm_खोलो(काष्ठा vm_area_काष्ठा *area)
अणु
पूर्ण


अटल व्योम snd_usX2Y_hwdep_pcm_vm_बंद(काष्ठा vm_area_काष्ठा *area)
अणु
पूर्ण


अटल vm_fault_t snd_usX2Y_hwdep_pcm_vm_fault(काष्ठा vm_fault *vmf)
अणु
	अचिन्हित दीर्घ offset;
	व्योम *vaddr;

	offset = vmf->pgoff << PAGE_SHIFT;
	vaddr = (अक्षर *)((काष्ठा usX2Ydev *)vmf->vma->vm_निजी_data)->hwdep_pcm_shm + offset;
	vmf->page = virt_to_page(vaddr);
	get_page(vmf->page);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा vm_operations_काष्ठा snd_usX2Y_hwdep_pcm_vm_ops = अणु
	.खोलो = snd_usX2Y_hwdep_pcm_vm_खोलो,
	.बंद = snd_usX2Y_hwdep_pcm_vm_बंद,
	.fault = snd_usX2Y_hwdep_pcm_vm_fault,
पूर्ण;


अटल पूर्णांक snd_usX2Y_hwdep_pcm_mmap(काष्ठा snd_hwdep * hw, काष्ठा file *filp, काष्ठा vm_area_काष्ठा *area)
अणु
	अचिन्हित दीर्घ	size = (अचिन्हित दीर्घ)(area->vm_end - area->vm_start);
	काष्ठा usX2Ydev	*usX2Y = hw->निजी_data;

	अगर (!(usX2Y->chip_status & USX2Y_STAT_CHIP_INIT))
		वापस -EBUSY;

	/* अगर userspace tries to mmap beyond end of our buffer, fail */ 
	अगर (size > PAGE_ALIGN(माप(काष्ठा snd_usX2Y_hwdep_pcm_shm))) अणु
		snd_prपूर्णांकd("%lu > %lu\n", size, (अचिन्हित दीर्घ)माप(काष्ठा snd_usX2Y_hwdep_pcm_shm)); 
		वापस -EINVAL;
	पूर्ण

	अगर (!usX2Y->hwdep_pcm_shm) अणु
		वापस -ENODEV;
	पूर्ण
	area->vm_ops = &snd_usX2Y_hwdep_pcm_vm_ops;
	area->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	area->vm_निजी_data = hw->निजी_data;
	वापस 0;
पूर्ण


अटल व्योम snd_usX2Y_hwdep_pcm_निजी_मुक्त(काष्ठा snd_hwdep *hwdep)
अणु
	काष्ठा usX2Ydev *usX2Y = hwdep->निजी_data;
	अगर (शून्य != usX2Y->hwdep_pcm_shm)
		मुक्त_pages_exact(usX2Y->hwdep_pcm_shm, माप(काष्ठा snd_usX2Y_hwdep_pcm_shm));
पूर्ण


पूर्णांक usX2Y_hwdep_pcm_new(काष्ठा snd_card *card)
अणु
	पूर्णांक err;
	काष्ठा snd_hwdep *hw;
	काष्ठा snd_pcm *pcm;
	काष्ठा usb_device *dev = usX2Y(card)->dev;
	अगर (1 != nr_of_packs())
		वापस 0;

	अगर ((err = snd_hwdep_new(card, SND_USX2Y_USBPCM_ID, 1, &hw)) < 0)
		वापस err;

	hw->अगरace = SNDRV_HWDEP_IFACE_USX2Y_PCM;
	hw->निजी_data = usX2Y(card);
	hw->निजी_मुक्त = snd_usX2Y_hwdep_pcm_निजी_मुक्त;
	hw->ops.खोलो = snd_usX2Y_hwdep_pcm_खोलो;
	hw->ops.release = snd_usX2Y_hwdep_pcm_release;
	hw->ops.mmap = snd_usX2Y_hwdep_pcm_mmap;
	hw->exclusive = 1;
	प्र_लिखो(hw->name, "/dev/bus/usb/%03d/%03d/hwdeppcm", dev->bus->busnum, dev->devnum);

	err = snd_pcm_new(card, NAME_ALLCAPS" hwdep Audio", 2, 1, 1, &pcm);
	अगर (err < 0) अणु
		वापस err;
	पूर्ण
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_usX2Y_usbpcm_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_usX2Y_usbpcm_ops);

	pcm->निजी_data = usX2Y(card)->subs;
	pcm->info_flags = 0;

	प्र_लिखो(pcm->name, NAME_ALLCAPS" hwdep Audio");
	snd_pcm_set_managed_buffer(pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream,
				   SNDRV_DMA_TYPE_CONTINUOUS,
				   शून्य,
				   64*1024, 128*1024);
	snd_pcm_set_managed_buffer(pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream,
				   SNDRV_DMA_TYPE_CONTINUOUS,
				   शून्य,
				   64*1024, 128*1024);

	वापस 0;
पूर्ण

#अन्यथा

पूर्णांक usX2Y_hwdep_pcm_new(काष्ठा snd_card *card)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर
