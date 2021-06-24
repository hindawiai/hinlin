<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_RCUPDATE_WAIT_H
#घोषणा _LINUX_SCHED_RCUPDATE_WAIT_H

/*
 * RCU synchronization types and methods:
 */

#समावेश <linux/rcupdate.h>
#समावेश <linux/completion.h>

/*
 * Structure allowing asynchronous रुकोing on RCU.
 */
काष्ठा rcu_synchronize अणु
	काष्ठा rcu_head head;
	काष्ठा completion completion;
पूर्ण;
व्योम wakeme_after_rcu(काष्ठा rcu_head *head);

व्योम __रुको_rcu_gp(bool checktiny, पूर्णांक n, call_rcu_func_t *crcu_array,
		   काष्ठा rcu_synchronize *rs_array);

#घोषणा _रुको_rcu_gp(checktiny, ...) \
करो अणु									\
	call_rcu_func_t __crcu_array[] = अणु __VA_ARGS__ पूर्ण;		\
	काष्ठा rcu_synchronize __rs_array[ARRAY_SIZE(__crcu_array)];	\
	__रुको_rcu_gp(checktiny, ARRAY_SIZE(__crcu_array),		\
			__crcu_array, __rs_array);			\
पूर्ण जबतक (0)

#घोषणा रुको_rcu_gp(...) _रुको_rcu_gp(false, __VA_ARGS__)

/**
 * synchronize_rcu_mult - Wait concurrently क्रम multiple grace periods
 * @...: List of call_rcu() functions क्रम dअगरferent grace periods to रुको on
 *
 * This macro रुकोs concurrently क्रम multiple types of RCU grace periods.
 * For example, synchronize_rcu_mult(call_rcu, call_rcu_tasks) would रुको
 * on concurrent RCU and RCU-tasks grace periods.  Waiting on a given SRCU
 * करोमुख्य requires you to ग_लिखो a wrapper function क्रम that SRCU करोमुख्य's
 * call_srcu() function, with this wrapper supplying the poपूर्णांकer to the
 * corresponding srcu_काष्ठा.
 *
 * The first argument tells Tiny RCU's _रुको_rcu_gp() not to
 * bother रुकोing क्रम RCU.  The reason क्रम this is because anywhere
 * synchronize_rcu_mult() can be called is स्वतःmatically alपढ़ोy a full
 * grace period.
 */
#घोषणा synchronize_rcu_mult(...) \
	_रुको_rcu_gp(IS_ENABLED(CONFIG_TINY_RCU), __VA_ARGS__)

#पूर्ण_अगर /* _LINUX_SCHED_RCUPDATE_WAIT_H */
