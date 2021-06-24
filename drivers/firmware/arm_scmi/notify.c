<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) Notअगरication support
 *
 * Copyright (C) 2020-2021 ARM Ltd.
 */
/**
 * DOC: Theory of operation
 *
 * SCMI Protocol specअगरication allows the platक्रमm to संकेत events to
 * पूर्णांकerested agents via notअगरication messages: this is an implementation
 * of the dispatch and delivery of such notअगरications to the पूर्णांकerested users
 * inside the Linux kernel.
 *
 * An SCMI Notअगरication core instance is initialized क्रम each active platक्रमm
 * instance identअगरied by the means of the usual &काष्ठा scmi_handle.
 *
 * Each SCMI Protocol implementation, during its initialization, रेजिस्टरs with
 * this core its set of supported events using scmi_रेजिस्टर_protocol_events():
 * all the needed descriptors are stored in the &काष्ठा रेजिस्टरed_protocols and
 * &काष्ठा रेजिस्टरed_events arrays.
 *
 * Kernel users पूर्णांकerested in some specअगरic event can रेजिस्टर their callbacks
 * providing the usual notअगरier_block descriptor, since this core implements
 * events' delivery using the standard Kernel notअगरication chains machinery.
 *
 * Given the number of possible events defined by SCMI and the extensibility
 * of the SCMI Protocol itself, the underlying notअगरication chains are created
 * and destroyed dynamically on demand depending on the number of users
 * effectively रेजिस्टरed क्रम an event, so that no support काष्ठाures or chains
 * are allocated until at least one user has रेजिस्टरed a notअगरier_block क्रम
 * such event. Similarly, events' generation itself is enabled at the platक्रमm
 * level only after at least one user has रेजिस्टरed, and it is shutकरोwn after
 * the last user क्रम that event has gone.
 *
 * All users provided callbacks and allocated notअगरication-chains are stored in
 * the @रेजिस्टरed_events_handlers hashtable. Callbacks' registration requests
 * क्रम still to be रेजिस्टरed events are instead kept in the dedicated common
 * hashtable @pending_events_handlers.
 *
 * An event is identअगरied univocally by the tuple (proto_id, evt_id, src_id)
 * and is served by its own dedicated notअगरication chain; inक्रमmation contained
 * in such tuples is used, in a few dअगरferent ways, to generate the needed
 * hash-keys.
 *
 * Here proto_id and evt_id are simply the protocol_id and message_id numbers
 * as described in the SCMI Protocol specअगरication, जबतक src_id represents an
 * optional, protocol dependent, source identअगरier (like करोमुख्य_id, perf_id
 * or sensor_id and so क्रमth).
 *
 * Upon reception of a notअगरication message from the platक्रमm the SCMI RX ISR
 * passes the received message payload and some ancillary inक्रमmation (including
 * an arrival बारtamp in nanoseconds) to the core via @scmi_notअगरy() which
 * pushes the event-data itself on a protocol-dedicated kfअगरo queue क्रम further
 * deferred processing as specअगरied in @scmi_events_dispatcher().
 *
 * Each protocol has it own dedicated work_काष्ठा and worker which, once kicked
 * by the ISR, takes care to empty its own dedicated queue, deliverying the
 * queued items पूर्णांकo the proper notअगरication-chain: notअगरications processing can
 * proceed concurrently on distinct workers only between events beदीर्घing to
 * dअगरferent protocols जबतक delivery of events within the same protocol is
 * still strictly sequentially ordered by समय of arrival.
 *
 * Events' inक्रमmation is then extracted from the SCMI Notअगरication messages and
 * conveyed, converted पूर्णांकo a custom per-event report काष्ठा, as the व्योम *data
 * param to the user callback provided by the रेजिस्टरed notअगरier_block, so that
 * from the user perspective his callback will look invoked like:
 *
 * पूर्णांक user_cb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event_id, व्योम *report)
 *
 */

#घोषणा dev_fmt(fmt) "SCMI Notifications - " fmt
#घोषणा pr_fmt(fmt) "SCMI Notifications - " fmt

#समावेश <linux/bitfield.h>
#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/refcount.h>
#समावेश <linux/scmi_protocol.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश "common.h"
#समावेश "notify.h"

#घोषणा SCMI_MAX_PROTO		256

#घोषणा PROTO_ID_MASK		GENMASK(31, 24)
#घोषणा EVT_ID_MASK		GENMASK(23, 16)
#घोषणा SRC_ID_MASK		GENMASK(15, 0)

/*
 * Builds an अचिन्हित 32bit key from the given input tuple to be used
 * as a key in hashtables.
 */
#घोषणा MAKE_HASH_KEY(p, e, s)			\
	(FIELD_PREP(PROTO_ID_MASK, (p)) |	\
	   FIELD_PREP(EVT_ID_MASK, (e)) |	\
	   FIELD_PREP(SRC_ID_MASK, (s)))

#घोषणा MAKE_ALL_SRCS_KEY(p, e)		MAKE_HASH_KEY((p), (e), SRC_ID_MASK)

/*
 * Assumes that the stored obj includes its own hash-key in a field named 'key':
 * with this simplअगरication this macro can be equally used क्रम all the objects'
 * types hashed by this implementation.
 *
 * @__ht: The hashtable name
 * @__obj: A poपूर्णांकer to the object type to be retrieved from the hashtable;
 *	   it will be used as a cursor जबतक scanning the hastable and it will
 *	   be possibly left as शून्य when @__k is not found
 * @__k: The key to search क्रम
 */
#घोषणा KEY_FIND(__ht, __obj, __k)				\
(अणु								\
	typeof(__k) k_ = __k;					\
	typeof(__obj) obj_;					\
								\
	hash_क्रम_each_possible((__ht), obj_, hash, k_)		\
		अगर (obj_->key == k_)				\
			अवरोध;					\
	__obj = obj_;						\
पूर्ण)

#घोषणा KEY_XTRACT_PROTO_ID(key)	FIELD_GET(PROTO_ID_MASK, (key))
#घोषणा KEY_XTRACT_EVT_ID(key)		FIELD_GET(EVT_ID_MASK, (key))
#घोषणा KEY_XTRACT_SRC_ID(key)		FIELD_GET(SRC_ID_MASK, (key))

/*
 * A set of macros used to access safely @रेजिस्टरed_protocols and
 * @रेजिस्टरed_events arrays; these are fixed in size and each entry is possibly
 * populated at protocols' registration समय and then only पढ़ो but NEVER
 * modअगरied or हटाओd.
 */
#घोषणा SCMI_GET_PROTO(__ni, __pid)					\
(अणु									\
	typeof(__ni) ni_ = __ni;					\
	काष्ठा scmi_रेजिस्टरed_events_desc *__pd = शून्य;		\
									\
	अगर (ni_)							\
		__pd = READ_ONCE(ni_->रेजिस्टरed_protocols[(__pid)]);	\
	__pd;								\
पूर्ण)

#घोषणा SCMI_GET_REVT_FROM_PD(__pd, __eid)				\
(अणु									\
	typeof(__pd) pd_ = __pd;					\
	typeof(__eid) eid_ = __eid;					\
	काष्ठा scmi_रेजिस्टरed_event *__revt = शून्य;			\
									\
	अगर (pd_ && eid_ < pd_->num_events)				\
		__revt = READ_ONCE(pd_->रेजिस्टरed_events[eid_]);	\
	__revt;								\
पूर्ण)

#घोषणा SCMI_GET_REVT(__ni, __pid, __eid)				\
(अणु									\
	काष्ठा scmi_रेजिस्टरed_event *__revt;				\
	काष्ठा scmi_रेजिस्टरed_events_desc *__pd;			\
									\
	__pd = SCMI_GET_PROTO((__ni), (__pid));				\
	__revt = SCMI_GET_REVT_FROM_PD(__pd, (__eid));			\
	__revt;								\
पूर्ण)

/* A couple of utility macros to limit cruft when calling protocols' helpers */
#घोषणा REVT_NOTIFY_SET_STATUS(revt, eid, sid, state)		\
(अणु								\
	typeof(revt) r = revt;					\
	r->proto->ops->set_notअगरy_enabled(r->proto->ph,		\
					(eid), (sid), (state));	\
पूर्ण)

#घोषणा REVT_NOTIFY_ENABLE(revt, eid, sid)			\
	REVT_NOTIFY_SET_STATUS((revt), (eid), (sid), true)

#घोषणा REVT_NOTIFY_DISABLE(revt, eid, sid)			\
	REVT_NOTIFY_SET_STATUS((revt), (eid), (sid), false)

#घोषणा REVT_FILL_REPORT(revt, ...)				\
(अणु								\
	typeof(revt) r = revt;					\
	r->proto->ops->fill_custom_report(r->proto->ph,		\
					  __VA_ARGS__);		\
पूर्ण)

#घोषणा SCMI_PENDING_HASH_SZ		4
#घोषणा SCMI_REGISTERED_HASH_SZ		6

काष्ठा scmi_रेजिस्टरed_events_desc;

/**
 * काष्ठा scmi_notअगरy_instance  - Represents an instance of the notअगरication
 * core
 * @gid: GroupID used क्रम devres
 * @handle: A reference to the platक्रमm instance
 * @init_work: A work item to perक्रमm final initializations of pending handlers
 * @notअगरy_wq: A reference to the allocated Kernel cmwq
 * @pending_mtx: A mutex to protect @pending_events_handlers
 * @रेजिस्टरed_protocols: A अटलally allocated array containing poपूर्णांकers to
 *			  all the रेजिस्टरed protocol-level specअगरic inक्रमmation
 *			  related to events' handling
 * @pending_events_handlers: An hashtable containing all pending events'
 *			     handlers descriptors
 *
 * Each platक्रमm instance, represented by a handle, has its own instance of
 * the notअगरication subप्रणाली represented by this काष्ठाure.
 */
काष्ठा scmi_notअगरy_instance अणु
	व्योम			*gid;
	काष्ठा scmi_handle	*handle;
	काष्ठा work_काष्ठा	init_work;
	काष्ठा workqueue_काष्ठा	*notअगरy_wq;
	/* lock to protect pending_events_handlers */
	काष्ठा mutex		pending_mtx;
	काष्ठा scmi_रेजिस्टरed_events_desc	**रेजिस्टरed_protocols;
	DECLARE_HASHTABLE(pending_events_handlers, SCMI_PENDING_HASH_SZ);
पूर्ण;

/**
 * काष्ठा events_queue  - Describes a queue and its associated worker
 * @sz: Size in bytes of the related kfअगरo
 * @kfअगरo: A dedicated Kernel kfअगरo descriptor
 * @notअगरy_work: A custom work item bound to this queue
 * @wq: A reference to the associated workqueue
 *
 * Each protocol has its own dedicated events_queue descriptor.
 */
काष्ठा events_queue अणु
	माप_प्रकार			sz;
	काष्ठा kfअगरo		kfअगरo;
	काष्ठा work_काष्ठा	notअगरy_work;
	काष्ठा workqueue_काष्ठा	*wq;
पूर्ण;

/**
 * काष्ठा scmi_event_header  - A utility header
 * @बारtamp: The बारtamp, in nanoseconds (bootसमय), which was associated
 *	       to this event as soon as it entered the SCMI RX ISR
 * @payld_sz: Effective size of the embedded message payload which follows
 * @evt_id: Event ID (corresponds to the Event MsgID क्रम this Protocol)
 * @payld: A reference to the embedded event payload
 *
 * This header is prepended to each received event message payload beक्रमe
 * queueing it on the related &काष्ठा events_queue.
 */
काष्ठा scmi_event_header अणु
	kसमय_प्रकार बारtamp;
	माप_प्रकार payld_sz;
	अचिन्हित अक्षर evt_id;
	अचिन्हित अक्षर payld[];
पूर्ण;

काष्ठा scmi_रेजिस्टरed_event;

/**
 * काष्ठा scmi_रेजिस्टरed_events_desc  - Protocol Specअगरic inक्रमmation
 * @id: Protocol ID
 * @ops: Protocol specअगरic and event-related operations
 * @equeue: The embedded per-protocol events_queue
 * @ni: A reference to the initialized instance descriptor
 * @eh: A reference to pre-allocated buffer to be used as a scratch area by the
 *	deferred worker when fetching data from the kfअगरo
 * @eh_sz: Size of the pre-allocated buffer @eh
 * @in_flight: A reference to an in flight &काष्ठा scmi_रेजिस्टरed_event
 * @num_events: Number of events in @रेजिस्टरed_events
 * @रेजिस्टरed_events: A dynamically allocated array holding all the रेजिस्टरed
 *		       events' descriptors, whose fixed-size is determined at
 *		       compile समय.
 * @रेजिस्टरed_mtx: A mutex to protect @रेजिस्टरed_events_handlers
 * @ph: SCMI protocol handle reference
 * @रेजिस्टरed_events_handlers: An hashtable containing all events' handlers
 *				descriptors रेजिस्टरed क्रम this protocol
 *
 * All protocols that रेजिस्टर at least one event have their protocol-specअगरic
 * inक्रमmation stored here, together with the embedded allocated events_queue.
 * These descriptors are stored in the @रेजिस्टरed_protocols array at protocol
 * registration समय.
 *
 * Once these descriptors are successfully रेजिस्टरed, they are NEVER again
 * हटाओd or modअगरied since protocols करो not unरेजिस्टर ever, so that, once
 * we safely grab a NON-शून्य reference from the array we can keep it and use it.
 */
काष्ठा scmi_रेजिस्टरed_events_desc अणु
	u8				id;
	स्थिर काष्ठा scmi_event_ops	*ops;
	काष्ठा events_queue		equeue;
	काष्ठा scmi_notअगरy_instance	*ni;
	काष्ठा scmi_event_header	*eh;
	माप_प्रकार				eh_sz;
	व्योम				*in_flight;
	पूर्णांक				num_events;
	काष्ठा scmi_रेजिस्टरed_event	**रेजिस्टरed_events;
	/* mutex to protect रेजिस्टरed_events_handlers */
	काष्ठा mutex			रेजिस्टरed_mtx;
	स्थिर काष्ठा scmi_protocol_handle	*ph;
	DECLARE_HASHTABLE(रेजिस्टरed_events_handlers, SCMI_REGISTERED_HASH_SZ);
पूर्ण;

/**
 * काष्ठा scmi_रेजिस्टरed_event  - Event Specअगरic Inक्रमmation
 * @proto: A reference to the associated protocol descriptor
 * @evt: A reference to the associated event descriptor (as provided at
 *       registration समय)
 * @report: A pre-allocated buffer used by the deferred worker to fill a
 *	    customized event report
 * @num_sources: The number of possible sources क्रम this event as stated at
 *		 events' registration समय
 * @sources: A reference to a dynamically allocated array used to refcount the
 *	     events' enable requests क्रम all the existing sources
 * @sources_mtx: A mutex to serialize the access to @sources
 *
 * All रेजिस्टरed events are represented by one of these काष्ठाures that are
 * stored in the @रेजिस्टरed_events array at protocol registration समय.
 *
 * Once these descriptors are successfully रेजिस्टरed, they are NEVER again
 * हटाओd or modअगरied since protocols करो not unरेजिस्टर ever, so that once we
 * safely grab a NON-शून्य reference from the table we can keep it and use it.
 */
काष्ठा scmi_रेजिस्टरed_event अणु
	काष्ठा scmi_रेजिस्टरed_events_desc *proto;
	स्थिर काष्ठा scmi_event	*evt;
	व्योम		*report;
	u32		num_sources;
	refcount_t	*sources;
	/* locking to serialize the access to sources */
	काष्ठा mutex	sources_mtx;
पूर्ण;

/**
 * काष्ठा scmi_event_handler  - Event handler inक्रमmation
 * @key: The used hashkey
 * @users: A reference count क्रम number of active users क्रम this handler
 * @r_evt: A reference to the associated रेजिस्टरed event; when this is शून्य
 *	   this handler is pending, which means that identअगरies a set of
 *	   callbacks पूर्णांकended to be attached to an event which is still not
 *	   known nor रेजिस्टरed by any protocol at that poपूर्णांक in समय
 * @chain: The notअगरication chain dedicated to this specअगरic event tuple
 * @hash: The hlist_node used क्रम collision handling
 * @enabled: A boolean which records अगर event's generation has been alपढ़ोy
 *	     enabled क्रम this handler as a whole
 *
 * This काष्ठाure collects all the inक्रमmation needed to process a received
 * event identअगरied by the tuple (proto_id, evt_id, src_id).
 * These descriptors are stored in a per-protocol @रेजिस्टरed_events_handlers
 * table using as a key a value derived from that tuple.
 */
काष्ठा scmi_event_handler अणु
	u32				key;
	refcount_t			users;
	काष्ठा scmi_रेजिस्टरed_event	*r_evt;
	काष्ठा blocking_notअगरier_head	chain;
	काष्ठा hlist_node		hash;
	bool				enabled;
पूर्ण;

#घोषणा IS_HNDL_PENDING(hndl)	(!(hndl)->r_evt)

अटल काष्ठा scmi_event_handler *
scmi_get_active_handler(काष्ठा scmi_notअगरy_instance *ni, u32 evt_key);
अटल व्योम scmi_put_active_handler(काष्ठा scmi_notअगरy_instance *ni,
				    काष्ठा scmi_event_handler *hndl);
अटल bool scmi_put_handler_unlocked(काष्ठा scmi_notअगरy_instance *ni,
				      काष्ठा scmi_event_handler *hndl);

/**
 * scmi_lookup_and_call_event_chain()  - Lookup the proper chain and call it
 * @ni: A reference to the notअगरication instance to use
 * @evt_key: The key to use to lookup the related notअगरication chain
 * @report: The customized event-specअगरic report to pass करोwn to the callbacks
 *	    as their *data parameter.
 */
अटल अंतरभूत व्योम
scmi_lookup_and_call_event_chain(काष्ठा scmi_notअगरy_instance *ni,
				 u32 evt_key, व्योम *report)
अणु
	पूर्णांक ret;
	काष्ठा scmi_event_handler *hndl;

	/*
	 * Here ensure the event handler cannot vanish जबतक using it.
	 * It is legitimate, though, क्रम an handler not to be found at all here,
	 * e.g. when it has been unरेजिस्टरed by the user after some events had
	 * alपढ़ोy been queued.
	 */
	hndl = scmi_get_active_handler(ni, evt_key);
	अगर (!hndl)
		वापस;

	ret = blocking_notअगरier_call_chain(&hndl->chain,
					   KEY_XTRACT_EVT_ID(evt_key),
					   report);
	/* Notअगरiers are NOT supposed to cut the chain ... */
	WARN_ON_ONCE(ret & NOTIFY_STOP_MASK);

	scmi_put_active_handler(ni, hndl);
पूर्ण

/**
 * scmi_process_event_header()  - Dequeue and process an event header
 * @eq: The queue to use
 * @pd: The protocol descriptor to use
 *
 * Read an event header from the protocol queue पूर्णांकo the dedicated scratch
 * buffer and looks क्रम a matching रेजिस्टरed event; in हाल an anomalously
 * sized पढ़ो is detected just flush the queue.
 *
 * Return:
 * * a reference to the matching रेजिस्टरed event when found
 * * ERR_PTR(-EINVAL) when NO रेजिस्टरed event could be found
 * * शून्य when the queue is empty
 */
अटल अंतरभूत काष्ठा scmi_रेजिस्टरed_event *
scmi_process_event_header(काष्ठा events_queue *eq,
			  काष्ठा scmi_रेजिस्टरed_events_desc *pd)
अणु
	अचिन्हित पूर्णांक outs;
	काष्ठा scmi_रेजिस्टरed_event *r_evt;

	outs = kfअगरo_out(&eq->kfअगरo, pd->eh,
			 माप(काष्ठा scmi_event_header));
	अगर (!outs)
		वापस शून्य;
	अगर (outs != माप(काष्ठा scmi_event_header)) अणु
		dev_err(pd->ni->handle->dev, "corrupted EVT header. Flush.\n");
		kfअगरo_reset_out(&eq->kfअगरo);
		वापस शून्य;
	पूर्ण

	r_evt = SCMI_GET_REVT_FROM_PD(pd, pd->eh->evt_id);
	अगर (!r_evt)
		r_evt = ERR_PTR(-EINVAL);

	वापस r_evt;
पूर्ण

/**
 * scmi_process_event_payload()  - Dequeue and process an event payload
 * @eq: The queue to use
 * @pd: The protocol descriptor to use
 * @r_evt: The रेजिस्टरed event descriptor to use
 *
 * Read an event payload from the protocol queue पूर्णांकo the dedicated scratch
 * buffer, fills a custom report and then look क्रम matching event handlers and
 * call them; skip any unknown event (as marked by scmi_process_event_header())
 * and in हाल an anomalously sized पढ़ो is detected just flush the queue.
 *
 * Return: False when the queue is empty
 */
अटल अंतरभूत bool
scmi_process_event_payload(काष्ठा events_queue *eq,
			   काष्ठा scmi_रेजिस्टरed_events_desc *pd,
			   काष्ठा scmi_रेजिस्टरed_event *r_evt)
अणु
	u32 src_id, key;
	अचिन्हित पूर्णांक outs;
	व्योम *report = शून्य;

	outs = kfअगरo_out(&eq->kfअगरo, pd->eh->payld, pd->eh->payld_sz);
	अगर (!outs)
		वापस false;

	/* Any in-flight event has now been officially processed */
	pd->in_flight = शून्य;

	अगर (outs != pd->eh->payld_sz) अणु
		dev_err(pd->ni->handle->dev, "corrupted EVT Payload. Flush.\n");
		kfअगरo_reset_out(&eq->kfअगरo);
		वापस false;
	पूर्ण

	अगर (IS_ERR(r_evt)) अणु
		dev_warn(pd->ni->handle->dev,
			 "SKIP UNKNOWN EVT - proto:%X  evt:%d\n",
			 pd->id, pd->eh->evt_id);
		वापस true;
	पूर्ण

	report = REVT_FILL_REPORT(r_evt, pd->eh->evt_id, pd->eh->बारtamp,
				  pd->eh->payld, pd->eh->payld_sz,
				  r_evt->report, &src_id);
	अगर (!report) अणु
		dev_err(pd->ni->handle->dev,
			"report not available - proto:%X  evt:%d\n",
			pd->id, pd->eh->evt_id);
		वापस true;
	पूर्ण

	/* At first search क्रम a generic ALL src_ids handler... */
	key = MAKE_ALL_SRCS_KEY(pd->id, pd->eh->evt_id);
	scmi_lookup_and_call_event_chain(pd->ni, key, report);

	/* ...then search क्रम any specअगरic src_id */
	key = MAKE_HASH_KEY(pd->id, pd->eh->evt_id, src_id);
	scmi_lookup_and_call_event_chain(pd->ni, key, report);

	वापस true;
पूर्ण

/**
 * scmi_events_dispatcher()  - Common worker logic क्रम all work items.
 * @work: The work item to use, which is associated to a dedicated events_queue
 *
 * Logic:
 *  1. dequeue one pending RX notअगरication (queued in SCMI RX ISR context)
 *  2. generate a custom event report from the received event message
 *  3. lookup क्रम any रेजिस्टरed ALL_SRC_IDs handler:
 *    - > call the related notअगरication chain passing in the report
 *  4. lookup क्रम any रेजिस्टरed specअगरic SRC_ID handler:
 *    - > call the related notअगरication chain passing in the report
 *
 * Note that:
 * * a dedicated per-protocol kfअगरo queue is used: in this way an anomalous
 *   flood of events cannot saturate other protocols' queues.
 * * each per-protocol queue is associated to a distinct work_item, which
 *   means, in turn, that:
 *   + all protocols can process their dedicated queues concurrently
 *     (since notअगरy_wq:max_active != 1)
 *   + anyway at most one worker instance is allowed to run on the same queue
 *     concurrently: this ensures that we can have only one concurrent
 *     पढ़ोer/ग_लिखोr on the associated kfअगरo, so that we can use it lock-less
 *
 * Context: Process context.
 */
अटल व्योम scmi_events_dispatcher(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा events_queue *eq;
	काष्ठा scmi_रेजिस्टरed_events_desc *pd;
	काष्ठा scmi_रेजिस्टरed_event *r_evt;

	eq = container_of(work, काष्ठा events_queue, notअगरy_work);
	pd = container_of(eq, काष्ठा scmi_रेजिस्टरed_events_desc, equeue);
	/*
	 * In order to keep the queue lock-less and the number of memcopies
	 * to the bare minimum needed, the dispatcher accounts क्रम the
	 * possibility of per-protocol in-flight events: i.e. an event whose
	 * reception could end up being split across two subsequent runs of this
	 * worker, first the header, then the payload.
	 */
	करो अणु
		अगर (!pd->in_flight) अणु
			r_evt = scmi_process_event_header(eq, pd);
			अगर (!r_evt)
				अवरोध;
			pd->in_flight = r_evt;
		पूर्ण अन्यथा अणु
			r_evt = pd->in_flight;
		पूर्ण
	पूर्ण जबतक (scmi_process_event_payload(eq, pd, r_evt));
पूर्ण

/**
 * scmi_notअगरy()  - Queues a notअगरication क्रम further deferred processing
 * @handle: The handle identअगरying the platक्रमm instance from which the
 *	    dispatched event is generated
 * @proto_id: Protocol ID
 * @evt_id: Event ID (msgID)
 * @buf: Event Message Payload (without the header)
 * @len: Event Message Payload size
 * @ts: RX Timestamp in nanoseconds (bootसमय)
 *
 * Context: Called in पूर्णांकerrupt context to queue a received event क्रम
 * deferred processing.
 *
 * Return: 0 on Success
 */
पूर्णांक scmi_notअगरy(स्थिर काष्ठा scmi_handle *handle, u8 proto_id, u8 evt_id,
		स्थिर व्योम *buf, माप_प्रकार len, kसमय_प्रकार ts)
अणु
	काष्ठा scmi_रेजिस्टरed_event *r_evt;
	काष्ठा scmi_event_header eh;
	काष्ठा scmi_notअगरy_instance *ni;

	ni = scmi_notअगरication_instance_data_get(handle);
	अगर (!ni)
		वापस 0;

	r_evt = SCMI_GET_REVT(ni, proto_id, evt_id);
	अगर (!r_evt)
		वापस -EINVAL;

	अगर (len > r_evt->evt->max_payld_sz) अणु
		dev_err(handle->dev, "discard badly sized message\n");
		वापस -EINVAL;
	पूर्ण
	अगर (kfअगरo_avail(&r_evt->proto->equeue.kfअगरo) < माप(eh) + len) अणु
		dev_warn(handle->dev,
			 "queue full, dropping proto_id:%d  evt_id:%d  ts:%lld\n",
			 proto_id, evt_id, kसमय_प्रकारo_ns(ts));
		वापस -ENOMEM;
	पूर्ण

	eh.बारtamp = ts;
	eh.evt_id = evt_id;
	eh.payld_sz = len;
	/*
	 * Header and payload are enqueued with two distinct kfअगरo_in() (so non
	 * atomic), but this situation is handled properly on the consumer side
	 * with in-flight events tracking.
	 */
	kfअगरo_in(&r_evt->proto->equeue.kfअगरo, &eh, माप(eh));
	kfअगरo_in(&r_evt->proto->equeue.kfअगरo, buf, len);
	/*
	 * Don't care about वापस value here since we just want to ensure that
	 * a work is queued all the बार whenever some items have been pushed
	 * on the kfअगरo:
	 * - अगर work was alपढ़ोy queued it will simply fail to queue a new one
	 *   since it is not needed
	 * - अगर work was not queued alपढ़ोy it will be now, even in हाल work
	 *   was in fact alपढ़ोy running: this behavior aव्योमs any possible race
	 *   when this function pushes new items onto the kfअगरos after the
	 *   related executing worker had alपढ़ोy determined the kfअगरo to be
	 *   empty and it was terminating.
	 */
	queue_work(r_evt->proto->equeue.wq,
		   &r_evt->proto->equeue.notअगरy_work);

	वापस 0;
पूर्ण

/**
 * scmi_kfअगरo_मुक्त()  - Devres action helper to मुक्त the kfअगरo
 * @kfअगरo: The kfअगरo to मुक्त
 */
अटल व्योम scmi_kfअगरo_मुक्त(व्योम *kfअगरo)
अणु
	kfअगरo_मुक्त((काष्ठा kfअगरo *)kfअगरo);
पूर्ण

/**
 * scmi_initialize_events_queue()  - Allocate/Initialize a kfअगरo buffer
 * @ni: A reference to the notअगरication instance to use
 * @equeue: The events_queue to initialize
 * @sz: Size of the kfअगरo buffer to allocate
 *
 * Allocate a buffer क्रम the kfअगरo and initialize it.
 *
 * Return: 0 on Success
 */
अटल पूर्णांक scmi_initialize_events_queue(काष्ठा scmi_notअगरy_instance *ni,
					काष्ठा events_queue *equeue, माप_प्रकार sz)
अणु
	पूर्णांक ret;

	अगर (kfअगरo_alloc(&equeue->kfअगरo, sz, GFP_KERNEL))
		वापस -ENOMEM;
	/* Size could have been roundup to घातer-of-two */
	equeue->sz = kfअगरo_size(&equeue->kfअगरo);

	ret = devm_add_action_or_reset(ni->handle->dev, scmi_kfअगरo_मुक्त,
				       &equeue->kfअगरo);
	अगर (ret)
		वापस ret;

	INIT_WORK(&equeue->notअगरy_work, scmi_events_dispatcher);
	equeue->wq = ni->notअगरy_wq;

	वापस ret;
पूर्ण

/**
 * scmi_allocate_रेजिस्टरed_events_desc()  - Allocate a रेजिस्टरed events'
 * descriptor
 * @ni: A reference to the &काष्ठा scmi_notअगरy_instance notअगरication instance
 *	to use
 * @proto_id: Protocol ID
 * @queue_sz: Size of the associated queue to allocate
 * @eh_sz: Size of the event header scratch area to pre-allocate
 * @num_events: Number of events to support (size of @रेजिस्टरed_events)
 * @ops: Poपूर्णांकer to a काष्ठा holding references to protocol specअगरic helpers
 *	 needed during events handling
 *
 * It is supposed to be called only once क्रम each protocol at protocol
 * initialization समय, so it warns अगर the requested protocol is found alपढ़ोy
 * रेजिस्टरed.
 *
 * Return: The allocated and रेजिस्टरed descriptor on Success
 */
अटल काष्ठा scmi_रेजिस्टरed_events_desc *
scmi_allocate_रेजिस्टरed_events_desc(काष्ठा scmi_notअगरy_instance *ni,
				     u8 proto_id, माप_प्रकार queue_sz, माप_प्रकार eh_sz,
				     पूर्णांक num_events,
				     स्थिर काष्ठा scmi_event_ops *ops)
अणु
	पूर्णांक ret;
	काष्ठा scmi_रेजिस्टरed_events_desc *pd;

	/* Ensure protocols are up to date */
	smp_rmb();
	अगर (WARN_ON(ni->रेजिस्टरed_protocols[proto_id]))
		वापस ERR_PTR(-EINVAL);

	pd = devm_kzalloc(ni->handle->dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस ERR_PTR(-ENOMEM);
	pd->id = proto_id;
	pd->ops = ops;
	pd->ni = ni;

	ret = scmi_initialize_events_queue(ni, &pd->equeue, queue_sz);
	अगर (ret)
		वापस ERR_PTR(ret);

	pd->eh = devm_kzalloc(ni->handle->dev, eh_sz, GFP_KERNEL);
	अगर (!pd->eh)
		वापस ERR_PTR(-ENOMEM);
	pd->eh_sz = eh_sz;

	pd->रेजिस्टरed_events = devm_kसुस्मृति(ni->handle->dev, num_events,
					     माप(अक्षर *), GFP_KERNEL);
	अगर (!pd->रेजिस्टरed_events)
		वापस ERR_PTR(-ENOMEM);
	pd->num_events = num_events;

	/* Initialize per protocol handlers table */
	mutex_init(&pd->रेजिस्टरed_mtx);
	hash_init(pd->रेजिस्टरed_events_handlers);

	वापस pd;
पूर्ण

/**
 * scmi_रेजिस्टर_protocol_events()  - Register Protocol Events with the core
 * @handle: The handle identअगरying the platक्रमm instance against which the
 *	    protocol's events are रेजिस्टरed
 * @proto_id: Protocol ID
 * @ph: SCMI protocol handle.
 * @ee: A काष्ठाure describing the events supported by this protocol.
 *
 * Used by SCMI Protocols initialization code to रेजिस्टर with the notअगरication
 * core the list of supported events and their descriptors: takes care to
 * pre-allocate and store all needed descriptors, scratch buffers and event
 * queues.
 *
 * Return: 0 on Success
 */
पूर्णांक scmi_रेजिस्टर_protocol_events(स्थिर काष्ठा scmi_handle *handle, u8 proto_id,
				  स्थिर काष्ठा scmi_protocol_handle *ph,
				  स्थिर काष्ठा scmi_protocol_events *ee)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक num_sources;
	माप_प्रकार payld_sz = 0;
	काष्ठा scmi_रेजिस्टरed_events_desc *pd;
	काष्ठा scmi_notअगरy_instance *ni;
	स्थिर काष्ठा scmi_event *evt;

	अगर (!ee || !ee->ops || !ee->evts || !ph ||
	    (!ee->num_sources && !ee->ops->get_num_sources))
		वापस -EINVAL;

	ni = scmi_notअगरication_instance_data_get(handle);
	अगर (!ni)
		वापस -ENOMEM;

	/* num_sources cannot be <= 0 */
	अगर (ee->num_sources) अणु
		num_sources = ee->num_sources;
	पूर्ण अन्यथा अणु
		पूर्णांक nsrc = ee->ops->get_num_sources(ph);

		अगर (nsrc <= 0)
			वापस -EINVAL;
		num_sources = nsrc;
	पूर्ण

	evt = ee->evts;
	क्रम (i = 0; i < ee->num_events; i++)
		payld_sz = max_t(माप_प्रकार, payld_sz, evt[i].max_payld_sz);
	payld_sz += माप(काष्ठा scmi_event_header);

	pd = scmi_allocate_रेजिस्टरed_events_desc(ni, proto_id, ee->queue_sz,
						  payld_sz, ee->num_events,
						  ee->ops);
	अगर (IS_ERR(pd))
		वापस PTR_ERR(pd);

	pd->ph = ph;
	क्रम (i = 0; i < ee->num_events; i++, evt++) अणु
		काष्ठा scmi_रेजिस्टरed_event *r_evt;

		r_evt = devm_kzalloc(ni->handle->dev, माप(*r_evt),
				     GFP_KERNEL);
		अगर (!r_evt)
			वापस -ENOMEM;
		r_evt->proto = pd;
		r_evt->evt = evt;

		r_evt->sources = devm_kसुस्मृति(ni->handle->dev, num_sources,
					      माप(refcount_t), GFP_KERNEL);
		अगर (!r_evt->sources)
			वापस -ENOMEM;
		r_evt->num_sources = num_sources;
		mutex_init(&r_evt->sources_mtx);

		r_evt->report = devm_kzalloc(ni->handle->dev,
					     evt->max_report_sz, GFP_KERNEL);
		अगर (!r_evt->report)
			वापस -ENOMEM;

		pd->रेजिस्टरed_events[i] = r_evt;
		/* Ensure events are updated */
		smp_wmb();
		dev_dbg(handle->dev, "registered event - %lX\n",
			MAKE_ALL_SRCS_KEY(r_evt->proto->id, r_evt->evt->id));
	पूर्ण

	/* Register protocol and events...it will never be हटाओd */
	ni->रेजिस्टरed_protocols[proto_id] = pd;
	/* Ensure protocols are updated */
	smp_wmb();

	/*
	 * Finalize any pending events' handler which could have been रुकोing
	 * क्रम this protocol's events registration.
	 */
	schedule_work(&ni->init_work);

	वापस 0;
पूर्ण

/**
 * scmi_deरेजिस्टर_protocol_events  - Deरेजिस्टर protocol events with the core
 * @handle: The handle identअगरying the platक्रमm instance against which the
 *	    protocol's events are रेजिस्टरed
 * @proto_id: Protocol ID
 */
व्योम scmi_deरेजिस्टर_protocol_events(स्थिर काष्ठा scmi_handle *handle,
				     u8 proto_id)
अणु
	काष्ठा scmi_notअगरy_instance *ni;
	काष्ठा scmi_रेजिस्टरed_events_desc *pd;

	ni = scmi_notअगरication_instance_data_get(handle);
	अगर (!ni)
		वापस;

	pd = ni->रेजिस्टरed_protocols[proto_id];
	अगर (!pd)
		वापस;

	ni->रेजिस्टरed_protocols[proto_id] = शून्य;
	/* Ensure protocols are updated */
	smp_wmb();

	cancel_work_sync(&pd->equeue.notअगरy_work);
पूर्ण

/**
 * scmi_allocate_event_handler()  - Allocate Event handler
 * @ni: A reference to the notअगरication instance to use
 * @evt_key: 32bit key uniquely bind to the event identअगरied by the tuple
 *	     (proto_id, evt_id, src_id)
 *
 * Allocate an event handler and related notअगरication chain associated with
 * the provided event handler key.
 * Note that, at this poपूर्णांक, a related रेजिस्टरed_event is still to be
 * associated to this handler descriptor (hndl->r_evt == शून्य), so the handler
 * is initialized as pending.
 *
 * Context: Assumes to be called with @pending_mtx alपढ़ोy acquired.
 * Return: the freshly allocated काष्ठाure on Success
 */
अटल काष्ठा scmi_event_handler *
scmi_allocate_event_handler(काष्ठा scmi_notअगरy_instance *ni, u32 evt_key)
अणु
	काष्ठा scmi_event_handler *hndl;

	hndl = kzalloc(माप(*hndl), GFP_KERNEL);
	अगर (!hndl)
		वापस शून्य;
	hndl->key = evt_key;
	BLOCKING_INIT_NOTIFIER_HEAD(&hndl->chain);
	refcount_set(&hndl->users, 1);
	/* New handlers are created pending */
	hash_add(ni->pending_events_handlers, &hndl->hash, hndl->key);

	वापस hndl;
पूर्ण

/**
 * scmi_मुक्त_event_handler()  - Free the provided Event handler
 * @hndl: The event handler काष्ठाure to मुक्त
 *
 * Context: Assumes to be called with proper locking acquired depending
 *	    on the situation.
 */
अटल व्योम scmi_मुक्त_event_handler(काष्ठा scmi_event_handler *hndl)
अणु
	hash_del(&hndl->hash);
	kमुक्त(hndl);
पूर्ण

/**
 * scmi_bind_event_handler()  - Helper to attempt binding an handler to an event
 * @ni: A reference to the notअगरication instance to use
 * @hndl: The event handler to bind
 *
 * If an associated रेजिस्टरed event is found, move the handler from the pending
 * पूर्णांकo the रेजिस्टरed table.
 *
 * Context: Assumes to be called with @pending_mtx alपढ़ोy acquired.
 *
 * Return: 0 on Success
 */
अटल अंतरभूत पूर्णांक scmi_bind_event_handler(काष्ठा scmi_notअगरy_instance *ni,
					  काष्ठा scmi_event_handler *hndl)
अणु
	काष्ठा scmi_रेजिस्टरed_event *r_evt;

	r_evt = SCMI_GET_REVT(ni, KEY_XTRACT_PROTO_ID(hndl->key),
			      KEY_XTRACT_EVT_ID(hndl->key));
	अगर (!r_evt)
		वापस -EINVAL;

	/*
	 * Remove from pending and insert पूर्णांकo रेजिस्टरed जबतक getting hold
	 * of protocol instance.
	 */
	hash_del(&hndl->hash);
	/*
	 * Acquire protocols only क्रम NON pending handlers, so as NOT to trigger
	 * protocol initialization when a notअगरier is रेजिस्टरed against a still
	 * not रेजिस्टरed protocol, since it would make little sense to क्रमce init
	 * protocols क्रम which still no SCMI driver user exists: they wouldn't
	 * emit any event anyway till some SCMI driver starts using it.
	 */
	scmi_protocol_acquire(ni->handle, KEY_XTRACT_PROTO_ID(hndl->key));
	hndl->r_evt = r_evt;

	mutex_lock(&r_evt->proto->रेजिस्टरed_mtx);
	hash_add(r_evt->proto->रेजिस्टरed_events_handlers,
		 &hndl->hash, hndl->key);
	mutex_unlock(&r_evt->proto->रेजिस्टरed_mtx);

	वापस 0;
पूर्ण

/**
 * scmi_valid_pending_handler()  - Helper to check pending status of handlers
 * @ni: A reference to the notअगरication instance to use
 * @hndl: The event handler to check
 *
 * An handler is considered pending when its r_evt == शून्य, because the related
 * event was still unknown at handler's registration समय; anyway, since all
 * protocols रेजिस्टर their supported events once क्रम all at protocols'
 * initialization समय, a pending handler cannot be considered valid anymore अगर
 * the underlying event (which it is रुकोing क्रम), beदीर्घs to an alपढ़ोy
 * initialized and रेजिस्टरed protocol.
 *
 * Return: 0 on Success
 */
अटल अंतरभूत पूर्णांक scmi_valid_pending_handler(काष्ठा scmi_notअगरy_instance *ni,
					     काष्ठा scmi_event_handler *hndl)
अणु
	काष्ठा scmi_रेजिस्टरed_events_desc *pd;

	अगर (!IS_HNDL_PENDING(hndl))
		वापस -EINVAL;

	pd = SCMI_GET_PROTO(ni, KEY_XTRACT_PROTO_ID(hndl->key));
	अगर (pd)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * scmi_रेजिस्टर_event_handler()  - Register whenever possible an Event handler
 * @ni: A reference to the notअगरication instance to use
 * @hndl: The event handler to रेजिस्टर
 *
 * At first try to bind an event handler to its associated event, then check अगर
 * it was at least a valid pending handler: अगर it was not bound nor valid वापस
 * false.
 *
 * Valid pending incomplete bindings will be periodically retried by a dedicated
 * worker which is kicked each समय a new protocol completes its own
 * registration phase.
 *
 * Context: Assumes to be called with @pending_mtx acquired.
 *
 * Return: 0 on Success
 */
अटल पूर्णांक scmi_रेजिस्टर_event_handler(काष्ठा scmi_notअगरy_instance *ni,
				       काष्ठा scmi_event_handler *hndl)
अणु
	पूर्णांक ret;

	ret = scmi_bind_event_handler(ni, hndl);
	अगर (!ret) अणु
		dev_dbg(ni->handle->dev, "registered NEW handler - key:%X\n",
			hndl->key);
	पूर्ण अन्यथा अणु
		ret = scmi_valid_pending_handler(ni, hndl);
		अगर (!ret)
			dev_dbg(ni->handle->dev,
				"registered PENDING handler - key:%X\n",
				hndl->key);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * __scmi_event_handler_get_ops()  - Utility to get or create an event handler
 * @ni: A reference to the notअगरication instance to use
 * @evt_key: The event key to use
 * @create: A boolean flag to specअगरy अगर a handler must be created when
 *	    not alपढ़ोy existent
 *
 * Search क्रम the desired handler matching the key in both the per-protocol
 * रेजिस्टरed table and the common pending table:
 * * अगर found adjust users refcount
 * * अगर not found and @create is true, create and रेजिस्टर the new handler:
 *   handler could end up being रेजिस्टरed as pending अगर no matching event
 *   could be found.
 *
 * An handler is guaranteed to reside in one and only one of the tables at
 * any one समय; to ensure this the whole search and create is perक्रमmed
 * holding the @pending_mtx lock, with @रेजिस्टरed_mtx additionally acquired
 * अगर needed.
 *
 * Note that when a nested acquisition of these mutexes is needed the locking
 * order is always (same as in @init_work):
 * 1. pending_mtx
 * 2. रेजिस्टरed_mtx
 *
 * Events generation is NOT enabled right after creation within this routine
 * since at creation समय we usually want to have all setup and पढ़ोy beक्रमe
 * events really start flowing.
 *
 * Return: A properly refcounted handler on Success, शून्य on Failure
 */
अटल अंतरभूत काष्ठा scmi_event_handler *
__scmi_event_handler_get_ops(काष्ठा scmi_notअगरy_instance *ni,
			     u32 evt_key, bool create)
अणु
	काष्ठा scmi_रेजिस्टरed_event *r_evt;
	काष्ठा scmi_event_handler *hndl = शून्य;

	r_evt = SCMI_GET_REVT(ni, KEY_XTRACT_PROTO_ID(evt_key),
			      KEY_XTRACT_EVT_ID(evt_key));

	mutex_lock(&ni->pending_mtx);
	/* Search रेजिस्टरed events at first ... अगर possible at all */
	अगर (r_evt) अणु
		mutex_lock(&r_evt->proto->रेजिस्टरed_mtx);
		hndl = KEY_FIND(r_evt->proto->रेजिस्टरed_events_handlers,
				hndl, evt_key);
		अगर (hndl)
			refcount_inc(&hndl->users);
		mutex_unlock(&r_evt->proto->रेजिस्टरed_mtx);
	पूर्ण

	/* ...then amongst pending. */
	अगर (!hndl) अणु
		hndl = KEY_FIND(ni->pending_events_handlers, hndl, evt_key);
		अगर (hndl)
			refcount_inc(&hndl->users);
	पूर्ण

	/* Create अगर still not found and required */
	अगर (!hndl && create) अणु
		hndl = scmi_allocate_event_handler(ni, evt_key);
		अगर (hndl && scmi_रेजिस्टर_event_handler(ni, hndl)) अणु
			dev_dbg(ni->handle->dev,
				"purging UNKNOWN handler - key:%X\n",
				hndl->key);
			/* this hndl can be only a pending one */
			scmi_put_handler_unlocked(ni, hndl);
			hndl = शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(&ni->pending_mtx);

	वापस hndl;
पूर्ण

अटल काष्ठा scmi_event_handler *
scmi_get_handler(काष्ठा scmi_notअगरy_instance *ni, u32 evt_key)
अणु
	वापस __scmi_event_handler_get_ops(ni, evt_key, false);
पूर्ण

अटल काष्ठा scmi_event_handler *
scmi_get_or_create_handler(काष्ठा scmi_notअगरy_instance *ni, u32 evt_key)
अणु
	वापस __scmi_event_handler_get_ops(ni, evt_key, true);
पूर्ण

/**
 * scmi_get_active_handler()  - Helper to get active handlers only
 * @ni: A reference to the notअगरication instance to use
 * @evt_key: The event key to use
 *
 * Search क्रम the desired handler matching the key only in the per-protocol
 * table of रेजिस्टरed handlers: this is called only from the dispatching path
 * so want to be as quick as possible and करो not care about pending.
 *
 * Return: A properly refcounted active handler
 */
अटल काष्ठा scmi_event_handler *
scmi_get_active_handler(काष्ठा scmi_notअगरy_instance *ni, u32 evt_key)
अणु
	काष्ठा scmi_रेजिस्टरed_event *r_evt;
	काष्ठा scmi_event_handler *hndl = शून्य;

	r_evt = SCMI_GET_REVT(ni, KEY_XTRACT_PROTO_ID(evt_key),
			      KEY_XTRACT_EVT_ID(evt_key));
	अगर (r_evt) अणु
		mutex_lock(&r_evt->proto->रेजिस्टरed_mtx);
		hndl = KEY_FIND(r_evt->proto->रेजिस्टरed_events_handlers,
				hndl, evt_key);
		अगर (hndl)
			refcount_inc(&hndl->users);
		mutex_unlock(&r_evt->proto->रेजिस्टरed_mtx);
	पूर्ण

	वापस hndl;
पूर्ण

/**
 * __scmi_enable_evt()  - Enable/disable events generation
 * @r_evt: The रेजिस्टरed event to act upon
 * @src_id: The src_id to act upon
 * @enable: The action to perक्रमm: true->Enable, false->Disable
 *
 * Takes care of proper refcounting जबतक perक्रमming enable/disable: handles
 * the special हाल of ALL sources requests by itself.
 * Returns successfully अगर at least one of the required src_id has been
 * successfully enabled/disabled.
 *
 * Return: 0 on Success
 */
अटल अंतरभूत पूर्णांक __scmi_enable_evt(काष्ठा scmi_रेजिस्टरed_event *r_evt,
				    u32 src_id, bool enable)
अणु
	पूर्णांक retvals = 0;
	u32 num_sources;
	refcount_t *sid;

	अगर (src_id == SRC_ID_MASK) अणु
		src_id = 0;
		num_sources = r_evt->num_sources;
	पूर्ण अन्यथा अगर (src_id < r_evt->num_sources) अणु
		num_sources = 1;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&r_evt->sources_mtx);
	अगर (enable) अणु
		क्रम (; num_sources; src_id++, num_sources--) अणु
			पूर्णांक ret = 0;

			sid = &r_evt->sources[src_id];
			अगर (refcount_पढ़ो(sid) == 0) अणु
				ret = REVT_NOTIFY_ENABLE(r_evt, r_evt->evt->id,
							 src_id);
				अगर (!ret)
					refcount_set(sid, 1);
			पूर्ण अन्यथा अणु
				refcount_inc(sid);
			पूर्ण
			retvals += !ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (; num_sources; src_id++, num_sources--) अणु
			sid = &r_evt->sources[src_id];
			अगर (refcount_dec_and_test(sid))
				REVT_NOTIFY_DISABLE(r_evt,
						    r_evt->evt->id, src_id);
		पूर्ण
		retvals = 1;
	पूर्ण
	mutex_unlock(&r_evt->sources_mtx);

	वापस retvals ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक scmi_enable_events(काष्ठा scmi_event_handler *hndl)
अणु
	पूर्णांक ret = 0;

	अगर (!hndl->enabled) अणु
		ret = __scmi_enable_evt(hndl->r_evt,
					KEY_XTRACT_SRC_ID(hndl->key), true);
		अगर (!ret)
			hndl->enabled = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक scmi_disable_events(काष्ठा scmi_event_handler *hndl)
अणु
	पूर्णांक ret = 0;

	अगर (hndl->enabled) अणु
		ret = __scmi_enable_evt(hndl->r_evt,
					KEY_XTRACT_SRC_ID(hndl->key), false);
		अगर (!ret)
			hndl->enabled = false;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * scmi_put_handler_unlocked()  - Put an event handler
 * @ni: A reference to the notअगरication instance to use
 * @hndl: The event handler to act upon
 *
 * After having got exclusive access to the रेजिस्टरed handlers hashtable,
 * update the refcount and अगर @hndl is no more in use by anyone:
 * * ask क्रम events' generation disabling
 * * unरेजिस्टर and मुक्त the handler itself
 *
 * Context: Assumes all the proper locking has been managed by the caller.
 *
 * Return: True अगर handler was मुक्तd (users dropped to zero)
 */
अटल bool scmi_put_handler_unlocked(काष्ठा scmi_notअगरy_instance *ni,
				      काष्ठा scmi_event_handler *hndl)
अणु
	bool मुक्तd = false;

	अगर (refcount_dec_and_test(&hndl->users)) अणु
		अगर (!IS_HNDL_PENDING(hndl))
			scmi_disable_events(hndl);
		scmi_मुक्त_event_handler(hndl);
		मुक्तd = true;
	पूर्ण

	वापस मुक्तd;
पूर्ण

अटल व्योम scmi_put_handler(काष्ठा scmi_notअगरy_instance *ni,
			     काष्ठा scmi_event_handler *hndl)
अणु
	bool मुक्तd;
	u8 protocol_id;
	काष्ठा scmi_रेजिस्टरed_event *r_evt = hndl->r_evt;

	mutex_lock(&ni->pending_mtx);
	अगर (r_evt) अणु
		protocol_id = r_evt->proto->id;
		mutex_lock(&r_evt->proto->रेजिस्टरed_mtx);
	पूर्ण

	मुक्तd = scmi_put_handler_unlocked(ni, hndl);

	अगर (r_evt) अणु
		mutex_unlock(&r_evt->proto->रेजिस्टरed_mtx);
		/*
		 * Only रेजिस्टरed handler acquired protocol; must be here
		 * released only AFTER unlocking रेजिस्टरed_mtx, since
		 * releasing a protocol can trigger its de-initialization
		 * (ie. including r_evt and रेजिस्टरed_mtx)
		 */
		अगर (मुक्तd)
			scmi_protocol_release(ni->handle, protocol_id);
	पूर्ण
	mutex_unlock(&ni->pending_mtx);
पूर्ण

अटल व्योम scmi_put_active_handler(काष्ठा scmi_notअगरy_instance *ni,
				    काष्ठा scmi_event_handler *hndl)
अणु
	bool मुक्तd;
	काष्ठा scmi_रेजिस्टरed_event *r_evt = hndl->r_evt;
	u8 protocol_id = r_evt->proto->id;

	mutex_lock(&r_evt->proto->रेजिस्टरed_mtx);
	मुक्तd = scmi_put_handler_unlocked(ni, hndl);
	mutex_unlock(&r_evt->proto->रेजिस्टरed_mtx);
	अगर (मुक्तd)
		scmi_protocol_release(ni->handle, protocol_id);
पूर्ण

/**
 * scmi_event_handler_enable_events()  - Enable events associated to an handler
 * @hndl: The Event handler to act upon
 *
 * Return: 0 on Success
 */
अटल पूर्णांक scmi_event_handler_enable_events(काष्ठा scmi_event_handler *hndl)
अणु
	अगर (scmi_enable_events(hndl)) अणु
		pr_err("Failed to ENABLE events for key:%X !\n", hndl->key);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * scmi_notअगरier_रेजिस्टर()  - Register a notअगरier_block क्रम an event
 * @handle: The handle identअगरying the platक्रमm instance against which the
 *	    callback is रेजिस्टरed
 * @proto_id: Protocol ID
 * @evt_id: Event ID
 * @src_id: Source ID, when शून्य रेजिस्टर क्रम events coming क्रमm ALL possible
 *	    sources
 * @nb: A standard notअगरier block to रेजिस्टर क्रम the specअगरied event
 *
 * Generic helper to रेजिस्टर a notअगरier_block against a protocol event.
 *
 * A notअगरier_block @nb will be रेजिस्टरed क्रम each distinct event identअगरied
 * by the tuple (proto_id, evt_id, src_id) on a dedicated notअगरication chain
 * so that:
 *
 *	(proto_X, evt_Y, src_Z) --> chain_X_Y_Z
 *
 * @src_id meaning is protocol specअगरic and identअगरies the origin of the event
 * (like करोमुख्य_id, sensor_id and so क्रमth).
 *
 * @src_id can be शून्य to signअगरy that the caller is पूर्णांकerested in receiving
 * notअगरications from ALL the available sources क्रम that protocol OR simply that
 * the protocol करोes not support distinct sources.
 *
 * As soon as one user क्रम the specअगरied tuple appears, an handler is created,
 * and that specअगरic event's generation is enabled at the platक्रमm level, unless
 * an associated रेजिस्टरed event is found missing, meaning that the needed
 * protocol is still to be initialized and the handler has just been रेजिस्टरed
 * as still pending.
 *
 * Return: 0 on Success
 */
अटल पूर्णांक scmi_notअगरier_रेजिस्टर(स्थिर काष्ठा scmi_handle *handle,
				  u8 proto_id, u8 evt_id, स्थिर u32 *src_id,
				  काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक ret = 0;
	u32 evt_key;
	काष्ठा scmi_event_handler *hndl;
	काष्ठा scmi_notअगरy_instance *ni;

	ni = scmi_notअगरication_instance_data_get(handle);
	अगर (!ni)
		वापस -ENODEV;

	evt_key = MAKE_HASH_KEY(proto_id, evt_id,
				src_id ? *src_id : SRC_ID_MASK);
	hndl = scmi_get_or_create_handler(ni, evt_key);
	अगर (!hndl)
		वापस -EINVAL;

	blocking_notअगरier_chain_रेजिस्टर(&hndl->chain, nb);

	/* Enable events क्रम not pending handlers */
	अगर (!IS_HNDL_PENDING(hndl)) अणु
		ret = scmi_event_handler_enable_events(hndl);
		अगर (ret)
			scmi_put_handler(ni, hndl);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * scmi_notअगरier_unरेजिस्टर()  - Unरेजिस्टर a notअगरier_block क्रम an event
 * @handle: The handle identअगरying the platक्रमm instance against which the
 *	    callback is unरेजिस्टरed
 * @proto_id: Protocol ID
 * @evt_id: Event ID
 * @src_id: Source ID
 * @nb: The notअगरier_block to unरेजिस्टर
 *
 * Takes care to unरेजिस्टर the provided @nb from the notअगरication chain
 * associated to the specअगरied event and, अगर there are no more users क्रम the
 * event handler, मुक्तs also the associated event handler काष्ठाures.
 * (this could possibly cause disabling of event's generation at platक्रमm level)
 *
 * Return: 0 on Success
 */
अटल पूर्णांक scmi_notअगरier_unरेजिस्टर(स्थिर काष्ठा scmi_handle *handle,
				    u8 proto_id, u8 evt_id, स्थिर u32 *src_id,
				    काष्ठा notअगरier_block *nb)
अणु
	u32 evt_key;
	काष्ठा scmi_event_handler *hndl;
	काष्ठा scmi_notअगरy_instance *ni;

	ni = scmi_notअगरication_instance_data_get(handle);
	अगर (!ni)
		वापस -ENODEV;

	evt_key = MAKE_HASH_KEY(proto_id, evt_id,
				src_id ? *src_id : SRC_ID_MASK);
	hndl = scmi_get_handler(ni, evt_key);
	अगर (!hndl)
		वापस -EINVAL;

	/*
	 * Note that this chain unregistration call is safe on its own
	 * being पूर्णांकernally रक्षित by an rwsem.
	 */
	blocking_notअगरier_chain_unरेजिस्टर(&hndl->chain, nb);
	scmi_put_handler(ni, hndl);

	/*
	 * This balances the initial get issued in @scmi_notअगरier_रेजिस्टर.
	 * If this notअगरier_block happened to be the last known user callback
	 * क्रम this event, the handler is here मुक्तd and the event's generation
	 * stopped.
	 *
	 * Note that, an ongoing concurrent lookup on the delivery workqueue
	 * path could still hold the refcount to 1 even after this routine
	 * completes: in such a हाल it will be the final put on the delivery
	 * path which will finally मुक्त this unused handler.
	 */
	scmi_put_handler(ni, hndl);

	वापस 0;
पूर्ण

काष्ठा scmi_notअगरier_devres अणु
	स्थिर काष्ठा scmi_handle *handle;
	u8 proto_id;
	u8 evt_id;
	u32 __src_id;
	u32 *src_id;
	काष्ठा notअगरier_block *nb;
पूर्ण;

अटल व्योम scmi_devm_release_notअगरier(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा scmi_notअगरier_devres *dres = res;

	scmi_notअगरier_unरेजिस्टर(dres->handle, dres->proto_id, dres->evt_id,
				 dres->src_id, dres->nb);
पूर्ण

/**
 * scmi_devm_notअगरier_रेजिस्टर()  - Managed registration of a notअगरier_block
 * क्रम an event
 * @sdev: A reference to an scmi_device whose embedded काष्ठा device is to
 *	  be used क्रम devres accounting.
 * @proto_id: Protocol ID
 * @evt_id: Event ID
 * @src_id: Source ID, when शून्य रेजिस्टर क्रम events coming क्रमm ALL possible
 *	    sources
 * @nb: A standard notअगरier block to रेजिस्टर क्रम the specअगरied event
 *
 * Generic devres managed helper to रेजिस्टर a notअगरier_block against a
 * protocol event.
 */
अटल पूर्णांक scmi_devm_notअगरier_रेजिस्टर(काष्ठा scmi_device *sdev,
				       u8 proto_id, u8 evt_id,
				       स्थिर u32 *src_id,
				       काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक ret;
	काष्ठा scmi_notअगरier_devres *dres;

	dres = devres_alloc(scmi_devm_release_notअगरier,
			    माप(*dres), GFP_KERNEL);
	अगर (!dres)
		वापस -ENOMEM;

	ret = scmi_notअगरier_रेजिस्टर(sdev->handle, proto_id,
				     evt_id, src_id, nb);
	अगर (ret) अणु
		devres_मुक्त(dres);
		वापस ret;
	पूर्ण

	dres->handle = sdev->handle;
	dres->proto_id = proto_id;
	dres->evt_id = evt_id;
	dres->nb = nb;
	अगर (src_id) अणु
		dres->__src_id = *src_id;
		dres->src_id = &dres->__src_id;
	पूर्ण अन्यथा अणु
		dres->src_id = शून्य;
	पूर्ण
	devres_add(&sdev->dev, dres);

	वापस ret;
पूर्ण

अटल पूर्णांक scmi_devm_notअगरier_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा scmi_notअगरier_devres *dres = res;
	काष्ठा scmi_notअगरier_devres *xres = data;

	अगर (WARN_ON(!dres || !xres))
		वापस 0;

	वापस dres->proto_id == xres->proto_id &&
		dres->evt_id == xres->evt_id &&
		dres->nb == xres->nb &&
		((!dres->src_id && !xres->src_id) ||
		  (dres->src_id && xres->src_id &&
		   dres->__src_id == xres->__src_id));
पूर्ण

/**
 * scmi_devm_notअगरier_unरेजिस्टर()  - Managed un-registration of a
 * notअगरier_block क्रम an event
 * @sdev: A reference to an scmi_device whose embedded काष्ठा device is to
 *	  be used क्रम devres accounting.
 * @proto_id: Protocol ID
 * @evt_id: Event ID
 * @src_id: Source ID, when शून्य रेजिस्टर क्रम events coming क्रमm ALL possible
 *	    sources
 * @nb: A standard notअगरier block to रेजिस्टर क्रम the specअगरied event
 *
 * Generic devres managed helper to explicitly un-रेजिस्टर a notअगरier_block
 * against a protocol event, which was previously रेजिस्टरed using the above
 * @scmi_devm_notअगरier_रेजिस्टर.
 */
अटल पूर्णांक scmi_devm_notअगरier_unरेजिस्टर(काष्ठा scmi_device *sdev,
					 u8 proto_id, u8 evt_id,
					 स्थिर u32 *src_id,
					 काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक ret;
	काष्ठा scmi_notअगरier_devres dres;

	dres.handle = sdev->handle;
	dres.proto_id = proto_id;
	dres.evt_id = evt_id;
	अगर (src_id) अणु
		dres.__src_id = *src_id;
		dres.src_id = &dres.__src_id;
	पूर्ण अन्यथा अणु
		dres.src_id = शून्य;
	पूर्ण

	ret = devres_release(&sdev->dev, scmi_devm_release_notअगरier,
			     scmi_devm_notअगरier_match, &dres);

	WARN_ON(ret);

	वापस ret;
पूर्ण

/**
 * scmi_protocols_late_init()  - Worker क्रम late initialization
 * @work: The work item to use associated to the proper SCMI instance
 *
 * This kicks in whenever a new protocol has completed its own registration via
 * scmi_रेजिस्टर_protocol_events(): it is in अक्षरge of scanning the table of
 * pending handlers (रेजिस्टरed by users जबतक the related protocol was still
 * not initialized) and finalizing their initialization whenever possible;
 * invalid pending handlers are purged at this poपूर्णांक in समय.
 */
अटल व्योम scmi_protocols_late_init(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक bkt;
	काष्ठा scmi_event_handler *hndl;
	काष्ठा scmi_notअगरy_instance *ni;
	काष्ठा hlist_node *पंचांगp;

	ni = container_of(work, काष्ठा scmi_notअगरy_instance, init_work);

	/* Ensure protocols and events are up to date */
	smp_rmb();

	mutex_lock(&ni->pending_mtx);
	hash_क्रम_each_safe(ni->pending_events_handlers, bkt, पंचांगp, hndl, hash) अणु
		पूर्णांक ret;

		ret = scmi_bind_event_handler(ni, hndl);
		अगर (!ret) अणु
			dev_dbg(ni->handle->dev,
				"finalized PENDING handler - key:%X\n",
				hndl->key);
			ret = scmi_event_handler_enable_events(hndl);
			अगर (ret) अणु
				dev_dbg(ni->handle->dev,
					"purging INVALID handler - key:%X\n",
					hndl->key);
				scmi_put_active_handler(ni, hndl);
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = scmi_valid_pending_handler(ni, hndl);
			अगर (ret) अणु
				dev_dbg(ni->handle->dev,
					"purging PENDING handler - key:%X\n",
					hndl->key);
				/* this hndl can be only a pending one */
				scmi_put_handler_unlocked(ni, hndl);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&ni->pending_mtx);
पूर्ण

/*
 * notअगरy_ops are attached to the handle so that can be accessed
 * directly from an scmi_driver to रेजिस्टर its own notअगरiers.
 */
अटल स्थिर काष्ठा scmi_notअगरy_ops notअगरy_ops = अणु
	.devm_event_notअगरier_रेजिस्टर = scmi_devm_notअगरier_रेजिस्टर,
	.devm_event_notअगरier_unरेजिस्टर = scmi_devm_notअगरier_unरेजिस्टर,
	.event_notअगरier_रेजिस्टर = scmi_notअगरier_रेजिस्टर,
	.event_notअगरier_unरेजिस्टर = scmi_notअगरier_unरेजिस्टर,
पूर्ण;

/**
 * scmi_notअगरication_init()  - Initializes Notअगरication Core Support
 * @handle: The handle identअगरying the platक्रमm instance to initialize
 *
 * This function lays out all the basic resources needed by the notअगरication
 * core instance identअगरied by the provided handle: once करोne, all of the
 * SCMI Protocols can रेजिस्टर their events with the core during their own
 * initializations.
 *
 * Note that failing to initialize the core notअगरications support करोes not
 * cause the whole SCMI Protocols stack to fail its initialization.
 *
 * SCMI Notअगरication Initialization happens in 2 steps:
 * * initialization: basic common allocations (this function)
 * * registration: protocols asynchronously come पूर्णांकo lअगरe and रेजिस्टरs their
 *		   own supported list of events with the core; this causes
 *		   further per-protocol allocations
 *
 * Any user's callback registration attempt, referring a still not रेजिस्टरed
 * event, will be रेजिस्टरed as pending and finalized later (अगर possible)
 * by scmi_protocols_late_init() work.
 * This allows क्रम lazy initialization of SCMI Protocols due to late (or
 * missing) SCMI drivers' modules loading.
 *
 * Return: 0 on Success
 */
पूर्णांक scmi_notअगरication_init(काष्ठा scmi_handle *handle)
अणु
	व्योम *gid;
	काष्ठा scmi_notअगरy_instance *ni;

	gid = devres_खोलो_group(handle->dev, शून्य, GFP_KERNEL);
	अगर (!gid)
		वापस -ENOMEM;

	ni = devm_kzalloc(handle->dev, माप(*ni), GFP_KERNEL);
	अगर (!ni)
		जाओ err;

	ni->gid = gid;
	ni->handle = handle;

	ni->रेजिस्टरed_protocols = devm_kसुस्मृति(handle->dev, SCMI_MAX_PROTO,
						माप(अक्षर *), GFP_KERNEL);
	अगर (!ni->रेजिस्टरed_protocols)
		जाओ err;

	ni->notअगरy_wq = alloc_workqueue(dev_name(handle->dev),
					WQ_UNBOUND | WQ_FREEZABLE | WQ_SYSFS,
					0);
	अगर (!ni->notअगरy_wq)
		जाओ err;

	mutex_init(&ni->pending_mtx);
	hash_init(ni->pending_events_handlers);

	INIT_WORK(&ni->init_work, scmi_protocols_late_init);

	scmi_notअगरication_instance_data_set(handle, ni);
	handle->notअगरy_ops = &notअगरy_ops;
	/* Ensure handle is up to date */
	smp_wmb();

	dev_info(handle->dev, "Core Enabled.\n");

	devres_बंद_group(handle->dev, ni->gid);

	वापस 0;

err:
	dev_warn(handle->dev, "Initialization Failed.\n");
	devres_release_group(handle->dev, gid);
	वापस -ENOMEM;
पूर्ण

/**
 * scmi_notअगरication_निकास()  - Shutकरोwn and clean Notअगरication core
 * @handle: The handle identअगरying the platक्रमm instance to shutकरोwn
 */
व्योम scmi_notअगरication_निकास(काष्ठा scmi_handle *handle)
अणु
	काष्ठा scmi_notअगरy_instance *ni;

	ni = scmi_notअगरication_instance_data_get(handle);
	अगर (!ni)
		वापस;
	scmi_notअगरication_instance_data_set(handle, शून्य);

	/* Destroy जबतक letting pending work complete */
	destroy_workqueue(ni->notअगरy_wq);

	devres_release_group(ni->handle->dev, ni->gid);
पूर्ण
