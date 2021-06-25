<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 Atheros Communications, Inc.,  All Rights Reserved.
 * Copyright (C) 2006 FON Technology, SL.
 * Copyright (C) 2006 Imre Kaloz <kaloz@खोलोwrt.org>
 * Copyright (C) 2006 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2012 Alexandros C. Couloumbis <alex@ozo.com>
 */

/*
 * Platक्रमm devices क्रम Atheros AR2315 SoCs
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/memblock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/समय.स>

#समावेश <ath25_platक्रमm.h>

#समावेश "devices.h"
#समावेश "ar2315.h"
#समावेश "ar2315_regs.h"

अटल व्योम __iomem *ar2315_rst_base;
अटल काष्ठा irq_करोमुख्य *ar2315_misc_irq_करोमुख्य;

अटल अंतरभूत u32 ar2315_rst_reg_पढ़ो(u32 reg)
अणु
	वापस __raw_पढ़ोl(ar2315_rst_base + reg);
पूर्ण

अटल अंतरभूत व्योम ar2315_rst_reg_ग_लिखो(u32 reg, u32 val)
अणु
	__raw_ग_लिखोl(val, ar2315_rst_base + reg);
पूर्ण

अटल अंतरभूत व्योम ar2315_rst_reg_mask(u32 reg, u32 mask, u32 val)
अणु
	u32 ret = ar2315_rst_reg_पढ़ो(reg);

	ret &= ~mask;
	ret |= val;
	ar2315_rst_reg_ग_लिखो(reg, ret);
पूर्ण

अटल irqवापस_t ar2315_ahb_err_handler(पूर्णांक cpl, व्योम *dev_id)
अणु
	ar2315_rst_reg_ग_लिखो(AR2315_AHB_ERR0, AR2315_AHB_ERROR_DET);
	ar2315_rst_reg_पढ़ो(AR2315_AHB_ERR1);

	pr_emerg("AHB fatal error\n");
	machine_restart("AHB error"); /* Catastrophic failure */

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ar2315_misc_irq_handler(काष्ठा irq_desc *desc)
अणु
	u32 pending = ar2315_rst_reg_पढ़ो(AR2315_ISR) &
		      ar2315_rst_reg_पढ़ो(AR2315_IMR);
	अचिन्हित nr, misc_irq = 0;

	अगर (pending) अणु
		काष्ठा irq_करोमुख्य *करोमुख्य = irq_desc_get_handler_data(desc);

		nr = __ffs(pending);
		misc_irq = irq_find_mapping(करोमुख्य, nr);
	पूर्ण

	अगर (misc_irq) अणु
		अगर (nr == AR2315_MISC_IRQ_GPIO)
			ar2315_rst_reg_ग_लिखो(AR2315_ISR, AR2315_ISR_GPIO);
		अन्यथा अगर (nr == AR2315_MISC_IRQ_WATCHDOG)
			ar2315_rst_reg_ग_लिखो(AR2315_ISR, AR2315_ISR_WD);
		generic_handle_irq(misc_irq);
	पूर्ण अन्यथा अणु
		spurious_पूर्णांकerrupt();
	पूर्ण
पूर्ण

अटल व्योम ar2315_misc_irq_unmask(काष्ठा irq_data *d)
अणु
	ar2315_rst_reg_mask(AR2315_IMR, 0, BIT(d->hwirq));
पूर्ण

अटल व्योम ar2315_misc_irq_mask(काष्ठा irq_data *d)
अणु
	ar2315_rst_reg_mask(AR2315_IMR, BIT(d->hwirq), 0);
पूर्ण

अटल काष्ठा irq_chip ar2315_misc_irq_chip = अणु
	.name		= "ar2315-misc",
	.irq_unmask	= ar2315_misc_irq_unmask,
	.irq_mask	= ar2315_misc_irq_mask,
पूर्ण;

अटल पूर्णांक ar2315_misc_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित irq,
			       irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(irq, &ar2315_misc_irq_chip, handle_level_irq);
	वापस 0;
पूर्ण

अटल काष्ठा irq_करोमुख्य_ops ar2315_misc_irq_करोमुख्य_ops = अणु
	.map = ar2315_misc_irq_map,
पूर्ण;

/*
 * Called when an पूर्णांकerrupt is received, this function
 * determines exactly which पूर्णांकerrupt it was, and it
 * invokes the appropriate handler.
 *
 * Implicitly, we also define पूर्णांकerrupt priority by
 * choosing which to dispatch first.
 */
अटल व्योम ar2315_irq_dispatch(व्योम)
अणु
	u32 pending = पढ़ो_c0_status() & पढ़ो_c0_cause();

	अगर (pending & CAUSEF_IP3)
		करो_IRQ(AR2315_IRQ_WLAN0);
#अगर_घोषित CONFIG_PCI_AR2315
	अन्यथा अगर (pending & CAUSEF_IP5)
		करो_IRQ(AR2315_IRQ_LCBUS_PCI);
#पूर्ण_अगर
	अन्यथा अगर (pending & CAUSEF_IP2)
		करो_IRQ(AR2315_IRQ_MISC);
	अन्यथा अगर (pending & CAUSEF_IP7)
		करो_IRQ(ATH25_IRQ_CPU_CLOCK);
	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

व्योम __init ar2315_arch_init_irq(व्योम)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित irq;

	ath25_irq_dispatch = ar2315_irq_dispatch;

	करोमुख्य = irq_करोमुख्य_add_linear(शून्य, AR2315_MISC_IRQ_COUNT,
				       &ar2315_misc_irq_करोमुख्य_ops, शून्य);
	अगर (!करोमुख्य)
		panic("Failed to add IRQ domain");

	irq = irq_create_mapping(करोमुख्य, AR2315_MISC_IRQ_AHB);
	अगर (request_irq(irq, ar2315_ahb_err_handler, 0, "ar2315-ahb-error",
			शून्य))
		pr_err("Failed to register ar2315-ahb-error interrupt\n");

	irq_set_chained_handler_and_data(AR2315_IRQ_MISC,
					 ar2315_misc_irq_handler, करोमुख्य);

	ar2315_misc_irq_करोमुख्य = करोमुख्य;
पूर्ण

व्योम __init ar2315_init_devices(व्योम)
अणु
	/* Find board configuration */
	ath25_find_config(AR2315_SPI_READ_BASE, AR2315_SPI_READ_SIZE);

	ath25_add_wmac(0, AR2315_WLAN0_BASE, AR2315_IRQ_WLAN0);
पूर्ण

अटल व्योम ar2315_restart(अक्षर *command)
अणु
	व्योम (*mips_reset_vec)(व्योम) = (व्योम *)0xbfc00000;

	local_irq_disable();

	/* try reset the प्रणाली via reset control */
	ar2315_rst_reg_ग_लिखो(AR2315_COLD_RESET, AR2317_RESET_SYSTEM);

	/* Cold reset करोes not work on the AR2315/6, use the GPIO reset bits
	 * a workaround. Give it some समय to attempt a gpio based hardware
	 * reset (atheros reference design workaround) */

	/* TODO: implement the GPIO reset workaround */

	/* Some boards (e.g. Senao EOC-2610) करोn't implement the reset logic
	 * workaround. Attempt to jump to the mips reset location -
	 * the boot loader itself might be able to recover the प्रणाली */
	mips_reset_vec();
पूर्ण

/*
 * This table is indexed by bits 5..4 of the CLOCKCTL1 रेजिस्टर
 * to determine the predevisor value.
 */
अटल पूर्णांक घड़ीctl1_preभागide_table[4] __initdata = अणु 1, 2, 4, 5 पूर्ण;
अटल पूर्णांक pllc_भागide_table[5] __initdata = अणु 2, 3, 4, 6, 3 पूर्ण;

अटल अचिन्हित __init ar2315_sys_clk(u32 घड़ी_ctl)
अणु
	अचिन्हित पूर्णांक pllc_ctrl, cpu_भाग;
	अचिन्हित पूर्णांक pllc_out, refभाग, fभाग, भागby2;
	अचिन्हित पूर्णांक clk_भाग;

	pllc_ctrl = ar2315_rst_reg_पढ़ो(AR2315_PLLC_CTL);
	refभाग = ATH25_REG_MS(pllc_ctrl, AR2315_PLLC_REF_DIV);
	refभाग = घड़ीctl1_preभागide_table[refभाग];
	fभाग = ATH25_REG_MS(pllc_ctrl, AR2315_PLLC_FDBACK_DIV);
	भागby2 = ATH25_REG_MS(pllc_ctrl, AR2315_PLLC_ADD_FDBACK_DIV) + 1;
	pllc_out = (40000000 / refभाग) * (2 * भागby2) * fभाग;

	/* clkm input selected */
	चयन (घड़ी_ctl & AR2315_CPUCLK_CLK_SEL_M) अणु
	हाल 0:
	हाल 1:
		clk_भाग = ATH25_REG_MS(pllc_ctrl, AR2315_PLLC_CLKM_DIV);
		clk_भाग = pllc_भागide_table[clk_भाग];
		अवरोध;
	हाल 2:
		clk_भाग = ATH25_REG_MS(pllc_ctrl, AR2315_PLLC_CLKC_DIV);
		clk_भाग = pllc_भागide_table[clk_भाग];
		अवरोध;
	शेष:
		pllc_out = 40000000;
		clk_भाग = 1;
		अवरोध;
	पूर्ण

	cpu_भाग = ATH25_REG_MS(घड़ी_ctl, AR2315_CPUCLK_CLK_DIV);
	cpu_भाग = cpu_भाग * 2 ?: 1;

	वापस pllc_out / (clk_भाग * cpu_भाग);
पूर्ण

अटल अंतरभूत अचिन्हित ar2315_cpu_frequency(व्योम)
अणु
	वापस ar2315_sys_clk(ar2315_rst_reg_पढ़ो(AR2315_CPUCLK));
पूर्ण

अटल अंतरभूत अचिन्हित ar2315_apb_frequency(व्योम)
अणु
	वापस ar2315_sys_clk(ar2315_rst_reg_पढ़ो(AR2315_AMBACLK));
पूर्ण

व्योम __init ar2315_plat_समय_init(व्योम)
अणु
	mips_hpt_frequency = ar2315_cpu_frequency() / 2;
पूर्ण

व्योम __init ar2315_plat_mem_setup(व्योम)
अणु
	व्योम __iomem *sdram_base;
	u32 memsize, memcfg;
	u32 devid;
	u32 config;

	/* Detect memory size */
	sdram_base = ioremap(AR2315_SDRAMCTL_BASE,
				     AR2315_SDRAMCTL_SIZE);
	memcfg = __raw_पढ़ोl(sdram_base + AR2315_MEM_CFG);
	memsize   = 1 + ATH25_REG_MS(memcfg, AR2315_MEM_CFG_DATA_WIDTH);
	memsize <<= 1 + ATH25_REG_MS(memcfg, AR2315_MEM_CFG_COL_WIDTH);
	memsize <<= 1 + ATH25_REG_MS(memcfg, AR2315_MEM_CFG_ROW_WIDTH);
	memsize <<= 3;
	memblock_add(0, memsize);
	iounmap(sdram_base);

	ar2315_rst_base = ioremap(AR2315_RST_BASE, AR2315_RST_SIZE);

	/* Detect the hardware based on the device ID */
	devid = ar2315_rst_reg_पढ़ो(AR2315_SREV) & AR2315_REV_CHIP;
	चयन (devid) अणु
	हाल 0x91:	/* Need to check */
		ath25_soc = ATH25_SOC_AR2318;
		अवरोध;
	हाल 0x90:
		ath25_soc = ATH25_SOC_AR2317;
		अवरोध;
	हाल 0x87:
		ath25_soc = ATH25_SOC_AR2316;
		अवरोध;
	हाल 0x86:
	शेष:
		ath25_soc = ATH25_SOC_AR2315;
		अवरोध;
	पूर्ण
	ath25_board.devid = devid;

	/* Clear any lingering AHB errors */
	config = पढ़ो_c0_config();
	ग_लिखो_c0_config(config & ~0x3);
	ar2315_rst_reg_ग_लिखो(AR2315_AHB_ERR0, AR2315_AHB_ERROR_DET);
	ar2315_rst_reg_पढ़ो(AR2315_AHB_ERR1);
	ar2315_rst_reg_ग_लिखो(AR2315_WDT_CTRL, AR2315_WDT_CTRL_IGNORE);

	_machine_restart = ar2315_restart;
पूर्ण

#अगर_घोषित CONFIG_PCI_AR2315
अटल काष्ठा resource ar2315_pci_res[] = अणु
	अणु
		.name = "ar2315-pci-ctrl",
		.flags = IORESOURCE_MEM,
		.start = AR2315_PCI_BASE,
		.end = AR2315_PCI_BASE + AR2315_PCI_SIZE - 1,
	पूर्ण,
	अणु
		.name = "ar2315-pci-ext",
		.flags = IORESOURCE_MEM,
		.start = AR2315_PCI_EXT_BASE,
		.end = AR2315_PCI_EXT_BASE + AR2315_PCI_EXT_SIZE - 1,
	पूर्ण,
	अणु
		.name = "ar2315-pci",
		.flags = IORESOURCE_IRQ,
		.start = AR2315_IRQ_LCBUS_PCI,
		.end = AR2315_IRQ_LCBUS_PCI,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

व्योम __init ar2315_arch_init(व्योम)
अणु
	अचिन्हित irq = irq_create_mapping(ar2315_misc_irq_करोमुख्य,
					  AR2315_MISC_IRQ_UART0);

	ath25_serial_setup(AR2315_UART0_BASE, irq, ar2315_apb_frequency());

#अगर_घोषित CONFIG_PCI_AR2315
	अगर (ath25_soc == ATH25_SOC_AR2315) अणु
		/* Reset PCI DMA logic */
		ar2315_rst_reg_mask(AR2315_RESET, 0, AR2315_RESET_PCIDMA);
		msleep(20);
		ar2315_rst_reg_mask(AR2315_RESET, AR2315_RESET_PCIDMA, 0);
		msleep(20);

		/* Configure endians */
		ar2315_rst_reg_mask(AR2315_ENDIAN_CTL, 0, AR2315_CONFIG_PCIAHB |
				    AR2315_CONFIG_PCIAHB_BRIDGE);

		/* Configure as PCI host with DMA */
		ar2315_rst_reg_ग_लिखो(AR2315_PCICLK, AR2315_PCICLK_PLLC_CLKM |
				  (AR2315_PCICLK_IN_FREQ_DIV_6 <<
				   AR2315_PCICLK_DIV_S));
		ar2315_rst_reg_mask(AR2315_AHB_ARB_CTL, 0, AR2315_ARB_PCI);
		ar2315_rst_reg_mask(AR2315_IF_CTL, AR2315_IF_PCI_CLK_MASK |
				    AR2315_IF_MASK, AR2315_IF_PCI |
				    AR2315_IF_PCI_HOST | AR2315_IF_PCI_INTR |
				    (AR2315_IF_PCI_CLK_OUTPUT_CLK <<
				     AR2315_IF_PCI_CLK_SHIFT));

		platक्रमm_device_रेजिस्टर_simple("ar2315-pci", -1,
						ar2315_pci_res,
						ARRAY_SIZE(ar2315_pci_res));
	पूर्ण
#पूर्ण_अगर
पूर्ण
