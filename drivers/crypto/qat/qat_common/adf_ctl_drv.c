<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/bitops.h>
#समावेश <linux/pci.h>
#समावेश <linux/cdev.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/crypto.h>

#समावेश "adf_accel_devices.h"
#समावेश "adf_common_drv.h"
#समावेश "adf_cfg.h"
#समावेश "adf_cfg_common.h"
#समावेश "adf_cfg_user.h"

#घोषणा DEVICE_NAME "qat_adf_ctl"

अटल DEFINE_MUTEX(adf_ctl_lock);
अटल दीर्घ adf_ctl_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

अटल स्थिर काष्ठा file_operations adf_ctl_ops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = adf_ctl_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;

काष्ठा adf_ctl_drv_info अणु
	अचिन्हित पूर्णांक major;
	काष्ठा cdev drv_cdev;
	काष्ठा class *drv_class;
पूर्ण;

अटल काष्ठा adf_ctl_drv_info adf_ctl_drv;

अटल व्योम adf_chr_drv_destroy(व्योम)
अणु
	device_destroy(adf_ctl_drv.drv_class, MKDEV(adf_ctl_drv.major, 0));
	cdev_del(&adf_ctl_drv.drv_cdev);
	class_destroy(adf_ctl_drv.drv_class);
	unरेजिस्टर_chrdev_region(MKDEV(adf_ctl_drv.major, 0), 1);
पूर्ण

अटल पूर्णांक adf_chr_drv_create(व्योम)
अणु
	dev_t dev_id;
	काष्ठा device *drv_device;

	अगर (alloc_chrdev_region(&dev_id, 0, 1, DEVICE_NAME)) अणु
		pr_err("QAT: unable to allocate chrdev region\n");
		वापस -EFAULT;
	पूर्ण

	adf_ctl_drv.drv_class = class_create(THIS_MODULE, DEVICE_NAME);
	अगर (IS_ERR(adf_ctl_drv.drv_class)) अणु
		pr_err("QAT: class_create failed for adf_ctl\n");
		जाओ err_chrdev_unreg;
	पूर्ण
	adf_ctl_drv.major = MAJOR(dev_id);
	cdev_init(&adf_ctl_drv.drv_cdev, &adf_ctl_ops);
	अगर (cdev_add(&adf_ctl_drv.drv_cdev, dev_id, 1)) अणु
		pr_err("QAT: cdev add failed\n");
		जाओ err_class_destr;
	पूर्ण

	drv_device = device_create(adf_ctl_drv.drv_class, शून्य,
				   MKDEV(adf_ctl_drv.major, 0),
				   शून्य, DEVICE_NAME);
	अगर (IS_ERR(drv_device)) अणु
		pr_err("QAT: failed to create device\n");
		जाओ err_cdev_del;
	पूर्ण
	वापस 0;
err_cdev_del:
	cdev_del(&adf_ctl_drv.drv_cdev);
err_class_destr:
	class_destroy(adf_ctl_drv.drv_class);
err_chrdev_unreg:
	unरेजिस्टर_chrdev_region(dev_id, 1);
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक adf_ctl_alloc_resources(काष्ठा adf_user_cfg_ctl_data **ctl_data,
				   अचिन्हित दीर्घ arg)
अणु
	काष्ठा adf_user_cfg_ctl_data *cfg_data;

	cfg_data = kzalloc(माप(*cfg_data), GFP_KERNEL);
	अगर (!cfg_data)
		वापस -ENOMEM;

	/* Initialize device id to NO DEVICE as 0 is a valid device id */
	cfg_data->device_id = ADF_CFG_NO_DEVICE;

	अगर (copy_from_user(cfg_data, (व्योम __user *)arg, माप(*cfg_data))) अणु
		pr_err("QAT: failed to copy from user cfg_data.\n");
		kमुक्त(cfg_data);
		वापस -EIO;
	पूर्ण

	*ctl_data = cfg_data;
	वापस 0;
पूर्ण

अटल पूर्णांक adf_add_key_value_data(काष्ठा adf_accel_dev *accel_dev,
				  स्थिर अक्षर *section,
				  स्थिर काष्ठा adf_user_cfg_key_val *key_val)
अणु
	अगर (key_val->type == ADF_HEX) अणु
		दीर्घ *ptr = (दीर्घ *)key_val->val;
		दीर्घ val = *ptr;

		अगर (adf_cfg_add_key_value_param(accel_dev, section,
						key_val->key, (व्योम *)val,
						key_val->type)) अणु
			dev_err(&GET_DEV(accel_dev),
				"failed to add hex keyvalue.\n");
			वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (adf_cfg_add_key_value_param(accel_dev, section,
						key_val->key, key_val->val,
						key_val->type)) अणु
			dev_err(&GET_DEV(accel_dev),
				"failed to add keyvalue.\n");
			वापस -EFAULT;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adf_copy_key_value_data(काष्ठा adf_accel_dev *accel_dev,
				   काष्ठा adf_user_cfg_ctl_data *ctl_data)
अणु
	काष्ठा adf_user_cfg_key_val key_val;
	काष्ठा adf_user_cfg_key_val *params_head;
	काष्ठा adf_user_cfg_section section, *section_head;

	section_head = ctl_data->config_section;

	जबतक (section_head) अणु
		अगर (copy_from_user(&section, (व्योम __user *)section_head,
				   माप(*section_head))) अणु
			dev_err(&GET_DEV(accel_dev),
				"failed to copy section info\n");
			जाओ out_err;
		पूर्ण

		अगर (adf_cfg_section_add(accel_dev, section.name)) अणु
			dev_err(&GET_DEV(accel_dev),
				"failed to add section.\n");
			जाओ out_err;
		पूर्ण

		params_head = section.params;

		जबतक (params_head) अणु
			अगर (copy_from_user(&key_val, (व्योम __user *)params_head,
					   माप(key_val))) अणु
				dev_err(&GET_DEV(accel_dev),
					"Failed to copy keyvalue.\n");
				जाओ out_err;
			पूर्ण
			अगर (adf_add_key_value_data(accel_dev, section.name,
						   &key_val)) अणु
				जाओ out_err;
			पूर्ण
			params_head = key_val.next;
		पूर्ण
		section_head = section.next;
	पूर्ण
	वापस 0;
out_err:
	adf_cfg_del_all(accel_dev);
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक adf_ctl_ioctl_dev_config(काष्ठा file *fp, अचिन्हित पूर्णांक cmd,
				    अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;
	काष्ठा adf_user_cfg_ctl_data *ctl_data;
	काष्ठा adf_accel_dev *accel_dev;

	ret = adf_ctl_alloc_resources(&ctl_data, arg);
	अगर (ret)
		वापस ret;

	accel_dev = adf_devmgr_get_dev_by_id(ctl_data->device_id);
	अगर (!accel_dev) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (adf_dev_started(accel_dev)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (adf_copy_key_value_data(accel_dev, ctl_data)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	set_bit(ADF_STATUS_CONFIGURED, &accel_dev->status);
out:
	kमुक्त(ctl_data);
	वापस ret;
पूर्ण

अटल पूर्णांक adf_ctl_is_device_in_use(पूर्णांक id)
अणु
	काष्ठा adf_accel_dev *dev;

	list_क्रम_each_entry(dev, adf_devmgr_get_head(), list) अणु
		अगर (id == dev->accel_id || id == ADF_CFG_ALL_DEVICES) अणु
			अगर (adf_devmgr_in_reset(dev) || adf_dev_in_use(dev)) अणु
				dev_info(&GET_DEV(dev),
					 "device qat_dev%d is busy\n",
					 dev->accel_id);
				वापस -EBUSY;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम adf_ctl_stop_devices(u32 id)
अणु
	काष्ठा adf_accel_dev *accel_dev;

	list_क्रम_each_entry(accel_dev, adf_devmgr_get_head(), list) अणु
		अगर (id == accel_dev->accel_id || id == ADF_CFG_ALL_DEVICES) अणु
			अगर (!adf_dev_started(accel_dev))
				जारी;

			/* First stop all VFs */
			अगर (!accel_dev->is_vf)
				जारी;

			adf_dev_stop(accel_dev);
			adf_dev_shutकरोwn(accel_dev);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(accel_dev, adf_devmgr_get_head(), list) अणु
		अगर (id == accel_dev->accel_id || id == ADF_CFG_ALL_DEVICES) अणु
			अगर (!adf_dev_started(accel_dev))
				जारी;

			adf_dev_stop(accel_dev);
			adf_dev_shutकरोwn(accel_dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक adf_ctl_ioctl_dev_stop(काष्ठा file *fp, अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;
	काष्ठा adf_user_cfg_ctl_data *ctl_data;

	ret = adf_ctl_alloc_resources(&ctl_data, arg);
	अगर (ret)
		वापस ret;

	अगर (adf_devmgr_verअगरy_id(ctl_data->device_id)) अणु
		pr_err("QAT: Device %d not found\n", ctl_data->device_id);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ret = adf_ctl_is_device_in_use(ctl_data->device_id);
	अगर (ret)
		जाओ out;

	अगर (ctl_data->device_id == ADF_CFG_ALL_DEVICES)
		pr_info("QAT: Stopping all acceleration devices.\n");
	अन्यथा
		pr_info("QAT: Stopping acceleration device qat_dev%d.\n",
			ctl_data->device_id);

	adf_ctl_stop_devices(ctl_data->device_id);

out:
	kमुक्त(ctl_data);
	वापस ret;
पूर्ण

अटल पूर्णांक adf_ctl_ioctl_dev_start(काष्ठा file *fp, अचिन्हित पूर्णांक cmd,
				   अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;
	काष्ठा adf_user_cfg_ctl_data *ctl_data;
	काष्ठा adf_accel_dev *accel_dev;

	ret = adf_ctl_alloc_resources(&ctl_data, arg);
	अगर (ret)
		वापस ret;

	ret = -ENODEV;
	accel_dev = adf_devmgr_get_dev_by_id(ctl_data->device_id);
	अगर (!accel_dev)
		जाओ out;

	अगर (!adf_dev_started(accel_dev)) अणु
		dev_info(&GET_DEV(accel_dev),
			 "Starting acceleration device qat_dev%d.\n",
			 ctl_data->device_id);
		ret = adf_dev_init(accel_dev);
		अगर (!ret)
			ret = adf_dev_start(accel_dev);
	पूर्ण अन्यथा अणु
		dev_info(&GET_DEV(accel_dev),
			 "Acceleration device qat_dev%d already started.\n",
			 ctl_data->device_id);
	पूर्ण
	अगर (ret) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to start qat_dev%d\n",
			ctl_data->device_id);
		adf_dev_stop(accel_dev);
		adf_dev_shutकरोwn(accel_dev);
	पूर्ण
out:
	kमुक्त(ctl_data);
	वापस ret;
पूर्ण

अटल पूर्णांक adf_ctl_ioctl_get_num_devices(काष्ठा file *fp, अचिन्हित पूर्णांक cmd,
					 अचिन्हित दीर्घ arg)
अणु
	u32 num_devices = 0;

	adf_devmgr_get_num_dev(&num_devices);
	अगर (copy_to_user((व्योम __user *)arg, &num_devices, माप(num_devices)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक adf_ctl_ioctl_get_status(काष्ठा file *fp, अचिन्हित पूर्णांक cmd,
				    अचिन्हित दीर्घ arg)
अणु
	काष्ठा adf_hw_device_data *hw_data;
	काष्ठा adf_dev_status_info dev_info;
	काष्ठा adf_accel_dev *accel_dev;

	अगर (copy_from_user(&dev_info, (व्योम __user *)arg,
			   माप(काष्ठा adf_dev_status_info))) अणु
		pr_err("QAT: failed to copy from user.\n");
		वापस -EFAULT;
	पूर्ण

	accel_dev = adf_devmgr_get_dev_by_id(dev_info.accel_id);
	अगर (!accel_dev)
		वापस -ENODEV;

	hw_data = accel_dev->hw_device;
	dev_info.state = adf_dev_started(accel_dev) ? DEV_UP : DEV_DOWN;
	dev_info.num_ae = hw_data->get_num_aes(hw_data);
	dev_info.num_accel = hw_data->get_num_accels(hw_data);
	dev_info.num_logical_accel = hw_data->num_logical_accel;
	dev_info.banks_per_accel = hw_data->num_banks
					/ hw_data->num_logical_accel;
	strlcpy(dev_info.name, hw_data->dev_class->name, माप(dev_info.name));
	dev_info.instance_id = hw_data->instance_id;
	dev_info.type = hw_data->dev_class->type;
	dev_info.bus = accel_to_pci_dev(accel_dev)->bus->number;
	dev_info.dev = PCI_SLOT(accel_to_pci_dev(accel_dev)->devfn);
	dev_info.fun = PCI_FUNC(accel_to_pci_dev(accel_dev)->devfn);

	अगर (copy_to_user((व्योम __user *)arg, &dev_info,
			 माप(काष्ठा adf_dev_status_info))) अणु
		dev_err(&GET_DEV(accel_dev), "failed to copy status.\n");
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ adf_ctl_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&adf_ctl_lock))
		वापस -EFAULT;

	चयन (cmd) अणु
	हाल IOCTL_CONFIG_SYS_RESOURCE_PARAMETERS:
		ret = adf_ctl_ioctl_dev_config(fp, cmd, arg);
		अवरोध;

	हाल IOCTL_STOP_ACCEL_DEV:
		ret = adf_ctl_ioctl_dev_stop(fp, cmd, arg);
		अवरोध;

	हाल IOCTL_START_ACCEL_DEV:
		ret = adf_ctl_ioctl_dev_start(fp, cmd, arg);
		अवरोध;

	हाल IOCTL_GET_NUM_DEVICES:
		ret = adf_ctl_ioctl_get_num_devices(fp, cmd, arg);
		अवरोध;

	हाल IOCTL_STATUS_ACCEL_DEV:
		ret = adf_ctl_ioctl_get_status(fp, cmd, arg);
		अवरोध;
	शेष:
		pr_err("QAT: Invalid ioctl\n");
		ret = -EFAULT;
		अवरोध;
	पूर्ण
	mutex_unlock(&adf_ctl_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक __init adf_रेजिस्टर_ctl_device_driver(व्योम)
अणु
	अगर (adf_chr_drv_create())
		जाओ err_chr_dev;

	अगर (adf_init_aer())
		जाओ err_aer;

	अगर (adf_init_pf_wq())
		जाओ err_pf_wq;

	अगर (adf_init_vf_wq())
		जाओ err_vf_wq;

	अगर (qat_crypto_रेजिस्टर())
		जाओ err_crypto_रेजिस्टर;

	वापस 0;

err_crypto_रेजिस्टर:
	adf_निकास_vf_wq();
err_vf_wq:
	adf_निकास_pf_wq();
err_pf_wq:
	adf_निकास_aer();
err_aer:
	adf_chr_drv_destroy();
err_chr_dev:
	mutex_destroy(&adf_ctl_lock);
	वापस -EFAULT;
पूर्ण

अटल व्योम __निकास adf_unरेजिस्टर_ctl_device_driver(व्योम)
अणु
	adf_chr_drv_destroy();
	adf_निकास_aer();
	adf_निकास_vf_wq();
	adf_निकास_pf_wq();
	qat_crypto_unरेजिस्टर();
	adf_clean_vf_map(false);
	mutex_destroy(&adf_ctl_lock);
पूर्ण

module_init(adf_रेजिस्टर_ctl_device_driver);
module_निकास(adf_unरेजिस्टर_ctl_device_driver);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Intel");
MODULE_DESCRIPTION("Intel(R) QuickAssist Technology");
MODULE_ALIAS_CRYPTO("intel_qat");
MODULE_VERSION(ADF_DRV_VERSION);
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
