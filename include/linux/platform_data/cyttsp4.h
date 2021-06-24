<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Header file क्रम:
 * Cypress TrueTouch(TM) Standard Product (TTSP) touchscreen drivers.
 * For use with Cypress Txx3xx parts.
 * Supported parts include:
 * CY8CTST341
 * CY8CTMA340
 *
 * Copyright (C) 2009, 2010, 2011 Cypress Semiconductor, Inc.
 * Copyright (C) 2012 Javier Martinez Canillas <javier@करोजबतक0.org>
 *
 * Contact Cypress Semiconductor at www.cypress.com (kev@cypress.com)
 */
#अगर_अघोषित _CYTTSP4_H_
#घोषणा _CYTTSP4_H_

#घोषणा CYTTSP4_MT_NAME "cyttsp4_mt"
#घोषणा CYTTSP4_I2C_NAME "cyttsp4_i2c_adapter"
#घोषणा CYTTSP4_SPI_NAME "cyttsp4_spi_adapter"

#घोषणा CY_TOUCH_SETTINGS_MAX 32

काष्ठा touch_framework अणु
	स्थिर uपूर्णांक16_t  *असल;
	uपूर्णांक8_t         size;
	uपूर्णांक8_t         enable_vkeys;
पूर्ण __packed;

काष्ठा cyttsp4_mt_platक्रमm_data अणु
	काष्ठा touch_framework *frmwrk;
	अचिन्हित लघु flags;
	अक्षर स्थिर *inp_dev_name;
पूर्ण;

काष्ठा touch_settings अणु
	स्थिर uपूर्णांक8_t *data;
	uपूर्णांक32_t size;
	uपूर्णांक8_t tag;
पूर्ण __packed;

काष्ठा cyttsp4_core_platक्रमm_data अणु
	पूर्णांक irq_gpio;
	पूर्णांक rst_gpio;
	पूर्णांक level_irq_udelay;
	पूर्णांक (*xres)(काष्ठा cyttsp4_core_platक्रमm_data *pdata,
		काष्ठा device *dev);
	पूर्णांक (*init)(काष्ठा cyttsp4_core_platक्रमm_data *pdata,
		पूर्णांक on, काष्ठा device *dev);
	पूर्णांक (*घातer)(काष्ठा cyttsp4_core_platक्रमm_data *pdata,
		पूर्णांक on, काष्ठा device *dev, atomic_t *ignore_irq);
	पूर्णांक (*irq_stat)(काष्ठा cyttsp4_core_platक्रमm_data *pdata,
		काष्ठा device *dev);
	काष्ठा touch_settings *sett[CY_TOUCH_SETTINGS_MAX];
पूर्ण;

काष्ठा cyttsp4_platक्रमm_data अणु
	काष्ठा cyttsp4_core_platक्रमm_data *core_pdata;
	काष्ठा cyttsp4_mt_platक्रमm_data *mt_pdata;
पूर्ण;

#पूर्ण_अगर /* _CYTTSP4_H_ */
