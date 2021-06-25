<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * descriptions + helper functions क्रम simple dvb plls.
 *
 * (c) 2004 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/idr.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <यंत्र/types.h>

#समावेश "dvb-pll.h"

#घोषणा dprपूर्णांकk(fmt, arg...) \
	prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt), __func__, ##arg)

काष्ठा dvb_pll_priv अणु
	/* pll number */
	पूर्णांक nr;

	/* i2c details */
	पूर्णांक pll_i2c_address;
	काष्ठा i2c_adapter *i2c;

	/* the PLL descriptor */
	स्थिर काष्ठा dvb_pll_desc *pll_desc;

	/* cached frequency/bandwidth */
	u32 frequency;
	u32 bandwidth;
पूर्ण;

#घोषणा DVB_PLL_MAX 64
अटल DEFINE_IDA(pll_ida);

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable verbose debug messages");

अटल अचिन्हित पूर्णांक id[DVB_PLL_MAX] =
	अणु [ 0 ... (DVB_PLL_MAX-1) ] = DVB_PLL_UNDEFINED पूर्ण;
module_param_array(id, पूर्णांक, शून्य, 0644);
MODULE_PARM_DESC(id, "force pll id to use (DEBUG ONLY)");

/* ----------------------------------------------------------- */

काष्ठा dvb_pll_desc अणु
	स्थिर अक्षर *name;
	u32  min;
	u32  max;
	u32  अगरfreq;
	व्योम (*set)(काष्ठा dvb_frontend *fe, u8 *buf);
	u8   *initdata;
	u8   *initdata2;
	u8   *sleepdata;
	पूर्णांक  count;
	काष्ठा अणु
		u32 limit;
		u32 stepsize;
		u8  config;
		u8  cb;
	पूर्ण entries[];
पूर्ण;

/* ----------------------------------------------------------- */
/* descriptions                                                */

अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_thomson_dtt7579 = अणु
	.name  = "Thomson dtt7579",
	.min   = 177 * MHz,
	.max   = 858 * MHz,
	.अगरfreq= 36166667,
	.sleepdata = (u8[])अणु 2, 0xb4, 0x03 पूर्ण,
	.count = 4,
	.entries = अणु
		अणु  443250000, 166667, 0xb4, 0x02 पूर्ण,
		अणु  542000000, 166667, 0xb4, 0x08 पूर्ण,
		अणु  771000000, 166667, 0xbc, 0x08 पूर्ण,
		अणु  999999999, 166667, 0xf4, 0x08 पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम thomson_dtt759x_bw(काष्ठा dvb_frontend *fe, u8 *buf)
अणु
	u32 bw = fe->dtv_property_cache.bandwidth_hz;
	अगर (bw == 7000000)
		buf[3] |= 0x10;
पूर्ण

अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_thomson_dtt759x = अणु
	.name  = "Thomson dtt759x",
	.min   = 177 * MHz,
	.max   = 896 * MHz,
	.set   = thomson_dtt759x_bw,
	.अगरfreq= 36166667,
	.sleepdata = (u8[])अणु 2, 0x84, 0x03 पूर्ण,
	.count = 5,
	.entries = अणु
		अणु  264000000, 166667, 0xb4, 0x02 पूर्ण,
		अणु  470000000, 166667, 0xbc, 0x02 पूर्ण,
		अणु  735000000, 166667, 0xbc, 0x08 पूर्ण,
		अणु  835000000, 166667, 0xf4, 0x08 पूर्ण,
		अणु  999999999, 166667, 0xfc, 0x08 पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम thomson_dtt7520x_bw(काष्ठा dvb_frontend *fe, u8 *buf)
अणु
	u32 bw = fe->dtv_property_cache.bandwidth_hz;
	अगर (bw == 8000000)
		buf[3] ^= 0x10;
पूर्ण

अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_thomson_dtt7520x = अणु
	.name  = "Thomson dtt7520x",
	.min   = 185 * MHz,
	.max   = 900 * MHz,
	.set   = thomson_dtt7520x_bw,
	.अगरfreq = 36166667,
	.count = 7,
	.entries = अणु
		अणु  305000000, 166667, 0xb4, 0x12 पूर्ण,
		अणु  405000000, 166667, 0xbc, 0x12 पूर्ण,
		अणु  445000000, 166667, 0xbc, 0x12 पूर्ण,
		अणु  465000000, 166667, 0xf4, 0x18 पूर्ण,
		अणु  735000000, 166667, 0xfc, 0x18 पूर्ण,
		अणु  835000000, 166667, 0xbc, 0x18 पूर्ण,
		अणु  999999999, 166667, 0xfc, 0x18 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_lg_z201 = अणु
	.name  = "LG z201",
	.min   = 174 * MHz,
	.max   = 862 * MHz,
	.अगरfreq= 36166667,
	.sleepdata = (u8[])अणु 2, 0xbc, 0x03 पूर्ण,
	.count = 5,
	.entries = अणु
		अणु  157500000, 166667, 0xbc, 0x01 पूर्ण,
		अणु  443250000, 166667, 0xbc, 0x02 पूर्ण,
		अणु  542000000, 166667, 0xbc, 0x04 पूर्ण,
		अणु  830000000, 166667, 0xf4, 0x04 पूर्ण,
		अणु  999999999, 166667, 0xfc, 0x04 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_unknown_1 = अणु
	.name  = "unknown 1", /* used by dntv live dvb-t */
	.min   = 174 * MHz,
	.max   = 862 * MHz,
	.अगरfreq= 36166667,
	.count = 9,
	.entries = अणु
		अणु  150000000, 166667, 0xb4, 0x01 पूर्ण,
		अणु  173000000, 166667, 0xbc, 0x01 पूर्ण,
		अणु  250000000, 166667, 0xb4, 0x02 पूर्ण,
		अणु  400000000, 166667, 0xbc, 0x02 पूर्ण,
		अणु  420000000, 166667, 0xf4, 0x02 पूर्ण,
		अणु  470000000, 166667, 0xfc, 0x02 पूर्ण,
		अणु  600000000, 166667, 0xbc, 0x08 पूर्ण,
		अणु  730000000, 166667, 0xf4, 0x08 पूर्ण,
		अणु  999999999, 166667, 0xfc, 0x08 पूर्ण,
	पूर्ण,
पूर्ण;

/* Infineon TUA6010XS
 * used in Thomson Cable Tuner
 */
अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_tua6010xs = अणु
	.name  = "Infineon TUA6010XS",
	.min   = 44250 * kHz,
	.max   = 858 * MHz,
	.अगरfreq= 36125000,
	.count = 3,
	.entries = अणु
		अणु  115750000, 62500, 0x8e, 0x03 पूर्ण,
		अणु  403250000, 62500, 0x8e, 0x06 पूर्ण,
		अणु  999999999, 62500, 0x8e, 0x85 पूर्ण,
	पूर्ण,
पूर्ण;

/* Panasonic env57h1xd5 (some Philips PLL ?) */
अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_env57h1xd5 = अणु
	.name  = "Panasonic ENV57H1XD5",
	.min   = 44250 * kHz,
	.max   = 858 * MHz,
	.अगरfreq= 36125000,
	.count = 4,
	.entries = अणु
		अणु  153000000, 166667, 0xc2, 0x41 पूर्ण,
		अणु  470000000, 166667, 0xc2, 0x42 पूर्ण,
		अणु  526000000, 166667, 0xc2, 0x84 पूर्ण,
		अणु  999999999, 166667, 0xc2, 0xa4 पूर्ण,
	पूर्ण,
पूर्ण;

/* Philips TDA6650/TDA6651
 * used in Panasonic ENV77H11D5
 */
अटल व्योम tda665x_bw(काष्ठा dvb_frontend *fe, u8 *buf)
अणु
	u32 bw = fe->dtv_property_cache.bandwidth_hz;
	अगर (bw == 8000000)
		buf[3] |= 0x08;
पूर्ण

अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_tda665x = अणु
	.name  = "Philips TDA6650/TDA6651",
	.min   = 44250 * kHz,
	.max   = 858 * MHz,
	.set   = tda665x_bw,
	.अगरfreq= 36166667,
	.initdata = (u8[])अणु 4, 0x0b, 0xf5, 0x85, 0xab पूर्ण,
	.count = 12,
	.entries = अणु
		अणु   93834000, 166667, 0xca, 0x61 /* 011 0 0 0  01 */ पूर्ण,
		अणु  123834000, 166667, 0xca, 0xa1 /* 101 0 0 0  01 */ पूर्ण,
		अणु  161000000, 166667, 0xca, 0xa1 /* 101 0 0 0  01 */ पूर्ण,
		अणु  163834000, 166667, 0xca, 0xc2 /* 110 0 0 0  10 */ पूर्ण,
		अणु  253834000, 166667, 0xca, 0x62 /* 011 0 0 0  10 */ पूर्ण,
		अणु  383834000, 166667, 0xca, 0xa2 /* 101 0 0 0  10 */ पूर्ण,
		अणु  443834000, 166667, 0xca, 0xc2 /* 110 0 0 0  10 */ पूर्ण,
		अणु  444000000, 166667, 0xca, 0xc4 /* 110 0 0 1  00 */ पूर्ण,
		अणु  583834000, 166667, 0xca, 0x64 /* 011 0 0 1  00 */ पूर्ण,
		अणु  793834000, 166667, 0xca, 0xa4 /* 101 0 0 1  00 */ पूर्ण,
		अणु  444834000, 166667, 0xca, 0xc4 /* 110 0 0 1  00 */ पूर्ण,
		अणु  861000000, 166667, 0xca, 0xe4 /* 111 0 0 1  00 */ पूर्ण,
	पूर्ण
पूर्ण;

/* Infineon TUA6034
 * used in LG TDTP E102P
 */
अटल व्योम tua6034_bw(काष्ठा dvb_frontend *fe, u8 *buf)
अणु
	u32 bw = fe->dtv_property_cache.bandwidth_hz;
	अगर (bw == 7000000)
		buf[3] |= 0x08;
पूर्ण

अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_tua6034 = अणु
	.name  = "Infineon TUA6034",
	.min   = 44250 * kHz,
	.max   = 858 * MHz,
	.अगरfreq= 36166667,
	.count = 3,
	.set   = tua6034_bw,
	.entries = अणु
		अणु  174500000, 62500, 0xce, 0x01 पूर्ण,
		अणु  230000000, 62500, 0xce, 0x02 पूर्ण,
		अणु  999999999, 62500, 0xce, 0x04 पूर्ण,
	पूर्ण,
पूर्ण;

/* ALPS TDED4
 * used in Nebula-Cards and USB boxes
 */
अटल व्योम tded4_bw(काष्ठा dvb_frontend *fe, u8 *buf)
अणु
	u32 bw = fe->dtv_property_cache.bandwidth_hz;
	अगर (bw == 8000000)
		buf[3] |= 0x04;
पूर्ण

अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_tded4 = अणु
	.name = "ALPS TDED4",
	.min =  47 * MHz,
	.max = 863 * MHz,
	.अगरfreq= 36166667,
	.set   = tded4_bw,
	.count = 4,
	.entries = अणु
		अणु 153000000, 166667, 0x85, 0x01 पूर्ण,
		अणु 470000000, 166667, 0x85, 0x02 पूर्ण,
		अणु 823000000, 166667, 0x85, 0x08 पूर्ण,
		अणु 999999999, 166667, 0x85, 0x88 पूर्ण,
	पूर्ण
पूर्ण;

/* ALPS TDHU2
 * used in AverTVHD MCE A180
 */
अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_tdhu2 = अणु
	.name = "ALPS TDHU2",
	.min =  54 * MHz,
	.max = 864 * MHz,
	.अगरfreq= 44000000,
	.count = 4,
	.entries = अणु
		अणु 162000000, 62500, 0x85, 0x01 पूर्ण,
		अणु 426000000, 62500, 0x85, 0x02 पूर्ण,
		अणु 782000000, 62500, 0x85, 0x08 पूर्ण,
		अणु 999999999, 62500, 0x85, 0x88 पूर्ण,
	पूर्ण
पूर्ण;

/* Samsung TBMV30111IN / TBMV30712IN1
 * used in Air2PC ATSC - 2nd generation (nxt2002)
 */
अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_samsung_tbmv = अणु
	.name = "Samsung TBMV30111IN / TBMV30712IN1",
	.min =  54 * MHz,
	.max = 860 * MHz,
	.अगरfreq= 44000000,
	.count = 6,
	.entries = अणु
		अणु 172000000, 166667, 0xb4, 0x01 पूर्ण,
		अणु 214000000, 166667, 0xb4, 0x02 पूर्ण,
		अणु 467000000, 166667, 0xbc, 0x02 पूर्ण,
		अणु 721000000, 166667, 0xbc, 0x08 पूर्ण,
		अणु 841000000, 166667, 0xf4, 0x08 पूर्ण,
		अणु 999999999, 166667, 0xfc, 0x02 पूर्ण,
	पूर्ण
पूर्ण;

/*
 * Philips SD1878 Tuner.
 */
अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_philips_sd1878_tda8261 = अणु
	.name  = "Philips SD1878",
	.min   =  950 * MHz,
	.max   = 2150 * MHz,
	.अगरfreq= 249, /* zero-IF, offset 249 is to round up */
	.count = 4,
	.entries = अणु
		अणु 1250000, 500, 0xc4, 0x00पूर्ण,
		अणु 1450000, 500, 0xc4, 0x40पूर्ण,
		अणु 2050000, 500, 0xc4, 0x80पूर्ण,
		अणु 2150000, 500, 0xc4, 0xc0पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम opera1_bw(काष्ठा dvb_frontend *fe, u8 *buf)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा dvb_pll_priv *priv = fe->tuner_priv;
	u32 b_w  = (c->symbol_rate * 27) / 32000;
	काष्ठा i2c_msg msg = अणु
		.addr = priv->pll_i2c_address,
		.flags = 0,
		.buf = buf,
		.len = 4
	पूर्ण;
	पूर्णांक result;
	u8 lpf;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	result = i2c_transfer(priv->i2c, &msg, 1);
	अगर (result != 1)
		pr_err("%s: i2c_transfer failed:%d",
			__func__, result);

	अगर (b_w <= 10000)
		lpf = 0xc;
	अन्यथा अगर (b_w <= 12000)
		lpf = 0x2;
	अन्यथा अगर (b_w <= 14000)
		lpf = 0xa;
	अन्यथा अगर (b_w <= 16000)
		lpf = 0x6;
	अन्यथा अगर (b_w <= 18000)
		lpf = 0xe;
	अन्यथा अगर (b_w <= 20000)
		lpf = 0x1;
	अन्यथा अगर (b_w <= 22000)
		lpf = 0x9;
	अन्यथा अगर (b_w <= 24000)
		lpf = 0x5;
	अन्यथा अगर (b_w <= 26000)
		lpf = 0xd;
	अन्यथा अगर (b_w <= 28000)
		lpf = 0x3;
		अन्यथा
		lpf = 0xb;
	buf[2] ^= 0x1c; /* Flip bits 3-5 */
	/* Set lpf */
	buf[2] |= ((lpf >> 2) & 0x3) << 3;
	buf[3] |= (lpf & 0x3) << 2;

	वापस;
पूर्ण

अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_opera1 = अणु
	.name  = "Opera Tuner",
	.min   =  900 * MHz,
	.max   = 2250 * MHz,
	.initdata = (u8[])अणु 4, 0x08, 0xe5, 0xe1, 0x00 पूर्ण,
	.initdata2 = (u8[])अणु 4, 0x08, 0xe5, 0xe5, 0x00 पूर्ण,
	.अगरfreq= 0,
	.set   = opera1_bw,
	.count = 8,
	.entries = अणु
		अणु 1064000, 500, 0xf9, 0xc2 पूर्ण,
		अणु 1169000, 500, 0xf9, 0xe2 पूर्ण,
		अणु 1299000, 500, 0xf9, 0x20 पूर्ण,
		अणु 1444000, 500, 0xf9, 0x40 पूर्ण,
		अणु 1606000, 500, 0xf9, 0x60 पूर्ण,
		अणु 1777000, 500, 0xf9, 0x80 पूर्ण,
		अणु 1941000, 500, 0xf9, 0xa0 पूर्ण,
		अणु 2250000, 500, 0xf9, 0xc0 पूर्ण,
	पूर्ण
पूर्ण;

अटल व्योम samsung_dtos403ih102a_set(काष्ठा dvb_frontend *fe, u8 *buf)
अणु
	काष्ठा dvb_pll_priv *priv = fe->tuner_priv;
	काष्ठा i2c_msg msg = अणु
		.addr = priv->pll_i2c_address,
		.flags = 0,
		.buf = buf,
		.len = 4
	पूर्ण;
	पूर्णांक result;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	result = i2c_transfer(priv->i2c, &msg, 1);
	अगर (result != 1)
		pr_err("%s: i2c_transfer failed:%d",
			__func__, result);

	buf[2] = 0x9e;
	buf[3] = 0x90;

	वापस;
पूर्ण

/* unknown pll used in Samsung DTOS403IH102A DVB-C tuner */
अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_samsung_dtos403ih102a = अणु
	.name   = "Samsung DTOS403IH102A",
	.min    = 44250 * kHz,
	.max    = 858 * MHz,
	.अगरfreq =  36125000,
	.count  = 8,
	.set    = samsung_dtos403ih102a_set,
	.entries = अणु
		अणु 135000000, 62500, 0xbe, 0x01 पूर्ण,
		अणु 177000000, 62500, 0xf6, 0x01 पूर्ण,
		अणु 370000000, 62500, 0xbe, 0x02 पूर्ण,
		अणु 450000000, 62500, 0xf6, 0x02 पूर्ण,
		अणु 466000000, 62500, 0xfe, 0x02 पूर्ण,
		अणु 538000000, 62500, 0xbe, 0x08 पूर्ण,
		अणु 826000000, 62500, 0xf6, 0x08 पूर्ण,
		अणु 999999999, 62500, 0xfe, 0x08 पूर्ण,
	पूर्ण
पूर्ण;

/* Samsung TDTC9251DH0 DVB-T NIM, as used on AirStar 2 */
अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_samsung_tdtc9251dh0 = अणु
	.name	= "Samsung TDTC9251DH0",
	.min	=  48 * MHz,
	.max	= 863 * MHz,
	.अगरfreq	=  36166667,
	.count	= 3,
	.entries = अणु
		अणु 157500000, 166667, 0xcc, 0x09 पूर्ण,
		अणु 443000000, 166667, 0xcc, 0x0a पूर्ण,
		अणु 863000000, 166667, 0xcc, 0x08 पूर्ण,
	पूर्ण
पूर्ण;

/* Samsung TBDU18132 DVB-S NIM with TSA5059 PLL, used in SkyStar2 DVB-S 2.3 */
अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_samsung_tbdu18132 = अणु
	.name = "Samsung TBDU18132",
	.min	=  950 * MHz,
	.max	= 2150 * MHz, /* guesses */
	.अगरfreq = 0,
	.count = 2,
	.entries = अणु
		अणु 1550000, 125, 0x84, 0x82 पूर्ण,
		अणु 4095937, 125, 0x84, 0x80 पूर्ण,
	पूर्ण
	/* TSA5059 PLL has a 17 bit भागisor rather than the 15 bits supported
	 * by this driver.  The two extra bits are 0x60 in the third byte.  15
	 * bits is enough क्रम over 4 GHz, which is enough to cover the range
	 * of this tuner.  We could use the additional भागisor bits by adding
	 * more entries, e.g.
	 अणु 0x0ffff * 125 + 125/2, 125, 0x84 | 0x20, पूर्ण,
	 अणु 0x17fff * 125 + 125/2, 125, 0x84 | 0x40, पूर्ण,
	 अणु 0x1ffff * 125 + 125/2, 125, 0x84 | 0x60, पूर्ण, */
पूर्ण;

/* Samsung TBMU24112 DVB-S NIM with SL1935 zero-IF tuner */
अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_samsung_tbmu24112 = अणु
	.name = "Samsung TBMU24112",
	.min	=  950 * MHz,
	.max	= 2150 * MHz, /* guesses */
	.अगरfreq = 0,
	.count = 2,
	.entries = अणु
		अणु 1500000, 125, 0x84, 0x18 पूर्ण,
		अणु 9999999, 125, 0x84, 0x08 पूर्ण,
	पूर्ण
पूर्ण;

/* Alps TDEE4 DVB-C NIM, used on Cablestar 2 */
/* byte 4 : 1  *   *   AGD R3  R2  R1  R0
 * byte 5 : C1 *   RE  RTS BS4 BS3 BS2 BS1
 * AGD = 1, R3 R2 R1 R0 = 0 1 0 1 => byte 4 = 1**10101 = 0x95
 * Range(MHz)  C1 *  RE RTS BS4 BS3 BS2 BS1  Byte 5
 *  47 - 153   0  *  0   0   0   0   0   1   0x01
 * 153 - 430   0  *  0   0   0   0   1   0   0x02
 * 430 - 822   0  *  0   0   1   0   0   0   0x08
 * 822 - 862   1  *  0   0   1   0   0   0   0x88 */
अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_alps_tdee4 = अणु
	.name = "ALPS TDEE4",
	.min	=  47 * MHz,
	.max	= 862 * MHz,
	.अगरfreq	=  36125000,
	.count = 4,
	.entries = अणु
		अणु 153000000, 62500, 0x95, 0x01 पूर्ण,
		अणु 430000000, 62500, 0x95, 0x02 पूर्ण,
		अणु 822000000, 62500, 0x95, 0x08 पूर्ण,
		अणु 999999999, 62500, 0x95, 0x88 पूर्ण,
	पूर्ण
पूर्ण;

/* Infineon TUA6034 ISDB-T, used in Friio */
/* CP cur. 50uA, AGC takeover: 103dBuV, PORT3 on */
अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_tua6034_friio = अणु
	.name   = "Infineon TUA6034 ISDB-T (Friio)",
	.min    =  90 * MHz,
	.max    = 770 * MHz,
	.अगरfreq =  57000000,
	.initdata = (u8[])अणु 4, 0x9a, 0x50, 0xb2, 0x08 पूर्ण,
	.sleepdata = (u8[])अणु 4, 0x9a, 0x70, 0xb3, 0x0b पूर्ण,
	.count = 3,
	.entries = अणु
		अणु 170000000, 142857, 0xba, 0x09 पूर्ण,
		अणु 470000000, 142857, 0xba, 0x0a पूर्ण,
		अणु 770000000, 142857, 0xb2, 0x08 पूर्ण,
	पूर्ण
पूर्ण;

/* Philips TDA6651 ISDB-T, used in Earthsoft PT1 */
अटल स्थिर काष्ठा dvb_pll_desc dvb_pll_tda665x_earth_pt1 = अणु
	.name   = "Philips TDA6651 ISDB-T (EarthSoft PT1)",
	.min    =  90 * MHz,
	.max    = 770 * MHz,
	.अगरfreq =  57000000,
	.initdata = (u8[])अणु 5, 0x0e, 0x7f, 0xc1, 0x80, 0x80 पूर्ण,
	.count = 10,
	.entries = अणु
		अणु 140000000, 142857, 0xc1, 0x81 पूर्ण,
		अणु 170000000, 142857, 0xc1, 0xa1 पूर्ण,
		अणु 220000000, 142857, 0xc1, 0x62 पूर्ण,
		अणु 330000000, 142857, 0xc1, 0xa2 पूर्ण,
		अणु 402000000, 142857, 0xc1, 0xe2 पूर्ण,
		अणु 450000000, 142857, 0xc1, 0x64 पूर्ण,
		अणु 550000000, 142857, 0xc1, 0x84 पूर्ण,
		अणु 600000000, 142857, 0xc1, 0xa4 पूर्ण,
		अणु 700000000, 142857, 0xc1, 0xc4 पूर्ण,
		अणु 770000000, 142857, 0xc1, 0xe4 पूर्ण,
	पूर्ण
पूर्ण;

/* ----------------------------------------------------------- */

अटल स्थिर काष्ठा dvb_pll_desc *pll_list[] = अणु
	[DVB_PLL_UNDEFINED]              = शून्य,
	[DVB_PLL_THOMSON_DTT7579]        = &dvb_pll_thomson_dtt7579,
	[DVB_PLL_THOMSON_DTT759X]        = &dvb_pll_thomson_dtt759x,
	[DVB_PLL_THOMSON_DTT7520X]       = &dvb_pll_thomson_dtt7520x,
	[DVB_PLL_LG_Z201]                = &dvb_pll_lg_z201,
	[DVB_PLL_UNKNOWN_1]              = &dvb_pll_unknown_1,
	[DVB_PLL_TUA6010XS]              = &dvb_pll_tua6010xs,
	[DVB_PLL_ENV57H1XD5]             = &dvb_pll_env57h1xd5,
	[DVB_PLL_TUA6034]                = &dvb_pll_tua6034,
	[DVB_PLL_TDA665X]                = &dvb_pll_tda665x,
	[DVB_PLL_TDED4]                  = &dvb_pll_tded4,
	[DVB_PLL_TDEE4]                  = &dvb_pll_alps_tdee4,
	[DVB_PLL_TDHU2]                  = &dvb_pll_tdhu2,
	[DVB_PLL_SAMSUNG_TBMV]           = &dvb_pll_samsung_tbmv,
	[DVB_PLL_PHILIPS_SD1878_TDA8261] = &dvb_pll_philips_sd1878_tda8261,
	[DVB_PLL_OPERA1]                 = &dvb_pll_opera1,
	[DVB_PLL_SAMSUNG_DTOS403IH102A]  = &dvb_pll_samsung_dtos403ih102a,
	[DVB_PLL_SAMSUNG_TDTC9251DH0]    = &dvb_pll_samsung_tdtc9251dh0,
	[DVB_PLL_SAMSUNG_TBDU18132]	 = &dvb_pll_samsung_tbdu18132,
	[DVB_PLL_SAMSUNG_TBMU24112]      = &dvb_pll_samsung_tbmu24112,
	[DVB_PLL_TUA6034_FRIIO]          = &dvb_pll_tua6034_friio,
	[DVB_PLL_TDA665X_EARTH_PT1]      = &dvb_pll_tda665x_earth_pt1,
पूर्ण;

/* ----------------------------------------------------------- */
/* code                                                        */

अटल पूर्णांक dvb_pll_configure(काष्ठा dvb_frontend *fe, u8 *buf,
			     स्थिर u32 frequency)
अणु
	काष्ठा dvb_pll_priv *priv = fe->tuner_priv;
	स्थिर काष्ठा dvb_pll_desc *desc = priv->pll_desc;
	u32 भाग;
	पूर्णांक i;

	क्रम (i = 0; i < desc->count; i++) अणु
		अगर (frequency > desc->entries[i].limit)
			जारी;
		अवरोध;
	पूर्ण

	अगर (debug)
		dprपूर्णांकk("pll: %s: freq=%d | i=%d/%d\n", desc->name,
		       frequency, i, desc->count);
	अगर (i == desc->count)
		वापस -EINVAL;

	भाग = (frequency + desc->अगरfreq +
	       desc->entries[i].stepsize/2) / desc->entries[i].stepsize;
	buf[0] = भाग >> 8;
	buf[1] = भाग & 0xff;
	buf[2] = desc->entries[i].config;
	buf[3] = desc->entries[i].cb;

	अगर (desc->set)
		desc->set(fe, buf);

	अगर (debug)
		dprपूर्णांकk("pll: %s: div=%d | buf=0x%02x,0x%02x,0x%02x,0x%02x\n",
		       desc->name, भाग, buf[0], buf[1], buf[2], buf[3]);

	// calculate the frequency we set it to
	वापस (भाग * desc->entries[i].stepsize) - desc->अगरfreq;
पूर्ण

अटल व्योम dvb_pll_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक dvb_pll_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_pll_priv *priv = fe->tuner_priv;

	अगर (priv->i2c == शून्य)
		वापस -EINVAL;

	अगर (priv->pll_desc->sleepdata) अणु
		काष्ठा i2c_msg msg = अणु .flags = 0,
			.addr = priv->pll_i2c_address,
			.buf = priv->pll_desc->sleepdata + 1,
			.len = priv->pll_desc->sleepdata[0] पूर्ण;

		पूर्णांक result;

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		अगर ((result = i2c_transfer(priv->i2c, &msg, 1)) != 1) अणु
			वापस result;
		पूर्ण
		वापस 0;
	पूर्ण
	/* Shouldn't be called when initdata is शून्य, maybe BUG()? */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dvb_pll_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा dvb_pll_priv *priv = fe->tuner_priv;
	u8 buf[4];
	काष्ठा i2c_msg msg =
		अणु .addr = priv->pll_i2c_address, .flags = 0,
		  .buf = buf, .len = माप(buf) पूर्ण;
	पूर्णांक result;
	u32 frequency = 0;

	अगर (priv->i2c == शून्य)
		वापस -EINVAL;

	result = dvb_pll_configure(fe, buf, c->frequency);
	अगर (result < 0)
		वापस result;
	अन्यथा
		frequency = result;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर ((result = i2c_transfer(priv->i2c, &msg, 1)) != 1) अणु
		वापस result;
	पूर्ण

	priv->frequency = frequency;
	priv->bandwidth = c->bandwidth_hz;

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_pll_calc_regs(काष्ठा dvb_frontend *fe,
			     u8 *buf, पूर्णांक buf_len)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा dvb_pll_priv *priv = fe->tuner_priv;
	पूर्णांक result;
	u32 frequency = 0;

	अगर (buf_len < 5)
		वापस -EINVAL;

	result = dvb_pll_configure(fe, buf + 1, c->frequency);
	अगर (result < 0)
		वापस result;
	अन्यथा
		frequency = result;

	buf[0] = priv->pll_i2c_address;

	priv->frequency = frequency;
	priv->bandwidth = c->bandwidth_hz;

	वापस 5;
पूर्ण

अटल पूर्णांक dvb_pll_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा dvb_pll_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_pll_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा dvb_pll_priv *priv = fe->tuner_priv;
	*bandwidth = priv->bandwidth;
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_pll_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_pll_priv *priv = fe->tuner_priv;

	अगर (priv->i2c == शून्य)
		वापस -EINVAL;

	अगर (priv->pll_desc->initdata) अणु
		काष्ठा i2c_msg msg = अणु .flags = 0,
			.addr = priv->pll_i2c_address,
			.buf = priv->pll_desc->initdata + 1,
			.len = priv->pll_desc->initdata[0] पूर्ण;

		पूर्णांक result;
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		result = i2c_transfer(priv->i2c, &msg, 1);
		अगर (result != 1)
			वापस result;
		अगर (priv->pll_desc->initdata2) अणु
			msg.buf = priv->pll_desc->initdata2 + 1;
			msg.len = priv->pll_desc->initdata2[0];
			अगर (fe->ops.i2c_gate_ctrl)
				fe->ops.i2c_gate_ctrl(fe, 1);
			result = i2c_transfer(priv->i2c, &msg, 1);
			अगर (result != 1)
				वापस result;
		पूर्ण
		वापस 0;
	पूर्ण
	/* Shouldn't be called when initdata is शून्य, maybe BUG()? */
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops dvb_pll_tuner_ops = अणु
	.release = dvb_pll_release,
	.sleep = dvb_pll_sleep,
	.init = dvb_pll_init,
	.set_params = dvb_pll_set_params,
	.calc_regs = dvb_pll_calc_regs,
	.get_frequency = dvb_pll_get_frequency,
	.get_bandwidth = dvb_pll_get_bandwidth,
पूर्ण;

काष्ठा dvb_frontend *dvb_pll_attach(काष्ठा dvb_frontend *fe, पूर्णांक pll_addr,
				    काष्ठा i2c_adapter *i2c,
				    अचिन्हित पूर्णांक pll_desc_id)
अणु
	u8 *b1;
	काष्ठा i2c_msg msg = अणु .addr = pll_addr, .flags = I2C_M_RD, .len = 1 पूर्ण;
	काष्ठा dvb_pll_priv *priv = शून्य;
	पूर्णांक ret;
	स्थिर काष्ठा dvb_pll_desc *desc;
	पूर्णांक nr;

	b1 = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!b1)
		वापस शून्य;

	b1[0] = 0;
	msg.buf = b1;

	nr = ida_simple_get(&pll_ida, 0, DVB_PLL_MAX, GFP_KERNEL);
	अगर (nr < 0) अणु
		kमुक्त(b1);
		वापस शून्य;
	पूर्ण

	अगर (id[nr] > DVB_PLL_UNDEFINED && id[nr] < ARRAY_SIZE(pll_list))
		pll_desc_id = id[nr];

	BUG_ON(pll_desc_id < 1 || pll_desc_id >= ARRAY_SIZE(pll_list));

	desc = pll_list[pll_desc_id];

	अगर (i2c != शून्य) अणु
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		ret = i2c_transfer (i2c, &msg, 1);
		अगर (ret != 1)
			जाओ out;
		अगर (fe->ops.i2c_gate_ctrl)
			     fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	priv = kzalloc(माप(काष्ठा dvb_pll_priv), GFP_KERNEL);
	अगर (!priv)
		जाओ out;

	priv->pll_i2c_address = pll_addr;
	priv->i2c = i2c;
	priv->pll_desc = desc;
	priv->nr = nr;

	स_नकल(&fe->ops.tuner_ops, &dvb_pll_tuner_ops,
	       माप(काष्ठा dvb_tuner_ops));

	strscpy(fe->ops.tuner_ops.info.name, desc->name,
		माप(fe->ops.tuner_ops.info.name));

	fe->ops.tuner_ops.info.frequency_min_hz = desc->min;
	fe->ops.tuner_ops.info.frequency_max_hz = desc->max;

	dprपूर्णांकk("%s tuner, frequency range: %u...%u\n",
		desc->name, desc->min, desc->max);

	अगर (!desc->initdata)
		fe->ops.tuner_ops.init = शून्य;
	अगर (!desc->sleepdata)
		fe->ops.tuner_ops.sleep = शून्य;

	fe->tuner_priv = priv;

	अगर ((debug) || (id[priv->nr] == pll_desc_id)) अणु
		dprपूर्णांकk("dvb-pll[%d]", priv->nr);
		अगर (i2c != शून्य)
			pr_cont(" %d-%04x", i2c_adapter_id(i2c), pll_addr);
		pr_cont(": id# %d (%s) attached, %s\n", pll_desc_id, desc->name,
		       id[priv->nr] == pll_desc_id ?
				"insmod option" : "autodetected");
	पूर्ण

	kमुक्त(b1);

	वापस fe;
out:
	kमुक्त(b1);
	ida_simple_हटाओ(&pll_ida, nr);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dvb_pll_attach);


अटल पूर्णांक
dvb_pll_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा dvb_pll_config *cfg;
	काष्ठा dvb_frontend *fe;
	अचिन्हित पूर्णांक desc_id;

	cfg = client->dev.platक्रमm_data;
	fe = cfg->fe;
	i2c_set_clientdata(client, fe);
	desc_id = (अचिन्हित पूर्णांक) id->driver_data;

	अगर (!dvb_pll_attach(fe, client->addr, client->adapter, desc_id))
		वापस -ENOMEM;

	/*
	 * Unset tuner_ops.release (== dvb_pll_release)
	 * which has been just set in the above dvb_pll_attach(),
	 * because अगर tuner_ops.release was left defined,
	 * this module would be 'put' twice on निकास:
	 * once by dvb_frontend_detach() and another by dvb_module_release().
	 *
	 * dvb_pll_release is instead executed in the i2c driver's .हटाओ(),
	 * keeping dvb_pll_attach untouched क्रम legacy (dvb_attach) drivers.
	 */
	fe->ops.tuner_ops.release = शून्य;
	dev_info(&client->dev, "DVB Simple Tuner attached.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_pll_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा dvb_frontend *fe = i2c_get_clientdata(client);
	काष्ठा dvb_pll_priv *priv = fe->tuner_priv;

	ida_simple_हटाओ(&pll_ida, priv->nr);
	dvb_pll_release(fe);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा i2c_device_id dvb_pll_id[] = अणु
	अणु"dtt7579",		DVB_PLL_THOMSON_DTT7579पूर्ण,
	अणु"dtt759x",		DVB_PLL_THOMSON_DTT759Xपूर्ण,
	अणु"z201",		DVB_PLL_LG_Z201पूर्ण,
	अणु"unknown_1",		DVB_PLL_UNKNOWN_1पूर्ण,
	अणु"tua6010xs",		DVB_PLL_TUA6010XSपूर्ण,
	अणु"env57h1xd5",		DVB_PLL_ENV57H1XD5पूर्ण,
	अणु"tua6034",		DVB_PLL_TUA6034पूर्ण,
	अणु"tda665x",		DVB_PLL_TDA665Xपूर्ण,
	अणु"tded4",		DVB_PLL_TDED4पूर्ण,
	अणु"tdhu2",		DVB_PLL_TDHU2पूर्ण,
	अणु"tbmv",		DVB_PLL_SAMSUNG_TBMVपूर्ण,
	अणु"sd1878_tda8261",	DVB_PLL_PHILIPS_SD1878_TDA8261पूर्ण,
	अणु"opera1",		DVB_PLL_OPERA1पूर्ण,
	अणु"dtos403ih102a",	DVB_PLL_SAMSUNG_DTOS403IH102Aपूर्ण,
	अणु"tdtc9251dh0",		DVB_PLL_SAMSUNG_TDTC9251DH0पूर्ण,
	अणु"tbdu18132",		DVB_PLL_SAMSUNG_TBDU18132पूर्ण,
	अणु"tbmu24112",		DVB_PLL_SAMSUNG_TBMU24112पूर्ण,
	अणु"tdee4",		DVB_PLL_TDEE4पूर्ण,
	अणु"dtt7520x",		DVB_PLL_THOMSON_DTT7520Xपूर्ण,
	अणु"tua6034_friio",	DVB_PLL_TUA6034_FRIIOपूर्ण,
	अणु"tda665x_earthpt1",	DVB_PLL_TDA665X_EARTH_PT1पूर्ण,
	अणुपूर्ण
पूर्ण;


MODULE_DEVICE_TABLE(i2c, dvb_pll_id);

अटल काष्ठा i2c_driver dvb_pll_driver = अणु
	.driver = अणु
		.name = "dvb_pll",
	पूर्ण,
	.probe    = dvb_pll_probe,
	.हटाओ   = dvb_pll_हटाओ,
	.id_table = dvb_pll_id,
पूर्ण;

module_i2c_driver(dvb_pll_driver);

MODULE_DESCRIPTION("dvb pll library");
MODULE_AUTHOR("Gerd Knorr");
MODULE_LICENSE("GPL");
