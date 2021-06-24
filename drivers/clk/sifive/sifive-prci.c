<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 SiFive, Inc.
 * Copyright (C) 2020 Zong Li
 */

#समावेश <linux/clkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश "sifive-prci.h"
#समावेश "fu540-prci.h"
#समावेश "fu740-prci.h"

अटल स्थिर काष्ठा prci_clk_desc prci_clk_fu540 = अणु
	.clks = __prci_init_घड़ीs_fu540,
	.num_clks = ARRAY_SIZE(__prci_init_घड़ीs_fu540),
पूर्ण;

/*
 * Private functions
 */

/**
 * __prci_पढ़ोl() - पढ़ो from a PRCI रेजिस्टर
 * @pd: PRCI context
 * @offs: रेजिस्टर offset to पढ़ो from (in bytes, from PRCI base address)
 *
 * Read the रेजिस्टर located at offset @offs from the base भव
 * address of the PRCI रेजिस्टर target described by @pd, and वापस
 * the value to the caller.
 *
 * Context: Any context.
 *
 * Return: the contents of the रेजिस्टर described by @pd and @offs.
 */
अटल u32 __prci_पढ़ोl(काष्ठा __prci_data *pd, u32 offs)
अणु
	वापस पढ़ोl_relaxed(pd->va + offs);
पूर्ण

अटल व्योम __prci_ग_लिखोl(u32 v, u32 offs, काष्ठा __prci_data *pd)
अणु
	ग_लिखोl_relaxed(v, pd->va + offs);
पूर्ण

/* WRPLL-related निजी functions */

/**
 * __prci_wrpll_unpack() - unpack WRPLL configuration रेजिस्टरs पूर्णांकo parameters
 * @c: ptr to a काष्ठा wrpll_cfg record to ग_लिखो config पूर्णांकo
 * @r: value पढ़ो from the PRCI PLL configuration रेजिस्टर
 *
 * Given a value @r पढ़ो from an FU740 PRCI PLL configuration रेजिस्टर,
 * split it पूर्णांकo fields and populate it पूर्णांकo the WRPLL configuration record
 * poपूर्णांकed to by @c.
 *
 * The COREPLLCFG0 macros are used below, but the other *PLLCFG0 macros
 * have the same रेजिस्टर layout.
 *
 * Context: Any context.
 */
अटल व्योम __prci_wrpll_unpack(काष्ठा wrpll_cfg *c, u32 r)
अणु
	u32 v;

	v = r & PRCI_COREPLLCFG0_DIVR_MASK;
	v >>= PRCI_COREPLLCFG0_DIVR_SHIFT;
	c->भागr = v;

	v = r & PRCI_COREPLLCFG0_DIVF_MASK;
	v >>= PRCI_COREPLLCFG0_DIVF_SHIFT;
	c->भागf = v;

	v = r & PRCI_COREPLLCFG0_DIVQ_MASK;
	v >>= PRCI_COREPLLCFG0_DIVQ_SHIFT;
	c->भागq = v;

	v = r & PRCI_COREPLLCFG0_RANGE_MASK;
	v >>= PRCI_COREPLLCFG0_RANGE_SHIFT;
	c->range = v;

	c->flags &=
	    (WRPLL_FLAGS_INT_FEEDBACK_MASK | WRPLL_FLAGS_EXT_FEEDBACK_MASK);

	/* बाह्यal feedback mode not supported */
	c->flags |= WRPLL_FLAGS_INT_FEEDBACK_MASK;
पूर्ण

/**
 * __prci_wrpll_pack() - pack PLL configuration parameters पूर्णांकo a रेजिस्टर value
 * @c: poपूर्णांकer to a काष्ठा wrpll_cfg record containing the PLL's cfg
 *
 * Using a set of WRPLL configuration values poपूर्णांकed to by @c,
 * assemble a PRCI PLL configuration रेजिस्टर value, and वापस it to
 * the caller.
 *
 * Context: Any context.  Caller must ensure that the contents of the
 *          record poपूर्णांकed to by @c करो not change during the execution
 *          of this function.
 *
 * Returns: a value suitable क्रम writing पूर्णांकo a PRCI PLL configuration
 *          रेजिस्टर
 */
अटल u32 __prci_wrpll_pack(स्थिर काष्ठा wrpll_cfg *c)
अणु
	u32 r = 0;

	r |= c->भागr << PRCI_COREPLLCFG0_DIVR_SHIFT;
	r |= c->भागf << PRCI_COREPLLCFG0_DIVF_SHIFT;
	r |= c->भागq << PRCI_COREPLLCFG0_DIVQ_SHIFT;
	r |= c->range << PRCI_COREPLLCFG0_RANGE_SHIFT;

	/* बाह्यal feedback mode not supported */
	r |= PRCI_COREPLLCFG0_FSE_MASK;

	वापस r;
पूर्ण

/**
 * __prci_wrpll_पढ़ो_cfg0() - पढ़ो the WRPLL configuration from the PRCI
 * @pd: PRCI context
 * @pwd: PRCI WRPLL metadata
 *
 * Read the current configuration of the PLL identअगरied by @pwd from
 * the PRCI identअगरied by @pd, and store it पूर्णांकo the local configuration
 * cache in @pwd.
 *
 * Context: Any context.  Caller must prevent the records poपूर्णांकed to by
 *          @pd and @pwd from changing during execution.
 */
अटल व्योम __prci_wrpll_पढ़ो_cfg0(काष्ठा __prci_data *pd,
				   काष्ठा __prci_wrpll_data *pwd)
अणु
	__prci_wrpll_unpack(&pwd->c, __prci_पढ़ोl(pd, pwd->cfg0_offs));
पूर्ण

/**
 * __prci_wrpll_ग_लिखो_cfg0() - ग_लिखो WRPLL configuration पूर्णांकo the PRCI
 * @pd: PRCI context
 * @pwd: PRCI WRPLL metadata
 * @c: WRPLL configuration record to ग_लिखो
 *
 * Write the WRPLL configuration described by @c पूर्णांकo the WRPLL
 * configuration रेजिस्टर identअगरied by @pwd in the PRCI instance
 * described by @c.  Make a cached copy of the WRPLL's current
 * configuration so it can be used by other code.
 *
 * Context: Any context.  Caller must prevent the records poपूर्णांकed to by
 *          @pd and @pwd from changing during execution.
 */
अटल व्योम __prci_wrpll_ग_लिखो_cfg0(काष्ठा __prci_data *pd,
				    काष्ठा __prci_wrpll_data *pwd,
				    काष्ठा wrpll_cfg *c)
अणु
	__prci_ग_लिखोl(__prci_wrpll_pack(c), pwd->cfg0_offs, pd);

	स_नकल(&pwd->c, c, माप(*c));
पूर्ण

/**
 * __prci_wrpll_ग_लिखो_cfg1() - ग_लिखो Clock enable/disable configuration
 * पूर्णांकo the PRCI
 * @pd: PRCI context
 * @pwd: PRCI WRPLL metadata
 * @enable: Clock enable or disable value
 */
अटल व्योम __prci_wrpll_ग_लिखो_cfg1(काष्ठा __prci_data *pd,
				    काष्ठा __prci_wrpll_data *pwd,
				    u32 enable)
अणु
	__prci_ग_लिखोl(enable, pwd->cfg1_offs, pd);
पूर्ण

/*
 * Linux घड़ी framework पूर्णांकegration
 *
 * See the Linux घड़ी framework करोcumentation क्रम more inक्रमmation on
 * these functions.
 */

अचिन्हित दीर्घ sअगरive_prci_wrpll_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा __prci_घड़ी *pc = clk_hw_to_prci_घड़ी(hw);
	काष्ठा __prci_wrpll_data *pwd = pc->pwd;

	वापस wrpll_calc_output_rate(&pwd->c, parent_rate);
पूर्ण

दीर्घ sअगरive_prci_wrpll_round_rate(काष्ठा clk_hw *hw,
				  अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा __prci_घड़ी *pc = clk_hw_to_prci_घड़ी(hw);
	काष्ठा __prci_wrpll_data *pwd = pc->pwd;
	काष्ठा wrpll_cfg c;

	स_नकल(&c, &pwd->c, माप(c));

	wrpll_configure_क्रम_rate(&c, rate, *parent_rate);

	वापस wrpll_calc_output_rate(&c, *parent_rate);
पूर्ण

पूर्णांक sअगरive_prci_wrpll_set_rate(काष्ठा clk_hw *hw,
			       अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा __prci_घड़ी *pc = clk_hw_to_prci_घड़ी(hw);
	काष्ठा __prci_wrpll_data *pwd = pc->pwd;
	काष्ठा __prci_data *pd = pc->pd;
	पूर्णांक r;

	r = wrpll_configure_क्रम_rate(&pwd->c, rate, parent_rate);
	अगर (r)
		वापस r;

	अगर (pwd->enable_bypass)
		pwd->enable_bypass(pd);

	__prci_wrpll_ग_लिखो_cfg0(pd, pwd, &pwd->c);

	udelay(wrpll_calc_max_lock_us(&pwd->c));

	वापस 0;
पूर्ण

पूर्णांक sअगरive_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा __prci_घड़ी *pc = clk_hw_to_prci_घड़ी(hw);
	काष्ठा __prci_wrpll_data *pwd = pc->pwd;
	काष्ठा __prci_data *pd = pc->pd;
	u32 r;

	r = __prci_पढ़ोl(pd, pwd->cfg1_offs);

	अगर (r & PRCI_COREPLLCFG1_CKE_MASK)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक sअगरive_prci_घड़ी_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा __prci_घड़ी *pc = clk_hw_to_prci_घड़ी(hw);
	काष्ठा __prci_wrpll_data *pwd = pc->pwd;
	काष्ठा __prci_data *pd = pc->pd;

	अगर (sअगरive_clk_is_enabled(hw))
		वापस 0;

	__prci_wrpll_ग_लिखो_cfg1(pd, pwd, PRCI_COREPLLCFG1_CKE_MASK);

	अगर (pwd->disable_bypass)
		pwd->disable_bypass(pd);

	वापस 0;
पूर्ण

व्योम sअगरive_prci_घड़ी_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा __prci_घड़ी *pc = clk_hw_to_prci_घड़ी(hw);
	काष्ठा __prci_wrpll_data *pwd = pc->pwd;
	काष्ठा __prci_data *pd = pc->pd;
	u32 r;

	अगर (pwd->enable_bypass)
		pwd->enable_bypass(pd);

	r = __prci_पढ़ोl(pd, pwd->cfg1_offs);
	r &= ~PRCI_COREPLLCFG1_CKE_MASK;

	__prci_wrpll_ग_लिखो_cfg1(pd, pwd, r);
पूर्ण

/* TLCLKSEL घड़ी पूर्णांकegration */

अचिन्हित दीर्घ sअगरive_prci_tlclksel_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा __prci_घड़ी *pc = clk_hw_to_prci_घड़ी(hw);
	काष्ठा __prci_data *pd = pc->pd;
	u32 v;
	u8 भाग;

	v = __prci_पढ़ोl(pd, PRCI_CLKMUXSTATUSREG_OFFSET);
	v &= PRCI_CLKMUXSTATUSREG_TLCLKSEL_STATUS_MASK;
	भाग = v ? 1 : 2;

	वापस भाग_u64(parent_rate, भाग);
पूर्ण

/* HFPCLK घड़ी पूर्णांकegration */

अचिन्हित दीर्घ sअगरive_prci_hfpclkplद_भाग_recalc_rate(काष्ठा clk_hw *hw,
						   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा __prci_घड़ी *pc = clk_hw_to_prci_घड़ी(hw);
	काष्ठा __prci_data *pd = pc->pd;
	u32 भाग = __prci_पढ़ोl(pd, PRCI_HFPCLKPLLDIV_OFFSET);

	वापस भाग_u64(parent_rate, भाग + 2);
पूर्ण

/*
 * Core घड़ी mux control
 */

/**
 * sअगरive_prci_coreclksel_use_hfclk() - चयन the CORECLK mux to output HFCLK
 * @pd: काष्ठा __prci_data * क्रम the PRCI containing the CORECLK mux reg
 *
 * Switch the CORECLK mux to the HFCLK input source; वापस once complete.
 *
 * Context: Any context.  Caller must prevent concurrent changes to the
 *          PRCI_CORECLKSEL_OFFSET रेजिस्टर.
 */
व्योम sअगरive_prci_coreclksel_use_hfclk(काष्ठा __prci_data *pd)
अणु
	u32 r;

	r = __prci_पढ़ोl(pd, PRCI_CORECLKSEL_OFFSET);
	r |= PRCI_CORECLKSEL_CORECLKSEL_MASK;
	__prci_ग_लिखोl(r, PRCI_CORECLKSEL_OFFSET, pd);

	r = __prci_पढ़ोl(pd, PRCI_CORECLKSEL_OFFSET);	/* barrier */
पूर्ण

/**
 * sअगरive_prci_coreclksel_use_corepll() - चयन the CORECLK mux to output
 * COREPLL
 * @pd: काष्ठा __prci_data * क्रम the PRCI containing the CORECLK mux reg
 *
 * Switch the CORECLK mux to the COREPLL output घड़ी; वापस once complete.
 *
 * Context: Any context.  Caller must prevent concurrent changes to the
 *          PRCI_CORECLKSEL_OFFSET रेजिस्टर.
 */
व्योम sअगरive_prci_coreclksel_use_corepll(काष्ठा __prci_data *pd)
अणु
	u32 r;

	r = __prci_पढ़ोl(pd, PRCI_CORECLKSEL_OFFSET);
	r &= ~PRCI_CORECLKSEL_CORECLKSEL_MASK;
	__prci_ग_लिखोl(r, PRCI_CORECLKSEL_OFFSET, pd);

	r = __prci_पढ़ोl(pd, PRCI_CORECLKSEL_OFFSET);	/* barrier */
पूर्ण

/**
 * sअगरive_prci_coreclksel_use_final_corepll() - चयन the CORECLK mux to output
 * FINAL_COREPLL
 * @pd: काष्ठा __prci_data * क्रम the PRCI containing the CORECLK mux reg
 *
 * Switch the CORECLK mux to the final COREPLL output घड़ी; वापस once
 * complete.
 *
 * Context: Any context.  Caller must prevent concurrent changes to the
 *          PRCI_CORECLKSEL_OFFSET रेजिस्टर.
 */
व्योम sअगरive_prci_coreclksel_use_final_corepll(काष्ठा __prci_data *pd)
अणु
	u32 r;

	r = __prci_पढ़ोl(pd, PRCI_CORECLKSEL_OFFSET);
	r &= ~PRCI_CORECLKSEL_CORECLKSEL_MASK;
	__prci_ग_लिखोl(r, PRCI_CORECLKSEL_OFFSET, pd);

	r = __prci_पढ़ोl(pd, PRCI_CORECLKSEL_OFFSET);	/* barrier */
पूर्ण

/**
 * sअगरive_prci_corepllsel_use_dvfscorepll() - चयन the COREPLL mux to
 * output DVFS_COREPLL
 * @pd: काष्ठा __prci_data * क्रम the PRCI containing the COREPLL mux reg
 *
 * Switch the COREPLL mux to the DVFSCOREPLL output घड़ी; वापस once complete.
 *
 * Context: Any context.  Caller must prevent concurrent changes to the
 *          PRCI_COREPLLSEL_OFFSET रेजिस्टर.
 */
व्योम sअगरive_prci_corepllsel_use_dvfscorepll(काष्ठा __prci_data *pd)
अणु
	u32 r;

	r = __prci_पढ़ोl(pd, PRCI_COREPLLSEL_OFFSET);
	r |= PRCI_COREPLLSEL_COREPLLSEL_MASK;
	__prci_ग_लिखोl(r, PRCI_COREPLLSEL_OFFSET, pd);

	r = __prci_पढ़ोl(pd, PRCI_COREPLLSEL_OFFSET);	/* barrier */
पूर्ण

/**
 * sअगरive_prci_corepllsel_use_corepll() - चयन the COREPLL mux to
 * output COREPLL
 * @pd: काष्ठा __prci_data * क्रम the PRCI containing the COREPLL mux reg
 *
 * Switch the COREPLL mux to the COREPLL output घड़ी; वापस once complete.
 *
 * Context: Any context.  Caller must prevent concurrent changes to the
 *          PRCI_COREPLLSEL_OFFSET रेजिस्टर.
 */
व्योम sअगरive_prci_corepllsel_use_corepll(काष्ठा __prci_data *pd)
अणु
	u32 r;

	r = __prci_पढ़ोl(pd, PRCI_COREPLLSEL_OFFSET);
	r &= ~PRCI_COREPLLSEL_COREPLLSEL_MASK;
	__prci_ग_लिखोl(r, PRCI_COREPLLSEL_OFFSET, pd);

	r = __prci_पढ़ोl(pd, PRCI_COREPLLSEL_OFFSET);	/* barrier */
पूर्ण

/**
 * sअगरive_prci_hfpclkpllsel_use_hfclk() - चयन the HFPCLKPLL mux to
 * output HFCLK
 * @pd: काष्ठा __prci_data * क्रम the PRCI containing the HFPCLKPLL mux reg
 *
 * Switch the HFPCLKPLL mux to the HFCLK input source; वापस once complete.
 *
 * Context: Any context.  Caller must prevent concurrent changes to the
 *          PRCI_HFPCLKPLLSEL_OFFSET रेजिस्टर.
 */
व्योम sअगरive_prci_hfpclkpllsel_use_hfclk(काष्ठा __prci_data *pd)
अणु
	u32 r;

	r = __prci_पढ़ोl(pd, PRCI_HFPCLKPLLSEL_OFFSET);
	r |= PRCI_HFPCLKPLLSEL_HFPCLKPLLSEL_MASK;
	__prci_ग_लिखोl(r, PRCI_HFPCLKPLLSEL_OFFSET, pd);

	r = __prci_पढ़ोl(pd, PRCI_HFPCLKPLLSEL_OFFSET);	/* barrier */
पूर्ण

/**
 * sअगरive_prci_hfpclkpllsel_use_hfpclkpll() - चयन the HFPCLKPLL mux to
 * output HFPCLKPLL
 * @pd: काष्ठा __prci_data * क्रम the PRCI containing the HFPCLKPLL mux reg
 *
 * Switch the HFPCLKPLL mux to the HFPCLKPLL output घड़ी; वापस once complete.
 *
 * Context: Any context.  Caller must prevent concurrent changes to the
 *          PRCI_HFPCLKPLLSEL_OFFSET रेजिस्टर.
 */
व्योम sअगरive_prci_hfpclkpllsel_use_hfpclkpll(काष्ठा __prci_data *pd)
अणु
	u32 r;

	r = __prci_पढ़ोl(pd, PRCI_HFPCLKPLLSEL_OFFSET);
	r &= ~PRCI_HFPCLKPLLSEL_HFPCLKPLLSEL_MASK;
	__prci_ग_लिखोl(r, PRCI_HFPCLKPLLSEL_OFFSET, pd);

	r = __prci_पढ़ोl(pd, PRCI_HFPCLKPLLSEL_OFFSET);	/* barrier */
पूर्ण

/* PCIE AUX घड़ी APIs क्रम enable, disable. */
पूर्णांक sअगरive_prci_pcie_aux_घड़ी_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा __prci_घड़ी *pc = clk_hw_to_prci_घड़ी(hw);
	काष्ठा __prci_data *pd = pc->pd;
	u32 r;

	r = __prci_पढ़ोl(pd, PRCI_PCIE_AUX_OFFSET);

	अगर (r & PRCI_PCIE_AUX_EN_MASK)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक sअगरive_prci_pcie_aux_घड़ी_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा __prci_घड़ी *pc = clk_hw_to_prci_घड़ी(hw);
	काष्ठा __prci_data *pd = pc->pd;
	u32 r __maybe_unused;

	अगर (sअगरive_prci_pcie_aux_घड़ी_is_enabled(hw))
		वापस 0;

	__prci_ग_लिखोl(1, PRCI_PCIE_AUX_OFFSET, pd);
	r = __prci_पढ़ोl(pd, PRCI_PCIE_AUX_OFFSET);	/* barrier */

	वापस 0;
पूर्ण

व्योम sअगरive_prci_pcie_aux_घड़ी_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा __prci_घड़ी *pc = clk_hw_to_prci_घड़ी(hw);
	काष्ठा __prci_data *pd = pc->pd;
	u32 r __maybe_unused;

	__prci_ग_लिखोl(0, PRCI_PCIE_AUX_OFFSET, pd);
	r = __prci_पढ़ोl(pd, PRCI_PCIE_AUX_OFFSET);	/* barrier */

पूर्ण

/**
 * __prci_रेजिस्टर_घड़ीs() - रेजिस्टर घड़ी controls in the PRCI
 * @dev: Linux काष्ठा device
 * @pd: The poपूर्णांकer क्रम PRCI per-device instance data
 * @desc: The poपूर्णांकer क्रम the inक्रमmation of घड़ीs of each SoCs
 *
 * Register the list of घड़ी controls described in __prci_init_घड़ीs[] with
 * the Linux घड़ी framework.
 *
 * Return: 0 upon success or a negative error code upon failure.
 */
अटल पूर्णांक __prci_रेजिस्टर_घड़ीs(काष्ठा device *dev, काष्ठा __prci_data *pd,
				  स्थिर काष्ठा prci_clk_desc *desc)
अणु
	काष्ठा clk_init_data init = अणु पूर्ण;
	काष्ठा __prci_घड़ी *pic;
	पूर्णांक parent_count, i, r;

	parent_count = of_clk_get_parent_count(dev->of_node);
	अगर (parent_count != EXPECTED_CLK_PARENT_COUNT) अणु
		dev_err(dev, "expected only two parent clocks, found %d\n",
			parent_count);
		वापस -EINVAL;
	पूर्ण

	/* Register PLLs */
	क्रम (i = 0; i < desc->num_clks; ++i) अणु
		pic = &(desc->clks[i]);

		init.name = pic->name;
		init.parent_names = &pic->parent_name;
		init.num_parents = 1;
		init.ops = pic->ops;
		pic->hw.init = &init;

		pic->pd = pd;

		अगर (pic->pwd)
			__prci_wrpll_पढ़ो_cfg0(pd, pic->pwd);

		r = devm_clk_hw_रेजिस्टर(dev, &pic->hw);
		अगर (r) अणु
			dev_warn(dev, "Failed to register clock %s: %d\n",
				 init.name, r);
			वापस r;
		पूर्ण

		r = clk_hw_रेजिस्टर_clkdev(&pic->hw, pic->name, dev_name(dev));
		अगर (r) अणु
			dev_warn(dev, "Failed to register clkdev for %s: %d\n",
				 init.name, r);
			वापस r;
		पूर्ण

		pd->hw_clks.hws[i] = &pic->hw;
	पूर्ण

	pd->hw_clks.num = i;

	r = devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					&pd->hw_clks);
	अगर (r) अणु
		dev_err(dev, "could not add hw_provider: %d\n", r);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sअगरive_prci_init() - initialize prci data and check parent count
 * @pdev: platक्रमm device poपूर्णांकer क्रम the prci
 *
 * Return: 0 upon success or a negative error code upon failure.
 */
अटल पूर्णांक sअगरive_prci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा __prci_data *pd;
	स्थिर काष्ठा prci_clk_desc *desc;
	पूर्णांक r;

	desc = of_device_get_match_data(&pdev->dev);

	pd = devm_kzalloc(dev, काष्ठा_size(pd, hw_clks.hws, desc->num_clks), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pd->va = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(pd->va))
		वापस PTR_ERR(pd->va);

	pd->reset.rcdev.owner = THIS_MODULE;
	pd->reset.rcdev.nr_resets = PRCI_RST_NR;
	pd->reset.rcdev.ops = &reset_simple_ops;
	pd->reset.rcdev.of_node = pdev->dev.of_node;
	pd->reset.active_low = true;
	pd->reset.membase = pd->va + PRCI_DEVICESRESETREG_OFFSET;
	spin_lock_init(&pd->reset.lock);

	r = devm_reset_controller_रेजिस्टर(&pdev->dev, &pd->reset.rcdev);
	अगर (r) अणु
		dev_err(dev, "could not register reset controller: %d\n", r);
		वापस r;
	पूर्ण
	r = __prci_रेजिस्टर_घड़ीs(dev, pd, desc);
	अगर (r) अणु
		dev_err(dev, "could not register clocks: %d\n", r);
		वापस r;
	पूर्ण

	dev_dbg(dev, "SiFive PRCI probed\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sअगरive_prci_of_match[] = अणु
	अणु.compatible = "sifive,fu540-c000-prci", .data = &prci_clk_fu540पूर्ण,
	अणु.compatible = "sifive,fu740-c000-prci", .data = &prci_clk_fu740पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sअगरive_prci_driver = अणु
	.driver = अणु
		.name = "sifive-clk-prci",
		.of_match_table = sअगरive_prci_of_match,
	पूर्ण,
	.probe = sअगरive_prci_probe,
पूर्ण;

अटल पूर्णांक __init sअगरive_prci_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sअगरive_prci_driver);
पूर्ण
core_initcall(sअगरive_prci_init);
