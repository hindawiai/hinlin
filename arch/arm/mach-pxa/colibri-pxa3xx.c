<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  arch/arm/mach-pxa/colibri-pxa3xx.c
 *
 *  Common functions क्रम all Toradex PXA3xx modules
 *
 *  Daniel Mack <daniel@caiaq.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/etherdevice.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <mach/pxa3xx-regs.h>
#समावेश "mfp-pxa300.h"
#समावेश "colibri.h"
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mtd-nand-pxa3xx.h>

#समावेश "generic.h"
#समावेश "devices.h"

#अगर defined(CONFIG_AX88796)
#घोषणा ETHER_ADDR_LEN 6
अटल u8 ether_mac_addr[ETHER_ADDR_LEN];

व्योम __init colibri_pxa3xx_init_eth(काष्ठा ax_plat_data *plat_data)
अणु
	पूर्णांक i;
	u64 serial = ((u64) प्रणाली_serial_high << 32) | प्रणाली_serial_low;

	/*
	 * If the bootloader passed in a serial boot tag, which contains a
	 * valid ethernet MAC, pass it to the पूर्णांकerface. Toradex ships the
	 * modules with their own bootloader which provides a valid MAC
	 * this way.
	 */

	क्रम (i = 0; i < ETHER_ADDR_LEN; i++) अणु
		ether_mac_addr[i] = serial & 0xff;
		serial >>= 8;
	पूर्ण

	अगर (is_valid_ether_addr(ether_mac_addr)) अणु
		plat_data->flags |= AXFLG_MAC_FROMPLATFORM;
		plat_data->mac_addr = ether_mac_addr;
		prपूर्णांकk(KERN_INFO "%s(): taking MAC from serial boot tag\n",
			__func__);
	पूर्ण अन्यथा अणु
		plat_data->flags |= AXFLG_MAC_FROMDEV;
		prपूर्णांकk(KERN_INFO "%s(): no valid serial boot tag found, "
			"taking MAC from device\n", __func__);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल पूर्णांक lcd_bl_pin;

/*
 * LCD panel (Sharp LQ043T3DX02)
 */
अटल व्योम colibri_lcd_backlight(पूर्णांक on)
अणु
	gpio_set_value(lcd_bl_pin, !!on);
पूर्ण

अटल काष्ठा pxafb_mode_info sharp_lq43_mode = अणु
	.pixघड़ी	= 101936,
	.xres		= 480,
	.yres		= 272,
	.bpp		= 32,
	.depth		= 18,
	.hsync_len      = 41,
	.left_margin    = 2,
	.right_margin   = 2,
	.vsync_len      = 10,
	.upper_margin   = 2,
	.lower_margin   = 2,
	.sync	   	= 0,
	.cmap_greyscale = 0,
पूर्ण;

अटल काष्ठा pxafb_mach_info sharp_lq43_info = अणु
	.modes		= &sharp_lq43_mode,
	.num_modes	= 1,
	.cmap_inverse	= 0,
	.cmap_अटल	= 0,
	.lcd_conn	= LCD_COLOR_TFT_18BPP,
	.pxafb_backlight_घातer = colibri_lcd_backlight,
पूर्ण;

व्योम __init colibri_pxa3xx_init_lcd(पूर्णांक bl_pin)
अणु
	lcd_bl_pin = bl_pin;
	gpio_request(bl_pin, "lcd backlight");
	gpio_direction_output(bl_pin, 0);
	pxa_set_fb_info(शून्य, &sharp_lq43_info);
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_MARVELL)
अटल काष्ठा mtd_partition colibri_nand_partitions[] = अणु
	अणु
		.name        = "bootloader",
		.offset      = 0,
		.size        = SZ_512K,
		.mask_flags  = MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	अणु
		.name        = "kernel",
		.offset      = MTDPART_OFS_APPEND,
		.size        = SZ_4M,
		.mask_flags  = MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	अणु
		.name        = "reserved",
		.offset      = MTDPART_OFS_APPEND,
		.size        = SZ_1M,
		.mask_flags  = MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	अणु
		.name        = "fs",
		.offset      = MTDPART_OFS_APPEND,
		.size        = MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxa3xx_nand_platक्रमm_data colibri_nand_info = अणु
	.keep_config	= 1,
	.parts		= colibri_nand_partitions,
	.nr_parts	= ARRAY_SIZE(colibri_nand_partitions),
पूर्ण;

व्योम __init colibri_pxa3xx_init_nand(व्योम)
अणु
	pxa3xx_set_nand_info(&colibri_nand_info);
पूर्ण
#पूर्ण_अगर

