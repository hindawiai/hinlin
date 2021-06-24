<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	kirkwood_freq.c: cpufreq driver क्रम the Marvell kirkwood
 *
 *	Copyright (C) 2013 Andrew Lunn <andrew@lunn.ch>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/proc-fns.h>

#घोषणा CPU_SW_INT_BLK BIT(28)

अटल काष्ठा priv
अणु
	काष्ठा clk *cpu_clk;
	काष्ठा clk *ddr_clk;
	काष्ठा clk *घातersave_clk;
	काष्ठा device *dev;
	व्योम __iomem *base;
पूर्ण priv;

#घोषणा STATE_CPU_FREQ 0x01
#घोषणा STATE_DDR_FREQ 0x02

/*
 * Kirkwood can swap the घड़ी to the CPU between two घड़ीs:
 *
 * - cpu clk
 * - ddr clk
 *
 * The frequencies are set at runसमय beक्रमe रेजिस्टरing this table.
 */
अटल काष्ठा cpufreq_frequency_table kirkwood_freq_table[] = अणु
	अणु0, STATE_CPU_FREQ,	0पूर्ण, /* CPU uses cpuclk */
	अणु0, STATE_DDR_FREQ,	0पूर्ण, /* CPU uses ddrclk */
	अणु0, 0,			CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक kirkwood_cpufreq_get_cpu_frequency(अचिन्हित पूर्णांक cpu)
अणु
	वापस clk_get_rate(priv.घातersave_clk) / 1000;
पूर्ण

अटल पूर्णांक kirkwood_cpufreq_target(काष्ठा cpufreq_policy *policy,
			    अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक state = kirkwood_freq_table[index].driver_data;
	अचिन्हित दीर्घ reg;

	local_irq_disable();

	/* Disable पूर्णांकerrupts to the CPU */
	reg = पढ़ोl_relaxed(priv.base);
	reg |= CPU_SW_INT_BLK;
	ग_लिखोl_relaxed(reg, priv.base);

	चयन (state) अणु
	हाल STATE_CPU_FREQ:
		clk_set_parent(priv.घातersave_clk, priv.cpu_clk);
		अवरोध;
	हाल STATE_DDR_FREQ:
		clk_set_parent(priv.घातersave_clk, priv.ddr_clk);
		अवरोध;
	पूर्ण

	/* Wait-क्रम-Interrupt, जबतक the hardware changes frequency */
	cpu_करो_idle();

	/* Enable पूर्णांकerrupts to the CPU */
	reg = पढ़ोl_relaxed(priv.base);
	reg &= ~CPU_SW_INT_BLK;
	ग_लिखोl_relaxed(reg, priv.base);

	local_irq_enable();

	वापस 0;
पूर्ण

/* Module init and निकास code */
अटल पूर्णांक kirkwood_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	cpufreq_generic_init(policy, kirkwood_freq_table, 5000);
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver kirkwood_cpufreq_driver = अणु
	.flags	= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.get	= kirkwood_cpufreq_get_cpu_frequency,
	.verअगरy	= cpufreq_generic_frequency_table_verअगरy,
	.target_index = kirkwood_cpufreq_target,
	.init	= kirkwood_cpufreq_cpu_init,
	.name	= "kirkwood-cpufreq",
	.attr	= cpufreq_generic_attr,
पूर्ण;

अटल पूर्णांक kirkwood_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np;
	पूर्णांक err;

	priv.dev = &pdev->dev;

	priv.base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv.base))
		वापस PTR_ERR(priv.base);

	np = of_cpu_device_node_get(0);
	अगर (!np) अणु
		dev_err(&pdev->dev, "failed to get cpu device node\n");
		वापस -ENODEV;
	पूर्ण

	priv.cpu_clk = of_clk_get_by_name(np, "cpu_clk");
	अगर (IS_ERR(priv.cpu_clk)) अणु
		dev_err(priv.dev, "Unable to get cpuclk\n");
		err = PTR_ERR(priv.cpu_clk);
		जाओ out_node;
	पूर्ण

	err = clk_prepare_enable(priv.cpu_clk);
	अगर (err) अणु
		dev_err(priv.dev, "Unable to prepare cpuclk\n");
		जाओ out_node;
	पूर्ण

	kirkwood_freq_table[0].frequency = clk_get_rate(priv.cpu_clk) / 1000;

	priv.ddr_clk = of_clk_get_by_name(np, "ddrclk");
	अगर (IS_ERR(priv.ddr_clk)) अणु
		dev_err(priv.dev, "Unable to get ddrclk\n");
		err = PTR_ERR(priv.ddr_clk);
		जाओ out_cpu;
	पूर्ण

	err = clk_prepare_enable(priv.ddr_clk);
	अगर (err) अणु
		dev_err(priv.dev, "Unable to prepare ddrclk\n");
		जाओ out_cpu;
	पूर्ण
	kirkwood_freq_table[1].frequency = clk_get_rate(priv.ddr_clk) / 1000;

	priv.घातersave_clk = of_clk_get_by_name(np, "powersave");
	अगर (IS_ERR(priv.घातersave_clk)) अणु
		dev_err(priv.dev, "Unable to get powersave\n");
		err = PTR_ERR(priv.घातersave_clk);
		जाओ out_ddr;
	पूर्ण
	err = clk_prepare_enable(priv.घातersave_clk);
	अगर (err) अणु
		dev_err(priv.dev, "Unable to prepare powersave clk\n");
		जाओ out_ddr;
	पूर्ण

	err = cpufreq_रेजिस्टर_driver(&kirkwood_cpufreq_driver);
	अगर (err) अणु
		dev_err(priv.dev, "Failed to register cpufreq driver\n");
		जाओ out_घातersave;
	पूर्ण

	of_node_put(np);
	वापस 0;

out_घातersave:
	clk_disable_unprepare(priv.घातersave_clk);
out_ddr:
	clk_disable_unprepare(priv.ddr_clk);
out_cpu:
	clk_disable_unprepare(priv.cpu_clk);
out_node:
	of_node_put(np);

	वापस err;
पूर्ण

अटल पूर्णांक kirkwood_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cpufreq_unरेजिस्टर_driver(&kirkwood_cpufreq_driver);

	clk_disable_unprepare(priv.घातersave_clk);
	clk_disable_unprepare(priv.ddr_clk);
	clk_disable_unprepare(priv.cpu_clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver kirkwood_cpufreq_platक्रमm_driver = अणु
	.probe = kirkwood_cpufreq_probe,
	.हटाओ = kirkwood_cpufreq_हटाओ,
	.driver = अणु
		.name = "kirkwood-cpufreq",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(kirkwood_cpufreq_platक्रमm_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Andrew Lunn <andrew@lunn.ch");
MODULE_DESCRIPTION("cpufreq driver for Marvell's kirkwood CPU");
MODULE_ALIAS("platform:kirkwood-cpufreq");
