<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_REVO_H
#घोषणा __SOUND_REVO_H

/*
 *   ALSA driver क्रम ICEnsemble ICE1712 (Envy24)
 *
 *   Lowlevel functions क्रम M-Audio Revolution 7.1
 *
 *	Copyright (c) 2003 Takashi Iwai <tiwai@suse.de>
 */      

#घोषणा REVO_DEVICE_DESC \
		"{MidiMan M Audio,Revolution 7.1},"\
		"{MidiMan M Audio,Revolution 5.1},"\
		"{MidiMan M Audio,Audiophile 192},"

#घोषणा VT1724_SUBDEVICE_REVOLUTION71	0x12143036
#घोषणा VT1724_SUBDEVICE_REVOLUTION51	0x12143136
#घोषणा VT1724_SUBDEVICE_AUDIOPHILE192	0x12143236

/* entry poपूर्णांक */
बाह्य काष्ठा snd_ice1712_card_info snd_vt1724_revo_cards[];


/*
 *  MidiMan M-Audio Revolution GPIO definitions
 */

#घोषणा VT1724_REVO_CCLK	0x02
#घोषणा VT1724_REVO_CDIN	0x04	/* not used */
#घोषणा VT1724_REVO_CDOUT	0x08
#घोषणा VT1724_REVO_CS0		0x10	/* AK5365 chipselect क्रम (revo51) */
#घोषणा VT1724_REVO_CS1		0x20	/* front AKM4381 chipselect */
#घोषणा VT1724_REVO_CS2		0x40	/* surround AKM4355 CS (revo71) */
#घोषणा VT1724_REVO_I2C_DATA    0x40    /* I2C: PT 2258 SDA (on revo51) */
#घोषणा VT1724_REVO_I2C_CLOCK   0x80    /* I2C: PT 2258 SCL (on revo51) */
#घोषणा VT1724_REVO_CS3		0x80	/* AK4114 क्रम AP192 */
#घोषणा VT1724_REVO_MUTE	(1<<22)	/* 0 = all mute, 1 = normal operation */

#पूर्ण_अगर /* __SOUND_REVO_H */
