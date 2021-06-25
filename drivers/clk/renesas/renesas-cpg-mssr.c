<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas Clock Pulse Generator / Module Standby and Software Reset
 *
 * Copyright (C) 2015 Glider bvba
 *
 * Based on clk-mstp.c, clk-rcar-gen2.c, and clk-rcar-gen3.c
 *
 * Copyright (C) 2013 Ideas On Board SPRL
 * Copyright (C) 2015 Renesas Electronics Corp.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/renesas.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/psci.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/renesas-cpg-mssr.h>

#समावेश "renesas-cpg-mssr.h"
#समावेश "clk-div6.h"

#अगर_घोषित DEBUG
#घोषणा WARN_DEBUG(x)	WARN_ON(x)
#अन्यथा
#घोषणा WARN_DEBUG(x)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर


/*
 * Module Standby and Software Reset रेजिस्टर offets.
 *
 * If the रेजिस्टरs exist, these are valid क्रम SH-Mobile, R-Mobile,
 * R-Car Gen2, R-Car Gen3, and RZ/G1.
 * These are NOT valid क्रम R-Car Gen1 and RZ/A1!
 */

/*
 * Module Stop Status Register offsets
 */

अटल स्थिर u16 mstpsr[] = अणु
	0x030, 0x038, 0x040, 0x048, 0x04C, 0x03C, 0x1C0, 0x1C4,
	0x9A0, 0x9A4, 0x9A8, 0x9AC,
पूर्ण;

अटल स्थिर u16 mstpsr_क्रम_v3u[] = अणु
	0x2E00, 0x2E04, 0x2E08, 0x2E0C, 0x2E10, 0x2E14, 0x2E18, 0x2E1C,
	0x2E20, 0x2E24, 0x2E28, 0x2E2C, 0x2E30, 0x2E34, 0x2E38,
पूर्ण;

/*
 * System Module Stop Control Register offsets
 */

अटल स्थिर u16 smstpcr[] = अणु
	0x130, 0x134, 0x138, 0x13C, 0x140, 0x144, 0x148, 0x14C,
	0x990, 0x994, 0x998, 0x99C,
पूर्ण;

अटल स्थिर u16 mstpcr_क्रम_v3u[] = अणु
	0x2D00, 0x2D04, 0x2D08, 0x2D0C, 0x2D10, 0x2D14, 0x2D18, 0x2D1C,
	0x2D20, 0x2D24, 0x2D28, 0x2D2C, 0x2D30, 0x2D34, 0x2D38,
पूर्ण;

/*
 * Standby Control Register offsets (RZ/A)
 * Base address is FRQCR रेजिस्टर
 */

अटल स्थिर u16 stbcr[] = अणु
	0xFFFF/*dummy*/, 0x010, 0x014, 0x410, 0x414, 0x418, 0x41C, 0x420,
	0x424, 0x428, 0x42C,
पूर्ण;

/*
 * Software Reset Register offsets
 */

अटल स्थिर u16 srcr[] = अणु
	0x0A0, 0x0A8, 0x0B0, 0x0B8, 0x0BC, 0x0C4, 0x1C8, 0x1CC,
	0x920, 0x924, 0x928, 0x92C,
पूर्ण;

अटल स्थिर u16 srcr_क्रम_v3u[] = अणु
	0x2C00, 0x2C04, 0x2C08, 0x2C0C, 0x2C10, 0x2C14, 0x2C18, 0x2C1C,
	0x2C20, 0x2C24, 0x2C28, 0x2C2C, 0x2C30, 0x2C34, 0x2C38,
पूर्ण;

/* Realसमय Module Stop Control Register offsets */
#घोषणा RMSTPCR(i)	(smstpcr[i] - 0x20)

/* Modem Module Stop Control Register offsets (r8a73a4) */
#घोषणा MMSTPCR(i)	(smstpcr[i] + 0x20)

/* Software Reset Clearing Register offsets */

अटल स्थिर u16 srstclr[] = अणु
	0x940, 0x944, 0x948, 0x94C, 0x950, 0x954, 0x958, 0x95C,
	0x960, 0x964, 0x968, 0x96C,
पूर्ण;

अटल स्थिर u16 srstclr_क्रम_v3u[] = अणु
	0x2C80, 0x2C84, 0x2C88, 0x2C8C, 0x2C90, 0x2C94, 0x2C98, 0x2C9C,
	0x2CA0, 0x2CA4, 0x2CA8, 0x2CAC, 0x2CB0, 0x2CB4, 0x2CB8,
पूर्ण;

/**
 * काष्ठा cpg_mssr_priv - Clock Pulse Generator / Module Standby
 *                        and Software Reset Private Data
 *
 * @rcdev: Optional reset controller entity
 * @dev: CPG/MSSR device
 * @base: CPG/MSSR रेजिस्टर block base address
 * @reg_layout: CPG/MSSR रेजिस्टर layout
 * @rmw_lock: protects RMW रेजिस्टर accesses
 * @np: Device node in DT क्रम this CPG/MSSR module
 * @num_core_clks: Number of Core Clocks in clks[]
 * @num_mod_clks: Number of Module Clocks in clks[]
 * @last_dt_core_clk: ID of the last Core Clock exported to DT
 * @notअगरiers: Notअगरier chain to save/restore घड़ी state क्रम प्रणाली resume
 * @status_regs: Poपूर्णांकer to status रेजिस्टरs array
 * @control_regs: Poपूर्णांकer to control रेजिस्टरs array
 * @reset_regs: Poपूर्णांकer to reset रेजिस्टरs array
 * @reset_clear_regs:  Poपूर्णांकer to reset clearing रेजिस्टरs array
 * @smstpcr_saved: [].mask: Mask of SMSTPCR[] bits under our control
 *                 [].val: Saved values of SMSTPCR[]
 * @clks: Array containing all Core and Module Clocks
 */
काष्ठा cpg_mssr_priv अणु
#अगर_घोषित CONFIG_RESET_CONTROLLER
	काष्ठा reset_controller_dev rcdev;
#पूर्ण_अगर
	काष्ठा device *dev;
	व्योम __iomem *base;
	क्रमागत clk_reg_layout reg_layout;
	spinlock_t rmw_lock;
	काष्ठा device_node *np;

	अचिन्हित पूर्णांक num_core_clks;
	अचिन्हित पूर्णांक num_mod_clks;
	अचिन्हित पूर्णांक last_dt_core_clk;

	काष्ठा raw_notअगरier_head notअगरiers;
	स्थिर u16 *status_regs;
	स्थिर u16 *control_regs;
	स्थिर u16 *reset_regs;
	स्थिर u16 *reset_clear_regs;
	काष्ठा अणु
		u32 mask;
		u32 val;
	पूर्ण smstpcr_saved[ARRAY_SIZE(mstpsr_क्रम_v3u)];

	काष्ठा clk *clks[];
पूर्ण;

अटल काष्ठा cpg_mssr_priv *cpg_mssr_priv;

/**
 * काष्ठा mstp_घड़ी - MSTP gating घड़ी
 * @hw: handle between common and hardware-specअगरic पूर्णांकerfaces
 * @index: MSTP घड़ी number
 * @priv: CPG/MSSR निजी data
 */
काष्ठा mstp_घड़ी अणु
	काष्ठा clk_hw hw;
	u32 index;
	काष्ठा cpg_mssr_priv *priv;
पूर्ण;

#घोषणा to_mstp_घड़ी(_hw) container_of(_hw, काष्ठा mstp_घड़ी, hw)

अटल पूर्णांक cpg_mstp_घड़ी_endisable(काष्ठा clk_hw *hw, bool enable)
अणु
	काष्ठा mstp_घड़ी *घड़ी = to_mstp_घड़ी(hw);
	काष्ठा cpg_mssr_priv *priv = घड़ी->priv;
	अचिन्हित पूर्णांक reg = घड़ी->index / 32;
	अचिन्हित पूर्णांक bit = घड़ी->index % 32;
	काष्ठा device *dev = priv->dev;
	u32 biपंचांगask = BIT(bit);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	u32 value;

	dev_dbg(dev, "MSTP %u%02u/%pC %s\n", reg, bit, hw->clk,
		enable ? "ON" : "OFF");
	spin_lock_irqsave(&priv->rmw_lock, flags);

	अगर (priv->reg_layout == CLK_REG_LAYOUT_RZ_A) अणु
		value = पढ़ोb(priv->base + priv->control_regs[reg]);
		अगर (enable)
			value &= ~biपंचांगask;
		अन्यथा
			value |= biपंचांगask;
		ग_लिखोb(value, priv->base + priv->control_regs[reg]);

		/* dummy पढ़ो to ensure ग_लिखो has completed */
		पढ़ोb(priv->base + priv->control_regs[reg]);
		barrier_data(priv->base + priv->control_regs[reg]);
	पूर्ण अन्यथा अणु
		value = पढ़ोl(priv->base + priv->control_regs[reg]);
		अगर (enable)
			value &= ~biपंचांगask;
		अन्यथा
			value |= biपंचांगask;
		ग_लिखोl(value, priv->base + priv->control_regs[reg]);
	पूर्ण

	spin_unlock_irqrestore(&priv->rmw_lock, flags);

	अगर (!enable || priv->reg_layout == CLK_REG_LAYOUT_RZ_A)
		वापस 0;

	क्रम (i = 1000; i > 0; --i) अणु
		अगर (!(पढ़ोl(priv->base + priv->status_regs[reg]) & biपंचांगask))
			अवरोध;
		cpu_relax();
	पूर्ण

	अगर (!i) अणु
		dev_err(dev, "Failed to enable SMSTP %p[%d]\n",
			priv->base + priv->control_regs[reg], bit);
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
	काष्ठा cpg_mssr_priv *priv = घड़ी->priv;
	u32 value;

	अगर (priv->reg_layout == CLK_REG_LAYOUT_RZ_A)
		value = पढ़ोb(priv->base + priv->control_regs[घड़ी->index / 32]);
	अन्यथा
		value = पढ़ोl(priv->base + priv->status_regs[घड़ी->index / 32]);

	वापस !(value & BIT(घड़ी->index % 32));
पूर्ण

अटल स्थिर काष्ठा clk_ops cpg_mstp_घड़ी_ops = अणु
	.enable = cpg_mstp_घड़ी_enable,
	.disable = cpg_mstp_घड़ी_disable,
	.is_enabled = cpg_mstp_घड़ी_is_enabled,
पूर्ण;

अटल
काष्ठा clk *cpg_mssr_clk_src_twocell_get(काष्ठा of_phandle_args *clkspec,
					 व्योम *data)
अणु
	अचिन्हित पूर्णांक clkidx = clkspec->args[1];
	काष्ठा cpg_mssr_priv *priv = data;
	काष्ठा device *dev = priv->dev;
	अचिन्हित पूर्णांक idx;
	स्थिर अक्षर *type;
	काष्ठा clk *clk;
	पूर्णांक range_check;

	चयन (clkspec->args[0]) अणु
	हाल CPG_CORE:
		type = "core";
		अगर (clkidx > priv->last_dt_core_clk) अणु
			dev_err(dev, "Invalid %s clock index %u\n", type,
			       clkidx);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		clk = priv->clks[clkidx];
		अवरोध;

	हाल CPG_MOD:
		type = "module";
		अगर (priv->reg_layout == CLK_REG_LAYOUT_RZ_A) अणु
			idx = MOD_CLK_PACK_10(clkidx);
			range_check = 7 - (clkidx % 10);
		पूर्ण अन्यथा अणु
			idx = MOD_CLK_PACK(clkidx);
			range_check = 31 - (clkidx % 100);
		पूर्ण
		अगर (range_check < 0 || idx >= priv->num_mod_clks) अणु
			dev_err(dev, "Invalid %s clock index %u\n", type,
				clkidx);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		clk = priv->clks[priv->num_core_clks + idx];
		अवरोध;

	शेष:
		dev_err(dev, "Invalid CPG clock type %u\n", clkspec->args[0]);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (IS_ERR(clk))
		dev_err(dev, "Cannot get %s clock %u: %ld", type, clkidx,
		       PTR_ERR(clk));
	अन्यथा
		dev_dbg(dev, "clock (%u, %u) is %pC at %lu Hz\n",
			clkspec->args[0], clkspec->args[1], clk,
			clk_get_rate(clk));
	वापस clk;
पूर्ण

अटल व्योम __init cpg_mssr_रेजिस्टर_core_clk(स्थिर काष्ठा cpg_core_clk *core,
					      स्थिर काष्ठा cpg_mssr_info *info,
					      काष्ठा cpg_mssr_priv *priv)
अणु
	काष्ठा clk *clk = ERR_PTR(-ENOTSUPP), *parent;
	काष्ठा device *dev = priv->dev;
	अचिन्हित पूर्णांक id = core->id, भाग = core->भाग;
	स्थिर अक्षर *parent_name;

	WARN_DEBUG(id >= priv->num_core_clks);
	WARN_DEBUG(PTR_ERR(priv->clks[id]) != -ENOENT);

	अगर (!core->name) अणु
		/* Skip शून्यअगरied घड़ी */
		वापस;
	पूर्ण

	चयन (core->type) अणु
	हाल CLK_TYPE_IN:
		clk = of_clk_get_by_name(priv->np, core->name);
		अवरोध;

	हाल CLK_TYPE_FF:
	हाल CLK_TYPE_DIV6P1:
	हाल CLK_TYPE_DIV6_RO:
		WARN_DEBUG(core->parent >= priv->num_core_clks);
		parent = priv->clks[core->parent];
		अगर (IS_ERR(parent)) अणु
			clk = parent;
			जाओ fail;
		पूर्ण

		parent_name = __clk_get_name(parent);

		अगर (core->type == CLK_TYPE_DIV6_RO)
			/* Multiply with the DIV6 रेजिस्टर value */
			भाग *= (पढ़ोl(priv->base + core->offset) & 0x3f) + 1;

		अगर (core->type == CLK_TYPE_DIV6P1) अणु
			clk = cpg_भाग6_रेजिस्टर(core->name, 1, &parent_name,
						priv->base + core->offset,
						&priv->notअगरiers);
		पूर्ण अन्यथा अणु
			clk = clk_रेजिस्टर_fixed_factor(शून्य, core->name,
							parent_name, 0,
							core->mult, भाग);
		पूर्ण
		अवरोध;

	हाल CLK_TYPE_FR:
		clk = clk_रेजिस्टर_fixed_rate(शून्य, core->name, शून्य, 0,
					      core->mult);
		अवरोध;

	शेष:
		अगर (info->cpg_clk_रेजिस्टर)
			clk = info->cpg_clk_रेजिस्टर(dev, core, info,
						     priv->clks, priv->base,
						     &priv->notअगरiers);
		अन्यथा
			dev_err(dev, "%s has unsupported core clock type %u\n",
				core->name, core->type);
		अवरोध;
	पूर्ण

	अगर (IS_ERR_OR_शून्य(clk))
		जाओ fail;

	dev_dbg(dev, "Core clock %pC at %lu Hz\n", clk, clk_get_rate(clk));
	priv->clks[id] = clk;
	वापस;

fail:
	dev_err(dev, "Failed to register %s clock %s: %ld\n", "core",
		core->name, PTR_ERR(clk));
पूर्ण

अटल व्योम __init cpg_mssr_रेजिस्टर_mod_clk(स्थिर काष्ठा mssr_mod_clk *mod,
					     स्थिर काष्ठा cpg_mssr_info *info,
					     काष्ठा cpg_mssr_priv *priv)
अणु
	काष्ठा mstp_घड़ी *घड़ी = शून्य;
	काष्ठा device *dev = priv->dev;
	अचिन्हित पूर्णांक id = mod->id;
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा clk *parent, *clk;
	स्थिर अक्षर *parent_name;
	अचिन्हित पूर्णांक i;

	WARN_DEBUG(id < priv->num_core_clks);
	WARN_DEBUG(id >= priv->num_core_clks + priv->num_mod_clks);
	WARN_DEBUG(mod->parent >= priv->num_core_clks + priv->num_mod_clks);
	WARN_DEBUG(PTR_ERR(priv->clks[id]) != -ENOENT);

	अगर (!mod->name) अणु
		/* Skip शून्यअगरied घड़ी */
		वापस;
	पूर्ण

	parent = priv->clks[mod->parent];
	अगर (IS_ERR(parent)) अणु
		clk = parent;
		जाओ fail;
	पूर्ण

	घड़ी = kzalloc(माप(*घड़ी), GFP_KERNEL);
	अगर (!घड़ी) अणु
		clk = ERR_PTR(-ENOMEM);
		जाओ fail;
	पूर्ण

	init.name = mod->name;
	init.ops = &cpg_mstp_घड़ी_ops;
	init.flags = CLK_SET_RATE_PARENT;
	parent_name = __clk_get_name(parent);
	init.parent_names = &parent_name;
	init.num_parents = 1;

	घड़ी->index = id - priv->num_core_clks;
	घड़ी->priv = priv;
	घड़ी->hw.init = &init;

	क्रम (i = 0; i < info->num_crit_mod_clks; i++)
		अगर (id == info->crit_mod_clks[i] &&
		    cpg_mstp_घड़ी_is_enabled(&घड़ी->hw)) अणु
			dev_dbg(dev, "MSTP %s setting CLK_IS_CRITICAL\n",
				mod->name);
			init.flags |= CLK_IS_CRITICAL;
			अवरोध;
		पूर्ण

	clk = clk_रेजिस्टर(शून्य, &घड़ी->hw);
	अगर (IS_ERR(clk))
		जाओ fail;

	dev_dbg(dev, "Module clock %pC at %lu Hz\n", clk, clk_get_rate(clk));
	priv->clks[id] = clk;
	priv->smstpcr_saved[घड़ी->index / 32].mask |= BIT(घड़ी->index % 32);
	वापस;

fail:
	dev_err(dev, "Failed to register %s clock %s: %ld\n", "module",
		mod->name, PTR_ERR(clk));
	kमुक्त(घड़ी);
पूर्ण

काष्ठा cpg_mssr_clk_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	अचिन्हित पूर्णांक num_core_pm_clks;
	अचिन्हित पूर्णांक core_pm_clks[];
पूर्ण;

अटल काष्ठा cpg_mssr_clk_करोमुख्य *cpg_mssr_clk_करोमुख्य;

अटल bool cpg_mssr_is_pm_clk(स्थिर काष्ठा of_phandle_args *clkspec,
			       काष्ठा cpg_mssr_clk_करोमुख्य *pd)
अणु
	अचिन्हित पूर्णांक i;

	अगर (clkspec->np != pd->genpd.dev.of_node || clkspec->args_count != 2)
		वापस false;

	चयन (clkspec->args[0]) अणु
	हाल CPG_CORE:
		क्रम (i = 0; i < pd->num_core_pm_clks; i++)
			अगर (clkspec->args[1] == pd->core_pm_clks[i])
				वापस true;
		वापस false;

	हाल CPG_MOD:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

पूर्णांक cpg_mssr_attach_dev(काष्ठा generic_pm_करोमुख्य *unused, काष्ठा device *dev)
अणु
	काष्ठा cpg_mssr_clk_करोमुख्य *pd = cpg_mssr_clk_करोमुख्य;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा of_phandle_args clkspec;
	काष्ठा clk *clk;
	पूर्णांक i = 0;
	पूर्णांक error;

	अगर (!pd) अणु
		dev_dbg(dev, "CPG/MSSR clock domain not yet available\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	जबतक (!of_parse_phandle_with_args(np, "clocks", "#clock-cells", i,
					   &clkspec)) अणु
		अगर (cpg_mssr_is_pm_clk(&clkspec, pd))
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

व्योम cpg_mssr_detach_dev(काष्ठा generic_pm_करोमुख्य *unused, काष्ठा device *dev)
अणु
	अगर (!pm_clk_no_घड़ीs(dev))
		pm_clk_destroy(dev);
पूर्ण

अटल पूर्णांक __init cpg_mssr_add_clk_करोमुख्य(काष्ठा device *dev,
					  स्थिर अचिन्हित पूर्णांक *core_pm_clks,
					  अचिन्हित पूर्णांक num_core_pm_clks)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा generic_pm_करोमुख्य *genpd;
	काष्ठा cpg_mssr_clk_करोमुख्य *pd;
	माप_प्रकार pm_size = num_core_pm_clks * माप(core_pm_clks[0]);

	pd = devm_kzalloc(dev, माप(*pd) + pm_size, GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	pd->num_core_pm_clks = num_core_pm_clks;
	स_नकल(pd->core_pm_clks, core_pm_clks, pm_size);

	genpd = &pd->genpd;
	genpd->name = np->name;
	genpd->flags = GENPD_FLAG_PM_CLK | GENPD_FLAG_ALWAYS_ON |
		       GENPD_FLAG_ACTIVE_WAKEUP;
	genpd->attach_dev = cpg_mssr_attach_dev;
	genpd->detach_dev = cpg_mssr_detach_dev;
	pm_genpd_init(genpd, &pm_करोमुख्य_always_on_gov, false);
	cpg_mssr_clk_करोमुख्य = pd;

	of_genpd_add_provider_simple(np, genpd);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_RESET_CONTROLLER

#घोषणा rcdev_to_priv(x)	container_of(x, काष्ठा cpg_mssr_priv, rcdev)

अटल पूर्णांक cpg_mssr_reset(काष्ठा reset_controller_dev *rcdev,
			  अचिन्हित दीर्घ id)
अणु
	काष्ठा cpg_mssr_priv *priv = rcdev_to_priv(rcdev);
	अचिन्हित पूर्णांक reg = id / 32;
	अचिन्हित पूर्णांक bit = id % 32;
	u32 biपंचांगask = BIT(bit);

	dev_dbg(priv->dev, "reset %u%02u\n", reg, bit);

	/* Reset module */
	ग_लिखोl(biपंचांगask, priv->base + priv->reset_regs[reg]);

	/* Wait क्रम at least one cycle of the RCLK घड़ी (@ ca. 32 kHz) */
	udelay(35);

	/* Release module from reset state */
	ग_लिखोl(biपंचांगask, priv->base + priv->reset_clear_regs[reg]);

	वापस 0;
पूर्ण

अटल पूर्णांक cpg_mssr_निश्चित(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id)
अणु
	काष्ठा cpg_mssr_priv *priv = rcdev_to_priv(rcdev);
	अचिन्हित पूर्णांक reg = id / 32;
	अचिन्हित पूर्णांक bit = id % 32;
	u32 biपंचांगask = BIT(bit);

	dev_dbg(priv->dev, "assert %u%02u\n", reg, bit);

	ग_लिखोl(biपंचांगask, priv->base + priv->reset_regs[reg]);
	वापस 0;
पूर्ण

अटल पूर्णांक cpg_mssr_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
			     अचिन्हित दीर्घ id)
अणु
	काष्ठा cpg_mssr_priv *priv = rcdev_to_priv(rcdev);
	अचिन्हित पूर्णांक reg = id / 32;
	अचिन्हित पूर्णांक bit = id % 32;
	u32 biपंचांगask = BIT(bit);

	dev_dbg(priv->dev, "deassert %u%02u\n", reg, bit);

	ग_लिखोl(biपंचांगask, priv->base + priv->reset_clear_regs[reg]);
	वापस 0;
पूर्ण

अटल पूर्णांक cpg_mssr_status(काष्ठा reset_controller_dev *rcdev,
			   अचिन्हित दीर्घ id)
अणु
	काष्ठा cpg_mssr_priv *priv = rcdev_to_priv(rcdev);
	अचिन्हित पूर्णांक reg = id / 32;
	अचिन्हित पूर्णांक bit = id % 32;
	u32 biपंचांगask = BIT(bit);

	वापस !!(पढ़ोl(priv->base + priv->reset_regs[reg]) & biपंचांगask);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops cpg_mssr_reset_ops = अणु
	.reset = cpg_mssr_reset,
	.निश्चित = cpg_mssr_निश्चित,
	.deनिश्चित = cpg_mssr_deनिश्चित,
	.status = cpg_mssr_status,
पूर्ण;

अटल पूर्णांक cpg_mssr_reset_xlate(काष्ठा reset_controller_dev *rcdev,
				स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	काष्ठा cpg_mssr_priv *priv = rcdev_to_priv(rcdev);
	अचिन्हित पूर्णांक unpacked = reset_spec->args[0];
	अचिन्हित पूर्णांक idx = MOD_CLK_PACK(unpacked);

	अगर (unpacked % 100 > 31 || idx >= rcdev->nr_resets) अणु
		dev_err(priv->dev, "Invalid reset index %u\n", unpacked);
		वापस -EINVAL;
	पूर्ण

	वापस idx;
पूर्ण

अटल पूर्णांक cpg_mssr_reset_controller_रेजिस्टर(काष्ठा cpg_mssr_priv *priv)
अणु
	priv->rcdev.ops = &cpg_mssr_reset_ops;
	priv->rcdev.of_node = priv->dev->of_node;
	priv->rcdev.of_reset_n_cells = 1;
	priv->rcdev.of_xlate = cpg_mssr_reset_xlate;
	priv->rcdev.nr_resets = priv->num_mod_clks;
	वापस devm_reset_controller_रेजिस्टर(priv->dev, &priv->rcdev);
पूर्ण

#अन्यथा /* !CONFIG_RESET_CONTROLLER */
अटल अंतरभूत पूर्णांक cpg_mssr_reset_controller_रेजिस्टर(काष्ठा cpg_mssr_priv *priv)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_RESET_CONTROLLER */


अटल स्थिर काष्ठा of_device_id cpg_mssr_match[] = अणु
#अगर_घोषित CONFIG_CLK_R7S9210
	अणु
		.compatible = "renesas,r7s9210-cpg-mssr",
		.data = &r7s9210_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A7742
	अणु
		.compatible = "renesas,r8a7742-cpg-mssr",
		.data = &r8a7742_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A7743
	अणु
		.compatible = "renesas,r8a7743-cpg-mssr",
		.data = &r8a7743_cpg_mssr_info,
	पूर्ण,
	/* RZ/G1N is (almost) identical to RZ/G1M w.r.t. घड़ीs. */
	अणु
		.compatible = "renesas,r8a7744-cpg-mssr",
		.data = &r8a7743_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A7745
	अणु
		.compatible = "renesas,r8a7745-cpg-mssr",
		.data = &r8a7745_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A77470
	अणु
		.compatible = "renesas,r8a77470-cpg-mssr",
		.data = &r8a77470_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A774A1
	अणु
		.compatible = "renesas,r8a774a1-cpg-mssr",
		.data = &r8a774a1_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A774B1
	अणु
		.compatible = "renesas,r8a774b1-cpg-mssr",
		.data = &r8a774b1_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A774C0
	अणु
		.compatible = "renesas,r8a774c0-cpg-mssr",
		.data = &r8a774c0_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A774E1
	अणु
		.compatible = "renesas,r8a774e1-cpg-mssr",
		.data = &r8a774e1_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A7790
	अणु
		.compatible = "renesas,r8a7790-cpg-mssr",
		.data = &r8a7790_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A7791
	अणु
		.compatible = "renesas,r8a7791-cpg-mssr",
		.data = &r8a7791_cpg_mssr_info,
	पूर्ण,
	/* R-Car M2-N is (almost) identical to R-Car M2-W w.r.t. घड़ीs. */
	अणु
		.compatible = "renesas,r8a7793-cpg-mssr",
		.data = &r8a7791_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A7792
	अणु
		.compatible = "renesas,r8a7792-cpg-mssr",
		.data = &r8a7792_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A7794
	अणु
		.compatible = "renesas,r8a7794-cpg-mssr",
		.data = &r8a7794_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A7795
	अणु
		.compatible = "renesas,r8a7795-cpg-mssr",
		.data = &r8a7795_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A77960
	अणु
		.compatible = "renesas,r8a7796-cpg-mssr",
		.data = &r8a7796_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A77961
	अणु
		.compatible = "renesas,r8a77961-cpg-mssr",
		.data = &r8a7796_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A77965
	अणु
		.compatible = "renesas,r8a77965-cpg-mssr",
		.data = &r8a77965_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A77970
	अणु
		.compatible = "renesas,r8a77970-cpg-mssr",
		.data = &r8a77970_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A77980
	अणु
		.compatible = "renesas,r8a77980-cpg-mssr",
		.data = &r8a77980_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A77990
	अणु
		.compatible = "renesas,r8a77990-cpg-mssr",
		.data = &r8a77990_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A77995
	अणु
		.compatible = "renesas,r8a77995-cpg-mssr",
		.data = &r8a77995_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLK_R8A779A0
	अणु
		.compatible = "renesas,r8a779a0-cpg-mssr",
		.data = &r8a779a0_cpg_mssr_info,
	पूर्ण,
#पूर्ण_अगर
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल व्योम cpg_mssr_del_clk_provider(व्योम *data)
अणु
	of_clk_del_provider(data);
पूर्ण

#अगर defined(CONFIG_PM_SLEEP) && defined(CONFIG_ARM_PSCI_FW)
अटल पूर्णांक cpg_mssr_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा cpg_mssr_priv *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reg;

	/* This is the best we can करो to check क्रम the presence of PSCI */
	अगर (!psci_ops.cpu_suspend)
		वापस 0;

	/* Save module रेजिस्टरs with bits under our control */
	क्रम (reg = 0; reg < ARRAY_SIZE(priv->smstpcr_saved); reg++) अणु
		अगर (priv->smstpcr_saved[reg].mask)
			priv->smstpcr_saved[reg].val =
				priv->reg_layout == CLK_REG_LAYOUT_RZ_A ?
				पढ़ोb(priv->base + priv->control_regs[reg]) :
				पढ़ोl(priv->base + priv->control_regs[reg]);
	पूर्ण

	/* Save core घड़ीs */
	raw_notअगरier_call_chain(&priv->notअगरiers, PM_EVENT_SUSPEND, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक cpg_mssr_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा cpg_mssr_priv *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reg, i;
	u32 mask, oldval, newval;

	/* This is the best we can करो to check क्रम the presence of PSCI */
	अगर (!psci_ops.cpu_suspend)
		वापस 0;

	/* Restore core घड़ीs */
	raw_notअगरier_call_chain(&priv->notअगरiers, PM_EVENT_RESUME, शून्य);

	/* Restore module घड़ीs */
	क्रम (reg = 0; reg < ARRAY_SIZE(priv->smstpcr_saved); reg++) अणु
		mask = priv->smstpcr_saved[reg].mask;
		अगर (!mask)
			जारी;

		अगर (priv->reg_layout == CLK_REG_LAYOUT_RZ_A)
			oldval = पढ़ोb(priv->base + priv->control_regs[reg]);
		अन्यथा
			oldval = पढ़ोl(priv->base + priv->control_regs[reg]);
		newval = oldval & ~mask;
		newval |= priv->smstpcr_saved[reg].val & mask;
		अगर (newval == oldval)
			जारी;

		अगर (priv->reg_layout == CLK_REG_LAYOUT_RZ_A) अणु
			ग_लिखोb(newval, priv->base + priv->control_regs[reg]);
			/* dummy पढ़ो to ensure ग_लिखो has completed */
			पढ़ोb(priv->base + priv->control_regs[reg]);
			barrier_data(priv->base + priv->control_regs[reg]);
			जारी;
		पूर्ण अन्यथा
			ग_लिखोl(newval, priv->base + priv->control_regs[reg]);

		/* Wait until enabled घड़ीs are really enabled */
		mask &= ~priv->smstpcr_saved[reg].val;
		अगर (!mask)
			जारी;

		क्रम (i = 1000; i > 0; --i) अणु
			oldval = पढ़ोl(priv->base + priv->status_regs[reg]);
			अगर (!(oldval & mask))
				अवरोध;
			cpu_relax();
		पूर्ण

		अगर (!i)
			dev_warn(dev, "Failed to enable %s%u[0x%x]\n",
				 priv->reg_layout == CLK_REG_LAYOUT_RZ_A ?
				 "STB" : "SMSTP", reg, oldval & mask);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cpg_mssr_pm = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(cpg_mssr_suspend_noirq,
				      cpg_mssr_resume_noirq)
पूर्ण;
#घोषणा DEV_PM_OPS	&cpg_mssr_pm
#अन्यथा
#घोषणा DEV_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP && CONFIG_ARM_PSCI_FW */

अटल पूर्णांक __init cpg_mssr_common_init(काष्ठा device *dev,
				       काष्ठा device_node *np,
				       स्थिर काष्ठा cpg_mssr_info *info)
अणु
	काष्ठा cpg_mssr_priv *priv;
	अचिन्हित पूर्णांक nclks, i;
	पूर्णांक error;

	अगर (info->init) अणु
		error = info->init(dev);
		अगर (error)
			वापस error;
	पूर्ण

	nclks = info->num_total_core_clks + info->num_hw_mod_clks;
	priv = kzalloc(काष्ठा_size(priv, clks, nclks), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->np = np;
	priv->dev = dev;
	spin_lock_init(&priv->rmw_lock);

	priv->base = of_iomap(np, 0);
	अगर (!priv->base) अणु
		error = -ENOMEM;
		जाओ out_err;
	पूर्ण

	cpg_mssr_priv = priv;
	priv->num_core_clks = info->num_total_core_clks;
	priv->num_mod_clks = info->num_hw_mod_clks;
	priv->last_dt_core_clk = info->last_dt_core_clk;
	RAW_INIT_NOTIFIER_HEAD(&priv->notअगरiers);
	priv->reg_layout = info->reg_layout;
	अगर (priv->reg_layout == CLK_REG_LAYOUT_RCAR_GEN2_AND_GEN3) अणु
		priv->status_regs = mstpsr;
		priv->control_regs = smstpcr;
		priv->reset_regs = srcr;
		priv->reset_clear_regs = srstclr;
	पूर्ण अन्यथा अगर (priv->reg_layout == CLK_REG_LAYOUT_RZ_A) अणु
		priv->control_regs = stbcr;
	पूर्ण अन्यथा अगर (priv->reg_layout == CLK_REG_LAYOUT_RCAR_V3U) अणु
		priv->status_regs = mstpsr_क्रम_v3u;
		priv->control_regs = mstpcr_क्रम_v3u;
		priv->reset_regs = srcr_क्रम_v3u;
		priv->reset_clear_regs = srstclr_क्रम_v3u;
	पूर्ण अन्यथा अणु
		error = -EINVAL;
		जाओ out_err;
	पूर्ण

	क्रम (i = 0; i < nclks; i++)
		priv->clks[i] = ERR_PTR(-ENOENT);

	error = of_clk_add_provider(np, cpg_mssr_clk_src_twocell_get, priv);
	अगर (error)
		जाओ out_err;

	वापस 0;

out_err:
	अगर (priv->base)
		iounmap(priv->base);
	kमुक्त(priv);

	वापस error;
पूर्ण

व्योम __init cpg_mssr_early_init(काष्ठा device_node *np,
				स्थिर काष्ठा cpg_mssr_info *info)
अणु
	पूर्णांक error;
	पूर्णांक i;

	error = cpg_mssr_common_init(शून्य, np, info);
	अगर (error)
		वापस;

	क्रम (i = 0; i < info->num_early_core_clks; i++)
		cpg_mssr_रेजिस्टर_core_clk(&info->early_core_clks[i], info,
					   cpg_mssr_priv);

	क्रम (i = 0; i < info->num_early_mod_clks; i++)
		cpg_mssr_रेजिस्टर_mod_clk(&info->early_mod_clks[i], info,
					  cpg_mssr_priv);

पूर्ण

अटल पूर्णांक __init cpg_mssr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा cpg_mssr_info *info;
	काष्ठा cpg_mssr_priv *priv;
	अचिन्हित पूर्णांक i;
	पूर्णांक error;

	info = of_device_get_match_data(dev);

	अगर (!cpg_mssr_priv) अणु
		error = cpg_mssr_common_init(dev, dev->of_node, info);
		अगर (error)
			वापस error;
	पूर्ण

	priv = cpg_mssr_priv;
	priv->dev = dev;
	dev_set_drvdata(dev, priv);

	क्रम (i = 0; i < info->num_core_clks; i++)
		cpg_mssr_रेजिस्टर_core_clk(&info->core_clks[i], info, priv);

	क्रम (i = 0; i < info->num_mod_clks; i++)
		cpg_mssr_रेजिस्टर_mod_clk(&info->mod_clks[i], info, priv);

	error = devm_add_action_or_reset(dev,
					 cpg_mssr_del_clk_provider,
					 np);
	अगर (error)
		वापस error;

	error = cpg_mssr_add_clk_करोमुख्य(dev, info->core_pm_clks,
					info->num_core_pm_clks);
	अगर (error)
		वापस error;

	/* Reset Controller not supported क्रम Standby Control SoCs */
	अगर (priv->reg_layout == CLK_REG_LAYOUT_RZ_A)
		वापस 0;

	error = cpg_mssr_reset_controller_रेजिस्टर(priv);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cpg_mssr_driver = अणु
	.driver		= अणु
		.name	= "renesas-cpg-mssr",
		.of_match_table = cpg_mssr_match,
		.pm = DEV_PM_OPS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init cpg_mssr_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&cpg_mssr_driver, cpg_mssr_probe);
पूर्ण

subsys_initcall(cpg_mssr_init);

व्योम __init cpg_core_nullअगरy_range(काष्ठा cpg_core_clk *core_clks,
				   अचिन्हित पूर्णांक num_core_clks,
				   अचिन्हित पूर्णांक first_clk,
				   अचिन्हित पूर्णांक last_clk)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_core_clks; i++)
		अगर (core_clks[i].id >= first_clk &&
		    core_clks[i].id <= last_clk)
			core_clks[i].name = शून्य;
पूर्ण

व्योम __init mssr_mod_nullअगरy(काष्ठा mssr_mod_clk *mod_clks,
			     अचिन्हित पूर्णांक num_mod_clks,
			     स्थिर अचिन्हित पूर्णांक *clks, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < num_mod_clks && j < n; i++)
		अगर (mod_clks[i].id == clks[j]) अणु
			mod_clks[i].name = शून्य;
			j++;
		पूर्ण
पूर्ण

व्योम __init mssr_mod_reparent(काष्ठा mssr_mod_clk *mod_clks,
			      अचिन्हित पूर्णांक num_mod_clks,
			      स्थिर काष्ठा mssr_mod_reparent *clks,
			      अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < num_mod_clks && j < n; i++)
		अगर (mod_clks[i].id == clks[j].clk) अणु
			mod_clks[i].parent = clks[j].parent;
			j++;
		पूर्ण
पूर्ण

MODULE_DESCRIPTION("Renesas CPG/MSSR Driver");
MODULE_LICENSE("GPL v2");
