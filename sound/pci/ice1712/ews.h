<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_EWS_H
#घोषणा __SOUND_EWS_H

/*
 *   ALSA driver क्रम ICEnsemble ICE1712 (Envy24)
 *
 *   Lowlevel functions क्रम Terratec EWS88MT/D, EWX24/96, DMX 6Fire
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 *                    2002 Takashi Iwai <tiwai@suse.de>
 */      

#घोषणा EWS_DEVICE_DESC \
		"{TerraTec,EWX 24/96},"\
		"{TerraTec,EWS 88MT},"\
		"{TerraTec,EWS 88D},"\
		"{TerraTec,DMX 6Fire},"\
		"{TerraTec,Phase 88}," \
		"{terrasoniq,TS 88},"

#घोषणा ICE1712_SUBDEVICE_EWX2496	0x3b153011
#घोषणा ICE1712_SUBDEVICE_EWS88MT	0x3b151511
#घोषणा ICE1712_SUBDEVICE_EWS88MT_NEW	0x3b152511
#घोषणा ICE1712_SUBDEVICE_EWS88D	0x3b152b11
#घोषणा ICE1712_SUBDEVICE_DMX6FIRE	0x3b153811
#घोषणा ICE1712_SUBDEVICE_PHASE88	0x3b155111
#घोषणा ICE1712_SUBDEVICE_TS88   	0x3b157c11

/* entry poपूर्णांक */
बाह्य काष्ठा snd_ice1712_card_info snd_ice1712_ews_cards[];


/* TerraTec EWX 24/96 configuration definitions */

#घोषणा ICE1712_EWX2496_AK4524_CS	0x01	/* AK4524 chip select; low = active */
#घोषणा ICE1712_EWX2496_AIN_SEL		0x02	/* input sensitivity चयन; high = louder */
#घोषणा ICE1712_EWX2496_AOUT_SEL	0x04	/* output sensitivity चयन; high = louder */
#घोषणा ICE1712_EWX2496_RW		0x08	/* पढ़ो/ग_लिखो चयन क्रम i2c; high = ग_लिखो  */
#घोषणा ICE1712_EWX2496_SERIAL_DATA	0x10	/* i2c & ak4524 data */
#घोषणा ICE1712_EWX2496_SERIAL_CLOCK	0x20	/* i2c & ak4524 घड़ी */
#घोषणा ICE1712_EWX2496_TX2		0x40	/* MIDI2 (not used) */
#घोषणा ICE1712_EWX2496_RX2		0x80	/* MIDI2 (not used) */

/* TerraTec EWS 88MT/D configuration definitions */
/* RW, SDA snd SCLK are identical with EWX24/96 */
#घोषणा ICE1712_EWS88_CS8414_RATE	0x07	/* CS8414 sample rate: gpio 0-2 */
#घोषणा ICE1712_EWS88_RW		0x08	/* पढ़ो/ग_लिखो चयन क्रम i2c; high = ग_लिखो  */
#घोषणा ICE1712_EWS88_SERIAL_DATA	0x10	/* i2c & ak4524 data */
#घोषणा ICE1712_EWS88_SERIAL_CLOCK	0x20	/* i2c & ak4524 घड़ी */
#घोषणा ICE1712_EWS88_TX2		0x40	/* MIDI2 (only on 88D) */
#घोषणा ICE1712_EWS88_RX2		0x80	/* MIDI2 (only on 88D) */

/* i2c address */
#घोषणा ICE1712_EWS88MT_CS8404_ADDR	(0x40>>1)
#घोषणा ICE1712_EWS88MT_INPUT_ADDR	(0x46>>1)
#घोषणा ICE1712_EWS88MT_OUTPUT_ADDR	(0x48>>1)
#घोषणा ICE1712_EWS88MT_OUTPUT_SENSE	0x40	/* mask */
#घोषणा ICE1712_EWS88D_PCF_ADDR		(0x40>>1)

/* TerraTec DMX 6Fire configuration definitions */
#घोषणा ICE1712_6FIRE_AK4524_CS_MASK	0x07	/* AK4524 chip select #1-#3 */
#घोषणा ICE1712_6FIRE_RW		0x08	/* पढ़ो/ग_लिखो चयन क्रम i2c; high = ग_लिखो  */
#घोषणा ICE1712_6FIRE_SERIAL_DATA	0x10	/* i2c & ak4524 data */
#घोषणा ICE1712_6FIRE_SERIAL_CLOCK	0x20	/* i2c & ak4524 घड़ी */
#घोषणा ICE1712_6FIRE_TX2		0x40	/* MIDI2 */
#घोषणा ICE1712_6FIRE_RX2		0x80	/* MIDI2 */

#घोषणा ICE1712_6FIRE_PCF9554_ADDR	(0x40>>1)
#घोषणा ICE1712_6FIRE_CS8427_ADDR	(0x22)

#पूर्ण_अगर /* __SOUND_EWS_H */
