<शैली गुरु>
/*
 * arch/arm/mach-orion5x/common.c
 *
 * Core functions क्रम Marvell Orion 5x SoCs
 *
 * Maपूर्णांकainer: Tzachi Perelstein <tzachi@marvell.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/mv643xx_i2c.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/cpu.h>
#समावेश <linux/platक्रमm_data/dsa.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <linux/platक्रमm_data/mtd-orion_nand.h>
#समावेश <linux/platक्रमm_data/usb-ehci-orion.h>
#समावेश <plat/समय.स>
#समावेश <plat/common.h>

#समावेश "bridge-regs.h"
#समावेश "common.h"
#समावेश "orion5x.h"

/*****************************************************************************
 * I/O Address Mapping
 ****************************************************************************/
अटल काष्ठा map_desc orion5x_io_desc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ) ORION5X_REGS_VIRT_BASE,
		.pfn		= __phys_to_pfn(ORION5X_REGS_PHYS_BASE),
		.length		= ORION5X_REGS_SIZE,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ) ORION5X_PCIE_WA_VIRT_BASE,
		.pfn		= __phys_to_pfn(ORION5X_PCIE_WA_PHYS_BASE),
		.length		= ORION5X_PCIE_WA_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

व्योम __init orion5x_map_io(व्योम)
अणु
	iotable_init(orion5x_io_desc, ARRAY_SIZE(orion5x_io_desc));
पूर्ण


/*****************************************************************************
 * CLK tree
 ****************************************************************************/
अटल काष्ठा clk *tclk;

व्योम __init clk_init(व्योम)
अणु
	tclk = clk_रेजिस्टर_fixed_rate(शून्य, "tclk", शून्य, 0, orion5x_tclk);

	orion_clkdev_init(tclk);
पूर्ण

/*****************************************************************************
 * EHCI0
 ****************************************************************************/
व्योम __init orion5x_ehci0_init(व्योम)
अणु
	orion_ehci_init(ORION5X_USB0_PHYS_BASE, IRQ_ORION5X_USB0_CTRL,
			EHCI_PHY_ORION);
पूर्ण


/*****************************************************************************
 * EHCI1
 ****************************************************************************/
व्योम __init orion5x_ehci1_init(व्योम)
अणु
	orion_ehci_1_init(ORION5X_USB1_PHYS_BASE, IRQ_ORION5X_USB1_CTRL);
पूर्ण


/*****************************************************************************
 * GE00
 ****************************************************************************/
व्योम __init orion5x_eth_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data)
अणु
	orion_ge00_init(eth_data,
			ORION5X_ETH_PHYS_BASE, IRQ_ORION5X_ETH_SUM,
			IRQ_ORION5X_ETH_ERR,
			MV643XX_TX_CSUM_DEFAULT_LIMIT);
पूर्ण


/*****************************************************************************
 * Ethernet चयन
 ****************************************************************************/
व्योम __init orion5x_eth_चयन_init(काष्ठा dsa_chip_data *d)
अणु
	orion_ge00_चयन_init(d);
पूर्ण


/*****************************************************************************
 * I2C
 ****************************************************************************/
व्योम __init orion5x_i2c_init(व्योम)
अणु
	orion_i2c_init(I2C_PHYS_BASE, IRQ_ORION5X_I2C, 8);

पूर्ण


/*****************************************************************************
 * SATA
 ****************************************************************************/
व्योम __init orion5x_sata_init(काष्ठा mv_sata_platक्रमm_data *sata_data)
अणु
	orion_sata_init(sata_data, ORION5X_SATA_PHYS_BASE, IRQ_ORION5X_SATA);
पूर्ण


/*****************************************************************************
 * SPI
 ****************************************************************************/
व्योम __init orion5x_spi_init(व्योम)
अणु
	orion_spi_init(SPI_PHYS_BASE);
पूर्ण


/*****************************************************************************
 * UART0
 ****************************************************************************/
व्योम __init orion5x_uart0_init(व्योम)
अणु
	orion_uart0_init(UART0_VIRT_BASE, UART0_PHYS_BASE,
			 IRQ_ORION5X_UART0, tclk);
पूर्ण

/*****************************************************************************
 * UART1
 ****************************************************************************/
व्योम __init orion5x_uart1_init(व्योम)
अणु
	orion_uart1_init(UART1_VIRT_BASE, UART1_PHYS_BASE,
			 IRQ_ORION5X_UART1, tclk);
पूर्ण

/*****************************************************************************
 * XOR engine
 ****************************************************************************/
व्योम __init orion5x_xor_init(व्योम)
अणु
	orion_xor0_init(ORION5X_XOR_PHYS_BASE,
			ORION5X_XOR_PHYS_BASE + 0x200,
			IRQ_ORION5X_XOR0, IRQ_ORION5X_XOR1);
पूर्ण

/*****************************************************************************
 * Cryptographic Engines and Security Accelerator (CESA)
 ****************************************************************************/
अटल व्योम __init orion5x_crypto_init(व्योम)
अणु
	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_SRAM_TARGET,
				    ORION_MBUS_SRAM_ATTR,
				    ORION5X_SRAM_PHYS_BASE,
				    ORION5X_SRAM_SIZE);
	orion_crypto_init(ORION5X_CRYPTO_PHYS_BASE, ORION5X_SRAM_PHYS_BASE,
			  SZ_8K, IRQ_ORION5X_CESA);
पूर्ण

/*****************************************************************************
 * Watchकरोg
 ****************************************************************************/
अटल काष्ठा resource orion_wdt_resource[] = अणु
		DEFINE_RES_MEM(TIMER_PHYS_BASE, 0x04),
		DEFINE_RES_MEM(RSTOUTn_MASK_PHYS, 0x04),
पूर्ण;

अटल काष्ठा platक्रमm_device orion_wdt_device = अणु
	.name		= "orion_wdt",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(orion_wdt_resource),
	.resource	= orion_wdt_resource,
पूर्ण;

अटल व्योम __init orion5x_wdt_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&orion_wdt_device);
पूर्ण


/*****************************************************************************
 * Time handling
 ****************************************************************************/
व्योम __init orion5x_init_early(व्योम)
अणु
	u32 rev, dev;
	स्थिर अक्षर *mbus_soc_name;

	orion_समय_set_base(TIMER_VIRT_BASE);

	/* Initialize the MBUS driver */
	orion5x_pcie_id(&dev, &rev);
	अगर (dev == MV88F5281_DEV_ID)
		mbus_soc_name = "marvell,orion5x-88f5281-mbus";
	अन्यथा अगर (dev == MV88F5182_DEV_ID)
		mbus_soc_name = "marvell,orion5x-88f5182-mbus";
	अन्यथा अगर (dev == MV88F5181_DEV_ID)
		mbus_soc_name = "marvell,orion5x-88f5181-mbus";
	अन्यथा अगर (dev == MV88F6183_DEV_ID)
		mbus_soc_name = "marvell,orion5x-88f6183-mbus";
	अन्यथा
		mbus_soc_name = शून्य;
	mvebu_mbus_init(mbus_soc_name, ORION5X_BRIDGE_WINS_BASE,
			ORION5X_BRIDGE_WINS_SZ,
			ORION5X_DDR_WINS_BASE, ORION5X_DDR_WINS_SZ);
पूर्ण

व्योम orion5x_setup_wins(व्योम)
अणु
	/*
	 * The PCIe winकरोws will no दीर्घer be अटलally allocated
	 * here once Orion5x is migrated to the pci-mvebu driver.
	 */
	mvebu_mbus_add_winकरोw_remap_by_id(ORION_MBUS_PCIE_IO_TARGET,
					  ORION_MBUS_PCIE_IO_ATTR,
					  ORION5X_PCIE_IO_PHYS_BASE,
					  ORION5X_PCIE_IO_SIZE,
					  ORION5X_PCIE_IO_BUS_BASE);
	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_PCIE_MEM_TARGET,
				    ORION_MBUS_PCIE_MEM_ATTR,
				    ORION5X_PCIE_MEM_PHYS_BASE,
				    ORION5X_PCIE_MEM_SIZE);
	mvebu_mbus_add_winकरोw_remap_by_id(ORION_MBUS_PCI_IO_TARGET,
					  ORION_MBUS_PCI_IO_ATTR,
					  ORION5X_PCI_IO_PHYS_BASE,
					  ORION5X_PCI_IO_SIZE,
					  ORION5X_PCI_IO_BUS_BASE);
	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_PCI_MEM_TARGET,
				    ORION_MBUS_PCI_MEM_ATTR,
				    ORION5X_PCI_MEM_PHYS_BASE,
				    ORION5X_PCI_MEM_SIZE);
पूर्ण

पूर्णांक orion5x_tclk;

अटल पूर्णांक __init orion5x_find_tclk(व्योम)
अणु
	u32 dev, rev;

	orion5x_pcie_id(&dev, &rev);
	अगर (dev == MV88F6183_DEV_ID &&
	    (पढ़ोl(MPP_RESET_SAMPLE) & 0x00000200) == 0)
		वापस 133333333;

	वापस 166666667;
पूर्ण

व्योम __init orion5x_समयr_init(व्योम)
अणु
	orion5x_tclk = orion5x_find_tclk();

	orion_समय_init(ORION5X_BRIDGE_VIRT_BASE, BRIDGE_INT_TIMER1_CLR,
			IRQ_ORION5X_BRIDGE, orion5x_tclk);
पूर्ण


/*****************************************************************************
 * General
 ****************************************************************************/
/*
 * Identअगरy device ID and rev from PCIe configuration header space '0'.
 */
व्योम __init orion5x_id(u32 *dev, u32 *rev, अक्षर **dev_name)
अणु
	orion5x_pcie_id(dev, rev);

	अगर (*dev == MV88F5281_DEV_ID) अणु
		अगर (*rev == MV88F5281_REV_D2) अणु
			*dev_name = "MV88F5281-D2";
		पूर्ण अन्यथा अगर (*rev == MV88F5281_REV_D1) अणु
			*dev_name = "MV88F5281-D1";
		पूर्ण अन्यथा अगर (*rev == MV88F5281_REV_D0) अणु
			*dev_name = "MV88F5281-D0";
		पूर्ण अन्यथा अणु
			*dev_name = "MV88F5281-Rev-Unsupported";
		पूर्ण
	पूर्ण अन्यथा अगर (*dev == MV88F5182_DEV_ID) अणु
		अगर (*rev == MV88F5182_REV_A2) अणु
			*dev_name = "MV88F5182-A2";
		पूर्ण अन्यथा अणु
			*dev_name = "MV88F5182-Rev-Unsupported";
		पूर्ण
	पूर्ण अन्यथा अगर (*dev == MV88F5181_DEV_ID) अणु
		अगर (*rev == MV88F5181_REV_B1) अणु
			*dev_name = "MV88F5181-Rev-B1";
		पूर्ण अन्यथा अगर (*rev == MV88F5181L_REV_A1) अणु
			*dev_name = "MV88F5181L-Rev-A1";
		पूर्ण अन्यथा अणु
			*dev_name = "MV88F5181(L)-Rev-Unsupported";
		पूर्ण
	पूर्ण अन्यथा अगर (*dev == MV88F6183_DEV_ID) अणु
		अगर (*rev == MV88F6183_REV_B0) अणु
			*dev_name = "MV88F6183-Rev-B0";
		पूर्ण अन्यथा अणु
			*dev_name = "MV88F6183-Rev-Unsupported";
		पूर्ण
	पूर्ण अन्यथा अणु
		*dev_name = "Device-Unknown";
	पूर्ण
पूर्ण

व्योम __init orion5x_init(व्योम)
अणु
	अक्षर *dev_name;
	u32 dev, rev;

	orion5x_id(&dev, &rev, &dev_name);
	prपूर्णांकk(KERN_INFO "Orion ID: %s. TCLK=%d.\n", dev_name, orion5x_tclk);

	/*
	 * Setup Orion address map
	 */
	orion5x_setup_wins();

	/* Setup root of clk tree */
	clk_init();

	/*
	 * Don't issue "Wait for Interrupt" inकाष्ठाion अगर we are
	 * running on D0 5281 silicon.
	 */
	अगर (dev == MV88F5281_DEV_ID && rev == MV88F5281_REV_D0) अणु
		prपूर्णांकk(KERN_INFO "Orion: Applying 5281 D0 WFI workaround.\n");
		cpu_idle_poll_ctrl(true);
	पूर्ण

	/*
	 * The 5082/5181l/5182/6082/6082l/6183 have crypto
	 * जबतक 5180n/5181/5281 करोn't have crypto.
	 */
	अगर ((dev == MV88F5181_DEV_ID && rev >= MV88F5181L_REV_A0) ||
	    dev == MV88F5182_DEV_ID || dev == MV88F6183_DEV_ID)
		orion5x_crypto_init();

	/*
	 * Register watchकरोg driver
	 */
	orion5x_wdt_init();
पूर्ण

व्योम orion5x_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	/*
	 * Enable and issue soft reset
	 */
	orion5x_setbits(RSTOUTn_MASK, (1 << 2));
	orion5x_setbits(CPU_SOFT_RESET, 1);
	mdelay(200);
	orion5x_clrbits(CPU_SOFT_RESET, 1);
पूर्ण

/*
 * Many orion-based प्रणालीs have buggy bootloader implementations.
 * This is a common fixup क्रम bogus memory tags.
 */
व्योम __init tag_fixup_mem32(काष्ठा tag *t, अक्षर **from)
अणु
	क्रम (; t->hdr.size; t = tag_next(t))
		अगर (t->hdr.tag == ATAG_MEM &&
		    (!t->u.mem.size || t->u.mem.size & ~PAGE_MASK ||
		     t->u.mem.start & ~PAGE_MASK)) अणु
			prपूर्णांकk(KERN_WARNING
			       "Clearing invalid memory bank %dKB@0x%08x\n",
			       t->u.mem.size / 1024, t->u.mem.start);
			t->hdr.tag = 0;
		पूर्ण
पूर्ण
