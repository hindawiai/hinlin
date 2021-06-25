<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Clock event driver क्रम the CS5535/CS5536
 *
 * Copyright (C) 2006, Advanced Micro Devices, Inc.
 * Copyright (C) 2007  Andres Salomon <dilinger@debian.org>
 * Copyright (C) 2009  Andres Salomon <dilinger@collabora.co.uk>
 *
 * The MFGPTs are करोcumented in AMD Geode CS5536 Companion Device Data Book.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/cs5535.h>
#समावेश <linux/घड़ीchips.h>

#घोषणा DRV_NAME "cs5535-clockevt"

अटल पूर्णांक समयr_irq;
module_param_hw_named(irq, समयr_irq, पूर्णांक, irq, 0644);
MODULE_PARM_DESC(irq, "Which IRQ to use for the clock source MFGPT ticks.");

/*
 * We are using the 32.768kHz input घड़ी - it's the only one that has the
 * ranges we find desirable.  The following table lists the suitable
 * भागisors and the associated Hz, minimum पूर्णांकerval and the maximum पूर्णांकerval:
 *
 *  Divisor   Hz      Min Delta (s)  Max Delta (s)
 *   1        32768   .00048828125      2.000
 *   2        16384   .0009765625       4.000
 *   4         8192   .001953125        8.000
 *   8         4096   .00390625        16.000
 *   16        2048   .0078125         32.000
 *   32        1024   .015625          64.000
 *   64         512   .03125          128.000
 *  128         256   .0625           256.000
 *  256         128   .125            512.000
 */

अटल काष्ठा cs5535_mfgpt_समयr *cs5535_event_घड़ी;

/* Selected from the table above */

#घोषणा MFGPT_DIVISOR 16
#घोषणा MFGPT_SCALE  4     /* भागisor = 2^(scale) */
#घोषणा MFGPT_HZ  (32768 / MFGPT_DIVISOR)
#घोषणा MFGPT_PERIODIC (MFGPT_HZ / HZ)

/*
 * The MFGPT समयrs on the CS5536 provide us with suitable समयrs to use
 * as घड़ी event sources - not as good as a HPET or APIC, but certainly
 * better than the PIT.  This isn't a general purpose MFGPT driver, but
 * a simplअगरied one deचिन्हित specअगरically to act as a घड़ी event source.
 * For full details about the MFGPT, please consult the CS5536 data sheet.
 */

अटल व्योम disable_समयr(काष्ठा cs5535_mfgpt_समयr *समयr)
अणु
	/* aव्योम races by clearing CMP1 and CMP2 unconditionally */
	cs5535_mfgpt_ग_लिखो(समयr, MFGPT_REG_SETUP,
			(uपूर्णांक16_t) ~MFGPT_SETUP_CNTEN | MFGPT_SETUP_CMP1 |
				MFGPT_SETUP_CMP2);
पूर्ण

अटल व्योम start_समयr(काष्ठा cs5535_mfgpt_समयr *समयr, uपूर्णांक16_t delta)
अणु
	cs5535_mfgpt_ग_लिखो(समयr, MFGPT_REG_CMP2, delta);
	cs5535_mfgpt_ग_लिखो(समयr, MFGPT_REG_COUNTER, 0);

	cs5535_mfgpt_ग_लिखो(समयr, MFGPT_REG_SETUP,
			MFGPT_SETUP_CNTEN | MFGPT_SETUP_CMP2);
पूर्ण

अटल पूर्णांक mfgpt_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	disable_समयr(cs5535_event_घड़ी);
	वापस 0;
पूर्ण

अटल पूर्णांक mfgpt_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	disable_समयr(cs5535_event_घड़ी);
	start_समयr(cs5535_event_घड़ी, MFGPT_PERIODIC);
	वापस 0;
पूर्ण

अटल पूर्णांक mfgpt_next_event(अचिन्हित दीर्घ delta, काष्ठा घड़ी_event_device *evt)
अणु
	start_समयr(cs5535_event_घड़ी, delta);
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device cs5535_घड़ीevent = अणु
	.name = DRV_NAME,
	.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
	.set_state_shutकरोwn = mfgpt_shutकरोwn,
	.set_state_periodic = mfgpt_set_periodic,
	.set_state_oneshot = mfgpt_shutकरोwn,
	.tick_resume = mfgpt_shutकरोwn,
	.set_next_event = mfgpt_next_event,
	.rating = 250,
पूर्ण;

अटल irqवापस_t mfgpt_tick(पूर्णांक irq, व्योम *dev_id)
अणु
	uपूर्णांक16_t val = cs5535_mfgpt_पढ़ो(cs5535_event_घड़ी, MFGPT_REG_SETUP);

	/* See अगर the पूर्णांकerrupt was क्रम us */
	अगर (!(val & (MFGPT_SETUP_SETUP | MFGPT_SETUP_CMP2 | MFGPT_SETUP_CMP1)))
		वापस IRQ_NONE;

	/* Turn off the घड़ी (and clear the event) */
	disable_समयr(cs5535_event_घड़ी);

	अगर (घड़ीevent_state_detached(&cs5535_घड़ीevent) ||
	    घड़ीevent_state_shutकरोwn(&cs5535_घड़ीevent))
		वापस IRQ_HANDLED;

	/* Clear the counter */
	cs5535_mfgpt_ग_लिखो(cs5535_event_घड़ी, MFGPT_REG_COUNTER, 0);

	/* Restart the घड़ी in periodic mode */

	अगर (घड़ीevent_state_periodic(&cs5535_घड़ीevent))
		cs5535_mfgpt_ग_लिखो(cs5535_event_घड़ी, MFGPT_REG_SETUP,
				MFGPT_SETUP_CNTEN | MFGPT_SETUP_CMP2);

	cs5535_घड़ीevent.event_handler(&cs5535_घड़ीevent);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init cs5535_mfgpt_init(व्योम)
अणु
	अचिन्हित दीर्घ flags = IRQF_NOBALANCING | IRQF_TIMER | IRQF_SHARED;
	काष्ठा cs5535_mfgpt_समयr *समयr;
	पूर्णांक ret;
	uपूर्णांक16_t val;

	समयr = cs5535_mfgpt_alloc_समयr(MFGPT_TIMER_ANY, MFGPT_DOMAIN_WORKING);
	अगर (!समयr) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": Could not allocate MFGPT timer\n");
		वापस -ENODEV;
	पूर्ण
	cs5535_event_घड़ी = समयr;

	/* Set up the IRQ on the MFGPT side */
	अगर (cs5535_mfgpt_setup_irq(समयr, MFGPT_CMP2, &समयr_irq)) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": Could not set up IRQ %d\n",
				समयr_irq);
		जाओ err_समयr;
	पूर्ण

	/* And रेजिस्टर it with the kernel */
	ret = request_irq(समयr_irq, mfgpt_tick, flags, DRV_NAME, समयr);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": Unable to set up the interrupt.\n");
		जाओ err_irq;
	पूर्ण

	/* Set the घड़ी scale and enable the event mode क्रम CMP2 */
	val = MFGPT_SCALE | (3 << 8);

	cs5535_mfgpt_ग_लिखो(cs5535_event_घड़ी, MFGPT_REG_SETUP, val);

	/* Set up the घड़ी event */
	prपूर्णांकk(KERN_INFO DRV_NAME
		": Registering MFGPT timer as a clock event, using IRQ %d\n",
		समयr_irq);
	घड़ीevents_config_and_रेजिस्टर(&cs5535_घड़ीevent, MFGPT_HZ,
					0xF, 0xFFFE);

	वापस 0;

err_irq:
	cs5535_mfgpt_release_irq(cs5535_event_घड़ी, MFGPT_CMP2, &समयr_irq);
err_समयr:
	cs5535_mfgpt_मुक्त_समयr(cs5535_event_घड़ी);
	prपूर्णांकk(KERN_ERR DRV_NAME ": Unable to set up the MFGPT clock source\n");
	वापस -EIO;
पूर्ण

module_init(cs5535_mfgpt_init);

MODULE_AUTHOR("Andres Salomon <dilinger@queued.net>");
MODULE_DESCRIPTION("CS5535/CS5536 MFGPT clock event driver");
MODULE_LICENSE("GPL");
