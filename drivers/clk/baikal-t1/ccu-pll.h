<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
 *
 * Baikal-T1 CCU PLL पूर्णांकerface driver
 */
#अगर_अघोषित __CLK_BT1_CCU_PLL_H__
#घोषणा __CLK_BT1_CCU_PLL_H__

#समावेश <linux/clk-provider.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bits.h>
#समावेश <linux/of.h>

/*
 * काष्ठा ccu_pll_init_data - CCU PLL initialization data
 * @id: Clock निजी identअगरier.
 * @name: Clocks name.
 * @parent_name: Clocks parent name in a fw node.
 * @base: PLL रेजिस्टरs base address with respect to the sys_regs base.
 * @sys_regs: Baikal-T1 System Controller रेजिस्टरs map.
 * @np: Poपूर्णांकer to the node describing the CCU PLLs.
 * @flags: PLL घड़ी flags.
 */
काष्ठा ccu_pll_init_data अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित पूर्णांक base;
	काष्ठा regmap *sys_regs;
	काष्ठा device_node *np;
	अचिन्हित दीर्घ flags;
पूर्ण;

/*
 * काष्ठा ccu_pll - CCU PLL descriptor
 * @hw: clk_hw of the PLL.
 * @id: Clock निजी identअगरier.
 * @reg_ctl: PLL control रेजिस्टर base.
 * @reg_ctl1: PLL control1 रेजिस्टर base.
 * @sys_regs: Baikal-T1 System Controller रेजिस्टरs map.
 * @lock: PLL state change spin-lock.
 */
काष्ठा ccu_pll अणु
	काष्ठा clk_hw hw;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक reg_ctl;
	अचिन्हित पूर्णांक reg_ctl1;
	काष्ठा regmap *sys_regs;
	spinlock_t lock;
पूर्ण;
#घोषणा to_ccu_pll(_hw) container_of(_hw, काष्ठा ccu_pll, hw)

अटल अंतरभूत काष्ठा clk_hw *ccu_pll_get_clk_hw(काष्ठा ccu_pll *pll)
अणु
	वापस pll ? &pll->hw : शून्य;
पूर्ण

काष्ठा ccu_pll *ccu_pll_hw_रेजिस्टर(स्थिर काष्ठा ccu_pll_init_data *init);

व्योम ccu_pll_hw_unरेजिस्टर(काष्ठा ccu_pll *pll);

#पूर्ण_अगर /* __CLK_BT1_CCU_PLL_H__ */
