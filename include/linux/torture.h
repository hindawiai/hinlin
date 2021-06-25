<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Common functions क्रम in-kernel torture tests.
 *
 * Copyright IBM Corporation, 2014
 *
 * Author: Paul E. McKenney <paulmck@linux.ibm.com>
 */

#अगर_अघोषित __LINUX_TORTURE_H
#घोषणा __LINUX_TORTURE_H

#समावेश <linux/types.h>
#समावेश <linux/cache.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/completion.h>
#समावेश <linux/debugobjects.h>
#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>

/* Definitions क्रम a non-string torture-test module parameter. */
#घोषणा torture_param(type, name, init, msg) \
	अटल type name = init; \
	module_param(name, type, 0444); \
	MODULE_PARM_DESC(name, msg);

#घोषणा TORTURE_FLAG "-torture:"
#घोषणा TOROUT_STRING(s) \
	pr_alert("%s" TORTURE_FLAG " %s\n", torture_type, s)
#घोषणा VERBOSE_TOROUT_STRING(s) \
करो अणु										\
	अगर (verbose) अणु								\
		verbose_torout_sleep();						\
		pr_alert("%s" TORTURE_FLAG " %s\n", torture_type, s);		\
	पूर्ण									\
पूर्ण जबतक (0)
#घोषणा VERBOSE_TOROUT_ERRSTRING(s) \
करो अणु										\
	अगर (verbose) अणु								\
		verbose_torout_sleep();						\
		pr_alert("%s" TORTURE_FLAG "!!! %s\n", torture_type, s);	\
	पूर्ण									\
पूर्ण जबतक (0)
व्योम verbose_torout_sleep(व्योम);

/* Definitions क्रम online/offline exerciser. */
#अगर_घोषित CONFIG_HOTPLUG_CPU
पूर्णांक torture_num_online_cpus(व्योम);
#अन्यथा /* #अगर_घोषित CONFIG_HOTPLUG_CPU */
अटल अंतरभूत पूर्णांक torture_num_online_cpus(व्योम) अणु वापस 1; पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_HOTPLUG_CPU */
प्रकार व्योम torture_ofl_func(व्योम);
bool torture_offline(पूर्णांक cpu, दीर्घ *n_onl_attempts, दीर्घ *n_onl_successes,
		     अचिन्हित दीर्घ *sum_offl, पूर्णांक *min_onl, पूर्णांक *max_onl);
bool torture_online(पूर्णांक cpu, दीर्घ *n_onl_attempts, दीर्घ *n_onl_successes,
		    अचिन्हित दीर्घ *sum_onl, पूर्णांक *min_onl, पूर्णांक *max_onl);
पूर्णांक torture_onoff_init(दीर्घ ooholकरोff, दीर्घ ooपूर्णांकerval, torture_ofl_func *f);
व्योम torture_onoff_stats(व्योम);
bool torture_onoff_failures(व्योम);

/* Low-rider अक्रमom number generator. */
काष्ठा torture_अक्रमom_state अणु
	अचिन्हित दीर्घ trs_state;
	दीर्घ trs_count;
पूर्ण;
#घोषणा DEFINE_TORTURE_RANDOM(name) काष्ठा torture_अक्रमom_state name = अणु 0, 0 पूर्ण
#घोषणा DEFINE_TORTURE_RANDOM_PERCPU(name) \
	DEFINE_PER_CPU(काष्ठा torture_अक्रमom_state, name)
अचिन्हित दीर्घ torture_अक्रमom(काष्ठा torture_अक्रमom_state *trsp);
अटल अंतरभूत व्योम torture_अक्रमom_init(काष्ठा torture_अक्रमom_state *trsp)
अणु
	trsp->trs_state = 0;
	trsp->trs_count = 0;
पूर्ण

/* Definitions क्रम high-resolution-समयr sleeps. */
पूर्णांक torture_hrसमयout_ns(kसमय_प्रकार baset_ns, u32 fuzzt_ns, काष्ठा torture_अक्रमom_state *trsp);
पूर्णांक torture_hrसमयout_us(u32 baset_us, u32 fuzzt_ns, काष्ठा torture_अक्रमom_state *trsp);
पूर्णांक torture_hrसमयout_ms(u32 baset_ms, u32 fuzzt_us, काष्ठा torture_अक्रमom_state *trsp);
पूर्णांक torture_hrसमयout_jअगरfies(u32 baset_j, काष्ठा torture_अक्रमom_state *trsp);
पूर्णांक torture_hrसमयout_s(u32 baset_s, u32 fuzzt_ms, काष्ठा torture_अक्रमom_state *trsp);

/* Task shuffler, which causes CPUs to occasionally go idle. */
व्योम torture_shuffle_task_रेजिस्टर(काष्ठा task_काष्ठा *tp);
पूर्णांक torture_shuffle_init(दीर्घ shuffपूर्णांक);

/* Test स्वतः-shutकरोwn handling. */
व्योम torture_shutकरोwn_असलorb(स्थिर अक्षर *title);
पूर्णांक torture_shutकरोwn_init(पूर्णांक ssecs, व्योम (*cleanup)(व्योम));

/* Task stuttering, which क्रमces load/no-load transitions. */
bool stutter_रुको(स्थिर अक्षर *title);
पूर्णांक torture_stutter_init(पूर्णांक s, पूर्णांक sgap);

/* Initialization and cleanup. */
bool torture_init_begin(अक्षर *ttype, पूर्णांक v);
व्योम torture_init_end(व्योम);
bool torture_cleanup_begin(व्योम);
व्योम torture_cleanup_end(व्योम);
bool torture_must_stop(व्योम);
bool torture_must_stop_irq(व्योम);
व्योम torture_kthपढ़ो_stopping(अक्षर *title);
पूर्णांक _torture_create_kthपढ़ो(पूर्णांक (*fn)(व्योम *arg), व्योम *arg, अक्षर *s, अक्षर *m,
			     अक्षर *f, काष्ठा task_काष्ठा **tp);
व्योम _torture_stop_kthपढ़ो(अक्षर *m, काष्ठा task_काष्ठा **tp);

#घोषणा torture_create_kthपढ़ो(n, arg, tp) \
	_torture_create_kthपढ़ो(n, (arg), #n, "Creating " #n " task", \
				"Failed to create " #n, &(tp))
#घोषणा torture_stop_kthपढ़ो(n, tp) \
	_torture_stop_kthपढ़ो("Stopping " #n " task", &(tp))

#अगर_घोषित CONFIG_PREEMPTION
#घोषणा torture_preempt_schedule() preempt_schedule()
#अन्यथा
#घोषणा torture_preempt_schedule()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_TORTURE_H */
