<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/arm/mach-footbridge/ebsa285.c
 *
 * EBSA285 machine fixup
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>

#समावेश <यंत्र/hardware/dec21285.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <यंत्र/mach/arch.h>

#समावेश "common.h"

/* LEDs */
#अगर defined(CONFIG_NEW_LEDS) && defined(CONFIG_LEDS_CLASS)
#घोषणा XBUS_AMBER_L	BIT(0)
#घोषणा XBUS_GREEN_L	BIT(1)
#घोषणा XBUS_RED_L	BIT(2)
#घोषणा XBUS_TOGGLE	BIT(7)

काष्ठा ebsa285_led अणु
	काष्ठा led_classdev     cdev;
	u8                      mask;
पूर्ण;

/*
 * The triggers lines up below will only be used अगर the
 * LED triggers are compiled in.
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *trigger;
पूर्ण ebsa285_leds[] = अणु
	अणु "ebsa285:amber", "cpu0", पूर्ण,
	अणु "ebsa285:green", "heartbeat", पूर्ण,
	अणु "ebsa285:red",पूर्ण,
पूर्ण;

अटल अचिन्हित अक्षर hw_led_state;
अटल व्योम __iomem *xbus;

अटल व्योम ebsa285_led_set(काष्ठा led_classdev *cdev,
		क्रमागत led_brightness b)
अणु
	काष्ठा ebsa285_led *led = container_of(cdev,
			काष्ठा ebsa285_led, cdev);

	अगर (b == LED_OFF)
		hw_led_state |= led->mask;
	अन्यथा
		hw_led_state &= ~led->mask;
	ग_लिखोb(hw_led_state, xbus);
पूर्ण

अटल क्रमागत led_brightness ebsa285_led_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा ebsa285_led *led = container_of(cdev,
			काष्ठा ebsa285_led, cdev);

	वापस hw_led_state & led->mask ? LED_OFF : LED_FULL;
पूर्ण

अटल पूर्णांक __init ebsa285_leds_init(व्योम)
अणु
	पूर्णांक i;

	अगर (!machine_is_ebsa285())
		वापस -ENODEV;

	xbus = ioremap(XBUS_CS2, SZ_4K);
	अगर (!xbus)
		वापस -ENOMEM;

	/* 3 LEDS all off */
	hw_led_state = XBUS_AMBER_L | XBUS_GREEN_L | XBUS_RED_L;
	ग_लिखोb(hw_led_state, xbus);

	क्रम (i = 0; i < ARRAY_SIZE(ebsa285_leds); i++) अणु
		काष्ठा ebsa285_led *led;

		led = kzalloc(माप(*led), GFP_KERNEL);
		अगर (!led)
			अवरोध;

		led->cdev.name = ebsa285_leds[i].name;
		led->cdev.brightness_set = ebsa285_led_set;
		led->cdev.brightness_get = ebsa285_led_get;
		led->cdev.शेष_trigger = ebsa285_leds[i].trigger;
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
fs_initcall(ebsa285_leds_init);
#पूर्ण_अगर

MACHINE_START(EBSA285, "EBSA285")
	/* Maपूर्णांकainer: Russell King */
	.atag_offset	= 0x100,
	.video_start	= 0x000a0000,
	.video_end	= 0x000bffff,
	.map_io		= footbridge_map_io,
	.init_early	= footbridge_sched_घड़ी,
	.init_irq	= footbridge_init_irq,
	.init_समय	= footbridge_समयr_init,
	.restart	= footbridge_restart,
MACHINE_END

