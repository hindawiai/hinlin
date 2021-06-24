<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/mman.h>
#समावेश <linux/file.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/ipc.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/syscalls.h>

/*
 * sys_pipe() is the normal C calling standard क्रम creating
 * a pipe. It's not the way Unix traditionally करोes this, though.
 */
यंत्रlinkage पूर्णांक sys_sh_pipe(व्योम)
अणु
	पूर्णांक fd[2];
	पूर्णांक error;

	error = करो_pipe_flags(fd, 0);
	अगर (!error) अणु
		current_pt_regs()->regs[1] = fd[1];
		वापस fd[0];
	पूर्ण
	वापस error;
पूर्ण

यंत्रlinkage sमाप_प्रकार sys_pपढ़ो_wrapper(अचिन्हित पूर्णांक fd, अक्षर __user *buf,
			     माप_प्रकार count, दीर्घ dummy, loff_t pos)
अणु
	वापस ksys_pपढ़ो64(fd, buf, count, pos);
पूर्ण

यंत्रlinkage sमाप_प्रकार sys_pग_लिखो_wrapper(अचिन्हित पूर्णांक fd, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, दीर्घ dummy, loff_t pos)
अणु
	वापस ksys_pग_लिखो64(fd, buf, count, pos);
पूर्ण

यंत्रlinkage पूर्णांक sys_fadvise64_64_wrapper(पूर्णांक fd, u32 offset0, u32 offset1,
				u32 len0, u32 len1, पूर्णांक advice)
अणु
#अगर_घोषित  __LITTLE_ENDIAN__
	वापस ksys_fadvise64_64(fd, (u64)offset1 << 32 | offset0,
				 (u64)len1 << 32 | len0, advice);
#अन्यथा
	वापस ksys_fadvise64_64(fd, (u64)offset0 << 32 | offset1,
				 (u64)len0 << 32 | len1, advice);
#पूर्ण_अगर
पूर्ण
