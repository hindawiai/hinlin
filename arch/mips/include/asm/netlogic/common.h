<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
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
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _NETLOGIC_COMMON_H_
#घोषणा _NETLOGIC_COMMON_H_

/*
 * Common SMP definitions
 */
#घोषणा RESET_VEC_PHYS		0x1fc00000
#घोषणा RESET_VEC_SIZE		8192		/* 8KB reset code and data */
#घोषणा RESET_DATA_PHYS		(RESET_VEC_PHYS + (1<<10))

/* Offsets of parameters in the RESET_DATA_PHYS area */
#घोषणा BOOT_THREAD_MODE	0
#घोषणा BOOT_NMI_LOCK		4
#घोषणा BOOT_NMI_HANDLER	8

/* CPU पढ़ोy flags क्रम each CPU */
#घोषणा BOOT_CPU_READY		2048

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/cpumask.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-netlogic/multi-node.h>

काष्ठा irq_desc;
व्योम nlm_smp_function_ipi_handler(काष्ठा irq_desc *desc);
व्योम nlm_smp_resched_ipi_handler(काष्ठा irq_desc *desc);
व्योम nlm_smp_irq_init(पूर्णांक hwcpuid);
व्योम nlm_boot_secondary_cpus(व्योम);
पूर्णांक nlm_wakeup_secondary_cpus(व्योम);
व्योम nlm_rmiboot_preboot(व्योम);
व्योम nlm_percpu_init(पूर्णांक hwcpuid);

अटल अंतरभूत व्योम *
nlm_get_boot_data(पूर्णांक offset)
अणु
	वापस (व्योम *)(CKSEG1ADDR(RESET_DATA_PHYS) + offset);
पूर्ण

अटल अंतरभूत व्योम
nlm_set_nmi_handler(व्योम *handler)
अणु
	व्योम *nmih = nlm_get_boot_data(BOOT_NMI_HANDLER);

	*(पूर्णांक64_t *)nmih = (दीर्घ)handler;
पूर्ण

/*
 * Misc.
 */
व्योम nlm_init_boot_cpu(व्योम);
अचिन्हित पूर्णांक nlm_get_cpu_frequency(व्योम);
बाह्य स्थिर काष्ठा plat_smp_ops nlm_smp_ops;
बाह्य अक्षर nlm_reset_entry[], nlm_reset_entry_end[];

बाह्य अचिन्हित पूर्णांक nlm_thपढ़ोs_per_core;
बाह्य cpumask_t nlm_cpumask;

काष्ठा irq_data;
uपूर्णांक64_t nlm_pci_irqmask(पूर्णांक node);
व्योम nlm_setup_pic_irq(पूर्णांक node, पूर्णांक picirq, पूर्णांक irq, पूर्णांक irt);
व्योम nlm_set_pic_extra_ack(पूर्णांक node, पूर्णांक irq,  व्योम (*xack)(काष्ठा irq_data *));

#अगर_घोषित CONFIG_PCI_MSI
व्योम nlm_dispatch_msi(पूर्णांक node, पूर्णांक lirq);
व्योम nlm_dispatch_msix(पूर्णांक node, पूर्णांक msixirq);
#पूर्ण_अगर

/*
 * The NR_IRQs is भागided between nodes, each of them has a separate irq space
 */
अटल अंतरभूत पूर्णांक nlm_irq_to_xirq(पूर्णांक node, पूर्णांक irq)
अणु
	वापस node * NR_IRQS / NLM_NR_NODES + irq;
पूर्ण

#अगर_घोषित CONFIG_CPU_XLR
#घोषणा nlm_cores_per_node()	8
#अन्यथा
अटल अंतरभूत पूर्णांक nlm_cores_per_node(व्योम)
अणु
	वापस ((पढ़ो_c0_prid() & PRID_IMP_MASK)
				== PRID_IMP_NETLOGIC_XLP9XX) ? 32 : 8;
पूर्ण
#पूर्ण_अगर
अटल अंतरभूत पूर्णांक nlm_thपढ़ोs_per_node(व्योम)
अणु
	वापस nlm_cores_per_node() * NLM_THREADS_PER_CORE;
पूर्ण

अटल अंतरभूत पूर्णांक nlm_hwtid_to_node(पूर्णांक hwtid)
अणु
	वापस hwtid / nlm_thपढ़ोs_per_node();
पूर्ण

बाह्य पूर्णांक nlm_cpu_पढ़ोy[];
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _NETLOGIC_COMMON_H_ */
