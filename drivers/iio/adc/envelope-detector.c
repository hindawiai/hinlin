<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम an envelope detector using a DAC and a comparator
 *
 * Copyright (C) 2016 Axentia Technologies AB
 *
 * Author: Peter Rosin <peda@axentia.se>
 */

/*
 * The DAC is used to find the peak level of an alternating voltage input
 * संकेत by a binary search using the output of a comparator wired to
 * an पूर्णांकerrupt pin. Like so:
 *                           _
 *                          | \
 *     input +------>-------|+ \
 *                          |   \
 *            .-------.     |    पूर्ण---.
 *            |       |     |   /    |
 *            |    dac|-->--|- /     |
 *            |       |     |_/      |
 *            |       |              |
 *            |       |              |
 *            |    irq|------<-------'
 *            |       |
 *            '-------'
 */

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

काष्ठा envelope अणु
	spinlock_t comp_lock; /* protects comp */
	पूर्णांक comp;

	काष्ठा mutex पढ़ो_lock; /* protects everything अन्यथा */

	पूर्णांक comp_irq;
	u32 comp_irq_trigger;
	u32 comp_irq_trigger_inv;

	काष्ठा iio_channel *dac;
	काष्ठा delayed_work comp_समयout;

	अचिन्हित पूर्णांक comp_पूर्णांकerval;
	bool invert;
	u32 dac_max;

	पूर्णांक high;
	पूर्णांक level;
	पूर्णांक low;

	काष्ठा completion करोne;
पूर्ण;

/*
 * The envelope_detector_comp_latch function works together with the compare
 * पूर्णांकerrupt service routine below (envelope_detector_comp_isr) as a latch
 * (one-bit memory) क्रम अगर the पूर्णांकerrupt has triggered since last calling
 * this function.
 * The ..._comp_isr function disables the पूर्णांकerrupt so that the cpu करोes not
 * need to service a possible पूर्णांकerrupt flood from the comparator when no-one
 * cares anyway, and this ..._comp_latch function reenables them again अगर
 * needed.
 */
अटल पूर्णांक envelope_detector_comp_latch(काष्ठा envelope *env)
अणु
	पूर्णांक comp;

	spin_lock_irq(&env->comp_lock);
	comp = env->comp;
	env->comp = 0;
	spin_unlock_irq(&env->comp_lock);

	अगर (!comp)
		वापस 0;

	/*
	 * The irq was disabled, and is reenabled just now.
	 * But there might have been a pending irq that
	 * happened जबतक the irq was disabled that fires
	 * just as the irq is reenabled. That is not what
	 * is desired.
	 */
	enable_irq(env->comp_irq);

	/* So, synchronize this possibly pending irq... */
	synchronize_irq(env->comp_irq);

	/* ...and reकरो the whole dance. */
	spin_lock_irq(&env->comp_lock);
	comp = env->comp;
	env->comp = 0;
	spin_unlock_irq(&env->comp_lock);

	अगर (comp)
		enable_irq(env->comp_irq);

	वापस 1;
पूर्ण

अटल irqवापस_t envelope_detector_comp_isr(पूर्णांक irq, व्योम *ctx)
अणु
	काष्ठा envelope *env = ctx;

	spin_lock(&env->comp_lock);
	env->comp = 1;
	disable_irq_nosync(env->comp_irq);
	spin_unlock(&env->comp_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम envelope_detector_setup_compare(काष्ठा envelope *env)
अणु
	पूर्णांक ret;

	/*
	 * Do a binary search क्रम the peak input level, and stop
	 * when that level is "trapped" between two adjacent DAC
	 * values.
	 * When invert is active, use the midpoपूर्णांक न्यूनमान so that
	 * env->level ends up as env->low when the termination
	 * criteria below is fulfilled, and use the midpoपूर्णांक
	 * उच्चमानing when invert is not active so that env->level
	 * ends up as env->high in that हाल.
	 */
	env->level = (env->high + env->low + !env->invert) / 2;

	अगर (env->high == env->low + 1) अणु
		complete(&env->करोne);
		वापस;
	पूर्ण

	/* Set a "safe" DAC level (अगर there is such a thing)... */
	ret = iio_ग_लिखो_channel_raw(env->dac, env->invert ? 0 : env->dac_max);
	अगर (ret < 0)
		जाओ err;

	/* ...clear the comparison result... */
	envelope_detector_comp_latch(env);

	/* ...set the real DAC level... */
	ret = iio_ग_लिखो_channel_raw(env->dac, env->level);
	अगर (ret < 0)
		जाओ err;

	/* ...and रुको क्रम a bit to see अगर the latch catches anything. */
	schedule_delayed_work(&env->comp_समयout,
			      msecs_to_jअगरfies(env->comp_पूर्णांकerval));
	वापस;

err:
	env->level = ret;
	complete(&env->करोne);
पूर्ण

अटल व्योम envelope_detector_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा envelope *env = container_of(work, काष्ठा envelope,
					    comp_समयout.work);

	/* Adjust low/high depending on the latch content... */
	अगर (!envelope_detector_comp_latch(env) ^ !env->invert)
		env->low = env->level;
	अन्यथा
		env->high = env->level;

	/* ...and जारी the search. */
	envelope_detector_setup_compare(env);
पूर्ण

अटल पूर्णांक envelope_detector_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				      काष्ठा iio_chan_spec स्थिर *chan,
				      पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा envelope *env = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		/*
		 * When invert is active, start with high=max+1 and low=0
		 * since we will end up with the low value when the
		 * termination criteria is fulfilled (rounding करोwn). And
		 * start with high=max and low=-1 when invert is not active
		 * since we will end up with the high value in that हाल.
		 * This ensures that the वापसed value in both हालs are
		 * in the same range as the DAC and is a value that has not
		 * triggered the comparator.
		 */
		mutex_lock(&env->पढ़ो_lock);
		env->high = env->dac_max + env->invert;
		env->low = -1 + env->invert;
		envelope_detector_setup_compare(env);
		रुको_क्रम_completion(&env->करोne);
		अगर (env->level < 0) अणु
			ret = env->level;
			जाओ err_unlock;
		पूर्ण
		*val = env->invert ? env->dac_max - env->level : env->level;
		mutex_unlock(&env->पढ़ो_lock);

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		वापस iio_पढ़ो_channel_scale(env->dac, val, val2);
	पूर्ण

	वापस -EINVAL;

err_unlock:
	mutex_unlock(&env->पढ़ो_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार envelope_show_invert(काष्ठा iio_dev *indio_dev,
				    uपूर्णांकptr_t निजी,
				    काष्ठा iio_chan_spec स्थिर *ch, अक्षर *buf)
अणु
	काष्ठा envelope *env = iio_priv(indio_dev);

	वापस प्र_लिखो(buf, "%u\n", env->invert);
पूर्ण

अटल sमाप_प्रकार envelope_store_invert(काष्ठा iio_dev *indio_dev,
				     uपूर्णांकptr_t निजी,
				     काष्ठा iio_chan_spec स्थिर *ch,
				     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा envelope *env = iio_priv(indio_dev);
	अचिन्हित दीर्घ invert;
	पूर्णांक ret;
	u32 trigger;

	ret = kम_से_अदीर्घ(buf, 0, &invert);
	अगर (ret < 0)
		वापस ret;
	अगर (invert > 1)
		वापस -EINVAL;

	trigger = invert ? env->comp_irq_trigger_inv : env->comp_irq_trigger;

	mutex_lock(&env->पढ़ो_lock);
	अगर (invert != env->invert)
		ret = irq_set_irq_type(env->comp_irq, trigger);
	अगर (!ret) अणु
		env->invert = invert;
		ret = len;
	पूर्ण
	mutex_unlock(&env->पढ़ो_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार envelope_show_comp_पूर्णांकerval(काष्ठा iio_dev *indio_dev,
					   uपूर्णांकptr_t निजी,
					   काष्ठा iio_chan_spec स्थिर *ch,
					   अक्षर *buf)
अणु
	काष्ठा envelope *env = iio_priv(indio_dev);

	वापस प्र_लिखो(buf, "%u\n", env->comp_पूर्णांकerval);
पूर्ण

अटल sमाप_प्रकार envelope_store_comp_पूर्णांकerval(काष्ठा iio_dev *indio_dev,
					    uपूर्णांकptr_t निजी,
					    काष्ठा iio_chan_spec स्थिर *ch,
					    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा envelope *env = iio_priv(indio_dev);
	अचिन्हित दीर्घ पूर्णांकerval;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &पूर्णांकerval);
	अगर (ret < 0)
		वापस ret;
	अगर (पूर्णांकerval > 1000)
		वापस -EINVAL;

	mutex_lock(&env->पढ़ो_lock);
	env->comp_पूर्णांकerval = पूर्णांकerval;
	mutex_unlock(&env->पढ़ो_lock);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info envelope_detector_ext_info[] = अणु
	अणु .name = "invert",
	  .पढ़ो = envelope_show_invert,
	  .ग_लिखो = envelope_store_invert, पूर्ण,
	अणु .name = "compare_interval",
	  .पढ़ो = envelope_show_comp_पूर्णांकerval,
	  .ग_लिखो = envelope_store_comp_पूर्णांकerval, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec envelope_detector_iio_channel = अणु
	.type = IIO_ALTVOLTAGE,
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW)
			    | BIT(IIO_CHAN_INFO_SCALE),
	.ext_info = envelope_detector_ext_info,
	.indexed = 1,
पूर्ण;

अटल स्थिर काष्ठा iio_info envelope_detector_info = अणु
	.पढ़ो_raw = &envelope_detector_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक envelope_detector_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा envelope *env;
	क्रमागत iio_chan_type type;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*env));
	अगर (!indio_dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, indio_dev);
	env = iio_priv(indio_dev);
	env->comp_पूर्णांकerval = 50; /* some sensible शेष? */

	spin_lock_init(&env->comp_lock);
	mutex_init(&env->पढ़ो_lock);
	init_completion(&env->करोne);
	INIT_DELAYED_WORK(&env->comp_समयout, envelope_detector_समयout);

	indio_dev->name = dev_name(dev);
	indio_dev->info = &envelope_detector_info;
	indio_dev->channels = &envelope_detector_iio_channel;
	indio_dev->num_channels = 1;

	env->dac = devm_iio_channel_get(dev, "dac");
	अगर (IS_ERR(env->dac))
		वापस dev_err_probe(dev, PTR_ERR(env->dac),
				     "failed to get dac input channel\n");

	env->comp_irq = platक्रमm_get_irq_byname(pdev, "comp");
	अगर (env->comp_irq < 0)
		वापस env->comp_irq;

	ret = devm_request_irq(dev, env->comp_irq, envelope_detector_comp_isr,
			       0, "envelope-detector", env);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "failed to request interrupt\n");

	env->comp_irq_trigger = irq_get_trigger_type(env->comp_irq);
	अगर (env->comp_irq_trigger & IRQF_TRIGGER_RISING)
		env->comp_irq_trigger_inv |= IRQF_TRIGGER_FALLING;
	अगर (env->comp_irq_trigger & IRQF_TRIGGER_FALLING)
		env->comp_irq_trigger_inv |= IRQF_TRIGGER_RISING;
	अगर (env->comp_irq_trigger & IRQF_TRIGGER_HIGH)
		env->comp_irq_trigger_inv |= IRQF_TRIGGER_LOW;
	अगर (env->comp_irq_trigger & IRQF_TRIGGER_LOW)
		env->comp_irq_trigger_inv |= IRQF_TRIGGER_HIGH;

	ret = iio_get_channel_type(env->dac, &type);
	अगर (ret < 0)
		वापस ret;

	अगर (type != IIO_VOLTAGE) अणु
		dev_err(dev, "dac is of the wrong type\n");
		वापस -EINVAL;
	पूर्ण

	ret = iio_पढ़ो_max_channel_raw(env->dac, &env->dac_max);
	अगर (ret < 0) अणु
		dev_err(dev, "dac does not indicate its raw maximum value\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id envelope_detector_match[] = अणु
	अणु .compatible = "axentia,tse850-envelope-detector", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, envelope_detector_match);

अटल काष्ठा platक्रमm_driver envelope_detector_driver = अणु
	.probe = envelope_detector_probe,
	.driver = अणु
		.name = "iio-envelope-detector",
		.of_match_table = envelope_detector_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(envelope_detector_driver);

MODULE_DESCRIPTION("Envelope detector using a DAC and a comparator");
MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_LICENSE("GPL v2");
