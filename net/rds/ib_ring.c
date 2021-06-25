<शैली गुरु>
/*
 * Copyright (c) 2006 Oracle.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#समावेश <linux/kernel.h>

#समावेश "rds.h"
#समावेश "ib.h"

/*
 * Locking क्रम IB rings.
 * We assume that allocation is always रक्षित by a mutex
 * in the caller (this is a valid assumption क्रम the current
 * implementation).
 *
 * Freeing always happens in an पूर्णांकerrupt, and hence only
 * races with allocations, but not with other मुक्त()s.
 *
 * The पूर्णांकeraction between allocation and मुक्तing is that
 * the alloc code has to determine the number of मुक्त entries.
 * To this end, we मुख्यtain two counters; an allocation counter
 * and a मुक्त counter. Both are allowed to run मुक्तly, and wrap
 * around.
 * The number of used entries is always (alloc_ctr - मुक्त_ctr) % NR.
 *
 * The current implementation makes मुक्त_ctr atomic. When the
 * caller finds an allocation fails, it should set an "alloc fail"
 * bit and retry the allocation. The "alloc fail" bit essentially tells
 * the CQ completion handlers to wake it up after मुक्तing some
 * more entries.
 */

/*
 * This only happens on shutकरोwn.
 */
DECLARE_WAIT_QUEUE_HEAD(rds_ib_ring_empty_रुको);

व्योम rds_ib_ring_init(काष्ठा rds_ib_work_ring *ring, u32 nr)
अणु
	स_रखो(ring, 0, माप(*ring));
	ring->w_nr = nr;
	rdsdebug("ring %p nr %u\n", ring, ring->w_nr);
पूर्ण

अटल अंतरभूत u32 __rds_ib_ring_used(काष्ठा rds_ib_work_ring *ring)
अणु
	u32 dअगरf;

	/* This assumes that atomic_t has at least as many bits as u32 */
	dअगरf = ring->w_alloc_ctr - (u32) atomic_पढ़ो(&ring->w_मुक्त_ctr);
	BUG_ON(dअगरf > ring->w_nr);

	वापस dअगरf;
पूर्ण

व्योम rds_ib_ring_resize(काष्ठा rds_ib_work_ring *ring, u32 nr)
अणु
	/* We only ever get called from the connection setup code,
	 * prior to creating the QP. */
	BUG_ON(__rds_ib_ring_used(ring));
	ring->w_nr = nr;
पूर्ण

अटल पूर्णांक __rds_ib_ring_empty(काष्ठा rds_ib_work_ring *ring)
अणु
	वापस __rds_ib_ring_used(ring) == 0;
पूर्ण

u32 rds_ib_ring_alloc(काष्ठा rds_ib_work_ring *ring, u32 val, u32 *pos)
अणु
	u32 ret = 0, avail;

	avail = ring->w_nr - __rds_ib_ring_used(ring);

	rdsdebug("ring %p val %u next %u free %u\n", ring, val,
		 ring->w_alloc_ptr, avail);

	अगर (val && avail) अणु
		ret = min(val, avail);
		*pos = ring->w_alloc_ptr;

		ring->w_alloc_ptr = (ring->w_alloc_ptr + ret) % ring->w_nr;
		ring->w_alloc_ctr += ret;
	पूर्ण

	वापस ret;
पूर्ण

व्योम rds_ib_ring_मुक्त(काष्ठा rds_ib_work_ring *ring, u32 val)
अणु
	ring->w_मुक्त_ptr = (ring->w_मुक्त_ptr + val) % ring->w_nr;
	atomic_add(val, &ring->w_मुक्त_ctr);

	अगर (__rds_ib_ring_empty(ring) &&
	    रुकोqueue_active(&rds_ib_ring_empty_रुको))
		wake_up(&rds_ib_ring_empty_रुको);
पूर्ण

व्योम rds_ib_ring_unalloc(काष्ठा rds_ib_work_ring *ring, u32 val)
अणु
	ring->w_alloc_ptr = (ring->w_alloc_ptr - val) % ring->w_nr;
	ring->w_alloc_ctr -= val;
पूर्ण

पूर्णांक rds_ib_ring_empty(काष्ठा rds_ib_work_ring *ring)
अणु
	वापस __rds_ib_ring_empty(ring);
पूर्ण

पूर्णांक rds_ib_ring_low(काष्ठा rds_ib_work_ring *ring)
अणु
	वापस __rds_ib_ring_used(ring) <= (ring->w_nr >> 1);
पूर्ण

/*
 * वापसs the oldest alloced ring entry.  This will be the next one
 * मुक्तd.  This can't be called अगर there are none allocated.
 */
u32 rds_ib_ring_oldest(काष्ठा rds_ib_work_ring *ring)
अणु
	वापस ring->w_मुक्त_ptr;
पूर्ण

/*
 * वापसs the number of completed work requests.
 */

u32 rds_ib_ring_completed(काष्ठा rds_ib_work_ring *ring, u32 wr_id, u32 oldest)
अणु
	u32 ret;

	अगर (oldest <= (अचिन्हित दीर्घ दीर्घ)wr_id)
		ret = (अचिन्हित दीर्घ दीर्घ)wr_id - oldest + 1;
	अन्यथा
		ret = ring->w_nr - oldest + (अचिन्हित दीर्घ दीर्घ)wr_id + 1;

	rdsdebug("ring %p ret %u wr_id %u oldest %u\n", ring, ret,
		 wr_id, oldest);
	वापस ret;
पूर्ण
