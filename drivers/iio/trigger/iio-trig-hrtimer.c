<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * The industrial I/O periodic hrसमयr trigger driver
 *
 * Copyright (C) Intuitive Aerial AB
 * Written by Marten Svanfeldt, marten@पूर्णांकuitiveaerial.com
 * Copyright (C) 2012, Analog Devices Inc.
 *	Author: Lars-Peter Clausen <lars@metafoo.de>
 * Copyright (C) 2015, Intel Corporation
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/hrसमयr.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/sw_trigger.h>

/* Defined locally, not in समय64.h yet. */
#घोषणा PSEC_PER_SEC   1000000000000LL

/* शेष sampling frequency - 100Hz */
#घोषणा HRTIMER_DEFAULT_SAMPLING_FREQUENCY 100

काष्ठा iio_hrसमयr_info अणु
	काष्ठा iio_sw_trigger swt;
	काष्ठा hrसमयr समयr;
	पूर्णांक sampling_frequency[2];
	kसमय_प्रकार period;
पूर्ण;

अटल स्थिर काष्ठा config_item_type iio_hrसमयr_type = अणु
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल
sमाप_प्रकार iio_hrसमयr_show_sampling_frequency(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा iio_trigger *trig = to_iio_trigger(dev);
	काष्ठा iio_hrसमयr_info *info = iio_trigger_get_drvdata(trig);

	वापस iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_MICRO,
			ARRAY_SIZE(info->sampling_frequency),
			info->sampling_frequency);
पूर्ण

अटल
sमाप_प्रकार iio_hrसमयr_store_sampling_frequency(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_trigger *trig = to_iio_trigger(dev);
	काष्ठा iio_hrसमयr_info *info = iio_trigger_get_drvdata(trig);
	अचिन्हित दीर्घ दीर्घ val;
	u64 period;
	पूर्णांक पूर्णांकeger, fract, ret;

	ret = iio_str_to_fixpoपूर्णांक(buf, 100, &पूर्णांकeger, &fract);
	अगर (ret)
		वापस ret;
	अगर (पूर्णांकeger < 0 || fract < 0)
		वापस -दुस्फल;

	val = fract + 1000ULL * पूर्णांकeger;  /* mHz */

	अगर (!val || val > अच_पूर्णांक_उच्च)
		वापस -EINVAL;

	info->sampling_frequency[0] = पूर्णांकeger;  /* Hz */
	info->sampling_frequency[1] = fract * 1000;  /* uHz */
	period = PSEC_PER_SEC;
	करो_भाग(period, val);
	info->period = period;  /* nS */

	वापस len;
पूर्ण

अटल DEVICE_ATTR(sampling_frequency, S_IRUGO | S_IWUSR,
		   iio_hrसमयr_show_sampling_frequency,
		   iio_hrसमयr_store_sampling_frequency);

अटल काष्ठा attribute *iio_hrसमयr_attrs[] = अणु
	&dev_attr_sampling_frequency.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group iio_hrसमयr_attr_group = अणु
	.attrs = iio_hrसमयr_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *iio_hrसमयr_attr_groups[] = अणु
	&iio_hrसमयr_attr_group,
	शून्य
पूर्ण;

अटल क्रमागत hrसमयr_restart iio_hrसमयr_trig_handler(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा iio_hrसमयr_info *info;

	info = container_of(समयr, काष्ठा iio_hrसमयr_info, समयr);

	hrसमयr_क्रमward_now(समयr, info->period);
	iio_trigger_poll(info->swt.trigger);

	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक iio_trig_hrसमयr_set_state(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_hrसमयr_info *trig_info;

	trig_info = iio_trigger_get_drvdata(trig);

	अगर (state)
		hrसमयr_start(&trig_info->समयr, trig_info->period,
			      HRTIMER_MODE_REL_HARD);
	अन्यथा
		hrसमयr_cancel(&trig_info->समयr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops iio_hrसमयr_trigger_ops = अणु
	.set_trigger_state = iio_trig_hrसमयr_set_state,
पूर्ण;

अटल काष्ठा iio_sw_trigger *iio_trig_hrसमयr_probe(स्थिर अक्षर *name)
अणु
	काष्ठा iio_hrसमयr_info *trig_info;
	पूर्णांक ret;

	trig_info = kzalloc(माप(*trig_info), GFP_KERNEL);
	अगर (!trig_info)
		वापस ERR_PTR(-ENOMEM);

	trig_info->swt.trigger = iio_trigger_alloc(शून्य, "%s", name);
	अगर (!trig_info->swt.trigger) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_trig_info;
	पूर्ण

	iio_trigger_set_drvdata(trig_info->swt.trigger, trig_info);
	trig_info->swt.trigger->ops = &iio_hrसमयr_trigger_ops;
	trig_info->swt.trigger->dev.groups = iio_hrसमयr_attr_groups;

	hrसमयr_init(&trig_info->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_HARD);
	trig_info->समयr.function = iio_hrसमयr_trig_handler;

	trig_info->sampling_frequency[0] = HRTIMER_DEFAULT_SAMPLING_FREQUENCY;
	trig_info->period = NSEC_PER_SEC / trig_info->sampling_frequency[0];

	ret = iio_trigger_रेजिस्टर(trig_info->swt.trigger);
	अगर (ret)
		जाओ err_मुक्त_trigger;

	iio_swt_group_init_type_name(&trig_info->swt, name, &iio_hrसमयr_type);
	वापस &trig_info->swt;
err_मुक्त_trigger:
	iio_trigger_मुक्त(trig_info->swt.trigger);
err_मुक्त_trig_info:
	kमुक्त(trig_info);

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक iio_trig_hrसमयr_हटाओ(काष्ठा iio_sw_trigger *swt)
अणु
	काष्ठा iio_hrसमयr_info *trig_info;

	trig_info = iio_trigger_get_drvdata(swt->trigger);

	iio_trigger_unरेजिस्टर(swt->trigger);

	/* cancel the समयr after unreg to make sure no one rearms it */
	hrसमयr_cancel(&trig_info->समयr);
	iio_trigger_मुक्त(swt->trigger);
	kमुक्त(trig_info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_sw_trigger_ops iio_trig_hrसमयr_ops = अणु
	.probe		= iio_trig_hrसमयr_probe,
	.हटाओ		= iio_trig_hrसमयr_हटाओ,
पूर्ण;

अटल काष्ठा iio_sw_trigger_type iio_trig_hrसमयr = अणु
	.name = "hrtimer",
	.owner = THIS_MODULE,
	.ops = &iio_trig_hrसमयr_ops,
पूर्ण;

module_iio_sw_trigger_driver(iio_trig_hrसमयr);

MODULE_AUTHOR("Marten Svanfeldt <marten@intuitiveaerial.com>");
MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("Periodic hrtimer trigger for the IIO subsystem");
MODULE_LICENSE("GPL v2");
