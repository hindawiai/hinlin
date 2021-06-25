<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vvar.h: Shared vDSO/kernel variable declarations
 * Copyright (c) 2011 Andy Lutomirski
 *
 * A handful of variables are accessible (पढ़ो-only) from userspace
 * code in the vsyscall page and the vdso.  They are declared here.
 * Some other file must define them with DEFINE_VVAR.
 *
 * In normal kernel code, they are used like any other variable.
 * In user code, they are accessed through the VVAR macro.
 *
 * These variables live in a page of kernel data that has an extra RO
 * mapping क्रम userspace.  Each variable needs a unique offset within
 * that page; specअगरy that offset with the DECLARE_VVAR macro.  (If
 * you mess up, the linker will catch it.)
 */

#अगर_अघोषित _ASM_X86_VVAR_H
#घोषणा _ASM_X86_VVAR_H

#अगर_घोषित EMIT_VVAR
/*
 * EMIT_VVAR() is used by the kernel linker script to put vvars in the
 * right place. Also, it's used by kernel code to import offsets values.
 */
#घोषणा DECLARE_VVAR(offset, type, name) \
	EMIT_VVAR(name, offset)

#अन्यथा

बाह्य अक्षर __vvar_page;

#घोषणा DECLARE_VVAR(offset, type, name)				\
	बाह्य type vvar_ ## name[CS_BASES]				\
	__attribute__((visibility("hidden")));				\
	बाह्य type समयns_ ## name[CS_BASES]				\
	__attribute__((visibility("hidden")));				\

#घोषणा VVAR(name) (vvar_ ## name)
#घोषणा TIMENS(name) (समयns_ ## name)

#घोषणा DEFINE_VVAR(type, name)						\
	type name[CS_BASES]						\
	__attribute__((section(".vvar_" #name), aligned(16))) __visible

#पूर्ण_अगर

/* DECLARE_VVAR(offset, type, name) */

DECLARE_VVAR(128, काष्ठा vdso_data, _vdso_data)

#अघोषित DECLARE_VVAR

#पूर्ण_अगर
