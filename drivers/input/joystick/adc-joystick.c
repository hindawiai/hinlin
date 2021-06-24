<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Input driver क्रम joysticks connected over ADC.
 * Copyright (c) 2019-2020 Artur Rojek <contact@artur-rojek.eu>
 */
#समावेश <linux/प्रकार.स>
#समावेश <linux/input.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

#समावेश <यंत्र/unaligned.h>

काष्ठा adc_joystick_axis अणु
	u32 code;
	s32 range[2];
	s32 fuzz;
	s32 flat;
पूर्ण;

काष्ठा adc_joystick अणु
	काष्ठा input_dev *input;
	काष्ठा iio_cb_buffer *buffer;
	काष्ठा adc_joystick_axis *axes;
	काष्ठा iio_channel *chans;
	पूर्णांक num_chans;
पूर्ण;

अटल पूर्णांक adc_joystick_handle(स्थिर व्योम *data, व्योम *निजी)
अणु
	काष्ठा adc_joystick *joy = निजी;
	क्रमागत iio_endian endianness;
	पूर्णांक bytes, msb, val, idx, i;
	स्थिर u16 *data_u16;
	bool sign;

	bytes = joy->chans[0].channel->scan_type.storagebits >> 3;

	क्रम (i = 0; i < joy->num_chans; ++i) अणु
		idx = joy->chans[i].channel->scan_index;
		endianness = joy->chans[i].channel->scan_type.endianness;
		msb = joy->chans[i].channel->scan_type.realbits - 1;
		sign = छोटे(joy->chans[i].channel->scan_type.sign) == 's';

		चयन (bytes) अणु
		हाल 1:
			val = ((स्थिर u8 *)data)[idx];
			अवरोध;
		हाल 2:
			data_u16 = (स्थिर u16 *)data + idx;

			/*
			 * Data is aligned to the sample size by IIO core.
			 * Call `get_unaligned_xe16` to hide type casting.
			 */
			अगर (endianness == IIO_BE)
				val = get_unaligned_be16(data_u16);
			अन्यथा अगर (endianness == IIO_LE)
				val = get_unaligned_le16(data_u16);
			अन्यथा /* IIO_CPU */
				val = *data_u16;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		val >>= joy->chans[i].channel->scan_type.shअगरt;
		अगर (sign)
			val = sign_extend32(val, msb);
		अन्यथा
			val &= GENMASK(msb, 0);
		input_report_असल(joy->input, joy->axes[i].code, val);
	पूर्ण

	input_sync(joy->input);

	वापस 0;
पूर्ण

अटल पूर्णांक adc_joystick_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा adc_joystick *joy = input_get_drvdata(dev);
	काष्ठा device *devp = &dev->dev;
	पूर्णांक ret;

	ret = iio_channel_start_all_cb(joy->buffer);
	अगर (ret)
		dev_err(devp, "Unable to start callback buffer: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम adc_joystick_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा adc_joystick *joy = input_get_drvdata(dev);

	iio_channel_stop_all_cb(joy->buffer);
पूर्ण

अटल व्योम adc_joystick_cleanup(व्योम *data)
अणु
	iio_channel_release_all_cb(data);
पूर्ण

अटल पूर्णांक adc_joystick_set_axes(काष्ठा device *dev, काष्ठा adc_joystick *joy)
अणु
	काष्ठा adc_joystick_axis *axes;
	काष्ठा fwnode_handle *child;
	पूर्णांक num_axes, error, i;

	num_axes = device_get_child_node_count(dev);
	अगर (!num_axes) अणु
		dev_err(dev, "Unable to find child nodes\n");
		वापस -EINVAL;
	पूर्ण

	अगर (num_axes != joy->num_chans) अणु
		dev_err(dev, "Got %d child nodes for %d channels\n",
			num_axes, joy->num_chans);
		वापस -EINVAL;
	पूर्ण

	axes = devm_kदो_स्मृति_array(dev, num_axes, माप(*axes), GFP_KERNEL);
	अगर (!axes)
		वापस -ENOMEM;

	device_क्रम_each_child_node(dev, child) अणु
		error = fwnode_property_पढ़ो_u32(child, "reg", &i);
		अगर (error) अणु
			dev_err(dev, "reg invalid or missing\n");
			जाओ err_fwnode_put;
		पूर्ण

		अगर (i >= num_axes) अणु
			error = -EINVAL;
			dev_err(dev, "No matching axis for reg %d\n", i);
			जाओ err_fwnode_put;
		पूर्ण

		error = fwnode_property_पढ़ो_u32(child, "linux,code",
						 &axes[i].code);
		अगर (error) अणु
			dev_err(dev, "linux,code invalid or missing\n");
			जाओ err_fwnode_put;
		पूर्ण

		error = fwnode_property_पढ़ो_u32_array(child, "abs-range",
						       axes[i].range, 2);
		अगर (error) अणु
			dev_err(dev, "abs-range invalid or missing\n");
			जाओ err_fwnode_put;
		पूर्ण

		fwnode_property_पढ़ो_u32(child, "abs-fuzz", &axes[i].fuzz);
		fwnode_property_पढ़ो_u32(child, "abs-flat", &axes[i].flat);

		input_set_असल_params(joy->input, axes[i].code,
				     axes[i].range[0], axes[i].range[1],
				     axes[i].fuzz, axes[i].flat);
		input_set_capability(joy->input, EV_ABS, axes[i].code);
	पूर्ण

	joy->axes = axes;

	वापस 0;

err_fwnode_put:
	fwnode_handle_put(child);
	वापस error;
पूर्ण

अटल पूर्णांक adc_joystick_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा adc_joystick *joy;
	काष्ठा input_dev *input;
	पूर्णांक error;
	पूर्णांक bits;
	पूर्णांक i;

	joy = devm_kzalloc(dev, माप(*joy), GFP_KERNEL);
	अगर (!joy)
		वापस -ENOMEM;

	joy->chans = devm_iio_channel_get_all(dev);
	अगर (IS_ERR(joy->chans)) अणु
		error = PTR_ERR(joy->chans);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Unable to get IIO channels");
		वापस error;
	पूर्ण

	/* Count how many channels we got. शून्य terminated. */
	क्रम (i = 0; joy->chans[i].indio_dev; i++) अणु
		bits = joy->chans[i].channel->scan_type.storagebits;
		अगर (!bits || bits > 16) अणु
			dev_err(dev, "Unsupported channel storage size\n");
			वापस -EINVAL;
		पूर्ण
		अगर (bits != joy->chans[0].channel->scan_type.storagebits) अणु
			dev_err(dev, "Channels must have equal storage size\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	joy->num_chans = i;

	input = devm_input_allocate_device(dev);
	अगर (!input) अणु
		dev_err(dev, "Unable to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	joy->input = input;
	input->name = pdev->name;
	input->id.bustype = BUS_HOST;
	input->खोलो = adc_joystick_खोलो;
	input->बंद = adc_joystick_बंद;

	error = adc_joystick_set_axes(dev, joy);
	अगर (error)
		वापस error;

	input_set_drvdata(input, joy);
	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "Unable to register input device\n");
		वापस error;
	पूर्ण

	joy->buffer = iio_channel_get_all_cb(dev, adc_joystick_handle, joy);
	अगर (IS_ERR(joy->buffer)) अणु
		dev_err(dev, "Unable to allocate callback buffer\n");
		वापस PTR_ERR(joy->buffer);
	पूर्ण

	error = devm_add_action_or_reset(dev, adc_joystick_cleanup, joy->buffer);
	अगर (error)  अणु
		dev_err(dev, "Unable to add action\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id adc_joystick_of_match[] = अणु
	अणु .compatible = "adc-joystick", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adc_joystick_of_match);

अटल काष्ठा platक्रमm_driver adc_joystick_driver = अणु
	.driver = अणु
		.name = "adc-joystick",
		.of_match_table = adc_joystick_of_match,
	पूर्ण,
	.probe = adc_joystick_probe,
पूर्ण;
module_platक्रमm_driver(adc_joystick_driver);

MODULE_DESCRIPTION("Input driver for joysticks connected over ADC");
MODULE_AUTHOR("Artur Rojek <contact@artur-rojek.eu>");
MODULE_LICENSE("GPL");
