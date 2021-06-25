<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Plantower PMS7003 particulate matter sensor driver
 *
 * Copyright (c) Tomasz Duszynski <tduszyns@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/serdev.h>

#घोषणा PMS7003_DRIVER_NAME "pms7003"

#घोषणा PMS7003_MAGIC 0x424d
/* last 2 data bytes hold frame checksum */
#घोषणा PMS7003_MAX_DATA_LENGTH 28
#घोषणा PMS7003_CHECKSUM_LENGTH 2
#घोषणा PMS7003_PM10_OFFSET 10
#घोषणा PMS7003_PM2P5_OFFSET 8
#घोषणा PMS7003_PM1_OFFSET 6

#घोषणा PMS7003_TIMEOUT msecs_to_jअगरfies(6000)
#घोषणा PMS7003_CMD_LENGTH 7
#घोषणा PMS7003_PM_MAX 1000
#घोषणा PMS7003_PM_MIN 0

क्रमागत अणु
	PM1,
	PM2P5,
	PM10,
पूर्ण;

क्रमागत pms7003_cmd अणु
	CMD_WAKEUP,
	CMD_ENTER_PASSIVE_MODE,
	CMD_READ_PASSIVE,
	CMD_SLEEP,
पूर्ण;

/*
 * commands have following क्रमmat:
 *
 * +------+------+-----+------+-----+-----------+-----------+
 * | 0x42 | 0x4d | cmd | 0x00 | arg | cksum msb | cksum lsb |
 * +------+------+-----+------+-----+-----------+-----------+
 */
अटल स्थिर u8 pms7003_cmd_tbl[][PMS7003_CMD_LENGTH] = अणु
	[CMD_WAKEUP] = अणु 0x42, 0x4d, 0xe4, 0x00, 0x01, 0x01, 0x74 पूर्ण,
	[CMD_ENTER_PASSIVE_MODE] = अणु 0x42, 0x4d, 0xe1, 0x00, 0x00, 0x01, 0x70 पूर्ण,
	[CMD_READ_PASSIVE] = अणु 0x42, 0x4d, 0xe2, 0x00, 0x00, 0x01, 0x71 पूर्ण,
	[CMD_SLEEP] = अणु 0x42, 0x4d, 0xe4, 0x00, 0x00, 0x01, 0x73 पूर्ण,
पूर्ण;

काष्ठा pms7003_frame अणु
	u8 data[PMS7003_MAX_DATA_LENGTH];
	u16 expected_length;
	u16 length;
पूर्ण;

काष्ठा pms7003_state अणु
	काष्ठा serdev_device *serdev;
	काष्ठा pms7003_frame frame;
	काष्ठा completion frame_पढ़ोy;
	काष्ठा mutex lock; /* must be held whenever state माला_लो touched */
	/* Used to स्थिरruct scan to push to the IIO buffer */
	काष्ठा अणु
		u16 data[3]; /* PM1, PM2P5, PM10 */
		s64 ts;
	पूर्ण scan;
पूर्ण;

अटल पूर्णांक pms7003_करो_cmd(काष्ठा pms7003_state *state, क्रमागत pms7003_cmd cmd)
अणु
	पूर्णांक ret;

	ret = serdev_device_ग_लिखो(state->serdev, pms7003_cmd_tbl[cmd],
				  PMS7003_CMD_LENGTH, PMS7003_TIMEOUT);
	अगर (ret < PMS7003_CMD_LENGTH)
		वापस ret < 0 ? ret : -EIO;

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&state->frame_पढ़ोy,
							PMS7003_TIMEOUT);
	अगर (!ret)
		ret = -ETIMEDOUT;

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल u16 pms7003_get_pm(स्थिर u8 *data)
अणु
	वापस clamp_val(get_unaligned_be16(data),
			 PMS7003_PM_MIN, PMS7003_PM_MAX);
पूर्ण

अटल irqवापस_t pms7003_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा pms7003_state *state = iio_priv(indio_dev);
	काष्ठा pms7003_frame *frame = &state->frame;
	पूर्णांक ret;

	mutex_lock(&state->lock);
	ret = pms7003_करो_cmd(state, CMD_READ_PASSIVE);
	अगर (ret) अणु
		mutex_unlock(&state->lock);
		जाओ err;
	पूर्ण

	state->scan.data[PM1] =
		pms7003_get_pm(frame->data + PMS7003_PM1_OFFSET);
	state->scan.data[PM2P5] =
		pms7003_get_pm(frame->data + PMS7003_PM2P5_OFFSET);
	state->scan.data[PM10] =
		pms7003_get_pm(frame->data + PMS7003_PM10_OFFSET);
	mutex_unlock(&state->lock);

	iio_push_to_buffers_with_बारtamp(indio_dev, &state->scan,
					   iio_get_समय_ns(indio_dev));
err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pms7003_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा pms7003_state *state = iio_priv(indio_dev);
	काष्ठा pms7003_frame *frame = &state->frame;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_MASSCONCENTRATION:
			mutex_lock(&state->lock);
			ret = pms7003_करो_cmd(state, CMD_READ_PASSIVE);
			अगर (ret) अणु
				mutex_unlock(&state->lock);
				वापस ret;
			पूर्ण

			*val = pms7003_get_pm(frame->data + chan->address);
			mutex_unlock(&state->lock);

			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info pms7003_info = अणु
	.पढ़ो_raw = pms7003_पढ़ो_raw,
पूर्ण;

#घोषणा PMS7003_CHAN(_index, _mod, _addr) अणु \
	.type = IIO_MASSCONCENTRATION, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_ ## _mod, \
	.address = _addr, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED), \
	.scan_index = _index, \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 10, \
		.storagebits = 16, \
		.endianness = IIO_CPU, \
	पूर्ण, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec pms7003_channels[] = अणु
	PMS7003_CHAN(0, PM1, PMS7003_PM1_OFFSET),
	PMS7003_CHAN(1, PM2P5, PMS7003_PM2P5_OFFSET),
	PMS7003_CHAN(2, PM10, PMS7003_PM10_OFFSET),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल u16 pms7003_calc_checksum(काष्ठा pms7003_frame *frame)
अणु
	u16 checksum = (PMS7003_MAGIC >> 8) + (u8)(PMS7003_MAGIC & 0xff) +
		       (frame->length >> 8) + (u8)frame->length;
	पूर्णांक i;

	क्रम (i = 0; i < frame->length - PMS7003_CHECKSUM_LENGTH; i++)
		checksum += frame->data[i];

	वापस checksum;
पूर्ण

अटल bool pms7003_frame_is_okay(काष्ठा pms7003_frame *frame)
अणु
	पूर्णांक offset = frame->length - PMS7003_CHECKSUM_LENGTH;
	u16 checksum = get_unaligned_be16(frame->data + offset);

	वापस checksum == pms7003_calc_checksum(frame);
पूर्ण

अटल पूर्णांक pms7003_receive_buf(काष्ठा serdev_device *serdev,
			       स्थिर अचिन्हित अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा iio_dev *indio_dev = serdev_device_get_drvdata(serdev);
	काष्ठा pms7003_state *state = iio_priv(indio_dev);
	काष्ठा pms7003_frame *frame = &state->frame;
	पूर्णांक num;

	अगर (!frame->expected_length) अणु
		u16 magic;

		/* रुको क्रम SOF and data length */
		अगर (size < 4)
			वापस 0;

		magic = get_unaligned_be16(buf);
		अगर (magic != PMS7003_MAGIC)
			वापस 2;

		num = get_unaligned_be16(buf + 2);
		अगर (num <= PMS7003_MAX_DATA_LENGTH) अणु
			frame->expected_length = num;
			frame->length = 0;
		पूर्ण

		वापस 4;
	पूर्ण

	num = min(size, (माप_प्रकार)(frame->expected_length - frame->length));
	स_नकल(frame->data + frame->length, buf, num);
	frame->length += num;

	अगर (frame->length == frame->expected_length) अणु
		अगर (pms7003_frame_is_okay(frame))
			complete(&state->frame_पढ़ोy);

		frame->expected_length = 0;
	पूर्ण

	वापस num;
पूर्ण

अटल स्थिर काष्ठा serdev_device_ops pms7003_serdev_ops = अणु
	.receive_buf = pms7003_receive_buf,
	.ग_लिखो_wakeup = serdev_device_ग_लिखो_wakeup,
पूर्ण;

अटल व्योम pms7003_stop(व्योम *data)
अणु
	काष्ठा pms7003_state *state = data;

	pms7003_करो_cmd(state, CMD_SLEEP);
पूर्ण

अटल स्थिर अचिन्हित दीर्घ pms7003_scan_masks[] = अणु 0x07, 0x00 पूर्ण;

अटल पूर्णांक pms7003_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा pms7003_state *state;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&serdev->dev, माप(*state));
	अगर (!indio_dev)
		वापस -ENOMEM;

	state = iio_priv(indio_dev);
	serdev_device_set_drvdata(serdev, indio_dev);
	state->serdev = serdev;
	indio_dev->info = &pms7003_info;
	indio_dev->name = PMS7003_DRIVER_NAME;
	indio_dev->channels = pms7003_channels;
	indio_dev->num_channels = ARRAY_SIZE(pms7003_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->available_scan_masks = pms7003_scan_masks;

	mutex_init(&state->lock);
	init_completion(&state->frame_पढ़ोy);

	serdev_device_set_client_ops(serdev, &pms7003_serdev_ops);
	ret = devm_serdev_device_खोलो(&serdev->dev, serdev);
	अगर (ret)
		वापस ret;

	serdev_device_set_baudrate(serdev, 9600);
	serdev_device_set_flow_control(serdev, false);

	ret = serdev_device_set_parity(serdev, SERDEV_PARITY_NONE);
	अगर (ret)
		वापस ret;

	ret = pms7003_करो_cmd(state, CMD_WAKEUP);
	अगर (ret) अणु
		dev_err(&serdev->dev, "failed to wakeup sensor\n");
		वापस ret;
	पूर्ण

	ret = pms7003_करो_cmd(state, CMD_ENTER_PASSIVE_MODE);
	अगर (ret) अणु
		dev_err(&serdev->dev, "failed to enter passive mode\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&serdev->dev, pms7003_stop, state);
	अगर (ret)
		वापस ret;

	ret = devm_iio_triggered_buffer_setup(&serdev->dev, indio_dev, शून्य,
					      pms7003_trigger_handler, शून्य);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&serdev->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id pms7003_of_match[] = अणु
	अणु .compatible = "plantower,pms1003" पूर्ण,
	अणु .compatible = "plantower,pms3003" पूर्ण,
	अणु .compatible = "plantower,pms5003" पूर्ण,
	अणु .compatible = "plantower,pms6003" पूर्ण,
	अणु .compatible = "plantower,pms7003" पूर्ण,
	अणु .compatible = "plantower,pmsa003" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pms7003_of_match);

अटल काष्ठा serdev_device_driver pms7003_driver = अणु
	.driver = अणु
		.name = PMS7003_DRIVER_NAME,
		.of_match_table = pms7003_of_match,
	पूर्ण,
	.probe = pms7003_probe,
पूर्ण;
module_serdev_device_driver(pms7003_driver);

MODULE_AUTHOR("Tomasz Duszynski <tduszyns@gmail.com>");
MODULE_DESCRIPTION("Plantower PMS7003 particulate matter sensor driver");
MODULE_LICENSE("GPL v2");
