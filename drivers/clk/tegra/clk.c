<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clkdev.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/reset-controller.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "clk.h"

/* Global data of Tegra CPU CAR ops */
अटल काष्ठा tegra_cpu_car_ops dummy_car_ops;
काष्ठा tegra_cpu_car_ops *tegra_cpu_car_ops = &dummy_car_ops;

पूर्णांक *periph_clk_enb_refcnt;
अटल पूर्णांक periph_banks;
अटल u32 *periph_state_ctx;
अटल काष्ठा clk **clks;
अटल पूर्णांक clk_num;
अटल काष्ठा clk_onecell_data clk_data;

/* Handlers क्रम SoC-specअगरic reset lines */
अटल पूर्णांक (*special_reset_निश्चित)(अचिन्हित दीर्घ);
अटल पूर्णांक (*special_reset_deनिश्चित)(अचिन्हित दीर्घ);
अटल अचिन्हित पूर्णांक num_special_reset;

अटल स्थिर काष्ठा tegra_clk_periph_regs periph_regs[] = अणु
	[0] = अणु
		.enb_reg = CLK_OUT_ENB_L,
		.enb_set_reg = CLK_OUT_ENB_SET_L,
		.enb_clr_reg = CLK_OUT_ENB_CLR_L,
		.rst_reg = RST_DEVICES_L,
		.rst_set_reg = RST_DEVICES_SET_L,
		.rst_clr_reg = RST_DEVICES_CLR_L,
	पूर्ण,
	[1] = अणु
		.enb_reg = CLK_OUT_ENB_H,
		.enb_set_reg = CLK_OUT_ENB_SET_H,
		.enb_clr_reg = CLK_OUT_ENB_CLR_H,
		.rst_reg = RST_DEVICES_H,
		.rst_set_reg = RST_DEVICES_SET_H,
		.rst_clr_reg = RST_DEVICES_CLR_H,
	पूर्ण,
	[2] = अणु
		.enb_reg = CLK_OUT_ENB_U,
		.enb_set_reg = CLK_OUT_ENB_SET_U,
		.enb_clr_reg = CLK_OUT_ENB_CLR_U,
		.rst_reg = RST_DEVICES_U,
		.rst_set_reg = RST_DEVICES_SET_U,
		.rst_clr_reg = RST_DEVICES_CLR_U,
	पूर्ण,
	[3] = अणु
		.enb_reg = CLK_OUT_ENB_V,
		.enb_set_reg = CLK_OUT_ENB_SET_V,
		.enb_clr_reg = CLK_OUT_ENB_CLR_V,
		.rst_reg = RST_DEVICES_V,
		.rst_set_reg = RST_DEVICES_SET_V,
		.rst_clr_reg = RST_DEVICES_CLR_V,
	पूर्ण,
	[4] = अणु
		.enb_reg = CLK_OUT_ENB_W,
		.enb_set_reg = CLK_OUT_ENB_SET_W,
		.enb_clr_reg = CLK_OUT_ENB_CLR_W,
		.rst_reg = RST_DEVICES_W,
		.rst_set_reg = RST_DEVICES_SET_W,
		.rst_clr_reg = RST_DEVICES_CLR_W,
	पूर्ण,
	[5] = अणु
		.enb_reg = CLK_OUT_ENB_X,
		.enb_set_reg = CLK_OUT_ENB_SET_X,
		.enb_clr_reg = CLK_OUT_ENB_CLR_X,
		.rst_reg = RST_DEVICES_X,
		.rst_set_reg = RST_DEVICES_SET_X,
		.rst_clr_reg = RST_DEVICES_CLR_X,
	पूर्ण,
	[6] = अणु
		.enb_reg = CLK_OUT_ENB_Y,
		.enb_set_reg = CLK_OUT_ENB_SET_Y,
		.enb_clr_reg = CLK_OUT_ENB_CLR_Y,
		.rst_reg = RST_DEVICES_Y,
		.rst_set_reg = RST_DEVICES_SET_Y,
		.rst_clr_reg = RST_DEVICES_CLR_Y,
	पूर्ण,
पूर्ण;

अटल व्योम __iomem *clk_base;

अटल पूर्णांक tegra_clk_rst_निश्चित(काष्ठा reset_controller_dev *rcdev,
		अचिन्हित दीर्घ id)
अणु
	/*
	 * If peripheral is on the APB bus then we must पढ़ो the APB bus to
	 * flush the ग_लिखो operation in apb bus. This will aव्योम peripheral
	 * access after disabling घड़ी. Since the reset driver has no
	 * knowledge of which reset IDs represent which devices, simply करो
	 * this all the समय.
	 */
	tegra_पढ़ो_chipid();

	अगर (id < periph_banks * 32) अणु
		ग_लिखोl_relaxed(BIT(id % 32),
			       clk_base + periph_regs[id / 32].rst_set_reg);
		वापस 0;
	पूर्ण अन्यथा अगर (id < periph_banks * 32 + num_special_reset) अणु
		वापस special_reset_निश्चित(id);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tegra_clk_rst_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
		अचिन्हित दीर्घ id)
अणु
	अगर (id < periph_banks * 32) अणु
		ग_लिखोl_relaxed(BIT(id % 32),
			       clk_base + periph_regs[id / 32].rst_clr_reg);
		वापस 0;
	पूर्ण अन्यथा अगर (id < periph_banks * 32 + num_special_reset) अणु
		वापस special_reset_deनिश्चित(id);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tegra_clk_rst_reset(काष्ठा reset_controller_dev *rcdev,
		अचिन्हित दीर्घ id)
अणु
	पूर्णांक err;

	err = tegra_clk_rst_निश्चित(rcdev, id);
	अगर (err)
		वापस err;

	udelay(1);

	वापस tegra_clk_rst_deनिश्चित(rcdev, id);
पूर्ण

स्थिर काष्ठा tegra_clk_periph_regs *get_reg_bank(पूर्णांक clkid)
अणु
	पूर्णांक reg_bank = clkid / 32;

	अगर (reg_bank < periph_banks)
		वापस &periph_regs[reg_bank];
	अन्यथा अणु
		WARN_ON(1);
		वापस शून्य;
	पूर्ण
पूर्ण

व्योम tegra_clk_set_pllp_out_cpu(bool enable)
अणु
	u32 val;

	val = पढ़ोl_relaxed(clk_base + CLK_OUT_ENB_Y);
	अगर (enable)
		val |= CLK_ENB_PLLP_OUT_CPU;
	अन्यथा
		val &= ~CLK_ENB_PLLP_OUT_CPU;

	ग_लिखोl_relaxed(val, clk_base + CLK_OUT_ENB_Y);
पूर्ण

व्योम tegra_clk_periph_suspend(व्योम)
अणु
	अचिन्हित पूर्णांक i, idx;

	idx = 0;
	क्रम (i = 0; i < periph_banks; i++, idx++)
		periph_state_ctx[idx] =
			पढ़ोl_relaxed(clk_base + periph_regs[i].enb_reg);

	क्रम (i = 0; i < periph_banks; i++, idx++)
		periph_state_ctx[idx] =
			पढ़ोl_relaxed(clk_base + periph_regs[i].rst_reg);
पूर्ण

व्योम tegra_clk_periph_resume(व्योम)
अणु
	अचिन्हित पूर्णांक i, idx;

	idx = 0;
	क्रम (i = 0; i < periph_banks; i++, idx++)
		ग_लिखोl_relaxed(periph_state_ctx[idx],
			       clk_base + periph_regs[i].enb_reg);
	/*
	 * All non-boot peripherals will be in reset state on resume.
	 * Wait क्रम 5us of reset propagation delay beक्रमe de-निश्चितing
	 * the peripherals based on the saved context.
	 */
	fence_udelay(5, clk_base);

	क्रम (i = 0; i < periph_banks; i++, idx++)
		ग_लिखोl_relaxed(periph_state_ctx[idx],
			       clk_base + periph_regs[i].rst_reg);

	fence_udelay(2, clk_base);
पूर्ण

अटल पूर्णांक tegra_clk_periph_ctx_init(पूर्णांक banks)
अणु
	periph_state_ctx = kसुस्मृति(2 * banks, माप(*periph_state_ctx),
				   GFP_KERNEL);
	अगर (!periph_state_ctx)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

काष्ठा clk ** __init tegra_clk_init(व्योम __iomem *regs, पूर्णांक num, पूर्णांक banks)
अणु
	clk_base = regs;

	अगर (WARN_ON(banks > ARRAY_SIZE(periph_regs)))
		वापस शून्य;

	periph_clk_enb_refcnt = kसुस्मृति(32 * banks,
					माप(*periph_clk_enb_refcnt),
					GFP_KERNEL);
	अगर (!periph_clk_enb_refcnt)
		वापस शून्य;

	periph_banks = banks;

	clks = kसुस्मृति(num, माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!clks) अणु
		kमुक्त(periph_clk_enb_refcnt);
		वापस शून्य;
	पूर्ण

	clk_num = num;

	अगर (IS_ENABLED(CONFIG_PM_SLEEP)) अणु
		अगर (tegra_clk_periph_ctx_init(banks)) अणु
			kमुक्त(periph_clk_enb_refcnt);
			kमुक्त(clks);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस clks;
पूर्ण

व्योम __init tegra_init_dup_clks(काष्ठा tegra_clk_duplicate *dup_list,
				काष्ठा clk *clks[], पूर्णांक clk_max)
अणु
	काष्ठा clk *clk;

	क्रम (; dup_list->clk_id < clk_max; dup_list++) अणु
		clk = clks[dup_list->clk_id];
		dup_list->lookup.clk = clk;
		clkdev_add(&dup_list->lookup);
	पूर्ण
पूर्ण

व्योम __init tegra_init_from_table(काष्ठा tegra_clk_init_table *tbl,
				  काष्ठा clk *clks[], पूर्णांक clk_max)
अणु
	काष्ठा clk *clk;

	क्रम (; tbl->clk_id < clk_max; tbl++) अणु
		clk = clks[tbl->clk_id];
		अगर (IS_ERR_OR_शून्य(clk)) अणु
			pr_err("%s: invalid entry %ld in clks array for id %d\n",
			       __func__, PTR_ERR(clk), tbl->clk_id);
			WARN_ON(1);

			जारी;
		पूर्ण

		अगर (tbl->parent_id < clk_max) अणु
			काष्ठा clk *parent = clks[tbl->parent_id];
			अगर (clk_set_parent(clk, parent)) अणु
				pr_err("%s: Failed to set parent %s of %s\n",
				       __func__, __clk_get_name(parent),
				       __clk_get_name(clk));
				WARN_ON(1);
			पूर्ण
		पूर्ण

		अगर (tbl->rate)
			अगर (clk_set_rate(clk, tbl->rate)) अणु
				pr_err("%s: Failed to set rate %lu of %s\n",
				       __func__, tbl->rate,
				       __clk_get_name(clk));
				WARN_ON(1);
			पूर्ण

		अगर (tbl->state)
			अगर (clk_prepare_enable(clk)) अणु
				pr_err("%s: Failed to enable %s\n", __func__,
				       __clk_get_name(clk));
				WARN_ON(1);
			पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reset_control_ops rst_ops = अणु
	.निश्चित = tegra_clk_rst_निश्चित,
	.deनिश्चित = tegra_clk_rst_deनिश्चित,
	.reset = tegra_clk_rst_reset,
पूर्ण;

अटल काष्ठा reset_controller_dev rst_ctlr = अणु
	.ops = &rst_ops,
	.owner = THIS_MODULE,
	.of_reset_n_cells = 1,
पूर्ण;

व्योम __init tegra_add_of_provider(काष्ठा device_node *np,
				  व्योम *clk_src_onecell_get)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < clk_num; i++) अणु
		अगर (IS_ERR(clks[i])) अणु
			pr_err
			    ("Tegra clk %d: register failed with %ld\n",
			     i, PTR_ERR(clks[i]));
		पूर्ण
		अगर (!clks[i])
			clks[i] = ERR_PTR(-EINVAL);
	पूर्ण

	clk_data.clks = clks;
	clk_data.clk_num = clk_num;
	of_clk_add_provider(np, clk_src_onecell_get, &clk_data);

	rst_ctlr.of_node = np;
	rst_ctlr.nr_resets = periph_banks * 32 + num_special_reset;
	reset_controller_रेजिस्टर(&rst_ctlr);
पूर्ण

व्योम __init tegra_init_special_resets(अचिन्हित पूर्णांक num,
				      पूर्णांक (*निश्चित)(अचिन्हित दीर्घ),
				      पूर्णांक (*deनिश्चित)(अचिन्हित दीर्घ))
अणु
	num_special_reset = num;
	special_reset_निश्चित = निश्चित;
	special_reset_deनिश्चित = deनिश्चित;
पूर्ण

व्योम __init tegra_रेजिस्टर_devclks(काष्ठा tegra_devclk *dev_clks, पूर्णांक num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num; i++, dev_clks++)
		clk_रेजिस्टर_clkdev(clks[dev_clks->dt_id], dev_clks->con_id,
				dev_clks->dev_id);

	क्रम (i = 0; i < clk_num; i++) अणु
		अगर (!IS_ERR_OR_शून्य(clks[i]))
			clk_रेजिस्टर_clkdev(clks[i], __clk_get_name(clks[i]),
				"tegra-clk-debug");
	पूर्ण
पूर्ण

काष्ठा clk ** __init tegra_lookup_dt_id(पूर्णांक clk_id,
					काष्ठा tegra_clk *tegra_clk)
अणु
	अगर (tegra_clk[clk_id].present)
		वापस &clks[tegra_clk[clk_id].dt_id];
	अन्यथा
		वापस शून्य;
पूर्ण

tegra_clk_apply_init_table_func tegra_clk_apply_init_table;

अटल पूर्णांक __init tegra_घड़ीs_apply_init_table(व्योम)
अणु
	अगर (!tegra_clk_apply_init_table)
		वापस 0;

	tegra_clk_apply_init_table();

	वापस 0;
पूर्ण
arch_initcall(tegra_घड़ीs_apply_init_table);
