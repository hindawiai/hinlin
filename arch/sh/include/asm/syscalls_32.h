<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_SYSCALLS_32_H
#घोषणा __ASM_SH_SYSCALLS_32_H

#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>
#समावेश <linux/types.h>

काष्ठा pt_regs;

यंत्रlinkage पूर्णांक sys_sigवापस(व्योम);
यंत्रlinkage पूर्णांक sys_rt_sigवापस(व्योम);
यंत्रlinkage पूर्णांक sys_sh_pipe(व्योम);
यंत्रlinkage sमाप_प्रकार sys_pपढ़ो_wrapper(अचिन्हित पूर्णांक fd, अक्षर __user *buf,
				     माप_प्रकार count, दीर्घ dummy, loff_t pos);
यंत्रlinkage sमाप_प्रकार sys_pग_लिखो_wrapper(अचिन्हित पूर्णांक fd, स्थिर अक्षर __user *buf,
				      माप_प्रकार count, दीर्घ dummy, loff_t pos);
यंत्रlinkage पूर्णांक sys_fadvise64_64_wrapper(पूर्णांक fd, u32 offset0, u32 offset1,
					u32 len0, u32 len1, पूर्णांक advice);

/* Misc syscall related bits */
यंत्रlinkage दीर्घ करो_syscall_trace_enter(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम करो_syscall_trace_leave(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक save_r0,
				 अचिन्हित दीर्घ thपढ़ो_info_flags);

#पूर्ण_अगर /* __ASM_SH_SYSCALLS_32_H */
