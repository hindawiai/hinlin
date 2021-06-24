<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2008 Cavium Networks
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/atomic.h>
#समावेश "cns3xxx.h"
#समावेश "pm.h"
#समावेश "core.h"

व्योम cns3xxx_pwr_clk_en(अचिन्हित पूर्णांक block)
अणु
	u32 reg = __raw_पढ़ोl(PM_CLK_GATE_REG);

	reg |= (block & PM_CLK_GATE_REG_MASK);
	__raw_ग_लिखोl(reg, PM_CLK_GATE_REG);
पूर्ण
EXPORT_SYMBOL(cns3xxx_pwr_clk_en);

व्योम cns3xxx_pwr_clk_dis(अचिन्हित पूर्णांक block)
अणु
	u32 reg = __raw_पढ़ोl(PM_CLK_GATE_REG);

	reg &= ~(block & PM_CLK_GATE_REG_MASK);
	__raw_ग_लिखोl(reg, PM_CLK_GATE_REG);
पूर्ण
EXPORT_SYMBOL(cns3xxx_pwr_clk_dis);

व्योम cns3xxx_pwr_घातer_up(अचिन्हित पूर्णांक block)
अणु
	u32 reg = __raw_पढ़ोl(PM_PLL_HM_PD_CTRL_REG);

	reg &= ~(block & CNS3XXX_PWR_PLL_ALL);
	__raw_ग_लिखोl(reg, PM_PLL_HM_PD_CTRL_REG);

	/* Wait क्रम 300us क्रम the PLL output घड़ी locked. */
	udelay(300);
पूर्ण;
EXPORT_SYMBOL(cns3xxx_pwr_घातer_up);

व्योम cns3xxx_pwr_घातer_करोwn(अचिन्हित पूर्णांक block)
अणु
	u32 reg = __raw_पढ़ोl(PM_PLL_HM_PD_CTRL_REG);

	/* ग_लिखो '1' to घातer करोwn */
	reg |= (block & CNS3XXX_PWR_PLL_ALL);
	__raw_ग_लिखोl(reg, PM_PLL_HM_PD_CTRL_REG);
पूर्ण;
EXPORT_SYMBOL(cns3xxx_pwr_घातer_करोwn);

अटल व्योम cns3xxx_pwr_soft_rst_क्रमce(अचिन्हित पूर्णांक block)
अणु
	u32 reg = __raw_पढ़ोl(PM_SOFT_RST_REG);

	/*
	 * bit 0, 28, 29 => program low to reset,
	 * the other अन्यथा program low and then high
	 */
	अगर (block & 0x30000001) अणु
		reg &= ~(block & PM_SOFT_RST_REG_MASK);
	पूर्ण अन्यथा अणु
		reg &= ~(block & PM_SOFT_RST_REG_MASK);
		__raw_ग_लिखोl(reg, PM_SOFT_RST_REG);
		reg |= (block & PM_SOFT_RST_REG_MASK);
	पूर्ण

	__raw_ग_लिखोl(reg, PM_SOFT_RST_REG);
पूर्ण

व्योम cns3xxx_pwr_soft_rst(अचिन्हित पूर्णांक block)
अणु
	अटल अचिन्हित पूर्णांक soft_reset;

	अगर (soft_reset & block) अणु
		/* SPI/I2C/GPIO use the same block, reset once. */
		वापस;
	पूर्ण अन्यथा अणु
		soft_reset |= block;
	पूर्ण
	cns3xxx_pwr_soft_rst_क्रमce(block);
पूर्ण
EXPORT_SYMBOL(cns3xxx_pwr_soft_rst);

व्योम cns3xxx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	/*
	 * To reset, we hit the on-board reset रेजिस्टर
	 * in the प्रणाली FPGA.
	 */
	cns3xxx_pwr_soft_rst(CNS3XXX_PWR_SOFTWARE_RST(GLOBAL));
पूर्ण

/*
 * cns3xxx_cpu_घड़ी - वापस CPU/L2 घड़ी
 *  aclk: cpu घड़ी/2
 *  hclk: cpu घड़ी/4
 *  pclk: cpu घड़ी/8
 */
पूर्णांक cns3xxx_cpu_घड़ी(व्योम)
अणु
	u32 reg = __raw_पढ़ोl(PM_CLK_CTRL_REG);
	पूर्णांक cpu;
	पूर्णांक cpu_sel;
	पूर्णांक भाग_sel;

	cpu_sel = (reg >> PM_CLK_CTRL_REG_OFFSET_PLL_CPU_SEL) & 0xf;
	भाग_sel = (reg >> PM_CLK_CTRL_REG_OFFSET_CPU_CLK_DIV) & 0x3;

	cpu = (300 + ((cpu_sel / 3) * 100) + ((cpu_sel % 3) * 33)) >> भाग_sel;

	वापस cpu;
पूर्ण
EXPORT_SYMBOL(cns3xxx_cpu_घड़ी);

atomic_t usb_pwr_ref = ATOMIC_INIT(0);
EXPORT_SYMBOL(usb_pwr_ref);
