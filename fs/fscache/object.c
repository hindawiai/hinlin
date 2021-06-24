<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* FS-Cache object state machine handler
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * See Documentation/fileप्रणालीs/caching/object.rst क्रम a description of the
 * object state machine and the in-kernel representations.
 */

#घोषणा FSCACHE_DEBUG_LEVEL COOKIE
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/prefetch.h>
#समावेश "internal.h"

अटल स्थिर काष्ठा fscache_state *fscache_पात_initialisation(काष्ठा fscache_object *, पूर्णांक);
अटल स्थिर काष्ठा fscache_state *fscache_समाप्त_dependents(काष्ठा fscache_object *, पूर्णांक);
अटल स्थिर काष्ठा fscache_state *fscache_drop_object(काष्ठा fscache_object *, पूर्णांक);
अटल स्थिर काष्ठा fscache_state *fscache_initialise_object(काष्ठा fscache_object *, पूर्णांक);
अटल स्थिर काष्ठा fscache_state *fscache_invalidate_object(काष्ठा fscache_object *, पूर्णांक);
अटल स्थिर काष्ठा fscache_state *fscache_jumpstart_dependents(काष्ठा fscache_object *, पूर्णांक);
अटल स्थिर काष्ठा fscache_state *fscache_समाप्त_object(काष्ठा fscache_object *, पूर्णांक);
अटल स्थिर काष्ठा fscache_state *fscache_lookup_failure(काष्ठा fscache_object *, पूर्णांक);
अटल स्थिर काष्ठा fscache_state *fscache_look_up_object(काष्ठा fscache_object *, पूर्णांक);
अटल स्थिर काष्ठा fscache_state *fscache_object_available(काष्ठा fscache_object *, पूर्णांक);
अटल स्थिर काष्ठा fscache_state *fscache_parent_पढ़ोy(काष्ठा fscache_object *, पूर्णांक);
अटल स्थिर काष्ठा fscache_state *fscache_update_object(काष्ठा fscache_object *, पूर्णांक);
अटल स्थिर काष्ठा fscache_state *fscache_object_dead(काष्ठा fscache_object *, पूर्णांक);

#घोषणा __STATE_NAME(n) fscache_osm_##n
#घोषणा STATE(n) (&__STATE_NAME(n))

/*
 * Define a work state.  Work states are execution states.  No event processing
 * is perक्रमmed by them.  The function attached to a work state वापसs a
 * poपूर्णांकer indicating the next state to which the state machine should
 * transition.  Returning NO_TRANSIT repeats the current state, but goes back
 * to the scheduler first.
 */
#घोषणा WORK_STATE(n, sn, f) \
	स्थिर काष्ठा fscache_state __STATE_NAME(n) = अणु			\
		.name = #n,						\
		.लघु_name = sn,					\
		.work = f						\
	पूर्ण

/*
 * Returns from work states.
 */
#घोषणा transit_to(state) (अणु prefetch(&STATE(state)->work); STATE(state); पूर्ण)

#घोषणा NO_TRANSIT ((काष्ठा fscache_state *)शून्य)

/*
 * Define a रुको state.  Wait states are event processing states.  No execution
 * is perक्रमmed by them.  Wait states are just tables of "अगर event X occurs,
 * clear it and transition to state Y".  The dispatcher वापसs to the
 * scheduler अगर none of the events in which the रुको state has an पूर्णांकerest are
 * currently pending.
 */
#घोषणा WAIT_STATE(n, sn, ...) \
	स्थिर काष्ठा fscache_state __STATE_NAME(n) = अणु			\
		.name = #n,						\
		.लघु_name = sn,					\
		.work = शून्य,						\
		.transitions = अणु __VA_ARGS__, अणु 0, शून्य पूर्ण पूर्ण		\
	पूर्ण

#घोषणा TRANSIT_TO(state, emask) \
	अणु .events = (emask), .transit_to = STATE(state) पूर्ण

/*
 * The object state machine.
 */
अटल WORK_STATE(INIT_OBJECT,		"INIT", fscache_initialise_object);
अटल WORK_STATE(PARENT_READY,		"PRDY", fscache_parent_पढ़ोy);
अटल WORK_STATE(ABORT_INIT,		"ABRT", fscache_पात_initialisation);
अटल WORK_STATE(LOOK_UP_OBJECT,	"LOOK", fscache_look_up_object);
अटल WORK_STATE(CREATE_OBJECT,	"CRTO", fscache_look_up_object);
अटल WORK_STATE(OBJECT_AVAILABLE,	"AVBL", fscache_object_available);
अटल WORK_STATE(JUMPSTART_DEPS,	"JUMP", fscache_jumpstart_dependents);

अटल WORK_STATE(INVALIDATE_OBJECT,	"INVL", fscache_invalidate_object);
अटल WORK_STATE(UPDATE_OBJECT,	"UPDT", fscache_update_object);

अटल WORK_STATE(LOOKUP_FAILURE,	"LCFL", fscache_lookup_failure);
अटल WORK_STATE(KILL_OBJECT,		"KILL", fscache_समाप्त_object);
अटल WORK_STATE(KILL_DEPENDENTS,	"KDEP", fscache_समाप्त_dependents);
अटल WORK_STATE(DROP_OBJECT,		"DROP", fscache_drop_object);
अटल WORK_STATE(OBJECT_DEAD,		"DEAD", fscache_object_dead);

अटल WAIT_STATE(WAIT_FOR_INIT,	"?INI",
		  TRANSIT_TO(INIT_OBJECT,	1 << FSCACHE_OBJECT_EV_NEW_CHILD));

अटल WAIT_STATE(WAIT_FOR_PARENT,	"?PRN",
		  TRANSIT_TO(PARENT_READY,	1 << FSCACHE_OBJECT_EV_PARENT_READY));

अटल WAIT_STATE(WAIT_FOR_CMD,		"?CMD",
		  TRANSIT_TO(INVALIDATE_OBJECT,	1 << FSCACHE_OBJECT_EV_INVALIDATE),
		  TRANSIT_TO(UPDATE_OBJECT,	1 << FSCACHE_OBJECT_EV_UPDATE),
		  TRANSIT_TO(JUMPSTART_DEPS,	1 << FSCACHE_OBJECT_EV_NEW_CHILD));

अटल WAIT_STATE(WAIT_FOR_CLEARANCE,	"?CLR",
		  TRANSIT_TO(KILL_OBJECT,	1 << FSCACHE_OBJECT_EV_CLEARED));

/*
 * Out-of-band event transition tables.  These are क्रम handling unexpected
 * events, such as an I/O error.  If an OOB event occurs, the state machine
 * clears and disables the event and क्रमces a transition to the nominated work
 * state (acurrently executing work states will complete first).
 *
 * In such a situation, object->state remembers the state the machine should
 * have been in/gone to and वापसing NO_TRANSIT वापसs to that.
 */
अटल स्थिर काष्ठा fscache_transition fscache_osm_init_oob[] = अणु
	   TRANSIT_TO(ABORT_INIT,
		      (1 << FSCACHE_OBJECT_EV_ERROR) |
		      (1 << FSCACHE_OBJECT_EV_KILL)),
	   अणु 0, शून्य पूर्ण
पूर्ण;

अटल स्थिर काष्ठा fscache_transition fscache_osm_lookup_oob[] = अणु
	   TRANSIT_TO(LOOKUP_FAILURE,
		      (1 << FSCACHE_OBJECT_EV_ERROR) |
		      (1 << FSCACHE_OBJECT_EV_KILL)),
	   अणु 0, शून्य पूर्ण
पूर्ण;

अटल स्थिर काष्ठा fscache_transition fscache_osm_run_oob[] = अणु
	   TRANSIT_TO(KILL_OBJECT,
		      (1 << FSCACHE_OBJECT_EV_ERROR) |
		      (1 << FSCACHE_OBJECT_EV_KILL)),
	   अणु 0, शून्य पूर्ण
पूर्ण;

अटल पूर्णांक  fscache_get_object(काष्ठा fscache_object *,
			       क्रमागत fscache_obj_ref_trace);
अटल व्योम fscache_put_object(काष्ठा fscache_object *,
			       क्रमागत fscache_obj_ref_trace);
अटल bool fscache_enqueue_dependents(काष्ठा fscache_object *, पूर्णांक);
अटल व्योम fscache_dequeue_object(काष्ठा fscache_object *);
अटल व्योम fscache_update_aux_data(काष्ठा fscache_object *);

/*
 * we need to notअगरy the parent when an op completes that we had outstanding
 * upon it
 */
अटल अंतरभूत व्योम fscache_करोne_parent_op(काष्ठा fscache_object *object)
अणु
	काष्ठा fscache_object *parent = object->parent;

	_enter("OBJ%x {OBJ%x,%x}",
	       object->debug_id, parent->debug_id, parent->n_ops);

	spin_lock_nested(&parent->lock, 1);
	parent->n_obj_ops--;
	parent->n_ops--;
	अगर (parent->n_ops == 0)
		fscache_उठाओ_event(parent, FSCACHE_OBJECT_EV_CLEARED);
	spin_unlock(&parent->lock);
पूर्ण

/*
 * Object state machine dispatcher.
 */
अटल व्योम fscache_object_sm_dispatcher(काष्ठा fscache_object *object)
अणु
	स्थिर काष्ठा fscache_transition *t;
	स्थिर काष्ठा fscache_state *state, *new_state;
	अचिन्हित दीर्घ events, event_mask;
	bool oob;
	पूर्णांक event = -1;

	ASSERT(object != शून्य);

	_enter("{OBJ%x,%s,%lx}",
	       object->debug_id, object->state->name, object->events);

	event_mask = object->event_mask;
restart:
	object->event_mask = 0; /* Mask normal event handling */
	state = object->state;
restart_masked:
	events = object->events;

	/* Handle any out-of-band events (typically an error) */
	अगर (events & object->oob_event_mask) अणु
		_debug("{OBJ%x} oob %lx",
		       object->debug_id, events & object->oob_event_mask);
		oob = true;
		क्रम (t = object->oob_table; t->events; t++) अणु
			अगर (events & t->events) अणु
				state = t->transit_to;
				ASSERT(state->work != शून्य);
				event = fls(events & t->events) - 1;
				__clear_bit(event, &object->oob_event_mask);
				clear_bit(event, &object->events);
				जाओ execute_work_state;
			पूर्ण
		पूर्ण
	पूर्ण
	oob = false;

	/* Wait states are just transition tables */
	अगर (!state->work) अणु
		अगर (events & event_mask) अणु
			क्रम (t = state->transitions; t->events; t++) अणु
				अगर (events & t->events) अणु
					new_state = t->transit_to;
					event = fls(events & t->events) - 1;
					trace_fscache_osm(object, state,
							  true, false, event);
					clear_bit(event, &object->events);
					_debug("{OBJ%x} ev %d: %s -> %s",
					       object->debug_id, event,
					       state->name, new_state->name);
					object->state = state = new_state;
					जाओ execute_work_state;
				पूर्ण
			पूर्ण

			/* The event mask didn't include all the tabled bits */
			BUG();
		पूर्ण
		/* Ranकरोmly woke up */
		जाओ unmask_events;
	पूर्ण

execute_work_state:
	_debug("{OBJ%x} exec %s", object->debug_id, state->name);

	trace_fscache_osm(object, state, false, oob, event);
	new_state = state->work(object, event);
	event = -1;
	अगर (new_state == NO_TRANSIT) अणु
		_debug("{OBJ%x} %s notrans", object->debug_id, state->name);
		अगर (unlikely(state == STATE(OBJECT_DEAD))) अणु
			_leave(" [dead]");
			वापस;
		पूर्ण
		fscache_enqueue_object(object);
		event_mask = object->oob_event_mask;
		जाओ unmask_events;
	पूर्ण

	_debug("{OBJ%x} %s -> %s",
	       object->debug_id, state->name, new_state->name);
	object->state = state = new_state;

	अगर (state->work) अणु
		अगर (unlikely(state == STATE(OBJECT_DEAD))) अणु
			_leave(" [dead]");
			वापस;
		पूर्ण
		जाओ restart_masked;
	पूर्ण

	/* Transited to रुको state */
	event_mask = object->oob_event_mask;
	क्रम (t = state->transitions; t->events; t++)
		event_mask |= t->events;

unmask_events:
	object->event_mask = event_mask;
	smp_mb();
	events = object->events;
	अगर (events & event_mask)
		जाओ restart;
	_leave(" [msk %lx]", event_mask);
पूर्ण

/*
 * execute an object
 */
अटल व्योम fscache_object_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fscache_object *object =
		container_of(work, काष्ठा fscache_object, work);
	अचिन्हित दीर्घ start;

	_enter("{OBJ%x}", object->debug_id);

	start = jअगरfies;
	fscache_object_sm_dispatcher(object);
	fscache_hist(fscache_objs_histogram, start);
	fscache_put_object(object, fscache_obj_put_work);
पूर्ण

/**
 * fscache_object_init - Initialise a cache object description
 * @object: Object description
 * @cookie: Cookie object will be attached to
 * @cache: Cache in which backing object will be found
 *
 * Initialise a cache object description to its basic values.
 *
 * See Documentation/fileप्रणालीs/caching/backend-api.rst क्रम a complete
 * description.
 */
व्योम fscache_object_init(काष्ठा fscache_object *object,
			 काष्ठा fscache_cookie *cookie,
			 काष्ठा fscache_cache *cache)
अणु
	स्थिर काष्ठा fscache_transition *t;

	atomic_inc(&cache->object_count);

	object->state = STATE(WAIT_FOR_INIT);
	object->oob_table = fscache_osm_init_oob;
	object->flags = 1 << FSCACHE_OBJECT_IS_LIVE;
	spin_lock_init(&object->lock);
	INIT_LIST_HEAD(&object->cache_link);
	INIT_HLIST_NODE(&object->cookie_link);
	INIT_WORK(&object->work, fscache_object_work_func);
	INIT_LIST_HEAD(&object->dependents);
	INIT_LIST_HEAD(&object->dep_link);
	INIT_LIST_HEAD(&object->pending_ops);
	object->n_children = 0;
	object->n_ops = object->n_in_progress = object->n_exclusive = 0;
	object->events = 0;
	object->store_limit = 0;
	object->store_limit_l = 0;
	object->cache = cache;
	object->cookie = cookie;
	fscache_cookie_get(cookie, fscache_cookie_get_attach_object);
	object->parent = शून्य;
#अगर_घोषित CONFIG_FSCACHE_OBJECT_LIST
	RB_CLEAR_NODE(&object->objlist_link);
#पूर्ण_अगर

	object->oob_event_mask = 0;
	क्रम (t = object->oob_table; t->events; t++)
		object->oob_event_mask |= t->events;
	object->event_mask = object->oob_event_mask;
	क्रम (t = object->state->transitions; t->events; t++)
		object->event_mask |= t->events;
पूर्ण
EXPORT_SYMBOL(fscache_object_init);

/*
 * Mark the object as no दीर्घer being live, making sure that we synchronise
 * against op submission.
 */
अटल अंतरभूत व्योम fscache_mark_object_dead(काष्ठा fscache_object *object)
अणु
	spin_lock(&object->lock);
	clear_bit(FSCACHE_OBJECT_IS_LIVE, &object->flags);
	spin_unlock(&object->lock);
पूर्ण

/*
 * Abort object initialisation beक्रमe we start it.
 */
अटल स्थिर काष्ठा fscache_state *fscache_पात_initialisation(काष्ठा fscache_object *object,
								पूर्णांक event)
अणु
	_enter("{OBJ%x},%d", object->debug_id, event);

	object->oob_event_mask = 0;
	fscache_dequeue_object(object);
	वापस transit_to(KILL_OBJECT);
पूर्ण

/*
 * initialise an object
 * - check the specअगरied object's parent to see अगर we can make use of it
 *   immediately to करो a creation
 * - we may need to start the process of creating a parent and we need to रुको
 *   क्रम the parent's lookup and creation to complete if it's not there yet
 */
अटल स्थिर काष्ठा fscache_state *fscache_initialise_object(काष्ठा fscache_object *object,
							     पूर्णांक event)
अणु
	काष्ठा fscache_object *parent;
	bool success;

	_enter("{OBJ%x},%d", object->debug_id, event);

	ASSERT(list_empty(&object->dep_link));

	parent = object->parent;
	अगर (!parent) अणु
		_leave(" [no parent]");
		वापस transit_to(DROP_OBJECT);
	पूर्ण

	_debug("parent: %s of:%lx", parent->state->name, parent->flags);

	अगर (fscache_object_is_dying(parent)) अणु
		_leave(" [bad parent]");
		वापस transit_to(DROP_OBJECT);
	पूर्ण

	अगर (fscache_object_is_available(parent)) अणु
		_leave(" [ready]");
		वापस transit_to(PARENT_READY);
	पूर्ण

	_debug("wait");

	spin_lock(&parent->lock);
	fscache_stat(&fscache_n_cop_grab_object);
	success = false;
	अगर (fscache_object_is_live(parent) &&
	    object->cache->ops->grab_object(object, fscache_obj_get_add_to_deps)) अणु
		list_add(&object->dep_link, &parent->dependents);
		success = true;
	पूर्ण
	fscache_stat_d(&fscache_n_cop_grab_object);
	spin_unlock(&parent->lock);
	अगर (!success) अणु
		_leave(" [grab failed]");
		वापस transit_to(DROP_OBJECT);
	पूर्ण

	/* fscache_acquire_non_index_cookie() uses this
	 * to wake the chain up */
	fscache_उठाओ_event(parent, FSCACHE_OBJECT_EV_NEW_CHILD);
	_leave(" [wait]");
	वापस transit_to(WAIT_FOR_PARENT);
पूर्ण

/*
 * Once the parent object is पढ़ोy, we should kick off our lookup op.
 */
अटल स्थिर काष्ठा fscache_state *fscache_parent_पढ़ोy(काष्ठा fscache_object *object,
							पूर्णांक event)
अणु
	काष्ठा fscache_object *parent = object->parent;

	_enter("{OBJ%x},%d", object->debug_id, event);

	ASSERT(parent != शून्य);

	spin_lock(&parent->lock);
	parent->n_ops++;
	parent->n_obj_ops++;
	object->lookup_jअगर = jअगरfies;
	spin_unlock(&parent->lock);

	_leave("");
	वापस transit_to(LOOK_UP_OBJECT);
पूर्ण

/*
 * look an object up in the cache from which it was allocated
 * - we hold an "access lock" on the parent object, so the parent object cannot
 *   be withdrawn by either party till we've finished
 */
अटल स्थिर काष्ठा fscache_state *fscache_look_up_object(काष्ठा fscache_object *object,
							  पूर्णांक event)
अणु
	काष्ठा fscache_cookie *cookie = object->cookie;
	काष्ठा fscache_object *parent = object->parent;
	पूर्णांक ret;

	_enter("{OBJ%x},%d", object->debug_id, event);

	object->oob_table = fscache_osm_lookup_oob;

	ASSERT(parent != शून्य);
	ASSERTCMP(parent->n_ops, >, 0);
	ASSERTCMP(parent->n_obj_ops, >, 0);

	/* make sure the parent is still available */
	ASSERT(fscache_object_is_available(parent));

	अगर (fscache_object_is_dying(parent) ||
	    test_bit(FSCACHE_IOERROR, &object->cache->flags) ||
	    !fscache_use_cookie(object)) अणु
		_leave(" [unavailable]");
		वापस transit_to(LOOKUP_FAILURE);
	पूर्ण

	_debug("LOOKUP \"%s\" in \"%s\"",
	       cookie->def->name, object->cache->tag->name);

	fscache_stat(&fscache_n_object_lookups);
	fscache_stat(&fscache_n_cop_lookup_object);
	ret = object->cache->ops->lookup_object(object);
	fscache_stat_d(&fscache_n_cop_lookup_object);

	fscache_unuse_cookie(object);

	अगर (ret == -ETIMEDOUT) अणु
		/* probably stuck behind another object, so move this one to
		 * the back of the queue */
		fscache_stat(&fscache_n_object_lookups_समयd_out);
		_leave(" [timeout]");
		वापस NO_TRANSIT;
	पूर्ण

	अगर (ret < 0) अणु
		_leave(" [error]");
		वापस transit_to(LOOKUP_FAILURE);
	पूर्ण

	_leave(" [ok]");
	वापस transit_to(OBJECT_AVAILABLE);
पूर्ण

/**
 * fscache_object_lookup_negative - Note negative cookie lookup
 * @object: Object poपूर्णांकing to cookie to mark
 *
 * Note negative lookup, permitting those रुकोing to पढ़ो data from an alपढ़ोy
 * existing backing object to जारी as there's no data क्रम them to पढ़ो.
 */
व्योम fscache_object_lookup_negative(काष्ठा fscache_object *object)
अणु
	काष्ठा fscache_cookie *cookie = object->cookie;

	_enter("{OBJ%x,%s}", object->debug_id, object->state->name);

	अगर (!test_and_set_bit(FSCACHE_OBJECT_IS_LOOKED_UP, &object->flags)) अणु
		fscache_stat(&fscache_n_object_lookups_negative);

		/* Allow ग_लिखो requests to begin stacking up and पढ़ो requests to begin
		 * वापसing ENODATA.
		 */
		set_bit(FSCACHE_COOKIE_NO_DATA_YET, &cookie->flags);
		clear_bit(FSCACHE_COOKIE_UNAVAILABLE, &cookie->flags);

		_debug("wake up lookup %p", &cookie->flags);
		clear_bit_unlock(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags);
		wake_up_bit(&cookie->flags, FSCACHE_COOKIE_LOOKING_UP);
	पूर्ण
	_leave("");
पूर्ण
EXPORT_SYMBOL(fscache_object_lookup_negative);

/**
 * fscache_obtained_object - Note successful object lookup or creation
 * @object: Object poपूर्णांकing to cookie to mark
 *
 * Note successful lookup and/or creation, permitting those रुकोing to ग_लिखो
 * data to a backing object to जारी.
 *
 * Note that after calling this, an object's cookie may be relinquished by the
 * netfs, and so must be accessed with object lock held.
 */
व्योम fscache_obtained_object(काष्ठा fscache_object *object)
अणु
	काष्ठा fscache_cookie *cookie = object->cookie;

	_enter("{OBJ%x,%s}", object->debug_id, object->state->name);

	/* अगर we were still looking up, then we must have a positive lookup
	 * result, in which हाल there may be data available */
	अगर (!test_and_set_bit(FSCACHE_OBJECT_IS_LOOKED_UP, &object->flags)) अणु
		fscache_stat(&fscache_n_object_lookups_positive);

		/* We करो (presumably) have data */
		clear_bit_unlock(FSCACHE_COOKIE_NO_DATA_YET, &cookie->flags);
		clear_bit(FSCACHE_COOKIE_UNAVAILABLE, &cookie->flags);

		/* Allow ग_लिखो requests to begin stacking up and पढ़ो requests
		 * to begin shovelling data.
		 */
		clear_bit_unlock(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags);
		wake_up_bit(&cookie->flags, FSCACHE_COOKIE_LOOKING_UP);
	पूर्ण अन्यथा अणु
		fscache_stat(&fscache_n_object_created);
	पूर्ण

	set_bit(FSCACHE_OBJECT_IS_AVAILABLE, &object->flags);
	_leave("");
पूर्ण
EXPORT_SYMBOL(fscache_obtained_object);

/*
 * handle an object that has just become available
 */
अटल स्थिर काष्ठा fscache_state *fscache_object_available(काष्ठा fscache_object *object,
							    पूर्णांक event)
अणु
	_enter("{OBJ%x},%d", object->debug_id, event);

	object->oob_table = fscache_osm_run_oob;

	spin_lock(&object->lock);

	fscache_करोne_parent_op(object);
	अगर (object->n_in_progress == 0) अणु
		अगर (object->n_ops > 0) अणु
			ASSERTCMP(object->n_ops, >=, object->n_obj_ops);
			fscache_start_operations(object);
		पूर्ण अन्यथा अणु
			ASSERT(list_empty(&object->pending_ops));
		पूर्ण
	पूर्ण
	spin_unlock(&object->lock);

	fscache_stat(&fscache_n_cop_lookup_complete);
	object->cache->ops->lookup_complete(object);
	fscache_stat_d(&fscache_n_cop_lookup_complete);

	fscache_hist(fscache_obj_instantiate_histogram, object->lookup_jअगर);
	fscache_stat(&fscache_n_object_avail);

	_leave("");
	वापस transit_to(JUMPSTART_DEPS);
पूर्ण

/*
 * Wake up this object's dependent objects now that we've become available.
 */
अटल स्थिर काष्ठा fscache_state *fscache_jumpstart_dependents(काष्ठा fscache_object *object,
								पूर्णांक event)
अणु
	_enter("{OBJ%x},%d", object->debug_id, event);

	अगर (!fscache_enqueue_dependents(object, FSCACHE_OBJECT_EV_PARENT_READY))
		वापस NO_TRANSIT; /* Not finished; requeue */
	वापस transit_to(WAIT_FOR_CMD);
पूर्ण

/*
 * Handle lookup or creation failute.
 */
अटल स्थिर काष्ठा fscache_state *fscache_lookup_failure(काष्ठा fscache_object *object,
							  पूर्णांक event)
अणु
	काष्ठा fscache_cookie *cookie;

	_enter("{OBJ%x},%d", object->debug_id, event);

	object->oob_event_mask = 0;

	fscache_stat(&fscache_n_cop_lookup_complete);
	object->cache->ops->lookup_complete(object);
	fscache_stat_d(&fscache_n_cop_lookup_complete);

	set_bit(FSCACHE_OBJECT_KILLED_BY_CACHE, &object->flags);

	cookie = object->cookie;
	set_bit(FSCACHE_COOKIE_UNAVAILABLE, &cookie->flags);
	अगर (test_and_clear_bit(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags))
		wake_up_bit(&cookie->flags, FSCACHE_COOKIE_LOOKING_UP);

	fscache_करोne_parent_op(object);
	वापस transit_to(KILL_OBJECT);
पूर्ण

/*
 * Wait क्रम completion of all active operations on this object and the death of
 * all child objects of this object.
 */
अटल स्थिर काष्ठा fscache_state *fscache_समाप्त_object(काष्ठा fscache_object *object,
						       पूर्णांक event)
अणु
	_enter("{OBJ%x,%d,%d},%d",
	       object->debug_id, object->n_ops, object->n_children, event);

	fscache_mark_object_dead(object);
	object->oob_event_mask = 0;

	अगर (test_bit(FSCACHE_OBJECT_RETIRED, &object->flags)) अणु
		/* Reject any new पढ़ो/ग_लिखो ops and पात any that are pending. */
		clear_bit(FSCACHE_OBJECT_PENDING_WRITE, &object->flags);
		fscache_cancel_all_ops(object);
	पूर्ण

	अगर (list_empty(&object->dependents) &&
	    object->n_ops == 0 &&
	    object->n_children == 0)
		वापस transit_to(DROP_OBJECT);

	अगर (object->n_in_progress == 0) अणु
		spin_lock(&object->lock);
		अगर (object->n_ops > 0 && object->n_in_progress == 0)
			fscache_start_operations(object);
		spin_unlock(&object->lock);
	पूर्ण

	अगर (!list_empty(&object->dependents))
		वापस transit_to(KILL_DEPENDENTS);

	वापस transit_to(WAIT_FOR_CLEARANCE);
पूर्ण

/*
 * Kill dependent objects.
 */
अटल स्थिर काष्ठा fscache_state *fscache_समाप्त_dependents(काष्ठा fscache_object *object,
							   पूर्णांक event)
अणु
	_enter("{OBJ%x},%d", object->debug_id, event);

	अगर (!fscache_enqueue_dependents(object, FSCACHE_OBJECT_EV_KILL))
		वापस NO_TRANSIT; /* Not finished */
	वापस transit_to(WAIT_FOR_CLEARANCE);
पूर्ण

/*
 * Drop an object's attachments
 */
अटल स्थिर काष्ठा fscache_state *fscache_drop_object(काष्ठा fscache_object *object,
						       पूर्णांक event)
अणु
	काष्ठा fscache_object *parent = object->parent;
	काष्ठा fscache_cookie *cookie = object->cookie;
	काष्ठा fscache_cache *cache = object->cache;
	bool awaken = false;

	_enter("{OBJ%x,%d},%d", object->debug_id, object->n_children, event);

	ASSERT(cookie != शून्य);
	ASSERT(!hlist_unhashed(&object->cookie_link));

	अगर (test_bit(FSCACHE_COOKIE_AUX_UPDATED, &cookie->flags)) अणु
		_debug("final update");
		fscache_update_aux_data(object);
	पूर्ण

	/* Make sure the cookie no दीर्घer poपूर्णांकs here and that the netfs isn't
	 * रुकोing क्रम us.
	 */
	spin_lock(&cookie->lock);
	hlist_del_init(&object->cookie_link);
	अगर (hlist_empty(&cookie->backing_objects) &&
	    test_and_clear_bit(FSCACHE_COOKIE_INVALIDATING, &cookie->flags))
		awaken = true;
	spin_unlock(&cookie->lock);

	अगर (awaken)
		wake_up_bit(&cookie->flags, FSCACHE_COOKIE_INVALIDATING);
	अगर (test_and_clear_bit(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags))
		wake_up_bit(&cookie->flags, FSCACHE_COOKIE_LOOKING_UP);


	/* Prevent a race with our last child, which has to संकेत EV_CLEARED
	 * beक्रमe dropping our spinlock.
	 */
	spin_lock(&object->lock);
	spin_unlock(&object->lock);

	/* Discard from the cache's collection of objects */
	spin_lock(&cache->object_list_lock);
	list_del_init(&object->cache_link);
	spin_unlock(&cache->object_list_lock);

	fscache_stat(&fscache_n_cop_drop_object);
	cache->ops->drop_object(object);
	fscache_stat_d(&fscache_n_cop_drop_object);

	/* The parent object wants to know when all it dependents have gone */
	अगर (parent) अणु
		_debug("release parent OBJ%x {%d}",
		       parent->debug_id, parent->n_children);

		spin_lock(&parent->lock);
		parent->n_children--;
		अगर (parent->n_children == 0)
			fscache_उठाओ_event(parent, FSCACHE_OBJECT_EV_CLEARED);
		spin_unlock(&parent->lock);
		object->parent = शून्य;
	पूर्ण

	/* this just shअगरts the object release to the work processor */
	fscache_put_object(object, fscache_obj_put_drop_obj);
	fscache_stat(&fscache_n_object_dead);

	_leave("");
	वापस transit_to(OBJECT_DEAD);
पूर्ण

/*
 * get a ref on an object
 */
अटल पूर्णांक fscache_get_object(काष्ठा fscache_object *object,
			      क्रमागत fscache_obj_ref_trace why)
अणु
	पूर्णांक ret;

	fscache_stat(&fscache_n_cop_grab_object);
	ret = object->cache->ops->grab_object(object, why) ? 0 : -EAGAIN;
	fscache_stat_d(&fscache_n_cop_grab_object);
	वापस ret;
पूर्ण

/*
 * Discard a ref on an object
 */
अटल व्योम fscache_put_object(काष्ठा fscache_object *object,
			       क्रमागत fscache_obj_ref_trace why)
अणु
	fscache_stat(&fscache_n_cop_put_object);
	object->cache->ops->put_object(object, why);
	fscache_stat_d(&fscache_n_cop_put_object);
पूर्ण

/**
 * fscache_object_destroy - Note that a cache object is about to be destroyed
 * @object: The object to be destroyed
 *
 * Note the imminent deकाष्ठाion and deallocation of a cache object record.
 */
व्योम fscache_object_destroy(काष्ठा fscache_object *object)
अणु
	fscache_objlist_हटाओ(object);

	/* We can get rid of the cookie now */
	fscache_cookie_put(object->cookie, fscache_cookie_put_object);
	object->cookie = शून्य;
पूर्ण
EXPORT_SYMBOL(fscache_object_destroy);

/*
 * enqueue an object क्रम metadata-type processing
 */
व्योम fscache_enqueue_object(काष्ठा fscache_object *object)
अणु
	_enter("{OBJ%x}", object->debug_id);

	अगर (fscache_get_object(object, fscache_obj_get_queue) >= 0) अणु
		रुको_queue_head_t *cong_wq =
			&get_cpu_var(fscache_object_cong_रुको);

		अगर (queue_work(fscache_object_wq, &object->work)) अणु
			अगर (fscache_object_congested())
				wake_up(cong_wq);
		पूर्ण अन्यथा
			fscache_put_object(object, fscache_obj_put_queue);

		put_cpu_var(fscache_object_cong_रुको);
	पूर्ण
पूर्ण

/**
 * fscache_object_sleep_till_congested - Sleep until object wq is congested
 * @समयoutp: Scheduler sleep समयout
 *
 * Allow an object handler to sleep until the object workqueue is congested.
 *
 * The caller must set up a wake up event beक्रमe calling this and must have set
 * the appropriate sleep mode (such as TASK_UNINTERRUPTIBLE) and tested its own
 * condition beक्रमe calling this function as no test is made here.
 *
 * %true is वापसed अगर the object wq is congested, %false otherwise.
 */
bool fscache_object_sleep_till_congested(चिन्हित दीर्घ *समयoutp)
अणु
	रुको_queue_head_t *cong_wq = this_cpu_ptr(&fscache_object_cong_रुको);
	DEFINE_WAIT(रुको);

	अगर (fscache_object_congested())
		वापस true;

	add_रुको_queue_exclusive(cong_wq, &रुको);
	अगर (!fscache_object_congested())
		*समयoutp = schedule_समयout(*समयoutp);
	finish_रुको(cong_wq, &रुको);

	वापस fscache_object_congested();
पूर्ण
EXPORT_SYMBOL_GPL(fscache_object_sleep_till_congested);

/*
 * Enqueue the dependents of an object क्रम metadata-type processing.
 *
 * If we करोn't manage to finish the list beक्रमe the scheduler wants to run
 * again then वापस false immediately.  We वापस true अगर the list was
 * cleared.
 */
अटल bool fscache_enqueue_dependents(काष्ठा fscache_object *object, पूर्णांक event)
अणु
	काष्ठा fscache_object *dep;
	bool ret = true;

	_enter("{OBJ%x}", object->debug_id);

	अगर (list_empty(&object->dependents))
		वापस true;

	spin_lock(&object->lock);

	जबतक (!list_empty(&object->dependents)) अणु
		dep = list_entry(object->dependents.next,
				 काष्ठा fscache_object, dep_link);
		list_del_init(&dep->dep_link);

		fscache_उठाओ_event(dep, event);
		fscache_put_object(dep, fscache_obj_put_enq_dep);

		अगर (!list_empty(&object->dependents) && need_resched()) अणु
			ret = false;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&object->lock);
	वापस ret;
पूर्ण

/*
 * हटाओ an object from whatever queue it's रुकोing on
 */
अटल व्योम fscache_dequeue_object(काष्ठा fscache_object *object)
अणु
	_enter("{OBJ%x}", object->debug_id);

	अगर (!list_empty(&object->dep_link)) अणु
		spin_lock(&object->parent->lock);
		list_del_init(&object->dep_link);
		spin_unlock(&object->parent->lock);
	पूर्ण

	_leave("");
पूर्ण

/**
 * fscache_check_aux - Ask the netfs whether an object on disk is still valid
 * @object: The object to ask about
 * @data: The auxiliary data क्रम the object
 * @datalen: The size of the auxiliary data
 *
 * This function consults the netfs about the coherency state of an object.
 * The caller must be holding a ref on cookie->n_active (held by
 * fscache_look_up_object() on behalf of the cache backend during object lookup
 * and creation).
 */
क्रमागत fscache_checkaux fscache_check_aux(काष्ठा fscache_object *object,
					स्थिर व्योम *data, uपूर्णांक16_t datalen,
					loff_t object_size)
अणु
	क्रमागत fscache_checkaux result;

	अगर (!object->cookie->def->check_aux) अणु
		fscache_stat(&fscache_n_checkaux_none);
		वापस FSCACHE_CHECKAUX_OKAY;
	पूर्ण

	result = object->cookie->def->check_aux(object->cookie->netfs_data,
						data, datalen, object_size);
	चयन (result) अणु
		/* entry okay as is */
	हाल FSCACHE_CHECKAUX_OKAY:
		fscache_stat(&fscache_n_checkaux_okay);
		अवरोध;

		/* entry requires update */
	हाल FSCACHE_CHECKAUX_NEEDS_UPDATE:
		fscache_stat(&fscache_n_checkaux_update);
		अवरोध;

		/* entry requires deletion */
	हाल FSCACHE_CHECKAUX_OBSOLETE:
		fscache_stat(&fscache_n_checkaux_obsolete);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	वापस result;
पूर्ण
EXPORT_SYMBOL(fscache_check_aux);

/*
 * Asynchronously invalidate an object.
 */
अटल स्थिर काष्ठा fscache_state *_fscache_invalidate_object(काष्ठा fscache_object *object,
							      पूर्णांक event)
अणु
	काष्ठा fscache_operation *op;
	काष्ठा fscache_cookie *cookie = object->cookie;

	_enter("{OBJ%x},%d", object->debug_id, event);

	/* We're going to need the cookie.  If the cookie is not available then
	 * retire the object instead.
	 */
	अगर (!fscache_use_cookie(object)) अणु
		ASSERT(radix_tree_empty(&object->cookie->stores));
		set_bit(FSCACHE_OBJECT_RETIRED, &object->flags);
		_leave(" [no cookie]");
		वापस transit_to(KILL_OBJECT);
	पूर्ण

	/* Reject any new पढ़ो/ग_लिखो ops and पात any that are pending. */
	fscache_invalidate_ग_लिखोs(cookie);
	clear_bit(FSCACHE_OBJECT_PENDING_WRITE, &object->flags);
	fscache_cancel_all_ops(object);

	/* Now we have to रुको क्रम in-progress पढ़ोs and ग_लिखोs */
	op = kzalloc(माप(*op), GFP_KERNEL);
	अगर (!op)
		जाओ nomem;

	fscache_operation_init(cookie, op, object->cache->ops->invalidate_object,
			       शून्य, शून्य);
	op->flags = FSCACHE_OP_ASYNC |
		(1 << FSCACHE_OP_EXCLUSIVE) |
		(1 << FSCACHE_OP_UNUSE_COOKIE);
	trace_fscache_page_op(cookie, शून्य, op, fscache_page_op_invalidate);

	spin_lock(&cookie->lock);
	अगर (fscache_submit_exclusive_op(object, op) < 0)
		जाओ submit_op_failed;
	spin_unlock(&cookie->lock);
	fscache_put_operation(op);

	/* Once we've completed the invalidation, we know there will be no data
	 * stored in the cache and thus we can reinstate the data-check-skip
	 * optimisation.
	 */
	set_bit(FSCACHE_COOKIE_NO_DATA_YET, &cookie->flags);

	/* We can allow पढ़ो and ग_लिखो requests to come in once again.  They'll
	 * queue up behind our exclusive invalidation operation.
	 */
	अगर (test_and_clear_bit(FSCACHE_COOKIE_INVALIDATING, &cookie->flags))
		wake_up_bit(&cookie->flags, FSCACHE_COOKIE_INVALIDATING);
	_leave(" [ok]");
	वापस transit_to(UPDATE_OBJECT);

nomem:
	fscache_mark_object_dead(object);
	fscache_unuse_cookie(object);
	_leave(" [ENOMEM]");
	वापस transit_to(KILL_OBJECT);

submit_op_failed:
	fscache_mark_object_dead(object);
	spin_unlock(&cookie->lock);
	fscache_unuse_cookie(object);
	kमुक्त(op);
	_leave(" [EIO]");
	वापस transit_to(KILL_OBJECT);
पूर्ण

अटल स्थिर काष्ठा fscache_state *fscache_invalidate_object(काष्ठा fscache_object *object,
							     पूर्णांक event)
अणु
	स्थिर काष्ठा fscache_state *s;

	fscache_stat(&fscache_n_invalidates_run);
	fscache_stat(&fscache_n_cop_invalidate_object);
	s = _fscache_invalidate_object(object, event);
	fscache_stat_d(&fscache_n_cop_invalidate_object);
	वापस s;
पूर्ण

/*
 * Update auxiliary data.
 */
अटल व्योम fscache_update_aux_data(काष्ठा fscache_object *object)
अणु
	fscache_stat(&fscache_n_updates_run);
	fscache_stat(&fscache_n_cop_update_object);
	object->cache->ops->update_object(object);
	fscache_stat_d(&fscache_n_cop_update_object);
पूर्ण

/*
 * Asynchronously update an object.
 */
अटल स्थिर काष्ठा fscache_state *fscache_update_object(काष्ठा fscache_object *object,
							 पूर्णांक event)
अणु
	_enter("{OBJ%x},%d", object->debug_id, event);

	fscache_update_aux_data(object);

	_leave("");
	वापस transit_to(WAIT_FOR_CMD);
पूर्ण

/**
 * fscache_object_retrying_stale - Note retrying stale object
 * @object: The object that will be retried
 *
 * Note that an object lookup found an on-disk object that was adjudged to be
 * stale and has been deleted.  The lookup will be retried.
 */
व्योम fscache_object_retrying_stale(काष्ठा fscache_object *object)
अणु
	fscache_stat(&fscache_n_cache_no_space_reject);
पूर्ण
EXPORT_SYMBOL(fscache_object_retrying_stale);

/**
 * fscache_object_mark_समाप्तed - Note that an object was समाप्तed
 * @object: The object that was culled
 * @why: The reason the object was समाप्तed.
 *
 * Note that an object was समाप्तed.  Returns true अगर the object was
 * alपढ़ोy marked समाप्तed, false अगर it wasn't.
 */
व्योम fscache_object_mark_समाप्तed(काष्ठा fscache_object *object,
				क्रमागत fscache_why_object_समाप्तed why)
अणु
	अगर (test_and_set_bit(FSCACHE_OBJECT_KILLED_BY_CACHE, &object->flags)) अणु
		pr_err("Error: Object already killed by cache [%s]\n",
		       object->cache->identअगरier);
		वापस;
	पूर्ण

	चयन (why) अणु
	हाल FSCACHE_OBJECT_NO_SPACE:
		fscache_stat(&fscache_n_cache_no_space_reject);
		अवरोध;
	हाल FSCACHE_OBJECT_IS_STALE:
		fscache_stat(&fscache_n_cache_stale_objects);
		अवरोध;
	हाल FSCACHE_OBJECT_WAS_RETIRED:
		fscache_stat(&fscache_n_cache_retired_objects);
		अवरोध;
	हाल FSCACHE_OBJECT_WAS_CULLED:
		fscache_stat(&fscache_n_cache_culled_objects);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fscache_object_mark_समाप्तed);

/*
 * The object is dead.  We can get here अगर an object माला_लो queued by an event
 * that would lead to its death (such as EV_KILL) when the dispatcher is
 * alपढ़ोy running (and so can be requeued) but hasn't yet cleared the event
 * mask.
 */
अटल स्थिर काष्ठा fscache_state *fscache_object_dead(काष्ठा fscache_object *object,
						       पूर्णांक event)
अणु
	अगर (!test_and_set_bit(FSCACHE_OBJECT_RUN_AFTER_DEAD,
			      &object->flags))
		वापस NO_TRANSIT;

	WARN(true, "FS-Cache object redispatched after death");
	वापस NO_TRANSIT;
पूर्ण
