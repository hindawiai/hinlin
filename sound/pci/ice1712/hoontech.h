<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_HOONTECH_H
#घोषणा __SOUND_HOONTECH_H

/*
 *   ALSA driver क्रम ICEnsemble ICE1712 (Envy24)
 *
 *   Lowlevel functions क्रम Hoontech STDSP24
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 */      

#घोषणा  HOONTECH_DEVICE_DESC \
	"{Hoontech,SoundTrack DSP 24}," \
	"{Hoontech,SoundTrack DSP 24 Value}," \
	"{Hoontech,SoundTrack DSP 24 Media 7.1}," \
	"{Event Electronics,EZ8},"

#घोषणा ICE1712_SUBDEVICE_STDSP24		0x12141217	/* Hoontech SoundTrack Audio DSP 24 */
#घोषणा ICE1712_SUBDEVICE_STDSP24_VALUE		0x00010010	/* A dummy id क्रम Hoontech SoundTrack Audio DSP 24 Value */
#घोषणा ICE1712_SUBDEVICE_STDSP24_MEDIA7_1	0x16141217	/* Hoontech ST Audio DSP24 Media 7.1 */
#घोषणा ICE1712_SUBDEVICE_EVENT_EZ8		0x00010001	/* A dummy id क्रम EZ8 */
#घोषणा ICE1712_SUBDEVICE_STAUDIO_ADCIII	0x00010002	/* A dummy id क्रम STAudio ADCIII */

बाह्य काष्ठा snd_ice1712_card_info snd_ice1712_hoontech_cards[];


/* Hoontech SoundTrack Audio DSP 24 GPIO definitions */

#घोषणा ICE1712_STDSP24_0_BOX(r, x)	r[0] = ((r[0] & ~3) | ((x)&3))
#घोषणा ICE1712_STDSP24_0_DAREAR(r, x)	r[0] = ((r[0] & ~4) | (((x)&1)<<2))
#घोषणा ICE1712_STDSP24_1_CHN1(r, x)	r[1] = ((r[1] & ~1) | ((x)&1))
#घोषणा ICE1712_STDSP24_1_CHN2(r, x)	r[1] = ((r[1] & ~2) | (((x)&1)<<1))
#घोषणा ICE1712_STDSP24_1_CHN3(r, x)	r[1] = ((r[1] & ~4) | (((x)&1)<<2))
#घोषणा ICE1712_STDSP24_2_CHN4(r, x)	r[2] = ((r[2] & ~1) | ((x)&1))
#घोषणा ICE1712_STDSP24_2_MIDIIN(r, x)	r[2] = ((r[2] & ~2) | (((x)&1)<<1))
#घोषणा ICE1712_STDSP24_2_MIDI1(r, x)	r[2] = ((r[2] & ~4) | (((x)&1)<<2))
#घोषणा ICE1712_STDSP24_3_MIDI2(r, x)	r[3] = ((r[3] & ~1) | ((x)&1))
#घोषणा ICE1712_STDSP24_3_MUTE(r, x)	r[3] = ((r[3] & ~2) | (((x)&1)<<1))
#घोषणा ICE1712_STDSP24_3_INSEL(r, x)	r[3] = ((r[3] & ~4) | (((x)&1)<<2))
#घोषणा ICE1712_STDSP24_SET_ADDR(r, a)	r[a&3] = ((r[a&3] & ~0x18) | (((a)&3)<<3))
#घोषणा ICE1712_STDSP24_CLOCK(r, a, c)	r[a&3] = ((r[a&3] & ~0x20) | (((c)&1)<<5))
#घोषणा ICE1712_STDSP24_CLOCK_BIT	(1<<5)

/* Hoontech SoundTrack Audio DSP 24 box configuration definitions */

#घोषणा ICE1712_STDSP24_DAREAR		(1<<0)
#घोषणा ICE1712_STDSP24_MUTE		(1<<1)
#घोषणा ICE1712_STDSP24_INSEL		(1<<2)

#घोषणा ICE1712_STDSP24_BOX_CHN1	(1<<0)	/* input channel 1 */
#घोषणा ICE1712_STDSP24_BOX_CHN2	(1<<1)	/* input channel 2 */
#घोषणा ICE1712_STDSP24_BOX_CHN3	(1<<2)	/* input channel 3 */
#घोषणा ICE1712_STDSP24_BOX_CHN4	(1<<3)	/* input channel 4 */
#घोषणा ICE1712_STDSP24_BOX_MIDI1	(1<<8)
#घोषणा ICE1712_STDSP24_BOX_MIDI2	(1<<9)

/* Hoontech SoundTrack Audio DSP 24 Value definitions क्रम modअगरied hardware */

#घोषणा ICE1712_STDSP24_AK4524_CS	0x03	/* AK4524 chip select; low = active */
#घोषणा ICE1712_STDSP24_SERIAL_DATA	0x0c	/* ak4524 data */
#घोषणा ICE1712_STDSP24_SERIAL_CLOCK	0x30	/* ak4524 घड़ी */

#पूर्ण_अगर /* __SOUND_HOONTECH_H */
