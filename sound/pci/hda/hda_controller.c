<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Implementation of primary alsa driver code base क्रम Intel HD Audio.
 *
 *  Copyright(c) 2004 Intel Corporation. All rights reserved.
 *
 *  Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 *                     PeiSen Hou <pshou@realtek.com.tw>
 */

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#अगर_घोषित CONFIG_X86
/* क्रम art-tsc conversion */
#समावेश <यंत्र/tsc.h>
#पूर्ण_अगर

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश "hda_controller.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "hda_controller_trace.h"

/* DSP lock helpers */
#घोषणा dsp_lock(dev)		snd_hdac_dsp_lock(azx_stream(dev))
#घोषणा dsp_unlock(dev)		snd_hdac_dsp_unlock(azx_stream(dev))
#घोषणा dsp_is_locked(dev)	snd_hdac_stream_is_locked(azx_stream(dev))

/* assign a stream क्रम the PCM */
अटल अंतरभूत काष्ठा azx_dev *
azx_assign_device(काष्ठा azx *chip, काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdac_stream *s;

	s = snd_hdac_stream_assign(azx_bus(chip), substream);
	अगर (!s)
		वापस शून्य;
	वापस stream_to_azx_dev(s);
पूर्ण

/* release the asचिन्हित stream */
अटल अंतरभूत व्योम azx_release_device(काष्ठा azx_dev *azx_dev)
अणु
	snd_hdac_stream_release(azx_stream(azx_dev));
पूर्ण

अटल अंतरभूत काष्ठा hda_pcm_stream *
to_hda_pcm_stream(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
	वापस &apcm->info->stream[substream->stream];
पूर्ण

अटल u64 azx_adjust_codec_delay(काष्ठा snd_pcm_substream *substream,
				u64 nsec)
अणु
	काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
	काष्ठा hda_pcm_stream *hinfo = to_hda_pcm_stream(substream);
	u64 codec_frames, codec_nsecs;

	अगर (!hinfo->ops.get_delay)
		वापस nsec;

	codec_frames = hinfo->ops.get_delay(hinfo, apcm->codec, substream);
	codec_nsecs = भाग_u64(codec_frames * 1000000000LL,
			      substream->runसमय->rate);

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		वापस nsec + codec_nsecs;

	वापस (nsec > codec_nsecs) ? nsec - codec_nsecs : 0;
पूर्ण

/*
 * PCM ops
 */

अटल पूर्णांक azx_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
	काष्ठा hda_pcm_stream *hinfo = to_hda_pcm_stream(substream);
	काष्ठा azx *chip = apcm->chip;
	काष्ठा azx_dev *azx_dev = get_azx_dev(substream);

	trace_azx_pcm_बंद(chip, azx_dev);
	mutex_lock(&chip->खोलो_mutex);
	azx_release_device(azx_dev);
	अगर (hinfo->ops.बंद)
		hinfo->ops.बंद(hinfo, apcm->codec, substream);
	snd_hda_घातer_करोwn(apcm->codec);
	mutex_unlock(&chip->खोलो_mutex);
	snd_hda_codec_pcm_put(apcm->info);
	वापस 0;
पूर्ण

अटल पूर्णांक azx_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
	काष्ठा azx *chip = apcm->chip;
	काष्ठा azx_dev *azx_dev = get_azx_dev(substream);
	पूर्णांक ret = 0;

	trace_azx_pcm_hw_params(chip, azx_dev);
	dsp_lock(azx_dev);
	अगर (dsp_is_locked(azx_dev)) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	azx_dev->core.bufsize = 0;
	azx_dev->core.period_bytes = 0;
	azx_dev->core.क्रमmat_val = 0;

unlock:
	dsp_unlock(azx_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक azx_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
	काष्ठा azx_dev *azx_dev = get_azx_dev(substream);
	काष्ठा hda_pcm_stream *hinfo = to_hda_pcm_stream(substream);

	/* reset BDL address */
	dsp_lock(azx_dev);
	अगर (!dsp_is_locked(azx_dev))
		snd_hdac_stream_cleanup(azx_stream(azx_dev));

	snd_hda_codec_cleanup(apcm->codec, hinfo, substream);

	azx_stream(azx_dev)->prepared = 0;
	dsp_unlock(azx_dev);
	वापस 0;
पूर्ण

अटल पूर्णांक azx_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
	काष्ठा azx *chip = apcm->chip;
	काष्ठा azx_dev *azx_dev = get_azx_dev(substream);
	काष्ठा hda_pcm_stream *hinfo = to_hda_pcm_stream(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक क्रमmat_val, stream_tag;
	पूर्णांक err;
	काष्ठा hda_spdअगर_out *spdअगर =
		snd_hda_spdअगर_out_of_nid(apcm->codec, hinfo->nid);
	अचिन्हित लघु ctls = spdअगर ? spdअगर->ctls : 0;

	trace_azx_pcm_prepare(chip, azx_dev);
	dsp_lock(azx_dev);
	अगर (dsp_is_locked(azx_dev)) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	snd_hdac_stream_reset(azx_stream(azx_dev));
	क्रमmat_val = snd_hdac_calc_stream_क्रमmat(runसमय->rate,
						runसमय->channels,
						runसमय->क्रमmat,
						hinfo->maxbps,
						ctls);
	अगर (!क्रमmat_val) अणु
		dev_err(chip->card->dev,
			"invalid format_val, rate=%d, ch=%d, format=%d\n",
			runसमय->rate, runसमय->channels, runसमय->क्रमmat);
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	err = snd_hdac_stream_set_params(azx_stream(azx_dev), क्रमmat_val);
	अगर (err < 0)
		जाओ unlock;

	snd_hdac_stream_setup(azx_stream(azx_dev));

	stream_tag = azx_dev->core.stream_tag;
	/* CA-IBG chips need the playback stream starting from 1 */
	अगर ((chip->driver_caps & AZX_DCAPS_CTX_WORKAROUND) &&
	    stream_tag > chip->capture_streams)
		stream_tag -= chip->capture_streams;
	err = snd_hda_codec_prepare(apcm->codec, hinfo, stream_tag,
				     azx_dev->core.क्रमmat_val, substream);

 unlock:
	अगर (!err)
		azx_stream(azx_dev)->prepared = 1;
	dsp_unlock(azx_dev);
	वापस err;
पूर्ण

अटल पूर्णांक azx_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
	काष्ठा azx *chip = apcm->chip;
	काष्ठा hdac_bus *bus = azx_bus(chip);
	काष्ठा azx_dev *azx_dev;
	काष्ठा snd_pcm_substream *s;
	काष्ठा hdac_stream *hstr;
	bool start;
	पूर्णांक sbits = 0;
	पूर्णांक sync_reg;

	azx_dev = get_azx_dev(substream);
	trace_azx_pcm_trigger(chip, azx_dev, cmd);

	hstr = azx_stream(azx_dev);
	अगर (chip->driver_caps & AZX_DCAPS_OLD_SSYNC)
		sync_reg = AZX_REG_OLD_SSYNC;
	अन्यथा
		sync_reg = AZX_REG_SSYNC;

	अगर (dsp_is_locked(azx_dev) || !hstr->prepared)
		वापस -EPIPE;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		start = true;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		start = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (s->pcm->card != substream->pcm->card)
			जारी;
		azx_dev = get_azx_dev(s);
		sbits |= 1 << azx_dev->core.index;
		snd_pcm_trigger_करोne(s, substream);
	पूर्ण

	spin_lock(&bus->reg_lock);

	/* first, set SYNC bits of corresponding streams */
	snd_hdac_stream_sync_trigger(hstr, true, sbits, sync_reg);

	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (s->pcm->card != substream->pcm->card)
			जारी;
		azx_dev = get_azx_dev(s);
		अगर (start) अणु
			azx_dev->insufficient = 1;
			snd_hdac_stream_start(azx_stream(azx_dev), true);
		पूर्ण अन्यथा अणु
			snd_hdac_stream_stop(azx_stream(azx_dev));
		पूर्ण
	पूर्ण
	spin_unlock(&bus->reg_lock);

	snd_hdac_stream_sync(hstr, start, sbits);

	spin_lock(&bus->reg_lock);
	/* reset SYNC bits */
	snd_hdac_stream_sync_trigger(hstr, false, sbits, sync_reg);
	अगर (start)
		snd_hdac_stream_समयcounter_init(hstr, sbits);
	spin_unlock(&bus->reg_lock);
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक azx_get_pos_lpib(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev)
अणु
	वापस snd_hdac_stream_get_pos_lpib(azx_stream(azx_dev));
पूर्ण
EXPORT_SYMBOL_GPL(azx_get_pos_lpib);

अचिन्हित पूर्णांक azx_get_pos_posbuf(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev)
अणु
	वापस snd_hdac_stream_get_pos_posbuf(azx_stream(azx_dev));
पूर्ण
EXPORT_SYMBOL_GPL(azx_get_pos_posbuf);

अचिन्हित पूर्णांक azx_get_position(काष्ठा azx *chip,
			      काष्ठा azx_dev *azx_dev)
अणु
	काष्ठा snd_pcm_substream *substream = azx_dev->core.substream;
	अचिन्हित पूर्णांक pos;
	पूर्णांक stream = substream->stream;
	पूर्णांक delay = 0;

	अगर (chip->get_position[stream])
		pos = chip->get_position[stream](chip, azx_dev);
	अन्यथा /* use the position buffer as शेष */
		pos = azx_get_pos_posbuf(chip, azx_dev);

	अगर (pos >= azx_dev->core.bufsize)
		pos = 0;

	अगर (substream->runसमय) अणु
		काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
		काष्ठा hda_pcm_stream *hinfo = to_hda_pcm_stream(substream);

		अगर (chip->get_delay[stream])
			delay += chip->get_delay[stream](chip, azx_dev, pos);
		अगर (hinfo->ops.get_delay)
			delay += hinfo->ops.get_delay(hinfo, apcm->codec,
						      substream);
		substream->runसमय->delay = delay;
	पूर्ण

	trace_azx_get_position(chip, azx_dev, pos, delay);
	वापस pos;
पूर्ण
EXPORT_SYMBOL_GPL(azx_get_position);

अटल snd_pcm_uframes_t azx_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
	काष्ठा azx *chip = apcm->chip;
	काष्ठा azx_dev *azx_dev = get_azx_dev(substream);
	वापस bytes_to_frames(substream->runसमय,
			       azx_get_position(chip, azx_dev));
पूर्ण

/*
 * azx_scale64: Scale base by mult/भाग जबतक not overflowing sanely
 *
 * Derived from scale64_check_overflow in kernel/समय/समयkeeping.c
 *
 * The पंचांगestamps क्रम a 48Khz stream can overflow after (2^64/10^9)/48K which
 * is about 384307 ie ~4.5 days.
 *
 * This scales the calculation so that overflow will happen but after 2^64 /
 * 48000 secs, which is pretty large!
 *
 * In caln below:
 *	base may overflow, but since there isnै t any additional भागision
 *	perक्रमmed on base itै s OK
 *	rem canै t overflow because both are 32-bit values
 */

#अगर_घोषित CONFIG_X86
अटल u64 azx_scale64(u64 base, u32 num, u32 den)
अणु
	u64 rem;

	rem = करो_भाग(base, den);

	base *= num;
	rem *= num;

	करो_भाग(rem, den);

	वापस base + rem;
पूर्ण

अटल पूर्णांक azx_get_sync_समय(kसमय_प्रकार *device,
		काष्ठा प्रणाली_counterval_t *प्रणाली, व्योम *ctx)
अणु
	काष्ठा snd_pcm_substream *substream = ctx;
	काष्ठा azx_dev *azx_dev = get_azx_dev(substream);
	काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
	काष्ठा azx *chip = apcm->chip;
	काष्ठा snd_pcm_runसमय *runसमय;
	u64 ll_counter, ll_counter_l, ll_counter_h;
	u64 tsc_counter, tsc_counter_l, tsc_counter_h;
	u32 wallclk_ctr, wallclk_cycles;
	bool direction;
	u32 dma_select;
	u32 समयout;
	u32 retry_count = 0;

	runसमय = substream->runसमय;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		direction = 1;
	अन्यथा
		direction = 0;

	/* 0th stream tag is not used, so DMA ch 0 is क्रम 1st stream tag */
	करो अणु
		समयout = 100;
		dma_select = (direction << GTSCC_CDMAS_DMA_सूची_SHIFT) |
					(azx_dev->core.stream_tag - 1);
		snd_hdac_chip_ग_लिखोl(azx_bus(chip), GTSCC, dma_select);

		/* Enable the capture */
		snd_hdac_chip_updatel(azx_bus(chip), GTSCC, 0, GTSCC_TSCCI_MASK);

		जबतक (समयout) अणु
			अगर (snd_hdac_chip_पढ़ोl(azx_bus(chip), GTSCC) &
						GTSCC_TSCCD_MASK)
				अवरोध;

			समयout--;
		पूर्ण

		अगर (!समयout) अणु
			dev_err(chip->card->dev, "GTSCC capture Timedout!\n");
			वापस -EIO;
		पूर्ण

		/* Read wall घड़ी counter */
		wallclk_ctr = snd_hdac_chip_पढ़ोl(azx_bus(chip), WALFCC);

		/* Read TSC counter */
		tsc_counter_l = snd_hdac_chip_पढ़ोl(azx_bus(chip), TSCCL);
		tsc_counter_h = snd_hdac_chip_पढ़ोl(azx_bus(chip), TSCCU);

		/* Read Link counter */
		ll_counter_l = snd_hdac_chip_पढ़ोl(azx_bus(chip), LLPCL);
		ll_counter_h = snd_hdac_chip_पढ़ोl(azx_bus(chip), LLPCU);

		/* Ack: रेजिस्टरs पढ़ो करोne */
		snd_hdac_chip_ग_लिखोl(azx_bus(chip), GTSCC, GTSCC_TSCCD_SHIFT);

		tsc_counter = (tsc_counter_h << TSCCU_CCU_SHIFT) |
						tsc_counter_l;

		ll_counter = (ll_counter_h << LLPC_CCU_SHIFT) |	ll_counter_l;
		wallclk_cycles = wallclk_ctr & WALFCC_CIF_MASK;

		/*
		 * An error occurs near frame "rollover". The घड़ीs in
		 * frame value indicates whether this error may have
		 * occurred. Here we use the value of 10 i.e.,
		 * HDA_MAX_CYCLE_OFFSET
		 */
		अगर (wallclk_cycles < HDA_MAX_CYCLE_VALUE - HDA_MAX_CYCLE_OFFSET
					&& wallclk_cycles > HDA_MAX_CYCLE_OFFSET)
			अवरोध;

		/*
		 * Sleep beक्रमe we पढ़ो again, अन्यथा we may again get
		 * value near to MAX_CYCLE. Try to sleep क्रम dअगरferent
		 * amount of समय so we करोnt hit the same number again
		 */
		udelay(retry_count++);

	पूर्ण जबतक (retry_count != HDA_MAX_CYCLE_READ_RETRY);

	अगर (retry_count == HDA_MAX_CYCLE_READ_RETRY) अणु
		dev_err_ratelimited(chip->card->dev,
			"Error in WALFCC cycle count\n");
		वापस -EIO;
	पूर्ण

	*device = ns_to_kसमय(azx_scale64(ll_counter,
				NSEC_PER_SEC, runसमय->rate));
	*device = kसमय_add_ns(*device, (wallclk_cycles * NSEC_PER_SEC) /
			       ((HDA_MAX_CYCLE_VALUE + 1) * runसमय->rate));

	*प्रणाली = convert_art_to_tsc(tsc_counter);

	वापस 0;
पूर्ण

#अन्यथा
अटल पूर्णांक azx_get_sync_समय(kसमय_प्रकार *device,
		काष्ठा प्रणाली_counterval_t *प्रणाली, व्योम *ctx)
अणु
	वापस -ENXIO;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक azx_get_crosststamp(काष्ठा snd_pcm_substream *substream,
			      काष्ठा प्रणाली_device_crosststamp *xtstamp)
अणु
	वापस get_device_प्रणाली_crosststamp(azx_get_sync_समय,
					substream, शून्य, xtstamp);
पूर्ण

अटल अंतरभूत bool is_link_समय_supported(काष्ठा snd_pcm_runसमय *runसमय,
				काष्ठा snd_pcm_audio_tstamp_config *ts)
अणु
	अगर (runसमय->hw.info & SNDRV_PCM_INFO_HAS_LINK_SYNCHRONIZED_ATIME)
		अगर (ts->type_requested == SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक azx_get_समय_info(काष्ठा snd_pcm_substream *substream,
			काष्ठा बारpec64 *प्रणाली_ts, काष्ठा बारpec64 *audio_ts,
			काष्ठा snd_pcm_audio_tstamp_config *audio_tstamp_config,
			काष्ठा snd_pcm_audio_tstamp_report *audio_tstamp_report)
अणु
	काष्ठा azx_dev *azx_dev = get_azx_dev(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा प्रणाली_device_crosststamp xtstamp;
	पूर्णांक ret;
	u64 nsec;

	अगर ((substream->runसमय->hw.info & SNDRV_PCM_INFO_HAS_LINK_ATIME) &&
		(audio_tstamp_config->type_requested == SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK)) अणु

		snd_pcm_समय_लो(substream->runसमय, प्रणाली_ts);

		nsec = समयcounter_पढ़ो(&azx_dev->core.tc);
		nsec = भाग_u64(nsec, 3); /* can be optimized */
		अगर (audio_tstamp_config->report_delay)
			nsec = azx_adjust_codec_delay(substream, nsec);

		*audio_ts = ns_to_बारpec64(nsec);

		audio_tstamp_report->actual_type = SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK;
		audio_tstamp_report->accuracy_report = 1; /* rest of काष्ठाure is valid */
		audio_tstamp_report->accuracy = 42; /* 24 MHz WallClock == 42ns resolution */

	पूर्ण अन्यथा अगर (is_link_समय_supported(runसमय, audio_tstamp_config)) अणु

		ret = azx_get_crosststamp(substream, &xtstamp);
		अगर (ret)
			वापस ret;

		चयन (runसमय->tstamp_type) अणु
		हाल SNDRV_PCM_TSTAMP_TYPE_MONOTONIC:
			वापस -EINVAL;

		हाल SNDRV_PCM_TSTAMP_TYPE_MONOTONIC_RAW:
			*प्रणाली_ts = kसमय_प्रकारo_बारpec64(xtstamp.sys_monoraw);
			अवरोध;

		शेष:
			*प्रणाली_ts = kसमय_प्रकारo_बारpec64(xtstamp.sys_realसमय);
			अवरोध;

		पूर्ण

		*audio_ts = kसमय_प्रकारo_बारpec64(xtstamp.device);

		audio_tstamp_report->actual_type =
			SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED;
		audio_tstamp_report->accuracy_report = 1;
		/* 24 MHz WallClock == 42ns resolution */
		audio_tstamp_report->accuracy = 42;

	पूर्ण अन्यथा अणु
		audio_tstamp_report->actual_type = SNDRV_PCM_AUDIO_TSTAMP_TYPE_DEFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware azx_pcm_hw = अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 /* No full-resume yet implemented */
				 /* SNDRV_PCM_INFO_RESUME |*/
				 SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_SYNC_START |
				 SNDRV_PCM_INFO_HAS_WALL_CLOCK | /* legacy */
				 SNDRV_PCM_INFO_HAS_LINK_ATIME |
				 SNDRV_PCM_INFO_NO_PERIOD_WAKEUP),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_48000,
	.rate_min =		48000,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	AZX_MAX_BUF_SIZE,
	.period_bytes_min =	128,
	.period_bytes_max =	AZX_MAX_BUF_SIZE / 2,
	.periods_min =		2,
	.periods_max =		AZX_MAX_FRAG,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक azx_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
	काष्ठा hda_pcm_stream *hinfo = to_hda_pcm_stream(substream);
	काष्ठा azx *chip = apcm->chip;
	काष्ठा azx_dev *azx_dev;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;
	पूर्णांक buff_step;

	snd_hda_codec_pcm_get(apcm->info);
	mutex_lock(&chip->खोलो_mutex);
	azx_dev = azx_assign_device(chip, substream);
	trace_azx_pcm_खोलो(chip, azx_dev);
	अगर (azx_dev == शून्य) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण
	runसमय->निजी_data = azx_dev;

	runसमय->hw = azx_pcm_hw;
	अगर (chip->gts_present)
		runसमय->hw.info |= SNDRV_PCM_INFO_HAS_LINK_SYNCHRONIZED_ATIME;
	runसमय->hw.channels_min = hinfo->channels_min;
	runसमय->hw.channels_max = hinfo->channels_max;
	runसमय->hw.क्रमmats = hinfo->क्रमmats;
	runसमय->hw.rates = hinfo->rates;
	snd_pcm_limit_hw_rates(runसमय);
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);

	/* aव्योम wrap-around with wall-घड़ी */
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_TIME,
				     20,
				     178000000);

	अगर (chip->align_buffer_size)
		/* स्थिरrain buffer sizes to be multiple of 128
		   bytes. This is more efficient in terms of memory
		   access but isn't required by the HDA spec and
		   prevents users from specअगरying exact period/buffer
		   sizes. For example क्रम 44.1kHz, a period size set
		   to 20ms will be rounded to 19.59ms. */
		buff_step = 128;
	अन्यथा
		/* Don't enक्रमce steps on buffer sizes, still need to
		   be multiple of 4 bytes (HDA spec). Tested on Intel
		   HDA controllers, may not work on all devices where
		   option needs to be disabled */
		buff_step = 4;

	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
				   buff_step);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
				   buff_step);
	snd_hda_घातer_up(apcm->codec);
	अगर (hinfo->ops.खोलो)
		err = hinfo->ops.खोलो(hinfo, apcm->codec, substream);
	अन्यथा
		err = -ENODEV;
	अगर (err < 0) अणु
		azx_release_device(azx_dev);
		जाओ घातerकरोwn;
	पूर्ण
	snd_pcm_limit_hw_rates(runसमय);
	/* sanity check */
	अगर (snd_BUG_ON(!runसमय->hw.channels_min) ||
	    snd_BUG_ON(!runसमय->hw.channels_max) ||
	    snd_BUG_ON(!runसमय->hw.क्रमmats) ||
	    snd_BUG_ON(!runसमय->hw.rates)) अणु
		azx_release_device(azx_dev);
		अगर (hinfo->ops.बंद)
			hinfo->ops.बंद(hinfo, apcm->codec, substream);
		err = -EINVAL;
		जाओ घातerकरोwn;
	पूर्ण

	/* disable LINK_ATIME बारtamps क्रम capture streams
	   until we figure out how to handle digital inमाला_दो */
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		runसमय->hw.info &= ~SNDRV_PCM_INFO_HAS_WALL_CLOCK; /* legacy */
		runसमय->hw.info &= ~SNDRV_PCM_INFO_HAS_LINK_ATIME;
	पूर्ण

	snd_pcm_set_sync(substream);
	mutex_unlock(&chip->खोलो_mutex);
	वापस 0;

 घातerकरोwn:
	snd_hda_घातer_करोwn(apcm->codec);
 unlock:
	mutex_unlock(&chip->खोलो_mutex);
	snd_hda_codec_pcm_put(apcm->info);
	वापस err;
पूर्ण

अटल पूर्णांक azx_pcm_mmap(काष्ठा snd_pcm_substream *substream,
			काष्ठा vm_area_काष्ठा *area)
अणु
	काष्ठा azx_pcm *apcm = snd_pcm_substream_chip(substream);
	काष्ठा azx *chip = apcm->chip;
	अगर (chip->ops->pcm_mmap_prepare)
		chip->ops->pcm_mmap_prepare(substream, area);
	वापस snd_pcm_lib_शेष_mmap(substream, area);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops azx_pcm_ops = अणु
	.खोलो = azx_pcm_खोलो,
	.बंद = azx_pcm_बंद,
	.hw_params = azx_pcm_hw_params,
	.hw_मुक्त = azx_pcm_hw_मुक्त,
	.prepare = azx_pcm_prepare,
	.trigger = azx_pcm_trigger,
	.poपूर्णांकer = azx_pcm_poपूर्णांकer,
	.get_समय_info =  azx_get_समय_info,
	.mmap = azx_pcm_mmap,
पूर्ण;

अटल व्योम azx_pcm_मुक्त(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा azx_pcm *apcm = pcm->निजी_data;
	अगर (apcm) अणु
		list_del(&apcm->list);
		apcm->info->pcm = शून्य;
		kमुक्त(apcm);
	पूर्ण
पूर्ण

#घोषणा MAX_PREALLOC_SIZE	(32 * 1024 * 1024)

पूर्णांक snd_hda_attach_pcm_stream(काष्ठा hda_bus *_bus, काष्ठा hda_codec *codec,
			      काष्ठा hda_pcm *cpcm)
अणु
	काष्ठा hdac_bus *bus = &_bus->core;
	काष्ठा azx *chip = bus_to_azx(bus);
	काष्ठा snd_pcm *pcm;
	काष्ठा azx_pcm *apcm;
	पूर्णांक pcm_dev = cpcm->device;
	अचिन्हित पूर्णांक size;
	पूर्णांक s, err;
	पूर्णांक type = SNDRV_DMA_TYPE_DEV_SG;

	list_क्रम_each_entry(apcm, &chip->pcm_list, list) अणु
		अगर (apcm->pcm->device == pcm_dev) अणु
			dev_err(chip->card->dev, "PCM %d already exists\n",
				pcm_dev);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	err = snd_pcm_new(chip->card, cpcm->name, pcm_dev,
			  cpcm->stream[SNDRV_PCM_STREAM_PLAYBACK].substreams,
			  cpcm->stream[SNDRV_PCM_STREAM_CAPTURE].substreams,
			  &pcm);
	अगर (err < 0)
		वापस err;
	strscpy(pcm->name, cpcm->name, माप(pcm->name));
	apcm = kzalloc(माप(*apcm), GFP_KERNEL);
	अगर (apcm == शून्य) अणु
		snd_device_मुक्त(chip->card, pcm);
		वापस -ENOMEM;
	पूर्ण
	apcm->chip = chip;
	apcm->pcm = pcm;
	apcm->codec = codec;
	apcm->info = cpcm;
	pcm->निजी_data = apcm;
	pcm->निजी_मुक्त = azx_pcm_मुक्त;
	अगर (cpcm->pcm_type == HDA_PCM_TYPE_MODEM)
		pcm->dev_class = SNDRV_PCM_CLASS_MODEM;
	list_add_tail(&apcm->list, &chip->pcm_list);
	cpcm->pcm = pcm;
	क्रम (s = 0; s < 2; s++) अणु
		अगर (cpcm->stream[s].substreams)
			snd_pcm_set_ops(pcm, s, &azx_pcm_ops);
	पूर्ण
	/* buffer pre-allocation */
	size = CONFIG_SND_HDA_PREALLOC_SIZE * 1024;
	अगर (size > MAX_PREALLOC_SIZE)
		size = MAX_PREALLOC_SIZE;
	अगर (chip->uc_buffer)
		type = SNDRV_DMA_TYPE_DEV_UC_SG;
	snd_pcm_set_managed_buffer_all(pcm, type, chip->card->dev,
				       size, MAX_PREALLOC_SIZE);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक azx_command_addr(u32 cmd)
अणु
	अचिन्हित पूर्णांक addr = cmd >> 28;

	अगर (addr >= AZX_MAX_CODECS) अणु
		snd_BUG();
		addr = 0;
	पूर्ण

	वापस addr;
पूर्ण

/* receive a response */
अटल पूर्णांक azx_rirb_get_response(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक addr,
				 अचिन्हित पूर्णांक *res)
अणु
	काष्ठा azx *chip = bus_to_azx(bus);
	काष्ठा hda_bus *hbus = &chip->bus;
	पूर्णांक err;

 again:
	err = snd_hdac_bus_get_response(bus, addr, res);
	अगर (!err)
		वापस 0;

	अगर (hbus->no_response_fallback)
		वापस -EIO;

	अगर (!bus->polling_mode) अणु
		dev_warn(chip->card->dev,
			 "azx_get_response timeout, switching to polling mode: last cmd=0x%08x\n",
			 bus->last_cmd[addr]);
		bus->polling_mode = 1;
		जाओ again;
	पूर्ण

	अगर (chip->msi) अणु
		dev_warn(chip->card->dev,
			 "No response from codec, disabling MSI: last cmd=0x%08x\n",
			 bus->last_cmd[addr]);
		अगर (chip->ops->disable_msi_reset_irq &&
		    chip->ops->disable_msi_reset_irq(chip) < 0)
			वापस -EIO;
		जाओ again;
	पूर्ण

	अगर (chip->probing) अणु
		/* If this critical समयout happens during the codec probing
		 * phase, this is likely an access to a non-existing codec
		 * slot.  Better to वापस an error and reset the प्रणाली.
		 */
		वापस -EIO;
	पूर्ण

	/* no fallback mechanism? */
	अगर (!chip->fallback_to_single_cmd)
		वापस -EIO;

	/* a fatal communication error; need either to reset or to fallback
	 * to the single_cmd mode
	 */
	अगर (hbus->allow_bus_reset && !hbus->response_reset && !hbus->in_reset) अणु
		hbus->response_reset = 1;
		dev_err(chip->card->dev,
			"No response from codec, resetting bus: last cmd=0x%08x\n",
			bus->last_cmd[addr]);
		वापस -EAGAIN; /* give a chance to retry */
	पूर्ण

	dev_err(chip->card->dev,
		"azx_get_response timeout, switching to single_cmd mode: last cmd=0x%08x\n",
		bus->last_cmd[addr]);
	chip->single_cmd = 1;
	hbus->response_reset = 0;
	snd_hdac_bus_stop_cmd_io(bus);
	वापस -EIO;
पूर्ण

/*
 * Use the single immediate command instead of CORB/RIRB क्रम simplicity
 *
 * Note: according to Intel, this is not preferred use.  The command was
 *       पूर्णांकended क्रम the BIOS only, and may get confused with unsolicited
 *       responses.  So, we shouldn't use it क्रम normal operation from the
 *       driver.
 *       I left the codes, however, क्रम debugging/testing purposes.
 */

/* receive a response */
अटल पूर्णांक azx_single_रुको_क्रम_response(काष्ठा azx *chip, अचिन्हित पूर्णांक addr)
अणु
	पूर्णांक समयout = 50;

	जबतक (समयout--) अणु
		/* check IRV busy bit */
		अगर (azx_पढ़ोw(chip, IRS) & AZX_IRS_VALID) अणु
			/* reuse rirb.res as the response वापस value */
			azx_bus(chip)->rirb.res[addr] = azx_पढ़ोl(chip, IR);
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	अगर (prपूर्णांकk_ratelimit())
		dev_dbg(chip->card->dev, "get_response timeout: IRS=0x%x\n",
			azx_पढ़ोw(chip, IRS));
	azx_bus(chip)->rirb.res[addr] = -1;
	वापस -EIO;
पूर्ण

/* send a command */
अटल पूर्णांक azx_single_send_cmd(काष्ठा hdac_bus *bus, u32 val)
अणु
	काष्ठा azx *chip = bus_to_azx(bus);
	अचिन्हित पूर्णांक addr = azx_command_addr(val);
	पूर्णांक समयout = 50;

	bus->last_cmd[azx_command_addr(val)] = val;
	जबतक (समयout--) अणु
		/* check ICB busy bit */
		अगर (!((azx_पढ़ोw(chip, IRS) & AZX_IRS_BUSY))) अणु
			/* Clear IRV valid bit */
			azx_ग_लिखोw(chip, IRS, azx_पढ़ोw(chip, IRS) |
				   AZX_IRS_VALID);
			azx_ग_लिखोl(chip, IC, val);
			azx_ग_लिखोw(chip, IRS, azx_पढ़ोw(chip, IRS) |
				   AZX_IRS_BUSY);
			वापस azx_single_रुको_क्रम_response(chip, addr);
		पूर्ण
		udelay(1);
	पूर्ण
	अगर (prपूर्णांकk_ratelimit())
		dev_dbg(chip->card->dev,
			"send_cmd timeout: IRS=0x%x, val=0x%x\n",
			azx_पढ़ोw(chip, IRS), val);
	वापस -EIO;
पूर्ण

/* receive a response */
अटल पूर्णांक azx_single_get_response(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक addr,
				   अचिन्हित पूर्णांक *res)
अणु
	अगर (res)
		*res = bus->rirb.res[addr];
	वापस 0;
पूर्ण

/*
 * The below are the मुख्य callbacks from hda_codec.
 *
 * They are just the skeleton to call sub-callbacks according to the
 * current setting of chip->single_cmd.
 */

/* send a command */
अटल पूर्णांक azx_send_cmd(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक val)
अणु
	काष्ठा azx *chip = bus_to_azx(bus);

	अगर (chip->disabled)
		वापस 0;
	अगर (chip->single_cmd)
		वापस azx_single_send_cmd(bus, val);
	अन्यथा
		वापस snd_hdac_bus_send_cmd(bus, val);
पूर्ण

/* get a response */
अटल पूर्णांक azx_get_response(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक addr,
			    अचिन्हित पूर्णांक *res)
अणु
	काष्ठा azx *chip = bus_to_azx(bus);

	अगर (chip->disabled)
		वापस 0;
	अगर (chip->single_cmd)
		वापस azx_single_get_response(bus, addr, res);
	अन्यथा
		वापस azx_rirb_get_response(bus, addr, res);
पूर्ण

अटल स्थिर काष्ठा hdac_bus_ops bus_core_ops = अणु
	.command = azx_send_cmd,
	.get_response = azx_get_response,
पूर्ण;

#अगर_घोषित CONFIG_SND_HDA_DSP_LOADER
/*
 * DSP loading code (e.g. क्रम CA0132)
 */

/* use the first stream क्रम loading DSP */
अटल काष्ठा azx_dev *
azx_get_dsp_loader_dev(काष्ठा azx *chip)
अणु
	काष्ठा hdac_bus *bus = azx_bus(chip);
	काष्ठा hdac_stream *s;

	list_क्रम_each_entry(s, &bus->stream_list, list)
		अगर (s->index == chip->playback_index_offset)
			वापस stream_to_azx_dev(s);

	वापस शून्य;
पूर्ण

पूर्णांक snd_hda_codec_load_dsp_prepare(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक क्रमmat,
				   अचिन्हित पूर्णांक byte_size,
				   काष्ठा snd_dma_buffer *bufp)
अणु
	काष्ठा hdac_bus *bus = &codec->bus->core;
	काष्ठा azx *chip = bus_to_azx(bus);
	काष्ठा azx_dev *azx_dev;
	काष्ठा hdac_stream *hstr;
	bool saved = false;
	पूर्णांक err;

	azx_dev = azx_get_dsp_loader_dev(chip);
	hstr = azx_stream(azx_dev);
	spin_lock_irq(&bus->reg_lock);
	अगर (hstr->खोलोed) अणु
		chip->saved_azx_dev = *azx_dev;
		saved = true;
	पूर्ण
	spin_unlock_irq(&bus->reg_lock);

	err = snd_hdac_dsp_prepare(hstr, क्रमmat, byte_size, bufp);
	अगर (err < 0) अणु
		spin_lock_irq(&bus->reg_lock);
		अगर (saved)
			*azx_dev = chip->saved_azx_dev;
		spin_unlock_irq(&bus->reg_lock);
		वापस err;
	पूर्ण

	hstr->prepared = 0;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_load_dsp_prepare);

व्योम snd_hda_codec_load_dsp_trigger(काष्ठा hda_codec *codec, bool start)
अणु
	काष्ठा hdac_bus *bus = &codec->bus->core;
	काष्ठा azx *chip = bus_to_azx(bus);
	काष्ठा azx_dev *azx_dev = azx_get_dsp_loader_dev(chip);

	snd_hdac_dsp_trigger(azx_stream(azx_dev), start);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_load_dsp_trigger);

व्योम snd_hda_codec_load_dsp_cleanup(काष्ठा hda_codec *codec,
				    काष्ठा snd_dma_buffer *dmab)
अणु
	काष्ठा hdac_bus *bus = &codec->bus->core;
	काष्ठा azx *chip = bus_to_azx(bus);
	काष्ठा azx_dev *azx_dev = azx_get_dsp_loader_dev(chip);
	काष्ठा hdac_stream *hstr = azx_stream(azx_dev);

	अगर (!dmab->area || !hstr->locked)
		वापस;

	snd_hdac_dsp_cleanup(hstr, dmab);
	spin_lock_irq(&bus->reg_lock);
	अगर (hstr->खोलोed)
		*azx_dev = chip->saved_azx_dev;
	hstr->locked = false;
	spin_unlock_irq(&bus->reg_lock);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_load_dsp_cleanup);
#पूर्ण_अगर /* CONFIG_SND_HDA_DSP_LOADER */

/*
 * reset and start the controller रेजिस्टरs
 */
व्योम azx_init_chip(काष्ठा azx *chip, bool full_reset)
अणु
	अगर (snd_hdac_bus_init_chip(azx_bus(chip), full_reset)) अणु
		/* correct RINTCNT क्रम CXT */
		अगर (chip->driver_caps & AZX_DCAPS_CTX_WORKAROUND)
			azx_ग_लिखोw(chip, RINTCNT, 0xc0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(azx_init_chip);

व्योम azx_stop_all_streams(काष्ठा azx *chip)
अणु
	काष्ठा hdac_bus *bus = azx_bus(chip);
	काष्ठा hdac_stream *s;

	list_क्रम_each_entry(s, &bus->stream_list, list)
		snd_hdac_stream_stop(s);
पूर्ण
EXPORT_SYMBOL_GPL(azx_stop_all_streams);

व्योम azx_stop_chip(काष्ठा azx *chip)
अणु
	snd_hdac_bus_stop_chip(azx_bus(chip));
पूर्ण
EXPORT_SYMBOL_GPL(azx_stop_chip);

/*
 * पूर्णांकerrupt handler
 */
अटल व्योम stream_update(काष्ठा hdac_bus *bus, काष्ठा hdac_stream *s)
अणु
	काष्ठा azx *chip = bus_to_azx(bus);
	काष्ठा azx_dev *azx_dev = stream_to_azx_dev(s);

	/* check whether this IRQ is really acceptable */
	अगर (!chip->ops->position_check ||
	    chip->ops->position_check(chip, azx_dev)) अणु
		spin_unlock(&bus->reg_lock);
		snd_pcm_period_elapsed(azx_stream(azx_dev)->substream);
		spin_lock(&bus->reg_lock);
	पूर्ण
पूर्ण

irqवापस_t azx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा azx *chip = dev_id;
	काष्ठा hdac_bus *bus = azx_bus(chip);
	u32 status;
	bool active, handled = false;
	पूर्णांक repeat = 0; /* count क्रम aव्योमing endless loop */

#अगर_घोषित CONFIG_PM
	अगर (azx_has_pm_runसमय(chip))
		अगर (!pm_runसमय_active(chip->card->dev))
			वापस IRQ_NONE;
#पूर्ण_अगर

	spin_lock(&bus->reg_lock);

	अगर (chip->disabled)
		जाओ unlock;

	करो अणु
		status = azx_पढ़ोl(chip, INTSTS);
		अगर (status == 0 || status == 0xffffffff)
			अवरोध;

		handled = true;
		active = false;
		अगर (snd_hdac_bus_handle_stream_irq(bus, status, stream_update))
			active = true;

		status = azx_पढ़ोb(chip, RIRBSTS);
		अगर (status & RIRB_INT_MASK) अणु
			/*
			 * Clearing the पूर्णांकerrupt status here ensures that no
			 * पूर्णांकerrupt माला_लो masked after the RIRB wp is पढ़ो in
			 * snd_hdac_bus_update_rirb. This aव्योमs a possible
			 * race condition where codec response in RIRB may
			 * reमुख्य unserviced by IRQ, eventually falling back
			 * to polling mode in azx_rirb_get_response.
			 */
			azx_ग_लिखोb(chip, RIRBSTS, RIRB_INT_MASK);
			active = true;
			अगर (status & RIRB_INT_RESPONSE) अणु
				अगर (chip->driver_caps & AZX_DCAPS_CTX_WORKAROUND)
					udelay(80);
				snd_hdac_bus_update_rirb(bus);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (active && ++repeat < 10);

 unlock:
	spin_unlock(&bus->reg_lock);

	वापस IRQ_RETVAL(handled);
पूर्ण
EXPORT_SYMBOL_GPL(azx_पूर्णांकerrupt);

/*
 * Codec initerface
 */

/*
 * Probe the given codec address
 */
अटल पूर्णांक probe_codec(काष्ठा azx *chip, पूर्णांक addr)
अणु
	अचिन्हित पूर्णांक cmd = (addr << 28) | (AC_NODE_ROOT << 20) |
		(AC_VERB_PARAMETERS << 8) | AC_PAR_VENDOR_ID;
	काष्ठा hdac_bus *bus = azx_bus(chip);
	पूर्णांक err;
	अचिन्हित पूर्णांक res = -1;

	mutex_lock(&bus->cmd_mutex);
	chip->probing = 1;
	azx_send_cmd(bus, cmd);
	err = azx_get_response(bus, addr, &res);
	chip->probing = 0;
	mutex_unlock(&bus->cmd_mutex);
	अगर (err < 0 || res == -1)
		वापस -EIO;
	dev_dbg(chip->card->dev, "codec #%d probed OK\n", addr);
	वापस 0;
पूर्ण

व्योम snd_hda_bus_reset(काष्ठा hda_bus *bus)
अणु
	काष्ठा azx *chip = bus_to_azx(&bus->core);

	bus->in_reset = 1;
	azx_stop_chip(chip);
	azx_init_chip(chip, true);
	अगर (bus->core.chip_init)
		snd_hda_bus_reset_codecs(bus);
	bus->in_reset = 0;
पूर्ण

/* HD-audio bus initialization */
पूर्णांक azx_bus_init(काष्ठा azx *chip, स्थिर अक्षर *model)
अणु
	काष्ठा hda_bus *bus = &chip->bus;
	पूर्णांक err;

	err = snd_hdac_bus_init(&bus->core, chip->card->dev, &bus_core_ops);
	अगर (err < 0)
		वापस err;

	bus->card = chip->card;
	mutex_init(&bus->prepare_mutex);
	bus->pci = chip->pci;
	bus->modelname = model;
	bus->mixer_asचिन्हित = -1;
	bus->core.snoop = azx_snoop(chip);
	अगर (chip->get_position[0] != azx_get_pos_lpib ||
	    chip->get_position[1] != azx_get_pos_lpib)
		bus->core.use_posbuf = true;
	bus->core.bdl_pos_adj = chip->bdl_pos_adj;
	अगर (chip->driver_caps & AZX_DCAPS_CORBRP_SELF_CLEAR)
		bus->core.corbrp_self_clear = true;

	अगर (chip->driver_caps & AZX_DCAPS_4K_BDLE_BOUNDARY)
		bus->core.align_bdle_4k = true;

	/* enable sync_ग_लिखो flag क्रम stable communication as शेष */
	bus->core.sync_ग_लिखो = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(azx_bus_init);

/* Probe codecs */
पूर्णांक azx_probe_codecs(काष्ठा azx *chip, अचिन्हित पूर्णांक max_slots)
अणु
	काष्ठा hdac_bus *bus = azx_bus(chip);
	पूर्णांक c, codecs, err;

	codecs = 0;
	अगर (!max_slots)
		max_slots = AZX_DEFAULT_CODECS;

	/* First try to probe all given codec slots */
	क्रम (c = 0; c < max_slots; c++) अणु
		अगर ((bus->codec_mask & (1 << c)) & chip->codec_probe_mask) अणु
			अगर (probe_codec(chip, c) < 0) अणु
				/* Some BIOSen give you wrong codec addresses
				 * that करोn't exist
				 */
				dev_warn(chip->card->dev,
					 "Codec #%d probe error; disabling it...\n", c);
				bus->codec_mask &= ~(1 << c);
				/* More badly, accessing to a non-existing
				 * codec often screws up the controller chip,
				 * and disturbs the further communications.
				 * Thus अगर an error occurs during probing,
				 * better to reset the controller chip to
				 * get back to the sanity state.
				 */
				azx_stop_chip(chip);
				azx_init_chip(chip, true);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Then create codec instances */
	क्रम (c = 0; c < max_slots; c++) अणु
		अगर ((bus->codec_mask & (1 << c)) & chip->codec_probe_mask) अणु
			काष्ठा hda_codec *codec;
			err = snd_hda_codec_new(&chip->bus, chip->card, c, &codec);
			अगर (err < 0)
				जारी;
			codec->jackpoll_पूर्णांकerval = chip->jackpoll_पूर्णांकerval;
			codec->beep_mode = chip->beep_mode;
			codecs++;
		पूर्ण
	पूर्ण
	अगर (!codecs) अणु
		dev_err(chip->card->dev, "no codecs initialized\n");
		वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(azx_probe_codecs);

/* configure each codec instance */
पूर्णांक azx_codec_configure(काष्ठा azx *chip)
अणु
	काष्ठा hda_codec *codec, *next;

	/* use _safe version here since snd_hda_codec_configure() deरेजिस्टरs
	 * the device upon error and deletes itself from the bus list.
	 */
	list_क्रम_each_codec_safe(codec, next, &chip->bus) अणु
		snd_hda_codec_configure(codec);
	पूर्ण

	अगर (!azx_bus(chip)->num_codecs)
		वापस -ENODEV;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(azx_codec_configure);

अटल पूर्णांक stream_direction(काष्ठा azx *chip, अचिन्हित अक्षर index)
अणु
	अगर (index >= chip->capture_index_offset &&
	    index < chip->capture_index_offset + chip->capture_streams)
		वापस SNDRV_PCM_STREAM_CAPTURE;
	वापस SNDRV_PCM_STREAM_PLAYBACK;
पूर्ण

/* initialize SD streams */
पूर्णांक azx_init_streams(काष्ठा azx *chip)
अणु
	पूर्णांक i;
	पूर्णांक stream_tags[2] = अणु 0, 0 पूर्ण;

	/* initialize each stream (aka device)
	 * assign the starting bdl address to each stream (device)
	 * and initialize
	 */
	क्रम (i = 0; i < chip->num_streams; i++) अणु
		काष्ठा azx_dev *azx_dev = kzalloc(माप(*azx_dev), GFP_KERNEL);
		पूर्णांक dir, tag;

		अगर (!azx_dev)
			वापस -ENOMEM;

		dir = stream_direction(chip, i);
		/* stream tag must be unique throughout
		 * the stream direction group,
		 * valid values 1...15
		 * use separate stream tag अगर the flag
		 * AZX_DCAPS_SEPARATE_STREAM_TAG is used
		 */
		अगर (chip->driver_caps & AZX_DCAPS_SEPARATE_STREAM_TAG)
			tag = ++stream_tags[dir];
		अन्यथा
			tag = i + 1;
		snd_hdac_stream_init(azx_bus(chip), azx_stream(azx_dev),
				     i, dir, tag);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(azx_init_streams);

व्योम azx_मुक्त_streams(काष्ठा azx *chip)
अणु
	काष्ठा hdac_bus *bus = azx_bus(chip);
	काष्ठा hdac_stream *s;

	जबतक (!list_empty(&bus->stream_list)) अणु
		s = list_first_entry(&bus->stream_list, काष्ठा hdac_stream, list);
		list_del(&s->list);
		kमुक्त(stream_to_azx_dev(s));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(azx_मुक्त_streams);
