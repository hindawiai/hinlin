<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम IMS Passenger Control Unit Devices
 *
 * Copyright (C) 2013 The IMS Company
 */

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/ihex.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/usb/cdc.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा IMS_PCU_KEYMAP_LEN		32

काष्ठा ims_pcu_buttons अणु
	काष्ठा input_dev *input;
	अक्षर name[32];
	अक्षर phys[32];
	अचिन्हित लघु keymap[IMS_PCU_KEYMAP_LEN];
पूर्ण;

काष्ठा ims_pcu_gamepad अणु
	काष्ठा input_dev *input;
	अक्षर name[32];
	अक्षर phys[32];
पूर्ण;

काष्ठा ims_pcu_backlight अणु
	काष्ठा led_classdev cdev;
	अक्षर name[32];
पूर्ण;

#घोषणा IMS_PCU_PART_NUMBER_LEN		15
#घोषणा IMS_PCU_SERIAL_NUMBER_LEN	8
#घोषणा IMS_PCU_DOM_LEN			8
#घोषणा IMS_PCU_FW_VERSION_LEN		(9 + 1)
#घोषणा IMS_PCU_BL_VERSION_LEN		(9 + 1)
#घोषणा IMS_PCU_BL_RESET_REASON_LEN	(2 + 1)

#घोषणा IMS_PCU_PCU_B_DEVICE_ID		5

#घोषणा IMS_PCU_BUF_SIZE		128

काष्ठा ims_pcu अणु
	काष्ठा usb_device *udev;
	काष्ठा device *dev; /* control पूर्णांकerface's device, used क्रम logging */

	अचिन्हित पूर्णांक device_no;

	bool bootloader_mode;

	अक्षर part_number[IMS_PCU_PART_NUMBER_LEN];
	अक्षर serial_number[IMS_PCU_SERIAL_NUMBER_LEN];
	अक्षर date_of_manufacturing[IMS_PCU_DOM_LEN];
	अक्षर fw_version[IMS_PCU_FW_VERSION_LEN];
	अक्षर bl_version[IMS_PCU_BL_VERSION_LEN];
	अक्षर reset_reason[IMS_PCU_BL_RESET_REASON_LEN];
	पूर्णांक update_firmware_status;
	u8 device_id;

	u8 ofn_reg_addr;

	काष्ठा usb_पूर्णांकerface *ctrl_पूर्णांकf;

	काष्ठा usb_endpoपूर्णांक_descriptor *ep_ctrl;
	काष्ठा urb *urb_ctrl;
	u8 *urb_ctrl_buf;
	dma_addr_t ctrl_dma;
	माप_प्रकार max_ctrl_size;

	काष्ठा usb_पूर्णांकerface *data_पूर्णांकf;

	काष्ठा usb_endpoपूर्णांक_descriptor *ep_in;
	काष्ठा urb *urb_in;
	u8 *urb_in_buf;
	dma_addr_t पढ़ो_dma;
	माप_प्रकार max_in_size;

	काष्ठा usb_endpoपूर्णांक_descriptor *ep_out;
	u8 *urb_out_buf;
	माप_प्रकार max_out_size;

	u8 पढ़ो_buf[IMS_PCU_BUF_SIZE];
	u8 पढ़ो_pos;
	u8 check_sum;
	bool have_stx;
	bool have_dle;

	u8 cmd_buf[IMS_PCU_BUF_SIZE];
	u8 ack_id;
	u8 expected_response;
	u8 cmd_buf_len;
	काष्ठा completion cmd_करोne;
	काष्ठा mutex cmd_mutex;

	u32 fw_start_addr;
	u32 fw_end_addr;
	काष्ठा completion async_firmware_करोne;

	काष्ठा ims_pcu_buttons buttons;
	काष्ठा ims_pcu_gamepad *gamepad;
	काष्ठा ims_pcu_backlight backlight;

	bool setup_complete; /* Input and LED devices have been created */
पूर्ण;


/*********************************************************************
 *             Buttons Input device support                          *
 *********************************************************************/

अटल स्थिर अचिन्हित लघु ims_pcu_keymap_1[] = अणु
	[1] = KEY_ATTENDANT_OFF,
	[2] = KEY_ATTENDANT_ON,
	[3] = KEY_LIGHTS_TOGGLE,
	[4] = KEY_VOLUMEUP,
	[5] = KEY_VOLUMEDOWN,
	[6] = KEY_INFO,
पूर्ण;

अटल स्थिर अचिन्हित लघु ims_pcu_keymap_2[] = अणु
	[4] = KEY_VOLUMEUP,
	[5] = KEY_VOLUMEDOWN,
	[6] = KEY_INFO,
पूर्ण;

अटल स्थिर अचिन्हित लघु ims_pcu_keymap_3[] = अणु
	[1] = KEY_HOMEPAGE,
	[2] = KEY_ATTENDANT_TOGGLE,
	[3] = KEY_LIGHTS_TOGGLE,
	[4] = KEY_VOLUMEUP,
	[5] = KEY_VOLUMEDOWN,
	[6] = KEY_DISPLAYTOGGLE,
	[18] = KEY_PLAYPAUSE,
पूर्ण;

अटल स्थिर अचिन्हित लघु ims_pcu_keymap_4[] = अणु
	[1] = KEY_ATTENDANT_OFF,
	[2] = KEY_ATTENDANT_ON,
	[3] = KEY_LIGHTS_TOGGLE,
	[4] = KEY_VOLUMEUP,
	[5] = KEY_VOLUMEDOWN,
	[6] = KEY_INFO,
	[18] = KEY_PLAYPAUSE,
पूर्ण;

अटल स्थिर अचिन्हित लघु ims_pcu_keymap_5[] = अणु
	[1] = KEY_ATTENDANT_OFF,
	[2] = KEY_ATTENDANT_ON,
	[3] = KEY_LIGHTS_TOGGLE,
पूर्ण;

काष्ठा ims_pcu_device_info अणु
	स्थिर अचिन्हित लघु *keymap;
	माप_प्रकार keymap_len;
	bool has_gamepad;
पूर्ण;

#घोषणा IMS_PCU_DEVINFO(_n, _gamepad)				\
	[_n] = अणु						\
		.keymap = ims_pcu_keymap_##_n,			\
		.keymap_len = ARRAY_SIZE(ims_pcu_keymap_##_n),	\
		.has_gamepad = _gamepad,			\
	पूर्ण

अटल स्थिर काष्ठा ims_pcu_device_info ims_pcu_device_info[] = अणु
	IMS_PCU_DEVINFO(1, true),
	IMS_PCU_DEVINFO(2, true),
	IMS_PCU_DEVINFO(3, true),
	IMS_PCU_DEVINFO(4, true),
	IMS_PCU_DEVINFO(5, false),
पूर्ण;

अटल व्योम ims_pcu_buttons_report(काष्ठा ims_pcu *pcu, u32 data)
अणु
	काष्ठा ims_pcu_buttons *buttons = &pcu->buttons;
	काष्ठा input_dev *input = buttons->input;
	पूर्णांक i;

	क्रम (i = 0; i < 32; i++) अणु
		अचिन्हित लघु keycode = buttons->keymap[i];

		अगर (keycode != KEY_RESERVED)
			input_report_key(input, keycode, data & (1UL << i));
	पूर्ण

	input_sync(input);
पूर्ण

अटल पूर्णांक ims_pcu_setup_buttons(काष्ठा ims_pcu *pcu,
				 स्थिर अचिन्हित लघु *keymap,
				 माप_प्रकार keymap_len)
अणु
	काष्ठा ims_pcu_buttons *buttons = &pcu->buttons;
	काष्ठा input_dev *input;
	पूर्णांक i;
	पूर्णांक error;

	input = input_allocate_device();
	अगर (!input) अणु
		dev_err(pcu->dev,
			"Not enough memory for input input device\n");
		वापस -ENOMEM;
	पूर्ण

	snम_लिखो(buttons->name, माप(buttons->name),
		 "IMS PCU#%d Button Interface", pcu->device_no);

	usb_make_path(pcu->udev, buttons->phys, माप(buttons->phys));
	strlcat(buttons->phys, "/input0", माप(buttons->phys));

	स_नकल(buttons->keymap, keymap, माप(*keymap) * keymap_len);

	input->name = buttons->name;
	input->phys = buttons->phys;
	usb_to_input_id(pcu->udev, &input->id);
	input->dev.parent = &pcu->ctrl_पूर्णांकf->dev;

	input->keycode = buttons->keymap;
	input->keycodemax = ARRAY_SIZE(buttons->keymap);
	input->keycodesize = माप(buttons->keymap[0]);

	__set_bit(EV_KEY, input->evbit);
	क्रम (i = 0; i < IMS_PCU_KEYMAP_LEN; i++)
		__set_bit(buttons->keymap[i], input->keybit);
	__clear_bit(KEY_RESERVED, input->keybit);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(pcu->dev,
			"Failed to register buttons input device: %d\n",
			error);
		input_मुक्त_device(input);
		वापस error;
	पूर्ण

	buttons->input = input;
	वापस 0;
पूर्ण

अटल व्योम ims_pcu_destroy_buttons(काष्ठा ims_pcu *pcu)
अणु
	काष्ठा ims_pcu_buttons *buttons = &pcu->buttons;

	input_unरेजिस्टर_device(buttons->input);
पूर्ण


/*********************************************************************
 *             Gamepad Input device support                          *
 *********************************************************************/

अटल व्योम ims_pcu_gamepad_report(काष्ठा ims_pcu *pcu, u32 data)
अणु
	काष्ठा ims_pcu_gamepad *gamepad = pcu->gamepad;
	काष्ठा input_dev *input = gamepad->input;
	पूर्णांक x, y;

	x = !!(data & (1 << 14)) - !!(data & (1 << 13));
	y = !!(data & (1 << 12)) - !!(data & (1 << 11));

	input_report_असल(input, ABS_X, x);
	input_report_असल(input, ABS_Y, y);

	input_report_key(input, BTN_A, data & (1 << 7));
	input_report_key(input, BTN_B, data & (1 << 8));
	input_report_key(input, BTN_X, data & (1 << 9));
	input_report_key(input, BTN_Y, data & (1 << 10));
	input_report_key(input, BTN_START, data & (1 << 15));
	input_report_key(input, BTN_SELECT, data & (1 << 16));

	input_sync(input);
पूर्ण

अटल पूर्णांक ims_pcu_setup_gamepad(काष्ठा ims_pcu *pcu)
अणु
	काष्ठा ims_pcu_gamepad *gamepad;
	काष्ठा input_dev *input;
	पूर्णांक error;

	gamepad = kzalloc(माप(काष्ठा ims_pcu_gamepad), GFP_KERNEL);
	input = input_allocate_device();
	अगर (!gamepad || !input) अणु
		dev_err(pcu->dev,
			"Not enough memory for gamepad device\n");
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	gamepad->input = input;

	snम_लिखो(gamepad->name, माप(gamepad->name),
		 "IMS PCU#%d Gamepad Interface", pcu->device_no);

	usb_make_path(pcu->udev, gamepad->phys, माप(gamepad->phys));
	strlcat(gamepad->phys, "/input1", माप(gamepad->phys));

	input->name = gamepad->name;
	input->phys = gamepad->phys;
	usb_to_input_id(pcu->udev, &input->id);
	input->dev.parent = &pcu->ctrl_पूर्णांकf->dev;

	__set_bit(EV_KEY, input->evbit);
	__set_bit(BTN_A, input->keybit);
	__set_bit(BTN_B, input->keybit);
	__set_bit(BTN_X, input->keybit);
	__set_bit(BTN_Y, input->keybit);
	__set_bit(BTN_START, input->keybit);
	__set_bit(BTN_SELECT, input->keybit);

	__set_bit(EV_ABS, input->evbit);
	input_set_असल_params(input, ABS_X, -1, 1, 0, 0);
	input_set_असल_params(input, ABS_Y, -1, 1, 0, 0);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(pcu->dev,
			"Failed to register gamepad input device: %d\n",
			error);
		जाओ err_मुक्त_mem;
	पूर्ण

	pcu->gamepad = gamepad;
	वापस 0;

err_मुक्त_mem:
	input_मुक्त_device(input);
	kमुक्त(gamepad);
	वापस error;
पूर्ण

अटल व्योम ims_pcu_destroy_gamepad(काष्ठा ims_pcu *pcu)
अणु
	काष्ठा ims_pcu_gamepad *gamepad = pcu->gamepad;

	input_unरेजिस्टर_device(gamepad->input);
	kमुक्त(gamepad);
पूर्ण


/*********************************************************************
 *             PCU Communication protocol handling                   *
 *********************************************************************/

#घोषणा IMS_PCU_PROTOCOL_STX		0x02
#घोषणा IMS_PCU_PROTOCOL_ETX		0x03
#घोषणा IMS_PCU_PROTOCOL_DLE		0x10

/* PCU commands */
#घोषणा IMS_PCU_CMD_STATUS		0xa0
#घोषणा IMS_PCU_CMD_PCU_RESET		0xa1
#घोषणा IMS_PCU_CMD_RESET_REASON	0xa2
#घोषणा IMS_PCU_CMD_SEND_BUTTONS	0xa3
#घोषणा IMS_PCU_CMD_JUMP_TO_BTLDR	0xa4
#घोषणा IMS_PCU_CMD_GET_INFO		0xa5
#घोषणा IMS_PCU_CMD_SET_BRIGHTNESS	0xa6
#घोषणा IMS_PCU_CMD_EEPROM		0xa7
#घोषणा IMS_PCU_CMD_GET_FW_VERSION	0xa8
#घोषणा IMS_PCU_CMD_GET_BL_VERSION	0xa9
#घोषणा IMS_PCU_CMD_SET_INFO		0xab
#घोषणा IMS_PCU_CMD_GET_BRIGHTNESS	0xac
#घोषणा IMS_PCU_CMD_GET_DEVICE_ID	0xae
#घोषणा IMS_PCU_CMD_SPECIAL_INFO	0xb0
#घोषणा IMS_PCU_CMD_BOOTLOADER		0xb1	/* Pass data to bootloader */
#घोषणा IMS_PCU_CMD_OFN_SET_CONFIG	0xb3
#घोषणा IMS_PCU_CMD_OFN_GET_CONFIG	0xb4

/* PCU responses */
#घोषणा IMS_PCU_RSP_STATUS		0xc0
#घोषणा IMS_PCU_RSP_PCU_RESET		0	/* Originally 0xc1 */
#घोषणा IMS_PCU_RSP_RESET_REASON	0xc2
#घोषणा IMS_PCU_RSP_SEND_BUTTONS	0xc3
#घोषणा IMS_PCU_RSP_JUMP_TO_BTLDR	0	/* Originally 0xc4 */
#घोषणा IMS_PCU_RSP_GET_INFO		0xc5
#घोषणा IMS_PCU_RSP_SET_BRIGHTNESS	0xc6
#घोषणा IMS_PCU_RSP_EEPROM		0xc7
#घोषणा IMS_PCU_RSP_GET_FW_VERSION	0xc8
#घोषणा IMS_PCU_RSP_GET_BL_VERSION	0xc9
#घोषणा IMS_PCU_RSP_SET_INFO		0xcb
#घोषणा IMS_PCU_RSP_GET_BRIGHTNESS	0xcc
#घोषणा IMS_PCU_RSP_CMD_INVALID		0xcd
#घोषणा IMS_PCU_RSP_GET_DEVICE_ID	0xce
#घोषणा IMS_PCU_RSP_SPECIAL_INFO	0xd0
#घोषणा IMS_PCU_RSP_BOOTLOADER		0xd1	/* Bootloader response */
#घोषणा IMS_PCU_RSP_OFN_SET_CONFIG	0xd2
#घोषणा IMS_PCU_RSP_OFN_GET_CONFIG	0xd3


#घोषणा IMS_PCU_RSP_EVNT_BUTTONS	0xe0	/* Unsolicited, button state */
#घोषणा IMS_PCU_GAMEPAD_MASK		0x0001ff80UL	/* Bits 7 through 16 */


#घोषणा IMS_PCU_MIN_PACKET_LEN		3
#घोषणा IMS_PCU_DATA_OFFSET		2

#घोषणा IMS_PCU_CMD_WRITE_TIMEOUT	100 /* msec */
#घोषणा IMS_PCU_CMD_RESPONSE_TIMEOUT	500 /* msec */

अटल व्योम ims_pcu_report_events(काष्ठा ims_pcu *pcu)
अणु
	u32 data = get_unaligned_be32(&pcu->पढ़ो_buf[3]);

	ims_pcu_buttons_report(pcu, data & ~IMS_PCU_GAMEPAD_MASK);
	अगर (pcu->gamepad)
		ims_pcu_gamepad_report(pcu, data);
पूर्ण

अटल व्योम ims_pcu_handle_response(काष्ठा ims_pcu *pcu)
अणु
	चयन (pcu->पढ़ो_buf[0]) अणु
	हाल IMS_PCU_RSP_EVNT_BUTTONS:
		अगर (likely(pcu->setup_complete))
			ims_pcu_report_events(pcu);
		अवरोध;

	शेष:
		/*
		 * See अगर we got command completion.
		 * If both the sequence and response code match save
		 * the data and संकेत completion.
		 */
		अगर (pcu->पढ़ो_buf[0] == pcu->expected_response &&
		    pcu->पढ़ो_buf[1] == pcu->ack_id - 1) अणु

			स_नकल(pcu->cmd_buf, pcu->पढ़ो_buf, pcu->पढ़ो_pos);
			pcu->cmd_buf_len = pcu->पढ़ो_pos;
			complete(&pcu->cmd_करोne);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ims_pcu_process_data(काष्ठा ims_pcu *pcu, काष्ठा urb *urb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < urb->actual_length; i++) अणु
		u8 data = pcu->urb_in_buf[i];

		/* Skip everything until we get Start Xmit */
		अगर (!pcu->have_stx && data != IMS_PCU_PROTOCOL_STX)
			जारी;

		अगर (pcu->have_dle) अणु
			pcu->have_dle = false;
			pcu->पढ़ो_buf[pcu->पढ़ो_pos++] = data;
			pcu->check_sum += data;
			जारी;
		पूर्ण

		चयन (data) अणु
		हाल IMS_PCU_PROTOCOL_STX:
			अगर (pcu->have_stx)
				dev_warn(pcu->dev,
					 "Unexpected STX at byte %d, discarding old data\n",
					 pcu->पढ़ो_pos);
			pcu->have_stx = true;
			pcu->have_dle = false;
			pcu->पढ़ो_pos = 0;
			pcu->check_sum = 0;
			अवरोध;

		हाल IMS_PCU_PROTOCOL_DLE:
			pcu->have_dle = true;
			अवरोध;

		हाल IMS_PCU_PROTOCOL_ETX:
			अगर (pcu->पढ़ो_pos < IMS_PCU_MIN_PACKET_LEN) अणु
				dev_warn(pcu->dev,
					 "Short packet received (%d bytes), ignoring\n",
					 pcu->पढ़ो_pos);
			पूर्ण अन्यथा अगर (pcu->check_sum != 0) अणु
				dev_warn(pcu->dev,
					 "Invalid checksum in packet (%d bytes), ignoring\n",
					 pcu->पढ़ो_pos);
			पूर्ण अन्यथा अणु
				ims_pcu_handle_response(pcu);
			पूर्ण

			pcu->have_stx = false;
			pcu->have_dle = false;
			pcu->पढ़ो_pos = 0;
			अवरोध;

		शेष:
			pcu->पढ़ो_buf[pcu->पढ़ो_pos++] = data;
			pcu->check_sum += data;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool ims_pcu_byte_needs_escape(u8 byte)
अणु
	वापस byte == IMS_PCU_PROTOCOL_STX ||
	       byte == IMS_PCU_PROTOCOL_ETX ||
	       byte == IMS_PCU_PROTOCOL_DLE;
पूर्ण

अटल पूर्णांक ims_pcu_send_cmd_chunk(काष्ठा ims_pcu *pcu,
				  u8 command, पूर्णांक chunk, पूर्णांक len)
अणु
	पूर्णांक error;

	error = usb_bulk_msg(pcu->udev,
			     usb_sndbulkpipe(pcu->udev,
					     pcu->ep_out->bEndpoपूर्णांकAddress),
			     pcu->urb_out_buf, len,
			     शून्य, IMS_PCU_CMD_WRITE_TIMEOUT);
	अगर (error < 0) अणु
		dev_dbg(pcu->dev,
			"Sending 0x%02x command failed at chunk %d: %d\n",
			command, chunk, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ims_pcu_send_command(काष्ठा ims_pcu *pcu,
				u8 command, स्थिर u8 *data, पूर्णांक len)
अणु
	पूर्णांक count = 0;
	पूर्णांक chunk = 0;
	पूर्णांक delta;
	पूर्णांक i;
	पूर्णांक error;
	u8 csum = 0;
	u8 ack_id;

	pcu->urb_out_buf[count++] = IMS_PCU_PROTOCOL_STX;

	/* We know the command need not be escaped */
	pcu->urb_out_buf[count++] = command;
	csum += command;

	ack_id = pcu->ack_id++;
	अगर (ack_id == 0xff)
		ack_id = pcu->ack_id++;

	अगर (ims_pcu_byte_needs_escape(ack_id))
		pcu->urb_out_buf[count++] = IMS_PCU_PROTOCOL_DLE;

	pcu->urb_out_buf[count++] = ack_id;
	csum += ack_id;

	क्रम (i = 0; i < len; i++) अणु

		delta = ims_pcu_byte_needs_escape(data[i]) ? 2 : 1;
		अगर (count + delta >= pcu->max_out_size) अणु
			error = ims_pcu_send_cmd_chunk(pcu, command,
						       ++chunk, count);
			अगर (error)
				वापस error;

			count = 0;
		पूर्ण

		अगर (delta == 2)
			pcu->urb_out_buf[count++] = IMS_PCU_PROTOCOL_DLE;

		pcu->urb_out_buf[count++] = data[i];
		csum += data[i];
	पूर्ण

	csum = 1 + ~csum;

	delta = ims_pcu_byte_needs_escape(csum) ? 3 : 2;
	अगर (count + delta >= pcu->max_out_size) अणु
		error = ims_pcu_send_cmd_chunk(pcu, command, ++chunk, count);
		अगर (error)
			वापस error;

		count = 0;
	पूर्ण

	अगर (delta == 3)
		pcu->urb_out_buf[count++] = IMS_PCU_PROTOCOL_DLE;

	pcu->urb_out_buf[count++] = csum;
	pcu->urb_out_buf[count++] = IMS_PCU_PROTOCOL_ETX;

	वापस ims_pcu_send_cmd_chunk(pcu, command, ++chunk, count);
पूर्ण

अटल पूर्णांक __ims_pcu_execute_command(काष्ठा ims_pcu *pcu,
				     u8 command, स्थिर व्योम *data, माप_प्रकार len,
				     u8 expected_response, पूर्णांक response_समय)
अणु
	पूर्णांक error;

	pcu->expected_response = expected_response;
	init_completion(&pcu->cmd_करोne);

	error = ims_pcu_send_command(pcu, command, data, len);
	अगर (error)
		वापस error;

	अगर (expected_response &&
	    !रुको_क्रम_completion_समयout(&pcu->cmd_करोne,
					 msecs_to_jअगरfies(response_समय))) अणु
		dev_dbg(pcu->dev, "Command 0x%02x timed out\n", command);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा ims_pcu_execute_command(pcu, code, data, len)			\
	__ims_pcu_execute_command(pcu,					\
				  IMS_PCU_CMD_##code, data, len,	\
				  IMS_PCU_RSP_##code,			\
				  IMS_PCU_CMD_RESPONSE_TIMEOUT)

#घोषणा ims_pcu_execute_query(pcu, code)				\
	ims_pcu_execute_command(pcu, code, शून्य, 0)

/* Bootloader commands */
#घोषणा IMS_PCU_BL_CMD_QUERY_DEVICE	0xa1
#घोषणा IMS_PCU_BL_CMD_UNLOCK_CONFIG	0xa2
#घोषणा IMS_PCU_BL_CMD_ERASE_APP	0xa3
#घोषणा IMS_PCU_BL_CMD_PROGRAM_DEVICE	0xa4
#घोषणा IMS_PCU_BL_CMD_PROGRAM_COMPLETE	0xa5
#घोषणा IMS_PCU_BL_CMD_READ_APP		0xa6
#घोषणा IMS_PCU_BL_CMD_RESET_DEVICE	0xa7
#घोषणा IMS_PCU_BL_CMD_LAUNCH_APP	0xa8

/* Bootloader commands */
#घोषणा IMS_PCU_BL_RSP_QUERY_DEVICE	0xc1
#घोषणा IMS_PCU_BL_RSP_UNLOCK_CONFIG	0xc2
#घोषणा IMS_PCU_BL_RSP_ERASE_APP	0xc3
#घोषणा IMS_PCU_BL_RSP_PROGRAM_DEVICE	0xc4
#घोषणा IMS_PCU_BL_RSP_PROGRAM_COMPLETE	0xc5
#घोषणा IMS_PCU_BL_RSP_READ_APP		0xc6
#घोषणा IMS_PCU_BL_RSP_RESET_DEVICE	0	/* originally 0xa7 */
#घोषणा IMS_PCU_BL_RSP_LAUNCH_APP	0	/* originally 0xa8 */

#घोषणा IMS_PCU_BL_DATA_OFFSET		3

अटल पूर्णांक __ims_pcu_execute_bl_command(काष्ठा ims_pcu *pcu,
				        u8 command, स्थिर व्योम *data, माप_प्रकार len,
				        u8 expected_response, पूर्णांक response_समय)
अणु
	पूर्णांक error;

	pcu->cmd_buf[0] = command;
	अगर (data)
		स_नकल(&pcu->cmd_buf[1], data, len);

	error = __ims_pcu_execute_command(pcu,
				IMS_PCU_CMD_BOOTLOADER, pcu->cmd_buf, len + 1,
				expected_response ? IMS_PCU_RSP_BOOTLOADER : 0,
				response_समय);
	अगर (error) अणु
		dev_err(pcu->dev,
			"Failure when sending 0x%02x command to bootloader, error: %d\n",
			pcu->cmd_buf[0], error);
		वापस error;
	पूर्ण

	अगर (expected_response && pcu->cmd_buf[2] != expected_response) अणु
		dev_err(pcu->dev,
			"Unexpected response from bootloader: 0x%02x, wanted 0x%02x\n",
			pcu->cmd_buf[2], expected_response);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा ims_pcu_execute_bl_command(pcu, code, data, len, समयout)	\
	__ims_pcu_execute_bl_command(pcu,				\
				     IMS_PCU_BL_CMD_##code, data, len,	\
				     IMS_PCU_BL_RSP_##code, समयout)	\

#घोषणा IMS_PCU_INFO_PART_OFFSET	2
#घोषणा IMS_PCU_INFO_DOM_OFFSET		17
#घोषणा IMS_PCU_INFO_SERIAL_OFFSET	25

#घोषणा IMS_PCU_SET_INFO_SIZE		31

अटल पूर्णांक ims_pcu_get_info(काष्ठा ims_pcu *pcu)
अणु
	पूर्णांक error;

	error = ims_pcu_execute_query(pcu, GET_INFO);
	अगर (error) अणु
		dev_err(pcu->dev,
			"GET_INFO command failed, error: %d\n", error);
		वापस error;
	पूर्ण

	स_नकल(pcu->part_number,
	       &pcu->cmd_buf[IMS_PCU_INFO_PART_OFFSET],
	       माप(pcu->part_number));
	स_नकल(pcu->date_of_manufacturing,
	       &pcu->cmd_buf[IMS_PCU_INFO_DOM_OFFSET],
	       माप(pcu->date_of_manufacturing));
	स_नकल(pcu->serial_number,
	       &pcu->cmd_buf[IMS_PCU_INFO_SERIAL_OFFSET],
	       माप(pcu->serial_number));

	वापस 0;
पूर्ण

अटल पूर्णांक ims_pcu_set_info(काष्ठा ims_pcu *pcu)
अणु
	पूर्णांक error;

	स_नकल(&pcu->cmd_buf[IMS_PCU_INFO_PART_OFFSET],
	       pcu->part_number, माप(pcu->part_number));
	स_नकल(&pcu->cmd_buf[IMS_PCU_INFO_DOM_OFFSET],
	       pcu->date_of_manufacturing, माप(pcu->date_of_manufacturing));
	स_नकल(&pcu->cmd_buf[IMS_PCU_INFO_SERIAL_OFFSET],
	       pcu->serial_number, माप(pcu->serial_number));

	error = ims_pcu_execute_command(pcu, SET_INFO,
					&pcu->cmd_buf[IMS_PCU_DATA_OFFSET],
					IMS_PCU_SET_INFO_SIZE);
	अगर (error) अणु
		dev_err(pcu->dev,
			"Failed to update device information, error: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ims_pcu_चयन_to_bootloader(काष्ठा ims_pcu *pcu)
अणु
	पूर्णांक error;

	/* Execute jump to the bootoloader */
	error = ims_pcu_execute_command(pcu, JUMP_TO_BTLDR, शून्य, 0);
	अगर (error) अणु
		dev_err(pcu->dev,
			"Failure when sending JUMP TO BOOLTLOADER command, error: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/*********************************************************************
 *             Firmware Update handling                              *
 *********************************************************************/

#घोषणा IMS_PCU_FIRMWARE_NAME	"imspcu.fw"

काष्ठा ims_pcu_flash_fmt अणु
	__le32 addr;
	u8 len;
	u8 data[];
पूर्ण;

अटल अचिन्हित पूर्णांक ims_pcu_count_fw_records(स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा ihex_binrec *rec = (स्थिर काष्ठा ihex_binrec *)fw->data;
	अचिन्हित पूर्णांक count = 0;

	जबतक (rec) अणु
		count++;
		rec = ihex_next_binrec(rec);
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक ims_pcu_verअगरy_block(काष्ठा ims_pcu *pcu,
				u32 addr, u8 len, स्थिर u8 *data)
अणु
	काष्ठा ims_pcu_flash_fmt *fragment;
	पूर्णांक error;

	fragment = (व्योम *)&pcu->cmd_buf[1];
	put_unaligned_le32(addr, &fragment->addr);
	fragment->len = len;

	error = ims_pcu_execute_bl_command(pcu, READ_APP, शून्य, 5,
					IMS_PCU_CMD_RESPONSE_TIMEOUT);
	अगर (error) अणु
		dev_err(pcu->dev,
			"Failed to retrieve block at 0x%08x, len %d, error: %d\n",
			addr, len, error);
		वापस error;
	पूर्ण

	fragment = (व्योम *)&pcu->cmd_buf[IMS_PCU_BL_DATA_OFFSET];
	अगर (get_unaligned_le32(&fragment->addr) != addr ||
	    fragment->len != len) अणु
		dev_err(pcu->dev,
			"Wrong block when retrieving 0x%08x (0x%08x), len %d (%d)\n",
			addr, get_unaligned_le32(&fragment->addr),
			len, fragment->len);
		वापस -EINVAL;
	पूर्ण

	अगर (स_भेद(fragment->data, data, len)) अणु
		dev_err(pcu->dev,
			"Mismatch in block at 0x%08x, len %d\n",
			addr, len);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ims_pcu_flash_firmware(काष्ठा ims_pcu *pcu,
				  स्थिर काष्ठा firmware *fw,
				  अचिन्हित पूर्णांक n_fw_records)
अणु
	स्थिर काष्ठा ihex_binrec *rec = (स्थिर काष्ठा ihex_binrec *)fw->data;
	काष्ठा ims_pcu_flash_fmt *fragment;
	अचिन्हित पूर्णांक count = 0;
	u32 addr;
	u8 len;
	पूर्णांक error;

	error = ims_pcu_execute_bl_command(pcu, ERASE_APP, शून्य, 0, 2000);
	अगर (error) अणु
		dev_err(pcu->dev,
			"Failed to erase application image, error: %d\n",
			error);
		वापस error;
	पूर्ण

	जबतक (rec) अणु
		/*
		 * The firmware क्रमmat is messed up क्रम some reason.
		 * The address twice that of what is needed क्रम some
		 * reason and we end up overwriting half of the data
		 * with the next record.
		 */
		addr = be32_to_cpu(rec->addr) / 2;
		len = be16_to_cpu(rec->len);

		fragment = (व्योम *)&pcu->cmd_buf[1];
		put_unaligned_le32(addr, &fragment->addr);
		fragment->len = len;
		स_नकल(fragment->data, rec->data, len);

		error = ims_pcu_execute_bl_command(pcu, PROGRAM_DEVICE,
						शून्य, len + 5,
						IMS_PCU_CMD_RESPONSE_TIMEOUT);
		अगर (error) अणु
			dev_err(pcu->dev,
				"Failed to write block at 0x%08x, len %d, error: %d\n",
				addr, len, error);
			वापस error;
		पूर्ण

		अगर (addr >= pcu->fw_start_addr && addr < pcu->fw_end_addr) अणु
			error = ims_pcu_verअगरy_block(pcu, addr, len, rec->data);
			अगर (error)
				वापस error;
		पूर्ण

		count++;
		pcu->update_firmware_status = (count * 100) / n_fw_records;

		rec = ihex_next_binrec(rec);
	पूर्ण

	error = ims_pcu_execute_bl_command(pcu, PROGRAM_COMPLETE,
					    शून्य, 0, 2000);
	अगर (error)
		dev_err(pcu->dev,
			"Failed to send PROGRAM_COMPLETE, error: %d\n",
			error);

	वापस 0;
पूर्ण

अटल पूर्णांक ims_pcu_handle_firmware_update(काष्ठा ims_pcu *pcu,
					  स्थिर काष्ठा firmware *fw)
अणु
	अचिन्हित पूर्णांक n_fw_records;
	पूर्णांक retval;

	dev_info(pcu->dev, "Updating firmware %s, size: %zu\n",
		 IMS_PCU_FIRMWARE_NAME, fw->size);

	n_fw_records = ims_pcu_count_fw_records(fw);

	retval = ims_pcu_flash_firmware(pcu, fw, n_fw_records);
	अगर (retval)
		जाओ out;

	retval = ims_pcu_execute_bl_command(pcu, LAUNCH_APP, शून्य, 0, 0);
	अगर (retval)
		dev_err(pcu->dev,
			"Failed to start application image, error: %d\n",
			retval);

out:
	pcu->update_firmware_status = retval;
	sysfs_notअगरy(&pcu->dev->kobj, शून्य, "update_firmware_status");
	वापस retval;
पूर्ण

अटल व्योम ims_pcu_process_async_firmware(स्थिर काष्ठा firmware *fw,
					   व्योम *context)
अणु
	काष्ठा ims_pcu *pcu = context;
	पूर्णांक error;

	अगर (!fw) अणु
		dev_err(pcu->dev, "Failed to get firmware %s\n",
			IMS_PCU_FIRMWARE_NAME);
		जाओ out;
	पूर्ण

	error = ihex_validate_fw(fw);
	अगर (error) अणु
		dev_err(pcu->dev, "Firmware %s is invalid\n",
			IMS_PCU_FIRMWARE_NAME);
		जाओ out;
	पूर्ण

	mutex_lock(&pcu->cmd_mutex);
	ims_pcu_handle_firmware_update(pcu, fw);
	mutex_unlock(&pcu->cmd_mutex);

	release_firmware(fw);

out:
	complete(&pcu->async_firmware_करोne);
पूर्ण

/*********************************************************************
 *             Backlight LED device support                          *
 *********************************************************************/

#घोषणा IMS_PCU_MAX_BRIGHTNESS		31998

अटल पूर्णांक ims_pcu_backlight_set_brightness(काष्ठा led_classdev *cdev,
					    क्रमागत led_brightness value)
अणु
	काष्ठा ims_pcu_backlight *backlight =
			container_of(cdev, काष्ठा ims_pcu_backlight, cdev);
	काष्ठा ims_pcu *pcu =
			container_of(backlight, काष्ठा ims_pcu, backlight);
	__le16 br_val = cpu_to_le16(value);
	पूर्णांक error;

	mutex_lock(&pcu->cmd_mutex);

	error = ims_pcu_execute_command(pcu, SET_BRIGHTNESS,
					&br_val, माप(br_val));
	अगर (error && error != -ENODEV)
		dev_warn(pcu->dev,
			 "Failed to set desired brightness %u, error: %d\n",
			 value, error);

	mutex_unlock(&pcu->cmd_mutex);

	वापस error;
पूर्ण

अटल क्रमागत led_brightness
ims_pcu_backlight_get_brightness(काष्ठा led_classdev *cdev)
अणु
	काष्ठा ims_pcu_backlight *backlight =
			container_of(cdev, काष्ठा ims_pcu_backlight, cdev);
	काष्ठा ims_pcu *pcu =
			container_of(backlight, काष्ठा ims_pcu, backlight);
	पूर्णांक brightness;
	पूर्णांक error;

	mutex_lock(&pcu->cmd_mutex);

	error = ims_pcu_execute_query(pcu, GET_BRIGHTNESS);
	अगर (error) अणु
		dev_warn(pcu->dev,
			 "Failed to get current brightness, error: %d\n",
			 error);
		/* Assume the LED is OFF */
		brightness = LED_OFF;
	पूर्ण अन्यथा अणु
		brightness =
			get_unaligned_le16(&pcu->cmd_buf[IMS_PCU_DATA_OFFSET]);
	पूर्ण

	mutex_unlock(&pcu->cmd_mutex);

	वापस brightness;
पूर्ण

अटल पूर्णांक ims_pcu_setup_backlight(काष्ठा ims_pcu *pcu)
अणु
	काष्ठा ims_pcu_backlight *backlight = &pcu->backlight;
	पूर्णांक error;

	snम_लिखो(backlight->name, माप(backlight->name),
		 "pcu%d::kbd_backlight", pcu->device_no);

	backlight->cdev.name = backlight->name;
	backlight->cdev.max_brightness = IMS_PCU_MAX_BRIGHTNESS;
	backlight->cdev.brightness_get = ims_pcu_backlight_get_brightness;
	backlight->cdev.brightness_set_blocking =
					 ims_pcu_backlight_set_brightness;

	error = led_classdev_रेजिस्टर(pcu->dev, &backlight->cdev);
	अगर (error) अणु
		dev_err(pcu->dev,
			"Failed to register backlight LED device, error: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ims_pcu_destroy_backlight(काष्ठा ims_pcu *pcu)
अणु
	काष्ठा ims_pcu_backlight *backlight = &pcu->backlight;

	led_classdev_unरेजिस्टर(&backlight->cdev);
पूर्ण


/*********************************************************************
 *             Sysfs attributes handling                             *
 *********************************************************************/

काष्ठा ims_pcu_attribute अणु
	काष्ठा device_attribute dattr;
	माप_प्रकार field_offset;
	पूर्णांक field_length;
पूर्ण;

अटल sमाप_प्रकार ims_pcu_attribute_show(काष्ठा device *dev,
				      काष्ठा device_attribute *dattr,
				      अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा ims_pcu_attribute *attr =
			container_of(dattr, काष्ठा ims_pcu_attribute, dattr);
	अक्षर *field = (अक्षर *)pcu + attr->field_offset;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%.*s\n", attr->field_length, field);
पूर्ण

अटल sमाप_प्रकार ims_pcu_attribute_store(काष्ठा device *dev,
				       काष्ठा device_attribute *dattr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु

	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा ims_pcu_attribute *attr =
			container_of(dattr, काष्ठा ims_pcu_attribute, dattr);
	अक्षर *field = (अक्षर *)pcu + attr->field_offset;
	माप_प्रकार data_len;
	पूर्णांक error;

	अगर (count > attr->field_length)
		वापस -EINVAL;

	data_len = strnlen(buf, attr->field_length);
	अगर (data_len > attr->field_length)
		वापस -EINVAL;

	error = mutex_lock_पूर्णांकerruptible(&pcu->cmd_mutex);
	अगर (error)
		वापस error;

	स_रखो(field, 0, attr->field_length);
	स_नकल(field, buf, data_len);

	error = ims_pcu_set_info(pcu);

	/*
	 * Even अगर update failed, let's fetch the info again as we just
	 * clobbered one of the fields.
	 */
	ims_pcu_get_info(pcu);

	mutex_unlock(&pcu->cmd_mutex);

	वापस error < 0 ? error : count;
पूर्ण

#घोषणा IMS_PCU_ATTR(_field, _mode)					\
काष्ठा ims_pcu_attribute ims_pcu_attr_##_field = अणु			\
	.dattr = __ATTR(_field, _mode,					\
			ims_pcu_attribute_show,				\
			ims_pcu_attribute_store),			\
	.field_offset = दुरत्व(काष्ठा ims_pcu, _field),		\
	.field_length = माप(((काष्ठा ims_pcu *)शून्य)->_field),	\
पूर्ण

#घोषणा IMS_PCU_RO_ATTR(_field)						\
		IMS_PCU_ATTR(_field, S_IRUGO)
#घोषणा IMS_PCU_RW_ATTR(_field)						\
		IMS_PCU_ATTR(_field, S_IRUGO | S_IWUSR)

अटल IMS_PCU_RW_ATTR(part_number);
अटल IMS_PCU_RW_ATTR(serial_number);
अटल IMS_PCU_RW_ATTR(date_of_manufacturing);

अटल IMS_PCU_RO_ATTR(fw_version);
अटल IMS_PCU_RO_ATTR(bl_version);
अटल IMS_PCU_RO_ATTR(reset_reason);

अटल sमाप_प्रकार ims_pcu_reset_device(काष्ठा device *dev,
				    काष्ठा device_attribute *dattr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अटल स्थिर u8 reset_byte = 1;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक value;
	पूर्णांक error;

	error = kstrtoपूर्णांक(buf, 0, &value);
	अगर (error)
		वापस error;

	अगर (value != 1)
		वापस -EINVAL;

	dev_info(pcu->dev, "Attempting to reset device\n");

	error = ims_pcu_execute_command(pcu, PCU_RESET, &reset_byte, 1);
	अगर (error) अणु
		dev_info(pcu->dev,
			 "Failed to reset device, error: %d\n",
			 error);
		वापस error;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(reset_device, S_IWUSR, शून्य, ims_pcu_reset_device);

अटल sमाप_प्रकार ims_pcu_update_firmware_store(काष्ठा device *dev,
					     काष्ठा device_attribute *dattr,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक value;
	पूर्णांक error;

	error = kstrtoपूर्णांक(buf, 0, &value);
	अगर (error)
		वापस error;

	अगर (value != 1)
		वापस -EINVAL;

	error = mutex_lock_पूर्णांकerruptible(&pcu->cmd_mutex);
	अगर (error)
		वापस error;

	error = request_ihex_firmware(&fw, IMS_PCU_FIRMWARE_NAME, pcu->dev);
	अगर (error) अणु
		dev_err(pcu->dev, "Failed to request firmware %s, error: %d\n",
			IMS_PCU_FIRMWARE_NAME, error);
		जाओ out;
	पूर्ण

	/*
	 * If we are alपढ़ोy in bootloader mode we can proceed with
	 * flashing the firmware.
	 *
	 * If we are in application mode, then we need to चयन पूर्णांकo
	 * bootloader mode, which will cause the device to disconnect
	 * and reconnect as dअगरferent device.
	 */
	अगर (pcu->bootloader_mode)
		error = ims_pcu_handle_firmware_update(pcu, fw);
	अन्यथा
		error = ims_pcu_चयन_to_bootloader(pcu);

	release_firmware(fw);

out:
	mutex_unlock(&pcu->cmd_mutex);
	वापस error ?: count;
पूर्ण

अटल DEVICE_ATTR(update_firmware, S_IWUSR,
		   शून्य, ims_pcu_update_firmware_store);

अटल sमाप_प्रकार
ims_pcu_update_firmware_status_show(काष्ठा device *dev,
				    काष्ठा device_attribute *dattr,
				    अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", pcu->update_firmware_status);
पूर्ण

अटल DEVICE_ATTR(update_firmware_status, S_IRUGO,
		   ims_pcu_update_firmware_status_show, शून्य);

अटल काष्ठा attribute *ims_pcu_attrs[] = अणु
	&ims_pcu_attr_part_number.dattr.attr,
	&ims_pcu_attr_serial_number.dattr.attr,
	&ims_pcu_attr_date_of_manufacturing.dattr.attr,
	&ims_pcu_attr_fw_version.dattr.attr,
	&ims_pcu_attr_bl_version.dattr.attr,
	&ims_pcu_attr_reset_reason.dattr.attr,
	&dev_attr_reset_device.attr,
	&dev_attr_update_firmware.attr,
	&dev_attr_update_firmware_status.attr,
	शून्य
पूर्ण;

अटल umode_t ims_pcu_is_attr_visible(काष्ठा kobject *kobj,
				       काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	umode_t mode = attr->mode;

	अगर (pcu->bootloader_mode) अणु
		अगर (attr != &dev_attr_update_firmware_status.attr &&
		    attr != &dev_attr_update_firmware.attr &&
		    attr != &dev_attr_reset_device.attr) अणु
			mode = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (attr == &dev_attr_update_firmware_status.attr)
			mode = 0;
	पूर्ण

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group ims_pcu_attr_group = अणु
	.is_visible	= ims_pcu_is_attr_visible,
	.attrs		= ims_pcu_attrs,
पूर्ण;

/* Support क्रम a separate OFN attribute group */

#घोषणा OFN_REG_RESULT_OFFSET	2

अटल पूर्णांक ims_pcu_पढ़ो_ofn_config(काष्ठा ims_pcu *pcu, u8 addr, u8 *data)
अणु
	पूर्णांक error;
	s16 result;

	error = ims_pcu_execute_command(pcu, OFN_GET_CONFIG,
					&addr, माप(addr));
	अगर (error)
		वापस error;

	result = (s16)get_unaligned_le16(pcu->cmd_buf + OFN_REG_RESULT_OFFSET);
	अगर (result < 0)
		वापस -EIO;

	/* We only need LSB */
	*data = pcu->cmd_buf[OFN_REG_RESULT_OFFSET];
	वापस 0;
पूर्ण

अटल पूर्णांक ims_pcu_ग_लिखो_ofn_config(काष्ठा ims_pcu *pcu, u8 addr, u8 data)
अणु
	u8 buffer[] = अणु addr, data पूर्ण;
	पूर्णांक error;
	s16 result;

	error = ims_pcu_execute_command(pcu, OFN_SET_CONFIG,
					&buffer, माप(buffer));
	अगर (error)
		वापस error;

	result = (s16)get_unaligned_le16(pcu->cmd_buf + OFN_REG_RESULT_OFFSET);
	अगर (result < 0)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ims_pcu_ofn_reg_data_show(काष्ठा device *dev,
					 काष्ठा device_attribute *dattr,
					 अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक error;
	u8 data;

	mutex_lock(&pcu->cmd_mutex);
	error = ims_pcu_पढ़ो_ofn_config(pcu, pcu->ofn_reg_addr, &data);
	mutex_unlock(&pcu->cmd_mutex);

	अगर (error)
		वापस error;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%x\n", data);
पूर्ण

अटल sमाप_प्रकार ims_pcu_ofn_reg_data_store(काष्ठा device *dev,
					  काष्ठा device_attribute *dattr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक error;
	u8 value;

	error = kstrtou8(buf, 0, &value);
	अगर (error)
		वापस error;

	mutex_lock(&pcu->cmd_mutex);
	error = ims_pcu_ग_लिखो_ofn_config(pcu, pcu->ofn_reg_addr, value);
	mutex_unlock(&pcu->cmd_mutex);

	वापस error ?: count;
पूर्ण

अटल DEVICE_ATTR(reg_data, S_IRUGO | S_IWUSR,
		   ims_pcu_ofn_reg_data_show, ims_pcu_ofn_reg_data_store);

अटल sमाप_प्रकार ims_pcu_ofn_reg_addr_show(काष्ठा device *dev,
					 काष्ठा device_attribute *dattr,
					 अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक error;

	mutex_lock(&pcu->cmd_mutex);
	error = scnम_लिखो(buf, PAGE_SIZE, "%x\n", pcu->ofn_reg_addr);
	mutex_unlock(&pcu->cmd_mutex);

	वापस error;
पूर्ण

अटल sमाप_प्रकार ims_pcu_ofn_reg_addr_store(काष्ठा device *dev,
					  काष्ठा device_attribute *dattr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक error;
	u8 value;

	error = kstrtou8(buf, 0, &value);
	अगर (error)
		वापस error;

	mutex_lock(&pcu->cmd_mutex);
	pcu->ofn_reg_addr = value;
	mutex_unlock(&pcu->cmd_mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(reg_addr, S_IRUGO | S_IWUSR,
		   ims_pcu_ofn_reg_addr_show, ims_pcu_ofn_reg_addr_store);

काष्ठा ims_pcu_ofn_bit_attribute अणु
	काष्ठा device_attribute dattr;
	u8 addr;
	u8 nr;
पूर्ण;

अटल sमाप_प्रकार ims_pcu_ofn_bit_show(काष्ठा device *dev,
				    काष्ठा device_attribute *dattr,
				    अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा ims_pcu_ofn_bit_attribute *attr =
		container_of(dattr, काष्ठा ims_pcu_ofn_bit_attribute, dattr);
	पूर्णांक error;
	u8 data;

	mutex_lock(&pcu->cmd_mutex);
	error = ims_pcu_पढ़ो_ofn_config(pcu, attr->addr, &data);
	mutex_unlock(&pcu->cmd_mutex);

	अगर (error)
		वापस error;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", !!(data & (1 << attr->nr)));
पूर्ण

अटल sमाप_प्रकार ims_pcu_ofn_bit_store(काष्ठा device *dev,
				     काष्ठा device_attribute *dattr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा ims_pcu_ofn_bit_attribute *attr =
		container_of(dattr, काष्ठा ims_pcu_ofn_bit_attribute, dattr);
	पूर्णांक error;
	पूर्णांक value;
	u8 data;

	error = kstrtoपूर्णांक(buf, 0, &value);
	अगर (error)
		वापस error;

	अगर (value > 1)
		वापस -EINVAL;

	mutex_lock(&pcu->cmd_mutex);

	error = ims_pcu_पढ़ो_ofn_config(pcu, attr->addr, &data);
	अगर (!error) अणु
		अगर (value)
			data |= 1U << attr->nr;
		अन्यथा
			data &= ~(1U << attr->nr);

		error = ims_pcu_ग_लिखो_ofn_config(pcu, attr->addr, data);
	पूर्ण

	mutex_unlock(&pcu->cmd_mutex);

	वापस error ?: count;
पूर्ण

#घोषणा IMS_PCU_OFN_BIT_ATTR(_field, _addr, _nr)			\
काष्ठा ims_pcu_ofn_bit_attribute ims_pcu_ofn_attr_##_field = अणु		\
	.dattr = __ATTR(_field, S_IWUSR | S_IRUGO,			\
			ims_pcu_ofn_bit_show, ims_pcu_ofn_bit_store),	\
	.addr = _addr,							\
	.nr = _nr,							\
पूर्ण

अटल IMS_PCU_OFN_BIT_ATTR(engine_enable,   0x60, 7);
अटल IMS_PCU_OFN_BIT_ATTR(speed_enable,    0x60, 6);
अटल IMS_PCU_OFN_BIT_ATTR(निश्चित_enable,   0x60, 5);
अटल IMS_PCU_OFN_BIT_ATTR(xyquant_enable,  0x60, 4);
अटल IMS_PCU_OFN_BIT_ATTR(xyscale_enable,  0x60, 1);

अटल IMS_PCU_OFN_BIT_ATTR(scale_x2,        0x63, 6);
अटल IMS_PCU_OFN_BIT_ATTR(scale_y2,        0x63, 7);

अटल काष्ठा attribute *ims_pcu_ofn_attrs[] = अणु
	&dev_attr_reg_data.attr,
	&dev_attr_reg_addr.attr,
	&ims_pcu_ofn_attr_engine_enable.dattr.attr,
	&ims_pcu_ofn_attr_speed_enable.dattr.attr,
	&ims_pcu_ofn_attr_निश्चित_enable.dattr.attr,
	&ims_pcu_ofn_attr_xyquant_enable.dattr.attr,
	&ims_pcu_ofn_attr_xyscale_enable.dattr.attr,
	&ims_pcu_ofn_attr_scale_x2.dattr.attr,
	&ims_pcu_ofn_attr_scale_y2.dattr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ims_pcu_ofn_attr_group = अणु
	.name	= "ofn",
	.attrs	= ims_pcu_ofn_attrs,
पूर्ण;

अटल व्योम ims_pcu_irq(काष्ठा urb *urb)
अणु
	काष्ठा ims_pcu *pcu = urb->context;
	पूर्णांक retval, status;

	status = urb->status;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(pcu->dev, "%s - urb shutting down with status: %d\n",
			__func__, status);
		वापस;
	शेष:
		dev_dbg(pcu->dev, "%s - nonzero urb status received: %d\n",
			__func__, status);
		जाओ निकास;
	पूर्ण

	dev_dbg(pcu->dev, "%s: received %d: %*ph\n", __func__,
		urb->actual_length, urb->actual_length, pcu->urb_in_buf);

	अगर (urb == pcu->urb_in)
		ims_pcu_process_data(pcu, urb);

निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval && retval != -ENODEV)
		dev_err(pcu->dev, "%s - usb_submit_urb failed with result %d\n",
			__func__, retval);
पूर्ण

अटल पूर्णांक ims_pcu_buffers_alloc(काष्ठा ims_pcu *pcu)
अणु
	पूर्णांक error;

	pcu->urb_in_buf = usb_alloc_coherent(pcu->udev, pcu->max_in_size,
					     GFP_KERNEL, &pcu->पढ़ो_dma);
	अगर (!pcu->urb_in_buf) अणु
		dev_err(pcu->dev,
			"Failed to allocate memory for read buffer\n");
		वापस -ENOMEM;
	पूर्ण

	pcu->urb_in = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!pcu->urb_in) अणु
		dev_err(pcu->dev, "Failed to allocate input URB\n");
		error = -ENOMEM;
		जाओ err_मुक्त_urb_in_buf;
	पूर्ण

	pcu->urb_in->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	pcu->urb_in->transfer_dma = pcu->पढ़ो_dma;

	usb_fill_bulk_urb(pcu->urb_in, pcu->udev,
			  usb_rcvbulkpipe(pcu->udev,
					  pcu->ep_in->bEndpoपूर्णांकAddress),
			  pcu->urb_in_buf, pcu->max_in_size,
			  ims_pcu_irq, pcu);

	/*
	 * We are using usb_bulk_msg() क्रम sending so there is no poपूर्णांक
	 * in allocating memory with usb_alloc_coherent().
	 */
	pcu->urb_out_buf = kदो_स्मृति(pcu->max_out_size, GFP_KERNEL);
	अगर (!pcu->urb_out_buf) अणु
		dev_err(pcu->dev, "Failed to allocate memory for write buffer\n");
		error = -ENOMEM;
		जाओ err_मुक्त_in_urb;
	पूर्ण

	pcu->urb_ctrl_buf = usb_alloc_coherent(pcu->udev, pcu->max_ctrl_size,
					       GFP_KERNEL, &pcu->ctrl_dma);
	अगर (!pcu->urb_ctrl_buf) अणु
		dev_err(pcu->dev,
			"Failed to allocate memory for read buffer\n");
		error = -ENOMEM;
		जाओ err_मुक्त_urb_out_buf;
	पूर्ण

	pcu->urb_ctrl = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!pcu->urb_ctrl) अणु
		dev_err(pcu->dev, "Failed to allocate input URB\n");
		error = -ENOMEM;
		जाओ err_मुक्त_urb_ctrl_buf;
	पूर्ण

	pcu->urb_ctrl->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	pcu->urb_ctrl->transfer_dma = pcu->ctrl_dma;

	usb_fill_पूर्णांक_urb(pcu->urb_ctrl, pcu->udev,
			  usb_rcvपूर्णांकpipe(pcu->udev,
					 pcu->ep_ctrl->bEndpoपूर्णांकAddress),
			  pcu->urb_ctrl_buf, pcu->max_ctrl_size,
			  ims_pcu_irq, pcu, pcu->ep_ctrl->bInterval);

	वापस 0;

err_मुक्त_urb_ctrl_buf:
	usb_मुक्त_coherent(pcu->udev, pcu->max_ctrl_size,
			  pcu->urb_ctrl_buf, pcu->ctrl_dma);
err_मुक्त_urb_out_buf:
	kमुक्त(pcu->urb_out_buf);
err_मुक्त_in_urb:
	usb_मुक्त_urb(pcu->urb_in);
err_मुक्त_urb_in_buf:
	usb_मुक्त_coherent(pcu->udev, pcu->max_in_size,
			  pcu->urb_in_buf, pcu->पढ़ो_dma);
	वापस error;
पूर्ण

अटल व्योम ims_pcu_buffers_मुक्त(काष्ठा ims_pcu *pcu)
अणु
	usb_समाप्त_urb(pcu->urb_in);
	usb_मुक्त_urb(pcu->urb_in);

	usb_मुक्त_coherent(pcu->udev, pcu->max_out_size,
			  pcu->urb_in_buf, pcu->पढ़ो_dma);

	kमुक्त(pcu->urb_out_buf);

	usb_समाप्त_urb(pcu->urb_ctrl);
	usb_मुक्त_urb(pcu->urb_ctrl);

	usb_मुक्त_coherent(pcu->udev, pcu->max_ctrl_size,
			  pcu->urb_ctrl_buf, pcu->ctrl_dma);
पूर्ण

अटल स्थिर काष्ठा usb_cdc_जोड़_desc *
ims_pcu_get_cdc_जोड़_desc(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	स्थिर व्योम *buf = पूर्णांकf->altsetting->extra;
	माप_प्रकार buflen = पूर्णांकf->altsetting->extralen;
	काष्ठा usb_cdc_जोड़_desc *जोड़_desc;

	अगर (!buf) अणु
		dev_err(&पूर्णांकf->dev, "Missing descriptor data\n");
		वापस शून्य;
	पूर्ण

	अगर (!buflen) अणु
		dev_err(&पूर्णांकf->dev, "Zero length descriptor\n");
		वापस शून्य;
	पूर्ण

	जबतक (buflen >= माप(*जोड़_desc)) अणु
		जोड़_desc = (काष्ठा usb_cdc_जोड़_desc *)buf;

		अगर (जोड़_desc->bLength > buflen) अणु
			dev_err(&पूर्णांकf->dev, "Too large descriptor\n");
			वापस शून्य;
		पूर्ण

		अगर (जोड़_desc->bDescriptorType == USB_DT_CS_INTERFACE &&
		    जोड़_desc->bDescriptorSubType == USB_CDC_UNION_TYPE) अणु
			dev_dbg(&पूर्णांकf->dev, "Found union header\n");

			अगर (जोड़_desc->bLength >= माप(*जोड़_desc))
				वापस जोड़_desc;

			dev_err(&पूर्णांकf->dev,
				"Union descriptor too short (%d vs %zd)\n",
				जोड़_desc->bLength, माप(*जोड़_desc));
			वापस शून्य;
		पूर्ण

		buflen -= जोड़_desc->bLength;
		buf += जोड़_desc->bLength;
	पूर्ण

	dev_err(&पूर्णांकf->dev, "Missing CDC union descriptor\n");
	वापस शून्य;
पूर्ण

अटल पूर्णांक ims_pcu_parse_cdc_data(काष्ठा usb_पूर्णांकerface *पूर्णांकf, काष्ठा ims_pcu *pcu)
अणु
	स्थिर काष्ठा usb_cdc_जोड़_desc *जोड़_desc;
	काष्ठा usb_host_पूर्णांकerface *alt;

	जोड़_desc = ims_pcu_get_cdc_जोड़_desc(पूर्णांकf);
	अगर (!जोड़_desc)
		वापस -EINVAL;

	pcu->ctrl_पूर्णांकf = usb_अगरnum_to_अगर(pcu->udev,
					 जोड़_desc->bMasterInterface0);
	अगर (!pcu->ctrl_पूर्णांकf)
		वापस -EINVAL;

	alt = pcu->ctrl_पूर्णांकf->cur_altsetting;

	अगर (alt->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	pcu->ep_ctrl = &alt->endpoपूर्णांक[0].desc;
	pcu->max_ctrl_size = usb_endpoपूर्णांक_maxp(pcu->ep_ctrl);

	pcu->data_पूर्णांकf = usb_अगरnum_to_अगर(pcu->udev,
					 जोड़_desc->bSlaveInterface0);
	अगर (!pcu->data_पूर्णांकf)
		वापस -EINVAL;

	alt = pcu->data_पूर्णांकf->cur_altsetting;
	अगर (alt->desc.bNumEndpoपूर्णांकs != 2) अणु
		dev_err(pcu->dev,
			"Incorrect number of endpoints on data interface (%d)\n",
			alt->desc.bNumEndpoपूर्णांकs);
		वापस -EINVAL;
	पूर्ण

	pcu->ep_out = &alt->endpoपूर्णांक[0].desc;
	अगर (!usb_endpoपूर्णांक_is_bulk_out(pcu->ep_out)) अणु
		dev_err(pcu->dev,
			"First endpoint on data interface is not BULK OUT\n");
		वापस -EINVAL;
	पूर्ण

	pcu->max_out_size = usb_endpoपूर्णांक_maxp(pcu->ep_out);
	अगर (pcu->max_out_size < 8) अणु
		dev_err(pcu->dev,
			"Max OUT packet size is too small (%zd)\n",
			pcu->max_out_size);
		वापस -EINVAL;
	पूर्ण

	pcu->ep_in = &alt->endpoपूर्णांक[1].desc;
	अगर (!usb_endpoपूर्णांक_is_bulk_in(pcu->ep_in)) अणु
		dev_err(pcu->dev,
			"Second endpoint on data interface is not BULK IN\n");
		वापस -EINVAL;
	पूर्ण

	pcu->max_in_size = usb_endpoपूर्णांक_maxp(pcu->ep_in);
	अगर (pcu->max_in_size < 8) अणु
		dev_err(pcu->dev,
			"Max IN packet size is too small (%zd)\n",
			pcu->max_in_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ims_pcu_start_io(काष्ठा ims_pcu *pcu)
अणु
	पूर्णांक error;

	error = usb_submit_urb(pcu->urb_ctrl, GFP_KERNEL);
	अगर (error) अणु
		dev_err(pcu->dev,
			"Failed to start control IO - usb_submit_urb failed with result: %d\n",
			error);
		वापस -EIO;
	पूर्ण

	error = usb_submit_urb(pcu->urb_in, GFP_KERNEL);
	अगर (error) अणु
		dev_err(pcu->dev,
			"Failed to start IO - usb_submit_urb failed with result: %d\n",
			error);
		usb_समाप्त_urb(pcu->urb_ctrl);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ims_pcu_stop_io(काष्ठा ims_pcu *pcu)
अणु
	usb_समाप्त_urb(pcu->urb_in);
	usb_समाप्त_urb(pcu->urb_ctrl);
पूर्ण

अटल पूर्णांक ims_pcu_line_setup(काष्ठा ims_pcu *pcu)
अणु
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface = pcu->ctrl_पूर्णांकf->cur_altsetting;
	काष्ठा usb_cdc_line_coding *line = (व्योम *)pcu->cmd_buf;
	पूर्णांक error;

	स_रखो(line, 0, माप(*line));
	line->dwDTERate = cpu_to_le32(57600);
	line->bDataBits = 8;

	error = usb_control_msg(pcu->udev, usb_sndctrlpipe(pcu->udev, 0),
				USB_CDC_REQ_SET_LINE_CODING,
				USB_TYPE_CLASS | USB_RECIP_INTERFACE,
				0, पूर्णांकerface->desc.bInterfaceNumber,
				line, माप(काष्ठा usb_cdc_line_coding),
				5000);
	अगर (error < 0) अणु
		dev_err(pcu->dev, "Failed to set line coding, error: %d\n",
			error);
		वापस error;
	पूर्ण

	error = usb_control_msg(pcu->udev, usb_sndctrlpipe(pcu->udev, 0),
				USB_CDC_REQ_SET_CONTROL_LINE_STATE,
				USB_TYPE_CLASS | USB_RECIP_INTERFACE,
				0x03, पूर्णांकerface->desc.bInterfaceNumber,
				शून्य, 0, 5000);
	अगर (error < 0) अणु
		dev_err(pcu->dev, "Failed to set line state, error: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ims_pcu_get_device_info(काष्ठा ims_pcu *pcu)
अणु
	पूर्णांक error;

	error = ims_pcu_get_info(pcu);
	अगर (error)
		वापस error;

	error = ims_pcu_execute_query(pcu, GET_FW_VERSION);
	अगर (error) अणु
		dev_err(pcu->dev,
			"GET_FW_VERSION command failed, error: %d\n", error);
		वापस error;
	पूर्ण

	snम_लिखो(pcu->fw_version, माप(pcu->fw_version),
		 "%02d%02d%02d%02d.%c%c",
		 pcu->cmd_buf[2], pcu->cmd_buf[3], pcu->cmd_buf[4], pcu->cmd_buf[5],
		 pcu->cmd_buf[6], pcu->cmd_buf[7]);

	error = ims_pcu_execute_query(pcu, GET_BL_VERSION);
	अगर (error) अणु
		dev_err(pcu->dev,
			"GET_BL_VERSION command failed, error: %d\n", error);
		वापस error;
	पूर्ण

	snम_लिखो(pcu->bl_version, माप(pcu->bl_version),
		 "%02d%02d%02d%02d.%c%c",
		 pcu->cmd_buf[2], pcu->cmd_buf[3], pcu->cmd_buf[4], pcu->cmd_buf[5],
		 pcu->cmd_buf[6], pcu->cmd_buf[7]);

	error = ims_pcu_execute_query(pcu, RESET_REASON);
	अगर (error) अणु
		dev_err(pcu->dev,
			"RESET_REASON command failed, error: %d\n", error);
		वापस error;
	पूर्ण

	snम_लिखो(pcu->reset_reason, माप(pcu->reset_reason),
		 "%02x", pcu->cmd_buf[IMS_PCU_DATA_OFFSET]);

	dev_dbg(pcu->dev,
		"P/N: %s, MD: %s, S/N: %s, FW: %s, BL: %s, RR: %s\n",
		pcu->part_number,
		pcu->date_of_manufacturing,
		pcu->serial_number,
		pcu->fw_version,
		pcu->bl_version,
		pcu->reset_reason);

	वापस 0;
पूर्ण

अटल पूर्णांक ims_pcu_identअगरy_type(काष्ठा ims_pcu *pcu, u8 *device_id)
अणु
	पूर्णांक error;

	error = ims_pcu_execute_query(pcu, GET_DEVICE_ID);
	अगर (error) अणु
		dev_err(pcu->dev,
			"GET_DEVICE_ID command failed, error: %d\n", error);
		वापस error;
	पूर्ण

	*device_id = pcu->cmd_buf[IMS_PCU_DATA_OFFSET];
	dev_dbg(pcu->dev, "Detected device ID: %d\n", *device_id);

	वापस 0;
पूर्ण

अटल पूर्णांक ims_pcu_init_application_mode(काष्ठा ims_pcu *pcu)
अणु
	अटल atomic_t device_no = ATOMIC_INIT(-1);

	स्थिर काष्ठा ims_pcu_device_info *info;
	पूर्णांक error;

	error = ims_pcu_get_device_info(pcu);
	अगर (error) अणु
		/* Device करोes not respond to basic queries, hopeless */
		वापस error;
	पूर्ण

	error = ims_pcu_identअगरy_type(pcu, &pcu->device_id);
	अगर (error) अणु
		dev_err(pcu->dev,
			"Failed to identify device, error: %d\n", error);
		/*
		 * Do not संकेत error, but करो not create input nor
		 * backlight devices either, let userspace figure this
		 * out (flash a new firmware?).
		 */
		वापस 0;
	पूर्ण

	अगर (pcu->device_id >= ARRAY_SIZE(ims_pcu_device_info) ||
	    !ims_pcu_device_info[pcu->device_id].keymap) अणु
		dev_err(pcu->dev, "Device ID %d is not valid\n", pcu->device_id);
		/* Same as above, punt to userspace */
		वापस 0;
	पूर्ण

	/* Device appears to be operable, complete initialization */
	pcu->device_no = atomic_inc_वापस(&device_no);

	/*
	 * PCU-B devices, both GEN_1 and GEN_2 करो not have OFN sensor
	 */
	अगर (pcu->device_id != IMS_PCU_PCU_B_DEVICE_ID) अणु
		error = sysfs_create_group(&pcu->dev->kobj,
					   &ims_pcu_ofn_attr_group);
		अगर (error)
			वापस error;
	पूर्ण

	error = ims_pcu_setup_backlight(pcu);
	अगर (error)
		वापस error;

	info = &ims_pcu_device_info[pcu->device_id];
	error = ims_pcu_setup_buttons(pcu, info->keymap, info->keymap_len);
	अगर (error)
		जाओ err_destroy_backlight;

	अगर (info->has_gamepad) अणु
		error = ims_pcu_setup_gamepad(pcu);
		अगर (error)
			जाओ err_destroy_buttons;
	पूर्ण

	pcu->setup_complete = true;

	वापस 0;

err_destroy_buttons:
	ims_pcu_destroy_buttons(pcu);
err_destroy_backlight:
	ims_pcu_destroy_backlight(pcu);
	वापस error;
पूर्ण

अटल व्योम ims_pcu_destroy_application_mode(काष्ठा ims_pcu *pcu)
अणु
	अगर (pcu->setup_complete) अणु
		pcu->setup_complete = false;
		mb(); /* make sure flag setting is not reordered */

		अगर (pcu->gamepad)
			ims_pcu_destroy_gamepad(pcu);
		ims_pcu_destroy_buttons(pcu);
		ims_pcu_destroy_backlight(pcu);

		अगर (pcu->device_id != IMS_PCU_PCU_B_DEVICE_ID)
			sysfs_हटाओ_group(&pcu->dev->kobj,
					   &ims_pcu_ofn_attr_group);
	पूर्ण
पूर्ण

अटल पूर्णांक ims_pcu_init_bootloader_mode(काष्ठा ims_pcu *pcu)
अणु
	पूर्णांक error;

	error = ims_pcu_execute_bl_command(pcu, QUERY_DEVICE, शून्य, 0,
					   IMS_PCU_CMD_RESPONSE_TIMEOUT);
	अगर (error) अणु
		dev_err(pcu->dev, "Bootloader does not respond, aborting\n");
		वापस error;
	पूर्ण

	pcu->fw_start_addr =
		get_unaligned_le32(&pcu->cmd_buf[IMS_PCU_DATA_OFFSET + 11]);
	pcu->fw_end_addr =
		get_unaligned_le32(&pcu->cmd_buf[IMS_PCU_DATA_OFFSET + 15]);

	dev_info(pcu->dev,
		 "Device is in bootloader mode (addr 0x%08x-0x%08x), requesting firmware\n",
		 pcu->fw_start_addr, pcu->fw_end_addr);

	error = request_firmware_noरुको(THIS_MODULE, true,
					IMS_PCU_FIRMWARE_NAME,
					pcu->dev, GFP_KERNEL, pcu,
					ims_pcu_process_async_firmware);
	अगर (error) अणु
		/* This error is not fatal, let userspace have another chance */
		complete(&pcu->async_firmware_करोne);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ims_pcu_destroy_bootloader_mode(काष्ठा ims_pcu *pcu)
अणु
	/* Make sure our initial firmware request has completed */
	रुको_क्रम_completion(&pcu->async_firmware_करोne);
पूर्ण

#घोषणा IMS_PCU_APPLICATION_MODE	0
#घोषणा IMS_PCU_BOOTLOADER_MODE		1

अटल काष्ठा usb_driver ims_pcu_driver;

अटल पूर्णांक ims_pcu_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा ims_pcu *pcu;
	पूर्णांक error;

	pcu = kzalloc(माप(काष्ठा ims_pcu), GFP_KERNEL);
	अगर (!pcu)
		वापस -ENOMEM;

	pcu->dev = &पूर्णांकf->dev;
	pcu->udev = udev;
	pcu->bootloader_mode = id->driver_info == IMS_PCU_BOOTLOADER_MODE;
	mutex_init(&pcu->cmd_mutex);
	init_completion(&pcu->cmd_करोne);
	init_completion(&pcu->async_firmware_करोne);

	error = ims_pcu_parse_cdc_data(पूर्णांकf, pcu);
	अगर (error)
		जाओ err_मुक्त_mem;

	error = usb_driver_claim_पूर्णांकerface(&ims_pcu_driver,
					   pcu->data_पूर्णांकf, pcu);
	अगर (error) अणु
		dev_err(&पूर्णांकf->dev,
			"Unable to claim corresponding data interface: %d\n",
			error);
		जाओ err_मुक्त_mem;
	पूर्ण

	usb_set_पूर्णांकfdata(pcu->ctrl_पूर्णांकf, pcu);

	error = ims_pcu_buffers_alloc(pcu);
	अगर (error)
		जाओ err_unclaim_पूर्णांकf;

	error = ims_pcu_start_io(pcu);
	अगर (error)
		जाओ err_मुक्त_buffers;

	error = ims_pcu_line_setup(pcu);
	अगर (error)
		जाओ err_stop_io;

	error = sysfs_create_group(&पूर्णांकf->dev.kobj, &ims_pcu_attr_group);
	अगर (error)
		जाओ err_stop_io;

	error = pcu->bootloader_mode ?
			ims_pcu_init_bootloader_mode(pcu) :
			ims_pcu_init_application_mode(pcu);
	अगर (error)
		जाओ err_हटाओ_sysfs;

	वापस 0;

err_हटाओ_sysfs:
	sysfs_हटाओ_group(&पूर्णांकf->dev.kobj, &ims_pcu_attr_group);
err_stop_io:
	ims_pcu_stop_io(pcu);
err_मुक्त_buffers:
	ims_pcu_buffers_मुक्त(pcu);
err_unclaim_पूर्णांकf:
	usb_driver_release_पूर्णांकerface(&ims_pcu_driver, pcu->data_पूर्णांकf);
err_मुक्त_mem:
	kमुक्त(pcu);
	वापस error;
पूर्ण

अटल व्योम ims_pcu_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकf->cur_altsetting;

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	/*
	 * See अगर we are dealing with control or data पूर्णांकerface. The cleanup
	 * happens when we unbind primary (control) पूर्णांकerface.
	 */
	अगर (alt->desc.bInterfaceClass != USB_CLASS_COMM)
		वापस;

	sysfs_हटाओ_group(&पूर्णांकf->dev.kobj, &ims_pcu_attr_group);

	ims_pcu_stop_io(pcu);

	अगर (pcu->bootloader_mode)
		ims_pcu_destroy_bootloader_mode(pcu);
	अन्यथा
		ims_pcu_destroy_application_mode(pcu);

	ims_pcu_buffers_मुक्त(pcu);
	kमुक्त(pcu);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ims_pcu_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   pm_message_t message)
अणु
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकf->cur_altsetting;

	अगर (alt->desc.bInterfaceClass == USB_CLASS_COMM)
		ims_pcu_stop_io(pcu);

	वापस 0;
पूर्ण

अटल पूर्णांक ims_pcu_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ims_pcu *pcu = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकf->cur_altsetting;
	पूर्णांक retval = 0;

	अगर (alt->desc.bInterfaceClass == USB_CLASS_COMM) अणु
		retval = ims_pcu_start_io(pcu);
		अगर (retval == 0)
			retval = ims_pcu_line_setup(pcu);
	पूर्ण

	वापस retval;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा usb_device_id ims_pcu_id_table[] = अणु
	अणु
		USB_DEVICE_AND_INTERFACE_INFO(0x04d8, 0x0082,
					USB_CLASS_COMM,
					USB_CDC_SUBCLASS_ACM,
					USB_CDC_ACM_PROTO_AT_V25TER),
		.driver_info = IMS_PCU_APPLICATION_MODE,
	पूर्ण,
	अणु
		USB_DEVICE_AND_INTERFACE_INFO(0x04d8, 0x0083,
					USB_CLASS_COMM,
					USB_CDC_SUBCLASS_ACM,
					USB_CDC_ACM_PROTO_AT_V25TER),
		.driver_info = IMS_PCU_BOOTLOADER_MODE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा usb_driver ims_pcu_driver = अणु
	.name			= "ims_pcu",
	.id_table		= ims_pcu_id_table,
	.probe			= ims_pcu_probe,
	.disconnect		= ims_pcu_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend		= ims_pcu_suspend,
	.resume			= ims_pcu_resume,
	.reset_resume		= ims_pcu_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(ims_pcu_driver);

MODULE_DESCRIPTION("IMS Passenger Control Unit driver");
MODULE_AUTHOR("Dmitry Torokhov <dmitry.torokhov@gmail.com>");
MODULE_LICENSE("GPL");
