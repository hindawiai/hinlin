<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	STV6110(A) Silicon tuner driver

	Copyright (C) Manu Abraham <abraham.manu@gmail.com>

	Copyright (C) ST Microelectronics

*/

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <media/dvb_frontend.h>

#समावेश "stv6110x_reg.h"
#समावेश "stv6110x.h"
#समावेश "stv6110x_priv.h"

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

अटल अचिन्हित पूर्णांक verbose;
module_param(verbose, पूर्णांक, 0644);
MODULE_PARM_DESC(verbose, "Set Verbosity level");

अटल पूर्णांक stv6110x_पढ़ो_reg(काष्ठा stv6110x_state *stv6110x, u8 reg, u8 *data)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा stv6110x_config *config = stv6110x->config;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = config->addr, .flags = 0,	   .buf = b0, .len = 1 पूर्ण,
		अणु .addr = config->addr, .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण
	पूर्ण;

	ret = i2c_transfer(stv6110x->i2c, msg, 2);
	अगर (ret != 2) अणु
		dprपूर्णांकk(FE_ERROR, 1, "I/O Error");
		वापस -EREMOTEIO;
	पूर्ण
	*data = b1[0];

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_ग_लिखो_regs(काष्ठा stv6110x_state *stv6110x, पूर्णांक start, u8 data[], पूर्णांक len)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा stv6110x_config *config = stv6110x->config;
	u8 buf[MAX_XFER_SIZE];

	काष्ठा i2c_msg msg = अणु
		.addr = config->addr,
		.flags = 0,
		.buf = buf,
		.len = len + 1
	पूर्ण;

	अगर (1 + len > माप(buf)) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: i2c wr: len=%d is too big!\n",
		       KBUILD_MODNAME, len);
		वापस -EINVAL;
	पूर्ण

	अगर (start + len > 8)
		वापस -EINVAL;

	buf[0] = start;
	स_नकल(&buf[1], data, len);

	ret = i2c_transfer(stv6110x->i2c, &msg, 1);
	अगर (ret != 1) अणु
		dprपूर्णांकk(FE_ERROR, 1, "I/O Error");
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_ग_लिखो_reg(काष्ठा stv6110x_state *stv6110x, u8 reg, u8 data)
अणु
	u8 पंचांगp = data; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	वापस stv6110x_ग_लिखो_regs(stv6110x, reg, &पंचांगp, 1);
पूर्ण

अटल पूर्णांक stv6110x_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv6110x_state *stv6110x = fe->tuner_priv;
	पूर्णांक ret;

	ret = stv6110x_ग_लिखो_regs(stv6110x, 0, stv6110x->regs,
				  ARRAY_SIZE(stv6110x->regs));
	अगर (ret < 0) अणु
		dprपूर्णांकk(FE_ERROR, 1, "Initialization failed");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_set_frequency(काष्ठा dvb_frontend *fe, u32 frequency)
अणु
	काष्ठा stv6110x_state *stv6110x = fe->tuner_priv;
	u32 rDiv, भागider;
	s32 pVal, pCalc, rDivOpt = 0, pCalcOpt = 1000;
	u8 i;

	STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL1], CTRL1_K, (REFCLOCK_MHz - 16));

	अगर (frequency <= 1023000) अणु
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_TNG1], TNG1_DIV4SEL, 1);
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_TNG1], TNG1_PRESC32_ON, 0);
		pVal = 40;
	पूर्ण अन्यथा अगर (frequency <= 1300000) अणु
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_TNG1], TNG1_DIV4SEL, 1);
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_TNG1], TNG1_PRESC32_ON, 1);
		pVal = 40;
	पूर्ण अन्यथा अगर (frequency <= 2046000) अणु
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_TNG1], TNG1_DIV4SEL, 0);
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_TNG1], TNG1_PRESC32_ON, 0);
		pVal = 20;
	पूर्ण अन्यथा अणु
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_TNG1], TNG1_DIV4SEL, 0);
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_TNG1], TNG1_PRESC32_ON, 1);
		pVal = 20;
	पूर्ण

	क्रम (rDiv = 0; rDiv <= 3; rDiv++) अणु
		pCalc = (REFCLOCK_kHz / 100) / R_DIV(rDiv);

		अगर ((असल((s32)(pCalc - pVal))) < (असल((s32)(pCalcOpt - pVal))))
			rDivOpt = rDiv;

		pCalcOpt = (REFCLOCK_kHz / 100) / R_DIV(rDivOpt);
	पूर्ण

	भागider = (frequency * R_DIV(rDivOpt) * pVal) / REFCLOCK_kHz;
	भागider = (भागider + 5) / 10;

	STV6110x_SETFIELD(stv6110x->regs[STV6110x_TNG1], TNG1_R_DIV, rDivOpt);
	STV6110x_SETFIELD(stv6110x->regs[STV6110x_TNG1], TNG1_N_DIV_11_8, MSB(भागider));
	STV6110x_SETFIELD(stv6110x->regs[STV6110x_TNG0], TNG0_N_DIV_7_0, LSB(भागider));

	/* VCO Auto calibration */
	STV6110x_SETFIELD(stv6110x->regs[STV6110x_STAT1], STAT1_CALVCO_STRT, 1);

	stv6110x_ग_लिखो_reg(stv6110x, STV6110x_CTRL1, stv6110x->regs[STV6110x_CTRL1]);
	stv6110x_ग_लिखो_reg(stv6110x, STV6110x_TNG1, stv6110x->regs[STV6110x_TNG1]);
	stv6110x_ग_लिखो_reg(stv6110x, STV6110x_TNG0, stv6110x->regs[STV6110x_TNG0]);
	stv6110x_ग_लिखो_reg(stv6110x, STV6110x_STAT1, stv6110x->regs[STV6110x_STAT1]);

	क्रम (i = 0; i < TRIALS; i++) अणु
		stv6110x_पढ़ो_reg(stv6110x, STV6110x_STAT1, &stv6110x->regs[STV6110x_STAT1]);
		अगर (!STV6110x_GETFIELD(STAT1_CALVCO_STRT, stv6110x->regs[STV6110x_STAT1]))
				अवरोध;
		msleep(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा stv6110x_state *stv6110x = fe->tuner_priv;

	stv6110x_पढ़ो_reg(stv6110x, STV6110x_TNG1, &stv6110x->regs[STV6110x_TNG1]);
	stv6110x_पढ़ो_reg(stv6110x, STV6110x_TNG0, &stv6110x->regs[STV6110x_TNG0]);

	*frequency = (MAKEWORD16(STV6110x_GETFIELD(TNG1_N_DIV_11_8, stv6110x->regs[STV6110x_TNG1]),
				 STV6110x_GETFIELD(TNG0_N_DIV_7_0, stv6110x->regs[STV6110x_TNG0]))) * REFCLOCK_kHz;

	*frequency /= (1 << (STV6110x_GETFIELD(TNG1_R_DIV, stv6110x->regs[STV6110x_TNG1]) +
			     STV6110x_GETFIELD(TNG1_DIV4SEL, stv6110x->regs[STV6110x_TNG1])));

	*frequency >>= 2;

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_set_bandwidth(काष्ठा dvb_frontend *fe, u32 bandwidth)
अणु
	काष्ठा stv6110x_state *stv6110x = fe->tuner_priv;
	u32 halfbw;
	u8 i;

	halfbw = bandwidth >> 1;

	अगर (halfbw > 36000000)
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL3], CTRL3_CF, 31); /* LPF */
	अन्यथा अगर (halfbw < 5000000)
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL3], CTRL3_CF, 0); /* LPF */
	अन्यथा
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL3], CTRL3_CF, ((halfbw / 1000000) - 5)); /* LPF */


	STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL3], CTRL3_RCCLK_OFF, 0x0); /* cal. clk activated */
	STV6110x_SETFIELD(stv6110x->regs[STV6110x_STAT1], STAT1_CALRC_STRT, 0x1); /* LPF स्वतः cal */

	stv6110x_ग_लिखो_reg(stv6110x, STV6110x_CTRL3, stv6110x->regs[STV6110x_CTRL3]);
	stv6110x_ग_लिखो_reg(stv6110x, STV6110x_STAT1, stv6110x->regs[STV6110x_STAT1]);

	क्रम (i = 0; i < TRIALS; i++) अणु
		stv6110x_पढ़ो_reg(stv6110x, STV6110x_STAT1, &stv6110x->regs[STV6110x_STAT1]);
		अगर (!STV6110x_GETFIELD(STAT1_CALRC_STRT, stv6110x->regs[STV6110x_STAT1]))
			अवरोध;
		msleep(1);
	पूर्ण
	STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL3], CTRL3_RCCLK_OFF, 0x1); /* cal. करोne */
	stv6110x_ग_लिखो_reg(stv6110x, STV6110x_CTRL3, stv6110x->regs[STV6110x_CTRL3]);

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा stv6110x_state *stv6110x = fe->tuner_priv;

	stv6110x_पढ़ो_reg(stv6110x, STV6110x_CTRL3, &stv6110x->regs[STV6110x_CTRL3]);
	*bandwidth = (STV6110x_GETFIELD(CTRL3_CF, stv6110x->regs[STV6110x_CTRL3]) + 5) * 2000000;

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_set_refघड़ी(काष्ठा dvb_frontend *fe, u32 refघड़ी)
अणु
	काष्ठा stv6110x_state *stv6110x = fe->tuner_priv;

	/* setup भागider */
	चयन (refघड़ी) अणु
	शेष:
	हाल 1:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2], CTRL2_CO_DIV, 0);
		अवरोध;
	हाल 2:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2], CTRL2_CO_DIV, 1);
		अवरोध;
	हाल 4:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2], CTRL2_CO_DIV, 2);
		अवरोध;
	हाल 8:
	हाल 0:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2], CTRL2_CO_DIV, 3);
		अवरोध;
	पूर्ण
	stv6110x_ग_लिखो_reg(stv6110x, STV6110x_CTRL2, stv6110x->regs[STV6110x_CTRL2]);

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_get_bbgain(काष्ठा dvb_frontend *fe, u32 *gain)
अणु
	काष्ठा stv6110x_state *stv6110x = fe->tuner_priv;

	stv6110x_पढ़ो_reg(stv6110x, STV6110x_CTRL2, &stv6110x->regs[STV6110x_CTRL2]);
	*gain = 2 * STV6110x_GETFIELD(CTRL2_BBGAIN, stv6110x->regs[STV6110x_CTRL2]);

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_set_bbgain(काष्ठा dvb_frontend *fe, u32 gain)
अणु
	काष्ठा stv6110x_state *stv6110x = fe->tuner_priv;

	STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2], CTRL2_BBGAIN, gain / 2);
	stv6110x_ग_लिखो_reg(stv6110x, STV6110x_CTRL2, stv6110x->regs[STV6110x_CTRL2]);

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_set_mode(काष्ठा dvb_frontend *fe, क्रमागत tuner_mode mode)
अणु
	काष्ठा stv6110x_state *stv6110x = fe->tuner_priv;
	पूर्णांक ret;

	चयन (mode) अणु
	हाल TUNER_SLEEP:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL1], CTRL1_SYN, 0);
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL1], CTRL1_RX, 0);
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL1], CTRL1_LPT, 0);
		अवरोध;

	हाल TUNER_WAKE:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL1], CTRL1_SYN, 1);
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL1], CTRL1_RX, 1);
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL1], CTRL1_LPT, 1);
		अवरोध;
	पूर्ण

	ret = stv6110x_ग_लिखो_reg(stv6110x, STV6110x_CTRL1, stv6110x->regs[STV6110x_CTRL1]);
	अगर (ret < 0) अणु
		dprपूर्णांकk(FE_ERROR, 1, "I/O Error");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_sleep(काष्ठा dvb_frontend *fe)
अणु
	अगर (fe->tuner_priv)
		वापस stv6110x_set_mode(fe, TUNER_SLEEP);

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	काष्ठा stv6110x_state *stv6110x = fe->tuner_priv;

	stv6110x_पढ़ो_reg(stv6110x, STV6110x_STAT1, &stv6110x->regs[STV6110x_STAT1]);

	अगर (STV6110x_GETFIELD(STAT1_LOCK, stv6110x->regs[STV6110x_STAT1]))
		*status = TUNER_PHASELOCKED;
	अन्यथा
		*status = 0;

	वापस 0;
पूर्ण


अटल व्योम stv6110x_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv6110x_state *stv6110x = fe->tuner_priv;

	fe->tuner_priv = शून्य;
	kमुक्त(stv6110x);
पूर्ण

अटल व्योम st6110x_init_regs(काष्ठा stv6110x_state *stv6110x)
अणु
	u8 शेष_regs[] = अणु0x07, 0x11, 0xdc, 0x85, 0x17, 0x01, 0xe6, 0x1eपूर्ण;

	स_नकल(stv6110x->regs, शेष_regs, 8);
पूर्ण

अटल व्योम stv6110x_setup_भागider(काष्ठा stv6110x_state *stv6110x)
अणु
	चयन (stv6110x->config->clk_भाग) अणु
	शेष:
	हाल 1:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2],
				  CTRL2_CO_DIV,
				  0);
		अवरोध;
	हाल 2:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2],
				  CTRL2_CO_DIV,
				  1);
		अवरोध;
	हाल 4:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2],
				  CTRL2_CO_DIV,
				  2);
		अवरोध;
	हाल 8:
	हाल 0:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2],
				  CTRL2_CO_DIV,
				  3);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops stv6110x_ops = अणु
	.info = अणु
		.name		  = "STV6110(A) Silicon Tuner",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
	पूर्ण,
	.release		= stv6110x_release
पूर्ण;

अटल काष्ठा stv6110x_devctl stv6110x_ctl = अणु
	.tuner_init		= stv6110x_init,
	.tuner_sleep		= stv6110x_sleep,
	.tuner_set_mode		= stv6110x_set_mode,
	.tuner_set_frequency	= stv6110x_set_frequency,
	.tuner_get_frequency	= stv6110x_get_frequency,
	.tuner_set_bandwidth	= stv6110x_set_bandwidth,
	.tuner_get_bandwidth	= stv6110x_get_bandwidth,
	.tuner_set_bbgain	= stv6110x_set_bbgain,
	.tuner_get_bbgain	= stv6110x_get_bbgain,
	.tuner_set_refclk	= stv6110x_set_refघड़ी,
	.tuner_get_status	= stv6110x_get_status,
पूर्ण;

अटल व्योम stv6110x_set_frontend_opts(काष्ठा stv6110x_state *stv6110x)
अणु
	stv6110x->frontend->tuner_priv		= stv6110x;
	stv6110x->frontend->ops.tuner_ops	= stv6110x_ops;
पूर्ण

अटल काष्ठा stv6110x_devctl *stv6110x_get_devctl(काष्ठा i2c_client *client)
अणु
	काष्ठा stv6110x_state *stv6110x = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	वापस stv6110x->devctl;
पूर्ण

अटल पूर्णांक stv6110x_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा stv6110x_config *config = client->dev.platक्रमm_data;

	काष्ठा stv6110x_state *stv6110x;

	stv6110x = kzalloc(माप(*stv6110x), GFP_KERNEL);
	अगर (!stv6110x)
		वापस -ENOMEM;

	stv6110x->frontend	= config->frontend;
	stv6110x->i2c		= client->adapter;
	stv6110x->config	= config;
	stv6110x->devctl	= &stv6110x_ctl;

	st6110x_init_regs(stv6110x);
	stv6110x_setup_भागider(stv6110x);
	stv6110x_set_frontend_opts(stv6110x);

	dev_info(&stv6110x->i2c->dev, "Probed STV6110x\n");

	i2c_set_clientdata(client, stv6110x);

	/* setup callbacks */
	config->get_devctl = stv6110x_get_devctl;

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा stv6110x_state *stv6110x = i2c_get_clientdata(client);

	stv6110x_release(stv6110x->frontend);
	वापस 0;
पूर्ण

स्थिर काष्ठा stv6110x_devctl *stv6110x_attach(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा stv6110x_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा stv6110x_state *stv6110x;

	stv6110x = kzalloc(माप(*stv6110x), GFP_KERNEL);
	अगर (!stv6110x)
		वापस शून्य;

	stv6110x->frontend	= fe;
	stv6110x->i2c		= i2c;
	stv6110x->config	= config;
	stv6110x->devctl	= &stv6110x_ctl;

	st6110x_init_regs(stv6110x);
	stv6110x_setup_भागider(stv6110x);
	stv6110x_set_frontend_opts(stv6110x);

	fe->tuner_priv		= stv6110x;
	fe->ops.tuner_ops	= stv6110x_ops;

	dev_info(&stv6110x->i2c->dev, "Attaching STV6110x\n");
	वापस stv6110x->devctl;
पूर्ण
EXPORT_SYMBOL(stv6110x_attach);

अटल स्थिर काष्ठा i2c_device_id stv6110x_id_table[] = अणु
	अणु"stv6110x", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, stv6110x_id_table);

अटल काष्ठा i2c_driver stv6110x_driver = अणु
	.driver = अणु
		.name	= "stv6110x",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= stv6110x_probe,
	.हटाओ		= stv6110x_हटाओ,
	.id_table	= stv6110x_id_table,
पूर्ण;

module_i2c_driver(stv6110x_driver);

MODULE_AUTHOR("Manu Abraham");
MODULE_DESCRIPTION("STV6110x Silicon tuner");
MODULE_LICENSE("GPL");
