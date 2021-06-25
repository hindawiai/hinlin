<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Marvell Technology Group Ltd.
 *
 * Alexandre Belloni <alexandre.belloni@मुक्त-electrons.com>
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 */
#समावेश <linux/bitops.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "berlin2-div.h"

/*
 * Clock भागiders in Berlin2 SoCs comprise a complex cell to select
 * input pll and भागider. The भव काष्ठाure as it is used in Marvell
 * BSP code can be seen as:
 *
 *                      +---+
 * pll0 --------------->| 0 |                   +---+
 *           +---+      |(B)|--+--------------->| 0 |      +---+
 * pll1.0 -->| 0 |  +-->| 1 |  |   +--------+   |(E)|----->| 0 |   +---+
 * pll1.1 -->| 1 |  |   +---+  +-->|(C) 1:M |-->| 1 |      |(F)|-->|(G)|->
 * ...    -->|(A)|--+          |   +--------+   +---+  +-->| 1 |   +---+
 * ...    -->|   |             +-->|(D) 1:3 |----------+   +---+
 * pll1.N -->| N |                 +---------
 *           +---+
 *
 * (A) input pll घड़ी mux controlled by               <PllSelect[1:n]>
 * (B) input pll bypass mux controlled by              <PllSwitch>
 * (C) programmable घड़ी भागider controlled by        <Select[1:n]>
 * (D) स्थिरant भाग-by-3 घड़ी भागider
 * (E) programmable घड़ी भागider bypass controlled by <Switch>
 * (F) स्थिरant भाग-by-3 घड़ी mux controlled by       <D3Switch>
 * (G) घड़ी gate controlled by                        <Enable>
 *
 * For whatever reason, above control संकेतs come in two flavors:
 * - single रेजिस्टर भागiders with all bits in one रेजिस्टर
 * - shared रेजिस्टर भागiders with bits spपढ़ो over multiple रेजिस्टरs
 *   (including संकेतs क्रम the same cell spपढ़ो over consecutive रेजिस्टरs)
 *
 * Also, घड़ी gate and pll mux is not available on every भाग cell, so
 * we have to deal with those, too. We reuse common घड़ी composite driver
 * क्रम it.
 */

#घोषणा PLL_SELECT_MASK	0x7
#घोषणा DIV_SELECT_MASK	0x7

काष्ठा berlin2_भाग अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	काष्ठा berlin2_भाग_map map;
	spinlock_t *lock;
पूर्ण;

#घोषणा to_berlin2_भाग(hw) container_of(hw, काष्ठा berlin2_भाग, hw)

अटल u8 clk_भाग[] = अणु 1, 2, 4, 6, 8, 12, 1, 1 पूर्ण;

अटल पूर्णांक berlin2_भाग_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा berlin2_भाग *भाग = to_berlin2_भाग(hw);
	काष्ठा berlin2_भाग_map *map = &भाग->map;
	u32 reg;

	अगर (भाग->lock)
		spin_lock(भाग->lock);

	reg = पढ़ोl_relaxed(भाग->base + map->gate_offs);
	reg >>= map->gate_shअगरt;

	अगर (भाग->lock)
		spin_unlock(भाग->lock);

	वापस (reg & 0x1);
पूर्ण

अटल पूर्णांक berlin2_भाग_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा berlin2_भाग *भाग = to_berlin2_भाग(hw);
	काष्ठा berlin2_भाग_map *map = &भाग->map;
	u32 reg;

	अगर (भाग->lock)
		spin_lock(भाग->lock);

	reg = पढ़ोl_relaxed(भाग->base + map->gate_offs);
	reg |= BIT(map->gate_shअगरt);
	ग_लिखोl_relaxed(reg, भाग->base + map->gate_offs);

	अगर (भाग->lock)
		spin_unlock(भाग->lock);

	वापस 0;
पूर्ण

अटल व्योम berlin2_भाग_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा berlin2_भाग *भाग = to_berlin2_भाग(hw);
	काष्ठा berlin2_भाग_map *map = &भाग->map;
	u32 reg;

	अगर (भाग->lock)
		spin_lock(भाग->lock);

	reg = पढ़ोl_relaxed(भाग->base + map->gate_offs);
	reg &= ~BIT(map->gate_shअगरt);
	ग_लिखोl_relaxed(reg, भाग->base + map->gate_offs);

	अगर (भाग->lock)
		spin_unlock(भाग->lock);
पूर्ण

अटल पूर्णांक berlin2_भाग_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा berlin2_भाग *भाग = to_berlin2_भाग(hw);
	काष्ठा berlin2_भाग_map *map = &भाग->map;
	u32 reg;

	अगर (भाग->lock)
		spin_lock(भाग->lock);

	/* index == 0 is PLL_SWITCH */
	reg = पढ़ोl_relaxed(भाग->base + map->pll_चयन_offs);
	अगर (index == 0)
		reg &= ~BIT(map->pll_चयन_shअगरt);
	अन्यथा
		reg |= BIT(map->pll_चयन_shअगरt);
	ग_लिखोl_relaxed(reg, भाग->base + map->pll_चयन_offs);

	/* index > 0 is PLL_SELECT */
	अगर (index > 0) अणु
		reg = पढ़ोl_relaxed(भाग->base + map->pll_select_offs);
		reg &= ~(PLL_SELECT_MASK << map->pll_select_shअगरt);
		reg |= (index - 1) << map->pll_select_shअगरt;
		ग_लिखोl_relaxed(reg, भाग->base + map->pll_select_offs);
	पूर्ण

	अगर (भाग->lock)
		spin_unlock(भाग->lock);

	वापस 0;
पूर्ण

अटल u8 berlin2_भाग_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा berlin2_भाग *भाग = to_berlin2_भाग(hw);
	काष्ठा berlin2_भाग_map *map = &भाग->map;
	u32 reg;
	u8 index = 0;

	अगर (भाग->lock)
		spin_lock(भाग->lock);

	/* PLL_SWITCH == 0 is index 0 */
	reg = पढ़ोl_relaxed(भाग->base + map->pll_चयन_offs);
	reg &= BIT(map->pll_चयन_shअगरt);
	अगर (reg) अणु
		reg = पढ़ोl_relaxed(भाग->base + map->pll_select_offs);
		reg >>= map->pll_select_shअगरt;
		reg &= PLL_SELECT_MASK;
		index = 1 + reg;
	पूर्ण

	अगर (भाग->lock)
		spin_unlock(भाग->lock);

	वापस index;
पूर्ण

अटल अचिन्हित दीर्घ berlin2_भाग_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा berlin2_भाग *भाग = to_berlin2_भाग(hw);
	काष्ठा berlin2_भाग_map *map = &भाग->map;
	u32 भागsw, भाग3sw, भागider = 1;

	अगर (भाग->lock)
		spin_lock(भाग->lock);

	भागsw = पढ़ोl_relaxed(भाग->base + map->भाग_चयन_offs) &
		(1 << map->भाग_चयन_shअगरt);
	भाग3sw = पढ़ोl_relaxed(भाग->base + map->भाग3_चयन_offs) &
		(1 << map->भाग3_चयन_shअगरt);

	/* स्थिरant भागide-by-3 (करोminant) */
	अगर (भाग3sw != 0) अणु
		भागider = 3;
	/* भागider can be bypassed with DIV_SWITCH == 0 */
	पूर्ण अन्यथा अगर (भागsw == 0) अणु
		भागider = 1;
	/* घड़ी भागider determined by DIV_SELECT */
	पूर्ण अन्यथा अणु
		u32 reg;
		reg = पढ़ोl_relaxed(भाग->base + map->भाग_select_offs);
		reg >>= map->भाग_select_shअगरt;
		reg &= DIV_SELECT_MASK;
		भागider = clk_भाग[reg];
	पूर्ण

	अगर (भाग->lock)
		spin_unlock(भाग->lock);

	वापस parent_rate / भागider;
पूर्ण

अटल स्थिर काष्ठा clk_ops berlin2_भाग_rate_ops = अणु
	.recalc_rate	= berlin2_भाग_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops berlin2_भाग_gate_ops = अणु
	.is_enabled	= berlin2_भाग_is_enabled,
	.enable		= berlin2_भाग_enable,
	.disable	= berlin2_भाग_disable,
पूर्ण;

अटल स्थिर काष्ठा clk_ops berlin2_भाग_mux_ops = अणु
	.set_parent	= berlin2_भाग_set_parent,
	.get_parent	= berlin2_भाग_get_parent,
पूर्ण;

काष्ठा clk_hw * __init
berlin2_भाग_रेजिस्टर(स्थिर काष्ठा berlin2_भाग_map *map,
		     व्योम __iomem *base, स्थिर अक्षर *name, u8 भाग_flags,
		     स्थिर अक्षर **parent_names, पूर्णांक num_parents,
		     अचिन्हित दीर्घ flags, spinlock_t *lock)
अणु
	स्थिर काष्ठा clk_ops *mux_ops = &berlin2_भाग_mux_ops;
	स्थिर काष्ठा clk_ops *rate_ops = &berlin2_भाग_rate_ops;
	स्थिर काष्ठा clk_ops *gate_ops = &berlin2_भाग_gate_ops;
	काष्ठा berlin2_भाग *भाग;

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	/* copy भाग_map to allow __initस्थिर */
	स_नकल(&भाग->map, map, माप(*map));
	भाग->base = base;
	भाग->lock = lock;

	अगर ((भाग_flags & BERLIN2_DIV_HAS_GATE) == 0)
		gate_ops = शून्य;
	अगर ((भाग_flags & BERLIN2_DIV_HAS_MUX) == 0)
		mux_ops = शून्य;

	वापस clk_hw_रेजिस्टर_composite(शून्य, name, parent_names, num_parents,
				      &भाग->hw, mux_ops, &भाग->hw, rate_ops,
				      &भाग->hw, gate_ops, flags);
पूर्ण
