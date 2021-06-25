<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cortina Gemini SoC Clock Controller driver
 * Copyright (c) 2017 Linus Walleij <linus.walleij@linaro.org>
 */

#घोषणा pr_fmt(fmt) "clk-gemini: " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/reset-controller.h>
#समावेश <dt-bindings/reset/cortina,gemini-reset.h>
#समावेश <dt-bindings/घड़ी/cortina,gemini-घड़ी.h>

/* Globally visible घड़ीs */
अटल DEFINE_SPINLOCK(gemini_clk_lock);

#घोषणा GEMINI_GLOBAL_STATUS		0x04
#घोषणा PLL_OSC_SEL			BIT(30)
#घोषणा AHBSPEED_SHIFT			(15)
#घोषणा AHBSPEED_MASK			0x07
#घोषणा CPU_AHB_RATIO_SHIFT		(18)
#घोषणा CPU_AHB_RATIO_MASK		0x03

#घोषणा GEMINI_GLOBAL_PLL_CONTROL	0x08

#घोषणा GEMINI_GLOBAL_SOFT_RESET	0x0c

#घोषणा GEMINI_GLOBAL_MISC_CONTROL	0x30
#घोषणा PCI_CLK_66MHZ			BIT(18)

#घोषणा GEMINI_GLOBAL_CLOCK_CONTROL	0x34
#घोषणा PCI_CLKRUN_EN			BIT(16)
#घोषणा TVC_HALFDIV_SHIFT		(24)
#घोषणा TVC_HALFDIV_MASK		0x1f
#घोषणा SECURITY_CLK_SEL		BIT(29)

#घोषणा GEMINI_GLOBAL_PCI_DLL_CONTROL	0x44
#घोषणा PCI_DLL_BYPASS			BIT(31)
#घोषणा PCI_DLL_TAP_SEL_MASK		0x1f

/**
 * काष्ठा gemini_data_data - Gemini gated घड़ीs
 * @bit_idx: the bit used to gate this घड़ी in the घड़ी रेजिस्टर
 * @name: the घड़ी name
 * @parent_name: the name of the parent घड़ी
 * @flags: standard घड़ी framework flags
 */
काष्ठा gemini_gate_data अणु
	u8 bit_idx;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित दीर्घ flags;
पूर्ण;

/**
 * काष्ठा clk_gemini_pci - Gemini PCI घड़ी
 * @hw: corresponding घड़ी hardware entry
 * @map: regmap to access the रेजिस्टरs
 * @rate: current rate
 */
काष्ठा clk_gemini_pci अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *map;
	अचिन्हित दीर्घ rate;
पूर्ण;

/**
 * काष्ठा gemini_reset - gemini reset controller
 * @map: regmap to access the containing प्रणाली controller
 * @rcdev: reset controller device
 */
काष्ठा gemini_reset अणु
	काष्ठा regmap *map;
	काष्ठा reset_controller_dev rcdev;
पूर्ण;

/* Keeps track of all घड़ीs */
अटल काष्ठा clk_hw_onecell_data *gemini_clk_data;

अटल स्थिर काष्ठा gemini_gate_data gemini_gates[] = अणु
	अणु 1, "security-gate", "secdiv", 0 पूर्ण,
	अणु 2, "gmac0-gate", "ahb", 0 पूर्ण,
	अणु 3, "gmac1-gate", "ahb", 0 पूर्ण,
	अणु 4, "sata0-gate", "ahb", 0 पूर्ण,
	अणु 5, "sata1-gate", "ahb", 0 पूर्ण,
	अणु 6, "usb0-gate", "ahb", 0 पूर्ण,
	अणु 7, "usb1-gate", "ahb", 0 पूर्ण,
	अणु 8, "ide-gate", "ahb", 0 पूर्ण,
	अणु 9, "pci-gate", "ahb", 0 पूर्ण,
	/*
	 * The DDR controller may never have a driver, but certainly must
	 * not be gated off.
	 */
	अणु 10, "ddr-gate", "ahb", CLK_IS_CRITICAL पूर्ण,
	/*
	 * The flash controller must be on to access NOR flash through the
	 * memory map.
	 */
	अणु 11, "flash-gate", "ahb", CLK_IGNORE_UNUSED पूर्ण,
	अणु 12, "tvc-gate", "ahb", 0 पूर्ण,
	अणु 13, "boot-gate", "apb", 0 पूर्ण,
पूर्ण;

#घोषणा to_pciclk(_hw) container_of(_hw, काष्ठा clk_gemini_pci, hw)

#घोषणा to_gemini_reset(p) container_of((p), काष्ठा gemini_reset, rcdev)

अटल अचिन्हित दीर्घ gemini_pci_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_gemini_pci *pciclk = to_pciclk(hw);
	u32 val;

	regmap_पढ़ो(pciclk->map, GEMINI_GLOBAL_MISC_CONTROL, &val);
	अगर (val & PCI_CLK_66MHZ)
		वापस 66000000;
	वापस 33000000;
पूर्ण

अटल दीर्घ gemini_pci_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *prate)
अणु
	/* We support 33 and 66 MHz */
	अगर (rate < 48000000)
		वापस 33000000;
	वापस 66000000;
पूर्ण

अटल पूर्णांक gemini_pci_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_gemini_pci *pciclk = to_pciclk(hw);

	अगर (rate == 33000000)
		वापस regmap_update_bits(pciclk->map,
					  GEMINI_GLOBAL_MISC_CONTROL,
					  PCI_CLK_66MHZ, 0);
	अगर (rate == 66000000)
		वापस regmap_update_bits(pciclk->map,
					  GEMINI_GLOBAL_MISC_CONTROL,
					  0, PCI_CLK_66MHZ);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gemini_pci_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gemini_pci *pciclk = to_pciclk(hw);

	regmap_update_bits(pciclk->map, GEMINI_GLOBAL_CLOCK_CONTROL,
			   0, PCI_CLKRUN_EN);
	वापस 0;
पूर्ण

अटल व्योम gemini_pci_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gemini_pci *pciclk = to_pciclk(hw);

	regmap_update_bits(pciclk->map, GEMINI_GLOBAL_CLOCK_CONTROL,
			   PCI_CLKRUN_EN, 0);
पूर्ण

अटल पूर्णांक gemini_pci_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gemini_pci *pciclk = to_pciclk(hw);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(pciclk->map, GEMINI_GLOBAL_CLOCK_CONTROL, &val);
	वापस !!(val & PCI_CLKRUN_EN);
पूर्ण

अटल स्थिर काष्ठा clk_ops gemini_pci_clk_ops = अणु
	.recalc_rate = gemini_pci_recalc_rate,
	.round_rate = gemini_pci_round_rate,
	.set_rate = gemini_pci_set_rate,
	.enable = gemini_pci_enable,
	.disable = gemini_pci_disable,
	.is_enabled = gemini_pci_is_enabled,
पूर्ण;

अटल काष्ठा clk_hw *gemini_pci_clk_setup(स्थिर अक्षर *name,
					   स्थिर अक्षर *parent_name,
					   काष्ठा regmap *map)
अणु
	काष्ठा clk_gemini_pci *pciclk;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	pciclk = kzalloc(माप(*pciclk), GFP_KERNEL);
	अगर (!pciclk)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &gemini_pci_clk_ops;
	init.flags = 0;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	pciclk->map = map;
	pciclk->hw.init = &init;

	ret = clk_hw_रेजिस्टर(शून्य, &pciclk->hw);
	अगर (ret) अणु
		kमुक्त(pciclk);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &pciclk->hw;
पूर्ण

/*
 * This is a self-deनिश्चितing reset controller.
 */
अटल पूर्णांक gemini_reset(काष्ठा reset_controller_dev *rcdev,
			अचिन्हित दीर्घ id)
अणु
	काष्ठा gemini_reset *gr = to_gemini_reset(rcdev);

	/* Manual says to always set BIT 30 (CPU1) to 1 */
	वापस regmap_ग_लिखो(gr->map,
			    GEMINI_GLOBAL_SOFT_RESET,
			    BIT(GEMINI_RESET_CPU1) | BIT(id));
पूर्ण

अटल पूर्णांक gemini_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक gemini_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक gemini_reset_status(काष्ठा reset_controller_dev *rcdev,
			     अचिन्हित दीर्घ id)
अणु
	काष्ठा gemini_reset *gr = to_gemini_reset(rcdev);
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(gr->map, GEMINI_GLOBAL_SOFT_RESET, &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & BIT(id));
पूर्ण

अटल स्थिर काष्ठा reset_control_ops gemini_reset_ops = अणु
	.reset = gemini_reset,
	.निश्चित = gemini_reset_निश्चित,
	.deनिश्चित = gemini_reset_deनिश्चित,
	.status = gemini_reset_status,
पूर्ण;

अटल पूर्णांक gemini_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	/* Gives the fracions 1x, 1.5x, 1.85x and 2x */
	अचिन्हित पूर्णांक cpu_ahb_mult[4] = अणु 1, 3, 24, 2 पूर्ण;
	अचिन्हित पूर्णांक cpu_ahb_भाग[4] = अणु 1, 2, 13, 1 पूर्ण;
	व्योम __iomem *base;
	काष्ठा gemini_reset *gr;
	काष्ठा regmap *map;
	काष्ठा clk_hw *hw;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	अचिन्हित पूर्णांक mult, भाग;
	काष्ठा resource *res;
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	gr = devm_kzalloc(dev, माप(*gr), GFP_KERNEL);
	अगर (!gr)
		वापस -ENOMEM;

	/* Remap the प्रणाली controller क्रम the exclusive रेजिस्टर */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	map = syscon_node_to_regmap(np);
	अगर (IS_ERR(map)) अणु
		dev_err(dev, "no syscon regmap\n");
		वापस PTR_ERR(map);
	पूर्ण

	gr->map = map;
	gr->rcdev.owner = THIS_MODULE;
	gr->rcdev.nr_resets = 32;
	gr->rcdev.ops = &gemini_reset_ops;
	gr->rcdev.of_node = np;

	ret = devm_reset_controller_रेजिस्टर(dev, &gr->rcdev);
	अगर (ret) अणु
		dev_err(dev, "could not register reset controller\n");
		वापस ret;
	पूर्ण

	/* RTC घड़ी 32768 Hz */
	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "rtc", शून्य, 0, 32768);
	gemini_clk_data->hws[GEMINI_CLK_RTC] = hw;

	/* CPU घड़ी derived as a fixed ratio from the AHB घड़ी */
	regmap_पढ़ो(map, GEMINI_GLOBAL_STATUS, &val);
	val >>= CPU_AHB_RATIO_SHIFT;
	val &= CPU_AHB_RATIO_MASK;
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "cpu", "ahb", 0,
					  cpu_ahb_mult[val],
					  cpu_ahb_भाग[val]);
	gemini_clk_data->hws[GEMINI_CLK_CPU] = hw;

	/* Security घड़ी is 1:1 or 0.75 of APB */
	regmap_पढ़ो(map, GEMINI_GLOBAL_CLOCK_CONTROL, &val);
	अगर (val & SECURITY_CLK_SEL) अणु
		mult = 1;
		भाग = 1;
	पूर्ण अन्यथा अणु
		mult = 3;
		भाग = 4;
	पूर्ण
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "secdiv", "ahb", 0, mult, भाग);

	/*
	 * These are the leaf gates, at boot no घड़ीs are gated.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(gemini_gates); i++) अणु
		स्थिर काष्ठा gemini_gate_data *gd;

		gd = &gemini_gates[i];
		gemini_clk_data->hws[GEMINI_CLK_GATES + i] =
			clk_hw_रेजिस्टर_gate(शून्य, gd->name,
					     gd->parent_name,
					     gd->flags,
					     base + GEMINI_GLOBAL_CLOCK_CONTROL,
					     gd->bit_idx,
					     CLK_GATE_SET_TO_DISABLE,
					     &gemini_clk_lock);
	पूर्ण

	/*
	 * The TV Interface Controller has a 5-bit half भागider रेजिस्टर.
	 * This घड़ी is supposed to be 27MHz as this is an exact multiple
	 * of PAL and NTSC frequencies. The रेजिस्टर is unकरोcumented :(
	 * FIXME: figure out the parent and how the भागider works.
	 */
	mult = 1;
	भाग = ((val >> TVC_HALFDIV_SHIFT) & TVC_HALFDIV_MASK);
	dev_dbg(dev, "TVC half divider value = %d\n", भाग);
	भाग += 1;
	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "tvcdiv", "xtal", 0, 27000000);
	gemini_clk_data->hws[GEMINI_CLK_TVC] = hw;

	/* FIXME: very unclear what the parent is */
	hw = gemini_pci_clk_setup("PCI", "xtal", map);
	gemini_clk_data->hws[GEMINI_CLK_PCI] = hw;

	/* FIXME: very unclear what the parent is */
	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "uart", "xtal", 0, 48000000);
	gemini_clk_data->hws[GEMINI_CLK_UART] = hw;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gemini_clk_dt_ids[] = अणु
	अणु .compatible = "cortina,gemini-syscon", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver gemini_clk_driver = अणु
	.probe  = gemini_clk_probe,
	.driver = अणु
		.name = "gemini-clk",
		.of_match_table = gemini_clk_dt_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(gemini_clk_driver);

अटल व्योम __init gemini_cc_init(काष्ठा device_node *np)
अणु
	काष्ठा regmap *map;
	काष्ठा clk_hw *hw;
	अचिन्हित दीर्घ freq;
	अचिन्हित पूर्णांक mult, भाग;
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	gemini_clk_data = kzalloc(काष्ठा_size(gemini_clk_data, hws,
					      GEMINI_NUM_CLKS),
				  GFP_KERNEL);
	अगर (!gemini_clk_data)
		वापस;

	/*
	 * This way all घड़ी fetched beक्रमe the platक्रमm device probes,
	 * except those we assign here क्रम early use, will be deferred.
	 */
	क्रम (i = 0; i < GEMINI_NUM_CLKS; i++)
		gemini_clk_data->hws[i] = ERR_PTR(-EPROBE_DEFER);

	map = syscon_node_to_regmap(np);
	अगर (IS_ERR(map)) अणु
		pr_err("no syscon regmap\n");
		वापस;
	पूर्ण
	/*
	 * We check that the regmap works on this very first access,
	 * but as this is an MMIO-backed regmap, subsequent regmap
	 * access is not going to fail and we skip error checks from
	 * this poपूर्णांक.
	 */
	ret = regmap_पढ़ो(map, GEMINI_GLOBAL_STATUS, &val);
	अगर (ret) अणु
		pr_err("failed to read global status register\n");
		वापस;
	पूर्ण

	/*
	 * XTAL is the crystal oscillator, 60 or 30 MHz selected from
	 * strap pin E6
	 */
	अगर (val & PLL_OSC_SEL)
		freq = 30000000;
	अन्यथा
		freq = 60000000;
	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "xtal", शून्य, 0, freq);
	pr_debug("main crystal @%lu MHz\n", freq / 1000000);

	/* VCO घड़ी derived from the crystal */
	mult = 13 + ((val >> AHBSPEED_SHIFT) & AHBSPEED_MASK);
	भाग = 2;
	/* If we run on 30 MHz crystal we have to multiply with two */
	अगर (val & PLL_OSC_SEL)
		mult *= 2;
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "vco", "xtal", 0, mult, भाग);

	/* The AHB घड़ी is always 1/3 of the VCO */
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "ahb", "vco", 0, 1, 3);
	gemini_clk_data->hws[GEMINI_CLK_AHB] = hw;

	/* The APB घड़ी is always 1/6 of the AHB */
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "apb", "ahb", 0, 1, 6);
	gemini_clk_data->hws[GEMINI_CLK_APB] = hw;

	/* Register the घड़ीs to be accessed by the device tree */
	gemini_clk_data->num = GEMINI_NUM_CLKS;
	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, gemini_clk_data);
पूर्ण
CLK_OF_DECLARE_DRIVER(gemini_cc, "cortina,gemini-syscon", gemini_cc_init);
