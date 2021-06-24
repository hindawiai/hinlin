<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2008 Simtec Electronics
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/

/*
 * NOTE: Code in this file is not used when booting with Device Tree support.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/irq.h>

#समावेश <linux/soc/samsung/s3c-pm.h>
#समावेश "regs-clock.h"

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश "sdhci.h"
#समावेश "adc-core.h"
#समावेश "iic-core.h"

#समावेश "ata-core-s3c64xx.h"
#समावेश "s3c64xx.h"
#समावेश "onenand-core-s3c64xx.h"

व्योम __init s3c6410_map_io(व्योम)
अणु
	/* initialise device inक्रमmation early */
	s3c6410_शेष_sdhci0();
	s3c6410_शेष_sdhci1();
	s3c6410_शेष_sdhci2();

	/* the i2c devices are directly compatible with s3c2440 */
	s3c_i2c0_setname("s3c2440-i2c");
	s3c_i2c1_setname("s3c2440-i2c");

	s3c_adc_setname("s3c64xx-adc");
	s3c_device_nand.name = "s3c6400-nand";
	s3c_onenand_setname("s3c6410-onenand");
	s3c64xx_onenand1_setname("s3c6410-onenand");
	s3c_cfcon_setname("s3c64xx-pata");
पूर्ण

व्योम __init s3c6410_init_irq(व्योम)
अणु
	/* VIC0 is missing IRQ7, VIC1 is fully populated. */
	s3c64xx_init_irq(~0 & ~(1 << 7), ~0);
पूर्ण

काष्ठा bus_type s3c6410_subsys = अणु
	.name		= "s3c6410-core",
	.dev_name	= "s3c6410-core",
पूर्ण;

अटल काष्ठा device s3c6410_dev = अणु
	.bus	= &s3c6410_subsys,
पूर्ण;

अटल पूर्णांक __init s3c6410_core_init(व्योम)
अणु
	/* Not applicable when using DT. */
	अगर (of_have_populated_dt() || !soc_is_s3c64xx())
		वापस 0;

	वापस subsys_प्रणाली_रेजिस्टर(&s3c6410_subsys, शून्य);
पूर्ण

core_initcall(s3c6410_core_init);

पूर्णांक __init s3c6410_init(व्योम)
अणु
	prपूर्णांकk("S3C6410: Initialising architecture\n");

	वापस device_रेजिस्टर(&s3c6410_dev);
पूर्ण
