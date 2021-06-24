<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Nomadik घड़ी implementation
 * Copyright (C) 2013 ST-Ericsson AB
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#घोषणा pr_fmt(fmt) "Nomadik SRC clocks: " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/reboot.h>

/*
 * The Nomadik घड़ी tree is described in the STN8815A12 DB V4.2
 * reference manual क्रम the chip, page 94 ff.
 * Clock IDs are in the STn8815 Reference Manual table 3, page 27.
 */

#घोषणा SRC_CR			0x00U
#घोषणा SRC_CR_T0_ENSEL		BIT(15)
#घोषणा SRC_CR_T1_ENSEL		BIT(17)
#घोषणा SRC_CR_T2_ENSEL		BIT(19)
#घोषणा SRC_CR_T3_ENSEL		BIT(21)
#घोषणा SRC_CR_T4_ENSEL		BIT(23)
#घोषणा SRC_CR_T5_ENSEL		BIT(25)
#घोषणा SRC_CR_T6_ENSEL		BIT(27)
#घोषणा SRC_CR_T7_ENSEL		BIT(29)
#घोषणा SRC_XTALCR		0x0CU
#घोषणा SRC_XTALCR_XTALTIMEN	BIT(20)
#घोषणा SRC_XTALCR_SXTALDIS	BIT(19)
#घोषणा SRC_XTALCR_MXTALSTAT	BIT(2)
#घोषणा SRC_XTALCR_MXTALEN	BIT(1)
#घोषणा SRC_XTALCR_MXTALOVER	BIT(0)
#घोषणा SRC_PLLCR		0x10U
#घोषणा SRC_PLLCR_PLLTIMEN	BIT(29)
#घोषणा SRC_PLLCR_PLL2EN	BIT(28)
#घोषणा SRC_PLLCR_PLL1STAT	BIT(2)
#घोषणा SRC_PLLCR_PLL1EN	BIT(1)
#घोषणा SRC_PLLCR_PLL1OVER	BIT(0)
#घोषणा SRC_PLLFR		0x14U
#घोषणा SRC_PCKEN0		0x24U
#घोषणा SRC_PCKDIS0		0x28U
#घोषणा SRC_PCKENSR0		0x2CU
#घोषणा SRC_PCKSR0		0x30U
#घोषणा SRC_PCKEN1		0x34U
#घोषणा SRC_PCKDIS1		0x38U
#घोषणा SRC_PCKENSR1		0x3CU
#घोषणा SRC_PCKSR1		0x40U

/* Lock protecting the SRC_CR रेजिस्टर */
अटल DEFINE_SPINLOCK(src_lock);
/* Base address of the SRC */
अटल व्योम __iomem *src_base;

अटल पूर्णांक nomadik_clk_reboot_handler(काष्ठा notअगरier_block *this,
				अचिन्हित दीर्घ code,
				व्योम *unused)
अणु
	u32 val;

	/* The मुख्य chrystal need to be enabled क्रम reboot to work */
	val = पढ़ोl(src_base + SRC_XTALCR);
	val &= ~SRC_XTALCR_MXTALOVER;
	val |= SRC_XTALCR_MXTALEN;
	pr_crit("force-enabling MXTALO\n");
	ग_लिखोl(val, src_base + SRC_XTALCR);
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block nomadik_clk_reboot_notअगरier = अणु
	.notअगरier_call = nomadik_clk_reboot_handler,
पूर्ण;

अटल स्थिर काष्ठा of_device_id nomadik_src_match[] __initस्थिर = अणु
	अणु .compatible = "stericsson,nomadik-src" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल व्योम __init nomadik_src_init(व्योम)
अणु
	काष्ठा device_node *np;
	u32 val;

	np = of_find_matching_node(शून्य, nomadik_src_match);
	अगर (!np) अणु
		pr_crit("no matching node for SRC, aborting clock init\n");
		वापस;
	पूर्ण
	src_base = of_iomap(np, 0);
	अगर (!src_base) अणु
		pr_err("%s: must have src parent node with REGS (%pOFn)\n",
		       __func__, np);
		वापस;
	पूर्ण

	/* Set all समयrs to use the 2.4 MHz TIMCLK */
	val = पढ़ोl(src_base + SRC_CR);
	val |= SRC_CR_T0_ENSEL;
	val |= SRC_CR_T1_ENSEL;
	val |= SRC_CR_T2_ENSEL;
	val |= SRC_CR_T3_ENSEL;
	val |= SRC_CR_T4_ENSEL;
	val |= SRC_CR_T5_ENSEL;
	val |= SRC_CR_T6_ENSEL;
	val |= SRC_CR_T7_ENSEL;
	ग_लिखोl(val, src_base + SRC_CR);

	val = पढ़ोl(src_base + SRC_XTALCR);
	pr_info("SXTALO is %s\n",
		(val & SRC_XTALCR_SXTALDIS) ? "disabled" : "enabled");
	pr_info("MXTAL is %s\n",
		(val & SRC_XTALCR_MXTALSTAT) ? "enabled" : "disabled");
	अगर (of_property_पढ़ो_bool(np, "disable-sxtalo")) अणु
		/* The machine uses an बाह्यal oscillator circuit */
		val |= SRC_XTALCR_SXTALDIS;
		pr_info("disabling SXTALO\n");
	पूर्ण
	अगर (of_property_पढ़ो_bool(np, "disable-mxtalo")) अणु
		/* Disable this too: also run by बाह्यal oscillator */
		val |= SRC_XTALCR_MXTALOVER;
		val &= ~SRC_XTALCR_MXTALEN;
		pr_info("disabling MXTALO\n");
	पूर्ण
	ग_लिखोl(val, src_base + SRC_XTALCR);
	रेजिस्टर_reboot_notअगरier(&nomadik_clk_reboot_notअगरier);
पूर्ण

/**
 * काष्ठा clk_pll1 - Nomadik PLL1 घड़ी
 * @hw: corresponding घड़ी hardware entry
 * @id: PLL instance: 1 or 2
 */
काष्ठा clk_pll अणु
	काष्ठा clk_hw hw;
	पूर्णांक id;
पूर्ण;

/**
 * काष्ठा clk_src - Nomadik src घड़ी
 * @hw: corresponding घड़ी hardware entry
 * @id: the घड़ी ID
 * @group1: true अगर the घड़ी is in group1, अन्यथा it is in group0
 * @clkbit: bit 0...31 corresponding to the घड़ी in each घड़ी रेजिस्टर
 */
काष्ठा clk_src अणु
	काष्ठा clk_hw hw;
	पूर्णांक id;
	bool group1;
	u32 clkbit;
पूर्ण;

#घोषणा to_pll(_hw) container_of(_hw, काष्ठा clk_pll, hw)
#घोषणा to_src(_hw) container_of(_hw, काष्ठा clk_src, hw)

अटल पूर्णांक pll_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_pll(hw);
	u32 val;

	spin_lock(&src_lock);
	val = पढ़ोl(src_base + SRC_PLLCR);
	अगर (pll->id == 1) अणु
		अगर (val & SRC_PLLCR_PLL1OVER) अणु
			val |= SRC_PLLCR_PLL1EN;
			ग_लिखोl(val, src_base + SRC_PLLCR);
		पूर्ण
	पूर्ण अन्यथा अगर (pll->id == 2) अणु
		val |= SRC_PLLCR_PLL2EN;
		ग_लिखोl(val, src_base + SRC_PLLCR);
	पूर्ण
	spin_unlock(&src_lock);
	वापस 0;
पूर्ण

अटल व्योम pll_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_pll(hw);
	u32 val;

	spin_lock(&src_lock);
	val = पढ़ोl(src_base + SRC_PLLCR);
	अगर (pll->id == 1) अणु
		अगर (val & SRC_PLLCR_PLL1OVER) अणु
			val &= ~SRC_PLLCR_PLL1EN;
			ग_लिखोl(val, src_base + SRC_PLLCR);
		पूर्ण
	पूर्ण अन्यथा अगर (pll->id == 2) अणु
		val &= ~SRC_PLLCR_PLL2EN;
		ग_लिखोl(val, src_base + SRC_PLLCR);
	पूर्ण
	spin_unlock(&src_lock);
पूर्ण

अटल पूर्णांक pll_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_pll(hw);
	u32 val;

	val = पढ़ोl(src_base + SRC_PLLCR);
	अगर (pll->id == 1) अणु
		अगर (val & SRC_PLLCR_PLL1OVER)
			वापस !!(val & SRC_PLLCR_PLL1EN);
	पूर्ण अन्यथा अगर (pll->id == 2) अणु
		वापस !!(val & SRC_PLLCR_PLL2EN);
	पूर्ण
	वापस 1;
पूर्ण

अटल अचिन्हित दीर्घ pll_clk_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pll *pll = to_pll(hw);
	u32 val;

	val = पढ़ोl(src_base + SRC_PLLFR);

	अगर (pll->id == 1) अणु
		u8 mul;
		u8 भाग;

		mul = (val >> 8) & 0x3FU;
		mul += 2;
		भाग = val & 0x07U;
		वापस (parent_rate * mul) >> भाग;
	पूर्ण

	अगर (pll->id == 2) अणु
		u8 mul;

		mul = (val >> 24) & 0x3FU;
		mul += 2;
		वापस (parent_rate * mul);
	पूर्ण

	/* Unknown PLL */
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा clk_ops pll_clk_ops = अणु
	.enable = pll_clk_enable,
	.disable = pll_clk_disable,
	.is_enabled = pll_clk_is_enabled,
	.recalc_rate = pll_clk_recalc_rate,
पूर्ण;

अटल काष्ठा clk_hw * __init
pll_clk_रेजिस्टर(काष्ठा device *dev, स्थिर अक्षर *name,
		 स्थिर अक्षर *parent_name, u32 id)
अणु
	पूर्णांक ret;
	काष्ठा clk_pll *pll;
	काष्ठा clk_init_data init;

	अगर (id != 1 && id != 2) अणु
		pr_err("%s: the Nomadik has only PLL 1 & 2\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &pll_clk_ops;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);
	pll->hw.init = &init;
	pll->id = id;

	pr_debug("register PLL1 clock \"%s\"\n", name);

	ret = clk_hw_रेजिस्टर(dev, &pll->hw);
	अगर (ret) अणु
		kमुक्त(pll);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &pll->hw;
पूर्ण

/*
 * The Nomadik SRC घड़ीs are gated, but not in the sense that
 * you पढ़ो-modअगरy-ग_लिखो a रेजिस्टर. Instead there are separate
 * घड़ी enable and घड़ी disable रेजिस्टरs. Writing a '1' bit in
 * the enable रेजिस्टर क्रम a certain घड़ी ungates that घड़ी without
 * affecting the other घड़ीs. The disable रेजिस्टर works the opposite
 * way.
 */

अटल पूर्णांक src_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_src *sclk = to_src(hw);
	u32 enreg = sclk->group1 ? SRC_PCKEN1 : SRC_PCKEN0;
	u32 sreg = sclk->group1 ? SRC_PCKSR1 : SRC_PCKSR0;

	ग_लिखोl(sclk->clkbit, src_base + enreg);
	/* spin until enabled */
	जबतक (!(पढ़ोl(src_base + sreg) & sclk->clkbit))
		cpu_relax();
	वापस 0;
पूर्ण

अटल व्योम src_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_src *sclk = to_src(hw);
	u32 disreg = sclk->group1 ? SRC_PCKDIS1 : SRC_PCKDIS0;
	u32 sreg = sclk->group1 ? SRC_PCKSR1 : SRC_PCKSR0;

	ग_लिखोl(sclk->clkbit, src_base + disreg);
	/* spin until disabled */
	जबतक (पढ़ोl(src_base + sreg) & sclk->clkbit)
		cpu_relax();
पूर्ण

अटल पूर्णांक src_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_src *sclk = to_src(hw);
	u32 sreg = sclk->group1 ? SRC_PCKSR1 : SRC_PCKSR0;
	u32 val = पढ़ोl(src_base + sreg);

	वापस !!(val & sclk->clkbit);
पूर्ण

अटल अचिन्हित दीर्घ
src_clk_recalc_rate(काष्ठा clk_hw *hw,
		    अचिन्हित दीर्घ parent_rate)
अणु
	वापस parent_rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops src_clk_ops = अणु
	.enable = src_clk_enable,
	.disable = src_clk_disable,
	.is_enabled = src_clk_is_enabled,
	.recalc_rate = src_clk_recalc_rate,
पूर्ण;

अटल काष्ठा clk_hw * __init
src_clk_रेजिस्टर(काष्ठा device *dev, स्थिर अक्षर *name,
		 स्थिर अक्षर *parent_name, u8 id)
अणु
	पूर्णांक ret;
	काष्ठा clk_src *sclk;
	काष्ठा clk_init_data init;

	sclk = kzalloc(माप(*sclk), GFP_KERNEL);
	अगर (!sclk)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &src_clk_ops;
	/* Do not क्रमce-disable the अटल SDRAM controller */
	अगर (id == 2)
		init.flags = CLK_IGNORE_UNUSED;
	अन्यथा
		init.flags = 0;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);
	sclk->hw.init = &init;
	sclk->id = id;
	sclk->group1 = (id > 31);
	sclk->clkbit = BIT(id & 0x1f);

	pr_debug("register clock \"%s\" ID: %d group: %d bits: %08x\n",
		 name, id, sclk->group1, sclk->clkbit);

	ret = clk_hw_रेजिस्टर(dev, &sclk->hw);
	अगर (ret) अणु
		kमुक्त(sclk);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &sclk->hw;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

अटल u32 src_pcksr0_boot;
अटल u32 src_pcksr1_boot;

अटल स्थिर अक्षर * स्थिर src_clk_names[] = अणु
	"HCLKDMA0  ",
	"HCLKSMC   ",
	"HCLKSDRAM ",
	"HCLKDMA1  ",
	"HCLKCLCD  ",
	"PCLKIRDA  ",
	"PCLKSSP   ",
	"PCLKUART0 ",
	"PCLKSDI   ",
	"PCLKI2C0  ",
	"PCLKI2C1  ",
	"PCLKUART1 ",
	"PCLMSP0   ",
	"HCLKUSB   ",
	"HCLKDIF   ",
	"HCLKSAA   ",
	"HCLKSVA   ",
	"PCLKHSI   ",
	"PCLKXTI   ",
	"PCLKUART2 ",
	"PCLKMSP1  ",
	"PCLKMSP2  ",
	"PCLKOWM   ",
	"HCLKHPI   ",
	"PCLKSKE   ",
	"PCLKHSEM  ",
	"HCLK3D    ",
	"HCLKHASH  ",
	"HCLKCRYP  ",
	"PCLKMSHC  ",
	"HCLKUSBM  ",
	"HCLKRNG   ",
	"RESERVED  ",
	"RESERVED  ",
	"RESERVED  ",
	"RESERVED  ",
	"CLDCLK    ",
	"IRDACLK   ",
	"SSPICLK   ",
	"UART0CLK  ",
	"SDICLK    ",
	"I2C0CLK   ",
	"I2C1CLK   ",
	"UART1CLK  ",
	"MSPCLK0   ",
	"USBCLK    ",
	"DIFCLK    ",
	"IPI2CCLK  ",
	"IPBMCCLK  ",
	"HSICLKRX  ",
	"HSICLKTX  ",
	"UART2CLK  ",
	"MSPCLK1   ",
	"MSPCLK2   ",
	"OWMCLK    ",
	"RESERVED  ",
	"SKECLK    ",
	"RESERVED  ",
	"3DCLK     ",
	"PCLKMSP3  ",
	"MSPCLK3   ",
	"MSHCCLK   ",
	"USBMCLK   ",
	"RNGCCLK   ",
पूर्ण;

अटल पूर्णांक nomadik_src_clk_debugfs_show(काष्ठा seq_file *s, व्योम *what)
अणु
	पूर्णांक i;
	u32 src_pcksr0 = पढ़ोl(src_base + SRC_PCKSR0);
	u32 src_pcksr1 = पढ़ोl(src_base + SRC_PCKSR1);
	u32 src_pckensr0 = पढ़ोl(src_base + SRC_PCKENSR0);
	u32 src_pckensr1 = पढ़ोl(src_base + SRC_PCKENSR1);

	seq_माला_दो(s, "Clock:      Boot:   Now:    Request: ASKED:\n");
	क्रम (i = 0; i < ARRAY_SIZE(src_clk_names); i++) अणु
		u32 pcksrb = (i < 0x20) ? src_pcksr0_boot : src_pcksr1_boot;
		u32 pcksr = (i < 0x20) ? src_pcksr0 : src_pcksr1;
		u32 pckreq = (i < 0x20) ? src_pckensr0 : src_pckensr1;
		u32 mask = BIT(i & 0x1f);

		seq_म_लिखो(s, "%s  %s     %s     %s\n",
			   src_clk_names[i],
			   (pcksrb & mask) ? "on " : "off",
			   (pcksr & mask) ? "on " : "off",
			   (pckreq & mask) ? "on " : "off");
	पूर्ण
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(nomadik_src_clk_debugfs);

अटल पूर्णांक __init nomadik_src_clk_init_debugfs(व्योम)
अणु
	/* Vital क्रम multiplatक्रमm */
	अगर (!src_base)
		वापस -ENODEV;
	src_pcksr0_boot = पढ़ोl(src_base + SRC_PCKSR0);
	src_pcksr1_boot = पढ़ोl(src_base + SRC_PCKSR1);
	debugfs_create_file("nomadik-src-clk", S_IFREG | S_IRUGO,
			    शून्य, शून्य, &nomadik_src_clk_debugfs_fops);
	वापस 0;
पूर्ण
device_initcall(nomadik_src_clk_init_debugfs);

#पूर्ण_अगर

अटल व्योम __init of_nomadik_pll_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *clk_name = np->name;
	स्थिर अक्षर *parent_name;
	u32 pll_id;

	अगर (!src_base)
		nomadik_src_init();

	अगर (of_property_पढ़ो_u32(np, "pll-id", &pll_id)) अणु
		pr_err("%s: PLL \"%s\" missing pll-id property\n",
			__func__, clk_name);
		वापस;
	पूर्ण
	parent_name = of_clk_get_parent_name(np, 0);
	hw = pll_clk_रेजिस्टर(शून्य, clk_name, parent_name, pll_id);
	अगर (!IS_ERR(hw))
		of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(nomadik_pll_clk,
	"st,nomadik-pll-clock", of_nomadik_pll_setup);

अटल व्योम __init of_nomadik_hclk_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *clk_name = np->name;
	स्थिर अक्षर *parent_name;

	अगर (!src_base)
		nomadik_src_init();

	parent_name = of_clk_get_parent_name(np, 0);
	/*
	 * The HCLK भागides PLL1 with 1 (passthru), 2, 3 or 4.
	 */
	hw = clk_hw_रेजिस्टर_भागider(शून्य, clk_name, parent_name,
			   0, src_base + SRC_CR,
			   13, 2,
			   CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO,
			   &src_lock);
	अगर (!IS_ERR(hw))
		of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(nomadik_hclk_clk,
	"st,nomadik-hclk-clock", of_nomadik_hclk_setup);

अटल व्योम __init of_nomadik_src_clk_setup(काष्ठा device_node *np)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *clk_name = np->name;
	स्थिर अक्षर *parent_name;
	u32 clk_id;

	अगर (!src_base)
		nomadik_src_init();

	अगर (of_property_पढ़ो_u32(np, "clock-id", &clk_id)) अणु
		pr_err("%s: SRC clock \"%s\" missing clock-id property\n",
			__func__, clk_name);
		वापस;
	पूर्ण
	parent_name = of_clk_get_parent_name(np, 0);
	hw = src_clk_रेजिस्टर(शून्य, clk_name, parent_name, clk_id);
	अगर (!IS_ERR(hw))
		of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(nomadik_src_clk,
	"st,nomadik-src-clock", of_nomadik_src_clk_setup);
