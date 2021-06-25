<शैली गुरु>
/*
 * Copyright (c) 2012-2016 VMware, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of EITHER the GNU General Public License
 * version 2 as published by the Free Software Foundation or the BSD
 * 2-Clause License. This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License version 2 क्रम more details at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.hपंचांगl.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program available in the file COPYING in the मुख्य
 * directory of this source tree.
 *
 * The BSD 2-Clause License
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __PVRDMA_RING_H__
#घोषणा __PVRDMA_RING_H__

#समावेश <linux/types.h>

#घोषणा PVRDMA_INVALID_IDX	-1	/* Invalid index. */

काष्ठा pvrdma_ring अणु
	atomic_t prod_tail;	/* Producer tail. */
	atomic_t cons_head;	/* Consumer head. */
पूर्ण;

काष्ठा pvrdma_ring_state अणु
	काष्ठा pvrdma_ring tx;	/* Tx ring. */
	काष्ठा pvrdma_ring rx;	/* Rx ring. */
पूर्ण;

अटल अंतरभूत पूर्णांक pvrdma_idx_valid(__u32 idx, __u32 max_elems)
अणु
	/* Generates fewer inकाष्ठाions than a less-than. */
	वापस (idx & ~((max_elems << 1) - 1)) == 0;
पूर्ण

अटल अंतरभूत __s32 pvrdma_idx(atomic_t *var, __u32 max_elems)
अणु
	स्थिर अचिन्हित पूर्णांक idx = atomic_पढ़ो(var);

	अगर (pvrdma_idx_valid(idx, max_elems))
		वापस idx & (max_elems - 1);
	वापस PVRDMA_INVALID_IDX;
पूर्ण

अटल अंतरभूत व्योम pvrdma_idx_ring_inc(atomic_t *var, __u32 max_elems)
अणु
	__u32 idx = atomic_पढ़ो(var) + 1;	/* Increment. */

	idx &= (max_elems << 1) - 1;		/* Modulo size, flip gen. */
	atomic_set(var, idx);
पूर्ण

अटल अंतरभूत __s32 pvrdma_idx_ring_has_space(स्थिर काष्ठा pvrdma_ring *r,
					      __u32 max_elems, __u32 *out_tail)
अणु
	स्थिर __u32 tail = atomic_पढ़ो(&r->prod_tail);
	स्थिर __u32 head = atomic_पढ़ो(&r->cons_head);

	अगर (pvrdma_idx_valid(tail, max_elems) &&
	    pvrdma_idx_valid(head, max_elems)) अणु
		*out_tail = tail & (max_elems - 1);
		वापस tail != (head ^ max_elems);
	पूर्ण
	वापस PVRDMA_INVALID_IDX;
पूर्ण

अटल अंतरभूत __s32 pvrdma_idx_ring_has_data(स्थिर काष्ठा pvrdma_ring *r,
					     __u32 max_elems, __u32 *out_head)
अणु
	स्थिर __u32 tail = atomic_पढ़ो(&r->prod_tail);
	स्थिर __u32 head = atomic_पढ़ो(&r->cons_head);

	अगर (pvrdma_idx_valid(tail, max_elems) &&
	    pvrdma_idx_valid(head, max_elems)) अणु
		*out_head = head & (max_elems - 1);
		वापस tail != head;
	पूर्ण
	वापस PVRDMA_INVALID_IDX;
पूर्ण

#पूर्ण_अगर /* __PVRDMA_RING_H__ */
