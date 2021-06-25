<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ZyDAS ZD1301 driver (demodulator)
 *
 * Copyright (C) 2015 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित ZD1301_DEMOD_H
#घोषणा ZD1301_DEMOD_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

/**
 * काष्ठा zd1301_demod_platक्रमm_data - Platक्रमm data क्रम the zd1301_demod driver
 * @reg_priv: First argument of reg_पढ़ो and reg_ग_लिखो callbacks.
 * @reg_पढ़ो: Register पढ़ो callback.
 * @reg_ग_लिखो: Register ग_लिखो callback.
 */
काष्ठा zd1301_demod_platक्रमm_data अणु
	व्योम *reg_priv;
	पूर्णांक (*reg_पढ़ो)(व्योम *, u16, u8 *);
	पूर्णांक (*reg_ग_लिखो)(व्योम *, u16, u8);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_ZD1301_DEMOD)
/**
 * zd1301_demod_get_dvb_frontend() - Get poपूर्णांकer to DVB frontend
 * @pdev: Poपूर्णांकer to platक्रमm device
 *
 * Return: Poपूर्णांकer to DVB frontend which given platक्रमm device owns.
 */
काष्ठा dvb_frontend *zd1301_demod_get_dvb_frontend(काष्ठा platक्रमm_device *pdev);

/**
 * zd1301_demod_get_i2c_adapter() - Get poपूर्णांकer to I2C adapter
 * @pdev: Poपूर्णांकer to platक्रमm device
 *
 * Return: Poपूर्णांकer to I2C adapter which given platक्रमm device owns.
 */
काष्ठा i2c_adapter *zd1301_demod_get_i2c_adapter(काष्ठा platक्रमm_device *pdev);

#अन्यथा

अटल अंतरभूत काष्ठा dvb_frontend *zd1301_demod_get_dvb_frontend(काष्ठा platक्रमm_device *dev)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);

	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा i2c_adapter *zd1301_demod_get_i2c_adapter(काष्ठा platक्रमm_device *dev)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);

	वापस शून्य;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* ZD1301_DEMOD_H */
