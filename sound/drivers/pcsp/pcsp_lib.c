<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PC-Speaker driver क्रम Linux
 *
 * Copyright (C) 1993-1997  Michael Beck
 * Copyright (C) 1997-2001  David Woodhouse
 * Copyright (C) 2001-2008  Stas Sergeev
 */

#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <sound/pcm.h>
#समावेश "pcsp.h"

अटल bool nक्रमce_wa;
module_param(nक्रमce_wa, bool, 0444);
MODULE_PARM_DESC(nक्रमce_wa, "Apply NForce chipset workaround "
		"(expect bad sound)");

#घोषणा DMIX_WANTS_S16	1

/*
 * Call snd_pcm_period_elapsed in a work
 * This aव्योमs spinlock messes and दीर्घ-running irq contexts
 */
अटल व्योम pcsp_call_pcm_elapsed(काष्ठा work_काष्ठा *work)
अणु
	अगर (atomic_पढ़ो(&pcsp_chip.समयr_active)) अणु
		काष्ठा snd_pcm_substream *substream;
		substream = pcsp_chip.playback_substream;
		अगर (substream)
			snd_pcm_period_elapsed(substream);
	पूर्ण
पूर्ण

अटल DECLARE_WORK(pcsp_pcm_work, pcsp_call_pcm_elapsed);

/* ग_लिखो the port and वापसs the next expire समय in ns;
 * called at the trigger-start and in hrसमयr callback
 */
अटल u64 pcsp_समयr_update(काष्ठा snd_pcsp *chip)
अणु
	अचिन्हित अक्षर समयr_cnt, val;
	u64 ns;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित दीर्घ flags;

	अगर (chip->thalf) अणु
		outb(chip->val61, 0x61);
		chip->thalf = 0;
		वापस chip->ns_rem;
	पूर्ण

	substream = chip->playback_substream;
	अगर (!substream)
		वापस 0;

	runसमय = substream->runसमय;
	/* assume it is mono! */
	val = runसमय->dma_area[chip->playback_ptr + chip->fmt_size - 1];
	अगर (chip->is_चिन्हित)
		val ^= 0x80;
	समयr_cnt = val * CUR_DIV() / 256;

	अगर (समयr_cnt && chip->enable) अणु
		raw_spin_lock_irqsave(&i8253_lock, flags);
		अगर (!nक्रमce_wa) अणु
			outb_p(chip->val61, 0x61);
			outb_p(समयr_cnt, 0x42);
			outb(chip->val61 ^ 1, 0x61);
		पूर्ण अन्यथा अणु
			outb(chip->val61 ^ 2, 0x61);
			chip->thalf = 1;
		पूर्ण
		raw_spin_unlock_irqrestore(&i8253_lock, flags);
	पूर्ण

	chip->ns_rem = PCSP_PERIOD_NS();
	ns = (chip->thalf ? PCSP_CALC_NS(समयr_cnt) : chip->ns_rem);
	chip->ns_rem -= ns;
	वापस ns;
पूर्ण

अटल व्योम pcsp_poपूर्णांकer_update(काष्ठा snd_pcsp *chip)
अणु
	काष्ठा snd_pcm_substream *substream;
	माप_प्रकार period_bytes, buffer_bytes;
	पूर्णांक periods_elapsed;
	अचिन्हित दीर्घ flags;

	/* update the playback position */
	substream = chip->playback_substream;
	अगर (!substream)
		वापस;

	period_bytes = snd_pcm_lib_period_bytes(substream);
	buffer_bytes = snd_pcm_lib_buffer_bytes(substream);

	spin_lock_irqsave(&chip->substream_lock, flags);
	chip->playback_ptr += PCSP_INDEX_INC() * chip->fmt_size;
	periods_elapsed = chip->playback_ptr - chip->period_ptr;
	अगर (periods_elapsed < 0) अणु
#अगर PCSP_DEBUG
		prपूर्णांकk(KERN_INFO "PCSP: buffer_bytes mod period_bytes != 0 ? "
			"(%zi %zi %zi)\n",
			chip->playback_ptr, period_bytes, buffer_bytes);
#पूर्ण_अगर
		periods_elapsed += buffer_bytes;
	पूर्ण
	periods_elapsed /= period_bytes;
	/* wrap the poपूर्णांकer _beक्रमe_ calling snd_pcm_period_elapsed(),
	 * or ALSA will BUG on us. */
	chip->playback_ptr %= buffer_bytes;

	अगर (periods_elapsed) अणु
		chip->period_ptr += periods_elapsed * period_bytes;
		chip->period_ptr %= buffer_bytes;
		queue_work(प्रणाली_highpri_wq, &pcsp_pcm_work);
	पूर्ण
	spin_unlock_irqrestore(&chip->substream_lock, flags);
पूर्ण

क्रमागत hrसमयr_restart pcsp_करो_समयr(काष्ठा hrसमयr *handle)
अणु
	काष्ठा snd_pcsp *chip = container_of(handle, काष्ठा snd_pcsp, समयr);
	पूर्णांक poपूर्णांकer_update;
	u64 ns;

	अगर (!atomic_पढ़ो(&chip->समयr_active) || !chip->playback_substream)
		वापस HRTIMER_NORESTART;

	poपूर्णांकer_update = !chip->thalf;
	ns = pcsp_समयr_update(chip);
	अगर (!ns) अणु
		prपूर्णांकk(KERN_WARNING "PCSP: unexpected stop\n");
		वापस HRTIMER_NORESTART;
	पूर्ण

	अगर (poपूर्णांकer_update)
		pcsp_poपूर्णांकer_update(chip);

	hrसमयr_क्रमward(handle, hrसमयr_get_expires(handle), ns_to_kसमय(ns));

	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक pcsp_start_playing(काष्ठा snd_pcsp *chip)
अणु
#अगर PCSP_DEBUG
	prपूर्णांकk(KERN_INFO "PCSP: start_playing called\n");
#पूर्ण_अगर
	अगर (atomic_पढ़ो(&chip->समयr_active)) अणु
		prपूर्णांकk(KERN_ERR "PCSP: Timer already active\n");
		वापस -EIO;
	पूर्ण

	raw_spin_lock(&i8253_lock);
	chip->val61 = inb(0x61) | 0x03;
	outb_p(0x92, 0x43);	/* binary, mode 1, LSB only, ch 2 */
	raw_spin_unlock(&i8253_lock);
	atomic_set(&chip->समयr_active, 1);
	chip->thalf = 0;

	hrसमयr_start(&pcsp_chip.समयr, 0, HRTIMER_MODE_REL);
	वापस 0;
पूर्ण

अटल व्योम pcsp_stop_playing(काष्ठा snd_pcsp *chip)
अणु
#अगर PCSP_DEBUG
	prपूर्णांकk(KERN_INFO "PCSP: stop_playing called\n");
#पूर्ण_अगर
	अगर (!atomic_पढ़ो(&chip->समयr_active))
		वापस;

	atomic_set(&chip->समयr_active, 0);
	raw_spin_lock(&i8253_lock);
	/* restore the समयr */
	outb_p(0xb6, 0x43);	/* binary, mode 3, LSB/MSB, ch 2 */
	outb(chip->val61 & 0xFC, 0x61);
	raw_spin_unlock(&i8253_lock);
पूर्ण

/*
 * Force to stop and sync the stream
 */
व्योम pcsp_sync_stop(काष्ठा snd_pcsp *chip)
अणु
	local_irq_disable();
	pcsp_stop_playing(chip);
	local_irq_enable();
	hrसमयr_cancel(&chip->समयr);
	cancel_work_sync(&pcsp_pcm_work);
पूर्ण

अटल पूर्णांक snd_pcsp_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcsp *chip = snd_pcm_substream_chip(substream);
#अगर PCSP_DEBUG
	prपूर्णांकk(KERN_INFO "PCSP: close called\n");
#पूर्ण_अगर
	pcsp_sync_stop(chip);
	chip->playback_substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcsp_playback_hw_params(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_pcsp *chip = snd_pcm_substream_chip(substream);
	pcsp_sync_stop(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcsp_playback_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcsp *chip = snd_pcm_substream_chip(substream);
#अगर PCSP_DEBUG
	prपूर्णांकk(KERN_INFO "PCSP: hw_free called\n");
#पूर्ण_अगर
	pcsp_sync_stop(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcsp_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcsp *chip = snd_pcm_substream_chip(substream);
	pcsp_sync_stop(chip);
	chip->playback_ptr = 0;
	chip->period_ptr = 0;
	chip->fmt_size =
		snd_pcm_क्रमmat_physical_width(substream->runसमय->क्रमmat) >> 3;
	chip->is_चिन्हित = snd_pcm_क्रमmat_चिन्हित(substream->runसमय->क्रमmat);
#अगर PCSP_DEBUG
	prपूर्णांकk(KERN_INFO "PCSP: prepare called, "
			"size=%zi psize=%zi f=%zi f1=%i fsize=%i\n",
			snd_pcm_lib_buffer_bytes(substream),
			snd_pcm_lib_period_bytes(substream),
			snd_pcm_lib_buffer_bytes(substream) /
			snd_pcm_lib_period_bytes(substream),
			substream->runसमय->periods,
			chip->fmt_size);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcsp_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_pcsp *chip = snd_pcm_substream_chip(substream);
#अगर PCSP_DEBUG
	prपूर्णांकk(KERN_INFO "PCSP: trigger called\n");
#पूर्ण_अगर
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		वापस pcsp_start_playing(chip);
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		pcsp_stop_playing(chip);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_pcsp_playback_poपूर्णांकer(काष्ठा snd_pcm_substream
						   *substream)
अणु
	काष्ठा snd_pcsp *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक pos;
	spin_lock(&chip->substream_lock);
	pos = chip->playback_ptr;
	spin_unlock(&chip->substream_lock);
	वापस bytes_to_frames(substream->runसमय, pos);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_pcsp_playback = अणु
	.info = (SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_HALF_DUPLEX |
		 SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats = (SNDRV_PCM_FMTBIT_U8
#अगर DMIX_WANTS_S16
		    | SNDRV_PCM_FMTBIT_S16_LE
#पूर्ण_अगर
	    ),
	.rates = SNDRV_PCM_RATE_KNOT,
	.rate_min = PCSP_DEFAULT_SRATE,
	.rate_max = PCSP_DEFAULT_SRATE,
	.channels_min = 1,
	.channels_max = 1,
	.buffer_bytes_max = PCSP_BUFFER_SIZE,
	.period_bytes_min = 64,
	.period_bytes_max = PCSP_MAX_PERIOD_SIZE,
	.periods_min = 2,
	.periods_max = PCSP_MAX_PERIODS,
	.fअगरo_size = 0,
पूर्ण;

अटल पूर्णांक snd_pcsp_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcsp *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
#अगर PCSP_DEBUG
	prपूर्णांकk(KERN_INFO "PCSP: open called\n");
#पूर्ण_अगर
	अगर (atomic_पढ़ो(&chip->समयr_active)) अणु
		prपूर्णांकk(KERN_ERR "PCSP: still active!!\n");
		वापस -EBUSY;
	पूर्ण
	runसमय->hw = snd_pcsp_playback;
	chip->playback_substream = substream;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_pcsp_playback_ops = अणु
	.खोलो = snd_pcsp_playback_खोलो,
	.बंद = snd_pcsp_playback_बंद,
	.hw_params = snd_pcsp_playback_hw_params,
	.hw_मुक्त = snd_pcsp_playback_hw_मुक्त,
	.prepare = snd_pcsp_playback_prepare,
	.trigger = snd_pcsp_trigger,
	.poपूर्णांकer = snd_pcsp_playback_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_pcsp_new_pcm(काष्ठा snd_pcsp *chip)
अणु
	पूर्णांक err;

	err = snd_pcm_new(chip->card, "pcspeaker", 0, 1, 0, &chip->pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(chip->pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_pcsp_playback_ops);

	chip->pcm->निजी_data = chip;
	chip->pcm->info_flags = SNDRV_PCM_INFO_HALF_DUPLEX;
	म_नकल(chip->pcm->name, "pcsp");

	snd_pcm_set_managed_buffer_all(chip->pcm,
				       SNDRV_DMA_TYPE_CONTINUOUS,
				       शून्य,
				       PCSP_BUFFER_SIZE,
				       PCSP_BUFFER_SIZE);

	वापस 0;
पूर्ण
