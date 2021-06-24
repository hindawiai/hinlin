<शैली गुरु>
/*
 * arch/arm/mach-करोve/cm-a510.c
 *
 * Copyright (C) 2010 CompuLab, Ltd.
 * Konstantin Sinyuk <kostyas@compulab.co.il>
 *
 * Based on Marvell DB-MV88AP510-BP Development Board Setup
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "dove.h"
#समावेश "common.h"

अटल काष्ठा mv643xx_eth_platक्रमm_data cm_a510_ge00_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_ADDR_DEFAULT,
पूर्ण;

अटल काष्ठा mv_sata_platक्रमm_data cm_a510_sata_data = अणु
	.n_ports        = 1,
पूर्ण;

/*
 * SPI Devices:
 * SPI0: 1M Flash Winbond w25q32bv
 */
अटल स्थिर काष्ठा flash_platक्रमm_data cm_a510_spi_flash_data = अणु
	.type		= "w25q32bv",
पूर्ण;

अटल काष्ठा spi_board_info __initdata cm_a510_spi_flash_info[] = अणु
	अणु
		.modalias       = "m25p80",
		.platक्रमm_data  = &cm_a510_spi_flash_data,
		.irq            = -1,
		.max_speed_hz   = 20000000,
		.bus_num        = 0,
		.chip_select    = 0,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init cm_a510_pci_init(व्योम)
अणु
	अगर (machine_is_cm_a510())
		करोve_pcie_init(1, 1);

	वापस 0;
पूर्ण

subsys_initcall(cm_a510_pci_init);

/* Board Init */
अटल व्योम __init cm_a510_init(व्योम)
अणु
	/*
	 * Basic Dove setup. Needs to be called early.
	 */
	करोve_init();

	करोve_ge00_init(&cm_a510_ge00_data);
	करोve_ehci0_init();
	करोve_ehci1_init();
	करोve_sata_init(&cm_a510_sata_data);
	करोve_sdio0_init();
	करोve_sdio1_init();
	करोve_spi0_init();
	करोve_spi1_init();
	करोve_uart0_init();
	करोve_uart1_init();
	करोve_i2c_init();
	spi_रेजिस्टर_board_info(cm_a510_spi_flash_info,
				ARRAY_SIZE(cm_a510_spi_flash_info));
पूर्ण

MACHINE_START(CM_A510, "Compulab CM-A510 Board")
	.atag_offset	= 0x100,
	.nr_irqs	= DOVE_NR_IRQS,
	.init_machine	= cm_a510_init,
	.map_io		= करोve_map_io,
	.init_early	= करोve_init_early,
	.init_irq	= करोve_init_irq,
	.init_समय	= करोve_समयr_init,
	.restart	= करोve_restart,
MACHINE_END
