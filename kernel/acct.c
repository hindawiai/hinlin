<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/kernel/acct.c
 *
 *  BSD Process Accounting क्रम Linux
 *
 *  Author: Marco van Wieringen <mvw@planets.elm.net>
 *
 *  Some code based on ideas and code from:
 *  Thomas K. Dyas <tdyas@eden.rutgers.edu>
 *
 *  This file implements BSD-style process accounting. Whenever any
 *  process निकासs, an accounting record of type "struct acct" is
 *  written to the file specअगरied with the acct() प्रणाली call. It is
 *  up to user-level programs to करो useful things with the accounting
 *  log. The kernel just provides the raw accounting inक्रमmation.
 *
 * (C) Copyright 1995 - 1997 Marco van Wieringen - ELM Consultancy B.V.
 *
 *  Plugged two leaks. 1) It didn't वापस acct_file पूर्णांकo the मुक्त_filps अगर
 *  the file happened to be पढ़ो-only. 2) If the accounting was suspended
 *  due to the lack of space it happily allowed to reखोलो it and completely
 *  lost the old acct_file. 3/10/98, Al Viro.
 *
 *  Now we silently बंद acct_file on attempt to reखोलो. Cleaned sys_acct().
 *  XTerms and EMACS are manअगरestations of pure evil. 21/10/98, AV.
 *
 *  Fixed a nasty पूर्णांकeraction with sys_umount(). If the accounting
 *  was suspeneded we failed to stop it on umount(). Messy.
 *  Another one: remount to पढ़ोonly didn't stop accounting.
 *	Question: what should we करो अगर we have CAP_SYS_ADMIN but not
 *  CAP_SYS_PACCT? Current code करोes the following: umount वापसs -EBUSY
 *  unless we are messing with the root. In that हाल we are getting a
 *  real mess with करो_remount_sb(). 9/11/98, AV.
 *
 *  Fixed a bunch of races (and pair of leaks). Probably not the best way,
 *  but this one obviously करोesn't पूर्णांकroduce deadlocks. Later. BTW, found
 *  one race (and leak) in BSD implementation.
 *  OK, that's better. ANOTHER race and leak in BSD variant. There always
 *  is one more bug... 10/11/98, AV.
 *
 *	Oh, fsck... Oopsable SMP race in करो_process_acct() - we must hold
 * ->mmap_lock to walk the vma list of current->mm. Nasty, since it leaks
 * a काष्ठा file खोलोed क्रम ग_लिखो. Fixed. 2/6/2000, AV.
 */

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/acct.h>
#समावेश <linux/capability.h>
#समावेश <linux/file.h>
#समावेश <linux/tty.h>
#समावेश <linux/security.h>
#समावेश <linux/vfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/बार.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/mount.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched/cpuसमय.स>

#समावेश <यंत्र/भाग64.h>
#समावेश <linux/blkdev.h> /* sector_भाग */
#समावेश <linux/pid_namespace.h>
#समावेश <linux/fs_pin.h>

/*
 * These स्थिरants control the amount of मुक्तspace that suspend and
 * resume the process accounting प्रणाली, and the समय delay between
 * each check.
 * Turned पूर्णांकo sysctl-controllable parameters. AV, 12/11/98
 */

पूर्णांक acct_parm[3] = अणु4, 2, 30पूर्ण;
#घोषणा RESUME		(acct_parm[0])	/* >foo% मुक्त space - resume */
#घोषणा SUSPEND		(acct_parm[1])	/* <foo% मुक्त space - suspend */
#घोषणा ACCT_TIMEOUT	(acct_parm[2])	/* foo second समयout between checks */

/*
 * External references and all of the globals.
 */

काष्ठा bsd_acct_काष्ठा अणु
	काष्ठा fs_pin		pin;
	atomic_दीर्घ_t		count;
	काष्ठा rcu_head		rcu;
	काष्ठा mutex		lock;
	पूर्णांक			active;
	अचिन्हित दीर्घ		needcheck;
	काष्ठा file		*file;
	काष्ठा pid_namespace	*ns;
	काष्ठा work_काष्ठा	work;
	काष्ठा completion	करोne;
पूर्ण;

अटल व्योम करो_acct_process(काष्ठा bsd_acct_काष्ठा *acct);

/*
 * Check the amount of मुक्त space and suspend/resume accordingly.
 */
अटल पूर्णांक check_मुक्त_space(काष्ठा bsd_acct_काष्ठा *acct)
अणु
	काष्ठा kstatfs sbuf;

	अगर (समय_is_after_jअगरfies(acct->needcheck))
		जाओ out;

	/* May block */
	अगर (vfs_statfs(&acct->file->f_path, &sbuf))
		जाओ out;

	अगर (acct->active) अणु
		u64 suspend = sbuf.f_blocks * SUSPEND;
		करो_भाग(suspend, 100);
		अगर (sbuf.f_bavail <= suspend) अणु
			acct->active = 0;
			pr_info("Process accounting paused\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		u64 resume = sbuf.f_blocks * RESUME;
		करो_भाग(resume, 100);
		अगर (sbuf.f_bavail >= resume) अणु
			acct->active = 1;
			pr_info("Process accounting resumed\n");
		पूर्ण
	पूर्ण

	acct->needcheck = jअगरfies + ACCT_TIMEOUT*HZ;
out:
	वापस acct->active;
पूर्ण

अटल व्योम acct_put(काष्ठा bsd_acct_काष्ठा *p)
अणु
	अगर (atomic_दीर्घ_dec_and_test(&p->count))
		kमुक्त_rcu(p, rcu);
पूर्ण

अटल अंतरभूत काष्ठा bsd_acct_काष्ठा *to_acct(काष्ठा fs_pin *p)
अणु
	वापस p ? container_of(p, काष्ठा bsd_acct_काष्ठा, pin) : शून्य;
पूर्ण

अटल काष्ठा bsd_acct_काष्ठा *acct_get(काष्ठा pid_namespace *ns)
अणु
	काष्ठा bsd_acct_काष्ठा *res;
again:
	smp_rmb();
	rcu_पढ़ो_lock();
	res = to_acct(READ_ONCE(ns->bacct));
	अगर (!res) अणु
		rcu_पढ़ो_unlock();
		वापस शून्य;
	पूर्ण
	अगर (!atomic_दीर्घ_inc_not_zero(&res->count)) अणु
		rcu_पढ़ो_unlock();
		cpu_relax();
		जाओ again;
	पूर्ण
	rcu_पढ़ो_unlock();
	mutex_lock(&res->lock);
	अगर (res != to_acct(READ_ONCE(ns->bacct))) अणु
		mutex_unlock(&res->lock);
		acct_put(res);
		जाओ again;
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम acct_pin_समाप्त(काष्ठा fs_pin *pin)
अणु
	काष्ठा bsd_acct_काष्ठा *acct = to_acct(pin);
	mutex_lock(&acct->lock);
	करो_acct_process(acct);
	schedule_work(&acct->work);
	रुको_क्रम_completion(&acct->करोne);
	cmpxchg(&acct->ns->bacct, pin, शून्य);
	mutex_unlock(&acct->lock);
	pin_हटाओ(pin);
	acct_put(acct);
पूर्ण

अटल व्योम बंद_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bsd_acct_काष्ठा *acct = container_of(work, काष्ठा bsd_acct_काष्ठा, work);
	काष्ठा file *file = acct->file;
	अगर (file->f_op->flush)
		file->f_op->flush(file, शून्य);
	__fput_sync(file);
	complete(&acct->करोne);
पूर्ण

अटल पूर्णांक acct_on(काष्ठा filename *pathname)
अणु
	काष्ठा file *file;
	काष्ठा vfsmount *mnt, *पूर्णांकernal;
	काष्ठा pid_namespace *ns = task_active_pid_ns(current);
	काष्ठा bsd_acct_काष्ठा *acct;
	काष्ठा fs_pin *old;
	पूर्णांक err;

	acct = kzalloc(माप(काष्ठा bsd_acct_काष्ठा), GFP_KERNEL);
	अगर (!acct)
		वापस -ENOMEM;

	/* Dअगरference from BSD - they करोn't करो O_APPEND */
	file = file_खोलो_name(pathname, O_WRONLY|O_APPEND|O_LARGEखाता, 0);
	अगर (IS_ERR(file)) अणु
		kमुक्त(acct);
		वापस PTR_ERR(file);
	पूर्ण

	अगर (!S_ISREG(file_inode(file)->i_mode)) अणु
		kमुक्त(acct);
		filp_बंद(file, शून्य);
		वापस -EACCES;
	पूर्ण

	अगर (!(file->f_mode & FMODE_CAN_WRITE)) अणु
		kमुक्त(acct);
		filp_बंद(file, शून्य);
		वापस -EIO;
	पूर्ण
	पूर्णांकernal = mnt_clone_पूर्णांकernal(&file->f_path);
	अगर (IS_ERR(पूर्णांकernal)) अणु
		kमुक्त(acct);
		filp_बंद(file, शून्य);
		वापस PTR_ERR(पूर्णांकernal);
	पूर्ण
	err = __mnt_want_ग_लिखो(पूर्णांकernal);
	अगर (err) अणु
		mntput(पूर्णांकernal);
		kमुक्त(acct);
		filp_बंद(file, शून्य);
		वापस err;
	पूर्ण
	mnt = file->f_path.mnt;
	file->f_path.mnt = पूर्णांकernal;

	atomic_दीर्घ_set(&acct->count, 1);
	init_fs_pin(&acct->pin, acct_pin_समाप्त);
	acct->file = file;
	acct->needcheck = jअगरfies;
	acct->ns = ns;
	mutex_init(&acct->lock);
	INIT_WORK(&acct->work, बंद_work);
	init_completion(&acct->करोne);
	mutex_lock_nested(&acct->lock, 1);	/* nobody has seen it yet */
	pin_insert(&acct->pin, mnt);

	rcu_पढ़ो_lock();
	old = xchg(&ns->bacct, &acct->pin);
	mutex_unlock(&acct->lock);
	pin_समाप्त(old);
	__mnt_drop_ग_लिखो(mnt);
	mntput(mnt);
	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(acct_on_mutex);

/**
 * sys_acct - enable/disable process accounting
 * @name: file name क्रम accounting records or शून्य to shutकरोwn accounting
 *
 * sys_acct() is the only प्रणाली call needed to implement process
 * accounting. It takes the name of the file where accounting records
 * should be written. If the filename is शून्य, accounting will be
 * shutकरोwn.
 *
 * Returns: 0 क्रम success or negative त्रुटि_सं values क्रम failure.
 */
SYSCALL_DEFINE1(acct, स्थिर अक्षर __user *, name)
अणु
	पूर्णांक error = 0;

	अगर (!capable(CAP_SYS_PACCT))
		वापस -EPERM;

	अगर (name) अणु
		काष्ठा filename *पंचांगp = getname(name);

		अगर (IS_ERR(पंचांगp))
			वापस PTR_ERR(पंचांगp);
		mutex_lock(&acct_on_mutex);
		error = acct_on(पंचांगp);
		mutex_unlock(&acct_on_mutex);
		putname(पंचांगp);
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_lock();
		pin_समाप्त(task_active_pid_ns(current)->bacct);
	पूर्ण

	वापस error;
पूर्ण

व्योम acct_निकास_ns(काष्ठा pid_namespace *ns)
अणु
	rcu_पढ़ो_lock();
	pin_समाप्त(ns->bacct);
पूर्ण

/*
 *  encode an अचिन्हित दीर्घ पूर्णांकo a comp_t
 *
 *  This routine has been aकरोpted from the encode_comp_t() function in
 *  the kern_acct.c file of the FreeBSD operating प्रणाली. The encoding
 *  is a 13-bit fraction with a 3-bit (base 8) exponent.
 */

#घोषणा	MANTSIZE	13			/* 13 bit mantissa. */
#घोषणा	EXPSIZE		3			/* Base 8 (3 bit) exponent. */
#घोषणा	MAXFRACT	((1 << MANTSIZE) - 1)	/* Maximum fractional value. */

अटल comp_t encode_comp_t(अचिन्हित दीर्घ value)
अणु
	पूर्णांक exp, rnd;

	exp = rnd = 0;
	जबतक (value > MAXFRACT) अणु
		rnd = value & (1 << (EXPSIZE - 1));	/* Round up? */
		value >>= EXPSIZE;	/* Base 8 exponent == 3 bit shअगरt. */
		exp++;
	पूर्ण

	/*
	 * If we need to round up, करो it (and handle overflow correctly).
	 */
	अगर (rnd && (++value > MAXFRACT)) अणु
		value >>= EXPSIZE;
		exp++;
	पूर्ण

	/*
	 * Clean it up and polish it off.
	 */
	exp <<= MANTSIZE;		/* Shअगरt the exponent पूर्णांकo place */
	exp += value;			/* and add on the mantissa. */
	वापस exp;
पूर्ण

#अगर ACCT_VERSION == 1 || ACCT_VERSION == 2
/*
 * encode an u64 पूर्णांकo a comp2_t (24 bits)
 *
 * Format: 5 bit base 2 exponent, 20 bits mantissa.
 * The leading bit of the mantissa is not stored, but implied क्रम
 * non-zero exponents.
 * Largest encodable value is 50 bits.
 */

#घोषणा MANTSIZE2       20                      /* 20 bit mantissa. */
#घोषणा EXPSIZE2        5                       /* 5 bit base 2 exponent. */
#घोषणा MAXFRACT2       ((1ul << MANTSIZE2) - 1) /* Maximum fractional value. */
#घोषणा MAXEXP2         ((1 << EXPSIZE2) - 1)    /* Maximum exponent. */

अटल comp2_t encode_comp2_t(u64 value)
अणु
	पूर्णांक exp, rnd;

	exp = (value > (MAXFRACT2>>1));
	rnd = 0;
	जबतक (value > MAXFRACT2) अणु
		rnd = value & 1;
		value >>= 1;
		exp++;
	पूर्ण

	/*
	 * If we need to round up, करो it (and handle overflow correctly).
	 */
	अगर (rnd && (++value > MAXFRACT2)) अणु
		value >>= 1;
		exp++;
	पूर्ण

	अगर (exp > MAXEXP2) अणु
		/* Overflow. Return largest representable number instead. */
		वापस (1ul << (MANTSIZE2+EXPSIZE2-1)) - 1;
	पूर्ण अन्यथा अणु
		वापस (value & (MAXFRACT2>>1)) | (exp << (MANTSIZE2-1));
	पूर्ण
पूर्ण
#या_अगर ACCT_VERSION == 3
/*
 * encode an u64 पूर्णांकo a 32 bit IEEE भग्न
 */
अटल u32 encode_भग्न(u64 value)
अणु
	अचिन्हित exp = 190;
	अचिन्हित u;

	अगर (value == 0)
		वापस 0;
	जबतक ((s64)value > 0) अणु
		value <<= 1;
		exp--;
	पूर्ण
	u = (u32)(value >> 40) & 0x7fffffu;
	वापस u | (exp << 23);
पूर्ण
#पूर्ण_अगर

/*
 *  Write an accounting entry क्रम an निकासing process
 *
 *  The acct_process() call is the workhorse of the process
 *  accounting प्रणाली. The काष्ठा acct is built here and then written
 *  पूर्णांकo the accounting file. This function should only be called from
 *  करो_निकास() or when चयनing to a dअगरferent output file.
 */

अटल व्योम fill_ac(acct_t *ac)
अणु
	काष्ठा pacct_काष्ठा *pacct = &current->संकेत->pacct;
	u64 elapsed, run_समय;
	समय64_t bसमय;
	काष्ठा tty_काष्ठा *tty;

	/*
	 * Fill the accounting काष्ठा with the needed info as recorded
	 * by the dअगरferent kernel functions.
	 */
	स_रखो(ac, 0, माप(acct_t));

	ac->ac_version = ACCT_VERSION | ACCT_BYTEORDER;
	strlcpy(ac->ac_comm, current->comm, माप(ac->ac_comm));

	/* calculate run_समय in nsec*/
	run_समय = kसमय_get_ns();
	run_समय -= current->group_leader->start_समय;
	/* convert nsec -> AHZ */
	elapsed = nsec_to_AHZ(run_समय);
#अगर ACCT_VERSION == 3
	ac->ac_eसमय = encode_भग्न(elapsed);
#अन्यथा
	ac->ac_eसमय = encode_comp_t(elapsed < (अचिन्हित दीर्घ) -1l ?
				(अचिन्हित दीर्घ) elapsed : (अचिन्हित दीर्घ) -1l);
#पूर्ण_अगर
#अगर ACCT_VERSION == 1 || ACCT_VERSION == 2
	अणु
		/* new enlarged eसमय field */
		comp2_t eसमय = encode_comp2_t(elapsed);

		ac->ac_eसमय_hi = eसमय >> 16;
		ac->ac_eसमय_lo = (u16) eसमय;
	पूर्ण
#पूर्ण_अगर
	करो_भाग(elapsed, AHZ);
	bसमय = kसमय_get_real_seconds() - elapsed;
	ac->ac_bसमय = clamp_t(समय64_t, bसमय, 0, U32_MAX);
#अगर ACCT_VERSION==2
	ac->ac_ahz = AHZ;
#पूर्ण_अगर

	spin_lock_irq(&current->sighand->siglock);
	tty = current->संकेत->tty;	/* Safe as we hold the siglock */
	ac->ac_tty = tty ? old_encode_dev(tty_devnum(tty)) : 0;
	ac->ac_uसमय = encode_comp_t(nsec_to_AHZ(pacct->ac_uसमय));
	ac->ac_sसमय = encode_comp_t(nsec_to_AHZ(pacct->ac_sसमय));
	ac->ac_flag = pacct->ac_flag;
	ac->ac_mem = encode_comp_t(pacct->ac_mem);
	ac->ac_minflt = encode_comp_t(pacct->ac_minflt);
	ac->ac_majflt = encode_comp_t(pacct->ac_majflt);
	ac->ac_निकासcode = pacct->ac_निकासcode;
	spin_unlock_irq(&current->sighand->siglock);
पूर्ण
/*
 *  करो_acct_process करोes all actual work. Caller holds the reference to file.
 */
अटल व्योम करो_acct_process(काष्ठा bsd_acct_काष्ठा *acct)
अणु
	acct_t ac;
	अचिन्हित दीर्घ flim;
	स्थिर काष्ठा cred *orig_cred;
	काष्ठा file *file = acct->file;

	/*
	 * Accounting records are not subject to resource limits.
	 */
	flim = current->संकेत->rlim[RLIMIT_FSIZE].rlim_cur;
	current->संकेत->rlim[RLIMIT_FSIZE].rlim_cur = RLIM_अनन्त;
	/* Perक्रमm file operations on behalf of whoever enabled accounting */
	orig_cred = override_creds(file->f_cred);

	/*
	 * First check to see अगर there is enough मुक्त_space to जारी
	 * the process accounting प्रणाली.
	 */
	अगर (!check_मुक्त_space(acct))
		जाओ out;

	fill_ac(&ac);
	/* we really need to bite the bullet and change layout */
	ac.ac_uid = from_kuid_munged(file->f_cred->user_ns, orig_cred->uid);
	ac.ac_gid = from_kgid_munged(file->f_cred->user_ns, orig_cred->gid);
#अगर ACCT_VERSION == 1 || ACCT_VERSION == 2
	/* backward-compatible 16 bit fields */
	ac.ac_uid16 = ac.ac_uid;
	ac.ac_gid16 = ac.ac_gid;
#या_अगर ACCT_VERSION == 3
	अणु
		काष्ठा pid_namespace *ns = acct->ns;

		ac.ac_pid = task_tgid_nr_ns(current, ns);
		rcu_पढ़ो_lock();
		ac.ac_ppid = task_tgid_nr_ns(rcu_dereference(current->real_parent),
					     ns);
		rcu_पढ़ो_unlock();
	पूर्ण
#पूर्ण_अगर
	/*
	 * Get मुक्तze protection. If the fs is frozen, just skip the ग_लिखो
	 * as we could deadlock the प्रणाली otherwise.
	 */
	अगर (file_start_ग_लिखो_trylock(file)) अणु
		/* it's been खोलोed O_APPEND, so position is irrelevant */
		loff_t pos = 0;
		__kernel_ग_लिखो(file, &ac, माप(acct_t), &pos);
		file_end_ग_लिखो(file);
	पूर्ण
out:
	current->संकेत->rlim[RLIMIT_FSIZE].rlim_cur = flim;
	revert_creds(orig_cred);
पूर्ण

/**
 * acct_collect - collect accounting inक्रमmation पूर्णांकo pacct_काष्ठा
 * @निकासcode: task निकास code
 * @group_dead: not 0, अगर this thपढ़ो is the last one in the process.
 */
व्योम acct_collect(दीर्घ निकासcode, पूर्णांक group_dead)
अणु
	काष्ठा pacct_काष्ठा *pacct = &current->संकेत->pacct;
	u64 uसमय, sसमय;
	अचिन्हित दीर्घ vsize = 0;

	अगर (group_dead && current->mm) अणु
		काष्ठा vm_area_काष्ठा *vma;

		mmap_पढ़ो_lock(current->mm);
		vma = current->mm->mmap;
		जबतक (vma) अणु
			vsize += vma->vm_end - vma->vm_start;
			vma = vma->vm_next;
		पूर्ण
		mmap_पढ़ो_unlock(current->mm);
	पूर्ण

	spin_lock_irq(&current->sighand->siglock);
	अगर (group_dead)
		pacct->ac_mem = vsize / 1024;
	अगर (thपढ़ो_group_leader(current)) अणु
		pacct->ac_निकासcode = निकासcode;
		अगर (current->flags & PF_FORKNOEXEC)
			pacct->ac_flag |= AFORK;
	पूर्ण
	अगर (current->flags & PF_SUPERPRIV)
		pacct->ac_flag |= ASU;
	अगर (current->flags & PF_DUMPCORE)
		pacct->ac_flag |= ACORE;
	अगर (current->flags & PF_SIGNALED)
		pacct->ac_flag |= AXSIG;

	task_cpuसमय(current, &uसमय, &sसमय);
	pacct->ac_uसमय += uसमय;
	pacct->ac_sसमय += sसमय;
	pacct->ac_minflt += current->min_flt;
	pacct->ac_majflt += current->maj_flt;
	spin_unlock_irq(&current->sighand->siglock);
पूर्ण

अटल व्योम slow_acct_process(काष्ठा pid_namespace *ns)
अणु
	क्रम ( ; ns; ns = ns->parent) अणु
		काष्ठा bsd_acct_काष्ठा *acct = acct_get(ns);
		अगर (acct) अणु
			करो_acct_process(acct);
			mutex_unlock(&acct->lock);
			acct_put(acct);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * acct_process - handles process accounting क्रम an निकासing task
 */
व्योम acct_process(व्योम)
अणु
	काष्ठा pid_namespace *ns;

	/*
	 * This loop is safe lockless, since current is still
	 * alive and holds its namespace, which in turn holds
	 * its parent.
	 */
	क्रम (ns = task_active_pid_ns(current); ns != शून्य; ns = ns->parent) अणु
		अगर (ns->bacct)
			अवरोध;
	पूर्ण
	अगर (unlikely(ns))
		slow_acct_process(ns);
पूर्ण
