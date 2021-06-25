<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics uvis25 sensor driver
 *
 * Copyright 2017 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/regmap.h>

#समावेश "st_uvis25.h"

#घोषणा ST_UVIS25_REG_WHOAMI_ADDR	0x0f
#घोषणा ST_UVIS25_REG_WHOAMI_VAL	0xca
#घोषणा ST_UVIS25_REG_CTRL1_ADDR	0x20
#घोषणा ST_UVIS25_REG_ODR_MASK		BIT(0)
#घोषणा ST_UVIS25_REG_BDU_MASK		BIT(1)
#घोषणा ST_UVIS25_REG_CTRL2_ADDR	0x21
#घोषणा ST_UVIS25_REG_BOOT_MASK		BIT(7)
#घोषणा ST_UVIS25_REG_CTRL3_ADDR	0x22
#घोषणा ST_UVIS25_REG_HL_MASK		BIT(7)
#घोषणा ST_UVIS25_REG_STATUS_ADDR	0x27
#घोषणा ST_UVIS25_REG_UV_DA_MASK	BIT(0)
#घोषणा ST_UVIS25_REG_OUT_ADDR		0x28

अटल स्थिर काष्ठा iio_chan_spec st_uvis25_channels[] = अणु
	अणु
		.type = IIO_UVINDEX,
		.address = ST_UVIS25_REG_OUT_ADDR,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 8,
			.storagebits = 8,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल पूर्णांक st_uvis25_check_whoami(काष्ठा st_uvis25_hw *hw)
अणु
	पूर्णांक err, data;

	err = regmap_पढ़ो(hw->regmap, ST_UVIS25_REG_WHOAMI_ADDR, &data);
	अगर (err < 0) अणु
		dev_err(regmap_get_device(hw->regmap),
			"failed to read whoami register\n");
		वापस err;
	पूर्ण

	अगर (data != ST_UVIS25_REG_WHOAMI_VAL) अणु
		dev_err(regmap_get_device(hw->regmap),
			"wrong whoami {%02x vs %02x}\n",
			data, ST_UVIS25_REG_WHOAMI_VAL);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st_uvis25_set_enable(काष्ठा st_uvis25_hw *hw, bool enable)
अणु
	पूर्णांक err;

	err = regmap_update_bits(hw->regmap, ST_UVIS25_REG_CTRL1_ADDR,
				 ST_UVIS25_REG_ODR_MASK, enable);
	अगर (err < 0)
		वापस err;

	hw->enabled = enable;

	वापस 0;
पूर्ण

अटल पूर्णांक st_uvis25_पढ़ो_oneshot(काष्ठा st_uvis25_hw *hw, u8 addr, पूर्णांक *val)
अणु
	पूर्णांक err;

	err = st_uvis25_set_enable(hw, true);
	अगर (err < 0)
		वापस err;

	msleep(1500);

	/*
	 * in order to aव्योम possible race conditions with पूर्णांकerrupt
	 * generation, disable the sensor first and then poll output
	 * रेजिस्टर. That sequence guarantees the पूर्णांकerrupt will be reset
	 * when irq line is unmasked
	 */
	err = st_uvis25_set_enable(hw, false);
	अगर (err < 0)
		वापस err;

	err = regmap_पढ़ो(hw->regmap, addr, val);

	वापस err < 0 ? err : IIO_VAL_INT;
पूर्ण

अटल पूर्णांक st_uvis25_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
			      काष्ठा iio_chan_spec स्थिर *ch,
			      पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;

	ret = iio_device_claim_direct_mode(iio_dev);
	अगर (ret)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED: अणु
		काष्ठा st_uvis25_hw *hw = iio_priv(iio_dev);

		/*
		 * mask irq line during oneshot पढ़ो since the sensor
		 * करोes not export the capability to disable data-पढ़ोy line
		 * in the रेजिस्टर map and it is enabled by शेष.
		 * If the line is unmasked during पढ़ो_raw() it will be set
		 * active and never reset since the trigger is disabled
		 */
		अगर (hw->irq > 0)
			disable_irq(hw->irq);
		ret = st_uvis25_पढ़ो_oneshot(hw, ch->address, val);
		अगर (hw->irq > 0)
			enable_irq(hw->irq);
		अवरोध;
	पूर्ण
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	iio_device_release_direct_mode(iio_dev);

	वापस ret;
पूर्ण

अटल irqवापस_t st_uvis25_trigger_handler_thपढ़ो(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा st_uvis25_hw *hw = निजी;
	पूर्णांक err, status;

	err = regmap_पढ़ो(hw->regmap, ST_UVIS25_REG_STATUS_ADDR, &status);
	अगर (err < 0)
		वापस IRQ_HANDLED;

	अगर (!(status & ST_UVIS25_REG_UV_DA_MASK))
		वापस IRQ_NONE;

	iio_trigger_poll_chained(hw->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक st_uvis25_allocate_trigger(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा st_uvis25_hw *hw = iio_priv(iio_dev);
	काष्ठा device *dev = regmap_get_device(hw->regmap);
	bool irq_active_low = false;
	अचिन्हित दीर्घ irq_type;
	पूर्णांक err;

	irq_type = irqd_get_trigger_type(irq_get_irq_data(hw->irq));

	चयन (irq_type) अणु
	हाल IRQF_TRIGGER_HIGH:
	हाल IRQF_TRIGGER_RISING:
		अवरोध;
	हाल IRQF_TRIGGER_LOW:
	हाल IRQF_TRIGGER_FALLING:
		irq_active_low = true;
		अवरोध;
	शेष:
		dev_info(dev, "mode %lx unsupported\n", irq_type);
		वापस -EINVAL;
	पूर्ण

	err = regmap_update_bits(hw->regmap, ST_UVIS25_REG_CTRL3_ADDR,
				 ST_UVIS25_REG_HL_MASK, irq_active_low);
	अगर (err < 0)
		वापस err;

	err = devm_request_thपढ़ोed_irq(dev, hw->irq, शून्य,
					st_uvis25_trigger_handler_thपढ़ो,
					irq_type | IRQF_ONESHOT,
					iio_dev->name, hw);
	अगर (err) अणु
		dev_err(dev, "failed to request trigger irq %d\n",
			hw->irq);
		वापस err;
	पूर्ण

	hw->trig = devm_iio_trigger_alloc(dev, "%s-trigger",
					  iio_dev->name);
	अगर (!hw->trig)
		वापस -ENOMEM;

	iio_trigger_set_drvdata(hw->trig, iio_dev);

	वापस devm_iio_trigger_रेजिस्टर(dev, hw->trig);
पूर्ण

अटल पूर्णांक st_uvis25_buffer_preenable(काष्ठा iio_dev *iio_dev)
अणु
	वापस st_uvis25_set_enable(iio_priv(iio_dev), true);
पूर्ण

अटल पूर्णांक st_uvis25_buffer_postdisable(काष्ठा iio_dev *iio_dev)
अणु
	वापस st_uvis25_set_enable(iio_priv(iio_dev), false);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops st_uvis25_buffer_ops = अणु
	.preenable = st_uvis25_buffer_preenable,
	.postdisable = st_uvis25_buffer_postdisable,
पूर्ण;

अटल irqवापस_t st_uvis25_buffer_handler_thपढ़ो(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *iio_dev = pf->indio_dev;
	काष्ठा st_uvis25_hw *hw = iio_priv(iio_dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = regmap_पढ़ो(hw->regmap, ST_UVIS25_REG_OUT_ADDR, &val);
	अगर (err < 0)
		जाओ out;

	hw->scan.chan = val;

	iio_push_to_buffers_with_बारtamp(iio_dev, &hw->scan,
					   iio_get_समय_ns(iio_dev));

out:
	iio_trigger_notअगरy_करोne(hw->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक st_uvis25_allocate_buffer(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा st_uvis25_hw *hw = iio_priv(iio_dev);

	वापस devm_iio_triggered_buffer_setup(regmap_get_device(hw->regmap),
					       iio_dev, शून्य,
					       st_uvis25_buffer_handler_thपढ़ो,
					       &st_uvis25_buffer_ops);
पूर्ण

अटल स्थिर काष्ठा iio_info st_uvis25_info = अणु
	.पढ़ो_raw = st_uvis25_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक st_uvis25_init_sensor(काष्ठा st_uvis25_hw *hw)
अणु
	पूर्णांक err;

	err = regmap_update_bits(hw->regmap, ST_UVIS25_REG_CTRL2_ADDR,
				 ST_UVIS25_REG_BOOT_MASK, 1);
	अगर (err < 0)
		वापस err;

	msleep(2000);

	वापस regmap_update_bits(hw->regmap, ST_UVIS25_REG_CTRL1_ADDR,
				  ST_UVIS25_REG_BDU_MASK, 1);
पूर्ण

पूर्णांक st_uvis25_probe(काष्ठा device *dev, पूर्णांक irq, काष्ठा regmap *regmap)
अणु
	काष्ठा st_uvis25_hw *hw;
	काष्ठा iio_dev *iio_dev;
	पूर्णांक err;

	iio_dev = devm_iio_device_alloc(dev, माप(*hw));
	अगर (!iio_dev)
		वापस -ENOMEM;

	dev_set_drvdata(dev, (व्योम *)iio_dev);

	hw = iio_priv(iio_dev);
	hw->irq = irq;
	hw->regmap = regmap;

	err = st_uvis25_check_whoami(hw);
	अगर (err < 0)
		वापस err;

	iio_dev->modes = INDIO_सूचीECT_MODE;
	iio_dev->channels = st_uvis25_channels;
	iio_dev->num_channels = ARRAY_SIZE(st_uvis25_channels);
	iio_dev->name = ST_UVIS25_DEV_NAME;
	iio_dev->info = &st_uvis25_info;

	err = st_uvis25_init_sensor(hw);
	अगर (err < 0)
		वापस err;

	अगर (hw->irq > 0) अणु
		err = st_uvis25_allocate_buffer(iio_dev);
		अगर (err < 0)
			वापस err;

		err = st_uvis25_allocate_trigger(iio_dev);
		अगर (err)
			वापस err;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(dev, iio_dev);
पूर्ण
EXPORT_SYMBOL(st_uvis25_probe);

अटल पूर्णांक __maybe_unused st_uvis25_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *iio_dev = dev_get_drvdata(dev);
	काष्ठा st_uvis25_hw *hw = iio_priv(iio_dev);

	वापस regmap_update_bits(hw->regmap, ST_UVIS25_REG_CTRL1_ADDR,
				  ST_UVIS25_REG_ODR_MASK, 0);
पूर्ण

अटल पूर्णांक __maybe_unused st_uvis25_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *iio_dev = dev_get_drvdata(dev);
	काष्ठा st_uvis25_hw *hw = iio_priv(iio_dev);

	अगर (hw->enabled)
		वापस regmap_update_bits(hw->regmap, ST_UVIS25_REG_CTRL1_ADDR,
					  ST_UVIS25_REG_ODR_MASK, 1);

	वापस 0;
पूर्ण

स्थिर काष्ठा dev_pm_ops st_uvis25_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(st_uvis25_suspend, st_uvis25_resume)
पूर्ण;
EXPORT_SYMBOL(st_uvis25_pm_ops);

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>");
MODULE_DESCRIPTION("STMicroelectronics uvis25 sensor driver");
MODULE_LICENSE("GPL v2");
