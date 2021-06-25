<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * isl6405.c - driver क्रम dual lnb supply and control ic ISL6405
 *
 * Copyright (C) 2008 Harपंचांगut Hackmann
 * Copyright (C) 2006 Oliver Endriss
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
#समावेश "isl6405.h"

काष्ठा isl6405 अणु
	u8			config;
	u8			override_or;
	u8			override_and;
	काष्ठा i2c_adapter	*i2c;
	u8			i2c_addr;
पूर्ण;

अटल पूर्णांक isl6405_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा isl6405 *isl6405 = (काष्ठा isl6405 *) fe->sec_priv;
	काष्ठा i2c_msg msg = अणु	.addr = isl6405->i2c_addr, .flags = 0,
				.buf = &isl6405->config,
				.len = माप(isl6405->config) पूर्ण;

	अगर (isl6405->override_or & 0x80) अणु
		isl6405->config &= ~(ISL6405_VSEL2 | ISL6405_EN2);
		चयन (voltage) अणु
		हाल SEC_VOLTAGE_OFF:
			अवरोध;
		हाल SEC_VOLTAGE_13:
			isl6405->config |= ISL6405_EN2;
			अवरोध;
		हाल SEC_VOLTAGE_18:
			isl6405->config |= (ISL6405_EN2 | ISL6405_VSEL2);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		isl6405->config &= ~(ISL6405_VSEL1 | ISL6405_EN1);
		चयन (voltage) अणु
		हाल SEC_VOLTAGE_OFF:
			अवरोध;
		हाल SEC_VOLTAGE_13:
			isl6405->config |= ISL6405_EN1;
			अवरोध;
		हाल SEC_VOLTAGE_18:
			isl6405->config |= (ISL6405_EN1 | ISL6405_VSEL1);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	isl6405->config |= isl6405->override_or;
	isl6405->config &= isl6405->override_and;

	वापस (i2c_transfer(isl6405->i2c, &msg, 1) == 1) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक isl6405_enable_high_lnb_voltage(काष्ठा dvb_frontend *fe, दीर्घ arg)
अणु
	काष्ठा isl6405 *isl6405 = (काष्ठा isl6405 *) fe->sec_priv;
	काष्ठा i2c_msg msg = अणु	.addr = isl6405->i2c_addr, .flags = 0,
				.buf = &isl6405->config,
				.len = माप(isl6405->config) पूर्ण;

	अगर (isl6405->override_or & 0x80) अणु
		अगर (arg)
			isl6405->config |= ISL6405_LLC2;
		अन्यथा
			isl6405->config &= ~ISL6405_LLC2;
	पूर्ण अन्यथा अणु
		अगर (arg)
			isl6405->config |= ISL6405_LLC1;
		अन्यथा
			isl6405->config &= ~ISL6405_LLC1;
	पूर्ण
	isl6405->config |= isl6405->override_or;
	isl6405->config &= isl6405->override_and;

	वापस (i2c_transfer(isl6405->i2c, &msg, 1) == 1) ? 0 : -EIO;
पूर्ण

अटल व्योम isl6405_release(काष्ठा dvb_frontend *fe)
अणु
	/* घातer off */
	isl6405_set_voltage(fe, SEC_VOLTAGE_OFF);

	/* मुक्त */
	kमुक्त(fe->sec_priv);
	fe->sec_priv = शून्य;
पूर्ण

काष्ठा dvb_frontend *isl6405_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c,
				    u8 i2c_addr, u8 override_set, u8 override_clear)
अणु
	काष्ठा isl6405 *isl6405 = kदो_स्मृति(माप(काष्ठा isl6405), GFP_KERNEL);
	अगर (!isl6405)
		वापस शून्य;

	/* शेष configuration */
	अगर (override_set & 0x80)
		isl6405->config = ISL6405_ISEL2;
	अन्यथा
		isl6405->config = ISL6405_ISEL1;
	isl6405->i2c = i2c;
	isl6405->i2c_addr = i2c_addr;
	fe->sec_priv = isl6405;

	/* bits which should be क्रमced to '1' */
	isl6405->override_or = override_set;

	/* bits which should be क्रमced to '0' */
	isl6405->override_and = ~override_clear;

	/* detect अगर it is present or not */
	अगर (isl6405_set_voltage(fe, SEC_VOLTAGE_OFF)) अणु
		kमुक्त(isl6405);
		fe->sec_priv = शून्य;
		वापस शून्य;
	पूर्ण

	/* install release callback */
	fe->ops.release_sec = isl6405_release;

	/* override frontend ops */
	fe->ops.set_voltage = isl6405_set_voltage;
	fe->ops.enable_high_lnb_voltage = isl6405_enable_high_lnb_voltage;

	वापस fe;
पूर्ण
EXPORT_SYMBOL(isl6405_attach);

MODULE_DESCRIPTION("Driver for lnb supply and control ic isl6405");
MODULE_AUTHOR("Hartmut Hackmann & Oliver Endriss");
MODULE_LICENSE("GPL");
