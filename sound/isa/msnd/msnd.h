<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*********************************************************************
 *
 * msnd.h
 *
 * Turtle Beach MultiSound Sound Card Driver क्रम Linux
 *
 * Some parts of this header file were derived from the Turtle Beach
 * MultiSound Driver Development Kit.
 *
 * Copyright (C) 1998 Andrew Veliath
 * Copyright (C) 1993 Turtle Beach Systems, Inc.
 *
 ********************************************************************/
#अगर_अघोषित __MSND_H
#घोषणा __MSND_H

#घोषणा DEFSAMPLERATE		44100
#घोषणा DEFSAMPLESIZE		SNDRV_PCM_FORMAT_S16
#घोषणा DEFCHANNELS		1

#घोषणा SRAM_BANK_SIZE		0x8000
#घोषणा SRAM_CNTL_START		0x7F00
#घोषणा SMA_STRUCT_START	0x7F40

#घोषणा DSP_BASE_ADDR		0x4000
#घोषणा DSP_BANK_BASE		0x4000

#घोषणा AGND			0x01
#घोषणा SIGNAL			0x02

#घोषणा EXT_DSP_BIT_DCAL	0x0001
#घोषणा EXT_DSP_BIT_MIDI_CON	0x0002

#घोषणा BUFFSIZE		0x8000
#घोषणा HOSTQ_SIZE		0x40

#घोषणा DAP_BUFF_SIZE		0x2400

#घोषणा DAPQ_STRUCT_SIZE	0x10
#घोषणा DARQ_STRUCT_SIZE	0x10
#घोषणा DAPQ_BUFF_SIZE		(3 * 0x10)
#घोषणा DARQ_BUFF_SIZE		(3 * 0x10)
#घोषणा MODQ_BUFF_SIZE		0x400

#घोषणा DAPQ_DATA_BUFF		0x6C00
#घोषणा DARQ_DATA_BUFF		0x6C30
#घोषणा MODQ_DATA_BUFF		0x6C60
#घोषणा MIDQ_DATA_BUFF		0x7060

#घोषणा DAPQ_OFFSET		SRAM_CNTL_START
#घोषणा DARQ_OFFSET		(SRAM_CNTL_START + 0x08)
#घोषणा MODQ_OFFSET		(SRAM_CNTL_START + 0x10)
#घोषणा MIDQ_OFFSET		(SRAM_CNTL_START + 0x18)
#घोषणा DSPQ_OFFSET		(SRAM_CNTL_START + 0x20)

#घोषणा	HP_ICR			0x00
#घोषणा	HP_CVR			0x01
#घोषणा	HP_ISR			0x02
#घोषणा	HP_IVR			0x03
#घोषणा HP_NU			0x04
#घोषणा HP_INFO			0x04
#घोषणा	HP_TXH			0x05
#घोषणा	HP_RXH			0x05
#घोषणा	HP_TXM			0x06
#घोषणा	HP_RXM			0x06
#घोषणा	HP_TXL			0x07
#घोषणा	HP_RXL			0x07

#घोषणा HP_ICR_DEF		0x00
#घोषणा HP_CVR_DEF		0x12
#घोषणा HP_ISR_DEF		0x06
#घोषणा HP_IVR_DEF		0x0f
#घोषणा HP_NU_DEF		0x00

#घोषणा	HP_IRQM			0x09

#घोषणा	HPR_BLRC		0x08
#घोषणा	HPR_SPR1		0x09
#घोषणा	HPR_SPR2		0x0A
#घोषणा	HPR_TCL0		0x0B
#घोषणा	HPR_TCL1		0x0C
#घोषणा	HPR_TCL2		0x0D
#घोषणा	HPR_TCL3		0x0E
#घोषणा	HPR_TCL4		0x0F

#घोषणा	HPICR_INIT		0x80
#घोषणा HPICR_HM1		0x40
#घोषणा HPICR_HM0		0x20
#घोषणा HPICR_HF1		0x10
#घोषणा HPICR_HF0		0x08
#घोषणा	HPICR_TREQ		0x02
#घोषणा	HPICR_RREQ		0x01

#घोषणा HPCVR_HC		0x80

#घोषणा	HPISR_HREQ		0x80
#घोषणा HPISR_DMA		0x40
#घोषणा HPISR_HF3		0x10
#घोषणा HPISR_HF2		0x08
#घोषणा	HPISR_TRDY		0x04
#घोषणा	HPISR_TXDE		0x02
#घोषणा	HPISR_RXDF		0x01

#घोषणा	HPIO_290		0
#घोषणा	HPIO_260		1
#घोषणा	HPIO_250		2
#घोषणा	HPIO_240		3
#घोषणा	HPIO_230		4
#घोषणा	HPIO_220		5
#घोषणा	HPIO_210		6
#घोषणा	HPIO_3E0		7

#घोषणा	HPMEM_NONE		0
#घोषणा	HPMEM_B000		1
#घोषणा	HPMEM_C800		2
#घोषणा	HPMEM_D000		3
#घोषणा	HPMEM_D400		4
#घोषणा	HPMEM_D800		5
#घोषणा	HPMEM_E000		6
#घोषणा	HPMEM_E800		7

#घोषणा	HPIRQ_NONE		0
#घोषणा HPIRQ_5			1
#घोषणा HPIRQ_7			2
#घोषणा HPIRQ_9			3
#घोषणा HPIRQ_10		4
#घोषणा HPIRQ_11		5
#घोषणा HPIRQ_12		6
#घोषणा HPIRQ_15		7

#घोषणा	HIMT_PLAY_DONE		0x00
#घोषणा	HIMT_RECORD_DONE	0x01
#घोषणा	HIMT_MIDI_EOS		0x02
#घोषणा	HIMT_MIDI_OUT		0x03

#घोषणा	HIMT_MIDI_IN_UCHAR	0x0E
#घोषणा	HIMT_DSP		0x0F

#घोषणा	HDEX_BASE	       	0x92
#घोषणा	HDEX_PLAY_START		(0 + HDEX_BASE)
#घोषणा	HDEX_PLAY_STOP		(1 + HDEX_BASE)
#घोषणा	HDEX_PLAY_PAUSE		(2 + HDEX_BASE)
#घोषणा	HDEX_PLAY_RESUME	(3 + HDEX_BASE)
#घोषणा	HDEX_RECORD_START	(4 + HDEX_BASE)
#घोषणा	HDEX_RECORD_STOP	(5 + HDEX_BASE)
#घोषणा	HDEX_MIDI_IN_START 	(6 + HDEX_BASE)
#घोषणा	HDEX_MIDI_IN_STOP	(7 + HDEX_BASE)
#घोषणा	HDEX_MIDI_OUT_START	(8 + HDEX_BASE)
#घोषणा	HDEX_MIDI_OUT_STOP	(9 + HDEX_BASE)
#घोषणा	HDEX_AUX_REQ		(10 + HDEX_BASE)

#घोषणा	HDEXAR_CLEAR_PEAKS	1
#घोषणा	HDEXAR_IN_SET_POTS	2
#घोषणा	HDEXAR_AUX_SET_POTS	3
#घोषणा	HDEXAR_CAL_A_TO_D	4
#घोषणा	HDEXAR_RD_EXT_DSP_BITS	5

/* Pinnacle only HDEXAR defs */
#घोषणा	HDEXAR_SET_ANA_IN	0
#घोषणा	HDEXAR_SET_SYNTH_IN	4
#घोषणा	HDEXAR_READ_DAT_IN	5
#घोषणा	HDEXAR_MIC_SET_POTS	6
#घोषणा	HDEXAR_SET_DAT_IN	7

#घोषणा HDEXAR_SET_SYNTH_48	8
#घोषणा HDEXAR_SET_SYNTH_44	9

#घोषणा HIWORD(l)		((u16)((((u32)(l)) >> 16) & 0xFFFF))
#घोषणा LOWORD(l)		((u16)(u32)(l))
#घोषणा HIBYTE(w)		((u8)(((u16)(w) >> 8) & 0xFF))
#घोषणा LOBYTE(w)		((u8)(w))
#घोषणा MAKELONG(low, hi)	((दीर्घ)(((u16)(low))|(((u32)((u16)(hi)))<<16)))
#घोषणा MAKEWORD(low, hi)	((u16)(((u8)(low))|(((u16)((u8)(hi)))<<8)))

#घोषणा PCTODSP_OFFSET(w)	(u16)((w)/2)
#घोषणा PCTODSP_BASED(w)	(u16)(((w)/2) + DSP_BASE_ADDR)
#घोषणा DSPTOPC_BASED(w)	(((w) - DSP_BASE_ADDR) * 2)

#अगर_घोषित SLOWIO
#  undef outb
#  undef inb
#  define outb			outb_p
#  define inb			inb_p
#पूर्ण_अगर

/* JobQueueStruct */
#घोषणा JQS_wStart		0x00
#घोषणा JQS_wSize		0x02
#घोषणा JQS_wHead		0x04
#घोषणा JQS_wTail		0x06
#घोषणा JQS__size		0x08

/* DAQueueDataStruct */
#घोषणा DAQDS_wStart		0x00
#घोषणा DAQDS_wSize		0x02
#घोषणा DAQDS_wFormat		0x04
#घोषणा DAQDS_wSampleSize	0x06
#घोषणा DAQDS_wChannels		0x08
#घोषणा DAQDS_wSampleRate	0x0A
#घोषणा DAQDS_wIntMsg		0x0C
#घोषणा DAQDS_wFlags		0x0E
#घोषणा DAQDS__size		0x10

#समावेश <sound/pcm.h>

काष्ठा snd_msnd अणु
	व्योम __iomem		*mappedbase;
	पूर्णांक			play_period_bytes;
	पूर्णांक			playLimit;
	पूर्णांक			playPeriods;
	पूर्णांक 			playDMAPos;
	पूर्णांक			banksPlayed;
	पूर्णांक 			captureDMAPos;
	पूर्णांक			capturePeriodBytes;
	पूर्णांक			captureLimit;
	पूर्णांक			capturePeriods;
	काष्ठा snd_card		*card;
	व्योम			*msndmidi_mpu;
	काष्ठा snd_rawmidi	*rmidi;

	/* Hardware resources */
	दीर्घ io;
	पूर्णांक memid, irqid;
	पूर्णांक irq, irq_ref;
	अचिन्हित दीर्घ base;

	/* Motorola 56k DSP SMA */
	व्योम __iomem	*SMA;
	व्योम __iomem	*DAPQ;
	व्योम __iomem	*DARQ;
	व्योम __iomem	*MODQ;
	व्योम __iomem	*MIDQ;
	व्योम __iomem	*DSPQ;
	पूर्णांक dspq_data_buff, dspq_buff_size;

	/* State variables */
	क्रमागत अणु msndClassic, msndPinnacle पूर्ण type;
	भ_शेषe_t mode;
	अचिन्हित दीर्घ flags;
#घोषणा F_RESETTING			0
#घोषणा F_HAVEDIGITAL			1
#घोषणा F_AUDIO_WRITE_INUSE		2
#घोषणा F_WRITING			3
#घोषणा F_WRITEBLOCK			4
#घोषणा F_WRITEFLUSH			5
#घोषणा F_AUDIO_READ_INUSE		6
#घोषणा F_READING			7
#घोषणा F_READBLOCK			8
#घोषणा F_EXT_MIDI_INUSE		9
#घोषणा F_HDR_MIDI_INUSE		10
#घोषणा F_DISABLE_WRITE_NDELAY		11
	spinlock_t lock;
	spinlock_t mixer_lock;
	पूर्णांक nresets;
	अचिन्हित recsrc;
#घोषणा LEVEL_ENTRIES 32
	पूर्णांक left_levels[LEVEL_ENTRIES];
	पूर्णांक right_levels[LEVEL_ENTRIES];
	पूर्णांक calibrate_संकेत;
	पूर्णांक play_sample_size, play_sample_rate, play_channels;
	पूर्णांक play_ndelay;
	पूर्णांक capture_sample_size, capture_sample_rate, capture_channels;
	पूर्णांक capture_ndelay;
	u8 bCurrentMidiPatch;

	पूर्णांक last_playbank, last_recbank;
	काष्ठा snd_pcm_substream *playback_substream;
	काष्ठा snd_pcm_substream *capture_substream;

पूर्ण;

व्योम snd_msnd_init_queue(व्योम __iomem *base, पूर्णांक start, पूर्णांक size);

पूर्णांक snd_msnd_send_dsp_cmd(काष्ठा snd_msnd *chip, u8 cmd);
पूर्णांक snd_msnd_send_word(काष्ठा snd_msnd *chip,
			   अचिन्हित अक्षर high,
			   अचिन्हित अक्षर mid,
			   अचिन्हित अक्षर low);
पूर्णांक snd_msnd_upload_host(काष्ठा snd_msnd *chip,
			     स्थिर u8 *bin, पूर्णांक len);
पूर्णांक snd_msnd_enable_irq(काष्ठा snd_msnd *chip);
पूर्णांक snd_msnd_disable_irq(काष्ठा snd_msnd *chip);
व्योम snd_msnd_dsp_halt(काष्ठा snd_msnd *chip, काष्ठा file *file);
पूर्णांक snd_msnd_DAPQ(काष्ठा snd_msnd *chip, पूर्णांक start);
पूर्णांक snd_msnd_DARQ(काष्ठा snd_msnd *chip, पूर्णांक start);
पूर्णांक snd_msnd_pcm(काष्ठा snd_card *card, पूर्णांक device);

पूर्णांक snd_msndmidi_new(काष्ठा snd_card *card, पूर्णांक device);
व्योम snd_msndmidi_input_पढ़ो(व्योम *mpu);

व्योम snd_msndmix_setup(काष्ठा snd_msnd *chip);
पूर्णांक snd_msndmix_new(काष्ठा snd_card *card);
पूर्णांक snd_msndmix_क्रमce_recsrc(काष्ठा snd_msnd *chip, पूर्णांक recsrc);
#पूर्ण_अगर /* __MSND_H */
