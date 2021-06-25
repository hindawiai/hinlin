<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2016
 *
 * Author: Benjamin Gaignard <benjamin.gaignard@st.com>
 *
 */

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/समयr/sपंचांग32-समयr-trigger.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/mfd/sपंचांग32-समयrs.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>

#घोषणा MAX_TRIGGERS 7
#घोषणा MAX_VALIDS 5

/* List the triggers created by each समयr */
अटल स्थिर व्योम *triggers_table[][MAX_TRIGGERS] = अणु
	अणु TIM1_TRGO, TIM1_TRGO2, TIM1_CH1, TIM1_CH2, TIM1_CH3, TIM1_CH4,पूर्ण,
	अणु TIM2_TRGO, TIM2_CH1, TIM2_CH2, TIM2_CH3, TIM2_CH4,पूर्ण,
	अणु TIM3_TRGO, TIM3_CH1, TIM3_CH2, TIM3_CH3, TIM3_CH4,पूर्ण,
	अणु TIM4_TRGO, TIM4_CH1, TIM4_CH2, TIM4_CH3, TIM4_CH4,पूर्ण,
	अणु TIM5_TRGO, TIM5_CH1, TIM5_CH2, TIM5_CH3, TIM5_CH4,पूर्ण,
	अणु TIM6_TRGO,पूर्ण,
	अणु TIM7_TRGO,पूर्ण,
	अणु TIM8_TRGO, TIM8_TRGO2, TIM8_CH1, TIM8_CH2, TIM8_CH3, TIM8_CH4,पूर्ण,
	अणु TIM9_TRGO, TIM9_CH1, TIM9_CH2,पूर्ण,
	अणु TIM10_OC1,पूर्ण,
	अणु TIM11_OC1,पूर्ण,
	अणु TIM12_TRGO, TIM12_CH1, TIM12_CH2,पूर्ण,
	अणु TIM13_OC1,पूर्ण,
	अणु TIM14_OC1,पूर्ण,
	अणु TIM15_TRGO,पूर्ण,
	अणु TIM16_OC1,पूर्ण,
	अणु TIM17_OC1,पूर्ण,
पूर्ण;

/* List the triggers accepted by each समयr */
अटल स्थिर व्योम *valids_table[][MAX_VALIDS] = अणु
	अणु TIM5_TRGO, TIM2_TRGO, TIM3_TRGO, TIM4_TRGO,पूर्ण,
	अणु TIM1_TRGO, TIM8_TRGO, TIM3_TRGO, TIM4_TRGO,पूर्ण,
	अणु TIM1_TRGO, TIM2_TRGO, TIM5_TRGO, TIM4_TRGO,पूर्ण,
	अणु TIM1_TRGO, TIM2_TRGO, TIM3_TRGO, TIM8_TRGO,पूर्ण,
	अणु TIM2_TRGO, TIM3_TRGO, TIM4_TRGO, TIM8_TRGO,पूर्ण,
	अणु पूर्ण, /* समयr 6 */
	अणु पूर्ण, /* समयr 7 */
	अणु TIM1_TRGO, TIM2_TRGO, TIM4_TRGO, TIM5_TRGO,पूर्ण,
	अणु TIM2_TRGO, TIM3_TRGO, TIM10_OC1, TIM11_OC1,पूर्ण,
	अणु पूर्ण, /* समयr 10 */
	अणु पूर्ण, /* समयr 11 */
	अणु TIM4_TRGO, TIM5_TRGO, TIM13_OC1, TIM14_OC1,पूर्ण,
पूर्ण;

अटल स्थिर व्योम *sपंचांग32h7_valids_table[][MAX_VALIDS] = अणु
	अणु TIM15_TRGO, TIM2_TRGO, TIM3_TRGO, TIM4_TRGO,पूर्ण,
	अणु TIM1_TRGO, TIM8_TRGO, TIM3_TRGO, TIM4_TRGO,पूर्ण,
	अणु TIM1_TRGO, TIM2_TRGO, TIM15_TRGO, TIM4_TRGO,पूर्ण,
	अणु TIM1_TRGO, TIM2_TRGO, TIM3_TRGO, TIM8_TRGO,पूर्ण,
	अणु TIM1_TRGO, TIM8_TRGO, TIM3_TRGO, TIM4_TRGO,पूर्ण,
	अणु पूर्ण, /* समयr 6 */
	अणु पूर्ण, /* समयr 7 */
	अणु TIM1_TRGO, TIM2_TRGO, TIM4_TRGO, TIM5_TRGO,पूर्ण,
	अणु पूर्ण, /* समयr 9 */
	अणु पूर्ण, /* समयr 10 */
	अणु पूर्ण, /* समयr 11 */
	अणु TIM4_TRGO, TIM5_TRGO, TIM13_OC1, TIM14_OC1,पूर्ण,
	अणु पूर्ण, /* समयr 13 */
	अणु पूर्ण, /* समयr 14 */
	अणु TIM1_TRGO, TIM3_TRGO, TIM16_OC1, TIM17_OC1,पूर्ण,
	अणु पूर्ण, /* समयr 16 */
	अणु पूर्ण, /* समयr 17 */
पूर्ण;

काष्ठा sपंचांग32_समयr_trigger_regs अणु
	u32 cr1;
	u32 cr2;
	u32 psc;
	u32 arr;
	u32 cnt;
	u32 smcr;
पूर्ण;

काष्ठा sपंचांग32_समयr_trigger अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
	bool enabled;
	u32 max_arr;
	स्थिर व्योम *triggers;
	स्थिर व्योम *valids;
	bool has_trgo2;
	काष्ठा mutex lock; /* concurrent sysfs configuration */
	काष्ठा list_head tr_list;
	काष्ठा sपंचांग32_समयr_trigger_regs bak;
पूर्ण;

काष्ठा sपंचांग32_समयr_trigger_cfg अणु
	स्थिर व्योम *(*valids_table)[MAX_VALIDS];
	स्थिर अचिन्हित पूर्णांक num_valids_table;
पूर्ण;

अटल bool sपंचांग32_समयr_is_trgo2_name(स्थिर अक्षर *name)
अणु
	वापस !!म_माला(name, "trgo2");
पूर्ण

अटल bool sपंचांग32_समयr_is_trgo_name(स्थिर अक्षर *name)
अणु
	वापस (!!म_माला(name, "trgo") && !म_माला(name, "trgo2"));
पूर्ण

अटल पूर्णांक sपंचांग32_समयr_start(काष्ठा sपंचांग32_समयr_trigger *priv,
			     काष्ठा iio_trigger *trig,
			     अचिन्हित पूर्णांक frequency)
अणु
	अचिन्हित दीर्घ दीर्घ prd, भाग;
	पूर्णांक prescaler = 0;
	u32 ccer;

	/* Period and prescaler values depends of घड़ी rate */
	भाग = (अचिन्हित दीर्घ दीर्घ)clk_get_rate(priv->clk);

	करो_भाग(भाग, frequency);

	prd = भाग;

	/*
	 * Increase prescaler value until we get a result that fit
	 * with स्वतः reload रेजिस्टर maximum value.
	 */
	जबतक (भाग > priv->max_arr) अणु
		prescaler++;
		भाग = prd;
		करो_भाग(भाग, (prescaler + 1));
	पूर्ण
	prd = भाग;

	अगर (prescaler > MAX_TIM_PSC) अणु
		dev_err(priv->dev, "prescaler exceeds the maximum value\n");
		वापस -EINVAL;
	पूर्ण

	/* Check अगर nobody अन्यथा use the समयr */
	regmap_पढ़ो(priv->regmap, TIM_CCER, &ccer);
	अगर (ccer & TIM_CCER_CCXE)
		वापस -EBUSY;

	mutex_lock(&priv->lock);
	अगर (!priv->enabled) अणु
		priv->enabled = true;
		clk_enable(priv->clk);
	पूर्ण

	regmap_ग_लिखो(priv->regmap, TIM_PSC, prescaler);
	regmap_ग_लिखो(priv->regmap, TIM_ARR, prd - 1);
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_ARPE, TIM_CR1_ARPE);

	/* Force master mode to update mode */
	अगर (sपंचांग32_समयr_is_trgo2_name(trig->name))
		regmap_update_bits(priv->regmap, TIM_CR2, TIM_CR2_MMS2,
				   0x2 << TIM_CR2_MMS2_SHIFT);
	अन्यथा
		regmap_update_bits(priv->regmap, TIM_CR2, TIM_CR2_MMS,
				   0x2 << TIM_CR2_MMS_SHIFT);

	/* Make sure that रेजिस्टरs are updated */
	regmap_update_bits(priv->regmap, TIM_EGR, TIM_EGR_UG, TIM_EGR_UG);

	/* Enable controller */
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, TIM_CR1_CEN);
	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_समयr_stop(काष्ठा sपंचांग32_समयr_trigger *priv,
			     काष्ठा iio_trigger *trig)
अणु
	u32 ccer;

	regmap_पढ़ो(priv->regmap, TIM_CCER, &ccer);
	अगर (ccer & TIM_CCER_CCXE)
		वापस;

	mutex_lock(&priv->lock);
	/* Stop समयr */
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_ARPE, 0);
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, 0);
	regmap_ग_लिखो(priv->regmap, TIM_PSC, 0);
	regmap_ग_लिखो(priv->regmap, TIM_ARR, 0);

	/* Force disable master mode */
	अगर (sपंचांग32_समयr_is_trgo2_name(trig->name))
		regmap_update_bits(priv->regmap, TIM_CR2, TIM_CR2_MMS2, 0);
	अन्यथा
		regmap_update_bits(priv->regmap, TIM_CR2, TIM_CR2_MMS, 0);

	/* Make sure that रेजिस्टरs are updated */
	regmap_update_bits(priv->regmap, TIM_EGR, TIM_EGR_UG, TIM_EGR_UG);

	अगर (priv->enabled) अणु
		priv->enabled = false;
		clk_disable(priv->clk);
	पूर्ण
	mutex_unlock(&priv->lock);
पूर्ण

अटल sमाप_प्रकार sपंचांग32_tt_store_frequency(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_trigger *trig = to_iio_trigger(dev);
	काष्ठा sपंचांग32_समयr_trigger *priv = iio_trigger_get_drvdata(trig);
	अचिन्हित पूर्णांक freq;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &freq);
	अगर (ret)
		वापस ret;

	अगर (freq == 0) अणु
		sपंचांग32_समयr_stop(priv, trig);
	पूर्ण अन्यथा अणु
		ret = sपंचांग32_समयr_start(priv, trig, freq);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार sपंचांग32_tt_पढ़ो_frequency(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iio_trigger *trig = to_iio_trigger(dev);
	काष्ठा sपंचांग32_समयr_trigger *priv = iio_trigger_get_drvdata(trig);
	u32 psc, arr, cr1;
	अचिन्हित दीर्घ दीर्घ freq = 0;

	regmap_पढ़ो(priv->regmap, TIM_CR1, &cr1);
	regmap_पढ़ो(priv->regmap, TIM_PSC, &psc);
	regmap_पढ़ो(priv->regmap, TIM_ARR, &arr);

	अगर (cr1 & TIM_CR1_CEN) अणु
		freq = (अचिन्हित दीर्घ दीर्घ)clk_get_rate(priv->clk);
		करो_भाग(freq, psc + 1);
		करो_भाग(freq, arr + 1);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", (अचिन्हित पूर्णांक)freq);
पूर्ण

अटल IIO_DEV_ATTR_SAMP_FREQ(0660,
			      sपंचांग32_tt_पढ़ो_frequency,
			      sपंचांग32_tt_store_frequency);

#घोषणा MASTER_MODE_MAX		7
#घोषणा MASTER_MODE2_MAX	15

अटल अक्षर *master_mode_table[] = अणु
	"reset",
	"enable",
	"update",
	"compare_pulse",
	"OC1REF",
	"OC2REF",
	"OC3REF",
	"OC4REF",
	/* Master mode selection 2 only */
	"OC5REF",
	"OC6REF",
	"compare_pulse_OC4REF",
	"compare_pulse_OC6REF",
	"compare_pulse_OC4REF_r_or_OC6REF_r",
	"compare_pulse_OC4REF_r_or_OC6REF_f",
	"compare_pulse_OC5REF_r_or_OC6REF_r",
	"compare_pulse_OC5REF_r_or_OC6REF_f",
पूर्ण;

अटल sमाप_प्रकार sपंचांग32_tt_show_master_mode(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = dev_get_drvdata(dev);
	काष्ठा iio_trigger *trig = to_iio_trigger(dev);
	u32 cr2;

	regmap_पढ़ो(priv->regmap, TIM_CR2, &cr2);

	अगर (sपंचांग32_समयr_is_trgo2_name(trig->name))
		cr2 = (cr2 & TIM_CR2_MMS2) >> TIM_CR2_MMS2_SHIFT;
	अन्यथा
		cr2 = (cr2 & TIM_CR2_MMS) >> TIM_CR2_MMS_SHIFT;

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", master_mode_table[cr2]);
पूर्ण

अटल sमाप_प्रकार sपंचांग32_tt_store_master_mode(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = dev_get_drvdata(dev);
	काष्ठा iio_trigger *trig = to_iio_trigger(dev);
	u32 mask, shअगरt, master_mode_max;
	पूर्णांक i;

	अगर (sपंचांग32_समयr_is_trgo2_name(trig->name)) अणु
		mask = TIM_CR2_MMS2;
		shअगरt = TIM_CR2_MMS2_SHIFT;
		master_mode_max = MASTER_MODE2_MAX;
	पूर्ण अन्यथा अणु
		mask = TIM_CR2_MMS;
		shअगरt = TIM_CR2_MMS_SHIFT;
		master_mode_max = MASTER_MODE_MAX;
	पूर्ण

	क्रम (i = 0; i <= master_mode_max; i++) अणु
		अगर (!म_भेदन(master_mode_table[i], buf,
			     म_माप(master_mode_table[i]))) अणु
			mutex_lock(&priv->lock);
			अगर (!priv->enabled) अणु
				/* Clock should be enabled first */
				priv->enabled = true;
				clk_enable(priv->clk);
			पूर्ण
			regmap_update_bits(priv->regmap, TIM_CR2, mask,
					   i << shअगरt);
			mutex_unlock(&priv->lock);
			वापस len;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार sपंचांग32_tt_show_master_mode_avail(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा iio_trigger *trig = to_iio_trigger(dev);
	अचिन्हित पूर्णांक i, master_mode_max;
	माप_प्रकार len = 0;

	अगर (sपंचांग32_समयr_is_trgo2_name(trig->name))
		master_mode_max = MASTER_MODE2_MAX;
	अन्यथा
		master_mode_max = MASTER_MODE_MAX;

	क्रम (i = 0; i <= master_mode_max; i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"%s ", master_mode_table[i]);

	/* replace trailing space by newline */
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(master_mode_available, 0444,
		       sपंचांग32_tt_show_master_mode_avail, शून्य, 0);

अटल IIO_DEVICE_ATTR(master_mode, 0660,
		       sपंचांग32_tt_show_master_mode,
		       sपंचांग32_tt_store_master_mode,
		       0);

अटल काष्ठा attribute *sपंचांग32_trigger_attrs[] = अणु
	&iio_dev_attr_sampling_frequency.dev_attr.attr,
	&iio_dev_attr_master_mode.dev_attr.attr,
	&iio_dev_attr_master_mode_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group sपंचांग32_trigger_attr_group = अणु
	.attrs = sपंचांग32_trigger_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *sपंचांग32_trigger_attr_groups[] = अणु
	&sपंचांग32_trigger_attr_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा iio_trigger_ops समयr_trigger_ops = अणु
पूर्ण;

अटल व्योम sपंचांग32_unरेजिस्टर_iio_triggers(काष्ठा sपंचांग32_समयr_trigger *priv)
अणु
	काष्ठा iio_trigger *tr;

	list_क्रम_each_entry(tr, &priv->tr_list, alloc_list)
		iio_trigger_unरेजिस्टर(tr);
पूर्ण

अटल पूर्णांक sपंचांग32_रेजिस्टर_iio_triggers(काष्ठा sपंचांग32_समयr_trigger *priv)
अणु
	पूर्णांक ret;
	स्थिर अक्षर * स्थिर *cur = priv->triggers;

	INIT_LIST_HEAD(&priv->tr_list);

	जबतक (cur && *cur) अणु
		काष्ठा iio_trigger *trig;
		bool cur_is_trgo = sपंचांग32_समयr_is_trgo_name(*cur);
		bool cur_is_trgo2 = sपंचांग32_समयr_is_trgo2_name(*cur);

		अगर (cur_is_trgo2 && !priv->has_trgo2) अणु
			cur++;
			जारी;
		पूर्ण

		trig = devm_iio_trigger_alloc(priv->dev, "%s", *cur);
		अगर  (!trig)
			वापस -ENOMEM;

		trig->dev.parent = priv->dev->parent;
		trig->ops = &समयr_trigger_ops;

		/*
		 * sampling frequency and master mode attributes
		 * should only be available on trgo/trgo2 triggers
		 */
		अगर (cur_is_trgo || cur_is_trgo2)
			trig->dev.groups = sपंचांग32_trigger_attr_groups;

		iio_trigger_set_drvdata(trig, priv);

		ret = iio_trigger_रेजिस्टर(trig);
		अगर (ret) अणु
			sपंचांग32_unरेजिस्टर_iio_triggers(priv);
			वापस ret;
		पूर्ण

		list_add_tail(&trig->alloc_list, &priv->tr_list);
		cur++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_counter_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				  काष्ठा iio_chan_spec स्थिर *chan,
				  पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = iio_priv(indio_dev);
	u32 dat;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		regmap_पढ़ो(priv->regmap, TIM_CNT, &dat);
		*val = dat;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_ENABLE:
		regmap_पढ़ो(priv->regmap, TIM_CR1, &dat);
		*val = (dat & TIM_CR1_CEN) ? 1 : 0;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		regmap_पढ़ो(priv->regmap, TIM_SMCR, &dat);
		dat &= TIM_SMCR_SMS;

		*val = 1;
		*val2 = 0;

		/* in quadrature हाल scale = 0.25 */
		अगर (dat == 3)
			*val2 = 2;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_counter_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				   काष्ठा iio_chan_spec स्थिर *chan,
				   पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस regmap_ग_लिखो(priv->regmap, TIM_CNT, val);

	हाल IIO_CHAN_INFO_SCALE:
		/* fixed scale */
		वापस -EINVAL;

	हाल IIO_CHAN_INFO_ENABLE:
		mutex_lock(&priv->lock);
		अगर (val) अणु
			अगर (!priv->enabled) अणु
				priv->enabled = true;
				clk_enable(priv->clk);
			पूर्ण
			regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN,
					   TIM_CR1_CEN);
		पूर्ण अन्यथा अणु
			regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN,
					   0);
			अगर (priv->enabled) अणु
				priv->enabled = false;
				clk_disable(priv->clk);
			पूर्ण
		पूर्ण
		mutex_unlock(&priv->lock);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_counter_validate_trigger(काष्ठा iio_dev *indio_dev,
					  काष्ठा iio_trigger *trig)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = iio_priv(indio_dev);
	स्थिर अक्षर * स्थिर *cur = priv->valids;
	अचिन्हित पूर्णांक i = 0;

	अगर (!is_sपंचांग32_समयr_trigger(trig))
		वापस -EINVAL;

	जबतक (cur && *cur) अणु
		अगर (!म_भेदन(trig->name, *cur, म_माप(trig->name))) अणु
			regmap_update_bits(priv->regmap,
					   TIM_SMCR, TIM_SMCR_TS,
					   i << TIM_SMCR_TS_SHIFT);
			वापस 0;
		पूर्ण
		cur++;
		i++;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info sपंचांग32_trigger_info = अणु
	.validate_trigger = sपंचांग32_counter_validate_trigger,
	.पढ़ो_raw = sपंचांग32_counter_पढ़ो_raw,
	.ग_लिखो_raw = sपंचांग32_counter_ग_लिखो_raw
पूर्ण;

अटल स्थिर अक्षर *स्थिर sपंचांग32_trigger_modes[] = अणु
	"trigger",
पूर्ण;

अटल पूर्णांक sपंचांग32_set_trigger_mode(काष्ठा iio_dev *indio_dev,
				  स्थिर काष्ठा iio_chan_spec *chan,
				  अचिन्हित पूर्णांक mode)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = iio_priv(indio_dev);

	regmap_update_bits(priv->regmap, TIM_SMCR, TIM_SMCR_SMS, TIM_SMCR_SMS);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_get_trigger_mode(काष्ठा iio_dev *indio_dev,
				  स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = iio_priv(indio_dev);
	u32 smcr;

	regmap_पढ़ो(priv->regmap, TIM_SMCR, &smcr);

	वापस (smcr & TIM_SMCR_SMS) == TIM_SMCR_SMS ? 0 : -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत sपंचांग32_trigger_mode_क्रमागत = अणु
	.items = sपंचांग32_trigger_modes,
	.num_items = ARRAY_SIZE(sपंचांग32_trigger_modes),
	.set = sपंचांग32_set_trigger_mode,
	.get = sपंचांग32_get_trigger_mode
पूर्ण;

अटल स्थिर अक्षर *स्थिर sपंचांग32_enable_modes[] = अणु
	"always",
	"gated",
	"triggered",
पूर्ण;

अटल पूर्णांक sपंचांग32_enable_mode2sms(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल 0:
		वापस 0;
	हाल 1:
		वापस 5;
	हाल 2:
		वापस 6;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_set_enable_mode(काष्ठा iio_dev *indio_dev,
				 स्थिर काष्ठा iio_chan_spec *chan,
				 अचिन्हित पूर्णांक mode)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = iio_priv(indio_dev);
	पूर्णांक sms = sपंचांग32_enable_mode2sms(mode);

	अगर (sms < 0)
		वापस sms;
	/*
	 * Triggered mode sets CEN bit स्वतःmatically by hardware. So, first
	 * enable counter घड़ी, so it can use it. Keeps it in sync with CEN.
	 */
	mutex_lock(&priv->lock);
	अगर (sms == 6 && !priv->enabled) अणु
		clk_enable(priv->clk);
		priv->enabled = true;
	पूर्ण
	mutex_unlock(&priv->lock);

	regmap_update_bits(priv->regmap, TIM_SMCR, TIM_SMCR_SMS, sms);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sms2enable_mode(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल 0:
		वापस 0;
	हाल 5:
		वापस 1;
	हाल 6:
		वापस 2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_get_enable_mode(काष्ठा iio_dev *indio_dev,
				 स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = iio_priv(indio_dev);
	u32 smcr;

	regmap_पढ़ो(priv->regmap, TIM_SMCR, &smcr);
	smcr &= TIM_SMCR_SMS;

	वापस sपंचांग32_sms2enable_mode(smcr);
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत sपंचांग32_enable_mode_क्रमागत = अणु
	.items = sपंचांग32_enable_modes,
	.num_items = ARRAY_SIZE(sपंचांग32_enable_modes),
	.set = sपंचांग32_set_enable_mode,
	.get = sपंचांग32_get_enable_mode
पूर्ण;

अटल sमाप_प्रकार sपंचांग32_count_get_preset(काष्ठा iio_dev *indio_dev,
				      uपूर्णांकptr_t निजी,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      अक्षर *buf)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = iio_priv(indio_dev);
	u32 arr;

	regmap_पढ़ो(priv->regmap, TIM_ARR, &arr);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", arr);
पूर्ण

अटल sमाप_प्रकार sपंचांग32_count_set_preset(काष्ठा iio_dev *indio_dev,
				      uपूर्णांकptr_t निजी,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = iio_priv(indio_dev);
	अचिन्हित पूर्णांक preset;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 0, &preset);
	अगर (ret)
		वापस ret;

	/* TIMx_ARR रेजिस्टर shouldn't be buffered (ARPE=0) */
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_ARPE, 0);
	regmap_ग_लिखो(priv->regmap, TIM_ARR, preset);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info sपंचांग32_trigger_count_info[] = अणु
	अणु
		.name = "preset",
		.shared = IIO_SEPARATE,
		.पढ़ो = sपंचांग32_count_get_preset,
		.ग_लिखो = sपंचांग32_count_set_preset
	पूर्ण,
	IIO_ENUM("enable_mode", IIO_SEPARATE, &sपंचांग32_enable_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("enable_mode", &sपंचांग32_enable_mode_क्रमागत),
	IIO_ENUM("trigger_mode", IIO_SEPARATE, &sपंचांग32_trigger_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("trigger_mode", &sपंचांग32_trigger_mode_क्रमागत),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec sपंचांग32_trigger_channel = अणु
	.type = IIO_COUNT,
	.channel = 0,
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			      BIT(IIO_CHAN_INFO_ENABLE) |
			      BIT(IIO_CHAN_INFO_SCALE),
	.ext_info = sपंचांग32_trigger_count_info,
	.indexed = 1
पूर्ण;

अटल काष्ठा sपंचांग32_समयr_trigger *sपंचांग32_setup_counter_device(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev,
					  माप(काष्ठा sपंचांग32_समयr_trigger));
	अगर (!indio_dev)
		वापस शून्य;

	indio_dev->name = dev_name(dev);
	indio_dev->info = &sपंचांग32_trigger_info;
	indio_dev->modes = INDIO_HARDWARE_TRIGGERED;
	indio_dev->num_channels = 1;
	indio_dev->channels = &sपंचांग32_trigger_channel;

	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret)
		वापस शून्य;

	वापस iio_priv(indio_dev);
पूर्ण

/**
 * is_sपंचांग32_समयr_trigger
 * @trig: trigger to be checked
 *
 * वापस true अगर the trigger is a valid sपंचांग32 iio समयr trigger
 * either वापस false
 */
bool is_sपंचांग32_समयr_trigger(काष्ठा iio_trigger *trig)
अणु
	वापस (trig->ops == &समयr_trigger_ops);
पूर्ण
EXPORT_SYMBOL(is_sपंचांग32_समयr_trigger);

अटल व्योम sपंचांग32_समयr_detect_trgo2(काष्ठा sपंचांग32_समयr_trigger *priv)
अणु
	u32 val;

	/*
	 * Master mode selection 2 bits can only be written and पढ़ो back when
	 * समयr supports it.
	 */
	regmap_update_bits(priv->regmap, TIM_CR2, TIM_CR2_MMS2, TIM_CR2_MMS2);
	regmap_पढ़ो(priv->regmap, TIM_CR2, &val);
	regmap_update_bits(priv->regmap, TIM_CR2, TIM_CR2_MMS2, 0);
	priv->has_trgo2 = !!val;
पूर्ण

अटल पूर्णांक sपंचांग32_समयr_trigger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sपंचांग32_समयr_trigger *priv;
	काष्ठा sपंचांग32_समयrs *ddata = dev_get_drvdata(pdev->dev.parent);
	स्थिर काष्ठा sपंचांग32_समयr_trigger_cfg *cfg;
	अचिन्हित पूर्णांक index;
	पूर्णांक ret;

	अगर (of_property_पढ़ो_u32(dev->of_node, "reg", &index))
		वापस -EINVAL;

	cfg = (स्थिर काष्ठा sपंचांग32_समयr_trigger_cfg *)
		of_match_device(dev->driver->of_match_table, dev)->data;

	अगर (index >= ARRAY_SIZE(triggers_table) ||
	    index >= cfg->num_valids_table)
		वापस -EINVAL;

	/* Create an IIO device only अगर we have triggers to be validated */
	अगर (*cfg->valids_table[index])
		priv = sपंचांग32_setup_counter_device(dev);
	अन्यथा
		priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);

	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->regmap = ddata->regmap;
	priv->clk = ddata->clk;
	priv->max_arr = ddata->max_arr;
	priv->triggers = triggers_table[index];
	priv->valids = cfg->valids_table[index];
	sपंचांग32_समयr_detect_trgo2(priv);
	mutex_init(&priv->lock);

	ret = sपंचांग32_रेजिस्टर_iio_triggers(priv);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_समयr_trigger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = platक्रमm_get_drvdata(pdev);
	u32 val;

	/* Unरेजिस्टर triggers beक्रमe everything can be safely turned off */
	sपंचांग32_unरेजिस्टर_iio_triggers(priv);

	/* Check अगर nobody अन्यथा use the समयr, then disable it */
	regmap_पढ़ो(priv->regmap, TIM_CCER, &val);
	अगर (!(val & TIM_CCER_CCXE))
		regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, 0);

	अगर (priv->enabled)
		clk_disable(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_समयr_trigger_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = dev_get_drvdata(dev);

	/* Only take care of enabled समयr: करोn't disturb other MFD child */
	अगर (priv->enabled) अणु
		/* Backup रेजिस्टरs that may get lost in low घातer mode */
		regmap_पढ़ो(priv->regmap, TIM_CR1, &priv->bak.cr1);
		regmap_पढ़ो(priv->regmap, TIM_CR2, &priv->bak.cr2);
		regmap_पढ़ो(priv->regmap, TIM_PSC, &priv->bak.psc);
		regmap_पढ़ो(priv->regmap, TIM_ARR, &priv->bak.arr);
		regmap_पढ़ो(priv->regmap, TIM_CNT, &priv->bak.cnt);
		regmap_पढ़ो(priv->regmap, TIM_SMCR, &priv->bak.smcr);

		/* Disable the समयr */
		regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, 0);
		clk_disable(priv->clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_समयr_trigger_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_समयr_trigger *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (priv->enabled) अणु
		ret = clk_enable(priv->clk);
		अगर (ret)
			वापस ret;

		/* restore master/slave modes */
		regmap_ग_लिखो(priv->regmap, TIM_SMCR, priv->bak.smcr);
		regmap_ग_लिखो(priv->regmap, TIM_CR2, priv->bak.cr2);

		/* restore sampling_frequency (trgo / trgo2 triggers) */
		regmap_ग_लिखो(priv->regmap, TIM_PSC, priv->bak.psc);
		regmap_ग_लिखो(priv->regmap, TIM_ARR, priv->bak.arr);
		regmap_ग_लिखो(priv->regmap, TIM_CNT, priv->bak.cnt);

		/* Also re-enables the समयr */
		regmap_ग_लिखो(priv->regmap, TIM_CR1, priv->bak.cr1);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sपंचांग32_समयr_trigger_pm_ops,
			 sपंचांग32_समयr_trigger_suspend,
			 sपंचांग32_समयr_trigger_resume);

अटल स्थिर काष्ठा sपंचांग32_समयr_trigger_cfg sपंचांग32_समयr_trg_cfg = अणु
	.valids_table = valids_table,
	.num_valids_table = ARRAY_SIZE(valids_table),
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_समयr_trigger_cfg sपंचांग32h7_समयr_trg_cfg = अणु
	.valids_table = sपंचांग32h7_valids_table,
	.num_valids_table = ARRAY_SIZE(sपंचांग32h7_valids_table),
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_trig_of_match[] = अणु
	अणु
		.compatible = "st,stm32-timer-trigger",
		.data = (व्योम *)&sपंचांग32_समयr_trg_cfg,
	पूर्ण, अणु
		.compatible = "st,stm32h7-timer-trigger",
		.data = (व्योम *)&sपंचांग32h7_समयr_trg_cfg,
	पूर्ण,
	अणु /* end node */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_trig_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_समयr_trigger_driver = अणु
	.probe = sपंचांग32_समयr_trigger_probe,
	.हटाओ = sपंचांग32_समयr_trigger_हटाओ,
	.driver = अणु
		.name = "stm32-timer-trigger",
		.of_match_table = sपंचांग32_trig_of_match,
		.pm = &sपंचांग32_समयr_trigger_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_समयr_trigger_driver);

MODULE_ALIAS("platform: stm32-timer-trigger");
MODULE_DESCRIPTION("STMicroelectronics STM32 Timer Trigger driver");
MODULE_LICENSE("GPL v2");
