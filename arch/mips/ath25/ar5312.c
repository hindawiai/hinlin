<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 Atheros Communications, Inc.,  All Rights Reserved.
 * Copyright (C) 2006 FON Technology, SL.
 * Copyright (C) 2006 Imre Kaloz <kaloz@खोलोwrt.org>
 * Copyright (C) 2006-2009 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2012 Alexandros C. Couloumbis <alex@ozo.com>
 */

/*
 * Platक्रमm devices क्रम Atheros AR5312 SoCs
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/memblock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/reboot.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/समय.स>

#समावेश <ath25_platक्रमm.h>

#समावेश "devices.h"
#समावेश "ar5312.h"
#समावेश "ar5312_regs.h"

अटल व्योम __iomem *ar5312_rst_base;
अटल काष्ठा irq_करोमुख्य *ar5312_misc_irq_करोमुख्य;

अटल अंतरभूत u32 ar5312_rst_reg_पढ़ो(u32 reg)
अणु
	वापस __raw_पढ़ोl(ar5312_rst_base + reg);
पूर्ण

अटल अंतरभूत व्योम ar5312_rst_reg_ग_लिखो(u32 reg, u32 val)
अणु
	__raw_ग_लिखोl(val, ar5312_rst_base + reg);
पूर्ण

अटल अंतरभूत व्योम ar5312_rst_reg_mask(u32 reg, u32 mask, u32 val)
अणु
	u32 ret = ar5312_rst_reg_पढ़ो(reg);

	ret &= ~mask;
	ret |= val;
	ar5312_rst_reg_ग_लिखो(reg, ret);
पूर्ण

अटल irqवापस_t ar5312_ahb_err_handler(पूर्णांक cpl, व्योम *dev_id)
अणु
	u32 proc1 = ar5312_rst_reg_पढ़ो(AR5312_PROC1);
	u32 proc_addr = ar5312_rst_reg_पढ़ो(AR5312_PROCADDR); /* clears error */
	u32 dma1 = ar5312_rst_reg_पढ़ो(AR5312_DMA1);
	u32 dma_addr = ar5312_rst_reg_पढ़ो(AR5312_DMAADDR);   /* clears error */

	pr_emerg("AHB interrupt: PROCADDR=0x%8.8x PROC1=0x%8.8x DMAADDR=0x%8.8x DMA1=0x%8.8x\n",
		 proc_addr, proc1, dma_addr, dma1);

	machine_restart("AHB error"); /* Catastrophic failure */
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ar5312_misc_irq_handler(काष्ठा irq_desc *desc)
अणु
	u32 pending = ar5312_rst_reg_पढ़ो(AR5312_ISR) &
		      ar5312_rst_reg_पढ़ो(AR5312_IMR);
	अचिन्हित nr, misc_irq = 0;

	अगर (pending) अणु
		काष्ठा irq_करोमुख्य *करोमुख्य = irq_desc_get_handler_data(desc);

		nr = __ffs(pending);
		misc_irq = irq_find_mapping(करोमुख्य, nr);
	पूर्ण

	अगर (misc_irq) अणु
		generic_handle_irq(misc_irq);
		अगर (nr == AR5312_MISC_IRQ_TIMER)
			ar5312_rst_reg_पढ़ो(AR5312_TIMER);
	पूर्ण अन्यथा अणु
		spurious_पूर्णांकerrupt();
	पूर्ण
पूर्ण

/* Enable the specअगरied AR5312_MISC_IRQ पूर्णांकerrupt */
अटल व्योम ar5312_misc_irq_unmask(काष्ठा irq_data *d)
अणु
	ar5312_rst_reg_mask(AR5312_IMR, 0, BIT(d->hwirq));
पूर्ण

/* Disable the specअगरied AR5312_MISC_IRQ पूर्णांकerrupt */
अटल व्योम ar5312_misc_irq_mask(काष्ठा irq_data *d)
अणु
	ar5312_rst_reg_mask(AR5312_IMR, BIT(d->hwirq), 0);
	ar5312_rst_reg_पढ़ो(AR5312_IMR); /* flush ग_लिखो buffer */
पूर्ण

अटल काष्ठा irq_chip ar5312_misc_irq_chip = अणु
	.name		= "ar5312-misc",
	.irq_unmask	= ar5312_misc_irq_unmask,
	.irq_mask	= ar5312_misc_irq_mask,
पूर्ण;

अटल पूर्णांक ar5312_misc_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित irq,
			       irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(irq, &ar5312_misc_irq_chip, handle_level_irq);
	वापस 0;
पूर्ण

अटल काष्ठा irq_करोमुख्य_ops ar5312_misc_irq_करोमुख्य_ops = अणु
	.map = ar5312_misc_irq_map,
पूर्ण;

अटल व्योम ar5312_irq_dispatch(व्योम)
अणु
	u32 pending = पढ़ो_c0_status() & पढ़ो_c0_cause();

	अगर (pending & CAUSEF_IP2)
		करो_IRQ(AR5312_IRQ_WLAN0);
	अन्यथा अगर (pending & CAUSEF_IP5)
		करो_IRQ(AR5312_IRQ_WLAN1);
	अन्यथा अगर (pending & CAUSEF_IP6)
		करो_IRQ(AR5312_IRQ_MISC);
	अन्यथा अगर (pending & CAUSEF_IP7)
		करो_IRQ(ATH25_IRQ_CPU_CLOCK);
	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

व्योम __init ar5312_arch_init_irq(व्योम)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित irq;

	ath25_irq_dispatch = ar5312_irq_dispatch;

	करोमुख्य = irq_करोमुख्य_add_linear(शून्य, AR5312_MISC_IRQ_COUNT,
				       &ar5312_misc_irq_करोमुख्य_ops, शून्य);
	अगर (!करोमुख्य)
		panic("Failed to add IRQ domain");

	irq = irq_create_mapping(करोमुख्य, AR5312_MISC_IRQ_AHB_PROC);
	अगर (request_irq(irq, ar5312_ahb_err_handler, 0, "ar5312-ahb-error",
			शून्य))
		pr_err("Failed to register ar5312-ahb-error interrupt\n");

	irq_set_chained_handler_and_data(AR5312_IRQ_MISC,
					 ar5312_misc_irq_handler, करोमुख्य);

	ar5312_misc_irq_करोमुख्य = करोमुख्य;
पूर्ण

अटल काष्ठा physmap_flash_data ar5312_flash_data = अणु
	.width = 2,
पूर्ण;

अटल काष्ठा resource ar5312_flash_resource = अणु
	.start = AR5312_FLASH_BASE,
	.end = AR5312_FLASH_BASE + AR5312_FLASH_SIZE - 1,
	.flags = IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device ar5312_physmap_flash = अणु
	.name = "physmap-flash",
	.id = 0,
	.dev.platक्रमm_data = &ar5312_flash_data,
	.resource = &ar5312_flash_resource,
	.num_resources = 1,
पूर्ण;

अटल व्योम __init ar5312_flash_init(व्योम)
अणु
	व्योम __iomem *flashctl_base;
	u32 ctl;

	flashctl_base = ioremap(AR5312_FLASHCTL_BASE,
					AR5312_FLASHCTL_SIZE);

	ctl = __raw_पढ़ोl(flashctl_base + AR5312_FLASHCTL0);
	ctl &= AR5312_FLASHCTL_MW;

	/* fixup flash width */
	चयन (ctl) अणु
	हाल AR5312_FLASHCTL_MW16:
		ar5312_flash_data.width = 2;
		अवरोध;
	हाल AR5312_FLASHCTL_MW8:
	शेष:
		ar5312_flash_data.width = 1;
		अवरोध;
	पूर्ण

	/*
	 * Configure flash bank 0.
	 * Assume 8M winकरोw size. Flash will be aliased अगर it's smaller
	 */
	ctl |= AR5312_FLASHCTL_E | AR5312_FLASHCTL_AC_8M | AR5312_FLASHCTL_RBLE;
	ctl |= 0x01 << AR5312_FLASHCTL_IDCY_S;
	ctl |= 0x07 << AR5312_FLASHCTL_WST1_S;
	ctl |= 0x07 << AR5312_FLASHCTL_WST2_S;
	__raw_ग_लिखोl(ctl, flashctl_base + AR5312_FLASHCTL0);

	/* Disable other flash banks */
	ctl = __raw_पढ़ोl(flashctl_base + AR5312_FLASHCTL1);
	ctl &= ~(AR5312_FLASHCTL_E | AR5312_FLASHCTL_AC);
	__raw_ग_लिखोl(ctl, flashctl_base + AR5312_FLASHCTL1);
	ctl = __raw_पढ़ोl(flashctl_base + AR5312_FLASHCTL2);
	ctl &= ~(AR5312_FLASHCTL_E | AR5312_FLASHCTL_AC);
	__raw_ग_लिखोl(ctl, flashctl_base + AR5312_FLASHCTL2);

	iounmap(flashctl_base);
पूर्ण

व्योम __init ar5312_init_devices(व्योम)
अणु
	काष्ठा ath25_boarddata *config;

	ar5312_flash_init();

	/* Locate board/radio config data */
	ath25_find_config(AR5312_FLASH_BASE, AR5312_FLASH_SIZE);
	config = ath25_board.config;

	/* AR2313 has CPU minor rev. 10 */
	अगर ((current_cpu_data.processor_id & 0xff) == 0x0a)
		ath25_soc = ATH25_SOC_AR2313;

	/* AR2312 shares the same Silicon ID as AR5312 */
	अन्यथा अगर (config->flags & BD_ISCASPER)
		ath25_soc = ATH25_SOC_AR2312;

	/* Everything अन्यथा is probably AR5312 or compatible */
	अन्यथा
		ath25_soc = ATH25_SOC_AR5312;

	platक्रमm_device_रेजिस्टर(&ar5312_physmap_flash);

	चयन (ath25_soc) अणु
	हाल ATH25_SOC_AR5312:
		अगर (!ath25_board.radio)
			वापस;

		अगर (!(config->flags & BD_WLAN0))
			अवरोध;

		ath25_add_wmac(0, AR5312_WLAN0_BASE, AR5312_IRQ_WLAN0);
		अवरोध;
	हाल ATH25_SOC_AR2312:
	हाल ATH25_SOC_AR2313:
		अगर (!ath25_board.radio)
			वापस;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (config->flags & BD_WLAN1)
		ath25_add_wmac(1, AR5312_WLAN1_BASE, AR5312_IRQ_WLAN1);
पूर्ण

अटल व्योम ar5312_restart(अक्षर *command)
अणु
	/* reset the प्रणाली */
	local_irq_disable();
	जबतक (1)
		ar5312_rst_reg_ग_लिखो(AR5312_RESET, AR5312_RESET_SYSTEM);
पूर्ण

/*
 * This table is indexed by bits 5..4 of the CLOCKCTL1 रेजिस्टर
 * to determine the predevisor value.
 */
अटल अचिन्हित घड़ीctl1_preभागide_table[4] __initdata = अणु 1, 2, 4, 5 पूर्ण;

अटल अचिन्हित __init ar5312_cpu_frequency(व्योम)
अणु
	u32 scratch, devid, घड़ी_ctl1;
	u32 preभागide_mask, multiplier_mask, द्विगुनr_mask;
	अचिन्हित preभागide_shअगरt, multiplier_shअगरt;
	अचिन्हित preभागide_select, preभागisor, multiplier;

	/* Trust the bootrom's idea of cpu frequency. */
	scratch = ar5312_rst_reg_पढ़ो(AR5312_SCRATCH);
	अगर (scratch)
		वापस scratch;

	devid = ar5312_rst_reg_पढ़ो(AR5312_REV);
	devid = (devid & AR5312_REV_MAJ) >> AR5312_REV_MAJ_S;
	अगर (devid == AR5312_REV_MAJ_AR2313) अणु
		preभागide_mask = AR2313_CLOCKCTL1_PREDIVIDE_MASK;
		preभागide_shअगरt = AR2313_CLOCKCTL1_PREDIVIDE_SHIFT;
		multiplier_mask = AR2313_CLOCKCTL1_MULTIPLIER_MASK;
		multiplier_shअगरt = AR2313_CLOCKCTL1_MULTIPLIER_SHIFT;
		द्विगुनr_mask = AR2313_CLOCKCTL1_DOUBLER_MASK;
	पूर्ण अन्यथा अणु /* AR5312 and AR2312 */
		preभागide_mask = AR5312_CLOCKCTL1_PREDIVIDE_MASK;
		preभागide_shअगरt = AR5312_CLOCKCTL1_PREDIVIDE_SHIFT;
		multiplier_mask = AR5312_CLOCKCTL1_MULTIPLIER_MASK;
		multiplier_shअगरt = AR5312_CLOCKCTL1_MULTIPLIER_SHIFT;
		द्विगुनr_mask = AR5312_CLOCKCTL1_DOUBLER_MASK;
	पूर्ण

	/*
	 * Clocking is derived from a fixed 40MHz input घड़ी.
	 *
	 *  cpu_freq = input_घड़ी * MULT (where MULT is PLL multiplier)
	 *  sys_freq = cpu_freq / 4	  (used क्रम APB घड़ी, serial,
	 *				   flash, Timer, Watchकरोg Timer)
	 *
	 *  cnt_freq = cpu_freq / 2	  (use क्रम CPU count/compare)
	 *
	 * So, क्रम example, with a PLL multiplier of 5, we have
	 *
	 *  cpu_freq = 200MHz
	 *  sys_freq = 50MHz
	 *  cnt_freq = 100MHz
	 *
	 * We compute the CPU frequency, based on PLL settings.
	 */

	घड़ी_ctl1 = ar5312_rst_reg_पढ़ो(AR5312_CLOCKCTL1);
	preभागide_select = (घड़ी_ctl1 & preभागide_mask) >> preभागide_shअगरt;
	preभागisor = घड़ीctl1_preभागide_table[preभागide_select];
	multiplier = (घड़ी_ctl1 & multiplier_mask) >> multiplier_shअगरt;

	अगर (घड़ी_ctl1 & द्विगुनr_mask)
		multiplier <<= 1;

	वापस (40000000 / preभागisor) * multiplier;
पूर्ण

अटल अंतरभूत अचिन्हित ar5312_sys_frequency(व्योम)
अणु
	वापस ar5312_cpu_frequency() / 4;
पूर्ण

व्योम __init ar5312_plat_समय_init(व्योम)
अणु
	mips_hpt_frequency = ar5312_cpu_frequency() / 2;
पूर्ण

व्योम __init ar5312_plat_mem_setup(व्योम)
अणु
	व्योम __iomem *sdram_base;
	u32 memsize, memcfg, bank0_ac, bank1_ac;
	u32 devid;

	/* Detect memory size */
	sdram_base = ioremap(AR5312_SDRAMCTL_BASE,
				     AR5312_SDRAMCTL_SIZE);
	memcfg = __raw_पढ़ोl(sdram_base + AR5312_MEM_CFG1);
	bank0_ac = ATH25_REG_MS(memcfg, AR5312_MEM_CFG1_AC0);
	bank1_ac = ATH25_REG_MS(memcfg, AR5312_MEM_CFG1_AC1);
	memsize = (bank0_ac ? (1 << (bank0_ac + 1)) : 0) +
		  (bank1_ac ? (1 << (bank1_ac + 1)) : 0);
	memsize <<= 20;
	memblock_add(0, memsize);
	iounmap(sdram_base);

	ar5312_rst_base = ioremap(AR5312_RST_BASE, AR5312_RST_SIZE);

	devid = ar5312_rst_reg_पढ़ो(AR5312_REV);
	devid >>= AR5312_REV_WMAC_MIN_S;
	devid &= AR5312_REV_CHIP;
	ath25_board.devid = (u16)devid;

	/* Clear any lingering AHB errors */
	ar5312_rst_reg_पढ़ो(AR5312_PROCADDR);
	ar5312_rst_reg_पढ़ो(AR5312_DMAADDR);
	ar5312_rst_reg_ग_लिखो(AR5312_WDT_CTRL, AR5312_WDT_CTRL_IGNORE);

	_machine_restart = ar5312_restart;
पूर्ण

व्योम __init ar5312_arch_init(व्योम)
अणु
	अचिन्हित irq = irq_create_mapping(ar5312_misc_irq_करोमुख्य,
					  AR5312_MISC_IRQ_UART0);

	ath25_serial_setup(AR5312_UART0_BASE, irq, ar5312_sys_frequency());
पूर्ण
