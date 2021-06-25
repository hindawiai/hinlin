<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम Ntrig/Microsoft Touchscreens over SPI
 *
 *  Copyright (c) 2016 Red Hat Inc.
 */


#समावेश <linux/kernel.h>

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/acpi.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा SURFACE3_PACKET_SIZE	264

#घोषणा SURFACE3_REPORT_TOUCH	0xd2
#घोषणा SURFACE3_REPORT_PEN	0x16

काष्ठा surface3_ts_data अणु
	काष्ठा spi_device *spi;
	काष्ठा gpio_desc *gpiod_rst[2];
	काष्ठा input_dev *input_dev;
	काष्ठा input_dev *pen_input_dev;
	पूर्णांक pen_tool;

	u8 rd_buf[SURFACE3_PACKET_SIZE]		____cacheline_aligned;
पूर्ण;

काष्ठा surface3_ts_data_finger अणु
	u8 status;
	__le16 tracking_id;
	__le16 x;
	__le16 cx;
	__le16 y;
	__le16 cy;
	__le16 width;
	__le16 height;
	u32 padding;
पूर्ण __packed;

काष्ठा surface3_ts_data_pen अणु
	u8 status;
	__le16 x;
	__le16 y;
	__le16 pressure;
	u8 padding;
पूर्ण __packed;

अटल पूर्णांक surface3_spi_पढ़ो(काष्ठा surface3_ts_data *ts_data)
अणु
	काष्ठा spi_device *spi = ts_data->spi;

	स_रखो(ts_data->rd_buf, 0, माप(ts_data->rd_buf));
	वापस spi_पढ़ो(spi, ts_data->rd_buf, माप(ts_data->rd_buf));
पूर्ण

अटल व्योम surface3_spi_report_touch(काष्ठा surface3_ts_data *ts_data,
				   काष्ठा surface3_ts_data_finger *finger)
अणु
	पूर्णांक st = finger->status & 0x01;
	पूर्णांक slot;

	slot = input_mt_get_slot_by_key(ts_data->input_dev,
				get_unaligned_le16(&finger->tracking_id));
	अगर (slot < 0)
		वापस;

	input_mt_slot(ts_data->input_dev, slot);
	input_mt_report_slot_state(ts_data->input_dev, MT_TOOL_FINGER, st);
	अगर (st) अणु
		input_report_असल(ts_data->input_dev,
				 ABS_MT_POSITION_X,
				 get_unaligned_le16(&finger->x));
		input_report_असल(ts_data->input_dev,
				 ABS_MT_POSITION_Y,
				 get_unaligned_le16(&finger->y));
		input_report_असल(ts_data->input_dev,
				 ABS_MT_WIDTH_MAJOR,
				 get_unaligned_le16(&finger->width));
		input_report_असल(ts_data->input_dev,
				 ABS_MT_WIDTH_MINOR,
				 get_unaligned_le16(&finger->height));
	पूर्ण
पूर्ण

अटल व्योम surface3_spi_process_touch(काष्ठा surface3_ts_data *ts_data, u8 *data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 13; i++) अणु
		काष्ठा surface3_ts_data_finger *finger;

		finger = (काष्ठा surface3_ts_data_finger *)&data[17 +
				i * माप(काष्ठा surface3_ts_data_finger)];

		/*
		 * When bit 5 of status is 1, it marks the end of the report:
		 * - touch present: 0xe7
		 * - touch released: 0xe4
		 * - nothing valuable: 0xff
		 */
		अगर (finger->status & 0x10)
			अवरोध;

		surface3_spi_report_touch(ts_data, finger);
	पूर्ण

	input_mt_sync_frame(ts_data->input_dev);
	input_sync(ts_data->input_dev);
पूर्ण

अटल व्योम surface3_spi_report_pen(काष्ठा surface3_ts_data *ts_data,
				    काष्ठा surface3_ts_data_pen *pen)
अणु
	काष्ठा input_dev *dev = ts_data->pen_input_dev;
	पूर्णांक st = pen->status;
	पूर्णांक prox = st & 0x01;
	पूर्णांक rubber = st & 0x18;
	पूर्णांक tool = (prox && rubber) ? BTN_TOOL_RUBBER : BTN_TOOL_PEN;

	/* fake proximity out to चयन tools */
	अगर (ts_data->pen_tool != tool) अणु
		input_report_key(dev, ts_data->pen_tool, 0);
		input_sync(dev);
		ts_data->pen_tool = tool;
	पूर्ण

	input_report_key(dev, BTN_TOUCH, st & 0x12);

	input_report_key(dev, ts_data->pen_tool, prox);

	अगर (st) अणु
		input_report_key(dev,
				 BTN_STYLUS,
				 st & 0x04);

		input_report_असल(dev,
				 ABS_X,
				 get_unaligned_le16(&pen->x));
		input_report_असल(dev,
				 ABS_Y,
				 get_unaligned_le16(&pen->y));
		input_report_असल(dev,
				 ABS_PRESSURE,
				 get_unaligned_le16(&pen->pressure));
	पूर्ण
पूर्ण

अटल व्योम surface3_spi_process_pen(काष्ठा surface3_ts_data *ts_data, u8 *data)
अणु
	काष्ठा surface3_ts_data_pen *pen;

	pen = (काष्ठा surface3_ts_data_pen *)&data[15];

	surface3_spi_report_pen(ts_data, pen);
	input_sync(ts_data->pen_input_dev);
पूर्ण

अटल व्योम surface3_spi_process(काष्ठा surface3_ts_data *ts_data)
अणु
	अटल स्थिर अक्षर header[] = अणु
		0xff, 0xff, 0xff, 0xff, 0xa5, 0x5a, 0xe7, 0x7e, 0x01
	पूर्ण;
	u8 *data = ts_data->rd_buf;

	अगर (स_भेद(header, data, माप(header)))
		dev_err(&ts_data->spi->dev,
			"%s header error: %*ph, ignoring...\n",
			__func__, (पूर्णांक)माप(header), data);

	चयन (data[9]) अणु
	हाल SURFACE3_REPORT_TOUCH:
		surface3_spi_process_touch(ts_data, data);
		अवरोध;
	हाल SURFACE3_REPORT_PEN:
		surface3_spi_process_pen(ts_data, data);
		अवरोध;
	शेष:
		dev_err(&ts_data->spi->dev,
			"%s unknown packet type: %x, ignoring...\n",
			__func__, data[9]);
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t surface3_spi_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा surface3_ts_data *data = dev_id;

	अगर (surface3_spi_पढ़ो(data))
		वापस IRQ_HANDLED;

	dev_dbg(&data->spi->dev, "%s received -> %*ph\n",
		__func__, SURFACE3_PACKET_SIZE, data->rd_buf);
	surface3_spi_process(data);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम surface3_spi_घातer(काष्ठा surface3_ts_data *data, bool on)
अणु
	gpiod_set_value(data->gpiod_rst[0], on);
	gpiod_set_value(data->gpiod_rst[1], on);
	/* let the device settle a little */
	msleep(20);
पूर्ण

/**
 * surface3_spi_get_gpio_config - Get GPIO config from ACPI/DT
 *
 * @data: surface3_spi_ts_data poपूर्णांकer
 */
अटल पूर्णांक surface3_spi_get_gpio_config(काष्ठा surface3_ts_data *data)
अणु
	पूर्णांक error;
	काष्ठा device *dev;
	काष्ठा gpio_desc *gpiod;
	पूर्णांक i;

	dev = &data->spi->dev;

	/* Get the reset lines GPIO pin number */
	क्रम (i = 0; i < 2; i++) अणु
		gpiod = devm_gpiod_get_index(dev, शून्य, i, GPIOD_OUT_LOW);
		अगर (IS_ERR(gpiod)) अणु
			error = PTR_ERR(gpiod);
			अगर (error != -EPROBE_DEFER)
				dev_err(dev,
					"Failed to get power GPIO %d: %d\n",
					i,
					error);
			वापस error;
		पूर्ण

		data->gpiod_rst[i] = gpiod;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक surface3_spi_create_touch_input(काष्ठा surface3_ts_data *data)
अणु
	काष्ठा input_dev *input;
	पूर्णांक error;

	input = devm_input_allocate_device(&data->spi->dev);
	अगर (!input)
		वापस -ENOMEM;

	data->input_dev = input;

	input_set_असल_params(input, ABS_MT_POSITION_X, 0, 9600, 0, 0);
	input_असल_set_res(input, ABS_MT_POSITION_X, 40);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0, 7200, 0, 0);
	input_असल_set_res(input, ABS_MT_POSITION_Y, 48);
	input_set_असल_params(input, ABS_MT_WIDTH_MAJOR, 0, 1024, 0, 0);
	input_set_असल_params(input, ABS_MT_WIDTH_MINOR, 0, 1024, 0, 0);
	input_mt_init_slots(input, 10, INPUT_MT_सूचीECT);

	input->name = "Surface3 SPI Capacitive TouchScreen";
	input->phys = "input/ts";
	input->id.bustype = BUS_SPI;
	input->id.venकरोr = 0x045e;	/* Microsoft */
	input->id.product = 0x0001;
	input->id.version = 0x0000;

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&data->spi->dev,
			"Failed to register input device: %d", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक surface3_spi_create_pen_input(काष्ठा surface3_ts_data *data)
अणु
	काष्ठा input_dev *input;
	पूर्णांक error;

	input = devm_input_allocate_device(&data->spi->dev);
	अगर (!input)
		वापस -ENOMEM;

	data->pen_input_dev = input;
	data->pen_tool = BTN_TOOL_PEN;

	__set_bit(INPUT_PROP_सूचीECT, input->propbit);
	__set_bit(INPUT_PROP_POINTER, input->propbit);
	input_set_असल_params(input, ABS_X, 0, 9600, 0, 0);
	input_असल_set_res(input, ABS_X, 40);
	input_set_असल_params(input, ABS_Y, 0, 7200, 0, 0);
	input_असल_set_res(input, ABS_Y, 48);
	input_set_असल_params(input, ABS_PRESSURE, 0, 1024, 0, 0);
	input_set_capability(input, EV_KEY, BTN_TOUCH);
	input_set_capability(input, EV_KEY, BTN_STYLUS);
	input_set_capability(input, EV_KEY, BTN_TOOL_PEN);
	input_set_capability(input, EV_KEY, BTN_TOOL_RUBBER);

	input->name = "Surface3 SPI Pen Input";
	input->phys = "input/ts";
	input->id.bustype = BUS_SPI;
	input->id.venकरोr = 0x045e;     /* Microsoft */
	input->id.product = 0x0002;
	input->id.version = 0x0000;

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&data->spi->dev,
			"Failed to register input device: %d", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक surface3_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा surface3_ts_data *data;
	पूर्णांक error;

	/* Set up SPI*/
	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_0;
	error = spi_setup(spi);
	अगर (error)
		वापस error;

	data = devm_kzalloc(&spi->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->spi = spi;
	spi_set_drvdata(spi, data);

	error = surface3_spi_get_gpio_config(data);
	अगर (error)
		वापस error;

	surface3_spi_घातer(data, true);
	surface3_spi_घातer(data, false);
	surface3_spi_घातer(data, true);

	error = surface3_spi_create_touch_input(data);
	अगर (error)
		वापस error;

	error = surface3_spi_create_pen_input(data);
	अगर (error)
		वापस error;

	error = devm_request_thपढ़ोed_irq(&spi->dev, spi->irq,
					  शून्य, surface3_spi_irq_handler,
					  IRQF_ONESHOT,
					  "Surface3-irq", data);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused surface3_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा surface3_ts_data *data = spi_get_drvdata(spi);

	disable_irq(data->spi->irq);

	surface3_spi_घातer(data, false);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused surface3_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा surface3_ts_data *data = spi_get_drvdata(spi);

	surface3_spi_घातer(data, true);

	enable_irq(data->spi->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(surface3_spi_pm_ops,
			 surface3_spi_suspend,
			 surface3_spi_resume);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id surface3_spi_acpi_match[] = अणु
	अणु "MSHW0037", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, surface3_spi_acpi_match);
#पूर्ण_अगर

अटल काष्ठा spi_driver surface3_spi_driver = अणु
	.driver = अणु
		.name	= "Surface3-spi",
		.acpi_match_table = ACPI_PTR(surface3_spi_acpi_match),
		.pm = &surface3_spi_pm_ops,
	पूर्ण,
	.probe = surface3_spi_probe,
पूर्ण;

module_spi_driver(surface3_spi_driver);

MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@gmail.com>");
MODULE_DESCRIPTION("Surface 3 SPI touchscreen driver");
MODULE_LICENSE("GPL v2");
