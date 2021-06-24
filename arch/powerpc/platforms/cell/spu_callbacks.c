<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * System call callback functions क्रम SPUs
 */

#अघोषित DEBUG

#समावेश <linux/kallsyms.h>
#समावेश <linux/export.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/syscalls.h>
#समावेश <यंत्र/unistd.h>

/*
 * This table defines the प्रणाली calls that an SPU can call.
 * It is currently a subset of the 64 bit घातerpc प्रणाली calls,
 * with the exact semantics.
 *
 * The reasons क्रम disabling some of the प्रणाली calls are:
 * 1. They पूर्णांकeract with the way SPU syscalls are handled
 *    and we can't let them execute ever:
 *	restart_syscall, निकास, क्रम, execve, ptrace, ...
 * 2. They are deprecated and replaced by other means:
 *	uselib, pciconfig_*, sysfs, ...
 * 3. They are somewhat पूर्णांकeracting with the प्रणाली in a way
 *    we करोn't want an SPU to:
 *	reboot, init_module, mount, kexec_load
 * 4. They are optional and we can't rely on them being
 *    linked पूर्णांकo the kernel. Unक्रमtunately, the cond_syscall
 *    helper करोes not work here as it करोes not add the necessary
 *    opd symbols:
 *	mbind, mq_खोलो, ipc, ...
 */

अटल व्योम *spu_syscall_table[] = अणु
#घोषणा __SYSCALL_WITH_COMPAT(nr, entry, compat) __SYSCALL(nr, entry)
#घोषणा __SYSCALL(nr, entry) [nr] = entry,
#समावेश <यंत्र/syscall_table_spu.h>
पूर्ण;

दीर्घ spu_sys_callback(काष्ठा spu_syscall_block *s)
अणु
	दीर्घ (*syscall)(u64 a1, u64 a2, u64 a3, u64 a4, u64 a5, u64 a6);

	अगर (s->nr_ret >= ARRAY_SIZE(spu_syscall_table)) अणु
		pr_debug("%s: invalid syscall #%lld", __func__, s->nr_ret);
		वापस -ENOSYS;
	पूर्ण

	syscall = spu_syscall_table[s->nr_ret];

	pr_debug("SPU-syscall "
		 "%pSR:syscall%lld(%llx, %llx, %llx, %llx, %llx, %llx)\n",
		 syscall,
		 s->nr_ret,
		 s->parm[0], s->parm[1], s->parm[2],
		 s->parm[3], s->parm[4], s->parm[5]);

	वापस syscall(s->parm[0], s->parm[1], s->parm[2],
		       s->parm[3], s->parm[4], s->parm[5]);
पूर्ण
EXPORT_SYMBOL_GPL(spu_sys_callback);
