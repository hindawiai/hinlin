<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      	An implementation of a loadable kernel mode driver providing
 *		multiple kernel/user space bidirectional communications links.
 *
 * 		Author: 	Alan Cox <alan@lxorguk.ukuu.org.uk>
 * 
 *              Adapted to become the Linux 2.0 Coda pseuकरो device
 *              Peter  Braam  <braam@maths.ox.ac.uk> 
 *              Michael Callahan <mjc@emmy.smith.edu>           
 *
 *              Changes क्रम Linux 2.1
 *              Copyright (c) 1997 Carnegie-Mellon University
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/major.h>
#समावेश <linux/समय.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/delay.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/poll.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/pid_namespace.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#समावेश <linux/coda.h>
#समावेश "coda_psdev.h"
#समावेश "coda_linux.h"

#समावेश "coda_int.h"

/* statistics */
पूर्णांक           coda_hard;         /* allows संकेतs during upcalls */
अचिन्हित दीर्घ coda_समयout = 30; /* .. secs, then संकेतs will dequeue */


काष्ठा venus_comm coda_comms[MAX_CODADEVS];
अटल काष्ठा class *coda_psdev_class;

/*
 * Device operations
 */

अटल __poll_t coda_psdev_poll(काष्ठा file *file, poll_table * रुको)
अणु
        काष्ठा venus_comm *vcp = (काष्ठा venus_comm *) file->निजी_data;
	__poll_t mask = EPOLLOUT | EPOLLWRNORM;

	poll_रुको(file, &vcp->vc_रुकोq, रुको);
	mutex_lock(&vcp->vc_mutex);
	अगर (!list_empty(&vcp->vc_pending))
                mask |= EPOLLIN | EPOLLRDNORM;
	mutex_unlock(&vcp->vc_mutex);

	वापस mask;
पूर्ण

अटल दीर्घ coda_psdev_ioctl(काष्ठा file * filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक data;

	चयन(cmd) अणु
	हाल CIOC_KERNEL_VERSION:
		data = CODA_KERNEL_VERSION;
		वापस put_user(data, (पूर्णांक __user *) arg);
	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	Receive a message written by Venus to the psdev
 */
 
अटल sमाप_प्रकार coda_psdev_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, 
				माप_प्रकार nbytes, loff_t *off)
अणु
        काष्ठा venus_comm *vcp = (काष्ठा venus_comm *) file->निजी_data;
        काष्ठा upc_req *req = शून्य;
        काष्ठा upc_req *पंचांगp;
	काष्ठा list_head *lh;
	काष्ठा coda_in_hdr hdr;
	sमाप_प्रकार retval = 0, count = 0;
	पूर्णांक error;

	/* make sure there is enough to copy out the (opcode, unique) values */
	अगर (nbytes < (2 * माप(u_पूर्णांक32_t)))
		वापस -EINVAL;

        /* Peek at the opcode, uniquefier */
	अगर (copy_from_user(&hdr, buf, 2 * माप(u_पूर्णांक32_t)))
	        वापस -EFAULT;

        अगर (DOWNCALL(hdr.opcode)) अणु
		जोड़ outputArgs *dcbuf;
		पूर्णांक size = माप(*dcbuf);

		अगर  ( nbytes < माप(काष्ठा coda_out_hdr) ) अणु
			pr_warn("coda_downcall opc %d uniq %d, not enough!\n",
				hdr.opcode, hdr.unique);
			count = nbytes;
			जाओ out;
		पूर्ण
		अगर ( nbytes > size ) अणु
			pr_warn("downcall opc %d, uniq %d, too much!",
				hdr.opcode, hdr.unique);
		        nbytes = size;
		पूर्ण
		dcbuf = kvदो_स्मृति(nbytes, GFP_KERNEL);
		अगर (!dcbuf) अणु
			retval = -ENOMEM;
			जाओ out;
		पूर्ण
		अगर (copy_from_user(dcbuf, buf, nbytes)) अणु
			kvमुक्त(dcbuf);
			retval = -EFAULT;
			जाओ out;
		पूर्ण

		/* what करोwncall errors करोes Venus handle ? */
		error = coda_करोwncall(vcp, hdr.opcode, dcbuf, nbytes);

		kvमुक्त(dcbuf);
		अगर (error) अणु
			pr_warn("%s: coda_downcall error: %d\n",
				__func__, error);
			retval = error;
			जाओ out;
		पूर्ण
		count = nbytes;
		जाओ out;
	पूर्ण
        
	/* Look क्रम the message on the processing queue. */
	mutex_lock(&vcp->vc_mutex);
	list_क्रम_each(lh, &vcp->vc_processing) अणु
		पंचांगp = list_entry(lh, काष्ठा upc_req , uc_chain);
		अगर (पंचांगp->uc_unique == hdr.unique) अणु
			req = पंचांगp;
			list_del(&req->uc_chain);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&vcp->vc_mutex);

	अगर (!req) अणु
		pr_warn("%s: msg (%d, %d) not found\n",
			__func__, hdr.opcode, hdr.unique);
		retval = -ESRCH;
		जाओ out;
	पूर्ण

        /* move data पूर्णांकo response buffer. */
	अगर (req->uc_outSize < nbytes) अणु
		pr_warn("%s: too much cnt: %d, cnt: %ld, opc: %d, uniq: %d.\n",
			__func__, req->uc_outSize, (दीर्घ)nbytes,
			hdr.opcode, hdr.unique);
		nbytes = req->uc_outSize; /* करोn't have more space! */
	पूर्ण
        अगर (copy_from_user(req->uc_data, buf, nbytes)) अणु
		req->uc_flags |= CODA_REQ_ABORT;
		wake_up(&req->uc_sleep);
		retval = -EFAULT;
		जाओ out;
	पूर्ण

	/* adjust outsize. is this useful ?? */
	req->uc_outSize = nbytes;
	req->uc_flags |= CODA_REQ_WRITE;
	count = nbytes;

	/* Convert filedescriptor पूर्णांकo a file handle */
	अगर (req->uc_opcode == CODA_OPEN_BY_FD) अणु
		काष्ठा coda_खोलो_by_fd_out *outp =
			(काष्ठा coda_खोलो_by_fd_out *)req->uc_data;
		अगर (!outp->oh.result) अणु
			outp->fh = fget(outp->fd);
			अगर (!outp->fh)
				वापस -EBADF;
		पूर्ण
	पूर्ण

        wake_up(&req->uc_sleep);
out:
        वापस(count ? count : retval);  
पूर्ण

/*
 *	Read a message from the kernel to Venus
 */

अटल sमाप_प्रकार coda_psdev_पढ़ो(काष्ठा file * file, अक्षर __user * buf, 
			       माप_प्रकार nbytes, loff_t *off)
अणु
	DECLARE_WAITQUEUE(रुको, current);
        काष्ठा venus_comm *vcp = (काष्ठा venus_comm *) file->निजी_data;
        काष्ठा upc_req *req;
	sमाप_प्रकार retval = 0, count = 0;

	अगर (nbytes == 0)
		वापस 0;

	mutex_lock(&vcp->vc_mutex);

	add_रुको_queue(&vcp->vc_रुकोq, &रुको);
	set_current_state(TASK_INTERRUPTIBLE);

	जबतक (list_empty(&vcp->vc_pending)) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			retval = -EAGAIN;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			retval = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		mutex_unlock(&vcp->vc_mutex);
		schedule();
		mutex_lock(&vcp->vc_mutex);
	पूर्ण

	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&vcp->vc_रुकोq, &रुको);

	अगर (retval)
		जाओ out;

	req = list_entry(vcp->vc_pending.next, काष्ठा upc_req,uc_chain);
	list_del(&req->uc_chain);

	/* Move the input args पूर्णांकo userspace */
	count = req->uc_inSize;
	अगर (nbytes < req->uc_inSize) अणु
		pr_warn("%s: Venus read %ld bytes of %d in message\n",
			__func__, (दीर्घ)nbytes, req->uc_inSize);
		count = nbytes;
        पूर्ण

	अगर (copy_to_user(buf, req->uc_data, count))
	        retval = -EFAULT;
        
	/* If request was not a संकेत, enqueue and करोn't मुक्त */
	अगर (!(req->uc_flags & CODA_REQ_ASYNC)) अणु
		req->uc_flags |= CODA_REQ_READ;
		list_add_tail(&(req->uc_chain), &vcp->vc_processing);
		जाओ out;
	पूर्ण

	kvमुक्त(req->uc_data);
	kमुक्त(req);
out:
	mutex_unlock(&vcp->vc_mutex);
	वापस (count ? count : retval);
पूर्ण

अटल पूर्णांक coda_psdev_खोलो(काष्ठा inode * inode, काष्ठा file * file)
अणु
	काष्ठा venus_comm *vcp;
	पूर्णांक idx, err;

	अगर (task_active_pid_ns(current) != &init_pid_ns)
		वापस -EINVAL;

	अगर (current_user_ns() != &init_user_ns)
		वापस -EINVAL;

	idx = iminor(inode);
	अगर (idx < 0 || idx >= MAX_CODADEVS)
		वापस -ENODEV;

	err = -EBUSY;
	vcp = &coda_comms[idx];
	mutex_lock(&vcp->vc_mutex);

	अगर (!vcp->vc_inuse) अणु
		vcp->vc_inuse++;

		INIT_LIST_HEAD(&vcp->vc_pending);
		INIT_LIST_HEAD(&vcp->vc_processing);
		init_रुकोqueue_head(&vcp->vc_रुकोq);
		vcp->vc_sb = शून्य;
		vcp->vc_seq = 0;

		file->निजी_data = vcp;
		err = 0;
	पूर्ण

	mutex_unlock(&vcp->vc_mutex);
	वापस err;
पूर्ण


अटल पूर्णांक coda_psdev_release(काष्ठा inode * inode, काष्ठा file * file)
अणु
	काष्ठा venus_comm *vcp = (काष्ठा venus_comm *) file->निजी_data;
	काष्ठा upc_req *req, *पंचांगp;

	अगर (!vcp || !vcp->vc_inuse ) अणु
		pr_warn("%s: Not open.\n", __func__);
		वापस -1;
	पूर्ण

	mutex_lock(&vcp->vc_mutex);

	/* Wakeup clients so they can वापस. */
	list_क्रम_each_entry_safe(req, पंचांगp, &vcp->vc_pending, uc_chain) अणु
		list_del(&req->uc_chain);

		/* Async requests need to be मुक्तd here */
		अगर (req->uc_flags & CODA_REQ_ASYNC) अणु
			kvमुक्त(req->uc_data);
			kमुक्त(req);
			जारी;
		पूर्ण
		req->uc_flags |= CODA_REQ_ABORT;
		wake_up(&req->uc_sleep);
	पूर्ण

	list_क्रम_each_entry_safe(req, पंचांगp, &vcp->vc_processing, uc_chain) अणु
		list_del(&req->uc_chain);

		req->uc_flags |= CODA_REQ_ABORT;
		wake_up(&req->uc_sleep);
	पूर्ण

	file->निजी_data = शून्य;
	vcp->vc_inuse--;
	mutex_unlock(&vcp->vc_mutex);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा file_operations coda_psdev_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= coda_psdev_पढ़ो,
	.ग_लिखो		= coda_psdev_ग_लिखो,
	.poll		= coda_psdev_poll,
	.unlocked_ioctl	= coda_psdev_ioctl,
	.खोलो		= coda_psdev_खोलो,
	.release	= coda_psdev_release,
	.llseek		= noop_llseek,
पूर्ण;

अटल पूर्णांक __init init_coda_psdev(व्योम)
अणु
	पूर्णांक i, err = 0;
	अगर (रेजिस्टर_chrdev(CODA_PSDEV_MAJOR, "coda", &coda_psdev_fops)) अणु
		pr_err("%s: unable to get major %d\n",
		       __func__, CODA_PSDEV_MAJOR);
		वापस -EIO;
	पूर्ण
	coda_psdev_class = class_create(THIS_MODULE, "coda");
	अगर (IS_ERR(coda_psdev_class)) अणु
		err = PTR_ERR(coda_psdev_class);
		जाओ out_chrdev;
	पूर्ण		
	क्रम (i = 0; i < MAX_CODADEVS; i++) अणु
		mutex_init(&(&coda_comms[i])->vc_mutex);
		device_create(coda_psdev_class, शून्य,
			      MKDEV(CODA_PSDEV_MAJOR, i), शून्य, "cfs%d", i);
	पूर्ण
	coda_sysctl_init();
	जाओ out;

out_chrdev:
	unरेजिस्टर_chrdev(CODA_PSDEV_MAJOR, "coda");
out:
	वापस err;
पूर्ण

MODULE_AUTHOR("Jan Harkes, Peter J. Braam");
MODULE_DESCRIPTION("Coda Distributed File System VFS interface");
MODULE_ALIAS_CHARDEV_MAJOR(CODA_PSDEV_MAJOR);
MODULE_LICENSE("GPL");
MODULE_VERSION("7.0");

अटल पूर्णांक __init init_coda(व्योम)
अणु
	पूर्णांक status;
	पूर्णांक i;

	status = coda_init_inodecache();
	अगर (status)
		जाओ out2;
	status = init_coda_psdev();
	अगर ( status ) अणु
		pr_warn("Problem (%d) in init_coda_psdev\n", status);
		जाओ out1;
	पूर्ण
	
	status = रेजिस्टर_fileप्रणाली(&coda_fs_type);
	अगर (status) अणु
		pr_warn("failed to register filesystem!\n");
		जाओ out;
	पूर्ण
	वापस 0;
out:
	क्रम (i = 0; i < MAX_CODADEVS; i++)
		device_destroy(coda_psdev_class, MKDEV(CODA_PSDEV_MAJOR, i));
	class_destroy(coda_psdev_class);
	unरेजिस्टर_chrdev(CODA_PSDEV_MAJOR, "coda");
	coda_sysctl_clean();
out1:
	coda_destroy_inodecache();
out2:
	वापस status;
पूर्ण

अटल व्योम __निकास निकास_coda(व्योम)
अणु
        पूर्णांक err, i;

	err = unरेजिस्टर_fileप्रणाली(&coda_fs_type);
	अगर (err != 0)
		pr_warn("failed to unregister filesystem\n");
	क्रम (i = 0; i < MAX_CODADEVS; i++)
		device_destroy(coda_psdev_class, MKDEV(CODA_PSDEV_MAJOR, i));
	class_destroy(coda_psdev_class);
	unरेजिस्टर_chrdev(CODA_PSDEV_MAJOR, "coda");
	coda_sysctl_clean();
	coda_destroy_inodecache();
पूर्ण

module_init(init_coda);
module_निकास(निकास_coda);

