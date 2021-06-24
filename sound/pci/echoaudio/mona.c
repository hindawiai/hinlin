<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ALSA driver क्रम Echoaudio soundcards.
 *  Copyright (C) 2003-2004 Giuliano Pochini <pochini@shiny.it>
 */

#घोषणा ECHO24_FAMILY
#घोषणा ECHOCARD_MONA
#घोषणा ECHOCARD_NAME "Mona"
#घोषणा ECHOCARD_HAS_MONITOR
#घोषणा ECHOCARD_HAS_ASIC
#घोषणा ECHOCARD_HAS_SUPER_INTERLEAVE
#घोषणा ECHOCARD_HAS_DIGITAL_IO
#घोषणा ECHOCARD_HAS_DIGITAL_IN_AUTOMUTE
#घोषणा ECHOCARD_HAS_DIGITAL_MODE_SWITCH
#घोषणा ECHOCARD_HAS_EXTERNAL_CLOCK
#घोषणा ECHOCARD_HAS_ADAT	6
#घोषणा ECHOCARD_HAS_STEREO_BIG_ENDIAN32

/* Pipe indexes */
#घोषणा PX_ANALOG_OUT	0	/* 6 */
#घोषणा PX_DIGITAL_OUT	6	/* 8 */
#घोषणा PX_ANALOG_IN	14	/* 4 */
#घोषणा PX_DIGITAL_IN	18	/* 8 */
#घोषणा PX_NUM		26

/* Bus indexes */
#घोषणा BX_ANALOG_OUT	0	/* 6 */
#घोषणा BX_DIGITAL_OUT	6	/* 8 */
#घोषणा BX_ANALOG_IN	14	/* 4 */
#घोषणा BX_DIGITAL_IN	18	/* 8 */
#घोषणा BX_NUM		26


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
MODULE_FIRMWARE("ea/mona_301_dsp.fw");
MODULE_FIRMWARE("ea/mona_361_dsp.fw");
MODULE_FIRMWARE("ea/mona_301_1_asic_48.fw");
MODULE_FIRMWARE("ea/mona_301_1_asic_96.fw");
MODULE_FIRMWARE("ea/mona_361_1_asic_48.fw");
MODULE_FIRMWARE("ea/mona_361_1_asic_96.fw");
MODULE_FIRMWARE("ea/mona_2_asic.fw");

#घोषणा FW_361_LOADER		0
#घोषणा FW_MONA_301_DSP		1
#घोषणा FW_MONA_361_DSP		2
#घोषणा FW_MONA_301_1_ASIC48	3
#घोषणा FW_MONA_301_1_ASIC96	4
#घोषणा FW_MONA_361_1_ASIC48	5
#घोषणा FW_MONA_361_1_ASIC96	6
#घोषणा FW_MONA_2_ASIC		7

अटल स्थिर काष्ठा firmware card_fw[] = अणु
	अणु0, "loader_dsp.fw"पूर्ण,
	अणु0, "mona_301_dsp.fw"पूर्ण,
	अणु0, "mona_361_dsp.fw"पूर्ण,
	अणु0, "mona_301_1_asic_48.fw"पूर्ण,
	अणु0, "mona_301_1_asic_96.fw"पूर्ण,
	अणु0, "mona_361_1_asic_48.fw"पूर्ण,
	अणु0, "mona_361_1_asic_96.fw"पूर्ण,
	अणु0, "mona_2_asic.fw"पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_echo_ids[] = अणु
	अणु0x1057, 0x1801, 0xECC0, 0x0070, 0, 0, 0पूर्ण,	/* DSP 56301 Mona rev.0 */
	अणु0x1057, 0x1801, 0xECC0, 0x0071, 0, 0, 0पूर्ण,	/* DSP 56301 Mona rev.1 */
	अणु0x1057, 0x1801, 0xECC0, 0x0072, 0, 0, 0पूर्ण,	/* DSP 56301 Mona rev.2 */
	अणु0x1057, 0x3410, 0xECC0, 0x0070, 0, 0, 0पूर्ण,	/* DSP 56361 Mona rev.0 */
	अणु0x1057, 0x3410, 0xECC0, 0x0071, 0, 0, 0पूर्ण,	/* DSP 56361 Mona rev.1 */
	अणु0x1057, 0x3410, 0xECC0, 0x0072, 0, 0, 0पूर्ण,	/* DSP 56361 Mona rev.2 */
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
	.rates = 	SNDRV_PCM_RATE_8000_48000 |
			SNDRV_PCM_RATE_88200 |
			SNDRV_PCM_RATE_96000,
	.rate_min = 8000,
	.rate_max = 96000,
	.channels_min = 1,
	.channels_max = 8,
	.buffer_bytes_max = 262144,
	.period_bytes_min = 32,
	.period_bytes_max = 131072,
	.periods_min = 2,
	.periods_max = 220,
	/* One page (4k) contains 512 inकाष्ठाions. I करोn't know अगर the hw
	supports lists दीर्घer than this. In this हाल periods_max=220 is a
	safe limit to make sure the list never exceeds 512 inकाष्ठाions. */
पूर्ण;


#समावेश "mona_dsp.c"
#समावेश "echoaudio_dsp.c"
#समावेश "echoaudio_gml.c"
#समावेश "echoaudio.c"
