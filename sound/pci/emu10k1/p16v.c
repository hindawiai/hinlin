<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by James Courtier-Dutton <James@superbug.demon.co.uk>
 *  Driver p16v chips
 *  Version: 0.25
 *
 *  FEATURES currently supported:
 *    Output fixed at S32_LE, 2 channel to hw:0,0
 *    Rates: 44.1, 48, 96, 192.
 *
 *  Changelog:
 *  0.8
 *    Use separate card based buffer क्रम periods table.
 *  0.9
 *    Use 2 channel output streams instead of 8 channel.
 *       (8 channel output streams might be good क्रम ASIO type output)
 *    Corrected speaker output, so Front -> Front etc.
 *  0.10
 *    Fixed missed पूर्णांकerrupts.
 *  0.11
 *    Add Sound card model number and names.
 *    Add Analog volume controls.
 *  0.12
 *    Corrected playback पूर्णांकerrupts. Now पूर्णांकerrupt per period, instead of half period.
 *  0.13
 *    Use single trigger क्रम multichannel.
 *  0.14
 *    Mic capture now works at fixed: S32_LE, 96000Hz, Stereo.
 *  0.15
 *    Force buffer_size / period_size == INTEGER.
 *  0.16
 *    Update p16v.c to work with changed alsa api.
 *  0.17
 *    Update p16v.c to work with changed alsa api. Removed boot_devs.
 *  0.18
 *    Merging with snd-emu10k1 driver.
 *  0.19
 *    One stereo channel at 24bit now works.
 *  0.20
 *    Added better रेजिस्टर defines.
 *  0.21
 *    Integrated with snd-emu10k1 driver.
 *  0.22
 *    Removed #अगर 0 ... #पूर्ण_अगर
 *  0.23
 *    Implement dअगरferent capture rates.
 *  0.24
 *    Implement dअगरferent capture source channels.
 *    e.g. When HD Capture source is set to SPDIF,
 *    setting HD Capture channel to 0 captures from CDROM digital input.
 *    setting HD Capture channel to 1 captures from SPDIF in.
 *  0.25
 *    Include capture buffer sizes.
 *
 *  BUGS:
 *    Some stability problems when unloading the snd-p16v kernel module.
 *    --
 *
 *  TODO:
 *    SPDIF out.
 *    Find out how to change capture sample rates. E.g. To record SPDIF at 48000Hz.
 *    Currently capture fixed at 48000Hz.
 *
 *    --
 *  GENERAL INFO:
 *    Model: SB0240
 *    P16V Chip: CA0151-DBS
 *    Audigy 2 Chip: CA0102-IAT
 *    AC97 Codec: STAC 9721
 *    ADC: Philips 1361T (Stereo 24bit)
 *    DAC: CS4382-K (8-channel, 24bit, 192Khz)
 *
 *  This code was initially based on code from ALSA's emu10k1x.c which is:
 *  Copyright (c) by Francisco Moraes <fmoraes@nc.rr.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/moduleparam.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/info.h>
#समावेश <sound/tlv.h>
#समावेश <sound/emu10k1.h>
#समावेश "p16v.h"

#घोषणा SET_CHANNEL 0  /* Testing channel outमाला_दो 0=Front, 1=Center/LFE, 2=Unknown, 3=Rear */
#घोषणा PCM_FRONT_CHANNEL 0
#घोषणा PCM_REAR_CHANNEL 1
#घोषणा PCM_CENTER_LFE_CHANNEL 2
#घोषणा PCM_SIDE_CHANNEL 3
#घोषणा CONTROL_FRONT_CHANNEL 0
#घोषणा CONTROL_REAR_CHANNEL 3
#घोषणा CONTROL_CENTER_LFE_CHANNEL 1
#घोषणा CONTROL_SIDE_CHANNEL 2

/* Card IDs:
 * Class 0401: 1102:0004 (rev 04) Subप्रणाली: 1102:2002 -> Audigy2 ZS 7.1 Model:SB0350
 * Class 0401: 1102:0004 (rev 04) Subप्रणाली: 1102:1007 -> Audigy2 6.1    Model:SB0240
 * Class 0401: 1102:0004 (rev 04) Subप्रणाली: 1102:1002 -> Audigy2 Platinum  Model:SB msb0240230009266
 * Class 0401: 1102:0004 (rev 04) Subप्रणाली: 1102:2007 -> Audigy4 Pro Model:SB0380 M1SB0380472001901E
 *
 */

 /* hardware definition */
अटल स्थिर काष्ठा snd_pcm_hardware snd_p16v_playback_hw = अणु
	.info =			SNDRV_PCM_INFO_MMAP | 
				SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_BLOCK_TRANSFER |
				SNDRV_PCM_INFO_RESUME |
				SNDRV_PCM_INFO_MMAP_VALID |
				SNDRV_PCM_INFO_SYNC_START,
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_LE, /* Only supports 24-bit samples padded to 32 bits. */
	.rates =		SNDRV_PCM_RATE_192000 | SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_44100, 
	.rate_min =		44100,
	.rate_max =		192000,
	.channels_min =		8, 
	.channels_max =		8,
	.buffer_bytes_max =	((65536 - 64) * 8),
	.period_bytes_min =	64,
	.period_bytes_max =	(65536 - 64),
	.periods_min =		2,
	.periods_max =		8,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_p16v_capture_hw = अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_LE,
	.rates =		SNDRV_PCM_RATE_192000 | SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_44100, 
	.rate_min =		44100,
	.rate_max =		192000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(65536 - 64),
	.period_bytes_min =	64,
	.period_bytes_max =	(65536 - 128) >> 1,  /* size has to be N*64 bytes */
	.periods_min =		2,
	.periods_max =		2,
	.fअगरo_size =		0,
पूर्ण;

अटल व्योम snd_p16v_pcm_मुक्त_substream(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;

	kमुक्त(epcm);
पूर्ण

/* खोलो_playback callback */
अटल पूर्णांक snd_p16v_pcm_खोलो_playback_channel(काष्ठा snd_pcm_substream *substream, पूर्णांक channel_id)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
        काष्ठा snd_emu10k1_voice *channel = &(emu->p16v_voices[channel_id]);
	काष्ठा snd_emu10k1_pcm *epcm;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	epcm = kzalloc(माप(*epcm), GFP_KERNEL);
	/* dev_dbg(emu->card->dev, "epcm kcalloc: %p\n", epcm); */

	अगर (epcm == शून्य)
		वापस -ENOMEM;
	epcm->emu = emu;
	epcm->substream = substream;
	/*
	dev_dbg(emu->card->dev, "epcm device=%d, channel_id=%d\n",
		   substream->pcm->device, channel_id);
	*/
	runसमय->निजी_data = epcm;
	runसमय->निजी_मुक्त = snd_p16v_pcm_मुक्त_substream;
  
	runसमय->hw = snd_p16v_playback_hw;

        channel->emu = emu;
        channel->number = channel_id;

        channel->use=1;
#अगर 0 /* debug */
	dev_dbg(emu->card->dev,
		   "p16v: open channel_id=%d, channel=%p, use=0x%x\n",
		   channel_id, channel, channel->use);
	dev_dbg(emu->card->dev, "open:channel_id=%d, chip=%p, channel=%p\n",
	       channel_id, chip, channel);
#पूर्ण_अगर /* debug */
	/* channel->पूर्णांकerrupt = snd_p16v_pcm_channel_पूर्णांकerrupt; */
	channel->epcm = epcm;
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
                वापस err;

	runसमय->sync.id32[0] = substream->pcm->card->number;
	runसमय->sync.id32[1] = 'P';
	runसमय->sync.id32[2] = 16;
	runसमय->sync.id32[3] = 'V';

	वापस 0;
पूर्ण
/* खोलो_capture callback */
अटल पूर्णांक snd_p16v_pcm_खोलो_capture_channel(काष्ठा snd_pcm_substream *substream, पूर्णांक channel_id)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_emu10k1_voice *channel = &(emu->p16v_capture_voice);
	काष्ठा snd_emu10k1_pcm *epcm;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	epcm = kzalloc(माप(*epcm), GFP_KERNEL);
	/* dev_dbg(emu->card->dev, "epcm kcalloc: %p\n", epcm); */

	अगर (epcm == शून्य)
		वापस -ENOMEM;
	epcm->emu = emu;
	epcm->substream = substream;
	/*
	dev_dbg(emu->card->dev, "epcm device=%d, channel_id=%d\n",
		   substream->pcm->device, channel_id);
	*/
	runसमय->निजी_data = epcm;
	runसमय->निजी_मुक्त = snd_p16v_pcm_मुक्त_substream;
  
	runसमय->hw = snd_p16v_capture_hw;

	channel->emu = emu;
	channel->number = channel_id;

	channel->use=1;
#अगर 0 /* debug */
	dev_dbg(emu->card->dev,
		   "p16v: open channel_id=%d, channel=%p, use=0x%x\n",
		   channel_id, channel, channel->use);
	dev_dbg(emu->card->dev, "open:channel_id=%d, chip=%p, channel=%p\n",
	       channel_id, chip, channel);
#पूर्ण_अगर /* debug */
	/* channel->पूर्णांकerrupt = snd_p16v_pcm_channel_पूर्णांकerrupt; */
	channel->epcm = epcm;
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		वापस err;

	वापस 0;
पूर्ण


/* बंद callback */
अटल पूर्णांक snd_p16v_pcm_बंद_playback(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	//काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	//काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	emu->p16v_voices[substream->pcm->device - emu->p16v_device_offset].use = 0;
	/* FIXME: maybe zero others */
	वापस 0;
पूर्ण

/* बंद callback */
अटल पूर्णांक snd_p16v_pcm_बंद_capture(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	//काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	//काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	emu->p16v_capture_voice.use = 0;
	/* FIXME: maybe zero others */
	वापस 0;
पूर्ण

अटल पूर्णांक snd_p16v_pcm_खोलो_playback_front(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_p16v_pcm_खोलो_playback_channel(substream, PCM_FRONT_CHANNEL);
पूर्ण

अटल पूर्णांक snd_p16v_pcm_खोलो_capture(काष्ठा snd_pcm_substream *substream)
अणु
	// Only using channel 0 क्रम now, but the card has 2 channels.
	वापस snd_p16v_pcm_खोलो_capture_channel(substream, 0);
पूर्ण

/* prepare playback callback */
अटल पूर्णांक snd_p16v_pcm_prepare_playback(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक channel = substream->pcm->device - emu->p16v_device_offset;
	u32 *table_base = (u32 *)(emu->p16v_buffer.area+(8*16*channel));
	u32 period_size_bytes = frames_to_bytes(runसमय, runसमय->period_size);
	पूर्णांक i;
	u32 पंचांगp;
	
#अगर 0 /* debug */
	dev_dbg(emu->card->dev,
		"prepare:channel_number=%d, rate=%d, "
		   "format=0x%x, channels=%d, buffer_size=%ld, "
		   "period_size=%ld, periods=%u, frames_to_bytes=%d\n",
		   channel, runसमय->rate, runसमय->क्रमmat, runसमय->channels,
		   runसमय->buffer_size, runसमय->period_size,
		   runसमय->periods, frames_to_bytes(runसमय, 1));
	dev_dbg(emu->card->dev,
		"dma_addr=%x, dma_area=%p, table_base=%p\n",
		   runसमय->dma_addr, runसमय->dma_area, table_base);
	dev_dbg(emu->card->dev,
		"dma_addr=%x, dma_area=%p, dma_bytes(size)=%x\n",
		   emu->p16v_buffer.addr, emu->p16v_buffer.area,
		   emu->p16v_buffer.bytes);
#पूर्ण_अगर /* debug */
	पंचांगp = snd_emu10k1_ptr_पढ़ो(emu, A_SPDIF_SAMPLERATE, channel);
        चयन (runसमय->rate) अणु
	हाल 44100:
	  snd_emu10k1_ptr_ग_लिखो(emu, A_SPDIF_SAMPLERATE, channel, (पंचांगp & ~0xe0e0) | 0x8080);
	  अवरोध;
	हाल 96000:
	  snd_emu10k1_ptr_ग_लिखो(emu, A_SPDIF_SAMPLERATE, channel, (पंचांगp & ~0xe0e0) | 0x4040);
	  अवरोध;
	हाल 192000:
	  snd_emu10k1_ptr_ग_लिखो(emu, A_SPDIF_SAMPLERATE, channel, (पंचांगp & ~0xe0e0) | 0x2020);
	  अवरोध;
	हाल 48000:
	शेष:
	  snd_emu10k1_ptr_ग_लिखो(emu, A_SPDIF_SAMPLERATE, channel, (पंचांगp & ~0xe0e0) | 0x0000);
	  अवरोध;
	पूर्ण
	/* FIXME: Check emu->buffer.size beक्रमe actually writing to it. */
	क्रम(i = 0; i < runसमय->periods; i++) अणु
		table_base[i*2]=runसमय->dma_addr+(i*period_size_bytes);
		table_base[(i*2)+1]=period_size_bytes<<16;
	पूर्ण
 
	snd_emu10k1_ptr20_ग_लिखो(emu, PLAYBACK_LIST_ADDR, channel, emu->p16v_buffer.addr+(8*16*channel));
	snd_emu10k1_ptr20_ग_लिखो(emu, PLAYBACK_LIST_SIZE, channel, (runसमय->periods - 1) << 19);
	snd_emu10k1_ptr20_ग_लिखो(emu, PLAYBACK_LIST_PTR, channel, 0);
	snd_emu10k1_ptr20_ग_लिखो(emu, PLAYBACK_DMA_ADDR, channel, runसमय->dma_addr);
	//snd_emu10k1_ptr20_ग_लिखो(emu, PLAYBACK_PERIOD_SIZE, channel, frames_to_bytes(runसमय, runसमय->period_size)<<16); // buffer size in bytes
	snd_emu10k1_ptr20_ग_लिखो(emu, PLAYBACK_PERIOD_SIZE, channel, 0); // buffer size in bytes
	snd_emu10k1_ptr20_ग_लिखो(emu, PLAYBACK_POINTER, channel, 0);
	snd_emu10k1_ptr20_ग_लिखो(emu, 0x07, channel, 0x0);
	snd_emu10k1_ptr20_ग_लिखो(emu, 0x08, channel, 0);

	वापस 0;
पूर्ण

/* prepare capture callback */
अटल पूर्णांक snd_p16v_pcm_prepare_capture(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक channel = substream->pcm->device - emu->p16v_device_offset;
	u32 पंचांगp;

	/*
	dev_dbg(emu->card->dev, "prepare capture:channel_number=%d, rate=%d, "
	       "format=0x%x, channels=%d, buffer_size=%ld, period_size=%ld, "
	       "frames_to_bytes=%d\n",
	       channel, runसमय->rate, runसमय->क्रमmat, runसमय->channels,
	       runसमय->buffer_size, runसमय->period_size,
	       frames_to_bytes(runसमय, 1));
	*/
	पंचांगp = snd_emu10k1_ptr_पढ़ो(emu, A_SPDIF_SAMPLERATE, channel);
        चयन (runसमय->rate) अणु
	हाल 44100:
	  snd_emu10k1_ptr_ग_लिखो(emu, A_SPDIF_SAMPLERATE, channel, (पंचांगp & ~0x0e00) | 0x0800);
	  अवरोध;
	हाल 96000:
	  snd_emu10k1_ptr_ग_लिखो(emu, A_SPDIF_SAMPLERATE, channel, (पंचांगp & ~0x0e00) | 0x0400);
	  अवरोध;
	हाल 192000:
	  snd_emu10k1_ptr_ग_लिखो(emu, A_SPDIF_SAMPLERATE, channel, (पंचांगp & ~0x0e00) | 0x0200);
	  अवरोध;
	हाल 48000:
	शेष:
	  snd_emu10k1_ptr_ग_लिखो(emu, A_SPDIF_SAMPLERATE, channel, (पंचांगp & ~0x0e00) | 0x0000);
	  अवरोध;
	पूर्ण
	/* FIXME: Check emu->buffer.size beक्रमe actually writing to it. */
	snd_emu10k1_ptr20_ग_लिखो(emu, 0x13, channel, 0);
	snd_emu10k1_ptr20_ग_लिखो(emu, CAPTURE_DMA_ADDR, channel, runसमय->dma_addr);
	snd_emu10k1_ptr20_ग_लिखो(emu, CAPTURE_BUFFER_SIZE, channel, frames_to_bytes(runसमय, runसमय->buffer_size) << 16); // buffer size in bytes
	snd_emu10k1_ptr20_ग_लिखो(emu, CAPTURE_POINTER, channel, 0);
	//snd_emu10k1_ptr20_ग_लिखो(emu, CAPTURE_SOURCE, 0x0, 0x333300e4); /* Select MIC or Line in */
	//snd_emu10k1_ptr20_ग_लिखो(emu, EXTENDED_INT_MASK, 0, snd_emu10k1_ptr20_पढ़ो(emu, EXTENDED_INT_MASK, 0) | (0x110000<<channel));

	वापस 0;
पूर्ण

अटल व्योम snd_p16v_पूर्णांकr_enable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक पूर्णांकrenb)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक enable;

	spin_lock_irqsave(&emu->emu_lock, flags);
	enable = inl(emu->port + INTE2) | पूर्णांकrenb;
	outl(enable, emu->port + INTE2);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

अटल व्योम snd_p16v_पूर्णांकr_disable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक पूर्णांकrenb)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक disable;

	spin_lock_irqsave(&emu->emu_lock, flags);
	disable = inl(emu->port + INTE2) & (~पूर्णांकrenb);
	outl(disable, emu->port + INTE2);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

/* trigger_playback callback */
अटल पूर्णांक snd_p16v_pcm_trigger_playback(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा snd_emu10k1_pcm *epcm;
	पूर्णांक channel;
	पूर्णांक result = 0;
        काष्ठा snd_pcm_substream *s;
	u32 basic = 0;
	u32 पूर्णांकe = 0;
	पूर्णांक running = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		running=1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	शेष:
		running = 0;
		अवरोध;
	पूर्ण
        snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (snd_pcm_substream_chip(s) != emu ||
		    s->stream != SNDRV_PCM_STREAM_PLAYBACK)
			जारी;
		runसमय = s->runसमय;
		epcm = runसमय->निजी_data;
		channel = substream->pcm->device-emu->p16v_device_offset;
		/* dev_dbg(emu->card->dev, "p16v channel=%d\n", channel); */
		epcm->running = running;
		basic |= (0x1<<channel);
		पूर्णांकe |= (INTE2_PLAYBACK_CH_0_LOOP<<channel);
                snd_pcm_trigger_करोne(s, substream);
        पूर्ण
	/* dev_dbg(emu->card->dev, "basic=0x%x, inte=0x%x\n", basic, पूर्णांकe); */

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_p16v_पूर्णांकr_enable(emu, पूर्णांकe);
		snd_emu10k1_ptr20_ग_लिखो(emu, BASIC_INTERRUPT, 0, snd_emu10k1_ptr20_पढ़ो(emu, BASIC_INTERRUPT, 0)| (basic));
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		snd_emu10k1_ptr20_ग_लिखो(emu, BASIC_INTERRUPT, 0, snd_emu10k1_ptr20_पढ़ो(emu, BASIC_INTERRUPT, 0) & ~(basic));
		snd_p16v_पूर्णांकr_disable(emu, पूर्णांकe);
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

/* trigger_capture callback */
अटल पूर्णांक snd_p16v_pcm_trigger_capture(काष्ठा snd_pcm_substream *substream,
                                   पूर्णांक cmd)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	पूर्णांक channel = 0;
	पूर्णांक result = 0;
	u32 पूर्णांकe = INTE2_CAPTURE_CH_0_LOOP | INTE2_CAPTURE_CH_0_HALF_LOOP;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_p16v_पूर्णांकr_enable(emu, पूर्णांकe);
		snd_emu10k1_ptr20_ग_लिखो(emu, BASIC_INTERRUPT, 0, snd_emu10k1_ptr20_पढ़ो(emu, BASIC_INTERRUPT, 0)|(0x100<<channel));
		epcm->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		snd_emu10k1_ptr20_ग_लिखो(emu, BASIC_INTERRUPT, 0, snd_emu10k1_ptr20_पढ़ो(emu, BASIC_INTERRUPT, 0) & ~(0x100<<channel));
		snd_p16v_पूर्णांकr_disable(emu, पूर्णांकe);
		//snd_emu10k1_ptr20_ग_लिखो(emu, EXTENDED_INT_MASK, 0, snd_emu10k1_ptr20_पढ़ो(emu, EXTENDED_INT_MASK, 0) & ~(0x110000<<channel));
		epcm->running = 0;
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

/* poपूर्णांकer_playback callback */
अटल snd_pcm_uframes_t
snd_p16v_pcm_poपूर्णांकer_playback(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	snd_pcm_uframes_t ptr, ptr1, ptr2,ptr3,ptr4 = 0;
	पूर्णांक channel = substream->pcm->device - emu->p16v_device_offset;
	अगर (!epcm->running)
		वापस 0;

	ptr3 = snd_emu10k1_ptr20_पढ़ो(emu, PLAYBACK_LIST_PTR, channel);
	ptr1 = snd_emu10k1_ptr20_पढ़ो(emu, PLAYBACK_POINTER, channel);
	ptr4 = snd_emu10k1_ptr20_पढ़ो(emu, PLAYBACK_LIST_PTR, channel);
	अगर (ptr3 != ptr4) ptr1 = snd_emu10k1_ptr20_पढ़ो(emu, PLAYBACK_POINTER, channel);
	ptr2 = bytes_to_frames(runसमय, ptr1);
	ptr2+= (ptr4 >> 3) * runसमय->period_size;
	ptr=ptr2;
        अगर (ptr >= runसमय->buffer_size)
		ptr -= runसमय->buffer_size;

	वापस ptr;
पूर्ण

/* poपूर्णांकer_capture callback */
अटल snd_pcm_uframes_t
snd_p16v_pcm_poपूर्णांकer_capture(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_emu10k1_pcm *epcm = runसमय->निजी_data;
	snd_pcm_uframes_t ptr, ptr1, ptr2 = 0;
	पूर्णांक channel = 0;

	अगर (!epcm->running)
		वापस 0;

	ptr1 = snd_emu10k1_ptr20_पढ़ो(emu, CAPTURE_POINTER, channel);
	ptr2 = bytes_to_frames(runसमय, ptr1);
	ptr=ptr2;
	अगर (ptr >= runसमय->buffer_size) अणु
		ptr -= runसमय->buffer_size;
		dev_warn(emu->card->dev, "buffer capture limited!\n");
	पूर्ण
	/*
	dev_dbg(emu->card->dev, "ptr1 = 0x%lx, ptr2=0x%lx, ptr=0x%lx, "
	       "buffer_size = 0x%x, period_size = 0x%x, bits=%d, rate=%d\n",
	       ptr1, ptr2, ptr, (पूर्णांक)runसमय->buffer_size,
	       (पूर्णांक)runसमय->period_size, (पूर्णांक)runसमय->frame_bits,
	       (पूर्णांक)runसमय->rate);
	*/
	वापस ptr;
पूर्ण

/* चालकs */
अटल स्थिर काष्ठा snd_pcm_ops snd_p16v_playback_front_ops = अणु
	.खोलो =        snd_p16v_pcm_खोलो_playback_front,
	.बंद =       snd_p16v_pcm_बंद_playback,
	.prepare =     snd_p16v_pcm_prepare_playback,
	.trigger =     snd_p16v_pcm_trigger_playback,
	.poपूर्णांकer =     snd_p16v_pcm_poपूर्णांकer_playback,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_p16v_capture_ops = अणु
	.खोलो =        snd_p16v_pcm_खोलो_capture,
	.बंद =       snd_p16v_pcm_बंद_capture,
	.prepare =     snd_p16v_pcm_prepare_capture,
	.trigger =     snd_p16v_pcm_trigger_capture,
	.poपूर्णांकer =     snd_p16v_pcm_poपूर्णांकer_capture,
पूर्ण;


पूर्णांक snd_p16v_मुक्त(काष्ठा snd_emu10k1 *chip)
अणु
	// release the data
	अगर (chip->p16v_buffer.area) अणु
		snd_dma_मुक्त_pages(&chip->p16v_buffer);
		/*
		dev_dbg(chip->card->dev, "period lables free: %p\n",
			   &chip->p16v_buffer);
		*/
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक snd_p16v_pcm(काष्ठा snd_emu10k1 *emu, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक err;
        पूर्णांक capture=1;
  
	/* dev_dbg(emu->card->dev, "snd_p16v_pcm called. device=%d\n", device); */
	emu->p16v_device_offset = device;

	अगर ((err = snd_pcm_new(emu->card, "p16v", device, 1, capture, &pcm)) < 0)
		वापस err;
  
	pcm->निजी_data = emu;
	// Single playback 8 channel device.
	// Single capture 2 channel device.
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_p16v_playback_front_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_p16v_capture_ops);

	pcm->info_flags = 0;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	म_नकल(pcm->name, "p16v");
	emu->pcm_p16v = pcm;

	क्रम(substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream; 
	    substream; 
	    substream = substream->next) अणु
		snd_pcm_set_managed_buffer(substream, SNDRV_DMA_TYPE_DEV,
					   &emu->pci->dev,
					   (65536 - 64) * 8,
					   (65536 - 64) * 8);
		/*
		dev_dbg(emu->card->dev,
			   "preallocate playback substream: err=%d\n", err);
		*/
	पूर्ण

	क्रम (substream = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream; 
	      substream; 
	      substream = substream->next) अणु
		snd_pcm_set_managed_buffer(substream, SNDRV_DMA_TYPE_DEV,
					   &emu->pci->dev,
					   65536 - 64, 65536 - 64);
		/*
		dev_dbg(emu->card->dev,
			   "preallocate capture substream: err=%d\n", err);
		*/
	पूर्ण
  
	वापस 0;
पूर्ण

अटल पूर्णांक snd_p16v_volume_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
        uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
        uinfo->count = 2;
        uinfo->value.पूर्णांकeger.min = 0;
        uinfo->value.पूर्णांकeger.max = 255;
        वापस 0;
पूर्ण

अटल पूर्णांक snd_p16v_volume_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
        काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	पूर्णांक high_low = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	u32 value;

	value = snd_emu10k1_ptr20_पढ़ो(emu, reg, high_low);
	अगर (high_low) अणु
		ucontrol->value.पूर्णांकeger.value[0] = 0xff - ((value >> 24) & 0xff); /* Left */
		ucontrol->value.पूर्णांकeger.value[1] = 0xff - ((value >> 16) & 0xff); /* Right */
	पूर्ण अन्यथा अणु
		ucontrol->value.पूर्णांकeger.value[0] = 0xff - ((value >> 8) & 0xff); /* Left */
		ucontrol->value.पूर्णांकeger.value[1] = 0xff - ((value >> 0) & 0xff); /* Right */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_p16v_volume_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
        काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	पूर्णांक high_low = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
        u32 value, oval;

	oval = value = snd_emu10k1_ptr20_पढ़ो(emu, reg, 0);
	अगर (high_low == 1) अणु
		value &= 0xffff;
		value |= ((0xff - ucontrol->value.पूर्णांकeger.value[0]) << 24) |
			((0xff - ucontrol->value.पूर्णांकeger.value[1]) << 16);
	पूर्ण अन्यथा अणु
		value &= 0xffff0000;
		value |= ((0xff - ucontrol->value.पूर्णांकeger.value[0]) << 8) |
			((0xff - ucontrol->value.पूर्णांकeger.value[1]) );
	पूर्ण
	अगर (value != oval) अणु
		snd_emu10k1_ptr20_ग_लिखो(emu, reg, 0, value);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_p16v_capture_source_info(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[8] = अणु
		"SPDIF", "I2S", "SRC48", "SRCMulti_SPDIF", "SRCMulti_I2S",
		"CDIF", "FX", "AC97"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 8, texts);
पूर्ण

अटल पूर्णांक snd_p16v_capture_source_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = emu->p16v_capture_source;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_p16v_capture_source_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change = 0;
	u32 mask;
	u32 source;

	val = ucontrol->value.क्रमागतerated.item[0] ;
	अगर (val > 7)
		वापस -EINVAL;
	change = (emu->p16v_capture_source != val);
	अगर (change) अणु
		emu->p16v_capture_source = val;
		source = (val << 28) | (val << 24) | (val << 20) | (val << 16);
		mask = snd_emu10k1_ptr20_पढ़ो(emu, BASIC_INTERRUPT, 0) & 0xffff;
		snd_emu10k1_ptr20_ग_लिखो(emu, BASIC_INTERRUPT, 0, source | mask);
	पूर्ण
        वापस change;
पूर्ण

अटल पूर्णांक snd_p16v_capture_channel_info(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु "0", "1", "2", "3", पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 4, texts);
पूर्ण

अटल पूर्णांक snd_p16v_capture_channel_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = emu->p16v_capture_channel;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_p16v_capture_channel_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change = 0;
	u32 पंचांगp;

	val = ucontrol->value.क्रमागतerated.item[0] ;
	अगर (val > 3)
		वापस -EINVAL;
	change = (emu->p16v_capture_channel != val);
	अगर (change) अणु
		emu->p16v_capture_channel = val;
		पंचांगp = snd_emu10k1_ptr20_पढ़ो(emu, CAPTURE_P16V_SOURCE, 0) & 0xfffc;
		snd_emu10k1_ptr20_ग_लिखो(emu, CAPTURE_P16V_SOURCE, 0, पंचांगp | val);
	पूर्ण
        वापस change;
पूर्ण
अटल स्थिर DECLARE_TLV_DB_SCALE(snd_p16v_db_scale1, -5175, 25, 1);

#घोषणा P16V_VOL(xname,xreg,xhl) अणु \
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
        .access = SNDRV_CTL_ELEM_ACCESS_READWRITE |             \
                  SNDRV_CTL_ELEM_ACCESS_TLV_READ,               \
	.info = snd_p16v_volume_info, \
	.get = snd_p16v_volume_get, \
	.put = snd_p16v_volume_put, \
	.tlv = अणु .p = snd_p16v_db_scale1 पूर्ण,	\
	.निजी_value = ((xreg) | ((xhl) << 8)) \
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new p16v_mixer_controls[] = अणु
	P16V_VOL("HD Analog Front Playback Volume", PLAYBACK_VOLUME_MIXER9, 0),
	P16V_VOL("HD Analog Rear Playback Volume", PLAYBACK_VOLUME_MIXER10, 1),
	P16V_VOL("HD Analog Center/LFE Playback Volume", PLAYBACK_VOLUME_MIXER9, 1),
	P16V_VOL("HD Analog Side Playback Volume", PLAYBACK_VOLUME_MIXER10, 0),
	P16V_VOL("HD SPDIF Front Playback Volume", PLAYBACK_VOLUME_MIXER7, 0),
	P16V_VOL("HD SPDIF Rear Playback Volume", PLAYBACK_VOLUME_MIXER8, 1),
	P16V_VOL("HD SPDIF Center/LFE Playback Volume", PLAYBACK_VOLUME_MIXER7, 1),
	P16V_VOL("HD SPDIF Side Playback Volume", PLAYBACK_VOLUME_MIXER8, 0),
	अणु
		.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
		.name =		"HD source Capture",
		.info =		snd_p16v_capture_source_info,
		.get =		snd_p16v_capture_source_get,
		.put =		snd_p16v_capture_source_put
	पूर्ण,
	अणु
		.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
		.name =		"HD channel Capture",
		.info =		snd_p16v_capture_channel_info,
		.get =		snd_p16v_capture_channel_get,
		.put =		snd_p16v_capture_channel_put
	पूर्ण,
पूर्ण;


पूर्णांक snd_p16v_mixer(काष्ठा snd_emu10k1 *emu)
अणु
	पूर्णांक i, err;
        काष्ठा snd_card *card = emu->card;

	क्रम (i = 0; i < ARRAY_SIZE(p16v_mixer_controls); i++) अणु
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&p16v_mixer_controls[i],
							  emu))) < 0)
			वापस err;
	पूर्ण
        वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

#घोषणा NUM_CHS	1	/* up to 4, but only first channel is used */

पूर्णांक snd_p16v_alloc_pm_buffer(काष्ठा snd_emu10k1 *emu)
अणु
	emu->p16v_saved = vदो_स्मृति(array_size(NUM_CHS * 4, 0x80));
	अगर (! emu->p16v_saved)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम snd_p16v_मुक्त_pm_buffer(काष्ठा snd_emu10k1 *emu)
अणु
	vमुक्त(emu->p16v_saved);
पूर्ण

व्योम snd_p16v_suspend(काष्ठा snd_emu10k1 *emu)
अणु
	पूर्णांक i, ch;
	अचिन्हित पूर्णांक *val;

	val = emu->p16v_saved;
	क्रम (ch = 0; ch < NUM_CHS; ch++)
		क्रम (i = 0; i < 0x80; i++, val++)
			*val = snd_emu10k1_ptr20_पढ़ो(emu, i, ch);
पूर्ण

व्योम snd_p16v_resume(काष्ठा snd_emu10k1 *emu)
अणु
	पूर्णांक i, ch;
	अचिन्हित पूर्णांक *val;

	val = emu->p16v_saved;
	क्रम (ch = 0; ch < NUM_CHS; ch++)
		क्रम (i = 0; i < 0x80; i++, val++)
			snd_emu10k1_ptr20_ग_लिखो(emu, i, ch, *val);
पूर्ण
#पूर्ण_अगर
