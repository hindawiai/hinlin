<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2005 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://armlinux.simtec.co.uk/
 *
 * S3C - HWMon पूर्णांकerface क्रम ADC
*/

#अगर_अघोषित __HWMON_S3C_H__
#घोषणा __HWMON_S3C_H__

/**
 * s3c_hwmon_chcfg - channel configuration
 * @name: The name to give this channel.
 * @mult: Multiply the ADC value पढ़ो by this.
 * @भाग: Divide the value from the ADC by this.
 *
 * The value पढ़ो from the ADC is converted to a value that
 * hwmon expects (mV) by result = (value_पढ़ो * @mult) / @भाग.
 */
काष्ठा s3c_hwmon_chcfg अणु
	स्थिर अक्षर	*name;
	अचिन्हित पूर्णांक	mult;
	अचिन्हित पूर्णांक	भाग;
पूर्ण;

/**
 * s3c_hwmon_pdata - HWMON platक्रमm data
 * @in: One configuration क्रम each possible channel used.
 */
काष्ठा s3c_hwmon_pdata अणु
	काष्ठा s3c_hwmon_chcfg	*in[8];
पूर्ण;

/**
 * s3c_hwmon_set_platdata - Set platक्रमm data क्रम S3C HWMON device
 * @pd: Platक्रमm data to रेजिस्टर to device.
 *
 * Register the given platक्रमm data क्रम use with the S3C HWMON device.
 * The call will copy the platक्रमm data, so the board definitions can
 * make the काष्ठाure itself __initdata.
 */
बाह्य व्योम __init s3c_hwmon_set_platdata(काष्ठा s3c_hwmon_pdata *pd);

#पूर्ण_अगर /* __HWMON_S3C_H__ */
