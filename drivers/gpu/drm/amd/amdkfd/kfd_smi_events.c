<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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

#समावेश <linux/poll.h>
#समावेश <linux/रुको.h>
#समावेश <linux/anon_inodes.h>
#समावेश <uapi/linux/kfd_ioctl.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_vm.h"
#समावेश "kfd_priv.h"
#समावेश "kfd_smi_events.h"

काष्ठा kfd_smi_client अणु
	काष्ठा list_head list;
	काष्ठा kfअगरo fअगरo;
	रुको_queue_head_t रुको_queue;
	/* events enabled */
	uपूर्णांक64_t events;
	काष्ठा kfd_dev *dev;
	spinlock_t lock;
पूर्ण;

#घोषणा MAX_KFIFO_SIZE	1024

अटल __poll_t kfd_smi_ev_poll(काष्ठा file *, काष्ठा poll_table_काष्ठा *);
अटल sमाप_प्रकार kfd_smi_ev_पढ़ो(काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
अटल sमाप_प्रकार kfd_smi_ev_ग_लिखो(काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार,
				loff_t *);
अटल पूर्णांक kfd_smi_ev_release(काष्ठा inode *, काष्ठा file *);

अटल स्थिर अक्षर kfd_smi_name[] = "kfd_smi_ev";

अटल स्थिर काष्ठा file_operations kfd_smi_ev_fops = अणु
	.owner = THIS_MODULE,
	.poll = kfd_smi_ev_poll,
	.पढ़ो = kfd_smi_ev_पढ़ो,
	.ग_लिखो = kfd_smi_ev_ग_लिखो,
	.release = kfd_smi_ev_release
पूर्ण;

अटल __poll_t kfd_smi_ev_poll(काष्ठा file *filep,
				काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा kfd_smi_client *client = filep->निजी_data;
	__poll_t mask = 0;

	poll_रुको(filep, &client->रुको_queue, रुको);

	spin_lock(&client->lock);
	अगर (!kfअगरo_is_empty(&client->fअगरo))
		mask = EPOLLIN | EPOLLRDNORM;
	spin_unlock(&client->lock);

	वापस mask;
पूर्ण

अटल sमाप_प्रकार kfd_smi_ev_पढ़ो(काष्ठा file *filep, अक्षर __user *user,
			       माप_प्रकार size, loff_t *offset)
अणु
	पूर्णांक ret;
	माप_प्रकार to_copy;
	काष्ठा kfd_smi_client *client = filep->निजी_data;
	अचिन्हित अक्षर *buf;

	buf = kदो_स्मृति_array(MAX_KFIFO_SIZE, माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* kfअगरo_to_user can sleep so we can't use spinlock protection around
	 * it. Instead, we kfअगरo out as spinlocked then copy them to the user.
	 */
	spin_lock(&client->lock);
	to_copy = kfअगरo_len(&client->fअगरo);
	अगर (!to_copy) अणु
		spin_unlock(&client->lock);
		ret = -EAGAIN;
		जाओ ret_err;
	पूर्ण
	to_copy = min3(size, माप(buf), to_copy);
	ret = kfअगरo_out(&client->fअगरo, buf, to_copy);
	spin_unlock(&client->lock);
	अगर (ret <= 0) अणु
		ret = -EAGAIN;
		जाओ ret_err;
	पूर्ण

	ret = copy_to_user(user, buf, to_copy);
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ ret_err;
	पूर्ण

	kमुक्त(buf);
	वापस to_copy;

ret_err:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार kfd_smi_ev_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *user,
				माप_प्रकार size, loff_t *offset)
अणु
	काष्ठा kfd_smi_client *client = filep->निजी_data;
	uपूर्णांक64_t events;

	अगर (!access_ok(user, size) || size < माप(events))
		वापस -EFAULT;
	अगर (copy_from_user(&events, user, माप(events)))
		वापस -EFAULT;

	WRITE_ONCE(client->events, events);

	वापस माप(events);
पूर्ण

अटल पूर्णांक kfd_smi_ev_release(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा kfd_smi_client *client = filep->निजी_data;
	काष्ठा kfd_dev *dev = client->dev;

	spin_lock(&dev->smi_lock);
	list_del_rcu(&client->list);
	spin_unlock(&dev->smi_lock);

	synchronize_rcu();
	kfअगरo_मुक्त(&client->fअगरo);
	kमुक्त(client);

	वापस 0;
पूर्ण

अटल व्योम add_event_to_kfअगरo(काष्ठा kfd_dev *dev, अचिन्हित पूर्णांक smi_event,
			      अक्षर *event_msg, पूर्णांक len)
अणु
	काष्ठा kfd_smi_client *client;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(client, &dev->smi_clients, list) अणु
		अगर (!(READ_ONCE(client->events) &
				KFD_SMI_EVENT_MASK_FROM_INDEX(smi_event)))
			जारी;
		spin_lock(&client->lock);
		अगर (kfअगरo_avail(&client->fअगरo) >= len) अणु
			kfअगरo_in(&client->fअगरo, event_msg, len);
			wake_up_all(&client->रुको_queue);
		पूर्ण अन्यथा अणु
			pr_debug("smi_event(EventID: %u): no space left\n",
					smi_event);
		पूर्ण
		spin_unlock(&client->lock);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

व्योम kfd_smi_event_update_gpu_reset(काष्ठा kfd_dev *dev, bool post_reset)
अणु
	/*
	 * GpuReset msg = Reset seq number (incremented क्रम
	 * every reset message sent beक्रमe GPU reset).
	 * 1 byte event + 1 byte space + 8 bytes seq num +
	 * 1 byte \न + 1 byte \0 = 12
	 */
	अक्षर fअगरo_in[12];
	पूर्णांक len;
	अचिन्हित पूर्णांक event;

	अगर (list_empty(&dev->smi_clients))
		वापस;

	स_रखो(fअगरo_in, 0x0, माप(fअगरo_in));

	अगर (post_reset) अणु
		event = KFD_SMI_EVENT_GPU_POST_RESET;
	पूर्ण अन्यथा अणु
		event = KFD_SMI_EVENT_GPU_PRE_RESET;
		++(dev->reset_seq_num);
	पूर्ण

	len = snम_लिखो(fअगरo_in, माप(fअगरo_in), "%x %x\n", event,
						dev->reset_seq_num);

	add_event_to_kfअगरo(dev, event, fअगरo_in, len);
पूर्ण

व्योम kfd_smi_event_update_thermal_throttling(काष्ठा kfd_dev *dev,
					     uपूर्णांक32_t throttle_biपंचांगask)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)dev->kgd;
	/*
	 * ThermalThrottle msg = throttle_biपंचांगask(8):
	 * 			 thermal_पूर्णांकerrupt_count(16):
	 * 1 byte event + 1 byte space + 8 byte throttle_biपंचांगask +
	 * 1 byte : + 16 byte thermal_पूर्णांकerupt_counter + 1 byte \न +
	 * 1 byte \0 = 29
	 */
	अक्षर fअगरo_in[29];
	पूर्णांक len;

	अगर (list_empty(&dev->smi_clients))
		वापस;

	len = snम_लिखो(fअगरo_in, माप(fअगरo_in), "%x %x:%llx\n",
		       KFD_SMI_EVENT_THERMAL_THROTTLE, throttle_biपंचांगask,
		       atomic64_पढ़ो(&adev->smu.throttle_पूर्णांक_counter));

	add_event_to_kfअगरo(dev, KFD_SMI_EVENT_THERMAL_THROTTLE,	fअगरo_in, len);
पूर्ण

व्योम kfd_smi_event_update_vmfault(काष्ठा kfd_dev *dev, uपूर्णांक16_t pasid)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)dev->kgd;
	काष्ठा amdgpu_task_info task_info;
	/* VmFault msg = (hex)uपूर्णांक32_pid(8) + :(1) + task name(16) = 25 */
	/* 1 byte event + 1 byte space + 25 bytes msg + 1 byte \न +
	 * 1 byte \0 = 29
	 */
	अक्षर fअगरo_in[29];
	पूर्णांक len;

	अगर (list_empty(&dev->smi_clients))
		वापस;

	स_रखो(&task_info, 0, माप(काष्ठा amdgpu_task_info));
	amdgpu_vm_get_task_info(adev, pasid, &task_info);
	/* Report VM faults from user applications, not retry from kernel */
	अगर (!task_info.pid)
		वापस;

	len = snम_लिखो(fअगरo_in, माप(fअगरo_in), "%x %x:%s\n", KFD_SMI_EVENT_VMFAULT,
		task_info.pid, task_info.task_name);

	add_event_to_kfअगरo(dev, KFD_SMI_EVENT_VMFAULT, fअगरo_in, len);
पूर्ण

पूर्णांक kfd_smi_event_खोलो(काष्ठा kfd_dev *dev, uपूर्णांक32_t *fd)
अणु
	काष्ठा kfd_smi_client *client;
	पूर्णांक ret;

	client = kzalloc(माप(काष्ठा kfd_smi_client), GFP_KERNEL);
	अगर (!client)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&client->list);

	ret = kfअगरo_alloc(&client->fअगरo, MAX_KFIFO_SIZE, GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(client);
		वापस ret;
	पूर्ण

	ret = anon_inode_getfd(kfd_smi_name, &kfd_smi_ev_fops, (व्योम *)client,
			       O_RDWR);
	अगर (ret < 0) अणु
		kfअगरo_मुक्त(&client->fअगरo);
		kमुक्त(client);
		वापस ret;
	पूर्ण
	*fd = ret;

	init_रुकोqueue_head(&client->रुको_queue);
	spin_lock_init(&client->lock);
	client->events = 0;
	client->dev = dev;

	spin_lock(&dev->smi_lock);
	list_add_rcu(&client->list, &dev->smi_clients);
	spin_unlock(&dev->smi_lock);

	वापस 0;
पूर्ण
