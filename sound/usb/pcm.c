<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/audio-v2.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "usbaudio.h"
#समावेश "card.h"
#समावेश "quirks.h"
#समावेश "endpoint.h"
#समावेश "helper.h"
#समावेश "pcm.h"
#समावेश "clock.h"
#समावेश "power.h"
#समावेश "media.h"
#समावेश "implicit.h"

#घोषणा SUBSTREAM_FLAG_DATA_EP_STARTED	0
#घोषणा SUBSTREAM_FLAG_SYNC_EP_STARTED	1

/* वापस the estimated delay based on USB frame counters */
snd_pcm_uframes_t snd_usb_pcm_delay(काष्ठा snd_usb_substream *subs,
				    अचिन्हित पूर्णांक rate)
अणु
	पूर्णांक current_frame_number;
	पूर्णांक frame_dअगरf;
	पूर्णांक est_delay;

	अगर (!subs->last_delay)
		वापस 0; /* लघु path */

	current_frame_number = usb_get_current_frame_number(subs->dev);
	/*
	 * HCD implementations use dअगरferent widths, use lower 8 bits.
	 * The delay will be managed up to 256ms, which is more than
	 * enough
	 */
	frame_dअगरf = (current_frame_number - subs->last_frame_number) & 0xff;

	/* Approximation based on number of samples per USB frame (ms),
	   some truncation क्रम 44.1 but the estimate is good enough */
	est_delay =  frame_dअगरf * rate / 1000;
	अगर (subs->direction == SNDRV_PCM_STREAM_PLAYBACK)
		est_delay = subs->last_delay - est_delay;
	अन्यथा
		est_delay = subs->last_delay + est_delay;

	अगर (est_delay < 0)
		est_delay = 0;
	वापस est_delay;
पूर्ण

/*
 * वापस the current pcm poपूर्णांकer.  just based on the hwptr_करोne value.
 */
अटल snd_pcm_uframes_t snd_usb_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_usb_substream *subs = substream->runसमय->निजी_data;
	अचिन्हित पूर्णांक hwptr_करोne;

	अगर (atomic_पढ़ो(&subs->stream->chip->shutकरोwn))
		वापस SNDRV_PCM_POS_XRUN;
	spin_lock(&subs->lock);
	hwptr_करोne = subs->hwptr_करोne;
	substream->runसमय->delay = snd_usb_pcm_delay(subs,
						substream->runसमय->rate);
	spin_unlock(&subs->lock);
	वापस hwptr_करोne / (substream->runसमय->frame_bits >> 3);
पूर्ण

/*
 * find a matching audio क्रमmat
 */
अटल स्थिर काष्ठा audioक्रमmat *
find_क्रमmat(काष्ठा list_head *fmt_list_head, snd_pcm_क्रमmat_t क्रमmat,
	    अचिन्हित पूर्णांक rate, अचिन्हित पूर्णांक channels, bool strict_match,
	    काष्ठा snd_usb_substream *subs)
अणु
	स्थिर काष्ठा audioक्रमmat *fp;
	स्थिर काष्ठा audioक्रमmat *found = शून्य;
	पूर्णांक cur_attr = 0, attr;

	list_क्रम_each_entry(fp, fmt_list_head, list) अणु
		अगर (strict_match) अणु
			अगर (!(fp->क्रमmats & pcm_क्रमmat_to_bits(क्रमmat)))
				जारी;
			अगर (fp->channels != channels)
				जारी;
		पूर्ण
		अगर (rate < fp->rate_min || rate > fp->rate_max)
			जारी;
		अगर (!(fp->rates & SNDRV_PCM_RATE_CONTINUOUS)) अणु
			अचिन्हित पूर्णांक i;
			क्रम (i = 0; i < fp->nr_rates; i++)
				अगर (fp->rate_table[i] == rate)
					अवरोध;
			अगर (i >= fp->nr_rates)
				जारी;
		पूर्ण
		attr = fp->ep_attr & USB_ENDPOINT_SYNCTYPE;
		अगर (!found) अणु
			found = fp;
			cur_attr = attr;
			जारी;
		पूर्ण
		/* aव्योम async out and adaptive in अगर the other method
		 * supports the same क्रमmat.
		 * this is a workaround क्रम the हाल like
		 * M-audio audiophile USB.
		 */
		अगर (subs && attr != cur_attr) अणु
			अगर ((attr == USB_ENDPOINT_SYNC_ASYNC &&
			     subs->direction == SNDRV_PCM_STREAM_PLAYBACK) ||
			    (attr == USB_ENDPOINT_SYNC_ADAPTIVE &&
			     subs->direction == SNDRV_PCM_STREAM_CAPTURE))
				जारी;
			अगर ((cur_attr == USB_ENDPOINT_SYNC_ASYNC &&
			     subs->direction == SNDRV_PCM_STREAM_PLAYBACK) ||
			    (cur_attr == USB_ENDPOINT_SYNC_ADAPTIVE &&
			     subs->direction == SNDRV_PCM_STREAM_CAPTURE)) अणु
				found = fp;
				cur_attr = attr;
				जारी;
			पूर्ण
		पूर्ण
		/* find the क्रमmat with the largest max. packet size */
		अगर (fp->maxpacksize > found->maxpacksize) अणु
			found = fp;
			cur_attr = attr;
		पूर्ण
	पूर्ण
	वापस found;
पूर्ण

अटल स्थिर काष्ठा audioक्रमmat *
find_substream_क्रमmat(काष्ठा snd_usb_substream *subs,
		      स्थिर काष्ठा snd_pcm_hw_params *params)
अणु
	वापस find_क्रमmat(&subs->fmt_list, params_क्रमmat(params),
			   params_rate(params), params_channels(params),
			   true, subs);
पूर्ण

अटल पूर्णांक init_pitch_v1(काष्ठा snd_usb_audio *chip, पूर्णांक ep)
अणु
	काष्ठा usb_device *dev = chip->dev;
	अचिन्हित अक्षर data[1];
	पूर्णांक err;

	data[0] = 1;
	err = snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), UAC_SET_CUR,
			      USB_TYPE_CLASS|USB_RECIP_ENDPOINT|USB_सूची_OUT,
			      UAC_EP_CS_ATTR_PITCH_CONTROL << 8, ep,
			      data, माप(data));
	वापस err;
पूर्ण

अटल पूर्णांक init_pitch_v2(काष्ठा snd_usb_audio *chip, पूर्णांक ep)
अणु
	काष्ठा usb_device *dev = chip->dev;
	अचिन्हित अक्षर data[1];
	पूर्णांक err;

	data[0] = 1;
	err = snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), UAC2_CS_CUR,
			      USB_TYPE_CLASS | USB_RECIP_ENDPOINT | USB_सूची_OUT,
			      UAC2_EP_CS_PITCH << 8, 0,
			      data, माप(data));
	वापस err;
पूर्ण

/*
 * initialize the pitch control and sample rate
 */
पूर्णांक snd_usb_init_pitch(काष्ठा snd_usb_audio *chip,
		       स्थिर काष्ठा audioक्रमmat *fmt)
अणु
	पूर्णांक err;

	/* अगर endpoपूर्णांक करोesn't have pitch control, bail out */
	अगर (!(fmt->attributes & UAC_EP_CS_ATTR_PITCH_CONTROL))
		वापस 0;

	usb_audio_dbg(chip, "enable PITCH for EP 0x%x\n", fmt->endpoपूर्णांक);

	चयन (fmt->protocol) अणु
	हाल UAC_VERSION_1:
		err = init_pitch_v1(chip, fmt->endpoपूर्णांक);
		अवरोध;
	हाल UAC_VERSION_2:
		err = init_pitch_v2(chip, fmt->endpoपूर्णांक);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (err < 0) अणु
		usb_audio_err(chip, "failed to enable PITCH for EP 0x%x\n",
			      fmt->endpoपूर्णांक);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool stop_endpoपूर्णांकs(काष्ठा snd_usb_substream *subs)
अणु
	bool stopped = 0;

	अगर (test_and_clear_bit(SUBSTREAM_FLAG_SYNC_EP_STARTED, &subs->flags)) अणु
		snd_usb_endpoपूर्णांक_stop(subs->sync_endpoपूर्णांक);
		stopped = true;
	पूर्ण
	अगर (test_and_clear_bit(SUBSTREAM_FLAG_DATA_EP_STARTED, &subs->flags)) अणु
		snd_usb_endpoपूर्णांक_stop(subs->data_endpoपूर्णांक);
		stopped = true;
	पूर्ण
	वापस stopped;
पूर्ण

अटल पूर्णांक start_endpoपूर्णांकs(काष्ठा snd_usb_substream *subs)
अणु
	पूर्णांक err;

	अगर (!subs->data_endpoपूर्णांक)
		वापस -EINVAL;

	अगर (!test_and_set_bit(SUBSTREAM_FLAG_DATA_EP_STARTED, &subs->flags)) अणु
		err = snd_usb_endpoपूर्णांक_start(subs->data_endpoपूर्णांक);
		अगर (err < 0) अणु
			clear_bit(SUBSTREAM_FLAG_DATA_EP_STARTED, &subs->flags);
			जाओ error;
		पूर्ण
	पूर्ण

	अगर (subs->sync_endpoपूर्णांक &&
	    !test_and_set_bit(SUBSTREAM_FLAG_SYNC_EP_STARTED, &subs->flags)) अणु
		err = snd_usb_endpoपूर्णांक_start(subs->sync_endpoपूर्णांक);
		अगर (err < 0) अणु
			clear_bit(SUBSTREAM_FLAG_SYNC_EP_STARTED, &subs->flags);
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;

 error:
	stop_endpoपूर्णांकs(subs);
	वापस err;
पूर्ण

अटल व्योम sync_pending_stops(काष्ठा snd_usb_substream *subs)
अणु
	snd_usb_endpoपूर्णांक_sync_pending_stop(subs->sync_endpoपूर्णांक);
	snd_usb_endpoपूर्णांक_sync_pending_stop(subs->data_endpoपूर्णांक);
पूर्ण

/* PCM sync_stop callback */
अटल पूर्णांक snd_usb_pcm_sync_stop(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_usb_substream *subs = substream->runसमय->निजी_data;

	sync_pending_stops(subs);
	वापस 0;
पूर्ण

/* Set up sync endpoपूर्णांक */
पूर्णांक snd_usb_audioक्रमmat_set_sync_ep(काष्ठा snd_usb_audio *chip,
				    काष्ठा audioक्रमmat *fmt)
अणु
	काष्ठा usb_device *dev = chip->dev;
	काष्ठा usb_host_पूर्णांकerface *alts;
	काष्ठा usb_पूर्णांकerface_descriptor *altsd;
	अचिन्हित पूर्णांक ep, attr, sync_attr;
	bool is_playback;
	पूर्णांक err;

	alts = snd_usb_get_host_पूर्णांकerface(chip, fmt->अगरace, fmt->altsetting);
	अगर (!alts)
		वापस 0;
	altsd = get_अगरace_desc(alts);

	err = snd_usb_parse_implicit_fb_quirk(chip, fmt, alts);
	अगर (err > 0)
		वापस 0; /* matched */

	/*
	 * Generic sync EP handling
	 */

	अगर (altsd->bNumEndpoपूर्णांकs < 2)
		वापस 0;

	is_playback = !(get_endpoपूर्णांक(alts, 0)->bEndpoपूर्णांकAddress & USB_सूची_IN);
	attr = fmt->ep_attr & USB_ENDPOINT_SYNCTYPE;
	अगर ((is_playback && (attr == USB_ENDPOINT_SYNC_SYNC ||
			     attr == USB_ENDPOINT_SYNC_ADAPTIVE)) ||
	    (!is_playback && attr != USB_ENDPOINT_SYNC_ADAPTIVE))
		वापस 0;

	sync_attr = get_endpoपूर्णांक(alts, 1)->bmAttributes;

	/*
	 * In हाल of illegal SYNC_NONE क्रम OUT endpoपूर्णांक, we keep going to see
	 * अगर we करोn't find a sync endpoपूर्णांक, as on M-Audio Transit. In हाल of
	 * error fall back to SYNC mode and करोn't create sync endpoपूर्णांक
	 */

	/* check sync-pipe endpoपूर्णांक */
	/* ... and check descriptor size beक्रमe accessing bSynchAddress
	   because there is a version of the SB Audigy 2 NX firmware lacking
	   the audio fields in the endpoपूर्णांक descriptors */
	अगर ((sync_attr & USB_ENDPOINT_XFERTYPE_MASK) != USB_ENDPOINT_XFER_ISOC ||
	    (get_endpoपूर्णांक(alts, 1)->bLength >= USB_DT_ENDPOINT_AUDIO_SIZE &&
	     get_endpoपूर्णांक(alts, 1)->bSynchAddress != 0)) अणु
		dev_err(&dev->dev,
			"%d:%d : invalid sync pipe. bmAttributes %02x, bLength %d, bSynchAddress %02x\n",
			   fmt->अगरace, fmt->altsetting,
			   get_endpoपूर्णांक(alts, 1)->bmAttributes,
			   get_endpoपूर्णांक(alts, 1)->bLength,
			   get_endpoपूर्णांक(alts, 1)->bSynchAddress);
		अगर (is_playback && attr == USB_ENDPOINT_SYNC_NONE)
			वापस 0;
		वापस -EINVAL;
	पूर्ण
	ep = get_endpoपूर्णांक(alts, 1)->bEndpoपूर्णांकAddress;
	अगर (get_endpoपूर्णांक(alts, 0)->bLength >= USB_DT_ENDPOINT_AUDIO_SIZE &&
	    get_endpoपूर्णांक(alts, 0)->bSynchAddress != 0 &&
	    ((is_playback && ep != (अचिन्हित पूर्णांक)(get_endpoपूर्णांक(alts, 0)->bSynchAddress | USB_सूची_IN)) ||
	     (!is_playback && ep != (अचिन्हित पूर्णांक)(get_endpoपूर्णांक(alts, 0)->bSynchAddress & ~USB_सूची_IN)))) अणु
		dev_err(&dev->dev,
			"%d:%d : invalid sync pipe. is_playback %d, ep %02x, bSynchAddress %02x\n",
			   fmt->अगरace, fmt->altsetting,
			   is_playback, ep, get_endpoपूर्णांक(alts, 0)->bSynchAddress);
		अगर (is_playback && attr == USB_ENDPOINT_SYNC_NONE)
			वापस 0;
		वापस -EINVAL;
	पूर्ण

	fmt->sync_ep = ep;
	fmt->sync_अगरace = altsd->bInterfaceNumber;
	fmt->sync_altsetting = altsd->bAlternateSetting;
	fmt->sync_ep_idx = 1;
	अगर ((sync_attr & USB_ENDPOINT_USAGE_MASK) == USB_ENDPOINT_USAGE_IMPLICIT_FB)
		fmt->implicit_fb = 1;

	dev_dbg(&dev->dev, "%d:%d: found sync_ep=0x%x, iface=%d, alt=%d, implicit_fb=%d\n",
		fmt->अगरace, fmt->altsetting, fmt->sync_ep, fmt->sync_अगरace,
		fmt->sync_altsetting, fmt->implicit_fb);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_usb_pcm_change_state(काष्ठा snd_usb_substream *subs, पूर्णांक state)
अणु
	पूर्णांक ret;

	अगर (!subs->str_pd)
		वापस 0;

	ret = snd_usb_घातer_करोमुख्य_set(subs->stream->chip, subs->str_pd, state);
	अगर (ret < 0) अणु
		dev_err(&subs->dev->dev,
			"Cannot change Power Domain ID: %d to state: %d. Err: %d\n",
			subs->str_pd->pd_id, state, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_usb_pcm_suspend(काष्ठा snd_usb_stream *as)
अणु
	पूर्णांक ret;

	ret = snd_usb_pcm_change_state(&as->substream[0], UAC3_PD_STATE_D2);
	अगर (ret < 0)
		वापस ret;

	ret = snd_usb_pcm_change_state(&as->substream[1], UAC3_PD_STATE_D2);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक snd_usb_pcm_resume(काष्ठा snd_usb_stream *as)
अणु
	पूर्णांक ret;

	ret = snd_usb_pcm_change_state(&as->substream[0], UAC3_PD_STATE_D1);
	अगर (ret < 0)
		वापस ret;

	ret = snd_usb_pcm_change_state(&as->substream[1], UAC3_PD_STATE_D1);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम बंद_endpoपूर्णांकs(काष्ठा snd_usb_audio *chip,
			    काष्ठा snd_usb_substream *subs)
अणु
	अगर (subs->data_endpoपूर्णांक) अणु
		snd_usb_endpoपूर्णांक_set_sync(chip, subs->data_endpoपूर्णांक, शून्य);
		snd_usb_endpoपूर्णांक_बंद(chip, subs->data_endpoपूर्णांक);
		subs->data_endpoपूर्णांक = शून्य;
	पूर्ण

	अगर (subs->sync_endpoपूर्णांक) अणु
		snd_usb_endpoपूर्णांक_बंद(chip, subs->sync_endpoपूर्णांक);
		subs->sync_endpoपूर्णांक = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक configure_endpoपूर्णांकs(काष्ठा snd_usb_audio *chip,
			       काष्ठा snd_usb_substream *subs)
अणु
	पूर्णांक err;

	अगर (subs->data_endpoपूर्णांक->need_setup) अणु
		/* stop any running stream beक्रमehand */
		अगर (stop_endpoपूर्णांकs(subs))
			sync_pending_stops(subs);
		err = snd_usb_endpoपूर्णांक_configure(chip, subs->data_endpoपूर्णांक);
		अगर (err < 0)
			वापस err;
		snd_usb_set_क्रमmat_quirk(subs, subs->cur_audiofmt);
	पूर्ण

	अगर (subs->sync_endpoपूर्णांक) अणु
		err = snd_usb_endpoपूर्णांक_configure(chip, subs->sync_endpoपूर्णांक);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * hw_params callback
 *
 * allocate a buffer and set the given audio क्रमmat.
 *
 * so far we use a physically linear buffer although packetize transfer
 * करोesn't need a continuous area.
 * अगर sg buffer is supported on the later version of alsa, we'll follow
 * that.
 */
अटल पूर्णांक snd_usb_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_usb_substream *subs = substream->runसमय->निजी_data;
	काष्ठा snd_usb_audio *chip = subs->stream->chip;
	स्थिर काष्ठा audioक्रमmat *fmt;
	स्थिर काष्ठा audioक्रमmat *sync_fmt;
	पूर्णांक ret;

	ret = snd_media_start_pipeline(subs);
	अगर (ret)
		वापस ret;

	fmt = find_substream_क्रमmat(subs, hw_params);
	अगर (!fmt) अणु
		usb_audio_dbg(chip,
			      "cannot find format: format=%s, rate=%d, channels=%d\n",
			      snd_pcm_क्रमmat_name(params_क्रमmat(hw_params)),
			      params_rate(hw_params), params_channels(hw_params));
		ret = -EINVAL;
		जाओ stop_pipeline;
	पूर्ण

	अगर (fmt->implicit_fb) अणु
		sync_fmt = snd_usb_find_implicit_fb_sync_क्रमmat(chip, fmt,
								hw_params,
								!substream->stream);
		अगर (!sync_fmt) अणु
			usb_audio_dbg(chip,
				      "cannot find sync format: ep=0x%x, iface=%d:%d, format=%s, rate=%d, channels=%d\n",
				      fmt->sync_ep, fmt->sync_अगरace,
				      fmt->sync_altsetting,
				      snd_pcm_क्रमmat_name(params_क्रमmat(hw_params)),
				      params_rate(hw_params), params_channels(hw_params));
			ret = -EINVAL;
			जाओ stop_pipeline;
		पूर्ण
	पूर्ण अन्यथा अणु
		sync_fmt = fmt;
	पूर्ण

	ret = snd_usb_lock_shutकरोwn(chip);
	अगर (ret < 0)
		जाओ stop_pipeline;

	ret = snd_usb_pcm_change_state(subs, UAC3_PD_STATE_D0);
	अगर (ret < 0)
		जाओ unlock;

	अगर (subs->data_endpoपूर्णांक) अणु
		अगर (snd_usb_endpoपूर्णांक_compatible(chip, subs->data_endpoपूर्णांक,
						fmt, hw_params))
			जाओ unlock;
		बंद_endpoपूर्णांकs(chip, subs);
	पूर्ण

	subs->data_endpoपूर्णांक = snd_usb_endpoपूर्णांक_खोलो(chip, fmt, hw_params, false);
	अगर (!subs->data_endpoपूर्णांक) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	अगर (fmt->sync_ep) अणु
		subs->sync_endpoपूर्णांक = snd_usb_endpoपूर्णांक_खोलो(chip, sync_fmt,
							    hw_params,
							    fmt == sync_fmt);
		अगर (!subs->sync_endpoपूर्णांक) अणु
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण

		snd_usb_endpoपूर्णांक_set_sync(chip, subs->data_endpoपूर्णांक,
					  subs->sync_endpoपूर्णांक);
	पूर्ण

	mutex_lock(&chip->mutex);
	subs->cur_audiofmt = fmt;
	mutex_unlock(&chip->mutex);

	ret = configure_endpoपूर्णांकs(chip, subs);

 unlock:
	अगर (ret < 0)
		बंद_endpoपूर्णांकs(chip, subs);

	snd_usb_unlock_shutकरोwn(chip);
 stop_pipeline:
	अगर (ret < 0)
		snd_media_stop_pipeline(subs);

	वापस ret;
पूर्ण

/*
 * hw_मुक्त callback
 *
 * reset the audio क्रमmat and release the buffer
 */
अटल पूर्णांक snd_usb_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_usb_substream *subs = substream->runसमय->निजी_data;
	काष्ठा snd_usb_audio *chip = subs->stream->chip;

	snd_media_stop_pipeline(subs);
	mutex_lock(&chip->mutex);
	subs->cur_audiofmt = शून्य;
	mutex_unlock(&chip->mutex);
	अगर (!snd_usb_lock_shutकरोwn(chip)) अणु
		अगर (stop_endpoपूर्णांकs(subs))
			sync_pending_stops(subs);
		बंद_endpoपूर्णांकs(chip, subs);
		snd_usb_unlock_shutकरोwn(chip);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * prepare callback
 *
 * only a few subtle things...
 */
अटल पूर्णांक snd_usb_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_usb_substream *subs = runसमय->निजी_data;
	काष्ठा snd_usb_audio *chip = subs->stream->chip;
	पूर्णांक ret;

	ret = snd_usb_lock_shutकरोwn(chip);
	अगर (ret < 0)
		वापस ret;
	अगर (snd_BUG_ON(!subs->data_endpoपूर्णांक)) अणु
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	ret = configure_endpoपूर्णांकs(chip, subs);
	अगर (ret < 0)
		जाओ unlock;

	/* reset the poपूर्णांकer */
	subs->hwptr_करोne = 0;
	subs->transfer_करोne = 0;
	subs->last_delay = 0;
	subs->last_frame_number = 0;
	runसमय->delay = 0;

	/* क्रम playback, submit the URBs now; otherwise, the first hwptr_करोne
	 * updates क्रम all URBs would happen at the same समय when starting */
	अगर (subs->direction == SNDRV_PCM_STREAM_PLAYBACK)
		ret = start_endpoपूर्णांकs(subs);

 unlock:
	snd_usb_unlock_shutकरोwn(chip);
	वापस ret;
पूर्ण

/*
 * h/w स्थिरraपूर्णांकs
 */

#अगर_घोषित HW_CONST_DEBUG
#घोषणा hwc_debug(fmt, args...) pr_debug(fmt, ##args)
#अन्यथा
#घोषणा hwc_debug(fmt, args...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_pcm_hardware snd_usb_hardware =
अणु
	.info =			SNDRV_PCM_INFO_MMAP |
				SNDRV_PCM_INFO_MMAP_VALID |
				SNDRV_PCM_INFO_BATCH |
				SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_BLOCK_TRANSFER |
				SNDRV_PCM_INFO_PAUSE,
	.channels_min =		1,
	.channels_max =		256,
	.buffer_bytes_max =	1024 * 1024,
	.period_bytes_min =	64,
	.period_bytes_max =	512 * 1024,
	.periods_min =		2,
	.periods_max =		1024,
पूर्ण;

अटल पूर्णांक hw_check_valid_क्रमmat(काष्ठा snd_usb_substream *subs,
				 काष्ठा snd_pcm_hw_params *params,
				 स्थिर काष्ठा audioक्रमmat *fp)
अणु
	काष्ठा snd_पूर्णांकerval *it = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *ct = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *fmts = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_पूर्णांकerval *pt = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_PERIOD_TIME);
	काष्ठा snd_mask check_fmts;
	अचिन्हित पूर्णांक pसमय;

	/* check the क्रमmat */
	snd_mask_none(&check_fmts);
	check_fmts.bits[0] = (u32)fp->क्रमmats;
	check_fmts.bits[1] = (u32)(fp->क्रमmats >> 32);
	snd_mask_पूर्णांकersect(&check_fmts, fmts);
	अगर (snd_mask_empty(&check_fmts)) अणु
		hwc_debug("   > check: no supported format 0x%llx\n", fp->क्रमmats);
		वापस 0;
	पूर्ण
	/* check the channels */
	अगर (fp->channels < ct->min || fp->channels > ct->max) अणु
		hwc_debug("   > check: no valid channels %d (%d/%d)\n", fp->channels, ct->min, ct->max);
		वापस 0;
	पूर्ण
	/* check the rate is within the range */
	अगर (fp->rate_min > it->max || (fp->rate_min == it->max && it->खोलोmax)) अणु
		hwc_debug("   > check: rate_min %d > max %d\n", fp->rate_min, it->max);
		वापस 0;
	पूर्ण
	अगर (fp->rate_max < it->min || (fp->rate_max == it->min && it->खोलोmin)) अणु
		hwc_debug("   > check: rate_max %d < min %d\n", fp->rate_max, it->min);
		वापस 0;
	पूर्ण
	/* check whether the period समय is >= the data packet पूर्णांकerval */
	अगर (subs->speed != USB_SPEED_FULL) अणु
		pसमय = 125 * (1 << fp->dataपूर्णांकerval);
		अगर (pसमय > pt->max || (pसमय == pt->max && pt->खोलोmax)) अणु
			hwc_debug("   > check: ptime %u > max %u\n", pसमय, pt->max);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक apply_hw_params_minmax(काष्ठा snd_पूर्णांकerval *it, अचिन्हित पूर्णांक rmin,
				  अचिन्हित पूर्णांक rmax)
अणु
	पूर्णांक changed;

	अगर (rmin > rmax) अणु
		hwc_debug("  --> get empty\n");
		it->empty = 1;
		वापस -EINVAL;
	पूर्ण

	changed = 0;
	अगर (it->min < rmin) अणु
		it->min = rmin;
		it->खोलोmin = 0;
		changed = 1;
	पूर्ण
	अगर (it->max > rmax) अणु
		it->max = rmax;
		it->खोलोmax = 0;
		changed = 1;
	पूर्ण
	अगर (snd_पूर्णांकerval_checkempty(it)) अणु
		it->empty = 1;
		वापस -EINVAL;
	पूर्ण
	hwc_debug("  --> (%d, %d) (changed = %d)\n", it->min, it->max, changed);
	वापस changed;
पूर्ण

अटल पूर्णांक hw_rule_rate(काष्ठा snd_pcm_hw_params *params,
			काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_usb_substream *subs = rule->निजी;
	स्थिर काष्ठा audioक्रमmat *fp;
	काष्ठा snd_पूर्णांकerval *it = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	अचिन्हित पूर्णांक rmin, rmax, r;
	पूर्णांक i;

	hwc_debug("hw_rule_rate: (%d,%d)\n", it->min, it->max);
	rmin = अच_पूर्णांक_उच्च;
	rmax = 0;
	list_क्रम_each_entry(fp, &subs->fmt_list, list) अणु
		अगर (!hw_check_valid_क्रमmat(subs, params, fp))
			जारी;
		अगर (fp->rate_table && fp->nr_rates) अणु
			क्रम (i = 0; i < fp->nr_rates; i++) अणु
				r = fp->rate_table[i];
				अगर (!snd_पूर्णांकerval_test(it, r))
					जारी;
				rmin = min(rmin, r);
				rmax = max(rmax, r);
			पूर्ण
		पूर्ण अन्यथा अणु
			rmin = min(rmin, fp->rate_min);
			rmax = max(rmax, fp->rate_max);
		पूर्ण
	पूर्ण

	वापस apply_hw_params_minmax(it, rmin, rmax);
पूर्ण


अटल पूर्णांक hw_rule_channels(काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_usb_substream *subs = rule->निजी;
	स्थिर काष्ठा audioक्रमmat *fp;
	काष्ठा snd_पूर्णांकerval *it = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	अचिन्हित पूर्णांक rmin, rmax;

	hwc_debug("hw_rule_channels: (%d,%d)\n", it->min, it->max);
	rmin = अच_पूर्णांक_उच्च;
	rmax = 0;
	list_क्रम_each_entry(fp, &subs->fmt_list, list) अणु
		अगर (!hw_check_valid_क्रमmat(subs, params, fp))
			जारी;
		rmin = min(rmin, fp->channels);
		rmax = max(rmax, fp->channels);
	पूर्ण

	वापस apply_hw_params_minmax(it, rmin, rmax);
पूर्ण

अटल पूर्णांक apply_hw_params_क्रमmat_bits(काष्ठा snd_mask *fmt, u64 fbits)
अणु
	u32 oldbits[2];
	पूर्णांक changed;

	oldbits[0] = fmt->bits[0];
	oldbits[1] = fmt->bits[1];
	fmt->bits[0] &= (u32)fbits;
	fmt->bits[1] &= (u32)(fbits >> 32);
	अगर (!fmt->bits[0] && !fmt->bits[1]) अणु
		hwc_debug("  --> get empty\n");
		वापस -EINVAL;
	पूर्ण
	changed = (oldbits[0] != fmt->bits[0] || oldbits[1] != fmt->bits[1]);
	hwc_debug("  --> %x:%x (changed = %d)\n", fmt->bits[0], fmt->bits[1], changed);
	वापस changed;
पूर्ण

अटल पूर्णांक hw_rule_क्रमmat(काष्ठा snd_pcm_hw_params *params,
			  काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_usb_substream *subs = rule->निजी;
	स्थिर काष्ठा audioक्रमmat *fp;
	काष्ठा snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	u64 fbits;

	hwc_debug("hw_rule_format: %x:%x\n", fmt->bits[0], fmt->bits[1]);
	fbits = 0;
	list_क्रम_each_entry(fp, &subs->fmt_list, list) अणु
		अगर (!hw_check_valid_क्रमmat(subs, params, fp))
			जारी;
		fbits |= fp->क्रमmats;
	पूर्ण
	वापस apply_hw_params_क्रमmat_bits(fmt, fbits);
पूर्ण

अटल पूर्णांक hw_rule_period_समय(काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_usb_substream *subs = rule->निजी;
	स्थिर काष्ठा audioक्रमmat *fp;
	काष्ठा snd_पूर्णांकerval *it;
	अचिन्हित अक्षर min_dataपूर्णांकerval;
	अचिन्हित पूर्णांक pmin;

	it = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_PERIOD_TIME);
	hwc_debug("hw_rule_period_time: (%u,%u)\n", it->min, it->max);
	min_dataपूर्णांकerval = 0xff;
	list_क्रम_each_entry(fp, &subs->fmt_list, list) अणु
		अगर (!hw_check_valid_क्रमmat(subs, params, fp))
			जारी;
		min_dataपूर्णांकerval = min(min_dataपूर्णांकerval, fp->dataपूर्णांकerval);
	पूर्ण
	अगर (min_dataपूर्णांकerval == 0xff) अणु
		hwc_debug("  --> get empty\n");
		it->empty = 1;
		वापस -EINVAL;
	पूर्ण
	pmin = 125 * (1 << min_dataपूर्णांकerval);

	वापस apply_hw_params_minmax(it, pmin, अच_पूर्णांक_उच्च);
पूर्ण

/* get the EP or the sync EP क्रम implicit fb when it's alपढ़ोy set up */
अटल स्थिर काष्ठा snd_usb_endpoपूर्णांक *
get_sync_ep_from_substream(काष्ठा snd_usb_substream *subs)
अणु
	काष्ठा snd_usb_audio *chip = subs->stream->chip;
	स्थिर काष्ठा audioक्रमmat *fp;
	स्थिर काष्ठा snd_usb_endpoपूर्णांक *ep;

	list_क्रम_each_entry(fp, &subs->fmt_list, list) अणु
		ep = snd_usb_get_endpoपूर्णांक(chip, fp->endpoपूर्णांक);
		अगर (ep && ep->cur_audiofmt) अणु
			/* अगर EP is alपढ़ोy खोलोed solely क्रम this substream,
			 * we still allow us to change the parameter; otherwise
			 * this substream has to follow the existing parameter
			 */
			अगर (ep->cur_audiofmt != subs->cur_audiofmt || ep->खोलोed > 1)
				वापस ep;
		पूर्ण
		अगर (!fp->implicit_fb)
			जारी;
		/* क्रम the implicit fb, check the sync ep as well */
		ep = snd_usb_get_endpoपूर्णांक(chip, fp->sync_ep);
		अगर (ep && ep->cur_audiofmt)
			वापस ep;
	पूर्ण
	वापस शून्य;
पूर्ण

/* additional hw स्थिरraपूर्णांकs क्रम implicit feedback mode */
अटल पूर्णांक hw_rule_क्रमmat_implicit_fb(काष्ठा snd_pcm_hw_params *params,
				      काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_usb_substream *subs = rule->निजी;
	स्थिर काष्ठा snd_usb_endpoपूर्णांक *ep;
	काष्ठा snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);

	ep = get_sync_ep_from_substream(subs);
	अगर (!ep)
		वापस 0;

	hwc_debug("applying %s\n", __func__);
	वापस apply_hw_params_क्रमmat_bits(fmt, pcm_क्रमmat_to_bits(ep->cur_क्रमmat));
पूर्ण

अटल पूर्णांक hw_rule_rate_implicit_fb(काष्ठा snd_pcm_hw_params *params,
				    काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_usb_substream *subs = rule->निजी;
	स्थिर काष्ठा snd_usb_endpoपूर्णांक *ep;
	काष्ठा snd_पूर्णांकerval *it;

	ep = get_sync_ep_from_substream(subs);
	अगर (!ep)
		वापस 0;

	hwc_debug("applying %s\n", __func__);
	it = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	वापस apply_hw_params_minmax(it, ep->cur_rate, ep->cur_rate);
पूर्ण

अटल पूर्णांक hw_rule_period_size_implicit_fb(काष्ठा snd_pcm_hw_params *params,
					   काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_usb_substream *subs = rule->निजी;
	स्थिर काष्ठा snd_usb_endpoपूर्णांक *ep;
	काष्ठा snd_पूर्णांकerval *it;

	ep = get_sync_ep_from_substream(subs);
	अगर (!ep)
		वापस 0;

	hwc_debug("applying %s\n", __func__);
	it = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
	वापस apply_hw_params_minmax(it, ep->cur_period_frames,
				      ep->cur_period_frames);
पूर्ण

अटल पूर्णांक hw_rule_periods_implicit_fb(काष्ठा snd_pcm_hw_params *params,
				       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_usb_substream *subs = rule->निजी;
	स्थिर काष्ठा snd_usb_endpoपूर्णांक *ep;
	काष्ठा snd_पूर्णांकerval *it;

	ep = get_sync_ep_from_substream(subs);
	अगर (!ep)
		वापस 0;

	hwc_debug("applying %s\n", __func__);
	it = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_PERIODS);
	वापस apply_hw_params_minmax(it, ep->cur_buffer_periods,
				      ep->cur_buffer_periods);
पूर्ण

/*
 * set up the runसमय hardware inक्रमmation.
 */

अटल पूर्णांक setup_hw_info(काष्ठा snd_pcm_runसमय *runसमय, काष्ठा snd_usb_substream *subs)
अणु
	स्थिर काष्ठा audioक्रमmat *fp;
	अचिन्हित पूर्णांक pt, pपंचांगin;
	पूर्णांक param_period_समय_अगर_needed = -1;
	पूर्णांक err;

	runसमय->hw.क्रमmats = subs->क्रमmats;

	runसमय->hw.rate_min = 0x7fffffff;
	runसमय->hw.rate_max = 0;
	runसमय->hw.channels_min = 256;
	runसमय->hw.channels_max = 0;
	runसमय->hw.rates = 0;
	pपंचांगin = अच_पूर्णांक_उच्च;
	/* check min/max rates and channels */
	list_क्रम_each_entry(fp, &subs->fmt_list, list) अणु
		runसमय->hw.rates |= fp->rates;
		अगर (runसमय->hw.rate_min > fp->rate_min)
			runसमय->hw.rate_min = fp->rate_min;
		अगर (runसमय->hw.rate_max < fp->rate_max)
			runसमय->hw.rate_max = fp->rate_max;
		अगर (runसमय->hw.channels_min > fp->channels)
			runसमय->hw.channels_min = fp->channels;
		अगर (runसमय->hw.channels_max < fp->channels)
			runसमय->hw.channels_max = fp->channels;
		अगर (fp->fmt_type == UAC_FORMAT_TYPE_II && fp->frame_size > 0) अणु
			/* FIXME: there might be more than one audio क्रमmats... */
			runसमय->hw.period_bytes_min = runसमय->hw.period_bytes_max =
				fp->frame_size;
		पूर्ण
		pt = 125 * (1 << fp->dataपूर्णांकerval);
		pपंचांगin = min(pपंचांगin, pt);
	पूर्ण

	param_period_समय_अगर_needed = SNDRV_PCM_HW_PARAM_PERIOD_TIME;
	अगर (subs->speed == USB_SPEED_FULL)
		/* full speed devices have fixed data packet पूर्णांकerval */
		pपंचांगin = 1000;
	अगर (pपंचांगin == 1000)
		/* अगर period समय करोesn't go below 1 ms, no rules needed */
		param_period_समय_अगर_needed = -1;

	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
					   SNDRV_PCM_HW_PARAM_PERIOD_TIME,
					   pपंचांगin, अच_पूर्णांक_उच्च);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				  hw_rule_rate, subs,
				  SNDRV_PCM_HW_PARAM_RATE,
				  SNDRV_PCM_HW_PARAM_FORMAT,
				  SNDRV_PCM_HW_PARAM_CHANNELS,
				  param_period_समय_अगर_needed,
				  -1);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  hw_rule_channels, subs,
				  SNDRV_PCM_HW_PARAM_CHANNELS,
				  SNDRV_PCM_HW_PARAM_FORMAT,
				  SNDRV_PCM_HW_PARAM_RATE,
				  param_period_समय_अगर_needed,
				  -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_FORMAT,
				  hw_rule_क्रमmat, subs,
				  SNDRV_PCM_HW_PARAM_FORMAT,
				  SNDRV_PCM_HW_PARAM_RATE,
				  SNDRV_PCM_HW_PARAM_CHANNELS,
				  param_period_समय_अगर_needed,
				  -1);
	अगर (err < 0)
		वापस err;
	अगर (param_period_समय_अगर_needed >= 0) अणु
		err = snd_pcm_hw_rule_add(runसमय, 0,
					  SNDRV_PCM_HW_PARAM_PERIOD_TIME,
					  hw_rule_period_समय, subs,
					  SNDRV_PCM_HW_PARAM_FORMAT,
					  SNDRV_PCM_HW_PARAM_CHANNELS,
					  SNDRV_PCM_HW_PARAM_RATE,
					  -1);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* additional hw स्थिरraपूर्णांकs क्रम implicit fb */
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_FORMAT,
				  hw_rule_क्रमmat_implicit_fb, subs,
				  SNDRV_PCM_HW_PARAM_FORMAT, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				  hw_rule_rate_implicit_fb, subs,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
				  hw_rule_period_size_implicit_fb, subs,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE, -1);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIODS,
				  hw_rule_periods_implicit_fb, subs,
				  SNDRV_PCM_HW_PARAM_PERIODS, -1);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_usb_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक direction = substream->stream;
	काष्ठा snd_usb_stream *as = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_usb_substream *subs = &as->substream[direction];
	पूर्णांक ret;

	runसमय->hw = snd_usb_hardware;
	runसमय->निजी_data = subs;
	subs->pcm_substream = substream;
	/* runसमय PM is also करोne there */

	/* initialize DSD/DOP context */
	subs->dsd_करोp.byte_idx = 0;
	subs->dsd_करोp.channel = 0;
	subs->dsd_करोp.marker = 1;

	ret = setup_hw_info(runसमय, subs);
	अगर (ret < 0)
		वापस ret;
	ret = snd_usb_स्वतःresume(subs->stream->chip);
	अगर (ret < 0)
		वापस ret;
	ret = snd_media_stream_init(subs, as->pcm, direction);
	अगर (ret < 0)
		snd_usb_स्वतःsuspend(subs->stream->chip);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_usb_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक direction = substream->stream;
	काष्ठा snd_usb_stream *as = snd_pcm_substream_chip(substream);
	काष्ठा snd_usb_substream *subs = &as->substream[direction];
	पूर्णांक ret;

	snd_media_stop_pipeline(subs);

	अगर (!snd_usb_lock_shutकरोwn(subs->stream->chip)) अणु
		ret = snd_usb_pcm_change_state(subs, UAC3_PD_STATE_D1);
		snd_usb_unlock_shutकरोwn(subs->stream->chip);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	subs->pcm_substream = शून्य;
	snd_usb_स्वतःsuspend(subs->stream->chip);

	वापस 0;
पूर्ण

/* Since a URB can handle only a single linear buffer, we must use द्विगुन
 * buffering when the data to be transferred overflows the buffer boundary.
 * To aव्योम inconsistencies when updating hwptr_करोne, we use द्विगुन buffering
 * क्रम all URBs.
 */
अटल व्योम retire_capture_urb(काष्ठा snd_usb_substream *subs,
			       काष्ठा urb *urb)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = subs->pcm_substream->runसमय;
	अचिन्हित पूर्णांक stride, frames, bytes, oldptr;
	पूर्णांक i, period_elapsed = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर *cp;
	पूर्णांक current_frame_number;

	/* पढ़ो frame number here, update poपूर्णांकer in critical section */
	current_frame_number = usb_get_current_frame_number(subs->dev);

	stride = runसमय->frame_bits >> 3;

	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		cp = (अचिन्हित अक्षर *)urb->transfer_buffer + urb->iso_frame_desc[i].offset + subs->pkt_offset_adj;
		अगर (urb->iso_frame_desc[i].status && prपूर्णांकk_ratelimit()) अणु
			dev_dbg(&subs->dev->dev, "frame %d active: %d\n",
				i, urb->iso_frame_desc[i].status);
			// जारी;
		पूर्ण
		bytes = urb->iso_frame_desc[i].actual_length;
		अगर (subs->stream_offset_adj > 0) अणु
			अचिन्हित पूर्णांक adj = min(subs->stream_offset_adj, bytes);
			cp += adj;
			bytes -= adj;
			subs->stream_offset_adj -= adj;
		पूर्ण
		frames = bytes / stride;
		अगर (!subs->txfr_quirk)
			bytes = frames * stride;
		अगर (bytes % (runसमय->sample_bits >> 3) != 0) अणु
			पूर्णांक oldbytes = bytes;
			bytes = frames * stride;
			dev_warn_ratelimited(&subs->dev->dev,
				 "Corrected urb data len. %d->%d\n",
							oldbytes, bytes);
		पूर्ण
		/* update the current poपूर्णांकer */
		spin_lock_irqsave(&subs->lock, flags);
		oldptr = subs->hwptr_करोne;
		subs->hwptr_करोne += bytes;
		अगर (subs->hwptr_करोne >= runसमय->buffer_size * stride)
			subs->hwptr_करोne -= runसमय->buffer_size * stride;
		frames = (bytes + (oldptr % stride)) / stride;
		subs->transfer_करोne += frames;
		अगर (subs->transfer_करोne >= runसमय->period_size) अणु
			subs->transfer_करोne -= runसमय->period_size;
			period_elapsed = 1;
		पूर्ण
		/* capture delay is by स्थिरruction limited to one URB,
		 * reset delays here
		 */
		runसमय->delay = subs->last_delay = 0;

		/* realign last_frame_number */
		subs->last_frame_number = current_frame_number;
		subs->last_frame_number &= 0xFF; /* keep 8 LSBs */

		spin_unlock_irqrestore(&subs->lock, flags);
		/* copy a data chunk */
		अगर (oldptr + bytes > runसमय->buffer_size * stride) अणु
			अचिन्हित पूर्णांक bytes1 =
					runसमय->buffer_size * stride - oldptr;
			स_नकल(runसमय->dma_area + oldptr, cp, bytes1);
			स_नकल(runसमय->dma_area, cp + bytes1, bytes - bytes1);
		पूर्ण अन्यथा अणु
			स_नकल(runसमय->dma_area + oldptr, cp, bytes);
		पूर्ण
	पूर्ण

	अगर (period_elapsed)
		snd_pcm_period_elapsed(subs->pcm_substream);
पूर्ण

अटल अंतरभूत व्योम fill_playback_urb_dsd_करोp(काष्ठा snd_usb_substream *subs,
					     काष्ठा urb *urb, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = subs->pcm_substream->runसमय;
	अचिन्हित पूर्णांक stride = runसमय->frame_bits >> 3;
	अचिन्हित पूर्णांक dst_idx = 0;
	अचिन्हित पूर्णांक src_idx = subs->hwptr_करोne;
	अचिन्हित पूर्णांक wrap = runसमय->buffer_size * stride;
	u8 *dst = urb->transfer_buffer;
	u8 *src = runसमय->dma_area;
	u8 marker[] = अणु 0x05, 0xfa पूर्ण;

	/*
	 * The DSP DOP क्रमmat defines a way to transport DSD samples over
	 * normal PCM data endpoपूर्णांकs. It requires stuffing of marker bytes
	 * (0x05 and 0xfa, alternating per sample frame), and then expects
	 * 2 additional bytes of actual payload. The whole frame is stored
	 * LSB.
	 *
	 * Hence, क्रम a stereo transport, the buffer layout looks like this,
	 * where L refers to left channel samples and R to right.
	 *
	 *   L1 L2 0x05   R1 R2 0x05   L3 L4 0xfa  R3 R4 0xfa
	 *   L5 L6 0x05   R5 R6 0x05   L7 L8 0xfa  R7 R8 0xfa
	 *   .....
	 *
	 */

	जबतक (bytes--) अणु
		अगर (++subs->dsd_करोp.byte_idx == 3) अणु
			/* frame boundary? */
			dst[dst_idx++] = marker[subs->dsd_करोp.marker];
			src_idx += 2;
			subs->dsd_करोp.byte_idx = 0;

			अगर (++subs->dsd_करोp.channel % runसमय->channels == 0) अणु
				/* alternate the marker */
				subs->dsd_करोp.marker++;
				subs->dsd_करोp.marker %= ARRAY_SIZE(marker);
				subs->dsd_करोp.channel = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* stuff the DSD payload */
			पूर्णांक idx = (src_idx + subs->dsd_करोp.byte_idx - 1) % wrap;

			अगर (subs->cur_audiofmt->dsd_bitrev)
				dst[dst_idx++] = bitrev8(src[idx]);
			अन्यथा
				dst[dst_idx++] = src[idx];

			subs->hwptr_करोne++;
		पूर्ण
	पूर्ण
	अगर (subs->hwptr_करोne >= runसमय->buffer_size * stride)
		subs->hwptr_करोne -= runसमय->buffer_size * stride;
पूर्ण

अटल व्योम copy_to_urb(काष्ठा snd_usb_substream *subs, काष्ठा urb *urb,
			पूर्णांक offset, पूर्णांक stride, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = subs->pcm_substream->runसमय;

	अगर (subs->hwptr_करोne + bytes > runसमय->buffer_size * stride) अणु
		/* err, the transferred area goes over buffer boundary. */
		अचिन्हित पूर्णांक bytes1 =
			runसमय->buffer_size * stride - subs->hwptr_करोne;
		स_नकल(urb->transfer_buffer + offset,
		       runसमय->dma_area + subs->hwptr_करोne, bytes1);
		स_नकल(urb->transfer_buffer + offset + bytes1,
		       runसमय->dma_area, bytes - bytes1);
	पूर्ण अन्यथा अणु
		स_नकल(urb->transfer_buffer + offset,
		       runसमय->dma_area + subs->hwptr_करोne, bytes);
	पूर्ण
	subs->hwptr_करोne += bytes;
	अगर (subs->hwptr_करोne >= runसमय->buffer_size * stride)
		subs->hwptr_करोne -= runसमय->buffer_size * stride;
पूर्ण

अटल अचिन्हित पूर्णांक copy_to_urb_quirk(काष्ठा snd_usb_substream *subs,
				      काष्ठा urb *urb, पूर्णांक stride,
				      अचिन्हित पूर्णांक bytes)
अणु
	__le32 packet_length;
	पूर्णांक i;

	/* Put __le32 length descriptor at start of each packet. */
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		अचिन्हित पूर्णांक length = urb->iso_frame_desc[i].length;
		अचिन्हित पूर्णांक offset = urb->iso_frame_desc[i].offset;

		packet_length = cpu_to_le32(length);
		offset += i * माप(packet_length);
		urb->iso_frame_desc[i].offset = offset;
		urb->iso_frame_desc[i].length += माप(packet_length);
		स_नकल(urb->transfer_buffer + offset,
		       &packet_length, माप(packet_length));
		copy_to_urb(subs, urb, offset + माप(packet_length),
			    stride, length);
	पूर्ण
	/* Adjust transfer size accordingly. */
	bytes += urb->number_of_packets * माप(packet_length);
	वापस bytes;
पूर्ण

अटल व्योम prepare_playback_urb(काष्ठा snd_usb_substream *subs,
				 काष्ठा urb *urb)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = subs->pcm_substream->runसमय;
	काष्ठा snd_usb_endpoपूर्णांक *ep = subs->data_endpoपूर्णांक;
	काष्ठा snd_urb_ctx *ctx = urb->context;
	अचिन्हित पूर्णांक counts, frames, bytes;
	पूर्णांक i, stride, period_elapsed = 0;
	अचिन्हित दीर्घ flags;

	stride = runसमय->frame_bits >> 3;

	frames = 0;
	urb->number_of_packets = 0;
	spin_lock_irqsave(&subs->lock, flags);
	subs->frame_limit += ep->max_urb_frames;
	क्रम (i = 0; i < ctx->packets; i++) अणु
		counts = snd_usb_endpoपूर्णांक_next_packet_size(ep, ctx, i);
		/* set up descriptor */
		urb->iso_frame_desc[i].offset = frames * ep->stride;
		urb->iso_frame_desc[i].length = counts * ep->stride;
		frames += counts;
		urb->number_of_packets++;
		subs->transfer_करोne += counts;
		अगर (subs->transfer_करोne >= runसमय->period_size) अणु
			subs->transfer_करोne -= runसमय->period_size;
			subs->frame_limit = 0;
			period_elapsed = 1;
			अगर (subs->fmt_type == UAC_FORMAT_TYPE_II) अणु
				अगर (subs->transfer_करोne > 0) अणु
					/* FIXME: fill-max mode is not
					 * supported yet */
					frames -= subs->transfer_करोne;
					counts -= subs->transfer_करोne;
					urb->iso_frame_desc[i].length =
						counts * ep->stride;
					subs->transfer_करोne = 0;
				पूर्ण
				i++;
				अगर (i < ctx->packets) अणु
					/* add a transfer delimiter */
					urb->iso_frame_desc[i].offset =
						frames * ep->stride;
					urb->iso_frame_desc[i].length = 0;
					urb->number_of_packets++;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		/* finish at the period boundary or after enough frames */
		अगर ((period_elapsed ||
				subs->transfer_करोne >= subs->frame_limit) &&
		    !snd_usb_endpoपूर्णांक_implicit_feedback_sink(ep))
			अवरोध;
	पूर्ण
	bytes = frames * ep->stride;

	अगर (unlikely(ep->cur_क्रमmat == SNDRV_PCM_FORMAT_DSD_U16_LE &&
		     subs->cur_audiofmt->dsd_करोp)) अणु
		fill_playback_urb_dsd_करोp(subs, urb, bytes);
	पूर्ण अन्यथा अगर (unlikely(ep->cur_क्रमmat == SNDRV_PCM_FORMAT_DSD_U8 &&
			   subs->cur_audiofmt->dsd_bitrev)) अणु
		/* bit-reverse the bytes */
		u8 *buf = urb->transfer_buffer;
		क्रम (i = 0; i < bytes; i++) अणु
			पूर्णांक idx = (subs->hwptr_करोne + i)
				% (runसमय->buffer_size * stride);
			buf[i] = bitrev8(runसमय->dma_area[idx]);
		पूर्ण

		subs->hwptr_करोne += bytes;
		अगर (subs->hwptr_करोne >= runसमय->buffer_size * stride)
			subs->hwptr_करोne -= runसमय->buffer_size * stride;
	पूर्ण अन्यथा अणु
		/* usual PCM */
		अगर (!subs->tx_length_quirk)
			copy_to_urb(subs, urb, 0, stride, bytes);
		अन्यथा
			bytes = copy_to_urb_quirk(subs, urb, stride, bytes);
			/* bytes is now amount of outgoing data */
	पूर्ण

	/* update delay with exact number of samples queued */
	runसमय->delay = subs->last_delay;
	runसमय->delay += frames;
	subs->last_delay = runसमय->delay;

	/* realign last_frame_number */
	subs->last_frame_number = usb_get_current_frame_number(subs->dev);
	subs->last_frame_number &= 0xFF; /* keep 8 LSBs */

	अगर (subs->trigger_tstamp_pending_update) अणु
		/* this is the first actual URB submitted,
		 * update trigger बारtamp to reflect actual start समय
		 */
		snd_pcm_समय_लो(runसमय, &runसमय->trigger_tstamp);
		subs->trigger_tstamp_pending_update = false;
	पूर्ण

	spin_unlock_irqrestore(&subs->lock, flags);
	urb->transfer_buffer_length = bytes;
	अगर (period_elapsed)
		snd_pcm_period_elapsed(subs->pcm_substream);
पूर्ण

/*
 * process after playback data complete
 * - decrease the delay count again
 */
अटल व्योम retire_playback_urb(काष्ठा snd_usb_substream *subs,
			       काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_pcm_runसमय *runसमय = subs->pcm_substream->runसमय;
	काष्ठा snd_usb_endpoपूर्णांक *ep = subs->data_endpoपूर्णांक;
	पूर्णांक processed = urb->transfer_buffer_length / ep->stride;
	पूर्णांक est_delay;

	/* ignore the delay accounting when processed=0 is given, i.e.
	 * silent payloads are processed beक्रमe handling the actual data
	 */
	अगर (!processed)
		वापस;

	spin_lock_irqsave(&subs->lock, flags);
	अगर (!subs->last_delay)
		जाओ out; /* लघु path */

	est_delay = snd_usb_pcm_delay(subs, runसमय->rate);
	/* update delay with exact number of samples played */
	अगर (processed > subs->last_delay)
		subs->last_delay = 0;
	अन्यथा
		subs->last_delay -= processed;
	runसमय->delay = subs->last_delay;

	/*
	 * Report when delay estimate is off by more than 2ms.
	 * The error should be lower than 2ms since the estimate relies
	 * on two पढ़ोs of a counter updated every ms.
	 */
	अगर (असल(est_delay - subs->last_delay) * 1000 > runसमय->rate * 2)
		dev_dbg_ratelimited(&subs->dev->dev,
			"delay: estimated %d, actual %d\n",
			est_delay, subs->last_delay);

	अगर (!subs->running) अणु
		/* update last_frame_number क्रम delay counting here since
		 * prepare_playback_urb won't be called during छोड़ो
		 */
		subs->last_frame_number =
			usb_get_current_frame_number(subs->dev) & 0xff;
	पूर्ण

 out:
	spin_unlock_irqrestore(&subs->lock, flags);
पूर्ण

अटल पूर्णांक snd_usb_substream_playback_trigger(काष्ठा snd_pcm_substream *substream,
					      पूर्णांक cmd)
अणु
	काष्ठा snd_usb_substream *subs = substream->runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		subs->trigger_tstamp_pending_update = true;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		snd_usb_endpoपूर्णांक_set_callback(subs->data_endpoपूर्णांक,
					      prepare_playback_urb,
					      retire_playback_urb,
					      subs);
		subs->running = 1;
		dev_dbg(&subs->dev->dev, "%d:%d Start Playback PCM\n",
			subs->cur_audiofmt->अगरace,
			subs->cur_audiofmt->altsetting);
		वापस 0;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		stop_endpoपूर्णांकs(subs);
		snd_usb_endpoपूर्णांक_set_callback(subs->data_endpoपूर्णांक,
					      शून्य, शून्य, शून्य);
		subs->running = 0;
		dev_dbg(&subs->dev->dev, "%d:%d Stop Playback PCM\n",
			subs->cur_audiofmt->अगरace,
			subs->cur_audiofmt->altsetting);
		वापस 0;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		/* keep retire_data_urb क्रम delay calculation */
		snd_usb_endpoपूर्णांक_set_callback(subs->data_endpoपूर्णांक,
					      शून्य,
					      retire_playback_urb,
					      subs);
		subs->running = 0;
		dev_dbg(&subs->dev->dev, "%d:%d Pause Playback PCM\n",
			subs->cur_audiofmt->अगरace,
			subs->cur_audiofmt->altsetting);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक snd_usb_substream_capture_trigger(काष्ठा snd_pcm_substream *substream,
					     पूर्णांक cmd)
अणु
	पूर्णांक err;
	काष्ठा snd_usb_substream *subs = substream->runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		err = start_endpoपूर्णांकs(subs);
		अगर (err < 0)
			वापस err;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		snd_usb_endpoपूर्णांक_set_callback(subs->data_endpoपूर्णांक,
					      शून्य, retire_capture_urb,
					      subs);
		subs->running = 1;
		dev_dbg(&subs->dev->dev, "%d:%d Start Capture PCM\n",
			subs->cur_audiofmt->अगरace,
			subs->cur_audiofmt->altsetting);
		वापस 0;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		stop_endpoपूर्णांकs(subs);
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		snd_usb_endpoपूर्णांक_set_callback(subs->data_endpoपूर्णांक,
					      शून्य, शून्य, शून्य);
		subs->running = 0;
		dev_dbg(&subs->dev->dev, "%d:%d Stop Capture PCM\n",
			subs->cur_audiofmt->अगरace,
			subs->cur_audiofmt->altsetting);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_usb_playback_ops = अणु
	.खोलो =		snd_usb_pcm_खोलो,
	.बंद =	snd_usb_pcm_बंद,
	.hw_params =	snd_usb_hw_params,
	.hw_मुक्त =	snd_usb_hw_मुक्त,
	.prepare =	snd_usb_pcm_prepare,
	.trigger =	snd_usb_substream_playback_trigger,
	.sync_stop =	snd_usb_pcm_sync_stop,
	.poपूर्णांकer =	snd_usb_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_usb_capture_ops = अणु
	.खोलो =		snd_usb_pcm_खोलो,
	.बंद =	snd_usb_pcm_बंद,
	.hw_params =	snd_usb_hw_params,
	.hw_मुक्त =	snd_usb_hw_मुक्त,
	.prepare =	snd_usb_pcm_prepare,
	.trigger =	snd_usb_substream_capture_trigger,
	.sync_stop =	snd_usb_pcm_sync_stop,
	.poपूर्णांकer =	snd_usb_pcm_poपूर्णांकer,
पूर्ण;

व्योम snd_usb_set_pcm_ops(काष्ठा snd_pcm *pcm, पूर्णांक stream)
अणु
	स्थिर काष्ठा snd_pcm_ops *ops;

	ops = stream == SNDRV_PCM_STREAM_PLAYBACK ?
			&snd_usb_playback_ops : &snd_usb_capture_ops;
	snd_pcm_set_ops(pcm, stream, ops);
पूर्ण

व्योम snd_usb_pपुनः_स्मृतिate_buffer(काष्ठा snd_usb_substream *subs)
अणु
	काष्ठा snd_pcm *pcm = subs->stream->pcm;
	काष्ठा snd_pcm_substream *s = pcm->streams[subs->direction].substream;
	काष्ठा device *dev = subs->dev->bus->sysdev;

	अगर (snd_usb_use_vदो_स्मृति)
		snd_pcm_set_managed_buffer(s, SNDRV_DMA_TYPE_VMALLOC,
					   शून्य, 0, 0);
	अन्यथा
		snd_pcm_set_managed_buffer(s, SNDRV_DMA_TYPE_DEV_SG,
					   dev, 64*1024, 512*1024);
पूर्ण
