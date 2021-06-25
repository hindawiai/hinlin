<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the Auvitek USB bridge
 *
 *  Copyright (c) 2008 Steven Toth <stoth@linuxtv.org>
 */

/* We'll start to नाम these रेजिस्टरs once we have a better
 * understanding of their meaning.
 */
#घोषणा REG_000 0x000
#घोषणा REG_001 0x001
#घोषणा REG_002 0x002
#घोषणा REG_003 0x003

#घोषणा AU0828_SENSORCTRL_100 0x100
#घोषणा AU0828_SENSORCTRL_VBI_103 0x103

/* I2C रेजिस्टरs */
#घोषणा AU0828_I2C_TRIGGER_200		0x200
#घोषणा AU0828_I2C_STATUS_201		0x201
#घोषणा AU0828_I2C_CLK_DIVIDER_202	0x202
#घोषणा AU0828_I2C_DEST_ADDR_203	0x203
#घोषणा AU0828_I2C_WRITE_FIFO_205	0x205
#घोषणा AU0828_I2C_READ_FIFO_209	0x209
#घोषणा AU0828_I2C_MULTIBYTE_MODE_2FF	0x2ff

/* Audio रेजिस्टरs */
#घोषणा AU0828_AUDIOCTRL_50C 0x50C

#घोषणा REG_600 0x600

/*********************************************************************/
/* Here are स्थिरants क्रम values associated with the above रेजिस्टरs */

/* I2C Trigger (Reg 0x200) */
#घोषणा AU0828_I2C_TRIGGER_WRITE	0x01
#घोषणा AU0828_I2C_TRIGGER_READ		0x20
#घोषणा AU0828_I2C_TRIGGER_HOLD		0x40

/* I2C Status (Reg 0x201) */
#घोषणा AU0828_I2C_STATUS_READ_DONE	0x01
#घोषणा AU0828_I2C_STATUS_NO_READ_ACK	0x02
#घोषणा AU0828_I2C_STATUS_WRITE_DONE	0x04
#घोषणा AU0828_I2C_STATUS_NO_WRITE_ACK	0x08
#घोषणा AU0828_I2C_STATUS_BUSY		0x10

/* I2C Clock Divider (Reg 0x202) */
#घोषणा AU0828_I2C_CLK_250KHZ 0x07
#घोषणा AU0828_I2C_CLK_100KHZ 0x14
#घोषणा AU0828_I2C_CLK_30KHZ  0x40
#घोषणा AU0828_I2C_CLK_20KHZ  0x60
