<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Clock implementation क्रम VIA/Wondermedia SoC's
 * Copyright (C) 2012 Tony Prisk <linux@prisktech.co.nz>
 */

#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>

#घोषणा LEGACY_PMC_BASE		0xD8130000

/* All घड़ीs share the same lock as none can be changed concurrently */
अटल DEFINE_SPINLOCK(_lock);

काष्ठा clk_device अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*भाग_reg;
	अचिन्हित पूर्णांक	भाग_mask;
	व्योम __iomem	*en_reg;
	पूर्णांक		en_bit;
	spinlock_t	*lock;
पूर्ण;

/*
 * Add new PLL_TYPE_x definitions here as required. Use the first known model
 * to support the new type as the name.
 * Add हाल statements to vtwm_pll_recalc_rate(), vtwm_pll_round_round() and
 * vtwm_pll_set_rate() to handle the new PLL_TYPE_x
 */

#घोषणा PLL_TYPE_VT8500		0
#घोषणा PLL_TYPE_WM8650		1
#घोषणा PLL_TYPE_WM8750		2
#घोषणा PLL_TYPE_WM8850		3

काष्ठा clk_pll अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	spinlock_t	*lock;
	पूर्णांक		type;
पूर्ण;

अटल व्योम __iomem *pmc_base;

अटल __init व्योम vtwm_set_pmc_base(व्योम)
अणु
	काष्ठा device_node *np =
		of_find_compatible_node(शून्य, शून्य, "via,vt8500-pmc");

	अगर (np)
		pmc_base = of_iomap(np, 0);
	अन्यथा
		pmc_base = ioremap(LEGACY_PMC_BASE, 0x1000);
	of_node_put(np);

	अगर (!pmc_base)
		pr_err("%s:of_iomap(pmc) failed\n", __func__);
पूर्ण

#घोषणा to_clk_device(_hw) container_of(_hw, काष्ठा clk_device, hw)

#घोषणा VT8500_PMC_BUSY_MASK		0x18

अटल व्योम vt8500_pmc_रुको_busy(व्योम)
अणु
	जबतक (पढ़ोl(pmc_base) & VT8500_PMC_BUSY_MASK)
		cpu_relax();
पूर्ण

अटल पूर्णांक vt8500_dclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_device *cdev = to_clk_device(hw);
	u32 en_val;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(cdev->lock, flags);

	en_val = पढ़ोl(cdev->en_reg);
	en_val |= BIT(cdev->en_bit);
	ग_लिखोl(en_val, cdev->en_reg);

	spin_unlock_irqrestore(cdev->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम vt8500_dclk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_device *cdev = to_clk_device(hw);
	u32 en_val;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(cdev->lock, flags);

	en_val = पढ़ोl(cdev->en_reg);
	en_val &= ~BIT(cdev->en_bit);
	ग_लिखोl(en_val, cdev->en_reg);

	spin_unlock_irqrestore(cdev->lock, flags);
पूर्ण

अटल पूर्णांक vt8500_dclk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_device *cdev = to_clk_device(hw);
	u32 en_val = (पढ़ोl(cdev->en_reg) & BIT(cdev->en_bit));

	वापस en_val ? 1 : 0;
पूर्ण

अटल अचिन्हित दीर्घ vt8500_dclk_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_device *cdev = to_clk_device(hw);
	u32 भाग = पढ़ोl(cdev->भाग_reg) & cdev->भाग_mask;

	/* Special हाल क्रम SDMMC devices */
	अगर ((cdev->भाग_mask == 0x3F) && (भाग & BIT(5)))
		भाग = 64 * (भाग & 0x1f);

	/* भाग == 0 is actually the highest भागisor */
	अगर (भाग == 0)
		भाग = (cdev->भाग_mask + 1);

	वापस parent_rate / भाग;
पूर्ण

अटल दीर्घ vt8500_dclk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_device *cdev = to_clk_device(hw);
	u32 भागisor;

	अगर (rate == 0)
		वापस 0;

	भागisor = *prate / rate;

	/* If prate / rate would be decimal, incr the भागisor */
	अगर (rate * भागisor < *prate)
		भागisor++;

	/*
	 * If this is a request क्रम SDMMC we have to adjust the भागisor
	 * when >31 to use the fixed preभागisor
	 */
	अगर ((cdev->भाग_mask == 0x3F) && (भागisor > 31)) अणु
		भागisor = 64 * ((भागisor / 64) + 1);
	पूर्ण

	वापस *prate / भागisor;
पूर्ण

अटल पूर्णांक vt8500_dclk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_device *cdev = to_clk_device(hw);
	u32 भागisor;
	अचिन्हित दीर्घ flags = 0;

	अगर (rate == 0)
		वापस 0;

	भागisor =  parent_rate / rate;

	अगर (भागisor == cdev->भाग_mask + 1)
		भागisor = 0;

	/* SDMMC mask may need to be corrected beक्रमe testing अगर its valid */
	अगर ((cdev->भाग_mask == 0x3F) && (भागisor > 31)) अणु
		/*
		 * Bit 5 is a fixed /64 preभागisor. If the requested भागisor
		 * is >31 then correct क्रम the fixed भागisor being required.
		 */
		भागisor = 0x20 + (भागisor / 64);
	पूर्ण

	अगर (भागisor > cdev->भाग_mask) अणु
		pr_err("%s: invalid divisor for clock\n", __func__);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(cdev->lock, flags);

	vt8500_pmc_रुको_busy();
	ग_लिखोl(भागisor, cdev->भाग_reg);
	vt8500_pmc_रुको_busy();

	spin_unlock_irqrestore(cdev->lock, flags);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा clk_ops vt8500_gated_clk_ops = अणु
	.enable = vt8500_dclk_enable,
	.disable = vt8500_dclk_disable,
	.is_enabled = vt8500_dclk_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा clk_ops vt8500_भागisor_clk_ops = अणु
	.round_rate = vt8500_dclk_round_rate,
	.set_rate = vt8500_dclk_set_rate,
	.recalc_rate = vt8500_dclk_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops vt8500_gated_भागisor_clk_ops = अणु
	.enable = vt8500_dclk_enable,
	.disable = vt8500_dclk_disable,
	.is_enabled = vt8500_dclk_is_enabled,
	.round_rate = vt8500_dclk_round_rate,
	.set_rate = vt8500_dclk_set_rate,
	.recalc_rate = vt8500_dclk_recalc_rate,
पूर्ण;

#घोषणा CLK_INIT_GATED			BIT(0)
#घोषणा CLK_INIT_DIVISOR		BIT(1)
#घोषणा CLK_INIT_GATED_DIVISOR		(CLK_INIT_DIVISOR | CLK_INIT_GATED)

अटल __init व्योम vtwm_device_clk_init(काष्ठा device_node *node)
अणु
	u32 en_reg, भाग_reg;
	काष्ठा clk_hw *hw;
	काष्ठा clk_device *dev_clk;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parent_name;
	काष्ठा clk_init_data init;
	पूर्णांक rc;
	पूर्णांक clk_init_flags = 0;

	अगर (!pmc_base)
		vtwm_set_pmc_base();

	dev_clk = kzalloc(माप(*dev_clk), GFP_KERNEL);
	अगर (WARN_ON(!dev_clk))
		वापस;

	dev_clk->lock = &_lock;

	rc = of_property_पढ़ो_u32(node, "enable-reg", &en_reg);
	अगर (!rc) अणु
		dev_clk->en_reg = pmc_base + en_reg;
		rc = of_property_पढ़ो_u32(node, "enable-bit", &dev_clk->en_bit);
		अगर (rc) अणु
			pr_err("%s: enable-bit property required for gated clock\n",
								__func__);
			वापस;
		पूर्ण
		clk_init_flags |= CLK_INIT_GATED;
	पूर्ण

	rc = of_property_पढ़ो_u32(node, "divisor-reg", &भाग_reg);
	अगर (!rc) अणु
		dev_clk->भाग_reg = pmc_base + भाग_reg;
		/*
		 * use 0x1f as the शेष mask since it covers
		 * almost all the घड़ीs and reduces dts properties
		 */
		dev_clk->भाग_mask = 0x1f;

		of_property_पढ़ो_u32(node, "divisor-mask", &dev_clk->भाग_mask);
		clk_init_flags |= CLK_INIT_DIVISOR;
	पूर्ण

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	चयन (clk_init_flags) अणु
	हाल CLK_INIT_GATED:
		init.ops = &vt8500_gated_clk_ops;
		अवरोध;
	हाल CLK_INIT_DIVISOR:
		init.ops = &vt8500_भागisor_clk_ops;
		अवरोध;
	हाल CLK_INIT_GATED_DIVISOR:
		init.ops = &vt8500_gated_भागisor_clk_ops;
		अवरोध;
	शेष:
		pr_err("%s: Invalid clock description in device tree\n",
								__func__);
		kमुक्त(dev_clk);
		वापस;
	पूर्ण

	init.name = clk_name;
	init.flags = 0;
	parent_name = of_clk_get_parent_name(node, 0);
	init.parent_names = &parent_name;
	init.num_parents = 1;

	dev_clk->hw.init = &init;

	hw = &dev_clk->hw;
	rc = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (WARN_ON(rc)) अणु
		kमुक्त(dev_clk);
		वापस;
	पूर्ण
	rc = of_clk_add_hw_provider(node, of_clk_hw_simple_get, hw);
	clk_hw_रेजिस्टर_clkdev(hw, clk_name, शून्य);
पूर्ण
CLK_OF_DECLARE(vt8500_device, "via,vt8500-device-clock", vtwm_device_clk_init);

/* PLL घड़ी related functions */

#घोषणा to_clk_pll(_hw) container_of(_hw, काष्ठा clk_pll, hw)

/* Helper macros क्रम PLL_VT8500 */
#घोषणा VT8500_PLL_MUL(x)	((x & 0x1F) << 1)
#घोषणा VT8500_PLL_DIV(x)	((x & 0x100) ? 1 : 2)

#घोषणा VT8500_BITS_TO_FREQ(r, m, d)					\
				((r / d) * m)

#घोषणा VT8500_BITS_TO_VAL(m, d)					\
				((d == 2 ? 0 : 0x100) | ((m >> 1) & 0x1F))

/* Helper macros क्रम PLL_WM8650 */
#घोषणा WM8650_PLL_MUL(x)	(x & 0x3FF)
#घोषणा WM8650_PLL_DIV(x)	(((x >> 10) & 7) * (1 << ((x >> 13) & 3)))

#घोषणा WM8650_BITS_TO_FREQ(r, m, d1, d2)				\
				(r * m / (d1 * (1 << d2)))

#घोषणा WM8650_BITS_TO_VAL(m, d1, d2)					\
				((d2 << 13) | (d1 << 10) | (m & 0x3FF))

/* Helper macros क्रम PLL_WM8750 */
#घोषणा WM8750_PLL_MUL(x)	(((x >> 16) & 0xFF) + 1)
#घोषणा WM8750_PLL_DIV(x)	((((x >> 8) & 1) + 1) * (1 << (x & 7)))

#घोषणा WM8750_BITS_TO_FREQ(r, m, d1, d2)				\
				(r * (m+1) / ((d1+1) * (1 << d2)))

#घोषणा WM8750_BITS_TO_VAL(f, m, d1, d2)				\
		((f << 24) | ((m - 1) << 16) | ((d1 - 1) << 8) | d2)

/* Helper macros क्रम PLL_WM8850 */
#घोषणा WM8850_PLL_MUL(x)	((((x >> 16) & 0x7F) + 1) * 2)
#घोषणा WM8850_PLL_DIV(x)	((((x >> 8) & 1) + 1) * (1 << (x & 3)))

#घोषणा WM8850_BITS_TO_FREQ(r, m, d1, d2)				\
				(r * ((m + 1) * 2) / ((d1+1) * (1 << d2)))

#घोषणा WM8850_BITS_TO_VAL(m, d1, d2)					\
		((((m / 2) - 1) << 16) | ((d1 - 1) << 8) | d2)

अटल पूर्णांक vt8500_find_pll_bits(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate,
				u32 *multiplier, u32 *preभाग)
अणु
	अचिन्हित दीर्घ tclk;

	/* sanity check */
	अगर ((rate < parent_rate * 4) || (rate > parent_rate * 62)) अणु
		pr_err("%s: requested rate out of range\n", __func__);
		*multiplier = 0;
		*preभाग = 1;
		वापस -EINVAL;
	पूर्ण
	अगर (rate <= parent_rate * 31)
		/* use the preभाग to द्विगुन the resolution */
		*preभाग = 2;
	अन्यथा
		*preभाग = 1;

	*multiplier = rate / (parent_rate / *preभाग);
	tclk = (parent_rate / *preभाग) * *multiplier;

	अगर (tclk != rate)
		pr_warn("%s: requested rate %lu, found rate %lu\n", __func__,
								rate, tclk);

	वापस 0;
पूर्ण

/*
 * M * parent [O1] => / P [O2] => / D [O3]
 * Where O1 is 900MHz...3GHz;
 * O2 is 600MHz >= (M * parent) / P >= 300MHz;
 * M is 36...120 [25MHz parent]; D is 1 or 2 or 4 or 8.
 * Possible ranges (O3):
 * D = 8: 37,5MHz...75MHz
 * D = 4: 75MHz...150MHz
 * D = 2: 150MHz...300MHz
 * D = 1: 300MHz...600MHz
 */
अटल पूर्णांक wm8650_find_pll_bits(अचिन्हित दीर्घ rate,
	अचिन्हित दीर्घ parent_rate, u32 *multiplier, u32 *भागisor1,
	u32 *भागisor2)
अणु
	अचिन्हित दीर्घ O1, min_err, rate_err;

	अगर (!parent_rate || (rate < 37500000) || (rate > 600000000))
		वापस -EINVAL;

	*भागisor2 = rate <= 75000000 ? 3 : rate <= 150000000 ? 2 :
					   rate <= 300000000 ? 1 : 0;
	/*
	 * Divisor P cannot be calculated. Test all भागisors and find where M
	 * will be as बंद as possible to the requested rate.
	 */
	min_err = अच_दीर्घ_उच्च;
	क्रम (*भागisor1 = 5; *भागisor1 >= 3; (*भागisor1)--) अणु
		O1 = rate * *भागisor1 * (1 << (*भागisor2));
		rate_err = O1 % parent_rate;
		अगर (rate_err < min_err) अणु
			*multiplier = O1 / parent_rate;
			अगर (rate_err == 0)
				वापस 0;

			min_err = rate_err;
		पूर्ण
	पूर्ण

	अगर ((*multiplier < 3) || (*multiplier > 1023))
		वापस -EINVAL;

	pr_warn("%s: rate error is %lu\n", __func__, min_err);

	वापस 0;
पूर्ण

अटल u32 wm8750_get_filter(u32 parent_rate, u32 भागisor1)
अणु
	/* calculate frequency (MHz) after pre-भागisor */
	u32 freq = (parent_rate / 1000000) / (भागisor1 + 1);

	अगर ((freq < 10) || (freq > 200))
		pr_warn("%s: PLL recommended input frequency 10..200Mhz (requested %d Mhz)\n",
				__func__, freq);

	अगर (freq >= 166)
		वापस 7;
	अन्यथा अगर (freq >= 104)
		वापस 6;
	अन्यथा अगर (freq >= 65)
		वापस 5;
	अन्यथा अगर (freq >= 42)
		वापस 4;
	अन्यथा अगर (freq >= 26)
		वापस 3;
	अन्यथा अगर (freq >= 16)
		वापस 2;
	अन्यथा अगर (freq >= 10)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8750_find_pll_bits(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate,
				u32 *filter, u32 *multiplier, u32 *भागisor1, u32 *भागisor2)
अणु
	u32 mul;
	पूर्णांक भाग1, भाग2;
	अचिन्हित दीर्घ tclk, rate_err, best_err;

	best_err = (अचिन्हित दीर्घ)-1;

	/* Find the बंदst match (lower or equal to requested) */
	क्रम (भाग1 = 1; भाग1 >= 0; भाग1--)
		क्रम (भाग2 = 7; भाग2 >= 0; भाग2--)
			क्रम (mul = 0; mul <= 255; mul++) अणु
				tclk = parent_rate * (mul + 1) / ((भाग1 + 1) * (1 << भाग2));
				अगर (tclk > rate)
					जारी;
				/* error will always be +ve */
				rate_err = rate - tclk;
				अगर (rate_err == 0) अणु
					*filter = wm8750_get_filter(parent_rate, भाग1);
					*multiplier = mul;
					*भागisor1 = भाग1;
					*भागisor2 = भाग2;
					वापस 0;
				पूर्ण

				अगर (rate_err < best_err) अणु
					best_err = rate_err;
					*multiplier = mul;
					*भागisor1 = भाग1;
					*भागisor2 = भाग2;
				पूर्ण
			पूर्ण

	अगर (best_err == (अचिन्हित दीर्घ)-1) अणु
		pr_warn("%s: impossible rate %lu\n", __func__, rate);
		वापस -EINVAL;
	पूर्ण

	/* अगर we got here, it wasn't an exact match */
	pr_warn("%s: requested rate %lu, found rate %lu\n", __func__, rate,
							rate - best_err);

	*filter = wm8750_get_filter(parent_rate, *भागisor1);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8850_find_pll_bits(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate,
				u32 *multiplier, u32 *भागisor1, u32 *भागisor2)
अणु
	u32 mul;
	पूर्णांक भाग1, भाग2;
	अचिन्हित दीर्घ tclk, rate_err, best_err;

	best_err = (अचिन्हित दीर्घ)-1;

	/* Find the बंदst match (lower or equal to requested) */
	क्रम (भाग1 = 1; भाग1 >= 0; भाग1--)
		क्रम (भाग2 = 3; भाग2 >= 0; भाग2--)
			क्रम (mul = 0; mul <= 127; mul++) अणु
				tclk = parent_rate * ((mul + 1) * 2) /
						((भाग1 + 1) * (1 << भाग2));
				अगर (tclk > rate)
					जारी;
				/* error will always be +ve */
				rate_err = rate - tclk;
				अगर (rate_err == 0) अणु
					*multiplier = mul;
					*भागisor1 = भाग1;
					*भागisor2 = भाग2;
					वापस 0;
				पूर्ण

				अगर (rate_err < best_err) अणु
					best_err = rate_err;
					*multiplier = mul;
					*भागisor1 = भाग1;
					*भागisor2 = भाग2;
				पूर्ण
			पूर्ण

	अगर (best_err == (अचिन्हित दीर्घ)-1) अणु
		pr_warn("%s: impossible rate %lu\n", __func__, rate);
		वापस -EINVAL;
	पूर्ण

	/* अगर we got here, it wasn't an exact match */
	pr_warn("%s: requested rate %lu, found rate %lu\n", __func__, rate,
							rate - best_err);

	वापस 0;
पूर्ण

अटल पूर्णांक vtwm_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	u32 filter, mul, भाग1, भाग2;
	u32 pll_val;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	/* sanity check */

	चयन (pll->type) अणु
	हाल PLL_TYPE_VT8500:
		ret = vt8500_find_pll_bits(rate, parent_rate, &mul, &भाग1);
		अगर (!ret)
			pll_val = VT8500_BITS_TO_VAL(mul, भाग1);
		अवरोध;
	हाल PLL_TYPE_WM8650:
		ret = wm8650_find_pll_bits(rate, parent_rate, &mul, &भाग1, &भाग2);
		अगर (!ret)
			pll_val = WM8650_BITS_TO_VAL(mul, भाग1, भाग2);
		अवरोध;
	हाल PLL_TYPE_WM8750:
		ret = wm8750_find_pll_bits(rate, parent_rate, &filter, &mul, &भाग1, &भाग2);
		अगर (!ret)
			pll_val = WM8750_BITS_TO_VAL(filter, mul, भाग1, भाग2);
		अवरोध;
	हाल PLL_TYPE_WM8850:
		ret = wm8850_find_pll_bits(rate, parent_rate, &mul, &भाग1, &भाग2);
		अगर (!ret)
			pll_val = WM8850_BITS_TO_VAL(mul, भाग1, भाग2);
		अवरोध;
	शेष:
		pr_err("%s: invalid pll type\n", __func__);
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	spin_lock_irqsave(pll->lock, flags);

	vt8500_pmc_रुको_busy();
	ग_लिखोl(pll_val, pll->reg);
	vt8500_pmc_रुको_busy();

	spin_unlock_irqrestore(pll->lock, flags);

	वापस 0;
पूर्ण

अटल दीर्घ vtwm_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	u32 filter, mul, भाग1, भाग2;
	दीर्घ round_rate;
	पूर्णांक ret;

	चयन (pll->type) अणु
	हाल PLL_TYPE_VT8500:
		ret = vt8500_find_pll_bits(rate, *prate, &mul, &भाग1);
		अगर (!ret)
			round_rate = VT8500_BITS_TO_FREQ(*prate, mul, भाग1);
		अवरोध;
	हाल PLL_TYPE_WM8650:
		ret = wm8650_find_pll_bits(rate, *prate, &mul, &भाग1, &भाग2);
		अगर (!ret)
			round_rate = WM8650_BITS_TO_FREQ(*prate, mul, भाग1, भाग2);
		अवरोध;
	हाल PLL_TYPE_WM8750:
		ret = wm8750_find_pll_bits(rate, *prate, &filter, &mul, &भाग1, &भाग2);
		अगर (!ret)
			round_rate = WM8750_BITS_TO_FREQ(*prate, mul, भाग1, भाग2);
		अवरोध;
	हाल PLL_TYPE_WM8850:
		ret = wm8850_find_pll_bits(rate, *prate, &mul, &भाग1, &भाग2);
		अगर (!ret)
			round_rate = WM8850_BITS_TO_FREQ(*prate, mul, भाग1, भाग2);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	वापस round_rate;
पूर्ण

अटल अचिन्हित दीर्घ vtwm_pll_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	u32 pll_val = पढ़ोl(pll->reg);
	अचिन्हित दीर्घ pll_freq;

	चयन (pll->type) अणु
	हाल PLL_TYPE_VT8500:
		pll_freq = parent_rate * VT8500_PLL_MUL(pll_val);
		pll_freq /= VT8500_PLL_DIV(pll_val);
		अवरोध;
	हाल PLL_TYPE_WM8650:
		pll_freq = parent_rate * WM8650_PLL_MUL(pll_val);
		pll_freq /= WM8650_PLL_DIV(pll_val);
		अवरोध;
	हाल PLL_TYPE_WM8750:
		pll_freq = parent_rate * WM8750_PLL_MUL(pll_val);
		pll_freq /= WM8750_PLL_DIV(pll_val);
		अवरोध;
	हाल PLL_TYPE_WM8850:
		pll_freq = parent_rate * WM8850_PLL_MUL(pll_val);
		pll_freq /= WM8850_PLL_DIV(pll_val);
		अवरोध;
	शेष:
		pll_freq = 0;
	पूर्ण

	वापस pll_freq;
पूर्ण

अटल स्थिर काष्ठा clk_ops vtwm_pll_ops = अणु
	.round_rate = vtwm_pll_round_rate,
	.set_rate = vtwm_pll_set_rate,
	.recalc_rate = vtwm_pll_recalc_rate,
पूर्ण;

अटल __init व्योम vtwm_pll_clk_init(काष्ठा device_node *node, पूर्णांक pll_type)
अणु
	u32 reg;
	काष्ठा clk_hw *hw;
	काष्ठा clk_pll *pll_clk;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parent_name;
	काष्ठा clk_init_data init;
	पूर्णांक rc;

	अगर (!pmc_base)
		vtwm_set_pmc_base();

	rc = of_property_पढ़ो_u32(node, "reg", &reg);
	अगर (WARN_ON(rc))
		वापस;

	pll_clk = kzalloc(माप(*pll_clk), GFP_KERNEL);
	अगर (WARN_ON(!pll_clk))
		वापस;

	pll_clk->reg = pmc_base + reg;
	pll_clk->lock = &_lock;
	pll_clk->type = pll_type;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	init.name = clk_name;
	init.ops = &vtwm_pll_ops;
	init.flags = 0;
	parent_name = of_clk_get_parent_name(node, 0);
	init.parent_names = &parent_name;
	init.num_parents = 1;

	pll_clk->hw.init = &init;

	hw = &pll_clk->hw;
	rc = clk_hw_रेजिस्टर(शून्य, &pll_clk->hw);
	अगर (WARN_ON(rc)) अणु
		kमुक्त(pll_clk);
		वापस;
	पूर्ण
	rc = of_clk_add_hw_provider(node, of_clk_hw_simple_get, hw);
	clk_hw_रेजिस्टर_clkdev(hw, clk_name, शून्य);
पूर्ण


/* Wrappers क्रम initialization functions */

अटल व्योम __init vt8500_pll_init(काष्ठा device_node *node)
अणु
	vtwm_pll_clk_init(node, PLL_TYPE_VT8500);
पूर्ण
CLK_OF_DECLARE(vt8500_pll, "via,vt8500-pll-clock", vt8500_pll_init);

अटल व्योम __init wm8650_pll_init(काष्ठा device_node *node)
अणु
	vtwm_pll_clk_init(node, PLL_TYPE_WM8650);
पूर्ण
CLK_OF_DECLARE(wm8650_pll, "wm,wm8650-pll-clock", wm8650_pll_init);

अटल व्योम __init wm8750_pll_init(काष्ठा device_node *node)
अणु
	vtwm_pll_clk_init(node, PLL_TYPE_WM8750);
पूर्ण
CLK_OF_DECLARE(wm8750_pll, "wm,wm8750-pll-clock", wm8750_pll_init);

अटल व्योम __init wm8850_pll_init(काष्ठा device_node *node)
अणु
	vtwm_pll_clk_init(node, PLL_TYPE_WM8850);
पूर्ण
CLK_OF_DECLARE(wm8850_pll, "wm,wm8850-pll-clock", wm8850_pll_init);
