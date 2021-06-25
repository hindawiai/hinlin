<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * A generic FSM based on fsm used in isdn4linux
 *
 */

#समावेश "fsm.h"
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>

MODULE_AUTHOR("(C) 2000 IBM Corp. by Fritz Elfert (felfert@millenux.com)");
MODULE_DESCRIPTION("Finite state machine helper functions");
MODULE_LICENSE("GPL");

fsm_instance *
init_fsm(अक्षर *name, स्थिर अक्षर **state_names, स्थिर अक्षर **event_names, पूर्णांक nr_states,
		पूर्णांक nr_events, स्थिर fsm_node *पंचांगpl, पूर्णांक पंचांगpl_len, gfp_t order)
अणु
	पूर्णांक i;
	fsm_instance *this;
	fsm_function_t *m;
	fsm *f;

	this = kzalloc(माप(fsm_instance), order);
	अगर (this == शून्य) अणु
		prपूर्णांकk(KERN_WARNING
			"fsm(%s): init_fsm: Couldn't alloc instance\n", name);
		वापस शून्य;
	पूर्ण
	strlcpy(this->name, name, माप(this->name));
	init_रुकोqueue_head(&this->रुको_q);

	f = kzalloc(माप(fsm), order);
	अगर (f == शून्य) अणु
		prपूर्णांकk(KERN_WARNING
			"fsm(%s): init_fsm: Couldn't alloc fsm\n", name);
		kमुक्त_fsm(this);
		वापस शून्य;
	पूर्ण
	f->nr_events = nr_events;
	f->nr_states = nr_states;
	f->event_names = event_names;
	f->state_names = state_names;
	this->f = f;

	m = kसुस्मृति(nr_states*nr_events, माप(fsm_function_t), order);
	अगर (m == शून्य) अणु
		prपूर्णांकk(KERN_WARNING
			"fsm(%s): init_fsm: Couldn't alloc jumptable\n", name);
		kमुक्त_fsm(this);
		वापस शून्य;
	पूर्ण
	f->jumpmatrix = m;

	क्रम (i = 0; i < पंचांगpl_len; i++) अणु
		अगर ((पंचांगpl[i].cond_state >= nr_states) ||
		    (पंचांगpl[i].cond_event >= nr_events)   ) अणु
			prपूर्णांकk(KERN_ERR
				"fsm(%s): init_fsm: Bad template l=%d st(%ld/%ld) ev(%ld/%ld)\n",
				name, i, (दीर्घ)पंचांगpl[i].cond_state, (दीर्घ)f->nr_states,
				(दीर्घ)पंचांगpl[i].cond_event, (दीर्घ)f->nr_events);
			kमुक्त_fsm(this);
			वापस शून्य;
		पूर्ण अन्यथा
			m[nr_states * पंचांगpl[i].cond_event + पंचांगpl[i].cond_state] =
				पंचांगpl[i].function;
	पूर्ण
	वापस this;
पूर्ण

व्योम
kमुक्त_fsm(fsm_instance *this)
अणु
	अगर (this) अणु
		अगर (this->f) अणु
			kमुक्त(this->f->jumpmatrix);
			kमुक्त(this->f);
		पूर्ण
		kमुक्त(this);
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_WARNING
			"fsm: kfree_fsm called with NULL argument\n");
पूर्ण

#अगर FSM_DEBUG_HISTORY
व्योम
fsm_prपूर्णांक_history(fsm_instance *fi)
अणु
	पूर्णांक idx = 0;
	पूर्णांक i;

	अगर (fi->history_size >= FSM_HISTORY_SIZE)
		idx = fi->history_index;

	prपूर्णांकk(KERN_DEBUG "fsm(%s): History:\n", fi->name);
	क्रम (i = 0; i < fi->history_size; i++) अणु
		पूर्णांक e = fi->history[idx].event;
		पूर्णांक s = fi->history[idx++].state;
		idx %= FSM_HISTORY_SIZE;
		अगर (e == -1)
			prपूर्णांकk(KERN_DEBUG "  S=%s\n",
			       fi->f->state_names[s]);
		अन्यथा
			prपूर्णांकk(KERN_DEBUG "  S=%s E=%s\n",
			       fi->f->state_names[s],
			       fi->f->event_names[e]);
	पूर्ण
	fi->history_size = fi->history_index = 0;
पूर्ण

व्योम
fsm_record_history(fsm_instance *fi, पूर्णांक state, पूर्णांक event)
अणु
	fi->history[fi->history_index].state = state;
	fi->history[fi->history_index++].event = event;
	fi->history_index %= FSM_HISTORY_SIZE;
	अगर (fi->history_size < FSM_HISTORY_SIZE)
		fi->history_size++;
पूर्ण
#पूर्ण_अगर

स्थिर अक्षर *
fsm_माला_लोtate_str(fsm_instance *fi)
अणु
	पूर्णांक st = atomic_पढ़ो(&fi->state);
	अगर (st >= fi->f->nr_states)
		वापस "Invalid";
	वापस fi->f->state_names[st];
पूर्ण

अटल व्योम
fsm_expire_समयr(काष्ठा समयr_list *t)
अणु
	fsm_समयr *this = from_समयr(this, t, tl);
#अगर FSM_TIMER_DEBUG
	prपूर्णांकk(KERN_DEBUG "fsm(%s): Timer %p expired\n",
	       this->fi->name, this);
#पूर्ण_अगर
	fsm_event(this->fi, this->expire_event, this->event_arg);
पूर्ण

व्योम
fsm_समय_रखोr(fsm_instance *fi, fsm_समयr *this)
अणु
	this->fi = fi;
#अगर FSM_TIMER_DEBUG
	prपूर्णांकk(KERN_DEBUG "fsm(%s): Create timer %p\n", fi->name,
	       this);
#पूर्ण_अगर
	समयr_setup(&this->tl, fsm_expire_समयr, 0);
पूर्ण

व्योम
fsm_delसमयr(fsm_समयr *this)
अणु
#अगर FSM_TIMER_DEBUG
	prपूर्णांकk(KERN_DEBUG "fsm(%s): Delete timer %p\n", this->fi->name,
		this);
#पूर्ण_अगर
	del_समयr(&this->tl);
पूर्ण

पूर्णांक
fsm_addसमयr(fsm_समयr *this, पूर्णांक millisec, पूर्णांक event, व्योम *arg)
अणु

#अगर FSM_TIMER_DEBUG
	prपूर्णांकk(KERN_DEBUG "fsm(%s): Add timer %p %dms\n",
	       this->fi->name, this, millisec);
#पूर्ण_अगर

	समयr_setup(&this->tl, fsm_expire_समयr, 0);
	this->expire_event = event;
	this->event_arg = arg;
	this->tl.expires = jअगरfies + (millisec * HZ) / 1000;
	add_समयr(&this->tl);
	वापस 0;
पूर्ण

/* FIXME: this function is never used, why */
व्योम
fsm_modसमयr(fsm_समयr *this, पूर्णांक millisec, पूर्णांक event, व्योम *arg)
अणु

#अगर FSM_TIMER_DEBUG
	prपूर्णांकk(KERN_DEBUG "fsm(%s): Restart timer %p %dms\n",
		this->fi->name, this, millisec);
#पूर्ण_अगर

	del_समयr(&this->tl);
	समयr_setup(&this->tl, fsm_expire_समयr, 0);
	this->expire_event = event;
	this->event_arg = arg;
	this->tl.expires = jअगरfies + (millisec * HZ) / 1000;
	add_समयr(&this->tl);
पूर्ण

EXPORT_SYMBOL(init_fsm);
EXPORT_SYMBOL(kमुक्त_fsm);
EXPORT_SYMBOL(fsm_समय_रखोr);
EXPORT_SYMBOL(fsm_delसमयr);
EXPORT_SYMBOL(fsm_addसमयr);
EXPORT_SYMBOL(fsm_modसमयr);
EXPORT_SYMBOL(fsm_माला_लोtate_str);

#अगर FSM_DEBUG_HISTORY
EXPORT_SYMBOL(fsm_prपूर्णांक_history);
EXPORT_SYMBOL(fsm_record_history);
#पूर्ण_अगर
