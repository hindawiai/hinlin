<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_AD1816A_H
#घोषणा __SOUND_AD1816A_H

/*
    ad1816a.h - definitions क्रम ADI SoundPort AD1816A chip.
    Copyright (C) 1999-2000 by Massimo Piccioni <dafastidio@libero.it>

*/

#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/समयr.h>

#घोषणा AD1816A_REG(r)			(chip->port + r)

#घोषणा AD1816A_CHIP_STATUS		0x00
#घोषणा AD1816A_INसूची_ADDR		0x00
#घोषणा AD1816A_INTERRUPT_STATUS	0x01
#घोषणा AD1816A_INसूची_DATA_LOW		0x02
#घोषणा AD1816A_INसूची_DATA_HIGH		0x03
#घोषणा AD1816A_PIO_DEBUG		0x04
#घोषणा AD1816A_PIO_STATUS		0x05
#घोषणा AD1816A_PIO_DATA		0x06
#घोषणा AD1816A_RESERVED_7		0x07
#घोषणा AD1816A_PLAYBACK_CONFIG		0x08
#घोषणा AD1816A_CAPTURE_CONFIG		0x09
#घोषणा AD1816A_RESERVED_10		0x0a
#घोषणा AD1816A_RESERVED_11		0x0b
#घोषणा AD1816A_JOYSTICK_RAW_DATA	0x0c
#घोषणा AD1816A_JOYSTICK_CTRL		0x0d
#घोषणा AD1816A_JOY_POS_DATA_LOW	0x0e
#घोषणा AD1816A_JOY_POS_DATA_HIGH	0x0f

#घोषणा AD1816A_LOW_BYTE_TMP		0x00
#घोषणा AD1816A_INTERRUPT_ENABLE	0x01
#घोषणा AD1816A_EXTERNAL_CTRL		0x01
#घोषणा AD1816A_PLAYBACK_SAMPLE_RATE	0x02
#घोषणा AD1816A_CAPTURE_SAMPLE_RATE	0x03
#घोषणा AD1816A_VOICE_ATT		0x04
#घोषणा AD1816A_FM_ATT			0x05
#घोषणा AD1816A_I2S_1_ATT		0x06
#घोषणा AD1816A_I2S_0_ATT		0x07
#घोषणा AD1816A_PLAYBACK_BASE_COUNT	0x08
#घोषणा AD1816A_PLAYBACK_CURR_COUNT	0x09
#घोषणा AD1816A_CAPTURE_BASE_COUNT	0x0a
#घोषणा AD1816A_CAPTURE_CURR_COUNT	0x0b
#घोषणा AD1816A_TIMER_BASE_COUNT	0x0c
#घोषणा AD1816A_TIMER_CURR_COUNT	0x0d
#घोषणा AD1816A_MASTER_ATT		0x0e
#घोषणा AD1816A_CD_GAIN_ATT		0x0f
#घोषणा AD1816A_SYNTH_GAIN_ATT		0x10
#घोषणा AD1816A_VID_GAIN_ATT		0x11
#घोषणा AD1816A_LINE_GAIN_ATT		0x12
#घोषणा AD1816A_MIC_GAIN_ATT		0x13
#घोषणा AD1816A_PHONE_IN_GAIN_ATT	0x13
#घोषणा AD1816A_ADC_SOURCE_SEL		0x14
#घोषणा AD1816A_ADC_PGA			0x14
#घोषणा AD1816A_CHIP_CONFIG		0x20
#घोषणा AD1816A_DSP_CONFIG		0x21
#घोषणा AD1816A_FM_SAMPLE_RATE		0x22
#घोषणा AD1816A_I2S_1_SAMPLE_RATE	0x23
#घोषणा AD1816A_I2S_0_SAMPLE_RATE	0x24
#घोषणा AD1816A_RESERVED_37		0x25
#घोषणा AD1816A_PROGRAM_CLOCK_RATE	0x26
#घोषणा AD1816A_3D_PHAT_CTRL		0x27
#घोषणा AD1816A_PHONE_OUT_ATT		0x27
#घोषणा AD1816A_RESERVED_40		0x28
#घोषणा AD1816A_HW_VOL_BUT		0x29
#घोषणा AD1816A_DSP_MAILBOX_0		0x2a
#घोषणा AD1816A_DSP_MAILBOX_1		0x2b
#घोषणा AD1816A_POWERDOWN_CTRL		0x2c
#घोषणा AD1816A_TIMER_CTRL		0x2c
#घोषणा AD1816A_VERSION_ID		0x2d
#घोषणा AD1816A_RESERVED_46		0x2e

#घोषणा AD1816A_READY			0x80

#घोषणा AD1816A_PLAYBACK_IRQ_PENDING	0x80
#घोषणा AD1816A_CAPTURE_IRQ_PENDING	0x40
#घोषणा AD1816A_TIMER_IRQ_PENDING	0x20

#घोषणा AD1816A_PLAYBACK_ENABLE		0x01
#घोषणा AD1816A_PLAYBACK_PIO		0x02
#घोषणा AD1816A_CAPTURE_ENABLE		0x01
#घोषणा AD1816A_CAPTURE_PIO		0x02

#घोषणा AD1816A_FMT_LINEAR_8		0x00
#घोषणा AD1816A_FMT_ULAW_8		0x08
#घोषणा AD1816A_FMT_LINEAR_16_LIT	0x10
#घोषणा AD1816A_FMT_ALAW_8		0x18
#घोषणा AD1816A_FMT_LINEAR_16_BIG	0x30
#घोषणा AD1816A_FMT_ALL			0x38
#घोषणा AD1816A_FMT_STEREO		0x04

#घोषणा AD1816A_PLAYBACK_IRQ_ENABLE	0x8000
#घोषणा AD1816A_CAPTURE_IRQ_ENABLE	0x4000
#घोषणा AD1816A_TIMER_IRQ_ENABLE	0x2000
#घोषणा AD1816A_TIMER_ENABLE		0x0080

#घोषणा AD1816A_SRC_LINE		0x00
#घोषणा AD1816A_SRC_OUT			0x10
#घोषणा AD1816A_SRC_CD			0x20
#घोषणा AD1816A_SRC_SYNTH		0x30
#घोषणा AD1816A_SRC_VIDEO		0x40
#घोषणा AD1816A_SRC_MIC			0x50
#घोषणा AD1816A_SRC_MONO		0x50
#घोषणा AD1816A_SRC_PHONE_IN		0x60
#घोषणा AD1816A_SRC_MASK		0x70

#घोषणा AD1816A_CAPTURE_NOT_EQUAL	0x1000
#घोषणा AD1816A_WSS_ENABLE		0x8000

काष्ठा snd_ad1816a अणु
	अचिन्हित दीर्घ port;
	काष्ठा resource *res_port;
	पूर्णांक irq;
	पूर्णांक dma1;
	पूर्णांक dma2;

	अचिन्हित लघु hardware;
	अचिन्हित लघु version;

	spinlock_t lock;

	अचिन्हित लघु mode;
	अचिन्हित पूर्णांक घड़ी_freq;

	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;

	काष्ठा snd_pcm_substream *playback_substream;
	काष्ठा snd_pcm_substream *capture_substream;
	अचिन्हित पूर्णांक p_dma_size;
	अचिन्हित पूर्णांक c_dma_size;

	काष्ठा snd_समयr *समयr;
#अगर_घोषित CONFIG_PM
	अचिन्हित लघु image[48];
#पूर्ण_अगर
पूर्ण;


#घोषणा AD1816A_HW_AUTO		0
#घोषणा AD1816A_HW_AD1816A	1
#घोषणा AD1816A_HW_AD1815	2
#घोषणा AD1816A_HW_AD18MAX10	3

#घोषणा AD1816A_MODE_PLAYBACK	0x01
#घोषणा AD1816A_MODE_CAPTURE	0x02
#घोषणा AD1816A_MODE_TIMER	0x04
#घोषणा AD1816A_MODE_OPEN	(AD1816A_MODE_PLAYBACK |	\
				AD1816A_MODE_CAPTURE |		\
				AD1816A_MODE_TIMER)


बाह्य पूर्णांक snd_ad1816a_create(काष्ठा snd_card *card, अचिन्हित दीर्घ port,
			      पूर्णांक irq, पूर्णांक dma1, पूर्णांक dma2,
			      काष्ठा snd_ad1816a *chip);

बाह्य पूर्णांक snd_ad1816a_pcm(काष्ठा snd_ad1816a *chip, पूर्णांक device);
बाह्य पूर्णांक snd_ad1816a_mixer(काष्ठा snd_ad1816a *chip);
बाह्य पूर्णांक snd_ad1816a_समयr(काष्ठा snd_ad1816a *chip, पूर्णांक device);
#अगर_घोषित CONFIG_PM
बाह्य व्योम snd_ad1816a_suspend(काष्ठा snd_ad1816a *chip);
बाह्य व्योम snd_ad1816a_resume(काष्ठा snd_ad1816a *chip);
#पूर्ण_अगर

#पूर्ण_अगर	/* __SOUND_AD1816A_H */
