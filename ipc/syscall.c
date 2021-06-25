<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sys_ipc() is the old de-multiplexer क्रम the SysV IPC calls.
 *
 * This is really horribly ugly, and new architectures should just wire up
 * the inभागidual syscalls instead.
 */
#समावेश <linux/unistd.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/security.h>
#समावेश <linux/ipc_namespace.h>
#समावेश "util.h"

#अगर_घोषित __ARCH_WANT_SYS_IPC
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ipc.h>
#समावेश <linux/shm.h>
#समावेश <linux/uaccess.h>

पूर्णांक ksys_ipc(अचिन्हित पूर्णांक call, पूर्णांक first, अचिन्हित दीर्घ second,
	अचिन्हित दीर्घ third, व्योम __user * ptr, दीर्घ fअगरth)
अणु
	पूर्णांक version, ret;

	version = call >> 16; /* hack क्रम backward compatibility */
	call &= 0xffff;

	चयन (call) अणु
	हाल SEMOP:
		वापस ksys_semसमयकरोp(first, (काष्ठा sembuf __user *)ptr,
				       second, शून्य);
	हाल SEMTIMEDOP:
		अगर (IS_ENABLED(CONFIG_64BIT))
			वापस ksys_semसमयकरोp(first, ptr, second,
			        (स्थिर काष्ठा __kernel_बारpec __user *)fअगरth);
		अन्यथा अगर (IS_ENABLED(CONFIG_COMPAT_32BIT_TIME))
			वापस compat_ksys_semसमयकरोp(first, ptr, second,
			        (स्थिर काष्ठा old_बारpec32 __user *)fअगरth);
		अन्यथा
			वापस -ENOSYS;

	हाल SEMGET:
		वापस ksys_semget(first, second, third);
	हाल SEMCTL: अणु
		अचिन्हित दीर्घ arg;
		अगर (!ptr)
			वापस -EINVAL;
		अगर (get_user(arg, (अचिन्हित दीर्घ __user *) ptr))
			वापस -EFAULT;
		वापस ksys_old_semctl(first, second, third, arg);
	पूर्ण

	हाल MSGSND:
		वापस ksys_msgsnd(first, (काष्ठा msgbuf __user *) ptr,
				  second, third);
	हाल MSGRCV:
		चयन (version) अणु
		हाल 0: अणु
			काष्ठा ipc_kludge पंचांगp;
			अगर (!ptr)
				वापस -EINVAL;

			अगर (copy_from_user(&पंचांगp,
					   (काष्ठा ipc_kludge __user *) ptr,
					   माप(पंचांगp)))
				वापस -EFAULT;
			वापस ksys_msgrcv(first, पंचांगp.msgp, second,
					   पंचांगp.msgtyp, third);
		पूर्ण
		शेष:
			वापस ksys_msgrcv(first,
					   (काष्ठा msgbuf __user *) ptr,
					   second, fअगरth, third);
		पूर्ण
	हाल MSGGET:
		वापस ksys_msgget((key_t) first, second);
	हाल MSGCTL:
		वापस ksys_old_msgctl(first, second,
				   (काष्ठा msqid_ds __user *)ptr);

	हाल SHMAT:
		चयन (version) अणु
		शेष: अणु
			अचिन्हित दीर्घ raddr;
			ret = करो_shmat(first, (अक्षर __user *)ptr,
				       second, &raddr, SHMLBA);
			अगर (ret)
				वापस ret;
			वापस put_user(raddr, (अचिन्हित दीर्घ __user *) third);
		पूर्ण
		हाल 1:
			/*
			 * This was the entry poपूर्णांक क्रम kernel-originating calls
			 * from iBCS2 in 2.2 days.
			 */
			वापस -EINVAL;
		पूर्ण
	हाल SHMDT:
		वापस ksys_shmdt((अक्षर __user *)ptr);
	हाल SHMGET:
		वापस ksys_shmget(first, second, third);
	हाल SHMCTL:
		वापस ksys_old_shmctl(first, second,
				   (काष्ठा shmid_ds __user *) ptr);
	शेष:
		वापस -ENOSYS;
	पूर्ण
पूर्ण

SYSCALL_DEFINE6(ipc, अचिन्हित पूर्णांक, call, पूर्णांक, first, अचिन्हित दीर्घ, second,
		अचिन्हित दीर्घ, third, व्योम __user *, ptr, दीर्घ, fअगरth)
अणु
	वापस ksys_ipc(call, first, second, third, ptr, fअगरth);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
#समावेश <linux/compat.h>

#अगर_अघोषित COMPAT_SHMLBA
#घोषणा COMPAT_SHMLBA	SHMLBA
#पूर्ण_अगर

काष्ठा compat_ipc_kludge अणु
	compat_uptr_t msgp;
	compat_दीर्घ_t msgtyp;
पूर्ण;

#अगर_घोषित CONFIG_ARCH_WANT_OLD_COMPAT_IPC
पूर्णांक compat_ksys_ipc(u32 call, पूर्णांक first, पूर्णांक second,
	u32 third, compat_uptr_t ptr, u32 fअगरth)
अणु
	पूर्णांक version;
	u32 pad;

	version = call >> 16; /* hack क्रम backward compatibility */
	call &= 0xffff;

	चयन (call) अणु
	हाल SEMOP:
		/* काष्ठा sembuf is the same on 32 and 64bit :)) */
		वापस ksys_semसमयकरोp(first, compat_ptr(ptr), second, शून्य);
	हाल SEMTIMEDOP:
		अगर (!IS_ENABLED(CONFIG_COMPAT_32BIT_TIME))
			वापस -ENOSYS;
		वापस compat_ksys_semसमयकरोp(first, compat_ptr(ptr), second,
						compat_ptr(fअगरth));
	हाल SEMGET:
		वापस ksys_semget(first, second, third);
	हाल SEMCTL:
		अगर (!ptr)
			वापस -EINVAL;
		अगर (get_user(pad, (u32 __user *) compat_ptr(ptr)))
			वापस -EFAULT;
		वापस compat_ksys_old_semctl(first, second, third, pad);

	हाल MSGSND:
		वापस compat_ksys_msgsnd(first, ptr, second, third);

	हाल MSGRCV: अणु
		व्योम __user *uptr = compat_ptr(ptr);

		अगर (first < 0 || second < 0)
			वापस -EINVAL;

		अगर (!version) अणु
			काष्ठा compat_ipc_kludge ipck;
			अगर (!uptr)
				वापस -EINVAL;
			अगर (copy_from_user(&ipck, uptr, माप(ipck)))
				वापस -EFAULT;
			वापस compat_ksys_msgrcv(first, ipck.msgp, second,
						 ipck.msgtyp, third);
		पूर्ण
		वापस compat_ksys_msgrcv(first, ptr, second, fअगरth, third);
	पूर्ण
	हाल MSGGET:
		वापस ksys_msgget(first, second);
	हाल MSGCTL:
		वापस compat_ksys_old_msgctl(first, second, compat_ptr(ptr));

	हाल SHMAT: अणु
		पूर्णांक err;
		अचिन्हित दीर्घ raddr;

		अगर (version == 1)
			वापस -EINVAL;
		err = करो_shmat(first, compat_ptr(ptr), second, &raddr,
			       COMPAT_SHMLBA);
		अगर (err < 0)
			वापस err;
		वापस put_user(raddr, (compat_uदीर्घ_t __user *)compat_ptr(third));
	पूर्ण
	हाल SHMDT:
		वापस ksys_shmdt(compat_ptr(ptr));
	हाल SHMGET:
		वापस ksys_shmget(first, (अचिन्हित पूर्णांक)second, third);
	हाल SHMCTL:
		वापस compat_ksys_old_shmctl(first, second, compat_ptr(ptr));
	पूर्ण

	वापस -ENOSYS;
पूर्ण

COMPAT_SYSCALL_DEFINE6(ipc, u32, call, पूर्णांक, first, पूर्णांक, second,
	u32, third, compat_uptr_t, ptr, u32, fअगरth)
अणु
	वापस compat_ksys_ipc(call, first, second, third, ptr, fअगरth);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
