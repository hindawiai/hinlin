<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Actions Semi Leopard
 *
 * This file is based on arm realview smp platक्रमm.
 *
 * Copyright 2012 Actions Semi Inc.
 * Author: Actions Semi, Inc.
 *
 * Copyright (c) 2017 Andreas Fथअrber
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/smp.h>
#समावेश <linux/soc/actions/owl-sps.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>

#घोषणा OWL_CPU1_ADDR	0x50
#घोषणा OWL_CPU1_FLAG	0x5c

#घोषणा OWL_CPUx_FLAG_BOOT	0x55aa

#घोषणा OWL_SPS_PG_CTL_PWR_CPU2	BIT(5)
#घोषणा OWL_SPS_PG_CTL_PWR_CPU3	BIT(6)
#घोषणा OWL_SPS_PG_CTL_ACK_CPU2	BIT(21)
#घोषणा OWL_SPS_PG_CTL_ACK_CPU3	BIT(22)

अटल व्योम __iomem *scu_base_addr;
अटल व्योम __iomem *sps_base_addr;
अटल व्योम __iomem *समयr_base_addr;
अटल पूर्णांक ncores;

अटल पूर्णांक s500_wakeup_secondary(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret;

	अगर (cpu > 3)
		वापस -EINVAL;

	/* The generic PM करोमुख्य driver is not available this early. */
	चयन (cpu) अणु
	हाल 2:
		ret = owl_sps_set_pg(sps_base_addr,
		                     OWL_SPS_PG_CTL_PWR_CPU2,
				     OWL_SPS_PG_CTL_ACK_CPU2, true);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल 3:
		ret = owl_sps_set_pg(sps_base_addr,
		                     OWL_SPS_PG_CTL_PWR_CPU3,
				     OWL_SPS_PG_CTL_ACK_CPU3, true);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण

	/* रुको क्रम CPUx to run to WFE inकाष्ठाion */
	udelay(200);

	ग_लिखोl(__pa_symbol(secondary_startup),
	       समयr_base_addr + OWL_CPU1_ADDR + (cpu - 1) * 4);
	ग_लिखोl(OWL_CPUx_FLAG_BOOT,
	       समयr_base_addr + OWL_CPU1_FLAG + (cpu - 1) * 4);

	dsb_sev();
	mb();

	वापस 0;
पूर्ण

अटल पूर्णांक s500_smp_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret;

	ret = s500_wakeup_secondary(cpu);
	अगर (ret)
		वापस ret;

	udelay(10);

	smp_send_reschedule(cpu);

	ग_लिखोl(0, समयr_base_addr + OWL_CPU1_ADDR + (cpu - 1) * 4);
	ग_लिखोl(0, समयr_base_addr + OWL_CPU1_FLAG + (cpu - 1) * 4);

	वापस 0;
पूर्ण

अटल व्योम __init s500_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *node;

	node = of_find_compatible_node(शून्य, शून्य, "actions,s500-timer");
	अगर (!node) अणु
		pr_err("%s: missing timer\n", __func__);
		वापस;
	पूर्ण

	समयr_base_addr = of_iomap(node, 0);
	अगर (!समयr_base_addr) अणु
		pr_err("%s: could not map timer registers\n", __func__);
		वापस;
	पूर्ण

	node = of_find_compatible_node(शून्य, शून्य, "actions,s500-sps");
	अगर (!node) अणु
		pr_err("%s: missing sps\n", __func__);
		वापस;
	पूर्ण

	sps_base_addr = of_iomap(node, 0);
	अगर (!sps_base_addr) अणु
		pr_err("%s: could not map sps registers\n", __func__);
		वापस;
	पूर्ण

	अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A9) अणु
		node = of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9-scu");
		अगर (!node) अणु
			pr_err("%s: missing scu\n", __func__);
			वापस;
		पूर्ण

		scu_base_addr = of_iomap(node, 0);
		अगर (!scu_base_addr) अणु
			pr_err("%s: could not map scu registers\n", __func__);
			वापस;
		पूर्ण

		/*
		 * While the number of cpus is gathered from dt, also get the
		 * number of cores from the scu to verअगरy this value when
		 * booting the cores.
		 */
		ncores = scu_get_core_count(scu_base_addr);
		pr_debug("%s: ncores %d\n", __func__, ncores);

		scu_enable(scu_base_addr);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा smp_operations s500_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus = s500_smp_prepare_cpus,
	.smp_boot_secondary = s500_smp_boot_secondary,
पूर्ण;
CPU_METHOD_OF_DECLARE(s500_smp, "actions,s500-smp", &s500_smp_ops);
