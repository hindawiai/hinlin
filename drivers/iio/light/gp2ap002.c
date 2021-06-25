<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * These are the two Sharp GP2AP002 variants supported by this driver:
 * GP2AP002A00F Ambient Light and Proximity Sensor
 * GP2AP002S00F Proximity Sensor
 *
 * Copyright (C) 2020 Linaro Ltd.
 * Author: Linus Walleij <linus.walleij@linaro.org>
 *
 * Based partly on the code in Sony Ericssons GP2AP00200F driver by
 * Courtney Cavin and Oskar Andero in drivers/input/misc/gp2ap002a00f.c
 * Based partly on a Samsung misc driver submitted by
 * Donggeun Kim & Minkyu Kang in 2011:
 * https://lore.kernel.org/lkml/1315556546-7445-1-git-send-email-dg77.kim@samsung.com/
 * Based partly on a submission by
 * Jonathan Bakker and Paweध Chmiel in january 2019:
 * https://lore.kernel.org/linux-input/20190125175045.22576-1-pawel.mikolaj.chmiel@gmail.com/
 * Based partly on code from the Samsung GT-S7710 by <mjchen@sta.samsung.com>
 * Based partly on the code in LG Electronics GP2AP00200F driver by
 * Kenobi Lee <sungyoung.lee@lge.com> and EunYoung Cho <ey.cho@lge.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/consumer.h> /* To get our ADC channel */
#समावेश <linux/iio/types.h> /* To deal with our ADC channel */
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bits.h>
#समावेश <linux/math64.h>
#समावेश <linux/pm.h>

#घोषणा GP2AP002_PROX_CHANNEL 0
#घोषणा GP2AP002_ALS_CHANNEL 1

/* ------------------------------------------------------------------------ */
/* ADDRESS SYMBOL             DATA                                 Init R/W */
/*                   D7    D6    D5    D4    D3    D2    D1    D0           */
/* ------------------------------------------------------------------------ */
/*    0      PROX     X     X     X     X     X     X     X    VO  H'00   R */
/*    1      GAIN     X     X     X     X  LED0     X     X     X  H'00   W */
/*    2       HYS  HYSD HYSC1 HYSC0     X HYSF3 HYSF2 HYSF1 HYSF0  H'00   W */
/*    3     CYCLE     X     X CYCL2 CYCL1 CYCL0  OSC2     X     X  H'00   W */
/*    4     OPMOD     X     X     X   ASD     X     X  VCON   SSD  H'00   W */
/*    6       CON     X     X     X OCON1 OCON0     X     X     X  H'00   W */
/* ------------------------------------------------------------------------ */
/* VO   :Proximity sensing result(0: no detection, 1: detection)            */
/* LED0 :Select चयन क्रम LED driver's On-registence(0:2x higher, 1:normal)*/
/* HYSD/HYSF :Adjusts the receiver sensitivity                              */
/* OSC  :Select चयन पूर्णांकernal clocl frequency hoppling(0:effective)       */
/* CYCL :Determine the detection cycle(typically 8ms, up to 128x)           */
/* SSD  :Software Shutकरोwn function(0:shutकरोwn, 1:operating)                */
/* VCON :VOUT output method control(0:normal, 1:पूर्णांकerrupt)                  */
/* ASD  :Select चयन क्रम analog sleep function(0:ineffective, 1:effective)*/
/* OCON :Select चयन क्रम enabling/disabling VOUT (00:enable, 11:disable)  */

#घोषणा GP2AP002_PROX				0x00
#घोषणा GP2AP002_GAIN				0x01
#घोषणा GP2AP002_HYS				0x02
#घोषणा GP2AP002_CYCLE				0x03
#घोषणा GP2AP002_OPMOD				0x04
#घोषणा GP2AP002_CON				0x06

#घोषणा GP2AP002_PROX_VO_DETECT			BIT(0)

/* Setting this bit to 0 means 2x higher LED resistance */
#घोषणा GP2AP002_GAIN_LED_NORMAL		BIT(3)

/*
 * These bits adjusts the proximity sensitivity, determining अक्षरacteristics
 * of the detection distance and its hysteresis.
 */
#घोषणा GP2AP002_HYS_HYSD_SHIFT		7
#घोषणा GP2AP002_HYS_HYSD_MASK		BIT(7)
#घोषणा GP2AP002_HYS_HYSC_SHIFT		5
#घोषणा GP2AP002_HYS_HYSC_MASK		GENMASK(6, 5)
#घोषणा GP2AP002_HYS_HYSF_SHIFT		0
#घोषणा GP2AP002_HYS_HYSF_MASK		GENMASK(3, 0)
#घोषणा GP2AP002_HYS_MASK		(GP2AP002_HYS_HYSD_MASK | \
					 GP2AP002_HYS_HYSC_MASK | \
					 GP2AP002_HYS_HYSF_MASK)

/*
 * These values determine the detection cycle response समय
 * 0: 8ms, 1: 16ms, 2: 32ms, 3: 64ms, 4: 128ms,
 * 5: 256ms, 6: 512ms, 7: 1024ms
 */
#घोषणा GP2AP002_CYCLE_CYCL_SHIFT	3
#घोषणा GP2AP002_CYCLE_CYCL_MASK	GENMASK(5, 3)

/*
 * Select चयन क्रम पूर्णांकernal घड़ी frequency hopping
 *	0: effective,
 *	1: ineffective
 */
#घोषणा GP2AP002_CYCLE_OSC_EFFECTIVE	0
#घोषणा GP2AP002_CYCLE_OSC_INEFFECTIVE	BIT(2)
#घोषणा GP2AP002_CYCLE_OSC_MASK		BIT(2)

/* Analog sleep effective */
#घोषणा GP2AP002_OPMOD_ASD		BIT(4)
/* Enable chip */
#घोषणा GP2AP002_OPMOD_SSD_OPERATING	BIT(0)
/* IRQ mode */
#घोषणा GP2AP002_OPMOD_VCON_IRQ		BIT(1)
#घोषणा GP2AP002_OPMOD_MASK		(BIT(0) | BIT(1) | BIT(4))

/*
 * Select चयन क्रम enabling/disabling Vout pin
 * 0: enable
 * 2: क्रमce to go Low
 * 3: क्रमce to go High
 */
#घोषणा GP2AP002_CON_OCON_SHIFT		3
#घोषणा GP2AP002_CON_OCON_ENABLE	(0x0 << GP2AP002_CON_OCON_SHIFT)
#घोषणा GP2AP002_CON_OCON_LOW		(0x2 << GP2AP002_CON_OCON_SHIFT)
#घोषणा GP2AP002_CON_OCON_HIGH		(0x3 << GP2AP002_CON_OCON_SHIFT)
#घोषणा GP2AP002_CON_OCON_MASK		(0x3 << GP2AP002_CON_OCON_SHIFT)

/**
 * काष्ठा gp2ap002 - GP2AP002 state
 * @map: regmap poपूर्णांकer क्रम the i2c regmap
 * @dev: poपूर्णांकer to parent device
 * @vdd: regulator controlling VDD
 * @vio: regulator controlling VIO
 * @alsout: IIO ADC channel to convert the ALSOUT संकेत
 * @hys_far: hysteresis control from device tree
 * @hys_बंद: hysteresis control from device tree
 * @is_gp2ap002s00f: this is the GP2AP002F variant of the chip
 * @irq: the IRQ line used by this device
 * @enabled: we cannot पढ़ो the status of the hardware so we need to
 * keep track of whether the event is enabled using this state variable
 */
काष्ठा gp2ap002 अणु
	काष्ठा regmap *map;
	काष्ठा device *dev;
	काष्ठा regulator *vdd;
	काष्ठा regulator *vio;
	काष्ठा iio_channel *alsout;
	u8 hys_far;
	u8 hys_बंद;
	bool is_gp2ap002s00f;
	पूर्णांक irq;
	bool enabled;
पूर्ण;

अटल irqवापस_t gp2ap002_prox_irq(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा iio_dev *indio_dev = d;
	काष्ठा gp2ap002 *gp2ap002 = iio_priv(indio_dev);
	u64 ev;
	पूर्णांक val;
	पूर्णांक ret;

	अगर (!gp2ap002->enabled)
		जाओ err_retrig;

	ret = regmap_पढ़ो(gp2ap002->map, GP2AP002_PROX, &val);
	अगर (ret) अणु
		dev_err(gp2ap002->dev, "error reading proximity\n");
		जाओ err_retrig;
	पूर्ण

	अगर (val & GP2AP002_PROX_VO_DETECT) अणु
		/* Close */
		dev_dbg(gp2ap002->dev, "close\n");
		ret = regmap_ग_लिखो(gp2ap002->map, GP2AP002_HYS,
				   gp2ap002->hys_far);
		अगर (ret)
			dev_err(gp2ap002->dev,
				"error setting up proximity hysteresis\n");
		ev = IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, GP2AP002_PROX_CHANNEL,
					IIO_EV_TYPE_THRESH, IIO_EV_सूची_RISING);
	पूर्ण अन्यथा अणु
		/* Far */
		dev_dbg(gp2ap002->dev, "far\n");
		ret = regmap_ग_लिखो(gp2ap002->map, GP2AP002_HYS,
				   gp2ap002->hys_बंद);
		अगर (ret)
			dev_err(gp2ap002->dev,
				"error setting up proximity hysteresis\n");
		ev = IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, GP2AP002_PROX_CHANNEL,
					IIO_EV_TYPE_THRESH, IIO_EV_सूची_FALLING);
	पूर्ण
	iio_push_event(indio_dev, ev, iio_get_समय_ns(indio_dev));

	/*
	 * After changing hysteresis, we need to रुको क्रम one detection
	 * cycle to see अगर anything changed, or we will just trigger the
	 * previous पूर्णांकerrupt again. A detection cycle depends on the CYCLE
	 * रेजिस्टर, we are hard-coding ~8 ms in probe() so रुको some more
	 * than this, 20-30 ms.
	 */
	usleep_range(20000, 30000);

err_retrig:
	ret = regmap_ग_लिखो(gp2ap002->map, GP2AP002_CON,
			   GP2AP002_CON_OCON_ENABLE);
	अगर (ret)
		dev_err(gp2ap002->dev, "error setting up VOUT control\n");

	वापस IRQ_HANDLED;
पूर्ण

/*
 * This array maps current and lux.
 *
 * Ambient light sensing range is 3 to 55000 lux.
 *
 * This mapping is based on the following क्रमmula.
 * illuminance = 10 ^ (current[mA] / 10)
 *
 * When the ADC measures 0, वापस 0 lux.
 */
अटल स्थिर u16 gp2ap002_illuminance_table[] = अणु
	0, 1, 1, 2, 2, 3, 4, 5, 6, 8, 10, 12, 16, 20, 25, 32, 40, 50, 63, 79,
	100, 126, 158, 200, 251, 316, 398, 501, 631, 794, 1000, 1259, 1585,
	1995, 2512, 3162, 3981, 5012, 6310, 7943, 10000, 12589, 15849, 19953,
	25119, 31623, 39811, 50119,
पूर्ण;

अटल पूर्णांक gp2ap002_get_lux(काष्ठा gp2ap002 *gp2ap002)
अणु
	पूर्णांक ret, res;
	u16 lux;

	ret = iio_पढ़ो_channel_processed(gp2ap002->alsout, &res);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(gp2ap002->dev, "read %d mA from ADC\n", res);

	/* ensure we करोn't under/overflow */
	res = clamp(res, 0, (पूर्णांक)ARRAY_SIZE(gp2ap002_illuminance_table) - 1);
	lux = gp2ap002_illuminance_table[res];

	वापस (पूर्णांक)lux;
पूर्ण

अटल पूर्णांक gp2ap002_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा gp2ap002 *gp2ap002 = iio_priv(indio_dev);
	पूर्णांक ret;

	pm_runसमय_get_sync(gp2ap002->dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = gp2ap002_get_lux(gp2ap002);
			अगर (ret < 0)
				वापस ret;
			*val = ret;
			ret = IIO_VAL_INT;
			जाओ out;
		शेष:
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	शेष:
		ret = -EINVAL;
	पूर्ण

out:
	pm_runसमय_mark_last_busy(gp2ap002->dev);
	pm_runसमय_put_स्वतःsuspend(gp2ap002->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक gp2ap002_init(काष्ठा gp2ap002 *gp2ap002)
अणु
	पूर्णांक ret;

	/* Set up the IR LED resistance */
	ret = regmap_ग_लिखो(gp2ap002->map, GP2AP002_GAIN,
			   GP2AP002_GAIN_LED_NORMAL);
	अगर (ret) अणु
		dev_err(gp2ap002->dev, "error setting up LED gain\n");
		वापस ret;
	पूर्ण
	ret = regmap_ग_लिखो(gp2ap002->map, GP2AP002_HYS, gp2ap002->hys_far);
	अगर (ret) अणु
		dev_err(gp2ap002->dev,
			"error setting up proximity hysteresis\n");
		वापस ret;
	पूर्ण

	/* Disable पूर्णांकernal frequency hopping */
	ret = regmap_ग_लिखो(gp2ap002->map, GP2AP002_CYCLE,
			   GP2AP002_CYCLE_OSC_INEFFECTIVE);
	अगर (ret) अणु
		dev_err(gp2ap002->dev,
			"error setting up internal frequency hopping\n");
		वापस ret;
	पूर्ण

	/* Enable chip and IRQ, disable analog sleep */
	ret = regmap_ग_लिखो(gp2ap002->map, GP2AP002_OPMOD,
			   GP2AP002_OPMOD_SSD_OPERATING |
			   GP2AP002_OPMOD_VCON_IRQ);
	अगर (ret) अणु
		dev_err(gp2ap002->dev, "error setting up operation mode\n");
		वापस ret;
	पूर्ण

	/* Interrupt on VOUT enabled */
	ret = regmap_ग_लिखो(gp2ap002->map, GP2AP002_CON,
			   GP2AP002_CON_OCON_ENABLE);
	अगर (ret)
		dev_err(gp2ap002->dev, "error setting up VOUT control\n");

	वापस ret;
पूर्ण

अटल पूर्णांक gp2ap002_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir)
अणु
	काष्ठा gp2ap002 *gp2ap002 = iio_priv(indio_dev);

	/*
	 * We just keep track of this पूर्णांकernally, as it is not possible to
	 * query the hardware.
	 */
	वापस gp2ap002->enabled;
पूर्ण

अटल पूर्णांक gp2ap002_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				       स्थिर काष्ठा iio_chan_spec *chan,
				       क्रमागत iio_event_type type,
				       क्रमागत iio_event_direction dir,
				       पूर्णांक state)
अणु
	काष्ठा gp2ap002 *gp2ap002 = iio_priv(indio_dev);

	अगर (state) अणु
		/*
		 * This will bring the regulators up (unless they are on
		 * alपढ़ोy) and reपूर्णांकialize the sensor by using runसमय_pm
		 * callbacks.
		 */
		pm_runसमय_get_sync(gp2ap002->dev);
		gp2ap002->enabled = true;
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(gp2ap002->dev);
		pm_runसमय_put_स्वतःsuspend(gp2ap002->dev);
		gp2ap002->enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info gp2ap002_info = अणु
	.पढ़ो_raw = gp2ap002_पढ़ो_raw,
	.पढ़ो_event_config = gp2ap002_पढ़ो_event_config,
	.ग_लिखो_event_config = gp2ap002_ग_लिखो_event_config,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec gp2ap002_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec gp2ap002_channels[] = अणु
	अणु
		.type = IIO_PROXIMITY,
		.event_spec = gp2ap002_events,
		.num_event_specs = ARRAY_SIZE(gp2ap002_events),
	पूर्ण,
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.channel = GP2AP002_ALS_CHANNEL,
	पूर्ण,
पूर्ण;

/*
 * We need a special regmap because this hardware expects to
 * ग_लिखो single bytes to रेजिस्टरs but पढ़ो a 16bit word on some
 * variants and discard the lower 8 bits so combine
 * i2c_smbus_पढ़ो_word_data() with i2c_smbus_ग_लिखो_byte_data()
 * selectively like this.
 */
अटल पूर्णांक gp2ap002_regmap_i2c_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				    अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_word_data(i2c, reg);
	अगर (ret < 0)
		वापस ret;

	*val = (ret >> 8) & 0xFF;

	वापस 0;
पूर्ण

अटल पूर्णांक gp2ap002_regmap_i2c_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				     अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	वापस i2c_smbus_ग_लिखो_byte_data(i2c, reg, val);
पूर्ण

अटल काष्ठा regmap_bus gp2ap002_regmap_bus = अणु
	.reg_पढ़ो = gp2ap002_regmap_i2c_पढ़ो,
	.reg_ग_लिखो = gp2ap002_regmap_i2c_ग_लिखो,
पूर्ण;

अटल पूर्णांक gp2ap002_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा gp2ap002 *gp2ap002;
	काष्ठा iio_dev *indio_dev;
	काष्ठा device *dev = &client->dev;
	क्रमागत iio_chan_type ch_type;
	अटल स्थिर काष्ठा regmap_config config = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = GP2AP002_CON,
	पूर्ण;
	काष्ठा regmap *regmap;
	पूर्णांक num_chan;
	स्थिर अक्षर *compat;
	u8 val;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*gp2ap002));
	अगर (!indio_dev)
		वापस -ENOMEM;
	i2c_set_clientdata(client, indio_dev);

	gp2ap002 = iio_priv(indio_dev);
	gp2ap002->dev = dev;

	/*
	 * Check the device compatible like this makes it possible to use
	 * ACPI PRP0001 क्रम रेजिस्टरing the sensor using device tree
	 * properties.
	 */
	ret = device_property_पढ़ो_string(dev, "compatible", &compat);
	अगर (ret) अणु
		dev_err(dev, "cannot check compatible\n");
		वापस ret;
	पूर्ण
	gp2ap002->is_gp2ap002s00f = !म_भेद(compat, "sharp,gp2ap002s00f");

	regmap = devm_regmap_init(dev, &gp2ap002_regmap_bus, dev, &config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to register i2c regmap %ld\n", PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण
	gp2ap002->map = regmap;

	/*
	 * The hysteresis settings are coded पूर्णांकo the device tree as values
	 * to be written पूर्णांकo the hysteresis रेजिस्टर. The datasheet defines
	 * modes "A", "B1" and "B2" with fixed values to be use but venकरोr
	 * code trees क्रम actual devices are tweaking these values and refer to
	 * modes named things like "B1.5". To be able to support any devices,
	 * we allow passing an arbitrary hysteresis setting क्रम "near" and
	 * "far".
	 */

	/* Check the device tree क्रम the IR LED hysteresis */
	ret = device_property_पढ़ो_u8(dev, "sharp,proximity-far-hysteresis",
				      &val);
	अगर (ret) अणु
		dev_err(dev, "failed to obtain proximity far setting\n");
		वापस ret;
	पूर्ण
	dev_dbg(dev, "proximity far setting %02x\n", val);
	gp2ap002->hys_far = val;

	ret = device_property_पढ़ो_u8(dev, "sharp,proximity-close-hysteresis",
				      &val);
	अगर (ret) अणु
		dev_err(dev, "failed to obtain proximity close setting\n");
		वापस ret;
	पूर्ण
	dev_dbg(dev, "proximity close setting %02x\n", val);
	gp2ap002->hys_बंद = val;

	/* The GP2AP002A00F has a light sensor too */
	अगर (!gp2ap002->is_gp2ap002s00f) अणु
		gp2ap002->alsout = devm_iio_channel_get(dev, "alsout");
		अगर (IS_ERR(gp2ap002->alsout)) अणु
			अगर (PTR_ERR(gp2ap002->alsout) == -ENODEV) अणु
				dev_err(dev, "no ADC, deferring...\n");
				वापस -EPROBE_DEFER;
			पूर्ण
			dev_err(dev, "failed to get ALSOUT ADC channel\n");
			वापस PTR_ERR(gp2ap002->alsout);
		पूर्ण
		ret = iio_get_channel_type(gp2ap002->alsout, &ch_type);
		अगर (ret < 0)
			वापस ret;
		अगर (ch_type != IIO_CURRENT) अणु
			dev_err(dev,
				"wrong type of IIO channel specified for ALSOUT\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	gp2ap002->vdd = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(gp2ap002->vdd)) अणु
		dev_err(dev, "failed to get VDD regulator\n");
		वापस PTR_ERR(gp2ap002->vdd);
	पूर्ण
	gp2ap002->vio = devm_regulator_get(dev, "vio");
	अगर (IS_ERR(gp2ap002->vio)) अणु
		dev_err(dev, "failed to get VIO regulator\n");
		वापस PTR_ERR(gp2ap002->vio);
	पूर्ण

	/* Operating voltage 2.4V .. 3.6V according to datasheet */
	ret = regulator_set_voltage(gp2ap002->vdd, 2400000, 3600000);
	अगर (ret) अणु
		dev_err(dev, "failed to sett VDD voltage\n");
		वापस ret;
	पूर्ण

	/* VIO should be between 1.65V and VDD */
	ret = regulator_get_voltage(gp2ap002->vdd);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get VDD voltage\n");
		वापस ret;
	पूर्ण
	ret = regulator_set_voltage(gp2ap002->vio, 1650000, ret);
	अगर (ret) अणु
		dev_err(dev, "failed to set VIO voltage\n");
		वापस ret;
	पूर्ण

	ret = regulator_enable(gp2ap002->vdd);
	अगर (ret) अणु
		dev_err(dev, "failed to enable VDD regulator\n");
		वापस ret;
	पूर्ण
	ret = regulator_enable(gp2ap002->vio);
	अगर (ret) अणु
		dev_err(dev, "failed to enable VIO regulator\n");
		जाओ out_disable_vdd;
	पूर्ण

	msleep(20);

	/*
	 * Initialize the device and संकेत to runसमय PM that now we are
	 * definitely up and using घातer.
	 */
	ret = gp2ap002_init(gp2ap002);
	अगर (ret) अणु
		dev_err(dev, "initialization failed\n");
		जाओ out_disable_vio;
	पूर्ण
	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	gp2ap002->enabled = false;

	ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
					gp2ap002_prox_irq, IRQF_ONESHOT,
					"gp2ap002", indio_dev);
	अगर (ret) अणु
		dev_err(dev, "unable to request IRQ\n");
		जाओ out_put_pm;
	पूर्ण
	gp2ap002->irq = client->irq;

	/*
	 * As the device takes 20 ms + regulator delay to come up with a fresh
	 * measurement after घातer-on, करो not shut it करोwn unnecessarily.
	 * Set स्वतःsuspend to a one second.
	 */
	pm_runसमय_set_स्वतःsuspend_delay(dev, 1000);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_put(dev);

	indio_dev->info = &gp2ap002_info;
	indio_dev->name = "gp2ap002";
	indio_dev->channels = gp2ap002_channels;
	/* Skip light channel क्रम the proximity-only sensor */
	num_chan = ARRAY_SIZE(gp2ap002_channels);
	अगर (gp2ap002->is_gp2ap002s00f)
		num_chan--;
	indio_dev->num_channels = num_chan;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ out_disable_pm;
	dev_dbg(dev, "Sharp GP2AP002 probed successfully\n");

	वापस 0;

out_put_pm:
	pm_runसमय_put_noidle(dev);
out_disable_pm:
	pm_runसमय_disable(dev);
out_disable_vio:
	regulator_disable(gp2ap002->vio);
out_disable_vdd:
	regulator_disable(gp2ap002->vdd);
	वापस ret;
पूर्ण

अटल पूर्णांक gp2ap002_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा gp2ap002 *gp2ap002 = iio_priv(indio_dev);
	काष्ठा device *dev = &client->dev;

	pm_runसमय_get_sync(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
	iio_device_unरेजिस्टर(indio_dev);
	regulator_disable(gp2ap002->vio);
	regulator_disable(gp2ap002->vdd);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused gp2ap002_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा gp2ap002 *gp2ap002 = iio_priv(indio_dev);
	पूर्णांक ret;

	/* Deactivate the IRQ */
	disable_irq(gp2ap002->irq);

	/* Disable chip and IRQ, everything off */
	ret = regmap_ग_लिखो(gp2ap002->map, GP2AP002_OPMOD, 0x00);
	अगर (ret) अणु
		dev_err(gp2ap002->dev, "error setting up operation mode\n");
		वापस ret;
	पूर्ण
	/*
	 * As these regulators may be shared, at least we are now in
	 * sleep even अगर the regulators aren't really turned off.
	 */
	regulator_disable(gp2ap002->vio);
	regulator_disable(gp2ap002->vdd);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused gp2ap002_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा gp2ap002 *gp2ap002 = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_enable(gp2ap002->vdd);
	अगर (ret) अणु
		dev_err(dev, "failed to enable VDD regulator in resume path\n");
		वापस ret;
	पूर्ण
	ret = regulator_enable(gp2ap002->vio);
	अगर (ret) अणु
		dev_err(dev, "failed to enable VIO regulator in resume path\n");
		वापस ret;
	पूर्ण

	msleep(20);

	ret = gp2ap002_init(gp2ap002);
	अगर (ret) अणु
		dev_err(dev, "re-initialization failed\n");
		वापस ret;
	पूर्ण

	/* Re-activate the IRQ */
	enable_irq(gp2ap002->irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops gp2ap002_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(gp2ap002_runसमय_suspend,
			   gp2ap002_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id gp2ap002_id_table[] = अणु
	अणु "gp2ap002", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, gp2ap002_id_table);

अटल स्थिर काष्ठा of_device_id gp2ap002_of_match[] = अणु
	अणु .compatible = "sharp,gp2ap002a00f" पूर्ण,
	अणु .compatible = "sharp,gp2ap002s00f" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gp2ap002_of_match);

अटल काष्ठा i2c_driver gp2ap002_driver = अणु
	.driver = अणु
		.name = "gp2ap002",
		.of_match_table = gp2ap002_of_match,
		.pm = &gp2ap002_dev_pm_ops,
	पूर्ण,
	.probe = gp2ap002_probe,
	.हटाओ = gp2ap002_हटाओ,
	.id_table = gp2ap002_id_table,
पूर्ण;
module_i2c_driver(gp2ap002_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("GP2AP002 ambient light and proximity sensor driver");
MODULE_LICENSE("GPL v2");
