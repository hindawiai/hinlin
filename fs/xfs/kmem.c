<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश <linux/backing-dev.h>
#समावेश "xfs_message.h"
#समावेश "xfs_trace.h"

व्योम *
kmem_alloc(माप_प्रकार size, xfs_km_flags_t flags)
अणु
	पूर्णांक	retries = 0;
	gfp_t	lflags = kmem_flags_convert(flags);
	व्योम	*ptr;

	trace_kmem_alloc(size, flags, _RET_IP_);

	करो अणु
		ptr = kदो_स्मृति(size, lflags);
		अगर (ptr || (flags & KM_MAYFAIL))
			वापस ptr;
		अगर (!(++retries % 100))
			xfs_err(शून्य,
	"%s(%u) possible memory allocation deadlock size %u in %s (mode:0x%x)",
				current->comm, current->pid,
				(अचिन्हित पूर्णांक)size, __func__, lflags);
		congestion_रुको(BLK_RW_ASYNC, HZ/50);
	पूर्ण जबतक (1);
पूर्ण


/*
 * __vदो_स्मृति() will allocate data pages and auxiliary काष्ठाures (e.g.
 * pagetables) with GFP_KERNEL, yet we may be under GFP_NOFS context here. Hence
 * we need to tell memory reclaim that we are in such a context via
 * PF_MEMALLOC_NOFS to prevent memory reclaim re-entering the fileप्रणाली here
 * and potentially deadlocking.
 */
अटल व्योम *
__kmem_vदो_स्मृति(माप_प्रकार size, xfs_km_flags_t flags)
अणु
	अचिन्हित nofs_flag = 0;
	व्योम	*ptr;
	gfp_t	lflags = kmem_flags_convert(flags);

	अगर (flags & KM_NOFS)
		nofs_flag = meदो_स्मृति_nofs_save();

	ptr = __vदो_स्मृति(size, lflags);

	अगर (flags & KM_NOFS)
		meदो_स्मृति_nofs_restore(nofs_flag);

	वापस ptr;
पूर्ण

/*
 * Same as kmem_alloc_large, except we guarantee the buffer वापसed is aligned
 * to the @align_mask. We only guarantee alignment up to page size, we'll clamp
 * alignment at page size अगर it is larger. vदो_स्मृति always वापसs a PAGE_SIZE
 * aligned region.
 */
व्योम *
kmem_alloc_io(माप_प्रकार size, पूर्णांक align_mask, xfs_km_flags_t flags)
अणु
	व्योम	*ptr;

	trace_kmem_alloc_io(size, flags, _RET_IP_);

	अगर (WARN_ON_ONCE(align_mask >= PAGE_SIZE))
		align_mask = PAGE_SIZE - 1;

	ptr = kmem_alloc(size, flags | KM_MAYFAIL);
	अगर (ptr) अणु
		अगर (!((uपूर्णांकptr_t)ptr & align_mask))
			वापस ptr;
		kमुक्त(ptr);
	पूर्ण
	वापस __kmem_vदो_स्मृति(size, flags);
पूर्ण

व्योम *
kmem_alloc_large(माप_प्रकार size, xfs_km_flags_t flags)
अणु
	व्योम	*ptr;

	trace_kmem_alloc_large(size, flags, _RET_IP_);

	ptr = kmem_alloc(size, flags | KM_MAYFAIL);
	अगर (ptr)
		वापस ptr;
	वापस __kmem_vदो_स्मृति(size, flags);
पूर्ण
