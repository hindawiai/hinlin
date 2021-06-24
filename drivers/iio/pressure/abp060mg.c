<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 - Marcin Malagowski <mrc@bourne.st>
 */
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>

#घोषणा ABP060MG_ERROR_MASK   0xC000
#घोषणा ABP060MG_RESP_TIME_MS 40
#घोषणा ABP060MG_MIN_COUNTS   1638  /* = 0x0666 (10% of u14) */
#घोषणा ABP060MG_MAX_COUNTS   14745 /* = 0x3999 (90% of u14) */
#घोषणा ABP060MG_NUM_COUNTS   (ABP060MG_MAX_COUNTS - ABP060MG_MIN_COUNTS)

क्रमागत abp_variant अणु
	/* gage [kPa] */
	ABP006KG, ABP010KG, ABP016KG, ABP025KG, ABP040KG, ABP060KG, ABP100KG,
	ABP160KG, ABP250KG, ABP400KG, ABP600KG, ABP001GG,
	/* dअगरferential [kPa] */
	ABP006KD, ABP010KD, ABP016KD, ABP025KD, ABP040KD, ABP060KD, ABP100KD,
	ABP160KD, ABP250KD, ABP400KD,
	/* gage [psi] */
	ABP001PG, ABP005PG, ABP015PG, ABP030PG, ABP060PG, ABP100PG, ABP150PG,
	/* dअगरferential [psi] */
	ABP001PD, ABP005PD, ABP015PD, ABP030PD, ABP060PD,
पूर्ण;

काष्ठा abp_config अणु
	पूर्णांक min;
	पूर्णांक max;
पूर्ण;

अटल काष्ठा abp_config abp_config[] = अणु
	/* mbar & kPa variants */
	[ABP006KG] = अणु .min =       0, .max =     6000 पूर्ण,
	[ABP010KG] = अणु .min =       0, .max =    10000 पूर्ण,
	[ABP016KG] = अणु .min =       0, .max =    16000 पूर्ण,
	[ABP025KG] = अणु .min =       0, .max =    25000 पूर्ण,
	[ABP040KG] = अणु .min =       0, .max =    40000 पूर्ण,
	[ABP060KG] = अणु .min =       0, .max =    60000 पूर्ण,
	[ABP100KG] = अणु .min =       0, .max =   100000 पूर्ण,
	[ABP160KG] = अणु .min =       0, .max =   160000 पूर्ण,
	[ABP250KG] = अणु .min =       0, .max =   250000 पूर्ण,
	[ABP400KG] = अणु .min =       0, .max =   400000 पूर्ण,
	[ABP600KG] = अणु .min =       0, .max =   600000 पूर्ण,
	[ABP001GG] = अणु .min =       0, .max =  1000000 पूर्ण,
	[ABP006KD] = अणु .min =   -6000, .max =     6000 पूर्ण,
	[ABP010KD] = अणु .min =  -10000, .max =    10000 पूर्ण,
	[ABP016KD] = अणु .min =  -16000, .max =    16000 पूर्ण,
	[ABP025KD] = अणु .min =  -25000, .max =    25000 पूर्ण,
	[ABP040KD] = अणु .min =  -40000, .max =    40000 पूर्ण,
	[ABP060KD] = अणु .min =  -60000, .max =    60000 पूर्ण,
	[ABP100KD] = अणु .min = -100000, .max =   100000 पूर्ण,
	[ABP160KD] = अणु .min = -160000, .max =   160000 पूर्ण,
	[ABP250KD] = अणु .min = -250000, .max =   250000 पूर्ण,
	[ABP400KD] = अणु .min = -400000, .max =   400000 पूर्ण,
	/* psi variants (1 psi ~ 6895 Pa) */
	[ABP001PG] = अणु .min =       0, .max =     6985 पूर्ण,
	[ABP005PG] = अणु .min =       0, .max =    34474 पूर्ण,
	[ABP015PG] = अणु .min =       0, .max =   103421 पूर्ण,
	[ABP030PG] = अणु .min =       0, .max =   206843 पूर्ण,
	[ABP060PG] = अणु .min =       0, .max =   413686 पूर्ण,
	[ABP100PG] = अणु .min =       0, .max =   689476 पूर्ण,
	[ABP150PG] = अणु .min =       0, .max =  1034214 पूर्ण,
	[ABP001PD] = अणु .min =   -6895, .max =     6895 पूर्ण,
	[ABP005PD] = अणु .min =  -34474, .max =    34474 पूर्ण,
	[ABP015PD] = अणु .min = -103421, .max =   103421 पूर्ण,
	[ABP030PD] = अणु .min = -206843, .max =   206843 पूर्ण,
	[ABP060PD] = अणु .min = -413686, .max =   413686 पूर्ण,
पूर्ण;

काष्ठा abp_state अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;

	/*
	 * bus-dependent MEASURE_REQUEST length.
	 * If no SMBUS_QUICK support, need to send dummy byte
	 */
	पूर्णांक mreq_len;

	/* model-dependent values (calculated on probe) */
	पूर्णांक scale;
	पूर्णांक offset;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec abp060mg_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
पूर्ण;

अटल पूर्णांक abp060mg_get_measurement(काष्ठा abp_state *state, पूर्णांक *val)
अणु
	काष्ठा i2c_client *client = state->client;
	__be16 buf[2];
	u16 pressure;
	पूर्णांक ret;

	buf[0] = 0;
	ret = i2c_master_send(client, (u8 *)&buf, state->mreq_len);
	अगर (ret < 0)
		वापस ret;

	msleep_पूर्णांकerruptible(ABP060MG_RESP_TIME_MS);

	ret = i2c_master_recv(client, (u8 *)&buf, माप(buf));
	अगर (ret < 0)
		वापस ret;

	pressure = be16_to_cpu(buf[0]);
	अगर (pressure & ABP060MG_ERROR_MASK)
		वापस -EIO;

	अगर (pressure < ABP060MG_MIN_COUNTS || pressure > ABP060MG_MAX_COUNTS)
		वापस -EIO;

	*val = pressure;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक abp060mg_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा abp_state *state = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&state->lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = abp060mg_get_measurement(state, val);
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = state->offset;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		*val = state->scale;
		*val2 = ABP060MG_NUM_COUNTS * 1000; /* to kPa */
		ret = IIO_VAL_FRACTIONAL;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&state->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info abp060mg_info = अणु
	.पढ़ो_raw = abp060mg_पढ़ो_raw,
पूर्ण;

अटल व्योम abp060mg_init_device(काष्ठा iio_dev *indio_dev, अचिन्हित दीर्घ id)
अणु
	काष्ठा abp_state *state = iio_priv(indio_dev);
	काष्ठा abp_config *cfg = &abp_config[id];

	state->scale = cfg->max - cfg->min;
	state->offset = -ABP060MG_MIN_COUNTS;

	अगर (cfg->min < 0) /* dअगरferential */
		state->offset -= ABP060MG_NUM_COUNTS >> 1;
पूर्ण

अटल पूर्णांक abp060mg_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा abp_state *state;
	अचिन्हित दीर्घ cfg_id = id->driver_data;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*state));
	अगर (!indio_dev)
		वापस -ENOMEM;

	state = iio_priv(indio_dev);
	i2c_set_clientdata(client, state);
	state->client = client;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_QUICK))
		state->mreq_len = 1;

	abp060mg_init_device(indio_dev, cfg_id);

	indio_dev->name = dev_name(&client->dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &abp060mg_info;

	indio_dev->channels = abp060mg_channels;
	indio_dev->num_channels = ARRAY_SIZE(abp060mg_channels);

	mutex_init(&state->lock);

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id abp060mg_id_table[] = अणु
	/* mbar & kPa variants (abp060m [60 mbar] == abp006k [6 kPa]) */
	/*    gage: */
	अणु "abp060mg", ABP006KG पूर्ण, अणु "abp006kg", ABP006KG पूर्ण,
	अणु "abp100mg", ABP010KG पूर्ण, अणु "abp010kg", ABP010KG पूर्ण,
	अणु "abp160mg", ABP016KG पूर्ण, अणु "abp016kg", ABP016KG पूर्ण,
	अणु "abp250mg", ABP025KG पूर्ण, अणु "abp025kg", ABP025KG पूर्ण,
	अणु "abp400mg", ABP040KG पूर्ण, अणु "abp040kg", ABP040KG पूर्ण,
	अणु "abp600mg", ABP060KG पूर्ण, अणु "abp060kg", ABP060KG पूर्ण,
	अणु "abp001bg", ABP100KG पूर्ण, अणु "abp100kg", ABP100KG पूर्ण,
	अणु "abp1_6bg", ABP160KG पूर्ण, अणु "abp160kg", ABP160KG पूर्ण,
	अणु "abp2_5bg", ABP250KG पूर्ण, अणु "abp250kg", ABP250KG पूर्ण,
	अणु "abp004bg", ABP400KG पूर्ण, अणु "abp400kg", ABP400KG पूर्ण,
	अणु "abp006bg", ABP600KG पूर्ण, अणु "abp600kg", ABP600KG पूर्ण,
	अणु "abp010bg", ABP001GG पूर्ण, अणु "abp001gg", ABP001GG पूर्ण,
	/*    dअगरferential: */
	अणु "abp060md", ABP006KD पूर्ण, अणु "abp006kd", ABP006KD पूर्ण,
	अणु "abp100md", ABP010KD पूर्ण, अणु "abp010kd", ABP010KD पूर्ण,
	अणु "abp160md", ABP016KD पूर्ण, अणु "abp016kd", ABP016KD पूर्ण,
	अणु "abp250md", ABP025KD पूर्ण, अणु "abp025kd", ABP025KD पूर्ण,
	अणु "abp400md", ABP040KD पूर्ण, अणु "abp040kd", ABP040KD पूर्ण,
	अणु "abp600md", ABP060KD पूर्ण, अणु "abp060kd", ABP060KD पूर्ण,
	अणु "abp001bd", ABP100KD पूर्ण, अणु "abp100kd", ABP100KD पूर्ण,
	अणु "abp1_6bd", ABP160KD पूर्ण, अणु "abp160kd", ABP160KD पूर्ण,
	अणु "abp2_5bd", ABP250KD पूर्ण, अणु "abp250kd", ABP250KD पूर्ण,
	अणु "abp004bd", ABP400KD पूर्ण, अणु "abp400kd", ABP400KD पूर्ण,
	/* psi variants */
	/*    gage: */
	अणु "abp001pg", ABP001PG पूर्ण,
	अणु "abp005pg", ABP005PG पूर्ण,
	अणु "abp015pg", ABP015PG पूर्ण,
	अणु "abp030pg", ABP030PG पूर्ण,
	अणु "abp060pg", ABP060PG पूर्ण,
	अणु "abp100pg", ABP100PG पूर्ण,
	अणु "abp150pg", ABP150PG पूर्ण,
	/*    dअगरferential: */
	अणु "abp001pd", ABP001PD पूर्ण,
	अणु "abp005pd", ABP005PD पूर्ण,
	अणु "abp015pd", ABP015PD पूर्ण,
	अणु "abp030pd", ABP030PD पूर्ण,
	अणु "abp060pd", ABP060PD पूर्ण,
	अणु /* empty */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, abp060mg_id_table);

अटल काष्ठा i2c_driver abp060mg_driver = अणु
	.driver = अणु
		.name = "abp060mg",
	पूर्ण,
	.probe = abp060mg_probe,
	.id_table = abp060mg_id_table,
पूर्ण;
module_i2c_driver(abp060mg_driver);

MODULE_AUTHOR("Marcin Malagowski <mrc@bourne.st>");
MODULE_DESCRIPTION("Honeywell ABP pressure sensor driver");
MODULE_LICENSE("GPL");
