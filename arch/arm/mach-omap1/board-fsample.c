<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/board-fsample.c
 *
 * Modअगरied from board-perseus2.c
 *
 * Original OMAP730 support by Jean Pihet <j-pihet@ti.com>
 * Updated क्रम 2.6 by Kevin Hilman <kjh@hilman.org>
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/platnand.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/input.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/omapfb.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/tc.h>
#समावेश <mach/mux.h>
#समावेश "flash.h"
#समावेश <linux/platक्रमm_data/keypad-omap.h>

#समावेश <mach/hardware.h>

#समावेश "iomap.h"
#समावेश "common.h"
#समावेश "fpga.h"

/* fsample is pretty बंद to p2-sample */

#घोषणा fsample_cpld_पढ़ो(reg) __raw_पढ़ोb(reg)
#घोषणा fsample_cpld_ग_लिखो(val, reg) __raw_ग_लिखोb(val, reg)

#घोषणा FSAMPLE_CPLD_BASE    0xE8100000
#घोषणा FSAMPLE_CPLD_SIZE    SZ_4K
#घोषणा FSAMPLE_CPLD_START   0x05080000

#घोषणा FSAMPLE_CPLD_REG_A   (FSAMPLE_CPLD_BASE + 0x00)
#घोषणा FSAMPLE_CPLD_SWITCH  (FSAMPLE_CPLD_BASE + 0x02)
#घोषणा FSAMPLE_CPLD_UART    (FSAMPLE_CPLD_BASE + 0x02)
#घोषणा FSAMPLE_CPLD_REG_B   (FSAMPLE_CPLD_BASE + 0x04)
#घोषणा FSAMPLE_CPLD_VERSION (FSAMPLE_CPLD_BASE + 0x06)
#घोषणा FSAMPLE_CPLD_SET_CLR (FSAMPLE_CPLD_BASE + 0x06)

#घोषणा FSAMPLE_CPLD_BIT_BT_RESET         0
#घोषणा FSAMPLE_CPLD_BIT_LCD_RESET        1
#घोषणा FSAMPLE_CPLD_BIT_CAM_PWDN         2
#घोषणा FSAMPLE_CPLD_BIT_CHARGER_ENABLE   3
#घोषणा FSAMPLE_CPLD_BIT_SD_MMC_EN        4
#घोषणा FSAMPLE_CPLD_BIT_aGPS_PWREN       5
#घोषणा FSAMPLE_CPLD_BIT_BACKLIGHT        6
#घोषणा FSAMPLE_CPLD_BIT_aGPS_EN_RESET    7
#घोषणा FSAMPLE_CPLD_BIT_aGPS_SLEEPx_N    8
#घोषणा FSAMPLE_CPLD_BIT_OTG_RESET        9

#घोषणा fsample_cpld_set(bit) \
    fsample_cpld_ग_लिखो((((bit) & 15) << 4) | 0x0f, FSAMPLE_CPLD_SET_CLR)

#घोषणा fsample_cpld_clear(bit) \
    fsample_cpld_ग_लिखो(0xf0 | ((bit) & 15), FSAMPLE_CPLD_SET_CLR)

अटल स्थिर अचिन्हित पूर्णांक fsample_keymap[] = अणु
	KEY(0, 0, KEY_UP),
	KEY(1, 0, KEY_RIGHT),
	KEY(2, 0, KEY_LEFT),
	KEY(3, 0, KEY_DOWN),
	KEY(4, 0, KEY_ENTER),
	KEY(0, 1, KEY_F10),
	KEY(1, 1, KEY_SEND),
	KEY(2, 1, KEY_END),
	KEY(3, 1, KEY_VOLUMEDOWN),
	KEY(4, 1, KEY_VOLUMEUP),
	KEY(5, 1, KEY_RECORD),
	KEY(0, 2, KEY_F9),
	KEY(1, 2, KEY_3),
	KEY(2, 2, KEY_6),
	KEY(3, 2, KEY_9),
	KEY(4, 2, KEY_KPDOT),
	KEY(0, 3, KEY_BACK),
	KEY(1, 3, KEY_2),
	KEY(2, 3, KEY_5),
	KEY(3, 3, KEY_8),
	KEY(4, 3, KEY_0),
	KEY(5, 3, KEY_KPSLASH),
	KEY(0, 4, KEY_HOME),
	KEY(1, 4, KEY_1),
	KEY(2, 4, KEY_4),
	KEY(3, 4, KEY_7),
	KEY(4, 4, KEY_KPASTERISK),
	KEY(5, 4, KEY_POWER),
पूर्ण;

अटल काष्ठा smc91x_platdata smc91x_info = अणु
	.flags	= SMC91X_USE_16BIT | SMC91X_NOWAIT,
	.leda	= RPC_LED_100_10,
	.ledb	= RPC_LED_TX_RX,
पूर्ण;

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start	= H2P2_DBG_FPGA_ETHR_START,	/* Physical */
		.end	= H2P2_DBG_FPGA_ETHR_START + 0xf,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= INT_7XX_MPU_EXT_NIRQ,
		.end	= 0,
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण,
पूर्ण;

अटल व्योम __init fsample_init_smc91x(व्योम)
अणु
	__raw_ग_लिखोb(1, H2P2_DBG_FPGA_LAN_RESET);
	mdelay(50);
	__raw_ग_लिखोb(__raw_पढ़ोb(H2P2_DBG_FPGA_LAN_RESET) & ~1,
		   H2P2_DBG_FPGA_LAN_RESET);
	mdelay(50);
पूर्ण

अटल काष्ठा mtd_partition nor_partitions[] = अणु
	/* bootloader (U-Boot, etc) in first sector */
	अणु
	      .name		= "bootloader",
	      .offset		= 0,
	      .size		= SZ_128K,
	      .mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	/* bootloader params in the next sector */
	अणु
	      .name		= "params",
	      .offset		= MTDPART_OFS_APPEND,
	      .size		= SZ_128K,
	      .mask_flags	= 0,
	पूर्ण,
	/* kernel */
	अणु
	      .name		= "kernel",
	      .offset		= MTDPART_OFS_APPEND,
	      .size		= SZ_2M,
	      .mask_flags	= 0
	पूर्ण,
	/* rest of flash is a file प्रणाली */
	अणु
	      .name		= "rootfs",
	      .offset		= MTDPART_OFS_APPEND,
	      .size		= MTDPART_SIZ_FULL,
	      .mask_flags	= 0
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data nor_data = अणु
	.width		= 2,
	.set_vpp	= omap1_set_vpp,
	.parts		= nor_partitions,
	.nr_parts	= ARRAY_SIZE(nor_partitions),
पूर्ण;

अटल काष्ठा resource nor_resource = अणु
	.start		= OMAP_CS0_PHYS,
	.end		= OMAP_CS0_PHYS + SZ_32M - 1,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device nor_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &nor_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &nor_resource,
पूर्ण;

#घोषणा FSAMPLE_न_अंकD_RB_GPIO_PIN	62

अटल पूर्णांक nand_dev_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	वापस gpio_get_value(FSAMPLE_न_अंकD_RB_GPIO_PIN);
पूर्ण

अटल काष्ठा platक्रमm_nand_data nand_data = अणु
	.chip	= अणु
		.nr_chips		= 1,
		.chip_offset		= 0,
		.options		= न_अंकD_SAMSUNG_LP_OPTIONS,
	पूर्ण,
	.ctrl	= अणु
		.cmd_ctrl	= omap1_nand_cmd_ctl,
		.dev_पढ़ोy	= nand_dev_पढ़ोy,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource nand_resource = अणु
	.start		= OMAP_CS3_PHYS,
	.end		= OMAP_CS3_PHYS + SZ_4K - 1,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device nand_device = अणु
	.name		= "gen_nand",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &nand_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &nand_resource,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.dev	= अणु
		.platक्रमm_data	= &smc91x_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
पूर्ण;

अटल काष्ठा resource kp_resources[] = अणु
	[0] = अणु
		.start	= INT_7XX_MPUIO_KEYPAD,
		.end	= INT_7XX_MPUIO_KEYPAD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा matrix_keymap_data fsample_keymap_data = अणु
	.keymap		= fsample_keymap,
	.keymap_size	= ARRAY_SIZE(fsample_keymap),
पूर्ण;

अटल काष्ठा omap_kp_platक्रमm_data kp_data = अणु
	.rows		= 8,
	.cols		= 8,
	.keymap_data	= &fsample_keymap_data,
	.delay		= 4,
पूर्ण;

अटल काष्ठा platक्रमm_device kp_device = अणु
	.name		= "omap-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &kp_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(kp_resources),
	.resource	= kp_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&nor_device,
	&nand_device,
	&smc91x_device,
	&kp_device,
पूर्ण;

अटल स्थिर काष्ठा omap_lcd_config fsample_lcd_config = अणु
	.ctrl_name	= "internal",
पूर्ण;

अटल व्योम __init omap_fsample_init(व्योम)
अणु
	/* Early, board-dependent init */

	/*
	 * Hold GSM Reset until needed
	 */
	omap_ग_लिखोw(omap_पढ़ोw(OMAP7XX_DSP_M_CTL) & ~1, OMAP7XX_DSP_M_CTL);

	/*
	 * UARTs -> करोne स्वतःmagically by 8250 driver
	 */

	/*
	 * CSx timings, GPIO Mux ... setup
	 */

	/* Flash: CS0 timings setup */
	omap_ग_लिखोl(0x0000fff3, OMAP7XX_FLASH_CFG_0);
	omap_ग_लिखोl(0x00000088, OMAP7XX_FLASH_ACFG_0);

	/*
	 * Ethernet support through the debug board
	 * CS1 timings setup
	 */
	omap_ग_लिखोl(0x0000fff3, OMAP7XX_FLASH_CFG_1);
	omap_ग_लिखोl(0x00000000, OMAP7XX_FLASH_ACFG_1);

	/*
	 * Configure MPU_EXT_NIRQ IO in IO_CONF9 रेजिस्टर,
	 * It is used as the Ethernet controller पूर्णांकerrupt
	 */
	omap_ग_लिखोl(omap_पढ़ोl(OMAP7XX_IO_CONF_9) & 0x1FFFFFFF,
			OMAP7XX_IO_CONF_9);

	fsample_init_smc91x();

	BUG_ON(gpio_request(FSAMPLE_न_अंकD_RB_GPIO_PIN, "NAND ready") < 0);
	gpio_direction_input(FSAMPLE_न_अंकD_RB_GPIO_PIN);

	omap_cfg_reg(L3_1610_FLASH_CS2B_OE);
	omap_cfg_reg(M8_1610_FLASH_CS2B_WE);

	/* Mux pins क्रम keypad */
	omap_cfg_reg(E2_7XX_KBR0);
	omap_cfg_reg(J7_7XX_KBR1);
	omap_cfg_reg(E1_7XX_KBR2);
	omap_cfg_reg(F3_7XX_KBR3);
	omap_cfg_reg(D2_7XX_KBR4);
	omap_cfg_reg(C2_7XX_KBC0);
	omap_cfg_reg(D3_7XX_KBC1);
	omap_cfg_reg(E4_7XX_KBC2);
	omap_cfg_reg(F4_7XX_KBC3);
	omap_cfg_reg(E3_7XX_KBC4);

	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));

	omap_serial_init();
	omap_रेजिस्टर_i2c_bus(1, 100, शून्य, 0);

	omapfb_set_lcd_config(&fsample_lcd_config);
पूर्ण

/* Only FPGA needs to be mapped here. All others are करोne with ioremap */
अटल काष्ठा map_desc omap_fsample_io_desc[] __initdata = अणु
	अणु
		.भव	= H2P2_DBG_FPGA_BASE,
		.pfn		= __phys_to_pfn(H2P2_DBG_FPGA_START),
		.length		= H2P2_DBG_FPGA_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= FSAMPLE_CPLD_BASE,
		.pfn		= __phys_to_pfn(FSAMPLE_CPLD_START),
		.length		= FSAMPLE_CPLD_SIZE,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init omap_fsample_map_io(व्योम)
अणु
	omap15xx_map_io();
	iotable_init(omap_fsample_io_desc,
		     ARRAY_SIZE(omap_fsample_io_desc));
पूर्ण

MACHINE_START(OMAP_FSAMPLE, "OMAP730 F-Sample")
/* Maपूर्णांकainer: Brian Swetland <swetland@google.com> */
	.atag_offset	= 0x100,
	.map_io		= omap_fsample_map_io,
	.init_early	= omap1_init_early,
	.init_irq	= omap1_init_irq,
	.handle_irq	= omap1_handle_irq,
	.init_machine	= omap_fsample_init,
	.init_late	= omap1_init_late,
	.init_समय	= omap1_समयr_init,
	.restart	= omap1_restart,
MACHINE_END
