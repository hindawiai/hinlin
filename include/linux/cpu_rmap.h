<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __LINUX_CPU_RMAP_H
#घोषणा __LINUX_CPU_RMAP_H

/*
 * cpu_rmap.c: CPU affinity reverse-map support
 * Copyright 2011 Solarflare Communications Inc.
 */

#समावेश <linux/cpumask.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/kref.h>

/**
 * काष्ठा cpu_rmap - CPU affinity reverse-map
 * @refcount: kref क्रम object
 * @size: Number of objects to be reverse-mapped
 * @used: Number of objects added
 * @obj: Poपूर्णांकer to array of object poपूर्णांकers
 * @near: For each CPU, the index and distance to the nearest object,
 *      based on affinity masks
 */
काष्ठा cpu_rmap अणु
	काष्ठा kref	refcount;
	u16		size, used;
	व्योम		**obj;
	काष्ठा अणु
		u16	index;
		u16	dist;
	पूर्ण		near[];
पूर्ण;
#घोषणा CPU_RMAP_DIST_INF 0xffff

बाह्य काष्ठा cpu_rmap *alloc_cpu_rmap(अचिन्हित पूर्णांक size, gfp_t flags);
बाह्य पूर्णांक cpu_rmap_put(काष्ठा cpu_rmap *rmap);

बाह्य पूर्णांक cpu_rmap_add(काष्ठा cpu_rmap *rmap, व्योम *obj);
बाह्य पूर्णांक cpu_rmap_update(काष्ठा cpu_rmap *rmap, u16 index,
			   स्थिर काष्ठा cpumask *affinity);

अटल अंतरभूत u16 cpu_rmap_lookup_index(काष्ठा cpu_rmap *rmap, अचिन्हित पूर्णांक cpu)
अणु
	वापस rmap->near[cpu].index;
पूर्ण

अटल अंतरभूत व्योम *cpu_rmap_lookup_obj(काष्ठा cpu_rmap *rmap, अचिन्हित पूर्णांक cpu)
अणु
	वापस rmap->obj[rmap->near[cpu].index];
पूर्ण

/**
 * alloc_irq_cpu_rmap - allocate CPU affinity reverse-map क्रम IRQs
 * @size: Number of objects to be mapped
 *
 * Must be called in process context.
 */
अटल अंतरभूत काष्ठा cpu_rmap *alloc_irq_cpu_rmap(अचिन्हित पूर्णांक size)
अणु
	वापस alloc_cpu_rmap(size, GFP_KERNEL);
पूर्ण
बाह्य व्योम मुक्त_irq_cpu_rmap(काष्ठा cpu_rmap *rmap);

बाह्य पूर्णांक irq_cpu_rmap_add(काष्ठा cpu_rmap *rmap, पूर्णांक irq);

#पूर्ण_अगर /* __LINUX_CPU_RMAP_H */
