<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * General MIPS MT support routines, usable in AP/SP and SMVP.
 * Copyright (C) 2005 Mips Technologies, Inc
 */
#समावेश <linux/cpu.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/cred.h>
#समावेश <linux/security.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

/*
 * CPU mask used to set process affinity क्रम MT VPEs/TCs with FPUs
 */
cpumask_t mt_fpu_cpumask;

अटल पूर्णांक fpaff_threshold = -1;
अचिन्हित दीर्घ mt_fpemul_threshold;

/*
 * Replacement functions क्रम the sys_sched_setaffinity() and
 * sys_sched_getaffinity() प्रणाली calls, so that we can पूर्णांकegrate
 * FPU affinity with the user's requested processor affinity.
 * This code is 98% identical with the sys_sched_setaffinity()
 * and sys_sched_getaffinity() प्रणाली calls, and should be
 * updated when kernel/sched/core.c changes.
 */

/*
 * find_process_by_pid - find a process with a matching PID value.
 * used in sys_sched_set/getaffinity() in kernel/sched/core.c, so
 * cloned here.
 */
अटल अंतरभूत काष्ठा task_काष्ठा *find_process_by_pid(pid_t pid)
अणु
	वापस pid ? find_task_by_vpid(pid) : current;
पूर्ण

/*
 * check the target process has a UID that matches the current process's
 */
अटल bool check_same_owner(काष्ठा task_काष्ठा *p)
अणु
	स्थिर काष्ठा cred *cred = current_cred(), *pcred;
	bool match;

	rcu_पढ़ो_lock();
	pcred = __task_cred(p);
	match = (uid_eq(cred->euid, pcred->euid) ||
		 uid_eq(cred->euid, pcred->uid));
	rcu_पढ़ो_unlock();
	वापस match;
पूर्ण

/*
 * mipsmt_sys_sched_setaffinity - set the cpu affinity of a process
 */
यंत्रlinkage दीर्घ mipsmt_sys_sched_setaffinity(pid_t pid, अचिन्हित पूर्णांक len,
				      अचिन्हित दीर्घ __user *user_mask_ptr)
अणु
	cpumask_var_t cpus_allowed, new_mask, effective_mask;
	काष्ठा thपढ़ो_info *ti;
	काष्ठा task_काष्ठा *p;
	पूर्णांक retval;

	अगर (len < माप(new_mask))
		वापस -EINVAL;

	अगर (copy_from_user(&new_mask, user_mask_ptr, माप(new_mask)))
		वापस -EFAULT;

	get_online_cpus();
	rcu_पढ़ो_lock();

	p = find_process_by_pid(pid);
	अगर (!p) अणु
		rcu_पढ़ो_unlock();
		put_online_cpus();
		वापस -ESRCH;
	पूर्ण

	/* Prevent p going away */
	get_task_काष्ठा(p);
	rcu_पढ़ो_unlock();

	अगर (!alloc_cpumask_var(&cpus_allowed, GFP_KERNEL)) अणु
		retval = -ENOMEM;
		जाओ out_put_task;
	पूर्ण
	अगर (!alloc_cpumask_var(&new_mask, GFP_KERNEL)) अणु
		retval = -ENOMEM;
		जाओ out_मुक्त_cpus_allowed;
	पूर्ण
	अगर (!alloc_cpumask_var(&effective_mask, GFP_KERNEL)) अणु
		retval = -ENOMEM;
		जाओ out_मुक्त_new_mask;
	पूर्ण
	अगर (!check_same_owner(p) && !capable(CAP_SYS_NICE)) अणु
		retval = -EPERM;
		जाओ out_unlock;
	पूर्ण

	retval = security_task_setscheduler(p);
	अगर (retval)
		जाओ out_unlock;

	/* Record new user-specअगरied CPU set क्रम future reference */
	cpumask_copy(&p->thपढ़ो.user_cpus_allowed, new_mask);

 again:
	/* Compute new global allowed CPU set अगर necessary */
	ti = task_thपढ़ो_info(p);
	अगर (test_ti_thपढ़ो_flag(ti, TIF_FPUBOUND) &&
	    cpumask_पूर्णांकersects(new_mask, &mt_fpu_cpumask)) अणु
		cpumask_and(effective_mask, new_mask, &mt_fpu_cpumask);
		retval = set_cpus_allowed_ptr(p, effective_mask);
	पूर्ण अन्यथा अणु
		cpumask_copy(effective_mask, new_mask);
		clear_ti_thपढ़ो_flag(ti, TIF_FPUBOUND);
		retval = set_cpus_allowed_ptr(p, new_mask);
	पूर्ण

	अगर (!retval) अणु
		cpuset_cpus_allowed(p, cpus_allowed);
		अगर (!cpumask_subset(effective_mask, cpus_allowed)) अणु
			/*
			 * We must have raced with a concurrent cpuset
			 * update. Just reset the cpus_allowed to the
			 * cpuset's cpus_allowed
			 */
			cpumask_copy(new_mask, cpus_allowed);
			जाओ again;
		पूर्ण
	पूर्ण
out_unlock:
	मुक्त_cpumask_var(effective_mask);
out_मुक्त_new_mask:
	मुक्त_cpumask_var(new_mask);
out_मुक्त_cpus_allowed:
	मुक्त_cpumask_var(cpus_allowed);
out_put_task:
	put_task_काष्ठा(p);
	put_online_cpus();
	वापस retval;
पूर्ण

/*
 * mipsmt_sys_sched_getaffinity - get the cpu affinity of a process
 */
यंत्रlinkage दीर्घ mipsmt_sys_sched_getaffinity(pid_t pid, अचिन्हित पूर्णांक len,
				      अचिन्हित दीर्घ __user *user_mask_ptr)
अणु
	अचिन्हित पूर्णांक real_len;
	cpumask_t allowed, mask;
	पूर्णांक retval;
	काष्ठा task_काष्ठा *p;

	real_len = माप(mask);
	अगर (len < real_len)
		वापस -EINVAL;

	get_online_cpus();
	rcu_पढ़ो_lock();

	retval = -ESRCH;
	p = find_process_by_pid(pid);
	अगर (!p)
		जाओ out_unlock;
	retval = security_task_माला_लोcheduler(p);
	अगर (retval)
		जाओ out_unlock;

	cpumask_or(&allowed, &p->thपढ़ो.user_cpus_allowed, p->cpus_ptr);
	cpumask_and(&mask, &allowed, cpu_active_mask);

out_unlock:
	rcu_पढ़ो_unlock();
	put_online_cpus();
	अगर (retval)
		वापस retval;
	अगर (copy_to_user(user_mask_ptr, &mask, real_len))
		वापस -EFAULT;
	वापस real_len;
पूर्ण


अटल पूर्णांक __init fpaff_thresh(अक्षर *str)
अणु
	get_option(&str, &fpaff_threshold);
	वापस 1;
पूर्ण
__setup("fpaff=", fpaff_thresh);

/*
 * FPU Use Factor empirically derived from experiments on 34K
 */
#घोषणा FPUSEFACTOR 2000

अटल __init पूर्णांक mt_fp_affinity_init(व्योम)
अणु
	अगर (fpaff_threshold >= 0) अणु
		mt_fpemul_threshold = fpaff_threshold;
	पूर्ण अन्यथा अणु
		mt_fpemul_threshold =
			(FPUSEFACTOR * (loops_per_jअगरfy/(500000/HZ))) / HZ;
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "FPU Affinity set after %ld emulations\n",
	       mt_fpemul_threshold);

	वापस 0;
पूर्ण
arch_initcall(mt_fp_affinity_init);
