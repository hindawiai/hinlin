<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R-Car Gen2 Clock Pulse Generator
 *
 * Copyright (C) 2016 Cogent Embedded Inc.
 */

#समावेश <linux/bug.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

#समावेश "renesas-cpg-mssr.h"
#समावेश "rcar-gen2-cpg.h"

#घोषणा CPG_FRQCRB		0x0004
#घोषणा CPG_FRQCRB_KICK		BIT(31)
#घोषणा CPG_SDCKCR		0x0074
#घोषणा CPG_PLL0CR		0x00d8
#घोषणा CPG_PLL0CR_STC_SHIFT	24
#घोषणा CPG_PLL0CR_STC_MASK	(0x7f << CPG_PLL0CR_STC_SHIFT)
#घोषणा CPG_FRQCRC		0x00e0
#घोषणा CPG_FRQCRC_ZFC_SHIFT	8
#घोषणा CPG_FRQCRC_ZFC_MASK	(0x1f << CPG_FRQCRC_ZFC_SHIFT)
#घोषणा CPG_ADSPCKCR		0x025c
#घोषणा CPG_RCANCKCR		0x0270

अटल spinlock_t cpg_lock;

/*
 * Z Clock
 *
 * Traits of this घड़ी:
 * prepare - clk_prepare only ensures that parents are prepared
 * enable - clk_enable only ensures that parents are enabled
 * rate - rate is adjustable.  clk->rate = parent->rate * mult / 32
 * parent - fixed parent.  No clk_set_parent support
 */

काष्ठा cpg_z_clk अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
	व्योम __iomem *kick_reg;
पूर्ण;

#घोषणा to_z_clk(_hw)	container_of(_hw, काष्ठा cpg_z_clk, hw)

अटल अचिन्हित दीर्घ cpg_z_clk_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा cpg_z_clk *zclk = to_z_clk(hw);
	अचिन्हित पूर्णांक mult;
	अचिन्हित पूर्णांक val;

	val = (पढ़ोl(zclk->reg) & CPG_FRQCRC_ZFC_MASK) >> CPG_FRQCRC_ZFC_SHIFT;
	mult = 32 - val;

	वापस भाग_u64((u64)parent_rate * mult, 32);
पूर्ण

अटल पूर्णांक cpg_z_clk_determine_rate(काष्ठा clk_hw *hw,
				    काष्ठा clk_rate_request *req)
अणु
	अचिन्हित दीर्घ prate = req->best_parent_rate;
	अचिन्हित पूर्णांक min_mult, max_mult, mult;

	min_mult = max(भाग64_ul(req->min_rate * 32ULL, prate), 1ULL);
	max_mult = min(भाग64_ul(req->max_rate * 32ULL, prate), 32ULL);
	अगर (max_mult < min_mult)
		वापस -EINVAL;

	mult = भाग64_ul(req->rate * 32ULL, prate);
	mult = clamp(mult, min_mult, max_mult);

	req->rate = भाग_u64((u64)prate * mult, 32);
	वापस 0;
पूर्ण

अटल पूर्णांक cpg_z_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा cpg_z_clk *zclk = to_z_clk(hw);
	अचिन्हित पूर्णांक mult;
	u32 val, kick;
	अचिन्हित पूर्णांक i;

	mult = भाग64_ul(rate * 32ULL, parent_rate);
	mult = clamp(mult, 1U, 32U);

	अगर (पढ़ोl(zclk->kick_reg) & CPG_FRQCRB_KICK)
		वापस -EBUSY;

	val = पढ़ोl(zclk->reg);
	val &= ~CPG_FRQCRC_ZFC_MASK;
	val |= (32 - mult) << CPG_FRQCRC_ZFC_SHIFT;
	ग_लिखोl(val, zclk->reg);

	/*
	 * Set KICK bit in FRQCRB to update hardware setting and रुको क्रम
	 * घड़ी change completion.
	 */
	kick = पढ़ोl(zclk->kick_reg);
	kick |= CPG_FRQCRB_KICK;
	ग_लिखोl(kick, zclk->kick_reg);

	/*
	 * Note: There is no HW inक्रमmation about the worst हाल latency.
	 *
	 * Using experimental measurements, it seems that no more than
	 * ~10 iterations are needed, independently of the CPU rate.
	 * Since this value might be dependent on बाह्यal xtal rate, pll1
	 * rate or even the other emulation घड़ीs rate, use 1000 as a
	 * "super" safe value.
	 */
	क्रम (i = 1000; i; i--) अणु
		अगर (!(पढ़ोl(zclk->kick_reg) & CPG_FRQCRB_KICK))
			वापस 0;

		cpu_relax();
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल स्थिर काष्ठा clk_ops cpg_z_clk_ops = अणु
	.recalc_rate = cpg_z_clk_recalc_rate,
	.determine_rate = cpg_z_clk_determine_rate,
	.set_rate = cpg_z_clk_set_rate,
पूर्ण;

अटल काष्ठा clk * __init cpg_z_clk_रेजिस्टर(स्थिर अक्षर *name,
					      स्थिर अक्षर *parent_name,
					      व्योम __iomem *base)
अणु
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा cpg_z_clk *zclk;
	काष्ठा clk *clk;

	zclk = kzalloc(माप(*zclk), GFP_KERNEL);
	अगर (!zclk)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &cpg_z_clk_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	zclk->reg = base + CPG_FRQCRC;
	zclk->kick_reg = base + CPG_FRQCRB;
	zclk->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &zclk->hw);
	अगर (IS_ERR(clk))
		kमुक्त(zclk);

	वापस clk;
पूर्ण

अटल काष्ठा clk * __init cpg_rcan_clk_रेजिस्टर(स्थिर अक्षर *name,
						 स्थिर अक्षर *parent_name,
						 व्योम __iomem *base)
अणु
	काष्ठा clk_fixed_factor *fixed;
	काष्ठा clk_gate *gate;
	काष्ठा clk *clk;

	fixed = kzalloc(माप(*fixed), GFP_KERNEL);
	अगर (!fixed)
		वापस ERR_PTR(-ENOMEM);

	fixed->mult = 1;
	fixed->भाग = 6;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate) अणु
		kमुक्त(fixed);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	gate->reg = base + CPG_RCANCKCR;
	gate->bit_idx = 8;
	gate->flags = CLK_GATE_SET_TO_DISABLE;
	gate->lock = &cpg_lock;

	clk = clk_रेजिस्टर_composite(शून्य, name, &parent_name, 1, शून्य, शून्य,
				     &fixed->hw, &clk_fixed_factor_ops,
				     &gate->hw, &clk_gate_ops, 0);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(gate);
		kमुक्त(fixed);
	पूर्ण

	वापस clk;
पूर्ण

/* ADSP भागisors */
अटल स्थिर काष्ठा clk_भाग_प्रकारable cpg_adsp_भाग_प्रकारable[] = अणु
	अणु  1,  3 पूर्ण, अणु  2,  4 पूर्ण, अणु  3,  6 पूर्ण, अणु  4,  8 पूर्ण,
	अणु  5, 12 पूर्ण, अणु  6, 16 पूर्ण, अणु  7, 18 पूर्ण, अणु  8, 24 पूर्ण,
	अणु 10, 36 पूर्ण, अणु 11, 48 पूर्ण, अणु  0,  0 पूर्ण,
पूर्ण;

अटल काष्ठा clk * __init cpg_adsp_clk_रेजिस्टर(स्थिर अक्षर *name,
						 स्थिर अक्षर *parent_name,
						 व्योम __iomem *base)
अणु
	काष्ठा clk_भागider *भाग;
	काष्ठा clk_gate *gate;
	काष्ठा clk *clk;

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	भाग->reg = base + CPG_ADSPCKCR;
	भाग->width = 4;
	भाग->table = cpg_adsp_भाग_प्रकारable;
	भाग->lock = &cpg_lock;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate) अणु
		kमुक्त(भाग);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	gate->reg = base + CPG_ADSPCKCR;
	gate->bit_idx = 8;
	gate->flags = CLK_GATE_SET_TO_DISABLE;
	gate->lock = &cpg_lock;

	clk = clk_रेजिस्टर_composite(शून्य, name, &parent_name, 1, शून्य, शून्य,
				     &भाग->hw, &clk_भागider_ops,
				     &gate->hw, &clk_gate_ops, 0);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(gate);
		kमुक्त(भाग);
	पूर्ण

	वापस clk;
पूर्ण

/* SDHI भागisors */
अटल स्थिर काष्ठा clk_भाग_प्रकारable cpg_sdh_भाग_प्रकारable[] = अणु
	अणु  0,  2 पूर्ण, अणु  1,  3 पूर्ण, अणु  2,  4 पूर्ण, अणु  3,  6 पूर्ण,
	अणु  4,  8 पूर्ण, अणु  5, 12 पूर्ण, अणु  6, 16 पूर्ण, अणु  7, 18 पूर्ण,
	अणु  8, 24 पूर्ण, अणु 10, 36 पूर्ण, अणु 11, 48 पूर्ण, अणु  0,  0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable cpg_sd01_भाग_प्रकारable[] = अणु
	अणु  4,  8 पूर्ण, अणु  5, 12 पूर्ण, अणु  6, 16 पूर्ण, अणु  7, 18 पूर्ण,
	अणु  8, 24 पूर्ण, अणु 10, 36 पूर्ण, अणु 11, 48 पूर्ण, अणु 12, 10 पूर्ण,
	अणु  0,  0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rcar_gen2_cpg_pll_config *cpg_pll_config __initdata;
अटल अचिन्हित पूर्णांक cpg_pll0_भाग __initdata;
अटल u32 cpg_mode __initdata;
अटल u32 cpg_quirks __initdata;

#घोषणा SD_SKIP_FIRST	BIT(0)		/* Skip first घड़ी in SD table */

अटल स्थिर काष्ठा soc_device_attribute cpg_quirks_match[] __initस्थिर = अणु
	अणु
		.soc_id = "r8a77470",
		.data = (व्योम *)SD_SKIP_FIRST,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

काष्ठा clk * __init rcar_gen2_cpg_clk_रेजिस्टर(काष्ठा device *dev,
	स्थिर काष्ठा cpg_core_clk *core, स्थिर काष्ठा cpg_mssr_info *info,
	काष्ठा clk **clks, व्योम __iomem *base,
	काष्ठा raw_notअगरier_head *notअगरiers)
अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *table = शून्य;
	स्थिर काष्ठा clk *parent;
	स्थिर अक्षर *parent_name;
	अचिन्हित पूर्णांक mult = 1;
	अचिन्हित पूर्णांक भाग = 1;
	अचिन्हित पूर्णांक shअगरt;

	parent = clks[core->parent];
	अगर (IS_ERR(parent))
		वापस ERR_CAST(parent);

	parent_name = __clk_get_name(parent);

	चयन (core->type) अणु
	/* R-Car Gen2 */
	हाल CLK_TYPE_GEN2_MAIN:
		भाग = cpg_pll_config->extal_भाग;
		अवरोध;

	हाल CLK_TYPE_GEN2_PLL0:
		/*
		 * PLL0 is a  configurable multiplier घड़ी except on R-Car
		 * V2H/E2. Register the PLL0 घड़ी as a fixed factor घड़ी क्रम
		 * now as there's no generic multiplier घड़ी implementation and
		 * we  currently  have no need to change  the multiplier value.
		 */
		mult = cpg_pll_config->pll0_mult;
		भाग  = cpg_pll0_भाग;
		अगर (!mult) अणु
			u32 pll0cr = पढ़ोl(base + CPG_PLL0CR);

			mult = (((pll0cr & CPG_PLL0CR_STC_MASK) >>
				 CPG_PLL0CR_STC_SHIFT) + 1) * 2;
		पूर्ण
		अवरोध;

	हाल CLK_TYPE_GEN2_PLL1:
		mult = cpg_pll_config->pll1_mult / 2;
		अवरोध;

	हाल CLK_TYPE_GEN2_PLL3:
		mult = cpg_pll_config->pll3_mult;
		अवरोध;

	हाल CLK_TYPE_GEN2_Z:
		वापस cpg_z_clk_रेजिस्टर(core->name, parent_name, base);

	हाल CLK_TYPE_GEN2_LB:
		भाग = cpg_mode & BIT(18) ? 36 : 24;
		अवरोध;

	हाल CLK_TYPE_GEN2_ADSP:
		वापस cpg_adsp_clk_रेजिस्टर(core->name, parent_name, base);

	हाल CLK_TYPE_GEN2_SDH:
		table = cpg_sdh_भाग_प्रकारable;
		shअगरt = 8;
		अवरोध;

	हाल CLK_TYPE_GEN2_SD0:
		table = cpg_sd01_भाग_प्रकारable;
		अगर (cpg_quirks & SD_SKIP_FIRST)
			table++;

		shअगरt = 4;
		अवरोध;

	हाल CLK_TYPE_GEN2_SD1:
		table = cpg_sd01_भाग_प्रकारable;
		अगर (cpg_quirks & SD_SKIP_FIRST)
			table++;

		shअगरt = 0;
		अवरोध;

	हाल CLK_TYPE_GEN2_QSPI:
		भाग = (cpg_mode & (BIT(3) | BIT(2) | BIT(1))) == BIT(2) ?
		      8 : 10;
		अवरोध;

	हाल CLK_TYPE_GEN2_RCAN:
		वापस cpg_rcan_clk_रेजिस्टर(core->name, parent_name, base);

	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!table)
		वापस clk_रेजिस्टर_fixed_factor(शून्य, core->name, parent_name,
						 0, mult, भाग);
	अन्यथा
		वापस clk_रेजिस्टर_भागider_table(शून्य, core->name,
						  parent_name, 0,
						  base + CPG_SDCKCR, shअगरt, 4,
						  0, table, &cpg_lock);
पूर्ण

पूर्णांक __init rcar_gen2_cpg_init(स्थिर काष्ठा rcar_gen2_cpg_pll_config *config,
			      अचिन्हित पूर्णांक pll0_भाग, u32 mode)
अणु
	स्थिर काष्ठा soc_device_attribute *attr;

	cpg_pll_config = config;
	cpg_pll0_भाग = pll0_भाग;
	cpg_mode = mode;
	attr = soc_device_match(cpg_quirks_match);
	अगर (attr)
		cpg_quirks = (uपूर्णांकptr_t)attr->data;
	pr_debug("%s: mode = 0x%x quirks = 0x%x\n", __func__, mode, cpg_quirks);

	spin_lock_init(&cpg_lock);

	वापस 0;
पूर्ण
