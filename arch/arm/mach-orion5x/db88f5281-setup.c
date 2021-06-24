<शैली गुरु>
/*
 * arch/arm/mach-orion5x/db88f5281-setup.c
 *
 * Marvell Orion-2 Development Board Setup
 *
 * Maपूर्णांकainer: Tzachi Perelstein <tzachi@marvell.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/i2c.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <linux/platक्रमm_data/mtd-orion_nand.h>
#समावेश "common.h"
#समावेश "mpp.h"
#समावेश "orion5x.h"

/*****************************************************************************
 * DB-88F5281 on board devices
 ****************************************************************************/

/*
 * 512K NOR flash Device bus boot chip select
 */

#घोषणा DB88F5281_NOR_BOOT_BASE		0xf4000000
#घोषणा DB88F5281_NOR_BOOT_SIZE		SZ_512K

/*
 * 7-Segment on Device bus chip select 0
 */

#घोषणा DB88F5281_7SEG_BASE		0xfa000000
#घोषणा DB88F5281_7SEG_SIZE		SZ_1K

/*
 * 32M NOR flash on Device bus chip select 1
 */

#घोषणा DB88F5281_NOR_BASE		0xfc000000
#घोषणा DB88F5281_NOR_SIZE		SZ_32M

/*
 * 32M न_अंकD flash on Device bus chip select 2
 */

#घोषणा DB88F5281_न_अंकD_BASE		0xfa800000
#घोषणा DB88F5281_न_अंकD_SIZE		SZ_1K

/*
 * PCI
 */

#घोषणा DB88F5281_PCI_SLOT0_OFFS		7
#घोषणा DB88F5281_PCI_SLOT0_IRQ_PIN		12
#घोषणा DB88F5281_PCI_SLOT1_SLOT2_IRQ_PIN	13

/*****************************************************************************
 * 512M NOR Flash on Device bus Boot CS
 ****************************************************************************/

अटल काष्ठा physmap_flash_data db88f5281_boot_flash_data = अणु
	.width		= 1,	/* 8 bit bus width */
पूर्ण;

अटल काष्ठा resource db88f5281_boot_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
	.start		= DB88F5281_NOR_BOOT_BASE,
	.end		= DB88F5281_NOR_BOOT_BASE + DB88F5281_NOR_BOOT_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device db88f5281_boot_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &db88f5281_boot_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &db88f5281_boot_flash_resource,
पूर्ण;

/*****************************************************************************
 * 32M NOR Flash on Device bus CS1
 ****************************************************************************/

अटल काष्ठा physmap_flash_data db88f5281_nor_flash_data = अणु
	.width		= 4,	/* 32 bit bus width */
पूर्ण;

अटल काष्ठा resource db88f5281_nor_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
	.start		= DB88F5281_NOR_BASE,
	.end		= DB88F5281_NOR_BASE + DB88F5281_NOR_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device db88f5281_nor_flash = अणु
	.name		= "physmap-flash",
	.id		= 1,
	.dev		= अणु
		.platक्रमm_data	= &db88f5281_nor_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &db88f5281_nor_flash_resource,
पूर्ण;

/*****************************************************************************
 * 32M न_अंकD Flash on Device bus CS2
 ****************************************************************************/

अटल काष्ठा mtd_partition db88f5281_nand_parts[] = अणु
	अणु
		.name = "kernel",
		.offset = 0,
		.size = SZ_2M,
	पूर्ण, अणु
		.name = "root",
		.offset = SZ_2M,
		.size = (SZ_16M - SZ_2M),
	पूर्ण, अणु
		.name = "user",
		.offset = SZ_16M,
		.size = SZ_8M,
	पूर्ण, अणु
		.name = "recovery",
		.offset = (SZ_16M + SZ_8M),
		.size = SZ_8M,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource db88f5281_nand_resource = अणु
	.flags		= IORESOURCE_MEM,
	.start		= DB88F5281_न_अंकD_BASE,
	.end		= DB88F5281_न_अंकD_BASE + DB88F5281_न_अंकD_SIZE - 1,
पूर्ण;

अटल काष्ठा orion_nand_data db88f5281_nand_data = अणु
	.parts		= db88f5281_nand_parts,
	.nr_parts	= ARRAY_SIZE(db88f5281_nand_parts),
	.cle		= 0,
	.ale		= 1,
	.width		= 8,
पूर्ण;

अटल काष्ठा platक्रमm_device db88f5281_nand_flash = अणु
	.name		= "orion_nand",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &db88f5281_nand_data,
	पूर्ण,
	.resource	= &db88f5281_nand_resource,
	.num_resources	= 1,
पूर्ण;

/*****************************************************************************
 * 7-Segment on Device bus CS0
 * Dummy counter every 2 sec
 ****************************************************************************/

अटल व्योम __iomem *db88f5281_7seg;
अटल काष्ठा समयr_list db88f5281_समयr;

अटल व्योम db88f5281_7seg_event(काष्ठा समयr_list *unused)
अणु
	अटल पूर्णांक count = 0;
	ग_लिखोl(0, db88f5281_7seg + (count << 4));
	count = (count + 1) & 7;
	mod_समयr(&db88f5281_समयr, jअगरfies + 2 * HZ);
पूर्ण

अटल पूर्णांक __init db88f5281_7seg_init(व्योम)
अणु
	अगर (machine_is_db88f5281()) अणु
		db88f5281_7seg = ioremap(DB88F5281_7SEG_BASE,
					DB88F5281_7SEG_SIZE);
		अगर (!db88f5281_7seg) अणु
			prपूर्णांकk(KERN_ERR "Failed to ioremap db88f5281_7seg\n");
			वापस -EIO;
		पूर्ण
		समयr_setup(&db88f5281_समयr, db88f5281_7seg_event, 0);
		mod_समयr(&db88f5281_समयr, jअगरfies + 2 * HZ);
	पूर्ण

	वापस 0;
पूर्ण

__initcall(db88f5281_7seg_init);

/*****************************************************************************
 * PCI
 ****************************************************************************/

अटल व्योम __init db88f5281_pci_preinit(व्योम)
अणु
	पूर्णांक pin;

	/*
	 * Configure PCI GPIO IRQ pins
	 */
	pin = DB88F5281_PCI_SLOT0_IRQ_PIN;
	अगर (gpio_request(pin, "PCI Int1") == 0) अणु
		अगर (gpio_direction_input(pin) == 0) अणु
			irq_set_irq_type(gpio_to_irq(pin), IRQ_TYPE_LEVEL_LOW);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "db88f5281_pci_preinit failed to "
					"set_irq_type pin %d\n", pin);
			gpio_मुक्त(pin);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "db88f5281_pci_preinit failed to gpio_request %d\n", pin);
	पूर्ण

	pin = DB88F5281_PCI_SLOT1_SLOT2_IRQ_PIN;
	अगर (gpio_request(pin, "PCI Int2") == 0) अणु
		अगर (gpio_direction_input(pin) == 0) अणु
			irq_set_irq_type(gpio_to_irq(pin), IRQ_TYPE_LEVEL_LOW);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "db88f5281_pci_preinit failed "
					"to set_irq_type pin %d\n", pin);
			gpio_मुक्त(pin);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "db88f5281_pci_preinit failed to gpio_request %d\n", pin);
	पूर्ण
पूर्ण

अटल पूर्णांक __init db88f5281_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot,
	u8 pin)
अणु
	पूर्णांक irq;

	/*
	 * Check क्रम devices with hard-wired IRQs.
	 */
	irq = orion5x_pci_map_irq(dev, slot, pin);
	अगर (irq != -1)
		वापस irq;

	/*
	 * PCI IRQs are connected via GPIOs.
	 */
	चयन (slot - DB88F5281_PCI_SLOT0_OFFS) अणु
	हाल 0:
		वापस gpio_to_irq(DB88F5281_PCI_SLOT0_IRQ_PIN);
	हाल 1:
	हाल 2:
		वापस gpio_to_irq(DB88F5281_PCI_SLOT1_SLOT2_IRQ_PIN);
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल काष्ठा hw_pci db88f5281_pci __initdata = अणु
	.nr_controllers	= 2,
	.preinit	= db88f5281_pci_preinit,
	.setup		= orion5x_pci_sys_setup,
	.scan		= orion5x_pci_sys_scan_bus,
	.map_irq	= db88f5281_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init db88f5281_pci_init(व्योम)
अणु
	अगर (machine_is_db88f5281())
		pci_common_init(&db88f5281_pci);

	वापस 0;
पूर्ण

subsys_initcall(db88f5281_pci_init);

/*****************************************************************************
 * Ethernet
 ****************************************************************************/
अटल काष्ठा mv643xx_eth_platक्रमm_data db88f5281_eth_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_ADDR(8),
पूर्ण;

/*****************************************************************************
 * RTC DS1339 on I2C bus
 ****************************************************************************/
अटल काष्ठा i2c_board_info __initdata db88f5281_i2c_rtc = अणु
	I2C_BOARD_INFO("ds1339", 0x68),
पूर्ण;

/*****************************************************************************
 * General Setup
 ****************************************************************************/
अटल अचिन्हित पूर्णांक db88f5281_mpp_modes[] __initdata = अणु
	MPP0_GPIO,		/* USB Over Current */
	MPP1_GPIO,		/* USB Vbat input */
	MPP2_PCI_ARB,		/* PCI_REQn[2] */
	MPP3_PCI_ARB,		/* PCI_GNTn[2] */
	MPP4_PCI_ARB,		/* PCI_REQn[3] */
	MPP5_PCI_ARB,		/* PCI_GNTn[3] */
	MPP6_GPIO,		/* JP0, CON17.2 */
	MPP7_GPIO,		/* JP1, CON17.1 */
	MPP8_GPIO,		/* JP2, CON11.2 */
	MPP9_GPIO,		/* JP3, CON11.3 */
	MPP10_GPIO,		/* RTC पूर्णांक */
	MPP11_GPIO,		/* Baud Rate Generator */
	MPP12_GPIO,		/* PCI पूर्णांक 1 */
	MPP13_GPIO,		/* PCI पूर्णांक 2 */
	MPP14_न_अंकD,		/* न_अंकD_REn[2] */
	MPP15_न_अंकD,		/* न_अंकD_WEn[2] */
	MPP16_UART,		/* UART1_RX */
	MPP17_UART,		/* UART1_TX */
	MPP18_UART,		/* UART1_CTSn */
	MPP19_UART,		/* UART1_RTSn */
	0,
पूर्ण;

अटल व्योम __init db88f5281_init(व्योम)
अणु
	/*
	 * Basic Orion setup. Need to be called early.
	 */
	orion5x_init();

	orion5x_mpp_conf(db88f5281_mpp_modes);
	ग_लिखोl(0, MPP_DEV_CTRL);		/* DEV_D[31:16] */

	/*
	 * Configure peripherals.
	 */
	orion5x_ehci0_init();
	orion5x_eth_init(&db88f5281_eth_data);
	orion5x_i2c_init();
	orion5x_uart0_init();
	orion5x_uart1_init();

	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    DB88F5281_NOR_BOOT_BASE,
				    DB88F5281_NOR_BOOT_SIZE);
	platक्रमm_device_रेजिस्टर(&db88f5281_boot_flash);

	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_TARGET(0),
				    ORION_MBUS_DEVBUS_ATTR(0),
				    DB88F5281_7SEG_BASE,
				    DB88F5281_7SEG_SIZE);

	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_TARGET(1),
				    ORION_MBUS_DEVBUS_ATTR(1),
				    DB88F5281_NOR_BASE,
				    DB88F5281_NOR_SIZE);
	platक्रमm_device_रेजिस्टर(&db88f5281_nor_flash);

	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_TARGET(2),
				    ORION_MBUS_DEVBUS_ATTR(2),
				    DB88F5281_न_अंकD_BASE,
				    DB88F5281_न_अंकD_SIZE);
	platक्रमm_device_रेजिस्टर(&db88f5281_nand_flash);

	i2c_रेजिस्टर_board_info(0, &db88f5281_i2c_rtc, 1);
पूर्ण

MACHINE_START(DB88F5281, "Marvell Orion-2 Development Board")
	/* Maपूर्णांकainer: Tzachi Perelstein <tzachi@marvell.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= db88f5281_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.restart	= orion5x_restart,
MACHINE_END
