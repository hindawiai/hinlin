<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012-2013 Freescale Semiconductor, Inc.
 */

#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>

#समावेश <linux/irqchip.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>

#समावेश "common.h"
#समावेश "hardware.h"

#घोषणा MSCM_CPxCOUNT		0x00c
#घोषणा MSCM_CPxCFG1		0x014

अटल व्योम __init vf610_detect_cpu(व्योम)
अणु
	काष्ठा device_node *np;
	u32 cpxcount, cpxcfg1;
	अचिन्हित पूर्णांक cpu_type;
	व्योम __iomem *mscm;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,vf610-mscm-cpucfg");
	अगर (WARN_ON(!np))
		वापस;

	mscm = of_iomap(np, 0);
	of_node_put(np);

	अगर (WARN_ON(!mscm))
		वापस;

	cpxcount = पढ़ोl_relaxed(mscm + MSCM_CPxCOUNT);
	cpxcfg1  = पढ़ोl_relaxed(mscm + MSCM_CPxCFG1);

	iounmap(mscm);

	cpu_type = cpxcount ? MXC_CPU_VF600 : MXC_CPU_VF500;

	अगर (cpxcfg1)
		cpu_type |= MXC_CPU_VFx10;

	mxc_set_cpu_type(cpu_type);
पूर्ण

अटल व्योम __init vf610_init_machine(व्योम)
अणु
	vf610_detect_cpu();

	of_platक्रमm_शेष_populate(शून्य, शून्य, शून्य);
पूर्ण

अटल स्थिर अक्षर * स्थिर vf610_dt_compat[] __initस्थिर = अणु
	"fsl,vf500",
	"fsl,vf510",
	"fsl,vf600",
	"fsl,vf610",
	"fsl,vf610m4",
	शून्य,
पूर्ण;

DT_MACHINE_START(VYBRID_VF610, "Freescale Vybrid VF5xx/VF6xx (Device Tree)")
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.init_machine   = vf610_init_machine,
	.dt_compat	= vf610_dt_compat,
MACHINE_END
