<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// handle em28xx IR remotes via linux kernel input layer.
//
// Copyright (C) 2005 Luकरोvico Caveकरोn <caveकरोn@sssup.it>
//		      Markus Rechberger <mrechberger@gmail.com>
//		      Mauro Carvalho Chehab <mchehab@kernel.org>
//		      Sascha Sommer <saschasommer@मुक्तnet.de>
//
// This program is मुक्त software; you can redistribute it and/or modअगरy
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License क्रम more details.

#समावेश "em28xx.h"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitrev.h>

#घोषणा EM28XX_SNAPSHOT_KEY				KEY_CAMERA
#घोषणा EM28XX_BUTTONS_DEBOUNCED_QUERY_INTERVAL		500 /* [ms] */
#घोषणा EM28XX_BUTTONS_VOLATILE_QUERY_INTERVAL		100 /* [ms] */

अटल अचिन्हित पूर्णांक ir_debug;
module_param(ir_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(ir_debug, "enable debug messages [IR]");

#घोषणा MODULE_NAME "em28xx"

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (ir_debug)							\
		dev_prपूर्णांकk(KERN_DEBUG, &ir->dev->पूर्णांकf->dev,		\
			   "input: %s: " fmt, __func__, ## arg);	\
पूर्ण जबतक (0)

/*
 * Polling काष्ठाure used by em28xx IR's
 */

काष्ठा em28xx_ir_poll_result अणु
	अचिन्हित पूर्णांक toggle_bit:1;
	अचिन्हित पूर्णांक पढ़ो_count:7;

	क्रमागत rc_proto protocol;
	u32 scancode;
पूर्ण;

काष्ठा em28xx_IR अणु
	काष्ठा em28xx *dev;
	काष्ठा rc_dev *rc;
	अक्षर phys[32];

	/* poll decoder */
	पूर्णांक polling;
	काष्ठा delayed_work work;
	अचिन्हित पूर्णांक full_code:1;
	अचिन्हित पूर्णांक last_पढ़ोcount;
	u64 rc_proto;

	काष्ठा i2c_client *i2c_client;

	पूर्णांक  (*get_key_i2c)(काष्ठा i2c_client *ir, क्रमागत rc_proto *protocol,
			    u32 *scancode);
	पूर्णांक  (*get_key)(काष्ठा em28xx_IR *ir, काष्ठा em28xx_ir_poll_result *r);
पूर्ण;

/*
 * I2C IR based get keycodes - should be used with ir-kbd-i2c
 */

अटल पूर्णांक em28xx_get_key_terratec(काष्ठा i2c_client *i2c_dev,
				   क्रमागत rc_proto *protocol, u32 *scancode)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर b;

	/* poll IR chip */
	rc = i2c_master_recv(i2c_dev, &b, 1);
	अगर (rc != 1) अणु
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण

	/*
	 * it seems that 0xFE indicates that a button is still hold
	 * करोwn, जबतक 0xff indicates that no button is hold करोwn.
	 */

	अगर (b == 0xff)
		वापस 0;

	अगर (b == 0xfe)
		/* keep old data */
		वापस 1;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = b;
	वापस 1;
पूर्ण

अटल पूर्णांक em28xx_get_key_em_haup(काष्ठा i2c_client *i2c_dev,
				  क्रमागत rc_proto *protocol, u32 *scancode)
अणु
	अचिन्हित अक्षर buf[2];
	पूर्णांक size;

	/* poll IR chip */
	size = i2c_master_recv(i2c_dev, buf, माप(buf));

	अगर (size != 2)
		वापस -EIO;

	/* Does eliminate repeated parity code */
	अगर (buf[1] == 0xff)
		वापस 0;

	/*
	 * Rearranges bits to the right order.
	 * The bit order were determined experimentally by using
	 * The original Hauppauge Grey IR and another RC5 that uses addr=0x08
	 * The RC5 code has 14 bits, but we've experimentally determined
	 * the meaning क्रम only 11 bits.
	 * So, the code translation is not complete. Yet, it is enough to
	 * work with the provided RC5 IR.
	 */
	*protocol = RC_PROTO_RC5;
	*scancode = (bitrev8(buf[1]) & 0x1f) << 8 | bitrev8(buf[0]) >> 2;
	वापस 1;
पूर्ण

अटल पूर्णांक em28xx_get_key_pinnacle_usb_grey(काष्ठा i2c_client *i2c_dev,
					    क्रमागत rc_proto *protocol,
					    u32 *scancode)
अणु
	अचिन्हित अक्षर buf[3];

	/* poll IR chip */

	अगर (i2c_master_recv(i2c_dev, buf, 3) != 3)
		वापस -EIO;

	अगर (buf[0] != 0x00)
		वापस 0;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = buf[2] & 0x3f;
	वापस 1;
पूर्ण

अटल पूर्णांक em28xx_get_key_winfast_usbii_deluxe(काष्ठा i2c_client *i2c_dev,
					       क्रमागत rc_proto *protocol,
					       u32 *scancode)
अणु
	अचिन्हित अक्षर subaddr, keydetect, key;

	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = i2c_dev->addr,
			.flags = 0,
			.buf = &subaddr, .len = 1
		पूर्ण, अणु
			.addr = i2c_dev->addr,
			.flags = I2C_M_RD,
			.buf = &keydetect,
			.len = 1
		पूर्ण
	पूर्ण;

	subaddr = 0x10;
	अगर (i2c_transfer(i2c_dev->adapter, msg, 2) != 2)
		वापस -EIO;
	अगर (keydetect == 0x00)
		वापस 0;

	subaddr = 0x00;
	msg[1].buf = &key;
	अगर (i2c_transfer(i2c_dev->adapter, msg, 2) != 2)
		वापस -EIO;
	अगर (key == 0x00)
		वापस 0;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = key;
	वापस 1;
पूर्ण

/*
 * Poll based get keycode functions
 */

/* This is क्रम the em2860/em2880 */
अटल पूर्णांक शेष_polling_getkey(काष्ठा em28xx_IR *ir,
				  काष्ठा em28xx_ir_poll_result *poll_result)
अणु
	काष्ठा em28xx *dev = ir->dev;
	पूर्णांक rc;
	u8 msg[3] = अणु 0, 0, 0 पूर्ण;

	/*
	 * Read key toggle, bअक्रम, and key code
	 * on रेजिस्टरs 0x45, 0x46 and 0x47
	 */
	rc = dev->em28xx_पढ़ो_reg_req_len(dev, 0, EM28XX_R45_IR,
					  msg, माप(msg));
	अगर (rc < 0)
		वापस rc;

	/* Infrared toggle (Reg 0x45[7]) */
	poll_result->toggle_bit = (msg[0] >> 7);

	/* Infrared पढ़ो count (Reg 0x45[6:0] */
	poll_result->पढ़ो_count = (msg[0] & 0x7f);

	/* Remote Control Address/Data (Regs 0x46/0x47) */
	चयन (ir->rc_proto) अणु
	हाल RC_PROTO_BIT_RC5:
		poll_result->protocol = RC_PROTO_RC5;
		poll_result->scancode = RC_SCANCODE_RC5(msg[1], msg[2]);
		अवरोध;

	हाल RC_PROTO_BIT_NEC:
		poll_result->protocol = RC_PROTO_NEC;
		poll_result->scancode = RC_SCANCODE_NEC(msg[1], msg[2]);
		अवरोध;

	शेष:
		poll_result->protocol = RC_PROTO_UNKNOWN;
		poll_result->scancode = msg[1] << 8 | msg[2];
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक em2874_polling_getkey(काष्ठा em28xx_IR *ir,
				 काष्ठा em28xx_ir_poll_result *poll_result)
अणु
	काष्ठा em28xx *dev = ir->dev;
	पूर्णांक rc;
	u8 msg[5] = अणु 0, 0, 0, 0, 0 पूर्ण;

	/*
	 * Read key toggle, bअक्रम, and key code
	 * on रेजिस्टरs 0x51-55
	 */
	rc = dev->em28xx_पढ़ो_reg_req_len(dev, 0, EM2874_R51_IR,
					  msg, माप(msg));
	अगर (rc < 0)
		वापस rc;

	/* Infrared toggle (Reg 0x51[7]) */
	poll_result->toggle_bit = (msg[0] >> 7);

	/* Infrared पढ़ो count (Reg 0x51[6:0] */
	poll_result->पढ़ो_count = (msg[0] & 0x7f);

	/*
	 * Remote Control Address (Reg 0x52)
	 * Remote Control Data (Reg 0x53-0x55)
	 */
	चयन (ir->rc_proto) अणु
	हाल RC_PROTO_BIT_RC5:
		poll_result->protocol = RC_PROTO_RC5;
		poll_result->scancode = RC_SCANCODE_RC5(msg[1], msg[2]);
		अवरोध;

	हाल RC_PROTO_BIT_NEC:
		poll_result->scancode = ir_nec_bytes_to_scancode(msg[1], msg[2], msg[3], msg[4],
								 &poll_result->protocol);
		अवरोध;

	हाल RC_PROTO_BIT_RC6_0:
		poll_result->protocol = RC_PROTO_RC6_0;
		poll_result->scancode = RC_SCANCODE_RC6_0(msg[1], msg[2]);
		अवरोध;

	शेष:
		poll_result->protocol = RC_PROTO_UNKNOWN;
		poll_result->scancode = (msg[1] << 24) | (msg[2] << 16) |
					(msg[3] << 8)  | msg[4];
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Polling code क्रम em28xx
 */

अटल पूर्णांक em28xx_i2c_ir_handle_key(काष्ठा em28xx_IR *ir)
अणु
	अटल u32 scancode;
	क्रमागत rc_proto protocol;
	पूर्णांक rc;

	rc = ir->get_key_i2c(ir->i2c_client, &protocol, &scancode);
	अगर (rc < 0) अणु
		dprपूर्णांकk("ir->get_key_i2c() failed: %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (rc) अणु
		dprपूर्णांकk("%s: proto = 0x%04x, scancode = 0x%04x\n",
			__func__, protocol, scancode);
		rc_keyकरोwn(ir->rc, protocol, scancode, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम em28xx_ir_handle_key(काष्ठा em28xx_IR *ir)
अणु
	पूर्णांक result;
	काष्ठा em28xx_ir_poll_result poll_result;

	/* पढ़ो the रेजिस्टरs containing the IR status */
	result = ir->get_key(ir, &poll_result);
	अगर (unlikely(result < 0)) अणु
		dprपूर्णांकk("ir->get_key() failed: %d\n", result);
		वापस;
	पूर्ण

	अगर (unlikely(poll_result.पढ़ो_count != ir->last_पढ़ोcount)) अणु
		dprपूर्णांकk("%s: toggle: %d, count: %d, key 0x%04x\n", __func__,
			poll_result.toggle_bit, poll_result.पढ़ो_count,
			poll_result.scancode);
		अगर (ir->full_code)
			rc_keyकरोwn(ir->rc,
				   poll_result.protocol,
				   poll_result.scancode,
				   poll_result.toggle_bit);
		अन्यथा
			rc_keyकरोwn(ir->rc,
				   RC_PROTO_UNKNOWN,
				   poll_result.scancode & 0xff,
				   poll_result.toggle_bit);

		अगर (ir->dev->chip_id == CHIP_ID_EM2874 ||
		    ir->dev->chip_id == CHIP_ID_EM2884)
			/*
			 * The em2874 clears the पढ़ोcount field every समय the
			 * रेजिस्टर is पढ़ो.  The em2860/2880 datasheet says
			 * that it is supposed to clear the पढ़ोcount, but it
			 * करोesn't. So with the em2874, we are looking क्रम a
			 * non-zero पढ़ो count as opposed to a पढ़ोcount
			 * that is incrementing
			 */
			ir->last_पढ़ोcount = 0;
		अन्यथा
			ir->last_पढ़ोcount = poll_result.पढ़ो_count;
	पूर्ण
पूर्ण

अटल व्योम em28xx_ir_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा em28xx_IR *ir = container_of(work, काष्ठा em28xx_IR, work.work);

	अगर (ir->i2c_client) /* बाह्यal i2c device */
		em28xx_i2c_ir_handle_key(ir);
	अन्यथा /* पूर्णांकernal device */
		em28xx_ir_handle_key(ir);
	schedule_delayed_work(&ir->work, msecs_to_jअगरfies(ir->polling));
पूर्ण

अटल पूर्णांक em28xx_ir_start(काष्ठा rc_dev *rc)
अणु
	काष्ठा em28xx_IR *ir = rc->priv;

	INIT_DELAYED_WORK(&ir->work, em28xx_ir_work);
	schedule_delayed_work(&ir->work, 0);

	वापस 0;
पूर्ण

अटल व्योम em28xx_ir_stop(काष्ठा rc_dev *rc)
अणु
	काष्ठा em28xx_IR *ir = rc->priv;

	cancel_delayed_work_sync(&ir->work);
पूर्ण

अटल पूर्णांक em2860_ir_change_protocol(काष्ठा rc_dev *rc_dev, u64 *rc_proto)
अणु
	काष्ठा em28xx_IR *ir = rc_dev->priv;
	काष्ठा em28xx *dev = ir->dev;

	/* Adjust xclk based on IR table क्रम RC5/NEC tables */
	अगर (*rc_proto & RC_PROTO_BIT_RC5) अणु
		dev->board.xclk |= EM28XX_XCLK_IR_RC5_MODE;
		ir->full_code = 1;
		*rc_proto = RC_PROTO_BIT_RC5;
	पूर्ण अन्यथा अगर (*rc_proto & RC_PROTO_BIT_NEC) अणु
		dev->board.xclk &= ~EM28XX_XCLK_IR_RC5_MODE;
		ir->full_code = 1;
		*rc_proto = RC_PROTO_BIT_NEC;
	पूर्ण अन्यथा अगर (*rc_proto & RC_PROTO_BIT_UNKNOWN) अणु
		*rc_proto = RC_PROTO_BIT_UNKNOWN;
	पूर्ण अन्यथा अणु
		*rc_proto = ir->rc_proto;
		वापस -EINVAL;
	पूर्ण
	em28xx_ग_लिखो_reg_bits(dev, EM28XX_R0F_XCLK, dev->board.xclk,
			      EM28XX_XCLK_IR_RC5_MODE);

	ir->rc_proto = *rc_proto;

	वापस 0;
पूर्ण

अटल पूर्णांक em2874_ir_change_protocol(काष्ठा rc_dev *rc_dev, u64 *rc_proto)
अणु
	काष्ठा em28xx_IR *ir = rc_dev->priv;
	काष्ठा em28xx *dev = ir->dev;
	u8 ir_config = EM2874_IR_RC5;

	/* Adjust xclk and set type based on IR table क्रम RC5/NEC/RC6 tables */
	अगर (*rc_proto & RC_PROTO_BIT_RC5) अणु
		dev->board.xclk |= EM28XX_XCLK_IR_RC5_MODE;
		ir->full_code = 1;
		*rc_proto = RC_PROTO_BIT_RC5;
	पूर्ण अन्यथा अगर (*rc_proto & RC_PROTO_BIT_NEC) अणु
		dev->board.xclk &= ~EM28XX_XCLK_IR_RC5_MODE;
		ir_config = EM2874_IR_NEC | EM2874_IR_NEC_NO_PARITY;
		ir->full_code = 1;
		*rc_proto = RC_PROTO_BIT_NEC;
	पूर्ण अन्यथा अगर (*rc_proto & RC_PROTO_BIT_RC6_0) अणु
		dev->board.xclk |= EM28XX_XCLK_IR_RC5_MODE;
		ir_config = EM2874_IR_RC6_MODE_0;
		ir->full_code = 1;
		*rc_proto = RC_PROTO_BIT_RC6_0;
	पूर्ण अन्यथा अगर (*rc_proto & RC_PROTO_BIT_UNKNOWN) अणु
		*rc_proto = RC_PROTO_BIT_UNKNOWN;
	पूर्ण अन्यथा अणु
		*rc_proto = ir->rc_proto;
		वापस -EINVAL;
	पूर्ण
	em28xx_ग_लिखो_regs(dev, EM2874_R50_IR_CONFIG, &ir_config, 1);
	em28xx_ग_लिखो_reg_bits(dev, EM28XX_R0F_XCLK, dev->board.xclk,
			      EM28XX_XCLK_IR_RC5_MODE);

	ir->rc_proto = *rc_proto;

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_ir_change_protocol(काष्ठा rc_dev *rc_dev, u64 *rc_proto)
अणु
	काष्ठा em28xx_IR *ir = rc_dev->priv;
	काष्ठा em28xx *dev = ir->dev;

	/* Setup the proper handler based on the chip */
	चयन (dev->chip_id) अणु
	हाल CHIP_ID_EM2860:
	हाल CHIP_ID_EM2883:
		वापस em2860_ir_change_protocol(rc_dev, rc_proto);
	हाल CHIP_ID_EM2884:
	हाल CHIP_ID_EM2874:
	हाल CHIP_ID_EM28174:
	हाल CHIP_ID_EM28178:
		वापस em2874_ir_change_protocol(rc_dev, rc_proto);
	शेष:
		dev_err(&ir->dev->पूर्णांकf->dev,
			"Unrecognized em28xx chip id 0x%02x: IR not supported\n",
			dev->chip_id);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक em28xx_probe_i2c_ir(काष्ठा em28xx *dev)
अणु
	पूर्णांक i = 0;
	/*
	 * Leadtek winfast tv USBII deluxe can find a non working IR-device
	 * at address 0x18, so अगर that address is needed क्रम another board in
	 * the future, please put it after 0x1f.
	 */
	अटल स्थिर अचिन्हित लघु addr_list[] = अणु
		 0x1f, 0x30, 0x47, I2C_CLIENT_END
	पूर्ण;

	जबतक (addr_list[i] != I2C_CLIENT_END) अणु
		अगर (i2c_probe_func_quick_पढ़ो(&dev->i2c_adap[dev->def_i2c_bus],
					      addr_list[i]) == 1)
			वापस addr_list[i];
		i++;
	पूर्ण

	वापस -ENODEV;
पूर्ण

/*
 * Handle buttons
 */

अटल व्योम em28xx_query_buttons(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा em28xx *dev =
		container_of(work, काष्ठा em28xx, buttons_query_work.work);
	u8 i, j;
	पूर्णांक regval;
	bool is_pressed, was_pressed;
	स्थिर काष्ठा em28xx_led *led;

	/* Poll and evaluate all addresses */
	क्रम (i = 0; i < dev->num_button_polling_addresses; i++) अणु
		/* Read value from रेजिस्टर */
		regval = em28xx_पढ़ो_reg(dev, dev->button_polling_addresses[i]);
		अगर (regval < 0)
			जारी;
		/* Check states of the buttons and act */
		j = 0;
		जबतक (dev->board.buttons[j].role >= 0 &&
		       dev->board.buttons[j].role < EM28XX_NUM_BUTTON_ROLES) अणु
			स्थिर काष्ठा em28xx_button *button;

			button = &dev->board.buttons[j];

			/* Check अगर button uses the current address */
			अगर (button->reg_r != dev->button_polling_addresses[i]) अणु
				j++;
				जारी;
			पूर्ण
			/* Determine अगर button is and was pressed last समय */
			is_pressed = regval & button->mask;
			was_pressed = dev->button_polling_last_values[i]
				       & button->mask;
			अगर (button->inverted) अणु
				is_pressed = !is_pressed;
				was_pressed = !was_pressed;
			पूर्ण
			/* Clear button state (अगर needed) */
			अगर (is_pressed && button->reg_clearing)
				em28xx_ग_लिखो_reg(dev, button->reg_clearing,
						 (~regval & button->mask)
						    | (regval & ~button->mask));
			/* Handle button state */
			अगर (!is_pressed || was_pressed) अणु
				j++;
				जारी;
			पूर्ण
			चयन (button->role) अणु
			हाल EM28XX_BUTTON_SNAPSHOT:
				/* Emulate the keypress */
				input_report_key(dev->sbutton_input_dev,
						 EM28XX_SNAPSHOT_KEY, 1);
				/* Unpress the key */
				input_report_key(dev->sbutton_input_dev,
						 EM28XX_SNAPSHOT_KEY, 0);
				अवरोध;
			हाल EM28XX_BUTTON_ILLUMINATION:
				led = em28xx_find_led(dev,
						      EM28XX_LED_ILLUMINATION);
				/* Switch illumination LED on/off */
				अगर (led)
					em28xx_toggle_reg_bits(dev,
							       led->gpio_reg,
							       led->gpio_mask);
				अवरोध;
			शेष:
				WARN_ONCE(1, "BUG: unhandled button role.");
			पूर्ण
			/* Next button */
			j++;
		पूर्ण
		/* Save current value क्रम comparison during the next polling */
		dev->button_polling_last_values[i] = regval;
	पूर्ण
	/* Schedule next poll */
	schedule_delayed_work(&dev->buttons_query_work,
			      msecs_to_jअगरfies(dev->button_polling_पूर्णांकerval));
पूर्ण

अटल पूर्णांक em28xx_रेजिस्टर_snapshot_button(काष्ठा em28xx *dev)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	dev_info(&dev->पूर्णांकf->dev, "Registering snapshot button...\n");
	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	usb_make_path(udev, dev->snapshot_button_path,
		      माप(dev->snapshot_button_path));
	strlcat(dev->snapshot_button_path, "/sbutton",
		माप(dev->snapshot_button_path));

	input_dev->name = "em28xx snapshot button";
	input_dev->phys = dev->snapshot_button_path;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	set_bit(EM28XX_SNAPSHOT_KEY, input_dev->keybit);
	input_dev->keycodesize = 0;
	input_dev->keycodemax = 0;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.parent = &dev->पूर्णांकf->dev;

	err = input_रेजिस्टर_device(input_dev);
	अगर (err) अणु
		dev_err(&dev->पूर्णांकf->dev, "input_register_device failed\n");
		input_मुक्त_device(input_dev);
		वापस err;
	पूर्ण

	dev->sbutton_input_dev = input_dev;
	वापस 0;
पूर्ण

अटल व्योम em28xx_init_buttons(काष्ठा em28xx *dev)
अणु
	u8  i = 0, j = 0;
	bool addr_new = false;

	dev->button_polling_पूर्णांकerval = EM28XX_BUTTONS_DEBOUNCED_QUERY_INTERVAL;
	जबतक (dev->board.buttons[i].role >= 0 &&
	       dev->board.buttons[i].role < EM28XX_NUM_BUTTON_ROLES) अणु
		स्थिर काष्ठा em28xx_button *button = &dev->board.buttons[i];

		/* Check अगर polling address is alपढ़ोy on the list */
		addr_new = true;
		क्रम (j = 0; j < dev->num_button_polling_addresses; j++) अणु
			अगर (button->reg_r == dev->button_polling_addresses[j]) अणु
				addr_new = false;
				अवरोध;
			पूर्ण
		पूर्ण
		/* Check अगर max. number of polling addresses is exceeded */
		अगर (addr_new && dev->num_button_polling_addresses
					   >= EM28XX_NUM_BUTTON_ADDRESSES_MAX) अणु
			WARN_ONCE(1, "BUG: maximum number of button polling addresses exceeded.");
			जाओ next_button;
		पूर्ण
		/* Button role specअगरic checks and actions */
		अगर (button->role == EM28XX_BUTTON_SNAPSHOT) अणु
			/* Register input device */
			अगर (em28xx_रेजिस्टर_snapshot_button(dev) < 0)
				जाओ next_button;
		पूर्ण अन्यथा अगर (button->role == EM28XX_BUTTON_ILLUMINATION) अणु
			/* Check sanity */
			अगर (!em28xx_find_led(dev, EM28XX_LED_ILLUMINATION)) अणु
				dev_err(&dev->पूर्णांकf->dev,
					"BUG: illumination button defined, but no illumination LED.\n");
				जाओ next_button;
			पूर्ण
		पूर्ण
		/* Add पढ़ो address to list of polling addresses */
		अगर (addr_new) अणु
			अचिन्हित पूर्णांक index = dev->num_button_polling_addresses;

			dev->button_polling_addresses[index] = button->reg_r;
			dev->num_button_polling_addresses++;
		पूर्ण
		/* Reduce polling पूर्णांकerval अगर necessary */
		अगर (!button->reg_clearing)
			dev->button_polling_पूर्णांकerval =
					 EM28XX_BUTTONS_VOLATILE_QUERY_INTERVAL;
next_button:
		/* Next button */
		i++;
	पूर्ण

	/* Start polling */
	अगर (dev->num_button_polling_addresses) अणु
		स_रखो(dev->button_polling_last_values, 0,
		       EM28XX_NUM_BUTTON_ADDRESSES_MAX);
		schedule_delayed_work(&dev->buttons_query_work,
				      msecs_to_jअगरfies(dev->button_polling_पूर्णांकerval));
	पूर्ण
पूर्ण

अटल व्योम em28xx_shutकरोwn_buttons(काष्ठा em28xx *dev)
अणु
	/* Cancel polling */
	cancel_delayed_work_sync(&dev->buttons_query_work);
	/* Clear polling addresses list */
	dev->num_button_polling_addresses = 0;
	/* Deरेजिस्टर input devices */
	अगर (dev->sbutton_input_dev) अणु
		dev_info(&dev->पूर्णांकf->dev, "Deregistering snapshot button\n");
		input_unरेजिस्टर_device(dev->sbutton_input_dev);
		dev->sbutton_input_dev = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक em28xx_ir_init(काष्ठा em28xx *dev)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	काष्ठा em28xx_IR *ir;
	काष्ठा rc_dev *rc;
	पूर्णांक err = -ENOMEM;
	u64 rc_proto;
	u16 i2c_rc_dev_addr = 0;

	अगर (dev->is_audio_only) अणु
		/* Shouldn't initialize IR क्रम this पूर्णांकerface */
		वापस 0;
	पूर्ण

	kref_get(&dev->ref);
	INIT_DELAYED_WORK(&dev->buttons_query_work, em28xx_query_buttons);

	अगर (dev->board.buttons)
		em28xx_init_buttons(dev);

	अगर (dev->board.has_ir_i2c) अणु
		i2c_rc_dev_addr = em28xx_probe_i2c_ir(dev);
		अगर (!i2c_rc_dev_addr) अणु
			dev->board.has_ir_i2c = 0;
			dev_warn(&dev->पूर्णांकf->dev,
				 "No i2c IR remote control device found.\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (!dev->board.ir_codes && !dev->board.has_ir_i2c) अणु
		/* No remote control support */
		dev_warn(&dev->पूर्णांकf->dev,
			 "Remote control support is not available for this card.\n");
		वापस 0;
	पूर्ण

	dev_info(&dev->पूर्णांकf->dev, "Registering input extension\n");

	ir = kzalloc(माप(*ir), GFP_KERNEL);
	अगर (!ir)
		वापस -ENOMEM;
	rc = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!rc)
		जाओ error;

	/* record handles to ourself */
	ir->dev = dev;
	dev->ir = ir;
	ir->rc = rc;

	rc->priv = ir;
	rc->खोलो = em28xx_ir_start;
	rc->बंद = em28xx_ir_stop;

	अगर (dev->board.has_ir_i2c) अणु	/* बाह्यal i2c device */
		चयन (dev->model) अणु
		हाल EM2800_BOARD_TERRATEC_CINERGY_200:
		हाल EM2820_BOARD_TERRATEC_CINERGY_250:
			rc->map_name = RC_MAP_EM_TERRATEC;
			ir->get_key_i2c = em28xx_get_key_terratec;
			अवरोध;
		हाल EM2820_BOARD_PINNACLE_USB_2:
			rc->map_name = RC_MAP_PINNACLE_GREY;
			ir->get_key_i2c = em28xx_get_key_pinnacle_usb_grey;
			अवरोध;
		हाल EM2820_BOARD_HAUPPAUGE_WINTV_USB_2:
			rc->map_name = RC_MAP_HAUPPAUGE;
			ir->get_key_i2c = em28xx_get_key_em_haup;
			rc->allowed_protocols = RC_PROTO_BIT_RC5;
			अवरोध;
		हाल EM2820_BOARD_LEADTEK_WINFAST_USBII_DELUXE:
			rc->map_name = RC_MAP_WINFAST_USBII_DELUXE;
			ir->get_key_i2c = em28xx_get_key_winfast_usbii_deluxe;
			अवरोध;
		शेष:
			err = -ENODEV;
			जाओ error;
		पूर्ण

		ir->i2c_client = kzalloc(माप(*ir->i2c_client), GFP_KERNEL);
		अगर (!ir->i2c_client)
			जाओ error;
		ir->i2c_client->adapter = &ir->dev->i2c_adap[dev->def_i2c_bus];
		ir->i2c_client->addr = i2c_rc_dev_addr;
		ir->i2c_client->flags = 0;
		/* NOTE: all other fields of i2c_client are unused */
	पूर्ण अन्यथा अणु	/* पूर्णांकernal device */
		चयन (dev->chip_id) अणु
		हाल CHIP_ID_EM2860:
		हाल CHIP_ID_EM2883:
			rc->allowed_protocols = RC_PROTO_BIT_RC5 |
						RC_PROTO_BIT_NEC;
			ir->get_key = शेष_polling_getkey;
			अवरोध;
		हाल CHIP_ID_EM2884:
		हाल CHIP_ID_EM2874:
		हाल CHIP_ID_EM28174:
		हाल CHIP_ID_EM28178:
			ir->get_key = em2874_polling_getkey;
			rc->allowed_protocols = RC_PROTO_BIT_RC5 |
				RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX |
				RC_PROTO_BIT_NEC32 | RC_PROTO_BIT_RC6_0;
			अवरोध;
		शेष:
			err = -ENODEV;
			जाओ error;
		पूर्ण

		rc->change_protocol = em28xx_ir_change_protocol;
		rc->map_name = dev->board.ir_codes;

		/* By शेष, keep protocol field untouched */
		rc_proto = RC_PROTO_BIT_UNKNOWN;
		err = em28xx_ir_change_protocol(rc, &rc_proto);
		अगर (err)
			जाओ error;
	पूर्ण

	/* This is how often we ask the chip क्रम IR inक्रमmation */
	ir->polling = 100; /* ms */

	usb_make_path(udev, ir->phys, माप(ir->phys));
	strlcat(ir->phys, "/input0", माप(ir->phys));

	rc->device_name = em28xx_boards[dev->model].name;
	rc->input_phys = ir->phys;
	usb_to_input_id(udev, &rc->input_id);
	rc->dev.parent = &dev->पूर्णांकf->dev;
	rc->driver_name = MODULE_NAME;

	/* all करोne */
	err = rc_रेजिस्टर_device(rc);
	अगर (err)
		जाओ error;

	dev_info(&dev->पूर्णांकf->dev, "Input extension successfully initialized\n");

	वापस 0;

error:
	kमुक्त(ir->i2c_client);
	dev->ir = शून्य;
	rc_मुक्त_device(rc);
	kमुक्त(ir);
	वापस err;
पूर्ण

अटल पूर्णांक em28xx_ir_fini(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_IR *ir = dev->ir;

	अगर (dev->is_audio_only) अणु
		/* Shouldn't initialize IR क्रम this पूर्णांकerface */
		वापस 0;
	पूर्ण

	dev_info(&dev->पूर्णांकf->dev, "Closing input extension\n");

	em28xx_shutकरोwn_buttons(dev);

	/* skip detach on non attached boards */
	अगर (!ir)
		जाओ ref_put;

	rc_unरेजिस्टर_device(ir->rc);

	kमुक्त(ir->i2c_client);

	/* करोne */
	kमुक्त(ir);
	dev->ir = शून्य;

ref_put:
	kref_put(&dev->ref, em28xx_मुक्त_device);

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_ir_suspend(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_IR *ir = dev->ir;

	अगर (dev->is_audio_only)
		वापस 0;

	dev_info(&dev->पूर्णांकf->dev, "Suspending input extension\n");
	अगर (ir)
		cancel_delayed_work_sync(&ir->work);
	cancel_delayed_work_sync(&dev->buttons_query_work);
	/*
	 * is canceling delayed work sufficient or करोes the rc event
	 * kthपढ़ो needs stopping? kthपढ़ो is stopped in
	 * ir_raw_event_unरेजिस्टर()
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_ir_resume(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_IR *ir = dev->ir;

	अगर (dev->is_audio_only)
		वापस 0;

	dev_info(&dev->पूर्णांकf->dev, "Resuming input extension\n");
	/*
	 * अगर suspend calls ir_raw_event_unरेजिस्टर(), the should call
	 * ir_raw_event_रेजिस्टर()
	 */
	अगर (ir)
		schedule_delayed_work(&ir->work, msecs_to_jअगरfies(ir->polling));
	अगर (dev->num_button_polling_addresses)
		schedule_delayed_work(&dev->buttons_query_work,
				      msecs_to_jअगरfies(dev->button_polling_पूर्णांकerval));
	वापस 0;
पूर्ण

अटल काष्ठा em28xx_ops rc_ops = अणु
	.id   = EM28XX_RC,
	.name = "Em28xx Input Extension",
	.init = em28xx_ir_init,
	.fini = em28xx_ir_fini,
	.suspend = em28xx_ir_suspend,
	.resume = em28xx_ir_resume,
पूर्ण;

अटल पूर्णांक __init em28xx_rc_रेजिस्टर(व्योम)
अणु
	वापस em28xx_रेजिस्टर_extension(&rc_ops);
पूर्ण

अटल व्योम __निकास em28xx_rc_unरेजिस्टर(व्योम)
अणु
	em28xx_unरेजिस्टर_extension(&rc_ops);
पूर्ण

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_DESCRIPTION(DRIVER_DESC " - input interface");
MODULE_VERSION(EM28XX_VERSION);

module_init(em28xx_rc_रेजिस्टर);
module_निकास(em28xx_rc_unरेजिस्टर);
