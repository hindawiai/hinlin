<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/clk/tegra/clk-emc.c
 *
 * Copyright (c) 2014, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author:
 *	Mikko Perttunen <mperttunen@nvidia.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sort.h>
#समावेश <linux/माला.स>

#समावेश <soc/tegra/fuse.h>

#समावेश "clk.h"

#घोषणा CLK_SOURCE_EMC 0x19c

#घोषणा CLK_SOURCE_EMC_EMC_2X_CLK_DIVISOR_SHIFT 0
#घोषणा CLK_SOURCE_EMC_EMC_2X_CLK_DIVISOR_MASK 0xff
#घोषणा CLK_SOURCE_EMC_EMC_2X_CLK_DIVISOR(x) (((x) & CLK_SOURCE_EMC_EMC_2X_CLK_DIVISOR_MASK) << \
					      CLK_SOURCE_EMC_EMC_2X_CLK_DIVISOR_SHIFT)

#घोषणा CLK_SOURCE_EMC_EMC_2X_CLK_SRC_SHIFT 29
#घोषणा CLK_SOURCE_EMC_EMC_2X_CLK_SRC_MASK 0x7
#घोषणा CLK_SOURCE_EMC_EMC_2X_CLK_SRC(x) (((x) & CLK_SOURCE_EMC_EMC_2X_CLK_SRC_MASK) << \
					  CLK_SOURCE_EMC_EMC_2X_CLK_SRC_SHIFT)

अटल स्थिर अक्षर * स्थिर emc_parent_clk_names[] = अणु
	"pll_m", "pll_c", "pll_p", "clk_m", "pll_m_ud",
	"pll_c2", "pll_c3", "pll_c_ud"
पूर्ण;

/*
 * List of घड़ी sources क्रम various parents the EMC घड़ी can have.
 * When we change the timing to a timing with a parent that has the same
 * घड़ी source as the current parent, we must first change to a backup
 * timing that has a dअगरferent घड़ी source.
 */

#घोषणा EMC_SRC_PLL_M 0
#घोषणा EMC_SRC_PLL_C 1
#घोषणा EMC_SRC_PLL_P 2
#घोषणा EMC_SRC_CLK_M 3
#घोषणा EMC_SRC_PLL_C2 4
#घोषणा EMC_SRC_PLL_C3 5

अटल स्थिर अक्षर emc_parent_clk_sources[] = अणु
	EMC_SRC_PLL_M, EMC_SRC_PLL_C, EMC_SRC_PLL_P, EMC_SRC_CLK_M,
	EMC_SRC_PLL_M, EMC_SRC_PLL_C2, EMC_SRC_PLL_C3, EMC_SRC_PLL_C
पूर्ण;

काष्ठा emc_timing अणु
	अचिन्हित दीर्घ rate, parent_rate;
	u8 parent_index;
	काष्ठा clk *parent;
	u32 ram_code;
पूर्ण;

काष्ठा tegra_clk_emc अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *clk_regs;
	काष्ठा clk *prev_parent;
	bool changing_timing;

	काष्ठा device_node *emc_node;
	काष्ठा tegra_emc *emc;

	पूर्णांक num_timings;
	काष्ठा emc_timing *timings;
	spinlock_t *lock;

	tegra124_emc_prepare_timing_change_cb *prepare_timing_change;
	tegra124_emc_complete_timing_change_cb *complete_timing_change;
पूर्ण;

/* Common घड़ी framework callback implementations */

अटल अचिन्हित दीर्घ emc_recalc_rate(काष्ठा clk_hw *hw,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_emc *tegra;
	u32 val, भाग;

	tegra = container_of(hw, काष्ठा tegra_clk_emc, hw);

	/*
	 * CCF wrongly assumes that the parent won't change during set_rate,
	 * so get the parent rate explicitly.
	 */
	parent_rate = clk_hw_get_rate(clk_hw_get_parent(hw));

	val = पढ़ोl(tegra->clk_regs + CLK_SOURCE_EMC);
	भाग = val & CLK_SOURCE_EMC_EMC_2X_CLK_DIVISOR_MASK;

	वापस parent_rate / (भाग + 2) * 2;
पूर्ण

/*
 * Rounds up unless no higher rate exists, in which हाल करोwn. This way is
 * safer since things have EMC rate न्यूनमानs. Also करोn't touch parent_rate
 * since we करोn't want the CCF to play with our parent घड़ीs.
 */
अटल पूर्णांक emc_determine_rate(काष्ठा clk_hw *hw, काष्ठा clk_rate_request *req)
अणु
	काष्ठा tegra_clk_emc *tegra;
	u8 ram_code = tegra_पढ़ो_ram_code();
	काष्ठा emc_timing *timing = शून्य;
	पूर्णांक i, k, t;

	tegra = container_of(hw, काष्ठा tegra_clk_emc, hw);

	क्रम (k = 0; k < tegra->num_timings; k++) अणु
		अगर (tegra->timings[k].ram_code == ram_code)
			अवरोध;
	पूर्ण

	क्रम (t = k; t < tegra->num_timings; t++) अणु
		अगर (tegra->timings[t].ram_code != ram_code)
			अवरोध;
	पूर्ण

	क्रम (i = k; i < t; i++) अणु
		timing = tegra->timings + i;

		अगर (timing->rate < req->rate && i != t - 1)
			जारी;

		अगर (timing->rate > req->max_rate) अणु
			i = max(i, k + 1);
			req->rate = tegra->timings[i - 1].rate;
			वापस 0;
		पूर्ण

		अगर (timing->rate < req->min_rate)
			जारी;

		req->rate = timing->rate;
		वापस 0;
	पूर्ण

	अगर (timing) अणु
		req->rate = timing->rate;
		वापस 0;
	पूर्ण

	req->rate = clk_hw_get_rate(hw);
	वापस 0;
पूर्ण

अटल u8 emc_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_emc *tegra;
	u32 val;

	tegra = container_of(hw, काष्ठा tegra_clk_emc, hw);

	val = पढ़ोl(tegra->clk_regs + CLK_SOURCE_EMC);

	वापस (val >> CLK_SOURCE_EMC_EMC_2X_CLK_SRC_SHIFT)
		& CLK_SOURCE_EMC_EMC_2X_CLK_SRC_MASK;
पूर्ण

अटल काष्ठा tegra_emc *emc_ensure_emc_driver(काष्ठा tegra_clk_emc *tegra)
अणु
	काष्ठा platक्रमm_device *pdev;

	अगर (tegra->emc)
		वापस tegra->emc;

	अगर (!tegra->prepare_timing_change || !tegra->complete_timing_change)
		वापस शून्य;

	अगर (!tegra->emc_node)
		वापस शून्य;

	pdev = of_find_device_by_node(tegra->emc_node);
	अगर (!pdev) अणु
		pr_err("%s: could not get external memory controller\n",
		       __func__);
		वापस शून्य;
	पूर्ण

	of_node_put(tegra->emc_node);
	tegra->emc_node = शून्य;

	tegra->emc = platक्रमm_get_drvdata(pdev);
	अगर (!tegra->emc) अणु
		pr_err("%s: cannot find EMC driver\n", __func__);
		वापस शून्य;
	पूर्ण

	वापस tegra->emc;
पूर्ण

अटल पूर्णांक emc_set_timing(काष्ठा tegra_clk_emc *tegra,
			  काष्ठा emc_timing *timing)
अणु
	पूर्णांक err;
	u8 भाग;
	u32 car_value;
	अचिन्हित दीर्घ flags = 0;
	काष्ठा tegra_emc *emc = emc_ensure_emc_driver(tegra);

	अगर (!emc)
		वापस -ENOENT;

	pr_debug("going to rate %ld prate %ld p %s\n", timing->rate,
		 timing->parent_rate, __clk_get_name(timing->parent));

	अगर (emc_get_parent(&tegra->hw) == timing->parent_index &&
	    clk_get_rate(timing->parent) != timing->parent_rate) अणु
		WARN_ONCE(1, "parent %s rate mismatch %lu %lu\n",
			  __clk_get_name(timing->parent),
			  clk_get_rate(timing->parent),
			  timing->parent_rate);
		वापस -EINVAL;
	पूर्ण

	tegra->changing_timing = true;

	err = clk_set_rate(timing->parent, timing->parent_rate);
	अगर (err) अणु
		pr_err("cannot change parent %s rate to %ld: %d\n",
		       __clk_get_name(timing->parent), timing->parent_rate,
		       err);

		वापस err;
	पूर्ण

	err = clk_prepare_enable(timing->parent);
	अगर (err) अणु
		pr_err("cannot enable parent clock: %d\n", err);
		वापस err;
	पूर्ण

	भाग = timing->parent_rate / (timing->rate / 2) - 2;

	err = tegra->prepare_timing_change(emc, timing->rate);
	अगर (err)
		वापस err;

	spin_lock_irqsave(tegra->lock, flags);

	car_value = पढ़ोl(tegra->clk_regs + CLK_SOURCE_EMC);

	car_value &= ~CLK_SOURCE_EMC_EMC_2X_CLK_SRC(~0);
	car_value |= CLK_SOURCE_EMC_EMC_2X_CLK_SRC(timing->parent_index);

	car_value &= ~CLK_SOURCE_EMC_EMC_2X_CLK_DIVISOR(~0);
	car_value |= CLK_SOURCE_EMC_EMC_2X_CLK_DIVISOR(भाग);

	ग_लिखोl(car_value, tegra->clk_regs + CLK_SOURCE_EMC);

	spin_unlock_irqrestore(tegra->lock, flags);

	tegra->complete_timing_change(emc, timing->rate);

	clk_hw_reparent(&tegra->hw, __clk_get_hw(timing->parent));
	clk_disable_unprepare(tegra->prev_parent);

	tegra->prev_parent = timing->parent;
	tegra->changing_timing = false;

	वापस 0;
पूर्ण

/*
 * Get backup timing to use as an पूर्णांकermediate step when a change between
 * two timings with the same घड़ी source has been requested. First try to
 * find a timing with a higher घड़ी rate to aव्योम a rate below any set rate
 * न्यूनमानs. If that is not possible, find a lower rate.
 */
अटल काष्ठा emc_timing *get_backup_timing(काष्ठा tegra_clk_emc *tegra,
					    पूर्णांक timing_index)
अणु
	पूर्णांक i;
	u32 ram_code = tegra_पढ़ो_ram_code();
	काष्ठा emc_timing *timing;

	क्रम (i = timing_index+1; i < tegra->num_timings; i++) अणु
		timing = tegra->timings + i;
		अगर (timing->ram_code != ram_code)
			अवरोध;

		अगर (emc_parent_clk_sources[timing->parent_index] !=
		    emc_parent_clk_sources[
		      tegra->timings[timing_index].parent_index])
			वापस timing;
	पूर्ण

	क्रम (i = timing_index-1; i >= 0; --i) अणु
		timing = tegra->timings + i;
		अगर (timing->ram_code != ram_code)
			अवरोध;

		अगर (emc_parent_clk_sources[timing->parent_index] !=
		    emc_parent_clk_sources[
		      tegra->timings[timing_index].parent_index])
			वापस timing;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक emc_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_emc *tegra;
	काष्ठा emc_timing *timing = शून्य;
	पूर्णांक i, err;
	u32 ram_code = tegra_पढ़ो_ram_code();

	tegra = container_of(hw, काष्ठा tegra_clk_emc, hw);

	अगर (clk_hw_get_rate(hw) == rate)
		वापस 0;

	/*
	 * When emc_set_timing changes the parent rate, CCF will propagate
	 * that करोwnward to us, so ignore any set_rate calls जबतक a rate
	 * change is alपढ़ोy going on.
	 */
	अगर (tegra->changing_timing)
		वापस 0;

	क्रम (i = 0; i < tegra->num_timings; i++) अणु
		अगर (tegra->timings[i].rate == rate &&
		    tegra->timings[i].ram_code == ram_code) अणु
			timing = tegra->timings + i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!timing) अणु
		pr_err("cannot switch to rate %ld without emc table\n", rate);
		वापस -EINVAL;
	पूर्ण

	अगर (emc_parent_clk_sources[emc_get_parent(hw)] ==
	    emc_parent_clk_sources[timing->parent_index] &&
	    clk_get_rate(timing->parent) != timing->parent_rate) अणु
		/*
		 * Parent घड़ी source not changed but parent rate has changed,
		 * need to temporarily चयन to another parent
		 */

		काष्ठा emc_timing *backup_timing;

		backup_timing = get_backup_timing(tegra, i);
		अगर (!backup_timing) अणु
			pr_err("cannot find backup timing\n");
			वापस -EINVAL;
		पूर्ण

		pr_debug("using %ld as backup rate when going to %ld\n",
			 backup_timing->rate, rate);

		err = emc_set_timing(tegra, backup_timing);
		अगर (err) अणु
			pr_err("cannot set backup timing: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस emc_set_timing(tegra, timing);
पूर्ण

/* Initialization and deinitialization */

अटल पूर्णांक load_one_timing_from_dt(काष्ठा tegra_clk_emc *tegra,
				   काष्ठा emc_timing *timing,
				   काष्ठा device_node *node)
अणु
	पूर्णांक err, i;
	u32 पंचांगp;

	err = of_property_पढ़ो_u32(node, "clock-frequency", &पंचांगp);
	अगर (err) अणु
		pr_err("timing %pOF: failed to read rate\n", node);
		वापस err;
	पूर्ण

	timing->rate = पंचांगp;

	err = of_property_पढ़ो_u32(node, "nvidia,parent-clock-frequency", &पंचांगp);
	अगर (err) अणु
		pr_err("timing %pOF: failed to read parent rate\n", node);
		वापस err;
	पूर्ण

	timing->parent_rate = पंचांगp;

	timing->parent = of_clk_get_by_name(node, "emc-parent");
	अगर (IS_ERR(timing->parent)) अणु
		pr_err("timing %pOF: failed to get parent clock\n", node);
		वापस PTR_ERR(timing->parent);
	पूर्ण

	timing->parent_index = 0xff;
	i = match_string(emc_parent_clk_names, ARRAY_SIZE(emc_parent_clk_names),
			 __clk_get_name(timing->parent));
	अगर (i < 0) अणु
		pr_err("timing %pOF: %s is not a valid parent\n",
		       node, __clk_get_name(timing->parent));
		clk_put(timing->parent);
		वापस -EINVAL;
	पूर्ण

	timing->parent_index = i;
	वापस 0;
पूर्ण

अटल पूर्णांक cmp_timings(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	स्थिर काष्ठा emc_timing *a = _a;
	स्थिर काष्ठा emc_timing *b = _b;

	अगर (a->rate < b->rate)
		वापस -1;
	अन्यथा अगर (a->rate == b->rate)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक load_timings_from_dt(काष्ठा tegra_clk_emc *tegra,
				काष्ठा device_node *node,
				u32 ram_code)
अणु
	काष्ठा emc_timing *timings_ptr;
	काष्ठा device_node *child;
	पूर्णांक child_count = of_get_child_count(node);
	पूर्णांक i = 0, err;
	माप_प्रकार size;

	size = (tegra->num_timings + child_count) * माप(काष्ठा emc_timing);

	tegra->timings = kपुनः_स्मृति(tegra->timings, size, GFP_KERNEL);
	अगर (!tegra->timings)
		वापस -ENOMEM;

	timings_ptr = tegra->timings + tegra->num_timings;
	tegra->num_timings += child_count;

	क्रम_each_child_of_node(node, child) अणु
		काष्ठा emc_timing *timing = timings_ptr + (i++);

		err = load_one_timing_from_dt(tegra, timing, child);
		अगर (err) अणु
			of_node_put(child);
			वापस err;
		पूर्ण

		timing->ram_code = ram_code;
	पूर्ण

	sort(timings_ptr, child_count, माप(काष्ठा emc_timing),
	     cmp_timings, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops tegra_clk_emc_ops = अणु
	.recalc_rate = emc_recalc_rate,
	.determine_rate = emc_determine_rate,
	.set_rate = emc_set_rate,
	.get_parent = emc_get_parent,
पूर्ण;

काष्ठा clk *tegra124_clk_रेजिस्टर_emc(व्योम __iomem *base, काष्ठा device_node *np,
				      spinlock_t *lock)
अणु
	काष्ठा tegra_clk_emc *tegra;
	काष्ठा clk_init_data init;
	काष्ठा device_node *node;
	u32 node_ram_code;
	काष्ठा clk *clk;
	पूर्णांक err;

	tegra = kसुस्मृति(1, माप(*tegra), GFP_KERNEL);
	अगर (!tegra)
		वापस ERR_PTR(-ENOMEM);

	tegra->clk_regs = base;
	tegra->lock = lock;

	tegra->num_timings = 0;

	क्रम_each_child_of_node(np, node) अणु
		err = of_property_पढ़ो_u32(node, "nvidia,ram-code",
					   &node_ram_code);
		अगर (err)
			जारी;

		/*
		 * Store timings क्रम all ram codes as we cannot पढ़ो the
		 * fuses until the apbmisc driver is loaded.
		 */
		err = load_timings_from_dt(tegra, node, node_ram_code);
		अगर (err) अणु
			of_node_put(node);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण

	अगर (tegra->num_timings == 0)
		pr_warn("%s: no memory timings registered\n", __func__);

	tegra->emc_node = of_parse_phandle(np,
			"nvidia,external-memory-controller", 0);
	अगर (!tegra->emc_node)
		pr_warn("%s: couldn't find node for EMC driver\n", __func__);

	init.name = "emc";
	init.ops = &tegra_clk_emc_ops;
	init.flags = CLK_IS_CRITICAL;
	init.parent_names = emc_parent_clk_names;
	init.num_parents = ARRAY_SIZE(emc_parent_clk_names);

	tegra->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &tegra->hw);
	अगर (IS_ERR(clk))
		वापस clk;

	tegra->prev_parent = clk_hw_get_parent_by_index(
		&tegra->hw, emc_get_parent(&tegra->hw))->clk;
	tegra->changing_timing = false;

	/* Allow debugging tools to see the EMC घड़ी */
	clk_रेजिस्टर_clkdev(clk, "emc", "tegra-clk-debug");

	वापस clk;
पूर्ण;

व्योम tegra124_clk_set_emc_callbacks(tegra124_emc_prepare_timing_change_cb *prep_cb,
				    tegra124_emc_complete_timing_change_cb *complete_cb)
अणु
	काष्ठा clk *clk = __clk_lookup("emc");
	काष्ठा tegra_clk_emc *tegra;
	काष्ठा clk_hw *hw;

	अगर (clk) अणु
		hw = __clk_get_hw(clk);
		tegra = container_of(hw, काष्ठा tegra_clk_emc, hw);

		tegra->prepare_timing_change = prep_cb;
		tegra->complete_timing_change = complete_cb;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tegra124_clk_set_emc_callbacks);

bool tegra124_clk_emc_driver_available(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_emc *tegra = container_of(hw, काष्ठा tegra_clk_emc, hw);

	वापस tegra->prepare_timing_change && tegra->complete_timing_change;
पूर्ण
