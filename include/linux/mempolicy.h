<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NUMA memory policies क्रम Linux.
 * Copyright 2003,2004 Andi Kleen SuSE Lअसल
 */
#अगर_अघोषित _LINUX_MEMPOLICY_H
#घोषणा _LINUX_MEMPOLICY_H 1

#समावेश <linux/sched.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/dax.h>
#समावेश <linux/slab.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/pagemap.h>
#समावेश <uapi/linux/mempolicy.h>

काष्ठा mm_काष्ठा;

#अगर_घोषित CONFIG_NUMA

/*
 * Describe a memory policy.
 *
 * A mempolicy can be either associated with a process or with a VMA.
 * For VMA related allocations the VMA policy is preferred, otherwise
 * the process policy is used. Interrupts ignore the memory policy
 * of the current process.
 *
 * Locking policy क्रम पूर्णांकerleave:
 * In process context there is no locking because only the process accesses
 * its own state. All vma manipulation is somewhat रक्षित by a करोwn_पढ़ो on
 * mmap_lock.
 *
 * Freeing policy:
 * Mempolicy objects are reference counted.  A mempolicy will be मुक्तd when
 * mpol_put() decrements the reference count to zero.
 *
 * Duplicating policy objects:
 * mpol_dup() allocates a new mempolicy and copies the specअगरied mempolicy
 * to the new storage.  The reference count of the new object is initialized
 * to 1, representing the caller of mpol_dup().
 */
काष्ठा mempolicy अणु
	atomic_t refcnt;
	अचिन्हित लघु mode; 	/* See MPOL_* above */
	अचिन्हित लघु flags;	/* See set_mempolicy() MPOL_F_* above */
	जोड़ अणु
		लघु 		 preferred_node; /* preferred */
		nodemask_t	 nodes;		/* पूर्णांकerleave/bind */
		/* undefined क्रम शेष */
	पूर्ण v;
	जोड़ अणु
		nodemask_t cpuset_mems_allowed;	/* relative to these nodes */
		nodemask_t user_nodemask;	/* nodemask passed by user */
	पूर्ण w;
पूर्ण;

/*
 * Support क्रम managing mempolicy data objects (clone, copy, destroy)
 * The शेष fast path of a शून्य MPOL_DEFAULT policy is always अंतरभूतd.
 */

बाह्य व्योम __mpol_put(काष्ठा mempolicy *pol);
अटल अंतरभूत व्योम mpol_put(काष्ठा mempolicy *pol)
अणु
	अगर (pol)
		__mpol_put(pol);
पूर्ण

/*
 * Does mempolicy pol need explicit unref after use?
 * Currently only needed क्रम shared policies.
 */
अटल अंतरभूत पूर्णांक mpol_needs_cond_ref(काष्ठा mempolicy *pol)
अणु
	वापस (pol && (pol->flags & MPOL_F_SHARED));
पूर्ण

अटल अंतरभूत व्योम mpol_cond_put(काष्ठा mempolicy *pol)
अणु
	अगर (mpol_needs_cond_ref(pol))
		__mpol_put(pol);
पूर्ण

बाह्य काष्ठा mempolicy *__mpol_dup(काष्ठा mempolicy *pol);
अटल अंतरभूत काष्ठा mempolicy *mpol_dup(काष्ठा mempolicy *pol)
अणु
	अगर (pol)
		pol = __mpol_dup(pol);
	वापस pol;
पूर्ण

#घोषणा vma_policy(vma) ((vma)->vm_policy)

अटल अंतरभूत व्योम mpol_get(काष्ठा mempolicy *pol)
अणु
	अगर (pol)
		atomic_inc(&pol->refcnt);
पूर्ण

बाह्य bool __mpol_equal(काष्ठा mempolicy *a, काष्ठा mempolicy *b);
अटल अंतरभूत bool mpol_equal(काष्ठा mempolicy *a, काष्ठा mempolicy *b)
अणु
	अगर (a == b)
		वापस true;
	वापस __mpol_equal(a, b);
पूर्ण

/*
 * Tree of shared policies क्रम a shared memory region.
 * Maपूर्णांकain the policies in a pseuकरो mm that contains vmas. The vmas
 * carry the policy. As a special twist the pseuकरो mm is indexed in pages, not
 * bytes, so that we can work with shared memory segments bigger than
 * अचिन्हित दीर्घ.
 */

काष्ठा sp_node अणु
	काष्ठा rb_node nd;
	अचिन्हित दीर्घ start, end;
	काष्ठा mempolicy *policy;
पूर्ण;

काष्ठा shared_policy अणु
	काष्ठा rb_root root;
	rwlock_t lock;
पूर्ण;

पूर्णांक vma_dup_policy(काष्ठा vm_area_काष्ठा *src, काष्ठा vm_area_काष्ठा *dst);
व्योम mpol_shared_policy_init(काष्ठा shared_policy *sp, काष्ठा mempolicy *mpol);
पूर्णांक mpol_set_shared_policy(काष्ठा shared_policy *info,
				काष्ठा vm_area_काष्ठा *vma,
				काष्ठा mempolicy *new);
व्योम mpol_मुक्त_shared_policy(काष्ठा shared_policy *p);
काष्ठा mempolicy *mpol_shared_policy_lookup(काष्ठा shared_policy *sp,
					    अचिन्हित दीर्घ idx);

काष्ठा mempolicy *get_task_policy(काष्ठा task_काष्ठा *p);
काष्ठा mempolicy *__get_vma_policy(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr);
bool vma_policy_mof(काष्ठा vm_area_काष्ठा *vma);

बाह्य व्योम numa_शेष_policy(व्योम);
बाह्य व्योम numa_policy_init(व्योम);
बाह्य व्योम mpol_rebind_task(काष्ठा task_काष्ठा *tsk, स्थिर nodemask_t *new);
बाह्य व्योम mpol_rebind_mm(काष्ठा mm_काष्ठा *mm, nodemask_t *new);

बाह्य पूर्णांक huge_node(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ addr, gfp_t gfp_flags,
				काष्ठा mempolicy **mpol, nodemask_t **nodemask);
बाह्य bool init_nodemask_of_mempolicy(nodemask_t *mask);
बाह्य bool mempolicy_nodemask_पूर्णांकersects(काष्ठा task_काष्ठा *tsk,
				स्थिर nodemask_t *mask);
बाह्य nodemask_t *policy_nodemask(gfp_t gfp, काष्ठा mempolicy *policy);

अटल अंतरभूत nodemask_t *policy_nodemask_current(gfp_t gfp)
अणु
	काष्ठा mempolicy *mpol = get_task_policy(current);

	वापस policy_nodemask(gfp, mpol);
पूर्ण

बाह्य अचिन्हित पूर्णांक mempolicy_slab_node(व्योम);

बाह्य क्रमागत zone_type policy_zone;

अटल अंतरभूत व्योम check_highest_zone(क्रमागत zone_type k)
अणु
	अगर (k > policy_zone && k != ZONE_MOVABLE)
		policy_zone = k;
पूर्ण

पूर्णांक करो_migrate_pages(काष्ठा mm_काष्ठा *mm, स्थिर nodemask_t *from,
		     स्थिर nodemask_t *to, पूर्णांक flags);


#अगर_घोषित CONFIG_TMPFS
बाह्य पूर्णांक mpol_parse_str(अक्षर *str, काष्ठा mempolicy **mpol);
#पूर्ण_अगर

बाह्य व्योम mpol_to_str(अक्षर *buffer, पूर्णांक maxlen, काष्ठा mempolicy *pol);

/* Check अगर a vma is migratable */
बाह्य bool vma_migratable(काष्ठा vm_area_काष्ठा *vma);

बाह्य पूर्णांक mpol_misplaced(काष्ठा page *, काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ);
बाह्य व्योम mpol_put_task_policy(काष्ठा task_काष्ठा *);

#अन्यथा

काष्ठा mempolicy अणुपूर्ण;

अटल अंतरभूत bool mpol_equal(काष्ठा mempolicy *a, काष्ठा mempolicy *b)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम mpol_put(काष्ठा mempolicy *p)
अणु
पूर्ण

अटल अंतरभूत व्योम mpol_cond_put(काष्ठा mempolicy *pol)
अणु
पूर्ण

अटल अंतरभूत व्योम mpol_get(काष्ठा mempolicy *pol)
अणु
पूर्ण

काष्ठा shared_policy अणुपूर्ण;

अटल अंतरभूत व्योम mpol_shared_policy_init(काष्ठा shared_policy *sp,
						काष्ठा mempolicy *mpol)
अणु
पूर्ण

अटल अंतरभूत व्योम mpol_मुक्त_shared_policy(काष्ठा shared_policy *p)
अणु
पूर्ण

अटल अंतरभूत काष्ठा mempolicy *
mpol_shared_policy_lookup(काष्ठा shared_policy *sp, अचिन्हित दीर्घ idx)
अणु
	वापस शून्य;
पूर्ण

#घोषणा vma_policy(vma) शून्य

अटल अंतरभूत पूर्णांक
vma_dup_policy(काष्ठा vm_area_काष्ठा *src, काष्ठा vm_area_काष्ठा *dst)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम numa_policy_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम numa_शेष_policy(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम mpol_rebind_task(काष्ठा task_काष्ठा *tsk,
				स्थिर nodemask_t *new)
अणु
पूर्ण

अटल अंतरभूत व्योम mpol_rebind_mm(काष्ठा mm_काष्ठा *mm, nodemask_t *new)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक huge_node(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ addr, gfp_t gfp_flags,
				काष्ठा mempolicy **mpol, nodemask_t **nodemask)
अणु
	*mpol = शून्य;
	*nodemask = शून्य;
	वापस 0;
पूर्ण

अटल अंतरभूत bool init_nodemask_of_mempolicy(nodemask_t *m)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक करो_migrate_pages(काष्ठा mm_काष्ठा *mm, स्थिर nodemask_t *from,
				   स्थिर nodemask_t *to, पूर्णांक flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम check_highest_zone(पूर्णांक k)
अणु
पूर्ण

#अगर_घोषित CONFIG_TMPFS
अटल अंतरभूत पूर्णांक mpol_parse_str(अक्षर *str, काष्ठा mempolicy **mpol)
अणु
	वापस 1;	/* error */
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक mpol_misplaced(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ address)
अणु
	वापस -1; /* no node preference */
पूर्ण

अटल अंतरभूत व्योम mpol_put_task_policy(काष्ठा task_काष्ठा *task)
अणु
पूर्ण

अटल अंतरभूत nodemask_t *policy_nodemask_current(gfp_t gfp)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA */
#पूर्ण_अगर
