<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pcm emulation on emu8000 wavetable
 *
 *  Copyright (C) 2002 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "emu8000_local.h"

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>

/*
 * define the following अगर you want to use this pcm with non-पूर्णांकerleaved mode
 */
/* #घोषणा USE_NONINTERLEAVE */

/* NOTE: क्रम using the non-पूर्णांकerleaved mode with alsa-lib, you have to set
 * mmap_emulation flag to 1 in your .asoundrc, such like
 *
 *	pcm.emu8k अणु
 *		type plug
 *		slave.pcm अणु
 *			type hw
 *			card 0
 *			device 1
 *			mmap_emulation 1
 *		पूर्ण
 *	पूर्ण
 *
 * besides, क्रम the समय being, the non-पूर्णांकerleaved mode करोesn't work well on
 * alsa-lib...
 */


काष्ठा snd_emu8k_pcm अणु
	काष्ठा snd_emu8000 *emu;
	काष्ठा snd_pcm_substream *substream;

	अचिन्हित पूर्णांक allocated_bytes;
	काष्ठा snd_util_memblk *block;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक buf_size;
	अचिन्हित पूर्णांक period_size;
	अचिन्हित पूर्णांक loop_start[2];
	अचिन्हित पूर्णांक pitch;
	पूर्णांक panning[2];
	पूर्णांक last_ptr;
	पूर्णांक period_pos;
	पूर्णांक voices;
	अचिन्हित पूर्णांक dram_खोलोed: 1;
	अचिन्हित पूर्णांक running: 1;
	अचिन्हित पूर्णांक समयr_running: 1;
	काष्ठा समयr_list समयr;
	spinlock_t समयr_lock;
पूर्ण;

#घोषणा LOOP_BLANK_SIZE		8


/*
 * खोलो up channels क्रम the simultaneous data transfer and playback
 */
अटल पूर्णांक
emu8k_खोलो_dram_क्रम_pcm(काष्ठा snd_emu8000 *emu, पूर्णांक channels)
अणु
	पूर्णांक i;

	/* reserve up to 2 voices क्रम playback */
	snd_emux_lock_voice(emu->emu, 0);
	अगर (channels > 1)
		snd_emux_lock_voice(emu->emu, 1);

	/* reserve 28 voices क्रम loading */
	क्रम (i = channels + 1; i < EMU8000_DRAM_VOICES; i++) अणु
		अचिन्हित पूर्णांक mode = EMU8000_RAM_WRITE;
		snd_emux_lock_voice(emu->emu, i);
#अगर_अघोषित USE_NONINTERLEAVE
		अगर (channels > 1 && (i & 1) != 0)
			mode |= EMU8000_RAM_RIGHT;
#पूर्ण_अगर
		snd_emu8000_dma_chan(emu, i, mode);
	पूर्ण

	/* assign voice 31 and 32 to ROM */
	EMU8000_VTFT_WRITE(emu, 30, 0);
	EMU8000_PSST_WRITE(emu, 30, 0x1d8);
	EMU8000_CSL_WRITE(emu, 30, 0x1e0);
	EMU8000_CCCA_WRITE(emu, 30, 0x1d8);
	EMU8000_VTFT_WRITE(emu, 31, 0);
	EMU8000_PSST_WRITE(emu, 31, 0x1d8);
	EMU8000_CSL_WRITE(emu, 31, 0x1e0);
	EMU8000_CCCA_WRITE(emu, 31, 0x1d8);

	वापस 0;
पूर्ण

/*
 */
अटल व्योम
snd_emu8000_ग_लिखो_रुको(काष्ठा snd_emu8000 *emu, पूर्णांक can_schedule)
अणु
	जबतक ((EMU8000_SMALW_READ(emu) & 0x80000000) != 0) अणु
		अगर (can_schedule) अणु
			schedule_समयout_पूर्णांकerruptible(1);
			अगर (संकेत_pending(current))
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * बंद all channels
 */
अटल व्योम
emu8k_बंद_dram(काष्ठा snd_emu8000 *emu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		snd_emux_unlock_voice(emu->emu, i);
	क्रम (; i < EMU8000_DRAM_VOICES; i++) अणु
		snd_emu8000_dma_chan(emu, i, EMU8000_RAM_CLOSE);
		snd_emux_unlock_voice(emu->emu, i);
	पूर्ण
पूर्ण

/*
 * convert Hz to AWE32 rate offset (see emux/soundfont.c)
 */

#घोषणा OFFSET_SAMPLERATE	1011119		/* base = 44100 */
#घोषणा SAMPLERATE_RATIO	4096

अटल पूर्णांक calc_rate_offset(पूर्णांक hz)
अणु
	वापस snd_sf_linear_to_log(hz, OFFSET_SAMPLERATE, SAMPLERATE_RATIO);
पूर्ण


/*
 */

अटल स्थिर काष्ठा snd_pcm_hardware emu8k_pcm_hw = अणु
#अगर_घोषित USE_NONINTERLEAVE
	.info =			SNDRV_PCM_INFO_NONINTERLEAVED,
#अन्यथा
	.info =			SNDRV_PCM_INFO_INTERLEAVED,
#पूर्ण_अगर
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	1024,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		1024,
	.fअगरo_size =		0,

पूर्ण;

/*
 * get the current position at the given channel from CCCA रेजिस्टर
 */
अटल अंतरभूत पूर्णांक emu8k_get_curpos(काष्ठा snd_emu8k_pcm *rec, पूर्णांक ch)
अणु
	पूर्णांक val = EMU8000_CCCA_READ(rec->emu, ch) & 0xfffffff;
	val -= rec->loop_start[ch] - 1;
	वापस val;
पूर्ण


/*
 * समयr पूर्णांकerrupt handler
 * check the current position and update the period अगर necessary.
 */
अटल व्योम emu8k_pcm_समयr_func(काष्ठा समयr_list *t)
अणु
	काष्ठा snd_emu8k_pcm *rec = from_समयr(rec, t, समयr);
	पूर्णांक ptr, delta;

	spin_lock(&rec->समयr_lock);
	/* update the current poपूर्णांकer */
	ptr = emu8k_get_curpos(rec, 0);
	अगर (ptr < rec->last_ptr)
		delta = ptr + rec->buf_size - rec->last_ptr;
	अन्यथा
		delta = ptr - rec->last_ptr;
	rec->period_pos += delta;
	rec->last_ptr = ptr;

	/* reprogram समयr */
	mod_समयr(&rec->समयr, jअगरfies + 1);

	/* update period */
	अगर (rec->period_pos >= (पूर्णांक)rec->period_size) अणु
		rec->period_pos %= rec->period_size;
		spin_unlock(&rec->समयr_lock);
		snd_pcm_period_elapsed(rec->substream);
		वापस;
	पूर्ण
	spin_unlock(&rec->समयr_lock);
पूर्ण


/*
 * खोलो pcm
 * creating an instance here
 */
अटल पूर्णांक emu8k_pcm_खोलो(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_emu8000 *emu = snd_pcm_substream_chip(subs);
	काष्ठा snd_emu8k_pcm *rec;
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;

	rec = kzalloc(माप(*rec), GFP_KERNEL);
	अगर (! rec)
		वापस -ENOMEM;

	rec->emu = emu;
	rec->substream = subs;
	runसमय->निजी_data = rec;

	spin_lock_init(&rec->समयr_lock);
	समयr_setup(&rec->समयr, emu8k_pcm_समयr_func, 0);

	runसमय->hw = emu8k_pcm_hw;
	runसमय->hw.buffer_bytes_max = emu->mem_size - LOOP_BLANK_SIZE * 3;
	runसमय->hw.period_bytes_max = runसमय->hw.buffer_bytes_max / 2;

	/* use समयr to update periods.. (specअगरied in msec) */
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_PERIOD_TIME,
				     (1000000 + HZ - 1) / HZ, अच_पूर्णांक_उच्च);

	वापस 0;
पूर्ण

अटल पूर्णांक emu8k_pcm_बंद(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_emu8k_pcm *rec = subs->runसमय->निजी_data;
	kमुक्त(rec);
	subs->runसमय->निजी_data = शून्य;
	वापस 0;
पूर्ण

/*
 * calculate pitch target
 */
अटल पूर्णांक calc_pitch_target(पूर्णांक pitch)
अणु
	पूर्णांक ptarget = 1 << (pitch >> 12);
	अगर (pitch & 0x800) ptarget += (ptarget * 0x102e) / 0x2710;
	अगर (pitch & 0x400) ptarget += (ptarget * 0x764) / 0x2710;
	अगर (pitch & 0x200) ptarget += (ptarget * 0x389) / 0x2710;
	ptarget += (ptarget >> 1);
	अगर (ptarget > 0xffff) ptarget = 0xffff;
	वापस ptarget;
पूर्ण

/*
 * set up the voice
 */
अटल व्योम setup_voice(काष्ठा snd_emu8k_pcm *rec, पूर्णांक ch)
अणु
	काष्ठा snd_emu8000 *hw = rec->emu;
	अचिन्हित पूर्णांक temp;

	/* channel to be silent and idle */
	EMU8000_DCYSUSV_WRITE(hw, ch, 0x0080);
	EMU8000_VTFT_WRITE(hw, ch, 0x0000FFFF);
	EMU8000_CVCF_WRITE(hw, ch, 0x0000FFFF);
	EMU8000_PTRX_WRITE(hw, ch, 0);
	EMU8000_CPF_WRITE(hw, ch, 0);

	/* pitch offset */
	EMU8000_IP_WRITE(hw, ch, rec->pitch);
	/* set envelope parameters */
	EMU8000_ENVVAL_WRITE(hw, ch, 0x8000);
	EMU8000_ATKHLD_WRITE(hw, ch, 0x7f7f);
	EMU8000_DCYSUS_WRITE(hw, ch, 0x7f7f);
	EMU8000_ENVVOL_WRITE(hw, ch, 0x8000);
	EMU8000_ATKHLDV_WRITE(hw, ch, 0x7f7f);
	/* decay/sustain parameter क्रम volume envelope is used
	   क्रम triggerg the voice */
	/* modulation envelope heights */
	EMU8000_PEFE_WRITE(hw, ch, 0x0);
	/* lfo1/2 delay */
	EMU8000_LFO1VAL_WRITE(hw, ch, 0x8000);
	EMU8000_LFO2VAL_WRITE(hw, ch, 0x8000);
	/* lfo1 pitch & cutoff shअगरt */
	EMU8000_FMMOD_WRITE(hw, ch, 0);
	/* lfo1 volume & freq */
	EMU8000_TREMFRQ_WRITE(hw, ch, 0);
	/* lfo2 pitch & freq */
	EMU8000_FM2FRQ2_WRITE(hw, ch, 0);
	/* pan & loop start */
	temp = rec->panning[ch];
	temp = (temp <<24) | ((अचिन्हित पूर्णांक)rec->loop_start[ch] - 1);
	EMU8000_PSST_WRITE(hw, ch, temp);
	/* chorus & loop end (chorus 8bit, MSB) */
	temp = 0; // chorus
	temp = (temp << 24) | ((अचिन्हित पूर्णांक)rec->loop_start[ch] + rec->buf_size - 1);
	EMU8000_CSL_WRITE(hw, ch, temp);
	/* Q & current address (Q 4bit value, MSB) */
	temp = 0; // filterQ
	temp = (temp << 28) | ((अचिन्हित पूर्णांक)rec->loop_start[ch] - 1);
	EMU8000_CCCA_WRITE(hw, ch, temp);
	/* clear unknown रेजिस्टरs */
	EMU8000_00A0_WRITE(hw, ch, 0);
	EMU8000_0080_WRITE(hw, ch, 0);
पूर्ण

/*
 * trigger the voice
 */
अटल व्योम start_voice(काष्ठा snd_emu8k_pcm *rec, पूर्णांक ch)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu8000 *hw = rec->emu;
	अचिन्हित पूर्णांक temp, aux;
	पूर्णांक pt = calc_pitch_target(rec->pitch);

	/* cutoff and volume */
	EMU8000_IFATN_WRITE(hw, ch, 0xff00);
	EMU8000_VTFT_WRITE(hw, ch, 0xffff);
	EMU8000_CVCF_WRITE(hw, ch, 0xffff);
	/* trigger envelope */
	EMU8000_DCYSUSV_WRITE(hw, ch, 0x7f7f);
	/* set reverb and pitch target */
	temp = 0; // reverb
	अगर (rec->panning[ch] == 0)
		aux = 0xff;
	अन्यथा
		aux = (-rec->panning[ch]) & 0xff;
	temp = (temp << 8) | (pt << 16) | aux;
	EMU8000_PTRX_WRITE(hw, ch, temp);
	EMU8000_CPF_WRITE(hw, ch, pt << 16);

	/* start समयr */
	spin_lock_irqsave(&rec->समयr_lock, flags);
	अगर (! rec->समयr_running) अणु
		mod_समयr(&rec->समयr, jअगरfies + 1);
		rec->समयr_running = 1;
	पूर्ण
	spin_unlock_irqrestore(&rec->समयr_lock, flags);
पूर्ण

/*
 * stop the voice immediately
 */
अटल व्योम stop_voice(काष्ठा snd_emu8k_pcm *rec, पूर्णांक ch)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu8000 *hw = rec->emu;

	EMU8000_DCYSUSV_WRITE(hw, ch, 0x807F);

	/* stop समयr */
	spin_lock_irqsave(&rec->समयr_lock, flags);
	अगर (rec->समयr_running) अणु
		del_समयr(&rec->समयr);
		rec->समयr_running = 0;
	पूर्ण
	spin_unlock_irqrestore(&rec->समयr_lock, flags);
पूर्ण

अटल पूर्णांक emu8k_pcm_trigger(काष्ठा snd_pcm_substream *subs, पूर्णांक cmd)
अणु
	काष्ठा snd_emu8k_pcm *rec = subs->runसमय->निजी_data;
	पूर्णांक ch;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		क्रम (ch = 0; ch < rec->voices; ch++)
			start_voice(rec, ch);
		rec->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		rec->running = 0;
		क्रम (ch = 0; ch < rec->voices; ch++)
			stop_voice(rec, ch);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * copy / silence ops
 */

/*
 * this macro should be inserted in the copy/silence loops
 * to reduce the latency.  without this, the प्रणाली will hang up
 * during the whole loop.
 */
#घोषणा CHECK_SCHEDULER() \
करो अणु \
	cond_resched();\
	अगर (संकेत_pending(current))\
		वापस -EAGAIN;\
पूर्ण जबतक (0)

क्रमागत अणु
	COPY_USER, COPY_KERNEL, FILL_SILENCE,
पूर्ण;

#घोषणा GET_VAL(sval, buf, mode)					\
	करो अणु								\
		चयन (mode) अणु						\
		हाल FILL_SILENCE:					\
			sval = 0;					\
			अवरोध;						\
		हाल COPY_KERNEL:					\
			sval = *buf++;					\
			अवरोध;						\
		शेष:						\
			अगर (get_user(sval, (अचिन्हित लघु __user *)buf)) \
				वापस -EFAULT;				\
			buf++;						\
			अवरोध;						\
		पूर्ण							\
	पूर्ण जबतक (0)

#अगर_घोषित USE_NONINTERLEAVE

#घोषणा LOOP_WRITE(rec, offset, _buf, count, mode)		\
	करो अणु							\
		काष्ठा snd_emu8000 *emu = (rec)->emu;		\
		अचिन्हित लघु *buf = (__क्रमce अचिन्हित लघु *)(_buf); \
		snd_emu8000_ग_लिखो_रुको(emu, 1);			\
		EMU8000_SMALW_WRITE(emu, offset);		\
		जबतक (count > 0) अणु				\
			अचिन्हित लघु sval;			\
			CHECK_SCHEDULER();			\
			GET_VAL(sval, buf, mode);		\
			EMU8000_SMLD_WRITE(emu, sval);		\
			count--;				\
		पूर्ण						\
	पूर्ण जबतक (0)

/* copy one channel block */
अटल पूर्णांक emu8k_pcm_copy(काष्ठा snd_pcm_substream *subs,
			  पूर्णांक voice, अचिन्हित दीर्घ pos,
			  व्योम __user *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_emu8k_pcm *rec = subs->runसमय->निजी_data;

	/* convert to word unit */
	pos = (pos << 1) + rec->loop_start[voice];
	count <<= 1;
	LOOP_WRITE(rec, pos, src, count, COPY_USER);
	वापस 0;
पूर्ण

अटल पूर्णांक emu8k_pcm_copy_kernel(काष्ठा snd_pcm_substream *subs,
				 पूर्णांक voice, अचिन्हित दीर्घ pos,
				 व्योम *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_emu8k_pcm *rec = subs->runसमय->निजी_data;

	/* convert to word unit */
	pos = (pos << 1) + rec->loop_start[voice];
	count <<= 1;
	LOOP_WRITE(rec, pos, src, count, COPY_KERNEL);
	वापस 0;
पूर्ण

/* make a channel block silence */
अटल पूर्णांक emu8k_pcm_silence(काष्ठा snd_pcm_substream *subs,
			     पूर्णांक voice, अचिन्हित दीर्घ pos, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_emu8k_pcm *rec = subs->runसमय->निजी_data;

	/* convert to word unit */
	pos = (pos << 1) + rec->loop_start[voice];
	count <<= 1;
	LOOP_WRITE(rec, pos, शून्य, count, FILL_SILENCE);
	वापस 0;
पूर्ण

#अन्यथा /* पूर्णांकerleave */

#घोषणा LOOP_WRITE(rec, pos, _buf, count, mode)				\
	करो अणु								\
		काष्ठा snd_emu8000 *emu = rec->emu;			\
		अचिन्हित लघु *buf = (__क्रमce अचिन्हित लघु *)(_buf);	\
		snd_emu8000_ग_लिखो_रुको(emu, 1);				\
		EMU8000_SMALW_WRITE(emu, pos + rec->loop_start[0]);	\
		अगर (rec->voices > 1)					\
			EMU8000_SMARW_WRITE(emu, pos + rec->loop_start[1]); \
		जबतक (count > 0) अणु					\
			अचिन्हित लघु sval;				\
			CHECK_SCHEDULER();				\
			GET_VAL(sval, buf, mode);			\
			EMU8000_SMLD_WRITE(emu, sval);			\
			अगर (rec->voices > 1) अणु				\
				CHECK_SCHEDULER();			\
				GET_VAL(sval, buf, mode);		\
				EMU8000_SMRD_WRITE(emu, sval);		\
			पूर्ण						\
			count--;					\
		पूर्ण							\
	पूर्ण जबतक (0)


/*
 * copy the पूर्णांकerleaved data can be करोne easily by using
 * DMA "left" and "right" channels on emu8k engine.
 */
अटल पूर्णांक emu8k_pcm_copy(काष्ठा snd_pcm_substream *subs,
			  पूर्णांक voice, अचिन्हित दीर्घ pos,
			  व्योम __user *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_emu8k_pcm *rec = subs->runसमय->निजी_data;

	/* convert to frames */
	pos = bytes_to_frames(subs->runसमय, pos);
	count = bytes_to_frames(subs->runसमय, count);
	LOOP_WRITE(rec, pos, src, count, COPY_USER);
	वापस 0;
पूर्ण

अटल पूर्णांक emu8k_pcm_copy_kernel(काष्ठा snd_pcm_substream *subs,
				 पूर्णांक voice, अचिन्हित दीर्घ pos,
				 व्योम *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_emu8k_pcm *rec = subs->runसमय->निजी_data;

	/* convert to frames */
	pos = bytes_to_frames(subs->runसमय, pos);
	count = bytes_to_frames(subs->runसमय, count);
	LOOP_WRITE(rec, pos, src, count, COPY_KERNEL);
	वापस 0;
पूर्ण

अटल पूर्णांक emu8k_pcm_silence(काष्ठा snd_pcm_substream *subs,
			     पूर्णांक voice, अचिन्हित दीर्घ pos, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_emu8k_pcm *rec = subs->runसमय->निजी_data;

	/* convert to frames */
	pos = bytes_to_frames(subs->runसमय, pos);
	count = bytes_to_frames(subs->runसमय, count);
	LOOP_WRITE(rec, pos, शून्य, count, FILL_SILENCE);
	वापस 0;
पूर्ण
#पूर्ण_अगर


/*
 * allocate a memory block
 */
अटल पूर्णांक emu8k_pcm_hw_params(काष्ठा snd_pcm_substream *subs,
			       काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_emu8k_pcm *rec = subs->runसमय->निजी_data;

	अगर (rec->block) अणु
		/* पुनः_स्मृतिation - release the old block */
		snd_util_mem_मुक्त(rec->emu->memhdr, rec->block);
		rec->block = शून्य;
	पूर्ण

	rec->allocated_bytes = params_buffer_bytes(hw_params) + LOOP_BLANK_SIZE * 4;
	rec->block = snd_util_mem_alloc(rec->emu->memhdr, rec->allocated_bytes);
	अगर (! rec->block)
		वापस -ENOMEM;
	rec->offset = EMU8000_DRAM_OFFSET + (rec->block->offset >> 1); /* in word */
	/* at least dma_bytes must be set क्रम non-पूर्णांकerleaved mode */
	subs->dma_buffer.bytes = params_buffer_bytes(hw_params);

	वापस 0;
पूर्ण

/*
 * मुक्त the memory block
 */
अटल पूर्णांक emu8k_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_emu8k_pcm *rec = subs->runसमय->निजी_data;

	अगर (rec->block) अणु
		पूर्णांक ch;
		क्रम (ch = 0; ch < rec->voices; ch++)
			stop_voice(rec, ch); // to be sure
		अगर (rec->dram_खोलोed)
			emu8k_बंद_dram(rec->emu);
		snd_util_mem_मुक्त(rec->emu->memhdr, rec->block);
		rec->block = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

/*
 */
अटल पूर्णांक emu8k_pcm_prepare(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_emu8k_pcm *rec = subs->runसमय->निजी_data;

	rec->pitch = 0xe000 + calc_rate_offset(subs->runसमय->rate);
	rec->last_ptr = 0;
	rec->period_pos = 0;

	rec->buf_size = subs->runसमय->buffer_size;
	rec->period_size = subs->runसमय->period_size;
	rec->voices = subs->runसमय->channels;
	rec->loop_start[0] = rec->offset + LOOP_BLANK_SIZE;
	अगर (rec->voices > 1)
		rec->loop_start[1] = rec->loop_start[0] + rec->buf_size + LOOP_BLANK_SIZE;
	अगर (rec->voices > 1) अणु
		rec->panning[0] = 0xff;
		rec->panning[1] = 0x00;
	पूर्ण अन्यथा
		rec->panning[0] = 0x80;

	अगर (! rec->dram_खोलोed) अणु
		पूर्णांक err, i, ch;

		snd_emux_terminate_all(rec->emu->emu);
		अगर ((err = emu8k_खोलो_dram_क्रम_pcm(rec->emu, rec->voices)) != 0)
			वापस err;
		rec->dram_खोलोed = 1;

		/* clear loop blanks */
		snd_emu8000_ग_लिखो_रुको(rec->emu, 0);
		EMU8000_SMALW_WRITE(rec->emu, rec->offset);
		क्रम (i = 0; i < LOOP_BLANK_SIZE; i++)
			EMU8000_SMLD_WRITE(rec->emu, 0);
		क्रम (ch = 0; ch < rec->voices; ch++) अणु
			EMU8000_SMALW_WRITE(rec->emu, rec->loop_start[ch] + rec->buf_size);
			क्रम (i = 0; i < LOOP_BLANK_SIZE; i++)
				EMU8000_SMLD_WRITE(rec->emu, 0);
		पूर्ण
	पूर्ण

	setup_voice(rec, 0);
	अगर (rec->voices > 1)
		setup_voice(rec, 1);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t emu8k_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_emu8k_pcm *rec = subs->runसमय->निजी_data;
	अगर (rec->running)
		वापस emu8k_get_curpos(rec, 0);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा snd_pcm_ops emu8k_pcm_ops = अणु
	.खोलो =		emu8k_pcm_खोलो,
	.बंद =	emu8k_pcm_बंद,
	.hw_params =	emu8k_pcm_hw_params,
	.hw_मुक्त =	emu8k_pcm_hw_मुक्त,
	.prepare =	emu8k_pcm_prepare,
	.trigger =	emu8k_pcm_trigger,
	.poपूर्णांकer =	emu8k_pcm_poपूर्णांकer,
	.copy_user =	emu8k_pcm_copy,
	.copy_kernel =	emu8k_pcm_copy_kernel,
	.fill_silence =	emu8k_pcm_silence,
पूर्ण;


अटल व्योम snd_emu8000_pcm_मुक्त(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_emu8000 *emu = pcm->निजी_data;
	emu->pcm = शून्य;
पूर्ण

पूर्णांक snd_emu8000_pcm_new(काष्ठा snd_card *card, काष्ठा snd_emu8000 *emu, पूर्णांक index)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(card, "Emu8000 PCM", index, 1, 0, &pcm)) < 0)
		वापस err;
	pcm->निजी_data = emu;
	pcm->निजी_मुक्त = snd_emu8000_pcm_मुक्त;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &emu8k_pcm_ops);
	emu->pcm = pcm;

	snd_device_रेजिस्टर(card, pcm);

	वापस 0;
पूर्ण
