<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SLAB_H
#घोषणा SLAB_H

#समावेश <linux/types.h>
#समावेश <linux/gfp.h>

#घोषणा SLAB_HWCACHE_ALIGN 1
#घोषणा SLAB_PANIC 2
#घोषणा SLAB_RECLAIM_ACCOUNT    0x00020000UL            /* Objects are reclaimable */

व्योम *kदो_स्मृति(माप_प्रकार size, gfp_t);
व्योम kमुक्त(व्योम *);

अटल अंतरभूत व्योम *kzalloc(माप_प्रकार size, gfp_t gfp)
अणु
        वापस kदो_स्मृति(size, gfp | __GFP_ZERO);
पूर्ण

व्योम *kmem_cache_alloc(काष्ठा kmem_cache *cachep, पूर्णांक flags);
व्योम kmem_cache_मुक्त(काष्ठा kmem_cache *cachep, व्योम *objp);

काष्ठा kmem_cache *kmem_cache_create(स्थिर अक्षर *name, अचिन्हित पूर्णांक size,
			अचिन्हित पूर्णांक align, अचिन्हित पूर्णांक flags,
			व्योम (*ctor)(व्योम *));

#पूर्ण_अगर		/* SLAB_H */
