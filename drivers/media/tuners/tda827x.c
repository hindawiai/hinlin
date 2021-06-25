<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * (c) 2005 Harपंचांगut Hackmann
 * (c) 2007 Michael Krufky
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/types.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/videodev2.h>

#समावेश "tda827x.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

#घोषणा dprपूर्णांकk(args...) \
	करो अणु					    \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "tda827x: " args); \
	पूर्ण जबतक (0)

काष्ठा tda827x_priv अणु
	पूर्णांक i2c_addr;
	काष्ठा i2c_adapter *i2c_adap;
	काष्ठा tda827x_config *cfg;

	अचिन्हित पूर्णांक sgIF;
	अचिन्हित अक्षर lpsel;

	u32 frequency;
	u32 bandwidth;
पूर्ण;

अटल व्योम tda827x_set_std(काष्ठा dvb_frontend *fe,
			    काष्ठा analog_parameters *params)
अणु
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	अक्षर *mode;

	priv->lpsel = 0;
	अगर (params->std & V4L2_STD_MN) अणु
		priv->sgIF = 92;
		priv->lpsel = 1;
		mode = "MN";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_B) अणु
		priv->sgIF = 108;
		mode = "B";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_GH) अणु
		priv->sgIF = 124;
		mode = "GH";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_PAL_I) अणु
		priv->sgIF = 124;
		mode = "I";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_DK) अणु
		priv->sgIF = 124;
		mode = "DK";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_SECAM_L) अणु
		priv->sgIF = 124;
		mode = "L";
	पूर्ण अन्यथा अगर (params->std & V4L2_STD_SECAM_LC) अणु
		priv->sgIF = 20;
		mode = "LC";
	पूर्ण अन्यथा अणु
		priv->sgIF = 124;
		mode = "xx";
	पूर्ण

	अगर (params->mode == V4L2_TUNER_RADIO) अणु
		priv->sgIF = 88; /* अगर frequency is 5.5 MHz */
		dprपूर्णांकk("setting tda827x to radio FM\n");
	पूर्ण अन्यथा
		dprपूर्णांकk("setting tda827x to system %s\n", mode);
पूर्ण


/* ------------------------------------------------------------------ */

काष्ठा tda827x_data अणु
	u32 lomax;
	u8  spd;
	u8  bs;
	u8  bp;
	u8  cp;
	u8  gc3;
	u8 भाग1p5;
पूर्ण;

अटल स्थिर काष्ठा tda827x_data tda827x_table[] = अणु
	अणु .lomax =  62000000, .spd = 3, .bs = 2, .bp = 0, .cp = 0, .gc3 = 3, .भाग1p5 = 1पूर्ण,
	अणु .lomax =  66000000, .spd = 3, .bs = 3, .bp = 0, .cp = 0, .gc3 = 3, .भाग1p5 = 1पूर्ण,
	अणु .lomax =  76000000, .spd = 3, .bs = 1, .bp = 0, .cp = 0, .gc3 = 3, .भाग1p5 = 0पूर्ण,
	अणु .lomax =  84000000, .spd = 3, .bs = 2, .bp = 0, .cp = 0, .gc3 = 3, .भाग1p5 = 0पूर्ण,
	अणु .lomax =  93000000, .spd = 3, .bs = 2, .bp = 0, .cp = 0, .gc3 = 1, .भाग1p5 = 0पूर्ण,
	अणु .lomax =  98000000, .spd = 3, .bs = 3, .bp = 0, .cp = 0, .gc3 = 1, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 109000000, .spd = 3, .bs = 3, .bp = 1, .cp = 0, .gc3 = 1, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 123000000, .spd = 2, .bs = 2, .bp = 1, .cp = 0, .gc3 = 1, .भाग1p5 = 1पूर्ण,
	अणु .lomax = 133000000, .spd = 2, .bs = 3, .bp = 1, .cp = 0, .gc3 = 1, .भाग1p5 = 1पूर्ण,
	अणु .lomax = 151000000, .spd = 2, .bs = 1, .bp = 1, .cp = 0, .gc3 = 1, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 154000000, .spd = 2, .bs = 2, .bp = 1, .cp = 0, .gc3 = 1, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 181000000, .spd = 2, .bs = 2, .bp = 1, .cp = 0, .gc3 = 0, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 185000000, .spd = 2, .bs = 2, .bp = 2, .cp = 0, .gc3 = 1, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 217000000, .spd = 2, .bs = 3, .bp = 2, .cp = 0, .gc3 = 1, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 244000000, .spd = 1, .bs = 2, .bp = 2, .cp = 0, .gc3 = 1, .भाग1p5 = 1पूर्ण,
	अणु .lomax = 265000000, .spd = 1, .bs = 3, .bp = 2, .cp = 0, .gc3 = 1, .भाग1p5 = 1पूर्ण,
	अणु .lomax = 302000000, .spd = 1, .bs = 1, .bp = 2, .cp = 0, .gc3 = 1, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 324000000, .spd = 1, .bs = 2, .bp = 2, .cp = 0, .gc3 = 1, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 370000000, .spd = 1, .bs = 2, .bp = 3, .cp = 0, .gc3 = 1, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 454000000, .spd = 1, .bs = 3, .bp = 3, .cp = 0, .gc3 = 1, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 493000000, .spd = 0, .bs = 2, .bp = 3, .cp = 0, .gc3 = 1, .भाग1p5 = 1पूर्ण,
	अणु .lomax = 530000000, .spd = 0, .bs = 3, .bp = 3, .cp = 0, .gc3 = 1, .भाग1p5 = 1पूर्ण,
	अणु .lomax = 554000000, .spd = 0, .bs = 1, .bp = 3, .cp = 0, .gc3 = 1, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 604000000, .spd = 0, .bs = 1, .bp = 4, .cp = 0, .gc3 = 0, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 696000000, .spd = 0, .bs = 2, .bp = 4, .cp = 0, .gc3 = 0, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 740000000, .spd = 0, .bs = 2, .bp = 4, .cp = 1, .gc3 = 0, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 820000000, .spd = 0, .bs = 3, .bp = 4, .cp = 0, .gc3 = 0, .भाग1p5 = 0पूर्ण,
	अणु .lomax = 865000000, .spd = 0, .bs = 3, .bp = 4, .cp = 1, .gc3 = 0, .भाग1p5 = 0पूर्ण,
	अणु .lomax =         0, .spd = 0, .bs = 0, .bp = 0, .cp = 0, .gc3 = 0, .भाग1p5 = 0पूर्ण
पूर्ण;

अटल पूर्णांक tuner_transfer(काष्ठा dvb_frontend *fe,
			  काष्ठा i2c_msg *msg,
			  स्थिर पूर्णांक size)
अणु
	पूर्णांक rc;
	काष्ठा tda827x_priv *priv = fe->tuner_priv;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	rc = i2c_transfer(priv->i2c_adap, msg, size);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	अगर (rc >= 0 && rc != size)
		वापस -EIO;

	वापस rc;
पूर्ण

अटल पूर्णांक tda827xo_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	u8 buf[14];
	पूर्णांक rc;

	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_addr, .flags = 0,
			       .buf = buf, .len = माप(buf) पूर्ण;
	पूर्णांक i, tuner_freq, अगर_freq;
	u32 N;

	dprपूर्णांकk("%s:\n", __func__);
	अगर (c->bandwidth_hz == 0) अणु
		अगर_freq = 5000000;
	पूर्ण अन्यथा अगर (c->bandwidth_hz <= 6000000) अणु
		अगर_freq = 4000000;
	पूर्ण अन्यथा अगर (c->bandwidth_hz <= 7000000) अणु
		अगर_freq = 4500000;
	पूर्ण अन्यथा अणु	/* 8 MHz */
		अगर_freq = 5000000;
	पूर्ण
	tuner_freq = c->frequency;

	i = 0;
	जबतक (tda827x_table[i].lomax < tuner_freq) अणु
		अगर (tda827x_table[i + 1].lomax == 0)
			अवरोध;
		i++;
	पूर्ण

	tuner_freq += अगर_freq;

	N = ((tuner_freq + 125000) / 250000) << (tda827x_table[i].spd + 2);
	buf[0] = 0;
	buf[1] = (N>>8) | 0x40;
	buf[2] = N & 0xff;
	buf[3] = 0;
	buf[4] = 0x52;
	buf[5] = (tda827x_table[i].spd << 6) + (tda827x_table[i].भाग1p5 << 5) +
				(tda827x_table[i].bs << 3) +
				tda827x_table[i].bp;
	buf[6] = (tda827x_table[i].gc3 << 4) + 0x8f;
	buf[7] = 0xbf;
	buf[8] = 0x2a;
	buf[9] = 0x05;
	buf[10] = 0xff;
	buf[11] = 0x00;
	buf[12] = 0x00;
	buf[13] = 0x40;

	msg.len = 14;
	rc = tuner_transfer(fe, &msg, 1);
	अगर (rc < 0)
		जाओ err;

	msleep(500);
	/* correct CP value */
	buf[0] = 0x30;
	buf[1] = 0x50 + tda827x_table[i].cp;
	msg.len = 2;

	rc = tuner_transfer(fe, &msg, 1);
	अगर (rc < 0)
		जाओ err;

	priv->frequency = c->frequency;
	priv->bandwidth = c->bandwidth_hz;

	वापस 0;

err:
	prपूर्णांकk(KERN_ERR "%s: could not write to tuner at addr: 0x%02x\n",
	       __func__, priv->i2c_addr << 1);
	वापस rc;
पूर्ण

अटल पूर्णांक tda827xo_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	अटल u8 buf[] = अणु 0x30, 0xd0 पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_addr, .flags = 0,
			       .buf = buf, .len = माप(buf) पूर्ण;

	dprपूर्णांकk("%s:\n", __func__);
	tuner_transfer(fe, &msg, 1);

	अगर (priv->cfg && priv->cfg->sleep)
		priv->cfg->sleep(fe);

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक tda827xo_set_analog_params(काष्ठा dvb_frontend *fe,
				      काष्ठा analog_parameters *params)
अणु
	अचिन्हित अक्षर tuner_reg[8];
	अचिन्हित अक्षर reg2[2];
	u32 N;
	पूर्णांक i;
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_addr, .flags = 0 पूर्ण;
	अचिन्हित पूर्णांक freq = params->frequency;

	tda827x_set_std(fe, params);

	अगर (params->mode == V4L2_TUNER_RADIO)
		freq = freq / 1000;

	N = freq + priv->sgIF;

	i = 0;
	जबतक (tda827x_table[i].lomax < N * 62500) अणु
		अगर (tda827x_table[i + 1].lomax == 0)
			अवरोध;
		i++;
	पूर्ण

	N = N << tda827x_table[i].spd;

	tuner_reg[0] = 0;
	tuner_reg[1] = (अचिन्हित अक्षर)(N>>8);
	tuner_reg[2] = (अचिन्हित अक्षर) N;
	tuner_reg[3] = 0x40;
	tuner_reg[4] = 0x52 + (priv->lpsel << 5);
	tuner_reg[5] = (tda827x_table[i].spd    << 6) +
		       (tda827x_table[i].भाग1p5 << 5) +
		       (tda827x_table[i].bs     << 3) + tda827x_table[i].bp;
	tuner_reg[6] = 0x8f + (tda827x_table[i].gc3 << 4);
	tuner_reg[7] = 0x8f;

	msg.buf = tuner_reg;
	msg.len = 8;
	tuner_transfer(fe, &msg, 1);

	msg.buf = reg2;
	msg.len = 2;
	reg2[0] = 0x80;
	reg2[1] = 0;
	tuner_transfer(fe, &msg, 1);

	reg2[0] = 0x60;
	reg2[1] = 0xbf;
	tuner_transfer(fe, &msg, 1);

	reg2[0] = 0x30;
	reg2[1] = tuner_reg[4] + 0x80;
	tuner_transfer(fe, &msg, 1);

	msleep(1);
	reg2[0] = 0x30;
	reg2[1] = tuner_reg[4] + 4;
	tuner_transfer(fe, &msg, 1);

	msleep(1);
	reg2[0] = 0x30;
	reg2[1] = tuner_reg[4];
	tuner_transfer(fe, &msg, 1);

	msleep(550);
	reg2[0] = 0x30;
	reg2[1] = (tuner_reg[4] & 0xfc) + tda827x_table[i].cp;
	tuner_transfer(fe, &msg, 1);

	reg2[0] = 0x60;
	reg2[1] = 0x3f;
	tuner_transfer(fe, &msg, 1);

	reg2[0] = 0x80;
	reg2[1] = 0x08;   /* Vsync en */
	tuner_transfer(fe, &msg, 1);

	priv->frequency = params->frequency;

	वापस 0;
पूर्ण

अटल व्योम tda827xo_agcf(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर data[] = अणु 0x80, 0x0c पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_addr, .flags = 0,
			       .buf = data, .len = 2पूर्ण;

	tuner_transfer(fe, &msg, 1);
पूर्ण

/* ------------------------------------------------------------------ */

काष्ठा tda827xa_data अणु
	u32 lomax;
	u8  svco;
	u8  spd;
	u8  scr;
	u8  sbs;
	u8  gc3;
पूर्ण;

अटल काष्ठा tda827xa_data tda827xa_dvbt[] = अणु
	अणु .lomax =  56875000, .svco = 3, .spd = 4, .scr = 0, .sbs = 0, .gc3 = 1पूर्ण,
	अणु .lomax =  67250000, .svco = 0, .spd = 3, .scr = 0, .sbs = 0, .gc3 = 1पूर्ण,
	अणु .lomax =  81250000, .svco = 1, .spd = 3, .scr = 0, .sbs = 0, .gc3 = 1पूर्ण,
	अणु .lomax =  97500000, .svco = 2, .spd = 3, .scr = 0, .sbs = 0, .gc3 = 1पूर्ण,
	अणु .lomax = 113750000, .svco = 3, .spd = 3, .scr = 0, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 134500000, .svco = 0, .spd = 2, .scr = 0, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 154000000, .svco = 1, .spd = 2, .scr = 0, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 162500000, .svco = 1, .spd = 2, .scr = 0, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 183000000, .svco = 2, .spd = 2, .scr = 0, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 195000000, .svco = 2, .spd = 2, .scr = 0, .sbs = 2, .gc3 = 1पूर्ण,
	अणु .lomax = 227500000, .svco = 3, .spd = 2, .scr = 0, .sbs = 2, .gc3 = 1पूर्ण,
	अणु .lomax = 269000000, .svco = 0, .spd = 1, .scr = 0, .sbs = 2, .gc3 = 1पूर्ण,
	अणु .lomax = 290000000, .svco = 1, .spd = 1, .scr = 0, .sbs = 2, .gc3 = 1पूर्ण,
	अणु .lomax = 325000000, .svco = 1, .spd = 1, .scr = 0, .sbs = 3, .gc3 = 1पूर्ण,
	अणु .lomax = 390000000, .svco = 2, .spd = 1, .scr = 0, .sbs = 3, .gc3 = 1पूर्ण,
	अणु .lomax = 455000000, .svco = 3, .spd = 1, .scr = 0, .sbs = 3, .gc3 = 1पूर्ण,
	अणु .lomax = 520000000, .svco = 0, .spd = 0, .scr = 0, .sbs = 3, .gc3 = 1पूर्ण,
	अणु .lomax = 538000000, .svco = 0, .spd = 0, .scr = 1, .sbs = 3, .gc3 = 1पूर्ण,
	अणु .lomax = 550000000, .svco = 1, .spd = 0, .scr = 0, .sbs = 3, .gc3 = 1पूर्ण,
	अणु .lomax = 620000000, .svco = 1, .spd = 0, .scr = 0, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax = 650000000, .svco = 1, .spd = 0, .scr = 1, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax = 700000000, .svco = 2, .spd = 0, .scr = 0, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax = 780000000, .svco = 2, .spd = 0, .scr = 1, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax = 820000000, .svco = 3, .spd = 0, .scr = 0, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax = 870000000, .svco = 3, .spd = 0, .scr = 1, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax = 911000000, .svco = 3, .spd = 0, .scr = 2, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax =         0, .svco = 0, .spd = 0, .scr = 0, .sbs = 0, .gc3 = 0पूर्ण
पूर्ण;

अटल काष्ठा tda827xa_data tda827xa_dvbc[] = अणु
	अणु .lomax =  50125000, .svco = 2, .spd = 4, .scr = 2, .sbs = 0, .gc3 = 3पूर्ण,
	अणु .lomax =  58500000, .svco = 3, .spd = 4, .scr = 2, .sbs = 0, .gc3 = 3पूर्ण,
	अणु .lomax =  69250000, .svco = 0, .spd = 3, .scr = 2, .sbs = 0, .gc3 = 3पूर्ण,
	अणु .lomax =  83625000, .svco = 1, .spd = 3, .scr = 2, .sbs = 0, .gc3 = 3पूर्ण,
	अणु .lomax =  97500000, .svco = 2, .spd = 3, .scr = 2, .sbs = 0, .gc3 = 3पूर्ण,
	अणु .lomax = 100250000, .svco = 2, .spd = 3, .scr = 2, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 117000000, .svco = 3, .spd = 3, .scr = 2, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 138500000, .svco = 0, .spd = 2, .scr = 2, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 167250000, .svco = 1, .spd = 2, .scr = 2, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 187000000, .svco = 2, .spd = 2, .scr = 2, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 200500000, .svco = 2, .spd = 2, .scr = 2, .sbs = 2, .gc3 = 1पूर्ण,
	अणु .lomax = 234000000, .svco = 3, .spd = 2, .scr = 2, .sbs = 2, .gc3 = 3पूर्ण,
	अणु .lomax = 277000000, .svco = 0, .spd = 1, .scr = 2, .sbs = 2, .gc3 = 3पूर्ण,
	अणु .lomax = 325000000, .svco = 1, .spd = 1, .scr = 2, .sbs = 2, .gc3 = 1पूर्ण,
	अणु .lomax = 334500000, .svco = 1, .spd = 1, .scr = 2, .sbs = 3, .gc3 = 3पूर्ण,
	अणु .lomax = 401000000, .svco = 2, .spd = 1, .scr = 2, .sbs = 3, .gc3 = 3पूर्ण,
	अणु .lomax = 468000000, .svco = 3, .spd = 1, .scr = 2, .sbs = 3, .gc3 = 1पूर्ण,
	अणु .lomax = 535000000, .svco = 0, .spd = 0, .scr = 1, .sbs = 3, .gc3 = 1पूर्ण,
	अणु .lomax = 554000000, .svco = 0, .spd = 0, .scr = 2, .sbs = 3, .gc3 = 1पूर्ण,
	अणु .lomax = 638000000, .svco = 1, .spd = 0, .scr = 1, .sbs = 4, .gc3 = 1पूर्ण,
	अणु .lomax = 669000000, .svco = 1, .spd = 0, .scr = 2, .sbs = 4, .gc3 = 1पूर्ण,
	अणु .lomax = 720000000, .svco = 2, .spd = 0, .scr = 1, .sbs = 4, .gc3 = 1पूर्ण,
	अणु .lomax = 802000000, .svco = 2, .spd = 0, .scr = 2, .sbs = 4, .gc3 = 1पूर्ण,
	अणु .lomax = 835000000, .svco = 3, .spd = 0, .scr = 1, .sbs = 4, .gc3 = 1पूर्ण,
	अणु .lomax = 885000000, .svco = 3, .spd = 0, .scr = 1, .sbs = 4, .gc3 = 1पूर्ण,
	अणु .lomax = 911000000, .svco = 3, .spd = 0, .scr = 2, .sbs = 4, .gc3 = 1पूर्ण,
	अणु .lomax =         0, .svco = 0, .spd = 0, .scr = 0, .sbs = 0, .gc3 = 0पूर्ण
पूर्ण;

अटल काष्ठा tda827xa_data tda827xa_analog[] = अणु
	अणु .lomax =  56875000, .svco = 3, .spd = 4, .scr = 0, .sbs = 0, .gc3 = 3पूर्ण,
	अणु .lomax =  67250000, .svco = 0, .spd = 3, .scr = 0, .sbs = 0, .gc3 = 3पूर्ण,
	अणु .lomax =  81250000, .svco = 1, .spd = 3, .scr = 0, .sbs = 0, .gc3 = 3पूर्ण,
	अणु .lomax =  97500000, .svco = 2, .spd = 3, .scr = 0, .sbs = 0, .gc3 = 3पूर्ण,
	अणु .lomax = 113750000, .svco = 3, .spd = 3, .scr = 0, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 134500000, .svco = 0, .spd = 2, .scr = 0, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 154000000, .svco = 1, .spd = 2, .scr = 0, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 162500000, .svco = 1, .spd = 2, .scr = 0, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 183000000, .svco = 2, .spd = 2, .scr = 0, .sbs = 1, .gc3 = 1पूर्ण,
	अणु .lomax = 195000000, .svco = 2, .spd = 2, .scr = 0, .sbs = 2, .gc3 = 1पूर्ण,
	अणु .lomax = 227500000, .svco = 3, .spd = 2, .scr = 0, .sbs = 2, .gc3 = 3पूर्ण,
	अणु .lomax = 269000000, .svco = 0, .spd = 1, .scr = 0, .sbs = 2, .gc3 = 3पूर्ण,
	अणु .lomax = 325000000, .svco = 1, .spd = 1, .scr = 0, .sbs = 2, .gc3 = 1पूर्ण,
	अणु .lomax = 390000000, .svco = 2, .spd = 1, .scr = 0, .sbs = 3, .gc3 = 3पूर्ण,
	अणु .lomax = 455000000, .svco = 3, .spd = 1, .scr = 0, .sbs = 3, .gc3 = 3पूर्ण,
	अणु .lomax = 520000000, .svco = 0, .spd = 0, .scr = 0, .sbs = 3, .gc3 = 1पूर्ण,
	अणु .lomax = 538000000, .svco = 0, .spd = 0, .scr = 1, .sbs = 3, .gc3 = 1पूर्ण,
	अणु .lomax = 554000000, .svco = 1, .spd = 0, .scr = 0, .sbs = 3, .gc3 = 1पूर्ण,
	अणु .lomax = 620000000, .svco = 1, .spd = 0, .scr = 0, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax = 650000000, .svco = 1, .spd = 0, .scr = 1, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax = 700000000, .svco = 2, .spd = 0, .scr = 0, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax = 780000000, .svco = 2, .spd = 0, .scr = 1, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax = 820000000, .svco = 3, .spd = 0, .scr = 0, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax = 870000000, .svco = 3, .spd = 0, .scr = 1, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax = 911000000, .svco = 3, .spd = 0, .scr = 2, .sbs = 4, .gc3 = 0पूर्ण,
	अणु .lomax =         0, .svco = 0, .spd = 0, .scr = 0, .sbs = 0, .gc3 = 0पूर्ण
पूर्ण;

अटल पूर्णांक tda827xa_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	अटल u8 buf[] = अणु 0x30, 0x90 पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_addr, .flags = 0,
			       .buf = buf, .len = माप(buf) पूर्ण;

	dprपूर्णांकk("%s:\n", __func__);

	tuner_transfer(fe, &msg, 1);

	अगर (priv->cfg && priv->cfg->sleep)
		priv->cfg->sleep(fe);

	वापस 0;
पूर्ण

अटल व्योम tda827xa_lna_gain(काष्ठा dvb_frontend *fe, पूर्णांक high,
			      काष्ठा analog_parameters *params)
अणु
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर buf[] = अणु0x22, 0x01पूर्ण;
	पूर्णांक arg;
	पूर्णांक gp_func;
	काष्ठा i2c_msg msg = अणु .flags = 0, .buf = buf, .len = माप(buf) पूर्ण;

	अगर (शून्य == priv->cfg) अणु
		dprपूर्णांकk("tda827x_config not defined, cannot set LNA gain!\n");
		वापस;
	पूर्ण
	msg.addr = priv->cfg->चयन_addr;
	अगर (priv->cfg->config) अणु
		अगर (high)
			dprपूर्णांकk("setting LNA to high gain\n");
		अन्यथा
			dprपूर्णांकk("setting LNA to low gain\n");
	पूर्ण
	चयन (priv->cfg->config) अणु
	हाल TDA8290_LNA_OFF: /* no LNA */
		अवरोध;
	हाल TDA8290_LNA_GP0_HIGH_ON: /* चयन is GPIO 0 of tda8290 */
	हाल TDA8290_LNA_GP0_HIGH_OFF:
		अगर (params == शून्य) अणु
			gp_func = 0;
			arg  = 0;
		पूर्ण अन्यथा अणु
			/* turn Vsync on */
			gp_func = 1;
			अगर (params->std & V4L2_STD_MN)
				arg = 1;
			अन्यथा
				arg = 0;
		पूर्ण
		अगर (fe->callback)
			fe->callback(priv->i2c_adap->algo_data,
				     DVB_FRONTEND_COMPONENT_TUNER,
				     gp_func, arg);
		buf[1] = high ? 0 : 1;
		अगर (priv->cfg->config == TDA8290_LNA_GP0_HIGH_OFF)
			buf[1] = high ? 1 : 0;
		tuner_transfer(fe, &msg, 1);
		अवरोध;
	हाल TDA8290_LNA_ON_BRIDGE: /* चयन with GPIO of saa713x */
		अगर (fe->callback)
			fe->callback(priv->i2c_adap->algo_data,
				     DVB_FRONTEND_COMPONENT_TUNER, 0, high);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक tda827xa_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	काष्ठा tda827xa_data *frequency_map = tda827xa_dvbt;
	u8 buf[11];

	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_addr, .flags = 0,
			       .buf = buf, .len = माप(buf) पूर्ण;

	पूर्णांक i, tuner_freq, अगर_freq, rc;
	u32 N;

	dprपूर्णांकk("%s:\n", __func__);

	tda827xa_lna_gain(fe, 1, शून्य);
	msleep(20);

	अगर (c->bandwidth_hz == 0) अणु
		अगर_freq = 5000000;
	पूर्ण अन्यथा अगर (c->bandwidth_hz <= 6000000) अणु
		अगर_freq = 4000000;
	पूर्ण अन्यथा अगर (c->bandwidth_hz <= 7000000) अणु
		अगर_freq = 4500000;
	पूर्ण अन्यथा अणु	/* 8 MHz */
		अगर_freq = 5000000;
	पूर्ण
	tuner_freq = c->frequency;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_C:
		dprपूर्णांकk("%s select tda827xa_dvbc\n", __func__);
		frequency_map = tda827xa_dvbc;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	i = 0;
	जबतक (frequency_map[i].lomax < tuner_freq) अणु
		अगर (frequency_map[i + 1].lomax == 0)
			अवरोध;
		i++;
	पूर्ण

	tuner_freq += अगर_freq;

	N = ((tuner_freq + 31250) / 62500) << frequency_map[i].spd;
	buf[0] = 0;            // subaddress
	buf[1] = N >> 8;
	buf[2] = N & 0xff;
	buf[3] = 0;
	buf[4] = 0x16;
	buf[5] = (frequency_map[i].spd << 5) + (frequency_map[i].svco << 3) +
			frequency_map[i].sbs;
	buf[6] = 0x4b + (frequency_map[i].gc3 << 4);
	buf[7] = 0x1c;
	buf[8] = 0x06;
	buf[9] = 0x24;
	buf[10] = 0x00;
	msg.len = 11;
	rc = tuner_transfer(fe, &msg, 1);
	अगर (rc < 0)
		जाओ err;

	buf[0] = 0x90;
	buf[1] = 0xff;
	buf[2] = 0x60;
	buf[3] = 0x00;
	buf[4] = 0x59;  // lpsel, क्रम 6MHz + 2
	msg.len = 5;
	rc = tuner_transfer(fe, &msg, 1);
	अगर (rc < 0)
		जाओ err;

	buf[0] = 0xa0;
	buf[1] = 0x40;
	msg.len = 2;
	rc = tuner_transfer(fe, &msg, 1);
	अगर (rc < 0)
		जाओ err;

	msleep(11);
	msg.flags = I2C_M_RD;
	rc = tuner_transfer(fe, &msg, 1);
	अगर (rc < 0)
		जाओ err;
	msg.flags = 0;

	buf[1] >>= 4;
	dprपूर्णांकk("tda8275a AGC2 gain is: %d\n", buf[1]);
	अगर ((buf[1]) < 2) अणु
		tda827xa_lna_gain(fe, 0, शून्य);
		buf[0] = 0x60;
		buf[1] = 0x0c;
		rc = tuner_transfer(fe, &msg, 1);
		अगर (rc < 0)
			जाओ err;
	पूर्ण

	buf[0] = 0xc0;
	buf[1] = 0x99;    // lpsel, क्रम 6MHz + 2
	rc = tuner_transfer(fe, &msg, 1);
	अगर (rc < 0)
		जाओ err;

	buf[0] = 0x60;
	buf[1] = 0x3c;
	rc = tuner_transfer(fe, &msg, 1);
	अगर (rc < 0)
		जाओ err;

	/* correct CP value */
	buf[0] = 0x30;
	buf[1] = 0x10 + frequency_map[i].scr;
	rc = tuner_transfer(fe, &msg, 1);
	अगर (rc < 0)
		जाओ err;

	msleep(163);
	buf[0] = 0xc0;
	buf[1] = 0x39;  // lpsel, क्रम 6MHz + 2
	rc = tuner_transfer(fe, &msg, 1);
	अगर (rc < 0)
		जाओ err;

	msleep(3);
	/* मुक्तze AGC1 */
	buf[0] = 0x50;
	buf[1] = 0x4f + (frequency_map[i].gc3 << 4);
	rc = tuner_transfer(fe, &msg, 1);
	अगर (rc < 0)
		जाओ err;

	priv->frequency = c->frequency;
	priv->bandwidth = c->bandwidth_hz;

	वापस 0;

err:
	prपूर्णांकk(KERN_ERR "%s: could not write to tuner at addr: 0x%02x\n",
	       __func__, priv->i2c_addr << 1);
	वापस rc;
पूर्ण


अटल पूर्णांक tda827xa_set_analog_params(काष्ठा dvb_frontend *fe,
				      काष्ठा analog_parameters *params)
अणु
	अचिन्हित अक्षर tuner_reg[11];
	u32 N;
	पूर्णांक i;
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_addr, .flags = 0,
			       .buf = tuner_reg, .len = माप(tuner_reg) पूर्ण;
	अचिन्हित पूर्णांक freq = params->frequency;

	tda827x_set_std(fe, params);

	tda827xa_lna_gain(fe, 1, params);
	msleep(10);

	अगर (params->mode == V4L2_TUNER_RADIO)
		freq = freq / 1000;

	N = freq + priv->sgIF;

	i = 0;
	जबतक (tda827xa_analog[i].lomax < N * 62500) अणु
		अगर (tda827xa_analog[i + 1].lomax == 0)
			अवरोध;
		i++;
	पूर्ण

	N = N << tda827xa_analog[i].spd;

	tuner_reg[0] = 0;
	tuner_reg[1] = (अचिन्हित अक्षर)(N>>8);
	tuner_reg[2] = (अचिन्हित अक्षर) N;
	tuner_reg[3] = 0;
	tuner_reg[4] = 0x16;
	tuner_reg[5] = (tda827xa_analog[i].spd << 5) +
		       (tda827xa_analog[i].svco << 3) +
			tda827xa_analog[i].sbs;
	tuner_reg[6] = 0x8b + (tda827xa_analog[i].gc3 << 4);
	tuner_reg[7] = 0x1c;
	tuner_reg[8] = 4;
	tuner_reg[9] = 0x20;
	tuner_reg[10] = 0x00;
	msg.len = 11;
	tuner_transfer(fe, &msg, 1);

	tuner_reg[0] = 0x90;
	tuner_reg[1] = 0xff;
	tuner_reg[2] = 0xe0;
	tuner_reg[3] = 0;
	tuner_reg[4] = 0x99 + (priv->lpsel << 1);
	msg.len = 5;
	tuner_transfer(fe, &msg, 1);

	tuner_reg[0] = 0xa0;
	tuner_reg[1] = 0xc0;
	msg.len = 2;
	tuner_transfer(fe, &msg, 1);

	tuner_reg[0] = 0x30;
	tuner_reg[1] = 0x10 + tda827xa_analog[i].scr;
	tuner_transfer(fe, &msg, 1);

	msg.flags = I2C_M_RD;
	tuner_transfer(fe, &msg, 1);
	msg.flags = 0;
	tuner_reg[1] >>= 4;
	dprपूर्णांकk("AGC2 gain is: %d\n", tuner_reg[1]);
	अगर (tuner_reg[1] < 1)
		tda827xa_lna_gain(fe, 0, params);

	msleep(100);
	tuner_reg[0] = 0x60;
	tuner_reg[1] = 0x3c;
	tuner_transfer(fe, &msg, 1);

	msleep(163);
	tuner_reg[0] = 0x50;
	tuner_reg[1] = 0x8f + (tda827xa_analog[i].gc3 << 4);
	tuner_transfer(fe, &msg, 1);

	tuner_reg[0] = 0x80;
	tuner_reg[1] = 0x28;
	tuner_transfer(fe, &msg, 1);

	tuner_reg[0] = 0xb0;
	tuner_reg[1] = 0x01;
	tuner_transfer(fe, &msg, 1);

	tuner_reg[0] = 0xc0;
	tuner_reg[1] = 0x19 + (priv->lpsel << 1);
	tuner_transfer(fe, &msg, 1);

	priv->frequency = params->frequency;

	वापस 0;
पूर्ण

अटल व्योम tda827xa_agcf(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर data[] = अणु0x80, 0x2cपूर्ण;
	काष्ठा i2c_msg msg = अणु.addr = priv->i2c_addr, .flags = 0,
			      .buf = data, .len = 2पूर्ण;
	tuner_transfer(fe, &msg, 1);
पूर्ण

/* ------------------------------------------------------------------ */

अटल व्योम tda827x_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक tda827x_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक tda827x_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	*bandwidth = priv->bandwidth;
	वापस 0;
पूर्ण

अटल पूर्णांक tda827x_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	dprपूर्णांकk("%s:\n", __func__);
	अगर (priv->cfg && priv->cfg->init)
		priv->cfg->init(fe);

	वापस 0;
पूर्ण

अटल पूर्णांक tda827x_probe_version(काष्ठा dvb_frontend *fe);

अटल पूर्णांक tda827x_initial_init(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	ret = tda827x_probe_version(fe);
	अगर (ret)
		वापस ret;
	वापस fe->ops.tuner_ops.init(fe);
पूर्ण

अटल पूर्णांक tda827x_initial_sleep(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	ret = tda827x_probe_version(fe);
	अगर (ret)
		वापस ret;
	वापस fe->ops.tuner_ops.sleep(fe);
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tda827xo_tuner_ops = अणु
	.info = अणु
		.name = "Philips TDA827X",
		.frequency_min_hz  =  55 * MHz,
		.frequency_max_hz  = 860 * MHz,
		.frequency_step_hz = 250 * kHz
	पूर्ण,
	.release = tda827x_release,
	.init = tda827x_initial_init,
	.sleep = tda827x_initial_sleep,
	.set_params = tda827xo_set_params,
	.set_analog_params = tda827xo_set_analog_params,
	.get_frequency = tda827x_get_frequency,
	.get_bandwidth = tda827x_get_bandwidth,
पूर्ण;

अटल स्थिर काष्ठा dvb_tuner_ops tda827xa_tuner_ops = अणु
	.info = अणु
		.name = "Philips TDA827XA",
		.frequency_min_hz  =  44 * MHz,
		.frequency_max_hz  = 906 * MHz,
		.frequency_step_hz = 62500
	पूर्ण,
	.release = tda827x_release,
	.init = tda827x_init,
	.sleep = tda827xa_sleep,
	.set_params = tda827xa_set_params,
	.set_analog_params = tda827xa_set_analog_params,
	.get_frequency = tda827x_get_frequency,
	.get_bandwidth = tda827x_get_bandwidth,
पूर्ण;

अटल पूर्णांक tda827x_probe_version(काष्ठा dvb_frontend *fe)
अणु
	u8 data;
	पूर्णांक rc;
	काष्ठा tda827x_priv *priv = fe->tuner_priv;
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_addr, .flags = I2C_M_RD,
			       .buf = &data, .len = 1 पूर्ण;

	rc = tuner_transfer(fe, &msg, 1);

	अगर (rc < 0) अणु
		prपूर्णांकk("%s: could not read from tuner at addr: 0x%02x\n",
		       __func__, msg.addr << 1);
		वापस rc;
	पूर्ण
	अगर ((data & 0x3c) == 0) अणु
		dprपूर्णांकk("tda827x tuner found\n");
		fe->ops.tuner_ops.init  = tda827x_init;
		fe->ops.tuner_ops.sleep = tda827xo_sleep;
		अगर (priv->cfg)
			priv->cfg->agcf = tda827xo_agcf;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("tda827xa tuner found\n");
		स_नकल(&fe->ops.tuner_ops, &tda827xa_tuner_ops, माप(काष्ठा dvb_tuner_ops));
		अगर (priv->cfg)
			priv->cfg->agcf = tda827xa_agcf;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा dvb_frontend *tda827x_attach(काष्ठा dvb_frontend *fe, पूर्णांक addr,
				    काष्ठा i2c_adapter *i2c,
				    काष्ठा tda827x_config *cfg)
अणु
	काष्ठा tda827x_priv *priv = शून्य;

	dprपूर्णांकk("%s:\n", __func__);
	priv = kzalloc(माप(काष्ठा tda827x_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	priv->i2c_addr = addr;
	priv->i2c_adap = i2c;
	priv->cfg = cfg;
	स_नकल(&fe->ops.tuner_ops, &tda827xo_tuner_ops, माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = priv;

	dprपूर्णांकk("type set to %s\n", fe->ops.tuner_ops.info.name);

	वापस fe;
पूर्ण
EXPORT_SYMBOL_GPL(tda827x_attach);

MODULE_DESCRIPTION("DVB TDA827x driver");
MODULE_AUTHOR("Hartmut Hackmann <hartmut.hackmann@t-online.de>");
MODULE_AUTHOR("Michael Krufky <mkrufky@linuxtv.org>");
MODULE_LICENSE("GPL");
