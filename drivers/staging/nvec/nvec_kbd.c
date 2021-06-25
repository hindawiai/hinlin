<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * nvec_kbd: keyboard driver क्रम a NVIDIA compliant embedded controller
 *
 * Copyright (C) 2011 The AC100 Kernel Team <ac100@lists.launchpad.net>
 *
 * Authors:  Pierre-Hugues Husson <phhusson@मुक्त.fr>
 *           Marc Dietrich <marvin24@gmx.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "nvec-keytable.h"
#समावेश "nvec.h"

क्रमागत kbd_subcmds अणु
	CNFG_WAKE = 3,
	CNFG_WAKE_KEY_REPORTING,
	SET_LEDS = 0xed,
	ENABLE_KBD = 0xf4,
	DISABLE_KBD,
पूर्ण;

अटल अचिन्हित अक्षर keycodes[ARRAY_SIZE(code_tab_102us)
			      + ARRAY_SIZE(extcode_tab_us102)];

काष्ठा nvec_keys अणु
	काष्ठा input_dev *input;
	काष्ठा notअगरier_block notअगरier;
	काष्ठा nvec_chip *nvec;
	bool caps_lock;
पूर्ण;

अटल काष्ठा nvec_keys keys_dev;

अटल व्योम nvec_kbd_toggle_led(व्योम)
अणु
	अक्षर buf[] = अणु NVEC_KBD, SET_LEDS, 0 पूर्ण;

	keys_dev.caps_lock = !keys_dev.caps_lock;

	अगर (keys_dev.caps_lock)
		/* should be BIT(0) only, firmware bug? */
		buf[2] = BIT(0) | BIT(1) | BIT(2);

	nvec_ग_लिखो_async(keys_dev.nvec, buf, माप(buf));
पूर्ण

अटल पूर्णांक nvec_keys_notअगरier(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ event_type, व्योम *data)
अणु
	पूर्णांक code, state;
	अचिन्हित अक्षर *msg = data;

	अगर (event_type == NVEC_KB_EVT) अणु
		पूर्णांक _size = (msg[0] & (3 << 5)) >> 5;

/* घातer on/off button */
		अगर (_size == NVEC_VAR_SIZE)
			वापस NOTIFY_STOP;

		अगर (_size == NVEC_3BYTES)
			msg++;

		code = msg[1] & 0x7f;
		state = msg[1] & 0x80;

		अगर (code_tअसल[_size][code] == KEY_CAPSLOCK && state)
			nvec_kbd_toggle_led();

		input_report_key(keys_dev.input, code_tअसल[_size][code],
				 !state);
		input_sync(keys_dev.input);

		वापस NOTIFY_STOP;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक nvec_kbd_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
			  अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा nvec_chip *nvec = keys_dev.nvec;
	अक्षर buf[] = अणु NVEC_KBD, SET_LEDS, 0 पूर्ण;

	अगर (type == EV_REP)
		वापस 0;

	अगर (type != EV_LED)
		वापस -1;

	अगर (code != LED_CAPSL)
		वापस -1;

	buf[2] = !!value;
	nvec_ग_लिखो_async(nvec, buf, माप(buf));

	वापस 0;
पूर्ण

अटल पूर्णांक nvec_kbd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvec_chip *nvec = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक i, j, err;
	काष्ठा input_dev *idev;
	अक्षर	clear_leds[] = अणु NVEC_KBD, SET_LEDS, 0 पूर्ण,
		enable_kbd[] = अणु NVEC_KBD, ENABLE_KBD पूर्ण,
		cnfg_wake[] = अणु NVEC_KBD, CNFG_WAKE, true, true पूर्ण,
		cnfg_wake_key_reporting[] = अणु NVEC_KBD, CNFG_WAKE_KEY_REPORTING,
						true पूर्ण;

	j = 0;

	क्रम (i = 0; i < ARRAY_SIZE(code_tab_102us); ++i)
		keycodes[j++] = code_tab_102us[i];

	क्रम (i = 0; i < ARRAY_SIZE(extcode_tab_us102); ++i)
		keycodes[j++] = extcode_tab_us102[i];

	idev = devm_input_allocate_device(&pdev->dev);
	अगर (!idev)
		वापस -ENOMEM;
	idev->name = "nvec keyboard";
	idev->phys = "nvec";
	idev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP) | BIT_MASK(EV_LED);
	idev->ledbit[0] = BIT_MASK(LED_CAPSL);
	idev->event = nvec_kbd_event;
	idev->keycode = keycodes;
	idev->keycodesize = माप(अचिन्हित अक्षर);
	idev->keycodemax = ARRAY_SIZE(keycodes);

	क्रम (i = 0; i < ARRAY_SIZE(keycodes); ++i)
		set_bit(keycodes[i], idev->keybit);

	clear_bit(0, idev->keybit);
	err = input_रेजिस्टर_device(idev);
	अगर (err)
		वापस err;

	keys_dev.input = idev;
	keys_dev.notअगरier.notअगरier_call = nvec_keys_notअगरier;
	keys_dev.nvec = nvec;
	nvec_रेजिस्टर_notअगरier(nvec, &keys_dev.notअगरier, 0);

	/* Enable keyboard */
	nvec_ग_लिखो_async(nvec, enable_kbd, 2);

	/* configures wake on special keys */
	nvec_ग_लिखो_async(nvec, cnfg_wake, 4);
	/* enable wake key reporting */
	nvec_ग_लिखो_async(nvec, cnfg_wake_key_reporting, 3);

	/* Disable caps lock LED */
	nvec_ग_लिखो_async(nvec, clear_leds, माप(clear_leds));

	वापस 0;
पूर्ण

अटल पूर्णांक nvec_kbd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvec_chip *nvec = dev_get_drvdata(pdev->dev.parent);
	अक्षर disable_kbd[] = अणु NVEC_KBD, DISABLE_KBD पूर्ण,
	     uncnfg_wake_key_reporting[] = अणु NVEC_KBD, CNFG_WAKE_KEY_REPORTING,
						false पूर्ण;
	nvec_ग_लिखो_async(nvec, uncnfg_wake_key_reporting, 3);
	nvec_ग_लिखो_async(nvec, disable_kbd, 2);
	nvec_unरेजिस्टर_notअगरier(nvec, &keys_dev.notअगरier);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver nvec_kbd_driver = अणु
	.probe  = nvec_kbd_probe,
	.हटाओ = nvec_kbd_हटाओ,
	.driver = अणु
		.name = "nvec-kbd",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(nvec_kbd_driver);

MODULE_AUTHOR("Marc Dietrich <marvin24@gmx.de>");
MODULE_DESCRIPTION("NVEC keyboard driver");
MODULE_ALIAS("platform:nvec-kbd");
MODULE_LICENSE("GPL");
