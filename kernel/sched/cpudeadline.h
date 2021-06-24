<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#घोषणा IDX_INVALID		-1

काष्ठा cpudl_item अणु
	u64			dl;
	पूर्णांक			cpu;
	पूर्णांक			idx;
पूर्ण;

काष्ठा cpudl अणु
	raw_spinlock_t		lock;
	पूर्णांक			size;
	cpumask_var_t		मुक्त_cpus;
	काष्ठा cpudl_item	*elements;
पूर्ण;

#अगर_घोषित CONFIG_SMP
पूर्णांक  cpudl_find(काष्ठा cpudl *cp, काष्ठा task_काष्ठा *p, काष्ठा cpumask *later_mask);
व्योम cpudl_set(काष्ठा cpudl *cp, पूर्णांक cpu, u64 dl);
व्योम cpudl_clear(काष्ठा cpudl *cp, पूर्णांक cpu);
पूर्णांक  cpudl_init(काष्ठा cpudl *cp);
व्योम cpudl_set_मुक्तcpu(काष्ठा cpudl *cp, पूर्णांक cpu);
व्योम cpudl_clear_मुक्तcpu(काष्ठा cpudl *cp, पूर्णांक cpu);
व्योम cpudl_cleanup(काष्ठा cpudl *cp);
#पूर्ण_अगर /* CONFIG_SMP */
