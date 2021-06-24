<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 ARM Ltd.
 */
#अगर_अघोषित __ASM_VDSO_PROCESSOR_H
#घोषणा __ASM_VDSO_PROCESSOR_H

#अगर_अघोषित __ASSEMBLY__

#अगर __LINUX_ARM_ARCH__ == 6 || defined(CONFIG_ARM_ERRATA_754327)
#घोषणा cpu_relax()						\
	करो अणु							\
		smp_mb();					\
		__यंत्र__ __अस्थिर__("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;");	\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा cpu_relax()			barrier()
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_PROCESSOR_H */
