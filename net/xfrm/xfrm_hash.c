<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* xfrm_hash.c: Common hash table code.
 *
 * Copyright (C) 2006 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/xfrm.h>

#समावेश "xfrm_hash.h"

काष्ठा hlist_head *xfrm_hash_alloc(अचिन्हित पूर्णांक sz)
अणु
	काष्ठा hlist_head *n;

	अगर (sz <= PAGE_SIZE)
		n = kzalloc(sz, GFP_KERNEL);
	अन्यथा अगर (hashdist)
		n = vzalloc(sz);
	अन्यथा
		n = (काष्ठा hlist_head *)
			__get_मुक्त_pages(GFP_KERNEL | __GFP_NOWARN | __GFP_ZERO,
					 get_order(sz));

	वापस n;
पूर्ण

व्योम xfrm_hash_मुक्त(काष्ठा hlist_head *n, अचिन्हित पूर्णांक sz)
अणु
	अगर (sz <= PAGE_SIZE)
		kमुक्त(n);
	अन्यथा अगर (hashdist)
		vमुक्त(n);
	अन्यथा
		मुक्त_pages((अचिन्हित दीर्घ)n, get_order(sz));
पूर्ण
