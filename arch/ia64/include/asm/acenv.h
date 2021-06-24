<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * IA64 specअगरic ACPICA environments and implementation
 *
 * Copyright (C) 2014, Intel Corporation
 *   Author: Lv Zheng <lv.zheng@पूर्णांकel.com>
 */

#अगर_अघोषित _ASM_IA64_ACENV_H
#घोषणा _ASM_IA64_ACENV_H

#समावेश <यंत्र/पूर्णांकrinsics.h>

#घोषणा COMPILER_DEPENDENT_INT64	दीर्घ
#घोषणा COMPILER_DEPENDENT_UINT64	अचिन्हित दीर्घ

/* Asm macros */

अटल अंतरभूत पूर्णांक
ia64_acpi_acquire_global_lock(अचिन्हित पूर्णांक *lock)
अणु
	अचिन्हित पूर्णांक old, new, val;
	करो अणु
		old = *lock;
		new = (((old & ~0x3) + 2) + ((old >> 1) & 0x1));
		val = ia64_cmpxchg4_acq(lock, new, old);
	पूर्ण जबतक (unlikely (val != old));
	वापस (new < 3) ? -1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ia64_acpi_release_global_lock(अचिन्हित पूर्णांक *lock)
अणु
	अचिन्हित पूर्णांक old, new, val;
	करो अणु
		old = *lock;
		new = old & ~0x3;
		val = ia64_cmpxchg4_acq(lock, new, old);
	पूर्ण जबतक (unlikely (val != old));
	वापस old & 0x1;
पूर्ण

#घोषणा ACPI_ACQUIRE_GLOBAL_LOCK(facs, Acq)				\
	((Acq) = ia64_acpi_acquire_global_lock(&facs->global_lock))

#घोषणा ACPI_RELEASE_GLOBAL_LOCK(facs, Acq)				\
	((Acq) = ia64_acpi_release_global_lock(&facs->global_lock))

#पूर्ण_अगर /* _ASM_IA64_ACENV_H */
