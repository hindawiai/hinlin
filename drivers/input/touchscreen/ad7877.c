<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006-2008 Michael Hennerich, Analog Devices Inc.
 *
 * Description:	AD7877 based touchscreen, sensor (ADCs), DAC and GPIO driver
 * Based on:	ads7846.c
 *
 * Bugs:        Enter bugs at http://blackfin.uclinux.org/
 *
 * History:
 * Copyright (c) 2005 David Brownell
 * Copyright (c) 2006 Nokia Corporation
 * Various changes: Imre Deak <imre.deak@nokia.com>
 *
 * Using code from:
 *  - corgi_ts.c
 *	Copyright (C) 2004-2005 Riअक्षरd Purdie
 *  - omap_ts.[hc], ads7846.h, ts_osk.c
 *	Copyright (C) 2002 MontaVista Software
 *	Copyright (C) 2004 Texas Instruments
 *	Copyright (C) 2005 Dirk Behme
 */


#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ad7877.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/irq.h>

#घोषणा	TS_PEN_UP_TIMEOUT	msecs_to_jअगरfies(100)

#घोषणा MAX_SPI_FREQ_HZ			20000000
#घोषणा	MAX_12BIT			((1<<12)-1)

#घोषणा AD7877_REG_ZEROS			0
#घोषणा AD7877_REG_CTRL1			1
#घोषणा AD7877_REG_CTRL2			2
#घोषणा AD7877_REG_ALERT			3
#घोषणा AD7877_REG_AUX1HIGH			4
#घोषणा AD7877_REG_AUX1LOW			5
#घोषणा AD7877_REG_BAT1HIGH			6
#घोषणा AD7877_REG_BAT1LOW			7
#घोषणा AD7877_REG_BAT2HIGH			8
#घोषणा AD7877_REG_BAT2LOW			9
#घोषणा AD7877_REG_TEMP1HIGH			10
#घोषणा AD7877_REG_TEMP1LOW			11
#घोषणा AD7877_REG_SEQ0				12
#घोषणा AD7877_REG_SEQ1				13
#घोषणा AD7877_REG_DAC				14
#घोषणा AD7877_REG_NONE1			15
#घोषणा AD7877_REG_EXTWRITE			15
#घोषणा AD7877_REG_XPLUS			16
#घोषणा AD7877_REG_YPLUS			17
#घोषणा AD7877_REG_Z2				18
#घोषणा AD7877_REG_aux1				19
#घोषणा AD7877_REG_aux2				20
#घोषणा AD7877_REG_aux3				21
#घोषणा AD7877_REG_bat1				22
#घोषणा AD7877_REG_bat2				23
#घोषणा AD7877_REG_temp1			24
#घोषणा AD7877_REG_temp2			25
#घोषणा AD7877_REG_Z1				26
#घोषणा AD7877_REG_GPIOCTRL1			27
#घोषणा AD7877_REG_GPIOCTRL2			28
#घोषणा AD7877_REG_GPIODATA			29
#घोषणा AD7877_REG_NONE2			30
#घोषणा AD7877_REG_NONE3			31

#घोषणा AD7877_SEQ_YPLUS_BIT			(1<<11)
#घोषणा AD7877_SEQ_XPLUS_BIT			(1<<10)
#घोषणा AD7877_SEQ_Z2_BIT			(1<<9)
#घोषणा AD7877_SEQ_AUX1_BIT			(1<<8)
#घोषणा AD7877_SEQ_AUX2_BIT			(1<<7)
#घोषणा AD7877_SEQ_AUX3_BIT			(1<<6)
#घोषणा AD7877_SEQ_BAT1_BIT			(1<<5)
#घोषणा AD7877_SEQ_BAT2_BIT			(1<<4)
#घोषणा AD7877_SEQ_TEMP1_BIT			(1<<3)
#घोषणा AD7877_SEQ_TEMP2_BIT			(1<<2)
#घोषणा AD7877_SEQ_Z1_BIT			(1<<1)

क्रमागत अणु
	AD7877_SEQ_YPOS  = 0,
	AD7877_SEQ_XPOS  = 1,
	AD7877_SEQ_Z2    = 2,
	AD7877_SEQ_AUX1  = 3,
	AD7877_SEQ_AUX2  = 4,
	AD7877_SEQ_AUX3  = 5,
	AD7877_SEQ_BAT1  = 6,
	AD7877_SEQ_BAT2  = 7,
	AD7877_SEQ_TEMP1 = 8,
	AD7877_SEQ_TEMP2 = 9,
	AD7877_SEQ_Z1    = 10,
	AD7877_NR_SENSE  = 11,
पूर्ण;

/* DAC Register Default RANGE 0 to Vcc, Volatge Mode, DAC On */
#घोषणा AD7877_DAC_CONF			0x1

/* If gpio3 is set AUX3/GPIO3 acts as GPIO Output */
#घोषणा AD7877_EXTW_GPIO_3_CONF		0x1C4
#घोषणा AD7877_EXTW_GPIO_DATA		0x200

/* Control REG 2 */
#घोषणा AD7877_TMR(x)			((x & 0x3) << 0)
#घोषणा AD7877_REF(x)			((x & 0x1) << 2)
#घोषणा AD7877_POL(x)			((x & 0x1) << 3)
#घोषणा AD7877_FCD(x)			((x & 0x3) << 4)
#घोषणा AD7877_PM(x)			((x & 0x3) << 6)
#घोषणा AD7877_ACQ(x)			((x & 0x3) << 8)
#घोषणा AD7877_AVG(x)			((x & 0x3) << 10)

/* Control REG 1 */
#घोषणा	AD7877_SER			(1 << 11)	/* non-dअगरferential */
#घोषणा	AD7877_DFR			(0 << 11)	/* dअगरferential */

#घोषणा AD7877_MODE_NOC  (0)	/* Do not convert */
#घोषणा AD7877_MODE_SCC  (1)	/* Single channel conversion */
#घोषणा AD7877_MODE_SEQ0 (2)	/* Sequence 0 in Slave Mode */
#घोषणा AD7877_MODE_SEQ1 (3)	/* Sequence 1 in Master Mode */

#घोषणा AD7877_CHANADD(x)		((x&0xF)<<7)
#घोषणा AD7877_READADD(x)		((x)<<2)
#घोषणा AD7877_WRITEADD(x)		((x)<<12)

#घोषणा AD7877_READ_CHAN(x) (AD7877_WRITEADD(AD7877_REG_CTRL1) | AD7877_SER | \
		AD7877_MODE_SCC | AD7877_CHANADD(AD7877_REG_ ## x) | \
		AD7877_READADD(AD7877_REG_ ## x))

#घोषणा AD7877_MM_SEQUENCE (AD7877_SEQ_YPLUS_BIT | AD7877_SEQ_XPLUS_BIT | \
		AD7877_SEQ_Z2_BIT | AD7877_SEQ_Z1_BIT)

/*
 * Non-touchscreen sensors only use single-ended conversions.
 */

काष्ठा ser_req अणु
	u16			reset;
	u16			ref_on;
	u16			command;
	काष्ठा spi_message	msg;
	काष्ठा spi_transfer	xfer[6];

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	u16 sample ____cacheline_aligned;
पूर्ण;

काष्ठा ad7877 अणु
	काष्ठा input_dev	*input;
	अक्षर			phys[32];

	काष्ठा spi_device	*spi;
	u16			model;
	u16			vref_delay_usecs;
	u16			x_plate_ohms;
	u16			pressure_max;

	u16			cmd_crtl1;
	u16			cmd_crtl2;
	u16			cmd_dummy;
	u16			dac;

	u8			stopacq_polarity;
	u8			first_conversion_delay;
	u8			acquisition_समय;
	u8			averaging;
	u8			pen_करोwn_acc_पूर्णांकerval;

	काष्ठा spi_transfer	xfer[AD7877_NR_SENSE + 2];
	काष्ठा spi_message	msg;

	काष्ठा mutex		mutex;
	bool			disabled;	/* P: mutex */
	bool			gpio3;		/* P: mutex */
	bool			gpio4;		/* P: mutex */

	spinlock_t		lock;
	काष्ठा समयr_list	समयr;		/* P: lock */

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	u16 conversion_data[AD7877_NR_SENSE] ____cacheline_aligned;
पूर्ण;

अटल bool gpio3;
module_param(gpio3, bool, 0);
MODULE_PARM_DESC(gpio3, "If gpio3 is set to 1 AUX3 acts as GPIO3");

अटल पूर्णांक ad7877_पढ़ो(काष्ठा spi_device *spi, u16 reg)
अणु
	काष्ठा ser_req *req;
	पूर्णांक status, ret;

	req = kzalloc(माप *req, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	spi_message_init(&req->msg);

	req->command = (u16) (AD7877_WRITEADD(AD7877_REG_CTRL1) |
			AD7877_READADD(reg));
	req->xfer[0].tx_buf = &req->command;
	req->xfer[0].len = 2;
	req->xfer[0].cs_change = 1;

	req->xfer[1].rx_buf = &req->sample;
	req->xfer[1].len = 2;

	spi_message_add_tail(&req->xfer[0], &req->msg);
	spi_message_add_tail(&req->xfer[1], &req->msg);

	status = spi_sync(spi, &req->msg);
	ret = status ? : req->sample;

	kमुक्त(req);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7877_ग_लिखो(काष्ठा spi_device *spi, u16 reg, u16 val)
अणु
	काष्ठा ser_req *req;
	पूर्णांक status;

	req = kzalloc(माप *req, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	spi_message_init(&req->msg);

	req->command = (u16) (AD7877_WRITEADD(reg) | (val & MAX_12BIT));
	req->xfer[0].tx_buf = &req->command;
	req->xfer[0].len = 2;

	spi_message_add_tail(&req->xfer[0], &req->msg);

	status = spi_sync(spi, &req->msg);

	kमुक्त(req);

	वापस status;
पूर्ण

अटल पूर्णांक ad7877_पढ़ो_adc(काष्ठा spi_device *spi, अचिन्हित command)
अणु
	काष्ठा ad7877 *ts = spi_get_drvdata(spi);
	काष्ठा ser_req *req;
	पूर्णांक status;
	पूर्णांक sample;
	पूर्णांक i;

	req = kzalloc(माप *req, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	spi_message_init(&req->msg);

	/* activate reference, so it has समय to settle; */
	req->ref_on = AD7877_WRITEADD(AD7877_REG_CTRL2) |
			 AD7877_POL(ts->stopacq_polarity) |
			 AD7877_AVG(0) | AD7877_PM(2) | AD7877_TMR(0) |
			 AD7877_ACQ(ts->acquisition_समय) | AD7877_FCD(0);

	req->reset = AD7877_WRITEADD(AD7877_REG_CTRL1) | AD7877_MODE_NOC;

	req->command = (u16) command;

	req->xfer[0].tx_buf = &req->reset;
	req->xfer[0].len = 2;
	req->xfer[0].cs_change = 1;

	req->xfer[1].tx_buf = &req->ref_on;
	req->xfer[1].len = 2;
	req->xfer[1].delay.value = ts->vref_delay_usecs;
	req->xfer[1].delay.unit = SPI_DELAY_UNIT_USECS;
	req->xfer[1].cs_change = 1;

	req->xfer[2].tx_buf = &req->command;
	req->xfer[2].len = 2;
	req->xfer[2].delay.value = ts->vref_delay_usecs;
	req->xfer[2].delay.unit = SPI_DELAY_UNIT_USECS;
	req->xfer[2].cs_change = 1;

	req->xfer[3].rx_buf = &req->sample;
	req->xfer[3].len = 2;
	req->xfer[3].cs_change = 1;

	req->xfer[4].tx_buf = &ts->cmd_crtl2;	/*REF OFF*/
	req->xfer[4].len = 2;
	req->xfer[4].cs_change = 1;

	req->xfer[5].tx_buf = &ts->cmd_crtl1;	/*DEFAULT*/
	req->xfer[5].len = 2;

	/* group all the transfers together, so we can't पूर्णांकerfere with
	 * पढ़ोing touchscreen state; disable penirq जबतक sampling
	 */
	क्रम (i = 0; i < 6; i++)
		spi_message_add_tail(&req->xfer[i], &req->msg);

	status = spi_sync(spi, &req->msg);
	sample = req->sample;

	kमुक्त(req);

	वापस status ? : sample;
पूर्ण

अटल पूर्णांक ad7877_process_data(काष्ठा ad7877 *ts)
अणु
	काष्ठा input_dev *input_dev = ts->input;
	अचिन्हित Rt;
	u16 x, y, z1, z2;

	x = ts->conversion_data[AD7877_SEQ_XPOS] & MAX_12BIT;
	y = ts->conversion_data[AD7877_SEQ_YPOS] & MAX_12BIT;
	z1 = ts->conversion_data[AD7877_SEQ_Z1] & MAX_12BIT;
	z2 = ts->conversion_data[AD7877_SEQ_Z2] & MAX_12BIT;

	/*
	 * The samples processed here are alपढ़ोy preprocessed by the AD7877.
	 * The preprocessing function consists of an averaging filter.
	 * The combination of 'first conversion delay' and averaging provides a robust solution,
	 * discarding the spurious noise in the संकेत and keeping only the data of पूर्णांकerest.
	 * The size of the averaging filter is programmable. (dev.platक्रमm_data, see linux/spi/ad7877.h)
	 * Other user-programmable conversion controls include variable acquisition समय,
	 * and first conversion delay. Up to 16 averages can be taken per conversion.
	 */

	अगर (likely(x && z1)) अणु
		/* compute touch pressure resistance using equation #1 */
		Rt = (z2 - z1) * x * ts->x_plate_ohms;
		Rt /= z1;
		Rt = (Rt + 2047) >> 12;

		/*
		 * Sample found inconsistent, pressure is beyond
		 * the maximum. Don't report it to user space.
		 */
		अगर (Rt > ts->pressure_max)
			वापस -EINVAL;

		अगर (!समयr_pending(&ts->समयr))
			input_report_key(input_dev, BTN_TOUCH, 1);

		input_report_असल(input_dev, ABS_X, x);
		input_report_असल(input_dev, ABS_Y, y);
		input_report_असल(input_dev, ABS_PRESSURE, Rt);
		input_sync(input_dev);

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम ad7877_ts_event_release(काष्ठा ad7877 *ts)
अणु
	काष्ठा input_dev *input_dev = ts->input;

	input_report_असल(input_dev, ABS_PRESSURE, 0);
	input_report_key(input_dev, BTN_TOUCH, 0);
	input_sync(input_dev);
पूर्ण

अटल व्योम ad7877_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ad7877 *ts = from_समयr(ts, t, समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ts->lock, flags);
	ad7877_ts_event_release(ts);
	spin_unlock_irqrestore(&ts->lock, flags);
पूर्ण

अटल irqवापस_t ad7877_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा ad7877 *ts = handle;
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	error = spi_sync(ts->spi, &ts->msg);
	अगर (error) अणु
		dev_err(&ts->spi->dev, "spi_sync --> %d\n", error);
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&ts->lock, flags);
	error = ad7877_process_data(ts);
	अगर (!error)
		mod_समयr(&ts->समयr, jअगरfies + TS_PEN_UP_TIMEOUT);
	spin_unlock_irqrestore(&ts->lock, flags);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ad7877_disable(व्योम *data)
अणु
	काष्ठा ad7877 *ts = data;

	mutex_lock(&ts->mutex);

	अगर (!ts->disabled) अणु
		ts->disabled = true;
		disable_irq(ts->spi->irq);

		अगर (del_समयr_sync(&ts->समयr))
			ad7877_ts_event_release(ts);
	पूर्ण

	/*
	 * We know the chip's in lowघातer mode since we always
	 * leave it that way after every request
	 */

	mutex_unlock(&ts->mutex);
पूर्ण

अटल व्योम ad7877_enable(काष्ठा ad7877 *ts)
अणु
	mutex_lock(&ts->mutex);

	अगर (ts->disabled) अणु
		ts->disabled = false;
		enable_irq(ts->spi->irq);
	पूर्ण

	mutex_unlock(&ts->mutex);
पूर्ण

#घोषणा SHOW(name) अटल sमाप_प्रकार \
name ## _show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	काष्ठा ad7877 *ts = dev_get_drvdata(dev); \
	sमाप_प्रकार v = ad7877_पढ़ो_adc(ts->spi, \
			AD7877_READ_CHAN(name)); \
	अगर (v < 0) \
		वापस v; \
	वापस प्र_लिखो(buf, "%u\n", (अचिन्हित) v); \
पूर्ण \
अटल DEVICE_ATTR(name, S_IRUGO, name ## _show, शून्य);

SHOW(aux1)
SHOW(aux2)
SHOW(aux3)
SHOW(bat1)
SHOW(bat2)
SHOW(temp1)
SHOW(temp2)

अटल sमाप_प्रकार ad7877_disable_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ad7877 *ts = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", ts->disabled);
पूर्ण

अटल sमाप_प्रकार ad7877_disable_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ad7877 *ts = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	अगर (val)
		ad7877_disable(ts);
	अन्यथा
		ad7877_enable(ts);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(disable, 0664, ad7877_disable_show, ad7877_disable_store);

अटल sमाप_प्रकार ad7877_dac_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ad7877 *ts = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", ts->dac);
पूर्ण

अटल sमाप_प्रकार ad7877_dac_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ad7877 *ts = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	mutex_lock(&ts->mutex);
	ts->dac = val & 0xFF;
	ad7877_ग_लिखो(ts->spi, AD7877_REG_DAC, (ts->dac << 4) | AD7877_DAC_CONF);
	mutex_unlock(&ts->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(dac, 0664, ad7877_dac_show, ad7877_dac_store);

अटल sमाप_प्रकार ad7877_gpio3_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ad7877 *ts = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", ts->gpio3);
पूर्ण

अटल sमाप_प्रकार ad7877_gpio3_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ad7877 *ts = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	mutex_lock(&ts->mutex);
	ts->gpio3 = !!val;
	ad7877_ग_लिखो(ts->spi, AD7877_REG_EXTWRITE, AD7877_EXTW_GPIO_DATA |
		 (ts->gpio4 << 4) | (ts->gpio3 << 5));
	mutex_unlock(&ts->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(gpio3, 0664, ad7877_gpio3_show, ad7877_gpio3_store);

अटल sमाप_प्रकार ad7877_gpio4_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ad7877 *ts = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", ts->gpio4);
पूर्ण

अटल sमाप_प्रकार ad7877_gpio4_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ad7877 *ts = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &val);
	अगर (error)
		वापस error;

	mutex_lock(&ts->mutex);
	ts->gpio4 = !!val;
	ad7877_ग_लिखो(ts->spi, AD7877_REG_EXTWRITE, AD7877_EXTW_GPIO_DATA |
		     (ts->gpio4 << 4) | (ts->gpio3 << 5));
	mutex_unlock(&ts->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(gpio4, 0664, ad7877_gpio4_show, ad7877_gpio4_store);

अटल काष्ठा attribute *ad7877_attributes[] = अणु
	&dev_attr_temp1.attr,
	&dev_attr_temp2.attr,
	&dev_attr_aux1.attr,
	&dev_attr_aux2.attr,
	&dev_attr_aux3.attr,
	&dev_attr_bat1.attr,
	&dev_attr_bat2.attr,
	&dev_attr_disable.attr,
	&dev_attr_dac.attr,
	&dev_attr_gpio3.attr,
	&dev_attr_gpio4.attr,
	शून्य
पूर्ण;

अटल umode_t ad7877_attr_is_visible(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, पूर्णांक n)
अणु
	umode_t mode = attr->mode;

	अगर (attr == &dev_attr_aux3.attr) अणु
		अगर (gpio3)
			mode = 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_gpio3.attr) अणु
		अगर (!gpio3)
			mode = 0;
	पूर्ण

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group ad7877_attr_group = अणु
	.is_visible	= ad7877_attr_is_visible,
	.attrs		= ad7877_attributes,
पूर्ण;

अटल व्योम ad7877_setup_ts_def_msg(काष्ठा spi_device *spi, काष्ठा ad7877 *ts)
अणु
	काष्ठा spi_message *m;
	पूर्णांक i;

	ts->cmd_crtl2 = AD7877_WRITEADD(AD7877_REG_CTRL2) |
			AD7877_POL(ts->stopacq_polarity) |
			AD7877_AVG(ts->averaging) | AD7877_PM(1) |
			AD7877_TMR(ts->pen_करोwn_acc_पूर्णांकerval) |
			AD7877_ACQ(ts->acquisition_समय) |
			AD7877_FCD(ts->first_conversion_delay);

	ad7877_ग_लिखो(spi, AD7877_REG_CTRL2, ts->cmd_crtl2);

	ts->cmd_crtl1 = AD7877_WRITEADD(AD7877_REG_CTRL1) |
			AD7877_READADD(AD7877_REG_XPLUS-1) |
			AD7877_MODE_SEQ1 | AD7877_DFR;

	ad7877_ग_लिखो(spi, AD7877_REG_CTRL1, ts->cmd_crtl1);

	ts->cmd_dummy = 0;

	m = &ts->msg;

	spi_message_init(m);

	m->context = ts;

	ts->xfer[0].tx_buf = &ts->cmd_crtl1;
	ts->xfer[0].len = 2;
	ts->xfer[0].cs_change = 1;

	spi_message_add_tail(&ts->xfer[0], m);

	ts->xfer[1].tx_buf = &ts->cmd_dummy; /* Send ZERO */
	ts->xfer[1].len = 2;
	ts->xfer[1].cs_change = 1;

	spi_message_add_tail(&ts->xfer[1], m);

	क्रम (i = 0; i < AD7877_NR_SENSE; i++) अणु
		ts->xfer[i + 2].rx_buf = &ts->conversion_data[AD7877_SEQ_YPOS + i];
		ts->xfer[i + 2].len = 2;
		अगर (i < (AD7877_NR_SENSE - 1))
			ts->xfer[i + 2].cs_change = 1;
		spi_message_add_tail(&ts->xfer[i + 2], m);
	पूर्ण
पूर्ण

अटल पूर्णांक ad7877_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad7877			*ts;
	काष्ठा input_dev		*input_dev;
	काष्ठा ad7877_platक्रमm_data	*pdata = dev_get_platdata(&spi->dev);
	पूर्णांक				err;
	u16				verअगरy;

	अगर (!spi->irq) अणु
		dev_dbg(&spi->dev, "no IRQ?\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!pdata) अणु
		dev_dbg(&spi->dev, "no platform data?\n");
		वापस -ENODEV;
	पूर्ण

	/* करोn't exceed max specअगरied SPI CLK frequency */
	अगर (spi->max_speed_hz > MAX_SPI_FREQ_HZ) अणु
		dev_dbg(&spi->dev, "SPI CLK %d Hz?\n",spi->max_speed_hz);
		वापस -EINVAL;
	पूर्ण

	spi->bits_per_word = 16;
	err = spi_setup(spi);
	अगर (err) अणु
		dev_dbg(&spi->dev, "spi master doesn't support 16 bits/word\n");
		वापस err;
	पूर्ण

	ts = devm_kzalloc(&spi->dev, माप(काष्ठा ad7877), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	input_dev = devm_input_allocate_device(&spi->dev);
	अगर (!input_dev)
		वापस -ENOMEM;

	err = devm_add_action_or_reset(&spi->dev, ad7877_disable, ts);
	अगर (err)
		वापस err;

	spi_set_drvdata(spi, ts);
	ts->spi = spi;
	ts->input = input_dev;

	समयr_setup(&ts->समयr, ad7877_समयr, 0);
	mutex_init(&ts->mutex);
	spin_lock_init(&ts->lock);

	ts->model = pdata->model ? : 7877;
	ts->vref_delay_usecs = pdata->vref_delay_usecs ? : 100;
	ts->x_plate_ohms = pdata->x_plate_ohms ? : 400;
	ts->pressure_max = pdata->pressure_max ? : ~0;

	ts->stopacq_polarity = pdata->stopacq_polarity;
	ts->first_conversion_delay = pdata->first_conversion_delay;
	ts->acquisition_समय = pdata->acquisition_समय;
	ts->averaging = pdata->averaging;
	ts->pen_करोwn_acc_पूर्णांकerval = pdata->pen_करोwn_acc_पूर्णांकerval;

	snम_लिखो(ts->phys, माप(ts->phys), "%s/input0", dev_name(&spi->dev));

	input_dev->name = "AD7877 Touchscreen";
	input_dev->phys = ts->phys;
	input_dev->dev.parent = &spi->dev;

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(ABS_X, input_dev->असलbit);
	__set_bit(ABS_Y, input_dev->असलbit);
	__set_bit(ABS_PRESSURE, input_dev->असलbit);

	input_set_असल_params(input_dev, ABS_X,
			pdata->x_min ? : 0,
			pdata->x_max ? : MAX_12BIT,
			0, 0);
	input_set_असल_params(input_dev, ABS_Y,
			pdata->y_min ? : 0,
			pdata->y_max ? : MAX_12BIT,
			0, 0);
	input_set_असल_params(input_dev, ABS_PRESSURE,
			pdata->pressure_min, pdata->pressure_max, 0, 0);

	ad7877_ग_लिखो(spi, AD7877_REG_SEQ1, AD7877_MM_SEQUENCE);

	verअगरy = ad7877_पढ़ो(spi, AD7877_REG_SEQ1);

	अगर (verअगरy != AD7877_MM_SEQUENCE) अणु
		dev_err(&spi->dev, "%s: Failed to probe %s\n",
			dev_name(&spi->dev), input_dev->name);
		वापस -ENODEV;
	पूर्ण

	अगर (gpio3)
		ad7877_ग_लिखो(spi, AD7877_REG_EXTWRITE, AD7877_EXTW_GPIO_3_CONF);

	ad7877_setup_ts_def_msg(spi, ts);

	/* Request AD7877 /DAV GPIO पूर्णांकerrupt */

	err = devm_request_thपढ़ोed_irq(&spi->dev, spi->irq, शून्य, ad7877_irq,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					spi->dev.driver->name, ts);
	अगर (err) अणु
		dev_dbg(&spi->dev, "irq %d busy?\n", spi->irq);
		वापस err;
	पूर्ण

	err = devm_device_add_group(&spi->dev, &ad7877_attr_group);
	अगर (err)
		वापस err;

	err = input_रेजिस्टर_device(input_dev);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ad7877_suspend(काष्ठा device *dev)
अणु
	काष्ठा ad7877 *ts = dev_get_drvdata(dev);

	ad7877_disable(ts);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ad7877_resume(काष्ठा device *dev)
अणु
	काष्ठा ad7877 *ts = dev_get_drvdata(dev);

	ad7877_enable(ts);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ad7877_pm, ad7877_suspend, ad7877_resume);

अटल काष्ठा spi_driver ad7877_driver = अणु
	.driver = अणु
		.name	= "ad7877",
		.pm	= &ad7877_pm,
	पूर्ण,
	.probe		= ad7877_probe,
पूर्ण;

module_spi_driver(ad7877_driver);

MODULE_AUTHOR("Michael Hennerich <hennerich@blackfin.uclinux.org>");
MODULE_DESCRIPTION("AD7877 touchscreen Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:ad7877");
