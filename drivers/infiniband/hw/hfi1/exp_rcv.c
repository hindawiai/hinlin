<शैली गुरु>
/*
 * Copyright(c) 2017 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश "exp_rcv.h"
#समावेश "trace.h"

/**
 * hfi1_exp_tid_set_init - initialize exp_tid_set
 * @set: the set
 */
अटल व्योम hfi1_exp_tid_set_init(काष्ठा exp_tid_set *set)
अणु
	INIT_LIST_HEAD(&set->list);
	set->count = 0;
पूर्ण

/**
 * hfi1_exp_tid_group_init - initialize rcd expected receive
 * @rcd: the rcd
 */
व्योम hfi1_exp_tid_group_init(काष्ठा hfi1_ctxtdata *rcd)
अणु
	hfi1_exp_tid_set_init(&rcd->tid_group_list);
	hfi1_exp_tid_set_init(&rcd->tid_used_list);
	hfi1_exp_tid_set_init(&rcd->tid_full_list);
पूर्ण

/**
 * hfi1_alloc_ctxt_rcv_groups - initialize expected receive groups
 * @rcd: the context to add the groupings to
 */
पूर्णांक hfi1_alloc_ctxt_rcv_groups(काष्ठा hfi1_ctxtdata *rcd)
अणु
	काष्ठा hfi1_devdata *dd = rcd->dd;
	u32 tidbase;
	काष्ठा tid_group *grp;
	पूर्णांक i;
	u32 ngroups;

	ngroups = rcd->expected_count / dd->rcv_entries.group_size;
	rcd->groups =
		kसुस्मृति_node(ngroups, माप(*rcd->groups),
			     GFP_KERNEL, rcd->numa_id);
	अगर (!rcd->groups)
		वापस -ENOMEM;
	tidbase = rcd->expected_base;
	क्रम (i = 0; i < ngroups; i++) अणु
		grp = &rcd->groups[i];
		grp->size = dd->rcv_entries.group_size;
		grp->base = tidbase;
		tid_group_add_tail(grp, &rcd->tid_group_list);
		tidbase += dd->rcv_entries.group_size;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hfi1_मुक्त_ctxt_rcv_groups - मुक्त  expected receive groups
 * @rcd: the context to मुक्त
 *
 * The routine dismantles the expect receive linked
 * list and clears any tids associated with the receive
 * context.
 *
 * This should only be called क्रम kernel contexts and the
 * a base user context.
 */
व्योम hfi1_मुक्त_ctxt_rcv_groups(काष्ठा hfi1_ctxtdata *rcd)
अणु
	kमुक्त(rcd->groups);
	rcd->groups = शून्य;
	hfi1_exp_tid_group_init(rcd);

	hfi1_clear_tids(rcd);
पूर्ण
