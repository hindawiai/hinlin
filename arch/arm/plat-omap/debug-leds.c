<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/plat-omap/debug-leds.c
 *
 * Copyright 2011 by Bryan Wu <bryan.wu@canonical.com>
 * Copyright 2003 by Texas Instruments Incorporated
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_data/gpio-omap.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/mach-types.h>

/* Many OMAP development platक्रमms reuse the same "debug board"; these
 * platक्रमms include H2, H3, H4, and Perseus2.  There are 16 LEDs on the
 * debug board (all green), accessed through FPGA रेजिस्टरs.
 */

/* NOTE:  most boards करोn't have a अटल mapping क्रम the FPGA ... */
काष्ठा h2p2_dbg_fpga अणु
	/* offset 0x00 */
	u16		smc91x[8];
	/* offset 0x10 */
	u16		fpga_rev;
	u16		board_rev;
	u16		gpio_outमाला_दो;
	u16		leds;
	/* offset 0x18 */
	u16		misc_inमाला_दो;
	u16		lan_status;
	u16		lan_reset;
	u16		reserved0;
	/* offset 0x20 */
	u16		ps2_data;
	u16		ps2_ctrl;
	/* plus also 4 rs232 ports ... */
पूर्ण;

अटल काष्ठा h2p2_dbg_fpga __iomem *fpga;

अटल u16 fpga_led_state;

काष्ठा dbg_led अणु
	काष्ठा led_classdev	cdev;
	u16			mask;
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *trigger;
पूर्ण dbg_leds[] = अणु
	अणु "dbg:d4", "heartbeat", पूर्ण,
	अणु "dbg:d5", "cpu0", पूर्ण,
	अणु "dbg:d6", "default-on", पूर्ण,
	अणु "dbg:d7", पूर्ण,
	अणु "dbg:d8", पूर्ण,
	अणु "dbg:d9", पूर्ण,
	अणु "dbg:d10", पूर्ण,
	अणु "dbg:d11", पूर्ण,
	अणु "dbg:d12", पूर्ण,
	अणु "dbg:d13", पूर्ण,
	अणु "dbg:d14", पूर्ण,
	अणु "dbg:d15", पूर्ण,
	अणु "dbg:d16", पूर्ण,
	अणु "dbg:d17", पूर्ण,
	अणु "dbg:d18", पूर्ण,
	अणु "dbg:d19", पूर्ण,
पूर्ण;

/*
 * The triggers lines up below will only be used अगर the
 * LED triggers are compiled in.
 */
अटल व्योम dbg_led_set(काष्ठा led_classdev *cdev,
			      क्रमागत led_brightness b)
अणु
	काष्ठा dbg_led *led = container_of(cdev, काष्ठा dbg_led, cdev);
	u16 reg;

	reg = पढ़ोw_relaxed(&fpga->leds);
	अगर (b != LED_OFF)
		reg |= led->mask;
	अन्यथा
		reg &= ~led->mask;
	ग_लिखोw_relaxed(reg, &fpga->leds);
पूर्ण

अटल क्रमागत led_brightness dbg_led_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा dbg_led *led = container_of(cdev, काष्ठा dbg_led, cdev);
	u16 reg;

	reg = पढ़ोw_relaxed(&fpga->leds);
	वापस (reg & led->mask) ? LED_FULL : LED_OFF;
पूर्ण

अटल पूर्णांक fpga_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource	*iomem;
	पूर्णांक i;

	iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!iomem)
		वापस -ENODEV;

	fpga = ioremap(iomem->start, resource_size(iomem));
	ग_लिखोw_relaxed(0xff, &fpga->leds);

	क्रम (i = 0; i < ARRAY_SIZE(dbg_leds); i++) अणु
		काष्ठा dbg_led *led;

		led = kzalloc(माप(*led), GFP_KERNEL);
		अगर (!led)
			अवरोध;

		led->cdev.name = dbg_leds[i].name;
		led->cdev.brightness_set = dbg_led_set;
		led->cdev.brightness_get = dbg_led_get;
		led->cdev.शेष_trigger = dbg_leds[i].trigger;
		led->mask = BIT(i);

		अगर (led_classdev_रेजिस्टर(शून्य, &led->cdev) < 0) अणु
			kमुक्त(led);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fpga_suspend_noirq(काष्ठा device *dev)
अणु
	fpga_led_state = पढ़ोw_relaxed(&fpga->leds);
	ग_लिखोw_relaxed(0xff, &fpga->leds);

	वापस 0;
पूर्ण

अटल पूर्णांक fpga_resume_noirq(काष्ठा device *dev)
अणु
	ग_लिखोw_relaxed(~fpga_led_state, &fpga->leds);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fpga_dev_pm_ops = अणु
	.suspend_noirq = fpga_suspend_noirq,
	.resume_noirq = fpga_resume_noirq,
पूर्ण;

अटल काष्ठा platक्रमm_driver led_driver = अणु
	.driver.name	= "omap_dbg_led",
	.driver.pm	= &fpga_dev_pm_ops,
	.probe		= fpga_probe,
पूर्ण;

अटल पूर्णांक __init fpga_init(व्योम)
अणु
	अगर (machine_is_omap_h4()
			|| machine_is_omap_h3()
			|| machine_is_omap_h2()
			|| machine_is_omap_perseus2()
			)
		वापस platक्रमm_driver_रेजिस्टर(&led_driver);
	वापस 0;
पूर्ण
fs_initcall(fpga_init);
