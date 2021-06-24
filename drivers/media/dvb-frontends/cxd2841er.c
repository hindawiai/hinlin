<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cxd2841er.c
 *
 * Sony digital demodulator driver क्रम
 *	CXD2841ER - DVB-S/S2/T/T2/C/C2
 *	CXD2854ER - DVB-S/S2/T/T2/C/C2, ISDB-T/S
 *
 * Copyright 2012 Sony Corporation
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
  */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/math64.h>
#समावेश <linux/log2.h>
#समावेश <linux/dynamic_debug.h>
#समावेश <linux/kernel.h>

#समावेश <media/dvb_गणित.स>
#समावेश <media/dvb_frontend.h>
#समावेश "cxd2841er.h"
#समावेश "cxd2841er_priv.h"

#घोषणा MAX_WRITE_REGSIZE	16
#घोषणा LOG2_E_100X 144

#घोषणा INTLOG10X100(x) ((u32) (((u64) पूर्णांकlog10(x) * 100) >> 24))

/* DVB-C स्थिरellation */
क्रमागत sony_dvbc_स्थिरellation_t अणु
	SONY_DVBC_CONSTELLATION_16QAM,
	SONY_DVBC_CONSTELLATION_32QAM,
	SONY_DVBC_CONSTELLATION_64QAM,
	SONY_DVBC_CONSTELLATION_128QAM,
	SONY_DVBC_CONSTELLATION_256QAM
पूर्ण;

क्रमागत cxd2841er_state अणु
	STATE_SHUTDOWN = 0,
	STATE_SLEEP_S,
	STATE_ACTIVE_S,
	STATE_SLEEP_TC,
	STATE_ACTIVE_TC
पूर्ण;

काष्ठा cxd2841er_priv अणु
	काष्ठा dvb_frontend		frontend;
	काष्ठा i2c_adapter		*i2c;
	u8				i2c_addr_slvx;
	u8				i2c_addr_slvt;
	स्थिर काष्ठा cxd2841er_config	*config;
	क्रमागत cxd2841er_state		state;
	u8				प्रणाली;
	क्रमागत cxd2841er_xtal		xtal;
	क्रमागत fe_caps caps;
	u32				flags;
	अचिन्हित दीर्घ			stats_समय;
पूर्ण;

अटल स्थिर काष्ठा cxd2841er_cnr_data s_cn_data[] = अणु
	अणु 0x033e, 0 पूर्ण, अणु 0x0339, 100 पूर्ण, अणु 0x0333, 200 पूर्ण,
	अणु 0x032e, 300 पूर्ण, अणु 0x0329, 400 पूर्ण, अणु 0x0324, 500 पूर्ण,
	अणु 0x031e, 600 पूर्ण, अणु 0x0319, 700 पूर्ण, अणु 0x0314, 800 पूर्ण,
	अणु 0x030f, 900 पूर्ण, अणु 0x030a, 1000 पूर्ण, अणु 0x02ff, 1100 पूर्ण,
	अणु 0x02f4, 1200 पूर्ण, अणु 0x02e9, 1300 पूर्ण, अणु 0x02de, 1400 पूर्ण,
	अणु 0x02d4, 1500 पूर्ण, अणु 0x02c9, 1600 पूर्ण, अणु 0x02bf, 1700 पूर्ण,
	अणु 0x02b5, 1800 पूर्ण, अणु 0x02ab, 1900 पूर्ण, अणु 0x02a1, 2000 पूर्ण,
	अणु 0x029b, 2100 पूर्ण, अणु 0x0295, 2200 पूर्ण, अणु 0x0290, 2300 पूर्ण,
	अणु 0x028a, 2400 पूर्ण, अणु 0x0284, 2500 पूर्ण, अणु 0x027f, 2600 पूर्ण,
	अणु 0x0279, 2700 पूर्ण, अणु 0x0274, 2800 पूर्ण, अणु 0x026e, 2900 पूर्ण,
	अणु 0x0269, 3000 पूर्ण, अणु 0x0262, 3100 पूर्ण, अणु 0x025c, 3200 पूर्ण,
	अणु 0x0255, 3300 पूर्ण, अणु 0x024f, 3400 पूर्ण, अणु 0x0249, 3500 पूर्ण,
	अणु 0x0242, 3600 पूर्ण, अणु 0x023c, 3700 पूर्ण, अणु 0x0236, 3800 पूर्ण,
	अणु 0x0230, 3900 पूर्ण, अणु 0x022a, 4000 पूर्ण, अणु 0x0223, 4100 पूर्ण,
	अणु 0x021c, 4200 पूर्ण, अणु 0x0215, 4300 पूर्ण, अणु 0x020e, 4400 पूर्ण,
	अणु 0x0207, 4500 पूर्ण, अणु 0x0201, 4600 पूर्ण, अणु 0x01fa, 4700 पूर्ण,
	अणु 0x01f4, 4800 पूर्ण, अणु 0x01ed, 4900 पूर्ण, अणु 0x01e7, 5000 पूर्ण,
	अणु 0x01e0, 5100 पूर्ण, अणु 0x01d9, 5200 पूर्ण, अणु 0x01d2, 5300 पूर्ण,
	अणु 0x01cb, 5400 पूर्ण, अणु 0x01c4, 5500 पूर्ण, अणु 0x01be, 5600 पूर्ण,
	अणु 0x01b7, 5700 पूर्ण, अणु 0x01b1, 5800 पूर्ण, अणु 0x01aa, 5900 पूर्ण,
	अणु 0x01a4, 6000 पूर्ण, अणु 0x019d, 6100 पूर्ण, अणु 0x0196, 6200 पूर्ण,
	अणु 0x018f, 6300 पूर्ण, अणु 0x0189, 6400 पूर्ण, अणु 0x0182, 6500 पूर्ण,
	अणु 0x017c, 6600 पूर्ण, अणु 0x0175, 6700 पूर्ण, अणु 0x016f, 6800 पूर्ण,
	अणु 0x0169, 6900 पूर्ण, अणु 0x0163, 7000 पूर्ण, अणु 0x015c, 7100 पूर्ण,
	अणु 0x0156, 7200 पूर्ण, अणु 0x0150, 7300 पूर्ण, अणु 0x014a, 7400 पूर्ण,
	अणु 0x0144, 7500 पूर्ण, अणु 0x013e, 7600 पूर्ण, अणु 0x0138, 7700 पूर्ण,
	अणु 0x0132, 7800 पूर्ण, अणु 0x012d, 7900 पूर्ण, अणु 0x0127, 8000 पूर्ण,
	अणु 0x0121, 8100 पूर्ण, अणु 0x011c, 8200 पूर्ण, अणु 0x0116, 8300 पूर्ण,
	अणु 0x0111, 8400 पूर्ण, अणु 0x010b, 8500 पूर्ण, अणु 0x0106, 8600 पूर्ण,
	अणु 0x0101, 8700 पूर्ण, अणु 0x00fc, 8800 पूर्ण, अणु 0x00f7, 8900 पूर्ण,
	अणु 0x00f2, 9000 पूर्ण, अणु 0x00ee, 9100 पूर्ण, अणु 0x00ea, 9200 पूर्ण,
	अणु 0x00e6, 9300 पूर्ण, अणु 0x00e2, 9400 पूर्ण, अणु 0x00de, 9500 पूर्ण,
	अणु 0x00da, 9600 पूर्ण, अणु 0x00d7, 9700 पूर्ण, अणु 0x00d3, 9800 पूर्ण,
	अणु 0x00d0, 9900 पूर्ण, अणु 0x00cc, 10000 पूर्ण, अणु 0x00c7, 10100 पूर्ण,
	अणु 0x00c3, 10200 पूर्ण, अणु 0x00bf, 10300 पूर्ण, अणु 0x00ba, 10400 पूर्ण,
	अणु 0x00b6, 10500 पूर्ण, अणु 0x00b2, 10600 पूर्ण, अणु 0x00ae, 10700 पूर्ण,
	अणु 0x00aa, 10800 पूर्ण, अणु 0x00a7, 10900 पूर्ण, अणु 0x00a3, 11000 पूर्ण,
	अणु 0x009f, 11100 पूर्ण, अणु 0x009c, 11200 पूर्ण, अणु 0x0098, 11300 पूर्ण,
	अणु 0x0094, 11400 पूर्ण, अणु 0x0091, 11500 पूर्ण, अणु 0x008e, 11600 पूर्ण,
	अणु 0x008a, 11700 पूर्ण, अणु 0x0087, 11800 पूर्ण, अणु 0x0084, 11900 पूर्ण,
	अणु 0x0081, 12000 पूर्ण, अणु 0x007e, 12100 पूर्ण, अणु 0x007b, 12200 पूर्ण,
	अणु 0x0079, 12300 पूर्ण, अणु 0x0076, 12400 पूर्ण, अणु 0x0073, 12500 पूर्ण,
	अणु 0x0071, 12600 पूर्ण, अणु 0x006e, 12700 पूर्ण, अणु 0x006c, 12800 पूर्ण,
	अणु 0x0069, 12900 पूर्ण, अणु 0x0067, 13000 पूर्ण, अणु 0x0065, 13100 पूर्ण,
	अणु 0x0062, 13200 पूर्ण, अणु 0x0060, 13300 पूर्ण, अणु 0x005e, 13400 पूर्ण,
	अणु 0x005c, 13500 पूर्ण, अणु 0x005a, 13600 पूर्ण, अणु 0x0058, 13700 पूर्ण,
	अणु 0x0056, 13800 पूर्ण, अणु 0x0054, 13900 पूर्ण, अणु 0x0052, 14000 पूर्ण,
	अणु 0x0050, 14100 पूर्ण, अणु 0x004e, 14200 पूर्ण, अणु 0x004c, 14300 पूर्ण,
	अणु 0x004b, 14400 पूर्ण, अणु 0x0049, 14500 पूर्ण, अणु 0x0047, 14600 पूर्ण,
	अणु 0x0046, 14700 पूर्ण, अणु 0x0044, 14800 पूर्ण, अणु 0x0043, 14900 पूर्ण,
	अणु 0x0041, 15000 पूर्ण, अणु 0x003f, 15100 पूर्ण, अणु 0x003e, 15200 पूर्ण,
	अणु 0x003c, 15300 पूर्ण, अणु 0x003b, 15400 पूर्ण, अणु 0x003a, 15500 पूर्ण,
	अणु 0x0037, 15700 पूर्ण, अणु 0x0036, 15800 पूर्ण, अणु 0x0034, 15900 पूर्ण,
	अणु 0x0033, 16000 पूर्ण, अणु 0x0032, 16100 पूर्ण, अणु 0x0031, 16200 पूर्ण,
	अणु 0x0030, 16300 पूर्ण, अणु 0x002f, 16400 पूर्ण, अणु 0x002e, 16500 पूर्ण,
	अणु 0x002d, 16600 पूर्ण, अणु 0x002c, 16700 पूर्ण, अणु 0x002b, 16800 पूर्ण,
	अणु 0x002a, 16900 पूर्ण, अणु 0x0029, 17000 पूर्ण, अणु 0x0028, 17100 पूर्ण,
	अणु 0x0027, 17200 पूर्ण, अणु 0x0026, 17300 पूर्ण, अणु 0x0025, 17400 पूर्ण,
	अणु 0x0024, 17500 पूर्ण, अणु 0x0023, 17600 पूर्ण, अणु 0x0022, 17800 पूर्ण,
	अणु 0x0021, 17900 पूर्ण, अणु 0x0020, 18000 पूर्ण, अणु 0x001f, 18200 पूर्ण,
	अणु 0x001e, 18300 पूर्ण, अणु 0x001d, 18500 पूर्ण, अणु 0x001c, 18700 पूर्ण,
	अणु 0x001b, 18900 पूर्ण, अणु 0x001a, 19000 पूर्ण, अणु 0x0019, 19200 पूर्ण,
	अणु 0x0018, 19300 पूर्ण, अणु 0x0017, 19500 पूर्ण, अणु 0x0016, 19700 पूर्ण,
	अणु 0x0015, 19900 पूर्ण, अणु 0x0014, 20000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxd2841er_cnr_data s2_cn_data[] = अणु
	अणु 0x05af, 0 पूर्ण, अणु 0x0597, 100 पूर्ण, अणु 0x057e, 200 पूर्ण,
	अणु 0x0567, 300 पूर्ण, अणु 0x0550, 400 पूर्ण, अणु 0x0539, 500 पूर्ण,
	अणु 0x0522, 600 पूर्ण, अणु 0x050c, 700 पूर्ण, अणु 0x04f6, 800 पूर्ण,
	अणु 0x04e1, 900 पूर्ण, अणु 0x04cc, 1000 पूर्ण, अणु 0x04b6, 1100 पूर्ण,
	अणु 0x04a1, 1200 पूर्ण, अणु 0x048c, 1300 पूर्ण, अणु 0x0477, 1400 पूर्ण,
	अणु 0x0463, 1500 पूर्ण, अणु 0x044f, 1600 पूर्ण, अणु 0x043c, 1700 पूर्ण,
	अणु 0x0428, 1800 पूर्ण, अणु 0x0416, 1900 पूर्ण, अणु 0x0403, 2000 पूर्ण,
	अणु 0x03ef, 2100 पूर्ण, अणु 0x03dc, 2200 पूर्ण, अणु 0x03c9, 2300 पूर्ण,
	अणु 0x03b6, 2400 पूर्ण, अणु 0x03a4, 2500 पूर्ण, अणु 0x0392, 2600 पूर्ण,
	अणु 0x0381, 2700 पूर्ण, अणु 0x036f, 2800 पूर्ण, अणु 0x035f, 2900 पूर्ण,
	अणु 0x034e, 3000 पूर्ण, अणु 0x033d, 3100 पूर्ण, अणु 0x032d, 3200 पूर्ण,
	अणु 0x031d, 3300 पूर्ण, अणु 0x030d, 3400 पूर्ण, अणु 0x02fd, 3500 पूर्ण,
	अणु 0x02ee, 3600 पूर्ण, अणु 0x02df, 3700 पूर्ण, अणु 0x02d0, 3800 पूर्ण,
	अणु 0x02c2, 3900 पूर्ण, अणु 0x02b4, 4000 पूर्ण, अणु 0x02a6, 4100 पूर्ण,
	अणु 0x0299, 4200 पूर्ण, अणु 0x028c, 4300 पूर्ण, अणु 0x027f, 4400 पूर्ण,
	अणु 0x0272, 4500 पूर्ण, अणु 0x0265, 4600 पूर्ण, अणु 0x0259, 4700 पूर्ण,
	अणु 0x024d, 4800 पूर्ण, अणु 0x0241, 4900 पूर्ण, अणु 0x0236, 5000 पूर्ण,
	अणु 0x022b, 5100 पूर्ण, अणु 0x0220, 5200 पूर्ण, अणु 0x0215, 5300 पूर्ण,
	अणु 0x020a, 5400 पूर्ण, अणु 0x0200, 5500 पूर्ण, अणु 0x01f6, 5600 पूर्ण,
	अणु 0x01ec, 5700 पूर्ण, अणु 0x01e2, 5800 पूर्ण, अणु 0x01d8, 5900 पूर्ण,
	अणु 0x01cf, 6000 पूर्ण, अणु 0x01c6, 6100 पूर्ण, अणु 0x01bc, 6200 पूर्ण,
	अणु 0x01b3, 6300 पूर्ण, अणु 0x01aa, 6400 पूर्ण, अणु 0x01a2, 6500 पूर्ण,
	अणु 0x0199, 6600 पूर्ण, अणु 0x0191, 6700 पूर्ण, अणु 0x0189, 6800 पूर्ण,
	अणु 0x0181, 6900 पूर्ण, अणु 0x0179, 7000 पूर्ण, अणु 0x0171, 7100 पूर्ण,
	अणु 0x0169, 7200 पूर्ण, अणु 0x0161, 7300 पूर्ण, अणु 0x015a, 7400 पूर्ण,
	अणु 0x0153, 7500 पूर्ण, अणु 0x014b, 7600 पूर्ण, अणु 0x0144, 7700 पूर्ण,
	अणु 0x013d, 7800 पूर्ण, अणु 0x0137, 7900 पूर्ण, अणु 0x0130, 8000 पूर्ण,
	अणु 0x012a, 8100 पूर्ण, अणु 0x0124, 8200 पूर्ण, अणु 0x011e, 8300 पूर्ण,
	अणु 0x0118, 8400 पूर्ण, अणु 0x0112, 8500 पूर्ण, अणु 0x010c, 8600 पूर्ण,
	अणु 0x0107, 8700 पूर्ण, अणु 0x0101, 8800 पूर्ण, अणु 0x00fc, 8900 पूर्ण,
	अणु 0x00f7, 9000 पूर्ण, अणु 0x00f2, 9100 पूर्ण, अणु 0x00ec, 9200 पूर्ण,
	अणु 0x00e7, 9300 पूर्ण, अणु 0x00e2, 9400 पूर्ण, अणु 0x00dd, 9500 पूर्ण,
	अणु 0x00d8, 9600 पूर्ण, अणु 0x00d4, 9700 पूर्ण, अणु 0x00cf, 9800 पूर्ण,
	अणु 0x00ca, 9900 पूर्ण, अणु 0x00c6, 10000 पूर्ण, अणु 0x00c2, 10100 पूर्ण,
	अणु 0x00be, 10200 पूर्ण, अणु 0x00b9, 10300 पूर्ण, अणु 0x00b5, 10400 पूर्ण,
	अणु 0x00b1, 10500 पूर्ण, अणु 0x00ae, 10600 पूर्ण, अणु 0x00aa, 10700 पूर्ण,
	अणु 0x00a6, 10800 पूर्ण, अणु 0x00a3, 10900 पूर्ण, अणु 0x009f, 11000 पूर्ण,
	अणु 0x009b, 11100 पूर्ण, अणु 0x0098, 11200 पूर्ण, अणु 0x0095, 11300 पूर्ण,
	अणु 0x0091, 11400 पूर्ण, अणु 0x008e, 11500 पूर्ण, अणु 0x008b, 11600 पूर्ण,
	अणु 0x0088, 11700 पूर्ण, अणु 0x0085, 11800 पूर्ण, अणु 0x0082, 11900 पूर्ण,
	अणु 0x007f, 12000 पूर्ण, अणु 0x007c, 12100 पूर्ण, अणु 0x007a, 12200 पूर्ण,
	अणु 0x0077, 12300 पूर्ण, अणु 0x0074, 12400 पूर्ण, अणु 0x0072, 12500 पूर्ण,
	अणु 0x006f, 12600 पूर्ण, अणु 0x006d, 12700 पूर्ण, अणु 0x006b, 12800 पूर्ण,
	अणु 0x0068, 12900 पूर्ण, अणु 0x0066, 13000 पूर्ण, अणु 0x0064, 13100 पूर्ण,
	अणु 0x0061, 13200 पूर्ण, अणु 0x005f, 13300 पूर्ण, अणु 0x005d, 13400 पूर्ण,
	अणु 0x005b, 13500 पूर्ण, अणु 0x0059, 13600 पूर्ण, अणु 0x0057, 13700 पूर्ण,
	अणु 0x0055, 13800 पूर्ण, अणु 0x0053, 13900 पूर्ण, अणु 0x0051, 14000 पूर्ण,
	अणु 0x004f, 14100 पूर्ण, अणु 0x004e, 14200 पूर्ण, अणु 0x004c, 14300 पूर्ण,
	अणु 0x004a, 14400 पूर्ण, अणु 0x0049, 14500 पूर्ण, अणु 0x0047, 14600 पूर्ण,
	अणु 0x0045, 14700 पूर्ण, अणु 0x0044, 14800 पूर्ण, अणु 0x0042, 14900 पूर्ण,
	अणु 0x0041, 15000 पूर्ण, अणु 0x003f, 15100 पूर्ण, अणु 0x003e, 15200 पूर्ण,
	अणु 0x003c, 15300 पूर्ण, अणु 0x003b, 15400 पूर्ण, अणु 0x003a, 15500 पूर्ण,
	अणु 0x0038, 15600 पूर्ण, अणु 0x0037, 15700 पूर्ण, अणु 0x0036, 15800 पूर्ण,
	अणु 0x0034, 15900 पूर्ण, अणु 0x0033, 16000 पूर्ण, अणु 0x0032, 16100 पूर्ण,
	अणु 0x0031, 16200 पूर्ण, अणु 0x0030, 16300 पूर्ण, अणु 0x002f, 16400 पूर्ण,
	अणु 0x002e, 16500 पूर्ण, अणु 0x002d, 16600 पूर्ण, अणु 0x002c, 16700 पूर्ण,
	अणु 0x002b, 16800 पूर्ण, अणु 0x002a, 16900 पूर्ण, अणु 0x0029, 17000 पूर्ण,
	अणु 0x0028, 17100 पूर्ण, अणु 0x0027, 17200 पूर्ण, अणु 0x0026, 17300 पूर्ण,
	अणु 0x0025, 17400 पूर्ण, अणु 0x0024, 17500 पूर्ण, अणु 0x0023, 17600 पूर्ण,
	अणु 0x0022, 17800 पूर्ण, अणु 0x0021, 17900 पूर्ण, अणु 0x0020, 18000 पूर्ण,
	अणु 0x001f, 18200 पूर्ण, अणु 0x001e, 18300 पूर्ण, अणु 0x001d, 18500 पूर्ण,
	अणु 0x001c, 18700 पूर्ण, अणु 0x001b, 18900 पूर्ण, अणु 0x001a, 19000 पूर्ण,
	अणु 0x0019, 19200 पूर्ण, अणु 0x0018, 19300 पूर्ण, अणु 0x0017, 19500 पूर्ण,
	अणु 0x0016, 19700 पूर्ण, अणु 0x0015, 19900 पूर्ण, अणु 0x0014, 20000 पूर्ण,
पूर्ण;

अटल पूर्णांक cxd2841er_मुक्तze_regs(काष्ठा cxd2841er_priv *priv);
अटल पूर्णांक cxd2841er_unमुक्तze_regs(काष्ठा cxd2841er_priv *priv);

अटल व्योम cxd2841er_i2c_debug(काष्ठा cxd2841er_priv *priv,
				u8 addr, u8 reg, u8 ग_लिखो,
				स्थिर u8 *data, u32 len)
अणु
	dev_dbg(&priv->i2c->dev,
		"cxd2841er: I2C %s addr %02x reg 0x%02x size %d data %*ph\n",
		(ग_लिखो == 0 ? "read" : "write"), addr, reg, len, len, data);
पूर्ण

अटल पूर्णांक cxd2841er_ग_लिखो_regs(काष्ठा cxd2841er_priv *priv,
				u8 addr, u8 reg, स्थिर u8 *data, u32 len)
अणु
	पूर्णांक ret;
	u8 buf[MAX_WRITE_REGSIZE + 1];
	u8 i2c_addr = (addr == I2C_SLVX ?
		priv->i2c_addr_slvx : priv->i2c_addr_slvt);
	काष्ठा i2c_msg msg[1] = अणु
		अणु
			.addr = i2c_addr,
			.flags = 0,
			.len = len + 1,
			.buf = buf,
		पूर्ण
	पूर्ण;

	अगर (len + 1 >= माप(buf)) अणु
		dev_warn(&priv->i2c->dev, "wr reg=%04x: len=%d is too big!\n",
			 reg, len + 1);
		वापस -E2BIG;
	पूर्ण

	cxd2841er_i2c_debug(priv, i2c_addr, reg, 1, data, len);
	buf[0] = reg;
	स_नकल(&buf[1], data, len);

	ret = i2c_transfer(priv->i2c, msg, 1);
	अगर (ret >= 0 && ret != 1)
		ret = -EIO;
	अगर (ret < 0) अणु
		dev_warn(&priv->i2c->dev,
			"%s: i2c wr failed=%d addr=%02x reg=%02x len=%d\n",
			KBUILD_MODNAME, ret, i2c_addr, reg, len);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_ग_लिखो_reg(काष्ठा cxd2841er_priv *priv,
			       u8 addr, u8 reg, u8 val)
अणु
	u8 पंचांगp = val; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	वापस cxd2841er_ग_लिखो_regs(priv, addr, reg, &पंचांगp, 1);
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_regs(काष्ठा cxd2841er_priv *priv,
			       u8 addr, u8 reg, u8 *val, u32 len)
अणु
	पूर्णांक ret;
	u8 i2c_addr = (addr == I2C_SLVX ?
		priv->i2c_addr_slvx : priv->i2c_addr_slvt);
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = i2c_addr,
			.flags = 0,
			.len = 1,
			.buf = &reg,
		पूर्ण, अणु
			.addr = i2c_addr,
			.flags = I2C_M_RD,
			.len = len,
			.buf = val,
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(priv->i2c, msg, 2);
	अगर (ret >= 0 && ret != 2)
		ret = -EIO;
	अगर (ret < 0) अणु
		dev_warn(&priv->i2c->dev,
			"%s: i2c rd failed=%d addr=%02x reg=%02x\n",
			KBUILD_MODNAME, ret, i2c_addr, reg);
		वापस ret;
	पूर्ण
	cxd2841er_i2c_debug(priv, i2c_addr, reg, 0, val, len);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_reg(काष्ठा cxd2841er_priv *priv,
			      u8 addr, u8 reg, u8 *val)
अणु
	वापस cxd2841er_पढ़ो_regs(priv, addr, reg, val, 1);
पूर्ण

अटल पूर्णांक cxd2841er_set_reg_bits(काष्ठा cxd2841er_priv *priv,
				  u8 addr, u8 reg, u8 data, u8 mask)
अणु
	पूर्णांक res;
	u8 rdata;

	अगर (mask != 0xff) अणु
		res = cxd2841er_पढ़ो_reg(priv, addr, reg, &rdata);
		अगर (res)
			वापस res;
		data = ((data & mask) | (rdata & (mask ^ 0xFF)));
	पूर्ण
	वापस cxd2841er_ग_लिखो_reg(priv, addr, reg, data);
पूर्ण

अटल u32 cxd2841er_calc_अगरfreq_xtal(क्रमागत cxd2841er_xtal xtal, u32 अगरhz)
अणु
	u64 पंचांगp;

	पंचांगp = (u64) अगरhz * 16777216;
	करो_भाग(पंचांगp, ((xtal == SONY_XTAL_24000) ? 48000000 : 41000000));

	वापस (u32) पंचांगp;
पूर्ण

अटल u32 cxd2841er_calc_अगरfreq(u32 अगरhz)
अणु
	वापस cxd2841er_calc_अगरfreq_xtal(SONY_XTAL_20500, अगरhz);
पूर्ण

अटल पूर्णांक cxd2841er_get_अगर_hz(काष्ठा cxd2841er_priv *priv, u32 def_hz)
अणु
	u32 hz;

	अगर (priv->frontend.ops.tuner_ops.get_अगर_frequency
			&& (priv->flags & CXD2841ER_AUTO_IFHZ))
		priv->frontend.ops.tuner_ops.get_अगर_frequency(
			&priv->frontend, &hz);
	अन्यथा
		hz = def_hz;

	वापस hz;
पूर्ण

अटल पूर्णांक cxd2841er_tuner_set(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;

	अगर ((priv->flags & CXD2841ER_USE_GATECTRL) && fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);
	अगर ((priv->flags & CXD2841ER_USE_GATECTRL) && fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_dvbs2_set_symbol_rate(काष्ठा cxd2841er_priv *priv,
					   u32 symbol_rate)
अणु
	u32 reg_value = 0;
	u8 data[3] = अणु0, 0, 0पूर्ण;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	/*
	 * regValue = (symbolRateKSps * 2^14 / 1000) + 0.5
	 *          = ((symbolRateKSps * 2^14) + 500) / 1000
	 *          = ((symbolRateKSps * 16384) + 500) / 1000
	 */
	reg_value = DIV_ROUND_CLOSEST(symbol_rate * 16384, 1000);
	अगर ((reg_value == 0) || (reg_value > 0xFFFFF)) अणु
		dev_err(&priv->i2c->dev,
			"%s(): reg_value is out of range\n", __func__);
		वापस -EINVAL;
	पूर्ण
	data[0] = (u8)((reg_value >> 16) & 0x0F);
	data[1] = (u8)((reg_value >>  8) & 0xFF);
	data[2] = (u8)(reg_value & 0xFF);
	/* Set SLV-T Bank : 0xAE */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xae);
	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x20, data, 3);
	वापस 0;
पूर्ण

अटल व्योम cxd2841er_set_ts_घड़ी_mode(काष्ठा cxd2841er_priv *priv,
					u8 प्रणाली);

अटल पूर्णांक cxd2841er_sleep_s_to_active_s(काष्ठा cxd2841er_priv *priv,
					 u8 प्रणाली, u32 symbol_rate)
अणु
	पूर्णांक ret;
	u8 data[4] = अणु 0, 0, 0, 0 पूर्ण;

	अगर (priv->state != STATE_SLEEP_S) अणु
		dev_err(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, (पूर्णांक)priv->state);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	cxd2841er_set_ts_घड़ी_mode(priv, SYS_DVBS);
	/* Set demod mode */
	अगर (प्रणाली == SYS_DVBS) अणु
		data[0] = 0x0A;
	पूर्ण अन्यथा अगर (प्रणाली == SYS_DVBS2) अणु
		data[0] = 0x0B;
	पूर्ण अन्यथा अणु
		dev_err(&priv->i2c->dev, "%s(): invalid delsys %d\n",
			__func__, प्रणाली);
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x17, data[0]);
	/* DVB-S/S2 */
	data[0] = 0x00;
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Enable S/S2 स्वतः detection 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2d, data[0]);
	/* Set SLV-T Bank : 0xAE */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xae);
	/* Enable S/S2 स्वतः detection 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x30, data[0]);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Enable demod घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2c, 0x01);
	/* Enable ADC घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x31, 0x01);
	/* Enable ADC 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x63, 0x16);
	/* Enable ADC 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x65, 0x3f);
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* Enable ADC 3 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x18, 0x00);
	/* Set SLV-T Bank : 0xA3 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xa3);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xac, 0x00);
	data[0] = 0x07;
	data[1] = 0x3B;
	data[2] = 0x08;
	data[3] = 0xC5;
	/* Set SLV-T Bank : 0xAB */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xab);
	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x98, data, 4);
	data[0] = 0x05;
	data[1] = 0x80;
	data[2] = 0x0A;
	data[3] = 0x80;
	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xa8, data, 4);
	data[0] = 0x0C;
	data[1] = 0xCC;
	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xc3, data, 2);
	/* Set demod parameter */
	ret = cxd2841er_dvbs2_set_symbol_rate(priv, symbol_rate);
	अगर (ret != 0)
		वापस ret;
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* disable Hi-Z setting 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x80, 0x10);
	/* disable Hi-Z setting 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x81, 0x00);
	priv->state = STATE_ACTIVE_S;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_sleep_tc_to_active_t_band(काष्ठा cxd2841er_priv *priv,
					       u32 bandwidth);

अटल पूर्णांक cxd2841er_sleep_tc_to_active_t2_band(काष्ठा cxd2841er_priv *priv,
						u32 bandwidth);

अटल पूर्णांक cxd2841er_sleep_tc_to_active_c_band(काष्ठा cxd2841er_priv *priv,
					       u32 bandwidth);

अटल पूर्णांक cxd2841er_sleep_tc_to_active_i(काष्ठा cxd2841er_priv *priv,
		u32 bandwidth);

अटल पूर्णांक cxd2841er_active_i_to_sleep_tc(काष्ठा cxd2841er_priv *priv);

अटल पूर्णांक cxd2841er_sleep_tc_to_shutकरोwn(काष्ठा cxd2841er_priv *priv);

अटल पूर्णांक cxd2841er_shutकरोwn_to_sleep_tc(काष्ठा cxd2841er_priv *priv);

अटल पूर्णांक cxd2841er_sleep_tc(काष्ठा dvb_frontend *fe);

अटल पूर्णांक cxd2841er_retune_active(काष्ठा cxd2841er_priv *priv,
				   काष्ठा dtv_frontend_properties *p)
अणु
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_S &&
			priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* disable TS output */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xc3, 0x01);
	अगर (priv->state == STATE_ACTIVE_S)
		वापस cxd2841er_dvbs2_set_symbol_rate(
				priv, p->symbol_rate / 1000);
	अन्यथा अगर (priv->state == STATE_ACTIVE_TC) अणु
		चयन (priv->प्रणाली) अणु
		हाल SYS_DVBT:
			वापस cxd2841er_sleep_tc_to_active_t_band(
					priv, p->bandwidth_hz);
		हाल SYS_DVBT2:
			वापस cxd2841er_sleep_tc_to_active_t2_band(
					priv, p->bandwidth_hz);
		हाल SYS_DVBC_ANNEX_A:
			वापस cxd2841er_sleep_tc_to_active_c_band(
					priv, p->bandwidth_hz);
		हाल SYS_ISDBT:
			cxd2841er_active_i_to_sleep_tc(priv);
			cxd2841er_sleep_tc_to_shutकरोwn(priv);
			cxd2841er_shutकरोwn_to_sleep_tc(priv);
			वापस cxd2841er_sleep_tc_to_active_i(
					priv, p->bandwidth_hz);
		पूर्ण
	पूर्ण
	dev_dbg(&priv->i2c->dev, "%s(): invalid delivery system %d\n",
		__func__, priv->प्रणाली);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cxd2841er_active_s_to_sleep_s(काष्ठा cxd2841er_priv *priv)
अणु
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_S) अणु
		dev_err(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* disable TS output */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xc3, 0x01);
	/* enable Hi-Z setting 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x80, 0x1f);
	/* enable Hi-Z setting 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x81, 0xff);
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* disable ADC 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x18, 0x01);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* disable ADC घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x31, 0x00);
	/* disable ADC 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x63, 0x16);
	/* disable ADC 3 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x65, 0x27);
	/* SADC Bias ON */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x69, 0x06);
	/* disable demod घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2c, 0x00);
	/* Set SLV-T Bank : 0xAE */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xae);
	/* disable S/S2 स्वतः detection1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x30, 0x00);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* disable S/S2 स्वतः detection2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2d, 0x00);
	priv->state = STATE_SLEEP_S;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_sleep_s_to_shutकरोwn(काष्ठा cxd2841er_priv *priv)
अणु
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_SLEEP_S) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid demod state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Disable DSQOUT */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x80, 0x3f);
	/* Disable DSQIN */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x9c, 0x00);
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* Disable oscillator */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x15, 0x01);
	/* Set demod mode */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x17, 0x01);
	priv->state = STATE_SHUTDOWN;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_sleep_tc_to_shutकरोwn(काष्ठा cxd2841er_priv *priv)
अणु
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_SLEEP_TC) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid demod state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* Disable oscillator */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x15, 0x01);
	/* Set demod mode */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x17, 0x01);
	priv->state = STATE_SHUTDOWN;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_active_t_to_sleep_tc(काष्ठा cxd2841er_priv *priv)
अणु
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_err(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* disable TS output */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xc3, 0x01);
	/* enable Hi-Z setting 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x80, 0x3f);
	/* enable Hi-Z setting 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x81, 0xff);
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* disable ADC 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x18, 0x01);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Disable ADC 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x43, 0x0a);
	/* Disable ADC 3 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x41, 0x0a);
	/* Disable ADC घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x30, 0x00);
	/* Disable RF level monitor */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2f, 0x00);
	/* Disable demod घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2c, 0x00);
	priv->state = STATE_SLEEP_TC;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_active_t2_to_sleep_tc(काष्ठा cxd2841er_priv *priv)
अणु
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_err(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* disable TS output */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xc3, 0x01);
	/* enable Hi-Z setting 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x80, 0x3f);
	/* enable Hi-Z setting 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x81, 0xff);
	/* Cancel DVB-T2 setting */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x13);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x83, 0x40);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x86, 0x21);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x9e, 0x09, 0x0f);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x9f, 0xfb);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x2a);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x38, 0x00, 0x0f);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x2b);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x11, 0x00, 0x3f);
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* disable ADC 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x18, 0x01);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Disable ADC 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x43, 0x0a);
	/* Disable ADC 3 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x41, 0x0a);
	/* Disable ADC घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x30, 0x00);
	/* Disable RF level monitor */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2f, 0x00);
	/* Disable demod घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2c, 0x00);
	priv->state = STATE_SLEEP_TC;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_active_c_to_sleep_tc(काष्ठा cxd2841er_priv *priv)
अणु
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_err(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* disable TS output */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xc3, 0x01);
	/* enable Hi-Z setting 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x80, 0x3f);
	/* enable Hi-Z setting 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x81, 0xff);
	/* Cancel DVB-C setting */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x11);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xa3, 0x00, 0x1f);
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* disable ADC 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x18, 0x01);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Disable ADC 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x43, 0x0a);
	/* Disable ADC 3 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x41, 0x0a);
	/* Disable ADC घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x30, 0x00);
	/* Disable RF level monitor */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2f, 0x00);
	/* Disable demod घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2c, 0x00);
	priv->state = STATE_SLEEP_TC;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_active_i_to_sleep_tc(काष्ठा cxd2841er_priv *priv)
अणु
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_err(&priv->i2c->dev, "%s(): invalid state %d\n",
				__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* disable TS output */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xc3, 0x01);
	/* enable Hi-Z setting 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x80, 0x3f);
	/* enable Hi-Z setting 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x81, 0xff);

	/* TODO: Cancel demod parameter */

	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* disable ADC 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x18, 0x01);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Disable ADC 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x43, 0x0a);
	/* Disable ADC 3 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x41, 0x0a);
	/* Disable ADC घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x30, 0x00);
	/* Disable RF level monitor */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2f, 0x00);
	/* Disable demod घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2c, 0x00);
	priv->state = STATE_SLEEP_TC;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_shutकरोwn_to_sleep_s(काष्ठा cxd2841er_priv *priv)
अणु
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_SHUTDOWN) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid demod state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* Clear all demodulator रेजिस्टरs */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x02, 0x00);
	usleep_range(3000, 5000);
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* Set demod SW reset */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x10, 0x01);

	चयन (priv->xtal) अणु
	हाल SONY_XTAL_20500:
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x14, 0x00);
		अवरोध;
	हाल SONY_XTAL_24000:
		/* Select demod frequency */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x12, 0x00);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x14, 0x03);
		अवरोध;
	हाल SONY_XTAL_41000:
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x14, 0x01);
		अवरोध;
	शेष:
		dev_dbg(&priv->i2c->dev, "%s(): invalid demod xtal %d\n",
				__func__, priv->xtal);
		वापस -EINVAL;
	पूर्ण

	/* Set demod mode */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x17, 0x0a);
	/* Clear demod SW reset */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x10, 0x00);
	usleep_range(1000, 2000);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* enable DSQOUT */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x80, 0x1F);
	/* enable DSQIN */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x9C, 0x40);
	/* TADC Bias On */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x43, 0x0a);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x41, 0x0a);
	/* SADC Bias On */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x63, 0x16);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x65, 0x27);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x69, 0x06);
	priv->state = STATE_SLEEP_S;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_shutकरोwn_to_sleep_tc(काष्ठा cxd2841er_priv *priv)
अणु
	u8 data = 0;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_SHUTDOWN) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid demod state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* Clear all demodulator रेजिस्टरs */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x02, 0x00);
	usleep_range(3000, 5000);
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* Set demod SW reset */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x10, 0x01);
  /* Select ADC घड़ी mode */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x13, 0x00);

	चयन (priv->xtal) अणु
	हाल SONY_XTAL_20500:
		data = 0x0;
		अवरोध;
	हाल SONY_XTAL_24000:
		/* Select demod frequency */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x12, 0x00);
		data = 0x3;
		अवरोध;
	हाल SONY_XTAL_41000:
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x12, 0x00);
		data = 0x1;
		अवरोध;
	पूर्ण
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x14, data);
	/* Clear demod SW reset */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x10, 0x00);
	usleep_range(1000, 2000);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* TADC Bias On */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x43, 0x0a);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x41, 0x0a);
	/* SADC Bias On */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x63, 0x16);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x65, 0x27);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x69, 0x06);
	priv->state = STATE_SLEEP_TC;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_tune_करोne(काष्ठा cxd2841er_priv *priv)
अणु
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0, 0);
	/* SW Reset */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xfe, 0x01);
	/* Enable TS output */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xc3, 0x00);
	वापस 0;
पूर्ण

/* Set TS parallel mode */
अटल व्योम cxd2841er_set_ts_घड़ी_mode(काष्ठा cxd2841er_priv *priv,
					u8 प्रणाली)
अणु
	u8 serial_ts, ts_rate_ctrl_off, ts_in_off;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0xc4, &serial_ts);
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0xd3, &ts_rate_ctrl_off);
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0xde, &ts_in_off);
	dev_dbg(&priv->i2c->dev, "%s(): ser_ts=0x%02x rate_ctrl_off=0x%02x in_off=0x%02x\n",
		__func__, serial_ts, ts_rate_ctrl_off, ts_in_off);

	/*
	 * slave    Bank    Addr    Bit    शेष    Name
	 * <SLV-T>  00h     C4h     [1:0]  2'b??      OSERCKMODE
	 */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xc4,
		((priv->flags & CXD2841ER_TS_SERIAL) ? 0x01 : 0x00), 0x03);
	/*
	 * slave    Bank    Addr    Bit    शेष    Name
	 * <SLV-T>  00h     D1h     [1:0]  2'b??      OSERDUTYMODE
	 */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xd1,
		((priv->flags & CXD2841ER_TS_SERIAL) ? 0x01 : 0x00), 0x03);
	/*
	 * slave    Bank    Addr    Bit    शेष    Name
	 * <SLV-T>  00h     D9h     [7:0]  8'h08      OTSCKPERIOD
	 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xd9, 0x08);
	/*
	 * Disable TS IF Clock
	 * slave    Bank    Addr    Bit    शेष    Name
	 * <SLV-T>  00h     32h     [0]    1'b1       OREG_CK_TSIF_EN
	 */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x32, 0x00, 0x01);
	/*
	 * slave    Bank    Addr    Bit    शेष    Name
	 * <SLV-T>  00h     33h     [1:0]  2'b01      OREG_CKSEL_TSIF
	 */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x33,
		((priv->flags & CXD2841ER_TS_SERIAL) ? 0x01 : 0x00), 0x03);
	/*
	 * Enable TS IF Clock
	 * slave    Bank    Addr    Bit    शेष    Name
	 * <SLV-T>  00h     32h     [0]    1'b1       OREG_CK_TSIF_EN
	 */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x32, 0x01, 0x01);

	अगर (प्रणाली == SYS_DVBT) अणु
		/* Enable parity period क्रम DVB-T */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
		cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x66, 0x01, 0x01);
	पूर्ण अन्यथा अगर (प्रणाली == SYS_DVBC_ANNEX_A) अणु
		/* Enable parity period क्रम DVB-C */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x40);
		cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x66, 0x01, 0x01);
	पूर्ण
पूर्ण

अटल u8 cxd2841er_chip_id(काष्ठा cxd2841er_priv *priv)
अणु
	u8 chip_id = 0;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0, 0) == 0)
		cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0xfd, &chip_id);
	अन्यथा अगर (cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0, 0) == 0)
		cxd2841er_पढ़ो_reg(priv, I2C_SLVX, 0xfd, &chip_id);

	वापस chip_id;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_status_s(काष्ठा dvb_frontend *fe,
				   क्रमागत fe_status *status)
अणु
	u8 reg = 0;
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	*status = 0;
	अगर (priv->state != STATE_ACTIVE_S) अणु
		dev_err(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-T Bank : 0xA0 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xa0);
	/*
	 *  slave     Bank      Addr      Bit      Signal name
	 * <SLV-T>    A0h       11h       [2]      ITSLOCK
	 */
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x11, &reg);
	अगर (reg & 0x04) अणु
		*status = FE_HAS_SIGNAL
			| FE_HAS_CARRIER
			| FE_HAS_VITERBI
			| FE_HAS_SYNC
			| FE_HAS_LOCK;
	पूर्ण
	dev_dbg(&priv->i2c->dev, "%s(): result 0x%x\n", __func__, *status);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_status_t_t2(काष्ठा cxd2841er_priv *priv,
				      u8 *sync, u8 *tslock, u8 *unlock)
अणु
	u8 data = 0;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC)
		वापस -EINVAL;
	अगर (priv->प्रणाली == SYS_DVBT) अणु
		/* Set SLV-T Bank : 0x10 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	पूर्ण अन्यथा अणु
		/* Set SLV-T Bank : 0x20 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x20);
	पूर्ण
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x10, &data);
	अगर ((data & 0x07) == 0x07) अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): invalid hardware state detected\n", __func__);
		*sync = 0;
		*tslock = 0;
		*unlock = 0;
	पूर्ण अन्यथा अणु
		*sync = ((data & 0x07) == 0x6 ? 1 : 0);
		*tslock = ((data & 0x20) ? 1 : 0);
		*unlock = ((data & 0x10) ? 1 : 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_status_c(काष्ठा cxd2841er_priv *priv, u8 *tslock)
अणु
	u8 data;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC)
		वापस -EINVAL;
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x40);
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x88, &data);
	अगर ((data & 0x01) == 0) अणु
		*tslock = 0;
	पूर्ण अन्यथा अणु
		cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x10, &data);
		*tslock = ((data & 0x20) ? 1 : 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_status_i(काष्ठा cxd2841er_priv *priv,
		u8 *sync, u8 *tslock, u8 *unlock)
अणु
	u8 data = 0;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC)
		वापस -EINVAL;
	/* Set SLV-T Bank : 0x60 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x60);
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x10, &data);
	dev_dbg(&priv->i2c->dev,
			"%s(): lock=0x%x\n", __func__, data);
	*sync = ((data & 0x02) ? 1 : 0);
	*tslock = ((data & 0x01) ? 1 : 0);
	*unlock = ((data & 0x10) ? 1 : 0);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_status_tc(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_status *status)
अणु
	पूर्णांक ret = 0;
	u8 sync = 0;
	u8 tslock = 0;
	u8 unlock = 0;
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;

	*status = 0;
	अगर (priv->state == STATE_ACTIVE_TC) अणु
		अगर (priv->प्रणाली == SYS_DVBT || priv->प्रणाली == SYS_DVBT2) अणु
			ret = cxd2841er_पढ़ो_status_t_t2(
				priv, &sync, &tslock, &unlock);
			अगर (ret)
				जाओ करोne;
			अगर (unlock)
				जाओ करोne;
			अगर (sync)
				*status = FE_HAS_SIGNAL |
					FE_HAS_CARRIER |
					FE_HAS_VITERBI |
					FE_HAS_SYNC;
			अगर (tslock)
				*status |= FE_HAS_LOCK;
		पूर्ण अन्यथा अगर (priv->प्रणाली == SYS_ISDBT) अणु
			ret = cxd2841er_पढ़ो_status_i(
					priv, &sync, &tslock, &unlock);
			अगर (ret)
				जाओ करोne;
			अगर (unlock)
				जाओ करोne;
			अगर (sync)
				*status = FE_HAS_SIGNAL |
					FE_HAS_CARRIER |
					FE_HAS_VITERBI |
					FE_HAS_SYNC;
			अगर (tslock)
				*status |= FE_HAS_LOCK;
		पूर्ण अन्यथा अगर (priv->प्रणाली == SYS_DVBC_ANNEX_A) अणु
			ret = cxd2841er_पढ़ो_status_c(priv, &tslock);
			अगर (ret)
				जाओ करोne;
			अगर (tslock)
				*status = FE_HAS_SIGNAL |
					FE_HAS_CARRIER |
					FE_HAS_VITERBI |
					FE_HAS_SYNC |
					FE_HAS_LOCK;
		पूर्ण
	पूर्ण
करोne:
	dev_dbg(&priv->i2c->dev, "%s(): status 0x%x\n", __func__, *status);
	वापस ret;
पूर्ण

अटल पूर्णांक cxd2841er_get_carrier_offset_s_s2(काष्ठा cxd2841er_priv *priv,
					     पूर्णांक *offset)
अणु
	u8 data[3];
	u8 is_hs_mode;
	s32 cfrl_ctrlval;
	s32 temp_भाग, temp_q, temp_r;

	अगर (priv->state != STATE_ACTIVE_S) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	/*
	 * Get High Sampling Rate mode
	 *  slave     Bank      Addr      Bit      Signal name
	 * <SLV-T>    A0h       10h       [0]      ITRL_LOCK
	 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xa0);
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x10, &data[0]);
	अगर (data[0] & 0x01) अणु
		/*
		 *  slave     Bank      Addr      Bit      Signal name
		 * <SLV-T>    A0h       50h       [4]      IHSMODE
		 */
		cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x50, &data[0]);
		is_hs_mode = (data[0] & 0x10 ? 1 : 0);
	पूर्ण अन्यथा अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): unable to detect sampling rate mode\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	/*
	 *  slave     Bank      Addr      Bit      Signal name
	 * <SLV-T>    A0h       45h       [4:0]    ICFRL_CTRLVAL[20:16]
	 * <SLV-T>    A0h       46h       [7:0]    ICFRL_CTRLVAL[15:8]
	 * <SLV-T>    A0h       47h       [7:0]    ICFRL_CTRLVAL[7:0]
	 */
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x45, data, 3);
	cfrl_ctrlval = sign_extend32((((u32)data[0] & 0x1F) << 16) |
				(((u32)data[1] & 0xFF) <<  8) |
				((u32)data[2] & 0xFF), 20);
	temp_भाग = (is_hs_mode ? 1048576 : 1572864);
	अगर (cfrl_ctrlval > 0) अणु
		temp_q = भाग_s64_rem(97375LL * cfrl_ctrlval,
			temp_भाग, &temp_r);
	पूर्ण अन्यथा अणु
		temp_q = भाग_s64_rem(-97375LL * cfrl_ctrlval,
			temp_भाग, &temp_r);
	पूर्ण
	अगर (temp_r >= temp_भाग / 2)
		temp_q++;
	अगर (cfrl_ctrlval > 0)
		temp_q *= -1;
	*offset = temp_q;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_get_carrier_offset_i(काष्ठा cxd2841er_priv *priv,
					   u32 bandwidth, पूर्णांक *offset)
अणु
	u8 data[4];

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	अगर (priv->प्रणाली != SYS_ISDBT) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid delivery system %d\n",
			__func__, priv->प्रणाली);
		वापस -EINVAL;
	पूर्ण
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x60);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x4c, data, माप(data));
	*offset = -1 * sign_extend32(
		((u32)(data[0] & 0x1F) << 24) | ((u32)data[1] << 16) |
		((u32)data[2] << 8) | (u32)data[3], 29);

	चयन (bandwidth) अणु
	हाल 6000000:
		*offset = -1 * ((*offset) * 8/264);
		अवरोध;
	हाल 7000000:
		*offset = -1 * ((*offset) * 8/231);
		अवरोध;
	हाल 8000000:
		*offset = -1 * ((*offset) * 8/198);
		अवरोध;
	शेष:
		dev_dbg(&priv->i2c->dev, "%s(): invalid bandwidth %d\n",
				__func__, bandwidth);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&priv->i2c->dev, "%s(): bandwidth %d offset %d\n",
			__func__, bandwidth, *offset);

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_get_carrier_offset_t(काष्ठा cxd2841er_priv *priv,
					   u32 bandwidth, पूर्णांक *offset)
अणु
	u8 data[4];

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	अगर (priv->प्रणाली != SYS_DVBT) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid delivery system %d\n",
			__func__, priv->प्रणाली);
		वापस -EINVAL;
	पूर्ण
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x4c, data, माप(data));
	*offset = -1 * sign_extend32(
		((u32)(data[0] & 0x1F) << 24) | ((u32)data[1] << 16) |
		((u32)data[2] << 8) | (u32)data[3], 29);
	*offset *= (bandwidth / 1000000);
	*offset /= 235;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_get_carrier_offset_t2(काष्ठा cxd2841er_priv *priv,
					   u32 bandwidth, पूर्णांक *offset)
अणु
	u8 data[4];

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	अगर (priv->प्रणाली != SYS_DVBT2) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid delivery system %d\n",
			__func__, priv->प्रणाली);
		वापस -EINVAL;
	पूर्ण
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x20);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x4c, data, माप(data));
	*offset = -1 * sign_extend32(
		((u32)(data[0] & 0x0F) << 24) | ((u32)data[1] << 16) |
		((u32)data[2] << 8) | (u32)data[3], 27);
	चयन (bandwidth) अणु
	हाल 1712000:
		*offset /= 582;
		अवरोध;
	हाल 5000000:
	हाल 6000000:
	हाल 7000000:
	हाल 8000000:
		*offset *= (bandwidth / 1000000);
		*offset /= 940;
		अवरोध;
	शेष:
		dev_dbg(&priv->i2c->dev, "%s(): invalid bandwidth %d\n",
			__func__, bandwidth);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_get_carrier_offset_c(काष्ठा cxd2841er_priv *priv,
					  पूर्णांक *offset)
अणु
	u8 data[2];

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	अगर (priv->प्रणाली != SYS_DVBC_ANNEX_A) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid delivery system %d\n",
			__func__, priv->प्रणाली);
		वापस -EINVAL;
	पूर्ण
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x40);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x15, data, माप(data));
	*offset = भाग_s64(41000LL * sign_extend32((((u32)data[0] & 0x3f) << 8)
						| (u32)data[1], 13), 16384);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_packet_errors_c(
		काष्ठा cxd2841er_priv *priv, u32 *pक्रमागत)
अणु
	u8 data[3];

	*pक्रमागत = 0;
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
				__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x40);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0xea, data, माप(data));
	अगर (data[2] & 0x01)
		*pक्रमागत = ((u32)data[0] << 8) | (u32)data[1];
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_packet_errors_t(
		काष्ठा cxd2841er_priv *priv, u32 *pक्रमागत)
अणु
	u8 data[3];

	*pक्रमागत = 0;
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0xea, data, माप(data));
	अगर (data[2] & 0x01)
		*pक्रमागत = ((u32)data[0] << 8) | (u32)data[1];
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_packet_errors_t2(
		काष्ठा cxd2841er_priv *priv, u32 *pक्रमागत)
अणु
	u8 data[3];

	*pक्रमागत = 0;
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x24);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0xfd, data, माप(data));
	अगर (data[0] & 0x01)
		*pक्रमागत = ((u32)data[1] << 8) | (u32)data[2];
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_packet_errors_i(
		काष्ठा cxd2841er_priv *priv, u32 *pक्रमागत)
अणु
	u8 data[2];

	*pक्रमागत = 0;
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
				__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x60);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0xA1, data, 1);

	अगर (!(data[0] & 0x01))
		वापस 0;

	/* Layer A */
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0xA2, data, माप(data));
	*pक्रमागत = ((u32)data[0] << 8) | (u32)data[1];

	/* Layer B */
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0xA4, data, माप(data));
	*pक्रमागत += ((u32)data[0] << 8) | (u32)data[1];

	/* Layer C */
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0xA6, data, माप(data));
	*pक्रमागत += ((u32)data[0] << 8) | (u32)data[1];

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_ber_c(काष्ठा cxd2841er_priv *priv,
		u32 *bit_error, u32 *bit_count)
अणु
	u8 data[3];
	u32 bit_err, period_exp;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
				__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x40);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x62, data, माप(data));
	अगर (!(data[0] & 0x80)) अणु
		dev_dbg(&priv->i2c->dev,
				"%s(): no valid BER data\n", __func__);
		वापस -EINVAL;
	पूर्ण
	bit_err = ((u32)(data[0] & 0x3f) << 16) |
		((u32)data[1] << 8) |
		(u32)data[2];
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x60, data);
	period_exp = data[0] & 0x1f;

	अगर ((period_exp <= 11) && (bit_err > (1 << period_exp) * 204 * 8)) अणु
		dev_dbg(&priv->i2c->dev,
				"%s(): period_exp(%u) or bit_err(%u)  not in range. no valid BER data\n",
				__func__, period_exp, bit_err);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&priv->i2c->dev,
			"%s(): period_exp(%u) or bit_err(%u) count=%d\n",
			__func__, period_exp, bit_err,
			((1 << period_exp) * 204 * 8));

	*bit_error = bit_err;
	*bit_count = ((1 << period_exp) * 204 * 8);

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_ber_i(काष्ठा cxd2841er_priv *priv,
		u32 *bit_error, u32 *bit_count)
अणु
	u8 data[3];
	u8 pktnum[2];

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
				__func__, priv->state);
		वापस -EINVAL;
	पूर्ण

	cxd2841er_मुक्तze_regs(priv);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x60);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x5B, pktnum, माप(pktnum));
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x16, data, माप(data));
	cxd2841er_unमुक्तze_regs(priv);

	अगर (!pktnum[0] && !pktnum[1]) अणु
		dev_dbg(&priv->i2c->dev,
				"%s(): no valid BER data\n", __func__);
		वापस -EINVAL;
	पूर्ण

	*bit_error = ((u32)(data[0] & 0x7F) << 16) |
		((u32)data[1] << 8) | data[2];
	*bit_count = ((((u32)pktnum[0] << 8) | pktnum[1]) * 204 * 8);
	dev_dbg(&priv->i2c->dev, "%s(): bit_error=%u bit_count=%u\n",
			__func__, *bit_error, *bit_count);

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_mon_पढ़ो_ber_s(काष्ठा cxd2841er_priv *priv,
				    u32 *bit_error, u32 *bit_count)
अणु
	u8 data[11];

	/* Set SLV-T Bank : 0xA0 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xa0);
	/*
	 *  slave     Bank      Addr      Bit      Signal name
	 * <SLV-T>    A0h       35h       [0]      IFVBER_VALID
	 * <SLV-T>    A0h       36h       [5:0]    IFVBER_BITERR[21:16]
	 * <SLV-T>    A0h       37h       [7:0]    IFVBER_BITERR[15:8]
	 * <SLV-T>    A0h       38h       [7:0]    IFVBER_BITERR[7:0]
	 * <SLV-T>    A0h       3Dh       [5:0]    IFVBER_BITNUM[21:16]
	 * <SLV-T>    A0h       3Eh       [7:0]    IFVBER_BITNUM[15:8]
	 * <SLV-T>    A0h       3Fh       [7:0]    IFVBER_BITNUM[7:0]
	 */
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x35, data, 11);
	अगर (data[0] & 0x01) अणु
		*bit_error = ((u32)(data[1]  & 0x3F) << 16) |
			     ((u32)(data[2]  & 0xFF) <<  8) |
			     (u32)(data[3]  & 0xFF);
		*bit_count = ((u32)(data[8]  & 0x3F) << 16) |
			     ((u32)(data[9]  & 0xFF) <<  8) |
			     (u32)(data[10] & 0xFF);
		अगर ((*bit_count == 0) || (*bit_error > *bit_count)) अणु
			dev_dbg(&priv->i2c->dev,
				"%s(): invalid bit_error %d, bit_count %d\n",
				__func__, *bit_error, *bit_count);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण
	dev_dbg(&priv->i2c->dev, "%s(): no data available\n", __func__);
	वापस -EINVAL;
पूर्ण


अटल पूर्णांक cxd2841er_mon_पढ़ो_ber_s2(काष्ठा cxd2841er_priv *priv,
				     u32 *bit_error, u32 *bit_count)
अणु
	u8 data[5];
	u32 period;

	/* Set SLV-T Bank : 0xB2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xb2);
	/*
	 *  slave     Bank      Addr      Bit      Signal name
	 * <SLV-T>    B2h       30h       [0]      IFLBER_VALID
	 * <SLV-T>    B2h       31h       [3:0]    IFLBER_BITERR[27:24]
	 * <SLV-T>    B2h       32h       [7:0]    IFLBER_BITERR[23:16]
	 * <SLV-T>    B2h       33h       [7:0]    IFLBER_BITERR[15:8]
	 * <SLV-T>    B2h       34h       [7:0]    IFLBER_BITERR[7:0]
	 */
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x30, data, 5);
	अगर (data[0] & 0x01) अणु
		/* Bit error count */
		*bit_error = ((u32)(data[1] & 0x0F) << 24) |
			     ((u32)(data[2] & 0xFF) << 16) |
			     ((u32)(data[3] & 0xFF) <<  8) |
			     (u32)(data[4] & 0xFF);

		/* Set SLV-T Bank : 0xA0 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xa0);
		cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x7a, data);
		/* Measurement period */
		period = (u32)(1 << (data[0] & 0x0F));
		अगर (period == 0) अणु
			dev_dbg(&priv->i2c->dev,
				"%s(): period is 0\n", __func__);
			वापस -EINVAL;
		पूर्ण
		अगर (*bit_error > (period * 64800)) अणु
			dev_dbg(&priv->i2c->dev,
				"%s(): invalid bit_err 0x%x period 0x%x\n",
				__func__, *bit_error, period);
			वापस -EINVAL;
		पूर्ण
		*bit_count = period * 64800;

		वापस 0;
	पूर्ण अन्यथा अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): no data available\n", __func__);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_ber_t2(काष्ठा cxd2841er_priv *priv,
				 u32 *bit_error, u32 *bit_count)
अणु
	u8 data[4];
	u32 period_exp, n_ldpc;

	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): invalid state %d\n", __func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x20);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x39, data, माप(data));
	अगर (!(data[0] & 0x10)) अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): no valid BER data\n", __func__);
		वापस -EINVAL;
	पूर्ण
	*bit_error = ((u32)(data[0] & 0x0f) << 24) |
		     ((u32)data[1] << 16) |
		     ((u32)data[2] << 8) |
		     (u32)data[3];
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x6f, data);
	period_exp = data[0] & 0x0f;
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x22);
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x5e, data);
	n_ldpc = ((data[0] & 0x03) == 0 ? 16200 : 64800);
	अगर (*bit_error > ((1U << period_exp) * n_ldpc)) अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): invalid BER value\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/*
	 * FIXME: the right thing would be to वापस bit_error untouched,
	 * but, as we करोn't know the scale returned by the counters, let's
	 * at least preserver BER = bit_error/bit_count.
	 */
	अगर (period_exp >= 4) अणु
		*bit_count = (1U << (period_exp - 4)) * (n_ldpc / 200);
		*bit_error *= 3125ULL;
	पूर्ण अन्यथा अणु
		*bit_count = (1U << period_exp) * (n_ldpc / 200);
		*bit_error *= 50000ULL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_ber_t(काष्ठा cxd2841er_priv *priv,
				u32 *bit_error, u32 *bit_count)
अणु
	u8 data[2];
	u32 period;

	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): invalid state %d\n", __func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x39, data);
	अगर (!(data[0] & 0x01)) अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): no valid BER data\n", __func__);
		वापस 0;
	पूर्ण
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x22, data, माप(data));
	*bit_error = ((u32)data[0] << 8) | (u32)data[1];
	cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x6f, data);
	period = ((data[0] & 0x07) == 0) ? 256 : (4096 << (data[0] & 0x07));

	/*
	 * FIXME: the right thing would be to वापस bit_error untouched,
	 * but, as we करोn't know the scale returned by the counters, let's
	 * at least preserver BER = bit_error/bit_count.
	 */
	*bit_count = period / 128;
	*bit_error *= 78125ULL;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_मुक्तze_regs(काष्ठा cxd2841er_priv *priv)
अणु
	/*
	 * Freeze रेजिस्टरs: ensure multiple separate रेजिस्टर पढ़ोs
	 * are from the same snapshot
	 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x01, 0x01);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_unमुक्तze_regs(काष्ठा cxd2841er_priv *priv)
अणु
	/*
	 * un-मुक्तze रेजिस्टरs
	 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x01, 0x00);
	वापस 0;
पूर्ण

अटल u32 cxd2841er_dvbs_पढ़ो_snr(काष्ठा cxd2841er_priv *priv,
		u8 delsys, u32 *snr)
अणु
	u8 data[3];
	u32 res = 0, value;
	पूर्णांक min_index, max_index, index;
	अटल स्थिर काष्ठा cxd2841er_cnr_data *cn_data;

	cxd2841er_मुक्तze_regs(priv);
	/* Set SLV-T Bank : 0xA1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xa1);
	/*
	 *  slave     Bank      Addr      Bit     Signal name
	 * <SLV-T>    A1h       10h       [0]     ICPM_QUICKRDY
	 * <SLV-T>    A1h       11h       [4:0]   ICPM_QUICKCNDT[12:8]
	 * <SLV-T>    A1h       12h       [7:0]   ICPM_QUICKCNDT[7:0]
	 */
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x10, data, 3);
	cxd2841er_unमुक्तze_regs(priv);

	अगर (data[0] & 0x01) अणु
		value = ((u32)(data[1] & 0x1F) << 8) | (u32)(data[2] & 0xFF);
		min_index = 0;
		अगर (delsys == SYS_DVBS) अणु
			cn_data = s_cn_data;
			max_index = ARRAY_SIZE(s_cn_data) - 1;
		पूर्ण अन्यथा अणु
			cn_data = s2_cn_data;
			max_index = ARRAY_SIZE(s2_cn_data) - 1;
		पूर्ण
		अगर (value >= cn_data[min_index].value) अणु
			res = cn_data[min_index].cnr_x1000;
			जाओ करोne;
		पूर्ण
		अगर (value <= cn_data[max_index].value) अणु
			res = cn_data[max_index].cnr_x1000;
			जाओ करोne;
		पूर्ण
		जबतक ((max_index - min_index) > 1) अणु
			index = (max_index + min_index) / 2;
			अगर (value == cn_data[index].value) अणु
				res = cn_data[index].cnr_x1000;
				जाओ करोne;
			पूर्ण अन्यथा अगर (value > cn_data[index].value)
				max_index = index;
			अन्यथा
				min_index = index;
			अगर ((max_index - min_index) <= 1) अणु
				अगर (value == cn_data[max_index].value) अणु
					res = cn_data[max_index].cnr_x1000;
					जाओ करोne;
				पूर्ण अन्यथा अणु
					res = cn_data[min_index].cnr_x1000;
					जाओ करोne;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): no data available\n", __func__);
		वापस -EINVAL;
	पूर्ण
करोne:
	*snr = res;
	वापस 0;
पूर्ण

अटल uपूर्णांक32_t sony_log(uपूर्णांक32_t x)
अणु
	वापस (((10000>>8)*(पूर्णांकlog2(x)>>16) + LOG2_E_100X/2)/LOG2_E_100X);
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_snr_c(काष्ठा cxd2841er_priv *priv, u32 *snr)
अणु
	u32 reg;
	u8 data[2];
	क्रमागत sony_dvbc_स्थिरellation_t qam = SONY_DVBC_CONSTELLATION_16QAM;

	*snr = 0;
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev,
				"%s(): invalid state %d\n",
				__func__, priv->state);
		वापस -EINVAL;
	पूर्ण

	cxd2841er_मुक्तze_regs(priv);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x40);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x19, data, 1);
	qam = (क्रमागत sony_dvbc_स्थिरellation_t) (data[0] & 0x07);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x4C, data, 2);
	cxd2841er_unमुक्तze_regs(priv);

	reg = ((u32)(data[0]&0x1f) << 8) | (u32)data[1];
	अगर (reg == 0) अणु
		dev_dbg(&priv->i2c->dev,
				"%s(): reg value out of range\n", __func__);
		वापस 0;
	पूर्ण

	चयन (qam) अणु
	हाल SONY_DVBC_CONSTELLATION_16QAM:
	हाल SONY_DVBC_CONSTELLATION_64QAM:
	हाल SONY_DVBC_CONSTELLATION_256QAM:
		/* SNR(dB) = -9.50 * ln(IREG_SNR_ESTIMATE / (24320)) */
		अगर (reg < 126)
			reg = 126;
		*snr = -95 * (पूर्णांक32_t)sony_log(reg) + 95941;
		अवरोध;
	हाल SONY_DVBC_CONSTELLATION_32QAM:
	हाल SONY_DVBC_CONSTELLATION_128QAM:
		/* SNR(dB) = -8.75 * ln(IREG_SNR_ESTIMATE / (20800)) */
		अगर (reg < 69)
			reg = 69;
		*snr = -88 * (पूर्णांक32_t)sony_log(reg) + 86999;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_snr_t(काष्ठा cxd2841er_priv *priv, u32 *snr)
अणु
	u32 reg;
	u8 data[2];

	*snr = 0;
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): invalid state %d\n", __func__, priv->state);
		वापस -EINVAL;
	पूर्ण

	cxd2841er_मुक्तze_regs(priv);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x28, data, माप(data));
	cxd2841er_unमुक्तze_regs(priv);

	reg = ((u32)data[0] << 8) | (u32)data[1];
	अगर (reg == 0) अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): reg value out of range\n", __func__);
		वापस 0;
	पूर्ण
	अगर (reg > 4996)
		reg = 4996;
	*snr = 100 * ((INTLOG10X100(reg) - INTLOG10X100(5350 - reg)) + 285);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_snr_t2(काष्ठा cxd2841er_priv *priv, u32 *snr)
अणु
	u32 reg;
	u8 data[2];

	*snr = 0;
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): invalid state %d\n", __func__, priv->state);
		वापस -EINVAL;
	पूर्ण

	cxd2841er_मुक्तze_regs(priv);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x20);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x28, data, माप(data));
	cxd2841er_unमुक्तze_regs(priv);

	reg = ((u32)data[0] << 8) | (u32)data[1];
	अगर (reg == 0) अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): reg value out of range\n", __func__);
		वापस 0;
	पूर्ण
	अगर (reg > 10876)
		reg = 10876;
	*snr = 100 * ((INTLOG10X100(reg) - INTLOG10X100(12600 - reg)) + 320);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_पढ़ो_snr_i(काष्ठा cxd2841er_priv *priv, u32 *snr)
अणु
	u32 reg;
	u8 data[2];

	*snr = 0;
	अगर (priv->state != STATE_ACTIVE_TC) अणु
		dev_dbg(&priv->i2c->dev,
				"%s(): invalid state %d\n", __func__,
				priv->state);
		वापस -EINVAL;
	पूर्ण

	cxd2841er_मुक्तze_regs(priv);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x60);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x28, data, माप(data));
	cxd2841er_unमुक्तze_regs(priv);

	reg = ((u32)data[0] << 8) | (u32)data[1];
	अगर (reg == 0) अणु
		dev_dbg(&priv->i2c->dev,
				"%s(): reg value out of range\n", __func__);
		वापस 0;
	पूर्ण
	*snr = 10000 * (पूर्णांकlog10(reg) >> 24) - 9031;
	वापस 0;
पूर्ण

अटल u16 cxd2841er_पढ़ो_agc_gain_c(काष्ठा cxd2841er_priv *priv,
					u8 delsys)
अणु
	u8 data[2];

	cxd2841er_ग_लिखो_reg(
		priv, I2C_SLVT, 0x00, 0x40);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x49, data, 2);
	dev_dbg(&priv->i2c->dev,
			"%s(): AGC value=%u\n",
			__func__, (((u16)data[0] & 0x0F) << 8) |
			(u16)(data[1] & 0xFF));
	वापस ((((u16)data[0] & 0x0F) << 8) | (u16)(data[1] & 0xFF)) << 4;
पूर्ण

अटल u16 cxd2841er_पढ़ो_agc_gain_t_t2(काष्ठा cxd2841er_priv *priv,
					u8 delsys)
अणु
	u8 data[2];

	cxd2841er_ग_लिखो_reg(
		priv, I2C_SLVT, 0x00, (delsys == SYS_DVBT ? 0x10 : 0x20));
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x26, data, 2);
	dev_dbg(&priv->i2c->dev,
			"%s(): AGC value=%u\n",
			__func__, (((u16)data[0] & 0x0F) << 8) |
			(u16)(data[1] & 0xFF));
	वापस ((((u16)data[0] & 0x0F) << 8) | (u16)(data[1] & 0xFF)) << 4;
पूर्ण

अटल u16 cxd2841er_पढ़ो_agc_gain_i(काष्ठा cxd2841er_priv *priv,
		u8 delsys)
अणु
	u8 data[2];

	cxd2841er_ग_लिखो_reg(
			priv, I2C_SLVT, 0x00, 0x60);
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x26, data, 2);

	dev_dbg(&priv->i2c->dev,
			"%s(): AGC value=%u\n",
			__func__, (((u16)data[0] & 0x0F) << 8) |
			(u16)(data[1] & 0xFF));
	वापस ((((u16)data[0] & 0x0F) << 8) | (u16)(data[1] & 0xFF)) << 4;
पूर्ण

अटल u16 cxd2841er_पढ़ो_agc_gain_s(काष्ठा cxd2841er_priv *priv)
अणु
	u8 data[2];

	/* Set SLV-T Bank : 0xA0 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xa0);
	/*
	 *  slave     Bank      Addr      Bit       Signal name
	 * <SLV-T>    A0h       1Fh       [4:0]     IRFAGC_GAIN[12:8]
	 * <SLV-T>    A0h       20h       [7:0]     IRFAGC_GAIN[7:0]
	 */
	cxd2841er_पढ़ो_regs(priv, I2C_SLVT, 0x1f, data, 2);
	वापस ((((u16)data[0] & 0x1F) << 8) | (u16)(data[1] & 0xFF)) << 3;
पूर्ण

अटल व्योम cxd2841er_पढ़ो_ber(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;
	u32 ret, bit_error = 0, bit_count = 0;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	चयन (p->delivery_प्रणाली) अणु
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_B:
	हाल SYS_DVBC_ANNEX_C:
		ret = cxd2841er_पढ़ो_ber_c(priv, &bit_error, &bit_count);
		अवरोध;
	हाल SYS_ISDBT:
		ret = cxd2841er_पढ़ो_ber_i(priv, &bit_error, &bit_count);
		अवरोध;
	हाल SYS_DVBS:
		ret = cxd2841er_mon_पढ़ो_ber_s(priv, &bit_error, &bit_count);
		अवरोध;
	हाल SYS_DVBS2:
		ret = cxd2841er_mon_पढ़ो_ber_s2(priv, &bit_error, &bit_count);
		अवरोध;
	हाल SYS_DVBT:
		ret = cxd2841er_पढ़ो_ber_t(priv, &bit_error, &bit_count);
		अवरोध;
	हाल SYS_DVBT2:
		ret = cxd2841er_पढ़ो_ber_t2(priv, &bit_error, &bit_count);
		अवरोध;
	शेष:
		p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस;
	पूर्ण

	अगर (!ret) अणु
		p->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		p->post_bit_error.stat[0].uvalue += bit_error;
		p->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		p->post_bit_count.stat[0].uvalue += bit_count;
	पूर्ण अन्यथा अणु
		p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण
पूर्ण

अटल व्योम cxd2841er_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;
	s32 strength;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	चयन (p->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		strength = cxd2841er_पढ़ो_agc_gain_t_t2(priv,
							p->delivery_प्रणाली);
		p->strength.stat[0].scale = FE_SCALE_DECIBEL;
		/* Formula was empirically determinated @ 410 MHz */
		p->strength.stat[0].uvalue = strength * 366 / 100 - 89520;
		अवरोध;	/* Code moved out of the function */
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_B:
	हाल SYS_DVBC_ANNEX_C:
		strength = cxd2841er_पढ़ो_agc_gain_c(priv,
							p->delivery_प्रणाली);
		p->strength.stat[0].scale = FE_SCALE_DECIBEL;
		/*
		 * Formula was empirically determinated via linear regression,
		 * using frequencies: 175 MHz, 410 MHz and 800 MHz, and a
		 * stream modulated with QAM64
		 */
		p->strength.stat[0].uvalue = strength * 4045 / 1000 - 85224;
		अवरोध;
	हाल SYS_ISDBT:
		strength = cxd2841er_पढ़ो_agc_gain_i(priv, p->delivery_प्रणाली);
		p->strength.stat[0].scale = FE_SCALE_DECIBEL;
		/*
		 * Formula was empirically determinated via linear regression,
		 * using frequencies: 175 MHz, 410 MHz and 800 MHz.
		 */
		p->strength.stat[0].uvalue = strength * 3775 / 1000 - 90185;
		अवरोध;
	हाल SYS_DVBS:
	हाल SYS_DVBS2:
		strength = 65535 - cxd2841er_पढ़ो_agc_gain_s(priv);
		p->strength.stat[0].scale = FE_SCALE_RELATIVE;
		p->strength.stat[0].uvalue = strength;
		अवरोध;
	शेष:
		p->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम cxd2841er_पढ़ो_snr(काष्ठा dvb_frontend *fe)
अणु
	u32 पंचांगp = 0;
	पूर्णांक ret = 0;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	चयन (p->delivery_प्रणाली) अणु
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_B:
	हाल SYS_DVBC_ANNEX_C:
		ret = cxd2841er_पढ़ो_snr_c(priv, &पंचांगp);
		अवरोध;
	हाल SYS_DVBT:
		ret = cxd2841er_पढ़ो_snr_t(priv, &पंचांगp);
		अवरोध;
	हाल SYS_DVBT2:
		ret = cxd2841er_पढ़ो_snr_t2(priv, &पंचांगp);
		अवरोध;
	हाल SYS_ISDBT:
		ret = cxd2841er_पढ़ो_snr_i(priv, &पंचांगp);
		अवरोध;
	हाल SYS_DVBS:
	हाल SYS_DVBS2:
		ret = cxd2841er_dvbs_पढ़ो_snr(priv, p->delivery_प्रणाली, &पंचांगp);
		अवरोध;
	शेष:
		dev_dbg(&priv->i2c->dev, "%s(): unknown delivery system %d\n",
			__func__, p->delivery_प्रणाली);
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस;
	पूर्ण

	dev_dbg(&priv->i2c->dev, "%s(): snr=%d\n",
			__func__, (पूर्णांक32_t)पंचांगp);

	अगर (!ret) अणु
		p->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		p->cnr.stat[0].svalue = पंचांगp;
	पूर्ण अन्यथा अणु
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण
पूर्ण

अटल व्योम cxd2841er_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;
	u32 ucblocks = 0;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	चयन (p->delivery_प्रणाली) अणु
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_B:
	हाल SYS_DVBC_ANNEX_C:
		cxd2841er_पढ़ो_packet_errors_c(priv, &ucblocks);
		अवरोध;
	हाल SYS_DVBT:
		cxd2841er_पढ़ो_packet_errors_t(priv, &ucblocks);
		अवरोध;
	हाल SYS_DVBT2:
		cxd2841er_पढ़ो_packet_errors_t2(priv, &ucblocks);
		अवरोध;
	हाल SYS_ISDBT:
		cxd2841er_पढ़ो_packet_errors_i(priv, &ucblocks);
		अवरोध;
	शेष:
		p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस;
	पूर्ण
	dev_dbg(&priv->i2c->dev, "%s() ucblocks=%u\n", __func__, ucblocks);

	p->block_error.stat[0].scale = FE_SCALE_COUNTER;
	p->block_error.stat[0].uvalue = ucblocks;
पूर्ण

अटल पूर्णांक cxd2841er_dvbt2_set_profile(
	काष्ठा cxd2841er_priv *priv, क्रमागत cxd2841er_dvbt2_profile_t profile)
अणु
	u8 tune_mode;
	u8 seq_not2d_समय;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	चयन (profile) अणु
	हाल DVBT2_PROखाता_BASE:
		tune_mode = 0x01;
		/* Set early unlock समय */
		seq_not2d_समय = (priv->xtal == SONY_XTAL_24000)?0x0E:0x0C;
		अवरोध;
	हाल DVBT2_PROखाता_LITE:
		tune_mode = 0x05;
		/* Set early unlock समय */
		seq_not2d_समय = (priv->xtal == SONY_XTAL_24000)?0x2E:0x28;
		अवरोध;
	हाल DVBT2_PROखाता_ANY:
		tune_mode = 0x00;
		/* Set early unlock समय */
		seq_not2d_समय = (priv->xtal == SONY_XTAL_24000)?0x2E:0x28;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	/* Set SLV-T Bank : 0x2E */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x2e);
	/* Set profile and tune mode */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x10, tune_mode, 0x07);
	/* Set SLV-T Bank : 0x2B */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x2b);
	/* Set early unlock detection समय */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x9d, seq_not2d_समय);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_dvbt2_set_plp_config(काष्ठा cxd2841er_priv *priv,
					  u8 is_स्वतः, u8 plp_id)
अणु
	अगर (is_स्वतः) अणु
		dev_dbg(&priv->i2c->dev,
			"%s() using auto PLP selection\n", __func__);
	पूर्ण अन्यथा अणु
		dev_dbg(&priv->i2c->dev,
			"%s() using manual PLP selection, ID %d\n",
			__func__, plp_id);
	पूर्ण
	/* Set SLV-T Bank : 0x23 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x23);
	अगर (!is_स्वतः) अणु
		/* Manual PLP selection mode. Set the data PLP Id. */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xaf, plp_id);
	पूर्ण
	/* Auto PLP select (Scanning mode = 0x00). Data PLP select = 0x01. */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xad, (is_स्वतः ? 0x00 : 0x01));
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_sleep_tc_to_active_t2_band(काष्ठा cxd2841er_priv *priv,
						u32 bandwidth)
अणु
	u32 अगरfreq, अगरhz;
	u8 data[MAX_WRITE_REGSIZE];

	अटल स्थिर uपूर्णांक8_t nominalRate8bw[3][5] = अणु
		/* TRCG Nominal Rate [37:0] */
		अणु0x11, 0xF0, 0x00, 0x00, 0x00पूर्ण, /* 20.5MHz XTal */
		अणु0x15, 0x00, 0x00, 0x00, 0x00पूर्ण, /* 24MHz XTal */
		अणु0x11, 0xF0, 0x00, 0x00, 0x00पूर्ण  /* 41MHz XTal */
	पूर्ण;

	अटल स्थिर uपूर्णांक8_t nominalRate7bw[3][5] = अणु
		/* TRCG Nominal Rate [37:0] */
		अणु0x14, 0x80, 0x00, 0x00, 0x00पूर्ण, /* 20.5MHz XTal */
		अणु0x18, 0x00, 0x00, 0x00, 0x00पूर्ण, /* 24MHz XTal */
		अणु0x14, 0x80, 0x00, 0x00, 0x00पूर्ण  /* 41MHz XTal */
	पूर्ण;

	अटल स्थिर uपूर्णांक8_t nominalRate6bw[3][5] = अणु
		/* TRCG Nominal Rate [37:0] */
		अणु0x17, 0xEA, 0xAA, 0xAA, 0xAAपूर्ण, /* 20.5MHz XTal */
		अणु0x1C, 0x00, 0x00, 0x00, 0x00पूर्ण, /* 24MHz XTal */
		अणु0x17, 0xEA, 0xAA, 0xAA, 0xAAपूर्ण  /* 41MHz XTal */
	पूर्ण;

	अटल स्थिर uपूर्णांक8_t nominalRate5bw[3][5] = अणु
		/* TRCG Nominal Rate [37:0] */
		अणु0x1C, 0xB3, 0x33, 0x33, 0x33पूर्ण, /* 20.5MHz XTal */
		अणु0x21, 0x99, 0x99, 0x99, 0x99पूर्ण, /* 24MHz XTal */
		अणु0x1C, 0xB3, 0x33, 0x33, 0x33पूर्ण  /* 41MHz XTal */
	पूर्ण;

	अटल स्थिर uपूर्णांक8_t nominalRate17bw[3][5] = अणु
		/* TRCG Nominal Rate [37:0] */
		अणु0x58, 0xE2, 0xAF, 0xE0, 0xBCपूर्ण, /* 20.5MHz XTal */
		अणु0x68, 0x0F, 0xA2, 0x32, 0xD0पूर्ण, /* 24MHz XTal */
		अणु0x58, 0xE2, 0xAF, 0xE0, 0xBCपूर्ण  /* 41MHz XTal */
	पूर्ण;

	अटल स्थिर uपूर्णांक8_t itbCoef8bw[3][14] = अणु
		अणु0x26, 0xAF, 0x06, 0xCD, 0x13, 0xBB, 0x28, 0xBA,
			0x23, 0xA9, 0x1F, 0xA8, 0x2C, 0xC8पूर्ण, /* 20.5MHz XTal */
		अणु0x2F, 0xBA, 0x28, 0x9B, 0x28, 0x9D, 0x28, 0xA1,
			0x29, 0xA5, 0x2A, 0xAC, 0x29, 0xB5पूर्ण, /* 24MHz XTal   */
		अणु0x26, 0xAF, 0x06, 0xCD, 0x13, 0xBB, 0x28, 0xBA,
			0x23, 0xA9, 0x1F, 0xA8, 0x2C, 0xC8पूर्ण  /* 41MHz XTal   */
	पूर्ण;

	अटल स्थिर uपूर्णांक8_t itbCoef7bw[3][14] = अणु
		अणु0x2C, 0xBD, 0x02, 0xCF, 0x04, 0xF8, 0x23, 0xA6,
			0x29, 0xB0, 0x26, 0xA9, 0x21, 0xA5पूर्ण, /* 20.5MHz XTal */
		अणु0x30, 0xB1, 0x29, 0x9A, 0x28, 0x9C, 0x28, 0xA0,
			0x29, 0xA2, 0x2B, 0xA6, 0x2B, 0xADपूर्ण, /* 24MHz XTal   */
		अणु0x2C, 0xBD, 0x02, 0xCF, 0x04, 0xF8, 0x23, 0xA6,
			0x29, 0xB0, 0x26, 0xA9, 0x21, 0xA5पूर्ण  /* 41MHz XTal   */
	पूर्ण;

	अटल स्थिर uपूर्णांक8_t itbCoef6bw[3][14] = अणु
		अणु0x27, 0xA7, 0x28, 0xB3, 0x02, 0xF0, 0x01, 0xE8,
			0x00, 0xCF, 0x00, 0xE6, 0x23, 0xA4पूर्ण, /* 20.5MHz XTal */
		अणु0x31, 0xA8, 0x29, 0x9B, 0x27, 0x9C, 0x28, 0x9E,
			0x29, 0xA4, 0x29, 0xA2, 0x29, 0xA8पूर्ण, /* 24MHz XTal   */
		अणु0x27, 0xA7, 0x28, 0xB3, 0x02, 0xF0, 0x01, 0xE8,
			0x00, 0xCF, 0x00, 0xE6, 0x23, 0xA4पूर्ण  /* 41MHz XTal   */
	पूर्ण;

	अटल स्थिर uपूर्णांक8_t itbCoef5bw[3][14] = अणु
		अणु0x27, 0xA7, 0x28, 0xB3, 0x02, 0xF0, 0x01, 0xE8,
			0x00, 0xCF, 0x00, 0xE6, 0x23, 0xA4पूर्ण, /* 20.5MHz XTal */
		अणु0x31, 0xA8, 0x29, 0x9B, 0x27, 0x9C, 0x28, 0x9E,
			0x29, 0xA4, 0x29, 0xA2, 0x29, 0xA8पूर्ण, /* 24MHz XTal   */
		अणु0x27, 0xA7, 0x28, 0xB3, 0x02, 0xF0, 0x01, 0xE8,
			0x00, 0xCF, 0x00, 0xE6, 0x23, 0xA4पूर्ण  /* 41MHz XTal   */
	पूर्ण;

	अटल स्थिर uपूर्णांक8_t itbCoef17bw[3][14] = अणु
		अणु0x25, 0xA0, 0x36, 0x8D, 0x2E, 0x94, 0x28, 0x9B,
			0x32, 0x90, 0x2C, 0x9D, 0x29, 0x99पूर्ण, /* 20.5MHz XTal */
		अणु0x33, 0x8E, 0x2B, 0x97, 0x2D, 0x95, 0x37, 0x8B,
			0x30, 0x97, 0x2D, 0x9A, 0x21, 0xA4पूर्ण, /* 24MHz XTal   */
		अणु0x25, 0xA0, 0x36, 0x8D, 0x2E, 0x94, 0x28, 0x9B,
			0x32, 0x90, 0x2C, 0x9D, 0x29, 0x99पूर्ण  /* 41MHz XTal   */
	पूर्ण;

	/* Set SLV-T Bank : 0x20 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x20);

	चयन (bandwidth) अणु
	हाल 8000000:
		/* <Timing Recovery setting> */
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0x9F, nominalRate8bw[priv->xtal], 5);

		/* Set SLV-T Bank : 0x27 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x27);
		cxd2841er_set_reg_bits(priv, I2C_SLVT,
				0x7a, 0x00, 0x0f);

		/* Set SLV-T Bank : 0x10 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);

		/* Group delay equaliser settings क्रम
		 * ASCOT2D, ASCOT2E and ASCOT3 tuners
		 */
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0xA6, itbCoef8bw[priv->xtal], 14);
		/* <IF freq setting> */
		अगरhz = cxd2841er_get_अगर_hz(priv, 4800000);
		अगरfreq = cxd2841er_calc_अगरfreq_xtal(priv->xtal, अगरhz);
		data[0] = (u8) ((अगरfreq >> 16) & 0xff);
		data[1] = (u8)((अगरfreq >> 8) & 0xff);
		data[2] = (u8)(अगरfreq & 0xff);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xB6, data, 3);
		/* System bandwidth setting */
		cxd2841er_set_reg_bits(
				priv, I2C_SLVT, 0xD7, 0x00, 0x07);
		अवरोध;
	हाल 7000000:
		/* <Timing Recovery setting> */
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0x9F, nominalRate7bw[priv->xtal], 5);

		/* Set SLV-T Bank : 0x27 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x27);
		cxd2841er_set_reg_bits(priv, I2C_SLVT,
				0x7a, 0x00, 0x0f);

		/* Set SLV-T Bank : 0x10 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);

		/* Group delay equaliser settings क्रम
		 * ASCOT2D, ASCOT2E and ASCOT3 tuners
		 */
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0xA6, itbCoef7bw[priv->xtal], 14);
		/* <IF freq setting> */
		अगरhz = cxd2841er_get_अगर_hz(priv, 4200000);
		अगरfreq = cxd2841er_calc_अगरfreq_xtal(priv->xtal, अगरhz);
		data[0] = (u8) ((अगरfreq >> 16) & 0xff);
		data[1] = (u8)((अगरfreq >> 8) & 0xff);
		data[2] = (u8)(अगरfreq & 0xff);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xB6, data, 3);
		/* System bandwidth setting */
		cxd2841er_set_reg_bits(
				priv, I2C_SLVT, 0xD7, 0x02, 0x07);
		अवरोध;
	हाल 6000000:
		/* <Timing Recovery setting> */
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0x9F, nominalRate6bw[priv->xtal], 5);

		/* Set SLV-T Bank : 0x27 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x27);
		cxd2841er_set_reg_bits(priv, I2C_SLVT,
				0x7a, 0x00, 0x0f);

		/* Set SLV-T Bank : 0x10 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);

		/* Group delay equaliser settings क्रम
		 * ASCOT2D, ASCOT2E and ASCOT3 tuners
		 */
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0xA6, itbCoef6bw[priv->xtal], 14);
		/* <IF freq setting> */
		अगरhz = cxd2841er_get_अगर_hz(priv, 3600000);
		अगरfreq = cxd2841er_calc_अगरfreq_xtal(priv->xtal, अगरhz);
		data[0] = (u8) ((अगरfreq >> 16) & 0xff);
		data[1] = (u8)((अगरfreq >> 8) & 0xff);
		data[2] = (u8)(अगरfreq & 0xff);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xB6, data, 3);
		/* System bandwidth setting */
		cxd2841er_set_reg_bits(
				priv, I2C_SLVT, 0xD7, 0x04, 0x07);
		अवरोध;
	हाल 5000000:
		/* <Timing Recovery setting> */
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0x9F, nominalRate5bw[priv->xtal], 5);

		/* Set SLV-T Bank : 0x27 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x27);
		cxd2841er_set_reg_bits(priv, I2C_SLVT,
				0x7a, 0x00, 0x0f);

		/* Set SLV-T Bank : 0x10 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);

		/* Group delay equaliser settings क्रम
		 * ASCOT2D, ASCOT2E and ASCOT3 tuners
		 */
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0xA6, itbCoef5bw[priv->xtal], 14);
		/* <IF freq setting> */
		अगरhz = cxd2841er_get_अगर_hz(priv, 3600000);
		अगरfreq = cxd2841er_calc_अगरfreq_xtal(priv->xtal, अगरhz);
		data[0] = (u8) ((अगरfreq >> 16) & 0xff);
		data[1] = (u8)((अगरfreq >> 8) & 0xff);
		data[2] = (u8)(अगरfreq & 0xff);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xB6, data, 3);
		/* System bandwidth setting */
		cxd2841er_set_reg_bits(
				priv, I2C_SLVT, 0xD7, 0x06, 0x07);
		अवरोध;
	हाल 1712000:
		/* <Timing Recovery setting> */
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0x9F, nominalRate17bw[priv->xtal], 5);

		/* Set SLV-T Bank : 0x27 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x27);
		cxd2841er_set_reg_bits(priv, I2C_SLVT,
				0x7a, 0x03, 0x0f);

		/* Set SLV-T Bank : 0x10 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);

		/* Group delay equaliser settings क्रम
		 * ASCOT2D, ASCOT2E and ASCOT3 tuners
		 */
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0xA6, itbCoef17bw[priv->xtal], 14);
		/* <IF freq setting> */
		अगरhz = cxd2841er_get_अगर_hz(priv, 3500000);
		अगरfreq = cxd2841er_calc_अगरfreq_xtal(priv->xtal, अगरhz);
		data[0] = (u8) ((अगरfreq >> 16) & 0xff);
		data[1] = (u8)((अगरfreq >> 8) & 0xff);
		data[2] = (u8)(अगरfreq & 0xff);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xB6, data, 3);
		/* System bandwidth setting */
		cxd2841er_set_reg_bits(
				priv, I2C_SLVT, 0xD7, 0x03, 0x07);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_sleep_tc_to_active_t_band(
		काष्ठा cxd2841er_priv *priv, u32 bandwidth)
अणु
	u8 data[MAX_WRITE_REGSIZE];
	u32 अगरfreq, अगरhz;
	अटल स्थिर u8 nominalRate8bw[3][5] = अणु
		/* TRCG Nominal Rate [37:0] */
		अणु0x11, 0xF0, 0x00, 0x00, 0x00पूर्ण, /* 20.5MHz XTal */
		अणु0x15, 0x00, 0x00, 0x00, 0x00पूर्ण, /* 24MHz XTal */
		अणु0x11, 0xF0, 0x00, 0x00, 0x00पूर्ण  /* 41MHz XTal */
	पूर्ण;
	अटल स्थिर u8 nominalRate7bw[3][5] = अणु
		/* TRCG Nominal Rate [37:0] */
		अणु0x14, 0x80, 0x00, 0x00, 0x00पूर्ण, /* 20.5MHz XTal */
		अणु0x18, 0x00, 0x00, 0x00, 0x00पूर्ण, /* 24MHz XTal */
		अणु0x14, 0x80, 0x00, 0x00, 0x00पूर्ण  /* 41MHz XTal */
	पूर्ण;
	अटल स्थिर u8 nominalRate6bw[3][5] = अणु
		/* TRCG Nominal Rate [37:0] */
		अणु0x17, 0xEA, 0xAA, 0xAA, 0xAAपूर्ण, /* 20.5MHz XTal */
		अणु0x1C, 0x00, 0x00, 0x00, 0x00पूर्ण, /* 24MHz XTal */
		अणु0x17, 0xEA, 0xAA, 0xAA, 0xAAपूर्ण  /* 41MHz XTal */
	पूर्ण;
	अटल स्थिर u8 nominalRate5bw[3][5] = अणु
		/* TRCG Nominal Rate [37:0] */
		अणु0x1C, 0xB3, 0x33, 0x33, 0x33पूर्ण, /* 20.5MHz XTal */
		अणु0x21, 0x99, 0x99, 0x99, 0x99पूर्ण, /* 24MHz XTal */
		अणु0x1C, 0xB3, 0x33, 0x33, 0x33पूर्ण  /* 41MHz XTal */
	पूर्ण;

	अटल स्थिर u8 itbCoef8bw[3][14] = अणु
		अणु0x26, 0xAF, 0x06, 0xCD, 0x13, 0xBB, 0x28, 0xBA, 0x23, 0xA9,
			0x1F, 0xA8, 0x2C, 0xC8पूर्ण, /* 20.5MHz XTal */
		अणु0x2F, 0xBA, 0x28, 0x9B, 0x28, 0x9D, 0x28, 0xA1, 0x29, 0xA5,
			0x2A, 0xAC, 0x29, 0xB5पूर्ण, /* 24MHz XTal   */
		अणु0x26, 0xAF, 0x06, 0xCD, 0x13, 0xBB, 0x28, 0xBA, 0x23, 0xA9,
			0x1F, 0xA8, 0x2C, 0xC8पूर्ण  /* 41MHz XTal   */
	पूर्ण;
	अटल स्थिर u8 itbCoef7bw[3][14] = अणु
		अणु0x2C, 0xBD, 0x02, 0xCF, 0x04, 0xF8, 0x23, 0xA6, 0x29, 0xB0,
			0x26, 0xA9, 0x21, 0xA5पूर्ण, /* 20.5MHz XTal */
		अणु0x30, 0xB1, 0x29, 0x9A, 0x28, 0x9C, 0x28, 0xA0, 0x29, 0xA2,
			0x2B, 0xA6, 0x2B, 0xADपूर्ण, /* 24MHz XTal   */
		अणु0x2C, 0xBD, 0x02, 0xCF, 0x04, 0xF8, 0x23, 0xA6, 0x29, 0xB0,
			0x26, 0xA9, 0x21, 0xA5पूर्ण  /* 41MHz XTal   */
	पूर्ण;
	अटल स्थिर u8 itbCoef6bw[3][14] = अणु
		अणु0x27, 0xA7, 0x28, 0xB3, 0x02, 0xF0, 0x01, 0xE8, 0x00, 0xCF,
			0x00, 0xE6, 0x23, 0xA4पूर्ण, /* 20.5MHz XTal */
		अणु0x31, 0xA8, 0x29, 0x9B, 0x27, 0x9C, 0x28, 0x9E, 0x29, 0xA4,
			0x29, 0xA2, 0x29, 0xA8पूर्ण, /* 24MHz XTal   */
		अणु0x27, 0xA7, 0x28, 0xB3, 0x02, 0xF0, 0x01, 0xE8, 0x00, 0xCF,
			0x00, 0xE6, 0x23, 0xA4पूर्ण  /* 41MHz XTal   */
	पूर्ण;
	अटल स्थिर u8 itbCoef5bw[3][14] = अणु
		अणु0x27, 0xA7, 0x28, 0xB3, 0x02, 0xF0, 0x01, 0xE8, 0x00, 0xCF,
			0x00, 0xE6, 0x23, 0xA4पूर्ण, /* 20.5MHz XTal */
		अणु0x31, 0xA8, 0x29, 0x9B, 0x27, 0x9C, 0x28, 0x9E, 0x29, 0xA4,
			0x29, 0xA2, 0x29, 0xA8पूर्ण, /* 24MHz XTal   */
		अणु0x27, 0xA7, 0x28, 0xB3, 0x02, 0xF0, 0x01, 0xE8, 0x00, 0xCF,
			0x00, 0xE6, 0x23, 0xA4पूर्ण  /* 41MHz XTal   */
	पूर्ण;

	/* Set SLV-T Bank : 0x13 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x13);
	/* Echo perक्रमmance optimization setting */
	data[0] = 0x01;
	data[1] = 0x14;
	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x9C, data, 2);

	/* Set SLV-T Bank : 0x10 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);

	चयन (bandwidth) अणु
	हाल 8000000:
		/* <Timing Recovery setting> */
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0x9F, nominalRate8bw[priv->xtal], 5);
		/* Group delay equaliser settings क्रम
		 * ASCOT2D, ASCOT2E and ASCOT3 tuners
		*/
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0xA6, itbCoef8bw[priv->xtal], 14);
		/* <IF freq setting> */
		अगरhz = cxd2841er_get_अगर_hz(priv, 4800000);
		अगरfreq = cxd2841er_calc_अगरfreq_xtal(priv->xtal, अगरhz);
		data[0] = (u8) ((अगरfreq >> 16) & 0xff);
		data[1] = (u8)((अगरfreq >> 8) & 0xff);
		data[2] = (u8)(अगरfreq & 0xff);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xB6, data, 3);
		/* System bandwidth setting */
		cxd2841er_set_reg_bits(
			priv, I2C_SLVT, 0xD7, 0x00, 0x07);

		/* Demod core latency setting */
		अगर (priv->xtal == SONY_XTAL_24000) अणु
			data[0] = 0x15;
			data[1] = 0x28;
		पूर्ण अन्यथा अणु
			data[0] = 0x01;
			data[1] = 0xE0;
		पूर्ण
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xD9, data, 2);

		/* Notch filter setting */
		data[0] = 0x01;
		data[1] = 0x02;
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x17);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x38, data, 2);
		अवरोध;
	हाल 7000000:
		/* <Timing Recovery setting> */
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0x9F, nominalRate7bw[priv->xtal], 5);
		/* Group delay equaliser settings क्रम
		 * ASCOT2D, ASCOT2E and ASCOT3 tuners
		*/
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0xA6, itbCoef7bw[priv->xtal], 14);
		/* <IF freq setting> */
		अगरhz = cxd2841er_get_अगर_hz(priv, 4200000);
		अगरfreq = cxd2841er_calc_अगरfreq_xtal(priv->xtal, अगरhz);
		data[0] = (u8) ((अगरfreq >> 16) & 0xff);
		data[1] = (u8)((अगरfreq >> 8) & 0xff);
		data[2] = (u8)(अगरfreq & 0xff);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xB6, data, 3);
		/* System bandwidth setting */
		cxd2841er_set_reg_bits(
			priv, I2C_SLVT, 0xD7, 0x02, 0x07);

		/* Demod core latency setting */
		अगर (priv->xtal == SONY_XTAL_24000) अणु
			data[0] = 0x1F;
			data[1] = 0xF8;
		पूर्ण अन्यथा अणु
			data[0] = 0x12;
			data[1] = 0xF8;
		पूर्ण
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xD9, data, 2);

		/* Notch filter setting */
		data[0] = 0x00;
		data[1] = 0x03;
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x17);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x38, data, 2);
		अवरोध;
	हाल 6000000:
		/* <Timing Recovery setting> */
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0x9F, nominalRate6bw[priv->xtal], 5);
		/* Group delay equaliser settings क्रम
		 * ASCOT2D, ASCOT2E and ASCOT3 tuners
		*/
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0xA6, itbCoef6bw[priv->xtal], 14);
		/* <IF freq setting> */
		अगरhz = cxd2841er_get_अगर_hz(priv, 3600000);
		अगरfreq = cxd2841er_calc_अगरfreq_xtal(priv->xtal, अगरhz);
		data[0] = (u8) ((अगरfreq >> 16) & 0xff);
		data[1] = (u8)((अगरfreq >> 8) & 0xff);
		data[2] = (u8)(अगरfreq & 0xff);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xB6, data, 3);
		/* System bandwidth setting */
		cxd2841er_set_reg_bits(
			priv, I2C_SLVT, 0xD7, 0x04, 0x07);

		/* Demod core latency setting */
		अगर (priv->xtal == SONY_XTAL_24000) अणु
			data[0] = 0x25;
			data[1] = 0x4C;
		पूर्ण अन्यथा अणु
			data[0] = 0x1F;
			data[1] = 0xDC;
		पूर्ण
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xD9, data, 2);

		/* Notch filter setting */
		data[0] = 0x00;
		data[1] = 0x03;
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x17);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x38, data, 2);
		अवरोध;
	हाल 5000000:
		/* <Timing Recovery setting> */
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0x9F, nominalRate5bw[priv->xtal], 5);
		/* Group delay equaliser settings क्रम
		 * ASCOT2D, ASCOT2E and ASCOT3 tuners
		*/
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0xA6, itbCoef5bw[priv->xtal], 14);
		/* <IF freq setting> */
		अगरhz = cxd2841er_get_अगर_hz(priv, 3600000);
		अगरfreq = cxd2841er_calc_अगरfreq_xtal(priv->xtal, अगरhz);
		data[0] = (u8) ((अगरfreq >> 16) & 0xff);
		data[1] = (u8)((अगरfreq >> 8) & 0xff);
		data[2] = (u8)(अगरfreq & 0xff);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xB6, data, 3);
		/* System bandwidth setting */
		cxd2841er_set_reg_bits(
			priv, I2C_SLVT, 0xD7, 0x06, 0x07);

		/* Demod core latency setting */
		अगर (priv->xtal == SONY_XTAL_24000) अणु
			data[0] = 0x2C;
			data[1] = 0xC2;
		पूर्ण अन्यथा अणु
			data[0] = 0x26;
			data[1] = 0x3C;
		पूर्ण
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xD9, data, 2);

		/* Notch filter setting */
		data[0] = 0x00;
		data[1] = 0x03;
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x17);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x38, data, 2);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_sleep_tc_to_active_i_band(
		काष्ठा cxd2841er_priv *priv, u32 bandwidth)
अणु
	u32 अगरfreq, अगरhz;
	u8 data[3];

	/* TRCG Nominal Rate */
	अटल स्थिर u8 nominalRate8bw[3][5] = अणु
		अणु0x00, 0x00, 0x00, 0x00, 0x00पूर्ण, /* 20.5MHz XTal */
		अणु0x11, 0xB8, 0x00, 0x00, 0x00पूर्ण, /* 24MHz XTal */
		अणु0x00, 0x00, 0x00, 0x00, 0x00पूर्ण  /* 41MHz XTal */
	पूर्ण;

	अटल स्थिर u8 nominalRate7bw[3][5] = अणु
		अणु0x00, 0x00, 0x00, 0x00, 0x00पूर्ण, /* 20.5MHz XTal */
		अणु0x14, 0x40, 0x00, 0x00, 0x00पूर्ण, /* 24MHz XTal */
		अणु0x00, 0x00, 0x00, 0x00, 0x00पूर्ण  /* 41MHz XTal */
	पूर्ण;

	अटल स्थिर u8 nominalRate6bw[3][5] = अणु
		अणु0x14, 0x2E, 0x00, 0x00, 0x00पूर्ण, /* 20.5MHz XTal */
		अणु0x17, 0xA0, 0x00, 0x00, 0x00पूर्ण, /* 24MHz XTal */
		अणु0x14, 0x2E, 0x00, 0x00, 0x00पूर्ण  /* 41MHz XTal */
	पूर्ण;

	अटल स्थिर u8 itbCoef8bw[3][14] = अणु
		अणु0x00पूर्ण, /* 20.5MHz XTal */
		अणु0x2F, 0xBA, 0x28, 0x9B, 0x28, 0x9D, 0x28, 0xA1, 0x29,
			0xA5, 0x2A, 0xAC, 0x29, 0xB5पूर्ण, /* 24MHz Xtal */
		अणु0x0पूर्ण, /* 41MHz XTal   */
	पूर्ण;

	अटल स्थिर u8 itbCoef7bw[3][14] = अणु
		अणु0x00पूर्ण, /* 20.5MHz XTal */
		अणु0x30, 0xB1, 0x29, 0x9A, 0x28, 0x9C, 0x28, 0xA0, 0x29,
			0xA2, 0x2B, 0xA6, 0x2B, 0xADपूर्ण, /* 24MHz Xtal */
		अणु0x00पूर्ण, /* 41MHz XTal   */
	पूर्ण;

	अटल स्थिर u8 itbCoef6bw[3][14] = अणु
		अणु0x27, 0xA7, 0x28, 0xB3, 0x02, 0xF0, 0x01, 0xE8, 0x00,
			0xCF, 0x00, 0xE6, 0x23, 0xA4पूर्ण, /* 20.5MHz XTal */
		अणु0x31, 0xA8, 0x29, 0x9B, 0x27, 0x9C, 0x28, 0x9E, 0x29,
			0xA4, 0x29, 0xA2, 0x29, 0xA8पूर्ण, /* 24MHz Xtal   */
		अणु0x27, 0xA7, 0x28, 0xB3, 0x02, 0xF0, 0x01, 0xE8, 0x00,
			0xCF, 0x00, 0xE6, 0x23, 0xA4पूर्ण, /* 41MHz XTal   */
	पूर्ण;

	dev_dbg(&priv->i2c->dev, "%s() bandwidth=%u\n", __func__, bandwidth);
	/* Set SLV-T Bank : 0x10 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);

	/*  20.5/41MHz Xtal support is not available
	 *  on ISDB-T 7MHzBW and 8MHzBW
	*/
	अगर (priv->xtal != SONY_XTAL_24000 && bandwidth > 6000000) अणु
		dev_err(&priv->i2c->dev,
			"%s(): bandwidth %d supported only for 24MHz xtal\n",
			__func__, bandwidth);
		वापस -EINVAL;
	पूर्ण

	चयन (bandwidth) अणु
	हाल 8000000:
		/* TRCG Nominal Rate */
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0x9F, nominalRate8bw[priv->xtal], 5);
		/*  Group delay equaliser settings क्रम ASCOT tuners optimized */
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0xA6, itbCoef8bw[priv->xtal], 14);

		/* IF freq setting */
		अगरhz = cxd2841er_get_अगर_hz(priv, 4750000);
		अगरfreq = cxd2841er_calc_अगरfreq_xtal(priv->xtal, अगरhz);
		data[0] = (u8) ((अगरfreq >> 16) & 0xff);
		data[1] = (u8)((अगरfreq >> 8) & 0xff);
		data[2] = (u8)(अगरfreq & 0xff);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xB6, data, 3);

		/* System bandwidth setting */
		cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xd7, 0x0, 0x7);

		/* Demod core latency setting */
		data[0] = 0x13;
		data[1] = 0xFC;
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xD9, data, 2);

		/* Acquisition optimization setting */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x12);
		cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x71, 0x03, 0x07);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x15);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xBE, 0x03);
		अवरोध;
	हाल 7000000:
		/* TRCG Nominal Rate */
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0x9F, nominalRate7bw[priv->xtal], 5);
		/*  Group delay equaliser settings क्रम ASCOT tuners optimized */
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0xA6, itbCoef7bw[priv->xtal], 14);

		/* IF freq setting */
		अगरhz = cxd2841er_get_अगर_hz(priv, 4150000);
		अगरfreq = cxd2841er_calc_अगरfreq_xtal(priv->xtal, अगरhz);
		data[0] = (u8) ((अगरfreq >> 16) & 0xff);
		data[1] = (u8)((अगरfreq >> 8) & 0xff);
		data[2] = (u8)(अगरfreq & 0xff);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xB6, data, 3);

		/* System bandwidth setting */
		cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xd7, 0x02, 0x7);

		/* Demod core latency setting */
		data[0] = 0x1A;
		data[1] = 0xFA;
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xD9, data, 2);

		/* Acquisition optimization setting */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x12);
		cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x71, 0x03, 0x07);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x15);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xBE, 0x02);
		अवरोध;
	हाल 6000000:
		/* TRCG Nominal Rate */
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0x9F, nominalRate6bw[priv->xtal], 5);
		/*  Group delay equaliser settings क्रम ASCOT tuners optimized */
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(priv, I2C_SLVT,
				0xA6, itbCoef6bw[priv->xtal], 14);

		/* IF freq setting */
		अगरhz = cxd2841er_get_अगर_hz(priv, 3550000);
		अगरfreq = cxd2841er_calc_अगरfreq_xtal(priv->xtal, अगरhz);
		data[0] = (u8) ((अगरfreq >> 16) & 0xff);
		data[1] = (u8)((अगरfreq >> 8) & 0xff);
		data[2] = (u8)(अगरfreq & 0xff);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xB6, data, 3);

		/* System bandwidth setting */
		cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xd7, 0x04, 0x7);

		/* Demod core latency setting */
		अगर (priv->xtal == SONY_XTAL_24000) अणु
			data[0] = 0x1F;
			data[1] = 0x79;
		पूर्ण अन्यथा अणु
			data[0] = 0x1A;
			data[1] = 0xE2;
		पूर्ण
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xD9, data, 2);

		/* Acquisition optimization setting */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x12);
		cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x71, 0x07, 0x07);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x15);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xBE, 0x02);
		अवरोध;
	शेष:
		dev_dbg(&priv->i2c->dev, "%s(): invalid bandwidth %d\n",
				__func__, bandwidth);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_sleep_tc_to_active_c_band(काष्ठा cxd2841er_priv *priv,
					       u32 bandwidth)
अणु
	u8 bw7_8mhz_b10_a6[] = अणु
		0x2D, 0xC7, 0x04, 0xF4, 0x07, 0xC5, 0x2A, 0xB8,
		0x27, 0x9E, 0x27, 0xA4, 0x29, 0xAB पूर्ण;
	u8 bw6mhz_b10_a6[] = अणु
		0x27, 0xA7, 0x28, 0xB3, 0x02, 0xF0, 0x01, 0xE8,
		0x00, 0xCF, 0x00, 0xE6, 0x23, 0xA4 पूर्ण;
	u8 b10_b6[3];
	u32 अगरfreq, अगरhz;

	अगर (bandwidth != 6000000 &&
			bandwidth != 7000000 &&
			bandwidth != 8000000) अणु
		dev_info(&priv->i2c->dev, "%s(): unsupported bandwidth %d. Forcing 8Mhz!\n",
				__func__, bandwidth);
		bandwidth = 8000000;
	पूर्ण

	dev_dbg(&priv->i2c->dev, "%s() bw=%d\n", __func__, bandwidth);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	चयन (bandwidth) अणु
	हाल 8000000:
	हाल 7000000:
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(
				priv, I2C_SLVT, 0xa6,
				bw7_8mhz_b10_a6, माप(bw7_8mhz_b10_a6));
		अगरhz = cxd2841er_get_अगर_hz(priv, 4900000);
		अगरfreq = cxd2841er_calc_अगरfreq(अगरhz);
		अवरोध;
	हाल 6000000:
		अगर (priv->flags & CXD2841ER_ASCOT)
			cxd2841er_ग_लिखो_regs(
				priv, I2C_SLVT, 0xa6,
				bw6mhz_b10_a6, माप(bw6mhz_b10_a6));
		अगरhz = cxd2841er_get_अगर_hz(priv, 3700000);
		अगरfreq = cxd2841er_calc_अगरfreq(अगरhz);
		अवरोध;
	शेष:
		dev_err(&priv->i2c->dev, "%s(): unsupported bandwidth %d\n",
			__func__, bandwidth);
		वापस -EINVAL;
	पूर्ण
	/* <IF freq setting> */
	b10_b6[0] = (u8) ((अगरfreq >> 16) & 0xff);
	b10_b6[1] = (u8)((अगरfreq >> 8) & 0xff);
	b10_b6[2] = (u8)(अगरfreq & 0xff);
	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xb6, b10_b6, माप(b10_b6));
	/* Set SLV-T Bank : 0x11 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x11);
	चयन (bandwidth) अणु
	हाल 8000000:
	हाल 7000000:
		cxd2841er_set_reg_bits(
			priv, I2C_SLVT, 0xa3, 0x00, 0x1f);
		अवरोध;
	हाल 6000000:
		cxd2841er_set_reg_bits(
			priv, I2C_SLVT, 0xa3, 0x14, 0x1f);
		अवरोध;
	पूर्ण
	/* Set SLV-T Bank : 0x40 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x40);
	चयन (bandwidth) अणु
	हाल 8000000:
		cxd2841er_set_reg_bits(
			priv, I2C_SLVT, 0x26, 0x0b, 0x0f);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT,  0x27, 0x3e);
		अवरोध;
	हाल 7000000:
		cxd2841er_set_reg_bits(
			priv, I2C_SLVT, 0x26, 0x09, 0x0f);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT,  0x27, 0xd6);
		अवरोध;
	हाल 6000000:
		cxd2841er_set_reg_bits(
			priv, I2C_SLVT, 0x26, 0x08, 0x0f);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT,  0x27, 0x6e);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_sleep_tc_to_active_t(काष्ठा cxd2841er_priv *priv,
					  u32 bandwidth)
अणु
	u8 data[2] = अणु 0x09, 0x54 पूर्ण;
	u8 data24m[3] = अणु0xDC, 0x6C, 0x00पूर्ण;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	cxd2841er_set_ts_घड़ी_mode(priv, SYS_DVBT);
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* Set demod mode */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x17, 0x01);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Enable demod घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2c, 0x01);
	/* Disable RF level monitor */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2f, 0x00);
	/* Enable ADC घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x30, 0x00);
	/* Enable ADC 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x41, 0x1a);
	/* Enable ADC 2 & 3 */
	अगर (priv->xtal == SONY_XTAL_41000) अणु
		data[0] = 0x0A;
		data[1] = 0xD4;
	पूर्ण
	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x43, data, 2);
	/* Enable ADC 4 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x18, 0x00);
	/* Set SLV-T Bank : 0x10 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	/* IFAGC gain settings */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xd2, 0x0c, 0x1f);
	/* Set SLV-T Bank : 0x11 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x11);
	/* BBAGC TARGET level setting */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x6a, 0x50);
	/* Set SLV-T Bank : 0x10 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	/* ASCOT setting */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xa5,
		((priv->flags & CXD2841ER_ASCOT) ? 0x01 : 0x00), 0x01);
	/* Set SLV-T Bank : 0x18 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x18);
	/* Pre-RS BER monitor setting */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x36, 0x40, 0x07);
	/* FEC Auto Recovery setting */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x30, 0x01, 0x01);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x31, 0x01, 0x01);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* TSIF setting */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xce, 0x01, 0x01);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xcf, 0x01, 0x01);

	अगर (priv->xtal == SONY_XTAL_24000) अणु
		/* Set SLV-T Bank : 0x10 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xBF, 0x60);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x18);
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x24, data24m, 3);
	पूर्ण

	cxd2841er_sleep_tc_to_active_t_band(priv, bandwidth);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Disable HiZ Setting 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x80, 0x28);
	/* Disable HiZ Setting 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x81, 0x00);
	priv->state = STATE_ACTIVE_TC;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_sleep_tc_to_active_t2(काष्ठा cxd2841er_priv *priv,
					   u32 bandwidth)
अणु
	u8 data[MAX_WRITE_REGSIZE];

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	cxd2841er_set_ts_घड़ी_mode(priv, SYS_DVBT2);
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* Set demod mode */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x17, 0x02);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Enable demod घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2c, 0x01);
	/* Disable RF level monitor */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x59, 0x00);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2f, 0x00);
	/* Enable ADC घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x30, 0x00);
	/* Enable ADC 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x41, 0x1a);

	अगर (priv->xtal == SONY_XTAL_41000) अणु
		data[0] = 0x0A;
		data[1] = 0xD4;
	पूर्ण अन्यथा अणु
		data[0] = 0x09;
		data[1] = 0x54;
	पूर्ण

	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x43, data, 2);
	/* Enable ADC 4 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x18, 0x00);
	/* Set SLV-T Bank : 0x10 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	/* IFAGC gain settings */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xd2, 0x0c, 0x1f);
	/* Set SLV-T Bank : 0x11 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x11);
	/* BBAGC TARGET level setting */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x6a, 0x50);
	/* Set SLV-T Bank : 0x10 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	/* ASCOT setting */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xa5,
		((priv->flags & CXD2841ER_ASCOT) ? 0x01 : 0x00), 0x01);
	/* Set SLV-T Bank : 0x20 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x20);
	/* Acquisition optimization setting */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x8b, 0x3c);
	/* Set SLV-T Bank : 0x2b */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x2b);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x76, 0x20, 0x70);
	/* Set SLV-T Bank : 0x23 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x23);
	/* L1 Control setting */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xE6, 0x00, 0x03);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* TSIF setting */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xce, 0x01, 0x01);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xcf, 0x01, 0x01);
	/* DVB-T2 initial setting */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x13);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x83, 0x10);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x86, 0x34);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x9e, 0x09, 0x0f);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x9f, 0xd8);
	/* Set SLV-T Bank : 0x2a */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x2a);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x38, 0x04, 0x0f);
	/* Set SLV-T Bank : 0x2b */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x2b);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x11, 0x20, 0x3f);

	/* 24MHz Xtal setting */
	अगर (priv->xtal == SONY_XTAL_24000) अणु
		/* Set SLV-T Bank : 0x11 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x11);
		data[0] = 0xEB;
		data[1] = 0x03;
		data[2] = 0x3B;
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x33, data, 3);

		/* Set SLV-T Bank : 0x20 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x20);
		data[0] = 0x5E;
		data[1] = 0x5E;
		data[2] = 0x47;
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x95, data, 3);

		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x99, 0x18);

		data[0] = 0x3F;
		data[1] = 0xFF;
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xD9, data, 2);

		/* Set SLV-T Bank : 0x24 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x24);
		data[0] = 0x0B;
		data[1] = 0x72;
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x34, data, 2);

		data[0] = 0x93;
		data[1] = 0xF3;
		data[2] = 0x00;
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xD2, data, 3);

		data[0] = 0x05;
		data[1] = 0xB8;
		data[2] = 0xD8;
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xDD, data, 3);

		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xE0, 0x00);

		/* Set SLV-T Bank : 0x25 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x25);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xED, 0x60);

		/* Set SLV-T Bank : 0x27 */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x27);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xFA, 0x34);

		/* Set SLV-T Bank : 0x2B */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x2B);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x4B, 0x2F);
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x9E, 0x0E);

		/* Set SLV-T Bank : 0x2D */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x2D);
		data[0] = 0x89;
		data[1] = 0x89;
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x24, data, 2);

		/* Set SLV-T Bank : 0x5E */
		cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x5E);
		data[0] = 0x24;
		data[1] = 0x95;
		cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x8C, data, 2);
	पूर्ण

	cxd2841er_sleep_tc_to_active_t2_band(priv, bandwidth);

	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Disable HiZ Setting 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x80, 0x28);
	/* Disable HiZ Setting 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x81, 0x00);
	priv->state = STATE_ACTIVE_TC;
	वापस 0;
पूर्ण

/* ISDB-Tb part */
अटल पूर्णांक cxd2841er_sleep_tc_to_active_i(काष्ठा cxd2841er_priv *priv,
		u32 bandwidth)
अणु
	u8 data[2] = अणु 0x09, 0x54 पूर्ण;
	u8 data24m[2] = अणु0x60, 0x00पूर्ण;
	u8 data24m2[3] = अणु0xB7, 0x1B, 0x00पूर्ण;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	cxd2841er_set_ts_घड़ी_mode(priv, SYS_DVBT);
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* Set demod mode */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x17, 0x06);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Enable demod घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2c, 0x01);
	/* Enable RF level monitor */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2f, 0x01);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x59, 0x01);
	/* Enable ADC घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x30, 0x00);
	/* Enable ADC 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x41, 0x1a);
	/* xtal freq 20.5MHz or 24M */
	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x43, data, 2);
	/* Enable ADC 4 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x18, 0x00);
	/* ASCOT setting */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xa5,
		((priv->flags & CXD2841ER_ASCOT) ? 0x01 : 0x00), 0x01);
	/* FEC Auto Recovery setting */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x30, 0x01, 0x01);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x31, 0x00, 0x01);
	/* ISDB-T initial setting */
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xce, 0x00, 0x01);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xcf, 0x00, 0x01);
	/* Set SLV-T Bank : 0x10 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x69, 0x04, 0x07);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x6B, 0x03, 0x07);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x9D, 0x50, 0xFF);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xD3, 0x06, 0x1F);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xED, 0x00, 0x01);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xE2, 0xCE, 0x80);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xF2, 0x13, 0x10);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xDE, 0x2E, 0x3F);
	/* Set SLV-T Bank : 0x15 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x15);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xDE, 0x02, 0x03);
	/* Set SLV-T Bank : 0x1E */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x1E);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x73, 0x68, 0xFF);
	/* Set SLV-T Bank : 0x63 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x63);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0x81, 0x00, 0x01);

	/* क्रम xtal 24MHz */
	/* Set SLV-T Bank : 0x10 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xBF, data24m, 2);
	/* Set SLV-T Bank : 0x60 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x60);
	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0xA8, data24m2, 3);

	cxd2841er_sleep_tc_to_active_i_band(priv, bandwidth);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Disable HiZ Setting 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x80, 0x28);
	/* Disable HiZ Setting 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x81, 0x00);
	priv->state = STATE_ACTIVE_TC;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_sleep_tc_to_active_c(काष्ठा cxd2841er_priv *priv,
					  u32 bandwidth)
अणु
	u8 data[2] = अणु 0x09, 0x54 पूर्ण;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	cxd2841er_set_ts_घड़ी_mode(priv, SYS_DVBC_ANNEX_A);
	/* Set SLV-X Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x00, 0x00);
	/* Set demod mode */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x17, 0x04);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Enable demod घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2c, 0x01);
	/* Disable RF level monitor */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x59, 0x00);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x2f, 0x00);
	/* Enable ADC घड़ी */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x30, 0x00);
	/* Enable ADC 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x41, 0x1a);
	/* xtal freq 20.5MHz */
	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x43, data, 2);
	/* Enable ADC 4 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVX, 0x18, 0x00);
	/* Set SLV-T Bank : 0x10 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	/* IFAGC gain settings */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xd2, 0x09, 0x1f);
	/* Set SLV-T Bank : 0x11 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x11);
	/* BBAGC TARGET level setting */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x6a, 0x48);
	/* Set SLV-T Bank : 0x10 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	/* ASCOT setting */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xa5,
		((priv->flags & CXD2841ER_ASCOT) ? 0x01 : 0x00), 0x01);
	/* Set SLV-T Bank : 0x40 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x40);
	/* Demod setting */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xc3, 0x00, 0x04);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* TSIF setting */
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xce, 0x01, 0x01);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xcf, 0x01, 0x01);

	cxd2841er_sleep_tc_to_active_c_band(priv, bandwidth);
	/* Set SLV-T Bank : 0x00 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	/* Disable HiZ Setting 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x80, 0x28);
	/* Disable HiZ Setting 2 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x81, 0x00);
	priv->state = STATE_ACTIVE_TC;
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_get_frontend(काष्ठा dvb_frontend *fe,
				  काष्ठा dtv_frontend_properties *p)
अणु
	क्रमागत fe_status status = 0;
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state == STATE_ACTIVE_S)
		cxd2841er_पढ़ो_status_s(fe, &status);
	अन्यथा अगर (priv->state == STATE_ACTIVE_TC)
		cxd2841er_पढ़ो_status_tc(fe, &status);

	अगर (priv->state == STATE_ACTIVE_TC || priv->state == STATE_ACTIVE_S)
		cxd2841er_पढ़ो_संकेत_strength(fe);
	अन्यथा
		p->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	अगर (status & FE_HAS_LOCK) अणु
		अगर (priv->stats_समय &&
		    (!समय_after(jअगरfies, priv->stats_समय)))
			वापस 0;

		/* Prevent retrieving stats faster than once per second */
		priv->stats_समय = jअगरfies + msecs_to_jअगरfies(1000);

		cxd2841er_पढ़ो_snr(fe);
		cxd2841er_पढ़ो_ucblocks(fe);
		cxd2841er_पढ़ो_ber(fe);
	पूर्ण अन्यथा अणु
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_set_frontend_s(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret = 0, i, समयout, carr_offset;
	क्रमागत fe_status status;
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 symbol_rate = p->symbol_rate/1000;

	dev_dbg(&priv->i2c->dev, "%s(): %s frequency=%d symbol_rate=%d xtal=%d\n",
		__func__,
		(p->delivery_प्रणाली == SYS_DVBS ? "DVB-S" : "DVB-S2"),
		 p->frequency, symbol_rate, priv->xtal);

	अगर (priv->flags & CXD2841ER_EARLY_TUNE)
		cxd2841er_tuner_set(fe);

	चयन (priv->state) अणु
	हाल STATE_SLEEP_S:
		ret = cxd2841er_sleep_s_to_active_s(
			priv, p->delivery_प्रणाली, symbol_rate);
		अवरोध;
	हाल STATE_ACTIVE_S:
		ret = cxd2841er_retune_active(priv, p);
		अवरोध;
	शेष:
		dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण
	अगर (ret) अणु
		dev_dbg(&priv->i2c->dev, "%s(): tune failed\n", __func__);
		जाओ करोne;
	पूर्ण

	अगर (!(priv->flags & CXD2841ER_EARLY_TUNE))
		cxd2841er_tuner_set(fe);

	cxd2841er_tune_करोne(priv);
	समयout = DIV_ROUND_UP(3000000, symbol_rate) + 150;

	i = 0;
	करो अणु
		usleep_range(CXD2841ER_DVBS_POLLING_INVL*1000,
			(CXD2841ER_DVBS_POLLING_INVL + 2) * 1000);
		cxd2841er_पढ़ो_status_s(fe, &status);
		अगर (status & FE_HAS_LOCK)
			अवरोध;
		i++;
	पूर्ण जबतक (i < समयout / CXD2841ER_DVBS_POLLING_INVL);

	अगर (status & FE_HAS_LOCK) अणु
		अगर (cxd2841er_get_carrier_offset_s_s2(
				priv, &carr_offset)) अणु
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		dev_dbg(&priv->i2c->dev, "%s(): carrier_offset=%d\n",
			__func__, carr_offset);
	पूर्ण
करोne:
	/* Reset stats */
	p->strength.stat[0].scale = FE_SCALE_RELATIVE;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	/* Reset the रुको क्रम jअगरfies logic */
	priv->stats_समय = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2841er_set_frontend_tc(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret = 0, समयout;
	क्रमागत fe_status status;
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	dev_dbg(&priv->i2c->dev, "%s() delivery_system=%d bandwidth_hz=%d\n",
		 __func__, p->delivery_प्रणाली, p->bandwidth_hz);

	अगर (priv->flags & CXD2841ER_EARLY_TUNE)
		cxd2841er_tuner_set(fe);

	/* deconfigure/put demod to sleep on delsys चयन अगर active */
	अगर (priv->state == STATE_ACTIVE_TC &&
	    priv->प्रणाली != p->delivery_प्रणाली) अणु
		dev_dbg(&priv->i2c->dev, "%s(): old_delsys=%d, new_delsys=%d -> sleep\n",
			 __func__, priv->प्रणाली, p->delivery_प्रणाली);
		cxd2841er_sleep_tc(fe);
	पूर्ण

	अगर (p->delivery_प्रणाली == SYS_DVBT) अणु
		priv->प्रणाली = SYS_DVBT;
		चयन (priv->state) अणु
		हाल STATE_SLEEP_TC:
			ret = cxd2841er_sleep_tc_to_active_t(
				priv, p->bandwidth_hz);
			अवरोध;
		हाल STATE_ACTIVE_TC:
			ret = cxd2841er_retune_active(priv, p);
			अवरोध;
		शेष:
			dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
				__func__, priv->state);
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (p->delivery_प्रणाली == SYS_DVBT2) अणु
		priv->प्रणाली = SYS_DVBT2;
		cxd2841er_dvbt2_set_plp_config(priv,
			(पूर्णांक)(p->stream_id > 255), p->stream_id);
		cxd2841er_dvbt2_set_profile(priv, DVBT2_PROखाता_BASE);
		चयन (priv->state) अणु
		हाल STATE_SLEEP_TC:
			ret = cxd2841er_sleep_tc_to_active_t2(priv,
				p->bandwidth_hz);
			अवरोध;
		हाल STATE_ACTIVE_TC:
			ret = cxd2841er_retune_active(priv, p);
			अवरोध;
		शेष:
			dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
				__func__, priv->state);
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (p->delivery_प्रणाली == SYS_ISDBT) अणु
		priv->प्रणाली = SYS_ISDBT;
		चयन (priv->state) अणु
		हाल STATE_SLEEP_TC:
			ret = cxd2841er_sleep_tc_to_active_i(
					priv, p->bandwidth_hz);
			अवरोध;
		हाल STATE_ACTIVE_TC:
			ret = cxd2841er_retune_active(priv, p);
			अवरोध;
		शेष:
			dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
					__func__, priv->state);
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (p->delivery_प्रणाली == SYS_DVBC_ANNEX_A ||
			p->delivery_प्रणाली == SYS_DVBC_ANNEX_C) अणु
		priv->प्रणाली = SYS_DVBC_ANNEX_A;
		/* correct bandwidth */
		अगर (p->bandwidth_hz != 6000000 &&
				p->bandwidth_hz != 7000000 &&
				p->bandwidth_hz != 8000000) अणु
			p->bandwidth_hz = 8000000;
			dev_dbg(&priv->i2c->dev, "%s(): forcing bandwidth to %d\n",
					__func__, p->bandwidth_hz);
		पूर्ण

		चयन (priv->state) अणु
		हाल STATE_SLEEP_TC:
			ret = cxd2841er_sleep_tc_to_active_c(
				priv, p->bandwidth_hz);
			अवरोध;
		हाल STATE_ACTIVE_TC:
			ret = cxd2841er_retune_active(priv, p);
			अवरोध;
		शेष:
			dev_dbg(&priv->i2c->dev, "%s(): invalid state %d\n",
				__func__, priv->state);
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(&priv->i2c->dev,
			"%s(): invalid delivery system %d\n",
			__func__, p->delivery_प्रणाली);
		ret = -EINVAL;
	पूर्ण
	अगर (ret)
		जाओ करोne;

	अगर (!(priv->flags & CXD2841ER_EARLY_TUNE))
		cxd2841er_tuner_set(fe);

	cxd2841er_tune_करोne(priv);

	अगर (priv->flags & CXD2841ER_NO_WAIT_LOCK)
		जाओ करोne;

	समयout = 2500;
	जबतक (समयout > 0) अणु
		ret = cxd2841er_पढ़ो_status_tc(fe, &status);
		अगर (ret)
			जाओ करोne;
		अगर (status & FE_HAS_LOCK)
			अवरोध;
		msleep(20);
		समयout -= 20;
	पूर्ण
	अगर (समयout < 0)
		dev_dbg(&priv->i2c->dev,
			"%s(): LOCK wait timeout\n", __func__);
करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक cxd2841er_tune_s(काष्ठा dvb_frontend *fe,
			    bool re_tune,
			    अचिन्हित पूर्णांक mode_flags,
			    अचिन्हित पूर्णांक *delay,
			    क्रमागत fe_status *status)
अणु
	पूर्णांक ret, carrier_offset;
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	dev_dbg(&priv->i2c->dev, "%s() re_tune=%d\n", __func__, re_tune);
	अगर (re_tune) अणु
		ret = cxd2841er_set_frontend_s(fe);
		अगर (ret)
			वापस ret;
		cxd2841er_पढ़ो_status_s(fe, status);
		अगर (*status & FE_HAS_LOCK) अणु
			अगर (cxd2841er_get_carrier_offset_s_s2(
					priv, &carrier_offset))
				वापस -EINVAL;
			p->frequency += carrier_offset;
			ret = cxd2841er_set_frontend_s(fe);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	*delay = HZ / 5;
	वापस cxd2841er_पढ़ो_status_s(fe, status);
पूर्ण

अटल पूर्णांक cxd2841er_tune_tc(काष्ठा dvb_frontend *fe,
			     bool re_tune,
			     अचिन्हित पूर्णांक mode_flags,
			     अचिन्हित पूर्णांक *delay,
			     क्रमागत fe_status *status)
अणु
	पूर्णांक ret, carrier_offset;
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	dev_dbg(&priv->i2c->dev, "%s(): re_tune %d bandwidth=%d\n", __func__,
			re_tune, p->bandwidth_hz);
	अगर (re_tune) अणु
		ret = cxd2841er_set_frontend_tc(fe);
		अगर (ret)
			वापस ret;
		cxd2841er_पढ़ो_status_tc(fe, status);
		अगर (*status & FE_HAS_LOCK) अणु
			चयन (priv->प्रणाली) अणु
			हाल SYS_ISDBT:
				ret = cxd2841er_get_carrier_offset_i(
						priv, p->bandwidth_hz,
						&carrier_offset);
				अगर (ret)
					वापस ret;
				अवरोध;
			हाल SYS_DVBT:
				ret = cxd2841er_get_carrier_offset_t(
					priv, p->bandwidth_hz,
					&carrier_offset);
				अगर (ret)
					वापस ret;
				अवरोध;
			हाल SYS_DVBT2:
				ret = cxd2841er_get_carrier_offset_t2(
					priv, p->bandwidth_hz,
					&carrier_offset);
				अगर (ret)
					वापस ret;
				अवरोध;
			हाल SYS_DVBC_ANNEX_A:
				ret = cxd2841er_get_carrier_offset_c(
					priv, &carrier_offset);
				अगर (ret)
					वापस ret;
				अवरोध;
			शेष:
				dev_dbg(&priv->i2c->dev,
					"%s(): invalid delivery system %d\n",
					__func__, priv->प्रणाली);
				वापस -EINVAL;
			पूर्ण
			dev_dbg(&priv->i2c->dev, "%s(): carrier offset %d\n",
				__func__, carrier_offset);
			p->frequency += carrier_offset;
			ret = cxd2841er_set_frontend_tc(fe);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	*delay = HZ / 5;
	वापस cxd2841er_पढ़ो_status_tc(fe, status);
पूर्ण

अटल पूर्णांक cxd2841er_sleep_s(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	cxd2841er_active_s_to_sleep_s(fe->demodulator_priv);
	cxd2841er_sleep_s_to_shutकरोwn(fe->demodulator_priv);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_sleep_tc(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);

	अगर (priv->state == STATE_ACTIVE_TC) अणु
		चयन (priv->प्रणाली) अणु
		हाल SYS_DVBT:
			cxd2841er_active_t_to_sleep_tc(priv);
			अवरोध;
		हाल SYS_DVBT2:
			cxd2841er_active_t2_to_sleep_tc(priv);
			अवरोध;
		हाल SYS_ISDBT:
			cxd2841er_active_i_to_sleep_tc(priv);
			अवरोध;
		हाल SYS_DVBC_ANNEX_A:
			cxd2841er_active_c_to_sleep_tc(priv);
			अवरोध;
		शेष:
			dev_warn(&priv->i2c->dev,
				"%s(): unknown delivery system %d\n",
				__func__, priv->प्रणाली);
		पूर्ण
	पूर्ण
	अगर (priv->state != STATE_SLEEP_TC) अणु
		dev_err(&priv->i2c->dev, "%s(): invalid state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_shutकरोwn_tc(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);

	अगर (!cxd2841er_sleep_tc(fe))
		cxd2841er_sleep_tc_to_shutकरोwn(priv);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_send_burst(काष्ठा dvb_frontend *fe,
				क्रमागत fe_sec_mini_cmd burst)
अणु
	u8 data;
	काष्ठा cxd2841er_priv *priv  = fe->demodulator_priv;

	dev_dbg(&priv->i2c->dev, "%s(): burst mode %s\n", __func__,
		(burst == SEC_MINI_A ? "A" : "B"));
	अगर (priv->state != STATE_SLEEP_S &&
			priv->state != STATE_ACTIVE_S) अणु
		dev_err(&priv->i2c->dev, "%s(): invalid demod state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	data = (burst == SEC_MINI_A ? 0 : 1);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xbb);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x34, 0x01);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x35, data);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_set_tone(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_tone_mode tone)
अणु
	u8 data;
	काष्ठा cxd2841er_priv *priv  = fe->demodulator_priv;

	dev_dbg(&priv->i2c->dev, "%s(): tone %s\n", __func__,
		(tone == SEC_TONE_ON ? "On" : "Off"));
	अगर (priv->state != STATE_SLEEP_S &&
			priv->state != STATE_ACTIVE_S) अणु
		dev_err(&priv->i2c->dev, "%s(): invalid demod state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	data = (tone == SEC_TONE_ON ? 1 : 0);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xbb);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x36, data);
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_send_diseqc_msg(काष्ठा dvb_frontend *fe,
				     काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	पूर्णांक i;
	u8 data[12];
	काष्ठा cxd2841er_priv *priv  = fe->demodulator_priv;

	अगर (priv->state != STATE_SLEEP_S &&
			priv->state != STATE_ACTIVE_S) अणु
		dev_err(&priv->i2c->dev, "%s(): invalid demod state %d\n",
			__func__, priv->state);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(&priv->i2c->dev,
		"%s(): cmd->len %d\n", __func__, cmd->msg_len);
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xbb);
	/* DiDEqC enable */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x33, 0x01);
	/* cmd1 length & data */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x3d, cmd->msg_len);
	स_रखो(data, 0, माप(data));
	क्रम (i = 0; i < cmd->msg_len && i < माप(data); i++)
		data[i] = cmd->msg[i];
	cxd2841er_ग_लिखो_regs(priv, I2C_SLVT, 0x3e, data, माप(data));
	/* repeat count क्रम cmd1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x37, 1);
	/* repeat count क्रम cmd2: always 0 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x38, 0);
	/* start transmit */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x32, 0x01);
	/* रुको क्रम 1 sec समयout */
	क्रम (i = 0; i < 50; i++) अणु
		cxd2841er_पढ़ो_reg(priv, I2C_SLVT, 0x10, data);
		अगर (!data[0]) अणु
			dev_dbg(&priv->i2c->dev,
				"%s(): DiSEqC cmd has been sent\n", __func__);
			वापस 0;
		पूर्ण
		msleep(20);
	पूर्ण
	dev_dbg(&priv->i2c->dev,
		"%s(): DiSEqC cmd transmit timeout\n", __func__);
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम cxd2841er_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2841er_priv *priv  = fe->demodulator_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक cxd2841er_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;

	dev_dbg(&priv->i2c->dev, "%s(): enable=%d\n", __func__, enable);
	cxd2841er_set_reg_bits(
		priv, I2C_SLVX, 0x8, (enable ? 0x01 : 0x00), 0x01);
	वापस 0;
पूर्ण

अटल क्रमागत dvbfe_algo cxd2841er_get_algo(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	वापस DVBFE_ALGO_HW;
पूर्ण

अटल व्योम cxd2841er_init_stats(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	p->strength.len = 1;
	p->strength.stat[0].scale = FE_SCALE_RELATIVE;
	p->cnr.len = 1;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_error.len = 1;
	p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_error.len = 1;
	p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_count.len = 1;
	p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
पूर्ण


अटल पूर्णांक cxd2841er_init_s(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;

	/* sanity. क्रमce demod to SHUTDOWN state */
	अगर (priv->state == STATE_SLEEP_S) अणु
		dev_dbg(&priv->i2c->dev, "%s() forcing sleep->shutdown\n",
				__func__);
		cxd2841er_sleep_s_to_shutकरोwn(priv);
	पूर्ण अन्यथा अगर (priv->state == STATE_ACTIVE_S) अणु
		dev_dbg(&priv->i2c->dev, "%s() forcing active->sleep->shutdown\n",
				__func__);
		cxd2841er_active_s_to_sleep_s(priv);
		cxd2841er_sleep_s_to_shutकरोwn(priv);
	पूर्ण

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	cxd2841er_shutकरोwn_to_sleep_s(priv);
	/* SONY_DEMOD_CONFIG_SAT_IFAGCNEG set to 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0xa0);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xb9, 0x01, 0x01);

	cxd2841er_init_stats(fe);

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2841er_init_tc(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2841er_priv *priv = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	dev_dbg(&priv->i2c->dev, "%s() bandwidth_hz=%d\n",
			__func__, p->bandwidth_hz);
	cxd2841er_shutकरोwn_to_sleep_tc(priv);
	/* SONY_DEMOD_CONFIG_IFAGCNEG = 1 (0 क्रम NO_AGCNEG */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x10);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xcb,
		((priv->flags & CXD2841ER_NO_AGCNEG) ? 0x00 : 0x40), 0x40);
	/* SONY_DEMOD_CONFIG_IFAGC_ADC_FS = 0 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0xcd, 0x50);
	/* SONY_DEMOD_CONFIG_PARALLEL_SEL = 1 */
	cxd2841er_ग_लिखो_reg(priv, I2C_SLVT, 0x00, 0x00);
	cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xc4,
		((priv->flags & CXD2841ER_TS_SERIAL) ? 0x80 : 0x00), 0x80);

	/* clear TSCFG bits 3+4 */
	अगर (priv->flags & CXD2841ER_TSBITS)
		cxd2841er_set_reg_bits(priv, I2C_SLVT, 0xc4, 0x00, 0x18);

	cxd2841er_init_stats(fe);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cxd2841er_dvbs_s2_ops;
अटल काष्ठा dvb_frontend_ops cxd2841er_t_c_ops;

अटल काष्ठा dvb_frontend *cxd2841er_attach(काष्ठा cxd2841er_config *cfg,
					     काष्ठा i2c_adapter *i2c,
					     u8 प्रणाली)
अणु
	u8 chip_id = 0;
	स्थिर अक्षर *type;
	स्थिर अक्षर *name;
	काष्ठा cxd2841er_priv *priv = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	priv = kzalloc(माप(काष्ठा cxd2841er_priv), GFP_KERNEL);
	अगर (!priv)
		वापस शून्य;
	priv->i2c = i2c;
	priv->config = cfg;
	priv->i2c_addr_slvx = (cfg->i2c_addr + 4) >> 1;
	priv->i2c_addr_slvt = (cfg->i2c_addr) >> 1;
	priv->xtal = cfg->xtal;
	priv->flags = cfg->flags;
	priv->frontend.demodulator_priv = priv;
	dev_info(&priv->i2c->dev,
		"%s(): I2C adapter %p SLVX addr %x SLVT addr %x\n",
		__func__, priv->i2c,
		priv->i2c_addr_slvx, priv->i2c_addr_slvt);
	chip_id = cxd2841er_chip_id(priv);
	चयन (chip_id) अणु
	हाल CXD2837ER_CHIP_ID:
		snम_लिखो(cxd2841er_t_c_ops.info.name, 128,
				"Sony CXD2837ER DVB-T/T2/C demodulator");
		name = "CXD2837ER";
		type = "C/T/T2";
		अवरोध;
	हाल CXD2838ER_CHIP_ID:
		snम_लिखो(cxd2841er_t_c_ops.info.name, 128,
				"Sony CXD2838ER ISDB-T demodulator");
		cxd2841er_t_c_ops.delsys[0] = SYS_ISDBT;
		cxd2841er_t_c_ops.delsys[1] = SYS_UNDEFINED;
		cxd2841er_t_c_ops.delsys[2] = SYS_UNDEFINED;
		name = "CXD2838ER";
		type = "ISDB-T";
		अवरोध;
	हाल CXD2841ER_CHIP_ID:
		snम_लिखो(cxd2841er_t_c_ops.info.name, 128,
				"Sony CXD2841ER DVB-T/T2/C demodulator");
		name = "CXD2841ER";
		type = "T/T2/C/ISDB-T";
		अवरोध;
	हाल CXD2843ER_CHIP_ID:
		snम_लिखो(cxd2841er_t_c_ops.info.name, 128,
				"Sony CXD2843ER DVB-T/T2/C/C2 demodulator");
		name = "CXD2843ER";
		type = "C/C2/T/T2";
		अवरोध;
	हाल CXD2854ER_CHIP_ID:
		snम_लिखो(cxd2841er_t_c_ops.info.name, 128,
				"Sony CXD2854ER DVB-T/T2/C and ISDB-T demodulator");
		cxd2841er_t_c_ops.delsys[3] = SYS_ISDBT;
		name = "CXD2854ER";
		type = "C/C2/T/T2/ISDB-T";
		अवरोध;
	शेष:
		dev_err(&priv->i2c->dev, "%s(): invalid chip ID 0x%02x\n",
				__func__, chip_id);
		priv->frontend.demodulator_priv = शून्य;
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	/* create dvb_frontend */
	अगर (प्रणाली == SYS_DVBS) अणु
		स_नकल(&priv->frontend.ops,
			&cxd2841er_dvbs_s2_ops,
			माप(काष्ठा dvb_frontend_ops));
		type = "S/S2";
	पूर्ण अन्यथा अणु
		स_नकल(&priv->frontend.ops,
			&cxd2841er_t_c_ops,
			माप(काष्ठा dvb_frontend_ops));
	पूर्ण

	dev_info(&priv->i2c->dev,
		"%s(): attaching %s DVB-%s frontend\n",
		__func__, name, type);
	dev_info(&priv->i2c->dev, "%s(): chip ID 0x%02x OK.\n",
		__func__, chip_id);
	वापस &priv->frontend;
पूर्ण

काष्ठा dvb_frontend *cxd2841er_attach_s(काष्ठा cxd2841er_config *cfg,
					काष्ठा i2c_adapter *i2c)
अणु
	वापस cxd2841er_attach(cfg, i2c, SYS_DVBS);
पूर्ण
EXPORT_SYMBOL(cxd2841er_attach_s);

काष्ठा dvb_frontend *cxd2841er_attach_t_c(काष्ठा cxd2841er_config *cfg,
					काष्ठा i2c_adapter *i2c)
अणु
	वापस cxd2841er_attach(cfg, i2c, 0);
पूर्ण
EXPORT_SYMBOL(cxd2841er_attach_t_c);

अटल स्थिर काष्ठा dvb_frontend_ops cxd2841er_dvbs_s2_ops = अणु
	.delsys = अणु SYS_DVBS, SYS_DVBS2 पूर्ण,
	.info = अणु
		.name		= "Sony CXD2841ER DVB-S/S2 demodulator",
		.frequency_min_hz	=  500 * MHz,
		.frequency_max_hz	= 2500 * MHz,
		.symbol_rate_min = 1000000,
		.symbol_rate_max = 45000000,
		.symbol_rate_tolerance = 500,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK,
	पूर्ण,
	.init = cxd2841er_init_s,
	.sleep = cxd2841er_sleep_s,
	.release = cxd2841er_release,
	.set_frontend = cxd2841er_set_frontend_s,
	.get_frontend = cxd2841er_get_frontend,
	.पढ़ो_status = cxd2841er_पढ़ो_status_s,
	.i2c_gate_ctrl = cxd2841er_i2c_gate_ctrl,
	.get_frontend_algo = cxd2841er_get_algo,
	.set_tone = cxd2841er_set_tone,
	.diseqc_send_burst = cxd2841er_send_burst,
	.diseqc_send_master_cmd = cxd2841er_send_diseqc_msg,
	.tune = cxd2841er_tune_s
पूर्ण;

अटल काष्ठा dvb_frontend_ops cxd2841er_t_c_ops = अणु
	.delsys = अणु SYS_DVBT, SYS_DVBT2, SYS_DVBC_ANNEX_A पूर्ण,
	.info = अणु
		.name	= "", /* will set in attach function */
		.caps = FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_32 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO |
			FE_CAN_MUTE_TS |
			FE_CAN_2G_MODULATION,
		.frequency_min_hz =   42 * MHz,
		.frequency_max_hz = 1002 * MHz,
		.symbol_rate_min = 870000,
		.symbol_rate_max = 11700000
	पूर्ण,
	.init = cxd2841er_init_tc,
	.sleep = cxd2841er_shutकरोwn_tc,
	.release = cxd2841er_release,
	.set_frontend = cxd2841er_set_frontend_tc,
	.get_frontend = cxd2841er_get_frontend,
	.पढ़ो_status = cxd2841er_पढ़ो_status_tc,
	.tune = cxd2841er_tune_tc,
	.i2c_gate_ctrl = cxd2841er_i2c_gate_ctrl,
	.get_frontend_algo = cxd2841er_get_algo
पूर्ण;

MODULE_DESCRIPTION("Sony CXD2837/38/41/43/54ER DVB-C/C2/T/T2/S/S2 demodulator driver");
MODULE_AUTHOR("Sergey Kozlov <serjk@netup.ru>, Abylay Ospan <aospan@netup.ru>");
MODULE_LICENSE("GPL");
