<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम I2C connected EETI EXC3000 multiple touch controller
 *
 * Copyright (C) 2017 Ahmet Inan <inan@distec.de>
 *
 * minimal implementation based on egalax_ts.c and egalax_i2c.c
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/sizes.h>
#समावेश <linux/समयr.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा EXC3000_NUM_SLOTS		10
#घोषणा EXC3000_SLOTS_PER_FRAME		5
#घोषणा EXC3000_LEN_FRAME		66
#घोषणा EXC3000_LEN_VENDOR_REQUEST	68
#घोषणा EXC3000_LEN_POINT		10

#घोषणा EXC3000_LEN_MODEL_NAME		16
#घोषणा EXC3000_LEN_FW_VERSION		16

#घोषणा EXC3000_VENDOR_EVENT		0x03
#घोषणा EXC3000_MT1_EVENT		0x06
#घोषणा EXC3000_MT2_EVENT		0x18

#घोषणा EXC3000_TIMEOUT_MS		100

#घोषणा EXC3000_RESET_MS		10
#घोषणा EXC3000_READY_MS		100

अटल स्थिर काष्ठा i2c_device_id exc3000_id[];

काष्ठा eeti_dev_info अणु
	स्थिर अक्षर *name;
	पूर्णांक max_xy;
पूर्ण;

क्रमागत eeti_dev_id अणु
	EETI_EXC3000,
	EETI_EXC80H60,
	EETI_EXC80H84,
पूर्ण;

अटल काष्ठा eeti_dev_info exc3000_info[] = अणु
	[EETI_EXC3000] = अणु
		.name = "EETI EXC3000 Touch Screen",
		.max_xy = SZ_4K - 1,
	पूर्ण,
	[EETI_EXC80H60] = अणु
		.name = "EETI EXC80H60 Touch Screen",
		.max_xy = SZ_16K - 1,
	पूर्ण,
	[EETI_EXC80H84] = अणु
		.name = "EETI EXC80H84 Touch Screen",
		.max_xy = SZ_16K - 1,
	पूर्ण,
पूर्ण;

काष्ठा exc3000_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा eeti_dev_info *info;
	काष्ठा input_dev *input;
	काष्ठा touchscreen_properties prop;
	काष्ठा gpio_desc *reset;
	काष्ठा समयr_list समयr;
	u8 buf[2 * EXC3000_LEN_FRAME];
	काष्ठा completion रुको_event;
	काष्ठा mutex query_lock;
पूर्ण;

अटल व्योम exc3000_report_slots(काष्ठा input_dev *input,
				 काष्ठा touchscreen_properties *prop,
				 स्थिर u8 *buf, पूर्णांक num)
अणु
	क्रम (; num--; buf += EXC3000_LEN_POINT) अणु
		अगर (buf[0] & BIT(0)) अणु
			input_mt_slot(input, buf[1]);
			input_mt_report_slot_state(input, MT_TOOL_FINGER, true);
			touchscreen_report_pos(input, prop,
					       get_unaligned_le16(buf + 2),
					       get_unaligned_le16(buf + 4),
					       true);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम exc3000_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा exc3000_data *data = from_समयr(data, t, समयr);

	input_mt_sync_frame(data->input);
	input_sync(data->input);
पूर्ण

अटल अंतरभूत व्योम exc3000_schedule_समयr(काष्ठा exc3000_data *data)
अणु
	mod_समयr(&data->समयr, jअगरfies + msecs_to_jअगरfies(EXC3000_TIMEOUT_MS));
पूर्ण

अटल पूर्णांक exc3000_पढ़ो_frame(काष्ठा exc3000_data *data, u8 *buf)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	ret = i2c_master_send(client, "'", 2);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != 2)
		वापस -EIO;

	ret = i2c_master_recv(client, buf, EXC3000_LEN_FRAME);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != EXC3000_LEN_FRAME)
		वापस -EIO;

	अगर (get_unaligned_le16(buf) != EXC3000_LEN_FRAME)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक exc3000_handle_mt_event(काष्ठा exc3000_data *data)
अणु
	काष्ठा input_dev *input = data->input;
	पूर्णांक ret, total_slots;
	u8 *buf = data->buf;

	total_slots = buf[3];
	अगर (!total_slots || total_slots > EXC3000_NUM_SLOTS) अणु
		ret = -EINVAL;
		जाओ out_fail;
	पूर्ण

	अगर (total_slots > EXC3000_SLOTS_PER_FRAME) अणु
		/* Read 2nd frame to get the rest of the contacts. */
		ret = exc3000_पढ़ो_frame(data, buf + EXC3000_LEN_FRAME);
		अगर (ret)
			जाओ out_fail;

		/* 2nd chunk must have number of contacts set to 0. */
		अगर (buf[EXC3000_LEN_FRAME + 3] != 0) अणु
			ret = -EINVAL;
			जाओ out_fail;
		पूर्ण
	पूर्ण

	/*
	 * We पढ़ो full state successfully, no contacts will be "stuck".
	 */
	del_समयr_sync(&data->समयr);

	जबतक (total_slots > 0) अणु
		पूर्णांक slots = min(total_slots, EXC3000_SLOTS_PER_FRAME);

		exc3000_report_slots(input, &data->prop, buf + 4, slots);
		total_slots -= slots;
		buf += EXC3000_LEN_FRAME;
	पूर्ण

	input_mt_sync_frame(input);
	input_sync(input);

	वापस 0;

out_fail:
	/* Schedule a समयr to release "stuck" contacts */
	exc3000_schedule_समयr(data);

	वापस ret;
पूर्ण

अटल irqवापस_t exc3000_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा exc3000_data *data = dev_id;
	u8 *buf = data->buf;
	पूर्णांक ret;

	ret = exc3000_पढ़ो_frame(data, buf);
	अगर (ret) अणु
		/* Schedule a समयr to release "stuck" contacts */
		exc3000_schedule_समयr(data);
		जाओ out;
	पूर्ण

	चयन (buf[2]) अणु
	हाल EXC3000_VENDOR_EVENT:
		complete(&data->रुको_event);
		अवरोध;

	हाल EXC3000_MT1_EVENT:
	हाल EXC3000_MT2_EVENT:
		exc3000_handle_mt_event(data);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक exc3000_venकरोr_data_request(काष्ठा exc3000_data *data, u8 *request,
				       u8 request_len, u8 *response, पूर्णांक समयout)
अणु
	u8 buf[EXC3000_LEN_VENDOR_REQUEST] = अणु 0x67, 0x00, 0x42, 0x00, 0x03 पूर्ण;
	पूर्णांक ret;

	mutex_lock(&data->query_lock);

	reinit_completion(&data->रुको_event);

	buf[5] = request_len;
	स_नकल(&buf[6], request, request_len);

	ret = i2c_master_send(data->client, buf, EXC3000_LEN_VENDOR_REQUEST);
	अगर (ret < 0)
		जाओ out_unlock;

	अगर (response) अणु
		ret = रुको_क्रम_completion_समयout(&data->रुको_event,
						  समयout * HZ);
		अगर (ret <= 0) अणु
			ret = -ETIMEDOUT;
			जाओ out_unlock;
		पूर्ण

		अगर (data->buf[3] >= EXC3000_LEN_FRAME) अणु
			ret = -ENOSPC;
			जाओ out_unlock;
		पूर्ण

		स_नकल(response, &data->buf[4], data->buf[3]);
		ret = data->buf[3];
	पूर्ण

out_unlock:
	mutex_unlock(&data->query_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार fw_version_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा exc3000_data *data = i2c_get_clientdata(client);
	u8 response[EXC3000_LEN_FRAME];
	पूर्णांक ret;

	/* query bootloader info */
	ret = exc3000_venकरोr_data_request(data,
					  (u8[])अणु0x39, 0x02पूर्ण, 2, response, 1);
	अगर (ret < 0)
		वापस ret;

	/*
	 * If the bootloader version is non-zero then the device is in
	 * bootloader mode and won't answer a query क्रम the application FW
	 * version, so we just use the bootloader version info.
	 */
	अगर (response[2] || response[3])
		वापस प्र_लिखो(buf, "%d.%d\n", response[2], response[3]);

	ret = exc3000_venकरोr_data_request(data, (u8[])अणु'D'पूर्ण, 1, response, 1);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%s\n", &response[1]);
पूर्ण
अटल DEVICE_ATTR_RO(fw_version);

अटल sमाप_प्रकार model_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा exc3000_data *data = i2c_get_clientdata(client);
	u8 response[EXC3000_LEN_FRAME];
	पूर्णांक ret;

	ret = exc3000_venकरोr_data_request(data, (u8[])अणु'E'पूर्ण, 1, response, 1);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%s\n", &response[1]);
पूर्ण
अटल DEVICE_ATTR_RO(model);

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा exc3000_data *data = i2c_get_clientdata(client);
	u8 response[EXC3000_LEN_FRAME];
	पूर्णांक ret;

	ret = exc3000_venकरोr_data_request(data, (u8[])अणु'F'पूर्ण, 1, response, 1);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%s\n", &response[1]);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल काष्ठा attribute *sysfs_attrs[] = अणु
	&dev_attr_fw_version.attr,
	&dev_attr_model.attr,
	&dev_attr_type.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group exc3000_attribute_group = अणु
	.attrs = sysfs_attrs
पूर्ण;

अटल पूर्णांक exc3000_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा exc3000_data *data;
	काष्ठा input_dev *input;
	पूर्णांक error, max_xy, retry;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	data->info = device_get_match_data(&client->dev);
	अगर (!data->info) अणु
		क्रमागत eeti_dev_id eeti_dev_id =
			i2c_match_id(exc3000_id, client)->driver_data;
		data->info = &exc3000_info[eeti_dev_id];
	पूर्ण
	समयr_setup(&data->समयr, exc3000_समयr, 0);
	init_completion(&data->रुको_event);
	mutex_init(&data->query_lock);

	data->reset = devm_gpiod_get_optional(&client->dev, "reset",
					      GPIOD_OUT_HIGH);
	अगर (IS_ERR(data->reset))
		वापस PTR_ERR(data->reset);

	अगर (data->reset) अणु
		msleep(EXC3000_RESET_MS);
		gpiod_set_value_cansleep(data->reset, 0);
		msleep(EXC3000_READY_MS);
	पूर्ण

	input = devm_input_allocate_device(&client->dev);
	अगर (!input)
		वापस -ENOMEM;

	data->input = input;
	input_set_drvdata(input, data);

	input->name = data->info->name;
	input->id.bustype = BUS_I2C;

	max_xy = data->info->max_xy;
	input_set_असल_params(input, ABS_MT_POSITION_X, 0, max_xy, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0, max_xy, 0, 0);

	touchscreen_parse_properties(input, true, &data->prop);

	error = input_mt_init_slots(input, EXC3000_NUM_SLOTS,
				    INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);
	अगर (error)
		वापस error;

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, exc3000_पूर्णांकerrupt, IRQF_ONESHOT,
					  client->name, data);
	अगर (error)
		वापस error;

	/*
	 * IतऑC करोes not have built-in recovery, so retry on failure. This
	 * ensures, that the device probe will not fail क्रम temporary issues
	 * on the bus.  This is not needed क्रम the sysfs calls (userspace
	 * will receive the error code and can start another query) and
	 * cannot be करोne क्रम touch events (but that only means loosing one
	 * or two touch events anyways).
	 */
	क्रम (retry = 0; retry < 3; retry++) अणु
		u8 response[EXC3000_LEN_FRAME];

		error = exc3000_venकरोr_data_request(data, (u8[])अणु'E'पूर्ण, 1,
						    response, 1);
		अगर (error > 0) अणु
			dev_dbg(&client->dev, "TS Model: %s", &response[1]);
			error = 0;
			अवरोध;
		पूर्ण
		dev_warn(&client->dev, "Retry %d get EETI EXC3000 model: %d\n",
			 retry + 1, error);
	पूर्ण

	अगर (error)
		वापस error;

	i2c_set_clientdata(client, data);

	error = devm_device_add_group(&client->dev, &exc3000_attribute_group);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id exc3000_id[] = अणु
	अणु "exc3000", EETI_EXC3000 पूर्ण,
	अणु "exc80h60", EETI_EXC80H60 पूर्ण,
	अणु "exc80h84", EETI_EXC80H84 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, exc3000_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id exc3000_of_match[] = अणु
	अणु .compatible = "eeti,exc3000", .data = &exc3000_info[EETI_EXC3000] पूर्ण,
	अणु .compatible = "eeti,exc80h60", .data = &exc3000_info[EETI_EXC80H60] पूर्ण,
	अणु .compatible = "eeti,exc80h84", .data = &exc3000_info[EETI_EXC80H84] पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, exc3000_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver exc3000_driver = अणु
	.driver = अणु
		.name	= "exc3000",
		.of_match_table = of_match_ptr(exc3000_of_match),
	पूर्ण,
	.id_table	= exc3000_id,
	.probe_new	= exc3000_probe,
पूर्ण;

module_i2c_driver(exc3000_driver);

MODULE_AUTHOR("Ahmet Inan <inan@distec.de>");
MODULE_DESCRIPTION("I2C connected EETI EXC3000 multiple touch controller driver");
MODULE_LICENSE("GPL v2");
