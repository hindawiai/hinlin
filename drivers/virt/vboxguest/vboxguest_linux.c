<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * vboxguest linux pci driver, अक्षर-dev and input-device code,
 *
 * Copyright (C) 2006-2016 Oracle Corporation
 */

#समावेश <linux/cred.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/poll.h>
#समावेश <linux/vbox_utils.h>
#समावेश "vboxguest_core.h"

/** The device name. */
#घोषणा DEVICE_NAME		"vboxguest"
/** The device name क्रम the device node खोलो to everyone. */
#घोषणा DEVICE_NAME_USER	"vboxuser"
/** VirtualBox PCI venकरोr ID. */
#घोषणा VBOX_VENDORID		0x80ee
/** VMMDev PCI card product ID. */
#घोषणा VMMDEV_DEVICEID		0xcafe

/** Mutex protecting the global vbg_gdev poपूर्णांकer used by vbg_get/put_gdev. */
अटल DEFINE_MUTEX(vbg_gdev_mutex);
/** Global vbg_gdev poपूर्णांकer used by vbg_get/put_gdev. */
अटल काष्ठा vbg_dev *vbg_gdev;

अटल u32 vbg_misc_device_requestor(काष्ठा inode *inode)
अणु
	u32 requestor = VMMDEV_REQUESTOR_USERMODE |
			VMMDEV_REQUESTOR_CON_DONT_KNOW |
			VMMDEV_REQUESTOR_TRUST_NOT_GIVEN;

	अगर (from_kuid(current_user_ns(), current_uid()) == 0)
		requestor |= VMMDEV_REQUESTOR_USR_ROOT;
	अन्यथा
		requestor |= VMMDEV_REQUESTOR_USR_USER;

	अगर (in_egroup_p(inode->i_gid))
		requestor |= VMMDEV_REQUESTOR_GRP_VBOX;

	वापस requestor;
पूर्ण

अटल पूर्णांक vbg_misc_device_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा vbg_session *session;
	काष्ठा vbg_dev *gdev;

	/* misc_खोलो sets filp->निजी_data to our misc device */
	gdev = container_of(filp->निजी_data, काष्ठा vbg_dev, misc_device);

	session = vbg_core_खोलो_session(gdev, vbg_misc_device_requestor(inode));
	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	filp->निजी_data = session;
	वापस 0;
पूर्ण

अटल पूर्णांक vbg_misc_device_user_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा vbg_session *session;
	काष्ठा vbg_dev *gdev;

	/* misc_खोलो sets filp->निजी_data to our misc device */
	gdev = container_of(filp->निजी_data, काष्ठा vbg_dev,
			    misc_device_user);

	session = vbg_core_खोलो_session(gdev, vbg_misc_device_requestor(inode) |
					      VMMDEV_REQUESTOR_USER_DEVICE);
	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	filp->निजी_data = session;
	वापस 0;
पूर्ण

/**
 * Close device.
 * Return: 0 on success, negated त्रुटि_सं on failure.
 * @inode:		Poपूर्णांकer to inode info काष्ठाure.
 * @filp:		Associated file poपूर्णांकer.
 */
अटल पूर्णांक vbg_misc_device_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	vbg_core_बंद_session(filp->निजी_data);
	filp->निजी_data = शून्य;
	वापस 0;
पूर्ण

/**
 * Device I/O Control entry poपूर्णांक.
 * Return: 0 on success, negated त्रुटि_सं on failure.
 * @filp:		Associated file poपूर्णांकer.
 * @req:		The request specअगरied to ioctl().
 * @arg:		The argument specअगरied to ioctl().
 */
अटल दीर्घ vbg_misc_device_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक req,
				  अचिन्हित दीर्घ arg)
अणु
	काष्ठा vbg_session *session = filp->निजी_data;
	माप_प्रकार वापसed_size, size;
	काष्ठा vbg_ioctl_hdr hdr;
	bool is_vmmdev_req;
	पूर्णांक ret = 0;
	व्योम *buf;

	अगर (copy_from_user(&hdr, (व्योम *)arg, माप(hdr)))
		वापस -EFAULT;

	अगर (hdr.version != VBG_IOCTL_HDR_VERSION)
		वापस -EINVAL;

	अगर (hdr.size_in < माप(hdr) ||
	    (hdr.size_out && hdr.size_out < माप(hdr)))
		वापस -EINVAL;

	size = max(hdr.size_in, hdr.size_out);
	अगर (_IOC_SIZE(req) && _IOC_SIZE(req) != size)
		वापस -EINVAL;
	अगर (size > SZ_16M)
		वापस -E2BIG;

	/*
	 * IOCTL_VMMDEV_REQUEST needs the buffer to be below 4G to aव्योम
	 * the need क्रम a bounce-buffer and another copy later on.
	 */
	is_vmmdev_req = (req & ~IOCSIZE_MASK) == VBG_IOCTL_VMMDEV_REQUEST(0) ||
			 req == VBG_IOCTL_VMMDEV_REQUEST_BIG ||
			 req == VBG_IOCTL_VMMDEV_REQUEST_BIG_ALT;

	अगर (is_vmmdev_req)
		buf = vbg_req_alloc(size, VBG_IOCTL_HDR_TYPE_DEFAULT,
				    session->requestor);
	अन्यथा
		buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	*((काष्ठा vbg_ioctl_hdr *)buf) = hdr;
	अगर (copy_from_user(buf + माप(hdr), (व्योम *)arg + माप(hdr),
			   hdr.size_in - माप(hdr))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	अगर (hdr.size_in < size)
		स_रखो(buf + hdr.size_in, 0, size -  hdr.size_in);

	ret = vbg_core_ioctl(session, req, buf);
	अगर (ret)
		जाओ out;

	वापसed_size = ((काष्ठा vbg_ioctl_hdr *)buf)->size_out;
	अगर (वापसed_size > size) अणु
		vbg_debug("%s: too much output data %zu > %zu\n",
			  __func__, वापसed_size, size);
		वापसed_size = size;
	पूर्ण
	अगर (copy_to_user((व्योम *)arg, buf, वापसed_size) != 0)
		ret = -EFAULT;

out:
	अगर (is_vmmdev_req)
		vbg_req_मुक्त(buf, size);
	अन्यथा
		kमुक्त(buf);

	वापस ret;
पूर्ण

/** The file_operations काष्ठाures. */
अटल स्थिर काष्ठा file_operations vbg_misc_device_fops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= vbg_misc_device_खोलो,
	.release		= vbg_misc_device_बंद,
	.unlocked_ioctl		= vbg_misc_device_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= vbg_misc_device_ioctl,
#पूर्ण_अगर
पूर्ण;
अटल स्थिर काष्ठा file_operations vbg_misc_device_user_fops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= vbg_misc_device_user_खोलो,
	.release		= vbg_misc_device_बंद,
	.unlocked_ioctl		= vbg_misc_device_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= vbg_misc_device_ioctl,
#पूर्ण_अगर
पूर्ण;

/**
 * Called when the input device is first खोलोed.
 *
 * Sets up असलolute mouse reporting.
 */
अटल पूर्णांक vbg_input_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा vbg_dev *gdev = input_get_drvdata(input);
	u32 feat = VMMDEV_MOUSE_GUEST_CAN_ABSOLUTE | VMMDEV_MOUSE_NEW_PROTOCOL;

	वापस vbg_core_set_mouse_status(gdev, feat);
पूर्ण

/**
 * Called अगर all खोलो handles to the input device are बंदd.
 *
 * Disables असलolute reporting.
 */
अटल व्योम vbg_input_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा vbg_dev *gdev = input_get_drvdata(input);

	vbg_core_set_mouse_status(gdev, 0);
पूर्ण

/**
 * Creates the kernel input device.
 *
 * Return: 0 on success, negated त्रुटि_सं on failure.
 */
अटल पूर्णांक vbg_create_input_device(काष्ठा vbg_dev *gdev)
अणु
	काष्ठा input_dev *input;

	input = devm_input_allocate_device(gdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	input->id.bustype = BUS_PCI;
	input->id.venकरोr = VBOX_VENDORID;
	input->id.product = VMMDEV_DEVICEID;
	input->खोलो = vbg_input_खोलो;
	input->बंद = vbg_input_बंद;
	input->dev.parent = gdev->dev;
	input->name = "VirtualBox mouse integration";

	input_set_असल_params(input, ABS_X, VMMDEV_MOUSE_RANGE_MIN,
			     VMMDEV_MOUSE_RANGE_MAX, 0, 0);
	input_set_असल_params(input, ABS_Y, VMMDEV_MOUSE_RANGE_MIN,
			     VMMDEV_MOUSE_RANGE_MAX, 0, 0);
	input_set_capability(input, EV_KEY, BTN_MOUSE);
	input_set_drvdata(input, gdev);

	gdev->input = input;

	वापस input_रेजिस्टर_device(gdev->input);
पूर्ण

अटल sमाप_प्रकार host_version_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vbg_dev *gdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", gdev->host_version);
पूर्ण

अटल sमाप_प्रकार host_features_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vbg_dev *gdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%#x\n", gdev->host_features);
पूर्ण

अटल DEVICE_ATTR_RO(host_version);
अटल DEVICE_ATTR_RO(host_features);

/**
 * Does the PCI detection and init of the device.
 *
 * Return: 0 on success, negated त्रुटि_सं on failure.
 */
अटल पूर्णांक vbg_pci_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *dev = &pci->dev;
	resource_माप_प्रकार io, io_len, mmio, mmio_len;
	काष्ठा vmmdev_memory *vmmdev;
	काष्ठा vbg_dev *gdev;
	पूर्णांक ret;

	gdev = devm_kzalloc(dev, माप(*gdev), GFP_KERNEL);
	अगर (!gdev)
		वापस -ENOMEM;

	ret = pci_enable_device(pci);
	अगर (ret != 0) अणु
		vbg_err("vboxguest: Error enabling device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = -ENODEV;

	io = pci_resource_start(pci, 0);
	io_len = pci_resource_len(pci, 0);
	अगर (!io || !io_len) अणु
		vbg_err("vboxguest: Error IO-port resource (0) is missing\n");
		जाओ err_disable_pcidev;
	पूर्ण
	अगर (devm_request_region(dev, io, io_len, DEVICE_NAME) == शून्य) अणु
		vbg_err("vboxguest: Error could not claim IO resource\n");
		ret = -EBUSY;
		जाओ err_disable_pcidev;
	पूर्ण

	mmio = pci_resource_start(pci, 1);
	mmio_len = pci_resource_len(pci, 1);
	अगर (!mmio || !mmio_len) अणु
		vbg_err("vboxguest: Error MMIO resource (1) is missing\n");
		जाओ err_disable_pcidev;
	पूर्ण

	अगर (devm_request_mem_region(dev, mmio, mmio_len, DEVICE_NAME) == शून्य) अणु
		vbg_err("vboxguest: Error could not claim MMIO resource\n");
		ret = -EBUSY;
		जाओ err_disable_pcidev;
	पूर्ण

	vmmdev = devm_ioremap(dev, mmio, mmio_len);
	अगर (!vmmdev) अणु
		vbg_err("vboxguest: Error ioremap failed; MMIO addr=%pap size=%pap\n",
			&mmio, &mmio_len);
		जाओ err_disable_pcidev;
	पूर्ण

	/* Validate MMIO region version and size. */
	अगर (vmmdev->version != VMMDEV_MEMORY_VERSION ||
	    vmmdev->size < 32 || vmmdev->size > mmio_len) अणु
		vbg_err("vboxguest: Bogus VMMDev memory; version=%08x (expected %08x) size=%d (expected <= %d)\n",
			vmmdev->version, VMMDEV_MEMORY_VERSION,
			vmmdev->size, (पूर्णांक)mmio_len);
		जाओ err_disable_pcidev;
	पूर्ण

	gdev->io_port = io;
	gdev->mmio = vmmdev;
	gdev->dev = dev;
	gdev->misc_device.minor = MISC_DYNAMIC_MINOR;
	gdev->misc_device.name = DEVICE_NAME;
	gdev->misc_device.fops = &vbg_misc_device_fops;
	gdev->misc_device_user.minor = MISC_DYNAMIC_MINOR;
	gdev->misc_device_user.name = DEVICE_NAME_USER;
	gdev->misc_device_user.fops = &vbg_misc_device_user_fops;

	ret = vbg_core_init(gdev, VMMDEV_EVENT_MOUSE_POSITION_CHANGED);
	अगर (ret)
		जाओ err_disable_pcidev;

	ret = vbg_create_input_device(gdev);
	अगर (ret) अणु
		vbg_err("vboxguest: Error creating input device: %d\n", ret);
		जाओ err_vbg_core_निकास;
	पूर्ण

	ret = devm_request_irq(dev, pci->irq, vbg_core_isr, IRQF_SHARED,
			       DEVICE_NAME, gdev);
	अगर (ret) अणु
		vbg_err("vboxguest: Error requesting irq: %d\n", ret);
		जाओ err_vbg_core_निकास;
	पूर्ण

	ret = misc_रेजिस्टर(&gdev->misc_device);
	अगर (ret) अणु
		vbg_err("vboxguest: Error misc_register %s failed: %d\n",
			DEVICE_NAME, ret);
		जाओ err_vbg_core_निकास;
	पूर्ण

	ret = misc_रेजिस्टर(&gdev->misc_device_user);
	अगर (ret) अणु
		vbg_err("vboxguest: Error misc_register %s failed: %d\n",
			DEVICE_NAME_USER, ret);
		जाओ err_unरेजिस्टर_misc_device;
	पूर्ण

	mutex_lock(&vbg_gdev_mutex);
	अगर (!vbg_gdev)
		vbg_gdev = gdev;
	अन्यथा
		ret = -EBUSY;
	mutex_unlock(&vbg_gdev_mutex);

	अगर (ret) अणु
		vbg_err("vboxguest: Error more then 1 vbox guest pci device\n");
		जाओ err_unरेजिस्टर_misc_device_user;
	पूर्ण

	pci_set_drvdata(pci, gdev);
	device_create_file(dev, &dev_attr_host_version);
	device_create_file(dev, &dev_attr_host_features);

	vbg_info("vboxguest: misc device minor %d, IRQ %d, I/O port %x, MMIO at %pap (size %pap)\n",
		 gdev->misc_device.minor, pci->irq, gdev->io_port,
		 &mmio, &mmio_len);

	वापस 0;

err_unरेजिस्टर_misc_device_user:
	misc_deरेजिस्टर(&gdev->misc_device_user);
err_unरेजिस्टर_misc_device:
	misc_deरेजिस्टर(&gdev->misc_device);
err_vbg_core_निकास:
	vbg_core_निकास(gdev);
err_disable_pcidev:
	pci_disable_device(pci);

	वापस ret;
पूर्ण

अटल व्योम vbg_pci_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा vbg_dev *gdev = pci_get_drvdata(pci);

	mutex_lock(&vbg_gdev_mutex);
	vbg_gdev = शून्य;
	mutex_unlock(&vbg_gdev_mutex);

	device_हटाओ_file(gdev->dev, &dev_attr_host_features);
	device_हटाओ_file(gdev->dev, &dev_attr_host_version);
	misc_deरेजिस्टर(&gdev->misc_device_user);
	misc_deरेजिस्टर(&gdev->misc_device);
	vbg_core_निकास(gdev);
	pci_disable_device(pci);
पूर्ण

काष्ठा vbg_dev *vbg_get_gdev(व्योम)
अणु
	mutex_lock(&vbg_gdev_mutex);

	/*
	 * Note on success we keep the mutex locked until vbg_put_gdev(),
	 * this stops vbg_pci_हटाओ from removing the device from underneath
	 * vboxsf. vboxsf will only hold a reference क्रम a लघु जबतक.
	 */
	अगर (vbg_gdev)
		वापस vbg_gdev;

	mutex_unlock(&vbg_gdev_mutex);
	वापस ERR_PTR(-ENODEV);
पूर्ण
EXPORT_SYMBOL(vbg_get_gdev);

व्योम vbg_put_gdev(काष्ठा vbg_dev *gdev)
अणु
	WARN_ON(gdev != vbg_gdev);
	mutex_unlock(&vbg_gdev_mutex);
पूर्ण
EXPORT_SYMBOL(vbg_put_gdev);

/**
 * Callback क्रम mouse events.
 *
 * This is called at the end of the ISR, after leaving the event spinlock, अगर
 * VMMDEV_EVENT_MOUSE_POSITION_CHANGED was उठाओd by the host.
 *
 * @gdev:		The device extension.
 */
व्योम vbg_linux_mouse_event(काष्ठा vbg_dev *gdev)
अणु
	पूर्णांक rc;

	/* Report events to the kernel input device */
	gdev->mouse_status_req->mouse_features = 0;
	gdev->mouse_status_req->poपूर्णांकer_pos_x = 0;
	gdev->mouse_status_req->poपूर्णांकer_pos_y = 0;
	rc = vbg_req_perक्रमm(gdev, gdev->mouse_status_req);
	अगर (rc >= 0) अणु
		input_report_असल(gdev->input, ABS_X,
				 gdev->mouse_status_req->poपूर्णांकer_pos_x);
		input_report_असल(gdev->input, ABS_Y,
				 gdev->mouse_status_req->poपूर्णांकer_pos_y);
		input_sync(gdev->input);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_device_id vbg_pci_ids[] = अणु
	अणु .venकरोr = VBOX_VENDORID, .device = VMMDEV_DEVICEID पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci,  vbg_pci_ids);

अटल काष्ठा pci_driver vbg_pci_driver = अणु
	.name		= DEVICE_NAME,
	.id_table	= vbg_pci_ids,
	.probe		= vbg_pci_probe,
	.हटाओ		= vbg_pci_हटाओ,
पूर्ण;

module_pci_driver(vbg_pci_driver);

MODULE_AUTHOR("Oracle Corporation");
MODULE_DESCRIPTION("Oracle VM VirtualBox Guest Additions for Linux Module");
MODULE_LICENSE("GPL");
