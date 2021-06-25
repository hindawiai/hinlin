<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Intersil ISL6423 SEC and LNB Power supply controller

	Copyright (C) Manu Abraham <abraham.manu@gmail.com>

*/

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "isl6423.h"

अटल अचिन्हित पूर्णांक verbose;
module_param(verbose, पूर्णांक, 0644);
MODULE_PARM_DESC(verbose, "Set Verbosity level");

#घोषणा FE_ERROR				0
#घोषणा FE_NOTICE				1
#घोषणा FE_INFO					2
#घोषणा FE_DEBUG				3
#घोषणा FE_DEBUGREG				4

#घोषणा dprपूर्णांकk(__y, __z, क्रमmat, arg...) करो अणु						\
	अगर (__z) अणु									\
		अगर	((verbose > FE_ERROR) && (verbose > __y))			\
			prपूर्णांकk(KERN_ERR "%s: " क्रमmat "\n", __func__ , ##arg);		\
		अन्यथा अगर	((verbose > FE_NOTICE) && (verbose > __y))			\
			prपूर्णांकk(KERN_NOTICE "%s: " क्रमmat "\n", __func__ , ##arg);	\
		अन्यथा अगर ((verbose > FE_INFO) && (verbose > __y))			\
			prपूर्णांकk(KERN_INFO "%s: " क्रमmat "\n", __func__ , ##arg);		\
		अन्यथा अगर ((verbose > FE_DEBUG) && (verbose > __y))			\
			prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat "\n", __func__ , ##arg);	\
	पूर्ण अन्यथा अणु									\
		अगर (verbose > __y)							\
			prपूर्णांकk(क्रमmat, ##arg);						\
	पूर्ण										\
पूर्ण जबतक (0)

काष्ठा isl6423_dev अणु
	स्थिर काष्ठा isl6423_config	*config;
	काष्ठा i2c_adapter		*i2c;

	u8 reg_3;
	u8 reg_4;

	अचिन्हित पूर्णांक verbose;
पूर्ण;

अटल पूर्णांक isl6423_ग_लिखो(काष्ठा isl6423_dev *isl6423, u8 reg)
अणु
	काष्ठा i2c_adapter *i2c = isl6423->i2c;
	u8 addr			= isl6423->config->addr;
	पूर्णांक err = 0;

	काष्ठा i2c_msg msg = अणु .addr = addr, .flags = 0, .buf = &reg, .len = 1 पूर्ण;

	dprपूर्णांकk(FE_DEBUG, 1, "write reg %02X", reg);
	err = i2c_transfer(i2c, &msg, 1);
	अगर (err < 0)
		जाओ निकास;
	वापस 0;

निकास:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error <%d>", err);
	वापस err;
पूर्ण

अटल पूर्णांक isl6423_set_modulation(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा isl6423_dev *isl6423		= (काष्ठा isl6423_dev *) fe->sec_priv;
	स्थिर काष्ठा isl6423_config *config	= isl6423->config;
	पूर्णांक err = 0;
	u8 reg_2 = 0;

	reg_2 = 0x01 << 5;

	अगर (config->mod_बाह्य)
		reg_2 |= (1 << 3);
	अन्यथा
		reg_2 |= (1 << 4);

	err = isl6423_ग_लिखो(isl6423, reg_2);
	अगर (err < 0)
		जाओ निकास;
	वापस 0;

निकास:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error <%d>", err);
	वापस err;
पूर्ण

अटल पूर्णांक isl6423_voltage_boost(काष्ठा dvb_frontend *fe, दीर्घ arg)
अणु
	काष्ठा isl6423_dev *isl6423 = (काष्ठा isl6423_dev *) fe->sec_priv;
	u8 reg_3 = isl6423->reg_3;
	u8 reg_4 = isl6423->reg_4;
	पूर्णांक err = 0;

	अगर (arg) अणु
		/* EN = 1, VSPEN = 1, VBOT = 1 */
		reg_4 |= (1 << 4);
		reg_4 |= 0x1;
		reg_3 |= (1 << 3);
	पूर्ण अन्यथा अणु
		/* EN = 1, VSPEN = 1, VBOT = 0 */
		reg_4 |= (1 << 4);
		reg_4 &= ~0x1;
		reg_3 |= (1 << 3);
	पूर्ण
	err = isl6423_ग_लिखो(isl6423, reg_3);
	अगर (err < 0)
		जाओ निकास;

	err = isl6423_ग_लिखो(isl6423, reg_4);
	अगर (err < 0)
		जाओ निकास;

	isl6423->reg_3 = reg_3;
	isl6423->reg_4 = reg_4;

	वापस 0;
निकास:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error <%d>", err);
	वापस err;
पूर्ण


अटल पूर्णांक isl6423_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा isl6423_dev *isl6423 = (काष्ठा isl6423_dev *) fe->sec_priv;
	u8 reg_3 = isl6423->reg_3;
	u8 reg_4 = isl6423->reg_4;
	पूर्णांक err = 0;

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_OFF:
		/* EN = 0 */
		reg_4 &= ~(1 << 4);
		अवरोध;

	हाल SEC_VOLTAGE_13:
		/* EN = 1, VSPEN = 1, VTOP = 0, VBOT = 0 */
		reg_4 |= (1 << 4);
		reg_4 &= ~0x3;
		reg_3 |= (1 << 3);
		अवरोध;

	हाल SEC_VOLTAGE_18:
		/* EN = 1, VSPEN = 1, VTOP = 1, VBOT = 0 */
		reg_4 |= (1 << 4);
		reg_4 |=  0x2;
		reg_4 &= ~0x1;
		reg_3 |= (1 << 3);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	err = isl6423_ग_लिखो(isl6423, reg_3);
	अगर (err < 0)
		जाओ निकास;

	err = isl6423_ग_लिखो(isl6423, reg_4);
	अगर (err < 0)
		जाओ निकास;

	isl6423->reg_3 = reg_3;
	isl6423->reg_4 = reg_4;

	वापस 0;
निकास:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error <%d>", err);
	वापस err;
पूर्ण

अटल पूर्णांक isl6423_set_current(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा isl6423_dev *isl6423		= (काष्ठा isl6423_dev *) fe->sec_priv;
	u8 reg_3 = isl6423->reg_3;
	स्थिर काष्ठा isl6423_config *config	= isl6423->config;
	पूर्णांक err = 0;

	चयन (config->current_max) अणु
	हाल SEC_CURRENT_275m:
		/* 275mA */
		/* ISELH = 0, ISELL = 0 */
		reg_3 &= ~0x3;
		अवरोध;

	हाल SEC_CURRENT_515m:
		/* 515mA */
		/* ISELH = 0, ISELL = 1 */
		reg_3 &= ~0x2;
		reg_3 |=  0x1;
		अवरोध;

	हाल SEC_CURRENT_635m:
		/* 635mA */
		/* ISELH = 1, ISELL = 0 */
		reg_3 &= ~0x1;
		reg_3 |=  0x2;
		अवरोध;

	हाल SEC_CURRENT_800m:
		/* 800mA */
		/* ISELH = 1, ISELL = 1 */
		reg_3 |= 0x3;
		अवरोध;
	पूर्ण

	err = isl6423_ग_लिखो(isl6423, reg_3);
	अगर (err < 0)
		जाओ निकास;

	चयन (config->curlim) अणु
	हाल SEC_CURRENT_LIM_ON:
		/* DCL = 0 */
		reg_3 &= ~0x10;
		अवरोध;

	हाल SEC_CURRENT_LIM_OFF:
		/* DCL = 1 */
		reg_3 |= 0x10;
		अवरोध;
	पूर्ण

	err = isl6423_ग_लिखो(isl6423, reg_3);
	अगर (err < 0)
		जाओ निकास;

	isl6423->reg_3 = reg_3;

	वापस 0;
निकास:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error <%d>", err);
	वापस err;
पूर्ण

अटल व्योम isl6423_release(काष्ठा dvb_frontend *fe)
अणु
	isl6423_set_voltage(fe, SEC_VOLTAGE_OFF);

	kमुक्त(fe->sec_priv);
	fe->sec_priv = शून्य;
पूर्ण

काष्ठा dvb_frontend *isl6423_attach(काष्ठा dvb_frontend *fe,
				    काष्ठा i2c_adapter *i2c,
				    स्थिर काष्ठा isl6423_config *config)
अणु
	काष्ठा isl6423_dev *isl6423;

	isl6423 = kzalloc(माप(काष्ठा isl6423_dev), GFP_KERNEL);
	अगर (!isl6423)
		वापस शून्य;

	isl6423->config	= config;
	isl6423->i2c	= i2c;
	fe->sec_priv	= isl6423;

	/* SR3H = 0, SR3M = 1, SR3L = 0 */
	isl6423->reg_3 = 0x02 << 5;
	/* SR4H = 0, SR4M = 1, SR4L = 1 */
	isl6423->reg_4 = 0x03 << 5;

	अगर (isl6423_set_current(fe))
		जाओ निकास;

	अगर (isl6423_set_modulation(fe))
		जाओ निकास;

	fe->ops.release_sec		= isl6423_release;
	fe->ops.set_voltage		= isl6423_set_voltage;
	fe->ops.enable_high_lnb_voltage = isl6423_voltage_boost;
	isl6423->verbose		= verbose;

	वापस fe;

निकास:
	kमुक्त(isl6423);
	fe->sec_priv = शून्य;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(isl6423_attach);

MODULE_DESCRIPTION("ISL6423 SEC");
MODULE_AUTHOR("Manu Abraham");
MODULE_LICENSE("GPL");
