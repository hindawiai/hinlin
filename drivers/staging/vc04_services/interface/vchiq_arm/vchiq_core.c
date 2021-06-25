<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2010-2012 Broadcom. All rights reserved. */

#समावेश <linux/types.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/bitops.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/kref.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "vchiq_core.h"

#घोषणा VCHIQ_SLOT_HANDLER_STACK 8192

#घोषणा HANDLE_STATE_SHIFT 12

#घोषणा SLOT_INFO_FROM_INDEX(state, index) (state->slot_info + (index))
#घोषणा SLOT_DATA_FROM_INDEX(state, index) (state->slot_data + (index))
#घोषणा SLOT_INDEX_FROM_DATA(state, data) \
	(((अचिन्हित पूर्णांक)((अक्षर *)data - (अक्षर *)state->slot_data)) / \
	VCHIQ_SLOT_SIZE)
#घोषणा SLOT_INDEX_FROM_INFO(state, info) \
	((अचिन्हित पूर्णांक)(info - state->slot_info))
#घोषणा SLOT_QUEUE_INDEX_FROM_POS(pos) \
	((पूर्णांक)((अचिन्हित पूर्णांक)(pos) / VCHIQ_SLOT_SIZE))
#घोषणा SLOT_QUEUE_INDEX_FROM_POS_MASKED(pos) \
	(SLOT_QUEUE_INDEX_FROM_POS(pos) & VCHIQ_SLOT_QUEUE_MASK)

#घोषणा BULK_INDEX(x) (x & (VCHIQ_NUM_SERVICE_BULKS - 1))

#घोषणा SRVTRACE_LEVEL(srv) \
	(((srv) && (srv)->trace) ? VCHIQ_LOG_TRACE : vchiq_core_msg_log_level)
#घोषणा SRVTRACE_ENABLED(srv, lev) \
	(((srv) && (srv)->trace) || (vchiq_core_msg_log_level >= (lev)))

काष्ठा vchiq_खोलो_payload अणु
	पूर्णांक fourcc;
	पूर्णांक client_id;
	लघु version;
	लघु version_min;
पूर्ण;

काष्ठा vchiq_खोलोack_payload अणु
	लघु version;
पूर्ण;

क्रमागत अणु
	QMFLAGS_IS_BLOCKING     = BIT(0),
	QMFLAGS_NO_MUTEX_LOCK   = BIT(1),
	QMFLAGS_NO_MUTEX_UNLOCK = BIT(2)
पूर्ण;

/* we require this क्रम consistency between endpoपूर्णांकs */
vchiq_अटल_निश्चित(माप(काष्ठा vchiq_header) == 8);
vchiq_अटल_निश्चित(IS_POW2(माप(काष्ठा vchiq_header)));
vchiq_अटल_निश्चित(IS_POW2(VCHIQ_NUM_CURRENT_BULKS));
vchiq_अटल_निश्चित(IS_POW2(VCHIQ_NUM_SERVICE_BULKS));
vchiq_अटल_निश्चित(IS_POW2(VCHIQ_MAX_SERVICES));
vchiq_अटल_निश्चित(VCHIQ_VERSION >= VCHIQ_VERSION_MIN);

/* Run समय control of log level, based on KERN_XXX level. */
पूर्णांक vchiq_core_log_level = VCHIQ_LOG_DEFAULT;
पूर्णांक vchiq_core_msg_log_level = VCHIQ_LOG_DEFAULT;
पूर्णांक vchiq_sync_log_level = VCHIQ_LOG_DEFAULT;

DEFINE_SPINLOCK(bulk_रुकोer_spinlock);
अटल DEFINE_SPINLOCK(quota_spinlock);

काष्ठा vchiq_state *vchiq_states[VCHIQ_MAX_STATES];
अटल अचिन्हित पूर्णांक handle_seq;

अटल स्थिर अक्षर *स्थिर srvstate_names[] = अणु
	"FREE",
	"HIDDEN",
	"LISTENING",
	"OPENING",
	"OPEN",
	"OPENSYNC",
	"CLOSESENT",
	"CLOSERECVD",
	"CLOSEWAIT",
	"CLOSED"
पूर्ण;

अटल स्थिर अक्षर *स्थिर reason_names[] = अणु
	"SERVICE_OPENED",
	"SERVICE_CLOSED",
	"MESSAGE_AVAILABLE",
	"BULK_TRANSMIT_DONE",
	"BULK_RECEIVE_DONE",
	"BULK_TRANSMIT_ABORTED",
	"BULK_RECEIVE_ABORTED"
पूर्ण;

अटल स्थिर अक्षर *स्थिर conn_state_names[] = अणु
	"DISCONNECTED",
	"CONNECTING",
	"CONNECTED",
	"PAUSING",
	"PAUSE_SENT",
	"PAUSED",
	"RESUMING",
	"PAUSE_TIMEOUT",
	"RESUME_TIMEOUT"
पूर्ण;

अटल व्योम
release_message_sync(काष्ठा vchiq_state *state, काष्ठा vchiq_header *header);

अटल स्थिर अक्षर *msg_type_str(अचिन्हित पूर्णांक msg_type)
अणु
	चयन (msg_type) अणु
	हाल VCHIQ_MSG_PADDING:       वापस "PADDING";
	हाल VCHIQ_MSG_CONNECT:       वापस "CONNECT";
	हाल VCHIQ_MSG_OPEN:          वापस "OPEN";
	हाल VCHIQ_MSG_OPENACK:       वापस "OPENACK";
	हाल VCHIQ_MSG_CLOSE:         वापस "CLOSE";
	हाल VCHIQ_MSG_DATA:          वापस "DATA";
	हाल VCHIQ_MSG_BULK_RX:       वापस "BULK_RX";
	हाल VCHIQ_MSG_BULK_TX:       वापस "BULK_TX";
	हाल VCHIQ_MSG_BULK_RX_DONE:  वापस "BULK_RX_DONE";
	हाल VCHIQ_MSG_BULK_TX_DONE:  वापस "BULK_TX_DONE";
	हाल VCHIQ_MSG_PAUSE:         वापस "PAUSE";
	हाल VCHIQ_MSG_RESUME:        वापस "RESUME";
	हाल VCHIQ_MSG_REMOTE_USE:    वापस "REMOTE_USE";
	हाल VCHIQ_MSG_REMOTE_RELEASE:      वापस "REMOTE_RELEASE";
	हाल VCHIQ_MSG_REMOTE_USE_ACTIVE:   वापस "REMOTE_USE_ACTIVE";
	पूर्ण
	वापस "???";
पूर्ण

अटल अंतरभूत व्योम
vchiq_set_service_state(काष्ठा vchiq_service *service, पूर्णांक newstate)
अणु
	vchiq_log_info(vchiq_core_log_level, "%d: srv:%d %s->%s",
		service->state->id, service->localport,
		srvstate_names[service->srvstate],
		srvstate_names[newstate]);
	service->srvstate = newstate;
पूर्ण

काष्ठा vchiq_service *
find_service_by_handle(अचिन्हित पूर्णांक handle)
अणु
	काष्ठा vchiq_service *service;

	rcu_पढ़ो_lock();
	service = handle_to_service(handle);
	अगर (service && service->srvstate != VCHIQ_SRVSTATE_FREE &&
	    service->handle == handle &&
	    kref_get_unless_zero(&service->ref_count)) अणु
		service = rcu_poपूर्णांकer_hanकरोff(service);
		rcu_पढ़ो_unlock();
		वापस service;
	पूर्ण
	rcu_पढ़ो_unlock();
	vchiq_log_info(vchiq_core_log_level,
		       "Invalid service handle 0x%x", handle);
	वापस शून्य;
पूर्ण

काष्ठा vchiq_service *
find_service_by_port(काष्ठा vchiq_state *state, पूर्णांक localport)
अणु

	अगर ((अचिन्हित पूर्णांक)localport <= VCHIQ_PORT_MAX) अणु
		काष्ठा vchiq_service *service;

		rcu_पढ़ो_lock();
		service = rcu_dereference(state->services[localport]);
		अगर (service && service->srvstate != VCHIQ_SRVSTATE_FREE &&
		    kref_get_unless_zero(&service->ref_count)) अणु
			service = rcu_poपूर्णांकer_hanकरोff(service);
			rcu_पढ़ो_unlock();
			वापस service;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
	vchiq_log_info(vchiq_core_log_level,
		       "Invalid port %d", localport);
	वापस शून्य;
पूर्ण

काष्ठा vchiq_service *
find_service_क्रम_instance(काष्ठा vchiq_instance *instance,
	अचिन्हित पूर्णांक handle)
अणु
	काष्ठा vchiq_service *service;

	rcu_पढ़ो_lock();
	service = handle_to_service(handle);
	अगर (service && service->srvstate != VCHIQ_SRVSTATE_FREE &&
	    service->handle == handle &&
	    service->instance == instance &&
	    kref_get_unless_zero(&service->ref_count)) अणु
		service = rcu_poपूर्णांकer_hanकरोff(service);
		rcu_पढ़ो_unlock();
		वापस service;
	पूर्ण
	rcu_पढ़ो_unlock();
	vchiq_log_info(vchiq_core_log_level,
		       "Invalid service handle 0x%x", handle);
	वापस शून्य;
पूर्ण

काष्ठा vchiq_service *
find_बंदd_service_क्रम_instance(काष्ठा vchiq_instance *instance,
	अचिन्हित पूर्णांक handle)
अणु
	काष्ठा vchiq_service *service;

	rcu_पढ़ो_lock();
	service = handle_to_service(handle);
	अगर (service &&
	    (service->srvstate == VCHIQ_SRVSTATE_FREE ||
	     service->srvstate == VCHIQ_SRVSTATE_CLOSED) &&
	    service->handle == handle &&
	    service->instance == instance &&
	    kref_get_unless_zero(&service->ref_count)) अणु
		service = rcu_poपूर्णांकer_hanकरोff(service);
		rcu_पढ़ो_unlock();
		वापस service;
	पूर्ण
	rcu_पढ़ो_unlock();
	vchiq_log_info(vchiq_core_log_level,
		       "Invalid service handle 0x%x", handle);
	वापस service;
पूर्ण

काष्ठा vchiq_service *
__next_service_by_instance(काष्ठा vchiq_state *state,
			   काष्ठा vchiq_instance *instance,
			   पूर्णांक *pidx)
अणु
	काष्ठा vchiq_service *service = शून्य;
	पूर्णांक idx = *pidx;

	जबतक (idx < state->unused_service) अणु
		काष्ठा vchiq_service *srv;

		srv = rcu_dereference(state->services[idx++]);
		अगर (srv && srv->srvstate != VCHIQ_SRVSTATE_FREE &&
		    srv->instance == instance) अणु
			service = srv;
			अवरोध;
		पूर्ण
	पूर्ण

	*pidx = idx;
	वापस service;
पूर्ण

काष्ठा vchiq_service *
next_service_by_instance(काष्ठा vchiq_state *state,
			 काष्ठा vchiq_instance *instance,
			 पूर्णांक *pidx)
अणु
	काष्ठा vchiq_service *service;

	rcu_पढ़ो_lock();
	जबतक (1) अणु
		service = __next_service_by_instance(state, instance, pidx);
		अगर (!service)
			अवरोध;
		अगर (kref_get_unless_zero(&service->ref_count)) अणु
			service = rcu_poपूर्णांकer_hanकरोff(service);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस service;
पूर्ण

व्योम
lock_service(काष्ठा vchiq_service *service)
अणु
	अगर (!service) अणु
		WARN(1, "%s service is NULL\n", __func__);
		वापस;
	पूर्ण
	kref_get(&service->ref_count);
पूर्ण

अटल व्योम service_release(काष्ठा kref *kref)
अणु
	काष्ठा vchiq_service *service =
		container_of(kref, काष्ठा vchiq_service, ref_count);
	काष्ठा vchiq_state *state = service->state;

	WARN_ON(service->srvstate != VCHIQ_SRVSTATE_FREE);
	rcu_assign_poपूर्णांकer(state->services[service->localport], शून्य);
	अगर (service->userdata_term)
		service->userdata_term(service->base.userdata);
	kमुक्त_rcu(service, rcu);
पूर्ण

व्योम
unlock_service(काष्ठा vchiq_service *service)
अणु
	अगर (!service) अणु
		WARN(1, "%s: service is NULL\n", __func__);
		वापस;
	पूर्ण
	kref_put(&service->ref_count, service_release);
पूर्ण

पूर्णांक
vchiq_get_client_id(अचिन्हित पूर्णांक handle)
अणु
	काष्ठा vchiq_service *service;
	पूर्णांक id;

	rcu_पढ़ो_lock();
	service = handle_to_service(handle);
	id = service ? service->client_id : 0;
	rcu_पढ़ो_unlock();
	वापस id;
पूर्ण

व्योम *
vchiq_get_service_userdata(अचिन्हित पूर्णांक handle)
अणु
	व्योम *userdata;
	काष्ठा vchiq_service *service;

	rcu_पढ़ो_lock();
	service = handle_to_service(handle);
	userdata = service ? service->base.userdata : शून्य;
	rcu_पढ़ो_unlock();
	वापस userdata;
पूर्ण
EXPORT_SYMBOL(vchiq_get_service_userdata);

अटल व्योम
mark_service_closing_पूर्णांकernal(काष्ठा vchiq_service *service, पूर्णांक sh_thपढ़ो)
अणु
	काष्ठा vchiq_state *state = service->state;
	काष्ठा vchiq_service_quota *quota;

	service->closing = 1;

	/* Synchronise with other thपढ़ोs. */
	mutex_lock(&state->recycle_mutex);
	mutex_unlock(&state->recycle_mutex);
	अगर (!sh_thपढ़ो || (state->conn_state != VCHIQ_CONNSTATE_PAUSE_SENT)) अणु
		/*
		 * If we're pausing then the slot_mutex is held until resume
		 * by the slot handler.  Thereक्रमe करोn't try to acquire this
		 * mutex अगर we're the slot handler and in the छोड़ो sent state.
		 * We करोn't need to in this हाल anyway.
		 */
		mutex_lock(&state->slot_mutex);
		mutex_unlock(&state->slot_mutex);
	पूर्ण

	/* Unblock any sending thपढ़ो. */
	quota = &state->service_quotas[service->localport];
	complete(&quota->quota_event);
पूर्ण

अटल व्योम
mark_service_closing(काष्ठा vchiq_service *service)
अणु
	mark_service_closing_पूर्णांकernal(service, 0);
पूर्ण

अटल अंतरभूत क्रमागत vchiq_status
make_service_callback(काष्ठा vchiq_service *service, क्रमागत vchiq_reason reason,
		      काष्ठा vchiq_header *header, व्योम *bulk_userdata)
अणु
	क्रमागत vchiq_status status;

	vchiq_log_trace(vchiq_core_log_level, "%d: callback:%d (%s, %pK, %pK)",
		service->state->id, service->localport, reason_names[reason],
		header, bulk_userdata);
	status = service->base.callback(reason, header, service->handle,
		bulk_userdata);
	अगर (status == VCHIQ_ERROR) अणु
		vchiq_log_warning(vchiq_core_log_level,
			"%d: ignoring ERROR from callback to service %x",
			service->state->id, service->handle);
		status = VCHIQ_SUCCESS;
	पूर्ण

	अगर (reason != VCHIQ_MESSAGE_AVAILABLE)
		vchiq_release_message(service->handle, header);

	वापस status;
पूर्ण

अंतरभूत व्योम
vchiq_set_conn_state(काष्ठा vchiq_state *state, क्रमागत vchiq_connstate newstate)
अणु
	क्रमागत vchiq_connstate oldstate = state->conn_state;

	vchiq_log_info(vchiq_core_log_level, "%d: %s->%s", state->id,
		conn_state_names[oldstate],
		conn_state_names[newstate]);
	state->conn_state = newstate;
	vchiq_platक्रमm_conn_state_changed(state, oldstate, newstate);
पूर्ण

अटल अंतरभूत व्योम
remote_event_create(रुको_queue_head_t *wq, काष्ठा remote_event *event)
अणु
	event->armed = 0;
	/*
	 * Don't clear the 'fired' flag because it may alपढ़ोy have been set
	 * by the other side.
	 */
	init_रुकोqueue_head(wq);
पूर्ण

/*
 * All the event रुकोing routines in VCHIQ used a custom semaphore
 * implementation that filtered most संकेतs. This achieved a behaviour similar
 * to the "killable" family of functions. While cleaning up this code all the
 * routines where चयनed to the "interruptible" family of functions, as the
 * क्रमmer was deemed unjustअगरied and the use "killable" set all VCHIQ's
 * thपढ़ोs in D state.
 */
अटल अंतरभूत पूर्णांक
remote_event_रुको(रुको_queue_head_t *wq, काष्ठा remote_event *event)
अणु
	अगर (!event->fired) अणु
		event->armed = 1;
		dsb(sy);
		अगर (रुको_event_पूर्णांकerruptible(*wq, event->fired)) अणु
			event->armed = 0;
			वापस 0;
		पूर्ण
		event->armed = 0;
		wmb();
	पूर्ण

	event->fired = 0;
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम
remote_event_संकेत_local(रुको_queue_head_t *wq, काष्ठा remote_event *event)
अणु
	event->fired = 1;
	event->armed = 0;
	wake_up_all(wq);
पूर्ण

अटल अंतरभूत व्योम
remote_event_poll(रुको_queue_head_t *wq, काष्ठा remote_event *event)
अणु
	अगर (event->fired && event->armed)
		remote_event_संकेत_local(wq, event);
पूर्ण

व्योम
remote_event_pollall(काष्ठा vchiq_state *state)
अणु
	remote_event_poll(&state->sync_trigger_event, &state->local->sync_trigger);
	remote_event_poll(&state->sync_release_event, &state->local->sync_release);
	remote_event_poll(&state->trigger_event, &state->local->trigger);
	remote_event_poll(&state->recycle_event, &state->local->recycle);
पूर्ण

/*
 * Round up message sizes so that any space at the end of a slot is always big
 * enough क्रम a header. This relies on header size being a घातer of two, which
 * has been verअगरied earlier by a अटल निश्चितion.
 */

अटल अंतरभूत माप_प्रकार
calc_stride(माप_प्रकार size)
अणु
	/* Allow room क्रम the header */
	size += माप(काष्ठा vchiq_header);

	/* Round up */
	वापस (size + माप(काष्ठा vchiq_header) - 1) &
		~(माप(काष्ठा vchiq_header) - 1);
पूर्ण

/* Called by the slot handler thपढ़ो */
अटल काष्ठा vchiq_service *
get_listening_service(काष्ठा vchiq_state *state, पूर्णांक fourcc)
अणु
	पूर्णांक i;

	WARN_ON(fourcc == VCHIQ_FOURCC_INVALID);

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < state->unused_service; i++) अणु
		काष्ठा vchiq_service *service;

		service = rcu_dereference(state->services[i]);
		अगर (service &&
		    service->खुला_fourcc == fourcc &&
		    (service->srvstate == VCHIQ_SRVSTATE_LISTENING ||
		     (service->srvstate == VCHIQ_SRVSTATE_OPEN &&
		      service->remoteport == VCHIQ_PORT_FREE)) &&
		    kref_get_unless_zero(&service->ref_count)) अणु
			service = rcu_poपूर्णांकer_hanकरोff(service);
			rcu_पढ़ो_unlock();
			वापस service;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

/* Called by the slot handler thपढ़ो */
अटल काष्ठा vchiq_service *
get_connected_service(काष्ठा vchiq_state *state, अचिन्हित पूर्णांक port)
अणु
	पूर्णांक i;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < state->unused_service; i++) अणु
		काष्ठा vchiq_service *service =
			rcu_dereference(state->services[i]);

		अगर (service && service->srvstate == VCHIQ_SRVSTATE_OPEN &&
		    service->remoteport == port &&
		    kref_get_unless_zero(&service->ref_count)) अणु
			service = rcu_poपूर्णांकer_hanकरोff(service);
			rcu_पढ़ो_unlock();
			वापस service;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

अंतरभूत व्योम
request_poll(काष्ठा vchiq_state *state, काष्ठा vchiq_service *service,
	     पूर्णांक poll_type)
अणु
	u32 value;
	पूर्णांक index;

	अगर (!service)
		जाओ skip_service;

	करो अणु
		value = atomic_पढ़ो(&service->poll_flags);
	पूर्ण जबतक (atomic_cmpxchg(&service->poll_flags, value,
		 value | BIT(poll_type)) != value);

	index = BITSET_WORD(service->localport);
	करो अणु
		value = atomic_पढ़ो(&state->poll_services[index]);
	पूर्ण जबतक (atomic_cmpxchg(&state->poll_services[index],
		 value, value | BIT(service->localport & 0x1f)) != value);

skip_service:
	state->poll_needed = 1;
	wmb();

	/* ... and ensure the slot handler runs. */
	remote_event_संकेत_local(&state->trigger_event, &state->local->trigger);
पूर्ण

/*
 * Called from queue_message, by the slot handler and application thपढ़ोs,
 * with slot_mutex held
 */
अटल काष्ठा vchiq_header *
reserve_space(काष्ठा vchiq_state *state, माप_प्रकार space, पूर्णांक is_blocking)
अणु
	काष्ठा vchiq_shared_state *local = state->local;
	पूर्णांक tx_pos = state->local_tx_pos;
	पूर्णांक slot_space = VCHIQ_SLOT_SIZE - (tx_pos & VCHIQ_SLOT_MASK);

	अगर (space > slot_space) अणु
		काष्ठा vchiq_header *header;
		/* Fill the reमुख्यing space with padding */
		WARN_ON(!state->tx_data);
		header = (काष्ठा vchiq_header *)
			(state->tx_data + (tx_pos & VCHIQ_SLOT_MASK));
		header->msgid = VCHIQ_MSGID_PADDING;
		header->size = slot_space - माप(काष्ठा vchiq_header);

		tx_pos += slot_space;
	पूर्ण

	/* If necessary, get the next slot. */
	अगर ((tx_pos & VCHIQ_SLOT_MASK) == 0) अणु
		पूर्णांक slot_index;

		/* If there is no मुक्त slot... */

		अगर (!try_रुको_क्रम_completion(&state->slot_available_event)) अणु
			/* ...रुको क्रम one. */

			VCHIQ_STATS_INC(state, slot_stalls);

			/* But first, flush through the last slot. */
			state->local_tx_pos = tx_pos;
			local->tx_pos = tx_pos;
			remote_event_संकेत(&state->remote->trigger);

			अगर (!is_blocking ||
				(रुको_क्रम_completion_पूर्णांकerruptible(
				&state->slot_available_event)))
				वापस शून्य; /* No space available */
		पूर्ण

		अगर (tx_pos == (state->slot_queue_available * VCHIQ_SLOT_SIZE)) अणु
			complete(&state->slot_available_event);
			pr_warn("%s: invalid tx_pos: %d\n", __func__, tx_pos);
			वापस शून्य;
		पूर्ण

		slot_index = local->slot_queue[
			SLOT_QUEUE_INDEX_FROM_POS_MASKED(tx_pos)];
		state->tx_data =
			(अक्षर *)SLOT_DATA_FROM_INDEX(state, slot_index);
	पूर्ण

	state->local_tx_pos = tx_pos + space;

	वापस (काष्ठा vchiq_header *)(state->tx_data +
						(tx_pos & VCHIQ_SLOT_MASK));
पूर्ण

/* Called by the recycle thपढ़ो. */
अटल व्योम
process_मुक्त_queue(काष्ठा vchiq_state *state, BITSET_T *service_found,
		   माप_प्रकार length)
अणु
	काष्ठा vchiq_shared_state *local = state->local;
	पूर्णांक slot_queue_available;

	/*
	 * Find slots which have been मुक्तd by the other side, and वापस them
	 * to the available queue.
	 */
	slot_queue_available = state->slot_queue_available;

	/*
	 * Use a memory barrier to ensure that any state that may have been
	 * modअगरied by another thपढ़ो is not masked by stale prefetched
	 * values.
	 */
	mb();

	जबतक (slot_queue_available != local->slot_queue_recycle) अणु
		अचिन्हित पूर्णांक pos;
		पूर्णांक slot_index = local->slot_queue[slot_queue_available++ &
			VCHIQ_SLOT_QUEUE_MASK];
		अक्षर *data = (अक्षर *)SLOT_DATA_FROM_INDEX(state, slot_index);
		पूर्णांक data_found = 0;

		/*
		 * Beware of the address dependency - data is calculated
		 * using an index written by the other side.
		 */
		rmb();

		vchiq_log_trace(vchiq_core_log_level, "%d: pfq %d=%pK %x %x",
			state->id, slot_index, data,
			local->slot_queue_recycle, slot_queue_available);

		/* Initialise the biपंचांगask क्रम services which have used this slot */
		स_रखो(service_found, 0, length);

		pos = 0;

		जबतक (pos < VCHIQ_SLOT_SIZE) अणु
			काष्ठा vchiq_header *header =
				(काष्ठा vchiq_header *)(data + pos);
			पूर्णांक msgid = header->msgid;

			अगर (VCHIQ_MSG_TYPE(msgid) == VCHIQ_MSG_DATA) अणु
				पूर्णांक port = VCHIQ_MSG_SRCPORT(msgid);
				काष्ठा vchiq_service_quota *quota =
					&state->service_quotas[port];
				पूर्णांक count;

				spin_lock(&quota_spinlock);
				count = quota->message_use_count;
				अगर (count > 0)
					quota->message_use_count =
						count - 1;
				spin_unlock(&quota_spinlock);

				अगर (count == quota->message_quota)
					/*
					 * Signal the service that it
					 * has dropped below its quota
					 */
					complete(&quota->quota_event);
				अन्यथा अगर (count == 0) अणु
					vchiq_log_error(vchiq_core_log_level,
						"service %d message_use_count=%d (header %pK, msgid %x, header->msgid %x, header->size %x)",
						port,
						quota->message_use_count,
						header, msgid, header->msgid,
						header->size);
					WARN(1, "invalid message use count\n");
				पूर्ण
				अगर (!BITSET_IS_SET(service_found, port)) अणु
					/* Set the found bit क्रम this service */
					BITSET_SET(service_found, port);

					spin_lock(&quota_spinlock);
					count = quota->slot_use_count;
					अगर (count > 0)
						quota->slot_use_count =
							count - 1;
					spin_unlock(&quota_spinlock);

					अगर (count > 0) अणु
						/*
						 * Signal the service in हाल
						 * it has dropped below its quota
						 */
						complete(&quota->quota_event);
						vchiq_log_trace(
							vchiq_core_log_level,
							"%d: pfq:%d %x@%pK - slot_use->%d",
							state->id, port,
							header->size, header,
							count - 1);
					पूर्ण अन्यथा अणु
						vchiq_log_error(
							vchiq_core_log_level,
								"service %d slot_use_count=%d (header %pK, msgid %x, header->msgid %x, header->size %x)",
							port, count, header,
							msgid, header->msgid,
							header->size);
						WARN(1, "bad slot use count\n");
					पूर्ण
				पूर्ण

				data_found = 1;
			पूर्ण

			pos += calc_stride(header->size);
			अगर (pos > VCHIQ_SLOT_SIZE) अणु
				vchiq_log_error(vchiq_core_log_level,
					"pfq - pos %x: header %pK, msgid %x, header->msgid %x, header->size %x",
					pos, header, msgid, header->msgid,
					header->size);
				WARN(1, "invalid slot position\n");
			पूर्ण
		पूर्ण

		अगर (data_found) अणु
			पूर्णांक count;

			spin_lock(&quota_spinlock);
			count = state->data_use_count;
			अगर (count > 0)
				state->data_use_count =
					count - 1;
			spin_unlock(&quota_spinlock);
			अगर (count == state->data_quota)
				complete(&state->data_quota_event);
		पूर्ण

		/*
		 * Don't allow the slot to be reused until we are no
		 * दीर्घer पूर्णांकerested in it.
		 */
		mb();

		state->slot_queue_available = slot_queue_available;
		complete(&state->slot_available_event);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
स_नकल_copy_callback(
	व्योम *context, व्योम *dest,
	माप_प्रकार offset, माप_प्रकार maxsize)
अणु
	स_नकल(dest + offset, context + offset, maxsize);
	वापस maxsize;
पूर्ण

अटल sमाप_प्रकार
copy_message_data(
	sमाप_प्रकार (*copy_callback)(व्योम *context, व्योम *dest,
				 माप_प्रकार offset, माप_प्रकार maxsize),
	व्योम *context,
	व्योम *dest,
	माप_प्रकार size)
अणु
	माप_प्रकार pos = 0;

	जबतक (pos < size) अणु
		sमाप_प्रकार callback_result;
		माप_प्रकार max_bytes = size - pos;

		callback_result =
			copy_callback(context, dest + pos,
				      pos, max_bytes);

		अगर (callback_result < 0)
			वापस callback_result;

		अगर (!callback_result)
			वापस -EIO;

		अगर (callback_result > max_bytes)
			वापस -EIO;

		pos += callback_result;
	पूर्ण

	वापस size;
पूर्ण

/* Called by the slot handler and application thपढ़ोs */
अटल क्रमागत vchiq_status
queue_message(काष्ठा vchiq_state *state, काष्ठा vchiq_service *service,
	      पूर्णांक msgid,
	      sमाप_प्रकार (*copy_callback)(व्योम *context, व्योम *dest,
				       माप_प्रकार offset, माप_प्रकार maxsize),
	      व्योम *context, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा vchiq_shared_state *local;
	काष्ठा vchiq_service_quota *quota = शून्य;
	काष्ठा vchiq_header *header;
	पूर्णांक type = VCHIQ_MSG_TYPE(msgid);

	माप_प्रकार stride;

	local = state->local;

	stride = calc_stride(size);

	WARN_ON(!(stride <= VCHIQ_SLOT_SIZE));

	अगर (!(flags & QMFLAGS_NO_MUTEX_LOCK) &&
	    mutex_lock_समाप्तable(&state->slot_mutex))
		वापस VCHIQ_RETRY;

	अगर (type == VCHIQ_MSG_DATA) अणु
		पूर्णांक tx_end_index;

		अगर (!service) अणु
			WARN(1, "%s: service is NULL\n", __func__);
			mutex_unlock(&state->slot_mutex);
			वापस VCHIQ_ERROR;
		पूर्ण

		WARN_ON(flags & (QMFLAGS_NO_MUTEX_LOCK |
				 QMFLAGS_NO_MUTEX_UNLOCK));

		अगर (service->closing) अणु
			/* The service has been बंदd */
			mutex_unlock(&state->slot_mutex);
			वापस VCHIQ_ERROR;
		पूर्ण

		quota = &state->service_quotas[service->localport];

		spin_lock(&quota_spinlock);

		/*
		 * Ensure this service करोesn't use more than its quota of
		 * messages or slots
		 */
		tx_end_index = SLOT_QUEUE_INDEX_FROM_POS(
			state->local_tx_pos + stride - 1);

		/*
		 * Ensure data messages करोn't use more than their quota of
		 * slots
		 */
		जबतक ((tx_end_index != state->previous_data_index) &&
			(state->data_use_count == state->data_quota)) अणु
			VCHIQ_STATS_INC(state, data_stalls);
			spin_unlock(&quota_spinlock);
			mutex_unlock(&state->slot_mutex);

			अगर (रुको_क्रम_completion_पूर्णांकerruptible(
						&state->data_quota_event))
				वापस VCHIQ_RETRY;

			mutex_lock(&state->slot_mutex);
			spin_lock(&quota_spinlock);
			tx_end_index = SLOT_QUEUE_INDEX_FROM_POS(
				state->local_tx_pos + stride - 1);
			अगर ((tx_end_index == state->previous_data_index) ||
				(state->data_use_count < state->data_quota)) अणु
				/* Pass the संकेत on to other रुकोers */
				complete(&state->data_quota_event);
				अवरोध;
			पूर्ण
		पूर्ण

		जबतक ((quota->message_use_count == quota->message_quota) ||
			((tx_end_index != quota->previous_tx_index) &&
			(quota->slot_use_count ==
				quota->slot_quota))) अणु
			spin_unlock(&quota_spinlock);
			vchiq_log_trace(vchiq_core_log_level,
				"%d: qm:%d %s,%zx - quota stall (msg %d, slot %d)",
				state->id, service->localport,
				msg_type_str(type), size,
				quota->message_use_count,
				quota->slot_use_count);
			VCHIQ_SERVICE_STATS_INC(service, quota_stalls);
			mutex_unlock(&state->slot_mutex);
			अगर (रुको_क्रम_completion_पूर्णांकerruptible(
						&quota->quota_event))
				वापस VCHIQ_RETRY;
			अगर (service->closing)
				वापस VCHIQ_ERROR;
			अगर (mutex_lock_समाप्तable(&state->slot_mutex))
				वापस VCHIQ_RETRY;
			अगर (service->srvstate != VCHIQ_SRVSTATE_OPEN) अणु
				/* The service has been बंदd */
				mutex_unlock(&state->slot_mutex);
				वापस VCHIQ_ERROR;
			पूर्ण
			spin_lock(&quota_spinlock);
			tx_end_index = SLOT_QUEUE_INDEX_FROM_POS(
				state->local_tx_pos + stride - 1);
		पूर्ण

		spin_unlock(&quota_spinlock);
	पूर्ण

	header = reserve_space(state, stride, flags & QMFLAGS_IS_BLOCKING);

	अगर (!header) अणु
		अगर (service)
			VCHIQ_SERVICE_STATS_INC(service, slot_stalls);
		/*
		 * In the event of a failure, वापस the mutex to the
		 * state it was in
		 */
		अगर (!(flags & QMFLAGS_NO_MUTEX_LOCK))
			mutex_unlock(&state->slot_mutex);
		वापस VCHIQ_RETRY;
	पूर्ण

	अगर (type == VCHIQ_MSG_DATA) अणु
		sमाप_प्रकार callback_result;
		पूर्णांक tx_end_index;
		पूर्णांक slot_use_count;

		vchiq_log_info(vchiq_core_log_level,
			"%d: qm %s@%pK,%zx (%d->%d)",
			state->id, msg_type_str(VCHIQ_MSG_TYPE(msgid)),
			header, size, VCHIQ_MSG_SRCPORT(msgid),
			VCHIQ_MSG_DSTPORT(msgid));

		WARN_ON(flags & (QMFLAGS_NO_MUTEX_LOCK |
				 QMFLAGS_NO_MUTEX_UNLOCK));

		callback_result =
			copy_message_data(copy_callback, context,
					  header->data, size);

		अगर (callback_result < 0) अणु
			mutex_unlock(&state->slot_mutex);
			VCHIQ_SERVICE_STATS_INC(service,
						error_count);
			वापस VCHIQ_ERROR;
		पूर्ण

		अगर (SRVTRACE_ENABLED(service,
				     VCHIQ_LOG_INFO))
			vchiq_log_dump_mem("Sent", 0,
					   header->data,
					   min((माप_प्रकार)16,
					       (माप_प्रकार)callback_result));

		spin_lock(&quota_spinlock);
		quota->message_use_count++;

		tx_end_index =
			SLOT_QUEUE_INDEX_FROM_POS(state->local_tx_pos - 1);

		/*
		 * If this transmission can't fit in the last slot used by any
		 * service, the data_use_count must be increased.
		 */
		अगर (tx_end_index != state->previous_data_index) अणु
			state->previous_data_index = tx_end_index;
			state->data_use_count++;
		पूर्ण

		/*
		 * If this isn't the same slot last used by this service,
		 * the service's slot_use_count must be increased.
		 */
		अगर (tx_end_index != quota->previous_tx_index) अणु
			quota->previous_tx_index = tx_end_index;
			slot_use_count = ++quota->slot_use_count;
		पूर्ण अन्यथा अणु
			slot_use_count = 0;
		पूर्ण

		spin_unlock(&quota_spinlock);

		अगर (slot_use_count)
			vchiq_log_trace(vchiq_core_log_level,
				"%d: qm:%d %s,%zx - slot_use->%d (hdr %p)",
				state->id, service->localport,
				msg_type_str(VCHIQ_MSG_TYPE(msgid)), size,
				slot_use_count, header);

		VCHIQ_SERVICE_STATS_INC(service, ctrl_tx_count);
		VCHIQ_SERVICE_STATS_ADD(service, ctrl_tx_bytes, size);
	पूर्ण अन्यथा अणु
		vchiq_log_info(vchiq_core_log_level,
			"%d: qm %s@%pK,%zx (%d->%d)", state->id,
			msg_type_str(VCHIQ_MSG_TYPE(msgid)),
			header, size, VCHIQ_MSG_SRCPORT(msgid),
			VCHIQ_MSG_DSTPORT(msgid));
		अगर (size != 0) अणु
			/*
			 * It is assumed क्रम now that this code path
			 * only happens from calls inside this file.
			 *
			 * External callers are through the vchiq_queue_message
			 * path which always sets the type to be VCHIQ_MSG_DATA
			 *
			 * At first glance this appears to be correct but
			 * more review is needed.
			 */
			copy_message_data(copy_callback, context,
					  header->data, size);
		पूर्ण
		VCHIQ_STATS_INC(state, ctrl_tx_count);
	पूर्ण

	header->msgid = msgid;
	header->size = size;

	अणु
		पूर्णांक svc_fourcc;

		svc_fourcc = service
			? service->base.fourcc
			: VCHIQ_MAKE_FOURCC('?', '?', '?', '?');

		vchiq_log_info(SRVTRACE_LEVEL(service),
			"Sent Msg %s(%u) to %c%c%c%c s:%u d:%d len:%zu",
			msg_type_str(VCHIQ_MSG_TYPE(msgid)),
			VCHIQ_MSG_TYPE(msgid),
			VCHIQ_FOURCC_AS_4CHARS(svc_fourcc),
			VCHIQ_MSG_SRCPORT(msgid),
			VCHIQ_MSG_DSTPORT(msgid),
			size);
	पूर्ण

	/* Make sure the new header is visible to the peer. */
	wmb();

	/* Make the new tx_pos visible to the peer. */
	local->tx_pos = state->local_tx_pos;
	wmb();

	अगर (service && (type == VCHIQ_MSG_CLOSE))
		vchiq_set_service_state(service, VCHIQ_SRVSTATE_CLOSESENT);

	अगर (!(flags & QMFLAGS_NO_MUTEX_UNLOCK))
		mutex_unlock(&state->slot_mutex);

	remote_event_संकेत(&state->remote->trigger);

	वापस VCHIQ_SUCCESS;
पूर्ण

/* Called by the slot handler and application thपढ़ोs */
अटल क्रमागत vchiq_status
queue_message_sync(काष्ठा vchiq_state *state, काष्ठा vchiq_service *service,
		   पूर्णांक msgid,
		   sमाप_प्रकार (*copy_callback)(व्योम *context, व्योम *dest,
					    माप_प्रकार offset, माप_प्रकार maxsize),
		   व्योम *context, पूर्णांक size, पूर्णांक is_blocking)
अणु
	काष्ठा vchiq_shared_state *local;
	काष्ठा vchiq_header *header;
	sमाप_प्रकार callback_result;

	local = state->local;

	अगर (VCHIQ_MSG_TYPE(msgid) != VCHIQ_MSG_RESUME &&
	    mutex_lock_समाप्तable(&state->sync_mutex))
		वापस VCHIQ_RETRY;

	remote_event_रुको(&state->sync_release_event, &local->sync_release);

	rmb();

	header = (काष्ठा vchiq_header *)SLOT_DATA_FROM_INDEX(state,
		local->slot_sync);

	अणु
		पूर्णांक oldmsgid = header->msgid;

		अगर (oldmsgid != VCHIQ_MSGID_PADDING)
			vchiq_log_error(vchiq_core_log_level,
				"%d: qms - msgid %x, not PADDING",
				state->id, oldmsgid);
	पूर्ण

	vchiq_log_info(vchiq_sync_log_level,
		       "%d: qms %s@%pK,%x (%d->%d)", state->id,
		       msg_type_str(VCHIQ_MSG_TYPE(msgid)),
		       header, size, VCHIQ_MSG_SRCPORT(msgid),
		       VCHIQ_MSG_DSTPORT(msgid));

	callback_result =
		copy_message_data(copy_callback, context,
				  header->data, size);

	अगर (callback_result < 0) अणु
		mutex_unlock(&state->slot_mutex);
		VCHIQ_SERVICE_STATS_INC(service,
					error_count);
		वापस VCHIQ_ERROR;
	पूर्ण

	अगर (service) अणु
		अगर (SRVTRACE_ENABLED(service,
				     VCHIQ_LOG_INFO))
			vchiq_log_dump_mem("Sent", 0,
					   header->data,
					   min((माप_प्रकार)16,
					       (माप_प्रकार)callback_result));

		VCHIQ_SERVICE_STATS_INC(service, ctrl_tx_count);
		VCHIQ_SERVICE_STATS_ADD(service, ctrl_tx_bytes, size);
	पूर्ण अन्यथा अणु
		VCHIQ_STATS_INC(state, ctrl_tx_count);
	पूर्ण

	header->size = size;
	header->msgid = msgid;

	अगर (vchiq_sync_log_level >= VCHIQ_LOG_TRACE) अणु
		पूर्णांक svc_fourcc;

		svc_fourcc = service
			? service->base.fourcc
			: VCHIQ_MAKE_FOURCC('?', '?', '?', '?');

		vchiq_log_trace(vchiq_sync_log_level,
			"Sent Sync Msg %s(%u) to %c%c%c%c s:%u d:%d len:%d",
			msg_type_str(VCHIQ_MSG_TYPE(msgid)),
			VCHIQ_MSG_TYPE(msgid),
			VCHIQ_FOURCC_AS_4CHARS(svc_fourcc),
			VCHIQ_MSG_SRCPORT(msgid),
			VCHIQ_MSG_DSTPORT(msgid),
			size);
	पूर्ण

	remote_event_संकेत(&state->remote->sync_trigger);

	अगर (VCHIQ_MSG_TYPE(msgid) != VCHIQ_MSG_PAUSE)
		mutex_unlock(&state->sync_mutex);

	वापस VCHIQ_SUCCESS;
पूर्ण

अटल अंतरभूत व्योम
claim_slot(काष्ठा vchiq_slot_info *slot)
अणु
	slot->use_count++;
पूर्ण

अटल व्योम
release_slot(काष्ठा vchiq_state *state, काष्ठा vchiq_slot_info *slot_info,
	     काष्ठा vchiq_header *header, काष्ठा vchiq_service *service)
अणु
	पूर्णांक release_count;

	mutex_lock(&state->recycle_mutex);

	अगर (header) अणु
		पूर्णांक msgid = header->msgid;

		अगर (((msgid & VCHIQ_MSGID_CLAIMED) == 0) ||
			(service && service->closing)) अणु
			mutex_unlock(&state->recycle_mutex);
			वापस;
		पूर्ण

		/* Reग_लिखो the message header to prevent a द्विगुन release */
		header->msgid = msgid & ~VCHIQ_MSGID_CLAIMED;
	पूर्ण

	release_count = slot_info->release_count;
	slot_info->release_count = ++release_count;

	अगर (release_count == slot_info->use_count) अणु
		पूर्णांक slot_queue_recycle;
		/* Add to the मुक्तd queue */

		/*
		 * A पढ़ो barrier is necessary here to prevent speculative
		 * fetches of remote->slot_queue_recycle from overtaking the
		 * mutex.
		 */
		rmb();

		slot_queue_recycle = state->remote->slot_queue_recycle;
		state->remote->slot_queue[slot_queue_recycle &
			VCHIQ_SLOT_QUEUE_MASK] =
			SLOT_INDEX_FROM_INFO(state, slot_info);
		state->remote->slot_queue_recycle = slot_queue_recycle + 1;
		vchiq_log_info(vchiq_core_log_level,
			"%d: %s %d - recycle->%x", state->id, __func__,
			SLOT_INDEX_FROM_INFO(state, slot_info),
			state->remote->slot_queue_recycle);

		/*
		 * A ग_लिखो barrier is necessary, but remote_event_संकेत
		 * contains one.
		 */
		remote_event_संकेत(&state->remote->recycle);
	पूर्ण

	mutex_unlock(&state->recycle_mutex);
पूर्ण

/* Called by the slot handler - करोn't hold the bulk mutex */
अटल क्रमागत vchiq_status
notअगरy_bulks(काष्ठा vchiq_service *service, काष्ठा vchiq_bulk_queue *queue,
	     पूर्णांक retry_poll)
अणु
	क्रमागत vchiq_status status = VCHIQ_SUCCESS;

	vchiq_log_trace(vchiq_core_log_level,
		"%d: nb:%d %cx - p=%x rn=%x r=%x",
		service->state->id, service->localport,
		(queue == &service->bulk_tx) ? 't' : 'r',
		queue->process, queue->remote_notअगरy, queue->हटाओ);

	queue->remote_notअगरy = queue->process;

	अगर (status == VCHIQ_SUCCESS) अणु
		जबतक (queue->हटाओ != queue->remote_notअगरy) अणु
			काष्ठा vchiq_bulk *bulk =
				&queue->bulks[BULK_INDEX(queue->हटाओ)];

			/*
			 * Only generate callbacks क्रम non-dummy bulk
			 * requests, and non-terminated services
			 */
			अगर (bulk->data && service->instance) अणु
				अगर (bulk->actual != VCHIQ_BULK_ACTUAL_ABORTED) अणु
					अगर (bulk->dir == VCHIQ_BULK_TRANSMIT) अणु
						VCHIQ_SERVICE_STATS_INC(service,
							bulk_tx_count);
						VCHIQ_SERVICE_STATS_ADD(service,
							bulk_tx_bytes,
							bulk->actual);
					पूर्ण अन्यथा अणु
						VCHIQ_SERVICE_STATS_INC(service,
							bulk_rx_count);
						VCHIQ_SERVICE_STATS_ADD(service,
							bulk_rx_bytes,
							bulk->actual);
					पूर्ण
				पूर्ण अन्यथा अणु
					VCHIQ_SERVICE_STATS_INC(service,
						bulk_पातed_count);
				पूर्ण
				अगर (bulk->mode == VCHIQ_BULK_MODE_BLOCKING) अणु
					काष्ठा bulk_रुकोer *रुकोer;

					spin_lock(&bulk_रुकोer_spinlock);
					रुकोer = bulk->userdata;
					अगर (रुकोer) अणु
						रुकोer->actual = bulk->actual;
						complete(&रुकोer->event);
					पूर्ण
					spin_unlock(&bulk_रुकोer_spinlock);
				पूर्ण अन्यथा अगर (bulk->mode ==
					VCHIQ_BULK_MODE_CALLBACK) अणु
					क्रमागत vchiq_reason reason = (bulk->dir ==
						VCHIQ_BULK_TRANSMIT) ?
						((bulk->actual ==
						VCHIQ_BULK_ACTUAL_ABORTED) ?
						VCHIQ_BULK_TRANSMIT_ABORTED :
						VCHIQ_BULK_TRANSMIT_DONE) :
						((bulk->actual ==
						VCHIQ_BULK_ACTUAL_ABORTED) ?
						VCHIQ_BULK_RECEIVE_ABORTED :
						VCHIQ_BULK_RECEIVE_DONE);
					status = make_service_callback(service,
						reason,	शून्य, bulk->userdata);
					अगर (status == VCHIQ_RETRY)
						अवरोध;
				पूर्ण
			पूर्ण

			queue->हटाओ++;
			complete(&service->bulk_हटाओ_event);
		पूर्ण
		अगर (!retry_poll)
			status = VCHIQ_SUCCESS;
	पूर्ण

	अगर (status == VCHIQ_RETRY)
		request_poll(service->state, service,
			(queue == &service->bulk_tx) ?
			VCHIQ_POLL_TXNOTIFY : VCHIQ_POLL_RXNOTIFY);

	वापस status;
पूर्ण

/* Called by the slot handler thपढ़ो */
अटल व्योम
poll_services(काष्ठा vchiq_state *state)
अणु
	पूर्णांक group, i;

	क्रम (group = 0; group < BITSET_SIZE(state->unused_service); group++) अणु
		u32 flags;

		flags = atomic_xchg(&state->poll_services[group], 0);
		क्रम (i = 0; flags; i++) अणु
			अगर (flags & BIT(i)) अणु
				काष्ठा vchiq_service *service =
					find_service_by_port(state,
						(group<<5) + i);
				u32 service_flags;

				flags &= ~BIT(i);
				अगर (!service)
					जारी;
				service_flags =
					atomic_xchg(&service->poll_flags, 0);
				अगर (service_flags &
					BIT(VCHIQ_POLL_REMOVE)) अणु
					vchiq_log_info(vchiq_core_log_level,
						"%d: ps - remove %d<->%d",
						state->id, service->localport,
						service->remoteport);

					/*
					 * Make it look like a client, because
					 * it must be हटाओd and not left in
					 * the LISTENING state.
					 */
					service->खुला_fourcc =
						VCHIQ_FOURCC_INVALID;

					अगर (vchiq_बंद_service_पूर्णांकernal(
						service, 0/*!बंद_recvd*/) !=
						VCHIQ_SUCCESS)
						request_poll(state, service,
							VCHIQ_POLL_REMOVE);
				पूर्ण अन्यथा अगर (service_flags &
					BIT(VCHIQ_POLL_TERMINATE)) अणु
					vchiq_log_info(vchiq_core_log_level,
						"%d: ps - terminate %d<->%d",
						state->id, service->localport,
						service->remoteport);
					अगर (vchiq_बंद_service_पूर्णांकernal(
						service, 0/*!बंद_recvd*/) !=
						VCHIQ_SUCCESS)
						request_poll(state, service,
							VCHIQ_POLL_TERMINATE);
				पूर्ण
				अगर (service_flags & BIT(VCHIQ_POLL_TXNOTIFY))
					notअगरy_bulks(service,
						&service->bulk_tx,
						1/*retry_poll*/);
				अगर (service_flags & BIT(VCHIQ_POLL_RXNOTIFY))
					notअगरy_bulks(service,
						&service->bulk_rx,
						1/*retry_poll*/);
				unlock_service(service);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Called with the bulk_mutex held */
अटल व्योम
पात_outstanding_bulks(काष्ठा vchiq_service *service,
			काष्ठा vchiq_bulk_queue *queue)
अणु
	पूर्णांक is_tx = (queue == &service->bulk_tx);

	vchiq_log_trace(vchiq_core_log_level,
		"%d: aob:%d %cx - li=%x ri=%x p=%x",
		service->state->id, service->localport, is_tx ? 't' : 'r',
		queue->local_insert, queue->remote_insert, queue->process);

	WARN_ON(!((पूर्णांक)(queue->local_insert - queue->process) >= 0));
	WARN_ON(!((पूर्णांक)(queue->remote_insert - queue->process) >= 0));

	जबतक ((queue->process != queue->local_insert) ||
		(queue->process != queue->remote_insert)) अणु
		काष्ठा vchiq_bulk *bulk =
				&queue->bulks[BULK_INDEX(queue->process)];

		अगर (queue->process == queue->remote_insert) अणु
			/* fabricate a matching dummy bulk */
			bulk->remote_data = शून्य;
			bulk->remote_size = 0;
			queue->remote_insert++;
		पूर्ण

		अगर (queue->process != queue->local_insert) अणु
			vchiq_complete_bulk(bulk);

			vchiq_log_info(SRVTRACE_LEVEL(service),
				"%s %c%c%c%c d:%d ABORTED - tx len:%d, rx len:%d",
				is_tx ? "Send Bulk to" : "Recv Bulk from",
				VCHIQ_FOURCC_AS_4CHARS(service->base.fourcc),
				service->remoteport,
				bulk->size,
				bulk->remote_size);
		पूर्ण अन्यथा अणु
			/* fabricate a matching dummy bulk */
			bulk->data = 0;
			bulk->size = 0;
			bulk->actual = VCHIQ_BULK_ACTUAL_ABORTED;
			bulk->dir = is_tx ? VCHIQ_BULK_TRANSMIT :
				VCHIQ_BULK_RECEIVE;
			queue->local_insert++;
		पूर्ण

		queue->process++;
	पूर्ण
पूर्ण

अटल पूर्णांक
parse_खोलो(काष्ठा vchiq_state *state, काष्ठा vchiq_header *header)
अणु
	काष्ठा vchiq_service *service = शून्य;
	पूर्णांक msgid, size;
	अचिन्हित पूर्णांक localport, remoteport;

	msgid = header->msgid;
	size = header->size;
	localport = VCHIQ_MSG_DSTPORT(msgid);
	remoteport = VCHIQ_MSG_SRCPORT(msgid);
	अगर (size >= माप(काष्ठा vchiq_खोलो_payload)) अणु
		स्थिर काष्ठा vchiq_खोलो_payload *payload =
			(काष्ठा vchiq_खोलो_payload *)header->data;
		अचिन्हित पूर्णांक fourcc;

		fourcc = payload->fourcc;
		vchiq_log_info(vchiq_core_log_level,
			"%d: prs OPEN@%pK (%d->'%c%c%c%c')",
			state->id, header, localport,
			VCHIQ_FOURCC_AS_4CHARS(fourcc));

		service = get_listening_service(state, fourcc);

		अगर (service) अणु
			/* A matching service exists */
			लघु version = payload->version;
			लघु version_min = payload->version_min;

			अगर ((service->version < version_min) ||
				(version < service->version_min)) अणु
				/* Version mismatch */
				vchiq_loud_error_header();
				vchiq_loud_error("%d: service %d (%c%c%c%c) "
					"version mismatch - local (%d, min %d)"
					" vs. remote (%d, min %d)",
					state->id, service->localport,
					VCHIQ_FOURCC_AS_4CHARS(fourcc),
					service->version, service->version_min,
					version, version_min);
				vchiq_loud_error_footer();
				unlock_service(service);
				service = शून्य;
				जाओ fail_खोलो;
			पूर्ण
			service->peer_version = version;

			अगर (service->srvstate == VCHIQ_SRVSTATE_LISTENING) अणु
				काष्ठा vchiq_खोलोack_payload ack_payload = अणु
					service->version
				पूर्ण;

				अगर (state->version_common <
				    VCHIQ_VERSION_SYNCHRONOUS_MODE)
					service->sync = 0;

				/* Acknowledge the OPEN */
				अगर (service->sync) अणु
					अगर (queue_message_sync(
						state,
						शून्य,
						VCHIQ_MAKE_MSG(
							VCHIQ_MSG_OPENACK,
							service->localport,
							remoteport),
						स_नकल_copy_callback,
						&ack_payload,
						माप(ack_payload),
						0) == VCHIQ_RETRY)
						जाओ bail_not_पढ़ोy;
				पूर्ण अन्यथा अणु
					अगर (queue_message(state,
							शून्य,
							VCHIQ_MAKE_MSG(
							VCHIQ_MSG_OPENACK,
							service->localport,
							remoteport),
						स_नकल_copy_callback,
						&ack_payload,
						माप(ack_payload),
						0) == VCHIQ_RETRY)
						जाओ bail_not_पढ़ोy;
				पूर्ण

				/* The service is now खोलो */
				vchiq_set_service_state(service,
					service->sync ? VCHIQ_SRVSTATE_OPENSYNC
					: VCHIQ_SRVSTATE_OPEN);
			पूर्ण

			/* Success - the message has been dealt with */
			unlock_service(service);
			वापस 1;
		पूर्ण
	पूर्ण

fail_खोलो:
	/* No available service, or an invalid request - send a CLOSE */
	अगर (queue_message(state, शून्य,
		VCHIQ_MAKE_MSG(VCHIQ_MSG_CLOSE, 0, VCHIQ_MSG_SRCPORT(msgid)),
		शून्य, शून्य, 0, 0) == VCHIQ_RETRY)
		जाओ bail_not_पढ़ोy;

	वापस 1;

bail_not_पढ़ोy:
	अगर (service)
		unlock_service(service);

	वापस 0;
पूर्ण

/* Called by the slot handler thपढ़ो */
अटल व्योम
parse_rx_slots(काष्ठा vchiq_state *state)
अणु
	काष्ठा vchiq_shared_state *remote = state->remote;
	काष्ठा vchiq_service *service = शून्य;
	पूर्णांक tx_pos;

	DEBUG_INITIALISE(state->local)

	tx_pos = remote->tx_pos;

	जबतक (state->rx_pos != tx_pos) अणु
		काष्ठा vchiq_header *header;
		पूर्णांक msgid, size;
		पूर्णांक type;
		अचिन्हित पूर्णांक localport, remoteport;

		DEBUG_TRACE(PARSE_LINE);
		अगर (!state->rx_data) अणु
			पूर्णांक rx_index;

			WARN_ON(!((state->rx_pos & VCHIQ_SLOT_MASK) == 0));
			rx_index = remote->slot_queue[
				SLOT_QUEUE_INDEX_FROM_POS_MASKED(state->rx_pos)];
			state->rx_data = (अक्षर *)SLOT_DATA_FROM_INDEX(state,
				rx_index);
			state->rx_info = SLOT_INFO_FROM_INDEX(state, rx_index);

			/*
			 * Initialise use_count to one, and increment
			 * release_count at the end of the slot to aव्योम
			 * releasing the slot prematurely.
			 */
			state->rx_info->use_count = 1;
			state->rx_info->release_count = 0;
		पूर्ण

		header = (काष्ठा vchiq_header *)(state->rx_data +
			(state->rx_pos & VCHIQ_SLOT_MASK));
		DEBUG_VALUE(PARSE_HEADER, (पूर्णांक)(दीर्घ)header);
		msgid = header->msgid;
		DEBUG_VALUE(PARSE_MSGID, msgid);
		size = header->size;
		type = VCHIQ_MSG_TYPE(msgid);
		localport = VCHIQ_MSG_DSTPORT(msgid);
		remoteport = VCHIQ_MSG_SRCPORT(msgid);

		अगर (type != VCHIQ_MSG_DATA)
			VCHIQ_STATS_INC(state, ctrl_rx_count);

		चयन (type) अणु
		हाल VCHIQ_MSG_OPENACK:
		हाल VCHIQ_MSG_CLOSE:
		हाल VCHIQ_MSG_DATA:
		हाल VCHIQ_MSG_BULK_RX:
		हाल VCHIQ_MSG_BULK_TX:
		हाल VCHIQ_MSG_BULK_RX_DONE:
		हाल VCHIQ_MSG_BULK_TX_DONE:
			service = find_service_by_port(state, localport);
			अगर ((!service ||
			     ((service->remoteport != remoteport) &&
			      (service->remoteport != VCHIQ_PORT_FREE))) &&
			    (localport == 0) &&
			    (type == VCHIQ_MSG_CLOSE)) अणु
				/*
				 * This could be a CLOSE from a client which
				 * hadn't yet received the OPENACK - look क्रम
				 * the connected service
				 */
				अगर (service)
					unlock_service(service);
				service = get_connected_service(state,
					remoteport);
				अगर (service)
					vchiq_log_warning(vchiq_core_log_level,
						"%d: prs %s@%pK (%d->%d) - found connected service %d",
						state->id, msg_type_str(type),
						header, remoteport, localport,
						service->localport);
			पूर्ण

			अगर (!service) अणु
				vchiq_log_error(vchiq_core_log_level,
					"%d: prs %s@%pK (%d->%d) - invalid/closed service %d",
					state->id, msg_type_str(type),
					header, remoteport, localport,
					localport);
				जाओ skip_message;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (SRVTRACE_ENABLED(service, VCHIQ_LOG_INFO)) अणु
			पूर्णांक svc_fourcc;

			svc_fourcc = service
				? service->base.fourcc
				: VCHIQ_MAKE_FOURCC('?', '?', '?', '?');
			vchiq_log_info(SRVTRACE_LEVEL(service),
				"Rcvd Msg %s(%u) from %c%c%c%c s:%d d:%d len:%d",
				msg_type_str(type), type,
				VCHIQ_FOURCC_AS_4CHARS(svc_fourcc),
				remoteport, localport, size);
			अगर (size > 0)
				vchiq_log_dump_mem("Rcvd", 0, header->data,
					min(16, size));
		पूर्ण

		अगर (((अचिन्हित दीर्घ)header & VCHIQ_SLOT_MASK) +
		    calc_stride(size) > VCHIQ_SLOT_SIZE) अणु
			vchiq_log_error(vchiq_core_log_level,
				"header %pK (msgid %x) - size %x too big for slot",
				header, (अचिन्हित पूर्णांक)msgid,
				(अचिन्हित पूर्णांक)size);
			WARN(1, "oversized for slot\n");
		पूर्ण

		चयन (type) अणु
		हाल VCHIQ_MSG_OPEN:
			WARN_ON(!(VCHIQ_MSG_DSTPORT(msgid) == 0));
			अगर (!parse_खोलो(state, header))
				जाओ bail_not_पढ़ोy;
			अवरोध;
		हाल VCHIQ_MSG_OPENACK:
			अगर (size >= माप(काष्ठा vchiq_खोलोack_payload)) अणु
				स्थिर काष्ठा vchiq_खोलोack_payload *payload =
					(काष्ठा vchiq_खोलोack_payload *)
					header->data;
				service->peer_version = payload->version;
			पूर्ण
			vchiq_log_info(vchiq_core_log_level,
				"%d: prs OPENACK@%pK,%x (%d->%d) v:%d",
				state->id, header, size, remoteport, localport,
				service->peer_version);
			अगर (service->srvstate == VCHIQ_SRVSTATE_OPENING) अणु
				service->remoteport = remoteport;
				vchiq_set_service_state(service,
					VCHIQ_SRVSTATE_OPEN);
				complete(&service->हटाओ_event);
			पूर्ण अन्यथा
				vchiq_log_error(vchiq_core_log_level,
					"OPENACK received in state %s",
					srvstate_names[service->srvstate]);
			अवरोध;
		हाल VCHIQ_MSG_CLOSE:
			WARN_ON(size != 0); /* There should be no data */

			vchiq_log_info(vchiq_core_log_level,
				"%d: prs CLOSE@%pK (%d->%d)",
				state->id, header, remoteport, localport);

			mark_service_closing_पूर्णांकernal(service, 1);

			अगर (vchiq_बंद_service_पूर्णांकernal(service,
				1/*बंद_recvd*/) == VCHIQ_RETRY)
				जाओ bail_not_पढ़ोy;

			vchiq_log_info(vchiq_core_log_level,
				"Close Service %c%c%c%c s:%u d:%d",
				VCHIQ_FOURCC_AS_4CHARS(service->base.fourcc),
				service->localport,
				service->remoteport);
			अवरोध;
		हाल VCHIQ_MSG_DATA:
			vchiq_log_info(vchiq_core_log_level,
				"%d: prs DATA@%pK,%x (%d->%d)",
				state->id, header, size, remoteport, localport);

			अगर ((service->remoteport == remoteport) &&
			    (service->srvstate == VCHIQ_SRVSTATE_OPEN)) अणु
				header->msgid = msgid | VCHIQ_MSGID_CLAIMED;
				claim_slot(state->rx_info);
				DEBUG_TRACE(PARSE_LINE);
				अगर (make_service_callback(service,
					VCHIQ_MESSAGE_AVAILABLE, header,
					शून्य) == VCHIQ_RETRY) अणु
					DEBUG_TRACE(PARSE_LINE);
					जाओ bail_not_पढ़ोy;
				पूर्ण
				VCHIQ_SERVICE_STATS_INC(service, ctrl_rx_count);
				VCHIQ_SERVICE_STATS_ADD(service, ctrl_rx_bytes,
					size);
			पूर्ण अन्यथा अणु
				VCHIQ_STATS_INC(state, error_count);
			पूर्ण
			अवरोध;
		हाल VCHIQ_MSG_CONNECT:
			vchiq_log_info(vchiq_core_log_level,
				"%d: prs CONNECT@%pK", state->id, header);
			state->version_common =	((काष्ठा vchiq_slot_zero *)
						 state->slot_data)->version;
			complete(&state->connect);
			अवरोध;
		हाल VCHIQ_MSG_BULK_RX:
		हाल VCHIQ_MSG_BULK_TX:
			/*
			 * We should never receive a bulk request from the
			 * other side since we're not setup to perक्रमm as the
			 * master.
			 */
			WARN_ON(1);
			अवरोध;
		हाल VCHIQ_MSG_BULK_RX_DONE:
		हाल VCHIQ_MSG_BULK_TX_DONE:
			अगर ((service->remoteport == remoteport) &&
			    (service->srvstate != VCHIQ_SRVSTATE_FREE)) अणु
				काष्ठा vchiq_bulk_queue *queue;
				काष्ठा vchiq_bulk *bulk;

				queue = (type == VCHIQ_MSG_BULK_RX_DONE) ?
					&service->bulk_rx : &service->bulk_tx;

				DEBUG_TRACE(PARSE_LINE);
				अगर (mutex_lock_समाप्तable(&service->bulk_mutex)) अणु
					DEBUG_TRACE(PARSE_LINE);
					जाओ bail_not_पढ़ोy;
				पूर्ण
				अगर ((पूर्णांक)(queue->remote_insert -
					queue->local_insert) >= 0) अणु
					vchiq_log_error(vchiq_core_log_level,
						"%d: prs %s@%pK (%d->%d) unexpected (ri=%d,li=%d)",
						state->id, msg_type_str(type),
						header, remoteport, localport,
						queue->remote_insert,
						queue->local_insert);
					mutex_unlock(&service->bulk_mutex);
					अवरोध;
				पूर्ण
				अगर (queue->process != queue->remote_insert) अणु
					pr_err("%s: p %x != ri %x\n",
					       __func__,
					       queue->process,
					       queue->remote_insert);
					mutex_unlock(&service->bulk_mutex);
					जाओ bail_not_पढ़ोy;
				पूर्ण

				bulk = &queue->bulks[
					BULK_INDEX(queue->remote_insert)];
				bulk->actual = *(पूर्णांक *)header->data;
				queue->remote_insert++;

				vchiq_log_info(vchiq_core_log_level,
					"%d: prs %s@%pK (%d->%d) %x@%pad",
					state->id, msg_type_str(type),
					header, remoteport, localport,
					bulk->actual, &bulk->data);

				vchiq_log_trace(vchiq_core_log_level,
					"%d: prs:%d %cx li=%x ri=%x p=%x",
					state->id, localport,
					(type == VCHIQ_MSG_BULK_RX_DONE) ?
						'r' : 't',
					queue->local_insert,
					queue->remote_insert, queue->process);

				DEBUG_TRACE(PARSE_LINE);
				WARN_ON(queue->process == queue->local_insert);
				vchiq_complete_bulk(bulk);
				queue->process++;
				mutex_unlock(&service->bulk_mutex);
				DEBUG_TRACE(PARSE_LINE);
				notअगरy_bulks(service, queue, 1/*retry_poll*/);
				DEBUG_TRACE(PARSE_LINE);
			पूर्ण
			अवरोध;
		हाल VCHIQ_MSG_PADDING:
			vchiq_log_trace(vchiq_core_log_level,
				"%d: prs PADDING@%pK,%x",
				state->id, header, size);
			अवरोध;
		हाल VCHIQ_MSG_PAUSE:
			/* If initiated, संकेत the application thपढ़ो */
			vchiq_log_trace(vchiq_core_log_level,
				"%d: prs PAUSE@%pK,%x",
				state->id, header, size);
			अगर (state->conn_state == VCHIQ_CONNSTATE_PAUSED) अणु
				vchiq_log_error(vchiq_core_log_level,
					"%d: PAUSE received in state PAUSED",
					state->id);
				अवरोध;
			पूर्ण
			अगर (state->conn_state != VCHIQ_CONNSTATE_PAUSE_SENT) अणु
				/* Send a PAUSE in response */
				अगर (queue_message(state, शून्य,
					VCHIQ_MAKE_MSG(VCHIQ_MSG_PAUSE, 0, 0),
					शून्य, शून्य, 0, QMFLAGS_NO_MUTEX_UNLOCK)
				    == VCHIQ_RETRY)
					जाओ bail_not_पढ़ोy;
			पूर्ण
			/* At this poपूर्णांक slot_mutex is held */
			vchiq_set_conn_state(state, VCHIQ_CONNSTATE_PAUSED);
			अवरोध;
		हाल VCHIQ_MSG_RESUME:
			vchiq_log_trace(vchiq_core_log_level,
				"%d: prs RESUME@%pK,%x",
				state->id, header, size);
			/* Release the slot mutex */
			mutex_unlock(&state->slot_mutex);
			vchiq_set_conn_state(state, VCHIQ_CONNSTATE_CONNECTED);
			अवरोध;

		हाल VCHIQ_MSG_REMOTE_USE:
			vchiq_on_remote_use(state);
			अवरोध;
		हाल VCHIQ_MSG_REMOTE_RELEASE:
			vchiq_on_remote_release(state);
			अवरोध;
		हाल VCHIQ_MSG_REMOTE_USE_ACTIVE:
			अवरोध;

		शेष:
			vchiq_log_error(vchiq_core_log_level,
				"%d: prs invalid msgid %x@%pK,%x",
				state->id, msgid, header, size);
			WARN(1, "invalid message\n");
			अवरोध;
		पूर्ण

skip_message:
		अगर (service) अणु
			unlock_service(service);
			service = शून्य;
		पूर्ण

		state->rx_pos += calc_stride(size);

		DEBUG_TRACE(PARSE_LINE);
		/*
		 * Perक्रमm some housekeeping when the end of the slot is
		 * reached.
		 */
		अगर ((state->rx_pos & VCHIQ_SLOT_MASK) == 0) अणु
			/* Remove the extra reference count. */
			release_slot(state, state->rx_info, शून्य, शून्य);
			state->rx_data = शून्य;
		पूर्ण
	पूर्ण

bail_not_पढ़ोy:
	अगर (service)
		unlock_service(service);
पूर्ण

/* Called by the slot handler thपढ़ो */
अटल पूर्णांक
slot_handler_func(व्योम *v)
अणु
	काष्ठा vchiq_state *state = v;
	काष्ठा vchiq_shared_state *local = state->local;

	DEBUG_INITIALISE(local)

	जबतक (1) अणु
		DEBUG_COUNT(SLOT_HANDLER_COUNT);
		DEBUG_TRACE(SLOT_HANDLER_LINE);
		remote_event_रुको(&state->trigger_event, &local->trigger);

		rmb();

		DEBUG_TRACE(SLOT_HANDLER_LINE);
		अगर (state->poll_needed) अणु

			state->poll_needed = 0;

			/*
			 * Handle service polling and other rare conditions here
			 * out of the मुख्यline code
			 */
			चयन (state->conn_state) अणु
			हाल VCHIQ_CONNSTATE_CONNECTED:
				/* Poll the services as requested */
				poll_services(state);
				अवरोध;

			हाल VCHIQ_CONNSTATE_PAUSING:
				अगर (queue_message(state, शून्य,
					VCHIQ_MAKE_MSG(VCHIQ_MSG_PAUSE, 0, 0),
					शून्य, शून्य, 0,
					QMFLAGS_NO_MUTEX_UNLOCK)
				    != VCHIQ_RETRY) अणु
					vchiq_set_conn_state(state,
						VCHIQ_CONNSTATE_PAUSE_SENT);
				पूर्ण अन्यथा अणु
					/* Retry later */
					state->poll_needed = 1;
				पूर्ण
				अवरोध;

			हाल VCHIQ_CONNSTATE_RESUMING:
				अगर (queue_message(state, शून्य,
					VCHIQ_MAKE_MSG(VCHIQ_MSG_RESUME, 0, 0),
					शून्य, शून्य, 0, QMFLAGS_NO_MUTEX_LOCK)
					!= VCHIQ_RETRY) अणु
					vchiq_set_conn_state(state,
						VCHIQ_CONNSTATE_CONNECTED);
				पूर्ण अन्यथा अणु
					/*
					 * This should really be impossible,
					 * since the PAUSE should have flushed
					 * through outstanding messages.
					 */
					vchiq_log_error(vchiq_core_log_level,
						"Failed to send RESUME message");
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

		पूर्ण

		DEBUG_TRACE(SLOT_HANDLER_LINE);
		parse_rx_slots(state);
	पूर्ण
	वापस 0;
पूर्ण

/* Called by the recycle thपढ़ो */
अटल पूर्णांक
recycle_func(व्योम *v)
अणु
	काष्ठा vchiq_state *state = v;
	काष्ठा vchiq_shared_state *local = state->local;
	BITSET_T *found;
	माप_प्रकार length;

	length = माप(*found) * BITSET_SIZE(VCHIQ_MAX_SERVICES);

	found = kदो_स्मृति_array(BITSET_SIZE(VCHIQ_MAX_SERVICES), माप(*found),
			      GFP_KERNEL);
	अगर (!found)
		वापस -ENOMEM;

	जबतक (1) अणु
		remote_event_रुको(&state->recycle_event, &local->recycle);

		process_मुक्त_queue(state, found, length);
	पूर्ण
	वापस 0;
पूर्ण

/* Called by the sync thपढ़ो */
अटल पूर्णांक
sync_func(व्योम *v)
अणु
	काष्ठा vchiq_state *state = v;
	काष्ठा vchiq_shared_state *local = state->local;
	काष्ठा vchiq_header *header =
		(काष्ठा vchiq_header *)SLOT_DATA_FROM_INDEX(state,
			state->remote->slot_sync);

	जबतक (1) अणु
		काष्ठा vchiq_service *service;
		पूर्णांक msgid, size;
		पूर्णांक type;
		अचिन्हित पूर्णांक localport, remoteport;

		remote_event_रुको(&state->sync_trigger_event, &local->sync_trigger);

		rmb();

		msgid = header->msgid;
		size = header->size;
		type = VCHIQ_MSG_TYPE(msgid);
		localport = VCHIQ_MSG_DSTPORT(msgid);
		remoteport = VCHIQ_MSG_SRCPORT(msgid);

		service = find_service_by_port(state, localport);

		अगर (!service) अणु
			vchiq_log_error(vchiq_sync_log_level,
				"%d: sf %s@%pK (%d->%d) - invalid/closed service %d",
				state->id, msg_type_str(type),
				header, remoteport, localport, localport);
			release_message_sync(state, header);
			जारी;
		पूर्ण

		अगर (vchiq_sync_log_level >= VCHIQ_LOG_TRACE) अणु
			पूर्णांक svc_fourcc;

			svc_fourcc = service
				? service->base.fourcc
				: VCHIQ_MAKE_FOURCC('?', '?', '?', '?');
			vchiq_log_trace(vchiq_sync_log_level,
				"Rcvd Msg %s from %c%c%c%c s:%d d:%d len:%d",
				msg_type_str(type),
				VCHIQ_FOURCC_AS_4CHARS(svc_fourcc),
				remoteport, localport, size);
			अगर (size > 0)
				vchiq_log_dump_mem("Rcvd", 0, header->data,
					min(16, size));
		पूर्ण

		चयन (type) अणु
		हाल VCHIQ_MSG_OPENACK:
			अगर (size >= माप(काष्ठा vchiq_खोलोack_payload)) अणु
				स्थिर काष्ठा vchiq_खोलोack_payload *payload =
					(काष्ठा vchiq_खोलोack_payload *)
					header->data;
				service->peer_version = payload->version;
			पूर्ण
			vchiq_log_info(vchiq_sync_log_level,
				"%d: sf OPENACK@%pK,%x (%d->%d) v:%d",
				state->id, header, size, remoteport, localport,
				service->peer_version);
			अगर (service->srvstate == VCHIQ_SRVSTATE_OPENING) अणु
				service->remoteport = remoteport;
				vchiq_set_service_state(service,
					VCHIQ_SRVSTATE_OPENSYNC);
				service->sync = 1;
				complete(&service->हटाओ_event);
			पूर्ण
			release_message_sync(state, header);
			अवरोध;

		हाल VCHIQ_MSG_DATA:
			vchiq_log_trace(vchiq_sync_log_level,
				"%d: sf DATA@%pK,%x (%d->%d)",
				state->id, header, size, remoteport, localport);

			अगर ((service->remoteport == remoteport) &&
				(service->srvstate ==
				VCHIQ_SRVSTATE_OPENSYNC)) अणु
				अगर (make_service_callback(service,
					VCHIQ_MESSAGE_AVAILABLE, header,
					शून्य) == VCHIQ_RETRY)
					vchiq_log_error(vchiq_sync_log_level,
						"synchronous callback to service %d returns VCHIQ_RETRY",
						localport);
			पूर्ण
			अवरोध;

		शेष:
			vchiq_log_error(vchiq_sync_log_level,
				"%d: sf unexpected msgid %x@%pK,%x",
				state->id, msgid, header, size);
			release_message_sync(state, header);
			अवरोध;
		पूर्ण

		unlock_service(service);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
init_bulk_queue(काष्ठा vchiq_bulk_queue *queue)
अणु
	queue->local_insert = 0;
	queue->remote_insert = 0;
	queue->process = 0;
	queue->remote_notअगरy = 0;
	queue->हटाओ = 0;
पूर्ण

अंतरभूत स्थिर अक्षर *
get_conn_state_name(क्रमागत vchiq_connstate conn_state)
अणु
	वापस conn_state_names[conn_state];
पूर्ण

काष्ठा vchiq_slot_zero *
vchiq_init_slots(व्योम *mem_base, पूर्णांक mem_size)
अणु
	पूर्णांक mem_align =
		(पूर्णांक)((VCHIQ_SLOT_SIZE - (दीर्घ)mem_base) & VCHIQ_SLOT_MASK);
	काष्ठा vchiq_slot_zero *slot_zero =
		(काष्ठा vchiq_slot_zero *)(mem_base + mem_align);
	पूर्णांक num_slots = (mem_size - mem_align)/VCHIQ_SLOT_SIZE;
	पूर्णांक first_data_slot = VCHIQ_SLOT_ZERO_SLOTS;

	/* Ensure there is enough memory to run an असलolutely minimum प्रणाली */
	num_slots -= first_data_slot;

	अगर (num_slots < 4) अणु
		vchiq_log_error(vchiq_core_log_level,
			"%s - insufficient memory %x bytes",
			__func__, mem_size);
		वापस शून्य;
	पूर्ण

	स_रखो(slot_zero, 0, माप(काष्ठा vchiq_slot_zero));

	slot_zero->magic = VCHIQ_MAGIC;
	slot_zero->version = VCHIQ_VERSION;
	slot_zero->version_min = VCHIQ_VERSION_MIN;
	slot_zero->slot_zero_size = माप(काष्ठा vchiq_slot_zero);
	slot_zero->slot_size = VCHIQ_SLOT_SIZE;
	slot_zero->max_slots = VCHIQ_MAX_SLOTS;
	slot_zero->max_slots_per_side = VCHIQ_MAX_SLOTS_PER_SIDE;

	slot_zero->master.slot_sync = first_data_slot;
	slot_zero->master.slot_first = first_data_slot + 1;
	slot_zero->master.slot_last = first_data_slot + (num_slots/2) - 1;
	slot_zero->slave.slot_sync = first_data_slot + (num_slots/2);
	slot_zero->slave.slot_first = first_data_slot + (num_slots/2) + 1;
	slot_zero->slave.slot_last = first_data_slot + num_slots - 1;

	वापस slot_zero;
पूर्ण

क्रमागत vchiq_status
vchiq_init_state(काष्ठा vchiq_state *state, काष्ठा vchiq_slot_zero *slot_zero)
अणु
	काष्ठा vchiq_shared_state *local;
	काष्ठा vchiq_shared_state *remote;
	क्रमागत vchiq_status status;
	अक्षर thपढ़ोname[16];
	पूर्णांक i;

	अगर (vchiq_states[0]) अणु
		pr_err("%s: VCHIQ state already initialized\n", __func__);
		वापस VCHIQ_ERROR;
	पूर्ण

	local = &slot_zero->slave;
	remote = &slot_zero->master;

	अगर (local->initialised) अणु
		vchiq_loud_error_header();
		अगर (remote->initialised)
			vchiq_loud_error("local state has already been initialised");
		अन्यथा
			vchiq_loud_error("master/slave mismatch two slaves");
		vchiq_loud_error_footer();
		वापस VCHIQ_ERROR;
	पूर्ण

	स_रखो(state, 0, माप(काष्ठा vchiq_state));

	/*
	 * initialize shared state poपूर्णांकers
	 */

	state->local = local;
	state->remote = remote;
	state->slot_data = (काष्ठा vchiq_slot *)slot_zero;

	/*
	 * initialize events and mutexes
	 */

	init_completion(&state->connect);
	mutex_init(&state->mutex);
	mutex_init(&state->slot_mutex);
	mutex_init(&state->recycle_mutex);
	mutex_init(&state->sync_mutex);
	mutex_init(&state->bulk_transfer_mutex);

	init_completion(&state->slot_available_event);
	init_completion(&state->slot_हटाओ_event);
	init_completion(&state->data_quota_event);

	state->slot_queue_available = 0;

	क्रम (i = 0; i < VCHIQ_MAX_SERVICES; i++) अणु
		काष्ठा vchiq_service_quota *quota =
			&state->service_quotas[i];
		init_completion(&quota->quota_event);
	पूर्ण

	क्रम (i = local->slot_first; i <= local->slot_last; i++) अणु
		local->slot_queue[state->slot_queue_available++] = i;
		complete(&state->slot_available_event);
	पूर्ण

	state->शेष_slot_quota = state->slot_queue_available/2;
	state->शेष_message_quota =
		min((अचिन्हित लघु)(state->शेष_slot_quota * 256),
		(अचिन्हित लघु)~0);

	state->previous_data_index = -1;
	state->data_use_count = 0;
	state->data_quota = state->slot_queue_available - 1;

	remote_event_create(&state->trigger_event, &local->trigger);
	local->tx_pos = 0;
	remote_event_create(&state->recycle_event, &local->recycle);
	local->slot_queue_recycle = state->slot_queue_available;
	remote_event_create(&state->sync_trigger_event, &local->sync_trigger);
	remote_event_create(&state->sync_release_event, &local->sync_release);

	/* At start-of-day, the slot is empty and available */
	((काष्ठा vchiq_header *)
		SLOT_DATA_FROM_INDEX(state, local->slot_sync))->msgid =
							VCHIQ_MSGID_PADDING;
	remote_event_संकेत_local(&state->sync_release_event, &local->sync_release);

	local->debug[DEBUG_ENTRIES] = DEBUG_MAX;

	status = vchiq_platक्रमm_init_state(state);
	अगर (status != VCHIQ_SUCCESS)
		वापस VCHIQ_ERROR;

	/*
	 * bring up slot handler thपढ़ो
	 */
	snम_लिखो(thपढ़ोname, माप(thपढ़ोname), "vchiq-slot/%d", state->id);
	state->slot_handler_thपढ़ो = kthपढ़ो_create(&slot_handler_func,
		(व्योम *)state,
		thपढ़ोname);

	अगर (IS_ERR(state->slot_handler_thपढ़ो)) अणु
		vchiq_loud_error_header();
		vchiq_loud_error("couldn't create thread %s", thपढ़ोname);
		vchiq_loud_error_footer();
		वापस VCHIQ_ERROR;
	पूर्ण
	set_user_nice(state->slot_handler_thपढ़ो, -19);

	snम_लिखो(thपढ़ोname, माप(thपढ़ोname), "vchiq-recy/%d", state->id);
	state->recycle_thपढ़ो = kthपढ़ो_create(&recycle_func,
		(व्योम *)state,
		thपढ़ोname);
	अगर (IS_ERR(state->recycle_thपढ़ो)) अणु
		vchiq_loud_error_header();
		vchiq_loud_error("couldn't create thread %s", thपढ़ोname);
		vchiq_loud_error_footer();
		जाओ fail_मुक्त_handler_thपढ़ो;
	पूर्ण
	set_user_nice(state->recycle_thपढ़ो, -19);

	snम_लिखो(thपढ़ोname, माप(thपढ़ोname), "vchiq-sync/%d", state->id);
	state->sync_thपढ़ो = kthपढ़ो_create(&sync_func,
		(व्योम *)state,
		thपढ़ोname);
	अगर (IS_ERR(state->sync_thपढ़ो)) अणु
		vchiq_loud_error_header();
		vchiq_loud_error("couldn't create thread %s", thपढ़ोname);
		vchiq_loud_error_footer();
		जाओ fail_मुक्त_recycle_thपढ़ो;
	पूर्ण
	set_user_nice(state->sync_thपढ़ो, -20);

	wake_up_process(state->slot_handler_thपढ़ो);
	wake_up_process(state->recycle_thपढ़ो);
	wake_up_process(state->sync_thपढ़ो);

	vchiq_states[0] = state;

	/* Indicate पढ़ोiness to the other side */
	local->initialised = 1;

	वापस status;

fail_मुक्त_recycle_thपढ़ो:
	kthपढ़ो_stop(state->recycle_thपढ़ो);
fail_मुक्त_handler_thपढ़ो:
	kthपढ़ो_stop(state->slot_handler_thपढ़ो);

	वापस VCHIQ_ERROR;
पूर्ण

व्योम vchiq_msg_queue_push(अचिन्हित पूर्णांक handle, काष्ठा vchiq_header *header)
अणु
	काष्ठा vchiq_service *service = find_service_by_handle(handle);
	पूर्णांक pos;

	जबतक (service->msg_queue_ग_लिखो == service->msg_queue_पढ़ो +
		VCHIQ_MAX_SLOTS) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&service->msg_queue_pop))
			flush_संकेतs(current);
	पूर्ण

	pos = service->msg_queue_ग_लिखो++ & (VCHIQ_MAX_SLOTS - 1);
	service->msg_queue[pos] = header;

	complete(&service->msg_queue_push);
पूर्ण
EXPORT_SYMBOL(vchiq_msg_queue_push);

काष्ठा vchiq_header *vchiq_msg_hold(अचिन्हित पूर्णांक handle)
अणु
	काष्ठा vchiq_service *service = find_service_by_handle(handle);
	काष्ठा vchiq_header *header;
	पूर्णांक pos;

	अगर (service->msg_queue_ग_लिखो == service->msg_queue_पढ़ो)
		वापस शून्य;

	जबतक (service->msg_queue_ग_लिखो == service->msg_queue_पढ़ो) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&service->msg_queue_push))
			flush_संकेतs(current);
	पूर्ण

	pos = service->msg_queue_पढ़ो++ & (VCHIQ_MAX_SLOTS - 1);
	header = service->msg_queue[pos];

	complete(&service->msg_queue_pop);

	वापस header;
पूर्ण
EXPORT_SYMBOL(vchiq_msg_hold);

अटल पूर्णांक vchiq_validate_params(स्थिर काष्ठा vchiq_service_params_kernel *params)
अणु
	अगर (!params->callback || !params->fourcc) अणु
		vchiq_loud_error("Can't add service, invalid params\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Called from application thपढ़ो when a client or server service is created. */
काष्ठा vchiq_service *
vchiq_add_service_पूर्णांकernal(काष्ठा vchiq_state *state,
			   स्थिर काष्ठा vchiq_service_params_kernel *params,
			   पूर्णांक srvstate, काष्ठा vchiq_instance *instance,
			   vchiq_userdata_term userdata_term)
अणु
	काष्ठा vchiq_service *service;
	काष्ठा vchiq_service __rcu **pservice = शून्य;
	काष्ठा vchiq_service_quota *quota;
	पूर्णांक ret;
	पूर्णांक i;

	ret = vchiq_validate_params(params);
	अगर (ret)
		वापस शून्य;

	service = kदो_स्मृति(माप(*service), GFP_KERNEL);
	अगर (!service)
		वापस service;

	service->base.fourcc   = params->fourcc;
	service->base.callback = params->callback;
	service->base.userdata = params->userdata;
	service->handle        = VCHIQ_SERVICE_HANDLE_INVALID;
	kref_init(&service->ref_count);
	service->srvstate      = VCHIQ_SRVSTATE_FREE;
	service->userdata_term = userdata_term;
	service->localport     = VCHIQ_PORT_FREE;
	service->remoteport    = VCHIQ_PORT_FREE;

	service->खुला_fourcc = (srvstate == VCHIQ_SRVSTATE_OPENING) ?
		VCHIQ_FOURCC_INVALID : params->fourcc;
	service->client_id     = 0;
	service->स्वतः_बंद    = 1;
	service->sync          = 0;
	service->closing       = 0;
	service->trace         = 0;
	atomic_set(&service->poll_flags, 0);
	service->version       = params->version;
	service->version_min   = params->version_min;
	service->state         = state;
	service->instance      = instance;
	service->service_use_count = 0;
	service->msg_queue_पढ़ो = 0;
	service->msg_queue_ग_लिखो = 0;
	init_bulk_queue(&service->bulk_tx);
	init_bulk_queue(&service->bulk_rx);
	init_completion(&service->हटाओ_event);
	init_completion(&service->bulk_हटाओ_event);
	init_completion(&service->msg_queue_pop);
	init_completion(&service->msg_queue_push);
	mutex_init(&service->bulk_mutex);
	स_रखो(&service->stats, 0, माप(service->stats));
	स_रखो(&service->msg_queue, 0, माप(service->msg_queue));

	/*
	 * Although it is perfectly possible to use a spinlock
	 * to protect the creation of services, it is overसमाप्त as it
	 * disables पूर्णांकerrupts जबतक the array is searched.
	 * The only danger is of another thपढ़ो trying to create a
	 * service - service deletion is safe.
	 * Thereक्रमe it is preferable to use state->mutex which,
	 * although slower to claim, करोesn't block पूर्णांकerrupts जबतक
	 * it is held.
	 */

	mutex_lock(&state->mutex);

	/* Prepare to use a previously unused service */
	अगर (state->unused_service < VCHIQ_MAX_SERVICES)
		pservice = &state->services[state->unused_service];

	अगर (srvstate == VCHIQ_SRVSTATE_OPENING) अणु
		क्रम (i = 0; i < state->unused_service; i++) अणु
			अगर (!rcu_access_poपूर्णांकer(state->services[i])) अणु
				pservice = &state->services[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_lock();
		क्रम (i = (state->unused_service - 1); i >= 0; i--) अणु
			काष्ठा vchiq_service *srv;

			srv = rcu_dereference(state->services[i]);
			अगर (!srv)
				pservice = &state->services[i];
			अन्यथा अगर ((srv->खुला_fourcc == params->fourcc) &&
				 ((srv->instance != instance) ||
				  (srv->base.callback != params->callback))) अणु
				/*
				 * There is another server using this
				 * fourcc which करोesn't match.
				 */
				pservice = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (pservice) अणु
		service->localport = (pservice - state->services);
		अगर (!handle_seq)
			handle_seq = VCHIQ_MAX_STATES *
				 VCHIQ_MAX_SERVICES;
		service->handle = handle_seq |
			(state->id * VCHIQ_MAX_SERVICES) |
			service->localport;
		handle_seq += VCHIQ_MAX_STATES * VCHIQ_MAX_SERVICES;
		rcu_assign_poपूर्णांकer(*pservice, service);
		अगर (pservice == &state->services[state->unused_service])
			state->unused_service++;
	पूर्ण

	mutex_unlock(&state->mutex);

	अगर (!pservice) अणु
		kमुक्त(service);
		वापस शून्य;
	पूर्ण

	quota = &state->service_quotas[service->localport];
	quota->slot_quota = state->शेष_slot_quota;
	quota->message_quota = state->शेष_message_quota;
	अगर (quota->slot_use_count == 0)
		quota->previous_tx_index =
			SLOT_QUEUE_INDEX_FROM_POS(state->local_tx_pos)
			- 1;

	/* Bring this service online */
	vchiq_set_service_state(service, srvstate);

	vchiq_log_info(vchiq_core_msg_log_level,
		"%s Service %c%c%c%c SrcPort:%d",
		(srvstate == VCHIQ_SRVSTATE_OPENING)
		? "Open" : "Add",
		VCHIQ_FOURCC_AS_4CHARS(params->fourcc),
		service->localport);

	/* Don't unlock the service - leave it with a ref_count of 1. */

	वापस service;
पूर्ण

क्रमागत vchiq_status
vchiq_खोलो_service_पूर्णांकernal(काष्ठा vchiq_service *service, पूर्णांक client_id)
अणु
	काष्ठा vchiq_खोलो_payload payload = अणु
		service->base.fourcc,
		client_id,
		service->version,
		service->version_min
	पूर्ण;
	क्रमागत vchiq_status status = VCHIQ_SUCCESS;

	service->client_id = client_id;
	vchiq_use_service_पूर्णांकernal(service);
	status = queue_message(service->state,
			       शून्य,
			       VCHIQ_MAKE_MSG(VCHIQ_MSG_OPEN,
					      service->localport,
					      0),
			       स_नकल_copy_callback,
			       &payload,
			       माप(payload),
			       QMFLAGS_IS_BLOCKING);

	अगर (status != VCHIQ_SUCCESS)
		वापस status;

	/* Wait क्रम the ACK/NAK */
	अगर (रुको_क्रम_completion_पूर्णांकerruptible(&service->हटाओ_event)) अणु
		status = VCHIQ_RETRY;
		vchiq_release_service_पूर्णांकernal(service);
	पूर्ण अन्यथा अगर ((service->srvstate != VCHIQ_SRVSTATE_OPEN) &&
		   (service->srvstate != VCHIQ_SRVSTATE_OPENSYNC)) अणु
		अगर (service->srvstate != VCHIQ_SRVSTATE_CLOSEWAIT)
			vchiq_log_error(vchiq_core_log_level,
					"%d: osi - srvstate = %s (ref %u)",
					service->state->id,
					srvstate_names[service->srvstate],
					kref_पढ़ो(&service->ref_count));
		status = VCHIQ_ERROR;
		VCHIQ_SERVICE_STATS_INC(service, error_count);
		vchiq_release_service_पूर्णांकernal(service);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम
release_service_messages(काष्ठा vchiq_service *service)
अणु
	काष्ठा vchiq_state *state = service->state;
	पूर्णांक slot_last = state->remote->slot_last;
	पूर्णांक i;

	/* Release any claimed messages aimed at this service */

	अगर (service->sync) अणु
		काष्ठा vchiq_header *header =
			(काष्ठा vchiq_header *)SLOT_DATA_FROM_INDEX(state,
						state->remote->slot_sync);
		अगर (VCHIQ_MSG_DSTPORT(header->msgid) == service->localport)
			release_message_sync(state, header);

		वापस;
	पूर्ण

	क्रम (i = state->remote->slot_first; i <= slot_last; i++) अणु
		काष्ठा vchiq_slot_info *slot_info =
			SLOT_INFO_FROM_INDEX(state, i);
		अगर (slot_info->release_count != slot_info->use_count) अणु
			अक्षर *data =
				(अक्षर *)SLOT_DATA_FROM_INDEX(state, i);
			अचिन्हित पूर्णांक pos, end;

			end = VCHIQ_SLOT_SIZE;
			अगर (data == state->rx_data)
				/*
				 * This buffer is still being पढ़ो from - stop
				 * at the current पढ़ो position
				 */
				end = state->rx_pos & VCHIQ_SLOT_MASK;

			pos = 0;

			जबतक (pos < end) अणु
				काष्ठा vchiq_header *header =
					(काष्ठा vchiq_header *)(data + pos);
				पूर्णांक msgid = header->msgid;
				पूर्णांक port = VCHIQ_MSG_DSTPORT(msgid);

				अगर ((port == service->localport) &&
					(msgid & VCHIQ_MSGID_CLAIMED)) अणु
					vchiq_log_info(vchiq_core_log_level,
						"  fsi - hdr %pK", header);
					release_slot(state, slot_info, header,
						शून्य);
				पूर्ण
				pos += calc_stride(header->size);
				अगर (pos > VCHIQ_SLOT_SIZE) अणु
					vchiq_log_error(vchiq_core_log_level,
						"fsi - pos %x: header %pK, msgid %x, header->msgid %x, header->size %x",
						pos, header, msgid,
						header->msgid, header->size);
					WARN(1, "invalid slot position\n");
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
करो_पात_bulks(काष्ठा vchiq_service *service)
अणु
	क्रमागत vchiq_status status;

	/* Abort any outstanding bulk transfers */
	अगर (mutex_lock_समाप्तable(&service->bulk_mutex))
		वापस 0;
	पात_outstanding_bulks(service, &service->bulk_tx);
	पात_outstanding_bulks(service, &service->bulk_rx);
	mutex_unlock(&service->bulk_mutex);

	status = notअगरy_bulks(service, &service->bulk_tx, 0/*!retry_poll*/);
	अगर (status == VCHIQ_SUCCESS)
		status = notअगरy_bulks(service, &service->bulk_rx,
			0/*!retry_poll*/);
	वापस (status == VCHIQ_SUCCESS);
पूर्ण

अटल क्रमागत vchiq_status
बंद_service_complete(काष्ठा vchiq_service *service, पूर्णांक failstate)
अणु
	क्रमागत vchiq_status status;
	पूर्णांक is_server = (service->खुला_fourcc != VCHIQ_FOURCC_INVALID);
	पूर्णांक newstate;

	चयन (service->srvstate) अणु
	हाल VCHIQ_SRVSTATE_OPEN:
	हाल VCHIQ_SRVSTATE_CLOSESENT:
	हाल VCHIQ_SRVSTATE_CLOSERECVD:
		अगर (is_server) अणु
			अगर (service->स्वतः_बंद) अणु
				service->client_id = 0;
				service->remoteport = VCHIQ_PORT_FREE;
				newstate = VCHIQ_SRVSTATE_LISTENING;
			पूर्ण अन्यथा
				newstate = VCHIQ_SRVSTATE_CLOSEWAIT;
		पूर्ण अन्यथा
			newstate = VCHIQ_SRVSTATE_CLOSED;
		vchiq_set_service_state(service, newstate);
		अवरोध;
	हाल VCHIQ_SRVSTATE_LISTENING:
		अवरोध;
	शेष:
		vchiq_log_error(vchiq_core_log_level,
			"%s(%x) called in state %s", __func__,
			service->handle, srvstate_names[service->srvstate]);
		WARN(1, "%s in unexpected state\n", __func__);
		वापस VCHIQ_ERROR;
	पूर्ण

	status = make_service_callback(service,
		VCHIQ_SERVICE_CLOSED, शून्य, शून्य);

	अगर (status != VCHIQ_RETRY) अणु
		पूर्णांक uc = service->service_use_count;
		पूर्णांक i;
		/* Complete the बंद process */
		क्रम (i = 0; i < uc; i++)
			/*
			 * cater क्रम हालs where बंद is क्रमced and the
			 * client may not बंद all it's handles
			 */
			vchiq_release_service_पूर्णांकernal(service);

		service->client_id = 0;
		service->remoteport = VCHIQ_PORT_FREE;

		अगर (service->srvstate == VCHIQ_SRVSTATE_CLOSED)
			vchiq_मुक्त_service_पूर्णांकernal(service);
		अन्यथा अगर (service->srvstate != VCHIQ_SRVSTATE_CLOSEWAIT) अणु
			अगर (is_server)
				service->closing = 0;

			complete(&service->हटाओ_event);
		पूर्ण
	पूर्ण अन्यथा
		vchiq_set_service_state(service, failstate);

	वापस status;
पूर्ण

/* Called by the slot handler */
क्रमागत vchiq_status
vchiq_बंद_service_पूर्णांकernal(काष्ठा vchiq_service *service, पूर्णांक बंद_recvd)
अणु
	काष्ठा vchiq_state *state = service->state;
	क्रमागत vchiq_status status = VCHIQ_SUCCESS;
	पूर्णांक is_server = (service->खुला_fourcc != VCHIQ_FOURCC_INVALID);

	vchiq_log_info(vchiq_core_log_level, "%d: csi:%d,%d (%s)",
		service->state->id, service->localport, बंद_recvd,
		srvstate_names[service->srvstate]);

	चयन (service->srvstate) अणु
	हाल VCHIQ_SRVSTATE_CLOSED:
	हाल VCHIQ_SRVSTATE_HIDDEN:
	हाल VCHIQ_SRVSTATE_LISTENING:
	हाल VCHIQ_SRVSTATE_CLOSEWAIT:
		अगर (बंद_recvd)
			vchiq_log_error(vchiq_core_log_level,
				"%s(1) called in state %s",
				__func__, srvstate_names[service->srvstate]);
		अन्यथा अगर (is_server) अणु
			अगर (service->srvstate == VCHIQ_SRVSTATE_LISTENING) अणु
				status = VCHIQ_ERROR;
			पूर्ण अन्यथा अणु
				service->client_id = 0;
				service->remoteport = VCHIQ_PORT_FREE;
				अगर (service->srvstate ==
					VCHIQ_SRVSTATE_CLOSEWAIT)
					vchiq_set_service_state(service,
						VCHIQ_SRVSTATE_LISTENING);
			पूर्ण
			complete(&service->हटाओ_event);
		पूर्ण अन्यथा
			vchiq_मुक्त_service_पूर्णांकernal(service);
		अवरोध;
	हाल VCHIQ_SRVSTATE_OPENING:
		अगर (बंद_recvd) अणु
			/* The खोलो was rejected - tell the user */
			vchiq_set_service_state(service,
				VCHIQ_SRVSTATE_CLOSEWAIT);
			complete(&service->हटाओ_event);
		पूर्ण अन्यथा अणु
			/* Shutकरोwn mid-खोलो - let the other side know */
			status = queue_message(state, service,
				VCHIQ_MAKE_MSG
				(VCHIQ_MSG_CLOSE,
				service->localport,
				VCHIQ_MSG_DSTPORT(service->remoteport)),
				शून्य, शून्य, 0, 0);
		पूर्ण
		अवरोध;

	हाल VCHIQ_SRVSTATE_OPENSYNC:
		mutex_lock(&state->sync_mutex);
		fallthrough;
	हाल VCHIQ_SRVSTATE_OPEN:
		अगर (बंद_recvd) अणु
			अगर (!करो_पात_bulks(service))
				status = VCHIQ_RETRY;
		पूर्ण

		release_service_messages(service);

		अगर (status == VCHIQ_SUCCESS)
			status = queue_message(state, service,
				VCHIQ_MAKE_MSG
				(VCHIQ_MSG_CLOSE,
				service->localport,
				VCHIQ_MSG_DSTPORT(service->remoteport)),
				शून्य, शून्य, 0, QMFLAGS_NO_MUTEX_UNLOCK);

		अगर (status == VCHIQ_SUCCESS) अणु
			अगर (!बंद_recvd) अणु
				/* Change the state जबतक the mutex is still held */
				vchiq_set_service_state(service,
							VCHIQ_SRVSTATE_CLOSESENT);
				mutex_unlock(&state->slot_mutex);
				अगर (service->sync)
					mutex_unlock(&state->sync_mutex);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (service->srvstate == VCHIQ_SRVSTATE_OPENSYNC) अणु
			mutex_unlock(&state->sync_mutex);
			अवरोध;
		पूर्ण अन्यथा
			अवरोध;

		/* Change the state जबतक the mutex is still held */
		vchiq_set_service_state(service, VCHIQ_SRVSTATE_CLOSERECVD);
		mutex_unlock(&state->slot_mutex);
		अगर (service->sync)
			mutex_unlock(&state->sync_mutex);

		status = बंद_service_complete(service,
				VCHIQ_SRVSTATE_CLOSERECVD);
		अवरोध;

	हाल VCHIQ_SRVSTATE_CLOSESENT:
		अगर (!बंद_recvd)
			/* This happens when a process is समाप्तed mid-बंद */
			अवरोध;

		अगर (!करो_पात_bulks(service)) अणु
			status = VCHIQ_RETRY;
			अवरोध;
		पूर्ण

		अगर (status == VCHIQ_SUCCESS)
			status = बंद_service_complete(service,
				VCHIQ_SRVSTATE_CLOSERECVD);
		अवरोध;

	हाल VCHIQ_SRVSTATE_CLOSERECVD:
		अगर (!बंद_recvd && is_server)
			/* Force पूर्णांकo LISTENING mode */
			vchiq_set_service_state(service,
				VCHIQ_SRVSTATE_LISTENING);
		status = बंद_service_complete(service,
			VCHIQ_SRVSTATE_CLOSERECVD);
		अवरोध;

	शेष:
		vchiq_log_error(vchiq_core_log_level,
			"%s(%d) called in state %s", __func__,
			बंद_recvd, srvstate_names[service->srvstate]);
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/* Called from the application process upon process death */
व्योम
vchiq_terminate_service_पूर्णांकernal(काष्ठा vchiq_service *service)
अणु
	काष्ठा vchiq_state *state = service->state;

	vchiq_log_info(vchiq_core_log_level, "%d: tsi - (%d<->%d)",
		state->id, service->localport, service->remoteport);

	mark_service_closing(service);

	/* Mark the service क्रम removal by the slot handler */
	request_poll(state, service, VCHIQ_POLL_REMOVE);
पूर्ण

/* Called from the slot handler */
व्योम
vchiq_मुक्त_service_पूर्णांकernal(काष्ठा vchiq_service *service)
अणु
	काष्ठा vchiq_state *state = service->state;

	vchiq_log_info(vchiq_core_log_level, "%d: fsi - (%d)",
		state->id, service->localport);

	चयन (service->srvstate) अणु
	हाल VCHIQ_SRVSTATE_OPENING:
	हाल VCHIQ_SRVSTATE_CLOSED:
	हाल VCHIQ_SRVSTATE_HIDDEN:
	हाल VCHIQ_SRVSTATE_LISTENING:
	हाल VCHIQ_SRVSTATE_CLOSEWAIT:
		अवरोध;
	शेष:
		vchiq_log_error(vchiq_core_log_level,
			"%d: fsi - (%d) in state %s",
			state->id, service->localport,
			srvstate_names[service->srvstate]);
		वापस;
	पूर्ण

	vchiq_set_service_state(service, VCHIQ_SRVSTATE_FREE);

	complete(&service->हटाओ_event);

	/* Release the initial lock */
	unlock_service(service);
पूर्ण

क्रमागत vchiq_status
vchiq_connect_पूर्णांकernal(काष्ठा vchiq_state *state, काष्ठा vchiq_instance *instance)
अणु
	काष्ठा vchiq_service *service;
	पूर्णांक i;

	/* Find all services रेजिस्टरed to this client and enable them. */
	i = 0;
	जबतक ((service = next_service_by_instance(state, instance,
		&i)) !=	शून्य) अणु
		अगर (service->srvstate == VCHIQ_SRVSTATE_HIDDEN)
			vchiq_set_service_state(service,
				VCHIQ_SRVSTATE_LISTENING);
		unlock_service(service);
	पूर्ण

	अगर (state->conn_state == VCHIQ_CONNSTATE_DISCONNECTED) अणु
		अगर (queue_message(state, शून्य,
			VCHIQ_MAKE_MSG(VCHIQ_MSG_CONNECT, 0, 0), शून्य, शून्य,
			0, QMFLAGS_IS_BLOCKING) == VCHIQ_RETRY)
			वापस VCHIQ_RETRY;

		vchiq_set_conn_state(state, VCHIQ_CONNSTATE_CONNECTING);
	पूर्ण

	अगर (state->conn_state == VCHIQ_CONNSTATE_CONNECTING) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&state->connect))
			वापस VCHIQ_RETRY;

		vchiq_set_conn_state(state, VCHIQ_CONNSTATE_CONNECTED);
		complete(&state->connect);
	पूर्ण

	वापस VCHIQ_SUCCESS;
पूर्ण

क्रमागत vchiq_status
vchiq_shutकरोwn_पूर्णांकernal(काष्ठा vchiq_state *state, काष्ठा vchiq_instance *instance)
अणु
	काष्ठा vchiq_service *service;
	पूर्णांक i;

	/* Find all services रेजिस्टरed to this client and enable them. */
	i = 0;
	जबतक ((service = next_service_by_instance(state, instance,
		&i)) !=	शून्य) अणु
		(व्योम)vchiq_हटाओ_service(service->handle);
		unlock_service(service);
	पूर्ण

	वापस VCHIQ_SUCCESS;
पूर्ण

क्रमागत vchiq_status
vchiq_बंद_service(अचिन्हित पूर्णांक handle)
अणु
	/* Unरेजिस्टर the service */
	काष्ठा vchiq_service *service = find_service_by_handle(handle);
	क्रमागत vchiq_status status = VCHIQ_SUCCESS;

	अगर (!service)
		वापस VCHIQ_ERROR;

	vchiq_log_info(vchiq_core_log_level,
		"%d: close_service:%d",
		service->state->id, service->localport);

	अगर ((service->srvstate == VCHIQ_SRVSTATE_FREE) ||
	    (service->srvstate == VCHIQ_SRVSTATE_LISTENING) ||
	    (service->srvstate == VCHIQ_SRVSTATE_HIDDEN)) अणु
		unlock_service(service);
		वापस VCHIQ_ERROR;
	पूर्ण

	mark_service_closing(service);

	अगर (current == service->state->slot_handler_thपढ़ो) अणु
		status = vchiq_बंद_service_पूर्णांकernal(service,
			0/*!बंद_recvd*/);
		WARN_ON(status == VCHIQ_RETRY);
	पूर्ण अन्यथा अणु
	/* Mark the service क्रम termination by the slot handler */
		request_poll(service->state, service, VCHIQ_POLL_TERMINATE);
	पूर्ण

	जबतक (1) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&service->हटाओ_event)) अणु
			status = VCHIQ_RETRY;
			अवरोध;
		पूर्ण

		अगर ((service->srvstate == VCHIQ_SRVSTATE_FREE) ||
		    (service->srvstate == VCHIQ_SRVSTATE_LISTENING) ||
		    (service->srvstate == VCHIQ_SRVSTATE_OPEN))
			अवरोध;

		vchiq_log_warning(vchiq_core_log_level,
			"%d: close_service:%d - waiting in state %s",
			service->state->id, service->localport,
			srvstate_names[service->srvstate]);
	पूर्ण

	अगर ((status == VCHIQ_SUCCESS) &&
	    (service->srvstate != VCHIQ_SRVSTATE_FREE) &&
	    (service->srvstate != VCHIQ_SRVSTATE_LISTENING))
		status = VCHIQ_ERROR;

	unlock_service(service);

	वापस status;
पूर्ण
EXPORT_SYMBOL(vchiq_बंद_service);

क्रमागत vchiq_status
vchiq_हटाओ_service(अचिन्हित पूर्णांक handle)
अणु
	/* Unरेजिस्टर the service */
	काष्ठा vchiq_service *service = find_service_by_handle(handle);
	क्रमागत vchiq_status status = VCHIQ_SUCCESS;

	अगर (!service)
		वापस VCHIQ_ERROR;

	vchiq_log_info(vchiq_core_log_level,
		"%d: remove_service:%d",
		service->state->id, service->localport);

	अगर (service->srvstate == VCHIQ_SRVSTATE_FREE) अणु
		unlock_service(service);
		वापस VCHIQ_ERROR;
	पूर्ण

	mark_service_closing(service);

	अगर ((service->srvstate == VCHIQ_SRVSTATE_HIDDEN) ||
	    (current == service->state->slot_handler_thपढ़ो)) अणु
		/*
		 * Make it look like a client, because it must be हटाओd and
		 * not left in the LISTENING state.
		 */
		service->खुला_fourcc = VCHIQ_FOURCC_INVALID;

		status = vchiq_बंद_service_पूर्णांकernal(service,
			0/*!बंद_recvd*/);
		WARN_ON(status == VCHIQ_RETRY);
	पूर्ण अन्यथा अणु
		/* Mark the service क्रम removal by the slot handler */
		request_poll(service->state, service, VCHIQ_POLL_REMOVE);
	पूर्ण
	जबतक (1) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&service->हटाओ_event)) अणु
			status = VCHIQ_RETRY;
			अवरोध;
		पूर्ण

		अगर ((service->srvstate == VCHIQ_SRVSTATE_FREE) ||
		    (service->srvstate == VCHIQ_SRVSTATE_OPEN))
			अवरोध;

		vchiq_log_warning(vchiq_core_log_level,
			"%d: remove_service:%d - waiting in state %s",
			service->state->id, service->localport,
			srvstate_names[service->srvstate]);
	पूर्ण

	अगर ((status == VCHIQ_SUCCESS) &&
	    (service->srvstate != VCHIQ_SRVSTATE_FREE))
		status = VCHIQ_ERROR;

	unlock_service(service);

	वापस status;
पूर्ण

/*
 * This function may be called by kernel thपढ़ोs or user thपढ़ोs.
 * User thपढ़ोs may receive VCHIQ_RETRY to indicate that a संकेत has been
 * received and the call should be retried after being वापसed to user
 * context.
 * When called in blocking mode, the userdata field poपूर्णांकs to a bulk_रुकोer
 * काष्ठाure.
 */
क्रमागत vchiq_status vchiq_bulk_transfer(अचिन्हित पूर्णांक handle,
				   व्योम *offset, व्योम __user *uoffset,
				   पूर्णांक size, व्योम *userdata,
				   क्रमागत vchiq_bulk_mode mode,
				   क्रमागत vchiq_bulk_dir dir)
अणु
	काष्ठा vchiq_service *service = find_service_by_handle(handle);
	काष्ठा vchiq_bulk_queue *queue;
	काष्ठा vchiq_bulk *bulk;
	काष्ठा vchiq_state *state;
	काष्ठा bulk_रुकोer *bulk_रुकोer = शून्य;
	स्थिर अक्षर dir_अक्षर = (dir == VCHIQ_BULK_TRANSMIT) ? 't' : 'r';
	स्थिर पूर्णांक dir_msgtype = (dir == VCHIQ_BULK_TRANSMIT) ?
		VCHIQ_MSG_BULK_TX : VCHIQ_MSG_BULK_RX;
	क्रमागत vchiq_status status = VCHIQ_ERROR;
	पूर्णांक payload[2];

	अगर (!service)
		जाओ error_निकास;

	अगर (service->srvstate != VCHIQ_SRVSTATE_OPEN)
		जाओ error_निकास;

	अगर (!offset && !uoffset)
		जाओ error_निकास;

	अगर (vchiq_check_service(service) != VCHIQ_SUCCESS)
		जाओ error_निकास;

	चयन (mode) अणु
	हाल VCHIQ_BULK_MODE_NOCALLBACK:
	हाल VCHIQ_BULK_MODE_CALLBACK:
		अवरोध;
	हाल VCHIQ_BULK_MODE_BLOCKING:
		bulk_रुकोer = userdata;
		init_completion(&bulk_रुकोer->event);
		bulk_रुकोer->actual = 0;
		bulk_रुकोer->bulk = शून्य;
		अवरोध;
	हाल VCHIQ_BULK_MODE_WAITING:
		bulk_रुकोer = userdata;
		bulk = bulk_रुकोer->bulk;
		जाओ रुकोing;
	शेष:
		जाओ error_निकास;
	पूर्ण

	state = service->state;

	queue = (dir == VCHIQ_BULK_TRANSMIT) ?
		&service->bulk_tx : &service->bulk_rx;

	अगर (mutex_lock_समाप्तable(&service->bulk_mutex)) अणु
		status = VCHIQ_RETRY;
		जाओ error_निकास;
	पूर्ण

	अगर (queue->local_insert == queue->हटाओ + VCHIQ_NUM_SERVICE_BULKS) अणु
		VCHIQ_SERVICE_STATS_INC(service, bulk_stalls);
		करो अणु
			mutex_unlock(&service->bulk_mutex);
			अगर (रुको_क्रम_completion_पूर्णांकerruptible(
						&service->bulk_हटाओ_event)) अणु
				status = VCHIQ_RETRY;
				जाओ error_निकास;
			पूर्ण
			अगर (mutex_lock_समाप्तable(&service->bulk_mutex)) अणु
				status = VCHIQ_RETRY;
				जाओ error_निकास;
			पूर्ण
		पूर्ण जबतक (queue->local_insert == queue->हटाओ +
				VCHIQ_NUM_SERVICE_BULKS);
	पूर्ण

	bulk = &queue->bulks[BULK_INDEX(queue->local_insert)];

	bulk->mode = mode;
	bulk->dir = dir;
	bulk->userdata = userdata;
	bulk->size = size;
	bulk->actual = VCHIQ_BULK_ACTUAL_ABORTED;

	अगर (vchiq_prepare_bulk_data(bulk, offset, uoffset, size, dir)
			!= VCHIQ_SUCCESS)
		जाओ unlock_error_निकास;

	wmb();

	vchiq_log_info(vchiq_core_log_level,
		"%d: bt (%d->%d) %cx %x@%pad %pK",
		state->id, service->localport, service->remoteport, dir_अक्षर,
		size, &bulk->data, userdata);

	/*
	 * The slot mutex must be held when the service is being बंदd, so
	 * claim it here to ensure that isn't happening
	 */
	अगर (mutex_lock_समाप्तable(&state->slot_mutex)) अणु
		status = VCHIQ_RETRY;
		जाओ cancel_bulk_error_निकास;
	पूर्ण

	अगर (service->srvstate != VCHIQ_SRVSTATE_OPEN)
		जाओ unlock_both_error_निकास;

	payload[0] = lower_32_bits(bulk->data);
	payload[1] = bulk->size;
	status = queue_message(state,
			       शून्य,
			       VCHIQ_MAKE_MSG(dir_msgtype,
					      service->localport,
					      service->remoteport),
			       स_नकल_copy_callback,
			       &payload,
			       माप(payload),
			       QMFLAGS_IS_BLOCKING |
			       QMFLAGS_NO_MUTEX_LOCK |
			       QMFLAGS_NO_MUTEX_UNLOCK);
	अगर (status != VCHIQ_SUCCESS)
		जाओ unlock_both_error_निकास;

	queue->local_insert++;

	mutex_unlock(&state->slot_mutex);
	mutex_unlock(&service->bulk_mutex);

	vchiq_log_trace(vchiq_core_log_level,
		"%d: bt:%d %cx li=%x ri=%x p=%x",
		state->id,
		service->localport, dir_अक्षर,
		queue->local_insert, queue->remote_insert, queue->process);

रुकोing:
	unlock_service(service);

	status = VCHIQ_SUCCESS;

	अगर (bulk_रुकोer) अणु
		bulk_रुकोer->bulk = bulk;
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&bulk_रुकोer->event))
			status = VCHIQ_RETRY;
		अन्यथा अगर (bulk_रुकोer->actual == VCHIQ_BULK_ACTUAL_ABORTED)
			status = VCHIQ_ERROR;
	पूर्ण

	वापस status;

unlock_both_error_निकास:
	mutex_unlock(&state->slot_mutex);
cancel_bulk_error_निकास:
	vchiq_complete_bulk(bulk);
unlock_error_निकास:
	mutex_unlock(&service->bulk_mutex);

error_निकास:
	अगर (service)
		unlock_service(service);
	वापस status;
पूर्ण

क्रमागत vchiq_status
vchiq_queue_message(अचिन्हित पूर्णांक handle,
		    sमाप_प्रकार (*copy_callback)(व्योम *context, व्योम *dest,
					     माप_प्रकार offset, माप_प्रकार maxsize),
		    व्योम *context,
		    माप_प्रकार size)
अणु
	काष्ठा vchiq_service *service = find_service_by_handle(handle);
	क्रमागत vchiq_status status = VCHIQ_ERROR;

	अगर (!service)
		जाओ error_निकास;

	अगर (vchiq_check_service(service) != VCHIQ_SUCCESS)
		जाओ error_निकास;

	अगर (!size) अणु
		VCHIQ_SERVICE_STATS_INC(service, error_count);
		जाओ error_निकास;

	पूर्ण

	अगर (size > VCHIQ_MAX_MSG_SIZE) अणु
		VCHIQ_SERVICE_STATS_INC(service, error_count);
		जाओ error_निकास;
	पूर्ण

	चयन (service->srvstate) अणु
	हाल VCHIQ_SRVSTATE_OPEN:
		status = queue_message(service->state, service,
				VCHIQ_MAKE_MSG(VCHIQ_MSG_DATA,
					service->localport,
					service->remoteport),
				copy_callback, context, size, 1);
		अवरोध;
	हाल VCHIQ_SRVSTATE_OPENSYNC:
		status = queue_message_sync(service->state, service,
				VCHIQ_MAKE_MSG(VCHIQ_MSG_DATA,
					service->localport,
					service->remoteport),
				copy_callback, context, size, 1);
		अवरोध;
	शेष:
		status = VCHIQ_ERROR;
		अवरोध;
	पूर्ण

error_निकास:
	अगर (service)
		unlock_service(service);

	वापस status;
पूर्ण

पूर्णांक vchiq_queue_kernel_message(अचिन्हित पूर्णांक handle, व्योम *data, अचिन्हित पूर्णांक size)
अणु
	क्रमागत vchiq_status status;

	जबतक (1) अणु
		status = vchiq_queue_message(handle, स_नकल_copy_callback,
					     data, size);

		/*
		 * vchiq_queue_message() may वापस VCHIQ_RETRY, so we need to
		 * implement a retry mechanism since this function is supposed
		 * to block until queued
		 */
		अगर (status != VCHIQ_RETRY)
			अवरोध;

		msleep(1);
	पूर्ण

	वापस status;
पूर्ण
EXPORT_SYMBOL(vchiq_queue_kernel_message);

व्योम
vchiq_release_message(अचिन्हित पूर्णांक handle,
		      काष्ठा vchiq_header *header)
अणु
	काष्ठा vchiq_service *service = find_service_by_handle(handle);
	काष्ठा vchiq_shared_state *remote;
	काष्ठा vchiq_state *state;
	पूर्णांक slot_index;

	अगर (!service)
		वापस;

	state = service->state;
	remote = state->remote;

	slot_index = SLOT_INDEX_FROM_DATA(state, (व्योम *)header);

	अगर ((slot_index >= remote->slot_first) &&
	    (slot_index <= remote->slot_last)) अणु
		पूर्णांक msgid = header->msgid;

		अगर (msgid & VCHIQ_MSGID_CLAIMED) अणु
			काष्ठा vchiq_slot_info *slot_info =
				SLOT_INFO_FROM_INDEX(state, slot_index);

			release_slot(state, slot_info, header, service);
		पूर्ण
	पूर्ण अन्यथा अगर (slot_index == remote->slot_sync)
		release_message_sync(state, header);

	unlock_service(service);
पूर्ण
EXPORT_SYMBOL(vchiq_release_message);

अटल व्योम
release_message_sync(काष्ठा vchiq_state *state, काष्ठा vchiq_header *header)
अणु
	header->msgid = VCHIQ_MSGID_PADDING;
	remote_event_संकेत(&state->remote->sync_release);
पूर्ण

क्रमागत vchiq_status
vchiq_get_peer_version(अचिन्हित पूर्णांक handle, लघु *peer_version)
अणु
	क्रमागत vchiq_status status = VCHIQ_ERROR;
	काष्ठा vchiq_service *service = find_service_by_handle(handle);

	अगर (!service)
		जाओ निकास;

	अगर (vchiq_check_service(service) != VCHIQ_SUCCESS)
		जाओ निकास;

	अगर (!peer_version)
		जाओ निकास;

	*peer_version = service->peer_version;
	status = VCHIQ_SUCCESS;

निकास:
	अगर (service)
		unlock_service(service);
	वापस status;
पूर्ण
EXPORT_SYMBOL(vchiq_get_peer_version);

व्योम vchiq_get_config(काष्ठा vchiq_config *config)
अणु
	config->max_msg_size           = VCHIQ_MAX_MSG_SIZE;
	config->bulk_threshold         = VCHIQ_MAX_MSG_SIZE;
	config->max_outstanding_bulks  = VCHIQ_NUM_SERVICE_BULKS;
	config->max_services           = VCHIQ_MAX_SERVICES;
	config->version                = VCHIQ_VERSION;
	config->version_min            = VCHIQ_VERSION_MIN;
पूर्ण

क्रमागत vchiq_status
vchiq_set_service_option(अचिन्हित पूर्णांक handle,
	क्रमागत vchiq_service_option option, पूर्णांक value)
अणु
	काष्ठा vchiq_service *service = find_service_by_handle(handle);
	क्रमागत vchiq_status status = VCHIQ_ERROR;
	काष्ठा vchiq_service_quota *quota;

	अगर (!service)
		वापस VCHIQ_ERROR;

	चयन (option) अणु
	हाल VCHIQ_SERVICE_OPTION_AUTOCLOSE:
		service->स्वतः_बंद = value;
		status = VCHIQ_SUCCESS;
		अवरोध;

	हाल VCHIQ_SERVICE_OPTION_SLOT_QUOTA:
		quota = &service->state->service_quotas[service->localport];
		अगर (value == 0)
			value = service->state->शेष_slot_quota;
		अगर ((value >= quota->slot_use_count) &&
		    (value < (अचिन्हित लघु)~0)) अणु
			quota->slot_quota = value;
			अगर ((value >= quota->slot_use_count) &&
			    (quota->message_quota >= quota->message_use_count))
				/*
				 * Signal the service that it may have
				 * dropped below its quota
				 */
				complete(&quota->quota_event);
			status = VCHIQ_SUCCESS;
		पूर्ण
		अवरोध;

	हाल VCHIQ_SERVICE_OPTION_MESSAGE_QUOTA:
		quota = &service->state->service_quotas[service->localport];
		अगर (value == 0)
			value = service->state->शेष_message_quota;
		अगर ((value >= quota->message_use_count) &&
		    (value < (अचिन्हित लघु)~0)) अणु
			quota->message_quota = value;
			अगर ((value >= quota->message_use_count) &&
			    (quota->slot_quota >= quota->slot_use_count))
				/*
				 * Signal the service that it may have
				 * dropped below its quota
				 */
				complete(&quota->quota_event);
			status = VCHIQ_SUCCESS;
		पूर्ण
		अवरोध;

	हाल VCHIQ_SERVICE_OPTION_SYNCHRONOUS:
		अगर ((service->srvstate == VCHIQ_SRVSTATE_HIDDEN) ||
		    (service->srvstate == VCHIQ_SRVSTATE_LISTENING)) अणु
			service->sync = value;
			status = VCHIQ_SUCCESS;
		पूर्ण
		अवरोध;

	हाल VCHIQ_SERVICE_OPTION_TRACE:
		service->trace = value;
		status = VCHIQ_SUCCESS;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	unlock_service(service);

	वापस status;
पूर्ण

अटल पूर्णांक
vchiq_dump_shared_state(व्योम *dump_context, काष्ठा vchiq_state *state,
			काष्ठा vchiq_shared_state *shared, स्थिर अक्षर *label)
अणु
	अटल स्थिर अक्षर *स्थिर debug_names[] = अणु
		"<entries>",
		"SLOT_HANDLER_COUNT",
		"SLOT_HANDLER_LINE",
		"PARSE_LINE",
		"PARSE_HEADER",
		"PARSE_MSGID",
		"AWAIT_COMPLETION_LINE",
		"DEQUEUE_MESSAGE_LINE",
		"SERVICE_CALLBACK_LINE",
		"MSG_QUEUE_FULL_COUNT",
		"COMPLETION_QUEUE_FULL_COUNT"
	पूर्ण;
	पूर्णांक i;
	अक्षर buf[80];
	पूर्णांक len;
	पूर्णांक err;

	len = scnम_लिखो(buf, माप(buf),
		"  %s: slots %d-%d tx_pos=%x recycle=%x",
		label, shared->slot_first, shared->slot_last,
		shared->tx_pos, shared->slot_queue_recycle);
	err = vchiq_dump(dump_context, buf, len + 1);
	अगर (err)
		वापस err;

	len = scnम_लिखो(buf, माप(buf),
		"    Slots claimed:");
	err = vchiq_dump(dump_context, buf, len + 1);
	अगर (err)
		वापस err;

	क्रम (i = shared->slot_first; i <= shared->slot_last; i++) अणु
		काष्ठा vchiq_slot_info slot_info =
						*SLOT_INFO_FROM_INDEX(state, i);
		अगर (slot_info.use_count != slot_info.release_count) अणु
			len = scnम_लिखो(buf, माप(buf),
				"      %d: %d/%d", i, slot_info.use_count,
				slot_info.release_count);
			err = vchiq_dump(dump_context, buf, len + 1);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	क्रम (i = 1; i < shared->debug[DEBUG_ENTRIES]; i++) अणु
		len = scnम_लिखो(buf, माप(buf), "    DEBUG: %s = %d(%x)",
			debug_names[i], shared->debug[i], shared->debug[i]);
		err = vchiq_dump(dump_context, buf, len + 1);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vchiq_dump_state(व्योम *dump_context, काष्ठा vchiq_state *state)
अणु
	अक्षर buf[80];
	पूर्णांक len;
	पूर्णांक i;
	पूर्णांक err;

	len = scnम_लिखो(buf, माप(buf), "State %d: %s", state->id,
		conn_state_names[state->conn_state]);
	err = vchiq_dump(dump_context, buf, len + 1);
	अगर (err)
		वापस err;

	len = scnम_लिखो(buf, माप(buf),
		"  tx_pos=%x(@%pK), rx_pos=%x(@%pK)",
		state->local->tx_pos,
		state->tx_data + (state->local_tx_pos & VCHIQ_SLOT_MASK),
		state->rx_pos,
		state->rx_data + (state->rx_pos & VCHIQ_SLOT_MASK));
	err = vchiq_dump(dump_context, buf, len + 1);
	अगर (err)
		वापस err;

	len = scnम_लिखो(buf, माप(buf),
		"  Version: %d (min %d)",
		VCHIQ_VERSION, VCHIQ_VERSION_MIN);
	err = vchiq_dump(dump_context, buf, len + 1);
	अगर (err)
		वापस err;

	अगर (VCHIQ_ENABLE_STATS) अणु
		len = scnम_लिखो(buf, माप(buf),
			"  Stats: ctrl_tx_count=%d, ctrl_rx_count=%d, error_count=%d",
			state->stats.ctrl_tx_count, state->stats.ctrl_rx_count,
			state->stats.error_count);
		err = vchiq_dump(dump_context, buf, len + 1);
		अगर (err)
			वापस err;
	पूर्ण

	len = scnम_लिखो(buf, माप(buf),
		"  Slots: %d available (%d data), %d recyclable, %d stalls (%d data)",
		((state->slot_queue_available * VCHIQ_SLOT_SIZE) -
			state->local_tx_pos) / VCHIQ_SLOT_SIZE,
		state->data_quota - state->data_use_count,
		state->local->slot_queue_recycle - state->slot_queue_available,
		state->stats.slot_stalls, state->stats.data_stalls);
	err = vchiq_dump(dump_context, buf, len + 1);
	अगर (err)
		वापस err;

	err = vchiq_dump_platक्रमm_state(dump_context);
	अगर (err)
		वापस err;

	err = vchiq_dump_shared_state(dump_context,
				      state,
				      state->local,
				      "Local");
	अगर (err)
		वापस err;
	err = vchiq_dump_shared_state(dump_context,
				      state,
				      state->remote,
				      "Remote");
	अगर (err)
		वापस err;

	err = vchiq_dump_platक्रमm_instances(dump_context);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < state->unused_service; i++) अणु
		काष्ठा vchiq_service *service = find_service_by_port(state, i);

		अगर (service) अणु
			err = vchiq_dump_service_state(dump_context, service);
			unlock_service(service);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vchiq_dump_service_state(व्योम *dump_context, काष्ठा vchiq_service *service)
अणु
	अक्षर buf[80];
	पूर्णांक len;
	पूर्णांक err;
	अचिन्हित पूर्णांक ref_count;

	/*Don't include the lock just taken*/
	ref_count = kref_पढ़ो(&service->ref_count) - 1;
	len = scnम_लिखो(buf, माप(buf), "Service %u: %s (ref %u)",
			service->localport, srvstate_names[service->srvstate],
			ref_count);

	अगर (service->srvstate != VCHIQ_SRVSTATE_FREE) अणु
		अक्षर remoteport[30];
		काष्ठा vchiq_service_quota *quota =
			&service->state->service_quotas[service->localport];
		पूर्णांक fourcc = service->base.fourcc;
		पूर्णांक tx_pending, rx_pending;

		अगर (service->remoteport != VCHIQ_PORT_FREE) अणु
			पूर्णांक len2 = scnम_लिखो(remoteport, माप(remoteport),
				"%u", service->remoteport);

			अगर (service->खुला_fourcc != VCHIQ_FOURCC_INVALID)
				scnम_लिखो(remoteport + len2,
					माप(remoteport) - len2,
					" (client %x)", service->client_id);
		पूर्ण अन्यथा
			म_नकल(remoteport, "n/a");

		len += scnम_लिखो(buf + len, माप(buf) - len,
			" '%c%c%c%c' remote %s (msg use %d/%d, slot use %d/%d)",
			VCHIQ_FOURCC_AS_4CHARS(fourcc),
			remoteport,
			quota->message_use_count,
			quota->message_quota,
			quota->slot_use_count,
			quota->slot_quota);

		err = vchiq_dump(dump_context, buf, len + 1);
		अगर (err)
			वापस err;

		tx_pending = service->bulk_tx.local_insert -
			service->bulk_tx.remote_insert;

		rx_pending = service->bulk_rx.local_insert -
			service->bulk_rx.remote_insert;

		len = scnम_लिखो(buf, माप(buf),
			"  Bulk: tx_pending=%d (size %d), rx_pending=%d (size %d)",
			tx_pending,
			tx_pending ? service->bulk_tx.bulks[
			BULK_INDEX(service->bulk_tx.हटाओ)].size : 0,
			rx_pending,
			rx_pending ? service->bulk_rx.bulks[
			BULK_INDEX(service->bulk_rx.हटाओ)].size : 0);

		अगर (VCHIQ_ENABLE_STATS) अणु
			err = vchiq_dump(dump_context, buf, len + 1);
			अगर (err)
				वापस err;

			len = scnम_लिखो(buf, माप(buf),
				"  Ctrl: tx_count=%d, tx_bytes=%llu, rx_count=%d, rx_bytes=%llu",
				service->stats.ctrl_tx_count,
				service->stats.ctrl_tx_bytes,
				service->stats.ctrl_rx_count,
				service->stats.ctrl_rx_bytes);
			err = vchiq_dump(dump_context, buf, len + 1);
			अगर (err)
				वापस err;

			len = scnम_लिखो(buf, माप(buf),
				"  Bulk: tx_count=%d, tx_bytes=%llu, rx_count=%d, rx_bytes=%llu",
				service->stats.bulk_tx_count,
				service->stats.bulk_tx_bytes,
				service->stats.bulk_rx_count,
				service->stats.bulk_rx_bytes);
			err = vchiq_dump(dump_context, buf, len + 1);
			अगर (err)
				वापस err;

			len = scnम_लिखो(buf, माप(buf),
				"  %d quota stalls, %d slot stalls, %d bulk stalls, %d aborted, %d errors",
				service->stats.quota_stalls,
				service->stats.slot_stalls,
				service->stats.bulk_stalls,
				service->stats.bulk_पातed_count,
				service->stats.error_count);
		पूर्ण
	पूर्ण

	err = vchiq_dump(dump_context, buf, len + 1);
	अगर (err)
		वापस err;

	अगर (service->srvstate != VCHIQ_SRVSTATE_FREE)
		err = vchiq_dump_platक्रमm_service_state(dump_context, service);
	वापस err;
पूर्ण

व्योम
vchiq_loud_error_header(व्योम)
अणु
	vchiq_log_error(vchiq_core_log_level,
		"============================================================================");
	vchiq_log_error(vchiq_core_log_level,
		"============================================================================");
	vchiq_log_error(vchiq_core_log_level, "=====");
पूर्ण

व्योम
vchiq_loud_error_footer(व्योम)
अणु
	vchiq_log_error(vchiq_core_log_level, "=====");
	vchiq_log_error(vchiq_core_log_level,
		"============================================================================");
	vchiq_log_error(vchiq_core_log_level,
		"============================================================================");
पूर्ण

क्रमागत vchiq_status vchiq_send_remote_use(काष्ठा vchiq_state *state)
अणु
	अगर (state->conn_state == VCHIQ_CONNSTATE_DISCONNECTED)
		वापस VCHIQ_RETRY;

	वापस queue_message(state, शून्य,
			     VCHIQ_MAKE_MSG(VCHIQ_MSG_REMOTE_USE, 0, 0),
			     शून्य, शून्य, 0, 0);
पूर्ण

क्रमागत vchiq_status vchiq_send_remote_use_active(काष्ठा vchiq_state *state)
अणु
	अगर (state->conn_state == VCHIQ_CONNSTATE_DISCONNECTED)
		वापस VCHIQ_RETRY;

	वापस queue_message(state, शून्य,
			     VCHIQ_MAKE_MSG(VCHIQ_MSG_REMOTE_USE_ACTIVE, 0, 0),
			     शून्य, शून्य, 0, 0);
पूर्ण

व्योम vchiq_log_dump_mem(स्थिर अक्षर *label, u32 addr, स्थिर व्योम *व्योम_mem,
	माप_प्रकार num_bytes)
अणु
	स्थिर u8  *mem = व्योम_mem;
	माप_प्रकार          offset;
	अक्षर            line_buf[100];
	अक्षर           *s;

	जबतक (num_bytes > 0) अणु
		s = line_buf;

		क्रम (offset = 0; offset < 16; offset++) अणु
			अगर (offset < num_bytes)
				s += scnम_लिखो(s, 4, "%02x ", mem[offset]);
			अन्यथा
				s += scnम_लिखो(s, 4, "   ");
		पूर्ण

		क्रम (offset = 0; offset < 16; offset++) अणु
			अगर (offset < num_bytes) अणु
				u8 ch = mem[offset];

				अगर ((ch < ' ') || (ch > '~'))
					ch = '.';
				*s++ = (अक्षर)ch;
			पूर्ण
		पूर्ण
		*s++ = '\0';

		अगर (label && (*label != '\0'))
			vchiq_log_trace(VCHIQ_LOG_TRACE,
				"%s: %08x: %s", label, addr, line_buf);
		अन्यथा
			vchiq_log_trace(VCHIQ_LOG_TRACE,
				"%08x: %s", addr, line_buf);

		addr += 16;
		mem += 16;
		अगर (num_bytes > 16)
			num_bytes -= 16;
		अन्यथा
			num_bytes = 0;
	पूर्ण
पूर्ण
