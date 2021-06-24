<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NXP TDA10071 + Conexant CX24118A DVB-S/S2 demodulator + tuner driver
 *
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित TDA10071_PRIV
#घोषणा TDA10071_PRIV

#समावेश <media/dvb_frontend.h>
#समावेश "tda10071.h"
#समावेश <linux/firmware.h>
#समावेश <linux/regmap.h>

काष्ठा tda10071_dev अणु
	काष्ठा dvb_frontend fe;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा mutex cmd_execute_mutex;
	u32 clk;
	u16 i2c_wr_max;
	u8 ts_mode;
	bool spec_inv;
	u8 pll_multiplier;
	u8 tuner_i2c_addr;

	u8 meas_count;
	u32 dvbv3_ber;
	क्रमागत fe_status fe_status;
	क्रमागत fe_delivery_प्रणाली delivery_प्रणाली;
	bool warm; /* FW running */
	u64 post_bit_error;
	u64 block_error;
पूर्ण;

अटल काष्ठा tda10071_modcod अणु
	क्रमागत fe_delivery_प्रणाली delivery_प्रणाली;
	क्रमागत fe_modulation modulation;
	क्रमागत fe_code_rate fec;
	u8 val;
पूर्ण TDA10071_MODCOD[] = अणु
	/* NBC-QPSK */
	अणु SYS_DVBS2, QPSK,  FEC_AUTO, 0x00 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_1_2,  0x04 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_3_5,  0x05 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_2_3,  0x06 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_3_4,  0x07 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_4_5,  0x08 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_5_6,  0x09 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_8_9,  0x0a पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_9_10, 0x0b पूर्ण,
	/* 8PSK */
	अणु SYS_DVBS2, PSK_8, FEC_AUTO, 0x00 पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_3_5,  0x0c पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_2_3,  0x0d पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_3_4,  0x0e पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_5_6,  0x0f पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_8_9,  0x10 पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_9_10, 0x11 पूर्ण,
	/* QPSK */
	अणु SYS_DVBS,  QPSK,  FEC_AUTO, 0x2d पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_1_2,  0x2e पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_2_3,  0x2f पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_3_4,  0x30 पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_5_6,  0x31 पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_7_8,  0x32 पूर्ण,
पूर्ण;

काष्ठा tda10071_reg_val_mask अणु
	u8 reg;
	u8 val;
	u8 mask;
पूर्ण;

/* firmware filename */
#घोषणा TDA10071_FIRMWARE "dvb-fe-tda10071.fw"

/* firmware commands */
#घोषणा CMD_DEMOD_INIT          0x10
#घोषणा CMD_CHANGE_CHANNEL      0x11
#घोषणा CMD_MPEG_CONFIG         0x13
#घोषणा CMD_TUNER_INIT          0x15
#घोषणा CMD_GET_AGCACC          0x1a

#घोषणा CMD_LNB_CONFIG          0x20
#घोषणा CMD_LNB_SEND_DISEQC     0x21
#घोषणा CMD_LNB_SET_DC_LEVEL    0x22
#घोषणा CMD_LNB_PCB_CONFIG      0x23
#घोषणा CMD_LNB_SEND_TONEBURST  0x24
#घोषणा CMD_LNB_UPDATE_REPLY    0x25

#घोषणा CMD_GET_FW_VERSION      0x35
#घोषणा CMD_SET_SLEEP_MODE      0x36
#घोषणा CMD_BER_CONTROL         0x3e
#घोषणा CMD_BER_UPDATE_COUNTERS 0x3f

/* firmware command काष्ठा */
#घोषणा TDA10071_ARGLEN      30
काष्ठा tda10071_cmd अणु
	u8 args[TDA10071_ARGLEN];
	u8 len;
पूर्ण;


#पूर्ण_अगर /* TDA10071_PRIV */
