<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_SYSCALLS_H
#घोषणा __ASM_GENERIC_SYSCALLS_H

#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>

/*
 * Calling conventions क्रम these प्रणाली calls can dअगरfer, so
 * it's possible to override them.
 */

#अगर_अघोषित sys_mmap2
यंत्रlinkage दीर्घ sys_mmap2(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
			अचिन्हित दीर्घ fd, अचिन्हित दीर्घ pgoff);
#पूर्ण_अगर

#अगर_अघोषित sys_mmap
यंत्रlinkage दीर्घ sys_mmap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
			अचिन्हित दीर्घ fd, off_t pgoff);
#पूर्ण_अगर

#अगर_अघोषित sys_rt_sigवापस
यंत्रlinkage दीर्घ sys_rt_sigवापस(काष्ठा pt_regs *regs);
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_GENERIC_SYSCALLS_H */
