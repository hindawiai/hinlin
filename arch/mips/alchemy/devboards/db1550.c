<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Alchemy Db1550/Pb1550 board support
 *
 * (c) 2011 Manuel Lauss <manuel.lauss@googlemail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/platnand.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/gpio-au1000.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_eth.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_dbdma.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_psc.h>
#समावेश <यंत्र/mach-au1x00/au1550_spi.h>
#समावेश <यंत्र/mach-au1x00/au1550nd.h>
#समावेश <यंत्र/mach-db1x00/bcsr.h>
#समावेश <prom.h>
#समावेश "platform.h"

अटल व्योम __init db1550_hw_setup(व्योम)
अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ v;

	/* complete pin setup: assign GPIO16 to PSC0_SYNC1 (SPI cs# line)
	 * as well as PSC1_SYNC क्रम AC97 on PB1550.
	 */
	v = alchemy_rdsys(AU1000_SYS_PINFUNC);
	alchemy_wrsys(v | 1 | SYS_PF_PSC1_S1, AU1000_SYS_PINFUNC);

	/* reset the AC97 codec now, the reset समय in the psc-ac97 driver
	 * is apparently too लघु although it's ridiculous as it is.
	 */
	base = (व्योम __iomem *)KSEG1ADDR(AU1550_PSC1_PHYS_ADDR);
	__raw_ग_लिखोl(PSC_SEL_CLK_SERCLK | PSC_SEL_PS_AC97MODE,
		     base + PSC_SEL_OFFSET);
	__raw_ग_लिखोl(PSC_CTRL_DISABLE, base + PSC_CTRL_OFFSET);
	wmb();
	__raw_ग_लिखोl(PSC_AC97RST_RST, base + PSC_AC97RST_OFFSET);
	wmb();
पूर्ण

पूर्णांक __init db1550_board_setup(व्योम)
अणु
	अचिन्हित लघु whoami;

	bcsr_init(DB1550_BCSR_PHYS_ADDR,
		  DB1550_BCSR_PHYS_ADDR + DB1550_BCSR_HEXLED_OFS);

	whoami = bcsr_पढ़ो(BCSR_WHOAMI); /* PB1550 hexled offset dअगरfers */
	चयन (BCSR_WHOAMI_BOARD(whoami)) अणु
	हाल BCSR_WHOAMI_PB1550_SDR:
	हाल BCSR_WHOAMI_PB1550_DDR:
		bcsr_init(PB1550_BCSR_PHYS_ADDR,
			  PB1550_BCSR_PHYS_ADDR + PB1550_BCSR_HEXLED_OFS);
	हाल BCSR_WHOAMI_DB1550:
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	pr_info("Alchemy/AMD %s Board, CPLD Rev %d Board-ID %d	"	\
		"Daughtercard ID %d\n", get_प्रणाली_type(),
		(whoami >> 4) & 0xf, (whoami >> 8) & 0xf, whoami & 0xf);

	db1550_hw_setup();
	वापस 0;
पूर्ण

/*****************************************************************************/

अटल u64 au1550_all_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा mtd_partition db1550_spअगरlash_parts[] = अणु
	अणु
		.name	= "spi_flash",
		.offset = 0,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data db1550_spअगरlash_data = अणु
	.name		= "s25fl010",
	.parts		= db1550_spअगरlash_parts,
	.nr_parts	= ARRAY_SIZE(db1550_spअगरlash_parts),
	.type		= "m25p10",
पूर्ण;

अटल काष्ठा spi_board_info db1550_spi_devs[] __initdata = अणु
	अणु
		/* TI TMP121AIDBVR temp sensor */
		.modalias	= "tmp121",
		.max_speed_hz	= 2400000,
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_0,
	पूर्ण,
	अणु
		/* Spansion S25FL001D0FMA SPI flash */
		.modalias	= "m25p80",
		.max_speed_hz	= 2400000,
		.bus_num	= 0,
		.chip_select	= 1,
		.mode		= SPI_MODE_0,
		.platक्रमm_data	= &db1550_spअगरlash_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info db1550_i2c_devs[] __initdata = अणु
	अणु I2C_BOARD_INFO("24c04",  0x52),पूर्ण, /* AT24C04-10 I2C eeprom */
	अणु I2C_BOARD_INFO("ne1619", 0x2d),पूर्ण, /* adm1025-compat hwmon */
	अणु I2C_BOARD_INFO("wm8731", 0x1b),पूर्ण, /* I2S audio codec WM8731 */
पूर्ण;

/**********************************************************************/

अटल व्योम au1550_nand_cmd_ctrl(काष्ठा nand_chip *this, पूर्णांक cmd,
				 अचिन्हित पूर्णांक ctrl)
अणु
	अचिन्हित दीर्घ ioaddr = (अचिन्हित दीर्घ)this->legacy.IO_ADDR_W;

	ioaddr &= 0xffffff00;

	अगर (ctrl & न_अंकD_CLE) अणु
		ioaddr += MEM_STन_अंकD_CMD;
	पूर्ण अन्यथा अगर (ctrl & न_अंकD_ALE) अणु
		ioaddr += MEM_STन_अंकD_ADDR;
	पूर्ण अन्यथा अणु
		/* assume we want to r/w real data  by शेष */
		ioaddr += MEM_STन_अंकD_DATA;
	पूर्ण
	this->legacy.IO_ADDR_R = this->legacy.IO_ADDR_W = (व्योम __iomem *)ioaddr;
	अगर (cmd != न_अंकD_CMD_NONE) अणु
		__raw_ग_लिखोb(cmd, this->legacy.IO_ADDR_W);
		wmb();
	पूर्ण
पूर्ण

अटल पूर्णांक au1550_nand_device_पढ़ोy(काष्ठा nand_chip *this)
अणु
	वापस alchemy_rdsmem(AU1000_MEM_STSTAT) & 1;
पूर्ण

अटल काष्ठा mtd_partition db1550_nand_parts[] = अणु
	अणु
		.name	= "NAND FS 0",
		.offset = 0,
		.size	= 8 * 1024 * 1024,
	पूर्ण,
	अणु
		.name	= "NAND FS 1",
		.offset = MTDPART_OFS_APPEND,
		.size	= MTDPART_SIZ_FULL
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_nand_data db1550_nand_platdata = अणु
	.chip = अणु
		.nr_chips	= 1,
		.chip_offset	= 0,
		.nr_partitions	= ARRAY_SIZE(db1550_nand_parts),
		.partitions	= db1550_nand_parts,
		.chip_delay	= 20,
	पूर्ण,
	.ctrl = अणु
		.dev_पढ़ोy	= au1550_nand_device_पढ़ोy,
		.cmd_ctrl	= au1550_nand_cmd_ctrl,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource db1550_nand_res[] = अणु
	[0] = अणु
		.start	= 0x20000000,
		.end	= 0x200000ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1550_nand_dev = अणु
	.name		= "gen_nand",
	.num_resources	= ARRAY_SIZE(db1550_nand_res),
	.resource	= db1550_nand_res,
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &db1550_nand_platdata,
	पूर्ण
पूर्ण;

अटल काष्ठा au1550nd_platdata pb1550_nand_pd = अणु
	.parts		= db1550_nand_parts,
	.num_parts	= ARRAY_SIZE(db1550_nand_parts),
	.devwidth	= 0,	/* x8 न_अंकD शेष, needs fixing up */
पूर्ण;

अटल काष्ठा platक्रमm_device pb1550_nand_dev = अणु
	.name		= "au1550-nand",
	.id		= -1,
	.resource	= db1550_nand_res,
	.num_resources	= ARRAY_SIZE(db1550_nand_res),
	.dev		= अणु
		.platक्रमm_data	= &pb1550_nand_pd,
	पूर्ण,
पूर्ण;

अटल व्योम __init pb1550_nand_setup(व्योम)
अणु
	पूर्णांक boot_swapboot = (alchemy_rdsmem(AU1000_MEM_STSTAT) & (0x7 << 1)) |
			    ((bcsr_पढ़ो(BCSR_STATUS) >> 6) & 0x1);

	gpio_direction_input(206);	/* de-निश्चित न_अंकD CS# */
	चयन (boot_swapboot) अणु
	हाल 0: हाल 2: हाल 8: हाल 0xC: हाल 0xD:
		/* x16 न_अंकD Flash */
		pb1550_nand_pd.devwidth = 1;
		fallthrough;
	हाल 1: हाल 3: हाल 9: हाल 0xE: हाल 0xF:
		/* x8 न_अंकD, alपढ़ोy set up */
		platक्रमm_device_रेजिस्टर(&pb1550_nand_dev);
	पूर्ण
पूर्ण

/**********************************************************************/

अटल काष्ठा resource au1550_psc0_res[] = अणु
	[0] = अणु
		.start	= AU1550_PSC0_PHYS_ADDR,
		.end	= AU1550_PSC0_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1550_PSC0_INT,
		.end	= AU1550_PSC0_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1550_DSCR_CMD0_PSC0_TX,
		.end	= AU1550_DSCR_CMD0_PSC0_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1550_DSCR_CMD0_PSC0_RX,
		.end	= AU1550_DSCR_CMD0_PSC0_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल व्योम db1550_spi_cs_en(काष्ठा au1550_spi_info *spi, पूर्णांक cs, पूर्णांक pol)
अणु
	अगर (cs)
		bcsr_mod(BCSR_BOARD, 0, BCSR_BOARD_SPISEL);
	अन्यथा
		bcsr_mod(BCSR_BOARD, BCSR_BOARD_SPISEL, 0);
पूर्ण

अटल काष्ठा au1550_spi_info db1550_spi_platdata = अणु
	.मुख्यclk_hz	= 48000000,	/* PSC0 घड़ी: max. 2.4MHz SPI clk */
	.num_chipselect = 2,
	.activate_cs	= db1550_spi_cs_en,
पूर्ण;


अटल काष्ठा platक्रमm_device db1550_spi_dev = अणु
	.dev	= अणु
		.dma_mask		= &au1550_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &db1550_spi_platdata,
	पूर्ण,
	.name		= "au1550-spi",
	.id		= 0,	/* bus number */
	.num_resources	= ARRAY_SIZE(au1550_psc0_res),
	.resource	= au1550_psc0_res,
पूर्ण;

/**********************************************************************/

अटल काष्ठा resource au1550_psc1_res[] = अणु
	[0] = अणु
		.start	= AU1550_PSC1_PHYS_ADDR,
		.end	= AU1550_PSC1_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1550_PSC1_INT,
		.end	= AU1550_PSC1_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1550_DSCR_CMD0_PSC1_TX,
		.end	= AU1550_DSCR_CMD0_PSC1_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1550_DSCR_CMD0_PSC1_RX,
		.end	= AU1550_DSCR_CMD0_PSC1_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1550_ac97_dev = अणु
	.name		= "au1xpsc_ac97",
	.id		= 1,	/* PSC ID */
	.num_resources	= ARRAY_SIZE(au1550_psc1_res),
	.resource	= au1550_psc1_res,
पूर्ण;


अटल काष्ठा resource au1550_psc2_res[] = अणु
	[0] = अणु
		.start	= AU1550_PSC2_PHYS_ADDR,
		.end	= AU1550_PSC2_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1550_PSC2_INT,
		.end	= AU1550_PSC2_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1550_DSCR_CMD0_PSC2_TX,
		.end	= AU1550_DSCR_CMD0_PSC2_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1550_DSCR_CMD0_PSC2_RX,
		.end	= AU1550_DSCR_CMD0_PSC2_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1550_i2c_dev = अणु
	.name		= "au1xpsc_smbus",
	.id		= 0,	/* bus number */
	.num_resources	= ARRAY_SIZE(au1550_psc2_res),
	.resource	= au1550_psc2_res,
पूर्ण;

/**********************************************************************/

अटल काष्ठा resource au1550_psc3_res[] = अणु
	[0] = अणु
		.start	= AU1550_PSC3_PHYS_ADDR,
		.end	= AU1550_PSC3_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1550_PSC3_INT,
		.end	= AU1550_PSC3_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= AU1550_DSCR_CMD0_PSC3_TX,
		.end	= AU1550_DSCR_CMD0_PSC3_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= AU1550_DSCR_CMD0_PSC3_RX,
		.end	= AU1550_DSCR_CMD0_PSC3_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1550_i2s_dev = अणु
	.name		= "au1xpsc_i2s",
	.id		= 3,	/* PSC ID */
	.num_resources	= ARRAY_SIZE(au1550_psc3_res),
	.resource	= au1550_psc3_res,
पूर्ण;

/**********************************************************************/

अटल काष्ठा platक्रमm_device db1550_stac_dev = अणु
	.name		= "ac97-codec",
	.id		= 1,	/* on PSC1 */
पूर्ण;

अटल काष्ठा platक्रमm_device db1550_ac97dma_dev = अणु
	.name		= "au1xpsc-pcm",
	.id		= 1,	/* on PSC3 */
पूर्ण;

अटल काष्ठा platक्रमm_device db1550_i2sdma_dev = अणु
	.name		= "au1xpsc-pcm",
	.id		= 3,	/* on PSC3 */
पूर्ण;

अटल काष्ठा platक्रमm_device db1550_sndac97_dev = अणु
	.name		= "db1550-ac97",
	.dev = अणु
		.dma_mask		= &au1550_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1550_sndi2s_dev = अणु
	.name		= "db1550-i2s",
	.dev = अणु
		.dma_mask		= &au1550_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

/**********************************************************************/

अटल पूर्णांक db1550_map_pci_irq(स्थिर काष्ठा pci_dev *d, u8 slot, u8 pin)
अणु
	अगर ((slot < 11) || (slot > 13) || pin == 0)
		वापस -1;
	अगर (slot == 11)
		वापस (pin == 1) ? AU1550_PCI_INTC : 0xff;
	अगर (slot == 12) अणु
		चयन (pin) अणु
		हाल 1: वापस AU1550_PCI_INTB;
		हाल 2: वापस AU1550_PCI_INTC;
		हाल 3: वापस AU1550_PCI_INTD;
		हाल 4: वापस AU1550_PCI_INTA;
		पूर्ण
	पूर्ण
	अगर (slot == 13) अणु
		चयन (pin) अणु
		हाल 1: वापस AU1550_PCI_INTA;
		हाल 2: वापस AU1550_PCI_INTB;
		हाल 3: वापस AU1550_PCI_INTC;
		हाल 4: वापस AU1550_PCI_INTD;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक pb1550_map_pci_irq(स्थिर काष्ठा pci_dev *d, u8 slot, u8 pin)
अणु
	अगर ((slot < 12) || (slot > 13) || pin == 0)
		वापस -1;
	अगर (slot == 12) अणु
		चयन (pin) अणु
		हाल 1: वापस AU1500_PCI_INTB;
		हाल 2: वापस AU1500_PCI_INTC;
		हाल 3: वापस AU1500_PCI_INTD;
		हाल 4: वापस AU1500_PCI_INTA;
		पूर्ण
	पूर्ण
	अगर (slot == 13) अणु
		चयन (pin) अणु
		हाल 1: वापस AU1500_PCI_INTA;
		हाल 2: वापस AU1500_PCI_INTB;
		हाल 3: वापस AU1500_PCI_INTC;
		हाल 4: वापस AU1500_PCI_INTD;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल काष्ठा resource alchemy_pci_host_res[] = अणु
	[0] = अणु
		.start	= AU1500_PCI_PHYS_ADDR,
		.end	= AU1500_PCI_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा alchemy_pci_platdata db1550_pci_pd = अणु
	.board_map_irq	= db1550_map_pci_irq,
पूर्ण;

अटल काष्ठा platक्रमm_device db1550_pci_host_dev = अणु
	.dev.platक्रमm_data = &db1550_pci_pd,
	.name		= "alchemy-pci",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(alchemy_pci_host_res),
	.resource	= alchemy_pci_host_res,
पूर्ण;

/**********************************************************************/

अटल काष्ठा platक्रमm_device *db1550_devs[] __initdata = अणु
	&db1550_i2c_dev,
	&db1550_ac97_dev,
	&db1550_spi_dev,
	&db1550_i2s_dev,
	&db1550_stac_dev,
	&db1550_ac97dma_dev,
	&db1550_i2sdma_dev,
	&db1550_sndac97_dev,
	&db1550_sndi2s_dev,
पूर्ण;

/* must be arch_initcall; MIPS PCI scans busses in a subsys_initcall */
पूर्णांक __init db1550_pci_setup(पूर्णांक id)
अणु
	अगर (id)
		db1550_pci_pd.board_map_irq = pb1550_map_pci_irq;
	वापस platक्रमm_device_रेजिस्टर(&db1550_pci_host_dev);
पूर्ण

अटल व्योम __init db1550_devices(व्योम)
अणु
	alchemy_gpio_direction_output(203, 0);	/* red led on */

	irq_set_irq_type(AU1550_GPIO0_INT, IRQ_TYPE_EDGE_BOTH);	 /* CD0# */
	irq_set_irq_type(AU1550_GPIO1_INT, IRQ_TYPE_EDGE_BOTH);	 /* CD1# */
	irq_set_irq_type(AU1550_GPIO3_INT, IRQ_TYPE_LEVEL_LOW);	 /* CARD0# */
	irq_set_irq_type(AU1550_GPIO5_INT, IRQ_TYPE_LEVEL_LOW);	 /* CARD1# */
	irq_set_irq_type(AU1550_GPIO21_INT, IRQ_TYPE_LEVEL_LOW); /* STSCHG0# */
	irq_set_irq_type(AU1550_GPIO22_INT, IRQ_TYPE_LEVEL_LOW); /* STSCHG1# */

	db1x_रेजिस्टर_pcmcia_socket(
		AU1000_PCMCIA_ATTR_PHYS_ADDR,
		AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x000400000 - 1,
		AU1000_PCMCIA_MEM_PHYS_ADDR,
		AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x000400000 - 1,
		AU1000_PCMCIA_IO_PHYS_ADDR,
		AU1000_PCMCIA_IO_PHYS_ADDR   + 0x000010000 - 1,
		AU1550_GPIO3_INT, 0,
		/*AU1550_GPIO21_INT*/0, 0, 0);

	db1x_रेजिस्टर_pcmcia_socket(
		AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x004000000,
		AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x004400000 - 1,
		AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x004000000,
		AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x004400000 - 1,
		AU1000_PCMCIA_IO_PHYS_ADDR   + 0x004000000,
		AU1000_PCMCIA_IO_PHYS_ADDR   + 0x004010000 - 1,
		AU1550_GPIO5_INT, 1,
		/*AU1550_GPIO22_INT*/0, 0, 1);

	platक्रमm_device_रेजिस्टर(&db1550_nand_dev);

	alchemy_gpio_direction_output(202, 0);	/* green led on */
पूर्ण

अटल व्योम __init pb1550_devices(व्योम)
अणु
	irq_set_irq_type(AU1550_GPIO0_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1550_GPIO1_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1550_GPIO201_205_INT, IRQ_TYPE_LEVEL_HIGH);

	/* enable both PCMCIA card irqs in the shared line */
	alchemy_gpio2_enable_पूर्णांक(201);	/* socket 0 card irq */
	alchemy_gpio2_enable_पूर्णांक(202);	/* socket 1 card irq */

	/* Pb1550, like all others, also has statuschange irqs; however they're
	* wired up on one of the Au1550's shared GPIO201_205 line, which also
	* services the PCMCIA card पूर्णांकerrupts.	So we ignore statuschange and
	* use the GPIO201_205 exclusively क्रम card पूर्णांकerrupts, since a) pcmcia
	* drivers are used to shared irqs and b) statuschange isn't really use-
	* ful anyway.
	*/
	db1x_रेजिस्टर_pcmcia_socket(
		AU1000_PCMCIA_ATTR_PHYS_ADDR,
		AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x000400000 - 1,
		AU1000_PCMCIA_MEM_PHYS_ADDR,
		AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x000400000 - 1,
		AU1000_PCMCIA_IO_PHYS_ADDR,
		AU1000_PCMCIA_IO_PHYS_ADDR   + 0x000010000 - 1,
		AU1550_GPIO201_205_INT, AU1550_GPIO0_INT, 0, 0, 0);

	db1x_रेजिस्टर_pcmcia_socket(
		AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x008000000,
		AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x008400000 - 1,
		AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x008000000,
		AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x008400000 - 1,
		AU1000_PCMCIA_IO_PHYS_ADDR   + 0x008000000,
		AU1000_PCMCIA_IO_PHYS_ADDR   + 0x008010000 - 1,
		AU1550_GPIO201_205_INT, AU1550_GPIO1_INT, 0, 0, 1);

	pb1550_nand_setup();
पूर्ण

पूर्णांक __init db1550_dev_setup(व्योम)
अणु
	पूर्णांक swapped, id;
	काष्ठा clk *c;

	id = (BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI)) != BCSR_WHOAMI_DB1550);

	i2c_रेजिस्टर_board_info(0, db1550_i2c_devs,
				ARRAY_SIZE(db1550_i2c_devs));
	spi_रेजिस्टर_board_info(db1550_spi_devs,
				ARRAY_SIZE(db1550_i2c_devs));

	c = clk_get(शून्य, "psc0_intclk");
	अगर (!IS_ERR(c)) अणु
		clk_set_rate(c, 50000000);
		clk_prepare_enable(c);
		clk_put(c);
	पूर्ण
	c = clk_get(शून्य, "psc2_intclk");
	अगर (!IS_ERR(c)) अणु
		clk_set_rate(c, db1550_spi_platdata.मुख्यclk_hz);
		clk_prepare_enable(c);
		clk_put(c);
	पूर्ण

	/* Audio PSC घड़ी is supplied by codecs (PSC1, 3) FIXME: platdata!! */
	__raw_ग_लिखोl(PSC_SEL_CLK_SERCLK,
	    (व्योम __iomem *)KSEG1ADDR(AU1550_PSC1_PHYS_ADDR) + PSC_SEL_OFFSET);
	wmb();
	__raw_ग_लिखोl(PSC_SEL_CLK_SERCLK,
	    (व्योम __iomem *)KSEG1ADDR(AU1550_PSC3_PHYS_ADDR) + PSC_SEL_OFFSET);
	wmb();
	/* SPI/I2C use पूर्णांकernally supplied 50MHz source */
	__raw_ग_लिखोl(PSC_SEL_CLK_INTCLK,
	    (व्योम __iomem *)KSEG1ADDR(AU1550_PSC0_PHYS_ADDR) + PSC_SEL_OFFSET);
	wmb();
	__raw_ग_लिखोl(PSC_SEL_CLK_INTCLK,
	    (व्योम __iomem *)KSEG1ADDR(AU1550_PSC2_PHYS_ADDR) + PSC_SEL_OFFSET);
	wmb();

	id ? pb1550_devices() : db1550_devices();

	swapped = bcsr_पढ़ो(BCSR_STATUS) &
	       (id ? BCSR_STATUS_PB1550_SWAPBOOT : BCSR_STATUS_DB1000_SWAPBOOT);
	db1x_रेजिस्टर_norflash(128 << 20, 4, swapped);

	वापस platक्रमm_add_devices(db1550_devs, ARRAY_SIZE(db1550_devs));
पूर्ण
