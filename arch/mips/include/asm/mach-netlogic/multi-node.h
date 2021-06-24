<शैली गुरु>
/*
 * Copyright (c) 2003-2012 Broadcom Corporation
 * All Rights Reserved
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the Broadcom
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY BROADCOM ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BROADCOM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _NETLOGIC_MULTI_NODE_H_
#घोषणा _NETLOGIC_MULTI_NODE_H_

#अगर_अघोषित CONFIG_NLM_MULTINODE
#घोषणा NLM_NR_NODES		1
#अन्यथा
#अगर defined(CONFIG_NLM_MULTINODE_2)
#घोषणा NLM_NR_NODES		2
#या_अगर defined(CONFIG_NLM_MULTINODE_4)
#घोषणा NLM_NR_NODES		4
#अन्यथा
#घोषणा NLM_NR_NODES		1
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा NLM_THREADS_PER_CORE	4

काष्ठा nlm_soc_info अणु
	अचिन्हित दीर्घ	coremask;	/* cores enabled on the soc */
	अचिन्हित दीर्घ	ebase;		/* not used now */
	uपूर्णांक64_t	irqmask;	/* EIMR क्रम the node */
	uपूर्णांक64_t	sysbase;	/* only क्रम XLP - sys block base */
	uपूर्णांक64_t	picbase;	/* PIC block base */
	spinlock_t	piघड़ी;	/* lock क्रम PIC access */
	cpumask_t	cpumask;	/* logical cpu mask क्रम node */
	अचिन्हित पूर्णांक	socbus;
पूर्ण;

बाह्य काष्ठा nlm_soc_info nlm_nodes[NLM_NR_NODES];
#घोषणा nlm_get_node(i)		(&nlm_nodes[i])
#घोषणा nlm_node_present(n)	((n) >= 0 && (n) < NLM_NR_NODES && \
					nlm_get_node(n)->coremask != 0)
#अगर_घोषित CONFIG_CPU_XLR
#घोषणा nlm_current_node()	(&nlm_nodes[0])
#अन्यथा
#घोषणा nlm_current_node()	(&nlm_nodes[nlm_nodeid()])
#पूर्ण_अगर
व्योम nlm_node_init(पूर्णांक node);

#पूर्ण_अगर
