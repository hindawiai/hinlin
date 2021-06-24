<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
 *
 * Baikal-T1 CCU Dividers पूर्णांकerface driver
 */
#अगर_अघोषित __CLK_BT1_CCU_DIV_H__
#घोषणा __CLK_BT1_CCU_DIV_H__

#समावेश <linux/clk-provider.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bits.h>
#समावेश <linux/of.h>

/*
 * CCU Divider निजी flags
 * @CCU_DIV_SKIP_ONE: Due to some reason भागider can't be set to 1.
 *		      It can be 0 though, which is functionally the same.
 * @CCU_DIV_SKIP_ONE_TO_THREE: For some reason भागider can't be within [1,3].
 *			       It can be either 0 or greater than 3.
 * @CCU_DIV_LOCK_SHIFTED: Find lock-bit at non-standard position.
 * @CCU_DIV_RESET_DOMAIN: Provide reset घड़ी करोमुख्य method.
 */
#घोषणा CCU_DIV_SKIP_ONE		BIT(1)
#घोषणा CCU_DIV_SKIP_ONE_TO_THREE	BIT(2)
#घोषणा CCU_DIV_LOCK_SHIFTED		BIT(3)
#घोषणा CCU_DIV_RESET_DOMAIN		BIT(4)

/*
 * क्रमागत ccu_भाग_प्रकारype - CCU Divider types
 * @CCU_DIV_VAR: Clocks gate with variable भागider.
 * @CCU_DIV_GATE: Clocks gate with fixed भागider.
 * @CCU_DIV_FIXED: Ungateable घड़ी with fixed भागider.
 */
क्रमागत ccu_भाग_प्रकारype अणु
	CCU_DIV_VAR,
	CCU_DIV_GATE,
	CCU_DIV_FIXED
पूर्ण;

/*
 * काष्ठा ccu_भाग_init_data - CCU Divider initialization data
 * @id: Clocks निजी identअगरier.
 * @name: Clocks name.
 * @parent_name: Parent घड़ीs name in a fw node.
 * @base: Divider रेजिस्टर base address with respect to the sys_regs base.
 * @sys_regs: Baikal-T1 System Controller रेजिस्टरs map.
 * @np: Poपूर्णांकer to the node describing the CCU Dividers.
 * @type: CCU भागider type (variable, fixed with and without gate).
 * @width: Divider width अगर it's variable.
 * @भागider: Divider fixed value.
 * @flags: CCU Divider घड़ी flags.
 * @features: CCU Divider निजी features.
 */
काष्ठा ccu_भाग_init_data अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित पूर्णांक base;
	काष्ठा regmap *sys_regs;
	काष्ठा device_node *np;
	क्रमागत ccu_भाग_प्रकारype type;
	जोड़ अणु
		अचिन्हित पूर्णांक width;
		अचिन्हित पूर्णांक भागider;
	पूर्ण;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ features;
पूर्ण;

/*
 * काष्ठा ccu_भाग - CCU Divider descriptor
 * @hw: clk_hw of the भागider.
 * @id: Clock निजी identअगरier.
 * @reg_ctl: Divider control रेजिस्टर base address.
 * @sys_regs: Baikal-T1 System Controller रेजिस्टरs map.
 * @lock: Divider state change spin-lock.
 * @mask: Divider field mask.
 * @भागider: Divider fixed value.
 * @flags: Divider घड़ी flags.
 * @features: CCU Divider निजी features.
 */
काष्ठा ccu_भाग अणु
	काष्ठा clk_hw hw;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक reg_ctl;
	काष्ठा regmap *sys_regs;
	spinlock_t lock;
	जोड़ अणु
		u32 mask;
		अचिन्हित पूर्णांक भागider;
	पूर्ण;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ features;
पूर्ण;
#घोषणा to_ccu_भाग(_hw) container_of(_hw, काष्ठा ccu_भाग, hw)

अटल अंतरभूत काष्ठा clk_hw *ccu_भाग_get_clk_hw(काष्ठा ccu_भाग *भाग)
अणु
	वापस भाग ? &भाग->hw : शून्य;
पूर्ण

काष्ठा ccu_भाग *ccu_भाग_hw_रेजिस्टर(स्थिर काष्ठा ccu_भाग_init_data *init);

व्योम ccu_भाग_hw_unरेजिस्टर(काष्ठा ccu_भाग *भाग);

पूर्णांक ccu_भाग_reset_करोमुख्य(काष्ठा ccu_भाग *भाग);

#पूर्ण_अगर /* __CLK_BT1_CCU_DIV_H__ */
