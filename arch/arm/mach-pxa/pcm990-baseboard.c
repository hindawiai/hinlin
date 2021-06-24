<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  arch/arm/mach-pxa/pcm990-baseboard.c
 *  Support क्रम the Phytec phyCORE-PXA270 Development Platक्रमm (PCM-990).
 *
 *  Refer
 *   http://www.phytec.com/products/rdk/ARM-XScale/phyCORE-XScale-PXA270.hपंचांगl
 *  क्रम additional hardware info
 *
 *  Author:	Juergen Kilb
 *  Created:	April 05, 2005
 *  Copyright:	Phytec Messtechnik GmbH
 *  e-Mail:	armlinux@phytec.de
 *
 *  based on Intel Mainstone Board
 *
 *  Copyright 2007 Juergen Beisert @ Pengutronix (j.beisert@pengutronix.de)
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>

#समावेश <यंत्र/mach/map.h>
#समावेश "pxa27x.h"
#समावेश <mach/audपन.स>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश "pcm990_baseboard.h"
#समावेश <linux/platक्रमm_data/video-pxafb.h>

#समावेश "devices.h"
#समावेश "generic.h"

अटल अचिन्हित दीर्घ pcm990_pin_config[] __initdata = अणु
	/* MMC */
	GPIO32_MMC_CLK,
	GPIO112_MMC_CMD,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	/* USB */
	GPIO88_USBH1_PWR,
	GPIO89_USBH1_PEN,
	/* PWM0 */
	GPIO16_PWM0_OUT,

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,
पूर्ण;

अटल व्योम __iomem *pcm990_cpld_base;

अटल u8 pcm990_cpld_पढ़ोb(अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोb(pcm990_cpld_base + reg);
पूर्ण

अटल व्योम pcm990_cpld_ग_लिखोb(u8 value, अचिन्हित पूर्णांक reg)
अणु
	ग_लिखोb(value, pcm990_cpld_base + reg);
पूर्ण

/*
 * pcm990_lcd_घातer - control घातer supply to the LCD
 * @on: 0 = चयन off, 1 = चयन on
 *
 * Called by the pxafb driver
 */
#अगर_अघोषित CONFIG_PCM990_DISPLAY_NONE
अटल व्योम pcm990_lcd_घातer(पूर्णांक on, काष्ठा fb_var_screeninfo *var)
अणु
	अगर (on) अणु
		/* enable LCD-Latches
		 * घातer on LCD
		 */
		pcm990_cpld_ग_लिखोb(PCM990_CTRL_LCDPWR + PCM990_CTRL_LCDON,
				PCM990_CTRL_REG3);
	पूर्ण अन्यथा अणु
		/* disable LCD-Latches
		 * घातer off LCD
		 */
		pcm990_cpld_ग_लिखोb(0, PCM990_CTRL_REG3);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PCM990_DISPLAY_SHARP)
अटल काष्ठा pxafb_mode_info fb_info_sharp_lq084v1dg21 = अणु
	.pixघड़ी		= 28000,
	.xres			= 640,
	.yres			= 480,
	.bpp			= 16,
	.hsync_len		= 20,
	.left_margin		= 103,
	.right_margin		= 47,
	.vsync_len		= 6,
	.upper_margin		= 28,
	.lower_margin		= 5,
	.sync			= 0,
	.cmap_greyscale		= 0,
पूर्ण;

अटल काष्ठा pxafb_mach_info pcm990_fbinfo __initdata = अणु
	.modes			= &fb_info_sharp_lq084v1dg21,
	.num_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
	.pxafb_lcd_घातer	= pcm990_lcd_घातer,
पूर्ण;
#या_अगर defined(CONFIG_PCM990_DISPLAY_NEC)
काष्ठा pxafb_mode_info fb_info_nec_nl6448bc20_18d = अणु
	.pixघड़ी		= 39720,
	.xres			= 640,
	.yres			= 480,
	.bpp			= 16,
	.hsync_len		= 32,
	.left_margin		= 16,
	.right_margin		= 48,
	.vsync_len		= 2,
	.upper_margin		= 12,
	.lower_margin		= 17,
	.sync			= 0,
	.cmap_greyscale		= 0,
पूर्ण;

अटल काष्ठा pxafb_mach_info pcm990_fbinfo __initdata = अणु
	.modes			= &fb_info_nec_nl6448bc20_18d,
	.num_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
	.pxafb_lcd_घातer	= pcm990_lcd_घातer,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा pwm_lookup pcm990_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa27x-pwm.0", 0, "pwm-backlight.0", शून्य, 78770,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा platक्रमm_pwm_backlight_data pcm990_backlight_data = अणु
	.max_brightness	= 1023,
	.dft_brightness	= 1023,
पूर्ण;

अटल काष्ठा platक्रमm_device pcm990_backlight_device = अणु
	.name		= "pwm-backlight",
	.dev		= अणु
		.parent = &pxa27x_device_pwm0.dev,
		.platक्रमm_data = &pcm990_backlight_data,
	पूर्ण,
पूर्ण;

/*
 * The PCM-990 development baseboard uses PCM-027's hardware in the
 * following way:
 *
 * - LCD support is in use
 *  - GPIO16 is output क्रम back light on/off with PWM
 *  - GPIO58 ... GPIO73 are outमाला_दो क्रम display data
 *  - GPIO74 is output output क्रम LCDFCLK
 *  - GPIO75 is output क्रम LCDLCLK
 *  - GPIO76 is output क्रम LCDPCLK
 *  - GPIO77 is output क्रम LCDBIAS
 * - MMC support is in use
 *  - GPIO32 is output क्रम MMCCLK
 *  - GPIO92 is MMDAT0
 *  - GPIO109 is MMDAT1
 *  - GPIO110 is MMCS0
 *  - GPIO111 is MMCS1
 *  - GPIO112 is MMCMD
 * - IDE/CF card is in use
 *  - GPIO48 is output /POE
 *  - GPIO49 is output /PWE
 *  - GPIO50 is output /PIOR
 *  - GPIO51 is output /PIOW
 *  - GPIO54 is output /PCE2
 *  - GPIO55 is output /PREG
 *  - GPIO56 is input /PWAIT
 *  - GPIO57 is output /PIOS16
 *  - GPIO79 is output PSKTSEL
 *  - GPIO85 is output /PCE1
 * - FFUART is in use
 *  - GPIO34 is input FFRXD
 *  - GPIO35 is input FFCTS
 *  - GPIO36 is input FFDCD
 *  - GPIO37 is input FFDSR
 *  - GPIO38 is input FFRI
 *  - GPIO39 is output FFTXD
 *  - GPIO40 is output FFDTR
 *  - GPIO41 is output FFRTS
 * - BTUART is in use
 *  - GPIO42 is input BTRXD
 *  - GPIO43 is output BTTXD
 *  - GPIO44 is input BTCTS
 *  - GPIO45 is output BTRTS
 * - IRUART is in use
 *  - GPIO46 is input STDRXD
 *  - GPIO47 is output STDTXD
 * - AC97 is in use*)
 *  - GPIO28 is input AC97CLK
 *  - GPIO29 is input AC97DatIn
 *  - GPIO30 is output AC97DatO
 *  - GPIO31 is output AC97SYNC
 *  - GPIO113 is output AC97_RESET
 * - SSP is in use
 *  - GPIO23 is output SSPSCLK
 *  - GPIO24 is output chip select to Max7301
 *  - GPIO25 is output SSPTXD
 *  - GPIO26 is input SSPRXD
 *  - GPIO27 is input क्रम Max7301 IRQ
 *  - GPIO53 is input SSPSYSCLK
 * - SSP3 is in use
 *  - GPIO81 is output SSPTXD3
 *  - GPIO82 is input SSPRXD3
 *  - GPIO83 is output SSPSFRM
 *  - GPIO84 is output SSPCLK3
 *
 * Otherwise claimed GPIOs:
 * GPIO1 -> IRQ from user चयन
 * GPIO9 -> IRQ from घातer management
 * GPIO10 -> IRQ from WML9712 AC97 controller
 * GPIO11 -> IRQ from IDE controller
 * GPIO12 -> IRQ from CF controller
 * GPIO13 -> IRQ from CF controller
 * GPIO14 -> GPIO मुक्त
 * GPIO15 -> /CS1 selects baseboard's Control CPLD (U7, 16 bit wide data path)
 * GPIO19 -> GPIO मुक्त
 * GPIO20 -> /SDCS2
 * GPIO21 -> /CS3 PC card socket select
 * GPIO33 -> /CS5  network controller select
 * GPIO78 -> /CS2  (16 bit wide data path)
 * GPIO80 -> /CS4  (16 bit wide data path)
 * GPIO86 -> GPIO मुक्त
 * GPIO87 -> GPIO मुक्त
 * GPIO90 -> LED0 on CPU module
 * GPIO91 -> LED1 on CPI module
 * GPIO117 -> SCL
 * GPIO118 -> SDA
 */

अटल अचिन्हित दीर्घ pcm990_irq_enabled;

अटल व्योम pcm990_mask_ack_irq(काष्ठा irq_data *d)
अणु
	पूर्णांक pcm990_irq = (d->irq - PCM027_IRQ(0));

	pcm990_irq_enabled &= ~(1 << pcm990_irq);

	pcm990_cpld_ग_लिखोb(pcm990_irq_enabled, PCM990_CTRL_INTMSKENA);
पूर्ण

अटल व्योम pcm990_unmask_irq(काष्ठा irq_data *d)
अणु
	पूर्णांक pcm990_irq = (d->irq - PCM027_IRQ(0));
	u8 val;

	/* the irq can be acknowledged only अगर deनिश्चितed, so it's करोne here */

	pcm990_irq_enabled |= (1 << pcm990_irq);

	val = pcm990_cpld_पढ़ोb(PCM990_CTRL_INTSETCLR);
	val |= 1 << pcm990_irq;
	pcm990_cpld_ग_लिखोb(val, PCM990_CTRL_INTSETCLR);

	pcm990_cpld_ग_लिखोb(pcm990_irq_enabled, PCM990_CTRL_INTMSKENA);
पूर्ण

अटल काष्ठा irq_chip pcm990_irq_chip = अणु
	.irq_mask_ack	= pcm990_mask_ack_irq,
	.irq_unmask	= pcm990_unmask_irq,
पूर्ण;

अटल व्योम pcm990_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ pending;

	pending = ~pcm990_cpld_पढ़ोb(PCM990_CTRL_INTSETCLR);
	pending &= pcm990_irq_enabled;

	करो अणु
		/* clear our parent IRQ */
		desc->irq_data.chip->irq_ack(&desc->irq_data);
		अगर (likely(pending)) अणु
			irq = PCM027_IRQ(0) + __ffs(pending);
			generic_handle_irq(irq);
		पूर्ण
		pending = ~pcm990_cpld_पढ़ोb(PCM990_CTRL_INTSETCLR);
		pending &= pcm990_irq_enabled;
	पूर्ण जबतक (pending);
पूर्ण

अटल व्योम __init pcm990_init_irq(व्योम)
अणु
	पूर्णांक irq;

	/* setup extra PCM990 irqs */
	क्रम (irq = PCM027_IRQ(0); irq <= PCM027_IRQ(3); irq++) अणु
		irq_set_chip_and_handler(irq, &pcm990_irq_chip,
					 handle_level_irq);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण

	/* disable all Interrupts */
	pcm990_cpld_ग_लिखोb(0x0, PCM990_CTRL_INTMSKENA);
	pcm990_cpld_ग_लिखोb(0xff, PCM990_CTRL_INTSETCLR);

	irq_set_chained_handler(PCM990_CTRL_INT_IRQ, pcm990_irq_handler);
	irq_set_irq_type(PCM990_CTRL_INT_IRQ, PCM990_CTRL_INT_IRQ_EDGE);
पूर्ण

अटल पूर्णांक pcm990_mci_init(काष्ठा device *dev, irq_handler_t mci_detect_पूर्णांक,
			व्योम *data)
अणु
	पूर्णांक err;

	err = request_irq(PCM027_MMCDET_IRQ, mci_detect_पूर्णांक, 0,
			     "MMC card detect", data);
	अगर (err)
		prपूर्णांकk(KERN_ERR "pcm990_mci_init: MMC/SD: can't request MMC "
				"card detect IRQ\n");

	वापस err;
पूर्ण

अटल पूर्णांक pcm990_mci_setघातer(काष्ठा device *dev, अचिन्हित पूर्णांक vdd)
अणु
	काष्ठा pxamci_platक्रमm_data *p_d = dev->platक्रमm_data;
	u8 val;

	val = pcm990_cpld_पढ़ोb(PCM990_CTRL_REG5);

	अगर ((1 << vdd) & p_d->ocr_mask)
		val |= PCM990_CTRL_MMC2PWR;
	अन्यथा
		val &= ~PCM990_CTRL_MMC2PWR;

	pcm990_cpld_ग_लिखोb(PCM990_CTRL_MMC2PWR, PCM990_CTRL_REG5);
	वापस 0;
पूर्ण

अटल व्योम pcm990_mci_निकास(काष्ठा device *dev, व्योम *data)
अणु
	मुक्त_irq(PCM027_MMCDET_IRQ, data);
पूर्ण

#घोषणा MSECS_PER_JIFFY (1000/HZ)

अटल काष्ठा pxamci_platक्रमm_data pcm990_mci_platक्रमm_data = अणु
	.detect_delay_ms	= 250,
	.ocr_mask		= MMC_VDD_32_33 | MMC_VDD_33_34,
	.init 			= pcm990_mci_init,
	.setघातer 		= pcm990_mci_setघातer,
	.निकास			= pcm990_mci_निकास,
पूर्ण;

अटल काष्ठा pxaohci_platक्रमm_data pcm990_ohci_platक्रमm_data = अणु
	.port_mode	= PMM_PERPORT_MODE,
	.flags		= ENABLE_PORT1 | POWER_CONTROL_LOW | POWER_SENSE_LOW,
	.घातer_on_delay	= 10,
पूर्ण;

/*
 * प्रणाली init क्रम baseboard usage. Will be called by pcm027 init.
 *
 * Add platक्रमm devices present on this baseboard and init
 * them from CPU side as far as required to use them later on
 */
व्योम __init pcm990_baseboard_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(pcm990_pin_config));

	pcm990_cpld_base = ioremap(PCM990_CTRL_PHYS, PCM990_CTRL_SIZE);
	अगर (!pcm990_cpld_base) अणु
		pr_err("pcm990: failed to ioremap cpld\n");
		वापस;
	पूर्ण

	/* रेजिस्टर CPLD's IRQ controller */
	pcm990_init_irq();

#अगर_अघोषित CONFIG_PCM990_DISPLAY_NONE
	pxa_set_fb_info(शून्य, &pcm990_fbinfo);
#पूर्ण_अगर
	pwm_add_table(pcm990_pwm_lookup, ARRAY_SIZE(pcm990_pwm_lookup));
	platक्रमm_device_रेजिस्टर(&pcm990_backlight_device);

	/* MMC */
	pxa_set_mci_info(&pcm990_mci_platक्रमm_data);

	/* USB host */
	pxa_set_ohci_info(&pcm990_ohci_platक्रमm_data);

	pxa_set_i2c_info(शून्य);
	pxa_set_ac97_info(शून्य);

	prपूर्णांकk(KERN_INFO "PCM-990 Evaluation baseboard initialized\n");
पूर्ण
