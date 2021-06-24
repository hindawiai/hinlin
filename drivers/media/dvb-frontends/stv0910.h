<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the ST STV0910 DVB-S/S2 demodulator.
 *
 * Copyright (C) 2014-2015 Ralph Metzler <rjkm@metzlerbros.de>
 *                         Marcus Metzler <mocm@metzlerbros.de>
 *                         developed क्रम Digital Devices GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _STV0910_H_
#घोषणा _STV0910_H_

#समावेश <linux/types.h>
#समावेश <linux/i2c.h>

काष्ठा stv0910_cfg अणु
	u32 clk;
	u8  adr;
	u8  parallel;
	u8  rptlvl;
	u8  single;
	u8  tsspeed;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_STV0910)

काष्ठा dvb_frontend *stv0910_attach(काष्ठा i2c_adapter *i2c,
				    काष्ठा stv0910_cfg *cfg, पूर्णांक nr);

#अन्यथा

अटल अंतरभूत काष्ठा dvb_frontend *stv0910_attach(काष्ठा i2c_adapter *i2c,
						  काष्ठा stv0910_cfg *cfg,
						  पूर्णांक nr)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DVB_STV0910 */

#पूर्ण_अगर /* _STV0910_H_ */
