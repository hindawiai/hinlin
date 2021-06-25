<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Dummy stubs used when CONFIG_POSIX_TIMERS=n
 *
 * Created by:  Nicolas Pitre, July 2016
 * Copyright:   (C) 2016 Linaro Limited
 */

#समावेश <linux/linkage.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/समयkeeping.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/समय_namespace.h>
#समावेश <linux/compat.h>

#अगर_घोषित CONFIG_ARCH_HAS_SYSCALL_WRAPPER
/* Architectures may override SYS_NI and COMPAT_SYS_NI */
#समावेश <यंत्र/syscall_wrapper.h>
#पूर्ण_अगर

यंत्रlinkage दीर्घ sys_ni_posix_समयrs(व्योम)
अणु
	pr_err_once("process %d (%s) attempted a POSIX timer syscall "
		    "while CONFIG_POSIX_TIMERS is not set\n",
		    current->pid, current->comm);
	वापस -ENOSYS;
पूर्ण

#अगर_अघोषित SYS_NI
#घोषणा SYS_NI(name)  SYSCALL_ALIAS(sys_##name, sys_ni_posix_समयrs)
#पूर्ण_अगर

#अगर_अघोषित COMPAT_SYS_NI
#घोषणा COMPAT_SYS_NI(name)  SYSCALL_ALIAS(compat_sys_##name, sys_ni_posix_समयrs)
#पूर्ण_अगर

SYS_NI(समयr_create);
SYS_NI(समयr_समय_लो);
SYS_NI(समयr_getoverrun);
SYS_NI(समयr_समय_रखो);
SYS_NI(समयr_delete);
SYS_NI(घड़ी_adjसमय);
SYS_NI(getiसमयr);
SYS_NI(setiसमयr);
SYS_NI(घड़ी_adjसमय32);
#अगर_घोषित __ARCH_WANT_SYS_ALARM
SYS_NI(alarm);
#पूर्ण_अगर

/*
 * We preserve minimal support क्रम CLOCK_REALTIME and CLOCK_MONOTONIC
 * as it is easy to reमुख्य compatible with little code. CLOCK_BOOTTIME
 * is also included क्रम convenience as at least प्रणालीd uses it.
 */

SYSCALL_DEFINE2(घड़ी_समय_रखो, स्थिर घड़ीid_t, which_घड़ी,
		स्थिर काष्ठा __kernel_बारpec __user *, tp)
अणु
	काष्ठा बारpec64 new_tp;

	अगर (which_घड़ी != CLOCK_REALTIME)
		वापस -EINVAL;
	अगर (get_बारpec64(&new_tp, tp))
		वापस -EFAULT;

	वापस करो_sys_समय_रखोofday64(&new_tp, शून्य);
पूर्ण

पूर्णांक करो_घड़ी_समय_लो(घड़ीid_t which_घड़ी, काष्ठा बारpec64 *tp)
अणु
	चयन (which_घड़ी) अणु
	हाल CLOCK_REALTIME:
		kसमय_get_real_ts64(tp);
		अवरोध;
	हाल CLOCK_MONOTONIC:
		kसमय_get_ts64(tp);
		समयns_add_monotonic(tp);
		अवरोध;
	हाल CLOCK_BOOTTIME:
		kसमय_get_bootसमय_प्रकारs64(tp);
		समयns_add_bootसमय(tp);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
SYSCALL_DEFINE2(घड़ी_समय_लो, स्थिर घड़ीid_t, which_घड़ी,
		काष्ठा __kernel_बारpec __user *, tp)
अणु
	पूर्णांक ret;
	काष्ठा बारpec64 kernel_tp;

	ret = करो_घड़ी_समय_लो(which_घड़ी, &kernel_tp);
	अगर (ret)
		वापस ret;

	अगर (put_बारpec64(&kernel_tp, tp))
		वापस -EFAULT;
	वापस 0;
पूर्ण

SYSCALL_DEFINE2(घड़ी_getres, स्थिर घड़ीid_t, which_घड़ी, काष्ठा __kernel_बारpec __user *, tp)
अणु
	काष्ठा बारpec64 rtn_tp = अणु
		.tv_sec = 0,
		.tv_nsec = hrसमयr_resolution,
	पूर्ण;

	चयन (which_घड़ी) अणु
	हाल CLOCK_REALTIME:
	हाल CLOCK_MONOTONIC:
	हाल CLOCK_BOOTTIME:
		अगर (put_बारpec64(&rtn_tp, tp))
			वापस -EFAULT;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

SYSCALL_DEFINE4(घड़ी_nanosleep, स्थिर घड़ीid_t, which_घड़ी, पूर्णांक, flags,
		स्थिर काष्ठा __kernel_बारpec __user *, rqtp,
		काष्ठा __kernel_बारpec __user *, rmtp)
अणु
	काष्ठा बारpec64 t;
	kसमय_प्रकार texp;

	चयन (which_घड़ी) अणु
	हाल CLOCK_REALTIME:
	हाल CLOCK_MONOTONIC:
	हाल CLOCK_BOOTTIME:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (get_बारpec64(&t, rqtp))
		वापस -EFAULT;
	अगर (!बारpec64_valid(&t))
		वापस -EINVAL;
	अगर (flags & TIMER_ABSTIME)
		rmtp = शून्य;
	current->restart_block.nanosleep.type = rmtp ? TT_NATIVE : TT_NONE;
	current->restart_block.nanosleep.rmtp = rmtp;
	texp = बारpec64_to_kसमय(t);
	अगर (flags & TIMER_ABSTIME)
		texp = समयns_kसमय_प्रकारo_host(which_घड़ी, texp);
	वापस hrसमयr_nanosleep(texp, flags & TIMER_ABSTIME ?
				 HRTIMER_MODE_ABS : HRTIMER_MODE_REL,
				 which_घड़ी);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYS_NI(समयr_create);
#पूर्ण_अगर

#अगर defined(CONFIG_COMPAT) || defined(CONFIG_ALPHA)
COMPAT_SYS_NI(getiसमयr);
COMPAT_SYS_NI(setiसमयr);
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
SYS_NI(समयr_समय_रखो32);
SYS_NI(समयr_समय_लो32);

SYSCALL_DEFINE2(घड़ी_समय_रखो32, स्थिर घड़ीid_t, which_घड़ी,
		काष्ठा old_बारpec32 __user *, tp)
अणु
	काष्ठा बारpec64 new_tp;

	अगर (which_घड़ी != CLOCK_REALTIME)
		वापस -EINVAL;
	अगर (get_old_बारpec32(&new_tp, tp))
		वापस -EFAULT;

	वापस करो_sys_समय_रखोofday64(&new_tp, शून्य);
पूर्ण

SYSCALL_DEFINE2(घड़ी_समय_लो32, घड़ीid_t, which_घड़ी,
		काष्ठा old_बारpec32 __user *, tp)
अणु
	पूर्णांक ret;
	काष्ठा बारpec64 kernel_tp;

	ret = करो_घड़ी_समय_लो(which_घड़ी, &kernel_tp);
	अगर (ret)
		वापस ret;

	अगर (put_old_बारpec32(&kernel_tp, tp))
		वापस -EFAULT;
	वापस 0;
पूर्ण

SYSCALL_DEFINE2(घड़ी_getres_समय32, घड़ीid_t, which_घड़ी,
		काष्ठा old_बारpec32 __user *, tp)
अणु
	काष्ठा बारpec64 rtn_tp = अणु
		.tv_sec = 0,
		.tv_nsec = hrसमयr_resolution,
	पूर्ण;

	चयन (which_घड़ी) अणु
	हाल CLOCK_REALTIME:
	हाल CLOCK_MONOTONIC:
	हाल CLOCK_BOOTTIME:
		अगर (put_old_बारpec32(&rtn_tp, tp))
			वापस -EFAULT;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

SYSCALL_DEFINE4(घड़ी_nanosleep_समय32, घड़ीid_t, which_घड़ी, पूर्णांक, flags,
		काष्ठा old_बारpec32 __user *, rqtp,
		काष्ठा old_बारpec32 __user *, rmtp)
अणु
	काष्ठा बारpec64 t;
	kसमय_प्रकार texp;

	चयन (which_घड़ी) अणु
	हाल CLOCK_REALTIME:
	हाल CLOCK_MONOTONIC:
	हाल CLOCK_BOOTTIME:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (get_old_बारpec32(&t, rqtp))
		वापस -EFAULT;
	अगर (!बारpec64_valid(&t))
		वापस -EINVAL;
	अगर (flags & TIMER_ABSTIME)
		rmtp = शून्य;
	current->restart_block.nanosleep.type = rmtp ? TT_COMPAT : TT_NONE;
	current->restart_block.nanosleep.compat_rmtp = rmtp;
	texp = बारpec64_to_kसमय(t);
	अगर (flags & TIMER_ABSTIME)
		texp = समयns_kसमय_प्रकारo_host(which_घड़ी, texp);
	वापस hrसमयr_nanosleep(texp, flags & TIMER_ABSTIME ?
				 HRTIMER_MODE_ABS : HRTIMER_MODE_REL,
				 which_घड़ी);
पूर्ण
#पूर्ण_अगर
