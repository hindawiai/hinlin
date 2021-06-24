<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2016 Rockchip Electronics Co. Ltd.
 * Author: Lin Huang <hl@rock-chips.com>
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <soc/rockchip/rockchip_sip.h>
#समावेश "clk.h"

काष्ठा rockchip_ddrclk अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg_base;
	पूर्णांक		mux_offset;
	पूर्णांक		mux_shअगरt;
	पूर्णांक		mux_width;
	पूर्णांक		भाग_shअगरt;
	पूर्णांक		भाग_width;
	पूर्णांक		ddr_flag;
	spinlock_t	*lock;
पूर्ण;

#घोषणा to_rockchip_ddrclk_hw(hw) container_of(hw, काष्ठा rockchip_ddrclk, hw)

अटल पूर्णांक rockchip_ddrclk_sip_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
					अचिन्हित दीर्घ prate)
अणु
	काष्ठा rockchip_ddrclk *ddrclk = to_rockchip_ddrclk_hw(hw);
	अचिन्हित दीर्घ flags;
	काष्ठा arm_smccc_res res;

	spin_lock_irqsave(ddrclk->lock, flags);
	arm_smccc_smc(ROCKCHIP_SIP_DRAM_FREQ, drate, 0,
		      ROCKCHIP_SIP_CONFIG_DRAM_SET_RATE,
		      0, 0, 0, 0, &res);
	spin_unlock_irqrestore(ddrclk->lock, flags);

	वापस res.a0;
पूर्ण

अटल अचिन्हित दीर्घ
rockchip_ddrclk_sip_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(ROCKCHIP_SIP_DRAM_FREQ, 0, 0,
		      ROCKCHIP_SIP_CONFIG_DRAM_GET_RATE,
		      0, 0, 0, 0, &res);

	वापस res.a0;
पूर्ण

अटल दीर्घ rockchip_ddrclk_sip_round_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ rate,
					   अचिन्हित दीर्घ *prate)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(ROCKCHIP_SIP_DRAM_FREQ, rate, 0,
		      ROCKCHIP_SIP_CONFIG_DRAM_ROUND_RATE,
		      0, 0, 0, 0, &res);

	वापस res.a0;
पूर्ण

अटल u8 rockchip_ddrclk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_ddrclk *ddrclk = to_rockchip_ddrclk_hw(hw);
	u32 val;

	val = पढ़ोl(ddrclk->reg_base +
			ddrclk->mux_offset) >> ddrclk->mux_shअगरt;
	val &= GENMASK(ddrclk->mux_width - 1, 0);

	वापस val;
पूर्ण

अटल स्थिर काष्ठा clk_ops rockchip_ddrclk_sip_ops = अणु
	.recalc_rate = rockchip_ddrclk_sip_recalc_rate,
	.set_rate = rockchip_ddrclk_sip_set_rate,
	.round_rate = rockchip_ddrclk_sip_round_rate,
	.get_parent = rockchip_ddrclk_get_parent,
पूर्ण;

काष्ठा clk *rockchip_clk_रेजिस्टर_ddrclk(स्थिर अक्षर *name, पूर्णांक flags,
					 स्थिर अक्षर *स्थिर *parent_names,
					 u8 num_parents, पूर्णांक mux_offset,
					 पूर्णांक mux_shअगरt, पूर्णांक mux_width,
					 पूर्णांक भाग_shअगरt, पूर्णांक भाग_width,
					 पूर्णांक ddr_flag, व्योम __iomem *reg_base,
					 spinlock_t *lock)
अणु
	काष्ठा rockchip_ddrclk *ddrclk;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;

	ddrclk = kzalloc(माप(*ddrclk), GFP_KERNEL);
	अगर (!ddrclk)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	init.flags = flags;
	init.flags |= CLK_SET_RATE_NO_REPARENT;

	चयन (ddr_flag) अणु
	हाल ROCKCHIP_DDRCLK_SIP:
		init.ops = &rockchip_ddrclk_sip_ops;
		अवरोध;
	शेष:
		pr_err("%s: unsupported ddrclk type %d\n", __func__, ddr_flag);
		kमुक्त(ddrclk);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ddrclk->reg_base = reg_base;
	ddrclk->lock = lock;
	ddrclk->hw.init = &init;
	ddrclk->mux_offset = mux_offset;
	ddrclk->mux_shअगरt = mux_shअगरt;
	ddrclk->mux_width = mux_width;
	ddrclk->भाग_shअगरt = भाग_shअगरt;
	ddrclk->भाग_width = भाग_width;
	ddrclk->ddr_flag = ddr_flag;

	clk = clk_रेजिस्टर(शून्य, &ddrclk->hw);
	अगर (IS_ERR(clk))
		kमुक्त(ddrclk);

	वापस clk;
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_clk_रेजिस्टर_ddrclk);
