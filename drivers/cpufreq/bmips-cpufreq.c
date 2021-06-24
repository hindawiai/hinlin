<शैली गुरु>
/*
 * CPU frequency scaling क्रम Broadcom BMIPS SoCs
 *
 * Copyright (c) 2017 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/cpufreq.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

/* क्रम mips_hpt_frequency */
#समावेश <यंत्र/समय.स>

#घोषणा BMIPS_CPUFREQ_PREFIX	"bmips"
#घोषणा BMIPS_CPUFREQ_NAME	BMIPS_CPUFREQ_PREFIX "-cpufreq"

#घोषणा TRANSITION_LATENCY	(25 * 1000)	/* 25 us */

#घोषणा BMIPS5_CLK_DIV_SET_SHIFT	0x7
#घोषणा BMIPS5_CLK_DIV_SHIFT		0x4
#घोषणा BMIPS5_CLK_DIV_MASK		0xf

क्रमागत bmips_type अणु
	BMIPS5000,
	BMIPS5200,
पूर्ण;

काष्ठा cpufreq_compat अणु
	स्थिर अक्षर *compatible;
	अचिन्हित पूर्णांक bmips_type;
	अचिन्हित पूर्णांक clk_mult;
	अचिन्हित पूर्णांक max_freqs;
पूर्ण;

#घोषणा BMIPS(c, t, m, f) अणु \
	.compatible = c, \
	.bmips_type = (t), \
	.clk_mult = (m), \
	.max_freqs = (f), \
पूर्ण

अटल काष्ठा cpufreq_compat bmips_cpufreq_compat[] = अणु
	BMIPS("brcm,bmips5000", BMIPS5000, 8, 4),
	BMIPS("brcm,bmips5200", BMIPS5200, 8, 4),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा cpufreq_compat *priv;

अटल पूर्णांक htp_freq_to_cpu_freq(अचिन्हित पूर्णांक clk_mult)
अणु
	वापस mips_hpt_frequency * clk_mult / 1000;
पूर्ण

अटल काष्ठा cpufreq_frequency_table *
bmips_cpufreq_get_freq_table(स्थिर काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_frequency_table *table;
	अचिन्हित दीर्घ cpu_freq;
	पूर्णांक i;

	cpu_freq = htp_freq_to_cpu_freq(priv->clk_mult);

	table = kदो_स्मृति_array(priv->max_freqs + 1, माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < priv->max_freqs; i++) अणु
		table[i].frequency = cpu_freq / (1 << i);
		table[i].driver_data = i;
	पूर्ण
	table[i].frequency = CPUFREQ_TABLE_END;

	वापस table;
पूर्ण

अटल अचिन्हित पूर्णांक bmips_cpufreq_get(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक भाग;
	uपूर्णांक32_t mode;

	चयन (priv->bmips_type) अणु
	हाल BMIPS5200:
	हाल BMIPS5000:
		mode = पढ़ो_c0_brcm_mode();
		भाग = ((mode >> BMIPS5_CLK_DIV_SHIFT) & BMIPS5_CLK_DIV_MASK);
		अवरोध;
	शेष:
		भाग = 0;
	पूर्ण

	वापस htp_freq_to_cpu_freq(priv->clk_mult) / (1 << भाग);
पूर्ण

अटल पूर्णांक bmips_cpufreq_target_index(काष्ठा cpufreq_policy *policy,
				      अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक भाग = policy->freq_table[index].driver_data;

	चयन (priv->bmips_type) अणु
	हाल BMIPS5200:
	हाल BMIPS5000:
		change_c0_brcm_mode(BMIPS5_CLK_DIV_MASK << BMIPS5_CLK_DIV_SHIFT,
				    (1 << BMIPS5_CLK_DIV_SET_SHIFT) |
				    (भाग << BMIPS5_CLK_DIV_SHIFT));
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmips_cpufreq_निकास(काष्ठा cpufreq_policy *policy)
अणु
	kमुक्त(policy->freq_table);

	वापस 0;
पूर्ण

अटल पूर्णांक bmips_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_frequency_table *freq_table;

	freq_table = bmips_cpufreq_get_freq_table(policy);
	अगर (IS_ERR(freq_table)) अणु
		pr_err("%s: couldn't determine frequency table (%ld).\n",
			BMIPS_CPUFREQ_NAME, PTR_ERR(freq_table));
		वापस PTR_ERR(freq_table);
	पूर्ण

	cpufreq_generic_init(policy, freq_table, TRANSITION_LATENCY);
	pr_info("%s: registered\n", BMIPS_CPUFREQ_NAME);

	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver bmips_cpufreq_driver = अणु
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= bmips_cpufreq_target_index,
	.get		= bmips_cpufreq_get,
	.init		= bmips_cpufreq_init,
	.निकास		= bmips_cpufreq_निकास,
	.attr		= cpufreq_generic_attr,
	.name		= BMIPS_CPUFREQ_PREFIX,
पूर्ण;

अटल पूर्णांक __init bmips_cpufreq_probe(व्योम)
अणु
	काष्ठा cpufreq_compat *cc;
	काष्ठा device_node *np;

	क्रम (cc = bmips_cpufreq_compat; cc->compatible; cc++) अणु
		np = of_find_compatible_node(शून्य, "cpu", cc->compatible);
		अगर (np) अणु
			of_node_put(np);
			priv = cc;
			अवरोध;
		पूर्ण
	पूर्ण

	/* We hit the guard element of the array. No compatible CPU found. */
	अगर (!cc->compatible)
		वापस -ENODEV;

	वापस cpufreq_रेजिस्टर_driver(&bmips_cpufreq_driver);
पूर्ण
device_initcall(bmips_cpufreq_probe);

MODULE_AUTHOR("Markus Mayer <mmayer@broadcom.com>");
MODULE_DESCRIPTION("CPUfreq driver for Broadcom BMIPS SoCs");
MODULE_LICENSE("GPL");
