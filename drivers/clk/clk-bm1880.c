<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Biपंचांगain BM1880 SoC घड़ी driver
 *
 * Copyright (c) 2019 Linaro Ltd.
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/bm1880-घड़ी.h>

#घोषणा BM1880_CLK_MPLL_CTL	0x00
#घोषणा BM1880_CLK_SPLL_CTL	0x04
#घोषणा BM1880_CLK_FPLL_CTL	0x08
#घोषणा BM1880_CLK_DDRPLL_CTL	0x0c

#घोषणा BM1880_CLK_ENABLE0	0x00
#घोषणा BM1880_CLK_ENABLE1	0x04
#घोषणा BM1880_CLK_SELECT	0x20
#घोषणा BM1880_CLK_DIV0		0x40
#घोषणा BM1880_CLK_DIV1		0x44
#घोषणा BM1880_CLK_DIV2		0x48
#घोषणा BM1880_CLK_DIV3		0x4c
#घोषणा BM1880_CLK_DIV4		0x50
#घोषणा BM1880_CLK_DIV5		0x54
#घोषणा BM1880_CLK_DIV6		0x58
#घोषणा BM1880_CLK_DIV7		0x5c
#घोषणा BM1880_CLK_DIV8		0x60
#घोषणा BM1880_CLK_DIV9		0x64
#घोषणा BM1880_CLK_DIV10	0x68
#घोषणा BM1880_CLK_DIV11	0x6c
#घोषणा BM1880_CLK_DIV12	0x70
#घोषणा BM1880_CLK_DIV13	0x74
#घोषणा BM1880_CLK_DIV14	0x78
#घोषणा BM1880_CLK_DIV15	0x7c
#घोषणा BM1880_CLK_DIV16	0x80
#घोषणा BM1880_CLK_DIV17	0x84
#घोषणा BM1880_CLK_DIV18	0x88
#घोषणा BM1880_CLK_DIV19	0x8c
#घोषणा BM1880_CLK_DIV20	0x90
#घोषणा BM1880_CLK_DIV21	0x94
#घोषणा BM1880_CLK_DIV22	0x98
#घोषणा BM1880_CLK_DIV23	0x9c
#घोषणा BM1880_CLK_DIV24	0xa0
#घोषणा BM1880_CLK_DIV25	0xa4
#घोषणा BM1880_CLK_DIV26	0xa8
#घोषणा BM1880_CLK_DIV27	0xac
#घोषणा BM1880_CLK_DIV28	0xb0

#घोषणा to_bm1880_pll_clk(_hw) container_of(_hw, काष्ठा bm1880_pll_hw_घड़ी, hw)
#घोषणा to_bm1880_भाग_clk(_hw) container_of(_hw, काष्ठा bm1880_भाग_hw_घड़ी, hw)

अटल DEFINE_SPINLOCK(bm1880_clk_lock);

काष्ठा bm1880_घड़ी_data अणु
	व्योम __iomem *pll_base;
	व्योम __iomem *sys_base;
	काष्ठा clk_hw_onecell_data hw_data;
पूर्ण;

काष्ठा bm1880_gate_घड़ी अणु
	अचिन्हित पूर्णांक	id;
	स्थिर अक्षर	*name;
	स्थिर अक्षर      *parent;
	u32		gate_reg;
	s8		gate_shअगरt;
	अचिन्हित दीर्घ	flags;
पूर्ण;

काष्ठा bm1880_mux_घड़ी अणु
	अचिन्हित पूर्णांक	id;
	स्थिर अक्षर	*name;
	स्थिर अक्षर      * स्थिर *parents;
	s8		num_parents;
	u32		reg;
	s8		shअगरt;
	अचिन्हित दीर्घ	flags;
पूर्ण;

काष्ठा bm1880_भाग_घड़ी अणु
	अचिन्हित पूर्णांक	id;
	स्थिर अक्षर	*name;
	u32		reg;
	u8		shअगरt;
	u8		width;
	u32		initval;
	स्थिर काष्ठा clk_भाग_प्रकारable *table;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा bm1880_भाग_hw_घड़ी अणु
	काष्ठा bm1880_भाग_घड़ी भाग;
	व्योम __iomem *base;
	spinlock_t *lock;
	काष्ठा clk_hw hw;
	काष्ठा clk_init_data init;
पूर्ण;

काष्ठा bm1880_composite_घड़ी अणु
	अचिन्हित पूर्णांक	id;
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*parent;
	स्थिर अक्षर      * स्थिर *parents;
	अचिन्हित पूर्णांक	num_parents;
	अचिन्हित दीर्घ	flags;

	u32		gate_reg;
	u32		mux_reg;
	u32		भाग_reg;

	s8		gate_shअगरt;
	s8		mux_shअगरt;
	s8		भाग_shअगरt;
	s8		भाग_width;
	s16		भाग_initval;
	स्थिर काष्ठा clk_भाग_प्रकारable *table;
पूर्ण;

काष्ठा bm1880_pll_घड़ी अणु
	अचिन्हित पूर्णांक	id;
	स्थिर अक्षर	*name;
	u32		reg;
	अचिन्हित दीर्घ	flags;
पूर्ण;

काष्ठा bm1880_pll_hw_घड़ी अणु
	काष्ठा bm1880_pll_घड़ी pll;
	व्योम __iomem *base;
	काष्ठा clk_hw hw;
	काष्ठा clk_init_data init;
पूर्ण;

अटल स्थिर काष्ठा clk_ops bm1880_pll_ops;
अटल स्थिर काष्ठा clk_ops bm1880_clk_भाग_ops;

#घोषणा GATE_DIV(_id, _name, _parent, _gate_reg, _gate_shअगरt, _भाग_reg,	\
			_भाग_shअगरt, _भाग_width, _भाग_initval, _table,	\
			_flags) अणु					\
		.id = _id,						\
		.parent = _parent,					\
		.name = _name,						\
		.gate_reg = _gate_reg,					\
		.gate_shअगरt = _gate_shअगरt,				\
		.भाग_reg = _भाग_reg,					\
		.भाग_shअगरt = _भाग_shअगरt,				\
		.भाग_width = _भाग_width,				\
		.भाग_initval = _भाग_initval,				\
		.table = _table,					\
		.mux_shअगरt = -1,					\
		.flags = _flags,					\
	पूर्ण

#घोषणा GATE_MUX(_id, _name, _parents, _gate_reg, _gate_shअगरt,		\
			_mux_reg, _mux_shअगरt, _flags) अणु			\
		.id = _id,						\
		.parents = _parents,					\
		.num_parents = ARRAY_SIZE(_parents),			\
		.name = _name,						\
		.gate_reg = _gate_reg,					\
		.gate_shअगरt = _gate_shअगरt,				\
		.भाग_shअगरt = -1,					\
		.mux_reg = _mux_reg,					\
		.mux_shअगरt = _mux_shअगरt,				\
		.flags = _flags,					\
	पूर्ण

#घोषणा CLK_PLL(_id, _name, _parent, _reg, _flags) अणु			\
		.pll.id = _id,						\
		.pll.name = _name,					\
		.pll.reg = _reg,					\
		.hw.init = CLK_HW_INIT_PARENTS_DATA(_name, _parent,	\
						    &bm1880_pll_ops,	\
						    _flags),		\
	पूर्ण

#घोषणा CLK_DIV(_id, _name, _parent, _reg, _shअगरt, _width, _initval,	\
				_table,	_flags) अणु			\
		.भाग.id = _id,						\
		.भाग.name = _name,					\
		.भाग.reg = _reg,					\
		.भाग.shअगरt = _shअगरt,					\
		.भाग.width = _width,					\
		.भाग.initval = _initval,				\
		.भाग.table = _table,					\
		.hw.init = CLK_HW_INIT_HW(_name, _parent,		\
					  &bm1880_clk_भाग_ops,		\
					  _flags),			\
	पूर्ण

अटल काष्ठा clk_parent_data bm1880_pll_parent[] = अणु
	अणु .fw_name = "osc", .name = "osc" पूर्ण,
पूर्ण;

/*
 * All PLL घड़ीs are marked as CRITICAL, hence they are very crucial
 * क्रम the functioning of the SoC
 */
अटल काष्ठा bm1880_pll_hw_घड़ी bm1880_pll_clks[] = अणु
	CLK_PLL(BM1880_CLK_MPLL, "clk_mpll", bm1880_pll_parent,
		BM1880_CLK_MPLL_CTL, 0),
	CLK_PLL(BM1880_CLK_SPLL, "clk_spll", bm1880_pll_parent,
		BM1880_CLK_SPLL_CTL, 0),
	CLK_PLL(BM1880_CLK_FPLL, "clk_fpll", bm1880_pll_parent,
		BM1880_CLK_FPLL_CTL, 0),
	CLK_PLL(BM1880_CLK_DDRPLL, "clk_ddrpll", bm1880_pll_parent,
		BM1880_CLK_DDRPLL_CTL, 0),
पूर्ण;

/*
 * Clocks marked as CRITICAL are needed क्रम the proper functioning
 * of the SoC.
 */
अटल स्थिर काष्ठा bm1880_gate_घड़ी bm1880_gate_clks[] = अणु
	अणु BM1880_CLK_AHB_ROM, "clk_ahb_rom", "clk_mux_axi6",
	  BM1880_CLK_ENABLE0, 2, 0 पूर्ण,
	अणु BM1880_CLK_AXI_SRAM, "clk_axi_sram", "clk_axi1",
	  BM1880_CLK_ENABLE0, 3, 0 पूर्ण,
	/*
	 * Since this घड़ी is sourcing the DDR memory, let's mark it as
	 * critical to aव्योम gating.
	 */
	अणु BM1880_CLK_DDR_AXI, "clk_ddr_axi", "clk_mux_axi6",
	  BM1880_CLK_ENABLE0, 4, CLK_IS_CRITICAL पूर्ण,
	अणु BM1880_CLK_APB_EFUSE, "clk_apb_efuse", "clk_mux_axi6",
	  BM1880_CLK_ENABLE0, 6, 0 पूर्ण,
	अणु BM1880_CLK_AXI5_EMMC, "clk_axi5_emmc", "clk_axi5",
	  BM1880_CLK_ENABLE0, 7, 0 पूर्ण,
	अणु BM1880_CLK_AXI5_SD, "clk_axi5_sd", "clk_axi5",
	  BM1880_CLK_ENABLE0, 10, 0 पूर्ण,
	अणु BM1880_CLK_AXI4_ETH0, "clk_axi4_eth0", "clk_axi4",
	  BM1880_CLK_ENABLE0, 14, 0 पूर्ण,
	अणु BM1880_CLK_AXI4_ETH1, "clk_axi4_eth1", "clk_axi4",
	  BM1880_CLK_ENABLE0, 16, 0 पूर्ण,
	अणु BM1880_CLK_AXI1_GDMA, "clk_axi1_gdma", "clk_axi1",
	  BM1880_CLK_ENABLE0, 17, 0 पूर्ण,
	/* Don't gate GPIO घड़ीs as it is not owned by the GPIO driver */
	अणु BM1880_CLK_APB_GPIO, "clk_apb_gpio", "clk_mux_axi6",
	  BM1880_CLK_ENABLE0, 18, CLK_IGNORE_UNUSED पूर्ण,
	अणु BM1880_CLK_APB_GPIO_INTR, "clk_apb_gpio_intr", "clk_mux_axi6",
	  BM1880_CLK_ENABLE0, 19, CLK_IGNORE_UNUSED पूर्ण,
	अणु BM1880_CLK_AXI1_MINER, "clk_axi1_miner", "clk_axi1",
	  BM1880_CLK_ENABLE0, 21, 0 पूर्ण,
	अणु BM1880_CLK_AHB_SF, "clk_ahb_sf", "clk_mux_axi6",
	  BM1880_CLK_ENABLE0, 22, 0 पूर्ण,
	/*
	 * Not sure which module this घड़ी is sourcing but gating this घड़ी
	 * prevents the प्रणाली from booting. So, let's mark it as critical.
	 */
	अणु BM1880_CLK_SDMA_AXI, "clk_sdma_axi", "clk_axi5",
	  BM1880_CLK_ENABLE0, 23, CLK_IS_CRITICAL पूर्ण,
	अणु BM1880_CLK_APB_I2C, "clk_apb_i2c", "clk_mux_axi6",
	  BM1880_CLK_ENABLE0, 25, 0 पूर्ण,
	अणु BM1880_CLK_APB_WDT, "clk_apb_wdt", "clk_mux_axi6",
	  BM1880_CLK_ENABLE0, 26, 0 पूर्ण,
	अणु BM1880_CLK_APB_JPEG, "clk_apb_jpeg", "clk_axi6",
	  BM1880_CLK_ENABLE0, 27, 0 पूर्ण,
	अणु BM1880_CLK_AXI5_NF, "clk_axi5_nf", "clk_axi5",
	  BM1880_CLK_ENABLE0, 29, 0 पूर्ण,
	अणु BM1880_CLK_APB_NF, "clk_apb_nf", "clk_axi6",
	  BM1880_CLK_ENABLE0, 30, 0 पूर्ण,
	अणु BM1880_CLK_APB_PWM, "clk_apb_pwm", "clk_mux_axi6",
	  BM1880_CLK_ENABLE1, 0, 0 पूर्ण,
	अणु BM1880_CLK_RV, "clk_rv", "clk_mux_rv",
	  BM1880_CLK_ENABLE1, 1, 0 पूर्ण,
	अणु BM1880_CLK_APB_SPI, "clk_apb_spi", "clk_mux_axi6",
	  BM1880_CLK_ENABLE1, 2, 0 पूर्ण,
	अणु BM1880_CLK_UART_500M, "clk_uart_500m", "clk_div_uart_500m",
	  BM1880_CLK_ENABLE1, 4, 0 पूर्ण,
	अणु BM1880_CLK_APB_UART, "clk_apb_uart", "clk_axi6",
	  BM1880_CLK_ENABLE1, 5, 0 पूर्ण,
	अणु BM1880_CLK_APB_I2S, "clk_apb_i2s", "clk_axi6",
	  BM1880_CLK_ENABLE1, 6, 0 पूर्ण,
	अणु BM1880_CLK_AXI4_USB, "clk_axi4_usb", "clk_axi4",
	  BM1880_CLK_ENABLE1, 7, 0 पूर्ण,
	अणु BM1880_CLK_APB_USB, "clk_apb_usb", "clk_axi6",
	  BM1880_CLK_ENABLE1, 8, 0 पूर्ण,
	अणु BM1880_CLK_12M_USB, "clk_12m_usb", "clk_div_12m_usb",
	  BM1880_CLK_ENABLE1, 11, 0 पूर्ण,
	अणु BM1880_CLK_APB_VIDEO, "clk_apb_video", "clk_axi6",
	  BM1880_CLK_ENABLE1, 12, 0 पूर्ण,
	अणु BM1880_CLK_APB_VPP, "clk_apb_vpp", "clk_axi6",
	  BM1880_CLK_ENABLE1, 15, 0 पूर्ण,
	अणु BM1880_CLK_AXI6, "clk_axi6", "clk_mux_axi6",
	  BM1880_CLK_ENABLE1, 21, 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर clk_a53_parents[] = अणु "clk_spll", "clk_mpll" पूर्ण;
अटल स्थिर अक्षर * स्थिर clk_rv_parents[] = अणु "clk_div_1_rv", "clk_div_0_rv" पूर्ण;
अटल स्थिर अक्षर * स्थिर clk_axi1_parents[] = अणु "clk_div_1_axi1", "clk_div_0_axi1" पूर्ण;
अटल स्थिर अक्षर * स्थिर clk_axi6_parents[] = अणु "clk_div_1_axi6", "clk_div_0_axi6" पूर्ण;

अटल स्थिर काष्ठा bm1880_mux_घड़ी bm1880_mux_clks[] = अणु
	अणु BM1880_CLK_MUX_RV, "clk_mux_rv", clk_rv_parents, 2,
	  BM1880_CLK_SELECT, 1, 0 पूर्ण,
	अणु BM1880_CLK_MUX_AXI6, "clk_mux_axi6", clk_axi6_parents, 2,
	  BM1880_CLK_SELECT, 3, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable bm1880_भाग_प्रकारable_0[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 3 पूर्ण, अणु 3, 4 पूर्ण,
	अणु 4, 5 पूर्ण, अणु 5, 6 पूर्ण, अणु 6, 7 पूर्ण, अणु 7, 8 पूर्ण,
	अणु 8, 9 पूर्ण, अणु 9, 10 पूर्ण, अणु 10, 11 पूर्ण, अणु 11, 12 पूर्ण,
	अणु 12, 13 पूर्ण, अणु 13, 14 पूर्ण, अणु 14, 15 पूर्ण, अणु 15, 16 पूर्ण,
	अणु 16, 17 पूर्ण, अणु 17, 18 पूर्ण, अणु 18, 19 पूर्ण, अणु 19, 20 पूर्ण,
	अणु 20, 21 पूर्ण, अणु 21, 22 पूर्ण, अणु 22, 23 पूर्ण, अणु 23, 24 पूर्ण,
	अणु 24, 25 पूर्ण, अणु 25, 26 पूर्ण, अणु 26, 27 पूर्ण, अणु 27, 28 पूर्ण,
	अणु 28, 29 पूर्ण, अणु 29, 30 पूर्ण, अणु 30, 31 पूर्ण, अणु 31, 32 पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable bm1880_भाग_प्रकारable_1[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 3 पूर्ण, अणु 3, 4 पूर्ण,
	अणु 4, 5 पूर्ण, अणु 5, 6 पूर्ण, अणु 6, 7 पूर्ण, अणु 7, 8 पूर्ण,
	अणु 8, 9 पूर्ण, अणु 9, 10 पूर्ण, अणु 10, 11 पूर्ण, अणु 11, 12 पूर्ण,
	अणु 12, 13 पूर्ण, अणु 13, 14 पूर्ण, अणु 14, 15 पूर्ण, अणु 15, 16 पूर्ण,
	अणु 16, 17 पूर्ण, अणु 17, 18 पूर्ण, अणु 18, 19 पूर्ण, अणु 19, 20 पूर्ण,
	अणु 20, 21 पूर्ण, अणु 21, 22 पूर्ण, अणु 22, 23 पूर्ण, अणु 23, 24 पूर्ण,
	अणु 24, 25 पूर्ण, अणु 25, 26 पूर्ण, अणु 26, 27 पूर्ण, अणु 27, 28 पूर्ण,
	अणु 28, 29 पूर्ण, अणु 29, 30 पूर्ण, अणु 30, 31 पूर्ण, अणु 31, 32 पूर्ण,
	अणु 127, 128 पूर्ण, अणु 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable bm1880_भाग_प्रकारable_2[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 3 पूर्ण, अणु 3, 4 पूर्ण,
	अणु 4, 5 पूर्ण, अणु 5, 6 पूर्ण, अणु 6, 7 पूर्ण, अणु 7, 8 पूर्ण,
	अणु 8, 9 पूर्ण, अणु 9, 10 पूर्ण, अणु 10, 11 पूर्ण, अणु 11, 12 पूर्ण,
	अणु 12, 13 पूर्ण, अणु 13, 14 पूर्ण, अणु 14, 15 पूर्ण, अणु 15, 16 पूर्ण,
	अणु 16, 17 पूर्ण, अणु 17, 18 पूर्ण, अणु 18, 19 पूर्ण, अणु 19, 20 पूर्ण,
	अणु 20, 21 पूर्ण, अणु 21, 22 पूर्ण, अणु 22, 23 पूर्ण, अणु 23, 24 पूर्ण,
	अणु 24, 25 पूर्ण, अणु 25, 26 पूर्ण, अणु 26, 27 पूर्ण, अणु 27, 28 पूर्ण,
	अणु 28, 29 पूर्ण, अणु 29, 30 पूर्ण, अणु 30, 31 पूर्ण, अणु 31, 32 पूर्ण,
	अणु 127, 128 पूर्ण, अणु 255, 256 पूर्ण, अणु 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable bm1880_भाग_प्रकारable_3[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 3 पूर्ण, अणु 3, 4 पूर्ण,
	अणु 4, 5 पूर्ण, अणु 5, 6 पूर्ण, अणु 6, 7 पूर्ण, अणु 7, 8 पूर्ण,
	अणु 8, 9 पूर्ण, अणु 9, 10 पूर्ण, अणु 10, 11 पूर्ण, अणु 11, 12 पूर्ण,
	अणु 12, 13 पूर्ण, अणु 13, 14 पूर्ण, अणु 14, 15 पूर्ण, अणु 15, 16 पूर्ण,
	अणु 16, 17 पूर्ण, अणु 17, 18 पूर्ण, अणु 18, 19 पूर्ण, अणु 19, 20 पूर्ण,
	अणु 20, 21 पूर्ण, अणु 21, 22 पूर्ण, अणु 22, 23 पूर्ण, अणु 23, 24 पूर्ण,
	अणु 24, 25 पूर्ण, अणु 25, 26 पूर्ण, अणु 26, 27 पूर्ण, अणु 27, 28 पूर्ण,
	अणु 28, 29 पूर्ण, अणु 29, 30 पूर्ण, अणु 30, 31 पूर्ण, अणु 31, 32 पूर्ण,
	अणु 127, 128 पूर्ण, अणु 255, 256 पूर्ण, अणु 511, 512 पूर्ण, अणु 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable bm1880_भाग_प्रकारable_4[] = अणु
	अणु 0, 1 पूर्ण, अणु 1, 2 पूर्ण, अणु 2, 3 पूर्ण, अणु 3, 4 पूर्ण,
	अणु 4, 5 पूर्ण, अणु 5, 6 पूर्ण, अणु 6, 7 पूर्ण, अणु 7, 8 पूर्ण,
	अणु 8, 9 पूर्ण, अणु 9, 10 पूर्ण, अणु 10, 11 पूर्ण, अणु 11, 12 पूर्ण,
	अणु 12, 13 पूर्ण, अणु 13, 14 पूर्ण, अणु 14, 15 पूर्ण, अणु 15, 16 पूर्ण,
	अणु 16, 17 पूर्ण, अणु 17, 18 पूर्ण, अणु 18, 19 पूर्ण, अणु 19, 20 पूर्ण,
	अणु 20, 21 पूर्ण, अणु 21, 22 पूर्ण, अणु 22, 23 पूर्ण, अणु 23, 24 पूर्ण,
	अणु 24, 25 पूर्ण, अणु 25, 26 पूर्ण, अणु 26, 27 पूर्ण, अणु 27, 28 पूर्ण,
	अणु 28, 29 पूर्ण, अणु 29, 30 पूर्ण, अणु 30, 31 पूर्ण, अणु 31, 32 पूर्ण,
	अणु 127, 128 पूर्ण, अणु 255, 256 पूर्ण, अणु 511, 512 पूर्ण, अणु 65535, 65536 पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/*
 * Clocks marked as CRITICAL are needed क्रम the proper functioning
 * of the SoC.
 */
अटल काष्ठा bm1880_भाग_hw_घड़ी bm1880_भाग_clks[] = अणु
	CLK_DIV(BM1880_CLK_DIV_0_RV, "clk_div_0_rv", &bm1880_pll_clks[1].hw,
		BM1880_CLK_DIV12, 16, 5, 1, bm1880_भाग_प्रकारable_0, 0),
	CLK_DIV(BM1880_CLK_DIV_1_RV, "clk_div_1_rv", &bm1880_pll_clks[2].hw,
		BM1880_CLK_DIV13, 16, 5, 1, bm1880_भाग_प्रकारable_0, 0),
	CLK_DIV(BM1880_CLK_DIV_UART_500M, "clk_div_uart_500m", &bm1880_pll_clks[2].hw,
		BM1880_CLK_DIV15, 16, 7, 3, bm1880_भाग_प्रकारable_1, 0),
	CLK_DIV(BM1880_CLK_DIV_0_AXI1, "clk_div_0_axi1", &bm1880_pll_clks[0].hw,
		BM1880_CLK_DIV21, 16, 5, 2, bm1880_भाग_प्रकारable_0,
		0),
	CLK_DIV(BM1880_CLK_DIV_1_AXI1, "clk_div_1_axi1", &bm1880_pll_clks[2].hw,
		BM1880_CLK_DIV22, 16, 5, 3, bm1880_भाग_प्रकारable_0,
		0),
	CLK_DIV(BM1880_CLK_DIV_0_AXI6, "clk_div_0_axi6", &bm1880_pll_clks[2].hw,
		BM1880_CLK_DIV27, 16, 5, 15, bm1880_भाग_प्रकारable_0,
		0),
	CLK_DIV(BM1880_CLK_DIV_1_AXI6, "clk_div_1_axi6", &bm1880_pll_clks[0].hw,
		BM1880_CLK_DIV28, 16, 5, 11, bm1880_भाग_प्रकारable_0,
		0),
	CLK_DIV(BM1880_CLK_DIV_12M_USB, "clk_div_12m_usb", &bm1880_pll_clks[2].hw,
		BM1880_CLK_DIV18, 16, 7, 125, bm1880_भाग_प्रकारable_1, 0),
पूर्ण;

/*
 * Clocks marked as CRITICAL are all needed क्रम the proper functioning
 * of the SoC.
 */
अटल काष्ठा bm1880_composite_घड़ी bm1880_composite_clks[] = अणु
	/*
	 * Since clk_a53 and clk_50m_a53 घड़ीs are sourcing the CPU core,
	 * let's mark them as critical to aव्योम gating.
	 */
	GATE_MUX(BM1880_CLK_A53, "clk_a53", clk_a53_parents,
		 BM1880_CLK_ENABLE0, 0, BM1880_CLK_SELECT, 0,
		 CLK_IS_CRITICAL),
	GATE_DIV(BM1880_CLK_50M_A53, "clk_50m_a53", "clk_fpll",
		 BM1880_CLK_ENABLE0, 1, BM1880_CLK_DIV0, 16, 5, 30,
		 bm1880_भाग_प्रकारable_0, CLK_IS_CRITICAL),
	GATE_DIV(BM1880_CLK_EFUSE, "clk_efuse", "clk_fpll",
		 BM1880_CLK_ENABLE0, 5, BM1880_CLK_DIV1, 16, 7, 60,
		 bm1880_भाग_प्रकारable_1, 0),
	GATE_DIV(BM1880_CLK_EMMC, "clk_emmc", "clk_fpll",
		 BM1880_CLK_ENABLE0, 8, BM1880_CLK_DIV2, 16, 5, 15,
		 bm1880_भाग_प्रकारable_0, 0),
	GATE_DIV(BM1880_CLK_100K_EMMC, "clk_100k_emmc", "clk_div_12m_usb",
		 BM1880_CLK_ENABLE0, 9, BM1880_CLK_DIV3, 16, 8, 120,
		 bm1880_भाग_प्रकारable_2, 0),
	GATE_DIV(BM1880_CLK_SD, "clk_sd", "clk_fpll",
		 BM1880_CLK_ENABLE0, 11, BM1880_CLK_DIV4, 16, 5, 15,
		 bm1880_भाग_प्रकारable_0, 0),
	GATE_DIV(BM1880_CLK_100K_SD, "clk_100k_sd", "clk_div_12m_usb",
		 BM1880_CLK_ENABLE0, 12, BM1880_CLK_DIV5, 16, 8, 120,
		 bm1880_भाग_प्रकारable_2, 0),
	GATE_DIV(BM1880_CLK_500M_ETH0, "clk_500m_eth0", "clk_fpll",
		 BM1880_CLK_ENABLE0, 13, BM1880_CLK_DIV6, 16, 5, 3,
		 bm1880_भाग_प्रकारable_0, 0),
	GATE_DIV(BM1880_CLK_500M_ETH1, "clk_500m_eth1", "clk_fpll",
		 BM1880_CLK_ENABLE0, 15, BM1880_CLK_DIV7, 16, 5, 3,
		 bm1880_भाग_प्रकारable_0, 0),
	/* Don't gate GPIO घड़ीs as it is not owned by the GPIO driver */
	GATE_DIV(BM1880_CLK_GPIO_DB, "clk_gpio_db", "clk_div_12m_usb",
		 BM1880_CLK_ENABLE0, 20, BM1880_CLK_DIV8, 16, 16, 120,
		 bm1880_भाग_प्रकारable_4, CLK_IGNORE_UNUSED),
	GATE_DIV(BM1880_CLK_SDMA_AUD, "clk_sdma_aud", "clk_fpll",
		 BM1880_CLK_ENABLE0, 24, BM1880_CLK_DIV9, 16, 7, 61,
		 bm1880_भाग_प्रकारable_1, 0),
	GATE_DIV(BM1880_CLK_JPEG_AXI, "clk_jpeg_axi", "clk_fpll",
		 BM1880_CLK_ENABLE0, 28, BM1880_CLK_DIV10, 16, 5, 4,
		 bm1880_भाग_प्रकारable_0, 0),
	GATE_DIV(BM1880_CLK_NF, "clk_nf", "clk_fpll",
		 BM1880_CLK_ENABLE0, 31, BM1880_CLK_DIV11, 16, 5, 30,
		 bm1880_भाग_प्रकारable_0, 0),
	GATE_DIV(BM1880_CLK_TPU_AXI, "clk_tpu_axi", "clk_spll",
		 BM1880_CLK_ENABLE1, 3, BM1880_CLK_DIV14, 16, 5, 1,
		 bm1880_भाग_प्रकारable_0, 0),
	GATE_DIV(BM1880_CLK_125M_USB, "clk_125m_usb", "clk_fpll",
		 BM1880_CLK_ENABLE1, 9, BM1880_CLK_DIV16, 16, 5, 12,
		 bm1880_भाग_प्रकारable_0, 0),
	GATE_DIV(BM1880_CLK_33K_USB, "clk_33k_usb", "clk_div_12m_usb",
		 BM1880_CLK_ENABLE1, 10, BM1880_CLK_DIV17, 16, 9, 363,
		 bm1880_भाग_प्रकारable_3, 0),
	GATE_DIV(BM1880_CLK_VIDEO_AXI, "clk_video_axi", "clk_fpll",
		 BM1880_CLK_ENABLE1, 13, BM1880_CLK_DIV19, 16, 5, 4,
		 bm1880_भाग_प्रकारable_0, 0),
	GATE_DIV(BM1880_CLK_VPP_AXI, "clk_vpp_axi", "clk_fpll",
		 BM1880_CLK_ENABLE1, 14, BM1880_CLK_DIV20, 16, 5, 4,
		 bm1880_भाग_प्रकारable_0, 0),
	GATE_MUX(BM1880_CLK_AXI1, "clk_axi1", clk_axi1_parents,
		 BM1880_CLK_ENABLE1, 15, BM1880_CLK_SELECT, 2, 0),
	GATE_DIV(BM1880_CLK_AXI2, "clk_axi2", "clk_fpll",
		 BM1880_CLK_ENABLE1, 17, BM1880_CLK_DIV23, 16, 5, 3,
		 bm1880_भाग_प्रकारable_0, 0),
	GATE_DIV(BM1880_CLK_AXI3, "clk_axi3", "clk_mux_rv",
		 BM1880_CLK_ENABLE1, 18, BM1880_CLK_DIV24, 16, 5, 2,
		 bm1880_भाग_प्रकारable_0, 0),
	GATE_DIV(BM1880_CLK_AXI4, "clk_axi4", "clk_fpll",
		 BM1880_CLK_ENABLE1, 19, BM1880_CLK_DIV25, 16, 5, 6,
		 bm1880_भाग_प्रकारable_0, 0),
	GATE_DIV(BM1880_CLK_AXI5, "clk_axi5", "clk_fpll",
		 BM1880_CLK_ENABLE1, 20, BM1880_CLK_DIV26, 16, 5, 15,
		 bm1880_भाग_प्रकारable_0, 0),
पूर्ण;

अटल अचिन्हित दीर्घ bm1880_pll_rate_calc(u32 regval, अचिन्हित दीर्घ parent_rate)
अणु
	u64 numerator;
	u32 fbभाग, refभाग;
	u32 postभाग1, postभाग2, denominator;

	fbभाग = (regval >> 16) & 0xfff;
	refभाग = regval & 0x1f;
	postभाग1 = (regval >> 8) & 0x7;
	postभाग2 = (regval >> 12) & 0x7;

	numerator = parent_rate * fbभाग;
	denominator = refभाग * postभाग1 * postभाग2;
	करो_भाग(numerator, denominator);

	वापस (अचिन्हित दीर्घ)numerator;
पूर्ण

अटल अचिन्हित दीर्घ bm1880_pll_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा bm1880_pll_hw_घड़ी *pll_hw = to_bm1880_pll_clk(hw);
	अचिन्हित दीर्घ rate;
	u32 regval;

	regval = पढ़ोl(pll_hw->base + pll_hw->pll.reg);
	rate = bm1880_pll_rate_calc(regval, parent_rate);

	वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops bm1880_pll_ops = अणु
	.recalc_rate	= bm1880_pll_recalc_rate,
पूर्ण;

अटल काष्ठा clk_hw *bm1880_clk_रेजिस्टर_pll(काष्ठा bm1880_pll_hw_घड़ी *pll_clk,
					      व्योम __iomem *sys_base)
अणु
	काष्ठा clk_hw *hw;
	पूर्णांक err;

	pll_clk->base = sys_base;
	hw = &pll_clk->hw;

	err = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (err)
		वापस ERR_PTR(err);

	वापस hw;
पूर्ण

अटल व्योम bm1880_clk_unरेजिस्टर_pll(काष्ठा clk_hw *hw)
अणु
	काष्ठा bm1880_pll_hw_घड़ी *pll_hw = to_bm1880_pll_clk(hw);

	clk_hw_unरेजिस्टर(hw);
	kमुक्त(pll_hw);
पूर्ण

अटल पूर्णांक bm1880_clk_रेजिस्टर_plls(काष्ठा bm1880_pll_hw_घड़ी *clks,
				    पूर्णांक num_clks,
				    काष्ठा bm1880_घड़ी_data *data)
अणु
	काष्ठा clk_hw *hw;
	व्योम __iomem *pll_base = data->pll_base;
	पूर्णांक i;

	क्रम (i = 0; i < num_clks; i++) अणु
		काष्ठा bm1880_pll_hw_घड़ी *bm1880_clk = &clks[i];

		hw = bm1880_clk_रेजिस्टर_pll(bm1880_clk, pll_base);
		अगर (IS_ERR(hw)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, bm1880_clk->pll.name);
			जाओ err_clk;
		पूर्ण

		data->hw_data.hws[clks[i].pll.id] = hw;
	पूर्ण

	वापस 0;

err_clk:
	जबतक (i--)
		bm1880_clk_unरेजिस्टर_pll(data->hw_data.hws[clks[i].pll.id]);

	वापस PTR_ERR(hw);
पूर्ण

अटल पूर्णांक bm1880_clk_रेजिस्टर_mux(स्थिर काष्ठा bm1880_mux_घड़ी *clks,
				   पूर्णांक num_clks,
				   काष्ठा bm1880_घड़ी_data *data)
अणु
	काष्ठा clk_hw *hw;
	व्योम __iomem *sys_base = data->sys_base;
	पूर्णांक i;

	क्रम (i = 0; i < num_clks; i++) अणु
		hw = clk_hw_रेजिस्टर_mux(शून्य, clks[i].name,
					 clks[i].parents,
					 clks[i].num_parents,
					 clks[i].flags,
					 sys_base + clks[i].reg,
					 clks[i].shअगरt, 1, 0,
					 &bm1880_clk_lock);
		अगर (IS_ERR(hw)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जाओ err_clk;
		पूर्ण

		data->hw_data.hws[clks[i].id] = hw;
	पूर्ण

	वापस 0;

err_clk:
	जबतक (i--)
		clk_hw_unरेजिस्टर_mux(data->hw_data.hws[clks[i].id]);

	वापस PTR_ERR(hw);
पूर्ण

अटल अचिन्हित दीर्घ bm1880_clk_भाग_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा bm1880_भाग_hw_घड़ी *भाग_hw = to_bm1880_भाग_clk(hw);
	काष्ठा bm1880_भाग_घड़ी *भाग = &भाग_hw->भाग;
	व्योम __iomem *reg_addr = भाग_hw->base + भाग->reg;
	अचिन्हित पूर्णांक val;
	अचिन्हित दीर्घ rate;

	अगर (!(पढ़ोl(reg_addr) & BIT(3))) अणु
		val = भाग->initval;
	पूर्ण अन्यथा अणु
		val = पढ़ोl(reg_addr) >> भाग->shअगरt;
		val &= clk_भाग_mask(भाग->width);
	पूर्ण

	rate = भागider_recalc_rate(hw, parent_rate, val, भाग->table,
				   भाग->flags, भाग->width);

	वापस rate;
पूर्ण

अटल दीर्घ bm1880_clk_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *prate)
अणु
	काष्ठा bm1880_भाग_hw_घड़ी *भाग_hw = to_bm1880_भाग_clk(hw);
	काष्ठा bm1880_भाग_घड़ी *भाग = &भाग_hw->भाग;
	व्योम __iomem *reg_addr = भाग_hw->base + भाग->reg;

	अगर (भाग->flags & CLK_DIVIDER_READ_ONLY) अणु
		u32 val;

		val = पढ़ोl(reg_addr) >> भाग->shअगरt;
		val &= clk_भाग_mask(भाग->width);

		वापस भागider_ro_round_rate(hw, rate, prate, भाग->table,
					     भाग->width, भाग->flags,
					     val);
	पूर्ण

	वापस भागider_round_rate(hw, rate, prate, भाग->table,
				  भाग->width, भाग->flags);
पूर्ण

अटल पूर्णांक bm1880_clk_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा bm1880_भाग_hw_घड़ी *भाग_hw = to_bm1880_भाग_clk(hw);
	काष्ठा bm1880_भाग_घड़ी *भाग = &भाग_hw->भाग;
	व्योम __iomem *reg_addr = भाग_hw->base + भाग->reg;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक value;
	u32 val;

	value = भागider_get_val(rate, parent_rate, भाग->table,
				भाग->width, भाग_hw->भाग.flags);
	अगर (value < 0)
		वापस value;

	अगर (भाग_hw->lock)
		spin_lock_irqsave(भाग_hw->lock, flags);
	अन्यथा
		__acquire(भाग_hw->lock);

	val = पढ़ोl(reg_addr);
	val &= ~(clk_भाग_mask(भाग->width) << भाग_hw->भाग.shअगरt);
	val |= (u32)value << भाग->shअगरt;
	ग_लिखोl(val, reg_addr);

	अगर (भाग_hw->lock)
		spin_unlock_irqrestore(भाग_hw->lock, flags);
	अन्यथा
		__release(भाग_hw->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops bm1880_clk_भाग_ops = अणु
	.recalc_rate = bm1880_clk_भाग_recalc_rate,
	.round_rate = bm1880_clk_भाग_round_rate,
	.set_rate = bm1880_clk_भाग_set_rate,
पूर्ण;

अटल काष्ठा clk_hw *bm1880_clk_रेजिस्टर_भाग(काष्ठा bm1880_भाग_hw_घड़ी *भाग_clk,
					      व्योम __iomem *sys_base)
अणु
	काष्ठा clk_hw *hw;
	पूर्णांक err;

	भाग_clk->भाग.flags = CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO;
	भाग_clk->base = sys_base;
	भाग_clk->lock = &bm1880_clk_lock;

	hw = &भाग_clk->hw;
	err = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (err)
		वापस ERR_PTR(err);

	वापस hw;
पूर्ण

अटल व्योम bm1880_clk_unरेजिस्टर_भाग(काष्ठा clk_hw *hw)
अणु
	काष्ठा bm1880_भाग_hw_घड़ी *भाग_hw = to_bm1880_भाग_clk(hw);

	clk_hw_unरेजिस्टर(hw);
	kमुक्त(भाग_hw);
पूर्ण

अटल पूर्णांक bm1880_clk_रेजिस्टर_भागs(काष्ठा bm1880_भाग_hw_घड़ी *clks,
				    पूर्णांक num_clks,
				    काष्ठा bm1880_घड़ी_data *data)
अणु
	काष्ठा clk_hw *hw;
	व्योम __iomem *sys_base = data->sys_base;
	अचिन्हित पूर्णांक i, id;

	क्रम (i = 0; i < num_clks; i++) अणु
		काष्ठा bm1880_भाग_hw_घड़ी *bm1880_clk = &clks[i];

		hw = bm1880_clk_रेजिस्टर_भाग(bm1880_clk, sys_base);
		अगर (IS_ERR(hw)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, bm1880_clk->भाग.name);
			जाओ err_clk;
		पूर्ण

		id = clks[i].भाग.id;
		data->hw_data.hws[id] = hw;
	पूर्ण

	वापस 0;

err_clk:
	जबतक (i--)
		bm1880_clk_unरेजिस्टर_भाग(data->hw_data.hws[clks[i].भाग.id]);

	वापस PTR_ERR(hw);
पूर्ण

अटल पूर्णांक bm1880_clk_रेजिस्टर_gate(स्थिर काष्ठा bm1880_gate_घड़ी *clks,
				    पूर्णांक num_clks,
				    काष्ठा bm1880_घड़ी_data *data)
अणु
	काष्ठा clk_hw *hw;
	व्योम __iomem *sys_base = data->sys_base;
	पूर्णांक i;

	क्रम (i = 0; i < num_clks; i++) अणु
		hw = clk_hw_रेजिस्टर_gate(शून्य, clks[i].name,
					  clks[i].parent,
					  clks[i].flags,
					  sys_base + clks[i].gate_reg,
					  clks[i].gate_shअगरt, 0,
					  &bm1880_clk_lock);
		अगर (IS_ERR(hw)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जाओ err_clk;
		पूर्ण

		data->hw_data.hws[clks[i].id] = hw;
	पूर्ण

	वापस 0;

err_clk:
	जबतक (i--)
		clk_hw_unरेजिस्टर_gate(data->hw_data.hws[clks[i].id]);

	वापस PTR_ERR(hw);
पूर्ण

अटल काष्ठा clk_hw *bm1880_clk_रेजिस्टर_composite(काष्ठा bm1880_composite_घड़ी *clks,
						    व्योम __iomem *sys_base)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा clk_mux *mux = शून्य;
	काष्ठा clk_gate *gate = शून्य;
	काष्ठा bm1880_भाग_hw_घड़ी *भाग_hws = शून्य;
	काष्ठा clk_hw *mux_hw = शून्य, *gate_hw = शून्य, *भाग_hw = शून्य;
	स्थिर काष्ठा clk_ops *mux_ops = शून्य, *gate_ops = शून्य, *भाग_ops = शून्य;
	स्थिर अक्षर * स्थिर *parent_names;
	स्थिर अक्षर *parent;
	पूर्णांक num_parents;
	पूर्णांक ret;

	अगर (clks->mux_shअगरt >= 0) अणु
		mux = kzalloc(माप(*mux), GFP_KERNEL);
		अगर (!mux)
			वापस ERR_PTR(-ENOMEM);

		mux->reg = sys_base + clks->mux_reg;
		mux->mask = 1;
		mux->shअगरt = clks->mux_shअगरt;
		mux_hw = &mux->hw;
		mux_ops = &clk_mux_ops;
		mux->lock = &bm1880_clk_lock;

		parent_names = clks->parents;
		num_parents = clks->num_parents;
	पूर्ण अन्यथा अणु
		parent = clks->parent;
		parent_names = &parent;
		num_parents = 1;
	पूर्ण

	अगर (clks->gate_shअगरt >= 0) अणु
		gate = kzalloc(माप(*gate), GFP_KERNEL);
		अगर (!gate) अणु
			ret = -ENOMEM;
			जाओ err_out;
		पूर्ण

		gate->reg = sys_base + clks->gate_reg;
		gate->bit_idx = clks->gate_shअगरt;
		gate->lock = &bm1880_clk_lock;

		gate_hw = &gate->hw;
		gate_ops = &clk_gate_ops;
	पूर्ण

	अगर (clks->भाग_shअगरt >= 0) अणु
		भाग_hws = kzalloc(माप(*भाग_hws), GFP_KERNEL);
		अगर (!भाग_hws) अणु
			ret = -ENOMEM;
			जाओ err_out;
		पूर्ण

		भाग_hws->base = sys_base;
		भाग_hws->भाग.reg = clks->भाग_reg;
		भाग_hws->भाग.shअगरt = clks->भाग_shअगरt;
		भाग_hws->भाग.width = clks->भाग_width;
		भाग_hws->भाग.table = clks->table;
		भाग_hws->भाग.initval = clks->भाग_initval;
		भाग_hws->lock = &bm1880_clk_lock;
		भाग_hws->भाग.flags = CLK_DIVIDER_ONE_BASED |
				     CLK_DIVIDER_ALLOW_ZERO;

		भाग_hw = &भाग_hws->hw;
		भाग_ops = &bm1880_clk_भाग_ops;
	पूर्ण

	hw = clk_hw_रेजिस्टर_composite(शून्य, clks->name, parent_names,
				       num_parents, mux_hw, mux_ops, भाग_hw,
				       भाग_ops, gate_hw, gate_ops,
				       clks->flags);

	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ err_out;
	पूर्ण

	वापस hw;

err_out:
	kमुक्त(भाग_hws);
	kमुक्त(gate);
	kमुक्त(mux);

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक bm1880_clk_रेजिस्टर_composites(काष्ठा bm1880_composite_घड़ी *clks,
					  पूर्णांक num_clks,
					  काष्ठा bm1880_घड़ी_data *data)
अणु
	काष्ठा clk_hw *hw;
	व्योम __iomem *sys_base = data->sys_base;
	पूर्णांक i;

	क्रम (i = 0; i < num_clks; i++) अणु
		काष्ठा bm1880_composite_घड़ी *bm1880_clk = &clks[i];

		hw = bm1880_clk_रेजिस्टर_composite(bm1880_clk, sys_base);
		अगर (IS_ERR(hw)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, bm1880_clk->name);
			जाओ err_clk;
		पूर्ण

		data->hw_data.hws[clks[i].id] = hw;
	पूर्ण

	वापस 0;

err_clk:
	जबतक (i--)
		clk_hw_unरेजिस्टर_composite(data->hw_data.hws[clks[i].id]);

	वापस PTR_ERR(hw);
पूर्ण

अटल पूर्णांक bm1880_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bm1880_घड़ी_data *clk_data;
	व्योम __iomem *pll_base, *sys_base;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक num_clks, i;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pll_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(pll_base))
		वापस PTR_ERR(pll_base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	sys_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(sys_base))
		वापस PTR_ERR(sys_base);

	num_clks = ARRAY_SIZE(bm1880_pll_clks) +
		   ARRAY_SIZE(bm1880_भाग_clks) +
		   ARRAY_SIZE(bm1880_mux_clks) +
		   ARRAY_SIZE(bm1880_composite_clks) +
		   ARRAY_SIZE(bm1880_gate_clks);

	clk_data = devm_kzalloc(dev, काष्ठा_size(clk_data, hw_data.hws,
						 num_clks), GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	clk_data->pll_base = pll_base;
	clk_data->sys_base = sys_base;

	क्रम (i = 0; i < num_clks; i++)
		clk_data->hw_data.hws[i] = ERR_PTR(-ENOENT);

	clk_data->hw_data.num = num_clks;

	bm1880_clk_रेजिस्टर_plls(bm1880_pll_clks,
				 ARRAY_SIZE(bm1880_pll_clks),
				 clk_data);

	bm1880_clk_रेजिस्टर_भागs(bm1880_भाग_clks,
				 ARRAY_SIZE(bm1880_भाग_clks),
				 clk_data);

	bm1880_clk_रेजिस्टर_mux(bm1880_mux_clks,
				ARRAY_SIZE(bm1880_mux_clks),
				clk_data);

	bm1880_clk_रेजिस्टर_composites(bm1880_composite_clks,
				       ARRAY_SIZE(bm1880_composite_clks),
				       clk_data);

	bm1880_clk_रेजिस्टर_gate(bm1880_gate_clks,
				 ARRAY_SIZE(bm1880_gate_clks),
				 clk_data);

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
				      &clk_data->hw_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id bm1880_of_match[] = अणु
	अणु .compatible = "bitmain,bm1880-clk", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bm1880_of_match);

अटल काष्ठा platक्रमm_driver bm1880_clk_driver = अणु
	.driver = अणु
		.name = "bm1880-clk",
		.of_match_table = bm1880_of_match,
	पूर्ण,
	.probe = bm1880_clk_probe,
पूर्ण;
module_platक्रमm_driver(bm1880_clk_driver);

MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_DESCRIPTION("Clock driver for Bitmain BM1880 SoC");
MODULE_LICENSE("GPL v2");
