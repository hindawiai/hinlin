<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_PERCPU_H_
#घोषणा _ASM_POWERPC_PERCPU_H_
#अगर_घोषित __घातerpc64__

/*
 * Same as यंत्र-generic/percpu.h, except that we store the per cpu offset
 * in the paca. Based on the x86-64 implementation.
 */

#अगर_घोषित CONFIG_SMP

#घोषणा __my_cpu_offset local_paca->data_offset

#पूर्ण_अगर /* CONFIG_SMP */
#पूर्ण_अगर /* __घातerpc64__ */

#समावेश <यंत्र-generic/percpu.h>

#समावेश <यंत्र/paca.h>

#पूर्ण_अगर /* _ASM_POWERPC_PERCPU_H_ */
