<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Main SSAM/SSH controller काष्ठाure and functionality.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/atomic.h>
#समावेश <linux/completion.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kref.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/serdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/srcu.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/surface_aggregator/controller.h>
#समावेश <linux/surface_aggregator/serial_hub.h>

#समावेश "controller.h"
#समावेश "ssh_msgb.h"
#समावेश "ssh_request_layer.h"

#समावेश "trace.h"


/* -- Safe counters. -------------------------------------------------------- */

/**
 * ssh_seq_reset() - Reset/initialize sequence ID counter.
 * @c: The counter to reset.
 */
अटल व्योम ssh_seq_reset(काष्ठा ssh_seq_counter *c)
अणु
	WRITE_ONCE(c->value, 0);
पूर्ण

/**
 * ssh_seq_next() - Get next sequence ID.
 * @c: The counter providing the sequence IDs.
 *
 * Return: Returns the next sequence ID of the counter.
 */
अटल u8 ssh_seq_next(काष्ठा ssh_seq_counter *c)
अणु
	u8 old = READ_ONCE(c->value);
	u8 new = old + 1;
	u8 ret;

	जबतक (unlikely((ret = cmpxchg(&c->value, old, new)) != old)) अणु
		old = ret;
		new = old + 1;
	पूर्ण

	वापस old;
पूर्ण

/**
 * ssh_rqid_reset() - Reset/initialize request ID counter.
 * @c: The counter to reset.
 */
अटल व्योम ssh_rqid_reset(काष्ठा ssh_rqid_counter *c)
अणु
	WRITE_ONCE(c->value, 0);
पूर्ण

/**
 * ssh_rqid_next() - Get next request ID.
 * @c: The counter providing the request IDs.
 *
 * Return: Returns the next request ID of the counter, skipping any reserved
 * request IDs.
 */
अटल u16 ssh_rqid_next(काष्ठा ssh_rqid_counter *c)
अणु
	u16 old = READ_ONCE(c->value);
	u16 new = ssh_rqid_next_valid(old);
	u16 ret;

	जबतक (unlikely((ret = cmpxchg(&c->value, old, new)) != old)) अणु
		old = ret;
		new = ssh_rqid_next_valid(old);
	पूर्ण

	वापस old;
पूर्ण


/* -- Event notअगरier/callbacks. --------------------------------------------- */
/*
 * The notअगरier प्रणाली is based on linux/notअगरier.h, specअगरically the SRCU
 * implementation. The dअगरference to that is, that some bits of the notअगरier
 * call वापस value can be tracked across multiple calls. This is करोne so
 * that handling of events can be tracked and a warning can be issued in हाल
 * an event goes unhandled. The idea of that warning is that it should help
 * discover and identअगरy new/currently unimplemented features.
 */

/**
 * ssam_event_matches_notअगरier() - Test अगर an event matches a notअगरier.
 * @n: The event notअगरier to test against.
 * @event: The event to test.
 *
 * Return: Returns %true अगर the given event matches the given notअगरier
 * according to the rules set in the notअगरier's event mask, %false otherwise.
 */
अटल bool ssam_event_matches_notअगरier(स्थिर काष्ठा ssam_event_notअगरier *n,
					स्थिर काष्ठा ssam_event *event)
अणु
	bool match = n->event.id.target_category == event->target_category;

	अगर (n->event.mask & SSAM_EVENT_MASK_TARGET)
		match &= n->event.reg.target_id == event->target_id;

	अगर (n->event.mask & SSAM_EVENT_MASK_INSTANCE)
		match &= n->event.id.instance == event->instance_id;

	वापस match;
पूर्ण

/**
 * ssam_nfblk_call_chain() - Call event notअगरier callbacks of the given chain.
 * @nh:    The notअगरier head क्रम which the notअगरier callbacks should be called.
 * @event: The event data provided to the callbacks.
 *
 * Call all रेजिस्टरed notअगरier callbacks in order of their priority until
 * either no notअगरier is left or a notअगरier वापसs a value with the
 * %SSAM_NOTIF_STOP bit set. Note that this bit is स्वतःmatically set via
 * ssam_notअगरier_from_त्रुटि_सं() on any non-zero error value.
 *
 * Return: Returns the notअगरier status value, which contains the notअगरier
 * status bits (%SSAM_NOTIF_HANDLED and %SSAM_NOTIF_STOP) as well as a
 * potential error value वापसed from the last executed notअगरier callback.
 * Use ssam_notअगरier_to_त्रुटि_सं() to convert this value to the original error
 * value.
 */
अटल पूर्णांक ssam_nfblk_call_chain(काष्ठा ssam_nf_head *nh, काष्ठा ssam_event *event)
अणु
	काष्ठा ssam_event_notअगरier *nf;
	पूर्णांक ret = 0, idx;

	idx = srcu_पढ़ो_lock(&nh->srcu);

	list_क्रम_each_entry_rcu(nf, &nh->head, base.node,
				srcu_पढ़ो_lock_held(&nh->srcu)) अणु
		अगर (ssam_event_matches_notअगरier(nf, event)) अणु
			ret = (ret & SSAM_NOTIF_STATE_MASK) | nf->base.fn(nf, event);
			अगर (ret & SSAM_NOTIF_STOP)
				अवरोध;
		पूर्ण
	पूर्ण

	srcu_पढ़ो_unlock(&nh->srcu, idx);
	वापस ret;
पूर्ण

/**
 * ssam_nfblk_insert() - Insert a new notअगरier block पूर्णांकo the given notअगरier
 * list.
 * @nh: The notअगरier head पूर्णांकo which the block should be inserted.
 * @nb: The notअगरier block to add.
 *
 * Note: This function must be synchronized by the caller with respect to other
 * insert, find, and/or हटाओ calls by holding ``काष्ठा ssam_nf.lock``.
 *
 * Return: Returns zero on success, %-EEXIST अगर the notअगरier block has alपढ़ोy
 * been रेजिस्टरed.
 */
अटल पूर्णांक ssam_nfblk_insert(काष्ठा ssam_nf_head *nh, काष्ठा ssam_notअगरier_block *nb)
अणु
	काष्ठा ssam_notअगरier_block *p;
	काष्ठा list_head *h;

	/* Runs under lock, no need क्रम RCU variant. */
	list_क्रम_each(h, &nh->head) अणु
		p = list_entry(h, काष्ठा ssam_notअगरier_block, node);

		अगर (unlikely(p == nb)) अणु
			WARN(1, "double register detected");
			वापस -EEXIST;
		पूर्ण

		अगर (nb->priority > p->priority)
			अवरोध;
	पूर्ण

	list_add_tail_rcu(&nb->node, h);
	वापस 0;
पूर्ण

/**
 * ssam_nfblk_find() - Check अगर a notअगरier block is रेजिस्टरed on the given
 * notअगरier head.
 * list.
 * @nh: The notअगरier head on which to search.
 * @nb: The notअगरier block to search क्रम.
 *
 * Note: This function must be synchronized by the caller with respect to other
 * insert, find, and/or हटाओ calls by holding ``काष्ठा ssam_nf.lock``.
 *
 * Return: Returns true अगर the given notअगरier block is रेजिस्टरed on the given
 * notअगरier head, false otherwise.
 */
अटल bool ssam_nfblk_find(काष्ठा ssam_nf_head *nh, काष्ठा ssam_notअगरier_block *nb)
अणु
	काष्ठा ssam_notअगरier_block *p;

	/* Runs under lock, no need क्रम RCU variant. */
	list_क्रम_each_entry(p, &nh->head, node) अणु
		अगर (p == nb)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * ssam_nfblk_हटाओ() - Remove a notअगरier block from its notअगरier list.
 * @nb: The notअगरier block to be हटाओd.
 *
 * Note: This function must be synchronized by the caller with respect to
 * other insert, find, and/or हटाओ calls by holding ``काष्ठा ssam_nf.lock``.
 * Furthermore, the caller _must_ ensure SRCU synchronization by calling
 * synchronize_srcu() with ``nh->srcu`` after leaving the critical section, to
 * ensure that the हटाओd notअगरier block is not in use any more.
 */
अटल व्योम ssam_nfblk_हटाओ(काष्ठा ssam_notअगरier_block *nb)
अणु
	list_del_rcu(&nb->node);
पूर्ण

/**
 * ssam_nf_head_init() - Initialize the given notअगरier head.
 * @nh: The notअगरier head to initialize.
 */
अटल पूर्णांक ssam_nf_head_init(काष्ठा ssam_nf_head *nh)
अणु
	पूर्णांक status;

	status = init_srcu_काष्ठा(&nh->srcu);
	अगर (status)
		वापस status;

	INIT_LIST_HEAD(&nh->head);
	वापस 0;
पूर्ण

/**
 * ssam_nf_head_destroy() - Deinitialize the given notअगरier head.
 * @nh: The notअगरier head to deinitialize.
 */
अटल व्योम ssam_nf_head_destroy(काष्ठा ssam_nf_head *nh)
अणु
	cleanup_srcu_काष्ठा(&nh->srcu);
पूर्ण


/* -- Event/notअगरication registry. ------------------------------------------ */

/**
 * काष्ठा ssam_nf_refcount_key - Key used क्रम event activation reference
 * counting.
 * @reg: The registry via which the event is enabled/disabled.
 * @id:  The ID uniquely describing the event.
 */
काष्ठा ssam_nf_refcount_key अणु
	काष्ठा ssam_event_registry reg;
	काष्ठा ssam_event_id id;
पूर्ण;

/**
 * काष्ठा ssam_nf_refcount_entry - RB-tree entry क्रम reference counting event
 * activations.
 * @node:     The node of this entry in the rb-tree.
 * @key:      The key of the event.
 * @refcount: The reference-count of the event.
 * @flags:    The flags used when enabling the event.
 */
काष्ठा ssam_nf_refcount_entry अणु
	काष्ठा rb_node node;
	काष्ठा ssam_nf_refcount_key key;
	पूर्णांक refcount;
	u8 flags;
पूर्ण;

/**
 * ssam_nf_refcount_inc() - Increment reference-/activation-count of the given
 * event.
 * @nf:  The notअगरier प्रणाली reference.
 * @reg: The registry used to enable/disable the event.
 * @id:  The event ID.
 *
 * Increments the reference-/activation-count associated with the specअगरied
 * event type/ID, allocating a new entry क्रम this event ID अगर necessary. A
 * newly allocated entry will have a refcount of one.
 *
 * Note: ``nf->lock`` must be held when calling this function.
 *
 * Return: Returns the refcount entry on success. Returns an error poपूर्णांकer
 * with %-ENOSPC अगर there have alपढ़ोy been %पूर्णांक_उच्च events of the specअगरied
 * ID and type रेजिस्टरed, or %-ENOMEM अगर the entry could not be allocated.
 */
अटल काष्ठा ssam_nf_refcount_entry *
ssam_nf_refcount_inc(काष्ठा ssam_nf *nf, काष्ठा ssam_event_registry reg,
		     काष्ठा ssam_event_id id)
अणु
	काष्ठा ssam_nf_refcount_entry *entry;
	काष्ठा ssam_nf_refcount_key key;
	काष्ठा rb_node **link = &nf->refcount.rb_node;
	काष्ठा rb_node *parent = शून्य;
	पूर्णांक cmp;

	lockdep_निश्चित_held(&nf->lock);

	key.reg = reg;
	key.id = id;

	जबतक (*link) अणु
		entry = rb_entry(*link, काष्ठा ssam_nf_refcount_entry, node);
		parent = *link;

		cmp = स_भेद(&key, &entry->key, माप(key));
		अगर (cmp < 0) अणु
			link = &(*link)->rb_left;
		पूर्ण अन्यथा अगर (cmp > 0) अणु
			link = &(*link)->rb_right;
		पूर्ण अन्यथा अगर (entry->refcount < पूर्णांक_उच्च) अणु
			entry->refcount++;
			वापस entry;
		पूर्ण अन्यथा अणु
			WARN_ON(1);
			वापस ERR_PTR(-ENOSPC);
		पूर्ण
	पूर्ण

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस ERR_PTR(-ENOMEM);

	entry->key = key;
	entry->refcount = 1;

	rb_link_node(&entry->node, parent, link);
	rb_insert_color(&entry->node, &nf->refcount);

	वापस entry;
पूर्ण

/**
 * ssam_nf_refcount_dec() - Decrement reference-/activation-count of the given
 * event.
 * @nf:  The notअगरier प्रणाली reference.
 * @reg: The registry used to enable/disable the event.
 * @id:  The event ID.
 *
 * Decrements the reference-/activation-count of the specअगरied event,
 * वापसing its entry. If the वापसed entry has a refcount of zero, the
 * caller is responsible क्रम मुक्तing it using kमुक्त().
 *
 * Note: ``nf->lock`` must be held when calling this function.
 *
 * Return: Returns the refcount entry on success or %शून्य अगर the entry has not
 * been found.
 */
अटल काष्ठा ssam_nf_refcount_entry *
ssam_nf_refcount_dec(काष्ठा ssam_nf *nf, काष्ठा ssam_event_registry reg,
		     काष्ठा ssam_event_id id)
अणु
	काष्ठा ssam_nf_refcount_entry *entry;
	काष्ठा ssam_nf_refcount_key key;
	काष्ठा rb_node *node = nf->refcount.rb_node;
	पूर्णांक cmp;

	lockdep_निश्चित_held(&nf->lock);

	key.reg = reg;
	key.id = id;

	जबतक (node) अणु
		entry = rb_entry(node, काष्ठा ssam_nf_refcount_entry, node);

		cmp = स_भेद(&key, &entry->key, माप(key));
		अगर (cmp < 0) अणु
			node = node->rb_left;
		पूर्ण अन्यथा अगर (cmp > 0) अणु
			node = node->rb_right;
		पूर्ण अन्यथा अणु
			entry->refcount--;
			अगर (entry->refcount == 0)
				rb_erase(&entry->node, &nf->refcount);

			वापस entry;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ssam_nf_refcount_empty() - Test अगर the notअगरication प्रणाली has any
 * enabled/active events.
 * @nf: The notअगरication प्रणाली.
 */
अटल bool ssam_nf_refcount_empty(काष्ठा ssam_nf *nf)
अणु
	वापस RB_EMPTY_ROOT(&nf->refcount);
पूर्ण

/**
 * ssam_nf_call() - Call notअगरication callbacks क्रम the provided event.
 * @nf:    The notअगरier प्रणाली
 * @dev:   The associated device, only used क्रम logging.
 * @rqid:  The request ID of the event.
 * @event: The event provided to the callbacks.
 *
 * Execute रेजिस्टरed callbacks in order of their priority until either no
 * callback is left or a callback वापसs a value with the %SSAM_NOTIF_STOP
 * bit set. Note that this bit is set स्वतःmatically when converting non-zero
 * error values via ssam_notअगरier_from_त्रुटि_सं() to notअगरier values.
 *
 * Also note that any callback that could handle an event should वापस a value
 * with bit %SSAM_NOTIF_HANDLED set, indicating that the event करोes not go
 * unhandled/ignored. In हाल no रेजिस्टरed callback could handle an event,
 * this function will emit a warning.
 *
 * In हाल a callback failed, this function will emit an error message.
 */
अटल व्योम ssam_nf_call(काष्ठा ssam_nf *nf, काष्ठा device *dev, u16 rqid,
			 काष्ठा ssam_event *event)
अणु
	काष्ठा ssam_nf_head *nf_head;
	पूर्णांक status, nf_ret;

	अगर (!ssh_rqid_is_event(rqid)) अणु
		dev_warn(dev, "event: unsupported rqid: %#06x\n", rqid);
		वापस;
	पूर्ण

	nf_head = &nf->head[ssh_rqid_to_event(rqid)];
	nf_ret = ssam_nfblk_call_chain(nf_head, event);
	status = ssam_notअगरier_to_त्रुटि_सं(nf_ret);

	अगर (status < 0) अणु
		dev_err(dev,
			"event: error handling event: %d (tc: %#04x, tid: %#04x, cid: %#04x, iid: %#04x)\n",
			status, event->target_category, event->target_id,
			event->command_id, event->instance_id);
	पूर्ण अन्यथा अगर (!(nf_ret & SSAM_NOTIF_HANDLED)) अणु
		dev_warn(dev,
			 "event: unhandled event (rqid: %#04x, tc: %#04x, tid: %#04x, cid: %#04x, iid: %#04x)\n",
			 rqid, event->target_category, event->target_id,
			 event->command_id, event->instance_id);
	पूर्ण
पूर्ण

/**
 * ssam_nf_init() - Initialize the notअगरier प्रणाली.
 * @nf: The notअगरier प्रणाली to initialize.
 */
अटल पूर्णांक ssam_nf_init(काष्ठा ssam_nf *nf)
अणु
	पूर्णांक i, status;

	क्रम (i = 0; i < SSH_NUM_EVENTS; i++) अणु
		status = ssam_nf_head_init(&nf->head[i]);
		अगर (status)
			अवरोध;
	पूर्ण

	अगर (status) अणु
		जबतक (i--)
			ssam_nf_head_destroy(&nf->head[i]);

		वापस status;
	पूर्ण

	mutex_init(&nf->lock);
	वापस 0;
पूर्ण

/**
 * ssam_nf_destroy() - Deinitialize the notअगरier प्रणाली.
 * @nf: The notअगरier प्रणाली to deinitialize.
 */
अटल व्योम ssam_nf_destroy(काष्ठा ssam_nf *nf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SSH_NUM_EVENTS; i++)
		ssam_nf_head_destroy(&nf->head[i]);

	mutex_destroy(&nf->lock);
पूर्ण


/* -- Event/async request completion प्रणाली. -------------------------------- */

#घोषणा SSAM_CPLT_WQ_NAME	"ssam_cpltq"

/*
 * SSAM_CPLT_WQ_BATCH - Maximum number of event item completions executed per
 * work execution. Used to prevent livelocking of the workqueue. Value chosen
 * via educated guess, may be adjusted.
 */
#घोषणा SSAM_CPLT_WQ_BATCH	10

/*
 * SSAM_EVENT_ITEM_CACHE_PAYLOAD_LEN - Maximum payload length क्रम a cached
 * &काष्ठा ssam_event_item.
 *
 * This length has been chosen to be accommodate standard touchpad and
 * keyboard input events. Events with larger payloads will be allocated
 * separately.
 */
#घोषणा SSAM_EVENT_ITEM_CACHE_PAYLOAD_LEN	32

अटल काष्ठा kmem_cache *ssam_event_item_cache;

/**
 * ssam_event_item_cache_init() - Initialize the event item cache.
 */
पूर्णांक ssam_event_item_cache_init(व्योम)
अणु
	स्थिर अचिन्हित पूर्णांक size = माप(काष्ठा ssam_event_item)
				  + SSAM_EVENT_ITEM_CACHE_PAYLOAD_LEN;
	स्थिर अचिन्हित पूर्णांक align = __alignof__(काष्ठा ssam_event_item);
	काष्ठा kmem_cache *cache;

	cache = kmem_cache_create("ssam_event_item", size, align, 0, शून्य);
	अगर (!cache)
		वापस -ENOMEM;

	ssam_event_item_cache = cache;
	वापस 0;
पूर्ण

/**
 * ssam_event_item_cache_destroy() - Deinitialize the event item cache.
 */
व्योम ssam_event_item_cache_destroy(व्योम)
अणु
	kmem_cache_destroy(ssam_event_item_cache);
	ssam_event_item_cache = शून्य;
पूर्ण

अटल व्योम __ssam_event_item_मुक्त_cached(काष्ठा ssam_event_item *item)
अणु
	kmem_cache_मुक्त(ssam_event_item_cache, item);
पूर्ण

अटल व्योम __ssam_event_item_मुक्त_generic(काष्ठा ssam_event_item *item)
अणु
	kमुक्त(item);
पूर्ण

/**
 * ssam_event_item_मुक्त() - Free the provided event item.
 * @item: The event item to मुक्त.
 */
अटल व्योम ssam_event_item_मुक्त(काष्ठा ssam_event_item *item)
अणु
	trace_ssam_event_item_मुक्त(item);
	item->ops.मुक्त(item);
पूर्ण

/**
 * ssam_event_item_alloc() - Allocate an event item with the given payload size.
 * @len:   The event payload length.
 * @flags: The flags used क्रम allocation.
 *
 * Allocate an event item with the given payload size, preferring allocation
 * from the event item cache अगर the payload is small enough (i.e. smaller than
 * %SSAM_EVENT_ITEM_CACHE_PAYLOAD_LEN). Sets the item operations and payload
 * length values. The item मुक्त callback (``ops.मुक्त``) should not be
 * overwritten after this call.
 *
 * Return: Returns the newly allocated event item.
 */
अटल काष्ठा ssam_event_item *ssam_event_item_alloc(माप_प्रकार len, gfp_t flags)
अणु
	काष्ठा ssam_event_item *item;

	अगर (len <= SSAM_EVENT_ITEM_CACHE_PAYLOAD_LEN) अणु
		item = kmem_cache_alloc(ssam_event_item_cache, flags);
		अगर (!item)
			वापस शून्य;

		item->ops.मुक्त = __ssam_event_item_मुक्त_cached;
	पूर्ण अन्यथा अणु
		item = kzalloc(काष्ठा_size(item, event.data, len), flags);
		अगर (!item)
			वापस शून्य;

		item->ops.मुक्त = __ssam_event_item_मुक्त_generic;
	पूर्ण

	item->event.length = len;

	trace_ssam_event_item_alloc(item, len);
	वापस item;
पूर्ण

/**
 * ssam_event_queue_push() - Push an event item to the event queue.
 * @q:    The event queue.
 * @item: The item to add.
 */
अटल व्योम ssam_event_queue_push(काष्ठा ssam_event_queue *q,
				  काष्ठा ssam_event_item *item)
अणु
	spin_lock(&q->lock);
	list_add_tail(&item->node, &q->head);
	spin_unlock(&q->lock);
पूर्ण

/**
 * ssam_event_queue_pop() - Pop the next event item from the event queue.
 * @q: The event queue.
 *
 * Returns and हटाओs the next event item from the queue. Returns %शून्य If
 * there is no event item left.
 */
अटल काष्ठा ssam_event_item *ssam_event_queue_pop(काष्ठा ssam_event_queue *q)
अणु
	काष्ठा ssam_event_item *item;

	spin_lock(&q->lock);
	item = list_first_entry_or_null(&q->head, काष्ठा ssam_event_item, node);
	अगर (item)
		list_del(&item->node);
	spin_unlock(&q->lock);

	वापस item;
पूर्ण

/**
 * ssam_event_queue_is_empty() - Check अगर the event queue is empty.
 * @q: The event queue.
 */
अटल bool ssam_event_queue_is_empty(काष्ठा ssam_event_queue *q)
अणु
	bool empty;

	spin_lock(&q->lock);
	empty = list_empty(&q->head);
	spin_unlock(&q->lock);

	वापस empty;
पूर्ण

/**
 * ssam_cplt_get_event_queue() - Get the event queue क्रम the given parameters.
 * @cplt: The completion प्रणाली on which to look क्रम the queue.
 * @tid:  The target ID of the queue.
 * @rqid: The request ID representing the event ID क्रम which to get the queue.
 *
 * Return: Returns the event queue corresponding to the event type described
 * by the given parameters. If the request ID करोes not represent an event,
 * this function वापसs %शून्य. If the target ID is not supported, this
 * function will fall back to the शेष target ID (``tid = 1``).
 */
अटल
काष्ठा ssam_event_queue *ssam_cplt_get_event_queue(काष्ठा ssam_cplt *cplt,
						   u8 tid, u16 rqid)
अणु
	u16 event = ssh_rqid_to_event(rqid);
	u16 tidx = ssh_tid_to_index(tid);

	अगर (!ssh_rqid_is_event(rqid)) अणु
		dev_err(cplt->dev, "event: unsupported request ID: %#06x\n", rqid);
		वापस शून्य;
	पूर्ण

	अगर (!ssh_tid_is_valid(tid)) अणु
		dev_warn(cplt->dev, "event: unsupported target ID: %u\n", tid);
		tidx = 0;
	पूर्ण

	वापस &cplt->event.target[tidx].queue[event];
पूर्ण

/**
 * ssam_cplt_submit() - Submit a work item to the completion प्रणाली workqueue.
 * @cplt: The completion प्रणाली.
 * @work: The work item to submit.
 */
अटल bool ssam_cplt_submit(काष्ठा ssam_cplt *cplt, काष्ठा work_काष्ठा *work)
अणु
	वापस queue_work(cplt->wq, work);
पूर्ण

/**
 * ssam_cplt_submit_event() - Submit an event to the completion प्रणाली.
 * @cplt: The completion प्रणाली.
 * @item: The event item to submit.
 *
 * Submits the event to the completion प्रणाली by queuing it on the event item
 * queue and queuing the respective event queue work item on the completion
 * workqueue, which will eventually complete the event.
 *
 * Return: Returns zero on success, %-EINVAL अगर there is no event queue that
 * can handle the given event item.
 */
अटल पूर्णांक ssam_cplt_submit_event(काष्ठा ssam_cplt *cplt,
				  काष्ठा ssam_event_item *item)
अणु
	काष्ठा ssam_event_queue *evq;

	evq = ssam_cplt_get_event_queue(cplt, item->event.target_id, item->rqid);
	अगर (!evq)
		वापस -EINVAL;

	ssam_event_queue_push(evq, item);
	ssam_cplt_submit(cplt, &evq->work);
	वापस 0;
पूर्ण

/**
 * ssam_cplt_flush() - Flush the completion प्रणाली.
 * @cplt: The completion प्रणाली.
 *
 * Flush the completion प्रणाली by रुकोing until all currently submitted work
 * items have been completed.
 *
 * Note: This function करोes not guarantee that all events will have been
 * handled once this call terminates. In हाल of a larger number of
 * to-be-completed events, the event queue work function may re-schedule its
 * work item, which this flush operation will ignore.
 *
 * This operation is only पूर्णांकended to, during normal operation prior to
 * shutकरोwn, try to complete most events and requests to get them out of the
 * प्रणाली जबतक the प्रणाली is still fully operational. It करोes not aim to
 * provide any guarantee that all of them have been handled.
 */
अटल व्योम ssam_cplt_flush(काष्ठा ssam_cplt *cplt)
अणु
	flush_workqueue(cplt->wq);
पूर्ण

अटल व्योम ssam_event_queue_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ssam_event_queue *queue;
	काष्ठा ssam_event_item *item;
	काष्ठा ssam_nf *nf;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक iterations = SSAM_CPLT_WQ_BATCH;

	queue = container_of(work, काष्ठा ssam_event_queue, work);
	nf = &queue->cplt->event.notअगर;
	dev = queue->cplt->dev;

	/* Limit number of processed events to aव्योम livelocking. */
	करो अणु
		item = ssam_event_queue_pop(queue);
		अगर (!item)
			वापस;

		ssam_nf_call(nf, dev, item->rqid, &item->event);
		ssam_event_item_मुक्त(item);
	पूर्ण जबतक (--iterations);

	अगर (!ssam_event_queue_is_empty(queue))
		ssam_cplt_submit(queue->cplt, &queue->work);
पूर्ण

/**
 * ssam_event_queue_init() - Initialize an event queue.
 * @cplt: The completion प्रणाली on which the queue resides.
 * @evq:  The event queue to initialize.
 */
अटल व्योम ssam_event_queue_init(काष्ठा ssam_cplt *cplt,
				  काष्ठा ssam_event_queue *evq)
अणु
	evq->cplt = cplt;
	spin_lock_init(&evq->lock);
	INIT_LIST_HEAD(&evq->head);
	INIT_WORK(&evq->work, ssam_event_queue_work_fn);
पूर्ण

/**
 * ssam_cplt_init() - Initialize completion प्रणाली.
 * @cplt: The completion प्रणाली to initialize.
 * @dev:  The device used क्रम logging.
 */
अटल पूर्णांक ssam_cplt_init(काष्ठा ssam_cplt *cplt, काष्ठा device *dev)
अणु
	काष्ठा ssam_event_target *target;
	पूर्णांक status, c, i;

	cplt->dev = dev;

	cplt->wq = create_workqueue(SSAM_CPLT_WQ_NAME);
	अगर (!cplt->wq)
		वापस -ENOMEM;

	क्रम (c = 0; c < ARRAY_SIZE(cplt->event.target); c++) अणु
		target = &cplt->event.target[c];

		क्रम (i = 0; i < ARRAY_SIZE(target->queue); i++)
			ssam_event_queue_init(cplt, &target->queue[i]);
	पूर्ण

	status = ssam_nf_init(&cplt->event.notअगर);
	अगर (status)
		destroy_workqueue(cplt->wq);

	वापस status;
पूर्ण

/**
 * ssam_cplt_destroy() - Deinitialize the completion प्रणाली.
 * @cplt: The completion प्रणाली to deinitialize.
 *
 * Deinitialize the given completion प्रणाली and ensure that all pending, i.e.
 * yet-to-be-completed, event items and requests have been handled.
 */
अटल व्योम ssam_cplt_destroy(काष्ठा ssam_cplt *cplt)
अणु
	/*
	 * Note: destroy_workqueue ensures that all currently queued work will
	 * be fully completed and the workqueue drained. This means that this
	 * call will inherently also मुक्त any queued ssam_event_items, thus we
	 * करोn't have to take care of that here explicitly.
	 */
	destroy_workqueue(cplt->wq);
	ssam_nf_destroy(&cplt->event.notअगर);
पूर्ण


/* -- Main SSAM device काष्ठाures. ------------------------------------------ */

/**
 * ssam_controller_device() - Get the &काष्ठा device associated with this
 * controller.
 * @c: The controller क्रम which to get the device.
 *
 * Return: Returns the &काष्ठा device associated with this controller,
 * providing its lower-level transport.
 */
काष्ठा device *ssam_controller_device(काष्ठा ssam_controller *c)
अणु
	वापस ssh_rtl_get_device(&c->rtl);
पूर्ण
EXPORT_SYMBOL_GPL(ssam_controller_device);

अटल व्योम __ssam_controller_release(काष्ठा kref *kref)
अणु
	काष्ठा ssam_controller *ctrl = to_ssam_controller(kref, kref);

	/*
	 * The lock-call here is to satisfy lockdep. At this poपूर्णांक we really
	 * expect this to be the last reमुख्यing reference to the controller.
	 * Anything अन्यथा is a bug.
	 */
	ssam_controller_lock(ctrl);
	ssam_controller_destroy(ctrl);
	ssam_controller_unlock(ctrl);

	kमुक्त(ctrl);
पूर्ण

/**
 * ssam_controller_get() - Increment reference count of controller.
 * @c: The controller.
 *
 * Return: Returns the controller provided as input.
 */
काष्ठा ssam_controller *ssam_controller_get(काष्ठा ssam_controller *c)
अणु
	अगर (c)
		kref_get(&c->kref);
	वापस c;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_controller_get);

/**
 * ssam_controller_put() - Decrement reference count of controller.
 * @c: The controller.
 */
व्योम ssam_controller_put(काष्ठा ssam_controller *c)
अणु
	अगर (c)
		kref_put(&c->kref, __ssam_controller_release);
पूर्ण
EXPORT_SYMBOL_GPL(ssam_controller_put);

/**
 * ssam_controller_statelock() - Lock the controller against state transitions.
 * @c: The controller to lock.
 *
 * Lock the controller against state transitions. Holding this lock guarantees
 * that the controller will not transition between states, i.e. अगर the
 * controller is in state "started", when this lock has been acquired, it will
 * reमुख्य in this state at least until the lock has been released.
 *
 * Multiple clients may concurrently hold this lock. In other words: The
 * ``statelock`` functions represent the पढ़ो-lock part of a r/w-semaphore.
 * Actions causing state transitions of the controller must be executed जबतक
 * holding the ग_लिखो-part of this r/w-semaphore (see ssam_controller_lock()
 * and ssam_controller_unlock() क्रम that).
 *
 * See ssam_controller_stateunlock() क्रम the corresponding unlock function.
 */
व्योम ssam_controller_statelock(काष्ठा ssam_controller *c)
अणु
	करोwn_पढ़ो(&c->lock);
पूर्ण
EXPORT_SYMBOL_GPL(ssam_controller_statelock);

/**
 * ssam_controller_stateunlock() - Unlock controller state transitions.
 * @c: The controller to unlock.
 *
 * See ssam_controller_statelock() क्रम the corresponding lock function.
 */
व्योम ssam_controller_stateunlock(काष्ठा ssam_controller *c)
अणु
	up_पढ़ो(&c->lock);
पूर्ण
EXPORT_SYMBOL_GPL(ssam_controller_stateunlock);

/**
 * ssam_controller_lock() - Acquire the मुख्य controller lock.
 * @c: The controller to lock.
 *
 * This lock must be held क्रम any state transitions, including transition to
 * suspend/resumed states and during shutकरोwn. See ssam_controller_statelock()
 * क्रम more details on controller locking.
 *
 * See ssam_controller_unlock() क्रम the corresponding unlock function.
 */
व्योम ssam_controller_lock(काष्ठा ssam_controller *c)
अणु
	करोwn_ग_लिखो(&c->lock);
पूर्ण

/*
 * ssam_controller_unlock() - Release the मुख्य controller lock.
 * @c: The controller to unlock.
 *
 * See ssam_controller_lock() क्रम the corresponding lock function.
 */
व्योम ssam_controller_unlock(काष्ठा ssam_controller *c)
अणु
	up_ग_लिखो(&c->lock);
पूर्ण

अटल व्योम ssam_handle_event(काष्ठा ssh_rtl *rtl,
			      स्थिर काष्ठा ssh_command *cmd,
			      स्थिर काष्ठा ssam_span *data)
अणु
	काष्ठा ssam_controller *ctrl = to_ssam_controller(rtl, rtl);
	काष्ठा ssam_event_item *item;

	item = ssam_event_item_alloc(data->len, GFP_KERNEL);
	अगर (!item)
		वापस;

	item->rqid = get_unaligned_le16(&cmd->rqid);
	item->event.target_category = cmd->tc;
	item->event.target_id = cmd->tid_in;
	item->event.command_id = cmd->cid;
	item->event.instance_id = cmd->iid;
	स_नकल(&item->event.data[0], data->ptr, data->len);

	अगर (WARN_ON(ssam_cplt_submit_event(&ctrl->cplt, item)))
		ssam_event_item_मुक्त(item);
पूर्ण

अटल स्थिर काष्ठा ssh_rtl_ops ssam_rtl_ops = अणु
	.handle_event = ssam_handle_event,
पूर्ण;

अटल bool ssam_notअगरier_is_empty(काष्ठा ssam_controller *ctrl);
अटल व्योम ssam_notअगरier_unरेजिस्टर_all(काष्ठा ssam_controller *ctrl);

#घोषणा SSAM_SSH_DSM_REVISION	0

/* d5e383e1-d892-4a76-89fc-f6aaae7ed5b5 */
अटल स्थिर guid_t SSAM_SSH_DSM_GUID =
	GUID_INIT(0xd5e383e1, 0xd892, 0x4a76,
		  0x89, 0xfc, 0xf6, 0xaa, 0xae, 0x7e, 0xd5, 0xb5);

क्रमागत ssh_dsm_fn अणु
	SSH_DSM_FN_SSH_POWER_PROखाता             = 0x05,
	SSH_DSM_FN_SCREEN_ON_SLEEP_IDLE_TIMEOUT  = 0x06,
	SSH_DSM_FN_SCREEN_OFF_SLEEP_IDLE_TIMEOUT = 0x07,
	SSH_DSM_FN_D3_CLOSES_HANDLE              = 0x08,
	SSH_DSM_FN_SSH_BUFFER_SIZE               = 0x09,
पूर्ण;

अटल पूर्णांक ssam_dsm_get_functions(acpi_handle handle, u64 *funcs)
अणु
	जोड़ acpi_object *obj;
	u64 mask = 0;
	पूर्णांक i;

	*funcs = 0;

	/*
	 * The _DSM function is only present on newer models. It is not
	 * present on 5th and 6th generation devices (i.e. up to and including
	 * Surface Pro 6, Surface Laptop 2, Surface Book 2).
	 *
	 * If the _DSM is not present, indicate that no function is supported.
	 * This will result in शेष values being set.
	 */
	अगर (!acpi_has_method(handle, "_DSM"))
		वापस 0;

	obj = acpi_evaluate_dsm_typed(handle, &SSAM_SSH_DSM_GUID,
				      SSAM_SSH_DSM_REVISION, 0, शून्य,
				      ACPI_TYPE_BUFFER);
	अगर (!obj)
		वापस -EIO;

	क्रम (i = 0; i < obj->buffer.length && i < 8; i++)
		mask |= (((u64)obj->buffer.poपूर्णांकer[i]) << (i * 8));

	अगर (mask & BIT(0))
		*funcs = mask;

	ACPI_FREE(obj);
	वापस 0;
पूर्ण

अटल पूर्णांक ssam_dsm_load_u32(acpi_handle handle, u64 funcs, u64 func, u32 *ret)
अणु
	जोड़ acpi_object *obj;
	u64 val;

	अगर (!(funcs & BIT_ULL(func)))
		वापस 0; /* Not supported, leave *ret at its शेष value */

	obj = acpi_evaluate_dsm_typed(handle, &SSAM_SSH_DSM_GUID,
				      SSAM_SSH_DSM_REVISION, func, शून्य,
				      ACPI_TYPE_INTEGER);
	अगर (!obj)
		वापस -EIO;

	val = obj->पूर्णांकeger.value;
	ACPI_FREE(obj);

	अगर (val > U32_MAX)
		वापस -दुस्फल;

	*ret = val;
	वापस 0;
पूर्ण

/**
 * ssam_controller_caps_load_from_acpi() - Load controller capabilities from
 * ACPI _DSM.
 * @handle: The handle of the ACPI controller/SSH device.
 * @caps:   Where to store the capabilities in.
 *
 * Initializes the given controller capabilities with शेष values, then
 * checks and, अगर the respective _DSM functions are available, loads the
 * actual capabilities from the _DSM.
 *
 * Return: Returns zero on success, a negative error code on failure.
 */
अटल
पूर्णांक ssam_controller_caps_load_from_acpi(acpi_handle handle,
					काष्ठा ssam_controller_caps *caps)
अणु
	u32 d3_बंदs_handle = false;
	u64 funcs;
	पूर्णांक status;

	/* Set शेषs. */
	caps->ssh_घातer_profile = U32_MAX;
	caps->screen_on_sleep_idle_समयout = U32_MAX;
	caps->screen_off_sleep_idle_समयout = U32_MAX;
	caps->d3_बंदs_handle = false;
	caps->ssh_buffer_size = U32_MAX;

	/* Pre-load supported DSM functions. */
	status = ssam_dsm_get_functions(handle, &funcs);
	अगर (status)
		वापस status;

	/* Load actual values from ACPI, अगर present. */
	status = ssam_dsm_load_u32(handle, funcs, SSH_DSM_FN_SSH_POWER_PROखाता,
				   &caps->ssh_घातer_profile);
	अगर (status)
		वापस status;

	status = ssam_dsm_load_u32(handle, funcs,
				   SSH_DSM_FN_SCREEN_ON_SLEEP_IDLE_TIMEOUT,
				   &caps->screen_on_sleep_idle_समयout);
	अगर (status)
		वापस status;

	status = ssam_dsm_load_u32(handle, funcs,
				   SSH_DSM_FN_SCREEN_OFF_SLEEP_IDLE_TIMEOUT,
				   &caps->screen_off_sleep_idle_समयout);
	अगर (status)
		वापस status;

	status = ssam_dsm_load_u32(handle, funcs, SSH_DSM_FN_D3_CLOSES_HANDLE,
				   &d3_बंदs_handle);
	अगर (status)
		वापस status;

	caps->d3_बंदs_handle = !!d3_बंदs_handle;

	status = ssam_dsm_load_u32(handle, funcs, SSH_DSM_FN_SSH_BUFFER_SIZE,
				   &caps->ssh_buffer_size);
	अगर (status)
		वापस status;

	वापस 0;
पूर्ण

/**
 * ssam_controller_init() - Initialize SSAM controller.
 * @ctrl:   The controller to initialize.
 * @serdev: The serial device representing the underlying data transport.
 *
 * Initializes the given controller. Does neither start receiver nor
 * transmitter thपढ़ोs. After this call, the controller has to be hooked up to
 * the serdev core separately via &काष्ठा serdev_device_ops, relaying calls to
 * ssam_controller_receive_buf() and ssam_controller_ग_लिखो_wakeup(). Once the
 * controller has been hooked up, transmitter and receiver thपढ़ोs may be
 * started via ssam_controller_start(). These setup steps need to be completed
 * beक्रमe controller can be used क्रम requests.
 */
पूर्णांक ssam_controller_init(काष्ठा ssam_controller *ctrl,
			 काष्ठा serdev_device *serdev)
अणु
	acpi_handle handle = ACPI_HANDLE(&serdev->dev);
	पूर्णांक status;

	init_rwsem(&ctrl->lock);
	kref_init(&ctrl->kref);

	status = ssam_controller_caps_load_from_acpi(handle, &ctrl->caps);
	अगर (status)
		वापस status;

	dev_dbg(&serdev->dev,
		"device capabilities:\n"
		"  ssh_power_profile:             %u\n"
		"  ssh_buffer_size:               %u\n"
		"  screen_on_sleep_idle_timeout:  %u\n"
		"  screen_off_sleep_idle_timeout: %u\n"
		"  d3_closes_handle:              %u\n",
		ctrl->caps.ssh_घातer_profile,
		ctrl->caps.ssh_buffer_size,
		ctrl->caps.screen_on_sleep_idle_समयout,
		ctrl->caps.screen_off_sleep_idle_समयout,
		ctrl->caps.d3_बंदs_handle);

	ssh_seq_reset(&ctrl->counter.seq);
	ssh_rqid_reset(&ctrl->counter.rqid);

	/* Initialize event/request completion प्रणाली. */
	status = ssam_cplt_init(&ctrl->cplt, &serdev->dev);
	अगर (status)
		वापस status;

	/* Initialize request and packet transport layers. */
	status = ssh_rtl_init(&ctrl->rtl, serdev, &ssam_rtl_ops);
	अगर (status) अणु
		ssam_cplt_destroy(&ctrl->cplt);
		वापस status;
	पूर्ण

	/*
	 * Set state via ग_लिखो_once even though we expect to be in an
	 * exclusive context, due to smoke-testing in
	 * ssam_request_sync_submit().
	 */
	WRITE_ONCE(ctrl->state, SSAM_CONTROLLER_INITIALIZED);
	वापस 0;
पूर्ण

/**
 * ssam_controller_start() - Start the receiver and transmitter thपढ़ोs of the
 * controller.
 * @ctrl: The controller.
 *
 * Note: When this function is called, the controller should be properly
 * hooked up to the serdev core via &काष्ठा serdev_device_ops. Please refer
 * to ssam_controller_init() क्रम more details on controller initialization.
 *
 * This function must be called with the मुख्य controller lock held (i.e. by
 * calling ssam_controller_lock()).
 */
पूर्णांक ssam_controller_start(काष्ठा ssam_controller *ctrl)
अणु
	पूर्णांक status;

	lockdep_निश्चित_held_ग_लिखो(&ctrl->lock);

	अगर (ctrl->state != SSAM_CONTROLLER_INITIALIZED)
		वापस -EINVAL;

	status = ssh_rtl_start(&ctrl->rtl);
	अगर (status)
		वापस status;

	/*
	 * Set state via ग_लिखो_once even though we expect to be locked/in an
	 * exclusive context, due to smoke-testing in
	 * ssam_request_sync_submit().
	 */
	WRITE_ONCE(ctrl->state, SSAM_CONTROLLER_STARTED);
	वापस 0;
पूर्ण

/*
 * SSAM_CTRL_SHUTDOWN_FLUSH_TIMEOUT - Timeout क्रम flushing requests during
 * shutकरोwn.
 *
 * Chosen to be larger than one full request समयout, including packets timing
 * out. This value should give ample समय to complete any outstanding requests
 * during normal operation and account क्रम the odd package समयout.
 */
#घोषणा SSAM_CTRL_SHUTDOWN_FLUSH_TIMEOUT	msecs_to_jअगरfies(5000)

/**
 * ssam_controller_shutकरोwn() - Shut करोwn the controller.
 * @ctrl: The controller.
 *
 * Shuts करोwn the controller by flushing all pending requests and stopping the
 * transmitter and receiver thपढ़ोs. All requests submitted after this call
 * will fail with %-ESHUTDOWN. While it is discouraged to करो so, this function
 * is safe to use in parallel with ongoing request submission.
 *
 * In the course of this shutकरोwn procedure, all currently रेजिस्टरed
 * notअगरiers will be unरेजिस्टरed. It is, however, strongly recommended to not
 * rely on this behavior, and instead the party रेजिस्टरing the notअगरier
 * should unरेजिस्टर it beक्रमe the controller माला_लो shut करोwn, e.g. via the
 * SSAM bus which guarantees client devices to be हटाओd beक्रमe a shutकरोwn.
 *
 * Note that events may still be pending after this call, but, due to the
 * notअगरiers being unरेजिस्टरed, these events will be dropped when the
 * controller is subsequently destroyed via ssam_controller_destroy().
 *
 * This function must be called with the मुख्य controller lock held (i.e. by
 * calling ssam_controller_lock()).
 */
व्योम ssam_controller_shutकरोwn(काष्ठा ssam_controller *ctrl)
अणु
	क्रमागत ssam_controller_state s = ctrl->state;
	पूर्णांक status;

	lockdep_निश्चित_held_ग_लिखो(&ctrl->lock);

	अगर (s == SSAM_CONTROLLER_UNINITIALIZED || s == SSAM_CONTROLLER_STOPPED)
		वापस;

	/*
	 * Try to flush pending events and requests जबतक everything still
	 * works. Note: There may still be packets and/or requests in the
	 * प्रणाली after this call (e.g. via control packets submitted by the
	 * packet transport layer or flush समयout / failure, ...). Those will
	 * be handled with the ssh_rtl_shutकरोwn() call below.
	 */
	status = ssh_rtl_flush(&ctrl->rtl, SSAM_CTRL_SHUTDOWN_FLUSH_TIMEOUT);
	अगर (status) अणु
		ssam_err(ctrl, "failed to flush request transport layer: %d\n",
			 status);
	पूर्ण

	/* Try to flush all currently completing requests and events. */
	ssam_cplt_flush(&ctrl->cplt);

	/*
	 * We expect all notअगरiers to have been हटाओd by the respective client
	 * driver that set them up at this poपूर्णांक. If this warning occurs, some
	 * client driver has not करोne that...
	 */
	WARN_ON(!ssam_notअगरier_is_empty(ctrl));

	/*
	 * Nevertheless, we should still take care of drivers that करोn't behave
	 * well. Thus disable all enabled events, unरेजिस्टर all notअगरiers.
	 */
	ssam_notअगरier_unरेजिस्टर_all(ctrl);

	/*
	 * Cancel reमुख्यing requests. Ensure no new ones can be queued and stop
	 * thपढ़ोs.
	 */
	ssh_rtl_shutकरोwn(&ctrl->rtl);

	/*
	 * Set state via ग_लिखो_once even though we expect to be locked/in an
	 * exclusive context, due to smoke-testing in
	 * ssam_request_sync_submit().
	 */
	WRITE_ONCE(ctrl->state, SSAM_CONTROLLER_STOPPED);
	ctrl->rtl.ptl.serdev = शून्य;
पूर्ण

/**
 * ssam_controller_destroy() - Destroy the controller and मुक्त its resources.
 * @ctrl: The controller.
 *
 * Ensures that all resources associated with the controller get मुक्तd. This
 * function should only be called after the controller has been stopped via
 * ssam_controller_shutकरोwn(). In general, this function should not be called
 * directly. The only valid place to call this function directly is during
 * initialization, beक्रमe the controller has been fully initialized and passed
 * to other processes. This function is called स्वतःmatically when the
 * reference count of the controller reaches zero.
 *
 * This function must be called with the मुख्य controller lock held (i.e. by
 * calling ssam_controller_lock()).
 */
व्योम ssam_controller_destroy(काष्ठा ssam_controller *ctrl)
अणु
	lockdep_निश्चित_held_ग_लिखो(&ctrl->lock);

	अगर (ctrl->state == SSAM_CONTROLLER_UNINITIALIZED)
		वापस;

	WARN_ON(ctrl->state != SSAM_CONTROLLER_STOPPED);

	/*
	 * Note: New events could still have been received after the previous
	 * flush in ssam_controller_shutकरोwn, beक्रमe the request transport layer
	 * has been shut करोwn. At this poपूर्णांक, after the shutकरोwn, we can be sure
	 * that no new events will be queued. The call to ssam_cplt_destroy will
	 * ensure that those reमुख्यing are being completed and मुक्तd.
	 */

	/* Actually मुक्त resources. */
	ssam_cplt_destroy(&ctrl->cplt);
	ssh_rtl_destroy(&ctrl->rtl);

	/*
	 * Set state via ग_लिखो_once even though we expect to be locked/in an
	 * exclusive context, due to smoke-testing in
	 * ssam_request_sync_submit().
	 */
	WRITE_ONCE(ctrl->state, SSAM_CONTROLLER_UNINITIALIZED);
पूर्ण

/**
 * ssam_controller_suspend() - Suspend the controller.
 * @ctrl: The controller to suspend.
 *
 * Marks the controller as suspended. Note that display-off and D0-निकास
 * notअगरications have to be sent manually beक्रमe transitioning the controller
 * पूर्णांकo the suspended state via this function.
 *
 * See ssam_controller_resume() क्रम the corresponding resume function.
 *
 * Return: Returns %-EINVAL अगर the controller is currently not in the
 * "started" state.
 */
पूर्णांक ssam_controller_suspend(काष्ठा ssam_controller *ctrl)
अणु
	ssam_controller_lock(ctrl);

	अगर (ctrl->state != SSAM_CONTROLLER_STARTED) अणु
		ssam_controller_unlock(ctrl);
		वापस -EINVAL;
	पूर्ण

	ssam_dbg(ctrl, "pm: suspending controller\n");

	/*
	 * Set state via ग_लिखो_once even though we're locked, due to
	 * smoke-testing in ssam_request_sync_submit().
	 */
	WRITE_ONCE(ctrl->state, SSAM_CONTROLLER_SUSPENDED);

	ssam_controller_unlock(ctrl);
	वापस 0;
पूर्ण

/**
 * ssam_controller_resume() - Resume the controller from suspend.
 * @ctrl: The controller to resume.
 *
 * Resume the controller from the suspended state it was put पूर्णांकo via
 * ssam_controller_suspend(). This function करोes not issue display-on and
 * D0-entry notअगरications. If required, those have to be sent manually after
 * this call.
 *
 * Return: Returns %-EINVAL अगर the controller is currently not suspended.
 */
पूर्णांक ssam_controller_resume(काष्ठा ssam_controller *ctrl)
अणु
	ssam_controller_lock(ctrl);

	अगर (ctrl->state != SSAM_CONTROLLER_SUSPENDED) अणु
		ssam_controller_unlock(ctrl);
		वापस -EINVAL;
	पूर्ण

	ssam_dbg(ctrl, "pm: resuming controller\n");

	/*
	 * Set state via ग_लिखो_once even though we're locked, due to
	 * smoke-testing in ssam_request_sync_submit().
	 */
	WRITE_ONCE(ctrl->state, SSAM_CONTROLLER_STARTED);

	ssam_controller_unlock(ctrl);
	वापस 0;
पूर्ण


/* -- Top-level request पूर्णांकerface ------------------------------------------- */

/**
 * ssam_request_ग_लिखो_data() - Conकाष्ठा and ग_लिखो SAM request message to
 * buffer.
 * @buf:  The buffer to ग_लिखो the data to.
 * @ctrl: The controller via which the request will be sent.
 * @spec: The request data and specअगरication.
 *
 * Conकाष्ठाs a SAM/SSH request message and ग_लिखोs it to the provided buffer.
 * The request and transport counters, specअगरically RQID and SEQ, will be set
 * in this call. These counters are obtained from the controller. It is thus
 * only valid to send the resulting message via the controller specअगरied here.
 *
 * For calculation of the required buffer size, refer to the
 * SSH_COMMAND_MESSAGE_LENGTH() macro.
 *
 * Return: Returns the number of bytes used in the buffer on success. Returns
 * %-EINVAL अगर the payload length provided in the request specअगरication is too
 * large (larger than %SSH_COMMAND_MAX_PAYLOAD_SIZE) or अगर the provided buffer
 * is too small.
 */
sमाप_प्रकार ssam_request_ग_लिखो_data(काष्ठा ssam_span *buf,
				काष्ठा ssam_controller *ctrl,
				स्थिर काष्ठा ssam_request *spec)
अणु
	काष्ठा msgbuf msgb;
	u16 rqid;
	u8 seq;

	अगर (spec->length > SSH_COMMAND_MAX_PAYLOAD_SIZE)
		वापस -EINVAL;

	अगर (SSH_COMMAND_MESSAGE_LENGTH(spec->length) > buf->len)
		वापस -EINVAL;

	msgb_init(&msgb, buf->ptr, buf->len);
	seq = ssh_seq_next(&ctrl->counter.seq);
	rqid = ssh_rqid_next(&ctrl->counter.rqid);
	msgb_push_cmd(&msgb, seq, rqid, spec);

	वापस msgb_bytes_used(&msgb);
पूर्ण
EXPORT_SYMBOL_GPL(ssam_request_ग_लिखो_data);

अटल व्योम ssam_request_sync_complete(काष्ठा ssh_request *rqst,
				       स्थिर काष्ठा ssh_command *cmd,
				       स्थिर काष्ठा ssam_span *data, पूर्णांक status)
अणु
	काष्ठा ssh_rtl *rtl = ssh_request_rtl(rqst);
	काष्ठा ssam_request_sync *r;

	r = container_of(rqst, काष्ठा ssam_request_sync, base);
	r->status = status;

	अगर (r->resp)
		r->resp->length = 0;

	अगर (status) अणु
		rtl_dbg_cond(rtl, "rsp: request failed: %d\n", status);
		वापस;
	पूर्ण

	अगर (!data)	/* Handle requests without a response. */
		वापस;

	अगर (!r->resp || !r->resp->poपूर्णांकer) अणु
		अगर (data->len)
			rtl_warn(rtl, "rsp: no response buffer provided, dropping data\n");
		वापस;
	पूर्ण

	अगर (data->len > r->resp->capacity) अणु
		rtl_err(rtl,
			"rsp: response buffer too small, capacity: %zu bytes, got: %zu bytes\n",
			r->resp->capacity, data->len);
		r->status = -ENOSPC;
		वापस;
	पूर्ण

	r->resp->length = data->len;
	स_नकल(r->resp->poपूर्णांकer, data->ptr, data->len);
पूर्ण

अटल व्योम ssam_request_sync_release(काष्ठा ssh_request *rqst)
अणु
	complete_all(&container_of(rqst, काष्ठा ssam_request_sync, base)->comp);
पूर्ण

अटल स्थिर काष्ठा ssh_request_ops ssam_request_sync_ops = अणु
	.release = ssam_request_sync_release,
	.complete = ssam_request_sync_complete,
पूर्ण;

/**
 * ssam_request_sync_alloc() - Allocate a synchronous request.
 * @payload_len: The length of the request payload.
 * @flags:       Flags used क्रम allocation.
 * @rqst:        Where to store the poपूर्णांकer to the allocated request.
 * @buffer:      Where to store the buffer descriptor क्रम the message buffer of
 *               the request.
 *
 * Allocates a synchronous request with corresponding message buffer. The
 * request still needs to be initialized ssam_request_sync_init() beक्रमe
 * it can be submitted, and the message buffer data must still be set to the
 * वापसed buffer via ssam_request_sync_set_data() after it has been filled,
 * अगर need be with adjusted message length.
 *
 * After use, the request and its corresponding message buffer should be मुक्तd
 * via ssam_request_sync_मुक्त(). The buffer must not be मुक्तd separately.
 *
 * Return: Returns zero on success, %-ENOMEM अगर the request could not be
 * allocated.
 */
पूर्णांक ssam_request_sync_alloc(माप_प्रकार payload_len, gfp_t flags,
			    काष्ठा ssam_request_sync **rqst,
			    काष्ठा ssam_span *buffer)
अणु
	माप_प्रकार msglen = SSH_COMMAND_MESSAGE_LENGTH(payload_len);

	*rqst = kzalloc(माप(**rqst) + msglen, flags);
	अगर (!*rqst)
		वापस -ENOMEM;

	buffer->ptr = (u8 *)(*rqst + 1);
	buffer->len = msglen;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_request_sync_alloc);

/**
 * ssam_request_sync_मुक्त() - Free a synchronous request.
 * @rqst: The request to be मुक्तd.
 *
 * Free a synchronous request and its corresponding buffer allocated with
 * ssam_request_sync_alloc(). Do not use क्रम requests allocated on the stack
 * or via any other function.
 *
 * Warning: The caller must ensure that the request is not in use any more.
 * I.e. the caller must ensure that it has the only reference to the request
 * and the request is not currently pending. This means that the caller has
 * either never submitted the request, request submission has failed, or the
 * caller has रुकोed until the submitted request has been completed via
 * ssam_request_sync_रुको().
 */
व्योम ssam_request_sync_मुक्त(काष्ठा ssam_request_sync *rqst)
अणु
	kमुक्त(rqst);
पूर्ण
EXPORT_SYMBOL_GPL(ssam_request_sync_मुक्त);

/**
 * ssam_request_sync_init() - Initialize a synchronous request काष्ठा.
 * @rqst:  The request to initialize.
 * @flags: The request flags.
 *
 * Initializes the given request काष्ठा. Does not initialize the request
 * message data. This has to be करोne explicitly after this call via
 * ssam_request_sync_set_data() and the actual message data has to be written
 * via ssam_request_ग_लिखो_data().
 *
 * Return: Returns zero on success or %-EINVAL अगर the given flags are invalid.
 */
पूर्णांक ssam_request_sync_init(काष्ठा ssam_request_sync *rqst,
			   क्रमागत ssam_request_flags flags)
अणु
	पूर्णांक status;

	status = ssh_request_init(&rqst->base, flags, &ssam_request_sync_ops);
	अगर (status)
		वापस status;

	init_completion(&rqst->comp);
	rqst->resp = शून्य;
	rqst->status = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_request_sync_init);

/**
 * ssam_request_sync_submit() - Submit a synchronous request.
 * @ctrl: The controller with which to submit the request.
 * @rqst: The request to submit.
 *
 * Submit a synchronous request. The request has to be initialized and
 * properly set up, including response buffer (may be %शून्य अगर no response is
 * expected) and command message data. This function करोes not रुको क्रम the
 * request to be completed.
 *
 * If this function succeeds, ssam_request_sync_रुको() must be used to ensure
 * that the request has been completed beक्रमe the response data can be
 * accessed and/or the request can be मुक्तd. On failure, the request may
 * immediately be मुक्तd.
 *
 * This function may only be used अगर the controller is active, i.e. has been
 * initialized and not suspended.
 */
पूर्णांक ssam_request_sync_submit(काष्ठा ssam_controller *ctrl,
			     काष्ठा ssam_request_sync *rqst)
अणु
	पूर्णांक status;

	/*
	 * This is only a superficial check. In general, the caller needs to
	 * ensure that the controller is initialized and is not (and करोes not
	 * get) suspended during use, i.e. until the request has been completed
	 * (अगर _असलolutely_ necessary, by use of ssam_controller_statelock/
	 * ssam_controller_stateunlock, but something like ssam_client_link
	 * should be preferred as this needs to last until the request has been
	 * completed).
	 *
	 * Note that it is actually safe to use this function जबतक the
	 * controller is in the process of being shut करोwn (as ssh_rtl_submit
	 * is safe with regards to this), but it is generally discouraged to करो
	 * so.
	 */
	अगर (WARN_ON(READ_ONCE(ctrl->state) != SSAM_CONTROLLER_STARTED)) अणु
		ssh_request_put(&rqst->base);
		वापस -ENODEV;
	पूर्ण

	status = ssh_rtl_submit(&ctrl->rtl, &rqst->base);
	ssh_request_put(&rqst->base);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_request_sync_submit);

/**
 * ssam_request_sync() - Execute a synchronous request.
 * @ctrl: The controller via which the request will be submitted.
 * @spec: The request specअगरication and payload.
 * @rsp:  The response buffer.
 *
 * Allocates a synchronous request with its message data buffer on the heap
 * via ssam_request_sync_alloc(), fully initializes it via the provided
 * request specअगरication, submits it, and finally रुकोs क्रम its completion
 * beक्रमe मुक्तing it and वापसing its status.
 *
 * Return: Returns the status of the request or any failure during setup.
 */
पूर्णांक ssam_request_sync(काष्ठा ssam_controller *ctrl,
		      स्थिर काष्ठा ssam_request *spec,
		      काष्ठा ssam_response *rsp)
अणु
	काष्ठा ssam_request_sync *rqst;
	काष्ठा ssam_span buf;
	sमाप_प्रकार len;
	पूर्णांक status;

	status = ssam_request_sync_alloc(spec->length, GFP_KERNEL, &rqst, &buf);
	अगर (status)
		वापस status;

	status = ssam_request_sync_init(rqst, spec->flags);
	अगर (status)
		वापस status;

	ssam_request_sync_set_resp(rqst, rsp);

	len = ssam_request_ग_लिखो_data(&buf, ctrl, spec);
	अगर (len < 0) अणु
		ssam_request_sync_मुक्त(rqst);
		वापस len;
	पूर्ण

	ssam_request_sync_set_data(rqst, buf.ptr, len);

	status = ssam_request_sync_submit(ctrl, rqst);
	अगर (!status)
		status = ssam_request_sync_रुको(rqst);

	ssam_request_sync_मुक्त(rqst);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_request_sync);

/**
 * ssam_request_sync_with_buffer() - Execute a synchronous request with the
 * provided buffer as back-end क्रम the message buffer.
 * @ctrl: The controller via which the request will be submitted.
 * @spec: The request specअगरication and payload.
 * @rsp:  The response buffer.
 * @buf:  The buffer क्रम the request message data.
 *
 * Allocates a synchronous request काष्ठा on the stack, fully initializes it
 * using the provided buffer as message data buffer, submits it, and then
 * रुकोs क्रम its completion beक्रमe वापसing its status. The
 * SSH_COMMAND_MESSAGE_LENGTH() macro can be used to compute the required
 * message buffer size.
 *
 * This function करोes essentially the same as ssam_request_sync(), but instead
 * of dynamically allocating the request and message data buffer, it uses the
 * provided message data buffer and stores the (small) request काष्ठा on the
 * heap.
 *
 * Return: Returns the status of the request or any failure during setup.
 */
पूर्णांक ssam_request_sync_with_buffer(काष्ठा ssam_controller *ctrl,
				  स्थिर काष्ठा ssam_request *spec,
				  काष्ठा ssam_response *rsp,
				  काष्ठा ssam_span *buf)
अणु
	काष्ठा ssam_request_sync rqst;
	sमाप_प्रकार len;
	पूर्णांक status;

	status = ssam_request_sync_init(&rqst, spec->flags);
	अगर (status)
		वापस status;

	ssam_request_sync_set_resp(&rqst, rsp);

	len = ssam_request_ग_लिखो_data(buf, ctrl, spec);
	अगर (len < 0)
		वापस len;

	ssam_request_sync_set_data(&rqst, buf->ptr, len);

	status = ssam_request_sync_submit(ctrl, &rqst);
	अगर (!status)
		status = ssam_request_sync_रुको(&rqst);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_request_sync_with_buffer);


/* -- Internal SAM requests. ------------------------------------------------ */

SSAM_DEFINE_SYNC_REQUEST_R(ssam_ssh_get_firmware_version, __le32, अणु
	.target_category = SSAM_SSH_TC_SAM,
	.target_id       = 0x01,
	.command_id      = 0x13,
	.instance_id     = 0x00,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_R(ssam_ssh_notअगर_display_off, u8, अणु
	.target_category = SSAM_SSH_TC_SAM,
	.target_id       = 0x01,
	.command_id      = 0x15,
	.instance_id     = 0x00,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_R(ssam_ssh_notअगर_display_on, u8, अणु
	.target_category = SSAM_SSH_TC_SAM,
	.target_id       = 0x01,
	.command_id      = 0x16,
	.instance_id     = 0x00,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_R(ssam_ssh_notअगर_d0_निकास, u8, अणु
	.target_category = SSAM_SSH_TC_SAM,
	.target_id       = 0x01,
	.command_id      = 0x33,
	.instance_id     = 0x00,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_R(ssam_ssh_notअगर_d0_entry, u8, अणु
	.target_category = SSAM_SSH_TC_SAM,
	.target_id       = 0x01,
	.command_id      = 0x34,
	.instance_id     = 0x00,
पूर्ण);

/**
 * काष्ठा ssh_notअगरication_params - Command payload to enable/disable SSH
 * notअगरications.
 * @target_category: The target category क्रम which notअगरications should be
 *                   enabled/disabled.
 * @flags:           Flags determining how notअगरications are being sent.
 * @request_id:      The request ID that is used to send these notअगरications.
 * @instance_id:     The specअगरic instance in the given target category क्रम
 *                   which notअगरications should be enabled.
 */
काष्ठा ssh_notअगरication_params अणु
	u8 target_category;
	u8 flags;
	__le16 request_id;
	u8 instance_id;
पूर्ण __packed;

अटल_निश्चित(माप(काष्ठा ssh_notअगरication_params) == 5);

अटल पूर्णांक __ssam_ssh_event_request(काष्ठा ssam_controller *ctrl,
				    काष्ठा ssam_event_registry reg, u8 cid,
				    काष्ठा ssam_event_id id, u8 flags)
अणु
	काष्ठा ssh_notअगरication_params params;
	काष्ठा ssam_request rqst;
	काष्ठा ssam_response result;
	पूर्णांक status;

	u16 rqid = ssh_tc_to_rqid(id.target_category);
	u8 buf = 0;

	/* Only allow RQIDs that lie within the event spectrum. */
	अगर (!ssh_rqid_is_event(rqid))
		वापस -EINVAL;

	params.target_category = id.target_category;
	params.instance_id = id.instance;
	params.flags = flags;
	put_unaligned_le16(rqid, &params.request_id);

	rqst.target_category = reg.target_category;
	rqst.target_id = reg.target_id;
	rqst.command_id = cid;
	rqst.instance_id = 0x00;
	rqst.flags = SSAM_REQUEST_HAS_RESPONSE;
	rqst.length = माप(params);
	rqst.payload = (u8 *)&params;

	result.capacity = माप(buf);
	result.length = 0;
	result.poपूर्णांकer = &buf;

	status = ssam_retry(ssam_request_sync_onstack, ctrl, &rqst, &result,
			    माप(params));

	वापस status < 0 ? status : buf;
पूर्ण

/**
 * ssam_ssh_event_enable() - Enable SSH event.
 * @ctrl:  The controller क्रम which to enable the event.
 * @reg:   The event registry describing what request to use क्रम enabling and
 *         disabling the event.
 * @id:    The event identअगरier.
 * @flags: The event flags.
 *
 * Enables the specअगरied event on the EC. This function करोes not manage
 * reference counting of enabled events and is basically only a wrapper क्रम
 * the raw EC request. If the specअगरied event is alपढ़ोy enabled, the EC will
 * ignore this request.
 *
 * Return: Returns the status of the executed SAM request (zero on success and
 * negative on direct failure) or %-EPROTO अगर the request response indicates a
 * failure.
 */
अटल पूर्णांक ssam_ssh_event_enable(काष्ठा ssam_controller *ctrl,
				 काष्ठा ssam_event_registry reg,
				 काष्ठा ssam_event_id id, u8 flags)
अणु
	पूर्णांक status;

	status = __ssam_ssh_event_request(ctrl, reg, reg.cid_enable, id, flags);

	अगर (status < 0 && status != -EINVAL) अणु
		ssam_err(ctrl,
			 "failed to enable event source (tc: %#04x, iid: %#04x, reg: %#04x)\n",
			 id.target_category, id.instance, reg.target_category);
	पूर्ण

	अगर (status > 0) अणु
		ssam_err(ctrl,
			 "unexpected result while enabling event source: %#04x (tc: %#04x, iid: %#04x, reg: %#04x)\n",
			 status, id.target_category, id.instance, reg.target_category);
		वापस -EPROTO;
	पूर्ण

	वापस status;
पूर्ण

/**
 * ssam_ssh_event_disable() - Disable SSH event.
 * @ctrl:  The controller क्रम which to disable the event.
 * @reg:   The event registry describing what request to use क्रम enabling and
 *         disabling the event (must be same as used when enabling the event).
 * @id:    The event identअगरier.
 * @flags: The event flags (likely ignored क्रम disabling of events).
 *
 * Disables the specअगरied event on the EC. This function करोes not manage
 * reference counting of enabled events and is basically only a wrapper क्रम
 * the raw EC request. If the specअगरied event is alपढ़ोy disabled, the EC will
 * ignore this request.
 *
 * Return: Returns the status of the executed SAM request (zero on success and
 * negative on direct failure) or %-EPROTO अगर the request response indicates a
 * failure.
 */
अटल पूर्णांक ssam_ssh_event_disable(काष्ठा ssam_controller *ctrl,
				  काष्ठा ssam_event_registry reg,
				  काष्ठा ssam_event_id id, u8 flags)
अणु
	पूर्णांक status;

	status = __ssam_ssh_event_request(ctrl, reg, reg.cid_disable, id, flags);

	अगर (status < 0 && status != -EINVAL) अणु
		ssam_err(ctrl,
			 "failed to disable event source (tc: %#04x, iid: %#04x, reg: %#04x)\n",
			 id.target_category, id.instance, reg.target_category);
	पूर्ण

	अगर (status > 0) अणु
		ssam_err(ctrl,
			 "unexpected result while disabling event source: %#04x (tc: %#04x, iid: %#04x, reg: %#04x)\n",
			 status, id.target_category, id.instance, reg.target_category);
		वापस -EPROTO;
	पूर्ण

	वापस status;
पूर्ण


/* -- Wrappers क्रम पूर्णांकernal SAM requests. ----------------------------------- */

/**
 * ssam_get_firmware_version() - Get the SAM/EC firmware version.
 * @ctrl:    The controller.
 * @version: Where to store the version number.
 *
 * Return: Returns zero on success or the status of the executed SAM request
 * अगर that request failed.
 */
पूर्णांक ssam_get_firmware_version(काष्ठा ssam_controller *ctrl, u32 *version)
अणु
	__le32 __version;
	पूर्णांक status;

	status = ssam_retry(ssam_ssh_get_firmware_version, ctrl, &__version);
	अगर (status)
		वापस status;

	*version = le32_to_cpu(__version);
	वापस 0;
पूर्ण

/**
 * ssam_ctrl_notअगर_display_off() - Notअगरy EC that the display has been turned
 * off.
 * @ctrl: The controller.
 *
 * Notअगरy the EC that the display has been turned off and the driver may enter
 * a lower-घातer state. This will prevent events from being sent directly.
 * Rather, the EC संकेतs an event by pulling the wakeup GPIO high क्रम as दीर्घ
 * as there are pending events. The events then need to be manually released,
 * one by one, via the GPIO callback request. All pending events accumulated
 * during this state can also be released by issuing the display-on
 * notअगरication, e.g. via ssam_ctrl_notअगर_display_on(), which will also reset
 * the GPIO.
 *
 * On some devices, specअगरically ones with an पूर्णांकegrated keyboard, the keyboard
 * backlight will be turned off by this call.
 *
 * This function will only send the display-off notअगरication command अगर
 * display notअगरications are supported by the EC. Currently all known devices
 * support these notअगरications.
 *
 * Use ssam_ctrl_notअगर_display_on() to reverse the effects of this function.
 *
 * Return: Returns zero on success or अगर no request has been executed, the
 * status of the executed SAM request अगर that request failed, or %-EPROTO अगर
 * an unexpected response has been received.
 */
पूर्णांक ssam_ctrl_notअगर_display_off(काष्ठा ssam_controller *ctrl)
अणु
	पूर्णांक status;
	u8 response;

	ssam_dbg(ctrl, "pm: notifying display off\n");

	status = ssam_retry(ssam_ssh_notअगर_display_off, ctrl, &response);
	अगर (status)
		वापस status;

	अगर (response != 0) अणु
		ssam_err(ctrl, "unexpected response from display-off notification: %#04x\n",
			 response);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ssam_ctrl_notअगर_display_on() - Notअगरy EC that the display has been turned on.
 * @ctrl: The controller.
 *
 * Notअगरy the EC that the display has been turned back on and the driver has
 * निकासed its lower-घातer state. This notअगरication is the counterpart to the
 * display-off notअगरication sent via ssam_ctrl_notअगर_display_off() and will
 * reverse its effects, including resetting events to their शेष behavior.
 *
 * This function will only send the display-on notअगरication command अगर display
 * notअगरications are supported by the EC. Currently all known devices support
 * these notअगरications.
 *
 * See ssam_ctrl_notअगर_display_off() क्रम more details.
 *
 * Return: Returns zero on success or अगर no request has been executed, the
 * status of the executed SAM request अगर that request failed, or %-EPROTO अगर
 * an unexpected response has been received.
 */
पूर्णांक ssam_ctrl_notअगर_display_on(काष्ठा ssam_controller *ctrl)
अणु
	पूर्णांक status;
	u8 response;

	ssam_dbg(ctrl, "pm: notifying display on\n");

	status = ssam_retry(ssam_ssh_notअगर_display_on, ctrl, &response);
	अगर (status)
		वापस status;

	अगर (response != 0) अणु
		ssam_err(ctrl, "unexpected response from display-on notification: %#04x\n",
			 response);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ssam_ctrl_notअगर_d0_निकास() - Notअगरy EC that the driver/device निकासs the D0
 * घातer state.
 * @ctrl: The controller
 *
 * Notअगरies the EC that the driver prepares to निकास the D0 घातer state in
 * favor of a lower-घातer state. Exact effects of this function related to the
 * EC are currently unknown.
 *
 * This function will only send the D0-निकास notअगरication command अगर D0-state
 * notअगरications are supported by the EC. Only newer Surface generations
 * support these notअगरications.
 *
 * Use ssam_ctrl_notअगर_d0_entry() to reverse the effects of this function.
 *
 * Return: Returns zero on success or अगर no request has been executed, the
 * status of the executed SAM request अगर that request failed, or %-EPROTO अगर
 * an unexpected response has been received.
 */
पूर्णांक ssam_ctrl_notअगर_d0_निकास(काष्ठा ssam_controller *ctrl)
अणु
	पूर्णांक status;
	u8 response;

	अगर (!ctrl->caps.d3_बंदs_handle)
		वापस 0;

	ssam_dbg(ctrl, "pm: notifying D0 exit\n");

	status = ssam_retry(ssam_ssh_notअगर_d0_निकास, ctrl, &response);
	अगर (status)
		वापस status;

	अगर (response != 0) अणु
		ssam_err(ctrl, "unexpected response from D0-exit notification: %#04x\n",
			 response);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ssam_ctrl_notअगर_d0_entry() - Notअगरy EC that the driver/device enters the D0
 * घातer state.
 * @ctrl: The controller
 *
 * Notअगरies the EC that the driver has निकासed a lower-घातer state and entered
 * the D0 घातer state. Exact effects of this function related to the EC are
 * currently unknown.
 *
 * This function will only send the D0-entry notअगरication command अगर D0-state
 * notअगरications are supported by the EC. Only newer Surface generations
 * support these notअगरications.
 *
 * See ssam_ctrl_notअगर_d0_निकास() क्रम more details.
 *
 * Return: Returns zero on success or अगर no request has been executed, the
 * status of the executed SAM request अगर that request failed, or %-EPROTO अगर
 * an unexpected response has been received.
 */
पूर्णांक ssam_ctrl_notअगर_d0_entry(काष्ठा ssam_controller *ctrl)
अणु
	पूर्णांक status;
	u8 response;

	अगर (!ctrl->caps.d3_बंदs_handle)
		वापस 0;

	ssam_dbg(ctrl, "pm: notifying D0 entry\n");

	status = ssam_retry(ssam_ssh_notअगर_d0_entry, ctrl, &response);
	अगर (status)
		वापस status;

	अगर (response != 0) अणु
		ssam_err(ctrl, "unexpected response from D0-entry notification: %#04x\n",
			 response);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण


/* -- Top-level event registry पूर्णांकerface. ----------------------------------- */

/**
 * ssam_notअगरier_रेजिस्टर() - Register an event notअगरier.
 * @ctrl: The controller to रेजिस्टर the notअगरier on.
 * @n:    The event notअगरier to रेजिस्टर.
 *
 * Register an event notअगरier and increment the usage counter of the
 * associated SAM event. If the event was previously not enabled, it will be
 * enabled during this call.
 *
 * Return: Returns zero on success, %-ENOSPC अगर there have alपढ़ोy been
 * %पूर्णांक_उच्च notअगरiers क्रम the event ID/type associated with the notअगरier block
 * रेजिस्टरed, %-ENOMEM अगर the corresponding event entry could not be
 * allocated. If this is the first समय that a notअगरier block is रेजिस्टरed
 * क्रम the specअगरic associated event, वापसs the status of the event-enable
 * EC-command.
 */
पूर्णांक ssam_notअगरier_रेजिस्टर(काष्ठा ssam_controller *ctrl,
			   काष्ठा ssam_event_notअगरier *n)
अणु
	u16 rqid = ssh_tc_to_rqid(n->event.id.target_category);
	काष्ठा ssam_nf_refcount_entry *entry;
	काष्ठा ssam_nf_head *nf_head;
	काष्ठा ssam_nf *nf;
	पूर्णांक status;

	अगर (!ssh_rqid_is_event(rqid))
		वापस -EINVAL;

	nf = &ctrl->cplt.event.notअगर;
	nf_head = &nf->head[ssh_rqid_to_event(rqid)];

	mutex_lock(&nf->lock);

	entry = ssam_nf_refcount_inc(nf, n->event.reg, n->event.id);
	अगर (IS_ERR(entry)) अणु
		mutex_unlock(&nf->lock);
		वापस PTR_ERR(entry);
	पूर्ण

	ssam_dbg(ctrl, "enabling event (reg: %#04x, tc: %#04x, iid: %#04x, rc: %d)\n",
		 n->event.reg.target_category, n->event.id.target_category,
		 n->event.id.instance, entry->refcount);

	status = ssam_nfblk_insert(nf_head, &n->base);
	अगर (status) अणु
		entry = ssam_nf_refcount_dec(nf, n->event.reg, n->event.id);
		अगर (entry->refcount == 0)
			kमुक्त(entry);

		mutex_unlock(&nf->lock);
		वापस status;
	पूर्ण

	अगर (entry->refcount == 1) अणु
		status = ssam_ssh_event_enable(ctrl, n->event.reg, n->event.id,
					       n->event.flags);
		अगर (status) अणु
			ssam_nfblk_हटाओ(&n->base);
			kमुक्त(ssam_nf_refcount_dec(nf, n->event.reg, n->event.id));
			mutex_unlock(&nf->lock);
			synchronize_srcu(&nf_head->srcu);
			वापस status;
		पूर्ण

		entry->flags = n->event.flags;

	पूर्ण अन्यथा अगर (entry->flags != n->event.flags) अणु
		ssam_warn(ctrl,
			  "inconsistent flags when enabling event: got %#04x, expected %#04x (reg: %#04x, tc: %#04x, iid: %#04x)\n",
			  n->event.flags, entry->flags, n->event.reg.target_category,
			  n->event.id.target_category, n->event.id.instance);
	पूर्ण

	mutex_unlock(&nf->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_notअगरier_रेजिस्टर);

/**
 * ssam_notअगरier_unरेजिस्टर() - Unरेजिस्टर an event notअगरier.
 * @ctrl: The controller the notअगरier has been रेजिस्टरed on.
 * @n:    The event notअगरier to unरेजिस्टर.
 *
 * Unरेजिस्टर an event notअगरier and decrement the usage counter of the
 * associated SAM event. If the usage counter reaches zero, the event will be
 * disabled.
 *
 * Return: Returns zero on success, %-ENOENT अगर the given notअगरier block has
 * not been रेजिस्टरed on the controller. If the given notअगरier block was the
 * last one associated with its specअगरic event, वापसs the status of the
 * event-disable EC-command.
 */
पूर्णांक ssam_notअगरier_unरेजिस्टर(काष्ठा ssam_controller *ctrl,
			     काष्ठा ssam_event_notअगरier *n)
अणु
	u16 rqid = ssh_tc_to_rqid(n->event.id.target_category);
	काष्ठा ssam_nf_refcount_entry *entry;
	काष्ठा ssam_nf_head *nf_head;
	काष्ठा ssam_nf *nf;
	पूर्णांक status = 0;

	अगर (!ssh_rqid_is_event(rqid))
		वापस -EINVAL;

	nf = &ctrl->cplt.event.notअगर;
	nf_head = &nf->head[ssh_rqid_to_event(rqid)];

	mutex_lock(&nf->lock);

	अगर (!ssam_nfblk_find(nf_head, &n->base)) अणु
		mutex_unlock(&nf->lock);
		वापस -ENOENT;
	पूर्ण

	entry = ssam_nf_refcount_dec(nf, n->event.reg, n->event.id);
	अगर (WARN_ON(!entry)) अणु
		/*
		 * If this करोes not वापस an entry, there's a logic error
		 * somewhere: The notअगरier block is रेजिस्टरed, but the event
		 * refcount entry is not there. Remove the notअगरier block
		 * anyways.
		 */
		status = -ENOENT;
		जाओ हटाओ;
	पूर्ण

	ssam_dbg(ctrl, "disabling event (reg: %#04x, tc: %#04x, iid: %#04x, rc: %d)\n",
		 n->event.reg.target_category, n->event.id.target_category,
		 n->event.id.instance, entry->refcount);

	अगर (entry->flags != n->event.flags) अणु
		ssam_warn(ctrl,
			  "inconsistent flags when disabling event: got %#04x, expected %#04x (reg: %#04x, tc: %#04x, iid: %#04x)\n",
			  n->event.flags, entry->flags, n->event.reg.target_category,
			  n->event.id.target_category, n->event.id.instance);
	पूर्ण

	अगर (entry->refcount == 0) अणु
		status = ssam_ssh_event_disable(ctrl, n->event.reg, n->event.id,
						n->event.flags);
		kमुक्त(entry);
	पूर्ण

हटाओ:
	ssam_nfblk_हटाओ(&n->base);
	mutex_unlock(&nf->lock);
	synchronize_srcu(&nf_head->srcu);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_notअगरier_unरेजिस्टर);

/**
 * ssam_notअगरier_disable_रेजिस्टरed() - Disable events क्रम all रेजिस्टरed
 * notअगरiers.
 * @ctrl: The controller क्रम which to disable the notअगरiers/events.
 *
 * Disables events क्रम all currently रेजिस्टरed notअगरiers. In हाल of an error
 * (EC command failing), all previously disabled events will be restored and
 * the error code वापसed.
 *
 * This function is पूर्णांकended to disable all events prior to hibernation entry.
 * See ssam_notअगरier_restore_रेजिस्टरed() to restore/re-enable all events
 * disabled with this function.
 *
 * Note that this function will not disable events क्रम notअगरiers रेजिस्टरed
 * after calling this function. It should thus be made sure that no new
 * notअगरiers are going to be added after this call and beक्रमe the corresponding
 * call to ssam_notअगरier_restore_रेजिस्टरed().
 *
 * Return: Returns zero on success. In हाल of failure वापसs the error code
 * वापसed by the failed EC command to disable an event.
 */
पूर्णांक ssam_notअगरier_disable_रेजिस्टरed(काष्ठा ssam_controller *ctrl)
अणु
	काष्ठा ssam_nf *nf = &ctrl->cplt.event.notअगर;
	काष्ठा rb_node *n;
	पूर्णांक status;

	mutex_lock(&nf->lock);
	क्रम (n = rb_first(&nf->refcount); n; n = rb_next(n)) अणु
		काष्ठा ssam_nf_refcount_entry *e;

		e = rb_entry(n, काष्ठा ssam_nf_refcount_entry, node);
		status = ssam_ssh_event_disable(ctrl, e->key.reg,
						e->key.id, e->flags);
		अगर (status)
			जाओ err;
	पूर्ण
	mutex_unlock(&nf->lock);

	वापस 0;

err:
	क्रम (n = rb_prev(n); n; n = rb_prev(n)) अणु
		काष्ठा ssam_nf_refcount_entry *e;

		e = rb_entry(n, काष्ठा ssam_nf_refcount_entry, node);
		ssam_ssh_event_enable(ctrl, e->key.reg, e->key.id, e->flags);
	पूर्ण
	mutex_unlock(&nf->lock);

	वापस status;
पूर्ण

/**
 * ssam_notअगरier_restore_रेजिस्टरed() - Restore/re-enable events क्रम all
 * रेजिस्टरed notअगरiers.
 * @ctrl: The controller क्रम which to restore the notअगरiers/events.
 *
 * Restores/re-enables all events क्रम which notअगरiers have been रेजिस्टरed on
 * the given controller. In हाल of a failure, the error is logged and the
 * function जारीs to try and enable the reमुख्यing events.
 *
 * This function is पूर्णांकended to restore/re-enable all रेजिस्टरed events after
 * hibernation. See ssam_notअगरier_disable_रेजिस्टरed() क्रम the counter part
 * disabling the events and more details.
 */
व्योम ssam_notअगरier_restore_रेजिस्टरed(काष्ठा ssam_controller *ctrl)
अणु
	काष्ठा ssam_nf *nf = &ctrl->cplt.event.notअगर;
	काष्ठा rb_node *n;

	mutex_lock(&nf->lock);
	क्रम (n = rb_first(&nf->refcount); n; n = rb_next(n)) अणु
		काष्ठा ssam_nf_refcount_entry *e;

		e = rb_entry(n, काष्ठा ssam_nf_refcount_entry, node);

		/* Ignore errors, will get logged in call. */
		ssam_ssh_event_enable(ctrl, e->key.reg, e->key.id, e->flags);
	पूर्ण
	mutex_unlock(&nf->lock);
पूर्ण

/**
 * ssam_notअगरier_is_empty() - Check अगर there are any रेजिस्टरed notअगरiers.
 * @ctrl: The controller to check on.
 *
 * Return: Returns %true अगर there are currently no notअगरiers रेजिस्टरed on the
 * controller, %false otherwise.
 */
अटल bool ssam_notअगरier_is_empty(काष्ठा ssam_controller *ctrl)
अणु
	काष्ठा ssam_nf *nf = &ctrl->cplt.event.notअगर;
	bool result;

	mutex_lock(&nf->lock);
	result = ssam_nf_refcount_empty(nf);
	mutex_unlock(&nf->lock);

	वापस result;
पूर्ण

/**
 * ssam_notअगरier_unरेजिस्टर_all() - Unरेजिस्टर all currently रेजिस्टरed
 * notअगरiers.
 * @ctrl: The controller to unरेजिस्टर the notअगरiers on.
 *
 * Unरेजिस्टरs all currently रेजिस्टरed notअगरiers. This function is used to
 * ensure that all notअगरiers will be unरेजिस्टरed and associated
 * entries/resources मुक्तd when the controller is being shut करोwn.
 */
अटल व्योम ssam_notअगरier_unरेजिस्टर_all(काष्ठा ssam_controller *ctrl)
अणु
	काष्ठा ssam_nf *nf = &ctrl->cplt.event.notअगर;
	काष्ठा ssam_nf_refcount_entry *e, *n;

	mutex_lock(&nf->lock);
	rbtree_postorder_क्रम_each_entry_safe(e, n, &nf->refcount, node) अणु
		/* Ignore errors, will get logged in call. */
		ssam_ssh_event_disable(ctrl, e->key.reg, e->key.id, e->flags);
		kमुक्त(e);
	पूर्ण
	nf->refcount = RB_ROOT;
	mutex_unlock(&nf->lock);
पूर्ण


/* -- Wakeup IRQ. ----------------------------------------------------------- */

अटल irqवापस_t ssam_irq_handle(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ssam_controller *ctrl = dev_id;

	ssam_dbg(ctrl, "pm: wake irq triggered\n");

	/*
	 * Note: Proper wakeup detection is currently unimplemented.
	 *       When the EC is in display-off or any other non-D0 state, it
	 *       करोes not send events/notअगरications to the host. Instead it
	 *       संकेतs that there are events available via the wakeup IRQ.
	 *       This driver is responsible क्रम calling back to the EC to
	 *       release these events one-by-one.
	 *
	 *       This IRQ should not cause a full प्रणाली resume by its own.
	 *       Instead, events should be handled by their respective subप्रणाली
	 *       drivers, which in turn should संकेत whether a full प्रणाली
	 *       resume should be perक्रमmed.
	 *
	 * TODO: Send GPIO callback command repeatedly to EC until callback
	 *       वापसs 0x00. Return flag of callback is "has more events".
	 *       Each समय the command is sent, one event is "released". Once
	 *       all events have been released (वापस = 0x00), the GPIO is
	 *       re-armed. Detect wakeup events during this process, go back to
	 *       sleep अगर no wakeup event has been received.
	 */

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ssam_irq_setup() - Set up SAM EC wakeup-GPIO पूर्णांकerrupt.
 * @ctrl: The controller क्रम which the IRQ should be set up.
 *
 * Set up an IRQ क्रम the wakeup-GPIO pin of the SAM EC. This IRQ can be used
 * to wake the device from a low घातer state.
 *
 * Note that this IRQ can only be triggered जबतक the EC is in the display-off
 * state. In this state, events are not sent to the host in the usual way.
 * Instead the wakeup-GPIO माला_लो pulled to "high" as दीर्घ as there are pending
 * events and these events need to be released one-by-one via the GPIO
 * callback request, either until there are no events left and the GPIO is
 * reset, or all at once by transitioning the EC out of the display-off state,
 * which will also clear the GPIO.
 *
 * Not all events, however, should trigger a full प्रणाली wakeup. Instead the
 * driver should, अगर necessary, inspect and क्रमward each event to the
 * corresponding subप्रणाली, which in turn should decide अगर the प्रणाली needs to
 * be woken up. This logic has not been implemented yet, thus wakeup by this
 * IRQ should be disabled by शेष to aव्योम spurious wake-ups, caused, क्रम
 * example, by the reमुख्यing battery percentage changing. Refer to comments in
 * this function and comments in the corresponding IRQ handler क्रम more
 * details on how this should be implemented.
 *
 * See also ssam_ctrl_notअगर_display_off() and ssam_ctrl_notअगर_display_off()
 * क्रम functions to transition the EC पूर्णांकo and out of the display-off state as
 * well as more details on it.
 *
 * The IRQ is disabled by शेष and has to be enabled beक्रमe it can wake up
 * the device from suspend via ssam_irq_arm_क्रम_wakeup(). On tearकरोwn, the IRQ
 * should be मुक्तd via ssam_irq_मुक्त().
 */
पूर्णांक ssam_irq_setup(काष्ठा ssam_controller *ctrl)
अणु
	काष्ठा device *dev = ssam_controller_device(ctrl);
	काष्ठा gpio_desc *gpiod;
	पूर्णांक irq;
	पूर्णांक status;

	/*
	 * The actual GPIO पूर्णांकerrupt is declared in ACPI as TRIGGER_HIGH.
	 * However, the GPIO line only माला_लो reset by sending the GPIO callback
	 * command to SAM (or alternatively the display-on notअगरication). As
	 * proper handling क्रम this पूर्णांकerrupt is not implemented yet, leaving
	 * the IRQ at TRIGGER_HIGH would cause an IRQ storm (as the callback
	 * never माला_लो sent and thus the line never माला_लो reset). To aव्योम this,
	 * mark the IRQ as TRIGGER_RISING क्रम now, only creating a single
	 * पूर्णांकerrupt, and let the SAM resume callback during the controller
	 * resume process clear it.
	 */
	स्थिर पूर्णांक irqf = IRQF_ONESHOT | IRQF_TRIGGER_RISING | IRQF_NO_AUTOEN;

	gpiod = gpiod_get(dev, "ssam_wakeup-int", GPIOD_ASIS);
	अगर (IS_ERR(gpiod))
		वापस PTR_ERR(gpiod);

	irq = gpiod_to_irq(gpiod);
	gpiod_put(gpiod);

	अगर (irq < 0)
		वापस irq;

	status = request_thपढ़ोed_irq(irq, शून्य, ssam_irq_handle, irqf,
				      "ssam_wakeup", ctrl);
	अगर (status)
		वापस status;

	ctrl->irq.num = irq;
	वापस 0;
पूर्ण

/**
 * ssam_irq_मुक्त() - Free SAM EC wakeup-GPIO पूर्णांकerrupt.
 * @ctrl: The controller क्रम which the IRQ should be मुक्तd.
 *
 * Free the wakeup-GPIO IRQ previously set-up via ssam_irq_setup().
 */
व्योम ssam_irq_मुक्त(काष्ठा ssam_controller *ctrl)
अणु
	मुक्त_irq(ctrl->irq.num, ctrl);
	ctrl->irq.num = -1;
पूर्ण

/**
 * ssam_irq_arm_क्रम_wakeup() - Arm the EC IRQ क्रम wakeup, अगर enabled.
 * @ctrl: The controller क्रम which the IRQ should be armed.
 *
 * Sets up the IRQ so that it can be used to wake the device. Specअगरically,
 * this function enables the irq and then, अगर the device is allowed to wake up
 * the प्रणाली, calls enable_irq_wake(). See ssam_irq_disarm_wakeup() क्रम the
 * corresponding function to disable the IRQ.
 *
 * This function is पूर्णांकended to arm the IRQ beक्रमe entering S2idle suspend.
 *
 * Note: calls to ssam_irq_arm_क्रम_wakeup() and ssam_irq_disarm_wakeup() must
 * be balanced.
 */
पूर्णांक ssam_irq_arm_क्रम_wakeup(काष्ठा ssam_controller *ctrl)
अणु
	काष्ठा device *dev = ssam_controller_device(ctrl);
	पूर्णांक status;

	enable_irq(ctrl->irq.num);
	अगर (device_may_wakeup(dev)) अणु
		status = enable_irq_wake(ctrl->irq.num);
		अगर (status) अणु
			ssam_err(ctrl, "failed to enable wake IRQ: %d\n", status);
			disable_irq(ctrl->irq.num);
			वापस status;
		पूर्ण

		ctrl->irq.wakeup_enabled = true;
	पूर्ण अन्यथा अणु
		ctrl->irq.wakeup_enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ssam_irq_disarm_wakeup() - Disarm the wakeup IRQ.
 * @ctrl: The controller क्रम which the IRQ should be disarmed.
 *
 * Disarm the IRQ previously set up क्रम wake via ssam_irq_arm_क्रम_wakeup().
 *
 * This function is पूर्णांकended to disarm the IRQ after निकासing S2idle suspend.
 *
 * Note: calls to ssam_irq_arm_क्रम_wakeup() and ssam_irq_disarm_wakeup() must
 * be balanced.
 */
व्योम ssam_irq_disarm_wakeup(काष्ठा ssam_controller *ctrl)
अणु
	पूर्णांक status;

	अगर (ctrl->irq.wakeup_enabled) अणु
		status = disable_irq_wake(ctrl->irq.num);
		अगर (status)
			ssam_err(ctrl, "failed to disable wake IRQ: %d\n", status);

		ctrl->irq.wakeup_enabled = false;
	पूर्ण
	disable_irq(ctrl->irq.num);
पूर्ण
