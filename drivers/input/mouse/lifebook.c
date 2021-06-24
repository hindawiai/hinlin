<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Fujitsu B-series Lअगरebook PS/2 TouchScreen driver
 *
 * Copyright (c) 2005 Vojtech Pavlik <vojtech@suse.cz>
 * Copyright (c) 2005 Kenan Esau <kenan.esau@conan.de>
 *
 * TouchScreen detection, असलolute mode setting and packet layout is taken from
 * Harald Hoyer's description of the device.
 */

#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/libps2.h>
#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "psmouse.h"
#समावेश "lifebook.h"

काष्ठा lअगरebook_data अणु
	काष्ठा input_dev *dev2;		/* Relative device */
	अक्षर phys[32];
पूर्ण;

अटल bool lअगरebook_present;

अटल स्थिर अक्षर *desired_serio_phys;

अटल पूर्णांक lअगरebook_limit_serio3(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	desired_serio_phys = "isa0060/serio3";
	वापस 1;
पूर्ण

अटल bool lअगरebook_use_6byte_proto;

अटल पूर्णांक lअगरebook_set_6byte_proto(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	lअगरebook_use_6byte_proto = true;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id lअगरebook_dmi_table[] __initस्थिर = अणु
	अणु
		/* FLORA-ie 55mi */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "FLORA-ie 55mi"),
		पूर्ण,
	पूर्ण,
	अणु
		/* LअगरeBook B */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Lifebook B Series"),
		पूर्ण,
	पूर्ण,
	अणु
		/* LअगरeBook B */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "LifeBook B Series"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lअगरebook B */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK B Series"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lअगरebook B-2130 */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "ZEPHYR"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lअगरebook B213x/B2150 */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "LifeBook B2131/B2133/B2150"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Zephyr */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "ZEPHYR"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Panasonic CF-18 */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "CF-18"),
		पूर्ण,
		.callback = lअगरebook_limit_serio3,
	पूर्ण,
	अणु
		/* Panasonic CF-28 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Matsushita"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CF-28"),
		पूर्ण,
		.callback = lअगरebook_set_6byte_proto,
	पूर्ण,
	अणु
		/* Panasonic CF-29 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Matsushita"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CF-29"),
		पूर्ण,
		.callback = lअगरebook_set_6byte_proto,
	पूर्ण,
	अणु
		/* Panasonic CF-72 */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "CF-72"),
		पूर्ण,
		.callback = lअगरebook_set_6byte_proto,
	पूर्ण,
	अणु
		/* Lअगरebook B142 */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "LifeBook B142"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

व्योम __init lअगरebook_module_init(व्योम)
अणु
	lअगरebook_present = dmi_check_प्रणाली(lअगरebook_dmi_table);
पूर्ण

अटल psmouse_ret_t lअगरebook_process_byte(काष्ठा psmouse *psmouse)
अणु
	काष्ठा lअगरebook_data *priv = psmouse->निजी;
	काष्ठा input_dev *dev1 = psmouse->dev;
	काष्ठा input_dev *dev2 = priv ? priv->dev2 : शून्य;
	u8 *packet = psmouse->packet;
	bool relative_packet = packet[0] & 0x08;

	अगर (relative_packet || !lअगरebook_use_6byte_proto) अणु
		अगर (psmouse->pktcnt != 3)
			वापस PSMOUSE_GOOD_DATA;
	पूर्ण अन्यथा अणु
		चयन (psmouse->pktcnt) अणु
		हाल 1:
			वापस (packet[0] & 0xf8) == 0x00 ?
				PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;
		हाल 2:
			वापस PSMOUSE_GOOD_DATA;
		हाल 3:
			वापस ((packet[2] & 0x30) << 2) == (packet[2] & 0xc0) ?
				PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;
		हाल 4:
			वापस (packet[3] & 0xf8) == 0xc0 ?
				PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;
		हाल 5:
			वापस (packet[4] & 0xc0) == (packet[2] & 0xc0) ?
				PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;
		हाल 6:
			अगर (((packet[5] & 0x30) << 2) != (packet[5] & 0xc0))
				वापस PSMOUSE_BAD_DATA;
			अगर ((packet[5] & 0xc0) != (packet[1] & 0xc0))
				वापस PSMOUSE_BAD_DATA;
			अवरोध; /* report data */
		पूर्ण
	पूर्ण

	अगर (relative_packet) अणु
		अगर (!dev2)
			psmouse_warn(psmouse,
				     "got relative packet but no relative device set up\n");
	पूर्ण अन्यथा अणु
		अगर (lअगरebook_use_6byte_proto) अणु
			input_report_असल(dev1, ABS_X,
				((packet[1] & 0x3f) << 6) | (packet[2] & 0x3f));
			input_report_असल(dev1, ABS_Y,
				4096 - (((packet[4] & 0x3f) << 6) | (packet[5] & 0x3f)));
		पूर्ण अन्यथा अणु
			input_report_असल(dev1, ABS_X,
				(packet[1] | ((packet[0] & 0x30) << 4)));
			input_report_असल(dev1, ABS_Y,
				1024 - (packet[2] | ((packet[0] & 0xC0) << 2)));
		पूर्ण
		input_report_key(dev1, BTN_TOUCH, packet[0] & 0x04);
		input_sync(dev1);
	पूर्ण

	अगर (dev2) अणु
		अगर (relative_packet)
			psmouse_report_standard_motion(dev2, packet);

		psmouse_report_standard_buttons(dev2, packet[0]);
		input_sync(dev2);
	पूर्ण

	वापस PSMOUSE_FULL_PACKET;
पूर्ण

अटल पूर्णांक lअगरebook_असलolute_mode(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param;
	पूर्णांक error;

	error = psmouse_reset(psmouse);
	अगर (error)
		वापस error;

	/*
	 * Enable असलolute output -- ps2_command fails always but अगर
	 * you leave this call out the touchscreen will never send
	 * असलolute coordinates
	 */
	param = lअगरebook_use_6byte_proto ? 0x08 : 0x07;
	ps2_command(ps2dev, &param, PSMOUSE_CMD_SETRES);

	वापस 0;
पूर्ण

अटल व्योम lअगरebook_relative_mode(काष्ठा psmouse *psmouse)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param = 0x06;

	ps2_command(ps2dev, &param, PSMOUSE_CMD_SETRES);
पूर्ण

अटल व्योम lअगरebook_set_resolution(काष्ठा psmouse *psmouse, अचिन्हित पूर्णांक resolution)
अणु
	अटल स्थिर u8 params[] = अणु 0, 1, 2, 2, 3 पूर्ण;
	u8 p;

	अगर (resolution == 0 || resolution > 400)
		resolution = 400;

	p = params[resolution / 100];
	ps2_command(&psmouse->ps2dev, &p, PSMOUSE_CMD_SETRES);
	psmouse->resolution = 50 << p;
पूर्ण

अटल व्योम lअगरebook_disconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा lअगरebook_data *priv = psmouse->निजी;

	psmouse_reset(psmouse);
	अगर (priv) अणु
		input_unरेजिस्टर_device(priv->dev2);
		kमुक्त(priv);
	पूर्ण
	psmouse->निजी = शून्य;
पूर्ण

पूर्णांक lअगरebook_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	अगर (!lअगरebook_present)
		वापस -ENXIO;

	अगर (desired_serio_phys &&
	    म_भेद(psmouse->ps2dev.serio->phys, desired_serio_phys))
		वापस -ENXIO;

	अगर (set_properties) अणु
		psmouse->venकरोr = "Fujitsu";
		psmouse->name = "Lifebook TouchScreen";
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lअगरebook_create_relative_device(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev2;
	काष्ठा lअगरebook_data *priv;
	पूर्णांक error = -ENOMEM;

	priv = kzalloc(माप(काष्ठा lअगरebook_data), GFP_KERNEL);
	dev2 = input_allocate_device();
	अगर (!priv || !dev2)
		जाओ err_out;

	priv->dev2 = dev2;
	snम_लिखो(priv->phys, माप(priv->phys),
		 "%s/input1", psmouse->ps2dev.serio->phys);

	dev2->phys = priv->phys;
	dev2->name = "LBPS/2 Fujitsu Lifebook Touchpad";
	dev2->id.bustype = BUS_I8042;
	dev2->id.venकरोr  = 0x0002;
	dev2->id.product = PSMOUSE_LIFEBOOK;
	dev2->id.version = 0x0000;
	dev2->dev.parent = &psmouse->ps2dev.serio->dev;

	input_set_capability(dev2, EV_REL, REL_X);
	input_set_capability(dev2, EV_REL, REL_Y);
	input_set_capability(dev2, EV_KEY, BTN_LEFT);
	input_set_capability(dev2, EV_KEY, BTN_RIGHT);

	error = input_रेजिस्टर_device(priv->dev2);
	अगर (error)
		जाओ err_out;

	psmouse->निजी = priv;
	वापस 0;

 err_out:
	input_मुक्त_device(dev2);
	kमुक्त(priv);
	वापस error;
पूर्ण

पूर्णांक lअगरebook_init(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *dev1 = psmouse->dev;
	पूर्णांक max_coord = lअगरebook_use_6byte_proto ? 4096 : 1024;
	पूर्णांक error;

	error = lअगरebook_असलolute_mode(psmouse);
	अगर (error)
		वापस error;

	/* Clear शेष capabilities */
	biपंचांगap_zero(dev1->evbit, EV_CNT);
	biपंचांगap_zero(dev1->relbit, REL_CNT);
	biपंचांगap_zero(dev1->keybit, KEY_CNT);

	input_set_capability(dev1, EV_KEY, BTN_TOUCH);
	input_set_असल_params(dev1, ABS_X, 0, max_coord, 0, 0);
	input_set_असल_params(dev1, ABS_Y, 0, max_coord, 0, 0);

	अगर (!desired_serio_phys) अणु
		error = lअगरebook_create_relative_device(psmouse);
		अगर (error) अणु
			lअगरebook_relative_mode(psmouse);
			वापस error;
		पूर्ण
	पूर्ण

	psmouse->protocol_handler = lअगरebook_process_byte;
	psmouse->set_resolution = lअगरebook_set_resolution;
	psmouse->disconnect = lअगरebook_disconnect;
	psmouse->reconnect  = lअगरebook_असलolute_mode;

	psmouse->model = lअगरebook_use_6byte_proto ? 6 : 3;

	/*
	 * Use packet size = 3 even when using 6-byte protocol because
	 * that's what POLL will वापस on Lअगरebooks (according to spec).
	 */
	psmouse->pktsize = 3;

	वापस 0;
पूर्ण

