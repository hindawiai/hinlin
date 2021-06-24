<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lnbp22.h - driver क्रम lnb supply and control ic lnbp22
 *
 * Copyright (C) 2006 Dominik Kuhlen
 * Based on lnbp21 driver
 *
 * the project's page is at https://linuxtv.org
 */
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "lnbp22.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");


#घोषणा dprपूर्णांकk(lvl, arg...) अगर (debug >= (lvl)) prपूर्णांकk(arg)

काष्ठा lnbp22 अणु
	u8		    config[4];
	काष्ठा i2c_adapter *i2c;
पूर्ण;

अटल पूर्णांक lnbp22_set_voltage(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा lnbp22 *lnbp22 = (काष्ठा lnbp22 *)fe->sec_priv;
	काष्ठा i2c_msg msg = अणु
		.addr = 0x08,
		.flags = 0,
		.buf = (अक्षर *)&lnbp22->config,
		.len = माप(lnbp22->config),
	पूर्ण;

	dprपूर्णांकk(1, "%s: %d (18V=%d 13V=%d)\n", __func__, voltage,
	       SEC_VOLTAGE_18, SEC_VOLTAGE_13);

	lnbp22->config[3] = 0x60; /* Power करोwn */
	चयन (voltage) अणु
	हाल SEC_VOLTAGE_OFF:
		अवरोध;
	हाल SEC_VOLTAGE_13:
		lnbp22->config[3] |= LNBP22_EN;
		अवरोध;
	हाल SEC_VOLTAGE_18:
		lnbp22->config[3] |= (LNBP22_EN | LNBP22_VSEL);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk(1, "%s: 0x%02x)\n", __func__, lnbp22->config[3]);
	वापस (i2c_transfer(lnbp22->i2c, &msg, 1) == 1) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक lnbp22_enable_high_lnb_voltage(काष्ठा dvb_frontend *fe, दीर्घ arg)
अणु
	काष्ठा lnbp22 *lnbp22 = (काष्ठा lnbp22 *) fe->sec_priv;
	काष्ठा i2c_msg msg = अणु
		.addr = 0x08,
		.flags = 0,
		.buf = (अक्षर *)&lnbp22->config,
		.len = माप(lnbp22->config),
	पूर्ण;

	dprपूर्णांकk(1, "%s: %d\n", __func__, (पूर्णांक)arg);
	अगर (arg)
		lnbp22->config[3] |= LNBP22_LLC;
	अन्यथा
		lnbp22->config[3] &= ~LNBP22_LLC;

	वापस (i2c_transfer(lnbp22->i2c, &msg, 1) == 1) ? 0 : -EIO;
पूर्ण

अटल व्योम lnbp22_release(काष्ठा dvb_frontend *fe)
अणु
	dprपूर्णांकk(1, "%s\n", __func__);
	/* LNBP घातer off */
	lnbp22_set_voltage(fe, SEC_VOLTAGE_OFF);

	/* मुक्त data */
	kमुक्त(fe->sec_priv);
	fe->sec_priv = शून्य;
पूर्ण

काष्ठा dvb_frontend *lnbp22_attach(काष्ठा dvb_frontend *fe,
					काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा lnbp22 *lnbp22 = kदो_स्मृति(माप(काष्ठा lnbp22), GFP_KERNEL);
	अगर (!lnbp22)
		वापस शून्य;

	/* शेष configuration */
	lnbp22->config[0] = 0x00; /* ? */
	lnbp22->config[1] = 0x28; /* ? */
	lnbp22->config[2] = 0x48; /* ? */
	lnbp22->config[3] = 0x60; /* Power करोwn */
	lnbp22->i2c = i2c;
	fe->sec_priv = lnbp22;

	/* detect अगर it is present or not */
	अगर (lnbp22_set_voltage(fe, SEC_VOLTAGE_OFF)) अणु
		dprपूर्णांकk(0, "%s LNBP22 not found\n", __func__);
		kमुक्त(lnbp22);
		fe->sec_priv = शून्य;
		वापस शून्य;
	पूर्ण

	/* install release callback */
	fe->ops.release_sec = lnbp22_release;

	/* override frontend ops */
	fe->ops.set_voltage = lnbp22_set_voltage;
	fe->ops.enable_high_lnb_voltage = lnbp22_enable_high_lnb_voltage;

	वापस fe;
पूर्ण
EXPORT_SYMBOL(lnbp22_attach);

MODULE_DESCRIPTION("Driver for lnb supply and control ic lnbp22");
MODULE_AUTHOR("Dominik Kuhlen");
MODULE_LICENSE("GPL");
