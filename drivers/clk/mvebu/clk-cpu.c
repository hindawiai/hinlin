<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell MVEBU CPU घड़ी handling.
 *
 * Copyright (C) 2012 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>
#समावेश <linux/mvebu-pmsu.h>
#समावेश <यंत्र/smp_plat.h>

#घोषणा SYS_CTRL_CLK_DIVIDER_CTRL_OFFSET               0x0
#घोषणा   SYS_CTRL_CLK_DIVIDER_CTRL_RESET_ALL          0xff
#घोषणा   SYS_CTRL_CLK_DIVIDER_CTRL_RESET_SHIFT        8
#घोषणा SYS_CTRL_CLK_DIVIDER_CTRL2_OFFSET              0x8
#घोषणा   SYS_CTRL_CLK_DIVIDER_CTRL2_NBCLK_RATIO_SHIFT 16
#घोषणा SYS_CTRL_CLK_DIVIDER_VALUE_OFFSET              0xC
#घोषणा SYS_CTRL_CLK_DIVIDER_MASK                      0x3F

#घोषणा PMU_DFS_RATIO_SHIFT 16
#घोषणा PMU_DFS_RATIO_MASK  0x3F

#घोषणा MAX_CPU	    4
काष्ठा cpu_clk अणु
	काष्ठा clk_hw hw;
	पूर्णांक cpu;
	स्थिर अक्षर *clk_name;
	स्थिर अक्षर *parent_name;
	व्योम __iomem *reg_base;
	व्योम __iomem *pmu_dfs;
पूर्ण;

अटल काष्ठा clk **clks;

अटल काष्ठा clk_onecell_data clk_data;

#घोषणा to_cpu_clk(p) container_of(p, काष्ठा cpu_clk, hw)

अटल अचिन्हित दीर्घ clk_cpu_recalc_rate(काष्ठा clk_hw *hwclk,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा cpu_clk *cpuclk = to_cpu_clk(hwclk);
	u32 reg, भाग;

	reg = पढ़ोl(cpuclk->reg_base + SYS_CTRL_CLK_DIVIDER_VALUE_OFFSET);
	भाग = (reg >> (cpuclk->cpu * 8)) & SYS_CTRL_CLK_DIVIDER_MASK;
	वापस parent_rate / भाग;
पूर्ण

अटल दीर्घ clk_cpu_round_rate(काष्ठा clk_hw *hwclk, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	/* Valid ratio are 1:1, 1:2 and 1:3 */
	u32 भाग;

	भाग = *parent_rate / rate;
	अगर (भाग == 0)
		भाग = 1;
	अन्यथा अगर (भाग > 3)
		भाग = 3;

	वापस *parent_rate / भाग;
पूर्ण

अटल पूर्णांक clk_cpu_off_set_rate(काष्ठा clk_hw *hwclk, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)

अणु
	काष्ठा cpu_clk *cpuclk = to_cpu_clk(hwclk);
	u32 reg, भाग;
	u32 reload_mask;

	भाग = parent_rate / rate;
	reg = (पढ़ोl(cpuclk->reg_base + SYS_CTRL_CLK_DIVIDER_VALUE_OFFSET)
		& (~(SYS_CTRL_CLK_DIVIDER_MASK << (cpuclk->cpu * 8))))
		| (भाग << (cpuclk->cpu * 8));
	ग_लिखोl(reg, cpuclk->reg_base + SYS_CTRL_CLK_DIVIDER_VALUE_OFFSET);
	/* Set घड़ी भागider reload smooth bit mask */
	reload_mask = 1 << (20 + cpuclk->cpu);

	reg = पढ़ोl(cpuclk->reg_base + SYS_CTRL_CLK_DIVIDER_CTRL_OFFSET)
	    | reload_mask;
	ग_लिखोl(reg, cpuclk->reg_base + SYS_CTRL_CLK_DIVIDER_CTRL_OFFSET);

	/* Now trigger the घड़ी update */
	reg = पढ़ोl(cpuclk->reg_base + SYS_CTRL_CLK_DIVIDER_CTRL_OFFSET)
	    | 1 << 24;
	ग_लिखोl(reg, cpuclk->reg_base + SYS_CTRL_CLK_DIVIDER_CTRL_OFFSET);

	/* Wait क्रम घड़ीs to settle करोwn then clear reload request */
	udelay(1000);
	reg &= ~(reload_mask | 1 << 24);
	ग_लिखोl(reg, cpuclk->reg_base + SYS_CTRL_CLK_DIVIDER_CTRL_OFFSET);
	udelay(1000);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_cpu_on_set_rate(काष्ठा clk_hw *hwclk, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	u32 reg;
	अचिन्हित दीर्घ fabric_भाग, target_भाग, cur_rate;
	काष्ठा cpu_clk *cpuclk = to_cpu_clk(hwclk);

	/*
	 * PMU DFS रेजिस्टरs are not mapped, Device Tree करोes not
	 * describes them. We cannot change the frequency dynamically.
	 */
	अगर (!cpuclk->pmu_dfs)
		वापस -ENODEV;

	cur_rate = clk_hw_get_rate(hwclk);

	reg = पढ़ोl(cpuclk->reg_base + SYS_CTRL_CLK_DIVIDER_CTRL2_OFFSET);
	fabric_भाग = (reg >> SYS_CTRL_CLK_DIVIDER_CTRL2_NBCLK_RATIO_SHIFT) &
		SYS_CTRL_CLK_DIVIDER_MASK;

	/* Frequency is going up */
	अगर (rate == 2 * cur_rate)
		target_भाग = fabric_भाग / 2;
	/* Frequency is going करोwn */
	अन्यथा
		target_भाग = fabric_भाग;

	अगर (target_भाग == 0)
		target_भाग = 1;

	reg = पढ़ोl(cpuclk->pmu_dfs);
	reg &= ~(PMU_DFS_RATIO_MASK << PMU_DFS_RATIO_SHIFT);
	reg |= (target_भाग << PMU_DFS_RATIO_SHIFT);
	ग_लिखोl(reg, cpuclk->pmu_dfs);

	reg = पढ़ोl(cpuclk->reg_base + SYS_CTRL_CLK_DIVIDER_CTRL_OFFSET);
	reg |= (SYS_CTRL_CLK_DIVIDER_CTRL_RESET_ALL <<
		SYS_CTRL_CLK_DIVIDER_CTRL_RESET_SHIFT);
	ग_लिखोl(reg, cpuclk->reg_base + SYS_CTRL_CLK_DIVIDER_CTRL_OFFSET);

	वापस mvebu_pmsu_dfs_request(cpuclk->cpu);
पूर्ण

अटल पूर्णांक clk_cpu_set_rate(काष्ठा clk_hw *hwclk, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	अगर (__clk_is_enabled(hwclk->clk))
		वापस clk_cpu_on_set_rate(hwclk, rate, parent_rate);
	अन्यथा
		वापस clk_cpu_off_set_rate(hwclk, rate, parent_rate);
पूर्ण

अटल स्थिर काष्ठा clk_ops cpu_ops = अणु
	.recalc_rate = clk_cpu_recalc_rate,
	.round_rate = clk_cpu_round_rate,
	.set_rate = clk_cpu_set_rate,
पूर्ण;

अटल व्योम __init of_cpu_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा cpu_clk *cpuclk;
	व्योम __iomem *घड़ी_complex_base = of_iomap(node, 0);
	व्योम __iomem *pmu_dfs_base = of_iomap(node, 1);
	पूर्णांक ncpus = 0;
	काष्ठा device_node *dn;

	अगर (घड़ी_complex_base == शून्य) अणु
		pr_err("%s: clock-complex base register not set\n",
			__func__);
		वापस;
	पूर्ण

	अगर (pmu_dfs_base == शून्य)
		pr_warn("%s: pmu-dfs base register not set, dynamic frequency scaling not available\n",
			__func__);

	क्रम_each_of_cpu_node(dn)
		ncpus++;

	cpuclk = kसुस्मृति(ncpus, माप(*cpuclk), GFP_KERNEL);
	अगर (WARN_ON(!cpuclk))
		जाओ cpuclk_out;

	clks = kसुस्मृति(ncpus, माप(*clks), GFP_KERNEL);
	अगर (WARN_ON(!clks))
		जाओ clks_out;

	क्रम_each_of_cpu_node(dn) अणु
		काष्ठा clk_init_data init;
		काष्ठा clk *clk;
		अक्षर *clk_name = kzalloc(5, GFP_KERNEL);
		पूर्णांक cpu, err;

		अगर (WARN_ON(!clk_name))
			जाओ bail_out;

		err = of_property_पढ़ो_u32(dn, "reg", &cpu);
		अगर (WARN_ON(err))
			जाओ bail_out;

		प्र_लिखो(clk_name, "cpu%d", cpu);

		cpuclk[cpu].parent_name = of_clk_get_parent_name(node, 0);
		cpuclk[cpu].clk_name = clk_name;
		cpuclk[cpu].cpu = cpu;
		cpuclk[cpu].reg_base = घड़ी_complex_base;
		अगर (pmu_dfs_base)
			cpuclk[cpu].pmu_dfs = pmu_dfs_base + 4 * cpu;
		cpuclk[cpu].hw.init = &init;

		init.name = cpuclk[cpu].clk_name;
		init.ops = &cpu_ops;
		init.flags = 0;
		init.parent_names = &cpuclk[cpu].parent_name;
		init.num_parents = 1;

		clk = clk_रेजिस्टर(शून्य, &cpuclk[cpu].hw);
		अगर (WARN_ON(IS_ERR(clk)))
			जाओ bail_out;
		clks[cpu] = clk;
	पूर्ण
	clk_data.clk_num = MAX_CPU;
	clk_data.clks = clks;
	of_clk_add_provider(node, of_clk_src_onecell_get, &clk_data);

	वापस;
bail_out:
	kमुक्त(clks);
	जबतक(ncpus--)
		kमुक्त(cpuclk[ncpus].clk_name);
clks_out:
	kमुक्त(cpuclk);
cpuclk_out:
	iounmap(घड़ी_complex_base);
पूर्ण

CLK_OF_DECLARE(armada_xp_cpu_घड़ी, "marvell,armada-xp-cpu-clock",
					 of_cpu_clk_setup);

अटल व्योम __init of_mv98dx3236_cpu_clk_setup(काष्ठा device_node *node)
अणु
	of_clk_add_provider(node, of_clk_src_simple_get, शून्य);
पूर्ण

CLK_OF_DECLARE(mv98dx3236_cpu_घड़ी, "marvell,mv98dx3236-cpu-clock",
					 of_mv98dx3236_cpu_clk_setup);
