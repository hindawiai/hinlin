<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis VP-2040 driver

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

#समावेश "tda1002x.h"
#समावेश "mantis_common.h"
#समावेश "mantis_ioc.h"
#समावेश "mantis_dvb.h"
#समावेश "mantis_vp2040.h"

#घोषणा MANTIS_MODEL_NAME	"VP-2040"
#घोषणा MANTIS_DEV_TYPE		"DVB-C"

अटल काष्ठा tda1002x_config vp2040_tda1002x_cu1216_config = अणु
	.demod_address	= 0x18 >> 1,
	.invert		= 1,
पूर्ण;

अटल काष्ठा tda10023_config vp2040_tda10023_cu1216_config = अणु
	.demod_address	= 0x18 >> 1,
	.invert		= 1,
पूर्ण;

अटल पूर्णांक tda1002x_cu1216_tuner_set(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा mantis_pci *mantis	= fe->dvb->priv;
	काष्ठा i2c_adapter *adapter	= &mantis->adapter;

	u8 buf[6];
	काष्ठा i2c_msg msg = अणु.addr = 0x60, .flags = 0, .buf = buf, .len = माप(buf)पूर्ण;
	पूर्णांक i;

#घोषणा CU1216_IF 36125000
#घोषणा TUNER_MUL 62500

	u32 भाग = (p->frequency + CU1216_IF + TUNER_MUL / 2) / TUNER_MUL;

	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = भाग & 0xff;
	buf[2] = 0xce;
	buf[3] = (p->frequency < 150000000 ? 0x01 :
		  p->frequency < 445000000 ? 0x02 : 0x04);
	buf[4] = 0xde;
	buf[5] = 0x20;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	अगर (i2c_transfer(adapter, &msg, 1) != 1)
		वापस -EIO;

	/* रुको क्रम the pll lock */
	msg.flags = I2C_M_RD;
	msg.len = 1;
	क्रम (i = 0; i < 20; i++) अणु
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		अगर (i2c_transfer(adapter, &msg, 1) == 1 && (buf[0] & 0x40))
			अवरोध;

		msleep(10);
	पूर्ण

	/* चयन the अक्षरge pump to the lower current */
	msg.flags = 0;
	msg.len = 2;
	msg.buf = &buf[2];
	buf[2] &= ~0x40;
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	अगर (i2c_transfer(adapter, &msg, 1) != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल u8 पढ़ो_pwm(काष्ठा mantis_pci *mantis)
अणु
	काष्ठा i2c_adapter *adapter = &mantis->adapter;

	u8 b = 0xff;
	u8 pwm;
	काष्ठा i2c_msg msg[] = अणु
		अणु.addr = 0x50, .flags = 0, .buf = &b, .len = 1पूर्ण,
		अणु.addr = 0x50, .flags = I2C_M_RD, .buf = &pwm, .len = 1पूर्ण
	पूर्ण;

	अगर ((i2c_transfer(adapter, msg, 2) != 2)
	    || (pwm == 0xff))
		pwm = 0x48;

	वापस pwm;
पूर्ण

अटल पूर्णांक vp2040_frontend_init(काष्ठा mantis_pci *mantis, काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_adapter *adapter = &mantis->adapter;

	पूर्णांक err = 0;

	err = mantis_frontend_घातer(mantis, POWER_ON);
	अगर (err == 0) अणु
		mantis_frontend_soft_reset(mantis);
		msleep(250);

		dprपूर्णांकk(MANTIS_ERROR, 1, "Probing for CU1216 (DVB-C)");
		fe = dvb_attach(tda10021_attach, &vp2040_tda1002x_cu1216_config,
				     adapter,
				     पढ़ो_pwm(mantis));

		अगर (fe) अणु
			dprपूर्णांकk(MANTIS_ERROR, 1,
				"found Philips CU1216 DVB-C frontend (TDA10021) @ 0x%02x",
				vp2040_tda1002x_cu1216_config.demod_address);
		पूर्ण अन्यथा अणु
			fe = dvb_attach(tda10023_attach, &vp2040_tda10023_cu1216_config,
					     adapter,
					     पढ़ो_pwm(mantis));

			अगर (fe) अणु
				dprपूर्णांकk(MANTIS_ERROR, 1,
					"found Philips CU1216 DVB-C frontend (TDA10023) @ 0x%02x",
					vp2040_tda1002x_cu1216_config.demod_address);
			पूर्ण
		पूर्ण

		अगर (fe) अणु
			fe->ops.tuner_ops.set_params = tda1002x_cu1216_tuner_set;
			dprपूर्णांकk(MANTIS_ERROR, 1, "Mantis DVB-C Philips CU1216 frontend attach success");
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
	dprपूर्णांकk(MANTIS_DEBUG, 1, "Done!");

	वापस 0;
पूर्ण

काष्ठा mantis_hwconfig vp2040_config = अणु
	.model_name	= MANTIS_MODEL_NAME,
	.dev_type	= MANTIS_DEV_TYPE,
	.ts_size	= MANTIS_TS_204,

	.baud_rate	= MANTIS_BAUD_9600,
	.parity		= MANTIS_PARITY_NONE,
	.bytes		= 0,

	.frontend_init	= vp2040_frontend_init,
	.घातer		= GPIF_A12,
	.reset		= GPIF_A13,
पूर्ण;
