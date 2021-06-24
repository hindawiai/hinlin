<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __ASM_VDSO_PROCESSOR_H
#घोषणा __ASM_VDSO_PROCESSOR_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/barrier.h>

अटल अंतरभूत व्योम cpu_relax(व्योम)
अणु
#अगर_घोषित __riscv_muद_भाग
	पूर्णांक dummy;
	/* In lieu of a halt inकाष्ठाion, induce a दीर्घ-latency stall. */
	__यंत्र__ __अस्थिर__ ("div %0, %0, zero" : "=r" (dummy));
#पूर्ण_अगर
	barrier();
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_PROCESSOR_H */
