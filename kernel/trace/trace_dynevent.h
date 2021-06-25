<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common header file क्रम generic dynamic events.
 */

#अगर_अघोषित _TRACE_DYNEVENT_H
#घोषणा _TRACE_DYNEVENT_H

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/seq_file.h>

#समावेश "trace.h"

काष्ठा dyn_event;

/**
 * काष्ठा dyn_event_operations - Methods क्रम each type of dynamic events
 *
 * These methods must be set क्रम each type, since there is no शेष method.
 * Beक्रमe using this क्रम dyn_event_init(), it must be रेजिस्टरed by
 * dyn_event_रेजिस्टर().
 *
 * @create: Parse and create event method. This is invoked when user passes
 *  a event definition to dynamic_events पूर्णांकerface. This must not deकाष्ठा
 *  the arguments and वापस -ECANCELED अगर given arguments करोesn't match its
 *  command prefix.
 * @show: Showing method. This is invoked when user पढ़ोs the event definitions
 *  via dynamic_events पूर्णांकerface.
 * @is_busy: Check whether given event is busy so that it can not be deleted.
 *  Return true अगर it is busy, otherwise false.
 * @मुक्त: Delete the given event. Return 0 अगर success, otherwise error.
 * @match: Check whether given event and प्रणाली name match this event. The argc
 *  and argv is used क्रम exact match. Return true अगर it matches, otherwise
 *  false.
 *
 * Except क्रम @create, these methods are called under holding event_mutex.
 */
काष्ठा dyn_event_operations अणु
	काष्ठा list_head	list;
	पूर्णांक (*create)(स्थिर अक्षर *raw_command);
	पूर्णांक (*show)(काष्ठा seq_file *m, काष्ठा dyn_event *ev);
	bool (*is_busy)(काष्ठा dyn_event *ev);
	पूर्णांक (*मुक्त)(काष्ठा dyn_event *ev);
	bool (*match)(स्थिर अक्षर *प्रणाली, स्थिर अक्षर *event,
		      पूर्णांक argc, स्थिर अक्षर **argv, काष्ठा dyn_event *ev);
पूर्ण;

/* Register new dyn_event type -- must be called at first */
पूर्णांक dyn_event_रेजिस्टर(काष्ठा dyn_event_operations *ops);

/**
 * काष्ठा dyn_event - Dynamic event list header
 *
 * The dyn_event काष्ठाure encapsulates a list and a poपूर्णांकer to the चालकs
 * क्रम making a global list of dynamic events.
 * User must includes this in each event काष्ठाure, so that those events can
 * be added/हटाओd via dynamic_events पूर्णांकerface.
 */
काष्ठा dyn_event अणु
	काष्ठा list_head		list;
	काष्ठा dyn_event_operations	*ops;
पूर्ण;

बाह्य काष्ठा list_head dyn_event_list;

अटल अंतरभूत
पूर्णांक dyn_event_init(काष्ठा dyn_event *ev, काष्ठा dyn_event_operations *ops)
अणु
	अगर (!ev || !ops)
		वापस -EINVAL;

	INIT_LIST_HEAD(&ev->list);
	ev->ops = ops;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dyn_event_add(काष्ठा dyn_event *ev)
अणु
	lockdep_निश्चित_held(&event_mutex);

	अगर (!ev || !ev->ops)
		वापस -EINVAL;

	list_add_tail(&ev->list, &dyn_event_list);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dyn_event_हटाओ(काष्ठा dyn_event *ev)
अणु
	lockdep_निश्चित_held(&event_mutex);
	list_del_init(&ev->list);
पूर्ण

व्योम *dyn_event_seq_start(काष्ठा seq_file *m, loff_t *pos);
व्योम *dyn_event_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos);
व्योम dyn_event_seq_stop(काष्ठा seq_file *m, व्योम *v);
पूर्णांक dyn_events_release_all(काष्ठा dyn_event_operations *type);
पूर्णांक dyn_event_release(स्थिर अक्षर *raw_command, काष्ठा dyn_event_operations *type);

/*
 * क्रम_each_dyn_event	-	iterate over the dyn_event list
 * @pos:	the काष्ठा dyn_event * to use as a loop cursor
 *
 * This is just a basement of क्रम_each macro. Wrap this क्रम
 * each actual event काष्ठाure with ops filtering.
 */
#घोषणा क्रम_each_dyn_event(pos)	\
	list_क्रम_each_entry(pos, &dyn_event_list, list)

/*
 * क्रम_each_dyn_event	-	iterate over the dyn_event list safely
 * @pos:	the काष्ठा dyn_event * to use as a loop cursor
 * @n:		the काष्ठा dyn_event * to use as temporary storage
 */
#घोषणा क्रम_each_dyn_event_safe(pos, n)	\
	list_क्रम_each_entry_safe(pos, n, &dyn_event_list, list)

बाह्य व्योम dynevent_cmd_init(काष्ठा dynevent_cmd *cmd, अक्षर *buf, पूर्णांक maxlen,
			      क्रमागत dynevent_type type,
			      dynevent_create_fn_t run_command);

प्रकार पूर्णांक (*dynevent_check_arg_fn_t)(व्योम *data);

काष्ठा dynevent_arg अणु
	स्थिर अक्षर		*str;
	अक्षर			separator; /* e.g. ';', ',', or nothing */
पूर्ण;

बाह्य व्योम dynevent_arg_init(काष्ठा dynevent_arg *arg,
			      अक्षर separator);
बाह्य पूर्णांक dynevent_arg_add(काष्ठा dynevent_cmd *cmd,
			    काष्ठा dynevent_arg *arg,
			    dynevent_check_arg_fn_t check_arg);

काष्ठा dynevent_arg_pair अणु
	स्थिर अक्षर		*lhs;
	स्थिर अक्षर		*rhs;
	अक्षर			चालक; /* e.g. '=' or nothing */
	अक्षर			separator; /* e.g. ';', ',', or nothing */
पूर्ण;

बाह्य व्योम dynevent_arg_pair_init(काष्ठा dynevent_arg_pair *arg_pair,
				   अक्षर चालक, अक्षर separator);

बाह्य पूर्णांक dynevent_arg_pair_add(काष्ठा dynevent_cmd *cmd,
				 काष्ठा dynevent_arg_pair *arg_pair,
				 dynevent_check_arg_fn_t check_arg);
बाह्य पूर्णांक dynevent_str_add(काष्ठा dynevent_cmd *cmd, स्थिर अक्षर *str);

#पूर्ण_अगर
