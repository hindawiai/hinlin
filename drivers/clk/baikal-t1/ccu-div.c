<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
 *
 * Authors:
 *   Serge Semin <Sergey.Semin@baikalelectronics.ru>
 *   Dmitry Dunaev <dmitry.dunaev@baikalelectronics.ru>
 *
 * Baikal-T1 CCU Dividers पूर्णांकerface driver
 */

#घोषणा pr_fmt(fmt) "bt1-ccu-div: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/bits.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश <linux/समय64.h>
#समावेश <linux/debugfs.h>

#समावेश "ccu-div.h"

#घोषणा CCU_DIV_CTL			0x00
#घोषणा CCU_DIV_CTL_EN			BIT(0)
#घोषणा CCU_DIV_CTL_RST			BIT(1)
#घोषणा CCU_DIV_CTL_SET_CLKDIV		BIT(2)
#घोषणा CCU_DIV_CTL_CLKDIV_FLD		4
#घोषणा CCU_DIV_CTL_CLKDIV_MASK(_width) \
	GENMASK((_width) + CCU_DIV_CTL_CLKDIV_FLD - 1, CCU_DIV_CTL_CLKDIV_FLD)
#घोषणा CCU_DIV_CTL_LOCK_SHIFTED	BIT(27)
#घोषणा CCU_DIV_CTL_LOCK_NORMAL		BIT(31)

#घोषणा CCU_DIV_RST_DELAY_US		1
#घोषणा CCU_DIV_LOCK_CHECK_RETRIES	50

#घोषणा CCU_DIV_CLKDIV_MIN		0
#घोषणा CCU_DIV_CLKDIV_MAX(_mask) \
	((_mask) >> CCU_DIV_CTL_CLKDIV_FLD)

/*
 * Use the next two methods until there are generic field setter and
 * getter available with non-स्थिरant mask support.
 */
अटल अंतरभूत u32 ccu_भाग_get(u32 mask, u32 val)
अणु
	वापस (val & mask) >> CCU_DIV_CTL_CLKDIV_FLD;
पूर्ण

अटल अंतरभूत u32 ccu_भाग_prep(u32 mask, u32 val)
अणु
	वापस (val << CCU_DIV_CTL_CLKDIV_FLD) & mask;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ccu_भाग_lock_delay_ns(अचिन्हित दीर्घ ref_clk,
						  अचिन्हित दीर्घ भाग)
अणु
	u64 ns = 4ULL * (भाग ?: 1) * NSEC_PER_SEC;

	करो_भाग(ns, ref_clk);

	वापस ns;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ccu_भाग_calc_freq(अचिन्हित दीर्घ ref_clk,
					      अचिन्हित दीर्घ भाग)
अणु
	वापस ref_clk / (भाग ?: 1);
पूर्ण

अटल पूर्णांक ccu_भाग_var_update_clkभाग(काष्ठा ccu_भाग *भाग,
				     अचिन्हित दीर्घ parent_rate,
				     अचिन्हित दीर्घ भागider)
अणु
	अचिन्हित दीर्घ nd;
	u32 val = 0;
	u32 lock;
	पूर्णांक count;

	nd = ccu_भाग_lock_delay_ns(parent_rate, भागider);

	अगर (भाग->features & CCU_DIV_LOCK_SHIFTED)
		lock = CCU_DIV_CTL_LOCK_SHIFTED;
	अन्यथा
		lock = CCU_DIV_CTL_LOCK_NORMAL;

	regmap_update_bits(भाग->sys_regs, भाग->reg_ctl,
			   CCU_DIV_CTL_SET_CLKDIV, CCU_DIV_CTL_SET_CLKDIV);

	/*
	 * Until there is nsec-version of पढ़ोl_poll_समयout() is available
	 * we have to implement the next polling loop.
	 */
	count = CCU_DIV_LOCK_CHECK_RETRIES;
	करो अणु
		ndelay(nd);
		regmap_पढ़ो(भाग->sys_regs, भाग->reg_ctl, &val);
		अगर (val & lock)
			वापस 0;
	पूर्ण जबतक (--count);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ccu_भाग_var_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw *parent_hw = clk_hw_get_parent(hw);
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);
	अचिन्हित दीर्घ flags;
	u32 val = 0;
	पूर्णांक ret;

	अगर (!parent_hw) अणु
		pr_err("Can't enable '%s' with no parent", clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	regmap_पढ़ो(भाग->sys_regs, भाग->reg_ctl, &val);
	अगर (val & CCU_DIV_CTL_EN)
		वापस 0;

	spin_lock_irqsave(&भाग->lock, flags);
	ret = ccu_भाग_var_update_clkभाग(भाग, clk_hw_get_rate(parent_hw),
					ccu_भाग_get(भाग->mask, val));
	अगर (!ret)
		regmap_update_bits(भाग->sys_regs, भाग->reg_ctl,
				   CCU_DIV_CTL_EN, CCU_DIV_CTL_EN);
	spin_unlock_irqrestore(&भाग->lock, flags);
	अगर (ret)
		pr_err("Divider '%s' lock timed out\n", clk_hw_get_name(hw));

	वापस ret;
पूर्ण

अटल पूर्णांक ccu_भाग_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&भाग->lock, flags);
	regmap_update_bits(भाग->sys_regs, भाग->reg_ctl,
			   CCU_DIV_CTL_EN, CCU_DIV_CTL_EN);
	spin_unlock_irqrestore(&भाग->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम ccu_भाग_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&भाग->lock, flags);
	regmap_update_bits(भाग->sys_regs, भाग->reg_ctl, CCU_DIV_CTL_EN, 0);
	spin_unlock_irqrestore(&भाग->lock, flags);
पूर्ण

अटल पूर्णांक ccu_भाग_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);
	u32 val = 0;

	regmap_पढ़ो(भाग->sys_regs, भाग->reg_ctl, &val);

	वापस !!(val & CCU_DIV_CTL_EN);
पूर्ण

अटल अचिन्हित दीर्घ ccu_भाग_var_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);
	अचिन्हित दीर्घ भागider;
	u32 val = 0;

	regmap_पढ़ो(भाग->sys_regs, भाग->reg_ctl, &val);
	भागider = ccu_भाग_get(भाग->mask, val);

	वापस ccu_भाग_calc_freq(parent_rate, भागider);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ccu_भाग_var_calc_भागider(अचिन्हित दीर्घ rate,
						     अचिन्हित दीर्घ parent_rate,
						     अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित दीर्घ भागider;

	भागider = parent_rate / rate;
	वापस clamp_t(अचिन्हित दीर्घ, भागider, CCU_DIV_CLKDIV_MIN,
		       CCU_DIV_CLKDIV_MAX(mask));
पूर्ण

अटल दीर्घ ccu_भाग_var_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);
	अचिन्हित दीर्घ भागider;

	भागider = ccu_भाग_var_calc_भागider(rate, *parent_rate, भाग->mask);

	वापस ccu_भाग_calc_freq(*parent_rate, भागider);
पूर्ण

/*
 * This method is used क्रम the घड़ी भागider blocks, which support the
 * on-the-fly rate change. So due to lacking the EN bit functionality
 * they can't be gated beक्रमe the rate adjusपंचांगent.
 */
अटल पूर्णांक ccu_भाग_var_set_rate_slow(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);
	अचिन्हित दीर्घ flags, भागider;
	u32 val;
	पूर्णांक ret;

	भागider = ccu_भाग_var_calc_भागider(rate, parent_rate, भाग->mask);
	अगर (भागider == 1 && भाग->features & CCU_DIV_SKIP_ONE) अणु
		भागider = 0;
	पूर्ण अन्यथा अगर (भाग->features & CCU_DIV_SKIP_ONE_TO_THREE) अणु
		अगर (भागider == 1 || भागider == 2)
			भागider = 0;
		अन्यथा अगर (भागider == 3)
			भागider = 4;
	पूर्ण

	val = ccu_भाग_prep(भाग->mask, भागider);

	spin_lock_irqsave(&भाग->lock, flags);
	regmap_update_bits(भाग->sys_regs, भाग->reg_ctl, भाग->mask, val);
	ret = ccu_भाग_var_update_clkभाग(भाग, parent_rate, भागider);
	spin_unlock_irqrestore(&भाग->lock, flags);
	अगर (ret)
		pr_err("Divider '%s' lock timed out\n", clk_hw_get_name(hw));

	वापस ret;
पूर्ण

/*
 * This method is used क्रम the घड़ी भागider blocks, which करोn't support
 * the on-the-fly rate change.
 */
अटल पूर्णांक ccu_भाग_var_set_rate_fast(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);
	अचिन्हित दीर्घ flags, भागider;
	u32 val;

	भागider = ccu_भाग_var_calc_भागider(rate, parent_rate, भाग->mask);
	val = ccu_भाग_prep(भाग->mask, भागider);

	/*
	 * Also disable the घड़ी भागider block अगर it was enabled by शेष
	 * or by the bootloader.
	 */
	spin_lock_irqsave(&भाग->lock, flags);
	regmap_update_bits(भाग->sys_regs, भाग->reg_ctl,
			   भाग->mask | CCU_DIV_CTL_EN, val);
	spin_unlock_irqrestore(&भाग->lock, flags);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ ccu_भाग_fixed_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);

	वापस ccu_भाग_calc_freq(parent_rate, भाग->भागider);
पूर्ण

अटल दीर्घ ccu_भाग_fixed_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);

	वापस ccu_भाग_calc_freq(*parent_rate, भाग->भागider);
पूर्ण

अटल पूर्णांक ccu_भाग_fixed_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	वापस 0;
पूर्ण

पूर्णांक ccu_भाग_reset_करोमुख्य(काष्ठा ccu_भाग *भाग)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!भाग || !(भाग->features & CCU_DIV_RESET_DOMAIN))
		वापस -EINVAL;

	spin_lock_irqsave(&भाग->lock, flags);
	regmap_update_bits(भाग->sys_regs, भाग->reg_ctl,
			   CCU_DIV_CTL_RST, CCU_DIV_CTL_RST);
	spin_unlock_irqrestore(&भाग->lock, flags);

	/* The next delay must be enough to cover all the resets. */
	udelay(CCU_DIV_RST_DELAY_US);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

काष्ठा ccu_भाग_dbgfs_bit अणु
	काष्ठा ccu_भाग *भाग;
	स्थिर अक्षर *name;
	u32 mask;
पूर्ण;

#घोषणा CCU_DIV_DBGFS_BIT_ATTR(_name, _mask) अणु	\
		.name = _name,			\
		.mask = _mask			\
	पूर्ण

अटल स्थिर काष्ठा ccu_भाग_dbgfs_bit ccu_भाग_bits[] = अणु
	CCU_DIV_DBGFS_BIT_ATTR("div_en", CCU_DIV_CTL_EN),
	CCU_DIV_DBGFS_BIT_ATTR("div_rst", CCU_DIV_CTL_RST),
	CCU_DIV_DBGFS_BIT_ATTR("div_bypass", CCU_DIV_CTL_SET_CLKDIV),
	CCU_DIV_DBGFS_BIT_ATTR("div_lock", CCU_DIV_CTL_LOCK_NORMAL)
पूर्ण;

#घोषणा CCU_DIV_DBGFS_BIT_NUM	ARRAY_SIZE(ccu_भाग_bits)

/*
 * It can be dangerous to change the Divider settings behind घड़ी framework
 * back, thereक्रमe we करोn't provide any kernel config based compile समय option
 * क्रम this feature to enable.
 */
#अघोषित CCU_DIV_ALLOW_WRITE_DEBUGFS
#अगर_घोषित CCU_DIV_ALLOW_WRITE_DEBUGFS

अटल पूर्णांक ccu_भाग_dbgfs_bit_set(व्योम *priv, u64 val)
अणु
	स्थिर काष्ठा ccu_भाग_dbgfs_bit *bit = priv;
	काष्ठा ccu_भाग *भाग = bit->भाग;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&भाग->lock, flags);
	regmap_update_bits(भाग->sys_regs, भाग->reg_ctl,
			   bit->mask, val ? bit->mask : 0);
	spin_unlock_irqrestore(&भाग->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ccu_भाग_dbgfs_var_clkभाग_set(व्योम *priv, u64 val)
अणु
	काष्ठा ccu_भाग *भाग = priv;
	अचिन्हित दीर्घ flags;
	u32 data;

	val = clamp_t(u64, val, CCU_DIV_CLKDIV_MIN,
		      CCU_DIV_CLKDIV_MAX(भाग->mask));
	data = ccu_भाग_prep(भाग->mask, val);

	spin_lock_irqsave(&भाग->lock, flags);
	regmap_update_bits(भाग->sys_regs, भाग->reg_ctl, भाग->mask, data);
	spin_unlock_irqrestore(&भाग->lock, flags);

	वापस 0;
पूर्ण

#घोषणा ccu_भाग_dbgfs_mode		0644

#अन्यथा /* !CCU_DIV_ALLOW_WRITE_DEBUGFS */

#घोषणा ccu_भाग_dbgfs_bit_set		शून्य
#घोषणा ccu_भाग_dbgfs_var_clkभाग_set	शून्य
#घोषणा ccu_भाग_dbgfs_mode		0444

#पूर्ण_अगर /* !CCU_DIV_ALLOW_WRITE_DEBUGFS */

अटल पूर्णांक ccu_भाग_dbgfs_bit_get(व्योम *priv, u64 *val)
अणु
	स्थिर काष्ठा ccu_भाग_dbgfs_bit *bit = priv;
	काष्ठा ccu_भाग *भाग = bit->भाग;
	u32 data = 0;

	regmap_पढ़ो(भाग->sys_regs, भाग->reg_ctl, &data);
	*val = !!(data & bit->mask);

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(ccu_भाग_dbgfs_bit_fops,
	ccu_भाग_dbgfs_bit_get, ccu_भाग_dbgfs_bit_set, "%llu\n");

अटल पूर्णांक ccu_भाग_dbgfs_var_clkभाग_get(व्योम *priv, u64 *val)
अणु
	काष्ठा ccu_भाग *भाग = priv;
	u32 data = 0;

	regmap_पढ़ो(भाग->sys_regs, भाग->reg_ctl, &data);
	*val = ccu_भाग_get(भाग->mask, data);

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(ccu_भाग_dbgfs_var_clkभाग_fops,
	ccu_भाग_dbgfs_var_clkभाग_get, ccu_भाग_dbgfs_var_clkभाग_set, "%llu\n");

अटल पूर्णांक ccu_भाग_dbgfs_fixed_clkभाग_get(व्योम *priv, u64 *val)
अणु
	काष्ठा ccu_भाग *भाग = priv;

	*val = भाग->भागider;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(ccu_भाग_dbgfs_fixed_clkभाग_fops,
	ccu_भाग_dbgfs_fixed_clkभाग_get, शून्य, "%llu\n");

अटल व्योम ccu_भाग_var_debug_init(काष्ठा clk_hw *hw, काष्ठा dentry *dentry)
अणु
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);
	काष्ठा ccu_भाग_dbgfs_bit *bits;
	पूर्णांक didx, bidx, num = 2;
	स्थिर अक्षर *name;

	num += !!(भाग->flags & CLK_SET_RATE_GATE) +
		!!(भाग->features & CCU_DIV_RESET_DOMAIN);

	bits = kसुस्मृति(num, माप(*bits), GFP_KERNEL);
	अगर (!bits)
		वापस;

	क्रम (didx = 0, bidx = 0; bidx < CCU_DIV_DBGFS_BIT_NUM; ++bidx) अणु
		name = ccu_भाग_bits[bidx].name;
		अगर (!(भाग->flags & CLK_SET_RATE_GATE) &&
		    !म_भेद("div_en", name)) अणु
			जारी;
		पूर्ण

		अगर (!(भाग->features & CCU_DIV_RESET_DOMAIN) &&
		    !म_भेद("div_rst", name)) अणु
			जारी;
		पूर्ण

		bits[didx] = ccu_भाग_bits[bidx];
		bits[didx].भाग = भाग;

		अगर (भाग->features & CCU_DIV_LOCK_SHIFTED &&
		    !म_भेद("div_lock", name)) अणु
			bits[didx].mask = CCU_DIV_CTL_LOCK_SHIFTED;
		पूर्ण

		debugfs_create_file_unsafe(bits[didx].name, ccu_भाग_dbgfs_mode,
					   dentry, &bits[didx],
					   &ccu_भाग_dbgfs_bit_fops);
		++didx;
	पूर्ण

	debugfs_create_file_unsafe("div_clkdiv", ccu_भाग_dbgfs_mode, dentry,
				   भाग, &ccu_भाग_dbgfs_var_clkभाग_fops);
पूर्ण

अटल व्योम ccu_भाग_gate_debug_init(काष्ठा clk_hw *hw, काष्ठा dentry *dentry)
अणु
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);
	काष्ठा ccu_भाग_dbgfs_bit *bit;

	bit = kदो_स्मृति(माप(*bit), GFP_KERNEL);
	अगर (!bit)
		वापस;

	*bit = ccu_भाग_bits[0];
	bit->भाग = भाग;
	debugfs_create_file_unsafe(bit->name, ccu_भाग_dbgfs_mode, dentry, bit,
				   &ccu_भाग_dbgfs_bit_fops);

	debugfs_create_file_unsafe("div_clkdiv", 0400, dentry, भाग,
				   &ccu_भाग_dbgfs_fixed_clkभाग_fops);
पूर्ण

अटल व्योम ccu_भाग_fixed_debug_init(काष्ठा clk_hw *hw, काष्ठा dentry *dentry)
अणु
	काष्ठा ccu_भाग *भाग = to_ccu_भाग(hw);

	debugfs_create_file_unsafe("div_clkdiv", 0400, dentry, भाग,
				   &ccu_भाग_dbgfs_fixed_clkभाग_fops);
पूर्ण

#अन्यथा /* !CONFIG_DEBUG_FS */

#घोषणा ccu_भाग_var_debug_init शून्य
#घोषणा ccu_भाग_gate_debug_init शून्य
#घोषणा ccu_भाग_fixed_debug_init शून्य

#पूर्ण_अगर /* !CONFIG_DEBUG_FS */

अटल स्थिर काष्ठा clk_ops ccu_भाग_var_gate_to_set_ops = अणु
	.enable = ccu_भाग_var_enable,
	.disable = ccu_भाग_gate_disable,
	.is_enabled = ccu_भाग_gate_is_enabled,
	.recalc_rate = ccu_भाग_var_recalc_rate,
	.round_rate = ccu_भाग_var_round_rate,
	.set_rate = ccu_भाग_var_set_rate_fast,
	.debug_init = ccu_भाग_var_debug_init
पूर्ण;

अटल स्थिर काष्ठा clk_ops ccu_भाग_var_nogate_ops = अणु
	.recalc_rate = ccu_भाग_var_recalc_rate,
	.round_rate = ccu_भाग_var_round_rate,
	.set_rate = ccu_भाग_var_set_rate_slow,
	.debug_init = ccu_भाग_var_debug_init
पूर्ण;

अटल स्थिर काष्ठा clk_ops ccu_भाग_gate_ops = अणु
	.enable = ccu_भाग_gate_enable,
	.disable = ccu_भाग_gate_disable,
	.is_enabled = ccu_भाग_gate_is_enabled,
	.recalc_rate = ccu_भाग_fixed_recalc_rate,
	.round_rate = ccu_भाग_fixed_round_rate,
	.set_rate = ccu_भाग_fixed_set_rate,
	.debug_init = ccu_भाग_gate_debug_init
पूर्ण;

अटल स्थिर काष्ठा clk_ops ccu_भाग_fixed_ops = अणु
	.recalc_rate = ccu_भाग_fixed_recalc_rate,
	.round_rate = ccu_भाग_fixed_round_rate,
	.set_rate = ccu_भाग_fixed_set_rate,
	.debug_init = ccu_भाग_fixed_debug_init
पूर्ण;

काष्ठा ccu_भाग *ccu_भाग_hw_रेजिस्टर(स्थिर काष्ठा ccu_भाग_init_data *भाग_init)
अणु
	काष्ठा clk_parent_data parent_data = अणु पूर्ण;
	काष्ठा clk_init_data hw_init = अणु पूर्ण;
	काष्ठा ccu_भाग *भाग;
	पूर्णांक ret;

	अगर (!भाग_init)
		वापस ERR_PTR(-EINVAL);

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * Note since Baikal-T1 System Controller रेजिस्टरs are MMIO-backed
	 * we won't check the regmap IO operations वापस status, because it
	 * must be zero anyway.
	 */
	भाग->hw.init = &hw_init;
	भाग->id = भाग_init->id;
	भाग->reg_ctl = भाग_init->base + CCU_DIV_CTL;
	भाग->sys_regs = भाग_init->sys_regs;
	भाग->flags = भाग_init->flags;
	भाग->features = भाग_init->features;
	spin_lock_init(&भाग->lock);

	hw_init.name = भाग_init->name;
	hw_init.flags = भाग_init->flags;

	अगर (भाग_init->type == CCU_DIV_VAR) अणु
		अगर (hw_init.flags & CLK_SET_RATE_GATE)
			hw_init.ops = &ccu_भाग_var_gate_to_set_ops;
		अन्यथा
			hw_init.ops = &ccu_भाग_var_nogate_ops;
		भाग->mask = CCU_DIV_CTL_CLKDIV_MASK(भाग_init->width);
	पूर्ण अन्यथा अगर (भाग_init->type == CCU_DIV_GATE) अणु
		hw_init.ops = &ccu_भाग_gate_ops;
		भाग->भागider = भाग_init->भागider;
	पूर्ण अन्यथा अगर (भाग_init->type == CCU_DIV_FIXED) अणु
		hw_init.ops = &ccu_भाग_fixed_ops;
		भाग->भागider = भाग_init->भागider;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ err_मुक्त_भाग;
	पूर्ण

	अगर (!भाग_init->parent_name) अणु
		ret = -EINVAL;
		जाओ err_मुक्त_भाग;
	पूर्ण
	parent_data.fw_name = भाग_init->parent_name;
	hw_init.parent_data = &parent_data;
	hw_init.num_parents = 1;

	ret = of_clk_hw_रेजिस्टर(भाग_init->np, &भाग->hw);
	अगर (ret)
		जाओ err_मुक्त_भाग;

	वापस भाग;

err_मुक्त_भाग:
	kमुक्त(भाग);

	वापस ERR_PTR(ret);
पूर्ण

व्योम ccu_भाग_hw_unरेजिस्टर(काष्ठा ccu_भाग *भाग)
अणु
	clk_hw_unरेजिस्टर(&भाग->hw);

	kमुक्त(भाग);
पूर्ण
