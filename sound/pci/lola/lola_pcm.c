<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Support क्रम Digigram Lola PCI-e boards
 *
 *  Copyright (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश "lola.h"

#घोषणा LOLA_MAX_BDL_ENTRIES	8
#घोषणा LOLA_MAX_BUF_SIZE	(1024*1024*1024)
#घोषणा LOLA_BDL_ENTRY_SIZE	(16 * 16)

अटल काष्ठा lola_pcm *lola_get_pcm(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा lola *chip = snd_pcm_substream_chip(substream);
	वापस &chip->pcm[substream->stream];
पूर्ण

अटल काष्ठा lola_stream *lola_get_stream(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा lola_pcm *pcm = lola_get_pcm(substream);
	अचिन्हित पूर्णांक idx = substream->number;
	वापस &pcm->streams[idx];
पूर्ण

अटल अचिन्हित पूर्णांक lola_get_lrc(काष्ठा lola *chip)
अणु
	वापस lola_पढ़ोl(chip, BAR1, LRC);
पूर्ण

अटल अचिन्हित पूर्णांक lola_get_tstamp(काष्ठा lola *chip, bool quick_no_sync)
अणु
	अचिन्हित पूर्णांक tstamp = lola_get_lrc(chip) >> 8;
	अगर (chip->granularity) अणु
		अचिन्हित पूर्णांक रुको_banks = quick_no_sync ? 0 : 8;
		tstamp += (रुको_banks + 1) * chip->granularity - 1;
		tstamp -= tstamp % chip->granularity;
	पूर्ण
	वापस tstamp << 8;
पूर्ण

/* clear any pending पूर्णांकerrupt status */
अटल व्योम lola_stream_clear_pending_irq(काष्ठा lola *chip,
					  काष्ठा lola_stream *str)
अणु
	अचिन्हित पूर्णांक val = lola_dsd_पढ़ो(chip, str->dsd, STS);
	val &= LOLA_DSD_STS_DESE | LOLA_DSD_STS_BCIS;
	अगर (val)
		lola_dsd_ग_लिखो(chip, str->dsd, STS, val);
पूर्ण

अटल व्योम lola_stream_start(काष्ठा lola *chip, काष्ठा lola_stream *str,
			      अचिन्हित पूर्णांक tstamp)
अणु
	lola_stream_clear_pending_irq(chip, str);
	lola_dsd_ग_लिखो(chip, str->dsd, CTL,
		       LOLA_DSD_CTL_SRUN |
		       LOLA_DSD_CTL_IOCE |
		       LOLA_DSD_CTL_DEIE |
		       LOLA_DSD_CTL_VLRCV |
		       tstamp);
पूर्ण

अटल व्योम lola_stream_stop(काष्ठा lola *chip, काष्ठा lola_stream *str,
			     अचिन्हित पूर्णांक tstamp)
अणु
	lola_dsd_ग_लिखो(chip, str->dsd, CTL,
		       LOLA_DSD_CTL_IOCE |
		       LOLA_DSD_CTL_DEIE |
		       LOLA_DSD_CTL_VLRCV |
		       tstamp);
	lola_stream_clear_pending_irq(chip, str);
पूर्ण

अटल व्योम रुको_क्रम_srst_clear(काष्ठा lola *chip, काष्ठा lola_stream *str)
अणु
	अचिन्हित दीर्घ end_समय = jअगरfies + msecs_to_jअगरfies(200);
	जबतक (समय_beक्रमe(jअगरfies, end_समय)) अणु
		अचिन्हित पूर्णांक val;
		val = lola_dsd_पढ़ो(chip, str->dsd, CTL);
		अगर (!(val & LOLA_DSD_CTL_SRST))
			वापस;
		msleep(1);
	पूर्ण
	dev_warn(chip->card->dev, "SRST not clear (stream %d)\n", str->dsd);
पूर्ण

अटल पूर्णांक lola_stream_रुको_क्रम_fअगरo(काष्ठा lola *chip,
				     काष्ठा lola_stream *str,
				     bool पढ़ोy)
अणु
	अचिन्हित पूर्णांक val = पढ़ोy ? LOLA_DSD_STS_FIFORDY : 0;
	अचिन्हित दीर्घ end_समय = jअगरfies + msecs_to_jअगरfies(200);
	जबतक (समय_beक्रमe(jअगरfies, end_समय)) अणु
		अचिन्हित पूर्णांक reg = lola_dsd_पढ़ो(chip, str->dsd, STS);
		अगर ((reg & LOLA_DSD_STS_FIFORDY) == val)
			वापस 0;
		msleep(1);
	पूर्ण
	dev_warn(chip->card->dev, "FIFO not ready (stream %d)\n", str->dsd);
	वापस -EIO;
पूर्ण

/* sync क्रम FIFO पढ़ोy/empty क्रम all linked streams;
 * clear छोड़ोd flag when FIFO माला_लो पढ़ोy again
 */
अटल पूर्णांक lola_sync_रुको_क्रम_fअगरo(काष्ठा lola *chip,
				   काष्ठा snd_pcm_substream *substream,
				   bool पढ़ोy)
अणु
	अचिन्हित पूर्णांक val = पढ़ोy ? LOLA_DSD_STS_FIFORDY : 0;
	अचिन्हित दीर्घ end_समय = jअगरfies + msecs_to_jअगरfies(200);
	काष्ठा snd_pcm_substream *s;
	पूर्णांक pending = 0;

	जबतक (समय_beक्रमe(jअगरfies, end_समय)) अणु
		pending = 0;
		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			काष्ठा lola_stream *str;
			अगर (s->pcm->card != substream->pcm->card)
				जारी;
			str = lola_get_stream(s);
			अगर (str->prepared && str->छोड़ोd) अणु
				अचिन्हित पूर्णांक reg;
				reg = lola_dsd_पढ़ो(chip, str->dsd, STS);
				अगर ((reg & LOLA_DSD_STS_FIFORDY) != val) अणु
					pending = str->dsd + 1;
					अवरोध;
				पूर्ण
				अगर (पढ़ोy)
					str->छोड़ोd = 0;
			पूर्ण
		पूर्ण
		अगर (!pending)
			वापस 0;
		msleep(1);
	पूर्ण
	dev_warn(chip->card->dev, "FIFO not ready (pending %d)\n", pending - 1);
	वापस -EIO;
पूर्ण

/* finish छोड़ो - prepare क्रम a new resume */
अटल व्योम lola_sync_छोड़ो(काष्ठा lola *chip,
			    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_substream *s;

	lola_sync_रुको_क्रम_fअगरo(chip, substream, false);
	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		काष्ठा lola_stream *str;
		अगर (s->pcm->card != substream->pcm->card)
			जारी;
		str = lola_get_stream(s);
		अगर (str->छोड़ोd && str->prepared)
			lola_dsd_ग_लिखो(chip, str->dsd, CTL, LOLA_DSD_CTL_SRUN |
				       LOLA_DSD_CTL_IOCE | LOLA_DSD_CTL_DEIE);
	पूर्ण
	lola_sync_रुको_क्रम_fअगरo(chip, substream, true);
पूर्ण

अटल व्योम lola_stream_reset(काष्ठा lola *chip, काष्ठा lola_stream *str)
अणु
	अगर (str->prepared) अणु
		अगर (str->छोड़ोd)
			lola_sync_छोड़ो(chip, str->substream);
		str->prepared = 0;
		lola_dsd_ग_लिखो(chip, str->dsd, CTL,
			       LOLA_DSD_CTL_IOCE | LOLA_DSD_CTL_DEIE);
		lola_stream_रुको_क्रम_fअगरo(chip, str, false);
		lola_stream_clear_pending_irq(chip, str);
		lola_dsd_ग_लिखो(chip, str->dsd, CTL, LOLA_DSD_CTL_SRST);
		lola_dsd_ग_लिखो(chip, str->dsd, LVI, 0);
		lola_dsd_ग_लिखो(chip, str->dsd, BDPU, 0);
		lola_dsd_ग_लिखो(chip, str->dsd, BDPL, 0);
		रुको_क्रम_srst_clear(chip, str);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware lola_pcm_hw = अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_PAUSE),
	.क्रमmats =		(SNDRV_PCM_FMTBIT_S16_LE |
				 SNDRV_PCM_FMTBIT_S24_LE |
				 SNDRV_PCM_FMTBIT_S32_LE |
				 SNDRV_PCM_FMTBIT_FLOAT_LE),
	.rates =		SNDRV_PCM_RATE_8000_192000,
	.rate_min =		8000,
	.rate_max =		192000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	LOLA_MAX_BUF_SIZE,
	.period_bytes_min =	128,
	.period_bytes_max =	LOLA_MAX_BUF_SIZE / 2,
	.periods_min =		2,
	.periods_max =		LOLA_MAX_BDL_ENTRIES,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक lola_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा lola *chip = snd_pcm_substream_chip(substream);
	काष्ठा lola_pcm *pcm = lola_get_pcm(substream);
	काष्ठा lola_stream *str = lola_get_stream(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	mutex_lock(&chip->खोलो_mutex);
	अगर (str->खोलोed) अणु
		mutex_unlock(&chip->खोलो_mutex);
		वापस -EBUSY;
	पूर्ण
	str->substream = substream;
	str->master = शून्य;
	str->खोलोed = 1;
	runसमय->hw = lola_pcm_hw;
	runसमय->hw.channels_max = pcm->num_streams - str->index;
	अगर (chip->sample_rate) अणु
		/* sample rate is locked */
		runसमय->hw.rate_min = chip->sample_rate;
		runसमय->hw.rate_max = chip->sample_rate;
	पूर्ण अन्यथा अणु
		runसमय->hw.rate_min = chip->sample_rate_min;
		runसमय->hw.rate_max = chip->sample_rate_max;
	पूर्ण
	chip->ref_count_rate++;
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	/* period size = multiple of chip->granularity (8, 16 or 32 frames)*/
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
				   chip->granularity);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
				   chip->granularity);
	mutex_unlock(&chip->खोलो_mutex);
	वापस 0;
पूर्ण

अटल व्योम lola_cleanup_slave_streams(काष्ठा lola_pcm *pcm,
				       काष्ठा lola_stream *str)
अणु
	पूर्णांक i;
	क्रम (i = str->index + 1; i < pcm->num_streams; i++) अणु
		काष्ठा lola_stream *s = &pcm->streams[i];
		अगर (s->master != str)
			अवरोध;
		s->master = शून्य;
		s->खोलोed = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक lola_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा lola *chip = snd_pcm_substream_chip(substream);
	काष्ठा lola_stream *str = lola_get_stream(substream);

	mutex_lock(&chip->खोलो_mutex);
	अगर (str->substream == substream) अणु
		str->substream = शून्य;
		str->खोलोed = 0;
	पूर्ण
	अगर (--chip->ref_count_rate == 0) अणु
		/* release sample rate */
		chip->sample_rate = 0;
	पूर्ण
	mutex_unlock(&chip->खोलो_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक lola_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा lola_stream *str = lola_get_stream(substream);

	str->bufsize = 0;
	str->period_bytes = 0;
	str->क्रमmat_verb = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक lola_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा lola *chip = snd_pcm_substream_chip(substream);
	काष्ठा lola_pcm *pcm = lola_get_pcm(substream);
	काष्ठा lola_stream *str = lola_get_stream(substream);

	mutex_lock(&chip->खोलो_mutex);
	lola_stream_reset(chip, str);
	lola_cleanup_slave_streams(pcm, str);
	mutex_unlock(&chip->खोलो_mutex);
	वापस 0;
पूर्ण

/*
 * set up a BDL entry
 */
अटल पूर्णांक setup_bdle(काष्ठा snd_pcm_substream *substream,
		      काष्ठा lola_stream *str, __le32 **bdlp,
		      पूर्णांक ofs, पूर्णांक size)
अणु
	__le32 *bdl = *bdlp;

	जबतक (size > 0) अणु
		dma_addr_t addr;
		पूर्णांक chunk;

		अगर (str->frags >= LOLA_MAX_BDL_ENTRIES)
			वापस -EINVAL;

		addr = snd_pcm_sgbuf_get_addr(substream, ofs);
		/* program the address field of the BDL entry */
		bdl[0] = cpu_to_le32((u32)addr);
		bdl[1] = cpu_to_le32(upper_32_bits(addr));
		/* program the size field of the BDL entry */
		chunk = snd_pcm_sgbuf_get_chunk_size(substream, ofs, size);
		bdl[2] = cpu_to_le32(chunk);
		/* program the IOC to enable पूर्णांकerrupt
		 * only when the whole fragment is processed
		 */
		size -= chunk;
		bdl[3] = size ? 0 : cpu_to_le32(0x01);
		bdl += 4;
		str->frags++;
		ofs += chunk;
	पूर्ण
	*bdlp = bdl;
	वापस ofs;
पूर्ण

/*
 * set up BDL entries
 */
अटल पूर्णांक lola_setup_periods(काष्ठा lola *chip, काष्ठा lola_pcm *pcm,
			      काष्ठा snd_pcm_substream *substream,
			      काष्ठा lola_stream *str)
अणु
	__le32 *bdl;
	पूर्णांक i, ofs, periods, period_bytes;

	period_bytes = str->period_bytes;
	periods = str->bufsize / period_bytes;

	/* program the initial BDL entries */
	bdl = (__le32 *)(pcm->bdl.area + LOLA_BDL_ENTRY_SIZE * str->index);
	ofs = 0;
	str->frags = 0;
	क्रम (i = 0; i < periods; i++) अणु
		ofs = setup_bdle(substream, str, &bdl, ofs, period_bytes);
		अगर (ofs < 0)
			जाओ error;
	पूर्ण
	वापस 0;

 error:
	dev_err(chip->card->dev, "Too many BDL entries: buffer=%d, period=%d\n",
		   str->bufsize, period_bytes);
	वापस -EINVAL;
पूर्ण

अटल अचिन्हित पूर्णांक lola_get_क्रमmat_verb(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित पूर्णांक verb;

	चयन (substream->runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		verb = 0x00000000;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		verb = 0x00000200;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		verb = 0x00000300;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_FLOAT_LE:
		verb = 0x00001300;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	verb |= substream->runसमय->channels;
	वापस verb;
पूर्ण

अटल पूर्णांक lola_set_stream_config(काष्ठा lola *chip,
				  काष्ठा lola_stream *str,
				  पूर्णांक channels)
अणु
	पूर्णांक i, err;
	अचिन्हित पूर्णांक verb, val;

	/* set क्रमmat info क्रम all channels
	 * (with only one command क्रम the first channel)
	 */
	err = lola_codec_पढ़ो(chip, str->nid, LOLA_VERB_SET_STREAM_FORMAT,
			      str->क्रमmat_verb, 0, &val, शून्य);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "Cannot set stream format 0x%x\n",
		       str->क्रमmat_verb);
		वापस err;
	पूर्ण

	/* update stream - channel config */
	क्रम (i = 0; i < channels; i++) अणु
		verb = (str->index << 6) | i;
		err = lola_codec_पढ़ो(chip, str[i].nid,
				      LOLA_VERB_SET_CHANNEL_STREAMID, 0, verb,
				      &val, शून्य);
		अगर (err < 0) अणु
			dev_err(chip->card->dev,
				"Cannot set stream channel %d\n", i);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * set up the SD क्रम streaming
 */
अटल पूर्णांक lola_setup_controller(काष्ठा lola *chip, काष्ठा lola_pcm *pcm,
				 काष्ठा lola_stream *str)
अणु
	dma_addr_t bdl;

	अगर (str->prepared)
		वापस -EINVAL;

	/* set up BDL */
	bdl = pcm->bdl.addr + LOLA_BDL_ENTRY_SIZE * str->index;
	lola_dsd_ग_लिखो(chip, str->dsd, BDPL, (u32)bdl);
	lola_dsd_ग_लिखो(chip, str->dsd, BDPU, upper_32_bits(bdl));
	/* program the stream LVI (last valid index) of the BDL */
	lola_dsd_ग_लिखो(chip, str->dsd, LVI, str->frags - 1);
	lola_stream_clear_pending_irq(chip, str);

 	lola_dsd_ग_लिखो(chip, str->dsd, CTL,
		       LOLA_DSD_CTL_IOCE | LOLA_DSD_CTL_DEIE | LOLA_DSD_CTL_SRUN);

	str->prepared = 1;

	वापस lola_stream_रुको_क्रम_fअगरo(chip, str, true);
पूर्ण

अटल पूर्णांक lola_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा lola *chip = snd_pcm_substream_chip(substream);
	काष्ठा lola_pcm *pcm = lola_get_pcm(substream);
	काष्ठा lola_stream *str = lola_get_stream(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक bufsize, period_bytes, क्रमmat_verb;
	पूर्णांक i, err;

	mutex_lock(&chip->खोलो_mutex);
	lola_stream_reset(chip, str);
	lola_cleanup_slave_streams(pcm, str);
	अगर (str->index + runसमय->channels > pcm->num_streams) अणु
		mutex_unlock(&chip->खोलो_mutex);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 1; i < runसमय->channels; i++) अणु
		str[i].master = str;
		str[i].खोलोed = 1;
	पूर्ण
	mutex_unlock(&chip->खोलो_mutex);

	bufsize = snd_pcm_lib_buffer_bytes(substream);
	period_bytes = snd_pcm_lib_period_bytes(substream);
	क्रमmat_verb = lola_get_क्रमmat_verb(substream);

	str->bufsize = bufsize;
	str->period_bytes = period_bytes;
	str->क्रमmat_verb = क्रमmat_verb;

	err = lola_setup_periods(chip, pcm, substream, str);
	अगर (err < 0)
		वापस err;

	err = lola_set_sample_rate(chip, runसमय->rate);
	अगर (err < 0)
		वापस err;
	chip->sample_rate = runसमय->rate;	/* sample rate माला_लो locked */

	err = lola_set_stream_config(chip, str, runसमय->channels);
	अगर (err < 0)
		वापस err;

	err = lola_setup_controller(chip, pcm, str);
	अगर (err < 0) अणु
		lola_stream_reset(chip, str);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lola_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा lola *chip = snd_pcm_substream_chip(substream);
	काष्ठा lola_stream *str;
	काष्ठा snd_pcm_substream *s;
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक tstamp;
	bool sync_streams;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		start = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		start = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * sample correct synchronization is only needed starting several
	 * streams. On stop or अगर only one stream करो as quick as possible
	 */
	sync_streams = (start && snd_pcm_stream_linked(substream));
	tstamp = lola_get_tstamp(chip, !sync_streams);
	spin_lock(&chip->reg_lock);
	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (s->pcm->card != substream->pcm->card)
			जारी;
		str = lola_get_stream(s);
		अगर (start)
			lola_stream_start(chip, str, tstamp);
		अन्यथा
			lola_stream_stop(chip, str, tstamp);
		str->running = start;
		str->छोड़ोd = !start;
		snd_pcm_trigger_करोne(s, substream);
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t lola_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा lola *chip = snd_pcm_substream_chip(substream);
	काष्ठा lola_stream *str = lola_get_stream(substream);
	अचिन्हित पूर्णांक pos = lola_dsd_पढ़ो(chip, str->dsd, LPIB);

	अगर (pos >= str->bufsize)
		pos = 0;
	वापस bytes_to_frames(substream->runसमय, pos);
पूर्ण

व्योम lola_pcm_update(काष्ठा lola *chip, काष्ठा lola_pcm *pcm, अचिन्हित पूर्णांक bits)
अणु
	पूर्णांक i;

	क्रम (i = 0; bits && i < pcm->num_streams; i++) अणु
		अगर (bits & (1 << i)) अणु
			काष्ठा lola_stream *str = &pcm->streams[i];
			अगर (str->substream && str->running)
				snd_pcm_period_elapsed(str->substream);
			bits &= ~(1 << i);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops lola_pcm_ops = अणु
	.खोलो = lola_pcm_खोलो,
	.बंद = lola_pcm_बंद,
	.hw_params = lola_pcm_hw_params,
	.hw_मुक्त = lola_pcm_hw_मुक्त,
	.prepare = lola_pcm_prepare,
	.trigger = lola_pcm_trigger,
	.poपूर्णांकer = lola_pcm_poपूर्णांकer,
पूर्ण;

पूर्णांक lola_create_pcm(काष्ठा lola *chip)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक i, err;

	क्रम (i = 0; i < 2; i++) अणु
		err = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV,
					  &chip->pci->dev,
					  PAGE_SIZE, &chip->pcm[i].bdl);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = snd_pcm_new(chip->card, "Digigram Lola", 0,
			  chip->pcm[SNDRV_PCM_STREAM_PLAYBACK].num_streams,
			  chip->pcm[SNDRV_PCM_STREAM_CAPTURE].num_streams,
			  &pcm);
	अगर (err < 0)
		वापस err;
	strscpy(pcm->name, "Digigram Lola", माप(pcm->name));
	pcm->निजी_data = chip;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (chip->pcm[i].num_streams)
			snd_pcm_set_ops(pcm, i, &lola_pcm_ops);
	पूर्ण
	/* buffer pre-allocation */
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       1024 * 64, 32 * 1024 * 1024);
	वापस 0;
पूर्ण

व्योम lola_मुक्त_pcm(काष्ठा lola *chip)
अणु
	snd_dma_मुक्त_pages(&chip->pcm[0].bdl);
	snd_dma_मुक्त_pages(&chip->pcm[1].bdl);
पूर्ण

/*
 */

अटल पूर्णांक lola_init_stream(काष्ठा lola *chip, काष्ठा lola_stream *str,
			    पूर्णांक idx, पूर्णांक nid, पूर्णांक dir)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	str->nid = nid;
	str->index = idx;
	str->dsd = idx;
	अगर (dir == PLAY)
		str->dsd += MAX_STREAM_IN_COUNT;
	err = lola_पढ़ो_param(chip, nid, LOLA_PAR_AUDIO_WIDGET_CAP, &val);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "Can't read wcaps for 0x%x\n", nid);
		वापस err;
	पूर्ण
	अगर (dir == PLAY) अणु
		/* test TYPE and bits 0..11 (no test bit9 : Digital = 0/1) */
		अगर ((val & 0x00f00dff) != 0x00000010) अणु
			dev_err(chip->card->dev,
				"Invalid wcaps 0x%x for 0x%x\n",
			       val, nid);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* test TYPE and bits 0..11 (no test bit9 : Digital = 0/1)
		 * (bug : ignore bit8: Conn list = 0/1)
		 */
		अगर ((val & 0x00f00cff) != 0x00100010) अणु
			dev_err(chip->card->dev,
				"Invalid wcaps 0x%x for 0x%x\n",
			       val, nid);
			वापस -EINVAL;
		पूर्ण
		/* test bit9:DIGITAL and bit12:SRC_PRESENT*/
		अगर ((val & 0x00001200) == 0x00001200)
			chip->input_src_caps_mask |= (1 << idx);
	पूर्ण

	err = lola_पढ़ो_param(chip, nid, LOLA_PAR_STREAM_FORMATS, &val);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "Can't read FORMATS 0x%x\n", nid);
		वापस err;
	पूर्ण
	val &= 3;
	अगर (val == 3)
		str->can_भग्न = true;
	अगर (!(val & 1)) अणु
		dev_err(chip->card->dev,
			"Invalid formats 0x%x for 0x%x", val, nid);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक lola_init_pcm(काष्ठा lola *chip, पूर्णांक dir, पूर्णांक *nidp)
अणु
	काष्ठा lola_pcm *pcm = &chip->pcm[dir];
	पूर्णांक i, nid, err;

	nid = *nidp;
	क्रम (i = 0; i < pcm->num_streams; i++, nid++) अणु
		err = lola_init_stream(chip, &pcm->streams[i], i, nid, dir);
		अगर (err < 0)
			वापस err;
	पूर्ण
	*nidp = nid;
	वापस 0;
पूर्ण
