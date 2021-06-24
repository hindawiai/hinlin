<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/aspenite.c
 *
 *  Support क्रम the Marvell PXA168-based Aspenite and Zylonite2
 *  Development Platक्रमm.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_data/mv_usb.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <video/pxa168fb.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>

#समावेश "addr-map.h"
#समावेश "mfp-pxa168.h"
#समावेश "pxa168.h"
#समावेश "pxa910.h"
#समावेश "irqs.h"
#समावेश "common.h"

अटल अचिन्हित दीर्घ common_pin_config[] __initdata = अणु
	/* Data Flash Interface */
	GPIO0_DFI_D15,
	GPIO1_DFI_D14,
	GPIO2_DFI_D13,
	GPIO3_DFI_D12,
	GPIO4_DFI_D11,
	GPIO5_DFI_D10,
	GPIO6_DFI_D9,
	GPIO7_DFI_D8,
	GPIO8_DFI_D7,
	GPIO9_DFI_D6,
	GPIO10_DFI_D5,
	GPIO11_DFI_D4,
	GPIO12_DFI_D3,
	GPIO13_DFI_D2,
	GPIO14_DFI_D1,
	GPIO15_DFI_D0,

	/* Static Memory Controller */
	GPIO18_SMC_nCS0,
	GPIO34_SMC_nCS1,
	GPIO23_SMC_nLUA,
	GPIO25_SMC_nLLA,
	GPIO28_SMC_RDY,
	GPIO29_SMC_SCLK,
	GPIO35_SMC_BE1,
	GPIO36_SMC_BE2,
	GPIO27_GPIO,	/* Ethernet IRQ */

	/* UART1 */
	GPIO107_UART1_RXD,
	GPIO108_UART1_TXD,

	/* SSP1 */
	GPIO113_I2S_MCLK,
	GPIO114_I2S_FRM,
	GPIO115_I2S_BCLK,
	GPIO116_I2S_RXD,
	GPIO117_I2S_TXD,

	/* LCD */
	GPIO56_LCD_FCLK_RD,
	GPIO57_LCD_LCLK_A0,
	GPIO58_LCD_PCLK_WR,
	GPIO59_LCD_DENA_BIAS,
	GPIO60_LCD_DD0,
	GPIO61_LCD_DD1,
	GPIO62_LCD_DD2,
	GPIO63_LCD_DD3,
	GPIO64_LCD_DD4,
	GPIO65_LCD_DD5,
	GPIO66_LCD_DD6,
	GPIO67_LCD_DD7,
	GPIO68_LCD_DD8,
	GPIO69_LCD_DD9,
	GPIO70_LCD_DD10,
	GPIO71_LCD_DD11,
	GPIO72_LCD_DD12,
	GPIO73_LCD_DD13,
	GPIO74_LCD_DD14,
	GPIO75_LCD_DD15,
	GPIO76_LCD_DD16,
	GPIO77_LCD_DD17,
	GPIO78_LCD_DD18,
	GPIO79_LCD_DD19,
	GPIO80_LCD_DD20,
	GPIO81_LCD_DD21,
	GPIO82_LCD_DD22,
	GPIO83_LCD_DD23,

	/* Keypad */
	GPIO109_KP_MKIN1,
	GPIO110_KP_MKIN0,
	GPIO111_KP_MKOUT7,
	GPIO112_KP_MKOUT6,
	GPIO121_KP_MKIN4,
पूर्ण;

अटल काष्ठा pxa_gpio_platक्रमm_data pxa168_gpio_pdata = अणु
	.irq_base	= MMP_GPIO_TO_IRQ(0),
पूर्ण;

अटल काष्ठा smc91x_platdata smc91x_info = अणु
	.flags	= SMC91X_USE_16BIT | SMC91X_NOWAIT,
पूर्ण;

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start	= SMC_CS1_PHYS_BASE + 0x300,
		.end	= SMC_CS1_PHYS_BASE + 0xfffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= MMP_GPIO_TO_IRQ(27),
		.end	= MMP_GPIO_TO_IRQ(27),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data = &smc91x_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
पूर्ण;

अटल काष्ठा mtd_partition aspenite_nand_partitions[] = अणु
	अणु
		.name		= "bootloader",
		.offset		= 0,
		.size		= SZ_1M,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "reserved",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_128K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "reserved",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_8M,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= (SZ_2M + SZ_1M),
		.mask_flags	= 0,
	पूर्ण, अणु
		.name		= "filesystem",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_32M + SZ_16M,
		.mask_flags	= 0,
	पूर्ण
पूर्ण;

अटल काष्ठा pxa3xx_nand_platक्रमm_data aspenite_nand_info = अणु
	.parts		= aspenite_nand_partitions,
	.nr_parts	= ARRAY_SIZE(aspenite_nand_partitions),
पूर्ण;

अटल काष्ठा i2c_board_info aspenite_i2c_info[] __initdata = अणु
	अणु I2C_BOARD_INFO("wm8753", 0x1b), पूर्ण,
पूर्ण;

अटल काष्ठा fb_videomode video_modes[] = अणु
	[0] = अणु
		.pixघड़ी	= 30120,
		.refresh	= 60,
		.xres		= 800,
		.yres		= 480,
		.hsync_len	= 1,
		.left_margin	= 215,
		.right_margin	= 40,
		.vsync_len	= 1,
		.upper_margin	= 34,
		.lower_margin	= 10,
		.sync		= FB_SYNC_VERT_HIGH_ACT | FB_SYNC_HOR_HIGH_ACT,
	पूर्ण,
पूर्ण;

काष्ठा pxa168fb_mach_info aspenite_lcd_info = अणु
	.id			= "Graphic Frame",
	.modes			= video_modes,
	.num_modes		= ARRAY_SIZE(video_modes),
	.pix_fmt		= PIX_FMT_RGB565,
	.io_pin_allocation_mode = PIN_MODE_DUMB_24,
	.dumb_mode		= DUMB_MODE_RGB888,
	.active			= 1,
	.panel_rbswap		= 0,
	.invert_pixघड़ी	= 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक aspenite_matrix_key_map[] = अणु
	KEY(0, 6, KEY_UP),	/* SW 4 */
	KEY(0, 7, KEY_DOWN),	/* SW 5 */
	KEY(1, 6, KEY_LEFT),	/* SW 6 */
	KEY(1, 7, KEY_RIGHT),	/* SW 7 */
	KEY(4, 6, KEY_ENTER),	/* SW 8 */
	KEY(4, 7, KEY_ESC),	/* SW 9 */
पूर्ण;

अटल काष्ठा matrix_keymap_data aspenite_matrix_keymap_data = अणु
	.keymap			= aspenite_matrix_key_map,
	.keymap_size		= ARRAY_SIZE(aspenite_matrix_key_map),
पूर्ण;

अटल काष्ठा pxa27x_keypad_platक्रमm_data aspenite_keypad_info __initdata = अणु
	.matrix_key_rows	= 5,
	.matrix_key_cols	= 8,
	.matrix_keymap_data	= &aspenite_matrix_keymap_data,
	.debounce_पूर्णांकerval	= 30,
पूर्ण;

#अगर IS_ENABLED(CONFIG_USB_EHCI_MV)
अटल काष्ठा mv_usb_platक्रमm_data pxa168_sph_pdata = अणु
	.mode           = MV_USB_MODE_HOST,
	.phy_init	= pxa_usb_phy_init,
	.phy_deinit	= pxa_usb_phy_deinit,
	.set_vbus	= शून्य,
पूर्ण;
#पूर्ण_अगर

अटल व्योम __init common_init(व्योम)
अणु
	mfp_config(ARRAY_AND_SIZE(common_pin_config));

	/* on-chip devices */
	pxa168_add_uart(1);
	pxa168_add_twsi(1, शून्य, ARRAY_AND_SIZE(aspenite_i2c_info));
	pxa168_add_ssp(1);
	pxa168_add_nand(&aspenite_nand_info);
	pxa168_add_fb(&aspenite_lcd_info);
	pxa168_add_keypad(&aspenite_keypad_info);
	platक्रमm_device_add_data(&pxa168_device_gpio, &pxa168_gpio_pdata,
				 माप(काष्ठा pxa_gpio_platक्रमm_data));
	platक्रमm_device_रेजिस्टर(&pxa168_device_gpio);

	/* off-chip devices */
	platक्रमm_device_रेजिस्टर(&smc91x_device);

#अगर IS_ENABLED(CONFIG_USB_SUPPORT)
#अगर IS_ENABLED(CONFIG_PHY_PXA_USB)
	platक्रमm_device_रेजिस्टर(&pxa168_device_usb_phy);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_USB_EHCI_MV)
	pxa168_add_usb_host(&pxa168_sph_pdata);
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण

MACHINE_START(ASPENITE, "PXA168-based Aspenite Development Platform")
	.map_io		= mmp_map_io,
	.nr_irqs	= MMP_NR_IRQS,
	.init_irq       = pxa168_init_irq,
	.init_समय	= pxa168_समयr_init,
	.init_machine   = common_init,
	.restart	= pxa168_restart,
MACHINE_END

MACHINE_START(ZYLONITE2, "PXA168-based Zylonite2 Development Platform")
	.map_io		= mmp_map_io,
	.nr_irqs	= MMP_NR_IRQS,
	.init_irq       = pxa168_init_irq,
	.init_समय	= pxa168_समयr_init,
	.init_machine   = common_init,
	.restart	= pxa168_restart,
MACHINE_END
