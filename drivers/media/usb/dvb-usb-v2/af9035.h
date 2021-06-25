<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Afatech AF9035 DVB USB driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 * Copyright (C) 2012 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित AF9035_H
#घोषणा AF9035_H

#समावेश <linux/platक्रमm_device.h>
#समावेश "dvb_usb.h"
#समावेश "af9033.h"
#समावेश "tua9001.h"
#समावेश "fc0011.h"
#समावेश "fc0012.h"
#समावेश "mxl5007t.h"
#समावेश "tda18218.h"
#समावेश "fc2580.h"
#समावेश "it913x.h"
#समावेश "si2168.h"
#समावेश "si2157.h"

काष्ठा reg_val अणु
	u32 reg;
	u8  val;
पूर्ण;

काष्ठा reg_val_mask अणु
	u32 reg;
	u8  val;
	u8  mask;
पूर्ण;

काष्ठा usb_req अणु
	u8  cmd;
	u8  mbox;
	u8  wlen;
	u8  *wbuf;
	u8  rlen;
	u8  *rbuf;
पूर्ण;

काष्ठा state अणु
#घोषणा BUF_LEN 64
	u8 buf[BUF_LEN];
	u8 seq; /* packet sequence number */
	u8 prechip_version;
	u8 chip_version;
	u16 chip_type;
	u8 eeprom[256];
	bool no_eeprom;
	u8 ir_mode;
	u8 ir_type;
	u8 dual_mode:1;
	u8 no_पढ़ो:1;
	u8 af9033_i2c_addr[2];
	u8 it930x_addresses;
	काष्ठा af9033_config af9033_config[2];
	काष्ठा af9033_ops ops;
	#घोषणा AF9035_I2C_CLIENT_MAX 4
	काष्ठा i2c_client *i2c_client[AF9035_I2C_CLIENT_MAX];
	काष्ठा i2c_adapter *i2c_adapter_demod;
	काष्ठा platक्रमm_device *platक्रमm_device_tuner[2];
पूर्ण;

काष्ठा address_table अणु
	u8 frontend_i2c_addr;
	u8 tuner_i2c_addr;
	u8 tuner_अगर_port;
पूर्ण;

अटल स्थिर काष्ठा address_table it930x_addresses_table[] = अणु
	अणु 0x67, 0x63, 1 पूर्ण,
	अणु 0x64, 0x60, 0 पूर्ण,
पूर्ण;

अटल स्थिर u32 घड़ी_lut_af9035[] = अणु
	20480000, /*      FPGA */
	16384000, /* 16.38 MHz */
	20480000, /* 20.48 MHz */
	36000000, /* 36.00 MHz */
	30000000, /* 30.00 MHz */
	26000000, /* 26.00 MHz */
	28000000, /* 28.00 MHz */
	32000000, /* 32.00 MHz */
	34000000, /* 34.00 MHz */
	24000000, /* 24.00 MHz */
	22000000, /* 22.00 MHz */
	12000000, /* 12.00 MHz */
पूर्ण;

अटल स्थिर u32 घड़ी_lut_it9135[] = अणु
	12000000, /* 12.00 MHz */
	20480000, /* 20.48 MHz */
	36000000, /* 36.00 MHz */
	30000000, /* 30.00 MHz */
	26000000, /* 26.00 MHz */
	28000000, /* 28.00 MHz */
	32000000, /* 32.00 MHz */
	34000000, /* 34.00 MHz */
	24000000, /* 24.00 MHz */
	22000000, /* 22.00 MHz */
पूर्ण;

#घोषणा AF9035_FIRMWARE_AF9035 "dvb-usb-af9035-02.fw"
#घोषणा AF9035_FIRMWARE_IT9135_V1 "dvb-usb-it9135-01.fw"
#घोषणा AF9035_FIRMWARE_IT9135_V2 "dvb-usb-it9135-02.fw"
#घोषणा AF9035_FIRMWARE_IT9303 "dvb-usb-it9303-01.fw"

/*
 * eeprom is memory mapped as पढ़ो only. Writing that memory mapped address
 * will not corrupt eeprom.
 *
 * TS mode:
 * 0  TS
 * 1  DCA + PIP
 * 3  PIP
 * 5  DCA + PIP (AF9035 only)
 * n  DCA
 *
 * Values 0, 3 and 5 are seen to this day. 0 क्रम single TS and 3/5 क्रम dual TS.
 */

#घोषणा EEPROM_BASE_AF9035        0x42f5
#घोषणा EEPROM_BASE_IT9135        0x4994
#घोषणा EEPROM_SHIFT                0x10

#घोषणा EEPROM_IR_MODE              0x18
#घोषणा EEPROM_TS_MODE              0x31
#घोषणा EEPROM_2ND_DEMOD_ADDR       0x32
#घोषणा EEPROM_IR_TYPE              0x34
#घोषणा EEPROM_1_IF_L               0x38
#घोषणा EEPROM_1_IF_H               0x39
#घोषणा EEPROM_1_TUNER_ID           0x3c
#घोषणा EEPROM_2_IF_L               0x48
#घोषणा EEPROM_2_IF_H               0x49
#घोषणा EEPROM_2_TUNER_ID           0x4c

/* USB commands */
#घोषणा CMD_MEM_RD                  0x00
#घोषणा CMD_MEM_WR                  0x01
#घोषणा CMD_I2C_RD                  0x02
#घोषणा CMD_I2C_WR                  0x03
#घोषणा CMD_IR_GET                  0x18
#घोषणा CMD_FW_DL                   0x21
#घोषणा CMD_FW_QUERYINFO            0x22
#घोषणा CMD_FW_BOOT                 0x23
#घोषणा CMD_FW_DL_BEGIN             0x24
#घोषणा CMD_FW_DL_END               0x25
#घोषणा CMD_FW_SCATTER_WR           0x29
#घोषणा CMD_GENERIC_I2C_RD          0x2a
#घोषणा CMD_GENERIC_I2C_WR          0x2b

#पूर्ण_अगर
