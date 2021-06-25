<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ALSA driver क्रम Echoaudio soundcards.
 *  Copyright (C) 2003-2004 Giuliano Pochini <pochini@shiny.it>
 */

#घोषणा ECHOGALS_FAMILY
#घोषणा ECHOCARD_GINA20
#घोषणा ECHOCARD_NAME "Gina20"
#घोषणा ECHOCARD_HAS_MONITOR
#घोषणा ECHOCARD_HAS_INPUT_GAIN
#घोषणा ECHOCARD_HAS_DIGITAL_IO
#घोषणा ECHOCARD_HAS_EXTERNAL_CLOCK
#घोषणा ECHOCARD_HAS_ADAT	false

/* Pipe indexes */
#घोषणा PX_ANALOG_OUT	0	/* 8 */
#घोषणा PX_DIGITAL_OUT	8	/* 2 */
#घोषणा PX_ANALOG_IN	10	/* 2 */
#घोषणा PX_DIGITAL_IN	12	/* 2 */
#घोषणा PX_NUM		14

/* Bus indexes */
#घोषणा BX_ANALOG_OUT	0	/* 8 */
#घोषणा BX_DIGITAL_OUT	8	/* 2 */
#घोषणा BX_ANALOG_IN	10	/* 2 */
#घोषणा BX_DIGITAL_IN	12	/* 2 */
#घोषणा BX_NUM		14


#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/initval.h>
#समावेश <linux/atomic.h>
#समावेश "echoaudio.h"

MODULE_FIRMWARE("ea/gina20_dsp.fw");

#घोषणा FW_GINA20_DSP	0

अटल स्थिर काष्ठा firmware card_fw[] = अणु
	अणु0, "gina20_dsp.fw"पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_echo_ids[] = अणु
	अणु0x1057, 0x1801, 0xECC0, 0x0020, 0, 0, 0पूर्ण,	/* DSP 56301 Gina20 rev.0 */
	अणु0,पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware pcm_hardware_skel = अणु
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_PAUSE |
		SNDRV_PCM_INFO_SYNC_START,
	.क्रमmats =	SNDRV_PCM_FMTBIT_U8 |
			SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S24_3LE |
			SNDRV_PCM_FMTBIT_S32_LE |
			SNDRV_PCM_FMTBIT_S32_BE,
	.rates = SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000,
	.rate_min = 44100,
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 2,
	.buffer_bytes_max = 262144,
	.period_bytes_min = 32,
	.period_bytes_max = 131072,
	.periods_min = 2,
	.periods_max = 220,
	/* One page (4k) contains 512 inकाष्ठाions. I करोn't know अगर the hw
	supports lists दीर्घer than this. In this हाल periods_max=220 is a
	safe limit to make sure the list never exceeds 512 inकाष्ठाions. */
पूर्ण;


#समावेश "gina20_dsp.c"
#समावेश "echoaudio_dsp.c"
#समावेश "echoaudio.c"
