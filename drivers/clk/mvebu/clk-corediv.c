<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MVEBU Core भागider घड़ी
 *
 * Copyright (C) 2013 Marvell
 *
 * Ezequiel Garcia <ezequiel.garcia@मुक्त-electrons.com>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश "common.h"

#घोषणा CORE_CLK_DIV_RATIO_MASK		0xff

/*
 * This काष्ठाure describes the hardware details (bit offset and mask)
 * to configure one particular core भागider घड़ी. Those hardware
 * details may dअगरfer from one SoC to another. This काष्ठाure is
 * thereक्रमe typically instantiated अटलally to describe the
 * hardware details.
 */
काष्ठा clk_coreभाग_desc अणु
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक fieldbit;
पूर्ण;

/*
 * This काष्ठाure describes the hardware details to configure the core
 * भागider घड़ीs on a given SoC. Amongst others, it poपूर्णांकs to the
 * array of core भागider घड़ी descriptors क्रम this SoC, as well as
 * the corresponding operations to manipulate them.
 */
काष्ठा clk_coreभाग_soc_desc अणु
	स्थिर काष्ठा clk_coreभाग_desc *descs;
	अचिन्हित पूर्णांक ndescs;
	स्थिर काष्ठा clk_ops ops;
	u32 ratio_reload;
	u32 enable_bit_offset;
	u32 ratio_offset;
पूर्ण;

/*
 * This काष्ठाure represents one core भागider घड़ी क्रम the घड़ी
 * framework, and is dynamically allocated क्रम each core भागider घड़ी
 * existing in the current SoC.
 */
काष्ठा clk_coreभाग अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
	स्थिर काष्ठा clk_coreभाग_desc *desc;
	स्थिर काष्ठा clk_coreभाग_soc_desc *soc_desc;
	spinlock_t lock;
पूर्ण;

अटल काष्ठा clk_onecell_data clk_data;

/*
 * Description of the core भागider घड़ीs available. For now, we
 * support only न_अंकD, and it is available at the same रेजिस्टर
 * locations regardless of the SoC.
 */
अटल स्थिर काष्ठा clk_coreभाग_desc mvebu_coreभाग_desc[] = अणु
	अणु .mask = 0x3f, .offset = 8, .fieldbit = 1 पूर्ण, /* न_अंकD घड़ी */
पूर्ण;

अटल स्थिर काष्ठा clk_coreभाग_desc mv98dx3236_coreभाग_desc[] = अणु
	अणु .mask = 0x0f, .offset = 6, .fieldbit = 27 पूर्ण, /* न_अंकD घड़ी */
पूर्ण;

#घोषणा to_coreभाग_clk(p) container_of(p, काष्ठा clk_coreभाग, hw)

अटल पूर्णांक clk_coreभाग_is_enabled(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा clk_coreभाग *coreभाग = to_coreभाग_clk(hwclk);
	स्थिर काष्ठा clk_coreभाग_soc_desc *soc_desc = coreभाग->soc_desc;
	स्थिर काष्ठा clk_coreभाग_desc *desc = coreभाग->desc;
	u32 enable_mask = BIT(desc->fieldbit) << soc_desc->enable_bit_offset;

	वापस !!(पढ़ोl(coreभाग->reg) & enable_mask);
पूर्ण

अटल पूर्णांक clk_coreभाग_enable(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा clk_coreभाग *coreभाग = to_coreभाग_clk(hwclk);
	स्थिर काष्ठा clk_coreभाग_soc_desc *soc_desc = coreभाग->soc_desc;
	स्थिर काष्ठा clk_coreभाग_desc *desc = coreभाग->desc;
	अचिन्हित दीर्घ flags = 0;
	u32 reg;

	spin_lock_irqsave(&coreभाग->lock, flags);

	reg = पढ़ोl(coreभाग->reg);
	reg |= (BIT(desc->fieldbit) << soc_desc->enable_bit_offset);
	ग_लिखोl(reg, coreभाग->reg);

	spin_unlock_irqrestore(&coreभाग->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम clk_coreभाग_disable(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा clk_coreभाग *coreभाग = to_coreभाग_clk(hwclk);
	स्थिर काष्ठा clk_coreभाग_soc_desc *soc_desc = coreभाग->soc_desc;
	स्थिर काष्ठा clk_coreभाग_desc *desc = coreभाग->desc;
	अचिन्हित दीर्घ flags = 0;
	u32 reg;

	spin_lock_irqsave(&coreभाग->lock, flags);

	reg = पढ़ोl(coreभाग->reg);
	reg &= ~(BIT(desc->fieldbit) << soc_desc->enable_bit_offset);
	ग_लिखोl(reg, coreभाग->reg);

	spin_unlock_irqrestore(&coreभाग->lock, flags);
पूर्ण

अटल अचिन्हित दीर्घ clk_coreभाग_recalc_rate(काष्ठा clk_hw *hwclk,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_coreभाग *coreभाग = to_coreभाग_clk(hwclk);
	स्थिर काष्ठा clk_coreभाग_soc_desc *soc_desc = coreभाग->soc_desc;
	स्थिर काष्ठा clk_coreभाग_desc *desc = coreभाग->desc;
	u32 reg, भाग;

	reg = पढ़ोl(coreभाग->reg + soc_desc->ratio_offset);
	भाग = (reg >> desc->offset) & desc->mask;
	वापस parent_rate / भाग;
पूर्ण

अटल दीर्घ clk_coreभाग_round_rate(काष्ठा clk_hw *hwclk, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	/* Valid ratio are 1:4, 1:5, 1:6 and 1:8 */
	u32 भाग;

	भाग = *parent_rate / rate;
	अगर (भाग < 4)
		भाग = 4;
	अन्यथा अगर (भाग > 6)
		भाग = 8;

	वापस *parent_rate / भाग;
पूर्ण

अटल पूर्णांक clk_coreभाग_set_rate(काष्ठा clk_hw *hwclk, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_coreभाग *coreभाग = to_coreभाग_clk(hwclk);
	स्थिर काष्ठा clk_coreभाग_soc_desc *soc_desc = coreभाग->soc_desc;
	स्थिर काष्ठा clk_coreभाग_desc *desc = coreभाग->desc;
	अचिन्हित दीर्घ flags = 0;
	u32 reg, भाग;

	भाग = parent_rate / rate;

	spin_lock_irqsave(&coreभाग->lock, flags);

	/* Write new भागider to the भागider ratio रेजिस्टर */
	reg = पढ़ोl(coreभाग->reg + soc_desc->ratio_offset);
	reg &= ~(desc->mask << desc->offset);
	reg |= (भाग & desc->mask) << desc->offset;
	ग_लिखोl(reg, coreभाग->reg + soc_desc->ratio_offset);

	/* Set reload-क्रमce क्रम this घड़ी */
	reg = पढ़ोl(coreभाग->reg) | BIT(desc->fieldbit);
	ग_लिखोl(reg, coreभाग->reg);

	/* Now trigger the घड़ी update */
	reg = पढ़ोl(coreभाग->reg) | soc_desc->ratio_reload;
	ग_लिखोl(reg, coreभाग->reg);

	/*
	 * Wait क्रम घड़ीs to settle करोwn, and then clear all the
	 * ratios request and the reload request.
	 */
	udelay(1000);
	reg &= ~(CORE_CLK_DIV_RATIO_MASK | soc_desc->ratio_reload);
	ग_लिखोl(reg, coreभाग->reg);
	udelay(1000);

	spin_unlock_irqrestore(&coreभाग->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_coreभाग_soc_desc armada370_coreभाग_soc = अणु
	.descs = mvebu_coreभाग_desc,
	.ndescs = ARRAY_SIZE(mvebu_coreभाग_desc),
	.ops = अणु
		.enable = clk_coreभाग_enable,
		.disable = clk_coreभाग_disable,
		.is_enabled = clk_coreभाग_is_enabled,
		.recalc_rate = clk_coreभाग_recalc_rate,
		.round_rate = clk_coreभाग_round_rate,
		.set_rate = clk_coreभाग_set_rate,
	पूर्ण,
	.ratio_reload = BIT(8),
	.enable_bit_offset = 24,
	.ratio_offset = 0x8,
पूर्ण;

अटल स्थिर काष्ठा clk_coreभाग_soc_desc armada380_coreभाग_soc = अणु
	.descs = mvebu_coreभाग_desc,
	.ndescs = ARRAY_SIZE(mvebu_coreभाग_desc),
	.ops = अणु
		.enable = clk_coreभाग_enable,
		.disable = clk_coreभाग_disable,
		.is_enabled = clk_coreभाग_is_enabled,
		.recalc_rate = clk_coreभाग_recalc_rate,
		.round_rate = clk_coreभाग_round_rate,
		.set_rate = clk_coreभाग_set_rate,
	पूर्ण,
	.ratio_reload = BIT(8),
	.enable_bit_offset = 16,
	.ratio_offset = 0x4,
पूर्ण;

अटल स्थिर काष्ठा clk_coreभाग_soc_desc armada375_coreभाग_soc = अणु
	.descs = mvebu_coreभाग_desc,
	.ndescs = ARRAY_SIZE(mvebu_coreभाग_desc),
	.ops = अणु
		.recalc_rate = clk_coreभाग_recalc_rate,
		.round_rate = clk_coreभाग_round_rate,
		.set_rate = clk_coreभाग_set_rate,
	पूर्ण,
	.ratio_reload = BIT(8),
	.ratio_offset = 0x4,
पूर्ण;

अटल स्थिर काष्ठा clk_coreभाग_soc_desc mv98dx3236_coreभाग_soc = अणु
	.descs = mv98dx3236_coreभाग_desc,
	.ndescs = ARRAY_SIZE(mv98dx3236_coreभाग_desc),
	.ops = अणु
		.recalc_rate = clk_coreभाग_recalc_rate,
		.round_rate = clk_coreभाग_round_rate,
		.set_rate = clk_coreभाग_set_rate,
	पूर्ण,
	.ratio_reload = BIT(10),
	.ratio_offset = 0x8,
पूर्ण;

अटल व्योम __init
mvebu_coreभाग_clk_init(काष्ठा device_node *node,
		       स्थिर काष्ठा clk_coreभाग_soc_desc *soc_desc)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_coreभाग *coreभाग;
	काष्ठा clk **clks;
	व्योम __iomem *base;
	स्थिर अक्षर *parent_name;
	स्थिर अक्षर *clk_name;
	पूर्णांक i;

	base = of_iomap(node, 0);
	अगर (WARN_ON(!base))
		वापस;

	parent_name = of_clk_get_parent_name(node, 0);

	clk_data.clk_num = soc_desc->ndescs;

	/* clks holds the घड़ी array */
	clks = kसुस्मृति(clk_data.clk_num, माप(काष्ठा clk *),
				GFP_KERNEL);
	अगर (WARN_ON(!clks))
		जाओ err_unmap;
	/* coreभाग holds the घड़ी specअगरic array */
	coreभाग = kसुस्मृति(clk_data.clk_num, माप(काष्ठा clk_coreभाग),
				GFP_KERNEL);
	अगर (WARN_ON(!coreभाग))
		जाओ err_मुक्त_clks;

	spin_lock_init(&coreभाग->lock);

	क्रम (i = 0; i < clk_data.clk_num; i++) अणु
		of_property_पढ़ो_string_index(node, "clock-output-names",
					      i, &clk_name);
		init.num_parents = 1;
		init.parent_names = &parent_name;
		init.name = clk_name;
		init.ops = &soc_desc->ops;
		init.flags = 0;

		coreभाग[i].soc_desc = soc_desc;
		coreभाग[i].desc = soc_desc->descs + i;
		coreभाग[i].reg = base;
		coreभाग[i].hw.init = &init;

		clks[i] = clk_रेजिस्टर(शून्य, &coreभाग[i].hw);
		WARN_ON(IS_ERR(clks[i]));
	पूर्ण

	clk_data.clks = clks;
	of_clk_add_provider(node, of_clk_src_onecell_get, &clk_data);
	वापस;

err_मुक्त_clks:
	kमुक्त(clks);
err_unmap:
	iounmap(base);
पूर्ण

अटल व्योम __init armada370_coreभाग_clk_init(काष्ठा device_node *node)
अणु
	वापस mvebu_coreभाग_clk_init(node, &armada370_coreभाग_soc);
पूर्ण
CLK_OF_DECLARE(armada370_coreभाग_clk, "marvell,armada-370-corediv-clock",
	       armada370_coreभाग_clk_init);

अटल व्योम __init armada375_coreभाग_clk_init(काष्ठा device_node *node)
अणु
	वापस mvebu_coreभाग_clk_init(node, &armada375_coreभाग_soc);
पूर्ण
CLK_OF_DECLARE(armada375_coreभाग_clk, "marvell,armada-375-corediv-clock",
	       armada375_coreभाग_clk_init);

अटल व्योम __init armada380_coreभाग_clk_init(काष्ठा device_node *node)
अणु
	वापस mvebu_coreभाग_clk_init(node, &armada380_coreभाग_soc);
पूर्ण
CLK_OF_DECLARE(armada380_coreभाग_clk, "marvell,armada-380-corediv-clock",
	       armada380_coreभाग_clk_init);

अटल व्योम __init mv98dx3236_coreभाग_clk_init(काष्ठा device_node *node)
अणु
	वापस mvebu_coreभाग_clk_init(node, &mv98dx3236_coreभाग_soc);
पूर्ण
CLK_OF_DECLARE(mv98dx3236_coreभाग_clk, "marvell,mv98dx3236-corediv-clock",
	       mv98dx3236_coreभाग_clk_init);
