<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ALSA driver क्रम Echoaudio soundcards.
 *  Copyright (C) 2003-2004 Giuliano Pochini <pochini@shiny.it>
 */

#घोषणा ECHO3G_FAMILY
#घोषणा ECHOCARD_ECHO3G
#घोषणा ECHOCARD_NAME "Echo3G"
#घोषणा ECHOCARD_HAS_MONITOR
#घोषणा ECHOCARD_HAS_ASIC
#घोषणा ECHOCARD_HAS_INPUT_NOMINAL_LEVEL
#घोषणा ECHOCARD_HAS_OUTPUT_NOMINAL_LEVEL
#घोषणा ECHOCARD_HAS_SUPER_INTERLEAVE
#घोषणा ECHOCARD_HAS_DIGITAL_IO
#घोषणा ECHOCARD_HAS_DIGITAL_MODE_SWITCH
#घोषणा ECHOCARD_HAS_ADAT	6
#घोषणा ECHOCARD_HAS_EXTERNAL_CLOCK
#घोषणा ECHOCARD_HAS_STEREO_BIG_ENDIAN32
#घोषणा ECHOCARD_HAS_MIDI
#घोषणा ECHOCARD_HAS_PHANTOM_POWER

/* Pipe indexes */
#घोषणा PX_ANALOG_OUT	0
#घोषणा PX_DIGITAL_OUT	chip->px_digital_out
#घोषणा PX_ANALOG_IN	chip->px_analog_in
#घोषणा PX_DIGITAL_IN	chip->px_digital_in
#घोषणा PX_NUM		chip->px_num

/* Bus indexes */
#घोषणा BX_ANALOG_OUT	0
#घोषणा BX_DIGITAL_OUT	chip->bx_digital_out
#घोषणा BX_ANALOG_IN	chip->bx_analog_in
#घोषणा BX_DIGITAL_IN	chip->bx_digital_in
#घोषणा BX_NUM		chip->bx_num


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
#समावेश <sound/rawmidi.h>
#समावेश <linux/atomic.h>
#समावेश "echoaudio.h"

MODULE_FIRMWARE("ea/loader_dsp.fw");
MODULE_FIRMWARE("ea/echo3g_dsp.fw");
MODULE_FIRMWARE("ea/3g_asic.fw");

#घोषणा FW_361_LOADER	0
#घोषणा FW_ECHO3G_DSP	1
#घोषणा FW_3G_ASIC	2

अटल स्थिर काष्ठा firmware card_fw[] = अणु
	अणु0, "loader_dsp.fw"पूर्ण,
	अणु0, "echo3g_dsp.fw"पूर्ण,
	अणु0, "3g_asic.fw"पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_echo_ids[] = अणु
	अणु0x1057, 0x3410, 0xECC0, 0x0100, 0, 0, 0पूर्ण,	/* Echo 3G */
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
			SNDRV_PCM_RATE_96000 |
			SNDRV_PCM_RATE_CONTINUOUS,
	.rate_min = 32000,
	.rate_max = 100000,
	.channels_min = 1,
	.channels_max = 8,
	.buffer_bytes_max = 262144,
	.period_bytes_min = 32,
	.period_bytes_max = 131072,
	.periods_min = 2,
	.periods_max = 220,
पूर्ण;

#समावेश "echo3g_dsp.c"
#समावेश "echoaudio_dsp.c"
#समावेश "echoaudio_3g.c"
#समावेश "echoaudio.c"
#समावेश "midi.c"
