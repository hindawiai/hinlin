<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Driver क्रम Zarlink MT312 Satellite Channel Decoder

    Copyright (C) 2003 Andreas Oberritter <obi@linuxtv.org>


    References:
    http://products.zarlink.com/product_profiles/MT312.hपंचांग
    http://products.zarlink.com/product_profiles/SL1935.hपंचांग
*/

#अगर_अघोषित MT312_H
#घोषणा MT312_H

#समावेश <linux/dvb/frontend.h>

काष्ठा mt312_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* inverted voltage setting */
	अचिन्हित पूर्णांक voltage_inverted:1;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_MT312)
काष्ठा dvb_frontend *mt312_attach(स्थिर काष्ठा mt312_config *config,
					काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *mt312_attach(
	स्थिर काष्ठा mt312_config *config, काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_MT312 */

#पूर्ण_अगर /* MT312_H */
