<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * corsair-cpro.c - Linux driver क्रम Corsair Commander Pro
 * Copyright (C) 2020 Marius Zachmann <mail@mariuszachmann.de>
 *
 * This driver uses hid reports to communicate with the device to allow hidraw userspace drivers
 * still being used. The device करोes not use report ids. When using hidraw and this driver
 * simultaniously, reports could be चयनed.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/completion.h>
#समावेश <linux/hid.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#घोषणा USB_VENDOR_ID_CORSAIR			0x1b1c
#घोषणा USB_PRODUCT_ID_CORSAIR_COMMANDERPRO	0x0c10
#घोषणा USB_PRODUCT_ID_CORSAIR_1000D		0x1d00

#घोषणा OUT_BUFFER_SIZE		63
#घोषणा IN_BUFFER_SIZE		16
#घोषणा LABEL_LENGTH		11
#घोषणा REQ_TIMEOUT		300

#घोषणा CTL_GET_TMP_CNCT	0x10	/*
					 * वापसs in bytes 1-4 क्रम each temp sensor:
					 * 0 not connected
					 * 1 connected
					 */
#घोषणा CTL_GET_TMP		0x11	/*
					 * send: byte 1 is channel, rest zero
					 * rcv:  वापसs temp क्रम channel in centi-degree celsius
					 * in bytes 1 and 2
					 * वापसs 0x11 in byte 0 अगर no sensor is connected
					 */
#घोषणा CTL_GET_VOLT		0x12	/*
					 * send: byte 1 is rail number: 0 = 12v, 1 = 5v, 2 = 3.3v
					 * rcv:  वापसs millivolt in bytes 1,2
					 * वापसs error 0x10 अगर request is invalid
					 */
#घोषणा CTL_GET_FAN_CNCT	0x20	/*
					 * वापसs in bytes 1-6 क्रम each fan:
					 * 0 not connected
					 * 1 3pin
					 * 2 4pin
					 */
#घोषणा CTL_GET_FAN_RPM		0x21	/*
					 * send: byte 1 is channel, rest zero
					 * rcv:  वापसs rpm in bytes 1,2
					 */
#घोषणा CTL_GET_FAN_PWM		0x22	/*
					 * send: byte 1 is channel, rest zero
					 * rcv:  वापसs pwm in byte 1 अगर it was set
					 *	 वापसs error 0x12 अगर fan is controlled via
					 *	 fan_target or fan curve
					 */
#घोषणा CTL_SET_FAN_FPWM	0x23	/*
					 * set fixed pwm
					 * send: byte 1 is fan number
					 * send: byte 2 is percentage from 0 - 100
					 */
#घोषणा CTL_SET_FAN_TARGET	0x24	/*
					 * set target rpm
					 * send: byte 1 is fan number
					 * send: byte 2-3 is target
					 * device accepts all values from 0x00 - 0xFFFF
					 */

#घोषणा NUM_FANS		6
#घोषणा NUM_TEMP_SENSORS	4

काष्ठा ccp_device अणु
	काष्ठा hid_device *hdev;
	काष्ठा device *hwmon_dev;
	काष्ठा completion रुको_input_report;
	काष्ठा mutex mutex; /* whenever buffer is used, lock beक्रमe send_usb_cmd */
	u8 *buffer;
	पूर्णांक target[6];
	DECLARE_BITMAP(temp_cnct, NUM_TEMP_SENSORS);
	DECLARE_BITMAP(fan_cnct, NUM_FANS);
	अक्षर fan_label[6][LABEL_LENGTH];
पूर्ण;

/* converts response error in buffer to त्रुटि_सं */
अटल पूर्णांक ccp_get_त्रुटि_सं(काष्ठा ccp_device *ccp)
अणु
	चयन (ccp->buffer[0]) अणु
	हाल 0x00: /* success */
		वापस 0;
	हाल 0x01: /* called invalid command */
		वापस -EOPNOTSUPP;
	हाल 0x10: /* called GET_VOLT / GET_TMP with invalid arguments */
		वापस -EINVAL;
	हाल 0x11: /* requested temps of disconnected sensors */
	हाल 0x12: /* requested pwm of not pwm controlled channels */
		वापस -ENODATA;
	शेष:
		hid_dbg(ccp->hdev, "unknown device response error: %d", ccp->buffer[0]);
		वापस -EIO;
	पूर्ण
पूर्ण

/* send command, check क्रम error in response, response in ccp->buffer */
अटल पूर्णांक send_usb_cmd(काष्ठा ccp_device *ccp, u8 command, u8 byte1, u8 byte2, u8 byte3)
अणु
	अचिन्हित दीर्घ t;
	पूर्णांक ret;

	स_रखो(ccp->buffer, 0x00, OUT_BUFFER_SIZE);
	ccp->buffer[0] = command;
	ccp->buffer[1] = byte1;
	ccp->buffer[2] = byte2;
	ccp->buffer[3] = byte3;

	reinit_completion(&ccp->रुको_input_report);

	ret = hid_hw_output_report(ccp->hdev, ccp->buffer, OUT_BUFFER_SIZE);
	अगर (ret < 0)
		वापस ret;

	t = रुको_क्रम_completion_समयout(&ccp->रुको_input_report, msecs_to_jअगरfies(REQ_TIMEOUT));
	अगर (!t)
		वापस -ETIMEDOUT;

	वापस ccp_get_त्रुटि_सं(ccp);
पूर्ण

अटल पूर्णांक ccp_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा ccp_device *ccp = hid_get_drvdata(hdev);

	/* only copy buffer when requested */
	अगर (completion_करोne(&ccp->रुको_input_report))
		वापस 0;

	स_नकल(ccp->buffer, data, min(IN_BUFFER_SIZE, size));
	complete(&ccp->रुको_input_report);

	वापस 0;
पूर्ण

/* requests and वापसs single data values depending on channel */
अटल पूर्णांक get_data(काष्ठा ccp_device *ccp, पूर्णांक command, पूर्णांक channel, bool two_byte_data)
अणु
	पूर्णांक ret;

	mutex_lock(&ccp->mutex);

	ret = send_usb_cmd(ccp, command, channel, 0, 0);
	अगर (ret)
		जाओ out_unlock;

	ret = ccp->buffer[1];
	अगर (two_byte_data)
		ret = (ret << 8) + ccp->buffer[2];

out_unlock:
	mutex_unlock(&ccp->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक set_pwm(काष्ठा ccp_device *ccp, पूर्णांक channel, दीर्घ val)
अणु
	पूर्णांक ret;

	अगर (val < 0 || val > 255)
		वापस -EINVAL;

	/* The Corsair Commander Pro uses values from 0-100 */
	val = DIV_ROUND_CLOSEST(val * 100, 255);

	mutex_lock(&ccp->mutex);

	ret = send_usb_cmd(ccp, CTL_SET_FAN_FPWM, channel, val, 0);
	अगर (!ret)
		ccp->target[channel] = -ENODATA;

	mutex_unlock(&ccp->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक set_target(काष्ठा ccp_device *ccp, पूर्णांक channel, दीर्घ val)
अणु
	पूर्णांक ret;

	val = clamp_val(val, 0, 0xFFFF);
	ccp->target[channel] = val;

	mutex_lock(&ccp->mutex);
	ret = send_usb_cmd(ccp, CTL_SET_FAN_TARGET, channel, val >> 8, val);

	mutex_unlock(&ccp->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ccp_पढ़ो_string(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			   u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	काष्ठा ccp_device *ccp = dev_get_drvdata(dev);

	चयन (type) अणु
	हाल hwmon_fan:
		चयन (attr) अणु
		हाल hwmon_fan_label:
			*str = ccp->fan_label[channel];
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ccp_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		    u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा ccp_device *ccp = dev_get_drvdata(dev);
	पूर्णांक ret;

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			ret = get_data(ccp, CTL_GET_TMP, channel, true);
			अगर (ret < 0)
				वापस ret;
			*val = ret * 10;
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_fan:
		चयन (attr) अणु
		हाल hwmon_fan_input:
			ret = get_data(ccp, CTL_GET_FAN_RPM, channel, true);
			अगर (ret < 0)
				वापस ret;
			*val = ret;
			वापस 0;
		हाल hwmon_fan_target:
			/* how to पढ़ो target values from the device is unknown */
			/* driver वापसs last set value or 0			*/
			अगर (ccp->target[channel] < 0)
				वापस -ENODATA;
			*val = ccp->target[channel];
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_pwm:
		चयन (attr) अणु
		हाल hwmon_pwm_input:
			ret = get_data(ccp, CTL_GET_FAN_PWM, channel, false);
			अगर (ret < 0)
				वापस ret;
			*val = DIV_ROUND_CLOSEST(ret * 255, 100);
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
			ret = get_data(ccp, CTL_GET_VOLT, channel, true);
			अगर (ret < 0)
				वापस ret;
			*val = ret;
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण;

अटल पूर्णांक ccp_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		     u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा ccp_device *ccp = dev_get_drvdata(dev);

	चयन (type) अणु
	हाल hwmon_pwm:
		चयन (attr) अणु
		हाल hwmon_pwm_input:
			वापस set_pwm(ccp, channel, val);
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_fan:
		चयन (attr) अणु
		हाल hwmon_fan_target:
			वापस set_target(ccp, channel, val);
		शेष:
			अवरोध;
		पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण;

अटल umode_t ccp_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
			      u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा ccp_device *ccp = data;

	चयन (type) अणु
	हाल hwmon_temp:
		अगर (!test_bit(channel, ccp->temp_cnct))
			अवरोध;

		चयन (attr) अणु
		हाल hwmon_temp_input:
			वापस 0444;
		हाल hwmon_temp_label:
			वापस 0444;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_fan:
		अगर (!test_bit(channel, ccp->fan_cnct))
			अवरोध;

		चयन (attr) अणु
		हाल hwmon_fan_input:
			वापस 0444;
		हाल hwmon_fan_label:
			वापस 0444;
		हाल hwmon_fan_target:
			वापस 0644;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_pwm:
		अगर (!test_bit(channel, ccp->fan_cnct))
			अवरोध;

		चयन (attr) अणु
		हाल hwmon_pwm_input:
			वापस 0644;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
			वापस 0444;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops ccp_hwmon_ops = अणु
	.is_visible = ccp_is_visible,
	.पढ़ो = ccp_पढ़ो,
	.पढ़ो_string = ccp_पढ़ो_string,
	.ग_लिखो = ccp_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *ccp_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT
			   ),
	HWMON_CHANNEL_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_LABEL | HWMON_F_TARGET,
			   HWMON_F_INPUT | HWMON_F_LABEL | HWMON_F_TARGET,
			   HWMON_F_INPUT | HWMON_F_LABEL | HWMON_F_TARGET,
			   HWMON_F_INPUT | HWMON_F_LABEL | HWMON_F_TARGET,
			   HWMON_F_INPUT | HWMON_F_LABEL | HWMON_F_TARGET,
			   HWMON_F_INPUT | HWMON_F_LABEL | HWMON_F_TARGET
			   ),
	HWMON_CHANNEL_INFO(pwm,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT
			   ),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT
			   ),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info ccp_chip_info = अणु
	.ops = &ccp_hwmon_ops,
	.info = ccp_info,
पूर्ण;

/* पढ़ो fan connection status and set labels */
अटल पूर्णांक get_fan_cnct(काष्ठा ccp_device *ccp)
अणु
	पूर्णांक channel;
	पूर्णांक mode;
	पूर्णांक ret;

	ret = send_usb_cmd(ccp, CTL_GET_FAN_CNCT, 0, 0, 0);
	अगर (ret)
		वापस ret;

	क्रम (channel = 0; channel < NUM_FANS; channel++) अणु
		mode = ccp->buffer[channel + 1];
		अगर (mode == 0)
			जारी;

		set_bit(channel, ccp->fan_cnct);
		ccp->target[channel] = -ENODATA;

		चयन (mode) अणु
		हाल 1:
			scnम_लिखो(ccp->fan_label[channel], LABEL_LENGTH,
				  "fan%d 3pin", channel + 1);
			अवरोध;
		हाल 2:
			scnम_लिखो(ccp->fan_label[channel], LABEL_LENGTH,
				  "fan%d 4pin", channel + 1);
			अवरोध;
		शेष:
			scnम_लिखो(ccp->fan_label[channel], LABEL_LENGTH,
				  "fan%d other", channel + 1);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* पढ़ो temp sensor connection status */
अटल पूर्णांक get_temp_cnct(काष्ठा ccp_device *ccp)
अणु
	पूर्णांक channel;
	पूर्णांक mode;
	पूर्णांक ret;

	ret = send_usb_cmd(ccp, CTL_GET_TMP_CNCT, 0, 0, 0);
	अगर (ret)
		वापस ret;

	क्रम (channel = 0; channel < NUM_TEMP_SENSORS; channel++) अणु
		mode = ccp->buffer[channel + 1];
		अगर (mode == 0)
			जारी;

		set_bit(channel, ccp->temp_cnct);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा ccp_device *ccp;
	पूर्णांक ret;

	ccp = devm_kzalloc(&hdev->dev, माप(*ccp), GFP_KERNEL);
	अगर (!ccp)
		वापस -ENOMEM;

	ccp->buffer = devm_kदो_स्मृति(&hdev->dev, OUT_BUFFER_SIZE, GFP_KERNEL);
	अगर (!ccp->buffer)
		वापस -ENOMEM;

	ret = hid_parse(hdev);
	अगर (ret)
		वापस ret;

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	अगर (ret)
		वापस ret;

	ret = hid_hw_खोलो(hdev);
	अगर (ret)
		जाओ out_hw_stop;

	ccp->hdev = hdev;
	hid_set_drvdata(hdev, ccp);
	mutex_init(&ccp->mutex);
	init_completion(&ccp->रुको_input_report);

	hid_device_io_start(hdev);

	/* temp and fan connection status only updates when device is घातered on */
	ret = get_temp_cnct(ccp);
	अगर (ret)
		जाओ out_hw_बंद;

	ret = get_fan_cnct(ccp);
	अगर (ret)
		जाओ out_hw_बंद;
	ccp->hwmon_dev = hwmon_device_रेजिस्टर_with_info(&hdev->dev, "corsaircpro",
							 ccp, &ccp_chip_info, 0);
	अगर (IS_ERR(ccp->hwmon_dev)) अणु
		ret = PTR_ERR(ccp->hwmon_dev);
		जाओ out_hw_बंद;
	पूर्ण

	वापस 0;

out_hw_बंद:
	hid_hw_बंद(hdev);
out_hw_stop:
	hid_hw_stop(hdev);
	वापस ret;
पूर्ण

अटल व्योम ccp_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा ccp_device *ccp = hid_get_drvdata(hdev);

	hwmon_device_unरेजिस्टर(ccp->hwmon_dev);
	hid_hw_बंद(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id ccp_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CORSAIR, USB_PRODUCT_ID_CORSAIR_COMMANDERPRO) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CORSAIR, USB_PRODUCT_ID_CORSAIR_1000D) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा hid_driver ccp_driver = अणु
	.name = "corsair-cpro",
	.id_table = ccp_devices,
	.probe = ccp_probe,
	.हटाओ = ccp_हटाओ,
	.raw_event = ccp_raw_event,
पूर्ण;

MODULE_DEVICE_TABLE(hid, ccp_devices);
MODULE_LICENSE("GPL");

अटल पूर्णांक __init ccp_init(व्योम)
अणु
	वापस hid_रेजिस्टर_driver(&ccp_driver);
पूर्ण

अटल व्योम __निकास ccp_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&ccp_driver);
पूर्ण

/*
 * When compiling this driver as built-in, hwmon initcalls will get called beक्रमe the
 * hid driver and this driver would fail to रेजिस्टर. late_initcall solves this.
 */
late_initcall(ccp_init);
module_निकास(ccp_निकास);
