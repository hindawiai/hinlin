<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2014 ARM Limited
 */

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/sched_घड़ी.h>

#घोषणा SYS_24MHZ 0x05c

अटल व्योम __iomem *versatile_sys_24mhz;

अटल u64 notrace versatile_sys_24mhz_पढ़ो(व्योम)
अणु
	वापस पढ़ोl(versatile_sys_24mhz);
पूर्ण

अटल पूर्णांक __init versatile_sched_घड़ी_init(काष्ठा device_node *node)
अणु
	व्योम __iomem *base = of_iomap(node, 0);

	of_node_clear_flag(node, OF_POPULATED);

	अगर (!base)
		वापस -ENXIO;

	versatile_sys_24mhz = base + SYS_24MHZ;

	sched_घड़ी_रेजिस्टर(versatile_sys_24mhz_पढ़ो, 32, 24000000);

	वापस 0;
पूर्ण
TIMER_OF_DECLARE(vexpress, "arm,vexpress-sysreg",
		       versatile_sched_घड़ी_init);
TIMER_OF_DECLARE(versatile, "arm,versatile-sysreg",
		       versatile_sched_घड़ी_init);
