<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R-Car MSTP घड़ीs
 *
 * Copyright (C) 2013 Ideas On Board SPRL
 * Copyright (C) 2015 Glider bvba
 *
 * Contact: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/renesas.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/spinlock.h>

/*
 * MSTP घड़ीs. We can't use standard gate घड़ीs as we need to poll on the
 * status रेजिस्टर when enabling the घड़ी.
 */

#घोषणा MSTP_MAX_CLOCKS		32

/**
 * काष्ठा mstp_घड़ी_group - MSTP gating घड़ीs group
 *
 * @data: घड़ी specअगरier translation क्रम घड़ीs in this group
 * @smstpcr: module stop control रेजिस्टर
 * @mstpsr: module stop status रेजिस्टर (optional)
 * @lock: protects ग_लिखोs to SMSTPCR
 * @width_8bit: रेजिस्टरs are 8-bit, not 32-bit
 * @clks: घड़ीs in this group
 */
काष्ठा mstp_घड़ी_group अणु
	काष्ठा clk_onecell_data data;
	व्योम __iomem *smstpcr;
	व्योम __iomem *mstpsr;
	spinlock_t lock;
	bool width_8bit;
	काष्ठा clk *clks[];
पूर्ण;

/**
 * काष्ठा mstp_घड़ी - MSTP gating घड़ी
 * @hw: handle between common and hardware-specअगरic पूर्णांकerfaces
 * @bit_index: control bit index
 * @group: MSTP घड़ीs group
 */
काष्ठा mstp_घड़ी अणु
	काष्ठा clk_hw hw;
	u32 bit_index;
	काष्ठा mstp_घड़ी_group *group;
पूर्ण;

#घोषणा to_mstp_घड़ी(_hw) container_of(_hw, काष्ठा mstp_घड़ी, hw)

अटल अंतरभूत u32 cpg_mstp_पढ़ो(काष्ठा mstp_घड़ी_group *group,
				u32 __iomem *reg)
अणु
	वापस group->width_8bit ? पढ़ोb(reg) : पढ़ोl(reg);
पूर्ण

अटल अंतरभूत व्योम cpg_mstp_ग_लिखो(काष्ठा mstp_घड़ी_group *group, u32 val,
				  u32 __iomem *reg)
अणु
	group->width_8bit ? ग_लिखोb(val, reg) : ग_लिखोl(val, reg);
पूर्ण

अटल पूर्णांक cpg_mstp_घड़ी_endisable(काष्ठा clk_hw *hw, bool enable)
अणु
	काष्ठा mstp_घड़ी *घड़ी = to_mstp_घड़ी(hw);
	काष्ठा mstp_घड़ी_group *group = घड़ी->group;
	u32 biपंचांगask = BIT(घड़ी->bit_index);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	u32 value;

	spin_lock_irqsave(&group->lock, flags);

	value = cpg_mstp_पढ़ो(group, group->smstpcr);
	अगर (enable)
		value &= ~biपंचांगask;
	अन्यथा
		value |= biपंचांगask;
	cpg_mstp_ग_लिखो(group, value, group->smstpcr);

	अगर (!group->mstpsr) अणु
		/* dummy पढ़ो to ensure ग_लिखो has completed */
		cpg_mstp_पढ़ो(group, group->smstpcr);
		barrier_data(group->smstpcr);
	पूर्ण

	spin_unlock_irqrestore(&group->lock, flags);

	अगर (!enable || !group->mstpsr)
		वापस 0;

	क्रम (i = 1000; i > 0; --i) अणु
		अगर (!(cpg_mstp_पढ़ो(group, group->mstpsr) & biपंचांगask))
			अवरोध;
		cpu_relax();
	पूर्ण

	अगर (!i) अणु
		pr_err("%s: failed to enable %p[%d]\n", __func__,
		       group->smstpcr, घड़ी->bit_index);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpg_mstp_घड़ी_enable(काष्ठा clk_hw *hw)
अणु
	वापस cpg_mstp_घड़ी_endisable(hw, true);
पूर्ण

अटल व्योम cpg_mstp_घड़ी_disable(काष्ठा clk_hw *hw)
अणु
	cpg_mstp_घड़ी_endisable(hw, false);
पूर्ण

अटल पूर्णांक cpg_mstp_घड़ी_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा mstp_घड़ी *घड़ी = to_mstp_घड़ी(hw);
	काष्ठा mstp_घड़ी_group *group = घड़ी->group;
	u32 value;

	अगर (group->mstpsr)
		value = cpg_mstp_पढ़ो(group, group->mstpsr);
	अन्यथा
		value = cpg_mstp_पढ़ो(group, group->smstpcr);

	वापस !(value & BIT(घड़ी->bit_index));
पूर्ण

अटल स्थिर काष्ठा clk_ops cpg_mstp_घड़ी_ops = अणु
	.enable = cpg_mstp_घड़ी_enable,
	.disable = cpg_mstp_घड़ी_disable,
	.is_enabled = cpg_mstp_घड़ी_is_enabled,
पूर्ण;

अटल काष्ठा clk * __init cpg_mstp_घड़ी_रेजिस्टर(स्थिर अक्षर *name,
	स्थिर अक्षर *parent_name, अचिन्हित पूर्णांक index,
	काष्ठा mstp_घड़ी_group *group)
अणु
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा mstp_घड़ी *घड़ी;
	काष्ठा clk *clk;

	घड़ी = kzalloc(माप(*घड़ी), GFP_KERNEL);
	अगर (!घड़ी)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &cpg_mstp_घड़ी_ops;
	init.flags = CLK_SET_RATE_PARENT;
	/* INTC-SYS is the module घड़ी of the GIC, and must not be disabled */
	अगर (!म_भेद(name, "intc-sys")) अणु
		pr_debug("MSTP %s setting CLK_IS_CRITICAL\n", name);
		init.flags |= CLK_IS_CRITICAL;
	पूर्ण
	init.parent_names = &parent_name;
	init.num_parents = 1;

	घड़ी->bit_index = index;
	घड़ी->group = group;
	घड़ी->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &घड़ी->hw);

	अगर (IS_ERR(clk))
		kमुक्त(घड़ी);

	वापस clk;
पूर्ण

अटल व्योम __init cpg_mstp_घड़ीs_init(काष्ठा device_node *np)
अणु
	काष्ठा mstp_घड़ी_group *group;
	स्थिर अक्षर *idxname;
	काष्ठा clk **clks;
	अचिन्हित पूर्णांक i;

	group = kzalloc(काष्ठा_size(group, clks, MSTP_MAX_CLOCKS), GFP_KERNEL);
	अगर (!group)
		वापस;

	clks = group->clks;
	spin_lock_init(&group->lock);
	group->data.clks = clks;

	group->smstpcr = of_iomap(np, 0);
	group->mstpsr = of_iomap(np, 1);

	अगर (group->smstpcr == शून्य) अणु
		pr_err("%s: failed to remap SMSTPCR\n", __func__);
		kमुक्त(group);
		वापस;
	पूर्ण

	अगर (of_device_is_compatible(np, "renesas,r7s72100-mstp-clocks"))
		group->width_8bit = true;

	क्रम (i = 0; i < MSTP_MAX_CLOCKS; ++i)
		clks[i] = ERR_PTR(-ENOENT);

	अगर (of_find_property(np, "clock-indices", &i))
		idxname = "clock-indices";
	अन्यथा
		idxname = "renesas,clock-indices";

	क्रम (i = 0; i < MSTP_MAX_CLOCKS; ++i) अणु
		स्थिर अक्षर *parent_name;
		स्थिर अक्षर *name;
		u32 clkidx;
		पूर्णांक ret;

		/* Skip घड़ीs with no name. */
		ret = of_property_पढ़ो_string_index(np, "clock-output-names",
						    i, &name);
		अगर (ret < 0 || म_माप(name) == 0)
			जारी;

		parent_name = of_clk_get_parent_name(np, i);
		ret = of_property_पढ़ो_u32_index(np, idxname, i, &clkidx);
		अगर (parent_name == शून्य || ret < 0)
			अवरोध;

		अगर (clkidx >= MSTP_MAX_CLOCKS) अणु
			pr_err("%s: invalid clock %pOFn %s index %u\n",
			       __func__, np, name, clkidx);
			जारी;
		पूर्ण

		clks[clkidx] = cpg_mstp_घड़ी_रेजिस्टर(name, parent_name,
						       clkidx, group);
		अगर (!IS_ERR(clks[clkidx])) अणु
			group->data.clk_num = max(group->data.clk_num,
						  clkidx + 1);
			/*
			 * Register a clkdev to let board code retrieve the
			 * घड़ी by name and रेजिस्टर aliases क्रम non-DT
			 * devices.
			 *
			 * FIXME: Remove this when all devices that require a
			 * घड़ी will be instantiated from DT.
			 */
			clk_रेजिस्टर_clkdev(clks[clkidx], name, शून्य);
		पूर्ण अन्यथा अणु
			pr_err("%s: failed to register %pOFn %s clock (%ld)\n",
			       __func__, np, name, PTR_ERR(clks[clkidx]));
		पूर्ण
	पूर्ण

	of_clk_add_provider(np, of_clk_src_onecell_get, &group->data);
पूर्ण
CLK_OF_DECLARE(cpg_mstp_clks, "renesas,cpg-mstp-clocks", cpg_mstp_घड़ीs_init);

पूर्णांक cpg_mstp_attach_dev(काष्ठा generic_pm_करोमुख्य *unused, काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा of_phandle_args clkspec;
	काष्ठा clk *clk;
	पूर्णांक i = 0;
	पूर्णांक error;

	जबतक (!of_parse_phandle_with_args(np, "clocks", "#clock-cells", i,
					   &clkspec)) अणु
		अगर (of_device_is_compatible(clkspec.np,
					    "renesas,cpg-mstp-clocks"))
			जाओ found;

		/* BSC on r8a73a4/sh73a0 uses zb_clk instead of an mstp घड़ी */
		अगर (of_node_name_eq(clkspec.np, "zb_clk"))
			जाओ found;

		of_node_put(clkspec.np);
		i++;
	पूर्ण

	वापस 0;

found:
	clk = of_clk_get_from_provider(&clkspec);
	of_node_put(clkspec.np);

	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	error = pm_clk_create(dev);
	अगर (error)
		जाओ fail_put;

	error = pm_clk_add_clk(dev, clk);
	अगर (error)
		जाओ fail_destroy;

	वापस 0;

fail_destroy:
	pm_clk_destroy(dev);
fail_put:
	clk_put(clk);
	वापस error;
पूर्ण

व्योम cpg_mstp_detach_dev(काष्ठा generic_pm_करोमुख्य *unused, काष्ठा device *dev)
अणु
	अगर (!pm_clk_no_घड़ीs(dev))
		pm_clk_destroy(dev);
पूर्ण

व्योम __init cpg_mstp_add_clk_करोमुख्य(काष्ठा device_node *np)
अणु
	काष्ठा generic_pm_करोमुख्य *pd;
	u32 ncells;

	अगर (of_property_पढ़ो_u32(np, "#power-domain-cells", &ncells)) अणु
		pr_warn("%pOF lacks #power-domain-cells\n", np);
		वापस;
	पूर्ण

	pd = kzalloc(माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस;

	pd->name = np->name;
	pd->flags = GENPD_FLAG_PM_CLK | GENPD_FLAG_ALWAYS_ON |
		    GENPD_FLAG_ACTIVE_WAKEUP;
	pd->attach_dev = cpg_mstp_attach_dev;
	pd->detach_dev = cpg_mstp_detach_dev;
	pm_genpd_init(pd, &pm_करोमुख्य_always_on_gov, false);

	of_genpd_add_provider_simple(np, pd);
पूर्ण
