<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
*
* Copyright Adrian McMenamin 2005, 2006, 2007
* <adrian@mcmen.demon.co.uk>
* Requires firmware (BSD licenced) available from:
* http://linuxdc.cvs.sourceक्रमge.net/linuxdc/linux-sh-dc/sound/oss/aica/firmware/
* or the मुख्यtainer
*/

#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/info.h>
#समावेश <यंत्र/dma.h>
#समावेश <mach/sysasic.h>
#समावेश "aica.h"

MODULE_AUTHOR("Adrian McMenamin <adrian@mcmen.demon.co.uk>");
MODULE_DESCRIPTION("Dreamcast AICA sound (pcm) driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("aica_firmware.bin");

/* module parameters */
#घोषणा CARD_NAME "AICA"
अटल पूर्णांक index = -1;
अटल अक्षर *id;
अटल bool enable = 1;
module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for " CARD_NAME " soundcard.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for " CARD_NAME " soundcard.");
module_param(enable, bool, 0644);
MODULE_PARM_DESC(enable, "Enable " CARD_NAME " soundcard.");

/* Simple platक्रमm device */
अटल काष्ठा platक्रमm_device *pd;
अटल काष्ठा resource aica_memory_space[2] = अणु
	अणु
	 .name = "AICA ARM CONTROL",
	 .start = ARM_RESET_REGISTER,
	 .flags = IORESOURCE_MEM,
	 .end = ARM_RESET_REGISTER + 3,
	 पूर्ण,
	अणु
	 .name = "AICA Sound RAM",
	 .start = SPU_MEMORY_BASE,
	 .flags = IORESOURCE_MEM,
	 .end = SPU_MEMORY_BASE + 0x200000 - 1,
	 पूर्ण,
पूर्ण;

/* SPU specअगरic functions */
/* spu_ग_लिखो_रुको - रुको क्रम G2-SH FIFO to clear */
अटल व्योम spu_ग_लिखो_रुको(व्योम)
अणु
	पूर्णांक समय_count;
	समय_count = 0;
	जबतक (1) अणु
		अगर (!(पढ़ोl(G2_FIFO) & 0x11))
			अवरोध;
		/* To ensure hardware failure करोesn't wedge kernel */
		समय_count++;
		अगर (समय_count > 0x10000) अणु
			snd_prपूर्णांकk
			    ("WARNING: G2 FIFO appears to be blocked.\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* spu_स_रखो - ग_लिखो to memory in SPU address space */
अटल व्योम spu_स_रखो(u32 toi, u32 what, पूर्णांक length)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	अगर (snd_BUG_ON(length % 4))
		वापस;
	क्रम (i = 0; i < length; i++) अणु
		अगर (!(i % 8))
			spu_ग_लिखो_रुको();
		local_irq_save(flags);
		ग_लिखोl(what, toi + SPU_MEMORY_BASE);
		local_irq_restore(flags);
		toi++;
	पूर्ण
पूर्ण

/* spu_memload - ग_लिखो to SPU address space */
अटल व्योम spu_memload(u32 toi, स्थिर व्योम *from, पूर्णांक length)
अणु
	अचिन्हित दीर्घ flags;
	स्थिर u32 *froml = from;
	u32 __iomem *to = (u32 __iomem *) (SPU_MEMORY_BASE + toi);
	पूर्णांक i;
	u32 val;
	length = DIV_ROUND_UP(length, 4);
	spu_ग_लिखो_रुको();
	क्रम (i = 0; i < length; i++) अणु
		अगर (!(i % 8))
			spu_ग_लिखो_रुको();
		val = *froml;
		local_irq_save(flags);
		ग_लिखोl(val, to);
		local_irq_restore(flags);
		froml++;
		to++;
	पूर्ण
पूर्ण

/* spu_disable - set spu रेजिस्टरs to stop sound output */
अटल व्योम spu_disable(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	u32 regval;
	spu_ग_लिखो_रुको();
	regval = पढ़ोl(ARM_RESET_REGISTER);
	regval |= 1;
	spu_ग_लिखो_रुको();
	local_irq_save(flags);
	ग_लिखोl(regval, ARM_RESET_REGISTER);
	local_irq_restore(flags);
	क्रम (i = 0; i < 64; i++) अणु
		spu_ग_लिखो_रुको();
		regval = पढ़ोl(SPU_REGISTER_BASE + (i * 0x80));
		regval = (regval & ~0x4000) | 0x8000;
		spu_ग_लिखो_रुको();
		local_irq_save(flags);
		ग_लिखोl(regval, SPU_REGISTER_BASE + (i * 0x80));
		local_irq_restore(flags);
	पूर्ण
पूर्ण

/* spu_enable - set spu रेजिस्टरs to enable sound output */
अटल व्योम spu_enable(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	u32 regval = पढ़ोl(ARM_RESET_REGISTER);
	regval &= ~1;
	spu_ग_लिखो_रुको();
	local_irq_save(flags);
	ग_लिखोl(regval, ARM_RESET_REGISTER);
	local_irq_restore(flags);
पूर्ण

/* 
 * Halt the sound processor, clear the memory,
 * load some शेष ARM7 code, and then restart ARM7
*/
अटल व्योम spu_reset(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spu_disable();
	spu_स_रखो(0, 0, 0x200000 / 4);
	/* Put ARM7 in endless loop */
	local_irq_save(flags);
	__raw_ग_लिखोl(0xea000002, SPU_MEMORY_BASE);
	local_irq_restore(flags);
	spu_enable();
पूर्ण

/* aica_chn_start - ग_लिखो to spu to start playback */
अटल व्योम aica_chn_start(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spu_ग_लिखो_रुको();
	local_irq_save(flags);
	ग_लिखोl(AICA_CMD_KICK | AICA_CMD_START, (u32 *) AICA_CONTROL_POINT);
	local_irq_restore(flags);
पूर्ण

/* aica_chn_halt - ग_लिखो to spu to halt playback */
अटल व्योम aica_chn_halt(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spu_ग_लिखो_रुको();
	local_irq_save(flags);
	ग_लिखोl(AICA_CMD_KICK | AICA_CMD_STOP, (u32 *) AICA_CONTROL_POINT);
	local_irq_restore(flags);
पूर्ण

/* ALSA code below */
अटल स्थिर काष्ठा snd_pcm_hardware snd_pcm_aica_playback_hw = अणु
	.info = (SNDRV_PCM_INFO_NONINTERLEAVED),
	.क्रमmats =
	    (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE |
	     SNDRV_PCM_FMTBIT_IMA_ADPCM),
	.rates = SNDRV_PCM_RATE_8000_48000,
	.rate_min = 8000,
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 2,
	.buffer_bytes_max = AICA_BUFFER_SIZE,
	.period_bytes_min = AICA_PERIOD_SIZE,
	.period_bytes_max = AICA_PERIOD_SIZE,
	.periods_min = AICA_PERIOD_NUMBER,
	.periods_max = AICA_PERIOD_NUMBER,
पूर्ण;

अटल पूर्णांक aica_dma_transfer(पूर्णांक channels, पूर्णांक buffer_size,
			     काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक q, err, period_offset;
	काष्ठा snd_card_aica *dreamcastcard;
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित दीर्घ flags;
	err = 0;
	dreamcastcard = substream->pcm->निजी_data;
	period_offset = dreamcastcard->clicks;
	period_offset %= (AICA_PERIOD_NUMBER / channels);
	runसमय = substream->runसमय;
	क्रम (q = 0; q < channels; q++) अणु
		local_irq_save(flags);
		err = dma_xfer(AICA_DMA_CHANNEL,
			       (अचिन्हित दीर्घ) (runसमय->dma_area +
						(AICA_BUFFER_SIZE * q) /
						channels +
						AICA_PERIOD_SIZE *
						period_offset),
			       AICA_CHANNEL0_OFFSET + q * CHANNEL_OFFSET +
			       AICA_PERIOD_SIZE * period_offset,
			       buffer_size / channels, AICA_DMA_MODE);
		अगर (unlikely(err < 0)) अणु
			local_irq_restore(flags);
			अवरोध;
		पूर्ण
		dma_रुको_क्रम_completion(AICA_DMA_CHANNEL);
		local_irq_restore(flags);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम startup_aica(काष्ठा snd_card_aica *dreamcastcard)
अणु
	spu_memload(AICA_CHANNEL0_CONTROL_OFFSET,
		    dreamcastcard->channel, माप(काष्ठा aica_channel));
	aica_chn_start();
पूर्ण

अटल व्योम run_spu_dma(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक buffer_size;
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा snd_card_aica *dreamcastcard;
	dreamcastcard =
	    container_of(work, काष्ठा snd_card_aica, spu_dma_work);
	runसमय = dreamcastcard->substream->runसमय;
	अगर (unlikely(dreamcastcard->dma_check == 0)) अणु
		buffer_size =
		    frames_to_bytes(runसमय, runसमय->buffer_size);
		अगर (runसमय->channels > 1)
			dreamcastcard->channel->flags |= 0x01;
		aica_dma_transfer(runसमय->channels, buffer_size,
				  dreamcastcard->substream);
		startup_aica(dreamcastcard);
		dreamcastcard->clicks =
		    buffer_size / (AICA_PERIOD_SIZE * runसमय->channels);
		वापस;
	पूर्ण अन्यथा अणु
		aica_dma_transfer(runसमय->channels,
				  AICA_PERIOD_SIZE * runसमय->channels,
				  dreamcastcard->substream);
		snd_pcm_period_elapsed(dreamcastcard->substream);
		dreamcastcard->clicks++;
		अगर (unlikely(dreamcastcard->clicks >= AICA_PERIOD_NUMBER))
			dreamcastcard->clicks %= AICA_PERIOD_NUMBER;
		mod_समयr(&dreamcastcard->समयr, jअगरfies + 1);
	पूर्ण
पूर्ण

अटल व्योम aica_period_elapsed(काष्ठा समयr_list *t)
अणु
	काष्ठा snd_card_aica *dreamcastcard = from_समयr(dreamcastcard,
							      t, समयr);
	काष्ठा snd_pcm_substream *substream = dreamcastcard->substream;
	/*समयr function - so cannot sleep */
	पूर्णांक play_period;
	काष्ठा snd_pcm_runसमय *runसमय;
	runसमय = substream->runसमय;
	dreamcastcard = substream->pcm->निजी_data;
	/* Have we played out an additional period? */
	play_period =
	    frames_to_bytes(runसमय,
			    पढ़ोl
			    (AICA_CONTROL_CHANNEL_SAMPLE_NUMBER)) /
	    AICA_PERIOD_SIZE;
	अगर (play_period == dreamcastcard->current_period) अणु
		/* reschedule the समयr */
		mod_समयr(&(dreamcastcard->समयr), jअगरfies + 1);
		वापस;
	पूर्ण
	अगर (runसमय->channels > 1)
		dreamcastcard->current_period = play_period;
	अगर (unlikely(dreamcastcard->dma_check == 0))
		dreamcastcard->dma_check = 1;
	schedule_work(&(dreamcastcard->spu_dma_work));
पूर्ण

अटल व्योम spu_begin_dma(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_card_aica *dreamcastcard;
	काष्ठा snd_pcm_runसमय *runसमय;
	runसमय = substream->runसमय;
	dreamcastcard = substream->pcm->निजी_data;
	/*get the queue to करो the work */
	schedule_work(&(dreamcastcard->spu_dma_work));
	mod_समयr(&dreamcastcard->समयr, jअगरfies + 4);
पूर्ण

अटल पूर्णांक snd_aicapcm_pcm_खोलो(काष्ठा snd_pcm_substream
				*substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा aica_channel *channel;
	काष्ठा snd_card_aica *dreamcastcard;
	अगर (!enable)
		वापस -ENOENT;
	dreamcastcard = substream->pcm->निजी_data;
	channel = kदो_स्मृति(माप(काष्ठा aica_channel), GFP_KERNEL);
	अगर (!channel)
		वापस -ENOMEM;
	/* set शेषs क्रम channel */
	channel->sfmt = SM_8BIT;
	channel->cmd = AICA_CMD_START;
	channel->vol = dreamcastcard->master_volume;
	channel->pan = 0x80;
	channel->pos = 0;
	channel->flags = 0;	/* शेष to mono */
	dreamcastcard->channel = channel;
	runसमय = substream->runसमय;
	runसमय->hw = snd_pcm_aica_playback_hw;
	spu_enable();
	dreamcastcard->clicks = 0;
	dreamcastcard->current_period = 0;
	dreamcastcard->dma_check = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_aicapcm_pcm_बंद(काष्ठा snd_pcm_substream
				 *substream)
अणु
	काष्ठा snd_card_aica *dreamcastcard = substream->pcm->निजी_data;
	flush_work(&(dreamcastcard->spu_dma_work));
	del_समयr(&dreamcastcard->समयr);
	dreamcastcard->substream = शून्य;
	kमुक्त(dreamcastcard->channel);
	spu_disable();
	वापस 0;
पूर्ण

अटल पूर्णांक snd_aicapcm_pcm_prepare(काष्ठा snd_pcm_substream
				   *substream)
अणु
	काष्ठा snd_card_aica *dreamcastcard = substream->pcm->निजी_data;
	अगर ((substream->runसमय)->क्रमmat == SNDRV_PCM_FORMAT_S16_LE)
		dreamcastcard->channel->sfmt = SM_16BIT;
	dreamcastcard->channel->freq = substream->runसमय->rate;
	dreamcastcard->substream = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_aicapcm_pcm_trigger(काष्ठा snd_pcm_substream
				   *substream, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		spu_begin_dma(substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		aica_chn_halt();
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ snd_aicapcm_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream
					     *substream)
अणु
	वापस पढ़ोl(AICA_CONTROL_CHANNEL_SAMPLE_NUMBER);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_aicapcm_playback_ops = अणु
	.खोलो = snd_aicapcm_pcm_खोलो,
	.बंद = snd_aicapcm_pcm_बंद,
	.prepare = snd_aicapcm_pcm_prepare,
	.trigger = snd_aicapcm_pcm_trigger,
	.poपूर्णांकer = snd_aicapcm_pcm_poपूर्णांकer,
पूर्ण;

/* TO DO: set up to handle more than one pcm instance */
अटल पूर्णांक __init snd_aicapcmchip(काष्ठा snd_card_aica
				  *dreamcastcard, पूर्णांक pcm_index)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;
	/* AICA has no capture ability */
	err =
	    snd_pcm_new(dreamcastcard->card, "AICA PCM", pcm_index, 1, 0,
			&pcm);
	अगर (unlikely(err < 0))
		वापस err;
	pcm->निजी_data = dreamcastcard;
	म_नकल(pcm->name, "AICA PCM");
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_aicapcm_playback_ops);
	/* Allocate the DMA buffers */
	snd_pcm_set_managed_buffer_all(pcm,
				       SNDRV_DMA_TYPE_CONTINUOUS,
				       शून्य,
				       AICA_BUFFER_SIZE,
				       AICA_BUFFER_SIZE);
	वापस 0;
पूर्ण

/* Mixer controls */
#घोषणा aica_pcmचयन_info		snd_ctl_boolean_mono_info

अटल पूर्णांक aica_pcmचयन_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = 1;	/* TO DO: Fix me */
	वापस 0;
पूर्ण

अटल पूर्णांक aica_pcmचयन_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अगर (ucontrol->value.पूर्णांकeger.value[0] == 1)
		वापस 0;	/* TO DO: Fix me */
	अन्यथा
		aica_chn_halt();
	वापस 0;
पूर्ण

अटल पूर्णांक aica_pcmvolume_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0xFF;
	वापस 0;
पूर्ण

अटल पूर्णांक aica_pcmvolume_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_card_aica *dreamcastcard;
	dreamcastcard = kcontrol->निजी_data;
	अगर (unlikely(!dreamcastcard->channel))
		वापस -ETXTBSY;	/* we've not yet been set up */
	ucontrol->value.पूर्णांकeger.value[0] = dreamcastcard->channel->vol;
	वापस 0;
पूर्ण

अटल पूर्णांक aica_pcmvolume_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_card_aica *dreamcastcard;
	अचिन्हित पूर्णांक vol;
	dreamcastcard = kcontrol->निजी_data;
	अगर (unlikely(!dreamcastcard->channel))
		वापस -ETXTBSY;
	vol = ucontrol->value.पूर्णांकeger.value[0];
	अगर (vol > 0xff)
		वापस -EINVAL;
	अगर (unlikely(dreamcastcard->channel->vol == vol))
		वापस 0;
	dreamcastcard->channel->vol = ucontrol->value.पूर्णांकeger.value[0];
	dreamcastcard->master_volume = ucontrol->value.पूर्णांकeger.value[0];
	spu_memload(AICA_CHANNEL0_CONTROL_OFFSET,
		    dreamcastcard->channel, माप(काष्ठा aica_channel));
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_aica_pcmचयन_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "PCM Playback Switch",
	.index = 0,
	.info = aica_pcmचयन_info,
	.get = aica_pcmचयन_get,
	.put = aica_pcmचयन_put
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_aica_pcmvolume_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "PCM Playback Volume",
	.index = 0,
	.info = aica_pcmvolume_info,
	.get = aica_pcmvolume_get,
	.put = aica_pcmvolume_put
पूर्ण;

अटल पूर्णांक load_aica_firmware(व्योम)
अणु
	पूर्णांक err;
	स्थिर काष्ठा firmware *fw_entry;
	spu_reset();
	err = request_firmware(&fw_entry, "aica_firmware.bin", &pd->dev);
	अगर (unlikely(err))
		वापस err;
	/* ग_लिखो firmware पूर्णांकo memory */
	spu_disable();
	spu_memload(0, fw_entry->data, fw_entry->size);
	spu_enable();
	release_firmware(fw_entry);
	वापस err;
पूर्ण

अटल पूर्णांक add_aicamixer_controls(काष्ठा snd_card_aica *dreamcastcard)
अणु
	पूर्णांक err;
	err = snd_ctl_add
	    (dreamcastcard->card,
	     snd_ctl_new1(&snd_aica_pcmvolume_control, dreamcastcard));
	अगर (unlikely(err < 0))
		वापस err;
	err = snd_ctl_add
	    (dreamcastcard->card,
	     snd_ctl_new1(&snd_aica_pcmचयन_control, dreamcastcard));
	अगर (unlikely(err < 0))
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_aica_हटाओ(काष्ठा platक्रमm_device *devptr)
अणु
	काष्ठा snd_card_aica *dreamcastcard;
	dreamcastcard = platक्रमm_get_drvdata(devptr);
	अगर (unlikely(!dreamcastcard))
		वापस -ENODEV;
	snd_card_मुक्त(dreamcastcard->card);
	kमुक्त(dreamcastcard);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_aica_probe(काष्ठा platक्रमm_device *devptr)
अणु
	पूर्णांक err;
	काष्ठा snd_card_aica *dreamcastcard;
	dreamcastcard = kzalloc(माप(काष्ठा snd_card_aica), GFP_KERNEL);
	अगर (unlikely(!dreamcastcard))
		वापस -ENOMEM;
	err = snd_card_new(&devptr->dev, index, SND_AICA_DRIVER,
			   THIS_MODULE, 0, &dreamcastcard->card);
	अगर (unlikely(err < 0)) अणु
		kमुक्त(dreamcastcard);
		वापस err;
	पूर्ण
	म_नकल(dreamcastcard->card->driver, "snd_aica");
	म_नकल(dreamcastcard->card->लघुname, SND_AICA_DRIVER);
	म_नकल(dreamcastcard->card->दीर्घname,
	       "Yamaha AICA Super Intelligent Sound Processor for SEGA Dreamcast");
	/* Prepare to use the queue */
	INIT_WORK(&(dreamcastcard->spu_dma_work), run_spu_dma);
	समयr_setup(&dreamcastcard->समयr, aica_period_elapsed, 0);
	/* Load the PCM 'chip' */
	err = snd_aicapcmchip(dreamcastcard, 0);
	अगर (unlikely(err < 0))
		जाओ मुक्तdreamcast;
	/* Add basic controls */
	err = add_aicamixer_controls(dreamcastcard);
	अगर (unlikely(err < 0))
		जाओ मुक्तdreamcast;
	/* Register the card with ALSA subप्रणाली */
	err = snd_card_रेजिस्टर(dreamcastcard->card);
	अगर (unlikely(err < 0))
		जाओ मुक्तdreamcast;
	platक्रमm_set_drvdata(devptr, dreamcastcard);
	snd_prपूर्णांकk
	    ("ALSA Driver for Yamaha AICA Super Intelligent Sound Processor\n");
	वापस 0;
      मुक्तdreamcast:
	snd_card_मुक्त(dreamcastcard->card);
	kमुक्त(dreamcastcard);
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_aica_driver = अणु
	.probe = snd_aica_probe,
	.हटाओ = snd_aica_हटाओ,
	.driver = अणु
		.name = SND_AICA_DRIVER,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init aica_init(व्योम)
अणु
	पूर्णांक err;
	err = platक्रमm_driver_रेजिस्टर(&snd_aica_driver);
	अगर (unlikely(err < 0))
		वापस err;
	pd = platक्रमm_device_रेजिस्टर_simple(SND_AICA_DRIVER, -1,
					     aica_memory_space, 2);
	अगर (IS_ERR(pd)) अणु
		platक्रमm_driver_unरेजिस्टर(&snd_aica_driver);
		वापस PTR_ERR(pd);
	पूर्ण
	/* Load the firmware */
	वापस load_aica_firmware();
पूर्ण

अटल व्योम __निकास aica_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pd);
	platक्रमm_driver_unरेजिस्टर(&snd_aica_driver);
	/* Kill any sound still playing and reset ARM7 to safe state */
	spu_reset();
पूर्ण

module_init(aica_init);
module_निकास(aica_निकास);
