<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ARM IOC/IOMD i2c driver.
 *
 *  Copyright (C) 2000 Russell King
 *
 *  On Acorn machines, the following i2c devices are on the bus:
 *	- PCF8583 real समय घड़ी & अटल RAM
 */
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/पन.स>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/hardware/ioc.h>

#घोषणा FORCE_ONES	0xdc
#घोषणा SCL		0x02
#घोषणा SDA		0x01

/*
 * We must preserve all non-i2c output bits in IOC_CONTROL.
 * Note also that we need to preserve the value of SCL and
 * SDA outमाला_दो as well (which may be dअगरferent from the
 * values पढ़ो back from IOC_CONTROL).
 */
अटल u_पूर्णांक क्रमce_ones;

अटल व्योम ioc_setscl(व्योम *data, पूर्णांक state)
अणु
	u_पूर्णांक ioc_control = ioc_पढ़ोb(IOC_CONTROL) & ~(SCL | SDA);
	u_पूर्णांक ones = क्रमce_ones;

	अगर (state)
		ones |= SCL;
	अन्यथा
		ones &= ~SCL;

	क्रमce_ones = ones;

 	ioc_ग_लिखोb(ioc_control | ones, IOC_CONTROL);
पूर्ण

अटल व्योम ioc_setsda(व्योम *data, पूर्णांक state)
अणु
	u_पूर्णांक ioc_control = ioc_पढ़ोb(IOC_CONTROL) & ~(SCL | SDA);
	u_पूर्णांक ones = क्रमce_ones;

	अगर (state)
		ones |= SDA;
	अन्यथा
		ones &= ~SDA;

	क्रमce_ones = ones;

 	ioc_ग_लिखोb(ioc_control | ones, IOC_CONTROL);
पूर्ण

अटल पूर्णांक ioc_माला_लोcl(व्योम *data)
अणु
	वापस (ioc_पढ़ोb(IOC_CONTROL) & SCL) != 0;
पूर्ण

अटल पूर्णांक ioc_माला_लोda(व्योम *data)
अणु
	वापस (ioc_पढ़ोb(IOC_CONTROL) & SDA) != 0;
पूर्ण

अटल काष्ठा i2c_algo_bit_data ioc_data = अणु
	.setsda		= ioc_setsda,
	.setscl		= ioc_setscl,
	.माला_लोda		= ioc_माला_लोda,
	.माला_लोcl		= ioc_माला_लोcl,
	.udelay		= 80,
	.समयout	= HZ,
पूर्ण;

अटल काष्ठा i2c_adapter ioc_ops = अणु
	.nr			= 0,
	.name			= "ioc",
	.algo_data		= &ioc_data,
पूर्ण;

अटल पूर्णांक __init i2c_ioc_init(व्योम)
अणु
	क्रमce_ones = FORCE_ONES | SCL | SDA;

	वापस i2c_bit_add_numbered_bus(&ioc_ops);
पूर्ण

module_init(i2c_ioc_init);

MODULE_AUTHOR("Russell King <linux@armlinux.org.uk>");
MODULE_DESCRIPTION("ARM IOC/IOMD i2c driver");
MODULE_LICENSE("GPL v2");
