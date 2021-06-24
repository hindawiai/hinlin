<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "capture.h"
#समावेश "driver.h"
#समावेश "playback.h"

/* impulse response volume controls */
अटल पूर्णांक snd_line6_impulse_volume_info(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_line6_impulse_volume_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = line6pcm->impulse_volume;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_line6_impulse_volume_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक err;

	अगर (line6pcm->impulse_volume == value)
		वापस 0;

	line6pcm->impulse_volume = value;
	अगर (value > 0) अणु
		err = line6_pcm_acquire(line6pcm, LINE6_STREAM_IMPULSE, true);
		अगर (err < 0) अणु
			line6pcm->impulse_volume = 0;
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		line6_pcm_release(line6pcm, LINE6_STREAM_IMPULSE);
	पूर्ण
	वापस 1;
पूर्ण

/* impulse response period controls */
अटल पूर्णांक snd_line6_impulse_period_info(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 2000;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_line6_impulse_period_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = line6pcm->impulse_period;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_line6_impulse_period_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];

	अगर (line6pcm->impulse_period == value)
		वापस 0;

	line6pcm->impulse_period = value;
	वापस 1;
पूर्ण

/*
	Unlink all currently active URBs.
*/
अटल व्योम line6_unlink_audio_urbs(काष्ठा snd_line6_pcm *line6pcm,
				    काष्ठा line6_pcm_stream *pcms)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < line6pcm->line6->iso_buffers; i++) अणु
		अगर (test_bit(i, &pcms->active_urbs)) अणु
			अगर (!test_and_set_bit(i, &pcms->unlink_urbs))
				usb_unlink_urb(pcms->urbs[i]);
		पूर्ण
	पूर्ण
पूर्ण

/*
	Wait until unlinking of all currently active URBs has been finished.
*/
अटल व्योम line6_रुको_clear_audio_urbs(काष्ठा snd_line6_pcm *line6pcm,
					काष्ठा line6_pcm_stream *pcms)
अणु
	पूर्णांक समयout = HZ;
	पूर्णांक i;
	पूर्णांक alive;

	करो अणु
		alive = 0;
		क्रम (i = 0; i < line6pcm->line6->iso_buffers; i++) अणु
			अगर (test_bit(i, &pcms->active_urbs))
				alive++;
		पूर्ण
		अगर (!alive)
			अवरोध;
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(1);
	पूर्ण जबतक (--समयout > 0);
	अगर (alive)
		dev_err(line6pcm->line6->अगरcdev,
			"timeout: still %d active urbs..\n", alive);
पूर्ण

अटल अंतरभूत काष्ठा line6_pcm_stream *
get_stream(काष्ठा snd_line6_pcm *line6pcm, पूर्णांक direction)
अणु
	वापस (direction == SNDRV_PCM_STREAM_PLAYBACK) ?
		&line6pcm->out : &line6pcm->in;
पूर्ण

/* allocate a buffer अगर not खोलोed yet;
 * call this in line6pcm.state_mutex
 */
अटल पूर्णांक line6_buffer_acquire(काष्ठा snd_line6_pcm *line6pcm,
				काष्ठा line6_pcm_stream *pstr, पूर्णांक direction, पूर्णांक type)
अणु
	स्थिर पूर्णांक pkt_size =
		(direction == SNDRV_PCM_STREAM_PLAYBACK) ?
			line6pcm->max_packet_size_out :
			line6pcm->max_packet_size_in;

	/* Invoked multiple बार in a row so allocate once only */
	अगर (!test_and_set_bit(type, &pstr->खोलोed) && !pstr->buffer) अणु
		pstr->buffer =
			kदो_स्मृति(array3_size(line6pcm->line6->iso_buffers,
					    LINE6_ISO_PACKETS, pkt_size),
				GFP_KERNEL);
		अगर (!pstr->buffer)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/* मुक्त a buffer अगर all streams are बंदd;
 * call this in line6pcm.state_mutex
 */
अटल व्योम line6_buffer_release(काष्ठा snd_line6_pcm *line6pcm,
				 काष्ठा line6_pcm_stream *pstr, पूर्णांक type)
अणु
	clear_bit(type, &pstr->खोलोed);
	अगर (!pstr->खोलोed) अणु
		line6_रुको_clear_audio_urbs(line6pcm, pstr);
		kमुक्त(pstr->buffer);
		pstr->buffer = शून्य;
	पूर्ण
पूर्ण

/* start a PCM stream */
अटल पूर्णांक line6_stream_start(काष्ठा snd_line6_pcm *line6pcm, पूर्णांक direction,
			      पूर्णांक type)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा line6_pcm_stream *pstr = get_stream(line6pcm, direction);
	पूर्णांक ret = 0;

	spin_lock_irqsave(&pstr->lock, flags);
	अगर (!test_and_set_bit(type, &pstr->running) &&
	    !(pstr->active_urbs || pstr->unlink_urbs)) अणु
		pstr->count = 0;
		/* Submit all currently available URBs */
		अगर (direction == SNDRV_PCM_STREAM_PLAYBACK)
			ret = line6_submit_audio_out_all_urbs(line6pcm);
		अन्यथा
			ret = line6_submit_audio_in_all_urbs(line6pcm);
	पूर्ण

	अगर (ret < 0)
		clear_bit(type, &pstr->running);
	spin_unlock_irqrestore(&pstr->lock, flags);
	वापस ret;
पूर्ण

/* stop a PCM stream; this करोesn't sync with the unlinked URBs */
अटल व्योम line6_stream_stop(काष्ठा snd_line6_pcm *line6pcm, पूर्णांक direction,
			  पूर्णांक type)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा line6_pcm_stream *pstr = get_stream(line6pcm, direction);

	spin_lock_irqsave(&pstr->lock, flags);
	clear_bit(type, &pstr->running);
	अगर (!pstr->running) अणु
		spin_unlock_irqrestore(&pstr->lock, flags);
		line6_unlink_audio_urbs(line6pcm, pstr);
		spin_lock_irqsave(&pstr->lock, flags);
		अगर (direction == SNDRV_PCM_STREAM_CAPTURE) अणु
			line6pcm->prev_fbuf = शून्य;
			line6pcm->prev_fsize = 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pstr->lock, flags);
पूर्ण

/* common PCM trigger callback */
पूर्णांक snd_line6_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *s;
	पूर्णांक err;

	clear_bit(LINE6_FLAG_PREPARED, &line6pcm->flags);

	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (s->pcm->card != substream->pcm->card)
			जारी;

		चयन (cmd) अणु
		हाल SNDRV_PCM_TRIGGER_START:
		हाल SNDRV_PCM_TRIGGER_RESUME:
			अगर (s->stream == SNDRV_PCM_STREAM_CAPTURE &&
				(line6pcm->line6->properties->capabilities &
					LINE6_CAP_IN_NEEDS_OUT)) अणु
				err = line6_stream_start(line6pcm, SNDRV_PCM_STREAM_PLAYBACK,
						 LINE6_STREAM_CAPTURE_HELPER);
				अगर (err < 0)
					वापस err;
			पूर्ण
			err = line6_stream_start(line6pcm, s->stream,
						 LINE6_STREAM_PCM);
			अगर (err < 0)
				वापस err;
			अवरोध;

		हाल SNDRV_PCM_TRIGGER_STOP:
		हाल SNDRV_PCM_TRIGGER_SUSPEND:
			अगर (s->stream == SNDRV_PCM_STREAM_CAPTURE &&
				(line6pcm->line6->properties->capabilities &
					LINE6_CAP_IN_NEEDS_OUT)) अणु
				line6_stream_stop(line6pcm, SNDRV_PCM_STREAM_PLAYBACK,
					  LINE6_STREAM_CAPTURE_HELPER);
			पूर्ण
			line6_stream_stop(line6pcm, s->stream,
					  LINE6_STREAM_PCM);
			अवरोध;

		हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
			अगर (s->stream != SNDRV_PCM_STREAM_PLAYBACK)
				वापस -EINVAL;
			set_bit(LINE6_FLAG_PAUSE_PLAYBACK, &line6pcm->flags);
			अवरोध;

		हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
			अगर (s->stream != SNDRV_PCM_STREAM_PLAYBACK)
				वापस -EINVAL;
			clear_bit(LINE6_FLAG_PAUSE_PLAYBACK, &line6pcm->flags);
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* common PCM poपूर्णांकer callback */
snd_pcm_uframes_t snd_line6_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);
	काष्ठा line6_pcm_stream *pstr = get_stream(line6pcm, substream->stream);

	वापस pstr->pos_करोne;
पूर्ण

/* Acquire and optionally start duplex streams:
 * type is either LINE6_STREAM_IMPULSE or LINE6_STREAM_MONITOR
 */
पूर्णांक line6_pcm_acquire(काष्ठा snd_line6_pcm *line6pcm, पूर्णांक type, bool start)
अणु
	काष्ठा line6_pcm_stream *pstr;
	पूर्णांक ret = 0, dir;

	/* TODO: We should निश्चित SNDRV_PCM_STREAM_PLAYBACK/CAPTURE == 0/1 */
	mutex_lock(&line6pcm->state_mutex);
	क्रम (dir = 0; dir < 2; dir++) अणु
		pstr = get_stream(line6pcm, dir);
		ret = line6_buffer_acquire(line6pcm, pstr, dir, type);
		अगर (ret < 0)
			जाओ error;
		अगर (!pstr->running)
			line6_रुको_clear_audio_urbs(line6pcm, pstr);
	पूर्ण
	अगर (start) अणु
		क्रम (dir = 0; dir < 2; dir++) अणु
			ret = line6_stream_start(line6pcm, dir, type);
			अगर (ret < 0)
				जाओ error;
		पूर्ण
	पूर्ण
 error:
	mutex_unlock(&line6pcm->state_mutex);
	अगर (ret < 0)
		line6_pcm_release(line6pcm, type);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(line6_pcm_acquire);

/* Stop and release duplex streams */
व्योम line6_pcm_release(काष्ठा snd_line6_pcm *line6pcm, पूर्णांक type)
अणु
	काष्ठा line6_pcm_stream *pstr;
	पूर्णांक dir;

	mutex_lock(&line6pcm->state_mutex);
	क्रम (dir = 0; dir < 2; dir++)
		line6_stream_stop(line6pcm, dir, type);
	क्रम (dir = 0; dir < 2; dir++) अणु
		pstr = get_stream(line6pcm, dir);
		line6_buffer_release(line6pcm, pstr, type);
	पूर्ण
	mutex_unlock(&line6pcm->state_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(line6_pcm_release);

/* common PCM hw_params callback */
पूर्णांक snd_line6_hw_params(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_pcm_hw_params *hw_params)
अणु
	पूर्णांक ret;
	काष्ठा snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);
	काष्ठा line6_pcm_stream *pstr = get_stream(line6pcm, substream->stream);

	mutex_lock(&line6pcm->state_mutex);
	ret = line6_buffer_acquire(line6pcm, pstr, substream->stream,
	                           LINE6_STREAM_PCM);
	अगर (ret < 0)
		जाओ error;

	pstr->period = params_period_bytes(hw_params);
 error:
	mutex_unlock(&line6pcm->state_mutex);
	वापस ret;
पूर्ण

/* common PCM hw_मुक्त callback */
पूर्णांक snd_line6_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);
	काष्ठा line6_pcm_stream *pstr = get_stream(line6pcm, substream->stream);

	mutex_lock(&line6pcm->state_mutex);
	line6_buffer_release(line6pcm, pstr, LINE6_STREAM_PCM);
	mutex_unlock(&line6pcm->state_mutex);
	वापस 0;
पूर्ण


/* control info callback */
अटल पूर्णांक snd_line6_control_playback_info(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 256;
	वापस 0;
पूर्ण

/* control get callback */
अटल पूर्णांक snd_line6_control_playback_get(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक i;
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);

	क्रम (i = 0; i < 2; i++)
		ucontrol->value.पूर्णांकeger.value[i] = line6pcm->volume_playback[i];

	वापस 0;
पूर्ण

/* control put callback */
अटल पूर्णांक snd_line6_control_playback_put(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक i, changed = 0;
	काष्ठा snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);

	क्रम (i = 0; i < 2; i++)
		अगर (line6pcm->volume_playback[i] !=
		    ucontrol->value.पूर्णांकeger.value[i]) अणु
			line6pcm->volume_playback[i] =
			    ucontrol->value.पूर्णांकeger.value[i];
			changed = 1;
		पूर्ण

	वापस changed;
पूर्ण

/* control definition */
अटल स्थिर काष्ठा snd_kcontrol_new line6_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "PCM Playback Volume",
		.info = snd_line6_control_playback_info,
		.get = snd_line6_control_playback_get,
		.put = snd_line6_control_playback_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Impulse Response Volume",
		.info = snd_line6_impulse_volume_info,
		.get = snd_line6_impulse_volume_get,
		.put = snd_line6_impulse_volume_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Impulse Response Period",
		.info = snd_line6_impulse_period_info,
		.get = snd_line6_impulse_period_get,
		.put = snd_line6_impulse_period_put
	पूर्ण,
पूर्ण;

/*
	Cleanup the PCM device.
*/
अटल व्योम cleanup_urbs(काष्ठा line6_pcm_stream *pcms, पूर्णांक iso_buffers)
अणु
	पूर्णांक i;

	/* Most likely impossible in current code... */
	अगर (pcms->urbs == शून्य)
		वापस;

	क्रम (i = 0; i < iso_buffers; i++) अणु
		अगर (pcms->urbs[i]) अणु
			usb_समाप्त_urb(pcms->urbs[i]);
			usb_मुक्त_urb(pcms->urbs[i]);
		पूर्ण
	पूर्ण
	kमुक्त(pcms->urbs);
	pcms->urbs = शून्य;
पूर्ण

अटल व्योम line6_cleanup_pcm(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_pcm_chip(pcm);

	cleanup_urbs(&line6pcm->out, line6pcm->line6->iso_buffers);
	cleanup_urbs(&line6pcm->in, line6pcm->line6->iso_buffers);
	kमुक्त(line6pcm);
पूर्ण

/* create a PCM device */
अटल पूर्णांक snd_line6_new_pcm(काष्ठा usb_line6 *line6, काष्ठा snd_pcm **pcm_ret)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(line6->card, (अक्षर *)line6->properties->name,
			  0, 1, 1, pcm_ret);
	अगर (err < 0)
		वापस err;
	pcm = *pcm_ret;
	म_नकल(pcm->name, line6->properties->name);

	/* set चालकs */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_line6_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_line6_capture_ops);

	/* pre-allocation of buffers */
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_CONTINUOUS,
				       शून्य, 64 * 1024, 128 * 1024);
	वापस 0;
पूर्ण

/*
	Sync with PCM stream stops.
*/
व्योम line6_pcm_disconnect(काष्ठा snd_line6_pcm *line6pcm)
अणु
	line6_unlink_audio_urbs(line6pcm, &line6pcm->out);
	line6_unlink_audio_urbs(line6pcm, &line6pcm->in);
	line6_रुको_clear_audio_urbs(line6pcm, &line6pcm->out);
	line6_रुको_clear_audio_urbs(line6pcm, &line6pcm->in);
पूर्ण

/*
	Create and रेजिस्टर the PCM device and mixer entries.
	Create URBs क्रम playback and capture.
*/
पूर्णांक line6_init_pcm(काष्ठा usb_line6 *line6,
		   काष्ठा line6_pcm_properties *properties)
अणु
	पूर्णांक i, err;
	अचिन्हित ep_पढ़ो = line6->properties->ep_audio_r;
	अचिन्हित ep_ग_लिखो = line6->properties->ep_audio_w;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_line6_pcm *line6pcm;

	अगर (!(line6->properties->capabilities & LINE6_CAP_PCM))
		वापस 0;	/* skip PCM initialization and report success */

	err = snd_line6_new_pcm(line6, &pcm);
	अगर (err < 0)
		वापस err;

	line6pcm = kzalloc(माप(*line6pcm), GFP_KERNEL);
	अगर (!line6pcm)
		वापस -ENOMEM;

	mutex_init(&line6pcm->state_mutex);
	line6pcm->pcm = pcm;
	line6pcm->properties = properties;
	line6pcm->volume_playback[0] = line6pcm->volume_playback[1] = 255;
	line6pcm->volume_monitor = 255;
	line6pcm->line6 = line6;

	spin_lock_init(&line6pcm->out.lock);
	spin_lock_init(&line6pcm->in.lock);
	line6pcm->impulse_period = LINE6_IMPULSE_DEFAULT_PERIOD;

	line6->line6pcm = line6pcm;

	pcm->निजी_data = line6pcm;
	pcm->निजी_मुक्त = line6_cleanup_pcm;

	line6pcm->max_packet_size_in =
		usb_maxpacket(line6->usbdev,
			usb_rcvisocpipe(line6->usbdev, ep_पढ़ो), 0);
	line6pcm->max_packet_size_out =
		usb_maxpacket(line6->usbdev,
			usb_sndisocpipe(line6->usbdev, ep_ग_लिखो), 1);
	अगर (!line6pcm->max_packet_size_in || !line6pcm->max_packet_size_out) अणु
		dev_err(line6pcm->line6->अगरcdev,
			"cannot get proper max packet size\n");
		वापस -EINVAL;
	पूर्ण

	err = line6_create_audio_out_urbs(line6pcm);
	अगर (err < 0)
		वापस err;

	err = line6_create_audio_in_urbs(line6pcm);
	अगर (err < 0)
		वापस err;

	/* mixer: */
	क्रम (i = 0; i < ARRAY_SIZE(line6_controls); i++) अणु
		err = snd_ctl_add(line6->card,
				  snd_ctl_new1(&line6_controls[i], line6pcm));
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(line6_init_pcm);

/* prepare pcm callback */
पूर्णांक snd_line6_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);
	काष्ठा line6_pcm_stream *pstr = get_stream(line6pcm, substream->stream);

	mutex_lock(&line6pcm->state_mutex);
	अगर (!pstr->running)
		line6_रुको_clear_audio_urbs(line6pcm, pstr);

	अगर (!test_and_set_bit(LINE6_FLAG_PREPARED, &line6pcm->flags)) अणु
		line6pcm->out.count = 0;
		line6pcm->out.pos = 0;
		line6pcm->out.pos_करोne = 0;
		line6pcm->out.bytes = 0;
		line6pcm->in.count = 0;
		line6pcm->in.pos_करोne = 0;
		line6pcm->in.bytes = 0;
	पूर्ण

	mutex_unlock(&line6pcm->state_mutex);
	वापस 0;
पूर्ण
