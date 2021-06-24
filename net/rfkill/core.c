<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006 - 2007 Ivo van Doorn
 * Copyright (C) 2007 Dmitry Torokhov
 * Copyright 2009 Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/capability.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/रुको.h>
#समावेश <linux/poll.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>

#समावेश "rfkill.h"

#घोषणा POLL_INTERVAL		(5 * HZ)

#घोषणा RFKILL_BLOCK_HW		BIT(0)
#घोषणा RFKILL_BLOCK_SW		BIT(1)
#घोषणा RFKILL_BLOCK_SW_PREV	BIT(2)
#घोषणा RFKILL_BLOCK_ANY	(RFKILL_BLOCK_HW |\
				 RFKILL_BLOCK_SW |\
				 RFKILL_BLOCK_SW_PREV)
#घोषणा RFKILL_BLOCK_SW_SETCALL	BIT(31)

काष्ठा rfसमाप्त अणु
	spinlock_t		lock;

	क्रमागत rfसमाप्त_type	type;

	अचिन्हित दीर्घ		state;
	अचिन्हित दीर्घ		hard_block_reasons;

	u32			idx;

	bool			रेजिस्टरed;
	bool			persistent;
	bool			polling_छोड़ोd;
	bool			suspended;

	स्थिर काष्ठा rfसमाप्त_ops	*ops;
	व्योम			*data;

#अगर_घोषित CONFIG_RFKILL_LEDS
	काष्ठा led_trigger	led_trigger;
	स्थिर अक्षर		*ledtrigname;
#पूर्ण_अगर

	काष्ठा device		dev;
	काष्ठा list_head	node;

	काष्ठा delayed_work	poll_work;
	काष्ठा work_काष्ठा	uevent_work;
	काष्ठा work_काष्ठा	sync_work;
	अक्षर			name[];
पूर्ण;
#घोषणा to_rfसमाप्त(d)	container_of(d, काष्ठा rfसमाप्त, dev)

काष्ठा rfसमाप्त_पूर्णांक_event अणु
	काष्ठा list_head	list;
	काष्ठा rfसमाप्त_event_ext	ev;
पूर्ण;

काष्ठा rfसमाप्त_data अणु
	काष्ठा list_head	list;
	काष्ठा list_head	events;
	काष्ठा mutex		mtx;
	रुको_queue_head_t	पढ़ो_रुको;
	bool			input_handler;
पूर्ण;


MODULE_AUTHOR("Ivo van Doorn <IvDoorn@gmail.com>");
MODULE_AUTHOR("Johannes Berg <johannes@sipsolutions.net>");
MODULE_DESCRIPTION("RF switch support");
MODULE_LICENSE("GPL");


/*
 * The locking here should be made much smarter, we currently have
 * a bit of a stupid situation because drivers might want to रेजिस्टर
 * the rfसमाप्त काष्ठा under their own lock, and take this lock during
 * rfसमाप्त method calls -- which will cause an AB-BA deadlock situation.
 *
 * To fix that, we need to rework this code here to be mostly lock-मुक्त
 * and only use the mutex क्रम list manipulations, not to protect the
 * various other global variables. Then we can aव्योम holding the mutex
 * around driver operations, and all is happy.
 */
अटल LIST_HEAD(rfसमाप्त_list);	/* list of रेजिस्टरed rf चयनes */
अटल DEFINE_MUTEX(rfसमाप्त_global_mutex);
अटल LIST_HEAD(rfसमाप्त_fds);	/* list of खोलो fds of /dev/rfसमाप्त */

अटल अचिन्हित पूर्णांक rfसमाप्त_शेष_state = 1;
module_param_named(शेष_state, rfसमाप्त_शेष_state, uपूर्णांक, 0444);
MODULE_PARM_DESC(शेष_state,
		 "Default initial state for all radio types, 0 = radio off");

अटल काष्ठा अणु
	bool cur, sav;
पूर्ण rfसमाप्त_global_states[NUM_RFKILL_TYPES];

अटल bool rfसमाप्त_epo_lock_active;


#अगर_घोषित CONFIG_RFKILL_LEDS
अटल व्योम rfसमाप्त_led_trigger_event(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	काष्ठा led_trigger *trigger;

	अगर (!rfसमाप्त->रेजिस्टरed)
		वापस;

	trigger = &rfसमाप्त->led_trigger;

	अगर (rfसमाप्त->state & RFKILL_BLOCK_ANY)
		led_trigger_event(trigger, LED_OFF);
	अन्यथा
		led_trigger_event(trigger, LED_FULL);
पूर्ण

अटल पूर्णांक rfसमाप्त_led_trigger_activate(काष्ठा led_classdev *led)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त;

	rfसमाप्त = container_of(led->trigger, काष्ठा rfसमाप्त, led_trigger);

	rfसमाप्त_led_trigger_event(rfसमाप्त);

	वापस 0;
पूर्ण

स्थिर अक्षर *rfसमाप्त_get_led_trigger_name(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	वापस rfसमाप्त->led_trigger.name;
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_get_led_trigger_name);

व्योम rfसमाप्त_set_led_trigger_name(काष्ठा rfसमाप्त *rfसमाप्त, स्थिर अक्षर *name)
अणु
	BUG_ON(!rfसमाप्त);

	rfसमाप्त->ledtrigname = name;
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_set_led_trigger_name);

अटल पूर्णांक rfसमाप्त_led_trigger_रेजिस्टर(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	rfसमाप्त->led_trigger.name = rfसमाप्त->ledtrigname
					? : dev_name(&rfसमाप्त->dev);
	rfसमाप्त->led_trigger.activate = rfसमाप्त_led_trigger_activate;
	वापस led_trigger_रेजिस्टर(&rfसमाप्त->led_trigger);
पूर्ण

अटल व्योम rfसमाप्त_led_trigger_unरेजिस्टर(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	led_trigger_unरेजिस्टर(&rfसमाप्त->led_trigger);
पूर्ण

अटल काष्ठा led_trigger rfसमाप्त_any_led_trigger;
अटल काष्ठा led_trigger rfसमाप्त_none_led_trigger;
अटल काष्ठा work_काष्ठा rfसमाप्त_global_led_trigger_work;

अटल व्योम rfसमाप्त_global_led_trigger_worker(काष्ठा work_काष्ठा *work)
अणु
	क्रमागत led_brightness brightness = LED_OFF;
	काष्ठा rfसमाप्त *rfसमाप्त;

	mutex_lock(&rfसमाप्त_global_mutex);
	list_क्रम_each_entry(rfसमाप्त, &rfसमाप्त_list, node) अणु
		अगर (!(rfसमाप्त->state & RFKILL_BLOCK_ANY)) अणु
			brightness = LED_FULL;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&rfसमाप्त_global_mutex);

	led_trigger_event(&rfसमाप्त_any_led_trigger, brightness);
	led_trigger_event(&rfसमाप्त_none_led_trigger,
			  brightness == LED_OFF ? LED_FULL : LED_OFF);
पूर्ण

अटल व्योम rfसमाप्त_global_led_trigger_event(व्योम)
अणु
	schedule_work(&rfसमाप्त_global_led_trigger_work);
पूर्ण

अटल पूर्णांक rfसमाप्त_global_led_trigger_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret;

	INIT_WORK(&rfसमाप्त_global_led_trigger_work,
			rfसमाप्त_global_led_trigger_worker);

	rfसमाप्त_any_led_trigger.name = "rfkill-any";
	ret = led_trigger_रेजिस्टर(&rfसमाप्त_any_led_trigger);
	अगर (ret)
		वापस ret;

	rfसमाप्त_none_led_trigger.name = "rfkill-none";
	ret = led_trigger_रेजिस्टर(&rfसमाप्त_none_led_trigger);
	अगर (ret)
		led_trigger_unरेजिस्टर(&rfसमाप्त_any_led_trigger);
	अन्यथा
		/* Delay activation until all global triggers are रेजिस्टरed */
		rfसमाप्त_global_led_trigger_event();

	वापस ret;
पूर्ण

अटल व्योम rfसमाप्त_global_led_trigger_unरेजिस्टर(व्योम)
अणु
	led_trigger_unरेजिस्टर(&rfसमाप्त_none_led_trigger);
	led_trigger_unरेजिस्टर(&rfसमाप्त_any_led_trigger);
	cancel_work_sync(&rfसमाप्त_global_led_trigger_work);
पूर्ण
#अन्यथा
अटल व्योम rfसमाप्त_led_trigger_event(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक rfसमाप्त_led_trigger_रेजिस्टर(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rfसमाप्त_led_trigger_unरेजिस्टर(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
पूर्ण

अटल व्योम rfसमाप्त_global_led_trigger_event(व्योम)
अणु
पूर्ण

अटल पूर्णांक rfसमाप्त_global_led_trigger_रेजिस्टर(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम rfसमाप्त_global_led_trigger_unरेजिस्टर(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_RFKILL_LEDS */

अटल व्योम rfसमाप्त_fill_event(काष्ठा rfसमाप्त_event_ext *ev,
			      काष्ठा rfसमाप्त *rfसमाप्त,
			      क्रमागत rfसमाप्त_operation op)
अणु
	अचिन्हित दीर्घ flags;

	ev->idx = rfसमाप्त->idx;
	ev->type = rfसमाप्त->type;
	ev->op = op;

	spin_lock_irqsave(&rfसमाप्त->lock, flags);
	ev->hard = !!(rfसमाप्त->state & RFKILL_BLOCK_HW);
	ev->soft = !!(rfसमाप्त->state & (RFKILL_BLOCK_SW |
					RFKILL_BLOCK_SW_PREV));
	ev->hard_block_reasons = rfसमाप्त->hard_block_reasons;
	spin_unlock_irqrestore(&rfसमाप्त->lock, flags);
पूर्ण

अटल व्योम rfसमाप्त_send_events(काष्ठा rfसमाप्त *rfसमाप्त, क्रमागत rfसमाप्त_operation op)
अणु
	काष्ठा rfसमाप्त_data *data;
	काष्ठा rfसमाप्त_पूर्णांक_event *ev;

	list_क्रम_each_entry(data, &rfसमाप्त_fds, list) अणु
		ev = kzalloc(माप(*ev), GFP_KERNEL);
		अगर (!ev)
			जारी;
		rfसमाप्त_fill_event(&ev->ev, rfसमाप्त, op);
		mutex_lock(&data->mtx);
		list_add_tail(&ev->list, &data->events);
		mutex_unlock(&data->mtx);
		wake_up_पूर्णांकerruptible(&data->पढ़ो_रुको);
	पूर्ण
पूर्ण

अटल व्योम rfसमाप्त_event(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	अगर (!rfसमाप्त->रेजिस्टरed)
		वापस;

	kobject_uevent(&rfसमाप्त->dev.kobj, KOBJ_CHANGE);

	/* also send event to /dev/rfसमाप्त */
	rfसमाप्त_send_events(rfसमाप्त, RFKILL_OP_CHANGE);
पूर्ण

/**
 * rfसमाप्त_set_block - wrapper क्रम set_block method
 *
 * @rfसमाप्त: the rfसमाप्त काष्ठा to use
 * @blocked: the new software state
 *
 * Calls the set_block method (when applicable) and handles notअगरications
 * etc. as well.
 */
अटल व्योम rfसमाप्त_set_block(काष्ठा rfसमाप्त *rfसमाप्त, bool blocked)
अणु
	अचिन्हित दीर्घ flags;
	bool prev, curr;
	पूर्णांक err;

	अगर (unlikely(rfसमाप्त->dev.घातer.घातer_state.event & PM_EVENT_SLEEP))
		वापस;

	/*
	 * Some platक्रमms (...!) generate input events which affect the
	 * _hard_ समाप्त state -- whenever something tries to change the
	 * current software state query the hardware state too.
	 */
	अगर (rfसमाप्त->ops->query)
		rfसमाप्त->ops->query(rfसमाप्त, rfसमाप्त->data);

	spin_lock_irqsave(&rfसमाप्त->lock, flags);
	prev = rfसमाप्त->state & RFKILL_BLOCK_SW;

	अगर (prev)
		rfसमाप्त->state |= RFKILL_BLOCK_SW_PREV;
	अन्यथा
		rfसमाप्त->state &= ~RFKILL_BLOCK_SW_PREV;

	अगर (blocked)
		rfसमाप्त->state |= RFKILL_BLOCK_SW;
	अन्यथा
		rfसमाप्त->state &= ~RFKILL_BLOCK_SW;

	rfसमाप्त->state |= RFKILL_BLOCK_SW_SETCALL;
	spin_unlock_irqrestore(&rfसमाप्त->lock, flags);

	err = rfसमाप्त->ops->set_block(rfसमाप्त->data, blocked);

	spin_lock_irqsave(&rfसमाप्त->lock, flags);
	अगर (err) अणु
		/*
		 * Failed -- reset status to _PREV, which may be dअगरferent
		 * from what we have set _PREV to earlier in this function
		 * अगर rfसमाप्त_set_sw_state was invoked.
		 */
		अगर (rfसमाप्त->state & RFKILL_BLOCK_SW_PREV)
			rfसमाप्त->state |= RFKILL_BLOCK_SW;
		अन्यथा
			rfसमाप्त->state &= ~RFKILL_BLOCK_SW;
	पूर्ण
	rfसमाप्त->state &= ~RFKILL_BLOCK_SW_SETCALL;
	rfसमाप्त->state &= ~RFKILL_BLOCK_SW_PREV;
	curr = rfसमाप्त->state & RFKILL_BLOCK_SW;
	spin_unlock_irqrestore(&rfसमाप्त->lock, flags);

	rfसमाप्त_led_trigger_event(rfसमाप्त);
	rfसमाप्त_global_led_trigger_event();

	अगर (prev != curr)
		rfसमाप्त_event(rfसमाप्त);
पूर्ण

अटल व्योम rfसमाप्त_update_global_state(क्रमागत rfसमाप्त_type type, bool blocked)
अणु
	पूर्णांक i;

	अगर (type != RFKILL_TYPE_ALL) अणु
		rfसमाप्त_global_states[type].cur = blocked;
		वापस;
	पूर्ण

	क्रम (i = 0; i < NUM_RFKILL_TYPES; i++)
		rfसमाप्त_global_states[i].cur = blocked;
पूर्ण

#अगर_घोषित CONFIG_RFKILL_INPUT
अटल atomic_t rfसमाप्त_input_disabled = ATOMIC_INIT(0);

/**
 * __rfसमाप्त_चयन_all - Toggle state of all चयनes of given type
 * @type: type of पूर्णांकerfaces to be affected
 * @blocked: the new state
 *
 * This function sets the state of all चयनes of given type,
 * unless a specअगरic चयन is suspended.
 *
 * Caller must have acquired rfसमाप्त_global_mutex.
 */
अटल व्योम __rfसमाप्त_चयन_all(स्थिर क्रमागत rfसमाप्त_type type, bool blocked)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त;

	rfसमाप्त_update_global_state(type, blocked);
	list_क्रम_each_entry(rfसमाप्त, &rfसमाप्त_list, node) अणु
		अगर (rfसमाप्त->type != type && type != RFKILL_TYPE_ALL)
			जारी;

		rfसमाप्त_set_block(rfसमाप्त, blocked);
	पूर्ण
पूर्ण

/**
 * rfसमाप्त_चयन_all - Toggle state of all चयनes of given type
 * @type: type of पूर्णांकerfaces to be affected
 * @blocked: the new state
 *
 * Acquires rfसमाप्त_global_mutex and calls __rfसमाप्त_चयन_all(@type, @state).
 * Please refer to __rfसमाप्त_चयन_all() क्रम details.
 *
 * Does nothing अगर the EPO lock is active.
 */
व्योम rfसमाप्त_चयन_all(क्रमागत rfसमाप्त_type type, bool blocked)
अणु
	अगर (atomic_पढ़ो(&rfसमाप्त_input_disabled))
		वापस;

	mutex_lock(&rfसमाप्त_global_mutex);

	अगर (!rfसमाप्त_epo_lock_active)
		__rfसमाप्त_चयन_all(type, blocked);

	mutex_unlock(&rfसमाप्त_global_mutex);
पूर्ण

/**
 * rfसमाप्त_epo - emergency घातer off all transmitters
 *
 * This kicks all non-suspended rfसमाप्त devices to RFKILL_STATE_SOFT_BLOCKED,
 * ignoring everything in its path but rfसमाप्त_global_mutex and rfसमाप्त->mutex.
 *
 * The global state beक्रमe the EPO is saved and can be restored later
 * using rfसमाप्त_restore_states().
 */
व्योम rfसमाप्त_epo(व्योम)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त;
	पूर्णांक i;

	अगर (atomic_पढ़ो(&rfसमाप्त_input_disabled))
		वापस;

	mutex_lock(&rfसमाप्त_global_mutex);

	rfसमाप्त_epo_lock_active = true;
	list_क्रम_each_entry(rfसमाप्त, &rfसमाप्त_list, node)
		rfसमाप्त_set_block(rfसमाप्त, true);

	क्रम (i = 0; i < NUM_RFKILL_TYPES; i++) अणु
		rfसमाप्त_global_states[i].sav = rfसमाप्त_global_states[i].cur;
		rfसमाप्त_global_states[i].cur = true;
	पूर्ण

	mutex_unlock(&rfसमाप्त_global_mutex);
पूर्ण

/**
 * rfसमाप्त_restore_states - restore global states
 *
 * Restore (and sync चयनes to) the global state from the
 * states in rfसमाप्त_शेष_states.  This can unकरो the effects of
 * a call to rfसमाप्त_epo().
 */
व्योम rfसमाप्त_restore_states(व्योम)
अणु
	पूर्णांक i;

	अगर (atomic_पढ़ो(&rfसमाप्त_input_disabled))
		वापस;

	mutex_lock(&rfसमाप्त_global_mutex);

	rfसमाप्त_epo_lock_active = false;
	क्रम (i = 0; i < NUM_RFKILL_TYPES; i++)
		__rfसमाप्त_चयन_all(i, rfसमाप्त_global_states[i].sav);
	mutex_unlock(&rfसमाप्त_global_mutex);
पूर्ण

/**
 * rfसमाप्त_हटाओ_epo_lock - unlock state changes
 *
 * Used by rfसमाप्त-input manually unlock state changes, when
 * the EPO चयन is deactivated.
 */
व्योम rfसमाप्त_हटाओ_epo_lock(व्योम)
अणु
	अगर (atomic_पढ़ो(&rfसमाप्त_input_disabled))
		वापस;

	mutex_lock(&rfसमाप्त_global_mutex);
	rfसमाप्त_epo_lock_active = false;
	mutex_unlock(&rfसमाप्त_global_mutex);
पूर्ण

/**
 * rfसमाप्त_is_epo_lock_active - वापसs true EPO is active
 *
 * Returns 0 (false) अगर there is NOT an active EPO condition,
 * and 1 (true) अगर there is an active EPO condition, which
 * locks all radios in one of the BLOCKED states.
 *
 * Can be called in atomic context.
 */
bool rfसमाप्त_is_epo_lock_active(व्योम)
अणु
	वापस rfसमाप्त_epo_lock_active;
पूर्ण

/**
 * rfसमाप्त_get_global_sw_state - वापसs global state क्रम a type
 * @type: the type to get the global state of
 *
 * Returns the current global state क्रम a given wireless
 * device type.
 */
bool rfसमाप्त_get_global_sw_state(स्थिर क्रमागत rfसमाप्त_type type)
अणु
	वापस rfसमाप्त_global_states[type].cur;
पूर्ण
#पूर्ण_अगर

bool rfसमाप्त_set_hw_state_reason(काष्ठा rfसमाप्त *rfसमाप्त,
				bool blocked, अचिन्हित दीर्घ reason)
अणु
	अचिन्हित दीर्घ flags;
	bool ret, prev;

	BUG_ON(!rfसमाप्त);

	अगर (WARN(reason &
	    ~(RFKILL_HARD_BLOCK_SIGNAL | RFKILL_HARD_BLOCK_NOT_OWNER),
	    "hw_state reason not supported: 0x%lx", reason))
		वापस blocked;

	spin_lock_irqsave(&rfसमाप्त->lock, flags);
	prev = !!(rfसमाप्त->hard_block_reasons & reason);
	अगर (blocked) अणु
		rfसमाप्त->state |= RFKILL_BLOCK_HW;
		rfसमाप्त->hard_block_reasons |= reason;
	पूर्ण अन्यथा अणु
		rfसमाप्त->hard_block_reasons &= ~reason;
		अगर (!rfसमाप्त->hard_block_reasons)
			rfसमाप्त->state &= ~RFKILL_BLOCK_HW;
	पूर्ण
	ret = !!(rfसमाप्त->state & RFKILL_BLOCK_ANY);
	spin_unlock_irqrestore(&rfसमाप्त->lock, flags);

	rfसमाप्त_led_trigger_event(rfसमाप्त);
	rfसमाप्त_global_led_trigger_event();

	अगर (rfसमाप्त->रेजिस्टरed && prev != blocked)
		schedule_work(&rfसमाप्त->uevent_work);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_set_hw_state_reason);

अटल व्योम __rfसमाप्त_set_sw_state(काष्ठा rfसमाप्त *rfसमाप्त, bool blocked)
अणु
	u32 bit = RFKILL_BLOCK_SW;

	/* अगर in a ops->set_block right now, use other bit */
	अगर (rfसमाप्त->state & RFKILL_BLOCK_SW_SETCALL)
		bit = RFKILL_BLOCK_SW_PREV;

	अगर (blocked)
		rfसमाप्त->state |= bit;
	अन्यथा
		rfसमाप्त->state &= ~bit;
पूर्ण

bool rfसमाप्त_set_sw_state(काष्ठा rfसमाप्त *rfसमाप्त, bool blocked)
अणु
	अचिन्हित दीर्घ flags;
	bool prev, hwblock;

	BUG_ON(!rfसमाप्त);

	spin_lock_irqsave(&rfसमाप्त->lock, flags);
	prev = !!(rfसमाप्त->state & RFKILL_BLOCK_SW);
	__rfसमाप्त_set_sw_state(rfसमाप्त, blocked);
	hwblock = !!(rfसमाप्त->state & RFKILL_BLOCK_HW);
	blocked = blocked || hwblock;
	spin_unlock_irqrestore(&rfसमाप्त->lock, flags);

	अगर (!rfसमाप्त->रेजिस्टरed)
		वापस blocked;

	अगर (prev != blocked && !hwblock)
		schedule_work(&rfसमाप्त->uevent_work);

	rfसमाप्त_led_trigger_event(rfसमाप्त);
	rfसमाप्त_global_led_trigger_event();

	वापस blocked;
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_set_sw_state);

व्योम rfसमाप्त_init_sw_state(काष्ठा rfसमाप्त *rfसमाप्त, bool blocked)
अणु
	अचिन्हित दीर्घ flags;

	BUG_ON(!rfसमाप्त);
	BUG_ON(rfसमाप्त->रेजिस्टरed);

	spin_lock_irqsave(&rfसमाप्त->lock, flags);
	__rfसमाप्त_set_sw_state(rfसमाप्त, blocked);
	rfसमाप्त->persistent = true;
	spin_unlock_irqrestore(&rfसमाप्त->lock, flags);
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_init_sw_state);

व्योम rfसमाप्त_set_states(काष्ठा rfसमाप्त *rfसमाप्त, bool sw, bool hw)
अणु
	अचिन्हित दीर्घ flags;
	bool swprev, hwprev;

	BUG_ON(!rfसमाप्त);

	spin_lock_irqsave(&rfसमाप्त->lock, flags);

	/*
	 * No need to care about prev/setblock ... this is क्रम uevent only
	 * and that will get triggered by rfसमाप्त_set_block anyway.
	 */
	swprev = !!(rfसमाप्त->state & RFKILL_BLOCK_SW);
	hwprev = !!(rfसमाप्त->state & RFKILL_BLOCK_HW);
	__rfसमाप्त_set_sw_state(rfसमाप्त, sw);
	अगर (hw)
		rfसमाप्त->state |= RFKILL_BLOCK_HW;
	अन्यथा
		rfसमाप्त->state &= ~RFKILL_BLOCK_HW;

	spin_unlock_irqrestore(&rfसमाप्त->lock, flags);

	अगर (!rfसमाप्त->रेजिस्टरed) अणु
		rfसमाप्त->persistent = true;
	पूर्ण अन्यथा अणु
		अगर (swprev != sw || hwprev != hw)
			schedule_work(&rfसमाप्त->uevent_work);

		rfसमाप्त_led_trigger_event(rfसमाप्त);
		rfसमाप्त_global_led_trigger_event();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_set_states);

अटल स्थिर अक्षर * स्थिर rfसमाप्त_types[] = अणु
	शून्य, /* RFKILL_TYPE_ALL */
	"wlan",
	"bluetooth",
	"ultrawideband",
	"wimax",
	"wwan",
	"gps",
	"fm",
	"nfc",
पूर्ण;

क्रमागत rfसमाप्त_type rfसमाप्त_find_type(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(rfसमाप्त_types) != NUM_RFKILL_TYPES);

	अगर (!name)
		वापस RFKILL_TYPE_ALL;

	क्रम (i = 1; i < NUM_RFKILL_TYPES; i++)
		अगर (!म_भेद(name, rfसमाप्त_types[i]))
			वापस i;
	वापस RFKILL_TYPE_ALL;
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_find_type);

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);

	वापस प्र_लिखो(buf, "%s\n", rfसमाप्त->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);

	वापस प्र_लिखो(buf, "%s\n", rfसमाप्त_types[rfसमाप्त->type]);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार index_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);

	वापस प्र_लिखो(buf, "%d\n", rfसमाप्त->idx);
पूर्ण
अटल DEVICE_ATTR_RO(index);

अटल sमाप_प्रकार persistent_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);

	वापस प्र_लिखो(buf, "%d\n", rfसमाप्त->persistent);
पूर्ण
अटल DEVICE_ATTR_RO(persistent);

अटल sमाप_प्रकार hard_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);

	वापस प्र_लिखो(buf, "%d\n", (rfसमाप्त->state & RFKILL_BLOCK_HW) ? 1 : 0 );
पूर्ण
अटल DEVICE_ATTR_RO(hard);

अटल sमाप_प्रकार soft_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);

	वापस प्र_लिखो(buf, "%d\n", (rfसमाप्त->state & RFKILL_BLOCK_SW) ? 1 : 0 );
पूर्ण

अटल sमाप_प्रकार soft_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);
	अचिन्हित दीर्घ state;
	पूर्णांक err;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	err = kम_से_अदीर्घ(buf, 0, &state);
	अगर (err)
		वापस err;

	अगर (state > 1 )
		वापस -EINVAL;

	mutex_lock(&rfसमाप्त_global_mutex);
	rfसमाप्त_set_block(rfसमाप्त, state);
	mutex_unlock(&rfसमाप्त_global_mutex);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(soft);

अटल sमाप_प्रकार hard_block_reasons_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);

	वापस प्र_लिखो(buf, "0x%lx\n", rfसमाप्त->hard_block_reasons);
पूर्ण
अटल DEVICE_ATTR_RO(hard_block_reasons);

अटल u8 user_state_from_blocked(अचिन्हित दीर्घ state)
अणु
	अगर (state & RFKILL_BLOCK_HW)
		वापस RFKILL_USER_STATE_HARD_BLOCKED;
	अगर (state & RFKILL_BLOCK_SW)
		वापस RFKILL_USER_STATE_SOFT_BLOCKED;

	वापस RFKILL_USER_STATE_UNBLOCKED;
पूर्ण

अटल sमाप_प्रकार state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);

	वापस प्र_लिखो(buf, "%d\n", user_state_from_blocked(rfसमाप्त->state));
पूर्ण

अटल sमाप_प्रकार state_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);
	अचिन्हित दीर्घ state;
	पूर्णांक err;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	err = kम_से_अदीर्घ(buf, 0, &state);
	अगर (err)
		वापस err;

	अगर (state != RFKILL_USER_STATE_SOFT_BLOCKED &&
	    state != RFKILL_USER_STATE_UNBLOCKED)
		वापस -EINVAL;

	mutex_lock(&rfसमाप्त_global_mutex);
	rfसमाप्त_set_block(rfसमाप्त, state == RFKILL_USER_STATE_SOFT_BLOCKED);
	mutex_unlock(&rfसमाप्त_global_mutex);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(state);

अटल काष्ठा attribute *rfसमाप्त_dev_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_type.attr,
	&dev_attr_index.attr,
	&dev_attr_persistent.attr,
	&dev_attr_state.attr,
	&dev_attr_soft.attr,
	&dev_attr_hard.attr,
	&dev_attr_hard_block_reasons.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(rfसमाप्त_dev);

अटल व्योम rfसमाप्त_release(काष्ठा device *dev)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);

	kमुक्त(rfसमाप्त);
पूर्ण

अटल पूर्णांक rfसमाप्त_dev_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ reasons;
	u32 state;
	पूर्णांक error;

	error = add_uevent_var(env, "RFKILL_NAME=%s", rfसमाप्त->name);
	अगर (error)
		वापस error;
	error = add_uevent_var(env, "RFKILL_TYPE=%s",
			       rfसमाप्त_types[rfसमाप्त->type]);
	अगर (error)
		वापस error;
	spin_lock_irqsave(&rfसमाप्त->lock, flags);
	state = rfसमाप्त->state;
	reasons = rfसमाप्त->hard_block_reasons;
	spin_unlock_irqrestore(&rfसमाप्त->lock, flags);
	error = add_uevent_var(env, "RFKILL_STATE=%d",
			       user_state_from_blocked(state));
	अगर (error)
		वापस error;
	वापस add_uevent_var(env, "RFKILL_HW_BLOCK_REASON=0x%lx", reasons);
पूर्ण

व्योम rfसमाप्त_छोड़ो_polling(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	BUG_ON(!rfसमाप्त);

	अगर (!rfसमाप्त->ops->poll)
		वापस;

	rfसमाप्त->polling_छोड़ोd = true;
	cancel_delayed_work_sync(&rfसमाप्त->poll_work);
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_छोड़ो_polling);

व्योम rfसमाप्त_resume_polling(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	BUG_ON(!rfसमाप्त);

	अगर (!rfसमाप्त->ops->poll)
		वापस;

	rfसमाप्त->polling_छोड़ोd = false;

	अगर (rfसमाप्त->suspended)
		वापस;

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &rfसमाप्त->poll_work, 0);
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_resume_polling);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rfसमाप्त_suspend(काष्ठा device *dev)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);

	rfसमाप्त->suspended = true;
	cancel_delayed_work_sync(&rfसमाप्त->poll_work);

	वापस 0;
पूर्ण

अटल पूर्णांक rfसमाप्त_resume(काष्ठा device *dev)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त = to_rfसमाप्त(dev);
	bool cur;

	rfसमाप्त->suspended = false;

	अगर (!rfसमाप्त->रेजिस्टरed)
		वापस 0;

	अगर (!rfसमाप्त->persistent) अणु
		cur = !!(rfसमाप्त->state & RFKILL_BLOCK_SW);
		rfसमाप्त_set_block(rfसमाप्त, cur);
	पूर्ण

	अगर (rfसमाप्त->ops->poll && !rfसमाप्त->polling_छोड़ोd)
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &rfसमाप्त->poll_work, 0);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rfसमाप्त_pm_ops, rfसमाप्त_suspend, rfसमाप्त_resume);
#घोषणा RFKILL_PM_OPS (&rfसमाप्त_pm_ops)
#अन्यथा
#घोषणा RFKILL_PM_OPS शून्य
#पूर्ण_अगर

अटल काष्ठा class rfसमाप्त_class = अणु
	.name		= "rfkill",
	.dev_release	= rfसमाप्त_release,
	.dev_groups	= rfसमाप्त_dev_groups,
	.dev_uevent	= rfसमाप्त_dev_uevent,
	.pm		= RFKILL_PM_OPS,
पूर्ण;

bool rfसमाप्त_blocked(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	अचिन्हित दीर्घ flags;
	u32 state;

	spin_lock_irqsave(&rfसमाप्त->lock, flags);
	state = rfसमाप्त->state;
	spin_unlock_irqrestore(&rfसमाप्त->lock, flags);

	वापस !!(state & RFKILL_BLOCK_ANY);
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_blocked);


काष्ठा rfसमाप्त * __must_check rfसमाप्त_alloc(स्थिर अक्षर *name,
					  काष्ठा device *parent,
					  स्थिर क्रमागत rfसमाप्त_type type,
					  स्थिर काष्ठा rfसमाप्त_ops *ops,
					  व्योम *ops_data)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त;
	काष्ठा device *dev;

	अगर (WARN_ON(!ops))
		वापस शून्य;

	अगर (WARN_ON(!ops->set_block))
		वापस शून्य;

	अगर (WARN_ON(!name))
		वापस शून्य;

	अगर (WARN_ON(type == RFKILL_TYPE_ALL || type >= NUM_RFKILL_TYPES))
		वापस शून्य;

	rfसमाप्त = kzalloc(माप(*rfसमाप्त) + म_माप(name) + 1, GFP_KERNEL);
	अगर (!rfसमाप्त)
		वापस शून्य;

	spin_lock_init(&rfसमाप्त->lock);
	INIT_LIST_HEAD(&rfसमाप्त->node);
	rfसमाप्त->type = type;
	म_नकल(rfसमाप्त->name, name);
	rfसमाप्त->ops = ops;
	rfसमाप्त->data = ops_data;

	dev = &rfसमाप्त->dev;
	dev->class = &rfसमाप्त_class;
	dev->parent = parent;
	device_initialize(dev);

	वापस rfसमाप्त;
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_alloc);

अटल व्योम rfसमाप्त_poll(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त;

	rfसमाप्त = container_of(work, काष्ठा rfसमाप्त, poll_work.work);

	/*
	 * Poll hardware state -- driver will use one of the
	 * rfसमाप्त_setअणु,_hw,_swपूर्ण_state functions and use its
	 * वापस value to update the current status.
	 */
	rfसमाप्त->ops->poll(rfसमाप्त, rfसमाप्त->data);

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
		&rfसमाप्त->poll_work,
		round_jअगरfies_relative(POLL_INTERVAL));
पूर्ण

अटल व्योम rfसमाप्त_uevent_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त;

	rfसमाप्त = container_of(work, काष्ठा rfसमाप्त, uevent_work);

	mutex_lock(&rfसमाप्त_global_mutex);
	rfसमाप्त_event(rfसमाप्त);
	mutex_unlock(&rfसमाप्त_global_mutex);
पूर्ण

अटल व्योम rfसमाप्त_sync_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त;
	bool cur;

	rfसमाप्त = container_of(work, काष्ठा rfसमाप्त, sync_work);

	mutex_lock(&rfसमाप्त_global_mutex);
	cur = rfसमाप्त_global_states[rfसमाप्त->type].cur;
	rfसमाप्त_set_block(rfसमाप्त, cur);
	mutex_unlock(&rfसमाप्त_global_mutex);
पूर्ण

पूर्णांक __must_check rfसमाप्त_रेजिस्टर(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	अटल अचिन्हित दीर्घ rfसमाप्त_no;
	काष्ठा device *dev;
	पूर्णांक error;

	अगर (!rfसमाप्त)
		वापस -EINVAL;

	dev = &rfसमाप्त->dev;

	mutex_lock(&rfसमाप्त_global_mutex);

	अगर (rfसमाप्त->रेजिस्टरed) अणु
		error = -EALREADY;
		जाओ unlock;
	पूर्ण

	rfसमाप्त->idx = rfसमाप्त_no;
	dev_set_name(dev, "rfkill%lu", rfसमाप्त_no);
	rfसमाप्त_no++;

	list_add_tail(&rfसमाप्त->node, &rfसमाप्त_list);

	error = device_add(dev);
	अगर (error)
		जाओ हटाओ;

	error = rfसमाप्त_led_trigger_रेजिस्टर(rfसमाप्त);
	अगर (error)
		जाओ devdel;

	rfसमाप्त->रेजिस्टरed = true;

	INIT_DELAYED_WORK(&rfसमाप्त->poll_work, rfसमाप्त_poll);
	INIT_WORK(&rfसमाप्त->uevent_work, rfसमाप्त_uevent_work);
	INIT_WORK(&rfसमाप्त->sync_work, rfसमाप्त_sync_work);

	अगर (rfसमाप्त->ops->poll)
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
			&rfसमाप्त->poll_work,
			round_jअगरfies_relative(POLL_INTERVAL));

	अगर (!rfसमाप्त->persistent || rfसमाप्त_epo_lock_active) अणु
		schedule_work(&rfसमाप्त->sync_work);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_RFKILL_INPUT
		bool soft_blocked = !!(rfसमाप्त->state & RFKILL_BLOCK_SW);

		अगर (!atomic_पढ़ो(&rfसमाप्त_input_disabled))
			__rfसमाप्त_चयन_all(rfसमाप्त->type, soft_blocked);
#पूर्ण_अगर
	पूर्ण

	rfसमाप्त_global_led_trigger_event();
	rfसमाप्त_send_events(rfसमाप्त, RFKILL_OP_ADD);

	mutex_unlock(&rfसमाप्त_global_mutex);
	वापस 0;

 devdel:
	device_del(&rfसमाप्त->dev);
 हटाओ:
	list_del_init(&rfसमाप्त->node);
 unlock:
	mutex_unlock(&rfसमाप्त_global_mutex);
	वापस error;
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_रेजिस्टर);

व्योम rfसमाप्त_unरेजिस्टर(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	BUG_ON(!rfसमाप्त);

	अगर (rfसमाप्त->ops->poll)
		cancel_delayed_work_sync(&rfसमाप्त->poll_work);

	cancel_work_sync(&rfसमाप्त->uevent_work);
	cancel_work_sync(&rfसमाप्त->sync_work);

	rfसमाप्त->रेजिस्टरed = false;

	device_del(&rfसमाप्त->dev);

	mutex_lock(&rfसमाप्त_global_mutex);
	rfसमाप्त_send_events(rfसमाप्त, RFKILL_OP_DEL);
	list_del_init(&rfसमाप्त->node);
	rfसमाप्त_global_led_trigger_event();
	mutex_unlock(&rfसमाप्त_global_mutex);

	rfसमाप्त_led_trigger_unरेजिस्टर(rfसमाप्त);
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_unरेजिस्टर);

व्योम rfसमाप्त_destroy(काष्ठा rfसमाप्त *rfसमाप्त)
अणु
	अगर (rfसमाप्त)
		put_device(&rfसमाप्त->dev);
पूर्ण
EXPORT_SYMBOL(rfसमाप्त_destroy);

अटल पूर्णांक rfसमाप्त_fop_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा rfसमाप्त_data *data;
	काष्ठा rfसमाप्त *rfसमाप्त;
	काष्ठा rfसमाप्त_पूर्णांक_event *ev, *पंचांगp;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&data->events);
	mutex_init(&data->mtx);
	init_रुकोqueue_head(&data->पढ़ो_रुको);

	mutex_lock(&rfसमाप्त_global_mutex);
	mutex_lock(&data->mtx);
	/*
	 * start getting events from अन्यथाwhere but hold mtx to get
	 * startup events added first
	 */

	list_क्रम_each_entry(rfसमाप्त, &rfसमाप्त_list, node) अणु
		ev = kzalloc(माप(*ev), GFP_KERNEL);
		अगर (!ev)
			जाओ मुक्त;
		rfसमाप्त_fill_event(&ev->ev, rfसमाप्त, RFKILL_OP_ADD);
		list_add_tail(&ev->list, &data->events);
	पूर्ण
	list_add(&data->list, &rfसमाप्त_fds);
	mutex_unlock(&data->mtx);
	mutex_unlock(&rfसमाप्त_global_mutex);

	file->निजी_data = data;

	वापस stream_खोलो(inode, file);

 मुक्त:
	mutex_unlock(&data->mtx);
	mutex_unlock(&rfसमाप्त_global_mutex);
	mutex_destroy(&data->mtx);
	list_क्रम_each_entry_safe(ev, पंचांगp, &data->events, list)
		kमुक्त(ev);
	kमुक्त(data);
	वापस -ENOMEM;
पूर्ण

अटल __poll_t rfसमाप्त_fop_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा rfसमाप्त_data *data = file->निजी_data;
	__poll_t res = EPOLLOUT | EPOLLWRNORM;

	poll_रुको(file, &data->पढ़ो_रुको, रुको);

	mutex_lock(&data->mtx);
	अगर (!list_empty(&data->events))
		res = EPOLLIN | EPOLLRDNORM;
	mutex_unlock(&data->mtx);

	वापस res;
पूर्ण

अटल sमाप_प्रकार rfसमाप्त_fop_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा rfसमाप्त_data *data = file->निजी_data;
	काष्ठा rfसमाप्त_पूर्णांक_event *ev;
	अचिन्हित दीर्घ sz;
	पूर्णांक ret;

	mutex_lock(&data->mtx);

	जबतक (list_empty(&data->events)) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			ret = -EAGAIN;
			जाओ out;
		पूर्ण
		mutex_unlock(&data->mtx);
		/* since we re-check and it just compares poपूर्णांकers,
		 * using !list_empty() without locking isn't a problem
		 */
		ret = रुको_event_पूर्णांकerruptible(data->पढ़ो_रुको,
					       !list_empty(&data->events));
		mutex_lock(&data->mtx);

		अगर (ret)
			जाओ out;
	पूर्ण

	ev = list_first_entry(&data->events, काष्ठा rfसमाप्त_पूर्णांक_event,
				list);

	sz = min_t(अचिन्हित दीर्घ, माप(ev->ev), count);
	ret = sz;
	अगर (copy_to_user(buf, &ev->ev, sz))
		ret = -EFAULT;

	list_del(&ev->list);
	kमुक्त(ev);
 out:
	mutex_unlock(&data->mtx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार rfसमाप्त_fop_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त;
	काष्ठा rfसमाप्त_event_ext ev;
	पूर्णांक ret;

	/* we करोn't need the 'hard' variable but accept it */
	अगर (count < RFKILL_EVENT_SIZE_V1 - 1)
		वापस -EINVAL;

	/*
	 * Copy as much data as we can accept पूर्णांकo our 'ev' buffer,
	 * but tell userspace how much we've copied so it can determine
	 * our API version even in a ग_लिखो() call, अगर it cares.
	 */
	count = min(count, माप(ev));
	अगर (copy_from_user(&ev, buf, count))
		वापस -EFAULT;

	अगर (ev.type >= NUM_RFKILL_TYPES)
		वापस -EINVAL;

	mutex_lock(&rfसमाप्त_global_mutex);

	चयन (ev.op) अणु
	हाल RFKILL_OP_CHANGE_ALL:
		rfसमाप्त_update_global_state(ev.type, ev.soft);
		list_क्रम_each_entry(rfसमाप्त, &rfसमाप्त_list, node)
			अगर (rfसमाप्त->type == ev.type ||
			    ev.type == RFKILL_TYPE_ALL)
				rfसमाप्त_set_block(rfसमाप्त, ev.soft);
		ret = 0;
		अवरोध;
	हाल RFKILL_OP_CHANGE:
		list_क्रम_each_entry(rfसमाप्त, &rfसमाप्त_list, node)
			अगर (rfसमाप्त->idx == ev.idx &&
			    (rfसमाप्त->type == ev.type ||
			     ev.type == RFKILL_TYPE_ALL))
				rfसमाप्त_set_block(rfसमाप्त, ev.soft);
		ret = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&rfसमाप्त_global_mutex);

	वापस ret ?: count;
पूर्ण

अटल पूर्णांक rfसमाप्त_fop_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा rfसमाप्त_data *data = file->निजी_data;
	काष्ठा rfसमाप्त_पूर्णांक_event *ev, *पंचांगp;

	mutex_lock(&rfसमाप्त_global_mutex);
	list_del(&data->list);
	mutex_unlock(&rfसमाप्त_global_mutex);

	mutex_destroy(&data->mtx);
	list_क्रम_each_entry_safe(ev, पंचांगp, &data->events, list)
		kमुक्त(ev);

#अगर_घोषित CONFIG_RFKILL_INPUT
	अगर (data->input_handler)
		अगर (atomic_dec_वापस(&rfसमाप्त_input_disabled) == 0)
			prपूर्णांकk(KERN_DEBUG "rfkill: input handler enabled\n");
#पूर्ण_अगर

	kमुक्त(data);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_RFKILL_INPUT
अटल दीर्घ rfसमाप्त_fop_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	काष्ठा rfसमाप्त_data *data = file->निजी_data;

	अगर (_IOC_TYPE(cmd) != RFKILL_IOC_MAGIC)
		वापस -ENOSYS;

	अगर (_IOC_NR(cmd) != RFKILL_IOC_NOINPUT)
		वापस -ENOSYS;

	mutex_lock(&data->mtx);

	अगर (!data->input_handler) अणु
		अगर (atomic_inc_वापस(&rfसमाप्त_input_disabled) == 1)
			prपूर्णांकk(KERN_DEBUG "rfkill: input handler disabled\n");
		data->input_handler = true;
	पूर्ण

	mutex_unlock(&data->mtx);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations rfसमाप्त_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= rfसमाप्त_fop_खोलो,
	.पढ़ो		= rfसमाप्त_fop_पढ़ो,
	.ग_लिखो		= rfसमाप्त_fop_ग_लिखो,
	.poll		= rfसमाप्त_fop_poll,
	.release	= rfसमाप्त_fop_release,
#अगर_घोषित CONFIG_RFKILL_INPUT
	.unlocked_ioctl	= rfसमाप्त_fop_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
#पूर्ण_अगर
	.llseek		= no_llseek,
पूर्ण;

#घोषणा RFKILL_NAME "rfkill"

अटल काष्ठा miscdevice rfसमाप्त_miscdev = अणु
	.fops	= &rfसमाप्त_fops,
	.name	= RFKILL_NAME,
	.minor	= RFKILL_MINOR,
पूर्ण;

अटल पूर्णांक __init rfसमाप्त_init(व्योम)
अणु
	पूर्णांक error;

	rfसमाप्त_update_global_state(RFKILL_TYPE_ALL, !rfसमाप्त_शेष_state);

	error = class_रेजिस्टर(&rfसमाप्त_class);
	अगर (error)
		जाओ error_class;

	error = misc_रेजिस्टर(&rfसमाप्त_miscdev);
	अगर (error)
		जाओ error_misc;

	error = rfसमाप्त_global_led_trigger_रेजिस्टर();
	अगर (error)
		जाओ error_led_trigger;

#अगर_घोषित CONFIG_RFKILL_INPUT
	error = rfसमाप्त_handler_init();
	अगर (error)
		जाओ error_input;
#पूर्ण_अगर

	वापस 0;

#अगर_घोषित CONFIG_RFKILL_INPUT
error_input:
	rfसमाप्त_global_led_trigger_unरेजिस्टर();
#पूर्ण_अगर
error_led_trigger:
	misc_deरेजिस्टर(&rfसमाप्त_miscdev);
error_misc:
	class_unरेजिस्टर(&rfसमाप्त_class);
error_class:
	वापस error;
पूर्ण
subsys_initcall(rfसमाप्त_init);

अटल व्योम __निकास rfसमाप्त_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_RFKILL_INPUT
	rfसमाप्त_handler_निकास();
#पूर्ण_अगर
	rfसमाप्त_global_led_trigger_unरेजिस्टर();
	misc_deरेजिस्टर(&rfसमाप्त_miscdev);
	class_unरेजिस्टर(&rfसमाप्त_class);
पूर्ण
module_निकास(rfसमाप्त_निकास);

MODULE_ALIAS_MISCDEV(RFKILL_MINOR);
MODULE_ALIAS("devname:" RFKILL_NAME);
