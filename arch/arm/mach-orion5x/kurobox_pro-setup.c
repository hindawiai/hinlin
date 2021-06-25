<शैली गुरु>
/*
 * arch/arm/mach-orion5x/kurobox_pro-setup.c
 *
 * Maपूर्णांकainer: Ronen Shitrit <rshitrit@marvell.com>
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
#समावेश <linux/delay.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/i2c.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <linux/platक्रमm_data/mtd-orion_nand.h>
#समावेश "common.h"
#समावेश "mpp.h"
#समावेश "orion5x.h"

/*****************************************************************************
 * KUROBOX-PRO Info
 ****************************************************************************/

/*
 * 256K NOR flash Device bus boot chip select
 */

#घोषणा KUROBOX_PRO_NOR_BOOT_BASE	0xf4000000
#घोषणा KUROBOX_PRO_NOR_BOOT_SIZE	SZ_256K

/*
 * 256M न_अंकD flash on Device bus chip select 1
 */

#घोषणा KUROBOX_PRO_न_अंकD_BASE		0xfc000000
#घोषणा KUROBOX_PRO_न_अंकD_SIZE		SZ_2M

/*****************************************************************************
 * 256MB न_अंकD Flash on Device bus CS0
 ****************************************************************************/

अटल काष्ठा mtd_partition kurobox_pro_nand_parts[] = अणु
	अणु
		.name	= "uImage",
		.offset	= 0,
		.size	= SZ_4M,
	पूर्ण, अणु
		.name	= "rootfs",
		.offset	= SZ_4M,
		.size	= SZ_64M,
	पूर्ण, अणु
		.name	= "extra",
		.offset	= SZ_4M + SZ_64M,
		.size	= SZ_256M - (SZ_4M + SZ_64M),
	पूर्ण,
पूर्ण;

अटल काष्ठा resource kurobox_pro_nand_resource = अणु
	.flags		= IORESOURCE_MEM,
	.start		= KUROBOX_PRO_न_अंकD_BASE,
	.end		= KUROBOX_PRO_न_अंकD_BASE + KUROBOX_PRO_न_अंकD_SIZE - 1,
पूर्ण;

अटल काष्ठा orion_nand_data kurobox_pro_nand_data = अणु
	.parts		= kurobox_pro_nand_parts,
	.nr_parts	= ARRAY_SIZE(kurobox_pro_nand_parts),
	.cle		= 0,
	.ale		= 1,
	.width		= 8,
पूर्ण;

अटल काष्ठा platक्रमm_device kurobox_pro_nand_flash = अणु
	.name		= "orion_nand",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &kurobox_pro_nand_data,
	पूर्ण,
	.resource	= &kurobox_pro_nand_resource,
	.num_resources	= 1,
पूर्ण;

/*****************************************************************************
 * 256KB NOR Flash on BOOT Device
 ****************************************************************************/

अटल काष्ठा physmap_flash_data kurobox_pro_nor_flash_data = अणु
	.width		= 1,
पूर्ण;

अटल काष्ठा resource kurobox_pro_nor_flash_resource = अणु
	.flags			= IORESOURCE_MEM,
	.start			= KUROBOX_PRO_NOR_BOOT_BASE,
	.end			= KUROBOX_PRO_NOR_BOOT_BASE + KUROBOX_PRO_NOR_BOOT_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device kurobox_pro_nor_flash = अणु
	.name			= "physmap-flash",
	.id			= 0,
	.dev		= अणु
		.platक्रमm_data	= &kurobox_pro_nor_flash_data,
	पूर्ण,
	.num_resources		= 1,
	.resource		= &kurobox_pro_nor_flash_resource,
पूर्ण;

/*****************************************************************************
 * PCI
 ****************************************************************************/

अटल पूर्णांक __init kurobox_pro_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot,
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
	 * PCI isn't used on the Kuro
	 */
	वापस -1;
पूर्ण

अटल काष्ठा hw_pci kurobox_pro_pci __initdata = अणु
	.nr_controllers	= 2,
	.setup		= orion5x_pci_sys_setup,
	.scan		= orion5x_pci_sys_scan_bus,
	.map_irq	= kurobox_pro_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init kurobox_pro_pci_init(व्योम)
अणु
	अगर (machine_is_kurobox_pro()) अणु
		orion5x_pci_disable();
		pci_common_init(&kurobox_pro_pci);
	पूर्ण

	वापस 0;
पूर्ण

subsys_initcall(kurobox_pro_pci_init);

/*****************************************************************************
 * Ethernet
 ****************************************************************************/

अटल काष्ठा mv643xx_eth_platक्रमm_data kurobox_pro_eth_data = अणु
	.phy_addr	= MV643XX_ETH_PHY_ADDR(8),
पूर्ण;

/*****************************************************************************
 * RTC 5C372a on I2C bus
 ****************************************************************************/
अटल काष्ठा i2c_board_info __initdata kurobox_pro_i2c_rtc = अणु
	I2C_BOARD_INFO("rs5c372a", 0x32),
पूर्ण;

/*****************************************************************************
 * SATA
 ****************************************************************************/
अटल काष्ठा mv_sata_platक्रमm_data kurobox_pro_sata_data = अणु
	.n_ports	= 2,
पूर्ण;

/*****************************************************************************
 * Kurobox Pro specअगरic घातer off method via UART1-attached microcontroller
 ****************************************************************************/

#घोषणा UART1_REG(x)	(UART1_VIRT_BASE + ((UART_##x) << 2))

अटल पूर्णांक kurobox_pro_miconपढ़ो(अचिन्हित अक्षर *buf, पूर्णांक count)
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

अटल पूर्णांक kurobox_pro_miconग_लिखो(स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i = 0;

	जबतक (count--) अणु
		जबतक (!(पढ़ोl(UART1_REG(LSR)) & UART_LSR_THRE))
			barrier();
		ग_लिखोl(buf[i++], UART1_REG(TX));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kurobox_pro_miconsend(स्थिर अचिन्हित अक्षर *data, पूर्णांक count)
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
		kurobox_pro_miconग_लिखो(data, count);

		/* send checksum */
		kurobox_pro_miconग_लिखो(&checksum, 1);

		अगर (kurobox_pro_miconपढ़ो(recv_buf, माप(recv_buf)) <= 3) अणु
			prपूर्णांकk(KERN_ERR ">%s: receive failed.\n", __func__);

			/* send preamble to clear the receive buffer */
			स_रखो(&send_buf, 0xff, माप(send_buf));
			kurobox_pro_miconग_लिखो(send_buf, माप(send_buf));

			/* make dummy पढ़ोs */
			mdelay(100);
			kurobox_pro_miconपढ़ो(recv_buf, माप(recv_buf));
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

अटल व्योम kurobox_pro_घातer_off(व्योम)
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

	/* Send the commands to shutकरोwn the Kurobox Pro */
	kurobox_pro_miconsend(watchकरोgसमाप्त, माप(watchकरोgसमाप्त)) ;
	kurobox_pro_miconsend(shutकरोwnरुको, माप(shutकरोwnरुको)) ;
	kurobox_pro_miconsend(घातeroff, माप(घातeroff));
पूर्ण

/*****************************************************************************
 * General Setup
 ****************************************************************************/
अटल अचिन्हित पूर्णांक kurobox_pro_mpp_modes[] __initdata = अणु
	MPP0_UNUSED,
	MPP1_UNUSED,
	MPP2_GPIO,		/* GPIO Micon */
	MPP3_GPIO,		/* GPIO Rtc */
	MPP4_UNUSED,
	MPP5_UNUSED,
	MPP6_न_अंकD,		/* न_अंकD Flash REn */
	MPP7_न_अंकD,		/* न_अंकD Flash WEn */
	MPP8_UNUSED,
	MPP9_UNUSED,
	MPP10_UNUSED,
	MPP11_UNUSED,
	MPP12_SATA_LED,		/* SATA 0 presence */
	MPP13_SATA_LED,		/* SATA 1 presence */
	MPP14_SATA_LED,		/* SATA 0 active */
	MPP15_SATA_LED,		/* SATA 1 active */
	MPP16_UART,		/* UART1 RXD */
	MPP17_UART,		/* UART1 TXD */
	MPP18_UART,		/* UART1 CTSn */
	MPP19_UART,		/* UART1 RTSn */
	0,
पूर्ण;

अटल व्योम __init kurobox_pro_init(व्योम)
अणु
	/*
	 * Setup basic Orion functions. Need to be called early.
	 */
	orion5x_init();

	orion5x_mpp_conf(kurobox_pro_mpp_modes);

	/*
	 * Configure peripherals.
	 */
	orion5x_ehci0_init();
	orion5x_ehci1_init();
	orion5x_eth_init(&kurobox_pro_eth_data);
	orion5x_i2c_init();
	orion5x_sata_init(&kurobox_pro_sata_data);
	orion5x_uart0_init();
	orion5x_uart1_init();
	orion5x_xor_init();

	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    KUROBOX_PRO_NOR_BOOT_BASE,
				    KUROBOX_PRO_NOR_BOOT_SIZE);
	platक्रमm_device_रेजिस्टर(&kurobox_pro_nor_flash);

	अगर (machine_is_kurobox_pro()) अणु
		mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_TARGET(0),
					    ORION_MBUS_DEVBUS_ATTR(0),
					    KUROBOX_PRO_न_अंकD_BASE,
					    KUROBOX_PRO_न_अंकD_SIZE);
		platक्रमm_device_रेजिस्टर(&kurobox_pro_nand_flash);
	पूर्ण

	i2c_रेजिस्टर_board_info(0, &kurobox_pro_i2c_rtc, 1);

	/* रेजिस्टर Kurobox Pro specअगरic घातer-off method */
	pm_घातer_off = kurobox_pro_घातer_off;
पूर्ण

#अगर_घोषित CONFIG_MACH_KUROBOX_PRO
MACHINE_START(KUROBOX_PRO, "Buffalo/Revogear Kurobox Pro")
	/* Maपूर्णांकainer: Ronen Shitrit <rshitrit@marvell.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= kurobox_pro_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_LINKSTATION_PRO
MACHINE_START(LINKSTATION_PRO, "Buffalo Linkstation Pro/Live")
	/* Maपूर्णांकainer: Byron Bradley <byron.bbradley@gmail.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= kurobox_pro_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
#पूर्ण_अगर
