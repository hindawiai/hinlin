<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/lpd270.c
 *
 * Support क्रम the LogicPD PXA270 Card Engine.
 * Derived from the मुख्यstone code, which carries these notices:
 *
 * Author:	Nicolas Pitre
 * Created:	Nov 05, 2002
 * Copyright:	MontaVista Software Inc.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/bitops.h>
#समावेश <linux/fb.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/smc91x.h>

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश "pxa27x.h"
#समावेश "lpd270.h"
#समावेश <mach/audपन.स>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश <mach/smemc.h>

#समावेश "generic.h"
#समावेश "devices.h"

अटल अचिन्हित दीर्घ lpd270_pin_config[] __initdata = अणु
	/* Chip Selects */
	GPIO15_nCS_1,	/* Mainboard Flash */
	GPIO78_nCS_2,	/* CPLD + Ethernet */

	/* LCD - 16bpp Active TFT */
	GPIO58_LCD_LDD_0,
	GPIO59_LCD_LDD_1,
	GPIO60_LCD_LDD_2,
	GPIO61_LCD_LDD_3,
	GPIO62_LCD_LDD_4,
	GPIO63_LCD_LDD_5,
	GPIO64_LCD_LDD_6,
	GPIO65_LCD_LDD_7,
	GPIO66_LCD_LDD_8,
	GPIO67_LCD_LDD_9,
	GPIO68_LCD_LDD_10,
	GPIO69_LCD_LDD_11,
	GPIO70_LCD_LDD_12,
	GPIO71_LCD_LDD_13,
	GPIO72_LCD_LDD_14,
	GPIO73_LCD_LDD_15,
	GPIO74_LCD_FCLK,
	GPIO75_LCD_LCLK,
	GPIO76_LCD_PCLK,
	GPIO77_LCD_BIAS,
	GPIO16_PWM0_OUT,	/* Backlight */

	/* USB Host */
	GPIO88_USBH1_PWR,
	GPIO89_USBH1_PEN,

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,
	GPIO45_AC97_SYSCLK,

	GPIO1_GPIO | WAKEUP_ON_EDGE_BOTH,
पूर्ण;

अटल अचिन्हित पूर्णांक lpd270_irq_enabled;

अटल व्योम lpd270_mask_irq(काष्ठा irq_data *d)
अणु
	पूर्णांक lpd270_irq = d->irq - LPD270_IRQ(0);

	__raw_ग_लिखोw(~(1 << lpd270_irq), LPD270_INT_STATUS);

	lpd270_irq_enabled &= ~(1 << lpd270_irq);
	__raw_ग_लिखोw(lpd270_irq_enabled, LPD270_INT_MASK);
पूर्ण

अटल व्योम lpd270_unmask_irq(काष्ठा irq_data *d)
अणु
	पूर्णांक lpd270_irq = d->irq - LPD270_IRQ(0);

	lpd270_irq_enabled |= 1 << lpd270_irq;
	__raw_ग_लिखोw(lpd270_irq_enabled, LPD270_INT_MASK);
पूर्ण

अटल काष्ठा irq_chip lpd270_irq_chip = अणु
	.name		= "CPLD",
	.irq_ack	= lpd270_mask_irq,
	.irq_mask	= lpd270_mask_irq,
	.irq_unmask	= lpd270_unmask_irq,
पूर्ण;

अटल व्योम lpd270_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ pending;

	pending = __raw_पढ़ोw(LPD270_INT_STATUS) & lpd270_irq_enabled;
	करो अणु
		/* clear useless edge notअगरication */
		desc->irq_data.chip->irq_ack(&desc->irq_data);
		अगर (likely(pending)) अणु
			irq = LPD270_IRQ(0) + __ffs(pending);
			generic_handle_irq(irq);

			pending = __raw_पढ़ोw(LPD270_INT_STATUS) &
						lpd270_irq_enabled;
		पूर्ण
	पूर्ण जबतक (pending);
पूर्ण

अटल व्योम __init lpd270_init_irq(व्योम)
अणु
	पूर्णांक irq;

	pxa27x_init_irq();

	__raw_ग_लिखोw(0, LPD270_INT_MASK);
	__raw_ग_लिखोw(0, LPD270_INT_STATUS);

	/* setup extra LogicPD PXA270 irqs */
	क्रम (irq = LPD270_IRQ(2); irq <= LPD270_IRQ(4); irq++) अणु
		irq_set_chip_and_handler(irq, &lpd270_irq_chip,
					 handle_level_irq);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण
	irq_set_chained_handler(PXA_GPIO_TO_IRQ(0), lpd270_irq_handler);
	irq_set_irq_type(PXA_GPIO_TO_IRQ(0), IRQ_TYPE_EDGE_FALLING);
पूर्ण


#अगर_घोषित CONFIG_PM
अटल व्योम lpd270_irq_resume(व्योम)
अणु
	__raw_ग_लिखोw(lpd270_irq_enabled, LPD270_INT_MASK);
पूर्ण

अटल काष्ठा syscore_ops lpd270_irq_syscore_ops = अणु
	.resume = lpd270_irq_resume,
पूर्ण;

अटल पूर्णांक __init lpd270_irq_device_init(व्योम)
अणु
	अगर (machine_is_logicpd_pxa270()) अणु
		रेजिस्टर_syscore_ops(&lpd270_irq_syscore_ops);
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

device_initcall(lpd270_irq_device_init);
#पूर्ण_अगर


अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start	= LPD270_ETH_PHYS,
		.end	= (LPD270_ETH_PHYS + 0xfffff),
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= LPD270_ETHERNET_IRQ,
		.end	= LPD270_ETHERNET_IRQ,
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण,
पूर्ण;

काष्ठा smc91x_platdata smc91x_platdata = अणु
	.flags = SMC91X_USE_16BIT | SMC91X_NOWAIT,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
	.dev.platक्रमm_data = &smc91x_platdata,
पूर्ण;

अटल काष्ठा resource lpd270_flash_resources[] = अणु
	[0] = अणु
		.start	= PXA_CS0_PHYS,
		.end	= PXA_CS0_PHYS + SZ_64M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PXA_CS1_PHYS,
		.end	= PXA_CS1_PHYS + SZ_64M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition lpd270_flash0_partitions[] = अणु
	अणु
		.name =		"Bootloader",
		.size =		0x00040000,
		.offset =	0,
		.mask_flags =	MTD_WRITEABLE  /* क्रमce पढ़ो-only */
	पूर्ण, अणु
		.name =		"Kernel",
		.size =		0x00400000,
		.offset =	0x00040000,
	पूर्ण, अणु
		.name =		"Filesystem",
		.size =		MTDPART_SIZ_FULL,
		.offset =	0x00440000
	पूर्ण,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data lpd270_flash_data[2] = अणु
	अणु
		.name		= "processor-flash",
		.map_name	= "cfi_probe",
		.parts		= lpd270_flash0_partitions,
		.nr_parts	= ARRAY_SIZE(lpd270_flash0_partitions),
	पूर्ण, अणु
		.name		= "mainboard-flash",
		.map_name	= "cfi_probe",
		.parts		= शून्य,
		.nr_parts	= 0,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device lpd270_flash_device[2] = अणु
	अणु
		.name		= "pxa2xx-flash",
		.id		= 0,
		.dev = अणु
			.platक्रमm_data	= &lpd270_flash_data[0],
		पूर्ण,
		.resource	= &lpd270_flash_resources[0],
		.num_resources	= 1,
	पूर्ण, अणु
		.name		= "pxa2xx-flash",
		.id		= 1,
		.dev = अणु
			.platक्रमm_data	= &lpd270_flash_data[1],
		पूर्ण,
		.resource	= &lpd270_flash_resources[1],
		.num_resources	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा pwm_lookup lpd270_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa27x-pwm.0", 0, "pwm-backlight.0", शून्य, 78770,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा platक्रमm_pwm_backlight_data lpd270_backlight_data = अणु
	.max_brightness	= 1,
	.dft_brightness	= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device lpd270_backlight_device = अणु
	.name		= "pwm-backlight",
	.dev		= अणु
		.parent	= &pxa27x_device_pwm0.dev,
		.platक्रमm_data = &lpd270_backlight_data,
	पूर्ण,
पूर्ण;

/* 5.7" TFT QVGA (LoLo display number 1) */
अटल काष्ठा pxafb_mode_info sharp_lq057q3dc02_mode = अणु
	.pixघड़ी		= 150000,
	.xres			= 320,
	.yres			= 240,
	.bpp			= 16,
	.hsync_len		= 0x14,
	.left_margin		= 0x28,
	.right_margin		= 0x0a,
	.vsync_len		= 0x02,
	.upper_margin		= 0x08,
	.lower_margin		= 0x14,
	.sync			= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mach_info sharp_lq057q3dc02 = अणु
	.modes			= &sharp_lq057q3dc02_mode,
	.num_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL |
				  LCD_ALTERNATE_MAPPING,
पूर्ण;

/* 12.1" TFT SVGA (LoLo display number 2) */
अटल काष्ठा pxafb_mode_info sharp_lq121s1dg31_mode = अणु
	.pixघड़ी		= 50000,
	.xres			= 800,
	.yres			= 600,
	.bpp			= 16,
	.hsync_len		= 0x05,
	.left_margin		= 0x52,
	.right_margin		= 0x05,
	.vsync_len		= 0x04,
	.upper_margin		= 0x14,
	.lower_margin		= 0x0a,
	.sync			= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mach_info sharp_lq121s1dg31 = अणु
	.modes			= &sharp_lq121s1dg31_mode,
	.num_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL |
				  LCD_ALTERNATE_MAPPING,
पूर्ण;

/* 3.6" TFT QVGA (LoLo display number 3) */
अटल काष्ठा pxafb_mode_info sharp_lq036q1da01_mode = अणु
	.pixघड़ी		= 150000,
	.xres			= 320,
	.yres			= 240,
	.bpp			= 16,
	.hsync_len		= 0x0e,
	.left_margin		= 0x04,
	.right_margin		= 0x0a,
	.vsync_len		= 0x03,
	.upper_margin		= 0x03,
	.lower_margin		= 0x03,
	.sync			= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mach_info sharp_lq036q1da01 = अणु
	.modes			= &sharp_lq036q1da01_mode,
	.num_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL |
				  LCD_ALTERNATE_MAPPING,
पूर्ण;

/* 6.4" TFT VGA (LoLo display number 5) */
अटल काष्ठा pxafb_mode_info sharp_lq64d343_mode = अणु
	.pixघड़ी		= 25000,
	.xres			= 640,
	.yres			= 480,
	.bpp			= 16,
	.hsync_len		= 0x31,
	.left_margin		= 0x89,
	.right_margin		= 0x19,
	.vsync_len		= 0x12,
	.upper_margin		= 0x22,
	.lower_margin		= 0x00,
	.sync			= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mach_info sharp_lq64d343 = अणु
	.modes			= &sharp_lq64d343_mode,
	.num_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL |
				  LCD_ALTERNATE_MAPPING,
पूर्ण;

/* 10.4" TFT VGA (LoLo display number 7) */
अटल काष्ठा pxafb_mode_info sharp_lq10d368_mode = अणु
	.pixघड़ी		= 25000,
	.xres			= 640,
	.yres			= 480,
	.bpp			= 16,
	.hsync_len		= 0x31,
	.left_margin		= 0x89,
	.right_margin		= 0x19,
	.vsync_len		= 0x12,
	.upper_margin		= 0x22,
	.lower_margin		= 0x00,
	.sync			= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mach_info sharp_lq10d368 = अणु
	.modes			= &sharp_lq10d368_mode,
	.num_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL |
				  LCD_ALTERNATE_MAPPING,
पूर्ण;

/* 3.5" TFT QVGA (LoLo display number 8) */
अटल काष्ठा pxafb_mode_info sharp_lq035q7db02_20_mode = अणु
	.pixघड़ी		= 150000,
	.xres			= 240,
	.yres			= 320,
	.bpp			= 16,
	.hsync_len		= 0x0e,
	.left_margin		= 0x0a,
	.right_margin		= 0x0a,
	.vsync_len		= 0x03,
	.upper_margin		= 0x05,
	.lower_margin		= 0x14,
	.sync			= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mach_info sharp_lq035q7db02_20 = अणु
	.modes			= &sharp_lq035q7db02_20_mode,
	.num_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL |
				  LCD_ALTERNATE_MAPPING,
पूर्ण;

अटल काष्ठा pxafb_mach_info *lpd270_lcd_to_use;

अटल पूर्णांक __init lpd270_set_lcd(अक्षर *str)
अणु
	अगर (!strnहालcmp(str, "lq057q3dc02", 11)) अणु
		lpd270_lcd_to_use = &sharp_lq057q3dc02;
	पूर्ण अन्यथा अगर (!strnहालcmp(str, "lq121s1dg31", 11)) अणु
		lpd270_lcd_to_use = &sharp_lq121s1dg31;
	पूर्ण अन्यथा अगर (!strnहालcmp(str, "lq036q1da01", 11)) अणु
		lpd270_lcd_to_use = &sharp_lq036q1da01;
	पूर्ण अन्यथा अगर (!strnहालcmp(str, "lq64d343", 8)) अणु
		lpd270_lcd_to_use = &sharp_lq64d343;
	पूर्ण अन्यथा अगर (!strnहालcmp(str, "lq10d368", 8)) अणु
		lpd270_lcd_to_use = &sharp_lq10d368;
	पूर्ण अन्यथा अगर (!strnहालcmp(str, "lq035q7db02-20", 14)) अणु
		lpd270_lcd_to_use = &sharp_lq035q7db02_20;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "lpd270: unknown lcd panel [%s]\n", str);
	पूर्ण

	वापस 1;
पूर्ण

__setup("lcd=", lpd270_set_lcd);

अटल काष्ठा platक्रमm_device *platक्रमm_devices[] __initdata = अणु
	&smc91x_device,
	&lpd270_backlight_device,
	&lpd270_flash_device[0],
	&lpd270_flash_device[1],
पूर्ण;

अटल काष्ठा pxaohci_platक्रमm_data lpd270_ohci_platक्रमm_data = अणु
	.port_mode	= PMM_PERPORT_MODE,
	.flags		= ENABLE_PORT_ALL | POWER_CONTROL_LOW | POWER_SENSE_LOW,
पूर्ण;

अटल व्योम __init lpd270_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(lpd270_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	lpd270_flash_data[0].width = (__raw_पढ़ोl(BOOT_DEF) & 1) ? 2 : 4;
	lpd270_flash_data[1].width = 4;

	/*
	 * System bus arbiter setting:
	 * - Core_Park
	 * - LCD_wt:DMA_wt:CORE_Wt = 2:3:4
	 */
	ARB_CNTRL = ARB_CORE_PARK | 0x234;

	pwm_add_table(lpd270_pwm_lookup, ARRAY_SIZE(lpd270_pwm_lookup));
	platक्रमm_add_devices(platक्रमm_devices, ARRAY_SIZE(platक्रमm_devices));

	pxa_set_ac97_info(शून्य);

	अगर (lpd270_lcd_to_use != शून्य)
		pxa_set_fb_info(शून्य, lpd270_lcd_to_use);

	pxa_set_ohci_info(&lpd270_ohci_platक्रमm_data);
पूर्ण


अटल काष्ठा map_desc lpd270_io_desc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ)LPD270_CPLD_VIRT,
		.pfn		= __phys_to_pfn(LPD270_CPLD_PHYS),
		.length		= LPD270_CPLD_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल व्योम __init lpd270_map_io(व्योम)
अणु
	pxa27x_map_io();
	iotable_init(lpd270_io_desc, ARRAY_SIZE(lpd270_io_desc));

	/* क्रम use I SRAM as framebuffer.  */
	PSLR |= 0x00000F04;
	PCFR  = 0x00000066;
पूर्ण

MACHINE_START(LOGICPD_PXA270, "LogicPD PXA270 Card Engine")
	/* Maपूर्णांकainer: Peter Barada */
	.atag_offset	= 0x100,
	.map_io		= lpd270_map_io,
	.nr_irqs	= LPD270_NR_IRQS,
	.init_irq	= lpd270_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= lpd270_init,
	.restart	= pxa_restart,
MACHINE_END
