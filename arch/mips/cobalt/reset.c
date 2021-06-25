<शैली गुरु>
/*
 * Cobalt Reset operations
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1996, 1997 by Ralf Baechle
 * Copyright (C) 2001 by Liam Davies (ldavies@agile.tv)
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/leds.h>

#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/processor.h>

#समावेश <cobalt.h>

#घोषणा RESET_PORT	((व्योम __iomem *)CKSEG1ADDR(0x1c000000))
#घोषणा RESET		0x0f

DEFINE_LED_TRIGGER(घातer_off_led_trigger);

अटल पूर्णांक __init ledtrig_घातer_off_init(व्योम)
अणु
	led_trigger_रेजिस्टर_simple("power-off", &घातer_off_led_trigger);
	वापस 0;
पूर्ण
device_initcall(ledtrig_घातer_off_init);

व्योम cobalt_machine_halt(व्योम)
अणु
	/*
	 * turn on घातer off LED on RaQ
	 */
	led_trigger_event(घातer_off_led_trigger, LED_FULL);

	local_irq_disable();
	जबतक (1) अणु
		अगर (cpu_रुको)
			cpu_रुको();
	पूर्ण
पूर्ण

व्योम cobalt_machine_restart(अक्षर *command)
अणु
	ग_लिखोb(RESET, RESET_PORT);

	/* we should never get here */
	cobalt_machine_halt();
पूर्ण
