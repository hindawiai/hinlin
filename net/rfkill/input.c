<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Input layer to RF Kill पूर्णांकerface connector
 *
 * Copyright (c) 2007 Dmitry Torokhov
 * Copyright 2009 Johannes Berg <johannes@sipsolutions.net>
 *
 * If you ever run पूर्णांकo a situation in which you have a SW_ type rfसमाप्त
 * input device, then you can revive code that was हटाओd in the patch
 * "rfkill-input: remove unused code".
 */

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/init.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/sched.h>

#समावेश "rfkill.h"

क्रमागत rfसमाप्त_input_master_mode अणु
	RFKILL_INPUT_MASTER_UNLOCK = 0,
	RFKILL_INPUT_MASTER_RESTORE = 1,
	RFKILL_INPUT_MASTER_UNBLOCKALL = 2,
	NUM_RFKILL_INPUT_MASTER_MODES
पूर्ण;

/* Delay (in ms) between consecutive चयन ops */
#घोषणा RFKILL_OPS_DELAY 200

अटल क्रमागत rfसमाप्त_input_master_mode rfसमाप्त_master_चयन_mode =
					RFKILL_INPUT_MASTER_UNBLOCKALL;
module_param_named(master_चयन_mode, rfसमाप्त_master_चयन_mode, uपूर्णांक, 0);
MODULE_PARM_DESC(master_चयन_mode,
	"SW_RFKILL_ALL ON should: 0=do nothing (only unlock); 1=restore; 2=unblock all");

अटल DEFINE_SPINLOCK(rfसमाप्त_op_lock);
अटल bool rfसमाप्त_op_pending;
अटल अचिन्हित दीर्घ rfसमाप्त_sw_pending[BITS_TO_LONGS(NUM_RFKILL_TYPES)];
अटल अचिन्हित दीर्घ rfसमाप्त_sw_state[BITS_TO_LONGS(NUM_RFKILL_TYPES)];

क्रमागत rfसमाप्त_sched_op अणु
	RFKILL_GLOBAL_OP_EPO = 0,
	RFKILL_GLOBAL_OP_RESTORE,
	RFKILL_GLOBAL_OP_UNLOCK,
	RFKILL_GLOBAL_OP_UNBLOCK,
पूर्ण;

अटल क्रमागत rfसमाप्त_sched_op rfसमाप्त_master_चयन_op;
अटल क्रमागत rfसमाप्त_sched_op rfसमाप्त_op;

अटल व्योम __rfसमाप्त_handle_global_op(क्रमागत rfसमाप्त_sched_op op)
अणु
	अचिन्हित पूर्णांक i;

	चयन (op) अणु
	हाल RFKILL_GLOBAL_OP_EPO:
		rfसमाप्त_epo();
		अवरोध;
	हाल RFKILL_GLOBAL_OP_RESTORE:
		rfसमाप्त_restore_states();
		अवरोध;
	हाल RFKILL_GLOBAL_OP_UNLOCK:
		rfसमाप्त_हटाओ_epo_lock();
		अवरोध;
	हाल RFKILL_GLOBAL_OP_UNBLOCK:
		rfसमाप्त_हटाओ_epo_lock();
		क्रम (i = 0; i < NUM_RFKILL_TYPES; i++)
			rfसमाप्त_चयन_all(i, false);
		अवरोध;
	शेष:
		/* memory corruption or bug, fail safely */
		rfसमाप्त_epo();
		WARN(1, "Unknown requested operation %d! "
			"rfkill Emergency Power Off activated\n",
			op);
	पूर्ण
पूर्ण

अटल व्योम __rfसमाप्त_handle_normal_op(स्थिर क्रमागत rfसमाप्त_type type,
				      स्थिर bool complement)
अणु
	bool blocked;

	blocked = rfसमाप्त_get_global_sw_state(type);
	अगर (complement)
		blocked = !blocked;

	rfसमाप्त_चयन_all(type, blocked);
पूर्ण

अटल व्योम rfसमाप्त_op_handler(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित पूर्णांक i;
	bool c;

	spin_lock_irq(&rfसमाप्त_op_lock);
	करो अणु
		अगर (rfसमाप्त_op_pending) अणु
			क्रमागत rfसमाप्त_sched_op op = rfसमाप्त_op;
			rfसमाप्त_op_pending = false;
			स_रखो(rfसमाप्त_sw_pending, 0,
				माप(rfसमाप्त_sw_pending));
			spin_unlock_irq(&rfसमाप्त_op_lock);

			__rfसमाप्त_handle_global_op(op);

			spin_lock_irq(&rfसमाप्त_op_lock);

			/*
			 * handle global ops first -- during unlocked period
			 * we might have gotten a new global op.
			 */
			अगर (rfसमाप्त_op_pending)
				जारी;
		पूर्ण

		अगर (rfसमाप्त_is_epo_lock_active())
			जारी;

		क्रम (i = 0; i < NUM_RFKILL_TYPES; i++) अणु
			अगर (__test_and_clear_bit(i, rfसमाप्त_sw_pending)) अणु
				c = __test_and_clear_bit(i, rfसमाप्त_sw_state);
				spin_unlock_irq(&rfसमाप्त_op_lock);

				__rfसमाप्त_handle_normal_op(i, c);

				spin_lock_irq(&rfसमाप्त_op_lock);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (rfसमाप्त_op_pending);
	spin_unlock_irq(&rfसमाप्त_op_lock);
पूर्ण

अटल DECLARE_DELAYED_WORK(rfसमाप्त_op_work, rfसमाप्त_op_handler);
अटल अचिन्हित दीर्घ rfसमाप्त_last_scheduled;

अटल अचिन्हित दीर्घ rfसमाप्त_ratelimit(स्थिर अचिन्हित दीर्घ last)
अणु
	स्थिर अचिन्हित दीर्घ delay = msecs_to_jअगरfies(RFKILL_OPS_DELAY);
	वापस समय_after(jअगरfies, last + delay) ? 0 : delay;
पूर्ण

अटल व्योम rfसमाप्त_schedule_ratelimited(व्योम)
अणु
	अगर (schedule_delayed_work(&rfसमाप्त_op_work,
				  rfसमाप्त_ratelimit(rfसमाप्त_last_scheduled)))
		rfसमाप्त_last_scheduled = jअगरfies;
पूर्ण

अटल व्योम rfसमाप्त_schedule_global_op(क्रमागत rfसमाप्त_sched_op op)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rfसमाप्त_op_lock, flags);
	rfसमाप्त_op = op;
	rfसमाप्त_op_pending = true;
	अगर (op == RFKILL_GLOBAL_OP_EPO && !rfसमाप्त_is_epo_lock_active()) अणु
		/* bypass the limiter क्रम EPO */
		mod_delayed_work(प्रणाली_wq, &rfसमाप्त_op_work, 0);
		rfसमाप्त_last_scheduled = jअगरfies;
	पूर्ण अन्यथा
		rfसमाप्त_schedule_ratelimited();
	spin_unlock_irqrestore(&rfसमाप्त_op_lock, flags);
पूर्ण

अटल व्योम rfसमाप्त_schedule_toggle(क्रमागत rfसमाप्त_type type)
अणु
	अचिन्हित दीर्घ flags;

	अगर (rfसमाप्त_is_epo_lock_active())
		वापस;

	spin_lock_irqsave(&rfसमाप्त_op_lock, flags);
	अगर (!rfसमाप्त_op_pending) अणु
		__set_bit(type, rfसमाप्त_sw_pending);
		__change_bit(type, rfसमाप्त_sw_state);
		rfसमाप्त_schedule_ratelimited();
	पूर्ण
	spin_unlock_irqrestore(&rfसमाप्त_op_lock, flags);
पूर्ण

अटल व्योम rfसमाप्त_schedule_evsw_rfसमाप्तall(पूर्णांक state)
अणु
	अगर (state)
		rfसमाप्त_schedule_global_op(rfसमाप्त_master_चयन_op);
	अन्यथा
		rfसमाप्त_schedule_global_op(RFKILL_GLOBAL_OP_EPO);
पूर्ण

अटल व्योम rfसमाप्त_event(काष्ठा input_handle *handle, अचिन्हित पूर्णांक type,
			अचिन्हित पूर्णांक code, पूर्णांक data)
अणु
	अगर (type == EV_KEY && data == 1) अणु
		चयन (code) अणु
		हाल KEY_WLAN:
			rfसमाप्त_schedule_toggle(RFKILL_TYPE_WLAN);
			अवरोध;
		हाल KEY_BLUETOOTH:
			rfसमाप्त_schedule_toggle(RFKILL_TYPE_BLUETOOTH);
			अवरोध;
		हाल KEY_UWB:
			rfसमाप्त_schedule_toggle(RFKILL_TYPE_UWB);
			अवरोध;
		हाल KEY_WIMAX:
			rfसमाप्त_schedule_toggle(RFKILL_TYPE_WIMAX);
			अवरोध;
		हाल KEY_RFKILL:
			rfसमाप्त_schedule_toggle(RFKILL_TYPE_ALL);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (type == EV_SW && code == SW_RFKILL_ALL)
		rfसमाप्त_schedule_evsw_rfसमाप्तall(data);
पूर्ण

अटल पूर्णांक rfसमाप्त_connect(काष्ठा input_handler *handler, काष्ठा input_dev *dev,
			  स्थिर काष्ठा input_device_id *id)
अणु
	काष्ठा input_handle *handle;
	पूर्णांक error;

	handle = kzalloc(माप(काष्ठा input_handle), GFP_KERNEL);
	अगर (!handle)
		वापस -ENOMEM;

	handle->dev = dev;
	handle->handler = handler;
	handle->name = "rfkill";

	/* causes rfसमाप्त_start() to be called */
	error = input_रेजिस्टर_handle(handle);
	अगर (error)
		जाओ err_मुक्त_handle;

	error = input_खोलो_device(handle);
	अगर (error)
		जाओ err_unरेजिस्टर_handle;

	वापस 0;

 err_unरेजिस्टर_handle:
	input_unरेजिस्टर_handle(handle);
 err_मुक्त_handle:
	kमुक्त(handle);
	वापस error;
पूर्ण

अटल व्योम rfसमाप्त_start(काष्ठा input_handle *handle)
अणु
	/*
	 * Take event_lock to guard against configuration changes, we
	 * should be able to deal with concurrency with rfसमाप्त_event()
	 * just fine (which event_lock will also aव्योम).
	 */
	spin_lock_irq(&handle->dev->event_lock);

	अगर (test_bit(EV_SW, handle->dev->evbit) &&
	    test_bit(SW_RFKILL_ALL, handle->dev->swbit))
		rfसमाप्त_schedule_evsw_rfसमाप्तall(test_bit(SW_RFKILL_ALL,
							handle->dev->sw));

	spin_unlock_irq(&handle->dev->event_lock);
पूर्ण

अटल व्योम rfसमाप्त_disconnect(काष्ठा input_handle *handle)
अणु
	input_बंद_device(handle);
	input_unरेजिस्टर_handle(handle);
	kमुक्त(handle);
पूर्ण

अटल स्थिर काष्ठा input_device_id rfसमाप्त_ids[] = अणु
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT | INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
		.keybit = अणु [BIT_WORD(KEY_WLAN)] = BIT_MASK(KEY_WLAN) पूर्ण,
	पूर्ण,
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT | INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
		.keybit = अणु [BIT_WORD(KEY_BLUETOOTH)] = BIT_MASK(KEY_BLUETOOTH) पूर्ण,
	पूर्ण,
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT | INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
		.keybit = अणु [BIT_WORD(KEY_UWB)] = BIT_MASK(KEY_UWB) पूर्ण,
	पूर्ण,
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT | INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
		.keybit = अणु [BIT_WORD(KEY_WIMAX)] = BIT_MASK(KEY_WIMAX) पूर्ण,
	पूर्ण,
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT | INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
		.keybit = अणु [BIT_WORD(KEY_RFKILL)] = BIT_MASK(KEY_RFKILL) पूर्ण,
	पूर्ण,
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT | INPUT_DEVICE_ID_MATCH_SWBIT,
		.evbit = अणु BIT(EV_SW) पूर्ण,
		.swbit = अणु [BIT_WORD(SW_RFKILL_ALL)] = BIT_MASK(SW_RFKILL_ALL) पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा input_handler rfसमाप्त_handler = अणु
	.name =	"rfkill",
	.event = rfसमाप्त_event,
	.connect = rfसमाप्त_connect,
	.start = rfसमाप्त_start,
	.disconnect = rfसमाप्त_disconnect,
	.id_table = rfसमाप्त_ids,
पूर्ण;

पूर्णांक __init rfसमाप्त_handler_init(व्योम)
अणु
	चयन (rfसमाप्त_master_चयन_mode) अणु
	हाल RFKILL_INPUT_MASTER_UNBLOCKALL:
		rfसमाप्त_master_चयन_op = RFKILL_GLOBAL_OP_UNBLOCK;
		अवरोध;
	हाल RFKILL_INPUT_MASTER_RESTORE:
		rfसमाप्त_master_चयन_op = RFKILL_GLOBAL_OP_RESTORE;
		अवरोध;
	हाल RFKILL_INPUT_MASTER_UNLOCK:
		rfसमाप्त_master_चयन_op = RFKILL_GLOBAL_OP_UNLOCK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Aव्योम delay at first schedule */
	rfसमाप्त_last_scheduled =
			jअगरfies - msecs_to_jअगरfies(RFKILL_OPS_DELAY) - 1;
	वापस input_रेजिस्टर_handler(&rfसमाप्त_handler);
पूर्ण

व्योम __निकास rfसमाप्त_handler_निकास(व्योम)
अणु
	input_unरेजिस्टर_handler(&rfसमाप्त_handler);
	cancel_delayed_work_sync(&rfसमाप्त_op_work);
पूर्ण
