<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * /dev/mcelog driver
 *
 * K8 parts Copyright 2002,2003 Andi Kleen, SuSE Lअसल.
 * Rest from unknown author(s).
 * 2004 Andi Kleen. Rewrote most of it.
 * Copyright 2008 Intel Corporation
 * Author: Andi Kleen
 */

#समावेश <linux/miscdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/kmod.h>
#समावेश <linux/poll.h>

#समावेश "internal.h"

अटल BLOCKING_NOTIFIER_HEAD(mce_injector_chain);

अटल DEFINE_MUTEX(mce_chrdev_पढ़ो_mutex);

अटल अक्षर mce_helper[128];
अटल अक्षर *mce_helper_argv[2] = अणु mce_helper, शून्य पूर्ण;

/*
 * Lockless MCE logging infraकाष्ठाure.
 * This aव्योमs deadlocks on prपूर्णांकk locks without having to अवरोध locks. Also
 * separate MCEs from kernel messages to aव्योम bogus bug reports.
 */

अटल काष्ठा mce_log_buffer *mcelog;

अटल DECLARE_WAIT_QUEUE_HEAD(mce_chrdev_रुको);

अटल पूर्णांक dev_mce_log(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				व्योम *data)
अणु
	काष्ठा mce *mce = (काष्ठा mce *)data;
	अचिन्हित पूर्णांक entry;

	अगर (mce->kflags & MCE_HANDLED_CEC)
		वापस NOTIFY_DONE;

	mutex_lock(&mce_chrdev_पढ़ो_mutex);

	entry = mcelog->next;

	/*
	 * When the buffer fills up discard new entries. Assume that the
	 * earlier errors are the more पूर्णांकeresting ones:
	 */
	अगर (entry >= mcelog->len) अणु
		set_bit(MCE_OVERFLOW, (अचिन्हित दीर्घ *)&mcelog->flags);
		जाओ unlock;
	पूर्ण

	mcelog->next = entry + 1;

	स_नकल(mcelog->entry + entry, mce, माप(काष्ठा mce));
	mcelog->entry[entry].finished = 1;
	mcelog->entry[entry].kflags = 0;

	/* wake processes polling /dev/mcelog */
	wake_up_पूर्णांकerruptible(&mce_chrdev_रुको);

unlock:
	mutex_unlock(&mce_chrdev_पढ़ो_mutex);

	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_AMD)
		mce->kflags |= MCE_HANDLED_MCELOG;

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block dev_mcelog_nb = अणु
	.notअगरier_call	= dev_mce_log,
	.priority	= MCE_PRIO_MCELOG,
पूर्ण;

अटल व्योम mce_करो_trigger(काष्ठा work_काष्ठा *work)
अणु
	call_usermodehelper(mce_helper, mce_helper_argv, शून्य, UMH_NO_WAIT);
पूर्ण

अटल DECLARE_WORK(mce_trigger_work, mce_करो_trigger);


व्योम mce_work_trigger(व्योम)
अणु
	अगर (mce_helper[0])
		schedule_work(&mce_trigger_work);
पूर्ण

अटल sमाप_प्रकार
show_trigger(काष्ठा device *s, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	म_नकल(buf, mce_helper);
	म_जोड़ो(buf, "\n");
	वापस म_माप(mce_helper) + 1;
पूर्ण

अटल sमाप_प्रकार set_trigger(काष्ठा device *s, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार siz)
अणु
	अक्षर *p;

	म_नकलन(mce_helper, buf, माप(mce_helper));
	mce_helper[माप(mce_helper)-1] = 0;
	p = म_अक्षर(mce_helper, '\n');

	अगर (p)
		*p = 0;

	वापस म_माप(mce_helper) + !!p;
पूर्ण

DEVICE_ATTR(trigger, 0644, show_trigger, set_trigger);

/*
 * mce_chrdev: Character device /dev/mcelog to पढ़ो and clear the MCE log.
 */

अटल DEFINE_SPINLOCK(mce_chrdev_state_lock);
अटल पूर्णांक mce_chrdev_खोलो_count;	/* #बार खोलोed */
अटल पूर्णांक mce_chrdev_खोलो_exclu;	/* alपढ़ोy खोलो exclusive? */

अटल पूर्णांक mce_chrdev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	spin_lock(&mce_chrdev_state_lock);

	अगर (mce_chrdev_खोलो_exclu ||
	    (mce_chrdev_खोलो_count && (file->f_flags & O_EXCL))) अणु
		spin_unlock(&mce_chrdev_state_lock);

		वापस -EBUSY;
	पूर्ण

	अगर (file->f_flags & O_EXCL)
		mce_chrdev_खोलो_exclu = 1;
	mce_chrdev_खोलो_count++;

	spin_unlock(&mce_chrdev_state_lock);

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक mce_chrdev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	spin_lock(&mce_chrdev_state_lock);

	mce_chrdev_खोलो_count--;
	mce_chrdev_खोलो_exclu = 0;

	spin_unlock(&mce_chrdev_state_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mce_apei_पढ़ो_करोne;

/* Collect MCE record of previous boot in persistent storage via APEI ERST. */
अटल पूर्णांक __mce_पढ़ो_apei(अक्षर __user **ubuf, माप_प्रकार usize)
अणु
	पूर्णांक rc;
	u64 record_id;
	काष्ठा mce m;

	अगर (usize < माप(काष्ठा mce))
		वापस -EINVAL;

	rc = apei_पढ़ो_mce(&m, &record_id);
	/* Error or no more MCE record */
	अगर (rc <= 0) अणु
		mce_apei_पढ़ो_करोne = 1;
		/*
		 * When ERST is disabled, mce_chrdev_पढ़ो() should वापस
		 * "no record" instead of "no device."
		 */
		अगर (rc == -ENODEV)
			वापस 0;
		वापस rc;
	पूर्ण
	rc = -EFAULT;
	अगर (copy_to_user(*ubuf, &m, माप(काष्ठा mce)))
		वापस rc;
	/*
	 * In fact, we should have cleared the record after that has
	 * been flushed to the disk or sent to network in
	 * /sbin/mcelog, but we have no पूर्णांकerface to support that now,
	 * so just clear it to aव्योम duplication.
	 */
	rc = apei_clear_mce(record_id);
	अगर (rc) अणु
		mce_apei_पढ़ो_करोne = 1;
		वापस rc;
	पूर्ण
	*ubuf += माप(काष्ठा mce);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mce_chrdev_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				माप_प्रकार usize, loff_t *off)
अणु
	अक्षर __user *buf = ubuf;
	अचिन्हित next;
	पूर्णांक i, err;

	mutex_lock(&mce_chrdev_पढ़ो_mutex);

	अगर (!mce_apei_पढ़ो_करोne) अणु
		err = __mce_पढ़ो_apei(&buf, usize);
		अगर (err || buf != ubuf)
			जाओ out;
	पूर्ण

	/* Only supports full पढ़ोs right now */
	err = -EINVAL;
	अगर (*off != 0 || usize < mcelog->len * माप(काष्ठा mce))
		जाओ out;

	next = mcelog->next;
	err = 0;

	क्रम (i = 0; i < next; i++) अणु
		काष्ठा mce *m = &mcelog->entry[i];

		err |= copy_to_user(buf, m, माप(*m));
		buf += माप(*m);
	पूर्ण

	स_रखो(mcelog->entry, 0, next * माप(काष्ठा mce));
	mcelog->next = 0;

	अगर (err)
		err = -EFAULT;

out:
	mutex_unlock(&mce_chrdev_पढ़ो_mutex);

	वापस err ? err : buf - ubuf;
पूर्ण

अटल __poll_t mce_chrdev_poll(काष्ठा file *file, poll_table *रुको)
अणु
	poll_रुको(file, &mce_chrdev_रुको, रुको);
	अगर (READ_ONCE(mcelog->next))
		वापस EPOLLIN | EPOLLRDNORM;
	अगर (!mce_apei_पढ़ो_करोne && apei_check_mce())
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

अटल दीर्घ mce_chrdev_ioctl(काष्ठा file *f, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	पूर्णांक __user *p = (पूर्णांक __user *)arg;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल MCE_GET_RECORD_LEN:
		वापस put_user(माप(काष्ठा mce), p);
	हाल MCE_GET_LOG_LEN:
		वापस put_user(mcelog->len, p);
	हाल MCE_GETCLEAR_FLAGS: अणु
		अचिन्हित flags;

		करो अणु
			flags = mcelog->flags;
		पूर्ण जबतक (cmpxchg(&mcelog->flags, flags, 0) != flags);

		वापस put_user(flags, p);
	पूर्ण
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

व्योम mce_रेजिस्टर_injector_chain(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_रेजिस्टर(&mce_injector_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(mce_रेजिस्टर_injector_chain);

व्योम mce_unरेजिस्टर_injector_chain(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&mce_injector_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(mce_unरेजिस्टर_injector_chain);

अटल sमाप_प्रकार mce_chrdev_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
				माप_प्रकार usize, loff_t *off)
अणु
	काष्ठा mce m;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	/*
	 * There are some हालs where real MSR पढ़ोs could slip
	 * through.
	 */
	अगर (!boot_cpu_has(X86_FEATURE_MCE) || !boot_cpu_has(X86_FEATURE_MCA))
		वापस -EIO;

	अगर ((अचिन्हित दीर्घ)usize > माप(काष्ठा mce))
		usize = माप(काष्ठा mce);
	अगर (copy_from_user(&m, ubuf, usize))
		वापस -EFAULT;

	अगर (m.extcpu >= num_possible_cpus() || !cpu_online(m.extcpu))
		वापस -EINVAL;

	/*
	 * Need to give user space some समय to set everything up,
	 * so करो it a jअगरfie or two later everywhere.
	 */
	schedule_समयout(2);

	blocking_notअगरier_call_chain(&mce_injector_chain, 0, &m);

	वापस usize;
पूर्ण

अटल स्थिर काष्ठा file_operations mce_chrdev_ops = अणु
	.खोलो			= mce_chrdev_खोलो,
	.release		= mce_chrdev_release,
	.पढ़ो			= mce_chrdev_पढ़ो,
	.ग_लिखो			= mce_chrdev_ग_लिखो,
	.poll			= mce_chrdev_poll,
	.unlocked_ioctl		= mce_chrdev_ioctl,
	.compat_ioctl		= compat_ptr_ioctl,
	.llseek			= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice mce_chrdev_device = अणु
	MISC_MCELOG_MINOR,
	"mcelog",
	&mce_chrdev_ops,
पूर्ण;

अटल __init पूर्णांक dev_mcelog_init_device(व्योम)
अणु
	पूर्णांक mce_log_len;
	पूर्णांक err;

	mce_log_len = max(MCE_LOG_MIN_LEN, num_online_cpus());
	mcelog = kzalloc(काष्ठा_size(mcelog, entry, mce_log_len), GFP_KERNEL);
	अगर (!mcelog)
		वापस -ENOMEM;

	स_नकल(mcelog->signature, MCE_LOG_SIGNATURE, माप(mcelog->signature));
	mcelog->len = mce_log_len;
	mcelog->recordlen = माप(काष्ठा mce);

	/* रेजिस्टर अक्षरacter device /dev/mcelog */
	err = misc_रेजिस्टर(&mce_chrdev_device);
	अगर (err) अणु
		अगर (err == -EBUSY)
			/* Xen करोm0 might have रेजिस्टरed the device alपढ़ोy. */
			pr_info("Unable to init device /dev/mcelog, already registered");
		अन्यथा
			pr_err("Unable to init device /dev/mcelog (rc: %d)\n", err);

		kमुक्त(mcelog);
		वापस err;
	पूर्ण

	mce_रेजिस्टर_decode_chain(&dev_mcelog_nb);
	वापस 0;
पूर्ण
device_initcall_sync(dev_mcelog_init_device);
