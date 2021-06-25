<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/vmw_vmci_api.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>

#समावेश "vmci_driver.h"
#समावेश "vmci_event.h"

#घोषणा EVENT_MAGIC 0xEABE0000
#घोषणा VMCI_EVENT_MAX_ATTEMPTS 10

काष्ठा vmci_subscription अणु
	u32 id;
	u32 event;
	vmci_event_cb callback;
	व्योम *callback_data;
	काष्ठा list_head node;	/* on one of subscriber lists */
पूर्ण;

अटल काष्ठा list_head subscriber_array[VMCI_EVENT_MAX];
अटल DEFINE_MUTEX(subscriber_mutex);

पूर्णांक __init vmci_event_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VMCI_EVENT_MAX; i++)
		INIT_LIST_HEAD(&subscriber_array[i]);

	वापस VMCI_SUCCESS;
पूर्ण

व्योम vmci_event_निकास(व्योम)
अणु
	पूर्णांक e;

	/* We मुक्त all memory at निकास. */
	क्रम (e = 0; e < VMCI_EVENT_MAX; e++) अणु
		काष्ठा vmci_subscription *cur, *p2;
		list_क्रम_each_entry_safe(cur, p2, &subscriber_array[e], node) अणु

			/*
			 * We should never get here because all events
			 * should have been unरेजिस्टरed beक्रमe we try
			 * to unload the driver module.
			 */
			pr_warn("Unexpected free events occurring\n");
			list_del(&cur->node);
			kमुक्त(cur);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Find entry. Assumes subscriber_mutex is held.
 */
अटल काष्ठा vmci_subscription *event_find(u32 sub_id)
अणु
	पूर्णांक e;

	क्रम (e = 0; e < VMCI_EVENT_MAX; e++) अणु
		काष्ठा vmci_subscription *cur;
		list_क्रम_each_entry(cur, &subscriber_array[e], node) अणु
			अगर (cur->id == sub_id)
				वापस cur;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Actually delivers the events to the subscribers.
 * The callback function क्रम each subscriber is invoked.
 */
अटल व्योम event_deliver(काष्ठा vmci_event_msg *event_msg)
अणु
	काष्ठा vmci_subscription *cur;
	काष्ठा list_head *subscriber_list;

	rcu_पढ़ो_lock();
	subscriber_list = &subscriber_array[event_msg->event_data.event];
	list_क्रम_each_entry_rcu(cur, subscriber_list, node) अणु
		cur->callback(cur->id, &event_msg->event_data,
			      cur->callback_data);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Dispatcher क्रम the VMCI_EVENT_RECEIVE datagrams. Calls all
 * subscribers क्रम given event.
 */
पूर्णांक vmci_event_dispatch(काष्ठा vmci_datagram *msg)
अणु
	काष्ठा vmci_event_msg *event_msg = (काष्ठा vmci_event_msg *)msg;

	अगर (msg->payload_size < माप(u32) ||
	    msg->payload_size > माप(काष्ठा vmci_event_data_max))
		वापस VMCI_ERROR_INVALID_ARGS;

	अगर (!VMCI_EVENT_VALID(event_msg->event_data.event))
		वापस VMCI_ERROR_EVENT_UNKNOWN;

	event_deliver(event_msg);
	वापस VMCI_SUCCESS;
पूर्ण

/*
 * vmci_event_subscribe() - Subscribe to a given event.
 * @event:      The event to subscribe to.
 * @callback:   The callback to invoke upon the event.
 * @callback_data:      Data to pass to the callback.
 * @subscription_id:    ID used to track subscription.  Used with
 *              vmci_event_unsubscribe()
 *
 * Subscribes to the provided event. The callback specअगरied will be
 * fired from RCU critical section and thereक्रमe must not sleep.
 */
पूर्णांक vmci_event_subscribe(u32 event,
			 vmci_event_cb callback,
			 व्योम *callback_data,
			 u32 *new_subscription_id)
अणु
	काष्ठा vmci_subscription *sub;
	पूर्णांक attempts;
	पूर्णांक retval;
	bool have_new_id = false;

	अगर (!new_subscription_id) अणु
		pr_devel("%s: Invalid subscription (NULL)\n", __func__);
		वापस VMCI_ERROR_INVALID_ARGS;
	पूर्ण

	अगर (!VMCI_EVENT_VALID(event) || !callback) अणु
		pr_devel("%s: Failed to subscribe to event (type=%d) (callback=%p) (data=%p)\n",
			 __func__, event, callback, callback_data);
		वापस VMCI_ERROR_INVALID_ARGS;
	पूर्ण

	sub = kzalloc(माप(*sub), GFP_KERNEL);
	अगर (!sub)
		वापस VMCI_ERROR_NO_MEM;

	sub->id = VMCI_EVENT_MAX;
	sub->event = event;
	sub->callback = callback;
	sub->callback_data = callback_data;
	INIT_LIST_HEAD(&sub->node);

	mutex_lock(&subscriber_mutex);

	/* Creation of a new event is always allowed. */
	क्रम (attempts = 0; attempts < VMCI_EVENT_MAX_ATTEMPTS; attempts++) अणु
		अटल u32 subscription_id;
		/*
		 * We try to get an id a couple of समय beक्रमe
		 * claiming we are out of resources.
		 */

		/* Test क्रम duplicate id. */
		अगर (!event_find(++subscription_id)) अणु
			sub->id = subscription_id;
			have_new_id = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (have_new_id) अणु
		list_add_rcu(&sub->node, &subscriber_array[event]);
		retval = VMCI_SUCCESS;
	पूर्ण अन्यथा अणु
		retval = VMCI_ERROR_NO_RESOURCES;
	पूर्ण

	mutex_unlock(&subscriber_mutex);

	*new_subscription_id = sub->id;
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_event_subscribe);

/*
 * vmci_event_unsubscribe() - unsubscribe from an event.
 * @sub_id:     A subscription ID as provided by vmci_event_subscribe()
 *
 * Unsubscribe from given event. Removes it from list and मुक्तs it.
 * Will वापस callback_data अगर requested by caller.
 */
पूर्णांक vmci_event_unsubscribe(u32 sub_id)
अणु
	काष्ठा vmci_subscription *s;

	mutex_lock(&subscriber_mutex);
	s = event_find(sub_id);
	अगर (s)
		list_del_rcu(&s->node);
	mutex_unlock(&subscriber_mutex);

	अगर (!s)
		वापस VMCI_ERROR_NOT_FOUND;

	synchronize_rcu();
	kमुक्त(s);

	वापस VMCI_SUCCESS;
पूर्ण
EXPORT_SYMBOL_GPL(vmci_event_unsubscribe);
