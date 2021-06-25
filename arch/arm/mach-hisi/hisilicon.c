<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (HiSilicon's SoC based) flattened device tree enabled machine
 *
 * Copyright (c) 2012-2013 HiSilicon Ltd.
 * Copyright (c) 2012-2013 Linaro Ltd.
 *
 * Author: Haojian Zhuang <haojian.zhuang@linaro.org>
*/

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/irqchip.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#घोषणा HI3620_SYSCTRL_PHYS_BASE		0xfc802000
#घोषणा HI3620_SYSCTRL_VIRT_BASE		0xfe802000

/*
 * This table is only क्रम optimization. Since ioremap() could always share
 * the same mapping अगर it's defined as अटल IO mapping.
 *
 * Without this table, प्रणाली could also work. The cost is some भव address
 * spaces wasted since ioremap() may be called multi बार क्रम the same
 * IO space.
 */
अटल काष्ठा map_desc hi3620_io_desc[] __initdata = अणु
	अणु
		/* sysctrl */
		.pfn		= __phys_to_pfn(HI3620_SYSCTRL_PHYS_BASE),
		.भव	= HI3620_SYSCTRL_VIRT_BASE,
		.length		= 0x1000,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल व्योम __init hi3620_map_io(व्योम)
अणु
	debug_ll_io_init();
	iotable_init(hi3620_io_desc, ARRAY_SIZE(hi3620_io_desc));
पूर्ण

अटल स्थिर अक्षर *स्थिर hi3xxx_compat[] __initस्थिर = अणु
	"hisilicon,hi3620-hi4511",
	शून्य,
पूर्ण;

DT_MACHINE_START(HI3620, "Hisilicon Hi3620 (Flattened Device Tree)")
	.map_io		= hi3620_map_io,
	.dt_compat	= hi3xxx_compat,
MACHINE_END
