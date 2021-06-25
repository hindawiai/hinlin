<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* System call table क्रम x32 ABI. */

#समावेश <linux/linkage.h>
#समावेश <linux/sys.h>
#समावेश <linux/cache.h>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/syscall.h>

/*
 * Reuse the 64-bit entry poपूर्णांकs क्रम the x32 versions that occupy dअगरferent
 * slots in the syscall table.
 */
#घोषणा __x32_sys_पढ़ोv		__x64_sys_पढ़ोv
#घोषणा __x32_sys_ग_लिखोv	__x64_sys_ग_लिखोv
#घोषणा __x32_sys_माला_लोockopt	__x64_sys_माला_लोockopt
#घोषणा __x32_sys_setsockopt	__x64_sys_setsockopt
#घोषणा __x32_sys_vmsplice	__x64_sys_vmsplice
#घोषणा __x32_sys_process_vm_पढ़ोv	__x64_sys_process_vm_पढ़ोv
#घोषणा __x32_sys_process_vm_ग_लिखोv	__x64_sys_process_vm_ग_लिखोv

#घोषणा __SYSCALL_64(nr, sym)

#घोषणा __SYSCALL_X32(nr, sym) बाह्य दीर्घ __x32_##sym(स्थिर काष्ठा pt_regs *);
#घोषणा __SYSCALL_COMMON(nr, sym) बाह्य दीर्घ __x64_##sym(स्थिर काष्ठा pt_regs *);
#समावेश <यंत्र/syscalls_64.h>
#अघोषित __SYSCALL_X32
#अघोषित __SYSCALL_COMMON

#घोषणा __SYSCALL_X32(nr, sym) [nr] = __x32_##sym,
#घोषणा __SYSCALL_COMMON(nr, sym) [nr] = __x64_##sym,

यंत्रlinkage स्थिर sys_call_ptr_t x32_sys_call_table[__NR_x32_syscall_max+1] = अणु
	/*
	 * Smells like a compiler bug -- it करोesn't work
	 * when the & below is हटाओd.
	 */
	[0 ... __NR_x32_syscall_max] = &__x64_sys_ni_syscall,
#समावेश <यंत्र/syscalls_64.h>
पूर्ण;
