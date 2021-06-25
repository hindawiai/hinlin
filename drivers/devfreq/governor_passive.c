<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/devfreq/governor_passive.c
 *
 * Copyright (C) 2016 Samsung Electronics
 * Author: Chanwoo Choi <cw00.choi@samsung.com>
 * Author: MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/devfreq.h>
#समावेश "governor.h"

अटल पूर्णांक devfreq_passive_get_target_freq(काष्ठा devfreq *devfreq,
					अचिन्हित दीर्घ *freq)
अणु
	काष्ठा devfreq_passive_data *p_data
			= (काष्ठा devfreq_passive_data *)devfreq->data;
	काष्ठा devfreq *parent_devfreq = (काष्ठा devfreq *)p_data->parent;
	अचिन्हित दीर्घ child_freq = अच_दीर्घ_उच्च;
	काष्ठा dev_pm_opp *opp, *p_opp;
	पूर्णांक i, count;

	/*
	 * If the devfreq device with passive governor has the specअगरic method
	 * to determine the next frequency, should use the get_target_freq()
	 * of काष्ठा devfreq_passive_data.
	 */
	अगर (p_data->get_target_freq)
		वापस p_data->get_target_freq(devfreq, freq);

	/*
	 * If the parent and passive devfreq device uses the OPP table,
	 * get the next frequency by using the OPP table.
	 */

	/*
	 * - parent devfreq device uses the governors except क्रम passive.
	 * - passive devfreq device uses the passive governor.
	 *
	 * Each devfreq has the OPP table. After deciding the new frequency
	 * from the governor of parent devfreq device, the passive governor
	 * need to get the index of new frequency on OPP table of parent
	 * device. And then the index is used क्रम getting the suitable
	 * new frequency क्रम passive devfreq device.
	 */
	अगर (!devfreq->profile || !devfreq->profile->freq_table
		|| devfreq->profile->max_state <= 0)
		वापस -EINVAL;

	/*
	 * The passive governor have to get the correct frequency from OPP
	 * list of parent device. Because in this हाल, *freq is temporary
	 * value which is decided by ondemand governor.
	 */
	अगर (devfreq->opp_table && parent_devfreq->opp_table) अणु
		p_opp = devfreq_recommended_opp(parent_devfreq->dev.parent,
						freq, 0);
		अगर (IS_ERR(p_opp))
			वापस PTR_ERR(p_opp);

		opp = dev_pm_opp_xlate_required_opp(parent_devfreq->opp_table,
						    devfreq->opp_table, p_opp);
		dev_pm_opp_put(p_opp);

		अगर (IS_ERR(opp))
			वापस PTR_ERR(opp);

		*freq = dev_pm_opp_get_freq(opp);
		dev_pm_opp_put(opp);

		वापस 0;
	पूर्ण

	/*
	 * Get the OPP table's index of decided frequency by governor
	 * of parent device.
	 */
	क्रम (i = 0; i < parent_devfreq->profile->max_state; i++)
		अगर (parent_devfreq->profile->freq_table[i] == *freq)
			अवरोध;

	अगर (i == parent_devfreq->profile->max_state)
		वापस -EINVAL;

	/* Get the suitable frequency by using index of parent device. */
	अगर (i < devfreq->profile->max_state) अणु
		child_freq = devfreq->profile->freq_table[i];
	पूर्ण अन्यथा अणु
		count = devfreq->profile->max_state;
		child_freq = devfreq->profile->freq_table[count - 1];
	पूर्ण

	/* Return the suitable frequency क्रम passive device. */
	*freq = child_freq;

	वापस 0;
पूर्ण

अटल पूर्णांक devfreq_passive_notअगरier_call(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा devfreq_passive_data *data
			= container_of(nb, काष्ठा devfreq_passive_data, nb);
	काष्ठा devfreq *devfreq = (काष्ठा devfreq *)data->this;
	काष्ठा devfreq *parent = (काष्ठा devfreq *)data->parent;
	काष्ठा devfreq_freqs *freqs = (काष्ठा devfreq_freqs *)ptr;
	अचिन्हित दीर्घ freq = freqs->new;
	पूर्णांक ret = 0;

	mutex_lock_nested(&devfreq->lock, SINGLE_DEPTH_NESTING);
	चयन (event) अणु
	हाल DEVFREQ_PRECHANGE:
		अगर (parent->previous_freq > freq)
			ret = devfreq_update_target(devfreq, freq);

		अवरोध;
	हाल DEVFREQ_POSTCHANGE:
		अगर (parent->previous_freq < freq)
			ret = devfreq_update_target(devfreq, freq);
		अवरोध;
	पूर्ण
	mutex_unlock(&devfreq->lock);

	अगर (ret < 0)
		dev_warn(&devfreq->dev,
			"failed to update devfreq using passive governor\n");

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक devfreq_passive_event_handler(काष्ठा devfreq *devfreq,
				अचिन्हित पूर्णांक event, व्योम *data)
अणु
	काष्ठा devfreq_passive_data *p_data
			= (काष्ठा devfreq_passive_data *)devfreq->data;
	काष्ठा devfreq *parent = (काष्ठा devfreq *)p_data->parent;
	काष्ठा notअगरier_block *nb = &p_data->nb;
	पूर्णांक ret = 0;

	अगर (!parent)
		वापस -EPROBE_DEFER;

	चयन (event) अणु
	हाल DEVFREQ_GOV_START:
		अगर (!p_data->this)
			p_data->this = devfreq;

		nb->notअगरier_call = devfreq_passive_notअगरier_call;
		ret = devfreq_रेजिस्टर_notअगरier(parent, nb,
					DEVFREQ_TRANSITION_NOTIFIER);
		अवरोध;
	हाल DEVFREQ_GOV_STOP:
		WARN_ON(devfreq_unरेजिस्टर_notअगरier(parent, nb,
					DEVFREQ_TRANSITION_NOTIFIER));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा devfreq_governor devfreq_passive = अणु
	.name = DEVFREQ_GOV_PASSIVE,
	.flags = DEVFREQ_GOV_FLAG_IMMUTABLE,
	.get_target_freq = devfreq_passive_get_target_freq,
	.event_handler = devfreq_passive_event_handler,
पूर्ण;

अटल पूर्णांक __init devfreq_passive_init(व्योम)
अणु
	वापस devfreq_add_governor(&devfreq_passive);
पूर्ण
subsys_initcall(devfreq_passive_init);

अटल व्योम __निकास devfreq_passive_निकास(व्योम)
अणु
	पूर्णांक ret;

	ret = devfreq_हटाओ_governor(&devfreq_passive);
	अगर (ret)
		pr_err("%s: failed remove governor %d\n", __func__, ret);
पूर्ण
module_निकास(devfreq_passive_निकास);

MODULE_AUTHOR("Chanwoo Choi <cw00.choi@samsung.com>");
MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_DESCRIPTION("DEVFREQ Passive governor");
MODULE_LICENSE("GPL v2");
