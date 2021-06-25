<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Apple Onboard Audio pmf GPIOs
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <linux/slab.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/pmac_pfunc.h>
#समावेश "../aoa.h"

#घोषणा PMF_GPIO(name, bit)					\
अटल व्योम pmf_gpio_set_##name(काष्ठा gpio_runसमय *rt, पूर्णांक on)\
अणु								\
	काष्ठा pmf_args args = अणु .count = 1, .u[0].v = !on पूर्ण;	\
	पूर्णांक rc;							\
							\
	अगर (unlikely(!rt)) वापस;				\
	rc = pmf_call_function(rt->node, #name "-mute", &args);	\
	अगर (rc && rc != -ENODEV)				\
		prपूर्णांकk(KERN_WARNING "pmf_gpio_set_" #name	\
		" failed, rc: %d\n", rc);			\
	rt->implementation_निजी &= ~(1<<bit);		\
	rt->implementation_निजी |= (!!on << bit);		\
पूर्ण								\
अटल पूर्णांक pmf_gpio_get_##name(काष्ठा gpio_runसमय *rt)		\
अणु								\
	अगर (unlikely(!rt)) वापस 0;				\
	वापस (rt->implementation_निजी>>bit)&1;		\
पूर्ण

PMF_GPIO(headphone, 0);
PMF_GPIO(amp, 1);
PMF_GPIO(lineout, 2);

अटल व्योम pmf_gpio_set_hw_reset(काष्ठा gpio_runसमय *rt, पूर्णांक on)
अणु
	काष्ठा pmf_args args = अणु .count = 1, .u[0].v = !!on पूर्ण;
	पूर्णांक rc;

	अगर (unlikely(!rt)) वापस;
	rc = pmf_call_function(rt->node, "hw-reset", &args);
	अगर (rc)
		prपूर्णांकk(KERN_WARNING "pmf_gpio_set_hw_reset"
		       " failed, rc: %d\n", rc);
पूर्ण

अटल व्योम pmf_gpio_all_amps_off(काष्ठा gpio_runसमय *rt)
अणु
	पूर्णांक saved;

	अगर (unlikely(!rt)) वापस;
	saved = rt->implementation_निजी;
	pmf_gpio_set_headphone(rt, 0);
	pmf_gpio_set_amp(rt, 0);
	pmf_gpio_set_lineout(rt, 0);
	rt->implementation_निजी = saved;
पूर्ण

अटल व्योम pmf_gpio_all_amps_restore(काष्ठा gpio_runसमय *rt)
अणु
	पूर्णांक s;

	अगर (unlikely(!rt)) वापस;
	s = rt->implementation_निजी;
	pmf_gpio_set_headphone(rt, (s>>0)&1);
	pmf_gpio_set_amp(rt, (s>>1)&1);
	pmf_gpio_set_lineout(rt, (s>>2)&1);
पूर्ण

अटल व्योम pmf_handle_notअगरy(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gpio_notअगरication *notअगर =
		container_of(work, काष्ठा gpio_notअगरication, work.work);

	mutex_lock(&notअगर->mutex);
	अगर (notअगर->notअगरy)
		notअगर->notअगरy(notअगर->data);
	mutex_unlock(&notअगर->mutex);
पूर्ण

अटल व्योम pmf_gpio_init(काष्ठा gpio_runसमय *rt)
अणु
	pmf_gpio_all_amps_off(rt);
	rt->implementation_निजी = 0;
	INIT_DELAYED_WORK(&rt->headphone_notअगरy.work, pmf_handle_notअगरy);
	INIT_DELAYED_WORK(&rt->line_in_notअगरy.work, pmf_handle_notअगरy);
	INIT_DELAYED_WORK(&rt->line_out_notअगरy.work, pmf_handle_notअगरy);
	mutex_init(&rt->headphone_notअगरy.mutex);
	mutex_init(&rt->line_in_notअगरy.mutex);
	mutex_init(&rt->line_out_notअगरy.mutex);
पूर्ण

अटल व्योम pmf_gpio_निकास(काष्ठा gpio_runसमय *rt)
अणु
	pmf_gpio_all_amps_off(rt);
	rt->implementation_निजी = 0;

	अगर (rt->headphone_notअगरy.gpio_निजी)
		pmf_unरेजिस्टर_irq_client(rt->headphone_notअगरy.gpio_निजी);
	अगर (rt->line_in_notअगरy.gpio_निजी)
		pmf_unरेजिस्टर_irq_client(rt->line_in_notअगरy.gpio_निजी);
	अगर (rt->line_out_notअगरy.gpio_निजी)
		pmf_unरेजिस्टर_irq_client(rt->line_out_notअगरy.gpio_निजी);

	/* make sure no work is pending beक्रमe मुक्तing
	 * all things */
	cancel_delayed_work_sync(&rt->headphone_notअगरy.work);
	cancel_delayed_work_sync(&rt->line_in_notअगरy.work);
	cancel_delayed_work_sync(&rt->line_out_notअगरy.work);

	mutex_destroy(&rt->headphone_notअगरy.mutex);
	mutex_destroy(&rt->line_in_notअगरy.mutex);
	mutex_destroy(&rt->line_out_notअगरy.mutex);

	kमुक्त(rt->headphone_notअगरy.gpio_निजी);
	kमुक्त(rt->line_in_notअगरy.gpio_निजी);
	kमुक्त(rt->line_out_notअगरy.gpio_निजी);
पूर्ण

अटल व्योम pmf_handle_notअगरy_irq(व्योम *data)
अणु
	काष्ठा gpio_notअगरication *notअगर = data;

	schedule_delayed_work(&notअगर->work, 0);
पूर्ण

अटल पूर्णांक pmf_set_notअगरy(काष्ठा gpio_runसमय *rt,
			  क्रमागत notअगरy_type type,
			  notअगरy_func_t notअगरy,
			  व्योम *data)
अणु
	काष्ठा gpio_notअगरication *notअगर;
	notअगरy_func_t old;
	काष्ठा pmf_irq_client *irq_client;
	अक्षर *name;
	पूर्णांक err = -EBUSY;

	चयन (type) अणु
	हाल AOA_NOTIFY_HEADPHONE:
		notअगर = &rt->headphone_notअगरy;
		name = "headphone-detect";
		अवरोध;
	हाल AOA_NOTIFY_LINE_IN:
		notअगर = &rt->line_in_notअगरy;
		name = "linein-detect";
		अवरोध;
	हाल AOA_NOTIFY_LINE_OUT:
		notअगर = &rt->line_out_notअगरy;
		name = "lineout-detect";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&notअगर->mutex);

	old = notअगर->notअगरy;

	अगर (!old && !notअगरy) अणु
		err = 0;
		जाओ out_unlock;
	पूर्ण

	अगर (old && notअगरy) अणु
		अगर (old == notअगरy && notअगर->data == data)
			err = 0;
		जाओ out_unlock;
	पूर्ण

	अगर (old && !notअगरy) अणु
		irq_client = notअगर->gpio_निजी;
		pmf_unरेजिस्टर_irq_client(irq_client);
		kमुक्त(irq_client);
		notअगर->gpio_निजी = शून्य;
	पूर्ण
	अगर (!old && notअगरy) अणु
		irq_client = kzalloc(माप(काष्ठा pmf_irq_client),
				     GFP_KERNEL);
		अगर (!irq_client) अणु
			err = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
		irq_client->data = notअगर;
		irq_client->handler = pmf_handle_notअगरy_irq;
		irq_client->owner = THIS_MODULE;
		err = pmf_रेजिस्टर_irq_client(rt->node,
					      name,
					      irq_client);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "snd-aoa: gpio layer failed to"
					" register %s irq (%d)\n", name, err);
			kमुक्त(irq_client);
			जाओ out_unlock;
		पूर्ण
		notअगर->gpio_निजी = irq_client;
	पूर्ण
	notअगर->notअगरy = notअगरy;
	notअगर->data = data;

	err = 0;
 out_unlock:
	mutex_unlock(&notअगर->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक pmf_get_detect(काष्ठा gpio_runसमय *rt,
			  क्रमागत notअगरy_type type)
अणु
	अक्षर *name;
	पूर्णांक err = -EBUSY, ret;
	काष्ठा pmf_args args = अणु .count = 1, .u[0].p = &ret पूर्ण;

	चयन (type) अणु
	हाल AOA_NOTIFY_HEADPHONE:
		name = "headphone-detect";
		अवरोध;
	हाल AOA_NOTIFY_LINE_IN:
		name = "linein-detect";
		अवरोध;
	हाल AOA_NOTIFY_LINE_OUT:
		name = "lineout-detect";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = pmf_call_function(rt->node, name, &args);
	अगर (err)
		वापस err;
	वापस ret;
पूर्ण

अटल काष्ठा gpio_methods methods = अणु
	.init			= pmf_gpio_init,
	.निकास			= pmf_gpio_निकास,
	.all_amps_off		= pmf_gpio_all_amps_off,
	.all_amps_restore	= pmf_gpio_all_amps_restore,
	.set_headphone		= pmf_gpio_set_headphone,
	.set_speakers		= pmf_gpio_set_amp,
	.set_lineout		= pmf_gpio_set_lineout,
	.set_hw_reset		= pmf_gpio_set_hw_reset,
	.get_headphone		= pmf_gpio_get_headphone,
	.get_speakers		= pmf_gpio_get_amp,
	.get_lineout		= pmf_gpio_get_lineout,
	.set_notअगरy		= pmf_set_notअगरy,
	.get_detect		= pmf_get_detect,
पूर्ण;

काष्ठा gpio_methods *pmf_gpio_methods = &methods;
EXPORT_SYMBOL_GPL(pmf_gpio_methods);
