<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2005 Sven Luther <sl@bplan-gmbh.de>
 *  Thanks to :
 *	Dale Farnsworth <dale@farnsworth.org>
 *	Mark A. Greer <mgreer@mvista.com>
 *	Nicolas DET <nd@bplan-gmbh.de>
 *	Benjamin Herrenschmidt <benh@kernel.crashing.org>
 *  And anyone अन्यथा who helped me on this.
 */

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mv643xx.h>
#समावेश <linux/pci.h>

#घोषणा PEGASOS2_MARVELL_REGBASE 		(0xf1000000)
#घोषणा PEGASOS2_MARVELL_REGSIZE 		(0x00004000)
#घोषणा PEGASOS2_SRAM_BASE 			(0xf2000000)
#घोषणा PEGASOS2_SRAM_SIZE			(256*1024)

#घोषणा PEGASOS2_SRAM_BASE_ETH_PORT0			(PEGASOS2_SRAM_BASE)
#घोषणा PEGASOS2_SRAM_BASE_ETH_PORT1			(PEGASOS2_SRAM_BASE_ETH_PORT0 + (PEGASOS2_SRAM_SIZE / 2) )


#घोषणा PEGASOS2_SRAM_RXRING_SIZE		(PEGASOS2_SRAM_SIZE/4)
#घोषणा PEGASOS2_SRAM_TXRING_SIZE		(PEGASOS2_SRAM_SIZE/4)

#अघोषित BE_VERBOSE

अटल काष्ठा resource mv643xx_eth_shared_resources[] = अणु
	[0] = अणु
		.name	= "ethernet shared base",
		.start	= 0xf1000000 + MV643XX_ETH_SHARED_REGS,
		.end	= 0xf1000000 + MV643XX_ETH_SHARED_REGS +
					MV643XX_ETH_SHARED_REGS_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mv643xx_eth_shared_device = अणु
	.name		= MV643XX_ETH_SHARED_NAME,
	.id		= 0,
	.num_resources	= ARRAY_SIZE(mv643xx_eth_shared_resources),
	.resource	= mv643xx_eth_shared_resources,
पूर्ण;

/*
 * The orion mdio driver only covers shared + 0x4 up to shared + 0x84 - 1
 */
अटल काष्ठा resource mv643xx_eth_mvmdio_resources[] = अणु
	[0] = अणु
		.name	= "ethernet mdio base",
		.start	= 0xf1000000 + MV643XX_ETH_SHARED_REGS + 0x4,
		.end	= 0xf1000000 + MV643XX_ETH_SHARED_REGS + 0x83,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mv643xx_eth_mvmdio_device = अणु
	.name		= "orion-mdio",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(mv643xx_eth_mvmdio_resources),
	.resource	= mv643xx_eth_mvmdio_resources,
पूर्ण;

अटल काष्ठा resource mv643xx_eth_port1_resources[] = अणु
	[0] = अणु
		.name	= "eth port1 irq",
		.start	= 9,
		.end	= 9,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा mv643xx_eth_platक्रमm_data eth_port1_pd = अणु
	.shared		= &mv643xx_eth_shared_device,
	.port_number	= 1,
	.phy_addr	= MV643XX_ETH_PHY_ADDR(7),

	.tx_sram_addr = PEGASOS2_SRAM_BASE_ETH_PORT1,
	.tx_sram_size = PEGASOS2_SRAM_TXRING_SIZE,
	.tx_queue_size = PEGASOS2_SRAM_TXRING_SIZE/16,

	.rx_sram_addr = PEGASOS2_SRAM_BASE_ETH_PORT1 + PEGASOS2_SRAM_TXRING_SIZE,
	.rx_sram_size = PEGASOS2_SRAM_RXRING_SIZE,
	.rx_queue_size = PEGASOS2_SRAM_RXRING_SIZE/16,
पूर्ण;

अटल काष्ठा platक्रमm_device eth_port1_device = अणु
	.name		= MV643XX_ETH_NAME,
	.id		= 1,
	.num_resources	= ARRAY_SIZE(mv643xx_eth_port1_resources),
	.resource	= mv643xx_eth_port1_resources,
	.dev = अणु
		.platक्रमm_data = &eth_port1_pd,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *mv643xx_eth_pd_devs[] __initdata = अणु
	&mv643xx_eth_shared_device,
	&mv643xx_eth_mvmdio_device,
	&eth_port1_device,
पूर्ण;

/***********/
/***********/
#घोषणा MV_READ(offset,val) 	अणु val = पढ़ोl(mv643xx_reg_base + offset); पूर्ण
#घोषणा MV_WRITE(offset,data) ग_लिखोl(data, mv643xx_reg_base + offset)

अटल व्योम __iomem *mv643xx_reg_base;

अटल पूर्णांक Enable_SRAM(व्योम)
अणु
	u32 ALong;

	अगर (mv643xx_reg_base == शून्य)
		mv643xx_reg_base = ioremap(PEGASOS2_MARVELL_REGBASE,
					PEGASOS2_MARVELL_REGSIZE);

	अगर (mv643xx_reg_base == शून्य)
		वापस -ENOMEM;

#अगर_घोषित BE_VERBOSE
	prपूर्णांकk("Pegasos II/Marvell MV64361: register remapped from %p to %p\n",
		(व्योम *)PEGASOS2_MARVELL_REGBASE, (व्योम *)mv643xx_reg_base);
#पूर्ण_अगर

	MV_WRITE(MV64340_SRAM_CONFIG, 0);

	MV_WRITE(MV64340_INTEGRATED_SRAM_BASE_ADDR, PEGASOS2_SRAM_BASE >> 16);

	MV_READ(MV64340_BASE_ADDR_ENABLE, ALong);
	ALong &= ~(1 << 19);
	MV_WRITE(MV64340_BASE_ADDR_ENABLE, ALong);

	ALong = 0x02;
	ALong |= PEGASOS2_SRAM_BASE & 0xffff0000;
	MV_WRITE(MV643XX_ETH_BAR_4, ALong);

	MV_WRITE(MV643XX_ETH_SIZE_REG_4, (PEGASOS2_SRAM_SIZE-1) & 0xffff0000);

	MV_READ(MV643XX_ETH_BASE_ADDR_ENABLE_REG, ALong);
	ALong &= ~(1 << 4);
	MV_WRITE(MV643XX_ETH_BASE_ADDR_ENABLE_REG, ALong);

#अगर_घोषित BE_VERBOSE
	prपूर्णांकk("Pegasos II/Marvell MV64361: register unmapped\n");
	prपूर्णांकk("Pegasos II/Marvell MV64361: SRAM at %p, size=%x\n", (व्योम*) PEGASOS2_SRAM_BASE, PEGASOS2_SRAM_SIZE);
#पूर्ण_अगर

	iounmap(mv643xx_reg_base);
	mv643xx_reg_base = शून्य;

	वापस 1;
पूर्ण


/***********/
/***********/
अटल पूर्णांक __init mv643xx_eth_add_pds(व्योम)
अणु
	पूर्णांक ret = 0;
	अटल काष्ठा pci_device_id pci_marvell_mv64360[] = अणु
		अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, PCI_DEVICE_ID_MARVELL_MV64360) पूर्ण,
		अणु पूर्ण
	पूर्ण;

#अगर_घोषित BE_VERBOSE
	prपूर्णांकk("Pegasos II/Marvell MV64361: init\n");
#पूर्ण_अगर

	अगर (pci_dev_present(pci_marvell_mv64360)) अणु
		ret = platक्रमm_add_devices(mv643xx_eth_pd_devs,
				ARRAY_SIZE(mv643xx_eth_pd_devs));

		अगर ( Enable_SRAM() < 0)
		अणु
			eth_port1_pd.tx_sram_addr = 0;
			eth_port1_pd.tx_sram_size = 0;
			eth_port1_pd.rx_sram_addr = 0;
			eth_port1_pd.rx_sram_size = 0;

#अगर_घोषित BE_VERBOSE
			prपूर्णांकk("Pegasos II/Marvell MV64361: Can't enable the "
				"SRAM\n");
#पूर्ण_अगर
		पूर्ण
	पूर्ण

#अगर_घोषित BE_VERBOSE
	prपूर्णांकk("Pegasos II/Marvell MV64361: init is over\n");
#पूर्ण_अगर

	वापस ret;
पूर्ण

device_initcall(mv643xx_eth_add_pds);
