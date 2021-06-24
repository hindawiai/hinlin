<शैली गुरु>
/*
 * CPUFreq support क्रम Armada 370/XP platक्रमms.
 *
 * Copyright (C) 2012-2016 Marvell
 *
 * Yehuda Yitschak <yehuday@marvell.com>
 * Gregory Clement <gregory.clement@मुक्त-electrons.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) "mvebu-pmsu: " fmt

#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/resource.h>

अटल पूर्णांक __init armada_xp_pmsu_cpufreq_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource res;
	पूर्णांक ret, cpu;

	अगर (!of_machine_is_compatible("marvell,armadaxp"))
		वापस 0;

	/*
	 * In order to have proper cpufreq handling, we need to ensure
	 * that the Device Tree description of the CPU घड़ी includes
	 * the definition of the PMU DFS रेजिस्टरs. If not, we करो not
	 * रेजिस्टर the घड़ी notअगरier and the cpufreq driver. This
	 * piece of code is only क्रम compatibility with old Device
	 * Trees.
	 */
	np = of_find_compatible_node(शून्य, शून्य, "marvell,armada-xp-cpu-clock");
	अगर (!np)
		वापस 0;

	ret = of_address_to_resource(np, 1, &res);
	अगर (ret) अणु
		pr_warn(FW_WARN "not enabling cpufreq, deprecated armada-xp-cpu-clock binding\n");
		of_node_put(np);
		वापस 0;
	पूर्ण

	of_node_put(np);

	/*
	 * For each CPU, this loop रेजिस्टरs the operating poपूर्णांकs
	 * supported (which are the nominal CPU frequency and half of
	 * it), and रेजिस्टरs the घड़ी notअगरier that will take care
	 * of करोing the PMSU part of a frequency transition.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा device *cpu_dev;
		काष्ठा clk *clk;
		पूर्णांक ret;

		cpu_dev = get_cpu_device(cpu);
		अगर (!cpu_dev) अणु
			pr_err("Cannot get CPU %d\n", cpu);
			जारी;
		पूर्ण

		clk = clk_get(cpu_dev, शून्य);
		अगर (IS_ERR(clk)) अणु
			pr_err("Cannot get clock for CPU %d\n", cpu);
			वापस PTR_ERR(clk);
		पूर्ण

		ret = dev_pm_opp_add(cpu_dev, clk_get_rate(clk), 0);
		अगर (ret) अणु
			clk_put(clk);
			वापस ret;
		पूर्ण

		ret = dev_pm_opp_add(cpu_dev, clk_get_rate(clk) / 2, 0);
		अगर (ret) अणु
			dev_pm_opp_हटाओ(cpu_dev, clk_get_rate(clk));
			clk_put(clk);
			dev_err(cpu_dev, "Failed to register OPPs\n");
			वापस ret;
		पूर्ण

		ret = dev_pm_opp_set_sharing_cpus(cpu_dev,
						  cpumask_of(cpu_dev->id));
		अगर (ret)
			dev_err(cpu_dev, "%s: failed to mark OPPs as shared: %d\n",
				__func__, ret);
		clk_put(clk);
	पूर्ण

	platक्रमm_device_रेजिस्टर_simple("cpufreq-dt", -1, शून्य, 0);
	वापस 0;
पूर्ण
device_initcall(armada_xp_pmsu_cpufreq_init);
