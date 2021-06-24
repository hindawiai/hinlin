<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * All Sensors DLH series low voltage digital pressure sensors
 *
 * Copyright (c) 2019 AVL DiTEST GmbH
 *   Tomislav Denis <tomislav.denis@avl.com>
 *
 * Datasheet: https://www.allsensors.com/cad/DS-0355_Rev_B.PDF
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <यंत्र/unaligned.h>

/* Commands */
#घोषणा DLH_START_SINGLE    0xAA

/* Status bits */
#घोषणा DLH_STATUS_OK       0x40

/* DLH  data क्रमmat */
#घोषणा DLH_NUM_READ_BYTES  7
#घोषणा DLH_NUM_DATA_BYTES  3
#घोषणा DLH_NUM_PR_BITS     24
#घोषणा DLH_NUM_TEMP_BITS   24

/* DLH  timings */
#घोषणा DLH_SINGLE_DUT_MS   5

क्रमागत dhl_ids अणु
	dlhl60d,
	dlhl60g,
पूर्ण;

काष्ठा dlh_info अणु
	u8 osdig;           /* digital offset factor */
	अचिन्हित पूर्णांक fss;   /* full scale span (inch H2O) */
पूर्ण;

काष्ठा dlh_state अणु
	काष्ठा i2c_client *client;
	काष्ठा dlh_info info;
	bool use_पूर्णांकerrupt;
	काष्ठा completion completion;
	u8 rx_buf[DLH_NUM_READ_BYTES] ____cacheline_aligned;
पूर्ण;

अटल काष्ठा dlh_info dlh_info_tbl[] = अणु
	[dlhl60d] = अणु
		.osdig = 2,
		.fss = 120,
	पूर्ण,
	[dlhl60g] = अणु
		.osdig = 10,
		.fss = 60,
	पूर्ण,
पूर्ण;


अटल पूर्णांक dlh_cmd_start_single(काष्ठा dlh_state *st)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte(st->client, DLH_START_SINGLE);
	अगर (ret)
		dev_err(&st->client->dev,
			"%s: I2C write byte failed\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक dlh_cmd_पढ़ो_data(काष्ठा dlh_state *st)
अणु
	पूर्णांक ret;

	ret = i2c_master_recv(st->client, st->rx_buf, DLH_NUM_READ_BYTES);
	अगर (ret < 0) अणु
		dev_err(&st->client->dev,
			"%s: I2C read block failed\n", __func__);
		वापस ret;
	पूर्ण

	अगर (st->rx_buf[0] != DLH_STATUS_OK) अणु
		dev_err(&st->client->dev,
			"%s: invalid status 0x%02x\n", __func__, st->rx_buf[0]);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dlh_start_capture_and_पढ़ो(काष्ठा dlh_state *st)
अणु
	पूर्णांक ret;

	अगर (st->use_पूर्णांकerrupt)
		reinit_completion(&st->completion);

	ret = dlh_cmd_start_single(st);
	अगर (ret)
		वापस ret;

	अगर (st->use_पूर्णांकerrupt) अणु
		ret = रुको_क्रम_completion_समयout(&st->completion,
			msecs_to_jअगरfies(DLH_SINGLE_DUT_MS));
		अगर (!ret) अणु
			dev_err(&st->client->dev,
				"%s: conversion timed out\n", __func__);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		mdelay(DLH_SINGLE_DUT_MS);
	पूर्ण

	वापस dlh_cmd_पढ़ो_data(st);
पूर्ण

अटल पूर्णांक dlh_पढ़ो_direct(काष्ठा dlh_state *st,
	अचिन्हित पूर्णांक *pressure, अचिन्हित पूर्णांक *temperature)
अणु
	पूर्णांक ret;

	ret = dlh_start_capture_and_पढ़ो(st);
	अगर (ret)
		वापस ret;

	*pressure = get_unaligned_be32(&st->rx_buf[1]) >> 8;
	*temperature = get_unaligned_be32(&st->rx_buf[3]) &
		GENMASK(DLH_NUM_TEMP_BITS - 1, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक dlh_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *value,
	पूर्णांक *value2, दीर्घ mask)
अणु
	काष्ठा dlh_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक pressure, temperature;
	पूर्णांक ret;
	s64 पंचांगp;
	s32 rem;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = dlh_पढ़ो_direct(st, &pressure, &temperature);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		चयन (channel->type) अणु
		हाल IIO_PRESSURE:
			*value = pressure;
			वापस IIO_VAL_INT;

		हाल IIO_TEMP:
			*value = temperature;
			वापस IIO_VAL_INT;

		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (channel->type) अणु
		हाल IIO_PRESSURE:
			पंचांगp = भाग_s64(125LL * st->info.fss * 24909 * 100,
				1 << DLH_NUM_PR_BITS);
			पंचांगp = भाग_s64_rem(पंचांगp, 1000000000LL, &rem);
			*value = पंचांगp;
			*value2 = rem;
			वापस IIO_VAL_INT_PLUS_न_अंकO;

		हाल IIO_TEMP:
			*value = 125 * 1000;
			*value2 = DLH_NUM_TEMP_BITS;
			वापस IIO_VAL_FRACTIONAL_LOG2;

		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		चयन (channel->type) अणु
		हाल IIO_PRESSURE:
			*value = -125 * st->info.fss * 24909;
			*value2 = 100 * st->info.osdig * 100000;
			वापस IIO_VAL_FRACTIONAL;

		हाल IIO_TEMP:
			*value = -40 * 1000;
			वापस IIO_VAL_INT;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info dlh_info = अणु
	.पढ़ो_raw = dlh_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec dlh_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.indexed = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type =
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = DLH_NUM_PR_BITS,
			.storagebits = 32,
			.shअगरt = 8,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण, अणु
		.type = IIO_TEMP,
		.indexed = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type =
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = 1,
		.scan_type = अणु
			.sign = 'u',
			.realbits = DLH_NUM_TEMP_BITS,
			.storagebits = 32,
			.shअगरt = 8,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल irqवापस_t dlh_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा dlh_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक chn, i = 0;
	__be32 पंचांगp_buf[2];

	ret = dlh_start_capture_and_पढ़ो(st);
	अगर (ret)
		जाओ out;

	क्रम_each_set_bit(chn, indio_dev->active_scan_mask,
		indio_dev->masklength) अणु
		स_नकल(पंचांगp_buf + i,
			&st->rx_buf[1] + chn * DLH_NUM_DATA_BYTES,
			DLH_NUM_DATA_BYTES);
		i++;
	पूर्ण

	iio_push_to_buffers(indio_dev, पंचांगp_buf);

out:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dlh_पूर्णांकerrupt(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा dlh_state *st = iio_priv(indio_dev);

	complete(&st->completion);

	वापस IRQ_HANDLED;
पूर्ण;

अटल पूर्णांक dlh_probe(काष्ठा i2c_client *client,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा dlh_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
		I2C_FUNC_I2C | I2C_FUNC_SMBUS_WRITE_BYTE)) अणु
		dev_err(&client->dev,
			"adapter doesn't support required i2c functionality\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*st));
	अगर (!indio_dev) अणु
		dev_err(&client->dev, "failed to allocate iio device\n");
		वापस -ENOMEM;
	पूर्ण

	i2c_set_clientdata(client, indio_dev);

	st = iio_priv(indio_dev);
	st->info = dlh_info_tbl[id->driver_data];
	st->client = client;
	st->use_पूर्णांकerrupt = false;

	indio_dev->name = id->name;
	indio_dev->info = &dlh_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels =  dlh_channels;
	indio_dev->num_channels = ARRAY_SIZE(dlh_channels);

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
			dlh_पूर्णांकerrupt, शून्य,
			IRQF_TRIGGER_RISING | IRQF_ONESHOT,
			id->name, indio_dev);
		अगर (ret) अणु
			dev_err(&client->dev, "failed to allocate threaded irq");
			वापस ret;
		पूर्ण

		st->use_पूर्णांकerrupt = true;
		init_completion(&st->completion);
	पूर्ण

	ret = devm_iio_triggered_buffer_setup(&client->dev, indio_dev,
		शून्य, &dlh_trigger_handler, शून्य);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to setup iio buffer\n");
		वापस ret;
	पूर्ण

	ret = devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
	अगर (ret)
		dev_err(&client->dev, "failed to register iio device\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id dlh_of_match[] = अणु
	अणु .compatible = "asc,dlhl60d" पूर्ण,
	अणु .compatible = "asc,dlhl60g" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dlh_of_match);

अटल स्थिर काष्ठा i2c_device_id dlh_id[] = अणु
	अणु "dlhl60d",    dlhl60d पूर्ण,
	अणु "dlhl60g",    dlhl60g पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, dlh_id);

अटल काष्ठा i2c_driver dlh_driver = अणु
	.driver = अणु
		.name = "dlhl60d",
		.of_match_table = dlh_of_match,
	पूर्ण,
	.probe = dlh_probe,
	.id_table = dlh_id,
पूर्ण;
module_i2c_driver(dlh_driver);

MODULE_AUTHOR("Tomislav Denis <tomislav.denis@avl.com>");
MODULE_DESCRIPTION("Driver for All Sensors DLH series pressure sensors");
MODULE_LICENSE("GPL v2");
