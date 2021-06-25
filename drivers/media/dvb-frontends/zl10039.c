<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Zarlink ZL10039 DVB-S tuner
 *
 *  Copyright 2007 Jan D. Louw <jd.louw@mweb.co.za>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/dvb/frontend.h>

#समावेश <media/dvb_frontend.h>
#समावेश "zl10039.h"

अटल पूर्णांक debug;

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) \
			prपूर्णांकk(KERN_DEBUG args); \
	पूर्ण जबतक (0)

क्रमागत zl10039_model_id अणु
	ID_ZL10039 = 1
पूर्ण;

काष्ठा zl10039_state अणु
	काष्ठा i2c_adapter *i2c;
	u8 i2c_addr;
	u8 id;
पूर्ण;

क्रमागत zl10039_reg_addr अणु
	PLL0 = 0,
	PLL1,
	PLL2,
	PLL3,
	RFFE,
	BASE0,
	BASE1,
	BASE2,
	LO0,
	LO1,
	LO2,
	LO3,
	LO4,
	LO5,
	LO6,
	GENERAL
पूर्ण;

अटल पूर्णांक zl10039_पढ़ो(स्थिर काष्ठा zl10039_state *state,
			स्थिर क्रमागत zl10039_reg_addr reg, u8 *buf,
			स्थिर माप_प्रकार count)
अणु
	u8 regbuf[] = अणु reg पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु/* Write रेजिस्टर address */
			.addr = state->i2c_addr,
			.flags = 0,
			.buf = regbuf,
			.len = 1,
		पूर्ण, अणु/* Read count bytes */
			.addr = state->i2c_addr,
			.flags = I2C_M_RD,
			.buf = buf,
			.len = count,
		पूर्ण,
	पूर्ण;

	dprपूर्णांकk("%s\n", __func__);

	अगर (i2c_transfer(state->i2c, msg, 2) != 2) अणु
		dprपूर्णांकk("%s: i2c read error\n", __func__);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0; /* Success */
पूर्ण

अटल पूर्णांक zl10039_ग_लिखो(काष्ठा zl10039_state *state,
			स्थिर क्रमागत zl10039_reg_addr reg, स्थिर u8 *src,
			स्थिर माप_प्रकार count)
अणु
	u8 buf[MAX_XFER_SIZE];
	काष्ठा i2c_msg msg = अणु
		.addr = state->i2c_addr,
		.flags = 0,
		.buf = buf,
		.len = count + 1,
	पूर्ण;

	अगर (1 + count > माप(buf)) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: i2c wr reg=%04x: len=%zu is too big!\n",
		       KBUILD_MODNAME, reg, count);
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk("%s\n", __func__);
	/* Write रेजिस्टर address and data in one go */
	buf[0] = reg;
	स_नकल(&buf[1], src, count);
	अगर (i2c_transfer(state->i2c, &msg, 1) != 1) अणु
		dprपूर्णांकk("%s: i2c write error\n", __func__);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0; /* Success */
पूर्ण

अटल अंतरभूत पूर्णांक zl10039_पढ़ोreg(काष्ठा zl10039_state *state,
				स्थिर क्रमागत zl10039_reg_addr reg, u8 *val)
अणु
	वापस zl10039_पढ़ो(state, reg, val, 1);
पूर्ण

अटल अंतरभूत पूर्णांक zl10039_ग_लिखोreg(काष्ठा zl10039_state *state,
				स्थिर क्रमागत zl10039_reg_addr reg,
				स्थिर u8 val)
अणु
	स्थिर u8 पंचांगp = val; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	वापस zl10039_ग_लिखो(state, reg, &पंचांगp, 1);
पूर्ण

अटल पूर्णांक zl10039_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा zl10039_state *state = fe->tuner_priv;
	पूर्णांक ret;

	dprपूर्णांकk("%s\n", __func__);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	/* Reset logic */
	ret = zl10039_ग_लिखोreg(state, GENERAL, 0x40);
	अगर (ret < 0) अणु
		dprपूर्णांकk("Note: i2c write error normal when resetting the tuner\n");
	पूर्ण
	/* Wake up */
	ret = zl10039_ग_लिखोreg(state, GENERAL, 0x01);
	अगर (ret < 0) अणु
		dprपूर्णांकk("Tuner power up failed\n");
		वापस ret;
	पूर्ण
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक zl10039_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा zl10039_state *state = fe->tuner_priv;
	पूर्णांक ret;

	dprपूर्णांकk("%s\n", __func__);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	ret = zl10039_ग_लिखोreg(state, GENERAL, 0x80);
	अगर (ret < 0) अणु
		dprपूर्णांकk("Tuner sleep failed\n");
		वापस ret;
	पूर्ण
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक zl10039_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा zl10039_state *state = fe->tuner_priv;
	u8 buf[6];
	u8 bf;
	u32 fbw;
	u32 भाग;
	पूर्णांक ret;

	dprपूर्णांकk("%s\n", __func__);
	dprपूर्णांकk("Set frequency = %d, symbol rate = %d\n",
			c->frequency, c->symbol_rate);

	/* Assumed 10.111 MHz crystal oscillator */
	/* Cancelled num/den 80 to prevent overflow */
	भाग = (c->frequency * 1000) / 126387;
	fbw = (c->symbol_rate * 27) / 32000;
	/* Cancelled num/den 10 to prevent overflow */
	bf = ((fbw * 5088) / 1011100) - 1;

	/*PLL भागider*/
	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = (भाग >> 0) & 0xff;
	/*Reference भागider*/
	/* Select reference ratio of 80 */
	buf[2] = 0x1D;
	/*PLL test modes*/
	buf[3] = 0x40;
	/*RF Control रेजिस्टर*/
	buf[4] = 0x6E; /* Bypass enable */
	/*Baseband filter cutoff */
	buf[5] = bf;

	/* Open i2c gate */
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	/* BR = 10, Enable filter adjusपंचांगent */
	ret = zl10039_ग_लिखोreg(state, BASE1, 0x0A);
	अगर (ret < 0)
		जाओ error;
	/* Write new config values */
	ret = zl10039_ग_लिखो(state, PLL0, buf, माप(buf));
	अगर (ret < 0)
		जाओ error;
	/* BR = 10, Disable filter adjusपंचांगent */
	ret = zl10039_ग_लिखोreg(state, BASE1, 0x6A);
	अगर (ret < 0)
		जाओ error;

	/* Close i2c gate */
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);
	वापस 0;
error:
	dprपूर्णांकk("Error setting tuner\n");
	वापस ret;
पूर्ण

अटल व्योम zl10039_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा zl10039_state *state = fe->tuner_priv;

	dprपूर्णांकk("%s\n", __func__);
	kमुक्त(state);
	fe->tuner_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops zl10039_ops = अणु
	.release = zl10039_release,
	.init = zl10039_init,
	.sleep = zl10039_sleep,
	.set_params = zl10039_set_params,
पूर्ण;

काष्ठा dvb_frontend *zl10039_attach(काष्ठा dvb_frontend *fe,
		u8 i2c_addr, काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा zl10039_state *state = शून्य;

	dprपूर्णांकk("%s\n", __func__);
	state = kदो_स्मृति(माप(काष्ठा zl10039_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	state->i2c = i2c;
	state->i2c_addr = i2c_addr;

	/* Open i2c gate */
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	/* check अगर this is a valid tuner */
	अगर (zl10039_पढ़ोreg(state, GENERAL, &state->id) < 0) अणु
		/* Close i2c gate */
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
		जाओ error;
	पूर्ण
	/* Close i2c gate */
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	state->id = state->id & 0x0f;
	चयन (state->id) अणु
	हाल ID_ZL10039:
		strscpy(fe->ops.tuner_ops.info.name,
			"Zarlink ZL10039 DVB-S tuner",
			माप(fe->ops.tuner_ops.info.name));
		अवरोध;
	शेष:
		dprपूर्णांकk("Chip ID=%x does not match a known type\n", state->id);
		जाओ error;
	पूर्ण

	स_नकल(&fe->ops.tuner_ops, &zl10039_ops, माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = state;
	dprपूर्णांकk("Tuner attached @ i2c address 0x%02x\n", i2c_addr);
	वापस fe;
error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(zl10039_attach);

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");
MODULE_DESCRIPTION("Zarlink ZL10039 DVB-S tuner driver");
MODULE_AUTHOR("Jan D. Louw <jd.louw@mweb.co.za>");
MODULE_LICENSE("GPL");
