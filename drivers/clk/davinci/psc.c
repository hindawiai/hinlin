<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Clock driver क्रम TI Davinci PSC controllers
 *
 * Copyright (C) 2017 David Lechner <david@lechnology.com>
 *
 * Based on: drivers/clk/keystone/gate.c
 * Copyright (C) 2013 Texas Instruments.
 *	Murali Karicheri <m-karicheri2@ti.com>
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * And: arch/arm/mach-davinci/psc.c
 * Copyright (C) 2006 Texas Instruments.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk/davinci.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/err.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "psc.h"

/* PSC रेजिस्टर offsets */
#घोषणा EPCPR			0x070
#घोषणा PTCMD			0x120
#घोषणा PTSTAT			0x128
#घोषणा PDSTAT(n)		(0x200 + 4 * (n))
#घोषणा PDCTL(n)		(0x300 + 4 * (n))
#घोषणा MDSTAT(n)		(0x800 + 4 * (n))
#घोषणा MDCTL(n)		(0xa00 + 4 * (n))

/* PSC module states */
क्रमागत davinci_lpsc_state अणु
	LPSC_STATE_SWRSTDISABLE	= 0,
	LPSC_STATE_SYNCRST	= 1,
	LPSC_STATE_DISABLE	= 2,
	LPSC_STATE_ENABLE	= 3,
पूर्ण;

#घोषणा MDSTAT_STATE_MASK	GENMASK(5, 0)
#घोषणा MDSTAT_MCKOUT		BIT(12)
#घोषणा PDSTAT_STATE_MASK	GENMASK(4, 0)
#घोषणा MDCTL_FORCE		BIT(31)
#घोषणा MDCTL_LRESET		BIT(8)
#घोषणा PDCTL_EPCGOOD		BIT(8)
#घोषणा PDCTL_NEXT		BIT(0)

काष्ठा davinci_psc_data अणु
	काष्ठा clk_onecell_data clk_data;
	काष्ठा genpd_onecell_data pm_data;
	काष्ठा reset_controller_dev rcdev;
पूर्ण;

/**
 * काष्ठा davinci_lpsc_clk - LPSC घड़ी काष्ठाure
 * @dev: the device that provides this LPSC or शून्य
 * @hw: clk_hw क्रम the LPSC
 * @pm_करोमुख्य: घातer करोमुख्य क्रम the LPSC
 * @genpd_clk: घड़ी reference owned by @pm_करोमुख्य
 * @regmap: PSC MMIO region
 * @md: Module करोमुख्य (LPSC module id)
 * @pd: Power करोमुख्य
 * @flags: LPSC_* quirk flags
 */
काष्ठा davinci_lpsc_clk अणु
	काष्ठा device *dev;
	काष्ठा clk_hw hw;
	काष्ठा generic_pm_करोमुख्य pm_करोमुख्य;
	काष्ठा clk *genpd_clk;
	काष्ठा regmap *regmap;
	u32 md;
	u32 pd;
	u32 flags;
पूर्ण;

#घोषणा to_davinci_psc_data(x) container_of(x, काष्ठा davinci_psc_data, x)
#घोषणा to_davinci_lpsc_clk(x) container_of(x, काष्ठा davinci_lpsc_clk, x)

/**
 * best_dev_name - get the "best" device name.
 * @dev: the device
 *
 * Returns the device tree compatible name अगर the device has a DT node,
 * otherwise वापस the device name. This is मुख्यly needed because clkdev
 * lookups are limited to 20 अक्षरs क्रम dev_id and when using device tree,
 * dev_name(dev) is much दीर्घer than that.
 */
अटल अंतरभूत स्थिर अक्षर *best_dev_name(काष्ठा device *dev)
अणु
	स्थिर अक्षर *compatible;

	अगर (!of_property_पढ़ो_string(dev->of_node, "compatible", &compatible))
		वापस compatible;

	वापस dev_name(dev);
पूर्ण

अटल व्योम davinci_lpsc_config(काष्ठा davinci_lpsc_clk *lpsc,
				क्रमागत davinci_lpsc_state next_state)
अणु
	u32 epcpr, pdstat, mdstat, ptstat;

	regmap_ग_लिखो_bits(lpsc->regmap, MDCTL(lpsc->md), MDSTAT_STATE_MASK,
			  next_state);

	अगर (lpsc->flags & LPSC_FORCE)
		regmap_ग_लिखो_bits(lpsc->regmap, MDCTL(lpsc->md), MDCTL_FORCE,
				  MDCTL_FORCE);

	regmap_पढ़ो(lpsc->regmap, PDSTAT(lpsc->pd), &pdstat);
	अगर ((pdstat & PDSTAT_STATE_MASK) == 0) अणु
		regmap_ग_लिखो_bits(lpsc->regmap, PDCTL(lpsc->pd), PDCTL_NEXT,
				  PDCTL_NEXT);

		regmap_ग_लिखो(lpsc->regmap, PTCMD, BIT(lpsc->pd));

		regmap_पढ़ो_poll_समयout(lpsc->regmap, EPCPR, epcpr,
					 epcpr & BIT(lpsc->pd), 0, 0);

		regmap_ग_लिखो_bits(lpsc->regmap, PDCTL(lpsc->pd), PDCTL_EPCGOOD,
				  PDCTL_EPCGOOD);
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(lpsc->regmap, PTCMD, BIT(lpsc->pd));
	पूर्ण

	regmap_पढ़ो_poll_समयout(lpsc->regmap, PTSTAT, ptstat,
				 !(ptstat & BIT(lpsc->pd)), 0, 0);

	regmap_पढ़ो_poll_समयout(lpsc->regmap, MDSTAT(lpsc->md), mdstat,
				 (mdstat & MDSTAT_STATE_MASK) == next_state,
				 0, 0);
पूर्ण

अटल पूर्णांक davinci_lpsc_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा davinci_lpsc_clk *lpsc = to_davinci_lpsc_clk(hw);

	davinci_lpsc_config(lpsc, LPSC_STATE_ENABLE);

	वापस 0;
पूर्ण

अटल व्योम davinci_lpsc_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा davinci_lpsc_clk *lpsc = to_davinci_lpsc_clk(hw);

	davinci_lpsc_config(lpsc, LPSC_STATE_DISABLE);
पूर्ण

अटल पूर्णांक davinci_lpsc_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा davinci_lpsc_clk *lpsc = to_davinci_lpsc_clk(hw);
	u32 mdstat;

	regmap_पढ़ो(lpsc->regmap, MDSTAT(lpsc->md), &mdstat);

	वापस (mdstat & MDSTAT_MCKOUT) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops davinci_lpsc_clk_ops = अणु
	.enable		= davinci_lpsc_clk_enable,
	.disable	= davinci_lpsc_clk_disable,
	.is_enabled	= davinci_lpsc_clk_is_enabled,
पूर्ण;

अटल पूर्णांक davinci_psc_genpd_attach_dev(काष्ठा generic_pm_करोमुख्य *pm_करोमुख्य,
					काष्ठा device *dev)
अणु
	काष्ठा davinci_lpsc_clk *lpsc = to_davinci_lpsc_clk(pm_करोमुख्य);
	काष्ठा clk *clk;
	पूर्णांक ret;

	/*
	 * pm_clk_हटाओ_clk() will call clk_put(), so we have to use clk_get()
	 * to get the घड़ी instead of using lpsc->hw.clk directly.
	 */
	clk = clk_get_sys(best_dev_name(lpsc->dev), clk_hw_get_name(&lpsc->hw));
	अगर (IS_ERR(clk))
		वापस (PTR_ERR(clk));

	ret = pm_clk_create(dev);
	अगर (ret < 0)
		जाओ fail_clk_put;

	ret = pm_clk_add_clk(dev, clk);
	अगर (ret < 0)
		जाओ fail_pm_clk_destroy;

	lpsc->genpd_clk = clk;

	वापस 0;

fail_pm_clk_destroy:
	pm_clk_destroy(dev);
fail_clk_put:
	clk_put(clk);

	वापस ret;
पूर्ण

अटल व्योम davinci_psc_genpd_detach_dev(काष्ठा generic_pm_करोमुख्य *pm_करोमुख्य,
					 काष्ठा device *dev)
अणु
	काष्ठा davinci_lpsc_clk *lpsc = to_davinci_lpsc_clk(pm_करोमुख्य);

	pm_clk_हटाओ_clk(dev, lpsc->genpd_clk);
	pm_clk_destroy(dev);

	lpsc->genpd_clk = शून्य;
पूर्ण

/**
 * davinci_lpsc_clk_रेजिस्टर - रेजिस्टर LPSC घड़ी
 * @dev: the घड़ीs's device or शून्य
 * @name: name of this घड़ी
 * @parent_name: name of घड़ी's parent
 * @regmap: PSC MMIO region
 * @md: local PSC number
 * @pd: घातer करोमुख्य
 * @flags: LPSC_* flags
 */
अटल काष्ठा davinci_lpsc_clk *
davinci_lpsc_clk_रेजिस्टर(काष्ठा device *dev, स्थिर अक्षर *name,
			  स्थिर अक्षर *parent_name, काष्ठा regmap *regmap,
			  u32 md, u32 pd, u32 flags)
अणु
	काष्ठा clk_init_data init;
	काष्ठा davinci_lpsc_clk *lpsc;
	पूर्णांक ret;
	bool is_on;

	lpsc = kzalloc(माप(*lpsc), GFP_KERNEL);
	अगर (!lpsc)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &davinci_lpsc_clk_ops;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);
	init.flags = 0;

	अगर (flags & LPSC_ALWAYS_ENABLED)
		init.flags |= CLK_IS_CRITICAL;

	अगर (flags & LPSC_SET_RATE_PARENT)
		init.flags |= CLK_SET_RATE_PARENT;

	lpsc->dev = dev;
	lpsc->regmap = regmap;
	lpsc->hw.init = &init;
	lpsc->md = md;
	lpsc->pd = pd;
	lpsc->flags = flags;

	ret = clk_hw_रेजिस्टर(dev, &lpsc->hw);
	अगर (ret < 0) अणु
		kमुक्त(lpsc);
		वापस ERR_PTR(ret);
	पूर्ण

	/* क्रम now, genpd is only रेजिस्टरed when using device-tree */
	अगर (!dev || !dev->of_node)
		वापस lpsc;

	/* genpd attach needs a way to look up this घड़ी */
	ret = clk_hw_रेजिस्टर_clkdev(&lpsc->hw, name, best_dev_name(dev));

	lpsc->pm_करोमुख्य.name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s: %s",
					      best_dev_name(dev), name);
	lpsc->pm_करोमुख्य.attach_dev = davinci_psc_genpd_attach_dev;
	lpsc->pm_करोमुख्य.detach_dev = davinci_psc_genpd_detach_dev;
	lpsc->pm_करोमुख्य.flags = GENPD_FLAG_PM_CLK;

	is_on = davinci_lpsc_clk_is_enabled(&lpsc->hw);
	pm_genpd_init(&lpsc->pm_करोमुख्य, शून्य, is_on);

	वापस lpsc;
पूर्ण

अटल पूर्णांक davinci_lpsc_clk_reset(काष्ठा clk *clk, bool reset)
अणु
	काष्ठा clk_hw *hw = __clk_get_hw(clk);
	काष्ठा davinci_lpsc_clk *lpsc = to_davinci_lpsc_clk(hw);
	u32 mdctl;

	अगर (IS_ERR_OR_शून्य(lpsc))
		वापस -EINVAL;

	mdctl = reset ? 0 : MDCTL_LRESET;
	regmap_ग_लिखो_bits(lpsc->regmap, MDCTL(lpsc->md), MDCTL_LRESET, mdctl);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_psc_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				    अचिन्हित दीर्घ id)
अणु
	काष्ठा davinci_psc_data *psc = to_davinci_psc_data(rcdev);
	काष्ठा clk *clk = psc->clk_data.clks[id];

	वापस davinci_lpsc_clk_reset(clk, true);
पूर्ण

अटल पूर्णांक davinci_psc_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				      अचिन्हित दीर्घ id)
अणु
	काष्ठा davinci_psc_data *psc = to_davinci_psc_data(rcdev);
	काष्ठा clk *clk = psc->clk_data.clks[id];

	वापस davinci_lpsc_clk_reset(clk, false);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops davinci_psc_reset_ops = अणु
	.निश्चित		= davinci_psc_reset_निश्चित,
	.deनिश्चित	= davinci_psc_reset_deनिश्चित,
पूर्ण;

अटल पूर्णांक davinci_psc_reset_of_xlate(काष्ठा reset_controller_dev *rcdev,
				      स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	काष्ठा of_phandle_args clkspec = *reset_spec; /* discard स्थिर qualअगरier */
	काष्ठा clk *clk;
	काष्ठा clk_hw *hw;
	काष्ठा davinci_lpsc_clk *lpsc;

	/* the घड़ी node is the same as the reset node */
	clk = of_clk_get_from_provider(&clkspec);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	hw = __clk_get_hw(clk);
	lpsc = to_davinci_lpsc_clk(hw);
	clk_put(clk);

	/* not all modules support local reset */
	अगर (!(lpsc->flags & LPSC_LOCAL_RESET))
		वापस -EINVAL;

	वापस lpsc->md;
पूर्ण

अटल स्थिर काष्ठा regmap_config davinci_psc_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
पूर्ण;

अटल काष्ठा davinci_psc_data *
__davinci_psc_रेजिस्टर_घड़ीs(काष्ठा device *dev,
			      स्थिर काष्ठा davinci_lpsc_clk_info *info,
			      पूर्णांक num_clks,
			      व्योम __iomem *base)
अणु
	काष्ठा davinci_psc_data *psc;
	काष्ठा clk **clks;
	काष्ठा generic_pm_करोमुख्य **pm_करोमुख्यs;
	काष्ठा regmap *regmap;
	पूर्णांक i, ret;

	psc = kzalloc(माप(*psc), GFP_KERNEL);
	अगर (!psc)
		वापस ERR_PTR(-ENOMEM);

	clks = kदो_स्मृति_array(num_clks, माप(*clks), GFP_KERNEL);
	अगर (!clks) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_psc;
	पूर्ण

	psc->clk_data.clks = clks;
	psc->clk_data.clk_num = num_clks;

	/*
	 * init array with error so that of_clk_src_onecell_get() करोesn't
	 * वापस शून्य क्रम gaps in the sparse array
	 */
	क्रम (i = 0; i < num_clks; i++)
		clks[i] = ERR_PTR(-ENOENT);

	pm_करोमुख्यs = kसुस्मृति(num_clks, माप(*pm_करोमुख्यs), GFP_KERNEL);
	अगर (!pm_करोमुख्यs) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_clks;
	पूर्ण

	psc->pm_data.करोमुख्यs = pm_करोमुख्यs;
	psc->pm_data.num_करोमुख्यs = num_clks;

	regmap = regmap_init_mmio(dev, base, &davinci_psc_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		जाओ err_मुक्त_pm_करोमुख्यs;
	पूर्ण

	क्रम (; info->name; info++) अणु
		काष्ठा davinci_lpsc_clk *lpsc;

		lpsc = davinci_lpsc_clk_रेजिस्टर(dev, info->name, info->parent,
						 regmap, info->md, info->pd,
						 info->flags);
		अगर (IS_ERR(lpsc)) अणु
			dev_warn(dev, "Failed to register %s (%ld)\n",
				 info->name, PTR_ERR(lpsc));
			जारी;
		पूर्ण

		clks[info->md] = lpsc->hw.clk;
		pm_करोमुख्यs[info->md] = &lpsc->pm_करोमुख्य;
	पूर्ण

	/*
	 * क्रम now, a reset controller is only रेजिस्टरed when there is a device
	 * to associate it with.
	 */
	अगर (!dev)
		वापस psc;

	psc->rcdev.ops = &davinci_psc_reset_ops;
	psc->rcdev.owner = THIS_MODULE;
	psc->rcdev.dev = dev;
	psc->rcdev.of_node = dev->of_node;
	psc->rcdev.of_reset_n_cells = 1;
	psc->rcdev.of_xlate = davinci_psc_reset_of_xlate;
	psc->rcdev.nr_resets = num_clks;

	ret = devm_reset_controller_रेजिस्टर(dev, &psc->rcdev);
	अगर (ret < 0)
		dev_warn(dev, "Failed to register reset controller (%d)\n", ret);

	वापस psc;

err_मुक्त_pm_करोमुख्यs:
	kमुक्त(pm_करोमुख्यs);
err_मुक्त_clks:
	kमुक्त(clks);
err_मुक्त_psc:
	kमुक्त(psc);

	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक davinci_psc_रेजिस्टर_घड़ीs(काष्ठा device *dev,
				स्थिर काष्ठा davinci_lpsc_clk_info *info,
				u8 num_clks,
				व्योम __iomem *base)
अणु
	काष्ठा davinci_psc_data *psc;

	psc = __davinci_psc_रेजिस्टर_घड़ीs(dev, info, num_clks, base);
	अगर (IS_ERR(psc))
		वापस PTR_ERR(psc);

	क्रम (; info->name; info++) अणु
		स्थिर काष्ठा davinci_lpsc_clkdev_info *cdevs = info->cdevs;
		काष्ठा clk *clk = psc->clk_data.clks[info->md];

		अगर (!cdevs || IS_ERR_OR_शून्य(clk))
			जारी;

		क्रम (; cdevs->con_id || cdevs->dev_id; cdevs++)
			clk_रेजिस्टर_clkdev(clk, cdevs->con_id, cdevs->dev_id);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक of_davinci_psc_clk_init(काष्ठा device *dev,
			    स्थिर काष्ठा davinci_lpsc_clk_info *info,
			    u8 num_clks,
			    व्योम __iomem *base)
अणु
	काष्ठा device_node *node = dev->of_node;
	काष्ठा davinci_psc_data *psc;

	psc = __davinci_psc_रेजिस्टर_घड़ीs(dev, info, num_clks, base);
	अगर (IS_ERR(psc))
		वापस PTR_ERR(psc);

	of_genpd_add_provider_onecell(node, &psc->pm_data);

	of_clk_add_provider(node, of_clk_src_onecell_get, &psc->clk_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id davinci_psc_of_match[] = अणु
#अगर_घोषित CONFIG_ARCH_DAVINCI_DA850
	अणु .compatible = "ti,da850-psc0", .data = &of_da850_psc0_init_data पूर्ण,
	अणु .compatible = "ti,da850-psc1", .data = &of_da850_psc1_init_data पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id davinci_psc_id_table[] = अणु
#अगर_घोषित CONFIG_ARCH_DAVINCI_DA830
	अणु .name = "da830-psc0", .driver_data = (kernel_uदीर्घ_t)&da830_psc0_init_data पूर्ण,
	अणु .name = "da830-psc1", .driver_data = (kernel_uदीर्घ_t)&da830_psc1_init_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DA850
	अणु .name = "da850-psc0", .driver_data = (kernel_uदीर्घ_t)&da850_psc0_init_data पूर्ण,
	अणु .name = "da850-psc1", .driver_data = (kernel_uदीर्घ_t)&da850_psc1_init_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM355
	अणु .name = "dm355-psc",  .driver_data = (kernel_uदीर्घ_t)&dm355_psc_init_data  पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM365
	अणु .name = "dm365-psc",  .driver_data = (kernel_uदीर्घ_t)&dm365_psc_init_data  पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM644x
	अणु .name = "dm644x-psc", .driver_data = (kernel_uदीर्घ_t)&dm644x_psc_init_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_DAVINCI_DM646x
	अणु .name = "dm646x-psc", .driver_data = (kernel_uदीर्घ_t)&dm646x_psc_init_data पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक davinci_psc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा davinci_psc_init_data *init_data = शून्य;
	व्योम __iomem *base;
	पूर्णांक ret;

	of_id = of_match_device(davinci_psc_of_match, dev);
	अगर (of_id)
		init_data = of_id->data;
	अन्यथा अगर (pdev->id_entry)
		init_data = (व्योम *)pdev->id_entry->driver_data;

	अगर (!init_data) अणु
		dev_err(dev, "unable to find driver init data\n");
		वापस -EINVAL;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	ret = devm_clk_bulk_get(dev, init_data->num_parent_clks,
				init_data->parent_clks);
	अगर (ret < 0)
		वापस ret;

	वापस init_data->psc_init(dev, base);
पूर्ण

अटल काष्ठा platक्रमm_driver davinci_psc_driver = अणु
	.probe		= davinci_psc_probe,
	.driver		= अणु
		.name		= "davinci-psc-clk",
		.of_match_table	= davinci_psc_of_match,
	पूर्ण,
	.id_table	= davinci_psc_id_table,
पूर्ण;

अटल पूर्णांक __init davinci_psc_driver_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&davinci_psc_driver);
पूर्ण

/* has to be postcore_initcall because davinci_gpio depend on PSC घड़ीs */
postcore_initcall(davinci_psc_driver_init);
