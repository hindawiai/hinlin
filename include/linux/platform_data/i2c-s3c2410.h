<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2004-2009 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - I2C Controller platक्रमm_device info
*/

#अगर_अघोषित __I2C_S3C2410_H
#घोषणा __I2C_S3C2410_H __खाता__

#घोषणा S3C_IICFLG_FILTER	(1<<0)	/* enable s3c2440 filter */

काष्ठा platक्रमm_device;

/**
 *	काष्ठा s3c2410_platक्रमm_i2c - Platक्रमm data क्रम s3c I2C.
 *	@bus_num: The bus number to use (अगर possible).
 *	@flags: Any flags क्रम the I2C bus (E.g. S3C_IICFLK_FILTER).
 *	@slave_addr: The I2C address क्रम the slave device (अगर enabled).
 *	@frequency: The desired frequency in Hz of the bus.  This is
 *                  guaranteed to not be exceeded.  If the caller करोes
 *                  not care, use zero and the driver will select a
 *                  useful शेष.
 *	@sda_delay: The delay (in ns) applied to SDA edges.
 *	@cfg_gpio: A callback to configure the pins क्रम I2C operation.
 */
काष्ठा s3c2410_platक्रमm_i2c अणु
	पूर्णांक		bus_num;
	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	slave_addr;
	अचिन्हित दीर्घ	frequency;
	अचिन्हित पूर्णांक	sda_delay;

	व्योम	(*cfg_gpio)(काष्ठा platक्रमm_device *dev);
पूर्ण;

/**
 * s3c_i2c0_set_platdata - set platक्रमm data क्रम i2c0 device
 * @i2c: The platक्रमm data to set, or शून्य क्रम शेष data.
 *
 * Register the given platक्रमm data क्रम use with the i2c0 device. This
 * call copies the platक्रमm data, so the caller can use __initdata क्रम
 * their copy.
 *
 * This call will set cfg_gpio अगर is null to the शेष platक्रमm
 * implementation.
 *
 * Any user of s3c_device_i2c0 should call this, even अगर it is with
 * शून्य to ensure that the device is given the शेष platक्रमm data
 * as the driver will no दीर्घer carry शेषs.
 */
बाह्य व्योम s3c_i2c0_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *i2c);
बाह्य व्योम s3c_i2c1_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *i2c);
बाह्य व्योम s3c_i2c2_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *i2c);
बाह्य व्योम s3c_i2c3_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *i2c);
बाह्य व्योम s3c_i2c4_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *i2c);
बाह्य व्योम s3c_i2c5_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *i2c);
बाह्य व्योम s3c_i2c6_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *i2c);
बाह्य व्योम s3c_i2c7_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *i2c);
बाह्य व्योम s5p_i2c_hdmiphy_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *i2c);

/* defined by architecture to configure gpio */
बाह्य व्योम s3c_i2c0_cfg_gpio(काष्ठा platक्रमm_device *dev);
बाह्य व्योम s3c_i2c1_cfg_gpio(काष्ठा platक्रमm_device *dev);
बाह्य व्योम s3c_i2c2_cfg_gpio(काष्ठा platक्रमm_device *dev);
बाह्य व्योम s3c_i2c3_cfg_gpio(काष्ठा platक्रमm_device *dev);
बाह्य व्योम s3c_i2c4_cfg_gpio(काष्ठा platक्रमm_device *dev);
बाह्य व्योम s3c_i2c5_cfg_gpio(काष्ठा platक्रमm_device *dev);
बाह्य व्योम s3c_i2c6_cfg_gpio(काष्ठा platक्रमm_device *dev);
बाह्य व्योम s3c_i2c7_cfg_gpio(काष्ठा platक्रमm_device *dev);

बाह्य काष्ठा s3c2410_platक्रमm_i2c शेष_i2c_data;

#पूर्ण_अगर /* __I2C_S3C2410_H */
