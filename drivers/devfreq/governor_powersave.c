<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/devfreq/governor_घातersave.c
 *
 *  Copyright (C) 2011 Samsung Electronics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#समावेश <linux/devfreq.h>
#समावेश <linux/module.h>
#समावेश "governor.h"

अटल पूर्णांक devfreq_घातersave_func(काष्ठा devfreq *df,
				  अचिन्हित दीर्घ *freq)
अणु
	/*
	 * target callback should be able to get उच्चमानing value as
	 * said in devfreq.h
	 */
	*freq = DEVFREQ_MIN_FREQ;
	वापस 0;
पूर्ण

अटल पूर्णांक devfreq_घातersave_handler(काष्ठा devfreq *devfreq,
				अचिन्हित पूर्णांक event, व्योम *data)
अणु
	पूर्णांक ret = 0;

	अगर (event == DEVFREQ_GOV_START) अणु
		mutex_lock(&devfreq->lock);
		ret = update_devfreq(devfreq);
		mutex_unlock(&devfreq->lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा devfreq_governor devfreq_घातersave = अणु
	.name = DEVFREQ_GOV_POWERSAVE,
	.get_target_freq = devfreq_घातersave_func,
	.event_handler = devfreq_घातersave_handler,
पूर्ण;

अटल पूर्णांक __init devfreq_घातersave_init(व्योम)
अणु
	वापस devfreq_add_governor(&devfreq_घातersave);
पूर्ण
subsys_initcall(devfreq_घातersave_init);

अटल व्योम __निकास devfreq_घातersave_निकास(व्योम)
अणु
	पूर्णांक ret;

	ret = devfreq_हटाओ_governor(&devfreq_घातersave);
	अगर (ret)
		pr_err("%s: failed remove governor %d\n", __func__, ret);

	वापस;
पूर्ण
module_निकास(devfreq_घातersave_निकास);
MODULE_LICENSE("GPL");
