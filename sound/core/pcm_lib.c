<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Digital Audio (PCM) असलtract layer
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Abramo Bagnara <abramo@alsa-project.org>
 */

#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/समय.स>
#समावेश <linux/math64.h>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/समयr.h>

#समावेश "pcm_local.h"

#अगर_घोषित CONFIG_SND_PCM_XRUN_DEBUG
#घोषणा CREATE_TRACE_POINTS
#समावेश "pcm_trace.h"
#अन्यथा
#घोषणा trace_hwptr(substream, pos, in_पूर्णांकerrupt)
#घोषणा trace_xrun(substream)
#घोषणा trace_hw_ptr_error(substream, reason)
#घोषणा trace_applptr(substream, prev, curr)
#पूर्ण_अगर

अटल पूर्णांक fill_silence_frames(काष्ठा snd_pcm_substream *substream,
			       snd_pcm_uframes_t off, snd_pcm_uframes_t frames);

/*
 * fill ring buffer with silence
 * runसमय->silence_start: starting poपूर्णांकer to silence area
 * runसमय->silence_filled: size filled with silence
 * runसमय->silence_threshold: threshold from application
 * runसमय->silence_size: maximal size from application
 *
 * when runसमय->silence_size >= runसमय->boundary - fill processed area with silence immediately
 */
व्योम snd_pcm_playback_silence(काष्ठा snd_pcm_substream *substream, snd_pcm_uframes_t new_hw_ptr)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_uframes_t frames, ofs, transfer;
	पूर्णांक err;

	अगर (runसमय->silence_size < runसमय->boundary) अणु
		snd_pcm_sframes_t noise_dist, n;
		snd_pcm_uframes_t appl_ptr = READ_ONCE(runसमय->control->appl_ptr);
		अगर (runसमय->silence_start != appl_ptr) अणु
			n = appl_ptr - runसमय->silence_start;
			अगर (n < 0)
				n += runसमय->boundary;
			अगर ((snd_pcm_uframes_t)n < runसमय->silence_filled)
				runसमय->silence_filled -= n;
			अन्यथा
				runसमय->silence_filled = 0;
			runसमय->silence_start = appl_ptr;
		पूर्ण
		अगर (runसमय->silence_filled >= runसमय->buffer_size)
			वापस;
		noise_dist = snd_pcm_playback_hw_avail(runसमय) + runसमय->silence_filled;
		अगर (noise_dist >= (snd_pcm_sframes_t) runसमय->silence_threshold)
			वापस;
		frames = runसमय->silence_threshold - noise_dist;
		अगर (frames > runसमय->silence_size)
			frames = runसमय->silence_size;
	पूर्ण अन्यथा अणु
		अगर (new_hw_ptr == अच_दीर्घ_उच्च) अणु	/* initialization */
			snd_pcm_sframes_t avail = snd_pcm_playback_hw_avail(runसमय);
			अगर (avail > runसमय->buffer_size)
				avail = runसमय->buffer_size;
			runसमय->silence_filled = avail > 0 ? avail : 0;
			runसमय->silence_start = (runसमय->status->hw_ptr +
						  runसमय->silence_filled) %
						 runसमय->boundary;
		पूर्ण अन्यथा अणु
			ofs = runसमय->status->hw_ptr;
			frames = new_hw_ptr - ofs;
			अगर ((snd_pcm_sframes_t)frames < 0)
				frames += runसमय->boundary;
			runसमय->silence_filled -= frames;
			अगर ((snd_pcm_sframes_t)runसमय->silence_filled < 0) अणु
				runसमय->silence_filled = 0;
				runसमय->silence_start = new_hw_ptr;
			पूर्ण अन्यथा अणु
				runसमय->silence_start = ofs;
			पूर्ण
		पूर्ण
		frames = runसमय->buffer_size - runसमय->silence_filled;
	पूर्ण
	अगर (snd_BUG_ON(frames > runसमय->buffer_size))
		वापस;
	अगर (frames == 0)
		वापस;
	ofs = runसमय->silence_start % runसमय->buffer_size;
	जबतक (frames > 0) अणु
		transfer = ofs + frames > runसमय->buffer_size ? runसमय->buffer_size - ofs : frames;
		err = fill_silence_frames(substream, ofs, transfer);
		snd_BUG_ON(err < 0);
		runसमय->silence_filled += transfer;
		frames -= transfer;
		ofs = 0;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SND_DEBUG
व्योम snd_pcm_debug_name(काष्ठा snd_pcm_substream *substream,
			   अक्षर *name, माप_प्रकार len)
अणु
	snम_लिखो(name, len, "pcmC%dD%d%c:%d",
		 substream->pcm->card->number,
		 substream->pcm->device,
		 substream->stream ? 'c' : 'p',
		 substream->number);
पूर्ण
EXPORT_SYMBOL(snd_pcm_debug_name);
#पूर्ण_अगर

#घोषणा XRUN_DEBUG_BASIC	(1<<0)
#घोषणा XRUN_DEBUG_STACK	(1<<1)	/* dump also stack */
#घोषणा XRUN_DEBUG_JIFFIESCHECK	(1<<2)	/* करो jअगरfies check */

#अगर_घोषित CONFIG_SND_PCM_XRUN_DEBUG

#घोषणा xrun_debug(substream, mask) \
			((substream)->pstr->xrun_debug & (mask))
#अन्यथा
#घोषणा xrun_debug(substream, mask)	0
#पूर्ण_अगर

#घोषणा dump_stack_on_xrun(substream) करो अणु			\
		अगर (xrun_debug(substream, XRUN_DEBUG_STACK))	\
			dump_stack();				\
	पूर्ण जबतक (0)

/* call with stream lock held */
व्योम __snd_pcm_xrun(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	trace_xrun(substream);
	अगर (runसमय->tstamp_mode == SNDRV_PCM_TSTAMP_ENABLE) अणु
		काष्ठा बारpec64 tstamp;

		snd_pcm_समय_लो(runसमय, &tstamp);
		runसमय->status->tstamp.tv_sec = tstamp.tv_sec;
		runसमय->status->tstamp.tv_nsec = tstamp.tv_nsec;
	पूर्ण
	snd_pcm_stop(substream, SNDRV_PCM_STATE_XRUN);
	अगर (xrun_debug(substream, XRUN_DEBUG_BASIC)) अणु
		अक्षर name[16];
		snd_pcm_debug_name(substream, name, माप(name));
		pcm_warn(substream->pcm, "XRUN: %s\n", name);
		dump_stack_on_xrun(substream);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SND_PCM_XRUN_DEBUG
#घोषणा hw_ptr_error(substream, in_पूर्णांकerrupt, reason, fmt, args...)	\
	करो अणु								\
		trace_hw_ptr_error(substream, reason);	\
		अगर (xrun_debug(substream, XRUN_DEBUG_BASIC)) अणु		\
			pr_err_ratelimited("ALSA: PCM: [%c] " reason ": " fmt, \
					   (in_पूर्णांकerrupt) ? 'Q' : 'P', ##args);	\
			dump_stack_on_xrun(substream);			\
		पूर्ण							\
	पूर्ण जबतक (0)

#अन्यथा /* ! CONFIG_SND_PCM_XRUN_DEBUG */

#घोषणा hw_ptr_error(substream, fmt, args...) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

पूर्णांक snd_pcm_update_state(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_runसमय *runसमय)
अणु
	snd_pcm_uframes_t avail;

	avail = snd_pcm_avail(substream);
	अगर (avail > runसमय->avail_max)
		runसमय->avail_max = avail;
	अगर (runसमय->status->state == SNDRV_PCM_STATE_DRAINING) अणु
		अगर (avail >= runसमय->buffer_size) अणु
			snd_pcm_drain_करोne(substream);
			वापस -EPIPE;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (avail >= runसमय->stop_threshold) अणु
			__snd_pcm_xrun(substream);
			वापस -EPIPE;
		पूर्ण
	पूर्ण
	अगर (runसमय->twake) अणु
		अगर (avail >= runसमय->twake)
			wake_up(&runसमय->tsleep);
	पूर्ण अन्यथा अगर (avail >= runसमय->control->avail_min)
		wake_up(&runसमय->sleep);
	वापस 0;
पूर्ण

अटल व्योम update_audio_tstamp(काष्ठा snd_pcm_substream *substream,
				काष्ठा बारpec64 *curr_tstamp,
				काष्ठा बारpec64 *audio_tstamp)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	u64 audio_frames, audio_nsecs;
	काष्ठा बारpec64 driver_tstamp;

	अगर (runसमय->tstamp_mode != SNDRV_PCM_TSTAMP_ENABLE)
		वापस;

	अगर (!(substream->ops->get_समय_info) ||
		(runसमय->audio_tstamp_report.actual_type ==
			SNDRV_PCM_AUDIO_TSTAMP_TYPE_DEFAULT)) अणु

		/*
		 * provide audio बारtamp derived from poपूर्णांकer position
		 * add delay only अगर requested
		 */

		audio_frames = runसमय->hw_ptr_wrap + runसमय->status->hw_ptr;

		अगर (runसमय->audio_tstamp_config.report_delay) अणु
			अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
				audio_frames -=  runसमय->delay;
			अन्यथा
				audio_frames +=  runसमय->delay;
		पूर्ण
		audio_nsecs = भाग_u64(audio_frames * 1000000000LL,
				runसमय->rate);
		*audio_tstamp = ns_to_बारpec64(audio_nsecs);
	पूर्ण

	अगर (runसमय->status->audio_tstamp.tv_sec != audio_tstamp->tv_sec ||
	    runसमय->status->audio_tstamp.tv_nsec != audio_tstamp->tv_nsec) अणु
		runसमय->status->audio_tstamp.tv_sec = audio_tstamp->tv_sec;
		runसमय->status->audio_tstamp.tv_nsec = audio_tstamp->tv_nsec;
		runसमय->status->tstamp.tv_sec = curr_tstamp->tv_sec;
		runसमय->status->tstamp.tv_nsec = curr_tstamp->tv_nsec;
	पूर्ण


	/*
	 * re-take a driver बारtamp to let apps detect अगर the reference tstamp
	 * पढ़ो by low-level hardware was provided with a delay
	 */
	snd_pcm_समय_लो(substream->runसमय, &driver_tstamp);
	runसमय->driver_tstamp = driver_tstamp;
पूर्ण

अटल पूर्णांक snd_pcm_update_hw_ptr0(काष्ठा snd_pcm_substream *substream,
				  अचिन्हित पूर्णांक in_पूर्णांकerrupt)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_uframes_t pos;
	snd_pcm_uframes_t old_hw_ptr, new_hw_ptr, hw_base;
	snd_pcm_sframes_t hdelta, delta;
	अचिन्हित दीर्घ jdelta;
	अचिन्हित दीर्घ curr_jअगरfies;
	काष्ठा बारpec64 curr_tstamp;
	काष्ठा बारpec64 audio_tstamp;
	पूर्णांक crossed_boundary = 0;

	old_hw_ptr = runसमय->status->hw_ptr;

	/*
	 * group poपूर्णांकer, समय and jअगरfies पढ़ोs to allow क्रम more
	 * accurate correlations/corrections.
	 * The values are stored at the end of this routine after
	 * corrections क्रम hw_ptr position
	 */
	pos = substream->ops->poपूर्णांकer(substream);
	curr_jअगरfies = jअगरfies;
	अगर (runसमय->tstamp_mode == SNDRV_PCM_TSTAMP_ENABLE) अणु
		अगर ((substream->ops->get_समय_info) &&
			(runसमय->audio_tstamp_config.type_requested != SNDRV_PCM_AUDIO_TSTAMP_TYPE_DEFAULT)) अणु
			substream->ops->get_समय_info(substream, &curr_tstamp,
						&audio_tstamp,
						&runसमय->audio_tstamp_config,
						&runसमय->audio_tstamp_report);

			/* re-test in हाल tstamp type is not supported in hardware and was demoted to DEFAULT */
			अगर (runसमय->audio_tstamp_report.actual_type == SNDRV_PCM_AUDIO_TSTAMP_TYPE_DEFAULT)
				snd_pcm_समय_लो(runसमय, &curr_tstamp);
		पूर्ण अन्यथा
			snd_pcm_समय_लो(runसमय, &curr_tstamp);
	पूर्ण

	अगर (pos == SNDRV_PCM_POS_XRUN) अणु
		__snd_pcm_xrun(substream);
		वापस -EPIPE;
	पूर्ण
	अगर (pos >= runसमय->buffer_size) अणु
		अगर (prपूर्णांकk_ratelimit()) अणु
			अक्षर name[16];
			snd_pcm_debug_name(substream, name, माप(name));
			pcm_err(substream->pcm,
				"invalid position: %s, pos = %ld, buffer size = %ld, period size = %ld\n",
				name, pos, runसमय->buffer_size,
				runसमय->period_size);
		पूर्ण
		pos = 0;
	पूर्ण
	pos -= pos % runसमय->min_align;
	trace_hwptr(substream, pos, in_पूर्णांकerrupt);
	hw_base = runसमय->hw_ptr_base;
	new_hw_ptr = hw_base + pos;
	अगर (in_पूर्णांकerrupt) अणु
		/* we know that one period was processed */
		/* delta = "expected next hw_ptr" क्रम in_पूर्णांकerrupt != 0 */
		delta = runसमय->hw_ptr_पूर्णांकerrupt + runसमय->period_size;
		अगर (delta > new_hw_ptr) अणु
			/* check क्रम द्विगुन acknowledged पूर्णांकerrupts */
			hdelta = curr_jअगरfies - runसमय->hw_ptr_jअगरfies;
			अगर (hdelta > runसमय->hw_ptr_buffer_jअगरfies/2 + 1) अणु
				hw_base += runसमय->buffer_size;
				अगर (hw_base >= runसमय->boundary) अणु
					hw_base = 0;
					crossed_boundary++;
				पूर्ण
				new_hw_ptr = hw_base + pos;
				जाओ __delta;
			पूर्ण
		पूर्ण
	पूर्ण
	/* new_hw_ptr might be lower than old_hw_ptr in हाल when */
	/* poपूर्णांकer crosses the end of the ring buffer */
	अगर (new_hw_ptr < old_hw_ptr) अणु
		hw_base += runसमय->buffer_size;
		अगर (hw_base >= runसमय->boundary) अणु
			hw_base = 0;
			crossed_boundary++;
		पूर्ण
		new_hw_ptr = hw_base + pos;
	पूर्ण
      __delta:
	delta = new_hw_ptr - old_hw_ptr;
	अगर (delta < 0)
		delta += runसमय->boundary;

	अगर (runसमय->no_period_wakeup) अणु
		snd_pcm_sframes_t xrun_threshold;
		/*
		 * Without regular period पूर्णांकerrupts, we have to check
		 * the elapsed समय to detect xruns.
		 */
		jdelta = curr_jअगरfies - runसमय->hw_ptr_jअगरfies;
		अगर (jdelta < runसमय->hw_ptr_buffer_jअगरfies / 2)
			जाओ no_delta_check;
		hdelta = jdelta - delta * HZ / runसमय->rate;
		xrun_threshold = runसमय->hw_ptr_buffer_jअगरfies / 2 + 1;
		जबतक (hdelta > xrun_threshold) अणु
			delta += runसमय->buffer_size;
			hw_base += runसमय->buffer_size;
			अगर (hw_base >= runसमय->boundary) अणु
				hw_base = 0;
				crossed_boundary++;
			पूर्ण
			new_hw_ptr = hw_base + pos;
			hdelta -= runसमय->hw_ptr_buffer_jअगरfies;
		पूर्ण
		जाओ no_delta_check;
	पूर्ण

	/* something must be really wrong */
	अगर (delta >= runसमय->buffer_size + runसमय->period_size) अणु
		hw_ptr_error(substream, in_पूर्णांकerrupt, "Unexpected hw_ptr",
			     "(stream=%i, pos=%ld, new_hw_ptr=%ld, old_hw_ptr=%ld)\n",
			     substream->stream, (दीर्घ)pos,
			     (दीर्घ)new_hw_ptr, (दीर्घ)old_hw_ptr);
		वापस 0;
	पूर्ण

	/* Do jअगरfies check only in xrun_debug mode */
	अगर (!xrun_debug(substream, XRUN_DEBUG_JIFFIESCHECK))
		जाओ no_jअगरfies_check;

	/* Skip the jअगरfies check क्रम hardwares with BATCH flag.
	 * Such hardware usually just increases the position at each IRQ,
	 * thus it can't give any strange position.
	 */
	अगर (runसमय->hw.info & SNDRV_PCM_INFO_BATCH)
		जाओ no_jअगरfies_check;
	hdelta = delta;
	अगर (hdelta < runसमय->delay)
		जाओ no_jअगरfies_check;
	hdelta -= runसमय->delay;
	jdelta = curr_jअगरfies - runसमय->hw_ptr_jअगरfies;
	अगर (((hdelta * HZ) / runसमय->rate) > jdelta + HZ/100) अणु
		delta = jdelta /
			(((runसमय->period_size * HZ) / runसमय->rate)
								+ HZ/100);
		/* move new_hw_ptr according jअगरfies not pos variable */
		new_hw_ptr = old_hw_ptr;
		hw_base = delta;
		/* use loop to aव्योम checks क्रम delta overflows */
		/* the delta value is small or zero in most हालs */
		जबतक (delta > 0) अणु
			new_hw_ptr += runसमय->period_size;
			अगर (new_hw_ptr >= runसमय->boundary) अणु
				new_hw_ptr -= runसमय->boundary;
				crossed_boundary--;
			पूर्ण
			delta--;
		पूर्ण
		/* align hw_base to buffer_size */
		hw_ptr_error(substream, in_पूर्णांकerrupt, "hw_ptr skipping",
			     "(pos=%ld, delta=%ld, period=%ld, jdelta=%lu/%lu/%lu, hw_ptr=%ld/%ld)\n",
			     (दीर्घ)pos, (दीर्घ)hdelta,
			     (दीर्घ)runसमय->period_size, jdelta,
			     ((hdelta * HZ) / runसमय->rate), hw_base,
			     (अचिन्हित दीर्घ)old_hw_ptr,
			     (अचिन्हित दीर्घ)new_hw_ptr);
		/* reset values to proper state */
		delta = 0;
		hw_base = new_hw_ptr - (new_hw_ptr % runसमय->buffer_size);
	पूर्ण
 no_jअगरfies_check:
	अगर (delta > runसमय->period_size + runसमय->period_size / 2) अणु
		hw_ptr_error(substream, in_पूर्णांकerrupt,
			     "Lost interrupts?",
			     "(stream=%i, delta=%ld, new_hw_ptr=%ld, old_hw_ptr=%ld)\n",
			     substream->stream, (दीर्घ)delta,
			     (दीर्घ)new_hw_ptr,
			     (दीर्घ)old_hw_ptr);
	पूर्ण

 no_delta_check:
	अगर (runसमय->status->hw_ptr == new_hw_ptr) अणु
		runसमय->hw_ptr_jअगरfies = curr_jअगरfies;
		update_audio_tstamp(substream, &curr_tstamp, &audio_tstamp);
		वापस 0;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
	    runसमय->silence_size > 0)
		snd_pcm_playback_silence(substream, new_hw_ptr);

	अगर (in_पूर्णांकerrupt) अणु
		delta = new_hw_ptr - runसमय->hw_ptr_पूर्णांकerrupt;
		अगर (delta < 0)
			delta += runसमय->boundary;
		delta -= (snd_pcm_uframes_t)delta % runसमय->period_size;
		runसमय->hw_ptr_पूर्णांकerrupt += delta;
		अगर (runसमय->hw_ptr_पूर्णांकerrupt >= runसमय->boundary)
			runसमय->hw_ptr_पूर्णांकerrupt -= runसमय->boundary;
	पूर्ण
	runसमय->hw_ptr_base = hw_base;
	runसमय->status->hw_ptr = new_hw_ptr;
	runसमय->hw_ptr_jअगरfies = curr_jअगरfies;
	अगर (crossed_boundary) अणु
		snd_BUG_ON(crossed_boundary != 1);
		runसमय->hw_ptr_wrap += runसमय->boundary;
	पूर्ण

	update_audio_tstamp(substream, &curr_tstamp, &audio_tstamp);

	वापस snd_pcm_update_state(substream, runसमय);
पूर्ण

/* CAUTION: call it with irq disabled */
पूर्णांक snd_pcm_update_hw_ptr(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_update_hw_ptr0(substream, 0);
पूर्ण

/**
 * snd_pcm_set_ops - set the PCM चालकs
 * @pcm: the pcm instance
 * @direction: stream direction, SNDRV_PCM_STREAM_XXX
 * @ops: the चालक table
 *
 * Sets the given PCM चालकs to the pcm instance.
 */
व्योम snd_pcm_set_ops(काष्ठा snd_pcm *pcm, पूर्णांक direction,
		     स्थिर काष्ठा snd_pcm_ops *ops)
अणु
	काष्ठा snd_pcm_str *stream = &pcm->streams[direction];
	काष्ठा snd_pcm_substream *substream;
	
	क्रम (substream = stream->substream; substream != शून्य; substream = substream->next)
		substream->ops = ops;
पूर्ण
EXPORT_SYMBOL(snd_pcm_set_ops);

/**
 * snd_pcm_set_sync - set the PCM sync id
 * @substream: the pcm substream
 *
 * Sets the PCM sync identअगरier क्रम the card.
 */
व्योम snd_pcm_set_sync(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	
	runसमय->sync.id32[0] = substream->pcm->card->number;
	runसमय->sync.id32[1] = -1;
	runसमय->sync.id32[2] = -1;
	runसमय->sync.id32[3] = -1;
पूर्ण
EXPORT_SYMBOL(snd_pcm_set_sync);

/*
 *  Standard ioctl routine
 */

अटल अंतरभूत अचिन्हित पूर्णांक भाग32(अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b, 
				 अचिन्हित पूर्णांक *r)
अणु
	अगर (b == 0) अणु
		*r = 0;
		वापस अच_पूर्णांक_उच्च;
	पूर्ण
	*r = a % b;
	वापस a / b;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक भाग_करोwn(अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)
अणु
	अगर (b == 0)
		वापस अच_पूर्णांक_उच्च;
	वापस a / b;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक भाग_up(अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)
अणु
	अचिन्हित पूर्णांक r;
	अचिन्हित पूर्णांक q;
	अगर (b == 0)
		वापस अच_पूर्णांक_उच्च;
	q = भाग32(a, b, &r);
	अगर (r)
		++q;
	वापस q;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mul(अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)
अणु
	अगर (a == 0)
		वापस 0;
	अगर (भाग_करोwn(अच_पूर्णांक_उच्च, a) < b)
		वापस अच_पूर्णांक_उच्च;
	वापस a * b;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक muद_भाग32(अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b,
				    अचिन्हित पूर्णांक c, अचिन्हित पूर्णांक *r)
अणु
	u_पूर्णांक64_t n = (u_पूर्णांक64_t) a * b;
	अगर (c == 0) अणु
		*r = 0;
		वापस अच_पूर्णांक_उच्च;
	पूर्ण
	n = भाग_u64_rem(n, c, r);
	अगर (n >= अच_पूर्णांक_उच्च) अणु
		*r = 0;
		वापस अच_पूर्णांक_उच्च;
	पूर्ण
	वापस n;
पूर्ण

/**
 * snd_पूर्णांकerval_refine - refine the पूर्णांकerval value of configurator
 * @i: the पूर्णांकerval value to refine
 * @v: the पूर्णांकerval value to refer to
 *
 * Refines the पूर्णांकerval value with the reference value.
 * The पूर्णांकerval is changed to the range satisfying both पूर्णांकervals.
 * The पूर्णांकerval status (min, max, पूर्णांकeger, etc.) are evaluated.
 *
 * Return: Positive अगर the value is changed, zero अगर it's not changed, or a
 * negative error code.
 */
पूर्णांक snd_पूर्णांकerval_refine(काष्ठा snd_पूर्णांकerval *i, स्थिर काष्ठा snd_पूर्णांकerval *v)
अणु
	पूर्णांक changed = 0;
	अगर (snd_BUG_ON(snd_पूर्णांकerval_empty(i)))
		वापस -EINVAL;
	अगर (i->min < v->min) अणु
		i->min = v->min;
		i->खोलोmin = v->खोलोmin;
		changed = 1;
	पूर्ण अन्यथा अगर (i->min == v->min && !i->खोलोmin && v->खोलोmin) अणु
		i->खोलोmin = 1;
		changed = 1;
	पूर्ण
	अगर (i->max > v->max) अणु
		i->max = v->max;
		i->खोलोmax = v->खोलोmax;
		changed = 1;
	पूर्ण अन्यथा अगर (i->max == v->max && !i->खोलोmax && v->खोलोmax) अणु
		i->खोलोmax = 1;
		changed = 1;
	पूर्ण
	अगर (!i->पूर्णांकeger && v->पूर्णांकeger) अणु
		i->पूर्णांकeger = 1;
		changed = 1;
	पूर्ण
	अगर (i->पूर्णांकeger) अणु
		अगर (i->खोलोmin) अणु
			i->min++;
			i->खोलोmin = 0;
		पूर्ण
		अगर (i->खोलोmax) अणु
			i->max--;
			i->खोलोmax = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (!i->खोलोmin && !i->खोलोmax && i->min == i->max)
		i->पूर्णांकeger = 1;
	अगर (snd_पूर्णांकerval_checkempty(i)) अणु
		snd_पूर्णांकerval_none(i);
		वापस -EINVAL;
	पूर्ण
	वापस changed;
पूर्ण
EXPORT_SYMBOL(snd_पूर्णांकerval_refine);

अटल पूर्णांक snd_पूर्णांकerval_refine_first(काष्ठा snd_पूर्णांकerval *i)
अणु
	स्थिर अचिन्हित पूर्णांक last_max = i->max;

	अगर (snd_BUG_ON(snd_पूर्णांकerval_empty(i)))
		वापस -EINVAL;
	अगर (snd_पूर्णांकerval_single(i))
		वापस 0;
	i->max = i->min;
	अगर (i->खोलोmin)
		i->max++;
	/* only exclude max value अगर also excluded beक्रमe refine */
	i->खोलोmax = (i->खोलोmax && i->max >= last_max);
	वापस 1;
पूर्ण

अटल पूर्णांक snd_पूर्णांकerval_refine_last(काष्ठा snd_पूर्णांकerval *i)
अणु
	स्थिर अचिन्हित पूर्णांक last_min = i->min;

	अगर (snd_BUG_ON(snd_पूर्णांकerval_empty(i)))
		वापस -EINVAL;
	अगर (snd_पूर्णांकerval_single(i))
		वापस 0;
	i->min = i->max;
	अगर (i->खोलोmax)
		i->min--;
	/* only exclude min value अगर also excluded beक्रमe refine */
	i->खोलोmin = (i->खोलोmin && i->min <= last_min);
	वापस 1;
पूर्ण

व्योम snd_पूर्णांकerval_mul(स्थिर काष्ठा snd_पूर्णांकerval *a, स्थिर काष्ठा snd_पूर्णांकerval *b, काष्ठा snd_पूर्णांकerval *c)
अणु
	अगर (a->empty || b->empty) अणु
		snd_पूर्णांकerval_none(c);
		वापस;
	पूर्ण
	c->empty = 0;
	c->min = mul(a->min, b->min);
	c->खोलोmin = (a->खोलोmin || b->खोलोmin);
	c->max = mul(a->max,  b->max);
	c->खोलोmax = (a->खोलोmax || b->खोलोmax);
	c->पूर्णांकeger = (a->पूर्णांकeger && b->पूर्णांकeger);
पूर्ण

/**
 * snd_पूर्णांकerval_भाग - refine the पूर्णांकerval value with भागision
 * @a: भागidend
 * @b: भागisor
 * @c: quotient
 *
 * c = a / b
 *
 * Returns non-zero अगर the value is changed, zero अगर not changed.
 */
व्योम snd_पूर्णांकerval_भाग(स्थिर काष्ठा snd_पूर्णांकerval *a, स्थिर काष्ठा snd_पूर्णांकerval *b, काष्ठा snd_पूर्णांकerval *c)
अणु
	अचिन्हित पूर्णांक r;
	अगर (a->empty || b->empty) अणु
		snd_पूर्णांकerval_none(c);
		वापस;
	पूर्ण
	c->empty = 0;
	c->min = भाग32(a->min, b->max, &r);
	c->खोलोmin = (r || a->खोलोmin || b->खोलोmax);
	अगर (b->min > 0) अणु
		c->max = भाग32(a->max, b->min, &r);
		अगर (r) अणु
			c->max++;
			c->खोलोmax = 1;
		पूर्ण अन्यथा
			c->खोलोmax = (a->खोलोmax || b->खोलोmin);
	पूर्ण अन्यथा अणु
		c->max = अच_पूर्णांक_उच्च;
		c->खोलोmax = 0;
	पूर्ण
	c->पूर्णांकeger = 0;
पूर्ण

/**
 * snd_पूर्णांकerval_muद_भागk - refine the पूर्णांकerval value
 * @a: भागidend 1
 * @b: भागidend 2
 * @k: भागisor (as पूर्णांकeger)
 * @c: result
  *
 * c = a * b / k
 *
 * Returns non-zero अगर the value is changed, zero अगर not changed.
 */
व्योम snd_पूर्णांकerval_muद_भागk(स्थिर काष्ठा snd_पूर्णांकerval *a, स्थिर काष्ठा snd_पूर्णांकerval *b,
		      अचिन्हित पूर्णांक k, काष्ठा snd_पूर्णांकerval *c)
अणु
	अचिन्हित पूर्णांक r;
	अगर (a->empty || b->empty) अणु
		snd_पूर्णांकerval_none(c);
		वापस;
	पूर्ण
	c->empty = 0;
	c->min = muद_भाग32(a->min, b->min, k, &r);
	c->खोलोmin = (r || a->खोलोmin || b->खोलोmin);
	c->max = muद_भाग32(a->max, b->max, k, &r);
	अगर (r) अणु
		c->max++;
		c->खोलोmax = 1;
	पूर्ण अन्यथा
		c->खोलोmax = (a->खोलोmax || b->खोलोmax);
	c->पूर्णांकeger = 0;
पूर्ण

/**
 * snd_पूर्णांकerval_mulkभाग - refine the पूर्णांकerval value
 * @a: भागidend 1
 * @k: भागidend 2 (as पूर्णांकeger)
 * @b: भागisor
 * @c: result
 *
 * c = a * k / b
 *
 * Returns non-zero अगर the value is changed, zero अगर not changed.
 */
व्योम snd_पूर्णांकerval_mulkभाग(स्थिर काष्ठा snd_पूर्णांकerval *a, अचिन्हित पूर्णांक k,
		      स्थिर काष्ठा snd_पूर्णांकerval *b, काष्ठा snd_पूर्णांकerval *c)
अणु
	अचिन्हित पूर्णांक r;
	अगर (a->empty || b->empty) अणु
		snd_पूर्णांकerval_none(c);
		वापस;
	पूर्ण
	c->empty = 0;
	c->min = muद_भाग32(a->min, k, b->max, &r);
	c->खोलोmin = (r || a->खोलोmin || b->खोलोmax);
	अगर (b->min > 0) अणु
		c->max = muद_भाग32(a->max, k, b->min, &r);
		अगर (r) अणु
			c->max++;
			c->खोलोmax = 1;
		पूर्ण अन्यथा
			c->खोलोmax = (a->खोलोmax || b->खोलोmin);
	पूर्ण अन्यथा अणु
		c->max = अच_पूर्णांक_उच्च;
		c->खोलोmax = 0;
	पूर्ण
	c->पूर्णांकeger = 0;
पूर्ण

/* ---- */


/**
 * snd_पूर्णांकerval_ratnum - refine the पूर्णांकerval value
 * @i: पूर्णांकerval to refine
 * @rats_count: number of ratnum_t 
 * @rats: ratnum_t array
 * @nump: poपूर्णांकer to store the resultant numerator
 * @denp: poपूर्णांकer to store the resultant denominator
 *
 * Return: Positive अगर the value is changed, zero अगर it's not changed, or a
 * negative error code.
 */
पूर्णांक snd_पूर्णांकerval_ratnum(काष्ठा snd_पूर्णांकerval *i,
			अचिन्हित पूर्णांक rats_count, स्थिर काष्ठा snd_ratnum *rats,
			अचिन्हित पूर्णांक *nump, अचिन्हित पूर्णांक *denp)
अणु
	अचिन्हित पूर्णांक best_num, best_den;
	पूर्णांक best_dअगरf;
	अचिन्हित पूर्णांक k;
	काष्ठा snd_पूर्णांकerval t;
	पूर्णांक err;
	अचिन्हित पूर्णांक result_num, result_den;
	पूर्णांक result_dअगरf;

	best_num = best_den = best_dअगरf = 0;
	क्रम (k = 0; k < rats_count; ++k) अणु
		अचिन्हित पूर्णांक num = rats[k].num;
		अचिन्हित पूर्णांक den;
		अचिन्हित पूर्णांक q = i->min;
		पूर्णांक dअगरf;
		अगर (q == 0)
			q = 1;
		den = भाग_up(num, q);
		अगर (den < rats[k].den_min)
			जारी;
		अगर (den > rats[k].den_max)
			den = rats[k].den_max;
		अन्यथा अणु
			अचिन्हित पूर्णांक r;
			r = (den - rats[k].den_min) % rats[k].den_step;
			अगर (r != 0)
				den -= r;
		पूर्ण
		dअगरf = num - q * den;
		अगर (dअगरf < 0)
			dअगरf = -dअगरf;
		अगर (best_num == 0 ||
		    dअगरf * best_den < best_dअगरf * den) अणु
			best_dअगरf = dअगरf;
			best_den = den;
			best_num = num;
		पूर्ण
	पूर्ण
	अगर (best_den == 0) अणु
		i->empty = 1;
		वापस -EINVAL;
	पूर्ण
	t.min = भाग_करोwn(best_num, best_den);
	t.खोलोmin = !!(best_num % best_den);
	
	result_num = best_num;
	result_dअगरf = best_dअगरf;
	result_den = best_den;
	best_num = best_den = best_dअगरf = 0;
	क्रम (k = 0; k < rats_count; ++k) अणु
		अचिन्हित पूर्णांक num = rats[k].num;
		अचिन्हित पूर्णांक den;
		अचिन्हित पूर्णांक q = i->max;
		पूर्णांक dअगरf;
		अगर (q == 0) अणु
			i->empty = 1;
			वापस -EINVAL;
		पूर्ण
		den = भाग_करोwn(num, q);
		अगर (den > rats[k].den_max)
			जारी;
		अगर (den < rats[k].den_min)
			den = rats[k].den_min;
		अन्यथा अणु
			अचिन्हित पूर्णांक r;
			r = (den - rats[k].den_min) % rats[k].den_step;
			अगर (r != 0)
				den += rats[k].den_step - r;
		पूर्ण
		dअगरf = q * den - num;
		अगर (dअगरf < 0)
			dअगरf = -dअगरf;
		अगर (best_num == 0 ||
		    dअगरf * best_den < best_dअगरf * den) अणु
			best_dअगरf = dअगरf;
			best_den = den;
			best_num = num;
		पूर्ण
	पूर्ण
	अगर (best_den == 0) अणु
		i->empty = 1;
		वापस -EINVAL;
	पूर्ण
	t.max = भाग_up(best_num, best_den);
	t.खोलोmax = !!(best_num % best_den);
	t.पूर्णांकeger = 0;
	err = snd_पूर्णांकerval_refine(i, &t);
	अगर (err < 0)
		वापस err;

	अगर (snd_पूर्णांकerval_single(i)) अणु
		अगर (best_dअगरf * result_den < result_dअगरf * best_den) अणु
			result_num = best_num;
			result_den = best_den;
		पूर्ण
		अगर (nump)
			*nump = result_num;
		अगर (denp)
			*denp = result_den;
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_पूर्णांकerval_ratnum);

/**
 * snd_पूर्णांकerval_ratden - refine the पूर्णांकerval value
 * @i: पूर्णांकerval to refine
 * @rats_count: number of काष्ठा ratden
 * @rats: काष्ठा ratden array
 * @nump: poपूर्णांकer to store the resultant numerator
 * @denp: poपूर्णांकer to store the resultant denominator
 *
 * Return: Positive अगर the value is changed, zero अगर it's not changed, or a
 * negative error code.
 */
अटल पूर्णांक snd_पूर्णांकerval_ratden(काष्ठा snd_पूर्णांकerval *i,
			       अचिन्हित पूर्णांक rats_count,
			       स्थिर काष्ठा snd_ratden *rats,
			       अचिन्हित पूर्णांक *nump, अचिन्हित पूर्णांक *denp)
अणु
	अचिन्हित पूर्णांक best_num, best_dअगरf, best_den;
	अचिन्हित पूर्णांक k;
	काष्ठा snd_पूर्णांकerval t;
	पूर्णांक err;

	best_num = best_den = best_dअगरf = 0;
	क्रम (k = 0; k < rats_count; ++k) अणु
		अचिन्हित पूर्णांक num;
		अचिन्हित पूर्णांक den = rats[k].den;
		अचिन्हित पूर्णांक q = i->min;
		पूर्णांक dअगरf;
		num = mul(q, den);
		अगर (num > rats[k].num_max)
			जारी;
		अगर (num < rats[k].num_min)
			num = rats[k].num_max;
		अन्यथा अणु
			अचिन्हित पूर्णांक r;
			r = (num - rats[k].num_min) % rats[k].num_step;
			अगर (r != 0)
				num += rats[k].num_step - r;
		पूर्ण
		dअगरf = num - q * den;
		अगर (best_num == 0 ||
		    dअगरf * best_den < best_dअगरf * den) अणु
			best_dअगरf = dअगरf;
			best_den = den;
			best_num = num;
		पूर्ण
	पूर्ण
	अगर (best_den == 0) अणु
		i->empty = 1;
		वापस -EINVAL;
	पूर्ण
	t.min = भाग_करोwn(best_num, best_den);
	t.खोलोmin = !!(best_num % best_den);
	
	best_num = best_den = best_dअगरf = 0;
	क्रम (k = 0; k < rats_count; ++k) अणु
		अचिन्हित पूर्णांक num;
		अचिन्हित पूर्णांक den = rats[k].den;
		अचिन्हित पूर्णांक q = i->max;
		पूर्णांक dअगरf;
		num = mul(q, den);
		अगर (num < rats[k].num_min)
			जारी;
		अगर (num > rats[k].num_max)
			num = rats[k].num_max;
		अन्यथा अणु
			अचिन्हित पूर्णांक r;
			r = (num - rats[k].num_min) % rats[k].num_step;
			अगर (r != 0)
				num -= r;
		पूर्ण
		dअगरf = q * den - num;
		अगर (best_num == 0 ||
		    dअगरf * best_den < best_dअगरf * den) अणु
			best_dअगरf = dअगरf;
			best_den = den;
			best_num = num;
		पूर्ण
	पूर्ण
	अगर (best_den == 0) अणु
		i->empty = 1;
		वापस -EINVAL;
	पूर्ण
	t.max = भाग_up(best_num, best_den);
	t.खोलोmax = !!(best_num % best_den);
	t.पूर्णांकeger = 0;
	err = snd_पूर्णांकerval_refine(i, &t);
	अगर (err < 0)
		वापस err;

	अगर (snd_पूर्णांकerval_single(i)) अणु
		अगर (nump)
			*nump = best_num;
		अगर (denp)
			*denp = best_den;
	पूर्ण
	वापस err;
पूर्ण

/**
 * snd_पूर्णांकerval_list - refine the पूर्णांकerval value from the list
 * @i: the पूर्णांकerval value to refine
 * @count: the number of elements in the list
 * @list: the value list
 * @mask: the bit-mask to evaluate
 *
 * Refines the पूर्णांकerval value from the list.
 * When mask is non-zero, only the elements corresponding to bit 1 are
 * evaluated.
 *
 * Return: Positive अगर the value is changed, zero अगर it's not changed, or a
 * negative error code.
 */
पूर्णांक snd_पूर्णांकerval_list(काष्ठा snd_पूर्णांकerval *i, अचिन्हित पूर्णांक count,
		      स्थिर अचिन्हित पूर्णांक *list, अचिन्हित पूर्णांक mask)
अणु
        अचिन्हित पूर्णांक k;
	काष्ठा snd_पूर्णांकerval list_range;

	अगर (!count) अणु
		i->empty = 1;
		वापस -EINVAL;
	पूर्ण
	snd_पूर्णांकerval_any(&list_range);
	list_range.min = अच_पूर्णांक_उच्च;
	list_range.max = 0;
        क्रम (k = 0; k < count; k++) अणु
		अगर (mask && !(mask & (1 << k)))
			जारी;
		अगर (!snd_पूर्णांकerval_test(i, list[k]))
			जारी;
		list_range.min = min(list_range.min, list[k]);
		list_range.max = max(list_range.max, list[k]);
        पूर्ण
	वापस snd_पूर्णांकerval_refine(i, &list_range);
पूर्ण
EXPORT_SYMBOL(snd_पूर्णांकerval_list);

/**
 * snd_पूर्णांकerval_ranges - refine the पूर्णांकerval value from the list of ranges
 * @i: the पूर्णांकerval value to refine
 * @count: the number of elements in the list of ranges
 * @ranges: the ranges list
 * @mask: the bit-mask to evaluate
 *
 * Refines the पूर्णांकerval value from the list of ranges.
 * When mask is non-zero, only the elements corresponding to bit 1 are
 * evaluated.
 *
 * Return: Positive अगर the value is changed, zero अगर it's not changed, or a
 * negative error code.
 */
पूर्णांक snd_पूर्णांकerval_ranges(काष्ठा snd_पूर्णांकerval *i, अचिन्हित पूर्णांक count,
			स्थिर काष्ठा snd_पूर्णांकerval *ranges, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक k;
	काष्ठा snd_पूर्णांकerval range_जोड़;
	काष्ठा snd_पूर्णांकerval range;

	अगर (!count) अणु
		snd_पूर्णांकerval_none(i);
		वापस -EINVAL;
	पूर्ण
	snd_पूर्णांकerval_any(&range_जोड़);
	range_जोड़.min = अच_पूर्णांक_उच्च;
	range_जोड़.max = 0;
	क्रम (k = 0; k < count; k++) अणु
		अगर (mask && !(mask & (1 << k)))
			जारी;
		snd_पूर्णांकerval_copy(&range, &ranges[k]);
		अगर (snd_पूर्णांकerval_refine(&range, i) < 0)
			जारी;
		अगर (snd_पूर्णांकerval_empty(&range))
			जारी;

		अगर (range.min < range_जोड़.min) अणु
			range_जोड़.min = range.min;
			range_जोड़.खोलोmin = 1;
		पूर्ण
		अगर (range.min == range_जोड़.min && !range.खोलोmin)
			range_जोड़.खोलोmin = 0;
		अगर (range.max > range_जोड़.max) अणु
			range_जोड़.max = range.max;
			range_जोड़.खोलोmax = 1;
		पूर्ण
		अगर (range.max == range_जोड़.max && !range.खोलोmax)
			range_जोड़.खोलोmax = 0;
	पूर्ण
	वापस snd_पूर्णांकerval_refine(i, &range_जोड़);
पूर्ण
EXPORT_SYMBOL(snd_पूर्णांकerval_ranges);

अटल पूर्णांक snd_पूर्णांकerval_step(काष्ठा snd_पूर्णांकerval *i, अचिन्हित पूर्णांक step)
अणु
	अचिन्हित पूर्णांक n;
	पूर्णांक changed = 0;
	n = i->min % step;
	अगर (n != 0 || i->खोलोmin) अणु
		i->min += step - n;
		i->खोलोmin = 0;
		changed = 1;
	पूर्ण
	n = i->max % step;
	अगर (n != 0 || i->खोलोmax) अणु
		i->max -= n;
		i->खोलोmax = 0;
		changed = 1;
	पूर्ण
	अगर (snd_पूर्णांकerval_checkempty(i)) अणु
		i->empty = 1;
		वापस -EINVAL;
	पूर्ण
	वापस changed;
पूर्ण

/* Info स्थिरraपूर्णांकs helpers */

/**
 * snd_pcm_hw_rule_add - add the hw-स्थिरraपूर्णांक rule
 * @runसमय: the pcm runसमय instance
 * @cond: condition bits
 * @var: the variable to evaluate
 * @func: the evaluation function
 * @निजी: the निजी data poपूर्णांकer passed to function
 * @dep: the dependent variables
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_rule_add(काष्ठा snd_pcm_runसमय *runसमय, अचिन्हित पूर्णांक cond,
			पूर्णांक var,
			snd_pcm_hw_rule_func_t func, व्योम *निजी,
			पूर्णांक dep, ...)
अणु
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs *स्थिरrs = &runसमय->hw_स्थिरraपूर्णांकs;
	काष्ठा snd_pcm_hw_rule *c;
	अचिन्हित पूर्णांक k;
	बहु_सूची args;
	बहु_शुरू(args, dep);
	अगर (स्थिरrs->rules_num >= स्थिरrs->rules_all) अणु
		काष्ठा snd_pcm_hw_rule *new;
		अचिन्हित पूर्णांक new_rules = स्थिरrs->rules_all + 16;
		new = kपुनः_स्मृति_array(स्थिरrs->rules, new_rules,
				     माप(*c), GFP_KERNEL);
		अगर (!new) अणु
			बहु_पूर्ण(args);
			वापस -ENOMEM;
		पूर्ण
		स्थिरrs->rules = new;
		स्थिरrs->rules_all = new_rules;
	पूर्ण
	c = &स्थिरrs->rules[स्थिरrs->rules_num];
	c->cond = cond;
	c->func = func;
	c->var = var;
	c->निजी = निजी;
	k = 0;
	जबतक (1) अणु
		अगर (snd_BUG_ON(k >= ARRAY_SIZE(c->deps))) अणु
			बहु_पूर्ण(args);
			वापस -EINVAL;
		पूर्ण
		c->deps[k++] = dep;
		अगर (dep < 0)
			अवरोध;
		dep = बहु_तर्क(args, पूर्णांक);
	पूर्ण
	स्थिरrs->rules_num++;
	बहु_पूर्ण(args);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_rule_add);

/**
 * snd_pcm_hw_स्थिरraपूर्णांक_mask - apply the given biपंचांगap mask स्थिरraपूर्णांक
 * @runसमय: PCM runसमय instance
 * @var: hw_params variable to apply the mask
 * @mask: the biपंचांगap mask
 *
 * Apply the स्थिरraपूर्णांक of the given biपंचांगap mask to a 32-bit mask parameter.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_mask(काष्ठा snd_pcm_runसमय *runसमय, snd_pcm_hw_param_t var,
			       u_पूर्णांक32_t mask)
अणु
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs *स्थिरrs = &runसमय->hw_स्थिरraपूर्णांकs;
	काष्ठा snd_mask *maskp = स्थिरrs_mask(स्थिरrs, var);
	*maskp->bits &= mask;
	स_रखो(maskp->bits + 1, 0, (SNDRV_MASK_MAX-32) / 8); /* clear rest */
	अगर (*maskp->bits == 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**
 * snd_pcm_hw_स्थिरraपूर्णांक_mask64 - apply the given biपंचांगap mask स्थिरraपूर्णांक
 * @runसमय: PCM runसमय instance
 * @var: hw_params variable to apply the mask
 * @mask: the 64bit biपंचांगap mask
 *
 * Apply the स्थिरraपूर्णांक of the given biपंचांगap mask to a 64-bit mask parameter.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_mask64(काष्ठा snd_pcm_runसमय *runसमय, snd_pcm_hw_param_t var,
				 u_पूर्णांक64_t mask)
अणु
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs *स्थिरrs = &runसमय->hw_स्थिरraपूर्णांकs;
	काष्ठा snd_mask *maskp = स्थिरrs_mask(स्थिरrs, var);
	maskp->bits[0] &= (u_पूर्णांक32_t)mask;
	maskp->bits[1] &= (u_पूर्णांक32_t)(mask >> 32);
	स_रखो(maskp->bits + 2, 0, (SNDRV_MASK_MAX-64) / 8); /* clear rest */
	अगर (! maskp->bits[0] && ! maskp->bits[1])
		वापस -EINVAL;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_स्थिरraपूर्णांक_mask64);

/**
 * snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger - apply an पूर्णांकeger स्थिरraपूर्णांक to an पूर्णांकerval
 * @runसमय: PCM runसमय instance
 * @var: hw_params variable to apply the पूर्णांकeger स्थिरraपूर्णांक
 *
 * Apply the स्थिरraपूर्णांक of पूर्णांकeger to an पूर्णांकerval parameter.
 *
 * Return: Positive अगर the value is changed, zero अगर it's not changed, or a
 * negative error code.
 */
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(काष्ठा snd_pcm_runसमय *runसमय, snd_pcm_hw_param_t var)
अणु
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs *स्थिरrs = &runसमय->hw_स्थिरraपूर्णांकs;
	वापस snd_पूर्णांकerval_setपूर्णांकeger(स्थिरrs_पूर्णांकerval(स्थिरrs, var));
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger);

/**
 * snd_pcm_hw_स्थिरraपूर्णांक_minmax - apply a min/max range स्थिरraपूर्णांक to an पूर्णांकerval
 * @runसमय: PCM runसमय instance
 * @var: hw_params variable to apply the range
 * @min: the minimal value
 * @max: the maximal value
 * 
 * Apply the min/max range स्थिरraपूर्णांक to an पूर्णांकerval parameter.
 *
 * Return: Positive अगर the value is changed, zero अगर it's not changed, or a
 * negative error code.
 */
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_minmax(काष्ठा snd_pcm_runसमय *runसमय, snd_pcm_hw_param_t var,
				 अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max)
अणु
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांकs *स्थिरrs = &runसमय->hw_स्थिरraपूर्णांकs;
	काष्ठा snd_पूर्णांकerval t;
	t.min = min;
	t.max = max;
	t.खोलोmin = t.खोलोmax = 0;
	t.पूर्णांकeger = 0;
	वापस snd_पूर्णांकerval_refine(स्थिरrs_पूर्णांकerval(स्थिरrs, var), &t);
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_स्थिरraपूर्णांक_minmax);

अटल पूर्णांक snd_pcm_hw_rule_list(काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *list = rule->निजी;
	वापस snd_पूर्णांकerval_list(hw_param_पूर्णांकerval(params, rule->var), list->count, list->list, list->mask);
पूर्ण		


/**
 * snd_pcm_hw_स्थिरraपूर्णांक_list - apply a list of स्थिरraपूर्णांकs to a parameter
 * @runसमय: PCM runसमय instance
 * @cond: condition bits
 * @var: hw_params variable to apply the list स्थिरraपूर्णांक
 * @l: list
 * 
 * Apply the list of स्थिरraपूर्णांकs to an पूर्णांकerval parameter.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_list(काष्ठा snd_pcm_runसमय *runसमय,
			       अचिन्हित पूर्णांक cond,
			       snd_pcm_hw_param_t var,
			       स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *l)
अणु
	वापस snd_pcm_hw_rule_add(runसमय, cond, var,
				   snd_pcm_hw_rule_list, (व्योम *)l,
				   var, -1);
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_स्थिरraपूर्णांक_list);

अटल पूर्णांक snd_pcm_hw_rule_ranges(काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ranges *r = rule->निजी;
	वापस snd_पूर्णांकerval_ranges(hw_param_पूर्णांकerval(params, rule->var),
				   r->count, r->ranges, r->mask);
पूर्ण


/**
 * snd_pcm_hw_स्थिरraपूर्णांक_ranges - apply list of range स्थिरraपूर्णांकs to a parameter
 * @runसमय: PCM runसमय instance
 * @cond: condition bits
 * @var: hw_params variable to apply the list of range स्थिरraपूर्णांकs
 * @r: ranges
 *
 * Apply the list of range स्थिरraपूर्णांकs to an पूर्णांकerval parameter.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_ranges(काष्ठा snd_pcm_runसमय *runसमय,
				 अचिन्हित पूर्णांक cond,
				 snd_pcm_hw_param_t var,
				 स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ranges *r)
अणु
	वापस snd_pcm_hw_rule_add(runसमय, cond, var,
				   snd_pcm_hw_rule_ranges, (व्योम *)r,
				   var, -1);
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_स्थिरraपूर्णांक_ranges);

अटल पूर्णांक snd_pcm_hw_rule_ratnums(काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_pcm_hw_rule *rule)
अणु
	स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums *r = rule->निजी;
	अचिन्हित पूर्णांक num = 0, den = 0;
	पूर्णांक err;
	err = snd_पूर्णांकerval_ratnum(hw_param_पूर्णांकerval(params, rule->var),
				  r->nrats, r->rats, &num, &den);
	अगर (err >= 0 && den && rule->var == SNDRV_PCM_HW_PARAM_RATE) अणु
		params->rate_num = num;
		params->rate_den = den;
	पूर्ण
	वापस err;
पूर्ण

/**
 * snd_pcm_hw_स्थिरraपूर्णांक_ratnums - apply ratnums स्थिरraपूर्णांक to a parameter
 * @runसमय: PCM runसमय instance
 * @cond: condition bits
 * @var: hw_params variable to apply the ratnums स्थिरraपूर्णांक
 * @r: काष्ठा snd_ratnums स्थिरriants
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_ratnums(काष्ठा snd_pcm_runसमय *runसमय, 
				  अचिन्हित पूर्णांक cond,
				  snd_pcm_hw_param_t var,
				  स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums *r)
अणु
	वापस snd_pcm_hw_rule_add(runसमय, cond, var,
				   snd_pcm_hw_rule_ratnums, (व्योम *)r,
				   var, -1);
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_स्थिरraपूर्णांक_ratnums);

अटल पूर्णांक snd_pcm_hw_rule_ratdens(काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_pcm_hw_rule *rule)
अणु
	स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratdens *r = rule->निजी;
	अचिन्हित पूर्णांक num = 0, den = 0;
	पूर्णांक err = snd_पूर्णांकerval_ratden(hw_param_पूर्णांकerval(params, rule->var),
				  r->nrats, r->rats, &num, &den);
	अगर (err >= 0 && den && rule->var == SNDRV_PCM_HW_PARAM_RATE) अणु
		params->rate_num = num;
		params->rate_den = den;
	पूर्ण
	वापस err;
पूर्ण

/**
 * snd_pcm_hw_स्थिरraपूर्णांक_ratdens - apply ratdens स्थिरraपूर्णांक to a parameter
 * @runसमय: PCM runसमय instance
 * @cond: condition bits
 * @var: hw_params variable to apply the ratdens स्थिरraपूर्णांक
 * @r: काष्ठा snd_ratdens स्थिरriants
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_ratdens(काष्ठा snd_pcm_runसमय *runसमय, 
				  अचिन्हित पूर्णांक cond,
				  snd_pcm_hw_param_t var,
				  स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratdens *r)
अणु
	वापस snd_pcm_hw_rule_add(runसमय, cond, var,
				   snd_pcm_hw_rule_ratdens, (व्योम *)r,
				   var, -1);
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_स्थिरraपूर्णांक_ratdens);

अटल पूर्णांक snd_pcm_hw_rule_msbits(काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_pcm_hw_rule *rule)
अणु
	अचिन्हित पूर्णांक l = (अचिन्हित दीर्घ) rule->निजी;
	पूर्णांक width = l & 0xffff;
	अचिन्हित पूर्णांक msbits = l >> 16;
	स्थिर काष्ठा snd_पूर्णांकerval *i =
		hw_param_पूर्णांकerval_c(params, SNDRV_PCM_HW_PARAM_SAMPLE_BITS);

	अगर (!snd_पूर्णांकerval_single(i))
		वापस 0;

	अगर ((snd_पूर्णांकerval_value(i) == width) ||
	    (width == 0 && snd_पूर्णांकerval_value(i) > msbits))
		params->msbits = min_not_zero(params->msbits, msbits);

	वापस 0;
पूर्ण

/**
 * snd_pcm_hw_स्थिरraपूर्णांक_msbits - add a hw स्थिरraपूर्णांक msbits rule
 * @runसमय: PCM runसमय instance
 * @cond: condition bits
 * @width: sample bits width
 * @msbits: msbits width
 *
 * This स्थिरraपूर्णांक will set the number of most signअगरicant bits (msbits) अगर a
 * sample क्रमmat with the specअगरied width has been select. If width is set to 0
 * the msbits will be set क्रम any sample क्रमmat with a width larger than the
 * specअगरied msbits.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_msbits(काष्ठा snd_pcm_runसमय *runसमय, 
				 अचिन्हित पूर्णांक cond,
				 अचिन्हित पूर्णांक width,
				 अचिन्हित पूर्णांक msbits)
अणु
	अचिन्हित दीर्घ l = (msbits << 16) | width;
	वापस snd_pcm_hw_rule_add(runसमय, cond, -1,
				    snd_pcm_hw_rule_msbits,
				    (व्योम*) l,
				    SNDRV_PCM_HW_PARAM_SAMPLE_BITS, -1);
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_स्थिरraपूर्णांक_msbits);

अटल पूर्णांक snd_pcm_hw_rule_step(काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_pcm_hw_rule *rule)
अणु
	अचिन्हित दीर्घ step = (अचिन्हित दीर्घ) rule->निजी;
	वापस snd_पूर्णांकerval_step(hw_param_पूर्णांकerval(params, rule->var), step);
पूर्ण

/**
 * snd_pcm_hw_स्थिरraपूर्णांक_step - add a hw स्थिरraपूर्णांक step rule
 * @runसमय: PCM runसमय instance
 * @cond: condition bits
 * @var: hw_params variable to apply the step स्थिरraपूर्णांक
 * @step: step size
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_step(काष्ठा snd_pcm_runसमय *runसमय,
			       अचिन्हित पूर्णांक cond,
			       snd_pcm_hw_param_t var,
			       अचिन्हित दीर्घ step)
अणु
	वापस snd_pcm_hw_rule_add(runसमय, cond, var, 
				   snd_pcm_hw_rule_step, (व्योम *) step,
				   var, -1);
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_स्थिरraपूर्णांक_step);

अटल पूर्णांक snd_pcm_hw_rule_घात2(काष्ठा snd_pcm_hw_params *params, काष्ठा snd_pcm_hw_rule *rule)
अणु
	अटल स्थिर अचिन्हित पूर्णांक घात2_sizes[] = अणु
		1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7,
		1<<8, 1<<9, 1<<10, 1<<11, 1<<12, 1<<13, 1<<14, 1<<15,
		1<<16, 1<<17, 1<<18, 1<<19, 1<<20, 1<<21, 1<<22, 1<<23,
		1<<24, 1<<25, 1<<26, 1<<27, 1<<28, 1<<29, 1<<30
	पूर्ण;
	वापस snd_पूर्णांकerval_list(hw_param_पूर्णांकerval(params, rule->var),
				 ARRAY_SIZE(घात2_sizes), घात2_sizes, 0);
पूर्ण		

/**
 * snd_pcm_hw_स्थिरraपूर्णांक_घात2 - add a hw स्थिरraपूर्णांक घातer-of-2 rule
 * @runसमय: PCM runसमय instance
 * @cond: condition bits
 * @var: hw_params variable to apply the घातer-of-2 स्थिरraपूर्णांक
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_स्थिरraपूर्णांक_घात2(काष्ठा snd_pcm_runसमय *runसमय,
			       अचिन्हित पूर्णांक cond,
			       snd_pcm_hw_param_t var)
अणु
	वापस snd_pcm_hw_rule_add(runसमय, cond, var, 
				   snd_pcm_hw_rule_घात2, शून्य,
				   var, -1);
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_स्थिरraपूर्णांक_घात2);

अटल पूर्णांक snd_pcm_hw_rule_noresample_func(काष्ठा snd_pcm_hw_params *params,
					   काष्ठा snd_pcm_hw_rule *rule)
अणु
	अचिन्हित पूर्णांक base_rate = (अचिन्हित पूर्णांक)(uपूर्णांकptr_t)rule->निजी;
	काष्ठा snd_पूर्णांकerval *rate;

	rate = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	वापस snd_पूर्णांकerval_list(rate, 1, &base_rate, 0);
पूर्ण

/**
 * snd_pcm_hw_rule_noresample - add a rule to allow disabling hw resampling
 * @runसमय: PCM runसमय instance
 * @base_rate: the rate at which the hardware करोes not resample
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_rule_noresample(काष्ठा snd_pcm_runसमय *runसमय,
			       अचिन्हित पूर्णांक base_rate)
अणु
	वापस snd_pcm_hw_rule_add(runसमय, SNDRV_PCM_HW_PARAMS_NORESAMPLE,
				   SNDRV_PCM_HW_PARAM_RATE,
				   snd_pcm_hw_rule_noresample_func,
				   (व्योम *)(uपूर्णांकptr_t)base_rate,
				   SNDRV_PCM_HW_PARAM_RATE, -1);
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_rule_noresample);

अटल व्योम _snd_pcm_hw_param_any(काष्ठा snd_pcm_hw_params *params,
				  snd_pcm_hw_param_t var)
अणु
	अगर (hw_is_mask(var)) अणु
		snd_mask_any(hw_param_mask(params, var));
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
		वापस;
	पूर्ण
	अगर (hw_is_पूर्णांकerval(var)) अणु
		snd_पूर्णांकerval_any(hw_param_पूर्णांकerval(params, var));
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
		वापस;
	पूर्ण
	snd_BUG();
पूर्ण

व्योम _snd_pcm_hw_params_any(काष्ठा snd_pcm_hw_params *params)
अणु
	अचिन्हित पूर्णांक k;
	स_रखो(params, 0, माप(*params));
	क्रम (k = SNDRV_PCM_HW_PARAM_FIRST_MASK; k <= SNDRV_PCM_HW_PARAM_LAST_MASK; k++)
		_snd_pcm_hw_param_any(params, k);
	क्रम (k = SNDRV_PCM_HW_PARAM_FIRST_INTERVAL; k <= SNDRV_PCM_HW_PARAM_LAST_INTERVAL; k++)
		_snd_pcm_hw_param_any(params, k);
	params->info = ~0U;
पूर्ण
EXPORT_SYMBOL(_snd_pcm_hw_params_any);

/**
 * snd_pcm_hw_param_value - वापस @params field @var value
 * @params: the hw_params instance
 * @var: parameter to retrieve
 * @dir: poपूर्णांकer to the direction (-1,0,1) or %शून्य
 *
 * Return: The value क्रम field @var अगर it's fixed in configuration space
 * defined by @params. -%EINVAL otherwise.
 */
पूर्णांक snd_pcm_hw_param_value(स्थिर काष्ठा snd_pcm_hw_params *params,
			   snd_pcm_hw_param_t var, पूर्णांक *dir)
अणु
	अगर (hw_is_mask(var)) अणु
		स्थिर काष्ठा snd_mask *mask = hw_param_mask_c(params, var);
		अगर (!snd_mask_single(mask))
			वापस -EINVAL;
		अगर (dir)
			*dir = 0;
		वापस snd_mask_value(mask);
	पूर्ण
	अगर (hw_is_पूर्णांकerval(var)) अणु
		स्थिर काष्ठा snd_पूर्णांकerval *i = hw_param_पूर्णांकerval_c(params, var);
		अगर (!snd_पूर्णांकerval_single(i))
			वापस -EINVAL;
		अगर (dir)
			*dir = i->खोलोmin;
		वापस snd_पूर्णांकerval_value(i);
	पूर्ण
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_param_value);

व्योम _snd_pcm_hw_param_setempty(काष्ठा snd_pcm_hw_params *params,
				snd_pcm_hw_param_t var)
अणु
	अगर (hw_is_mask(var)) अणु
		snd_mask_none(hw_param_mask(params, var));
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	पूर्ण अन्यथा अगर (hw_is_पूर्णांकerval(var)) अणु
		snd_पूर्णांकerval_none(hw_param_पूर्णांकerval(params, var));
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	पूर्ण अन्यथा अणु
		snd_BUG();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(_snd_pcm_hw_param_setempty);

अटल पूर्णांक _snd_pcm_hw_param_first(काष्ठा snd_pcm_hw_params *params,
				   snd_pcm_hw_param_t var)
अणु
	पूर्णांक changed;
	अगर (hw_is_mask(var))
		changed = snd_mask_refine_first(hw_param_mask(params, var));
	अन्यथा अगर (hw_is_पूर्णांकerval(var))
		changed = snd_पूर्णांकerval_refine_first(hw_param_पूर्णांकerval(params, var));
	अन्यथा
		वापस -EINVAL;
	अगर (changed > 0) अणु
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	पूर्ण
	वापस changed;
पूर्ण


/**
 * snd_pcm_hw_param_first - refine config space and वापस minimum value
 * @pcm: PCM instance
 * @params: the hw_params instance
 * @var: parameter to retrieve
 * @dir: poपूर्णांकer to the direction (-1,0,1) or %शून्य
 *
 * Inside configuration space defined by @params हटाओ from @var all
 * values > minimum. Reduce configuration space accordingly.
 *
 * Return: The minimum, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_param_first(काष्ठा snd_pcm_substream *pcm, 
			   काष्ठा snd_pcm_hw_params *params, 
			   snd_pcm_hw_param_t var, पूर्णांक *dir)
अणु
	पूर्णांक changed = _snd_pcm_hw_param_first(params, var);
	अगर (changed < 0)
		वापस changed;
	अगर (params->rmask) अणु
		पूर्णांक err = snd_pcm_hw_refine(pcm, params);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस snd_pcm_hw_param_value(params, var, dir);
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_param_first);

अटल पूर्णांक _snd_pcm_hw_param_last(काष्ठा snd_pcm_hw_params *params,
				  snd_pcm_hw_param_t var)
अणु
	पूर्णांक changed;
	अगर (hw_is_mask(var))
		changed = snd_mask_refine_last(hw_param_mask(params, var));
	अन्यथा अगर (hw_is_पूर्णांकerval(var))
		changed = snd_पूर्णांकerval_refine_last(hw_param_पूर्णांकerval(params, var));
	अन्यथा
		वापस -EINVAL;
	अगर (changed > 0) अणु
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	पूर्ण
	वापस changed;
पूर्ण


/**
 * snd_pcm_hw_param_last - refine config space and वापस maximum value
 * @pcm: PCM instance
 * @params: the hw_params instance
 * @var: parameter to retrieve
 * @dir: poपूर्णांकer to the direction (-1,0,1) or %शून्य
 *
 * Inside configuration space defined by @params हटाओ from @var all
 * values < maximum. Reduce configuration space accordingly.
 *
 * Return: The maximum, or a negative error code on failure.
 */
पूर्णांक snd_pcm_hw_param_last(काष्ठा snd_pcm_substream *pcm, 
			  काष्ठा snd_pcm_hw_params *params,
			  snd_pcm_hw_param_t var, पूर्णांक *dir)
अणु
	पूर्णांक changed = _snd_pcm_hw_param_last(params, var);
	अगर (changed < 0)
		वापस changed;
	अगर (params->rmask) अणु
		पूर्णांक err = snd_pcm_hw_refine(pcm, params);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस snd_pcm_hw_param_value(params, var, dir);
पूर्ण
EXPORT_SYMBOL(snd_pcm_hw_param_last);

अटल पूर्णांक snd_pcm_lib_ioctl_reset(काष्ठा snd_pcm_substream *substream,
				   व्योम *arg)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ flags;
	snd_pcm_stream_lock_irqsave(substream, flags);
	अगर (snd_pcm_running(substream) &&
	    snd_pcm_update_hw_ptr(substream) >= 0)
		runसमय->status->hw_ptr %= runसमय->buffer_size;
	अन्यथा अणु
		runसमय->status->hw_ptr = 0;
		runसमय->hw_ptr_wrap = 0;
	पूर्ण
	snd_pcm_stream_unlock_irqrestore(substream, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_lib_ioctl_channel_info(काष्ठा snd_pcm_substream *substream,
					  व्योम *arg)
अणु
	काष्ठा snd_pcm_channel_info *info = arg;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक width;
	अगर (!(runसमय->info & SNDRV_PCM_INFO_MMAP)) अणु
		info->offset = -1;
		वापस 0;
	पूर्ण
	width = snd_pcm_क्रमmat_physical_width(runसमय->क्रमmat);
	अगर (width < 0)
		वापस width;
	info->offset = 0;
	चयन (runसमय->access) अणु
	हाल SNDRV_PCM_ACCESS_MMAP_INTERLEAVED:
	हाल SNDRV_PCM_ACCESS_RW_INTERLEAVED:
		info->first = info->channel * width;
		info->step = runसमय->channels * width;
		अवरोध;
	हाल SNDRV_PCM_ACCESS_MMAP_NONINTERLEAVED:
	हाल SNDRV_PCM_ACCESS_RW_NONINTERLEAVED:
	अणु
		माप_प्रकार size = runसमय->dma_bytes / runसमय->channels;
		info->first = info->channel * size * 8;
		info->step = width;
		अवरोध;
	पूर्ण
	शेष:
		snd_BUG();
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_lib_ioctl_fअगरo_size(काष्ठा snd_pcm_substream *substream,
				       व्योम *arg)
अणु
	काष्ठा snd_pcm_hw_params *params = arg;
	snd_pcm_क्रमmat_t क्रमmat;
	पूर्णांक channels;
	sमाप_प्रकार frame_size;

	params->fअगरo_size = substream->runसमय->hw.fअगरo_size;
	अगर (!(substream->runसमय->hw.info & SNDRV_PCM_INFO_FIFO_IN_FRAMES)) अणु
		क्रमmat = params_क्रमmat(params);
		channels = params_channels(params);
		frame_size = snd_pcm_क्रमmat_size(क्रमmat, channels);
		अगर (frame_size > 0)
			params->fअगरo_size /= (अचिन्हित)frame_size;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * snd_pcm_lib_ioctl - a generic PCM ioctl callback
 * @substream: the pcm substream instance
 * @cmd: ioctl command
 * @arg: ioctl argument
 *
 * Processes the generic ioctl commands क्रम PCM.
 * Can be passed as the ioctl callback क्रम PCM ops.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_lib_ioctl(काष्ठा snd_pcm_substream *substream,
		      अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल SNDRV_PCM_IOCTL1_RESET:
		वापस snd_pcm_lib_ioctl_reset(substream, arg);
	हाल SNDRV_PCM_IOCTL1_CHANNEL_INFO:
		वापस snd_pcm_lib_ioctl_channel_info(substream, arg);
	हाल SNDRV_PCM_IOCTL1_FIFO_SIZE:
		वापस snd_pcm_lib_ioctl_fअगरo_size(substream, arg);
	पूर्ण
	वापस -ENXIO;
पूर्ण
EXPORT_SYMBOL(snd_pcm_lib_ioctl);

/**
 * snd_pcm_period_elapsed - update the pcm status क्रम the next period
 * @substream: the pcm substream instance
 *
 * This function is called from the पूर्णांकerrupt handler when the
 * PCM has processed the period size.  It will update the current
 * poपूर्णांकer, wake up sleepers, etc.
 *
 * Even अगर more than one periods have elapsed since the last call, you
 * have to call this only once.
 */
व्योम snd_pcm_period_elapsed(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!substream))
		वापस;

	snd_pcm_stream_lock_irqsave(substream, flags);
	अगर (PCM_RUNTIME_CHECK(substream))
		जाओ _unlock;
	runसमय = substream->runसमय;

	अगर (!snd_pcm_running(substream) ||
	    snd_pcm_update_hw_ptr0(substream, 1) < 0)
		जाओ _end;

#अगर_घोषित CONFIG_SND_PCM_TIMER
	अगर (substream->समयr_running)
		snd_समयr_पूर्णांकerrupt(substream->समयr, 1);
#पूर्ण_अगर
 _end:
	समाप्त_fasync(&runसमय->fasync, SIGIO, POLL_IN);
 _unlock:
	snd_pcm_stream_unlock_irqrestore(substream, flags);
पूर्ण
EXPORT_SYMBOL(snd_pcm_period_elapsed);

/*
 * Wait until avail_min data becomes available
 * Returns a negative error code अगर any error occurs during operation.
 * The available space is stored on availp.  When err = 0 and avail = 0
 * on the capture stream, it indicates the stream is in DRAINING state.
 */
अटल पूर्णांक रुको_क्रम_avail(काष्ठा snd_pcm_substream *substream,
			      snd_pcm_uframes_t *availp)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक is_playback = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	रुको_queue_entry_t रुको;
	पूर्णांक err = 0;
	snd_pcm_uframes_t avail = 0;
	दीर्घ रुको_समय, tout;

	init_रुकोqueue_entry(&रुको, current);
	set_current_state(TASK_INTERRUPTIBLE);
	add_रुको_queue(&runसमय->tsleep, &रुको);

	अगर (runसमय->no_period_wakeup)
		रुको_समय = MAX_SCHEDULE_TIMEOUT;
	अन्यथा अणु
		/* use रुको समय from substream अगर available */
		अगर (substream->रुको_समय) अणु
			रुको_समय = substream->रुको_समय;
		पूर्ण अन्यथा अणु
			रुको_समय = 10;

			अगर (runसमय->rate) अणु
				दीर्घ t = runसमय->period_size * 2 /
					 runसमय->rate;
				रुको_समय = max(t, रुको_समय);
			पूर्ण
			रुको_समय = msecs_to_jअगरfies(रुको_समय * 1000);
		पूर्ण
	पूर्ण

	क्रम (;;) अणु
		अगर (संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		/*
		 * We need to check अगर space became available alपढ़ोy
		 * (and thus the wakeup happened alपढ़ोy) first to बंद
		 * the race of space alपढ़ोy having become available.
		 * This check must happen after been added to the रुकोqueue
		 * and having current state be INTERRUPTIBLE.
		 */
		avail = snd_pcm_avail(substream);
		अगर (avail >= runसमय->twake)
			अवरोध;
		snd_pcm_stream_unlock_irq(substream);

		tout = schedule_समयout(रुको_समय);

		snd_pcm_stream_lock_irq(substream);
		set_current_state(TASK_INTERRUPTIBLE);
		चयन (runसमय->status->state) अणु
		हाल SNDRV_PCM_STATE_SUSPENDED:
			err = -ESTRPIPE;
			जाओ _endloop;
		हाल SNDRV_PCM_STATE_XRUN:
			err = -EPIPE;
			जाओ _endloop;
		हाल SNDRV_PCM_STATE_DRAINING:
			अगर (is_playback)
				err = -EPIPE;
			अन्यथा 
				avail = 0; /* indicate draining */
			जाओ _endloop;
		हाल SNDRV_PCM_STATE_OPEN:
		हाल SNDRV_PCM_STATE_SETUP:
		हाल SNDRV_PCM_STATE_DISCONNECTED:
			err = -EBADFD;
			जाओ _endloop;
		हाल SNDRV_PCM_STATE_PAUSED:
			जारी;
		पूर्ण
		अगर (!tout) अणु
			pcm_dbg(substream->pcm,
				"%s write error (DMA or IRQ trouble?)\n",
				is_playback ? "playback" : "capture");
			err = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण
 _endloop:
	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&runसमय->tsleep, &रुको);
	*availp = avail;
	वापस err;
पूर्ण
	
प्रकार पूर्णांक (*pcm_transfer_f)(काष्ठा snd_pcm_substream *substream,
			      पूर्णांक channel, अचिन्हित दीर्घ hwoff,
			      व्योम *buf, अचिन्हित दीर्घ bytes);

प्रकार पूर्णांक (*pcm_copy_f)(काष्ठा snd_pcm_substream *, snd_pcm_uframes_t, व्योम *,
			  snd_pcm_uframes_t, snd_pcm_uframes_t, pcm_transfer_f);

/* calculate the target DMA-buffer position to be written/पढ़ो */
अटल व्योम *get_dma_ptr(काष्ठा snd_pcm_runसमय *runसमय,
			   पूर्णांक channel, अचिन्हित दीर्घ hwoff)
अणु
	वापस runसमय->dma_area + hwoff +
		channel * (runसमय->dma_bytes / runसमय->channels);
पूर्ण

/* शेष copy_user ops क्रम ग_लिखो; used क्रम both पूर्णांकerleaved and non- modes */
अटल पूर्णांक शेष_ग_लिखो_copy(काष्ठा snd_pcm_substream *substream,
			      पूर्णांक channel, अचिन्हित दीर्घ hwoff,
			      व्योम *buf, अचिन्हित दीर्घ bytes)
अणु
	अगर (copy_from_user(get_dma_ptr(substream->runसमय, channel, hwoff),
			   (व्योम __user *)buf, bytes))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/* शेष copy_kernel ops क्रम ग_लिखो */
अटल पूर्णांक शेष_ग_लिखो_copy_kernel(काष्ठा snd_pcm_substream *substream,
				     पूर्णांक channel, अचिन्हित दीर्घ hwoff,
				     व्योम *buf, अचिन्हित दीर्घ bytes)
अणु
	स_नकल(get_dma_ptr(substream->runसमय, channel, hwoff), buf, bytes);
	वापस 0;
पूर्ण

/* fill silence instead of copy data; called as a transfer helper
 * from __snd_pcm_lib_ग_लिखो() or directly from nonपूर्णांकerleaved_copy() when
 * a शून्य buffer is passed
 */
अटल पूर्णांक fill_silence(काष्ठा snd_pcm_substream *substream, पूर्णांक channel,
			अचिन्हित दीर्घ hwoff, व्योम *buf, अचिन्हित दीर्घ bytes)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		वापस 0;
	अगर (substream->ops->fill_silence)
		वापस substream->ops->fill_silence(substream, channel,
						    hwoff, bytes);

	snd_pcm_क्रमmat_set_silence(runसमय->क्रमmat,
				   get_dma_ptr(runसमय, channel, hwoff),
				   bytes_to_samples(runसमय, bytes));
	वापस 0;
पूर्ण

/* शेष copy_user ops क्रम पढ़ो; used क्रम both पूर्णांकerleaved and non- modes */
अटल पूर्णांक शेष_पढ़ो_copy(काष्ठा snd_pcm_substream *substream,
			     पूर्णांक channel, अचिन्हित दीर्घ hwoff,
			     व्योम *buf, अचिन्हित दीर्घ bytes)
अणु
	अगर (copy_to_user((व्योम __user *)buf,
			 get_dma_ptr(substream->runसमय, channel, hwoff),
			 bytes))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/* शेष copy_kernel ops क्रम पढ़ो */
अटल पूर्णांक शेष_पढ़ो_copy_kernel(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक channel, अचिन्हित दीर्घ hwoff,
				    व्योम *buf, अचिन्हित दीर्घ bytes)
अणु
	स_नकल(buf, get_dma_ptr(substream->runसमय, channel, hwoff), bytes);
	वापस 0;
पूर्ण

/* call transfer function with the converted poपूर्णांकers and sizes;
 * क्रम पूर्णांकerleaved mode, it's one shot क्रम all samples
 */
अटल पूर्णांक पूर्णांकerleaved_copy(काष्ठा snd_pcm_substream *substream,
			    snd_pcm_uframes_t hwoff, व्योम *data,
			    snd_pcm_uframes_t off,
			    snd_pcm_uframes_t frames,
			    pcm_transfer_f transfer)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	/* convert to bytes */
	hwoff = frames_to_bytes(runसमय, hwoff);
	off = frames_to_bytes(runसमय, off);
	frames = frames_to_bytes(runसमय, frames);
	वापस transfer(substream, 0, hwoff, data + off, frames);
पूर्ण

/* call transfer function with the converted poपूर्णांकers and sizes क्रम each
 * non-पूर्णांकerleaved channel; when buffer is शून्य, silencing instead of copying
 */
अटल पूर्णांक nonपूर्णांकerleaved_copy(काष्ठा snd_pcm_substream *substream,
			       snd_pcm_uframes_t hwoff, व्योम *data,
			       snd_pcm_uframes_t off,
			       snd_pcm_uframes_t frames,
			       pcm_transfer_f transfer)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक channels = runसमय->channels;
	व्योम **bufs = data;
	पूर्णांक c, err;

	/* convert to bytes; note that it's not frames_to_bytes() here.
	 * in non-पूर्णांकerleaved mode, we copy क्रम each channel, thus
	 * each copy is n_samples bytes x channels = whole frames.
	 */
	off = samples_to_bytes(runसमय, off);
	frames = samples_to_bytes(runसमय, frames);
	hwoff = samples_to_bytes(runसमय, hwoff);
	क्रम (c = 0; c < channels; ++c, ++bufs) अणु
		अगर (!data || !*bufs)
			err = fill_silence(substream, c, hwoff, शून्य, frames);
		अन्यथा
			err = transfer(substream, c, hwoff, *bufs + off,
				       frames);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* fill silence on the given buffer position;
 * called from snd_pcm_playback_silence()
 */
अटल पूर्णांक fill_silence_frames(काष्ठा snd_pcm_substream *substream,
			       snd_pcm_uframes_t off, snd_pcm_uframes_t frames)
अणु
	अगर (substream->runसमय->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED ||
	    substream->runसमय->access == SNDRV_PCM_ACCESS_MMAP_INTERLEAVED)
		वापस पूर्णांकerleaved_copy(substream, off, शून्य, 0, frames,
					fill_silence);
	अन्यथा
		वापस nonपूर्णांकerleaved_copy(substream, off, शून्य, 0, frames,
					   fill_silence);
पूर्ण

/* sanity-check क्रम पढ़ो/ग_लिखो methods */
अटल पूर्णांक pcm_sanity_check(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	अगर (PCM_RUNTIME_CHECK(substream))
		वापस -ENXIO;
	runसमय = substream->runसमय;
	अगर (snd_BUG_ON(!substream->ops->copy_user && !runसमय->dma_area))
		वापस -EINVAL;
	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN)
		वापस -EBADFD;
	वापस 0;
पूर्ण

अटल पूर्णांक pcm_accessible_state(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	चयन (runसमय->status->state) अणु
	हाल SNDRV_PCM_STATE_PREPARED:
	हाल SNDRV_PCM_STATE_RUNNING:
	हाल SNDRV_PCM_STATE_PAUSED:
		वापस 0;
	हाल SNDRV_PCM_STATE_XRUN:
		वापस -EPIPE;
	हाल SNDRV_PCM_STATE_SUSPENDED:
		वापस -ESTRPIPE;
	शेष:
		वापस -EBADFD;
	पूर्ण
पूर्ण

/* update to the given appl_ptr and call ack callback अगर needed;
 * when an error is वापसed, take back to the original value
 */
पूर्णांक pcm_lib_apply_appl_ptr(काष्ठा snd_pcm_substream *substream,
			   snd_pcm_uframes_t appl_ptr)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_uframes_t old_appl_ptr = runसमय->control->appl_ptr;
	पूर्णांक ret;

	अगर (old_appl_ptr == appl_ptr)
		वापस 0;

	runसमय->control->appl_ptr = appl_ptr;
	अगर (substream->ops->ack) अणु
		ret = substream->ops->ack(substream);
		अगर (ret < 0) अणु
			runसमय->control->appl_ptr = old_appl_ptr;
			वापस ret;
		पूर्ण
	पूर्ण

	trace_applptr(substream, old_appl_ptr, appl_ptr);

	वापस 0;
पूर्ण

/* the common loop क्रम पढ़ो/ग_लिखो data */
snd_pcm_sframes_t __snd_pcm_lib_xfer(काष्ठा snd_pcm_substream *substream,
				     व्योम *data, bool पूर्णांकerleaved,
				     snd_pcm_uframes_t size, bool in_kernel)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_uframes_t xfer = 0;
	snd_pcm_uframes_t offset = 0;
	snd_pcm_uframes_t avail;
	pcm_copy_f ग_लिखोr;
	pcm_transfer_f transfer;
	bool nonblock;
	bool is_playback;
	पूर्णांक err;

	err = pcm_sanity_check(substream);
	अगर (err < 0)
		वापस err;

	is_playback = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	अगर (पूर्णांकerleaved) अणु
		अगर (runसमय->access != SNDRV_PCM_ACCESS_RW_INTERLEAVED &&
		    runसमय->channels > 1)
			वापस -EINVAL;
		ग_लिखोr = पूर्णांकerleaved_copy;
	पूर्ण अन्यथा अणु
		अगर (runसमय->access != SNDRV_PCM_ACCESS_RW_NONINTERLEAVED)
			वापस -EINVAL;
		ग_लिखोr = nonपूर्णांकerleaved_copy;
	पूर्ण

	अगर (!data) अणु
		अगर (is_playback)
			transfer = fill_silence;
		अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (in_kernel) अणु
		अगर (substream->ops->copy_kernel)
			transfer = substream->ops->copy_kernel;
		अन्यथा
			transfer = is_playback ?
				शेष_ग_लिखो_copy_kernel : शेष_पढ़ो_copy_kernel;
	पूर्ण अन्यथा अणु
		अगर (substream->ops->copy_user)
			transfer = (pcm_transfer_f)substream->ops->copy_user;
		अन्यथा
			transfer = is_playback ?
				शेष_ग_लिखो_copy : शेष_पढ़ो_copy;
	पूर्ण

	अगर (size == 0)
		वापस 0;

	nonblock = !!(substream->f_flags & O_NONBLOCK);

	snd_pcm_stream_lock_irq(substream);
	err = pcm_accessible_state(runसमय);
	अगर (err < 0)
		जाओ _end_unlock;

	runसमय->twake = runसमय->control->avail_min ? : 1;
	अगर (runसमय->status->state == SNDRV_PCM_STATE_RUNNING)
		snd_pcm_update_hw_ptr(substream);

	/*
	 * If size < start_threshold, रुको indefinitely. Another
	 * thपढ़ो may start capture
	 */
	अगर (!is_playback &&
	    runसमय->status->state == SNDRV_PCM_STATE_PREPARED &&
	    size >= runसमय->start_threshold) अणु
		err = snd_pcm_start(substream);
		अगर (err < 0)
			जाओ _end_unlock;
	पूर्ण

	avail = snd_pcm_avail(substream);

	जबतक (size > 0) अणु
		snd_pcm_uframes_t frames, appl_ptr, appl_ofs;
		snd_pcm_uframes_t cont;
		अगर (!avail) अणु
			अगर (!is_playback &&
			    runसमय->status->state == SNDRV_PCM_STATE_DRAINING) अणु
				snd_pcm_stop(substream, SNDRV_PCM_STATE_SETUP);
				जाओ _end_unlock;
			पूर्ण
			अगर (nonblock) अणु
				err = -EAGAIN;
				जाओ _end_unlock;
			पूर्ण
			runसमय->twake = min_t(snd_pcm_uframes_t, size,
					runसमय->control->avail_min ? : 1);
			err = रुको_क्रम_avail(substream, &avail);
			अगर (err < 0)
				जाओ _end_unlock;
			अगर (!avail)
				जारी; /* draining */
		पूर्ण
		frames = size > avail ? avail : size;
		appl_ptr = READ_ONCE(runसमय->control->appl_ptr);
		appl_ofs = appl_ptr % runसमय->buffer_size;
		cont = runसमय->buffer_size - appl_ofs;
		अगर (frames > cont)
			frames = cont;
		अगर (snd_BUG_ON(!frames)) अणु
			err = -EINVAL;
			जाओ _end_unlock;
		पूर्ण
		snd_pcm_stream_unlock_irq(substream);
		err = ग_लिखोr(substream, appl_ofs, data, offset, frames,
			     transfer);
		snd_pcm_stream_lock_irq(substream);
		अगर (err < 0)
			जाओ _end_unlock;
		err = pcm_accessible_state(runसमय);
		अगर (err < 0)
			जाओ _end_unlock;
		appl_ptr += frames;
		अगर (appl_ptr >= runसमय->boundary)
			appl_ptr -= runसमय->boundary;
		err = pcm_lib_apply_appl_ptr(substream, appl_ptr);
		अगर (err < 0)
			जाओ _end_unlock;

		offset += frames;
		size -= frames;
		xfer += frames;
		avail -= frames;
		अगर (is_playback &&
		    runसमय->status->state == SNDRV_PCM_STATE_PREPARED &&
		    snd_pcm_playback_hw_avail(runसमय) >= (snd_pcm_sframes_t)runसमय->start_threshold) अणु
			err = snd_pcm_start(substream);
			अगर (err < 0)
				जाओ _end_unlock;
		पूर्ण
	पूर्ण
 _end_unlock:
	runसमय->twake = 0;
	अगर (xfer > 0 && err >= 0)
		snd_pcm_update_state(substream, runसमय);
	snd_pcm_stream_unlock_irq(substream);
	वापस xfer > 0 ? (snd_pcm_sframes_t)xfer : err;
पूर्ण
EXPORT_SYMBOL(__snd_pcm_lib_xfer);

/*
 * standard channel mapping helpers
 */

/* शेष channel maps क्रम multi-channel playbacks, up to 8 channels */
स्थिर काष्ठा snd_pcm_chmap_elem snd_pcm_std_chmaps[] = अणु
	अणु .channels = 1,
	  .map = अणु SNDRV_CHMAP_MONO पूर्ण पूर्ण,
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR पूर्ण पूर्ण,
	अणु .channels = 4,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
		   SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु .channels = 6,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
		   SNDRV_CHMAP_RL, SNDRV_CHMAP_RR,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_LFE पूर्ण पूर्ण,
	अणु .channels = 8,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
		   SNDRV_CHMAP_RL, SNDRV_CHMAP_RR,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_SL, SNDRV_CHMAP_SR पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;
EXPORT_SYMBOL_GPL(snd_pcm_std_chmaps);

/* alternative channel maps with CLFE <-> surround swapped क्रम 6/8 channels */
स्थिर काष्ठा snd_pcm_chmap_elem snd_pcm_alt_chmaps[] = अणु
	अणु .channels = 1,
	  .map = अणु SNDRV_CHMAP_MONO पूर्ण पूर्ण,
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR पूर्ण पूर्ण,
	अणु .channels = 4,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
		   SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु .channels = 6,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु .channels = 8,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_RL, SNDRV_CHMAP_RR,
		   SNDRV_CHMAP_SL, SNDRV_CHMAP_SR पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;
EXPORT_SYMBOL_GPL(snd_pcm_alt_chmaps);

अटल bool valid_chmap_channels(स्थिर काष्ठा snd_pcm_chmap *info, पूर्णांक ch)
अणु
	अगर (ch > info->max_channels)
		वापस false;
	वापस !info->channel_mask || (info->channel_mask & (1U << ch));
पूर्ण

अटल पूर्णांक pcm_chmap_ctl_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = info->max_channels;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = SNDRV_CHMAP_LAST;
	वापस 0;
पूर्ण

/* get callback क्रम channel map ctl element
 * stores the channel position firstly matching with the current channels
 */
अटल पूर्णांक pcm_chmap_ctl_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	काष्ठा snd_pcm_substream *substream;
	स्थिर काष्ठा snd_pcm_chmap_elem *map;

	अगर (!info->chmap)
		वापस -EINVAL;
	substream = snd_pcm_chmap_substream(info, idx);
	अगर (!substream)
		वापस -ENODEV;
	स_रखो(ucontrol->value.पूर्णांकeger.value, 0,
	       माप(दीर्घ) * info->max_channels);
	अगर (!substream->runसमय)
		वापस 0; /* no channels set */
	क्रम (map = info->chmap; map->channels; map++) अणु
		पूर्णांक i;
		अगर (map->channels == substream->runसमय->channels &&
		    valid_chmap_channels(info, map->channels)) अणु
			क्रम (i = 0; i < map->channels; i++)
				ucontrol->value.पूर्णांकeger.value[i] = map->map[i];
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* tlv callback क्रम channel map ctl element
 * expands the pre-defined channel maps in a क्रमm of TLV
 */
अटल पूर्णांक pcm_chmap_ctl_tlv(काष्ठा snd_kcontrol *kcontrol, पूर्णांक op_flag,
			     अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक __user *tlv)
अणु
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	स्थिर काष्ठा snd_pcm_chmap_elem *map;
	अचिन्हित पूर्णांक __user *dst;
	पूर्णांक c, count = 0;

	अगर (!info->chmap)
		वापस -EINVAL;
	अगर (size < 8)
		वापस -ENOMEM;
	अगर (put_user(SNDRV_CTL_TLVT_CONTAINER, tlv))
		वापस -EFAULT;
	size -= 8;
	dst = tlv + 2;
	क्रम (map = info->chmap; map->channels; map++) अणु
		पूर्णांक chs_bytes = map->channels * 4;
		अगर (!valid_chmap_channels(info, map->channels))
			जारी;
		अगर (size < 8)
			वापस -ENOMEM;
		अगर (put_user(SNDRV_CTL_TLVT_CHMAP_FIXED, dst) ||
		    put_user(chs_bytes, dst + 1))
			वापस -EFAULT;
		dst += 2;
		size -= 8;
		count += 8;
		अगर (size < chs_bytes)
			वापस -ENOMEM;
		size -= chs_bytes;
		count += chs_bytes;
		क्रम (c = 0; c < map->channels; c++) अणु
			अगर (put_user(map->map[c], dst))
				वापस -EFAULT;
			dst++;
		पूर्ण
	पूर्ण
	अगर (put_user(count, tlv + 1))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल व्योम pcm_chmap_ctl_निजी_मुक्त(काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	info->pcm->streams[info->stream].chmap_kctl = शून्य;
	kमुक्त(info);
पूर्ण

/**
 * snd_pcm_add_chmap_ctls - create channel-mapping control elements
 * @pcm: the asचिन्हित PCM instance
 * @stream: stream direction
 * @chmap: channel map elements (क्रम query)
 * @max_channels: the max number of channels क्रम the stream
 * @निजी_value: the value passed to each kcontrol's निजी_value field
 * @info_ret: store काष्ठा snd_pcm_chmap instance अगर non-शून्य
 *
 * Create channel-mapping control elements asचिन्हित to the given PCM stream(s).
 * Return: Zero अगर successful, or a negative error value.
 */
पूर्णांक snd_pcm_add_chmap_ctls(काष्ठा snd_pcm *pcm, पूर्णांक stream,
			   स्थिर काष्ठा snd_pcm_chmap_elem *chmap,
			   पूर्णांक max_channels,
			   अचिन्हित दीर्घ निजी_value,
			   काष्ठा snd_pcm_chmap **info_ret)
अणु
	काष्ठा snd_pcm_chmap *info;
	काष्ठा snd_kcontrol_new knew = अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ |
			SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK,
		.info = pcm_chmap_ctl_info,
		.get = pcm_chmap_ctl_get,
		.tlv.c = pcm_chmap_ctl_tlv,
	पूर्ण;
	पूर्णांक err;

	अगर (WARN_ON(pcm->streams[stream].chmap_kctl))
		वापस -EBUSY;
	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	info->pcm = pcm;
	info->stream = stream;
	info->chmap = chmap;
	info->max_channels = max_channels;
	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
		knew.name = "Playback Channel Map";
	अन्यथा
		knew.name = "Capture Channel Map";
	knew.device = pcm->device;
	knew.count = pcm->streams[stream].substream_count;
	knew.निजी_value = निजी_value;
	info->kctl = snd_ctl_new1(&knew, info);
	अगर (!info->kctl) अणु
		kमुक्त(info);
		वापस -ENOMEM;
	पूर्ण
	info->kctl->निजी_मुक्त = pcm_chmap_ctl_निजी_मुक्त;
	err = snd_ctl_add(pcm->card, info->kctl);
	अगर (err < 0)
		वापस err;
	pcm->streams[stream].chmap_kctl = info->kctl;
	अगर (info_ret)
		*info_ret = info;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_pcm_add_chmap_ctls);
