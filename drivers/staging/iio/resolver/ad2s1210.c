<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ad2s1210.c support क्रम the ADI Resolver to Digital Converters: AD2S1210
 *
 * Copyright (c) 2010-2010 Analog Devices Inc.
 */
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा DRV_NAME "ad2s1210"

#घोषणा AD2S1210_DEF_CONTROL		0x7E

#घोषणा AD2S1210_MSB_IS_HIGH		0x80
#घोषणा AD2S1210_MSB_IS_LOW		0x7F
#घोषणा AD2S1210_PHASE_LOCK_RANGE_44	0x20
#घोषणा AD2S1210_ENABLE_HYSTERESIS	0x10
#घोषणा AD2S1210_SET_ENRES1		0x08
#घोषणा AD2S1210_SET_ENRES0		0x04
#घोषणा AD2S1210_SET_RES1		0x02
#घोषणा AD2S1210_SET_RES0		0x01

#घोषणा AD2S1210_SET_RESOLUTION		(AD2S1210_SET_RES1 | AD2S1210_SET_RES0)

#घोषणा AD2S1210_REG_POSITION		0x80
#घोषणा AD2S1210_REG_VELOCITY		0x82
#घोषणा AD2S1210_REG_LOS_THRD		0x88
#घोषणा AD2S1210_REG_DOS_OVR_THRD	0x89
#घोषणा AD2S1210_REG_DOS_MIS_THRD	0x8A
#घोषणा AD2S1210_REG_DOS_RST_MAX_THRD	0x8B
#घोषणा AD2S1210_REG_DOS_RST_MIN_THRD	0x8C
#घोषणा AD2S1210_REG_LOT_HIGH_THRD	0x8D
#घोषणा AD2S1210_REG_LOT_LOW_THRD	0x8E
#घोषणा AD2S1210_REG_EXCIT_FREQ		0x91
#घोषणा AD2S1210_REG_CONTROL		0x92
#घोषणा AD2S1210_REG_SOFT_RESET		0xF0
#घोषणा AD2S1210_REG_FAULT		0xFF

#घोषणा AD2S1210_MIN_CLKIN	6144000
#घोषणा AD2S1210_MAX_CLKIN	10240000
#घोषणा AD2S1210_MIN_EXCIT	2000
#घोषणा AD2S1210_MAX_EXCIT	20000
#घोषणा AD2S1210_MIN_FCW	0x4
#घोषणा AD2S1210_MAX_FCW	0x50

#घोषणा AD2S1210_DEF_EXCIT	10000

क्रमागत ad2s1210_mode अणु
	MOD_POS = 0,
	MOD_VEL,
	MOD_CONFIG,
	MOD_RESERVED,
पूर्ण;

क्रमागत ad2s1210_gpios अणु
	AD2S1210_SAMPLE,
	AD2S1210_A0,
	AD2S1210_A1,
	AD2S1210_RES0,
	AD2S1210_RES1,
पूर्ण;

काष्ठा ad2s1210_gpio अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ flags;
पूर्ण;

अटल स्थिर काष्ठा ad2s1210_gpio gpios[] = अणु
	[AD2S1210_SAMPLE] = अणु .name = "adi,sample", .flags = GPIOD_OUT_LOW पूर्ण,
	[AD2S1210_A0] = अणु .name = "adi,a0", .flags = GPIOD_OUT_LOW पूर्ण,
	[AD2S1210_A1] = अणु .name = "adi,a1", .flags = GPIOD_OUT_LOW पूर्ण,
	[AD2S1210_RES0] = अणु .name = "adi,res0", .flags = GPIOD_OUT_LOW पूर्ण,
	[AD2S1210_RES1] = अणु .name = "adi,res1", .flags = GPIOD_OUT_LOW पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ad2s1210_resolution_value[] = अणु 10, 12, 14, 16 पूर्ण;

काष्ठा ad2s1210_state अणु
	काष्ठा mutex lock;
	काष्ठा spi_device *sdev;
	काष्ठा gpio_desc *gpios[5];
	अचिन्हित पूर्णांक fclkin;
	अचिन्हित पूर्णांक fexcit;
	bool hysteresis;
	u8 resolution;
	क्रमागत ad2s1210_mode mode;
	u8 rx[2] ____cacheline_aligned;
	u8 tx[2] ____cacheline_aligned;
पूर्ण;

अटल स्थिर पूर्णांक ad2s1210_mode_vals[4][2] = अणु
	[MOD_POS] = अणु 0, 0 पूर्ण,
	[MOD_VEL] = अणु 0, 1 पूर्ण,
	[MOD_CONFIG] = अणु 1, 0 पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम ad2s1210_set_mode(क्रमागत ad2s1210_mode mode,
				     काष्ठा ad2s1210_state *st)
अणु
	gpiod_set_value(st->gpios[AD2S1210_A0], ad2s1210_mode_vals[mode][0]);
	gpiod_set_value(st->gpios[AD2S1210_A1], ad2s1210_mode_vals[mode][1]);
	st->mode = mode;
पूर्ण

/* ग_लिखो 1 bytes (address or data) to the chip */
अटल पूर्णांक ad2s1210_config_ग_लिखो(काष्ठा ad2s1210_state *st, u8 data)
अणु
	पूर्णांक ret;

	ad2s1210_set_mode(MOD_CONFIG, st);
	st->tx[0] = data;
	ret = spi_ग_लिखो(st->sdev, st->tx, 1);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* पढ़ो value from one of the रेजिस्टरs */
अटल पूर्णांक ad2s1210_config_पढ़ो(काष्ठा ad2s1210_state *st,
				अचिन्हित अक्षर address)
अणु
	काष्ठा spi_transfer xfers[] = अणु
		अणु
			.len = 1,
			.rx_buf = &st->rx[0],
			.tx_buf = &st->tx[0],
			.cs_change = 1,
		पूर्ण, अणु
			.len = 1,
			.rx_buf = &st->rx[1],
			.tx_buf = &st->tx[1],
		पूर्ण,
	पूर्ण;
	पूर्णांक ret = 0;

	ad2s1210_set_mode(MOD_CONFIG, st);
	st->tx[0] = address | AD2S1210_MSB_IS_HIGH;
	st->tx[1] = AD2S1210_REG_FAULT;
	ret = spi_sync_transfer(st->sdev, xfers, 2);
	अगर (ret < 0)
		वापस ret;

	वापस st->rx[1];
पूर्ण

अटल अंतरभूत
पूर्णांक ad2s1210_update_frequency_control_word(काष्ठा ad2s1210_state *st)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर fcw;

	fcw = (अचिन्हित अक्षर)(st->fexcit * (1 << 15) / st->fclkin);
	अगर (fcw < AD2S1210_MIN_FCW || fcw > AD2S1210_MAX_FCW) अणु
		dev_err(&st->sdev->dev, "ad2s1210: FCW out of range\n");
		वापस -दुस्फल;
	पूर्ण

	ret = ad2s1210_config_ग_लिखो(st, AD2S1210_REG_EXCIT_FREQ);
	अगर (ret < 0)
		वापस ret;

	वापस ad2s1210_config_ग_लिखो(st, fcw);
पूर्ण

अटल स्थिर पूर्णांक ad2s1210_res_pins[4][2] = अणु
	अणु 0, 0 पूर्ण, अणु0, 1पूर्ण, अणु1, 0पूर्ण, अणु1, 1पूर्ण
पूर्ण;

अटल अंतरभूत व्योम ad2s1210_set_resolution_pin(काष्ठा ad2s1210_state *st)
अणु
	gpiod_set_value(st->gpios[AD2S1210_RES0],
			ad2s1210_res_pins[(st->resolution - 10) / 2][0]);
	gpiod_set_value(st->gpios[AD2S1210_RES1],
			ad2s1210_res_pins[(st->resolution - 10) / 2][1]);
पूर्ण

अटल अंतरभूत पूर्णांक ad2s1210_soft_reset(काष्ठा ad2s1210_state *st)
अणु
	पूर्णांक ret;

	ret = ad2s1210_config_ग_लिखो(st, AD2S1210_REG_SOFT_RESET);
	अगर (ret < 0)
		वापस ret;

	वापस ad2s1210_config_ग_लिखो(st, 0x0);
पूर्ण

अटल sमाप_प्रकार ad2s1210_show_fclkin(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));

	वापस प्र_लिखो(buf, "%u\n", st->fclkin);
पूर्ण

अटल sमाप_प्रकार ad2s1210_store_fclkin(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf,
				     माप_प्रकार len)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	अचिन्हित पूर्णांक fclkin;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &fclkin);
	अगर (ret)
		वापस ret;
	अगर (fclkin < AD2S1210_MIN_CLKIN || fclkin > AD2S1210_MAX_CLKIN) अणु
		dev_err(dev, "ad2s1210: fclkin out of range\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&st->lock);
	st->fclkin = fclkin;

	ret = ad2s1210_update_frequency_control_word(st);
	अगर (ret < 0)
		जाओ error_ret;
	ret = ad2s1210_soft_reset(st);
error_ret:
	mutex_unlock(&st->lock);

	वापस ret < 0 ? ret : len;
पूर्ण

अटल sमाप_प्रकार ad2s1210_show_fexcit(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));

	वापस प्र_लिखो(buf, "%u\n", st->fexcit);
पूर्ण

अटल sमाप_प्रकार ad2s1210_store_fexcit(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	अचिन्हित पूर्णांक fexcit;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &fexcit);
	अगर (ret < 0)
		वापस ret;
	अगर (fexcit < AD2S1210_MIN_EXCIT || fexcit > AD2S1210_MAX_EXCIT) अणु
		dev_err(dev,
			"ad2s1210: excitation frequency out of range\n");
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&st->lock);
	st->fexcit = fexcit;
	ret = ad2s1210_update_frequency_control_word(st);
	अगर (ret < 0)
		जाओ error_ret;
	ret = ad2s1210_soft_reset(st);
error_ret:
	mutex_unlock(&st->lock);

	वापस ret < 0 ? ret : len;
पूर्ण

अटल sमाप_प्रकार ad2s1210_show_control(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = ad2s1210_config_पढ़ो(st, AD2S1210_REG_CONTROL);
	mutex_unlock(&st->lock);
	वापस ret < 0 ? ret : प्र_लिखो(buf, "0x%x\n", ret);
पूर्ण

अटल sमाप_प्रकार ad2s1210_store_control(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	अचिन्हित अक्षर udata;
	अचिन्हित अक्षर data;
	पूर्णांक ret;

	ret = kstrtou8(buf, 16, &udata);
	अगर (ret)
		वापस -EINVAL;

	mutex_lock(&st->lock);
	ret = ad2s1210_config_ग_लिखो(st, AD2S1210_REG_CONTROL);
	अगर (ret < 0)
		जाओ error_ret;
	data = udata & AD2S1210_MSB_IS_LOW;
	ret = ad2s1210_config_ग_लिखो(st, data);
	अगर (ret < 0)
		जाओ error_ret;

	ret = ad2s1210_config_पढ़ो(st, AD2S1210_REG_CONTROL);
	अगर (ret < 0)
		जाओ error_ret;
	अगर (ret & AD2S1210_MSB_IS_HIGH) अणु
		ret = -EIO;
		dev_err(dev,
			"ad2s1210: write control register fail\n");
		जाओ error_ret;
	पूर्ण
	st->resolution =
		ad2s1210_resolution_value[data & AD2S1210_SET_RESOLUTION];
	ad2s1210_set_resolution_pin(st);
	ret = len;
	st->hysteresis = !!(data & AD2S1210_ENABLE_HYSTERESIS);

error_ret:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ad2s1210_show_resolution(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));

	वापस प्र_लिखो(buf, "%d\n", st->resolution);
पूर्ण

अटल sमाप_प्रकार ad2s1210_store_resolution(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	अचिन्हित अक्षर data;
	अचिन्हित अक्षर udata;
	पूर्णांक ret;

	ret = kstrtou8(buf, 10, &udata);
	अगर (ret || udata < 10 || udata > 16) अणु
		dev_err(dev, "ad2s1210: resolution out of range\n");
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&st->lock);
	ret = ad2s1210_config_पढ़ो(st, AD2S1210_REG_CONTROL);
	अगर (ret < 0)
		जाओ error_ret;
	data = ret;
	data &= ~AD2S1210_SET_RESOLUTION;
	data |= (udata - 10) >> 1;
	ret = ad2s1210_config_ग_लिखो(st, AD2S1210_REG_CONTROL);
	अगर (ret < 0)
		जाओ error_ret;
	ret = ad2s1210_config_ग_लिखो(st, data & AD2S1210_MSB_IS_LOW);
	अगर (ret < 0)
		जाओ error_ret;
	ret = ad2s1210_config_पढ़ो(st, AD2S1210_REG_CONTROL);
	अगर (ret < 0)
		जाओ error_ret;
	data = ret;
	अगर (data & AD2S1210_MSB_IS_HIGH) अणु
		ret = -EIO;
		dev_err(dev, "ad2s1210: setting resolution fail\n");
		जाओ error_ret;
	पूर्ण
	st->resolution =
		ad2s1210_resolution_value[data & AD2S1210_SET_RESOLUTION];
	ad2s1210_set_resolution_pin(st);
	ret = len;
error_ret:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

/* पढ़ो the fault रेजिस्टर since last sample */
अटल sमाप_प्रकार ad2s1210_show_fault(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = ad2s1210_config_पढ़ो(st, AD2S1210_REG_FAULT);
	mutex_unlock(&st->lock);

	वापस ret ? ret : प्र_लिखो(buf, "0x%x\n", ret);
पूर्ण

अटल sमाप_प्रकार ad2s1210_clear_fault(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf,
				    माप_प्रकार len)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	पूर्णांक ret;

	mutex_lock(&st->lock);
	gpiod_set_value(st->gpios[AD2S1210_SAMPLE], 0);
	/* delay (2 * tck + 20) nano seconds */
	udelay(1);
	gpiod_set_value(st->gpios[AD2S1210_SAMPLE], 1);
	ret = ad2s1210_config_पढ़ो(st, AD2S1210_REG_FAULT);
	अगर (ret < 0)
		जाओ error_ret;
	gpiod_set_value(st->gpios[AD2S1210_SAMPLE], 0);
	gpiod_set_value(st->gpios[AD2S1210_SAMPLE], 1);
error_ret:
	mutex_unlock(&st->lock);

	वापस ret < 0 ? ret : len;
पूर्ण

अटल sमाप_प्रकार ad2s1210_show_reg(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	काष्ठा iio_dev_attr *iattr = to_iio_dev_attr(attr);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = ad2s1210_config_पढ़ो(st, iattr->address);
	mutex_unlock(&st->lock);

	वापस ret < 0 ? ret : प्र_लिखो(buf, "%d\n", ret);
पूर्ण

अटल sमाप_प्रकार ad2s1210_store_reg(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	अचिन्हित अक्षर data;
	पूर्णांक ret;
	काष्ठा iio_dev_attr *iattr = to_iio_dev_attr(attr);

	ret = kstrtou8(buf, 10, &data);
	अगर (ret)
		वापस -EINVAL;
	mutex_lock(&st->lock);
	ret = ad2s1210_config_ग_लिखो(st, iattr->address);
	अगर (ret < 0)
		जाओ error_ret;
	ret = ad2s1210_config_ग_लिखो(st, data & AD2S1210_MSB_IS_LOW);
error_ret:
	mutex_unlock(&st->lock);
	वापस ret < 0 ? ret : len;
पूर्ण

अटल पूर्णांक ad2s1210_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val,
			     पूर्णांक *val2,
			     दीर्घ m)
अणु
	काष्ठा ad2s1210_state *st = iio_priv(indio_dev);
	u16 negative;
	पूर्णांक ret = 0;
	u16 pos;
	s16 vel;

	mutex_lock(&st->lock);
	gpiod_set_value(st->gpios[AD2S1210_SAMPLE], 0);
	/* delay (6 * tck + 20) nano seconds */
	udelay(1);

	चयन (chan->type) अणु
	हाल IIO_ANGL:
		ad2s1210_set_mode(MOD_POS, st);
		अवरोध;
	हाल IIO_ANGL_VEL:
		ad2s1210_set_mode(MOD_VEL, st);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (ret < 0)
		जाओ error_ret;
	ret = spi_पढ़ो(st->sdev, st->rx, 2);
	अगर (ret < 0)
		जाओ error_ret;

	चयन (chan->type) अणु
	हाल IIO_ANGL:
		pos = be16_to_cpup((__be16 *)st->rx);
		अगर (st->hysteresis)
			pos >>= 16 - st->resolution;
		*val = pos;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_ANGL_VEL:
		negative = st->rx[0] & 0x80;
		vel = be16_to_cpup((__be16 *)st->rx);
		vel >>= 16 - st->resolution;
		अगर (vel & 0x8000) अणु
			negative = (0xffff >> st->resolution) << st->resolution;
			vel |= negative;
		पूर्ण
		*val = vel;
		ret = IIO_VAL_INT;
		अवरोध;
	शेष:
		mutex_unlock(&st->lock);
		वापस -EINVAL;
	पूर्ण

error_ret:
	gpiod_set_value(st->gpios[AD2S1210_SAMPLE], 1);
	/* delay (2 * tck + 20) nano seconds */
	udelay(1);
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल IIO_DEVICE_ATTR(fclkin, 0644,
		       ad2s1210_show_fclkin, ad2s1210_store_fclkin, 0);
अटल IIO_DEVICE_ATTR(fexcit, 0644,
		       ad2s1210_show_fexcit,	ad2s1210_store_fexcit, 0);
अटल IIO_DEVICE_ATTR(control, 0644,
		       ad2s1210_show_control, ad2s1210_store_control, 0);
अटल IIO_DEVICE_ATTR(bits, 0644,
		       ad2s1210_show_resolution, ad2s1210_store_resolution, 0);
अटल IIO_DEVICE_ATTR(fault, 0644,
		       ad2s1210_show_fault, ad2s1210_clear_fault, 0);

अटल IIO_DEVICE_ATTR(los_thrd, 0644,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_LOS_THRD);
अटल IIO_DEVICE_ATTR(करोs_ovr_thrd, 0644,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_DOS_OVR_THRD);
अटल IIO_DEVICE_ATTR(करोs_mis_thrd, 0644,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_DOS_MIS_THRD);
अटल IIO_DEVICE_ATTR(करोs_rst_max_thrd, 0644,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_DOS_RST_MAX_THRD);
अटल IIO_DEVICE_ATTR(करोs_rst_min_thrd, 0644,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_DOS_RST_MIN_THRD);
अटल IIO_DEVICE_ATTR(lot_high_thrd, 0644,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_LOT_HIGH_THRD);
अटल IIO_DEVICE_ATTR(lot_low_thrd, 0644,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_LOT_LOW_THRD);

अटल स्थिर काष्ठा iio_chan_spec ad2s1210_channels[] = अणु
	अणु
		.type = IIO_ANGL,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण, अणु
		.type = IIO_ANGL_VEL,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण
पूर्ण;

अटल काष्ठा attribute *ad2s1210_attributes[] = अणु
	&iio_dev_attr_fclkin.dev_attr.attr,
	&iio_dev_attr_fexcit.dev_attr.attr,
	&iio_dev_attr_control.dev_attr.attr,
	&iio_dev_attr_bits.dev_attr.attr,
	&iio_dev_attr_fault.dev_attr.attr,
	&iio_dev_attr_los_thrd.dev_attr.attr,
	&iio_dev_attr_करोs_ovr_thrd.dev_attr.attr,
	&iio_dev_attr_करोs_mis_thrd.dev_attr.attr,
	&iio_dev_attr_करोs_rst_max_thrd.dev_attr.attr,
	&iio_dev_attr_करोs_rst_min_thrd.dev_attr.attr,
	&iio_dev_attr_lot_high_thrd.dev_attr.attr,
	&iio_dev_attr_lot_low_thrd.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad2s1210_attribute_group = अणु
	.attrs = ad2s1210_attributes,
पूर्ण;

अटल पूर्णांक ad2s1210_initial(काष्ठा ad2s1210_state *st)
अणु
	अचिन्हित अक्षर data;
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ad2s1210_set_resolution_pin(st);

	ret = ad2s1210_config_ग_लिखो(st, AD2S1210_REG_CONTROL);
	अगर (ret < 0)
		जाओ error_ret;
	data = AD2S1210_DEF_CONTROL & ~(AD2S1210_SET_RESOLUTION);
	data |= (st->resolution - 10) >> 1;
	ret = ad2s1210_config_ग_लिखो(st, data);
	अगर (ret < 0)
		जाओ error_ret;
	ret = ad2s1210_config_पढ़ो(st, AD2S1210_REG_CONTROL);
	अगर (ret < 0)
		जाओ error_ret;

	अगर (ret & AD2S1210_MSB_IS_HIGH) अणु
		ret = -EIO;
		जाओ error_ret;
	पूर्ण

	ret = ad2s1210_update_frequency_control_word(st);
	अगर (ret < 0)
		जाओ error_ret;
	ret = ad2s1210_soft_reset(st);
error_ret:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ad2s1210_info = अणु
	.पढ़ो_raw = ad2s1210_पढ़ो_raw,
	.attrs = &ad2s1210_attribute_group,
पूर्ण;

अटल पूर्णांक ad2s1210_setup_gpios(काष्ठा ad2s1210_state *st)
अणु
	काष्ठा spi_device *spi = st->sdev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(gpios); i++) अणु
		st->gpios[i] = devm_gpiod_get(&spi->dev, gpios[i].name,
					      gpios[i].flags);
		अगर (IS_ERR(st->gpios[i])) अणु
			ret = PTR_ERR(st->gpios[i]);
			dev_err(&spi->dev,
				"ad2s1210: failed to request %s GPIO: %d\n",
				gpios[i].name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad2s1210_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad2s1210_state *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;
	st = iio_priv(indio_dev);
	ret = ad2s1210_setup_gpios(st);
	अगर (ret < 0)
		वापस ret;

	spi_set_drvdata(spi, indio_dev);

	mutex_init(&st->lock);
	st->sdev = spi;
	st->hysteresis = true;
	st->mode = MOD_CONFIG;
	st->resolution = 12;
	st->fexcit = AD2S1210_DEF_EXCIT;

	indio_dev->info = &ad2s1210_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ad2s1210_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad2s1210_channels);
	indio_dev->name = spi_get_device_id(spi)->name;

	ret = devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
	अगर (ret)
		वापस ret;

	st->fclkin = spi->max_speed_hz;
	spi->mode = SPI_MODE_3;
	spi_setup(spi);
	ad2s1210_initial(st);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ad2s1210_of_match[] = अणु
	अणु .compatible = "adi,ad2s1210", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad2s1210_of_match);

अटल स्थिर काष्ठा spi_device_id ad2s1210_id[] = अणु
	अणु "ad2s1210" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad2s1210_id);

अटल काष्ठा spi_driver ad2s1210_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(ad2s1210_of_match),
	पूर्ण,
	.probe = ad2s1210_probe,
	.id_table = ad2s1210_id,
पूर्ण;
module_spi_driver(ad2s1210_driver);

MODULE_AUTHOR("Graff Yang <graff.yang@gmail.com>");
MODULE_DESCRIPTION("Analog Devices AD2S1210 Resolver to Digital SPI driver");
MODULE_LICENSE("GPL v2");
