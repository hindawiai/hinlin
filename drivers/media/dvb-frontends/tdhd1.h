<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * tdhd1.h - ALPS TDHD1-204A tuner support
 *
 * Copyright (C) 2008 Oliver Endriss <o.endriss@gmx.de>
 *
 * The project's page is at https://linuxtv.org
 */

#अगर_अघोषित TDHD1_H
#घोषणा TDHD1_H

#समावेश "tda1004x.h"

अटल पूर्णांक alps_tdhd1_204_request_firmware(काष्ठा dvb_frontend *fe, स्थिर काष्ठा firmware **fw, अक्षर *name);

अटल काष्ठा tda1004x_config alps_tdhd1_204a_config = अणु
	.demod_address = 0x8,
	.invert = 1,
	.invert_oclk = 0,
	.xtal_freq = TDA10046_XTAL_4M,
	.agc_config = TDA10046_AGC_DEFAULT,
	.अगर_freq = TDA10046_FREQ_3617,
	.request_firmware = alps_tdhd1_204_request_firmware
पूर्ण;

अटल पूर्णांक alps_tdhd1_204a_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा i2c_adapter *i2c = fe->tuner_priv;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x61, .flags = 0, .buf = data, .len = माप(data) पूर्ण;
	u32 भाग;

	भाग = (p->frequency + 36166666) / 166666;

	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = 0x85;

	अगर (p->frequency >= 174000000 && p->frequency <= 230000000)
		data[3] = 0x02;
	अन्यथा अगर (p->frequency >= 470000000 && p->frequency <= 823000000)
		data[3] = 0x0C;
	अन्यथा अगर (p->frequency > 823000000 && p->frequency <= 862000000)
		data[3] = 0x8C;
	अन्यथा
		वापस -EINVAL;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(i2c, &msg, 1) != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

#पूर्ण_अगर /* TDHD1_H */
