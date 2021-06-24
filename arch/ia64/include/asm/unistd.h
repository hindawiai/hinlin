<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * IA-64 Linux syscall numbers and अंतरभूत-functions.
 *
 * Copyright (C) 1998-2005 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */
#अगर_अघोषित _ASM_IA64_UNISTD_H
#घोषणा _ASM_IA64_UNISTD_H

#समावेश <uapi/यंत्र/unistd.h>

#घोषणा NR_syscalls		__NR_syscalls /* length of syscall table */

#घोषणा __ARCH_WANT_NEW_STAT
#घोषणा __ARCH_WANT_SYS_UTIME

#अगर !defined(__ASSEMBLY__) && !defined(ASSEMBLER)

#समावेश <linux/types.h>
#समावेश <linux/linkage.h>
#समावेश <linux/compiler.h>

बाह्य दीर्घ __ia64_syscall (दीर्घ a0, दीर्घ a1, दीर्घ a2, दीर्घ a3, दीर्घ a4, दीर्घ nr);

यंत्रlinkage अचिन्हित दीर्घ sys_mmap(
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				पूर्णांक prot, पूर्णांक flags,
				पूर्णांक fd, दीर्घ off);
यंत्रlinkage अचिन्हित दीर्घ sys_mmap2(
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				पूर्णांक prot, पूर्णांक flags,
				पूर्णांक fd, दीर्घ pgoff);
काष्ठा pt_regs;
यंत्रlinkage दीर्घ sys_ia64_pipe(व्योम);

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_IA64_UNISTD_H */
