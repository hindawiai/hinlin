<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PPS core file
 *
 * Copyright (C) 2005-2009   Roकरोlfo Giometti <giometti@linux.it>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/idr.h>
#समावेश <linux/mutex.h>
#समावेश <linux/cdev.h>
#समावेश <linux/poll.h>
#समावेश <linux/pps_kernel.h>
#समावेश <linux/slab.h>

#समावेश "kc.h"

/*
 * Local variables
 */

अटल dev_t pps_devt;
अटल काष्ठा class *pps_class;

अटल DEFINE_MUTEX(pps_idr_lock);
अटल DEFINE_IDR(pps_idr);

/*
 * Char device methods
 */

अटल __poll_t pps_cdev_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा pps_device *pps = file->निजी_data;

	poll_रुको(file, &pps->queue, रुको);

	वापस EPOLLIN | EPOLLRDNORM;
पूर्ण

अटल पूर्णांक pps_cdev_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा pps_device *pps = file->निजी_data;
	वापस fasync_helper(fd, file, on, &pps->async_queue);
पूर्ण

अटल पूर्णांक pps_cdev_pps_fetch(काष्ठा pps_device *pps, काष्ठा pps_fdata *fdata)
अणु
	अचिन्हित पूर्णांक ev = pps->last_ev;
	पूर्णांक err = 0;

	/* Manage the समयout */
	अगर (fdata->समयout.flags & PPS_TIME_INVALID)
		err = रुको_event_पूर्णांकerruptible(pps->queue,
				ev != pps->last_ev);
	अन्यथा अणु
		अचिन्हित दीर्घ ticks;

		dev_dbg(pps->dev, "timeout %lld.%09d\n",
				(दीर्घ दीर्घ) fdata->समयout.sec,
				fdata->समयout.nsec);
		ticks = fdata->समयout.sec * HZ;
		ticks += fdata->समयout.nsec / (NSEC_PER_SEC / HZ);

		अगर (ticks != 0) अणु
			err = रुको_event_पूर्णांकerruptible_समयout(
					pps->queue,
					ev != pps->last_ev,
					ticks);
			अगर (err == 0)
				वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	/* Check क्रम pending संकेतs */
	अगर (err == -ERESTARTSYS) अणु
		dev_dbg(pps->dev, "pending signal caught\n");
		वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ pps_cdev_ioctl(काष्ठा file *file,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा pps_device *pps = file->निजी_data;
	काष्ठा pps_kparams params;
	व्योम __user *uarg = (व्योम __user *) arg;
	पूर्णांक __user *iuarg = (पूर्णांक __user *) arg;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल PPS_GETPARAMS:
		dev_dbg(pps->dev, "PPS_GETPARAMS\n");

		spin_lock_irq(&pps->lock);

		/* Get the current parameters */
		params = pps->params;

		spin_unlock_irq(&pps->lock);

		err = copy_to_user(uarg, &params, माप(काष्ठा pps_kparams));
		अगर (err)
			वापस -EFAULT;

		अवरोध;

	हाल PPS_SETPARAMS:
		dev_dbg(pps->dev, "PPS_SETPARAMS\n");

		/* Check the capabilities */
		अगर (!capable(CAP_SYS_TIME))
			वापस -EPERM;

		err = copy_from_user(&params, uarg, माप(काष्ठा pps_kparams));
		अगर (err)
			वापस -EFAULT;
		अगर (!(params.mode & (PPS_CAPTUREASSERT | PPS_CAPTURECLEAR))) अणु
			dev_dbg(pps->dev, "capture mode unspecified (%x)\n",
								params.mode);
			वापस -EINVAL;
		पूर्ण

		/* Check क्रम supported capabilities */
		अगर ((params.mode & ~pps->info.mode) != 0) अणु
			dev_dbg(pps->dev, "unsupported capabilities (%x)\n",
								params.mode);
			वापस -EINVAL;
		पूर्ण

		spin_lock_irq(&pps->lock);

		/* Save the new parameters */
		pps->params = params;

		/* Restore the पढ़ो only parameters */
		अगर ((params.mode & (PPS_TSFMT_TSPEC | PPS_TSFMT_NTPFP)) == 0) अणु
			/* section 3.3 of RFC 2783 पूर्णांकerpreted */
			dev_dbg(pps->dev, "time format unspecified (%x)\n",
								params.mode);
			pps->params.mode |= PPS_TSFMT_TSPEC;
		पूर्ण
		अगर (pps->info.mode & PPS_CANWAIT)
			pps->params.mode |= PPS_CANWAIT;
		pps->params.api_version = PPS_API_VERS;

		/*
		 * Clear unused fields of pps_kparams to aव्योम leaking
		 * uninitialized data of the PPS_SETPARAMS caller via
		 * PPS_GETPARAMS
		 */
		pps->params.निश्चित_off_tu.flags = 0;
		pps->params.clear_off_tu.flags = 0;

		spin_unlock_irq(&pps->lock);

		अवरोध;

	हाल PPS_GETCAP:
		dev_dbg(pps->dev, "PPS_GETCAP\n");

		err = put_user(pps->info.mode, iuarg);
		अगर (err)
			वापस -EFAULT;

		अवरोध;

	हाल PPS_FETCH: अणु
		काष्ठा pps_fdata fdata;

		dev_dbg(pps->dev, "PPS_FETCH\n");

		err = copy_from_user(&fdata, uarg, माप(काष्ठा pps_fdata));
		अगर (err)
			वापस -EFAULT;

		err = pps_cdev_pps_fetch(pps, &fdata);
		अगर (err)
			वापस err;

		/* Return the fetched बारtamp */
		spin_lock_irq(&pps->lock);

		fdata.info.निश्चित_sequence = pps->निश्चित_sequence;
		fdata.info.clear_sequence = pps->clear_sequence;
		fdata.info.निश्चित_tu = pps->निश्चित_tu;
		fdata.info.clear_tu = pps->clear_tu;
		fdata.info.current_mode = pps->current_mode;

		spin_unlock_irq(&pps->lock);

		err = copy_to_user(uarg, &fdata, माप(काष्ठा pps_fdata));
		अगर (err)
			वापस -EFAULT;

		अवरोध;
	पूर्ण
	हाल PPS_KC_BIND: अणु
		काष्ठा pps_bind_args bind_args;

		dev_dbg(pps->dev, "PPS_KC_BIND\n");

		/* Check the capabilities */
		अगर (!capable(CAP_SYS_TIME))
			वापस -EPERM;

		अगर (copy_from_user(&bind_args, uarg,
					माप(काष्ठा pps_bind_args)))
			वापस -EFAULT;

		/* Check क्रम supported capabilities */
		अगर ((bind_args.edge & ~pps->info.mode) != 0) अणु
			dev_err(pps->dev, "unsupported capabilities (%x)\n",
					bind_args.edge);
			वापस -EINVAL;
		पूर्ण

		/* Validate parameters roughly */
		अगर (bind_args.tsक्रमmat != PPS_TSFMT_TSPEC ||
				(bind_args.edge & ~PPS_CAPTUREBOTH) != 0 ||
				bind_args.consumer != PPS_KC_HARDPPS) अणु
			dev_err(pps->dev, "invalid kernel consumer bind"
					" parameters (%x)\n", bind_args.edge);
			वापस -EINVAL;
		पूर्ण

		err = pps_kc_bind(pps, &bind_args);
		अगर (err < 0)
			वापस err;

		अवरोध;
	पूर्ण
	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ pps_cdev_compat_ioctl(काष्ठा file *file,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा pps_device *pps = file->निजी_data;
	व्योम __user *uarg = (व्योम __user *) arg;

	cmd = _IOC(_IOC_सूची(cmd), _IOC_TYPE(cmd), _IOC_NR(cmd), माप(व्योम *));

	अगर (cmd == PPS_FETCH) अणु
		काष्ठा pps_fdata_compat compat;
		काष्ठा pps_fdata fdata;
		पूर्णांक err;

		dev_dbg(pps->dev, "PPS_FETCH\n");

		err = copy_from_user(&compat, uarg, माप(काष्ठा pps_fdata_compat));
		अगर (err)
			वापस -EFAULT;

		स_नकल(&fdata.समयout, &compat.समयout,
					माप(काष्ठा pps_kसमय_compat));

		err = pps_cdev_pps_fetch(pps, &fdata);
		अगर (err)
			वापस err;

		/* Return the fetched बारtamp */
		spin_lock_irq(&pps->lock);

		compat.info.निश्चित_sequence = pps->निश्चित_sequence;
		compat.info.clear_sequence = pps->clear_sequence;
		compat.info.current_mode = pps->current_mode;

		स_नकल(&compat.info.निश्चित_tu, &pps->निश्चित_tu,
				माप(काष्ठा pps_kसमय_compat));
		स_नकल(&compat.info.clear_tu, &pps->clear_tu,
				माप(काष्ठा pps_kसमय_compat));

		spin_unlock_irq(&pps->lock);

		वापस copy_to_user(uarg, &compat,
				माप(काष्ठा pps_fdata_compat)) ? -EFAULT : 0;
	पूर्ण

	वापस pps_cdev_ioctl(file, cmd, arg);
पूर्ण
#अन्यथा
#घोषणा pps_cdev_compat_ioctl	शून्य
#पूर्ण_अगर

अटल पूर्णांक pps_cdev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा pps_device *pps = container_of(inode->i_cdev,
						काष्ठा pps_device, cdev);
	file->निजी_data = pps;
	kobject_get(&pps->dev->kobj);
	वापस 0;
पूर्ण

अटल पूर्णांक pps_cdev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा pps_device *pps = container_of(inode->i_cdev,
						काष्ठा pps_device, cdev);
	kobject_put(&pps->dev->kobj);
	वापस 0;
पूर्ण

/*
 * Char device stuff
 */

अटल स्थिर काष्ठा file_operations pps_cdev_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.poll		= pps_cdev_poll,
	.fasync		= pps_cdev_fasync,
	.compat_ioctl	= pps_cdev_compat_ioctl,
	.unlocked_ioctl	= pps_cdev_ioctl,
	.खोलो		= pps_cdev_खोलो,
	.release	= pps_cdev_release,
पूर्ण;

अटल व्योम pps_device_deकाष्ठा(काष्ठा device *dev)
अणु
	काष्ठा pps_device *pps = dev_get_drvdata(dev);

	cdev_del(&pps->cdev);

	/* Now we can release the ID क्रम re-use */
	pr_debug("deallocating pps%d\n", pps->id);
	mutex_lock(&pps_idr_lock);
	idr_हटाओ(&pps_idr, pps->id);
	mutex_unlock(&pps_idr_lock);

	kमुक्त(dev);
	kमुक्त(pps);
पूर्ण

पूर्णांक pps_रेजिस्टर_cdev(काष्ठा pps_device *pps)
अणु
	पूर्णांक err;
	dev_t devt;

	mutex_lock(&pps_idr_lock);
	/*
	 * Get new ID क्रम the new PPS source.  After idr_alloc() calling
	 * the new source will be मुक्तly available पूर्णांकo the kernel.
	 */
	err = idr_alloc(&pps_idr, pps, 0, PPS_MAX_SOURCES, GFP_KERNEL);
	अगर (err < 0) अणु
		अगर (err == -ENOSPC) अणु
			pr_err("%s: too many PPS sources in the system\n",
			       pps->info.name);
			err = -EBUSY;
		पूर्ण
		जाओ out_unlock;
	पूर्ण
	pps->id = err;
	mutex_unlock(&pps_idr_lock);

	devt = MKDEV(MAJOR(pps_devt), pps->id);

	cdev_init(&pps->cdev, &pps_cdev_fops);
	pps->cdev.owner = pps->info.owner;

	err = cdev_add(&pps->cdev, devt, 1);
	अगर (err) अणु
		pr_err("%s: failed to add char device %d:%d\n",
				pps->info.name, MAJOR(pps_devt), pps->id);
		जाओ मुक्त_idr;
	पूर्ण
	pps->dev = device_create(pps_class, pps->info.dev, devt, pps,
							"pps%d", pps->id);
	अगर (IS_ERR(pps->dev)) अणु
		err = PTR_ERR(pps->dev);
		जाओ del_cdev;
	पूर्ण

	/* Override the release function with our own */
	pps->dev->release = pps_device_deकाष्ठा;

	pr_debug("source %s got cdev (%d:%d)\n", pps->info.name,
			MAJOR(pps_devt), pps->id);

	वापस 0;

del_cdev:
	cdev_del(&pps->cdev);

मुक्त_idr:
	mutex_lock(&pps_idr_lock);
	idr_हटाओ(&pps_idr, pps->id);
out_unlock:
	mutex_unlock(&pps_idr_lock);
	वापस err;
पूर्ण

व्योम pps_unरेजिस्टर_cdev(काष्ठा pps_device *pps)
अणु
	pr_debug("unregistering pps%d\n", pps->id);
	pps->lookup_cookie = शून्य;
	device_destroy(pps_class, pps->dev->devt);
पूर्ण

/*
 * Look up a pps device by magic cookie.
 * The cookie is usually a poपूर्णांकer to some enclosing device, but this
 * code करोesn't care; you should never be dereferencing it.
 *
 * This is a bit of a kludge that is currently used only by the PPS
 * serial line discipline.  It may need to be tweaked when a second user
 * is found.
 *
 * There is no function पूर्णांकerface क्रम setting the lookup_cookie field.
 * It's initialized to शून्य when the pps device is created, and अगर a
 * client wants to use it, just fill it in afterward.
 *
 * The cookie is स्वतःmatically set to शून्य in pps_unरेजिस्टर_source()
 * so that it will not be used again, even अगर the pps device cannot
 * be हटाओd from the idr due to pending references holding the minor
 * number in use.
 */
काष्ठा pps_device *pps_lookup_dev(व्योम स्थिर *cookie)
अणु
	काष्ठा pps_device *pps;
	अचिन्हित id;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&pps_idr, pps, id)
		अगर (cookie == pps->lookup_cookie)
			अवरोध;
	rcu_पढ़ो_unlock();
	वापस pps;
पूर्ण
EXPORT_SYMBOL(pps_lookup_dev);

/*
 * Module stuff
 */

अटल व्योम __निकास pps_निकास(व्योम)
अणु
	class_destroy(pps_class);
	unरेजिस्टर_chrdev_region(pps_devt, PPS_MAX_SOURCES);
पूर्ण

अटल पूर्णांक __init pps_init(व्योम)
अणु
	पूर्णांक err;

	pps_class = class_create(THIS_MODULE, "pps");
	अगर (IS_ERR(pps_class)) अणु
		pr_err("failed to allocate class\n");
		वापस PTR_ERR(pps_class);
	पूर्ण
	pps_class->dev_groups = pps_groups;

	err = alloc_chrdev_region(&pps_devt, 0, PPS_MAX_SOURCES, "pps");
	अगर (err < 0) अणु
		pr_err("failed to allocate char device region\n");
		जाओ हटाओ_class;
	पूर्ण

	pr_info("LinuxPPS API ver. %d registered\n", PPS_API_VERS);
	pr_info("Software ver. %s - Copyright 2005-2007 Rodolfo Giometti "
		"<giometti@linux.it>\n", PPS_VERSION);

	वापस 0;

हटाओ_class:
	class_destroy(pps_class);

	वापस err;
पूर्ण

subsys_initcall(pps_init);
module_निकास(pps_निकास);

MODULE_AUTHOR("Rodolfo Giometti <giometti@linux.it>");
MODULE_DESCRIPTION("LinuxPPS support (RFC 2783) - ver. " PPS_VERSION);
MODULE_LICENSE("GPL");
