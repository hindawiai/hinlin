<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Infineon tua6100 pll.
 *
 * (c) 2006 Andrew de Quincey
 *
 * Based on code found in budget-av.c, which has the following:
 * Compiled from various sources by Michael Hunold <michael@mihu.de>
 *
 * CI पूर्णांकerface support (c) 2004 Olivier Gournet <ogournet@anevia.com> &
 *                               Andrew de Quincey <adq_dvb@lidskialf.net>
 *
 * Copyright (C) 2002 Ralph Metzler <rjkm@metzlerbros.de>
 *
 * Copyright (C) 1999-2002 Ralph  Metzler
 *                       & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <यंत्र/types.h>

#समावेश "tua6100.h"

काष्ठा tua6100_priv अणु
	/* i2c details */
	पूर्णांक i2c_address;
	काष्ठा i2c_adapter *i2c;
	u32 frequency;
पूर्ण;

अटल व्योम tua6100_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक tua6100_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tua6100_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	u8 reg0[] = अणु 0x00, 0x00 पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_address, .flags = 0, .buf = reg0, .len = 2 पूर्ण;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर ((ret = i2c_transfer (priv->i2c, &msg, 1)) != 1) अणु
		prपूर्णांकk("%s: i2c error\n", __func__);
	पूर्ण
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस (ret == 1) ? 0 : ret;
पूर्ण

अटल पूर्णांक tua6100_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा tua6100_priv *priv = fe->tuner_priv;
	u32 भाग;
	u32 preभाग;
	u8 reg0[] = अणु 0x00, 0x00 पूर्ण;
	u8 reg1[] = अणु 0x01, 0x00, 0x00, 0x00 पूर्ण;
	u8 reg2[] = अणु 0x02, 0x00, 0x00 पूर्ण;
	काष्ठा i2c_msg msg0 = अणु .addr = priv->i2c_address, .flags = 0, .buf = reg0, .len = 2 पूर्ण;
	काष्ठा i2c_msg msg1 = अणु .addr = priv->i2c_address, .flags = 0, .buf = reg1, .len = 4 पूर्ण;
	काष्ठा i2c_msg msg2 = अणु .addr = priv->i2c_address, .flags = 0, .buf = reg2, .len = 3 पूर्ण;

#घोषणा _R_VAL 4
#घोषणा _P_VAL 32
#घोषणा _ri 4000000

	// setup रेजिस्टर 0
	अगर (c->frequency < 2000000)
		reg0[1] = 0x03;
	अन्यथा
		reg0[1] = 0x07;

	// setup रेजिस्टर 1
	अगर (c->frequency < 1630000)
		reg1[1] = 0x2c;
	अन्यथा
		reg1[1] = 0x0c;

	अगर (_P_VAL == 64)
		reg1[1] |= 0x40;
	अगर (c->frequency >= 1525000)
		reg1[1] |= 0x80;

	// रेजिस्टर 2
	reg2[1] = (_R_VAL >> 8) & 0x03;
	reg2[2] = _R_VAL;
	अगर (c->frequency < 1455000)
		reg2[1] |= 0x1c;
	अन्यथा अगर (c->frequency < 1630000)
		reg2[1] |= 0x0c;
	अन्यथा
		reg2[1] |= 0x1c;

	/*
	 * The N भागisor ratio (note: c->frequency is in kHz, but we
	 * need it in Hz)
	 */
	preभाग = (c->frequency * _R_VAL) / (_ri / 1000);
	भाग = preभाग / _P_VAL;
	reg1[1] |= (भाग >> 9) & 0x03;
	reg1[2] = भाग >> 1;
	reg1[3] = (भाग << 7);
	priv->frequency = ((भाग * _P_VAL) * (_ri / 1000)) / _R_VAL;

	// Finally, calculate and store the value क्रम A
	reg1[3] |= (preभाग - (भाग*_P_VAL)) & 0x7f;

#अघोषित _R_VAL
#अघोषित _P_VAL
#अघोषित _ri

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(priv->i2c, &msg0, 1) != 1)
		वापस -EIO;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(priv->i2c, &msg2, 1) != 1)
		वापस -EIO;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(priv->i2c, &msg1, 1) != 1)
		वापस -EIO;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tua6100_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tua6100_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tua6100_tuner_ops = अणु
	.info = अणु
		.name = "Infineon TUA6100",
		.frequency_min_hz  =  950 * MHz,
		.frequency_max_hz  = 2150 * MHz,
		.frequency_step_hz =    1 * MHz,
	पूर्ण,
	.release = tua6100_release,
	.sleep = tua6100_sleep,
	.set_params = tua6100_set_params,
	.get_frequency = tua6100_get_frequency,
पूर्ण;

काष्ठा dvb_frontend *tua6100_attach(काष्ठा dvb_frontend *fe, पूर्णांक addr, काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा tua6100_priv *priv = शून्य;
	u8 b1 [] = अणु 0x80 पूर्ण;
	u8 b2 [] = अणु 0x00 पूर्ण;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = addr, .flags = 0, .buf = b1, .len = 1 पूर्ण,
				  अणु .addr = addr, .flags = I2C_M_RD, .buf = b2, .len = 1 पूर्ण पूर्ण;
	पूर्णांक ret;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	ret = i2c_transfer (i2c, msg, 2);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	अगर (ret != 2)
		वापस शून्य;

	priv = kzalloc(माप(काष्ठा tua6100_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	priv->i2c_address = addr;
	priv->i2c = i2c;

	स_नकल(&fe->ops.tuner_ops, &tua6100_tuner_ops, माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = priv;
	वापस fe;
पूर्ण
EXPORT_SYMBOL(tua6100_attach);

MODULE_DESCRIPTION("DVB tua6100 driver");
MODULE_AUTHOR("Andrew de Quincey");
MODULE_LICENSE("GPL");
