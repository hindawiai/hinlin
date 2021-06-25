<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dm355evm_keys.c - support buttons and IR remote on DM355 EVM board
 *
 * Copyright (c) 2008 by David Brownell
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/mfd/dm355evm_msp.h>
#समावेश <linux/module.h>


/*
 * The MSP430 firmware on the DM355 EVM monitors on-board pushbuttons
 * and an IR receptor used क्रम the remote control.  When any key is
 * pressed, or its स्वतःrepeat kicks in, an event is sent.  This driver
 * पढ़ो those events from the small (32 event) queue and reports them.
 *
 * Note that physically there can only be one of these devices.
 *
 * This driver was tested with firmware revision A4.
 */
काष्ठा dm355evm_keys अणु
	काष्ठा input_dev	*input;
	काष्ठा device		*dev;
पूर्ण;

/* These initial keycodes can be remapped */
अटल स्थिर काष्ठा key_entry dm355evm_keys[] = अणु
	/*
	 * Pushbuttons on the EVM board ... note that the labels क्रम these
	 * are SW10/SW11/etc on the PC board.  The left/right orientation
	 * comes only from the firmware's करोcumentation, and presumes the
	 * घातer connector is immediately in front of you and the IR sensor
	 * is to the right.  (That is, rotate the board counter-घड़ीwise
	 * by 90 degrees from the SW10/etc and "DM355 EVM" labels.)
	 */
	अणु KE_KEY, 0x00d8, अणु KEY_OK पूर्ण पूर्ण,		/* SW12 */
	अणु KE_KEY, 0x00b8, अणु KEY_UP पूर्ण पूर्ण,		/* SW13 */
	अणु KE_KEY, 0x00e8, अणु KEY_DOWN पूर्ण पूर्ण,	/* SW11 */
	अणु KE_KEY, 0x0078, अणु KEY_LEFT पूर्ण पूर्ण,	/* SW14 */
	अणु KE_KEY, 0x00f0, अणु KEY_RIGHT पूर्ण पूर्ण,	/* SW10 */

	/*
	 * IR buttons ... codes asचिन्हित to match the universal remote
	 * provided with the EVM (Philips PM4S) using DVD code 0020.
	 *
	 * These event codes match firmware करोcumentation, but other
	 * remote controls could easily send more RC5-encoded events.
	 * The PM4S manual was used in several हालs to help select
	 * a keycode reflecting the पूर्णांकended usage.
	 *
	 * RC5 codes are 14 bits, with two start bits (0x3 prefix)
	 * and a toggle bit (masked out below).
	 */
	अणु KE_KEY, 0x300c, अणु KEY_POWER पूर्ण पूर्ण,	/* NOTE: करोcs omit this */
	अणु KE_KEY, 0x3000, अणु KEY_NUMERIC_0 पूर्ण पूर्ण,
	अणु KE_KEY, 0x3001, अणु KEY_NUMERIC_1 पूर्ण पूर्ण,
	अणु KE_KEY, 0x3002, अणु KEY_NUMERIC_2 पूर्ण पूर्ण,
	अणु KE_KEY, 0x3003, अणु KEY_NUMERIC_3 पूर्ण पूर्ण,
	अणु KE_KEY, 0x3004, अणु KEY_NUMERIC_4 पूर्ण पूर्ण,
	अणु KE_KEY, 0x3005, अणु KEY_NUMERIC_5 पूर्ण पूर्ण,
	अणु KE_KEY, 0x3006, अणु KEY_NUMERIC_6 पूर्ण पूर्ण,
	अणु KE_KEY, 0x3007, अणु KEY_NUMERIC_7 पूर्ण पूर्ण,
	अणु KE_KEY, 0x3008, अणु KEY_NUMERIC_8 पूर्ण पूर्ण,
	अणु KE_KEY, 0x3009, अणु KEY_NUMERIC_9 पूर्ण पूर्ण,
	अणु KE_KEY, 0x3022, अणु KEY_ENTER पूर्ण पूर्ण,
	अणु KE_KEY, 0x30ec, अणु KEY_MODE पूर्ण पूर्ण,	/* "tv/vcr/..." */
	अणु KE_KEY, 0x300f, अणु KEY_SELECT पूर्ण पूर्ण,	/* "info" */
	अणु KE_KEY, 0x3020, अणु KEY_CHANNELUP पूर्ण पूर्ण,	/* "up" */
	अणु KE_KEY, 0x302e, अणु KEY_MENU पूर्ण पूर्ण,	/* "in/out" */
	अणु KE_KEY, 0x3011, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,	/* "left" */
	अणु KE_KEY, 0x300d, अणु KEY_MUTE पूर्ण पूर्ण,	/* "ok" */
	अणु KE_KEY, 0x3010, अणु KEY_VOLUMEUP पूर्ण पूर्ण,	/* "right" */
	अणु KE_KEY, 0x301e, अणु KEY_SUBTITLE पूर्ण पूर्ण,	/* "cc" */
	अणु KE_KEY, 0x3021, अणु KEY_CHANNELDOWN पूर्ण पूर्ण,/* "down" */
	अणु KE_KEY, 0x3022, अणु KEY_PREVIOUS पूर्ण पूर्ण,
	अणु KE_KEY, 0x3026, अणु KEY_SLEEP पूर्ण पूर्ण,
	अणु KE_KEY, 0x3172, अणु KEY_REWIND पूर्ण पूर्ण,	/* NOTE: करोcs wrongly say 0x30ca */
	अणु KE_KEY, 0x3175, अणु KEY_PLAY पूर्ण पूर्ण,
	अणु KE_KEY, 0x3174, अणु KEY_FASTFORWARD पूर्ण पूर्ण,
	अणु KE_KEY, 0x3177, अणु KEY_RECORD पूर्ण पूर्ण,
	अणु KE_KEY, 0x3176, अणु KEY_STOP पूर्ण पूर्ण,
	अणु KE_KEY, 0x3169, अणु KEY_PAUSE पूर्ण पूर्ण,
पूर्ण;

/*
 * Because we communicate with the MSP430 using I2C, and all I2C calls
 * in Linux sleep, we use a thपढ़ोed IRQ handler.  The IRQ itself is
 * active low, but we go through the GPIO controller so we can trigger
 * on falling edges and not worry about enabling/disabling the IRQ in
 * the keypress handling path.
 */
अटल irqवापस_t dm355evm_keys_irq(पूर्णांक irq, व्योम *_keys)
अणु
	अटल u16 last_event;
	काष्ठा dm355evm_keys *keys = _keys;
	स्थिर काष्ठा key_entry *ke;
	अचिन्हित पूर्णांक keycode;
	पूर्णांक status;
	u16 event;

	/* For simplicity we ignore INPUT_COUNT and just पढ़ो
	 * events until we get the "queue empty" indicator.
	 * Reading INPUT_LOW decrements the count.
	 */
	क्रम (;;) अणु
		status = dm355evm_msp_पढ़ो(DM355EVM_MSP_INPUT_HIGH);
		अगर (status < 0) अणु
			dev_dbg(keys->dev, "input high err %d\n",
					status);
			अवरोध;
		पूर्ण
		event = status << 8;

		status = dm355evm_msp_पढ़ो(DM355EVM_MSP_INPUT_LOW);
		अगर (status < 0) अणु
			dev_dbg(keys->dev, "input low err %d\n",
					status);
			अवरोध;
		पूर्ण
		event |= status;
		अगर (event == 0xdead)
			अवरोध;

		/* Press and release a button:  two events, same code.
		 * Press and hold (स्वतःrepeat), then release: N events
		 * (N > 2), same code.  For RC5 buttons the toggle bits
		 * distinguish (क्रम example) "1-autorepeat" from "1 1";
		 * but PCB buttons करोn't support that bit.
		 *
		 * So we must synthesize release events.  We करो that by
		 * mapping events to a press/release event pair; then
		 * to aव्योम adding extra events, skip the second event
		 * of each pair.
		 */
		अगर (event == last_event) अणु
			last_event = 0;
			जारी;
		पूर्ण
		last_event = event;

		/* ignore the RC5 toggle bit */
		event &= ~0x0800;

		/* find the key, or report it as unknown */
		ke = sparse_keymap_entry_from_scancode(keys->input, event);
		keycode = ke ? ke->keycode : KEY_UNKNOWN;
		dev_dbg(keys->dev,
			"input event 0x%04x--> keycode %d\n",
			event, keycode);

		/* report press + release */
		input_report_key(keys->input, keycode, 1);
		input_sync(keys->input);
		input_report_key(keys->input, keycode, 0);
		input_sync(keys->input);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*----------------------------------------------------------------------*/

अटल पूर्णांक dm355evm_keys_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dm355evm_keys	*keys;
	काष्ठा input_dev	*input;
	पूर्णांक			irq;
	पूर्णांक			error;

	keys = devm_kzalloc(&pdev->dev, माप (*keys), GFP_KERNEL);
	अगर (!keys)
		वापस -ENOMEM;

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	keys->dev = &pdev->dev;
	keys->input = input;

	input->name = "DM355 EVM Controls";
	input->phys = "dm355evm/input0";

	input->id.bustype = BUS_I2C;
	input->id.product = 0x0355;
	input->id.version = dm355evm_msp_पढ़ो(DM355EVM_MSP_FIRMREV);

	error = sparse_keymap_setup(input, dm355evm_keys, शून्य);
	अगर (error)
		वापस error;

	/* REVISIT:  flush the event queue? */

	/* set up "threaded IRQ handler" */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	error = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
					  शून्य, dm355evm_keys_irq,
					  IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					  dev_name(&pdev->dev), keys);
	अगर (error)
		वापस error;

	/* रेजिस्टर */
	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

/* REVISIT:  add suspend/resume when DaVinci supports it.  The IRQ should
 * be able to wake up the प्रणाली.  When device_may_wakeup(&pdev->dev), call
 * enable_irq_wake() on suspend, and disable_irq_wake() on resume.
 */

/*
 * I2C is used to talk to the MSP430, but this platक्रमm device is
 * exposed by an MFD driver that manages I2C communications.
 */
अटल काष्ठा platक्रमm_driver dm355evm_keys_driver = अणु
	.probe		= dm355evm_keys_probe,
	.driver		= अणु
		.name	= "dm355evm_keys",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(dm355evm_keys_driver);

MODULE_LICENSE("GPL");
