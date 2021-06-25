<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_SPARC64_PERCPU__
#घोषणा __ARCH_SPARC64_PERCPU__

#समावेश <linux/compiler.h>

#अगर_अघोषित BUILD_VDSO
रेजिस्टर अचिन्हित दीर्घ __local_per_cpu_offset यंत्र("g5");
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP

#समावेश <यंत्र/trap_block.h>

#घोषणा __per_cpu_offset(__cpu) \
	(trap_block[(__cpu)].__per_cpu_base)
#घोषणा per_cpu_offset(x) (__per_cpu_offset(x))

#घोषणा __my_cpu_offset __local_per_cpu_offset

#अन्यथा /* ! SMP */

#पूर्ण_अगर	/* SMP */

#समावेश <यंत्र-generic/percpu.h>

#पूर्ण_अगर /* __ARCH_SPARC64_PERCPU__ */
