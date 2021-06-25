<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Maxim MAX2165 silicon tuner
 *
 *  Copyright (c) 2009 David T. L. Wong <davidtlwong@gmail.com>
 */

#अगर_अघोषित __MAX2165_PRIV_H__
#घोषणा __MAX2165_PRIV_H__

#घोषणा REG_NDIV_INT 0x00
#घोषणा REG_NDIV_FRAC2 0x01
#घोषणा REG_NDIV_FRAC1 0x02
#घोषणा REG_NDIV_FRAC0 0x03
#घोषणा REG_TRACK_FILTER 0x04
#घोषणा REG_LNA 0x05
#घोषणा REG_PLL_CFG 0x06
#घोषणा REG_TEST 0x07
#घोषणा REG_SHUTDOWN 0x08
#घोषणा REG_VCO_CTRL 0x09
#घोषणा REG_BASEBAND_CTRL 0x0A
#घोषणा REG_DC_OFFSET_CTRL 0x0B
#घोषणा REG_DC_OFFSET_DAC 0x0C
#घोषणा REG_ROM_TABLE_ADDR 0x0D

/* Read Only Registers */
#घोषणा REG_ROM_TABLE_DATA 0x10
#घोषणा REG_STATUS 0x11
#घोषणा REG_AUTOTUNE 0x12

काष्ठा max2165_priv अणु
	काष्ठा max2165_config *config;
	काष्ठा i2c_adapter *i2c;

	u32 frequency;
	u32 bandwidth;

	u8 tf_ntch_low_cfg;
	u8 tf_ntch_hi_cfg;
	u8 tf_balun_low_ref;
	u8 tf_balun_hi_ref;
	u8 bb_filter_7mhz_cfg;
	u8 bb_filter_8mhz_cfg;
पूर्ण;

#पूर्ण_अगर
