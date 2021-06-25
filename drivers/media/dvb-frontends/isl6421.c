<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * isl6421.h - driver क्रम lnb supply and control ic ISL6421
 *
 * Copyright (C) 2006 Andrew de Quincey
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
#समावेश "isl6421.h"

काष्ठा isl6421 अणु
	u8			config;
	u8			override_or;
	u8			override_and;
	काष्ठा i2c_adapter	*i2c;
	u8			i2c_addr;
	bool			is_off;
पूर्ण;

अटल पूर्णांक isl6421_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	पूर्णांक ret;
	u8 buf;
	bool is_off;
	काष्ठा isl6421 *isl6421 = (काष्ठा isl6421 *) fe->sec_priv;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
		  .addr = isl6421->i2c_addr,
		  .flags = 0,
		  .buf = &isl6421->config,
		  .len = 1,
		पूर्ण, अणु
		  .addr = isl6421->i2c_addr,
		  .flags = I2C_M_RD,
		  .buf = &buf,
		  .len = 1,
		पूर्ण

	पूर्ण;

	isl6421->config &= ~(ISL6421_VSEL1 | ISL6421_EN1);

	चयन(voltage) अणु
	हाल SEC_VOLTAGE_OFF:
		is_off = true;
		अवरोध;
	हाल SEC_VOLTAGE_13:
		is_off = false;
		isl6421->config |= ISL6421_EN1;
		अवरोध;
	हाल SEC_VOLTAGE_18:
		is_off = false;
		isl6421->config |= (ISL6421_EN1 | ISL6421_VSEL1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * If LNBf were not घातered on, disable dynamic current limit, as,
	 * according with datasheet, highly capacitive load on the output may
	 * cause a dअगरficult start-up.
	 */
	अगर (isl6421->is_off && !is_off)
		isl6421->config |= ISL6421_DCL;

	isl6421->config |= isl6421->override_or;
	isl6421->config &= isl6421->override_and;

	ret = i2c_transfer(isl6421->i2c, msg, 2);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != 2)
		वापस -EIO;

	/* Store off status now in हाल future commands fail */
	isl6421->is_off = is_off;

	/* On overflow, the device will try again after 900 ms (typically) */
	अगर (!is_off && (buf & ISL6421_OLF1))
		msleep(1000);

	/* Re-enable dynamic current limit */
	अगर ((isl6421->config & ISL6421_DCL) &&
	    !(isl6421->override_or & ISL6421_DCL)) अणु
		isl6421->config &= ~ISL6421_DCL;

		ret = i2c_transfer(isl6421->i2c, msg, 2);
		अगर (ret < 0)
			वापस ret;
		अगर (ret != 2)
			वापस -EIO;
	पूर्ण

	/* Check अगर overload flag is active. If so, disable घातer */
	अगर (!is_off && (buf & ISL6421_OLF1)) अणु
		isl6421->config &= ~(ISL6421_VSEL1 | ISL6421_EN1);
		ret = i2c_transfer(isl6421->i2c, msg, 1);
		अगर (ret < 0)
			वापस ret;
		अगर (ret != 1)
			वापस -EIO;
		isl6421->is_off = true;

		dev_warn(&isl6421->i2c->dev,
			 "Overload current detected. disabling LNBf power\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक isl6421_enable_high_lnb_voltage(काष्ठा dvb_frontend *fe, दीर्घ arg)
अणु
	काष्ठा isl6421 *isl6421 = (काष्ठा isl6421 *) fe->sec_priv;
	काष्ठा i2c_msg msg = अणु	.addr = isl6421->i2c_addr, .flags = 0,
				.buf = &isl6421->config,
				.len = माप(isl6421->config) पूर्ण;

	अगर (arg)
		isl6421->config |= ISL6421_LLC1;
	अन्यथा
		isl6421->config &= ~ISL6421_LLC1;

	isl6421->config |= isl6421->override_or;
	isl6421->config &= isl6421->override_and;

	वापस (i2c_transfer(isl6421->i2c, &msg, 1) == 1) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक isl6421_set_tone(काष्ठा dvb_frontend *fe,
			    क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा isl6421 *isl6421 = (काष्ठा isl6421 *) fe->sec_priv;
	काष्ठा i2c_msg msg = अणु .addr = isl6421->i2c_addr, .flags = 0,
			       .buf = &isl6421->config,
			       .len = माप(isl6421->config) पूर्ण;

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		isl6421->config |= ISL6421_ENT1;
		अवरोध;
	हाल SEC_TONE_OFF:
		isl6421->config &= ~ISL6421_ENT1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	isl6421->config |= isl6421->override_or;
	isl6421->config &= isl6421->override_and;

	वापस (i2c_transfer(isl6421->i2c, &msg, 1) == 1) ? 0 : -EIO;
पूर्ण

अटल व्योम isl6421_release(काष्ठा dvb_frontend *fe)
अणु
	/* घातer off */
	isl6421_set_voltage(fe, SEC_VOLTAGE_OFF);

	/* मुक्त */
	kमुक्त(fe->sec_priv);
	fe->sec_priv = शून्य;
पूर्ण

काष्ठा dvb_frontend *isl6421_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, u8 i2c_addr,
		   u8 override_set, u8 override_clear, bool override_tone)
अणु
	काष्ठा isl6421 *isl6421 = kदो_स्मृति(माप(काष्ठा isl6421), GFP_KERNEL);
	अगर (!isl6421)
		वापस शून्य;

	/* शेष configuration */
	isl6421->config = ISL6421_ISEL1;
	isl6421->i2c = i2c;
	isl6421->i2c_addr = i2c_addr;
	fe->sec_priv = isl6421;

	/* bits which should be क्रमced to '1' */
	isl6421->override_or = override_set;

	/* bits which should be क्रमced to '0' */
	isl6421->override_and = ~override_clear;

	/* detect अगर it is present or not */
	अगर (isl6421_set_voltage(fe, SEC_VOLTAGE_OFF)) अणु
		kमुक्त(isl6421);
		fe->sec_priv = शून्य;
		वापस शून्य;
	पूर्ण

	isl6421->is_off = true;

	/* install release callback */
	fe->ops.release_sec = isl6421_release;

	/* override frontend ops */
	fe->ops.set_voltage = isl6421_set_voltage;
	fe->ops.enable_high_lnb_voltage = isl6421_enable_high_lnb_voltage;
	अगर (override_tone)
		fe->ops.set_tone = isl6421_set_tone;

	वापस fe;
पूर्ण
EXPORT_SYMBOL(isl6421_attach);

MODULE_DESCRIPTION("Driver for lnb supply and control ic isl6421");
MODULE_AUTHOR("Andrew de Quincey & Oliver Endriss");
MODULE_LICENSE("GPL");
