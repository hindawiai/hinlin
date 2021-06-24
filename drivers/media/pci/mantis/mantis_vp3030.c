<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis VP-3030 driver

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

#समावेश "zl10353.h"
#समावेश "tda665x.h"
#समावेश "mantis_common.h"
#समावेश "mantis_ioc.h"
#समावेश "mantis_dvb.h"
#समावेश "mantis_vp3030.h"

अटल काष्ठा zl10353_config mantis_vp3030_config = अणु
	.demod_address		= 0x0f,
पूर्ण;

अटल काष्ठा tda665x_config env57h12d5_config = अणु
	.name			= "ENV57H12D5 (ET-50DT)",
	.addr			= 0x60,
	.frequency_min		=  47 * MHz,
	.frequency_max		= 862 * MHz,
	.frequency_offst	=   3616667,
	.ref_multiplier		= 6, /* 1/6 MHz */
	.ref_भागider		= 100000, /* 1/6 MHz */
पूर्ण;

#घोषणा MANTIS_MODEL_NAME	"VP-3030"
#घोषणा MANTIS_DEV_TYPE		"DVB-T"


अटल पूर्णांक vp3030_frontend_init(काष्ठा mantis_pci *mantis, काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_adapter *adapter	= &mantis->adapter;
	काष्ठा mantis_hwconfig *config	= mantis->hwconfig;
	पूर्णांक err = 0;

	mantis_gpio_set_bits(mantis, config->reset, 0);
	msleep(100);
	err = mantis_frontend_घातer(mantis, POWER_ON);
	msleep(100);
	mantis_gpio_set_bits(mantis, config->reset, 1);

	अगर (err == 0) अणु
		msleep(250);
		dprपूर्णांकk(MANTIS_ERROR, 1, "Probing for 10353 (DVB-T)");
		fe = dvb_attach(zl10353_attach, &mantis_vp3030_config, adapter);

		अगर (!fe)
			वापस -1;

		dvb_attach(tda665x_attach, fe, &env57h12d5_config, adapter);
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

काष्ठा mantis_hwconfig vp3030_config = अणु
	.model_name	= MANTIS_MODEL_NAME,
	.dev_type	= MANTIS_DEV_TYPE,
	.ts_size	= MANTIS_TS_188,

	.baud_rate	= MANTIS_BAUD_9600,
	.parity		= MANTIS_PARITY_NONE,
	.bytes		= 0,

	.frontend_init	= vp3030_frontend_init,
	.घातer		= GPIF_A12,
	.reset		= GPIF_A13,

	.i2c_mode	= MANTIS_BYTE_MODE
पूर्ण;
