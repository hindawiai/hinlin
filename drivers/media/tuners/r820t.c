<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Rafael Micro R820T driver
//
// Copyright (C) 2013 Mauro Carvalho Chehab
//
// This driver was written from scratch, based on an existing driver
// that it is part of rtl-sdr git tree, released under GPLv2:
//	https://groups.google.com/क्रमum/#!topic/ultra-cheap-sdr/Y3rBखातापूर्णtHug
//	https://github.com/n1gp/gr-baz
//
// From what I understood from the thपढ़ोs, the original driver was converted
// to userspace from a Realtek tree. I couldn't find the original tree.
// However, the original driver look awkward on my eyes. So, I decided to
// ग_लिखो a new version from it from the scratch, जबतक trying to reproduce
// everything found there.
//
// TODO:
//	After locking, the original driver seems to have some routines to
//		improve reception. This was not implemented here yet.
//
//	RF Gain set/get is not implemented.

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/videodev2.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitrev.h>

#समावेश "tuner-i2c.h"
#समावेश "r820t.h"

/*
 * FIXME: I think that there are only 32 रेजिस्टरs, but better safe than
 *	  sorry. After finishing the driver, we may review it.
 */
#घोषणा REG_SHADOW_START	5
#घोषणा NUM_REGS		27
#घोषणा NUM_IMR			5
#घोषणा IMR_TRIAL		9

#घोषणा VER_NUM  49

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable verbose debug messages");

अटल पूर्णांक no_imr_cal;
module_param(no_imr_cal, पूर्णांक, 0444);
MODULE_PARM_DESC(no_imr_cal, "Disable IMR calibration at module init");


/*
 * क्रमागतs and काष्ठाures
 */

क्रमागत xtal_cap_value अणु
	XTAL_LOW_CAP_30P = 0,
	XTAL_LOW_CAP_20P,
	XTAL_LOW_CAP_10P,
	XTAL_LOW_CAP_0P,
	XTAL_HIGH_CAP_0P
पूर्ण;

काष्ठा r820t_sect_type अणु
	u8	phase_y;
	u8	gain_x;
	u16	value;
पूर्ण;

काष्ठा r820t_priv अणु
	काष्ठा list_head		hybrid_tuner_instance_list;
	स्थिर काष्ठा r820t_config	*cfg;
	काष्ठा tuner_i2c_props		i2c_props;
	काष्ठा mutex			lock;

	u8				regs[NUM_REGS];
	u8				buf[NUM_REGS + 1];
	क्रमागत xtal_cap_value		xtal_cap_sel;
	u16				pll;	/* kHz */
	u32				पूर्णांक_freq;
	u8				fil_cal_code;
	bool				imr_करोne;
	bool				has_lock;
	bool				init_करोne;
	काष्ठा r820t_sect_type		imr_data[NUM_IMR];

	/* Store current mode */
	u32				delsys;
	क्रमागत v4l2_tuner_type		type;
	v4l2_std_id			std;
	u32				bw;	/* in MHz */
पूर्ण;

काष्ठा r820t_freq_range अणु
	u32	freq;
	u8	खोलो_d;
	u8	rf_mux_ploy;
	u8	tf_c;
	u8	xtal_cap20p;
	u8	xtal_cap10p;
	u8	xtal_cap0p;
	u8	imr_mem;		/* Not used, currently */
पूर्ण;

#घोषणा VCO_POWER_REF   0x02
#घोषणा DIP_FREQ	32000000

/*
 * Static स्थिरants
 */

अटल LIST_HEAD(hybrid_tuner_instance_list);
अटल DEFINE_MUTEX(r820t_list_mutex);

/* Those initial values start from REG_SHADOW_START */
अटल स्थिर u8 r820t_init_array[NUM_REGS] = अणु
	0x83, 0x32, 0x75,			/* 05 to 07 */
	0xc0, 0x40, 0xd6, 0x6c,			/* 08 to 0b */
	0xf5, 0x63, 0x75, 0x68,			/* 0c to 0f */
	0x6c, 0x83, 0x80, 0x00,			/* 10 to 13 */
	0x0f, 0x00, 0xc0, 0x30,			/* 14 to 17 */
	0x48, 0xcc, 0x60, 0x00,			/* 18 to 1b */
	0x54, 0xae, 0x4a, 0xc0			/* 1c to 1f */
पूर्ण;

/* Tuner frequency ranges */
अटल स्थिर काष्ठा r820t_freq_range freq_ranges[] = अणु
	अणु
		.freq = 0,
		.खोलो_d = 0x08,		/* low */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0xdf,		/* R27[7:0]  band2,band0 */
		.xtal_cap20p = 0x02,	/* R16[1:0]  20pF (10)   */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 0,
	पूर्ण, अणु
		.freq = 50,		/* Start freq, in MHz */
		.खोलो_d = 0x08,		/* low */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0xbe,		/* R27[7:0]  band4,band1  */
		.xtal_cap20p = 0x02,	/* R16[1:0]  20pF (10)   */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 0,
	पूर्ण, अणु
		.freq = 55,		/* Start freq, in MHz */
		.खोलो_d = 0x08,		/* low */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x8b,		/* R27[7:0]  band7,band4 */
		.xtal_cap20p = 0x02,	/* R16[1:0]  20pF (10)   */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 0,
	पूर्ण, अणु
		.freq = 60,		/* Start freq, in MHz */
		.खोलो_d = 0x08,		/* low */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x7b,		/* R27[7:0]  band8,band4 */
		.xtal_cap20p = 0x02,	/* R16[1:0]  20pF (10)   */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 0,
	पूर्ण, अणु
		.freq = 65,		/* Start freq, in MHz */
		.खोलो_d = 0x08,		/* low */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x69,		/* R27[7:0]  band9,band6 */
		.xtal_cap20p = 0x02,	/* R16[1:0]  20pF (10)   */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 0,
	पूर्ण, अणु
		.freq = 70,		/* Start freq, in MHz */
		.खोलो_d = 0x08,		/* low */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x58,		/* R27[7:0]  band10,band7 */
		.xtal_cap20p = 0x02,	/* R16[1:0]  20pF (10)   */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 0,
	पूर्ण, अणु
		.freq = 75,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x44,		/* R27[7:0]  band11,band11 */
		.xtal_cap20p = 0x02,	/* R16[1:0]  20pF (10)   */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 0,
	पूर्ण, अणु
		.freq = 80,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x44,		/* R27[7:0]  band11,band11 */
		.xtal_cap20p = 0x02,	/* R16[1:0]  20pF (10)   */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 0,
	पूर्ण, अणु
		.freq = 90,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x34,		/* R27[7:0]  band12,band11 */
		.xtal_cap20p = 0x01,	/* R16[1:0]  10pF (01)   */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 0,
	पूर्ण, अणु
		.freq = 100,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x34,		/* R27[7:0]  band12,band11 */
		.xtal_cap20p = 0x01,	/* R16[1:0]  10pF (01)    */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 0,
	पूर्ण, अणु
		.freq = 110,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x24,		/* R27[7:0]  band13,band11 */
		.xtal_cap20p = 0x01,	/* R16[1:0]  10pF (01)   */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 1,
	पूर्ण, अणु
		.freq = 120,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x24,		/* R27[7:0]  band13,band11 */
		.xtal_cap20p = 0x01,	/* R16[1:0]  10pF (01)   */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 1,
	पूर्ण, अणु
		.freq = 140,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x14,		/* R27[7:0]  band14,band11 */
		.xtal_cap20p = 0x01,	/* R16[1:0]  10pF (01)   */
		.xtal_cap10p = 0x01,
		.xtal_cap0p = 0x00,
		.imr_mem = 1,
	पूर्ण, अणु
		.freq = 180,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x13,		/* R27[7:0]  band14,band12 */
		.xtal_cap20p = 0x00,	/* R16[1:0]  0pF (00)   */
		.xtal_cap10p = 0x00,
		.xtal_cap0p = 0x00,
		.imr_mem = 1,
	पूर्ण, अणु
		.freq = 220,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x13,		/* R27[7:0]  band14,band12 */
		.xtal_cap20p = 0x00,	/* R16[1:0]  0pF (00)   */
		.xtal_cap10p = 0x00,
		.xtal_cap0p = 0x00,
		.imr_mem = 2,
	पूर्ण, अणु
		.freq = 250,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x11,		/* R27[7:0]  highest,highest */
		.xtal_cap20p = 0x00,	/* R16[1:0]  0pF (00)   */
		.xtal_cap10p = 0x00,
		.xtal_cap0p = 0x00,
		.imr_mem = 2,
	पूर्ण, अणु
		.freq = 280,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x02,	/* R26[7:6]=0 (LPF)  R26[1:0]=2 (low) */
		.tf_c = 0x00,		/* R27[7:0]  highest,highest */
		.xtal_cap20p = 0x00,	/* R16[1:0]  0pF (00)   */
		.xtal_cap10p = 0x00,
		.xtal_cap0p = 0x00,
		.imr_mem = 2,
	पूर्ण, अणु
		.freq = 310,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x41,	/* R26[7:6]=1 (bypass)  R26[1:0]=1 (middle) */
		.tf_c = 0x00,		/* R27[7:0]  highest,highest */
		.xtal_cap20p = 0x00,	/* R16[1:0]  0pF (00)   */
		.xtal_cap10p = 0x00,
		.xtal_cap0p = 0x00,
		.imr_mem = 2,
	पूर्ण, अणु
		.freq = 450,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x41,	/* R26[7:6]=1 (bypass)  R26[1:0]=1 (middle) */
		.tf_c = 0x00,		/* R27[7:0]  highest,highest */
		.xtal_cap20p = 0x00,	/* R16[1:0]  0pF (00)   */
		.xtal_cap10p = 0x00,
		.xtal_cap0p = 0x00,
		.imr_mem = 3,
	पूर्ण, अणु
		.freq = 588,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x40,	/* R26[7:6]=1 (bypass)  R26[1:0]=0 (highest) */
		.tf_c = 0x00,		/* R27[7:0]  highest,highest */
		.xtal_cap20p = 0x00,	/* R16[1:0]  0pF (00)   */
		.xtal_cap10p = 0x00,
		.xtal_cap0p = 0x00,
		.imr_mem = 3,
	पूर्ण, अणु
		.freq = 650,		/* Start freq, in MHz */
		.खोलो_d = 0x00,		/* high */
		.rf_mux_ploy = 0x40,	/* R26[7:6]=1 (bypass)  R26[1:0]=0 (highest) */
		.tf_c = 0x00,		/* R27[7:0]  highest,highest */
		.xtal_cap20p = 0x00,	/* R16[1:0]  0pF (00)   */
		.xtal_cap10p = 0x00,
		.xtal_cap0p = 0x00,
		.imr_mem = 4,
	पूर्ण
पूर्ण;

अटल पूर्णांक r820t_xtal_capacitor[][2] = अणु
	अणु 0x0b, XTAL_LOW_CAP_30P पूर्ण,
	अणु 0x02, XTAL_LOW_CAP_20P पूर्ण,
	अणु 0x01, XTAL_LOW_CAP_10P पूर्ण,
	अणु 0x00, XTAL_LOW_CAP_0P  पूर्ण,
	अणु 0x10, XTAL_HIGH_CAP_0P पूर्ण,
पूर्ण;

/*
 * I2C पढ़ो/ग_लिखो code and shaकरोw रेजिस्टरs logic
 */
अटल व्योम shaकरोw_store(काष्ठा r820t_priv *priv, u8 reg, स्थिर u8 *val,
			 पूर्णांक len)
अणु
	पूर्णांक r = reg - REG_SHADOW_START;

	अगर (r < 0) अणु
		len += r;
		r = 0;
	पूर्ण
	अगर (len <= 0)
		वापस;
	अगर (len > NUM_REGS - r)
		len = NUM_REGS - r;

	tuner_dbg("%s: prev  reg=%02x len=%d: %*ph\n",
		  __func__, r + REG_SHADOW_START, len, len, val);

	स_नकल(&priv->regs[r], val, len);
पूर्ण

अटल पूर्णांक r820t_ग_लिखो(काष्ठा r820t_priv *priv, u8 reg, स्थिर u8 *val,
		       पूर्णांक len)
अणु
	पूर्णांक rc, size, pos = 0;

	/* Store the shaकरोw रेजिस्टरs */
	shaकरोw_store(priv, reg, val, len);

	करो अणु
		अगर (len > priv->cfg->max_i2c_msg_len - 1)
			size = priv->cfg->max_i2c_msg_len - 1;
		अन्यथा
			size = len;

		/* Fill I2C buffer */
		priv->buf[0] = reg;
		स_नकल(&priv->buf[1], &val[pos], size);

		rc = tuner_i2c_xfer_send(&priv->i2c_props, priv->buf, size + 1);
		अगर (rc != size + 1) अणु
			tuner_info("%s: i2c wr failed=%d reg=%02x len=%d: %*ph\n",
				   __func__, rc, reg, size, size, &priv->buf[1]);
			अगर (rc < 0)
				वापस rc;
			वापस -EREMOTEIO;
		पूर्ण
		tuner_dbg("%s: i2c wr reg=%02x len=%d: %*ph\n",
			  __func__, reg, size, size, &priv->buf[1]);

		reg += size;
		len -= size;
		pos += size;
	पूर्ण जबतक (len > 0);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक r820t_ग_लिखो_reg(काष्ठा r820t_priv *priv, u8 reg, u8 val)
अणु
	u8 पंचांगp = val; /* work around GCC PR81715 with asan-stack=1 */

	वापस r820t_ग_लिखो(priv, reg, &पंचांगp, 1);
पूर्ण

अटल पूर्णांक r820t_पढ़ो_cache_reg(काष्ठा r820t_priv *priv, पूर्णांक reg)
अणु
	reg -= REG_SHADOW_START;

	अगर (reg >= 0 && reg < NUM_REGS)
		वापस priv->regs[reg];
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक r820t_ग_लिखो_reg_mask(काष्ठा r820t_priv *priv, u8 reg, u8 val,
				u8 bit_mask)
अणु
	u8 पंचांगp = val;
	पूर्णांक rc = r820t_पढ़ो_cache_reg(priv, reg);

	अगर (rc < 0)
		वापस rc;

	पंचांगp = (rc & ~bit_mask) | (पंचांगp & bit_mask);

	वापस r820t_ग_लिखो(priv, reg, &पंचांगp, 1);
पूर्ण

अटल पूर्णांक r820t_पढ़ो(काष्ठा r820t_priv *priv, u8 reg, u8 *val, पूर्णांक len)
अणु
	पूर्णांक rc, i;
	u8 *p = &priv->buf[1];

	priv->buf[0] = reg;

	rc = tuner_i2c_xfer_send_recv(&priv->i2c_props, priv->buf, 1, p, len);
	अगर (rc != len) अणु
		tuner_info("%s: i2c rd failed=%d reg=%02x len=%d: %*ph\n",
			   __func__, rc, reg, len, len, p);
		अगर (rc < 0)
			वापस rc;
		वापस -EREMOTEIO;
	पूर्ण

	/* Copy data to the output buffer */
	क्रम (i = 0; i < len; i++)
		val[i] = bitrev8(p[i]);

	tuner_dbg("%s: i2c rd reg=%02x len=%d: %*ph\n",
		  __func__, reg, len, len, val);

	वापस 0;
पूर्ण

/*
 * r820t tuning logic
 */

अटल पूर्णांक r820t_set_mux(काष्ठा r820t_priv *priv, u32 freq)
अणु
	स्थिर काष्ठा r820t_freq_range *range;
	पूर्णांक i, rc;
	u8 val, reg08, reg09;

	/* Get the proper frequency range */
	freq = freq / 1000000;
	क्रम (i = 0; i < ARRAY_SIZE(freq_ranges) - 1; i++) अणु
		अगर (freq < freq_ranges[i + 1].freq)
			अवरोध;
	पूर्ण
	range = &freq_ranges[i];

	tuner_dbg("set r820t range#%d for frequency %d MHz\n", i, freq);

	/* Open Drain */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x17, range->खोलो_d, 0x08);
	अगर (rc < 0)
		वापस rc;

	/* RF_MUX,Polymux */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x1a, range->rf_mux_ploy, 0xc3);
	अगर (rc < 0)
		वापस rc;

	/* TF BAND */
	rc = r820t_ग_लिखो_reg(priv, 0x1b, range->tf_c);
	अगर (rc < 0)
		वापस rc;

	/* XTAL CAP & Drive */
	चयन (priv->xtal_cap_sel) अणु
	हाल XTAL_LOW_CAP_30P:
	हाल XTAL_LOW_CAP_20P:
		val = range->xtal_cap20p | 0x08;
		अवरोध;
	हाल XTAL_LOW_CAP_10P:
		val = range->xtal_cap10p | 0x08;
		अवरोध;
	हाल XTAL_HIGH_CAP_0P:
		val = range->xtal_cap0p | 0x00;
		अवरोध;
	शेष:
	हाल XTAL_LOW_CAP_0P:
		val = range->xtal_cap0p | 0x08;
		अवरोध;
	पूर्ण
	rc = r820t_ग_लिखो_reg_mask(priv, 0x10, val, 0x0b);
	अगर (rc < 0)
		वापस rc;

	अगर (priv->imr_करोne) अणु
		reg08 = priv->imr_data[range->imr_mem].gain_x;
		reg09 = priv->imr_data[range->imr_mem].phase_y;
	पूर्ण अन्यथा अणु
		reg08 = 0;
		reg09 = 0;
	पूर्ण
	rc = r820t_ग_लिखो_reg_mask(priv, 0x08, reg08, 0x3f);
	अगर (rc < 0)
		वापस rc;

	rc = r820t_ग_लिखो_reg_mask(priv, 0x09, reg09, 0x3f);

	वापस rc;
पूर्ण

अटल पूर्णांक r820t_set_pll(काष्ठा r820t_priv *priv, क्रमागत v4l2_tuner_type type,
			 u32 freq)
अणु
	u32 vco_freq;
	पूर्णांक rc, i;
	अचिन्हित sleep_समय = 10000;
	u32 vco_fra;		/* VCO contribution by SDM (kHz) */
	u32 vco_min  = 1770000;
	u32 vco_max  = vco_min * 2;
	u32 pll_ref;
	u16 n_sdm = 2;
	u16 sdm = 0;
	u8 mix_भाग = 2;
	u8 भाग_buf = 0;
	u8 भाग_num = 0;
	u8 refभाग2 = 0;
	u8 ni, si, nपूर्णांक, vco_fine_tune, val;
	u8 data[5];

	/* Frequency in kHz */
	freq = freq / 1000;
	pll_ref = priv->cfg->xtal / 1000;

#अगर 0
	/* Doesn't exist on rtl-sdk, and on field tests, caused troubles */
	अगर ((priv->cfg->rafael_chip == CHIP_R620D) ||
	   (priv->cfg->rafael_chip == CHIP_R828D) ||
	   (priv->cfg->rafael_chip == CHIP_R828)) अणु
		/* ref set refभाग2, reffreq = Xtal/2 on ATV application */
		अगर (type != V4L2_TUNER_DIGITAL_TV) अणु
			pll_ref /= 2;
			refभाग2 = 0x10;
			sleep_समय = 20000;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (priv->cfg->xtal > 24000000) अणु
			pll_ref /= 2;
			refभाग2 = 0x10;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	rc = r820t_ग_लिखो_reg_mask(priv, 0x10, refभाग2, 0x10);
	अगर (rc < 0)
		वापस rc;

	/* set pll स्वतःtune = 128kHz */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x1a, 0x00, 0x0c);
	अगर (rc < 0)
		वापस rc;

	/* set VCO current = 100 */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x12, 0x80, 0xe0);
	अगर (rc < 0)
		वापस rc;

	/* Calculate भागider */
	जबतक (mix_भाग <= 64) अणु
		अगर (((freq * mix_भाग) >= vco_min) &&
		   ((freq * mix_भाग) < vco_max)) अणु
			भाग_buf = mix_भाग;
			जबतक (भाग_buf > 2) अणु
				भाग_buf = भाग_buf >> 1;
				भाग_num++;
			पूर्ण
			अवरोध;
		पूर्ण
		mix_भाग = mix_भाग << 1;
	पूर्ण

	rc = r820t_पढ़ो(priv, 0x00, data, माप(data));
	अगर (rc < 0)
		वापस rc;

	vco_fine_tune = (data[4] & 0x30) >> 4;

	tuner_dbg("mix_div=%d div_num=%d vco_fine_tune=%d\n",
			mix_भाग, भाग_num, vco_fine_tune);

	/*
	 * XXX: R828D/16MHz seems to have always vco_fine_tune=1.
	 * Due to that, this calculation goes wrong.
	 */
	अगर (priv->cfg->rafael_chip != CHIP_R828D) अणु
		अगर (vco_fine_tune > VCO_POWER_REF)
			भाग_num = भाग_num - 1;
		अन्यथा अगर (vco_fine_tune < VCO_POWER_REF)
			भाग_num = भाग_num + 1;
	पूर्ण

	rc = r820t_ग_लिखो_reg_mask(priv, 0x10, भाग_num << 5, 0xe0);
	अगर (rc < 0)
		वापस rc;

	vco_freq = freq * mix_भाग;
	nपूर्णांक = vco_freq / (2 * pll_ref);
	vco_fra = vco_freq - 2 * pll_ref * nपूर्णांक;

	/* boundary spur prevention */
	अगर (vco_fra < pll_ref / 64) अणु
		vco_fra = 0;
	पूर्ण अन्यथा अगर (vco_fra > pll_ref * 127 / 64) अणु
		vco_fra = 0;
		nपूर्णांक++;
	पूर्ण अन्यथा अगर ((vco_fra > pll_ref * 127 / 128) && (vco_fra < pll_ref)) अणु
		vco_fra = pll_ref * 127 / 128;
	पूर्ण अन्यथा अगर ((vco_fra > pll_ref) && (vco_fra < pll_ref * 129 / 128)) अणु
		vco_fra = pll_ref * 129 / 128;
	पूर्ण

	ni = (nपूर्णांक - 13) / 4;
	si = nपूर्णांक - 4 * ni - 13;

	rc = r820t_ग_लिखो_reg(priv, 0x14, ni + (si << 6));
	अगर (rc < 0)
		वापस rc;

	/* pw_sdm */
	अगर (!vco_fra)
		val = 0x08;
	अन्यथा
		val = 0x00;

	rc = r820t_ग_लिखो_reg_mask(priv, 0x12, val, 0x08);
	अगर (rc < 0)
		वापस rc;

	/* sdm calculator */
	जबतक (vco_fra > 1) अणु
		अगर (vco_fra > (2 * pll_ref / n_sdm)) अणु
			sdm = sdm + 32768 / (n_sdm / 2);
			vco_fra = vco_fra - 2 * pll_ref / n_sdm;
			अगर (n_sdm >= 0x8000)
				अवरोध;
		पूर्ण
		n_sdm = n_sdm << 1;
	पूर्ण

	tuner_dbg("freq %d kHz, pll ref %d%s, sdm=0x%04x\n",
		  freq, pll_ref, refभाग2 ? " / 2" : "", sdm);

	rc = r820t_ग_लिखो_reg(priv, 0x16, sdm >> 8);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x15, sdm & 0xff);
	अगर (rc < 0)
		वापस rc;

	क्रम (i = 0; i < 2; i++) अणु
		usleep_range(sleep_समय, sleep_समय + 1000);

		/* Check अगर PLL has locked */
		rc = r820t_पढ़ो(priv, 0x00, data, 3);
		अगर (rc < 0)
			वापस rc;
		अगर (data[2] & 0x40)
			अवरोध;

		अगर (!i) अणु
			/* Didn't lock. Increase VCO current */
			rc = r820t_ग_लिखो_reg_mask(priv, 0x12, 0x60, 0xe0);
			अगर (rc < 0)
				वापस rc;
		पूर्ण
	पूर्ण

	अगर (!(data[2] & 0x40)) अणु
		priv->has_lock = false;
		वापस 0;
	पूर्ण

	priv->has_lock = true;
	tuner_dbg("tuner has lock at frequency %d kHz\n", freq);

	/* set pll स्वतःtune = 8kHz */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x1a, 0x08, 0x08);

	वापस rc;
पूर्ण

अटल पूर्णांक r820t_sysfreq_sel(काष्ठा r820t_priv *priv, u32 freq,
			     क्रमागत v4l2_tuner_type type,
			     v4l2_std_id std,
			     u32 delsys)
अणु
	पूर्णांक rc;
	u8 mixer_top, lna_top, cp_cur, भाग_buf_cur, lna_vth_l, mixer_vth_l;
	u8 air_cable1_in, cable2_in, pre_dect, lna_disअक्षरge, filter_cur;

	tuner_dbg("adjusting tuner parameters for the standard\n");

	चयन (delsys) अणु
	हाल SYS_DVBT:
		अगर ((freq == 506000000) || (freq == 666000000) ||
		   (freq == 818000000)) अणु
			mixer_top = 0x14;	/* mixer top:14 , top-1, low-disअक्षरge */
			lna_top = 0xe5;		/* detect bw 3, lna top:4, predet top:2 */
			cp_cur = 0x28;		/* 101, 0.2 */
			भाग_buf_cur = 0x20;	/* 10, 200u */
		पूर्ण अन्यथा अणु
			mixer_top = 0x24;	/* mixer top:13 , top-1, low-disअक्षरge */
			lna_top = 0xe5;		/* detect bw 3, lna top:4, predet top:2 */
			cp_cur = 0x38;		/* 111, स्वतः */
			भाग_buf_cur = 0x30;	/* 11, 150u */
		पूर्ण
		lna_vth_l = 0x53;		/* lna vth 0.84	,  vtl 0.64 */
		mixer_vth_l = 0x75;		/* mixer vth 1.04, vtl 0.84 */
		air_cable1_in = 0x00;
		cable2_in = 0x00;
		pre_dect = 0x40;
		lna_disअक्षरge = 14;
		filter_cur = 0x40;		/* 10, low */
		अवरोध;
	हाल SYS_DVBT2:
		mixer_top = 0x24;	/* mixer top:13 , top-1, low-disअक्षरge */
		lna_top = 0xe5;		/* detect bw 3, lna top:4, predet top:2 */
		lna_vth_l = 0x53;	/* lna vth 0.84	,  vtl 0.64 */
		mixer_vth_l = 0x75;	/* mixer vth 1.04, vtl 0.84 */
		air_cable1_in = 0x00;
		cable2_in = 0x00;
		pre_dect = 0x40;
		lna_disअक्षरge = 14;
		cp_cur = 0x38;		/* 111, स्वतः */
		भाग_buf_cur = 0x30;	/* 11, 150u */
		filter_cur = 0x40;	/* 10, low */
		अवरोध;
	हाल SYS_ISDBT:
		mixer_top = 0x24;	/* mixer top:13 , top-1, low-disअक्षरge */
		lna_top = 0xe5;		/* detect bw 3, lna top:4, predet top:2 */
		lna_vth_l = 0x75;	/* lna vth 1.04	,  vtl 0.84 */
		mixer_vth_l = 0x75;	/* mixer vth 1.04, vtl 0.84 */
		air_cable1_in = 0x00;
		cable2_in = 0x00;
		pre_dect = 0x40;
		lna_disअक्षरge = 14;
		cp_cur = 0x38;		/* 111, स्वतः */
		भाग_buf_cur = 0x30;	/* 11, 150u */
		filter_cur = 0x40;	/* 10, low */
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		mixer_top = 0x24;       /* mixer top:13 , top-1, low-disअक्षरge */
		lna_top = 0xe5;
		lna_vth_l = 0x62;
		mixer_vth_l = 0x75;
		air_cable1_in = 0x60;
		cable2_in = 0x00;
		pre_dect = 0x40;
		lna_disअक्षरge = 14;
		cp_cur = 0x38;          /* 111, स्वतः */
		भाग_buf_cur = 0x30;     /* 11, 150u */
		filter_cur = 0x40;      /* 10, low */
		अवरोध;
	शेष: /* DVB-T 8M */
		mixer_top = 0x24;	/* mixer top:13 , top-1, low-disअक्षरge */
		lna_top = 0xe5;		/* detect bw 3, lna top:4, predet top:2 */
		lna_vth_l = 0x53;	/* lna vth 0.84	,  vtl 0.64 */
		mixer_vth_l = 0x75;	/* mixer vth 1.04, vtl 0.84 */
		air_cable1_in = 0x00;
		cable2_in = 0x00;
		pre_dect = 0x40;
		lna_disअक्षरge = 14;
		cp_cur = 0x38;		/* 111, स्वतः */
		भाग_buf_cur = 0x30;	/* 11, 150u */
		filter_cur = 0x40;	/* 10, low */
		अवरोध;
	पूर्ण

	अगर (priv->cfg->use_diplexer &&
	   ((priv->cfg->rafael_chip == CHIP_R820T) ||
	   (priv->cfg->rafael_chip == CHIP_R828S) ||
	   (priv->cfg->rafael_chip == CHIP_R820C))) अणु
		अगर (freq > DIP_FREQ)
			air_cable1_in = 0x00;
		अन्यथा
			air_cable1_in = 0x60;
		cable2_in = 0x00;
	पूर्ण


	अगर (priv->cfg->use_predetect) अणु
		rc = r820t_ग_लिखो_reg_mask(priv, 0x06, pre_dect, 0x40);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	rc = r820t_ग_लिखो_reg_mask(priv, 0x1d, lna_top, 0xc7);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg_mask(priv, 0x1c, mixer_top, 0xf8);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x0d, lna_vth_l);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x0e, mixer_vth_l);
	अगर (rc < 0)
		वापस rc;

	/* Air-IN only क्रम Astrometa */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x05, air_cable1_in, 0x60);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg_mask(priv, 0x06, cable2_in, 0x08);
	अगर (rc < 0)
		वापस rc;

	rc = r820t_ग_लिखो_reg_mask(priv, 0x11, cp_cur, 0x38);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg_mask(priv, 0x17, भाग_buf_cur, 0x30);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg_mask(priv, 0x0a, filter_cur, 0x60);
	अगर (rc < 0)
		वापस rc;
	/*
	 * Original driver initializes regs 0x05 and 0x06 with the
	 * same value again on this poपूर्णांक. Probably, it is just an
	 * error there
	 */

	/*
	 * Set LNA
	 */

	tuner_dbg("adjusting LNA parameters\n");
	अगर (type != V4L2_TUNER_ANALOG_TV) अणु
		/* LNA TOP: lowest */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x1d, 0, 0x38);
		अगर (rc < 0)
			वापस rc;

		/* 0: normal mode */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x1c, 0, 0x04);
		अगर (rc < 0)
			वापस rc;

		/* 0: PRE_DECT off */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x06, 0, 0x40);
		अगर (rc < 0)
			वापस rc;

		/* agc clk 250hz */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x1a, 0x30, 0x30);
		अगर (rc < 0)
			वापस rc;

		msleep(250);

		/* ग_लिखो LNA TOP = 3 */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x1d, 0x18, 0x38);
		अगर (rc < 0)
			वापस rc;

		/*
		 * ग_लिखो disअक्षरge mode
		 * FIXME: IMHO, the mask here is wrong, but it matches
		 * what's there at the original driver
		 */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x1c, mixer_top, 0x04);
		अगर (rc < 0)
			वापस rc;

		/* LNA disअक्षरge current */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x1e, lna_disअक्षरge, 0x1f);
		अगर (rc < 0)
			वापस rc;

		/* agc clk 60hz */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x1a, 0x20, 0x30);
		अगर (rc < 0)
			वापस rc;
	पूर्ण अन्यथा अणु
		/* PRE_DECT off */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x06, 0, 0x40);
		अगर (rc < 0)
			वापस rc;

		/* ग_लिखो LNA TOP */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x1d, lna_top, 0x38);
		अगर (rc < 0)
			वापस rc;

		/*
		 * ग_लिखो disअक्षरge mode
		 * FIXME: IMHO, the mask here is wrong, but it matches
		 * what's there at the original driver
		 */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x1c, mixer_top, 0x04);
		अगर (rc < 0)
			वापस rc;

		/* LNA disअक्षरge current */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x1e, lna_disअक्षरge, 0x1f);
		अगर (rc < 0)
			वापस rc;

		/* agc clk 1Khz, बाह्यal det1 cap 1u */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x1a, 0x00, 0x30);
		अगर (rc < 0)
			वापस rc;

		rc = r820t_ग_लिखो_reg_mask(priv, 0x10, 0x00, 0x04);
		अगर (rc < 0)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक r820t_set_tv_standard(काष्ठा r820t_priv *priv,
				 अचिन्हित bw,
				 क्रमागत v4l2_tuner_type type,
				 v4l2_std_id std, u32 delsys)

अणु
	पूर्णांक rc, i;
	u32 अगर_khz, filt_cal_lo;
	u8 data[5], val;
	u8 filt_gain, img_r, filt_q, hp_cor, ext_enable, loop_through;
	u8 lt_att, flt_ext_widest, polyfil_cur;
	bool need_calibration;

	tuner_dbg("selecting the delivery system\n");

	अगर (delsys == SYS_ISDBT) अणु
		अगर_khz = 4063;
		filt_cal_lo = 59000;
		filt_gain = 0x10;	/* +3db, 6mhz on */
		img_r = 0x00;		/* image negative */
		filt_q = 0x10;		/* r10[4]:low q(1'b1) */
		hp_cor = 0x6a;		/* 1.7m disable, +2cap, 1.25mhz */
		ext_enable = 0x40;	/* r30[6], ext enable; r30[5]:0 ext at lna max */
		loop_through = 0x00;	/* r5[7], lt on */
		lt_att = 0x00;		/* r31[7], lt att enable */
		flt_ext_widest = 0x80;	/* r15[7]: flt_ext_wide on */
		polyfil_cur = 0x60;	/* r25[6:5]:min */
	पूर्ण अन्यथा अगर (delsys == SYS_DVBC_ANNEX_A) अणु
		अगर_khz = 5070;
		filt_cal_lo = 73500;
		filt_gain = 0x10;	/* +3db, 6mhz on */
		img_r = 0x00;		/* image negative */
		filt_q = 0x10;		/* r10[4]:low q(1'b1) */
		hp_cor = 0x0b;		/* 1.7m disable, +0cap, 1.0mhz */
		ext_enable = 0x40;	/* r30[6]=1 ext enable; r30[5]:1 ext at lna max-1 */
		loop_through = 0x00;	/* r5[7], lt on */
		lt_att = 0x00;		/* r31[7], lt att enable */
		flt_ext_widest = 0x00;	/* r15[7]: flt_ext_wide off */
		polyfil_cur = 0x60;	/* r25[6:5]:min */
	पूर्ण अन्यथा अगर (delsys == SYS_DVBC_ANNEX_C) अणु
		अगर_khz = 4063;
		filt_cal_lo = 55000;
		filt_gain = 0x10;	/* +3db, 6mhz on */
		img_r = 0x00;		/* image negative */
		filt_q = 0x10;		/* r10[4]:low q(1'b1) */
		hp_cor = 0x6a;		/* 1.7m disable, +0cap, 1.0mhz */
		ext_enable = 0x40;	/* r30[6]=1 ext enable; r30[5]:1 ext at lna max-1 */
		loop_through = 0x00;	/* r5[7], lt on */
		lt_att = 0x00;		/* r31[7], lt att enable */
		flt_ext_widest = 0x80;	/* r15[7]: flt_ext_wide on */
		polyfil_cur = 0x60;	/* r25[6:5]:min */
	पूर्ण अन्यथा अणु
		अगर (bw <= 6) अणु
			अगर_khz = 3570;
			filt_cal_lo = 56000;	/* 52000->56000 */
			filt_gain = 0x10;	/* +3db, 6mhz on */
			img_r = 0x00;		/* image negative */
			filt_q = 0x10;		/* r10[4]:low q(1'b1) */
			hp_cor = 0x6b;		/* 1.7m disable, +2cap, 1.0mhz */
			ext_enable = 0x60;	/* r30[6]=1 ext enable; r30[5]:1 ext at lna max-1 */
			loop_through = 0x00;	/* r5[7], lt on */
			lt_att = 0x00;		/* r31[7], lt att enable */
			flt_ext_widest = 0x00;	/* r15[7]: flt_ext_wide off */
			polyfil_cur = 0x60;	/* r25[6:5]:min */
		पूर्ण अन्यथा अगर (bw == 7) अणु
#अगर 0
			/*
			 * There are two 7 MHz tables defined on the original
			 * driver, but just the second one seems to be visible
			 * by rtl2832. Keep this one here commented, as it
			 * might be needed in the future
			 */

			अगर_khz = 4070;
			filt_cal_lo = 60000;
			filt_gain = 0x10;	/* +3db, 6mhz on */
			img_r = 0x00;		/* image negative */
			filt_q = 0x10;		/* r10[4]:low q(1'b1) */
			hp_cor = 0x2b;		/* 1.7m disable, +1cap, 1.0mhz */
			ext_enable = 0x60;	/* r30[6]=1 ext enable; r30[5]:1 ext at lna max-1 */
			loop_through = 0x00;	/* r5[7], lt on */
			lt_att = 0x00;		/* r31[7], lt att enable */
			flt_ext_widest = 0x00;	/* r15[7]: flt_ext_wide off */
			polyfil_cur = 0x60;	/* r25[6:5]:min */
#पूर्ण_अगर
			/* 7 MHz, second table */
			अगर_khz = 4570;
			filt_cal_lo = 63000;
			filt_gain = 0x10;	/* +3db, 6mhz on */
			img_r = 0x00;		/* image negative */
			filt_q = 0x10;		/* r10[4]:low q(1'b1) */
			hp_cor = 0x2a;		/* 1.7m disable, +1cap, 1.25mhz */
			ext_enable = 0x60;	/* r30[6]=1 ext enable; r30[5]:1 ext at lna max-1 */
			loop_through = 0x00;	/* r5[7], lt on */
			lt_att = 0x00;		/* r31[7], lt att enable */
			flt_ext_widest = 0x00;	/* r15[7]: flt_ext_wide off */
			polyfil_cur = 0x60;	/* r25[6:5]:min */
		पूर्ण अन्यथा अणु
			अगर_khz = 4570;
			filt_cal_lo = 68500;
			filt_gain = 0x10;	/* +3db, 6mhz on */
			img_r = 0x00;		/* image negative */
			filt_q = 0x10;		/* r10[4]:low q(1'b1) */
			hp_cor = 0x0b;		/* 1.7m disable, +0cap, 1.0mhz */
			ext_enable = 0x60;	/* r30[6]=1 ext enable; r30[5]:1 ext at lna max-1 */
			loop_through = 0x00;	/* r5[7], lt on */
			lt_att = 0x00;		/* r31[7], lt att enable */
			flt_ext_widest = 0x00;	/* r15[7]: flt_ext_wide off */
			polyfil_cur = 0x60;	/* r25[6:5]:min */
		पूर्ण
	पूर्ण

	/* Initialize the shaकरोw रेजिस्टरs */
	स_नकल(priv->regs, r820t_init_array, माप(r820t_init_array));

	/* Init Flag & Xtal_check Result */
	अगर (priv->imr_करोne)
		val = 1 | priv->xtal_cap_sel << 1;
	अन्यथा
		val = 0;
	rc = r820t_ग_लिखो_reg_mask(priv, 0x0c, val, 0x0f);
	अगर (rc < 0)
		वापस rc;

	/* version */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x13, VER_NUM, 0x3f);
	अगर (rc < 0)
		वापस rc;

	/* क्रम LT Gain test */
	अगर (type != V4L2_TUNER_ANALOG_TV) अणु
		rc = r820t_ग_लिखो_reg_mask(priv, 0x1d, 0x00, 0x38);
		अगर (rc < 0)
			वापस rc;
		usleep_range(1000, 2000);
	पूर्ण
	priv->पूर्णांक_freq = अगर_khz * 1000;

	/* Check अगर standard changed. If so, filter calibration is needed */
	अगर (type != priv->type)
		need_calibration = true;
	अन्यथा अगर ((type == V4L2_TUNER_ANALOG_TV) && (std != priv->std))
		need_calibration = true;
	अन्यथा अगर ((type == V4L2_TUNER_DIGITAL_TV) &&
		 ((delsys != priv->delsys) || bw != priv->bw))
		need_calibration = true;
	अन्यथा
		need_calibration = false;

	अगर (need_calibration) अणु
		tuner_dbg("calibrating the tuner\n");
		क्रम (i = 0; i < 2; i++) अणु
			/* Set filt_cap */
			rc = r820t_ग_लिखो_reg_mask(priv, 0x0b, hp_cor, 0x60);
			अगर (rc < 0)
				वापस rc;

			/* set cali clk =on */
			rc = r820t_ग_लिखो_reg_mask(priv, 0x0f, 0x04, 0x04);
			अगर (rc < 0)
				वापस rc;

			/* X'tal cap 0pF क्रम PLL */
			rc = r820t_ग_लिखो_reg_mask(priv, 0x10, 0x00, 0x03);
			अगर (rc < 0)
				वापस rc;

			rc = r820t_set_pll(priv, type, filt_cal_lo * 1000);
			अगर (rc < 0 || !priv->has_lock)
				वापस rc;

			/* Start Trigger */
			rc = r820t_ग_लिखो_reg_mask(priv, 0x0b, 0x10, 0x10);
			अगर (rc < 0)
				वापस rc;

			usleep_range(1000, 2000);

			/* Stop Trigger */
			rc = r820t_ग_लिखो_reg_mask(priv, 0x0b, 0x00, 0x10);
			अगर (rc < 0)
				वापस rc;

			/* set cali clk =off */
			rc = r820t_ग_लिखो_reg_mask(priv, 0x0f, 0x00, 0x04);
			अगर (rc < 0)
				वापस rc;

			/* Check अगर calibration worked */
			rc = r820t_पढ़ो(priv, 0x00, data, माप(data));
			अगर (rc < 0)
				वापस rc;

			priv->fil_cal_code = data[4] & 0x0f;
			अगर (priv->fil_cal_code && priv->fil_cal_code != 0x0f)
				अवरोध;
		पूर्ण
		/* narrowest */
		अगर (priv->fil_cal_code == 0x0f)
			priv->fil_cal_code = 0;
	पूर्ण

	rc = r820t_ग_लिखो_reg_mask(priv, 0x0a,
				  filt_q | priv->fil_cal_code, 0x1f);
	अगर (rc < 0)
		वापस rc;

	/* Set BW, Filter_gain, & HP corner */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x0b, hp_cor, 0xef);
	अगर (rc < 0)
		वापस rc;


	/* Set Img_R */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x07, img_r, 0x80);
	अगर (rc < 0)
		वापस rc;

	/* Set filt_3dB, V6MHz */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x06, filt_gain, 0x30);
	अगर (rc < 0)
		वापस rc;

	/* channel filter extension */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x1e, ext_enable, 0x60);
	अगर (rc < 0)
		वापस rc;

	/* Loop through */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x05, loop_through, 0x80);
	अगर (rc < 0)
		वापस rc;

	/* Loop through attenuation */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x1f, lt_att, 0x80);
	अगर (rc < 0)
		वापस rc;

	/* filter extension widest */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x0f, flt_ext_widest, 0x80);
	अगर (rc < 0)
		वापस rc;

	/* RF poly filter current */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x19, polyfil_cur, 0x60);
	अगर (rc < 0)
		वापस rc;

	/* Store current standard. If it changes, re-calibrate the tuner */
	priv->delsys = delsys;
	priv->type = type;
	priv->std = std;
	priv->bw = bw;

	वापस 0;
पूर्ण

अटल पूर्णांक r820t_पढ़ो_gain(काष्ठा r820t_priv *priv)
अणु
	u8 data[4];
	पूर्णांक rc;

	rc = r820t_पढ़ो(priv, 0x00, data, माप(data));
	अगर (rc < 0)
		वापस rc;

	वापस ((data[3] & 0x08) << 1) + ((data[3] & 0xf0) >> 4);
पूर्ण

#अगर 0
/* FIXME: This routine requires more testing */

/*
 * measured with a Racal 6103E GSM test set at 928 MHz with -60 dBm
 * input घातer, क्रम raw results see:
 *	http://steve-m.de/projects/rtl-sdr/gain_measurement/r820t/
 */

अटल स्थिर पूर्णांक r820t_lna_gain_steps[]  = अणु
	0, 9, 13, 40, 38, 13, 31, 22, 26, 31, 26, 14, 19, 5, 35, 13
पूर्ण;

अटल स्थिर पूर्णांक r820t_mixer_gain_steps[]  = अणु
	0, 5, 10, 10, 19, 9, 10, 25, 17, 10, 8, 16, 13, 6, 3, -8
पूर्ण;

अटल पूर्णांक r820t_set_gain_mode(काष्ठा r820t_priv *priv,
			       bool set_manual_gain,
			       पूर्णांक gain)
अणु
	पूर्णांक rc;

	अगर (set_manual_gain) अणु
		पूर्णांक i, total_gain = 0;
		uपूर्णांक8_t mix_index = 0, lna_index = 0;
		u8 data[4];

		/* LNA स्वतः off */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x05, 0x10, 0x10);
		अगर (rc < 0)
			वापस rc;

		 /* Mixer स्वतः off */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x07, 0, 0x10);
		अगर (rc < 0)
			वापस rc;

		rc = r820t_पढ़ो(priv, 0x00, data, माप(data));
		अगर (rc < 0)
			वापस rc;

		/* set fixed VGA gain क्रम now (16.3 dB) */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x0c, 0x08, 0x9f);
		अगर (rc < 0)
			वापस rc;

		क्रम (i = 0; i < 15; i++) अणु
			अगर (total_gain >= gain)
				अवरोध;

			total_gain += r820t_lna_gain_steps[++lna_index];

			अगर (total_gain >= gain)
				अवरोध;

			total_gain += r820t_mixer_gain_steps[++mix_index];
		पूर्ण

		/* set LNA gain */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x05, lna_index, 0x0f);
		अगर (rc < 0)
			वापस rc;

		/* set Mixer gain */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x07, mix_index, 0x0f);
		अगर (rc < 0)
			वापस rc;
	पूर्ण अन्यथा अणु
		/* LNA */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x05, 0, 0x10);
		अगर (rc < 0)
			वापस rc;

		/* Mixer */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x07, 0x10, 0x10);
		अगर (rc < 0)
			वापस rc;

		/* set fixed VGA gain क्रम now (26.5 dB) */
		rc = r820t_ग_लिखो_reg_mask(priv, 0x0c, 0x0b, 0x9f);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक generic_set_freq(काष्ठा dvb_frontend *fe,
			    u32 freq /* in HZ */,
			    अचिन्हित bw,
			    क्रमागत v4l2_tuner_type type,
			    v4l2_std_id std, u32 delsys)
अणु
	काष्ठा r820t_priv		*priv = fe->tuner_priv;
	पूर्णांक				rc;
	u32				lo_freq;

	tuner_dbg("should set frequency to %d kHz, bw %d MHz\n",
		  freq / 1000, bw);

	rc = r820t_set_tv_standard(priv, bw, type, std, delsys);
	अगर (rc < 0)
		जाओ err;

	अगर ((type == V4L2_TUNER_ANALOG_TV) && (std == V4L2_STD_SECAM_LC))
		lo_freq = freq - priv->पूर्णांक_freq;
	 अन्यथा
		lo_freq = freq + priv->पूर्णांक_freq;

	rc = r820t_set_mux(priv, lo_freq);
	अगर (rc < 0)
		जाओ err;

	rc = r820t_set_pll(priv, type, lo_freq);
	अगर (rc < 0 || !priv->has_lock)
		जाओ err;

	rc = r820t_sysfreq_sel(priv, freq, type, std, delsys);
	अगर (rc < 0)
		जाओ err;

	tuner_dbg("%s: PLL locked on frequency %d Hz, gain=%d\n",
		  __func__, freq, r820t_पढ़ो_gain(priv));

err:

	अगर (rc < 0)
		tuner_dbg("%s: failed=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/*
 * r820t standby logic
 */

अटल पूर्णांक r820t_standby(काष्ठा r820t_priv *priv)
अणु
	पूर्णांक rc;

	/* If device was not initialized yet, करोn't need to standby */
	अगर (!priv->init_करोne)
		वापस 0;

	rc = r820t_ग_लिखो_reg(priv, 0x06, 0xb1);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x05, 0x03);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x07, 0x3a);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x08, 0x40);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x09, 0xc0);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x0a, 0x36);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x0c, 0x35);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x0f, 0x68);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x11, 0x03);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x17, 0xf4);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_ग_लिखो_reg(priv, 0x19, 0x0c);

	/* Force initial calibration */
	priv->type = -1;

	वापस rc;
पूर्ण

/*
 * r820t device init logic
 */

अटल पूर्णांक r820t_xtal_check(काष्ठा r820t_priv *priv)
अणु
	पूर्णांक rc, i;
	u8 data[3], val;

	/* Initialize the shaकरोw रेजिस्टरs */
	स_नकल(priv->regs, r820t_init_array, माप(r820t_init_array));

	/* cap 30pF & Drive Low */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x10, 0x0b, 0x0b);
	अगर (rc < 0)
		वापस rc;

	/* set pll स्वतःtune = 128kHz */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x1a, 0x00, 0x0c);
	अगर (rc < 0)
		वापस rc;

	/* set manual initial reg = 111111;  */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x13, 0x7f, 0x7f);
	अगर (rc < 0)
		वापस rc;

	/* set स्वतः */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x13, 0x00, 0x40);
	अगर (rc < 0)
		वापस rc;

	/* Try several xtal capacitor alternatives */
	क्रम (i = 0; i < ARRAY_SIZE(r820t_xtal_capacitor); i++) अणु
		rc = r820t_ग_लिखो_reg_mask(priv, 0x10,
					  r820t_xtal_capacitor[i][0], 0x1b);
		अगर (rc < 0)
			वापस rc;

		usleep_range(5000, 6000);

		rc = r820t_पढ़ो(priv, 0x00, data, माप(data));
		अगर (rc < 0)
			वापस rc;
		अगर (!(data[2] & 0x40))
			जारी;

		val = data[2] & 0x3f;

		अगर (priv->cfg->xtal == 16000000 && (val > 29 || val < 23))
			अवरोध;

		अगर (val != 0x3f)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(r820t_xtal_capacitor))
		वापस -EINVAL;

	वापस r820t_xtal_capacitor[i][1];
पूर्ण

अटल पूर्णांक r820t_imr_prepare(काष्ठा r820t_priv *priv)
अणु
	पूर्णांक rc;

	/* Initialize the shaकरोw रेजिस्टरs */
	स_नकल(priv->regs, r820t_init_array, माप(r820t_init_array));

	/* lna off (air-in off) */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x05, 0x20, 0x20);
	अगर (rc < 0)
		वापस rc;

	/* mixer gain mode = manual */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x07, 0, 0x10);
	अगर (rc < 0)
		वापस rc;

	/* filter corner = lowest */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x0a, 0x0f, 0x0f);
	अगर (rc < 0)
		वापस rc;

	/* filter bw=+2cap, hp=5M */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x0b, 0x60, 0x6f);
	अगर (rc < 0)
		वापस rc;

	/* adc=on, vga code mode, gain = 26.5dB   */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x0c, 0x0b, 0x9f);
	अगर (rc < 0)
		वापस rc;

	/* ring clk = on */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x0f, 0, 0x08);
	अगर (rc < 0)
		वापस rc;

	/* ring घातer = on */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x18, 0x10, 0x10);
	अगर (rc < 0)
		वापस rc;

	/* from ring = ring pll in */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x1c, 0x02, 0x02);
	अगर (rc < 0)
		वापस rc;

	/* sw_pdect = det3 */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x1e, 0x80, 0x80);
	अगर (rc < 0)
		वापस rc;

	/* Set filt_3dB */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x06, 0x20, 0x20);

	वापस rc;
पूर्ण

अटल पूर्णांक r820t_multi_पढ़ो(काष्ठा r820t_priv *priv)
अणु
	पूर्णांक rc, i;
	u16 sum = 0;
	u8 data[2], min = 255, max = 0;

	usleep_range(5000, 6000);

	क्रम (i = 0; i < 6; i++) अणु
		rc = r820t_पढ़ो(priv, 0x00, data, माप(data));
		अगर (rc < 0)
			वापस rc;

		sum += data[1];

		अगर (data[1] < min)
			min = data[1];

		अगर (data[1] > max)
			max = data[1];
	पूर्ण
	rc = sum - max - min;

	वापस rc;
पूर्ण

अटल पूर्णांक r820t_imr_cross(काष्ठा r820t_priv *priv,
			   काष्ठा r820t_sect_type iq_poपूर्णांक[3],
			   u8 *x_direct)
अणु
	काष्ठा r820t_sect_type cross[5]; /* (0,0)(0,Q-1)(0,I-1)(Q-1,0)(I-1,0) */
	काष्ठा r820t_sect_type पंचांगp;
	पूर्णांक i, rc;
	u8 reg08, reg09;

	reg08 = r820t_पढ़ो_cache_reg(priv, 8) & 0xc0;
	reg09 = r820t_पढ़ो_cache_reg(priv, 9) & 0xc0;

	पंचांगp.gain_x = 0;
	पंचांगp.phase_y = 0;
	पंचांगp.value = 255;

	क्रम (i = 0; i < 5; i++) अणु
		चयन (i) अणु
		हाल 0:
			cross[i].gain_x  = reg08;
			cross[i].phase_y = reg09;
			अवरोध;
		हाल 1:
			cross[i].gain_x  = reg08;		/* 0 */
			cross[i].phase_y = reg09 + 1;		/* Q-1 */
			अवरोध;
		हाल 2:
			cross[i].gain_x  = reg08;		/* 0 */
			cross[i].phase_y = (reg09 | 0x20) + 1;	/* I-1 */
			अवरोध;
		हाल 3:
			cross[i].gain_x  = reg08 + 1;		/* Q-1 */
			cross[i].phase_y = reg09;
			अवरोध;
		शेष:
			cross[i].gain_x  = (reg08 | 0x20) + 1;	/* I-1 */
			cross[i].phase_y = reg09;
		पूर्ण

		rc = r820t_ग_लिखो_reg(priv, 0x08, cross[i].gain_x);
		अगर (rc < 0)
			वापस rc;

		rc = r820t_ग_लिखो_reg(priv, 0x09, cross[i].phase_y);
		अगर (rc < 0)
			वापस rc;

		rc = r820t_multi_पढ़ो(priv);
		अगर (rc < 0)
			वापस rc;

		cross[i].value = rc;

		अगर (cross[i].value < पंचांगp.value)
			पंचांगp = cross[i];
	पूर्ण

	अगर ((पंचांगp.phase_y & 0x1f) == 1) अणु	/* y-direction */
		*x_direct = 0;

		iq_poपूर्णांक[0] = cross[0];
		iq_poपूर्णांक[1] = cross[1];
		iq_poपूर्णांक[2] = cross[2];
	पूर्ण अन्यथा अणु				/* (0,0) or x-direction */
		*x_direct = 1;

		iq_poपूर्णांक[0] = cross[0];
		iq_poपूर्णांक[1] = cross[3];
		iq_poपूर्णांक[2] = cross[4];
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम r820t_compre_cor(काष्ठा r820t_sect_type iq[3])
अणु
	पूर्णांक i;

	क्रम (i = 3; i > 0; i--) अणु
		अगर (iq[0].value > iq[i - 1].value)
			swap(iq[0], iq[i - 1]);
	पूर्ण
पूर्ण

अटल पूर्णांक r820t_compre_step(काष्ठा r820t_priv *priv,
			     काष्ठा r820t_sect_type iq[3], u8 reg)
अणु
	पूर्णांक rc;
	काष्ठा r820t_sect_type पंचांगp;

	/*
	 * Purpose: अगर (Gain<9 or Phase<9), Gain+1 or Phase+1 and compare
	 * with min value:
	 *  new < min => update to min and जारी
	 *  new > min => Exit
	 */

	/* min value alपढ़ोy saved in iq[0] */
	पंचांगp.phase_y = iq[0].phase_y;
	पंचांगp.gain_x  = iq[0].gain_x;

	जबतक (((पंचांगp.gain_x & 0x1f) < IMR_TRIAL) &&
	      ((पंचांगp.phase_y & 0x1f) < IMR_TRIAL)) अणु
		अगर (reg == 0x08)
			पंचांगp.gain_x++;
		अन्यथा
			पंचांगp.phase_y++;

		rc = r820t_ग_लिखो_reg(priv, 0x08, पंचांगp.gain_x);
		अगर (rc < 0)
			वापस rc;

		rc = r820t_ग_लिखो_reg(priv, 0x09, पंचांगp.phase_y);
		अगर (rc < 0)
			वापस rc;

		rc = r820t_multi_पढ़ो(priv);
		अगर (rc < 0)
			वापस rc;
		पंचांगp.value = rc;

		अगर (पंचांगp.value <= iq[0].value) अणु
			iq[0].gain_x  = पंचांगp.gain_x;
			iq[0].phase_y = पंचांगp.phase_y;
			iq[0].value   = पंचांगp.value;
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक r820t_iq_tree(काष्ठा r820t_priv *priv,
			 काष्ठा r820t_sect_type iq[3],
			 u8 fix_val, u8 var_val, u8 fix_reg)
अणु
	पूर्णांक rc, i;
	u8 पंचांगp, var_reg;

	/*
	 * record IMC results by input gain/phase location then adjust
	 * gain or phase positive 1 step and negative 1 step,
	 * both record results
	 */

	अगर (fix_reg == 0x08)
		var_reg = 0x09;
	अन्यथा
		var_reg = 0x08;

	क्रम (i = 0; i < 3; i++) अणु
		rc = r820t_ग_लिखो_reg(priv, fix_reg, fix_val);
		अगर (rc < 0)
			वापस rc;

		rc = r820t_ग_लिखो_reg(priv, var_reg, var_val);
		अगर (rc < 0)
			वापस rc;

		rc = r820t_multi_पढ़ो(priv);
		अगर (rc < 0)
			वापस rc;
		iq[i].value = rc;

		अगर (fix_reg == 0x08) अणु
			iq[i].gain_x  = fix_val;
			iq[i].phase_y = var_val;
		पूर्ण अन्यथा अणु
			iq[i].phase_y = fix_val;
			iq[i].gain_x  = var_val;
		पूर्ण

		अगर (i == 0) अणु  /* try right-side poपूर्णांक */
			var_val++;
		पूर्ण अन्यथा अगर (i == 1) अणु /* try left-side poपूर्णांक */
			 /* अगर असलolute location is 1, change I/Q direction */
			अगर ((var_val & 0x1f) < 0x02) अणु
				पंचांगp = 2 - (var_val & 0x1f);

				/* b[5]:I/Q selection. 0:Q-path, 1:I-path */
				अगर (var_val & 0x20) अणु
					var_val &= 0xc0;
					var_val |= पंचांगp;
				पूर्ण अन्यथा अणु
					var_val |= 0x20 | पंचांगp;
				पूर्ण
			पूर्ण अन्यथा अणु
				var_val -= 2;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक r820t_section(काष्ठा r820t_priv *priv,
			 काष्ठा r820t_sect_type *iq_poपूर्णांक)
अणु
	पूर्णांक rc;
	काष्ठा r820t_sect_type compare_iq[3], compare_bet[3];

	/* Try X-1 column and save min result to compare_bet[0] */
	अगर (!(iq_poपूर्णांक->gain_x & 0x1f))
		compare_iq[0].gain_x = ((iq_poपूर्णांक->gain_x) & 0xdf) + 1;  /* Q-path, Gain=1 */
	अन्यथा
		compare_iq[0].gain_x  = iq_poपूर्णांक->gain_x - 1;  /* left poपूर्णांक */
	compare_iq[0].phase_y = iq_poपूर्णांक->phase_y;

	/* y-direction */
	rc = r820t_iq_tree(priv, compare_iq,  compare_iq[0].gain_x,
			compare_iq[0].phase_y, 0x08);
	अगर (rc < 0)
		वापस rc;

	r820t_compre_cor(compare_iq);

	compare_bet[0] = compare_iq[0];

	/* Try X column and save min result to compare_bet[1] */
	compare_iq[0].gain_x  = iq_poपूर्णांक->gain_x;
	compare_iq[0].phase_y = iq_poपूर्णांक->phase_y;

	rc = r820t_iq_tree(priv, compare_iq,  compare_iq[0].gain_x,
			   compare_iq[0].phase_y, 0x08);
	अगर (rc < 0)
		वापस rc;

	r820t_compre_cor(compare_iq);

	compare_bet[1] = compare_iq[0];

	/* Try X+1 column and save min result to compare_bet[2] */
	अगर ((iq_poपूर्णांक->gain_x & 0x1f) == 0x00)
		compare_iq[0].gain_x = ((iq_poपूर्णांक->gain_x) | 0x20) + 1;  /* I-path, Gain=1 */
	अन्यथा
		compare_iq[0].gain_x = iq_poपूर्णांक->gain_x + 1;
	compare_iq[0].phase_y = iq_poपूर्णांक->phase_y;

	rc = r820t_iq_tree(priv, compare_iq,  compare_iq[0].gain_x,
			   compare_iq[0].phase_y, 0x08);
	अगर (rc < 0)
		वापस rc;

	r820t_compre_cor(compare_iq);

	compare_bet[2] = compare_iq[0];

	r820t_compre_cor(compare_bet);

	*iq_poपूर्णांक = compare_bet[0];

	वापस 0;
पूर्ण

अटल पूर्णांक r820t_vga_adjust(काष्ठा r820t_priv *priv)
अणु
	पूर्णांक rc;
	u8 vga_count;

	/* increase vga घातer to let image signअगरicant */
	क्रम (vga_count = 12; vga_count < 16; vga_count++) अणु
		rc = r820t_ग_लिखो_reg_mask(priv, 0x0c, vga_count, 0x0f);
		अगर (rc < 0)
			वापस rc;

		usleep_range(10000, 11000);

		rc = r820t_multi_पढ़ो(priv);
		अगर (rc < 0)
			वापस rc;

		अगर (rc > 40 * 4)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक r820t_iq(काष्ठा r820t_priv *priv, काष्ठा r820t_sect_type *iq_pont)
अणु
	काष्ठा r820t_sect_type compare_iq[3];
	पूर्णांक rc;
	u8 x_direction = 0;  /* 1:x, 0:y */
	u8 dir_reg, other_reg;

	r820t_vga_adjust(priv);

	rc = r820t_imr_cross(priv, compare_iq, &x_direction);
	अगर (rc < 0)
		वापस rc;

	अगर (x_direction == 1) अणु
		dir_reg   = 0x08;
		other_reg = 0x09;
	पूर्ण अन्यथा अणु
		dir_reg   = 0x09;
		other_reg = 0x08;
	पूर्ण

	/* compare and find min of 3 poपूर्णांकs. determine i/q direction */
	r820t_compre_cor(compare_iq);

	/* increase step to find min value of this direction */
	rc = r820t_compre_step(priv, compare_iq, dir_reg);
	अगर (rc < 0)
		वापस rc;

	/* the other direction */
	rc = r820t_iq_tree(priv, compare_iq,  compare_iq[0].gain_x,
				compare_iq[0].phase_y, dir_reg);
	अगर (rc < 0)
		वापस rc;

	/* compare and find min of 3 poपूर्णांकs. determine i/q direction */
	r820t_compre_cor(compare_iq);

	/* increase step to find min value on this direction */
	rc = r820t_compre_step(priv, compare_iq, other_reg);
	अगर (rc < 0)
		वापस rc;

	/* check 3 poपूर्णांकs again */
	rc = r820t_iq_tree(priv, compare_iq,  compare_iq[0].gain_x,
				compare_iq[0].phase_y, other_reg);
	अगर (rc < 0)
		वापस rc;

	r820t_compre_cor(compare_iq);

	/* section-9 check */
	rc = r820t_section(priv, compare_iq);

	*iq_pont = compare_iq[0];

	/* reset gain/phase control setting */
	rc = r820t_ग_लिखो_reg_mask(priv, 0x08, 0, 0x3f);
	अगर (rc < 0)
		वापस rc;

	rc = r820t_ग_लिखो_reg_mask(priv, 0x09, 0, 0x3f);

	वापस rc;
पूर्ण

अटल पूर्णांक r820t_f_imr(काष्ठा r820t_priv *priv, काष्ठा r820t_sect_type *iq_pont)
अणु
	पूर्णांक rc;

	r820t_vga_adjust(priv);

	/*
	 * search surrounding poपूर्णांकs from previous poपूर्णांक
	 * try (x-1), (x), (x+1) columns, and find min IMR result poपूर्णांक
	 */
	rc = r820t_section(priv, iq_pont);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक r820t_imr(काष्ठा r820t_priv *priv, अचिन्हित imr_mem, bool im_flag)
अणु
	काष्ठा r820t_sect_type imr_poपूर्णांक;
	पूर्णांक rc;
	u32 ring_vco, ring_freq, ring_ref;
	u8 n_ring, n;
	पूर्णांक reg18, reg19, reg1f;

	अगर (priv->cfg->xtal > 24000000)
		ring_ref = priv->cfg->xtal / 2000;
	अन्यथा
		ring_ref = priv->cfg->xtal / 1000;

	n_ring = 15;
	क्रम (n = 0; n < 16; n++) अणु
		अगर ((16 + n) * 8 * ring_ref >= 3100000) अणु
			n_ring = n;
			अवरोध;
		पूर्ण
	पूर्ण

	reg18 = r820t_पढ़ो_cache_reg(priv, 0x18);
	reg19 = r820t_पढ़ो_cache_reg(priv, 0x19);
	reg1f = r820t_पढ़ो_cache_reg(priv, 0x1f);

	reg18 &= 0xf0;      /* set ring[3:0] */
	reg18 |= n_ring;

	ring_vco = (16 + n_ring) * 8 * ring_ref;

	reg18 &= 0xdf;   /* clear ring_se23 */
	reg19 &= 0xfc;   /* clear ring_seद_भाग */
	reg1f &= 0xfc;   /* clear ring_att */

	चयन (imr_mem) अणु
	हाल 0:
		ring_freq = ring_vco / 48;
		reg18 |= 0x20;  /* ring_se23 = 1 */
		reg19 |= 0x03;  /* ring_seद_भाग = 3 */
		reg1f |= 0x02;  /* ring_att 10 */
		अवरोध;
	हाल 1:
		ring_freq = ring_vco / 16;
		reg18 |= 0x00;  /* ring_se23 = 0 */
		reg19 |= 0x02;  /* ring_seद_भाग = 2 */
		reg1f |= 0x00;  /* pw_ring 00 */
		अवरोध;
	हाल 2:
		ring_freq = ring_vco / 8;
		reg18 |= 0x00;  /* ring_se23 = 0 */
		reg19 |= 0x01;  /* ring_seद_भाग = 1 */
		reg1f |= 0x03;  /* pw_ring 11 */
		अवरोध;
	हाल 3:
		ring_freq = ring_vco / 6;
		reg18 |= 0x20;  /* ring_se23 = 1 */
		reg19 |= 0x00;  /* ring_seद_भाग = 0 */
		reg1f |= 0x03;  /* pw_ring 11 */
		अवरोध;
	हाल 4:
		ring_freq = ring_vco / 4;
		reg18 |= 0x00;  /* ring_se23 = 0 */
		reg19 |= 0x00;  /* ring_seद_भाग = 0 */
		reg1f |= 0x01;  /* pw_ring 01 */
		अवरोध;
	शेष:
		ring_freq = ring_vco / 4;
		reg18 |= 0x00;  /* ring_se23 = 0 */
		reg19 |= 0x00;  /* ring_seद_भाग = 0 */
		reg1f |= 0x01;  /* pw_ring 01 */
		अवरोध;
	पूर्ण


	/* ग_लिखो pw_ring, n_ring, ringभाग2 रेजिस्टरs */

	/* n_ring, ring_se23 */
	rc = r820t_ग_लिखो_reg(priv, 0x18, reg18);
	अगर (rc < 0)
		वापस rc;

	/* ring_seभाग */
	rc = r820t_ग_लिखो_reg(priv, 0x19, reg19);
	अगर (rc < 0)
		वापस rc;

	/* pw_ring */
	rc = r820t_ग_लिखो_reg(priv, 0x1f, reg1f);
	अगर (rc < 0)
		वापस rc;

	/* mux input freq ~ rf_in freq */
	rc = r820t_set_mux(priv, (ring_freq - 5300) * 1000);
	अगर (rc < 0)
		वापस rc;

	rc = r820t_set_pll(priv, V4L2_TUNER_DIGITAL_TV,
			   (ring_freq - 5300) * 1000);
	अगर (!priv->has_lock)
		rc = -EINVAL;
	अगर (rc < 0)
		वापस rc;

	अगर (im_flag) अणु
		rc = r820t_iq(priv, &imr_poपूर्णांक);
	पूर्ण अन्यथा अणु
		imr_poपूर्णांक.gain_x  = priv->imr_data[3].gain_x;
		imr_poपूर्णांक.phase_y = priv->imr_data[3].phase_y;
		imr_poपूर्णांक.value   = priv->imr_data[3].value;

		rc = r820t_f_imr(priv, &imr_poपूर्णांक);
	पूर्ण
	अगर (rc < 0)
		वापस rc;

	/* save IMR value */
	चयन (imr_mem) अणु
	हाल 0:
		priv->imr_data[0].gain_x  = imr_poपूर्णांक.gain_x;
		priv->imr_data[0].phase_y = imr_poपूर्णांक.phase_y;
		priv->imr_data[0].value   = imr_poपूर्णांक.value;
		अवरोध;
	हाल 1:
		priv->imr_data[1].gain_x  = imr_poपूर्णांक.gain_x;
		priv->imr_data[1].phase_y = imr_poपूर्णांक.phase_y;
		priv->imr_data[1].value   = imr_poपूर्णांक.value;
		अवरोध;
	हाल 2:
		priv->imr_data[2].gain_x  = imr_poपूर्णांक.gain_x;
		priv->imr_data[2].phase_y = imr_poपूर्णांक.phase_y;
		priv->imr_data[2].value   = imr_poपूर्णांक.value;
		अवरोध;
	हाल 3:
		priv->imr_data[3].gain_x  = imr_poपूर्णांक.gain_x;
		priv->imr_data[3].phase_y = imr_poपूर्णांक.phase_y;
		priv->imr_data[3].value   = imr_poपूर्णांक.value;
		अवरोध;
	हाल 4:
		priv->imr_data[4].gain_x  = imr_poपूर्णांक.gain_x;
		priv->imr_data[4].phase_y = imr_poपूर्णांक.phase_y;
		priv->imr_data[4].value   = imr_poपूर्णांक.value;
		अवरोध;
	शेष:
		priv->imr_data[4].gain_x  = imr_poपूर्णांक.gain_x;
		priv->imr_data[4].phase_y = imr_poपूर्णांक.phase_y;
		priv->imr_data[4].value   = imr_poपूर्णांक.value;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक r820t_imr_callibrate(काष्ठा r820t_priv *priv)
अणु
	पूर्णांक rc, i;
	पूर्णांक xtal_cap = 0;

	अगर (priv->init_करोne)
		वापस 0;

	/* Detect Xtal capacitance */
	अगर ((priv->cfg->rafael_chip == CHIP_R820T) ||
	    (priv->cfg->rafael_chip == CHIP_R828S) ||
	    (priv->cfg->rafael_chip == CHIP_R820C)) अणु
		priv->xtal_cap_sel = XTAL_HIGH_CAP_0P;
	पूर्ण अन्यथा अणु
		/* Initialize रेजिस्टरs */
		rc = r820t_ग_लिखो(priv, 0x05,
				r820t_init_array, माप(r820t_init_array));
		अगर (rc < 0)
			वापस rc;
		क्रम (i = 0; i < 3; i++) अणु
			rc = r820t_xtal_check(priv);
			अगर (rc < 0)
				वापस rc;
			अगर (!i || rc > xtal_cap)
				xtal_cap = rc;
		पूर्ण
		priv->xtal_cap_sel = xtal_cap;
	पूर्ण

	/*
	 * Disables IMR calibration. That emulates the same behaviour
	 * as what is करोne by rtl-sdr userspace library. Useful क्रम testing
	 */
	अगर (no_imr_cal) अणु
		priv->init_करोne = true;

		वापस 0;
	पूर्ण

	/* Initialize रेजिस्टरs */
	rc = r820t_ग_लिखो(priv, 0x05,
			 r820t_init_array, माप(r820t_init_array));
	अगर (rc < 0)
		वापस rc;

	rc = r820t_imr_prepare(priv);
	अगर (rc < 0)
		वापस rc;

	rc = r820t_imr(priv, 3, true);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_imr(priv, 1, false);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_imr(priv, 0, false);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_imr(priv, 2, false);
	अगर (rc < 0)
		वापस rc;
	rc = r820t_imr(priv, 4, false);
	अगर (rc < 0)
		वापस rc;

	priv->init_करोne = true;
	priv->imr_करोne = true;

	वापस 0;
पूर्ण

#अगर 0
/* Not used, क्रम now */
अटल पूर्णांक r820t_gpio(काष्ठा r820t_priv *priv, bool enable)
अणु
	वापस r820t_ग_लिखो_reg_mask(priv, 0x0f, enable ? 1 : 0, 0x01);
पूर्ण
#पूर्ण_अगर

/*
 *  r820t frontend operations and tuner attach code
 *
 * All driver locks and i2c control are only in this part of the code
 */

अटल पूर्णांक r820t_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा r820t_priv *priv = fe->tuner_priv;
	पूर्णांक rc;

	tuner_dbg("%s:\n", __func__);

	mutex_lock(&priv->lock);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	rc = r820t_imr_callibrate(priv);
	अगर (rc < 0)
		जाओ err;

	/* Initialize रेजिस्टरs */
	rc = r820t_ग_लिखो(priv, 0x05,
			 r820t_init_array, माप(r820t_init_array));

err:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);
	mutex_unlock(&priv->lock);

	अगर (rc < 0)
		tuner_dbg("%s: failed=%d\n", __func__, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक r820t_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा r820t_priv *priv = fe->tuner_priv;
	पूर्णांक rc;

	tuner_dbg("%s:\n", __func__);

	mutex_lock(&priv->lock);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	rc = r820t_standby(priv);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);
	mutex_unlock(&priv->lock);

	tuner_dbg("%s: failed=%d\n", __func__, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक r820t_set_analog_freq(काष्ठा dvb_frontend *fe,
				 काष्ठा analog_parameters *p)
अणु
	काष्ठा r820t_priv *priv = fe->tuner_priv;
	अचिन्हित bw;
	पूर्णांक rc;

	tuner_dbg("%s called\n", __func__);

	/* अगर std is not defined, choose one */
	अगर (!p->std)
		p->std = V4L2_STD_MN;

	अगर ((p->std == V4L2_STD_PAL_M) || (p->std == V4L2_STD_NTSC))
		bw = 6;
	अन्यथा
		bw = 8;

	mutex_lock(&priv->lock);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	rc = generic_set_freq(fe, 62500l * p->frequency, bw,
			      V4L2_TUNER_ANALOG_TV, p->std, SYS_UNDEFINED);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);
	mutex_unlock(&priv->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक r820t_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा r820t_priv *priv = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक rc;
	अचिन्हित bw;

	tuner_dbg("%s: delivery_system=%d frequency=%d bandwidth_hz=%d\n",
		__func__, c->delivery_प्रणाली, c->frequency, c->bandwidth_hz);

	mutex_lock(&priv->lock);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	bw = (c->bandwidth_hz + 500000) / 1000000;
	अगर (!bw)
		bw = 8;

	rc = generic_set_freq(fe, c->frequency, bw,
			      V4L2_TUNER_DIGITAL_TV, 0, c->delivery_प्रणाली);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);
	mutex_unlock(&priv->lock);

	अगर (rc)
		tuner_dbg("%s: failed=%d\n", __func__, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक r820t_संकेत(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा r820t_priv *priv = fe->tuner_priv;
	पूर्णांक rc = 0;

	mutex_lock(&priv->lock);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	अगर (priv->has_lock) अणु
		rc = r820t_पढ़ो_gain(priv);
		अगर (rc < 0)
			जाओ err;

		/* A higher gain at LNA means a lower संकेत strength */
		*strength = (45 - rc) << 4 | 0xff;
		अगर (*strength == 0xff)
			*strength = 0;
	पूर्ण अन्यथा अणु
		*strength = 0;
	पूर्ण

err:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);
	mutex_unlock(&priv->lock);

	tuner_dbg("%s: %s, gain=%d strength=%d\n",
		  __func__,
		  priv->has_lock ? "PLL locked" : "no signal",
		  rc, *strength);

	वापस 0;
पूर्ण

अटल पूर्णांक r820t_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा r820t_priv *priv = fe->tuner_priv;

	tuner_dbg("%s:\n", __func__);

	*frequency = priv->पूर्णांक_freq;

	वापस 0;
पूर्ण

अटल व्योम r820t_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा r820t_priv *priv = fe->tuner_priv;

	tuner_dbg("%s:\n", __func__);

	mutex_lock(&r820t_list_mutex);

	अगर (priv)
		hybrid_tuner_release_state(priv);

	mutex_unlock(&r820t_list_mutex);

	fe->tuner_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops r820t_tuner_ops = अणु
	.info = अणु
		.name             = "Rafael Micro R820T",
		.frequency_min_hz =   42 * MHz,
		.frequency_max_hz = 1002 * MHz,
	पूर्ण,
	.init = r820t_init,
	.release = r820t_release,
	.sleep = r820t_sleep,
	.set_params = r820t_set_params,
	.set_analog_params = r820t_set_analog_freq,
	.get_अगर_frequency = r820t_get_अगर_frequency,
	.get_rf_strength = r820t_संकेत,
पूर्ण;

काष्ठा dvb_frontend *r820t_attach(काष्ठा dvb_frontend *fe,
				  काष्ठा i2c_adapter *i2c,
				  स्थिर काष्ठा r820t_config *cfg)
अणु
	काष्ठा r820t_priv *priv;
	पूर्णांक rc = -ENODEV;
	u8 data[5];
	पूर्णांक instance;

	mutex_lock(&r820t_list_mutex);

	instance = hybrid_tuner_request_state(काष्ठा r820t_priv, priv,
					      hybrid_tuner_instance_list,
					      i2c, cfg->i2c_addr,
					      "r820t");
	चयन (instance) अणु
	हाल 0:
		/* memory allocation failure */
		जाओ err_no_gate;
	हाल 1:
		/* new tuner instance */
		priv->cfg = cfg;

		mutex_init(&priv->lock);

		fe->tuner_priv = priv;
		अवरोध;
	हाल 2:
		/* existing tuner instance */
		fe->tuner_priv = priv;
		अवरोध;
	पूर्ण

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	/* check अगर the tuner is there */
	rc = r820t_पढ़ो(priv, 0x00, data, माप(data));
	अगर (rc < 0)
		जाओ err;

	rc = r820t_sleep(fe);
	अगर (rc < 0)
		जाओ err;

	tuner_info("Rafael Micro r820t successfully identified\n");

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	mutex_unlock(&r820t_list_mutex);

	स_नकल(&fe->ops.tuner_ops, &r820t_tuner_ops,
			माप(काष्ठा dvb_tuner_ops));

	वापस fe;
err:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

err_no_gate:
	mutex_unlock(&r820t_list_mutex);

	pr_info("%s: failed=%d\n", __func__, rc);
	r820t_release(fe);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(r820t_attach);

MODULE_DESCRIPTION("Rafael Micro r820t silicon tuner driver");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_LICENSE("GPL v2");
