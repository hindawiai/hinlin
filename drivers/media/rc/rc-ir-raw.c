<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// rc-ir-raw.c - handle IR pulse/space events
//
// Copyright (C) 2010 by Mauro Carvalho Chehab

#समावेश <linux/export.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kmod.h>
#समावेश <linux/sched.h>
#समावेश "rc-core-priv.h"

/* Used to keep track of IR raw clients, रक्षित by ir_raw_handler_lock */
अटल LIST_HEAD(ir_raw_client_list);

/* Used to handle IR raw handler extensions */
DEFINE_MUTEX(ir_raw_handler_lock);
अटल LIST_HEAD(ir_raw_handler_list);
अटल atomic64_t available_protocols = ATOMIC64_INIT(0);

अटल पूर्णांक ir_raw_event_thपढ़ो(व्योम *data)
अणु
	काष्ठा ir_raw_event ev;
	काष्ठा ir_raw_handler *handler;
	काष्ठा ir_raw_event_ctrl *raw = data;
	काष्ठा rc_dev *dev = raw->dev;

	जबतक (1) अणु
		mutex_lock(&ir_raw_handler_lock);
		जबतक (kfअगरo_out(&raw->kfअगरo, &ev, 1)) अणु
			अगर (is_timing_event(ev)) अणु
				अगर (ev.duration == 0)
					dev_warn_once(&dev->dev, "nonsensical timing event of duration 0");
				अगर (is_timing_event(raw->prev_ev) &&
				    !is_transition(&ev, &raw->prev_ev))
					dev_warn_once(&dev->dev, "two consecutive events of type %s",
						      TO_STR(ev.pulse));
				अगर (raw->prev_ev.reset && ev.pulse == 0)
					dev_warn_once(&dev->dev, "timing event after reset should be pulse");
			पूर्ण
			list_क्रम_each_entry(handler, &ir_raw_handler_list, list)
				अगर (dev->enabled_protocols &
				    handler->protocols || !handler->protocols)
					handler->decode(dev, ev);
			lirc_raw_event(dev, ev);
			raw->prev_ev = ev;
		पूर्ण
		mutex_unlock(&ir_raw_handler_lock);

		set_current_state(TASK_INTERRUPTIBLE);

		अगर (kthपढ़ो_should_stop()) अणु
			__set_current_state(TASK_RUNNING);
			अवरोध;
		पूर्ण अन्यथा अगर (!kfअगरo_is_empty(&raw->kfअगरo))
			set_current_state(TASK_RUNNING);

		schedule();
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ir_raw_event_store() - pass a pulse/space duration to the raw ir decoders
 * @dev:	the काष्ठा rc_dev device descriptor
 * @ev:		the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This routine (which may be called from an पूर्णांकerrupt context) stores a
 * pulse/space duration क्रम the raw ir decoding state machines. Pulses are
 * संकेतled as positive values and spaces as negative values. A zero value
 * will reset the decoding state machines.
 */
पूर्णांक ir_raw_event_store(काष्ठा rc_dev *dev, काष्ठा ir_raw_event *ev)
अणु
	अगर (!dev->raw)
		वापस -EINVAL;

	dev_dbg(&dev->dev, "sample: (%05dus %s)\n",
		ev->duration, TO_STR(ev->pulse));

	अगर (!kfअगरo_put(&dev->raw->kfअगरo, *ev)) अणु
		dev_err(&dev->dev, "IR event FIFO is full!\n");
		वापस -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ir_raw_event_store);

/**
 * ir_raw_event_store_edge() - notअगरy raw ir decoders of the start of a pulse/space
 * @dev:	the काष्ठा rc_dev device descriptor
 * @pulse:	true क्रम pulse, false क्रम space
 *
 * This routine (which may be called from an पूर्णांकerrupt context) is used to
 * store the beginning of an ir pulse or space (or the start/end of ir
 * reception) क्रम the raw ir decoding state machines. This is used by
 * hardware which करोes not provide durations directly but only पूर्णांकerrupts
 * (or similar events) on state change.
 */
पूर्णांक ir_raw_event_store_edge(काष्ठा rc_dev *dev, bool pulse)
अणु
	kसमय_प्रकार			now;
	काष्ठा ir_raw_event	ev = अणुपूर्ण;

	अगर (!dev->raw)
		वापस -EINVAL;

	now = kसमय_get();
	ev.duration = kसमय_प्रकारo_us(kसमय_sub(now, dev->raw->last_event));
	ev.pulse = !pulse;

	वापस ir_raw_event_store_with_समयout(dev, &ev);
पूर्ण
EXPORT_SYMBOL_GPL(ir_raw_event_store_edge);

/*
 * ir_raw_event_store_with_समयout() - pass a pulse/space duration to the raw
 *				       ir decoders, schedule decoding and
 *				       समयout
 * @dev:	the काष्ठा rc_dev device descriptor
 * @ev:		the काष्ठा ir_raw_event descriptor of the pulse/space
 *
 * This routine (which may be called from an पूर्णांकerrupt context) stores a
 * pulse/space duration क्रम the raw ir decoding state machines, schedules
 * decoding and generates a समयout.
 */
पूर्णांक ir_raw_event_store_with_समयout(काष्ठा rc_dev *dev, काष्ठा ir_raw_event *ev)
अणु
	kसमय_प्रकार		now;
	पूर्णांक		rc = 0;

	अगर (!dev->raw)
		वापस -EINVAL;

	now = kसमय_get();

	spin_lock(&dev->raw->edge_spinlock);
	rc = ir_raw_event_store(dev, ev);

	dev->raw->last_event = now;

	/* समयr could be set to समयout (125ms by शेष) */
	अगर (!समयr_pending(&dev->raw->edge_handle) ||
	    समय_after(dev->raw->edge_handle.expires,
		       jअगरfies + msecs_to_jअगरfies(15))) अणु
		mod_समयr(&dev->raw->edge_handle,
			  jअगरfies + msecs_to_jअगरfies(15));
	पूर्ण
	spin_unlock(&dev->raw->edge_spinlock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ir_raw_event_store_with_समयout);

/**
 * ir_raw_event_store_with_filter() - pass next pulse/space to decoders with some processing
 * @dev:	the काष्ठा rc_dev device descriptor
 * @ev:		the event that has occurred
 *
 * This routine (which may be called from an पूर्णांकerrupt context) works
 * in similar manner to ir_raw_event_store_edge.
 * This routine is पूर्णांकended क्रम devices with limited पूर्णांकernal buffer
 * It स्वतःmerges samples of same type, and handles समयouts. Returns non-zero
 * अगर the event was added, and zero अगर the event was ignored due to idle
 * processing.
 */
पूर्णांक ir_raw_event_store_with_filter(काष्ठा rc_dev *dev, काष्ठा ir_raw_event *ev)
अणु
	अगर (!dev->raw)
		वापस -EINVAL;

	/* Ignore spaces in idle mode */
	अगर (dev->idle && !ev->pulse)
		वापस 0;
	अन्यथा अगर (dev->idle)
		ir_raw_event_set_idle(dev, false);

	अगर (!dev->raw->this_ev.duration)
		dev->raw->this_ev = *ev;
	अन्यथा अगर (ev->pulse == dev->raw->this_ev.pulse)
		dev->raw->this_ev.duration += ev->duration;
	अन्यथा अणु
		ir_raw_event_store(dev, &dev->raw->this_ev);
		dev->raw->this_ev = *ev;
	पूर्ण

	/* Enter idle mode अगर necessary */
	अगर (!ev->pulse && dev->समयout &&
	    dev->raw->this_ev.duration >= dev->समयout)
		ir_raw_event_set_idle(dev, true);

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(ir_raw_event_store_with_filter);

/**
 * ir_raw_event_set_idle() - provide hपूर्णांक to rc-core when the device is idle or not
 * @dev:	the काष्ठा rc_dev device descriptor
 * @idle:	whether the device is idle or not
 */
व्योम ir_raw_event_set_idle(काष्ठा rc_dev *dev, bool idle)
अणु
	अगर (!dev->raw)
		वापस;

	dev_dbg(&dev->dev, "%s idle mode\n", idle ? "enter" : "leave");

	अगर (idle) अणु
		dev->raw->this_ev.समयout = true;
		ir_raw_event_store(dev, &dev->raw->this_ev);
		dev->raw->this_ev = (काष्ठा ir_raw_event) अणुपूर्ण;
	पूर्ण

	अगर (dev->s_idle)
		dev->s_idle(dev, idle);

	dev->idle = idle;
पूर्ण
EXPORT_SYMBOL_GPL(ir_raw_event_set_idle);

/**
 * ir_raw_event_handle() - schedules the decoding of stored ir data
 * @dev:	the काष्ठा rc_dev device descriptor
 *
 * This routine will tell rc-core to start decoding stored ir data.
 */
व्योम ir_raw_event_handle(काष्ठा rc_dev *dev)
अणु
	अगर (!dev->raw || !dev->raw->thपढ़ो)
		वापस;

	wake_up_process(dev->raw->thपढ़ो);
पूर्ण
EXPORT_SYMBOL_GPL(ir_raw_event_handle);

/* used पूर्णांकernally by the sysfs पूर्णांकerface */
u64
ir_raw_get_allowed_protocols(व्योम)
अणु
	वापस atomic64_पढ़ो(&available_protocols);
पूर्ण

अटल पूर्णांक change_protocol(काष्ठा rc_dev *dev, u64 *rc_proto)
अणु
	काष्ठा ir_raw_handler *handler;
	u32 समयout = 0;

	mutex_lock(&ir_raw_handler_lock);
	list_क्रम_each_entry(handler, &ir_raw_handler_list, list) अणु
		अगर (!(dev->enabled_protocols & handler->protocols) &&
		    (*rc_proto & handler->protocols) && handler->raw_रेजिस्टर)
			handler->raw_रेजिस्टर(dev);

		अगर ((dev->enabled_protocols & handler->protocols) &&
		    !(*rc_proto & handler->protocols) &&
		    handler->raw_unरेजिस्टर)
			handler->raw_unरेजिस्टर(dev);
	पूर्ण
	mutex_unlock(&ir_raw_handler_lock);

	अगर (!dev->max_समयout)
		वापस 0;

	mutex_lock(&ir_raw_handler_lock);
	list_क्रम_each_entry(handler, &ir_raw_handler_list, list) अणु
		अगर (handler->protocols & *rc_proto) अणु
			अगर (समयout < handler->min_समयout)
				समयout = handler->min_समयout;
		पूर्ण
	पूर्ण
	mutex_unlock(&ir_raw_handler_lock);

	अगर (समयout == 0)
		समयout = IR_DEFAULT_TIMEOUT;
	अन्यथा
		समयout += MS_TO_US(10);

	अगर (समयout < dev->min_समयout)
		समयout = dev->min_समयout;
	अन्यथा अगर (समयout > dev->max_समयout)
		समयout = dev->max_समयout;

	अगर (dev->s_समयout)
		dev->s_समयout(dev, समयout);
	अन्यथा
		dev->समयout = समयout;

	वापस 0;
पूर्ण

अटल व्योम ir_raw_disable_protocols(काष्ठा rc_dev *dev, u64 protocols)
अणु
	mutex_lock(&dev->lock);
	dev->enabled_protocols &= ~protocols;
	mutex_unlock(&dev->lock);
पूर्ण

/**
 * ir_raw_gen_manchester() - Encode data with Manchester (bi-phase) modulation.
 * @ev:		Poपूर्णांकer to poपूर्णांकer to next मुक्त event. *@ev is incremented क्रम
 *		each raw event filled.
 * @max:	Maximum number of raw events to fill.
 * @timings:	Manchester modulation timings.
 * @n:		Number of bits of data.
 * @data:	Data bits to encode.
 *
 * Encodes the @n least signअगरicant bits of @data using Manchester (bi-phase)
 * modulation with the timing अक्षरacteristics described by @timings, writing up
 * to @max raw IR events using the *@ev poपूर्णांकer.
 *
 * Returns:	0 on success.
 *		-ENOBUFS अगर there isn't enough space in the array to fit the
 *		full encoded data. In this हाल all @max events will have been
 *		written.
 */
पूर्णांक ir_raw_gen_manchester(काष्ठा ir_raw_event **ev, अचिन्हित पूर्णांक max,
			  स्थिर काष्ठा ir_raw_timings_manchester *timings,
			  अचिन्हित पूर्णांक n, u64 data)
अणु
	bool need_pulse;
	u64 i;
	पूर्णांक ret = -ENOBUFS;

	i = BIT_ULL(n - 1);

	अगर (timings->leader_pulse) अणु
		अगर (!max--)
			वापस ret;
		init_ir_raw_event_duration((*ev), 1, timings->leader_pulse);
		अगर (timings->leader_space) अणु
			अगर (!max--)
				वापस ret;
			init_ir_raw_event_duration(++(*ev), 0,
						   timings->leader_space);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* जारी existing संकेत */
		--(*ev);
	पूर्ण
	/* from here on *ev will poपूर्णांक to the last event rather than the next */

	जबतक (n && i > 0) अणु
		need_pulse = !(data & i);
		अगर (timings->invert)
			need_pulse = !need_pulse;
		अगर (need_pulse == !!(*ev)->pulse) अणु
			(*ev)->duration += timings->घड़ी;
		पूर्ण अन्यथा अणु
			अगर (!max--)
				जाओ nobufs;
			init_ir_raw_event_duration(++(*ev), need_pulse,
						   timings->घड़ी);
		पूर्ण

		अगर (!max--)
			जाओ nobufs;
		init_ir_raw_event_duration(++(*ev), !need_pulse,
					   timings->घड़ी);
		i >>= 1;
	पूर्ण

	अगर (timings->trailer_space) अणु
		अगर (!(*ev)->pulse)
			(*ev)->duration += timings->trailer_space;
		अन्यथा अगर (!max--)
			जाओ nobufs;
		अन्यथा
			init_ir_raw_event_duration(++(*ev), 0,
						   timings->trailer_space);
	पूर्ण

	ret = 0;
nobufs:
	/* poपूर्णांक to the next event rather than last event beक्रमe वापसing */
	++(*ev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ir_raw_gen_manchester);

/**
 * ir_raw_gen_pd() - Encode data to raw events with pulse-distance modulation.
 * @ev:		Poपूर्णांकer to poपूर्णांकer to next मुक्त event. *@ev is incremented क्रम
 *		each raw event filled.
 * @max:	Maximum number of raw events to fill.
 * @timings:	Pulse distance modulation timings.
 * @n:		Number of bits of data.
 * @data:	Data bits to encode.
 *
 * Encodes the @n least signअगरicant bits of @data using pulse-distance
 * modulation with the timing अक्षरacteristics described by @timings, writing up
 * to @max raw IR events using the *@ev poपूर्णांकer.
 *
 * Returns:	0 on success.
 *		-ENOBUFS अगर there isn't enough space in the array to fit the
 *		full encoded data. In this हाल all @max events will have been
 *		written.
 */
पूर्णांक ir_raw_gen_pd(काष्ठा ir_raw_event **ev, अचिन्हित पूर्णांक max,
		  स्थिर काष्ठा ir_raw_timings_pd *timings,
		  अचिन्हित पूर्णांक n, u64 data)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	अचिन्हित पूर्णांक space;

	अगर (timings->header_pulse) अणु
		ret = ir_raw_gen_pulse_space(ev, &max, timings->header_pulse,
					     timings->header_space);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (timings->msb_first) अणु
		क्रम (i = n - 1; i >= 0; --i) अणु
			space = timings->bit_space[(data >> i) & 1];
			ret = ir_raw_gen_pulse_space(ev, &max,
						     timings->bit_pulse,
						     space);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < n; ++i, data >>= 1) अणु
			space = timings->bit_space[data & 1];
			ret = ir_raw_gen_pulse_space(ev, &max,
						     timings->bit_pulse,
						     space);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	ret = ir_raw_gen_pulse_space(ev, &max, timings->trailer_pulse,
				     timings->trailer_space);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ir_raw_gen_pd);

/**
 * ir_raw_gen_pl() - Encode data to raw events with pulse-length modulation.
 * @ev:		Poपूर्णांकer to poपूर्णांकer to next मुक्त event. *@ev is incremented क्रम
 *		each raw event filled.
 * @max:	Maximum number of raw events to fill.
 * @timings:	Pulse distance modulation timings.
 * @n:		Number of bits of data.
 * @data:	Data bits to encode.
 *
 * Encodes the @n least signअगरicant bits of @data using space-distance
 * modulation with the timing अक्षरacteristics described by @timings, writing up
 * to @max raw IR events using the *@ev poपूर्णांकer.
 *
 * Returns:	0 on success.
 *		-ENOBUFS अगर there isn't enough space in the array to fit the
 *		full encoded data. In this हाल all @max events will have been
 *		written.
 */
पूर्णांक ir_raw_gen_pl(काष्ठा ir_raw_event **ev, अचिन्हित पूर्णांक max,
		  स्थिर काष्ठा ir_raw_timings_pl *timings,
		  अचिन्हित पूर्णांक n, u64 data)
अणु
	पूर्णांक i;
	पूर्णांक ret = -ENOBUFS;
	अचिन्हित पूर्णांक pulse;

	अगर (!max--)
		वापस ret;

	init_ir_raw_event_duration((*ev)++, 1, timings->header_pulse);

	अगर (timings->msb_first) अणु
		क्रम (i = n - 1; i >= 0; --i) अणु
			अगर (!max--)
				वापस ret;
			init_ir_raw_event_duration((*ev)++, 0,
						   timings->bit_space);
			अगर (!max--)
				वापस ret;
			pulse = timings->bit_pulse[(data >> i) & 1];
			init_ir_raw_event_duration((*ev)++, 1, pulse);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < n; ++i, data >>= 1) अणु
			अगर (!max--)
				वापस ret;
			init_ir_raw_event_duration((*ev)++, 0,
						   timings->bit_space);
			अगर (!max--)
				वापस ret;
			pulse = timings->bit_pulse[data & 1];
			init_ir_raw_event_duration((*ev)++, 1, pulse);
		पूर्ण
	पूर्ण

	अगर (!max--)
		वापस ret;

	init_ir_raw_event_duration((*ev)++, 0, timings->trailer_space);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ir_raw_gen_pl);

/**
 * ir_raw_encode_scancode() - Encode a scancode as raw events
 *
 * @protocol:		protocol
 * @scancode:		scancode filter describing a single scancode
 * @events:		array of raw events to ग_लिखो पूर्णांकo
 * @max:		max number of raw events
 *
 * Attempts to encode the scancode as raw events.
 *
 * Returns:	The number of events written.
 *		-ENOBUFS अगर there isn't enough space in the array to fit the
 *		encoding. In this हाल all @max events will have been written.
 *		-EINVAL अगर the scancode is ambiguous or invalid, or अगर no
 *		compatible encoder was found.
 */
पूर्णांक ir_raw_encode_scancode(क्रमागत rc_proto protocol, u32 scancode,
			   काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max)
अणु
	काष्ठा ir_raw_handler *handler;
	पूर्णांक ret = -EINVAL;
	u64 mask = 1ULL << protocol;

	ir_raw_load_modules(&mask);

	mutex_lock(&ir_raw_handler_lock);
	list_क्रम_each_entry(handler, &ir_raw_handler_list, list) अणु
		अगर (handler->protocols & mask && handler->encode) अणु
			ret = handler->encode(protocol, scancode, events, max);
			अगर (ret >= 0 || ret == -ENOBUFS)
				अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ir_raw_handler_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ir_raw_encode_scancode);

/**
 * ir_raw_edge_handle() - Handle ir_raw_event_store_edge() processing
 *
 * @t:		समयr_list
 *
 * This callback is armed by ir_raw_event_store_edge(). It करोes two things:
 * first of all, rather than calling ir_raw_event_handle() क्रम each
 * edge and waking up the rc thपढ़ो, 15 ms after the first edge
 * ir_raw_event_handle() is called. Secondly, generate a समयout event
 * no more IR is received after the rc_dev समयout.
 */
अटल व्योम ir_raw_edge_handle(काष्ठा समयr_list *t)
अणु
	काष्ठा ir_raw_event_ctrl *raw = from_समयr(raw, t, edge_handle);
	काष्ठा rc_dev *dev = raw->dev;
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार पूर्णांकerval;

	spin_lock_irqsave(&dev->raw->edge_spinlock, flags);
	पूर्णांकerval = kसमय_sub(kसमय_get(), dev->raw->last_event);
	अगर (kसमय_प्रकारo_us(पूर्णांकerval) >= dev->समयout) अणु
		काष्ठा ir_raw_event ev = अणु
			.समयout = true,
			.duration = kसमय_प्रकारo_us(पूर्णांकerval)
		पूर्ण;

		ir_raw_event_store(dev, &ev);
	पूर्ण अन्यथा अणु
		mod_समयr(&dev->raw->edge_handle,
			  jअगरfies + usecs_to_jअगरfies(dev->समयout -
						     kसमय_प्रकारo_us(पूर्णांकerval)));
	पूर्ण
	spin_unlock_irqrestore(&dev->raw->edge_spinlock, flags);

	ir_raw_event_handle(dev);
पूर्ण

/**
 * ir_raw_encode_carrier() - Get carrier used क्रम protocol
 *
 * @protocol:		protocol
 *
 * Attempts to find the carrier क्रम the specअगरied protocol
 *
 * Returns:	The carrier in Hz
 *		-EINVAL अगर the protocol is invalid, or अगर no
 *		compatible encoder was found.
 */
पूर्णांक ir_raw_encode_carrier(क्रमागत rc_proto protocol)
अणु
	काष्ठा ir_raw_handler *handler;
	पूर्णांक ret = -EINVAL;
	u64 mask = BIT_ULL(protocol);

	mutex_lock(&ir_raw_handler_lock);
	list_क्रम_each_entry(handler, &ir_raw_handler_list, list) अणु
		अगर (handler->protocols & mask && handler->encode) अणु
			ret = handler->carrier;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ir_raw_handler_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ir_raw_encode_carrier);

/*
 * Used to (un)रेजिस्टर raw event clients
 */
पूर्णांक ir_raw_event_prepare(काष्ठा rc_dev *dev)
अणु
	अगर (!dev)
		वापस -EINVAL;

	dev->raw = kzalloc(माप(*dev->raw), GFP_KERNEL);
	अगर (!dev->raw)
		वापस -ENOMEM;

	dev->raw->dev = dev;
	dev->change_protocol = change_protocol;
	dev->idle = true;
	spin_lock_init(&dev->raw->edge_spinlock);
	समयr_setup(&dev->raw->edge_handle, ir_raw_edge_handle, 0);
	INIT_KFIFO(dev->raw->kfअगरo);

	वापस 0;
पूर्ण

पूर्णांक ir_raw_event_रेजिस्टर(काष्ठा rc_dev *dev)
अणु
	काष्ठा task_काष्ठा *thपढ़ो;

	thपढ़ो = kthपढ़ो_run(ir_raw_event_thपढ़ो, dev->raw, "rc%u", dev->minor);
	अगर (IS_ERR(thपढ़ो))
		वापस PTR_ERR(thपढ़ो);

	dev->raw->thपढ़ो = thपढ़ो;

	mutex_lock(&ir_raw_handler_lock);
	list_add_tail(&dev->raw->list, &ir_raw_client_list);
	mutex_unlock(&ir_raw_handler_lock);

	वापस 0;
पूर्ण

व्योम ir_raw_event_मुक्त(काष्ठा rc_dev *dev)
अणु
	अगर (!dev)
		वापस;

	kमुक्त(dev->raw);
	dev->raw = शून्य;
पूर्ण

व्योम ir_raw_event_unरेजिस्टर(काष्ठा rc_dev *dev)
अणु
	काष्ठा ir_raw_handler *handler;

	अगर (!dev || !dev->raw)
		वापस;

	kthपढ़ो_stop(dev->raw->thपढ़ो);
	del_समयr_sync(&dev->raw->edge_handle);

	mutex_lock(&ir_raw_handler_lock);
	list_del(&dev->raw->list);
	list_क्रम_each_entry(handler, &ir_raw_handler_list, list)
		अगर (handler->raw_unरेजिस्टर &&
		    (handler->protocols & dev->enabled_protocols))
			handler->raw_unरेजिस्टर(dev);

	lirc_bpf_मुक्त(dev);

	ir_raw_event_मुक्त(dev);

	/*
	 * A user can be calling bpf(BPF_PROG_अणुQUERY|ATTACH|DETACHपूर्ण), so
	 * ensure that the raw member is null on unlock; this is how
	 * "device gone" is checked.
	 */
	mutex_unlock(&ir_raw_handler_lock);
पूर्ण

/*
 * Extension पूर्णांकerface - used to रेजिस्टर the IR decoders
 */

पूर्णांक ir_raw_handler_रेजिस्टर(काष्ठा ir_raw_handler *ir_raw_handler)
अणु
	mutex_lock(&ir_raw_handler_lock);
	list_add_tail(&ir_raw_handler->list, &ir_raw_handler_list);
	atomic64_or(ir_raw_handler->protocols, &available_protocols);
	mutex_unlock(&ir_raw_handler_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ir_raw_handler_रेजिस्टर);

व्योम ir_raw_handler_unरेजिस्टर(काष्ठा ir_raw_handler *ir_raw_handler)
अणु
	काष्ठा ir_raw_event_ctrl *raw;
	u64 protocols = ir_raw_handler->protocols;

	mutex_lock(&ir_raw_handler_lock);
	list_del(&ir_raw_handler->list);
	list_क्रम_each_entry(raw, &ir_raw_client_list, list) अणु
		अगर (ir_raw_handler->raw_unरेजिस्टर &&
		    (raw->dev->enabled_protocols & protocols))
			ir_raw_handler->raw_unरेजिस्टर(raw->dev);
		ir_raw_disable_protocols(raw->dev, protocols);
	पूर्ण
	atomic64_andnot(protocols, &available_protocols);
	mutex_unlock(&ir_raw_handler_lock);
पूर्ण
EXPORT_SYMBOL(ir_raw_handler_unरेजिस्टर);
