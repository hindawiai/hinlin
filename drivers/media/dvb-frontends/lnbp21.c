<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lnbp21.c - driver क्रम lnb supply and control ic lnbp21
 *
 * Copyright (C) 2006, 2009 Oliver Endriss <o.endriss@gmx.de>
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 *
 * the project's page is at https://linuxtv.org
 */
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "lnbp21.h"
#समावेश "lnbh24.h"

काष्ठा lnbp21 अणु
	u8			config;
	u8			override_or;
	u8			override_and;
	काष्ठा i2c_adapter	*i2c;
	u8			i2c_addr;
पूर्ण;

अटल पूर्णांक lnbp21_set_voltage(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा lnbp21 *lnbp21 = (काष्ठा lnbp21 *) fe->sec_priv;
	काष्ठा i2c_msg msg = अणु	.addr = lnbp21->i2c_addr, .flags = 0,
				.buf = &lnbp21->config,
				.len = माप(lnbp21->config) पूर्ण;

	lnbp21->config &= ~(LNBP21_VSEL | LNBP21_EN);

	चयन(voltage) अणु
	हाल SEC_VOLTAGE_OFF:
		अवरोध;
	हाल SEC_VOLTAGE_13:
		lnbp21->config |= LNBP21_EN;
		अवरोध;
	हाल SEC_VOLTAGE_18:
		lnbp21->config |= (LNBP21_EN | LNBP21_VSEL);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	lnbp21->config |= lnbp21->override_or;
	lnbp21->config &= lnbp21->override_and;

	वापस (i2c_transfer(lnbp21->i2c, &msg, 1) == 1) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक lnbp21_enable_high_lnb_voltage(काष्ठा dvb_frontend *fe, दीर्घ arg)
अणु
	काष्ठा lnbp21 *lnbp21 = (काष्ठा lnbp21 *) fe->sec_priv;
	काष्ठा i2c_msg msg = अणु	.addr = lnbp21->i2c_addr, .flags = 0,
				.buf = &lnbp21->config,
				.len = माप(lnbp21->config) पूर्ण;

	अगर (arg)
		lnbp21->config |= LNBP21_LLC;
	अन्यथा
		lnbp21->config &= ~LNBP21_LLC;

	lnbp21->config |= lnbp21->override_or;
	lnbp21->config &= lnbp21->override_and;

	वापस (i2c_transfer(lnbp21->i2c, &msg, 1) == 1) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक lnbp21_set_tone(काष्ठा dvb_frontend *fe,
			   क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा lnbp21 *lnbp21 = (काष्ठा lnbp21 *) fe->sec_priv;
	काष्ठा i2c_msg msg = अणु	.addr = lnbp21->i2c_addr, .flags = 0,
				.buf = &lnbp21->config,
				.len = माप(lnbp21->config) पूर्ण;

	चयन (tone) अणु
	हाल SEC_TONE_OFF:
		lnbp21->config &= ~LNBP21_TEN;
		अवरोध;
	हाल SEC_TONE_ON:
		lnbp21->config |= LNBP21_TEN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	lnbp21->config |= lnbp21->override_or;
	lnbp21->config &= lnbp21->override_and;

	वापस (i2c_transfer(lnbp21->i2c, &msg, 1) == 1) ? 0 : -EIO;
पूर्ण

अटल व्योम lnbp21_release(काष्ठा dvb_frontend *fe)
अणु
	/* LNBP घातer off */
	lnbp21_set_voltage(fe, SEC_VOLTAGE_OFF);

	/* मुक्त data */
	kमुक्त(fe->sec_priv);
	fe->sec_priv = शून्य;
पूर्ण

अटल काष्ठा dvb_frontend *lnbx2x_attach(काष्ठा dvb_frontend *fe,
				काष्ठा i2c_adapter *i2c, u8 override_set,
				u8 override_clear, u8 i2c_addr, u8 config)
अणु
	काष्ठा lnbp21 *lnbp21 = kदो_स्मृति(माप(काष्ठा lnbp21), GFP_KERNEL);
	अगर (!lnbp21)
		वापस शून्य;

	/* शेष configuration */
	lnbp21->config = config;
	lnbp21->i2c = i2c;
	lnbp21->i2c_addr = i2c_addr;
	fe->sec_priv = lnbp21;

	/* bits which should be क्रमced to '1' */
	lnbp21->override_or = override_set;

	/* bits which should be क्रमced to '0' */
	lnbp21->override_and = ~override_clear;

	/* detect अगर it is present or not */
	अगर (lnbp21_set_voltage(fe, SEC_VOLTAGE_OFF)) अणु
		kमुक्त(lnbp21);
		वापस शून्य;
	पूर्ण

	/* install release callback */
	fe->ops.release_sec = lnbp21_release;

	/* override frontend ops */
	fe->ops.set_voltage = lnbp21_set_voltage;
	fe->ops.enable_high_lnb_voltage = lnbp21_enable_high_lnb_voltage;
	अगर (!(override_clear & LNBH24_TEN)) /*22kHz logic controlled by demod*/
		fe->ops.set_tone = lnbp21_set_tone;
	prपूर्णांकk(KERN_INFO "LNBx2x attached on addr=%x\n", lnbp21->i2c_addr);

	वापस fe;
पूर्ण

काष्ठा dvb_frontend *lnbh24_attach(काष्ठा dvb_frontend *fe,
				काष्ठा i2c_adapter *i2c, u8 override_set,
				u8 override_clear, u8 i2c_addr)
अणु
	वापस lnbx2x_attach(fe, i2c, override_set, override_clear,
							i2c_addr, LNBH24_TTX);
पूर्ण
EXPORT_SYMBOL(lnbh24_attach);

काष्ठा dvb_frontend *lnbp21_attach(काष्ठा dvb_frontend *fe,
				काष्ठा i2c_adapter *i2c, u8 override_set,
				u8 override_clear)
अणु
	वापस lnbx2x_attach(fe, i2c, override_set, override_clear,
							0x08, LNBP21_ISEL);
पूर्ण
EXPORT_SYMBOL(lnbp21_attach);

MODULE_DESCRIPTION("Driver for lnb supply and control ic lnbp21, lnbh24");
MODULE_AUTHOR("Oliver Endriss, Igor M. Liplianin");
MODULE_LICENSE("GPL");
