<शैली गुरु>
/*
 * arch/arm/mach-करोve/common.c
 *
 * Core functions क्रम Marvell Dove 88AP510 System On Chip
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_data/dma-mv_xor.h>
#समावेश <linux/platक्रमm_data/usb-ehci-orion.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/करोve/pmu.h>
#समावेश <यंत्र/hardware/cache-tauros2.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <plat/common.h>
#समावेश <plat/irq.h>
#समावेश <plat/समय.स>
#समावेश "bridge-regs.h"
#समावेश "pm.h"
#समावेश "common.h"

/* These can go away once Dove uses the mvebu-mbus DT binding */
#घोषणा DOVE_MBUS_PCIE0_MEM_TARGET    0x4
#घोषणा DOVE_MBUS_PCIE0_MEM_ATTR      0xe8
#घोषणा DOVE_MBUS_PCIE0_IO_TARGET     0x4
#घोषणा DOVE_MBUS_PCIE0_IO_ATTR       0xe0
#घोषणा DOVE_MBUS_PCIE1_MEM_TARGET    0x8
#घोषणा DOVE_MBUS_PCIE1_MEM_ATTR      0xe8
#घोषणा DOVE_MBUS_PCIE1_IO_TARGET     0x8
#घोषणा DOVE_MBUS_PCIE1_IO_ATTR       0xe0
#घोषणा DOVE_MBUS_CESA_TARGET         0x3
#घोषणा DOVE_MBUS_CESA_ATTR           0x1
#घोषणा DOVE_MBUS_BOOTROM_TARGET      0x1
#घोषणा DOVE_MBUS_BOOTROM_ATTR        0xfd
#घोषणा DOVE_MBUS_SCRATCHPAD_TARGET   0xd
#घोषणा DOVE_MBUS_SCRATCHPAD_ATTR     0x0

/*****************************************************************************
 * I/O Address Mapping
 ****************************************************************************/
अटल काष्ठा map_desc __maybe_unused करोve_io_desc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ) DOVE_SB_REGS_VIRT_BASE,
		.pfn		= __phys_to_pfn(DOVE_SB_REGS_PHYS_BASE),
		.length		= DOVE_SB_REGS_SIZE,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ) DOVE_NB_REGS_VIRT_BASE,
		.pfn		= __phys_to_pfn(DOVE_NB_REGS_PHYS_BASE),
		.length		= DOVE_NB_REGS_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

व्योम __init करोve_map_io(व्योम)
अणु
	iotable_init(करोve_io_desc, ARRAY_SIZE(करोve_io_desc));
पूर्ण

/*****************************************************************************
 * CLK tree
 ****************************************************************************/
अटल पूर्णांक करोve_tclk;

अटल DEFINE_SPINLOCK(gating_lock);
अटल काष्ठा clk *tclk;

अटल काष्ठा clk __init *करोve_रेजिस्टर_gate(स्थिर अक्षर *name,
					     स्थिर अक्षर *parent, u8 bit_idx)
अणु
	वापस clk_रेजिस्टर_gate(शून्य, name, parent, 0,
				 (व्योम __iomem *)CLOCK_GATING_CONTROL,
				 bit_idx, 0, &gating_lock);
पूर्ण

अटल व्योम __init करोve_clk_init(व्योम)
अणु
	काष्ठा clk *usb0, *usb1, *sata, *pex0, *pex1, *sdio0, *sdio1;
	काष्ठा clk *nand, *camera, *i2s0, *i2s1, *crypto, *ac97, *pdma;
	काष्ठा clk *xor0, *xor1, *ge, *gephy;

	tclk = clk_रेजिस्टर_fixed_rate(शून्य, "tclk", शून्य, 0, करोve_tclk);

	usb0 = करोve_रेजिस्टर_gate("usb0", "tclk", CLOCK_GATING_BIT_USB0);
	usb1 = करोve_रेजिस्टर_gate("usb1", "tclk", CLOCK_GATING_BIT_USB1);
	sata = करोve_रेजिस्टर_gate("sata", "tclk", CLOCK_GATING_BIT_SATA);
	pex0 = करोve_रेजिस्टर_gate("pex0", "tclk", CLOCK_GATING_BIT_PCIE0);
	pex1 = करोve_रेजिस्टर_gate("pex1", "tclk", CLOCK_GATING_BIT_PCIE1);
	sdio0 = करोve_रेजिस्टर_gate("sdio0", "tclk", CLOCK_GATING_BIT_SDIO0);
	sdio1 = करोve_रेजिस्टर_gate("sdio1", "tclk", CLOCK_GATING_BIT_SDIO1);
	nand = करोve_रेजिस्टर_gate("nand", "tclk", CLOCK_GATING_BIT_न_अंकD);
	camera = करोve_रेजिस्टर_gate("camera", "tclk", CLOCK_GATING_BIT_CAMERA);
	i2s0 = करोve_रेजिस्टर_gate("i2s0", "tclk", CLOCK_GATING_BIT_I2S0);
	i2s1 = करोve_रेजिस्टर_gate("i2s1", "tclk", CLOCK_GATING_BIT_I2S1);
	crypto = करोve_रेजिस्टर_gate("crypto", "tclk", CLOCK_GATING_BIT_CRYPTO);
	ac97 = करोve_रेजिस्टर_gate("ac97", "tclk", CLOCK_GATING_BIT_AC97);
	pdma = करोve_रेजिस्टर_gate("pdma", "tclk", CLOCK_GATING_BIT_PDMA);
	xor0 = करोve_रेजिस्टर_gate("xor0", "tclk", CLOCK_GATING_BIT_XOR0);
	xor1 = करोve_रेजिस्टर_gate("xor1", "tclk", CLOCK_GATING_BIT_XOR1);
	gephy = करोve_रेजिस्टर_gate("gephy", "tclk", CLOCK_GATING_BIT_GIGA_PHY);
	ge = करोve_रेजिस्टर_gate("ge", "gephy", CLOCK_GATING_BIT_GBE);

	orion_clkdev_add(शून्य, "orion_spi.0", tclk);
	orion_clkdev_add(शून्य, "orion_spi.1", tclk);
	orion_clkdev_add(शून्य, "orion_wdt", tclk);
	orion_clkdev_add(शून्य, "mv64xxx_i2c.0", tclk);

	orion_clkdev_add(शून्य, "orion-ehci.0", usb0);
	orion_clkdev_add(शून्य, "orion-ehci.1", usb1);
	orion_clkdev_add(शून्य, "mv643xx_eth_port.0", ge);
	orion_clkdev_add(शून्य, "sata_mv.0", sata);
	orion_clkdev_add("0", "pcie", pex0);
	orion_clkdev_add("1", "pcie", pex1);
	orion_clkdev_add(शून्य, "sdhci-dove.0", sdio0);
	orion_clkdev_add(शून्य, "sdhci-dove.1", sdio1);
	orion_clkdev_add(शून्य, "orion_nand", nand);
	orion_clkdev_add(शून्य, "cafe1000-ccic.0", camera);
	orion_clkdev_add(शून्य, "mvebu-audio.0", i2s0);
	orion_clkdev_add(शून्य, "mvebu-audio.1", i2s1);
	orion_clkdev_add(शून्य, "mv_crypto", crypto);
	orion_clkdev_add(शून्य, "dove-ac97", ac97);
	orion_clkdev_add(शून्य, "dove-pdma", pdma);
	orion_clkdev_add(शून्य, MV_XOR_NAME ".0", xor0);
	orion_clkdev_add(शून्य, MV_XOR_NAME ".1", xor1);
पूर्ण

/*****************************************************************************
 * EHCI0
 ****************************************************************************/
व्योम __init करोve_ehci0_init(व्योम)
अणु
	orion_ehci_init(DOVE_USB0_PHYS_BASE, IRQ_DOVE_USB0, EHCI_PHY_NA);
पूर्ण

/*****************************************************************************
 * EHCI1
 ****************************************************************************/
व्योम __init करोve_ehci1_init(व्योम)
अणु
	orion_ehci_1_init(DOVE_USB1_PHYS_BASE, IRQ_DOVE_USB1);
पूर्ण

/*****************************************************************************
 * GE00
 ****************************************************************************/
व्योम __init करोve_ge00_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data)
अणु
	orion_ge00_init(eth_data, DOVE_GE00_PHYS_BASE,
			IRQ_DOVE_GE00_SUM, IRQ_DOVE_GE00_ERR,
			1600);
पूर्ण

/*****************************************************************************
 * SoC RTC
 ****************************************************************************/
अटल व्योम __init करोve_rtc_init(व्योम)
अणु
	orion_rtc_init(DOVE_RTC_PHYS_BASE, IRQ_DOVE_RTC);
पूर्ण

/*****************************************************************************
 * SATA
 ****************************************************************************/
व्योम __init करोve_sata_init(काष्ठा mv_sata_platक्रमm_data *sata_data)
अणु
	orion_sata_init(sata_data, DOVE_SATA_PHYS_BASE, IRQ_DOVE_SATA);

पूर्ण

/*****************************************************************************
 * UART0
 ****************************************************************************/
व्योम __init करोve_uart0_init(व्योम)
अणु
	orion_uart0_init(DOVE_UART0_VIRT_BASE, DOVE_UART0_PHYS_BASE,
			 IRQ_DOVE_UART_0, tclk);
पूर्ण

/*****************************************************************************
 * UART1
 ****************************************************************************/
व्योम __init करोve_uart1_init(व्योम)
अणु
	orion_uart1_init(DOVE_UART1_VIRT_BASE, DOVE_UART1_PHYS_BASE,
			 IRQ_DOVE_UART_1, tclk);
पूर्ण

/*****************************************************************************
 * UART2
 ****************************************************************************/
व्योम __init करोve_uart2_init(व्योम)
अणु
	orion_uart2_init(DOVE_UART2_VIRT_BASE, DOVE_UART2_PHYS_BASE,
			 IRQ_DOVE_UART_2, tclk);
पूर्ण

/*****************************************************************************
 * UART3
 ****************************************************************************/
व्योम __init करोve_uart3_init(व्योम)
अणु
	orion_uart3_init(DOVE_UART3_VIRT_BASE, DOVE_UART3_PHYS_BASE,
			 IRQ_DOVE_UART_3, tclk);
पूर्ण

/*****************************************************************************
 * SPI
 ****************************************************************************/
व्योम __init करोve_spi0_init(व्योम)
अणु
	orion_spi_init(DOVE_SPI0_PHYS_BASE);
पूर्ण

व्योम __init करोve_spi1_init(व्योम)
अणु
	orion_spi_1_init(DOVE_SPI1_PHYS_BASE);
पूर्ण

/*****************************************************************************
 * I2C
 ****************************************************************************/
व्योम __init करोve_i2c_init(व्योम)
अणु
	orion_i2c_init(DOVE_I2C_PHYS_BASE, IRQ_DOVE_I2C, 10);
पूर्ण

/*****************************************************************************
 * Time handling
 ****************************************************************************/
व्योम __init करोve_init_early(व्योम)
अणु
	orion_समय_set_base(TIMER_VIRT_BASE);
	mvebu_mbus_init("marvell,dove-mbus",
			BRIDGE_WINS_BASE, BRIDGE_WINS_SZ,
			DOVE_MC_WINS_BASE, DOVE_MC_WINS_SZ);
पूर्ण

अटल पूर्णांक __init करोve_find_tclk(व्योम)
अणु
	वापस 166666667;
पूर्ण

व्योम __init करोve_समयr_init(व्योम)
अणु
	करोve_tclk = करोve_find_tclk();
	orion_समय_init(BRIDGE_VIRT_BASE, BRIDGE_INT_TIMER1_CLR,
			IRQ_DOVE_BRIDGE, करोve_tclk);
पूर्ण

/*****************************************************************************
 * XOR 0
 ****************************************************************************/
अटल व्योम __init करोve_xor0_init(व्योम)
अणु
	orion_xor0_init(DOVE_XOR0_PHYS_BASE, DOVE_XOR0_HIGH_PHYS_BASE,
			IRQ_DOVE_XOR_00, IRQ_DOVE_XOR_01);
पूर्ण

/*****************************************************************************
 * XOR 1
 ****************************************************************************/
अटल व्योम __init करोve_xor1_init(व्योम)
अणु
	orion_xor1_init(DOVE_XOR1_PHYS_BASE, DOVE_XOR1_HIGH_PHYS_BASE,
			IRQ_DOVE_XOR_10, IRQ_DOVE_XOR_11);
पूर्ण

/*****************************************************************************
 * SDIO
 ****************************************************************************/
अटल u64 sdio_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा resource करोve_sdio0_resources[] = अणु
	अणु
		.start	= DOVE_SDIO0_PHYS_BASE,
		.end	= DOVE_SDIO0_PHYS_BASE + 0xff,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_DOVE_SDIO0,
		.end	= IRQ_DOVE_SDIO0,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device करोve_sdio0 = अणु
	.name		= "sdhci-dove",
	.id		= 0,
	.dev		= अणु
		.dma_mask		= &sdio_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= करोve_sdio0_resources,
	.num_resources	= ARRAY_SIZE(करोve_sdio0_resources),
पूर्ण;

व्योम __init करोve_sdio0_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&करोve_sdio0);
पूर्ण

अटल काष्ठा resource करोve_sdio1_resources[] = अणु
	अणु
		.start	= DOVE_SDIO1_PHYS_BASE,
		.end	= DOVE_SDIO1_PHYS_BASE + 0xff,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_DOVE_SDIO1,
		.end	= IRQ_DOVE_SDIO1,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device करोve_sdio1 = अणु
	.name		= "sdhci-dove",
	.id		= 1,
	.dev		= अणु
		.dma_mask		= &sdio_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= करोve_sdio1_resources,
	.num_resources	= ARRAY_SIZE(करोve_sdio1_resources),
पूर्ण;

व्योम __init करोve_sdio1_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&करोve_sdio1);
पूर्ण

व्योम __init करोve_setup_cpu_wins(व्योम)
अणु
	/*
	 * The PCIe winकरोws will no दीर्घer be अटलally allocated
	 * here once Dove is migrated to the pci-mvebu driver. The
	 * non-PCIe winकरोws will no दीर्घer be created here once Dove
	 * fully moves to DT.
	 */
	mvebu_mbus_add_winकरोw_remap_by_id(DOVE_MBUS_PCIE0_IO_TARGET,
					  DOVE_MBUS_PCIE0_IO_ATTR,
					  DOVE_PCIE0_IO_PHYS_BASE,
					  DOVE_PCIE0_IO_SIZE,
					  DOVE_PCIE0_IO_BUS_BASE);
	mvebu_mbus_add_winकरोw_remap_by_id(DOVE_MBUS_PCIE1_IO_TARGET,
					  DOVE_MBUS_PCIE1_IO_ATTR,
					  DOVE_PCIE1_IO_PHYS_BASE,
					  DOVE_PCIE1_IO_SIZE,
					  DOVE_PCIE1_IO_BUS_BASE);
	mvebu_mbus_add_winकरोw_by_id(DOVE_MBUS_PCIE0_MEM_TARGET,
				    DOVE_MBUS_PCIE0_MEM_ATTR,
				    DOVE_PCIE0_MEM_PHYS_BASE,
				    DOVE_PCIE0_MEM_SIZE);
	mvebu_mbus_add_winकरोw_by_id(DOVE_MBUS_PCIE1_MEM_TARGET,
				    DOVE_MBUS_PCIE1_MEM_ATTR,
				    DOVE_PCIE1_MEM_PHYS_BASE,
				    DOVE_PCIE1_MEM_SIZE);
	mvebu_mbus_add_winकरोw_by_id(DOVE_MBUS_CESA_TARGET,
				    DOVE_MBUS_CESA_ATTR,
				    DOVE_CESA_PHYS_BASE,
				    DOVE_CESA_SIZE);
	mvebu_mbus_add_winकरोw_by_id(DOVE_MBUS_BOOTROM_TARGET,
				    DOVE_MBUS_BOOTROM_ATTR,
				    DOVE_BOOTROM_PHYS_BASE,
				    DOVE_BOOTROM_SIZE);
	mvebu_mbus_add_winकरोw_by_id(DOVE_MBUS_SCRATCHPAD_TARGET,
				    DOVE_MBUS_SCRATCHPAD_ATTR,
				    DOVE_SCRATCHPAD_PHYS_BASE,
				    DOVE_SCRATCHPAD_SIZE);
पूर्ण

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

अटल व्योम __init __maybe_unused orion_wdt_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&orion_wdt_device);
पूर्ण

अटल स्थिर काष्ठा करोve_pmu_करोमुख्य_initdata pmu_करोमुख्यs[] __initस्थिर = अणु
	अणु
		.pwr_mask = PMU_PWR_VPU_PWR_DWN_MASK,
		.rst_mask = PMU_SW_RST_VIDEO_MASK,
		.iso_mask = PMU_ISO_VIDEO_MASK,
		.name = "vpu-domain",
	पूर्ण, अणु
		.pwr_mask = PMU_PWR_GPU_PWR_DWN_MASK,
		.rst_mask = PMU_SW_RST_GPU_MASK,
		.iso_mask = PMU_ISO_GPU_MASK,
		.name = "gpu-domain",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा करोve_pmu_initdata pmu_data __initस्थिर = अणु
	.pmc_base = DOVE_PMU_VIRT_BASE,
	.pmu_base = DOVE_PMU_VIRT_BASE + 0x8000,
	.irq = IRQ_DOVE_PMU,
	.irq_करोमुख्य_start = IRQ_DOVE_PMU_START,
	.करोमुख्यs = pmu_करोमुख्यs,
पूर्ण;

व्योम __init करोve_init(व्योम)
अणु
	pr_info("Dove 88AP510 SoC, TCLK = %d MHz.\n",
		(करोve_tclk + 499999) / 1000000);

#अगर_घोषित CONFIG_CACHE_TAUROS2
	tauros2_init(0);
#पूर्ण_अगर
	करोve_setup_cpu_wins();

	/* Setup root of clk tree */
	करोve_clk_init();

	/* पूर्णांकernal devices that every board has */
	करोve_init_pmu_legacy(&pmu_data);
	करोve_rtc_init();
	करोve_xor0_init();
	करोve_xor1_init();
पूर्ण

व्योम करोve_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	/*
	 * Enable soft reset to निश्चित RSTOUTn.
	 */
	ग_लिखोl(SOFT_RESET_OUT_EN, RSTOUTn_MASK);

	/*
	 * Assert soft reset.
	 */
	ग_लिखोl(SOFT_RESET, SYSTEM_SOFT_RESET);

	जबतक (1)
		;
पूर्ण
