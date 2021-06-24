<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IBM/3270 Driver - fullscreen driver.
 *
 * Author(s):
 *   Original 3270 Code क्रम 2.4 written by Riअक्षरd Hitt (UTS Global)
 *   Rewritten क्रम 2.5/2.6 by Martin Schwidefsky <schwidefsky@de.ibm.com>
 *     Copyright IBM Corp. 2003, 2009
 */

#समावेश <linux/memblock.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/compat.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/idals.h>

#समावेश "raw3270.h"
#समावेश "ctrlchar.h"

अटल काष्ठा raw3270_fn fs3270_fn;

काष्ठा fs3270 अणु
	काष्ठा raw3270_view view;
	काष्ठा pid *fs_pid;		/* Pid of controlling program. */
	पूर्णांक पढ़ो_command;		/* ccw command to use क्रम पढ़ोs. */
	पूर्णांक ग_लिखो_command;		/* ccw command to use क्रम ग_लिखोs. */
	पूर्णांक attention;			/* Got attention. */
	पूर्णांक active;			/* Fullscreen view is active. */
	काष्ठा raw3270_request *init;	/* single init request. */
	रुको_queue_head_t रुको;		/* Init & attention रुको queue. */
	काष्ठा idal_buffer *rdbuf;	/* full-screen-deactivate buffer */
	माप_प्रकार rdbuf_size;		/* size of data वापसed by RDBUF */
पूर्ण;

अटल DEFINE_MUTEX(fs3270_mutex);

अटल व्योम
fs3270_wake_up(काष्ठा raw3270_request *rq, व्योम *data)
अणु
	wake_up((रुको_queue_head_t *) data);
पूर्ण

अटल अंतरभूत पूर्णांक
fs3270_working(काष्ठा fs3270 *fp)
अणु
	/*
	 * The fullscreen view is in working order अगर the view
	 * has been activated AND the initial request is finished.
	 */
	वापस fp->active && raw3270_request_final(fp->init);
पूर्ण

अटल पूर्णांक
fs3270_करो_io(काष्ठा raw3270_view *view, काष्ठा raw3270_request *rq)
अणु
	काष्ठा fs3270 *fp;
	पूर्णांक rc;

	fp = (काष्ठा fs3270 *) view;
	rq->callback = fs3270_wake_up;
	rq->callback_data = &fp->रुको;

	करो अणु
		अगर (!fs3270_working(fp)) अणु
			/* Fullscreen view isn't पढ़ोy yet. */
			rc = रुको_event_पूर्णांकerruptible(fp->रुको,
						      fs3270_working(fp));
			अगर (rc != 0)
				अवरोध;
		पूर्ण
		rc = raw3270_start(view, rq);
		अगर (rc == 0) अणु
			/* Started successfully. Now रुको क्रम completion. */
			रुको_event(fp->रुको, raw3270_request_final(rq));
		पूर्ण
	पूर्ण जबतक (rc == -EACCES);
	वापस rc;
पूर्ण

/*
 * Switch to the fullscreen view.
 */
अटल व्योम
fs3270_reset_callback(काष्ठा raw3270_request *rq, व्योम *data)
अणु
	काष्ठा fs3270 *fp;

	fp = (काष्ठा fs3270 *) rq->view;
	raw3270_request_reset(rq);
	wake_up(&fp->रुको);
पूर्ण

अटल व्योम
fs3270_restore_callback(काष्ठा raw3270_request *rq, व्योम *data)
अणु
	काष्ठा fs3270 *fp;

	fp = (काष्ठा fs3270 *) rq->view;
	अगर (rq->rc != 0 || rq->rescnt != 0) अणु
		अगर (fp->fs_pid)
			समाप्त_pid(fp->fs_pid, SIGHUP, 1);
	पूर्ण
	fp->rdbuf_size = 0;
	raw3270_request_reset(rq);
	wake_up(&fp->रुको);
पूर्ण

अटल पूर्णांक
fs3270_activate(काष्ठा raw3270_view *view)
अणु
	काष्ठा fs3270 *fp;
	अक्षर *cp;
	पूर्णांक rc;

	fp = (काष्ठा fs3270 *) view;

	/* If an old init command is still running just वापस. */
	अगर (!raw3270_request_final(fp->init))
		वापस 0;

	अगर (fp->rdbuf_size == 0) अणु
		/* No saved buffer. Just clear the screen. */
		raw3270_request_set_cmd(fp->init, TC_EWRITEA);
		fp->init->callback = fs3270_reset_callback;
	पूर्ण अन्यथा अणु
		/* Restore fullscreen buffer saved by fs3270_deactivate. */
		raw3270_request_set_cmd(fp->init, TC_EWRITEA);
		raw3270_request_set_idal(fp->init, fp->rdbuf);
		fp->init->ccw.count = fp->rdbuf_size;
		cp = fp->rdbuf->data[0];
		cp[0] = TW_KR;
		cp[1] = TO_SBA;
		cp[2] = cp[6];
		cp[3] = cp[7];
		cp[4] = TO_IC;
		cp[5] = TO_SBA;
		cp[6] = 0x40;
		cp[7] = 0x40;
		fp->init->rescnt = 0;
		fp->init->callback = fs3270_restore_callback;
	पूर्ण
	rc = fp->init->rc = raw3270_start_locked(view, fp->init);
	अगर (rc)
		fp->init->callback(fp->init, शून्य);
	अन्यथा
		fp->active = 1;
	वापस rc;
पूर्ण

/*
 * Shutकरोwn fullscreen view.
 */
अटल व्योम
fs3270_save_callback(काष्ठा raw3270_request *rq, व्योम *data)
अणु
	काष्ठा fs3270 *fp;

	fp = (काष्ठा fs3270 *) rq->view;

	/* Correct idal buffer element 0 address. */
	fp->rdbuf->data[0] -= 5;
	fp->rdbuf->size += 5;

	/*
	 * If the rdbuf command failed or the idal buffer is
	 * to small क्रम the amount of data वापसed by the
	 * rdbuf command, then we have no choice but to send
	 * a SIGHUP to the application.
	 */
	अगर (rq->rc != 0 || rq->rescnt == 0) अणु
		अगर (fp->fs_pid)
			समाप्त_pid(fp->fs_pid, SIGHUP, 1);
		fp->rdbuf_size = 0;
	पूर्ण अन्यथा
		fp->rdbuf_size = fp->rdbuf->size - rq->rescnt;
	raw3270_request_reset(rq);
	wake_up(&fp->रुको);
पूर्ण

अटल व्योम
fs3270_deactivate(काष्ठा raw3270_view *view)
अणु
	काष्ठा fs3270 *fp;

	fp = (काष्ठा fs3270 *) view;
	fp->active = 0;

	/* If an old init command is still running just वापस. */
	अगर (!raw3270_request_final(fp->init))
		वापस;

	/* Prepare पढ़ो-buffer request. */
	raw3270_request_set_cmd(fp->init, TC_RDBUF);
	/*
	 * Hackish: skip first 5 bytes of the idal buffer to make
	 * room क्रम the TW_KR/TO_SBA/<address>/<address>/TO_IC sequence
	 * in the activation command.
	 */
	fp->rdbuf->data[0] += 5;
	fp->rdbuf->size -= 5;
	raw3270_request_set_idal(fp->init, fp->rdbuf);
	fp->init->rescnt = 0;
	fp->init->callback = fs3270_save_callback;

	/* Start I/O to पढ़ो in the 3270 buffer. */
	fp->init->rc = raw3270_start_locked(view, fp->init);
	अगर (fp->init->rc)
		fp->init->callback(fp->init, शून्य);
पूर्ण

अटल व्योम
fs3270_irq(काष्ठा fs3270 *fp, काष्ठा raw3270_request *rq, काष्ठा irb *irb)
अणु
	/* Handle ATTN. Set indication and wake रुकोers क्रम attention. */
	अगर (irb->scsw.cmd.dstat & DEV_STAT_ATTENTION) अणु
		fp->attention = 1;
		wake_up(&fp->रुको);
	पूर्ण

	अगर (rq) अणु
		अगर (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK)
			rq->rc = -EIO;
		अन्यथा
			/* Normal end. Copy residual count. */
			rq->rescnt = irb->scsw.cmd.count;
	पूर्ण
पूर्ण

/*
 * Process पढ़ोs from fullscreen 3270.
 */
अटल sमाप_प्रकार
fs3270_पढ़ो(काष्ठा file *filp, अक्षर __user *data, माप_प्रकार count, loff_t *off)
अणु
	काष्ठा fs3270 *fp;
	काष्ठा raw3270_request *rq;
	काष्ठा idal_buffer *ib;
	sमाप_प्रकार rc;
	
	अगर (count == 0 || count > 65535)
		वापस -EINVAL;
	fp = filp->निजी_data;
	अगर (!fp)
		वापस -ENODEV;
	ib = idal_buffer_alloc(count, 0);
	अगर (IS_ERR(ib))
		वापस -ENOMEM;
	rq = raw3270_request_alloc(0);
	अगर (!IS_ERR(rq)) अणु
		अगर (fp->पढ़ो_command == 0 && fp->ग_लिखो_command != 0)
			fp->पढ़ो_command = 6;
		raw3270_request_set_cmd(rq, fp->पढ़ो_command ? : 2);
		raw3270_request_set_idal(rq, ib);
		rc = रुको_event_पूर्णांकerruptible(fp->रुको, fp->attention);
		fp->attention = 0;
		अगर (rc == 0) अणु
			rc = fs3270_करो_io(&fp->view, rq);
			अगर (rc == 0) अणु
				count -= rq->rescnt;
				अगर (idal_buffer_to_user(ib, data, count) != 0)
					rc = -EFAULT;
				अन्यथा
					rc = count;

			पूर्ण
		पूर्ण
		raw3270_request_मुक्त(rq);
	पूर्ण अन्यथा
		rc = PTR_ERR(rq);
	idal_buffer_मुक्त(ib);
	वापस rc;
पूर्ण

/*
 * Process ग_लिखोs to fullscreen 3270.
 */
अटल sमाप_प्रकार
fs3270_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *data, माप_प्रकार count, loff_t *off)
अणु
	काष्ठा fs3270 *fp;
	काष्ठा raw3270_request *rq;
	काष्ठा idal_buffer *ib;
	पूर्णांक ग_लिखो_command;
	sमाप_प्रकार rc;

	fp = filp->निजी_data;
	अगर (!fp)
		वापस -ENODEV;
	ib = idal_buffer_alloc(count, 0);
	अगर (IS_ERR(ib))
		वापस -ENOMEM;
	rq = raw3270_request_alloc(0);
	अगर (!IS_ERR(rq)) अणु
		अगर (idal_buffer_from_user(ib, data, count) == 0) अणु
			ग_लिखो_command = fp->ग_लिखो_command ? : 1;
			अगर (ग_लिखो_command == 5)
				ग_लिखो_command = 13;
			raw3270_request_set_cmd(rq, ग_लिखो_command);
			raw3270_request_set_idal(rq, ib);
			rc = fs3270_करो_io(&fp->view, rq);
			अगर (rc == 0)
				rc = count - rq->rescnt;
		पूर्ण अन्यथा
			rc = -EFAULT;
		raw3270_request_मुक्त(rq);
	पूर्ण अन्यथा
		rc = PTR_ERR(rq);
	idal_buffer_मुक्त(ib);
	वापस rc;
पूर्ण

/*
 * process ioctl commands क्रम the tube driver
 */
अटल दीर्घ
fs3270_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अक्षर __user *argp;
	काष्ठा fs3270 *fp;
	काष्ठा raw3270_iocb iocb;
	पूर्णांक rc;

	fp = filp->निजी_data;
	अगर (!fp)
		वापस -ENODEV;
	अगर (is_compat_task())
		argp = compat_ptr(arg);
	अन्यथा
		argp = (अक्षर __user *)arg;
	rc = 0;
	mutex_lock(&fs3270_mutex);
	चयन (cmd) अणु
	हाल TUBICMD:
		fp->पढ़ो_command = arg;
		अवरोध;
	हाल TUBOCMD:
		fp->ग_लिखो_command = arg;
		अवरोध;
	हाल TUBGETI:
		rc = put_user(fp->पढ़ो_command, argp);
		अवरोध;
	हाल TUBGETO:
		rc = put_user(fp->ग_लिखो_command, argp);
		अवरोध;
	हाल TUBGETMOD:
		iocb.model = fp->view.model;
		iocb.line_cnt = fp->view.rows;
		iocb.col_cnt = fp->view.cols;
		iocb.pf_cnt = 24;
		iocb.re_cnt = 20;
		iocb.map = 0;
		अगर (copy_to_user(argp, &iocb, माप(काष्ठा raw3270_iocb)))
			rc = -EFAULT;
		अवरोध;
	पूर्ण
	mutex_unlock(&fs3270_mutex);
	वापस rc;
पूर्ण

/*
 * Allocate fs3270 काष्ठाure.
 */
अटल काष्ठा fs3270 *
fs3270_alloc_view(व्योम)
अणु
	काष्ठा fs3270 *fp;

	fp = kzalloc(माप(काष्ठा fs3270),GFP_KERNEL);
	अगर (!fp)
		वापस ERR_PTR(-ENOMEM);
	fp->init = raw3270_request_alloc(0);
	अगर (IS_ERR(fp->init)) अणु
		kमुक्त(fp);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	वापस fp;
पूर्ण

/*
 * Free fs3270 काष्ठाure.
 */
अटल व्योम
fs3270_मुक्त_view(काष्ठा raw3270_view *view)
अणु
	काष्ठा fs3270 *fp;

	fp = (काष्ठा fs3270 *) view;
	अगर (fp->rdbuf)
		idal_buffer_मुक्त(fp->rdbuf);
	raw3270_request_मुक्त(((काष्ठा fs3270 *) view)->init);
	kमुक्त(view);
पूर्ण

/*
 * Unlink fs3270 data काष्ठाure from filp.
 */
अटल व्योम
fs3270_release(काष्ठा raw3270_view *view)
अणु
	काष्ठा fs3270 *fp;

	fp = (काष्ठा fs3270 *) view;
	अगर (fp->fs_pid)
		समाप्त_pid(fp->fs_pid, SIGHUP, 1);
पूर्ण

/* View to a 3270 device. Can be console, tty or fullscreen. */
अटल काष्ठा raw3270_fn fs3270_fn = अणु
	.activate = fs3270_activate,
	.deactivate = fs3270_deactivate,
	.पूर्णांकv = (व्योम *) fs3270_irq,
	.release = fs3270_release,
	.मुक्त = fs3270_मुक्त_view
पूर्ण;

/*
 * This routine is called whenever a 3270 fullscreen device is खोलोed.
 */
अटल पूर्णांक
fs3270_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा fs3270 *fp;
	काष्ठा idal_buffer *ib;
	पूर्णांक minor, rc = 0;

	अगर (imajor(file_inode(filp)) != IBM_FS3270_MAJOR)
		वापस -ENODEV;
	minor = iminor(file_inode(filp));
	/* Check क्रम minor 0 multiplexer. */
	अगर (minor == 0) अणु
		काष्ठा tty_काष्ठा *tty = get_current_tty();
		अगर (!tty || tty->driver->major != IBM_TTY3270_MAJOR) अणु
			tty_kref_put(tty);
			वापस -ENODEV;
		पूर्ण
		minor = tty->index;
		tty_kref_put(tty);
	पूर्ण
	mutex_lock(&fs3270_mutex);
	/* Check अगर some other program is alपढ़ोy using fullscreen mode. */
	fp = (काष्ठा fs3270 *) raw3270_find_view(&fs3270_fn, minor);
	अगर (!IS_ERR(fp)) अणु
		raw3270_put_view(&fp->view);
		rc = -EBUSY;
		जाओ out;
	पूर्ण
	/* Allocate fullscreen view काष्ठाure. */
	fp = fs3270_alloc_view();
	अगर (IS_ERR(fp)) अणु
		rc = PTR_ERR(fp);
		जाओ out;
	पूर्ण

	init_रुकोqueue_head(&fp->रुको);
	fp->fs_pid = get_pid(task_pid(current));
	rc = raw3270_add_view(&fp->view, &fs3270_fn, minor,
			      RAW3270_VIEW_LOCK_BH);
	अगर (rc) अणु
		fs3270_मुक्त_view(&fp->view);
		जाओ out;
	पूर्ण

	/* Allocate idal-buffer. */
	ib = idal_buffer_alloc(2*fp->view.rows*fp->view.cols + 5, 0);
	अगर (IS_ERR(ib)) अणु
		raw3270_put_view(&fp->view);
		raw3270_del_view(&fp->view);
		rc = PTR_ERR(ib);
		जाओ out;
	पूर्ण
	fp->rdbuf = ib;

	rc = raw3270_activate_view(&fp->view);
	अगर (rc) अणु
		raw3270_put_view(&fp->view);
		raw3270_del_view(&fp->view);
		जाओ out;
	पूर्ण
	stream_खोलो(inode, filp);
	filp->निजी_data = fp;
out:
	mutex_unlock(&fs3270_mutex);
	वापस rc;
पूर्ण

/*
 * This routine is called when the 3270 tty is बंदd. We रुको
 * क्रम the reमुख्यing request to be completed. Then we clean up.
 */
अटल पूर्णांक
fs3270_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा fs3270 *fp;

	fp = filp->निजी_data;
	filp->निजी_data = शून्य;
	अगर (fp) अणु
		put_pid(fp->fs_pid);
		fp->fs_pid = शून्य;
		raw3270_reset(&fp->view);
		raw3270_put_view(&fp->view);
		raw3270_del_view(&fp->view);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations fs3270_fops = अणु
	.owner		 = THIS_MODULE,		/* owner */
	.पढ़ो		 = fs3270_पढ़ो,		/* पढ़ो */
	.ग_लिखो		 = fs3270_ग_लिखो,	/* ग_लिखो */
	.unlocked_ioctl	 = fs3270_ioctl,	/* ioctl */
	.compat_ioctl	 = fs3270_ioctl,	/* ioctl */
	.खोलो		 = fs3270_खोलो,		/* खोलो */
	.release	 = fs3270_बंद,	/* release */
	.llseek		= no_llseek,
पूर्ण;

अटल व्योम fs3270_create_cb(पूर्णांक minor)
अणु
	__रेजिस्टर_chrdev(IBM_FS3270_MAJOR, minor, 1, "tub", &fs3270_fops);
	device_create(class3270, शून्य, MKDEV(IBM_FS3270_MAJOR, minor),
		      शून्य, "3270/tub%d", minor);
पूर्ण

अटल व्योम fs3270_destroy_cb(पूर्णांक minor)
अणु
	device_destroy(class3270, MKDEV(IBM_FS3270_MAJOR, minor));
	__unरेजिस्टर_chrdev(IBM_FS3270_MAJOR, minor, 1, "tub");
पूर्ण

अटल काष्ठा raw3270_notअगरier fs3270_notअगरier =
अणु
	.create = fs3270_create_cb,
	.destroy = fs3270_destroy_cb,
पूर्ण;

/*
 * 3270 fullscreen driver initialization.
 */
अटल पूर्णांक __init
fs3270_init(व्योम)
अणु
	पूर्णांक rc;

	rc = __रेजिस्टर_chrdev(IBM_FS3270_MAJOR, 0, 1, "fs3270", &fs3270_fops);
	अगर (rc)
		वापस rc;
	device_create(class3270, शून्य, MKDEV(IBM_FS3270_MAJOR, 0),
		      शून्य, "3270/tub");
	raw3270_रेजिस्टर_notअगरier(&fs3270_notअगरier);
	वापस 0;
पूर्ण

अटल व्योम __निकास
fs3270_निकास(व्योम)
अणु
	raw3270_unरेजिस्टर_notअगरier(&fs3270_notअगरier);
	device_destroy(class3270, MKDEV(IBM_FS3270_MAJOR, 0));
	__unरेजिस्टर_chrdev(IBM_FS3270_MAJOR, 0, 1, "fs3270");
पूर्ण

MODULE_LICENSE("GPL");
MODULE_ALIAS_CHARDEV_MAJOR(IBM_FS3270_MAJOR);

module_init(fs3270_init);
module_निकास(fs3270_निकास);
