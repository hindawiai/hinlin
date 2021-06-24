<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_SUPPORT_KMEM_H__
#घोषणा __XFS_SUPPORT_KMEM_H__

#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>

/*
 * General memory allocation पूर्णांकerfaces
 */

प्रकार अचिन्हित __bitwise xfs_km_flags_t;
#घोषणा KM_NOFS		((__क्रमce xfs_km_flags_t)0x0004u)
#घोषणा KM_MAYFAIL	((__क्रमce xfs_km_flags_t)0x0008u)
#घोषणा KM_ZERO		((__क्रमce xfs_km_flags_t)0x0010u)
#घोषणा KM_NOLOCKDEP	((__क्रमce xfs_km_flags_t)0x0020u)

/*
 * We use a special process flag to aव्योम recursive callbacks पूर्णांकo
 * the fileप्रणाली during transactions.  We will also issue our own
 * warnings, so we explicitly skip any generic ones (silly of us).
 */
अटल अंतरभूत gfp_t
kmem_flags_convert(xfs_km_flags_t flags)
अणु
	gfp_t	lflags;

	BUG_ON(flags & ~(KM_NOFS | KM_MAYFAIL | KM_ZERO | KM_NOLOCKDEP));

	lflags = GFP_KERNEL | __GFP_NOWARN;
	अगर (flags & KM_NOFS)
		lflags &= ~__GFP_FS;

	/*
	 * Default page/slab allocator behavior is to retry क्रम ever
	 * क्रम small allocations. We can override this behavior by using
	 * __GFP_RETRY_MAYFAIL which will tell the allocator to retry as दीर्घ
	 * as it is feasible but rather fail than retry क्रमever क्रम all
	 * request sizes.
	 */
	अगर (flags & KM_MAYFAIL)
		lflags |= __GFP_RETRY_MAYFAIL;

	अगर (flags & KM_ZERO)
		lflags |= __GFP_ZERO;

	अगर (flags & KM_NOLOCKDEP)
		lflags |= __GFP_NOLOCKDEP;

	वापस lflags;
पूर्ण

बाह्य व्योम *kmem_alloc(माप_प्रकार, xfs_km_flags_t);
बाह्य व्योम *kmem_alloc_io(माप_प्रकार size, पूर्णांक align_mask, xfs_km_flags_t flags);
बाह्य व्योम *kmem_alloc_large(माप_प्रकार size, xfs_km_flags_t);
अटल अंतरभूत व्योम  kmem_मुक्त(स्थिर व्योम *ptr)
अणु
	kvमुक्त(ptr);
पूर्ण


अटल अंतरभूत व्योम *
kmem_zalloc(माप_प्रकार size, xfs_km_flags_t flags)
अणु
	वापस kmem_alloc(size, flags | KM_ZERO);
पूर्ण

/*
 * Zone पूर्णांकerfaces
 */

#घोषणा kmem_zone	kmem_cache
#घोषणा kmem_zone_t	काष्ठा kmem_cache

अटल अंतरभूत काष्ठा page *
kmem_to_page(व्योम *addr)
अणु
	अगर (is_vदो_स्मृति_addr(addr))
		वापस vदो_स्मृति_to_page(addr);
	वापस virt_to_page(addr);
पूर्ण

#पूर्ण_अगर /* __XFS_SUPPORT_KMEM_H__ */
