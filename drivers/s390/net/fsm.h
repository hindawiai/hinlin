<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FSM_H_
#घोषणा _FSM_H_

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/समय.स>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/atomic.h>

/**
 * Define this to get debugging messages.
 */
#घोषणा FSM_DEBUG         0

/**
 * Define this to get debugging massages क्रम
 * समयr handling.
 */
#घोषणा FSM_TIMER_DEBUG   0

/**
 * Define these to record a history of
 * Events/Statechanges and prपूर्णांक it अगर a
 * action_function is not found.
 */
#घोषणा FSM_DEBUG_HISTORY 0
#घोषणा FSM_HISTORY_SIZE  40

काष्ठा fsm_instance_t;

/**
 * Definition of an action function, called by a FSM
 */
प्रकार व्योम (*fsm_function_t)(काष्ठा fsm_instance_t *, पूर्णांक, व्योम *);

/**
 * Internal jump table क्रम a FSM
 */
प्रकार काष्ठा अणु
	fsm_function_t *jumpmatrix;
	पूर्णांक nr_events;
	पूर्णांक nr_states;
	स्थिर अक्षर **event_names;
	स्थिर अक्षर **state_names;
पूर्ण fsm;

#अगर FSM_DEBUG_HISTORY
/**
 * Element of State/Event history used क्रम debugging.
 */
प्रकार काष्ठा अणु
	पूर्णांक state;
	पूर्णांक event;
पूर्ण fsm_history;
#पूर्ण_अगर

/**
 * Representation of a FSM
 */
प्रकार काष्ठा fsm_instance_t अणु
	fsm *f;
	atomic_t state;
	अक्षर name[16];
	व्योम *userdata;
	पूर्णांक userपूर्णांक;
	रुको_queue_head_t रुको_q;
#अगर FSM_DEBUG_HISTORY
	पूर्णांक         history_index;
	पूर्णांक         history_size;
	fsm_history history[FSM_HISTORY_SIZE];
#पूर्ण_अगर
पूर्ण fsm_instance;

/**
 * Description of a state-event combination
 */
प्रकार काष्ठा अणु
	पूर्णांक cond_state;
	पूर्णांक cond_event;
	fsm_function_t function;
पूर्ण fsm_node;

/**
 * Description of a FSM Timer.
 */
प्रकार काष्ठा अणु
	fsm_instance *fi;
	काष्ठा समयr_list tl;
	पूर्णांक expire_event;
	व्योम *event_arg;
पूर्ण fsm_समयr;

/**
 * Creates an FSM
 *
 * @param name        Name of this instance क्रम logging purposes.
 * @param state_names An array of names क्रम all states क्रम logging purposes.
 * @param event_names An array of names क्रम all events क्रम logging purposes.
 * @param nr_states   Number of states क्रम this instance.
 * @param nr_events   Number of events क्रम this instance.
 * @param पंचांगpl        An array of fsm_nodes, describing this FSM.
 * @param पंचांगpl_len    Length of the describing array.
 * @param order       Parameter क्रम allocation of the FSM data काष्ठाs.
 */
बाह्य fsm_instance *
init_fsm(अक्षर *name, स्थिर अक्षर **state_names,
	 स्थिर अक्षर **event_names,
	 पूर्णांक nr_states, पूर्णांक nr_events, स्थिर fsm_node *पंचांगpl,
	 पूर्णांक पंचांगpl_len, gfp_t order);

/**
 * Releases an FSM
 *
 * @param fi Poपूर्णांकer to an FSM, previously created with init_fsm.
 */
बाह्य व्योम kमुक्त_fsm(fsm_instance *fi);

#अगर FSM_DEBUG_HISTORY
बाह्य व्योम
fsm_prपूर्णांक_history(fsm_instance *fi);

बाह्य व्योम
fsm_record_history(fsm_instance *fi, पूर्णांक state, पूर्णांक event);
#पूर्ण_अगर

/**
 * Emits an event to a FSM.
 * If an action function is defined क्रम the current state/event combination,
 * this function is called.
 *
 * @param fi    Poपूर्णांकer to FSM which should receive the event.
 * @param event The event करो be delivered.
 * @param arg   A generic argument, handed to the action function.
 *
 * @वापस      0  on success,
 *              1  अगर current state or event is out of range
 *              !0 अगर state and event in range, but no action defined.
 */
अटल अंतरभूत पूर्णांक
fsm_event(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	fsm_function_t r;
	पूर्णांक state = atomic_पढ़ो(&fi->state);

	अगर ((state >= fi->f->nr_states) ||
	    (event >= fi->f->nr_events)       ) अणु
		prपूर्णांकk(KERN_ERR "fsm(%s): Invalid state st(%ld/%ld) ev(%d/%ld)\n",
			fi->name, (दीर्घ)state,(दीर्घ)fi->f->nr_states, event,
			(दीर्घ)fi->f->nr_events);
#अगर FSM_DEBUG_HISTORY
		fsm_prपूर्णांक_history(fi);
#पूर्ण_अगर
		वापस 1;
	पूर्ण
	r = fi->f->jumpmatrix[fi->f->nr_states * event + state];
	अगर (r) अणु
#अगर FSM_DEBUG
		prपूर्णांकk(KERN_DEBUG "fsm(%s): state %s event %s\n",
		       fi->name, fi->f->state_names[state],
		       fi->f->event_names[event]);
#पूर्ण_अगर
#अगर FSM_DEBUG_HISTORY
		fsm_record_history(fi, state, event);
#पूर्ण_अगर
		r(fi, event, arg);
		वापस 0;
	पूर्ण अन्यथा अणु
#अगर FSM_DEBUG || FSM_DEBUG_HISTORY
		prपूर्णांकk(KERN_DEBUG "fsm(%s): no function for event %s in state %s\n",
		       fi->name, fi->f->event_names[event],
		       fi->f->state_names[state]);
#पूर्ण_अगर
#अगर FSM_DEBUG_HISTORY
		fsm_prपूर्णांक_history(fi);
#पूर्ण_अगर
		वापस !0;
	पूर्ण
पूर्ण

/**
 * Modअगरies the state of an FSM.
 * This करोes <em>not</em> trigger an event or calls an action function.
 *
 * @param fi    Poपूर्णांकer to FSM
 * @param state The new state क्रम this FSM.
 */
अटल अंतरभूत व्योम
fsm_newstate(fsm_instance *fi, पूर्णांक newstate)
अणु
	atomic_set(&fi->state,newstate);
#अगर FSM_DEBUG_HISTORY
	fsm_record_history(fi, newstate, -1);
#पूर्ण_अगर
#अगर FSM_DEBUG
	prपूर्णांकk(KERN_DEBUG "fsm(%s): New state %s\n", fi->name,
		fi->f->state_names[newstate]);
#पूर्ण_अगर
	wake_up(&fi->रुको_q);
पूर्ण

/**
 * Retrieves the state of an FSM
 *
 * @param fi Poपूर्णांकer to FSM
 *
 * @वापस The current state of the FSM.
 */
अटल अंतरभूत पूर्णांक
fsm_माला_लोtate(fsm_instance *fi)
अणु
	वापस atomic_पढ़ो(&fi->state);
पूर्ण

/**
 * Retrieves the name of the state of an FSM
 *
 * @param fi Poपूर्णांकer to FSM
 *
 * @वापस The current state of the FSM in a human पढ़ोable क्रमm.
 */
बाह्य स्थिर अक्षर *fsm_माला_लोtate_str(fsm_instance *fi);

/**
 * Initializes a समयr क्रम an FSM.
 * This prepares an fsm_समयr क्रम usage with fsm_addसमयr.
 *
 * @param fi    Poपूर्णांकer to FSM
 * @param समयr The समयr to be initialized.
 */
बाह्य व्योम fsm_समय_रखोr(fsm_instance *fi, fsm_समयr *);

/**
 * Clears a pending समयr of an FSM instance.
 *
 * @param समयr The समयr to clear.
 */
बाह्य व्योम fsm_delसमयr(fsm_समयr *समयr);

/**
 * Adds and starts a समयr to an FSM instance.
 *
 * @param समयr    The समयr to be added. The field fi of that समयr
 *                 must have been set to poपूर्णांक to the instance.
 * @param millisec Duration, after which the समयr should expire.
 * @param event    Event, to trigger अगर समयr expires.
 * @param arg      Generic argument, provided to expiry function.
 *
 * @वापस         0 on success, -1 अगर समयr is alपढ़ोy active.
 */
बाह्य पूर्णांक fsm_addसमयr(fsm_समयr *समयr, पूर्णांक millisec, पूर्णांक event, व्योम *arg);

/**
 * Modअगरies a समयr of an FSM.
 *
 * @param समयr    The समयr to modअगरy.
 * @param millisec Duration, after which the समयr should expire.
 * @param event    Event, to trigger अगर समयr expires.
 * @param arg      Generic argument, provided to expiry function.
 */
बाह्य व्योम fsm_modसमयr(fsm_समयr *समयr, पूर्णांक millisec, पूर्णांक event, व्योम *arg);

#पूर्ण_अगर /* _FSM_H_ */
