<शैली गुरु>
/*
 * Clk driver क्रम NXP LPC18xx/LPC43xx Clock Control Unit (CCU)
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <dt-bindings/घड़ी/lpc18xx-ccu.h>

/* Bit defines क्रम CCU branch configuration रेजिस्टर */
#घोषणा LPC18XX_CCU_RUN		BIT(0)
#घोषणा LPC18XX_CCU_AUTO	BIT(1)
#घोषणा LPC18XX_CCU_DIV		BIT(5)
#घोषणा LPC18XX_CCU_DIVSTAT	BIT(27)

/* CCU branch feature bits */
#घोषणा CCU_BRANCH_IS_BUS	BIT(0)
#घोषणा CCU_BRANCH_HAVE_DIV2	BIT(1)

काष्ठा lpc18xx_branch_clk_data अणु
	स्थिर अक्षर **name;
	पूर्णांक num;
पूर्ण;

काष्ठा lpc18xx_clk_branch अणु
	स्थिर अक्षर *base_name;
	स्थिर अक्षर *name;
	u16 offset;
	u16 flags;
	काष्ठा clk *clk;
	काष्ठा clk_gate gate;
पूर्ण;

अटल काष्ठा lpc18xx_clk_branch clk_branches[] = अणु
	अणु"base_apb3_clk", "apb3_bus",		CLK_APB3_BUS,		CCU_BRANCH_IS_BUSपूर्ण,
	अणु"base_apb3_clk", "apb3_i2c1",		CLK_APB3_I2C1,		0पूर्ण,
	अणु"base_apb3_clk", "apb3_dac",		CLK_APB3_DAC,		0पूर्ण,
	अणु"base_apb3_clk", "apb3_adc0",		CLK_APB3_ADC0,		0पूर्ण,
	अणु"base_apb3_clk", "apb3_adc1",		CLK_APB3_ADC1,		0पूर्ण,
	अणु"base_apb3_clk", "apb3_can0",		CLK_APB3_CAN0,		0पूर्ण,

	अणु"base_apb1_clk", "apb1_bus",		CLK_APB1_BUS,		CCU_BRANCH_IS_BUSपूर्ण,
	अणु"base_apb1_clk", "apb1_mc_pwm",	CLK_APB1_MOTOCON_PWM,	0पूर्ण,
	अणु"base_apb1_clk", "apb1_i2c0",		CLK_APB1_I2C0,		0पूर्ण,
	अणु"base_apb1_clk", "apb1_i2s",		CLK_APB1_I2S,		0पूर्ण,
	अणु"base_apb1_clk", "apb1_can1",		CLK_APB1_CAN1,		0पूर्ण,

	अणु"base_spifi_clk", "spifi",		CLK_SPIFI,		0पूर्ण,

	अणु"base_cpu_clk", "cpu_bus",		CLK_CPU_BUS,		CCU_BRANCH_IS_BUSपूर्ण,
	अणु"base_cpu_clk", "cpu_spifi",		CLK_CPU_SPIFI,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_gpio",		CLK_CPU_GPIO,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_lcd",		CLK_CPU_LCD,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_ethernet",	CLK_CPU_ETHERNET,	0पूर्ण,
	अणु"base_cpu_clk", "cpu_usb0",		CLK_CPU_USB0,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_emc",		CLK_CPU_EMC,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_sdio",		CLK_CPU_SDIO,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_dma",		CLK_CPU_DMA,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_core",		CLK_CPU_CORE,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_sct",		CLK_CPU_SCT,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_usb1",		CLK_CPU_USB1,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_emcdiv",		CLK_CPU_EMCDIV,		CCU_BRANCH_HAVE_DIV2पूर्ण,
	अणु"base_cpu_clk", "cpu_flasha",		CLK_CPU_FLASHA,		CCU_BRANCH_HAVE_DIV2पूर्ण,
	अणु"base_cpu_clk", "cpu_flashb",		CLK_CPU_FLASHB,		CCU_BRANCH_HAVE_DIV2पूर्ण,
	अणु"base_cpu_clk", "cpu_m0app",		CLK_CPU_M0APP,		CCU_BRANCH_HAVE_DIV2पूर्ण,
	अणु"base_cpu_clk", "cpu_adchs",		CLK_CPU_ADCHS,		CCU_BRANCH_HAVE_DIV2पूर्ण,
	अणु"base_cpu_clk", "cpu_eeprom",		CLK_CPU_EEPROM,		CCU_BRANCH_HAVE_DIV2पूर्ण,
	अणु"base_cpu_clk", "cpu_wwdt",		CLK_CPU_WWDT,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_uart0",		CLK_CPU_UART0,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_uart1",		CLK_CPU_UART1,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_ssp0",		CLK_CPU_SSP0,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_timer0",		CLK_CPU_TIMER0,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_timer1",		CLK_CPU_TIMER1,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_scu",		CLK_CPU_SCU,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_creg",		CLK_CPU_CREG,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_ritimer",		CLK_CPU_RITIMER,	0पूर्ण,
	अणु"base_cpu_clk", "cpu_uart2",		CLK_CPU_UART2,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_uart3",		CLK_CPU_UART3,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_timer2",		CLK_CPU_TIMER2,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_timer3",		CLK_CPU_TIMER3,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_ssp1",		CLK_CPU_SSP1,		0पूर्ण,
	अणु"base_cpu_clk", "cpu_qei",		CLK_CPU_QEI,		0पूर्ण,

	अणु"base_periph_clk", "periph_bus",	CLK_PERIPH_BUS,		CCU_BRANCH_IS_BUSपूर्ण,
	अणु"base_periph_clk", "periph_core",	CLK_PERIPH_CORE,	0पूर्ण,
	अणु"base_periph_clk", "periph_sgpio",	CLK_PERIPH_SGPIO,	0पूर्ण,

	अणु"base_usb0_clk",  "usb0",		CLK_USB0,		0पूर्ण,
	अणु"base_usb1_clk",  "usb1",		CLK_USB1,		0पूर्ण,
	अणु"base_spi_clk",   "spi",		CLK_SPI,		0पूर्ण,
	अणु"base_adchs_clk", "adchs",		CLK_ADCHS,		0पूर्ण,

	अणु"base_audio_clk", "audio",		CLK_AUDIO,		0पूर्ण,
	अणु"base_uart3_clk", "apb2_uart3",	CLK_APB2_UART3,		0पूर्ण,
	अणु"base_uart2_clk", "apb2_uart2",	CLK_APB2_UART2,		0पूर्ण,
	अणु"base_uart1_clk", "apb0_uart1",	CLK_APB0_UART1,		0पूर्ण,
	अणु"base_uart0_clk", "apb0_uart0",	CLK_APB0_UART0,		0पूर्ण,
	अणु"base_ssp1_clk",  "apb2_ssp1",		CLK_APB2_SSP1,		0पूर्ण,
	अणु"base_ssp0_clk",  "apb0_ssp0",		CLK_APB0_SSP0,		0पूर्ण,
	अणु"base_sdio_clk",  "sdio",		CLK_SDIO,		0पूर्ण,
पूर्ण;

अटल काष्ठा clk *lpc18xx_ccu_branch_clk_get(काष्ठा of_phandle_args *clkspec,
					      व्योम *data)
अणु
	काष्ठा lpc18xx_branch_clk_data *clk_data = data;
	अचिन्हित पूर्णांक offset = clkspec->args[0];
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(clk_branches); i++) अणु
		अगर (clk_branches[i].offset != offset)
			जारी;

		क्रम (j = 0; j < clk_data->num; j++) अणु
			अगर (!म_भेद(clk_branches[i].base_name, clk_data->name[j]))
				वापस clk_branches[i].clk;
		पूर्ण
	पूर्ण

	pr_err("%s: invalid clock offset %d\n", __func__, offset);

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक lpc18xx_ccu_gate_endisable(काष्ठा clk_hw *hw, bool enable)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	u32 val;

	/*
	 * Divider field is ग_लिखो only, so भागider stat field must
	 * be पढ़ो so भागider field can be set accordingly.
	 */
	val = पढ़ोl(gate->reg);
	अगर (val & LPC18XX_CCU_DIVSTAT)
		val |= LPC18XX_CCU_DIV;

	अगर (enable) अणु
		val |= LPC18XX_CCU_RUN;
	पूर्ण अन्यथा अणु
		/*
		 * To safely disable a branch घड़ी a squence of two separate
		 * ग_लिखोs must be used. First ग_लिखो should set the AUTO bit
		 * and the next ग_लिखो should clear the RUN bit.
		 */
		val |= LPC18XX_CCU_AUTO;
		ग_लिखोl(val, gate->reg);

		val &= ~LPC18XX_CCU_RUN;
	पूर्ण

	ग_लिखोl(val, gate->reg);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_ccu_gate_enable(काष्ठा clk_hw *hw)
अणु
	वापस lpc18xx_ccu_gate_endisable(hw, true);
पूर्ण

अटल व्योम lpc18xx_ccu_gate_disable(काष्ठा clk_hw *hw)
अणु
	lpc18xx_ccu_gate_endisable(hw, false);
पूर्ण

अटल पूर्णांक lpc18xx_ccu_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	स्थिर काष्ठा clk_hw *parent;

	/*
	 * The branch घड़ी रेजिस्टरs are only accessible
	 * अगर the base (parent) घड़ी is enabled. Register
	 * access with a disabled base घड़ी will hang the
	 * प्रणाली.
	 */
	parent = clk_hw_get_parent(hw);
	अगर (!parent)
		वापस 0;

	अगर (!clk_hw_is_enabled(parent))
		वापस 0;

	वापस clk_gate_ops.is_enabled(hw);
पूर्ण

अटल स्थिर काष्ठा clk_ops lpc18xx_ccu_gate_ops = अणु
	.enable		= lpc18xx_ccu_gate_enable,
	.disable	= lpc18xx_ccu_gate_disable,
	.is_enabled	= lpc18xx_ccu_gate_is_enabled,
पूर्ण;

अटल व्योम lpc18xx_ccu_रेजिस्टर_branch_gate_भाग(काष्ठा lpc18xx_clk_branch *branch,
						 व्योम __iomem *reg_base,
						 स्थिर अक्षर *parent)
अणु
	स्थिर काष्ठा clk_ops *भाग_ops = शून्य;
	काष्ठा clk_भागider *भाग = शून्य;
	काष्ठा clk_hw *भाग_hw = शून्य;

	अगर (branch->flags & CCU_BRANCH_HAVE_DIV2) अणु
		भाग = kzalloc(माप(*भाग), GFP_KERNEL);
		अगर (!भाग)
			वापस;

		भाग->reg = branch->offset + reg_base;
		भाग->flags = CLK_DIVIDER_READ_ONLY;
		भाग->shअगरt = 27;
		भाग->width = 1;

		भाग_hw = &भाग->hw;
		भाग_ops = &clk_भागider_ro_ops;
	पूर्ण

	branch->gate.reg = branch->offset + reg_base;
	branch->gate.bit_idx = 0;

	branch->clk = clk_रेजिस्टर_composite(शून्य, branch->name, &parent, 1,
					     शून्य, शून्य,
					     भाग_hw, भाग_ops,
					     &branch->gate.hw, &lpc18xx_ccu_gate_ops, 0);
	अगर (IS_ERR(branch->clk)) अणु
		kमुक्त(भाग);
		pr_warn("%s: failed to register %s\n", __func__, branch->name);
		वापस;
	पूर्ण

	/* Grab essential branch घड़ीs क्रम CPU and SDRAM */
	चयन (branch->offset) अणु
	हाल CLK_CPU_EMC:
	हाल CLK_CPU_CORE:
	हाल CLK_CPU_CREG:
	हाल CLK_CPU_EMCDIV:
		clk_prepare_enable(branch->clk);
	पूर्ण
पूर्ण

अटल व्योम lpc18xx_ccu_रेजिस्टर_branch_clks(व्योम __iomem *reg_base,
					     स्थिर अक्षर *base_name)
अणु
	स्थिर अक्षर *parent = base_name;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(clk_branches); i++) अणु
		अगर (म_भेद(clk_branches[i].base_name, base_name))
			जारी;

		lpc18xx_ccu_रेजिस्टर_branch_gate_भाग(&clk_branches[i], reg_base,
						     parent);

		अगर (clk_branches[i].flags & CCU_BRANCH_IS_BUS)
			parent = clk_branches[i].name;
	पूर्ण
पूर्ण

अटल व्योम __init lpc18xx_ccu_init(काष्ठा device_node *np)
अणु
	काष्ठा lpc18xx_branch_clk_data *clk_data;
	व्योम __iomem *reg_base;
	पूर्णांक i, ret;

	reg_base = of_iomap(np, 0);
	अगर (!reg_base) अणु
		pr_warn("%s: failed to map address range\n", __func__);
		वापस;
	पूर्ण

	clk_data = kzalloc(माप(*clk_data), GFP_KERNEL);
	अगर (!clk_data) अणु
		iounmap(reg_base);
		वापस;
	पूर्ण

	clk_data->num = of_property_count_strings(np, "clock-names");
	clk_data->name = kसुस्मृति(clk_data->num, माप(अक्षर *), GFP_KERNEL);
	अगर (!clk_data->name) अणु
		iounmap(reg_base);
		kमुक्त(clk_data);
		वापस;
	पूर्ण

	क्रम (i = 0; i < clk_data->num; i++) अणु
		ret = of_property_पढ़ो_string_index(np, "clock-names", i,
						    &clk_data->name[i]);
		अगर (ret) अणु
			pr_warn("%s: failed to get clock name at idx %d\n",
				__func__, i);
			जारी;
		पूर्ण

		lpc18xx_ccu_रेजिस्टर_branch_clks(reg_base, clk_data->name[i]);
	पूर्ण

	of_clk_add_provider(np, lpc18xx_ccu_branch_clk_get, clk_data);
पूर्ण
CLK_OF_DECLARE(lpc18xx_ccu, "nxp,lpc1850-ccu", lpc18xx_ccu_init);
