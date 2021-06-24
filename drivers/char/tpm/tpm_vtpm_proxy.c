<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015, 2016 IBM Corporation
 * Copyright (C) 2016 Intel Corporation
 *
 * Author: Stefan Berger <stefanb@us.ibm.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Device driver क्रम vTPM (vTPM proxy driver)
 */

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/रुको.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/vtpm_proxy.h>
#समावेश <linux/file.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/poll.h>
#समावेश <linux/compat.h>

#समावेश "tpm.h"

#घोषणा VTPM_PROXY_REQ_COMPLETE_FLAG  BIT(0)

काष्ठा proxy_dev अणु
	काष्ठा tpm_chip *chip;

	u32 flags;                   /* खुला API flags */

	रुको_queue_head_t wq;

	काष्ठा mutex buf_lock;       /* protect buffer and flags */

	दीर्घ state;                  /* पूर्णांकernal state */
#घोषणा STATE_OPENED_FLAG        BIT(0)
#घोषणा STATE_WAIT_RESPONSE_FLAG BIT(1)  /* रुकोing क्रम emulator response */
#घोषणा STATE_REGISTERED_FLAG	 BIT(2)
#घोषणा STATE_DRIVER_COMMAND     BIT(3)  /* sending a driver specअगरic command */

	माप_प्रकार req_len;              /* length of queued TPM request */
	माप_प्रकार resp_len;             /* length of queued TPM response */
	u8 buffer[TPM_बफ_मानE];      /* request/response buffer */

	काष्ठा work_काष्ठा work;     /* task that retrieves TPM समयouts */
पूर्ण;

/* all supported flags */
#घोषणा VTPM_PROXY_FLAGS_ALL  (VTPM_PROXY_FLAG_TPM2)

अटल काष्ठा workqueue_काष्ठा *workqueue;

अटल व्योम vtpm_proxy_delete_device(काष्ठा proxy_dev *proxy_dev);

/*
 * Functions related to 'server side'
 */

/**
 * vtpm_proxy_fops_पढ़ो - Read TPM commands on 'server side'
 *
 * @filp: file poपूर्णांकer
 * @buf: पढ़ो buffer
 * @count: number of bytes to पढ़ो
 * @off: offset
 *
 * Return:
 *	Number of bytes पढ़ो or negative error code
 */
अटल sमाप_प्रकार vtpm_proxy_fops_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
				    माप_प्रकार count, loff_t *off)
अणु
	काष्ठा proxy_dev *proxy_dev = filp->निजी_data;
	माप_प्रकार len;
	पूर्णांक sig, rc;

	sig = रुको_event_पूर्णांकerruptible(proxy_dev->wq,
		proxy_dev->req_len != 0 ||
		!(proxy_dev->state & STATE_OPENED_FLAG));
	अगर (sig)
		वापस -EINTR;

	mutex_lock(&proxy_dev->buf_lock);

	अगर (!(proxy_dev->state & STATE_OPENED_FLAG)) अणु
		mutex_unlock(&proxy_dev->buf_lock);
		वापस -EPIPE;
	पूर्ण

	len = proxy_dev->req_len;

	अगर (count < len) अणु
		mutex_unlock(&proxy_dev->buf_lock);
		pr_debug("Invalid size in recv: count=%zd, req_len=%zd\n",
			 count, len);
		वापस -EIO;
	पूर्ण

	rc = copy_to_user(buf, proxy_dev->buffer, len);
	स_रखो(proxy_dev->buffer, 0, len);
	proxy_dev->req_len = 0;

	अगर (!rc)
		proxy_dev->state |= STATE_WAIT_RESPONSE_FLAG;

	mutex_unlock(&proxy_dev->buf_lock);

	अगर (rc)
		वापस -EFAULT;

	वापस len;
पूर्ण

/**
 * vtpm_proxy_fops_ग_लिखो - Write TPM responses on 'server side'
 *
 * @filp: file poपूर्णांकer
 * @buf: ग_लिखो buffer
 * @count: number of bytes to ग_लिखो
 * @off: offset
 *
 * Return:
 *	Number of bytes पढ़ो or negative error value
 */
अटल sमाप_प्रकार vtpm_proxy_fops_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
				     माप_प्रकार count, loff_t *off)
अणु
	काष्ठा proxy_dev *proxy_dev = filp->निजी_data;

	mutex_lock(&proxy_dev->buf_lock);

	अगर (!(proxy_dev->state & STATE_OPENED_FLAG)) अणु
		mutex_unlock(&proxy_dev->buf_lock);
		वापस -EPIPE;
	पूर्ण

	अगर (count > माप(proxy_dev->buffer) ||
	    !(proxy_dev->state & STATE_WAIT_RESPONSE_FLAG)) अणु
		mutex_unlock(&proxy_dev->buf_lock);
		वापस -EIO;
	पूर्ण

	proxy_dev->state &= ~STATE_WAIT_RESPONSE_FLAG;

	proxy_dev->req_len = 0;

	अगर (copy_from_user(proxy_dev->buffer, buf, count)) अणु
		mutex_unlock(&proxy_dev->buf_lock);
		वापस -EFAULT;
	पूर्ण

	proxy_dev->resp_len = count;

	mutex_unlock(&proxy_dev->buf_lock);

	wake_up_पूर्णांकerruptible(&proxy_dev->wq);

	वापस count;
पूर्ण

/*
 * vtpm_proxy_fops_poll - Poll status on 'server side'
 *
 * @filp: file poपूर्णांकer
 * @रुको: poll table
 *
 * Return: Poll flags
 */
अटल __poll_t vtpm_proxy_fops_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा proxy_dev *proxy_dev = filp->निजी_data;
	__poll_t ret;

	poll_रुको(filp, &proxy_dev->wq, रुको);

	ret = EPOLLOUT;

	mutex_lock(&proxy_dev->buf_lock);

	अगर (proxy_dev->req_len)
		ret |= EPOLLIN | EPOLLRDNORM;

	अगर (!(proxy_dev->state & STATE_OPENED_FLAG))
		ret |= EPOLLHUP;

	mutex_unlock(&proxy_dev->buf_lock);

	वापस ret;
पूर्ण

/*
 * vtpm_proxy_fops_खोलो - Open vTPM device on 'server side'
 *
 * @filp: file poपूर्णांकer
 *
 * Called when setting up the anonymous file descriptor
 */
अटल व्योम vtpm_proxy_fops_खोलो(काष्ठा file *filp)
अणु
	काष्ठा proxy_dev *proxy_dev = filp->निजी_data;

	proxy_dev->state |= STATE_OPENED_FLAG;
पूर्ण

/**
 * vtpm_proxy_fops_unकरो_खोलो - counter-part to vtpm_fops_खोलो
 *       Call to unकरो vtpm_proxy_fops_खोलो
 *
 *@proxy_dev: tpm proxy device
 */
अटल व्योम vtpm_proxy_fops_unकरो_खोलो(काष्ठा proxy_dev *proxy_dev)
अणु
	mutex_lock(&proxy_dev->buf_lock);

	proxy_dev->state &= ~STATE_OPENED_FLAG;

	mutex_unlock(&proxy_dev->buf_lock);

	/* no more TPM responses -- wake up anyone रुकोing क्रम them */
	wake_up_पूर्णांकerruptible(&proxy_dev->wq);
पूर्ण

/*
 * vtpm_proxy_fops_release - Close 'server side'
 *
 * @inode: inode
 * @filp: file poपूर्णांकer
 * Return:
 *      Always वापसs 0.
 */
अटल पूर्णांक vtpm_proxy_fops_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा proxy_dev *proxy_dev = filp->निजी_data;

	filp->निजी_data = शून्य;

	vtpm_proxy_delete_device(proxy_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations vtpm_proxy_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.पढ़ो = vtpm_proxy_fops_पढ़ो,
	.ग_लिखो = vtpm_proxy_fops_ग_लिखो,
	.poll = vtpm_proxy_fops_poll,
	.release = vtpm_proxy_fops_release,
पूर्ण;

/*
 * Functions invoked by the core TPM driver to send TPM commands to
 * 'server side' and receive responses from there.
 */

/*
 * Called when core TPM driver पढ़ोs TPM responses from 'server side'
 *
 * @chip: tpm chip to use
 * @buf: receive buffer
 * @count: bytes to पढ़ो
 * Return:
 *      Number of TPM response bytes पढ़ो, negative error value otherwise
 */
अटल पूर्णांक vtpm_proxy_tpm_op_recv(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा proxy_dev *proxy_dev = dev_get_drvdata(&chip->dev);
	माप_प्रकार len;

	/* process gone ? */
	mutex_lock(&proxy_dev->buf_lock);

	अगर (!(proxy_dev->state & STATE_OPENED_FLAG)) अणु
		mutex_unlock(&proxy_dev->buf_lock);
		वापस -EPIPE;
	पूर्ण

	len = proxy_dev->resp_len;
	अगर (count < len) अणु
		dev_err(&chip->dev,
			"Invalid size in recv: count=%zd, resp_len=%zd\n",
			count, len);
		len = -EIO;
		जाओ out;
	पूर्ण

	स_नकल(buf, proxy_dev->buffer, len);
	proxy_dev->resp_len = 0;

out:
	mutex_unlock(&proxy_dev->buf_lock);

	वापस len;
पूर्ण

अटल पूर्णांक vtpm_proxy_is_driver_command(काष्ठा tpm_chip *chip,
					u8 *buf, माप_प्रकार count)
अणु
	काष्ठा tpm_header *hdr = (काष्ठा tpm_header *)buf;

	अगर (count < माप(काष्ठा tpm_header))
		वापस 0;

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2) अणु
		चयन (be32_to_cpu(hdr->ordinal)) अणु
		हाल TPM2_CC_SET_LOCALITY:
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (be32_to_cpu(hdr->ordinal)) अणु
		हाल TPM_ORD_SET_LOCALITY:
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Called when core TPM driver क्रमwards TPM requests to 'server side'.
 *
 * @chip: tpm chip to use
 * @buf: send buffer
 * @count: bytes to send
 *
 * Return:
 *      0 in हाल of success, negative error value otherwise.
 */
अटल पूर्णांक vtpm_proxy_tpm_op_send(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा proxy_dev *proxy_dev = dev_get_drvdata(&chip->dev);

	अगर (count > माप(proxy_dev->buffer)) अणु
		dev_err(&chip->dev,
			"Invalid size in send: count=%zd, buffer size=%zd\n",
			count, माप(proxy_dev->buffer));
		वापस -EIO;
	पूर्ण

	अगर (!(proxy_dev->state & STATE_DRIVER_COMMAND) &&
	    vtpm_proxy_is_driver_command(chip, buf, count))
		वापस -EFAULT;

	mutex_lock(&proxy_dev->buf_lock);

	अगर (!(proxy_dev->state & STATE_OPENED_FLAG)) अणु
		mutex_unlock(&proxy_dev->buf_lock);
		वापस -EPIPE;
	पूर्ण

	proxy_dev->resp_len = 0;

	proxy_dev->req_len = count;
	स_नकल(proxy_dev->buffer, buf, count);

	proxy_dev->state &= ~STATE_WAIT_RESPONSE_FLAG;

	mutex_unlock(&proxy_dev->buf_lock);

	wake_up_पूर्णांकerruptible(&proxy_dev->wq);

	वापस 0;
पूर्ण

अटल व्योम vtpm_proxy_tpm_op_cancel(काष्ठा tpm_chip *chip)
अणु
	/* not supported */
पूर्ण

अटल u8 vtpm_proxy_tpm_op_status(काष्ठा tpm_chip *chip)
अणु
	काष्ठा proxy_dev *proxy_dev = dev_get_drvdata(&chip->dev);

	अगर (proxy_dev->resp_len)
		वापस VTPM_PROXY_REQ_COMPLETE_FLAG;

	वापस 0;
पूर्ण

अटल bool vtpm_proxy_tpm_req_canceled(काष्ठा tpm_chip  *chip, u8 status)
अणु
	काष्ठा proxy_dev *proxy_dev = dev_get_drvdata(&chip->dev);
	bool ret;

	mutex_lock(&proxy_dev->buf_lock);

	ret = !(proxy_dev->state & STATE_OPENED_FLAG);

	mutex_unlock(&proxy_dev->buf_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक vtpm_proxy_request_locality(काष्ठा tpm_chip *chip, पूर्णांक locality)
अणु
	काष्ठा tpm_buf buf;
	पूर्णांक rc;
	स्थिर काष्ठा tpm_header *header;
	काष्ठा proxy_dev *proxy_dev = dev_get_drvdata(&chip->dev);

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
		rc = tpm_buf_init(&buf, TPM2_ST_SESSIONS,
				  TPM2_CC_SET_LOCALITY);
	अन्यथा
		rc = tpm_buf_init(&buf, TPM_TAG_RQU_COMMAND,
				  TPM_ORD_SET_LOCALITY);
	अगर (rc)
		वापस rc;
	tpm_buf_append_u8(&buf, locality);

	proxy_dev->state |= STATE_DRIVER_COMMAND;

	rc = tpm_transmit_cmd(chip, &buf, 0, "attempting to set locality");

	proxy_dev->state &= ~STATE_DRIVER_COMMAND;

	अगर (rc < 0) अणु
		locality = rc;
		जाओ out;
	पूर्ण

	header = (स्थिर काष्ठा tpm_header *)buf.data;
	rc = be32_to_cpu(header->वापस_code);
	अगर (rc)
		locality = -1;

out:
	tpm_buf_destroy(&buf);

	वापस locality;
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops vtpm_proxy_tpm_ops = अणु
	.flags = TPM_OPS_AUTO_STARTUP,
	.recv = vtpm_proxy_tpm_op_recv,
	.send = vtpm_proxy_tpm_op_send,
	.cancel = vtpm_proxy_tpm_op_cancel,
	.status = vtpm_proxy_tpm_op_status,
	.req_complete_mask = VTPM_PROXY_REQ_COMPLETE_FLAG,
	.req_complete_val = VTPM_PROXY_REQ_COMPLETE_FLAG,
	.req_canceled = vtpm_proxy_tpm_req_canceled,
	.request_locality = vtpm_proxy_request_locality,
पूर्ण;

/*
 * Code related to the startup of the TPM 2 and startup of TPM 1.2 +
 * retrieval of समयouts and durations.
 */

अटल व्योम vtpm_proxy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा proxy_dev *proxy_dev = container_of(work, काष्ठा proxy_dev,
						   work);
	पूर्णांक rc;

	rc = tpm_chip_रेजिस्टर(proxy_dev->chip);
	अगर (rc)
		vtpm_proxy_fops_unकरो_खोलो(proxy_dev);
	अन्यथा
		proxy_dev->state |= STATE_REGISTERED_FLAG;
पूर्ण

/*
 * vtpm_proxy_work_stop: make sure the work has finished
 *
 * This function is useful when user space बंदd the fd
 * जबतक the driver still determines समयouts.
 */
अटल व्योम vtpm_proxy_work_stop(काष्ठा proxy_dev *proxy_dev)
अणु
	vtpm_proxy_fops_unकरो_खोलो(proxy_dev);
	flush_work(&proxy_dev->work);
पूर्ण

/*
 * vtpm_proxy_work_start: Schedule the work क्रम TPM 1.2 & 2 initialization
 */
अटल अंतरभूत व्योम vtpm_proxy_work_start(काष्ठा proxy_dev *proxy_dev)
अणु
	queue_work(workqueue, &proxy_dev->work);
पूर्ण

/*
 * Code related to creation and deletion of device pairs
 */
अटल काष्ठा proxy_dev *vtpm_proxy_create_proxy_dev(व्योम)
अणु
	काष्ठा proxy_dev *proxy_dev;
	काष्ठा tpm_chip *chip;
	पूर्णांक err;

	proxy_dev = kzalloc(माप(*proxy_dev), GFP_KERNEL);
	अगर (proxy_dev == शून्य)
		वापस ERR_PTR(-ENOMEM);

	init_रुकोqueue_head(&proxy_dev->wq);
	mutex_init(&proxy_dev->buf_lock);
	INIT_WORK(&proxy_dev->work, vtpm_proxy_work);

	chip = tpm_chip_alloc(शून्य, &vtpm_proxy_tpm_ops);
	अगर (IS_ERR(chip)) अणु
		err = PTR_ERR(chip);
		जाओ err_proxy_dev_मुक्त;
	पूर्ण
	dev_set_drvdata(&chip->dev, proxy_dev);

	proxy_dev->chip = chip;

	वापस proxy_dev;

err_proxy_dev_मुक्त:
	kमुक्त(proxy_dev);

	वापस ERR_PTR(err);
पूर्ण

/*
 * Unकरो what has been करोne in vtpm_create_proxy_dev
 */
अटल अंतरभूत व्योम vtpm_proxy_delete_proxy_dev(काष्ठा proxy_dev *proxy_dev)
अणु
	put_device(&proxy_dev->chip->dev); /* मुक्तs chip */
	kमुक्त(proxy_dev);
पूर्ण

/*
 * Create a /dev/tpm%d and 'server side' file descriptor pair
 *
 * Return:
 *      Returns file poपूर्णांकer on success, an error value otherwise
 */
अटल काष्ठा file *vtpm_proxy_create_device(
				 काष्ठा vtpm_proxy_new_dev *vtpm_new_dev)
अणु
	काष्ठा proxy_dev *proxy_dev;
	पूर्णांक rc, fd;
	काष्ठा file *file;

	अगर (vtpm_new_dev->flags & ~VTPM_PROXY_FLAGS_ALL)
		वापस ERR_PTR(-EOPNOTSUPP);

	proxy_dev = vtpm_proxy_create_proxy_dev();
	अगर (IS_ERR(proxy_dev))
		वापस ERR_CAST(proxy_dev);

	proxy_dev->flags = vtpm_new_dev->flags;

	/* setup an anonymous file क्रम the server-side */
	fd = get_unused_fd_flags(O_RDWR);
	अगर (fd < 0) अणु
		rc = fd;
		जाओ err_delete_proxy_dev;
	पूर्ण

	file = anon_inode_getfile("[vtpms]", &vtpm_proxy_fops, proxy_dev,
				  O_RDWR);
	अगर (IS_ERR(file)) अणु
		rc = PTR_ERR(file);
		जाओ err_put_unused_fd;
	पूर्ण

	/* from now on we can unwind with put_unused_fd() + fput() */
	/* simulate an खोलो() on the server side */
	vtpm_proxy_fops_खोलो(file);

	अगर (proxy_dev->flags & VTPM_PROXY_FLAG_TPM2)
		proxy_dev->chip->flags |= TPM_CHIP_FLAG_TPM2;

	vtpm_proxy_work_start(proxy_dev);

	vtpm_new_dev->fd = fd;
	vtpm_new_dev->major = MAJOR(proxy_dev->chip->dev.devt);
	vtpm_new_dev->minor = MINOR(proxy_dev->chip->dev.devt);
	vtpm_new_dev->tpm_num = proxy_dev->chip->dev_num;

	वापस file;

err_put_unused_fd:
	put_unused_fd(fd);

err_delete_proxy_dev:
	vtpm_proxy_delete_proxy_dev(proxy_dev);

	वापस ERR_PTR(rc);
पूर्ण

/*
 * Counter part to vtpm_create_device.
 */
अटल व्योम vtpm_proxy_delete_device(काष्ठा proxy_dev *proxy_dev)
अणु
	vtpm_proxy_work_stop(proxy_dev);

	/*
	 * A client may hold the 'ops' lock, so let it know that the server
	 * side shuts करोwn beक्रमe we try to grab the 'ops' lock when
	 * unरेजिस्टरing the chip.
	 */
	vtpm_proxy_fops_unकरो_खोलो(proxy_dev);

	अगर (proxy_dev->state & STATE_REGISTERED_FLAG)
		tpm_chip_unरेजिस्टर(proxy_dev->chip);

	vtpm_proxy_delete_proxy_dev(proxy_dev);
पूर्ण

/*
 * Code related to the control device /dev/vtpmx
 */

/**
 * vtpmx_ioc_new_dev - handler क्रम the %VTPM_PROXY_IOC_NEW_DEV ioctl
 * @file:	/dev/vtpmx
 * @ioctl:	the ioctl number
 * @arg:	poपूर्णांकer to the काष्ठा vtpmx_proxy_new_dev
 *
 * Creates an anonymous file that is used by the process acting as a TPM to
 * communicate with the client processes. The function will also add a new TPM
 * device through which data is proxied to this TPM acting process. The caller
 * will be provided with a file descriptor to communicate with the clients and
 * major and minor numbers क्रम the TPM device.
 */
अटल दीर्घ vtpmx_ioc_new_dev(काष्ठा file *file, अचिन्हित पूर्णांक ioctl,
			      अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा vtpm_proxy_new_dev __user *vtpm_new_dev_p;
	काष्ठा vtpm_proxy_new_dev vtpm_new_dev;
	काष्ठा file *vtpm_file;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	vtpm_new_dev_p = argp;

	अगर (copy_from_user(&vtpm_new_dev, vtpm_new_dev_p,
			   माप(vtpm_new_dev)))
		वापस -EFAULT;

	vtpm_file = vtpm_proxy_create_device(&vtpm_new_dev);
	अगर (IS_ERR(vtpm_file))
		वापस PTR_ERR(vtpm_file);

	अगर (copy_to_user(vtpm_new_dev_p, &vtpm_new_dev,
			 माप(vtpm_new_dev))) अणु
		put_unused_fd(vtpm_new_dev.fd);
		fput(vtpm_file);
		वापस -EFAULT;
	पूर्ण

	fd_install(vtpm_new_dev.fd, vtpm_file);
	वापस 0;
पूर्ण

/*
 * vtpmx_fops_ioctl: ioctl on /dev/vtpmx
 *
 * Return:
 *      Returns 0 on success, a negative error code otherwise.
 */
अटल दीर्घ vtpmx_fops_ioctl(काष्ठा file *f, अचिन्हित पूर्णांक ioctl,
			     अचिन्हित दीर्घ arg)
अणु
	चयन (ioctl) अणु
	हाल VTPM_PROXY_IOC_NEW_DEV:
		वापस vtpmx_ioc_new_dev(f, ioctl, arg);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations vtpmx_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = vtpmx_fops_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice vtpmx_miscdev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "vtpmx",
	.fops = &vtpmx_fops,
पूर्ण;

अटल पूर्णांक vtpmx_init(व्योम)
अणु
	वापस misc_रेजिस्टर(&vtpmx_miscdev);
पूर्ण

अटल व्योम vtpmx_cleanup(व्योम)
अणु
	misc_deरेजिस्टर(&vtpmx_miscdev);
पूर्ण

अटल पूर्णांक __init vtpm_module_init(व्योम)
अणु
	पूर्णांक rc;

	rc = vtpmx_init();
	अगर (rc) अणु
		pr_err("couldn't create vtpmx device\n");
		वापस rc;
	पूर्ण

	workqueue = create_workqueue("tpm-vtpm");
	अगर (!workqueue) अणु
		pr_err("couldn't create workqueue\n");
		rc = -ENOMEM;
		जाओ err_vtpmx_cleanup;
	पूर्ण

	वापस 0;

err_vtpmx_cleanup:
	vtpmx_cleanup();

	वापस rc;
पूर्ण

अटल व्योम __निकास vtpm_module_निकास(व्योम)
अणु
	destroy_workqueue(workqueue);
	vtpmx_cleanup();
पूर्ण

module_init(vtpm_module_init);
module_निकास(vtpm_module_निकास);

MODULE_AUTHOR("Stefan Berger (stefanb@us.ibm.com)");
MODULE_DESCRIPTION("vTPM Driver");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
