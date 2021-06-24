<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2011 Wolfson Microelectronics, plc
// Copyright (c) 2011 Samsung Electronics Co., Ltd.
//		http://www.samsung.com

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <linux/समय.स>

#समावेश <यंत्र/cpuidle.h>

#समावेश "cpu.h"
#समावेश "map.h"

#समावेश "regs-sys-s3c64xx.h"
#समावेश "regs-syscon-power-s3c64xx.h"

अटल पूर्णांक s3c64xx_enter_idle(काष्ठा cpuidle_device *dev,
			      काष्ठा cpuidle_driver *drv,
			      पूर्णांक index)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/* Setup PWRCFG to enter idle mode */
	पंचांगp = __raw_पढ़ोl(S3C64XX_PWR_CFG);
	पंचांगp &= ~S3C64XX_PWRCFG_CFG_WFI_MASK;
	पंचांगp |= S3C64XX_PWRCFG_CFG_WFI_IDLE;
	__raw_ग_लिखोl(पंचांगp, S3C64XX_PWR_CFG);

	cpu_करो_idle();

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver s3c64xx_cpuidle_driver = अणु
	.name	= "s3c64xx_cpuidle",
	.owner  = THIS_MODULE,
	.states = अणु
		अणु
			.enter            = s3c64xx_enter_idle,
			.निकास_latency     = 1,
			.target_residency = 1,
			.name             = "IDLE",
			.desc             = "System active, ARM gated",
		पूर्ण,
	पूर्ण,
	.state_count = 1,
पूर्ण;

अटल पूर्णांक __init s3c64xx_init_cpuidle(व्योम)
अणु
	अगर (soc_is_s3c64xx())
		वापस cpuidle_रेजिस्टर(&s3c64xx_cpuidle_driver, शून्य);
	वापस 0;
पूर्ण
device_initcall(s3c64xx_init_cpuidle);
