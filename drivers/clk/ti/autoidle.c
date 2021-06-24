<शैली गुरु>
/*
 * TI घड़ी स्वतःidle support
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * Tero Kristo <t-kristo@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/ti.h>

#समावेश "clock.h"

काष्ठा clk_ti_स्वतःidle अणु
	काष्ठा clk_omap_reg	reg;
	u8			shअगरt;
	u8			flags;
	स्थिर अक्षर		*name;
	काष्ठा list_head	node;
पूर्ण;

#घोषणा AUTOIDLE_LOW		0x1

अटल LIST_HEAD(स्वतःidle_clks);

/*
 * we have some non-atomic पढ़ो/ग_लिखो
 * operations behind it, so lets
 * take one lock क्रम handling स्वतःidle
 * of all घड़ीs
 */
अटल DEFINE_SPINLOCK(स्वतःidle_spinlock);

अटल पूर्णांक _omap2_clk_deny_idle(काष्ठा clk_hw_omap *clk)
अणु
	अगर (clk->ops && clk->ops->deny_idle) अणु
		अचिन्हित दीर्घ irqflags;

		spin_lock_irqsave(&स्वतःidle_spinlock, irqflags);
		clk->स्वतःidle_count++;
		अगर (clk->स्वतःidle_count == 1)
			clk->ops->deny_idle(clk);

		spin_unlock_irqrestore(&स्वतःidle_spinlock, irqflags);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _omap2_clk_allow_idle(काष्ठा clk_hw_omap *clk)
अणु
	अगर (clk->ops && clk->ops->allow_idle) अणु
		अचिन्हित दीर्घ irqflags;

		spin_lock_irqsave(&स्वतःidle_spinlock, irqflags);
		clk->स्वतःidle_count--;
		अगर (clk->स्वतःidle_count == 0)
			clk->ops->allow_idle(clk);

		spin_unlock_irqrestore(&स्वतःidle_spinlock, irqflags);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * omap2_clk_deny_idle - disable स्वतःidle on an OMAP घड़ी
 * @clk: काष्ठा clk * to disable स्वतःidle क्रम
 *
 * Disable स्वतःidle on an OMAP घड़ी.
 */
पूर्णांक omap2_clk_deny_idle(काष्ठा clk *clk)
अणु
	काष्ठा clk_hw *hw;

	अगर (!clk)
		वापस -EINVAL;

	hw = __clk_get_hw(clk);

	अगर (omap2_clk_is_hw_omap(hw)) अणु
		काष्ठा clk_hw_omap *c = to_clk_hw_omap(hw);

		वापस _omap2_clk_deny_idle(c);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * omap2_clk_allow_idle - enable स्वतःidle on an OMAP घड़ी
 * @clk: काष्ठा clk * to enable स्वतःidle क्रम
 *
 * Enable स्वतःidle on an OMAP घड़ी.
 */
पूर्णांक omap2_clk_allow_idle(काष्ठा clk *clk)
अणु
	काष्ठा clk_hw *hw;

	अगर (!clk)
		वापस -EINVAL;

	hw = __clk_get_hw(clk);

	अगर (omap2_clk_is_hw_omap(hw)) अणु
		काष्ठा clk_hw_omap *c = to_clk_hw_omap(hw);

		वापस _omap2_clk_allow_idle(c);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम _allow_स्वतःidle(काष्ठा clk_ti_स्वतःidle *clk)
अणु
	u32 val;

	val = ti_clk_ll_ops->clk_पढ़ोl(&clk->reg);

	अगर (clk->flags & AUTOIDLE_LOW)
		val &= ~(1 << clk->shअगरt);
	अन्यथा
		val |= (1 << clk->shअगरt);

	ti_clk_ll_ops->clk_ग_लिखोl(val, &clk->reg);
पूर्ण

अटल व्योम _deny_स्वतःidle(काष्ठा clk_ti_स्वतःidle *clk)
अणु
	u32 val;

	val = ti_clk_ll_ops->clk_पढ़ोl(&clk->reg);

	अगर (clk->flags & AUTOIDLE_LOW)
		val |= (1 << clk->shअगरt);
	अन्यथा
		val &= ~(1 << clk->shअगरt);

	ti_clk_ll_ops->clk_ग_लिखोl(val, &clk->reg);
पूर्ण

/**
 * _clk_generic_allow_स्वतःidle_all - enable स्वतःidle क्रम all घड़ीs
 *
 * Enables hardware स्वतःidle क्रम all रेजिस्टरed DT घड़ीs, which have
 * the feature.
 */
अटल व्योम _clk_generic_allow_स्वतःidle_all(व्योम)
अणु
	काष्ठा clk_ti_स्वतःidle *c;

	list_क्रम_each_entry(c, &स्वतःidle_clks, node)
		_allow_स्वतःidle(c);
पूर्ण

/**
 * _clk_generic_deny_स्वतःidle_all - disable स्वतःidle क्रम all घड़ीs
 *
 * Disables hardware स्वतःidle क्रम all रेजिस्टरed DT घड़ीs, which have
 * the feature.
 */
अटल व्योम _clk_generic_deny_स्वतःidle_all(व्योम)
अणु
	काष्ठा clk_ti_स्वतःidle *c;

	list_क्रम_each_entry(c, &स्वतःidle_clks, node)
		_deny_स्वतःidle(c);
पूर्ण

/**
 * of_ti_clk_स्वतःidle_setup - sets up hardware स्वतःidle क्रम a घड़ी
 * @node: poपूर्णांकer to the घड़ी device node
 *
 * Checks अगर a घड़ी has hardware स्वतःidle support or not (check
 * क्रम presence of 'ti,autoidle-shift' property in the device tree
 * node) and sets up the hardware स्वतःidle feature क्रम the घड़ी
 * अगर available. If स्वतःidle is available, the घड़ी is also added
 * to the स्वतःidle list क्रम later processing. Returns 0 on success,
 * negative error value on failure.
 */
पूर्णांक __init of_ti_clk_स्वतःidle_setup(काष्ठा device_node *node)
अणु
	u32 shअगरt;
	काष्ठा clk_ti_स्वतःidle *clk;
	पूर्णांक ret;

	/* Check अगर this घड़ी has स्वतःidle support or not */
	अगर (of_property_पढ़ो_u32(node, "ti,autoidle-shift", &shअगरt))
		वापस 0;

	clk = kzalloc(माप(*clk), GFP_KERNEL);

	अगर (!clk)
		वापस -ENOMEM;

	clk->shअगरt = shअगरt;
	clk->name = node->name;
	ret = ti_clk_get_reg_addr(node, 0, &clk->reg);
	अगर (ret) अणु
		kमुक्त(clk);
		वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_bool(node, "ti,invert-autoidle-bit"))
		clk->flags |= AUTOIDLE_LOW;

	list_add(&clk->node, &स्वतःidle_clks);

	वापस 0;
पूर्ण

/**
 * omap2_clk_enable_स्वतःidle_all - enable स्वतःidle on all OMAP घड़ीs that
 * support it
 *
 * Enable घड़ी स्वतःidle on all OMAP घड़ीs that have allow_idle
 * function poपूर्णांकers associated with them.  This function is पूर्णांकended
 * to be temporary until support क्रम this is added to the common घड़ी
 * code.  Returns 0.
 */
पूर्णांक omap2_clk_enable_स्वतःidle_all(व्योम)
अणु
	पूर्णांक ret;

	ret = omap2_clk_क्रम_each(_omap2_clk_allow_idle);
	अगर (ret)
		वापस ret;

	_clk_generic_allow_स्वतःidle_all();

	वापस 0;
पूर्ण

/**
 * omap2_clk_disable_स्वतःidle_all - disable स्वतःidle on all OMAP घड़ीs that
 * support it
 *
 * Disable घड़ी स्वतःidle on all OMAP घड़ीs that have allow_idle
 * function poपूर्णांकers associated with them.  This function is पूर्णांकended
 * to be temporary until support क्रम this is added to the common घड़ी
 * code.  Returns 0.
 */
पूर्णांक omap2_clk_disable_स्वतःidle_all(व्योम)
अणु
	पूर्णांक ret;

	ret = omap2_clk_क्रम_each(_omap2_clk_deny_idle);
	अगर (ret)
		वापस ret;

	_clk_generic_deny_स्वतःidle_all();

	वापस 0;
पूर्ण
