<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_CMP_H
#घोषणा _ASM_CMP_H

/*
 * Definitions क्रम CMP multitasking on MIPS cores
 */
काष्ठा task_काष्ठा;

बाह्य व्योम cmp_smp_setup(व्योम);
बाह्य व्योम cmp_smp_finish(व्योम);
बाह्य व्योम cmp_boot_secondary(पूर्णांक cpu, काष्ठा task_काष्ठा *t);
बाह्य व्योम cmp_init_secondary(व्योम);
बाह्य व्योम cmp_prepare_cpus(अचिन्हित पूर्णांक max_cpus);

/* This is platक्रमm specअगरic */
बाह्य व्योम cmp_send_ipi(पूर्णांक cpu, अचिन्हित पूर्णांक action);
#पूर्ण_अगर /*  _ASM_CMP_H */
