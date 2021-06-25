<शैली गुरु>
/*
 * Copyright (C) 2014 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) "mvebu-cpureset: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>
#समावेश <linux/resource.h>

#समावेश "common.h"

अटल व्योम __iomem *cpu_reset_base;
अटल माप_प्रकार cpu_reset_size;

#घोषणा CPU_RESET_OFFSET(cpu) (cpu * 0x8)
#घोषणा CPU_RESET_ASSERT      BIT(0)

पूर्णांक mvebu_cpu_reset_deनिश्चित(पूर्णांक cpu)
अणु
	u32 reg;

	अगर (!cpu_reset_base)
		वापस -ENODEV;

	अगर (CPU_RESET_OFFSET(cpu) >= cpu_reset_size)
		वापस -EINVAL;

	reg = पढ़ोl(cpu_reset_base + CPU_RESET_OFFSET(cpu));
	reg &= ~CPU_RESET_ASSERT;
	ग_लिखोl(reg, cpu_reset_base + CPU_RESET_OFFSET(cpu));

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_cpu_reset_map(काष्ठा device_node *np, पूर्णांक res_idx)
अणु
	काष्ठा resource res;

	अगर (of_address_to_resource(np, res_idx, &res)) अणु
		pr_err("unable to get resource\n");
		वापस -ENOENT;
	पूर्ण

	अगर (!request_mem_region(res.start, resource_size(&res),
				np->full_name)) अणु
		pr_err("unable to request region\n");
		वापस -EBUSY;
	पूर्ण

	cpu_reset_base = ioremap(res.start, resource_size(&res));
	अगर (!cpu_reset_base) अणु
		pr_err("unable to map registers\n");
		release_mem_region(res.start, resource_size(&res));
		वापस -ENOMEM;
	पूर्ण

	cpu_reset_size = resource_size(&res);

	वापस 0;
पूर्ण

अटल पूर्णांक __init mvebu_cpu_reset_init(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक res_idx;
	पूर्णांक ret;

	np = of_find_compatible_node(शून्य, शून्य,
				     "marvell,armada-370-cpu-reset");
	अगर (np) अणु
		res_idx = 0;
	पूर्ण अन्यथा अणु
		/*
		 * This code is kept क्रम backward compatibility with
		 * old Device Trees.
		 */
		np = of_find_compatible_node(शून्य, शून्य,
					     "marvell,armada-370-xp-pmsu");
		अगर (np) अणु
			pr_warn(FW_WARN "deprecated pmsu binding\n");
			res_idx = 1;
		पूर्ण
	पूर्ण

	/* No reset node found */
	अगर (!np)
		वापस -ENODEV;

	ret = mvebu_cpu_reset_map(np, res_idx);
	of_node_put(np);

	वापस ret;
पूर्ण

early_initcall(mvebu_cpu_reset_init);
