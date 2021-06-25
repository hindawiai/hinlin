<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics hts221 sensor driver
 *
 * Copyright 2016 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi@st.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bitfield.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/buffer.h>

#समावेश <linux/platक्रमm_data/st_sensors_pdata.h>

#समावेश "hts221.h"

#घोषणा HTS221_REG_DRDY_HL_ADDR		0x22
#घोषणा HTS221_REG_DRDY_HL_MASK		BIT(7)
#घोषणा HTS221_REG_DRDY_PP_OD_ADDR	0x22
#घोषणा HTS221_REG_DRDY_PP_OD_MASK	BIT(6)
#घोषणा HTS221_REG_DRDY_EN_ADDR		0x22
#घोषणा HTS221_REG_DRDY_EN_MASK		BIT(2)
#घोषणा HTS221_REG_STATUS_ADDR		0x27
#घोषणा HTS221_RH_DRDY_MASK		BIT(1)
#घोषणा HTS221_TEMP_DRDY_MASK		BIT(0)

अटल पूर्णांक hts221_trig_set_state(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_dev *iio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा hts221_hw *hw = iio_priv(iio_dev);

	वापस regmap_update_bits(hw->regmap, HTS221_REG_DRDY_EN_ADDR,
				  HTS221_REG_DRDY_EN_MASK,
				  FIELD_PREP(HTS221_REG_DRDY_EN_MASK, state));
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops hts221_trigger_ops = अणु
	.set_trigger_state = hts221_trig_set_state,
पूर्ण;

अटल irqवापस_t hts221_trigger_handler_thपढ़ो(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा hts221_hw *hw = निजी;
	पूर्णांक err, status;

	err = regmap_पढ़ो(hw->regmap, HTS221_REG_STATUS_ADDR, &status);
	अगर (err < 0)
		वापस IRQ_HANDLED;

	/*
	 * H_DA bit (humidity data available) is routed to DRDY line.
	 * Humidity sample is computed after temperature one.
	 * Here we can assume data channels are both available अगर H_DA bit
	 * is set in status रेजिस्टर
	 */
	अगर (!(status & HTS221_RH_DRDY_MASK))
		वापस IRQ_NONE;

	iio_trigger_poll_chained(hw->trig);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक hts221_allocate_trigger(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा hts221_hw *hw = iio_priv(iio_dev);
	काष्ठा st_sensors_platक्रमm_data *pdata = dev_get_platdata(hw->dev);
	bool irq_active_low = false, खोलो_drain = false;
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
		dev_info(hw->dev,
			 "mode %lx unsupported, using IRQF_TRIGGER_RISING\n",
			 irq_type);
		irq_type = IRQF_TRIGGER_RISING;
		अवरोध;
	पूर्ण

	err = regmap_update_bits(hw->regmap, HTS221_REG_DRDY_HL_ADDR,
				 HTS221_REG_DRDY_HL_MASK,
				 FIELD_PREP(HTS221_REG_DRDY_HL_MASK,
					    irq_active_low));
	अगर (err < 0)
		वापस err;

	अगर (device_property_पढ़ो_bool(hw->dev, "drive-open-drain") ||
	    (pdata && pdata->खोलो_drain)) अणु
		irq_type |= IRQF_SHARED;
		खोलो_drain = true;
	पूर्ण

	err = regmap_update_bits(hw->regmap, HTS221_REG_DRDY_PP_OD_ADDR,
				 HTS221_REG_DRDY_PP_OD_MASK,
				 FIELD_PREP(HTS221_REG_DRDY_PP_OD_MASK,
					    खोलो_drain));
	अगर (err < 0)
		वापस err;

	err = devm_request_thपढ़ोed_irq(hw->dev, hw->irq, शून्य,
					hts221_trigger_handler_thपढ़ो,
					irq_type | IRQF_ONESHOT,
					hw->name, hw);
	अगर (err) अणु
		dev_err(hw->dev, "failed to request trigger irq %d\n",
			hw->irq);
		वापस err;
	पूर्ण

	hw->trig = devm_iio_trigger_alloc(hw->dev, "%s-trigger",
					  iio_dev->name);
	अगर (!hw->trig)
		वापस -ENOMEM;

	iio_trigger_set_drvdata(hw->trig, iio_dev);
	hw->trig->ops = &hts221_trigger_ops;
	iio_dev->trig = iio_trigger_get(hw->trig);

	वापस devm_iio_trigger_रेजिस्टर(hw->dev, hw->trig);
पूर्ण

अटल पूर्णांक hts221_buffer_preenable(काष्ठा iio_dev *iio_dev)
अणु
	वापस hts221_set_enable(iio_priv(iio_dev), true);
पूर्ण

अटल पूर्णांक hts221_buffer_postdisable(काष्ठा iio_dev *iio_dev)
अणु
	वापस hts221_set_enable(iio_priv(iio_dev), false);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops hts221_buffer_ops = अणु
	.preenable = hts221_buffer_preenable,
	.postdisable = hts221_buffer_postdisable,
पूर्ण;

अटल irqवापस_t hts221_buffer_handler_thपढ़ो(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *iio_dev = pf->indio_dev;
	काष्ठा hts221_hw *hw = iio_priv(iio_dev);
	काष्ठा iio_chan_spec स्थिर *ch;
	पूर्णांक err;

	/* humidity data */
	ch = &iio_dev->channels[HTS221_SENSOR_H];
	err = regmap_bulk_पढ़ो(hw->regmap, ch->address,
			       &hw->scan.channels[0],
			       माप(hw->scan.channels[0]));
	अगर (err < 0)
		जाओ out;

	/* temperature data */
	ch = &iio_dev->channels[HTS221_SENSOR_T];
	err = regmap_bulk_पढ़ो(hw->regmap, ch->address,
			       &hw->scan.channels[1],
			       माप(hw->scan.channels[1]));
	अगर (err < 0)
		जाओ out;

	iio_push_to_buffers_with_बारtamp(iio_dev, &hw->scan,
					   iio_get_समय_ns(iio_dev));

out:
	iio_trigger_notअगरy_करोne(hw->trig);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक hts221_allocate_buffers(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा hts221_hw *hw = iio_priv(iio_dev);
	वापस devm_iio_triggered_buffer_setup(hw->dev, iio_dev,
					शून्य, hts221_buffer_handler_thपढ़ो,
					&hts221_buffer_ops);
पूर्ण

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo.bianconi@st.com>");
MODULE_DESCRIPTION("STMicroelectronics hts221 buffer driver");
MODULE_LICENSE("GPL v2");
