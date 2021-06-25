<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Marvell Technology Group Ltd.
 *
 * Alexandre Belloni <alexandre.belloni@मुक्त-electrons.com>
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "berlin2-div.h"
#समावेश "berlin2-pll.h"

काष्ठा berlin2_pll अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	काष्ठा berlin2_pll_map map;
पूर्ण;

#घोषणा to_berlin2_pll(hw) container_of(hw, काष्ठा berlin2_pll, hw)

#घोषणा SPLL_CTRL0	0x00
#घोषणा SPLL_CTRL1	0x04
#घोषणा SPLL_CTRL2	0x08
#घोषणा SPLL_CTRL3	0x0c
#घोषणा SPLL_CTRL4	0x10

#घोषणा FBDIV_MASK	0x1ff
#घोषणा RFDIV_MASK	0x1f
#घोषणा DIVSEL_MASK	0xf

/*
 * The output frequency क्रमmula क्रम the pll is:
 * clkout = fbभाग / refभाग * parent / vcoभाग
 */
अटल अचिन्हित दीर्घ
berlin2_pll_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा berlin2_pll *pll = to_berlin2_pll(hw);
	काष्ठा berlin2_pll_map *map = &pll->map;
	u32 val, fbभाग, rfभाग, vcoभागsel, vcoभाग;
	u64 rate = parent_rate;

	val = पढ़ोl_relaxed(pll->base + SPLL_CTRL0);
	fbभाग = (val >> map->fbभाग_shअगरt) & FBDIV_MASK;
	rfभाग = (val >> map->rfभाग_shअगरt) & RFDIV_MASK;
	अगर (rfभाग == 0) अणु
		pr_warn("%s has zero rfdiv\n", clk_hw_get_name(hw));
		rfभाग = 1;
	पूर्ण

	val = पढ़ोl_relaxed(pll->base + SPLL_CTRL1);
	vcoभागsel = (val >> map->भागsel_shअगरt) & DIVSEL_MASK;
	vcoभाग = map->vcoभाग[vcoभागsel];
	अगर (vcoभाग == 0) अणु
		pr_warn("%s has zero vcodiv (index %d)\n",
			clk_hw_get_name(hw), vcoभागsel);
		vcoभाग = 1;
	पूर्ण

	rate *= fbभाग * map->mult;
	करो_भाग(rate, rfभाग * vcoभाग);

	वापस (अचिन्हित दीर्घ)rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops berlin2_pll_ops = अणु
	.recalc_rate	= berlin2_pll_recalc_rate,
पूर्ण;

पूर्णांक __init
berlin2_pll_रेजिस्टर(स्थिर काष्ठा berlin2_pll_map *map,
		     व्योम __iomem *base, स्थिर अक्षर *name,
		     स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk_init_data init;
	काष्ठा berlin2_pll *pll;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस -ENOMEM;

	/* copy pll_map to allow __initस्थिर */
	स_नकल(&pll->map, map, माप(*map));
	pll->base = base;
	pll->hw.init = &init;
	init.name = name;
	init.ops = &berlin2_pll_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = flags;

	वापस clk_hw_रेजिस्टर(शून्य, &pll->hw);
पूर्ण
