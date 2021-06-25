<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_POWERPC_SYSCALLS_H
#घोषणा __ASM_POWERPC_SYSCALLS_H
#अगर_घोषित __KERNEL__

#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>
#समावेश <linux/types.h>

काष्ठा rtas_args;

यंत्रlinkage दीर्घ sys_mmap(अचिन्हित दीर्घ addr, माप_प्रकार len,
		अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
		अचिन्हित दीर्घ fd, off_t offset);
यंत्रlinkage दीर्घ sys_mmap2(अचिन्हित दीर्घ addr, माप_प्रकार len,
		अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
		अचिन्हित दीर्घ fd, अचिन्हित दीर्घ pgoff);
यंत्रlinkage दीर्घ ppc64_personality(अचिन्हित दीर्घ personality);
यंत्रlinkage दीर्घ sys_rtas(काष्ठा rtas_args __user *uargs);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __ASM_POWERPC_SYSCALLS_H */
