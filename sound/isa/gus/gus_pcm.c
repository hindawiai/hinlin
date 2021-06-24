<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम control of GF1 chip (PCM things)
 *
 *  InterWave chips supports पूर्णांकerleaved DMA, but this feature isn't used in
 *  this code.
 *  
 *  This code emulates स्वतःinit DMA transfer क्रम playback, recording by GF1
 *  chip करोesn't support स्वतःinit DMA.
 */

#समावेश <यंत्र/dma.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/gus.h>
#समावेश <sound/pcm_params.h>
#समावेश "gus_tables.h"

/* maximum rate */

#घोषणा SNDRV_GF1_PCM_RATE		48000

#घोषणा SNDRV_GF1_PCM_PFLG_NONE		0
#घोषणा SNDRV_GF1_PCM_PFLG_ACTIVE	(1<<0)
#घोषणा SNDRV_GF1_PCM_PFLG_NEUTRAL	(2<<0)

काष्ठा gus_pcm_निजी अणु
	काष्ठा snd_gus_card * gus;
	काष्ठा snd_pcm_substream *substream;
	spinlock_t lock;
	अचिन्हित पूर्णांक voices;
	काष्ठा snd_gus_voice *pvoices[2];
	अचिन्हित पूर्णांक memory;
	अचिन्हित लघु flags;
	अचिन्हित अक्षर voice_ctrl, ramp_ctrl;
	अचिन्हित पूर्णांक bpos;
	अचिन्हित पूर्णांक blocks;
	अचिन्हित पूर्णांक block_size;
	अचिन्हित पूर्णांक dma_size;
	रुको_queue_head_t sleep;
	atomic_t dma_count;
	पूर्णांक final_volume;
पूर्ण;

अटल व्योम snd_gf1_pcm_block_change_ack(काष्ठा snd_gus_card * gus, व्योम *निजी_data)
अणु
	काष्ठा gus_pcm_निजी *pcmp = निजी_data;

	अगर (pcmp) अणु
		atomic_dec(&pcmp->dma_count);
		wake_up(&pcmp->sleep);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_gf1_pcm_block_change(काष्ठा snd_pcm_substream *substream,
				    अचिन्हित पूर्णांक offset,
				    अचिन्हित पूर्णांक addr,
				    अचिन्हित पूर्णांक count)
अणु
	काष्ठा snd_gf1_dma_block block;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा gus_pcm_निजी *pcmp = runसमय->निजी_data;

	count += offset & 31;
	offset &= ~31;
	/*
	snd_prपूर्णांकk(KERN_DEBUG "block change - offset = 0x%x, count = 0x%x\n",
		   offset, count);
	*/
	स_रखो(&block, 0, माप(block));
	block.cmd = SNDRV_GF1_DMA_IRQ;
	अगर (snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat))
		block.cmd |= SNDRV_GF1_DMA_UNSIGNED;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		block.cmd |= SNDRV_GF1_DMA_16BIT;
	block.addr = addr & ~31;
	block.buffer = runसमय->dma_area + offset;
	block.buf_addr = runसमय->dma_addr + offset;
	block.count = count;
	block.निजी_data = pcmp;
	block.ack = snd_gf1_pcm_block_change_ack;
	अगर (!snd_gf1_dma_transfer_block(pcmp->gus, &block, 0, 0))
		atomic_inc(&pcmp->dma_count);
	वापस 0;
पूर्ण

अटल व्योम snd_gf1_pcm_trigger_up(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा gus_pcm_निजी *pcmp = runसमय->निजी_data;
	काष्ठा snd_gus_card * gus = pcmp->gus;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर voice_ctrl, ramp_ctrl;
	अचिन्हित लघु rate;
	अचिन्हित पूर्णांक curr, begin, end;
	अचिन्हित लघु vol;
	अचिन्हित अक्षर pan;
	अचिन्हित पूर्णांक voice;

	spin_lock_irqsave(&pcmp->lock, flags);
	अगर (pcmp->flags & SNDRV_GF1_PCM_PFLG_ACTIVE) अणु
		spin_unlock_irqrestore(&pcmp->lock, flags);
		वापस;
	पूर्ण
	pcmp->flags |= SNDRV_GF1_PCM_PFLG_ACTIVE;
	pcmp->final_volume = 0;
	spin_unlock_irqrestore(&pcmp->lock, flags);
	rate = snd_gf1_translate_freq(gus, runसमय->rate << 4);
	/* enable WAVE IRQ */
	voice_ctrl = snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16 ? 0x24 : 0x20;
	/* enable RAMP IRQ + rollover */
	ramp_ctrl = 0x24;
	अगर (pcmp->blocks == 1) अणु
		voice_ctrl |= 0x08;	/* loop enable */
		ramp_ctrl &= ~0x04;	/* disable rollover */
	पूर्ण
	क्रम (voice = 0; voice < pcmp->voices; voice++) अणु
		begin = pcmp->memory + voice * (pcmp->dma_size / runसमय->channels);
		curr = begin + (pcmp->bpos * pcmp->block_size) / runसमय->channels;
		end = curr + (pcmp->block_size / runसमय->channels);
		end -= snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16 ? 2 : 1;
		/*
		snd_prपूर्णांकk(KERN_DEBUG "init: curr=0x%x, begin=0x%x, end=0x%x, "
			   "ctrl=0x%x, ramp=0x%x, rate=0x%x\n",
			   curr, begin, end, voice_ctrl, ramp_ctrl, rate);
		*/
		pan = runसमय->channels == 2 ? (!voice ? 1 : 14) : 8;
		vol = !voice ? gus->gf1.pcm_volume_level_left : gus->gf1.pcm_volume_level_right;
		spin_lock_irqsave(&gus->reg_lock, flags);
		snd_gf1_select_voice(gus, pcmp->pvoices[voice]->number);
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_PAN, pan);
		snd_gf1_ग_लिखो16(gus, SNDRV_GF1_VW_FREQUENCY, rate);
		snd_gf1_ग_लिखो_addr(gus, SNDRV_GF1_VA_START, begin << 4, voice_ctrl & 4);
		snd_gf1_ग_लिखो_addr(gus, SNDRV_GF1_VA_END, end << 4, voice_ctrl & 4);
		snd_gf1_ग_लिखो_addr(gus, SNDRV_GF1_VA_CURRENT, curr << 4, voice_ctrl & 4);
		snd_gf1_ग_लिखो16(gus, SNDRV_GF1_VW_VOLUME, SNDRV_GF1_MIN_VOLUME << 4);
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_RATE, 0x2f);
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_START, SNDRV_GF1_MIN_OFFSET);
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_END, vol >> 8);
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_CONTROL, ramp_ctrl);
		अगर (!gus->gf1.enh_mode) अणु
			snd_gf1_delay(gus);
			snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_CONTROL, ramp_ctrl);
		पूर्ण
		spin_unlock_irqrestore(&gus->reg_lock, flags);
	पूर्ण
	spin_lock_irqsave(&gus->reg_lock, flags);
	क्रम (voice = 0; voice < pcmp->voices; voice++) अणु
		snd_gf1_select_voice(gus, pcmp->pvoices[voice]->number);
		अगर (gus->gf1.enh_mode)
			snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_MODE, 0x00);	/* deactivate voice */
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_ADDRESS_CONTROL, voice_ctrl);
		voice_ctrl &= ~0x20;
	पूर्ण
	voice_ctrl |= 0x20;
	अगर (!gus->gf1.enh_mode) अणु
		snd_gf1_delay(gus);
		क्रम (voice = 0; voice < pcmp->voices; voice++) अणु
			snd_gf1_select_voice(gus, pcmp->pvoices[voice]->number);
			snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_ADDRESS_CONTROL, voice_ctrl);
			voice_ctrl &= ~0x20;	/* disable IRQ क्रम next voice */
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

अटल व्योम snd_gf1_pcm_पूर्णांकerrupt_wave(काष्ठा snd_gus_card * gus,
				       काष्ठा snd_gus_voice *pvoice)
अणु
	काष्ठा gus_pcm_निजी * pcmp;
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित अक्षर voice_ctrl, ramp_ctrl;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक end, step;

	अगर (!pvoice->निजी_data) अणु
		snd_prपूर्णांकd("snd_gf1_pcm: unknown wave irq?\n");
		snd_gf1_smart_stop_voice(gus, pvoice->number);
		वापस;
	पूर्ण
	pcmp = pvoice->निजी_data;
	अगर (pcmp == शून्य) अणु
		snd_prपूर्णांकd("snd_gf1_pcm: unknown wave irq?\n");
		snd_gf1_smart_stop_voice(gus, pvoice->number);
		वापस;
	पूर्ण		
	gus = pcmp->gus;
	runसमय = pcmp->substream->runसमय;

	spin_lock(&gus->reg_lock);
	snd_gf1_select_voice(gus, pvoice->number);
	voice_ctrl = snd_gf1_पढ़ो8(gus, SNDRV_GF1_VB_ADDRESS_CONTROL) & ~0x8b;
	ramp_ctrl = (snd_gf1_पढ़ो8(gus, SNDRV_GF1_VB_VOLUME_CONTROL) & ~0xa4) | 0x03;
#अगर 0
	snd_gf1_select_voice(gus, pvoice->number);
	prपूर्णांकk(KERN_DEBUG "position = 0x%x\n",
	       (snd_gf1_पढ़ो_addr(gus, SNDRV_GF1_VA_CURRENT, voice_ctrl & 4) >> 4));
	snd_gf1_select_voice(gus, pcmp->pvoices[1]->number);
	prपूर्णांकk(KERN_DEBUG "position = 0x%x\n",
	       (snd_gf1_पढ़ो_addr(gus, SNDRV_GF1_VA_CURRENT, voice_ctrl & 4) >> 4));
	snd_gf1_select_voice(gus, pvoice->number);
#पूर्ण_अगर
	pcmp->bpos++;
	pcmp->bpos %= pcmp->blocks;
	अगर (pcmp->bpos + 1 >= pcmp->blocks) अणु	/* last block? */
		voice_ctrl |= 0x08;	/* enable loop */
	पूर्ण अन्यथा अणु
		ramp_ctrl |= 0x04;	/* enable rollover */
	पूर्ण
	end = pcmp->memory + (((pcmp->bpos + 1) * pcmp->block_size) / runसमय->channels);
	end -= voice_ctrl & 4 ? 2 : 1;
	step = pcmp->dma_size / runसमय->channels;
	voice_ctrl |= 0x20;
	अगर (!pcmp->final_volume) अणु
		ramp_ctrl |= 0x20;
		ramp_ctrl &= ~0x03;
	पूर्ण
	क्रम (idx = 0; idx < pcmp->voices; idx++, end += step) अणु
		snd_gf1_select_voice(gus, pcmp->pvoices[idx]->number);
		snd_gf1_ग_लिखो_addr(gus, SNDRV_GF1_VA_END, end << 4, voice_ctrl & 4);
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_ADDRESS_CONTROL, voice_ctrl);
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_CONTROL, ramp_ctrl);
		voice_ctrl &= ~0x20;
	पूर्ण
	अगर (!gus->gf1.enh_mode) अणु
		snd_gf1_delay(gus);
		voice_ctrl |= 0x20;
		क्रम (idx = 0; idx < pcmp->voices; idx++) अणु
			snd_gf1_select_voice(gus, pcmp->pvoices[idx]->number);
			snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_ADDRESS_CONTROL, voice_ctrl);
			snd_gf1_ग_लिखो8(gus, SNDRV_GF1_VB_VOLUME_CONTROL, ramp_ctrl);
			voice_ctrl &= ~0x20;
		पूर्ण
	पूर्ण
	spin_unlock(&gus->reg_lock);

	snd_pcm_period_elapsed(pcmp->substream);
#अगर 0
	अगर ((runसमय->flags & SNDRV_PCM_FLG_MMAP) &&
	    *runसमय->state == SNDRV_PCM_STATE_RUNNING) अणु
		end = pcmp->bpos * pcmp->block_size;
		अगर (runसमय->channels > 1) अणु
			snd_gf1_pcm_block_change(pcmp->substream, end, pcmp->memory + (end / 2), pcmp->block_size / 2);
			snd_gf1_pcm_block_change(pcmp->substream, end + (pcmp->block_size / 2), pcmp->memory + (pcmp->dma_size / 2) + (end / 2), pcmp->block_size / 2);
		पूर्ण अन्यथा अणु
			snd_gf1_pcm_block_change(pcmp->substream, end, pcmp->memory + end, pcmp->block_size);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम snd_gf1_pcm_पूर्णांकerrupt_volume(काष्ठा snd_gus_card * gus,
					 काष्ठा snd_gus_voice * pvoice)
अणु
	अचिन्हित लघु vol;
	पूर्णांक cvoice;
	काष्ठा gus_pcm_निजी *pcmp = pvoice->निजी_data;

	/* stop ramp, but leave rollover bit untouched */
	spin_lock(&gus->reg_lock);
	snd_gf1_select_voice(gus, pvoice->number);
	snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_VOLUME_CONTROL);
	spin_unlock(&gus->reg_lock);
	अगर (pcmp == शून्य)
		वापस;
	/* are we active? */
	अगर (!(pcmp->flags & SNDRV_GF1_PCM_PFLG_ACTIVE))
		वापस;
	/* load real volume - better precision */
	cvoice = pcmp->pvoices[0] == pvoice ? 0 : 1;
	अगर (pcmp->substream == शून्य)
		वापस;
	vol = !cvoice ? gus->gf1.pcm_volume_level_left : gus->gf1.pcm_volume_level_right;
	spin_lock(&gus->reg_lock);
	snd_gf1_select_voice(gus, pvoice->number);
	snd_gf1_ग_लिखो16(gus, SNDRV_GF1_VW_VOLUME, vol);
	pcmp->final_volume = 1;
	spin_unlock(&gus->reg_lock);
पूर्ण

अटल व्योम snd_gf1_pcm_volume_change(काष्ठा snd_gus_card * gus)
अणु
पूर्ण

अटल पूर्णांक snd_gf1_pcm_poke_block(काष्ठा snd_gus_card *gus, अचिन्हित अक्षर *buf,
				  अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
				  पूर्णांक w16, पूर्णांक invert)
अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित दीर्घ flags;

	/*
	prपूर्णांकk(KERN_DEBUG
	       "poke block; buf = 0x%x, pos = %i, count = %i, port = 0x%x\n",
	       (पूर्णांक)buf, pos, count, gus->gf1.port);
	*/
	जबतक (count > 0) अणु
		len = count;
		अगर (len > 512)		/* limit, to allow IRQ */
			len = 512;
		count -= len;
		अगर (gus->पूर्णांकerwave) अणु
			spin_lock_irqsave(&gus->reg_lock, flags);
			snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, 0x01 | (invert ? 0x08 : 0x00));
			snd_gf1_dram_addr(gus, pos);
			अगर (w16) अणु
				outb(SNDRV_GF1_GW_DRAM_IO16, GUSP(gus, GF1REGSEL));
				outsw(GUSP(gus, GF1DATALOW), buf, len >> 1);
			पूर्ण अन्यथा अणु
				outsb(GUSP(gus, DRAM), buf, len);
			पूर्ण
			spin_unlock_irqrestore(&gus->reg_lock, flags);
			buf += 512;
			pos += 512;
		पूर्ण अन्यथा अणु
			invert = invert ? 0x80 : 0x00;
			अगर (w16) अणु
				len >>= 1;
				जबतक (len--) अणु
					snd_gf1_poke(gus, pos++, *buf++);
					snd_gf1_poke(gus, pos++, *buf++ ^ invert);
				पूर्ण
			पूर्ण अन्यथा अणु
				जबतक (len--)
					snd_gf1_poke(gus, pos++, *buf++ ^ invert);
			पूर्ण
		पूर्ण
		अगर (count > 0 && !in_पूर्णांकerrupt()) अणु
			schedule_समयout_पूर्णांकerruptible(1);
			अगर (संकेत_pending(current))
				वापस -EAGAIN;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक get_bpos(काष्ठा gus_pcm_निजी *pcmp, पूर्णांक voice, अचिन्हित पूर्णांक pos,
		    अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक bpos = pos + (voice * (pcmp->dma_size / 2));
	अगर (snd_BUG_ON(bpos > pcmp->dma_size))
		वापस -EIO;
	अगर (snd_BUG_ON(bpos + len > pcmp->dma_size))
		वापस -EIO;
	वापस bpos;
पूर्ण

अटल पूर्णांक playback_copy_ack(काष्ठा snd_pcm_substream *substream,
			     अचिन्हित पूर्णांक bpos, अचिन्हित पूर्णांक len)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा gus_pcm_निजी *pcmp = runसमय->निजी_data;
	काष्ठा snd_gus_card *gus = pcmp->gus;
	पूर्णांक w16, invert;

	अगर (len > 32)
		वापस snd_gf1_pcm_block_change(substream, bpos,
						pcmp->memory + bpos, len);

	w16 = (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16);
	invert = snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat);
	वापस snd_gf1_pcm_poke_block(gus, runसमय->dma_area + bpos,
				      pcmp->memory + bpos, len, w16, invert);
पूर्ण

अटल पूर्णांक snd_gf1_pcm_playback_copy(काष्ठा snd_pcm_substream *substream,
				     पूर्णांक voice, अचिन्हित दीर्घ pos,
				     व्योम __user *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा gus_pcm_निजी *pcmp = runसमय->निजी_data;
	अचिन्हित पूर्णांक len = count;
	पूर्णांक bpos;

	bpos = get_bpos(pcmp, voice, pos, len);
	अगर (bpos < 0)
		वापस pos;
	अगर (copy_from_user(runसमय->dma_area + bpos, src, len))
		वापस -EFAULT;
	वापस playback_copy_ack(substream, bpos, len);
पूर्ण

अटल पूर्णांक snd_gf1_pcm_playback_copy_kernel(काष्ठा snd_pcm_substream *substream,
					    पूर्णांक voice, अचिन्हित दीर्घ pos,
					    व्योम *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा gus_pcm_निजी *pcmp = runसमय->निजी_data;
	अचिन्हित पूर्णांक len = count;
	पूर्णांक bpos;

	bpos = get_bpos(pcmp, voice, pos, len);
	अगर (bpos < 0)
		वापस pos;
	स_नकल(runसमय->dma_area + bpos, src, len);
	वापस playback_copy_ack(substream, bpos, len);
पूर्ण

अटल पूर्णांक snd_gf1_pcm_playback_silence(काष्ठा snd_pcm_substream *substream,
					पूर्णांक voice, अचिन्हित दीर्घ pos,
					अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा gus_pcm_निजी *pcmp = runसमय->निजी_data;
	अचिन्हित पूर्णांक len = count;
	पूर्णांक bpos;
	
	bpos = get_bpos(pcmp, voice, pos, len);
	अगर (bpos < 0)
		वापस pos;
	snd_pcm_क्रमmat_set_silence(runसमय->क्रमmat, runसमय->dma_area + bpos,
				   bytes_to_samples(runसमय, count));
	वापस playback_copy_ack(substream, bpos, len);
पूर्ण

अटल पूर्णांक snd_gf1_pcm_playback_hw_params(काष्ठा snd_pcm_substream *substream,
					  काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_gus_card *gus = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा gus_pcm_निजी *pcmp = runसमय->निजी_data;

	अगर (runसमय->buffer_changed) अणु
		काष्ठा snd_gf1_mem_block *block;
		अगर (pcmp->memory > 0) अणु
			snd_gf1_mem_मुक्त(&gus->gf1.mem_alloc, pcmp->memory);
			pcmp->memory = 0;
		पूर्ण
		अगर ((block = snd_gf1_mem_alloc(&gus->gf1.mem_alloc,
		                               SNDRV_GF1_MEM_OWNER_DRIVER,
					       "GF1 PCM",
		                               runसमय->dma_bytes, 1, 32,
		                               शून्य)) == शून्य)
			वापस -ENOMEM;
		pcmp->memory = block->ptr;
	पूर्ण
	pcmp->voices = params_channels(hw_params);
	अगर (pcmp->pvoices[0] == शून्य) अणु
		अगर ((pcmp->pvoices[0] = snd_gf1_alloc_voice(pcmp->gus, SNDRV_GF1_VOICE_TYPE_PCM, 0, 0)) == शून्य)
			वापस -ENOMEM;
		pcmp->pvoices[0]->handler_wave = snd_gf1_pcm_पूर्णांकerrupt_wave;
		pcmp->pvoices[0]->handler_volume = snd_gf1_pcm_पूर्णांकerrupt_volume;
		pcmp->pvoices[0]->volume_change = snd_gf1_pcm_volume_change;
		pcmp->pvoices[0]->निजी_data = pcmp;
	पूर्ण
	अगर (pcmp->voices > 1 && pcmp->pvoices[1] == शून्य) अणु
		अगर ((pcmp->pvoices[1] = snd_gf1_alloc_voice(pcmp->gus, SNDRV_GF1_VOICE_TYPE_PCM, 0, 0)) == शून्य)
			वापस -ENOMEM;
		pcmp->pvoices[1]->handler_wave = snd_gf1_pcm_पूर्णांकerrupt_wave;
		pcmp->pvoices[1]->handler_volume = snd_gf1_pcm_पूर्णांकerrupt_volume;
		pcmp->pvoices[1]->volume_change = snd_gf1_pcm_volume_change;
		pcmp->pvoices[1]->निजी_data = pcmp;
	पूर्ण अन्यथा अगर (pcmp->voices == 1) अणु
		अगर (pcmp->pvoices[1]) अणु
			snd_gf1_मुक्त_voice(pcmp->gus, pcmp->pvoices[1]);
			pcmp->pvoices[1] = शून्य;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_pcm_playback_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा gus_pcm_निजी *pcmp = runसमय->निजी_data;

	अगर (pcmp->pvoices[0]) अणु
		snd_gf1_मुक्त_voice(pcmp->gus, pcmp->pvoices[0]);
		pcmp->pvoices[0] = शून्य;
	पूर्ण
	अगर (pcmp->pvoices[1]) अणु
		snd_gf1_मुक्त_voice(pcmp->gus, pcmp->pvoices[1]);
		pcmp->pvoices[1] = शून्य;
	पूर्ण
	अगर (pcmp->memory > 0) अणु
		snd_gf1_mem_मुक्त(&pcmp->gus->gf1.mem_alloc, pcmp->memory);
		pcmp->memory = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_pcm_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा gus_pcm_निजी *pcmp = runसमय->निजी_data;

	pcmp->bpos = 0;
	pcmp->dma_size = snd_pcm_lib_buffer_bytes(substream);
	pcmp->block_size = snd_pcm_lib_period_bytes(substream);
	pcmp->blocks = pcmp->dma_size / pcmp->block_size;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_pcm_playback_trigger(काष्ठा snd_pcm_substream *substream,
					पूर्णांक cmd)
अणु
	काष्ठा snd_gus_card *gus = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा gus_pcm_निजी *pcmp = runसमय->निजी_data;
	पूर्णांक voice;

	अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
		snd_gf1_pcm_trigger_up(substream);
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		spin_lock(&pcmp->lock);
		pcmp->flags &= ~SNDRV_GF1_PCM_PFLG_ACTIVE;
		spin_unlock(&pcmp->lock);
		voice = pcmp->pvoices[0]->number;
		snd_gf1_stop_voices(gus, voice, voice);
		अगर (pcmp->pvoices[1]) अणु
			voice = pcmp->pvoices[1]->number;
			snd_gf1_stop_voices(gus, voice, voice);
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_gf1_pcm_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_gus_card *gus = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा gus_pcm_निजी *pcmp = runसमय->निजी_data;
	अचिन्हित पूर्णांक pos;
	अचिन्हित अक्षर voice_ctrl;

	pos = 0;
	spin_lock(&gus->reg_lock);
	अगर (pcmp->flags & SNDRV_GF1_PCM_PFLG_ACTIVE) अणु
		snd_gf1_select_voice(gus, pcmp->pvoices[0]->number);
		voice_ctrl = snd_gf1_पढ़ो8(gus, SNDRV_GF1_VB_ADDRESS_CONTROL);
		pos = (snd_gf1_पढ़ो_addr(gus, SNDRV_GF1_VA_CURRENT, voice_ctrl & 4) >> 4) - pcmp->memory;
		अगर (substream->runसमय->channels > 1)
			pos <<= 1;
		pos = bytes_to_frames(runसमय, pos);
	पूर्ण
	spin_unlock(&gus->reg_lock);
	वापस pos;
पूर्ण

अटल स्थिर काष्ठा snd_ratnum घड़ी = अणु
	.num = 9878400/16,
	.den_min = 2,
	.den_max = 257,
	.den_step = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums hw_स्थिरraपूर्णांकs_घड़ीs  = अणु
	.nrats = 1,
	.rats = &घड़ी,
पूर्ण;

अटल पूर्णांक snd_gf1_pcm_capture_hw_params(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_gus_card *gus = snd_pcm_substream_chip(substream);

	gus->c_dma_size = params_buffer_bytes(hw_params);
	gus->c_period_size = params_period_bytes(hw_params);
	gus->c_pos = 0;
	gus->gf1.pcm_rcntrl_reg = 0x21;		/* IRQ at end, enable & start */
	अगर (params_channels(hw_params) > 1)
		gus->gf1.pcm_rcntrl_reg |= 2;
	अगर (gus->gf1.dma2 > 3)
		gus->gf1.pcm_rcntrl_reg |= 4;
	अगर (snd_pcm_क्रमmat_अचिन्हित(params_क्रमmat(hw_params)))
		gus->gf1.pcm_rcntrl_reg |= 0x80;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_pcm_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_gus_card *gus = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_RECORD_RATE, runसमय->rate_den - 2);
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL, 0);	/* disable sampling */
	snd_gf1_i_look8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL);	/* Sampling Control Register */
	snd_dma_program(gus->gf1.dma2, runसमय->dma_addr, gus->c_period_size, DMA_MODE_READ);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_pcm_capture_trigger(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd)
अणु
	काष्ठा snd_gus_card *gus = snd_pcm_substream_chip(substream);
	पूर्णांक val;
	
	अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
		val = gus->gf1.pcm_rcntrl_reg;
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		val = 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	spin_lock(&gus->reg_lock);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL, val);
	snd_gf1_look8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL);
	spin_unlock(&gus->reg_lock);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_gf1_pcm_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_gus_card *gus = snd_pcm_substream_chip(substream);
	पूर्णांक pos = snd_dma_poपूर्णांकer(gus->gf1.dma2, gus->c_period_size);
	pos = bytes_to_frames(substream->runसमय, (gus->c_pos + pos) % gus->c_dma_size);
	वापस pos;
पूर्ण

अटल व्योम snd_gf1_pcm_पूर्णांकerrupt_dma_पढ़ो(काष्ठा snd_gus_card * gus)
अणु
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL, 0);	/* disable sampling */
	snd_gf1_i_look8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL);	/* Sampling Control Register */
	अगर (gus->pcm_cap_substream != शून्य) अणु
		snd_gf1_pcm_capture_prepare(gus->pcm_cap_substream); 
		snd_gf1_pcm_capture_trigger(gus->pcm_cap_substream, SNDRV_PCM_TRIGGER_START);
		gus->c_pos += gus->c_period_size;
		snd_pcm_period_elapsed(gus->pcm_cap_substream);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_gf1_pcm_playback =
अणु
	.info =			SNDRV_PCM_INFO_NONINTERLEAVED,
	.क्रमmats		= (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U8 |
				 SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE),
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		5510,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_gf1_pcm_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U8,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_44100,
	.rate_min =		5510,
	.rate_max =		44100,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल व्योम snd_gf1_pcm_playback_मुक्त(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	kमुक्त(runसमय->निजी_data);
पूर्ण

अटल पूर्णांक snd_gf1_pcm_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा gus_pcm_निजी *pcmp;
	काष्ठा snd_gus_card *gus = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	pcmp = kzalloc(माप(*pcmp), GFP_KERNEL);
	अगर (pcmp == शून्य)
		वापस -ENOMEM;
	pcmp->gus = gus;
	spin_lock_init(&pcmp->lock);
	init_रुकोqueue_head(&pcmp->sleep);
	atomic_set(&pcmp->dma_count, 0);

	runसमय->निजी_data = pcmp;
	runसमय->निजी_मुक्त = snd_gf1_pcm_playback_मुक्त;

#अगर 0
	prपूर्णांकk(KERN_DEBUG "playback.buffer = 0x%lx, gf1.pcm_buffer = 0x%lx\n",
	       (दीर्घ) pcm->playback.buffer, (दीर्घ) gus->gf1.pcm_buffer);
#पूर्ण_अगर
	अगर ((err = snd_gf1_dma_init(gus)) < 0)
		वापस err;
	pcmp->flags = SNDRV_GF1_PCM_PFLG_NONE;
	pcmp->substream = substream;
	runसमय->hw = snd_gf1_pcm_playback;
	snd_pcm_limit_isa_dma_size(gus->gf1.dma1, &runसमय->hw.buffer_bytes_max);
	snd_pcm_limit_isa_dma_size(gus->gf1.dma1, &runसमय->hw.period_bytes_max);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 64);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_pcm_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_gus_card *gus = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा gus_pcm_निजी *pcmp = runसमय->निजी_data;
	
	अगर (!रुको_event_समयout(pcmp->sleep, (atomic_पढ़ो(&pcmp->dma_count) <= 0), 2*HZ))
		snd_prपूर्णांकk(KERN_ERR "gf1 pcm - serious DMA problem\n");

	snd_gf1_dma_करोne(gus);	
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_pcm_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_gus_card *gus = snd_pcm_substream_chip(substream);

	gus->gf1.पूर्णांकerrupt_handler_dma_पढ़ो = snd_gf1_pcm_पूर्णांकerrupt_dma_पढ़ो;
	gus->pcm_cap_substream = substream;
	substream->runसमय->hw = snd_gf1_pcm_capture;
	snd_pcm_limit_isa_dma_size(gus->gf1.dma2, &runसमय->hw.buffer_bytes_max);
	snd_pcm_limit_isa_dma_size(gus->gf1.dma2, &runसमय->hw.period_bytes_max);
	snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &hw_स्थिरraपूर्णांकs_घड़ीs);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_pcm_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_gus_card *gus = snd_pcm_substream_chip(substream);

	gus->pcm_cap_substream = शून्य;
	snd_gf1_set_शेष_handlers(gus, SNDRV_GF1_HANDLER_DMA_READ);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_pcm_volume_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 127;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_pcm_volume_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_gus_card *gus = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&gus->pcm_volume_level_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = gus->gf1.pcm_volume_level_left1;
	ucontrol->value.पूर्णांकeger.value[1] = gus->gf1.pcm_volume_level_right1;
	spin_unlock_irqrestore(&gus->pcm_volume_level_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_pcm_volume_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_gus_card *gus = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित पूर्णांक idx;
	अचिन्हित लघु val1, val2, vol;
	काष्ठा gus_pcm_निजी *pcmp;
	काष्ठा snd_gus_voice *pvoice;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] & 127;
	val2 = ucontrol->value.पूर्णांकeger.value[1] & 127;
	spin_lock_irqsave(&gus->pcm_volume_level_lock, flags);
	change = val1 != gus->gf1.pcm_volume_level_left1 ||
	         val2 != gus->gf1.pcm_volume_level_right1;
	gus->gf1.pcm_volume_level_left1 = val1;
	gus->gf1.pcm_volume_level_right1 = val2;
	gus->gf1.pcm_volume_level_left = snd_gf1_lvol_to_gvol_raw(val1 << 9) << 4;
	gus->gf1.pcm_volume_level_right = snd_gf1_lvol_to_gvol_raw(val2 << 9) << 4;
	spin_unlock_irqrestore(&gus->pcm_volume_level_lock, flags);
	/* are we active? */
	spin_lock_irqsave(&gus->voice_alloc, flags);
	क्रम (idx = 0; idx < 32; idx++) अणु
		pvoice = &gus->gf1.voices[idx];
		अगर (!pvoice->pcm)
			जारी;
		pcmp = pvoice->निजी_data;
		अगर (!(pcmp->flags & SNDRV_GF1_PCM_PFLG_ACTIVE))
			जारी;
		/* load real volume - better precision */
		spin_lock(&gus->reg_lock);
		snd_gf1_select_voice(gus, pvoice->number);
		snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_VOLUME_CONTROL);
		vol = pvoice == pcmp->pvoices[0] ? gus->gf1.pcm_volume_level_left : gus->gf1.pcm_volume_level_right;
		snd_gf1_ग_लिखो16(gus, SNDRV_GF1_VW_VOLUME, vol);
		pcmp->final_volume = 1;
		spin_unlock(&gus->reg_lock);
	पूर्ण
	spin_unlock_irqrestore(&gus->voice_alloc, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_gf1_pcm_volume_control =
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "PCM Playback Volume",
	.info = snd_gf1_pcm_volume_info,
	.get = snd_gf1_pcm_volume_get,
	.put = snd_gf1_pcm_volume_put
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_gf1_pcm_volume_control1 =
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "GPCM Playback Volume",
	.info = snd_gf1_pcm_volume_info,
	.get = snd_gf1_pcm_volume_get,
	.put = snd_gf1_pcm_volume_put
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_gf1_pcm_playback_ops = अणु
	.खोलो =		snd_gf1_pcm_playback_खोलो,
	.बंद =	snd_gf1_pcm_playback_बंद,
	.hw_params =	snd_gf1_pcm_playback_hw_params,
	.hw_मुक्त =	snd_gf1_pcm_playback_hw_मुक्त,
	.prepare =	snd_gf1_pcm_playback_prepare,
	.trigger =	snd_gf1_pcm_playback_trigger,
	.poपूर्णांकer =	snd_gf1_pcm_playback_poपूर्णांकer,
	.copy_user =	snd_gf1_pcm_playback_copy,
	.copy_kernel =	snd_gf1_pcm_playback_copy_kernel,
	.fill_silence =	snd_gf1_pcm_playback_silence,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_gf1_pcm_capture_ops = अणु
	.खोलो =		snd_gf1_pcm_capture_खोलो,
	.बंद =	snd_gf1_pcm_capture_बंद,
	.hw_params =	snd_gf1_pcm_capture_hw_params,
	.prepare =	snd_gf1_pcm_capture_prepare,
	.trigger =	snd_gf1_pcm_capture_trigger,
	.poपूर्णांकer =	snd_gf1_pcm_capture_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_gf1_pcm_new(काष्ठा snd_gus_card *gus, पूर्णांक pcm_dev, पूर्णांक control_index)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक capture, err;

	card = gus->card;
	capture = !gus->पूर्णांकerwave && !gus->ess_flag && !gus->ace_flag ? 1 : 0;
	err = snd_pcm_new(card,
			  gus->पूर्णांकerwave ? "AMD InterWave" : "GF1",
			  pcm_dev,
			  gus->gf1.pcm_channels / 2,
			  capture,
			  &pcm);
	अगर (err < 0)
		वापस err;
	pcm->निजी_data = gus;
	/* playback setup */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_gf1_pcm_playback_ops);

	क्रम (substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream; substream; substream = substream->next)
		snd_pcm_set_managed_buffer(substream, SNDRV_DMA_TYPE_DEV,
					   card->dev,
					   64*1024, gus->gf1.dma1 > 3 ? 128*1024 : 64*1024);
	
	pcm->info_flags = 0;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	अगर (capture) अणु
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_gf1_pcm_capture_ops);
		अगर (gus->gf1.dma2 == gus->gf1.dma1)
			pcm->info_flags |= SNDRV_PCM_INFO_HALF_DUPLEX;
		snd_pcm_set_managed_buffer(pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream,
					   SNDRV_DMA_TYPE_DEV, card->dev,
					   64*1024, gus->gf1.dma2 > 3 ? 128*1024 : 64*1024);
	पूर्ण
	म_नकल(pcm->name, pcm->id);
	अगर (gus->पूर्णांकerwave) अणु
		प्र_लिखो(pcm->name + म_माप(pcm->name), " rev %c", gus->revision + 'A');
	पूर्ण
	म_जोड़ो(pcm->name, " (synth)");
	gus->pcm = pcm;

	अगर (gus->codec_flag)
		kctl = snd_ctl_new1(&snd_gf1_pcm_volume_control1, gus);
	अन्यथा
		kctl = snd_ctl_new1(&snd_gf1_pcm_volume_control, gus);
	अगर ((err = snd_ctl_add(card, kctl)) < 0)
		वापस err;
	kctl->id.index = control_index;

	वापस 0;
पूर्ण

