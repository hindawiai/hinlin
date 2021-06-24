<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * The input core
 *
 * Copyright (c) 1999-2002 Vojtech Pavlik
 */


#घोषणा pr_fmt(fmt) KBUILD_BASENAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/idr.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/major.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/poll.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rcupdate.h>
#समावेश "input-compat.h"
#समावेश "input-poller.h"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@suse.cz>");
MODULE_DESCRIPTION("Input core");
MODULE_LICENSE("GPL");

#घोषणा INPUT_MAX_CHAR_DEVICES		1024
#घोषणा INPUT_FIRST_DYNAMIC_DEV		256
अटल DEFINE_IDA(input_ida);

अटल LIST_HEAD(input_dev_list);
अटल LIST_HEAD(input_handler_list);

/*
 * input_mutex protects access to both input_dev_list and input_handler_list.
 * This also causes input_[un]रेजिस्टर_device and input_[un]रेजिस्टर_handler
 * be mutually exclusive which simplअगरies locking in drivers implementing
 * input handlers.
 */
अटल DEFINE_MUTEX(input_mutex);

अटल स्थिर काष्ठा input_value input_value_sync = अणु EV_SYN, SYN_REPORT, 1 पूर्ण;

अटल अंतरभूत पूर्णांक is_event_supported(अचिन्हित पूर्णांक code,
				     अचिन्हित दीर्घ *bm, अचिन्हित पूर्णांक max)
अणु
	वापस code <= max && test_bit(code, bm);
पूर्ण

अटल पूर्णांक input_defuzz_असल_event(पूर्णांक value, पूर्णांक old_val, पूर्णांक fuzz)
अणु
	अगर (fuzz) अणु
		अगर (value > old_val - fuzz / 2 && value < old_val + fuzz / 2)
			वापस old_val;

		अगर (value > old_val - fuzz && value < old_val + fuzz)
			वापस (old_val * 3 + value) / 4;

		अगर (value > old_val - fuzz * 2 && value < old_val + fuzz * 2)
			वापस (old_val + value) / 2;
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम input_start_स्वतःrepeat(काष्ठा input_dev *dev, पूर्णांक code)
अणु
	अगर (test_bit(EV_REP, dev->evbit) &&
	    dev->rep[REP_PERIOD] && dev->rep[REP_DELAY] &&
	    dev->समयr.function) अणु
		dev->repeat_key = code;
		mod_समयr(&dev->समयr,
			  jअगरfies + msecs_to_jअगरfies(dev->rep[REP_DELAY]));
	पूर्ण
पूर्ण

अटल व्योम input_stop_स्वतःrepeat(काष्ठा input_dev *dev)
अणु
	del_समयr(&dev->समयr);
पूर्ण

/*
 * Pass event first through all filters and then, अगर event has not been
 * filtered out, through all खोलो handles. This function is called with
 * dev->event_lock held and पूर्णांकerrupts disabled.
 */
अटल अचिन्हित पूर्णांक input_to_handler(काष्ठा input_handle *handle,
			काष्ठा input_value *vals, अचिन्हित पूर्णांक count)
अणु
	काष्ठा input_handler *handler = handle->handler;
	काष्ठा input_value *end = vals;
	काष्ठा input_value *v;

	अगर (handler->filter) अणु
		क्रम (v = vals; v != vals + count; v++) अणु
			अगर (handler->filter(handle, v->type, v->code, v->value))
				जारी;
			अगर (end != v)
				*end = *v;
			end++;
		पूर्ण
		count = end - vals;
	पूर्ण

	अगर (!count)
		वापस 0;

	अगर (handler->events)
		handler->events(handle, vals, count);
	अन्यथा अगर (handler->event)
		क्रम (v = vals; v != vals + count; v++)
			handler->event(handle, v->type, v->code, v->value);

	वापस count;
पूर्ण

/*
 * Pass values first through all filters and then, अगर event has not been
 * filtered out, through all खोलो handles. This function is called with
 * dev->event_lock held and पूर्णांकerrupts disabled.
 */
अटल व्योम input_pass_values(काष्ठा input_dev *dev,
			      काष्ठा input_value *vals, अचिन्हित पूर्णांक count)
अणु
	काष्ठा input_handle *handle;
	काष्ठा input_value *v;

	अगर (!count)
		वापस;

	rcu_पढ़ो_lock();

	handle = rcu_dereference(dev->grab);
	अगर (handle) अणु
		count = input_to_handler(handle, vals, count);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_rcu(handle, &dev->h_list, d_node)
			अगर (handle->खोलो) अणु
				count = input_to_handler(handle, vals, count);
				अगर (!count)
					अवरोध;
			पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	/* trigger स्वतः repeat क्रम key events */
	अगर (test_bit(EV_REP, dev->evbit) && test_bit(EV_KEY, dev->evbit)) अणु
		क्रम (v = vals; v != vals + count; v++) अणु
			अगर (v->type == EV_KEY && v->value != 2) अणु
				अगर (v->value)
					input_start_स्वतःrepeat(dev, v->code);
				अन्यथा
					input_stop_स्वतःrepeat(dev);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम input_pass_event(काष्ठा input_dev *dev,
			     अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा input_value vals[] = अणु अणु type, code, value पूर्ण पूर्ण;

	input_pass_values(dev, vals, ARRAY_SIZE(vals));
पूर्ण

/*
 * Generate software स्वतःrepeat event. Note that we take
 * dev->event_lock here to aव्योम racing with input_event
 * which may cause keys get "stuck".
 */
अटल व्योम input_repeat_key(काष्ठा समयr_list *t)
अणु
	काष्ठा input_dev *dev = from_समयr(dev, t, समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);

	अगर (test_bit(dev->repeat_key, dev->key) &&
	    is_event_supported(dev->repeat_key, dev->keybit, KEY_MAX)) अणु
		काष्ठा input_value vals[] =  अणु
			अणु EV_KEY, dev->repeat_key, 2 पूर्ण,
			input_value_sync
		पूर्ण;

		input_set_बारtamp(dev, kसमय_get());
		input_pass_values(dev, vals, ARRAY_SIZE(vals));

		अगर (dev->rep[REP_PERIOD])
			mod_समयr(&dev->समयr, jअगरfies +
					msecs_to_jअगरfies(dev->rep[REP_PERIOD]));
	पूर्ण

	spin_unlock_irqrestore(&dev->event_lock, flags);
पूर्ण

#घोषणा INPUT_IGNORE_EVENT	0
#घोषणा INPUT_PASS_TO_HANDLERS	1
#घोषणा INPUT_PASS_TO_DEVICE	2
#घोषणा INPUT_SLOT		4
#घोषणा INPUT_FLUSH		8
#घोषणा INPUT_PASS_TO_ALL	(INPUT_PASS_TO_HANDLERS | INPUT_PASS_TO_DEVICE)

अटल पूर्णांक input_handle_असल_event(काष्ठा input_dev *dev,
				  अचिन्हित पूर्णांक code, पूर्णांक *pval)
अणु
	काष्ठा input_mt *mt = dev->mt;
	bool is_mt_event;
	पूर्णांक *pold;

	अगर (code == ABS_MT_SLOT) अणु
		/*
		 * "Stage" the event; we'll flush it later, when we
		 * get actual touch data.
		 */
		अगर (mt && *pval >= 0 && *pval < mt->num_slots)
			mt->slot = *pval;

		वापस INPUT_IGNORE_EVENT;
	पूर्ण

	is_mt_event = input_is_mt_value(code);

	अगर (!is_mt_event) अणु
		pold = &dev->असलinfo[code].value;
	पूर्ण अन्यथा अगर (mt) अणु
		pold = &mt->slots[mt->slot].असल[code - ABS_MT_FIRST];
	पूर्ण अन्यथा अणु
		/*
		 * Bypass filtering क्रम multi-touch events when
		 * not employing slots.
		 */
		pold = शून्य;
	पूर्ण

	अगर (pold) अणु
		*pval = input_defuzz_असल_event(*pval, *pold,
						dev->असलinfo[code].fuzz);
		अगर (*pold == *pval)
			वापस INPUT_IGNORE_EVENT;

		*pold = *pval;
	पूर्ण

	/* Flush pending "slot" event */
	अगर (is_mt_event && mt && mt->slot != input_असल_get_val(dev, ABS_MT_SLOT)) अणु
		input_असल_set_val(dev, ABS_MT_SLOT, mt->slot);
		वापस INPUT_PASS_TO_HANDLERS | INPUT_SLOT;
	पूर्ण

	वापस INPUT_PASS_TO_HANDLERS;
पूर्ण

अटल पूर्णांक input_get_disposition(काष्ठा input_dev *dev,
			  अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक *pval)
अणु
	पूर्णांक disposition = INPUT_IGNORE_EVENT;
	पूर्णांक value = *pval;

	चयन (type) अणु

	हाल EV_SYN:
		चयन (code) अणु
		हाल SYN_CONFIG:
			disposition = INPUT_PASS_TO_ALL;
			अवरोध;

		हाल SYN_REPORT:
			disposition = INPUT_PASS_TO_HANDLERS | INPUT_FLUSH;
			अवरोध;
		हाल SYN_MT_REPORT:
			disposition = INPUT_PASS_TO_HANDLERS;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल EV_KEY:
		अगर (is_event_supported(code, dev->keybit, KEY_MAX)) अणु

			/* स्वतः-repeat bypasses state updates */
			अगर (value == 2) अणु
				disposition = INPUT_PASS_TO_HANDLERS;
				अवरोध;
			पूर्ण

			अगर (!!test_bit(code, dev->key) != !!value) अणु

				__change_bit(code, dev->key);
				disposition = INPUT_PASS_TO_HANDLERS;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल EV_SW:
		अगर (is_event_supported(code, dev->swbit, SW_MAX) &&
		    !!test_bit(code, dev->sw) != !!value) अणु

			__change_bit(code, dev->sw);
			disposition = INPUT_PASS_TO_HANDLERS;
		पूर्ण
		अवरोध;

	हाल EV_ABS:
		अगर (is_event_supported(code, dev->असलbit, ABS_MAX))
			disposition = input_handle_असल_event(dev, code, &value);

		अवरोध;

	हाल EV_REL:
		अगर (is_event_supported(code, dev->relbit, REL_MAX) && value)
			disposition = INPUT_PASS_TO_HANDLERS;

		अवरोध;

	हाल EV_MSC:
		अगर (is_event_supported(code, dev->mscbit, MSC_MAX))
			disposition = INPUT_PASS_TO_ALL;

		अवरोध;

	हाल EV_LED:
		अगर (is_event_supported(code, dev->ledbit, LED_MAX) &&
		    !!test_bit(code, dev->led) != !!value) अणु

			__change_bit(code, dev->led);
			disposition = INPUT_PASS_TO_ALL;
		पूर्ण
		अवरोध;

	हाल EV_SND:
		अगर (is_event_supported(code, dev->sndbit, SND_MAX)) अणु

			अगर (!!test_bit(code, dev->snd) != !!value)
				__change_bit(code, dev->snd);
			disposition = INPUT_PASS_TO_ALL;
		पूर्ण
		अवरोध;

	हाल EV_REP:
		अगर (code <= REP_MAX && value >= 0 && dev->rep[code] != value) अणु
			dev->rep[code] = value;
			disposition = INPUT_PASS_TO_ALL;
		पूर्ण
		अवरोध;

	हाल EV_FF:
		अगर (value >= 0)
			disposition = INPUT_PASS_TO_ALL;
		अवरोध;

	हाल EV_PWR:
		disposition = INPUT_PASS_TO_ALL;
		अवरोध;
	पूर्ण

	*pval = value;
	वापस disposition;
पूर्ण

अटल व्योम input_handle_event(काष्ठा input_dev *dev,
			       अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	पूर्णांक disposition;

	/* filter-out events from inhibited devices */
	अगर (dev->inhibited)
		वापस;

	disposition = input_get_disposition(dev, type, code, &value);
	अगर (disposition != INPUT_IGNORE_EVENT && type != EV_SYN)
		add_input_अक्रमomness(type, code, value);

	अगर ((disposition & INPUT_PASS_TO_DEVICE) && dev->event)
		dev->event(dev, type, code, value);

	अगर (!dev->vals)
		वापस;

	अगर (disposition & INPUT_PASS_TO_HANDLERS) अणु
		काष्ठा input_value *v;

		अगर (disposition & INPUT_SLOT) अणु
			v = &dev->vals[dev->num_vals++];
			v->type = EV_ABS;
			v->code = ABS_MT_SLOT;
			v->value = dev->mt->slot;
		पूर्ण

		v = &dev->vals[dev->num_vals++];
		v->type = type;
		v->code = code;
		v->value = value;
	पूर्ण

	अगर (disposition & INPUT_FLUSH) अणु
		अगर (dev->num_vals >= 2)
			input_pass_values(dev, dev->vals, dev->num_vals);
		dev->num_vals = 0;
		/*
		 * Reset the बारtamp on flush so we won't end up
		 * with a stale one. Note we only need to reset the
		 * monolithic one as we use its presence when deciding
		 * whether to generate a synthetic बारtamp.
		 */
		dev->बारtamp[INPUT_CLK_MONO] = kसमय_set(0, 0);
	पूर्ण अन्यथा अगर (dev->num_vals >= dev->max_vals - 2) अणु
		dev->vals[dev->num_vals++] = input_value_sync;
		input_pass_values(dev, dev->vals, dev->num_vals);
		dev->num_vals = 0;
	पूर्ण

पूर्ण

/**
 * input_event() - report new input event
 * @dev: device that generated the event
 * @type: type of the event
 * @code: event code
 * @value: value of the event
 *
 * This function should be used by drivers implementing various input
 * devices to report input events. See also input_inject_event().
 *
 * NOTE: input_event() may be safely used right after input device was
 * allocated with input_allocate_device(), even beक्रमe it is रेजिस्टरed
 * with input_रेजिस्टर_device(), but the event will not reach any of the
 * input handlers. Such early invocation of input_event() may be used
 * to 'seed' initial state of a चयन or initial position of असलolute
 * axis, etc.
 */
व्योम input_event(काष्ठा input_dev *dev,
		 अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;

	अगर (is_event_supported(type, dev->evbit, EV_MAX)) अणु

		spin_lock_irqsave(&dev->event_lock, flags);
		input_handle_event(dev, type, code, value);
		spin_unlock_irqrestore(&dev->event_lock, flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(input_event);

/**
 * input_inject_event() - send input event from input handler
 * @handle: input handle to send event through
 * @type: type of the event
 * @code: event code
 * @value: value of the event
 *
 * Similar to input_event() but will ignore event अगर device is
 * "grabbed" and handle injecting event is not the one that owns
 * the device.
 */
व्योम input_inject_event(काष्ठा input_handle *handle,
			अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा input_dev *dev = handle->dev;
	काष्ठा input_handle *grab;
	अचिन्हित दीर्घ flags;

	अगर (is_event_supported(type, dev->evbit, EV_MAX)) अणु
		spin_lock_irqsave(&dev->event_lock, flags);

		rcu_पढ़ो_lock();
		grab = rcu_dereference(dev->grab);
		अगर (!grab || grab == handle)
			input_handle_event(dev, type, code, value);
		rcu_पढ़ो_unlock();

		spin_unlock_irqrestore(&dev->event_lock, flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(input_inject_event);

/**
 * input_alloc_असलinfo - allocates array of input_असलinfo काष्ठाs
 * @dev: the input device emitting असलolute events
 *
 * If the असलinfo काष्ठा the caller asked क्रम is alपढ़ोy allocated, this
 * functions will not करो anything.
 */
व्योम input_alloc_असलinfo(काष्ठा input_dev *dev)
अणु
	अगर (dev->असलinfo)
		वापस;

	dev->असलinfo = kसुस्मृति(ABS_CNT, माप(*dev->असलinfo), GFP_KERNEL);
	अगर (!dev->असलinfo) अणु
		dev_err(dev->dev.parent ?: &dev->dev,
			"%s: unable to allocate memory\n", __func__);
		/*
		 * We will handle this allocation failure in
		 * input_रेजिस्टर_device() when we refuse to रेजिस्टर input
		 * device with ABS bits but without असलinfo.
		 */
	पूर्ण
पूर्ण
EXPORT_SYMBOL(input_alloc_असलinfo);

व्योम input_set_असल_params(काष्ठा input_dev *dev, अचिन्हित पूर्णांक axis,
			  पूर्णांक min, पूर्णांक max, पूर्णांक fuzz, पूर्णांक flat)
अणु
	काष्ठा input_असलinfo *असलinfo;

	input_alloc_असलinfo(dev);
	अगर (!dev->असलinfo)
		वापस;

	असलinfo = &dev->असलinfo[axis];
	असलinfo->minimum = min;
	असलinfo->maximum = max;
	असलinfo->fuzz = fuzz;
	असलinfo->flat = flat;

	__set_bit(EV_ABS, dev->evbit);
	__set_bit(axis, dev->असलbit);
पूर्ण
EXPORT_SYMBOL(input_set_असल_params);


/**
 * input_grab_device - grअसल device क्रम exclusive use
 * @handle: input handle that wants to own the device
 *
 * When a device is grabbed by an input handle all events generated by
 * the device are delivered only to this handle. Also events injected
 * by other input handles are ignored जबतक device is grabbed.
 */
पूर्णांक input_grab_device(काष्ठा input_handle *handle)
अणु
	काष्ठा input_dev *dev = handle->dev;
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&dev->mutex);
	अगर (retval)
		वापस retval;

	अगर (dev->grab) अणु
		retval = -EBUSY;
		जाओ out;
	पूर्ण

	rcu_assign_poपूर्णांकer(dev->grab, handle);

 out:
	mutex_unlock(&dev->mutex);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(input_grab_device);

अटल व्योम __input_release_device(काष्ठा input_handle *handle)
अणु
	काष्ठा input_dev *dev = handle->dev;
	काष्ठा input_handle *grabber;

	grabber = rcu_dereference_रक्षित(dev->grab,
					    lockdep_is_held(&dev->mutex));
	अगर (grabber == handle) अणु
		rcu_assign_poपूर्णांकer(dev->grab, शून्य);
		/* Make sure input_pass_event() notices that grab is gone */
		synchronize_rcu();

		list_क्रम_each_entry(handle, &dev->h_list, d_node)
			अगर (handle->खोलो && handle->handler->start)
				handle->handler->start(handle);
	पूर्ण
पूर्ण

/**
 * input_release_device - release previously grabbed device
 * @handle: input handle that owns the device
 *
 * Releases previously grabbed device so that other input handles can
 * start receiving input events. Upon release all handlers attached
 * to the device have their start() method called so they have a change
 * to synchronize device state with the rest of the प्रणाली.
 */
व्योम input_release_device(काष्ठा input_handle *handle)
अणु
	काष्ठा input_dev *dev = handle->dev;

	mutex_lock(&dev->mutex);
	__input_release_device(handle);
	mutex_unlock(&dev->mutex);
पूर्ण
EXPORT_SYMBOL(input_release_device);

/**
 * input_खोलो_device - खोलो input device
 * @handle: handle through which device is being accessed
 *
 * This function should be called by input handlers when they
 * want to start receive events from given input device.
 */
पूर्णांक input_खोलो_device(काष्ठा input_handle *handle)
अणु
	काष्ठा input_dev *dev = handle->dev;
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&dev->mutex);
	अगर (retval)
		वापस retval;

	अगर (dev->going_away) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	handle->खोलो++;

	अगर (dev->users++ || dev->inhibited) अणु
		/*
		 * Device is alपढ़ोy खोलोed and/or inhibited,
		 * so we can निकास immediately and report success.
		 */
		जाओ out;
	पूर्ण

	अगर (dev->खोलो) अणु
		retval = dev->खोलो(dev);
		अगर (retval) अणु
			dev->users--;
			handle->खोलो--;
			/*
			 * Make sure we are not delivering any more events
			 * through this handle
			 */
			synchronize_rcu();
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (dev->poller)
		input_dev_poller_start(dev->poller);

 out:
	mutex_unlock(&dev->mutex);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(input_खोलो_device);

पूर्णांक input_flush_device(काष्ठा input_handle *handle, काष्ठा file *file)
अणु
	काष्ठा input_dev *dev = handle->dev;
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&dev->mutex);
	अगर (retval)
		वापस retval;

	अगर (dev->flush)
		retval = dev->flush(dev, file);

	mutex_unlock(&dev->mutex);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(input_flush_device);

/**
 * input_बंद_device - बंद input device
 * @handle: handle through which device is being accessed
 *
 * This function should be called by input handlers when they
 * want to stop receive events from given input device.
 */
व्योम input_बंद_device(काष्ठा input_handle *handle)
अणु
	काष्ठा input_dev *dev = handle->dev;

	mutex_lock(&dev->mutex);

	__input_release_device(handle);

	अगर (!dev->inhibited && !--dev->users) अणु
		अगर (dev->poller)
			input_dev_poller_stop(dev->poller);
		अगर (dev->बंद)
			dev->बंद(dev);
	पूर्ण

	अगर (!--handle->खोलो) अणु
		/*
		 * synchronize_rcu() makes sure that input_pass_event()
		 * completed and that no more input events are delivered
		 * through this handle
		 */
		synchronize_rcu();
	पूर्ण

	mutex_unlock(&dev->mutex);
पूर्ण
EXPORT_SYMBOL(input_बंद_device);

/*
 * Simulate keyup events क्रम all keys that are marked as pressed.
 * The function must be called with dev->event_lock held.
 */
अटल व्योम input_dev_release_keys(काष्ठा input_dev *dev)
अणु
	bool need_sync = false;
	पूर्णांक code;

	अगर (is_event_supported(EV_KEY, dev->evbit, EV_MAX)) अणु
		क्रम_each_set_bit(code, dev->key, KEY_CNT) अणु
			input_pass_event(dev, EV_KEY, code, 0);
			need_sync = true;
		पूर्ण

		अगर (need_sync)
			input_pass_event(dev, EV_SYN, SYN_REPORT, 1);

		स_रखो(dev->key, 0, माप(dev->key));
	पूर्ण
पूर्ण

/*
 * Prepare device क्रम unरेजिस्टरing
 */
अटल व्योम input_disconnect_device(काष्ठा input_dev *dev)
अणु
	काष्ठा input_handle *handle;

	/*
	 * Mark device as going away. Note that we take dev->mutex here
	 * not to protect access to dev->going_away but rather to ensure
	 * that there are no thपढ़ोs in the middle of input_खोलो_device()
	 */
	mutex_lock(&dev->mutex);
	dev->going_away = true;
	mutex_unlock(&dev->mutex);

	spin_lock_irq(&dev->event_lock);

	/*
	 * Simulate keyup events क्रम all pressed keys so that handlers
	 * are not left with "stuck" keys. The driver may जारी
	 * generate events even after we करोne here but they will not
	 * reach any handlers.
	 */
	input_dev_release_keys(dev);

	list_क्रम_each_entry(handle, &dev->h_list, d_node)
		handle->खोलो = 0;

	spin_unlock_irq(&dev->event_lock);
पूर्ण

/**
 * input_scancode_to_scalar() - converts scancode in &काष्ठा input_keymap_entry
 * @ke: keymap entry containing scancode to be converted.
 * @scancode: poपूर्णांकer to the location where converted scancode should
 *	be stored.
 *
 * This function is used to convert scancode stored in &काष्ठा keymap_entry
 * पूर्णांकo scalar क्रमm understood by legacy keymap handling methods. These
 * methods expect scancodes to be represented as 'unsigned int'.
 */
पूर्णांक input_scancode_to_scalar(स्थिर काष्ठा input_keymap_entry *ke,
			     अचिन्हित पूर्णांक *scancode)
अणु
	चयन (ke->len) अणु
	हाल 1:
		*scancode = *((u8 *)ke->scancode);
		अवरोध;

	हाल 2:
		*scancode = *((u16 *)ke->scancode);
		अवरोध;

	हाल 4:
		*scancode = *((u32 *)ke->scancode);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(input_scancode_to_scalar);

/*
 * Those routines handle the शेष हाल where no [gs]etkeycode() is
 * defined. In this हाल, an array indexed by the scancode is used.
 */

अटल अचिन्हित पूर्णांक input_fetch_keycode(काष्ठा input_dev *dev,
					अचिन्हित पूर्णांक index)
अणु
	चयन (dev->keycodesize) अणु
	हाल 1:
		वापस ((u8 *)dev->keycode)[index];

	हाल 2:
		वापस ((u16 *)dev->keycode)[index];

	शेष:
		वापस ((u32 *)dev->keycode)[index];
	पूर्ण
पूर्ण

अटल पूर्णांक input_शेष_getkeycode(काष्ठा input_dev *dev,
				    काष्ठा input_keymap_entry *ke)
अणु
	अचिन्हित पूर्णांक index;
	पूर्णांक error;

	अगर (!dev->keycodesize)
		वापस -EINVAL;

	अगर (ke->flags & INPUT_KEYMAP_BY_INDEX)
		index = ke->index;
	अन्यथा अणु
		error = input_scancode_to_scalar(ke, &index);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (index >= dev->keycodemax)
		वापस -EINVAL;

	ke->keycode = input_fetch_keycode(dev, index);
	ke->index = index;
	ke->len = माप(index);
	स_नकल(ke->scancode, &index, माप(index));

	वापस 0;
पूर्ण

अटल पूर्णांक input_शेष_setkeycode(काष्ठा input_dev *dev,
				    स्थिर काष्ठा input_keymap_entry *ke,
				    अचिन्हित पूर्णांक *old_keycode)
अणु
	अचिन्हित पूर्णांक index;
	पूर्णांक error;
	पूर्णांक i;

	अगर (!dev->keycodesize)
		वापस -EINVAL;

	अगर (ke->flags & INPUT_KEYMAP_BY_INDEX) अणु
		index = ke->index;
	पूर्ण अन्यथा अणु
		error = input_scancode_to_scalar(ke, &index);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (index >= dev->keycodemax)
		वापस -EINVAL;

	अगर (dev->keycodesize < माप(ke->keycode) &&
			(ke->keycode >> (dev->keycodesize * 8)))
		वापस -EINVAL;

	चयन (dev->keycodesize) अणु
		हाल 1: अणु
			u8 *k = (u8 *)dev->keycode;
			*old_keycode = k[index];
			k[index] = ke->keycode;
			अवरोध;
		पूर्ण
		हाल 2: अणु
			u16 *k = (u16 *)dev->keycode;
			*old_keycode = k[index];
			k[index] = ke->keycode;
			अवरोध;
		पूर्ण
		शेष: अणु
			u32 *k = (u32 *)dev->keycode;
			*old_keycode = k[index];
			k[index] = ke->keycode;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (*old_keycode <= KEY_MAX) अणु
		__clear_bit(*old_keycode, dev->keybit);
		क्रम (i = 0; i < dev->keycodemax; i++) अणु
			अगर (input_fetch_keycode(dev, i) == *old_keycode) अणु
				__set_bit(*old_keycode, dev->keybit);
				/* Setting the bit twice is useless, so अवरोध */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	__set_bit(ke->keycode, dev->keybit);
	वापस 0;
पूर्ण

/**
 * input_get_keycode - retrieve keycode currently mapped to a given scancode
 * @dev: input device which keymap is being queried
 * @ke: keymap entry
 *
 * This function should be called by anyone पूर्णांकerested in retrieving current
 * keymap. Presently evdev handlers use it.
 */
पूर्णांक input_get_keycode(काष्ठा input_dev *dev, काष्ठा input_keymap_entry *ke)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	spin_lock_irqsave(&dev->event_lock, flags);
	retval = dev->getkeycode(dev, ke);
	spin_unlock_irqrestore(&dev->event_lock, flags);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(input_get_keycode);

/**
 * input_set_keycode - attribute a keycode to a given scancode
 * @dev: input device which keymap is being updated
 * @ke: new keymap entry
 *
 * This function should be called by anyone needing to update current
 * keymap. Presently keyboard and evdev handlers use it.
 */
पूर्णांक input_set_keycode(काष्ठा input_dev *dev,
		      स्थिर काष्ठा input_keymap_entry *ke)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक old_keycode;
	पूर्णांक retval;

	अगर (ke->keycode > KEY_MAX)
		वापस -EINVAL;

	spin_lock_irqsave(&dev->event_lock, flags);

	retval = dev->setkeycode(dev, ke, &old_keycode);
	अगर (retval)
		जाओ out;

	/* Make sure KEY_RESERVED did not get enabled. */
	__clear_bit(KEY_RESERVED, dev->keybit);

	/*
	 * Simulate keyup event अगर keycode is not present
	 * in the keymap anymore
	 */
	अगर (old_keycode > KEY_MAX) अणु
		dev_warn(dev->dev.parent ?: &dev->dev,
			 "%s: got too big old keycode %#x\n",
			 __func__, old_keycode);
	पूर्ण अन्यथा अगर (test_bit(EV_KEY, dev->evbit) &&
		   !is_event_supported(old_keycode, dev->keybit, KEY_MAX) &&
		   __test_and_clear_bit(old_keycode, dev->key)) अणु
		काष्ठा input_value vals[] =  अणु
			अणु EV_KEY, old_keycode, 0 पूर्ण,
			input_value_sync
		पूर्ण;

		input_pass_values(dev, vals, ARRAY_SIZE(vals));
	पूर्ण

 out:
	spin_unlock_irqrestore(&dev->event_lock, flags);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(input_set_keycode);

bool input_match_device_id(स्थिर काष्ठा input_dev *dev,
			   स्थिर काष्ठा input_device_id *id)
अणु
	अगर (id->flags & INPUT_DEVICE_ID_MATCH_BUS)
		अगर (id->bustype != dev->id.bustype)
			वापस false;

	अगर (id->flags & INPUT_DEVICE_ID_MATCH_VENDOR)
		अगर (id->venकरोr != dev->id.venकरोr)
			वापस false;

	अगर (id->flags & INPUT_DEVICE_ID_MATCH_PRODUCT)
		अगर (id->product != dev->id.product)
			वापस false;

	अगर (id->flags & INPUT_DEVICE_ID_MATCH_VERSION)
		अगर (id->version != dev->id.version)
			वापस false;

	अगर (!biपंचांगap_subset(id->evbit, dev->evbit, EV_MAX) ||
	    !biपंचांगap_subset(id->keybit, dev->keybit, KEY_MAX) ||
	    !biपंचांगap_subset(id->relbit, dev->relbit, REL_MAX) ||
	    !biपंचांगap_subset(id->असलbit, dev->असलbit, ABS_MAX) ||
	    !biपंचांगap_subset(id->mscbit, dev->mscbit, MSC_MAX) ||
	    !biपंचांगap_subset(id->ledbit, dev->ledbit, LED_MAX) ||
	    !biपंचांगap_subset(id->sndbit, dev->sndbit, SND_MAX) ||
	    !biपंचांगap_subset(id->ffbit, dev->ffbit, FF_MAX) ||
	    !biपंचांगap_subset(id->swbit, dev->swbit, SW_MAX) ||
	    !biपंचांगap_subset(id->propbit, dev->propbit, INPUT_PROP_MAX)) अणु
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(input_match_device_id);

अटल स्थिर काष्ठा input_device_id *input_match_device(काष्ठा input_handler *handler,
							काष्ठा input_dev *dev)
अणु
	स्थिर काष्ठा input_device_id *id;

	क्रम (id = handler->id_table; id->flags || id->driver_info; id++) अणु
		अगर (input_match_device_id(dev, id) &&
		    (!handler->match || handler->match(handler, dev))) अणु
			वापस id;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक input_attach_handler(काष्ठा input_dev *dev, काष्ठा input_handler *handler)
अणु
	स्थिर काष्ठा input_device_id *id;
	पूर्णांक error;

	id = input_match_device(handler, dev);
	अगर (!id)
		वापस -ENODEV;

	error = handler->connect(handler, dev, id);
	अगर (error && error != -ENODEV)
		pr_err("failed to attach handler %s to device %s, error: %d\n",
		       handler->name, kobject_name(&dev->dev.kobj), error);

	वापस error;
पूर्ण

#अगर_घोषित CONFIG_COMPAT

अटल पूर्णांक input_bits_to_string(अक्षर *buf, पूर्णांक buf_size,
				अचिन्हित दीर्घ bits, bool skip_empty)
अणु
	पूर्णांक len = 0;

	अगर (in_compat_syscall()) अणु
		u32 dword = bits >> 32;
		अगर (dword || !skip_empty)
			len += snम_लिखो(buf, buf_size, "%x ", dword);

		dword = bits & 0xffffffffUL;
		अगर (dword || !skip_empty || len)
			len += snम_लिखो(buf + len, max(buf_size - len, 0),
					"%x", dword);
	पूर्ण अन्यथा अणु
		अगर (bits || !skip_empty)
			len += snम_लिखो(buf, buf_size, "%lx", bits);
	पूर्ण

	वापस len;
पूर्ण

#अन्यथा /* !CONFIG_COMPAT */

अटल पूर्णांक input_bits_to_string(अक्षर *buf, पूर्णांक buf_size,
				अचिन्हित दीर्घ bits, bool skip_empty)
अणु
	वापस bits || !skip_empty ?
		snम_लिखो(buf, buf_size, "%lx", bits) : 0;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS

अटल काष्ठा proc_dir_entry *proc_bus_input_dir;
अटल DECLARE_WAIT_QUEUE_HEAD(input_devices_poll_रुको);
अटल पूर्णांक input_devices_state;

अटल अंतरभूत व्योम input_wakeup_procfs_पढ़ोers(व्योम)
अणु
	input_devices_state++;
	wake_up(&input_devices_poll_रुको);
पूर्ण

अटल __poll_t input_proc_devices_poll(काष्ठा file *file, poll_table *रुको)
अणु
	poll_रुको(file, &input_devices_poll_रुको, रुको);
	अगर (file->f_version != input_devices_state) अणु
		file->f_version = input_devices_state;
		वापस EPOLLIN | EPOLLRDNORM;
	पूर्ण

	वापस 0;
पूर्ण

जोड़ input_seq_state अणु
	काष्ठा अणु
		अचिन्हित लघु pos;
		bool mutex_acquired;
	पूर्ण;
	व्योम *p;
पूर्ण;

अटल व्योम *input_devices_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	जोड़ input_seq_state *state = (जोड़ input_seq_state *)&seq->निजी;
	पूर्णांक error;

	/* We need to fit पूर्णांकo seq->निजी poपूर्णांकer */
	BUILD_BUG_ON(माप(जोड़ input_seq_state) != माप(seq->निजी));

	error = mutex_lock_पूर्णांकerruptible(&input_mutex);
	अगर (error) अणु
		state->mutex_acquired = false;
		वापस ERR_PTR(error);
	पूर्ण

	state->mutex_acquired = true;

	वापस seq_list_start(&input_dev_list, *pos);
पूर्ण

अटल व्योम *input_devices_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_list_next(v, &input_dev_list, pos);
पूर्ण

अटल व्योम input_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	जोड़ input_seq_state *state = (जोड़ input_seq_state *)&seq->निजी;

	अगर (state->mutex_acquired)
		mutex_unlock(&input_mutex);
पूर्ण

अटल व्योम input_seq_prपूर्णांक_biपंचांगap(काष्ठा seq_file *seq, स्थिर अक्षर *name,
				   अचिन्हित दीर्घ *biपंचांगap, पूर्णांक max)
अणु
	पूर्णांक i;
	bool skip_empty = true;
	अक्षर buf[18];

	seq_म_लिखो(seq, "B: %s=", name);

	क्रम (i = BITS_TO_LONGS(max) - 1; i >= 0; i--) अणु
		अगर (input_bits_to_string(buf, माप(buf),
					 biपंचांगap[i], skip_empty)) अणु
			skip_empty = false;
			seq_म_लिखो(seq, "%s%s", buf, i > 0 ? " " : "");
		पूर्ण
	पूर्ण

	/*
	 * If no output was produced prपूर्णांक a single 0.
	 */
	अगर (skip_empty)
		seq_अ_दो(seq, '0');

	seq_अ_दो(seq, '\n');
पूर्ण

अटल पूर्णांक input_devices_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा input_dev *dev = container_of(v, काष्ठा input_dev, node);
	स्थिर अक्षर *path = kobject_get_path(&dev->dev.kobj, GFP_KERNEL);
	काष्ठा input_handle *handle;

	seq_म_लिखो(seq, "I: Bus=%04x Vendor=%04x Product=%04x Version=%04x\n",
		   dev->id.bustype, dev->id.venकरोr, dev->id.product, dev->id.version);

	seq_म_लिखो(seq, "N: Name=\"%s\"\n", dev->name ? dev->name : "");
	seq_म_लिखो(seq, "P: Phys=%s\n", dev->phys ? dev->phys : "");
	seq_म_लिखो(seq, "S: Sysfs=%s\n", path ? path : "");
	seq_म_लिखो(seq, "U: Uniq=%s\n", dev->uniq ? dev->uniq : "");
	seq_माला_दो(seq, "H: Handlers=");

	list_क्रम_each_entry(handle, &dev->h_list, d_node)
		seq_म_लिखो(seq, "%s ", handle->name);
	seq_अ_दो(seq, '\n');

	input_seq_prपूर्णांक_biपंचांगap(seq, "PROP", dev->propbit, INPUT_PROP_MAX);

	input_seq_prपूर्णांक_biपंचांगap(seq, "EV", dev->evbit, EV_MAX);
	अगर (test_bit(EV_KEY, dev->evbit))
		input_seq_prपूर्णांक_biपंचांगap(seq, "KEY", dev->keybit, KEY_MAX);
	अगर (test_bit(EV_REL, dev->evbit))
		input_seq_prपूर्णांक_biपंचांगap(seq, "REL", dev->relbit, REL_MAX);
	अगर (test_bit(EV_ABS, dev->evbit))
		input_seq_prपूर्णांक_biपंचांगap(seq, "ABS", dev->असलbit, ABS_MAX);
	अगर (test_bit(EV_MSC, dev->evbit))
		input_seq_prपूर्णांक_biपंचांगap(seq, "MSC", dev->mscbit, MSC_MAX);
	अगर (test_bit(EV_LED, dev->evbit))
		input_seq_prपूर्णांक_biपंचांगap(seq, "LED", dev->ledbit, LED_MAX);
	अगर (test_bit(EV_SND, dev->evbit))
		input_seq_prपूर्णांक_biपंचांगap(seq, "SND", dev->sndbit, SND_MAX);
	अगर (test_bit(EV_FF, dev->evbit))
		input_seq_prपूर्णांक_biपंचांगap(seq, "FF", dev->ffbit, FF_MAX);
	अगर (test_bit(EV_SW, dev->evbit))
		input_seq_prपूर्णांक_biपंचांगap(seq, "SW", dev->swbit, SW_MAX);

	seq_अ_दो(seq, '\n');

	kमुक्त(path);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations input_devices_seq_ops = अणु
	.start	= input_devices_seq_start,
	.next	= input_devices_seq_next,
	.stop	= input_seq_stop,
	.show	= input_devices_seq_show,
पूर्ण;

अटल पूर्णांक input_proc_devices_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &input_devices_seq_ops);
पूर्ण

अटल स्थिर काष्ठा proc_ops input_devices_proc_ops = अणु
	.proc_खोलो	= input_proc_devices_खोलो,
	.proc_poll	= input_proc_devices_poll,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release,
पूर्ण;

अटल व्योम *input_handlers_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	जोड़ input_seq_state *state = (जोड़ input_seq_state *)&seq->निजी;
	पूर्णांक error;

	/* We need to fit पूर्णांकo seq->निजी poपूर्णांकer */
	BUILD_BUG_ON(माप(जोड़ input_seq_state) != माप(seq->निजी));

	error = mutex_lock_पूर्णांकerruptible(&input_mutex);
	अगर (error) अणु
		state->mutex_acquired = false;
		वापस ERR_PTR(error);
	पूर्ण

	state->mutex_acquired = true;
	state->pos = *pos;

	वापस seq_list_start(&input_handler_list, *pos);
पूर्ण

अटल व्योम *input_handlers_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	जोड़ input_seq_state *state = (जोड़ input_seq_state *)&seq->निजी;

	state->pos = *pos + 1;
	वापस seq_list_next(v, &input_handler_list, pos);
पूर्ण

अटल पूर्णांक input_handlers_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा input_handler *handler = container_of(v, काष्ठा input_handler, node);
	जोड़ input_seq_state *state = (जोड़ input_seq_state *)&seq->निजी;

	seq_म_लिखो(seq, "N: Number=%u Name=%s", state->pos, handler->name);
	अगर (handler->filter)
		seq_माला_दो(seq, " (filter)");
	अगर (handler->legacy_minors)
		seq_म_लिखो(seq, " Minor=%d", handler->minor);
	seq_अ_दो(seq, '\n');

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations input_handlers_seq_ops = अणु
	.start	= input_handlers_seq_start,
	.next	= input_handlers_seq_next,
	.stop	= input_seq_stop,
	.show	= input_handlers_seq_show,
पूर्ण;

अटल पूर्णांक input_proc_handlers_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &input_handlers_seq_ops);
पूर्ण

अटल स्थिर काष्ठा proc_ops input_handlers_proc_ops = अणु
	.proc_खोलो	= input_proc_handlers_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release,
पूर्ण;

अटल पूर्णांक __init input_proc_init(व्योम)
अणु
	काष्ठा proc_dir_entry *entry;

	proc_bus_input_dir = proc_सूची_गढ़ो("bus/input", शून्य);
	अगर (!proc_bus_input_dir)
		वापस -ENOMEM;

	entry = proc_create("devices", 0, proc_bus_input_dir,
			    &input_devices_proc_ops);
	अगर (!entry)
		जाओ fail1;

	entry = proc_create("handlers", 0, proc_bus_input_dir,
			    &input_handlers_proc_ops);
	अगर (!entry)
		जाओ fail2;

	वापस 0;

 fail2:	हटाओ_proc_entry("devices", proc_bus_input_dir);
 fail1: हटाओ_proc_entry("bus/input", शून्य);
	वापस -ENOMEM;
पूर्ण

अटल व्योम input_proc_निकास(व्योम)
अणु
	हटाओ_proc_entry("devices", proc_bus_input_dir);
	हटाओ_proc_entry("handlers", proc_bus_input_dir);
	हटाओ_proc_entry("bus/input", शून्य);
पूर्ण

#अन्यथा /* !CONFIG_PROC_FS */
अटल अंतरभूत व्योम input_wakeup_procfs_पढ़ोers(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक input_proc_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम input_proc_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर

#घोषणा INPUT_DEV_STRING_ATTR_SHOW(name)				\
अटल sमाप_प्रकार input_dev_show_##name(काष्ठा device *dev,		\
				     काष्ठा device_attribute *attr,	\
				     अक्षर *buf)				\
अणु									\
	काष्ठा input_dev *input_dev = to_input_dev(dev);		\
									\
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n",			\
			 input_dev->name ? input_dev->name : "");	\
पूर्ण									\
अटल DEVICE_ATTR(name, S_IRUGO, input_dev_show_##name, शून्य)

INPUT_DEV_STRING_ATTR_SHOW(name);
INPUT_DEV_STRING_ATTR_SHOW(phys);
INPUT_DEV_STRING_ATTR_SHOW(uniq);

अटल पूर्णांक input_prपूर्णांक_modalias_bits(अक्षर *buf, पूर्णांक size,
				     अक्षर name, अचिन्हित दीर्घ *bm,
				     अचिन्हित पूर्णांक min_bit, अचिन्हित पूर्णांक max_bit)
अणु
	पूर्णांक len = 0, i;

	len += snम_लिखो(buf, max(size, 0), "%c", name);
	क्रम (i = min_bit; i < max_bit; i++)
		अगर (bm[BIT_WORD(i)] & BIT_MASK(i))
			len += snम_लिखो(buf + len, max(size - len, 0), "%X,", i);
	वापस len;
पूर्ण

अटल पूर्णांक input_prपूर्णांक_modalias(अक्षर *buf, पूर्णांक size, काष्ठा input_dev *id,
				पूर्णांक add_cr)
अणु
	पूर्णांक len;

	len = snम_लिखो(buf, max(size, 0),
		       "input:b%04Xv%04Xp%04Xe%04X-",
		       id->id.bustype, id->id.venकरोr,
		       id->id.product, id->id.version);

	len += input_prपूर्णांक_modalias_bits(buf + len, size - len,
				'e', id->evbit, 0, EV_MAX);
	len += input_prपूर्णांक_modalias_bits(buf + len, size - len,
				'k', id->keybit, KEY_MIN_INTERESTING, KEY_MAX);
	len += input_prपूर्णांक_modalias_bits(buf + len, size - len,
				'r', id->relbit, 0, REL_MAX);
	len += input_prपूर्णांक_modalias_bits(buf + len, size - len,
				'a', id->असलbit, 0, ABS_MAX);
	len += input_prपूर्णांक_modalias_bits(buf + len, size - len,
				'm', id->mscbit, 0, MSC_MAX);
	len += input_prपूर्णांक_modalias_bits(buf + len, size - len,
				'l', id->ledbit, 0, LED_MAX);
	len += input_prपूर्णांक_modalias_bits(buf + len, size - len,
				's', id->sndbit, 0, SND_MAX);
	len += input_prपूर्णांक_modalias_bits(buf + len, size - len,
				'f', id->ffbit, 0, FF_MAX);
	len += input_prपूर्णांक_modalias_bits(buf + len, size - len,
				'w', id->swbit, 0, SW_MAX);

	अगर (add_cr)
		len += snम_लिखो(buf + len, max(size - len, 0), "\n");

	वापस len;
पूर्ण

अटल sमाप_प्रकार input_dev_show_modalias(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा input_dev *id = to_input_dev(dev);
	sमाप_प्रकार len;

	len = input_prपूर्णांक_modalias(buf, PAGE_SIZE, id, 1);

	वापस min_t(पूर्णांक, len, PAGE_SIZE);
पूर्ण
अटल DEVICE_ATTR(modalias, S_IRUGO, input_dev_show_modalias, शून्य);

अटल पूर्णांक input_prपूर्णांक_biपंचांगap(अक्षर *buf, पूर्णांक buf_size, अचिन्हित दीर्घ *biपंचांगap,
			      पूर्णांक max, पूर्णांक add_cr);

अटल sमाप_प्रकार input_dev_show_properties(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा input_dev *input_dev = to_input_dev(dev);
	पूर्णांक len = input_prपूर्णांक_biपंचांगap(buf, PAGE_SIZE, input_dev->propbit,
				     INPUT_PROP_MAX, true);
	वापस min_t(पूर्णांक, len, PAGE_SIZE);
पूर्ण
अटल DEVICE_ATTR(properties, S_IRUGO, input_dev_show_properties, शून्य);

अटल पूर्णांक input_inhibit_device(काष्ठा input_dev *dev);
अटल पूर्णांक input_uninhibit_device(काष्ठा input_dev *dev);

अटल sमाप_प्रकार inhibited_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा input_dev *input_dev = to_input_dev(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", input_dev->inhibited);
पूर्ण

अटल sमाप_प्रकार inhibited_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार len)
अणु
	काष्ठा input_dev *input_dev = to_input_dev(dev);
	sमाप_प्रकार rv;
	bool inhibited;

	अगर (strtobool(buf, &inhibited))
		वापस -EINVAL;

	अगर (inhibited)
		rv = input_inhibit_device(input_dev);
	अन्यथा
		rv = input_uninhibit_device(input_dev);

	अगर (rv != 0)
		वापस rv;

	वापस len;
पूर्ण

अटल DEVICE_ATTR_RW(inhibited);

अटल काष्ठा attribute *input_dev_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_phys.attr,
	&dev_attr_uniq.attr,
	&dev_attr_modalias.attr,
	&dev_attr_properties.attr,
	&dev_attr_inhibited.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group input_dev_attr_group = अणु
	.attrs	= input_dev_attrs,
पूर्ण;

#घोषणा INPUT_DEV_ID_ATTR(name)						\
अटल sमाप_प्रकार input_dev_show_id_##name(काष्ठा device *dev,		\
					काष्ठा device_attribute *attr,	\
					अक्षर *buf)			\
अणु									\
	काष्ठा input_dev *input_dev = to_input_dev(dev);		\
	वापस scnम_लिखो(buf, PAGE_SIZE, "%04x\n", input_dev->id.name);	\
पूर्ण									\
अटल DEVICE_ATTR(name, S_IRUGO, input_dev_show_id_##name, शून्य)

INPUT_DEV_ID_ATTR(bustype);
INPUT_DEV_ID_ATTR(venकरोr);
INPUT_DEV_ID_ATTR(product);
INPUT_DEV_ID_ATTR(version);

अटल काष्ठा attribute *input_dev_id_attrs[] = अणु
	&dev_attr_bustype.attr,
	&dev_attr_venकरोr.attr,
	&dev_attr_product.attr,
	&dev_attr_version.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group input_dev_id_attr_group = अणु
	.name	= "id",
	.attrs	= input_dev_id_attrs,
पूर्ण;

अटल पूर्णांक input_prपूर्णांक_biपंचांगap(अक्षर *buf, पूर्णांक buf_size, अचिन्हित दीर्घ *biपंचांगap,
			      पूर्णांक max, पूर्णांक add_cr)
अणु
	पूर्णांक i;
	पूर्णांक len = 0;
	bool skip_empty = true;

	क्रम (i = BITS_TO_LONGS(max) - 1; i >= 0; i--) अणु
		len += input_bits_to_string(buf + len, max(buf_size - len, 0),
					    biपंचांगap[i], skip_empty);
		अगर (len) अणु
			skip_empty = false;
			अगर (i > 0)
				len += snम_लिखो(buf + len, max(buf_size - len, 0), " ");
		पूर्ण
	पूर्ण

	/*
	 * If no output was produced prपूर्णांक a single 0.
	 */
	अगर (len == 0)
		len = snम_लिखो(buf, buf_size, "%d", 0);

	अगर (add_cr)
		len += snम_लिखो(buf + len, max(buf_size - len, 0), "\n");

	वापस len;
पूर्ण

#घोषणा INPUT_DEV_CAP_ATTR(ev, bm)					\
अटल sमाप_प्रकार input_dev_show_cap_##bm(काष्ठा device *dev,		\
				       काष्ठा device_attribute *attr,	\
				       अक्षर *buf)			\
अणु									\
	काष्ठा input_dev *input_dev = to_input_dev(dev);		\
	पूर्णांक len = input_prपूर्णांक_biपंचांगap(buf, PAGE_SIZE,			\
				     input_dev->bm##bit, ev##_MAX,	\
				     true);				\
	वापस min_t(पूर्णांक, len, PAGE_SIZE);				\
पूर्ण									\
अटल DEVICE_ATTR(bm, S_IRUGO, input_dev_show_cap_##bm, शून्य)

INPUT_DEV_CAP_ATTR(EV, ev);
INPUT_DEV_CAP_ATTR(KEY, key);
INPUT_DEV_CAP_ATTR(REL, rel);
INPUT_DEV_CAP_ATTR(ABS, असल);
INPUT_DEV_CAP_ATTR(MSC, msc);
INPUT_DEV_CAP_ATTR(LED, led);
INPUT_DEV_CAP_ATTR(SND, snd);
INPUT_DEV_CAP_ATTR(FF, ff);
INPUT_DEV_CAP_ATTR(SW, sw);

अटल काष्ठा attribute *input_dev_caps_attrs[] = अणु
	&dev_attr_ev.attr,
	&dev_attr_key.attr,
	&dev_attr_rel.attr,
	&dev_attr_असल.attr,
	&dev_attr_msc.attr,
	&dev_attr_led.attr,
	&dev_attr_snd.attr,
	&dev_attr_ff.attr,
	&dev_attr_sw.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group input_dev_caps_attr_group = अणु
	.name	= "capabilities",
	.attrs	= input_dev_caps_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *input_dev_attr_groups[] = अणु
	&input_dev_attr_group,
	&input_dev_id_attr_group,
	&input_dev_caps_attr_group,
	&input_poller_attribute_group,
	शून्य
पूर्ण;

अटल व्योम input_dev_release(काष्ठा device *device)
अणु
	काष्ठा input_dev *dev = to_input_dev(device);

	input_ff_destroy(dev);
	input_mt_destroy_slots(dev);
	kमुक्त(dev->poller);
	kमुक्त(dev->असलinfo);
	kमुक्त(dev->vals);
	kमुक्त(dev);

	module_put(THIS_MODULE);
पूर्ण

/*
 * Input uevent पूर्णांकerface - loading event handlers based on
 * device bitfields.
 */
अटल पूर्णांक input_add_uevent_bm_var(काष्ठा kobj_uevent_env *env,
				   स्थिर अक्षर *name, अचिन्हित दीर्घ *biपंचांगap, पूर्णांक max)
अणु
	पूर्णांक len;

	अगर (add_uevent_var(env, "%s", name))
		वापस -ENOMEM;

	len = input_prपूर्णांक_biपंचांगap(&env->buf[env->buflen - 1],
				 माप(env->buf) - env->buflen,
				 biपंचांगap, max, false);
	अगर (len >= (माप(env->buf) - env->buflen))
		वापस -ENOMEM;

	env->buflen += len;
	वापस 0;
पूर्ण

अटल पूर्णांक input_add_uevent_modalias_var(काष्ठा kobj_uevent_env *env,
					 काष्ठा input_dev *dev)
अणु
	पूर्णांक len;

	अगर (add_uevent_var(env, "MODALIAS="))
		वापस -ENOMEM;

	len = input_prपूर्णांक_modalias(&env->buf[env->buflen - 1],
				   माप(env->buf) - env->buflen,
				   dev, 0);
	अगर (len >= (माप(env->buf) - env->buflen))
		वापस -ENOMEM;

	env->buflen += len;
	वापस 0;
पूर्ण

#घोषणा INPUT_ADD_HOTPLUG_VAR(fmt, val...)				\
	करो अणु								\
		पूर्णांक err = add_uevent_var(env, fmt, val);		\
		अगर (err)						\
			वापस err;					\
	पूर्ण जबतक (0)

#घोषणा INPUT_ADD_HOTPLUG_BM_VAR(name, bm, max)				\
	करो अणु								\
		पूर्णांक err = input_add_uevent_bm_var(env, name, bm, max);	\
		अगर (err)						\
			वापस err;					\
	पूर्ण जबतक (0)

#घोषणा INPUT_ADD_HOTPLUG_MODALIAS_VAR(dev)				\
	करो अणु								\
		पूर्णांक err = input_add_uevent_modalias_var(env, dev);	\
		अगर (err)						\
			वापस err;					\
	पूर्ण जबतक (0)

अटल पूर्णांक input_dev_uevent(काष्ठा device *device, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा input_dev *dev = to_input_dev(device);

	INPUT_ADD_HOTPLUG_VAR("PRODUCT=%x/%x/%x/%x",
				dev->id.bustype, dev->id.venकरोr,
				dev->id.product, dev->id.version);
	अगर (dev->name)
		INPUT_ADD_HOTPLUG_VAR("NAME=\"%s\"", dev->name);
	अगर (dev->phys)
		INPUT_ADD_HOTPLUG_VAR("PHYS=\"%s\"", dev->phys);
	अगर (dev->uniq)
		INPUT_ADD_HOTPLUG_VAR("UNIQ=\"%s\"", dev->uniq);

	INPUT_ADD_HOTPLUG_BM_VAR("PROP=", dev->propbit, INPUT_PROP_MAX);

	INPUT_ADD_HOTPLUG_BM_VAR("EV=", dev->evbit, EV_MAX);
	अगर (test_bit(EV_KEY, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("KEY=", dev->keybit, KEY_MAX);
	अगर (test_bit(EV_REL, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("REL=", dev->relbit, REL_MAX);
	अगर (test_bit(EV_ABS, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("ABS=", dev->असलbit, ABS_MAX);
	अगर (test_bit(EV_MSC, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("MSC=", dev->mscbit, MSC_MAX);
	अगर (test_bit(EV_LED, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("LED=", dev->ledbit, LED_MAX);
	अगर (test_bit(EV_SND, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("SND=", dev->sndbit, SND_MAX);
	अगर (test_bit(EV_FF, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("FF=", dev->ffbit, FF_MAX);
	अगर (test_bit(EV_SW, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("SW=", dev->swbit, SW_MAX);

	INPUT_ADD_HOTPLUG_MODALIAS_VAR(dev);

	वापस 0;
पूर्ण

#घोषणा INPUT_DO_TOGGLE(dev, type, bits, on)				\
	करो अणु								\
		पूर्णांक i;							\
		bool active;						\
									\
		अगर (!test_bit(EV_##type, dev->evbit))			\
			अवरोध;						\
									\
		क्रम_each_set_bit(i, dev->bits##bit, type##_CNT) अणु	\
			active = test_bit(i, dev->bits);		\
			अगर (!active && !on)				\
				जारी;				\
									\
			dev->event(dev, EV_##type, i, on ? active : 0);	\
		पूर्ण							\
	पूर्ण जबतक (0)

अटल व्योम input_dev_toggle(काष्ठा input_dev *dev, bool activate)
अणु
	अगर (!dev->event)
		वापस;

	INPUT_DO_TOGGLE(dev, LED, led, activate);
	INPUT_DO_TOGGLE(dev, SND, snd, activate);

	अगर (activate && test_bit(EV_REP, dev->evbit)) अणु
		dev->event(dev, EV_REP, REP_PERIOD, dev->rep[REP_PERIOD]);
		dev->event(dev, EV_REP, REP_DELAY, dev->rep[REP_DELAY]);
	पूर्ण
पूर्ण

/**
 * input_reset_device() - reset/restore the state of input device
 * @dev: input device whose state needs to be reset
 *
 * This function tries to reset the state of an खोलोed input device and
 * bring पूर्णांकernal state and state अगर the hardware in sync with each other.
 * We mark all keys as released, restore LED state, repeat rate, etc.
 */
व्योम input_reset_device(काष्ठा input_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	mutex_lock(&dev->mutex);
	spin_lock_irqsave(&dev->event_lock, flags);

	input_dev_toggle(dev, true);
	input_dev_release_keys(dev);

	spin_unlock_irqrestore(&dev->event_lock, flags);
	mutex_unlock(&dev->mutex);
पूर्ण
EXPORT_SYMBOL(input_reset_device);

अटल पूर्णांक input_inhibit_device(काष्ठा input_dev *dev)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&dev->mutex);

	अगर (dev->inhibited)
		जाओ out;

	अगर (dev->users) अणु
		अगर (dev->बंद)
			dev->बंद(dev);
		अगर (dev->poller)
			input_dev_poller_stop(dev->poller);
	पूर्ण

	spin_lock_irq(&dev->event_lock);
	input_dev_release_keys(dev);
	input_dev_toggle(dev, false);
	spin_unlock_irq(&dev->event_lock);

	dev->inhibited = true;

out:
	mutex_unlock(&dev->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक input_uninhibit_device(काष्ठा input_dev *dev)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&dev->mutex);

	अगर (!dev->inhibited)
		जाओ out;

	अगर (dev->users) अणु
		अगर (dev->खोलो) अणु
			ret = dev->खोलो(dev);
			अगर (ret)
				जाओ out;
		पूर्ण
		अगर (dev->poller)
			input_dev_poller_start(dev->poller);
	पूर्ण

	dev->inhibited = false;
	spin_lock_irq(&dev->event_lock);
	input_dev_toggle(dev, true);
	spin_unlock_irq(&dev->event_lock);

out:
	mutex_unlock(&dev->mutex);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक input_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा input_dev *input_dev = to_input_dev(dev);

	spin_lock_irq(&input_dev->event_lock);

	/*
	 * Keys that are pressed now are unlikely to be
	 * still pressed when we resume.
	 */
	input_dev_release_keys(input_dev);

	/* Turn off LEDs and sounds, अगर any are active. */
	input_dev_toggle(input_dev, false);

	spin_unlock_irq(&input_dev->event_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक input_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा input_dev *input_dev = to_input_dev(dev);

	spin_lock_irq(&input_dev->event_lock);

	/* Restore state of LEDs and sounds, अगर any were active. */
	input_dev_toggle(input_dev, true);

	spin_unlock_irq(&input_dev->event_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक input_dev_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा input_dev *input_dev = to_input_dev(dev);

	spin_lock_irq(&input_dev->event_lock);

	/*
	 * Keys that are pressed now are unlikely to be
	 * still pressed when we resume.
	 */
	input_dev_release_keys(input_dev);

	spin_unlock_irq(&input_dev->event_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक input_dev_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा input_dev *input_dev = to_input_dev(dev);

	spin_lock_irq(&input_dev->event_lock);

	/* Turn off LEDs and sounds, अगर any are active. */
	input_dev_toggle(input_dev, false);

	spin_unlock_irq(&input_dev->event_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops input_dev_pm_ops = अणु
	.suspend	= input_dev_suspend,
	.resume		= input_dev_resume,
	.मुक्तze		= input_dev_मुक्तze,
	.घातeroff	= input_dev_घातeroff,
	.restore	= input_dev_resume,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा device_type input_dev_type = अणु
	.groups		= input_dev_attr_groups,
	.release	= input_dev_release,
	.uevent		= input_dev_uevent,
#अगर_घोषित CONFIG_PM_SLEEP
	.pm		= &input_dev_pm_ops,
#पूर्ण_अगर
पूर्ण;

अटल अक्षर *input_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "input/%s", dev_name(dev));
पूर्ण

काष्ठा class input_class = अणु
	.name		= "input",
	.devnode	= input_devnode,
पूर्ण;
EXPORT_SYMBOL_GPL(input_class);

/**
 * input_allocate_device - allocate memory क्रम new input device
 *
 * Returns prepared काष्ठा input_dev or %शून्य.
 *
 * NOTE: Use input_मुक्त_device() to मुक्त devices that have not been
 * रेजिस्टरed; input_unरेजिस्टर_device() should be used क्रम alपढ़ोy
 * रेजिस्टरed devices.
 */
काष्ठा input_dev *input_allocate_device(व्योम)
अणु
	अटल atomic_t input_no = ATOMIC_INIT(-1);
	काष्ठा input_dev *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev) अणु
		dev->dev.type = &input_dev_type;
		dev->dev.class = &input_class;
		device_initialize(&dev->dev);
		mutex_init(&dev->mutex);
		spin_lock_init(&dev->event_lock);
		समयr_setup(&dev->समयr, शून्य, 0);
		INIT_LIST_HEAD(&dev->h_list);
		INIT_LIST_HEAD(&dev->node);

		dev_set_name(&dev->dev, "input%lu",
			     (अचिन्हित दीर्घ)atomic_inc_वापस(&input_no));

		__module_get(THIS_MODULE);
	पूर्ण

	वापस dev;
पूर्ण
EXPORT_SYMBOL(input_allocate_device);

काष्ठा input_devres अणु
	काष्ठा input_dev *input;
पूर्ण;

अटल पूर्णांक devm_input_device_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा input_devres *devres = res;

	वापस devres->input == data;
पूर्ण

अटल व्योम devm_input_device_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा input_devres *devres = res;
	काष्ठा input_dev *input = devres->input;

	dev_dbg(dev, "%s: dropping reference to %s\n",
		__func__, dev_name(&input->dev));
	input_put_device(input);
पूर्ण

/**
 * devm_input_allocate_device - allocate managed input device
 * @dev: device owning the input device being created
 *
 * Returns prepared काष्ठा input_dev or %शून्य.
 *
 * Managed input devices करो not need to be explicitly unरेजिस्टरed or
 * मुक्तd as it will be करोne स्वतःmatically when owner device unbinds from
 * its driver (or binding fails). Once managed input device is allocated,
 * it is पढ़ोy to be set up and रेजिस्टरed in the same fashion as regular
 * input device. There are no special devm_input_device_[un]रेजिस्टर()
 * variants, regular ones work with both managed and unmanaged devices,
 * should you need them. In most हालs however, managed input device need
 * not be explicitly unरेजिस्टरed or मुक्तd.
 *
 * NOTE: the owner device is set up as parent of input device and users
 * should not override it.
 */
काष्ठा input_dev *devm_input_allocate_device(काष्ठा device *dev)
अणु
	काष्ठा input_dev *input;
	काष्ठा input_devres *devres;

	devres = devres_alloc(devm_input_device_release,
			      माप(*devres), GFP_KERNEL);
	अगर (!devres)
		वापस शून्य;

	input = input_allocate_device();
	अगर (!input) अणु
		devres_मुक्त(devres);
		वापस शून्य;
	पूर्ण

	input->dev.parent = dev;
	input->devres_managed = true;

	devres->input = input;
	devres_add(dev, devres);

	वापस input;
पूर्ण
EXPORT_SYMBOL(devm_input_allocate_device);

/**
 * input_मुक्त_device - मुक्त memory occupied by input_dev काष्ठाure
 * @dev: input device to मुक्त
 *
 * This function should only be used अगर input_रेजिस्टर_device()
 * was not called yet or अगर it failed. Once device was रेजिस्टरed
 * use input_unरेजिस्टर_device() and memory will be मुक्तd once last
 * reference to the device is dropped.
 *
 * Device should be allocated by input_allocate_device().
 *
 * NOTE: If there are references to the input device then memory
 * will not be मुक्तd until last reference is dropped.
 */
व्योम input_मुक्त_device(काष्ठा input_dev *dev)
अणु
	अगर (dev) अणु
		अगर (dev->devres_managed)
			WARN_ON(devres_destroy(dev->dev.parent,
						devm_input_device_release,
						devm_input_device_match,
						dev));
		input_put_device(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(input_मुक्त_device);

/**
 * input_set_बारtamp - set बारtamp क्रम input events
 * @dev: input device to set बारtamp क्रम
 * @बारtamp: the समय at which the event has occurred
 *   in CLOCK_MONOTONIC
 *
 * This function is पूर्णांकended to provide to the input प्रणाली a more
 * accurate समय of when an event actually occurred. The driver should
 * call this function as soon as a बारtamp is acquired ensuring
 * घड़ी conversions in input_set_बारtamp are करोne correctly.
 *
 * The प्रणाली entering suspend state between बारtamp acquisition and
 * calling input_set_बारtamp can result in inaccurate conversions.
 */
व्योम input_set_बारtamp(काष्ठा input_dev *dev, kसमय_प्रकार बारtamp)
अणु
	dev->बारtamp[INPUT_CLK_MONO] = बारtamp;
	dev->बारtamp[INPUT_CLK_REAL] = kसमय_mono_to_real(बारtamp);
	dev->बारtamp[INPUT_CLK_BOOT] = kसमय_mono_to_any(बारtamp,
							   TK_OFFS_BOOT);
पूर्ण
EXPORT_SYMBOL(input_set_बारtamp);

/**
 * input_get_बारtamp - get बारtamp क्रम input events
 * @dev: input device to get बारtamp from
 *
 * A valid बारtamp is a बारtamp of non-zero value.
 */
kसमय_प्रकार *input_get_बारtamp(काष्ठा input_dev *dev)
अणु
	स्थिर kसमय_प्रकार invalid_बारtamp = kसमय_set(0, 0);

	अगर (!kसमय_compare(dev->बारtamp[INPUT_CLK_MONO], invalid_बारtamp))
		input_set_बारtamp(dev, kसमय_get());

	वापस dev->बारtamp;
पूर्ण
EXPORT_SYMBOL(input_get_बारtamp);

/**
 * input_set_capability - mark device as capable of a certain event
 * @dev: device that is capable of emitting or accepting event
 * @type: type of the event (EV_KEY, EV_REL, etc...)
 * @code: event code
 *
 * In addition to setting up corresponding bit in appropriate capability
 * biपंचांगap the function also adjusts dev->evbit.
 */
व्योम input_set_capability(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code)
अणु
	चयन (type) अणु
	हाल EV_KEY:
		__set_bit(code, dev->keybit);
		अवरोध;

	हाल EV_REL:
		__set_bit(code, dev->relbit);
		अवरोध;

	हाल EV_ABS:
		input_alloc_असलinfo(dev);
		अगर (!dev->असलinfo)
			वापस;

		__set_bit(code, dev->असलbit);
		अवरोध;

	हाल EV_MSC:
		__set_bit(code, dev->mscbit);
		अवरोध;

	हाल EV_SW:
		__set_bit(code, dev->swbit);
		अवरोध;

	हाल EV_LED:
		__set_bit(code, dev->ledbit);
		अवरोध;

	हाल EV_SND:
		__set_bit(code, dev->sndbit);
		अवरोध;

	हाल EV_FF:
		__set_bit(code, dev->ffbit);
		अवरोध;

	हाल EV_PWR:
		/* करो nothing */
		अवरोध;

	शेष:
		pr_err("%s: unknown type %u (code %u)\n", __func__, type, code);
		dump_stack();
		वापस;
	पूर्ण

	__set_bit(type, dev->evbit);
पूर्ण
EXPORT_SYMBOL(input_set_capability);

अटल अचिन्हित पूर्णांक input_estimate_events_per_packet(काष्ठा input_dev *dev)
अणु
	पूर्णांक mt_slots;
	पूर्णांक i;
	अचिन्हित पूर्णांक events;

	अगर (dev->mt) अणु
		mt_slots = dev->mt->num_slots;
	पूर्ण अन्यथा अगर (test_bit(ABS_MT_TRACKING_ID, dev->असलbit)) अणु
		mt_slots = dev->असलinfo[ABS_MT_TRACKING_ID].maximum -
			   dev->असलinfo[ABS_MT_TRACKING_ID].minimum + 1,
		mt_slots = clamp(mt_slots, 2, 32);
	पूर्ण अन्यथा अगर (test_bit(ABS_MT_POSITION_X, dev->असलbit)) अणु
		mt_slots = 2;
	पूर्ण अन्यथा अणु
		mt_slots = 0;
	पूर्ण

	events = mt_slots + 1; /* count SYN_MT_REPORT and SYN_REPORT */

	अगर (test_bit(EV_ABS, dev->evbit))
		क्रम_each_set_bit(i, dev->असलbit, ABS_CNT)
			events += input_is_mt_axis(i) ? mt_slots : 1;

	अगर (test_bit(EV_REL, dev->evbit))
		events += biपंचांगap_weight(dev->relbit, REL_CNT);

	/* Make room क्रम KEY and MSC events */
	events += 7;

	वापस events;
पूर्ण

#घोषणा INPUT_CLEANSE_BITMASK(dev, type, bits)				\
	करो अणु								\
		अगर (!test_bit(EV_##type, dev->evbit))			\
			स_रखो(dev->bits##bit, 0,			\
				माप(dev->bits##bit));		\
	पूर्ण जबतक (0)

अटल व्योम input_cleanse_biपंचांगasks(काष्ठा input_dev *dev)
अणु
	INPUT_CLEANSE_BITMASK(dev, KEY, key);
	INPUT_CLEANSE_BITMASK(dev, REL, rel);
	INPUT_CLEANSE_BITMASK(dev, ABS, असल);
	INPUT_CLEANSE_BITMASK(dev, MSC, msc);
	INPUT_CLEANSE_BITMASK(dev, LED, led);
	INPUT_CLEANSE_BITMASK(dev, SND, snd);
	INPUT_CLEANSE_BITMASK(dev, FF, ff);
	INPUT_CLEANSE_BITMASK(dev, SW, sw);
पूर्ण

अटल व्योम __input_unरेजिस्टर_device(काष्ठा input_dev *dev)
अणु
	काष्ठा input_handle *handle, *next;

	input_disconnect_device(dev);

	mutex_lock(&input_mutex);

	list_क्रम_each_entry_safe(handle, next, &dev->h_list, d_node)
		handle->handler->disconnect(handle);
	WARN_ON(!list_empty(&dev->h_list));

	del_समयr_sync(&dev->समयr);
	list_del_init(&dev->node);

	input_wakeup_procfs_पढ़ोers();

	mutex_unlock(&input_mutex);

	device_del(&dev->dev);
पूर्ण

अटल व्योम devm_input_device_unरेजिस्टर(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा input_devres *devres = res;
	काष्ठा input_dev *input = devres->input;

	dev_dbg(dev, "%s: unregistering device %s\n",
		__func__, dev_name(&input->dev));
	__input_unरेजिस्टर_device(input);
पूर्ण

/**
 * input_enable_softrepeat - enable software स्वतःrepeat
 * @dev: input device
 * @delay: repeat delay
 * @period: repeat period
 *
 * Enable software स्वतःrepeat on the input device.
 */
व्योम input_enable_softrepeat(काष्ठा input_dev *dev, पूर्णांक delay, पूर्णांक period)
अणु
	dev->समयr.function = input_repeat_key;
	dev->rep[REP_DELAY] = delay;
	dev->rep[REP_PERIOD] = period;
पूर्ण
EXPORT_SYMBOL(input_enable_softrepeat);

bool input_device_enabled(काष्ठा input_dev *dev)
अणु
	lockdep_निश्चित_held(&dev->mutex);

	वापस !dev->inhibited && dev->users > 0;
पूर्ण
EXPORT_SYMBOL_GPL(input_device_enabled);

/**
 * input_रेजिस्टर_device - रेजिस्टर device with input core
 * @dev: device to be रेजिस्टरed
 *
 * This function रेजिस्टरs device with input core. The device must be
 * allocated with input_allocate_device() and all it's capabilities
 * set up beक्रमe रेजिस्टरing.
 * If function fails the device must be मुक्तd with input_मुक्त_device().
 * Once device has been successfully रेजिस्टरed it can be unरेजिस्टरed
 * with input_unरेजिस्टर_device(); input_मुक्त_device() should not be
 * called in this हाल.
 *
 * Note that this function is also used to रेजिस्टर managed input devices
 * (ones allocated with devm_input_allocate_device()). Such managed input
 * devices need not be explicitly unरेजिस्टरed or मुक्तd, their tear करोwn
 * is controlled by the devres infraकाष्ठाure. It is also worth noting
 * that tear करोwn of managed input devices is पूर्णांकernally a 2-step process:
 * रेजिस्टरed managed input device is first unरेजिस्टरed, but stays in
 * memory and can still handle input_event() calls (although events will
 * not be delivered anywhere). The मुक्तing of managed input device will
 * happen later, when devres stack is unwound to the poपूर्णांक where device
 * allocation was made.
 */
पूर्णांक input_रेजिस्टर_device(काष्ठा input_dev *dev)
अणु
	काष्ठा input_devres *devres = शून्य;
	काष्ठा input_handler *handler;
	अचिन्हित पूर्णांक packet_size;
	स्थिर अक्षर *path;
	पूर्णांक error;

	अगर (test_bit(EV_ABS, dev->evbit) && !dev->असलinfo) अणु
		dev_err(&dev->dev,
			"Absolute device without dev->absinfo, refusing to register\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dev->devres_managed) अणु
		devres = devres_alloc(devm_input_device_unरेजिस्टर,
				      माप(*devres), GFP_KERNEL);
		अगर (!devres)
			वापस -ENOMEM;

		devres->input = dev;
	पूर्ण

	/* Every input device generates EV_SYN/SYN_REPORT events. */
	__set_bit(EV_SYN, dev->evbit);

	/* KEY_RESERVED is not supposed to be transmitted to userspace. */
	__clear_bit(KEY_RESERVED, dev->keybit);

	/* Make sure that biपंचांगasks not mentioned in dev->evbit are clean. */
	input_cleanse_biपंचांगasks(dev);

	packet_size = input_estimate_events_per_packet(dev);
	अगर (dev->hपूर्णांक_events_per_packet < packet_size)
		dev->hपूर्णांक_events_per_packet = packet_size;

	dev->max_vals = dev->hपूर्णांक_events_per_packet + 2;
	dev->vals = kसुस्मृति(dev->max_vals, माप(*dev->vals), GFP_KERNEL);
	अगर (!dev->vals) अणु
		error = -ENOMEM;
		जाओ err_devres_मुक्त;
	पूर्ण

	/*
	 * If delay and period are pre-set by the driver, then स्वतःrepeating
	 * is handled by the driver itself and we करोn't करो it in input.c.
	 */
	अगर (!dev->rep[REP_DELAY] && !dev->rep[REP_PERIOD])
		input_enable_softrepeat(dev, 250, 33);

	अगर (!dev->getkeycode)
		dev->getkeycode = input_शेष_getkeycode;

	अगर (!dev->setkeycode)
		dev->setkeycode = input_शेष_setkeycode;

	अगर (dev->poller)
		input_dev_poller_finalize(dev->poller);

	error = device_add(&dev->dev);
	अगर (error)
		जाओ err_मुक्त_vals;

	path = kobject_get_path(&dev->dev.kobj, GFP_KERNEL);
	pr_info("%s as %s\n",
		dev->name ? dev->name : "Unspecified device",
		path ? path : "N/A");
	kमुक्त(path);

	error = mutex_lock_पूर्णांकerruptible(&input_mutex);
	अगर (error)
		जाओ err_device_del;

	list_add_tail(&dev->node, &input_dev_list);

	list_क्रम_each_entry(handler, &input_handler_list, node)
		input_attach_handler(dev, handler);

	input_wakeup_procfs_पढ़ोers();

	mutex_unlock(&input_mutex);

	अगर (dev->devres_managed) अणु
		dev_dbg(dev->dev.parent, "%s: registering %s with devres.\n",
			__func__, dev_name(&dev->dev));
		devres_add(dev->dev.parent, devres);
	पूर्ण
	वापस 0;

err_device_del:
	device_del(&dev->dev);
err_मुक्त_vals:
	kमुक्त(dev->vals);
	dev->vals = शून्य;
err_devres_मुक्त:
	devres_मुक्त(devres);
	वापस error;
पूर्ण
EXPORT_SYMBOL(input_रेजिस्टर_device);

/**
 * input_unरेजिस्टर_device - unरेजिस्टर previously रेजिस्टरed device
 * @dev: device to be unरेजिस्टरed
 *
 * This function unरेजिस्टरs an input device. Once device is unरेजिस्टरed
 * the caller should not try to access it as it may get मुक्तd at any moment.
 */
व्योम input_unरेजिस्टर_device(काष्ठा input_dev *dev)
अणु
	अगर (dev->devres_managed) अणु
		WARN_ON(devres_destroy(dev->dev.parent,
					devm_input_device_unरेजिस्टर,
					devm_input_device_match,
					dev));
		__input_unरेजिस्टर_device(dev);
		/*
		 * We करो not करो input_put_device() here because it will be करोne
		 * when 2nd devres fires up.
		 */
	पूर्ण अन्यथा अणु
		__input_unरेजिस्टर_device(dev);
		input_put_device(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(input_unरेजिस्टर_device);

/**
 * input_रेजिस्टर_handler - रेजिस्टर a new input handler
 * @handler: handler to be रेजिस्टरed
 *
 * This function रेजिस्टरs a new input handler (पूर्णांकerface) क्रम input
 * devices in the प्रणाली and attaches it to all input devices that
 * are compatible with the handler.
 */
पूर्णांक input_रेजिस्टर_handler(काष्ठा input_handler *handler)
अणु
	काष्ठा input_dev *dev;
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&input_mutex);
	अगर (error)
		वापस error;

	INIT_LIST_HEAD(&handler->h_list);

	list_add_tail(&handler->node, &input_handler_list);

	list_क्रम_each_entry(dev, &input_dev_list, node)
		input_attach_handler(dev, handler);

	input_wakeup_procfs_पढ़ोers();

	mutex_unlock(&input_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(input_रेजिस्टर_handler);

/**
 * input_unरेजिस्टर_handler - unरेजिस्टरs an input handler
 * @handler: handler to be unरेजिस्टरed
 *
 * This function disconnects a handler from its input devices and
 * हटाओs it from lists of known handlers.
 */
व्योम input_unरेजिस्टर_handler(काष्ठा input_handler *handler)
अणु
	काष्ठा input_handle *handle, *next;

	mutex_lock(&input_mutex);

	list_क्रम_each_entry_safe(handle, next, &handler->h_list, h_node)
		handler->disconnect(handle);
	WARN_ON(!list_empty(&handler->h_list));

	list_del_init(&handler->node);

	input_wakeup_procfs_पढ़ोers();

	mutex_unlock(&input_mutex);
पूर्ण
EXPORT_SYMBOL(input_unरेजिस्टर_handler);

/**
 * input_handler_क्रम_each_handle - handle iterator
 * @handler: input handler to iterate
 * @data: data क्रम the callback
 * @fn: function to be called क्रम each handle
 *
 * Iterate over @bus's list of devices, and call @fn क्रम each, passing
 * it @data and stop when @fn वापसs a non-zero value. The function is
 * using RCU to traverse the list and thereक्रमe may be using in atomic
 * contexts. The @fn callback is invoked from RCU critical section and
 * thus must not sleep.
 */
पूर्णांक input_handler_क्रम_each_handle(काष्ठा input_handler *handler, व्योम *data,
				  पूर्णांक (*fn)(काष्ठा input_handle *, व्योम *))
अणु
	काष्ठा input_handle *handle;
	पूर्णांक retval = 0;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(handle, &handler->h_list, h_node) अणु
		retval = fn(handle, data);
		अगर (retval)
			अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस retval;
पूर्ण
EXPORT_SYMBOL(input_handler_क्रम_each_handle);

/**
 * input_रेजिस्टर_handle - रेजिस्टर a new input handle
 * @handle: handle to रेजिस्टर
 *
 * This function माला_दो a new input handle onto device's
 * and handler's lists so that events can flow through
 * it once it is खोलोed using input_खोलो_device().
 *
 * This function is supposed to be called from handler's
 * connect() method.
 */
पूर्णांक input_रेजिस्टर_handle(काष्ठा input_handle *handle)
अणु
	काष्ठा input_handler *handler = handle->handler;
	काष्ठा input_dev *dev = handle->dev;
	पूर्णांक error;

	/*
	 * We take dev->mutex here to prevent race with
	 * input_release_device().
	 */
	error = mutex_lock_पूर्णांकerruptible(&dev->mutex);
	अगर (error)
		वापस error;

	/*
	 * Filters go to the head of the list, normal handlers
	 * to the tail.
	 */
	अगर (handler->filter)
		list_add_rcu(&handle->d_node, &dev->h_list);
	अन्यथा
		list_add_tail_rcu(&handle->d_node, &dev->h_list);

	mutex_unlock(&dev->mutex);

	/*
	 * Since we are supposed to be called from ->connect()
	 * which is mutually exclusive with ->disconnect()
	 * we can't be racing with input_unरेजिस्टर_handle()
	 * and so separate lock is not needed here.
	 */
	list_add_tail_rcu(&handle->h_node, &handler->h_list);

	अगर (handler->start)
		handler->start(handle);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(input_रेजिस्टर_handle);

/**
 * input_unरेजिस्टर_handle - unरेजिस्टर an input handle
 * @handle: handle to unरेजिस्टर
 *
 * This function हटाओs input handle from device's
 * and handler's lists.
 *
 * This function is supposed to be called from handler's
 * disconnect() method.
 */
व्योम input_unरेजिस्टर_handle(काष्ठा input_handle *handle)
अणु
	काष्ठा input_dev *dev = handle->dev;

	list_del_rcu(&handle->h_node);

	/*
	 * Take dev->mutex to prevent race with input_release_device().
	 */
	mutex_lock(&dev->mutex);
	list_del_rcu(&handle->d_node);
	mutex_unlock(&dev->mutex);

	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL(input_unरेजिस्टर_handle);

/**
 * input_get_new_minor - allocates a new input minor number
 * @legacy_base: beginning or the legacy range to be searched
 * @legacy_num: size of legacy range
 * @allow_dynamic: whether we can also take ID from the dynamic range
 *
 * This function allocates a new device minor क्रम from input major namespace.
 * Caller can request legacy minor by specअगरying @legacy_base and @legacy_num
 * parameters and whether ID can be allocated from dynamic range अगर there are
 * no मुक्त IDs in legacy range.
 */
पूर्णांक input_get_new_minor(पूर्णांक legacy_base, अचिन्हित पूर्णांक legacy_num,
			bool allow_dynamic)
अणु
	/*
	 * This function should be called from input handler's ->connect()
	 * methods, which are serialized with input_mutex, so no additional
	 * locking is needed here.
	 */
	अगर (legacy_base >= 0) अणु
		पूर्णांक minor = ida_simple_get(&input_ida,
					   legacy_base,
					   legacy_base + legacy_num,
					   GFP_KERNEL);
		अगर (minor >= 0 || !allow_dynamic)
			वापस minor;
	पूर्ण

	वापस ida_simple_get(&input_ida,
			      INPUT_FIRST_DYNAMIC_DEV, INPUT_MAX_CHAR_DEVICES,
			      GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(input_get_new_minor);

/**
 * input_मुक्त_minor - release previously allocated minor
 * @minor: minor to be released
 *
 * This function releases previously allocated input minor so that it can be
 * reused later.
 */
व्योम input_मुक्त_minor(अचिन्हित पूर्णांक minor)
अणु
	ida_simple_हटाओ(&input_ida, minor);
पूर्ण
EXPORT_SYMBOL(input_मुक्त_minor);

अटल पूर्णांक __init input_init(व्योम)
अणु
	पूर्णांक err;

	err = class_रेजिस्टर(&input_class);
	अगर (err) अणु
		pr_err("unable to register input_dev class\n");
		वापस err;
	पूर्ण

	err = input_proc_init();
	अगर (err)
		जाओ fail1;

	err = रेजिस्टर_chrdev_region(MKDEV(INPUT_MAJOR, 0),
				     INPUT_MAX_CHAR_DEVICES, "input");
	अगर (err) अणु
		pr_err("unable to register char major %d", INPUT_MAJOR);
		जाओ fail2;
	पूर्ण

	वापस 0;

 fail2:	input_proc_निकास();
 fail1:	class_unरेजिस्टर(&input_class);
	वापस err;
पूर्ण

अटल व्योम __निकास input_निकास(व्योम)
अणु
	input_proc_निकास();
	unरेजिस्टर_chrdev_region(MKDEV(INPUT_MAJOR, 0),
				 INPUT_MAX_CHAR_DEVICES);
	class_unरेजिस्टर(&input_class);
पूर्ण

subsys_initcall(input_init);
module_निकास(input_निकास);
