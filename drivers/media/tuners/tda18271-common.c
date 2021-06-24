<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    tda18271-common.c - driver क्रम the Philips / NXP TDA18271 silicon tuner

    Copyright (C) 2007, 2008 Michael Krufky <mkrufky@linuxtv.org>

*/

#समावेश "tda18271-priv.h"

अटल पूर्णांक tda18271_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	क्रमागत tda18271_i2c_gate gate;
	पूर्णांक ret = 0;

	चयन (priv->gate) अणु
	हाल TDA18271_GATE_DIGITAL:
	हाल TDA18271_GATE_ANALOG:
		gate = priv->gate;
		अवरोध;
	हाल TDA18271_GATE_AUTO:
	शेष:
		चयन (priv->mode) अणु
		हाल TDA18271_DIGITAL:
			gate = TDA18271_GATE_DIGITAL;
			अवरोध;
		हाल TDA18271_ANALOG:
		शेष:
			gate = TDA18271_GATE_ANALOG;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (gate) अणु
	हाल TDA18271_GATE_ANALOG:
		अगर (fe->ops.analog_ops.i2c_gate_ctrl)
			ret = fe->ops.analog_ops.i2c_gate_ctrl(fe, enable);
		अवरोध;
	हाल TDA18271_GATE_DIGITAL:
		अगर (fe->ops.i2c_gate_ctrl)
			ret = fe->ops.i2c_gate_ctrl(fe, enable);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण;

/*---------------------------------------------------------------------*/

अटल व्योम tda18271_dump_regs(काष्ठा dvb_frontend *fe, पूर्णांक extended)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;

	tda_reg("=== TDA18271 REG DUMP ===\n");
	tda_reg("ID_BYTE            = 0x%02x\n", 0xff & regs[R_ID]);
	tda_reg("THERMO_BYTE        = 0x%02x\n", 0xff & regs[R_TM]);
	tda_reg("POWER_LEVEL_BYTE   = 0x%02x\n", 0xff & regs[R_PL]);
	tda_reg("EASY_PROG_BYTE_1   = 0x%02x\n", 0xff & regs[R_EP1]);
	tda_reg("EASY_PROG_BYTE_2   = 0x%02x\n", 0xff & regs[R_EP2]);
	tda_reg("EASY_PROG_BYTE_3   = 0x%02x\n", 0xff & regs[R_EP3]);
	tda_reg("EASY_PROG_BYTE_4   = 0x%02x\n", 0xff & regs[R_EP4]);
	tda_reg("EASY_PROG_BYTE_5   = 0x%02x\n", 0xff & regs[R_EP5]);
	tda_reg("CAL_POST_DIV_BYTE  = 0x%02x\n", 0xff & regs[R_CPD]);
	tda_reg("CAL_DIV_BYTE_1     = 0x%02x\n", 0xff & regs[R_CD1]);
	tda_reg("CAL_DIV_BYTE_2     = 0x%02x\n", 0xff & regs[R_CD2]);
	tda_reg("CAL_DIV_BYTE_3     = 0x%02x\n", 0xff & regs[R_CD3]);
	tda_reg("MAIN_POST_DIV_BYTE = 0x%02x\n", 0xff & regs[R_MPD]);
	tda_reg("MAIN_DIV_BYTE_1    = 0x%02x\n", 0xff & regs[R_MD1]);
	tda_reg("MAIN_DIV_BYTE_2    = 0x%02x\n", 0xff & regs[R_MD2]);
	tda_reg("MAIN_DIV_BYTE_3    = 0x%02x\n", 0xff & regs[R_MD3]);

	/* only dump extended regs अगर DBG_ADV is set */
	अगर (!(tda18271_debug & DBG_ADV))
		वापस;

	/* W indicates ग_लिखो-only रेजिस्टरs.
	 * Register dump क्रम ग_लिखो-only रेजिस्टरs shows last value written. */

	tda_reg("EXTENDED_BYTE_1    = 0x%02x\n", 0xff & regs[R_EB1]);
	tda_reg("EXTENDED_BYTE_2    = 0x%02x\n", 0xff & regs[R_EB2]);
	tda_reg("EXTENDED_BYTE_3    = 0x%02x\n", 0xff & regs[R_EB3]);
	tda_reg("EXTENDED_BYTE_4    = 0x%02x\n", 0xff & regs[R_EB4]);
	tda_reg("EXTENDED_BYTE_5    = 0x%02x\n", 0xff & regs[R_EB5]);
	tda_reg("EXTENDED_BYTE_6    = 0x%02x\n", 0xff & regs[R_EB6]);
	tda_reg("EXTENDED_BYTE_7    = 0x%02x\n", 0xff & regs[R_EB7]);
	tda_reg("EXTENDED_BYTE_8    = 0x%02x\n", 0xff & regs[R_EB8]);
	tda_reg("EXTENDED_BYTE_9  W = 0x%02x\n", 0xff & regs[R_EB9]);
	tda_reg("EXTENDED_BYTE_10   = 0x%02x\n", 0xff & regs[R_EB10]);
	tda_reg("EXTENDED_BYTE_11   = 0x%02x\n", 0xff & regs[R_EB11]);
	tda_reg("EXTENDED_BYTE_12   = 0x%02x\n", 0xff & regs[R_EB12]);
	tda_reg("EXTENDED_BYTE_13   = 0x%02x\n", 0xff & regs[R_EB13]);
	tda_reg("EXTENDED_BYTE_14   = 0x%02x\n", 0xff & regs[R_EB14]);
	tda_reg("EXTENDED_BYTE_15   = 0x%02x\n", 0xff & regs[R_EB15]);
	tda_reg("EXTENDED_BYTE_16 W = 0x%02x\n", 0xff & regs[R_EB16]);
	tda_reg("EXTENDED_BYTE_17 W = 0x%02x\n", 0xff & regs[R_EB17]);
	tda_reg("EXTENDED_BYTE_18   = 0x%02x\n", 0xff & regs[R_EB18]);
	tda_reg("EXTENDED_BYTE_19 W = 0x%02x\n", 0xff & regs[R_EB19]);
	tda_reg("EXTENDED_BYTE_20 W = 0x%02x\n", 0xff & regs[R_EB20]);
	tda_reg("EXTENDED_BYTE_21   = 0x%02x\n", 0xff & regs[R_EB21]);
	tda_reg("EXTENDED_BYTE_22   = 0x%02x\n", 0xff & regs[R_EB22]);
	tda_reg("EXTENDED_BYTE_23   = 0x%02x\n", 0xff & regs[R_EB23]);
पूर्ण

पूर्णांक tda18271_पढ़ो_regs(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	अचिन्हित अक्षर buf = 0x00;
	पूर्णांक ret;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = priv->i2c_props.addr, .flags = 0,
		  .buf = &buf, .len = 1 पूर्ण,
		अणु .addr = priv->i2c_props.addr, .flags = I2C_M_RD,
		  .buf = regs, .len = 16 पूर्ण
	पूर्ण;

	tda18271_i2c_gate_ctrl(fe, 1);

	/* पढ़ो all रेजिस्टरs */
	ret = i2c_transfer(priv->i2c_props.adap, msg, 2);

	tda18271_i2c_gate_ctrl(fe, 0);

	अगर (ret != 2)
		tda_err("ERROR: i2c_transfer returned: %d\n", ret);

	अगर (tda18271_debug & DBG_REG)
		tda18271_dump_regs(fe, 0);

	वापस (ret == 2 ? 0 : ret);
पूर्ण

पूर्णांक tda18271_पढ़ो_extended(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	अचिन्हित अक्षर regdump[TDA18271_NUM_REGS];
	अचिन्हित अक्षर buf = 0x00;
	पूर्णांक ret, i;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = priv->i2c_props.addr, .flags = 0,
		  .buf = &buf, .len = 1 पूर्ण,
		अणु .addr = priv->i2c_props.addr, .flags = I2C_M_RD,
		  .buf = regdump, .len = TDA18271_NUM_REGS पूर्ण
	पूर्ण;

	tda18271_i2c_gate_ctrl(fe, 1);

	/* पढ़ो all रेजिस्टरs */
	ret = i2c_transfer(priv->i2c_props.adap, msg, 2);

	tda18271_i2c_gate_ctrl(fe, 0);

	अगर (ret != 2)
		tda_err("ERROR: i2c_transfer returned: %d\n", ret);

	क्रम (i = 0; i < TDA18271_NUM_REGS; i++) अणु
		/* करोn't update ग_लिखो-only रेजिस्टरs */
		अगर ((i != R_EB9)  &&
		    (i != R_EB16) &&
		    (i != R_EB17) &&
		    (i != R_EB19) &&
		    (i != R_EB20))
			regs[i] = regdump[i];
	पूर्ण

	अगर (tda18271_debug & DBG_REG)
		tda18271_dump_regs(fe, 1);

	वापस (ret == 2 ? 0 : ret);
पूर्ण

अटल पूर्णांक __tda18271_ग_लिखो_regs(काष्ठा dvb_frontend *fe, पूर्णांक idx, पूर्णांक len,
			bool lock_i2c)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	अचिन्हित अक्षर buf[TDA18271_NUM_REGS + 1];
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_props.addr, .flags = 0,
			       .buf = buf पूर्ण;
	पूर्णांक i, ret = 1, max;

	BUG_ON((len == 0) || (idx + len > माप(buf)));

	चयन (priv->small_i2c) अणु
	हाल TDA18271_03_BYTE_CHUNK_INIT:
		max = 3;
		अवरोध;
	हाल TDA18271_08_BYTE_CHUNK_INIT:
		max = 8;
		अवरोध;
	हाल TDA18271_16_BYTE_CHUNK_INIT:
		max = 16;
		अवरोध;
	हाल TDA18271_39_BYTE_CHUNK_INIT:
	शेष:
		max = 39;
	पूर्ण


	/*
	 * If lock_i2c is true, it will take the I2C bus क्रम tda18271 निजी
	 * usage during the entire ग_लिखो ops, as otherwise, bad things could
	 * happen.
	 * During device init, several ग_लिखो operations will happen. So,
	 * tda18271_init_regs controls the I2C lock directly,
	 * disabling lock_i2c here.
	 */
	अगर (lock_i2c) अणु
		tda18271_i2c_gate_ctrl(fe, 1);
		i2c_lock_bus(priv->i2c_props.adap, I2C_LOCK_SEGMENT);
	पूर्ण
	जबतक (len) अणु
		अगर (max > len)
			max = len;

		buf[0] = idx;
		क्रम (i = 1; i <= max; i++)
			buf[i] = regs[idx - 1 + i];

		msg.len = max + 1;

		/* ग_लिखो रेजिस्टरs */
		ret = __i2c_transfer(priv->i2c_props.adap, &msg, 1);
		अगर (ret != 1)
			अवरोध;

		idx += max;
		len -= max;
	पूर्ण
	अगर (lock_i2c) अणु
		i2c_unlock_bus(priv->i2c_props.adap, I2C_LOCK_SEGMENT);
		tda18271_i2c_gate_ctrl(fe, 0);
	पूर्ण

	अगर (ret != 1)
		tda_err("ERROR: idx = 0x%x, len = %d, i2c_transfer returned: %d\n",
			idx, max, ret);

	वापस (ret == 1 ? 0 : ret);
पूर्ण

पूर्णांक tda18271_ग_लिखो_regs(काष्ठा dvb_frontend *fe, पूर्णांक idx, पूर्णांक len)
अणु
	वापस __tda18271_ग_लिखो_regs(fe, idx, len, true);
पूर्ण

/*---------------------------------------------------------------------*/

अटल पूर्णांक __tda18271_अक्षरge_pump_source(काष्ठा dvb_frontend *fe,
					 क्रमागत tda18271_pll pll, पूर्णांक क्रमce,
					 bool lock_i2c)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;

	पूर्णांक r_cp = (pll == TDA18271_CAL_PLL) ? R_EB7 : R_EB4;

	regs[r_cp] &= ~0x20;
	regs[r_cp] |= ((क्रमce & 1) << 5);

	वापस __tda18271_ग_लिखो_regs(fe, r_cp, 1, lock_i2c);
पूर्ण

पूर्णांक tda18271_अक्षरge_pump_source(काष्ठा dvb_frontend *fe,
				क्रमागत tda18271_pll pll, पूर्णांक क्रमce)
अणु
	वापस __tda18271_अक्षरge_pump_source(fe, pll, क्रमce, true);
पूर्ण


पूर्णांक tda18271_init_regs(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;

	tda_dbg("initializing registers for device @ %d-%04x\n",
		i2c_adapter_id(priv->i2c_props.adap),
		priv->i2c_props.addr);

	/*
	 * Don't let any other I2C transfer to happen at adapter during init,
	 * as those could cause bad things
	 */
	tda18271_i2c_gate_ctrl(fe, 1);
	i2c_lock_bus(priv->i2c_props.adap, I2C_LOCK_SEGMENT);

	/* initialize रेजिस्टरs */
	चयन (priv->id) अणु
	हाल TDA18271HDC1:
		regs[R_ID]   = 0x83;
		अवरोध;
	हाल TDA18271HDC2:
		regs[R_ID]   = 0x84;
		अवरोध;
	पूर्ण

	regs[R_TM]   = 0x08;
	regs[R_PL]   = 0x80;
	regs[R_EP1]  = 0xc6;
	regs[R_EP2]  = 0xdf;
	regs[R_EP3]  = 0x16;
	regs[R_EP4]  = 0x60;
	regs[R_EP5]  = 0x80;
	regs[R_CPD]  = 0x80;
	regs[R_CD1]  = 0x00;
	regs[R_CD2]  = 0x00;
	regs[R_CD3]  = 0x00;
	regs[R_MPD]  = 0x00;
	regs[R_MD1]  = 0x00;
	regs[R_MD2]  = 0x00;
	regs[R_MD3]  = 0x00;

	चयन (priv->id) अणु
	हाल TDA18271HDC1:
		regs[R_EB1]  = 0xff;
		अवरोध;
	हाल TDA18271HDC2:
		regs[R_EB1]  = 0xfc;
		अवरोध;
	पूर्ण

	regs[R_EB2]  = 0x01;
	regs[R_EB3]  = 0x84;
	regs[R_EB4]  = 0x41;
	regs[R_EB5]  = 0x01;
	regs[R_EB6]  = 0x84;
	regs[R_EB7]  = 0x40;
	regs[R_EB8]  = 0x07;
	regs[R_EB9]  = 0x00;
	regs[R_EB10] = 0x00;
	regs[R_EB11] = 0x96;

	चयन (priv->id) अणु
	हाल TDA18271HDC1:
		regs[R_EB12] = 0x0f;
		अवरोध;
	हाल TDA18271HDC2:
		regs[R_EB12] = 0x33;
		अवरोध;
	पूर्ण

	regs[R_EB13] = 0xc1;
	regs[R_EB14] = 0x00;
	regs[R_EB15] = 0x8f;
	regs[R_EB16] = 0x00;
	regs[R_EB17] = 0x00;

	चयन (priv->id) अणु
	हाल TDA18271HDC1:
		regs[R_EB18] = 0x00;
		अवरोध;
	हाल TDA18271HDC2:
		regs[R_EB18] = 0x8c;
		अवरोध;
	पूर्ण

	regs[R_EB19] = 0x00;
	regs[R_EB20] = 0x20;

	चयन (priv->id) अणु
	हाल TDA18271HDC1:
		regs[R_EB21] = 0x33;
		अवरोध;
	हाल TDA18271HDC2:
		regs[R_EB21] = 0xb3;
		अवरोध;
	पूर्ण

	regs[R_EB22] = 0x48;
	regs[R_EB23] = 0xb0;

	__tda18271_ग_लिखो_regs(fe, 0x00, TDA18271_NUM_REGS, false);

	/* setup agc1 gain */
	regs[R_EB17] = 0x00;
	__tda18271_ग_लिखो_regs(fe, R_EB17, 1, false);
	regs[R_EB17] = 0x03;
	__tda18271_ग_लिखो_regs(fe, R_EB17, 1, false);
	regs[R_EB17] = 0x43;
	__tda18271_ग_लिखो_regs(fe, R_EB17, 1, false);
	regs[R_EB17] = 0x4c;
	__tda18271_ग_लिखो_regs(fe, R_EB17, 1, false);

	/* setup agc2 gain */
	अगर ((priv->id) == TDA18271HDC1) अणु
		regs[R_EB20] = 0xa0;
		__tda18271_ग_लिखो_regs(fe, R_EB20, 1, false);
		regs[R_EB20] = 0xa7;
		__tda18271_ग_लिखो_regs(fe, R_EB20, 1, false);
		regs[R_EB20] = 0xe7;
		__tda18271_ग_लिखो_regs(fe, R_EB20, 1, false);
		regs[R_EB20] = 0xec;
		__tda18271_ग_लिखो_regs(fe, R_EB20, 1, false);
	पूर्ण

	/* image rejection calibration */

	/* low-band */
	regs[R_EP3] = 0x1f;
	regs[R_EP4] = 0x66;
	regs[R_EP5] = 0x81;
	regs[R_CPD] = 0xcc;
	regs[R_CD1] = 0x6c;
	regs[R_CD2] = 0x00;
	regs[R_CD3] = 0x00;
	regs[R_MPD] = 0xcd;
	regs[R_MD1] = 0x77;
	regs[R_MD2] = 0x08;
	regs[R_MD3] = 0x00;

	__tda18271_ग_लिखो_regs(fe, R_EP3, 11, false);

	अगर ((priv->id) == TDA18271HDC2) अणु
		/* मुख्य pll cp source on */
		__tda18271_अक्षरge_pump_source(fe, TDA18271_MAIN_PLL, 1, false);
		msleep(1);

		/* मुख्य pll cp source off */
		__tda18271_अक्षरge_pump_source(fe, TDA18271_MAIN_PLL, 0, false);
	पूर्ण

	msleep(5); /* pll locking */

	/* launch detector */
	__tda18271_ग_लिखो_regs(fe, R_EP1, 1, false);
	msleep(5); /* wanted low measurement */

	regs[R_EP5] = 0x85;
	regs[R_CPD] = 0xcb;
	regs[R_CD1] = 0x66;
	regs[R_CD2] = 0x70;

	__tda18271_ग_लिखो_regs(fe, R_EP3, 7, false);
	msleep(5); /* pll locking */

	/* launch optimization algorithm */
	__tda18271_ग_लिखो_regs(fe, R_EP2, 1, false);
	msleep(30); /* image low optimization completion */

	/* mid-band */
	regs[R_EP5] = 0x82;
	regs[R_CPD] = 0xa8;
	regs[R_CD2] = 0x00;
	regs[R_MPD] = 0xa9;
	regs[R_MD1] = 0x73;
	regs[R_MD2] = 0x1a;

	__tda18271_ग_लिखो_regs(fe, R_EP3, 11, false);
	msleep(5); /* pll locking */

	/* launch detector */
	__tda18271_ग_लिखो_regs(fe, R_EP1, 1, false);
	msleep(5); /* wanted mid measurement */

	regs[R_EP5] = 0x86;
	regs[R_CPD] = 0xa8;
	regs[R_CD1] = 0x66;
	regs[R_CD2] = 0xa0;

	__tda18271_ग_लिखो_regs(fe, R_EP3, 7, false);
	msleep(5); /* pll locking */

	/* launch optimization algorithm */
	__tda18271_ग_लिखो_regs(fe, R_EP2, 1, false);
	msleep(30); /* image mid optimization completion */

	/* high-band */
	regs[R_EP5] = 0x83;
	regs[R_CPD] = 0x98;
	regs[R_CD1] = 0x65;
	regs[R_CD2] = 0x00;
	regs[R_MPD] = 0x99;
	regs[R_MD1] = 0x71;
	regs[R_MD2] = 0xcd;

	__tda18271_ग_लिखो_regs(fe, R_EP3, 11, false);
	msleep(5); /* pll locking */

	/* launch detector */
	__tda18271_ग_लिखो_regs(fe, R_EP1, 1, false);
	msleep(5); /* wanted high measurement */

	regs[R_EP5] = 0x87;
	regs[R_CD1] = 0x65;
	regs[R_CD2] = 0x50;

	__tda18271_ग_लिखो_regs(fe, R_EP3, 7, false);
	msleep(5); /* pll locking */

	/* launch optimization algorithm */
	__tda18271_ग_लिखो_regs(fe, R_EP2, 1, false);
	msleep(30); /* image high optimization completion */

	/* वापस to normal mode */
	regs[R_EP4] = 0x64;
	__tda18271_ग_लिखो_regs(fe, R_EP4, 1, false);

	/* synchronize */
	__tda18271_ग_लिखो_regs(fe, R_EP1, 1, false);

	i2c_unlock_bus(priv->i2c_props.adap, I2C_LOCK_SEGMENT);
	tda18271_i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------*/

/*
 *  Standby modes, EP3 [7:5]
 *
 *  | SM  || SM_LT || SM_XT || mode description
 *  |=====\\=======\\=======\\====================================
 *  |  0  ||   0   ||   0   || normal mode
 *  |-----||-------||-------||------------------------------------
 *  |     ||       ||       || standby mode w/ slave tuner output
 *  |  1  ||   0   ||   0   || & loop through & xtal oscillator on
 *  |-----||-------||-------||------------------------------------
 *  |  1  ||   1   ||   0   || standby mode w/ xtal oscillator on
 *  |-----||-------||-------||------------------------------------
 *  |  1  ||   1   ||   1   || घातer off
 *
 */

पूर्णांक tda18271_set_standby_mode(काष्ठा dvb_frontend *fe,
			      पूर्णांक sm, पूर्णांक sm_lt, पूर्णांक sm_xt)
अणु
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;

	अगर (tda18271_debug & DBG_ADV)
		tda_dbg("sm = %d, sm_lt = %d, sm_xt = %d\n", sm, sm_lt, sm_xt);

	regs[R_EP3]  &= ~0xe0; /* clear sm, sm_lt, sm_xt */
	regs[R_EP3]  |= (sm    ? (1 << 7) : 0) |
			(sm_lt ? (1 << 6) : 0) |
			(sm_xt ? (1 << 5) : 0);

	वापस tda18271_ग_लिखो_regs(fe, R_EP3, 1);
पूर्ण

/*---------------------------------------------------------------------*/

पूर्णांक tda18271_calc_मुख्य_pll(काष्ठा dvb_frontend *fe, u32 freq)
अणु
	/* sets मुख्य post भागider & भागider bytes, but करोes not ग_लिखो them */
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	u8 d, pd;
	u32 भाग;

	पूर्णांक ret = tda18271_lookup_pll_map(fe, MAIN_PLL, &freq, &pd, &d);
	अगर (tda_fail(ret))
		जाओ fail;

	regs[R_MPD]   = (0x7f & pd);

	भाग =  ((d * (freq / 1000)) << 7) / 125;

	regs[R_MD1]   = 0x7f & (भाग >> 16);
	regs[R_MD2]   = 0xff & (भाग >> 8);
	regs[R_MD3]   = 0xff & भाग;
fail:
	वापस ret;
पूर्ण

पूर्णांक tda18271_calc_cal_pll(काष्ठा dvb_frontend *fe, u32 freq)
अणु
	/* sets cal post भागider & भागider bytes, but करोes not ग_लिखो them */
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	u8 d, pd;
	u32 भाग;

	पूर्णांक ret = tda18271_lookup_pll_map(fe, CAL_PLL, &freq, &pd, &d);
	अगर (tda_fail(ret))
		जाओ fail;

	regs[R_CPD]   = pd;

	भाग =  ((d * (freq / 1000)) << 7) / 125;

	regs[R_CD1]   = 0x7f & (भाग >> 16);
	regs[R_CD2]   = 0xff & (भाग >> 8);
	regs[R_CD3]   = 0xff & भाग;
fail:
	वापस ret;
पूर्ण

/*---------------------------------------------------------------------*/

पूर्णांक tda18271_calc_bp_filter(काष्ठा dvb_frontend *fe, u32 *freq)
अणु
	/* sets bp filter bits, but करोes not ग_लिखो them */
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	u8 val;

	पूर्णांक ret = tda18271_lookup_map(fe, BP_FILTER, freq, &val);
	अगर (tda_fail(ret))
		जाओ fail;

	regs[R_EP1]  &= ~0x07; /* clear bp filter bits */
	regs[R_EP1]  |= (0x07 & val);
fail:
	वापस ret;
पूर्ण

पूर्णांक tda18271_calc_km(काष्ठा dvb_frontend *fe, u32 *freq)
अणु
	/* sets K & M bits, but करोes not ग_लिखो them */
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	u8 val;

	पूर्णांक ret = tda18271_lookup_map(fe, RF_CAL_KMCO, freq, &val);
	अगर (tda_fail(ret))
		जाओ fail;

	regs[R_EB13] &= ~0x7c; /* clear k & m bits */
	regs[R_EB13] |= (0x7c & val);
fail:
	वापस ret;
पूर्ण

पूर्णांक tda18271_calc_rf_band(काष्ठा dvb_frontend *fe, u32 *freq)
अणु
	/* sets rf band bits, but करोes not ग_लिखो them */
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	u8 val;

	पूर्णांक ret = tda18271_lookup_map(fe, RF_BAND, freq, &val);
	अगर (tda_fail(ret))
		जाओ fail;

	regs[R_EP2]  &= ~0xe0; /* clear rf band bits */
	regs[R_EP2]  |= (0xe0 & (val << 5));
fail:
	वापस ret;
पूर्ण

पूर्णांक tda18271_calc_gain_taper(काष्ठा dvb_frontend *fe, u32 *freq)
अणु
	/* sets gain taper bits, but करोes not ग_लिखो them */
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	u8 val;

	पूर्णांक ret = tda18271_lookup_map(fe, GAIN_TAPER, freq, &val);
	अगर (tda_fail(ret))
		जाओ fail;

	regs[R_EP2]  &= ~0x1f; /* clear gain taper bits */
	regs[R_EP2]  |= (0x1f & val);
fail:
	वापस ret;
पूर्ण

पूर्णांक tda18271_calc_ir_measure(काष्ठा dvb_frontend *fe, u32 *freq)
अणु
	/* sets IR Meas bits, but करोes not ग_लिखो them */
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	u8 val;

	पूर्णांक ret = tda18271_lookup_map(fe, IR_MEASURE, freq, &val);
	अगर (tda_fail(ret))
		जाओ fail;

	regs[R_EP5] &= ~0x07;
	regs[R_EP5] |= (0x07 & val);
fail:
	वापस ret;
पूर्ण

पूर्णांक tda18271_calc_rf_cal(काष्ठा dvb_frontend *fe, u32 *freq)
अणु
	/* sets rf cal byte (RFC_Cprog), but करोes not ग_लिखो it */
	काष्ठा tda18271_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर *regs = priv->tda18271_regs;
	u8 val;

	पूर्णांक ret = tda18271_lookup_map(fe, RF_CAL, freq, &val);
	/* The TDA18271HD/C1 rf_cal map lookup is expected to go out of range
	 * क्रम frequencies above 61.1 MHz.  In these हालs, the पूर्णांकernal RF
	 * tracking filters calibration mechanism is used.
	 *
	 * There is no need to warn the user about this.
	 */
	अगर (ret < 0)
		जाओ fail;

	regs[R_EB14] = val;
fail:
	वापस ret;
पूर्ण

व्योम _tda_prपूर्णांकk(काष्ठा tda18271_priv *state, स्थिर अक्षर *level,
		 स्थिर अक्षर *func, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (state)
		prपूर्णांकk("%s%s: [%d-%04x|%c] %pV",
		       level, func, i2c_adapter_id(state->i2c_props.adap),
		       state->i2c_props.addr,
		       (state->role == TDA18271_MASTER) ? 'M' : 'S',
		       &vaf);
	अन्यथा
		prपूर्णांकk("%s%s: %pV", level, func, &vaf);

	बहु_पूर्ण(args);
पूर्ण
