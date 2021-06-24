<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ADE7854/58/68/78 Polyphase Multअगरunction Energy Metering IC Driver
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश "meter.h"
#समावेश "ade7854.h"

अटल sमाप_प्रकार ade7854_पढ़ो_8bit(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	पूर्णांक ret;
	u32 val = 0;
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	ret = st->पढ़ो_reg(dev, this_attr->address, &val, 8);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार ade7854_पढ़ो_16bit(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	पूर्णांक ret;
	u32 val = 0;
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	ret = st->पढ़ो_reg(dev, this_attr->address, &val, 16);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार ade7854_पढ़ो_24bit(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	पूर्णांक ret;
	u32 val;
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	ret = st->पढ़ो_reg(dev, this_attr->address, &val, 24);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार ade7854_पढ़ो_32bit(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	पूर्णांक ret;
	u32 val = 0;
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);

	ret = st->पढ़ो_reg(dev, this_attr->address, &val, 32);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार ade7854_ग_लिखो_8bit(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf,
				  माप_प्रकार len)
अणु
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);

	पूर्णांक ret;
	u8 val;

	ret = kstrtou8(buf, 10, &val);
	अगर (ret)
		जाओ error_ret;
	ret = st->ग_लिखो_reg(dev, this_attr->address, val, 8);

error_ret:
	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार ade7854_ग_लिखो_16bit(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf,
				   माप_प्रकार len)
अणु
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);

	पूर्णांक ret;
	u16 val;

	ret = kstrtou16(buf, 10, &val);
	अगर (ret)
		जाओ error_ret;
	ret = st->ग_लिखो_reg(dev, this_attr->address, val, 16);

error_ret:
	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार ade7854_ग_लिखो_24bit(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf,
				   माप_प्रकार len)
अणु
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);

	पूर्णांक ret;
	u32 val;

	ret = kstrtou32(buf, 10, &val);
	अगर (ret)
		जाओ error_ret;
	ret = st->ग_लिखो_reg(dev, this_attr->address, val, 24);

error_ret:
	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार ade7854_ग_लिखो_32bit(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf,
				   माप_प्रकार len)
अणु
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);

	पूर्णांक ret;
	u32 val;

	ret = kstrtou32(buf, 10, &val);
	अगर (ret)
		जाओ error_ret;
	ret = st->ग_लिखो_reg(dev, this_attr->address, val, 32);

error_ret:
	वापस ret ? ret : len;
पूर्ण

अटल पूर्णांक ade7854_reset(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);
	u32 val;

	st->पढ़ो_reg(dev, ADE7854_CONFIG, &val, 16);
	val |= BIT(7); /* Software Chip Reset */

	वापस st->ग_लिखो_reg(dev, ADE7854_CONFIG, val, 16);
पूर्ण

अटल IIO_DEV_ATTR_AIGAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_AIGAIN);
अटल IIO_DEV_ATTR_BIGAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_BIGAIN);
अटल IIO_DEV_ATTR_CIGAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_CIGAIN);
अटल IIO_DEV_ATTR_NIGAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_NIGAIN);
अटल IIO_DEV_ATTR_AVGAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_AVGAIN);
अटल IIO_DEV_ATTR_BVGAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_BVGAIN);
अटल IIO_DEV_ATTR_CVGAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_CVGAIN);
अटल IIO_DEV_ATTR_APPARENT_POWER_A_GAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_AVAGAIN);
अटल IIO_DEV_ATTR_APPARENT_POWER_B_GAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_BVAGAIN);
अटल IIO_DEV_ATTR_APPARENT_POWER_C_GAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_CVAGAIN);
अटल IIO_DEV_ATTR_ACTIVE_POWER_A_OFFSET(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_AWATTOS);
अटल IIO_DEV_ATTR_ACTIVE_POWER_B_OFFSET(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_BWATTOS);
अटल IIO_DEV_ATTR_ACTIVE_POWER_C_OFFSET(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_CWATTOS);
अटल IIO_DEV_ATTR_REACTIVE_POWER_A_GAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_AVARGAIN);
अटल IIO_DEV_ATTR_REACTIVE_POWER_B_GAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_BVARGAIN);
अटल IIO_DEV_ATTR_REACTIVE_POWER_C_GAIN(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_CVARGAIN);
अटल IIO_DEV_ATTR_REACTIVE_POWER_A_OFFSET(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_AVAROS);
अटल IIO_DEV_ATTR_REACTIVE_POWER_B_OFFSET(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_BVAROS);
अटल IIO_DEV_ATTR_REACTIVE_POWER_C_OFFSET(0644,
		ade7854_पढ़ो_24bit,
		ade7854_ग_लिखो_24bit,
		ADE7854_CVAROS);
अटल IIO_DEV_ATTR_VPEAK(0644,
		ade7854_पढ़ो_32bit,
		ade7854_ग_लिखो_32bit,
		ADE7854_VPEAK);
अटल IIO_DEV_ATTR_IPEAK(0644,
		ade7854_पढ़ो_32bit,
		ade7854_ग_लिखो_32bit,
		ADE7854_IPEAK);
अटल IIO_DEV_ATTR_APHCAL(0644,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_APHCAL);
अटल IIO_DEV_ATTR_BPHCAL(0644,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_BPHCAL);
अटल IIO_DEV_ATTR_CPHCAL(0644,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_CPHCAL);
अटल IIO_DEV_ATTR_CF1DEN(0644,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_CF1DEN);
अटल IIO_DEV_ATTR_CF2DEN(0644,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_CF2DEN);
अटल IIO_DEV_ATTR_CF3DEN(0644,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_CF3DEN);
अटल IIO_DEV_ATTR_LINECYC(0644,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_LINECYC);
अटल IIO_DEV_ATTR_SAGCYC(0644,
		ade7854_पढ़ो_8bit,
		ade7854_ग_लिखो_8bit,
		ADE7854_SAGCYC);
अटल IIO_DEV_ATTR_CFCYC(0644,
		ade7854_पढ़ो_8bit,
		ade7854_ग_लिखो_8bit,
		ADE7854_CFCYC);
अटल IIO_DEV_ATTR_PEAKCYC(0644,
		ade7854_पढ़ो_8bit,
		ade7854_ग_लिखो_8bit,
		ADE7854_PEAKCYC);
अटल IIO_DEV_ATTR_CHKSUM(ade7854_पढ़ो_24bit,
		ADE7854_CHECKSUM);
अटल IIO_DEV_ATTR_ANGLE0(ade7854_पढ़ो_24bit,
		ADE7854_ANGLE0);
अटल IIO_DEV_ATTR_ANGLE1(ade7854_पढ़ो_24bit,
		ADE7854_ANGLE1);
अटल IIO_DEV_ATTR_ANGLE2(ade7854_पढ़ो_24bit,
		ADE7854_ANGLE2);
अटल IIO_DEV_ATTR_AIRMS(0444,
		ade7854_पढ़ो_24bit,
		शून्य,
		ADE7854_AIRMS);
अटल IIO_DEV_ATTR_BIRMS(0444,
		ade7854_पढ़ो_24bit,
		शून्य,
		ADE7854_BIRMS);
अटल IIO_DEV_ATTR_CIRMS(0444,
		ade7854_पढ़ो_24bit,
		शून्य,
		ADE7854_CIRMS);
अटल IIO_DEV_ATTR_NIRMS(0444,
		ade7854_पढ़ो_24bit,
		शून्य,
		ADE7854_NIRMS);
अटल IIO_DEV_ATTR_AVRMS(0444,
		ade7854_पढ़ो_24bit,
		शून्य,
		ADE7854_AVRMS);
अटल IIO_DEV_ATTR_BVRMS(0444,
		ade7854_पढ़ो_24bit,
		शून्य,
		ADE7854_BVRMS);
अटल IIO_DEV_ATTR_CVRMS(0444,
		ade7854_पढ़ो_24bit,
		शून्य,
		ADE7854_CVRMS);
अटल IIO_DEV_ATTR_AIRMSOS(0444,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_AIRMSOS);
अटल IIO_DEV_ATTR_BIRMSOS(0444,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_BIRMSOS);
अटल IIO_DEV_ATTR_CIRMSOS(0444,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_CIRMSOS);
अटल IIO_DEV_ATTR_AVRMSOS(0444,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_AVRMSOS);
अटल IIO_DEV_ATTR_BVRMSOS(0444,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_BVRMSOS);
अटल IIO_DEV_ATTR_CVRMSOS(0444,
		ade7854_पढ़ो_16bit,
		ade7854_ग_लिखो_16bit,
		ADE7854_CVRMSOS);
अटल IIO_DEV_ATTR_VOLT_A(ade7854_पढ़ो_24bit,
		ADE7854_VAWV);
अटल IIO_DEV_ATTR_VOLT_B(ade7854_पढ़ो_24bit,
		ADE7854_VBWV);
अटल IIO_DEV_ATTR_VOLT_C(ade7854_पढ़ो_24bit,
		ADE7854_VCWV);
अटल IIO_DEV_ATTR_CURRENT_A(ade7854_पढ़ो_24bit,
		ADE7854_IAWV);
अटल IIO_DEV_ATTR_CURRENT_B(ade7854_पढ़ो_24bit,
		ADE7854_IBWV);
अटल IIO_DEV_ATTR_CURRENT_C(ade7854_पढ़ो_24bit,
		ADE7854_ICWV);
अटल IIO_DEV_ATTR_AWATTHR(ade7854_पढ़ो_32bit,
		ADE7854_AWATTHR);
अटल IIO_DEV_ATTR_BWATTHR(ade7854_पढ़ो_32bit,
		ADE7854_BWATTHR);
अटल IIO_DEV_ATTR_CWATTHR(ade7854_पढ़ो_32bit,
		ADE7854_CWATTHR);
अटल IIO_DEV_ATTR_AFWATTHR(ade7854_पढ़ो_32bit,
		ADE7854_AFWATTHR);
अटल IIO_DEV_ATTR_BFWATTHR(ade7854_पढ़ो_32bit,
		ADE7854_BFWATTHR);
अटल IIO_DEV_ATTR_CFWATTHR(ade7854_पढ़ो_32bit,
		ADE7854_CFWATTHR);
अटल IIO_DEV_ATTR_AVARHR(ade7854_पढ़ो_32bit,
		ADE7854_AVARHR);
अटल IIO_DEV_ATTR_BVARHR(ade7854_पढ़ो_32bit,
		ADE7854_BVARHR);
अटल IIO_DEV_ATTR_CVARHR(ade7854_पढ़ो_32bit,
		ADE7854_CVARHR);
अटल IIO_DEV_ATTR_AVAHR(ade7854_पढ़ो_32bit,
		ADE7854_AVAHR);
अटल IIO_DEV_ATTR_BVAHR(ade7854_पढ़ो_32bit,
		ADE7854_BVAHR);
अटल IIO_DEV_ATTR_CVAHR(ade7854_पढ़ो_32bit,
		ADE7854_CVAHR);

अटल पूर्णांक ade7854_set_irq(काष्ठा device *dev, bool enable)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);

	पूर्णांक ret;
	u32 irqen;

	ret = st->पढ़ो_reg(dev, ADE7854_MASK0, &irqen, 32);
	अगर (ret < 0)
		वापस ret;

	अगर (enable)
		irqen |= BIT(17); /* 1: पूर्णांकerrupt enabled when all periodical
				   * (at 8 kHz rate) DSP computations finish.
				   */
	अन्यथा
		irqen &= ~BIT(17);

	वापस st->ग_लिखो_reg(dev, ADE7854_MASK0, irqen, 32);
पूर्ण

अटल पूर्णांक ade7854_initial_setup(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &indio_dev->dev;

	/* Disable IRQ */
	ret = ade7854_set_irq(dev, false);
	अगर (ret) अणु
		dev_err(dev, "disable irq failed");
		जाओ err_ret;
	पूर्ण

	ade7854_reset(dev);
	usleep_range(ADE7854_STARTUP_DELAY, ADE7854_STARTUP_DELAY + 100);

err_ret:
	वापस ret;
पूर्ण

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("8000");

अटल IIO_CONST_ATTR(name, "ade7854");

अटल काष्ठा attribute *ade7854_attributes[] = अणु
	&iio_dev_attr_aigain.dev_attr.attr,
	&iio_dev_attr_bigain.dev_attr.attr,
	&iio_dev_attr_cigain.dev_attr.attr,
	&iio_dev_attr_nigain.dev_attr.attr,
	&iio_dev_attr_avgain.dev_attr.attr,
	&iio_dev_attr_bvgain.dev_attr.attr,
	&iio_dev_attr_cvgain.dev_attr.attr,
	&iio_dev_attr_linecyc.dev_attr.attr,
	&iio_dev_attr_sagcyc.dev_attr.attr,
	&iio_dev_attr_cfcyc.dev_attr.attr,
	&iio_dev_attr_peakcyc.dev_attr.attr,
	&iio_dev_attr_chksum.dev_attr.attr,
	&iio_dev_attr_apparent_घातer_a_gain.dev_attr.attr,
	&iio_dev_attr_apparent_घातer_b_gain.dev_attr.attr,
	&iio_dev_attr_apparent_घातer_c_gain.dev_attr.attr,
	&iio_dev_attr_active_घातer_a_offset.dev_attr.attr,
	&iio_dev_attr_active_घातer_b_offset.dev_attr.attr,
	&iio_dev_attr_active_घातer_c_offset.dev_attr.attr,
	&iio_dev_attr_reactive_घातer_a_gain.dev_attr.attr,
	&iio_dev_attr_reactive_घातer_b_gain.dev_attr.attr,
	&iio_dev_attr_reactive_घातer_c_gain.dev_attr.attr,
	&iio_dev_attr_reactive_घातer_a_offset.dev_attr.attr,
	&iio_dev_attr_reactive_घातer_b_offset.dev_attr.attr,
	&iio_dev_attr_reactive_घातer_c_offset.dev_attr.attr,
	&iio_dev_attr_awatthr.dev_attr.attr,
	&iio_dev_attr_bwatthr.dev_attr.attr,
	&iio_dev_attr_cwatthr.dev_attr.attr,
	&iio_dev_attr_afwatthr.dev_attr.attr,
	&iio_dev_attr_bfwatthr.dev_attr.attr,
	&iio_dev_attr_cfwatthr.dev_attr.attr,
	&iio_dev_attr_avarhr.dev_attr.attr,
	&iio_dev_attr_bvarhr.dev_attr.attr,
	&iio_dev_attr_cvarhr.dev_attr.attr,
	&iio_dev_attr_angle0.dev_attr.attr,
	&iio_dev_attr_angle1.dev_attr.attr,
	&iio_dev_attr_angle2.dev_attr.attr,
	&iio_dev_attr_avahr.dev_attr.attr,
	&iio_dev_attr_bvahr.dev_attr.attr,
	&iio_dev_attr_cvahr.dev_attr.attr,
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	&iio_स्थिर_attr_name.dev_attr.attr,
	&iio_dev_attr_vpeak.dev_attr.attr,
	&iio_dev_attr_ipeak.dev_attr.attr,
	&iio_dev_attr_aphcal.dev_attr.attr,
	&iio_dev_attr_bphcal.dev_attr.attr,
	&iio_dev_attr_cphcal.dev_attr.attr,
	&iio_dev_attr_cf1den.dev_attr.attr,
	&iio_dev_attr_cf2den.dev_attr.attr,
	&iio_dev_attr_cf3den.dev_attr.attr,
	&iio_dev_attr_airms.dev_attr.attr,
	&iio_dev_attr_birms.dev_attr.attr,
	&iio_dev_attr_cirms.dev_attr.attr,
	&iio_dev_attr_nirms.dev_attr.attr,
	&iio_dev_attr_avrms.dev_attr.attr,
	&iio_dev_attr_bvrms.dev_attr.attr,
	&iio_dev_attr_cvrms.dev_attr.attr,
	&iio_dev_attr_airmsos.dev_attr.attr,
	&iio_dev_attr_birmsos.dev_attr.attr,
	&iio_dev_attr_cirmsos.dev_attr.attr,
	&iio_dev_attr_avrmsos.dev_attr.attr,
	&iio_dev_attr_bvrmsos.dev_attr.attr,
	&iio_dev_attr_cvrmsos.dev_attr.attr,
	&iio_dev_attr_volt_a.dev_attr.attr,
	&iio_dev_attr_volt_b.dev_attr.attr,
	&iio_dev_attr_volt_c.dev_attr.attr,
	&iio_dev_attr_current_a.dev_attr.attr,
	&iio_dev_attr_current_b.dev_attr.attr,
	&iio_dev_attr_current_c.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ade7854_attribute_group = अणु
	.attrs = ade7854_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info ade7854_info = अणु
	.attrs = &ade7854_attribute_group,
पूर्ण;

पूर्णांक ade7854_probe(काष्ठा iio_dev *indio_dev, काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा ade7854_state *st = iio_priv(indio_dev);
	/* setup the industrialio driver allocated elements */
	mutex_init(&st->buf_lock);

	indio_dev->dev.parent = dev;
	indio_dev->info = &ade7854_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret)
		वापस ret;

	/* Get the device पूर्णांकo a sane initial state */
	वापस ade7854_initial_setup(indio_dev);
पूर्ण
EXPORT_SYMBOL(ade7854_probe);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ADE7854/58/68/78 Polyphase Energy Meter");
MODULE_LICENSE("GPL v2");
