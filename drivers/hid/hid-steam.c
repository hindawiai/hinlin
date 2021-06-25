<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * HID driver क्रम Valve Steam Controller
 *
 * Copyright (c) 2018 Rodrigo Rivas Costa <rodrigorivascosta@gmail.com>
 *
 * Supports both the wired and wireless पूर्णांकerfaces.
 *
 * This controller has a builtin emulation of mouse and keyboard: the right pad
 * can be used as a mouse, the shoulder buttons are mouse buttons, A and B
 * buttons are ENTER and ESCAPE, and so on. This is implemented as additional
 * HID पूर्णांकerfaces.
 *
 * This is known as the "lizard mode", because apparently lizards like to use
 * the computer from the coach, without a proper mouse and keyboard.
 *
 * This driver will disable the lizard mode when the input device is खोलोed
 * and re-enable it when the input device is बंदd, so as not to अवरोध user
 * mode behaviour. The lizard_mode parameter can be used to change that.
 *
 * There are a few user space applications (notably Steam Client) that use
 * the hidraw पूर्णांकerface directly to create input devices (XTest, uinput...).
 * In order to aव्योम अवरोधing them this driver creates a layered hidraw device,
 * so it can detect when the client is running and then:
 *  - it will not send any command to the controller.
 *  - this input device will be हटाओd, to aव्योम द्विगुन input of the same
 *    user action.
 * When the client is बंदd, this input device will be created again.
 *
 * For additional functions, such as changing the right-pad margin or चयनing
 * the led, you can use the user-space tool at:
 *
 *   https://github.com/rodrigorc/steamctrl
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/delay.h>
#समावेश <linux/घातer_supply.h>
#समावेश "hid-ids.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rodrigo Rivas Costa <rodrigorivascosta@gmail.com>");

अटल bool lizard_mode = true;

अटल DEFINE_MUTEX(steam_devices_lock);
अटल LIST_HEAD(steam_devices);

#घोषणा STEAM_QUIRK_WIRELESS		BIT(0)

/* Touch pads are 40 mm in diameter and 65535 units */
#घोषणा STEAM_PAD_RESOLUTION 1638
/* Trigger runs are about 5 mm and 256 units */
#घोषणा STEAM_TRIGGER_RESOLUTION 51
/* Joystick runs are about 5 mm and 256 units */
#घोषणा STEAM_JOYSTICK_RESOLUTION 51

#घोषणा STEAM_PAD_FUZZ 256

/*
 * Commands that can be sent in a feature report.
 * Thanks to Valve क्रम some valuable hपूर्णांकs.
 */
#घोषणा STEAM_CMD_SET_MAPPINGS		0x80
#घोषणा STEAM_CMD_CLEAR_MAPPINGS	0x81
#घोषणा STEAM_CMD_GET_MAPPINGS		0x82
#घोषणा STEAM_CMD_GET_ATTRIB		0x83
#घोषणा STEAM_CMD_GET_ATTRIB_LABEL	0x84
#घोषणा STEAM_CMD_DEFAULT_MAPPINGS	0x85
#घोषणा STEAM_CMD_FACTORY_RESET		0x86
#घोषणा STEAM_CMD_WRITE_REGISTER	0x87
#घोषणा STEAM_CMD_CLEAR_REGISTER	0x88
#घोषणा STEAM_CMD_READ_REGISTER		0x89
#घोषणा STEAM_CMD_GET_REGISTER_LABEL	0x8a
#घोषणा STEAM_CMD_GET_REGISTER_MAX	0x8b
#घोषणा STEAM_CMD_GET_REGISTER_DEFAULT	0x8c
#घोषणा STEAM_CMD_SET_MODE		0x8d
#घोषणा STEAM_CMD_DEFAULT_MOUSE		0x8e
#घोषणा STEAM_CMD_FORCEFEEDBAK		0x8f
#घोषणा STEAM_CMD_REQUEST_COMM_STATUS	0xb4
#घोषणा STEAM_CMD_GET_SERIAL		0xae

/* Some useful रेजिस्टर ids */
#घोषणा STEAM_REG_LPAD_MODE		0x07
#घोषणा STEAM_REG_RPAD_MODE		0x08
#घोषणा STEAM_REG_RPAD_MARGIN		0x18
#घोषणा STEAM_REG_LED			0x2d
#घोषणा STEAM_REG_GYRO_MODE		0x30

/* Raw event identअगरiers */
#घोषणा STEAM_EV_INPUT_DATA		0x01
#घोषणा STEAM_EV_CONNECT		0x03
#घोषणा STEAM_EV_BATTERY		0x04

/* Values क्रम GYRO_MODE (biपंचांगask) */
#घोषणा STEAM_GYRO_MODE_OFF		0x0000
#घोषणा STEAM_GYRO_MODE_STEERING	0x0001
#घोषणा STEAM_GYRO_MODE_TILT		0x0002
#घोषणा STEAM_GYRO_MODE_SEND_ORIENTATION	0x0004
#घोषणा STEAM_GYRO_MODE_SEND_RAW_ACCEL		0x0008
#घोषणा STEAM_GYRO_MODE_SEND_RAW_GYRO		0x0010

/* Other अक्रमom स्थिरants */
#घोषणा STEAM_SERIAL_LEN 10

काष्ठा steam_device अणु
	काष्ठा list_head list;
	spinlock_t lock;
	काष्ठा hid_device *hdev, *client_hdev;
	काष्ठा mutex mutex;
	bool client_खोलोed;
	काष्ठा input_dev __rcu *input;
	अचिन्हित दीर्घ quirks;
	काष्ठा work_काष्ठा work_connect;
	bool connected;
	अक्षर serial_no[STEAM_SERIAL_LEN + 1];
	काष्ठा घातer_supply_desc battery_desc;
	काष्ठा घातer_supply __rcu *battery;
	u8 battery_अक्षरge;
	u16 voltage;
पूर्ण;

अटल पूर्णांक steam_recv_report(काष्ठा steam_device *steam,
		u8 *data, पूर्णांक size)
अणु
	काष्ठा hid_report *r;
	u8 *buf;
	पूर्णांक ret;

	r = steam->hdev->report_क्रमागत[HID_FEATURE_REPORT].report_id_hash[0];
	अगर (hid_report_len(r) < 64)
		वापस -EINVAL;

	buf = hid_alloc_report_buf(r, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/*
	 * The report ID is always 0, so strip the first byte from the output.
	 * hid_report_len() is not counting the report ID, so +1 to the length
	 * or अन्यथा we get a EOVERFLOW. We are safe from a buffer overflow
	 * because hid_alloc_report_buf() allocates +7 bytes.
	 */
	ret = hid_hw_raw_request(steam->hdev, 0x00,
			buf, hid_report_len(r) + 1,
			HID_FEATURE_REPORT, HID_REQ_GET_REPORT);
	अगर (ret > 0)
		स_नकल(data, buf + 1, min(size, ret - 1));
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक steam_send_report(काष्ठा steam_device *steam,
		u8 *cmd, पूर्णांक size)
अणु
	काष्ठा hid_report *r;
	u8 *buf;
	अचिन्हित पूर्णांक retries = 50;
	पूर्णांक ret;

	r = steam->hdev->report_क्रमागत[HID_FEATURE_REPORT].report_id_hash[0];
	अगर (hid_report_len(r) < 64)
		वापस -EINVAL;

	buf = hid_alloc_report_buf(r, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* The report ID is always 0 */
	स_नकल(buf + 1, cmd, size);

	/*
	 * Someबार the wireless controller fails with EPIPE
	 * when sending a feature report.
	 * Doing a HID_REQ_GET_REPORT and रुकोing क्रम a जबतक
	 * seems to fix that.
	 */
	करो अणु
		ret = hid_hw_raw_request(steam->hdev, 0,
				buf, size + 1,
				HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
		अगर (ret != -EPIPE)
			अवरोध;
		msleep(20);
	पूर्ण जबतक (--retries);

	kमुक्त(buf);
	अगर (ret < 0)
		hid_err(steam->hdev, "%s: error %d (%*ph)\n", __func__,
				ret, size, cmd);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक steam_send_report_byte(काष्ठा steam_device *steam, u8 cmd)
अणु
	वापस steam_send_report(steam, &cmd, 1);
पूर्ण

अटल पूर्णांक steam_ग_लिखो_रेजिस्टरs(काष्ठा steam_device *steam,
		/* u8 reg, u16 val */...)
अणु
	/* Send: 0x87 len (reg valLo valHi)* */
	u8 reg;
	u16 val;
	u8 cmd[64] = अणुSTEAM_CMD_WRITE_REGISTER, 0x00पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, steam);
	क्रम (;;) अणु
		reg = बहु_तर्क(args, पूर्णांक);
		अगर (reg == 0)
			अवरोध;
		val = बहु_तर्क(args, पूर्णांक);
		cmd[cmd[1] + 2] = reg;
		cmd[cmd[1] + 3] = val & 0xff;
		cmd[cmd[1] + 4] = val >> 8;
		cmd[1] += 3;
	पूर्ण
	बहु_पूर्ण(args);

	वापस steam_send_report(steam, cmd, 2 + cmd[1]);
पूर्ण

अटल पूर्णांक steam_get_serial(काष्ठा steam_device *steam)
अणु
	/*
	 * Send: 0xae 0x15 0x01
	 * Recv: 0xae 0x15 0x01 serialnumber (10 अक्षरs)
	 */
	पूर्णांक ret;
	u8 cmd[] = अणुSTEAM_CMD_GET_SERIAL, 0x15, 0x01पूर्ण;
	u8 reply[3 + STEAM_SERIAL_LEN + 1];

	ret = steam_send_report(steam, cmd, माप(cmd));
	अगर (ret < 0)
		वापस ret;
	ret = steam_recv_report(steam, reply, माप(reply));
	अगर (ret < 0)
		वापस ret;
	अगर (reply[0] != 0xae || reply[1] != 0x15 || reply[2] != 0x01)
		वापस -EIO;
	reply[3 + STEAM_SERIAL_LEN] = 0;
	strlcpy(steam->serial_no, reply + 3, माप(steam->serial_no));
	वापस 0;
पूर्ण

/*
 * This command requests the wireless adaptor to post an event
 * with the connection status. Useful अगर this driver is loaded when
 * the controller is alपढ़ोy connected.
 */
अटल अंतरभूत पूर्णांक steam_request_conn_status(काष्ठा steam_device *steam)
अणु
	वापस steam_send_report_byte(steam, STEAM_CMD_REQUEST_COMM_STATUS);
पूर्ण

अटल व्योम steam_set_lizard_mode(काष्ठा steam_device *steam, bool enable)
अणु
	अगर (enable) अणु
		/* enable esc, enter, cursors */
		steam_send_report_byte(steam, STEAM_CMD_DEFAULT_MAPPINGS);
		/* enable mouse */
		steam_send_report_byte(steam, STEAM_CMD_DEFAULT_MOUSE);
		steam_ग_लिखो_रेजिस्टरs(steam,
			STEAM_REG_RPAD_MARGIN, 0x01, /* enable margin */
			0);
	पूर्ण अन्यथा अणु
		/* disable esc, enter, cursor */
		steam_send_report_byte(steam, STEAM_CMD_CLEAR_MAPPINGS);
		steam_ग_लिखो_रेजिस्टरs(steam,
			STEAM_REG_RPAD_MODE, 0x07, /* disable mouse */
			STEAM_REG_RPAD_MARGIN, 0x00, /* disable margin */
			0);
	पूर्ण
पूर्ण

अटल पूर्णांक steam_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा steam_device *steam = input_get_drvdata(dev);

	mutex_lock(&steam->mutex);
	अगर (!steam->client_खोलोed && lizard_mode)
		steam_set_lizard_mode(steam, false);
	mutex_unlock(&steam->mutex);
	वापस 0;
पूर्ण

अटल व्योम steam_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा steam_device *steam = input_get_drvdata(dev);

	mutex_lock(&steam->mutex);
	अगर (!steam->client_खोलोed && lizard_mode)
		steam_set_lizard_mode(steam, true);
	mutex_unlock(&steam->mutex);
पूर्ण

अटल क्रमागत घातer_supply_property steam_battery_props[] = अणु
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_SCOPE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
पूर्ण;

अटल पूर्णांक steam_battery_get_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा steam_device *steam = घातer_supply_get_drvdata(psy);
	अचिन्हित दीर्घ flags;
	s16 volts;
	u8 batt;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&steam->lock, flags);
	volts = steam->voltage;
	batt = steam->battery_अक्षरge;
	spin_unlock_irqrestore(&steam->lock, flags);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_SCOPE:
		val->पूर्णांकval = POWER_SUPPLY_SCOPE_DEVICE;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = volts * 1000; /* mV -> uV */
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = batt;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक steam_battery_रेजिस्टर(काष्ठा steam_device *steam)
अणु
	काष्ठा घातer_supply *battery;
	काष्ठा घातer_supply_config battery_cfg = अणु .drv_data = steam, पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	steam->battery_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	steam->battery_desc.properties = steam_battery_props;
	steam->battery_desc.num_properties = ARRAY_SIZE(steam_battery_props);
	steam->battery_desc.get_property = steam_battery_get_property;
	steam->battery_desc.name = devm_kaप्र_लिखो(&steam->hdev->dev,
			GFP_KERNEL, "steam-controller-%s-battery",
			steam->serial_no);
	अगर (!steam->battery_desc.name)
		वापस -ENOMEM;

	/* aव्योम the warning of 0% battery जबतक रुकोing क्रम the first info */
	spin_lock_irqsave(&steam->lock, flags);
	steam->voltage = 3000;
	steam->battery_अक्षरge = 100;
	spin_unlock_irqrestore(&steam->lock, flags);

	battery = घातer_supply_रेजिस्टर(&steam->hdev->dev,
			&steam->battery_desc, &battery_cfg);
	अगर (IS_ERR(battery)) अणु
		ret = PTR_ERR(battery);
		hid_err(steam->hdev,
				"%s:power_supply_register failed with error %d\n",
				__func__, ret);
		वापस ret;
	पूर्ण
	rcu_assign_poपूर्णांकer(steam->battery, battery);
	घातer_supply_घातers(battery, &steam->hdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक steam_input_रेजिस्टर(काष्ठा steam_device *steam)
अणु
	काष्ठा hid_device *hdev = steam->hdev;
	काष्ठा input_dev *input;
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	input = rcu_dereference(steam->input);
	rcu_पढ़ो_unlock();
	अगर (input) अणु
		dbg_hid("%s: already connected\n", __func__);
		वापस 0;
	पूर्ण

	input = input_allocate_device();
	अगर (!input)
		वापस -ENOMEM;

	input_set_drvdata(input, steam);
	input->dev.parent = &hdev->dev;
	input->खोलो = steam_input_खोलो;
	input->बंद = steam_input_बंद;

	input->name = (steam->quirks & STEAM_QUIRK_WIRELESS) ?
		"Wireless Steam Controller" :
		"Steam Controller";
	input->phys = hdev->phys;
	input->uniq = steam->serial_no;
	input->id.bustype = hdev->bus;
	input->id.venकरोr = hdev->venकरोr;
	input->id.product = hdev->product;
	input->id.version = hdev->version;

	input_set_capability(input, EV_KEY, BTN_TR2);
	input_set_capability(input, EV_KEY, BTN_TL2);
	input_set_capability(input, EV_KEY, BTN_TR);
	input_set_capability(input, EV_KEY, BTN_TL);
	input_set_capability(input, EV_KEY, BTN_Y);
	input_set_capability(input, EV_KEY, BTN_B);
	input_set_capability(input, EV_KEY, BTN_X);
	input_set_capability(input, EV_KEY, BTN_A);
	input_set_capability(input, EV_KEY, BTN_DPAD_UP);
	input_set_capability(input, EV_KEY, BTN_DPAD_RIGHT);
	input_set_capability(input, EV_KEY, BTN_DPAD_LEFT);
	input_set_capability(input, EV_KEY, BTN_DPAD_DOWN);
	input_set_capability(input, EV_KEY, BTN_SELECT);
	input_set_capability(input, EV_KEY, BTN_MODE);
	input_set_capability(input, EV_KEY, BTN_START);
	input_set_capability(input, EV_KEY, BTN_GEAR_DOWN);
	input_set_capability(input, EV_KEY, BTN_GEAR_UP);
	input_set_capability(input, EV_KEY, BTN_THUMBR);
	input_set_capability(input, EV_KEY, BTN_THUMBL);
	input_set_capability(input, EV_KEY, BTN_THUMB);
	input_set_capability(input, EV_KEY, BTN_THUMB2);

	input_set_असल_params(input, ABS_HAT2Y, 0, 255, 0, 0);
	input_set_असल_params(input, ABS_HAT2X, 0, 255, 0, 0);
	input_set_असल_params(input, ABS_X, -32767, 32767, 0, 0);
	input_set_असल_params(input, ABS_Y, -32767, 32767, 0, 0);
	input_set_असल_params(input, ABS_RX, -32767, 32767,
			STEAM_PAD_FUZZ, 0);
	input_set_असल_params(input, ABS_RY, -32767, 32767,
			STEAM_PAD_FUZZ, 0);
	input_set_असल_params(input, ABS_HAT0X, -32767, 32767,
			STEAM_PAD_FUZZ, 0);
	input_set_असल_params(input, ABS_HAT0Y, -32767, 32767,
			STEAM_PAD_FUZZ, 0);
	input_असल_set_res(input, ABS_X, STEAM_JOYSTICK_RESOLUTION);
	input_असल_set_res(input, ABS_Y, STEAM_JOYSTICK_RESOLUTION);
	input_असल_set_res(input, ABS_RX, STEAM_PAD_RESOLUTION);
	input_असल_set_res(input, ABS_RY, STEAM_PAD_RESOLUTION);
	input_असल_set_res(input, ABS_HAT0X, STEAM_PAD_RESOLUTION);
	input_असल_set_res(input, ABS_HAT0Y, STEAM_PAD_RESOLUTION);
	input_असल_set_res(input, ABS_HAT2Y, STEAM_TRIGGER_RESOLUTION);
	input_असल_set_res(input, ABS_HAT2X, STEAM_TRIGGER_RESOLUTION);

	ret = input_रेजिस्टर_device(input);
	अगर (ret)
		जाओ input_रेजिस्टर_fail;

	rcu_assign_poपूर्णांकer(steam->input, input);
	वापस 0;

input_रेजिस्टर_fail:
	input_मुक्त_device(input);
	वापस ret;
पूर्ण

अटल व्योम steam_input_unरेजिस्टर(काष्ठा steam_device *steam)
अणु
	काष्ठा input_dev *input;
	rcu_पढ़ो_lock();
	input = rcu_dereference(steam->input);
	rcu_पढ़ो_unlock();
	अगर (!input)
		वापस;
	RCU_INIT_POINTER(steam->input, शून्य);
	synchronize_rcu();
	input_unरेजिस्टर_device(input);
पूर्ण

अटल व्योम steam_battery_unरेजिस्टर(काष्ठा steam_device *steam)
अणु
	काष्ठा घातer_supply *battery;

	rcu_पढ़ो_lock();
	battery = rcu_dereference(steam->battery);
	rcu_पढ़ो_unlock();

	अगर (!battery)
		वापस;
	RCU_INIT_POINTER(steam->battery, शून्य);
	synchronize_rcu();
	घातer_supply_unरेजिस्टर(battery);
पूर्ण

अटल पूर्णांक steam_रेजिस्टर(काष्ठा steam_device *steam)
अणु
	पूर्णांक ret;
	bool client_खोलोed;

	/*
	 * This function can be called several बार in a row with the
	 * wireless adaptor, without steam_unरेजिस्टर() between them, because
	 * another client send a get_connection_status command, क्रम example.
	 * The battery and serial number are set just once per device.
	 */
	अगर (!steam->serial_no[0]) अणु
		/*
		 * Unlikely, but getting the serial could fail, and it is not so
		 * important, so make up a serial number and go on.
		 */
		mutex_lock(&steam->mutex);
		अगर (steam_get_serial(steam) < 0)
			strlcpy(steam->serial_no, "XXXXXXXXXX",
					माप(steam->serial_no));
		mutex_unlock(&steam->mutex);

		hid_info(steam->hdev, "Steam Controller '%s' connected",
				steam->serial_no);

		/* ignore battery errors, we can live without it */
		अगर (steam->quirks & STEAM_QUIRK_WIRELESS)
			steam_battery_रेजिस्टर(steam);

		mutex_lock(&steam_devices_lock);
		अगर (list_empty(&steam->list))
			list_add(&steam->list, &steam_devices);
		mutex_unlock(&steam_devices_lock);
	पूर्ण

	mutex_lock(&steam->mutex);
	client_खोलोed = steam->client_खोलोed;
	अगर (!client_खोलोed)
		steam_set_lizard_mode(steam, lizard_mode);
	mutex_unlock(&steam->mutex);

	अगर (!client_खोलोed)
		ret = steam_input_रेजिस्टर(steam);
	अन्यथा
		ret = 0;

	वापस ret;
पूर्ण

अटल व्योम steam_unरेजिस्टर(काष्ठा steam_device *steam)
अणु
	steam_battery_unरेजिस्टर(steam);
	steam_input_unरेजिस्टर(steam);
	अगर (steam->serial_no[0]) अणु
		hid_info(steam->hdev, "Steam Controller '%s' disconnected",
				steam->serial_no);
		mutex_lock(&steam_devices_lock);
		list_del_init(&steam->list);
		mutex_unlock(&steam_devices_lock);
		steam->serial_no[0] = 0;
	पूर्ण
पूर्ण

अटल व्योम steam_work_connect_cb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा steam_device *steam = container_of(work, काष्ठा steam_device,
							work_connect);
	अचिन्हित दीर्घ flags;
	bool connected;
	पूर्णांक ret;

	spin_lock_irqsave(&steam->lock, flags);
	connected = steam->connected;
	spin_unlock_irqrestore(&steam->lock, flags);

	अगर (connected) अणु
		ret = steam_रेजिस्टर(steam);
		अगर (ret) अणु
			hid_err(steam->hdev,
				"%s:steam_register failed with error %d\n",
				__func__, ret);
		पूर्ण
	पूर्ण अन्यथा अणु
		steam_unरेजिस्टर(steam);
	पूर्ण
पूर्ण

अटल bool steam_is_valve_पूर्णांकerface(काष्ठा hid_device *hdev)
अणु
	काष्ठा hid_report_क्रमागत *rep_क्रमागत;

	/*
	 * The wired device creates 3 पूर्णांकerfaces:
	 *  0: emulated mouse.
	 *  1: emulated keyboard.
	 *  2: the real game pad.
	 * The wireless device creates 5 पूर्णांकerfaces:
	 *  0: emulated keyboard.
	 *  1-4: slots where up to 4 real game pads will be connected to.
	 * We know which one is the real gamepad पूर्णांकerface because they are the
	 * only ones with a feature report.
	 */
	rep_क्रमागत = &hdev->report_क्रमागत[HID_FEATURE_REPORT];
	वापस !list_empty(&rep_क्रमागत->report_list);
पूर्ण

अटल पूर्णांक steam_client_ll_parse(काष्ठा hid_device *hdev)
अणु
	काष्ठा steam_device *steam = hdev->driver_data;

	वापस hid_parse_report(hdev, steam->hdev->dev_rdesc,
			steam->hdev->dev_rsize);
पूर्ण

अटल पूर्णांक steam_client_ll_start(काष्ठा hid_device *hdev)
अणु
	वापस 0;
पूर्ण

अटल व्योम steam_client_ll_stop(काष्ठा hid_device *hdev)
अणु
पूर्ण

अटल पूर्णांक steam_client_ll_खोलो(काष्ठा hid_device *hdev)
अणु
	काष्ठा steam_device *steam = hdev->driver_data;

	mutex_lock(&steam->mutex);
	steam->client_खोलोed = true;
	mutex_unlock(&steam->mutex);

	steam_input_unरेजिस्टर(steam);

	वापस 0;
पूर्ण

अटल व्योम steam_client_ll_बंद(काष्ठा hid_device *hdev)
अणु
	काष्ठा steam_device *steam = hdev->driver_data;

	अचिन्हित दीर्घ flags;
	bool connected;

	spin_lock_irqsave(&steam->lock, flags);
	connected = steam->connected;
	spin_unlock_irqrestore(&steam->lock, flags);

	mutex_lock(&steam->mutex);
	steam->client_खोलोed = false;
	अगर (connected)
		steam_set_lizard_mode(steam, lizard_mode);
	mutex_unlock(&steam->mutex);

	अगर (connected)
		steam_input_रेजिस्टर(steam);
पूर्ण

अटल पूर्णांक steam_client_ll_raw_request(काष्ठा hid_device *hdev,
				अचिन्हित अक्षर reportnum, u8 *buf,
				माप_प्रकार count, अचिन्हित अक्षर report_type,
				पूर्णांक reqtype)
अणु
	काष्ठा steam_device *steam = hdev->driver_data;

	वापस hid_hw_raw_request(steam->hdev, reportnum, buf, count,
			report_type, reqtype);
पूर्ण

अटल काष्ठा hid_ll_driver steam_client_ll_driver = अणु
	.parse = steam_client_ll_parse,
	.start = steam_client_ll_start,
	.stop = steam_client_ll_stop,
	.खोलो = steam_client_ll_खोलो,
	.बंद = steam_client_ll_बंद,
	.raw_request = steam_client_ll_raw_request,
पूर्ण;

अटल काष्ठा hid_device *steam_create_client_hid(काष्ठा hid_device *hdev)
अणु
	काष्ठा hid_device *client_hdev;

	client_hdev = hid_allocate_device();
	अगर (IS_ERR(client_hdev))
		वापस client_hdev;

	client_hdev->ll_driver = &steam_client_ll_driver;
	client_hdev->dev.parent = hdev->dev.parent;
	client_hdev->bus = hdev->bus;
	client_hdev->venकरोr = hdev->venकरोr;
	client_hdev->product = hdev->product;
	client_hdev->version = hdev->version;
	client_hdev->type = hdev->type;
	client_hdev->country = hdev->country;
	strlcpy(client_hdev->name, hdev->name,
			माप(client_hdev->name));
	strlcpy(client_hdev->phys, hdev->phys,
			माप(client_hdev->phys));
	/*
	 * Since we use the same device info than the real पूर्णांकerface to
	 * trick userspace, we will be calling steam_probe recursively.
	 * We need to recognize the client पूर्णांकerface somehow.
	 */
	client_hdev->group = HID_GROUP_STEAM;
	वापस client_hdev;
पूर्ण

अटल पूर्णांक steam_probe(काष्ठा hid_device *hdev,
				स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा steam_device *steam;
	पूर्णांक ret;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev,
			"%s:parse of hid interface failed\n", __func__);
		वापस ret;
	पूर्ण

	/*
	 * The भव client_dev is only used क्रम hidraw.
	 * Also aव्योम the recursive probe.
	 */
	अगर (hdev->group == HID_GROUP_STEAM)
		वापस hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	/*
	 * The non-valve पूर्णांकerfaces (mouse and keyboard emulation) are
	 * connected without changes.
	 */
	अगर (!steam_is_valve_पूर्णांकerface(hdev))
		वापस hid_hw_start(hdev, HID_CONNECT_DEFAULT);

	steam = devm_kzalloc(&hdev->dev, माप(*steam), GFP_KERNEL);
	अगर (!steam) अणु
		ret = -ENOMEM;
		जाओ steam_alloc_fail;
	पूर्ण
	steam->hdev = hdev;
	hid_set_drvdata(hdev, steam);
	spin_lock_init(&steam->lock);
	mutex_init(&steam->mutex);
	steam->quirks = id->driver_data;
	INIT_WORK(&steam->work_connect, steam_work_connect_cb);
	INIT_LIST_HEAD(&steam->list);

	steam->client_hdev = steam_create_client_hid(hdev);
	अगर (IS_ERR(steam->client_hdev)) अणु
		ret = PTR_ERR(steam->client_hdev);
		जाओ client_hdev_fail;
	पूर्ण
	steam->client_hdev->driver_data = steam;

	/*
	 * With the real steam controller पूर्णांकerface, करो not connect hidraw.
	 * Instead, create the client_hid and connect that.
	 */
	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT & ~HID_CONNECT_HIDRAW);
	अगर (ret)
		जाओ hid_hw_start_fail;

	ret = hid_add_device(steam->client_hdev);
	अगर (ret)
		जाओ client_hdev_add_fail;

	ret = hid_hw_खोलो(hdev);
	अगर (ret) अणु
		hid_err(hdev,
			"%s:hid_hw_open\n",
			__func__);
		जाओ hid_hw_खोलो_fail;
	पूर्ण

	अगर (steam->quirks & STEAM_QUIRK_WIRELESS) अणु
		hid_info(hdev, "Steam wireless receiver connected");
		/* If using a wireless adaptor ask क्रम connection status */
		steam->connected = false;
		steam_request_conn_status(steam);
	पूर्ण अन्यथा अणु
		/* A wired connection is always present */
		steam->connected = true;
		ret = steam_रेजिस्टर(steam);
		अगर (ret) अणु
			hid_err(hdev,
				"%s:steam_register failed with error %d\n",
				__func__, ret);
			जाओ input_रेजिस्टर_fail;
		पूर्ण
	पूर्ण

	वापस 0;

input_रेजिस्टर_fail:
hid_hw_खोलो_fail:
client_hdev_add_fail:
	hid_hw_stop(hdev);
hid_hw_start_fail:
	hid_destroy_device(steam->client_hdev);
client_hdev_fail:
	cancel_work_sync(&steam->work_connect);
steam_alloc_fail:
	hid_err(hdev, "%s: failed with error %d\n",
			__func__, ret);
	वापस ret;
पूर्ण

अटल व्योम steam_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा steam_device *steam = hid_get_drvdata(hdev);

	अगर (!steam || hdev->group == HID_GROUP_STEAM) अणु
		hid_hw_stop(hdev);
		वापस;
	पूर्ण

	hid_destroy_device(steam->client_hdev);
	steam->client_खोलोed = false;
	cancel_work_sync(&steam->work_connect);
	अगर (steam->quirks & STEAM_QUIRK_WIRELESS) अणु
		hid_info(hdev, "Steam wireless receiver disconnected");
	पूर्ण
	hid_hw_बंद(hdev);
	hid_hw_stop(hdev);
	steam_unरेजिस्टर(steam);
पूर्ण

अटल व्योम steam_करो_connect_event(काष्ठा steam_device *steam, bool connected)
अणु
	अचिन्हित दीर्घ flags;
	bool changed;

	spin_lock_irqsave(&steam->lock, flags);
	changed = steam->connected != connected;
	steam->connected = connected;
	spin_unlock_irqrestore(&steam->lock, flags);

	अगर (changed && schedule_work(&steam->work_connect) == 0)
		dbg_hid("%s: connected=%d event already queued\n",
				__func__, connected);
पूर्ण

/*
 * Some input data in the protocol has the opposite sign.
 * Clamp the values to 32767..-32767 so that the range is
 * symmetrical and can be negated safely.
 */
अटल अंतरभूत s16 steam_le16(u8 *data)
अणु
	s16 x = (s16) le16_to_cpup((__le16 *)data);

	वापस x == -32768 ? -32767 : x;
पूर्ण

/*
 * The size क्रम this message payload is 60.
 * The known values are:
 *  (* values are not sent through wireless)
 *  (* accelerator/gyro is disabled by शेष)
 *  Offset| Type  | Mapped to |Meaning
 * -------+-------+-----------+--------------------------
 *  4-7   | u32   | --        | sequence number
 *  8-10  | 24bit | see below | buttons
 *  11    | u8    | ABS_HAT2Y | left trigger
 *  12    | u8    | ABS_HAT2X | right trigger
 *  13-15 | --    | --        | always 0
 *  16-17 | s16   | ABS_X/ABS_HAT0X     | X value
 *  18-19 | s16   | ABS_Y/ABS_HAT0Y     | Y value
 *  20-21 | s16   | ABS_RX    | right-pad X value
 *  22-23 | s16   | ABS_RY    | right-pad Y value
 *  24-25 | s16   | --        | * left trigger
 *  26-27 | s16   | --        | * right trigger
 *  28-29 | s16   | --        | * accelerometer X value
 *  30-31 | s16   | --        | * accelerometer Y value
 *  32-33 | s16   | --        | * accelerometer Z value
 *  34-35 | s16   | --        | gyro X value
 *  36-36 | s16   | --        | gyro Y value
 *  38-39 | s16   | --        | gyro Z value
 *  40-41 | s16   | --        | quaternion W value
 *  42-43 | s16   | --        | quaternion X value
 *  44-45 | s16   | --        | quaternion Y value
 *  46-47 | s16   | --        | quaternion Z value
 *  48-49 | --    | --        | always 0
 *  50-51 | s16   | --        | * left trigger (uncalibrated)
 *  52-53 | s16   | --        | * right trigger (uncalibrated)
 *  54-55 | s16   | --        | * joystick X value (uncalibrated)
 *  56-57 | s16   | --        | * joystick Y value (uncalibrated)
 *  58-59 | s16   | --        | * left-pad X value
 *  60-61 | s16   | --        | * left-pad Y value
 *  62-63 | u16   | --        | * battery voltage
 *
 * The buttons are:
 *  Bit  | Mapped to  | Description
 * ------+------------+--------------------------------
 *  8.0  | BTN_TR2    | right trigger fully pressed
 *  8.1  | BTN_TL2    | left trigger fully pressed
 *  8.2  | BTN_TR     | right shoulder
 *  8.3  | BTN_TL     | left shoulder
 *  8.4  | BTN_Y      | button Y
 *  8.5  | BTN_B      | button B
 *  8.6  | BTN_X      | button X
 *  8.7  | BTN_A      | button A
 *  9.0  | BTN_DPAD_UP    | lef-pad up
 *  9.1  | BTN_DPAD_RIGHT | lef-pad right
 *  9.2  | BTN_DPAD_LEFT  | lef-pad left
 *  9.3  | BTN_DPAD_DOWN  | lef-pad करोwn
 *  9.4  | BTN_SELECT | menu left
 *  9.5  | BTN_MODE   | steam logo
 *  9.6  | BTN_START  | menu right
 *  9.7  | BTN_GEAR_DOWN | left back lever
 * 10.0  | BTN_GEAR_UP   | right back lever
 * 10.1  | --         | left-pad clicked
 * 10.2  | BTN_THUMBR | right-pad clicked
 * 10.3  | BTN_THUMB  | left-pad touched (but see explanation below)
 * 10.4  | BTN_THUMB2 | right-pad touched
 * 10.5  | --         | unknown
 * 10.6  | BTN_THUMBL | joystick clicked
 * 10.7  | --         | lpad_and_joy
 */

अटल व्योम steam_करो_input_event(काष्ठा steam_device *steam,
		काष्ठा input_dev *input, u8 *data)
अणु
	/* 24 bits of buttons */
	u8 b8, b9, b10;
	s16 x, y;
	bool lpad_touched, lpad_and_joy;

	b8 = data[8];
	b9 = data[9];
	b10 = data[10];

	input_report_असल(input, ABS_HAT2Y, data[11]);
	input_report_असल(input, ABS_HAT2X, data[12]);

	/*
	 * These two bits tells how to पूर्णांकerpret the values X and Y.
	 * lpad_and_joy tells that the joystick and the lpad are used at the
	 * same समय.
	 * lpad_touched tells whether X/Y are to be पढ़ो as lpad coord or
	 * joystick values.
	 * (lpad_touched || lpad_and_joy) tells अगर the lpad is really touched.
	 */
	lpad_touched = b10 & BIT(3);
	lpad_and_joy = b10 & BIT(7);
	x = steam_le16(data + 16);
	y = -steam_le16(data + 18);

	input_report_असल(input, lpad_touched ? ABS_HAT0X : ABS_X, x);
	input_report_असल(input, lpad_touched ? ABS_HAT0Y : ABS_Y, y);
	/* Check अगर joystick is centered */
	अगर (lpad_touched && !lpad_and_joy) अणु
		input_report_असल(input, ABS_X, 0);
		input_report_असल(input, ABS_Y, 0);
	पूर्ण
	/* Check अगर lpad is untouched */
	अगर (!(lpad_touched || lpad_and_joy)) अणु
		input_report_असल(input, ABS_HAT0X, 0);
		input_report_असल(input, ABS_HAT0Y, 0);
	पूर्ण

	input_report_असल(input, ABS_RX, steam_le16(data + 20));
	input_report_असल(input, ABS_RY, -steam_le16(data + 22));

	input_event(input, EV_KEY, BTN_TR2, !!(b8 & BIT(0)));
	input_event(input, EV_KEY, BTN_TL2, !!(b8 & BIT(1)));
	input_event(input, EV_KEY, BTN_TR, !!(b8 & BIT(2)));
	input_event(input, EV_KEY, BTN_TL, !!(b8 & BIT(3)));
	input_event(input, EV_KEY, BTN_Y, !!(b8 & BIT(4)));
	input_event(input, EV_KEY, BTN_B, !!(b8 & BIT(5)));
	input_event(input, EV_KEY, BTN_X, !!(b8 & BIT(6)));
	input_event(input, EV_KEY, BTN_A, !!(b8 & BIT(7)));
	input_event(input, EV_KEY, BTN_SELECT, !!(b9 & BIT(4)));
	input_event(input, EV_KEY, BTN_MODE, !!(b9 & BIT(5)));
	input_event(input, EV_KEY, BTN_START, !!(b9 & BIT(6)));
	input_event(input, EV_KEY, BTN_GEAR_DOWN, !!(b9 & BIT(7)));
	input_event(input, EV_KEY, BTN_GEAR_UP, !!(b10 & BIT(0)));
	input_event(input, EV_KEY, BTN_THUMBR, !!(b10 & BIT(2)));
	input_event(input, EV_KEY, BTN_THUMBL, !!(b10 & BIT(6)));
	input_event(input, EV_KEY, BTN_THUMB, lpad_touched || lpad_and_joy);
	input_event(input, EV_KEY, BTN_THUMB2, !!(b10 & BIT(4)));
	input_event(input, EV_KEY, BTN_DPAD_UP, !!(b9 & BIT(0)));
	input_event(input, EV_KEY, BTN_DPAD_RIGHT, !!(b9 & BIT(1)));
	input_event(input, EV_KEY, BTN_DPAD_LEFT, !!(b9 & BIT(2)));
	input_event(input, EV_KEY, BTN_DPAD_DOWN, !!(b9 & BIT(3)));

	input_sync(input);
पूर्ण

/*
 * The size क्रम this message payload is 11.
 * The known values are:
 *  Offset| Type  | Meaning
 * -------+-------+---------------------------
 *  4-7   | u32   | sequence number
 *  8-11  | --    | always 0
 *  12-13 | u16   | voltage (mV)
 *  14    | u8    | battery percent
 */
अटल व्योम steam_करो_battery_event(काष्ठा steam_device *steam,
		काष्ठा घातer_supply *battery, u8 *data)
अणु
	अचिन्हित दीर्घ flags;

	s16 volts = steam_le16(data + 12);
	u8 batt = data[14];

	/* Creating the battery may have failed */
	rcu_पढ़ो_lock();
	battery = rcu_dereference(steam->battery);
	अगर (likely(battery)) अणु
		spin_lock_irqsave(&steam->lock, flags);
		steam->voltage = volts;
		steam->battery_अक्षरge = batt;
		spin_unlock_irqrestore(&steam->lock, flags);
		घातer_supply_changed(battery);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक steam_raw_event(काष्ठा hid_device *hdev,
			काष्ठा hid_report *report, u8 *data,
			पूर्णांक size)
अणु
	काष्ठा steam_device *steam = hid_get_drvdata(hdev);
	काष्ठा input_dev *input;
	काष्ठा घातer_supply *battery;

	अगर (!steam)
		वापस 0;

	अगर (steam->client_खोलोed)
		hid_input_report(steam->client_hdev, HID_FEATURE_REPORT,
				data, size, 0);
	/*
	 * All messages are size=64, all values little-endian.
	 * The क्रमmat is:
	 *  Offset| Meaning
	 * -------+--------------------------------------------
	 *  0-1   | always 0x01, 0x00, maybe protocol version?
	 *  2     | type of message
	 *  3     | length of the real payload (not checked)
	 *  4-n   | payload data, depends on the type
	 *
	 * There are these known types of message:
	 *  0x01: input data (60 bytes)
	 *  0x03: wireless connect/disconnect (1 byte)
	 *  0x04: battery status (11 bytes)
	 */

	अगर (size != 64 || data[0] != 1 || data[1] != 0)
		वापस 0;

	चयन (data[2]) अणु
	हाल STEAM_EV_INPUT_DATA:
		अगर (steam->client_खोलोed)
			वापस 0;
		rcu_पढ़ो_lock();
		input = rcu_dereference(steam->input);
		अगर (likely(input))
			steam_करो_input_event(steam, input, data);
		rcu_पढ़ो_unlock();
		अवरोध;
	हाल STEAM_EV_CONNECT:
		/*
		 * The payload of this event is a single byte:
		 *  0x01: disconnected.
		 *  0x02: connected.
		 */
		चयन (data[4]) अणु
		हाल 0x01:
			steam_करो_connect_event(steam, false);
			अवरोध;
		हाल 0x02:
			steam_करो_connect_event(steam, true);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल STEAM_EV_BATTERY:
		अगर (steam->quirks & STEAM_QUIRK_WIRELESS) अणु
			rcu_पढ़ो_lock();
			battery = rcu_dereference(steam->battery);
			अगर (likely(battery)) अणु
				steam_करो_battery_event(steam, battery, data);
			पूर्ण अन्यथा अणु
				dbg_hid(
					"%s: battery data without connect event\n",
					__func__);
				steam_करो_connect_event(steam, true);
			पूर्ण
			rcu_पढ़ो_unlock();
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक steam_param_set_lizard_mode(स्थिर अक्षर *val,
					स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा steam_device *steam;
	पूर्णांक ret;

	ret = param_set_bool(val, kp);
	अगर (ret)
		वापस ret;

	mutex_lock(&steam_devices_lock);
	list_क्रम_each_entry(steam, &steam_devices, list) अणु
		mutex_lock(&steam->mutex);
		अगर (!steam->client_खोलोed)
			steam_set_lizard_mode(steam, lizard_mode);
		mutex_unlock(&steam->mutex);
	पूर्ण
	mutex_unlock(&steam_devices_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops steam_lizard_mode_ops = अणु
	.set	= steam_param_set_lizard_mode,
	.get	= param_get_bool,
पूर्ण;

module_param_cb(lizard_mode, &steam_lizard_mode_ops, &lizard_mode, 0644);
MODULE_PARM_DESC(lizard_mode,
	"Enable mouse and keyboard emulation (lizard mode) when the gamepad is not in use");

अटल स्थिर काष्ठा hid_device_id steam_controllers[] = अणु
	अणु /* Wired Steam Controller */
	  HID_USB_DEVICE(USB_VENDOR_ID_VALVE,
		USB_DEVICE_ID_STEAM_CONTROLLER)
	पूर्ण,
	अणु /* Wireless Steam Controller */
	  HID_USB_DEVICE(USB_VENDOR_ID_VALVE,
		USB_DEVICE_ID_STEAM_CONTROLLER_WIRELESS),
	  .driver_data = STEAM_QUIRK_WIRELESS
	पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, steam_controllers);

अटल काष्ठा hid_driver steam_controller_driver = अणु
	.name = "hid-steam",
	.id_table = steam_controllers,
	.probe = steam_probe,
	.हटाओ = steam_हटाओ,
	.raw_event = steam_raw_event,
पूर्ण;

module_hid_driver(steam_controller_driver);
