<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* aica.h
 * Header file क्रम ALSA driver क्रम
 * Sega Dreamcast Yamaha AICA sound
 * Copyright Adrian McMenamin
 * <adrian@mcmen.demon.co.uk>
 * 2006
 */

/* SPU memory and रेजिस्टर स्थिरants etc */
#घोषणा G2_FIFO 0xa05f688c
#घोषणा SPU_MEMORY_BASE 0xA0800000
#घोषणा ARM_RESET_REGISTER 0xA0702C00
#घोषणा SPU_REGISTER_BASE 0xA0700000

/* AICA channels stuff */
#घोषणा AICA_CONTROL_POINT 0xA0810000
#घोषणा AICA_CONTROL_CHANNEL_SAMPLE_NUMBER 0xA0810008
#घोषणा AICA_CHANNEL0_CONTROL_OFFSET 0x10004

/* Command values */
#घोषणा AICA_CMD_KICK 0x80000000
#घोषणा AICA_CMD_NONE 0
#घोषणा AICA_CMD_START 1
#घोषणा AICA_CMD_STOP 2
#घोषणा AICA_CMD_VOL 3

/* Sound modes */
#घोषणा SM_8BIT		1
#घोषणा SM_16BIT	0
#घोषणा SM_ADPCM	2

/* Buffer and period size */
#घोषणा AICA_BUFFER_SIZE 0x8000
#घोषणा AICA_PERIOD_SIZE 0x800
#घोषणा AICA_PERIOD_NUMBER 16

#घोषणा AICA_CHANNEL0_OFFSET 0x11000
#घोषणा AICA_CHANNEL1_OFFSET 0x21000
#घोषणा CHANNEL_OFFSET 0x10000

#घोषणा AICA_DMA_CHANNEL 5
#घोषणा AICA_DMA_MODE 5

#घोषणा SND_AICA_DRIVER "AICA"

काष्ठा aica_channel अणु
	uपूर्णांक32_t cmd;		/* Command ID           */
	uपूर्णांक32_t pos;		/* Sample position      */
	uपूर्णांक32_t length;	/* Sample length        */
	uपूर्णांक32_t freq;		/* Frequency            */
	uपूर्णांक32_t vol;		/* Volume 0-255         */
	uपूर्णांक32_t pan;		/* Pan 0-255            */
	uपूर्णांक32_t sfmt;		/* Sound क्रमmat         */
	uपूर्णांक32_t flags;		/* Bit flags            */
पूर्ण;

काष्ठा snd_card_aica अणु
	काष्ठा work_काष्ठा spu_dma_work;
	काष्ठा snd_card *card;
	काष्ठा aica_channel *channel;
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक clicks;
	पूर्णांक current_period;
	काष्ठा समयr_list समयr;
	पूर्णांक master_volume;
	पूर्णांक dma_check;
पूर्ण;
