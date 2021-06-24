<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_AMP_H
#घोषणा __SOUND_AMP_H

/*
 *   ALSA driver क्रम VIA VT1724 (Envy24HT)
 *
 *   Lowlevel functions क्रम Advanced Micro Peripherals Ltd AUDIO2000
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 */      

#घोषणा  AMP_AUDIO2000_DEVICE_DESC 	       "{AMP Ltd,AUDIO2000},"\
					       "{Chaintech,AV-710},"

#अगर 0
#घोषणा VT1724_SUBDEVICE_AUDIO2000	0x12142417	/* Advanced Micro Peripherals Ltd AUDIO2000 */
#अन्यथा
#घोषणा VT1724_SUBDEVICE_AUDIO2000	0x00030003	/* a dummy ID क्रम AMP Audio2000 */
#पूर्ण_अगर
#घोषणा VT1724_SUBDEVICE_AV710		0x12142417	/* AV710 - the same ID with Audio2000! */

/* WM8728 on I2C क्रम AV710 */
#घोषणा WM_DEV		0x36

#घोषणा WM_ATTEN_L	0x00
#घोषणा WM_ATTEN_R	0x01
#घोषणा WM_DAC_CTRL	0x02
#घोषणा WM_INT_CTRL	0x03

बाह्य काष्ठा snd_ice1712_card_info  snd_vt1724_amp_cards[];


#पूर्ण_अगर /* __SOUND_AMP_H */
