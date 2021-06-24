<शैली गुरु>
/*
 * arch/arm/mach-mv78x00/rd78x00-masa-setup.c
 *
 * Marvell RD-78x00-mASA Development Board Setup
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
#समावेश <linux/ethtool.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "mv78xx0.h"
#समावेश "common.h"

अटल काष्ठा mv643xx_eth_platक्रमm_data rd78x00_masa_ge00_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_ADDR(8),
पूर्ण;

अटल काष्ठा mv643xx_eth_platक्रमm_data rd78x00_masa_ge01_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_ADDR(9),
पूर्ण;

अटल काष्ठा mv643xx_eth_platक्रमm_data rd78x00_masa_ge10_data = अणु
पूर्ण;

अटल काष्ठा mv643xx_eth_platक्रमm_data rd78x00_masa_ge11_data = अणु
पूर्ण;

अटल काष्ठा mv_sata_platक्रमm_data rd78x00_masa_sata_data = अणु
	.n_ports	= 2,
पूर्ण;

अटल व्योम __init rd78x00_masa_init(व्योम)
अणु
	/*
	 * Basic MV78x00 setup. Needs to be called early.
	 */
	mv78xx0_init();

	/*
	 * Partition on-chip peripherals between the two CPU cores.
	 */
	अगर (mv78xx0_core_index() == 0) अणु
		mv78xx0_ehci0_init();
		mv78xx0_ehci1_init();
		mv78xx0_ge00_init(&rd78x00_masa_ge00_data);
		mv78xx0_ge10_init(&rd78x00_masa_ge10_data);
		mv78xx0_sata_init(&rd78x00_masa_sata_data);
		mv78xx0_uart0_init();
		mv78xx0_uart2_init();
	पूर्ण अन्यथा अणु
		mv78xx0_ehci2_init();
		mv78xx0_ge01_init(&rd78x00_masa_ge01_data);
		mv78xx0_ge11_init(&rd78x00_masa_ge11_data);
		mv78xx0_uart1_init();
		mv78xx0_uart3_init();
	पूर्ण
पूर्ण

अटल पूर्णांक __init rd78x00_pci_init(व्योम)
अणु
	/*
	 * Assign all PCIe devices to CPU core #0.
	 */
	अगर (machine_is_rd78x00_masa() && mv78xx0_core_index() == 0)
		mv78xx0_pcie_init(1, 1);

	वापस 0;
पूर्ण
subsys_initcall(rd78x00_pci_init);

MACHINE_START(RD78X00_MASA, "Marvell RD-78x00-MASA Development Board")
	/* Maपूर्णांकainer: Lennert Buytenhek <buytenh@marvell.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= MV78XX0_NR_IRQS,
	.init_machine	= rd78x00_masa_init,
	.map_io		= mv78xx0_map_io,
	.init_early	= mv78xx0_init_early,
	.init_irq	= mv78xx0_init_irq,
	.init_समय	= mv78xx0_समयr_init,
	.restart	= mv78xx0_restart,
MACHINE_END
