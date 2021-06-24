<शैली गुरु>
/*
 * arch/arm/mach-करोve/करोve-db-setup.c
 *
 * Marvell DB-MV88AP510-BP Development Board Setup
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/समयr.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pci.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>
#समावेश <linux/gpपन.स>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "dove.h"
#समावेश "common.h"

अटल काष्ठा mv643xx_eth_platक्रमm_data करोve_db_ge00_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_ADDR_DEFAULT,
पूर्ण;

अटल काष्ठा mv_sata_platक्रमm_data करोve_db_sata_data = अणु
	.n_ports        = 1,
पूर्ण;

/*****************************************************************************
 * SPI Devices:
 * 	SPI0: 4M Flash ST-M25P32-VMF6P
 ****************************************************************************/
अटल स्थिर काष्ठा flash_platक्रमm_data करोve_db_spi_flash_data = अणु
	.type		= "m25p64",
पूर्ण;

अटल काष्ठा spi_board_info __initdata करोve_db_spi_flash_info[] = अणु
	अणु
		.modalias       = "m25p80",
		.platक्रमm_data  = &करोve_db_spi_flash_data,
		.irq            = -1,
		.max_speed_hz   = 20000000,
		.bus_num        = 0,
		.chip_select    = 0,
	पूर्ण,
पूर्ण;

/*****************************************************************************
 * PCI
 ****************************************************************************/
अटल पूर्णांक __init करोve_db_pci_init(व्योम)
अणु
	अगर (machine_is_करोve_db())
		करोve_pcie_init(1, 1);

	वापस 0;
पूर्ण

subsys_initcall(करोve_db_pci_init);

/*****************************************************************************
 * Board Init
 ****************************************************************************/
अटल व्योम __init करोve_db_init(व्योम)
अणु
	/*
	 * Basic Dove setup. Needs to be called early.
	 */
	करोve_init();

	करोve_ge00_init(&करोve_db_ge00_data);
	करोve_ehci0_init();
	करोve_ehci1_init();
	करोve_sata_init(&करोve_db_sata_data);
	करोve_sdio0_init();
	करोve_sdio1_init();
	करोve_spi0_init();
	करोve_spi1_init();
	करोve_uart0_init();
	करोve_uart1_init();
	करोve_i2c_init();
	spi_रेजिस्टर_board_info(करोve_db_spi_flash_info,
				ARRAY_SIZE(करोve_db_spi_flash_info));
पूर्ण

MACHINE_START(DOVE_DB, "Marvell DB-MV88AP510-BP Development Board")
	.atag_offset	= 0x100,
	.nr_irqs	= DOVE_NR_IRQS,
	.init_machine	= करोve_db_init,
	.map_io		= करोve_map_io,
	.init_early	= करोve_init_early,
	.init_irq	= करोve_init_irq,
	.init_समय	= करोve_समयr_init,
	.restart	= करोve_restart,
MACHINE_END
