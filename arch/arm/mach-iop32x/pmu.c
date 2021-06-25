<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PMU IRQ registration क्रम the iop3xx xscale PMU families.
 * Copyright (C) 2010 Will Deacon, ARM Ltd.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश "irqs.h"

अटल काष्ठा resource pmu_resource = अणु
	.start	= IRQ_IOP32X_CORE_PMU,
	.end	= IRQ_IOP32X_CORE_PMU,
	.flags	= IORESOURCE_IRQ,
पूर्ण;

अटल काष्ठा platक्रमm_device pmu_device = अणु
	.name		= "xscale-pmu",
	.id		= -1,
	.resource	= &pmu_resource,
	.num_resources	= 1,
पूर्ण;

अटल पूर्णांक __init iop3xx_pmu_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&pmu_device);
	वापस 0;
पूर्ण

arch_initcall(iop3xx_pmu_init);
