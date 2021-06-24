<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Francisco Moraes <fmoraes@nc.rr.com>
 *  Driver EMU10K1X chips
 *
 *  Parts of this code were adapted from audigyls.c driver which is
 *  Copyright (c) by James Courtier-Dutton <James@superbug.demon.co.uk>
 *
 *  BUGS:
 *    --
 *
 *  TODO:
 *
 *  Chips (SB0200 model):
 *    - EMU10K1X-DBQ
 *    - STAC 9708T
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/info.h>
#समावेश <sound/rawmidi.h>

MODULE_AUTHOR("Francisco Moraes <fmoraes@nc.rr.com>");
MODULE_DESCRIPTION("EMU10K1X");
MODULE_LICENSE("GPL");

// module parameters (see "Module Parameters")
अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for the EMU10K1X soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for the EMU10K1X soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable the EMU10K1X soundcard.");


// some definitions were borrowed from emu10k1 driver as they seem to be the same
/************************************************************************************************/
/* PCI function 0 रेजिस्टरs, address = <val> + PCIBASE0						*/
/************************************************************************************************/

#घोषणा PTR			0x00		/* Indexed रेजिस्टर set poपूर्णांकer रेजिस्टर	*/
						/* NOTE: The CHANNELNUM and ADDRESS words can	*/
						/* be modअगरied independently of each other.	*/

#घोषणा DATA			0x04		/* Indexed रेजिस्टर set data रेजिस्टर		*/

#घोषणा IPR			0x08		/* Global पूर्णांकerrupt pending रेजिस्टर		*/
						/* Clear pending पूर्णांकerrupts by writing a 1 to	*/
						/* the relevant bits and zero to the other bits	*/
#घोषणा IPR_MIDITRANSBUFEMPTY   0x00000001	/* MIDI UART transmit buffer empty		*/
#घोषणा IPR_MIसूचीECVBUFEMPTY    0x00000002	/* MIDI UART receive buffer empty		*/
#घोषणा IPR_CH_0_LOOP           0x00000800      /* Channel 0 loop                               */
#घोषणा IPR_CH_0_HALF_LOOP      0x00000100      /* Channel 0 half loop                          */
#घोषणा IPR_CAP_0_LOOP          0x00080000      /* Channel capture loop                         */
#घोषणा IPR_CAP_0_HALF_LOOP     0x00010000      /* Channel capture half loop                    */

#घोषणा INTE			0x0c		/* Interrupt enable रेजिस्टर			*/
#घोषणा INTE_MIDITXENABLE       0x00000001	/* Enable MIDI transmit-buffer-empty पूर्णांकerrupts	*/
#घोषणा INTE_MIसूचीXENABLE       0x00000002	/* Enable MIDI receive-buffer-empty पूर्णांकerrupts	*/
#घोषणा INTE_CH_0_LOOP          0x00000800      /* Channel 0 loop                               */
#घोषणा INTE_CH_0_HALF_LOOP     0x00000100      /* Channel 0 half loop                          */
#घोषणा INTE_CAP_0_LOOP         0x00080000      /* Channel capture loop                         */
#घोषणा INTE_CAP_0_HALF_LOOP    0x00010000      /* Channel capture half loop                    */

#घोषणा HCFG			0x14		/* Hardware config रेजिस्टर			*/

#घोषणा HCFG_LOCKSOUNDCACHE	0x00000008	/* 1 = Cancel busपंचांगaster accesses to soundcache */
						/* NOTE: This should generally never be used.  	*/
#घोषणा HCFG_AUDIOENABLE	0x00000001	/* 0 = CODECs transmit zero-valued samples	*/
						/* Should be set to 1 when the EMU10K1 is	*/
						/* completely initialized.			*/
#घोषणा GPIO			0x18		/* Defaults: 00001080-Analog, 00001000-SPDIF.   */


#घोषणा AC97DATA		0x1c		/* AC97 रेजिस्टर set data रेजिस्टर (16 bit)	*/

#घोषणा AC97ADDRESS		0x1e		/* AC97 रेजिस्टर set address रेजिस्टर (8 bit)	*/

/********************************************************************************************************/
/* Emu10k1x poपूर्णांकer-offset रेजिस्टर set, accessed through the PTR and DATA रेजिस्टरs			*/
/********************************************************************************************************/
#घोषणा PLAYBACK_LIST_ADDR	0x00		/* Base DMA address of a list of poपूर्णांकers to each period/size */
						/* One list entry: 4 bytes क्रम DMA address, 
						 * 4 bytes क्रम period_size << 16.
						 * One list entry is 8 bytes दीर्घ.
						 * One list entry क्रम each period in the buffer.
						 */
#घोषणा PLAYBACK_LIST_SIZE	0x01		/* Size of list in bytes << 16. E.g. 8 periods -> 0x00380000  */
#घोषणा PLAYBACK_LIST_PTR	0x02		/* Poपूर्णांकer to the current period being played */
#घोषणा PLAYBACK_DMA_ADDR	0x04		/* Playback DMA address */
#घोषणा PLAYBACK_PERIOD_SIZE	0x05		/* Playback period size */
#घोषणा PLAYBACK_POINTER	0x06		/* Playback period poपूर्णांकer. Sample currently in DAC */
#घोषणा PLAYBACK_UNKNOWN1       0x07
#घोषणा PLAYBACK_UNKNOWN2       0x08

/* Only one capture channel supported */
#घोषणा CAPTURE_DMA_ADDR	0x10		/* Capture DMA address */
#घोषणा CAPTURE_BUFFER_SIZE	0x11		/* Capture buffer size */
#घोषणा CAPTURE_POINTER		0x12		/* Capture buffer poपूर्णांकer. Sample currently in ADC */
#घोषणा CAPTURE_UNKNOWN         0x13

/* From 0x20 - 0x3f, last samples played on each channel */

#घोषणा TRIGGER_CHANNEL         0x40            /* Trigger channel playback                     */
#घोषणा TRIGGER_CHANNEL_0       0x00000001      /* Trigger channel 0                            */
#घोषणा TRIGGER_CHANNEL_1       0x00000002      /* Trigger channel 1                            */
#घोषणा TRIGGER_CHANNEL_2       0x00000004      /* Trigger channel 2                            */
#घोषणा TRIGGER_CAPTURE         0x00000100      /* Trigger capture channel                      */

#घोषणा ROUTING                 0x41            /* Setup sound routing ?                        */
#घोषणा ROUTING_FRONT_LEFT      0x00000001
#घोषणा ROUTING_FRONT_RIGHT     0x00000002
#घोषणा ROUTING_REAR_LEFT       0x00000004
#घोषणा ROUTING_REAR_RIGHT      0x00000008
#घोषणा ROUTING_CENTER_LFE      0x00010000

#घोषणा SPCS0			0x42		/* SPDIF output Channel Status 0 रेजिस्टर	*/

#घोषणा SPCS1			0x43		/* SPDIF output Channel Status 1 रेजिस्टर	*/

#घोषणा SPCS2			0x44		/* SPDIF output Channel Status 2 रेजिस्टर	*/

#घोषणा SPCS_CLKACCYMASK	0x30000000	/* Clock accuracy				*/
#घोषणा SPCS_CLKACCY_1000PPM	0x00000000	/* 1000 parts per million			*/
#घोषणा SPCS_CLKACCY_50PPM	0x10000000	/* 50 parts per million				*/
#घोषणा SPCS_CLKACCY_VARIABLE	0x20000000	/* Variable accuracy				*/
#घोषणा SPCS_SAMPLERATEMASK	0x0f000000	/* Sample rate					*/
#घोषणा SPCS_SAMPLERATE_44	0x00000000	/* 44.1kHz sample rate				*/
#घोषणा SPCS_SAMPLERATE_48	0x02000000	/* 48kHz sample rate				*/
#घोषणा SPCS_SAMPLERATE_32	0x03000000	/* 32kHz sample rate				*/
#घोषणा SPCS_CHANNELNUMMASK	0x00f00000	/* Channel number				*/
#घोषणा SPCS_CHANNELNUM_UNSPEC	0x00000000	/* Unspecअगरied channel number			*/
#घोषणा SPCS_CHANNELNUM_LEFT	0x00100000	/* Left channel					*/
#घोषणा SPCS_CHANNELNUM_RIGHT	0x00200000	/* Right channel				*/
#घोषणा SPCS_SOURCENUMMASK	0x000f0000	/* Source number				*/
#घोषणा SPCS_SOURCENUM_UNSPEC	0x00000000	/* Unspecअगरied source number			*/
#घोषणा SPCS_GENERATIONSTATUS	0x00008000	/* Originality flag (see IEC-958 spec)		*/
#घोषणा SPCS_CATEGORYCODEMASK	0x00007f00	/* Category code (see IEC-958 spec)		*/
#घोषणा SPCS_MODEMASK		0x000000c0	/* Mode (see IEC-958 spec)			*/
#घोषणा SPCS_EMPHASISMASK	0x00000038	/* Emphasis					*/
#घोषणा SPCS_EMPHASIS_NONE	0x00000000	/* No emphasis					*/
#घोषणा SPCS_EMPHASIS_50_15	0x00000008	/* 50/15 usec 2 channel				*/
#घोषणा SPCS_COPYRIGHT		0x00000004	/* Copyright निश्चितed flag -- करो not modअगरy	*/
#घोषणा SPCS_NOTAUDIODATA	0x00000002	/* 0 = Digital audio, 1 = not audio		*/
#घोषणा SPCS_PROFESSIONAL	0x00000001	/* 0 = Consumer (IEC-958), 1 = pro (AES3-1992)	*/

#घोषणा SPDIF_SELECT		0x45		/* Enables SPDIF or Analogue outमाला_दो 0-Analogue, 0x700-SPDIF */

/* This is the MPU port on the card                      					*/
#घोषणा MUDATA		0x47
#घोषणा MUCMD		0x48
#घोषणा MUSTAT		MUCMD

/* From 0x50 - 0x5f, last samples captured */

/*
 * The hardware has 3 channels क्रम playback and 1 क्रम capture.
 *  - channel 0 is the front channel
 *  - channel 1 is the rear channel
 *  - channel 2 is the center/lfe channel
 * Volume is controlled by the AC97 क्रम the front and rear channels by
 * the PCM Playback Volume, Sigmatel Surround Playback Volume and 
 * Surround Playback Volume. The Sigmatel 4-Speaker Stereo चयन affects
 * the front/rear channel mixing in the REAR OUT jack. When using the
 * 4-Speaker Stereo, both front and rear channels will be mixed in the
 * REAR OUT.
 * The center/lfe channel has no volume control and cannot be muted during
 * playback.
 */

काष्ठा emu10k1x_voice अणु
	काष्ठा emu10k1x *emu;
	पूर्णांक number;
	पूर्णांक use;
  
	काष्ठा emu10k1x_pcm *epcm;
पूर्ण;

काष्ठा emu10k1x_pcm अणु
	काष्ठा emu10k1x *emu;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा emu10k1x_voice *voice;
	अचिन्हित लघु running;
पूर्ण;

काष्ठा emu10k1x_midi अणु
	काष्ठा emu10k1x *emu;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *substream_input;
	काष्ठा snd_rawmidi_substream *substream_output;
	अचिन्हित पूर्णांक midi_mode;
	spinlock_t input_lock;
	spinlock_t output_lock;
	spinlock_t खोलो_lock;
	पूर्णांक tx_enable, rx_enable;
	पूर्णांक port;
	पूर्णांक ipr_tx, ipr_rx;
	व्योम (*पूर्णांकerrupt)(काष्ठा emu10k1x *emu, अचिन्हित पूर्णांक status);
पूर्ण;

// definition of the chip-specअगरic record
काष्ठा emu10k1x अणु
	काष्ठा snd_card *card;
	काष्ठा pci_dev *pci;

	अचिन्हित दीर्घ port;
	काष्ठा resource *res_port;
	पूर्णांक irq;

	अचिन्हित अक्षर revision;		/* chip revision */
	अचिन्हित पूर्णांक serial;            /* serial number */
	अचिन्हित लघु model;		/* subप्रणाली id */

	spinlock_t emu_lock;
	spinlock_t voice_lock;

	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_pcm *pcm;

	काष्ठा emu10k1x_voice voices[3];
	काष्ठा emu10k1x_voice capture_voice;
	u32 spdअगर_bits[3]; // SPDIF out setup

	काष्ठा snd_dma_buffer dma_buffer;

	काष्ठा emu10k1x_midi midi;
पूर्ण;

/* hardware definition */
अटल स्थिर काष्ठा snd_pcm_hardware snd_emu10k1x_playback_hw = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | 
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_48000,
	.rate_min =		48000,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(32*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(16*1024),
	.periods_min =		2,
	.periods_max =		8,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_emu10k1x_capture_hw = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | 
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_48000,
	.rate_min =		48000,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(32*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(16*1024),
	.periods_min =		2,
	.periods_max =		2,
	.fअगरo_size =		0,
पूर्ण;

अटल अचिन्हित पूर्णांक snd_emu10k1x_ptr_पढ़ो(काष्ठा emu10k1x * emu, 
					  अचिन्हित पूर्णांक reg, 
					  अचिन्हित पूर्णांक chn)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक regptr, val;
  
	regptr = (reg << 16) | chn;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(regptr, emu->port + PTR);
	val = inl(emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
	वापस val;
पूर्ण

अटल व्योम snd_emu10k1x_ptr_ग_लिखो(काष्ठा emu10k1x *emu, 
				   अचिन्हित पूर्णांक reg, 
				   अचिन्हित पूर्णांक chn, 
				   अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक regptr;
	अचिन्हित दीर्घ flags;

	regptr = (reg << 16) | chn;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(regptr, emu->port + PTR);
	outl(data, emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

अटल व्योम snd_emu10k1x_पूर्णांकr_enable(काष्ठा emu10k1x *emu, अचिन्हित पूर्णांक पूर्णांकrenb)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पूर्णांकr_enable;

	spin_lock_irqsave(&emu->emu_lock, flags);
	पूर्णांकr_enable = inl(emu->port + INTE) | पूर्णांकrenb;
	outl(पूर्णांकr_enable, emu->port + INTE);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

अटल व्योम snd_emu10k1x_पूर्णांकr_disable(काष्ठा emu10k1x *emu, अचिन्हित पूर्णांक पूर्णांकrenb)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पूर्णांकr_enable;

	spin_lock_irqsave(&emu->emu_lock, flags);
	पूर्णांकr_enable = inl(emu->port + INTE) & ~पूर्णांकrenb;
	outl(पूर्णांकr_enable, emu->port + INTE);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

अटल व्योम snd_emu10k1x_gpio_ग_लिखो(काष्ठा emu10k1x *emu, अचिन्हित पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(value, emu->port + GPIO);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

अटल व्योम snd_emu10k1x_pcm_मुक्त_substream(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	kमुक्त(runसमय->निजी_data);
पूर्ण

अटल व्योम snd_emu10k1x_pcm_पूर्णांकerrupt(काष्ठा emu10k1x *emu, काष्ठा emu10k1x_voice *voice)
अणु
	काष्ठा emu10k1x_pcm *epcm;

	अगर ((epcm = voice->epcm) == शून्य)
		वापस;
	अगर (epcm->substream == शून्य)
		वापस;
#अगर 0
	dev_info(emu->card->dev,
		 "IRQ: position = 0x%x, period = 0x%x, size = 0x%x\n",
		   epcm->substream->ops->poपूर्णांकer(epcm->substream),
		   snd_pcm_lib_period_bytes(epcm->substream),
		   snd_pcm_lib_buffer_bytes(epcm->substream));
#पूर्ण_अगर
	snd_pcm_period_elapsed(epcm->substream);
पूर्ण

/* खोलो callback */
अटल पूर्णांक snd_emu10k1x_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा emu10k1x *chip = snd_pcm_substream_chip(substream);
	काष्ठा emu10k1x_pcm *epcm;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS)) < 0) अणु
		वापस err;
	पूर्ण
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 64)) < 0)
                वापस err;

	epcm = kzalloc(माप(*epcm), GFP_KERNEL);
	अगर (epcm == शून्य)
		वापस -ENOMEM;
	epcm->emu = chip;
	epcm->substream = substream;
  
	runसमय->निजी_data = epcm;
	runसमय->निजी_मुक्त = snd_emu10k1x_pcm_मुक्त_substream;
  
	runसमय->hw = snd_emu10k1x_playback_hw;

	वापस 0;
पूर्ण

/* बंद callback */
अटल पूर्णांक snd_emu10k1x_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

/* hw_params callback */
अटल पूर्णांक snd_emu10k1x_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा emu10k1x_pcm *epcm = runसमय->निजी_data;

	अगर (! epcm->voice) अणु
		epcm->voice = &epcm->emu->voices[substream->pcm->device];
		epcm->voice->use = 1;
		epcm->voice->epcm = epcm;
	पूर्ण

	वापस 0;
पूर्ण

/* hw_मुक्त callback */
अटल पूर्णांक snd_emu10k1x_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा emu10k1x_pcm *epcm;

	अगर (runसमय->निजी_data == शून्य)
		वापस 0;
	
	epcm = runसमय->निजी_data;

	अगर (epcm->voice) अणु
		epcm->voice->use = 0;
		epcm->voice->epcm = शून्य;
		epcm->voice = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/* prepare callback */
अटल पूर्णांक snd_emu10k1x_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा emu10k1x *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा emu10k1x_pcm *epcm = runसमय->निजी_data;
	पूर्णांक voice = epcm->voice->number;
	u32 *table_base = (u32 *)(emu->dma_buffer.area+1024*voice);
	u32 period_size_bytes = frames_to_bytes(runसमय, runसमय->period_size);
	पूर्णांक i;
	
	क्रम(i = 0; i < runसमय->periods; i++) अणु
		*table_base++=runसमय->dma_addr+(i*period_size_bytes);
		*table_base++=period_size_bytes<<16;
	पूर्ण

	snd_emu10k1x_ptr_ग_लिखो(emu, PLAYBACK_LIST_ADDR, voice, emu->dma_buffer.addr+1024*voice);
	snd_emu10k1x_ptr_ग_लिखो(emu, PLAYBACK_LIST_SIZE, voice, (runसमय->periods - 1) << 19);
	snd_emu10k1x_ptr_ग_लिखो(emu, PLAYBACK_LIST_PTR, voice, 0);
	snd_emu10k1x_ptr_ग_लिखो(emu, PLAYBACK_POINTER, voice, 0);
	snd_emu10k1x_ptr_ग_लिखो(emu, PLAYBACK_UNKNOWN1, voice, 0);
	snd_emu10k1x_ptr_ग_लिखो(emu, PLAYBACK_UNKNOWN2, voice, 0);
	snd_emu10k1x_ptr_ग_लिखो(emu, PLAYBACK_DMA_ADDR, voice, runसमय->dma_addr);

	snd_emu10k1x_ptr_ग_लिखो(emu, PLAYBACK_PERIOD_SIZE, voice, frames_to_bytes(runसमय, runसमय->period_size)<<16);

	वापस 0;
पूर्ण

/* trigger callback */
अटल पूर्णांक snd_emu10k1x_pcm_trigger(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd)
अणु
	काष्ठा emu10k1x *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा emu10k1x_pcm *epcm = runसमय->निजी_data;
	पूर्णांक channel = epcm->voice->number;
	पूर्णांक result = 0;

	/*
	dev_dbg(emu->card->dev,
		"trigger - emu10k1x = 0x%x, cmd = %i, pointer = %d\n",
		(पूर्णांक)emu, cmd, (पूर्णांक)substream->ops->poपूर्णांकer(substream));
	*/

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर(runसमय->periods == 2)
			snd_emu10k1x_पूर्णांकr_enable(emu, (INTE_CH_0_LOOP | INTE_CH_0_HALF_LOOP) << channel);
		अन्यथा
			snd_emu10k1x_पूर्णांकr_enable(emu, INTE_CH_0_LOOP << channel);
		epcm->running = 1;
		snd_emu10k1x_ptr_ग_लिखो(emu, TRIGGER_CHANNEL, 0, snd_emu10k1x_ptr_पढ़ो(emu, TRIGGER_CHANNEL, 0)|(TRIGGER_CHANNEL_0<<channel));
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		epcm->running = 0;
		snd_emu10k1x_पूर्णांकr_disable(emu, (INTE_CH_0_LOOP | INTE_CH_0_HALF_LOOP) << channel);
		snd_emu10k1x_ptr_ग_लिखो(emu, TRIGGER_CHANNEL, 0, snd_emu10k1x_ptr_पढ़ो(emu, TRIGGER_CHANNEL, 0) & ~(TRIGGER_CHANNEL_0<<channel));
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

/* poपूर्णांकer callback */
अटल snd_pcm_uframes_t
snd_emu10k1x_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा emu10k1x *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा emu10k1x_pcm *epcm = runसमय->निजी_data;
	पूर्णांक channel = epcm->voice->number;
	snd_pcm_uframes_t ptr = 0, ptr1 = 0, ptr2= 0,ptr3 = 0,ptr4 = 0;

	अगर (!epcm->running)
		वापस 0;

	ptr3 = snd_emu10k1x_ptr_पढ़ो(emu, PLAYBACK_LIST_PTR, channel);
	ptr1 = snd_emu10k1x_ptr_पढ़ो(emu, PLAYBACK_POINTER, channel);
	ptr4 = snd_emu10k1x_ptr_पढ़ो(emu, PLAYBACK_LIST_PTR, channel);

	अगर(ptr4 == 0 && ptr1 == frames_to_bytes(runसमय, runसमय->buffer_size))
		वापस 0;
	
	अगर (ptr3 != ptr4) 
		ptr1 = snd_emu10k1x_ptr_पढ़ो(emu, PLAYBACK_POINTER, channel);
	ptr2 = bytes_to_frames(runसमय, ptr1);
	ptr2 += (ptr4 >> 3) * runसमय->period_size;
	ptr = ptr2;

	अगर (ptr >= runसमय->buffer_size)
		ptr -= runसमय->buffer_size;

	वापस ptr;
पूर्ण

/* चालकs */
अटल स्थिर काष्ठा snd_pcm_ops snd_emu10k1x_playback_ops = अणु
	.खोलो =        snd_emu10k1x_playback_खोलो,
	.बंद =       snd_emu10k1x_playback_बंद,
	.hw_params =   snd_emu10k1x_pcm_hw_params,
	.hw_मुक्त =     snd_emu10k1x_pcm_hw_मुक्त,
	.prepare =     snd_emu10k1x_pcm_prepare,
	.trigger =     snd_emu10k1x_pcm_trigger,
	.poपूर्णांकer =     snd_emu10k1x_pcm_poपूर्णांकer,
पूर्ण;

/* खोलो_capture callback */
अटल पूर्णांक snd_emu10k1x_pcm_खोलो_capture(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा emu10k1x *chip = snd_pcm_substream_chip(substream);
	काष्ठा emu10k1x_pcm *epcm;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
                वापस err;
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 64)) < 0)
                वापस err;

	epcm = kzalloc(माप(*epcm), GFP_KERNEL);
	अगर (epcm == शून्य)
		वापस -ENOMEM;

	epcm->emu = chip;
	epcm->substream = substream;

	runसमय->निजी_data = epcm;
	runसमय->निजी_मुक्त = snd_emu10k1x_pcm_मुक्त_substream;

	runसमय->hw = snd_emu10k1x_capture_hw;

	वापस 0;
पूर्ण

/* बंद callback */
अटल पूर्णांक snd_emu10k1x_pcm_बंद_capture(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

/* hw_params callback */
अटल पूर्णांक snd_emu10k1x_pcm_hw_params_capture(काष्ठा snd_pcm_substream *substream,
					      काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा emu10k1x_pcm *epcm = runसमय->निजी_data;

	अगर (! epcm->voice) अणु
		अगर (epcm->emu->capture_voice.use)
			वापस -EBUSY;
		epcm->voice = &epcm->emu->capture_voice;
		epcm->voice->epcm = epcm;
		epcm->voice->use = 1;
	पूर्ण

	वापस 0;
पूर्ण

/* hw_मुक्त callback */
अटल पूर्णांक snd_emu10k1x_pcm_hw_मुक्त_capture(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	काष्ठा emu10k1x_pcm *epcm;

	अगर (runसमय->निजी_data == शून्य)
		वापस 0;
	epcm = runसमय->निजी_data;

	अगर (epcm->voice) अणु
		epcm->voice->use = 0;
		epcm->voice->epcm = शून्य;
		epcm->voice = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/* prepare capture callback */
अटल पूर्णांक snd_emu10k1x_pcm_prepare_capture(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा emu10k1x *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_emu10k1x_ptr_ग_लिखो(emu, CAPTURE_DMA_ADDR, 0, runसमय->dma_addr);
	snd_emu10k1x_ptr_ग_लिखो(emu, CAPTURE_BUFFER_SIZE, 0, frames_to_bytes(runसमय, runसमय->buffer_size)<<16); // buffer size in bytes
	snd_emu10k1x_ptr_ग_लिखो(emu, CAPTURE_POINTER, 0, 0);
	snd_emu10k1x_ptr_ग_लिखो(emu, CAPTURE_UNKNOWN, 0, 0);

	वापस 0;
पूर्ण

/* trigger_capture callback */
अटल पूर्णांक snd_emu10k1x_pcm_trigger_capture(काष्ठा snd_pcm_substream *substream,
					    पूर्णांक cmd)
अणु
	काष्ठा emu10k1x *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा emu10k1x_pcm *epcm = runसमय->निजी_data;
	पूर्णांक result = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_emu10k1x_पूर्णांकr_enable(emu, INTE_CAP_0_LOOP | 
					 INTE_CAP_0_HALF_LOOP);
		snd_emu10k1x_ptr_ग_लिखो(emu, TRIGGER_CHANNEL, 0, snd_emu10k1x_ptr_पढ़ो(emu, TRIGGER_CHANNEL, 0)|TRIGGER_CAPTURE);
		epcm->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		epcm->running = 0;
		snd_emu10k1x_पूर्णांकr_disable(emu, INTE_CAP_0_LOOP | 
					  INTE_CAP_0_HALF_LOOP);
		snd_emu10k1x_ptr_ग_लिखो(emu, TRIGGER_CHANNEL, 0, snd_emu10k1x_ptr_पढ़ो(emu, TRIGGER_CHANNEL, 0) & ~(TRIGGER_CAPTURE));
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

/* poपूर्णांकer_capture callback */
अटल snd_pcm_uframes_t
snd_emu10k1x_pcm_poपूर्णांकer_capture(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा emu10k1x *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा emu10k1x_pcm *epcm = runसमय->निजी_data;
	snd_pcm_uframes_t ptr;

	अगर (!epcm->running)
		वापस 0;

	ptr = bytes_to_frames(runसमय, snd_emu10k1x_ptr_पढ़ो(emu, CAPTURE_POINTER, 0));
	अगर (ptr >= runसमय->buffer_size)
		ptr -= runसमय->buffer_size;

	वापस ptr;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_emu10k1x_capture_ops = अणु
	.खोलो =        snd_emu10k1x_pcm_खोलो_capture,
	.बंद =       snd_emu10k1x_pcm_बंद_capture,
	.hw_params =   snd_emu10k1x_pcm_hw_params_capture,
	.hw_मुक्त =     snd_emu10k1x_pcm_hw_मुक्त_capture,
	.prepare =     snd_emu10k1x_pcm_prepare_capture,
	.trigger =     snd_emu10k1x_pcm_trigger_capture,
	.poपूर्णांकer =     snd_emu10k1x_pcm_poपूर्णांकer_capture,
पूर्ण;

अटल अचिन्हित लघु snd_emu10k1x_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
					     अचिन्हित लघु reg)
अणु
	काष्ठा emu10k1x *emu = ac97->निजी_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु val;
  
	spin_lock_irqsave(&emu->emu_lock, flags);
	outb(reg, emu->port + AC97ADDRESS);
	val = inw(emu->port + AC97DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
	वापस val;
पूर्ण

अटल व्योम snd_emu10k1x_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97,
				    अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	काष्ठा emu10k1x *emu = ac97->निजी_data;
	अचिन्हित दीर्घ flags;
  
	spin_lock_irqsave(&emu->emu_lock, flags);
	outb(reg, emu->port + AC97ADDRESS);
	outw(val, emu->port + AC97DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

अटल पूर्णांक snd_emu10k1x_ac97(काष्ठा emu10k1x *chip)
अणु
	काष्ठा snd_ac97_bus *pbus;
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_emu10k1x_ac97_ग_लिखो,
		.पढ़ो = snd_emu10k1x_ac97_पढ़ो,
	पूर्ण;
  
	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, शून्य, &pbus)) < 0)
		वापस err;
	pbus->no_vra = 1; /* we करोn't need VRA */

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	ac97.scaps = AC97_SCAP_NO_SPDIF;
	वापस snd_ac97_mixer(pbus, &ac97, &chip->ac97);
पूर्ण

अटल पूर्णांक snd_emu10k1x_मुक्त(काष्ठा emu10k1x *chip)
अणु
	snd_emu10k1x_ptr_ग_लिखो(chip, TRIGGER_CHANNEL, 0, 0);
	// disable पूर्णांकerrupts
	outl(0, chip->port + INTE);
	// disable audio
	outl(HCFG_LOCKSOUNDCACHE, chip->port + HCFG);

	/* release the irq */
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);

	// release the i/o port
	release_and_मुक्त_resource(chip->res_port);

	// release the DMA
	अगर (chip->dma_buffer.area) अणु
		snd_dma_मुक्त_pages(&chip->dma_buffer);
	पूर्ण

	pci_disable_device(chip->pci);

	// release the data
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1x_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा emu10k1x *chip = device->device_data;
	वापस snd_emu10k1x_मुक्त(chip);
पूर्ण

अटल irqवापस_t snd_emu10k1x_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक status;

	काष्ठा emu10k1x *chip = dev_id;
	काष्ठा emu10k1x_voice *pvoice = chip->voices;
	पूर्णांक i;
	पूर्णांक mask;

	status = inl(chip->port + IPR);

	अगर (! status)
		वापस IRQ_NONE;

	// capture पूर्णांकerrupt
	अगर (status & (IPR_CAP_0_LOOP | IPR_CAP_0_HALF_LOOP)) अणु
		काष्ठा emu10k1x_voice *cap_voice = &chip->capture_voice;
		अगर (cap_voice->use)
			snd_emu10k1x_pcm_पूर्णांकerrupt(chip, cap_voice);
		अन्यथा
			snd_emu10k1x_पूर्णांकr_disable(chip, 
						  INTE_CAP_0_LOOP |
						  INTE_CAP_0_HALF_LOOP);
	पूर्ण
		
	mask = IPR_CH_0_LOOP|IPR_CH_0_HALF_LOOP;
	क्रम (i = 0; i < 3; i++) अणु
		अगर (status & mask) अणु
			अगर (pvoice->use)
				snd_emu10k1x_pcm_पूर्णांकerrupt(chip, pvoice);
			अन्यथा 
				snd_emu10k1x_पूर्णांकr_disable(chip, mask);
		पूर्ण
		pvoice++;
		mask <<= 1;
	पूर्ण
		
	अगर (status & (IPR_MIDITRANSBUFEMPTY|IPR_MIसूचीECVBUFEMPTY)) अणु
		अगर (chip->midi.पूर्णांकerrupt)
			chip->midi.पूर्णांकerrupt(chip, status);
		अन्यथा
			snd_emu10k1x_पूर्णांकr_disable(chip, INTE_MIDITXENABLE|INTE_MIसूचीXENABLE);
	पूर्ण
		
	// acknowledge the पूर्णांकerrupt अगर necessary
	outl(status, chip->port + IPR);

	/* dev_dbg(chip->card->dev, "interrupt %08x\n", status); */
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_chmap_elem surround_map[] = अणु
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_chmap_elem clfe_map[] = अणु
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_FC, SNDRV_CHMAP_LFE पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक snd_emu10k1x_pcm(काष्ठा emu10k1x *emu, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	स्थिर काष्ठा snd_pcm_chmap_elem *map = शून्य;
	पूर्णांक err;
	पूर्णांक capture = 0;
  
	अगर (device == 0)
		capture = 1;
	
	अगर ((err = snd_pcm_new(emu->card, "emu10k1x", device, 1, capture, &pcm)) < 0)
		वापस err;
  
	pcm->निजी_data = emu;
	
	चयन(device) अणु
	हाल 0:
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_emu10k1x_playback_ops);
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_emu10k1x_capture_ops);
		अवरोध;
	हाल 1:
	हाल 2:
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_emu10k1x_playback_ops);
		अवरोध;
	पूर्ण

	pcm->info_flags = 0;
	चयन(device) अणु
	हाल 0:
		म_नकल(pcm->name, "EMU10K1X Front");
		map = snd_pcm_std_chmaps;
		अवरोध;
	हाल 1:
		म_नकल(pcm->name, "EMU10K1X Rear");
		map = surround_map;
		अवरोध;
	हाल 2:
		म_नकल(pcm->name, "EMU10K1X Center/LFE");
		map = clfe_map;
		अवरोध;
	पूर्ण
	emu->pcm = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &emu->pci->dev, 32*1024, 32*1024);
  
	वापस snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK, map, 2,
				     1 << 2, शून्य);
पूर्ण

अटल पूर्णांक snd_emu10k1x_create(काष्ठा snd_card *card,
			       काष्ठा pci_dev *pci,
			       काष्ठा emu10k1x **rchip)
अणु
	काष्ठा emu10k1x *chip;
	पूर्णांक err;
	पूर्णांक ch;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_emu10k1x_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(28)) < 0) अणु
		dev_err(card->dev, "error to set 28bit mask DMA\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;

	spin_lock_init(&chip->emu_lock);
	spin_lock_init(&chip->voice_lock);
  
	chip->port = pci_resource_start(pci, 0);
	अगर ((chip->res_port = request_region(chip->port, 8,
					     "EMU10K1X")) == शून्य) अणु 
		dev_err(card->dev, "cannot allocate the port 0x%lx\n",
			chip->port);
		snd_emu10k1x_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण

	अगर (request_irq(pci->irq, snd_emu10k1x_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "cannot grab irq %d\n", pci->irq);
		snd_emu10k1x_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;
  
	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				4 * 1024, &chip->dma_buffer) < 0) अणु
		snd_emu10k1x_मुक्त(chip);
		वापस -ENOMEM;
	पूर्ण

	pci_set_master(pci);
	/* पढ़ो revision & serial */
	chip->revision = pci->revision;
	pci_पढ़ो_config_dword(pci, PCI_SUBSYSTEM_VENDOR_ID, &chip->serial);
	pci_पढ़ो_config_word(pci, PCI_SUBSYSTEM_ID, &chip->model);
	dev_info(card->dev, "Model %04x Rev %08x Serial %08x\n", chip->model,
		   chip->revision, chip->serial);

	outl(0, chip->port + INTE);	

	क्रम(ch = 0; ch < 3; ch++) अणु
		chip->voices[ch].emu = chip;
		chip->voices[ch].number = ch;
	पूर्ण

	/*
	 *  Init to 0x02109204 :
	 *  Clock accuracy    = 0     (1000ppm)
	 *  Sample Rate       = 2     (48kHz)
	 *  Audio Channel     = 1     (Left of 2)
	 *  Source Number     = 0     (Unspecअगरied)
	 *  Generation Status = 1     (Original क्रम Cat Code 12)
	 *  Cat Code          = 12    (Digital Signal Mixer)
	 *  Mode              = 0     (Mode 0)
	 *  Emphasis          = 0     (None)
	 *  CP                = 1     (Copyright unनिश्चितed)
	 *  AN                = 0     (Audio data)
	 *  P                 = 0     (Consumer)
	 */
	snd_emu10k1x_ptr_ग_लिखो(chip, SPCS0, 0,
			       chip->spdअगर_bits[0] = 
			       SPCS_CLKACCY_1000PPM | SPCS_SAMPLERATE_48 |
			       SPCS_CHANNELNUM_LEFT | SPCS_SOURCENUM_UNSPEC |
			       SPCS_GENERATIONSTATUS | 0x00001200 |
			       0x00000000 | SPCS_EMPHASIS_NONE | SPCS_COPYRIGHT);
	snd_emu10k1x_ptr_ग_लिखो(chip, SPCS1, 0,
			       chip->spdअगर_bits[1] = 
			       SPCS_CLKACCY_1000PPM | SPCS_SAMPLERATE_48 |
			       SPCS_CHANNELNUM_LEFT | SPCS_SOURCENUM_UNSPEC |
			       SPCS_GENERATIONSTATUS | 0x00001200 |
			       0x00000000 | SPCS_EMPHASIS_NONE | SPCS_COPYRIGHT);
	snd_emu10k1x_ptr_ग_लिखो(chip, SPCS2, 0,
			       chip->spdअगर_bits[2] = 
			       SPCS_CLKACCY_1000PPM | SPCS_SAMPLERATE_48 |
			       SPCS_CHANNELNUM_LEFT | SPCS_SOURCENUM_UNSPEC |
			       SPCS_GENERATIONSTATUS | 0x00001200 |
			       0x00000000 | SPCS_EMPHASIS_NONE | SPCS_COPYRIGHT);

	snd_emu10k1x_ptr_ग_लिखो(chip, SPDIF_SELECT, 0, 0x700); // disable SPDIF
	snd_emu10k1x_ptr_ग_लिखो(chip, ROUTING, 0, 0x1003F); // routing
	snd_emu10k1x_gpio_ग_लिखो(chip, 0x1080); // analog mode

	outl(HCFG_LOCKSOUNDCACHE|HCFG_AUDIOENABLE, chip->port+HCFG);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL,
				  chip, &ops)) < 0) अणु
		snd_emu10k1x_मुक्त(chip);
		वापस err;
	पूर्ण
	*rchip = chip;
	वापस 0;
पूर्ण

अटल व्योम snd_emu10k1x_proc_reg_पढ़ो(काष्ठा snd_info_entry *entry, 
				       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा emu10k1x *emu = entry->निजी_data;
	अचिन्हित दीर्घ value,value1,value2;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	snd_iम_लिखो(buffer, "Registers:\n\n");
	क्रम(i = 0; i < 0x20; i+=4) अणु
		spin_lock_irqsave(&emu->emu_lock, flags);
		value = inl(emu->port + i);
		spin_unlock_irqrestore(&emu->emu_lock, flags);
		snd_iम_लिखो(buffer, "Register %02X: %08lX\n", i, value);
	पूर्ण
	snd_iम_लिखो(buffer, "\nRegisters\n\n");
	क्रम(i = 0; i <= 0x48; i++) अणु
		value = snd_emu10k1x_ptr_पढ़ो(emu, i, 0);
		अगर(i < 0x10 || (i >= 0x20 && i < 0x40)) अणु
			value1 = snd_emu10k1x_ptr_पढ़ो(emu, i, 1);
			value2 = snd_emu10k1x_ptr_पढ़ो(emu, i, 2);
			snd_iम_लिखो(buffer, "%02X: %08lX %08lX %08lX\n", i, value, value1, value2);
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "%02X: %08lX\n", i, value);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम snd_emu10k1x_proc_reg_ग_लिखो(काष्ठा snd_info_entry *entry, 
					काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा emu10k1x *emu = entry->निजी_data;
	अक्षर line[64];
	अचिन्हित पूर्णांक reg, channel_id , val;

	जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
		अगर (माला_पूछो(line, "%x %x %x", &reg, &channel_id, &val) != 3)
			जारी;

		अगर (reg < 0x49 && channel_id <= 2)
			snd_emu10k1x_ptr_ग_लिखो(emu, reg, channel_id, val);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_emu10k1x_proc_init(काष्ठा emu10k1x *emu)
अणु
	snd_card_rw_proc_new(emu->card, "emu10k1x_regs", emu,
			     snd_emu10k1x_proc_reg_पढ़ो,
			     snd_emu10k1x_proc_reg_ग_लिखो);
	वापस 0;
पूर्ण

#घोषणा snd_emu10k1x_shared_spdअगर_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_emu10k1x_shared_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा emu10k1x *emu = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = (snd_emu10k1x_ptr_पढ़ो(emu, SPDIF_SELECT, 0) == 0x700) ? 0 : 1;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1x_shared_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा emu10k1x *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;

	val = ucontrol->value.पूर्णांकeger.value[0] ;

	अगर (val) अणु
		// enable spdअगर output
		snd_emu10k1x_ptr_ग_लिखो(emu, SPDIF_SELECT, 0, 0x000);
		snd_emu10k1x_ptr_ग_लिखो(emu, ROUTING, 0, 0x700);
		snd_emu10k1x_gpio_ग_लिखो(emu, 0x1000);
	पूर्ण अन्यथा अणु
		// disable spdअगर output
		snd_emu10k1x_ptr_ग_लिखो(emu, SPDIF_SELECT, 0, 0x700);
		snd_emu10k1x_ptr_ग_लिखो(emu, ROUTING, 0, 0x1003F);
		snd_emu10k1x_gpio_ग_लिखो(emu, 0x1080);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1x_shared_spdअगर =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Analog/Digital Output Jack",
	.info =		snd_emu10k1x_shared_spdअगर_info,
	.get =		snd_emu10k1x_shared_spdअगर_get,
	.put =		snd_emu10k1x_shared_spdअगर_put
पूर्ण;

अटल पूर्णांक snd_emu10k1x_spdअगर_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1x_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा emu10k1x *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);

	ucontrol->value.iec958.status[0] = (emu->spdअगर_bits[idx] >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (emu->spdअगर_bits[idx] >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (emu->spdअगर_bits[idx] >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (emu->spdअगर_bits[idx] >> 24) & 0xff;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1x_spdअगर_get_mask(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0xff;
	ucontrol->value.iec958.status[3] = 0xff;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1x_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा emu10k1x *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;

	val = (ucontrol->value.iec958.status[0] << 0) |
		(ucontrol->value.iec958.status[1] << 8) |
		(ucontrol->value.iec958.status[2] << 16) |
		(ucontrol->value.iec958.status[3] << 24);
	change = val != emu->spdअगर_bits[idx];
	अगर (change) अणु
		snd_emu10k1x_ptr_ग_लिखो(emu, SPCS0 + idx, 0, val);
		emu->spdअगर_bits[idx] = val;
	पूर्ण
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1x_spdअगर_mask_control =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,MASK),
	.count =	3,
	.info =         snd_emu10k1x_spdअगर_info,
	.get =          snd_emu10k1x_spdअगर_get_mask
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1x_spdअगर_control =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.count =	3,
	.info =         snd_emu10k1x_spdअगर_info,
	.get =          snd_emu10k1x_spdअगर_get,
	.put =          snd_emu10k1x_spdअगर_put
पूर्ण;

अटल पूर्णांक snd_emu10k1x_mixer(काष्ठा emu10k1x *emu)
अणु
	पूर्णांक err;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_card *card = emu->card;

	अगर ((kctl = snd_ctl_new1(&snd_emu10k1x_spdअगर_mask_control, emu)) == शून्य)
		वापस -ENOMEM;
	अगर ((err = snd_ctl_add(card, kctl)))
		वापस err;
	अगर ((kctl = snd_ctl_new1(&snd_emu10k1x_shared_spdअगर, emu)) == शून्य)
		वापस -ENOMEM;
	अगर ((err = snd_ctl_add(card, kctl)))
		वापस err;
	अगर ((kctl = snd_ctl_new1(&snd_emu10k1x_spdअगर_control, emu)) == शून्य)
		वापस -ENOMEM;
	अगर ((err = snd_ctl_add(card, kctl)))
		वापस err;

	वापस 0;
पूर्ण

#घोषणा EMU10K1X_MIDI_MODE_INPUT	(1<<0)
#घोषणा EMU10K1X_MIDI_MODE_OUTPUT	(1<<1)

अटल अंतरभूत अचिन्हित अक्षर mpu401_पढ़ो(काष्ठा emu10k1x *emu, काष्ठा emu10k1x_midi *mpu, पूर्णांक idx)
अणु
	वापस (अचिन्हित अक्षर)snd_emu10k1x_ptr_पढ़ो(emu, mpu->port + idx, 0);
पूर्ण

अटल अंतरभूत व्योम mpu401_ग_लिखो(काष्ठा emu10k1x *emu, काष्ठा emu10k1x_midi *mpu, पूर्णांक data, पूर्णांक idx)
अणु
	snd_emu10k1x_ptr_ग_लिखो(emu, mpu->port + idx, 0, data);
पूर्ण

#घोषणा mpu401_ग_लिखो_data(emu, mpu, data)	mpu401_ग_लिखो(emu, mpu, data, 0)
#घोषणा mpu401_ग_लिखो_cmd(emu, mpu, data)	mpu401_ग_लिखो(emu, mpu, data, 1)
#घोषणा mpu401_पढ़ो_data(emu, mpu)		mpu401_पढ़ो(emu, mpu, 0)
#घोषणा mpu401_पढ़ो_stat(emu, mpu)		mpu401_पढ़ो(emu, mpu, 1)

#घोषणा mpu401_input_avail(emu,mpu)	(!(mpu401_पढ़ो_stat(emu,mpu) & 0x80))
#घोषणा mpu401_output_पढ़ोy(emu,mpu)	(!(mpu401_पढ़ो_stat(emu,mpu) & 0x40))

#घोषणा MPU401_RESET		0xff
#घोषणा MPU401_ENTER_UART	0x3f
#घोषणा MPU401_ACK		0xfe

अटल व्योम mpu401_clear_rx(काष्ठा emu10k1x *emu, काष्ठा emu10k1x_midi *mpu)
अणु
	पूर्णांक समयout = 100000;
	क्रम (; समयout > 0 && mpu401_input_avail(emu, mpu); समयout--)
		mpu401_पढ़ो_data(emu, mpu);
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (समयout <= 0)
		dev_err(emu->card->dev,
			"cmd: clear rx timeout (status = 0x%x)\n",
			mpu401_पढ़ो_stat(emu, mpu));
#पूर्ण_अगर
पूर्ण

/*

 */

अटल व्योम करो_emu10k1x_midi_पूर्णांकerrupt(काष्ठा emu10k1x *emu,
				       काष्ठा emu10k1x_midi *midi, अचिन्हित पूर्णांक status)
अणु
	अचिन्हित अक्षर byte;

	अगर (midi->rmidi == शून्य) अणु
		snd_emu10k1x_पूर्णांकr_disable(emu, midi->tx_enable | midi->rx_enable);
		वापस;
	पूर्ण

	spin_lock(&midi->input_lock);
	अगर ((status & midi->ipr_rx) && mpu401_input_avail(emu, midi)) अणु
		अगर (!(midi->midi_mode & EMU10K1X_MIDI_MODE_INPUT)) अणु
			mpu401_clear_rx(emu, midi);
		पूर्ण अन्यथा अणु
			byte = mpu401_पढ़ो_data(emu, midi);
			अगर (midi->substream_input)
				snd_rawmidi_receive(midi->substream_input, &byte, 1);
		पूर्ण
	पूर्ण
	spin_unlock(&midi->input_lock);

	spin_lock(&midi->output_lock);
	अगर ((status & midi->ipr_tx) && mpu401_output_पढ़ोy(emu, midi)) अणु
		अगर (midi->substream_output &&
		    snd_rawmidi_transmit(midi->substream_output, &byte, 1) == 1) अणु
			mpu401_ग_लिखो_data(emu, midi, byte);
		पूर्ण अन्यथा अणु
			snd_emu10k1x_पूर्णांकr_disable(emu, midi->tx_enable);
		पूर्ण
	पूर्ण
	spin_unlock(&midi->output_lock);
पूर्ण

अटल व्योम snd_emu10k1x_midi_पूर्णांकerrupt(काष्ठा emu10k1x *emu, अचिन्हित पूर्णांक status)
अणु
	करो_emu10k1x_midi_पूर्णांकerrupt(emu, &emu->midi, status);
पूर्ण

अटल पूर्णांक snd_emu10k1x_midi_cmd(काष्ठा emu10k1x * emu,
				  काष्ठा emu10k1x_midi *midi, अचिन्हित अक्षर cmd, पूर्णांक ack)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक समयout, ok;

	spin_lock_irqsave(&midi->input_lock, flags);
	mpu401_ग_लिखो_data(emu, midi, 0x00);
	/* mpu401_clear_rx(emu, midi); */

	mpu401_ग_लिखो_cmd(emu, midi, cmd);
	अगर (ack) अणु
		ok = 0;
		समयout = 10000;
		जबतक (!ok && समयout-- > 0) अणु
			अगर (mpu401_input_avail(emu, midi)) अणु
				अगर (mpu401_पढ़ो_data(emu, midi) == MPU401_ACK)
					ok = 1;
			पूर्ण
		पूर्ण
		अगर (!ok && mpu401_पढ़ो_data(emu, midi) == MPU401_ACK)
			ok = 1;
	पूर्ण अन्यथा अणु
		ok = 1;
	पूर्ण
	spin_unlock_irqrestore(&midi->input_lock, flags);
	अगर (!ok) अणु
		dev_err(emu->card->dev,
			"midi_cmd: 0x%x failed at 0x%lx (status = 0x%x, data = 0x%x)!!!\n",
			   cmd, emu->port,
			   mpu401_पढ़ो_stat(emu, midi),
			   mpu401_पढ़ो_data(emu, midi));
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1x_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा emu10k1x *emu;
	काष्ठा emu10k1x_midi *midi = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;
	
	emu = midi->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -ENXIO;
	spin_lock_irqsave(&midi->खोलो_lock, flags);
	midi->midi_mode |= EMU10K1X_MIDI_MODE_INPUT;
	midi->substream_input = substream;
	अगर (!(midi->midi_mode & EMU10K1X_MIDI_MODE_OUTPUT)) अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
		अगर (snd_emu10k1x_midi_cmd(emu, midi, MPU401_RESET, 1))
			जाओ error_out;
		अगर (snd_emu10k1x_midi_cmd(emu, midi, MPU401_ENTER_UART, 1))
			जाओ error_out;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
	पूर्ण
	वापस 0;

error_out:
	वापस -EIO;
पूर्ण

अटल पूर्णांक snd_emu10k1x_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा emu10k1x *emu;
	काष्ठा emu10k1x_midi *midi = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	emu = midi->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -ENXIO;
	spin_lock_irqsave(&midi->खोलो_lock, flags);
	midi->midi_mode |= EMU10K1X_MIDI_MODE_OUTPUT;
	midi->substream_output = substream;
	अगर (!(midi->midi_mode & EMU10K1X_MIDI_MODE_INPUT)) अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
		अगर (snd_emu10k1x_midi_cmd(emu, midi, MPU401_RESET, 1))
			जाओ error_out;
		अगर (snd_emu10k1x_midi_cmd(emu, midi, MPU401_ENTER_UART, 1))
			जाओ error_out;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
	पूर्ण
	वापस 0;

error_out:
	वापस -EIO;
पूर्ण

अटल पूर्णांक snd_emu10k1x_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा emu10k1x *emu;
	काष्ठा emu10k1x_midi *midi = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	emu = midi->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -ENXIO;
	spin_lock_irqsave(&midi->खोलो_lock, flags);
	snd_emu10k1x_पूर्णांकr_disable(emu, midi->rx_enable);
	midi->midi_mode &= ~EMU10K1X_MIDI_MODE_INPUT;
	midi->substream_input = शून्य;
	अगर (!(midi->midi_mode & EMU10K1X_MIDI_MODE_OUTPUT)) अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
		err = snd_emu10k1x_midi_cmd(emu, midi, MPU401_RESET, 0);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक snd_emu10k1x_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा emu10k1x *emu;
	काष्ठा emu10k1x_midi *midi = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	emu = midi->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -ENXIO;
	spin_lock_irqsave(&midi->खोलो_lock, flags);
	snd_emu10k1x_पूर्णांकr_disable(emu, midi->tx_enable);
	midi->midi_mode &= ~EMU10K1X_MIDI_MODE_OUTPUT;
	midi->substream_output = शून्य;
	अगर (!(midi->midi_mode & EMU10K1X_MIDI_MODE_INPUT)) अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
		err = snd_emu10k1x_midi_cmd(emu, midi, MPU401_RESET, 0);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम snd_emu10k1x_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा emu10k1x *emu;
	काष्ठा emu10k1x_midi *midi = substream->rmidi->निजी_data;
	emu = midi->emu;
	अगर (snd_BUG_ON(!emu))
		वापस;

	अगर (up)
		snd_emu10k1x_पूर्णांकr_enable(emu, midi->rx_enable);
	अन्यथा
		snd_emu10k1x_पूर्णांकr_disable(emu, midi->rx_enable);
पूर्ण

अटल व्योम snd_emu10k1x_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा emu10k1x *emu;
	काष्ठा emu10k1x_midi *midi = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	emu = midi->emu;
	अगर (snd_BUG_ON(!emu))
		वापस;

	अगर (up) अणु
		पूर्णांक max = 4;
		अचिन्हित अक्षर byte;
	
		/* try to send some amount of bytes here beक्रमe पूर्णांकerrupts */
		spin_lock_irqsave(&midi->output_lock, flags);
		जबतक (max > 0) अणु
			अगर (mpu401_output_पढ़ोy(emu, midi)) अणु
				अगर (!(midi->midi_mode & EMU10K1X_MIDI_MODE_OUTPUT) ||
				    snd_rawmidi_transmit(substream, &byte, 1) != 1) अणु
					/* no more data */
					spin_unlock_irqrestore(&midi->output_lock, flags);
					वापस;
				पूर्ण
				mpu401_ग_लिखो_data(emu, midi, byte);
				max--;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&midi->output_lock, flags);
		snd_emu10k1x_पूर्णांकr_enable(emu, midi->tx_enable);
	पूर्ण अन्यथा अणु
		snd_emu10k1x_पूर्णांकr_disable(emu, midi->tx_enable);
	पूर्ण
पूर्ण

/*

 */

अटल स्थिर काष्ठा snd_rawmidi_ops snd_emu10k1x_midi_output =
अणु
	.खोलो =		snd_emu10k1x_midi_output_खोलो,
	.बंद =	snd_emu10k1x_midi_output_बंद,
	.trigger =	snd_emu10k1x_midi_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_emu10k1x_midi_input =
अणु
	.खोलो =		snd_emu10k1x_midi_input_खोलो,
	.बंद =	snd_emu10k1x_midi_input_बंद,
	.trigger =	snd_emu10k1x_midi_input_trigger,
पूर्ण;

अटल व्योम snd_emu10k1x_midi_मुक्त(काष्ठा snd_rawmidi *rmidi)
अणु
	काष्ठा emu10k1x_midi *midi = rmidi->निजी_data;
	midi->पूर्णांकerrupt = शून्य;
	midi->rmidi = शून्य;
पूर्ण

अटल पूर्णांक emu10k1x_midi_init(काष्ठा emu10k1x *emu,
			      काष्ठा emu10k1x_midi *midi, पूर्णांक device,
			      अक्षर *name)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;

	अगर ((err = snd_rawmidi_new(emu->card, name, device, 1, 1, &rmidi)) < 0)
		वापस err;
	midi->emu = emu;
	spin_lock_init(&midi->खोलो_lock);
	spin_lock_init(&midi->input_lock);
	spin_lock_init(&midi->output_lock);
	म_नकल(rmidi->name, name);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_emu10k1x_midi_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_emu10k1x_midi_input);
	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT |
	                     SNDRV_RAWMIDI_INFO_INPUT |
	                     SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->निजी_data = midi;
	rmidi->निजी_मुक्त = snd_emu10k1x_midi_मुक्त;
	midi->rmidi = rmidi;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1x_midi(काष्ठा emu10k1x *emu)
अणु
	काष्ठा emu10k1x_midi *midi = &emu->midi;
	पूर्णांक err;

	अगर ((err = emu10k1x_midi_init(emu, midi, 0, "EMU10K1X MPU-401 (UART)")) < 0)
		वापस err;

	midi->tx_enable = INTE_MIDITXENABLE;
	midi->rx_enable = INTE_MIसूचीXENABLE;
	midi->port = MUDATA;
	midi->ipr_tx = IPR_MIDITRANSBUFEMPTY;
	midi->ipr_rx = IPR_MIसूचीECVBUFEMPTY;
	midi->पूर्णांकerrupt = snd_emu10k1x_midi_पूर्णांकerrupt;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1x_probe(काष्ठा pci_dev *pci,
			      स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा emu10k1x *chip;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

	अगर ((err = snd_emu10k1x_create(card, pci, &chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	अगर ((err = snd_emu10k1x_pcm(chip, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_emu10k1x_pcm(chip, 1)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_emu10k1x_pcm(chip, 2)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	अगर ((err = snd_emu10k1x_ac97(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	अगर ((err = snd_emu10k1x_mixer(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	
	अगर ((err = snd_emu10k1x_midi(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	snd_emu10k1x_proc_init(chip);

	म_नकल(card->driver, "EMU10K1X");
	म_नकल(card->लघुname, "Dell Sound Blaster Live!");
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx irq %i",
		card->लघुname, chip->port, chip->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_emu10k1x_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

// PCI IDs
अटल स्थिर काष्ठा pci_device_id snd_emu10k1x_ids[] = अणु
	अणु PCI_VDEVICE(CREATIVE, 0x0006), 0 पूर्ण,	/* Dell OEM version (EMU10K1) */
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, snd_emu10k1x_ids);

// pci_driver definition
अटल काष्ठा pci_driver emu10k1x_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_emu10k1x_ids,
	.probe = snd_emu10k1x_probe,
	.हटाओ = snd_emu10k1x_हटाओ,
पूर्ण;

module_pci_driver(emu10k1x_driver);
