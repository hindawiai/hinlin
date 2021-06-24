<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/devfreq/governor_simpleondemand.c
 *
 *  Copyright (C) 2011 Samsung Electronics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/math64.h>
#समावेश "governor.h"

/* Default स्थिरants क्रम DevFreq-Simple-Ondemand (DFSO) */
#घोषणा DFSO_UPTHRESHOLD	(90)
#घोषणा DFSO_DOWNDIFFERENCTIAL	(5)
अटल पूर्णांक devfreq_simple_ondemand_func(काष्ठा devfreq *df,
					अचिन्हित दीर्घ *freq)
अणु
	पूर्णांक err;
	काष्ठा devfreq_dev_status *stat;
	अचिन्हित दीर्घ दीर्घ a, b;
	अचिन्हित पूर्णांक dfso_upthreshold = DFSO_UPTHRESHOLD;
	अचिन्हित पूर्णांक dfso_करोwndअगरferential = DFSO_DOWNDIFFERENCTIAL;
	काष्ठा devfreq_simple_ondemand_data *data = df->data;

	err = devfreq_update_stats(df);
	अगर (err)
		वापस err;

	stat = &df->last_status;

	अगर (data) अणु
		अगर (data->upthreshold)
			dfso_upthreshold = data->upthreshold;
		अगर (data->करोwndअगरferential)
			dfso_करोwndअगरferential = data->करोwndअगरferential;
	पूर्ण
	अगर (dfso_upthreshold > 100 ||
	    dfso_upthreshold < dfso_करोwndअगरferential)
		वापस -EINVAL;

	/* Assume MAX अगर it is going to be भागided by zero */
	अगर (stat->total_समय == 0) अणु
		*freq = DEVFREQ_MAX_FREQ;
		वापस 0;
	पूर्ण

	/* Prevent overflow */
	अगर (stat->busy_समय >= (1 << 24) || stat->total_समय >= (1 << 24)) अणु
		stat->busy_समय >>= 7;
		stat->total_समय >>= 7;
	पूर्ण

	/* Set MAX अगर it's busy enough */
	अगर (stat->busy_समय * 100 >
	    stat->total_समय * dfso_upthreshold) अणु
		*freq = DEVFREQ_MAX_FREQ;
		वापस 0;
	पूर्ण

	/* Set MAX अगर we करो not know the initial frequency */
	अगर (stat->current_frequency == 0) अणु
		*freq = DEVFREQ_MAX_FREQ;
		वापस 0;
	पूर्ण

	/* Keep the current frequency */
	अगर (stat->busy_समय * 100 >
	    stat->total_समय * (dfso_upthreshold - dfso_करोwndअगरferential)) अणु
		*freq = stat->current_frequency;
		वापस 0;
	पूर्ण

	/* Set the desired frequency based on the load */
	a = stat->busy_समय;
	a *= stat->current_frequency;
	b = भाग_u64(a, stat->total_समय);
	b *= 100;
	b = भाग_u64(b, (dfso_upthreshold - dfso_करोwndअगरferential / 2));
	*freq = (अचिन्हित दीर्घ) b;

	वापस 0;
पूर्ण

अटल पूर्णांक devfreq_simple_ondemand_handler(काष्ठा devfreq *devfreq,
				अचिन्हित पूर्णांक event, व्योम *data)
अणु
	चयन (event) अणु
	हाल DEVFREQ_GOV_START:
		devfreq_monitor_start(devfreq);
		अवरोध;

	हाल DEVFREQ_GOV_STOP:
		devfreq_monitor_stop(devfreq);
		अवरोध;

	हाल DEVFREQ_GOV_UPDATE_INTERVAL:
		devfreq_update_पूर्णांकerval(devfreq, (अचिन्हित पूर्णांक *)data);
		अवरोध;

	हाल DEVFREQ_GOV_SUSPEND:
		devfreq_monitor_suspend(devfreq);
		अवरोध;

	हाल DEVFREQ_GOV_RESUME:
		devfreq_monitor_resume(devfreq);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा devfreq_governor devfreq_simple_ondemand = अणु
	.name = DEVFREQ_GOV_SIMPLE_ONDEMAND,
	.attrs = DEVFREQ_GOV_ATTR_POLLING_INTERVAL
		| DEVFREQ_GOV_ATTR_TIMER,
	.get_target_freq = devfreq_simple_ondemand_func,
	.event_handler = devfreq_simple_ondemand_handler,
पूर्ण;

अटल पूर्णांक __init devfreq_simple_ondemand_init(व्योम)
अणु
	वापस devfreq_add_governor(&devfreq_simple_ondemand);
पूर्ण
subsys_initcall(devfreq_simple_ondemand_init);

अटल व्योम __निकास devfreq_simple_ondemand_निकास(व्योम)
अणु
	पूर्णांक ret;

	ret = devfreq_हटाओ_governor(&devfreq_simple_ondemand);
	अगर (ret)
		pr_err("%s: failed remove governor %d\n", __func__, ret);

	वापस;
पूर्ण
module_निकास(devfreq_simple_ondemand_निकास);
MODULE_LICENSE("GPL");
