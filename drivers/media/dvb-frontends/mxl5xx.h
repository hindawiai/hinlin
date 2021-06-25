<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the MaxLinear MxL5xx family of tuners/demods
 *
 * Copyright (C) 2014-2015 Ralph Metzler <rjkm@metzlerbros.de>
 *                         Marcus Metzler <mocm@metzlerbros.de>
 *                         developed क्रम Digital Devices GmbH
 *
 * based on code:
 * Copyright (c) 2011-2013 MaxLinear, Inc. All rights reserved
 * which was released under GPL V2
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _MXL5XX_H_
#घोषणा _MXL5XX_H_

#समावेश <linux/types.h>
#समावेश <linux/i2c.h>

#समावेश <media/dvb_frontend.h>

काष्ठा mxl5xx_cfg अणु
	u8   adr;
	u8   type;
	u32  cap;
	u32  clk;
	u32  ts_clk;

	u8  *fw;
	u32  fw_len;

	पूर्णांक (*fw_पढ़ो)(व्योम *priv, u8 *buf, u32 len);
	व्योम *fw_priv;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_MXL5XX)

बाह्य काष्ठा dvb_frontend *mxl5xx_attach(काष्ठा i2c_adapter *i2c,
	काष्ठा mxl5xx_cfg *cfg, u32 demod, u32 tuner,
	पूर्णांक (**fn_set_input)(काष्ठा dvb_frontend *, पूर्णांक));

#अन्यथा

अटल अंतरभूत काष्ठा dvb_frontend *mxl5xx_attach(काष्ठा i2c_adapter *i2c,
	काष्ठा mxl5xx_cfg *cfg, u32 demod, u32 tuner,
	पूर्णांक (**fn_set_input)(काष्ठा dvb_frontend *, पूर्णांक))
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DVB_MXL5XX */

#पूर्ण_अगर /* _MXL5XX_H_ */
