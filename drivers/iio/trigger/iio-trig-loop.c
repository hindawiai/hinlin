<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Jonathan Cameron <jic23@kernel.org>
 *
 * Based on a mashup of the hrसमयr trigger and continuous sampling proposal of
 * Gregor Boirie <gregor.boirie@parrot.com>
 *
 * Note this is still rather experimental and may eat babies.
 *
 * Toकरो
 * * Protect against connection of devices that 'need' the top half
 *   handler.
 * * Work out how to run top half handlers in this context अगर it is
 *   safe to करो so (बारtamp grabbing क्रम example)
 *
 * Tested against a max1363. Used about 33% cpu क्रम the thपढ़ो and 20%
 * क्रम generic_buffer piping to /dev/null. Watermark set at 64 on a 128
 * element kfअगरo buffer.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/sw_trigger.h>

काष्ठा iio_loop_info अणु
	काष्ठा iio_sw_trigger swt;
	काष्ठा task_काष्ठा *task;
पूर्ण;

अटल स्थिर काष्ठा config_item_type iio_loop_type = अणु
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक iio_loop_thपढ़ो(व्योम *data)
अणु
	काष्ठा iio_trigger *trig = data;

	set_मुक्तzable();

	करो अणु
		iio_trigger_poll_chained(trig);
	पूर्ण जबतक (likely(!kthपढ़ो_मुक्तzable_should_stop(शून्य)));

	वापस 0;
पूर्ण

अटल पूर्णांक iio_loop_trigger_set_state(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_loop_info *loop_trig = iio_trigger_get_drvdata(trig);

	अगर (state) अणु
		loop_trig->task = kthपढ़ो_run(iio_loop_thपढ़ो,
					      trig, trig->name);
		अगर (IS_ERR(loop_trig->task)) अणु
			dev_err(&trig->dev,
				"failed to create trigger loop thread\n");
			वापस PTR_ERR(loop_trig->task);
		पूर्ण
	पूर्ण अन्यथा अणु
		kthपढ़ो_stop(loop_trig->task);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops iio_loop_trigger_ops = अणु
	.set_trigger_state = iio_loop_trigger_set_state,
पूर्ण;

अटल काष्ठा iio_sw_trigger *iio_trig_loop_probe(स्थिर अक्षर *name)
अणु
	काष्ठा iio_loop_info *trig_info;
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
	trig_info->swt.trigger->ops = &iio_loop_trigger_ops;

	ret = iio_trigger_रेजिस्टर(trig_info->swt.trigger);
	अगर (ret)
		जाओ err_मुक्त_trigger;

	iio_swt_group_init_type_name(&trig_info->swt, name, &iio_loop_type);

	वापस &trig_info->swt;

err_मुक्त_trigger:
	iio_trigger_मुक्त(trig_info->swt.trigger);
err_मुक्त_trig_info:
	kमुक्त(trig_info);

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक iio_trig_loop_हटाओ(काष्ठा iio_sw_trigger *swt)
अणु
	काष्ठा iio_loop_info *trig_info;

	trig_info = iio_trigger_get_drvdata(swt->trigger);

	iio_trigger_unरेजिस्टर(swt->trigger);
	iio_trigger_मुक्त(swt->trigger);
	kमुक्त(trig_info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_sw_trigger_ops iio_trig_loop_ops = अणु
	.probe = iio_trig_loop_probe,
	.हटाओ = iio_trig_loop_हटाओ,
पूर्ण;

अटल काष्ठा iio_sw_trigger_type iio_trig_loop = अणु
	.name = "loop",
	.owner = THIS_MODULE,
	.ops = &iio_trig_loop_ops,
पूर्ण;

module_iio_sw_trigger_driver(iio_trig_loop);

MODULE_AUTHOR("Jonathan Cameron <jic23@kernel.org>");
MODULE_DESCRIPTION("Loop based trigger for the iio subsystem");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:iio-trig-loop");
