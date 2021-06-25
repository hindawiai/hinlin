<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018, The Linux Foundation. All rights reserved.

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/krait-l2-accessors.h>

#समावेश "clk-krait.h"

/* Secondary and primary muxes share the same cp15 रेजिस्टर */
अटल DEFINE_SPINLOCK(krait_घड़ी_reg_lock);

#घोषणा LPL_SHIFT	8
अटल व्योम __krait_mux_set_sel(काष्ठा krait_mux_clk *mux, पूर्णांक sel)
अणु
	अचिन्हित दीर्घ flags;
	u32 regval;

	spin_lock_irqsave(&krait_घड़ी_reg_lock, flags);
	regval = krait_get_l2_indirect_reg(mux->offset);
	regval &= ~(mux->mask << mux->shअगरt);
	regval |= (sel & mux->mask) << mux->shअगरt;
	अगर (mux->lpl) अणु
		regval &= ~(mux->mask << (mux->shअगरt + LPL_SHIFT));
		regval |= (sel & mux->mask) << (mux->shअगरt + LPL_SHIFT);
	पूर्ण
	krait_set_l2_indirect_reg(mux->offset, regval);
	spin_unlock_irqrestore(&krait_घड़ी_reg_lock, flags);

	/* Wait क्रम चयन to complete. */
	mb();
	udelay(1);
पूर्ण

अटल पूर्णांक krait_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा krait_mux_clk *mux = to_krait_mux_clk(hw);
	u32 sel;

	sel = clk_mux_index_to_val(mux->parent_map, 0, index);
	mux->en_mask = sel;
	/* Don't touch mux if CPU is off as it won't work */
	अगर (__clk_is_enabled(hw->clk))
		__krait_mux_set_sel(mux, sel);

	mux->reparent = true;

	वापस 0;
पूर्ण

अटल u8 krait_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा krait_mux_clk *mux = to_krait_mux_clk(hw);
	u32 sel;

	sel = krait_get_l2_indirect_reg(mux->offset);
	sel >>= mux->shअगरt;
	sel &= mux->mask;
	mux->en_mask = sel;

	वापस clk_mux_val_to_index(hw, mux->parent_map, 0, sel);
पूर्ण

स्थिर काष्ठा clk_ops krait_mux_clk_ops = अणु
	.set_parent = krait_mux_set_parent,
	.get_parent = krait_mux_get_parent,
	.determine_rate = __clk_mux_determine_rate_बंदst,
पूर्ण;
EXPORT_SYMBOL_GPL(krait_mux_clk_ops);

/* The भागider can भागide by 2, 4, 6 and 8. But we only really need भाग-2. */
अटल दीर्घ krait_भाग2_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *parent_rate)
अणु
	*parent_rate = clk_hw_round_rate(clk_hw_get_parent(hw), rate * 2);
	वापस DIV_ROUND_UP(*parent_rate, 2);
पूर्ण

अटल पूर्णांक krait_भाग2_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा krait_भाग2_clk *d = to_krait_भाग2_clk(hw);
	अचिन्हित दीर्घ flags;
	u32 val;
	u32 mask = BIT(d->width) - 1;

	अगर (d->lpl)
		mask = mask << (d->shअगरt + LPL_SHIFT) | mask << d->shअगरt;

	spin_lock_irqsave(&krait_घड़ी_reg_lock, flags);
	val = krait_get_l2_indirect_reg(d->offset);
	val &= ~mask;
	krait_set_l2_indirect_reg(d->offset, val);
	spin_unlock_irqrestore(&krait_घड़ी_reg_lock, flags);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ
krait_भाग2_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा krait_भाग2_clk *d = to_krait_भाग2_clk(hw);
	u32 mask = BIT(d->width) - 1;
	u32 भाग;

	भाग = krait_get_l2_indirect_reg(d->offset);
	भाग >>= d->shअगरt;
	भाग &= mask;
	भाग = (भाग + 1) * 2;

	वापस DIV_ROUND_UP(parent_rate, भाग);
पूर्ण

स्थिर काष्ठा clk_ops krait_भाग2_clk_ops = अणु
	.round_rate = krait_भाग2_round_rate,
	.set_rate = krait_भाग2_set_rate,
	.recalc_rate = krait_भाग2_recalc_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(krait_भाग2_clk_ops);
