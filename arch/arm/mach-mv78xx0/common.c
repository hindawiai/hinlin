<शैली गुरु>
/*
 * arch/arm/mach-mv78xx0/common.c
 *
 * Core functions क्रम Marvell MV78xx0 SoCs
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/ethtool.h>
#समावेश <यंत्र/hardware/cache-feroceon-l2.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <linux/platक्रमm_data/usb-ehci-orion.h>
#समावेश <linux/platक्रमm_data/mtd-orion_nand.h>
#समावेश <plat/समय.स>
#समावेश <plat/common.h>
#समावेश <plat/addr-map.h>
#समावेश "mv78xx0.h"
#समावेश "bridge-regs.h"
#समावेश "common.h"

अटल पूर्णांक get_tclk(व्योम);

/*****************************************************************************
 * Common bits
 ****************************************************************************/
पूर्णांक mv78xx0_core_index(व्योम)
अणु
	u32 extra;

	/*
	 * Read Extra Features रेजिस्टर.
	 */
	__यंत्र__("mrc p15, 1, %0, c15, c1, 0" : "=r" (extra));

	वापस !!(extra & 0x00004000);
पूर्ण

अटल पूर्णांक get_hclk(व्योम)
अणु
	पूर्णांक hclk;

	/*
	 * HCLK tick rate is configured by DEV_D[7:5] pins.
	 */
	चयन ((पढ़ोl(SAMPLE_AT_RESET_LOW) >> 5) & 7) अणु
	हाल 0:
		hclk = 166666667;
		अवरोध;
	हाल 1:
		hclk = 200000000;
		अवरोध;
	हाल 2:
		hclk = 266666667;
		अवरोध;
	हाल 3:
		hclk = 333333333;
		अवरोध;
	हाल 4:
		hclk = 400000000;
		अवरोध;
	शेष:
		panic("unknown HCLK PLL setting: %.8x\n",
			पढ़ोl(SAMPLE_AT_RESET_LOW));
	पूर्ण

	वापस hclk;
पूर्ण

अटल व्योम get_pclk_l2clk(पूर्णांक hclk, पूर्णांक core_index, पूर्णांक *pclk, पूर्णांक *l2clk)
अणु
	u32 cfg;

	/*
	 * Core #0 PCLK/L2CLK is configured by bits [13:8], core #1
	 * PCLK/L2CLK by bits [19:14].
	 */
	अगर (core_index == 0) अणु
		cfg = (पढ़ोl(SAMPLE_AT_RESET_LOW) >> 8) & 0x3f;
	पूर्ण अन्यथा अणु
		cfg = (पढ़ोl(SAMPLE_AT_RESET_LOW) >> 14) & 0x3f;
	पूर्ण

	/*
	 * Bits [11:8] ([17:14] क्रम core #1) configure the PCLK:HCLK
	 * ratio (1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6).
	 */
	*pclk = ((u64)hclk * (2 + (cfg & 0xf))) >> 1;

	/*
	 * Bits [13:12] ([19:18] क्रम core #1) configure the PCLK:L2CLK
	 * ratio (1, 2, 3).
	 */
	*l2clk = *pclk / (((cfg >> 4) & 3) + 1);
पूर्ण

अटल पूर्णांक get_tclk(व्योम)
अणु
	पूर्णांक tclk_freq;

	/*
	 * TCLK tick rate is configured by DEV_A[2:0] strap pins.
	 */
	चयन ((पढ़ोl(SAMPLE_AT_RESET_HIGH) >> 6) & 7) अणु
	हाल 1:
		tclk_freq = 166666667;
		अवरोध;
	हाल 3:
		tclk_freq = 200000000;
		अवरोध;
	शेष:
		panic("unknown TCLK PLL setting: %.8x\n",
			पढ़ोl(SAMPLE_AT_RESET_HIGH));
	पूर्ण

	वापस tclk_freq;
पूर्ण


/*****************************************************************************
 * I/O Address Mapping
 ****************************************************************************/
अटल काष्ठा map_desc mv78xx0_io_desc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ) MV78XX0_CORE_REGS_VIRT_BASE,
		.pfn		= 0,
		.length		= MV78XX0_CORE_REGS_SIZE,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ) MV78XX0_REGS_VIRT_BASE,
		.pfn		= __phys_to_pfn(MV78XX0_REGS_PHYS_BASE),
		.length		= MV78XX0_REGS_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

व्योम __init mv78xx0_map_io(व्योम)
अणु
	अचिन्हित दीर्घ phys;

	/*
	 * Map the right set of per-core रेजिस्टरs depending on
	 * which core we are running on.
	 */
	अगर (mv78xx0_core_index() == 0) अणु
		phys = MV78XX0_CORE0_REGS_PHYS_BASE;
	पूर्ण अन्यथा अणु
		phys = MV78XX0_CORE1_REGS_PHYS_BASE;
	पूर्ण
	mv78xx0_io_desc[0].pfn = __phys_to_pfn(phys);

	iotable_init(mv78xx0_io_desc, ARRAY_SIZE(mv78xx0_io_desc));
पूर्ण


/*****************************************************************************
 * CLK tree
 ****************************************************************************/
अटल काष्ठा clk *tclk;

अटल व्योम __init clk_init(व्योम)
अणु
	tclk = clk_रेजिस्टर_fixed_rate(शून्य, "tclk", शून्य, 0, get_tclk());

	orion_clkdev_init(tclk);
पूर्ण

/*****************************************************************************
 * EHCI
 ****************************************************************************/
व्योम __init mv78xx0_ehci0_init(व्योम)
अणु
	orion_ehci_init(USB0_PHYS_BASE, IRQ_MV78XX0_USB_0, EHCI_PHY_NA);
पूर्ण


/*****************************************************************************
 * EHCI1
 ****************************************************************************/
व्योम __init mv78xx0_ehci1_init(व्योम)
अणु
	orion_ehci_1_init(USB1_PHYS_BASE, IRQ_MV78XX0_USB_1);
पूर्ण


/*****************************************************************************
 * EHCI2
 ****************************************************************************/
व्योम __init mv78xx0_ehci2_init(व्योम)
अणु
	orion_ehci_2_init(USB2_PHYS_BASE, IRQ_MV78XX0_USB_2);
पूर्ण


/*****************************************************************************
 * GE00
 ****************************************************************************/
व्योम __init mv78xx0_ge00_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data)
अणु
	orion_ge00_init(eth_data,
			GE00_PHYS_BASE, IRQ_MV78XX0_GE00_SUM,
			IRQ_MV78XX0_GE_ERR,
			MV643XX_TX_CSUM_DEFAULT_LIMIT);
पूर्ण


/*****************************************************************************
 * GE01
 ****************************************************************************/
व्योम __init mv78xx0_ge01_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data)
अणु
	orion_ge01_init(eth_data,
			GE01_PHYS_BASE, IRQ_MV78XX0_GE01_SUM,
			MV643XX_TX_CSUM_DEFAULT_LIMIT);
पूर्ण


/*****************************************************************************
 * GE10
 ****************************************************************************/
व्योम __init mv78xx0_ge10_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data)
अणु
	u32 dev, rev;

	/*
	 * On the Z0, ge10 and ge11 are पूर्णांकernally connected back
	 * to back, and not brought out.
	 */
	mv78xx0_pcie_id(&dev, &rev);
	अगर (dev == MV78X00_Z0_DEV_ID) अणु
		eth_data->phy_addr = MV643XX_ETH_PHY_NONE;
		eth_data->speed = SPEED_1000;
		eth_data->duplex = DUPLEX_FULL;
	पूर्ण

	orion_ge10_init(eth_data, GE10_PHYS_BASE, IRQ_MV78XX0_GE10_SUM);
पूर्ण


/*****************************************************************************
 * GE11
 ****************************************************************************/
व्योम __init mv78xx0_ge11_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data)
अणु
	u32 dev, rev;

	/*
	 * On the Z0, ge10 and ge11 are पूर्णांकernally connected back
	 * to back, and not brought out.
	 */
	mv78xx0_pcie_id(&dev, &rev);
	अगर (dev == MV78X00_Z0_DEV_ID) अणु
		eth_data->phy_addr = MV643XX_ETH_PHY_NONE;
		eth_data->speed = SPEED_1000;
		eth_data->duplex = DUPLEX_FULL;
	पूर्ण

	orion_ge11_init(eth_data, GE11_PHYS_BASE, IRQ_MV78XX0_GE11_SUM);
पूर्ण

/*****************************************************************************
 * I2C
 ****************************************************************************/
व्योम __init mv78xx0_i2c_init(व्योम)
अणु
	orion_i2c_init(I2C_0_PHYS_BASE, IRQ_MV78XX0_I2C_0, 8);
	orion_i2c_1_init(I2C_1_PHYS_BASE, IRQ_MV78XX0_I2C_1, 8);
पूर्ण

/*****************************************************************************
 * SATA
 ****************************************************************************/
व्योम __init mv78xx0_sata_init(काष्ठा mv_sata_platक्रमm_data *sata_data)
अणु
	orion_sata_init(sata_data, SATA_PHYS_BASE, IRQ_MV78XX0_SATA);
पूर्ण


/*****************************************************************************
 * UART0
 ****************************************************************************/
व्योम __init mv78xx0_uart0_init(व्योम)
अणु
	orion_uart0_init(UART0_VIRT_BASE, UART0_PHYS_BASE,
			 IRQ_MV78XX0_UART_0, tclk);
पूर्ण


/*****************************************************************************
 * UART1
 ****************************************************************************/
व्योम __init mv78xx0_uart1_init(व्योम)
अणु
	orion_uart1_init(UART1_VIRT_BASE, UART1_PHYS_BASE,
			 IRQ_MV78XX0_UART_1, tclk);
पूर्ण


/*****************************************************************************
 * UART2
 ****************************************************************************/
व्योम __init mv78xx0_uart2_init(व्योम)
अणु
	orion_uart2_init(UART2_VIRT_BASE, UART2_PHYS_BASE,
			 IRQ_MV78XX0_UART_2, tclk);
पूर्ण

/*****************************************************************************
 * UART3
 ****************************************************************************/
व्योम __init mv78xx0_uart3_init(व्योम)
अणु
	orion_uart3_init(UART3_VIRT_BASE, UART3_PHYS_BASE,
			 IRQ_MV78XX0_UART_3, tclk);
पूर्ण

/*****************************************************************************
 * Time handling
 ****************************************************************************/
व्योम __init mv78xx0_init_early(व्योम)
अणु
	orion_समय_set_base(TIMER_VIRT_BASE);
	अगर (mv78xx0_core_index() == 0)
		mvebu_mbus_init("marvell,mv78xx0-mbus",
				BRIDGE_WINS_CPU0_BASE, BRIDGE_WINS_SZ,
				DDR_WINDOW_CPU0_BASE, DDR_WINDOW_CPU_SZ);
	अन्यथा
		mvebu_mbus_init("marvell,mv78xx0-mbus",
				BRIDGE_WINS_CPU1_BASE, BRIDGE_WINS_SZ,
				DDR_WINDOW_CPU1_BASE, DDR_WINDOW_CPU_SZ);
पूर्ण

व्योम __ref mv78xx0_समयr_init(व्योम)
अणु
	orion_समय_init(BRIDGE_VIRT_BASE, BRIDGE_INT_TIMER1_CLR,
			IRQ_MV78XX0_TIMER_1, get_tclk());
पूर्ण


/*****************************************************************************
 * General
 ****************************************************************************/
अटल अक्षर * __init mv78xx0_id(व्योम)
अणु
	u32 dev, rev;

	mv78xx0_pcie_id(&dev, &rev);

	अगर (dev == MV78X00_Z0_DEV_ID) अणु
		अगर (rev == MV78X00_REV_Z0)
			वापस "MV78X00-Z0";
		अन्यथा
			वापस "MV78X00-Rev-Unsupported";
	पूर्ण अन्यथा अगर (dev == MV78100_DEV_ID) अणु
		अगर (rev == MV78100_REV_A0)
			वापस "MV78100-A0";
		अन्यथा अगर (rev == MV78100_REV_A1)
			वापस "MV78100-A1";
		अन्यथा
			वापस "MV78100-Rev-Unsupported";
	पूर्ण अन्यथा अगर (dev == MV78200_DEV_ID) अणु
		अगर (rev == MV78100_REV_A0)
			वापस "MV78200-A0";
		अन्यथा
			वापस "MV78200-Rev-Unsupported";
	पूर्ण अन्यथा अणु
		वापस "Device-Unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक __init is_l2_ग_लिखोthrough(व्योम)
अणु
	वापस !!(पढ़ोl(CPU_CONTROL) & L2_WRITETHROUGH);
पूर्ण

व्योम __init mv78xx0_init(व्योम)
अणु
	पूर्णांक core_index;
	पूर्णांक hclk;
	पूर्णांक pclk;
	पूर्णांक l2clk;

	core_index = mv78xx0_core_index();
	hclk = get_hclk();
	get_pclk_l2clk(hclk, core_index, &pclk, &l2clk);

	prपूर्णांकk(KERN_INFO "%s ", mv78xx0_id());
	prपूर्णांकk("core #%d, ", core_index);
	prपूर्णांकk("PCLK = %dMHz, ", (pclk + 499999) / 1000000);
	prपूर्णांकk("L2 = %dMHz, ", (l2clk + 499999) / 1000000);
	prपूर्णांकk("HCLK = %dMHz, ", (hclk + 499999) / 1000000);
	prपूर्णांकk("TCLK = %dMHz\n", (get_tclk() + 499999) / 1000000);

	अगर (IS_ENABLED(CONFIG_CACHE_FEROCEON_L2))
		feroceon_l2_init(is_l2_ग_लिखोthrough());

	/* Setup root of clk tree */
	clk_init();
पूर्ण

व्योम mv78xx0_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
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
