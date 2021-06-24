<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * X86 specअगरic ACPICA environments and implementation
 *
 * Copyright (C) 2014, Intel Corporation
 *   Author: Lv Zheng <lv.zheng@पूर्णांकel.com>
 */

#अगर_अघोषित _ASM_X86_ACENV_H
#घोषणा _ASM_X86_ACENV_H

#समावेश <यंत्र/special_insns.h>

/* Asm macros */

#घोषणा ACPI_FLUSH_CPU_CACHE()	wbinvd()

पूर्णांक __acpi_acquire_global_lock(अचिन्हित पूर्णांक *lock);
पूर्णांक __acpi_release_global_lock(अचिन्हित पूर्णांक *lock);

#घोषणा ACPI_ACQUIRE_GLOBAL_LOCK(facs, Acq) \
	((Acq) = __acpi_acquire_global_lock(&facs->global_lock))

#घोषणा ACPI_RELEASE_GLOBAL_LOCK(facs, Acq) \
	((Acq) = __acpi_release_global_lock(&facs->global_lock))

/*
 * Math helper यंत्र macros
 */
#घोषणा ACPI_DIV_64_BY_32(n_hi, n_lo, d32, q32, r32) \
	यंत्र("divl %2;"				     \
	    : "=a"(q32), "=d"(r32)		     \
	    : "r"(d32),				     \
	     "0"(n_lo), "1"(n_hi))

#घोषणा ACPI_SHIFT_RIGHT_64(n_hi, n_lo) \
	यंत्र("shrl   $1,%2	;"	\
	    "rcrl   $1,%3;"		\
	    : "=r"(n_hi), "=r"(n_lo)	\
	    : "0"(n_hi), "1"(n_lo))

#पूर्ण_अगर /* _ASM_X86_ACENV_H */
