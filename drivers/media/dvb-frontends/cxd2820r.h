<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Sony CXD2820R demodulator driver
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */


#अगर_अघोषित CXD2820R_H
#घोषणा CXD2820R_H

#समावेश <linux/dvb/frontend.h>

#घोषणा CXD2820R_GPIO_D (0 << 0) /* disable */
#घोषणा CXD2820R_GPIO_E (1 << 0) /* enable */
#घोषणा CXD2820R_GPIO_O (0 << 1) /* output */
#घोषणा CXD2820R_GPIO_I (1 << 1) /* input */
#घोषणा CXD2820R_GPIO_L (0 << 2) /* output low */
#घोषणा CXD2820R_GPIO_H (1 << 2) /* output high */

#घोषणा CXD2820R_TS_SERIAL        0x08
#घोषणा CXD2820R_TS_SERIAL_MSB    0x28
#घोषणा CXD2820R_TS_PARALLEL      0x30
#घोषणा CXD2820R_TS_PARALLEL_MSB  0x70

/*
 * I2C address: 0x6c, 0x6d
 */

/**
 * काष्ठा cxd2820r_platक्रमm_data - Platक्रमm data क्रम the cxd2820r driver
 * @ts_mode: TS mode.
 * @ts_clk_inv: TS घड़ी inverted.
 * @अगर_agc_polarity: IF AGC polarity.
 * @spec_inv: Input spectrum inverted.
 * @gpio_chip_base: GPIO.
 * @get_dvb_frontend: Get DVB frontend.
 */
काष्ठा cxd2820r_platक्रमm_data अणु
	u8 ts_mode;
	bool ts_clk_inv;
	bool अगर_agc_polarity;
	bool spec_inv;
	पूर्णांक **gpio_chip_base;

	काष्ठा dvb_frontend* (*get_dvb_frontend)(काष्ठा i2c_client *);
/* निजी: For legacy media attach wrapper. Do not set value. */
	bool attach_in_use;
पूर्ण;

/**
 * काष्ठा cxd2820r_config - configuration क्रम cxd2020r demod
 *
 * @i2c_address: Demodulator I2C address. Driver determines DVB-C slave I2C
 *		 address स्वतःmatically from master address.
 *		 Default: none, must set. Values: 0x6c, 0x6d.
 * @ts_mode:	TS output mode. Default: none, must set. Values: FIXME?
 * @ts_घड़ी_inv: TS घड़ी inverted. Default: 0. Values: 0, 1.
 * @अगर_agc_polarity: Default: 0. Values: 0, 1
 * @spec_inv:	Spectrum inversion. Default: 0. Values: 0, 1.
 */
काष्ठा cxd2820r_config अणु
	/* Demodulator I2C address.
	 * Driver determines DVB-C slave I2C address स्वतःmatically from master
	 * address.
	 * Default: none, must set
	 * Values: 0x6c, 0x6d
	 */
	u8 i2c_address;

	/* TS output mode.
	 * Default: none, must set.
	 * Values:
	 */
	u8 ts_mode;

	/* TS घड़ी inverted.
	 * Default: 0
	 * Values: 0, 1
	 */
	bool ts_घड़ी_inv;

	/* IF AGC polarity.
	 * Default: 0
	 * Values: 0, 1
	 */
	bool अगर_agc_polarity;

	/* Spectrum inversion.
	 * Default: 0
	 * Values: 0, 1
	 */
	bool spec_inv;
पूर्ण;


#अगर IS_REACHABLE(CONFIG_DVB_CXD2820R)
/**
 * cxd2820r_attach - Attach a cxd2820r demod
 *
 * @config: poपूर्णांकer to &काष्ठा cxd2820r_config with demod configuration.
 * @i2c: i2c adapter to use.
 * @gpio_chip_base: अगर zero, disables GPIO setting. Otherwise, अगर
 *		    CONFIG_GPIOLIB is set dynamically allocate
 *		    gpio base; अगर is not set, use its value to
 *		    setup the GPIO pins.
 *
 * वापस: FE poपूर्णांकer on success, शून्य on failure.
 */
बाह्य काष्ठा dvb_frontend *cxd2820r_attach(
	स्थिर काष्ठा cxd2820r_config *config,
	काष्ठा i2c_adapter *i2c,
	पूर्णांक *gpio_chip_base
);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *cxd2820r_attach(
	स्थिर काष्ठा cxd2820r_config *config,
	काष्ठा i2c_adapter *i2c,
	पूर्णांक *gpio_chip_base
)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* CXD2820R_H */
