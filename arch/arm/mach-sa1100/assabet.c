<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-sa1100/assabet.c
 *
 * Author: Nicolas Pitre
 *
 * This file contains all Assabet-specअगरic tweaks.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/gpio-reg.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/ucb1x00.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>

#समावेश <video/sa1100fb.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgtable-hwdef.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <linux/platक्रमm_data/irda-sa11x0.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <mach/assabet.h>
#समावेश <linux/platक्रमm_data/mfd-mcp-sa11x0.h>
#समावेश <mach/irqs.h>

#समावेश "generic.h"

#घोषणा ASSABET_BCR_DB1110 \
	(ASSABET_BCR_SPK_OFF    | \
	 ASSABET_BCR_LED_GREEN  | ASSABET_BCR_LED_RED   | \
	 ASSABET_BCR_RS232EN    | ASSABET_BCR_LCD_12RGB | \
	 ASSABET_BCR_IRDA_MD0)

#घोषणा ASSABET_BCR_DB1111 \
	(ASSABET_BCR_SPK_OFF    | \
	 ASSABET_BCR_LED_GREEN  | ASSABET_BCR_LED_RED   | \
	 ASSABET_BCR_RS232EN    | ASSABET_BCR_LCD_12RGB | \
	 ASSABET_BCR_CF_BUS_OFF | ASSABET_BCR_STEREO_LB | \
	 ASSABET_BCR_IRDA_MD0   | ASSABET_BCR_CF_RST)

अचिन्हित दीर्घ SCR_value = ASSABET_SCR_INIT;
EXPORT_SYMBOL(SCR_value);

अटल काष्ठा gpio_chip *assabet_bcr_gc;

अटल स्थिर अक्षर *assabet_names[] = अणु
	"cf_pwr", "cf_gfx_reset", "nsoft_reset", "irda_fsel",
	"irda_md0", "irda_md1", "stereo_loopback", "ncf_bus_on",
	"audio_pwr_on", "light_pwr_on", "lcd16data", "lcd_pwr_on",
	"rs232_on", "nred_led", "ngreen_led", "vib_on",
	"com_dtr", "com_rts", "radio_wake_mod", "i2c_enab",
	"tvir_enab", "qmute", "radio_pwr_on", "spkr_off",
	"rs232_valid", "com_dcd", "com_cts", "com_dsr",
	"radio_cts", "radio_dsr", "radio_dcd", "radio_ri",
पूर्ण;

/* The old deprecated पूर्णांकerface */
व्योम ASSABET_BCR_frob(अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित दीर्घ m = mask, v = val;

	assabet_bcr_gc->set_multiple(assabet_bcr_gc, &m, &v);
पूर्ण
EXPORT_SYMBOL(ASSABET_BCR_frob);

अटल पूर्णांक __init assabet_init_gpio(व्योम __iomem *reg, u32 def_val)
अणु
	काष्ठा gpio_chip *gc;

	ग_लिखोl_relaxed(def_val, reg);

	gc = gpio_reg_init(शून्य, reg, -1, 32, "assabet", 0xff000000, def_val,
			   assabet_names, शून्य, शून्य);

	अगर (IS_ERR(gc))
		वापस PTR_ERR(gc);

	assabet_bcr_gc = gc;

	वापस gc->base;
पूर्ण

/*
 * The codec reset goes to three devices, so we need to release
 * the rest when any one of these requests it.  However, that
 * causes the ADV7171 to consume around 100mA - more than half
 * the LCD-blanked घातer.
 *
 * With the ADV7171, LCD and backlight enabled, we go over
 * budget on the MAX846 Li-Ion अक्षरger, and अगर no Li-Ion battery
 * is connected, the Assabet crashes.
 */
#घोषणा RST_UCB1X00 (1 << 0)
#घोषणा RST_UDA1341 (1 << 1)
#घोषणा RST_ADV7171 (1 << 2)

#घोषणा SDA GPIO_GPIO(15)
#घोषणा SCK GPIO_GPIO(18)
#घोषणा MOD GPIO_GPIO(17)

अटल व्योम adv7171_start(व्योम)
अणु
	GPSR = SCK;
	udelay(1);
	GPSR = SDA;
	udelay(2);
	GPCR = SDA;
पूर्ण

अटल व्योम adv7171_stop(व्योम)
अणु
	GPSR = SCK;
	udelay(2);
	GPSR = SDA;
	udelay(1);
पूर्ण

अटल व्योम adv7171_send(अचिन्हित byte)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < 8; i++, byte <<= 1) अणु
		GPCR = SCK;
		udelay(1);
		अगर (byte & 0x80)
			GPSR = SDA;
		अन्यथा
			GPCR = SDA;
		udelay(1);
		GPSR = SCK;
		udelay(1);
	पूर्ण
	GPCR = SCK;
	udelay(1);
	GPSR = SDA;
	udelay(1);
	GPDR &= ~SDA;
	GPSR = SCK;
	udelay(1);
	अगर (GPLR & SDA)
		prपूर्णांकk(KERN_WARNING "No ACK from ADV7171\n");
	udelay(1);
	GPCR = SCK | SDA;
	udelay(1);
	GPDR |= SDA;
	udelay(1);
पूर्ण

अटल व्योम adv7171_ग_लिखो(अचिन्हित reg, अचिन्हित val)
अणु
	अचिन्हित gpdr = GPDR;
	अचिन्हित gplr = GPLR;

	ASSABET_BCR_frob(ASSABET_BCR_AUDIO_ON, ASSABET_BCR_AUDIO_ON);
	udelay(100);

	GPCR = SDA | SCK | MOD; /* clear L3 mode to ensure UDA1341 करोesn't respond */
	GPDR = (GPDR | SCK | MOD) & ~SDA;
	udelay(10);
	अगर (!(GPLR & SDA))
		prपूर्णांकk(KERN_WARNING "Something dragging SDA down?\n");
	GPDR |= SDA;

	adv7171_start();
	adv7171_send(0x54);
	adv7171_send(reg);
	adv7171_send(val);
	adv7171_stop();

	/* Restore GPIO state क्रम L3 bus */
	GPSR = gplr & (SDA | SCK | MOD);
	GPCR = (~gplr) & (SDA | SCK | MOD);
	GPDR = gpdr;
पूर्ण

अटल व्योम adv7171_sleep(व्योम)
अणु
	/* Put the ADV7171 पूर्णांकo sleep mode */
	adv7171_ग_लिखो(0x04, 0x40);
पूर्ण

अटल अचिन्हित codec_nreset;

अटल व्योम assabet_codec_reset(अचिन्हित mask, पूर्णांक set)
अणु
	अचिन्हित दीर्घ flags;
	bool old;

	local_irq_save(flags);
	old = !codec_nreset;
	अगर (set)
		codec_nreset &= ~mask;
	अन्यथा
		codec_nreset |= mask;

	अगर (old != !codec_nreset) अणु
		अगर (codec_nreset) अणु
			ASSABET_BCR_set(ASSABET_BCR_NCODEC_RST);
			adv7171_sleep();
		पूर्ण अन्यथा अणु
			ASSABET_BCR_clear(ASSABET_BCR_NCODEC_RST);
		पूर्ण
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल व्योम assabet_ucb1x00_reset(क्रमागत ucb1x00_reset state)
अणु
	पूर्णांक set = state == UCB_RST_REMOVE || state == UCB_RST_SUSPEND ||
		state == UCB_RST_PROBE_FAIL;
	assabet_codec_reset(RST_UCB1X00, set);
पूर्ण

व्योम assabet_uda1341_reset(पूर्णांक set)
अणु
	assabet_codec_reset(RST_UDA1341, set);
पूर्ण
EXPORT_SYMBOL(assabet_uda1341_reset);


/*
 * Assabet flash support code.
 */

#अगर_घोषित ASSABET_REV_4
/*
 * Phase 4 Assabet has two 28F160B3 flash parts in bank 0:
 */
अटल काष्ठा mtd_partition assabet_partitions[] = अणु
	अणु
		.name		= "bootloader",
		.size		= 0x00020000,
		.offset		= 0,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "bootloader params",
		.size		= 0x00020000,
		.offset		= MTDPART_OFS_APPEND,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "jffs",
		.size		= MTDPART_SIZ_FULL,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण
पूर्ण;
#अन्यथा
/*
 * Phase 5 Assabet has two 28F128J3A flash parts in bank 0:
 */
अटल काष्ठा mtd_partition assabet_partitions[] = अणु
	अणु
		.name		= "bootloader",
		.size		= 0x00040000,
		.offset		= 0,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "bootloader params",
		.size		= 0x00040000,
		.offset		= MTDPART_OFS_APPEND,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "jffs",
		.size		= MTDPART_SIZ_FULL,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा flash_platक्रमm_data assabet_flash_data = अणु
	.map_name	= "cfi_probe",
	.parts		= assabet_partitions,
	.nr_parts	= ARRAY_SIZE(assabet_partitions),
पूर्ण;

अटल काष्ठा resource assabet_flash_resources[] = अणु
	DEFINE_RES_MEM(SA1100_CS0_PHYS, SZ_32M),
	DEFINE_RES_MEM(SA1100_CS1_PHYS, SZ_32M),
पूर्ण;


/*
 * Assabet IrDA support code.
 */

अटल पूर्णांक assabet_irda_set_घातer(काष्ठा device *dev, अचिन्हित पूर्णांक state)
अणु
	अटल अचिन्हित पूर्णांक bcr_state[4] = अणु
		ASSABET_BCR_IRDA_MD0,
		ASSABET_BCR_IRDA_MD1|ASSABET_BCR_IRDA_MD0,
		ASSABET_BCR_IRDA_MD1,
		0
	पूर्ण;

	अगर (state < 4)
		ASSABET_BCR_frob(ASSABET_BCR_IRDA_MD1 | ASSABET_BCR_IRDA_MD0,
				 bcr_state[state]);
	वापस 0;
पूर्ण

अटल व्योम assabet_irda_set_speed(काष्ठा device *dev, अचिन्हित पूर्णांक speed)
अणु
	अगर (speed < 4000000)
		ASSABET_BCR_clear(ASSABET_BCR_IRDA_FSEL);
	अन्यथा
		ASSABET_BCR_set(ASSABET_BCR_IRDA_FSEL);
पूर्ण

अटल काष्ठा irda_platक्रमm_data assabet_irda_data = अणु
	.set_घातer	= assabet_irda_set_घातer,
	.set_speed	= assabet_irda_set_speed,
पूर्ण;

अटल काष्ठा ucb1x00_plat_data assabet_ucb1x00_data = अणु
	.reset		= assabet_ucb1x00_reset,
	.gpio_base	= -1,
	.can_wakeup	= 1,
पूर्ण;

अटल काष्ठा mcp_plat_data assabet_mcp_data = अणु
	.mccr0		= MCCR0_ADM,
	.sclk_rate	= 11981000,
	.codec_pdata	= &assabet_ucb1x00_data,
पूर्ण;

अटल व्योम assabet_lcd_set_visual(u32 visual)
अणु
	u_पूर्णांक is_true_color = visual == FB_VISUAL_TRUECOLOR;

	अगर (machine_is_assabet()) अणु
#अगर 1		// phase 4 or newer Assabet's
		अगर (is_true_color)
			ASSABET_BCR_set(ASSABET_BCR_LCD_12RGB);
		अन्यथा
			ASSABET_BCR_clear(ASSABET_BCR_LCD_12RGB);
#अन्यथा
		// older Assabet's
		अगर (is_true_color)
			ASSABET_BCR_clear(ASSABET_BCR_LCD_12RGB);
		अन्यथा
			ASSABET_BCR_set(ASSABET_BCR_LCD_12RGB);
#पूर्ण_अगर
	पूर्ण
पूर्ण

#अगर_अघोषित ASSABET_PAL_VIDEO
अटल व्योम assabet_lcd_backlight_घातer(पूर्णांक on)
अणु
	अगर (on)
		ASSABET_BCR_set(ASSABET_BCR_LIGHT_ON);
	अन्यथा
		ASSABET_BCR_clear(ASSABET_BCR_LIGHT_ON);
पूर्ण

/*
 * Turn on/off the backlight.  When turning the backlight on, we रुको
 * 500us after turning it on so we करोn't cause the supplies to droop
 * when we enable the LCD controller (and cause a hard reset.)
 */
अटल व्योम assabet_lcd_घातer(पूर्णांक on)
अणु
	अगर (on) अणु
		ASSABET_BCR_set(ASSABET_BCR_LCD_ON);
		udelay(500);
	पूर्ण अन्यथा
		ASSABET_BCR_clear(ASSABET_BCR_LCD_ON);
पूर्ण

/*
 * The assabet uses a sharp LQ039Q2DS54 LCD module.  It is actually
 * takes an RGB666 संकेत, but we provide it with an RGB565 संकेत
 * instead (def_rgb_16).
 */
अटल काष्ठा sa1100fb_mach_info lq039q2ds54_info = अणु
	.pixघड़ी	= 171521,	.bpp		= 16,
	.xres		= 320,		.yres		= 240,

	.hsync_len	= 5,		.vsync_len	= 1,
	.left_margin	= 61,		.upper_margin	= 3,
	.right_margin	= 9,		.lower_margin	= 0,

	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,

	.lccr0		= LCCR0_Color | LCCR0_Sngl | LCCR0_Act,
	.lccr3		= LCCR3_OutEnH | LCCR3_PixRsEdg | LCCR3_ACBsDiv(2),

	.backlight_घातer = assabet_lcd_backlight_घातer,
	.lcd_घातer = assabet_lcd_घातer,
	.set_visual = assabet_lcd_set_visual,
पूर्ण;
#अन्यथा
अटल व्योम assabet_pal_backlight_घातer(पूर्णांक on)
अणु
	ASSABET_BCR_clear(ASSABET_BCR_LIGHT_ON);
पूर्ण

अटल व्योम assabet_pal_घातer(पूर्णांक on)
अणु
	ASSABET_BCR_clear(ASSABET_BCR_LCD_ON);
पूर्ण

अटल काष्ठा sa1100fb_mach_info pal_info = अणु
	.pixघड़ी	= 67797,	.bpp		= 16,
	.xres		= 640,		.yres		= 512,

	.hsync_len	= 64,		.vsync_len	= 6,
	.left_margin	= 125,		.upper_margin	= 70,
	.right_margin	= 115,		.lower_margin	= 36,

	.lccr0		= LCCR0_Color | LCCR0_Sngl | LCCR0_Act,
	.lccr3		= LCCR3_OutEnH | LCCR3_PixRsEdg | LCCR3_ACBsDiv(512),

	.backlight_घातer = assabet_pal_backlight_घातer,
	.lcd_घातer = assabet_pal_घातer,
	.set_visual = assabet_lcd_set_visual,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ASSABET_NEPONSET
अटल काष्ठा resource neponset_resources[] = अणु
	DEFINE_RES_MEM(0x10000000, 0x08000000),
	DEFINE_RES_MEM(0x18000000, 0x04000000),
	DEFINE_RES_MEM(0x40000000, SZ_8K),
	DEFINE_RES_IRQ(IRQ_GPIO25),
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा gpiod_lookup_table assabet_cf_gpio_table = अणु
	.dev_id = "sa11x0-pcmcia.1",
	.table = अणु
		GPIO_LOOKUP("gpio", 21, "ready", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio", 22, "detect", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio", 24, "bvd2", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio", 25, "bvd1", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("assabet", 1, "reset", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("assabet", 7, "bus-enable", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा regulator_consumer_supply assabet_cf_vcc_consumers[] = अणु
	REGULATOR_SUPPLY("vcc", "sa11x0-pcmcia.1"),
पूर्ण;

अटल काष्ठा fixed_voltage_config assabet_cf_vcc_pdata __initdata = अणु
	.supply_name = "cf-power",
	.microvolts = 3300000,
पूर्ण;

अटल काष्ठा gpiod_lookup_table assabet_cf_vcc_gpio_table = अणु
	.dev_id = "reg-fixed-voltage.0",
	.table = अणु
		GPIO_LOOKUP("assabet", 0, शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led assabet_leds[] __initdata = अणु
	अणु
		.name = "assabet:red",
		.शेष_trigger = "cpu0",
		.active_low = 1,
		.शेष_state = LEDS_GPIO_DEFSTATE_KEEP,
	पूर्ण, अणु
		.name = "assabet:green",
		.शेष_trigger = "heartbeat",
		.active_low = 1,
		.शेष_state = LEDS_GPIO_DEFSTATE_KEEP,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led_platक्रमm_data assabet_leds_pdata __initस्थिर = अणु
	.num_leds = ARRAY_SIZE(assabet_leds),
	.leds = assabet_leds,
पूर्ण;

अटल काष्ठा gpio_keys_button assabet_keys_buttons[] = अणु
	अणु
		.gpio = 0,
		.irq = IRQ_GPIO0,
		.desc = "gpio0",
		.wakeup = 1,
		.can_disable = 1,
		.debounce_पूर्णांकerval = 5,
	पूर्ण, अणु
		.gpio = 1,
		.irq = IRQ_GPIO1,
		.desc = "gpio1",
		.wakeup = 1,
		.can_disable = 1,
		.debounce_पूर्णांकerval = 5,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_keys_platक्रमm_data assabet_keys_pdata = अणु
	.buttons = assabet_keys_buttons,
	.nbuttons = ARRAY_SIZE(assabet_keys_buttons),
	.rep = 0,
पूर्ण;

अटल काष्ठा gpiod_lookup_table assabet_uart1_gpio_table = अणु
	.dev_id = "sa11x0-uart.1",
	.table = अणु
		GPIO_LOOKUP("assabet", 16, "dtr", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("assabet", 17, "rts", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("assabet", 25, "dcd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("assabet", 26, "cts", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("assabet", 27, "dsr", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table assabet_uart3_gpio_table = अणु
	.dev_id = "sa11x0-uart.3",
	.table = अणु
		GPIO_LOOKUP("assabet", 28, "cts", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("assabet", 29, "dsr", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("assabet", 30, "dcd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("assabet", 31, "rng", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init assabet_init(व्योम)
अणु
	/*
	 * Ensure that the घातer supply is in "high power" mode.
	 */
	GPSR = GPIO_GPIO16;
	GPDR |= GPIO_GPIO16;

	/*
	 * Ensure that these pins are set as outमाला_दो and are driving
	 * logic 0.  This ensures that we won't inadvertently toggle
	 * the WS latch in the CPLD, and we करोn't भग्न causing
	 * excessive घातer drain.  --rmk
	 */
	GPCR = GPIO_SSP_TXD | GPIO_SSP_SCLK | GPIO_SSP_SFRM;
	GPDR |= GPIO_SSP_TXD | GPIO_SSP_SCLK | GPIO_SSP_SFRM;

	/*
	 * Also set GPIO27 as an output; this is used to घड़ी UART3
	 * via the FPGA and as otherwise has no pullups or pullकरोwns,
	 * so stop it भग्नing.
	 */
	GPCR = GPIO_GPIO27;
	GPDR |= GPIO_GPIO27;

	/*
	 * Set up रेजिस्टरs क्रम sleep mode.
	 */
	PWER = PWER_GPIO0;
	PGSR = 0;
	PCFR = 0;
	PSDR = 0;
	PPDR |= PPC_TXD3 | PPC_TXD1;
	PPSR |= PPC_TXD3 | PPC_TXD1;

	sa11x0_ppc_configure_mcp();

	अगर (machine_has_neponset()) अणु
#अगर_अघोषित CONFIG_ASSABET_NEPONSET
		prपूर्णांकk( "Warning: Neponset detected but full support "
			"hasn't been configured in the kernel\n" );
#अन्यथा
		platक्रमm_device_रेजिस्टर_simple("neponset", 0,
			neponset_resources, ARRAY_SIZE(neponset_resources));
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		gpiod_add_lookup_table(&assabet_uart1_gpio_table);
		gpiod_add_lookup_table(&assabet_uart3_gpio_table);
		gpiod_add_lookup_table(&assabet_cf_vcc_gpio_table);

		sa11x0_रेजिस्टर_fixed_regulator(0, &assabet_cf_vcc_pdata,
					assabet_cf_vcc_consumers,
					ARRAY_SIZE(assabet_cf_vcc_consumers),
					true);

	पूर्ण

	platक्रमm_device_रेजिस्टर_resndata(शून्य, "gpio-keys", 0,
					  शून्य, 0,
					  &assabet_keys_pdata,
					  माप(assabet_keys_pdata));

	gpio_led_रेजिस्टर_device(-1, &assabet_leds_pdata);

#अगर_अघोषित ASSABET_PAL_VIDEO
	sa11x0_रेजिस्टर_lcd(&lq039q2ds54_info);
#अन्यथा
	sa11x0_रेजिस्टर_lcd(&pal_video);
#पूर्ण_अगर
	sa11x0_रेजिस्टर_mtd(&assabet_flash_data, assabet_flash_resources,
			    ARRAY_SIZE(assabet_flash_resources));
	sa11x0_रेजिस्टर_irda(&assabet_irda_data);
	sa11x0_रेजिस्टर_mcp(&assabet_mcp_data);

	अगर (!machine_has_neponset())
		sa11x0_रेजिस्टर_pcmcia(1, &assabet_cf_gpio_table);
पूर्ण

/*
 * On Assabet, we must probe क्रम the Neponset board _beक्रमe_
 * paging_init() has occurred to actually determine the amount
 * of RAM available.  To करो so, we map the appropriate IO section
 * in the page table here in order to access GPIO रेजिस्टरs.
 */
अटल व्योम __init map_sa1100_gpio_regs( व्योम )
अणु
	अचिन्हित दीर्घ phys = __PREG(GPLR) & PMD_MASK;
	अचिन्हित दीर्घ virt = (अचिन्हित दीर्घ)io_p2v(phys);
	पूर्णांक prot = PMD_TYPE_SECT | PMD_SECT_AP_WRITE | PMD_DOMAIN(DOMAIN_IO);
	pmd_t *pmd;

	pmd = pmd_off_k(virt);
	*pmd = __pmd(phys | prot);
	flush_pmd_entry(pmd);
पूर्ण

/*
 * Read System Configuration "Register"
 * (taken from "Intel StrongARM SA-1110 Microprocessor Development Board
 * User's Guide", section 4.4.1)
 *
 * This same scan is perक्रमmed in arch/arm/boot/compressed/head-sa1100.S
 * to set up the serial port क्रम decompression status messages. We
 * repeat it here because the kernel may not be loaded as a zImage, and
 * also because it's a hassle to communicate the SCR value to the kernel
 * from the decompressor.
 *
 * Note that IRQs are guaranteed to be disabled.
 */
अटल व्योम __init get_assabet_scr(व्योम)
अणु
	अचिन्हित दीर्घ scr, i;

	GPDR |= 0x3fc;			/* Configure GPIO 9:2 as outमाला_दो */
	GPSR = 0x3fc;			/* Write 0xFF to GPIO 9:2 */
	GPDR &= ~(0x3fc);		/* Configure GPIO 9:2 as inमाला_दो */
	क्रम(i = 100; i--; )		/* Read GPIO 9:2 */
		scr = GPLR;
	GPDR |= 0x3fc;			/*  restore correct pin direction */
	scr &= 0x3fc;			/* save as प्रणाली configuration byte. */
	SCR_value = scr;
पूर्ण

अटल व्योम __init
fixup_assabet(काष्ठा tag *tags, अक्षर **cmdline)
अणु
	/* This must be करोne beक्रमe any call to machine_has_neponset() */
	map_sa1100_gpio_regs();
	get_assabet_scr();

	अगर (machine_has_neponset())
		prपूर्णांकk("Neponset expansion board detected\n");
पूर्ण


अटल व्योम assabet_uart_pm(काष्ठा uart_port *port, u_पूर्णांक state, u_पूर्णांक oldstate)
अणु
	अगर (port->mapbase == _Ser1UTCR0) अणु
		अगर (state)
			ASSABET_BCR_clear(ASSABET_BCR_RS232EN);
		अन्यथा
			ASSABET_BCR_set(ASSABET_BCR_RS232EN);
	पूर्ण
पूर्ण

अटल काष्ठा sa1100_port_fns assabet_port_fns __initdata = अणु
	.pm		= assabet_uart_pm,
पूर्ण;

अटल काष्ठा map_desc assabet_io_desc[] __initdata = अणु
  	अणु	/* Board Control Register */
		.भव	=  0xf1000000,
		.pfn		= __phys_to_pfn(0x12000000),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* MQ200 */
		.भव	=  0xf2800000,
		.pfn		= __phys_to_pfn(0x4b800000),
		.length		= 0x00800000,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init assabet_map_io(व्योम)
अणु
	sa1100_map_io();
	iotable_init(assabet_io_desc, ARRAY_SIZE(assabet_io_desc));

	/*
	 * Set SUS bit in SDCR0 so serial port 1 functions.
	 * Its called GPCLKR0 in my SA1110 manual.
	 */
	Ser1SDCR0 |= SDCR0_SUS;
	MSC1 = (MSC1 & ~0xffff) |
		MSC_NonBrst | MSC_32BitStMem |
		MSC_RdAcc(2) | MSC_WrAcc(2) | MSC_Rec(0);

	अगर (!machine_has_neponset())
		sa1100_रेजिस्टर_uart_fns(&assabet_port_fns);

	/*
	 * When Neponset is attached, the first UART should be
	 * UART3.  That's what Angel is करोing and many करोcuments
	 * are stating this.
	 *
	 * We करो the Neponset mapping even अगर Neponset support
	 * isn't compiled in so the user will still get something on
	 * the expected physical serial port.
	 *
	 * We no दीर्घer करो this; not all boot loaders support it,
	 * and UART3 appears to be somewhat unreliable with blob.
	 */
	sa1100_रेजिस्टर_uart(0, 1);
	sa1100_रेजिस्टर_uart(2, 3);
पूर्ण

व्योम __init assabet_init_irq(व्योम)
अणु
	अचिन्हित पूर्णांक assabet_gpio_base;
	u32 def_val;

	sa1100_init_irq();

	अगर (machine_has_neponset())
		def_val = ASSABET_BCR_DB1111;
	अन्यथा
		def_val = ASSABET_BCR_DB1110;

	/*
	 * Angel sets this, but other bootloaders may not.
	 *
	 * This must precede any driver calls to BCR_set() or BCR_clear().
	 */
	assabet_gpio_base = assabet_init_gpio((व्योम *)&ASSABET_BCR, def_val);

	assabet_leds[0].gpio = assabet_gpio_base + 13;
	assabet_leds[1].gpio = assabet_gpio_base + 14;
पूर्ण

MACHINE_START(ASSABET, "Intel-Assabet")
	.atag_offset	= 0x100,
	.fixup		= fixup_assabet,
	.map_io		= assabet_map_io,
	.nr_irqs	= SA1100_NR_IRQS,
	.init_irq	= assabet_init_irq,
	.init_समय	= sa1100_समयr_init,
	.init_machine	= assabet_init,
	.init_late	= sa11x0_init_late,
#अगर_घोषित CONFIG_SA1111
	.dma_zone_size	= SZ_1M,
#पूर्ण_अगर
	.restart	= sa11x0_restart,
MACHINE_END
