<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/माला.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/module.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/cache.h>
#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/kcmp.h>
#समावेश <linux/capability.h>
#समावेश <linux/list.h>
#समावेश <linux/eventpoll.h>
#समावेश <linux/file.h>

#समावेश <यंत्र/unistd.h>

/*
 * We करोn't expose the real in-memory order of objects क्रम security reasons.
 * But still the comparison results should be suitable क्रम sorting. So we
 * obfuscate kernel poपूर्णांकers values and compare the production instead.
 *
 * The obfuscation is करोne in two steps. First we xor the kernel poपूर्णांकer with
 * a अक्रमom value, which माला_दो poपूर्णांकer पूर्णांकo a new position in a reordered space.
 * Secondly we multiply the xor production with a large odd अक्रमom number to
 * permute its bits even more (the odd multiplier guarantees that the product
 * is unique ever after the high bits are truncated, since any odd number is
 * relative prime to 2^n).
 *
 * Note also that the obfuscation itself is invisible to userspace and अगर needed
 * it can be changed to an alternate scheme.
 */
अटल अचिन्हित दीर्घ cookies[KCMP_TYPES][2] __पढ़ो_mostly;

अटल दीर्घ kptr_obfuscate(दीर्घ v, पूर्णांक type)
अणु
	वापस (v ^ cookies[type][0]) * cookies[type][1];
पूर्ण

/*
 * 0 - equal, i.e. v1 = v2
 * 1 - less than, i.e. v1 < v2
 * 2 - greater than, i.e. v1 > v2
 * 3 - not equal but ordering unavailable (reserved क्रम future)
 */
अटल पूर्णांक kcmp_ptr(व्योम *v1, व्योम *v2, क्रमागत kcmp_type type)
अणु
	दीर्घ t1, t2;

	t1 = kptr_obfuscate((दीर्घ)v1, type);
	t2 = kptr_obfuscate((दीर्घ)v2, type);

	वापस (t1 < t2) | ((t1 > t2) << 1);
पूर्ण

/* The caller must have pinned the task */
अटल काष्ठा file *
get_file_raw_ptr(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा file *file;

	rcu_पढ़ो_lock();
	file = task_lookup_fd_rcu(task, idx);
	rcu_पढ़ो_unlock();

	वापस file;
पूर्ण

अटल व्योम kcmp_unlock(काष्ठा rw_semaphore *l1, काष्ठा rw_semaphore *l2)
अणु
	अगर (likely(l2 != l1))
		up_पढ़ो(l2);
	up_पढ़ो(l1);
पूर्ण

अटल पूर्णांक kcmp_lock(काष्ठा rw_semaphore *l1, काष्ठा rw_semaphore *l2)
अणु
	पूर्णांक err;

	अगर (l2 > l1)
		swap(l1, l2);

	err = करोwn_पढ़ो_समाप्तable(l1);
	अगर (!err && likely(l1 != l2)) अणु
		err = करोwn_पढ़ो_समाप्तable_nested(l2, SINGLE_DEPTH_NESTING);
		अगर (err)
			up_पढ़ो(l1);
	पूर्ण

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_EPOLL
अटल पूर्णांक kcmp_epoll_target(काष्ठा task_काष्ठा *task1,
			     काष्ठा task_काष्ठा *task2,
			     अचिन्हित दीर्घ idx1,
			     काष्ठा kcmp_epoll_slot __user *uslot)
अणु
	काष्ठा file *filp, *filp_epoll, *filp_tgt;
	काष्ठा kcmp_epoll_slot slot;

	अगर (copy_from_user(&slot, uslot, माप(slot)))
		वापस -EFAULT;

	filp = get_file_raw_ptr(task1, idx1);
	अगर (!filp)
		वापस -EBADF;

	filp_epoll = fget_task(task2, slot.efd);
	अगर (!filp_epoll)
		वापस -EBADF;

	filp_tgt = get_epoll_tfile_raw_ptr(filp_epoll, slot.tfd, slot.toff);
	fput(filp_epoll);

	अगर (IS_ERR(filp_tgt))
		वापस PTR_ERR(filp_tgt);

	वापस kcmp_ptr(filp, filp_tgt, KCMP_खाता);
पूर्ण
#अन्यथा
अटल पूर्णांक kcmp_epoll_target(काष्ठा task_काष्ठा *task1,
			     काष्ठा task_काष्ठा *task2,
			     अचिन्हित दीर्घ idx1,
			     काष्ठा kcmp_epoll_slot __user *uslot)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

SYSCALL_DEFINE5(kcmp, pid_t, pid1, pid_t, pid2, पूर्णांक, type,
		अचिन्हित दीर्घ, idx1, अचिन्हित दीर्घ, idx2)
अणु
	काष्ठा task_काष्ठा *task1, *task2;
	पूर्णांक ret;

	rcu_पढ़ो_lock();

	/*
	 * Tasks are looked up in caller's PID namespace only.
	 */
	task1 = find_task_by_vpid(pid1);
	task2 = find_task_by_vpid(pid2);
	अगर (!task1 || !task2)
		जाओ err_no_task;

	get_task_काष्ठा(task1);
	get_task_काष्ठा(task2);

	rcu_पढ़ो_unlock();

	/*
	 * One should have enough rights to inspect task details.
	 */
	ret = kcmp_lock(&task1->संकेत->exec_update_lock,
			&task2->संकेत->exec_update_lock);
	अगर (ret)
		जाओ err;
	अगर (!ptrace_may_access(task1, PTRACE_MODE_READ_REALCREDS) ||
	    !ptrace_may_access(task2, PTRACE_MODE_READ_REALCREDS)) अणु
		ret = -EPERM;
		जाओ err_unlock;
	पूर्ण

	चयन (type) अणु
	हाल KCMP_खाता: अणु
		काष्ठा file *filp1, *filp2;

		filp1 = get_file_raw_ptr(task1, idx1);
		filp2 = get_file_raw_ptr(task2, idx2);

		अगर (filp1 && filp2)
			ret = kcmp_ptr(filp1, filp2, KCMP_खाता);
		अन्यथा
			ret = -EBADF;
		अवरोध;
	पूर्ण
	हाल KCMP_VM:
		ret = kcmp_ptr(task1->mm, task2->mm, KCMP_VM);
		अवरोध;
	हाल KCMP_खाताS:
		ret = kcmp_ptr(task1->files, task2->files, KCMP_खाताS);
		अवरोध;
	हाल KCMP_FS:
		ret = kcmp_ptr(task1->fs, task2->fs, KCMP_FS);
		अवरोध;
	हाल KCMP_SIGHAND:
		ret = kcmp_ptr(task1->sighand, task2->sighand, KCMP_SIGHAND);
		अवरोध;
	हाल KCMP_IO:
		ret = kcmp_ptr(task1->io_context, task2->io_context, KCMP_IO);
		अवरोध;
	हाल KCMP_SYSVSEM:
#अगर_घोषित CONFIG_SYSVIPC
		ret = kcmp_ptr(task1->sysvsem.unकरो_list,
			       task2->sysvsem.unकरो_list,
			       KCMP_SYSVSEM);
#अन्यथा
		ret = -EOPNOTSUPP;
#पूर्ण_अगर
		अवरोध;
	हाल KCMP_EPOLL_TFD:
		ret = kcmp_epoll_target(task1, task2, idx1, (व्योम *)idx2);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

err_unlock:
	kcmp_unlock(&task1->संकेत->exec_update_lock,
		    &task2->संकेत->exec_update_lock);
err:
	put_task_काष्ठा(task1);
	put_task_काष्ठा(task2);

	वापस ret;

err_no_task:
	rcu_पढ़ो_unlock();
	वापस -ESRCH;
पूर्ण

अटल __init पूर्णांक kcmp_cookies_init(व्योम)
अणु
	पूर्णांक i;

	get_अक्रमom_bytes(cookies, माप(cookies));

	क्रम (i = 0; i < KCMP_TYPES; i++)
		cookies[i][1] |= (~(~0UL >>  1) | 1);

	वापस 0;
पूर्ण
arch_initcall(kcmp_cookies_init);
