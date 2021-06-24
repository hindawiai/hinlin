<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Freescale MC44S803 Low Power CMOS Broadband Tuner
 *
 *  Copyright (c) 2009 Jochen Friedrich <jochen@scram.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>

#समावेश "mc44s803.h"
#समावेश "mc44s803_priv.h"

#घोषणा mc_prपूर्णांकk(level, क्रमmat, arg...)	\
	prपूर्णांकk(level "mc44s803: " क्रमmat , ## arg)

/* Writes a single रेजिस्टर */
अटल पूर्णांक mc44s803_ग_लिखोreg(काष्ठा mc44s803_priv *priv, u32 val)
अणु
	u8 buf[3];
	काष्ठा i2c_msg msg = अणु
		.addr = priv->cfg->i2c_address, .flags = 0, .buf = buf, .len = 3
	पूर्ण;

	buf[0] = (val & 0xff0000) >> 16;
	buf[1] = (val & 0xff00) >> 8;
	buf[2] = (val & 0xff);

	अगर (i2c_transfer(priv->i2c, &msg, 1) != 1) अणु
		mc_prपूर्णांकk(KERN_WARNING, "I2C write failed\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

/* Reads a single रेजिस्टर */
अटल पूर्णांक mc44s803_पढ़ोreg(काष्ठा mc44s803_priv *priv, u8 reg, u32 *val)
अणु
	u32 wval;
	u8 buf[3];
	पूर्णांक ret;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = priv->cfg->i2c_address, .flags = I2C_M_RD,
		  .buf = buf, .len = 3 पूर्ण,
	पूर्ण;

	wval = MC44S803_REG_SM(MC44S803_REG_DATAREG, MC44S803_ADDR) |
	       MC44S803_REG_SM(reg, MC44S803_D);

	ret = mc44s803_ग_लिखोreg(priv, wval);
	अगर (ret)
		वापस ret;

	अगर (i2c_transfer(priv->i2c, msg, 1) != 1) अणु
		mc_prपूर्णांकk(KERN_WARNING, "I2C read failed\n");
		वापस -EREMOTEIO;
	पूर्ण

	*val = (buf[0] << 16) | (buf[1] << 8) | buf[2];

	वापस 0;
पूर्ण

अटल व्योम mc44s803_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mc44s803_priv *priv = fe->tuner_priv;

	fe->tuner_priv = शून्य;
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक mc44s803_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mc44s803_priv *priv = fe->tuner_priv;
	u32 val;
	पूर्णांक err;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

/* Reset chip */
	val = MC44S803_REG_SM(MC44S803_REG_RESET, MC44S803_ADDR) |
	      MC44S803_REG_SM(1, MC44S803_RS);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

	val = MC44S803_REG_SM(MC44S803_REG_RESET, MC44S803_ADDR);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

/* Power Up and Start Osc */

	val = MC44S803_REG_SM(MC44S803_REG_REFOSC, MC44S803_ADDR) |
	      MC44S803_REG_SM(0xC0, MC44S803_REFOSC) |
	      MC44S803_REG_SM(1, MC44S803_OSCSEL);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

	val = MC44S803_REG_SM(MC44S803_REG_POWER, MC44S803_ADDR) |
	      MC44S803_REG_SM(0x200, MC44S803_POWER);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

	msleep(10);

	val = MC44S803_REG_SM(MC44S803_REG_REFOSC, MC44S803_ADDR) |
	      MC44S803_REG_SM(0x40, MC44S803_REFOSC) |
	      MC44S803_REG_SM(1, MC44S803_OSCSEL);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

	msleep(20);

/* Setup Mixer */

	val = MC44S803_REG_SM(MC44S803_REG_MIXER, MC44S803_ADDR) |
	      MC44S803_REG_SM(1, MC44S803_TRI_STATE) |
	      MC44S803_REG_SM(0x7F, MC44S803_MIXER_RES);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

/* Setup Cirquit Adjust */

	val = MC44S803_REG_SM(MC44S803_REG_CIRCADJ, MC44S803_ADDR) |
	      MC44S803_REG_SM(1, MC44S803_G1) |
	      MC44S803_REG_SM(1, MC44S803_G3) |
	      MC44S803_REG_SM(0x3, MC44S803_CIRCADJ_RES) |
	      MC44S803_REG_SM(1, MC44S803_G6) |
	      MC44S803_REG_SM(priv->cfg->dig_out, MC44S803_S1) |
	      MC44S803_REG_SM(0x3, MC44S803_LP) |
	      MC44S803_REG_SM(1, MC44S803_CLRF) |
	      MC44S803_REG_SM(1, MC44S803_CLIF);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

	val = MC44S803_REG_SM(MC44S803_REG_CIRCADJ, MC44S803_ADDR) |
	      MC44S803_REG_SM(1, MC44S803_G1) |
	      MC44S803_REG_SM(1, MC44S803_G3) |
	      MC44S803_REG_SM(0x3, MC44S803_CIRCADJ_RES) |
	      MC44S803_REG_SM(1, MC44S803_G6) |
	      MC44S803_REG_SM(priv->cfg->dig_out, MC44S803_S1) |
	      MC44S803_REG_SM(0x3, MC44S803_LP);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

/* Setup Digtune */

	val = MC44S803_REG_SM(MC44S803_REG_DIGTUNE, MC44S803_ADDR) |
	      MC44S803_REG_SM(3, MC44S803_XOD);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

/* Setup AGC */

	val = MC44S803_REG_SM(MC44S803_REG_LNAAGC, MC44S803_ADDR) |
	      MC44S803_REG_SM(1, MC44S803_AT1) |
	      MC44S803_REG_SM(1, MC44S803_AT2) |
	      MC44S803_REG_SM(1, MC44S803_AGC_AN_DIG) |
	      MC44S803_REG_SM(1, MC44S803_AGC_READ_EN) |
	      MC44S803_REG_SM(1, MC44S803_LNA0);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);
	वापस 0;

निकास:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	mc_prपूर्णांकk(KERN_WARNING, "I/O Error\n");
	वापस err;
पूर्ण

अटल पूर्णांक mc44s803_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mc44s803_priv *priv = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 r1, r2, n1, n2, lo1, lo2, freq, val;
	पूर्णांक err;

	priv->frequency = c->frequency;

	r1 = MC44S803_OSC / 1000000;
	r2 = MC44S803_OSC /  100000;

	n1 = (c->frequency + MC44S803_IF1 + 500000) / 1000000;
	freq = MC44S803_OSC / r1 * n1;
	lo1 = ((60 * n1) + (r1 / 2)) / r1;
	freq = freq - c->frequency;

	n2 = (freq - MC44S803_IF2 + 50000) / 100000;
	lo2 = ((60 * n2) + (r2 / 2)) / r2;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	val = MC44S803_REG_SM(MC44S803_REG_REFDIV, MC44S803_ADDR) |
	      MC44S803_REG_SM(r1-1, MC44S803_R1) |
	      MC44S803_REG_SM(r2-1, MC44S803_R2) |
	      MC44S803_REG_SM(1, MC44S803_REFBUF_EN);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

	val = MC44S803_REG_SM(MC44S803_REG_LO1, MC44S803_ADDR) |
	      MC44S803_REG_SM(n1-2, MC44S803_LO1);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

	val = MC44S803_REG_SM(MC44S803_REG_LO2, MC44S803_ADDR) |
	      MC44S803_REG_SM(n2-2, MC44S803_LO2);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

	val = MC44S803_REG_SM(MC44S803_REG_DIGTUNE, MC44S803_ADDR) |
	      MC44S803_REG_SM(1, MC44S803_DA) |
	      MC44S803_REG_SM(lo1, MC44S803_LO_REF) |
	      MC44S803_REG_SM(1, MC44S803_AT);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

	val = MC44S803_REG_SM(MC44S803_REG_DIGTUNE, MC44S803_ADDR) |
	      MC44S803_REG_SM(2, MC44S803_DA) |
	      MC44S803_REG_SM(lo2, MC44S803_LO_REF) |
	      MC44S803_REG_SM(1, MC44S803_AT);

	err = mc44s803_ग_लिखोreg(priv, val);
	अगर (err)
		जाओ निकास;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस 0;

निकास:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	mc_prपूर्णांकk(KERN_WARNING, "I/O Error\n");
	वापस err;
पूर्ण

अटल पूर्णांक mc44s803_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा mc44s803_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक mc44s803_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	*frequency = MC44S803_IF2; /* 36.125 MHz */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops mc44s803_tuner_ops = अणु
	.info = अणु
		.name              = "Freescale MC44S803",
		.frequency_min_hz  =   48 * MHz,
		.frequency_max_hz  = 1000 * MHz,
		.frequency_step_hz =  100 * kHz,
	पूर्ण,

	.release       = mc44s803_release,
	.init          = mc44s803_init,
	.set_params    = mc44s803_set_params,
	.get_frequency = mc44s803_get_frequency,
	.get_अगर_frequency = mc44s803_get_अगर_frequency,
पूर्ण;

/* This functions tries to identअगरy a MC44S803 tuner by पढ़ोing the ID
   रेजिस्टर. This is hasty. */
काष्ठा dvb_frontend *mc44s803_attach(काष्ठा dvb_frontend *fe,
	 काष्ठा i2c_adapter *i2c, काष्ठा mc44s803_config *cfg)
अणु
	काष्ठा mc44s803_priv *priv;
	u32 reg;
	u8 id;
	पूर्णांक ret;

	reg = 0;

	priv = kzalloc(माप(काष्ठा mc44s803_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	priv->cfg = cfg;
	priv->i2c = i2c;
	priv->fe  = fe;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो i2c_gate */

	ret = mc44s803_पढ़ोreg(priv, MC44S803_REG_ID, &reg);
	अगर (ret)
		जाओ error;

	id = MC44S803_REG_MS(reg, MC44S803_ID);

	अगर (id != 0x14) अणु
		mc_prपूर्णांकk(KERN_ERR, "unsupported ID (%x should be 0x14)\n",
			  id);
		जाओ error;
	पूर्ण

	mc_prपूर्णांकk(KERN_INFO, "successfully identified (ID = %x)\n", id);
	स_नकल(&fe->ops.tuner_ops, &mc44s803_tuner_ops,
	       माप(काष्ठा dvb_tuner_ops));

	fe->tuner_priv = priv;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद i2c_gate */

	वापस fe;

error:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद i2c_gate */

	kमुक्त(priv);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mc44s803_attach);

MODULE_AUTHOR("Jochen Friedrich");
MODULE_DESCRIPTION("Freescale MC44S803 silicon tuner driver");
MODULE_LICENSE("GPL");
