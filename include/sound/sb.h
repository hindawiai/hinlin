<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_SB_H
#घोषणा __SOUND_SB_H

/*
 *  Header file क्रम SoundBlaster cards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

क्रमागत sb_hw_type अणु
	SB_HW_AUTO,
	SB_HW_10,
	SB_HW_20,
	SB_HW_201,
	SB_HW_PRO,
	SB_HW_JAZZ16,		/* Media Vision Jazz16 */
	SB_HW_16,
	SB_HW_16CSP,		/* SB16 with CSP chip */
	SB_HW_ALS100,		/* Avance Logic ALS100 chip */
	SB_HW_ALS4000,		/* Avance Logic ALS4000 chip */
	SB_HW_DT019X,		/* Diamond Tech. DT-019X / Avance Logic ALS-007 */
	SB_HW_CS5530,		/* Cyrix/NatSemi 5530 VSA1 */
पूर्ण;

#घोषणा SB_OPEN_PCM			0x01
#घोषणा SB_OPEN_MIDI_INPUT		0x02
#घोषणा SB_OPEN_MIDI_OUTPUT		0x04
#घोषणा SB_OPEN_MIDI_INPUT_TRIGGER	0x08
#घोषणा SB_OPEN_MIDI_OUTPUT_TRIGGER	0x10

#घोषणा SB_MODE_HALT		0x00
#घोषणा SB_MODE_PLAYBACK_8	0x01
#घोषणा SB_MODE_PLAYBACK_16	0x02
#घोषणा SB_MODE_PLAYBACK	(SB_MODE_PLAYBACK_8 | SB_MODE_PLAYBACK_16)
#घोषणा SB_MODE_CAPTURE_8	0x04
#घोषणा SB_MODE_CAPTURE_16	0x08
#घोषणा SB_MODE_CAPTURE		(SB_MODE_CAPTURE_8 | SB_MODE_CAPTURE_16)

#घोषणा SB_RATE_LOCK_PLAYBACK	0x10
#घोषणा SB_RATE_LOCK_CAPTURE	0x20
#घोषणा SB_RATE_LOCK		(SB_RATE_LOCK_PLAYBACK | SB_RATE_LOCK_CAPTURE)

#घोषणा SB_MPU_INPUT		1

काष्ठा snd_sb अणु
	अचिन्हित दीर्घ port;		/* base port of DSP chip */
	काष्ठा resource *res_port;
	अचिन्हित दीर्घ mpu_port;		/* MPU port क्रम SB DSP 4.0+ */
	पूर्णांक irq;			/* IRQ number of DSP chip */
	पूर्णांक dma8;			/* 8-bit DMA */
	पूर्णांक dma16;			/* 16-bit DMA */
	अचिन्हित लघु version;		/* version of DSP chip */
	क्रमागत sb_hw_type hardware;	/* see to SB_HW_XXXX */

	अचिन्हित दीर्घ alt_port;		/* alternate port (ALS4000) */
	काष्ठा pci_dev *pci;		/* ALS4000 */

	अचिन्हित पूर्णांक खोलो;		/* see to SB_OPEN_XXXX क्रम sb8 */
					/* also SNDRV_SB_CSP_MODE_XXX क्रम sb16_csp */
	अचिन्हित पूर्णांक mode;		/* current mode of stream */
	अचिन्हित पूर्णांक क्रमce_mode16;	/* क्रमce 16-bit mode of streams */
	अचिन्हित पूर्णांक locked_rate;	/* sb16 duplex */
	अचिन्हित पूर्णांक playback_क्रमmat;
	अचिन्हित पूर्णांक capture_क्रमmat;
	काष्ठा समयr_list midi_समयr;
	अचिन्हित पूर्णांक p_dma_size;
	अचिन्हित पूर्णांक p_period_size;
	अचिन्हित पूर्णांक c_dma_size;
	अचिन्हित पूर्णांक c_period_size;

	spinlock_t mixer_lock;

	अक्षर name[32];

	व्योम *csp; /* used only when CONFIG_SND_SB16_CSP is set */

	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *playback_substream;
	काष्ठा snd_pcm_substream *capture_substream;

	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *midi_substream_input;
	काष्ठा snd_rawmidi_substream *midi_substream_output;
	irq_handler_t rmidi_callback;

	spinlock_t reg_lock;
	spinlock_t खोलो_lock;
	spinlock_t midi_input_lock;

	काष्ठा snd_info_entry *proc_entry;

#अगर_घोषित CONFIG_PM
	अचिन्हित अक्षर saved_regs[0x20];
#पूर्ण_अगर
पूर्ण;

/* I/O ports */

#घोषणा SBP(chip, x)		((chip)->port + s_b_SB_##x)
#घोषणा SBP1(port, x)		((port) + s_b_SB_##x)

#घोषणा s_b_SB_RESET		0x6
#घोषणा s_b_SB_READ		0xa
#घोषणा s_b_SB_WRITE		0xc
#घोषणा s_b_SB_COMMAND		0xc
#घोषणा s_b_SB_STATUS		0xc
#घोषणा s_b_SB_DATA_AVAIL	0xe
#घोषणा s_b_SB_DATA_AVAIL_16 	0xf
#घोषणा s_b_SB_MIXER_ADDR	0x4
#घोषणा s_b_SB_MIXER_DATA	0x5
#घोषणा s_b_SB_OPL3_LEFT	0x0
#घोषणा s_b_SB_OPL3_RIGHT	0x2
#घोषणा s_b_SB_OPL3_BOTH	0x8

#घोषणा SB_DSP_OUTPUT		0x14
#घोषणा SB_DSP_INPUT		0x24
#घोषणा SB_DSP_BLOCK_SIZE	0x48
#घोषणा SB_DSP_HI_OUTPUT	0x91
#घोषणा SB_DSP_HI_INPUT		0x99
#घोषणा SB_DSP_LO_OUTPUT_AUTO	0x1c
#घोषणा SB_DSP_LO_INPUT_AUTO	0x2c
#घोषणा SB_DSP_HI_OUTPUT_AUTO	0x90
#घोषणा SB_DSP_HI_INPUT_AUTO	0x98
#घोषणा SB_DSP_IMMED_INT	0xf2
#घोषणा SB_DSP_GET_VERSION	0xe1
#घोषणा SB_DSP_SPEAKER_ON	0xd1
#घोषणा SB_DSP_SPEAKER_OFF	0xd3
#घोषणा SB_DSP_DMA8_OFF		0xd0
#घोषणा SB_DSP_DMA8_ON		0xd4
#घोषणा SB_DSP_DMA8_EXIT	0xda
#घोषणा SB_DSP_DMA16_OFF	0xd5
#घोषणा SB_DSP_DMA16_ON		0xd6
#घोषणा SB_DSP_DMA16_EXIT	0xd9
#घोषणा SB_DSP_SAMPLE_RATE	0x40
#घोषणा SB_DSP_SAMPLE_RATE_OUT	0x41
#घोषणा SB_DSP_SAMPLE_RATE_IN	0x42
#घोषणा SB_DSP_MONO_8BIT	0xa0
#घोषणा SB_DSP_MONO_16BIT	0xa4
#घोषणा SB_DSP_STEREO_8BIT	0xa8
#घोषणा SB_DSP_STEREO_16BIT	0xac

#घोषणा SB_DSP_MIDI_INPUT_IRQ	0x31
#घोषणा SB_DSP_MIDI_UART_IRQ	0x35
#घोषणा SB_DSP_MIDI_OUTPUT	0x38

#घोषणा SB_DSP4_OUT8_AI		0xc6
#घोषणा SB_DSP4_IN8_AI		0xce
#घोषणा SB_DSP4_OUT16_AI	0xb6
#घोषणा SB_DSP4_IN16_AI		0xbe
#घोषणा SB_DSP4_MODE_UNS_MONO	0x00
#घोषणा SB_DSP4_MODE_SIGN_MONO	0x10
#घोषणा SB_DSP4_MODE_UNS_STEREO	0x20
#घोषणा SB_DSP4_MODE_SIGN_STEREO 0x30

#घोषणा SB_DSP4_OUTPUT		0x3c
#घोषणा SB_DSP4_INPUT_LEFT	0x3d
#घोषणा SB_DSP4_INPUT_RIGHT	0x3e

/* रेजिस्टरs क्रम SB 2.0 mixer */
#घोषणा SB_DSP20_MASTER_DEV	0x02
#घोषणा SB_DSP20_PCM_DEV	0x0A
#घोषणा SB_DSP20_CD_DEV		0x08
#घोषणा SB_DSP20_FM_DEV		0x06

/* रेजिस्टरs क्रम SB PRO mixer */
#घोषणा SB_DSP_MASTER_DEV	0x22
#घोषणा SB_DSP_PCM_DEV		0x04
#घोषणा SB_DSP_LINE_DEV		0x2e
#घोषणा SB_DSP_CD_DEV		0x28
#घोषणा SB_DSP_FM_DEV		0x26
#घोषणा SB_DSP_MIC_DEV		0x0a
#घोषणा SB_DSP_CAPTURE_SOURCE	0x0c
#घोषणा SB_DSP_CAPTURE_FILT	0x0c
#घोषणा SB_DSP_PLAYBACK_FILT	0x0e
#घोषणा SB_DSP_STEREO_SW	0x0e

#घोषणा SB_DSP_MIXS_MIC0	0x00	/* same as MIC */
#घोषणा SB_DSP_MIXS_CD		0x01
#घोषणा SB_DSP_MIXS_MIC		0x02
#घोषणा SB_DSP_MIXS_LINE	0x03

/* रेजिस्टरs (only क्रम left channel) क्रम SB 16 mixer */
#घोषणा SB_DSP4_MASTER_DEV	0x30
#घोषणा SB_DSP4_BASS_DEV	0x46
#घोषणा SB_DSP4_TREBLE_DEV	0x44
#घोषणा SB_DSP4_SYNTH_DEV	0x34
#घोषणा SB_DSP4_PCM_DEV		0x32
#घोषणा SB_DSP4_SPEAKER_DEV	0x3b
#घोषणा SB_DSP4_LINE_DEV	0x38
#घोषणा SB_DSP4_MIC_DEV		0x3a
#घोषणा SB_DSP4_OUTPUT_SW	0x3c
#घोषणा SB_DSP4_CD_DEV		0x36
#घोषणा SB_DSP4_IGAIN_DEV	0x3f
#घोषणा SB_DSP4_OGAIN_DEV	0x41
#घोषणा SB_DSP4_MIC_AGC		0x43

/* additional रेजिस्टरs क्रम SB 16 mixer */
#घोषणा SB_DSP4_IRQSETUP	0x80
#घोषणा SB_DSP4_DMASETUP	0x81
#घोषणा SB_DSP4_IRQSTATUS	0x82
#घोषणा SB_DSP4_MPUSETUP	0x84

#घोषणा SB_DSP4_3DSE		0x90

/* Registers क्रम DT-019x / ALS-007 mixer */
#घोषणा SB_DT019X_MASTER_DEV	0x62
#घोषणा SB_DT019X_PCM_DEV	0x64
#घोषणा SB_DT019X_SYNTH_DEV	0x66
#घोषणा SB_DT019X_CD_DEV	0x68
#घोषणा SB_DT019X_MIC_DEV	0x6a
#घोषणा SB_DT019X_SPKR_DEV	0x6a
#घोषणा SB_DT019X_LINE_DEV	0x6e
#घोषणा SB_DT019X_OUTPUT_SW2	0x4c
#घोषणा SB_DT019X_CAPTURE_SW	0x6c

#घोषणा SB_DT019X_CAP_CD	0x02
#घोषणा SB_DT019X_CAP_MIC	0x04
#घोषणा SB_DT019X_CAP_LINE	0x06
#घोषणा SB_DT019X_CAP_SYNTH	0x07
#घोषणा SB_DT019X_CAP_MAIN	0x07

#घोषणा SB_ALS4000_MONO_IO_CTRL	0x4b
#घोषणा SB_ALS4000_OUT_MIXER_CTRL_2	0x4c
#घोषणा SB_ALS4000_MIC_IN_GAIN	0x4d
#घोषणा SB_ALS4000_ANALOG_REFRNC_VOLT_CTRL 0x4e
#घोषणा SB_ALS4000_FMDAC	0x4f
#घोषणा SB_ALS4000_3D_SND_FX	0x50
#घोषणा SB_ALS4000_3D_TIME_DELAY	0x51
#घोषणा SB_ALS4000_3D_AUTO_MUTE	0x52
#घोषणा SB_ALS4000_ANALOG_BLOCK_CTRL 0x53
#घोषणा SB_ALS4000_3D_DELAYLINE_PATTERN 0x54
#घोषणा SB_ALS4000_CR3_CONFIGURATION	0xc3 /* bit 7 is Digital Loop Enable */
#घोषणा SB_ALS4000_QSOUND	0xdb

/* IRQ setting biपंचांगap */
#घोषणा SB_IRQSETUP_IRQ9	0x01
#घोषणा SB_IRQSETUP_IRQ5	0x02
#घोषणा SB_IRQSETUP_IRQ7	0x04
#घोषणा SB_IRQSETUP_IRQ10	0x08

/* IRQ types */
#घोषणा SB_IRQTYPE_8BIT		0x01
#घोषणा SB_IRQTYPE_16BIT	0x02
#घोषणा SB_IRQTYPE_MPUIN	0x04
#घोषणा ALS4K_IRQTYPE_CR1E_DMA	0x20

/* DMA setting biपंचांगap */
#घोषणा SB_DMASETUP_DMA0	0x01
#घोषणा SB_DMASETUP_DMA1	0x02
#घोषणा SB_DMASETUP_DMA3	0x08
#घोषणा SB_DMASETUP_DMA5	0x20
#घोषणा SB_DMASETUP_DMA6	0x40
#घोषणा SB_DMASETUP_DMA7	0x80

/*
 *
 */

अटल अंतरभूत व्योम snd_sb_ack_8bit(काष्ठा snd_sb *chip)
अणु
	inb(SBP(chip, DATA_AVAIL));
पूर्ण

अटल अंतरभूत व्योम snd_sb_ack_16bit(काष्ठा snd_sb *chip)
अणु
	inb(SBP(chip, DATA_AVAIL_16));
पूर्ण

/* sb_common.c */
पूर्णांक snd_sbdsp_command(काष्ठा snd_sb *chip, अचिन्हित अक्षर val);
पूर्णांक snd_sbdsp_get_byte(काष्ठा snd_sb *chip);
पूर्णांक snd_sbdsp_reset(काष्ठा snd_sb *chip);
पूर्णांक snd_sbdsp_create(काष्ठा snd_card *card,
		     अचिन्हित दीर्घ port,
		     पूर्णांक irq,
		     irq_handler_t irq_handler,
		     पूर्णांक dma8, पूर्णांक dma16,
		     अचिन्हित लघु hardware,
		     काष्ठा snd_sb **r_chip);
/* sb_mixer.c */
व्योम snd_sbmixer_ग_लिखो(काष्ठा snd_sb *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर data);
अचिन्हित अक्षर snd_sbmixer_पढ़ो(काष्ठा snd_sb *chip, अचिन्हित अक्षर reg);
पूर्णांक snd_sbmixer_new(काष्ठा snd_sb *chip);
#अगर_घोषित CONFIG_PM
व्योम snd_sbmixer_suspend(काष्ठा snd_sb *chip);
व्योम snd_sbmixer_resume(काष्ठा snd_sb *chip);
#पूर्ण_अगर

/* sb8_init.c */
पूर्णांक snd_sb8dsp_pcm(काष्ठा snd_sb *chip, पूर्णांक device);
/* sb8.c */
irqवापस_t snd_sb8dsp_पूर्णांकerrupt(काष्ठा snd_sb *chip);
पूर्णांक snd_sb8_playback_खोलो(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_sb8_capture_खोलो(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_sb8_playback_बंद(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_sb8_capture_बंद(काष्ठा snd_pcm_substream *substream);
/* midi8.c */
irqवापस_t snd_sb8dsp_midi_पूर्णांकerrupt(काष्ठा snd_sb *chip);
पूर्णांक snd_sb8dsp_midi(काष्ठा snd_sb *chip, पूर्णांक device);

/* sb16_init.c */
पूर्णांक snd_sb16dsp_pcm(काष्ठा snd_sb *chip, पूर्णांक device);
स्थिर काष्ठा snd_pcm_ops *snd_sb16dsp_get_pcm_ops(पूर्णांक direction);
पूर्णांक snd_sb16dsp_configure(काष्ठा snd_sb *chip);
/* sb16.c */
irqवापस_t snd_sb16dsp_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

/* exported mixer stuffs */
क्रमागत अणु
	SB_MIX_SINGLE,
	SB_MIX_DOUBLE,
	SB_MIX_INPUT_SW,
	SB_MIX_CAPTURE_PRO,
	SB_MIX_CAPTURE_DT019X,
	SB_MIX_MONO_CAPTURE_ALS4K
पूर्ण;

#घोषणा SB_MIXVAL_DOUBLE(left_reg, right_reg, left_shअगरt, right_shअगरt, mask) \
  ((left_reg) | ((right_reg) << 8) | ((left_shअगरt) << 16) | ((right_shअगरt) << 19) | ((mask) << 24))
#घोषणा SB_MIXVAL_SINGLE(reg, shअगरt, mask) \
  ((reg) | ((shअगरt) << 16) | ((mask) << 24))
#घोषणा SB_MIXVAL_INPUT_SW(reg1, reg2, left_shअगरt, right_shअगरt) \
  ((reg1) | ((reg2) << 8) | ((left_shअगरt) << 16) | ((right_shअगरt) << 24))

पूर्णांक snd_sbmixer_add_ctl(काष्ठा snd_sb *chip, स्थिर अक्षर *name, पूर्णांक index, पूर्णांक type, अचिन्हित दीर्घ value);

/* क्रम ease of use */
काष्ठा sbmix_elem अणु
	स्थिर अक्षर *name;
	पूर्णांक type;
	अचिन्हित दीर्घ निजी_value;
पूर्ण;

#घोषणा SB_SINGLE(xname, reg, shअगरt, mask) \
अणु .name = xname, \
  .type = SB_MIX_SINGLE, \
  .निजी_value = SB_MIXVAL_SINGLE(reg, shअगरt, mask) पूर्ण

#घोषणा SB_DOUBLE(xname, left_reg, right_reg, left_shअगरt, right_shअगरt, mask) \
अणु .name = xname, \
  .type = SB_MIX_DOUBLE, \
  .निजी_value = SB_MIXVAL_DOUBLE(left_reg, right_reg, left_shअगरt, right_shअगरt, mask) पूर्ण

#घोषणा SB16_INPUT_SW(xname, reg1, reg2, left_shअगरt, right_shअगरt) \
अणु .name = xname, \
  .type = SB_MIX_INPUT_SW, \
  .निजी_value = SB_MIXVAL_INPUT_SW(reg1, reg2, left_shअगरt, right_shअगरt) पूर्ण

अटल अंतरभूत पूर्णांक snd_sbmixer_add_ctl_elem(काष्ठा snd_sb *chip, स्थिर काष्ठा sbmix_elem *c)
अणु
	वापस snd_sbmixer_add_ctl(chip, c->name, 0, c->type, c->निजी_value);
पूर्ण

#पूर्ण_अगर /* __SOUND_SB_H */
