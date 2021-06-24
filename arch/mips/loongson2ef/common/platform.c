<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */

#समावेश <linux/err.h>
#समावेश <linux/smp.h>
#समावेश <linux/platक्रमm_device.h>

अटल काष्ठा platक्रमm_device loongson2_cpufreq_device = अणु
	.name = "loongson2_cpufreq",
	.id = -1,
पूर्ण;

अटल पूर्णांक __init loongson2_cpufreq_init(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;

	/* Only 2F revision and it's successors support CPUFreq */
	अगर ((c->processor_id & PRID_REV_MASK) >= PRID_REV_LOONGSON2F)
		वापस platक्रमm_device_रेजिस्टर(&loongson2_cpufreq_device);

	वापस -ENODEV;
पूर्ण

arch_initcall(loongson2_cpufreq_init);
