<शैली गुरु>
/*
 * Setup poपूर्णांकers to hardware-dependent routines.
 * Copyright (C) 2000-2001 Toshiba Corporation
 *
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Support क्रम TX4938 in 2.6 - Manish Lachwani (mlachwani@mvista.com)
 */
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/mtd/physmap.h>

#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/pci.h>
#समावेश <यंत्र/txx9/rbtx4938.h>
#समावेश <linux/spi/spi.h>
#समावेश <यंत्र/txx9/spi.h>
#समावेश <यंत्र/txx9pपन.स>

अटल व्योम rbtx4938_machine_restart(अक्षर *command)
अणु
	local_irq_disable();
	ग_लिखोb(1, rbtx4938_softresetlock_addr);
	ग_लिखोb(1, rbtx4938_sfvol_addr);
	ग_लिखोb(1, rbtx4938_softreset_addr);
	/* fallback */
	(*_machine_halt)();
पूर्ण

अटल व्योम __init rbtx4938_pci_setup(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	पूर्णांक extarb = !(__raw_पढ़ोq(&tx4938_ccfgptr->ccfg) & TX4938_CCFG_PCIARB);
	काष्ठा pci_controller *c = &txx9_primary_pcic;

	रेजिस्टर_pci_controller(c);

	अगर (__raw_पढ़ोq(&tx4938_ccfgptr->ccfg) & TX4938_CCFG_PCI66)
		txx9_pci_option =
			(txx9_pci_option & ~TXX9_PCI_OPT_CLK_MASK) |
			TXX9_PCI_OPT_CLK_66; /* alपढ़ोy configured */

	/* Reset PCI Bus */
	ग_लिखोb(0, rbtx4938_pcireset_addr);
	/* Reset PCIC */
	txx9_set64(&tx4938_ccfgptr->clkctr, TX4938_CLKCTR_PCIRST);
	अगर ((txx9_pci_option & TXX9_PCI_OPT_CLK_MASK) ==
	    TXX9_PCI_OPT_CLK_66)
		tx4938_pciclk66_setup();
	mdelay(10);
	/* clear PCIC reset */
	txx9_clear64(&tx4938_ccfgptr->clkctr, TX4938_CLKCTR_PCIRST);
	ग_लिखोb(1, rbtx4938_pcireset_addr);
	iob();

	tx4938_report_pciclk();
	tx4927_pcic_setup(tx4938_pcicptr, c, extarb);
	अगर ((txx9_pci_option & TXX9_PCI_OPT_CLK_MASK) ==
	    TXX9_PCI_OPT_CLK_AUTO &&
	    txx9_pci66_check(c, 0, 0)) अणु
		/* Reset PCI Bus */
		ग_लिखोb(0, rbtx4938_pcireset_addr);
		/* Reset PCIC */
		txx9_set64(&tx4938_ccfgptr->clkctr, TX4938_CLKCTR_PCIRST);
		tx4938_pciclk66_setup();
		mdelay(10);
		/* clear PCIC reset */
		txx9_clear64(&tx4938_ccfgptr->clkctr, TX4938_CLKCTR_PCIRST);
		ग_लिखोb(1, rbtx4938_pcireset_addr);
		iob();
		/* Reinitialize PCIC */
		tx4938_report_pciclk();
		tx4927_pcic_setup(tx4938_pcicptr, c, extarb);
	पूर्ण

	अगर (__raw_पढ़ोq(&tx4938_ccfgptr->pcfg) &
	    (TX4938_PCFG_ETH0_SEL|TX4938_PCFG_ETH1_SEL)) अणु
		/* Reset PCIC1 */
		txx9_set64(&tx4938_ccfgptr->clkctr, TX4938_CLKCTR_PCIC1RST);
		/* PCI1DMD==0 => PCI1CLK==GBUSCLK/2 => PCI66 */
		अगर (!(__raw_पढ़ोq(&tx4938_ccfgptr->ccfg)
		      & TX4938_CCFG_PCI1DMD))
			tx4938_ccfg_set(TX4938_CCFG_PCI1_66);
		mdelay(10);
		/* clear PCIC1 reset */
		txx9_clear64(&tx4938_ccfgptr->clkctr, TX4938_CLKCTR_PCIC1RST);
		tx4938_report_pci1clk();

		/* mem:64K(max), io:64K(max) (enough क्रम ETH0,ETH1) */
		c = txx9_alloc_pci_controller(शून्य, 0, 0x10000, 0, 0x10000);
		रेजिस्टर_pci_controller(c);
		tx4927_pcic_setup(tx4938_pcic1ptr, c, 0);
	पूर्ण
	tx4938_setup_pcierr_irq();
#पूर्ण_अगर /* CONFIG_PCI */
पूर्ण

/* SPI support */

/* chip select क्रम SPI devices */
#घोषणा SEEPROM1_CS	7	/* PIO7 */
#घोषणा SEEPROM2_CS	0	/* IOC */
#घोषणा SEEPROM3_CS	1	/* IOC */
#घोषणा SRTC_CS 2	/* IOC */
#घोषणा SPI_BUSNO	0

अटल पूर्णांक __init rbtx4938_ethaddr_init(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	अचिन्हित अक्षर dat[17];
	अचिन्हित अक्षर sum;
	पूर्णांक i;

	/* 0-3: "MAC\0", 4-9:eth0, 10-15:eth1, 16:sum */
	अगर (spi_eeprom_पढ़ो(SPI_BUSNO, SEEPROM1_CS, 0, dat, माप(dat))) अणु
		pr_err("seeprom: read error.\n");
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		अगर (म_भेद(dat, "MAC") != 0)
			pr_warn("seeprom: bad signature.\n");
		क्रम (i = 0, sum = 0; i < माप(dat); i++)
			sum += dat[i];
		अगर (sum)
			pr_warn("seeprom: bad checksum.\n");
	पूर्ण
	tx4938_ethaddr_init(&dat[4], &dat[4 + 6]);
#पूर्ण_अगर /* CONFIG_PCI */
	वापस 0;
पूर्ण

अटल व्योम __init rbtx4938_spi_setup(व्योम)
अणु
	/* set SPI_SEL */
	txx9_set64(&tx4938_ccfgptr->pcfg, TX4938_PCFG_SPI_SEL);
पूर्ण

अटल काष्ठा resource rbtx4938_fpga_resource;

अटल व्योम __init rbtx4938_समय_init(व्योम)
अणु
	tx4938_समय_init(0);
पूर्ण

अटल व्योम __init rbtx4938_mem_setup(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ pcfg;

	अगर (txx9_master_घड़ी == 0)
		txx9_master_घड़ी = 25000000; /* 25MHz */

	tx4938_setup();

#अगर_घोषित CONFIG_PCI
	txx9_alloc_pci_controller(&txx9_primary_pcic, 0, 0, 0, 0);
	txx9_board_pcibios_setup = tx4927_pcibios_setup;
#अन्यथा
	set_io_port_base(RBTX4938_ETHER_BASE);
#पूर्ण_अगर

	tx4938_sio_init(7372800, 0);

#अगर_घोषित CONFIG_TOSHIBA_RBTX4938_MPLEX_PIO58_61
	pr_info("PIOSEL: disabling both ATA and NAND selection\n");
	txx9_clear64(&tx4938_ccfgptr->pcfg,
		     TX4938_PCFG_NDF_SEL | TX4938_PCFG_ATA_SEL);
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOSHIBA_RBTX4938_MPLEX_न_अंकD
	pr_info("PIOSEL: enabling NAND selection\n");
	txx9_set64(&tx4938_ccfgptr->pcfg, TX4938_PCFG_NDF_SEL);
	txx9_clear64(&tx4938_ccfgptr->pcfg, TX4938_PCFG_ATA_SEL);
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOSHIBA_RBTX4938_MPLEX_ATA
	pr_info("PIOSEL: enabling ATA selection\n");
	txx9_set64(&tx4938_ccfgptr->pcfg, TX4938_PCFG_ATA_SEL);
	txx9_clear64(&tx4938_ccfgptr->pcfg, TX4938_PCFG_NDF_SEL);
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOSHIBA_RBTX4938_MPLEX_KEEP
	pcfg = ____raw_पढ़ोq(&tx4938_ccfgptr->pcfg);
	pr_info("PIOSEL: NAND %s, ATA %s\n",
		(pcfg & TX4938_PCFG_NDF_SEL) ? "enabled" : "disabled",
		(pcfg & TX4938_PCFG_ATA_SEL) ? "enabled" : "disabled");
#पूर्ण_अगर

	rbtx4938_spi_setup();
	pcfg = ____raw_पढ़ोq(&tx4938_ccfgptr->pcfg);	/* updated */
	/* fixup piosel */
	अगर ((pcfg & (TX4938_PCFG_ATA_SEL | TX4938_PCFG_NDF_SEL)) ==
	    TX4938_PCFG_ATA_SEL)
		ग_लिखोb((पढ़ोb(rbtx4938_piosel_addr) & 0x03) | 0x04,
		       rbtx4938_piosel_addr);
	अन्यथा अगर ((pcfg & (TX4938_PCFG_ATA_SEL | TX4938_PCFG_NDF_SEL)) ==
		 TX4938_PCFG_NDF_SEL)
		ग_लिखोb((पढ़ोb(rbtx4938_piosel_addr) & 0x03) | 0x08,
		       rbtx4938_piosel_addr);
	अन्यथा
		ग_लिखोb(पढ़ोb(rbtx4938_piosel_addr) & ~(0x08 | 0x04),
		       rbtx4938_piosel_addr);

	rbtx4938_fpga_resource.name = "FPGA Registers";
	rbtx4938_fpga_resource.start = CPHYSADDR(RBTX4938_FPGA_REG_ADDR);
	rbtx4938_fpga_resource.end = CPHYSADDR(RBTX4938_FPGA_REG_ADDR) + 0xffff;
	rbtx4938_fpga_resource.flags = IORESOURCE_MEM | IORESOURCE_BUSY;
	अगर (request_resource(&txx9_ce_res[2], &rbtx4938_fpga_resource))
		pr_err("request resource for fpga failed\n");

	_machine_restart = rbtx4938_machine_restart;

	ग_लिखोb(0xff, rbtx4938_led_addr);
	pr_info("RBTX4938 --- FPGA(Rev %02x) DIPSW:%02x,%02x\n",
		पढ़ोb(rbtx4938_fpga_rev_addr),
		पढ़ोb(rbtx4938_dipsw_addr), पढ़ोb(rbtx4938_bdipsw_addr));
पूर्ण

अटल व्योम __init rbtx4938_ne_init(व्योम)
अणु
	काष्ठा resource res[] = अणु
		अणु
			.start	= RBTX4938_RTL_8019_BASE,
			.end	= RBTX4938_RTL_8019_BASE + 0x20 - 1,
			.flags	= IORESOURCE_IO,
		पूर्ण, अणु
			.start	= RBTX4938_RTL_8019_IRQ,
			.flags	= IORESOURCE_IRQ,
		पूर्ण
	पूर्ण;
	platक्रमm_device_रेजिस्टर_simple("ne", -1, res, ARRAY_SIZE(res));
पूर्ण

अटल DEFINE_SPINLOCK(rbtx4938_spi_gpio_lock);

अटल व्योम rbtx4938_spi_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				  पूर्णांक value)
अणु
	u8 val;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&rbtx4938_spi_gpio_lock, flags);
	val = पढ़ोb(rbtx4938_spics_addr);
	अगर (value)
		val |= 1 << offset;
	अन्यथा
		val &= ~(1 << offset);
	ग_लिखोb(val, rbtx4938_spics_addr);
	mmiowb();
	spin_unlock_irqrestore(&rbtx4938_spi_gpio_lock, flags);
पूर्ण

अटल पूर्णांक rbtx4938_spi_gpio_dir_out(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	rbtx4938_spi_gpio_set(chip, offset, value);
	वापस 0;
पूर्ण

अटल काष्ठा gpio_chip rbtx4938_spi_gpio_chip = अणु
	.set = rbtx4938_spi_gpio_set,
	.direction_output = rbtx4938_spi_gpio_dir_out,
	.label = "RBTX4938-SPICS",
	.base = 16,
	.ngpio = 3,
पूर्ण;

अटल पूर्णांक __init rbtx4938_spi_init(व्योम)
अणु
	काष्ठा spi_board_info srtc_info = अणु
		.modalias = "rtc-rs5c348",
		.max_speed_hz = 1000000, /* 1.0Mbps @ Vdd 2.0V */
		.bus_num = 0,
		.chip_select = 16 + SRTC_CS,
		/* Mode 1 (High-Active, Shअगरt-Then-Sample), High Avtive CS  */
		.mode = SPI_MODE_1 | SPI_CS_HIGH,
	पूर्ण;
	spi_रेजिस्टर_board_info(&srtc_info, 1);
	spi_eeprom_रेजिस्टर(SPI_BUSNO, SEEPROM1_CS, 128);
	spi_eeprom_रेजिस्टर(SPI_BUSNO, 16 + SEEPROM2_CS, 128);
	spi_eeprom_रेजिस्टर(SPI_BUSNO, 16 + SEEPROM3_CS, 128);
	gpio_request(16 + SRTC_CS, "rtc-rs5c348");
	gpio_direction_output(16 + SRTC_CS, 0);
	gpio_request(SEEPROM1_CS, "seeprom1");
	gpio_direction_output(SEEPROM1_CS, 1);
	gpio_request(16 + SEEPROM2_CS, "seeprom2");
	gpio_direction_output(16 + SEEPROM2_CS, 1);
	gpio_request(16 + SEEPROM3_CS, "seeprom3");
	gpio_direction_output(16 + SEEPROM3_CS, 1);
	tx4938_spi_init(SPI_BUSNO);
	वापस 0;
पूर्ण

अटल व्योम __init rbtx4938_mtd_init(व्योम)
अणु
	काष्ठा physmap_flash_data pdata = अणु
		.width = 4,
	पूर्ण;

	चयन (पढ़ोb(rbtx4938_bdipsw_addr) & 7) अणु
	हाल 0:
		/* Boot */
		txx9_physmap_flash_init(0, 0x1fc00000, 0x400000, &pdata);
		/* System */
		txx9_physmap_flash_init(1, 0x1e000000, 0x1000000, &pdata);
		अवरोध;
	हाल 1:
		/* System */
		txx9_physmap_flash_init(0, 0x1f000000, 0x1000000, &pdata);
		/* Boot */
		txx9_physmap_flash_init(1, 0x1ec00000, 0x400000, &pdata);
		अवरोध;
	हाल 2:
		/* Ext */
		txx9_physmap_flash_init(0, 0x1f000000, 0x1000000, &pdata);
		/* System */
		txx9_physmap_flash_init(1, 0x1e000000, 0x1000000, &pdata);
		/* Boot */
		txx9_physmap_flash_init(2, 0x1dc00000, 0x400000, &pdata);
		अवरोध;
	हाल 3:
		/* Boot */
		txx9_physmap_flash_init(1, 0x1bc00000, 0x400000, &pdata);
		/* System */
		txx9_physmap_flash_init(2, 0x1a000000, 0x1000000, &pdata);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __init rbtx4938_arch_init(व्योम)
अणु
	txx9_gpio_init(TX4938_PIO_REG & 0xfffffffffULL, 0, TX4938_NUM_PIO);
	gpiochip_add_data(&rbtx4938_spi_gpio_chip, शून्य);
	rbtx4938_pci_setup();
	rbtx4938_spi_init();
पूर्ण

अटल व्योम __init rbtx4938_device_init(व्योम)
अणु
	rbtx4938_ethaddr_init();
	rbtx4938_ne_init();
	tx4938_wdt_init();
	rbtx4938_mtd_init();
	/* TC58DVM82A1FT: tDH=10ns, tWP=tRP=tREADID=35ns */
	tx4938_ndfmc_init(10, 35);
	tx4938_ata_init(RBTX4938_IRQ_IOC_ATA, 0, 1);
	tx4938_dmac_init(0, 2);
	tx4938_aclc_init();
	platक्रमm_device_रेजिस्टर_simple("txx9aclc-generic", -1, शून्य, 0);
	tx4938_sramc_init();
	txx9_iocled_init(RBTX4938_LED_ADDR - IO_BASE, -1, 8, 1, "green", शून्य);
पूर्ण

काष्ठा txx9_board_vec rbtx4938_vec __initdata = अणु
	.प्रणाली = "Toshiba RBTX4938",
	.prom_init = rbtx4938_prom_init,
	.mem_setup = rbtx4938_mem_setup,
	.irq_setup = rbtx4938_irq_setup,
	.समय_init = rbtx4938_समय_init,
	.device_init = rbtx4938_device_init,
	.arch_init = rbtx4938_arch_init,
#अगर_घोषित CONFIG_PCI
	.pci_map_irq = rbtx4938_pci_map_irq,
#पूर्ण_अगर
पूर्ण;
