<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2020 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 *
 * Based on panfrost_devfreq.c:
 *   Copyright 2019 Collabora ltd.
 */
#समावेश <linux/clk.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/devfreq_cooling.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/property.h>

#समावेश "lima_device.h"
#समावेश "lima_devfreq.h"

अटल व्योम lima_devfreq_update_utilization(काष्ठा lima_devfreq *devfreq)
अणु
	kसमय_प्रकार now, last;

	now = kसमय_get();
	last = devfreq->समय_last_update;

	अगर (devfreq->busy_count > 0)
		devfreq->busy_समय += kसमय_sub(now, last);
	अन्यथा
		devfreq->idle_समय += kसमय_sub(now, last);

	devfreq->समय_last_update = now;
पूर्ण

अटल पूर्णांक lima_devfreq_target(काष्ठा device *dev, अचिन्हित दीर्घ *freq,
			       u32 flags)
अणु
	काष्ठा dev_pm_opp *opp;

	opp = devfreq_recommended_opp(dev, freq, flags);
	अगर (IS_ERR(opp))
		वापस PTR_ERR(opp);
	dev_pm_opp_put(opp);

	वापस dev_pm_opp_set_rate(dev, *freq);
पूर्ण

अटल व्योम lima_devfreq_reset(काष्ठा lima_devfreq *devfreq)
अणु
	devfreq->busy_समय = 0;
	devfreq->idle_समय = 0;
	devfreq->समय_last_update = kसमय_get();
पूर्ण

अटल पूर्णांक lima_devfreq_get_dev_status(काष्ठा device *dev,
				       काष्ठा devfreq_dev_status *status)
अणु
	काष्ठा lima_device *ldev = dev_get_drvdata(dev);
	काष्ठा lima_devfreq *devfreq = &ldev->devfreq;
	अचिन्हित दीर्घ irqflags;

	status->current_frequency = clk_get_rate(ldev->clk_gpu);

	spin_lock_irqsave(&devfreq->lock, irqflags);

	lima_devfreq_update_utilization(devfreq);

	status->total_समय = kसमय_प्रकारo_ns(kसमय_add(devfreq->busy_समय,
						   devfreq->idle_समय));
	status->busy_समय = kसमय_प्रकारo_ns(devfreq->busy_समय);

	lima_devfreq_reset(devfreq);

	spin_unlock_irqrestore(&devfreq->lock, irqflags);

	dev_dbg(ldev->dev, "busy %lu total %lu %lu %% freq %lu MHz\n",
		status->busy_समय, status->total_समय,
		status->busy_समय / (status->total_समय / 100),
		status->current_frequency / 1000 / 1000);

	वापस 0;
पूर्ण

अटल काष्ठा devfreq_dev_profile lima_devfreq_profile = अणु
	.समयr = DEVFREQ_TIMER_DELAYED,
	.polling_ms = 50, /* ~3 frames */
	.target = lima_devfreq_target,
	.get_dev_status = lima_devfreq_get_dev_status,
पूर्ण;

व्योम lima_devfreq_fini(काष्ठा lima_device *ldev)
अणु
	काष्ठा lima_devfreq *devfreq = &ldev->devfreq;

	अगर (devfreq->cooling) अणु
		devfreq_cooling_unरेजिस्टर(devfreq->cooling);
		devfreq->cooling = शून्य;
	पूर्ण

	अगर (devfreq->devfreq) अणु
		devm_devfreq_हटाओ_device(ldev->dev, devfreq->devfreq);
		devfreq->devfreq = शून्य;
	पूर्ण
पूर्ण

पूर्णांक lima_devfreq_init(काष्ठा lima_device *ldev)
अणु
	काष्ठा thermal_cooling_device *cooling;
	काष्ठा device *dev = ldev->dev;
	काष्ठा devfreq *devfreq;
	काष्ठा lima_devfreq *ldevfreq = &ldev->devfreq;
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ cur_freq;
	पूर्णांक ret;

	अगर (!device_property_present(dev, "operating-points-v2"))
		/* Optional, जारी without devfreq */
		वापस 0;

	spin_lock_init(&ldevfreq->lock);

	ret = devm_pm_opp_set_clkname(dev, "core");
	अगर (ret)
		वापस ret;

	ret = devm_pm_opp_set_regulators(dev, (स्थिर अक्षर *[])अणु "mali" पूर्ण, 1);
	अगर (ret) अणु
		/* Continue अगर the optional regulator is missing */
		अगर (ret != -ENODEV)
			वापस ret;
	पूर्ण

	ret = devm_pm_opp_of_add_table(dev);
	अगर (ret)
		वापस ret;

	lima_devfreq_reset(ldevfreq);

	cur_freq = clk_get_rate(ldev->clk_gpu);

	opp = devfreq_recommended_opp(dev, &cur_freq, 0);
	अगर (IS_ERR(opp))
		वापस PTR_ERR(opp);

	lima_devfreq_profile.initial_freq = cur_freq;
	dev_pm_opp_put(opp);

	/*
	 * Setup शेष thresholds क्रम the simple_ondemand governor.
	 * The values are chosen based on experiments.
	 */
	ldevfreq->gov_data.upthreshold = 30;
	ldevfreq->gov_data.करोwndअगरferential = 5;

	devfreq = devm_devfreq_add_device(dev, &lima_devfreq_profile,
					  DEVFREQ_GOV_SIMPLE_ONDEMAND,
					  &ldevfreq->gov_data);
	अगर (IS_ERR(devfreq)) अणु
		dev_err(dev, "Couldn't initialize GPU devfreq\n");
		वापस PTR_ERR(devfreq);
	पूर्ण

	ldevfreq->devfreq = devfreq;

	cooling = of_devfreq_cooling_रेजिस्टर(dev->of_node, devfreq);
	अगर (IS_ERR(cooling))
		dev_info(dev, "Failed to register cooling device\n");
	अन्यथा
		ldevfreq->cooling = cooling;

	वापस 0;
पूर्ण

व्योम lima_devfreq_record_busy(काष्ठा lima_devfreq *devfreq)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (!devfreq->devfreq)
		वापस;

	spin_lock_irqsave(&devfreq->lock, irqflags);

	lima_devfreq_update_utilization(devfreq);

	devfreq->busy_count++;

	spin_unlock_irqrestore(&devfreq->lock, irqflags);
पूर्ण

व्योम lima_devfreq_record_idle(काष्ठा lima_devfreq *devfreq)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (!devfreq->devfreq)
		वापस;

	spin_lock_irqsave(&devfreq->lock, irqflags);

	lima_devfreq_update_utilization(devfreq);

	WARN_ON(--devfreq->busy_count < 0);

	spin_unlock_irqrestore(&devfreq->lock, irqflags);
पूर्ण

पूर्णांक lima_devfreq_resume(काष्ठा lima_devfreq *devfreq)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (!devfreq->devfreq)
		वापस 0;

	spin_lock_irqsave(&devfreq->lock, irqflags);

	lima_devfreq_reset(devfreq);

	spin_unlock_irqrestore(&devfreq->lock, irqflags);

	वापस devfreq_resume_device(devfreq->devfreq);
पूर्ण

पूर्णांक lima_devfreq_suspend(काष्ठा lima_devfreq *devfreq)
अणु
	अगर (!devfreq->devfreq)
		वापस 0;

	वापस devfreq_suspend_device(devfreq->devfreq);
पूर्ण
