<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 */

#समावेश <linux/of_clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/sbi.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/समयx.h>

अचिन्हित दीर्घ riscv_समयbase __ro_after_init;
EXPORT_SYMBOL_GPL(riscv_समयbase);

व्योम __init समय_init(व्योम)
अणु
	काष्ठा device_node *cpu;
	u32 prop;

	cpu = of_find_node_by_path("/cpus");
	अगर (!cpu || of_property_पढ़ो_u32(cpu, "timebase-frequency", &prop))
		panic(KERN_WARNING "RISC-V system with no 'timebase-frequency' in DTS\n");
	of_node_put(cpu);
	riscv_समयbase = prop;

	lpj_fine = riscv_समयbase / HZ;

	of_clk_init(शून्य);
	समयr_probe();
पूर्ण

व्योम घड़ीsource_arch_init(काष्ठा घड़ीsource *cs)
अणु
#अगर_घोषित CONFIG_GENERIC_GETTIMखातापूर्णDAY
	cs->vdso_घड़ी_mode = VDSO_CLOCKMODE_ARCHTIMER;
#अन्यथा
	cs->vdso_घड़ी_mode = VDSO_CLOCKMODE_NONE;
#पूर्ण_अगर
पूर्ण
