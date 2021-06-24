<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2010 Samsung Electronics Co., Ltd.
//		http://www.samsung.com/
//
// S3C64XX setup inक्रमmation क्रम IDE

#समावेश <linux/kernel.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पन.स>

#समावेश <linux/platक्रमm_data/ata-samsung_cf.h>

#समावेश "map.h"
#समावेश "regs-clock.h"
#समावेश "gpio-cfg.h"
#समावेश "gpio-samsung.h"

व्योम s3c64xx_ide_setup_gpio(व्योम)
अणु
	u32 reg;

	reg = पढ़ोl(S3C_MEM_SYS_CFG) & (~0x3f);

	/* Independent CF पूर्णांकerface, CF chip select configuration */
	ग_लिखोl(reg | MEM_SYS_CFG_INDEP_CF |
		MEM_SYS_CFG_EBI_FIX_PRI_CFCON, S3C_MEM_SYS_CFG);

	s3c_gpio_cfgpin(S3C64XX_GPB(4), S3C_GPIO_SFN(4));

	/* Set XhiDATA[15:0] pins as CF Data[15:0] */
	s3c_gpio_cfgpin_range(S3C64XX_GPK(0), 16, S3C_GPIO_SFN(5));

	/* Set XhiADDR[2:0] pins as CF ADDR[2:0] */
	s3c_gpio_cfgpin_range(S3C64XX_GPL(0), 3, S3C_GPIO_SFN(6));

	/* Set Xhi ctrl pins as CF ctrl pins(IORDY, IOWR, IORD, CE[0:1]) */
	s3c_gpio_cfgpin(S3C64XX_GPM(5), S3C_GPIO_SFN(1));
	s3c_gpio_cfgpin_range(S3C64XX_GPM(0), 5, S3C_GPIO_SFN(6));
पूर्ण
