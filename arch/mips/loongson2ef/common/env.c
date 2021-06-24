<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Based on Ocelot Linux port, which is
 * Copyright 2001 MontaVista Software Inc.
 * Author: jsun@mvista.com or jsun@junsun.net
 *
 * Copyright 2003 ICT CAS
 * Author: Michael Guo <guoyi@ict.ac.cn>
 *
 * Copyright (C) 2007 Lemote Inc. & Institute of Computing Technology
 * Author: Fuxin Zhang, zhangfx@lemote.com
 *
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */
#समावेश <linux/export.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/fw/fw.h>
#समावेश <loongson.h>

u32 cpu_घड़ी_freq;
EXPORT_SYMBOL(cpu_घड़ी_freq);

व्योम __init prom_init_env(व्योम)
अणु
	/* pmon passes arguments in 32bit poपूर्णांकers */
	अचिन्हित पूर्णांक processor_id;

	cpu_घड़ी_freq = fw_दो_पर्याl("cpuclock");
	memsize = fw_दो_पर्याl("memsize");
	highmemsize = fw_दो_पर्याl("highmemsize");

	अगर (memsize == 0)
		memsize = 256;

	pr_info("memsize=%u, highmemsize=%u\n", memsize, highmemsize);

	अगर (cpu_घड़ी_freq == 0) अणु
		processor_id = (&current_cpu_data)->processor_id;
		चयन (processor_id & PRID_REV_MASK) अणु
		हाल PRID_REV_LOONGSON2E:
			cpu_घड़ी_freq = 533080000;
			अवरोध;
		हाल PRID_REV_LOONGSON2F:
			cpu_घड़ी_freq = 797000000;
			अवरोध;
		शेष:
			cpu_घड़ी_freq = 100000000;
			अवरोध;
		पूर्ण
	पूर्ण
	pr_info("CpuClock = %u\n", cpu_घड़ी_freq);
पूर्ण
