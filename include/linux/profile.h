<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PROखाता_H
#घोषणा _LINUX_PROखाता_H

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cache.h>

#समावेश <यंत्र/त्रुटिसं.स>

#घोषणा CPU_PROFILING	1
#घोषणा SCHED_PROFILING	2
#घोषणा SLEEP_PROFILING	3
#घोषणा KVM_PROFILING	4

काष्ठा proc_dir_entry;
काष्ठा notअगरier_block;

#अगर defined(CONFIG_PROFILING) && defined(CONFIG_PROC_FS)
व्योम create_prof_cpu_mask(व्योम);
पूर्णांक create_proc_profile(व्योम);
#अन्यथा
अटल अंतरभूत व्योम create_prof_cpu_mask(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक create_proc_profile(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

क्रमागत profile_type अणु
	PROखाता_TASK_EXIT,
	PROखाता_MUNMAP
पूर्ण;

#अगर_घोषित CONFIG_PROFILING

बाह्य पूर्णांक prof_on __पढ़ो_mostly;

/* init basic kernel profiler */
पूर्णांक profile_init(व्योम);
पूर्णांक profile_setup(अक्षर *str);
व्योम profile_tick(पूर्णांक type);
पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier);

/*
 * Add multiple profiler hits to a given address:
 */
व्योम profile_hits(पूर्णांक type, व्योम *ip, अचिन्हित पूर्णांक nr_hits);

/*
 * Single profiler hit:
 */
अटल अंतरभूत व्योम profile_hit(पूर्णांक type, व्योम *ip)
अणु
	/*
	 * Speedup क्रम the common (no profiling enabled) हाल:
	 */
	अगर (unlikely(prof_on == type))
		profile_hits(type, ip, 1);
पूर्ण

काष्ठा task_काष्ठा;
काष्ठा mm_काष्ठा;

/* task is in करो_निकास() */
व्योम profile_task_निकास(काष्ठा task_काष्ठा * task);

/* task is dead, मुक्त task काष्ठा ? Returns 1 अगर
 * the task was taken, 0 अगर the task should be मुक्तd.
 */
पूर्णांक profile_hanकरोff_task(काष्ठा task_काष्ठा * task);

/* sys_munmap */
व्योम profile_munmap(अचिन्हित दीर्घ addr);

पूर्णांक task_hanकरोff_रेजिस्टर(काष्ठा notअगरier_block * n);
पूर्णांक task_hanकरोff_unरेजिस्टर(काष्ठा notअगरier_block * n);

पूर्णांक profile_event_रेजिस्टर(क्रमागत profile_type, काष्ठा notअगरier_block * n);
पूर्णांक profile_event_unरेजिस्टर(क्रमागत profile_type, काष्ठा notअगरier_block * n);

#अन्यथा

#घोषणा prof_on 0

अटल अंतरभूत पूर्णांक profile_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम profile_tick(पूर्णांक type)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम profile_hits(पूर्णांक type, व्योम *ip, अचिन्हित पूर्णांक nr_hits)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम profile_hit(पूर्णांक type, व्योम *ip)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक task_hanकरोff_रेजिस्टर(काष्ठा notअगरier_block * n)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक task_hanकरोff_unरेजिस्टर(काष्ठा notअगरier_block * n)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक profile_event_रेजिस्टर(क्रमागत profile_type t, काष्ठा notअगरier_block * n)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक profile_event_unरेजिस्टर(क्रमागत profile_type t, काष्ठा notअगरier_block * n)
अणु
	वापस -ENOSYS;
पूर्ण

#घोषणा profile_task_निकास(a) करो अणु पूर्ण जबतक (0)
#घोषणा profile_hanकरोff_task(a) (0)
#घोषणा profile_munmap(a) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_PROFILING */

#पूर्ण_अगर /* _LINUX_PROखाता_H */
