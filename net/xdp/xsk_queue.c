<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* XDP user-space ring काष्ठाure
 * Copyright(c) 2018 Intel Corporation.
 */

#समावेश <linux/log2.h>
#समावेश <linux/slab.h>
#समावेश <linux/overflow.h>
#समावेश <net/xdp_sock_drv.h>

#समावेश "xsk_queue.h"

अटल माप_प्रकार xskq_get_ring_size(काष्ठा xsk_queue *q, bool umem_queue)
अणु
	काष्ठा xdp_umem_ring *umem_ring;
	काष्ठा xdp_rxtx_ring *rxtx_ring;

	अगर (umem_queue)
		वापस काष्ठा_size(umem_ring, desc, q->nentries);
	वापस काष्ठा_size(rxtx_ring, desc, q->nentries);
पूर्ण

काष्ठा xsk_queue *xskq_create(u32 nentries, bool umem_queue)
अणु
	काष्ठा xsk_queue *q;
	gfp_t gfp_flags;
	माप_प्रकार size;

	q = kzalloc(माप(*q), GFP_KERNEL);
	अगर (!q)
		वापस शून्य;

	q->nentries = nentries;
	q->ring_mask = nentries - 1;

	gfp_flags = GFP_KERNEL | __GFP_ZERO | __GFP_NOWARN |
		    __GFP_COMP  | __GFP_NORETRY;
	size = xskq_get_ring_size(q, umem_queue);

	q->ring = (काष्ठा xdp_ring *)__get_मुक्त_pages(gfp_flags,
						      get_order(size));
	अगर (!q->ring) अणु
		kमुक्त(q);
		वापस शून्य;
	पूर्ण

	वापस q;
पूर्ण

व्योम xskq_destroy(काष्ठा xsk_queue *q)
अणु
	अगर (!q)
		वापस;

	page_frag_मुक्त(q->ring);
	kमुक्त(q);
पूर्ण
