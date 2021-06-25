<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ALSA driver क्रम Echoaudio soundcards.
 *  Copyright (C) 2003-2004 Giuliano Pochini <pochini@shiny.it>
 */

#घोषणा INDIGO_FAMILY
#घोषणा ECHOCARD_INDIGO_DJ
#घोषणा ECHOCARD_NAME "Indigo DJ"
#घोषणा ECHOCARD_HAS_SUPER_INTERLEAVE
#घोषणा ECHOCARD_HAS_VMIXER
#घोषणा ECHOCARD_HAS_STEREO_BIG_ENDIAN32

/* Pipe indexes */
#घोषणा PX_ANALOG_OUT	0	/* 8 */
#घोषणा PX_DIGITAL_OUT	8	/* 0 */
#घोषणा PX_ANALOG_IN	8	/* 0 */
#घोषणा PX_DIGITAL_IN	8	/* 0 */
#घोषणा PX_NUM		8

/* Bus indexes */
#घोषणा BX_ANALOG_OUT	0	/* 4 */
#घोषणा BX_DIGITAL_OUT	4	/* 0 */
#घोषणा BX_ANALOG_IN	4	/* 0 */
#घोषणा BX_DIGITAL_IN	4	/* 0 */
#घोषणा BX_NUM		4


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

MODULE_FIRMWARE("ea/loader_dsp.fw");
MODULE_FIRMWARE("ea/indigo_dj_dsp.fw");

#घोषणा FW_361_LOADER		0
#घोषणा FW_INDIGO_DJ_DSP	1

अटल स्थिर काष्ठा firmware card_fw[] = अणु
	अणु0, "loader_dsp.fw"पूर्ण,
	अणु0, "indigo_dj_dsp.fw"पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_echo_ids[] = अणु
	अणु0x1057, 0x3410, 0xECC0, 0x00B0, 0, 0, 0पूर्ण,	/* Indigo DJ*/
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
	.rates = 	SNDRV_PCM_RATE_32000 |
			SNDRV_PCM_RATE_44100 |
			SNDRV_PCM_RATE_48000 |
			SNDRV_PCM_RATE_88200 |
			SNDRV_PCM_RATE_96000,
	.rate_min = 32000,
	.rate_max = 96000,
	.channels_min = 1,
	.channels_max = 4,
	.buffer_bytes_max = 262144,
	.period_bytes_min = 32,
	.period_bytes_max = 131072,
	.periods_min = 2,
	.periods_max = 220,
पूर्ण;

#समावेश "indigodj_dsp.c"
#समावेश "echoaudio_dsp.c"
#समावेश "echoaudio.c"

