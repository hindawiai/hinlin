<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
 *
 * Authors:
 *   Serge Semin <Sergey.Semin@baikalelectronics.ru>
 *   Dmitry Dunaev <dmitry.dunaev@baikalelectronics.ru>
 *
 * Baikal-T1 CCU Dividers घड़ी driver
 */

#घोषणा pr_fmt(fmt) "bt1-ccu-div: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/ioport.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/bt1-ccu.h>
#समावेश <dt-bindings/reset/bt1-ccu.h>

#समावेश "ccu-div.h"

#घोषणा CCU_AXI_MAIN_BASE		0x030
#घोषणा CCU_AXI_DDR_BASE		0x034
#घोषणा CCU_AXI_SATA_BASE		0x038
#घोषणा CCU_AXI_GMAC0_BASE		0x03C
#घोषणा CCU_AXI_GMAC1_BASE		0x040
#घोषणा CCU_AXI_XGMAC_BASE		0x044
#घोषणा CCU_AXI_PCIE_M_BASE		0x048
#घोषणा CCU_AXI_PCIE_S_BASE		0x04C
#घोषणा CCU_AXI_USB_BASE		0x050
#घोषणा CCU_AXI_HWA_BASE		0x054
#घोषणा CCU_AXI_SRAM_BASE		0x058

#घोषणा CCU_SYS_SATA_REF_BASE		0x060
#घोषणा CCU_SYS_APB_BASE		0x064
#घोषणा CCU_SYS_GMAC0_BASE		0x068
#घोषणा CCU_SYS_GMAC1_BASE		0x06C
#घोषणा CCU_SYS_XGMAC_BASE		0x070
#घोषणा CCU_SYS_USB_BASE		0x074
#घोषणा CCU_SYS_PVT_BASE		0x078
#घोषणा CCU_SYS_HWA_BASE		0x07C
#घोषणा CCU_SYS_UART_BASE		0x084
#घोषणा CCU_SYS_TIMER0_BASE		0x088
#घोषणा CCU_SYS_TIMER1_BASE		0x08C
#घोषणा CCU_SYS_TIMER2_BASE		0x090
#घोषणा CCU_SYS_WDT_BASE		0x150

#घोषणा CCU_DIV_VAR_INFO(_id, _name, _pname, _base, _width, _flags, _features) \
	अणु								\
		.id = _id,						\
		.name = _name,						\
		.parent_name = _pname,					\
		.base = _base,						\
		.type = CCU_DIV_VAR,					\
		.width = _width,					\
		.flags = _flags,					\
		.features = _features					\
	पूर्ण

#घोषणा CCU_DIV_GATE_INFO(_id, _name, _pname, _base, _भागider)	\
	अणु							\
		.id = _id,					\
		.name = _name,					\
		.parent_name = _pname,				\
		.base = _base,					\
		.type = CCU_DIV_GATE,				\
		.भागider = _भागider				\
	पूर्ण

#घोषणा CCU_DIV_FIXED_INFO(_id, _name, _pname, _भागider)	\
	अणु							\
		.id = _id,					\
		.name = _name,					\
		.parent_name = _pname,				\
		.type = CCU_DIV_FIXED,				\
		.भागider = _भागider				\
	पूर्ण

#घोषणा CCU_DIV_RST_MAP(_rst_id, _clk_id)	\
	अणु					\
		.rst_id = _rst_id,		\
		.clk_id = _clk_id		\
	पूर्ण

काष्ठा ccu_भाग_info अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित पूर्णांक base;
	क्रमागत ccu_भाग_प्रकारype type;
	जोड़ अणु
		अचिन्हित पूर्णांक width;
		अचिन्हित पूर्णांक भागider;
	पूर्ण;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ features;
पूर्ण;

काष्ठा ccu_भाग_rst_map अणु
	अचिन्हित पूर्णांक rst_id;
	अचिन्हित पूर्णांक clk_id;
पूर्ण;

काष्ठा ccu_भाग_data अणु
	काष्ठा device_node *np;
	काष्ठा regmap *sys_regs;

	अचिन्हित पूर्णांक भागs_num;
	स्थिर काष्ठा ccu_भाग_info *भागs_info;
	काष्ठा ccu_भाग **भागs;

	अचिन्हित पूर्णांक rst_num;
	स्थिर काष्ठा ccu_भाग_rst_map *rst_map;
	काष्ठा reset_controller_dev rcdev;
पूर्ण;
#घोषणा to_ccu_भाग_data(_rcdev) container_of(_rcdev, काष्ठा ccu_भाग_data, rcdev)

/*
 * AXI Main Interconnect (axi_मुख्य_clk) and DDR AXI-bus (axi_ddr_clk) घड़ीs
 * must be left enabled in any हाल, since क्रमmer one is responsible क्रम
 * घड़ीing a bus between CPU cores and the rest of the SoC components, जबतक
 * the later is घड़ीing the AXI-bus between DDR controller and the Main
 * Interconnect. So should any of these घड़ीs get to be disabled, the प्रणाली
 * will literally stop working. That's why we marked them as critical.
 */
अटल स्थिर काष्ठा ccu_भाग_info axi_info[] = अणु
	CCU_DIV_VAR_INFO(CCU_AXI_MAIN_CLK, "axi_main_clk", "pcie_clk",
			 CCU_AXI_MAIN_BASE, 4,
			 CLK_IS_CRITICAL, CCU_DIV_RESET_DOMAIN),
	CCU_DIV_VAR_INFO(CCU_AXI_DDR_CLK, "axi_ddr_clk", "sata_clk",
			 CCU_AXI_DDR_BASE, 4,
			 CLK_IS_CRITICAL | CLK_SET_RATE_GATE,
			 CCU_DIV_RESET_DOMAIN),
	CCU_DIV_VAR_INFO(CCU_AXI_SATA_CLK, "axi_sata_clk", "sata_clk",
			 CCU_AXI_SATA_BASE, 4,
			 CLK_SET_RATE_GATE, CCU_DIV_RESET_DOMAIN),
	CCU_DIV_VAR_INFO(CCU_AXI_GMAC0_CLK, "axi_gmac0_clk", "eth_clk",
			 CCU_AXI_GMAC0_BASE, 4,
			 CLK_SET_RATE_GATE, CCU_DIV_RESET_DOMAIN),
	CCU_DIV_VAR_INFO(CCU_AXI_GMAC1_CLK, "axi_gmac1_clk", "eth_clk",
			 CCU_AXI_GMAC1_BASE, 4,
			 CLK_SET_RATE_GATE, CCU_DIV_RESET_DOMAIN),
	CCU_DIV_VAR_INFO(CCU_AXI_XGMAC_CLK, "axi_xgmac_clk", "eth_clk",
			 CCU_AXI_XGMAC_BASE, 4,
			 CLK_SET_RATE_GATE, CCU_DIV_RESET_DOMAIN),
	CCU_DIV_VAR_INFO(CCU_AXI_PCIE_M_CLK, "axi_pcie_m_clk", "pcie_clk",
			 CCU_AXI_PCIE_M_BASE, 4,
			 CLK_SET_RATE_GATE, CCU_DIV_RESET_DOMAIN),
	CCU_DIV_VAR_INFO(CCU_AXI_PCIE_S_CLK, "axi_pcie_s_clk", "pcie_clk",
			 CCU_AXI_PCIE_S_BASE, 4,
			 CLK_SET_RATE_GATE, CCU_DIV_RESET_DOMAIN),
	CCU_DIV_VAR_INFO(CCU_AXI_USB_CLK, "axi_usb_clk", "sata_clk",
			 CCU_AXI_USB_BASE, 4,
			 CLK_SET_RATE_GATE, CCU_DIV_RESET_DOMAIN),
	CCU_DIV_VAR_INFO(CCU_AXI_HWA_CLK, "axi_hwa_clk", "sata_clk",
			 CCU_AXI_HWA_BASE, 4,
			 CLK_SET_RATE_GATE, CCU_DIV_RESET_DOMAIN),
	CCU_DIV_VAR_INFO(CCU_AXI_SRAM_CLK, "axi_sram_clk", "eth_clk",
			 CCU_AXI_SRAM_BASE, 4,
			 CLK_SET_RATE_GATE, CCU_DIV_RESET_DOMAIN)
पूर्ण;

अटल स्थिर काष्ठा ccu_भाग_rst_map axi_rst_map[] = अणु
	CCU_DIV_RST_MAP(CCU_AXI_MAIN_RST, CCU_AXI_MAIN_CLK),
	CCU_DIV_RST_MAP(CCU_AXI_DDR_RST, CCU_AXI_DDR_CLK),
	CCU_DIV_RST_MAP(CCU_AXI_SATA_RST, CCU_AXI_SATA_CLK),
	CCU_DIV_RST_MAP(CCU_AXI_GMAC0_RST, CCU_AXI_GMAC0_CLK),
	CCU_DIV_RST_MAP(CCU_AXI_GMAC1_RST, CCU_AXI_GMAC1_CLK),
	CCU_DIV_RST_MAP(CCU_AXI_XGMAC_RST, CCU_AXI_XGMAC_CLK),
	CCU_DIV_RST_MAP(CCU_AXI_PCIE_M_RST, CCU_AXI_PCIE_M_CLK),
	CCU_DIV_RST_MAP(CCU_AXI_PCIE_S_RST, CCU_AXI_PCIE_S_CLK),
	CCU_DIV_RST_MAP(CCU_AXI_USB_RST, CCU_AXI_USB_CLK),
	CCU_DIV_RST_MAP(CCU_AXI_HWA_RST, CCU_AXI_HWA_CLK),
	CCU_DIV_RST_MAP(CCU_AXI_SRAM_RST, CCU_AXI_SRAM_CLK)
पूर्ण;

/*
 * APB-bus घड़ी is marked as critical since it's a मुख्य communication bus
 * क्रम the SoC devices रेजिस्टरs IO-operations.
 */
अटल स्थिर काष्ठा ccu_भाग_info sys_info[] = अणु
	CCU_DIV_VAR_INFO(CCU_SYS_SATA_REF_CLK, "sys_sata_ref_clk",
			 "sata_clk", CCU_SYS_SATA_REF_BASE, 4,
			 CLK_SET_RATE_GATE,
			 CCU_DIV_SKIP_ONE | CCU_DIV_LOCK_SHIFTED |
			 CCU_DIV_RESET_DOMAIN),
	CCU_DIV_VAR_INFO(CCU_SYS_APB_CLK, "sys_apb_clk",
			 "pcie_clk", CCU_SYS_APB_BASE, 5,
			 CLK_IS_CRITICAL, CCU_DIV_RESET_DOMAIN),
	CCU_DIV_GATE_INFO(CCU_SYS_GMAC0_TX_CLK, "sys_gmac0_tx_clk",
			  "eth_clk", CCU_SYS_GMAC0_BASE, 5),
	CCU_DIV_FIXED_INFO(CCU_SYS_GMAC0_PTP_CLK, "sys_gmac0_ptp_clk",
			   "eth_clk", 10),
	CCU_DIV_GATE_INFO(CCU_SYS_GMAC1_TX_CLK, "sys_gmac1_tx_clk",
			  "eth_clk", CCU_SYS_GMAC1_BASE, 5),
	CCU_DIV_FIXED_INFO(CCU_SYS_GMAC1_PTP_CLK, "sys_gmac1_ptp_clk",
			   "eth_clk", 10),
	CCU_DIV_GATE_INFO(CCU_SYS_XGMAC_REF_CLK, "sys_xgmac_ref_clk",
			  "eth_clk", CCU_SYS_XGMAC_BASE, 8),
	CCU_DIV_FIXED_INFO(CCU_SYS_XGMAC_PTP_CLK, "sys_xgmac_ptp_clk",
			   "eth_clk", 10),
	CCU_DIV_GATE_INFO(CCU_SYS_USB_CLK, "sys_usb_clk",
			  "eth_clk", CCU_SYS_USB_BASE, 10),
	CCU_DIV_VAR_INFO(CCU_SYS_PVT_CLK, "sys_pvt_clk",
			 "ref_clk", CCU_SYS_PVT_BASE, 5,
			 CLK_SET_RATE_GATE, 0),
	CCU_DIV_VAR_INFO(CCU_SYS_HWA_CLK, "sys_hwa_clk",
			 "sata_clk", CCU_SYS_HWA_BASE, 4,
			 CLK_SET_RATE_GATE, 0),
	CCU_DIV_VAR_INFO(CCU_SYS_UART_CLK, "sys_uart_clk",
			 "eth_clk", CCU_SYS_UART_BASE, 17,
			 CLK_SET_RATE_GATE, 0),
	CCU_DIV_FIXED_INFO(CCU_SYS_I2C1_CLK, "sys_i2c1_clk",
			   "eth_clk", 10),
	CCU_DIV_FIXED_INFO(CCU_SYS_I2C2_CLK, "sys_i2c2_clk",
			   "eth_clk", 10),
	CCU_DIV_FIXED_INFO(CCU_SYS_GPIO_CLK, "sys_gpio_clk",
			   "ref_clk", 25),
	CCU_DIV_VAR_INFO(CCU_SYS_TIMER0_CLK, "sys_timer0_clk",
			 "ref_clk", CCU_SYS_TIMER0_BASE, 17,
			 CLK_SET_RATE_GATE, 0),
	CCU_DIV_VAR_INFO(CCU_SYS_TIMER1_CLK, "sys_timer1_clk",
			 "ref_clk", CCU_SYS_TIMER1_BASE, 17,
			 CLK_SET_RATE_GATE, 0),
	CCU_DIV_VAR_INFO(CCU_SYS_TIMER2_CLK, "sys_timer2_clk",
			 "ref_clk", CCU_SYS_TIMER2_BASE, 17,
			 CLK_SET_RATE_GATE, 0),
	CCU_DIV_VAR_INFO(CCU_SYS_WDT_CLK, "sys_wdt_clk",
			 "eth_clk", CCU_SYS_WDT_BASE, 17,
			 CLK_SET_RATE_GATE, CCU_DIV_SKIP_ONE_TO_THREE)
पूर्ण;

अटल स्थिर काष्ठा ccu_भाग_rst_map sys_rst_map[] = अणु
	CCU_DIV_RST_MAP(CCU_SYS_SATA_REF_RST, CCU_SYS_SATA_REF_CLK),
	CCU_DIV_RST_MAP(CCU_SYS_APB_RST, CCU_SYS_APB_CLK),
पूर्ण;

अटल काष्ठा ccu_भाग *ccu_भाग_find_desc(काष्ठा ccu_भाग_data *data,
					 अचिन्हित पूर्णांक clk_id)
अणु
	काष्ठा ccu_भाग *भाग;
	पूर्णांक idx;

	क्रम (idx = 0; idx < data->भागs_num; ++idx) अणु
		भाग = data->भागs[idx];
		अगर (भाग && भाग->id == clk_id)
			वापस भाग;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक ccu_भाग_reset(काष्ठा reset_controller_dev *rcdev,
			 अचिन्हित दीर्घ rst_id)
अणु
	काष्ठा ccu_भाग_data *data = to_ccu_भाग_data(rcdev);
	स्थिर काष्ठा ccu_भाग_rst_map *map;
	काष्ठा ccu_भाग *भाग;
	पूर्णांक idx, ret;

	क्रम (idx = 0, map = data->rst_map; idx < data->rst_num; ++idx, ++map) अणु
		अगर (map->rst_id == rst_id)
			अवरोध;
	पूर्ण
	अगर (idx == data->rst_num) अणु
		pr_err("Invalid reset ID %lu specified\n", rst_id);
		वापस -EINVAL;
	पूर्ण

	भाग = ccu_भाग_find_desc(data, map->clk_id);
	अगर (IS_ERR(भाग)) अणु
		pr_err("Invalid clock ID %d in mapping\n", map->clk_id);
		वापस PTR_ERR(भाग);
	पूर्ण

	ret = ccu_भाग_reset_करोमुख्य(भाग);
	अगर (ret) अणु
		pr_err("Reset isn't supported by divider %s\n",
			clk_hw_get_name(ccu_भाग_get_clk_hw(भाग)));
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops ccu_भाग_rst_ops = अणु
	.reset = ccu_भाग_reset,
पूर्ण;

अटल काष्ठा ccu_भाग_data *ccu_भाग_create_data(काष्ठा device_node *np)
अणु
	काष्ठा ccu_भाग_data *data;
	पूर्णांक ret;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	data->np = np;
	अगर (of_device_is_compatible(np, "baikal,bt1-ccu-axi")) अणु
		data->भागs_num = ARRAY_SIZE(axi_info);
		data->भागs_info = axi_info;
		data->rst_num = ARRAY_SIZE(axi_rst_map);
		data->rst_map = axi_rst_map;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "baikal,bt1-ccu-sys")) अणु
		data->भागs_num = ARRAY_SIZE(sys_info);
		data->भागs_info = sys_info;
		data->rst_num = ARRAY_SIZE(sys_rst_map);
		data->rst_map = sys_rst_map;
	पूर्ण अन्यथा अणु
		pr_err("Incompatible DT node '%s' specified\n",
			of_node_full_name(np));
		ret = -EINVAL;
		जाओ err_kमुक्त_data;
	पूर्ण

	data->भागs = kसुस्मृति(data->भागs_num, माप(*data->भागs), GFP_KERNEL);
	अगर (!data->भागs) अणु
		ret = -ENOMEM;
		जाओ err_kमुक्त_data;
	पूर्ण

	वापस data;

err_kमुक्त_data:
	kमुक्त(data);

	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम ccu_भाग_मुक्त_data(काष्ठा ccu_भाग_data *data)
अणु
	kमुक्त(data->भागs);

	kमुक्त(data);
पूर्ण

अटल पूर्णांक ccu_भाग_find_sys_regs(काष्ठा ccu_भाग_data *data)
अणु
	data->sys_regs = syscon_node_to_regmap(data->np->parent);
	अगर (IS_ERR(data->sys_regs)) अणु
		pr_err("Failed to find syscon regs for '%s'\n",
			of_node_full_name(data->np));
		वापस PTR_ERR(data->sys_regs);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा clk_hw *ccu_भाग_of_clk_hw_get(काष्ठा of_phandle_args *clkspec,
					    व्योम *priv)
अणु
	काष्ठा ccu_भाग_data *data = priv;
	काष्ठा ccu_भाग *भाग;
	अचिन्हित पूर्णांक clk_id;

	clk_id = clkspec->args[0];
	भाग = ccu_भाग_find_desc(data, clk_id);
	अगर (IS_ERR(भाग)) अणु
		pr_info("Invalid clock ID %d specified\n", clk_id);
		वापस ERR_CAST(भाग);
	पूर्ण

	वापस ccu_भाग_get_clk_hw(भाग);
पूर्ण

अटल पूर्णांक ccu_भाग_clk_रेजिस्टर(काष्ठा ccu_भाग_data *data)
अणु
	पूर्णांक idx, ret;

	क्रम (idx = 0; idx < data->भागs_num; ++idx) अणु
		स्थिर काष्ठा ccu_भाग_info *info = &data->भागs_info[idx];
		काष्ठा ccu_भाग_init_data init = अणु0पूर्ण;

		init.id = info->id;
		init.name = info->name;
		init.parent_name = info->parent_name;
		init.np = data->np;
		init.type = info->type;
		init.flags = info->flags;
		init.features = info->features;

		अगर (init.type == CCU_DIV_VAR) अणु
			init.base = info->base;
			init.sys_regs = data->sys_regs;
			init.width = info->width;
		पूर्ण अन्यथा अगर (init.type == CCU_DIV_GATE) अणु
			init.base = info->base;
			init.sys_regs = data->sys_regs;
			init.भागider = info->भागider;
		पूर्ण अन्यथा अणु
			init.भागider = info->भागider;
		पूर्ण

		data->भागs[idx] = ccu_भाग_hw_रेजिस्टर(&init);
		अगर (IS_ERR(data->भागs[idx])) अणु
			ret = PTR_ERR(data->भागs[idx]);
			pr_err("Couldn't register divider '%s' hw\n",
				init.name);
			जाओ err_hw_unरेजिस्टर;
		पूर्ण
	पूर्ण

	ret = of_clk_add_hw_provider(data->np, ccu_भाग_of_clk_hw_get, data);
	अगर (ret) अणु
		pr_err("Couldn't register dividers '%s' clock provider\n",
			of_node_full_name(data->np));
		जाओ err_hw_unरेजिस्टर;
	पूर्ण

	वापस 0;

err_hw_unरेजिस्टर:
	क्रम (--idx; idx >= 0; --idx)
		ccu_भाग_hw_unरेजिस्टर(data->भागs[idx]);

	वापस ret;
पूर्ण

अटल व्योम ccu_भाग_clk_unरेजिस्टर(काष्ठा ccu_भाग_data *data)
अणु
	पूर्णांक idx;

	of_clk_del_provider(data->np);

	क्रम (idx = 0; idx < data->भागs_num; ++idx)
		ccu_भाग_hw_unरेजिस्टर(data->भागs[idx]);
पूर्ण

अटल पूर्णांक ccu_भाग_rst_रेजिस्टर(काष्ठा ccu_भाग_data *data)
अणु
	पूर्णांक ret;

	data->rcdev.ops = &ccu_भाग_rst_ops;
	data->rcdev.of_node = data->np;
	data->rcdev.nr_resets = data->rst_num;

	ret = reset_controller_रेजिस्टर(&data->rcdev);
	अगर (ret)
		pr_err("Couldn't register divider '%s' reset controller\n",
			of_node_full_name(data->np));

	वापस ret;
पूर्ण

अटल व्योम ccu_भाग_init(काष्ठा device_node *np)
अणु
	काष्ठा ccu_भाग_data *data;
	पूर्णांक ret;

	data = ccu_भाग_create_data(np);
	अगर (IS_ERR(data))
		वापस;

	ret = ccu_भाग_find_sys_regs(data);
	अगर (ret)
		जाओ err_मुक्त_data;

	ret = ccu_भाग_clk_रेजिस्टर(data);
	अगर (ret)
		जाओ err_मुक्त_data;

	ret = ccu_भाग_rst_रेजिस्टर(data);
	अगर (ret)
		जाओ err_clk_unरेजिस्टर;

	वापस;

err_clk_unरेजिस्टर:
	ccu_भाग_clk_unरेजिस्टर(data);

err_मुक्त_data:
	ccu_भाग_मुक्त_data(data);
पूर्ण

CLK_OF_DECLARE(ccu_axi, "baikal,bt1-ccu-axi", ccu_भाग_init);
CLK_OF_DECLARE(ccu_sys, "baikal,bt1-ccu-sys", ccu_भाग_init);
