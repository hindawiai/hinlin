<शैली गुरु>
/*
 * Copyright(c) 2020 Cornelis Networks, Inc.
 * Copyright(c) 2016 Intel Corporation.
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
#अगर_अघोषित _HFI1_MMU_RB_H
#घोषणा _HFI1_MMU_RB_H

#समावेश "hfi.h"

काष्ठा mmu_rb_node अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ len;
	अचिन्हित दीर्घ __last;
	काष्ठा rb_node node;
	काष्ठा mmu_rb_handler *handler;
	काष्ठा list_head list;
पूर्ण;

/*
 * NOTE: filter, insert, invalidate, and evict must not sleep.  Only हटाओ is
 * allowed to sleep.
 */
काष्ठा mmu_rb_ops अणु
	bool (*filter)(काष्ठा mmu_rb_node *node, अचिन्हित दीर्घ addr,
		       अचिन्हित दीर्घ len);
	पूर्णांक (*insert)(व्योम *ops_arg, काष्ठा mmu_rb_node *mnode);
	व्योम (*हटाओ)(व्योम *ops_arg, काष्ठा mmu_rb_node *mnode);
	पूर्णांक (*invalidate)(व्योम *ops_arg, काष्ठा mmu_rb_node *node);
	पूर्णांक (*evict)(व्योम *ops_arg, काष्ठा mmu_rb_node *mnode,
		     व्योम *evict_arg, bool *stop);
पूर्ण;

काष्ठा mmu_rb_handler अणु
	काष्ठा mmu_notअगरier mn;
	काष्ठा rb_root_cached root;
	व्योम *ops_arg;
	spinlock_t lock;        /* protect the RB tree */
	काष्ठा mmu_rb_ops *ops;
	काष्ठा list_head lru_list;
	काष्ठा work_काष्ठा del_work;
	काष्ठा list_head del_list;
	काष्ठा workqueue_काष्ठा *wq;
पूर्ण;

पूर्णांक hfi1_mmu_rb_रेजिस्टर(व्योम *ops_arg,
			 काष्ठा mmu_rb_ops *ops,
			 काष्ठा workqueue_काष्ठा *wq,
			 काष्ठा mmu_rb_handler **handler);
व्योम hfi1_mmu_rb_unरेजिस्टर(काष्ठा mmu_rb_handler *handler);
पूर्णांक hfi1_mmu_rb_insert(काष्ठा mmu_rb_handler *handler,
		       काष्ठा mmu_rb_node *mnode);
व्योम hfi1_mmu_rb_evict(काष्ठा mmu_rb_handler *handler, व्योम *evict_arg);
व्योम hfi1_mmu_rb_हटाओ(काष्ठा mmu_rb_handler *handler,
			काष्ठा mmu_rb_node *mnode);
bool hfi1_mmu_rb_हटाओ_unless_exact(काष्ठा mmu_rb_handler *handler,
				     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				     काष्ठा mmu_rb_node **rb_node);

#पूर्ण_अगर /* _HFI1_MMU_RB_H */
