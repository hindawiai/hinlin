<शैली गुरु>
/*
 * Copyright(c) 2015 - 2020 Intel Corporation.
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
#अगर_अघोषित _HFI1_AFFINITY_H
#घोषणा _HFI1_AFFINITY_H

#समावेश "hfi.h"

क्रमागत irq_type अणु
	IRQ_SDMA,
	IRQ_RCVCTXT,
	IRQ_NETDEVCTXT,
	IRQ_GENERAL,
	IRQ_OTHER
पूर्ण;

/* Can be used क्रम both memory and cpu */
क्रमागत affinity_flags अणु
	AFF_AUTO,
	AFF_NUMA_LOCAL,
	AFF_DEV_LOCAL,
	AFF_IRQ_LOCAL
पूर्ण;

काष्ठा cpu_mask_set अणु
	काष्ठा cpumask mask;
	काष्ठा cpumask used;
	uपूर्णांक gen;
पूर्ण;

काष्ठा hfi1_msix_entry;

/* Initialize non-HT cpu cores mask */
व्योम init_real_cpu_mask(व्योम);
/* Initialize driver affinity data */
पूर्णांक hfi1_dev_affinity_init(काष्ठा hfi1_devdata *dd);
/*
 * Set IRQ affinity to a CPU. The function will determine the
 * CPU and set the affinity to it.
 */
पूर्णांक hfi1_get_irq_affinity(काष्ठा hfi1_devdata *dd,
			  काष्ठा hfi1_msix_entry *msix);
/*
 * Remove the IRQ's CPU affinity. This function also updates
 * any पूर्णांकernal CPU tracking data
 */
व्योम hfi1_put_irq_affinity(काष्ठा hfi1_devdata *dd,
			   काष्ठा hfi1_msix_entry *msix);
/*
 * Determine a CPU affinity क्रम a user process, अगर the process करोes not
 * have an affinity set yet.
 */
पूर्णांक hfi1_get_proc_affinity(पूर्णांक node);
/* Release a CPU used by a user process. */
व्योम hfi1_put_proc_affinity(पूर्णांक cpu);

काष्ठा hfi1_affinity_node अणु
	पूर्णांक node;
	u16 __percpu *comp_vect_affinity;
	काष्ठा cpu_mask_set def_पूर्णांकr;
	काष्ठा cpu_mask_set rcv_पूर्णांकr;
	काष्ठा cpumask general_पूर्णांकr_mask;
	काष्ठा cpumask comp_vect_mask;
	काष्ठा list_head list;
पूर्ण;

काष्ठा hfi1_affinity_node_list अणु
	काष्ठा list_head list;
	काष्ठा cpumask real_cpu_mask;
	काष्ठा cpu_mask_set proc;
	पूर्णांक num_core_siblings;
	पूर्णांक num_possible_nodes;
	पूर्णांक num_online_nodes;
	पूर्णांक num_online_cpus;
	काष्ठा mutex lock; /* protects affinity nodes */
पूर्ण;

पूर्णांक node_affinity_init(व्योम);
व्योम node_affinity_destroy_all(व्योम);
बाह्य काष्ठा hfi1_affinity_node_list node_affinity;
व्योम hfi1_dev_affinity_clean_up(काष्ठा hfi1_devdata *dd);
पूर्णांक hfi1_comp_vect_mappings_lookup(काष्ठा rvt_dev_info *rdi, पूर्णांक comp_vect);
पूर्णांक hfi1_comp_vectors_set_up(काष्ठा hfi1_devdata *dd);
व्योम hfi1_comp_vectors_clean_up(काष्ठा hfi1_devdata *dd);

#पूर्ण_अगर /* _HFI1_AFFINITY_H */
