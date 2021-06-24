<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the ST STV6111 tuner
 *
 * Copyright (C) 2014 Digital Devices GmbH
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

#अगर_अघोषित _STV6111_H_
#घोषणा _STV6111_H_

#अगर IS_REACHABLE(CONFIG_DVB_STV6111)

काष्ठा dvb_frontend *stv6111_attach(काष्ठा dvb_frontend *fe,
				    काष्ठा i2c_adapter *i2c, u8 adr);

#अन्यथा

अटल अंतरभूत काष्ठा dvb_frontend *stv6111_attach(काष्ठा dvb_frontend *fe,
						  काष्ठा i2c_adapter *i2c,
						  u8 adr)
अणु
	pr_warn("%s: Driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DVB_STV6111 */

#पूर्ण_अगर /* _STV6111_H_ */
