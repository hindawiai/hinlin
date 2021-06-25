<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* 
 * Driver क्रम NeoMagic 256AV and 256ZX chipsets.
 * Copyright (c) 2000 by Takashi Iwai <tiwai@suse.de>
 *
 * Based on nm256_audio.c OSS driver in linux kernel.
 * The original author of OSS nm256 driver wishes to reमुख्य anonymous,
 * so I just put my acknoledgment to him/her here.
 * The original author's web page is found at
 *	http://www.uglx.org/sony.hपंचांगl
 */
  
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>

#घोषणा CARD_NAME "NeoMagic 256AV/ZX"
#घोषणा DRIVER_NAME "NM256"

MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("NeoMagic NM256AV/ZX");
MODULE_LICENSE("GPL");

/*
 * some compile conditions.
 */

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;	/* Index */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;	/* ID क्रम this card */
अटल पूर्णांक playback_bufsize = 16;
अटल पूर्णांक capture_bufsize = 16;
अटल bool क्रमce_ac97;			/* disabled as शेष */
अटल पूर्णांक buffer_top;			/* not specअगरied */
अटल bool use_cache;			/* disabled */
अटल bool vaio_hack;			/* disabled */
अटल bool reset_workaround;
अटल bool reset_workaround_2;

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for " CARD_NAME " soundcard.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for " CARD_NAME " soundcard.");
module_param(playback_bufsize, पूर्णांक, 0444);
MODULE_PARM_DESC(playback_bufsize, "DAC frame size in kB for " CARD_NAME " soundcard.");
module_param(capture_bufsize, पूर्णांक, 0444);
MODULE_PARM_DESC(capture_bufsize, "ADC frame size in kB for " CARD_NAME " soundcard.");
module_param(क्रमce_ac97, bool, 0444);
MODULE_PARM_DESC(क्रमce_ac97, "Force to use AC97 codec for " CARD_NAME " soundcard.");
module_param(buffer_top, पूर्णांक, 0444);
MODULE_PARM_DESC(buffer_top, "Set the top address of audio buffer for " CARD_NAME " soundcard.");
module_param(use_cache, bool, 0444);
MODULE_PARM_DESC(use_cache, "Enable the cache for coefficient table access.");
module_param(vaio_hack, bool, 0444);
MODULE_PARM_DESC(vaio_hack, "Enable workaround for Sony VAIO notebooks.");
module_param(reset_workaround, bool, 0444);
MODULE_PARM_DESC(reset_workaround, "Enable AC97 RESET workaround for some laptops.");
module_param(reset_workaround_2, bool, 0444);
MODULE_PARM_DESC(reset_workaround_2, "Enable extended AC97 RESET workaround for some other laptops.");

/* just क्रम backward compatibility */
अटल bool enable;
module_param(enable, bool, 0444);



/*
 * hw definitions
 */

/* The BIOS signature. */
#घोषणा NM_SIGNATURE 0x4e4d0000
/* Signature mask. */
#घोषणा NM_SIG_MASK 0xffff0000

/* Size of the second memory area. */
#घोषणा NM_PORT2_SIZE 4096

/* The base offset of the mixer in the second memory area. */
#घोषणा NM_MIXER_OFFSET 0x600

/* The maximum size of a coefficient entry. */
#घोषणा NM_MAX_PLAYBACK_COEF_SIZE	0x5000
#घोषणा NM_MAX_RECORD_COEF_SIZE		0x1260

/* The पूर्णांकerrupt रेजिस्टर. */
#घोषणा NM_INT_REG 0xa04
/* And its bits. */
#घोषणा NM_PLAYBACK_INT 0x40
#घोषणा NM_RECORD_INT 0x100
#घोषणा NM_MISC_INT_1 0x4000
#घोषणा NM_MISC_INT_2 0x1
#घोषणा NM_ACK_INT(chip, X) snd_nm256_ग_लिखोw(chip, NM_INT_REG, (X) << 1)

/* The AV's "mixer ready" status bit and location. */
#घोषणा NM_MIXER_STATUS_OFFSET 0xa04
#घोषणा NM_MIXER_READY_MASK 0x0800
#घोषणा NM_MIXER_PRESENCE 0xa06
#घोषणा NM_PRESENCE_MASK 0x0050
#घोषणा NM_PRESENCE_VALUE 0x0040

/*
 * For the ZX.  It uses the same पूर्णांकerrupt रेजिस्टर, but it holds 32
 * bits instead of 16.
 */
#घोषणा NM2_PLAYBACK_INT 0x10000
#घोषणा NM2_RECORD_INT 0x80000
#घोषणा NM2_MISC_INT_1 0x8
#घोषणा NM2_MISC_INT_2 0x2
#घोषणा NM2_ACK_INT(chip, X) snd_nm256_ग_लिखोl(chip, NM_INT_REG, (X))

/* The ZX's "mixer ready" status bit and location. */
#घोषणा NM2_MIXER_STATUS_OFFSET 0xa06
#घोषणा NM2_MIXER_READY_MASK 0x0800

/* The playback रेजिस्टरs start from here. */
#घोषणा NM_PLAYBACK_REG_OFFSET 0x0
/* The record रेजिस्टरs start from here. */
#घोषणा NM_RECORD_REG_OFFSET 0x200

/* The rate रेजिस्टर is located 2 bytes from the start of the रेजिस्टर area. */
#घोषणा NM_RATE_REG_OFFSET 2

/* Mono/stereo flag, number of bits on playback, and rate mask. */
#घोषणा NM_RATE_STEREO 1
#घोषणा NM_RATE_BITS_16 2
#घोषणा NM_RATE_MASK 0xf0

/* Playback enable रेजिस्टर. */
#घोषणा NM_PLAYBACK_ENABLE_REG (NM_PLAYBACK_REG_OFFSET + 0x1)
#घोषणा NM_PLAYBACK_ENABLE_FLAG 1
#घोषणा NM_PLAYBACK_ONESHOT 2
#घोषणा NM_PLAYBACK_FREERUN 4

/* Mutes the audio output. */
#घोषणा NM_AUDIO_MUTE_REG (NM_PLAYBACK_REG_OFFSET + 0x18)
#घोषणा NM_AUDIO_MUTE_LEFT 0x8000
#घोषणा NM_AUDIO_MUTE_RIGHT 0x0080

/* Recording enable रेजिस्टर. */
#घोषणा NM_RECORD_ENABLE_REG (NM_RECORD_REG_OFFSET + 0)
#घोषणा NM_RECORD_ENABLE_FLAG 1
#घोषणा NM_RECORD_FREERUN 2

/* coefficient buffer poपूर्णांकer */
#घोषणा NM_COEFF_START_OFFSET	0x1c
#घोषणा NM_COEFF_END_OFFSET	0x20

/* DMA buffer offsets */
#घोषणा NM_RBUFFER_START (NM_RECORD_REG_OFFSET + 0x4)
#घोषणा NM_RBUFFER_END   (NM_RECORD_REG_OFFSET + 0x10)
#घोषणा NM_RBUFFER_WMARK (NM_RECORD_REG_OFFSET + 0xc)
#घोषणा NM_RBUFFER_CURRP (NM_RECORD_REG_OFFSET + 0x8)

#घोषणा NM_PBUFFER_START (NM_PLAYBACK_REG_OFFSET + 0x4)
#घोषणा NM_PBUFFER_END   (NM_PLAYBACK_REG_OFFSET + 0x14)
#घोषणा NM_PBUFFER_WMARK (NM_PLAYBACK_REG_OFFSET + 0xc)
#घोषणा NM_PBUFFER_CURRP (NM_PLAYBACK_REG_OFFSET + 0x8)

काष्ठा nm256_stream अणु

	काष्ठा nm256 *chip;
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक running;
	पूर्णांक suspended;
	
	u32 buf;	/* offset from chip->buffer */
	पूर्णांक bufsize;	/* buffer size in bytes */
	व्योम __iomem *bufptr;		/* mapped poपूर्णांकer */
	अचिन्हित दीर्घ bufptr_addr;	/* physical address of the mapped poपूर्णांकer */

	पूर्णांक dma_size;		/* buffer size of the substream in bytes */
	पूर्णांक period_size;	/* period size in bytes */
	पूर्णांक periods;		/* # of periods */
	पूर्णांक shअगरt;		/* bit shअगरts */
	पूर्णांक cur_period;		/* current period # */

पूर्ण;

काष्ठा nm256 अणु
	
	काष्ठा snd_card *card;

	व्योम __iomem *cport;		/* control port */
	काष्ठा resource *res_cport;	/* its resource */
	अचिन्हित दीर्घ cport_addr;	/* physical address */

	व्योम __iomem *buffer;		/* buffer */
	काष्ठा resource *res_buffer;	/* its resource */
	अचिन्हित दीर्घ buffer_addr;	/* buffer phyiscal address */

	u32 buffer_start;		/* start offset from pci resource 0 */
	u32 buffer_end;			/* end offset */
	u32 buffer_size;		/* total buffer size */

	u32 all_coeff_buf;		/* coefficient buffer */
	u32 coeff_buf[2];		/* coefficient buffer क्रम each stream */

	अचिन्हित पूर्णांक coeffs_current: 1;	/* coeff. table is loaded? */
	अचिन्हित पूर्णांक use_cache: 1;	/* use one big coef. table */
	अचिन्हित पूर्णांक reset_workaround: 1; /* Workaround क्रम some laptops to aव्योम मुक्तze */
	अचिन्हित पूर्णांक reset_workaround_2: 1; /* Extended workaround क्रम some other laptops to aव्योम मुक्तze */
	अचिन्हित पूर्णांक in_resume: 1;

	पूर्णांक mixer_base;			/* रेजिस्टर offset of ac97 mixer */
	पूर्णांक mixer_status_offset;	/* offset of mixer status reg. */
	पूर्णांक mixer_status_mask;		/* bit mask to test the mixer status */

	पूर्णांक irq;
	पूर्णांक irq_acks;
	irq_handler_t पूर्णांकerrupt;
	पूर्णांक badपूर्णांकrcount;		/* counter to check bogus पूर्णांकerrupts */
	काष्ठा mutex irq_mutex;

	काष्ठा nm256_stream streams[2];

	काष्ठा snd_ac97 *ac97;
	अचिन्हित लघु *ac97_regs; /* रेजिस्टर caches, only क्रम valid regs */

	काष्ठा snd_pcm *pcm;

	काष्ठा pci_dev *pci;

	spinlock_t reg_lock;

पूर्ण;


/*
 * include coefficient table
 */
#समावेश "nm256_coef.c"


/*
 * PCI ids
 */
अटल स्थिर काष्ठा pci_device_id snd_nm256_ids[] = अणु
	अणुPCI_VDEVICE(NEOMAGIC, PCI_DEVICE_ID_NEOMAGIC_NM256AV_AUDIO), 0पूर्ण,
	अणुPCI_VDEVICE(NEOMAGIC, PCI_DEVICE_ID_NEOMAGIC_NM256ZX_AUDIO), 0पूर्ण,
	अणुPCI_VDEVICE(NEOMAGIC, PCI_DEVICE_ID_NEOMAGIC_NM256XL_PLUS_AUDIO), 0पूर्ण,
	अणु0,पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_nm256_ids);


/*
 * lowlvel stuffs
 */

अटल अंतरभूत u8
snd_nm256_पढ़ोb(काष्ठा nm256 *chip, पूर्णांक offset)
अणु
	वापस पढ़ोb(chip->cport + offset);
पूर्ण

अटल अंतरभूत u16
snd_nm256_पढ़ोw(काष्ठा nm256 *chip, पूर्णांक offset)
अणु
	वापस पढ़ोw(chip->cport + offset);
पूर्ण

अटल अंतरभूत u32
snd_nm256_पढ़ोl(काष्ठा nm256 *chip, पूर्णांक offset)
अणु
	वापस पढ़ोl(chip->cport + offset);
पूर्ण

अटल अंतरभूत व्योम
snd_nm256_ग_लिखोb(काष्ठा nm256 *chip, पूर्णांक offset, u8 val)
अणु
	ग_लिखोb(val, chip->cport + offset);
पूर्ण

अटल अंतरभूत व्योम
snd_nm256_ग_लिखोw(काष्ठा nm256 *chip, पूर्णांक offset, u16 val)
अणु
	ग_लिखोw(val, chip->cport + offset);
पूर्ण

अटल अंतरभूत व्योम
snd_nm256_ग_लिखोl(काष्ठा nm256 *chip, पूर्णांक offset, u32 val)
अणु
	ग_लिखोl(val, chip->cport + offset);
पूर्ण

अटल अंतरभूत व्योम
snd_nm256_ग_लिखो_buffer(काष्ठा nm256 *chip, स्थिर व्योम *src, पूर्णांक offset, पूर्णांक size)
अणु
	offset -= chip->buffer_start;
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (offset < 0 || offset >= chip->buffer_size) अणु
		dev_err(chip->card->dev,
			"write_buffer invalid offset = %d size = %d\n",
			   offset, size);
		वापस;
	पूर्ण
#पूर्ण_अगर
	स_नकल_toio(chip->buffer + offset, src, size);
पूर्ण

/*
 * coefficient handlers -- what a magic!
 */

अटल u16
snd_nm256_get_start_offset(पूर्णांक which)
अणु
	u16 offset = 0;
	जबतक (which-- > 0)
		offset += coefficient_sizes[which];
	वापस offset;
पूर्ण

अटल व्योम
snd_nm256_load_one_coefficient(काष्ठा nm256 *chip, पूर्णांक stream, u32 port, पूर्णांक which)
अणु
	u32 coeff_buf = chip->coeff_buf[stream];
	u16 offset = snd_nm256_get_start_offset(which);
	u16 size = coefficient_sizes[which];

	snd_nm256_ग_लिखो_buffer(chip, coefficients + offset, coeff_buf, size);
	snd_nm256_ग_लिखोl(chip, port, coeff_buf);
	/* ???  Record seems to behave dअगरferently than playback.  */
	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
		size--;
	snd_nm256_ग_लिखोl(chip, port + 4, coeff_buf + size);
पूर्ण

अटल व्योम
snd_nm256_load_coefficient(काष्ठा nm256 *chip, पूर्णांक stream, पूर्णांक number)
अणु
	/* The enable रेजिस्टर क्रम the specअगरied engine.  */
	u32 poffset = (stream == SNDRV_PCM_STREAM_CAPTURE ?
		       NM_RECORD_ENABLE_REG : NM_PLAYBACK_ENABLE_REG);
	u32 addr = NM_COEFF_START_OFFSET;

	addr += (stream == SNDRV_PCM_STREAM_CAPTURE ?
		 NM_RECORD_REG_OFFSET : NM_PLAYBACK_REG_OFFSET);

	अगर (snd_nm256_पढ़ोb(chip, poffset) & 1) अणु
		dev_dbg(chip->card->dev,
			"NM256: Engine was enabled while loading coefficients!\n");
		वापस;
	पूर्ण

	/* The recording engine uses coefficient values 8-15.  */
	number &= 7;
	अगर (stream == SNDRV_PCM_STREAM_CAPTURE)
		number += 8;

	अगर (! chip->use_cache) अणु
		snd_nm256_load_one_coefficient(chip, stream, addr, number);
		वापस;
	पूर्ण
	अगर (! chip->coeffs_current) अणु
		snd_nm256_ग_लिखो_buffer(chip, coefficients, chip->all_coeff_buf,
				       NM_TOTAL_COEFF_COUNT * 4);
		chip->coeffs_current = 1;
	पूर्ण अन्यथा अणु
		u32 base = chip->all_coeff_buf;
		u32 offset = snd_nm256_get_start_offset(number);
		u32 end_offset = offset + coefficient_sizes[number];
		snd_nm256_ग_लिखोl(chip, addr, base + offset);
		अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
			end_offset--;
		snd_nm256_ग_लिखोl(chip, addr + 4, base + end_offset);
	पूर्ण
पूर्ण


/* The actual rates supported by the card. */
अटल स्थिर अचिन्हित पूर्णांक samplerates[8] = अणु
	8000, 11025, 16000, 22050, 24000, 32000, 44100, 48000,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_rates = अणु
	.count = ARRAY_SIZE(samplerates), 
	.list = samplerates,
	.mask = 0,
पूर्ण;

/*
 * वापस the index of the target rate
 */
अटल पूर्णांक
snd_nm256_fixed_rate(अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(samplerates); i++) अणु
		अगर (rate == samplerates[i])
			वापस i;
	पूर्ण
	snd_BUG();
	वापस 0;
पूर्ण

/*
 * set sample rate and क्रमmat
 */
अटल व्योम
snd_nm256_set_क्रमmat(काष्ठा nm256 *chip, काष्ठा nm256_stream *s,
		     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक rate_index = snd_nm256_fixed_rate(runसमय->rate);
	अचिन्हित अक्षर ratebits = (rate_index << 4) & NM_RATE_MASK;

	s->shअगरt = 0;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16) अणु
		ratebits |= NM_RATE_BITS_16;
		s->shअगरt++;
	पूर्ण
	अगर (runसमय->channels > 1) अणु
		ratebits |= NM_RATE_STEREO;
		s->shअगरt++;
	पूर्ण

	runसमय->rate = samplerates[rate_index];

	चयन (substream->stream) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		snd_nm256_load_coefficient(chip, 0, rate_index); /* 0 = playback */
		snd_nm256_ग_लिखोb(chip,
				 NM_PLAYBACK_REG_OFFSET + NM_RATE_REG_OFFSET,
				 ratebits);
		अवरोध;
	हाल SNDRV_PCM_STREAM_CAPTURE:
		snd_nm256_load_coefficient(chip, 1, rate_index); /* 1 = record */
		snd_nm256_ग_लिखोb(chip,
				 NM_RECORD_REG_OFFSET + NM_RATE_REG_OFFSET,
				 ratebits);
		अवरोध;
	पूर्ण
पूर्ण

/* acquire पूर्णांकerrupt */
अटल पूर्णांक snd_nm256_acquire_irq(काष्ठा nm256 *chip)
अणु
	mutex_lock(&chip->irq_mutex);
	अगर (chip->irq < 0) अणु
		अगर (request_irq(chip->pci->irq, chip->पूर्णांकerrupt, IRQF_SHARED,
				KBUILD_MODNAME, chip)) अणु
			dev_err(chip->card->dev,
				"unable to grab IRQ %d\n", chip->pci->irq);
			mutex_unlock(&chip->irq_mutex);
			वापस -EBUSY;
		पूर्ण
		chip->irq = chip->pci->irq;
		chip->card->sync_irq = chip->irq;
	पूर्ण
	chip->irq_acks++;
	mutex_unlock(&chip->irq_mutex);
	वापस 0;
पूर्ण

/* release पूर्णांकerrupt */
अटल व्योम snd_nm256_release_irq(काष्ठा nm256 *chip)
अणु
	mutex_lock(&chip->irq_mutex);
	अगर (chip->irq_acks > 0)
		chip->irq_acks--;
	अगर (chip->irq_acks == 0 && chip->irq >= 0) अणु
		मुक्त_irq(chip->irq, chip);
		chip->irq = -1;
		chip->card->sync_irq = -1;
	पूर्ण
	mutex_unlock(&chip->irq_mutex);
पूर्ण

/*
 * start / stop
 */

/* update the watermark (current period) */
अटल व्योम snd_nm256_pcm_mark(काष्ठा nm256 *chip, काष्ठा nm256_stream *s, पूर्णांक reg)
अणु
	s->cur_period++;
	s->cur_period %= s->periods;
	snd_nm256_ग_लिखोl(chip, reg, s->buf + s->cur_period * s->period_size);
पूर्ण

#घोषणा snd_nm256_playback_mark(chip, s) snd_nm256_pcm_mark(chip, s, NM_PBUFFER_WMARK)
#घोषणा snd_nm256_capture_mark(chip, s)  snd_nm256_pcm_mark(chip, s, NM_RBUFFER_WMARK)

अटल व्योम
snd_nm256_playback_start(काष्ठा nm256 *chip, काष्ठा nm256_stream *s,
			 काष्ठा snd_pcm_substream *substream)
अणु
	/* program buffer poपूर्णांकers */
	snd_nm256_ग_लिखोl(chip, NM_PBUFFER_START, s->buf);
	snd_nm256_ग_लिखोl(chip, NM_PBUFFER_END, s->buf + s->dma_size - (1 << s->shअगरt));
	snd_nm256_ग_लिखोl(chip, NM_PBUFFER_CURRP, s->buf);
	snd_nm256_playback_mark(chip, s);

	/* Enable playback engine and पूर्णांकerrupts. */
	snd_nm256_ग_लिखोb(chip, NM_PLAYBACK_ENABLE_REG,
			 NM_PLAYBACK_ENABLE_FLAG | NM_PLAYBACK_FREERUN);
	/* Enable both channels. */
	snd_nm256_ग_लिखोw(chip, NM_AUDIO_MUTE_REG, 0x0);
पूर्ण

अटल व्योम
snd_nm256_capture_start(काष्ठा nm256 *chip, काष्ठा nm256_stream *s,
			काष्ठा snd_pcm_substream *substream)
अणु
	/* program buffer poपूर्णांकers */
	snd_nm256_ग_लिखोl(chip, NM_RBUFFER_START, s->buf);
	snd_nm256_ग_लिखोl(chip, NM_RBUFFER_END, s->buf + s->dma_size);
	snd_nm256_ग_लिखोl(chip, NM_RBUFFER_CURRP, s->buf);
	snd_nm256_capture_mark(chip, s);

	/* Enable playback engine and पूर्णांकerrupts. */
	snd_nm256_ग_लिखोb(chip, NM_RECORD_ENABLE_REG,
			 NM_RECORD_ENABLE_FLAG | NM_RECORD_FREERUN);
पूर्ण

/* Stop the play engine. */
अटल व्योम
snd_nm256_playback_stop(काष्ठा nm256 *chip)
अणु
	/* Shut off sound from both channels. */
	snd_nm256_ग_लिखोw(chip, NM_AUDIO_MUTE_REG,
			 NM_AUDIO_MUTE_LEFT | NM_AUDIO_MUTE_RIGHT);
	/* Disable play engine. */
	snd_nm256_ग_लिखोb(chip, NM_PLAYBACK_ENABLE_REG, 0);
पूर्ण

अटल व्योम
snd_nm256_capture_stop(काष्ठा nm256 *chip)
अणु
	/* Disable recording engine. */
	snd_nm256_ग_लिखोb(chip, NM_RECORD_ENABLE_REG, 0);
पूर्ण

अटल पूर्णांक
snd_nm256_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा nm256 *chip = snd_pcm_substream_chip(substream);
	काष्ठा nm256_stream *s = substream->runसमय->निजी_data;
	पूर्णांक err = 0;

	अगर (snd_BUG_ON(!s))
		वापस -ENXIO;

	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_RESUME:
		s->suspended = 0;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (! s->running) अणु
			snd_nm256_playback_start(chip, s, substream);
			s->running = 1;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		s->suspended = 1;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (s->running) अणु
			snd_nm256_playback_stop(chip);
			s->running = 0;
		पूर्ण
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस err;
पूर्ण

अटल पूर्णांक
snd_nm256_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा nm256 *chip = snd_pcm_substream_chip(substream);
	काष्ठा nm256_stream *s = substream->runसमय->निजी_data;
	पूर्णांक err = 0;

	अगर (snd_BUG_ON(!s))
		वापस -ENXIO;

	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (! s->running) अणु
			snd_nm256_capture_start(chip, s, substream);
			s->running = 1;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (s->running) अणु
			snd_nm256_capture_stop(chip);
			s->running = 0;
		पूर्ण
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस err;
पूर्ण


/*
 * prepare playback/capture channel
 */
अटल पूर्णांक snd_nm256_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा nm256 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा nm256_stream *s = runसमय->निजी_data;

	अगर (snd_BUG_ON(!s))
		वापस -ENXIO;
	s->dma_size = frames_to_bytes(runसमय, substream->runसमय->buffer_size);
	s->period_size = frames_to_bytes(runसमय, substream->runसमय->period_size);
	s->periods = substream->runसमय->periods;
	s->cur_period = 0;

	spin_lock_irq(&chip->reg_lock);
	s->running = 0;
	snd_nm256_set_क्रमmat(chip, s, substream);
	spin_unlock_irq(&chip->reg_lock);

	वापस 0;
पूर्ण


/*
 * get the current poपूर्णांकer
 */
अटल snd_pcm_uframes_t
snd_nm256_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा nm256 *chip = snd_pcm_substream_chip(substream);
	काष्ठा nm256_stream *s = substream->runसमय->निजी_data;
	अचिन्हित दीर्घ curp;

	अगर (snd_BUG_ON(!s))
		वापस 0;
	curp = snd_nm256_पढ़ोl(chip, NM_PBUFFER_CURRP) - (अचिन्हित दीर्घ)s->buf;
	curp %= s->dma_size;
	वापस bytes_to_frames(substream->runसमय, curp);
पूर्ण

अटल snd_pcm_uframes_t
snd_nm256_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा nm256 *chip = snd_pcm_substream_chip(substream);
	काष्ठा nm256_stream *s = substream->runसमय->निजी_data;
	अचिन्हित दीर्घ curp;

	अगर (snd_BUG_ON(!s))
		वापस 0;
	curp = snd_nm256_पढ़ोl(chip, NM_RBUFFER_CURRP) - (अचिन्हित दीर्घ)s->buf;
	curp %= s->dma_size;	
	वापस bytes_to_frames(substream->runसमय, curp);
पूर्ण

/* Remapped I/O space can be accessible as poपूर्णांकer on i386 */
/* This might be changed in the future */
#अगर_अघोषित __i386__
/*
 * silence / copy क्रम playback
 */
अटल पूर्णांक
snd_nm256_playback_silence(काष्ठा snd_pcm_substream *substream,
			   पूर्णांक channel, अचिन्हित दीर्घ pos, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा nm256_stream *s = runसमय->निजी_data;

	स_रखो_io(s->bufptr + pos, 0, count);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_nm256_playback_copy(काष्ठा snd_pcm_substream *substream,
			पूर्णांक channel, अचिन्हित दीर्घ pos,
			व्योम __user *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा nm256_stream *s = runसमय->निजी_data;

	अगर (copy_from_user_toio(s->bufptr + pos, src, count))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_nm256_playback_copy_kernel(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक channel, अचिन्हित दीर्घ pos,
			       व्योम *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा nm256_stream *s = runसमय->निजी_data;

	स_नकल_toio(s->bufptr + pos, src, count);
	वापस 0;
पूर्ण

/*
 * copy to user
 */
अटल पूर्णांक
snd_nm256_capture_copy(काष्ठा snd_pcm_substream *substream,
		       पूर्णांक channel, अचिन्हित दीर्घ pos,
		       व्योम __user *dst, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा nm256_stream *s = runसमय->निजी_data;

	अगर (copy_to_user_fromio(dst, s->bufptr + pos, count))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_nm256_capture_copy_kernel(काष्ठा snd_pcm_substream *substream,
			      पूर्णांक channel, अचिन्हित दीर्घ pos,
			      व्योम *dst, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा nm256_stream *s = runसमय->निजी_data;

	स_नकल_fromio(dst, s->bufptr + pos, count);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !__i386__ */


/*
 * update playback/capture watermarks
 */

/* spinlock held! */
अटल व्योम
snd_nm256_playback_update(काष्ठा nm256 *chip)
अणु
	काष्ठा nm256_stream *s;

	s = &chip->streams[SNDRV_PCM_STREAM_PLAYBACK];
	अगर (s->running && s->substream) अणु
		spin_unlock(&chip->reg_lock);
		snd_pcm_period_elapsed(s->substream);
		spin_lock(&chip->reg_lock);
		snd_nm256_playback_mark(chip, s);
	पूर्ण
पूर्ण

/* spinlock held! */
अटल व्योम
snd_nm256_capture_update(काष्ठा nm256 *chip)
अणु
	काष्ठा nm256_stream *s;

	s = &chip->streams[SNDRV_PCM_STREAM_CAPTURE];
	अगर (s->running && s->substream) अणु
		spin_unlock(&chip->reg_lock);
		snd_pcm_period_elapsed(s->substream);
		spin_lock(&chip->reg_lock);
		snd_nm256_capture_mark(chip, s);
	पूर्ण
पूर्ण

/*
 * hardware info
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_nm256_playback =
अणु
	.info =			SNDRV_PCM_INFO_MMAP_IOMEM |SNDRV_PCM_INFO_MMAP_VALID |
				SNDRV_PCM_INFO_INTERLEAVED |
				/*SNDRV_PCM_INFO_PAUSE |*/
				SNDRV_PCM_INFO_RESUME,
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_KNOT/*24k*/ | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		8000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.periods_min =		2,
	.periods_max =		1024,
	.buffer_bytes_max =	128 * 1024,
	.period_bytes_min =	256,
	.period_bytes_max =	128 * 1024,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_nm256_capture =
अणु
	.info =			SNDRV_PCM_INFO_MMAP_IOMEM | SNDRV_PCM_INFO_MMAP_VALID |
				SNDRV_PCM_INFO_INTERLEAVED |
				/*SNDRV_PCM_INFO_PAUSE |*/
				SNDRV_PCM_INFO_RESUME,
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_KNOT/*24k*/ | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		8000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.periods_min =		2,
	.periods_max =		1024,
	.buffer_bytes_max =	128 * 1024,
	.period_bytes_min =	256,
	.period_bytes_max =	128 * 1024,
पूर्ण;


/* set dma transfer size */
अटल पूर्णांक snd_nm256_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *hw_params)
अणु
	/* area and addr are alपढ़ोy set and unchanged */
	substream->runसमय->dma_bytes = params_buffer_bytes(hw_params);
	वापस 0;
पूर्ण

/*
 * खोलो
 */
अटल व्योम snd_nm256_setup_stream(काष्ठा nm256 *chip, काष्ठा nm256_stream *s,
				   काष्ठा snd_pcm_substream *substream,
				   स्थिर काष्ठा snd_pcm_hardware *hw_ptr)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	s->running = 0;
	runसमय->hw = *hw_ptr;
	runसमय->hw.buffer_bytes_max = s->bufsize;
	runसमय->hw.period_bytes_max = s->bufsize / 2;
	runसमय->dma_area = (व्योम __क्रमce *) s->bufptr;
	runसमय->dma_addr = s->bufptr_addr;
	runसमय->dma_bytes = s->bufsize;
	runसमय->निजी_data = s;
	s->substream = substream;

	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &स्थिरraपूर्णांकs_rates);
पूर्ण

अटल पूर्णांक
snd_nm256_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा nm256 *chip = snd_pcm_substream_chip(substream);

	अगर (snd_nm256_acquire_irq(chip) < 0)
		वापस -EBUSY;
	snd_nm256_setup_stream(chip, &chip->streams[SNDRV_PCM_STREAM_PLAYBACK],
			       substream, &snd_nm256_playback);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_nm256_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा nm256 *chip = snd_pcm_substream_chip(substream);

	अगर (snd_nm256_acquire_irq(chip) < 0)
		वापस -EBUSY;
	snd_nm256_setup_stream(chip, &chip->streams[SNDRV_PCM_STREAM_CAPTURE],
			       substream, &snd_nm256_capture);
	वापस 0;
पूर्ण

/*
 * बंद - we करोn't have to करो special..
 */
अटल पूर्णांक
snd_nm256_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा nm256 *chip = snd_pcm_substream_chip(substream);

	snd_nm256_release_irq(chip);
	वापस 0;
पूर्ण


अटल पूर्णांक
snd_nm256_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा nm256 *chip = snd_pcm_substream_chip(substream);

	snd_nm256_release_irq(chip);
	वापस 0;
पूर्ण

/*
 * create a pcm instance
 */
अटल स्थिर काष्ठा snd_pcm_ops snd_nm256_playback_ops = अणु
	.खोलो =		snd_nm256_playback_खोलो,
	.बंद =	snd_nm256_playback_बंद,
	.hw_params =	snd_nm256_pcm_hw_params,
	.prepare =	snd_nm256_pcm_prepare,
	.trigger =	snd_nm256_playback_trigger,
	.poपूर्णांकer =	snd_nm256_playback_poपूर्णांकer,
#अगर_अघोषित __i386__
	.copy_user =	snd_nm256_playback_copy,
	.copy_kernel =	snd_nm256_playback_copy_kernel,
	.fill_silence =	snd_nm256_playback_silence,
#पूर्ण_अगर
	.mmap =		snd_pcm_lib_mmap_iomem,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_nm256_capture_ops = अणु
	.खोलो =		snd_nm256_capture_खोलो,
	.बंद =	snd_nm256_capture_बंद,
	.hw_params =	snd_nm256_pcm_hw_params,
	.prepare =	snd_nm256_pcm_prepare,
	.trigger =	snd_nm256_capture_trigger,
	.poपूर्णांकer =	snd_nm256_capture_poपूर्णांकer,
#अगर_अघोषित __i386__
	.copy_user =	snd_nm256_capture_copy,
	.copy_kernel =	snd_nm256_capture_copy_kernel,
#पूर्ण_अगर
	.mmap =		snd_pcm_lib_mmap_iomem,
पूर्ण;

अटल पूर्णांक
snd_nm256_pcm(काष्ठा nm256 *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक i, err;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा nm256_stream *s = &chip->streams[i];
		s->bufptr = chip->buffer + (s->buf - chip->buffer_start);
		s->bufptr_addr = chip->buffer_addr + (s->buf - chip->buffer_start);
	पूर्ण

	err = snd_pcm_new(chip->card, chip->card->driver, device,
			  1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_nm256_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_nm256_capture_ops);

	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	chip->pcm = pcm;

	वापस 0;
पूर्ण


/* 
 * Initialize the hardware. 
 */
अटल व्योम
snd_nm256_init_chip(काष्ठा nm256 *chip)
अणु
	/* Reset everything. */
	snd_nm256_ग_लिखोb(chip, 0x0, 0x11);
	snd_nm256_ग_लिखोw(chip, 0x214, 0);
	/* stop sounds.. */
	//snd_nm256_playback_stop(chip);
	//snd_nm256_capture_stop(chip);
पूर्ण


अटल irqवापस_t
snd_nm256_पूर्णांकr_check(काष्ठा nm256 *chip)
अणु
	अगर (chip->badपूर्णांकrcount++ > 1000) अणु
		/*
		 * I'm not sure अगर the best thing is to stop the card from
		 * playing or just release the पूर्णांकerrupt (after all, we're in
		 * a bad situation, so करोing fancy stuff may not be such a good
		 * idea).
		 *
		 * I worry about the card engine continuing to play noise
		 * over and over, however--that could become a very
		 * obnoxious problem.  And we know that when this usually
		 * happens things are fairly safe, it just means the user's
		 * inserted a PCMCIA card and someone's spamming us with IRQ 9s.
		 */
		अगर (chip->streams[SNDRV_PCM_STREAM_PLAYBACK].running)
			snd_nm256_playback_stop(chip);
		अगर (chip->streams[SNDRV_PCM_STREAM_CAPTURE].running)
			snd_nm256_capture_stop(chip);
		chip->badपूर्णांकrcount = 0;
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

/* 
 * Handle a potential पूर्णांकerrupt क्रम the device referred to by DEV_ID. 
 *
 * I करोn't like the cut-n-paste job here either between the two routines,
 * but there are sufficient dअगरferences between the two पूर्णांकerrupt handlers
 * that parameterizing it isn't all that great either.  (Could use a macro,
 * I suppose...yucky bleah.)
 */

अटल irqवापस_t
snd_nm256_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा nm256 *chip = dev_id;
	u16 status;
	u8 cbyte;

	status = snd_nm256_पढ़ोw(chip, NM_INT_REG);

	/* Not ours. */
	अगर (status == 0)
		वापस snd_nm256_पूर्णांकr_check(chip);

	chip->badपूर्णांकrcount = 0;

	/* Rather boring; check क्रम inभागidual पूर्णांकerrupts and process them. */

	spin_lock(&chip->reg_lock);
	अगर (status & NM_PLAYBACK_INT) अणु
		status &= ~NM_PLAYBACK_INT;
		NM_ACK_INT(chip, NM_PLAYBACK_INT);
		snd_nm256_playback_update(chip);
	पूर्ण

	अगर (status & NM_RECORD_INT) अणु
		status &= ~NM_RECORD_INT;
		NM_ACK_INT(chip, NM_RECORD_INT);
		snd_nm256_capture_update(chip);
	पूर्ण

	अगर (status & NM_MISC_INT_1) अणु
		status &= ~NM_MISC_INT_1;
		NM_ACK_INT(chip, NM_MISC_INT_1);
		dev_dbg(chip->card->dev, "NM256: Got misc interrupt #1\n");
		snd_nm256_ग_लिखोw(chip, NM_INT_REG, 0x8000);
		cbyte = snd_nm256_पढ़ोb(chip, 0x400);
		snd_nm256_ग_लिखोb(chip, 0x400, cbyte | 2);
	पूर्ण

	अगर (status & NM_MISC_INT_2) अणु
		status &= ~NM_MISC_INT_2;
		NM_ACK_INT(chip, NM_MISC_INT_2);
		dev_dbg(chip->card->dev, "NM256: Got misc interrupt #2\n");
		cbyte = snd_nm256_पढ़ोb(chip, 0x400);
		snd_nm256_ग_लिखोb(chip, 0x400, cbyte & ~2);
	पूर्ण

	/* Unknown पूर्णांकerrupt. */
	अगर (status) अणु
		dev_dbg(chip->card->dev,
			"NM256: Fire in the hole! Unknown status 0x%x\n",
			   status);
		/* Pray. */
		NM_ACK_INT(chip, status);
	पूर्ण

	spin_unlock(&chip->reg_lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Handle a potential पूर्णांकerrupt क्रम the device referred to by DEV_ID.
 * This handler is क्रम the 256ZX, and is very similar to the non-ZX
 * routine.
 */

अटल irqवापस_t
snd_nm256_पूर्णांकerrupt_zx(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा nm256 *chip = dev_id;
	u32 status;
	u8 cbyte;

	status = snd_nm256_पढ़ोl(chip, NM_INT_REG);

	/* Not ours. */
	अगर (status == 0)
		वापस snd_nm256_पूर्णांकr_check(chip);

	chip->badपूर्णांकrcount = 0;

	/* Rather boring; check क्रम inभागidual पूर्णांकerrupts and process them. */

	spin_lock(&chip->reg_lock);
	अगर (status & NM2_PLAYBACK_INT) अणु
		status &= ~NM2_PLAYBACK_INT;
		NM2_ACK_INT(chip, NM2_PLAYBACK_INT);
		snd_nm256_playback_update(chip);
	पूर्ण

	अगर (status & NM2_RECORD_INT) अणु
		status &= ~NM2_RECORD_INT;
		NM2_ACK_INT(chip, NM2_RECORD_INT);
		snd_nm256_capture_update(chip);
	पूर्ण

	अगर (status & NM2_MISC_INT_1) अणु
		status &= ~NM2_MISC_INT_1;
		NM2_ACK_INT(chip, NM2_MISC_INT_1);
		dev_dbg(chip->card->dev, "NM256: Got misc interrupt #1\n");
		cbyte = snd_nm256_पढ़ोb(chip, 0x400);
		snd_nm256_ग_लिखोb(chip, 0x400, cbyte | 2);
	पूर्ण

	अगर (status & NM2_MISC_INT_2) अणु
		status &= ~NM2_MISC_INT_2;
		NM2_ACK_INT(chip, NM2_MISC_INT_2);
		dev_dbg(chip->card->dev, "NM256: Got misc interrupt #2\n");
		cbyte = snd_nm256_पढ़ोb(chip, 0x400);
		snd_nm256_ग_लिखोb(chip, 0x400, cbyte & ~2);
	पूर्ण

	/* Unknown पूर्णांकerrupt. */
	अगर (status) अणु
		dev_dbg(chip->card->dev,
			"NM256: Fire in the hole! Unknown status 0x%x\n",
			   status);
		/* Pray. */
		NM2_ACK_INT(chip, status);
	पूर्ण

	spin_unlock(&chip->reg_lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * AC97 पूर्णांकerface
 */

/*
 * Waits क्रम the mixer to become पढ़ोy to be written; वापसs a zero value
 * अगर it समयd out.
 */
अटल पूर्णांक
snd_nm256_ac97_पढ़ोy(काष्ठा nm256 *chip)
अणु
	पूर्णांक समयout = 10;
	u32 testaddr;
	u16 testb;

	testaddr = chip->mixer_status_offset;
	testb = chip->mixer_status_mask;

	/* 
	 * Loop around रुकोing क्रम the mixer to become पढ़ोy. 
	 */
	जबतक (समयout-- > 0) अणु
		अगर ((snd_nm256_पढ़ोw(chip, testaddr) & testb) == 0)
			वापस 1;
		udelay(100);
	पूर्ण
	वापस 0;
पूर्ण

/* 
 * Initial रेजिस्टर values to be written to the AC97 mixer.
 * While most of these are identical to the reset values, we करो this
 * so that we have most of the रेजिस्टर contents cached--this aव्योमs
 * पढ़ोing from the mixer directly (which seems to be problematic,
 * probably due to ignorance).
 */

काष्ठा initialValues अणु
	अचिन्हित लघु reg;
	अचिन्हित लघु value;
पूर्ण;

अटल स्थिर काष्ठा initialValues nm256_ac97_init_val[] =
अणु
	अणु AC97_MASTER, 		0x8000 पूर्ण,
	अणु AC97_HEADPHONE,	0x8000 पूर्ण,
	अणु AC97_MASTER_MONO,	0x8000 पूर्ण,
	अणु AC97_PC_BEEP,		0x8000 पूर्ण,
	अणु AC97_PHONE,		0x8008 पूर्ण,
	अणु AC97_MIC,		0x8000 पूर्ण,
	अणु AC97_LINE,		0x8808 पूर्ण,
	अणु AC97_CD,		0x8808 पूर्ण,
	अणु AC97_VIDEO,		0x8808 पूर्ण,
	अणु AC97_AUX,		0x8808 पूर्ण,
	अणु AC97_PCM,		0x8808 पूर्ण,
	अणु AC97_REC_SEL,		0x0000 पूर्ण,
	अणु AC97_REC_GAIN,	0x0B0B पूर्ण,
	अणु AC97_GENERAL_PURPOSE,	0x0000 पूर्ण,
	अणु AC97_3D_CONTROL,	0x8000 पूर्ण, 
	अणु AC97_VENDOR_ID1, 	0x8384 पूर्ण,
	अणु AC97_VENDOR_ID2,	0x7609 पूर्ण,
पूर्ण;

अटल पूर्णांक nm256_ac97_idx(अचिन्हित लघु reg)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(nm256_ac97_init_val); i++)
		अगर (nm256_ac97_init_val[i].reg == reg)
			वापस i;
	वापस -1;
पूर्ण

/*
 * some nm256 easily crash when पढ़ोing from mixer रेजिस्टरs
 * thus we're treating it as a ग_लिखो-only mixer and cache the
 * written values
 */
अटल अचिन्हित लघु
snd_nm256_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	काष्ठा nm256 *chip = ac97->निजी_data;
	पूर्णांक idx = nm256_ac97_idx(reg);

	अगर (idx < 0)
		वापस 0;
	वापस chip->ac97_regs[idx];
पूर्ण

/* 
 */
अटल व्योम
snd_nm256_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97,
		     अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	काष्ठा nm256 *chip = ac97->निजी_data;
	पूर्णांक tries = 2;
	पूर्णांक idx = nm256_ac97_idx(reg);
	u32 base;

	अगर (idx < 0)
		वापस;

	base = chip->mixer_base;

	snd_nm256_ac97_पढ़ोy(chip);

	/* Wait क्रम the ग_लिखो to take, too. */
	जबतक (tries-- > 0) अणु
		snd_nm256_ग_लिखोw(chip, base + reg, val);
		msleep(1);  /* a little delay here seems better.. */
		अगर (snd_nm256_ac97_पढ़ोy(chip)) अणु
			/* successful ग_लिखो: set cache */
			chip->ac97_regs[idx] = val;
			वापस;
		पूर्ण
	पूर्ण
	dev_dbg(chip->card->dev, "nm256: ac97 codec not ready..\n");
पूर्ण

/* अटल resolution table */
अटल स्थिर काष्ठा snd_ac97_res_table nm256_res_table[] = अणु
	अणु AC97_MASTER, 0x1f1f पूर्ण,
	अणु AC97_HEADPHONE, 0x1f1f पूर्ण,
	अणु AC97_MASTER_MONO, 0x001f पूर्ण,
	अणु AC97_PC_BEEP, 0x001f पूर्ण,
	अणु AC97_PHONE, 0x001f पूर्ण,
	अणु AC97_MIC, 0x001f पूर्ण,
	अणु AC97_LINE, 0x1f1f पूर्ण,
	अणु AC97_CD, 0x1f1f पूर्ण,
	अणु AC97_VIDEO, 0x1f1f पूर्ण,
	अणु AC97_AUX, 0x1f1f पूर्ण,
	अणु AC97_PCM, 0x1f1f पूर्ण,
	अणु AC97_REC_GAIN, 0x0f0f पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;

/* initialize the ac97 पूर्णांकo a known state */
अटल व्योम
snd_nm256_ac97_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा nm256 *chip = ac97->निजी_data;

	/* Reset the mixer.  'Tis magic!  */
	snd_nm256_ग_लिखोb(chip, 0x6c0, 1);
	अगर (! chip->reset_workaround) अणु
		/* Dell latitude LS will lock up by this */
		snd_nm256_ग_लिखोb(chip, 0x6cc, 0x87);
	पूर्ण
	अगर (! chip->reset_workaround_2) अणु
		/* Dell latitude CSx will lock up by this */
		snd_nm256_ग_लिखोb(chip, 0x6cc, 0x80);
		snd_nm256_ग_लिखोb(chip, 0x6cc, 0x0);
	पूर्ण
	अगर (! chip->in_resume) अणु
		पूर्णांक i;
		क्रम (i = 0; i < ARRAY_SIZE(nm256_ac97_init_val); i++) अणु
			/* preload the cache, so as to aव्योम even a single
			 * पढ़ो of the mixer regs
			 */
			snd_nm256_ac97_ग_लिखो(ac97, nm256_ac97_init_val[i].reg,
					     nm256_ac97_init_val[i].value);
		पूर्ण
	पूर्ण
पूर्ण

/* create an ac97 mixer पूर्णांकerface */
अटल पूर्णांक
snd_nm256_mixer(काष्ठा nm256 *chip)
अणु
	काष्ठा snd_ac97_bus *pbus;
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.reset = snd_nm256_ac97_reset,
		.ग_लिखो = snd_nm256_ac97_ग_लिखो,
		.पढ़ो = snd_nm256_ac97_पढ़ो,
	पूर्ण;

	chip->ac97_regs = kसुस्मृति(ARRAY_SIZE(nm256_ac97_init_val),
				  माप(लघु), GFP_KERNEL);
	अगर (! chip->ac97_regs)
		वापस -ENOMEM;

	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, शून्य, &pbus)) < 0)
		वापस err;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.scaps = AC97_SCAP_AUDIO; /* we support audio! */
	ac97.निजी_data = chip;
	ac97.res_table = nm256_res_table;
	pbus->no_vra = 1;
	err = snd_ac97_mixer(pbus, &ac97, &chip->ac97);
	अगर (err < 0)
		वापस err;
	अगर (! (chip->ac97->id & (0xf0000000))) अणु
		/* looks like an invalid id */
		प्र_लिखो(chip->card->mixername, "%s AC97", chip->card->driver);
	पूर्ण
	वापस 0;
पूर्ण

/* 
 * See अगर the signature left by the NM256 BIOS is पूर्णांकact; अगर so, we use
 * the associated address as the end of our audio buffer in the video
 * RAM.
 */

अटल पूर्णांक
snd_nm256_peek_क्रम_sig(काष्ठा nm256 *chip)
अणु
	/* The signature is located 1K below the end of video RAM.  */
	व्योम __iomem *temp;
	/* Default buffer end is 5120 bytes below the top of RAM.  */
	अचिन्हित दीर्घ poपूर्णांकer_found = chip->buffer_end - 0x1400;
	u32 sig;

	temp = ioremap(chip->buffer_addr + chip->buffer_end - 0x400, 16);
	अगर (temp == शून्य) अणु
		dev_err(chip->card->dev,
			"Unable to scan for card signature in video RAM\n");
		वापस -EBUSY;
	पूर्ण

	sig = पढ़ोl(temp);
	अगर ((sig & NM_SIG_MASK) == NM_SIGNATURE) अणु
		u32 poपूर्णांकer = पढ़ोl(temp + 4);

		/*
		 * If it's obviously invalid, don't use it
		 */
		अगर (poपूर्णांकer == 0xffffffff ||
		    poपूर्णांकer < chip->buffer_size ||
		    poपूर्णांकer > chip->buffer_end) अणु
			dev_err(chip->card->dev,
				"invalid signature found: 0x%x\n", poपूर्णांकer);
			iounmap(temp);
			वापस -ENODEV;
		पूर्ण अन्यथा अणु
			poपूर्णांकer_found = poपूर्णांकer;
			dev_info(chip->card->dev,
				 "found card signature in video RAM: 0x%x\n",
			       poपूर्णांकer);
		पूर्ण
	पूर्ण

	iounmap(temp);
	chip->buffer_end = poपूर्णांकer_found;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * APM event handler, so the card is properly reinitialized after a घातer
 * event.
 */
अटल पूर्णांक nm256_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा nm256 *chip = card->निजी_data;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_ac97_suspend(chip->ac97);
	chip->coeffs_current = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक nm256_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा nm256 *chip = card->निजी_data;
	पूर्णांक i;

	/* Perक्रमm a full reset on the hardware */
	chip->in_resume = 1;

	snd_nm256_init_chip(chip);

	/* restore ac97 */
	snd_ac97_resume(chip->ac97);

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा nm256_stream *s = &chip->streams[i];
		अगर (s->substream && s->suspended) अणु
			spin_lock_irq(&chip->reg_lock);
			snd_nm256_set_क्रमmat(chip, s, s->substream);
			spin_unlock_irq(&chip->reg_lock);
		पूर्ण
	पूर्ण

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	chip->in_resume = 0;
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(nm256_pm, nm256_suspend, nm256_resume);
#घोषणा NM256_PM_OPS	&nm256_pm
#अन्यथा
#घोषणा NM256_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक snd_nm256_मुक्त(काष्ठा nm256 *chip)
अणु
	अगर (chip->streams[SNDRV_PCM_STREAM_PLAYBACK].running)
		snd_nm256_playback_stop(chip);
	अगर (chip->streams[SNDRV_PCM_STREAM_CAPTURE].running)
		snd_nm256_capture_stop(chip);

	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);

	iounmap(chip->cport);
	iounmap(chip->buffer);
	release_and_मुक्त_resource(chip->res_cport);
	release_and_मुक्त_resource(chip->res_buffer);

	pci_disable_device(chip->pci);
	kमुक्त(chip->ac97_regs);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_nm256_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा nm256 *chip = device->device_data;
	वापस snd_nm256_मुक्त(chip);
पूर्ण

अटल पूर्णांक
snd_nm256_create(काष्ठा snd_card *card, काष्ठा pci_dev *pci,
		 काष्ठा nm256 **chip_ret)
अणु
	काष्ठा nm256 *chip;
	पूर्णांक err, pval;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_nm256_dev_मुक्त,
	पूर्ण;
	u32 addr;

	*chip_ret = शून्य;

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	chip->card = card;
	chip->pci = pci;
	chip->use_cache = use_cache;
	spin_lock_init(&chip->reg_lock);
	chip->irq = -1;
	mutex_init(&chip->irq_mutex);

	/* store buffer sizes in bytes */
	chip->streams[SNDRV_PCM_STREAM_PLAYBACK].bufsize = playback_bufsize * 1024;
	chip->streams[SNDRV_PCM_STREAM_CAPTURE].bufsize = capture_bufsize * 1024;

	/* 
	 * The NM256 has two memory ports.  The first port is nothing
	 * more than a chunk of video RAM, which is used as the I/O ring
	 * buffer.  The second port has the actual juicy stuff (like the
	 * mixer and the playback engine control रेजिस्टरs).
	 */

	chip->buffer_addr = pci_resource_start(pci, 0);
	chip->cport_addr = pci_resource_start(pci, 1);

	/* Init the memory port info.  */
	/* remap control port (#2) */
	chip->res_cport = request_mem_region(chip->cport_addr, NM_PORT2_SIZE,
					     card->driver);
	अगर (chip->res_cport == शून्य) अणु
		dev_err(card->dev, "memory region 0x%lx (size 0x%x) busy\n",
			   chip->cport_addr, NM_PORT2_SIZE);
		err = -EBUSY;
		जाओ __error;
	पूर्ण
	chip->cport = ioremap(chip->cport_addr, NM_PORT2_SIZE);
	अगर (chip->cport == शून्य) अणु
		dev_err(card->dev, "unable to map control port %lx\n",
			chip->cport_addr);
		err = -ENOMEM;
		जाओ __error;
	पूर्ण

	अगर (!म_भेद(card->driver, "NM256AV")) अणु
		/* Ok, try to see अगर this is a non-AC97 version of the hardware. */
		pval = snd_nm256_पढ़ोw(chip, NM_MIXER_PRESENCE);
		अगर ((pval & NM_PRESENCE_MASK) != NM_PRESENCE_VALUE) अणु
			अगर (! क्रमce_ac97) अणु
				dev_err(card->dev,
					"no ac97 is found!\n");
				dev_err(card->dev,
					"force the driver to load by passing in the module parameter\n");
				dev_err(card->dev,
					" force_ac97=1\n");
				dev_err(card->dev,
					"or try sb16, opl3sa2, or cs423x drivers instead.\n");
				err = -ENXIO;
				जाओ __error;
			पूर्ण
		पूर्ण
		chip->buffer_end = 2560 * 1024;
		chip->पूर्णांकerrupt = snd_nm256_पूर्णांकerrupt;
		chip->mixer_status_offset = NM_MIXER_STATUS_OFFSET;
		chip->mixer_status_mask = NM_MIXER_READY_MASK;
	पूर्ण अन्यथा अणु
		/* Not sure अगर there is any relevant detect क्रम the ZX or not.  */
		अगर (snd_nm256_पढ़ोb(chip, 0xa0b) != 0)
			chip->buffer_end = 6144 * 1024;
		अन्यथा
			chip->buffer_end = 4096 * 1024;

		chip->पूर्णांकerrupt = snd_nm256_पूर्णांकerrupt_zx;
		chip->mixer_status_offset = NM2_MIXER_STATUS_OFFSET;
		chip->mixer_status_mask = NM2_MIXER_READY_MASK;
	पूर्ण
	
	chip->buffer_size = chip->streams[SNDRV_PCM_STREAM_PLAYBACK].bufsize +
		chip->streams[SNDRV_PCM_STREAM_CAPTURE].bufsize;
	अगर (chip->use_cache)
		chip->buffer_size += NM_TOTAL_COEFF_COUNT * 4;
	अन्यथा
		chip->buffer_size += NM_MAX_PLAYBACK_COEF_SIZE + NM_MAX_RECORD_COEF_SIZE;

	अगर (buffer_top >= chip->buffer_size && buffer_top < chip->buffer_end)
		chip->buffer_end = buffer_top;
	अन्यथा अणु
		/* get buffer end poपूर्णांकer from signature */
		अगर ((err = snd_nm256_peek_क्रम_sig(chip)) < 0)
			जाओ __error;
	पूर्ण

	chip->buffer_start = chip->buffer_end - chip->buffer_size;
	chip->buffer_addr += chip->buffer_start;

	dev_info(card->dev, "Mapping port 1 from 0x%x - 0x%x\n",
	       chip->buffer_start, chip->buffer_end);

	chip->res_buffer = request_mem_region(chip->buffer_addr,
					      chip->buffer_size,
					      card->driver);
	अगर (chip->res_buffer == शून्य) अणु
		dev_err(card->dev, "buffer 0x%lx (size 0x%x) busy\n",
			   chip->buffer_addr, chip->buffer_size);
		err = -EBUSY;
		जाओ __error;
	पूर्ण
	chip->buffer = ioremap(chip->buffer_addr, chip->buffer_size);
	अगर (chip->buffer == शून्य) अणु
		err = -ENOMEM;
		dev_err(card->dev, "unable to map ring buffer at %lx\n",
			chip->buffer_addr);
		जाओ __error;
	पूर्ण

	/* set offsets */
	addr = chip->buffer_start;
	chip->streams[SNDRV_PCM_STREAM_PLAYBACK].buf = addr;
	addr += chip->streams[SNDRV_PCM_STREAM_PLAYBACK].bufsize;
	chip->streams[SNDRV_PCM_STREAM_CAPTURE].buf = addr;
	addr += chip->streams[SNDRV_PCM_STREAM_CAPTURE].bufsize;
	अगर (chip->use_cache) अणु
		chip->all_coeff_buf = addr;
	पूर्ण अन्यथा अणु
		chip->coeff_buf[SNDRV_PCM_STREAM_PLAYBACK] = addr;
		addr += NM_MAX_PLAYBACK_COEF_SIZE;
		chip->coeff_buf[SNDRV_PCM_STREAM_CAPTURE] = addr;
	पूर्ण

	/* Fixed setting. */
	chip->mixer_base = NM_MIXER_OFFSET;

	chip->coeffs_current = 0;

	snd_nm256_init_chip(chip);

	// pci_set_master(pci); /* needed? */
	
	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0)
		जाओ __error;

	*chip_ret = chip;
	वापस 0;

__error:
	snd_nm256_मुक्त(chip);
	वापस err;
पूर्ण


क्रमागत अणु NM_IGNORED, NM_RESET_WORKAROUND, NM_RESET_WORKAROUND_2 पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk nm256_quirks[] = अणु
	/* HP omnibook 4150 has cs4232 codec पूर्णांकernally */
	SND_PCI_QUIRK(0x103c, 0x0007, "HP omnibook 4150", NM_IGNORED),
	/* Reset workarounds to aव्योम lock-ups */
	SND_PCI_QUIRK(0x104d, 0x8041, "Sony PCG-F305", NM_RESET_WORKAROUND),
	SND_PCI_QUIRK(0x1028, 0x0080, "Dell Latitude LS", NM_RESET_WORKAROUND),
	SND_PCI_QUIRK(0x1028, 0x0091, "Dell Latitude CSx", NM_RESET_WORKAROUND_2),
	अणु पूर्ण /* terminator */
पूर्ण;


अटल पूर्णांक snd_nm256_probe(काष्ठा pci_dev *pci,
			   स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा snd_card *card;
	काष्ठा nm256 *chip;
	पूर्णांक err;
	स्थिर काष्ठा snd_pci_quirk *q;

	q = snd_pci_quirk_lookup(pci, nm256_quirks);
	अगर (q) अणु
		dev_dbg(&pci->dev, "Enabled quirk for %s.\n",
			    snd_pci_quirk_name(q));
		चयन (q->value) अणु
		हाल NM_IGNORED:
			dev_info(&pci->dev,
				 "The device is on the denylist. Loading stopped\n");
			वापस -ENODEV;
		हाल NM_RESET_WORKAROUND_2:
			reset_workaround_2 = 1;
			fallthrough;
		हाल NM_RESET_WORKAROUND:
			reset_workaround = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	err = snd_card_new(&pci->dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	चयन (pci->device) अणु
	हाल PCI_DEVICE_ID_NEOMAGIC_NM256AV_AUDIO:
		म_नकल(card->driver, "NM256AV");
		अवरोध;
	हाल PCI_DEVICE_ID_NEOMAGIC_NM256ZX_AUDIO:
		म_नकल(card->driver, "NM256ZX");
		अवरोध;
	हाल PCI_DEVICE_ID_NEOMAGIC_NM256XL_PLUS_AUDIO:
		म_नकल(card->driver, "NM256XL+");
		अवरोध;
	शेष:
		dev_err(&pci->dev, "invalid device id 0x%x\n", pci->device);
		snd_card_मुक्त(card);
		वापस -EINVAL;
	पूर्ण

	अगर (vaio_hack)
		buffer_top = 0x25a800;	/* this aव्योमs conflicts with XFree86 server */

	अगर (playback_bufsize < 4)
		playback_bufsize = 4;
	अगर (playback_bufsize > 128)
		playback_bufsize = 128;
	अगर (capture_bufsize < 4)
		capture_bufsize = 4;
	अगर (capture_bufsize > 128)
		capture_bufsize = 128;
	अगर ((err = snd_nm256_create(card, pci, &chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = chip;

	अगर (reset_workaround) अणु
		dev_dbg(&pci->dev, "reset_workaround activated\n");
		chip->reset_workaround = 1;
	पूर्ण

	अगर (reset_workaround_2) अणु
		dev_dbg(&pci->dev, "reset_workaround_2 activated\n");
		chip->reset_workaround_2 = 1;
	पूर्ण

	अगर ((err = snd_nm256_pcm(chip, 0)) < 0 ||
	    (err = snd_nm256_mixer(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	प्र_लिखो(card->लघुname, "NeoMagic %s", card->driver);
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx & 0x%lx, irq %d",
		card->लघुname,
		chip->buffer_addr, chip->cport_addr, chip->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	pci_set_drvdata(pci, card);
	वापस 0;
पूर्ण

अटल व्योम snd_nm256_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण


अटल काष्ठा pci_driver nm256_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_nm256_ids,
	.probe = snd_nm256_probe,
	.हटाओ = snd_nm256_हटाओ,
	.driver = अणु
		.pm = NM256_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(nm256_driver);
