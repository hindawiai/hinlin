<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R-Car Gen3 Clock Pulse Generator
 *
 * Copyright (C) 2015-2018 Glider bvba
 * Copyright (C) 2019 Renesas Electronics Corp.
 *
 * Based on clk-rcar-gen3.c
 *
 * Copyright (C) 2015 Renesas Electronics Corp.
 */

#समावेश <linux/bug.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

#समावेश "renesas-cpg-mssr.h"
#समावेश "rcar-cpg-lib.h"
#समावेश "rcar-gen3-cpg.h"

#घोषणा CPG_PLL0CR		0x00d8
#घोषणा CPG_PLL2CR		0x002c
#घोषणा CPG_PLL4CR		0x01f4

#घोषणा CPG_RCKCR_CKSEL	BIT(15)	/* RCLK Clock Source Select */

/*
 * Z Clock & Z2 Clock
 *
 * Traits of this घड़ी:
 * prepare - clk_prepare only ensures that parents are prepared
 * enable - clk_enable only ensures that parents are enabled
 * rate - rate is adjustable.  clk->rate = (parent->rate * mult / 32 ) / 2
 * parent - fixed parent.  No clk_set_parent support
 */
#घोषणा CPG_FRQCRB			0x00000004
#घोषणा CPG_FRQCRB_KICK			BIT(31)
#घोषणा CPG_FRQCRC			0x000000e0

काष्ठा cpg_z_clk अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
	व्योम __iomem *kick_reg;
	अचिन्हित दीर्घ mask;
	अचिन्हित पूर्णांक fixed_भाग;
पूर्ण;

#घोषणा to_z_clk(_hw)	container_of(_hw, काष्ठा cpg_z_clk, hw)

अटल अचिन्हित दीर्घ cpg_z_clk_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा cpg_z_clk *zclk = to_z_clk(hw);
	अचिन्हित पूर्णांक mult;
	u32 val;

	val = पढ़ोl(zclk->reg) & zclk->mask;
	mult = 32 - (val >> __ffs(zclk->mask));

	वापस DIV_ROUND_CLOSEST_ULL((u64)parent_rate * mult,
				     32 * zclk->fixed_भाग);
पूर्ण

अटल पूर्णांक cpg_z_clk_determine_rate(काष्ठा clk_hw *hw,
				    काष्ठा clk_rate_request *req)
अणु
	काष्ठा cpg_z_clk *zclk = to_z_clk(hw);
	अचिन्हित पूर्णांक min_mult, max_mult, mult;
	अचिन्हित दीर्घ prate;

	prate = req->best_parent_rate / zclk->fixed_भाग;
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
	अचिन्हित पूर्णांक i;

	mult = DIV64_U64_ROUND_CLOSEST(rate * 32ULL * zclk->fixed_भाग,
				       parent_rate);
	mult = clamp(mult, 1U, 32U);

	अगर (पढ़ोl(zclk->kick_reg) & CPG_FRQCRB_KICK)
		वापस -EBUSY;

	cpg_reg_modअगरy(zclk->reg, zclk->mask,
		       ((32 - mult) << __ffs(zclk->mask)) & zclk->mask);

	/*
	 * Set KICK bit in FRQCRB to update hardware setting and रुको क्रम
	 * घड़ी change completion.
	 */
	cpg_reg_modअगरy(zclk->kick_reg, 0, CPG_FRQCRB_KICK);

	/*
	 * Note: There is no HW inक्रमmation about the worst हाल latency.
	 *
	 * Using experimental measurements, it seems that no more than
	 * ~10 iterations are needed, independently of the CPU rate.
	 * Since this value might be dependent of बाह्यal xtal rate, pll1
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
					      व्योम __iomem *reg,
					      अचिन्हित पूर्णांक भाग,
					      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा cpg_z_clk *zclk;
	काष्ठा clk *clk;

	zclk = kzalloc(माप(*zclk), GFP_KERNEL);
	अगर (!zclk)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &cpg_z_clk_ops;
	init.flags = 0;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	zclk->reg = reg + CPG_FRQCRC;
	zclk->kick_reg = reg + CPG_FRQCRB;
	zclk->hw.init = &init;
	zclk->mask = GENMASK(offset + 4, offset);
	zclk->fixed_भाग = भाग; /* PLLVCO x 1/भाग x SYS-CPU भागider */

	clk = clk_रेजिस्टर(शून्य, &zclk->hw);
	अगर (IS_ERR(clk))
		kमुक्त(zclk);

	वापस clk;
पूर्ण

काष्ठा rpc_घड़ी अणु
	काष्ठा clk_भागider भाग;
	काष्ठा clk_gate gate;
	/*
	 * One notअगरier covers both RPC and RPCD2 घड़ीs as they are both
	 * controlled by the same RPCCKCR रेजिस्टर...
	 */
	काष्ठा cpg_simple_notअगरier csn;
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable cpg_rpcsrc_भाग_प्रकारable[] = अणु
	अणु 2, 5 पूर्ण, अणु 3, 6 पूर्ण, अणु 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable cpg_rpc_भाग_प्रकारable[] = अणु
	अणु 1, 2 पूर्ण, अणु 3, 4 पूर्ण, अणु 5, 6 पूर्ण, अणु 7, 8 पूर्ण, अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा clk * __init cpg_rpc_clk_रेजिस्टर(स्थिर अक्षर *name,
	व्योम __iomem *base, स्थिर अक्षर *parent_name,
	काष्ठा raw_notअगरier_head *notअगरiers)
अणु
	काष्ठा rpc_घड़ी *rpc;
	काष्ठा clk *clk;

	rpc = kzalloc(माप(*rpc), GFP_KERNEL);
	अगर (!rpc)
		वापस ERR_PTR(-ENOMEM);

	rpc->भाग.reg = base + CPG_RPCCKCR;
	rpc->भाग.width = 3;
	rpc->भाग.table = cpg_rpc_भाग_प्रकारable;
	rpc->भाग.lock = &cpg_lock;

	rpc->gate.reg = base + CPG_RPCCKCR;
	rpc->gate.bit_idx = 8;
	rpc->gate.flags = CLK_GATE_SET_TO_DISABLE;
	rpc->gate.lock = &cpg_lock;

	rpc->csn.reg = base + CPG_RPCCKCR;

	clk = clk_रेजिस्टर_composite(शून्य, name, &parent_name, 1, शून्य, शून्य,
				     &rpc->भाग.hw,  &clk_भागider_ops,
				     &rpc->gate.hw, &clk_gate_ops,
				     CLK_SET_RATE_PARENT);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(rpc);
		वापस clk;
	पूर्ण

	cpg_simple_notअगरier_रेजिस्टर(notअगरiers, &rpc->csn);
	वापस clk;
पूर्ण

काष्ठा rpcd2_घड़ी अणु
	काष्ठा clk_fixed_factor fixed;
	काष्ठा clk_gate gate;
पूर्ण;

अटल काष्ठा clk * __init cpg_rpcd2_clk_रेजिस्टर(स्थिर अक्षर *name,
						  व्योम __iomem *base,
						  स्थिर अक्षर *parent_name)
अणु
	काष्ठा rpcd2_घड़ी *rpcd2;
	काष्ठा clk *clk;

	rpcd2 = kzalloc(माप(*rpcd2), GFP_KERNEL);
	अगर (!rpcd2)
		वापस ERR_PTR(-ENOMEM);

	rpcd2->fixed.mult = 1;
	rpcd2->fixed.भाग = 2;

	rpcd2->gate.reg = base + CPG_RPCCKCR;
	rpcd2->gate.bit_idx = 9;
	rpcd2->gate.flags = CLK_GATE_SET_TO_DISABLE;
	rpcd2->gate.lock = &cpg_lock;

	clk = clk_रेजिस्टर_composite(शून्य, name, &parent_name, 1, शून्य, शून्य,
				     &rpcd2->fixed.hw, &clk_fixed_factor_ops,
				     &rpcd2->gate.hw, &clk_gate_ops,
				     CLK_SET_RATE_PARENT);
	अगर (IS_ERR(clk))
		kमुक्त(rpcd2);

	वापस clk;
पूर्ण


अटल स्थिर काष्ठा rcar_gen3_cpg_pll_config *cpg_pll_config __initdata;
अटल अचिन्हित पूर्णांक cpg_clk_extalr __initdata;
अटल u32 cpg_mode __initdata;
अटल u32 cpg_quirks __initdata;

#घोषणा PLL_ERRATA	BIT(0)		/* Missing PLL0/2/4 post-भागider */
#घोषणा RCKCR_CKSEL	BIT(1)		/* Manual RCLK parent selection */
#घोषणा SD_SKIP_FIRST	BIT(2)		/* Skip first घड़ी in SD table */


अटल स्थिर काष्ठा soc_device_attribute cpg_quirks_match[] __initस्थिर = अणु
	अणु
		.soc_id = "r8a7795", .revision = "ES1.0",
		.data = (व्योम *)(PLL_ERRATA | RCKCR_CKSEL | SD_SKIP_FIRST),
	पूर्ण,
	अणु
		.soc_id = "r8a7795", .revision = "ES1.*",
		.data = (व्योम *)(RCKCR_CKSEL | SD_SKIP_FIRST),
	पूर्ण,
	अणु
		.soc_id = "r8a7795", .revision = "ES2.0",
		.data = (व्योम *)SD_SKIP_FIRST,
	पूर्ण,
	अणु
		.soc_id = "r8a7796", .revision = "ES1.0",
		.data = (व्योम *)(RCKCR_CKSEL | SD_SKIP_FIRST),
	पूर्ण,
	अणु
		.soc_id = "r8a7796", .revision = "ES1.1",
		.data = (व्योम *)SD_SKIP_FIRST,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

काष्ठा clk * __init rcar_gen3_cpg_clk_रेजिस्टर(काष्ठा device *dev,
	स्थिर काष्ठा cpg_core_clk *core, स्थिर काष्ठा cpg_mssr_info *info,
	काष्ठा clk **clks, व्योम __iomem *base,
	काष्ठा raw_notअगरier_head *notअगरiers)
अणु
	स्थिर काष्ठा clk *parent;
	अचिन्हित पूर्णांक mult = 1;
	अचिन्हित पूर्णांक भाग = 1;
	u32 value;

	parent = clks[core->parent & 0xffff];	/* some types use high bits */
	अगर (IS_ERR(parent))
		वापस ERR_CAST(parent);

	चयन (core->type) अणु
	हाल CLK_TYPE_GEN3_MAIN:
		भाग = cpg_pll_config->extal_भाग;
		अवरोध;

	हाल CLK_TYPE_GEN3_PLL0:
		/*
		 * PLL0 is a configurable multiplier घड़ी. Register it as a
		 * fixed factor घड़ी क्रम now as there's no generic multiplier
		 * घड़ी implementation and we currently have no need to change
		 * the multiplier value.
		 */
		value = पढ़ोl(base + CPG_PLL0CR);
		mult = (((value >> 24) & 0x7f) + 1) * 2;
		अगर (cpg_quirks & PLL_ERRATA)
			mult *= 2;
		अवरोध;

	हाल CLK_TYPE_GEN3_PLL1:
		mult = cpg_pll_config->pll1_mult;
		भाग = cpg_pll_config->pll1_भाग;
		अवरोध;

	हाल CLK_TYPE_GEN3_PLL2:
		/*
		 * PLL2 is a configurable multiplier घड़ी. Register it as a
		 * fixed factor घड़ी क्रम now as there's no generic multiplier
		 * घड़ी implementation and we currently have no need to change
		 * the multiplier value.
		 */
		value = पढ़ोl(base + CPG_PLL2CR);
		mult = (((value >> 24) & 0x7f) + 1) * 2;
		अगर (cpg_quirks & PLL_ERRATA)
			mult *= 2;
		अवरोध;

	हाल CLK_TYPE_GEN3_PLL3:
		mult = cpg_pll_config->pll3_mult;
		भाग = cpg_pll_config->pll3_भाग;
		अवरोध;

	हाल CLK_TYPE_GEN3_PLL4:
		/*
		 * PLL4 is a configurable multiplier घड़ी. Register it as a
		 * fixed factor घड़ी क्रम now as there's no generic multiplier
		 * घड़ी implementation and we currently have no need to change
		 * the multiplier value.
		 */
		value = पढ़ोl(base + CPG_PLL4CR);
		mult = (((value >> 24) & 0x7f) + 1) * 2;
		अगर (cpg_quirks & PLL_ERRATA)
			mult *= 2;
		अवरोध;

	हाल CLK_TYPE_GEN3_SD:
		वापस cpg_sd_clk_रेजिस्टर(core->name, base, core->offset,
					   __clk_get_name(parent), notअगरiers,
					   cpg_quirks & SD_SKIP_FIRST);

	हाल CLK_TYPE_GEN3_R:
		अगर (cpg_quirks & RCKCR_CKSEL) अणु
			काष्ठा cpg_simple_notअगरier *csn;

			csn = kzalloc(माप(*csn), GFP_KERNEL);
			अगर (!csn)
				वापस ERR_PTR(-ENOMEM);

			csn->reg = base + CPG_RCKCR;

			/*
			 * RINT is शेष.
			 * Only अगर EXTALR is populated, we चयन to it.
			 */
			value = पढ़ोl(csn->reg) & 0x3f;

			अगर (clk_get_rate(clks[cpg_clk_extalr])) अणु
				parent = clks[cpg_clk_extalr];
				value |= CPG_RCKCR_CKSEL;
			पूर्ण

			ग_लिखोl(value, csn->reg);
			cpg_simple_notअगरier_रेजिस्टर(notअगरiers, csn);
			अवरोध;
		पूर्ण

		/* Select parent घड़ी of RCLK by MD28 */
		अगर (cpg_mode & BIT(28))
			parent = clks[cpg_clk_extalr];
		अवरोध;

	हाल CLK_TYPE_GEN3_MDSEL:
		/*
		 * Clock selectable between two parents and two fixed भागiders
		 * using a mode pin
		 */
		अगर (cpg_mode & BIT(core->offset)) अणु
			भाग = core->भाग & 0xffff;
		पूर्ण अन्यथा अणु
			parent = clks[core->parent >> 16];
			अगर (IS_ERR(parent))
				वापस ERR_CAST(parent);
			भाग = core->भाग >> 16;
		पूर्ण
		mult = 1;
		अवरोध;

	हाल CLK_TYPE_GEN3_Z:
		वापस cpg_z_clk_रेजिस्टर(core->name, __clk_get_name(parent),
					  base, core->भाग, core->offset);

	हाल CLK_TYPE_GEN3_OSC:
		/*
		 * Clock combining OSC EXTAL preभागider and a fixed भागider
		 */
		भाग = cpg_pll_config->osc_preभाग * core->भाग;
		अवरोध;

	हाल CLK_TYPE_GEN3_RCKSEL:
		/*
		 * Clock selectable between two parents and two fixed भागiders
		 * using RCKCR.CKSEL
		 */
		अगर (पढ़ोl(base + CPG_RCKCR) & CPG_RCKCR_CKSEL) अणु
			भाग = core->भाग & 0xffff;
		पूर्ण अन्यथा अणु
			parent = clks[core->parent >> 16];
			अगर (IS_ERR(parent))
				वापस ERR_CAST(parent);
			भाग = core->भाग >> 16;
		पूर्ण
		अवरोध;

	हाल CLK_TYPE_GEN3_RPCSRC:
		वापस clk_रेजिस्टर_भागider_table(शून्य, core->name,
						  __clk_get_name(parent), 0,
						  base + CPG_RPCCKCR, 3, 2, 0,
						  cpg_rpcsrc_भाग_प्रकारable,
						  &cpg_lock);

	हाल CLK_TYPE_GEN3_E3_RPCSRC:
		/*
		 * Register RPCSRC as fixed factor घड़ी based on the
		 * MD[4:1] pins and CPG_RPCCKCR[4:3] रेजिस्टर value क्रम
		 * which has been set prior to booting the kernel.
		 */
		value = (पढ़ोl(base + CPG_RPCCKCR) & GENMASK(4, 3)) >> 3;

		चयन (value) अणु
		हाल 0:
			भाग = 5;
			अवरोध;
		हाल 1:
			भाग = 3;
			अवरोध;
		हाल 2:
			parent = clks[core->parent >> 16];
			अगर (IS_ERR(parent))
				वापस ERR_CAST(parent);
			भाग = core->भाग;
			अवरोध;
		हाल 3:
		शेष:
			भाग = 2;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल CLK_TYPE_GEN3_RPC:
		वापस cpg_rpc_clk_रेजिस्टर(core->name, base,
					    __clk_get_name(parent), notअगरiers);

	हाल CLK_TYPE_GEN3_RPCD2:
		वापस cpg_rpcd2_clk_रेजिस्टर(core->name, base,
					      __clk_get_name(parent));

	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस clk_रेजिस्टर_fixed_factor(शून्य, core->name,
					 __clk_get_name(parent), 0, mult, भाग);
पूर्ण

पूर्णांक __init rcar_gen3_cpg_init(स्थिर काष्ठा rcar_gen3_cpg_pll_config *config,
			      अचिन्हित पूर्णांक clk_extalr, u32 mode)
अणु
	स्थिर काष्ठा soc_device_attribute *attr;

	cpg_pll_config = config;
	cpg_clk_extalr = clk_extalr;
	cpg_mode = mode;
	attr = soc_device_match(cpg_quirks_match);
	अगर (attr)
		cpg_quirks = (uपूर्णांकptr_t)attr->data;
	pr_debug("%s: mode = 0x%x quirks = 0x%x\n", __func__, mode, cpg_quirks);

	spin_lock_init(&cpg_lock);

	वापस 0;
पूर्ण
