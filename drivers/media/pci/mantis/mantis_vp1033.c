<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis VP-1033 driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "stv0299.h"
#समावेश "mantis_common.h"
#समावेश "mantis_ioc.h"
#समावेश "mantis_dvb.h"
#समावेश "mantis_vp1033.h"
#समावेश "mantis_reg.h"

अटल u8 lgtdqcs001f_inittab[] = अणु
	0x01, 0x15,
	0x02, 0x30,
	0x03, 0x00,
	0x04, 0x2a,
	0x05, 0x85,
	0x06, 0x02,
	0x07, 0x00,
	0x08, 0x00,
	0x0c, 0x01,
	0x0d, 0x81,
	0x0e, 0x44,
	0x0f, 0x94,
	0x10, 0x3c,
	0x11, 0x84,
	0x12, 0xb9,
	0x13, 0xb5,
	0x14, 0x4f,
	0x15, 0xc9,
	0x16, 0x80,
	0x17, 0x36,
	0x18, 0xfb,
	0x19, 0xcf,
	0x1a, 0xbc,
	0x1c, 0x2b,
	0x1d, 0x27,
	0x1e, 0x00,
	0x1f, 0x0b,
	0x20, 0xa1,
	0x21, 0x60,
	0x22, 0x00,
	0x23, 0x00,
	0x28, 0x00,
	0x29, 0x28,
	0x2a, 0x14,
	0x2b, 0x0f,
	0x2c, 0x09,
	0x2d, 0x05,
	0x31, 0x1f,
	0x32, 0x19,
	0x33, 0xfc,
	0x34, 0x13,
	0xff, 0xff,
पूर्ण;

#घोषणा MANTIS_MODEL_NAME	"VP-1033"
#घोषणा MANTIS_DEV_TYPE		"DVB-S/DSS"

अटल पूर्णांक lgtdqcs001f_tuner_set(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा mantis_pci *mantis	= fe->dvb->priv;
	काष्ठा i2c_adapter *adapter	= &mantis->adapter;

	u8 buf[4];
	u32 भाग;


	काष्ठा i2c_msg msg = अणु.addr = 0x61, .flags = 0, .buf = buf, .len = माप(buf)पूर्ण;

	भाग = p->frequency / 250;

	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] =  भाग & 0xff;
	buf[2] =  0x83;
	buf[3] =  0xc0;

	अगर (p->frequency < 1531000)
		buf[3] |= 0x04;
	अन्यथा
		buf[3] &= ~0x04;
	अगर (i2c_transfer(adapter, &msg, 1) < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "Write: I2C Transfer failed");
		वापस -EIO;
	पूर्ण
	msleep_पूर्णांकerruptible(100);

	वापस 0;
पूर्ण

अटल पूर्णांक lgtdqcs001f_set_symbol_rate(काष्ठा dvb_frontend *fe,
				       u32 srate, u32 ratio)
अणु
	u8 aclk = 0;
	u8 bclk = 0;

	अगर (srate < 1500000) अणु
		aclk = 0xb7;
		bclk = 0x47;
	पूर्ण अन्यथा अगर (srate < 3000000) अणु
		aclk = 0xb7;
		bclk = 0x4b;
	पूर्ण अन्यथा अगर (srate < 7000000) अणु
		aclk = 0xb7;
		bclk = 0x4f;
	पूर्ण अन्यथा अगर (srate < 14000000) अणु
		aclk = 0xb7;
		bclk = 0x53;
	पूर्ण अन्यथा अगर (srate < 30000000) अणु
		aclk = 0xb6;
		bclk = 0x53;
	पूर्ण अन्यथा अगर (srate < 45000000) अणु
		aclk = 0xb4;
		bclk = 0x51;
	पूर्ण
	stv0299_ग_लिखोreg(fe, 0x13, aclk);
	stv0299_ग_लिखोreg(fe, 0x14, bclk);

	stv0299_ग_लिखोreg(fe, 0x1f, (ratio >> 16) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x20, (ratio >>  8) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x21,  ratio & 0xf0);

	वापस 0;
पूर्ण

अटल काष्ठा stv0299_config lgtdqcs001f_config = अणु
	.demod_address		= 0x68,
	.inittab		= lgtdqcs001f_inittab,
	.mclk			= 88000000UL,
	.invert			= 0,
	.skip_reinit		= 0,
	.volt13_op0_op1		= STV0299_VOLT13_OP0,
	.min_delay_ms		= 100,
	.set_symbol_rate	= lgtdqcs001f_set_symbol_rate,
पूर्ण;

अटल पूर्णांक vp1033_frontend_init(काष्ठा mantis_pci *mantis, काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_adapter *adapter	= &mantis->adapter;

	पूर्णांक err = 0;

	err = mantis_frontend_घातer(mantis, POWER_ON);
	अगर (err == 0) अणु
		mantis_frontend_soft_reset(mantis);
		msleep(250);

		dprपूर्णांकk(MANTIS_ERROR, 1, "Probing for STV0299 (DVB-S)");
		fe = dvb_attach(stv0299_attach, &lgtdqcs001f_config, adapter);

		अगर (fe) अणु
			fe->ops.tuner_ops.set_params = lgtdqcs001f_tuner_set;
			dprपूर्णांकk(MANTIS_ERROR, 1, "found STV0299 DVB-S frontend @ 0x%02x",
				lgtdqcs001f_config.demod_address);

			dprपूर्णांकk(MANTIS_ERROR, 1, "Mantis DVB-S STV0299 frontend attach success");
		पूर्ण अन्यथा अणु
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "Frontend on <%s> POWER ON failed! <%d>",
			adapter->name,
			err);

		वापस -EIO;
	पूर्ण
	mantis->fe = fe;
	dprपूर्णांकk(MANTIS_ERROR, 1, "Done!");

	वापस 0;
पूर्ण

काष्ठा mantis_hwconfig vp1033_config = अणु
	.model_name		= MANTIS_MODEL_NAME,
	.dev_type		= MANTIS_DEV_TYPE,
	.ts_size		= MANTIS_TS_204,

	.baud_rate		= MANTIS_BAUD_9600,
	.parity			= MANTIS_PARITY_NONE,
	.bytes			= 0,

	.frontend_init		= vp1033_frontend_init,
	.घातer			= GPIF_A12,
	.reset			= GPIF_A13,
पूर्ण;
