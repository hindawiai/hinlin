<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_MINORS_H
#घोषणा __SOUND_MINORS_H

/*
 *  MINOR numbers
 */

#घोषणा SNDRV_OS_MINORS			256

#घोषणा SNDRV_MINOR_DEVICES		32
#घोषणा SNDRV_MINOR_CARD(minor)		((minor) >> 5)
#घोषणा SNDRV_MINOR_DEVICE(minor)	((minor) & 0x001f)
#घोषणा SNDRV_MINOR(card, dev)		(((card) << 5) | (dev))

/* these minors can still be used क्रम स्वतःloading devices (/dev/aload*) */
#घोषणा SNDRV_MINOR_CONTROL		0	/* 0 */
#घोषणा SNDRV_MINOR_GLOBAL		1	/* 1 */
#घोषणा SNDRV_MINOR_SEQUENCER		1	/* SNDRV_MINOR_GLOBAL + 0 * 32 */
#घोषणा SNDRV_MINOR_TIMER		33	/* SNDRV_MINOR_GLOBAL + 1 * 32 */

#अगर_अघोषित CONFIG_SND_DYNAMIC_MINORS
#घोषणा SNDRV_MINOR_COMPRESS		2	/* 2 - 3 */
#घोषणा SNDRV_MINOR_HWDEP		4	/* 4 - 7 */
#घोषणा SNDRV_MINOR_RAWMIDI		8	/* 8 - 15 */
#घोषणा SNDRV_MINOR_PCM_PLAYBACK	16	/* 16 - 23 */
#घोषणा SNDRV_MINOR_PCM_CAPTURE		24	/* 24 - 31 */

/* same as first respective minor number to make minor allocation easier */
#घोषणा SNDRV_DEVICE_TYPE_CONTROL	SNDRV_MINOR_CONTROL
#घोषणा SNDRV_DEVICE_TYPE_HWDEP		SNDRV_MINOR_HWDEP
#घोषणा SNDRV_DEVICE_TYPE_RAWMIDI	SNDRV_MINOR_RAWMIDI
#घोषणा SNDRV_DEVICE_TYPE_PCM_PLAYBACK	SNDRV_MINOR_PCM_PLAYBACK
#घोषणा SNDRV_DEVICE_TYPE_PCM_CAPTURE	SNDRV_MINOR_PCM_CAPTURE
#घोषणा SNDRV_DEVICE_TYPE_SEQUENCER	SNDRV_MINOR_SEQUENCER
#घोषणा SNDRV_DEVICE_TYPE_TIMER		SNDRV_MINOR_TIMER
#घोषणा SNDRV_DEVICE_TYPE_COMPRESS	SNDRV_MINOR_COMPRESS

#अन्यथा /* CONFIG_SND_DYNAMIC_MINORS */

क्रमागत अणु
	SNDRV_DEVICE_TYPE_CONTROL,
	SNDRV_DEVICE_TYPE_SEQUENCER,
	SNDRV_DEVICE_TYPE_TIMER,
	SNDRV_DEVICE_TYPE_HWDEP,
	SNDRV_DEVICE_TYPE_RAWMIDI,
	SNDRV_DEVICE_TYPE_PCM_PLAYBACK,
	SNDRV_DEVICE_TYPE_PCM_CAPTURE,
	SNDRV_DEVICE_TYPE_COMPRESS,
पूर्ण;

#पूर्ण_अगर /* CONFIG_SND_DYNAMIC_MINORS */

#घोषणा SNDRV_MINOR_HWDEPS		4
#घोषणा SNDRV_MINOR_RAWMIDIS		8
#घोषणा SNDRV_MINOR_PCMS		8


#अगर_घोषित CONFIG_SND_OSSEMUL

#घोषणा SNDRV_MINOR_OSS_DEVICES		16
#घोषणा SNDRV_MINOR_OSS_CARD(minor)	((minor) >> 4)
#घोषणा SNDRV_MINOR_OSS_DEVICE(minor)	((minor) & 0x000f)
#घोषणा SNDRV_MINOR_OSS(card, dev)	(((card) << 4) | (dev))

#घोषणा SNDRV_MINOR_OSS_MIXER		0	/* /dev/mixer - OSS 3.XX compatible */
#घोषणा SNDRV_MINOR_OSS_SEQUENCER	1	/* /dev/sequencer - OSS 3.XX compatible */
#घोषणा	SNDRV_MINOR_OSS_MIDI		2	/* /dev/midi - native midi पूर्णांकerface - OSS 3.XX compatible - UART */
#घोषणा SNDRV_MINOR_OSS_PCM		3	/* alias */
#घोषणा SNDRV_MINOR_OSS_PCM_8		3	/* /dev/dsp - 8bit PCM - OSS 3.XX compatible */
#घोषणा SNDRV_MINOR_OSS_AUDIO		4	/* /dev/audio - SunSparc compatible */
#घोषणा SNDRV_MINOR_OSS_PCM_16		5	/* /dev/dsp16 - 16bit PCM - OSS 3.XX compatible */
#घोषणा SNDRV_MINOR_OSS_SNDSTAT		6	/* /dev/sndstat - क्रम compatibility with OSS */
#घोषणा SNDRV_MINOR_OSS_RESERVED7	7	/* reserved क्रम future use */
#घोषणा SNDRV_MINOR_OSS_MUSIC		8	/* /dev/music - OSS 3.XX compatible */
#घोषणा SNDRV_MINOR_OSS_DMMIDI		9	/* /dev/dmmidi0 - this device can have another minor # with OSS */
#घोषणा SNDRV_MINOR_OSS_DMFM		10	/* /dev/dmfm0 - this device can have another minor # with OSS */
#घोषणा SNDRV_MINOR_OSS_MIXER1		11	/* alternate mixer */
#घोषणा SNDRV_MINOR_OSS_PCM1		12	/* alternate PCM (GF-A-1) */
#घोषणा SNDRV_MINOR_OSS_MIDI1		13	/* alternate midi - SYNTH */
#घोषणा SNDRV_MINOR_OSS_DMMIDI1		14	/* alternate dmmidi - SYNTH */
#घोषणा SNDRV_MINOR_OSS_RESERVED15	15	/* reserved क्रम future use */

#घोषणा SNDRV_OSS_DEVICE_TYPE_MIXER	0
#घोषणा SNDRV_OSS_DEVICE_TYPE_SEQUENCER	1
#घोषणा SNDRV_OSS_DEVICE_TYPE_PCM	2
#घोषणा SNDRV_OSS_DEVICE_TYPE_MIDI	3
#घोषणा SNDRV_OSS_DEVICE_TYPE_DMFM	4
#घोषणा SNDRV_OSS_DEVICE_TYPE_SNDSTAT	5
#घोषणा SNDRV_OSS_DEVICE_TYPE_MUSIC	6

#घोषणा MODULE_ALIAS_SNDRV_MINOR(type) \
	MODULE_ALIAS("sound-service-?-" __stringअगरy(type))

#पूर्ण_अगर

#पूर्ण_अगर /* __SOUND_MINORS_H */
