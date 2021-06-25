<शैली गुरु>
/*
 * drivers/cpufreq/spear-cpufreq.c
 *
 * CPU Frequency Scaling क्रम SPEAr platक्रमm
 *
 * Copyright (C) 2012 ST Microelectronics
 * Deepak Sikri <deepak.sikri@st.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

/* SPEAr CPUFreq driver data काष्ठाure */
अटल काष्ठा अणु
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक transition_latency;
	काष्ठा cpufreq_frequency_table *freq_tbl;
	u32 cnt;
पूर्ण spear_cpufreq;

अटल काष्ठा clk *spear1340_cpu_get_possible_parent(अचिन्हित दीर्घ newfreq)
अणु
	काष्ठा clk *sys_pclk;
	पूर्णांक pclk;
	/*
	 * In SPEAr1340, cpu clk's parent sys clk can take input from
	 * following sources
	 */
	स्थिर अक्षर *sys_clk_src[] = अणु
		"sys_syn_clk",
		"pll1_clk",
		"pll2_clk",
		"pll3_clk",
	पूर्ण;

	/*
	 * As sys clk can have multiple source with their own range
	 * limitation so we choose possible sources accordingly
	 */
	अगर (newfreq <= 300000000)
		pclk = 0; /* src is sys_syn_clk */
	अन्यथा अगर (newfreq > 300000000 && newfreq <= 500000000)
		pclk = 3; /* src is pll3_clk */
	अन्यथा अगर (newfreq == 600000000)
		pclk = 1; /* src is pll1_clk */
	अन्यथा
		वापस ERR_PTR(-EINVAL);

	/* Get parent to sys घड़ी */
	sys_pclk = clk_get(शून्य, sys_clk_src[pclk]);
	अगर (IS_ERR(sys_pclk))
		pr_err("Failed to get %s clock\n", sys_clk_src[pclk]);

	वापस sys_pclk;
पूर्ण

/*
 * In SPEAr1340, we cannot use newfreq directly because we need to actually
 * access a source घड़ी (clk) which might not be ancestor of cpu at present.
 * Hence in SPEAr1340 we would operate on source घड़ी directly beक्रमe चयनing
 * cpu घड़ी to it.
 */
अटल पूर्णांक spear1340_set_cpu_rate(काष्ठा clk *sys_pclk, अचिन्हित दीर्घ newfreq)
अणु
	काष्ठा clk *sys_clk;
	पूर्णांक ret = 0;

	sys_clk = clk_get_parent(spear_cpufreq.clk);
	अगर (IS_ERR(sys_clk)) अणु
		pr_err("failed to get cpu's parent (sys) clock\n");
		वापस PTR_ERR(sys_clk);
	पूर्ण

	/* Set the rate of the source घड़ी beक्रमe changing the parent */
	ret = clk_set_rate(sys_pclk, newfreq);
	अगर (ret) अणु
		pr_err("Failed to set sys clk rate to %lu\n", newfreq);
		वापस ret;
	पूर्ण

	ret = clk_set_parent(sys_clk, sys_pclk);
	अगर (ret) अणु
		pr_err("Failed to set sys clk parent\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spear_cpufreq_target(काष्ठा cpufreq_policy *policy,
		अचिन्हित पूर्णांक index)
अणु
	दीर्घ newfreq;
	काष्ठा clk *srcclk;
	पूर्णांक ret, mult = 1;

	newfreq = spear_cpufreq.freq_tbl[index].frequency * 1000;

	अगर (of_machine_is_compatible("st,spear1340")) अणु
		/*
		 * SPEAr1340 is special in the sense that due to the possibility
		 * of multiple घड़ी sources क्रम cpu clk's parent we can have
		 * dअगरferent घड़ी source क्रम dअगरferent frequency of cpu clk.
		 * Hence we need to choose one from amongst these possible घड़ी
		 * sources.
		 */
		srcclk = spear1340_cpu_get_possible_parent(newfreq);
		अगर (IS_ERR(srcclk)) अणु
			pr_err("Failed to get src clk\n");
			वापस PTR_ERR(srcclk);
		पूर्ण

		/* SPEAr1340: src clk is always 2 * पूर्णांकended cpu clk */
		mult = 2;
	पूर्ण अन्यथा अणु
		/*
		 * src घड़ी to be altered is ancestor of cpu घड़ी. Hence we
		 * can directly work on cpu clk
		 */
		srcclk = spear_cpufreq.clk;
	पूर्ण

	newfreq = clk_round_rate(srcclk, newfreq * mult);
	अगर (newfreq <= 0) अणु
		pr_err("clk_round_rate failed for cpu src clock\n");
		वापस newfreq;
	पूर्ण

	अगर (mult == 2)
		ret = spear1340_set_cpu_rate(srcclk, newfreq);
	अन्यथा
		ret = clk_set_rate(spear_cpufreq.clk, newfreq);

	अगर (ret)
		pr_err("CPU Freq: cpu clk_set_rate failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक spear_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	policy->clk = spear_cpufreq.clk;
	cpufreq_generic_init(policy, spear_cpufreq.freq_tbl,
			spear_cpufreq.transition_latency);
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver spear_cpufreq_driver = अणु
	.name		= "cpufreq-spear",
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= spear_cpufreq_target,
	.get		= cpufreq_generic_get,
	.init		= spear_cpufreq_init,
	.attr		= cpufreq_generic_attr,
पूर्ण;

अटल पूर्णांक spear_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा property *prop;
	काष्ठा cpufreq_frequency_table *freq_tbl;
	स्थिर __be32 *val;
	पूर्णांक cnt, i, ret;

	np = of_cpu_device_node_get(0);
	अगर (!np) अणु
		pr_err("No cpu node found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "clock-latency",
				&spear_cpufreq.transition_latency))
		spear_cpufreq.transition_latency = CPUFREQ_ETERNAL;

	prop = of_find_property(np, "cpufreq_tbl", शून्य);
	अगर (!prop || !prop->value) अणु
		pr_err("Invalid cpufreq_tbl\n");
		ret = -ENODEV;
		जाओ out_put_node;
	पूर्ण

	cnt = prop->length / माप(u32);
	val = prop->value;

	freq_tbl = kसुस्मृति(cnt + 1, माप(*freq_tbl), GFP_KERNEL);
	अगर (!freq_tbl) अणु
		ret = -ENOMEM;
		जाओ out_put_node;
	पूर्ण

	क्रम (i = 0; i < cnt; i++)
		freq_tbl[i].frequency = be32_to_cpup(val++);

	freq_tbl[i].frequency = CPUFREQ_TABLE_END;

	spear_cpufreq.freq_tbl = freq_tbl;

	of_node_put(np);

	spear_cpufreq.clk = clk_get(शून्य, "cpu_clk");
	अगर (IS_ERR(spear_cpufreq.clk)) अणु
		pr_err("Unable to get CPU clock\n");
		ret = PTR_ERR(spear_cpufreq.clk);
		जाओ out_put_mem;
	पूर्ण

	ret = cpufreq_रेजिस्टर_driver(&spear_cpufreq_driver);
	अगर (!ret)
		वापस 0;

	pr_err("failed register driver: %d\n", ret);
	clk_put(spear_cpufreq.clk);

out_put_mem:
	kमुक्त(freq_tbl);
	वापस ret;

out_put_node:
	of_node_put(np);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver spear_cpufreq_platdrv = अणु
	.driver = अणु
		.name	= "spear-cpufreq",
	पूर्ण,
	.probe		= spear_cpufreq_probe,
पूर्ण;
module_platक्रमm_driver(spear_cpufreq_platdrv);

MODULE_AUTHOR("Deepak Sikri <deepak.sikri@st.com>");
MODULE_DESCRIPTION("SPEAr CPUFreq driver");
MODULE_LICENSE("GPL");
