<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Buffalo Terastation Pro II/Live Board Setup
 *
 * Maपूर्णांकainer: Sylver Bruneau <sylver.bruneau@googlemail.com>
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/i2c.h>
#समावेश <linux/serial_reg.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश "common.h"
#समावेश "mpp.h"
#समावेश "orion5x.h"

/*****************************************************************************
 * Terastation Pro 2/Live Info
 ****************************************************************************/

/*
 * Terastation Pro 2 hardware :
 * - Marvell 88F5281-D0
 * - Marvell 88SX6042 SATA controller (PCI)
 * - Marvell 88E1118 Gigabit Ethernet PHY
 * - 256KB NOR flash
 * - 128MB of DDR RAM
 * - PCIe port (not equipped)
 */

/*
 * 256K NOR flash Device bus boot chip select
 */

#घोषणा TSP2_NOR_BOOT_BASE	0xf4000000
#घोषणा TSP2_NOR_BOOT_SIZE	SZ_256K

/*****************************************************************************
 * 256KB NOR Flash on BOOT Device
 ****************************************************************************/

अटल काष्ठा physmap_flash_data tsp2_nor_flash_data = अणु
	.width    = 1,
पूर्ण;

अटल काष्ठा resource tsp2_nor_flash_resource = अणु
	.flags = IORESOURCE_MEM,
	.start = TSP2_NOR_BOOT_BASE,
	.end   = TSP2_NOR_BOOT_BASE + TSP2_NOR_BOOT_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device tsp2_nor_flash = अणु
	.name          = "physmap-flash",
	.id            = 0,
	.dev           = अणु
		.platक्रमm_data	= &tsp2_nor_flash_data,
	पूर्ण,
	.num_resources = 1,
	.resource      = &tsp2_nor_flash_resource,
पूर्ण;

/*****************************************************************************
 * PCI
 ****************************************************************************/
#घोषणा TSP2_PCI_SLOT0_OFFS		7
#घोषणा TSP2_PCI_SLOT0_IRQ_PIN		11

अटल व्योम __init tsp2_pci_preinit(व्योम)
अणु
	पूर्णांक pin;

	/*
	 * Configure PCI GPIO IRQ pins
	 */
	pin = TSP2_PCI_SLOT0_IRQ_PIN;
	अगर (gpio_request(pin, "PCI Int1") == 0) अणु
		अगर (gpio_direction_input(pin) == 0) अणु
			irq_set_irq_type(gpio_to_irq(pin), IRQ_TYPE_LEVEL_LOW);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "tsp2_pci_preinit failed "
					"to set_irq_type pin %d\n", pin);
			gpio_मुक्त(pin);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "tsp2_pci_preinit failed to "
				"gpio_request %d\n", pin);
	पूर्ण
पूर्ण

अटल पूर्णांक __init tsp2_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
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
	अगर (slot == TSP2_PCI_SLOT0_OFFS)
		वापस gpio_to_irq(TSP2_PCI_SLOT0_IRQ_PIN);

	वापस -1;
पूर्ण

अटल काष्ठा hw_pci tsp2_pci __initdata = अणु
	.nr_controllers = 2,
	.preinit        = tsp2_pci_preinit,
	.setup          = orion5x_pci_sys_setup,
	.scan           = orion5x_pci_sys_scan_bus,
	.map_irq        = tsp2_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init tsp2_pci_init(व्योम)
अणु
	अगर (machine_is_terastation_pro2())
		pci_common_init(&tsp2_pci);

	वापस 0;
पूर्ण

subsys_initcall(tsp2_pci_init);

/*****************************************************************************
 * Ethernet
 ****************************************************************************/

अटल काष्ठा mv643xx_eth_platक्रमm_data tsp2_eth_data = अणु
	.phy_addr	= 0,
पूर्ण;

/*****************************************************************************
 * RTC 5C372a on I2C bus
 ****************************************************************************/

#घोषणा TSP2_RTC_GPIO	9

अटल काष्ठा i2c_board_info __initdata tsp2_i2c_rtc = अणु
	I2C_BOARD_INFO("rs5c372a", 0x32),
पूर्ण;

/*****************************************************************************
 * Terastation Pro II specअगरic घातer off method via UART1-attached
 * microcontroller
 ****************************************************************************/

#घोषणा UART1_REG(x)	(UART1_VIRT_BASE + ((UART_##x) << 2))

अटल पूर्णांक tsp2_miconपढ़ो(अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i;
	पूर्णांक समयout;

	क्रम (i = 0; i < count; i++) अणु
		समयout = 10;

		जबतक (!(पढ़ोl(UART1_REG(LSR)) & UART_LSR_DR)) अणु
			अगर (--समयout == 0)
				अवरोध;
			udelay(1000);
		पूर्ण

		अगर (समयout == 0)
			अवरोध;
		buf[i] = पढ़ोl(UART1_REG(RX));
	पूर्ण

	/* वापस पढ़ो bytes */
	वापस i;
पूर्ण

अटल पूर्णांक tsp2_miconग_लिखो(स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i = 0;

	जबतक (count--) अणु
		जबतक (!(पढ़ोl(UART1_REG(LSR)) & UART_LSR_THRE))
			barrier();
		ग_लिखोl(buf[i++], UART1_REG(TX));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tsp2_miconsend(स्थिर अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर checksum = 0;
	अचिन्हित अक्षर recv_buf[40];
	अचिन्हित अक्षर send_buf[40];
	अचिन्हित अक्षर correct_ack[3];
	पूर्णांक retry = 2;

	/* Generate checksum */
	क्रम (i = 0; i < count; i++)
		checksum -=  data[i];

	करो अणु
		/* Send data */
		tsp2_miconग_लिखो(data, count);

		/* send checksum */
		tsp2_miconग_लिखो(&checksum, 1);

		अगर (tsp2_miconपढ़ो(recv_buf, माप(recv_buf)) <= 3) अणु
			prपूर्णांकk(KERN_ERR ">%s: receive failed.\n", __func__);

			/* send preamble to clear the receive buffer */
			स_रखो(&send_buf, 0xff, माप(send_buf));
			tsp2_miconग_लिखो(send_buf, माप(send_buf));

			/* make dummy पढ़ोs */
			mdelay(100);
			tsp2_miconपढ़ो(recv_buf, माप(recv_buf));
		पूर्ण अन्यथा अणु
			/* Generate expected ack */
			correct_ack[0] = 0x01;
			correct_ack[1] = data[1];
			correct_ack[2] = 0x00;

			/* checksum Check */
			अगर ((recv_buf[0] + recv_buf[1] + recv_buf[2] +
			     recv_buf[3]) & 0xFF) अणु
				prपूर्णांकk(KERN_ERR ">%s: Checksum Error : "
					"Received data[%02x, %02x, %02x, %02x]"
					"\n", __func__, recv_buf[0],
					recv_buf[1], recv_buf[2], recv_buf[3]);
			पूर्ण अन्यथा अणु
				/* Check Received Data */
				अगर (correct_ack[0] == recv_buf[0] &&
				    correct_ack[1] == recv_buf[1] &&
				    correct_ack[2] == recv_buf[2]) अणु
					/* Interval क्रम next command */
					mdelay(10);

					/* Receive ACK */
					वापस 0;
				पूर्ण
			पूर्ण
			/* Received NAK or illegal Data */
			prपूर्णांकk(KERN_ERR ">%s: Error : NAK or Illegal Data "
					"Received\n", __func__);
		पूर्ण
	पूर्ण जबतक (retry--);

	/* Interval क्रम next command */
	mdelay(10);

	वापस -1;
पूर्ण

अटल व्योम tsp2_घातer_off(व्योम)
अणु
	स्थिर अचिन्हित अक्षर watchकरोgसमाप्त[]	= अणु0x01, 0x35, 0x00पूर्ण;
	स्थिर अचिन्हित अक्षर shutकरोwnरुको[]	= अणु0x00, 0x0cपूर्ण;
	स्थिर अचिन्हित अक्षर घातeroff[]		= अणु0x00, 0x06पूर्ण;
	/* 38400 baud भागisor */
	स्थिर अचिन्हित भागisor = ((orion5x_tclk + (8 * 38400)) / (16 * 38400));

	pr_info("%s: triggering power-off...\n", __func__);

	/* hijack uart1 and reset पूर्णांकo sane state (38400,8n1,even parity) */
	ग_लिखोl(0x83, UART1_REG(LCR));
	ग_लिखोl(भागisor & 0xff, UART1_REG(DLL));
	ग_लिखोl((भागisor >> 8) & 0xff, UART1_REG(DLM));
	ग_लिखोl(0x1b, UART1_REG(LCR));
	ग_लिखोl(0x00, UART1_REG(IER));
	ग_लिखोl(0x07, UART1_REG(FCR));
	ग_लिखोl(0x00, UART1_REG(MCR));

	/* Send the commands to shutकरोwn the Terastation Pro II */
	tsp2_miconsend(watchकरोgसमाप्त, माप(watchकरोgसमाप्त)) ;
	tsp2_miconsend(shutकरोwnरुको, माप(shutकरोwnरुको)) ;
	tsp2_miconsend(घातeroff, माप(घातeroff));
पूर्ण

/*****************************************************************************
 * General Setup
 ****************************************************************************/
अटल अचिन्हित पूर्णांक tsp2_mpp_modes[] __initdata = अणु
	MPP0_PCIE_RST_OUTn,
	MPP1_UNUSED,
	MPP2_UNUSED,
	MPP3_UNUSED,
	MPP4_न_अंकD,		/* BOOT न_अंकD Flash REn */
	MPP5_न_अंकD,		/* BOOT न_अंकD Flash WEn */
	MPP6_न_अंकD,		/* BOOT न_अंकD Flash HREn[0] */
	MPP7_न_अंकD,		/* BOOT न_अंकD Flash WEn[0] */
	MPP8_GPIO,		/* MICON पूर्णांक */
	MPP9_GPIO,		/* RTC पूर्णांक */
	MPP10_UNUSED,
	MPP11_GPIO,		/* PCI Int A */
	MPP12_UNUSED,
	MPP13_GPIO,		/* UPS on UART0 enable */
	MPP14_GPIO,		/* UPS low battery detection */
	MPP15_UNUSED,
	MPP16_UART,		/* UART1 RXD */
	MPP17_UART,		/* UART1 TXD */
	MPP18_UART,		/* UART1 CTSn */
	MPP19_UART,		/* UART1 RTSn */
	0,
पूर्ण;

अटल व्योम __init tsp2_init(व्योम)
अणु
	/*
	 * Setup basic Orion functions. Need to be called early.
	 */
	orion5x_init();

	orion5x_mpp_conf(tsp2_mpp_modes);

	/*
	 * Configure peripherals.
	 */
	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    TSP2_NOR_BOOT_BASE,
				    TSP2_NOR_BOOT_SIZE);
	platक्रमm_device_रेजिस्टर(&tsp2_nor_flash);

	orion5x_ehci0_init();
	orion5x_eth_init(&tsp2_eth_data);
	orion5x_i2c_init();
	orion5x_uart0_init();
	orion5x_uart1_init();

	/* Get RTC IRQ and रेजिस्टर the chip */
	अगर (gpio_request(TSP2_RTC_GPIO, "rtc") == 0) अणु
		अगर (gpio_direction_input(TSP2_RTC_GPIO) == 0)
			tsp2_i2c_rtc.irq = gpio_to_irq(TSP2_RTC_GPIO);
		अन्यथा
			gpio_मुक्त(TSP2_RTC_GPIO);
	पूर्ण
	अगर (tsp2_i2c_rtc.irq == 0)
		pr_warn("tsp2_init: failed to get RTC IRQ\n");
	i2c_रेजिस्टर_board_info(0, &tsp2_i2c_rtc, 1);

	/* रेजिस्टर Terastation Pro II specअगरic घातer-off method */
	pm_घातer_off = tsp2_घातer_off;
पूर्ण

MACHINE_START(TERASTATION_PRO2, "Buffalo Terastation Pro II/Live")
	/* Maपूर्णांकainer:  Sylver Bruneau <sylver.bruneau@googlemail.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= tsp2_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
