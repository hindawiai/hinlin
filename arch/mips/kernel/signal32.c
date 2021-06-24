<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1991, 1992  Linus Torvalds
 * Copyright (C) 1994 - 2000, 2006  Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2016, Imagination Technologies Ltd.
 */
#समावेश <linux/compat.h>
#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/compat-संकेत.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>

#समावेश "signal-common.h"

/* 32-bit compatibility types */

प्रकार अचिन्हित पूर्णांक __sighandler32_t;
प्रकार व्योम (*vfptr_t)(व्योम);

/*
 * Atomically swap in the new संकेत mask, and रुको क्रम a संकेत.
 */

यंत्रlinkage पूर्णांक sys32_संक_रोको(compat_sigset_t __user *uset)
अणु
	वापस compat_sys_rt_संक_रोको(uset, माप(compat_sigset_t));
पूर्ण

SYSCALL_DEFINE3(32_sigaction, दीर्घ, sig, स्थिर काष्ठा compat_sigaction __user *, act,
	काष्ठा compat_sigaction __user *, oact)
अणु
	काष्ठा k_sigaction new_ka, old_ka;
	पूर्णांक ret;
	पूर्णांक err = 0;

	अगर (act) अणु
		old_sigset_t mask;
		s32 handler;

		अगर (!access_ok(act, माप(*act)))
			वापस -EFAULT;
		err |= __get_user(handler, &act->sa_handler);
		new_ka.sa.sa_handler = (व्योम __user *)(s64)handler;
		err |= __get_user(new_ka.sa.sa_flags, &act->sa_flags);
		err |= __get_user(mask, &act->sa_mask.sig[0]);
		अगर (err)
			वापस -EFAULT;

		siginitset(&new_ka.sa.sa_mask, mask);
	पूर्ण

	ret = करो_sigaction(sig, act ? &new_ka : शून्य, oact ? &old_ka : शून्य);

	अगर (!ret && oact) अणु
		अगर (!access_ok(oact, माप(*oact)))
			वापस -EFAULT;
		err |= __put_user(old_ka.sa.sa_flags, &oact->sa_flags);
		err |= __put_user((u32)(u64)old_ka.sa.sa_handler,
				  &oact->sa_handler);
		err |= __put_user(old_ka.sa.sa_mask.sig[0], oact->sa_mask.sig);
		err |= __put_user(0, &oact->sa_mask.sig[1]);
		err |= __put_user(0, &oact->sa_mask.sig[2]);
		err |= __put_user(0, &oact->sa_mask.sig[3]);
		अगर (err)
			वापस -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण
