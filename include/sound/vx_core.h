<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Digigram VX soundcards
 *
 * Hardware core part
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SOUND_VX_COMMON_H
#घोषणा __SOUND_VX_COMMON_H

#समावेश <sound/pcm.h>
#समावेश <sound/hwdep.h>
#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा firmware;
काष्ठा device;

#घोषणा VX_DRIVER_VERSION	0x010000	/* 1.0.0 */

/*
 */
#घोषणा SIZE_MAX_CMD    0x10
#घोषणा SIZE_MAX_STATUS 0x10

काष्ठा vx_rmh अणु
	u16	LgCmd;		/* length of the command to send (WORDs) */
	u16	LgStat;		/* length of the status received (WORDs) */
	u32	Cmd[SIZE_MAX_CMD];
	u32	Stat[SIZE_MAX_STATUS];
	u16	DspStat;	/* status type, RMP_SSIZE_XXX */
पूर्ण;
	
प्रकार u64 pcx_समय_प्रकार;

#घोषणा VX_MAX_PIPES	16
#घोषणा VX_MAX_PERIODS	32
#घोषणा VX_MAX_CODECS	2

काष्ठा vx_ibl_info अणु
	पूर्णांक size;	/* the current IBL size (0 = query) in bytes */
	पूर्णांक max_size;	/* max. IBL size in bytes */
	पूर्णांक min_size;	/* min. IBL size in bytes */
	पूर्णांक granularity;	/* granularity */
पूर्ण;

काष्ठा vx_pipe अणु
	पूर्णांक number;
	अचिन्हित पूर्णांक is_capture: 1;
	अचिन्हित पूर्णांक data_mode: 1;
	अचिन्हित पूर्णांक running: 1;
	अचिन्हित पूर्णांक prepared: 1;
	पूर्णांक channels;
	अचिन्हित पूर्णांक dअगरfered_type;
	pcx_समय_प्रकार pcx_समय;
	काष्ठा snd_pcm_substream *substream;

	पूर्णांक hbuf_size;		/* H-buffer size in bytes */
	पूर्णांक buffer_bytes;	/* the ALSA pcm buffer size in bytes */
	पूर्णांक period_bytes;	/* the ALSA pcm period size in bytes */
	पूर्णांक hw_ptr;		/* the current hardware poपूर्णांकer in bytes */
	पूर्णांक position;		/* the current position in frames (playback only) */
	पूर्णांक transferred;	/* the transferred size (per period) in frames */
	पूर्णांक align;		/* size of alignment */
	u64 cur_count;		/* current sample position (क्रम playback) */

	अचिन्हित पूर्णांक references;     /* an output pipe may be used क्रम monitoring and/or playback */
	काष्ठा vx_pipe *monitoring_pipe;  /* poपूर्णांकer to the monitoring pipe (capture pipe only)*/
पूर्ण;

काष्ठा vx_core;

काष्ठा snd_vx_ops अणु
	/* low-level i/o */
	अचिन्हित अक्षर (*in8)(काष्ठा vx_core *chip, पूर्णांक reg);
	अचिन्हित पूर्णांक (*in32)(काष्ठा vx_core *chip, पूर्णांक reg);
	व्योम (*out8)(काष्ठा vx_core *chip, पूर्णांक reg, अचिन्हित अक्षर val);
	व्योम (*out32)(काष्ठा vx_core *chip, पूर्णांक reg, अचिन्हित पूर्णांक val);
	/* irq */
	पूर्णांक (*test_and_ack)(काष्ठा vx_core *chip);
	व्योम (*validate_irq)(काष्ठा vx_core *chip, पूर्णांक enable);
	/* codec */
	व्योम (*ग_लिखो_codec)(काष्ठा vx_core *chip, पूर्णांक codec, अचिन्हित पूर्णांक data);
	व्योम (*akm_ग_लिखो)(काष्ठा vx_core *chip, पूर्णांक reg, अचिन्हित पूर्णांक data);
	व्योम (*reset_codec)(काष्ठा vx_core *chip);
	व्योम (*change_audio_source)(काष्ठा vx_core *chip, पूर्णांक src);
	व्योम (*set_घड़ी_source)(काष्ठा vx_core *chp, पूर्णांक src);
	/* chip init */
	पूर्णांक (*load_dsp)(काष्ठा vx_core *chip, पूर्णांक idx, स्थिर काष्ठा firmware *fw);
	व्योम (*reset_dsp)(काष्ठा vx_core *chip);
	व्योम (*reset_board)(काष्ठा vx_core *chip, पूर्णांक cold_reset);
	पूर्णांक (*add_controls)(काष्ठा vx_core *chip);
	/* pcm */
	व्योम (*dma_ग_लिखो)(काष्ठा vx_core *chip, काष्ठा snd_pcm_runसमय *runसमय,
			  काष्ठा vx_pipe *pipe, पूर्णांक count);
	व्योम (*dma_पढ़ो)(काष्ठा vx_core *chip, काष्ठा snd_pcm_runसमय *runसमय,
			  काष्ठा vx_pipe *pipe, पूर्णांक count);
पूर्ण;

काष्ठा snd_vx_hardware अणु
	स्थिर अक्षर *name;
	पूर्णांक type;	/* VX_TYPE_XXX */

	/* hardware specs */
	अचिन्हित पूर्णांक num_codecs;
	अचिन्हित पूर्णांक num_ins;
	अचिन्हित पूर्णांक num_outs;
	अचिन्हित पूर्णांक output_level_max;
	स्थिर अचिन्हित पूर्णांक *output_level_db_scale;
पूर्ण;

/* hwdep id string */
#घोषणा SND_VX_HWDEP_ID		"VX Loader"

/* hardware type */
क्रमागत अणु
	/* VX222 PCI */
	VX_TYPE_BOARD,		/* old VX222 PCI */
	VX_TYPE_V2,		/* VX222 V2 PCI */
	VX_TYPE_MIC,		/* VX222 Mic PCI */
	/* VX-pocket */
	VX_TYPE_VXPOCKET,	/* VXpocket V2 */
	VX_TYPE_VXP440,		/* VXpocket 440 */
	VX_TYPE_NUMS
पूर्ण;

/* chip status */
क्रमागत अणु
	VX_STAT_XILINX_LOADED	= (1 << 0),	/* devices are रेजिस्टरed */
	VX_STAT_DEVICE_INIT	= (1 << 1),	/* devices are रेजिस्टरed */
	VX_STAT_CHIP_INIT	= (1 << 2),	/* all operational */
	VX_STAT_IN_SUSPEND	= (1 << 10),	/* in suspend phase */
	VX_STAT_IS_STALE	= (1 << 15)	/* device is stale */
पूर्ण;

/* min/max values क्रम analog output क्रम old codecs */
#घोषणा VX_ANALOG_OUT_LEVEL_MAX		0xe3

काष्ठा vx_core अणु
	/* ALSA stuff */
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm[VX_MAX_CODECS];
	पूर्णांक type;	/* VX_TYPE_XXX */

	पूर्णांक irq;
	/* ports are defined बाह्यally */

	/* low-level functions */
	स्थिर काष्ठा snd_vx_hardware *hw;
	स्थिर काष्ठा snd_vx_ops *ops;

	काष्ठा mutex lock;

	अचिन्हित पूर्णांक chip_status;
	अचिन्हित पूर्णांक pcm_running;

	काष्ठा device *dev;
	काष्ठा snd_hwdep *hwdep;

	काष्ठा vx_rmh irq_rmh;	/* RMH used in पूर्णांकerrupts */

	अचिन्हित पूर्णांक audio_info; /* see VX_AUDIO_INFO */
	अचिन्हित पूर्णांक audio_ins;
	अचिन्हित पूर्णांक audio_outs;
	काष्ठा vx_pipe **playback_pipes;
	काष्ठा vx_pipe **capture_pipes;

	/* घड़ी and audio sources */
	अचिन्हित पूर्णांक audio_source;	/* current audio input source */
	अचिन्हित पूर्णांक audio_source_target;
	अचिन्हित पूर्णांक घड़ी_mode;	/* घड़ी mode (VX_CLOCK_MODE_XXX) */
	अचिन्हित पूर्णांक घड़ी_source;	/* current घड़ी source (INTERNAL_QUARTZ or UER_SYNC) */
	अचिन्हित पूर्णांक freq;		/* current frequency */
	अचिन्हित पूर्णांक freq_detected;	/* detected frequency from digital in */
	अचिन्हित पूर्णांक uer_detected;	/* VX_UER_MODE_XXX */
	अचिन्हित पूर्णांक uer_bits;	/* IEC958 status bits */
	काष्ठा vx_ibl_info ibl;	/* IBL inक्रमmation */

	/* mixer setting */
	पूर्णांक output_level[VX_MAX_CODECS][2];	/* analog output level */
	पूर्णांक audio_gain[2][4];			/* digital audio level (playback/capture) */
	अचिन्हित अक्षर audio_active[4];		/* mute/unmute on digital playback */
	पूर्णांक audio_monitor[4];			/* playback hw-monitor level */
	अचिन्हित अक्षर audio_monitor_active[4];	/* playback hw-monitor mute/unmute */

	काष्ठा mutex mixer_mutex;

	स्थिर काष्ठा firmware *firmware[4]; /* loaded firmware data */
पूर्ण;


/*
 * स्थिरructor
 */
काष्ठा vx_core *snd_vx_create(काष्ठा snd_card *card,
			      स्थिर काष्ठा snd_vx_hardware *hw,
			      स्थिर काष्ठा snd_vx_ops *ops, पूर्णांक extra_size);
पूर्णांक snd_vx_setup_firmware(काष्ठा vx_core *chip);
पूर्णांक snd_vx_load_boot_image(काष्ठा vx_core *chip, स्थिर काष्ठा firmware *dsp);
पूर्णांक snd_vx_dsp_boot(काष्ठा vx_core *chip, स्थिर काष्ठा firmware *dsp);
पूर्णांक snd_vx_dsp_load(काष्ठा vx_core *chip, स्थिर काष्ठा firmware *dsp);

व्योम snd_vx_मुक्त_firmware(काष्ठा vx_core *chip);

/*
 * पूर्णांकerrupt handler; exported क्रम pcmcia
 */
irqवापस_t snd_vx_irq_handler(पूर्णांक irq, व्योम *dev);
irqवापस_t snd_vx_thपढ़ोed_irq_handler(पूर्णांक irq, व्योम *dev);

/*
 * lowlevel functions
 */
अटल अंतरभूत पूर्णांक vx_test_and_ack(काष्ठा vx_core *chip)
अणु
	वापस chip->ops->test_and_ack(chip);
पूर्ण

अटल अंतरभूत व्योम vx_validate_irq(काष्ठा vx_core *chip, पूर्णांक enable)
अणु
	chip->ops->validate_irq(chip, enable);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर snd_vx_inb(काष्ठा vx_core *chip, पूर्णांक reg)
अणु
	वापस chip->ops->in8(chip, reg);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_vx_inl(काष्ठा vx_core *chip, पूर्णांक reg)
अणु
	वापस chip->ops->in32(chip, reg);
पूर्ण

अटल अंतरभूत व्योम snd_vx_outb(काष्ठा vx_core *chip, पूर्णांक reg, अचिन्हित अक्षर val)
अणु
	chip->ops->out8(chip, reg, val);
पूर्ण

अटल अंतरभूत व्योम snd_vx_outl(काष्ठा vx_core *chip, पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	chip->ops->out32(chip, reg, val);
पूर्ण

#घोषणा vx_inb(chip,reg)	snd_vx_inb(chip, VX_##reg)
#घोषणा vx_outb(chip,reg,val)	snd_vx_outb(chip, VX_##reg,val)
#घोषणा vx_inl(chip,reg)	snd_vx_inl(chip, VX_##reg)
#घोषणा vx_outl(chip,reg,val)	snd_vx_outl(chip, VX_##reg,val)

अटल अंतरभूत व्योम vx_reset_dsp(काष्ठा vx_core *chip)
अणु
	chip->ops->reset_dsp(chip);
पूर्ण

पूर्णांक vx_send_msg(काष्ठा vx_core *chip, काष्ठा vx_rmh *rmh);
पूर्णांक vx_send_msg_nolock(काष्ठा vx_core *chip, काष्ठा vx_rmh *rmh);
पूर्णांक vx_send_rih(काष्ठा vx_core *chip, पूर्णांक cmd);
पूर्णांक vx_send_rih_nolock(काष्ठा vx_core *chip, पूर्णांक cmd);

व्योम vx_reset_codec(काष्ठा vx_core *chip, पूर्णांक cold_reset);

/*
 * check the bit on the specअगरied रेजिस्टर
 * वापसs zero अगर a bit matches, or a negative error code.
 * exported क्रम vxpocket driver
 */
पूर्णांक snd_vx_check_reg_bit(काष्ठा vx_core *chip, पूर्णांक reg, पूर्णांक mask, पूर्णांक bit, पूर्णांक समय);
#घोषणा vx_check_isr(chip,mask,bit,समय) snd_vx_check_reg_bit(chip, VX_ISR, mask, bit, समय)
#घोषणा vx_रुको_isr_bit(chip,bit) vx_check_isr(chip, bit, bit, 200)
#घोषणा vx_रुको_क्रम_rx_full(chip) vx_रुको_isr_bit(chip, ISR_RX_FULL)


/*
 * pseuकरो-DMA transfer
 */
अटल अंतरभूत व्योम vx_pseuकरो_dma_ग_लिखो(काष्ठा vx_core *chip, काष्ठा snd_pcm_runसमय *runसमय,
				       काष्ठा vx_pipe *pipe, पूर्णांक count)
अणु
	chip->ops->dma_ग_लिखो(chip, runसमय, pipe, count);
पूर्ण

अटल अंतरभूत व्योम vx_pseuकरो_dma_पढ़ो(काष्ठा vx_core *chip, काष्ठा snd_pcm_runसमय *runसमय,
				      काष्ठा vx_pipe *pipe, पूर्णांक count)
अणु
	chip->ops->dma_पढ़ो(chip, runसमय, pipe, count);
पूर्ण



/* error with hardware code,
 * the वापस value is -(VX_ERR_MASK | actual-hw-error-code)
 */
#घोषणा VX_ERR_MASK	0x1000000
#घोषणा vx_get_error(err)	(-(err) & ~VX_ERR_MASK)


/*
 * pcm stuff
 */
पूर्णांक snd_vx_pcm_new(काष्ठा vx_core *chip);
व्योम vx_pcm_update_पूर्णांकr(काष्ठा vx_core *chip, अचिन्हित पूर्णांक events);

/*
 * mixer stuff
 */
पूर्णांक snd_vx_mixer_new(काष्ठा vx_core *chip);
व्योम vx_toggle_dac_mute(काष्ठा vx_core *chip, पूर्णांक mute);
पूर्णांक vx_sync_audio_source(काष्ठा vx_core *chip);
पूर्णांक vx_set_monitor_level(काष्ठा vx_core *chip, पूर्णांक audio, पूर्णांक level, पूर्णांक active);

/*
 * IEC958 & घड़ी stuff
 */
व्योम vx_set_iec958_status(काष्ठा vx_core *chip, अचिन्हित पूर्णांक bits);
पूर्णांक vx_set_घड़ी(काष्ठा vx_core *chip, अचिन्हित पूर्णांक freq);
व्योम vx_set_पूर्णांकernal_घड़ी(काष्ठा vx_core *chip, अचिन्हित पूर्णांक freq);
पूर्णांक vx_change_frequency(काष्ठा vx_core *chip);


/*
 * PM
 */
पूर्णांक snd_vx_suspend(काष्ठा vx_core *card);
पूर्णांक snd_vx_resume(काष्ठा vx_core *card);

/*
 * hardware स्थिरants
 */

#घोषणा vx_has_new_dsp(chip)	((chip)->type != VX_TYPE_BOARD)
#घोषणा vx_is_pcmcia(chip)	((chip)->type >= VX_TYPE_VXPOCKET)

/* audio input source */
क्रमागत अणु
	VX_AUDIO_SRC_DIGITAL,
	VX_AUDIO_SRC_LINE,
	VX_AUDIO_SRC_MIC
पूर्ण;

/* घड़ी source */
क्रमागत अणु
	INTERNAL_QUARTZ,
	UER_SYNC
पूर्ण;

/* घड़ी mode */
क्रमागत अणु
	VX_CLOCK_MODE_AUTO,	/* depending on the current audio source */
	VX_CLOCK_MODE_INTERNAL,	/* fixed to पूर्णांकernal quartz */
	VX_CLOCK_MODE_EXTERNAL	/* fixed to UER sync */
पूर्ण;

/* SPDIF/UER type */
क्रमागत अणु
	VX_UER_MODE_CONSUMER,
	VX_UER_MODE_PROFESSIONAL,
	VX_UER_MODE_NOT_PRESENT,
पूर्ण;

/* रेजिस्टर indices */
क्रमागत अणु
	VX_ICR,
	VX_CVR,
	VX_ISR,
	VX_IVR,
	VX_RXH,
	VX_TXH = VX_RXH,
	VX_RXM,
	VX_TXM = VX_RXM,
	VX_RXL,
	VX_TXL = VX_RXL,
	VX_DMA,
	VX_CDSP,
	VX_RFREQ,
	VX_RUER_V2,
	VX_GAIN,
	VX_DATA = VX_GAIN,
	VX_MEMIRQ,
	VX_ACQ,
	VX_BIT0,
	VX_BIT1,
	VX_MIC0,
	VX_MIC1,
	VX_MIC2,
	VX_MIC3,
	VX_PLX0,
	VX_PLX1,
	VX_PLX2,

	VX_LOFREQ,  // V2: ACQ, VP: RFREQ
	VX_HIFREQ,  // V2: BIT0, VP: RUER_V2
	VX_CSUER,   // V2: BIT1, VP: BIT0
	VX_RUER,    // V2: RUER_V2, VP: BIT1

	VX_REG_MAX,

	/* aliases क्रम VX board */
	VX_RESET_DMA = VX_ISR,
	VX_CFG = VX_RFREQ,
	VX_STATUS = VX_MEMIRQ,
	VX_SELMIC = VX_MIC0,
	VX_COMPOT = VX_MIC1,
	VX_SCOMPR = VX_MIC2,
	VX_GLIMIT = VX_MIC3,
	VX_INTCSR = VX_PLX0,
	VX_CNTRL = VX_PLX1,
	VX_GPIOC = VX_PLX2,

	/* aliases क्रम VXPOCKET board */
	VX_MICRO = VX_MEMIRQ,
	VX_CODEC2 = VX_MEMIRQ,
	VX_DIALOG = VX_ACQ,

पूर्ण;

/* RMH status type */
क्रमागत अणु
	RMH_SSIZE_FIXED = 0,	/* status size given by the driver (in LgStat) */
	RMH_SSIZE_ARG = 1,	/* status size given in the LSB byte */
	RMH_SSIZE_MASK = 2,	/* status size given in biपंचांगask */
पूर्ण;


/* bits क्रम ICR रेजिस्टर */
#घोषणा ICR_HF1		0x10
#घोषणा ICR_HF0		0x08
#घोषणा ICR_TREQ	0x02	/* Interrupt mode + HREQ set on क्रम transfer (->DSP) request */
#घोषणा ICR_RREQ	0x01	/* Interrupt mode + RREQ set on क्रम transfer (->PC) request */

/* bits क्रम CVR रेजिस्टर */
#घोषणा CVR_HC		0x80

/* bits क्रम ISR रेजिस्टर */
#घोषणा ISR_HF3		0x10
#घोषणा ISR_HF2		0x08
#घोषणा ISR_CHK		0x10
#घोषणा ISR_ERR		0x08
#घोषणा ISR_TX_READY	0x04
#घोषणा ISR_TX_EMPTY	0x02
#घोषणा ISR_RX_FULL	0x01

/* Constants used to access the DATA रेजिस्टर */
#घोषणा VX_DATA_CODEC_MASK	0x80
#घोषणा VX_DATA_XICOR_MASK	0x80

/* Constants used to access the CSUER रेजिस्टर (both क्रम VX2 and VXP) */
#घोषणा VX_SUER_FREQ_MASK		0x0c
#घोषणा VX_SUER_FREQ_32KHz_MASK		0x0c
#घोषणा VX_SUER_FREQ_44KHz_MASK		0x00
#घोषणा VX_SUER_FREQ_48KHz_MASK		0x04
#घोषणा VX_SUER_DATA_PRESENT_MASK	0x02
#घोषणा VX_SUER_CLOCK_PRESENT_MASK	0x01

#घोषणा VX_CUER_HH_BITC_SEL_MASK	0x08
#घोषणा VX_CUER_MH_BITC_SEL_MASK	0x04
#घोषणा VX_CUER_ML_BITC_SEL_MASK	0x02
#घोषणा VX_CUER_LL_BITC_SEL_MASK	0x01

#घोषणा XX_UER_CBITS_OFFSET_MASK	0x1f


/* bits क्रम audio_info */
#घोषणा VX_AUDIO_INFO_REAL_TIME	(1<<0)	/* real-समय processing available */
#घोषणा VX_AUDIO_INFO_OFFLINE	(1<<1)	/* offline processing available */
#घोषणा VX_AUDIO_INFO_MPEG1	(1<<5)
#घोषणा VX_AUDIO_INFO_MPEG2	(1<<6)
#घोषणा VX_AUDIO_INFO_LINEAR_8	(1<<7)
#घोषणा VX_AUDIO_INFO_LINEAR_16	(1<<8)
#घोषणा VX_AUDIO_INFO_LINEAR_24	(1<<9)

/* DSP Interrupt Request values */
#घोषणा VXP_IRQ_OFFSET		0x40 /* add 0x40 offset क्रम vxpocket and vx222/v2 */
/* call with vx_send_irq_dsp() */
#घोषणा IRQ_MESS_WRITE_END          0x30
#घोषणा IRQ_MESS_WRITE_NEXT         0x32
#घोषणा IRQ_MESS_READ_NEXT          0x34
#घोषणा IRQ_MESS_READ_END           0x36
#घोषणा IRQ_MESSAGE                 0x38
#घोषणा IRQ_RESET_CHK               0x3A
#घोषणा IRQ_CONNECT_STREAM_NEXT     0x26
#घोषणा IRQ_CONNECT_STREAM_END      0x28
#घोषणा IRQ_PAUSE_START_CONNECT     0x2A
#घोषणा IRQ_END_CONNECTION          0x2C

/* Is there async. events pending ( IT Source Test ) */
#घोषणा ASYNC_EVENTS_PENDING            0x008000
#घोषणा HBUFFER_EVENTS_PENDING          0x004000   // Not always accurate
#घोषणा NOTIF_EVENTS_PENDING            0x002000
#घोषणा TIME_CODE_EVENT_PENDING         0x001000
#घोषणा FREQUENCY_CHANGE_EVENT_PENDING  0x000800
#घोषणा END_OF_BUFFER_EVENTS_PENDING    0x000400
#घोषणा FATAL_DSP_ERROR                 0xff0000

/* Stream Format Header Defines */ 
#घोषणा HEADER_FMT_BASE			0xFED00000
#घोषणा HEADER_FMT_MONO			0x000000C0
#घोषणा HEADER_FMT_INTEL		0x00008000
#घोषणा HEADER_FMT_16BITS		0x00002000
#घोषणा HEADER_FMT_24BITS		0x00004000
#घोषणा HEADER_FMT_UPTO11		0x00000200	/* frequency is less or equ. to 11k.*/
#घोषणा HEADER_FMT_UPTO32		0x00000100	/* frequency is over 11k and less then 32k.*/

/* Constants used to access the Codec */
#घोषणा XX_CODEC_SELECTOR               0x20
/* codec commands */
#घोषणा XX_CODEC_ADC_CONTROL_REGISTER   0x01
#घोषणा XX_CODEC_DAC_CONTROL_REGISTER   0x02
#घोषणा XX_CODEC_LEVEL_LEFT_REGISTER    0x03
#घोषणा XX_CODEC_LEVEL_RIGHT_REGISTER   0x04
#घोषणा XX_CODEC_PORT_MODE_REGISTER     0x05
#घोषणा XX_CODEC_STATUS_REPORT_REGISTER 0x06
#घोषणा XX_CODEC_CLOCK_CONTROL_REGISTER 0x07

/*
 * Audio-level control values
 */
#घोषणा CVAL_M110DB		0x000	/* -110dB */
#घोषणा CVAL_M99DB		0x02C
#घोषणा CVAL_M21DB		0x163
#घोषणा CVAL_M18DB		0x16F
#घोषणा CVAL_M10DB		0x18F
#घोषणा CVAL_0DB		0x1B7
#घोषणा CVAL_18DB		0x1FF	/* +18dB */
#घोषणा CVAL_MAX		0x1FF

#घोषणा AUDIO_IO_HAS_MUTE_LEVEL			0x400000
#घोषणा AUDIO_IO_HAS_MUTE_MONITORING_1		0x200000
#घोषणा AUDIO_IO_HAS_MUTE_MONITORING_2		0x100000
#घोषणा VALID_AUDIO_IO_DIGITAL_LEVEL		0x01
#घोषणा VALID_AUDIO_IO_MONITORING_LEVEL		0x02
#घोषणा VALID_AUDIO_IO_MUTE_LEVEL		0x04
#घोषणा VALID_AUDIO_IO_MUTE_MONITORING_1	0x08
#घोषणा VALID_AUDIO_IO_MUTE_MONITORING_2	0x10


#पूर्ण_अगर /* __SOUND_VX_COMMON_H */
