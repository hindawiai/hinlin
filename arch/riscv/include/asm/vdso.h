<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Limited
 * Copyright (C) 2014 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 */

#अगर_अघोषित _ASM_RISCV_VDSO_H
#घोषणा _ASM_RISCV_VDSO_H

#समावेश <linux/types.h>

#अगर_अघोषित CONFIG_GENERIC_TIME_VSYSCALL
काष्ठा vdso_data अणु
पूर्ण;
#पूर्ण_अगर

/*
 * The VDSO symbols are mapped पूर्णांकo Linux so we can just use regular symbol
 * addressing to get their offsets in userspace.  The symbols are mapped at an
 * offset of 0, but since the linker must support setting weak undefined
 * symbols to the असलolute address 0 it also happens to support other low
 * addresses even when the code model suggests those low addresses would not
 * otherwise be availiable.
 */
#घोषणा VDSO_SYMBOL(base, name)							\
(अणु										\
	बाह्य स्थिर अक्षर __vdso_##name[];					\
	(व्योम __user *)((अचिन्हित दीर्घ)(base) + __vdso_##name);			\
पूर्ण)

यंत्रlinkage दीर्घ sys_riscv_flush_icache(uपूर्णांकptr_t, uपूर्णांकptr_t, uपूर्णांकptr_t);

#पूर्ण_अगर /* _ASM_RISCV_VDSO_H */
