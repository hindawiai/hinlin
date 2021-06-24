<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTC subप्रणाली, base class
 *
 * Copyright (C) 2005 Tower Technologies
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 *
 * class skeleton from drivers/hwmon/hwmon.c
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/rtc.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "rtc-core.h"

अटल DEFINE_IDA(rtc_ida);
काष्ठा class *rtc_class;

अटल व्योम rtc_device_release(काष्ठा device *dev)
अणु
	काष्ठा rtc_device *rtc = to_rtc_device(dev);

	ida_simple_हटाओ(&rtc_ida, rtc->id);
	mutex_destroy(&rtc->ops_lock);
	kमुक्त(rtc);
पूर्ण

#अगर_घोषित CONFIG_RTC_HCTOSYS_DEVICE
/* Result of the last RTC to प्रणाली घड़ी attempt. */
पूर्णांक rtc_hctosys_ret = -ENODEV;

/* IMPORTANT: the RTC only stores whole seconds. It is arbitrary
 * whether it stores the most बंद value or the value with partial
 * seconds truncated. However, it is important that we use it to store
 * the truncated value. This is because otherwise it is necessary,
 * in an rtc sync function, to पढ़ो both xसमय.tv_sec and
 * xसमय.tv_nsec. On some processors (i.e. ARM), an atomic पढ़ो
 * of >32bits is not possible. So storing the most बंद value would
 * slow करोwn the sync API. So here we have the truncated value and
 * the best guess is to add 0.5s.
 */

अटल व्योम rtc_hctosys(काष्ठा rtc_device *rtc)
अणु
	पूर्णांक err;
	काष्ठा rtc_समय पंचांग;
	काष्ठा बारpec64 tv64 = अणु
		.tv_nsec = NSEC_PER_SEC >> 1,
	पूर्ण;

	err = rtc_पढ़ो_समय(rtc, &पंचांग);
	अगर (err) अणु
		dev_err(rtc->dev.parent,
			"hctosys: unable to read the hardware clock\n");
		जाओ err_पढ़ो;
	पूर्ण

	tv64.tv_sec = rtc_पंचांग_to_समय64(&पंचांग);

#अगर BITS_PER_LONG == 32
	अगर (tv64.tv_sec > पूर्णांक_उच्च) अणु
		err = -दुस्फल;
		जाओ err_पढ़ो;
	पूर्ण
#पूर्ण_अगर

	err = करो_समय_रखोofday64(&tv64);

	dev_info(rtc->dev.parent, "setting system clock to %ptR UTC (%lld)\n",
		 &पंचांग, (दीर्घ दीर्घ)tv64.tv_sec);

err_पढ़ो:
	rtc_hctosys_ret = err;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PM_SLEEP) && defined(CONFIG_RTC_HCTOSYS_DEVICE)
/*
 * On suspend(), measure the delta between one RTC and the
 * प्रणाली's wall घड़ी; restore it on resume().
 */

अटल काष्ठा बारpec64 old_rtc, old_प्रणाली, old_delta;

अटल पूर्णांक rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा rtc_device	*rtc = to_rtc_device(dev);
	काष्ठा rtc_समय		पंचांग;
	काष्ठा बारpec64	delta, delta_delta;
	पूर्णांक err;

	अगर (समयkeeping_rtc_skipsuspend())
		वापस 0;

	अगर (म_भेद(dev_name(&rtc->dev), CONFIG_RTC_HCTOSYS_DEVICE) != 0)
		वापस 0;

	/* snapshot the current RTC and प्रणाली समय at suspend*/
	err = rtc_पढ़ो_समय(rtc, &पंचांग);
	अगर (err < 0) अणु
		pr_debug("%s:  fail to read rtc time\n", dev_name(&rtc->dev));
		वापस 0;
	पूर्ण

	kसमय_get_real_ts64(&old_प्रणाली);
	old_rtc.tv_sec = rtc_पंचांग_to_समय64(&पंचांग);

	/*
	 * To aव्योम drअगरt caused by repeated suspend/resumes,
	 * which each can add ~1 second drअगरt error,
	 * try to compensate so the dअगरference in प्रणाली समय
	 * and rtc समय stays बंद to स्थिरant.
	 */
	delta = बारpec64_sub(old_प्रणाली, old_rtc);
	delta_delta = बारpec64_sub(delta, old_delta);
	अगर (delta_delta.tv_sec < -2 || delta_delta.tv_sec >= 2) अणु
		/*
		 * अगर delta_delta is too large, assume समय correction
		 * has occurred and set old_delta to the current delta.
		 */
		old_delta = delta;
	पूर्ण अन्यथा अणु
		/* Otherwise try to adjust old_प्रणाली to compensate */
		old_प्रणाली = बारpec64_sub(old_प्रणाली, delta_delta);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा rtc_device	*rtc = to_rtc_device(dev);
	काष्ठा rtc_समय		पंचांग;
	काष्ठा बारpec64	new_प्रणाली, new_rtc;
	काष्ठा बारpec64	sleep_समय;
	पूर्णांक err;

	अगर (समयkeeping_rtc_skipresume())
		वापस 0;

	rtc_hctosys_ret = -ENODEV;
	अगर (म_भेद(dev_name(&rtc->dev), CONFIG_RTC_HCTOSYS_DEVICE) != 0)
		वापस 0;

	/* snapshot the current rtc and प्रणाली समय at resume */
	kसमय_get_real_ts64(&new_प्रणाली);
	err = rtc_पढ़ो_समय(rtc, &पंचांग);
	अगर (err < 0) अणु
		pr_debug("%s:  fail to read rtc time\n", dev_name(&rtc->dev));
		वापस 0;
	पूर्ण

	new_rtc.tv_sec = rtc_पंचांग_to_समय64(&पंचांग);
	new_rtc.tv_nsec = 0;

	अगर (new_rtc.tv_sec < old_rtc.tv_sec) अणु
		pr_debug("%s:  time travel!\n", dev_name(&rtc->dev));
		वापस 0;
	पूर्ण

	/* calculate the RTC समय delta (sleep समय)*/
	sleep_समय = बारpec64_sub(new_rtc, old_rtc);

	/*
	 * Since these RTC suspend/resume handlers are not called
	 * at the very end of suspend or the start of resume,
	 * some run-समय may pass on either sides of the sleep समय
	 * so subtract kernel run-समय between rtc_suspend to rtc_resume
	 * to keep things accurate.
	 */
	sleep_समय = बारpec64_sub(sleep_समय,
				    बारpec64_sub(new_प्रणाली, old_प्रणाली));

	अगर (sleep_समय.tv_sec >= 0)
		समयkeeping_inject_sleepसमय64(&sleep_समय);
	rtc_hctosys_ret = 0;
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rtc_class_dev_pm_ops, rtc_suspend, rtc_resume);
#घोषणा RTC_CLASS_DEV_PM_OPS	(&rtc_class_dev_pm_ops)
#अन्यथा
#घोषणा RTC_CLASS_DEV_PM_OPS	शून्य
#पूर्ण_अगर

/* Ensure the caller will set the id beक्रमe releasing the device */
अटल काष्ठा rtc_device *rtc_allocate_device(व्योम)
अणु
	काष्ठा rtc_device *rtc;

	rtc = kzalloc(माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस शून्य;

	device_initialize(&rtc->dev);

	/*
	 * Drivers can revise this शेष after allocating the device.
	 * The शेष is what most RTCs करो: Increment seconds exactly one
	 * second after the ग_लिखो happened. This adds a शेष transport
	 * समय of 5ms which is at least halfways बंद to reality.
	 */
	rtc->set_offset_nsec = NSEC_PER_SEC + 5 * NSEC_PER_MSEC;

	rtc->irq_freq = 1;
	rtc->max_user_freq = 64;
	rtc->dev.class = rtc_class;
	rtc->dev.groups = rtc_get_dev_attribute_groups();
	rtc->dev.release = rtc_device_release;

	mutex_init(&rtc->ops_lock);
	spin_lock_init(&rtc->irq_lock);
	init_रुकोqueue_head(&rtc->irq_queue);

	/* Init समयrqueue */
	समयrqueue_init_head(&rtc->समयrqueue);
	INIT_WORK(&rtc->irqwork, rtc_समयr_करो_work);
	/* Init aie समयr */
	rtc_समयr_init(&rtc->aie_समयr, rtc_aie_update_irq, rtc);
	/* Init uie समयr */
	rtc_समयr_init(&rtc->uie_rtस_समयr, rtc_uie_update_irq, rtc);
	/* Init pie समयr */
	hrसमयr_init(&rtc->pie_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	rtc->pie_समयr.function = rtc_pie_update_irq;
	rtc->pie_enabled = 0;

	set_bit(RTC_FEATURE_ALARM, rtc->features);

	वापस rtc;
पूर्ण

अटल पूर्णांक rtc_device_get_id(काष्ठा device *dev)
अणु
	पूर्णांक of_id = -1, id = -1;

	अगर (dev->of_node)
		of_id = of_alias_get_id(dev->of_node, "rtc");
	अन्यथा अगर (dev->parent && dev->parent->of_node)
		of_id = of_alias_get_id(dev->parent->of_node, "rtc");

	अगर (of_id >= 0) अणु
		id = ida_simple_get(&rtc_ida, of_id, of_id + 1, GFP_KERNEL);
		अगर (id < 0)
			dev_warn(dev, "/aliases ID %d not available\n", of_id);
	पूर्ण

	अगर (id < 0)
		id = ida_simple_get(&rtc_ida, 0, 0, GFP_KERNEL);

	वापस id;
पूर्ण

अटल व्योम rtc_device_get_offset(काष्ठा rtc_device *rtc)
अणु
	समय64_t range_secs;
	u32 start_year;
	पूर्णांक ret;

	/*
	 * If RTC driver did not implement the range of RTC hardware device,
	 * then we can not expand the RTC range by adding or subtracting one
	 * offset.
	 */
	अगर (rtc->range_min == rtc->range_max)
		वापस;

	ret = device_property_पढ़ो_u32(rtc->dev.parent, "start-year",
				       &start_year);
	अगर (!ret) अणु
		rtc->start_secs = स_गढ़ो64(start_year, 1, 1, 0, 0, 0);
		rtc->set_start_समय = true;
	पूर्ण

	/*
	 * If user did not implement the start समय क्रम RTC driver, then no
	 * need to expand the RTC range.
	 */
	अगर (!rtc->set_start_समय)
		वापस;

	range_secs = rtc->range_max - rtc->range_min + 1;

	/*
	 * If the start_secs is larger than the maximum seconds (rtc->range_max)
	 * supported by RTC hardware or the maximum seconds of new expanded
	 * range (start_secs + rtc->range_max - rtc->range_min) is less than
	 * rtc->range_min, which means the minimum seconds (rtc->range_min) of
	 * RTC hardware will be mapped to start_secs by adding one offset, so
	 * the offset seconds calculation क्रमmula should be:
	 * rtc->offset_secs = rtc->start_secs - rtc->range_min;
	 *
	 * If the start_secs is larger than the minimum seconds (rtc->range_min)
	 * supported by RTC hardware, then there is one region is overlapped
	 * between the original RTC hardware range and the new expanded range,
	 * and this overlapped region करो not need to be mapped पूर्णांकo the new
	 * expanded range due to it is valid क्रम RTC device. So the minimum
	 * seconds of RTC hardware (rtc->range_min) should be mapped to
	 * rtc->range_max + 1, then the offset seconds क्रमmula should be:
	 * rtc->offset_secs = rtc->range_max - rtc->range_min + 1;
	 *
	 * If the start_secs is less than the minimum seconds (rtc->range_min),
	 * which is similar to हाल 2. So the start_secs should be mapped to
	 * start_secs + rtc->range_max - rtc->range_min + 1, then the
	 * offset seconds क्रमmula should be:
	 * rtc->offset_secs = -(rtc->range_max - rtc->range_min + 1);
	 *
	 * Otherwise the offset seconds should be 0.
	 */
	अगर (rtc->start_secs > rtc->range_max ||
	    rtc->start_secs + range_secs - 1 < rtc->range_min)
		rtc->offset_secs = rtc->start_secs - rtc->range_min;
	अन्यथा अगर (rtc->start_secs > rtc->range_min)
		rtc->offset_secs = range_secs;
	अन्यथा अगर (rtc->start_secs < rtc->range_min)
		rtc->offset_secs = -range_secs;
	अन्यथा
		rtc->offset_secs = 0;
पूर्ण

अटल व्योम devm_rtc_unरेजिस्टर_device(व्योम *data)
अणु
	काष्ठा rtc_device *rtc = data;

	mutex_lock(&rtc->ops_lock);
	/*
	 * Remove innards of this RTC, then disable it, beक्रमe
	 * letting any rtc_class_खोलो() users access it again
	 */
	rtc_proc_del_device(rtc);
	cdev_device_del(&rtc->अक्षर_dev, &rtc->dev);
	rtc->ops = शून्य;
	mutex_unlock(&rtc->ops_lock);
पूर्ण

अटल व्योम devm_rtc_release_device(व्योम *res)
अणु
	काष्ठा rtc_device *rtc = res;

	put_device(&rtc->dev);
पूर्ण

काष्ठा rtc_device *devm_rtc_allocate_device(काष्ठा device *dev)
अणु
	काष्ठा rtc_device *rtc;
	पूर्णांक id, err;

	id = rtc_device_get_id(dev);
	अगर (id < 0)
		वापस ERR_PTR(id);

	rtc = rtc_allocate_device();
	अगर (!rtc) अणु
		ida_simple_हटाओ(&rtc_ida, id);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	rtc->id = id;
	rtc->dev.parent = dev;
	dev_set_name(&rtc->dev, "rtc%d", id);

	err = devm_add_action_or_reset(dev, devm_rtc_release_device, rtc);
	अगर (err)
		वापस ERR_PTR(err);

	वापस rtc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_rtc_allocate_device);

पूर्णांक __devm_rtc_रेजिस्टर_device(काष्ठा module *owner, काष्ठा rtc_device *rtc)
अणु
	काष्ठा rtc_wkalrm alrm;
	पूर्णांक err;

	अगर (!rtc->ops) अणु
		dev_dbg(&rtc->dev, "no ops set\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!rtc->ops->set_alarm)
		clear_bit(RTC_FEATURE_ALARM, rtc->features);

	rtc->owner = owner;
	rtc_device_get_offset(rtc);

	/* Check to see अगर there is an ALARM alपढ़ोy set in hw */
	err = __rtc_पढ़ो_alarm(rtc, &alrm);
	अगर (!err && !rtc_valid_पंचांग(&alrm.समय))
		rtc_initialize_alarm(rtc, &alrm);

	rtc_dev_prepare(rtc);

	err = cdev_device_add(&rtc->अक्षर_dev, &rtc->dev);
	अगर (err)
		dev_warn(rtc->dev.parent, "failed to add char device %d:%d\n",
			 MAJOR(rtc->dev.devt), rtc->id);
	अन्यथा
		dev_dbg(rtc->dev.parent, "char device (%d:%d)\n",
			MAJOR(rtc->dev.devt), rtc->id);

	rtc_proc_add_device(rtc);

	dev_info(rtc->dev.parent, "registered as %s\n",
		 dev_name(&rtc->dev));

#अगर_घोषित CONFIG_RTC_HCTOSYS_DEVICE
	अगर (!म_भेद(dev_name(&rtc->dev), CONFIG_RTC_HCTOSYS_DEVICE))
		rtc_hctosys(rtc);
#पूर्ण_अगर

	वापस devm_add_action_or_reset(rtc->dev.parent,
					devm_rtc_unरेजिस्टर_device, rtc);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_rtc_रेजिस्टर_device);

/**
 * devm_rtc_device_रेजिस्टर - resource managed rtc_device_रेजिस्टर()
 * @dev: the device to रेजिस्टर
 * @name: the name of the device (unused)
 * @ops: the rtc operations काष्ठाure
 * @owner: the module owner
 *
 * @वापस a काष्ठा rtc on success, or an ERR_PTR on error
 *
 * Managed rtc_device_रेजिस्टर(). The rtc_device वापसed from this function
 * are स्वतःmatically मुक्तd on driver detach.
 * This function is deprecated, use devm_rtc_allocate_device and
 * rtc_रेजिस्टर_device instead
 */
काष्ठा rtc_device *devm_rtc_device_रेजिस्टर(काष्ठा device *dev,
					    स्थिर अक्षर *name,
					    स्थिर काष्ठा rtc_class_ops *ops,
					    काष्ठा module *owner)
अणु
	काष्ठा rtc_device *rtc;
	पूर्णांक err;

	rtc = devm_rtc_allocate_device(dev);
	अगर (IS_ERR(rtc))
		वापस rtc;

	rtc->ops = ops;

	err = __devm_rtc_रेजिस्टर_device(owner, rtc);
	अगर (err)
		वापस ERR_PTR(err);

	वापस rtc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_rtc_device_रेजिस्टर);

अटल पूर्णांक __init rtc_init(व्योम)
अणु
	rtc_class = class_create(THIS_MODULE, "rtc");
	अगर (IS_ERR(rtc_class)) अणु
		pr_err("couldn't create class\n");
		वापस PTR_ERR(rtc_class);
	पूर्ण
	rtc_class->pm = RTC_CLASS_DEV_PM_OPS;
	rtc_dev_init();
	वापस 0;
पूर्ण
subsys_initcall(rtc_init);
