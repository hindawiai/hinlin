<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/compat.h>
#समावेश <uapi/linux/kfd_ioctl.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/dma-buf.h>
#समावेश <यंत्र/processor.h>
#समावेश "kfd_priv.h"
#समावेश "kfd_device_queue_manager.h"
#समावेश "kfd_dbgmgr.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "kfd_smi_events.h"

अटल दीर्घ kfd_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
अटल पूर्णांक kfd_खोलो(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक kfd_release(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक kfd_mmap(काष्ठा file *, काष्ठा vm_area_काष्ठा *);

अटल स्थिर अक्षर kfd_dev_name[] = "kfd";

अटल स्थिर काष्ठा file_operations kfd_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = kfd_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.खोलो = kfd_खोलो,
	.release = kfd_release,
	.mmap = kfd_mmap,
पूर्ण;

अटल पूर्णांक kfd_अक्षर_dev_major = -1;
अटल काष्ठा class *kfd_class;
काष्ठा device *kfd_device;

पूर्णांक kfd_अक्षरdev_init(व्योम)
अणु
	पूर्णांक err = 0;

	kfd_अक्षर_dev_major = रेजिस्टर_chrdev(0, kfd_dev_name, &kfd_fops);
	err = kfd_अक्षर_dev_major;
	अगर (err < 0)
		जाओ err_रेजिस्टर_chrdev;

	kfd_class = class_create(THIS_MODULE, kfd_dev_name);
	err = PTR_ERR(kfd_class);
	अगर (IS_ERR(kfd_class))
		जाओ err_class_create;

	kfd_device = device_create(kfd_class, शून्य,
					MKDEV(kfd_अक्षर_dev_major, 0),
					शून्य, kfd_dev_name);
	err = PTR_ERR(kfd_device);
	अगर (IS_ERR(kfd_device))
		जाओ err_device_create;

	वापस 0;

err_device_create:
	class_destroy(kfd_class);
err_class_create:
	unरेजिस्टर_chrdev(kfd_अक्षर_dev_major, kfd_dev_name);
err_रेजिस्टर_chrdev:
	वापस err;
पूर्ण

व्योम kfd_अक्षरdev_निकास(व्योम)
अणु
	device_destroy(kfd_class, MKDEV(kfd_अक्षर_dev_major, 0));
	class_destroy(kfd_class);
	unरेजिस्टर_chrdev(kfd_अक्षर_dev_major, kfd_dev_name);
	kfd_device = शून्य;
पूर्ण

काष्ठा device *kfd_अक्षरdev(व्योम)
अणु
	वापस kfd_device;
पूर्ण


अटल पूर्णांक kfd_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा kfd_process *process;
	bool is_32bit_user_mode;

	अगर (iminor(inode) != 0)
		वापस -ENODEV;

	is_32bit_user_mode = in_compat_syscall();

	अगर (is_32bit_user_mode) अणु
		dev_warn(kfd_device,
			"Process %d (32-bit) failed to open /dev/kfd\n"
			"32-bit processes are not supported by amdkfd\n",
			current->pid);
		वापस -EPERM;
	पूर्ण

	process = kfd_create_process(filep);
	अगर (IS_ERR(process))
		वापस PTR_ERR(process);

	अगर (kfd_is_locked()) अणु
		dev_dbg(kfd_device, "kfd is locked!\n"
				"process %d unreferenced", process->pasid);
		kfd_unref_process(process);
		वापस -EAGAIN;
	पूर्ण

	/* filep now owns the reference वापसed by kfd_create_process */
	filep->निजी_data = process;

	dev_dbg(kfd_device, "process %d opened, compat mode (32 bit) - %d\n",
		process->pasid, process->is_32bit_user_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक kfd_release(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा kfd_process *process = filep->निजी_data;

	अगर (process)
		kfd_unref_process(process);

	वापस 0;
पूर्ण

अटल पूर्णांक kfd_ioctl_get_version(काष्ठा file *filep, काष्ठा kfd_process *p,
					व्योम *data)
अणु
	काष्ठा kfd_ioctl_get_version_args *args = data;

	args->major_version = KFD_IOCTL_MAJOR_VERSION;
	args->minor_version = KFD_IOCTL_MINOR_VERSION;

	वापस 0;
पूर्ण

अटल पूर्णांक set_queue_properties_from_user(काष्ठा queue_properties *q_properties,
				काष्ठा kfd_ioctl_create_queue_args *args)
अणु
	अगर (args->queue_percentage > KFD_MAX_QUEUE_PERCENTAGE) अणु
		pr_err("Queue percentage must be between 0 to KFD_MAX_QUEUE_PERCENTAGE\n");
		वापस -EINVAL;
	पूर्ण

	अगर (args->queue_priority > KFD_MAX_QUEUE_PRIORITY) अणु
		pr_err("Queue priority must be between 0 to KFD_MAX_QUEUE_PRIORITY\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((args->ring_base_address) &&
		(!access_ok((स्थिर व्योम __user *) args->ring_base_address,
			माप(uपूर्णांक64_t)))) अणु
		pr_err("Can't access ring base address\n");
		वापस -EFAULT;
	पूर्ण

	अगर (!is_घातer_of_2(args->ring_size) && (args->ring_size != 0)) अणु
		pr_err("Ring size must be a power of 2 or 0\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!access_ok((स्थिर व्योम __user *) args->पढ़ो_poपूर्णांकer_address,
			माप(uपूर्णांक32_t))) अणु
		pr_err("Can't access read pointer\n");
		वापस -EFAULT;
	पूर्ण

	अगर (!access_ok((स्थिर व्योम __user *) args->ग_लिखो_poपूर्णांकer_address,
			माप(uपूर्णांक32_t))) अणु
		pr_err("Can't access write pointer\n");
		वापस -EFAULT;
	पूर्ण

	अगर (args->eop_buffer_address &&
		!access_ok((स्थिर व्योम __user *) args->eop_buffer_address,
			माप(uपूर्णांक32_t))) अणु
		pr_debug("Can't access eop buffer");
		वापस -EFAULT;
	पूर्ण

	अगर (args->ctx_save_restore_address &&
		!access_ok((स्थिर व्योम __user *) args->ctx_save_restore_address,
			माप(uपूर्णांक32_t))) अणु
		pr_debug("Can't access ctx save restore buffer");
		वापस -EFAULT;
	पूर्ण

	q_properties->is_पूर्णांकerop = false;
	q_properties->is_gws = false;
	q_properties->queue_percent = args->queue_percentage;
	q_properties->priority = args->queue_priority;
	q_properties->queue_address = args->ring_base_address;
	q_properties->queue_size = args->ring_size;
	q_properties->पढ़ो_ptr = (uपूर्णांक32_t *) args->पढ़ो_poपूर्णांकer_address;
	q_properties->ग_लिखो_ptr = (uपूर्णांक32_t *) args->ग_लिखो_poपूर्णांकer_address;
	q_properties->eop_ring_buffer_address = args->eop_buffer_address;
	q_properties->eop_ring_buffer_size = args->eop_buffer_size;
	q_properties->ctx_save_restore_area_address =
			args->ctx_save_restore_address;
	q_properties->ctx_save_restore_area_size = args->ctx_save_restore_size;
	q_properties->ctl_stack_size = args->ctl_stack_size;
	अगर (args->queue_type == KFD_IOC_QUEUE_TYPE_COMPUTE ||
		args->queue_type == KFD_IOC_QUEUE_TYPE_COMPUTE_AQL)
		q_properties->type = KFD_QUEUE_TYPE_COMPUTE;
	अन्यथा अगर (args->queue_type == KFD_IOC_QUEUE_TYPE_SDMA)
		q_properties->type = KFD_QUEUE_TYPE_SDMA;
	अन्यथा अगर (args->queue_type == KFD_IOC_QUEUE_TYPE_SDMA_XGMI)
		q_properties->type = KFD_QUEUE_TYPE_SDMA_XGMI;
	अन्यथा
		वापस -ENOTSUPP;

	अगर (args->queue_type == KFD_IOC_QUEUE_TYPE_COMPUTE_AQL)
		q_properties->क्रमmat = KFD_QUEUE_FORMAT_AQL;
	अन्यथा
		q_properties->क्रमmat = KFD_QUEUE_FORMAT_PM4;

	pr_debug("Queue Percentage: %d, %d\n",
			q_properties->queue_percent, args->queue_percentage);

	pr_debug("Queue Priority: %d, %d\n",
			q_properties->priority, args->queue_priority);

	pr_debug("Queue Address: 0x%llX, 0x%llX\n",
			q_properties->queue_address, args->ring_base_address);

	pr_debug("Queue Size: 0x%llX, %u\n",
			q_properties->queue_size, args->ring_size);

	pr_debug("Queue r/w Pointers: %px, %px\n",
			q_properties->पढ़ो_ptr,
			q_properties->ग_लिखो_ptr);

	pr_debug("Queue Format: %d\n", q_properties->क्रमmat);

	pr_debug("Queue EOP: 0x%llX\n", q_properties->eop_ring_buffer_address);

	pr_debug("Queue CTX save area: 0x%llX\n",
			q_properties->ctx_save_restore_area_address);

	वापस 0;
पूर्ण

अटल पूर्णांक kfd_ioctl_create_queue(काष्ठा file *filep, काष्ठा kfd_process *p,
					व्योम *data)
अणु
	काष्ठा kfd_ioctl_create_queue_args *args = data;
	काष्ठा kfd_dev *dev;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक queue_id;
	काष्ठा kfd_process_device *pdd;
	काष्ठा queue_properties q_properties;
	uपूर्णांक32_t करोorbell_offset_in_process = 0;

	स_रखो(&q_properties, 0, माप(काष्ठा queue_properties));

	pr_debug("Creating queue ioctl\n");

	err = set_queue_properties_from_user(&q_properties, args);
	अगर (err)
		वापस err;

	pr_debug("Looking for gpu id 0x%x\n", args->gpu_id);
	dev = kfd_device_by_id(args->gpu_id);
	अगर (!dev) अणु
		pr_debug("Could not find gpu id 0x%x\n", args->gpu_id);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&p->mutex);

	pdd = kfd_bind_process_to_device(dev, p);
	अगर (IS_ERR(pdd)) अणु
		err = -ESRCH;
		जाओ err_bind_process;
	पूर्ण

	pr_debug("Creating queue for PASID 0x%x on gpu 0x%x\n",
			p->pasid,
			dev->id);

	err = pqm_create_queue(&p->pqm, dev, filep, &q_properties, &queue_id,
			&करोorbell_offset_in_process);
	अगर (err != 0)
		जाओ err_create_queue;

	args->queue_id = queue_id;


	/* Return gpu_id as करोorbell offset क्रम mmap usage */
	args->करोorbell_offset = KFD_MMAP_TYPE_DOORBELL;
	args->करोorbell_offset |= KFD_MMAP_GPU_ID(args->gpu_id);
	अगर (KFD_IS_SOC15(dev->device_info->asic_family))
		/* On SOC15 ASICs, include the करोorbell offset within the
		 * process करोorbell frame, which is 2 pages.
		 */
		args->करोorbell_offset |= करोorbell_offset_in_process;

	mutex_unlock(&p->mutex);

	pr_debug("Queue id %d was created successfully\n", args->queue_id);

	pr_debug("Ring buffer address == 0x%016llX\n",
			args->ring_base_address);

	pr_debug("Read ptr address    == 0x%016llX\n",
			args->पढ़ो_poपूर्णांकer_address);

	pr_debug("Write ptr address   == 0x%016llX\n",
			args->ग_लिखो_poपूर्णांकer_address);

	वापस 0;

err_create_queue:
err_bind_process:
	mutex_unlock(&p->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक kfd_ioctl_destroy_queue(काष्ठा file *filp, काष्ठा kfd_process *p,
					व्योम *data)
अणु
	पूर्णांक retval;
	काष्ठा kfd_ioctl_destroy_queue_args *args = data;

	pr_debug("Destroying queue id %d for pasid 0x%x\n",
				args->queue_id,
				p->pasid);

	mutex_lock(&p->mutex);

	retval = pqm_destroy_queue(&p->pqm, args->queue_id);

	mutex_unlock(&p->mutex);
	वापस retval;
पूर्ण

अटल पूर्णांक kfd_ioctl_update_queue(काष्ठा file *filp, काष्ठा kfd_process *p,
					व्योम *data)
अणु
	पूर्णांक retval;
	काष्ठा kfd_ioctl_update_queue_args *args = data;
	काष्ठा queue_properties properties;

	अगर (args->queue_percentage > KFD_MAX_QUEUE_PERCENTAGE) अणु
		pr_err("Queue percentage must be between 0 to KFD_MAX_QUEUE_PERCENTAGE\n");
		वापस -EINVAL;
	पूर्ण

	अगर (args->queue_priority > KFD_MAX_QUEUE_PRIORITY) अणु
		pr_err("Queue priority must be between 0 to KFD_MAX_QUEUE_PRIORITY\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((args->ring_base_address) &&
		(!access_ok((स्थिर व्योम __user *) args->ring_base_address,
			माप(uपूर्णांक64_t)))) अणु
		pr_err("Can't access ring base address\n");
		वापस -EFAULT;
	पूर्ण

	अगर (!is_घातer_of_2(args->ring_size) && (args->ring_size != 0)) अणु
		pr_err("Ring size must be a power of 2 or 0\n");
		वापस -EINVAL;
	पूर्ण

	properties.queue_address = args->ring_base_address;
	properties.queue_size = args->ring_size;
	properties.queue_percent = args->queue_percentage;
	properties.priority = args->queue_priority;

	pr_debug("Updating queue id %d for pasid 0x%x\n",
			args->queue_id, p->pasid);

	mutex_lock(&p->mutex);

	retval = pqm_update_queue(&p->pqm, args->queue_id, &properties);

	mutex_unlock(&p->mutex);

	वापस retval;
पूर्ण

अटल पूर्णांक kfd_ioctl_set_cu_mask(काष्ठा file *filp, काष्ठा kfd_process *p,
					व्योम *data)
अणु
	पूर्णांक retval;
	स्थिर पूर्णांक max_num_cus = 1024;
	काष्ठा kfd_ioctl_set_cu_mask_args *args = data;
	काष्ठा queue_properties properties;
	uपूर्णांक32_t __user *cu_mask_ptr = (uपूर्णांक32_t __user *)args->cu_mask_ptr;
	माप_प्रकार cu_mask_size = माप(uपूर्णांक32_t) * (args->num_cu_mask / 32);

	अगर ((args->num_cu_mask % 32) != 0) अणु
		pr_debug("num_cu_mask 0x%x must be a multiple of 32",
				args->num_cu_mask);
		वापस -EINVAL;
	पूर्ण

	properties.cu_mask_count = args->num_cu_mask;
	अगर (properties.cu_mask_count == 0) अणु
		pr_debug("CU mask cannot be 0");
		वापस -EINVAL;
	पूर्ण

	/* To prevent an unreasonably large CU mask size, set an arbitrary
	 * limit of max_num_cus bits.  We can then just drop any CU mask bits
	 * past max_num_cus bits and just use the first max_num_cus bits.
	 */
	अगर (properties.cu_mask_count > max_num_cus) अणु
		pr_debug("CU mask cannot be greater than 1024 bits");
		properties.cu_mask_count = max_num_cus;
		cu_mask_size = माप(uपूर्णांक32_t) * (max_num_cus/32);
	पूर्ण

	properties.cu_mask = kzalloc(cu_mask_size, GFP_KERNEL);
	अगर (!properties.cu_mask)
		वापस -ENOMEM;

	retval = copy_from_user(properties.cu_mask, cu_mask_ptr, cu_mask_size);
	अगर (retval) अणु
		pr_debug("Could not copy CU mask from userspace");
		kमुक्त(properties.cu_mask);
		वापस -EFAULT;
	पूर्ण

	mutex_lock(&p->mutex);

	retval = pqm_set_cu_mask(&p->pqm, args->queue_id, &properties);

	mutex_unlock(&p->mutex);

	अगर (retval)
		kमुक्त(properties.cu_mask);

	वापस retval;
पूर्ण

अटल पूर्णांक kfd_ioctl_get_queue_wave_state(काष्ठा file *filep,
					  काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_get_queue_wave_state_args *args = data;
	पूर्णांक r;

	mutex_lock(&p->mutex);

	r = pqm_get_wave_state(&p->pqm, args->queue_id,
			       (व्योम __user *)args->ctl_stack_address,
			       &args->ctl_stack_used_size,
			       &args->save_area_used_size);

	mutex_unlock(&p->mutex);

	वापस r;
पूर्ण

अटल पूर्णांक kfd_ioctl_set_memory_policy(काष्ठा file *filep,
					काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_set_memory_policy_args *args = data;
	काष्ठा kfd_dev *dev;
	पूर्णांक err = 0;
	काष्ठा kfd_process_device *pdd;
	क्रमागत cache_policy शेष_policy, alternate_policy;

	अगर (args->शेष_policy != KFD_IOC_CACHE_POLICY_COHERENT
	    && args->शेष_policy != KFD_IOC_CACHE_POLICY_NONCOHERENT) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (args->alternate_policy != KFD_IOC_CACHE_POLICY_COHERENT
	    && args->alternate_policy != KFD_IOC_CACHE_POLICY_NONCOHERENT) अणु
		वापस -EINVAL;
	पूर्ण

	dev = kfd_device_by_id(args->gpu_id);
	अगर (!dev)
		वापस -EINVAL;

	mutex_lock(&p->mutex);

	pdd = kfd_bind_process_to_device(dev, p);
	अगर (IS_ERR(pdd)) अणु
		err = -ESRCH;
		जाओ out;
	पूर्ण

	शेष_policy = (args->शेष_policy == KFD_IOC_CACHE_POLICY_COHERENT)
			 ? cache_policy_coherent : cache_policy_noncoherent;

	alternate_policy =
		(args->alternate_policy == KFD_IOC_CACHE_POLICY_COHERENT)
		   ? cache_policy_coherent : cache_policy_noncoherent;

	अगर (!dev->dqm->ops.set_cache_memory_policy(dev->dqm,
				&pdd->qpd,
				शेष_policy,
				alternate_policy,
				(व्योम __user *)args->alternate_aperture_base,
				args->alternate_aperture_size))
		err = -EINVAL;

out:
	mutex_unlock(&p->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक kfd_ioctl_set_trap_handler(काष्ठा file *filep,
					काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_set_trap_handler_args *args = data;
	काष्ठा kfd_dev *dev;
	पूर्णांक err = 0;
	काष्ठा kfd_process_device *pdd;

	dev = kfd_device_by_id(args->gpu_id);
	अगर (!dev)
		वापस -EINVAL;

	mutex_lock(&p->mutex);

	pdd = kfd_bind_process_to_device(dev, p);
	अगर (IS_ERR(pdd)) अणु
		err = -ESRCH;
		जाओ out;
	पूर्ण

	kfd_process_set_trap_handler(&pdd->qpd, args->tba_addr, args->पंचांगa_addr);

out:
	mutex_unlock(&p->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक kfd_ioctl_dbg_रेजिस्टर(काष्ठा file *filep,
				काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_dbg_रेजिस्टर_args *args = data;
	काष्ठा kfd_dev *dev;
	काष्ठा kfd_dbgmgr *dbgmgr_ptr;
	काष्ठा kfd_process_device *pdd;
	bool create_ok;
	दीर्घ status = 0;

	dev = kfd_device_by_id(args->gpu_id);
	अगर (!dev)
		वापस -EINVAL;

	अगर (dev->device_info->asic_family == CHIP_CARRIZO) अणु
		pr_debug("kfd_ioctl_dbg_register not supported on CZ\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&p->mutex);
	mutex_lock(kfd_get_dbgmgr_mutex());

	/*
	 * make sure that we have pdd, अगर this the first queue created क्रम
	 * this process
	 */
	pdd = kfd_bind_process_to_device(dev, p);
	अगर (IS_ERR(pdd)) अणु
		status = PTR_ERR(pdd);
		जाओ out;
	पूर्ण

	अगर (!dev->dbgmgr) अणु
		/* In हाल of a legal call, we have no dbgmgr yet */
		create_ok = kfd_dbgmgr_create(&dbgmgr_ptr, dev);
		अगर (create_ok) अणु
			status = kfd_dbgmgr_रेजिस्टर(dbgmgr_ptr, p);
			अगर (status != 0)
				kfd_dbgmgr_destroy(dbgmgr_ptr);
			अन्यथा
				dev->dbgmgr = dbgmgr_ptr;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_debug("debugger already registered\n");
		status = -EINVAL;
	पूर्ण

out:
	mutex_unlock(kfd_get_dbgmgr_mutex());
	mutex_unlock(&p->mutex);

	वापस status;
पूर्ण

अटल पूर्णांक kfd_ioctl_dbg_unरेजिस्टर(काष्ठा file *filep,
				काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_dbg_unरेजिस्टर_args *args = data;
	काष्ठा kfd_dev *dev;
	दीर्घ status;

	dev = kfd_device_by_id(args->gpu_id);
	अगर (!dev || !dev->dbgmgr)
		वापस -EINVAL;

	अगर (dev->device_info->asic_family == CHIP_CARRIZO) अणु
		pr_debug("kfd_ioctl_dbg_unregister not supported on CZ\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(kfd_get_dbgmgr_mutex());

	status = kfd_dbgmgr_unरेजिस्टर(dev->dbgmgr, p);
	अगर (!status) अणु
		kfd_dbgmgr_destroy(dev->dbgmgr);
		dev->dbgmgr = शून्य;
	पूर्ण

	mutex_unlock(kfd_get_dbgmgr_mutex());

	वापस status;
पूर्ण

/*
 * Parse and generate variable size data काष्ठाure क्रम address watch.
 * Total size of the buffer and # watch poपूर्णांकs is limited in order
 * to prevent kernel abuse. (no bearing to the much smaller HW limitation
 * which is enक्रमced by dbgdev module)
 * please also note that the watch address itself are not "copied from user",
 * since it be set पूर्णांकo the HW in user mode values.
 *
 */
अटल पूर्णांक kfd_ioctl_dbg_address_watch(काष्ठा file *filep,
					काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_dbg_address_watch_args *args = data;
	काष्ठा kfd_dev *dev;
	काष्ठा dbg_address_watch_info aw_info;
	अचिन्हित अक्षर *args_buff;
	दीर्घ status;
	व्योम __user *cmd_from_user;
	uपूर्णांक64_t watch_mask_value = 0;
	अचिन्हित पूर्णांक args_idx = 0;

	स_रखो((व्योम *) &aw_info, 0, माप(काष्ठा dbg_address_watch_info));

	dev = kfd_device_by_id(args->gpu_id);
	अगर (!dev)
		वापस -EINVAL;

	अगर (dev->device_info->asic_family == CHIP_CARRIZO) अणु
		pr_debug("kfd_ioctl_dbg_wave_control not supported on CZ\n");
		वापस -EINVAL;
	पूर्ण

	cmd_from_user = (व्योम __user *) args->content_ptr;

	/* Validate arguments */

	अगर ((args->buf_size_in_bytes > MAX_ALLOWED_AW_BUFF_SIZE) ||
		(args->buf_size_in_bytes <= माप(*args) + माप(पूर्णांक) * 2) ||
		(cmd_from_user == शून्य))
		वापस -EINVAL;

	/* this is the actual buffer to work with */
	args_buff = memdup_user(cmd_from_user,
				args->buf_size_in_bytes - माप(*args));
	अगर (IS_ERR(args_buff))
		वापस PTR_ERR(args_buff);

	aw_info.process = p;

	aw_info.num_watch_poपूर्णांकs = *((uपूर्णांक32_t *)(&args_buff[args_idx]));
	args_idx += माप(aw_info.num_watch_poपूर्णांकs);

	aw_info.watch_mode = (क्रमागत HSA_DBG_WATCH_MODE *) &args_buff[args_idx];
	args_idx += माप(क्रमागत HSA_DBG_WATCH_MODE) * aw_info.num_watch_poपूर्णांकs;

	/*
	 * set watch address base poपूर्णांकer to poपूर्णांक on the array base
	 * within args_buff
	 */
	aw_info.watch_address = (uपूर्णांक64_t *) &args_buff[args_idx];

	/* skip over the addresses buffer */
	args_idx += माप(aw_info.watch_address) * aw_info.num_watch_poपूर्णांकs;

	अगर (args_idx >= args->buf_size_in_bytes - माप(*args)) अणु
		status = -EINVAL;
		जाओ out;
	पूर्ण

	watch_mask_value = (uपूर्णांक64_t) args_buff[args_idx];

	अगर (watch_mask_value > 0) अणु
		/*
		 * There is an array of masks.
		 * set watch mask base poपूर्णांकer to poपूर्णांक on the array base
		 * within args_buff
		 */
		aw_info.watch_mask = (uपूर्णांक64_t *) &args_buff[args_idx];

		/* skip over the masks buffer */
		args_idx += माप(aw_info.watch_mask) *
				aw_info.num_watch_poपूर्णांकs;
	पूर्ण अन्यथा अणु
		/* just the शून्य mask, set to शून्य and skip over it */
		aw_info.watch_mask = शून्य;
		args_idx += माप(aw_info.watch_mask);
	पूर्ण

	अगर (args_idx >= args->buf_size_in_bytes - माप(args)) अणु
		status = -EINVAL;
		जाओ out;
	पूर्ण

	/* Currently HSA Event is not supported क्रम DBG */
	aw_info.watch_event = शून्य;

	mutex_lock(kfd_get_dbgmgr_mutex());

	status = kfd_dbgmgr_address_watch(dev->dbgmgr, &aw_info);

	mutex_unlock(kfd_get_dbgmgr_mutex());

out:
	kमुक्त(args_buff);

	वापस status;
पूर्ण

/* Parse and generate fixed size data काष्ठाure क्रम wave control */
अटल पूर्णांक kfd_ioctl_dbg_wave_control(काष्ठा file *filep,
					काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_dbg_wave_control_args *args = data;
	काष्ठा kfd_dev *dev;
	काष्ठा dbg_wave_control_info wac_info;
	अचिन्हित अक्षर *args_buff;
	uपूर्णांक32_t computed_buff_size;
	दीर्घ status;
	व्योम __user *cmd_from_user;
	अचिन्हित पूर्णांक args_idx = 0;

	स_रखो((व्योम *) &wac_info, 0, माप(काष्ठा dbg_wave_control_info));

	/* we use compact क्रमm, independent of the packing attribute value */
	computed_buff_size = माप(*args) +
				माप(wac_info.mode) +
				माप(wac_info.opeअक्रम) +
				माप(wac_info.dbgWave_msg.DbgWaveMsg) +
				माप(wac_info.dbgWave_msg.MemoryVA) +
				माप(wac_info.trapId);

	dev = kfd_device_by_id(args->gpu_id);
	अगर (!dev)
		वापस -EINVAL;

	अगर (dev->device_info->asic_family == CHIP_CARRIZO) अणु
		pr_debug("kfd_ioctl_dbg_wave_control not supported on CZ\n");
		वापस -EINVAL;
	पूर्ण

	/* input size must match the computed "compact" size */
	अगर (args->buf_size_in_bytes != computed_buff_size) अणु
		pr_debug("size mismatch, computed : actual %u : %u\n",
				args->buf_size_in_bytes, computed_buff_size);
		वापस -EINVAL;
	पूर्ण

	cmd_from_user = (व्योम __user *) args->content_ptr;

	अगर (cmd_from_user == शून्य)
		वापस -EINVAL;

	/* copy the entire buffer from user */

	args_buff = memdup_user(cmd_from_user,
				args->buf_size_in_bytes - माप(*args));
	अगर (IS_ERR(args_buff))
		वापस PTR_ERR(args_buff);

	/* move ptr to the start of the "pay-load" area */
	wac_info.process = p;

	wac_info.opeअक्रम = *((क्रमागत HSA_DBG_WAVEOP *)(&args_buff[args_idx]));
	args_idx += माप(wac_info.opeअक्रम);

	wac_info.mode = *((क्रमागत HSA_DBG_WAVEMODE *)(&args_buff[args_idx]));
	args_idx += माप(wac_info.mode);

	wac_info.trapId = *((uपूर्णांक32_t *)(&args_buff[args_idx]));
	args_idx += माप(wac_info.trapId);

	wac_info.dbgWave_msg.DbgWaveMsg.WaveMsgInfoGen2.Value =
					*((uपूर्णांक32_t *)(&args_buff[args_idx]));
	wac_info.dbgWave_msg.MemoryVA = शून्य;

	mutex_lock(kfd_get_dbgmgr_mutex());

	pr_debug("Calling dbg manager process %p, operand %u, mode %u, trapId %u, message %u\n",
			wac_info.process, wac_info.opeअक्रम,
			wac_info.mode, wac_info.trapId,
			wac_info.dbgWave_msg.DbgWaveMsg.WaveMsgInfoGen2.Value);

	status = kfd_dbgmgr_wave_control(dev->dbgmgr, &wac_info);

	pr_debug("Returned status of dbg manager is %ld\n", status);

	mutex_unlock(kfd_get_dbgmgr_mutex());

	kमुक्त(args_buff);

	वापस status;
पूर्ण

अटल पूर्णांक kfd_ioctl_get_घड़ी_counters(काष्ठा file *filep,
				काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_get_घड़ी_counters_args *args = data;
	काष्ठा kfd_dev *dev;

	dev = kfd_device_by_id(args->gpu_id);
	अगर (dev)
		/* Reading GPU घड़ी counter from KGD */
		args->gpu_घड़ी_counter = amdgpu_amdkfd_get_gpu_घड़ी_counter(dev->kgd);
	अन्यथा
		/* Node without GPU resource */
		args->gpu_घड़ी_counter = 0;

	/* No access to rdtsc. Using raw monotonic समय */
	args->cpu_घड़ी_counter = kसमय_get_raw_ns();
	args->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();

	/* Since the counter is in nano-seconds we use 1GHz frequency */
	args->प्रणाली_घड़ी_freq = 1000000000;

	वापस 0;
पूर्ण


अटल पूर्णांक kfd_ioctl_get_process_apertures(काष्ठा file *filp,
				काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_get_process_apertures_args *args = data;
	काष्ठा kfd_process_device_apertures *pAperture;
	पूर्णांक i;

	dev_dbg(kfd_device, "get apertures for PASID 0x%x", p->pasid);

	args->num_of_nodes = 0;

	mutex_lock(&p->mutex);
	/* Run over all pdd of the process */
	क्रम (i = 0; i < p->n_pdds; i++) अणु
		काष्ठा kfd_process_device *pdd = p->pdds[i];

		pAperture =
			&args->process_apertures[args->num_of_nodes];
		pAperture->gpu_id = pdd->dev->id;
		pAperture->lds_base = pdd->lds_base;
		pAperture->lds_limit = pdd->lds_limit;
		pAperture->gpuvm_base = pdd->gpuvm_base;
		pAperture->gpuvm_limit = pdd->gpuvm_limit;
		pAperture->scratch_base = pdd->scratch_base;
		pAperture->scratch_limit = pdd->scratch_limit;

		dev_dbg(kfd_device,
			"node id %u\n", args->num_of_nodes);
		dev_dbg(kfd_device,
			"gpu id %u\n", pdd->dev->id);
		dev_dbg(kfd_device,
			"lds_base %llX\n", pdd->lds_base);
		dev_dbg(kfd_device,
			"lds_limit %llX\n", pdd->lds_limit);
		dev_dbg(kfd_device,
			"gpuvm_base %llX\n", pdd->gpuvm_base);
		dev_dbg(kfd_device,
			"gpuvm_limit %llX\n", pdd->gpuvm_limit);
		dev_dbg(kfd_device,
			"scratch_base %llX\n", pdd->scratch_base);
		dev_dbg(kfd_device,
			"scratch_limit %llX\n", pdd->scratch_limit);

		अगर (++args->num_of_nodes >= NUM_OF_SUPPORTED_GPUS)
			अवरोध;
	पूर्ण
	mutex_unlock(&p->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक kfd_ioctl_get_process_apertures_new(काष्ठा file *filp,
				काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_get_process_apertures_new_args *args = data;
	काष्ठा kfd_process_device_apertures *pa;
	पूर्णांक ret;
	पूर्णांक i;

	dev_dbg(kfd_device, "get apertures for PASID 0x%x", p->pasid);

	अगर (args->num_of_nodes == 0) अणु
		/* Return number of nodes, so that user space can alloacate
		 * sufficient memory
		 */
		mutex_lock(&p->mutex);
		args->num_of_nodes = p->n_pdds;
		जाओ out_unlock;
	पूर्ण

	/* Fill in process-aperture inक्रमmation क्रम all available
	 * nodes, but not more than args->num_of_nodes as that is
	 * the amount of memory allocated by user
	 */
	pa = kzalloc((माप(काष्ठा kfd_process_device_apertures) *
				args->num_of_nodes), GFP_KERNEL);
	अगर (!pa)
		वापस -ENOMEM;

	mutex_lock(&p->mutex);

	अगर (!p->n_pdds) अणु
		args->num_of_nodes = 0;
		kमुक्त(pa);
		जाओ out_unlock;
	पूर्ण

	/* Run over all pdd of the process */
	क्रम (i = 0; i < min(p->n_pdds, args->num_of_nodes); i++) अणु
		काष्ठा kfd_process_device *pdd = p->pdds[i];

		pa[i].gpu_id = pdd->dev->id;
		pa[i].lds_base = pdd->lds_base;
		pa[i].lds_limit = pdd->lds_limit;
		pa[i].gpuvm_base = pdd->gpuvm_base;
		pa[i].gpuvm_limit = pdd->gpuvm_limit;
		pa[i].scratch_base = pdd->scratch_base;
		pa[i].scratch_limit = pdd->scratch_limit;

		dev_dbg(kfd_device,
			"gpu id %u\n", pdd->dev->id);
		dev_dbg(kfd_device,
			"lds_base %llX\n", pdd->lds_base);
		dev_dbg(kfd_device,
			"lds_limit %llX\n", pdd->lds_limit);
		dev_dbg(kfd_device,
			"gpuvm_base %llX\n", pdd->gpuvm_base);
		dev_dbg(kfd_device,
			"gpuvm_limit %llX\n", pdd->gpuvm_limit);
		dev_dbg(kfd_device,
			"scratch_base %llX\n", pdd->scratch_base);
		dev_dbg(kfd_device,
			"scratch_limit %llX\n", pdd->scratch_limit);
	पूर्ण
	mutex_unlock(&p->mutex);

	args->num_of_nodes = i;
	ret = copy_to_user(
			(व्योम __user *)args->kfd_process_device_apertures_ptr,
			pa,
			(i * माप(काष्ठा kfd_process_device_apertures)));
	kमुक्त(pa);
	वापस ret ? -EFAULT : 0;

out_unlock:
	mutex_unlock(&p->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक kfd_ioctl_create_event(काष्ठा file *filp, काष्ठा kfd_process *p,
					व्योम *data)
अणु
	काष्ठा kfd_ioctl_create_event_args *args = data;
	पूर्णांक err;

	/* For dGPUs the event page is allocated in user mode. The
	 * handle is passed to KFD with the first call to this IOCTL
	 * through the event_page_offset field.
	 */
	अगर (args->event_page_offset) अणु
		काष्ठा kfd_dev *kfd;
		काष्ठा kfd_process_device *pdd;
		व्योम *mem, *kern_addr;
		uपूर्णांक64_t size;

		अगर (p->संकेत_page) अणु
			pr_err("Event page is already set\n");
			वापस -EINVAL;
		पूर्ण

		kfd = kfd_device_by_id(GET_GPU_ID(args->event_page_offset));
		अगर (!kfd) अणु
			pr_err("Getting device by id failed in %s\n", __func__);
			वापस -EINVAL;
		पूर्ण

		mutex_lock(&p->mutex);
		pdd = kfd_bind_process_to_device(kfd, p);
		अगर (IS_ERR(pdd)) अणु
			err = PTR_ERR(pdd);
			जाओ out_unlock;
		पूर्ण

		mem = kfd_process_device_translate_handle(pdd,
				GET_IDR_HANDLE(args->event_page_offset));
		अगर (!mem) अणु
			pr_err("Can't find BO, offset is 0x%llx\n",
			       args->event_page_offset);
			err = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		mutex_unlock(&p->mutex);

		err = amdgpu_amdkfd_gpuvm_map_gtt_bo_to_kernel(kfd->kgd,
						mem, &kern_addr, &size);
		अगर (err) अणु
			pr_err("Failed to map event page to kernel\n");
			वापस err;
		पूर्ण

		err = kfd_event_page_set(p, kern_addr, size);
		अगर (err) अणु
			pr_err("Failed to set event page\n");
			वापस err;
		पूर्ण
	पूर्ण

	err = kfd_event_create(filp, p, args->event_type,
				args->स्वतः_reset != 0, args->node_id,
				&args->event_id, &args->event_trigger_data,
				&args->event_page_offset,
				&args->event_slot_index);

	वापस err;

out_unlock:
	mutex_unlock(&p->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक kfd_ioctl_destroy_event(काष्ठा file *filp, काष्ठा kfd_process *p,
					व्योम *data)
अणु
	काष्ठा kfd_ioctl_destroy_event_args *args = data;

	वापस kfd_event_destroy(p, args->event_id);
पूर्ण

अटल पूर्णांक kfd_ioctl_set_event(काष्ठा file *filp, काष्ठा kfd_process *p,
				व्योम *data)
अणु
	काष्ठा kfd_ioctl_set_event_args *args = data;

	वापस kfd_set_event(p, args->event_id);
पूर्ण

अटल पूर्णांक kfd_ioctl_reset_event(काष्ठा file *filp, काष्ठा kfd_process *p,
				व्योम *data)
अणु
	काष्ठा kfd_ioctl_reset_event_args *args = data;

	वापस kfd_reset_event(p, args->event_id);
पूर्ण

अटल पूर्णांक kfd_ioctl_रुको_events(काष्ठा file *filp, काष्ठा kfd_process *p,
				व्योम *data)
अणु
	काष्ठा kfd_ioctl_रुको_events_args *args = data;
	पूर्णांक err;

	err = kfd_रुको_on_events(p, args->num_events,
			(व्योम __user *)args->events_ptr,
			(args->रुको_क्रम_all != 0),
			args->समयout, &args->रुको_result);

	वापस err;
पूर्ण
अटल पूर्णांक kfd_ioctl_set_scratch_backing_va(काष्ठा file *filep,
					काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_set_scratch_backing_बहु_तर्कs *args = data;
	काष्ठा kfd_process_device *pdd;
	काष्ठा kfd_dev *dev;
	दीर्घ err;

	dev = kfd_device_by_id(args->gpu_id);
	अगर (!dev)
		वापस -EINVAL;

	mutex_lock(&p->mutex);

	pdd = kfd_bind_process_to_device(dev, p);
	अगर (IS_ERR(pdd)) अणु
		err = PTR_ERR(pdd);
		जाओ bind_process_to_device_fail;
	पूर्ण

	pdd->qpd.sh_hidden_निजी_base = args->va_addr;

	mutex_unlock(&p->mutex);

	अगर (dev->dqm->sched_policy == KFD_SCHED_POLICY_NO_HWS &&
	    pdd->qpd.vmid != 0 && dev->kfd2kgd->set_scratch_backing_va)
		dev->kfd2kgd->set_scratch_backing_va(
			dev->kgd, args->va_addr, pdd->qpd.vmid);

	वापस 0;

bind_process_to_device_fail:
	mutex_unlock(&p->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक kfd_ioctl_get_tile_config(काष्ठा file *filep,
		काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_get_tile_config_args *args = data;
	काष्ठा kfd_dev *dev;
	काष्ठा tile_config config;
	पूर्णांक err = 0;

	dev = kfd_device_by_id(args->gpu_id);
	अगर (!dev)
		वापस -EINVAL;

	amdgpu_amdkfd_get_tile_config(dev->kgd, &config);

	args->gb_addr_config = config.gb_addr_config;
	args->num_banks = config.num_banks;
	args->num_ranks = config.num_ranks;

	अगर (args->num_tile_configs > config.num_tile_configs)
		args->num_tile_configs = config.num_tile_configs;
	err = copy_to_user((व्योम __user *)args->tile_config_ptr,
			config.tile_config_ptr,
			args->num_tile_configs * माप(uपूर्णांक32_t));
	अगर (err) अणु
		args->num_tile_configs = 0;
		वापस -EFAULT;
	पूर्ण

	अगर (args->num_macro_tile_configs > config.num_macro_tile_configs)
		args->num_macro_tile_configs =
				config.num_macro_tile_configs;
	err = copy_to_user((व्योम __user *)args->macro_tile_config_ptr,
			config.macro_tile_config_ptr,
			args->num_macro_tile_configs * माप(uपूर्णांक32_t));
	अगर (err) अणु
		args->num_macro_tile_configs = 0;
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kfd_ioctl_acquire_vm(काष्ठा file *filep, काष्ठा kfd_process *p,
				व्योम *data)
अणु
	काष्ठा kfd_ioctl_acquire_vm_args *args = data;
	काष्ठा kfd_process_device *pdd;
	काष्ठा kfd_dev *dev;
	काष्ठा file *drm_file;
	पूर्णांक ret;

	dev = kfd_device_by_id(args->gpu_id);
	अगर (!dev)
		वापस -EINVAL;

	drm_file = fget(args->drm_fd);
	अगर (!drm_file)
		वापस -EINVAL;

	mutex_lock(&p->mutex);

	pdd = kfd_get_process_device_data(dev, p);
	अगर (!pdd) अणु
		ret = -EINVAL;
		जाओ err_unlock;
	पूर्ण

	अगर (pdd->drm_file) अणु
		ret = pdd->drm_file == drm_file ? 0 : -EBUSY;
		जाओ err_unlock;
	पूर्ण

	ret = kfd_process_device_init_vm(pdd, drm_file);
	अगर (ret)
		जाओ err_unlock;
	/* On success, the PDD keeps the drm_file reference */
	mutex_unlock(&p->mutex);

	वापस 0;

err_unlock:
	mutex_unlock(&p->mutex);
	fput(drm_file);
	वापस ret;
पूर्ण

bool kfd_dev_is_large_bar(काष्ठा kfd_dev *dev)
अणु
	काष्ठा kfd_local_mem_info mem_info;

	अगर (debug_largebar) अणु
		pr_debug("Simulate large-bar allocation on non large-bar machine\n");
		वापस true;
	पूर्ण

	अगर (dev->use_iommu_v2)
		वापस false;

	amdgpu_amdkfd_get_local_mem_info(dev->kgd, &mem_info);
	अगर (mem_info.local_mem_size_निजी == 0 &&
			mem_info.local_mem_size_खुला > 0)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक kfd_ioctl_alloc_memory_of_gpu(काष्ठा file *filep,
					काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_alloc_memory_of_gpu_args *args = data;
	काष्ठा kfd_process_device *pdd;
	व्योम *mem;
	काष्ठा kfd_dev *dev;
	पूर्णांक idr_handle;
	दीर्घ err;
	uपूर्णांक64_t offset = args->mmap_offset;
	uपूर्णांक32_t flags = args->flags;

	अगर (args->size == 0)
		वापस -EINVAL;

	dev = kfd_device_by_id(args->gpu_id);
	अगर (!dev)
		वापस -EINVAL;

	अगर ((flags & KFD_IOC_ALLOC_MEM_FLAGS_PUBLIC) &&
		(flags & KFD_IOC_ALLOC_MEM_FLAGS_VRAM) &&
		!kfd_dev_is_large_bar(dev)) अणु
		pr_err("Alloc host visible vram on small bar is not allowed\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&p->mutex);

	pdd = kfd_bind_process_to_device(dev, p);
	अगर (IS_ERR(pdd)) अणु
		err = PTR_ERR(pdd);
		जाओ err_unlock;
	पूर्ण

	अगर (flags & KFD_IOC_ALLOC_MEM_FLAGS_DOORBELL) अणु
		अगर (args->size != kfd_करोorbell_process_slice(dev)) अणु
			err = -EINVAL;
			जाओ err_unlock;
		पूर्ण
		offset = kfd_get_process_करोorbells(pdd);
	पूर्ण अन्यथा अगर (flags & KFD_IOC_ALLOC_MEM_FLAGS_MMIO_REMAP) अणु
		अगर (args->size != PAGE_SIZE) अणु
			err = -EINVAL;
			जाओ err_unlock;
		पूर्ण
		offset = amdgpu_amdkfd_get_mmio_remap_phys_addr(dev->kgd);
		अगर (!offset) अणु
			err = -ENOMEM;
			जाओ err_unlock;
		पूर्ण
	पूर्ण

	err = amdgpu_amdkfd_gpuvm_alloc_memory_of_gpu(
		dev->kgd, args->va_addr, args->size,
		pdd->vm, (काष्ठा kgd_mem **) &mem, &offset,
		flags);

	अगर (err)
		जाओ err_unlock;

	idr_handle = kfd_process_device_create_obj_handle(pdd, mem);
	अगर (idr_handle < 0) अणु
		err = -EFAULT;
		जाओ err_मुक्त;
	पूर्ण

	/* Update the VRAM usage count */
	अगर (flags & KFD_IOC_ALLOC_MEM_FLAGS_VRAM)
		WRITE_ONCE(pdd->vram_usage, pdd->vram_usage + args->size);

	mutex_unlock(&p->mutex);

	args->handle = MAKE_HANDLE(args->gpu_id, idr_handle);
	args->mmap_offset = offset;

	/* MMIO is mapped through kfd device
	 * Generate a kfd mmap offset
	 */
	अगर (flags & KFD_IOC_ALLOC_MEM_FLAGS_MMIO_REMAP)
		args->mmap_offset = KFD_MMAP_TYPE_MMIO
					| KFD_MMAP_GPU_ID(args->gpu_id);

	वापस 0;

err_मुक्त:
	amdgpu_amdkfd_gpuvm_मुक्त_memory_of_gpu(dev->kgd, (काष्ठा kgd_mem *)mem, शून्य);
err_unlock:
	mutex_unlock(&p->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक kfd_ioctl_मुक्त_memory_of_gpu(काष्ठा file *filep,
					काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_मुक्त_memory_of_gpu_args *args = data;
	काष्ठा kfd_process_device *pdd;
	व्योम *mem;
	काष्ठा kfd_dev *dev;
	पूर्णांक ret;
	uपूर्णांक64_t size = 0;

	dev = kfd_device_by_id(GET_GPU_ID(args->handle));
	अगर (!dev)
		वापस -EINVAL;

	mutex_lock(&p->mutex);

	pdd = kfd_get_process_device_data(dev, p);
	अगर (!pdd) अणु
		pr_err("Process device data doesn't exist\n");
		ret = -EINVAL;
		जाओ err_unlock;
	पूर्ण

	mem = kfd_process_device_translate_handle(
		pdd, GET_IDR_HANDLE(args->handle));
	अगर (!mem) अणु
		ret = -EINVAL;
		जाओ err_unlock;
	पूर्ण

	ret = amdgpu_amdkfd_gpuvm_मुक्त_memory_of_gpu(dev->kgd,
						(काष्ठा kgd_mem *)mem, &size);

	/* If मुक्तing the buffer failed, leave the handle in place क्रम
	 * clean-up during process tear-करोwn.
	 */
	अगर (!ret)
		kfd_process_device_हटाओ_obj_handle(
			pdd, GET_IDR_HANDLE(args->handle));

	WRITE_ONCE(pdd->vram_usage, pdd->vram_usage - size);

err_unlock:
	mutex_unlock(&p->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक kfd_ioctl_map_memory_to_gpu(काष्ठा file *filep,
					काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_map_memory_to_gpu_args *args = data;
	काष्ठा kfd_process_device *pdd, *peer_pdd;
	व्योम *mem;
	काष्ठा kfd_dev *dev, *peer;
	दीर्घ err = 0;
	पूर्णांक i;
	uपूर्णांक32_t *devices_arr = शून्य;

	dev = kfd_device_by_id(GET_GPU_ID(args->handle));
	अगर (!dev)
		वापस -EINVAL;

	अगर (!args->n_devices) अणु
		pr_debug("Device IDs array empty\n");
		वापस -EINVAL;
	पूर्ण
	अगर (args->n_success > args->n_devices) अणु
		pr_debug("n_success exceeds n_devices\n");
		वापस -EINVAL;
	पूर्ण

	devices_arr = kदो_स्मृति_array(args->n_devices, माप(*devices_arr),
				    GFP_KERNEL);
	अगर (!devices_arr)
		वापस -ENOMEM;

	err = copy_from_user(devices_arr,
			     (व्योम __user *)args->device_ids_array_ptr,
			     args->n_devices * माप(*devices_arr));
	अगर (err != 0) अणु
		err = -EFAULT;
		जाओ copy_from_user_failed;
	पूर्ण

	mutex_lock(&p->mutex);

	pdd = kfd_bind_process_to_device(dev, p);
	अगर (IS_ERR(pdd)) अणु
		err = PTR_ERR(pdd);
		जाओ bind_process_to_device_failed;
	पूर्ण

	mem = kfd_process_device_translate_handle(pdd,
						GET_IDR_HANDLE(args->handle));
	अगर (!mem) अणु
		err = -ENOMEM;
		जाओ get_mem_obj_from_handle_failed;
	पूर्ण

	क्रम (i = args->n_success; i < args->n_devices; i++) अणु
		peer = kfd_device_by_id(devices_arr[i]);
		अगर (!peer) अणु
			pr_debug("Getting device by id failed for 0x%x\n",
				 devices_arr[i]);
			err = -EINVAL;
			जाओ get_mem_obj_from_handle_failed;
		पूर्ण

		peer_pdd = kfd_bind_process_to_device(peer, p);
		अगर (IS_ERR(peer_pdd)) अणु
			err = PTR_ERR(peer_pdd);
			जाओ get_mem_obj_from_handle_failed;
		पूर्ण
		err = amdgpu_amdkfd_gpuvm_map_memory_to_gpu(
			peer->kgd, (काष्ठा kgd_mem *)mem, peer_pdd->vm);
		अगर (err) अणु
			pr_err("Failed to map to gpu %d/%d\n",
			       i, args->n_devices);
			जाओ map_memory_to_gpu_failed;
		पूर्ण
		args->n_success = i+1;
	पूर्ण

	mutex_unlock(&p->mutex);

	err = amdgpu_amdkfd_gpuvm_sync_memory(dev->kgd, (काष्ठा kgd_mem *) mem, true);
	अगर (err) अणु
		pr_debug("Sync memory failed, wait interrupted by user signal\n");
		जाओ sync_memory_failed;
	पूर्ण

	/* Flush TLBs after रुकोing क्रम the page table updates to complete */
	क्रम (i = 0; i < args->n_devices; i++) अणु
		peer = kfd_device_by_id(devices_arr[i]);
		अगर (WARN_ON_ONCE(!peer))
			जारी;
		peer_pdd = kfd_get_process_device_data(peer, p);
		अगर (WARN_ON_ONCE(!peer_pdd))
			जारी;
		kfd_flush_tlb(peer_pdd);
	पूर्ण

	kमुक्त(devices_arr);

	वापस err;

bind_process_to_device_failed:
get_mem_obj_from_handle_failed:
map_memory_to_gpu_failed:
	mutex_unlock(&p->mutex);
copy_from_user_failed:
sync_memory_failed:
	kमुक्त(devices_arr);

	वापस err;
पूर्ण

अटल पूर्णांक kfd_ioctl_unmap_memory_from_gpu(काष्ठा file *filep,
					काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_unmap_memory_from_gpu_args *args = data;
	काष्ठा kfd_process_device *pdd, *peer_pdd;
	व्योम *mem;
	काष्ठा kfd_dev *dev, *peer;
	दीर्घ err = 0;
	uपूर्णांक32_t *devices_arr = शून्य, i;

	dev = kfd_device_by_id(GET_GPU_ID(args->handle));
	अगर (!dev)
		वापस -EINVAL;

	अगर (!args->n_devices) अणु
		pr_debug("Device IDs array empty\n");
		वापस -EINVAL;
	पूर्ण
	अगर (args->n_success > args->n_devices) अणु
		pr_debug("n_success exceeds n_devices\n");
		वापस -EINVAL;
	पूर्ण

	devices_arr = kदो_स्मृति_array(args->n_devices, माप(*devices_arr),
				    GFP_KERNEL);
	अगर (!devices_arr)
		वापस -ENOMEM;

	err = copy_from_user(devices_arr,
			     (व्योम __user *)args->device_ids_array_ptr,
			     args->n_devices * माप(*devices_arr));
	अगर (err != 0) अणु
		err = -EFAULT;
		जाओ copy_from_user_failed;
	पूर्ण

	mutex_lock(&p->mutex);

	pdd = kfd_get_process_device_data(dev, p);
	अगर (!pdd) अणु
		err = -EINVAL;
		जाओ bind_process_to_device_failed;
	पूर्ण

	mem = kfd_process_device_translate_handle(pdd,
						GET_IDR_HANDLE(args->handle));
	अगर (!mem) अणु
		err = -ENOMEM;
		जाओ get_mem_obj_from_handle_failed;
	पूर्ण

	क्रम (i = args->n_success; i < args->n_devices; i++) अणु
		peer = kfd_device_by_id(devices_arr[i]);
		अगर (!peer) अणु
			err = -EINVAL;
			जाओ get_mem_obj_from_handle_failed;
		पूर्ण

		peer_pdd = kfd_get_process_device_data(peer, p);
		अगर (!peer_pdd) अणु
			err = -ENODEV;
			जाओ get_mem_obj_from_handle_failed;
		पूर्ण
		err = amdgpu_amdkfd_gpuvm_unmap_memory_from_gpu(
			peer->kgd, (काष्ठा kgd_mem *)mem, peer_pdd->vm);
		अगर (err) अणु
			pr_err("Failed to unmap from gpu %d/%d\n",
			       i, args->n_devices);
			जाओ unmap_memory_from_gpu_failed;
		पूर्ण
		args->n_success = i+1;
	पूर्ण
	kमुक्त(devices_arr);

	mutex_unlock(&p->mutex);

	वापस 0;

bind_process_to_device_failed:
get_mem_obj_from_handle_failed:
unmap_memory_from_gpu_failed:
	mutex_unlock(&p->mutex);
copy_from_user_failed:
	kमुक्त(devices_arr);
	वापस err;
पूर्ण

अटल पूर्णांक kfd_ioctl_alloc_queue_gws(काष्ठा file *filep,
		काष्ठा kfd_process *p, व्योम *data)
अणु
	पूर्णांक retval;
	काष्ठा kfd_ioctl_alloc_queue_gws_args *args = data;
	काष्ठा queue *q;
	काष्ठा kfd_dev *dev;

	mutex_lock(&p->mutex);
	q = pqm_get_user_queue(&p->pqm, args->queue_id);

	अगर (q) अणु
		dev = q->device;
	पूर्ण अन्यथा अणु
		retval = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (!dev->gws) अणु
		retval = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	अगर (dev->dqm->sched_policy == KFD_SCHED_POLICY_NO_HWS) अणु
		retval = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	retval = pqm_set_gws(&p->pqm, args->queue_id, args->num_gws ? dev->gws : शून्य);
	mutex_unlock(&p->mutex);

	args->first_gws = 0;
	वापस retval;

out_unlock:
	mutex_unlock(&p->mutex);
	वापस retval;
पूर्ण

अटल पूर्णांक kfd_ioctl_get_dmabuf_info(काष्ठा file *filep,
		काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_get_dmabuf_info_args *args = data;
	काष्ठा kfd_dev *dev = शून्य;
	काष्ठा kgd_dev *dma_buf_kgd;
	व्योम *metadata_buffer = शून्य;
	uपूर्णांक32_t flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक r;

	/* Find a KFD GPU device that supports the get_dmabuf_info query */
	क्रम (i = 0; kfd_topology_क्रमागत_kfd_devices(i, &dev) == 0; i++)
		अगर (dev)
			अवरोध;
	अगर (!dev)
		वापस -EINVAL;

	अगर (args->metadata_ptr) अणु
		metadata_buffer = kzalloc(args->metadata_size, GFP_KERNEL);
		अगर (!metadata_buffer)
			वापस -ENOMEM;
	पूर्ण

	/* Get dmabuf info from KGD */
	r = amdgpu_amdkfd_get_dmabuf_info(dev->kgd, args->dmabuf_fd,
					  &dma_buf_kgd, &args->size,
					  metadata_buffer, args->metadata_size,
					  &args->metadata_size, &flags);
	अगर (r)
		जाओ निकास;

	/* Reverse-lookup gpu_id from kgd poपूर्णांकer */
	dev = kfd_device_by_kgd(dma_buf_kgd);
	अगर (!dev) अणु
		r = -EINVAL;
		जाओ निकास;
	पूर्ण
	args->gpu_id = dev->id;
	args->flags = flags;

	/* Copy metadata buffer to user mode */
	अगर (metadata_buffer) अणु
		r = copy_to_user((व्योम __user *)args->metadata_ptr,
				 metadata_buffer, args->metadata_size);
		अगर (r != 0)
			r = -EFAULT;
	पूर्ण

निकास:
	kमुक्त(metadata_buffer);

	वापस r;
पूर्ण

अटल पूर्णांक kfd_ioctl_import_dmabuf(काष्ठा file *filep,
				   काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_import_dmabuf_args *args = data;
	काष्ठा kfd_process_device *pdd;
	काष्ठा dma_buf *dmabuf;
	काष्ठा kfd_dev *dev;
	पूर्णांक idr_handle;
	uपूर्णांक64_t size;
	व्योम *mem;
	पूर्णांक r;

	dev = kfd_device_by_id(args->gpu_id);
	अगर (!dev)
		वापस -EINVAL;

	dmabuf = dma_buf_get(args->dmabuf_fd);
	अगर (IS_ERR(dmabuf))
		वापस PTR_ERR(dmabuf);

	mutex_lock(&p->mutex);

	pdd = kfd_bind_process_to_device(dev, p);
	अगर (IS_ERR(pdd)) अणु
		r = PTR_ERR(pdd);
		जाओ err_unlock;
	पूर्ण

	r = amdgpu_amdkfd_gpuvm_import_dmabuf(dev->kgd, dmabuf,
					      args->va_addr, pdd->vm,
					      (काष्ठा kgd_mem **)&mem, &size,
					      शून्य);
	अगर (r)
		जाओ err_unlock;

	idr_handle = kfd_process_device_create_obj_handle(pdd, mem);
	अगर (idr_handle < 0) अणु
		r = -EFAULT;
		जाओ err_मुक्त;
	पूर्ण

	mutex_unlock(&p->mutex);
	dma_buf_put(dmabuf);

	args->handle = MAKE_HANDLE(args->gpu_id, idr_handle);

	वापस 0;

err_मुक्त:
	amdgpu_amdkfd_gpuvm_मुक्त_memory_of_gpu(dev->kgd, (काष्ठा kgd_mem *)mem, शून्य);
err_unlock:
	mutex_unlock(&p->mutex);
	dma_buf_put(dmabuf);
	वापस r;
पूर्ण

/* Handle requests क्रम watching SMI events */
अटल पूर्णांक kfd_ioctl_smi_events(काष्ठा file *filep,
				काष्ठा kfd_process *p, व्योम *data)
अणु
	काष्ठा kfd_ioctl_smi_events_args *args = data;
	काष्ठा kfd_dev *dev;

	dev = kfd_device_by_id(args->gpuid);
	अगर (!dev)
		वापस -EINVAL;

	वापस kfd_smi_event_खोलो(dev, &args->anon_fd);
पूर्ण

#घोषणा AMDKFD_IOCTL_DEF(ioctl, _func, _flags) \
	[_IOC_NR(ioctl)] = अणु.cmd = ioctl, .func = _func, .flags = _flags, \
			    .cmd_drv = 0, .name = #ioctlपूर्ण

/** Ioctl table */
अटल स्थिर काष्ठा amdkfd_ioctl_desc amdkfd_ioctls[] = अणु
	AMDKFD_IOCTL_DEF(AMDKFD_IOC_GET_VERSION,
			kfd_ioctl_get_version, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_CREATE_QUEUE,
			kfd_ioctl_create_queue, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_DESTROY_QUEUE,
			kfd_ioctl_destroy_queue, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_SET_MEMORY_POLICY,
			kfd_ioctl_set_memory_policy, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_GET_CLOCK_COUNTERS,
			kfd_ioctl_get_घड़ी_counters, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_GET_PROCESS_APERTURES,
			kfd_ioctl_get_process_apertures, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_UPDATE_QUEUE,
			kfd_ioctl_update_queue, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_CREATE_EVENT,
			kfd_ioctl_create_event, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_DESTROY_EVENT,
			kfd_ioctl_destroy_event, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_SET_EVENT,
			kfd_ioctl_set_event, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_RESET_EVENT,
			kfd_ioctl_reset_event, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_WAIT_EVENTS,
			kfd_ioctl_रुको_events, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_DBG_REGISTER,
			kfd_ioctl_dbg_रेजिस्टर, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_DBG_UNREGISTER,
			kfd_ioctl_dbg_unरेजिस्टर, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_DBG_ADDRESS_WATCH,
			kfd_ioctl_dbg_address_watch, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_DBG_WAVE_CONTROL,
			kfd_ioctl_dbg_wave_control, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_SET_SCRATCH_BACKING_VA,
			kfd_ioctl_set_scratch_backing_va, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_GET_TILE_CONFIG,
			kfd_ioctl_get_tile_config, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_SET_TRAP_HANDLER,
			kfd_ioctl_set_trap_handler, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_GET_PROCESS_APERTURES_NEW,
			kfd_ioctl_get_process_apertures_new, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_ACQUIRE_VM,
			kfd_ioctl_acquire_vm, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_ALLOC_MEMORY_OF_GPU,
			kfd_ioctl_alloc_memory_of_gpu, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_FREE_MEMORY_OF_GPU,
			kfd_ioctl_मुक्त_memory_of_gpu, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_MAP_MEMORY_TO_GPU,
			kfd_ioctl_map_memory_to_gpu, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_UNMAP_MEMORY_FROM_GPU,
			kfd_ioctl_unmap_memory_from_gpu, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_SET_CU_MASK,
			kfd_ioctl_set_cu_mask, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_GET_QUEUE_WAVE_STATE,
			kfd_ioctl_get_queue_wave_state, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_GET_DMABUF_INFO,
				kfd_ioctl_get_dmabuf_info, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_IMPORT_DMABUF,
				kfd_ioctl_import_dmabuf, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_ALLOC_QUEUE_GWS,
			kfd_ioctl_alloc_queue_gws, 0),

	AMDKFD_IOCTL_DEF(AMDKFD_IOC_SMI_EVENTS,
			kfd_ioctl_smi_events, 0),
पूर्ण;

#घोषणा AMDKFD_CORE_IOCTL_COUNT	ARRAY_SIZE(amdkfd_ioctls)

अटल दीर्घ kfd_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kfd_process *process;
	amdkfd_ioctl_t *func;
	स्थिर काष्ठा amdkfd_ioctl_desc *ioctl = शून्य;
	अचिन्हित पूर्णांक nr = _IOC_NR(cmd);
	अक्षर stack_kdata[128];
	अक्षर *kdata = शून्य;
	अचिन्हित पूर्णांक usize, asize;
	पूर्णांक retcode = -EINVAL;

	अगर (nr >= AMDKFD_CORE_IOCTL_COUNT)
		जाओ err_i1;

	अगर ((nr >= AMDKFD_COMMAND_START) && (nr < AMDKFD_COMMAND_END)) अणु
		u32 amdkfd_size;

		ioctl = &amdkfd_ioctls[nr];

		amdkfd_size = _IOC_SIZE(ioctl->cmd);
		usize = asize = _IOC_SIZE(cmd);
		अगर (amdkfd_size > asize)
			asize = amdkfd_size;

		cmd = ioctl->cmd;
	पूर्ण अन्यथा
		जाओ err_i1;

	dev_dbg(kfd_device, "ioctl cmd 0x%x (#0x%x), arg 0x%lx\n", cmd, nr, arg);

	/* Get the process काष्ठा from the filep. Only the process
	 * that खोलोed /dev/kfd can use the file descriptor. Child
	 * processes need to create their own KFD device context.
	 */
	process = filep->निजी_data;
	अगर (process->lead_thपढ़ो != current->group_leader) अणु
		dev_dbg(kfd_device, "Using KFD FD in wrong process\n");
		retcode = -EBADF;
		जाओ err_i1;
	पूर्ण

	/* Do not trust userspace, use our own definition */
	func = ioctl->func;

	अगर (unlikely(!func)) अणु
		dev_dbg(kfd_device, "no function\n");
		retcode = -EINVAL;
		जाओ err_i1;
	पूर्ण

	अगर (cmd & (IOC_IN | IOC_OUT)) अणु
		अगर (asize <= माप(stack_kdata)) अणु
			kdata = stack_kdata;
		पूर्ण अन्यथा अणु
			kdata = kदो_स्मृति(asize, GFP_KERNEL);
			अगर (!kdata) अणु
				retcode = -ENOMEM;
				जाओ err_i1;
			पूर्ण
		पूर्ण
		अगर (asize > usize)
			स_रखो(kdata + usize, 0, asize - usize);
	पूर्ण

	अगर (cmd & IOC_IN) अणु
		अगर (copy_from_user(kdata, (व्योम __user *)arg, usize) != 0) अणु
			retcode = -EFAULT;
			जाओ err_i1;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd & IOC_OUT) अणु
		स_रखो(kdata, 0, usize);
	पूर्ण

	retcode = func(filep, process, kdata);

	अगर (cmd & IOC_OUT)
		अगर (copy_to_user((व्योम __user *)arg, kdata, usize) != 0)
			retcode = -EFAULT;

err_i1:
	अगर (!ioctl)
		dev_dbg(kfd_device, "invalid ioctl: pid=%d, cmd=0x%02x, nr=0x%02x\n",
			  task_pid_nr(current), cmd, nr);

	अगर (kdata != stack_kdata)
		kमुक्त(kdata);

	अगर (retcode)
		dev_dbg(kfd_device, "ioctl cmd (#0x%x), arg 0x%lx, ret = %d\n",
				nr, arg, retcode);

	वापस retcode;
पूर्ण

अटल पूर्णांक kfd_mmio_mmap(काष्ठा kfd_dev *dev, काष्ठा kfd_process *process,
		      काष्ठा vm_area_काष्ठा *vma)
अणु
	phys_addr_t address;
	पूर्णांक ret;

	अगर (vma->vm_end - vma->vm_start != PAGE_SIZE)
		वापस -EINVAL;

	address = amdgpu_amdkfd_get_mmio_remap_phys_addr(dev->kgd);

	vma->vm_flags |= VM_IO | VM_DONTCOPY | VM_DONTEXPAND | VM_NORESERVE |
				VM_DONTDUMP | VM_PFNMAP;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	pr_debug("pasid 0x%x mapping mmio page\n"
		 "     target user address == 0x%08llX\n"
		 "     physical address    == 0x%08llX\n"
		 "     vm_flags            == 0x%04lX\n"
		 "     size                == 0x%04lX\n",
		 process->pasid, (अचिन्हित दीर्घ दीर्घ) vma->vm_start,
		 address, vma->vm_flags, PAGE_SIZE);

	ret = io_remap_pfn_range(vma,
				vma->vm_start,
				address >> PAGE_SHIFT,
				PAGE_SIZE,
				vma->vm_page_prot);
	वापस ret;
पूर्ण


अटल पूर्णांक kfd_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा kfd_process *process;
	काष्ठा kfd_dev *dev = शून्य;
	अचिन्हित दीर्घ mmap_offset;
	अचिन्हित पूर्णांक gpu_id;

	process = kfd_get_process(current);
	अगर (IS_ERR(process))
		वापस PTR_ERR(process);

	mmap_offset = vma->vm_pgoff << PAGE_SHIFT;
	gpu_id = KFD_MMAP_GET_GPU_ID(mmap_offset);
	अगर (gpu_id)
		dev = kfd_device_by_id(gpu_id);

	चयन (mmap_offset & KFD_MMAP_TYPE_MASK) अणु
	हाल KFD_MMAP_TYPE_DOORBELL:
		अगर (!dev)
			वापस -ENODEV;
		वापस kfd_करोorbell_mmap(dev, process, vma);

	हाल KFD_MMAP_TYPE_EVENTS:
		वापस kfd_event_mmap(process, vma);

	हाल KFD_MMAP_TYPE_RESERVED_MEM:
		अगर (!dev)
			वापस -ENODEV;
		वापस kfd_reserved_mem_mmap(dev, process, vma);
	हाल KFD_MMAP_TYPE_MMIO:
		अगर (!dev)
			वापस -ENODEV;
		वापस kfd_mmio_mmap(dev, process, vma);
	पूर्ण

	वापस -EFAULT;
पूर्ण
