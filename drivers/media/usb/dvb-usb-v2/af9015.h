<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * DVB USB Linux driver क्रम Afatech AF9015 DVB-T USB2.0 receiver
 *
 * Copyright (C) 2007 Antti Palosaari <crope@iki.fi>
 *
 * Thanks to Afatech who kindly provided inक्रमmation.
 */

#अगर_अघोषित AF9015_H
#घोषणा AF9015_H

#समावेश <linux/hash.h>
#समावेश <linux/regmap.h>
#समावेश "dvb_usb.h"
#समावेश "af9013.h"
#समावेश "dvb-pll.h"
#समावेश "mt2060.h"
#समावेश "qt1010.h"
#समावेश "tda18271.h"
#समावेश "mxl5005s.h"
#समावेश "mc44s803.h"
#समावेश "tda18218.h"
#समावेश "mxl5007t.h"

#घोषणा AF9015_FIRMWARE "dvb-usb-af9015.fw"

#घोषणा AF9015_I2C_EEPROM  0x50
#घोषणा AF9015_I2C_DEMOD   0x1c
#घोषणा AF9015_USB_TIMEOUT 2000

/* EEPROM locations */
#घोषणा AF9015_EEPROM_IR_MODE        0x18
#घोषणा AF9015_EEPROM_IR_REMOTE_TYPE 0x34
#घोषणा AF9015_EEPROM_TS_MODE        0x31
#घोषणा AF9015_EEPROM_DEMOD2_I2C     0x32

#घोषणा AF9015_EEPROM_SAW_BW1        0x35
#घोषणा AF9015_EEPROM_XTAL_TYPE1     0x36
#घोषणा AF9015_EEPROM_SPEC_INV1      0x37
#घोषणा AF9015_EEPROM_IF1L           0x38
#घोषणा AF9015_EEPROM_IF1H           0x39
#घोषणा AF9015_EEPROM_MT2060_IF1L    0x3a
#घोषणा AF9015_EEPROM_MT2060_IF1H    0x3b
#घोषणा AF9015_EEPROM_TUNER_ID1      0x3c

#घोषणा AF9015_EEPROM_SAW_BW2        0x45
#घोषणा AF9015_EEPROM_XTAL_TYPE2     0x46
#घोषणा AF9015_EEPROM_SPEC_INV2      0x47
#घोषणा AF9015_EEPROM_IF2L           0x48
#घोषणा AF9015_EEPROM_IF2H           0x49
#घोषणा AF9015_EEPROM_MT2060_IF2L    0x4a
#घोषणा AF9015_EEPROM_MT2060_IF2H    0x4b
#घोषणा AF9015_EEPROM_TUNER_ID2      0x4c

#घोषणा AF9015_EEPROM_OFFSET (AF9015_EEPROM_SAW_BW2 - AF9015_EEPROM_SAW_BW1)

काष्ठा req_t अणु
	u8  cmd;       /* [0] */
	/*  seq */     /* [1] */
	u8  i2c_addr;  /* [2] */
	u16 addr;      /* [3|4] */
	u8  mbox;      /* [5] */
	u8  addr_len;  /* [6] */
	u8  data_len;  /* [7] */
	u8  *data;
पूर्ण;

क्रमागत af9015_cmd अणु
	GET_CONFIG           = 0x10,
	DOWNLOAD_FIRMWARE    = 0x11,
	BOOT                 = 0x13,
	READ_MEMORY          = 0x20,
	WRITE_MEMORY         = 0x21,
	READ_WRITE_I2C       = 0x22,
	COPY_FIRMWARE        = 0x23,
	RECONNECT_USB        = 0x5a,
	WRITE_VIRTUAL_MEMORY = 0x26,
	GET_IR_CODE          = 0x27,
	READ_I2C,
	WRITE_I2C,
पूर्ण;

क्रमागत af9015_ir_mode अणु
	AF9015_IR_MODE_DISABLED = 0,
	AF9015_IR_MODE_HID,
	AF9015_IR_MODE_RLC,
	AF9015_IR_MODE_RC6,
	AF9015_IR_MODE_POLLING, /* just guess */
पूर्ण;

#घोषणा BUF_LEN 63
काष्ठा af9015_state अणु
	काष्ठा regmap *regmap;
	u8 buf[BUF_LEN]; /* bulk USB control message */
	u8 ir_mode;
	u8 rc_repeat;
	u32 rc_keycode;
	u8 rc_last[4];
	bool rc_failed;
	u8 dual_mode;
	u8 seq; /* packet sequence number */
	u16 mt2060_अगर1[2];
	u16 firmware_size;
	u16 firmware_checksum;
	u32 eeprom_sum;
	काष्ठा af9013_platक्रमm_data af9013_pdata[2];
	काष्ठा i2c_client *demod_i2c_client[2];
	u8 af9013_i2c_addr[2];
	bool usb_ts_अगर_configured[2];

	/* क्रम demod callback override */
	पूर्णांक (*set_frontend[2]) (काष्ठा dvb_frontend *fe);
	पूर्णांक (*पढ़ो_status[2]) (काष्ठा dvb_frontend *fe, क्रमागत fe_status *status);
	पूर्णांक (*init[2]) (काष्ठा dvb_frontend *fe);
	पूर्णांक (*sleep[2]) (काष्ठा dvb_frontend *fe);
	पूर्णांक (*tuner_init[2]) (काष्ठा dvb_frontend *fe);
	पूर्णांक (*tuner_sleep[2]) (काष्ठा dvb_frontend *fe);
	काष्ठा mutex fe_mutex;
पूर्ण;

क्रमागत af9015_remote अणु
	AF9015_REMOTE_NONE                    = 0,
/* 1 */	AF9015_REMOTE_A_LINK_DTU_M,
	AF9015_REMOTE_MSI_DIGIVOX_MINI_II_V3,
	AF9015_REMOTE_MYGICTV_U718,
	AF9015_REMOTE_DIGITTRADE_DVB_T,
/* 5 */	AF9015_REMOTE_AVERMEDIA_KS,
पूर्ण;

#पूर्ण_अगर
