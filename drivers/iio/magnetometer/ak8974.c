<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Asahi Kasei EMD Corporation AK8974
 * and Aichi Steel AMI305 magnetometer chips.
 * Based on a patch from Samu Onkalo and the AK8975 IIO driver.
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2010 NVIDIA Corporation.
 * Copyright (C) 2016 Linaro Ltd.
 *
 * Author: Samu Onkalo <samu.p.onkalo@nokia.com>
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h> /* For irq_get_irq_data() */
#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

/*
 * 16-bit रेजिस्टरs are little-endian. LSB is at the address defined below
 * and MSB is at the next higher address.
 */

/* These रेजिस्टरs are common क्रम AK8974 and AMI30x */
#घोषणा AK8974_SELFTEST		0x0C
#घोषणा AK8974_SELFTEST_IDLE	0x55
#घोषणा AK8974_SELFTEST_OK	0xAA

#घोषणा AK8974_INFO		0x0D

#घोषणा AK8974_WHOAMI		0x0F
#घोषणा AK8974_WHOAMI_VALUE_AMI306 0x46
#घोषणा AK8974_WHOAMI_VALUE_AMI305 0x47
#घोषणा AK8974_WHOAMI_VALUE_AK8974 0x48
#घोषणा AK8974_WHOAMI_VALUE_HSCDTD008A 0x49

#घोषणा AK8974_DATA_X		0x10
#घोषणा AK8974_DATA_Y		0x12
#घोषणा AK8974_DATA_Z		0x14
#घोषणा AK8974_INT_SRC		0x16
#घोषणा AK8974_STATUS		0x18
#घोषणा AK8974_INT_CLEAR	0x1A
#घोषणा AK8974_CTRL1		0x1B
#घोषणा AK8974_CTRL2		0x1C
#घोषणा AK8974_CTRL3		0x1D
#घोषणा AK8974_INT_CTRL		0x1E
#घोषणा AK8974_INT_THRES	0x26  /* Absolute any axis value threshold */
#घोषणा AK8974_PRESET		0x30

/* AK8974-specअगरic offsets */
#घोषणा AK8974_OFFSET_X		0x20
#घोषणा AK8974_OFFSET_Y		0x22
#घोषणा AK8974_OFFSET_Z		0x24
/* AMI305-specअगरic offsets */
#घोषणा AMI305_OFFSET_X		0x6C
#घोषणा AMI305_OFFSET_Y		0x72
#घोषणा AMI305_OFFSET_Z		0x78

/* Dअगरferent temperature रेजिस्टरs */
#घोषणा AK8974_TEMP		0x31
#घोषणा AMI305_TEMP		0x60

/* AMI306-specअगरic control रेजिस्टर */
#घोषणा AMI306_CTRL4		0x5C

/* AMI306 factory calibration data */

/* fine axis sensitivity */
#घोषणा AMI306_FINEOUTPUT_X	0x90
#घोषणा AMI306_FINEOUTPUT_Y	0x92
#घोषणा AMI306_FINEOUTPUT_Z	0x94

/* axis sensitivity */
#घोषणा AMI306_SENS_X		0x96
#घोषणा AMI306_SENS_Y		0x98
#घोषणा AMI306_SENS_Z		0x9A

/* axis cross-पूर्णांकerference */
#घोषणा AMI306_GAIN_PARA_XZ	0x9C
#घोषणा AMI306_GAIN_PARA_XY	0x9D
#घोषणा AMI306_GAIN_PARA_YZ	0x9E
#घोषणा AMI306_GAIN_PARA_YX	0x9F
#घोषणा AMI306_GAIN_PARA_ZY	0xA0
#घोषणा AMI306_GAIN_PARA_ZX	0xA1

/* offset at ZERO magnetic field */
#घोषणा AMI306_OFFZERO_X	0xF8
#घोषणा AMI306_OFFZERO_Y	0xFA
#घोषणा AMI306_OFFZERO_Z	0xFC


#घोषणा AK8974_INT_X_HIGH	BIT(7) /* Axis over +threshold  */
#घोषणा AK8974_INT_Y_HIGH	BIT(6)
#घोषणा AK8974_INT_Z_HIGH	BIT(5)
#घोषणा AK8974_INT_X_LOW	BIT(4) /* Axis below -threshold	*/
#घोषणा AK8974_INT_Y_LOW	BIT(3)
#घोषणा AK8974_INT_Z_LOW	BIT(2)
#घोषणा AK8974_INT_RANGE	BIT(1) /* Range overflow (any axis) */

#घोषणा AK8974_STATUS_DRDY	BIT(6) /* Data पढ़ोy */
#घोषणा AK8974_STATUS_OVERRUN	BIT(5) /* Data overrun */
#घोषणा AK8974_STATUS_INT	BIT(4) /* Interrupt occurred */

#घोषणा AK8974_CTRL1_POWER	BIT(7) /* 0 = standby; 1 = active */
#घोषणा AK8974_CTRL1_RATE	BIT(4) /* 0 = 10 Hz; 1 = 20 Hz	 */
#घोषणा AK8974_CTRL1_FORCE_EN	BIT(1) /* 0 = normal; 1 = क्रमce	 */
#घोषणा AK8974_CTRL1_MODE2	BIT(0) /* 0 */

#घोषणा AK8974_CTRL2_INT_EN	BIT(4)  /* 1 = enable पूर्णांकerrupts	      */
#घोषणा AK8974_CTRL2_DRDY_EN	BIT(3)  /* 1 = enable data पढ़ोy संकेत */
#घोषणा AK8974_CTRL2_DRDY_POL	BIT(2)  /* 1 = data पढ़ोy active high   */
#घोषणा AK8974_CTRL2_RESDEF	(AK8974_CTRL2_DRDY_POL)

#घोषणा AK8974_CTRL3_RESET	BIT(7) /* Software reset		  */
#घोषणा AK8974_CTRL3_FORCE	BIT(6) /* Start क्रमced measurement */
#घोषणा AK8974_CTRL3_SELFTEST	BIT(4) /* Set selftest रेजिस्टर	  */
#घोषणा AK8974_CTRL3_RESDEF	0x00

#घोषणा AK8974_INT_CTRL_XEN	BIT(7) /* Enable पूर्णांकerrupt क्रम this axis */
#घोषणा AK8974_INT_CTRL_YEN	BIT(6)
#घोषणा AK8974_INT_CTRL_ZEN	BIT(5)
#घोषणा AK8974_INT_CTRL_XYZEN	(BIT(7)|BIT(6)|BIT(5))
#घोषणा AK8974_INT_CTRL_POL	BIT(3) /* 0 = active low; 1 = active high */
#घोषणा AK8974_INT_CTRL_PULSE	BIT(1) /* 0 = latched; 1 = pulse (50 usec) */
#घोषणा AK8974_INT_CTRL_RESDEF	(AK8974_INT_CTRL_XYZEN | AK8974_INT_CTRL_POL)

/* HSCDTD008A-specअगरic control रेजिस्टर */
#घोषणा HSCDTD008A_CTRL4	0x1E
#घोषणा HSCDTD008A_CTRL4_MMD	BIT(7)	/* must be set to 1 */
#घोषणा HSCDTD008A_CTRL4_RANGE	BIT(4)	/* 0 = 14-bit output; 1 = 15-bit output */
#घोषणा HSCDTD008A_CTRL4_RESDEF	(HSCDTD008A_CTRL4_MMD | HSCDTD008A_CTRL4_RANGE)

/* The AMI305 has elaborate FW version and serial number रेजिस्टरs */
#घोषणा AMI305_VER		0xE8
#घोषणा AMI305_SN		0xEA

#घोषणा AK8974_MAX_RANGE	2048

#घोषणा AK8974_POWERON_DELAY	50
#घोषणा AK8974_ACTIVATE_DELAY	1
#घोषणा AK8974_SELFTEST_DELAY	1
/*
 * Set the स्वतःsuspend to two orders of magnitude larger than the घातeron
 * delay to make sane reasonable घातer tradeoff savings (5 seconds in
 * this हाल).
 */
#घोषणा AK8974_AUTOSUSPEND_DELAY 5000

#घोषणा AK8974_MEASTIME		3

#घोषणा AK8974_PWR_ON		1
#घोषणा AK8974_PWR_OFF		0

/**
 * काष्ठा ak8974 - state container क्रम the AK8974 driver
 * @i2c: parent I2C client
 * @orientation: mounting matrix, flipped axis etc
 * @map: regmap to access the AK8974 रेजिस्टरs over I2C
 * @regs: the avdd and dvdd घातer regulators
 * @name: the name of the part
 * @variant: the whoami ID value (क्रम selecting code paths)
 * @lock: locks the magnetometer क्रम exclusive use during a measurement
 * @drdy_irq: uses the DRDY IRQ line
 * @drdy_complete: completion क्रम DRDY
 * @drdy_active_low: the DRDY IRQ is active low
 * @scan: बारtamps
 */
काष्ठा ak8974 अणु
	काष्ठा i2c_client *i2c;
	काष्ठा iio_mount_matrix orientation;
	काष्ठा regmap *map;
	काष्ठा regulator_bulk_data regs[2];
	स्थिर अक्षर *name;
	u8 variant;
	काष्ठा mutex lock;
	bool drdy_irq;
	काष्ठा completion drdy_complete;
	bool drdy_active_low;
	/* Ensure बारtamp is naturally aligned */
	काष्ठा अणु
		__le16 channels[3];
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

अटल स्थिर अक्षर ak8974_reg_avdd[] = "avdd";
अटल स्थिर अक्षर ak8974_reg_dvdd[] = "dvdd";

अटल पूर्णांक ak8974_get_u16_val(काष्ठा ak8974 *ak8974, u8 reg, u16 *val)
अणु
	पूर्णांक ret;
	__le16 bulk;

	ret = regmap_bulk_पढ़ो(ak8974->map, reg, &bulk, 2);
	अगर (ret)
		वापस ret;
	*val = le16_to_cpu(bulk);

	वापस 0;
पूर्ण

अटल पूर्णांक ak8974_set_u16_val(काष्ठा ak8974 *ak8974, u8 reg, u16 val)
अणु
	__le16 bulk = cpu_to_le16(val);

	वापस regmap_bulk_ग_लिखो(ak8974->map, reg, &bulk, 2);
पूर्ण

अटल पूर्णांक ak8974_set_घातer(काष्ठा ak8974 *ak8974, bool mode)
अणु
	पूर्णांक ret;
	u8 val;

	val = mode ? AK8974_CTRL1_POWER : 0;
	val |= AK8974_CTRL1_FORCE_EN;
	ret = regmap_ग_लिखो(ak8974->map, AK8974_CTRL1, val);
	अगर (ret < 0)
		वापस ret;

	अगर (mode)
		msleep(AK8974_ACTIVATE_DELAY);

	वापस 0;
पूर्ण

अटल पूर्णांक ak8974_reset(काष्ठा ak8974 *ak8974)
अणु
	पूर्णांक ret;

	/* Power on to get रेजिस्टर access. Sets CTRL1 reg to reset state */
	ret = ak8974_set_घातer(ak8974, AK8974_PWR_ON);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(ak8974->map, AK8974_CTRL2, AK8974_CTRL2_RESDEF);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(ak8974->map, AK8974_CTRL3, AK8974_CTRL3_RESDEF);
	अगर (ret)
		वापस ret;
	अगर (ak8974->variant != AK8974_WHOAMI_VALUE_HSCDTD008A) अणु
		ret = regmap_ग_लिखो(ak8974->map, AK8974_INT_CTRL,
				   AK8974_INT_CTRL_RESDEF);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(ak8974->map, HSCDTD008A_CTRL4,
				   HSCDTD008A_CTRL4_RESDEF);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* After reset, घातer off is शेष state */
	वापस ak8974_set_घातer(ak8974, AK8974_PWR_OFF);
पूर्ण

अटल पूर्णांक ak8974_configure(काष्ठा ak8974 *ak8974)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(ak8974->map, AK8974_CTRL2, AK8974_CTRL2_DRDY_EN |
			   AK8974_CTRL2_INT_EN);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(ak8974->map, AK8974_CTRL3, 0);
	अगर (ret)
		वापस ret;
	अगर (ak8974->variant == AK8974_WHOAMI_VALUE_AMI306) अणु
		/* magic from datasheet: set high-speed measurement mode */
		ret = ak8974_set_u16_val(ak8974, AMI306_CTRL4, 0xA07E);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (ak8974->variant == AK8974_WHOAMI_VALUE_HSCDTD008A)
		वापस 0;
	ret = regmap_ग_लिखो(ak8974->map, AK8974_INT_CTRL, AK8974_INT_CTRL_POL);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(ak8974->map, AK8974_PRESET, 0);
पूर्ण

अटल पूर्णांक ak8974_trigmeas(काष्ठा ak8974 *ak8974)
अणु
	अचिन्हित पूर्णांक clear;
	u8 mask;
	u8 val;
	पूर्णांक ret;

	/* Clear any previous measurement overflow status */
	ret = regmap_पढ़ो(ak8974->map, AK8974_INT_CLEAR, &clear);
	अगर (ret)
		वापस ret;

	/* If we have a DRDY IRQ line, use it */
	अगर (ak8974->drdy_irq) अणु
		mask = AK8974_CTRL2_INT_EN |
			AK8974_CTRL2_DRDY_EN |
			AK8974_CTRL2_DRDY_POL;
		val = AK8974_CTRL2_DRDY_EN;

		अगर (!ak8974->drdy_active_low)
			val |= AK8974_CTRL2_DRDY_POL;

		init_completion(&ak8974->drdy_complete);
		ret = regmap_update_bits(ak8974->map, AK8974_CTRL2,
					 mask, val);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Force a measurement */
	वापस regmap_update_bits(ak8974->map,
				  AK8974_CTRL3,
				  AK8974_CTRL3_FORCE,
				  AK8974_CTRL3_FORCE);
पूर्ण

अटल पूर्णांक ak8974_aरुको_drdy(काष्ठा ak8974 *ak8974)
अणु
	पूर्णांक समयout = 2;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (ak8974->drdy_irq) अणु
		ret = रुको_क्रम_completion_समयout(&ak8974->drdy_complete,
					1 + msecs_to_jअगरfies(1000));
		अगर (!ret) अणु
			dev_err(&ak8974->i2c->dev,
				"timeout waiting for DRDY IRQ\n");
			वापस -ETIMEDOUT;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Default delay-based poll loop */
	करो अणु
		msleep(AK8974_MEASTIME);
		ret = regmap_पढ़ो(ak8974->map, AK8974_STATUS, &val);
		अगर (ret < 0)
			वापस ret;
		अगर (val & AK8974_STATUS_DRDY)
			वापस 0;
	पूर्ण जबतक (--समयout);

	dev_err(&ak8974->i2c->dev, "timeout waiting for DRDY\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ak8974_getresult(काष्ठा ak8974 *ak8974, __le16 *result)
अणु
	अचिन्हित पूर्णांक src;
	पूर्णांक ret;

	ret = ak8974_aरुको_drdy(ak8974);
	अगर (ret)
		वापस ret;
	ret = regmap_पढ़ो(ak8974->map, AK8974_INT_SRC, &src);
	अगर (ret < 0)
		वापस ret;

	/* Out of range overflow! Strong magnet बंद? */
	अगर (src & AK8974_INT_RANGE) अणु
		dev_err(&ak8974->i2c->dev,
			"range overflow in sensor\n");
		वापस -दुस्फल;
	पूर्ण

	ret = regmap_bulk_पढ़ो(ak8974->map, AK8974_DATA_X, result, 6);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल irqवापस_t ak8974_drdy_irq(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा ak8974 *ak8974 = d;

	अगर (!ak8974->drdy_irq)
		वापस IRQ_NONE;

	/* TODO: बारtamp here to get good measurement stamps */
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t ak8974_drdy_irq_thपढ़ो(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा ak8974 *ak8974 = d;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* Check अगर this was a DRDY from us */
	ret = regmap_पढ़ो(ak8974->map, AK8974_STATUS, &val);
	अगर (ret < 0) अणु
		dev_err(&ak8974->i2c->dev, "error reading DRDY status\n");
		वापस IRQ_HANDLED;
	पूर्ण
	अगर (val & AK8974_STATUS_DRDY) अणु
		/* Yes this was our IRQ */
		complete(&ak8974->drdy_complete);
		वापस IRQ_HANDLED;
	पूर्ण

	/* We may be on a shared IRQ, let the next client check */
	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक ak8974_selftest(काष्ठा ak8974 *ak8974)
अणु
	काष्ठा device *dev = &ak8974->i2c->dev;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(ak8974->map, AK8974_SELFTEST, &val);
	अगर (ret)
		वापस ret;
	अगर (val != AK8974_SELFTEST_IDLE) अणु
		dev_err(dev, "selftest not idle before test\n");
		वापस -EIO;
	पूर्ण

	/* Trigger self-test */
	ret = regmap_update_bits(ak8974->map,
			AK8974_CTRL3,
			AK8974_CTRL3_SELFTEST,
			AK8974_CTRL3_SELFTEST);
	अगर (ret) अणु
		dev_err(dev, "could not write CTRL3\n");
		वापस ret;
	पूर्ण

	msleep(AK8974_SELFTEST_DELAY);

	ret = regmap_पढ़ो(ak8974->map, AK8974_SELFTEST, &val);
	अगर (ret)
		वापस ret;
	अगर (val != AK8974_SELFTEST_OK) अणु
		dev_err(dev, "selftest result NOT OK (%02x)\n", val);
		वापस -EIO;
	पूर्ण

	ret = regmap_पढ़ो(ak8974->map, AK8974_SELFTEST, &val);
	अगर (ret)
		वापस ret;
	अगर (val != AK8974_SELFTEST_IDLE) अणु
		dev_err(dev, "selftest not idle after test (%02x)\n", val);
		वापस -EIO;
	पूर्ण
	dev_dbg(dev, "passed self-test\n");

	वापस 0;
पूर्ण

अटल व्योम ak8974_पढ़ो_calib_data(काष्ठा ak8974 *ak8974, अचिन्हित पूर्णांक reg,
				   __le16 *tab, माप_प्रकार tab_size)
अणु
	पूर्णांक ret = regmap_bulk_पढ़ो(ak8974->map, reg, tab, tab_size);
	अगर (ret) अणु
		स_रखो(tab, 0xFF, tab_size);
		dev_warn(&ak8974->i2c->dev,
			 "can't read calibration data (regs %u..%zu): %d\n",
			 reg, reg + tab_size - 1, ret);
	पूर्ण अन्यथा अणु
		add_device_अक्रमomness(tab, tab_size);
	पूर्ण
पूर्ण

अटल पूर्णांक ak8974_detect(काष्ठा ak8974 *ak8974)
अणु
	अचिन्हित पूर्णांक whoami;
	स्थिर अक्षर *name;
	पूर्णांक ret;
	अचिन्हित पूर्णांक fw;
	u16 sn;

	ret = regmap_पढ़ो(ak8974->map, AK8974_WHOAMI, &whoami);
	अगर (ret)
		वापस ret;

	name = "ami305";

	चयन (whoami) अणु
	हाल AK8974_WHOAMI_VALUE_AMI306:
		name = "ami306";
		fallthrough;
	हाल AK8974_WHOAMI_VALUE_AMI305:
		ret = regmap_पढ़ो(ak8974->map, AMI305_VER, &fw);
		अगर (ret)
			वापस ret;
		fw &= 0x7f; /* only bits 0 thru 6 valid */
		ret = ak8974_get_u16_val(ak8974, AMI305_SN, &sn);
		अगर (ret)
			वापस ret;
		add_device_अक्रमomness(&sn, माप(sn));
		dev_info(&ak8974->i2c->dev,
			 "detected %s, FW ver %02x, S/N: %04x\n",
			 name, fw, sn);
		अवरोध;
	हाल AK8974_WHOAMI_VALUE_AK8974:
		name = "ak8974";
		dev_info(&ak8974->i2c->dev, "detected AK8974\n");
		अवरोध;
	हाल AK8974_WHOAMI_VALUE_HSCDTD008A:
		name = "hscdtd008a";
		dev_info(&ak8974->i2c->dev, "detected hscdtd008a\n");
		अवरोध;
	शेष:
		dev_err(&ak8974->i2c->dev, "unsupported device (%02x) ",
			whoami);
		वापस -ENODEV;
	पूर्ण

	ak8974->name = name;
	ak8974->variant = whoami;

	अगर (whoami == AK8974_WHOAMI_VALUE_AMI306) अणु
		__le16 fab_data1[9], fab_data2[3];
		पूर्णांक i;

		ak8974_पढ़ो_calib_data(ak8974, AMI306_FINEOUTPUT_X,
				       fab_data1, माप(fab_data1));
		ak8974_पढ़ो_calib_data(ak8974, AMI306_OFFZERO_X,
				       fab_data2, माप(fab_data2));

		क्रम (i = 0; i < 3; ++i) अणु
			अटल स्थिर अक्षर axis[3] = "XYZ";
			अटल स्थिर अक्षर pgaxis[6] = "ZYZXYX";
			अचिन्हित offz = le16_to_cpu(fab_data2[i]) & 0x7F;
			अचिन्हित fine = le16_to_cpu(fab_data1[i]);
			अचिन्हित sens = le16_to_cpu(fab_data1[i + 3]);
			अचिन्हित pgain1 = le16_to_cpu(fab_data1[i + 6]);
			अचिन्हित pgain2 = pgain1 >> 8;

			pgain1 &= 0xFF;

			dev_info(&ak8974->i2c->dev,
				 "factory calibration for axis %c: offz=%u sens=%u fine=%u pga%c=%u pga%c=%u\n",
				 axis[i], offz, sens, fine, pgaxis[i * 2],
				 pgain1, pgaxis[i * 2 + 1], pgain2);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ak8974_measure_channel(काष्ठा ak8974 *ak8974, अचिन्हित दीर्घ address,
				  पूर्णांक *val)
अणु
	__le16 hw_values[3];
	पूर्णांक ret;

	pm_runसमय_get_sync(&ak8974->i2c->dev);
	mutex_lock(&ak8974->lock);

	/*
	 * We पढ़ो all axes and discard all but one, क्रम optimized
	 * पढ़ोing, use the triggered buffer.
	 */
	ret = ak8974_trigmeas(ak8974);
	अगर (ret)
		जाओ out_unlock;
	ret = ak8974_getresult(ak8974, hw_values);
	अगर (ret)
		जाओ out_unlock;
	/*
	 * This explicit cast to (s16) is necessary as the measurement
	 * is करोne in 2's complement with positive and negative values.
	 * The follwing assignment to *val will then convert the चिन्हित
	 * s16 value to a चिन्हित पूर्णांक value.
	 */
	*val = (s16)le16_to_cpu(hw_values[address]);
out_unlock:
	mutex_unlock(&ak8974->lock);
	pm_runसमय_mark_last_busy(&ak8974->i2c->dev);
	pm_runसमय_put_स्वतःsuspend(&ak8974->i2c->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक ak8974_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2,
			   दीर्घ mask)
अणु
	काष्ठा ak8974 *ak8974 = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->address > 2) अणु
			dev_err(&ak8974->i2c->dev, "faulty channel address\n");
			वापस -EIO;
		पूर्ण
		ret = ak8974_measure_channel(ak8974, chan->address, val);
		अगर (ret)
			वापस ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (ak8974->variant) अणु
		हाल AK8974_WHOAMI_VALUE_AMI306:
		हाल AK8974_WHOAMI_VALUE_AMI305:
			/*
			 * The datasheet क्रम AMI305 and AMI306, page 6
			 * specअगरies the range of the sensor to be
			 * +/- 12 Gauss.
			 */
			*val = 12;
			/*
			 * 12 bits are used, +/- 2^11
			 * [ -2048 .. 2047 ] (manual page 20)
			 * [ 0xf800 .. 0x07ff ]
			 */
			*val2 = 11;
			वापस IIO_VAL_FRACTIONAL_LOG2;
		हाल AK8974_WHOAMI_VALUE_HSCDTD008A:
			/*
			 * The datasheet क्रम HSCDTF008A, page 3 specअगरies the
			 * range of the sensor as +/- 2.4 mT per axis, which
			 * corresponds to +/- 2400 uT = +/- 24 Gauss.
			 */
			*val = 24;
			/*
			 * 15 bits are used (set up in CTRL4), +/- 2^14
			 * [ -16384 .. 16383 ] (manual page 24)
			 * [ 0xc000 .. 0x3fff ]
			 */
			*val2 = 14;
			वापस IIO_VAL_FRACTIONAL_LOG2;
		शेष:
			/* GUESSING +/- 12 Gauss */
			*val = 12;
			/* GUESSING 12 bits ADC +/- 2^11 */
			*val2 = 11;
			वापस IIO_VAL_FRACTIONAL_LOG2;
		पूर्ण
		अवरोध;
	शेष:
		/* Unknown request */
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम ak8974_fill_buffer(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ak8974 *ak8974 = iio_priv(indio_dev);
	पूर्णांक ret;

	pm_runसमय_get_sync(&ak8974->i2c->dev);
	mutex_lock(&ak8974->lock);

	ret = ak8974_trigmeas(ak8974);
	अगर (ret) अणु
		dev_err(&ak8974->i2c->dev, "error triggering measure\n");
		जाओ out_unlock;
	पूर्ण
	ret = ak8974_getresult(ak8974, ak8974->scan.channels);
	अगर (ret) अणु
		dev_err(&ak8974->i2c->dev, "error getting measures\n");
		जाओ out_unlock;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, &ak8974->scan,
					   iio_get_समय_ns(indio_dev));

 out_unlock:
	mutex_unlock(&ak8974->lock);
	pm_runसमय_mark_last_busy(&ak8974->i2c->dev);
	pm_runसमय_put_स्वतःsuspend(&ak8974->i2c->dev);
पूर्ण

अटल irqवापस_t ak8974_handle_trigger(पूर्णांक irq, व्योम *p)
अणु
	स्थिर काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;

	ak8974_fill_buffer(indio_dev);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_mount_matrix *
ak8974_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ak8974 *ak8974 = iio_priv(indio_dev);

	वापस &ak8974->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info ak8974_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, ak8974_get_mount_matrix),
	अणु पूर्ण,
पूर्ण;

#घोषणा AK8974_AXIS_CHANNEL(axis, index, bits)				\
	अणु								\
		.type = IIO_MAGN,					\
		.modअगरied = 1,						\
		.channel2 = IIO_MOD_##axis,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
			BIT(IIO_CHAN_INFO_SCALE),			\
		.ext_info = ak8974_ext_info,				\
		.address = index,					\
		.scan_index = index,					\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = bits,				\
			.storagebits = 16,				\
			.endianness = IIO_LE				\
		पूर्ण,							\
	पूर्ण

/*
 * We have no datasheet क्रम the AK8974 but we guess that its
 * ADC is 12 bits. The AMI305 and AMI306 certainly has 12bit
 * ADC.
 */
अटल स्थिर काष्ठा iio_chan_spec ak8974_12_bits_channels[] = अणु
	AK8974_AXIS_CHANNEL(X, 0, 12),
	AK8974_AXIS_CHANNEL(Y, 1, 12),
	AK8974_AXIS_CHANNEL(Z, 2, 12),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

/*
 * The HSCDTD008A has 15 bits resolution the way we set it up
 * in CTRL4.
 */
अटल स्थिर काष्ठा iio_chan_spec ak8974_15_bits_channels[] = अणु
	AK8974_AXIS_CHANNEL(X, 0, 15),
	AK8974_AXIS_CHANNEL(Y, 1, 15),
	AK8974_AXIS_CHANNEL(Z, 2, 15),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ ak8974_scan_masks[] = अणु 0x7, 0 पूर्ण;

अटल स्थिर काष्ठा iio_info ak8974_info = अणु
	.पढ़ो_raw = &ak8974_पढ़ो_raw,
पूर्ण;

अटल bool ak8974_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(i2c);
	काष्ठा ak8974 *ak8974 = iio_priv(indio_dev);

	चयन (reg) अणु
	हाल AK8974_CTRL1:
	हाल AK8974_CTRL2:
	हाल AK8974_CTRL3:
	हाल AK8974_INT_CTRL:
	हाल AK8974_INT_THRES:
	हाल AK8974_INT_THRES + 1:
		वापस true;
	हाल AK8974_PRESET:
	हाल AK8974_PRESET + 1:
		वापस ak8974->variant != AK8974_WHOAMI_VALUE_HSCDTD008A;
	हाल AK8974_OFFSET_X:
	हाल AK8974_OFFSET_X + 1:
	हाल AK8974_OFFSET_Y:
	हाल AK8974_OFFSET_Y + 1:
	हाल AK8974_OFFSET_Z:
	हाल AK8974_OFFSET_Z + 1:
		वापस ak8974->variant == AK8974_WHOAMI_VALUE_AK8974 ||
		       ak8974->variant == AK8974_WHOAMI_VALUE_HSCDTD008A;
	हाल AMI305_OFFSET_X:
	हाल AMI305_OFFSET_X + 1:
	हाल AMI305_OFFSET_Y:
	हाल AMI305_OFFSET_Y + 1:
	हाल AMI305_OFFSET_Z:
	हाल AMI305_OFFSET_Z + 1:
		वापस ak8974->variant == AK8974_WHOAMI_VALUE_AMI305 ||
		       ak8974->variant == AK8974_WHOAMI_VALUE_AMI306;
	हाल AMI306_CTRL4:
	हाल AMI306_CTRL4 + 1:
		वापस ak8974->variant == AK8974_WHOAMI_VALUE_AMI306;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool ak8974_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == AK8974_INT_CLEAR;
पूर्ण

अटल स्थिर काष्ठा regmap_config ak8974_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xff,
	.ग_लिखोable_reg = ak8974_ग_लिखोable_reg,
	.precious_reg = ak8974_precious_reg,
पूर्ण;

अटल पूर्णांक ak8974_probe(काष्ठा i2c_client *i2c,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ak8974 *ak8974;
	अचिन्हित दीर्घ irq_trig;
	पूर्णांक irq = i2c->irq;
	पूर्णांक ret;

	/* Register with IIO */
	indio_dev = devm_iio_device_alloc(&i2c->dev, माप(*ak8974));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	ak8974 = iio_priv(indio_dev);
	i2c_set_clientdata(i2c, indio_dev);
	ak8974->i2c = i2c;
	mutex_init(&ak8974->lock);

	ret = iio_पढ़ो_mount_matrix(&i2c->dev, "mount-matrix",
				    &ak8974->orientation);
	अगर (ret)
		वापस ret;

	ak8974->regs[0].supply = ak8974_reg_avdd;
	ak8974->regs[1].supply = ak8974_reg_dvdd;

	ret = devm_regulator_bulk_get(&i2c->dev,
				      ARRAY_SIZE(ak8974->regs),
				      ak8974->regs);
	अगर (ret < 0)
		वापस dev_err_probe(&i2c->dev, ret, "cannot get regulators\n");

	ret = regulator_bulk_enable(ARRAY_SIZE(ak8974->regs), ak8974->regs);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "cannot enable regulators\n");
		वापस ret;
	पूर्ण

	/* Take runसमय PM online */
	pm_runसमय_get_noresume(&i2c->dev);
	pm_runसमय_set_active(&i2c->dev);
	pm_runसमय_enable(&i2c->dev);

	ak8974->map = devm_regmap_init_i2c(i2c, &ak8974_regmap_config);
	अगर (IS_ERR(ak8974->map)) अणु
		dev_err(&i2c->dev, "failed to allocate register map\n");
		pm_runसमय_put_noidle(&i2c->dev);
		pm_runसमय_disable(&i2c->dev);
		वापस PTR_ERR(ak8974->map);
	पूर्ण

	ret = ak8974_set_घातer(ak8974, AK8974_PWR_ON);
	अगर (ret) अणु
		dev_err(&i2c->dev, "could not power on\n");
		जाओ disable_pm;
	पूर्ण

	ret = ak8974_detect(ak8974);
	अगर (ret) अणु
		dev_err(&i2c->dev, "neither AK8974 nor AMI30x found\n");
		जाओ disable_pm;
	पूर्ण

	ret = ak8974_selftest(ak8974);
	अगर (ret)
		dev_err(&i2c->dev, "selftest failed (continuing anyway)\n");

	ret = ak8974_reset(ak8974);
	अगर (ret) अणु
		dev_err(&i2c->dev, "AK8974 reset failed\n");
		जाओ disable_pm;
	पूर्ण

	चयन (ak8974->variant) अणु
	हाल AK8974_WHOAMI_VALUE_AMI306:
	हाल AK8974_WHOAMI_VALUE_AMI305:
		indio_dev->channels = ak8974_12_bits_channels;
		indio_dev->num_channels = ARRAY_SIZE(ak8974_12_bits_channels);
		अवरोध;
	हाल AK8974_WHOAMI_VALUE_HSCDTD008A:
		indio_dev->channels = ak8974_15_bits_channels;
		indio_dev->num_channels = ARRAY_SIZE(ak8974_15_bits_channels);
		अवरोध;
	शेष:
		indio_dev->channels = ak8974_12_bits_channels;
		indio_dev->num_channels = ARRAY_SIZE(ak8974_12_bits_channels);
		अवरोध;
	पूर्ण
	indio_dev->info = &ak8974_info;
	indio_dev->available_scan_masks = ak8974_scan_masks;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->name = ak8974->name;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 ak8974_handle_trigger,
					 शून्य);
	अगर (ret) अणु
		dev_err(&i2c->dev, "triggered buffer setup failed\n");
		जाओ disable_pm;
	पूर्ण

	/* If we have a valid DRDY IRQ, make use of it */
	अगर (irq > 0) अणु
		irq_trig = irqd_get_trigger_type(irq_get_irq_data(irq));
		अगर (irq_trig == IRQF_TRIGGER_RISING) अणु
			dev_info(&i2c->dev, "enable rising edge DRDY IRQ\n");
		पूर्ण अन्यथा अगर (irq_trig == IRQF_TRIGGER_FALLING) अणु
			ak8974->drdy_active_low = true;
			dev_info(&i2c->dev, "enable falling edge DRDY IRQ\n");
		पूर्ण अन्यथा अणु
			irq_trig = IRQF_TRIGGER_RISING;
		पूर्ण
		irq_trig |= IRQF_ONESHOT;
		irq_trig |= IRQF_SHARED;

		ret = devm_request_thपढ़ोed_irq(&i2c->dev,
						irq,
						ak8974_drdy_irq,
						ak8974_drdy_irq_thपढ़ो,
						irq_trig,
						ak8974->name,
						ak8974);
		अगर (ret) अणु
			dev_err(&i2c->dev, "unable to request DRDY IRQ "
				"- proceeding without IRQ\n");
			जाओ no_irq;
		पूर्ण
		ak8974->drdy_irq = true;
	पूर्ण

no_irq:
	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&i2c->dev, "device register failed\n");
		जाओ cleanup_buffer;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&i2c->dev,
					 AK8974_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(&i2c->dev);
	pm_runसमय_put(&i2c->dev);

	वापस 0;

cleanup_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
disable_pm:
	pm_runसमय_put_noidle(&i2c->dev);
	pm_runसमय_disable(&i2c->dev);
	ak8974_set_घातer(ak8974, AK8974_PWR_OFF);
	regulator_bulk_disable(ARRAY_SIZE(ak8974->regs), ak8974->regs);

	वापस ret;
पूर्ण

अटल पूर्णांक ak8974_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(i2c);
	काष्ठा ak8974 *ak8974 = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	pm_runसमय_get_sync(&i2c->dev);
	pm_runसमय_put_noidle(&i2c->dev);
	pm_runसमय_disable(&i2c->dev);
	ak8974_set_घातer(ak8974, AK8974_PWR_OFF);
	regulator_bulk_disable(ARRAY_SIZE(ak8974->regs), ak8974->regs);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ak8974_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा ak8974 *ak8974 =
		iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	ak8974_set_घातer(ak8974, AK8974_PWR_OFF);
	regulator_bulk_disable(ARRAY_SIZE(ak8974->regs), ak8974->regs);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ak8974_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा ak8974 *ak8974 =
		iio_priv(i2c_get_clientdata(to_i2c_client(dev)));
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ak8974->regs), ak8974->regs);
	अगर (ret)
		वापस ret;
	msleep(AK8974_POWERON_DELAY);
	ret = ak8974_set_घातer(ak8974, AK8974_PWR_ON);
	अगर (ret)
		जाओ out_regulator_disable;

	ret = ak8974_configure(ak8974);
	अगर (ret)
		जाओ out_disable_घातer;

	वापस 0;

out_disable_घातer:
	ak8974_set_घातer(ak8974, AK8974_PWR_OFF);
out_regulator_disable:
	regulator_bulk_disable(ARRAY_SIZE(ak8974->regs), ak8974->regs);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ak8974_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(ak8974_runसमय_suspend,
			   ak8974_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ak8974_id[] = अणु
	अणु"ami305", 0 पूर्ण,
	अणु"ami306", 0 पूर्ण,
	अणु"ak8974", 0 पूर्ण,
	अणु"hscdtd008a", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ak8974_id);

अटल स्थिर काष्ठा of_device_id ak8974_of_match[] = अणु
	अणु .compatible = "asahi-kasei,ak8974", पूर्ण,
	अणु .compatible = "alps,hscdtd008a", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ak8974_of_match);

अटल काष्ठा i2c_driver ak8974_driver = अणु
	.driver	 = अणु
		.name	= "ak8974",
		.pm = &ak8974_dev_pm_ops,
		.of_match_table = ak8974_of_match,
	पूर्ण,
	.probe	  = ak8974_probe,
	.हटाओ	  = ak8974_हटाओ,
	.id_table = ak8974_id,
पूर्ण;
module_i2c_driver(ak8974_driver);

MODULE_DESCRIPTION("AK8974 and AMI30x 3-axis magnetometer driver");
MODULE_AUTHOR("Samu Onkalo");
MODULE_AUTHOR("Linus Walleij");
MODULE_LICENSE("GPL v2");
