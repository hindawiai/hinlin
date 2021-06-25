<शैली गुरु>
/*
 * Generic linux-input device driver क्रम keyboard devices
 *
 * Copyright (c) 2001 Brian S. Julin
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *
 * References:
 * HP-HIL Technical Reference Manual.  Hewlett Packard Product No. 45918A
 *
 */

#समावेश <linux/hil.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/completion.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci_ids.h>

#घोषणा PREFIX "HIL: "

MODULE_AUTHOR("Brian S. Julin <bri@calyx.com>");
MODULE_DESCRIPTION("HIL keyboard/mouse driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("serio:ty03pr25id00ex*"); /* HIL keyboard */
MODULE_ALIAS("serio:ty03pr25id0Fex*"); /* HIL mouse */

#घोषणा HIL_PACKET_MAX_LENGTH 16

#घोषणा HIL_KBD_SET1_UPBIT 0x01
#घोषणा HIL_KBD_SET1_SHIFT 1
अटल अचिन्हित पूर्णांक hil_kbd_set1[HIL_KEYCODES_SET1_TBLSIZE] __पढ़ो_mostly =
	अणु HIL_KEYCODES_SET1 पूर्ण;

#घोषणा HIL_KBD_SET2_UPBIT 0x01
#घोषणा HIL_KBD_SET2_SHIFT 1
/* Set2 is user defined */

#घोषणा HIL_KBD_SET3_UPBIT 0x80
#घोषणा HIL_KBD_SET3_SHIFT 0
अटल अचिन्हित पूर्णांक hil_kbd_set3[HIL_KEYCODES_SET3_TBLSIZE] __पढ़ो_mostly =
	अणु HIL_KEYCODES_SET3 पूर्ण;

अटल स्थिर अक्षर hil_language[][16] = अणु HIL_LOCALE_MAP पूर्ण;

काष्ठा hil_dev अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;

	/* Input buffer and index क्रम packets from HIL bus. */
	hil_packet data[HIL_PACKET_MAX_LENGTH];
	पूर्णांक idx4; /* four counts per packet */

	/* Raw device info records from HIL bus, see hil.h क्रम fields. */
	अक्षर	idd[HIL_PACKET_MAX_LENGTH];	/* DID byte and IDD record */
	अक्षर	rsc[HIL_PACKET_MAX_LENGTH];	/* RSC record */
	अक्षर	exd[HIL_PACKET_MAX_LENGTH];	/* EXD record */
	अक्षर	rnm[HIL_PACKET_MAX_LENGTH + 1];	/* RNM record + शून्य term. */

	काष्ठा completion cmd_करोne;

	bool is_poपूर्णांकer;
	/* Extra device details needed क्रम poपूर्णांकing devices. */
	अचिन्हित पूर्णांक nbtn, naxes;
	अचिन्हित पूर्णांक btnmap[7];
पूर्ण;

अटल bool hil_dev_is_command_response(hil_packet p)
अणु
	अगर ((p & ~HIL_CMDCT_POL) == (HIL_ERR_INT | HIL_PKT_CMD | HIL_CMD_POL))
		वापस false;

	अगर ((p & ~HIL_CMDCT_RPL) == (HIL_ERR_INT | HIL_PKT_CMD | HIL_CMD_RPL))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम hil_dev_handle_command_response(काष्ठा hil_dev *dev)
अणु
	hil_packet p;
	अक्षर *buf;
	पूर्णांक i, idx;

	idx = dev->idx4 / 4;
	p = dev->data[idx - 1];

	चयन (p & HIL_PKT_DATA_MASK) अणु
	हाल HIL_CMD_IDD:
		buf = dev->idd;
		अवरोध;

	हाल HIL_CMD_RSC:
		buf = dev->rsc;
		अवरोध;

	हाल HIL_CMD_EXD:
		buf = dev->exd;
		अवरोध;

	हाल HIL_CMD_RNM:
		dev->rnm[HIL_PACKET_MAX_LENGTH] = 0;
		buf = dev->rnm;
		अवरोध;

	शेष:
		/* These occur when device isn't present */
		अगर (p != (HIL_ERR_INT | HIL_PKT_CMD)) अणु
			/* Anything अन्यथा we'd like to know about. */
			prपूर्णांकk(KERN_WARNING PREFIX "Device sent unknown record %x\n", p);
		पूर्ण
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < idx; i++)
		buf[i] = dev->data[i] & HIL_PKT_DATA_MASK;
	क्रम (; i < HIL_PACKET_MAX_LENGTH; i++)
		buf[i] = 0;
 out:
	complete(&dev->cmd_करोne);
पूर्ण

अटल व्योम hil_dev_handle_kbd_events(काष्ठा hil_dev *kbd)
अणु
	काष्ठा input_dev *dev = kbd->dev;
	पूर्णांक idx = kbd->idx4 / 4;
	पूर्णांक i;

	चयन (kbd->data[0] & HIL_POL_CHARTYPE_MASK) अणु
	हाल HIL_POL_CHARTYPE_NONE:
		वापस;

	हाल HIL_POL_CHARTYPE_ASCII:
		क्रम (i = 1; i < idx - 1; i++)
			input_report_key(dev, kbd->data[i] & 0x7f, 1);
		अवरोध;

	हाल HIL_POL_CHARTYPE_RSVD1:
	हाल HIL_POL_CHARTYPE_RSVD2:
	हाल HIL_POL_CHARTYPE_BINARY:
		क्रम (i = 1; i < idx - 1; i++)
			input_report_key(dev, kbd->data[i], 1);
		अवरोध;

	हाल HIL_POL_CHARTYPE_SET1:
		क्रम (i = 1; i < idx - 1; i++) अणु
			अचिन्हित पूर्णांक key = kbd->data[i];
			पूर्णांक up = key & HIL_KBD_SET1_UPBIT;

			key &= (~HIL_KBD_SET1_UPBIT & 0xff);
			key = hil_kbd_set1[key >> HIL_KBD_SET1_SHIFT];
			input_report_key(dev, key, !up);
		पूर्ण
		अवरोध;

	हाल HIL_POL_CHARTYPE_SET2:
		क्रम (i = 1; i < idx - 1; i++) अणु
			अचिन्हित पूर्णांक key = kbd->data[i];
			पूर्णांक up = key & HIL_KBD_SET2_UPBIT;

			key &= (~HIL_KBD_SET1_UPBIT & 0xff);
			key = key >> HIL_KBD_SET2_SHIFT;
			input_report_key(dev, key, !up);
		पूर्ण
		अवरोध;

	हाल HIL_POL_CHARTYPE_SET3:
		क्रम (i = 1; i < idx - 1; i++) अणु
			अचिन्हित पूर्णांक key = kbd->data[i];
			पूर्णांक up = key & HIL_KBD_SET3_UPBIT;

			key &= (~HIL_KBD_SET1_UPBIT & 0xff);
			key = hil_kbd_set3[key >> HIL_KBD_SET3_SHIFT];
			input_report_key(dev, key, !up);
		पूर्ण
		अवरोध;
	पूर्ण

	input_sync(dev);
पूर्ण

अटल व्योम hil_dev_handle_ptr_events(काष्ठा hil_dev *ptr)
अणु
	काष्ठा input_dev *dev = ptr->dev;
	पूर्णांक idx = ptr->idx4 / 4;
	hil_packet p = ptr->data[idx - 1];
	पूर्णांक i, cnt, laxis;
	bool असलdev, ax16;

	अगर ((p & HIL_CMDCT_POL) != idx - 1) अणु
		prपूर्णांकk(KERN_WARNING PREFIX
			"Malformed poll packet %x (idx = %i)\n", p, idx);
		वापस;
	पूर्ण

	i = (p & HIL_POL_AXIS_ALT) ? 3 : 0;
	laxis = (p & HIL_POL_NUM_AXES_MASK) + i;

	ax16 = ptr->idd[1] & HIL_IDD_HEADER_16BIT; /* 8 or 16bit resolution */
	असलdev = ptr->idd[1] & HIL_IDD_HEADER_ABS;

	क्रम (cnt = 1; i < laxis; i++) अणु
		अचिन्हित पूर्णांक lo, hi, val;

		lo = ptr->data[cnt++] & HIL_PKT_DATA_MASK;
		hi = ax16 ? (ptr->data[cnt++] & HIL_PKT_DATA_MASK) : 0;

		अगर (असलdev) अणु
			val = lo + (hi << 8);
#अगर_घोषित TABLET_AUTOADJUST
			अगर (val < input_असल_get_min(dev, ABS_X + i))
				input_असल_set_min(dev, ABS_X + i, val);
			अगर (val > input_असल_get_max(dev, ABS_X + i))
				input_असल_set_max(dev, ABS_X + i, val);
#पूर्ण_अगर
			अगर (i % 3)
				val = input_असल_get_max(dev, ABS_X + i) - val;
			input_report_असल(dev, ABS_X + i, val);
		पूर्ण अन्यथा अणु
			val = (पूर्णांक) (((पूर्णांक8_t) lo) | ((पूर्णांक8_t) hi << 8));
			अगर (i % 3)
				val *= -1;
			input_report_rel(dev, REL_X + i, val);
		पूर्ण
	पूर्ण

	जबतक (cnt < idx - 1) अणु
		अचिन्हित पूर्णांक btn = ptr->data[cnt++];
		पूर्णांक up = btn & 1;

		btn &= 0xfe;
		अगर (btn == 0x8e)
			जारी; /* TODO: proximity == touch? */
		अगर (btn > 0x8c || btn < 0x80)
			जारी;
		btn = (btn - 0x80) >> 1;
		btn = ptr->btnmap[btn];
		input_report_key(dev, btn, !up);
	पूर्ण

	input_sync(dev);
पूर्ण

अटल व्योम hil_dev_process_err(काष्ठा hil_dev *dev)
अणु
	prपूर्णांकk(KERN_WARNING PREFIX "errored HIL packet\n");
	dev->idx4 = 0;
	complete(&dev->cmd_करोne); /* just in हाल somebody is रुकोing */
पूर्ण

अटल irqवापस_t hil_dev_पूर्णांकerrupt(काष्ठा serio *serio,
				अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा hil_dev *dev;
	hil_packet packet;
	पूर्णांक idx;

	dev = serio_get_drvdata(serio);
	BUG_ON(dev == शून्य);

	अगर (dev->idx4 >= HIL_PACKET_MAX_LENGTH * माप(hil_packet)) अणु
		hil_dev_process_err(dev);
		जाओ out;
	पूर्ण

	idx = dev->idx4 / 4;
	अगर (!(dev->idx4 % 4))
		dev->data[idx] = 0;
	packet = dev->data[idx];
	packet |= ((hil_packet)data) << ((3 - (dev->idx4 % 4)) * 8);
	dev->data[idx] = packet;

	/* Records of N 4-byte hil_packets must terminate with a command. */
	अगर ((++dev->idx4 % 4) == 0) अणु
		अगर ((packet & 0xffff0000) != HIL_ERR_INT) अणु
			hil_dev_process_err(dev);
		पूर्ण अन्यथा अगर (packet & HIL_PKT_CMD) अणु
			अगर (hil_dev_is_command_response(packet))
				hil_dev_handle_command_response(dev);
			अन्यथा अगर (dev->is_poपूर्णांकer)
				hil_dev_handle_ptr_events(dev);
			अन्यथा
				hil_dev_handle_kbd_events(dev);
			dev->idx4 = 0;
		पूर्ण
	पूर्ण
 out:
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम hil_dev_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा hil_dev *dev = serio_get_drvdata(serio);

	BUG_ON(dev == शून्य);

	serio_बंद(serio);
	input_unरेजिस्टर_device(dev->dev);
	serio_set_drvdata(serio, शून्य);
	kमुक्त(dev);
पूर्ण

अटल व्योम hil_dev_keyboard_setup(काष्ठा hil_dev *kbd)
अणु
	काष्ठा input_dev *input_dev = kbd->dev;
	uपूर्णांक8_t did = kbd->idd[0];
	पूर्णांक i;

	input_dev->evbit[0]	= BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	input_dev->ledbit[0]	= BIT_MASK(LED_NUML) | BIT_MASK(LED_CAPSL) |
				  BIT_MASK(LED_SCROLLL);

	क्रम (i = 0; i < 128; i++) अणु
		__set_bit(hil_kbd_set1[i], input_dev->keybit);
		__set_bit(hil_kbd_set3[i], input_dev->keybit);
	पूर्ण
	__clear_bit(KEY_RESERVED, input_dev->keybit);

	input_dev->keycodemax	= HIL_KEYCODES_SET1_TBLSIZE;
	input_dev->keycodesize	= माप(hil_kbd_set1[0]);
	input_dev->keycode	= hil_kbd_set1;

	input_dev->name	= म_माप(kbd->rnm) ? kbd->rnm : "HIL keyboard";
	input_dev->phys	= "hpkbd/input0";

	prपूर्णांकk(KERN_INFO PREFIX "HIL keyboard found (did = 0x%02x, lang = %s)\n",
		did, hil_language[did & HIL_IDD_DID_TYPE_KB_LANG_MASK]);
पूर्ण

अटल व्योम hil_dev_poपूर्णांकer_setup(काष्ठा hil_dev *ptr)
अणु
	काष्ठा input_dev *input_dev = ptr->dev;
	uपूर्णांक8_t did = ptr->idd[0];
	uपूर्णांक8_t *idd = ptr->idd + 1;
	अचिन्हित पूर्णांक naxsets = HIL_IDD_NUM_AXSETS(*idd);
	अचिन्हित पूर्णांक i, btntype;
	स्थिर अक्षर *txt;

	ptr->naxes = HIL_IDD_NUM_AXES_PER_SET(*idd);

	चयन (did & HIL_IDD_DID_TYPE_MASK) अणु
	हाल HIL_IDD_DID_TYPE_REL:
		input_dev->evbit[0] = BIT_MASK(EV_REL);

		क्रम (i = 0; i < ptr->naxes; i++)
			__set_bit(REL_X + i, input_dev->relbit);

		क्रम (i = 3; naxsets > 1 && i < ptr->naxes + 3; i++)
			__set_bit(REL_X + i, input_dev->relbit);

		txt = "relative";
		अवरोध;

	हाल HIL_IDD_DID_TYPE_ABS:
		input_dev->evbit[0] = BIT_MASK(EV_ABS);

		क्रम (i = 0; i < ptr->naxes; i++)
			input_set_असल_params(input_dev, ABS_X + i,
					0, HIL_IDD_AXIS_MAX(idd, i), 0, 0);

		क्रम (i = 3; naxsets > 1 && i < ptr->naxes + 3; i++)
			input_set_असल_params(input_dev, ABS_X + i,
					0, HIL_IDD_AXIS_MAX(idd, i - 3), 0, 0);

#अगर_घोषित TABLET_AUTOADJUST
		क्रम (i = 0; i < ABS_MAX; i++) अणु
			पूर्णांक dअगरf = input_असल_get_max(input_dev, ABS_X + i) / 10;
			input_असल_set_min(input_dev, ABS_X + i,
				input_असल_get_min(input_dev, ABS_X + i) + dअगरf);
			input_असल_set_max(input_dev, ABS_X + i,
				input_असल_get_max(input_dev, ABS_X + i) - dअगरf);
		पूर्ण
#पूर्ण_अगर

		txt = "absolute";
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	ptr->nbtn = HIL_IDD_NUM_BUTTONS(idd);
	अगर (ptr->nbtn)
		input_dev->evbit[0] |= BIT_MASK(EV_KEY);

	btntype = BTN_MISC;
	अगर ((did & HIL_IDD_DID_ABS_TABLET_MASK) == HIL_IDD_DID_ABS_TABLET)
#अगर_घोषित TABLET_SIMULATES_MOUSE
		btntype = BTN_TOUCH;
#अन्यथा
		btntype = BTN_DIGI;
#पूर्ण_अगर
	अगर ((did & HIL_IDD_DID_ABS_TSCREEN_MASK) == HIL_IDD_DID_ABS_TSCREEN)
		btntype = BTN_TOUCH;

	अगर ((did & HIL_IDD_DID_REL_MOUSE_MASK) == HIL_IDD_DID_REL_MOUSE)
		btntype = BTN_MOUSE;

	क्रम (i = 0; i < ptr->nbtn; i++) अणु
		__set_bit(btntype | i, input_dev->keybit);
		ptr->btnmap[i] = btntype | i;
	पूर्ण

	अगर (btntype == BTN_MOUSE) अणु
		/* Swap buttons 2 and 3 */
		ptr->btnmap[1] = BTN_MIDDLE;
		ptr->btnmap[2] = BTN_RIGHT;
	पूर्ण

	input_dev->name = म_माप(ptr->rnm) ? ptr->rnm : "HIL pointer device";

	prपूर्णांकk(KERN_INFO PREFIX
		"HIL pointer device found (did: 0x%02x, axis: %s)\n",
		did, txt);
	prपूर्णांकk(KERN_INFO PREFIX
		"HIL pointer has %i buttons and %i sets of %i axes\n",
		ptr->nbtn, naxsets, ptr->naxes);
पूर्ण

अटल पूर्णांक hil_dev_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा hil_dev *dev;
	काष्ठा input_dev *input_dev;
	uपूर्णांक8_t did, *idd;
	पूर्णांक error;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!dev || !input_dev) अणु
		error = -ENOMEM;
		जाओ bail0;
	पूर्ण

	dev->serio = serio;
	dev->dev = input_dev;

	error = serio_खोलो(serio, drv);
	अगर (error)
		जाओ bail0;

	serio_set_drvdata(serio, dev);

	/* Get device info.  MLC driver supplies devid/status/etc. */
	init_completion(&dev->cmd_करोne);
	serio_ग_लिखो(serio, 0);
	serio_ग_लिखो(serio, 0);
	serio_ग_लिखो(serio, HIL_PKT_CMD >> 8);
	serio_ग_लिखो(serio, HIL_CMD_IDD);
	error = रुको_क्रम_completion_समाप्तable(&dev->cmd_करोne);
	अगर (error)
		जाओ bail1;

	reinit_completion(&dev->cmd_करोne);
	serio_ग_लिखो(serio, 0);
	serio_ग_लिखो(serio, 0);
	serio_ग_लिखो(serio, HIL_PKT_CMD >> 8);
	serio_ग_लिखो(serio, HIL_CMD_RSC);
	error = रुको_क्रम_completion_समाप्तable(&dev->cmd_करोne);
	अगर (error)
		जाओ bail1;

	reinit_completion(&dev->cmd_करोne);
	serio_ग_लिखो(serio, 0);
	serio_ग_लिखो(serio, 0);
	serio_ग_लिखो(serio, HIL_PKT_CMD >> 8);
	serio_ग_लिखो(serio, HIL_CMD_RNM);
	error = रुको_क्रम_completion_समाप्तable(&dev->cmd_करोne);
	अगर (error)
		जाओ bail1;

	reinit_completion(&dev->cmd_करोne);
	serio_ग_लिखो(serio, 0);
	serio_ग_लिखो(serio, 0);
	serio_ग_लिखो(serio, HIL_PKT_CMD >> 8);
	serio_ग_लिखो(serio, HIL_CMD_EXD);
	error = रुको_क्रम_completion_समाप्तable(&dev->cmd_करोne);
	अगर (error)
		जाओ bail1;

	did = dev->idd[0];
	idd = dev->idd + 1;

	चयन (did & HIL_IDD_DID_TYPE_MASK) अणु
	हाल HIL_IDD_DID_TYPE_KB_INTEGRAL:
	हाल HIL_IDD_DID_TYPE_KB_ITF:
	हाल HIL_IDD_DID_TYPE_KB_RSVD:
	हाल HIL_IDD_DID_TYPE_CHAR:
		अगर (HIL_IDD_NUM_BUTTONS(idd) ||
		    HIL_IDD_NUM_AXES_PER_SET(*idd)) अणु
			prपूर्णांकk(KERN_INFO PREFIX
				"combo devices are not supported.\n");
			जाओ bail1;
		पूर्ण

		dev->is_poपूर्णांकer = false;
		hil_dev_keyboard_setup(dev);
		अवरोध;

	हाल HIL_IDD_DID_TYPE_REL:
	हाल HIL_IDD_DID_TYPE_ABS:
		dev->is_poपूर्णांकer = true;
		hil_dev_poपूर्णांकer_setup(dev);
		अवरोध;

	शेष:
		जाओ bail1;
	पूर्ण

	input_dev->id.bustype	= BUS_HIL;
	input_dev->id.venकरोr	= PCI_VENDOR_ID_HP;
	input_dev->id.product	= 0x0001; /* TODO: get from kbd->rsc */
	input_dev->id.version	= 0x0100; /* TODO: get from kbd->rsc */
	input_dev->dev.parent	= &serio->dev;

	अगर (!dev->is_poपूर्णांकer) अणु
		serio_ग_लिखो(serio, 0);
		serio_ग_लिखो(serio, 0);
		serio_ग_लिखो(serio, HIL_PKT_CMD >> 8);
		/* Enable Keyचयन Autorepeat 1 */
		serio_ग_लिखो(serio, HIL_CMD_EK1);
		/* No need to रुको क्रम completion */
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error)
		जाओ bail1;

	वापस 0;

 bail1:
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
 bail0:
	input_मुक्त_device(input_dev);
	kमुक्त(dev);
	वापस error;
पूर्ण

अटल स्थिर काष्ठा serio_device_id hil_dev_ids[] = अणु
	अणु
		.type = SERIO_HIL_MLC,
		.proto = SERIO_HIL,
		.id = SERIO_ANY,
		.extra = SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, hil_dev_ids);

अटल काष्ठा serio_driver hil_serio_drv = अणु
	.driver		= अणु
		.name	= "hil_dev",
	पूर्ण,
	.description	= "HP HIL keyboard/mouse/tablet driver",
	.id_table	= hil_dev_ids,
	.connect	= hil_dev_connect,
	.disconnect	= hil_dev_disconnect,
	.पूर्णांकerrupt	= hil_dev_पूर्णांकerrupt
पूर्ण;

module_serio_driver(hil_serio_drv);
