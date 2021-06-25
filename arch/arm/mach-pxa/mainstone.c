<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/मुख्यstone.c
 *
 *  Support क्रम the Intel HCDDBBVA0 Development Platक्रमm.
 *  (go figure how they came up with such name...)
 *
 *  Author:	Nicolas Pitre
 *  Created:	Nov 05, 2002
 *  Copyright:	MontaVista Software Inc.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/gpio-reg.h>
#समावेश <linux/gpio/machine.h>
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
#समावेश <linux/input.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>

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
#समावेश <mach/मुख्यstone.h>
#समावेश <mach/audपन.स>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
#समावेश <mach/smemc.h>

#समावेश "generic.h"
#समावेश "devices.h"

अटल अचिन्हित दीर्घ मुख्यstone_pin_config[] = अणु
	/* Chip Select */
	GPIO15_nCS_1,

	/* LCD - 16bpp Active TFT */
	GPIOxx_LCD_TFT_16BPP,
	GPIO16_PWM0_OUT,	/* Backlight */

	/* MMC */
	GPIO32_MMC_CLK,
	GPIO112_MMC_CMD,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,

	/* USB Host Port 1 */
	GPIO88_USBH1_PWR,
	GPIO89_USBH1_PEN,

	/* PC Card */
	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO85_nPCE_1,
	GPIO54_nPCE_2,
	GPIO79_PSKTSEL,
	GPIO55_nPREG,
	GPIO56_nPWAIT,
	GPIO57_nIOIS16,

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,
	GPIO45_AC97_SYSCLK,

	/* Keypad */
	GPIO93_KP_DKIN_0,
	GPIO94_KP_DKIN_1,
	GPIO95_KP_DKIN_2,
	GPIO100_KP_MKIN_0	| WAKEUP_ON_LEVEL_HIGH,
	GPIO101_KP_MKIN_1	| WAKEUP_ON_LEVEL_HIGH,
	GPIO102_KP_MKIN_2	| WAKEUP_ON_LEVEL_HIGH,
	GPIO97_KP_MKIN_3	| WAKEUP_ON_LEVEL_HIGH,
	GPIO98_KP_MKIN_4	| WAKEUP_ON_LEVEL_HIGH,
	GPIO99_KP_MKIN_5	| WAKEUP_ON_LEVEL_HIGH,
	GPIO103_KP_MKOUT_0,
	GPIO104_KP_MKOUT_1,
	GPIO105_KP_MKOUT_2,
	GPIO106_KP_MKOUT_3,
	GPIO107_KP_MKOUT_4,
	GPIO108_KP_MKOUT_5,
	GPIO96_KP_MKOUT_6,

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	/* GPIO */
	GPIO1_GPIO | WAKEUP_ON_EDGE_BOTH,
पूर्ण;

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start	= (MST_ETH_PHYS + 0x300),
		.end	= (MST_ETH_PHYS + 0xfffff),
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= MAINSTONE_IRQ(3),
		.end	= MAINSTONE_IRQ(3),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा smc91x_platdata मुख्यstone_smc91x_info = अणु
	.flags	= SMC91X_USE_8BIT | SMC91X_USE_16BIT | SMC91X_USE_32BIT |
		  SMC91X_NOWAIT | SMC91X_USE_DMA,
	.pxa_u16_align4 = true,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
	.dev		= अणु
		.platक्रमm_data = &मुख्यstone_smc91x_info,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mst_audio_startup(काष्ठा snd_pcm_substream *substream, व्योम *priv)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		MST_MSCWR2 &= ~MST_MSCWR2_AC97_SPKROFF;
	वापस 0;
पूर्ण

अटल व्योम mst_audio_shutकरोwn(काष्ठा snd_pcm_substream *substream, व्योम *priv)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		MST_MSCWR2 |= MST_MSCWR2_AC97_SPKROFF;
पूर्ण

अटल दीर्घ mst_audio_suspend_mask;

अटल व्योम mst_audio_suspend(व्योम *priv)
अणु
	mst_audio_suspend_mask = MST_MSCWR2;
	MST_MSCWR2 |= MST_MSCWR2_AC97_SPKROFF;
पूर्ण

अटल व्योम mst_audio_resume(व्योम *priv)
अणु
	MST_MSCWR2 &= mst_audio_suspend_mask | ~MST_MSCWR2_AC97_SPKROFF;
पूर्ण

अटल pxa2xx_audio_ops_t mst_audio_ops = अणु
	.startup	= mst_audio_startup,
	.shutकरोwn	= mst_audio_shutकरोwn,
	.suspend	= mst_audio_suspend,
	.resume		= mst_audio_resume,
पूर्ण;

अटल काष्ठा resource flash_resources[] = अणु
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

अटल काष्ठा mtd_partition मुख्यstoneflash0_partitions[] = अणु
	अणु
		.name =		"Bootloader",
		.size =		0x00040000,
		.offset =	0,
		.mask_flags =	MTD_WRITEABLE  /* क्रमce पढ़ो-only */
	पूर्ण,अणु
		.name =		"Kernel",
		.size =		0x00400000,
		.offset =	0x00040000,
	पूर्ण,अणु
		.name =		"Filesystem",
		.size =		MTDPART_SIZ_FULL,
		.offset =	0x00440000
	पूर्ण
पूर्ण;

अटल काष्ठा flash_platक्रमm_data mst_flash_data[2] = अणु
	अणु
		.map_name	= "cfi_probe",
		.parts		= मुख्यstoneflash0_partitions,
		.nr_parts	= ARRAY_SIZE(मुख्यstoneflash0_partitions),
	पूर्ण, अणु
		.map_name	= "cfi_probe",
		.parts		= शून्य,
		.nr_parts	= 0,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device mst_flash_device[2] = अणु
	अणु
		.name		= "pxa2xx-flash",
		.id		= 0,
		.dev = अणु
			.platक्रमm_data = &mst_flash_data[0],
		पूर्ण,
		.resource = &flash_resources[0],
		.num_resources = 1,
	पूर्ण,
	अणु
		.name		= "pxa2xx-flash",
		.id		= 1,
		.dev = अणु
			.platक्रमm_data = &mst_flash_data[1],
		पूर्ण,
		.resource = &flash_resources[1],
		.num_resources = 1,
	पूर्ण,
पूर्ण;

#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल काष्ठा pwm_lookup मुख्यstone_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa27x-pwm.0", 0, "pwm-backlight.0", शून्य, 78770,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा platक्रमm_pwm_backlight_data मुख्यstone_backlight_data = अणु
	.max_brightness	= 1023,
	.dft_brightness	= 1023,
पूर्ण;

अटल काष्ठा platक्रमm_device मुख्यstone_backlight_device = अणु
	.name		= "pwm-backlight",
	.dev		= अणु
		.parent = &pxa27x_device_pwm0.dev,
		.platक्रमm_data = &मुख्यstone_backlight_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init मुख्यstone_backlight_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret;

	pwm_add_table(मुख्यstone_pwm_lookup, ARRAY_SIZE(मुख्यstone_pwm_lookup));

	ret = platक्रमm_device_रेजिस्टर(&मुख्यstone_backlight_device);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "mainstone: failed to register backlight device: %d\n", ret);
		pwm_हटाओ_table(मुख्यstone_pwm_lookup,
				 ARRAY_SIZE(मुख्यstone_pwm_lookup));
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा मुख्यstone_backlight_रेजिस्टर()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल काष्ठा pxafb_mode_info toshiba_lपंचांग04c380k_mode = अणु
	.pixघड़ी		= 50000,
	.xres			= 640,
	.yres			= 480,
	.bpp			= 16,
	.hsync_len		= 1,
	.left_margin		= 0x9f,
	.right_margin		= 1,
	.vsync_len		= 44,
	.upper_margin		= 0,
	.lower_margin		= 0,
	.sync			= FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mode_info toshiba_lपंचांग035a776c_mode = अणु
	.pixघड़ी		= 110000,
	.xres			= 240,
	.yres			= 320,
	.bpp			= 16,
	.hsync_len		= 4,
	.left_margin		= 8,
	.right_margin		= 20,
	.vsync_len		= 3,
	.upper_margin		= 1,
	.lower_margin		= 10,
	.sync			= FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mach_info मुख्यstone_pxafb_info = अणु
	.num_modes      	= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
पूर्ण;

अटल पूर्णांक मुख्यstone_mci_init(काष्ठा device *dev, irq_handler_t mstone_detect_पूर्णांक, व्योम *data)
अणु
	पूर्णांक err;

	/* make sure SD/Memory Stick multiplexer's संकेतs
	 * are routed to MMC controller
	 */
	MST_MSCWR1 &= ~MST_MSCWR1_MS_SEL;

	err = request_irq(MAINSTONE_MMC_IRQ, mstone_detect_पूर्णांक, 0,
			     "MMC card detect", data);
	अगर (err)
		prपूर्णांकk(KERN_ERR "mainstone_mci_init: MMC/SD: can't request MMC card detect IRQ\n");

	वापस err;
पूर्ण

अटल पूर्णांक मुख्यstone_mci_setघातer(काष्ठा device *dev, अचिन्हित पूर्णांक vdd)
अणु
	काष्ठा pxamci_platक्रमm_data* p_d = dev->platक्रमm_data;

	अगर (( 1 << vdd) & p_d->ocr_mask) अणु
		prपूर्णांकk(KERN_DEBUG "%s: on\n", __func__);
		MST_MSCWR1 |= MST_MSCWR1_MMC_ON;
		MST_MSCWR1 &= ~MST_MSCWR1_MS_SEL;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "%s: off\n", __func__);
		MST_MSCWR1 &= ~MST_MSCWR1_MMC_ON;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम मुख्यstone_mci_निकास(काष्ठा device *dev, व्योम *data)
अणु
	मुक्त_irq(MAINSTONE_MMC_IRQ, data);
पूर्ण

अटल काष्ठा pxamci_platक्रमm_data मुख्यstone_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
	.init 			= मुख्यstone_mci_init,
	.setघातer 		= मुख्यstone_mci_setघातer,
	.निकास			= मुख्यstone_mci_निकास,
पूर्ण;

अटल व्योम मुख्यstone_irda_transceiver_mode(काष्ठा device *dev, पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (mode & IR_SIRMODE) अणु
		MST_MSCWR1 &= ~MST_MSCWR1_IRDA_FIR;
	पूर्ण अन्यथा अगर (mode & IR_FIRMODE) अणु
		MST_MSCWR1 |= MST_MSCWR1_IRDA_FIR;
	पूर्ण
	pxa2xx_transceiver_mode(dev, mode);
	अगर (mode & IR_OFF) अणु
		MST_MSCWR1 = (MST_MSCWR1 & ~MST_MSCWR1_IRDA_MASK) | MST_MSCWR1_IRDA_OFF;
	पूर्ण अन्यथा अणु
		MST_MSCWR1 = (MST_MSCWR1 & ~MST_MSCWR1_IRDA_MASK) | MST_MSCWR1_IRDA_FULL;
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल काष्ठा pxaficp_platक्रमm_data मुख्यstone_ficp_platक्रमm_data = अणु
	.gpio_pwकरोwn		= -1,
	.transceiver_cap	= IR_SIRMODE | IR_FIRMODE | IR_OFF,
	.transceiver_mode	= मुख्यstone_irda_transceiver_mode,
पूर्ण;

अटल काष्ठा gpio_keys_button gpio_keys_button[] = अणु
	[0] = अणु
		.desc	= "wakeup",
		.code	= KEY_SUSPEND,
		.type	= EV_KEY,
		.gpio	= 1,
		.wakeup	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data मुख्यstone_gpio_keys = अणु
	.buttons	= gpio_keys_button,
	.nbuttons	= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device mst_gpio_keys_device = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &मुख्यstone_gpio_keys,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource mst_cplds_resources[] = अणु
	[0] = अणु
		.start	= MST_FPGA_PHYS + 0xc0,
		.end	= MST_FPGA_PHYS + 0xe0 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PXA_GPIO_TO_IRQ(0),
		.end	= PXA_GPIO_TO_IRQ(0),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_LOWEDGE,
	पूर्ण,
	[2] = अणु
		.start	= MAINSTONE_IRQ(0),
		.end	= MAINSTONE_IRQ(15),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mst_cplds_device = अणु
	.name		= "pxa_cplds_irqs",
	.id		= -1,
	.resource	= &mst_cplds_resources[0],
	.num_resources	= 3,
पूर्ण;

अटल काष्ठा platक्रमm_device *platक्रमm_devices[] __initdata = अणु
	&smc91x_device,
	&mst_flash_device[0],
	&mst_flash_device[1],
	&mst_gpio_keys_device,
	&mst_cplds_device,
पूर्ण;

अटल काष्ठा pxaohci_platक्रमm_data मुख्यstone_ohci_platक्रमm_data = अणु
	.port_mode	= PMM_PERPORT_MODE,
	.flags		= ENABLE_PORT_ALL | POWER_CONTROL_LOW | POWER_SENSE_LOW,
पूर्ण;

#अगर defined(CONFIG_KEYBOARD_PXA27x) || defined(CONFIG_KEYBOARD_PXA27x_MODULE)
अटल स्थिर अचिन्हित पूर्णांक मुख्यstone_matrix_keys[] = अणु
	KEY(0, 0, KEY_A), KEY(1, 0, KEY_B), KEY(2, 0, KEY_C),
	KEY(3, 0, KEY_D), KEY(4, 0, KEY_E), KEY(5, 0, KEY_F),
	KEY(0, 1, KEY_G), KEY(1, 1, KEY_H), KEY(2, 1, KEY_I),
	KEY(3, 1, KEY_J), KEY(4, 1, KEY_K), KEY(5, 1, KEY_L),
	KEY(0, 2, KEY_M), KEY(1, 2, KEY_N), KEY(2, 2, KEY_O),
	KEY(3, 2, KEY_P), KEY(4, 2, KEY_Q), KEY(5, 2, KEY_R),
	KEY(0, 3, KEY_S), KEY(1, 3, KEY_T), KEY(2, 3, KEY_U),
	KEY(3, 3, KEY_V), KEY(4, 3, KEY_W), KEY(5, 3, KEY_X),
	KEY(2, 4, KEY_Y), KEY(3, 4, KEY_Z),

	KEY(0, 4, KEY_DOT),	/* . */
	KEY(1, 4, KEY_CLOSE),	/* @ */
	KEY(4, 4, KEY_SLASH),
	KEY(5, 4, KEY_BACKSLASH),
	KEY(0, 5, KEY_HOME),
	KEY(1, 5, KEY_LEFTSHIFT),
	KEY(2, 5, KEY_SPACE),
	KEY(3, 5, KEY_SPACE),
	KEY(4, 5, KEY_ENTER),
	KEY(5, 5, KEY_BACKSPACE),

	KEY(0, 6, KEY_UP),
	KEY(1, 6, KEY_DOWN),
	KEY(2, 6, KEY_LEFT),
	KEY(3, 6, KEY_RIGHT),
	KEY(4, 6, KEY_SELECT),
पूर्ण;

अटल काष्ठा matrix_keymap_data मुख्यstone_matrix_keymap_data = अणु
	.keymap			= मुख्यstone_matrix_keys,
	.keymap_size		= ARRAY_SIZE(मुख्यstone_matrix_keys),
पूर्ण;

काष्ठा pxa27x_keypad_platक्रमm_data मुख्यstone_keypad_info = अणु
	.matrix_key_rows	= 6,
	.matrix_key_cols	= 7,
	.matrix_keymap_data	= &मुख्यstone_matrix_keymap_data,

	.enable_rotary0		= 1,
	.rotary0_up_key		= KEY_UP,
	.rotary0_करोwn_key	= KEY_DOWN,

	.debounce_पूर्णांकerval	= 30,
पूर्ण;

अटल व्योम __init मुख्यstone_init_keypad(व्योम)
अणु
	pxa_set_keypad_info(&मुख्यstone_keypad_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम मुख्यstone_init_keypad(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक mst_pcmcia0_irqs[11] = अणु
	[0 ... 4] = -1,
	[5] = MAINSTONE_S0_CD_IRQ,
	[6 ... 7] = -1,
	[8] = MAINSTONE_S0_STSCHG_IRQ,
	[9] = -1,
	[10] = MAINSTONE_S0_IRQ,
पूर्ण;

अटल पूर्णांक mst_pcmcia1_irqs[11] = अणु
	[0 ... 4] = -1,
	[5] = MAINSTONE_S1_CD_IRQ,
	[6 ... 7] = -1,
	[8] = MAINSTONE_S1_STSCHG_IRQ,
	[9] = -1,
	[10] = MAINSTONE_S1_IRQ,
पूर्ण;

अटल काष्ठा gpiod_lookup_table मुख्यstone_pcmcia_gpio_table = अणु
	.dev_id = "pxa2xx-pcmcia",
	.table = अणु
		GPIO_LOOKUP("mst-pcmcia0",  0, "a0vpp",   GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia0",  1, "a1vpp",   GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia0",  2, "a0vcc",   GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia0",  3, "a1vcc",   GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia0",  4, "areset",  GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia0",  5, "adetect", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("mst-pcmcia0",  6, "avs1",    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("mst-pcmcia0",  7, "avs2",    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("mst-pcmcia0",  8, "abvd1",   GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia0",  9, "abvd2",   GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia0", 10, "aready",  GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia1",  0, "b0vpp",   GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia1",  1, "b1vpp",   GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia1",  2, "b0vcc",   GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia1",  3, "b1vcc",   GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia1",  4, "breset",  GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia1",  5, "bdetect", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("mst-pcmcia1",  6, "bvs1",    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("mst-pcmcia1",  7, "bvs2",    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("mst-pcmcia1",  8, "bbvd1",   GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia1",  9, "bbvd2",   GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("mst-pcmcia1", 10, "bready",  GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init मुख्यstone_init(व्योम)
अणु
	पूर्णांक SW7 = 0;  /* FIXME: get from SCR (Mst करोc section 3.2.1.1) */

	pxa2xx_mfp_config(ARRAY_AND_SIZE(मुख्यstone_pin_config));

	/* Register board control रेजिस्टर(s) as GPIOs */
	gpio_reg_init(शून्य, (व्योम __iomem *)&MST_PCMCIA0, -1, 11,
		      "mst-pcmcia0", MST_PCMCIA_INPUTS, 0, शून्य,
		      शून्य, mst_pcmcia0_irqs);
	gpio_reg_init(शून्य, (व्योम __iomem *)&MST_PCMCIA1, -1, 11,
		      "mst-pcmcia1", MST_PCMCIA_INPUTS, 0, शून्य,
		      शून्य, mst_pcmcia1_irqs);
	gpiod_add_lookup_table(&मुख्यstone_pcmcia_gpio_table);

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	mst_flash_data[0].width = (__raw_पढ़ोl(BOOT_DEF) & 1) ? 2 : 4;
	mst_flash_data[1].width = 4;

	/* Compensate क्रम SW7 which swaps the flash banks */
	mst_flash_data[SW7].name = "processor-flash";
	mst_flash_data[SW7 ^ 1].name = "mainboard-flash";

	prपूर्णांकk(KERN_NOTICE "Mainstone configured to boot from %s\n",
	       mst_flash_data[0].name);

	/* प्रणाली bus arbiter setting
	 * - Core_Park
	 * - LCD_wt:DMA_wt:CORE_Wt = 2:3:4
	 */
	ARB_CNTRL = ARB_CORE_PARK | 0x234;

	platक्रमm_add_devices(platक्रमm_devices, ARRAY_SIZE(platक्रमm_devices));

	/* पढ़ोing Mainstone's "Virtual Configuration Register"
	   might be handy to select LCD type here */
	अगर (0)
		मुख्यstone_pxafb_info.modes = &toshiba_lपंचांग04c380k_mode;
	अन्यथा
		मुख्यstone_pxafb_info.modes = &toshiba_lपंचांग035a776c_mode;

	pxa_set_fb_info(शून्य, &मुख्यstone_pxafb_info);
	मुख्यstone_backlight_रेजिस्टर();

	pxa_set_mci_info(&मुख्यstone_mci_platक्रमm_data);
	pxa_set_ficp_info(&मुख्यstone_ficp_platक्रमm_data);
	pxa_set_ohci_info(&मुख्यstone_ohci_platक्रमm_data);
	pxa_set_i2c_info(शून्य);
	pxa_set_ac97_info(&mst_audio_ops);

	मुख्यstone_init_keypad();
पूर्ण


अटल काष्ठा map_desc मुख्यstone_io_desc[] __initdata = अणु
  	अणु	/* CPLD */
		.भव	=  MST_FPGA_VIRT,
		.pfn		= __phys_to_pfn(MST_FPGA_PHYS),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init मुख्यstone_map_io(व्योम)
अणु
	pxa27x_map_io();
	iotable_init(मुख्यstone_io_desc, ARRAY_SIZE(मुख्यstone_io_desc));

 	/*	क्रम use I SRAM as framebuffer.	*/
 	PSLR |= 0xF04;
 	PCFR = 0x66;
पूर्ण

/*
 * Driver क्रम the 8 discrete LEDs available क्रम general use:
 * Note: bits [15-8] are used to enable/blank the 8 7 segment hex displays
 * so be sure to not monkey with them here.
 */

#अगर defined(CONFIG_NEW_LEDS) && defined(CONFIG_LEDS_CLASS)
काष्ठा मुख्यstone_led अणु
	काष्ठा led_classdev	cdev;
	u8			mask;
पूर्ण;

/*
 * The triggers lines up below will only be used अगर the
 * LED triggers are compiled in.
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *trigger;
पूर्ण मुख्यstone_leds[] = अणु
	अणु "mainstone:D28", "default-on", पूर्ण,
	अणु "mainstone:D27", "cpu0", पूर्ण,
	अणु "mainstone:D26", "heartbeat" पूर्ण,
	अणु "mainstone:D25", पूर्ण,
	अणु "mainstone:D24", पूर्ण,
	अणु "mainstone:D23", पूर्ण,
	अणु "mainstone:D22", पूर्ण,
	अणु "mainstone:D21", पूर्ण,
पूर्ण;

अटल व्योम मुख्यstone_led_set(काष्ठा led_classdev *cdev,
			      क्रमागत led_brightness b)
अणु
	काष्ठा मुख्यstone_led *led = container_of(cdev,
					 काष्ठा मुख्यstone_led, cdev);
	u32 reg = MST_LEDCTRL;

	अगर (b != LED_OFF)
		reg |= led->mask;
	अन्यथा
		reg &= ~led->mask;

	MST_LEDCTRL = reg;
पूर्ण

अटल क्रमागत led_brightness मुख्यstone_led_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा मुख्यstone_led *led = container_of(cdev,
					 काष्ठा मुख्यstone_led, cdev);
	u32 reg = MST_LEDCTRL;

	वापस (reg & led->mask) ? LED_FULL : LED_OFF;
पूर्ण

अटल पूर्णांक __init मुख्यstone_leds_init(व्योम)
अणु
	पूर्णांक i;

	अगर (!machine_is_मुख्यstone())
		वापस -ENODEV;

	/* All ON */
	MST_LEDCTRL |= 0xff;
	क्रम (i = 0; i < ARRAY_SIZE(मुख्यstone_leds); i++) अणु
		काष्ठा मुख्यstone_led *led;

		led = kzalloc(माप(*led), GFP_KERNEL);
		अगर (!led)
			अवरोध;

		led->cdev.name = मुख्यstone_leds[i].name;
		led->cdev.brightness_set = मुख्यstone_led_set;
		led->cdev.brightness_get = मुख्यstone_led_get;
		led->cdev.शेष_trigger = मुख्यstone_leds[i].trigger;
		led->mask = BIT(i);

		अगर (led_classdev_रेजिस्टर(शून्य, &led->cdev) < 0) अणु
			kमुक्त(led);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Since we may have triggers on any subप्रणाली, defer registration
 * until after subप्रणाली_init.
 */
fs_initcall(मुख्यstone_leds_init);
#पूर्ण_अगर

MACHINE_START(MAINSTONE, "Intel HCDDBBVA0 Development Platform (aka Mainstone)")
	/* Maपूर्णांकainer: MontaVista Software Inc. */
	.atag_offset	= 0x100,	/* BLOB boot parameter setting */
	.map_io		= मुख्यstone_map_io,
	.nr_irqs	= MAINSTONE_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= मुख्यstone_init,
	.restart	= pxa_restart,
MACHINE_END
