<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Provides user-space access to the SSAM EC via the /dev/surface/aggregator
 * misc device. Intended क्रम debugging and development.
 *
 * Copyright (C) 2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/surface_aggregator/cdev.h>
#समावेश <linux/surface_aggregator/controller.h>

#घोषणा SSAM_CDEV_DEVICE_NAME	"surface_aggregator_cdev"

काष्ठा ssam_cdev अणु
	काष्ठा kref kref;
	काष्ठा rw_semaphore lock;
	काष्ठा ssam_controller *ctrl;
	काष्ठा miscdevice mdev;
पूर्ण;

अटल व्योम __ssam_cdev_release(काष्ठा kref *kref)
अणु
	kमुक्त(container_of(kref, काष्ठा ssam_cdev, kref));
पूर्ण

अटल काष्ठा ssam_cdev *ssam_cdev_get(काष्ठा ssam_cdev *cdev)
अणु
	अगर (cdev)
		kref_get(&cdev->kref);

	वापस cdev;
पूर्ण

अटल व्योम ssam_cdev_put(काष्ठा ssam_cdev *cdev)
अणु
	अगर (cdev)
		kref_put(&cdev->kref, __ssam_cdev_release);
पूर्ण

अटल पूर्णांक ssam_cdev_device_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा miscdevice *mdev = filp->निजी_data;
	काष्ठा ssam_cdev *cdev = container_of(mdev, काष्ठा ssam_cdev, mdev);

	filp->निजी_data = ssam_cdev_get(cdev);
	वापस stream_खोलो(inode, filp);
पूर्ण

अटल पूर्णांक ssam_cdev_device_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	ssam_cdev_put(filp->निजी_data);
	वापस 0;
पूर्ण

अटल दीर्घ ssam_cdev_request(काष्ठा ssam_cdev *cdev, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ssam_cdev_request __user *r;
	काष्ठा ssam_cdev_request rqst;
	काष्ठा ssam_request spec = अणुपूर्ण;
	काष्ठा ssam_response rsp = अणुपूर्ण;
	स्थिर व्योम __user *plddata;
	व्योम __user *rspdata;
	पूर्णांक status = 0, ret = 0, पंचांगp;

	r = (काष्ठा ssam_cdev_request __user *)arg;
	ret = copy_काष्ठा_from_user(&rqst, माप(rqst), r, माप(*r));
	अगर (ret)
		जाओ out;

	plddata = u64_to_user_ptr(rqst.payload.data);
	rspdata = u64_to_user_ptr(rqst.response.data);

	/* Setup basic request fields. */
	spec.target_category = rqst.target_category;
	spec.target_id = rqst.target_id;
	spec.command_id = rqst.command_id;
	spec.instance_id = rqst.instance_id;
	spec.flags = 0;
	spec.length = rqst.payload.length;
	spec.payload = शून्य;

	अगर (rqst.flags & SSAM_CDEV_REQUEST_HAS_RESPONSE)
		spec.flags |= SSAM_REQUEST_HAS_RESPONSE;

	अगर (rqst.flags & SSAM_CDEV_REQUEST_UNSEQUENCED)
		spec.flags |= SSAM_REQUEST_UNSEQUENCED;

	rsp.capacity = rqst.response.length;
	rsp.length = 0;
	rsp.poपूर्णांकer = शून्य;

	/* Get request payload from user-space. */
	अगर (spec.length) अणु
		अगर (!plddata) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		/*
		 * Note: spec.length is limited to U16_MAX bytes via काष्ठा
		 * ssam_cdev_request. This is slightly larger than the
		 * theoretical maximum (SSH_COMMAND_MAX_PAYLOAD_SIZE) of the
		 * underlying protocol (note that nothing remotely this size
		 * should ever be allocated in any normal हाल). This size is
		 * validated later in ssam_request_sync(), क्रम allocation the
		 * bound imposed by u16 should be enough.
		 */
		spec.payload = kzalloc(spec.length, GFP_KERNEL);
		अगर (!spec.payload) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		अगर (copy_from_user((व्योम *)spec.payload, plddata, spec.length)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Allocate response buffer. */
	अगर (rsp.capacity) अणु
		अगर (!rspdata) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		/*
		 * Note: rsp.capacity is limited to U16_MAX bytes via काष्ठा
		 * ssam_cdev_request. This is slightly larger than the
		 * theoretical maximum (SSH_COMMAND_MAX_PAYLOAD_SIZE) of the
		 * underlying protocol (note that nothing remotely this size
		 * should ever be allocated in any normal हाल). In later use,
		 * this capacity करोes not have to be strictly bounded, as it
		 * is only used as an output buffer to be written to. For
		 * allocation the bound imposed by u16 should be enough.
		 */
		rsp.poपूर्णांकer = kzalloc(rsp.capacity, GFP_KERNEL);
		अगर (!rsp.poपूर्णांकer) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Perक्रमm request. */
	status = ssam_request_sync(cdev->ctrl, &spec, &rsp);
	अगर (status)
		जाओ out;

	/* Copy response to user-space. */
	अगर (rsp.length && copy_to_user(rspdata, rsp.poपूर्णांकer, rsp.length))
		ret = -EFAULT;

out:
	/* Always try to set response-length and status. */
	पंचांगp = put_user(rsp.length, &r->response.length);
	अगर (पंचांगp)
		ret = पंचांगp;

	पंचांगp = put_user(status, &r->status);
	अगर (पंचांगp)
		ret = पंचांगp;

	/* Cleanup. */
	kमुक्त(spec.payload);
	kमुक्त(rsp.poपूर्णांकer);

	वापस ret;
पूर्ण

अटल दीर्घ __ssam_cdev_device_ioctl(काष्ठा ssam_cdev *cdev, अचिन्हित पूर्णांक cmd,
				     अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल SSAM_CDEV_REQUEST:
		वापस ssam_cdev_request(cdev, arg);

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल दीर्घ ssam_cdev_device_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				   अचिन्हित दीर्घ arg)
अणु
	काष्ठा ssam_cdev *cdev = file->निजी_data;
	दीर्घ status;

	/* Ensure that controller is valid क्रम as दीर्घ as we need it. */
	अगर (करोwn_पढ़ो_समाप्तable(&cdev->lock))
		वापस -ERESTARTSYS;

	अगर (!cdev->ctrl) अणु
		up_पढ़ो(&cdev->lock);
		वापस -ENODEV;
	पूर्ण

	status = __ssam_cdev_device_ioctl(cdev, cmd, arg);

	up_पढ़ो(&cdev->lock);
	वापस status;
पूर्ण

अटल स्थिर काष्ठा file_operations ssam_controller_fops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = ssam_cdev_device_खोलो,
	.release        = ssam_cdev_device_release,
	.unlocked_ioctl = ssam_cdev_device_ioctl,
	.compat_ioctl   = ssam_cdev_device_ioctl,
	.llseek         = noop_llseek,
पूर्ण;

अटल पूर्णांक ssam_dbg_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ssam_controller *ctrl;
	काष्ठा ssam_cdev *cdev;
	पूर्णांक status;

	ctrl = ssam_client_bind(&pdev->dev);
	अगर (IS_ERR(ctrl))
		वापस PTR_ERR(ctrl) == -ENODEV ? -EPROBE_DEFER : PTR_ERR(ctrl);

	cdev = kzalloc(माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस -ENOMEM;

	kref_init(&cdev->kref);
	init_rwsem(&cdev->lock);
	cdev->ctrl = ctrl;

	cdev->mdev.parent   = &pdev->dev;
	cdev->mdev.minor    = MISC_DYNAMIC_MINOR;
	cdev->mdev.name     = "surface_aggregator";
	cdev->mdev.nodename = "surface/aggregator";
	cdev->mdev.fops     = &ssam_controller_fops;

	status = misc_रेजिस्टर(&cdev->mdev);
	अगर (status) अणु
		kमुक्त(cdev);
		वापस status;
	पूर्ण

	platक्रमm_set_drvdata(pdev, cdev);
	वापस 0;
पूर्ण

अटल पूर्णांक ssam_dbg_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ssam_cdev *cdev = platक्रमm_get_drvdata(pdev);

	misc_deरेजिस्टर(&cdev->mdev);

	/*
	 * The controller is only guaranteed to be valid क्रम as दीर्घ as the
	 * driver is bound. Remove controller so that any lingering खोलो files
	 * cannot access it any more after we're gone.
	 */
	करोwn_ग_लिखो(&cdev->lock);
	cdev->ctrl = शून्य;
	up_ग_लिखो(&cdev->lock);

	ssam_cdev_put(cdev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device *ssam_cdev_device;

अटल काष्ठा platक्रमm_driver ssam_cdev_driver = अणु
	.probe = ssam_dbg_device_probe,
	.हटाओ = ssam_dbg_device_हटाओ,
	.driver = अणु
		.name = SSAM_CDEV_DEVICE_NAME,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ssam_debug_init(व्योम)
अणु
	पूर्णांक status;

	ssam_cdev_device = platक्रमm_device_alloc(SSAM_CDEV_DEVICE_NAME,
						 PLATFORM_DEVID_NONE);
	अगर (!ssam_cdev_device)
		वापस -ENOMEM;

	status = platक्रमm_device_add(ssam_cdev_device);
	अगर (status)
		जाओ err_device;

	status = platक्रमm_driver_रेजिस्टर(&ssam_cdev_driver);
	अगर (status)
		जाओ err_driver;

	वापस 0;

err_driver:
	platक्रमm_device_del(ssam_cdev_device);
err_device:
	platक्रमm_device_put(ssam_cdev_device);
	वापस status;
पूर्ण
module_init(ssam_debug_init);

अटल व्योम __निकास ssam_debug_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ssam_cdev_driver);
	platक्रमm_device_unरेजिस्टर(ssam_cdev_device);
पूर्ण
module_निकास(ssam_debug_निकास);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("User-space interface for Surface System Aggregator Module");
MODULE_LICENSE("GPL");
