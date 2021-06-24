<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2019 Collabora ltd. */

#समावेश <linux/clk.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/devfreq_cooling.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>

#समावेश "panfrost_device.h"
#समावेश "panfrost_devfreq.h"

अटल व्योम panfrost_devfreq_update_utilization(काष्ठा panfrost_devfreq *pfdevfreq)
अणु
	kसमय_प्रकार now, last;

	now = kसमय_get();
	last = pfdevfreq->समय_last_update;

	अगर (pfdevfreq->busy_count > 0)
		pfdevfreq->busy_समय += kसमय_sub(now, last);
	अन्यथा
		pfdevfreq->idle_समय += kसमय_sub(now, last);

	pfdevfreq->समय_last_update = now;
पूर्ण

अटल पूर्णांक panfrost_devfreq_target(काष्ठा device *dev, अचिन्हित दीर्घ *freq,
				   u32 flags)
अणु
	काष्ठा dev_pm_opp *opp;

	opp = devfreq_recommended_opp(dev, freq, flags);
	अगर (IS_ERR(opp))
		वापस PTR_ERR(opp);
	dev_pm_opp_put(opp);

	वापस dev_pm_opp_set_rate(dev, *freq);
पूर्ण

अटल व्योम panfrost_devfreq_reset(काष्ठा panfrost_devfreq *pfdevfreq)
अणु
	pfdevfreq->busy_समय = 0;
	pfdevfreq->idle_समय = 0;
	pfdevfreq->समय_last_update = kसमय_get();
पूर्ण

अटल पूर्णांक panfrost_devfreq_get_dev_status(काष्ठा device *dev,
					   काष्ठा devfreq_dev_status *status)
अणु
	काष्ठा panfrost_device *pfdev = dev_get_drvdata(dev);
	काष्ठा panfrost_devfreq *pfdevfreq = &pfdev->pfdevfreq;
	अचिन्हित दीर्घ irqflags;

	status->current_frequency = clk_get_rate(pfdev->घड़ी);

	spin_lock_irqsave(&pfdevfreq->lock, irqflags);

	panfrost_devfreq_update_utilization(pfdevfreq);

	status->total_समय = kसमय_प्रकारo_ns(kसमय_add(pfdevfreq->busy_समय,
						   pfdevfreq->idle_समय));

	status->busy_समय = kसमय_प्रकारo_ns(pfdevfreq->busy_समय);

	panfrost_devfreq_reset(pfdevfreq);

	spin_unlock_irqrestore(&pfdevfreq->lock, irqflags);

	dev_dbg(pfdev->dev, "busy %lu total %lu %lu %% freq %lu MHz\n",
		status->busy_समय, status->total_समय,
		status->busy_समय / (status->total_समय / 100),
		status->current_frequency / 1000 / 1000);

	वापस 0;
पूर्ण

अटल काष्ठा devfreq_dev_profile panfrost_devfreq_profile = अणु
	.समयr = DEVFREQ_TIMER_DELAYED,
	.polling_ms = 50, /* ~3 frames */
	.target = panfrost_devfreq_target,
	.get_dev_status = panfrost_devfreq_get_dev_status,
पूर्ण;

पूर्णांक panfrost_devfreq_init(काष्ठा panfrost_device *pfdev)
अणु
	पूर्णांक ret;
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ cur_freq;
	काष्ठा device *dev = &pfdev->pdev->dev;
	काष्ठा devfreq *devfreq;
	काष्ठा thermal_cooling_device *cooling;
	काष्ठा panfrost_devfreq *pfdevfreq = &pfdev->pfdevfreq;

	ret = devm_pm_opp_set_regulators(dev, pfdev->comp->supply_names,
					 pfdev->comp->num_supplies);
	अगर (ret) अणु
		/* Continue अगर the optional regulator is missing */
		अगर (ret != -ENODEV) अणु
			DRM_DEV_ERROR(dev, "Couldn't set OPP regulators\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_pm_opp_of_add_table(dev);
	अगर (ret) अणु
		/* Optional, जारी without devfreq */
		अगर (ret == -ENODEV)
			ret = 0;
		वापस ret;
	पूर्ण
	pfdevfreq->opp_of_table_added = true;

	spin_lock_init(&pfdevfreq->lock);

	panfrost_devfreq_reset(pfdevfreq);

	cur_freq = clk_get_rate(pfdev->घड़ी);

	opp = devfreq_recommended_opp(dev, &cur_freq, 0);
	अगर (IS_ERR(opp))
		वापस PTR_ERR(opp);

	panfrost_devfreq_profile.initial_freq = cur_freq;
	dev_pm_opp_put(opp);

	/*
	 * Setup शेष thresholds क्रम the simple_ondemand governor.
	 * The values are chosen based on experiments.
	 */
	pfdevfreq->gov_data.upthreshold = 45;
	pfdevfreq->gov_data.करोwndअगरferential = 5;

	devfreq = devm_devfreq_add_device(dev, &panfrost_devfreq_profile,
					  DEVFREQ_GOV_SIMPLE_ONDEMAND,
					  &pfdevfreq->gov_data);
	अगर (IS_ERR(devfreq)) अणु
		DRM_DEV_ERROR(dev, "Couldn't initialize GPU devfreq\n");
		वापस PTR_ERR(devfreq);
	पूर्ण
	pfdevfreq->devfreq = devfreq;

	cooling = devfreq_cooling_em_रेजिस्टर(devfreq, शून्य);
	अगर (IS_ERR(cooling))
		DRM_DEV_INFO(dev, "Failed to register cooling device\n");
	अन्यथा
		pfdevfreq->cooling = cooling;

	वापस 0;
पूर्ण

व्योम panfrost_devfreq_fini(काष्ठा panfrost_device *pfdev)
अणु
	काष्ठा panfrost_devfreq *pfdevfreq = &pfdev->pfdevfreq;

	अगर (pfdevfreq->cooling) अणु
		devfreq_cooling_unरेजिस्टर(pfdevfreq->cooling);
		pfdevfreq->cooling = शून्य;
	पूर्ण
पूर्ण

व्योम panfrost_devfreq_resume(काष्ठा panfrost_device *pfdev)
अणु
	काष्ठा panfrost_devfreq *pfdevfreq = &pfdev->pfdevfreq;

	अगर (!pfdevfreq->devfreq)
		वापस;

	panfrost_devfreq_reset(pfdevfreq);

	devfreq_resume_device(pfdevfreq->devfreq);
पूर्ण

व्योम panfrost_devfreq_suspend(काष्ठा panfrost_device *pfdev)
अणु
	काष्ठा panfrost_devfreq *pfdevfreq = &pfdev->pfdevfreq;

	अगर (!pfdevfreq->devfreq)
		वापस;

	devfreq_suspend_device(pfdevfreq->devfreq);
पूर्ण

व्योम panfrost_devfreq_record_busy(काष्ठा panfrost_devfreq *pfdevfreq)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (!pfdevfreq->devfreq)
		वापस;

	spin_lock_irqsave(&pfdevfreq->lock, irqflags);

	panfrost_devfreq_update_utilization(pfdevfreq);

	pfdevfreq->busy_count++;

	spin_unlock_irqrestore(&pfdevfreq->lock, irqflags);
पूर्ण

व्योम panfrost_devfreq_record_idle(काष्ठा panfrost_devfreq *pfdevfreq)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (!pfdevfreq->devfreq)
		वापस;

	spin_lock_irqsave(&pfdevfreq->lock, irqflags);

	panfrost_devfreq_update_utilization(pfdevfreq);

	WARN_ON(--pfdevfreq->busy_count < 0);

	spin_unlock_irqrestore(&pfdevfreq->lock, irqflags);
पूर्ण
