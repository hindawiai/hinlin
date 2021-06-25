<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#घोषणा CPUPRI_NR_PRIORITIES	(MAX_RT_PRIO+1)

#घोषणा CPUPRI_INVALID		-1
#घोषणा CPUPRI_NORMAL		 0
/* values 1-99 are क्रम RT1-RT99 priorities */
#घोषणा CPUPRI_HIGHER		100

काष्ठा cpupri_vec अणु
	atomic_t		count;
	cpumask_var_t		mask;
पूर्ण;

काष्ठा cpupri अणु
	काष्ठा cpupri_vec	pri_to_cpu[CPUPRI_NR_PRIORITIES];
	पूर्णांक			*cpu_to_pri;
पूर्ण;

#अगर_घोषित CONFIG_SMP
पूर्णांक  cpupri_find(काष्ठा cpupri *cp, काष्ठा task_काष्ठा *p,
		 काष्ठा cpumask *lowest_mask);
पूर्णांक  cpupri_find_fitness(काष्ठा cpupri *cp, काष्ठा task_काष्ठा *p,
			 काष्ठा cpumask *lowest_mask,
			 bool (*fitness_fn)(काष्ठा task_काष्ठा *p, पूर्णांक cpu));
व्योम cpupri_set(काष्ठा cpupri *cp, पूर्णांक cpu, पूर्णांक pri);
पूर्णांक  cpupri_init(काष्ठा cpupri *cp);
व्योम cpupri_cleanup(काष्ठा cpupri *cp);
#पूर्ण_अगर
