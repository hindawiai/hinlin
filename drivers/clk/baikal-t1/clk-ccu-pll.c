<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
 *
 * Authors:
 *   Serge Semin <Sergey.Semin@baikalelectronics.ru>
 *   Dmitry Dunaev <dmitry.dunaev@baikalelectronics.ru>
 *
 * Baikal-T1 CCU PLL घड़ीs driver
 */

#घोषणा pr_fmt(fmt) "bt1-ccu-pll: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/ioport.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/bt1-ccu.h>

#समावेश "ccu-pll.h"

#घोषणा CCU_CPU_PLL_BASE		0x000
#घोषणा CCU_SATA_PLL_BASE		0x008
#घोषणा CCU_DDR_PLL_BASE		0x010
#घोषणा CCU_PCIE_PLL_BASE		0x018
#घोषणा CCU_ETH_PLL_BASE		0x020

#घोषणा CCU_PLL_INFO(_id, _name, _pname, _base, _flags)	\
	अणु						\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _pname,			\
		.base = _base,				\
		.flags = _flags				\
	पूर्ण

#घोषणा CCU_PLL_NUM			ARRAY_SIZE(pll_info)

काष्ठा ccu_pll_info अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित पूर्णांक base;
	अचिन्हित दीर्घ flags;
पूर्ण;

/*
 * Alas we have to mark all PLLs as critical. CPU and DDR PLLs are sources of
 * CPU cores and DDR controller reference घड़ीs, due to which they obviously
 * shouldn't be ever gated. SATA and PCIe PLLs are the parents of APB-bus and
 * DDR controller AXI-bus घड़ीs. If they are gated the प्रणाली will be
 * unusable. Moreover disabling SATA and Ethernet PLLs causes स्वतःmatic reset
 * of the corresponding subप्रणालीs. So until we aren't पढ़ोy to re-initialize
 * all the devices consuming those PLLs, they will be marked as critical too.
 */
अटल स्थिर काष्ठा ccu_pll_info pll_info[] = अणु
	CCU_PLL_INFO(CCU_CPU_PLL, "cpu_pll", "ref_clk", CCU_CPU_PLL_BASE,
		     CLK_IS_CRITICAL),
	CCU_PLL_INFO(CCU_SATA_PLL, "sata_pll", "ref_clk", CCU_SATA_PLL_BASE,
		     CLK_IS_CRITICAL | CLK_SET_RATE_GATE),
	CCU_PLL_INFO(CCU_DDR_PLL, "ddr_pll", "ref_clk", CCU_DDR_PLL_BASE,
		     CLK_IS_CRITICAL | CLK_SET_RATE_GATE),
	CCU_PLL_INFO(CCU_PCIE_PLL, "pcie_pll", "ref_clk", CCU_PCIE_PLL_BASE,
		     CLK_IS_CRITICAL),
	CCU_PLL_INFO(CCU_ETH_PLL, "eth_pll", "ref_clk", CCU_ETH_PLL_BASE,
		     CLK_IS_CRITICAL | CLK_SET_RATE_GATE)
पूर्ण;

काष्ठा ccu_pll_data अणु
	काष्ठा device_node *np;
	काष्ठा regmap *sys_regs;
	काष्ठा ccu_pll *plls[CCU_PLL_NUM];
पूर्ण;

अटल काष्ठा ccu_pll *ccu_pll_find_desc(काष्ठा ccu_pll_data *data,
					 अचिन्हित पूर्णांक clk_id)
अणु
	काष्ठा ccu_pll *pll;
	पूर्णांक idx;

	क्रम (idx = 0; idx < CCU_PLL_NUM; ++idx) अणु
		pll = data->plls[idx];
		अगर (pll && pll->id == clk_id)
			वापस pll;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा ccu_pll_data *ccu_pll_create_data(काष्ठा device_node *np)
अणु
	काष्ठा ccu_pll_data *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	data->np = np;

	वापस data;
पूर्ण

अटल व्योम ccu_pll_मुक्त_data(काष्ठा ccu_pll_data *data)
अणु
	kमुक्त(data);
पूर्ण

अटल पूर्णांक ccu_pll_find_sys_regs(काष्ठा ccu_pll_data *data)
अणु
	data->sys_regs = syscon_node_to_regmap(data->np->parent);
	अगर (IS_ERR(data->sys_regs)) अणु
		pr_err("Failed to find syscon regs for '%s'\n",
			of_node_full_name(data->np));
		वापस PTR_ERR(data->sys_regs);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा clk_hw *ccu_pll_of_clk_hw_get(काष्ठा of_phandle_args *clkspec,
					    व्योम *priv)
अणु
	काष्ठा ccu_pll_data *data = priv;
	काष्ठा ccu_pll *pll;
	अचिन्हित पूर्णांक clk_id;

	clk_id = clkspec->args[0];
	pll = ccu_pll_find_desc(data, clk_id);
	अगर (IS_ERR(pll)) अणु
		pr_info("Invalid PLL clock ID %d specified\n", clk_id);
		वापस ERR_CAST(pll);
	पूर्ण

	वापस ccu_pll_get_clk_hw(pll);
पूर्ण

अटल पूर्णांक ccu_pll_clk_रेजिस्टर(काष्ठा ccu_pll_data *data)
अणु
	पूर्णांक idx, ret;

	क्रम (idx = 0; idx < CCU_PLL_NUM; ++idx) अणु
		स्थिर काष्ठा ccu_pll_info *info = &pll_info[idx];
		काष्ठा ccu_pll_init_data init = अणु0पूर्ण;

		init.id = info->id;
		init.name = info->name;
		init.parent_name = info->parent_name;
		init.base = info->base;
		init.sys_regs = data->sys_regs;
		init.np = data->np;
		init.flags = info->flags;

		data->plls[idx] = ccu_pll_hw_रेजिस्टर(&init);
		अगर (IS_ERR(data->plls[idx])) अणु
			ret = PTR_ERR(data->plls[idx]);
			pr_err("Couldn't register PLL hw '%s'\n",
				init.name);
			जाओ err_hw_unरेजिस्टर;
		पूर्ण
	पूर्ण

	ret = of_clk_add_hw_provider(data->np, ccu_pll_of_clk_hw_get, data);
	अगर (ret) अणु
		pr_err("Couldn't register PLL provider of '%s'\n",
			of_node_full_name(data->np));
		जाओ err_hw_unरेजिस्टर;
	पूर्ण

	वापस 0;

err_hw_unरेजिस्टर:
	क्रम (--idx; idx >= 0; --idx)
		ccu_pll_hw_unरेजिस्टर(data->plls[idx]);

	वापस ret;
पूर्ण

अटल __init व्योम ccu_pll_init(काष्ठा device_node *np)
अणु
	काष्ठा ccu_pll_data *data;
	पूर्णांक ret;

	data = ccu_pll_create_data(np);
	अगर (IS_ERR(data))
		वापस;

	ret = ccu_pll_find_sys_regs(data);
	अगर (ret)
		जाओ err_मुक्त_data;

	ret = ccu_pll_clk_रेजिस्टर(data);
	अगर (ret)
		जाओ err_मुक्त_data;

	वापस;

err_मुक्त_data:
	ccu_pll_मुक्त_data(data);
पूर्ण
CLK_OF_DECLARE(ccu_pll, "baikal,bt1-ccu-pll", ccu_pll_init);
