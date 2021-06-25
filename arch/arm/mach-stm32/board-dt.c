<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) Maxime Coquelin 2015
 * Copyright (C) STMicroelectronics 2017
 * Author:  Maxime Coquelin <mcoquelin.sपंचांग32@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/mach/arch.h>
#अगर_घोषित CONFIG_ARM_SINGLE_ARMV7M
#समावेश <यंत्र/v7m.h>
#पूर्ण_अगर

अटल स्थिर अक्षर *स्थिर sपंचांग32_compat[] __initस्थिर = अणु
	"st,stm32f429",
	"st,stm32f469",
	"st,stm32f746",
	"st,stm32f769",
	"st,stm32h743",
	"st,stm32h750",
	"st,stm32mp157",
	शून्य
पूर्ण;

DT_MACHINE_START(STM32DT, "STM32 (Device Tree Support)")
	.dt_compat = sपंचांग32_compat,
#अगर_घोषित CONFIG_ARM_SINGLE_ARMV7M
	.restart = armv7m_restart,
#पूर्ण_अगर
MACHINE_END
