<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics sensors core library driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/iio/common/st_sensors.h>

#समावेश "st_sensors_core.h"

पूर्णांक st_sensors_ग_लिखो_data_with_mask(काष्ठा iio_dev *indio_dev,
				    u8 reg_addr, u8 mask, u8 data)
अणु
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	वापस regmap_update_bits(sdata->regmap,
				  reg_addr, mask, data << __ffs(mask));
पूर्ण

पूर्णांक st_sensors_debugfs_reg_access(काष्ठा iio_dev *indio_dev,
				  अचिन्हित reg, अचिन्हित ग_लिखोval,
				  अचिन्हित *पढ़ोval)
अणु
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);
	पूर्णांक err;

	अगर (!पढ़ोval)
		वापस regmap_ग_लिखो(sdata->regmap, reg, ग_लिखोval);

	err = regmap_पढ़ो(sdata->regmap, reg, पढ़ोval);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(st_sensors_debugfs_reg_access);

अटल पूर्णांक st_sensors_match_odr(काष्ठा st_sensor_settings *sensor_settings,
			अचिन्हित पूर्णांक odr, काष्ठा st_sensor_odr_avl *odr_out)
अणु
	पूर्णांक i, ret = -EINVAL;

	क्रम (i = 0; i < ST_SENSORS_ODR_LIST_MAX; i++) अणु
		अगर (sensor_settings->odr.odr_avl[i].hz == 0)
			जाओ st_sensors_match_odr_error;

		अगर (sensor_settings->odr.odr_avl[i].hz == odr) अणु
			odr_out->hz = sensor_settings->odr.odr_avl[i].hz;
			odr_out->value = sensor_settings->odr.odr_avl[i].value;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

st_sensors_match_odr_error:
	वापस ret;
पूर्ण

पूर्णांक st_sensors_set_odr(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक odr)
अणु
	पूर्णांक err;
	काष्ठा st_sensor_odr_avl odr_out = अणु0, 0पूर्ण;
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	अगर (!sdata->sensor_settings->odr.mask)
		वापस 0;

	err = st_sensors_match_odr(sdata->sensor_settings, odr, &odr_out);
	अगर (err < 0)
		जाओ st_sensors_match_odr_error;

	अगर ((sdata->sensor_settings->odr.addr ==
					sdata->sensor_settings->pw.addr) &&
				(sdata->sensor_settings->odr.mask ==
					sdata->sensor_settings->pw.mask)) अणु
		अगर (sdata->enabled == true) अणु
			err = st_sensors_ग_लिखो_data_with_mask(indio_dev,
				sdata->sensor_settings->odr.addr,
				sdata->sensor_settings->odr.mask,
				odr_out.value);
		पूर्ण अन्यथा अणु
			err = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = st_sensors_ग_लिखो_data_with_mask(indio_dev,
			sdata->sensor_settings->odr.addr,
			sdata->sensor_settings->odr.mask,
			odr_out.value);
	पूर्ण
	अगर (err >= 0)
		sdata->odr = odr_out.hz;

st_sensors_match_odr_error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(st_sensors_set_odr);

अटल पूर्णांक st_sensors_match_fs(काष्ठा st_sensor_settings *sensor_settings,
					अचिन्हित पूर्णांक fs, पूर्णांक *index_fs_avl)
अणु
	पूर्णांक i, ret = -EINVAL;

	क्रम (i = 0; i < ST_SENSORS_FULLSCALE_AVL_MAX; i++) अणु
		अगर (sensor_settings->fs.fs_avl[i].num == 0)
			वापस ret;

		अगर (sensor_settings->fs.fs_avl[i].num == fs) अणु
			*index_fs_avl = i;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक st_sensors_set_fullscale(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक fs)
अणु
	पूर्णांक err, i = 0;
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	अगर (sdata->sensor_settings->fs.addr == 0)
		वापस 0;

	err = st_sensors_match_fs(sdata->sensor_settings, fs, &i);
	अगर (err < 0)
		जाओ st_accel_set_fullscale_error;

	err = st_sensors_ग_लिखो_data_with_mask(indio_dev,
				sdata->sensor_settings->fs.addr,
				sdata->sensor_settings->fs.mask,
				sdata->sensor_settings->fs.fs_avl[i].value);
	अगर (err < 0)
		जाओ st_accel_set_fullscale_error;

	sdata->current_fullscale = &sdata->sensor_settings->fs.fs_avl[i];
	वापस err;

st_accel_set_fullscale_error:
	dev_err(&indio_dev->dev, "failed to set new fullscale.\n");
	वापस err;
पूर्ण

पूर्णांक st_sensors_set_enable(काष्ठा iio_dev *indio_dev, bool enable)
अणु
	u8 पंचांगp_value;
	पूर्णांक err = -EINVAL;
	bool found = false;
	काष्ठा st_sensor_odr_avl odr_out = अणु0, 0पूर्ण;
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	अगर (enable) अणु
		पंचांगp_value = sdata->sensor_settings->pw.value_on;
		अगर ((sdata->sensor_settings->odr.addr ==
					sdata->sensor_settings->pw.addr) &&
				(sdata->sensor_settings->odr.mask ==
					sdata->sensor_settings->pw.mask)) अणु
			err = st_sensors_match_odr(sdata->sensor_settings,
							sdata->odr, &odr_out);
			अगर (err < 0)
				जाओ set_enable_error;
			पंचांगp_value = odr_out.value;
			found = true;
		पूर्ण
		err = st_sensors_ग_लिखो_data_with_mask(indio_dev,
				sdata->sensor_settings->pw.addr,
				sdata->sensor_settings->pw.mask, पंचांगp_value);
		अगर (err < 0)
			जाओ set_enable_error;

		sdata->enabled = true;

		अगर (found)
			sdata->odr = odr_out.hz;
	पूर्ण अन्यथा अणु
		err = st_sensors_ग_लिखो_data_with_mask(indio_dev,
				sdata->sensor_settings->pw.addr,
				sdata->sensor_settings->pw.mask,
				sdata->sensor_settings->pw.value_off);
		अगर (err < 0)
			जाओ set_enable_error;

		sdata->enabled = false;
	पूर्ण

set_enable_error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(st_sensors_set_enable);

पूर्णांक st_sensors_set_axis_enable(काष्ठा iio_dev *indio_dev, u8 axis_enable)
अणु
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);
	पूर्णांक err = 0;

	अगर (sdata->sensor_settings->enable_axis.addr)
		err = st_sensors_ग_लिखो_data_with_mask(indio_dev,
				sdata->sensor_settings->enable_axis.addr,
				sdata->sensor_settings->enable_axis.mask,
				axis_enable);
	वापस err;
पूर्ण
EXPORT_SYMBOL(st_sensors_set_axis_enable);

पूर्णांक st_sensors_घातer_enable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा st_sensor_data *pdata = iio_priv(indio_dev);
	पूर्णांक err;

	/* Regulators not mandatory, but अगर requested we should enable them. */
	pdata->vdd = devm_regulator_get(indio_dev->dev.parent, "vdd");
	अगर (IS_ERR(pdata->vdd)) अणु
		dev_err(&indio_dev->dev, "unable to get Vdd supply\n");
		वापस PTR_ERR(pdata->vdd);
	पूर्ण
	err = regulator_enable(pdata->vdd);
	अगर (err != 0) अणु
		dev_warn(&indio_dev->dev,
			 "Failed to enable specified Vdd supply\n");
		वापस err;
	पूर्ण

	pdata->vdd_io = devm_regulator_get(indio_dev->dev.parent, "vddio");
	अगर (IS_ERR(pdata->vdd_io)) अणु
		dev_err(&indio_dev->dev, "unable to get Vdd_IO supply\n");
		err = PTR_ERR(pdata->vdd_io);
		जाओ st_sensors_disable_vdd;
	पूर्ण
	err = regulator_enable(pdata->vdd_io);
	अगर (err != 0) अणु
		dev_warn(&indio_dev->dev,
			 "Failed to enable specified Vdd_IO supply\n");
		जाओ st_sensors_disable_vdd;
	पूर्ण

	वापस 0;

st_sensors_disable_vdd:
	regulator_disable(pdata->vdd);
	वापस err;
पूर्ण
EXPORT_SYMBOL(st_sensors_घातer_enable);

व्योम st_sensors_घातer_disable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा st_sensor_data *pdata = iio_priv(indio_dev);

	regulator_disable(pdata->vdd);
	regulator_disable(pdata->vdd_io);
पूर्ण
EXPORT_SYMBOL(st_sensors_घातer_disable);

अटल पूर्णांक st_sensors_set_drdy_पूर्णांक_pin(काष्ठा iio_dev *indio_dev,
					काष्ठा st_sensors_platक्रमm_data *pdata)
अणु
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	/* Sensor करोes not support पूर्णांकerrupts */
	अगर (!sdata->sensor_settings->drdy_irq.पूर्णांक1.addr &&
	    !sdata->sensor_settings->drdy_irq.पूर्णांक2.addr) अणु
		अगर (pdata->drdy_पूर्णांक_pin)
			dev_info(&indio_dev->dev,
				 "DRDY on pin INT%d specified, but sensor does not support interrupts\n",
				 pdata->drdy_पूर्णांक_pin);
		वापस 0;
	पूर्ण

	चयन (pdata->drdy_पूर्णांक_pin) अणु
	हाल 1:
		अगर (!sdata->sensor_settings->drdy_irq.पूर्णांक1.mask) अणु
			dev_err(&indio_dev->dev,
					"DRDY on INT1 not available.\n");
			वापस -EINVAL;
		पूर्ण
		sdata->drdy_पूर्णांक_pin = 1;
		अवरोध;
	हाल 2:
		अगर (!sdata->sensor_settings->drdy_irq.पूर्णांक2.mask) अणु
			dev_err(&indio_dev->dev,
					"DRDY on INT2 not available.\n");
			वापस -EINVAL;
		पूर्ण
		sdata->drdy_पूर्णांक_pin = 2;
		अवरोध;
	शेष:
		dev_err(&indio_dev->dev, "DRDY on pdata not valid.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->खोलो_drain) अणु
		अगर (!sdata->sensor_settings->drdy_irq.पूर्णांक1.addr_od &&
		    !sdata->sensor_settings->drdy_irq.पूर्णांक2.addr_od)
			dev_err(&indio_dev->dev,
				"open drain requested but unsupported.\n");
		अन्यथा
			sdata->पूर्णांक_pin_खोलो_drain = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा st_sensors_platक्रमm_data *st_sensors_dev_probe(काष्ठा device *dev,
		काष्ठा st_sensors_platक्रमm_data *defdata)
अणु
	काष्ठा st_sensors_platक्रमm_data *pdata;
	u32 val;

	अगर (!dev_fwnode(dev))
		वापस शून्य;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);
	अगर (!device_property_पढ़ो_u32(dev, "st,drdy-int-pin", &val) && (val <= 2))
		pdata->drdy_पूर्णांक_pin = (u8) val;
	अन्यथा
		pdata->drdy_पूर्णांक_pin = defdata ? defdata->drdy_पूर्णांक_pin : 0;

	pdata->खोलो_drain = device_property_पढ़ो_bool(dev, "drive-open-drain");

	वापस pdata;
पूर्ण

/**
 * st_sensors_dev_name_probe() - device probe क्रम ST sensor name
 * @dev: driver model representation of the device.
 * @name: device name buffer reference.
 * @len: device name buffer length.
 *
 * In effect this function matches an ID to an पूर्णांकernal kernel
 * name क्रम a certain sensor device, so that the rest of the स्वतःdetection can
 * rely on that name from this poपूर्णांक on. I2C/SPI devices will be नामd
 * to match the पूर्णांकernal kernel convention.
 */
व्योम st_sensors_dev_name_probe(काष्ठा device *dev, अक्षर *name, पूर्णांक len)
अणु
	स्थिर व्योम *match;

	match = device_get_match_data(dev);
	अगर (!match)
		वापस;

	/* The name from the match takes precedence अगर present */
	strlcpy(name, match, len);
पूर्ण
EXPORT_SYMBOL(st_sensors_dev_name_probe);

पूर्णांक st_sensors_init_sensor(काष्ठा iio_dev *indio_dev,
					काष्ठा st_sensors_platक्रमm_data *pdata)
अणु
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);
	काष्ठा st_sensors_platक्रमm_data *of_pdata;
	पूर्णांक err = 0;

	/* If OF/DT pdata exists, it will take precedence of anything अन्यथा */
	of_pdata = st_sensors_dev_probe(indio_dev->dev.parent, pdata);
	अगर (IS_ERR(of_pdata))
		वापस PTR_ERR(of_pdata);
	अगर (of_pdata)
		pdata = of_pdata;

	अगर (pdata) अणु
		err = st_sensors_set_drdy_पूर्णांक_pin(indio_dev, pdata);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = st_sensors_set_enable(indio_dev, false);
	अगर (err < 0)
		वापस err;

	/* Disable DRDY, this might be still be enabled after reboot. */
	err = st_sensors_set_dataपढ़ोy_irq(indio_dev, false);
	अगर (err < 0)
		वापस err;

	अगर (sdata->current_fullscale) अणु
		err = st_sensors_set_fullscale(indio_dev,
						sdata->current_fullscale->num);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा
		dev_info(&indio_dev->dev, "Full-scale not possible\n");

	err = st_sensors_set_odr(indio_dev, sdata->odr);
	अगर (err < 0)
		वापस err;

	/* set BDU */
	अगर (sdata->sensor_settings->bdu.addr) अणु
		err = st_sensors_ग_लिखो_data_with_mask(indio_dev,
					sdata->sensor_settings->bdu.addr,
					sdata->sensor_settings->bdu.mask, true);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* set DAS */
	अगर (sdata->sensor_settings->das.addr) अणु
		err = st_sensors_ग_लिखो_data_with_mask(indio_dev,
					sdata->sensor_settings->das.addr,
					sdata->sensor_settings->das.mask, 1);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (sdata->पूर्णांक_pin_खोलो_drain) अणु
		u8 addr, mask;

		अगर (sdata->drdy_पूर्णांक_pin == 1) अणु
			addr = sdata->sensor_settings->drdy_irq.पूर्णांक1.addr_od;
			mask = sdata->sensor_settings->drdy_irq.पूर्णांक1.mask_od;
		पूर्ण अन्यथा अणु
			addr = sdata->sensor_settings->drdy_irq.पूर्णांक2.addr_od;
			mask = sdata->sensor_settings->drdy_irq.पूर्णांक2.mask_od;
		पूर्ण

		dev_info(&indio_dev->dev,
			 "set interrupt line to open drain mode on pin %d\n",
			 sdata->drdy_पूर्णांक_pin);
		err = st_sensors_ग_लिखो_data_with_mask(indio_dev, addr,
						      mask, 1);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = st_sensors_set_axis_enable(indio_dev, ST_SENSORS_ENABLE_ALL_AXIS);

	वापस err;
पूर्ण
EXPORT_SYMBOL(st_sensors_init_sensor);

पूर्णांक st_sensors_set_dataपढ़ोy_irq(काष्ठा iio_dev *indio_dev, bool enable)
अणु
	पूर्णांक err;
	u8 drdy_addr, drdy_mask;
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	अगर (!sdata->sensor_settings->drdy_irq.पूर्णांक1.addr &&
	    !sdata->sensor_settings->drdy_irq.पूर्णांक2.addr) अणु
		/*
		 * there are some devices (e.g. LIS3MDL) where drdy line is
		 * routed to a given pin and it is not possible to select a
		 * dअगरferent one. Take पूर्णांकo account irq status रेजिस्टर
		 * to understand अगर irq trigger can be properly supported
		 */
		अगर (sdata->sensor_settings->drdy_irq.stat_drdy.addr)
			sdata->hw_irq_trigger = enable;
		वापस 0;
	पूर्ण

	/* Enable/Disable the पूर्णांकerrupt generator 1. */
	अगर (sdata->sensor_settings->drdy_irq.ig1.en_addr > 0) अणु
		err = st_sensors_ग_लिखो_data_with_mask(indio_dev,
				sdata->sensor_settings->drdy_irq.ig1.en_addr,
				sdata->sensor_settings->drdy_irq.ig1.en_mask,
				(पूर्णांक)enable);
		अगर (err < 0)
			जाओ st_accel_set_dataपढ़ोy_irq_error;
	पूर्ण

	अगर (sdata->drdy_पूर्णांक_pin == 1) अणु
		drdy_addr = sdata->sensor_settings->drdy_irq.पूर्णांक1.addr;
		drdy_mask = sdata->sensor_settings->drdy_irq.पूर्णांक1.mask;
	पूर्ण अन्यथा अणु
		drdy_addr = sdata->sensor_settings->drdy_irq.पूर्णांक2.addr;
		drdy_mask = sdata->sensor_settings->drdy_irq.पूर्णांक2.mask;
	पूर्ण

	/* Flag to the poll function that the hardware trigger is in use */
	sdata->hw_irq_trigger = enable;

	/* Enable/Disable the पूर्णांकerrupt generator क्रम data पढ़ोy. */
	err = st_sensors_ग_लिखो_data_with_mask(indio_dev, drdy_addr,
					      drdy_mask, (पूर्णांक)enable);

st_accel_set_dataपढ़ोy_irq_error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(st_sensors_set_dataपढ़ोy_irq);

पूर्णांक st_sensors_set_fullscale_by_gain(काष्ठा iio_dev *indio_dev, पूर्णांक scale)
अणु
	पूर्णांक err = -EINVAL, i;
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	क्रम (i = 0; i < ST_SENSORS_FULLSCALE_AVL_MAX; i++) अणु
		अगर ((sdata->sensor_settings->fs.fs_avl[i].gain == scale) &&
				(sdata->sensor_settings->fs.fs_avl[i].gain != 0)) अणु
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (err < 0)
		जाओ st_sensors_match_scale_error;

	err = st_sensors_set_fullscale(indio_dev,
				sdata->sensor_settings->fs.fs_avl[i].num);

st_sensors_match_scale_error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(st_sensors_set_fullscale_by_gain);

अटल पूर्णांक st_sensors_पढ़ो_axis_data(काष्ठा iio_dev *indio_dev,
				     काष्ठा iio_chan_spec स्थिर *ch, पूर्णांक *data)
अणु
	पूर्णांक err;
	u8 *outdata;
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);
	अचिन्हित पूर्णांक byte_क्रम_channel;

	byte_क्रम_channel = DIV_ROUND_UP(ch->scan_type.realbits +
					ch->scan_type.shअगरt, 8);
	outdata = kदो_स्मृति(byte_क्रम_channel, GFP_DMA | GFP_KERNEL);
	अगर (!outdata)
		वापस -ENOMEM;

	err = regmap_bulk_पढ़ो(sdata->regmap, ch->address,
			       outdata, byte_क्रम_channel);
	अगर (err < 0)
		जाओ st_sensors_मुक्त_memory;

	अगर (byte_क्रम_channel == 1)
		*data = (s8)*outdata;
	अन्यथा अगर (byte_क्रम_channel == 2)
		*data = (s16)get_unaligned_le16(outdata);
	अन्यथा अगर (byte_क्रम_channel == 3)
		*data = (s32)sign_extend32(get_unaligned_le24(outdata), 23);

st_sensors_मुक्त_memory:
	kमुक्त(outdata);

	वापस err;
पूर्ण

पूर्णांक st_sensors_पढ़ो_info_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *ch, पूर्णांक *val)
अणु
	पूर्णांक err;
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	mutex_lock(&indio_dev->mlock);
	अगर (indio_dev->currenपंचांगode == INDIO_BUFFER_TRIGGERED) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण अन्यथा अणु
		err = st_sensors_set_enable(indio_dev, true);
		अगर (err < 0)
			जाओ out;

		msleep((sdata->sensor_settings->booसमय * 1000) / sdata->odr);
		err = st_sensors_पढ़ो_axis_data(indio_dev, ch, val);
		अगर (err < 0)
			जाओ out;

		*val = *val >> ch->scan_type.shअगरt;

		err = st_sensors_set_enable(indio_dev, false);
	पूर्ण
out:
	mutex_unlock(&indio_dev->mlock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(st_sensors_पढ़ो_info_raw);

/*
 * st_sensors_get_settings_index() - get index of the sensor settings क्रम a
 *				     specअगरic device from list of settings
 * @name: device name buffer reference.
 * @list: sensor settings list.
 * @list_length: length of sensor settings list.
 *
 * Return: non negative number on success (valid index),
 *	   negative error code otherwise.
 */
पूर्णांक st_sensors_get_settings_index(स्थिर अक्षर *name,
				  स्थिर काष्ठा st_sensor_settings *list,
				  स्थिर पूर्णांक list_length)
अणु
	पूर्णांक i, n;

	क्रम (i = 0; i < list_length; i++) अणु
		क्रम (n = 0; n < ST_SENSORS_MAX_4WAI; n++) अणु
			अगर (म_भेद(name, list[i].sensors_supported[n]) == 0)
				वापस i;
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(st_sensors_get_settings_index);

/*
 * st_sensors_verअगरy_id() - verअगरy sensor ID (WhoAmI) is matching with the
 *			    expected value
 * @indio_dev: IIO device reference.
 *
 * Return: 0 on success (valid sensor ID), अन्यथा a negative error code.
 */
पूर्णांक st_sensors_verअगरy_id(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);
	पूर्णांक wai, err;

	अगर (sdata->sensor_settings->wai_addr) अणु
		err = regmap_पढ़ो(sdata->regmap,
				  sdata->sensor_settings->wai_addr, &wai);
		अगर (err < 0) अणु
			dev_err(&indio_dev->dev,
				"failed to read Who-Am-I register.\n");
			वापस err;
		पूर्ण

		अगर (sdata->sensor_settings->wai != wai) अणु
			dev_err(&indio_dev->dev,
				"%s: WhoAmI mismatch (0x%x).\n",
				indio_dev->name, wai);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(st_sensors_verअगरy_id);

sमाप_प्रकार st_sensors_sysfs_sampling_frequency_avail(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i, len = 0;
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	mutex_lock(&indio_dev->mlock);
	क्रम (i = 0; i < ST_SENSORS_ODR_LIST_MAX; i++) अणु
		अगर (sdata->sensor_settings->odr.odr_avl[i].hz == 0)
			अवरोध;

		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d ",
				sdata->sensor_settings->odr.odr_avl[i].hz);
	पूर्ण
	mutex_unlock(&indio_dev->mlock);
	buf[len - 1] = '\n';

	वापस len;
पूर्ण
EXPORT_SYMBOL(st_sensors_sysfs_sampling_frequency_avail);

sमाप_प्रकार st_sensors_sysfs_scale_avail(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i, len = 0, q, r;
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	mutex_lock(&indio_dev->mlock);
	क्रम (i = 0; i < ST_SENSORS_FULLSCALE_AVL_MAX; i++) अणु
		अगर (sdata->sensor_settings->fs.fs_avl[i].num == 0)
			अवरोध;

		q = sdata->sensor_settings->fs.fs_avl[i].gain / 1000000;
		r = sdata->sensor_settings->fs.fs_avl[i].gain % 1000000;

		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%u.%06u ", q, r);
	पूर्ण
	mutex_unlock(&indio_dev->mlock);
	buf[len - 1] = '\n';

	वापस len;
पूर्ण
EXPORT_SYMBOL(st_sensors_sysfs_scale_avail);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics ST-sensors core");
MODULE_LICENSE("GPL v2");
