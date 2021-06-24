<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis VP-1034 driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "mb86a16.h"
#समावेश "mantis_common.h"
#समावेश "mantis_ioc.h"
#समावेश "mantis_dvb.h"
#समावेश "mantis_vp1034.h"
#समावेश "mantis_reg.h"

अटल स्थिर काष्ठा mb86a16_config vp1034_mb86a16_config = अणु
	.demod_address	= 0x08,
	.set_voltage	= vp1034_set_voltage,
पूर्ण;

#घोषणा MANTIS_MODEL_NAME	"VP-1034"
#घोषणा MANTIS_DEV_TYPE		"DVB-S/DSS"

पूर्णांक vp1034_set_voltage(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा mantis_pci *mantis = fe->dvb->priv;

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		dprपूर्णांकk(MANTIS_ERROR, 1, "Polarization=[13V]");
		mantis_gpio_set_bits(mantis, 13, 1);
		mantis_gpio_set_bits(mantis, 14, 0);
		अवरोध;
	हाल SEC_VOLTAGE_18:
		dprपूर्णांकk(MANTIS_ERROR, 1, "Polarization=[18V]");
		mantis_gpio_set_bits(mantis, 13, 1);
		mantis_gpio_set_bits(mantis, 14, 1);
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		dprपूर्णांकk(MANTIS_ERROR, 1, "Frontend (dummy) POWERDOWN");
		अवरोध;
	शेष:
		dprपूर्णांकk(MANTIS_ERROR, 1, "Invalid = (%d)", (u32) voltage);
		वापस -EINVAL;
	पूर्ण
	mmग_लिखो(0x00, MANTIS_GPIF_DOUT);

	वापस 0;
पूर्ण

अटल पूर्णांक vp1034_frontend_init(काष्ठा mantis_pci *mantis, काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_adapter *adapter	= &mantis->adapter;

	पूर्णांक err = 0;

	err = mantis_frontend_घातer(mantis, POWER_ON);
	अगर (err == 0) अणु
		mantis_frontend_soft_reset(mantis);
		msleep(250);

		dprपूर्णांकk(MANTIS_ERROR, 1, "Probing for MB86A16 (DVB-S/DSS)");
		fe = dvb_attach(mb86a16_attach, &vp1034_mb86a16_config, adapter);
		अगर (fe) अणु
			dprपूर्णांकk(MANTIS_ERROR, 1,
			"found MB86A16 DVB-S/DSS frontend @0x%02x",
			vp1034_mb86a16_config.demod_address);

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

काष्ठा mantis_hwconfig vp1034_config = अणु
	.model_name	= MANTIS_MODEL_NAME,
	.dev_type	= MANTIS_DEV_TYPE,
	.ts_size	= MANTIS_TS_204,

	.baud_rate	= MANTIS_BAUD_9600,
	.parity		= MANTIS_PARITY_NONE,
	.bytes		= 0,

	.frontend_init	= vp1034_frontend_init,
	.घातer		= GPIF_A12,
	.reset		= GPIF_A13,
पूर्ण;
